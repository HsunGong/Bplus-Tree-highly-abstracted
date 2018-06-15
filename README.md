 **TicketSystem[^title]**
=====
###                        ----imitate 12306
[TOC]

<!-- ## Catalog
0. Division of Labour
1. Front End
2. After End
3. Conclusion
4. CopyRight @ -->

## Division of Labour

| 工作划分  | 人员 |
| -
|    后端，前端    | Linqi Chen |
|    后端，前端    | Fangyuan Zhang |
|    后端，文档    | Xun Gong |

## Front End

### outline
1. 框架使用
- 服务器端使用flask，大量功能使用JavaScript实现，前后端连接使用boost库进行封装，

- "/" 为主域名，为消费者页面
- "/main" 为管理界面路由前缀，
- "/auth" 为管理界面用户路由

- 管理界面使用了一些bootstrap进行风格优化
- 消费界面未使用框架进行风格优化，由陈林淇自行设计风格
- 密码未用明文储存，进行了hash加密，保证服务器端用户密码安全
- 进行了CSRF保护（跨站请求伪造）
- 注册界面使用了邮箱验证，登录界面加入验证
- 从环境变量获取配置变量，提高安全系数
- 在蓝本中实现程序功能，提高了程序灵活度
- （程序工厂函数方便单元测试，时间有限，未进行单元测试
- 消费页面 实现多种排序功能，添加了两种地点选择器

|-train
    |-app/
        |-templates/
        |-static/
        |-main/
        |-cus/
        |-auth/
        |-db/
        |-__init__.py
        |-email.py
        |-models.py
    |-tests/
    |-venv/
    |-requirements.txt
    |-config.py
    |-manage.py
    |-database.so
- db是后端数据库代码
- templates文件夹中是网页的html代码
- static文件夹中是js、css代码和icon图标
- main文件夹是管理界面的实现
- cus文件夹是消费界面的实现
- auth文件夹是管理界面用户的实现
- venv文件夹是虚拟环境
- tests文件夹是单元测试(未添加)
- config.py是配置文件
- manage.py构造了启动脚本
- database.so为后端
- pip install -r requirments.txt 安装所有库


## After End
### Outline

1. B+ Tree : 文件储存数据。 插入删除， 访问，迭代器。
2. 用户相关 ：注册，登录，查询，修改，访问权限，email登录
3. 火车相关 ：增加，公开，查询，修改，删除。
4. 票务相关 ：查询，中转查询，订购，退订。


### DataBase with B+ Tree 

```C++
//接口函数及原型
template<class Key, class V, class Compare = std::less<Key>, int32_t _K = 1>class database;
database<Key, V, cmp, _k>::class iterator;
database(const char *idxfilename, const char *datafilename);
void clear();
bool empty();
int32_t size();
iterator find(const Key &k);
iterator begin();
iterator end();
iterator insert(const Key &k, const V &val);
iterator insert(const std::pair<Key, V> &value);
iterator erase(const Key &k);
iterator erase(const Key &k, const V &val);
iterator erase(const std::pair<Key, V> &value);
iterator erase(const iterator &iter);
iterator modify(const Key &k, const V &val);
iterator modify(const std::pair<Key, V> &value);
iterator modify(iterator &iter, const V &val);
```
`具体实现：`
1. 初始化：读取或者新建树。将索引节点和记录节点（叶子）分开存储。初始化建立叶子节点（保证节点数量>0）
2. 查找函数：从根节点开始遍历，按照cmp规则找到最后一层叶子节点的位置，读取后，再找出具体位置。（不存在则throw）
3. 插入函数：
    - root 未存满一个节点 特判
    - root 儿子超过一个节点,进入pinsert（私有成员函数）
    - 如果root分裂，新建newroot
    - pinsert 函数：
```sequence
pinsert--> pinsert: type == 0
pinsert-> type: type == 1
type --> pinsert: type == 0
type -> addData: type == 1
addData-->end: no split
adddata->addidx: split
addidx-->end: nosplit
addidx->pinsert: split
```

    - adddata
    - addidx
4. 删除函数：
    - 根节点只有一个儿子，特判
    - perase 函数：
``` sequence
perase--> perase: type == 0
perase -> type: type == 1
type --> perase: type == 0
type -> deldata: type == 1
deldata-->end: no merge, no adopt
deldata-> end: adopt, left/right, which key changed 
deldata--> perase: merge, left/right, which key changed
perase-->delidx: merge
delidx-->perase: like deldata
delidx->end: like deldata
```
    - 参数传入位置，当前函数只读取当前节点。传入兄弟节点位置，备用
5. 修改函数：
    - 只能修改Value
6. 迭代器：
    - 只实现普通的迭代器，不实现const_iterator
    - 重载++, --, !=, ==, *, ->
    - write函数，用于使用迭代器修改数值之后，写入到文件中
    - &getkey() 用于得到key
7. 返回头尾迭代器，判定空函数，返回容量函数，清库函数。

### User Interface with bash
2. Detail class

    - 全局变量：inner_id, 返回最后一个id(可以用user_db库size取代)
    - 暂时变量用全局变量，read函数覆盖
    - class mstring; class cmp;//定长char数组
    - 其他类
    > * user_db : class user_id; class user;
    > * train_db : class train_id; class train; 
    > * train_order_db : class train_order; ..;
    > * left_ticket_db : class date_train; class left_ticket;
    > * ticekt_db : class user_ticekt; class ticket;

3. Detail functions

Tags: 具体内容与说明文档相似，此处不予赘述。

```c++
int regist();
bool login();
bool query_profile();
bool modify_profile();
bool modify_privilege();
bool query_ticket();[^catalog]
bool _query_ticket();
bool query_transfer();
bool buy_ticket();
bool query_order();
bool refund_ticket();
bool clean();
bool add_train();
bool delete_train();
bool modify_train();
bool query_train();
```

## Conclusion/Advanced

1. 可能加强的地方：
    * user 用线性表实现存储信息
    * user email映射
    * 使用系统命令，建立文件夹保存信息
    * b+树优化
        - 多索引目录对应同一个信息文件
        - 删除，插入函数
        - const_iterator实现

2. 反思：
    * 代码能力不足，写循环时，把i --> j 弄反
    * 大纲先打好有利于后面的书写
    * 熬夜不一定效果会更好，关键看什么时候效率更高。

---

Auther [@Xun Gong]( https://github.com/Insightcd )[@Linqi Chen](http://404)[@Fangyuan Zhang](http://404)
Time 2018.06.03


[^title]: 2018 Data Structure Big Work 2 for [ACM]2017 SJTU

[^catalog]: For each train has only one catalog, but when query, may have many

[1]: https://github.com/Insightcd <gongxun@sjtu.edu.cn>

[acm]: http://www.acm.sjtu.edu.cn "ACM"

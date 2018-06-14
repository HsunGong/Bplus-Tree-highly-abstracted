# **TicketSystem[^title]**--imitate 12306

[TOC]

## Catalog
0. Outline
1. Front End
2. After End
3. Conclusion
4. CopyRight

## Outline
1. 工作分配
| mokuai | renyuan |
|        | Linqi Chen |
|        | Fangyuan Zhang |
|        | Xun Gong |

## Front End

Tags: 

~~ wrong code ~~
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
    * pinsert 函数：
### User Interface with bash
2. Detail class

3. Detail functions


- [x]  
- [ ] 
> * dd
* 
+ 

```c++
@Auther


```


## Conclusion



---

Auther [@Xun Gong @Linqi Chen @Fangyuan Zhang][1]
Time 2018.06.03

[^title]: 2018 Data Structure Big Work 2 for ACM2017 SJTU

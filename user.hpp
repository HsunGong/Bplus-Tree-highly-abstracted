#pragma once
#include "database.hpp"
#include "main1.hpp"

class user {
public:
	//int id;
	char name[lsize];// 1 chinese word with 2 char
	char password[msize];
	char email[msize];//255+64+1
	char phone[msize];
	int privilege = 0;// 0--no, 1--re, 2--man

	user() {};
	user(const char *_name, const char *_password, const char *_email, const char *_phone, const int p = 0) : privilege(p) {
		//id = id;
		strcpy(name, _name);
		strcpy(password, _password);
		strcpy(email, _email);
		strcpy(phone, _phone);
	}
	void read(const char *_name, const char *_password, const char *_email, const char *_phone, const int p = 0) {
		//id = id;
		privilege = p;
		strcpy(name, _name);
		strcpy(password, _password);
		strcpy(email, _email);
		strcpy(phone, _phone);
	}
}_user;


class list{
public:
    fstream io;
    int inner_id;
    int size;
    list():size(sizeof(user)){
        ifstream in("user");
        if(!in){
            ofstream out("user");
            if(!out) throw file_error();
            out.close();

            io.open("user", ios::in | ios::out | ios::binary);
            if(!io) throw file_error();
            inner_id = 2017;
        }
        else{
            in.close();

            io.open("user", ios::in | ios::out | ios::binary);
            if(!io) throw file_error();
            io.seekg(0);
            io.read(reinterpret_cast<char*>(&inner_id), sizeof(int));
        }
    }
    ~list(){
        io.seekp(0);
        io.write(reinterpret_cast<char*>(&inner_id), sizeof(int));
    }
    void clear(){
        io.close();
        ofstream out("user");
        if(!out) throw file_error();
        io.close();
        io.open("user", ios::in | ios::out | ios::binary);
        if(!io) throw file_error();
        inner_id = 2017;
    }

    void read(const int &userid, user &x){
        io.seekg((userid - 2017)*size);
        io.read(reinterpret_cast<char*>(&x), size);
    }
    void write(const int &userid, user &x){
        io.seekp((userid - 2017)*size);
        io.write(reinterpret_cast<char*>(&x), size);
    }

    int add(user &x){
        if (inner_id == 2017) x.privilege = 2;
	    else x.privilege = 1;

	    ++inner_id;
	    write(inner_id, x);
       // cout << "add  " <<inner_id << endl;
	    return inner_id;
    }
    void get(int &userid, user &x){
       // cout << userid << "  is id\n";
        if(userid > inner_id) throw not_exist();
        read(userid, x);
    }
    bool modify(int &userid, user &x){       
       //user tmp;
       if(userid > inner_id) throw not_exist();
        write(userid, x);
    }
    bool modify_privilege(int &_admin, int &_other, const int &privilege){
        user admin, other;
        if(_admin > inner_id || _other > inner_id) throw not_exist();
        read(_admin, admin);
        read(_other, other);
        if(admin.privilege == 2){
            if(other.privilege != 2){
                other.privilege = privilege;
                write(_other, other);
                return 1;
            }
        }
        return 0;
    }
};
list user_db;

int regist() {
    user tmp(_name, _password, _email, _phone, _privilege);
	return user_db.add(tmp);
}

bool login() { 
    try{
        user_db.get(_id1, _user);
        //cout << "get sus\n";
    }catch(not_exist x){
        return 0;
    }
	if (strcoll(_user.password, _password) == 0)   return 1;
	return 0;
}

bool query_profile() {
    try{
        user_db.get(_id1, _user);
    }catch(not_exist x){
        //cout << "cant get!!!!\n";
        cout << "0\n";
        return 0;
    }
	cout << fixed << setprecision(6) << _user.name << " " << _user.email << " " << _user.phone << " " << _user.privilege << "\n";
	return 1;
}

bool modify_profile() {
    try{
        user_db.get(_id1, _user);
    }catch(not_exist x){
        //cout << "0\n";
        return 0;
    }
	user tmp(_name, _password, _email, _phone, _user.privilege);//id bucun
	user_db.modify(_id1, tmp);
	return 1;
}

bool modify_privilege() {
    //cout << "modify: " ;
	try{
        return user_db.modify_privilege(_id1, _id2, _privilege);
    }catch(...){
        return 0;
    }
}
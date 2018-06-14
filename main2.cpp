#include "main2.hpp"

int get_privilege(int &check_id) {
	iter_user it = user_db.find(check_id);
	if (it.getkey() == check_id)  return it->privilege;
	return 0;
}

int regist() {
	if (inner_id == 2017) _privilege = 2;
	else _privilege = 1;

	++inner_id;
	user tmp(_name, _password, _email, _phone, _privilege);//id bucun
	user_db.insert(inner_id, tmp);
	email_db.insert(mstring(_email), inner_id);
	return inner_id;
}

bool login() {
	iter_user it = user_db.find(_id1);
	if (it.getkey() == _id1 && cmp(it->password, _password))   return 1;
	return 0;
}
bool query_email() {
	cin >> _email;
	iter_email it = email_db.find(mstring(_email));
	if (cmp(it.getkey().a, _email))   return 1;
	return 0;
}

bool query_profile() {
	iter_user it = user_db.find(_id1);
	if (it.getkey() == _id1) {
		cout << fixed<< setprecision(6) <<it->name<<" "<<it->email<<" "<<it->phone<<" "<<it->privilege<<"\n";
		// printf("%s %s %s %d\n", it->name, it->email, it->phone, it->privilege);
		return 1;
	}
	cout << fixed<< setprecision(6)  << "0\n";
	return 0;
}

bool modify_profile() {
	iter_user it = user_db.find(_id1);
	// cout << fixed<< setprecision(6) <<it->name<<" "<<it->password<<" "<<it->email<<" "<<it->phone<<" "<<it->privilege<<"\n";
	if (it.getkey() == _id1) {
		user tmp(_name, _password, _email, _phone, it->privilege);//id bucun
		user_db.modify(it, tmp);
		return 1;
	}
	return 0;
}

bool modify_privilege() {
	if (get_privilege(_id1) == 2) {
		iter_user it = user_db.find(_id2);
		if (it.getkey() == _id2) {
			if(it->privilege == 1){
				it->privilege = _privilege;
				it.write();
			}
			else if(it->privilege == 2 && _privilege == 1)
				return 0;
			return 1;
		}
	}
	return 0;
}


bool add_train() {
	
	//try{}
	train_db.insert(_train.train_id, _train);
	return 1;
}
bool sale_train() {
	iter_train it = train_db.find(_train_id);
	if (it->sale != -1) return 0;

	// _train_order.read(it->catalog, it->train_id);
	// iter_train_order it2 = train_order_db.find(_train_order);
	// if (cmp(it2.getkey().train_id.a, _train_id.a)) return 0;

	for (int i = 0; i < it->num_station; ++i) {
		_train_order.read(it->catalog, it->train_id, it->station_name[i]);
		// strcpy(_train_order.station_name, it->station_name[i]);
		train_order_db.insert(_train_order, _catalog);
	}
	it->sale = 0;
	it.write();
	return 1;
}
bool query_train() {
	
	iter_train it = train_db.find(_train_id);
	if (cmp(_train_id.a, it.getkey().a) && it->sale != -1) {
		it->print();
		return 1;
	}

	cout << fixed<< setprecision(6)  << "0\n";
	return 0;
}

bool delete_train() {

	iter_train it3 = train_db.find(_train_id);
	if (it3->sale >= 0) return 0;
	// cout << fixed<< setprecision(6) <<"erase"<<_train_id.a<<endl;
	train_db.erase(_train_id);
	// cout << fixed<< setprecision(6) <<"erase"<<it4.getkey().a<<endl;

	return 1;
}

bool modify_train() {
	// _train.read();
	_train_id = _train.train_id;

	iter_train it3 = train_db.find(_train_id);
	if (it3->sale >= 0) return 0;
	// cout << fixed<< setprecision(6) <<_train_id.a<<" "<<it3.getkey().a<<endl;
	if (!cmp(it3.getkey().a, _train_id.a)) return 0;
	// if(it3->sale != -1)
	// 	for(int i = 0 ;i < it3->num_station; i ++){
	// 		_train_order.read(_catalog, _train_id, it3->start_time[i]);
	// 		iter_train_order it2 = train_order_db.find(_train_order);

	// 		train_order_db.erase(_train_order);
	// 	}
	
	train_db.modify(_train_id, _train);
	return 1;
}


struct prin{
	char train_id[msize];
	char loc1[msize];
	char loc2[msize];
	char time1[xssize], time2[xssize];
	char date1[msize];
	char date2[msize];
	char ticket_name[xlsize][msize];
	int left[xssize];
	double pri[xssize];
	int l, r, num_price;

	void print(){
		cout << fixed<< setprecision(6)  << train_id << " " << loc1 << " " << date1 << " " << time1  << " " << loc2 << " " << date2 << " " << time2;
		for(int p = 0; p < num_price; ++p){
			cout << fixed<< setprecision(6)  <<" "<< ticket_name[p] << " " << left[p] << " " << pri[p];
		}
		cout << fixed<< setprecision(6)  << '\n';
	}
};

bool query_ticket(mstring x = mstring()) {
	int i = 0;
	prin tt[xxxsize];
	for(int jp = 0; jp < strlen(_tmpcatalog); ++jp){
		_catalog = _tmpcatalog[jp];
		_train_order.read(_catalog,x, _loc1);
		iter_train_order it1 = train_order_db.find(_train_order);
	//	cout << fixed<< setprecision(6)  << "233:" << it1.getkey().catalog << ' ' << it1.getkey().train_id.a << endl;
		train_order _train_order2;
		_train_order2.read(_catalog, x, _loc2);
		iter_train_order it2 = train_order_db.find(_train_order2);
	//	cout << fixed<< setprecision(6)  << "233:" << it2.getkey().catalog << ' ' << it2.getkey().train_id.a << endl;
		
		while (1) {
	//		cout << fixed<< setprecision(6)  << 1 << endl;
			if (it1.getkey().catalog != it2.getkey().catalog || it1.getkey().catalog != _catalog) break;

	//		cout << fixed<< setprecision(6)  << 2 << endl;
			if (strcmp(it1.getkey().station_name, _loc1) != 0) break;
	//		cout << fixed<< setprecision(6)  << 3 << endl;
			if (strcmp(it2.getkey().station_name, _loc2) != 0) break;
	//		cout << fixed<< setprecision(6)  << 4 << endl;
			if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) < 0) {
				++it1;
			}
			else if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) > 0) {
				++it2;
			}
			else {
				iter_train it3 = train_db.find(it1.getkey().train_id);
				//cout << fixed<< setprecision(6)  << "kkk:" << it3 -> ticket_name << endl;
				_date_train.read(_date, it1.getkey().train_id);

				iter_left_ticket it4 = left_ticket_db.find(_date_train);
				bool flag;
				if (_c3(it4.getkey(), _date_train) || _c3(_date_train, it4.getkey())) flag = 0;
				else flag = 1;//has date in lef_ticket

				char date1[ssize], date2[ssize];
				strcpy(date1, _date);
				strcpy(date2, _date);
				int l, r;
				for (l = 0; l < it3->num_station; ++l) {
					if (cmp(_loc1, it3->station_name[l])) break;
				}
				check_date(date1, it3->start_time[0], it3->start_time[l]);

				for (r = 0; r < it3->num_station; ++r) {
					if (cmp(_loc2, it3->station_name[r])) break;
				}
				check_date(date2, it3->start_time[0], it3->arriv_time[r]);
				
				
				if(l < r){
					// cout << fixed<< setprecision(6)  << it3->train_id.a << ' ' << l << ' ' << r << ' ' << _loc1 << ' ' << _loc2 << endl;
					++i;
					// printf("%s %s %s %s %s ", it1.getkey().train_id.a, _loc1, date1, _loc2, date2);
					strcpy(tt[i].train_id, it3->train_id.a);
					strcpy(tt[i].loc1, _loc1);
					strcpy(tt[i].loc2, _loc2);
					strcpy(tt[i].date1, date1);
					strcpy(tt[i].date2, date2);
					strcpy(tt[i].time1, it3->start_time[l]);
					strcpy(tt[i].time2, it3->arriv_time[r]);
					tt[i].num_price = it3->num_price;
					tt[i].l = l;
					tt[i].r = r;

					for (int p = 0; p < it3->num_price; ++p) {
						// printf("%s %d %.2f ", it3->ticket_name[p], it4->check(l, r, p), it3->price[p]);
						strcpy(tt[i].ticket_name[p], it3->ticket_name[p]);
						if(flag) tt[i].left[p] = it4->check(l, r, p);
						else tt[i].left[p] = 2000;

						tt[i].pri[p] = 0;
						for(int se = l + 1; se <= r; ++se)
						tt[i].pri[p] += it3->price[se][p];
					}
				}
				++it1;
				++it2;
			}

		}
	}
	if(i == 0) cout << fixed<< setprecision(6)  << "0\n";
	else {
		cout << fixed<< setprecision(6) << i << '\n';
		for(int j = 1; j <= i; ++j) tt[j].print();
	}
	return 0;
}

int minutes(char *t0, char*t1) {
	int min = 0;
	int hour = 0;
	if (strcmp(t0, t1) >= 0) {
		hour += 24;
	}
	hour += (t0[0] - t1[0]) * 10 + (t0[1] - t1[1]);
	min += (t0[3] - t1[3]) * 10 + (t0[3] - t1[3]);
	min += hour * 60;
	return min;
}

bool _query_ticket(mstring x = mstring()) {
	int i = 0;
	prin tt[xxxsize];
		_catalog = _tmpcatalog[0];
		_train_order.read(_catalog,x, _loc1);
		iter_train_order it1 = train_order_db.find(_train_order);
	//	cout << fixed<< setprecision(6)  << "233:" << it1.getkey().catalog << ' ' << it1.getkey().train_id.a << endl;
		train_order _train_order2;
		_train_order2.read(_catalog, x, _loc2);
		iter_train_order it2 = train_order_db.find(_train_order2);
	//	cout << fixed<< setprecision(6)  << "233:" << it2.getkey().catalog << ' ' << it2.getkey().train_id.a << endl;
		
		while (1) {
	//		cout << fixed<< setprecision(6)  << 1 << endl;
			if (it1.getkey().catalog != it2.getkey().catalog || it1.getkey().catalog != _catalog) break;

	//		cout << fixed<< setprecision(6)  << 2 << endl;
			if (strcmp(it1.getkey().station_name, _loc1) != 0) break;
	//		cout << fixed<< setprecision(6)  << 3 << endl;
			if (strcmp(it2.getkey().station_name, _loc2) != 0) break;
	//		cout << fixed<< setprecision(6)  << 4 << endl;
			if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) < 0) {
				++it1;
			}
			else if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) > 0) {
				++it2;
			}
			else {
				iter_train it3 = train_db.find(it1.getkey().train_id);
				//cout << fixed<< setprecision(6)  << "kkk:" << it3 -> ticket_name << endl;
				_date_train.read(_date, it1.getkey().train_id);

				iter_left_ticket it4 = left_ticket_db.find(_date_train);
				bool flag;
				if (_c3(it4.getkey(), _date_train) || _c3(_date_train, it4.getkey())) flag = 0;
				else flag = 1;//has date in lef_ticket

				char date1[ssize], date2[ssize];
				strcpy(date1, _date);
				strcpy(date2, _date);
				int l, r;
				for (l = 0; l < it3->num_station; ++l) {
					if (cmp(_loc1, it3->station_name[l])) break;
				}
				check_date(date1, it3->start_time[0], it3->start_time[l]);

				for (r = 0; r < it3->num_station; ++r) {
					if (cmp(_loc2, it3->station_name[r])) break;
				}
				check_date(date2, it3->start_time[0], it3->arriv_time[r]);
				
				
				if(l < r){
					// cout << fixed<< setprecision(6)  << it3->train_id.a << ' ' << l << ' ' << r << ' ' << _loc1 << ' ' << _loc2 << endl;
					++i;
					// printf("%s %s %s %s %s ", it1.getkey().train_id.a, _loc1, date1, _loc2, date2);
					strcpy(tt[i].train_id, it3->train_id.a);
					strcpy(tt[i].loc1, _loc1);
					strcpy(tt[i].loc2, _loc2);
					strcpy(tt[i].date1, date1);
					strcpy(tt[i].date2, date2);
					strcpy(tt[i].time1, it3->start_time[l]);
					strcpy(tt[i].time2, it3->arriv_time[r]);
					tt[i].num_price = it3->num_price;
					tt[i].l = l;
					tt[i].r = r;

					for (int p = 0; p < it3->num_price; ++p) {
						// printf("%s %d %.2f ", it3->ticket_name[p], it4->check(l, r, p), it3->price[p]);
						strcpy(tt[i].ticket_name[p], it3->ticket_name[p]);
						if(flag) tt[i].left[p] = it4->check(l, r, p);
						else tt[i].left[p] = 2000;

						tt[i].pri[p] = 0;
						for(int se = l + 1; se <= r; ++se)
						tt[i].pri[p] += it3->price[se][p];
					}
				}
				++it1;
				++it2;
			}

		}
	

		//cout << fixed<< setprecision(6) << i << '\n';
		for(int j = 1; j <= i; ++j) tt[j].print();
	
	return 0;
}


bool _query_transfer(const mstring &first, const mstring &second, int &min, const char *begin, const char *end, char *loc_mid) {
	int tmp = min;
	iter_train it1, it2;
	it1 = train_db.find(first);
	it2 = train_db.find(second);
	if (it1->sale == -1 || it2->sale == -1) return 0;
	int cnt = 0;
	int l, r;//l --- i, j --- r
	for (l = 0; l < it1->num_station; ++l) 
		if (strcmp(it1->station_name[l], begin) == 0) break;
	for (r = 0; r < it2->num_station; ++r)
		if (strcmp(it2->station_name[r], end) == 0) break;
	for (int i = l; i < it1->num_station; ++i) {
		for (int j = 0; j <= r; ++j) {
			if (strcmp(it1->station_name[i], it2->station_name[j]) == 0) {
				//some rules
				int time = 0;
				time += minutes(it1->start_time[l], it1->arriv_time[i]);
				time += minutes(it1->start_time[i], it2->start_time[j]);
				time += minutes(it1->start_time[j], it2->arriv_time[l]);
				if (time < min) {
					min = time;
					strcpy(loc_mid, it1->station_name[i]);
				}
			}
		}
	}
	if (min < tmp) return 1;
	else return 0;
}

bool query_transfer() {
	mstring tt[xxxsize];
	char c1[xxxsize];
	int size = 0;
	iter_train_order it1;

	int min = 0x7ffffff;
	char loc_head[msize];
	char loc_mid[msize];
	char loc_tail[msize];
	strcpy(loc_head, _loc1);
	strcpy(loc_tail, _loc2);
	mstring first, second;
	char _c2;
	char _c1;

	for (int pp = 0; pp < strlen(_tmpcatalog); ++pp) {
		_catalog = _tmpcatalog[pp];
		_train_order.read(_catalog, mstring(), _loc1);
		it1 = train_order_db.find(_train_order);
		while (1) {
			if (_catalog != it1.getkey().catalog || strcmp(_loc1, it1.getkey().station_name) != 0)
				break;
			tt[++size] = it1.getkey().train_id;
			c1[size] = _catalog;
			++it1;
		}
	}
	//cout << size << endl;
	for (int pp = 0; pp < strlen(_tmpcatalog); ++pp) {
		_catalog = _tmpcatalog[pp];
		_train_order.read(_catalog, mstring(), _loc2);

		it1 = train_order_db.find(_train_order);
		int i = size;
		while (i) {
			if (_catalog != it1.getkey().catalog || strcmp(_loc2, it1.getkey().station_name) != 0) break;
			if (strcmp(tt[i].a, it1.getkey().train_id.a) == 0) {
				--i;
				continue;
			}
			if (_query_transfer(tt[i], it1.getkey().train_id, min, _loc1, _loc2, loc_mid)) {
				_c2 = _catalog;
				_c1 = c1[i];
				first = tt[i];
				second = it1.getkey().train_id;
				//cout << "get  "<< i << endl;
			}
			i--;
		}

	}
	if (strlen(first.a) == 0) {
		cout << -1 << '\n';
		return 0;
	}

	strcpy(_loc1, loc_head);
	strcpy(_loc2, loc_mid);
	_train_id = first;
	memset(_tmpcatalog, '\0', msize);
	_tmpcatalog[0] = _c1;
	_query_ticket(_train_id);

	strcpy(_loc1, loc_mid);
	strcpy(_loc2, loc_tail);
	_train_id = second;
	memset(_tmpcatalog, '\0', msize);
	_tmpcatalog[0] = _c2;
	_query_ticket(_train_id);
	return 0;
}



bool buy_ticket() {
	iter_train it = train_db.find(_train_id);
	if (!cmp(it.getkey().a, _train_id.a)) return 0;
	if (it->sale == -1) return 0;
	int i, j, p;
	for (i = 0; i < it->num_station; ++i) {
		if (strcmp(_loc1, it->station_name[i]) == 0) break;
	}
	for (j = 0; j < it->num_station; ++j) {
		if (strcmp(_loc2, it->station_name[j]) == 0) break;
	}
	for (p = 0; p < it->num_price; ++p) {
		if (strcmp(_ticket_name, it->ticket_name[p]) == 0) break;
	}
	if(i == it->num_station || j == it->num_station || p == it->num_price) return 0;
	if (i >= j) return 0;
	_date_train.read(_date, _train_id);
	iter_left_ticket it2 = left_ticket_db.find(_date_train);
	// cout<<":"<<_date<<" "<<_date_train.train_id.a<<" "<<_date_train.date<<endl;
	if (_date_train == it2.getkey()) {
		if (it2->check(i, j, p) < _num1) return 0;
		it2->buy(i, j, p, _num1);
		it2.write();
	}
	else {
		// if (it2->check(i, j, p) < _num1) return 0;
		it2 = left_ticket_db.insert(_date_train, left_ticket());
		it2 = left_ticket_db.find(_date_train);
		// cout<<":"<<_date<<endl;
		it2->buy(i, j, p, _num1);
		// cout<<(*it2)
		it2.write();
		//it->sale++;
		it.write();
	}

	// cout << fixed<< setprecision(6) <<"!!"<<endl;
	_user_ticket.read(it->catalog, _id1, _date, _train_id, _loc1, _loc2);
	iter_ticket it3 = ticket_db.find(_user_ticket);
	if (!_c4(_user_ticket, it3.getkey()) && !_c4(it3.getkey(), _user_ticket)) {
		it3->num_ticket[p] += _num1;
		it3.write();
	}
	else {
		int tmp[ssize];
		tmp[p] = _num1;
		double allprice[xssize] = {0};
		for(int m = 0; m < it->num_price; ++m){
			for(int n = i + 1; n <= j; ++n )
				allprice[m] += it->price[n][m];
		}

		_ticket.read(_train_id, it->catalog, _loc1, _loc2, _date, it->start_time[0],
			it->start_time[i], it->arriv_time[j],
			it->num_price, it->ticket_name, allprice, tmp);
		ticket_db.insert(_user_ticket, _ticket);
	}
	return 1;
}

bool refund_ticket() {
	// cout << fixed<< setprecision(6) <<":"<<endl;
	iter_train it = train_db.find(_train_id);
	// cout << fixed<< setprecision(6) <<it.getkey().a<<" "<<_train_id.a<<endl;
	if (!cmp(it.getkey().a, _train_id.a)) return 0;
	if (it->sale == -1) return 0;

	int i, j, p;
	for (i = 0; i < it->num_station; ++i) {
		if (strcmp(_loc1, it->station_name[i]) == 0) break;
	}
	for (j = 0; j < it->num_station; ++j) {
		if (strcmp(_loc2, it->station_name[j]) == 0) break;
	}
	for (p = 0; p < it->num_price; ++p) {
		if (strcmp(_ticket_name, it->ticket_name[p]) == 0) break;
	}


	_date_train.read(_date, _train_id);
	iter_left_ticket it2 = left_ticket_db.find(_date_train);
	// cout << fixed<< setprecision(6) <<"````"<<endl;
	if(!_c3(it2.getkey(),_date_train) && !_c3(_date_train, it2.getkey())) ;
	else return 0;
	it2->refund(i, j, p, _num1);
	// it2.write();
	// cout << fixed<< setprecision(6) <<"````"<<endl;
	// cout << fixed<< setprecision(6) <<_id1<<endl;
	_user_ticket.read(it->catalog, _id1, _date, _train_id, _loc1, _loc2);
	iter_ticket it3 = ticket_db.find(_user_ticket);
	// (*it3).print();
	if(!_c4(_user_ticket, it3.getkey()) && !_c4(it3.getkey(), _user_ticket) );
	else return 0;
	if(it3->num_ticket[p] < _num1) return 0;
	it3->num_ticket[p] -= _num1;
	// if(it3->num_ticket[p] == 0){
	//     for(int i = 0; i < it3->num_price; ++i)
	//         if(it3->num_ticket[p] > 0) break;

	//     // if(it3->num_price == i) ticket_db.erase();
	// }
	it3.write();
	return 1;
}

bool query_order() {
	int sum = 0;
	ticket tt[xxxsize];
	for(int i  = 0; i < strlen(_tmpcatalog) ;++i){
		_catalog = _tmpcatalog[i];
		// cout << fixed<< setprecision(6) <<_catalog<<endl;
		_user_ticket.read(_catalog, _id1, _date, _train_id, "\0", "\0");
		iter_ticket it = ticket_db.find(_user_ticket);
		while (1) {
			if(it == ticket_db.end()) break;
			// cout << fixed<< setprecision(6) <<"!!!"<<" "<<_user_ticket.train_id<<endl;
			if (!_c4(_user_ticket, it.getkey()) && !_c4(it.getkey(), _user_ticket)) break;
			//it->print();
			++sum;
			// cout << fixed<< setprecision(6) <<"~~~"<<endl;
			// cout << fixed<< setprecision(6) <<"!!!"<<endl;
			tt[sum].read(*it);
			// cout << fixed<< setprecision(6) <<"=.="<<endl;
			++it;
			// cout << fixed<< setprecision(6) <<"===="<<endl;
		}
	}
	// int i = size;
	cout << fixed<< setprecision(6)  << sum << '\n';
	while (sum) {
		tt[sum].print();
		sum--;
	}
	// cout << fixed<< setprecision(6) <<_catalog<<endl;
	return 1;
}

bool clean() {
	try {
		user_db.clear();
		train_db.clear();
		train_order_db.clear();
		left_ticket_db.clear();
		ticket_db.clear();
		//sss.clear();
		return 1;
	}
	catch (...) {
		return 0;
	}
}

int main() {
	ios::sync_with_stdio(0);

	fstream io("user");
	if (!io) {
		ofstream out("user");
		out << inner_id;
		out.close();
		io.open("user");
	}
	io >> inner_id;

	char cmd[msize];
	while (cin >> cmd) {
		//cerr<<cmd<< '\n';
		if (cmp(cmd, "register")) {
			cin >> _name >> _password >> _email >> _phone;
			cout << fixed<< setprecision(6)  << regist() << '\n';
		}
		else if (cmp(cmd, "login")) {
			cin >> _id1 >> _password;
			cout << fixed<< setprecision(6)  << login() << '\n';
		}
		else if (cmp(cmd, "query_profile")) {
			cin >> _id1;
			query_profile();
		}
		else if (cmp(cmd, "modify_profile")) {
			cin >> _id1 >> _name >> _password >> _email >> _phone;
			cout << fixed<< setprecision(6)  << modify_profile() << '\n';
		}
		else if (cmp(cmd, "modify_privilege")) {
			cin >> _id1 >> _id2 >> _privilege;
			cout << fixed<< setprecision(6)  << modify_privilege() << '\n';
		}
		else if (cmp(cmd, "query_ticket")) {

			cin >> _loc1 >> _loc2 >> _date >> _tmpcatalog;
			query_ticket();
		}
		else if (cmp(cmd, "query_transfer")) {
			cin >> _loc1 >> _loc2 >> _date >> _tmpcatalog;
				query_transfer();
			
		}
		else if (cmp(cmd, "buy_ticket")) {
			cin >> _id1 >> _num1 >> _train_id >> _loc1 >> _loc2 >> _date >> _ticket_name;
			cout << fixed<< setprecision(6)  << buy_ticket() << '\n';
		}
		else if (cmp(cmd, "query_order")) {
			cin >> _id1 >> _date >> _tmpcatalog;
			query_order();
		}
		else if (cmp(cmd, "refund_ticket")) {
			cin >> _id1 >> _num1 >> _train_id >> _loc1 >> _loc2 >> _date >> _ticket_name;
			cout << fixed<< setprecision(6)  << refund_ticket() << '\n';
		}
		else
			if (cmp(cmd, "add_train")) {
				_train.read();
				cout << fixed<< setprecision(6)  << add_train() << '\n';
			}
			else if (cmp(cmd, "sale_train")) {
				cin >> _train_id;
				cout << fixed<< setprecision(6)  << sale_train() << '\n';
			}
			else if (cmp(cmd, "query_train")) {
				cin >> _train_id;

				query_train();
			}
			else if (cmp(cmd, "delete_train")) {
				cin >> _train_id;
				cout << fixed<< setprecision(6)  << delete_train() << '\n';
			}
			else if (cmp(cmd, "modify_train")) {
				_train.read();
				cout << fixed<< setprecision(6)  << modify_train() << '\n';
			}
			else if (cmp(cmd, "clean")) {
				clean();
				cout << fixed<< setprecision(6)  << 1 << '\n';
			}
			else if (cmp(cmd, "exit")) {
				cout << fixed<< setprecision(6)  << "BYE" << '\n';
				break;
			}
			else {
				puts("Wrong Command");
			}
	}
	ofstream ou("user");
	ou << inner_id;
	return 0;
}
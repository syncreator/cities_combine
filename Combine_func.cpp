#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

struct Map
{
	int _in;
	int _num;
	char _lit;
};

bool comp_hipe(Map a, Map b) {

	return (a._num>b._num);
};


vector<string> combine_cities(vector<string> available_cities)
{
	struct Prog
	{
		string _city; //собственно слово
		int _n; //номер слова из основного списка
		int _m; //номер перебора по текущей первой букве
		int _sum; //результат по цепи включая текущее слово
	};
	
	vector<Prog> prog;
	vector<Prog> best_res;
	vector<Map> map, hipe;
	vector<string> temp;
	vector<string> memp;
	temp = available_cities;
	temp.push_back("[");
	//vector<string> smart;

	vector<string>::iterator it;
	vector<string>::iterator pt;
	vector<Map>::iterator st;
	vector<Prog>::iterator su;
	//Prog *tr;
	volatile char i, j, y(0), z(0);
	string str, dtr[4], mt;
	int n(0), m(0), t(0), sum(0), rate, s(0), q(0), max_sum;
	Map tp;
	Prog pr;
	Prog *tr;

	//сборка map (карта номеров контейнера по вектору на начало каждой буквы)
	for (it = available_cities.begin(), j = 'A', i = 0, n = 0; it != available_cities.end(); ++it, ++n)
	{
		if (i != (*it)[0] || it == available_cities.end() - 1)
		{
			if (s>1)
				while (j <= i)
				{
					if (j == i) {
						tp._in = n - s;
						tp._num = s;
					}
					else tp._in = -1;
					tp._lit = i;
					map.push_back(tp);
					++j;
				};
			s = 1;
			i = (*it)[0];
		}
		else ++s;
	}
	hipe = map;
	sort(hipe.begin(), hipe.end(), comp_hipe);
	//Вывод карты:
	for (st = map.begin(), n = 1; st != map.end(); ++st, ++n)
	{
		cout << "	" << n << "  " << st->_lit << "  _in=" << st->_in << "  _num=" << st->_num << endl;

	}
	cout << "------------------------------------------------------------------------" << endl;
	//Вывод отсортированного hipe
	for (st = hipe.begin(), n = 1; st != hipe.end(); ++st, ++n)
	{
		cout << "	" << n << "  " << st->_lit << "  _in=" << st->_in << "  _num=" << st->_num << endl;

	}
	cin.get();


	//основной прогон
	for (j = 'A', rate = 0; j <= 'Z'; ++j)//перебор 26 основных сборок!(сборка начинается со слова на одну из букв алфавита) 
	{
		i = j;
		t = 0;
		s = 0;
		sum = 0;
		max_sum = 0;
		it = temp.begin();
		z = hipe[0]._lit;//установим критерий выбора по последней букве
		while (!t)
		{
			for (/*it = temp.begin(),*/ m = 1, n = 0; it != temp.end(); /*++it,*/ ++n)
			{
				if (i == (*it)[0] && z == (*it)[it->size() - 1] - 32 && y != (*it)[it->size() - 1] - 32 /*&& sn[0]!= (*it)[it->size() - 1] - 32 && sn[1] != (*it)[it->size() - 1] - 32 && sn[2] != (*it)[it->size() - 1] - 32*/)
				{
					i = (*it)[it->size() - 1] - 32;//последняя буква уже в нижнем регистре, поэтому -32(переводим в верхний)!!!tolower();
												   //заполняем структуру прогона
					pr._city = *it;
					pr._n = it - temp.begin();
					pr._m = m;//?
					sum += it->size();
					pr._sum = sum;
					prog.push_back(pr);
					for (st = hipe.begin(); st != hipe.end(); ++st)if (((*it)[0]) == st->_lit) {/* cout << "    for st->_lit	" << st->_lit << ((*it)[0]) << endl; cin.get();*/ st->_num = (st->_num) - 1; }//корректируем hipe по факту выбора слова
					sort(hipe.begin(), hipe.end(), comp_hipe);//текущая сортировка hipe
					*it = "&none";//убираем использованное слово из исходного вектора
					q = 0;
					z = hipe[q]._lit;//если прогон идет норм, проверку последней буквы убираем
					it = temp.begin() + map[i - 65]._in; //определим итератор с которого начнется следующий поиск согласно карте и последней букве текущего слова
					//if (sum > 15100) {
						//cout << "	if find" << pr._n << "  " << pr._city << "  i=" << i << "  z=" << z << "  sum=" << sum << "  hipe= " << hipe[0]._num << " hipe_lit " << hipe[0]._lit << endl;
						//for (st = hipe.begin(); st != hipe.end(); ++st)cout << "	" << st->_lit << "  num=" << st->_num << endl;
						//cin.get();
					//}
					//}
				}
				else if (i < (*it)[0] && q < hipe.size() - 1) {
					z = hipe[++q]._lit; it = temp.begin() + map[i - 65]._in; /*if (rate > 12100) { cout << "	no_find  z=" << z << "  i=" << i <<"  hipe.size() - 1 = "<< hipe.size() - 1 <<"  hipe= " << hipe[0]._num << " hipe_lit " << hipe[0]._lit << endl; cin.get();}*/
				}//интелектуальный поиск по hipe
				else ++it;

			}if(sum>max_sum)max_sum = sum;
			if (sum > rate) { rate = sum;
			                  best_res.clear();
			                  best_res = prog;
							  cout << "	" << "  i=" << i << "  z=" << z << "  !!!  record sum=" << sum << endl; }
			
			tr = &prog.back();//указатель на последний контейнер прогона
			i = (tr->_city)[0];//первая буква последнего слова в прогоне
			z = (tr->_city)[(tr->_city).size() - 1] - 32 + 1;//последняя буква последнего слова в прогоне в верхнем регистре +1
			y = z - 1;
			q = 0;
			z = hipe[q]._lit;
			
			temp[tr->_n] = tr->_city;//возвращаем последнее слово прогона в темп
			if (dtr[0] == temp[tr->_n] || dtr[1] == temp[tr->_n] || dtr[2] == temp[tr->_n]/* || dtr[3] == temp[tr->_n]*/)t = 1;//Флаг зацикливания сборки
			//else temp[tr->_n] = tr->_city;//возвращаем последнее слово прогона в темп
			if (s < 3)dtr[s++] = temp[tr->_n];//Cлово которое вернулось в темп
			else s=0;
			for (st = hipe.begin(); st != hipe.end(); ++st)if (i == (st->_lit)) { if (st->_num == 0)st->_lit = 0;/* cout << "    for st->_lit	" << st->_lit << ((*it)[0]) << endl; cin.get();*/ st->_num = (st->_num) + 1; }//корректируем hipe по факту возврата слова в темп
			m = tr->_n;//порядковый номер слова в темпе
			sum -= (tr->_city).size();//изменяем значение sum
			it = temp.begin() + map[i - 65]._in;//определим итератор с которого начнется следующий поиск
			prog.pop_back();//удаляем последнее слово из прогона
			//if (rate > 15100) {
				//cout << " del from prog " << m << "  n= " << s << "  no_odd-> " << dtr[0] << "  odd-> " << dtr[1] << "  i=" << i << "  z=" << (int)z << " " << z << "  sum=" << sum << endl;
				/*for (st = hipe.begin(); st != hipe.end(); ++st)cout << "	" << st->_lit << "  num=" << st->_num << endl;
				cin.get();*/
				/*for (it = temp.begin() + map[y+1 - 66]._in,n= map[y+1 - 66]._in; (it < (temp.begin() + map[y+1 - 66]._in +100)) && (it < temp.end()); ++it, ++n)cout << "	" << n << "  " << *it << endl;
				*/
				//cin.get();
			//}
			++s;
		}
		prog.clear();
		temp.clear();
		hipe.clear();
		temp = available_cities;
		temp.push_back("[");
		hipe = map;
		sort(hipe.begin(), hipe.end(), comp_hipe);
		cout << "	" << n << "  " << j << "  " << max_sum << endl;
	}
	cin.get();
	temp.clear();
	//Вывод самой длинной сборки:
	for (su = best_res.begin(), n = 1; su != best_res.end(); ++su, ++n)
	{
		temp.push_back(su->_city);
		cout <<"   "<<n<<"  num="<< su->_n << "  " << su->_city << "  " << su->_sum << endl;

	}
	cin.get();

	return temp;
}

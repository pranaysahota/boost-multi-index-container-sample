//============================================================================
// Name        : boost-multi-index.cpp
// Author      : pranay
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <functional>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

using namespace std;
struct Account{
    int id;
    string account_name;
    bool privileged;
};

struct idxprimary_key{};
struct idxname{};

template <typename tid, typename trecord>
void iteratorFunction(const tid& idx, function<void(const trecord& record)> func){
    auto itr = idx.begin();
    while(itr != idx.end()){
        func(*itr ++);
    }
}

int main() {
    namespace bmi = boost::multi_index;
    bmi::multi_index_container<Account, bmi::indexed_by<
        bmi::ordered_unique<bmi::tag<idxprimary_key>, bmi::member<Account, int, &Account::id>>,
        bmi::ordered_unique<bmi::tag<idxname>, bmi::member<Account, string, &Account::account_name>>
    >> accounts_container;

    accounts_container.insert({1, "d", true});
    accounts_container.insert({2, "e", true});
    accounts_container.insert({3, "a", true});
    accounts_container.insert({4, "z", true});
    accounts_container.insert({5, "f", true});
    accounts_container.insert({6, "g", true});
    accounts_container.insert({7, "q", true});

    auto& itrxId = accounts_container.get<idxprimary_key>();
    auto& itrxName = accounts_container.get<idxname>();

    cout<<"Ordered by id"<<endl;
    iteratorFunction<decltype(itrxId), Account>(itrxId, [](const Account& account){ cout<<account.id <<", "<<account.account_name<<", "<<account.privileged<<endl;});
    cout<<"-----------------"<<endl;
    cout<<"Ordered by name"<<endl;
    iteratorFunction<decltype(itrxName), Account>(itrxName, [](const Account & account)
    {
        cout<<account.id <<", "<<account.account_name<<endl;
    }
    );
    return 0;
}

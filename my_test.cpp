#include <cassert>
#include <iostream>
#include "leveldb/write_batch.h"
#include "leveldb/db.h"

using namespace std;

int main(int argc, char** argv) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.error_if_exists =false;

    leveldb::Status status = leveldb::DB::Open(options,"./testdb",&db);
    if(!status.ok()){
        cerr << "Open Status" << status.ToString() <<endl;
    }else{
        cout <<"Open Status" << status.ToString() <<endl;
    }

    string key1 = "k1",key2 = "k2",value="v";

    //read/write operation
    leveldb::Status s = db->Put(leveldb::WriteOptions(),key1,value);
    if(!s.ok()){
        cerr << s.ToString()<< endl;
    }
    s= db->Get(leveldb::ReadOptions(),key1,&value);
    if(s.ok()){
        cout <<"key1 value: "<<value<<endl;
        s = db->Put(leveldb::WriteOptions(),key2,value);
        s = db->Get(leveldb::ReadOptions(),key2,&value);
        if(s.ok()){
            cout <<"key2 value is "<< value<<endl;
        }
    }else{
        cerr << "Get Status"<< s.ToString()<<endl;
    }

    if (s.ok()) {
        s= db->Delete(leveldb::WriteOptions(),key1);
    }else{
        cerr << "delete key1 status" << s.ToString() <<endl;
    }

    return 0;
}
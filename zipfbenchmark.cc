#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include <iostream>
#include <malloc.h>
#include "sys/time.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
using namespace leveldb;
int p,q;//p+q=100
int tracesize = 10000;
int maxnum = 100;
int minnum = 1;

int main(int argc, char* argv[]){
	srand((unsigned)time(NULL));
	DB* db;
	Options options;
	struct timeval start, end;
	//如果不存在则创建指定名称的leveldb
	options.create_if_missing = true;
	options.error_if_exists = true;
	int *trace = (int *)malloc(tracesize * sizeof(int));
	int i;
	int index = 0;
	p = 80;
	q = 20;
	for(i = 0; i < tracesize * p / 100; i ++){
		trace[index] = random(minnum,maxnum*p/100);
		index++;
		//cout << random(minnum,maxnum*p/100) << endl;
	}
	for(i = 0; i < tracesize * q /100; i++){
		trace[index] = random(maxnum*p/100+1,maxnum);
		index++;
		//cout << random(maxnum * p /100+1, maxnum) << endl; 
	}
        //打开leveldb
	const char* db_path = argv[1];
	Status status = DB::Open(options,db_path,&db);
	//检查是否成功打开文件
	if(!status.ok()){
		cout << "Failed to open leveldb: " <<db_path<<endl;
	}
	else{
		cout << "Open successfully!"<<endl;
	}
	//执行插入数据
	string val = "val";
	gettimeofday(&start, NULL);
	for(i = 0; i < tracesize; i ++){
		if(to_string(trace[i]) != NULL){
			//Status s = db -> Put(WriteOptions(),to_string(trace[i]),val);
			//assert(s.ok());
		}
	}
	gettimeofday(&end, NULL);
	int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("time: %d us\n", timeuse);
	delete trace;
	delete db;
	return 0;
}


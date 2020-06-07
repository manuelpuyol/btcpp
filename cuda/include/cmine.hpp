#ifndef CMINE_H
#define CMINE_H

#include<string>
#include<tuple>
#include<iostream>

using std::string;
using std::tuple;
using std::get;

#define NOT_FOUND -1
#define FOUND 1
#define BLOCKS 512
#define THREADS 512
#define TOTAL BLOCKS * THREADS
#define BUCKET (UINT32_MAX / uint32_t(TOTAL)) + 1

tuple<int, uint32_t> cmine(string str, int difficulty);

#endif
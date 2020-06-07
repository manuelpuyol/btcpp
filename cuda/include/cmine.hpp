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

#ifdef BENCHMARK
#define MAX_NONCE uint32_t(1024 * 1024)
#define BUCKET uint32_t(4)
#else
#define MAX_NONCE UINT32_MAX
#define BUCKET (MAX_NONCE / uint32_t(TOTAL)) + 1
#endif

tuple<int, uint32_t> cmine(string str, int difficulty);

#endif
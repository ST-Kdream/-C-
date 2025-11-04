#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<curl/curl.h>
using namespace std;

#define Local_Version "3.2.5"
#define Remote_Version_URL "https://raw.gitmirror.com/ST-Kdream/-C-/refs/heads/master/version.txt"
#define New_Download_URL "https://github.com/ST-Kdream/-c-/releases"

size_t WriteCallback(void* contents, size_t size, size_t nmumb, string* s);
string get_remote_version();
bool is_update(const string& local_version,const string& remote_version);
void version_check();
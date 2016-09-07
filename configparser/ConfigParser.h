#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class ConfigParser
{
public:
	enum settings {
		sce_root = 0, sce_address, sce_user, sce_pass,
		tgt_root, tgt_address, tgt_user, tgt_pass, count
	};

	ConfigParser(string name, char separator = '=');
	map<settings, string> parse();
	bool chck_tokens(map<ConfigParser::settings, string> token_array);
	
private:
	ifstream mFile;
	map<string, settings> mKeyWords;
	char mSeparator;
	string mValsWL;
	string mKeyWordWL;
	bool mError;

	pair<string, string> get_tokens(string line);
	string filter(string val, string filter);
};


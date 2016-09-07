#include "ConfigParser.h"
#include <algorithm>
#include "ConfigParserException.h"

ConfigParser::ConfigParser(string name, char separator)
	: mSeparator(separator),
	mError(false)
{
	try {
		mFile = ifstream(name, std::ifstream::in);

		if (!mFile.is_open()) {
			throw ConfigParserException("Config file not found.");
			mError = true;
		}

	mKeyWords = {
		{"sourceroot", settings::sce_root},
		{"sourceaddress", settings::sce_address},
		{"sourceuser", settings::sce_user},
		{"sourcepass", settings::sce_pass},

		{"targetroot", settings::tgt_root},
		{"targetaddress", settings::tgt_address},
		{"targetuser", settings::tgt_user},
		{"targetpass", settings::tgt_pass}
	};

	mValsWL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
				 "0123456789.:-=@/";

	mKeyWordWL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz";

	}
	catch (const std::ifstream::failure &err) {
		throw ConfigParserException("Error opening file.");
		mError = true;
	}
}

map<ConfigParser::settings, string> ConfigParser::parse() 
{
	string line;
	map<settings, string> result;
	if (mError) {
		return result;
	}

	while(getline(mFile, line))
	{
		if (line.length() == 0 || line.find(mSeparator) == string::npos)
			continue;

		line = filter(line, mValsWL);

		pair<string, string> data = get_tokens(line);
		string key_word = filter(data.first, mKeyWordWL);

		// is valid token
		if (mKeyWords.count(key_word) > 0) {
			settings setting = mKeyWords.find(key_word)->second;
			// every token is accepted only once
			if (result.count(setting) == 0) {
				result.insert(make_pair(setting, data.second));
			}
			else throw ConfigParserException("Token duplication.");
		}
	}
	return result;
}

pair<string, string> ConfigParser::get_tokens(string line) 
{
	size_t separator = line.find(mSeparator);
	string key_word = line.substr(0, separator);
	string value = line.substr(separator + 1);

	return make_pair(key_word, value);
}

string ConfigParser::filter(string val, string filter) 
{
	string result = "";
	for (char c : val) {
		if (!isspace(c) && filter.find(c) != string::npos)
			result += c;
	}
	return result;
}

bool ConfigParser::chck_tokens(map<ConfigParser::settings, string> token_array) 
{
	return (token_array.size() == settings::count);
}

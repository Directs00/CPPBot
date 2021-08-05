#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include "json.hpp"
#include <string>
#include <windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
using json = nlohmann::json;

vector<GrowtopiaBot> bots;

inline bool exists_test(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main() {
	SetConsoleTitleA("CPPBot By DrOreo002 Fixed by .Lucy#0085");
	init();
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	string botDataPath = cCurrentPath + string("\\bot.json");
	
	json j;

	if (!exists_test(botDataPath)) {
		string gid, gps, vr, wd, ow;
		cout << "GrowID: " << endl;
		getline(cin, gid);
		cout << "Password: " << endl;
		getline(cin, gps);
		cout << "Version: " << endl;
		getline(cin, vr);
		cout << "World: " << endl;
		getline(cin, wd);
		cout << "Owner: " << endl;
		getline(cin, ow);
		std::ofstream o(botDataPath);
		j["username"] = gid,j["password"] = gps,j["gameVersion"] = vr,j["targetWorld"] = wd,j["ownerUsername"] = ow;
		o << j << std::endl;
	}
	
	cout << "Loading bot data on path (" << botDataPath << ")" << endl;

	ifstream i(botDataPath);
	i >> j;

	GrowtopiaBot bot = {
		j["username"], j["password"]
	};
	cout << "------------------------" << endl;
	cout << "Bot loaded!. Using username " << j["username"].get<string>() << ", With owner " + j["ownerUsername"].get<string>() << endl;

	bot.gameVersion = j["gameVersion"].get<string>();
	bot.worldName = j["targetWorld"].get<string>();
	bot.ownerUsername = j["ownerUsername"].get<string>();

	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
		bot.userLoop();
	}
}

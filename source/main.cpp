
// ClauLint(JsonLint) `s clautext code -> C++ code.. and merge.
// using ClauToCpp and ClauLint(JsonLint)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>

#include "wiz/ClauText.h"
#include "clautocpp.h"
#include "claulint.h"

inline std::pair<bool, wiz::load_data::UserType> LoadFile(const std::string& fileName)
{
	wiz::load_data::UserType ut;

	bool valid = wiz::load_data::LoadData::LoadDataFromFile5_2(fileName, ut, 0, 0);

	return { valid, std::move(ut) };
}
inline std::pair<bool, wiz::load_data::UserType> LoadJsonFile(const std::string& fileName)
{
	wiz::load_data::UserType ut;

	bool valid = wiz::load_data::LoadData::LoadDataFromFileFastJson(fileName, ut, -1, 0);

	return { valid, std::move(ut) };
}

// todo SaveJsonFile? for Make Schema?
inline bool SaveFile(const std::string& fileName, wiz::load_data::UserType* data)
{
	wiz::load_data::LoadData::SaveWizDB(*data, fileName, "1");
	return true;
}


int main(int argc, char* argv[])
{
	try {
		auto x = LoadFile(argv[1]);
		if (x.first) {
			Lint lint;
			ClauToCpp::Init();
			wiz::load_data::UserType ut(x.second);
			lint.Init(ut);
			if (lint.Run()) {
				std::cout << "success" << "\n";
			}
			else {
				std::cout << "fail" << "\n";
			}
		}
	}
	catch (...) {
		std::cout << "fail (internal error)" << "\n";
	}

	return 0;
}


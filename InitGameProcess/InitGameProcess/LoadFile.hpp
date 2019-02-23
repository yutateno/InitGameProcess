#pragma once
#include "Basic.hpp"

#ifndef _ME_LoadFile_HPP
#define _ME_LoadFile_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>


// 読み込むファイルの種類
enum class ELOADFILE { graph, soundmem, mv1model, soundStream, sound3DSource };


/*
素材を複合してロードするクラス
*/
class LoadFile
{
private:

	// ファイル読み込み
	static unsigned int file_size(std::ifstream &fin);


public:
	// コンストラクタ
	LoadFile() {};

	// デストラクタ
	~LoadFile() {};


	// メディアのロードを行う
	static void MyLoad(const std::string path, int& file, const ELOADFILE type);
};

#endif // !_ME_LoadFile_HPP
/** @file
 * @author Казанкин Максим
 * @version 1.0
 * @date 22.12.23
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля mdfile.h
 */
#pragma once
#include <locale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cctype>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <string>
#include <cassert>
#include <arpa/inet.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
using namespace std;
using namespace CryptoPP;

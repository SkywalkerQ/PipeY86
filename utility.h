/*
 *   Copyright (C) 2014 by Yuquan Fang<lynx.cpp@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 3, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <utility>
#define ESP 4
#define EBP 5
#define NO_REG 8

class Instruction;
typedef std::vector<Instruction> Program;
extern Program prog;

typedef std::map<int,int> Memory;
typedef std::vector< std::pair<int, std::string > > MemorySeq;

static inline int hex2num(char ch)
{
    if (ch>='0' && ch<='9') return ch - '0';
    if (ch>='a' && ch<='z') return ch - 'a' + 10;
    return ch - 'A' + 10;
}

static inline int byte2int(char a,char b)
{
    return hex2num(a)*16 + hex2num(b);
}

static inline int readHexBigEndian(const std::string& str,int l,int r)
{
    int ret = 0;
    for (int i=l; i<=r; i++) {
        ret *= 16;
        ret += hex2num(str[i]);
    }
    return ret;
}

static inline void readTripleStr(std::fstream& stream,std::string& s1,std::string& s2,std::string& s3)
{
    std::string line;
    std::getline(stream,line);
    std::stringstream ss;
    ss.clear();
    ss.str(line);
    ss >> s1 >> s2;
    int pos = line.find("|");
    if (pos==std::string::npos)
        s3 = "";
    else
        s3 = line.substr(pos + 2,line.length() - pos - 1);
    //std::cerr << line << std::endl;
    //std::cerr << s1 << " "<< s2 << " " << s3 << std::endl;
}

static inline int readHexSmallEndian(const std::string& str,int l,int r)
{
    int ret = 0;
    for (int i=r; i-1>=l; i-=2) {
        ret *= 256;
        ret += byte2int(str[i - 1],str[i]);
    }
    //std::cerr << "Read hex : " << ret
    return ret;
}

static inline std::string int2Hex(int hex,int minWidth = 3,bool withx = true)
{
    std::stringstream ss;
    ss.clear();
    ss.str("");
    //ss.setf ( std::ios::hex, std::ios::basefield );  // set hex as the basefield
    //ss.setf ( std::ios::showbase );
    if (withx)
        ss << "0x" << std::setfill('0') << std::setw(minWidth) << std::hex << std::uppercase << hex;
    else
        ss << std::setfill('0') << std::setw(minWidth) << std::hex << std::uppercase << hex;
    return ss.str();
}

static inline std::string hex2Data(const std::string& hex)
{
    std::stringstream ss;
    ss.clear();
    ss.str("");
    for (int i=0; i + 1<hex.length(); i+=2) {
        ss << hex[i] << hex[i + 1] << " ";
    }
    return ss.str();
}

static inline void printMemory(Memory& memory,MemorySeq& seq)
{
    seq.clear();
    Memory::iterator current = memory.begin();
    while (current!=memory.end()) {
        int curAddr = current->first;
        std::string curVal = int2Hex(memory[curAddr],2,false);
        curVal += "    ";
        curVal += int2Hex(memory[curAddr + 1],2,false);
        curVal += "    ";
        curVal += int2Hex(memory[curAddr + 2],2,false);
        curVal += "    ";
        curVal += int2Hex(memory[curAddr + 3],2,false);
        seq.push_back(std::make_pair(curAddr,curVal));

        current = memory.find(curAddr + 3);
        current ++;
    }
}

//hello
#endif

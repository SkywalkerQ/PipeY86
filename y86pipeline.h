#ifndef Y86PIPELINE_H
#define Y86PIPELINE_H
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

class Instruction;
#include "instruction.h"
typedef std::vector<Instruction> Program;
typedef Instruction* InstructionPtr;
typedef std::map<int,int> Memory;

class Y86Pipeline
{
private:
    InstructionPtr fetchI,decodeI,executeI,memoryI,writeBackI;
    int m_register[10];
    
    int forwardReg[10];
    bool forwardStat[10];
    
    Memory m_memory;
    int orgStackAddr;
    
    bool ZeroFlag,OverflowFlag,SignFlag;
    
    void writeForwarding(int num,int value,bool stat)
    {
        forwardReg[num] = value;
        forwardStat[num] = stat;
    }
    bool readForwarding(int num,int& dest)
    {
        if (!forwardStat[num])
            return false;
        dest = forwardReg[num];
        return true;
    }
    void writeRegister(int num,int value) 
    { 
        m_register[num] = value; 
        std::cerr << "writing value " << value << " to R[" << num << "]" << std::endl;
    }
    int readMemory(int address) { return m_memory[address]; }
    void writeMemory(int address,int value) { m_memory[address] = value; }
    void recoverForwarding();
    
public:
    friend class InstructionPrivate;
    Y86Pipeline(const std::string& filename);
    bool running();
    void run();
    void execute();
    //int readRegister(int num) { return m_register[num]; }
    
    void setConditionCode(int a,int b,int val);
    bool jle() { return (SignFlag ^ OverflowFlag) | ZeroFlag; }
    bool jl() { return SignFlag ^ OverflowFlag; }
    bool e() { return ZeroFlag; }
    bool jne() { return ~ZeroFlag; }
    bool jge() { return ~(SignFlag ^ OverflowFlag); }
    bool jg() { return ~(SignFlag ^ OverflowFlag) & (~ZeroFlag); }
    //int nextInstruction(int current,int step = 1) {  }
};

#endif // Y86PIPELINE_H

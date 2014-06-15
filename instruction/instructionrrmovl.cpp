#include "instructionprivate.h"
#include "y86pipeline.h"

InstructionRrmovl :: InstructionRrmovl(const std::string& m_instructionCode, int address):InstructionPrivate(address)
{
}

InstructionRrmovl :: ~ InstructionRrmovl()
{
}

void InstructionRrmovl :: fetchStage()
{
    InstructionPrivate :: fetchStage();
    if (m_instructionCode.size()<4){
        stat = INS;
        std :: cerr << "invalid instruction." << std::endl;
        //invalid instruction ...
    }
    rA = hex2num(m_instructionCode[2]);
    rB = hex2num(m_instructionCode[3]);
    icode = 2; ifun = 0;
    srcA = rA;
    dstE = rB;
}

bool InstructionRrmovl :: decodeStage()
{
    InstructionPrivate :: decodeStage();
    //valA = m_pipeline->readRegister(rB);
    currentOperation = "R[rA] <- valA;";
    return readReg(rA,valA);
}

void InstructionRrmovl :: executeStage()
{
    InstructionPrivate :: executeStage();
    valE = 0 + valA;
    writeForwardReg(rB,valE,true);
    currentOperation = "R[rB] <- valE;";
}

void InstructionRrmovl :: memoryStage()
{
    InstructionPrivate :: memoryStage();
}

void InstructionRrmovl :: writeBackStage()
{
    InstructionPrivate :: writeBackStage();
    //m_pipeline->writeRegister(rB,valE);
    writeRealReg(rB,valE);
}


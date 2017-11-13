#include "Disassembler.h"
#include <iostream>
#include<string>

Disassembler::Disassembler(std::function<void(Data&, std::vector<uint8_t> const& bytes)> dis)
{
	disopcode = dis;
}

void Disassembler::Decode(std::vector<uint8_t> const& bytes)
{
	bytes_=bytes;
	for(unsigned int address=0;address < bytes.size();)
	{
		Data data;
		data.address = address;
		disopcode(data,bytes_);
		PrintInstruction(data);
		data.Reset();
		address += data.instructionLength;
	}
}


Disassembler::~Disassembler()
{
}

void Disassembler::PrintOperands(Data& data) const
{
	if(data.trap)
	{
		std::cout<<"undef";
		return;
	}
	for (auto operand = data.operands.begin();operand != data.operands.end();++operand)
	{
		std::cout<<*operand;
		if(std::next(operand) != data.operands.end())
			std::cout<<", " ;
	}
}

void Disassembler::PrintMnemo(Data& data) const
{
	if(data.trap)
		std::cout<<"undef";
	else 
		std::cout<<data.mnemonic;
}

void Disassembler::PrintInstruction(Data& data) const
{
	PrintAddress(data);
	std::cout<<":\t";
	PrintMnemo(data);
	std::cout<<"\t";
	PrintOperands(data);
	std::cout<<"\n";
}

void Disassembler::PrintAddress(Data& data) const
{
	printf("%08x",data.address);
}
void Disassembler::DecodeInstructions(Data& data)
{
	int opcode = bytes_[data.address];
	opcode <<= 8;
	opcode += bytes_[data.address +1];
	switch((opcode >> 12) & 0xF)
	{
	case 0x0:
		data.mnemonic = "add";
		break;
	case 0x1:
		data.mnemonic = "adc";
		break;
	default:
		data.trap = true;
	}
}
#include "Disassembler.h"
#include <iostream>
#include<string>

Disassembler::Disassembler()
{
}

void Disassembler::Decode(std::vector<uint8_t> const& bytes)
{
	for(unsigned int address=0;address < bytes.size();)
	{
		Data data;
		callback(data);
		data.address = address;
		PrintInstruction(data);
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
			std::cout<<', ';
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

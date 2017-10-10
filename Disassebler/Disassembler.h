#pragma once
#include <vector>
#include <array>
#include <functional>

class Disassembler
{
public:
	struct Data
	{
		std::array<std::string,20> operands;
		std::string mnemonic;
		unsigned int instructionLength=2;
		unsigned int address;
		bool trap=false;
	};
	std::function<void(Data &data)> callback;
		Disassembler();
	void Decode(std::vector<uint8_t> const &bytes);
	~Disassembler();
private:
	void PrintOperands(Data & const data) const;
	void PrintMnemo(Data & const data) const;
	void PrintInstruction(Data &const data) const;
	void PrintAddress(Data &const data) const;
};


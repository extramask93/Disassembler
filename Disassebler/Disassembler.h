#pragma once
#include <vector>
#include <array>
#include <functional>
struct Data
{
	std::vector<std::string> operands;
	std::string mnemonic = "";
	unsigned int instructionLength = 2;
	unsigned int address = 0;
	bool trap = false;
	void Reset()
	{
		trap = false;
		instructionLength = 2;
		mnemonic = "";
		operands.clear();
	}
};
class Disassembler
{
public:
	std::function<void(Data &data,std::vector<uint8_t> const &)> disopcode;
	Disassembler(std::function<void(Data&, std::vector<uint8_t> const& bytes)> dis);
	void Decode(std::vector<uint8_t> const &bytes);
	~Disassembler();
private:
	void DecodeInstructions(Data &data);
	void PrintOperands(Data & const data) const;
	void PrintMnemo(Data & const data) const;
	void PrintInstruction(Data &const data) const;
	void PrintAddress(Data &const data) const;
	std::vector<uint8_t> bytes_;
};


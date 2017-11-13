#pragma once
#include <string>
#define WRITE_MNEMO(n) { data.mnemonic += n; }
static constexpr bool brainDead = false; 
namespace avr{
inline int ExtractQ(int opcode)
{
	int ret = ((opcode >> 7) & 0x18) & (opcode & 0x7) & ((opcode >> 8) & 0x20);
	return ret;
}
static const std::string reg_names[] = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10",
								  "r11","r12","r13","r14","r15","r16","r17","r18","r19","r20","r21",
									"r22","r23","r24","r25","r26","r27","r28","r29","r30","r31"
};
inline void Write_RD(int opcode, Data &data)
{
	opcode >>=4;
	opcode &= 0x1F;
	data.operands.push_back(reg_names[opcode]);
}
inline void Write_RR(int opcode, Data &data)
{
	opcode = (opcode & 0xF) | ((opcode & 0x200) >> 5);
	data.operands.push_back(reg_names[opcode]);
}
void DecodeInstructions(Data& data, std::vector<uint8_t> const& bytes_)
{
	int opcode = bytes_[data.address];
	opcode <<= 8;
	opcode += bytes_[data.address + 1];
	switch ((opcode >> 12) & 0xF)
	{
	case 0x0:		/*NOP/MOVW/MULS/FMUL/FMULS/FMULSU/MULSU/CPC/SBC/LSL*/
		switch((opcode >> 10) & 0x3)
		{
		case 0x0:		/*NOP/MOVW/MULS/FMUL/FMULS/FMULSU/MULSU*/
			switch((opcode >> 8) & 0x3)
			{
			case 0x0:		/*NOP*/
				break;
			case 0x1:		/*MOVW*/
				break;
			case 0x2:		/*MULS*/
				break;
			case 0x3:		/*FMUL/FMULS/FMULSU/MULSU*/
				switch(((opcode >> 6) & 0x1) & ((opcode >> 3) & 0x1))
				{
				case 0x0:		/*MULSU*/
					break;
				case 0x1:		/*FMUL*/
					break;
				case 0x2:		/*FMULS*/
					break;
				case 0x3:		/*FMULSU*/
					break;
				}
				break;
			}
			break;
		case 0x1:		/*CPC*/
			break;
		case 0x2:		/*SBC*/
			break;
		case 0x3:		/*ADD/LSL*/
			break;
		}
	case 0x1:		/*CPSE/CP/SUB/ROL*/
		switch((opcode >> 10) & 0x3) {
		case 0x0:		/*CPSE*/
			break;
		case 0x1:		/*CP*/
			break;
		case 0x2:		/*SUB*/
			break;
		case 0x3:		/*ROL/ADC*/
			break;
		}
		break;
	case 0x2:		/*AND/TST/CLR/EOR/OR/MOV*/
		switch((opcode >> 10) & 0x3) {
		case 0x0:		/*AND/TST*/
			break;
		case 0x1:		/*CLR/EOR*/
			break;
		case 0x2:		/*OR*/
			break;
		case 0x3:		/*MOV*/
			break;
		}
		break;
	case 0x3:		/*CPI*/
		break;
	case 0x4:		/*SBCI*/
		break;
	case 0x5:		/*SUBI*/
		break;
	case 0x6:		/*ORI/SBR*/
		break;
	case 0x7:		/*ANDI/CBR*/
		break;
	case 0x8:		/*LD Rd,Z/LD Rd,Y/ST Rd,Z/ST Rd,Y/ldd Rd, Z+q/ldd Rd, Y+q/std Rd, Z+q/std Rd, Y+q*/
	case 0xA:
		if(brainDead)		/*sts16*/
		{
			;
		}
		else {
		switch(((opcode >> 3) & 0x1) & ((opcode >> 7) & 0x2))
		{
		case 0x0:		/*ldd Rd, Z+q / ld Rd, Z*/
			if(ExtractQ(opcode))		/*ldd Rd, Z+q*/
				;
			else		/*ld Rd, Z*/
				;
			break;
		case 0x1:		/*ldd Rd, Y+q / ld Rd, Y*/
			if (ExtractQ(opcode))		/*ldd Rd, Y+q*/
				;
			else		/*ld Rd, Y*/
				;
			break;
		case 0x2:		/*std Rd, Z+q / st Rd, Z*/
			if (ExtractQ(opcode))		/*std Rd, Z+q*/
				;
			else		/*st Rd, Z*/
				;
			break;
		case 0x3:		/*std Rd, Y+q / st Rd, Y*/
			if (ExtractQ(opcode))		/*std Rd, Y+q*/
				;
			else		/*st Rd, Y*/
				;
			break;
		}}
		break;
	case 0x9:
		switch((opcode >> 9) & 0x7)
		{
		case 0x0:		/*LDS32/LDD2/LDD3/LPM/LPM/ELPM2/ELPM3/LDD2/LDD3/LD1/LD2/LD3/POP*/
			switch(opcode & 0xF)
			{
			case 0x0:		/*LDS32/16*/
				break;
			case 0x1:		/*LD Rd, Z+*/
				break;
			case 0x2:		/*LD Rd, -Z*/
				break;
			case 0x4:		/*LPM Rd,Z*/
				break;
			case 0x5:		/*LPM Rd,Z+*/
				break;
			case 0x6:		/*ELPM Rd*/
				break;
			case 0x7:		/*ELPM Rd,Z*/
				break;
			case 0x9:		/*LD Rd, Y+*/
				break;
			case 0xA:		/*LD Rd,-Y*/
				break;
			case 0xC:		/*LD Rd, X*/
				break;
			case 0xD:		/*LD Rd, X+*/
				break;
			case 0xE:		/*LD Rd -X*/
				break;
			case 0xF:		/*POP*/
				break;
			default:
				data.trap = true;
			}
			break;
		case 0x1:		/*STS/STD6/STD7/XCH/LAS/LAC/LAT/STD2/STD3/ST1/ST2/ST3/PUSH*/
			switch(opcode & 0xF)
			{
			case 0x0:		/*STS*/
				break;
			case 0x1:		/*ST Z+,R*/
				break;
			case 0x2:		/*ST -Z,R*/
				break;
			case 0x4:		/*XCH*/
				break;
			case 0x5:		/*LAS*/
				break;
			case 0x6:		/*LAC*/
				break;
			case 0x7:		/*LAT*/
				break;
			case 0x9:		/*ST Y+,R*/
				break;
			case 0xA:		/*ST -Y,R*/
				break;
			case 0xC:		/*ST X,R*/
				break;
			case 0xD:		/*ST X+,R*/
				break;
			case 0xE:		/*ST -X,R*/
				break;
			case 0xF:		/*PUSH*/
				break;
			default:
				data.trap = true;
			}
			break;
		case 0x2:		/*SEC/IJMP/COM/NEG/SWAP/INC/ASR/LSR/ROR/BSET/DEC/CALL/DES/JMP/SEZ/EIJMP/SEN/SEV/SEH/SET/SEI/CLC/BCLR/CLZ/CLN/CLV/CLS/CLH/CLT/CLI/WDR/EMLP/SLEEP/BREAK/SPM/SPM2/ICALL/SPM2/EICALL/RET/RETILPM*/
			switch(opcode & 0xF)
			{
			case 0x0:		/*SEC/COM*/
				break;
			case 0x1:		/*NEG*/
				break;
			case 0x2:		/*SWAP*/
				break;
			case 0x3:		/*INC*/
				break;
			case 0x5:		/*ASR*/
				break;
			case 0x6:		/*LSR*/
				break;
			case 0x7:		/*ROR*/
				break;
			case 0x8:		/*BSET/SEZ/SEN/SEV/SEH/SET/SEI/CLC/BCLR/CLZ/CLN/CLV/CLS/CLH/CLT/CLI/WDR/EMLP/SLEEP/BREAK/SPM/SPM2/SPM2/RET/RETI/LPM*/
				switch((opcode >> 7) & 0x3) /*BSET/SEC/SEZ/SEN/SEV/SEH/SET/SEI*/
				{
				case 0x0:
					switch((opcode >> 4) & 0x7)
					{
					case 0x0:		/*BSET/SEC*/
						break;
					case 0x1:		/*SEZ*/
						break;
					case 0x2:		/*SEN*/
						break;
					case 0x3:		/*SEV*/
						break;
					case 0x5:		/*SEH*/
						break;
					case 0x6:		/*SET*/
						break;
					case 0x7:		/*SEI*/
						break;
					}
					break;
				case 0x1:
					switch((opcode >> 4) & 0x7) {
					case 0x0:		/*CLC*/
						break;
					case 0x1:		/*CLZ/*/
						break;
					case 0x2:		/*CLN*/
						break;
					case 0x3:		/*CLV*/
						break;
					case 0x4:		/*CLS*/
						break;
					case 0x5:		/*CLH*/
						break;
					case 0x6:		/*CLT*/
						break;
					case 0x7:		/*CLI*/
						break;
					}
					break;
				case 0x2:		/*RET/RETI*/
					switch((opcode >> 4) & 0x7)
					{
					case 0x0:		/*RET*/
						break;
					case 0x1:		/*RETI*/
						break;
					default:
						data.trap = true;
					}
					break;
				case 0x3:		/*SLEEP/BREAK/WDR/LPM R0, Z/ELPM R0/SPM/SPM Z+*/
					switch((opcode >> 4) & 0x7)
					{
					case 0x0:		/*SLEEP*/
						break;
					case 0x1:		/*BREAK*/
						break;
					case 0x2:		/*WDR*/
						break;
					case 0x4:		/*LPM R0, Z*/
						break;
					case 0x5:		/*ELPM R0*/
						break;
					case 0x6:		/*SPM*/
						break;
					case 0x7:		/*SPM Z+*/
						break;
					default:
						data.trap = true;
					}
					break;
				default:
					data.trap = true;
				}
				break;
			case 0x9:		/*EIJMP/ICALL/EICALL*/
				switch((opcode >> 4) & 0xF)
				{
				case 0x0:		/*ICALL*/
					break;
				case 0x1:		/*EICALL/EIJMP*/
					switch((opcode >> 8) & 0x1)
					{
					case 0x0:		/*EIJMP*/
						break;
					case 0x1:		/*EICALL*/
						break;
					}
					break;
				default:
					data.trap =true;
				}
				break;
			case 0xA:		/*DEC*/
				break;
			case 0xB:		/*DES*/
				break;
			case 0xC:		
			case 0xD:		/*JMP*/
				break;
			case 0xE:
			case 0xF:		/*CALL*/
				break;
			default:
				data.trap = true;
			}
			break;
		case 0x3:		/*ADIW/SBIW*/
			switch ((opcode >> 8) & 0x1)
			{
			case 0x0:		/*ADIW*/
				break;
			case 0x1:		/*SBIW*/
				break;
			}
			break;
		case 0x4:		/*CBI/SBIC*/
			switch ((opcode >> 8) & 0x1)
			{
			case 0x0:		/*CBI*/
				break;
			case 0x1:		/*SBIC*/
				break;
			}
			break;
		case 0x5:		/*SBI/SBIS*/
			switch((opcode >> 8) & 0x1)
			{
			case 0x0:		/*SBI*/
				break;
			case 0x1:		/*SBIS*/
				break;
			}
			break;
		case 0x6:
		case 0x7:		/*MUL*/
			break;
		}
		break;
	case 0xB:		/*IN/OUT*/
		switch((opcode >> 11) & 0x1)
		{
		case 0x0:		/*IN*/
			break;
		case 0x1:		/*OUT*/
			break;
		}
		break;
	case 0xC:		/*RJMP*/
		break;
	case 0xD:		/*RCALL*/
		break;
	case 0xE:		/*LDI/SER*/
		break;
	case 0xF:
		switch((opcode >> 10) & 0x3)
		{
		case 0x0:		/*BRLO/BRCS/BREQ/BRMI/BRVS/BRLT/BRHS/BRTS/BRIE/BRBS/BRCC/BRSH/BRNE/BRPL/BRVC/BRGE/BRHC/BRTC/BRID*/
			switch(opcode & 0x7)
			{
			case 0x0:		/*BRLO or BRCS*/
				break;		
			case 0x1:		/*BREQ*/
				break;	
			case 0x2:		/*BRMI*/
				break;
			case 0x3:		/*BRVS*/
				break;
			case 0x4:		/*BRLT*/
				break;
			case 0x5:		/*BRHS*/
				break;
			case 0x6:		/*BRTS*/
				break;
			case 0x7:		/*BRIE*/
				break;
			}
			break;
		case 0x1:		/*BRCC/BRSH/BRNE/BRPL/BRVC/BRGE/BRHC/BRTC/BRID*/
			switch(opcode & 0x7)
			{
			case 0x0:		/*BRCC or BRSH*/
				break;
			case 0x1:		/*BRNE*/
				break;
			case 0x2:		/*BRPL*/
				break;
			case 0x3:		/*BRVC*/
				break;
			case 0x4:		/*BRGE*/
				break;		
			case 0x5:		/*BRHC*/
				break;
			case 0x6:		/*BRTC*/
				break;
			case 0x7:		/*BRID*/
				break;
			}
			break;
		case 0x2:		/*BLD/BST*/
			switch ((opcode >> 9) & 0x1)
			{
			case 0x0:		/*BLD*/
				break;
			case 0x1:		/*BST*/
				break;
			}
			break;
		case 0x3:		/*SBRC/SBRS*/
			switch((opcode >> 9) & 0x1)
			{
			case 0x0:		/*SBRC*/
				break;
			case 0x1:		/*SBRS*/
				break;
			}
			break;
		}
		break;
	default:
		data.trap = true;
	}
}
}
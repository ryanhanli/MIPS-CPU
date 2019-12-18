#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "i_instructions.h"

void addi(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	int16_t s = (65535 & (instruction));
	int32_t IMM = s;
	int TEMP = registers[RS];
	int result = TEMP+IMM;
	registers[RT]=result;
}

void addiu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int IMM = (65535 & instruction);
	unsigned int TEMP = registers[RS];
	unsigned int result = TEMP+IMM;
	registers[RT]=result;
}

void andi(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int IMM = (65535 & instruction);
	registers[RT]=registers[RS]&IMM;
}

void ori(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int IMM = (65535 & instruction);
	registers[RT]=registers[RS]|IMM;
}

void xori(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int IMM = (65535 & instruction);
	registers[RT]=registers[RS]^IMM;
}

void slti(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	int16_t s = (65535 & (instruction));
	int32_t IMM = s;
	if(registers[RS]<IMM){
		registers[RT]=1;
	} else {
		registers[RT]=0;
	}
}

void sltiu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int IMM = (65535 & instruction);
	unsigned int TEMP = registers[RS];
	if(TEMP<IMM){
		registers[RT]=1;
	} else {
		registers[RT]=0;
	}
}

void beq(unsigned int instruction);

void bne(unsigned int instruction);

void lb(unsigned int instruction);

void lbu(unsigned int instruction);

void lh(unsigned int instruction);

void lhu(unsigned int instruction);

void lw(unsigned int instruction);

void lui(unsigned int instruction);

void sb(unsigned int instruction);

void sh(unsigned int instruction);

void sw(unsigned int instruction);
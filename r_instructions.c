
#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "r_instructions.h"

int bitExtracted(int number, int k, int p) 
{ 
	return (((1 << k) - 1) & (number >> (p - 1))); 
}

int bitExtractedL(long number, int k, int p) 
{ 
	return (((1 << k) - 1) & (number >> (p - 1))); 
} 

void add(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	int i = (int)registers[RS];
	int j = (int)registers[RT];
	int result_temp = i+j;
	unsigned int result = (unsigned int)result_temp;
	registers[RD]=result;
	
}

void addu(unsigned int instruction){ 
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	unsigned int result=registers[RS]+registers[RT];
	registers[RD]=result;
}
	
void sub(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	int i = (int)registers[RS];
	int j = (int)registers[RT];
	int result_temp = i-j;
	unsigned int result = (unsigned int)result_temp;
	registers[RD]=result;
}

void subu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	unsigned int result=registers[RS]-registers[RT];
	registers[RD]=result;
} 

void mult(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	long res = (long)(registers[RS]) * (long)(registers[RT]);
	HI = (4294967295 & ((res)>>32));
	LO = 4294967295 & res;
	
} 

void multu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	unsigned long res = (unsigned long) registers[RS] * (unsigned long) registers[RT];
	HI = (4294967295 & ((res)>>32));
	LO = 4294967295 & res;
} 

void div(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	int res = (int)(registers[RS]) / (int)(registers[RT]);
	int remainder = (int)(registers[RS]) % (int)(registers[RT]);
	HI = remainder;
	LO = res;
} 

void divu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	int res = registers[RS]/registers[RT];
	int remainder = registers[RS]%registers[RT];
	HI = remainder;
	LO = res;
} 

void and(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	registers[RD]=registers[RS]&registers[RT];
	
} 

void nor(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	registers[RD]=~(registers[RS]|registers[RT]);
	
} 

void or(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	registers[RD]=registers[RS]|registers[RT];
} 

void xor(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	registers[RD]=registers[RS]^registers[RT];
	
} 

void sll(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	registers[RD] = registers[RT]<<shamt;
	
} 

void sllv(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	registers[RD] = registers[RS]<<registers[RT];
	
} 

void srl(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	registers[RD] = registers[RT]>>shamt;
} 

void sra(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	unsigned int sign = (registers[RT])>>31;
	if (sign==1){
		unsigned int mask = ((1<<((int)shamt))-1);
		registers[RD] = (unsigned int) (registers[RT]>>(shamt));
		registers[RD] = (unsigned int) (registers[RD]|(mask<<(32-(shamt))));
	} else{
		registers[RD]=(unsigned int) (registers[RT] >> (shamt));
	}
	//value < 0 ? ~(~value >> amount) : value >> amount ;
} 

void srlv(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	registers[RD] = registers[RS]>>registers[RT];
	
} 

void srav(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	unsigned int shamt = (31 & ((instruction)>>6));
	unsigned int sign = (registers[RS])>>31;
	if (sign==1){
		unsigned int mask = ((1<<(registers[RT]))-1);
		registers[RD] = (unsigned int) (registers[RS]>>(registers[RT]));
		registers[RD] = (unsigned int) (registers[RD]|(mask<<(32-(registers[RT]))));
	} else{
		registers[RD]=(unsigned int) (registers[RT] >> (registers[RT]));
	}
} 

void slt(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	int i = (int)registers[RS];
	int j = (int)registers[RT];
	if (i<j) {
		registers[RD]=1;
	} else {
		registers[RD]=0;
	}
} 

void sltu(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	unsigned int RT = (31 & ((instruction)>>16));
	unsigned int RD = (31 & ((instruction)>>11));
	
	if(registers[RS]<registers[RT]){
		registers[RD]=1;
	} else {
		registers[RD]=0;
	}
} 

void jr(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	npc = registers[RS];
} 

void jalr(unsigned int instruction){
	unsigned int RS = (31 & ((instruction)>>21));
	registers[31] = pc + 4;
	npc = registers[RS];
} 

void mfhi(unsigned int instruction){
	unsigned int RD = (31 & ((instruction)>>11));
	registers[RD]=HI;
} 

void mflo(unsigned int instruction){
	unsigned int RD = (31 & ((instruction)>>11));
	registers[RD]=LO;
} 
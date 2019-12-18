#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "i_instructions.h"
#include "r_instructions.h"
#include "j_instructions.h"


void use_rinstruction(unsigned int instruc);

unsigned int registers[NUM_REGISTERS];

unsigned int pc;

unsigned int npc;

unsigned int HI;

unsigned int LO;

unsigned char memory[MEMORY_SIZE_IN_BYTES];


void cpu_initialize(){
    pc = CODE_STARTING_ADDRESS;
    npc = CODE_STARTING_ADDRESS;
	registers[29] = STACK_STARTING_ADDRESS;
    registers[0] = 0;
}

void use_rinstruction(unsigned int instruc){
    
    switch(((instruc) & 63)){
            
        case 0x20:
            add(instruc);
            break;
            
        case 0x21:
            addu(instruc);
            break;
            
        case 0x22:
            sub(instruc);
            break;
            
        case 0x23:
            subu(instruc);
            break;
        
        case 0x18:
            mult(instruc);
            break;
        
        case 0x19:
            multu(instruc);
            break;
        
        case 0x1a:
            div(instruc);
            break;

        case 0x1b:
            divu(instruc);
            break;
            
        case 0x10:
            mfhi(instruc);
            break;
            
        case 0x12:
            mflo(instruc);
            break;
            
        case 0x24:
            and(instruc);
            break;
            
        case 0x25:
            or(instruc);
            break;
        
        case 0x26:
            xor(instruc);
            break;
        
        case 0x27:
            nor(instruc);
            break;
        
        case 0x2A:
            slt(instruc);
            break;

        case 0x2B:
            sltu(instruc);
            break;
            
        case 0x00:
            sll(instruc);
            break;
            
        case 0x04:
            sllv(instruc);
            break;
            
        case 0x02:
            srl(instruc);
            break;
            
        case 0x06:
            srlv(instruc);
            break;
        
        case 0x03:
            sra(instruc);
            break;
        
        case 0x07:
            srav(instruc);
            break;
			
        case 0x08:
            jr(instruc);
            break;
			
        case 0x09:
            jalr(instruc);
            break;
			
        case 0x0c:
            syscall(instruc);
            break;
            
    }
}

int while_switch = 0;
void cpu_execute(){
    while_switch=1;
    while(while_switch){
        pc = npc;
        npc = pc+4;
        unsigned int *temp = (unsigned int*) &memory[pc];
        unsigned int instruc = *temp;
		
        switch(((instruc>>26) & 63)){
            case  0:
                use_rinstruction(instruc);
                break;
                
            case 0x08:
                addi(instruc);
                break;
                
            case 0x09:
                addiu(instruc);
                break;
                
            case 0x23:
                lw(instruc);
                break;
                
            case 0x21:
                lh(instruc);
                break;
            
            case 0x25:
                lhu(instruc);
                break;
            
            case 0x20:
                lb(instruc);
                break;
            
            case 0x24:
                lbu(instruc);
                break;

            case 0x2b:
                sw(instruc);
                break;
                
            case 0x29:
                sh(instruc);
                break;
                
            case 0x28:
                sb(instruc);
                break;
                
            case 0x0f:
                lui(instruc);
                break;
                
            case 0x0d:
                ori(instruc);
                break;
            
            case 0x0c:
                andi(instruc);
                break;
            
            case 0x0e:
                xori(instruc);
                break;
            
            case 0x0a:
                slti(instruc);
                break;

            case 0x0b:
                sltiu(instruc);
                break;
                
            case 0x04:
                beq(instruc);
                break;
              
            case 0x05:
                bne(instruc);
                break;
             
            case 0x02:
                j(instruc);
                break;
              
            case 0x03:
                jal(instruc);
                break;
        }
        
    }
}


void cpu_exit(int errorcode){
    while_switch = 0;
    if (!errorcode){
        printf("\nProgram terminated normally\n");
    }
    else{
        printf("\nProgram terminated abnormally with errorcode= %d \n", errorcode);
    }
}

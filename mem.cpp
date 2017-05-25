#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
string ins_MEMWB,targetType_MEMWB;
unsigned int finalContent_MEMWB,target_MEMWB;
void MEM(){
	string ins_MEM=ins_EXMEM,targetType_MEM=targetType_EXMEM;
	unsigned int address=result_EXMEM,target_MEM=target_EXMEM;
finalContent_MEMWB=result_EXMEM;

if (mem_AO){errorfile << "In cycle " << c_n+1 << ": Address Overflow" << endl; go_halt = true;mem_AO=false;}
if (mem_ME){errorfile << "In cycle " << c_n+1 << ": Misalignment Error" << endl; go_halt = true; mem_ME=false;}
//if (mem_NO){errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;mem_NO=false;}
if (!go_halt){
		if (ins_MEM=="LB"){finalContent_MEMWB = HtoD(address, 1, false); if (finalContent_MEMWB>= 128) finalContent_MEMWB = finalContent_MEMWB | 0xFFFFFF00;}
		if (ins_MEM=="LH"){finalContent_MEMWB = HtoD(address, 2, false); if (finalContent_MEMWB > 32767) finalContent_MEMWB = finalContent_MEMWB | 0xFFFF0000;}
		if (ins_MEM=="LW"){finalContent_MEMWB = HtoD(address, 4, false);}
		if (ins_MEM=="LBU"){finalContent_MEMWB = HtoD(address, 1, false);}
		if (ins_MEM=="LHU"){finalContent_MEMWB = HtoD(address, 2, false);}
		if (ins_MEM=="SB"){save(address, 1,( target_MEM & 0x000000FF));target_MEM=100;}
		if (ins_MEM=="SH"){save(address, 2,( target_MEM & 0x0000FFFF));target_MEM=100;}
		if (ins_MEM=="SW"){save(address, 4, target_MEM);target_MEM=100;}}
MEMs=ins_MEM;	ins_MEMWB=ins_MEM;targetType_MEMWB=targetType_MEM;target_MEMWB=target_MEM;
} 







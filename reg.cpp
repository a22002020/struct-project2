#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
//-----------------------------Res----------------------------------
unsigned int res[32], Lo=0, Hi=0, pc=0,moto_pc=0;
unsigned int Tres[100],TLo, THi,Tpc,Tresrt,Tresrd,Tresrs;
 string IFs,IDs,EXs,WBs,MEMs,IFID_reg;
void Res_init() {
	ins_IDEX="NOP";
	RS_IDEX=-1,RT_IDEX=-1,RD_IDEX=-1,C_IDEX=0;
	ins_EXMEM="NOP";
	targetType_EXMEM="NOP";
	result_EXMEM=0;
	target_EXMEM=100;
	
	ins_MEMWB="NOP";
	targetType_MEMWB="NOP";
	finalContent_MEMWB=0;
	target_MEMWB=100;
	
	
	pc = BtoD(instucts[0]); moto_pc = pc;
	res[29] = datas[0];
	IFs="00000000000000000000000000000000";IFID_reg="00000000000000000000000000000000";
	IDs="NOP";
	EXs="NOP";
	WBs="NOP";
	MEMs="NOP";
	if (outfile.is_open()) {
		outfile << "cycle 0" << endl;
		for (int i = 0; i < 32; i++) { outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl; }
		outfile << "$HI: " << DtoH(Hi) << endl;
    outfile << "$LO: " << DtoH(Lo) << endl;
		//outfile << "PC: " << DtoH(pc) << endl;
	}
}

//------------------------------------------------------------------
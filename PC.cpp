#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;

void IF(){
	if (!stall_ID){
	Tpc+=4;
	string ins;
	if(((int)pc-(int)moto_pc)>=0/*&&!go_halt*/)ins=instucts[(pc-moto_pc)/4 + 2];else ins="00000000000000000000000000000000";
 if (((int)pc-(int)moto_pc)>=(ins_num-2)*4) ins="00000000000000000000000000000000";
	IFs=ins;
	IFID_reg=IFs;
// if (IFID_reg=="00000000000000000000000000000000"){cout<<c_n<<"zhebukexue"<<endl;}
 //if (c_n==20)cout<<IFID_reg<<endl;
    IFs=DtoH(BtoD(IFs));if (IFs=="0x00000000")IFID_reg="00000000000000000000000000000000";
		if (TBflush){
		IFs=IFs+" to_be_flushed";
		IFID_reg="00000000000000000000000000000000";
		Tpc=pc+4*jumpC;
	}
	
	
	}
	else
	{
		string ins;
		if(((int)pc-(int)moto_pc)>=0)ins=instucts[(pc-moto_pc)/4 + 2];else ins="00000000000000000000000000000000";
		IFs=DtoH(BtoD(ins))+" to_be_stalled";
		
	}

	
	//IFs=DtoH(BtoD(ins));
}

string tGT;unsigned int content,targetReg;

void WB(int c){
	WBs=ins_MEMWB;
	tGT=targetType_MEMWB;
	content=finalContent_MEMWB,targetReg=target_MEMWB;
	if (targetReg!=100){Tres[targetReg]=content;}
 if (targetReg==0){errorfile << "In cycle " << c_n+1 << ": Write $0 Error" << endl;}
	Tres[0]=0;

}
void output(){
	outfile<<"IF: "<<IFs<<endl;
	outfile<<"ID: "<<IDs<<endl;
	outfile<<"EX: "<<EXs<<endl;
	outfile<<"DM: "<<MEMs<<endl;
	outfile<<"WB: "<<WBs<<endl;
	//outfile<<targetType_MEMWB<<endl;
	outfile << endl;
	outfile << endl;
	
}
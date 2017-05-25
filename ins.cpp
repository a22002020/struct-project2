#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
string ins_IDEX;
int RS_IDEX=-1,RT_IDEX=-1,RD_IDEX=-1,C_IDEX=0;
void write_zero(int k){
	if (k == 0) errorfile << "In cycle " << c_n << ": Write $0 Error" << endl;
}
void RType(){
	//cout<<IFID_reg<<endl;
	 RS_IDEX = BtoD(IFID_reg.substr(6, 5)); RT_IDEX = BtoD(IFID_reg.substr(11, 5)); C_IDEX= BtoDs(IFID_reg.substr(16)); 
}
void RTypeU(){
	//cout<<IFID_reg<<endl;
	 RS_IDEX = BtoD(IFID_reg.substr(6, 5)); RT_IDEX = BtoD(IFID_reg.substr(11, 5)); C_IDEX= BtoD(IFID_reg.substr(16)); 
}


void harzardDetectID(string str){
	string tEXs=EXs;
		if (str=="ADD"||str=="ADDU"||str=="SUB"||str=="AND"||str=="OR"||str=="XOR"||str=="NOR"||str=="NAND"||str=="SLT"||str=="MULT"||str=="MULTU"||str=="SW"||str=="SH"||str=="SB"){
			if (target_EXMEM==RS_IDEX&&target_EXMEM!=0)	{
				if (targetType_EXMEM=="LRT"){stall_ID=true;}	
			}
		
			if (target_EXMEM==RT_IDEX&&target_EXMEM!=0)	{
				if (targetType_EXMEM=="LRT"){stall_ID=true;}
			}	
			}
		if (
		str=="ADDI"||str=="ADDIU"||str=="LW"||str=="LH"||str=="LHU"||str=="LB"
		||str=="LBU"||str=="ANDI"||str=="ORI"
		||str=="NORI"||str=="SLTI"){
	
			if (target_EXMEM==RS_IDEX&&target_EXMEM!=0)	{
				if (targetType_EXMEM=="LRT"){stall_ID=true;}
			}
		
		}
		if (str=="SLL"||str=="SRL"||str=="SRA"){
				
			if (target_EXMEM==RT_IDEX&&target_EXMEM!=0)	{
				if (targetType_EXMEM=="LRT"){stall_ID=true;}
			}	
		}
		
		
}
void branchHF(string instr){
	if (instr=="BGTZ"||instr=="JR"){
		if (target_EXMEM==RS_IDEX) stall_ID=true;
		if (target_MEMWB==RS_IDEX&&targetType_MEMWB=="LRT") stall_ID=true;
		if (!stall_ID){
			unsigned int Tresrs=Tres[RS_IDEX];
			string tIDs=IDs;
			if (targetReg==RS_IDEX&&tGT=="LRT") {Tresrs=content;}
			if (target_MEMWB==RS_IDEX&&targetType_MEMWB!="LRT") {Tresrs=finalContent_MEMWB;if(target_MEMWB!=0)tIDs=IDs+" fwd_EX-DM_rs_$"+to_string(RS_IDEX);}
			IDs=tIDs;
			if (instr=="BGTZ"&&(int)Tresrs>0&&C_IDEX!=0){TBflush=true;jumpC=C_IDEX;}
      if (instr=="JR"){unsigned int tTpc;tTpc=Tresrs;/*if (tTpc!=pc+4)*/{TBflush=true;jumpC=(tTpc-pc)/4;}}
		}
	}
	else{
		if (target_EXMEM==RS_IDEX) stall_ID=true;
		if (target_EXMEM==RT_IDEX) stall_ID=true;
		if (target_MEMWB==RS_IDEX&&targetType_MEMWB=="LRT") stall_ID=true;
		if (target_MEMWB==RT_IDEX&&targetType_MEMWB=="LRT") stall_ID=true;
		if (!stall_ID){
			unsigned int Tresrs=Tres[RS_IDEX];
			unsigned int Tresrt=Tres[RT_IDEX];
			string tIDs=IDs;
			if (targetReg==RS_IDEX&&tGT=="LRT") {Tresrs=content;}
			if (target_MEMWB==RS_IDEX&&targetType_MEMWB!="LRT") {Tresrs=finalContent_MEMWB;if(target_MEMWB!=0)tIDs=IDs+" fwd_EX-DM_rs_$"+to_string(RS_IDEX);}
			IDs=tIDs;
			if (targetReg==RT_IDEX&&tGT=="LRT") {Tresrt=content;}
			if (target_MEMWB==RT_IDEX&&targetType_MEMWB!="LRT") {Tresrt=finalContent_MEMWB;if(target_MEMWB!=0)tIDs=IDs+" fwd_EX-DM_rt_$"+to_string(RT_IDEX);}
			IDs=tIDs;
    //  cout<<c_n<<endl;
    //  cout<<RS_IDEX<<" "<<Tresrs<<endl;
    //  cout<<RT_IDEX<<" "<<Tresrt<<endl;
			if (instr=="BEQ"&&Tresrs==Tresrt&&C_IDEX!=0){TBflush=true;jumpC=C_IDEX;}
			if (instr=="BNE"&&Tresrs!=Tresrt&&C_IDEX!=0){TBflush=true;jumpC=C_IDEX;}
		}
		
	}
}
void jumpFL(string str){
  unsigned int tTpc;
  tTpc=Tpc & 0xF0000000;tTpc=tTpc | (C_IDEX * 4); 
  if (tTpc!=pc+4){TBflush=true;jumpC=(tTpc-pc)/4;}
  if (str=="JAL") RT_IDEX=Tpc;
}

void ID(){
	string ins =IFID_reg;bool br=false;
	//outfile<<"opcode "<<IFID_reg<<endl;
	//if (ins=="00000000000000000000000000000000") {IDs="NOP";cout<<c_n<<"afgsdgfdgdfgfdg"<<endl;}
//	else
//	{
		string opcode = ins.substr(0, 6);

		if (opcode=="000000"){
			C_IDEX = BtoD(ins.substr(21, 5));
			RT_IDEX = BtoD(ins.substr(11, 5)); 
			RD_IDEX = BtoD(ins.substr(16, 5));
			RS_IDEX = BtoD(ins.substr(6, 5));
			string func = ins.substr(26);
				if (func== "000000") {IDs="SLL";if (RT_IDEX==0&&RD_IDEX==0&&C_IDEX==0)IDs="NOP"; }
				if (func== "000010" ){IDs="SRL";}
				if (func== "000011") {IDs="SRA";}
				if (func== "001000") {IDs="JR" ;ins_IDEX=IDs;br=true;branchHF("JR");}
				if (func== "010000"){IDs="MFHI";}
				if (func== "010010") {IDs="MFLO";}
				if (func== "011000") {IDs="MULT";}
				if (func== "011001") {IDs="MULTU";}
				if (func== "100000"){ IDs="ADD";}
				if (func== "100001") {IDs="ADDU";}
				if (func== "100010") {IDs="SUB";}
				if (func== "100100") {IDs="AND";}
				if (func== "100101") {IDs="OR";}
				if (func== "100110"){ IDs="XOR";}
				if (func== "100111"){ IDs="NOR";}
				if (func== "101000") {IDs="NAND";}
				if (func== "101010") {IDs="SLT";}
		}
		if (opcode.substr(0,5)=="00001"){
			C_IDEX = BtoD(ins.substr(6));
			if (opcode=="000010"){IDs="J" ;jumpFL("J");}
			if (opcode=="000011"){IDs="JAL";jumpFL("JAL");}
		}
		
		if (opcode=="000100"){IDs="BEQ" ;ins_IDEX=IDs;br=true;RType(); branchHF("BEQ");}
		if (opcode=="000101"){IDs="BNE" ;ins_IDEX=IDs;br=true;RType();  branchHF("BNE");}
		if (opcode=="000111"){IDs="BGTZ" ;ins_IDEX=IDs;br=true;RType();  branchHF("BGTZ");}
		if (opcode=="001000"){IDs="ADDI" ;RType(); }
		if (opcode=="001001"){IDs="ADDIU" ;RType(); }
		if (opcode=="001010"){IDs="SLTI" ;RType(); }
		if (opcode=="001100"){IDs="ANDI" ;RTypeU(); }
		if (opcode=="001101"){IDs="ORI" ;RTypeU(); }
		if (opcode=="001110"){IDs="NORI" ;RTypeU(); }
		if (opcode=="001111"){IDs="LUI" ;RTypeU(); }
		if (opcode=="100000"){IDs="LB" ;RType(); }
		if (opcode=="100001"){IDs="LH" ;RType(); }
		if (opcode=="100011"){IDs="LW" ;RType(); }
		if (opcode=="100100"){IDs="LBU" ;RType(); }
		if (opcode=="100101"){IDs="LHU" ;RType(); }
		if (opcode=="101000"){IDs="SB" ;RType(); }
		if (opcode=="101001"){IDs="SH" ;RType(); }
		if (opcode=="101011"){IDs="SW" ;RType(); }
		if (opcode=="111111"){IDs="HALT" ;}
		
//	}
 if (!br)ins_IDEX=IDs;
 
 
	harzardDetectID(IDs);
	
	if (stall_ID) {IDs=IDs+" to_be_stalled";ins_IDEX="NOP";}
	
	
}
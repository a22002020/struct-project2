#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
#include<sstream>

using namespace std;
string ins_EXMEM,targetType_EXMEM;
unsigned int result_EXMEM,target_EXMEM;

string to_string(int n)

{
ostringstream stream;
stream<<n;
return stream.str();
}

void harzardDetect(string str){
	string tEXs=EXs;
		if (str=="ADD"||str=="ADDU"||str=="SUB"||str=="AND"||str=="OR"||str=="XOR"||str=="NOR"||str=="NAND"||str=="SLT"||str=="MULT"||str=="MULTU"||str=="SW"||str=="SH"||str=="SB"){
			Tresrt=Tres[RT_IDEX];
			Tresrd=Tres[RD_IDEX];
			Tresrs=Tres[RS_IDEX];
			if (targetReg==RS_IDEX &&RS_IDEX!=0  &&tGT!="MEM"/*&&tGT=="LRT"*/){
			//	cout<<c_n+1<<endl;
				Tresrs=content;tEXs=EXs+" fwd_DM-WB_rs_$"+to_string(RS_IDEX);
			}		
			if (target_EXMEM==RS_IDEX&&RS_IDEX!=0&&targetType_EXMEM!="MEM")	{
				if (targetType_EXMEM=="LRT"){}
				else {Tresrs=result_EXMEM;tEXs=EXs+" fwd_EX-DM_rs_$"+to_string(RS_IDEX);}
			}
			EXs=tEXs;
			if (targetReg==RT_IDEX&&RT_IDEX!=0 &&tGT!="MEM"/*&&tGT=="LRT"*/){
				Tresrt=content;tEXs=EXs+" fwd_DM-WB_rt_$"+to_string(RT_IDEX);
			}		
			if (target_EXMEM==RT_IDEX&&RT_IDEX!=0&&targetType_EXMEM!="MEM")	{
				if (targetType_EXMEM=="LRT"){}
				else {Tresrt=result_EXMEM;tEXs=EXs+" fwd_EX-DM_rt_$"+to_string(RT_IDEX);}
			}	
			EXs=tEXs;
			}
		if (
		str=="ADDI"||str=="ADDIU"||str=="LW"||str=="LH"||str=="LHU"||str=="LB"
		||str=="LBU"||str=="ANDI"||str=="ORI"
		||str=="NORI"||str=="SLTI"){
			Tresrs=Tres[RS_IDEX];
			if (targetReg==RS_IDEX&&RS_IDEX!=0 &&tGT!="MEM"/* &&tGT=="LRT"*/){
				Tresrs=content;tEXs=EXs+" fwd_DM-WB_rs_$"+to_string(RS_IDEX);
			}		
			if (target_EXMEM==RS_IDEX&&RS_IDEX!=0&&targetType_EXMEM!="MEM")	{
				if (targetType_EXMEM=="LRT"){}
				else {//cout<<c_n+1<<endl;
					Tresrs=result_EXMEM;tEXs=EXs+" fwd_EX-DM_rs_$"+to_string(RS_IDEX);}
			}
			EXs=tEXs;
		}
		if (str=="SLL"||str=="SRL"||str=="SRA"){
   Tresrt=Tres[RT_IDEX];
			if (targetReg==RT_IDEX&&RT_IDEX!=0 &&tGT!="MEM"/*&&tGT=="LRT"*/){
				Tresrt=content;tEXs=EXs+" fwd_DM-WB_rt_$"+to_string(RT_IDEX);
			}		
			if (target_EXMEM==RT_IDEX&&RT_IDEX!=0&&targetType_EXMEM!="MEM")	{
				if (targetType_EXMEM=="LRT"){}
				else {Tresrt=result_EXMEM;tEXs=EXs+" fwd_EX-DM_rt_$"+to_string(RT_IDEX);}
			}	
			EXs=tEXs;
		}
		
		
}
	
	




void EX(){
	string insEX=ins_IDEX;
	EXs=insEX;
	harzardDetect(insEX);
	int rs=RS_IDEX, rt=RT_IDEX,rd=RD_IDEX,C=C_IDEX;
	result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";
	//cout<<c_n+1<<":"<<rt<<" "<<Tresrt<<" "<<C<<endl;
	if (insEX=="SLL"){result_EXMEM=Tresrt << C;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="SRL"){result_EXMEM=Tresrt >> C;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="SRA"){result_EXMEM=(int) Tresrt >> C;target_EXMEM=rd;targetType_EXMEM="RD";  }
	if (insEX=="JR"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="MFHI"){ multy_deal = false;result_EXMEM=THi;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="MFLO"){multy_deal = false;result_EXMEM=TLo;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="MULT"){if (multy_deal)errorfile << "In cycle " << c_n+1 << ": Overwrite HI-LO registers" << endl; multy_deal = true;unsigned long re = (long)(int)Tresrs *(long) (int)Tresrt; THi = re / 0x100000000; TLo = re % 0x100000000; result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="MULTU"){if (multy_deal)errorfile << "In cycle " << c_n+1 << ": Overwrite HI-LO registers" << endl; multy_deal = true;unsigned long re = (unsigned long)Tresrs * (unsigned long) Tresrt;  THi = re / 0x100000000; TLo = re % 0x100000000;result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="ADD"){long re = (long)(int)Tresrs + (long)(int)Tresrt;if (re>2147483647||re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;result_EXMEM= (unsigned int)((int)Tresrs + (int)Tresrt);target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="ADDU"){result_EXMEM=Tresrs + Tresrt;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="SUB"){unsigned int re =(unsigned int)((int)Tresrs - (int)Tresrt); int rss,rts,rees;if (Tresrs>0x7FFFFFFF) rss=1;else rss=0;if (Tresrt>0x80000000) rts=0;else rts=1;if (re>0x7FFFFFFF) rees=1;else rees=0; 
  //cout<<rss<<" "<<rts<<" "<<rees;
					if ((rss==0&&rts==0&&rees==1)||(rss==1&&rts==1&&rees==0))errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; result_EXMEM = (unsigned int)((int)Tresrs - (int)Tresrt);target_EXMEM=rd;targetType_EXMEM="RD"; }
	if (insEX=="AND"){result_EXMEM= Tresrs & Tresrt;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="OR"){result_EXMEM= Tresrs | Tresrt;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="XOR"){result_EXMEM= Tresrs ^ Tresrt;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="NOR"){result_EXMEM= ~(Tresrs | Tresrt);target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="NAND"){result_EXMEM= ~(Tresrs & Tresrt);target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="SLT"){result_EXMEM=(int)Tresrs < (int)Tresrt;target_EXMEM=rd;targetType_EXMEM="RD";}
	if (insEX=="J"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="JAL"){result_EXMEM = rt;target_EXMEM=31;targetType_EXMEM="31";}//??
	if (insEX=="BEQ"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="BNE"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="BGTZ"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}
	if (insEX=="ADDI"){long re = ((long)(int)Tresrs + (long)(int)C); if (re>2147483647 || re<intmin){	errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; }
						result_EXMEM= (int)Tresrs + (int)C;target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="ADDIU"){result_EXMEM=Tresrs + (unsigned int)C;target_EXMEM=rt;targetType_EXMEM="RT"; }
	if (insEX=="SLTI"){result_EXMEM=( (int)Tresrs) < C;target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="ANDI"){result_EXMEM=Tresrs & C;target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="ORI"){result_EXMEM=Tresrs | C;target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="NORI"){result_EXMEM=~(Tresrs | C);target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="LUI"){result_EXMEM=C<<16;target_EXMEM=rt;targetType_EXMEM="RT";}
	if (insEX=="LB"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)addrt > 1023||addrt <0) { mem_AO=true; } 
			else if(!go_halt){result_EXMEM=addr;target_EXMEM=rt;targetType_EXMEM="LRT";}
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;
			}
	if (insEX=="LH"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)(addrt + 1) > 1023||addrt <0) { mem_AO=true; }  
			if (addrt % 2 != 0) { mem_ME=true;} else if(!go_halt){result_EXMEM=addr;target_EXMEM=rt;targetType_EXMEM="LRT"; }
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;
			}
	if (insEX=="LW"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)(addrt + 3) > 1023||addrt <0) { mem_AO=true; }  
			if (addrt % 4 != 0) { mem_ME=true;} else if(!go_halt){result_EXMEM=addr;target_EXMEM=rt;targetType_EXMEM="LRT";}
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;
			}
	if (insEX=="LBU"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)addrt > 1023||addrt <0) { mem_AO=true; } else if(!go_halt){ result_EXMEM=addr;target_EXMEM=rt;targetType_EXMEM="LRT";}
			 long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; 
			}
	if (insEX=="LHU"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)(addrt + 1) > 1023||addrt <0) { mem_AO=true; } 
			if (addrt % 2 != 0) { mem_ME=true;} else if(!go_halt){result_EXMEM=addr;target_EXMEM=rt;targetType_EXMEM="LRT";}
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; 
		}
	if (insEX=="SB"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)addrt > 1023||addrt <0) { mem_AO=true; } else if(!go_halt){result_EXMEM=addr;target_EXMEM=Tresrt;targetType_EXMEM="MEM";}
				long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; 
				}
	if (insEX=="SH"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)(addrt + 1) > 1023||addrt <0) { mem_AO=true; }  
			if (addrt % 2 != 0) { mem_ME=true;} else if(!go_halt){result_EXMEM=addr;target_EXMEM=Tresrt;targetType_EXMEM="MEM";}
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl; 
	}
	if (insEX=="SW"){int addrt =(int) Tresrs +(int) C;long addr=addrt+8;
			if ((unsigned long)(addrt + 3) > 1023||addrt <0) { mem_AO=true; }  if(!go_halt){result_EXMEM=addr;target_EXMEM=Tresrt;targetType_EXMEM="MEM";}
      if (addrt % 4 != 0) {mem_ME=true; } else  if(!go_halt){result_EXMEM=addr;target_EXMEM=Tresrt;targetType_EXMEM="MEM";}
			long re = (long)(int)Tresrs + (long)(int)C; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_n+1 << ": Number Overflow" << endl;
	}
	if (insEX=="HALT"){result_EXMEM=0;target_EXMEM=100;targetType_EXMEM="NOP";}

	ins_EXMEM=insEX;
	//cout<<c_n+1<<":"<<ins_EXMEM<<" "<<result_EXMEM<<" "<<targetType_EXMEM<<endl;



}





	

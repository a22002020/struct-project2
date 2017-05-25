//--------------------------------------ins----------------------------
#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
bool multy_deal = false;	bool go_halt = false;unsigned int TLo = Lo,THi = Hi,Tpc = pc,Tres[100];
void deal_ins(unsigned int num,int c_num) {
	string ins ;
  if(((int)num-(int)moto_pc)>=0)ins=instucts[(num-moto_pc)/4 + 2];else ins="00000000000000000000000000000000";
  cout<<DtoH(BtoD(ins))<<endl;
//cout<<"cycle "<<c_num <<" " <<ins<<endl;
	
	for (int i = 0; i < 32; i++) Tres[i] = res[i];
 //cout<<c_num<<"  "<<(int)Tres[17] <<" "<<endl;
	Tpc += 4;
	string opcode = ins.substr(0, 6);
	if (opcode == "000000") {
		string func = ins.substr(26);
		
		/*00sll*/if (func == "000000") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0&& !(rd==0&&C==0&&rt==0)) errorfile << "In cycle "<<c_num<<": Write $0 Error" << endl;else  Tres[rd] = finalContent_MEMBW << C; }
		/*02srl*/if (func == "000010") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;
     else Tres[rd] = finalContent_MEMBW >> C; }
		/*03sra*/if (func == "000011") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; 
    else { Tres[rd] =(int) finalContent_MEMBW >> C; } }
		/*08jr*/if (func == "001000") { int rs = BtoD(ins.substr(6, 5)); Tpc = Tres[rs];}
		/*10mfhi*/if (func == "010000") { multy_deal = false; int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = THi; }
		/*12mflo*/if (func == "010010") { multy_deal = false; int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = TLo; }
		/*18mult*/if (func == "011000") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5));  unsigned long re = (long)(int)Tres[rs] *(long) (int)finalContent_MEMBW; THi = re / 0x100000000; TLo = re % 0x100000000; } }
		/*19multu*/if (func == "011001") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned long re = (unsigned long)Tres[rs] * (unsigned long) finalContent_MEMBW;  THi = re / 0x100000000; TLo = re % 0x100000000; }}
		/*20add*/if (func == "100000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { 
			long re = (long)(int)Tres[rs] + (long)(int)finalContent_MEMBW;
			if (re>2147483647||re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; 
			Tres[rd] = (unsigned int)((int)Tres[rs] + (int)finalContent_MEMBW); } }
	    /*21addu*/if (func == "100001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] + finalContent_MEMBW;}
	/*22sub*/if (func == "100010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;
	{ unsigned int re =(unsigned int)((int)Tres[rs] - (int)finalContent_MEMBW); int rss,rts,rees;if (Tres[rs]>0x7FFFFFFF) rss=1;else rss=0;if (finalContent_MEMBW>0x80000000) rts=0;else rts=1;if (re>0x7FFFFFFF) rees=1;else rees=0; 
  //cout<<rss<<" "<<rts<<" "<<rees;
	if ((rss==0&&rts==0&&rees==1)||(rss==1&&rts==1&&rees==0))errorfile << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rd] = (unsigned int)((int)Tres[rs] - (int)finalContent_MEMBW); } }
		/*24and*/if (func == "100100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] & finalContent_MEMBW; }
		/*25or*/if (func == "100101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] | finalContent_MEMBW; }
		/*26xor*/if (func == "100110") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] ^ finalContent_MEMBW; }
		/*27nor*/if (func == "100111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = ~(Tres[rs] | finalContent_MEMBW); }
		/*28nand*/if (func == "101000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = ~(Tres[rs] & finalContent_MEMBW); }
		/*2Aslt*/if (func == "101010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = (int)Tres[rs] < (int)finalContent_MEMBW; }
	}


	/*02j*/if (opcode == "000010") { int add = BtoD(ins.substr(6)); Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*03jal*/if (opcode == "000011") { int add = BtoD(ins.substr(6)); Tres[31] = Tpc; Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*04beq*/if (opcode == "000100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if (Tres[rs] == finalContent_MEMBW)Tpc += 4 * imm; }
	/*05bne*/if (opcode == "000101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if (Tres[rs] != finalContent_MEMBW)Tpc += 4 * imm; }
	/*07bgtz*/if (opcode == "000111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if ((int)Tres[rs]>0)Tpc += 4 * imm; }
	/*08addi*/if (opcode == "001000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); 
	if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  {
		long re = ((long)(int)Tres[rs] + (long)(int)imm); 
		if (re>2147483647 || re<intmin)
		{	errorfile << "In cycle " << c_num << ": Number Overflow" << endl; }
		finalContent_MEMBW = (int)Tres[rs] + (int)imm; } }
	/*09addiu*/if (opcode == "001001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16));  if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  finalContent_MEMBW = Tres[rs] + (unsigned int)imm; }
	/*0Aslti*/if (opcode == "001010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;   finalContent_MEMBW =( (int)Tres[rs]) < imm;}
	/*0Candi*/if (opcode == "001100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  finalContent_MEMBW = Tres[rs] & imm;}
	/*0Dori*/if (opcode == "001101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  finalContent_MEMBW = Tres[rs] | imm; }
	/*0Enori*/if (opcode == "001110") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  finalContent_MEMBW =~( Tres[rs] | imm); }
	/*0Flui*/if (opcode == "001111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  finalContent_MEMBW = imm<<16; }
	/*20lb*/if (opcode == "100000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)addrt > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if(!go_halt){ finalContent_MEMBW = HtoD(addr, 1, false); if (finalContent_MEMBW >= 128) finalContent_MEMBW = finalContent_MEMBW | 0xFFFFFF00; } } }
	/*21lh*/if (opcode == "100001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if ((unsigned long)(addrt + 1) > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if (addrt % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else if(!go_halt){ finalContent_MEMBW = HtoD(addr, 2, false); if (finalContent_MEMBW > 32767) finalContent_MEMBW = finalContent_MEMBW | 0xFFFF0000; } } }
	/*23lw*/if (opcode == "100011") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)(addrt + 3) > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if (addrt % 4 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else if(!go_halt)finalContent_MEMBW = HtoD(addr, 4, false); } }
	/*24lbu*/if (opcode == "100100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)addrt > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if(!go_halt)finalContent_MEMBW = HtoD(addr, 1, false); } }
	/*25lhu*/if (opcode == "100101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)(addrt + 1) > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if (addrt % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else if(!go_halt)finalContent_MEMBW = HtoD(addr, 2, false); } }
	/*28sb*/if (opcode == "101000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)addrt > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if(!go_halt){ save(addr, 1,( finalContent_MEMBW & 0x000000FF)); // cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3];
  }}
  }
	/*29sh*/if (opcode == "101001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)(addrt + 1) > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if (addrt % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else if(!go_halt){ save(addr, 2,( finalContent_MEMBW & 0x0000FFFF));
  //cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3];
   }}}
	/*2Bswv */if (opcode == "101011") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); int addrt =(int) Tres[rs] +(int) imm;long addr=addrt+8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned long)(addrt + 3) > 1023||addrt <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if (addrt % 4 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else  if(!go_halt){save(addr, 4, finalContent_MEMBW);
  //cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3]; 
  }}
   }


Tres[0]=0;
if (opcode == "111111" || go_halt) { 
		go_halt = true; return; }

	
	if (outfile.is_open()) {
	outfile << "cycle "<<c_num << endl;
	for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl;  }
	if (THi != Hi) { Hi = THi; outfile << "$HI: " << DtoH(Hi) << endl;  }
	if (TLo != Lo) { Lo = TLo; outfile << "$LO: " << DtoH(Lo) << endl; }
	if (Tpc != pc) { pc = Tpc; outfile << "PC: " << DtoH(pc) << endl;  }
	outfile << endl;
	outfile << endl;
	
	}


	

}

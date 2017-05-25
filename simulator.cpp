
#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
string instucts[50000];
unsigned int datas[50000];
int ins_num,data_num;
unsigned char buffer[50000];
long gay =0x80000000;
long intmin = -1*gay;



ofstream outfile("snapshot.rpt");
ofstream errorfile("error_dump.rpt");

unsigned int BtoD(string st) {
	int result = 0, ratio = 1;
	for (int i = st.length()-1; i >= 0; i--) {
		result += ratio*(st[i] - 48);
		ratio *= 2;
	}
	return result;
}
int BtoDs(string st) {
	int result = 0, ratio = 1;
	string s = st.substr(1);
	if (st[0] == '1')  for (int i = 0; i < s.length(); i++) if (s[i] == '0') s[i] = '1'; else s[i] = '0';
	result = BtoD(s);
	if (st[0]== '1') result = -1 * (result+1);
	return result;
}
void HtoB(int i, int j, int num) {
	unsigned short chr = (unsigned short)buffer[num];
	int kara = j * 8, made = (j + 1) * 8 - 1;
	if (chr != 0) 
		chr = chr;
	for (int ii = made; ii >= kara; ii--) {
		int out = chr % 2;
		instucts[i][ii] = out + '0';
		chr = chr / 2;
	}
}

string DtoH(unsigned int number) {
	string result="00000000";
	unsigned int temp=number;
	for (int i = 7; i >= 0; i--) {
		int k = temp % 16;
		if (k < 10) result[i] = k + '0'; else result[i] = k - 10 + 'A';
		temp /= 16;
	}
	return "0x" + result;
}
unsigned int HtoD(int n,int byt_num,bool isInit) {
	int kara; if (isInit)kara = n * byt_num; else kara = n;
	int made = kara + byt_num-1;
	unsigned int ratio = 1;
	unsigned int result = 0;
 //cout<<"load"<<c_n<<endl;
	for (int i = made; i >= kara; i--) {
   // cout<<(int)buffer[i]<<" ";
		result += buffer[i] * ratio;
		ratio *= 256;
	}
  //cout<<endl;
	return result;
}

void save(int addr, int byt_num,unsigned int input) {
	int kara = addr; int made = kara + byt_num - 1;
	unsigned int inn = input;
	for (int i = made; i >= kara; i--) {
		buffer[i] = input % 256;
		input /= 256;

	}


}

void input() {
	ifstream fin;
	fin.open("iimage.bin", ios::binary);
	if (!fin) {
		cout << "open error!" << endl;
	}
	//char buffer[5000];
	int len = 0;
	while (!fin.eof()/* && fin.peek() != EOF*/) {
		char tt;
		fin.get(tt); buffer[len] = (unsigned char)tt;
		len++;
	}
	buffer[len] = EOF; len++;
	//fin.read(buffer, 3073 * sizeof(char));
	ins_num = len / 4;
	int temp=0;
	for (int i = 0; i < ins_num; i++) {
		instucts[i] = "00000000000000000000000000000000";  
		for (int j = 0; j < 4; j++) {
			HtoB(i, j, temp);
			temp++;
		}
	}
	//for (int i = 0; i < ins_num; i++) cout << instucts[i]<< endl;
	ifstream fin2;
	fin2.open("dimage.bin", ios::binary);
	if (!fin2) {
		cout << "open error!" << endl;
	}

	len = 0;
	while (!fin2.eof()/* && fin.peek() != EOF*/) {
		char tt;
		fin2.get(tt); buffer[len] = (unsigned char)tt;
		len++;
	}
	buffer[len] = EOF; len++;
	//fin.read(buffer, 3073 * sizeof(char));
	data_num = len / 4;
	temp = 0;
	for (int i = 0; i < data_num; i++) {
		datas[i] = HtoD(i,4,true);
		
	}
 	for (int i=data_num*4;i<50000;i++)buffer[i]=(unsigned char)0;
	//for (int i = 0; i < data_num; i++) cout <<(int)buffer[16+i]<< endl;

}








bool go_halt = false,multy_deal = false,stall_ID=false,TBflush=false;int jumpC=0;
bool mem_AO=false,mem_ME=false,mem_NO=false;
int c_n = 0;
//---------------------------------------------------------------------
int main()
{
	//cout<<gay<<" "<<intmin<<endl;
	input();
	Res_init();
	int inum = BtoD(instucts[1]);
 ins_num=inum+2;
	TLo = Lo;THi = Hi;Tpc = pc;for (int i = 0; i < 32; i++) Tres[i] = res[i];
	while (
  ((int)pc -(int) moto_pc) / 4 < ins_num&&
  !go_halt&&!(IFs=="0xFFFFFFFF"&&IDs=="HALT"&&EXs=="HALT"&&MEMs=="HALT"&&WBs=="HALT")) {
		//cout<<"r17:"<<Tres[17]<<endl;
			if (outfile.is_open()) {
				if (c_n>0)outfile << "cycle "<<c_n << endl;
				for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl;  }
				if (THi != Hi) { Hi = THi; outfile << "$HI: " << DtoH(Hi) << endl;  }
				if (TLo != Lo) { Lo = TLo; outfile << "$LO: " << DtoH(Lo) << endl; }
				 { pc = Tpc; outfile << "PC: " << DtoH(pc) << endl;  }
			}
		
		stall_ID=false;
		TBflush=false;jumpC=0;
		WB(c_n);MEM();EX();ID();IF();output();
		//deal_ins(pc, c_n);
		c_n++;
		//TLo = Lo;THi = Hi;Tpc = pc;for (int i = 0; i < 32; i++) Tres[i] = res[i];
	}
 
 /*
 if (go_halt){
   if (outfile.is_open()) {
				if (c_n>0)outfile << "cycle "<<c_n << endl;
				for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl;  }
				if (THi != Hi) { Hi = THi; outfile << "$HI: " << DtoH(Hi) << endl;  }
				if (TLo != Lo) { Lo = TLo; outfile << "$LO: " << DtoH(Lo) << endl; }
				 { pc = Tpc; outfile << "PC: " << DtoH(pc) << endl;  }
			}	stall_ID=false;
		TBflush=false;jumpC=0;
		WB(c_n);MEM();EX();ID();IF();output();
 }*/
	outfile.close();
	errorfile.close();
    return 0;
}


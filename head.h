#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void Res_init();
void deal_ins(unsigned int num,int c_num);
extern string instucts[50000];
extern unsigned int datas[50000];
extern int ins_num,data_num,c_n;
extern unsigned char buffer[50000];
extern unsigned int res[32], Lo, Hi, pc,moto_pc;
extern long intmin;
extern ofstream outfile;
extern ofstream errorfile;
extern unsigned int Tres[100],TLo, THi,Tpc;
extern int jumpC;
extern string IFs,IDs,EXs,WBs,MEMs,IFID_reg;
extern	bool go_halt,multy_deal,stall_ID,TBflush;
extern string ins_IDEX;
extern int RS_IDEX,RT_IDEX,RD_IDEX,C_IDEX;
extern string ins_EXMEM,targetType_EXMEM,ins_MEMWB,targetType_MEMWB;
extern unsigned int result_EXMEM,target_EXMEM,finalContent_MEMWB,target_MEMWB,Tresrt,Tresrd,Tresrs;

extern string tGT;
extern unsigned int content,targetReg;
extern bool mem_AO,mem_ME,mem_NO;
unsigned int BtoD(string st);
int BtoDs(string st);
void HtoB(int i, int j, int num);
string DtoH(unsigned int number);
unsigned int HtoD(int n,int byt_num,bool isInit);
void save(int addr, int byt_num,unsigned int input);
void IF();
void ID();
void EX();
void MEM();
void WB(int c);
void output();
string to_string(int n);

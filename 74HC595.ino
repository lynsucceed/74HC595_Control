/*****************************************************
 * IO口扩展（串进并出）
 * 说明：74HC595 右移移位寄存器 先送MSB，再送LSB，从Q7—Q0
 * 引脚：q0-q7依次接数码管的a—hp
 * 效果：数码管依次显示0到9,再从9到0
 * Copyright (c) 2017 lynsucceed
 * Email: lynsucceed@gmail.com 
********************************************************/
int DS = 9;
int OE = 10; //gnd
int ST_CP = 11;
int SH_CP = 12;
int MR = 13; //vcc

void function(int DS,int SH_CP,int dat)
{
 digitalWrite(SH_CP,LOW); 
 digitalWrite(DS,dat);
 digitalWrite(SH_CP,HIGH);
}

void SMGdisplay( byte m)  
{
  int i=1;
  for( int j=1;j<=8;j++)   
  {
    function(DS,SH_CP,m&i);  
    i<<=1;
  }
}

void shift_bin( byte bin) //bin order 
{
  int i=0x80;
  for( int j=1;j<=8;j++)  
  {
    function(DS,SH_CP,bin&i);
    i>>=1;
  }
}

void setup() {
  // put your setup code here, to run once:
 pinMode(DS,OUTPUT);
 pinMode(OE,OUTPUT);
 pinMode(ST_CP,OUTPUT);
 pinMode(SH_CP,OUTPUT);
 pinMode(MR,OUTPUT);
 digitalWrite(MR,HIGH); // 高电平不复位
 digitalWrite(OE,LOW);  //低电平使能，移位寄存器输出
}

void loop() {
  // put your main code here, to run repeatedly:
int k = 0, t = 0;
int play[10]={0x03,0x9e,0x25,0x0c,0x99,0x48,0x41,0x1e,0x01,0x08}; // play:0 to 9
int bin[10]= {0x10,0x80,0x78,0x82,0x12,0x99,0x30,0xa4,0x79,0xc0}; // play:9 to 0

for(int s=1;s<=10;s++)
 {
  digitalWrite(ST_CP,LOW);
  SMGdisplay(play[k]);
  digitalWrite(ST_CP,HIGH);
  k++;
  delay(1000);
 }

for(int s=1;s<=10;s++)
 {
  digitalWrite(ST_CP,LOW);
  shift_bin(bin[t]);
  digitalWrite(ST_CP,HIGH);
  t++;
  delay(1000);
 }
}

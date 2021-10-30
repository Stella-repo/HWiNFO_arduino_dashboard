//first git test 
#include <U8glib.h>
#include <I2CMux.h>
#include <Wire.h>

#define I2CMulti_Addr 0x70

I2CMux I2CMulti(I2CMulti_Addr);

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);

int cpu_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int gpu_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int gpu_enc_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int srlength,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26;
String sr;
char ddr_red_unit[2],ddr_wrt_unit[2],cdr_red_unit[2],cdr_wrt_unit[2],int_upr_unit[2],int_dlr_unit[2];
int cpu_usg,cpu_tmp,t_sen,gpu_usg,gpu_enc,mem_lod,cpu_fan,fnt_fan,ddr_act,cdr_act,gpu_tmp,gpu_fan,cdr_abl,ddr_abl;
float mem_abl,ddr_red,ddr_wrt,cdr_red,cdr_wrt,int_upr,int_dlr;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  u8g.setFont(u8g_font_helvB08r);
  for (int i = 0; i < 6; i++)
  {     
    u8g.firstPage();
    do {
    I2CMulti.switchToBus(i);
    u8g.begin();
    u8g.drawStr(6,37,"Waiting HWiNFO Data..");
    }while( u8g.nextPage() );
  }
}

void loop() 
{
  if(Serial.available())
  {
    sr = Serial.readStringUntil('>'); 

    a1 = sr.indexOf("/");
    a2 = sr.indexOf("/", a1+1);
    a3 = sr.indexOf("/", a2+1);
    a4 = sr.indexOf("/", a3+1);
    a5 = sr.indexOf("/", a4+1);
    a6 = sr.indexOf("/", a5+1);
    a7 = sr.indexOf("/", a6+1);
    a8 = sr.indexOf("/", a7+1);
    a9 = sr.indexOf("/", a8+1);
    a10 = sr.indexOf("/", a9+1);
    a11 = sr.indexOf("/", a10+1);
    a12 = sr.indexOf("/", a11+1);
    a13 = sr.indexOf("/", a12+1);
    a14 = sr.indexOf("/", a13+1);
    a15 = sr.indexOf("/", a14+1);
    a16 = sr.indexOf("/", a15+1);
    a17 = sr.indexOf("/", a16+1);
    a18 = sr.indexOf("/", a17+1);
    a19 = sr.indexOf("/", a18+1);
    a20 = sr.indexOf("/", a19+1);
    a21 = sr.indexOf("/", a20+1);
    a22 = sr.indexOf("/", a21+1);
    a23 = sr.indexOf("/", a22+1);
    a24 = sr.indexOf("/", a23+1);
    a25 = sr.indexOf("/", a24+1);
    a26 = sr.indexOf("/", a25+1);

    srlength = sr.length();

    mem_abl = (sr.substring(0, a1)).toFloat();
    mem_lod = (sr.substring(a1+1, a2)).toInt();
    cpu_usg = (sr.substring(a2+1, a3)).toInt();
    cpu_tmp = (sr.substring(a3+1, a4)).toInt();
    cpu_fan = (sr.substring(a4+1, a5)).toInt();
    fnt_fan = (sr.substring(a5+1, a6)).toInt();
    t_sen = (sr.substring(a6+1, a7)).toInt();
    ddr_act = (sr.substring(a7+1, a8)).toInt();
    ddr_red = (sr.substring(a8+1, a9)).toFloat();
    ddr_wrt = (sr.substring(a9+1, a10)).toFloat();
    (sr.substring(a10+1, a11)).toCharArray(ddr_red_unit,2);
    (sr.substring(a11+1, a12)).toCharArray(ddr_wrt_unit,2);
    cdr_act = (sr.substring(a12+1, a13)).toInt();
    cdr_red = (sr.substring(a13+1, a14)).toFloat();
    cdr_wrt = (sr.substring(a14+1, a15)).toFloat();
    (sr.substring(a15+1, a16)).toCharArray(cdr_red_unit,2);
    (sr.substring(a16+1, a17)).toCharArray(cdr_wrt_unit,2);
    gpu_tmp = (sr.substring(a17+1, a18)).toInt();
    gpu_fan = (sr.substring(a18+1, a19)).toInt();
    gpu_usg = (sr.substring(a19+1, a20)).toInt();
    gpu_enc = (sr.substring(a20+1, a21)).toInt();
    int_upr = (sr.substring(a21+1, a22)).toFloat();
    int_dlr = (sr.substring(a22+1, a23)).toFloat();
    (sr.substring(a23+1, a24)).toCharArray(int_upr_unit,2);
    (sr.substring(a24+1, a25)).toCharArray(int_dlr_unit,2);
    cdr_abl = (sr.substring(a25+1, a26)).toInt();
    ddr_abl = (sr.substring(a26+1, srlength)).toInt();


    for (int i = 0; i < 59; i++)
    {
      cpu_log[i] = cpu_log[i+1];
      gpu_log[i] = gpu_log[i+1];
      gpu_enc_log[i] = gpu_enc_log[i+1];
    }
    cpu_log[59] = cpu_usg;
    gpu_log[59] = gpu_usg;
    gpu_enc_log[59] = gpu_enc;
    

  //CPU
    I2CMulti.switchToBus(0);
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_helvB08r);
      u8g.drawStr(0,8,"CPU");
      u8g.drawStr(53,36,"%");
      u8g.drawStr(21,48,"'C");
      u8g.drawStr(53,48 ,"'C");

      //cpu_usg
      u8g.setFont(u8g_font_helvB24r);
      if (cpu_usg < 10){
        u8g.setPrintPos(32, 36);
        u8g.print(cpu_usg);}
      else if (cpu_usg < 100){
        u8g.setPrintPos(14, 36);
        u8g.print(cpu_usg);}
      else{
        u8g.drawStr(0,36,"1");
        u8g.drawStr(14,36,"00");}

      //cpu_tmp
      u8g.setFont(u8g_font_helvB18r);
      u8g.setPrintPos(0, 64);
      u8g.print(cpu_tmp);
      
      //t_sen
      u8g.setPrintPos(33, 64);
      u8g.print(t_sen);

      //graph
      u8g.drawLine(64,0,128,0);
      u8g.drawLine(64,1,128,1);
      u8g.drawLine(64,0,64,64);
      u8g.drawLine(65,0,65,64);
      u8g.drawLine(126,0,126,64);
      u8g.drawLine(127,0,127,64);
      u8g.drawLine(64,62,128,62);
      u8g.drawLine(64,63,128,63);
      for (int i = 0; i < 60; i++)
      {
        if (map(cpu_log[59-i],0,100,0,60) < 1)
          {u8g.drawLine(125-i,61,125-i,60);}
        else
          {u8g.drawLine(125-i,61,125-i,61-map(cpu_log[59-i],0,100,0,60));}
      }
    }
    while(u8g.nextPage());

  //GPU
    I2CMulti.switchToBus(1);
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_helvB08r);
      u8g.drawStr(0,8,"GPU");
      u8g.drawStr(52,36,"%");
      u8g.drawStr(25,48,"%");
      u8g.drawStr(53,48 ,"'C");

      //gpu_usg
      u8g.setFont(u8g_font_helvB24r);
      if (gpu_usg < 10){
        u8g.setPrintPos(32, 36);
        u8g.print(gpu_usg);}
      else if (gpu_usg < 100){
        u8g.setPrintPos(14, 36);
        u8g.print(gpu_usg);}
      else{
        u8g.drawStr(0,36,"1");
        u8g.drawStr(14,36,"00");}
      

      //gpu_tmp
      u8g.setFont(u8g_font_helvB18r);
      u8g.setPrintPos(33, 64);
      u8g.print(gpu_tmp);
      
      //gpu_enc
      if (gpu_enc < 10){
        u8g.setPrintPos(13, 64);
        u8g.print(gpu_enc);}
      else if (gpu_enc < 100){
        u8g.setPrintPos(0, 64);
        u8g.print(gpu_enc);}
      else{
        u8g.drawStr(0,64,"!!!!");}

      //graph
      u8g.drawLine(64,0,128,0);
      u8g.drawLine(64,1,128,1);
      u8g.drawLine(64,0,64,64);
      u8g.drawLine(65,0,65,64);
      u8g.drawLine(126,0,126,64);
      u8g.drawLine(127,0,127,64);
      u8g.drawLine(64,62,128,62);
      u8g.drawLine(64,63,128,63);
      for (int i = 0; i < 60; i++)
      {
        if (map(gpu_log[59-i],0,100,0,60) < 1)
          {u8g.drawLine(125-i,61,125-i,60);}
        else
          {u8g.drawLine(125-i,61-map(gpu_enc_log[59-i],0,100,0,60),125-i,61-map(gpu_log[59-i],0,100,0,60));}
      }
    }
    while(u8g.nextPage());


  //RAM
    I2CMulti.switchToBus(2);
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_helvB08r);
      u8g.drawStr(20,8,"RAM");
      u8g.drawStr(47,34,"%");
      u8g.drawStr(47,59,"G");
      u8g.drawStr(88,8,"DISK");
      u8g.drawStr(120,33,"G");
      u8g.drawStr(120,59,"G");
      
      u8g.setFont(u8g_font_helvB14r);
      u8g.drawStr(59,32,"C:");
      u8g.drawStr(59,57,"D:");
      
      //mem_lod
      u8g.setFont(u8g_font_helvB18r);
      if (mem_lod < 10){
        u8g.setPrintPos(32, 34);
        u8g.print(mem_lod);}
      else if (mem_lod < 100){
        u8g.setPrintPos(20, 34);
        u8g.print(mem_lod);}
      else{
        u8g.drawStr(7,34,"100");}
        
      //mem_abl
      if (mem_abl < 10){
        u8g.setPrintPos(13, 59);
        u8g.print(mem_abl,1);}
      else if (mem_abl < 100){
        u8g.setPrintPos(0, 59);
        u8g.print(mem_abl,1);}

      //cdr_abl
      if (cdr_abl < 10){
        u8g.setPrintPos(107, 34);
        u8g.print(cdr_abl);}
      else if (cdr_abl < 100){
        u8g.setPrintPos(94, 34);
        u8g.print(cdr_abl);}
      else{
        u8g.setPrintPos(81, 34);
        u8g.print(cdr_abl);}

      //ddr_abl
      if (ddr_abl < 10){
        u8g.setPrintPos(107, 59);
        u8g.print(ddr_abl);}
      else if (ddr_abl < 100){
        u8g.setPrintPos(94, 59);
        u8g.print(ddr_abl);}
      else{
        u8g.setPrintPos(81, 59);
        u8g.print(ddr_abl);}
      
    }
    while(u8g.nextPage());


  //DISK
    I2CMulti.switchToBus(3);
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_helvB08r);
      u8g.drawStr(0,8,"DISK");
      u8g.drawStr(0,20,"C:");
      u8g.drawStr(0,47,"D:");
      u8g.drawStr(30,36,"%");
      u8g.drawStr(30,64,"%");
      u8g.drawStr(48,21,"Read");
      u8g.drawStr(92,21,"Write");
      u8g.drawStr(48,49,"Read");
      u8g.drawStr(92,49,"Write");
      
      //units
      u8g.setPrintPos(73, 36);
      u8g.print(cdr_red_unit);
      u8g.setPrintPos(119, 36);
      u8g.print(cdr_wrt_unit);
      u8g.setPrintPos(73, 64);
      u8g.print(ddr_red_unit);
      u8g.setPrintPos(119, 64);
      u8g.print(ddr_wrt_unit);
      
      //cdr_act
      u8g.setFont(u8g_font_helvB14r);
      if (cdr_act < 10){
        u8g.setPrintPos(20, 36);
        u8g.print(cdr_act);}
      else if (cdr_act < 100){
        u8g.setPrintPos(10, 36);
        u8g.print(cdr_act);}
      else{
        u8g.setPrintPos(0, 36);
        u8g.print(cdr_act);}
        
      //cdr_red
      if (cdr_red == 0){
        u8g.setPrintPos(63, 36);
        u8g.print(cdr_red, 0);}
      else if (cdr_red < 10){
        u8g.setPrintPos(48, 36);
        u8g.print(cdr_red, 1);}
      else if (cdr_red < 100){
        u8g.setPrintPos(38, 36);
        u8g.print(cdr_red, 1);}
      else if (cdr_red < 1000){
        u8g.setPrintPos(43, 36);
        u8g.print(cdr_red, 0);}
      else {
        u8g.setPrintPos(38, 36);
        u8g.print(cdr_red, 0);}

      //cdr_wrt
      if (cdr_wrt == 0){
        u8g.setPrintPos(109, 36);
        u8g.print(cdr_wrt, 0);}
      else if (cdr_wrt < 10){
        u8g.setPrintPos(94, 36);
        u8g.print(cdr_wrt, 1);}
      else if (cdr_wrt < 100){
        u8g.setPrintPos(84, 36);
        u8g.print(cdr_wrt, 1);}
      else if (cdr_wrt < 1000){
        u8g.setPrintPos(89, 36);
        u8g.print(cdr_wrt, 0);}
      else {
        u8g.setPrintPos(84, 36);
        u8g.print(cdr_wrt, 0);}
      
      //ddr_act
      if (ddr_act < 10){
        u8g.setPrintPos(20, 64);
        u8g.print(ddr_act);}
      else if (ddr_act < 100){
        u8g.setPrintPos(10, 64);
        u8g.print(ddr_act);}
      else{
        u8g.setPrintPos(0, 64);
        u8g.print(ddr_act);}
      
      //ddr_red
      if (ddr_red == 0){
        u8g.setPrintPos(63, 64);
        u8g.print(ddr_red, 0);}
      else if (ddr_red < 10){
        u8g.setPrintPos(48, 64);
        u8g.print(ddr_red, 1);}
      else if (ddr_red < 100){
        u8g.setPrintPos(38, 64);
        u8g.print(ddr_red, 1);}
      else if (ddr_red < 1000){
        u8g.setPrintPos(43, 64);
        u8g.print(ddr_red, 0);}
      else {
        u8g.setPrintPos(38, 64);
        u8g.print(ddr_red, 0);}

      //ddr_wrt
      if (ddr_wrt == 0){
        u8g.setPrintPos(109, 64);
        u8g.print(ddr_wrt, 0);}
      else if (ddr_wrt < 10){
        u8g.setPrintPos(94, 64);
        u8g.print(ddr_wrt, 1);}
      else if (ddr_wrt < 100){
        u8g.setPrintPos(84, 64);
        u8g.print(ddr_wrt, 1);}
      else if (ddr_wrt < 1000){
        u8g.setPrintPos(89, 64);
        u8g.print(ddr_wrt, 0);}
      else {
        u8g.setPrintPos(84, 64);
        u8g.print(ddr_wrt, 0);}
    }
    while(u8g.nextPage());


    //NET, FAN
    I2CMulti.switchToBus(4);
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_helvB08r);
      u8g.drawStr(20,8,"NET");
      u8g.drawStr(97,8,"FAN");
      u8g.drawStr(0,26,"^");
      u8g.drawStr(1,28,"l");
      u8g.drawStr180(3,46,"^");
      u8g.drawStr(1,53,"l");
      u8g.drawStr(63,26,"CPU");
      u8g.drawStr(63,42,"GPU");
      u8g.drawStr(64,58,"FNT");

      //units
      u8g.setPrintPos(52, 33);
      u8g.print(int_upr_unit);
      u8g.setPrintPos(52, 60);
      u8g.print(int_dlr_unit);

      //int_upr
      u8g.setFont(u8g_font_helvB18r);
      if (int_upr == 0){
        u8g.setPrintPos(39, 33);
        u8g.print(int_upr, 0);}
      else if (int_upr < 10){
        u8g.setPrintPos(19, 33);
        u8g.print(int_upr, 1);}
      else if (int_upr < 100){
        u8g.setPrintPos(6, 33);
        u8g.print(int_upr, 1);}
      else {
        u8g.setPrintPos(13, 33);
        u8g.print(int_upr, 0);}

      //int_dlr
      if (int_dlr == 0){
        u8g.setPrintPos(39, 60);
        u8g.print(int_dlr, 0);}
      else if (int_dlr < 10){
        u8g.setPrintPos(19, 60);
        u8g.print(int_dlr, 1);}
      else if (int_dlr < 100){
        u8g.setPrintPos(6, 60);
        u8g.print(int_dlr, 1);}
      else {
        u8g.setPrintPos(13, 60);
        u8g.print(int_dlr, 0);}

      //cpu_fan
      u8g.setFont(u8g_font_helvB14r);
      if (cpu_fan < 1000){
        u8g.setPrintPos(95, 28);
        u8g.print(cpu_fan);}
      else {
        u8g.setPrintPos(85, 28);
        u8g.print(cpu_fan);}      

      //gpu_fan
      if (gpu_fan == 0){
        u8g.setPrintPos(115, 44);
        u8g.print(gpu_fan);}
      else if (gpu_fan < 1000){
        u8g.setPrintPos(95, 44);
        u8g.print(gpu_fan);}
      else {
        u8g.setPrintPos(85, 44);
        u8g.print(gpu_fan);}     

      //fnt_fan
      if (fnt_fan < 1000){
        u8g.setPrintPos(95, 60);
        u8g.print(fnt_fan);}
      else {
        u8g.setPrintPos(85, 60);
        u8g.print(fnt_fan);}
    }
    while(u8g.nextPage());
  }
}
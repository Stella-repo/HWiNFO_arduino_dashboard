#include <U8glib.h>
#include <I2CMux.h>
#include <Wire.h>

#define I2CMulti_Addr 0x70 //멀티플렉서 주소 지정

I2CMux I2CMulti(I2CMulti_Addr);

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); //oled디스플레이 설정

int cpu_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int gpu_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int gpu_enc_log[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26;
String sr;
char ddr_red_unit[2],ddr_wrt_unit[2],cdr_red_unit[2],cdr_wrt_unit[2],int_upr_unit[2],int_dlr_unit[2];
int cpu_usg,cpu_tmp,t_sen,gpu_usg,gpu_enc,mem_usg,cpu_fan,fnt_fan,ddr_act,cdr_act,gpu_tmp,gpu_fan,cdr_abl,ddr_abl;
float mem_abl,ddr_red,ddr_wrt,cdr_red,cdr_wrt,int_upr,int_dlr;
int status = 1;


void disp() { //저장공간 줄이기용, 그래프 테두리 그리기
  for (int i = 0; i < 16; i++)
  {
    u8g.drawPixel(i*4+68,16);
    u8g.drawPixel(i*4+68,31);
    u8g.drawPixel(i*4+68,46);
  }
  u8g.drawLine(64,0,128,0);
  u8g.drawLine(64,0,64,64);
  u8g.drawLine(127,0,127,64);
  u8g.drawLine(64,63,128,63);
}
void f08() //저장공간 줄이기용..
  {u8g.setFont(u8g_font_helvB08r);}
void f14()
  {u8g.setFont(u8g_font_helvB14r);}
void f18()
  {u8g.setFont(u8g_font_helvB18r);}
void f24()
  {u8g.setFont(u8g_font_helvB24r);}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  f08();
  for (int i = 0; i < 5; i++) //첫페이지 생셩
  { 
    u8g.firstPage();
    do
    {
      I2CMulti.switchToBus(i);
      u8g.begin(); //이거 안해주면 한번씩 화면이 안깨어나는 버그가 있음
      u8g.drawStr(6,37,"Waiting HWiNFO Data..");
    }
    while( u8g.nextPage());
  }
  pinMode(9, INPUT_PULLUP); //oled화면 끄고켜기 버튼
}

void loop() {
  if (status == 0) //status가 0일때
    {if (digitalRead(9) == LOW) //버튼이 눌리면
      {status = 1;}} //status를 1로 변경
  else if (status == 1)
    {if (digitalRead(9) == LOW)
      {status = 0;}}

  if (status == 0) //status가 0이면
  {
    for (int i = 0; i < 5; i++)
    { 
      I2CMulti.switchToBus(i);
      u8g.firstPage();
      do {} //화면출력 아무거도 안하기
      while(u8g.nextPage());
    }
  }

  if (status == 1) //status가 1이고
  {
    if (Serial.available()) //시리얼포트를 통해 문자열이 날라오면 작업시작
    {
      sr = Serial.readStringUntil('>'); //'>'문자 전까지 읽어오기

      a1 = sr.indexOf("/"); //첫번째 '/'위치 찾기
      a2 = sr.indexOf("/", a1+1); //첫번째 '/'위치 뒤로부터 처음으로 나오는 '/'위치찾기
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

      mem_abl = (sr.substring(0, a1)).toFloat(); //맨앞부터 첫번째 '/'앞까지
      mem_usg = (sr.substring(a1+1, a2)).toInt(); //첫번째 '/'건너뛰고 다음부터 두번째 '/'앞까지
      cpu_usg = (sr.substring(a2+1, a3)).toInt(); //Int로 변경
      cpu_tmp = (sr.substring(a3+1, a4)).toInt();
      cpu_fan = (sr.substring(a4+1, a5)).toInt();
      fnt_fan = (sr.substring(a5+1, a6)).toInt();
      t_sen = (sr.substring(a6+1, a7)).toInt();
      ddr_act = (sr.substring(a7+1, a8)).toInt();
      ddr_red = (sr.substring(a8+1, a9)).toFloat(); //Float로 변경
      ddr_wrt = (sr.substring(a9+1, a10)).toFloat();
      (sr.substring(a10+1, a11)).toCharArray(ddr_red_unit,2); //Char로 변경
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
      ddr_abl = (sr.substring(a26+1, sr.length())).toInt();


      for (int i = 0; i < 59; i++) //그래프를 그리기 위해서 로그 값들을 앞으로 하나씩 밀기
      {
        cpu_log[i] = cpu_log[i+1];
        gpu_log[i] = gpu_log[i+1];
        gpu_enc_log[i] = gpu_enc_log[i+1];
      }
      cpu_log[59] = cpu_usg;
      gpu_log[59] = gpu_usg;
      gpu_enc_log[59] = gpu_enc;
      

    //CPU
      I2CMulti.switchToBus(0); //멀티플렉서의 0번 채널로 전환
      u8g.firstPage();
      do {
        f08(); //폰트크기 8로 변경
        u8g.drawStr(0,8,"CPU");
        u8g.drawStr(53,36,"%");
        u8g.drawStr(21,48,"'C");
        u8g.drawStr(53,48 ,"'C");

        //cpu_usg
        f24();
        if (cpu_usg < 10) { //값이 10보다 작으면 오른쪽에
          u8g.setPrintPos(32, 36);
          u8g.print(cpu_usg);}
        else if (cpu_usg < 100) { //값이 100보다 작으면 가운데에
          u8g.setPrintPos(14, 36);
          u8g.print(cpu_usg);}
        else { //값이 100이면 100출력(공간이 좁아서 위치 수동으로 잡아줌)
          u8g.drawStr(0,36,"1");
          u8g.drawStr(14,36,"00");}

        //cpu_tmp
        f18();
        u8g.setPrintPos(0, 64);
        u8g.print(cpu_tmp);
        
        //t_sen
        u8g.setPrintPos(32, 64);
        u8g.print(t_sen);

        //graph
        disp();
        for (int i = 0; i < 60; i++) //하나씩 선그어서 그래프 그리기
          {u8g.drawLine(125-i,61,125-i,61-map(cpu_log[59-i],0,100,0,60));}
      }                                   //0부터 100까지 나오는 수를 0부터 60까지 범위의 숫자로 멥핑
      while(u8g.nextPage());

    //GPU
      I2CMulti.switchToBus(1);
      u8g.firstPage();
      do {
        f08();
        u8g.drawStr(0,8,"GPU");
        u8g.drawStr(52,36,"%");
        u8g.drawStr(25,48,"%");
        u8g.drawStr(53,48 ,"'C");

        //gpu_usg
        f24();
        if (gpu_usg < 10) {
          u8g.setPrintPos(32, 36);
          u8g.print(gpu_usg);}
        else if (gpu_usg < 100) {
          u8g.setPrintPos(14, 36);
          u8g.print(gpu_usg);}
        else {
          u8g.drawStr(0,36,"1");
          u8g.drawStr(14,36,"00");}
        

        //gpu_tmp
        f18();
        u8g.setPrintPos(33, 64);
        u8g.print(gpu_tmp);
        
        //gpu_enc
        if (gpu_enc < 10) {
          u8g.setPrintPos(13, 64);
          u8g.print(gpu_enc);}
        else if (gpu_enc < 100) {
          u8g.setPrintPos(0, 64);
          u8g.print(gpu_enc);}
        else {
          u8g.drawStr(0,64,"!!!!");}

        //graph
        disp();
        for (int i = 0; i < 60; i++)
          {u8g.drawLine(125-i,61-map(gpu_enc_log[59-i],0,100,0,60),125-i,61-map(gpu_log[59-i],0,100,0,60));}
      }                           //enc사용량 만큼은 빼고 그리기(그래프에서 밑에 빈부분만큼이 nvenc사용량), enc=max일때 대비해서 enc그래프는 1픽셀 밑으로 지정
      while(u8g.nextPage());


    //RAM
      I2CMulti.switchToBus(2);
      u8g.firstPage();
      do {
        f08();
        u8g.drawStr(20,8,"RAM");
        u8g.drawStr(47,34,"%");
        u8g.drawStr(47,59,"G");
        u8g.drawStr(88,8,"DISK");
        u8g.drawStr(120,33,"G");
        u8g.drawStr(120,59,"G");
        
        f14();
        u8g.drawStr(59,32,"C:");
        u8g.drawStr(59,57,"D:");
        
        //mem_usg
        f18();
        if (mem_usg < 10) {
          u8g.setPrintPos(32, 34);
          u8g.print(mem_usg);}
        else if (mem_usg < 100) {
          u8g.setPrintPos(20, 34);
          u8g.print(mem_usg);}
        else {
          u8g.drawStr(7,34,"100");}
          
        //mem_abl
        if (mem_abl < 10) {
          u8g.setPrintPos(13, 59);
          u8g.print(mem_abl,1);} //소수 첫째자리까지만 출력
        else {
          u8g.setPrintPos(0, 59);
          u8g.print(mem_abl,1);}

        //cdr_abl
        if (cdr_abl < 10) {
          u8g.setPrintPos(107, 34);
          u8g.print(cdr_abl);}
        else if (cdr_abl < 100) {
          u8g.setPrintPos(94, 34);
          u8g.print(cdr_abl);}
        else {
          u8g.setPrintPos(81, 34);
          u8g.print(cdr_abl);}

        //ddr_abl
        if (ddr_abl < 10) {
          u8g.setPrintPos(107, 59);
          u8g.print(ddr_abl);}
        else if (ddr_abl < 100) {
          u8g.setPrintPos(94, 59);
          u8g.print(ddr_abl);}
        else {
          u8g.setPrintPos(81, 59);
          u8g.print(ddr_abl);}
      }
      while(u8g.nextPage());


    //DISK
      I2CMulti.switchToBus(3);
      u8g.firstPage();
      do {
        f08();
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
        f14();
        if (cdr_act < 10) {
          u8g.setPrintPos(20, 36);
          u8g.print(cdr_act);}
        else if (cdr_act < 100) {
          u8g.setPrintPos(10, 36);
          u8g.print(cdr_act);}
        else {
          u8g.setPrintPos(0, 36);
          u8g.print(cdr_act);}
          
        //cdr_red
        if (cdr_red == 0) {
          u8g.setPrintPos(63, 36);
          u8g.print(cdr_red, 0);}
        else if (cdr_red < 10) {
          u8g.setPrintPos(48, 36);
          u8g.print(cdr_red, 1);}
        else if (cdr_red < 100) {
          u8g.setPrintPos(38, 36);
          u8g.print(cdr_red, 1);}
        else if (cdr_red < 1000) {
          u8g.setPrintPos(43, 36);
          u8g.print(cdr_red, 0);}
        else {
          u8g.setPrintPos(38, 36);
          u8g.print(cdr_red, 0);}

        //cdr_wrt
        if (cdr_wrt == 0) {
          u8g.setPrintPos(109, 36);
          u8g.print(cdr_wrt, 0);}
        else if (cdr_wrt < 10) {
          u8g.setPrintPos(94, 36);
          u8g.print(cdr_wrt, 1);}
        else if (cdr_wrt < 100) {
          u8g.setPrintPos(84, 36);
          u8g.print(cdr_wrt, 1);}
        else if (cdr_wrt < 1000) {
          u8g.setPrintPos(89, 36);
          u8g.print(cdr_wrt, 0);}
        else {
          u8g.setPrintPos(84, 36);
          u8g.print(cdr_wrt, 0);}
        
        //ddr_act
        if (ddr_act < 10) {
          u8g.setPrintPos(20, 64);
          u8g.print(ddr_act);}
        else if (ddr_act < 100) {
          u8g.setPrintPos(10, 64);
          u8g.print(ddr_act);}
        else {
          u8g.setPrintPos(0, 64);
          u8g.print(ddr_act);}
        
        //ddr_red
        if (ddr_red == 0) {
          u8g.setPrintPos(63, 64);
          u8g.print(ddr_red, 0);}
        else if (ddr_red < 10) {
          u8g.setPrintPos(48, 64);
          u8g.print(ddr_red, 1);}
        else if (ddr_red < 100) {
          u8g.setPrintPos(38, 64);
          u8g.print(ddr_red, 1);}
        else if (ddr_red < 1000) {
          u8g.setPrintPos(43, 64);
          u8g.print(ddr_red, 0);}
        else {
          u8g.setPrintPos(38, 64);
          u8g.print(ddr_red, 0);}

        //ddr_wrt
        if (ddr_wrt == 0) {
          u8g.setPrintPos(109, 64);
          u8g.print(ddr_wrt, 0);}
        else if (ddr_wrt < 10) {
          u8g.setPrintPos(94, 64);
          u8g.print(ddr_wrt, 1);}
        else if (ddr_wrt < 100) {
          u8g.setPrintPos(84, 64);
          u8g.print(ddr_wrt, 1);}
        else if (ddr_wrt < 1000) {
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
        f08();
        u8g.drawStr(20,8,"NET");
        u8g.drawStr(97,8,"FAN");
        u8g.drawStr(0,26,"^"); //화살표 그리기
        u8g.drawStr(1,28,"l");
        u8g.drawStr180(3,46,"^"); //180도 회전해서 출력
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
        f18();
        if (int_upr == 0) {
          u8g.setPrintPos(39, 33);
          u8g.print(int_upr, 0);}
        else if (int_upr < 10) {
          u8g.setPrintPos(19, 33);
          u8g.print(int_upr, 1);}
        else if (int_upr < 100) {
          u8g.setPrintPos(6, 33);
          u8g.print(int_upr, 1);}
        else {
          u8g.setPrintPos(13, 33);
          u8g.print(int_upr, 0);}

        //int_dlr
        if (int_dlr == 0) {
          u8g.setPrintPos(39, 60);
          u8g.print(int_dlr, 0);}
        else if (int_dlr < 10) {
          u8g.setPrintPos(19, 60);
          u8g.print(int_dlr, 1);}
        else if (int_dlr < 100) {
          u8g.setPrintPos(6, 60);
          u8g.print(int_dlr, 1);}
        else {
          u8g.setPrintPos(13, 60);
          u8g.print(int_dlr, 0);}

        //cpu_fan
        f14();
        if (cpu_fan < 1000) {
          u8g.setPrintPos(95, 28);
          u8g.print(cpu_fan);}
        else {
          u8g.setPrintPos(85, 28);
          u8g.print(cpu_fan);}      

        //gpu_fan
        if (gpu_fan == 0) {
          u8g.setPrintPos(115, 44);
          u8g.print(gpu_fan);}
        else if (gpu_fan < 1000) {
          u8g.setPrintPos(95, 44);
          u8g.print(gpu_fan);}
        else {
          u8g.setPrintPos(85, 44);
          u8g.print(gpu_fan);}     

        //fnt_fan
        if (fnt_fan < 1000) {
          u8g.setPrintPos(95, 60);
          u8g.print(fnt_fan);}
        else {
          u8g.setPrintPos(85, 60);
          u8g.print(fnt_fan);}
      }
      while(u8g.nextPage());
    }
  }
}

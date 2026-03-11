#include <do_an.h>
#define timeintro 1000
#define thoigiantime 100
#define vantay input(PIN_D7)
char actual_password[6] = {2,4,0,1,0,4};
char given_password[6];   // Buffer to store the entered password
unsigned int8 count=0,id;
int pass=0;


void ScreenIntro();
void ScreenMain();
void nhapdulieu();
void xuatdulieu();
void xoa1kitu();
void xoatoanbo();
void nhapxuatdulieu();
void PasswordIncorrect();
void PasswordCorrect();
void hienthithoigian();
void cbvantay();

void main()
{
   Init();  
   Motor_stop();
   ScreenIntro();
   delay_ms(timeintro);
   lcd_command(0x01);
   /*if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai();
      nap_thoi_gian_htai_vao_ds1307();
   }*/
   doc_thoi_gian_tu_realtime();
   giaytam=giay_ds13;
   hien_thi_thoi_gian_ds1307();
   ScreenMain();
   while (true) 
   {
      hienthithoigian();
      key_4x4();
      if (mp!=0xff){
         if ((MP>=0)&&(MP<10)){nhapdulieu(); xuatdulieu();}//testkeypad();}
         else if (MP==13){xoa1kitu();}
         else if (MP==12){xoatoanbo();}
         else if (MP==15){nhapxuatdulieu();}
      }
      cbvantay();
   }
}
void cbvantay()
{
   if(vantay)
   {
      delay_ms(10);
      if(vantay)
      {
         PasswordCorrect();
      }
      while(vantay){hienthithoigian();}
   }
}
void hienthithoigian()
{
   doc_thoi_gian_tu_realtime();
   if (giaytam!=giay_ds13)
      {
         giaytam=giay_ds13; 
         hien_thi_thoi_gian_ds1307 ( );
      }
}
void ScreenIntro()
{
   lcd_command(0xC0); lcd_data("HuynhThiQuynhPhuong");
   lcd_command(0x94+5); lcd_data("22161067");
}
void ScreenMain()
{
   lcd_command(0x94); lcd_data("Enter Password:"); //lcd_data("240104");
}

void nhapdulieu()
{
   if (count<6) {
      given_password[count]=MP;
      count++;
   }
}
void xuatdulieu()
{
   lcd_command(0xD4+count-1); lcd_data(given_password[count-1]+0x30);
   delay_ms(timedelaykeypad); lcd_command(0xD4+count-1); lcd_data("*");
}
void xoa1kitu()
{
   lcd_command(0xD4+id);
   SWITCH(id) 
   {
      CASE 7:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--; BREAK;
      CASE 6:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;        
      CASE 5:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;
      CASE 4:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;
      CASE 3:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;
      CASE 2:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;
      CASE 1:  
         lcd_command(0xD4+id-1); lcd_data("*");id--;count--;BREAK;
   }
}
void xoatoanbo()
{
   count=id=0;
   lcd_command(0xD4); lcd_data("           ");
}
void nhapxuatdulieu()
{
   if(given_password[0]==actual_password[0] && given_password[1]==actual_password[1] && given_password[2]==actual_password[2] && given_password[3]==actual_password[3] && given_password[4]==actual_password[4] && given_password[5]==actual_password[5]) 

      
      PasswordCorrect();
   else 
      PasswordIncorrect();
}
void PasswordCorrect()
{
   output_high(LED_GRANTED); 
   output_low(LED_WAIT); 
   output_low(LED_DENIED); 
   Motor_start(); 
   xoatoanbo();
   lcd_command(0x94);
   lcd_data("Access Granted       ");
   pass=1;
   if(pass)
   {
      for(int i=0;i<thoigiantime;i++)
      {
         delay_ms(50);
         hienthithoigian();           
      }
      xoatoanbo(); 
      ScreenMain();
      pass=0;
      output_low(LED_GRANTED); 
      output_high(LED_WAIT); 
      output_low(LED_DENIED); 
      Motor_stop();
   }
}
void PasswordIncorrect()
{
   count=id=0;
   output_high(LED_DENIED); 
   output_low(LED_GRANTED); 
   output_low(LED_WAIT); 
  
   Motor_stop();  
   xoatoanbo();
   lcd_command(0x94);
   lcd_data("Try again: DENIED      "); 
   
   //printf("Access Denied\r\n");
}





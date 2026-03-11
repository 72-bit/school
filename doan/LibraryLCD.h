#define RS  Pin_E2   // thay doi chan tuy y
#define RW  Pin_E1              //
#define E   Pin_E0              //

#define A2  PIN_A2           //
#define A3  PIN_A3           //
#define A4  PIN_A4           //
#define A5  PIN_A5 
const unsigned char lcd_so_x[10][6] ={
                  0,1,2,4,3,5,               // so 0
                  1,2,32,3,7,3,              // so 1
                  6,6,2,4,3,3,               // so 2
                  6,6,2,3,3,5,               // so 3
                  7,3,7,32,32,7,             // so 4
                  7,6,6,3,3,5,               // so 5                               
                  0,6,6,4,3,5,               // so 6
                  1,1,7,32,32,7,             // so 7
                  0,6,2,4,3,5,               // so 8
                  0,6,2,3,3,5};             // so 9
const unsigned int lcd_ma_8doan[] = {
   0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan f - 0
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,  //doan a - 1
   0x1c,0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan b - 2
   0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,  //doan d - 3
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,  //doan e - 4
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e,0x1c,  //doan c - 5      
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x1f,0x1f,  //doan g+d-6 
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f
}; //doan i  -7
void setpin(int n)
{
   output_bit (A5,n&1);
   output_bit (A4,n&2);
   output_bit (A3,n&4);
   output_bit (A2,n&8);
}
void lcd_command(int n)
{
   setpin(swap(n));
   output_low(RS);
   output_low(RW);
   output_high(E);
   delay_us(1);
   output_low(E);
   delay_us(50);
   //////gui 4bit thap//////
   setpin(swap(n));
   output_high(E);
   delay_us(1);
   output_low(E);
   delay_us(50);
}
void lcd_data(char n)// void hien thi ky tu hoac chuoi ky tu ra man hinh
{
   //////gui 4bit cao///////
   setpin(swap(n));
   output_high(RS);
   output_low(RW);
   output_high(E);
   delay_us(1);
   output_low(E);
   delay_us(50);
   //////gui 4bit thap//////
   setpin(swap(n));
   output_high(E);
   delay_us(1);
   output_low(E);
   delay_us(50);
}
void lcd_setup()//khoi tao lcd
{
   set_tris_d(0);//set_tris theo ten port da khai bao #define o tren
   lcd_command(0x02);
   delay_ms(2);
   lcd_command(0x06);
   lcd_command(0x28);
   lcd_command(0x0c);
   lcd_command(0x01);
   delay_ms(100);
}
void hangcot(int x, int y)
{
   switch(x)
   {
      case 0: lcd_command(0x80+y); break;
      
      case 1: lcd_command(0xC0+y); break;
      
      case 2: lcd_command(0x94+y); break;
      
      case 3: lcd_command(0xD4+y); break;
      default:
      lcd_setup();
      lcd_data(" ERROR POSITION ");
      while(1){};
   }
}
Void ghiCGRAM(int text)// ghi ky tu dac biet vao CGRAM cua lcd
{
   int add;
   add=0;
   lcd_command(0x40);  //dia chi bat dau cua cgram
   while(add!=64)// ghi 64byte tuong duong 8 ky tu
   {
      lcd_data(text);//ghi tung byte vao cgram   
      add++;
   }      
}
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   hangcot(x1,y1);
   for (int i=0;i<6;i++)
   {
      if (i==3) hangcot(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

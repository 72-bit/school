#define giay_htai 0x45
#define phut_htai 0x16
#define gio_htai 0x18
#define thu_htai 7
#define ngay_htai 0x20
#define thang_htai 0x11
#define nam_htai 0x24
#define ma_ds 0x98
#define addr_wr_1307 0xd0
#define addr_rd_1307 0xd1
#define addr_mem 0x00
unsigned char nam_ds13,thang_ds13,ngay_ds13,thu_ds13,gio_ds13,phut_ds13,giay_ds13,ma_ds13,control_ds13,giaytam;
void thiet_lap_thoi_gian_hien_tai()
{
   giay_ds13 = giay_htai;
   phut_ds13 = phut_htai;
   gio_ds13 = gio_htai;
   thu_ds13 = thu_htai;
   ngay_ds13 = ngay_htai;
   thang_ds13 = thang_htai;
   nam_ds13 = nam_htai;
   control_ds13 = 0x90;
   ma_ds13 = ma_ds;
}
void nap_thoi_gian_htai_vao_ds1307()
{
   i2c_start();
   i2c_write(addr_wr_1307);
   i2c_write(0x00);
   i2c_write(giay_ds13);
   i2c_write(phut_ds13);
   i2c_write(gio_ds13);
   i2c_write(thu_ds13);
   i2c_write(ngay_ds13);
   i2c_write(thang_ds13);
   i2c_write(nam_ds13);
   i2c_write(control_ds13);
   i2c_write(ma_ds13);
   i2c_stop();
}
void doc_thoi_gian_tu_realtime()
{
   i2c_start();
   i2c_write(addr_wr_1307);
   i2c_write(addr_mem);
   i2c_start();
   i2c_write(addr_rd_1307);
   giay_ds13 = i2c_read();
   phut_ds13 = i2c_read();
   gio_ds13 = i2c_read();
   thu_ds13 = i2c_read();
   ngay_ds13 = i2c_read();
   thang_ds13 = i2c_read();
   nam_ds13 = i2c_read();
   control_ds13 = i2c_read();
   ma_ds13 = i2c_read(0); //not ack
   i2c_stop();
}
void doc_giay_tu_realtime()
{
   i2c_start();
   i2c_write(addr_wr_1307);
   i2c_write(addr_mem);
   i2c_start();
   i2c_write(addr_rd_1307);
   giay_ds13 = i2c_read(0);
   i2c_stop();
}
void hien_thi_thoi_gian_ds1307 ( )
{
   lcd_hienthi_so_z_toado_xy(gio_ds13/16,0,0);
   lcd_hienthi_so_z_toado_xy(gio_ds13%16,0,3);
   lcd_hienthi_so_z_toado_xy(phut_ds13/16,0,7);
   lcd_hienthi_so_z_toado_xy(phut_ds13%16,0,10);
   lcd_hienthi_so_z_toado_xy(giay_ds13/16,0,14);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16,0,17);
   /*hangcot(3,0);
   lcd_data(ngay_ds13/16 +0x30);
   lcd_data(ngay_ds13%16 +0x30);
   lcd_data('/');
   lcd_data(thang_ds13/16 +0x30);
   lcd_data(thang_ds13%16 +0x30);
   lcd_data('/');
   lcd_data(nam_ds13/16 +0x30);
   lcd_data(nam_ds13%16 +0x30);*/
}
void luu_giai_ma_hien_thi_sau_khi_chinh(){
   nap_thoi_gian_htai_vao_ds1307();
   hien_thi_thoi_gian_ds1307 ( );
}
unsigned int8 hieu_chinh_so_bcd_tang(unsigned int8 x ){
   unsigned int8 y;
   y = x;
   x = x & 0x0f;
   if (x==0x0a) y = y + 6;
   return(y);
}
unsigned int8 hieu_chinh_so_bcd_giam(unsigned int8 x ){
   unsigned int8 y;
   y = x;
   x = x & 0x0f;
   if (x==0x0f) y = y - 6;
   return(y);
}

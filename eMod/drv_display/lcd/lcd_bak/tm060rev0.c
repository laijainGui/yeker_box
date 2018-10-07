/*
*********************************************************************************************************
*                            sys_config.fex ����ʾ��
lcd_bl_en_used           = 0
lcd_bl_en                = 0

lcd_power_used           = 0
lcd_power                = 0

lcd_pwm_used             = 1
lcd_pwm                  = port:PA08<2><0><default><default>
*********************************************************************************************************
*/
#include "epdk.h"
//#include "emod.h"
#include "lcd_panel_cfg.h"



#define  T201ADDR   	  0x6c
#define  MAX_T201_LEN     24

#define TWI_WRITE_SPEC_RS   0
//#define TWI_READ_SPEC_RS    1

 ES_FILE       *fiic;

/////////////////////////////////////////////////////////////////////////////////////
//д�Ĵ���֮ǰ�������ȴ�TTL_clk��tc102оƬ������TC102���ܹ���
__u8  T201_INIT_TBL[MAX_T201_LEN][2]=
{
	{0x2a,0xa2},{0x2d,0xc2},{0x36,0x30},{0x46,0x49},{0x47,0x92},{0x48,0x00},{0x5f,0x00},{0x60,0xa5},
	{0x61,0x08},{0x62,0xff},{0x64,0x00},{0x80,0x01},{0x81,0xe4},{0x2c,0x08},{0x33,0x29},{0x34,0x09},{0x3d,0x00},
	{0x42,0x88},{0x43,0x86},{0x44,0x68},{0x45,0x88},{0x46,0x96},{0x47,0x48},{0x48,0x04}	
};





//__s32 IIC_Write_forT201(__u8 reg_addr, __u8 *data, __u8 len)
//{
//    __twi_dev_para_ex_t   iic_para = {0};
//    __s32 ret = EPDK_FAIL;
//    
//    iic_para.slave_addr         = T201ADDR>>1; //�豸��ַ��ֵΪ7bit��ַ��������д��־λ
//    iic_para.slave_addr_flag    = 0;
//    iic_para.byte_addr          = &reg_addr;    //��������豸�ļĴ�����ַ����8λ�Ļ�����Ҫ�������byte�ĵ�ַ�� ������8λΪ��������ֱ��ȡ��ַ
//    iic_para.byte_addr_width    = 1;            //�豸�Ĵ�����ַ�ĳ��ȣ���byteΪ��λ��������8λΪ��������ȡ1, ���>1�������賤�ȣ����3
//    iic_para.data               = data;         //����buffer
//    iic_para.byte_count         = len;          //��ȡ���ݳ���
//    
//    ret = eLIBs_fioctrl(fiic, TWI_WRITE_SPEC_RS,  0, (void *)&iic_para);
////    if (ret == EPDK_FAIL)
////    {
////        //FAIL ����
////        return EPDK_FAIL;
////    }
//    return ret;
//}

static __s32 IIC_Write_forT201(__u8  addr, __u8 *wdata, __u8 len )
{
    __twi_dev_para_ex_t  piic;

    eLIBs_eLIBs_memset(&piic, 0, sizeof(__twi_dev_para_ex_t));
    piic.slave_addr_flag = 0;
    piic.slave_addr      = 0x36;
    piic.byte_addr_width = 1;
    piic.byte_addr       = &addr;
    piic.data            = wdata;
    piic.byte_count      = len;
    
    return  eLIBs_fioctrl(fiic, TWI_WRITE_SPEC_RS, 0, (void *)&piic);
}

static __s32 IIC_read_forT201(__u8  addr, __u8 *rdata, __u8 len )
{
    __twi_dev_para_ex_t  piic;

    eLIBs_eLIBs_memset(&piic, 0, sizeof(__twi_dev_para_ex_t));
    piic.slave_addr_flag = 0;
    piic.slave_addr      = 0x36;
    piic.byte_addr_width = 1;
    piic.byte_addr       = &addr;
    piic.data            = rdata;
    piic.byte_count      = len;
    
    return  eLIBs_fioctrl(fiic, TWI_READ_SPEC_RS, 0, (void *)&piic);
}


static __s32 T201_Initialize(void)
{
	__u8 i=0;
	__u8 tData[2];
	__u8 rData[20]={0};
	int ret = 0;
	
	fiic = eLIBs_fopen("b:\\BUS\\TWI0", "r+");	
	if(!fiic)
        	{
        		eLIBs_printf("Open TWI Dev File Failed\n");
        		return EPDK_FAIL;
        	}
     eLIBs_fioctrl(fiic, TWI_SET_SCL_CLOCK , 0, ( void *)(100000));
     eLIBs_printf("Open TWI Dev File ok\n");  	   	
	for(i=0;i<MAX_T201_LEN;i++)
	{
		tData[0] = T201_INIT_TBL[i][1]	;
		//IIC_Write_forT201(T201ADDR, T201_INIT_TBL[i][0], tData, 1);
		ret = IIC_Write_forT201(T201_INIT_TBL[i][0], tData, 1);
		eLIBs_printf("write:ret = %d\n",ret);
		
		ret = IIC_read_forT201(T201_INIT_TBL[i][0], rData, 1 );
		eLIBs_printf("read:ret = %d\n",ret);
		
		eLIBs_printf("rData%d = %d\n",i,rData[0]);
		
	}	
	eLIBs_printf("T201 init ok\n");
	eLIBs_fclose(fiic);
	return EPDK_OK;
}




static void LCD_cfg_panel_info(__panel_para_t * info)
{
    eLIBs_memset(info,0,sizeof(__panel_para_t));

    //���Ļ�����Ϣ
    info->lcd_x                   = 800;
    info->lcd_y                   = 480;
    info->lcd_dclk_freq           = 50;  //MHz
    info->lcd_pwm_freq            = 1;  //KHz
    info->lcd_srgb                = 0x00202020;
    info->lcd_swap                = 0;
    info->lcd_pwm_pol             = 1;
    
    //���Ľӿ�������Ϣ
    info->lcd_if                  = 0;//0:HV , 1:8080 I/F, 2:TTL I/F, 3:LVDS
    
    //����HVģ�������Ϣ
    info->lcd_hv_if               = 0;
    info->lcd_hv_hspw             = 0;
    info->lcd_hv_lde_iovalue      = 0;
    info->lcd_hv_lde_used         = 0;
    info->lcd_hv_smode            = 0;
    info->lcd_hv_syuv_if          = 0;
    info->lcd_hv_vspw             = 0;
        
    //����HV������Ϣ
    info->lcd_hbp           = 3;
    info->lcd_ht            = 928;
    info->lcd_vbp           = 3;
    info->lcd_vt            = (2 * 525);

    //����IO������Ϣ
    info->lcd_io_cfg0             = 0x00000000;
    info->lcd_io_cfg1             = 0x00000000;
    info->lcd_io_strength         = 0;

    //TTL��Ļ��������Ϣ
    info->lcd_ttl_ckvd            = 0;
    info->lcd_ttl_ckvh            = 0;
    info->lcd_ttl_ckvt            = 0;
    info->lcd_ttl_datainv_en      = 0;
    info->lcd_ttl_datainv_sel     = 0;
    info->lcd_ttl_datarate        = 0;
    info->lcd_ttl_oehd            = 0;
    info->lcd_ttl_oehh            = 0;
    info->lcd_ttl_oevd            = 0;
    info->lcd_ttl_oevh            = 0;
    info->lcd_ttl_oevt            = 0;
    info->lcd_ttl_revd            = 0;
    info->lcd_ttl_revsel          = 0;
    info->lcd_ttl_sthd            = 0;
    info->lcd_ttl_sthh            = 0;
    info->lcd_ttl_stvdl           = 0;
    info->lcd_ttl_stvdp           = 0;
    info->lcd_ttl_stvh            = 0; 
        
    //cpu��Ļ��������Ϣ
    info->lcd_frm 			 = 0;	//0: disable; 1: enable rgb666 dither; 2:enable rgb656 dither
}

static __s32 LCD_open_flow(__u32 sel)
{  eLIBs_printf("LCD_open_flow-----------------------------\n");
	LCD_OPEN_FUNC(sel, LCD_power_on	, 10); 	//��LCD���磬����ʱ10ms
	LCD_OPEN_FUNC(sel, LCD_io_init	, 20); 	//����ͳ�ʼ��IO������ʱ20ms
	LCD_OPEN_FUNC(sel, TCON_open	, 200); //��LCD������������ʱ200ms
	

	
	LCD_OPEN_FUNC(sel, LCD_open_cmd	, 10); 	//ͨ��IO����LCDģ��Ϊ����ģʽ������ʱ10ms
	LCD_OPEN_FUNC(sel, LCD_bl_open	, 0); 	//�򿪱��⣬����ʱ0ms
	    //T201_Initialize();                      //T201��ʼ��
	//LCD_OPEN_FUNC(sel, T201_Initialize	, 0);    
   eLIBs_printf("LCD_open_flow ok-----------------------------\n");
	return 0;
}

static __s32 LCD_close_flow(__u32 sel)
{	
	LCD_CLOSE_FUNC(sel, LCD_bl_close    , 0); 	//�رձ��⣬����ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_close_cmd   , 0); 	//ͨ��IO����LCDģ��Ϊ����/����ģʽ������ʱ0ms
	LCD_CLOSE_FUNC(sel, TCON_close	    , 0); 	//�ر�LCD ������������ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_io_exit	    , 0); 	//����ʱIO��״̬���ͷţ�����ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_power_off   , 1700); //�ر�LCD���磬����ʱ1700ms

	return 0;
}


////////////////////////////////////////   POWER   ////////////////////////////////////////////////////////////////////
static void LCD_power_on(__u32 sel)//0 active
{
	__lcd_panel_init_para_t para;
	ES_FILE *fp;
		
	fp = eLIBs_fopen("b:\\HID\\POWER", "r+");
	
	// open LCD_VCC
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_PWREPT_SET, POWER_EPT_6, (void *) (POWER_EPT_MOS_N | POWER_EPT_GATE_ON)); 
   	// open IPSOUTSW
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_PWREPT_SET, POWER_EPT_3, (void *) (POWER_EPT_MOS_N | POWER_EPT_GATE_ON));
   	//set GPIO0 to LDO,control PA
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_VOUT_SET, POWER_VOL_LDO5, (void *) (3300));
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_VSTS_SET, POWER_VOL_LDO5, (void *) (1));
   	
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_SET_VBUS_CURR, POWER_VBUS_CUR_NOT_LIMIT, (void *) (0)); 
   	
	eLIBs_fclose(fp);
	
    LCD_POWER_EN(sel, 1);
}

static void LCD_power_off(__u32 sel)//0 active
{
	__lcd_panel_init_para_t para;
	ES_FILE *fp;

	fp = eLIBs_fopen("b:\\HID\\POWER", "r+");

	//close LCD_VCC
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_PWREPT_SET, POWER_EPT_6, (void *) (POWER_EPT_MOS_P | POWER_EPT_GATE_ON)); 
   	//close IPSOUTSW
   	eLIBs_fioctrl(fp, DRV_POWER_CMD_PWREPT_SET, POWER_EPT_3, (void *) (POWER_EPT_MOS_P | POWER_EPT_GATE_ON));
   	
	eLIBs_fclose(fp);
    LCD_POWER_EN(sel, 0);
}

////////////////////////////////////////   back light   ////////////////////////////////////////////////////////////////////
static void LCD_bl_open(__u32 sel)
{
    __u32 tmp;
	__lcd_panel_init_para_t para;
	ES_FILE *fp;

    LCD_PWM_EN(sel, 1);
    
   T201_Initialize(); 
   esKRNL_TimeDly(5);
//	__wait__;
   fp = eLIBs_fopen("b:\\HID\\POWER", "r+");

   	eLIBs_fioctrl(fp, DRV_POWRE_CMD_BL_CTRL, POWER_OPEN, (void *) (0) ); 
	eLIBs_fclose(fp);
}

static void LCD_bl_close(__u32 sel)
{
    __u32 tmp;
    __lcd_panel_init_para_t para;
	ES_FILE *fp;
	
	 fp = eLIBs_fopen("b:\\HID\\POWER", "r+");

   	eLIBs_fioctrl(fp, DRV_POWRE_CMD_BL_CTRL, POWER_CLOSE, (void *) (0) ); 
	eLIBs_fclose(fp);
	
    LCD_PWM_EN(sel, 0);
}


//����IO,����IO״̬Ϊ���HIGHT
static void  LCD_io_init(__u32 sel)
{	
}

//����IO״̬Ϊ���LOW,�ͷ�IO
static void LCD_io_exit(__u32 sel)
{
}

static void  LCD_open_cmd(__u32 sel)
{
}

static void  LCD_close_cmd(__u32 sel)
{
}

void LCD_get_panel_funs_0(__lcd_panel_fun_t * fun)
{
    fun->cfg_panel_info = LCD_cfg_panel_info;
    fun->cfg_open_flow = LCD_open_flow;
    fun->cfg_close_flow = LCD_close_flow;
}


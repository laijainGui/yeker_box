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
#include "lcd_panel_cfg.h"


static ES_FILE *fp_twi;

void delay_nus(__s32 us)
{
    int i;
    while(us--)
    {
        for(i=0; i<60;i++); 
    }   
}

static __hdle h_reset;

static __s32 Gpio_initialize(void)
{
	user_gpio_set_t gpio_set;

	gpio_set.port = 5;
	gpio_set.port_num = 5;
	gpio_set.mul_sel = 1;
	gpio_set.pull = 1;
	gpio_set.drv_level = 1;
	gpio_set.data = 1;

	h_reset = OSAL_GPIO_Request(&gpio_set, 1);
	OSAL_GPIO_DevSetONEPIN_IO_STATUS(h_reset, 1, 0);
}

static void gpio_reset(__u32 value)
{
	OSAL_GPIO_DevWRITE_ONEPIN_DATA(h_reset, value&0x01, 0);
}

static void LCD_cfg_panel_info(__panel_para_t * info)
{

    memset(info,0,sizeof(__panel_para_t));

	info->lcd_x                   = 720;
    info->lcd_y                   = 720;
    info->lcd_dclk_freq           = 29;  //33MHz    // ���ܵ���22MHz
    info->lcd_pwm_freq            = 1;  //KHz
    info->lcd_srgb                = 0x00202020;
    info->lcd_swap                = 0;
    /*���Ľӿ�������Ϣ*/
    info->lcd_if                  = 0;//0:HV , 1:8080 I/F, 2:TTL I/F, 3:LVDS
    /*����HVģ�������Ϣ*/
    info->lcd_hv_if               = 0;
    info->lcd_hv_hspw             = 20;
    info->lcd_hv_lde_iovalue      = 0;
    info->lcd_hv_lde_used         = 0;
    info->lcd_hv_smode            = 0;
    info->lcd_hv_syuv_if          = 0;
    info->lcd_hv_vspw             = 10;

    /*����HV������Ϣ*/
    info->lcd_hbp           = 40;
    info->lcd_ht            = 770;
    info->lcd_vbp           = 19;
    info->lcd_vt            = (2 * 749);//535   60- 61

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
    info->lcd_frm 			 = 1;	//0: disable; 1: enable rgb666 dither; 2:enable rgb656 dither
}

static __s32 LCD_open_flow(__u32 sel)
{
	Gpio_initialize();
	LCD_OPEN_FUNC(sel, LCD_power_on	, 10); 	//��LCD���磬����ʱ10ms
	LCD_OPEN_FUNC(sel, LCD_io_init	, 100); 	//����ͳ�ʼ��IO������ʱ20ms
	LCD_OPEN_FUNC(sel, TCON_open	, 50); //��LCD������������ʱ200ms
	LCD_OPEN_FUNC(sel, LCD_open_cmd	, 20); 	//ͨ��IO����LCDģ��Ϊ����ģʽ������ʱ10ms
	LCD_OPEN_FUNC(sel, LCD_bl_open	, 0); 	//�򿪱��⣬����ʱ0ms

	return 0;
}

static __s32 LCD_close_flow(__u32 sel)
{	
	LCD_CLOSE_FUNC(sel, LCD_bl_close    , 0); 	//�رձ��⣬����ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_close_cmd   , 0); 	//ͨ��IO����LCDģ��Ϊ����/����ģʽ������ʱ0ms
	LCD_CLOSE_FUNC(sel, TCON_close	    , 0); 	//�ر�LCD ������������ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_io_exit	    , 0); 	//����ʱIO��״̬���ͷţ�����ʱ0ms
	LCD_CLOSE_FUNC(sel, LCD_power_off   , 1000); //�ر�LCD���磬����ʱ1700ms

	return 0;
}


////////////////////////////////////////   POWER   ////////////////////////////////////////////////////////////////////
static void LCD_power_on(__u32 sel)//0 active
{
	gpio_reset(1);
    LCD_POWER_EN(sel, 1);
	esKRNL_TimeDly(50);
	gpio_reset(0);
	esKRNL_TimeDly(50);
	gpio_reset(1);
}

static void LCD_power_off(__u32 sel)//0 active
{
    LCD_POWER_EN(sel, 0);
}

////////////////////////////////////////   back light   ////////////////////////////////////////////////////////////////////
static void LCD_bl_open(__u32 sel)
{   
    LCD_BL_EN(sel, 1); 
    LCD_PWM_EN(sel, 1);
}

static void LCD_bl_close(__u32 sel)
{

    LCD_BL_EN(sel, 0); 
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

void LCD_get_panel_funs_1(__lcd_panel_fun_t * fun)
{

}

void hdmi_get_panel_funs_1(__lcd_panel_fun_t * fun)
{

}
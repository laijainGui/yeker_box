/*
*********************************************************************************************************
*                                                           eBase
*                                           the Abstract of Hardware
*
*                                   (c) Copyright 2006-2010, AW China
*                                                   All Rights Reserved
*
* File        :  bsp_lradc.h
* Date        :  2011-01-24
* Author      :  Victor
* Version     :  v1.00
* Description:  
*                                   Operation for LRADC module,AW1619
* History     :
*      <author>          <time>             <version >          <desc>
*       Victor         2011-01-24              1.0           create this file     
*
*********************************************************************************************************
*/
#ifndef _BSP_LRADC_H_
#define _BSP_LRADC_H_

/* set channel number */
typedef enum
{
 LRADC_ONE_CHANNEL   =  0x1, //default is ADC0
 LRADC_TWO_CHANNEL   =  0x2, //ADC0 and ADC1��warning: AW1619û��ADC1��ֻ��ADC0   
}
LRADC_CHANNEL_SELECT_SET;

/* set lradc module sample frequency */
typedef enum
{
 LRADC_SAMPLE_250HZ  = 0x1,  //4ms
 LRADC_SAMPLE_125HZ  = 0x2,  //8ms
 LRADC_SAMPLE_63HZ   = 0x3,  //16ms 
 LRADC_SAMPLE_32HZ   = 0x4,  //32ms   
}
LRADC_SAMPLE_SELECT_SET;

/* set lradc module level b voltage */
typedef enum
{
 LRADC_LEVELB_1_6V  =  0x1, //level b voltage
 LRADC_LEVELB_1_7V  =  0x2,
 LRADC_LEVELB_1_8V  =  0x3,
 LRADC_LEVELB_1_9V  =  0x4,
}
LRADC_LEVEL_B_SELECT_SET;

/*line control-return value for callback function */
typedef enum
{
 LRADC_LINE_INT_COMING = 0x0,
 LRADC_LINE_INT_GOING  = 0x1,
}
LRADC_LINE_NOTIFIER_SET;

/*
****************************************************************************************************
*
*             lradck_proc
*
*  Description:
*       ���Ͱ���̧����Ϣ�����ӿ�
*		�������������Ͱ���̧����Ϣ����������os�İ���������Ϣ������ɹ��ܣ�
*		����melis�µ�DEV_KEY_Ioctrl��wince��kbd_event��linux��input_event��input_syn�Ⱥ�����
*		
*  Parameters:
*		key_value	:	����ֵ������һ������̧���ˡ�
*
*  Return value:
*		         ��
*  Notes:
*
****************************************************************************************************
*/
typedef void (*lradc_proc)(__u32 key_value);

typedef struct tag_lradck_scancode_info{

    __u32	keyMin; 
    __u32	keyMax;
    __u32	keyCode; //keyMin-keyMax Scancode mapping to keyCode

}LRADC_KEY_SCANCODE;

typedef struct lradc_key_setting
{
    //irq variable���ڲ������ж�ʹ��
    __u32 irq_no;
    __u32 irq_flags;
    __u32 irq_prio;

    //����ͨ�����������ʣ���ѹB��ֵ
    __u32 channel;// 1:ADC0,2:ADC0 & ADC1
    __u32 sample;// 1,2,3,4
    __u32 voltageB;//1,2,3,4

    __u32  first_key_time;
    __u32  first_key_delay;
    __u32  repeat_key_time;
    
    //����ʹ��
    __u32 key_adc;//0:NOTUSED,1:ADC0,2:ADC1.
    lradc_proc key_down;//
    lradc_proc key_up;
    //���ü�ֵӳ���
    LRADC_KEY_SCANCODE *pKeycode;
    __u32 kc_size;//8��

    //�߿�ʹ��    
    __u32 line_adc;//0:NOTUSED,1:ADC0,2:ADC1.
    lradc_proc line_notifier;
}KEYC_SETTING;

/*
****************************************************************************************************
*
*  FunctionName:           eBSP_lradc_key_init
*
*  Description:
*               ����ʱ�ӣ������жϴ���������ֵӳ���ĳ�ʼ����
*           
*       
*  Parameters:
*       ioremap :  �����ַ��
*       pKeyc   :  �ⲿ������Դ�������ж�����ţ��Ĵ������ã���ѹB�������ʣ�ͨ����ѡ��
*
*  Return value:
*            �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_LRADCK_init(KEYC_SETTING *pKeyc);

/*
****************************************************************************************************
*
*  FunctionName:           eBSP_lradc_key_exit
*
*  Description:
*               ֹͣʱ�ӣ�ȡ��ע���жϴ��������ر�lradcģ�顣
*           
*       
*  Parameters:
*
*       pKeyc   :  �ⲿ������Դ�������ж�����ţ��Ĵ������ã���ѹB�������ʣ�ͨ����ѡ��
*
*  Return value:
*            �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_LRADCK_exit (KEYC_SETTING *pKeyc);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_set_firstKeyTime
*
*  Description:
*                   ���ð�����һ�ΰ���ʱ����Ӧʱ�䣬
*               ��ģ���ʼ��ʱָ���Ĳ���Ƶ��*first_timeΪ������һ�ΰ��µ���Ӧʱ�䡣
*              
*  Parameters:
*       first_time   : ������һ�ΰ���ʱ����Ӧʱ�䡣
*
*  Return value:
*            �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*          
****************************************************************************************************
*/
__s32 BSP_LRADCK_set_firstKeyTime(__u32 first_time);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_get_firstKeyTime
*
*  Description:
*                   ��ȡ������һ�ΰ���ʱ����Ӧʱ�䣬
*              
*  Parameters:
*       �ޡ�
*
*  Return value:
*           ���ذ�����һ�ΰ���ʱ����Ӧʱ�䡣����0��ʾ��������ֵ��ȷ��
*  Notes:
*          
****************************************************************************************************
*/
__u32 BSP_LRADCK_get_firstKeyTime(void);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_set_firstKeyDelay
*
*  Description:
*                   ���õ�һ�ΰ������º󷢵ڶ��ΰ�����Ϣ�ļ��ʱ�䡣Ҳ�ǳ���������ֵʱ�䡣     
*  Parameters:
*       �ޡ�
*
*  Return value:
*            �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*          
****************************************************************************************************
*/
__s32 BSP_LRADCK_set_firstKeyDelay(__u32 first_delay);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_get_firstKeyDelay
*
*  Description:
*                   ��ȡ��һ�ΰ������º󷢵ڶ��ΰ�����Ϣ�ļ��ʱ�䡣Ҳ�ǳ���������ֵʱ�䡣     
*  Parameters:
*       �ޡ�
*
*  Return value:
*           ���ص�һ�ΰ������º󷢵ڶ��ΰ�����Ϣ�ļ��ʱ�䡣����0��ʾ��������ֵ��ȷ��
*  Notes:
*          
****************************************************************************************************
*/
__u32 BSP_LRADCK_get_firstKeyDelay(void);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_set_rpKeyTime
*
*  Description:
*                   ���ð�����ס����ʱ�İ���������ϢƵ��ʱ�䡣          
*  Parameters:
*       �ޡ�
*
*  Return value:
*           �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*          
****************************************************************************************************
*/
__s32 BSP_LRADCK_set_rpKeyTime(__u32 repeat_time);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_get_rpKeyTime
*
*  Description:
*                   ��ȡ������ס����ʱ�İ���������ϢƵ��ʱ�䡣          
*  Parameters:
*       �ޡ�
*
*  Return value:
*           ���ذ�����ס����ʱ�İ���������ϢƵ��ʱ�䡣����0��ʾ��������ֵ��ȷ��
*  Notes:
*          
****************************************************************************************************
*/
__u32 BSP_LRADCK_get_rpKeyTime(void);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_LRADCK_lineCtrl_irq
*
*  Description:
*               �߿ؿ�����ر��ж�����,�߿�һ����Ҫ�������ж�Ϊfirst irq��last irq
*              
*  Parameters:
*
*       irq_type   :  �����ж����ͣ�first irq,data irq,keyup irq.
*       ctl: 0:disable��1:enable.
*
*  Return value:
*            �ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*           ֻ���ڳ�ʼ�������п����߿ع��ܴ˺�������ʹ�ã����򷵻�-1.
****************************************************************************************************
*/
__s32 BSP_LRADCK_lineCtrl_irq(__u32 irq_type, __u32 ctl);


#endif

/*
*********************************************************************************************************
*                                                           eBase
*                                           the Abstract of Hardware
*
*                                   (c) Copyright 2006-2010, AW China
*                                                   All Rights Reserved
*
* File        :  bsp_twi.h
* Date        :  2011-01-22
* Author      :  Victor
* Version     :  v1.00
* Description:  
*                                   Operation for TWI module,aw1619
* History     :
*      <author>          <time>             <version >          <desc>
*       Victor         2011-01-22              1.0           create this file    
*
*********************************************************************************************************
*/
#ifndef _BSP_TWI_H_
#define _BSP_TWI_H_


/* 7 bits or 10 bits slave address  */
#define TWI_SLAVE_ADDR_7BITS  0
#define TWI_SLAVE_ADDR_10BITS 1

/* slave's data register address length */
#define TWI_REG_ADDR_1_BYTE    1
#define TWI_REG_ADDR_2_BYTE    2
#define TWI_REG_ADDR_3_BYTE    3
#define TWI_REG_ADDR_4_BYTE    4

/* TWI write or read command */
#define TWI_WR_FLAG  0     
#define TWI_RD_FLAG  1

/* read or write format */
/* temporary support one types of write format and three types of read format */
#define TWI_WRITE_DATA_SPEC_RS            (0) //spec write
#define TWI_READ_DATA_SPEC_RS             (1) //spec read
#define TWI_READ_DATA_EX_NORS             (2) //no restart3
#define TWI_READ_DATA_EX_STPRS            (3) //stop + restart 

/* TWI ѡ����ѯ��ʽ�����жϷ�ʽ����*/
#define TWI_RW_POLLING_METHOD     1
#define TWI_RW_INTERRUPT_METHOD   0


#define TWI_SCLK_400KHZ    (400000) // 400kHz 
#define TWI_SCLK_100KHZ    (100000) //100kHz


typedef struct twi_para_set
{
    //��д��ʱ����Ҫ����Ĳ���
    __u16 slave_addr; //Slave��ַ
    __u8  slave_len;  //Slave��ַ����

    __u32 data_addr; //Slave���������ݼĴ�����ַ
    __u8  data_len; //Slave���������ݼĴ�����ַ����

    __u8  rw_flag; //����д��־λ��
    __u8  rw_format; //����ʽ��д��ʽ,�����ֹ淶�򲻹淶�Ķ�д��ʽ��

}TWI_PARA_SET_T;


typedef void (*TWI_CB)(__s32 ret);
/*   �ص�����TWI_CB�Ĳ���ret��ֵ���£��û��ɸ��ݷ���ֵ������ʹ�á�����Ŀɲ鿴spec
    0   : succeed
    -1  : fail            
    0xf8: On reset or stop the bus is idle            
    0xd8: second slave address has been transmitted; NOT ACK has been received            
    0x20: SLA+W has been transmitted; NOT ACK has been received   
    0x30: Data byte in I2CDAT has been transmitted; NOT ACK has been received
    0x48: SLA+R has been transmitted; NOT ACK has been received            
    0x58: Data byte has been received; NOT ACK has been transmitted 
*/

typedef struct twi_setting
{
    //��ʼ����������I2Cʱ��Ҫ����Ĳ���
    __s32  bus_num;
    __u32  sclk_req; //�û��趨�� 100kHz or 400kHz

    __u32  poll_flag;//0:ʹ���жϷ�ʽ��1:ʹ����ѯ��ʽ���ص���������ʵ�֡�
    // ��poll_flagΪ1ʱ�����Բ���д���漸���������ص���������ʵ�֡�
    //irq variable���ڲ������ж�ʹ��
    __u32  irq_no;
    __u32  irq_flags;
    __u32  irq_prio;    
    
    TWI_CB wakup_callback;//wakup the upper layer,�û�ʵ�ֻص�����

}TWI_SETTING_T;

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_init
*
*  Description:
*           ���TWI�Ļ�����ʼ�����ܣ������ڲ��ӿں��������üĴ�������������ߣ�����PIN�ź�APB clock��
*        ����twiģ��ʱ�ӣ���λ�ȡ����������ַ�������жϺ������жϴ��������ɹ��ϲ�init��ʼ��������
*
*  Parameters:
*       ioremap   :   �����ַ    
*       twi       :   �ⲿ����Դ���
*  Return value:
*           ��ʼ���ɹ�����0��ʧ�ܷ���-1��
*  Notes:
*         
****************************************************************************************************
*/
__s32 BSP_TWI_init(TWI_SETTING_T *twi);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_exit
*
*  Description:
*           ���TWI���˳������ܣ������ڲ��ӿں���������ر����ߣ�ֹͣʱ�ӣ�
*        ��λ�ȡ�ȡ���ж�ע�ᣬ�ͷ�twi��Դ������ɹ��ϲ�exit��ʼ��������
*       ��apbʱ�ӹرգ��ͷ�pin�š�
*  Parameters:
*       bus_num:  twiģ������ߺ�
*
*  Return value:
*         �˳��ɹ�����0��ʧ�ܷ���-1
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_exit(TWI_SETTING_T *twi);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_read
*
*  Description:
*               �������ݣ�����������������Ҫ���i2c��slave��ַ���Ĵ�����ַ���Լ�ѡ����ķ�ʽ��
*           Ŀǰ֧�����ֶ���ʽ�����淶��ʽ֧��7bit��10bit��ַ���������ֶ���ʽ֧��7���ص�ַ��10bit��ַ
*        �в���ȷ��
*
*  Parameters:
*            bus_num: twi���ߺ���
*           para   :  ���õĶ�д���ʽ    
*            buffer:  �������ݵĻ������׵�ַ
*            len   :  �������ݵĳ��ȡ�
*  Return value:
*           ���ɹ�����0,��Ҫpend��һ��ʧ�ܷ���-1,����Ҫpend;��ѯ��ʽ����ִ�лص�����-2���ⲿ��Ҫpend.
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_read(__s32 bus_num, TWI_PARA_SET_T *para, __u8 *buffer, __u32 len);
/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_write
*
*  Description:
*               �������ݣ���д������д����Ҫ���i2c��slave��ַ���Ĵ�����ַ���Լ�ѡ��д��ʽ��
*           Ŀǰ֧��һ��д��ʽ��д�淶��ʽ֧��7bit��10bit��ַ��
*
*  Parameters:
*           bus_num: twi���ߺ���
*           para   :  ���õĶ�д���ʽ  
*            buffer:  �������ݵĻ������׵�ַ
*            len   :  �������ݵĳ���
*  Return value:
*           д�ɹ�����0,��Ҫpend��һ��ʧ�ܷ���-1,����Ҫpend;��ѯ��ʽ����ִ�лص�����-2���ⲿ��Ҫpend.
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_write(__s32 bus_num, TWI_PARA_SET_T *para, const __u8 *buffer, __u32 len);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_set_clock
*
*  Description:
*              ���ù���ʱ�ӣ�scl��ʱ�ӡ�
*  Parameters:
*       busnum    :  twi�����ߺ�
*       sclk_reg : 100000 or 400000��100khz��400khz
*
*  Return value:
*         �˳��ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_set_clock(__s32 bus_num, __u32 sclk_req);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_get_line_status
*
*  Description:
*               �����i2cͨ�ų����ã�����SDA��SCL���������͵ȣ�ͨ���˽ӿ��û�����֪��SDA��SCL��״̬��
*           ���������������ڲ�����aw_twi_get_sda��aw_twi_get_sclʵ�֡�
*
*  Parameters:
*           bus_num:     TWIģ������ߺ�
*            sda_scl:  ѡ��SDA��SCL��0��SDA��1��SCL.
*  Return value:
*           ����sda��scl��״̬���ߵ�ƽΪ1�� �͵�ƽΪ0�����󷵻�-1�� 
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_get_line_status(__s32 bus_num, __u32 sda_scl);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_set_line_status
*
*  Description:
*           ����SDA��SCL��״̬�������߻����ͣ�ʹ�ô˽ӿ�ǰӦ���ȵ���eBSP_twi_usr_ctrl�����û����ƹ��ܡ�
*        Ҫ�ر��û��Կ�twi״̬����Ҫ�����ⲿ�ӿ�eBSP_twi_self_ctrl��
*
*  Parameters:
*            bus_num    :  twi�����ߺ�
*            sda_scl:  ѡ��SDA��SCL��0��SDA��1��SCL.
*            hi_lo  :  1:�ߵ�ƽ��0���͵�ƽ
*  Return value:
*           ����sda��scl��״̬���ߵ�ƽΪ1�� �͵�ƽΪ0��
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_set_line_status(__s32 bus_num, __u32 sda_scl, __u32 hi_low);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_TWI_line_ctrl
*
*  Description:
*               ����SDA��SCL���Ƿ����ܿ�״̬��ע��������ֱ�ӿ�����ر�SDA��SCL���ܿ�״̬��
*            �˺����ر�SDA��SCL�ܿ�״̬�������Կ�״̬��
*
*  Parameters:
*            bus_num    :  twi�����ߺ�
*            sda_scl:  ѡ��SDA��SCL��0��SDA��1��SCL.
*            ctl    :  0���ر��û����ƣ������Կء�1��ʹ���û����ƣ��û����Կ���SDA��SCL�ĵ�ƽ��
*  Return value:
*          �ɹ�����EBSP_TRUE,ʧ�ܷ���EBSP_FALSE.
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_TWI_line_ctrl(__s32 bus_num, __u32 sda_scl, __u32 ctl);

#endif

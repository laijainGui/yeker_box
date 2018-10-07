/*
*********************************************************************************************************
*                                     eBase
*                           the Abstract of Hardware
*
*                   (c) Copyright 2006-2010, AW China
*                                  All Rights Reserved
*
* File           :  bsp_spi.h
* Date         :  2011-02-12
* Author      :  Victor
* Version     :  v1.00
* Description:  
*               Operation for SPI module,aw1619
* History     :
*      <author>          <time>             <version >          <desc>
*       Victor         2011-02-12              1.0           create this file     
*********************************************************************************************************
*/

#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_


/* user define call back function,ret */
/*1: slaveģʽ�»��Ѷ��̣߳�0:�ɹ���-1:ʧ�� -2:��û��������̾�ʧ�ܣ� */


/* 
* 1.��ʼ��ʱ�����Խ�Ƭѡ�źſ���'|'����������ʾ������һ·Ƭѡ��
*   ����: (1) ����Ƭѡcs1,�� cs_bitmap = SPI_CHIP_SELECT_CS1;
*         (2) ����cs0��cs1,��cs_bitmap = SPI_CHIP_SELECT_CS0|SPI_CHIP_SELECT_CS1; 
*
* ��дʱ��SPIĳһ��ʱ��ֻ�ܶ�һ��Ƭѡ��Ч����chip_select��ֵ��
*   ����: ���ö�д�ӿ�ʱ��Ҫָ��CS2,chip_select = SPI_CHIP_SELECT_CS2;
*/
#define SPI_CHIP_SELECT_CS0 (0x01)
#define SPI_CHIP_SELECT_CS1 (0x02)
#define SPI_CHIP_SELECT_CS2 (0x04)
#define SPI_CHIP_SELECT_CS3 (0x08)


/* ����config��bitλ */
/*
*       ����ģʽ������4�֣�
*         0: ����ģʽ0��POL=0,PAL=0;
*         1: ����ģʽ1��POL=0,PAL=1;
*         2: ����ģʽ2��POL=1,PAL=0;
*         3: ����ģʽ3��POL=1,PAL=1;
*/
#define SPI_PHA_ACTIVE		    (0x01)
#define SPI_POL_ACTIVE		    (0x02)

#define SPI_MODE_0_ACTIVE		(0|0)
#define SPI_MODE_1_ACTIVE		(0|SPI_PHA_ACTIVE)
#define SPI_MODE_2_ACTIVE		(SPI_POL_ACTIVE|0)
#define SPI_MODE_3_ACTIVE		(SPI_POL_ACTIVE|SPI_PHA_ACTIVE) /*Ĭ��Ϊģʽ3*/
/* ������������ */
#define SPI_CS_HIGH_ACTIVE		    (0x04)  /*Ĭ��ΪƬѡ�͵�ƽ��Ч�����͵�ƽѡ��Ƭѡ*/
#define SPI_LSB_FIRST_ACTIVE		(0x08)  /*Ĭ��Ϊ�ȷ���MSB�����ȷ������λ*/

#define SPI_DUMMY_ONE_ACTIVE        (0x10)  /*Ĭ��Ϊ����ʱspi�������Զ����0����txFIFO */
#define SPI_RECEIVE_ALL_ACTIVE      (0x20)  /*Ĭ��Ϊ�������õ�burst�������͵�ʱ�����rxFIFO���յ����� */

#define SPI_RAPID_MODE_ACTIVE       (0x40) /* Ĭ��Ϊһ��ͨ���ٶȣ�ֻ����>= 80MHz��ʱ���²���Ҫ��������� */


/*���ó�ʼ������ʱʹ��*/
typedef struct aw_spi_info
{
    __s32 bus_num;
    __u32 master;//1:master;0:slaveģʽ
    __u32 config; //POL&PHA; SS_HIGH,BIT_PER_WORD
    __u32 num_chipselect;// 1,2,3,4��20ʹ���������������ٸ�cs
    __u32 cs_bitmap;/*��ʾspi bus������Ƭѡλ�� */
    __u32 bits_per_word;/* 0: 8 bit; 1:16 bit��Ĭ��Ϊ8 */
    __u32 spi_clk;/* spi clock,�û�Ҫ���ʱ��,Ĭ��Ϊ10Mhz */      
        
    // �����ж�
    __u32 irq_no;
    __u32 irq_flags;
    __u8  irq_prio;

    /* һ���÷�: 
     *   a. poll_method = 1;dma_poll = 1;
     *   b. poll_method = 0;dma_poll = 0;
     *
     *   ʹ���жϻ�����ѯ��ʽ���� 0-�жϣ�1-��ѯ��û��ע���жϺ���;
     *   ֻ��masterģʽ����ʹ����ѯ��slaveģʽ��������ж���ɴ��䡣
     *
     *   һ����˵��ʹ��poll method=1����dma poll=1ʹ�ã�
     *   ʹ�ó���:û��dma�жϻ���irq�жϲ����á�
    */
    __u32 poll_method;

    /* ����С��������˵������CPU���䷽ʽ(����+��ѯ)���������á�
     *  ���ڴ����������䣬����DMA���õķ�ʽ���䡣
     *  ���У�DMA�ɲ���DMA+POLL����DMA+dma callback
     *
     *  1: ʹ��poll����ҪDMA�ص��������ڵ�ǰ�������DMA��Դ���ͷţ�
     *  0��ʹ��dma callback��ҪDMA�ص��������ڻص��������DMA��Դ���ͷš�   
     */ 
    __u32 dma_poll;/* dma����+dma callback��dma����+POLL */
  

    void (*wakeup_callback)(__s32 ret);//para:   

}__spi_info_t;

/* ��д��ʱ����Ҫ���õ���Ϣ */
typedef struct aw_spi_setting
{  
    __s32 bus_num;//intial which num      
    
/*ʹ�ú�SPI_CHIP_SELECT_CSx��ֵ,����SPI_CHIP_SELECT_CS0|SPI_CHIP_SELECT_CS1����ʾʹ��������cs����Ƭѡ��*/
    __u32 chip_select;
 
    __u32 bits_per_word;/* 0: 8 bit; 1:16 bit */
    
    __u32 config;   /* POL��PHA,CS_HIGH_ACTIVE,LSB��DUMMY */
    __u32 spi_clk;/* spi clock,�û�Ҫ���ʱ�� */      
  
}__spi_setting_t;



/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_init
*
*  Description:
*       ����Ĭ�ϵķ�ʽ���ã�ʹ��SPIģ�飬��Ϊmaster/slaveģʽ������DHB/DDB/SMC����λFIFO��
*   Ƭѡ�͵�ƽ��ЧSSPOL=0��burst�ڼ䱣�ֵ͵�ƽSSCTL=1�������ڲ���������Ƭѡ���ţ�
*   ����ʱ��AHB�������жϴ�������underrun/overflow������ģʽ0��DRQ�صȣ��������SPI�жϴ�������
*
*  Parameters:  
*       spi       :   �ⲿ����Դ���
*  Return value:
*       ��ʼ���ɹ�����0��ʧ�ܷ���-1
*  Notes:
*      
****************************************************************************************************
*/
__s32 BSP_SPI_init(__spi_info_t *spi);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_exit
*
*  Description:
*           ���SPI���˳������ܣ��ͷ�SPI��Դ������ر�SPI��
*       ȡ��ע��SPI�жϴ���������AHBʱ�ӹرգ��ͷ�pin�š�
*
*  Parameters:
*       spi:  �ⲿ����Դ���
*
*  Return value:
*         �˳��ɹ�����0��ʧ�ܷ���-1
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_SPI_exit(__spi_info_t *spi);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_master_txrx
*
*  Description:
*           masterģʽ�ɵ��ã�ͨ��spi����Դ�������dma_used��dma_pollѡ��ͬ�Ĵ��䷽ʽ��
*       �ڲ�����BC/WTC������masterģʽ��˵��һ���ȷ������д������֮���ٶ����������ʹ�ã�
*       DMA��ʽ��������INT��ʽ��POLL��ʽ��CPU���䷽ʽ����POLL��ʽ��������ɾ����ж�TC��ɻ����ϲ������߳�,
*       ��æ�ȳ���
*
*  Parameters:
*       spi:     �ⲿ����Դ���
*       tx_buf:  ����buffer�׵�ַ
*       tx_len:  �������ݳ���   
*       rx_buf:  ����buffer�׵�ַ
*       rx_len:  �������ݳ���   
*  Return value:
*       �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*       ��������У�ʼ�ձ���Ƭѡ��SMCģʽ���Զ����dummy������chipselect��ÿ������һ��transfer������
*   ����������Ƿ񱣳�Ƭѡ���ⲿ
****************************************************************************************************
*/
__s32 BSP_SPI_master_txrx (__spi_setting_t *spi, void *tx_buf, u32 tx_len, void *rx_buf, u32 rx_len);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_master_waitclk
*
*  Description:
*        ���õȴ�ʱ����Ŀ�� ��ÿ��data transfer �У�����N���ȴ�״̬��spiģ�����SPI_SCLK��ΪN��WCC��
*         ����һ��data transfer���ӳ١�
*
*  Parameters:
*         bus_num: spi�ļĴ�������  
*         waitclk_cnt:  ����ĵȴ�ʱ����Ŀ
*
*  Return value:
*         �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*       ������masterģʽ����Ч��
****************************************************************************************************
*/
__s32 BSP_SPI_master_waitclk(__s32 bus_num, __u32 waitclk_cnt);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_master_sampledly
*
*  Description:
*        ���ò�����ʱ�����ٴ�����ʹ�á�
*
*  Parameters:
*         bus_num: spi�ļĴ�������  
*         on_off:  1-�򿪣�0-�ر�
*
*  Return value:
*         �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*       ������master����Ч��
****************************************************************************************************
*/
__s32 BSP_SPI_master_sampledly(__s32 bus_num, __u32 on_off);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_set_mode
*
*  Description:
*         ����ģʽ����ģʽ��
*
*  Parameters:
*         bus_num: spi�ļĴ�������  
*         master: master/slaveģʽ��0��slave��1��master
*
*  Return value:
*         �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*   
****************************************************************************************************
*/
__s32 BSP_SPI_set_mode(__s32 bus_num, __u32 master);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_config
*
*  Description:
*         ʵ���ϵ��÷��ͻ���սӿ�ʱ���Ѿ�������������������ԡ�
*      master:������,ģʽ-POL,PHA,Ƭѡ����-SSPOL,����bitΪ��ʼ-LMTF,�Զ����0/1-DDB,������Чburst-DHB.
*      slave : POL,PHA,SSPOL,LMTF,
*
*  Parameters:
*       bus_num��  spi�����ߺ�
*       bitmap:   ���ò�����NULL��ʾ����Ĭ��ֵ��
*
*  Return value:
*       �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*           ÿ�δ�������У��Ѿ������˴˽ӿڵĲ����� 
****************************************************************************************************
*/
__s32 BSP_SPI_config(__s32 bus_num, __u32 bitmap);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_ss_ctrl
*
*  Description:
*         �ֹ�����chip select�źţ�enableΪ1���û�����Ƭѡ�ߵ͵�ƽ��0��SPI�������Զ�����SS��ƽ��
*     �û��������Ҫ����disable����masterģʽ�£������Զ�Ƭѡ�ź���Чʱ���ô˽ӿڣ�������19/20оƬ�С�
*
*  Parameters:
*       bus_num:   spi�����ߺ�
*       on_off: ʹ�ܲ�����0: disable,1:enable.
* 
*  Return value:
*          �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*   ע������
****************************************************************************************************
*/
__s32 BSP_SPI_cs_ctrl(__s32 bus_num, __u32 on_off);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_ss_level
*
*  Description:
*         �û�����Ƭѡ�ĸߵ͵�ƽ��ֻ��BSP_SPI_ctrl��Ƭѡ�趨Ϊ�û����ƺ�ʹ����������������塣
*     ��masterģʽ�£������Զ�Ƭѡ�ź���Чʱ���ô˽ӿڣ�������19/20оƬ�С�
*    (       __u32 cs_change;
*       ��ʾ��������У��Ƿ�ʼ�ձ���Ƭѡ,0��ʾ����Ƭѡ�������֮ǰһ����ͬ�򱣳�Ƭѡ��
*       ʵ�ֵ�ʱ�����20���ֶ�����Ƭѡ������һ��transfer��ʱ���������Ƭѡ��оƬ�����Ա���Ƭѡ .)
*  Parameters:
*         hSPI:  spi�ļĴ���������
*         hi_lo�����øߵ͵�ƽ��0: �͵�ƽ��1���ߵ�ƽ�� 
*
*  Return value:
*           �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*      
****************************************************************************************************
*/
__s32 BSP_SPI_cs_level(__s32 bus_num, __u32 hi_lo);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_slave_tx
*
*  Description:
*                slaveģʽ�ɵ��ã�ͨ��spi����Դ�������dma_used��dma_pollѡ��ͬ�Ĵ��䷽ʽ��
*        ����slaveģʽ��˵��һ�����յ��������������֮����д����������txFIFO empty��Ϊ��������жϡ� 
*       DMA��ʽ��������INT��ʽ��POLL��ʽ��CPU���䷽ʽ����POLL��ʽ������������ж�TE��ɻ����ϲ�����
*       �̻߳�æ�ȳ��򡣷��͹����У��ȹص�RR������ʲô���ݣ������ϲ�����ġ�
*       ������: ����TO��
*
*  Parameters:
*       spi:     �ⲿ����Դ���
*       tx_buf:  ����buffer�׵�ַ
*       tx_len:  �������ݳ���   
*
*  Return value:
*       �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*       slaveû�еȴ���ѯ��ʽ��
****************************************************************************************************
*/
__s32 BSP_SPI_slave_tx(__spi_setting_t *spi, void *tx_buf, __u32 tx_len);

/*
****************************************************************************************************
*
*  FunctionName:           BSP_SPI_slave_rx
*
*  Description:
*           slaveģʽ�ɵ��ã�ͨ��spi����Դ�������dma_used��dma_pollѡ��ͬ�Ĵ��䷽ʽ��
*       ����slaveģʽ��˵��һ�����յ��������������֮����д����������rxFIFO ready��Ϊ���տ�ʼ�жϣ�
*       �����ϲ����ʱ���������RR�жϣ���������ٿ���RR�жϣ�ע�����ʱҪ��txFIFO������ݣ���Ȼ����txFIFO
*       underrun���󣨿��Կ��ǹر�����жϣ������մ������������rxFIFO overflow��
*       DMA��ʽ��������INT��ʽ��POLL��ʽ��CPU���䷽ʽ����POLL��ʽ�����俪ʼ���ж�RR�����ϲ������̡߳�
*       ��������: RR-->�ر�RR-->���ñ��ӿڽ���-->���ݽ��յ��������-->�������ݣ�������������ݡ�
*
*  Parameters:
*       spi:     �ⲿ����Դ���
*       rx_buf:  ����buffer�׵�ַ
*       rx_len:  �������ݳ���   
*
*  Return value:
*       �ɹ�����EBSP_TRUE��ʧ�ܷ���EBSP_FALSE��
*  Notes:
*       slaveû�еȴ���ѯ��ʽ��
****************************************************************************************************
*/
__s32 BSP_SPI_slave_rx(__spi_setting_t *spi, void *rx_buf, u32 rx_len);



#endif

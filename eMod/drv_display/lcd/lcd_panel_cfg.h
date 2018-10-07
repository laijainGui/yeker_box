
#ifndef __LCD_PANNEL_CFG_H__
#define __LCD_PANNEL_CFG_H__

#include <string.h>
#include "epdk.h"

#define USE_MIPI_TM68
void LCD_io_init(__u32 sel);
void LCD_io_exit(__u32 sel);
void LCD_open_cmd(__u32 sel);
void LCD_close_cmd(__u32 sel);
void LCD_power_on(__u32 sel);
void LCD_power_off(__u32 sel);
void LCD_bl_open(__u32 sel);//��LCD����
void LCD_bl_close(__u32 sel);//�ر�LCD����

extern void LCD_OPEN_FUNC(__u32 sel, LCD_FUNC func, __u32 delay/*ms*/);
extern void LCD_CLOSE_FUNC(__u32 sel, LCD_FUNC func, __u32 delay/*ms*/);
extern void TCON_open(__u32 sel);//��LCD������
extern void TCON_close(__u32 sel);//�ر�LCD������
extern void LCD_delay(__u32 count);
extern void LCD_get_init_para(__lcd_panel_init_para_t *para);

extern void LCD_cpu_register_irq(__u32 sel, void (*Lcd_cpuisr_proc) (void));
extern void LCD_CPU_AUTO_FLUSH(__u32 sel,__u8 en);
extern void LCD_CPU_RD(__u32 sel,__u32 index,__u32 * data);
extern void LCD_CPU_WR_INDEX(__u32 sel,__u32 index);
extern void LCD_CPU_WR(__u32 sel, __u32 index, __u32 data);

#define BIT0      0x00000001  
#define BIT1		  0x00000002  
#define BIT2		  0x00000004  
#define BIT3		  0x00000008  
#define BIT4		  0x00000010  
#define BIT5		  0x00000020  
#define BIT6		  0x00000040  
#define BIT7		  0x00000080  
#define BIT8		  0x00000100  
#define BIT9		  0x00000200  
#define BIT10		  0x00000400  
#define BIT11		  0x00000800  
#define BIT12		  0x00001000  
#define BIT13		  0x00002000  
#define BIT14		  0x00004000  
#define BIT15		  0x00008000  
#define BIT16		  0x00010000  
#define BIT17		  0x00020000  
#define BIT18		  0x00040000  
#define BIT19		  0x00080000  
#define BIT20		  0x00100000  
#define BIT21		  0x00200000  
#define BIT22		  0x00400000  
#define BIT23		  0x00800000  
#define BIT24		  0x01000000  
#define BIT25		  0x02000000  
#define BIT26		  0x04000000  
#define BIT27		  0x08000000  
#define BIT28		  0x10000000  
#define BIT29		  0x20000000  
#define BIT30		  0x40000000  
#define BIT31		  0x80000000 

#define sys_get_value(n)    (*((volatile __u8 *)(n)))          /* byte input */
#define sys_put_value(n,c)  (*((volatile __u8 *)(n))  = (c))   /* byte output */
#define sys_get_hvalue(n)   (*((volatile __u16 *)(n)))         /* half word input */
#define sys_put_hvalue(n,c) (*((volatile __u16 *)(n)) = (c))   /* half word output */
#define sys_get_wvalue(n)   (*((volatile __u32 *)(n)))          /* word input */
#define sys_put_wvalue(n,c) (*((volatile __u32 *)(n))  = (c))   /* word output */
#define sys_set_bit(n,c)    (*((volatile __u8 *)(n)) |= (c))   /* byte bit set */
#define sys_clr_bit(n,c)    (*((volatile __u8 *)(n)) &=~(c))   /* byte bit clear */
#define sys_set_hbit(n,c)   (*((volatile __u16 *)(n))|= (c))   /* half word bit set */
#define sys_clr_hbit(n,c)   (*((volatile __u16 *)(n))&=~(c))   /* half word bit clear */
#define sys_set_wbit(n,c)   (*((volatile __u32 *)(n))|= (c))    /* word bit set */
#define sys_cmp_wvalue(n,c) (c == (*((volatile __u32 *) (n))))
#define sys_clr_wbit(n,c)   (*((volatile __u32 *)(n))&=~(c))  

void delay_nus(__s32 us);
__s32 lcd_iic_write(__u8 slave_addr, __u16 sub_addr, __u8 *buf, __u32 len);
__s32 lcd_iic_read(__u8 slave_addr, __u8 sub_addr, __u8* buf, __s32 len);

int lcd_peripherals_init();
int lcd_peripherals_exit();

#endif


#include <apps.h>
#include "tongxin_demo.h"
#include "cp_i.h"
static int Bo_Te_Lv;
static int Jie_Ko_Way;
static int PC_38 = 2;
static __s32 xml_Lamp_Sent(char * cha,int delay);
static int Tong_Xin_ToInt(char cha);
static __s32 Jie_Ko_Pin(int port,int num,int data) ;
static void Lamp_Sent_Change_botelv(int botelv);
static __s32 Lamp_Sent(unsigned char * packet,int len);

/*=======> Lihan 20160127
	485 �շ�����Pin��: 0 = Tx, 1 = Rx	
 */
static __hdle _stat_485;

/* <======
 */


static int Tong_Xin_ToInt(char cha)
	{
		int cnt;
		if(cha > 90){
			cha = cha - 32;
		}
		cnt = 0;
		switch(cha){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				cnt = SLIB_atoi(&cha);
				break;
			case 'A':
				cnt = 10;
				break;
			case 'B':
				cnt = 11;
				break;
			case 'C':
				cnt = 12;
				break;
			case 'D':
				cnt = 13;
				break;
			case 'E':
				cnt = 14;
				break;
			case 'F':
				cnt = 15;
				break;
		}
		return cnt;
}

static char Tong_Xin_ToChar(int cha)
{
	char cnt;
	switch(cha){
		case 0:
			cnt = '0';
			break;
		case 1:
			cnt = '1';
			break;
		case 2:
			cnt = '2';
			break;
		case 3:
			cnt = '3';
			break;
		case 4:
			cnt = '4';
			break;
		case 5:
			cnt = '5';
			break;
		case 6:
			cnt = '6';
			break;
		case 7:
			cnt = '7';
			break;
		case 8:
			cnt = '8';
			break;
		case 9:
			cnt = '9';
			break;
		case 10:
			cnt = 'A';
			break;
		case 11:
			cnt = 'B';
			break;
		case 12:
			cnt = 'C';
			break;
		case 13:
			cnt = 'D';
			break;
		case 14:
			cnt = 'E';
			break;
		case 15:
			cnt = 'F';
			break;
	}
	return cnt;
}
static __s32 Jie_Ko_Pin(int port,int num,int data) 
{
	user_gpio_set_t gpio_set;
	 __hdle hvolume_ctrl = NULL;

	// gpio_set.name = "ea ctrl";
	 gpio_set.port = port;
	 gpio_set.port_num = num;
	 gpio_set.mul_sel = 1;
	 gpio_set.drv_level = 1;
	 gpio_set.pull = 1;
	 gpio_set.data = data;

	 hvolume_ctrl = esPINS_PinGrpReq(&gpio_set, 1);
	if (!hvolume_ctrl)
	{
		__wrn("request Power Off pin failed\n");
		return EPDK_FAIL;
	}

	esPINS_WritePinData(hvolume_ctrl, data, NULL);
	esPINS_PinGrpRel(hvolume_ctrl, 2);
	return EPDK_OK;
}

static void Lamp_Sent_Change_botelv(int botelv)
{
	ES_FILE * uart;
	//int bote;
	uart = eLIBs_fopen("b:\\BUS\\UART2", "r+");
	if (!uart) {
		LogE("Open UART 2 failed");
	}
	eLIBs_fioctrl(uart,UART_CMD_SET_BAUDRATE, 0, (void *)botelv);
	eLIBs_fclose(uart);
}

/* =======> Lihan 20160157
     485 �շ�����Pin�ţ�Ĭ��Ϊ����״̬��Pin������ߵ�ƽ
*/
static __hdle gpio_485_reg(void)
{
	__hdle hvolume_ctrl = NULL;
	user_gpio_set_t gpio_set;
	
	 // gpio_set.name = "ea ctrl";
	gpio_set.port = 1;
	gpio_set.port_num = 2;
	gpio_set.mul_sel = 1;
	gpio_set.drv_level = 1;
	gpio_set.pull = 1;
	gpio_set.data = 0;
	hvolume_ctrl = esPINS_PinGrpReq(&gpio_set, 1);
	if(hvolume_ctrl==0){
		__msg("gpio reg error\n");
		return  0;
	}
	return hvolume_ctrl;
}

static __s32 gpio_485_write(int data) 
{
	esPINS_WritePinData(_stat_485, data, NULL);
}

/* <=========
 */

static __s32 Lamp_Sent(unsigned char * packet,int len)
{
	ES_FILE * uart;
	uart = eLIBs_fopen("b:\\BUS\\UART2", "r+");
	if (!uart) {
		LogE("Open UART 2 failed");
		return EPDK_FAIL;
	}
	
	gpio_485_write(1);     // 485 Tx
	esKRNL_TimeDly(3);      // Delay
	//log_mi("len = %d\n",len);
	eLIBs_fwrite(packet, 1, len, uart);

	esKRNL_TimeDly(3);     // Delay
	gpio_485_write(0);   // 485 Rx
	
	eLIBs_fclose(uart);
	return EPDK_OK;
}
static __s32 xml_Lamp_Sent(char * cha,int delay)
{
	unsigned char * payload;
	int len;
	int i,j;
	len = (eLIBs_strlen(cha) + 1) / 3;
	payload = esMEMS_Malloc(0, len);
	//LogMI("cha = %s",cha);	
	for(i = 0,j = 0;i < len;i++,j++){
	  payload[i]= (Tong_Xin_ToInt(cha[j])<< 4) | (Tong_Xin_ToInt(cha[j + 1]));
	  j = j + 2;
	  //LogMI("payload[%d] = %d",i,payload[i]);	  
	}
	Lamp_Sent(payload,len);
	//LogMI("delay = %d",delay);	  
	len = delay / 10;
	if(delay != 0){
		if(len == 0){
			len = 1;
		}
	}
	//LogMI("len = %d",len);	  
	esKRNL_TimeDly(len);
	if(PC_38 != 0){//����Ĭ�϶˿�
	   PC_38 = 0;
	   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
    }
	esMEMS_Mfree(0, payload);
	return 1;
}

void XML_send_code(Test_handle * handler)
{
	Test_handle * desc;
	desc = (Test_handle *)handler;
	// 1
	if(desc->key_code1){
		if(SLIB_strcmp(desc->key_bus1,"RS232") == 0){
		   if(Jie_Ko_Way != 232){
			   Jie_Ko_Way = 232;
			   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
			   Jie_Ko_Pin(3,8,1);//nd0		 0�Ƿ�1����               �رշ���
		   }
		   //LogMI("key_bus = 232");	
		}else if(SLIB_strcmp(desc->key_bus1,"RS485") == 0){
		   if(Jie_Ko_Way != 485){
		   	   Jie_Ko_Way = 485;
			   //Jie_Ko_Pin(1,5,0);//���� 0�Ƿ�1����
			   Jie_Ko_Pin(3,8,0);//nd0       0�Ƿ�1����             ��������
		   }
		   //LogMI("key_bus = 485");	
		}
		if(SLIB_atoi(desc->key_baurate1) > 0){
			if(Bo_Te_Lv != SLIB_atoi(desc->key_baurate1)){
				Bo_Te_Lv = SLIB_atoi(desc->key_baurate1);
				Lamp_Sent_Change_botelv(Bo_Te_Lv);//������
			}
		}
	   xml_Lamp_Sent(desc->key_code1,SLIB_atoi(desc->key_delay1));//��ʱ������
	}
}

__s32 Button_Id_Bug(char * cha)
{
	unsigned char * payload;
	int len;
	int i,j;
	len = (eLIBs_strlen(cha) + 1) / 3;
	payload = esMEMS_Malloc(0, len);
	//LogMI("cha = %s",cha);	
	for(i = 0,j = 0;i < len;i++,j++){
	  payload[i]= (Tong_Xin_ToInt(cha[j])<< 4) | (Tong_Xin_ToInt(cha[j + 1]));
	  j = j + 2;
	  //LogMI("payload[%d] = %d",i,payload[i]);   
	}
	//Lamp_Sent(payload,len);
	esMEMS_Mfree(0, payload);
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////

void send_button_code_2(char * cha,int delay,char * array_in,char * array_out)
{
   int char_len,in_len,out_len;//���ݳ���
   int i,k;
   int place;//״̬����λ 0 ��ʼ1�ж���ʱ2��ʱ�жϽ���
   char * xml_Send_Date_Char;//������������ʱ����cha ��int��λ
   int ChuLi_ShuJu_Wei;//�ַ���������λ��
   char_len = eLIBs_strlen(cha); 
   in_len = eLIBs_strlen(array_in);  
   out_len = eLIBs_strlen(array_out);
   i = place = k =0;
   xml_Send_Date_Char = (char *)esMEMS_Malloc(0,(char_len + in_len + out_len - 7));// 9 = [in] + [out]
   
   for(ChuLi_ShuJu_Wei = 0,k = 0;k < (char_len + in_len + out_len - 7);ChuLi_ShuJu_Wei++){
	  if(cha[ChuLi_ShuJu_Wei]=='[' && cha[ChuLi_ShuJu_Wei + 1]=='i'){
		 place = 1;
		 for(i = 0;i < in_len;i++){
			 xml_Send_Date_Char[k] = array_in[i];
			 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
			 k++;
		 }
	  }
	  if(cha[ChuLi_ShuJu_Wei]==']'){
		 place = 0;
		 ChuLi_ShuJu_Wei++;
	  }
	  if(cha[ChuLi_ShuJu_Wei]=='[' && cha[ChuLi_ShuJu_Wei + 1]=='o'){
		 place = 1;
		 if(xml_Send_Date_Char[k - 1] != ','){
		 	xml_Send_Date_Char[k] = ',';
			k++;
		 }
		 for(i = 0;i < out_len;i++){
			 xml_Send_Date_Char[k] = array_out[i];
			//LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
			 k++;
		 }
	  }
	  if(cha[ChuLi_ShuJu_Wei]==']'){
		 place = 0;
		 ChuLi_ShuJu_Wei++;
	  }
	  if(place == 0){
		 xml_Send_Date_Char[k] = cha[ChuLi_ShuJu_Wei];
		 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
		 k++;
	  }
   } 
   LogMI("xml_Send_Date_Char = %s",xml_Send_Date_Char);
   xml_Lamp_Sent(xml_Send_Date_Char,delay);
   esMEMS_Mfree(0, xml_Send_Date_Char);
}

/////////////////////////////////////////////////////////////////////////////////////

void send_button_code_2_1(char * cha,int delay,char * array_in,char * array_out)
{
   int char_len,in_len,out_len;//���ݳ���
   int i,k,code_number;
   int place;//״̬����λ 0 ��ʼ1�ж���ʱ2��ʱ�жϽ���
   char * xml_Send_Date_Char;//������������ʱ����cha ��int��λ
   int ChuLi_ShuJu_Wei;//�ַ���������λ��
   char_len = eLIBs_strlen(cha); 
   in_len = eLIBs_strlen(array_in);  
   out_len = eLIBs_strlen(array_out);
   i = place = k =0;
   code_number = char_len + in_len + out_len;
   if(in_len == 0){
   	 code_number = code_number - 4;
	 //i++;
   }else if(in_len > 0){
	   code_number = code_number - 4;
	   code_number++;
   }
   if(out_len == 0){
	  code_number = code_number - 5;
	 //i++;
   }else if(out_len > 0){
	   code_number = code_number - 5;
	   code_number++;
   }
	// LogMI("array_in = %s",array_in);
	// LogMI("array_out = %s",array_out);
   xml_Send_Date_Char = (char *)esMEMS_Malloc(0,code_number + 1);// 9 = [in] + [out]
   for(ChuLi_ShuJu_Wei = 0,k = 0;k < code_number;ChuLi_ShuJu_Wei++){
      if(array_in){
		  if(cha[ChuLi_ShuJu_Wei]=='[' && cha[ChuLi_ShuJu_Wei + 1]=='i'){
			 place = 0;
			 for(i = 0;i < in_len;i++){
				 xml_Send_Date_Char[k] = array_in[i];
				 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
				 k++;
			 }
		  }
	  }
	  if(array_out){
		  if(cha[ChuLi_ShuJu_Wei]=='[' && cha[ChuLi_ShuJu_Wei + 1]=='o'){
			 place = 0;
			 if(xml_Send_Date_Char[k - 1] != ','){
			 	if(k != 0){
					xml_Send_Date_Char[k] = ',';
					//LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
					k++;
				}
			 }
			 for(i = 0;i < out_len;i++){
				 xml_Send_Date_Char[k] = array_out[i];
				 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
				 k++;
			 }
		  }
	  }
	  
	  if(place == 0){
			// LogMI("cha[%d] = %c",ChuLi_ShuJu_Wei,cha[ChuLi_ShuJu_Wei]);
			 xml_Send_Date_Char[k] = cha[ChuLi_ShuJu_Wei];
			// LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
		 if(cha[ChuLi_ShuJu_Wei] == '0' || cha[ChuLi_ShuJu_Wei] == '1' || cha[ChuLi_ShuJu_Wei] == '2' || cha[ChuLi_ShuJu_Wei] == '3'
		 	 || cha[ChuLi_ShuJu_Wei] == '4' || cha[ChuLi_ShuJu_Wei] == '5' || cha[ChuLi_ShuJu_Wei] == '6' || cha[ChuLi_ShuJu_Wei] == '7'
		 	 || cha[ChuLi_ShuJu_Wei] == '8' || cha[ChuLi_ShuJu_Wei] == '9'){
			 k++;
		 }else if(cha[ChuLi_ShuJu_Wei] == 'a' || cha[ChuLi_ShuJu_Wei] == 'b' || cha[ChuLi_ShuJu_Wei] == 'c'
		  || cha[ChuLi_ShuJu_Wei] == 'd' || cha[ChuLi_ShuJu_Wei] == 'e' || cha[ChuLi_ShuJu_Wei] == 'f'){
			 k++;
		 }else if(cha[ChuLi_ShuJu_Wei] == 'A' || cha[ChuLi_ShuJu_Wei] == 'B' || cha[ChuLi_ShuJu_Wei] == 'C'
		  || cha[ChuLi_ShuJu_Wei] == 'D' || cha[ChuLi_ShuJu_Wei] == 'E' || cha[ChuLi_ShuJu_Wei] == 'F'){
			 k++;
		 }else if(cha[ChuLi_ShuJu_Wei] == ','){
		     if(k > 0){
				 if(xml_Send_Date_Char[k - 1] != ','){
					 k++;
				 }
			 }
		 }else if(cha[ChuLi_ShuJu_Wei] == NULL){
			 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
		     break;
		 }
	  }
	  //LogMI("k = %d,ChuLi_ShuJu_Wei = %d",k,ChuLi_ShuJu_Wei);
   } 
   //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
   //LogMI("cha[%d] = %c",ChuLi_ShuJu_Wei,cha[ChuLi_ShuJu_Wei]);
   LogMI("xml_Send_Date_Char = %s",xml_Send_Date_Char);
   xml_Lamp_Sent(xml_Send_Date_Char,delay);
   esMEMS_Mfree(0, xml_Send_Date_Char);
}

void send_button_code_1(char * cha,int delay,int slider_value)
{
   int char_len,in_len;//���ݳ���
   int i,k;
   int place;//״̬����λ 0 ��ʼ1�ж���ʱ2��ʱ�жϽ���
   char * xml_Send_Date_Char;//������������ʱ����cha ��int��λ
   unsigned char * xml_Send_Date_value;
   int ChuLi_ShuJu_Wei;//�ַ���������λ��
  
   char_len = eLIBs_strlen(cha) + 1; 
   i = place = k =0;
   if(slider_value > 255){
	   xml_Send_Date_value = (unsigned char *)esMEMS_Malloc(0,5);
	   xml_Send_Date_value[0] = Tong_Xin_ToChar(slider_value/256/16);
	   xml_Send_Date_value[1] = Tong_Xin_ToChar(slider_value/256%16);
	   xml_Send_Date_value[2] = ',';
	   xml_Send_Date_value[3] = Tong_Xin_ToChar(slider_value%256/16);
	   xml_Send_Date_value[4] = Tong_Xin_ToChar(slider_value%256%16);
	   in_len = 5;
   }else{
	   xml_Send_Date_value = (unsigned char *)esMEMS_Malloc(0,2);
	   xml_Send_Date_value[0] = Tong_Xin_ToChar(slider_value%256/16);
	   xml_Send_Date_value[1] = Tong_Xin_ToChar(slider_value%256%16);
	   in_len = 2;
   }
   xml_Send_Date_Char = (char *)esMEMS_Malloc(0,char_len + in_len);
   for(ChuLi_ShuJu_Wei = 0,k = 0;ChuLi_ShuJu_Wei < char_len ;ChuLi_ShuJu_Wei++){
	  if(cha[ChuLi_ShuJu_Wei]=='[' && cha[ChuLi_ShuJu_Wei + 1]=='v'){
		 place = 1;
		 for(i = 0;i < in_len;i++){
			 xml_Send_Date_Char[k] = xml_Send_Date_value[i];
			 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
			 k++;
		 }
	  }else if(cha[ChuLi_ShuJu_Wei]==']'){
		 place = 0;
		 ChuLi_ShuJu_Wei++;
	  }
	  if(place == 0){
		 xml_Send_Date_Char[k] = cha[ChuLi_ShuJu_Wei];
		 //LogMI("xml_Send_Date_Char[%d] = %c",k,xml_Send_Date_Char[k]);
		 k++;
	  }
   } 
   //LogMI("xml_Send_Date_Char = %s",xml_Send_Date_Char);
   xml_Lamp_Sent(xml_Send_Date_Char,delay);
   esMEMS_Mfree(0, xml_Send_Date_Char);
   esMEMS_Mfree(0, xml_Send_Date_value);
}
static void send_button_code(char * baurate,char * datas,char * delay)
{
	if(SLIB_atoi(baurate) > 0){
		if(Bo_Te_Lv != SLIB_atoi(baurate)){
			Bo_Te_Lv = SLIB_atoi(baurate);
			Lamp_Sent_Change_botelv(Bo_Te_Lv);//������
		}
	}
	xml_Lamp_Sent(datas,SLIB_atoi(delay));//��ʱ������
}
void Send_ButtonCode_Normal(char * port,char * baurate,char * datas,char * delay)
{//�˿ڣ� �����ʣ����ݣ���ʱ
    char * duanko;
	int len;
	duanko = port;
	if(datas){
		if(SLIB_strcmp(duanko,"GPIO_1") == 0){
			Jie_Ko_Pin(3,9,SLIB_atoi(baurate)); //pc 9
			len = SLIB_atoi(delay) / 10;
			if(SLIB_atoi(delay) != 0){
				if(len == 0){
					len = 1;
				}
				esKRNL_TimeDly(len);
			}
		}else if(SLIB_strcmp(duanko,"GPIO_2") == 0){
			Jie_Ko_Pin(3,10,SLIB_atoi(baurate));//pc 10
			len = SLIB_atoi(delay) / 10;
			if(SLIB_atoi(delay) != 0){
				if(len == 0){
					len = 1;
				}
				esKRNL_TimeDly(len);
			}
		}else if(SLIB_strcmp(duanko,"GPIO_3") == 0){
			Jie_Ko_Pin(3,14,SLIB_atoi(baurate));//pc 14
			//Jie_Ko_Pin(1,5,SLIB_atoi(baurate));       //pa5
			len = SLIB_atoi(delay) / 10;
			if(SLIB_atoi(delay) != 0){
				if(len == 0){
					len = 1;
				}
				esKRNL_TimeDly(len);
			}
		}else if(SLIB_strcmp(duanko,"GPIO_4") == 0){
			Jie_Ko_Pin(3,11,SLIB_atoi(baurate));//pc 11
			len = SLIB_atoi(delay) / 10;
			if(SLIB_atoi(delay) != 0){
				if(len == 0){
					len = 1;
				}
				esKRNL_TimeDly(len);
			}
		}else if(SLIB_strcmp(duanko,"RS232_1") == 0){
			if(datas){
			   if(Jie_Ko_Way != 232){
				   Jie_Ko_Way = 232;
				   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
				   if(PC_38 != 1){
					   PC_38 = 1;
					   Jie_Ko_Pin(3,8,1);//nd0		 0�Ƿ�1���� 			  �رշ���
				   }
			   }
			   send_button_code(baurate,datas,delay);
			}
		}else if(SLIB_strcmp(duanko,"RS232_2") == 0){
			if(datas){
			   if(Jie_Ko_Way != 232){
				   Jie_Ko_Way = 232;
				   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
				   if(PC_38 != 0){
					   PC_38 = 0;
					   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
				   }
			   }
			   send_button_code(baurate,datas,delay);
			}
		}else if((SLIB_strcmp(duanko,"RS485_1") == 0)||(SLIB_strcmp(duanko,"RS485_2") == 0)
			            ||(SLIB_strcmp(duanko,"RS485_3") == 0)){
			if(datas){
			   if(Jie_Ko_Way != 485){
				   Jie_Ko_Way = 485;
				   //Jie_Ko_Pin(1,5,0);//���� 0�Ƿ�1����
				   if(PC_38 != 0){
					   PC_38 = 0;
					   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
				   }
			   }
			   send_button_code(baurate,datas,delay);
		    }
		}
	}
}
void Send_ButtonCode_Matrix(char * port,char * baurate,char * datas,char * delay,char * array_in,char * array_out)
{//�˿ڣ� ���أ��� ���ݣ� ��ʱ
	char * duanko;
	char * botelv;
	duanko = port;
	botelv = baurate;
	if(datas){
		if(SLIB_strcmp(duanko,"RS232_1") == 0){
		   if(Jie_Ko_Way != 232){
			   Jie_Ko_Way = 232;
			   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
			   if(PC_38 != 1){
				   PC_38 = 1;
				   Jie_Ko_Pin(3,8,1);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 232");	
		}else if(SLIB_strcmp(duanko,"RS232_2") == 0){
		   if(Jie_Ko_Way != 232){
			   Jie_Ko_Way = 232;
			   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
			   if(PC_38 != 0){
				   PC_38 = 0;
				   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 232");	
		}else if((SLIB_strcmp(duanko,"RS485_1") == 0)||(SLIB_strcmp(duanko,"RS485_2") == 0)
		            ||(SLIB_strcmp(duanko,"RS485_3") == 0)){
		   if(Jie_Ko_Way != 485){
			   Jie_Ko_Way = 485;
			   //Jie_Ko_Pin(1,5,0);//���� 0�Ƿ�1����
			   if(PC_38 != 0){
				   PC_38 = 0;
				   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 485");	
		}
		if(SLIB_atoi(botelv) > 0){
			if(Bo_Te_Lv != SLIB_atoi(botelv)){
				Bo_Te_Lv = SLIB_atoi(botelv);
				Lamp_Sent_Change_botelv(Bo_Te_Lv);//������
			}
		}
	   if(array_in){
	       send_button_code_2_1(datas, SLIB_atoi(delay), array_in, array_out);//�����뷢��
	   }else{
		   send_button_code_2_1(datas, SLIB_atoi(delay), array_in, array_out);//�����뷢��
	   }
	}
}
void Send_ButtonCode_Slider(char * port,char * baurate,char * datas,char * delay,int slider_value)
{//�˿ڣ� ���أ��� ���ݣ� ��ʱ
	char * duanko;
	char * botelv;
	duanko = port;
	botelv = baurate;
	if(datas){
		if(SLIB_strcmp(duanko,"RS232_1") == 0){
		   if(Jie_Ko_Way != 232){
			   Jie_Ko_Way = 232;
			   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
			   if(PC_38 != 1){
				   PC_38 = 1;
				   Jie_Ko_Pin(3,8,1);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 232");	
		}else if(SLIB_strcmp(duanko,"RS232_2") == 0){
		   if(Jie_Ko_Way != 232){
			   Jie_Ko_Way = 232;
			   //Jie_Ko_Pin(1,5,1);//���� 0�Ƿ�1����
			   if(PC_38 != 0){
				   PC_38 = 0;
				   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 232");	
		}else if((SLIB_strcmp(duanko,"RS485_1") == 0)||(SLIB_strcmp(duanko,"RS485_2") == 0)
		            ||(SLIB_strcmp(duanko,"RS485_3") == 0)){
		   if(Jie_Ko_Way != 485){
			   Jie_Ko_Way = 485;
			   //Jie_Ko_Pin(1,5,0);//���� 0�Ƿ�1����
			   if(PC_38 != 0){
				   PC_38 = 0;
				   Jie_Ko_Pin(3,8,0);//nd0		 0�Ƿ�1���� 			  �رշ���
			   }
		   }
		   //LogMI("key_bus = 485");	
		}
		if(SLIB_atoi(botelv) > 0){
			if(Bo_Te_Lv != SLIB_atoi(botelv)){
				Bo_Te_Lv = SLIB_atoi(botelv);
				Lamp_Sent_Change_botelv(Bo_Te_Lv);//������
			}
		}
	   send_button_code_1(datas,SLIB_atoi(delay),slider_value);//��ʱ������
	}
}

/* ======> Lihan 20160127
	485Ĭ��Ϊ����״̬
  */
void Uart_485_init(void)
{
	_stat_485 =  gpio_485_reg();
}
/* <=============
*/



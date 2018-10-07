
#ifndef H_SCROLLING_I_BENNIS_20130131
#define H_SCROLLING_I_BENNIS_20130131
#include "tongxin_demo.h"
#include "image_demo.h"
#include "zu_code_demo.h"//����������code�����
#define INVALIDATE_NULL         0
#define INVALIDATE_ALL          ((unsigned int)-1)
#define INVALIDATE_BUTTON       0x00000001
#define INVALIDATE_SLIDER       0x00000002
#define INVALIDATE_BACKGROUND   0x00000004
#define INVALIDATE_FOREGROUND   0x00000008

typedef struct {
    EWin_InheritInfo_ForHeader ewii;
    RECT wndRect;           // Window location which is relative to the whole scrolling control
} SCR_ScrollingWndInfo_ForHeader;

typedef struct {
    SCR_ScrollingWndInfo_ForHeader scrolling;
} SCR_ScrollingMainWinDescriptor;

typedef struct {
    SCR_ScrollingWndInfo_ForHeader scrolling;
    gg_handler pageNode;
    HTHEME background;
	unsigned long color_code; 
    void * backgroundData;
} SCR_ScrollingPageDescriptor;

typedef struct {
    SCR_ScrollingWndInfo_ForHeader scrolling;
    gg_handler buttonNode;
	
	//GUI_FONT * button_font;
	
    //HTHEME buttonOn;
	int buttonOn_id;
    //void * buttonOnData;
	//void * hSlider;
    //HTHEME buttonOff;
	int buttonOff_id;
    //void * buttonOffData;
	HTHEME buttonMove;
	void * buttonMoveData;
	int    imageview_num;                  //ͼƬ�� ��ʾ��ͼƬ���
	int    imageview_tal;                  //ͼƬ��ͼƬ����
		
	char * xml_button_controltype;         //��������
	char * xml_id;                         //��������
	char * xml_click_id;						   //��������
	
	int carray_type;                       //0��� 1 ����
	gg_char * key_up_code;                 //���������ݱ���( in / out )
	
    int buttonStatus;                      //����״̬
	int buttonStatus_old;                  //������һ��״̬
	int buttonStatus_close;                // 1 ����������0������
	int invalidate;
    unsigned inva;	

	int lampLimit;                         //������ �߶�/ ���
	int lampLimit_max;                     //���������ֵ
	int lampLimit_min;                     //��������Сֵ
	int lampLimit_height;                  //�������Ļ��� �߶�/ ���
	int lampValue;                         //����������λ��
	int old_lampValue;                     //��������һ������λ��
	int lampSlide;
	int lampStep;
	int value;                             //������ֵ
	int old_value;						   //��������һ�ε�ֵ
	int click_move;						   //�ܿ��ƶ�
	
	int word_x;                            //����x����
	int word_y;                            //����y����
	int word_size;                         //�����С��Ŀǰ�õ���ϵͳ�����С***************************
	int textview_chstr;                    //�ı����ı�id
	int word_id_on;                        //����id ����
	int word_id_off;                       //����id ����
	
	int page;                              //��ת����ת����ҳ
	unsigned long color_code;              //��ɫ
	
	ButtonCode_handle * code_handle;  //�������ݱ���
	Image_handle * image_date_handle;      //ͼƬ��ͼƬ���

} SCR_ScrollingButtonDescriptor;

extern H_WIN ScrollingAppendManage(char * name, SCR_ScrollingWndInfo_ForHeader * inherit);
extern H_WIN ScrollingAppendPage(char * name, SCR_ScrollingWndInfo_ForHeader * inherit, int size, gg_handler pageNode, H_WIN hLayer, __pGUI_WIN_CB wndProc);
extern H_WIN ScrollingAppendButton(char * name, SCR_ScrollingWndInfo_ForHeader * inherit, gg_handler buttonNode, __pGUI_WIN_CB wndProc);

typedef H_WIN (*BuilderCreate)(SCR_ScrollingWndInfo_ForHeader * inherit, gg_handler pageNode);
extern H_WIN SCR_ScrollingHostBuilder(EWin_InheritInfo_ForHeader * inherit, BuilderCreate create, gg_handler windowNode);
extern H_WIN ScrollingCreate_V0001(SCR_ScrollingWndInfo_ForHeader * inherit, gg_handler pageNode);
extern H_WIN ScrollingBorderWndCreate_V0001(char * name, SCR_ScrollingWndInfo_ForHeader * inherit);
extern void Normal_Return_DongZuo(char * toitemid,char * toitemstatus,int imageid,int groupid,char * father_toitemid);
void Onlyone_Return_DongZuo(char * toitemid,int groupid);
void Click_Return_DongZuo(char * toitemid,int if_only,int groupid);
void Array_Return_DongZuo(char * toitemid,int groupid);
void Main_Button_Up(char * toitemid,int relation,int relation_slave);
#endif


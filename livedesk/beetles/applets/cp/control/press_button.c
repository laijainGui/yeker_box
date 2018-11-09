#include "cp_i.h"
#include "scrolling_i.h"
#include "press_button.h"
#include "font_save_demo.h"

#if 0
__s32 press_button_proc(__gui_msg_t * msg)
{
    SCR_ScrollingItemDescriptor * wndDpt;
    press_button_t *press_button;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingItemDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		   //if_top_down_move = 1;
		}
		press_button  = (press_button_t *)esMEMS_Malloc(0, sizeof(press_button_t));
	    if (NULL == press_button) {
	        LogE("Malloc failed");
	        return NULL;
	    }
    	eLIBs_memset(press_button, 0, sizeof(press_button_t));
    	GUI_WinSetAddData(msg->h_deswin, (__u32)press_button);
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->item_node);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   press_button->text_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   press_button->text_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   press_button->text_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   //wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   //wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   press_button->text_color = hexToDec(Char_XML_Read + 2);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->item_node, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   press_button->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(press_button->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
		wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_MO;
		wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_MO] = msg->h_deswin;
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       press_button->text_id[0] = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       press_button->text_id[0] = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   press_button->text_id[1] = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       press_button->text_id[1] = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   press_button->bmp_id[0] = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   press_button->bmp_id[1] = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   press_button->status = 0;
	   wndDpt->item_node = NULL;
	   XML_Font_handle_Date(press_button->text_size, MW_SYS_FONT_PATH2);//���崴��
	   /*
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
		*/
  	  press_button->bmp_res[0].handle = user_theme_open(press_button->bmp_id[0]);
  	  press_button->bmp_res[0].data = user_theme_hdl2buf(press_button->bmp_res[0].handle);	
  	  press_button->bmp_res[1].handle = user_theme_open(press_button->bmp_id[1]);
  	  press_button->bmp_res[1].data = user_theme_hdl2buf(press_button->bmp_res[1].handle);		
	   break;
	   
    case GUI_MSG_DESTROY:
   	{
   		press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(press_button->code_handle){
			esMEMS_Mfree(0, press_button->code_handle);
		}
		user_theme_close(press_button->bmp_res[0].handle);
		user_theme_close(press_button->bmp_res[1].handle);
		
		esMEMS_Mfree(0, press_button);
        esMEMS_Mfree(0, wndDpt);
        break;
    }
		
    case GUI_MSG_PAINT:
    {
    	press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
    	
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(press_button->text_size,MW_SYS_FONT_PATH2);
			if(button_font){
				GUI_SetFont(button_font);
			}else{
				press_button->text_size= CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)press_button->text_color);
		  if (press_button->status) {
			  GUI_BMP_Draw(press_button->bmp_res[0].data, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
							  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
			  
		  	 if(press_button->text_id[0]){
				 user_langres_get_menu_text(press_button->text_id[0],str,100);
				 GUI_DispStringAt(str,press_button->text_x + wndDpt->scrolling.wndRect.x,press_button->text_y + wndDpt->scrolling.wndRect.y);
			 }
		  } else {
			  GUI_BMP_Draw(press_button->bmp_res[1].data, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
							  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
			 
			 if(press_button->text_id[1]){
				 user_langres_get_menu_text(press_button->text_id[1],str,100);
				 GUI_DispStringAt(str,press_button->text_x + wndDpt->scrolling.wndRect.x,press_button->text_y + wndDpt->scrolling.wndRect.y);
		     }
		 }				 
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
    }
		 
	case GUI_MSG_USER_GESTURE_MO:
	{
		press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_MO \n");
	    press_button->status = press_button->status ? 0 : 1;
	    wndDpt->inva = INVALIDATE_ALL;
	    GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
	    break;
	}
		
	case GUI_MSG_USER_GESTURE_CLICK:
	{
		press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK \n");
		//LogMI("wndDpt->xml_id %s\n",wndDpt->xml_id);
		//LogMI("Page_Number %d\n",Page_Number);
		//LogMI("wndDpt->xml_button_controltype %s\n",wndDpt->xml_button_controltype);
		//click_xml_id_name = father_xml_id_name = wndDpt->xml_id;
		//father_xml_id_relation = wndDpt->xml_button_controltype;
	     dsk_keytone_on();
		 press_button->status = 1;
		 wndDpt->inva = INVALIDATE_ALL;
		 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		 
		 Buttonhandle_Search_Up(press_button->code_handle);//������밴���ǵ���״̬ up
		 /*
		 //Find_Primary_Handle(wndDpt->xml_id);
		 Button_Status = press_button->status;
		
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������
		}
		wndDpt->buttonStatus_old= wndDpt->buttonStatus;
		*/
		break;
	}
		
    case GUI_MSG_USER_GESTURE_LPRESS:
    {
    	press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
    	
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_LPRESS \n");
	     //dsk_keytone_on();
	     press_button->status = 1;
	     wndDpt->inva = INVALIDATE_ALL;
	     GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		
		msgsend.id = GUI_MSG_USER_GESTURE_LPRESS;
		msgsend.h_deswin = GUI_WinGetParent(GUI_WinGetParent(msg->h_deswin));
		GUI_PostMessage(&msgsend);
		break;
	}
		#if 0
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
	{
		press_button_t *press_button = (press_button_t *)GUI_WinGetAddData(msg->h_deswin);
		
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			{
				if(msg->dwAddData2 == 1){//һ��
					if(wndDpt->buttonStatus != Button_Status){
						wndDpt->buttonStatus = Button_Status;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}else if(msg->dwAddData2 == 0){//ȡ��
					i = Button_Status ? 0 : 1;
					if(wndDpt->buttonStatus != i){
						wndDpt->buttonStatus = i;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"press") == 0){
			 wndDpt->xml_button_controltype = "press";
			 Find_Primary_Handle(wndDpt->xml_id);
		}
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
	}
		#endif
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 push_button_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		   //if_top_down_move = 1;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){//���ؼ�
		   wndDpt->xml_button_controltype = "onoff";
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
				  if (wndDpt->buttonStatus) {
				  	  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOn_id);
		              wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					  
				  	 if(wndDpt->word_id_on){
						 user_langres_get_menu_text(wndDpt->word_id_on,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
					 }
					 user_theme_close(wndDpt->buttonMove);
				  } else {
					  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOff_id);
					  wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					 
					 if(wndDpt->word_id_off){
						 user_langres_get_menu_text(wndDpt->word_id_off,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
				     }
					 user_theme_close(wndDpt->buttonMove);
				 }
/*				 
                             LogMI("eLIBs_strlen(str) (%d)", eLIBs_strlen(str));
				  str2[0] = str[0];
				  str2[1] = str[1];
				  str2[2] = str[2];
				  str2[3] = str[3];
				  GUI_DispStringAt(str2,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y + 20);
*/
				  //GUI_ClearRect(wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 10,
				  	     //  wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x + eLIBs_strlen(str) * 20,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 20);
						//Ӣ����һ��  ������ȫ��	
				    //GUI_DispStringAt("%",wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 20);
				 
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		 		 
		
	case GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR \n");
		if(wndDpt->buttonStatus_close == 1){
			break;
		}
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){//�����
			wndDpt->xml_button_controltype = "onoff";
			wndDpt->buttonStatus = msg->dwAddData2 ? 0 : 1;
			wndDpt->inva = INVALIDATE_ALL;
			GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		}
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK \n");
		LogMI("wndDpt->xml_id %s\n",wndDpt->xml_id);
		LogMI("Page_Number %d\n",Page_Number);
		LogMI("wndDpt->xml_button_controltype %s\n",wndDpt->xml_button_controltype);
		click_xml_id_name = father_xml_id_name = wndDpt->xml_id;
		father_xml_id_relation = wndDpt->xml_button_controltype;
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){
			dsk_keytone_on();
			wndDpt->xml_button_controltype = "onoff";
			if(wndDpt->buttonStatus_close == 0){
				wndDpt->buttonStatus = wndDpt->buttonStatus ? 0 : 1;
				wndDpt->inva = INVALIDATE_ALL;
				GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				
				if(wndDpt->buttonStatus == 1){
					Buttonhandle_Search_Up(wndDpt->code_handle);//�������
				}else{
					Buttonhandle_Search_Down(wndDpt->code_handle);//�������
				}
				
				Find_Primary_Handle(wndDpt->xml_id);
				Find_Onlyone_groupid(wndDpt->xml_id);
			}else if(wndDpt->buttonStatus_close == 10){
			    //if(wndDpt->buttonStatus == 1){
					wndDpt->buttonStatus = 0;
					if(wndDpt->buttonStatus_old == wndDpt->buttonStatus){
						break;
					}
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
					
					if(wndDpt->buttonStatus == 1){
						Buttonhandle_Search_Up(wndDpt->code_handle);//�������
					}else{
						Buttonhandle_Search_Down(wndDpt->code_handle);//�������
					}
					
					Find_Primary_Handle(wndDpt->xml_id);
					Find_Onlyone_groupid(wndDpt->xml_id);
				//}
			}else if(wndDpt->buttonStatus_close == 1){
				wndDpt->buttonStatus = wndDpt->buttonStatus ? 0 : 1;
				wndDpt->inva = INVALIDATE_ALL;
				GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				
				if(wndDpt->buttonStatus == 1){
					Buttonhandle_Search_Up(wndDpt->code_handle);//�������
				}else{
					Buttonhandle_Search_Down(wndDpt->code_handle);//�������
				}
				
				Find_Primary_Handle(wndDpt->xml_id);
				Find_Onlyone_groupid(wndDpt->xml_id);
			}
		}
		
		Button_Status = wndDpt->buttonStatus;
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������
		}
		wndDpt->buttonStatus_old= wndDpt->buttonStatus;
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
				if(msg->dwAddData2 == 1){//һ��
					if(wndDpt->buttonStatus != Button_Status){
						wndDpt->buttonStatus = Button_Status;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}else if(msg->dwAddData2 == 0){//ȡ��
					i = Button_Status ? 0 : 1;
					if(wndDpt->buttonStatus != i){
						wndDpt->buttonStatus = i;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){
			 wndDpt->xml_button_controltype = "onoff";
			 if(wndDpt->buttonStatus != wndDpt->buttonStatus_old){
				if(wndDpt->buttonStatus_close == 10){//�Ӽ��Ƕ�ѡһ ��ô���´���
					 if(wndDpt->buttonStatus == 0){
						 Find_Primary_Handle(wndDpt->xml_id);
						 Find_Onlyone_groupid(wndDpt->xml_id);//�´�
				     }else{
				         if(msg->dwAddData1 == 0){
							 Find_Primary_Handle(wndDpt->xml_id);//���������� ��click��������
						 }
					 }
				}else{
					 Find_Primary_Handle(wndDpt->xml_id);
			    }
			 }else{
				if(wndDpt->buttonStatus_close == 10){ 
				 	 if(wndDpt->buttonStatus == 0){
						 Find_Primary_Handle(wndDpt->xml_id);
						 Find_Onlyone_groupid(wndDpt->xml_id);//�´�
				     }
				}else{
					 Find_Primary_Handle(wndDpt->xml_id);
				}
		     }
		}
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_CONTRAL://��������ĸı�
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CONTRAL \n");
		father_xml_id_relation = wndDpt->xml_button_controltype;
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){
			wndDpt->xml_button_controltype = "onoff";
			if(wndDpt->buttonStatus_close == 10){
				wndDpt->buttonStatus_close = 10;
			}else{
			    wndDpt->buttonStatus_close = 1;
			}
		}
		break;
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){//������
				wndDpt->xml_button_controltype = "slider";
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status ? 0 : 1;
				}else{
					msgsend.id = GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR;
					msgsend.h_deswin = msg->h_deswin;
					msgsend.dwAddData2 = msg->dwAddData2 - 2;
					GUI_PostMessage(&msgsend);
				}
			}else if(SLIB_strcmp(wndDpt->xml_button_controltype,"imageview") == 0){//ͼƬ��
				wndDpt->xml_button_controltype = "imageview";
				i = XML_FindButtonState(father_xml_id_name);
				if(SLIB_strcmp(father_xml_id_relation,"press") == 0){
					if(i == 1){
						i = i - 1;
					}
				}
				if(i == 0){
					if(msg->dwAddData2 > 7){// 4+3=7
						wndDpt->imageview_num = msg->dwAddData2 - 7;
					}else if(msg->dwAddData2 == (2 + 4)){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}else if(msg->dwAddData2 == (3 + 4)){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 2){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 3){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}
				}
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status;
				}
				wndDpt->inva = INVALIDATE_ALL;
			}else{
				if(msg->dwAddData2 == 1){//һ��
					if(wndDpt->buttonStatus != Button_Status){
						wndDpt->buttonStatus = Button_Status;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}else if(msg->dwAddData2 == 0){//ȡ��
					i = Button_Status ? 0 : 1;
					if(wndDpt->buttonStatus != i){
						wndDpt->buttonStatus = i;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"press") == 0){
			 wndDpt->xml_button_controltype = "press";
			 //Find_Primary_Handle(wndDpt->xml_id);
		}else if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){
			 wndDpt->xml_button_controltype = "onoff";
			 if(wndDpt->buttonStatus != wndDpt->buttonStatus_old){
				 if(wndDpt->buttonStatus == 0){
					 //Find_Primary_Handle(wndDpt->xml_id);
					 Find_Onlyone_groupid(wndDpt->xml_id);//�´�
				 }
			 }
		}
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 slider_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){//������
		    wndDpt->xml_button_controltype = "slider";
			if(if_top_down_move == 0){
				wndDpt->scrolling.ewii.gestureArgs.attr_y |= GG_GESTURE_ATTR_SLIDE;
				wndDpt->scrolling.ewii.gestureArgs.hmsg_y[GG_GESTURE_MSG_DEST_SLIDE] = msg->h_deswin;
				wndDpt->lampLimit = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "height")));
			}else{
				wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_SLIDE;
				wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_SLIDE] = msg->h_deswin;
				wndDpt->lampLimit = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "width")));
			}
			wndDpt->lampLimit_min = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "min")));
			wndDpt->lampLimit_max = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "max")));
			wndDpt->lampLimit_height = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "slider_sticksize")));
			wndDpt->lampStep = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "step")));
			wndDpt->lampValue = 0;
			wndDpt->old_lampValue = wndDpt->lampValue + wndDpt->lampSlide;
		}
#ifdef THIS_DEBUG
	   LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
	   LogMI("wndDpt->scrolling.ewii.langid %d",wndDpt->scrolling.ewii.langid);
	   LogMI("wndDpt->xml_button_controltype %s",wndDpt->xml_button_controltype);
	   LogMI("Button location: %d,%d,%d,%d", wndDpt->scrolling.ewii.wndRect.x, wndDpt->scrolling.ewii.wndRect.y,
						   wndDpt->scrolling.ewii.wndRect.width, wndDpt->scrolling.ewii.wndRect.height);
	   LogMI("Button location which relative to scrolling control: %d,%d,%d,%d", wndDpt->scrolling.wndRect.x, wndDpt->scrolling.wndRect.y,
						   wndDpt->scrolling.wndRect.width, wndDpt->scrolling.wndRect.height);
#endif	   
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "slider_fore"))){//����
		   i = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "slider_fore")));
		   wndDpt->buttonMove = user_theme_open(i);
		   wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
	   }else{
		   wndDpt->buttonMove = NULL;
	   }	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
		   if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){//������
				wndDpt->xml_button_controltype = "slider";
				x = wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x;
				y = wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y;
				width = wndDpt->scrolling.ewii.wndRect.width;
				height = wndDpt->scrolling.ewii.wndRect.height;
				{
					if(if_top_down_move == 0){//����
						if((wndDpt->lampValue + wndDpt->lampSlide) > (height)){
							wndDpt->lampValue = height;
							wndDpt->lampSlide = 0;
						}
						if((wndDpt->lampValue + wndDpt->lampSlide) < (wndDpt->lampLimit_height)){
							wndDpt->lampValue = wndDpt->lampLimit_height;
							wndDpt->lampSlide = 0;
						}
						if(wndDpt->old_lampValue > (wndDpt->lampValue + wndDpt->lampSlide)){
							GUI_BMP_Draw(wndDpt->buttonMoveData,x,y + height - (wndDpt->lampValue + wndDpt->lampSlide));
							GUI_ClearRect(x,y + height - (wndDpt->old_lampValue),x + width,y + height - (wndDpt->lampValue + wndDpt->lampSlide));
							wndDpt->old_lampValue = wndDpt->lampValue + wndDpt->lampSlide;
						}else if(wndDpt->old_lampValue < (wndDpt->lampValue + wndDpt->lampSlide)){
							GUI_BMP_Draw(wndDpt->buttonMoveData, x,y + height - (wndDpt->lampValue + wndDpt->lampSlide));
							GUI_ClearRect(x,y + height - (wndDpt->lampValue + wndDpt->lampSlide) + wndDpt->lampLimit_height,x + width,
								y + height - (wndDpt->old_lampValue) + wndDpt->lampLimit_height);
							wndDpt->old_lampValue = wndDpt->lampValue + wndDpt->lampSlide;
						}
                        if(wndDpt->click_move == 0){					
						    wndDpt->value = ((wndDpt->lampValue + wndDpt->lampSlide) - 
								wndDpt->lampLimit_height) * wndDpt->lampLimit_max / (height - wndDpt->lampLimit_height);
						}else{
						    wndDpt->click_move = 0;
						}
						//LogMI("wndDpt->value = %d",wndDpt->value);
					}else if(if_top_down_move == 1){
						if((wndDpt->lampValue + wndDpt->lampSlide) > (width - wndDpt->lampLimit_height)){
							wndDpt->lampValue = width - wndDpt->lampLimit_height;
							wndDpt->lampSlide = 0;
						}
						if((wndDpt->lampValue + wndDpt->lampSlide) < 0){
							wndDpt->lampValue = 0;
							wndDpt->lampSlide = 0;
						}
						if(wndDpt->old_lampValue > (wndDpt->lampValue + wndDpt->lampSlide)){
							GUI_BMP_Draw(wndDpt->buttonMoveData, x + (wndDpt->lampValue + wndDpt->lampSlide), y);
							GUI_ClearRect(x + (wndDpt->lampValue + wndDpt->lampSlide) + wndDpt->lampLimit_height,y,x + wndDpt->old_lampValue + wndDpt->lampLimit_height,y + height);
							wndDpt->old_lampValue = wndDpt->lampValue + wndDpt->lampSlide;
						}else if(wndDpt->old_lampValue <= (wndDpt->lampValue + wndDpt->lampSlide)){
							GUI_BMP_Draw(wndDpt->buttonMoveData, x + (wndDpt->lampValue + wndDpt->lampSlide), y);
							GUI_ClearRect(x + wndDpt->old_lampValue,y,x + (wndDpt->lampValue + wndDpt->lampSlide),y + height);
							wndDpt->old_lampValue = wndDpt->lampValue + wndDpt->lampSlide;
						}
						if(wndDpt->click_move == 0){					
							if(width == wndDpt->lampLimit_height){
								wndDpt->value = 0;
							}else{
							    wndDpt->value = (wndDpt->lampValue + wndDpt->lampSlide) * wndDpt->lampLimit_max / 
									(width - wndDpt->lampLimit_height);
							}
						}else{
							wndDpt->click_move = 0;
						}
					}
					{
						GUI_ClearRect(wndDpt->scrolling.wndRect.x + wndDpt->word_x,wndDpt->scrolling.wndRect.y + wndDpt->word_y,
							 wndDpt->scrolling.wndRect.x + wndDpt->word_x + (wndDpt->word_size - wndDpt->word_size/2) * 3,wndDpt->scrolling.wndRect.y + wndDpt->word_y + wndDpt->word_size);
						if(wndDpt->value % wndDpt->lampStep > wndDpt->lampStep / 2){
							 wndDpt->value = (wndDpt->value / wndDpt->lampStep + 1) * wndDpt->lampStep;
						}else{
							 wndDpt->value = (wndDpt->value / wndDpt->lampStep + 0) * wndDpt->lampStep;
						}
						if(wndDpt->value >= wndDpt->lampLimit_max){
							wndDpt->value = wndDpt->lampLimit_max;
						}else if(wndDpt->value <= wndDpt->lampLimit_min){
							wndDpt->value = wndDpt->lampLimit_min;
						}
						//LogMI("wndDpt->value = %d",wndDpt->value);
						 if(wndDpt->value >= 100){
							 eLIBs_sprintf(str, "%d", wndDpt->value / 100);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
							 eLIBs_sprintf(str, "%d", wndDpt->value % 100 / 10);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x + wndDpt->word_size - wndDpt->word_size/2 * 1,wndDpt->scrolling.wndRect.y + wndDpt->word_y );
							 eLIBs_sprintf(str, "%d", wndDpt->value % 100 % 10);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x + wndDpt->word_size * 2 - wndDpt->word_size/2 * 2,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
							 //GUI_DispStringAt("%", wndDpt->scrolling.wndRect.x + wndDpt->word_x + 3 * wndDpt->word_size,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
						 }else if(wndDpt->value < 100 && wndDpt->value >= 10){
							 eLIBs_sprintf(str, "%d", wndDpt->value / 10);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
							 eLIBs_sprintf(str, "%d", wndDpt->value % 10);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x + wndDpt->word_size - wndDpt->word_size/2 * 1,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
							 //GUI_DispStringAt("%", wndDpt->scrolling.wndRect.x + wndDpt->word_x + 3 * wndDpt->word_size,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
						 }else if(wndDpt->value < 10 && wndDpt->value >= 0){
							 eLIBs_sprintf(str, "%d", wndDpt->value % 10);
							 GUI_DispStringAt(str, wndDpt->scrolling.wndRect.x + wndDpt->word_x ,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
							 //GUI_DispStringAt("%", wndDpt->scrolling.wndRect.x + wndDpt->word_x + 3 * wndDpt->word_size,wndDpt->scrolling.wndRect.y + wndDpt->word_y);
						 }
					 }
				}
			}
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		
	case GUI_MSG_USER_GESTURE_MOVE:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_MOVE \n");
		if(wndDpt->buttonStatus_close == 1){
			break;
		}
		 if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){			 
			 if(if_top_down_move == 0){
				 if (GG_GESTURE_DIR_TOP_DOWN != HISWORD(msg->dwAddData2)) {
					 break;
				 }
				 wndDpt->lampSlide = LOSWORD(msg->dwAddData2);
				 //LogMI(" wndDpt->lampSlide = %d", wndDpt->lampSlide);
				 //��Ҫ�Ӹ���ʾ�ж��Ƿ��ǵ�һ�βɼ����ݣ����ӣ���С��
			 }else{
				 if (GG_GESTURE_DIR_LEFT_RIGHT != HISWORD(msg->dwAddData2)) {
					 break;
				 }
				 wndDpt->lampSlide = -LOSWORD(msg->dwAddData2);
			 }
			 {
				 if (wndDpt->lampValue + wndDpt->lampSlide >= wndDpt->lampLimit ) {
					 wndDpt->lampSlide = wndDpt->lampLimit - wndDpt->lampValue;
				 } else if ((wndDpt->lampValue + wndDpt->lampSlide ) < wndDpt->lampLimit_min) {
					 wndDpt->lampSlide = 0;
					 wndDpt->lampValue = wndDpt->lampLimit_min;
				 } 
				 wndDpt->inva = INVALIDATE_ALL;
				 //LogMI("wndDpt->lampValue + wndDpt->lampSlide = %d",wndDpt->lampValue + wndDpt->lampSlide);
				 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
			 }
			 //��ֵ����10%�ŷ���
			 if(wndDpt->old_value > wndDpt->value){
				 if((wndDpt->old_value - wndDpt->value) > ((wndDpt->lampLimit_max - wndDpt->lampLimit_min) / 10)){
					 //�������ƶ�����
					 MoveSliderSendCode(wndDpt->code_handle,wndDpt->old_value,wndDpt->value,
						wndDpt->lampStep,(wndDpt->lampLimit_max - wndDpt->lampLimit_min) / 10);
					 wndDpt->old_value = wndDpt->value;
				 }
			 }else if(wndDpt->old_value < wndDpt->value){
				 if((wndDpt->value - wndDpt->old_value) > ((wndDpt->lampLimit_max - wndDpt->lampLimit_min) / 10)){
					 //�������ƶ�����
					 MoveSliderSendCode(wndDpt->code_handle,wndDpt->old_value,wndDpt->value,
						wndDpt->lampStep,(wndDpt->lampLimit_max - wndDpt->lampLimit_min) / 10);
					 wndDpt->old_value = wndDpt->value;
				 }
			 }else if(wndDpt->old_value == wndDpt->value){
				 //�������ƶ�����
				 if(wndDpt->value == wndDpt->lampLimit_min){
					 Down_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
				 }else if(wndDpt->value == wndDpt->lampLimit_max){
					 Up_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
				 }
			 }
		 }
		 break;
		 
	 case GUI_MSG_USER_GESTURE_DONE:
	 	LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_DONE \n");
	 	if(wndDpt->buttonStatus_close == 1){
			break;
		}
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){
			 width = wndDpt->scrolling.ewii.wndRect.width;
			 height = wndDpt->scrolling.ewii.wndRect.height;
			 if(if_top_down_move == 0){
				 if (GG_GESTURE_DIR_TOP_DOWN != HISWORD(msg->dwAddData2)) {
					 break;
				 }
			 }else{
				 if (GG_GESTURE_DIR_LEFT_RIGHT != HISWORD(msg->dwAddData2)) {
					 break;
				 }
			 }
			 if(wndDpt->value % wndDpt->lampStep > wndDpt->lampStep / 2){
			 	 wndDpt->value = (wndDpt->value / wndDpt->lampStep + 1) * wndDpt->lampStep;
			 }else{
				 wndDpt->value = (wndDpt->value / wndDpt->lampStep + 0) * wndDpt->lampStep;
			 }
			 if(if_top_down_move == 0){//320
				 wndDpt->lampValue = (height - wndDpt->lampLimit_height) * wndDpt->value / (wndDpt->lampLimit_max - wndDpt->lampLimit_min) + wndDpt->lampLimit_height;
			 }else{
				 wndDpt->lampValue = (width - wndDpt->lampLimit_height) * wndDpt->value / (wndDpt->lampLimit_max - wndDpt->lampLimit_min);
			 }
			 wndDpt->lampSlide = 0;
			 wndDpt->inva = INVALIDATE_ALL;
			 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
			 if(wndDpt->old_value > wndDpt->value){
				 Down_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);//���ƽ�������
			 }else if(wndDpt->old_value < wndDpt->value){
				 Up_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);//���ƽ�������
			 }else if(wndDpt->old_value == wndDpt->value){
				 if(wndDpt->value == wndDpt->lampLimit_min){
					 Down_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
				 }else if(wndDpt->value == wndDpt->lampLimit_max){
					 Up_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
				 }
			 }
			 wndDpt->old_value = wndDpt->value;
		 }
		 break;
		 
		
	case GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR \n");
		if(wndDpt->buttonStatus_close == 1){
			break;
		}
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){
		   wndDpt->xml_button_controltype = "slider";
		   //LogMI("msg->dwAddData2 = %d",msg->dwAddData2);
		   if(msg->dwAddData2 == 1){
				if(if_top_down_move == 0){//320
					 wndDpt->value += wndDpt->lampStep;
					 if(wndDpt->value >= wndDpt->lampLimit_max){
					 	 wndDpt->value = wndDpt->lampLimit_max;
					 }else if(wndDpt->value <= wndDpt->lampLimit_min){
						 wndDpt->value = wndDpt->lampLimit_min;
					 }
					 wndDpt->lampValue = (wndDpt->scrolling.ewii.wndRect.height - wndDpt->lampLimit_height)* wndDpt->value 
					 	          / (wndDpt->lampLimit_max - wndDpt->lampLimit_min) + wndDpt->lampLimit_height;
					 wndDpt->lampSlide = 0;
				}else if(if_top_down_move == 1){
					 wndDpt->value += wndDpt->lampStep;
					 if(wndDpt->value >= wndDpt->lampLimit_max){
						 wndDpt->value = wndDpt->lampLimit_max;
					 }else if(wndDpt->value <= wndDpt->lampLimit_min){
						 wndDpt->value = wndDpt->lampLimit_min;
					 }
					 wndDpt->lampValue = (wndDpt->scrolling.ewii.wndRect.width - wndDpt->lampLimit_height)* wndDpt->value / (wndDpt->lampLimit_max - wndDpt->lampLimit_min);
					 wndDpt->lampSlide = 0;
				}
		   	}else{
		   	    if(if_top_down_move == 0){//320
					 wndDpt->value -= wndDpt->lampStep;
					 if(wndDpt->value >= wndDpt->lampLimit_max){
						 wndDpt->value = wndDpt->lampLimit_max;
					 }else if(wndDpt->value <= wndDpt->lampLimit_min){
						 wndDpt->value = wndDpt->lampLimit_min;
					 }
					 wndDpt->lampValue = (wndDpt->scrolling.ewii.wndRect.height - wndDpt->lampLimit_height) * wndDpt->value
					 	      / (wndDpt->lampLimit_max - wndDpt->lampLimit_min) + wndDpt->lampLimit_height;
					 wndDpt->lampSlide = 0;
				}else if(if_top_down_move == 1){
					 wndDpt->value -= wndDpt->lampStep;
					 if(wndDpt->value >= wndDpt->lampLimit_max){
						 wndDpt->value = wndDpt->lampLimit_max;
					 }else if(wndDpt->value <= wndDpt->lampLimit_min){
						 wndDpt->value = wndDpt->lampLimit_min;
					 }
					 wndDpt->lampValue = (wndDpt->scrolling.ewii.wndRect.width - wndDpt->lampLimit_height) * wndDpt->value / (wndDpt->lampLimit_max - wndDpt->lampLimit_min);
					 wndDpt->lampSlide = 0;
				}
		   	}
		   //LogMI("wndDpt->value = %d",wndDpt->value);
		   wndDpt->click_move = 1;
		   if(wndDpt->old_value > wndDpt->value){
			   Down_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);//���ƽ�������
		   }else if(wndDpt->old_value < wndDpt->value){
			   Up_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);//���ƽ�������
		   }else if(wndDpt->old_value == wndDpt->value){
			   if(wndDpt->value == wndDpt->lampLimit_min){
				   Down_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
			   }else if(wndDpt->value == wndDpt->lampLimit_max){
				   Up_SliderSendCode(wndDpt->code_handle,wndDpt->lampStep,wndDpt->value);
			   }
		   }
		   wndDpt->old_value = wndDpt->value;
		   wndDpt->inva = INVALIDATE_ALL;
		   GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		}
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){//������
				wndDpt->xml_button_controltype = "slider";
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status ? 0 : 1;
				}else{
					msgsend.id = GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR;
					msgsend.h_deswin = msg->h_deswin;
					msgsend.dwAddData2 = msg->dwAddData2 - 2;
					GUI_PostMessage(&msgsend);
				}
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			if(SLIB_strcmp(wndDpt->xml_button_controltype,"slider") == 0){//������
				wndDpt->xml_button_controltype = "slider";
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status ? 0 : 1;
				}else{
					msgsend.id = GUI_MSG_USER_GESTURE_PAINT_NEIGHBOR;
					msgsend.h_deswin = msg->h_deswin;
					msgsend.dwAddData2 = msg->dwAddData2 - 2;
					GUI_PostMessage(&msgsend);
				}
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 imageview_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		   if_top_down_move = 1;
		}else{
			wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
			if_top_down_move = 0;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"imageview") == 0){//ͼƬ��
		   wndDpt->xml_button_controltype = "imageview";
		   group = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "image_total")));
		   imageid = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "image")));
		   wndDpt->image_date_handle = ImagehandleNew();
		   wndDpt->image_date_handle = Image_handle_add(wndDpt->image_date_handle,1,imageid);
		   
		   image_handler = GG_DOMGetBrotherElementByTagName(firstNode, "image");
		   wndDpt->imageview_tal = group;
		   for(i = 2;i <= group;i++){
			    image_handler = GG_DOMGetNextBrother(image_handler);
				imageid = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(image_handler, "image")));
				Image_handle_add(wndDpt->image_date_handle,i,imageid);
				//LogMI("imageid = %d",imageid);	  
		   }
		   wndDpt->imageview_num = 1;
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
		    if(SLIB_strcmp(wndDpt->xml_button_controltype,"imageview") == 0){
			  wndDpt->xml_button_controltype = "imageview";
			  imageid = Image_id_search(wndDpt->image_date_handle,wndDpt->imageview_num);
			  if(wndDpt->buttonOn_id != imageid){
				#if 0
				  GUI_ClearRect(wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y,
					   wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.width,
					   wndDpt->scrolling.ewii.wndRect.height) ;
				#endif
				  wndDpt->buttonOn_id = imageid;
			  }
			  //LogMI("imageid = %d",imageid);
			  //LogMI("wndDpt->imageview_num = %d",wndDpt->imageview_num);
			  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOn_id);
			  wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
			  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
							  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
			  user_theme_close(wndDpt->buttonMove);
			  Button_Status = wndDpt->imageview_num;
			  wndDpt->buttonStatus = imageid;
			  if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
				  father_xml_id_name2 = wndDpt->xml_id;
				  CFind_Primary_Toitemid(wndDpt->xml_id);//��������
			  }
			  wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		}
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			if(SLIB_strcmp(wndDpt->xml_button_controltype,"imageview") == 0){//ͼƬ��
				wndDpt->xml_button_controltype = "imageview";
				i = XML_FindButtonState(father_xml_id_name);
				if(SLIB_strcmp(father_xml_id_relation,"press") == 0){
					if(i == 1){
						i = i - 1;
					}
				}
				if(i == 0){
					if(msg->dwAddData2 > 7){// 4+3=7
						wndDpt->imageview_num = msg->dwAddData2 - 7;
					}else if(msg->dwAddData2 == (2 + 4)){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}else if(msg->dwAddData2 == (3 + 4)){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 2){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 3){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}
				}
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status;
				}
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			if(SLIB_strcmp(wndDpt->xml_button_controltype,"imageview") == 0){//ͼƬ��
				wndDpt->xml_button_controltype = "imageview";
				i = XML_FindButtonState(father_xml_id_name);
				if(SLIB_strcmp(father_xml_id_relation,"press") == 0){
					if(i == 1){
						i = i - 1;
					}
				}
				if(i == 0){
					if(msg->dwAddData2 > 7){// 4+3=7
						wndDpt->imageview_num = msg->dwAddData2 - 7;
					}else if(msg->dwAddData2 == (2 + 4)){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}else if(msg->dwAddData2 == (3 + 4)){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 2){
					   wndDpt->imageview_num -= 1;
					   if(wndDpt->imageview_num < 1){
						   wndDpt->imageview_num = 1;
					   }
					}else if(msg->dwAddData2 == 3){
					   wndDpt->imageview_num += 1;
					   if(wndDpt->imageview_num > wndDpt->imageview_tal){
						   wndDpt->imageview_num = wndDpt->imageview_tal;
					   }
					}
				}
				if(msg->dwAddData2 == 4){
					wndDpt->buttonStatus_close = Button_Status;
				}
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 textview_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"textview") == 0){//�ı���
		   wndDpt->xml_button_controltype = "textview";
		   wndDpt->textview_chstr = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "textview_text")));
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "slider_fore"))){//����
		   i = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "slider_fore")));
		   wndDpt->buttonMove = user_theme_open(i);
		   wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
	   }else{
		   wndDpt->buttonMove = NULL;
	   }	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
		   	if(SLIB_strcmp(wndDpt->xml_button_controltype,"textview") == 0){//�ı���
			     GUI_ClearRect(wndDpt->scrolling.wndRect.x,wndDpt->scrolling.wndRect.y,wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
				 user_langres_get_menu_text(wndDpt->textview_chstr,str,100);
				 //GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
				 GUI_DispStringAt(str,wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
				          wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
		   	}
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;

    default:
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 matrix_button_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"matrix") == 0){//�����
		   wndDpt->xml_button_controltype = "matrix";
		   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemio"));
		   wndDpt->key_up_code = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "key_up_code"));
		   group = Find_Array_groupnum(wndDpt->xml_id);
		   Save_Matrix_Static(group,0);
		   if(SLIB_strcmp(Char_XML_Read,"input") == 0){
			   wndDpt->carray_type = 1;//����
		   }else if(SLIB_strcmp(Char_XML_Read,"output") == 0){
			   wndDpt->carray_type = 0;//���
		   }else{
			   wndDpt->carray_type = -1;//�ĵ�����
		   }
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
		   	{
				  if (wndDpt->buttonStatus) {
				  	  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOn_id);
		              wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					  
				  	 if(wndDpt->word_id_on){
						 user_langres_get_menu_text(wndDpt->word_id_on,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
					 }
					 user_theme_close(wndDpt->buttonMove);
				  } else {
					  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOff_id);
					  wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					 
					 if(wndDpt->word_id_off){
						 user_langres_get_menu_text(wndDpt->word_id_off,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
				     }
					 user_theme_close(wndDpt->buttonMove);
				 }
			  }	
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		
	case GUI_MSG_USER_GESTURE_CLICK:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK \n");
		LogMI("wndDpt->xml_id %s\n",wndDpt->xml_id);
		LogMI("Page_Number %d\n",Page_Number);
		LogMI("wndDpt->xml_button_controltype %s\n",wndDpt->xml_button_controltype);
		click_xml_id_name = father_xml_id_name = wndDpt->xml_id;
		father_xml_id_relation = wndDpt->xml_button_controltype;
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"matrix") == 0){
			 dsk_keytone_on();
			 wndDpt->xml_button_controltype = "matrix";
			 group = Find_Array_groupnum(wndDpt->xml_id);// ��ȡ��ŵ�
			 if(wndDpt->carray_type == 1){
				 Save_Matrix_Static(group,1);
			 	 if(wndDpt->buttonStatus == 0){
				 	break;
				 }
				 Char_XML_Read = Item_code_return(group);//ȡ������code
				 //if(Char_XML_Read){
					 Find_Array_groupid(wndDpt->xml_id);// ui����
				 //}
				 if(!wndDpt->key_up_code){
				 	 ////�����ʼ��û�����ݴ���
				 	 wndDpt->key_up_code = NULL;
					 Item_Handle_Date(group,wndDpt->key_up_code);//��������code
				 }else{
					 Item_Handle_Date(group,wndDpt->key_up_code);//��������code
				 }
				 wndDpt->buttonStatus = 0;
				 wndDpt->inva = INVALIDATE_ALL;
				 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
			 }else if(wndDpt->carray_type == 0){
				 Char_XML_Read = Item_code_return(group);//ȡ������code
				 //LogMI("Char_XML_Read %s",Char_XML_Read);
				 //LogMI("wndDpt->key_up_code %s",wndDpt->key_up_code);
				 if(Char_XML_Read){
					 //if(wndDpt->key_up_code){
						 Buttonhandle_Search_2(wndDpt->code_handle,Char_XML_Read,wndDpt->key_up_code);
					 //}
				 }else{
					 //if(wndDpt->key_up_code){
						 Buttonhandle_Search_2(wndDpt->code_handle,Char_XML_Read,wndDpt->key_up_code);
					 //}
				 }
				 wndDpt->buttonStatus = 0;
				 wndDpt->inva = INVALIDATE_ALL;
				 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				 group = Find_Matrix_State(group);
				 LogMI("group %d",group);
				 if(group == 0){
					 msgsend.id = GUI_MSG_USER_GESTURE_CONTRAL;
					 msgsend.h_deswin = msg->h_deswin;
					 GUI_PostMessage(&msgsend);
				 }
			 }
			 break;
		}
		
		Button_Status = wndDpt->buttonStatus;
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������
		}
		wndDpt->buttonStatus_old= wndDpt->buttonStatus;
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Normal){
			{
				if(msg->dwAddData2 == 1){//һ��
					if(wndDpt->buttonStatus != Button_Status){
						wndDpt->buttonStatus = Button_Status;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}else if(msg->dwAddData2 == 0){//ȡ��
					i = Button_Status ? 0 : 1;
					if(wndDpt->buttonStatus != i){
						wndDpt->buttonStatus = i;
						wndDpt->inva = INVALIDATE_ALL;
					}
				}
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_CONTRAL://��������ĸı�
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CONTRAL \n");
		father_xml_id_relation = wndDpt->xml_button_controltype;
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"matrix") == 0){
			wndDpt->xml_button_controltype = "matrix";
			LogMI("wndDpt->carray_type %d",wndDpt->carray_type);
			if(wndDpt->carray_type == 0){
				LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
			}
		}
		break;
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 jump_button_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		   if_top_down_move = 1;
		}else{
			wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
			if_top_down_move = 0;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"jump") == 0){
		   wndDpt->xml_button_controltype = "jump";
		   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "jumpto"));
		   if(Char_XML_Read){
			     zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read)+1);
				 XML_GetChar_ToX(Char_XML_Read,zuid);
				 wndDpt->page = zuid[0];
				 esMEMS_Mfree(0, zuid);
		   	}else{
			     wndDpt->page = -1;
		   	}
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	   	   
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
		    {//�ǻ�����
		   	{
				  if (wndDpt->buttonStatus) {
				  	  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOn_id);
		              wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					  
				  	 if(wndDpt->word_id_on){
						 user_langres_get_menu_text(wndDpt->word_id_on,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
					 }
					 user_theme_close(wndDpt->buttonMove);
				  } else {
					  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOff_id);
					  wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					 
					 if(wndDpt->word_id_off){
						 user_langres_get_menu_text(wndDpt->word_id_off,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
				     }
					 user_theme_close(wndDpt->buttonMove);
				 }
/*				 
                             LogMI("eLIBs_strlen(str) (%d)", eLIBs_strlen(str));
				  str2[0] = str[0];
				  str2[1] = str[1];
				  str2[2] = str[2];
				  str2[3] = str[3];
				  GUI_DispStringAt(str2,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y + 20);
*/
				  //GUI_ClearRect(wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 10,
				  	     //  wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x + eLIBs_strlen(str) * 20,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 20);
						//Ӣ����һ��  ������ȫ��	
				    //GUI_DispStringAt("%",wndDpt->scrolling.ewii.word_x + wndDpt->scrolling.wndRect.x,wndDpt->scrolling.ewii.word_y + wndDpt->scrolling.wndRect.y + 20);
				 
			  }	
			}
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		
	case GUI_MSG_USER_GESTURE_CLICK:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK \n");
		LogMI("wndDpt->xml_id %s\n",wndDpt->xml_id);
		LogMI("Page_Number %d\n",Page_Number);
		LogMI("wndDpt->xml_button_controltype %s\n",wndDpt->xml_button_controltype);
		click_xml_id_name = father_xml_id_name = wndDpt->xml_id;
		father_xml_id_relation = wndDpt->xml_button_controltype;
	   if(SLIB_strcmp(wndDpt->xml_button_controltype,"jump") == 0){
			 wndDpt->xml_button_controltype = "jump";
			 if(wndDpt->page >= 0){
				 dsk_keytone_on();
				 if(if_top_down_move == 0){
				 	if(wndDpt->page > Page_Number){
						wndDpt->page = 1;
					}
					 msgsend.dwAddData2 = MAKELONG(wndDpt->page * 720,100);
				 } else if(if_top_down_move == 1){
					 if(wndDpt->page > Page_Number){
						 wndDpt->page = 1;
					 }
					 msgsend.dwAddData2 = MAKELONG(wndDpt->page * 720,100);
				 }
				 msgsend.id = GUI_MSG_USER_GESTURE_DONE;
				 msgsend.h_deswin = GUI_WinGetParent(GUI_WinGetParent(msg->h_deswin));
				 GUI_PostMessage(&msgsend);
			 }
			 break;
		}
		
		Button_Status = wndDpt->buttonStatus;
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������
		}
		wndDpt->buttonStatus_old= wndDpt->buttonStatus;
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"press") == 0){
			 wndDpt->xml_button_controltype = "press";
			 //Find_Primary_Handle(wndDpt->xml_id);
		}else if(SLIB_strcmp(wndDpt->xml_button_controltype,"onoff") == 0){
			 wndDpt->xml_button_controltype = "onoff";
			 if(wndDpt->buttonStatus != wndDpt->buttonStatus_old){
				 if(wndDpt->buttonStatus == 0){
					 //Find_Primary_Handle(wndDpt->xml_id);
					 Find_Onlyone_groupid(wndDpt->xml_id);//�´�
				 }
			 }
		}
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:
#ifdef THIS_DEBUG
        LogMI("Unhandled scrolling button window message (%d)", msg->id);
#endif
        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}

static __s32 delay_button_proc(__gui_msg_t * msg)
{
    SCR_ScrollingButtonDescriptor * wndDpt;
    gg_handler firstNode;
	gg_handler toiteNode;
    gg_handler node;
	GUI_FONT * button_font;
    RECT rect;
	int i,group,imageid;
	gg_char *Char_XML_Read;
	__gui_msg_t  msgsend;
	char str[100];
	//char str2[100];
	int x,y,width,height;
	gg_handler image_handler;
    wndDpt = (SCR_ScrollingButtonDescriptor *)GUI_WinGetAttr(msg->h_deswin);
    if ((!wndDpt) || (-1 == EWin_CheckInherit(&wndDpt->scrolling.ewii)) ||
        (!(wndDpt->scrolling.ewii.mask[0] & SCR_WNDINFOMASK_SBUTTON))) {
        LogE("Null or wrong scrolling button window data");
        return -1;
    }
    switch (msg->id) {
    case GUI_MSG_CREATE:
		LogMI("ButtonProcMsg: GUI_MSG_CREATE \n");
        // The following members must be set
        wndDpt->scrolling.ewii.hWnd = msg->h_deswin;
		wndDpt->scrolling.ewii.mask[0] |= SCR_WNDINFOMASK_GESTURE;
	    if(wndDpt->scrolling.ewii.gestureArgs.attr_y){
		   wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
		   wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
		   if_top_down_move = 1;
		}else{
			wndDpt->scrolling.ewii.gestureArgs.attr_x |= GG_GESTURE_ATTR_CLICK | GG_GESTURE_ATTR_LPRESS;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_CLICK] = msg->h_deswin;
			wndDpt->scrolling.ewii.gestureArgs.hmsg_x[GG_GESTURE_MSG_DEST_LPRESS] = msg->h_deswin;
			if_top_down_move = 0;
		}
	   // Setting end
	   firstNode = GG_DOMGetFirstChild(wndDpt->buttonNode);
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "x");
	   wndDpt->scrolling.ewii.wndRect.x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "y");
	   wndDpt->scrolling.ewii.wndRect.y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "width");
	   wndDpt->scrolling.ewii.wndRect.width = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "height");
	   wndDpt->scrolling.ewii.wndRect.height = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_x");
	   wndDpt->word_x = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_y");
	   wndDpt->word_y = SLIB_atoi(GG_DOMGetNodeValue(node));
	   node = GG_DOMGetBrotherElementByTagName(firstNode, "font_size");//�����С
	   wndDpt->word_size = SLIB_atoi(GG_DOMGetNodeValue(node));
	   
	   //wndDpt->button_font = GUI_SFT_CreateFont(wndDpt->word_size,MW_SYS_FONT_PATH2);
	   //wndDpt->word_size = wndDpt->scrolling.ewii.gdi.fontSize;//�����С ͨ�õ�

	   wndDpt->xml_button_controltype = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype")); 
	   wndDpt->xml_id = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "itemid"));
	   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "font_color"));
	   if(Char_XML_Read){
		   zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read));
		   XML_GetChar_ToX(Char_XML_Read,zuid);
		   wndDpt->color_code = (255*256*256*256+zuid[1]*256*256+zuid[2]*256+zuid[3]);
		   esMEMS_Mfree(0, zuid);
	   }
	   i = GG_DOMGetElementsByTagName(wndDpt->buttonNode, "item_code");
	   toiteNode = GG_DOMGetBrotherElementByTagName(firstNode, "item_code");
	   if(toiteNode){
		   wndDpt->code_handle = ButtonCodehandleNew();
		   Buttonhandle_add(wndDpt->code_handle,toiteNode,i,1);
	   }
	   // Window rectangle changed, sync to the window attribute
	   GG_FillRect(&rect, wndDpt->scrolling.wndRect.x + wndDpt->scrolling.ewii.wndRect.x,
						  wndDpt->scrolling.wndRect.y + wndDpt->scrolling.ewii.wndRect.y,
						  wndDpt->scrolling.ewii.wndRect.width,wndDpt->scrolling.ewii.wndRect.height);
	   GUI_WinSetWinRECT(msg->h_deswin, &rect);
	  if(SLIB_strcmp(wndDpt->xml_button_controltype,"delay") == 0){//��ʱ��
		   wndDpt->xml_button_controltype = "delay";
		   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "controltype"));
		   if(SLIB_strcmp(Char_XML_Read,"delayjump")){
			   Char_XML_Read = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "jumpto"));
			   if(Char_XML_Read){
					 zuid = (unsigned char *)esMEMS_Malloc(0,  eLIBs_strlen(Char_XML_Read)+1);
					 XML_GetChar_ToX(Char_XML_Read,zuid);
					 wndDpt->page = zuid[0];//��Ҫ��page ��һ�ŵ�host����
					 esMEMS_Mfree(0, zuid);
				}else{
				     wndDpt->page = -1;//��Ҫ��page ��һ�ŵ�host����
				}
		   }else{
			    LogMI("normal delay");
		   }
	   }
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on"))){
	       wndDpt->word_id_on = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_on")));
	   }else{
	       wndDpt->word_id_on = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off"))){
		   wndDpt->word_id_off = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "name_off")));
	   }else{
	       wndDpt->word_id_off = -1;
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release"))){
		   wndDpt->buttonOn_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_release")));
	   }
	   
	   if(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press"))){
		   wndDpt->buttonOff_id = SLIB_atoi(GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(firstNode, "icon_press")));
	   }	   
	      
	   wndDpt->old_value = wndDpt->value = 0;
	   wndDpt->buttonStatus_old = wndDpt->buttonStatus = 1;// 1 ���� 0 ����
	   wndDpt->buttonNode = NULL;
	   wndDpt->inva = INVALIDATE_ALL;
	   wndDpt->buttonStatus_close = 0;
	   XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
	   XML_haudongtiao_Handle_Date(msg->h_deswin,wndDpt->xml_id);//���水�������id
	   XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
	   if(Find_IfOnlyone(wndDpt->xml_id) >= 0){
		   wndDpt->buttonStatus_close = 10;
		}
	   break;
	   
    case GUI_MSG_DESTROY:
		LogMI("ButtonProcMsg: GUI_MSG_DESTROY \n");
		if(wndDpt->buttonMove){
			user_theme_close(wndDpt->buttonMove);
		}
		if(wndDpt->code_handle){
			esMEMS_Mfree(0, wndDpt->code_handle);
		}
		if(wndDpt->image_date_handle){
			esMEMS_Mfree(0, wndDpt->image_date_handle);
		}
        esMEMS_Mfree(0, wndDpt);
        break;
		
    case GUI_MSG_PAINT:
		LogMI("ButtonProcMsg: GUI_MSG_PAINT \n");
        if (wndDpt->inva) {
            GUI_LyrWinSel(wndDpt->scrolling.ewii.lyrHigher);
        }
		GUI_SetBkColor(0);
		if (INVALIDATE_BUTTON & wndDpt->inva) {
			GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);
			button_font = XML_Font_handle_Get_Font(wndDpt->word_size,MW_SYS_FONT_PATH2);
			//GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);
			//GUI_SetFont(wndDpt->button_font);
			if(button_font){
				//LogMI("font exit");
				GUI_SetFont(button_font);
			}else{
				//LogMI("have no font , system font ");
				wndDpt->word_size = CP_SYS_FONT_SIZE;
				//XML_Font_handle_Date(wndDpt->word_size,MW_SYS_FONT_PATH2);//���崴��
			    GUI_SetFont(wndDpt->scrolling.ewii.gdi.font);//ϵͳĬ������Ϊ20
			}
			//LogMI("wndDpt->word_size = %d",wndDpt->word_size);
			//GUI_SetFont(button_font);
			GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
			GUI_SetColor((GUI_COLOR)wndDpt->color_code);
		    {//�ǻ�����
		   	{
				  if (wndDpt->buttonStatus) {
				  	  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOn_id);
		              wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					  
				  	 if(wndDpt->word_id_on){
						 user_langres_get_menu_text(wndDpt->word_id_on,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
					 }
					 user_theme_close(wndDpt->buttonMove);
				  } else {
					  wndDpt->buttonMove = user_theme_open(wndDpt->buttonOff_id);
					  wndDpt->buttonMoveData = user_theme_hdl2buf(wndDpt->buttonMove);
					  GUI_BMP_Draw(wndDpt->buttonMoveData, wndDpt->scrolling.ewii.wndRect.x + wndDpt->scrolling.wndRect.x,
									  wndDpt->scrolling.ewii.wndRect.y + wndDpt->scrolling.wndRect.y);
					 
					 if(wndDpt->word_id_off){
						 user_langres_get_menu_text(wndDpt->word_id_off,str,100);
						 GUI_DispStringAt(str,wndDpt->word_x + wndDpt->scrolling.wndRect.x,wndDpt->word_y + wndDpt->scrolling.wndRect.y);
				     }
					 user_theme_close(wndDpt->buttonMove);
				 }
			  }	
			}
	    	wndDpt->inva = INVALIDATE_NULL;
	   	}
        break;
		
	case GUI_MSG_USER_GESTURE_CLICK:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK \n");
		LogMI("wndDpt->xml_id %s\n",wndDpt->xml_id);
		LogMI("Page_Number %d\n",Page_Number);
		LogMI("wndDpt->xml_button_controltype %s\n",wndDpt->xml_button_controltype);
		click_xml_id_name = father_xml_id_name = wndDpt->xml_id;
		father_xml_id_relation = wndDpt->xml_button_controltype;
		
		Button_Status = wndDpt->buttonStatus;
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������
		}
		wndDpt->buttonStatus_old= wndDpt->buttonStatus;
		break;
		
    case GUI_MSG_USER_GESTURE_LPRESS:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_LPRESS \n");
		if(SLIB_strcmp(wndDpt->xml_button_controltype,"delay") == 0){
		     dsk_keytone_on();
		     wndDpt->xml_button_controltype = "delay";
			 if(wndDpt->page >= 0){
				 if(if_top_down_move == 0){
					 msgsend.dwAddData2 = MAKELONG(wndDpt->page * 720,100);
				 } else if(if_top_down_move == 1){
					 msgsend.dwAddData2 = MAKELONG(wndDpt->page * 720,100);
				 }
				 msgsend.id = GUI_MSG_USER_GESTURE_DONE;
				 msgsend.h_deswin = GUI_WinGetParent(GUI_WinGetParent(msg->h_deswin));
				 GUI_PostMessage(&msgsend);
			 }else{
				 wndDpt->buttonStatus = wndDpt->buttonStatus ? 0 : 1;
				 wndDpt->inva = INVALIDATE_ALL;
				 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				 
				 Buttonhandle_Search_Up(wndDpt->code_handle);//�������
				 
				 wndDpt->buttonStatus = wndDpt->buttonStatus ? 0 : 1;
				 wndDpt->inva = INVALIDATE_ALL;
				 GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
			 }
			 break;
		}
		
		msgsend.id = GUI_MSG_USER_GESTURE_LPRESS;
		msgsend.h_deswin = GUI_WinGetParent(GUI_WinGetParent(msg->h_deswin));
		GUI_PostMessage(&msgsend);
		break;
		
	case GUI_MSG_USER_GESTURE_CLICK_MSG://�������
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_CLICK_MSG \n");
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		wndDpt->xml_click_id = click_xml_id_name;
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//LogMI("msg->dwAddData1 %d",msg->dwAddData1);
	    //�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_XIA_MSG://�´�����
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_XIA_MSG \n");
		if(SLIB_strcmp(click_xml_id_name,wndDpt->xml_click_id) == 0){
			break;//���ȵ������
		}
		i = XML_FindButtonState(father_xml_id_name);
		if(i >= 0){
			Button_Status = i;
		}
		//LogMI("wndDpt->buttonStatus_close %d",wndDpt->buttonStatus_close);
		if(wndDpt->buttonStatus_close == 10){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
			}
		}
		if(Button_Array){
			if(wndDpt->buttonStatus != 1){
				wndDpt->buttonStatus = 1;
				wndDpt->inva = INVALIDATE_ALL;
				wndDpt->buttonStatus_close = 10;
			}
		}
		//���水��״̬
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		//LogMI("wndDpt->xml_id %s",wndDpt->xml_id);
		//LogMI("wndDpt->buttonStatus %d",wndDpt->buttonStatus);
		//�´�
		
		//�ϴ�
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		//�ϴ�һ��
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
		break;
		
	case GUI_MSG_USER_GESTURE_SHANG_MSG:
		LogMI("ButtonProcMsg: GUI_MSG_USER_GESTURE_SHANG_MSG \n");
		if(SLIB_strcmp(father_xml_id_name2,wndDpt->xml_id) != 0){
			if(msg->dwAddData2 == 1){//һ��
			    if(msg->dwAddData1 != wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 0){//ȡ��
				break;//��֤�빤��һ��
			    if(msg->dwAddData1 == wndDpt->buttonStatus){
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}else if(msg->dwAddData2 == 5){
			    if(SLIB_strcmp(father_xml_id_relation,"onoff") == 0){
				    break;//��֤�빤��һ��
				}else{
					i = Imageview_Id_Return(wndDpt->xml_id,father_xml_id_name2);
					//LogMI("Button_Status %d",Button_Status);
					if(i == Button_Status){
						break;//��֤�빤��һ��
					}
					wndDpt->buttonStatus = 1;
					wndDpt->inva = INVALIDATE_ALL;
					GUI_WinUpdate(msg->h_deswin, ORANGE_TRUE);
				}
			}
		}
		XML_SaveButtonState_Handle(wndDpt->xml_id,wndDpt->buttonStatus);
		if(wndDpt->buttonStatus_old != wndDpt->buttonStatus){
			father_xml_id_name2 = wndDpt->xml_id;
			CFind_Primary_Toitemid(wndDpt->xml_id);//��������//�ϴ�
		}
		wndDpt->buttonStatus_old = wndDpt->buttonStatus;
		break;
    default:

        GUI_FrmWinDefaultProc(msg);
        break;
    }
    return 0;
}
#endif


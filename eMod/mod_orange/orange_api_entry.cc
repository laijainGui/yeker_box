#pragma arm section rodata="API_TBL"
const orangemod_api_entry_t orangemod_api =
{
	GUI_LyrWinCreate    	    ,
    GUI_LyrWinDelete    	    ,
    GUI_WinThreadCleanup		,
    GUI_WinSetFocusChild       	,
    GUI_WinGetFocusChild       	,
    GUI_WinSetActiveChild		,
    GUI_WinGetType				,
    GUI_WinGetLyrWin			,
    GUI_WinGetMainManWin		,
    GUI_WinGetManWin			,
    GUI_WinGetFrmWin			,
    GUI_WinGetParent			,
    GUI_WinGetFirstChild		,
    GUI_WinGetNextBro			,
    GUI_WinIsAncestor			,
    GUI_WinIsChild				,
    GUI_WinGetRootWin			,
    GUI_WinGetNextHostedWin		,
    GUI_WinGetFirstHostedWin	,
    GUI_WinGetOwnerWin			,
    GUI_WinGetDlgItem			,
    GUI_WinGetItemId			,
    GUI_WinGetPrimitiveWin		,
    GUI_WinGetHandFromId		,
    GUI_WinGetName             	,
    GUI_WinGetHandFromName     	,
    GUI_WinGetAttr             	,
    GUI_WinSetAttr             	,
    GUI_WinGetAddData          	,
    GUI_WinSetAddData          	,
    GUI_WinGetStyle            	,
    GUI_WinSetStyle            	,
    GUI_WinGetExStyle          	,
    GUI_WinSetExStyle          	,
    GUI_WinIsVisible			,
    GUI_WinSetNotifyCallback   	,
    GUI_WinGetNotifyCallback   	,
    GUI_WinSetCallback     		,
    GUI_WinGetCallback     		,
    GUI_NotifyParent           	,
    GUI_WinUpdate              	,
    GUI_InvalidateRect         	,
    GUI_WinSetCaptureWin       	,
    GUI_WinGetCaptureWin       	,
    GUI_WinReleaseCapture      	,
    GUI_WinSetTouchFocus       	,
    GUI_WinGetTouchFocus       	,
    GUI_WinReleaseTouchFocus   	,
    GUI_WinGetClient           	,
    GUI_WinGetWinRECT          	,
    GUI_WinSetWinRECT          	,
    GUI_WinGetClientRECT       	,
    GUI_WinSetClientRECT       	,
    GUI_WinGetClientFBRect     	,
    GUI_WinGetWinFBRect        	,
    GUI_ClientToScreen         	,
    GUI_ScreenToClient         	,
    GUI_WindowToScreen         	,
    GUI_ScreenToWindow         	,
    GUI_FBToScreen             	,
    GUI_ScreenToFB             	,
    GUI_LyrWinSetSrcWindow	   	,
    GUI_LyrWinSetScnWindow 		,
    GUI_LyrWinGetSrcWindow 		,
    GUI_LyrWinGetScnWindow 		,
    GUI_LyrWinGetFB		 		,
    GUI_LyrWinSetFB		 		,
    GUI_LyrWinSetSta		 	,
    GUI_LyrWinGetSta  			,
    GUI_LyrWinSel 		 		,
    GUI_LyrWinCacheOn		 	,
    GUI_LyrWinCacheOff     		,
    GUI_LyrWinFlushFB      		,
    GUI_LyrWinSetAlpha     		,
    GUI_LyrWinAlphaOn      		,
    GUI_LyrWinAlphaOff	 		,
    GUI_LyrWinCKOn		 		,
    GUI_LyrWinCKOff		 		,
    GUI_LyrWinSetBottom    		,
    GUI_LyrWinSetTop		 	,
    GUI_SetTimer				,
    GUI_KillTimer              	,
    GUI_ResetTimer             	,
    GUI_IsTimerInstalled       	,
    GUI_HaveFreeTimer          	,
    GUI_GetTickCount           	,
    GUI_GetTimerExpired        	,
    GUI_WinInit                	,
    GUI_WinExit                	,
    GUI_CharSetToEncode			,
    GUI_CursorCreate           	,
    GUI_CursorDelete           	,
    GUI_CursorShow             	,
    GUI_CursorHide             	,
    GUI_CursorSetPos           	,
    GUI_CursorGetPos           	,
    GUI_CursorSetPara          	,
    GUI_GetScnDir              	,
    GUI_SetScnDir              	,
    GUI_GetScreenSize          	,
    SysRectToGuiRect           	,
    GUI_Lock					,
    GUI_Unlock					,
    GUI_LockAccept				,
    GUITASK_Init				,
    GUITASK_CopyContext			,
    GUI_Init_layer				,
    GUI_SetDefault				,
    GUI_SetDrawMode				,
    GUI_SetFontMode				,
    GUI_SaveContext   			,
    GUI_RestoreContext			,
    GUI_OpenAlphaBlend			,
    GUI_CloseAlphaBlend			,
    GUI_RectsIntersect			,
    GUI_MoveRect       			,
    GUI_MergeRect      			,
    GUI__IntersectRects			,
    GUI__IntersectRect 			,
    GUI_SetClipRect				,
    GUI__DivideRound32   		,
    GUI_GetPenSize     			,
    GUI_GetPenShape    			,
    GUI_GetLineStyle   			,
    GUI_SetBkColor   			,
    GUI_SetColor     			,
    GUI_SetPenSize   			,
    GUI_SetPenShape  			,
    GUI_SetLineStyle 			,
    GUI_Log      				,
    GUI_Log1     				,
    GUI_Log2     				,
    GUI_Log3     				,
    GUI_Log4     				,
    GUI_Warn     				,
    GUI_Warn1    				,
    GUI_Warn2    				,
    GUI_Warn3    				,
    GUI_Warn4    				,
    GUI_ErrorOut 				,
    GUI_ErrorOut1				,
    GUI_ErrorOut2				,
    GUI_ErrorOut3				,
    GUI_ErrorOut4				,
    GUI_BMP_Draw         		,
    GUI_BitString_Draw			,
    GUI_BitString_DrawEx		,
    GUI_ARGB_Draw				,
    GUI_BMP_Draw_Trans			,
    GUI_BMP_GetXSize     		,
    GUI_BMP_GetYSize     		,
    GUI_Clear            		,
    GUI_ClearRect        		,
    GUI_ClearRectEx      		,
    GUI_DrawArc          		,
    GUI_DrawCircle       		,
    GUI_DrawEllipse      		,
    GUI_DrawGraph        		,
    GUI_DrawHLine        		,
    GUI_DrawLine         		,
    GUI_DrawLineRel      		,
    GUI_DrawLineTo       		,
    GUI_DrawPie          		,
    GUI_DrawPixel        		,
    GUI_DrawPoint        		,
    GUI_DrawPolygon      		,
    GUI_DrawRect         		,
    GUI_DrawRectEx       		,
    GUI_DrawVLine        		,
    GUI_FillCircle       		,
    GUI_FillEllipse      		,
    GUI_FillPolygon      		,
    GUI_FillRect         		,
    GUI_FillRectEx       		,
    GUI_InvertRect       		,
    GUI_MoveRel          		,
    GUI_MoveTo           		,
    GUI_SetRectMem				,
    GUI_GetRectMem				,
    GUI_DispCEOL 				,
    GUI_DispChar  				,
    GUI_DispChars 				,
    GUI_DispCharAt				,
    GUI_DispString         		,
    GUI_DispStringAt       		,
    GUI_DispStringAtCEOL   		,
    GUI_DispStringHCenterAt		,
    GUI__DispStringInRect  		,
    GUI_DispStringInRect   		,
    GUI_DispStringInRectMax		,
    GUI_DispStringLen      		,
    GUI_DispStringInRectWrap	,
    GUI_GetTextExtend			,
    GUI_GetYAdjust				,
    GUI_GetFont					,
    GUI_GetCharDistX			,
    GUI_GetStringDistX			,
    GUI_GetFontDistY			,
    GUI_GetFontSizeY			,
    GUI_GetFontInfo   			,
    GUI_GetYSizeOfFont			,
    GUI_GetYDistOfFont			,
    GUI_GetTextAlign			,
    GUI_GetTextMode				,
    GUI_IsInFont				,
    GUI_SetTextAlign			,
    GUI_SetTextMode				,
    GUI_SetFont					,
    GUI_GotoXY					,
    GUI_GotoX					,
    GUI_GotoY					,
    GUI_DispNextLine			,
    GUI_GetDefaultFont			,
    GUI_UC_GetCharSize      	,
    GUI_UC_GetCharCode      	,
    Big5_to_Unicode         	,
    GUI_UC_SetEncodeNone    	,
    GUI_UC_SetEncodeUTF8    	,
    GUI_UC_SetEncodeGB2312  	,
    GUI_UC_SetEncodeGBK     	,
    GUI_UC_SetEncodeBig5    	,
    GUI_UC_SetEncodeSJIS        ,
    GUI_UC_SetEncodeISO885916   ,
    GUI_UC_SetEncodeISO885915   ,
    GUI_UC_SetEncodeISO885914   ,
    GUI_UC_SetEncodeISO885913   ,
    GUI_UC_SetEncodeISO885912   ,
    GUI_UC_SetEncodeISO885911   ,
    GUI_UC_SetEncodeISO885910   ,
    GUI_UC_SetEncodeISO88599    ,
    GUI_UC_SetEncodeISO88598    ,
    GUI_UC_SetEncodeISO88597    ,
    GUI_UC_SetEncodeISO88596    ,
    GUI_UC_SetEncodeISO88595    ,
    GUI_UC_SetEncodeISO88594    ,
    GUI_UC_SetEncodeISO88593    ,
    GUI_UC_SetEncodeISO88592    ,
    GUI_UC_SetEncodeISO88591    ,
    GUI_UC_SetEncodeKIO8R       ,
    GUI_UC_SetEncodeEUCKR       ,
    GUI_UC_SetEncodeEUCJP       ,
    GUI_UC_SetEncodeCP874       ,
    GUI_UC_SetEncodeCP1250      ,
    GUI_UC_SetEncodeCP1251      ,
    GUI_UC_SetEncodeCP1253      ,
    GUI_UC_SetEncodeCP1255      ,
    GUI_UC_SetEncodeCP1256      ,
    GUI_UC_SetEncodeCP1257      ,
    GUI_UC_SetEncodeCP1258      ,
    GUI_DispBin  				,
    GUI_DispBinAt				,
    GUI_DispHex  				,
    GUI_DispHexAt				,
    GUI_ALLOC_GetNumFreeBytes	,
    GUI_ALLOC_AllocInit  		,
    GUI_ALLOC_AllocNoInit		,
    GUI_ALLOC_AllocZero  		,
    GUI_ALLOC_Free       		,
    GUI_ALLOC_FreePtr    		,
    GUI_ALLOC_GetSize    		,
    GUI_ALLOC_GetMaxSize 		,
    GUI_ALLOC_h2p        		,
    GUI_ALLOC_Init       		,
    GUI_SelectLCD				,
    GUI_SelectLayer				,
    GUI_CreateLayer				,
    GUI_ReleaseLayer			,
    GUI_SetLCDSize				,
    GUI_SetLCDDirection			,
    GUI_TOUCH_X_ActivateX		,
    GUI_TOUCH_X_ActivateY		,
    GUI_TOUCH_X_MeasureX		,
    GUI_TOUCH_X_MeasureY		,
    LCD_L0_Index2Color  		,
    LCD_L0_1_Index2Color		,
    LCD_L0_2_Index2Color		,
    LCD_L0_3_Index2Color		,
    LCD_L0_Color2Index  		,
    LCD_L0_1_Color2Index		,
    LCD_L0_2_Color2Index		,
    LCD_L0_3_Color2Index		,
    LCD_L0_GetIndexMask  		,
    LCD_L0_1_GetIndexMask		,
    LCD_L0_2_GetIndexMask		,
    LCD_L0_3_GetIndexMask		,
    LCD_GetXSize				,
    LCD_GetYSize				,
    LCD_GetXSizeEx				,
    LCD_GetYSizeEx				,
    LCD_GetNumColorsEx			,
    LCD_GetFixedPaletteEx		,
    LCD_GetXMag					,
    LCD_GetYMag					,
    LCD_GetSwapRBEx				,
    LCD_DrawHLine				,
    LCD_DrawPixel				,
    LCD_DrawVLine  				,
    LCD_SetClipRectEx			,
    LCD_SetClipRectMax			,
    LCD_Init					,
    LCD_Init_layer				,
    LCD_SetBkColor   			,
    LCD_SetColor     			,
    LCD_SetPixelIndex			,
    LCD_SetDrawMode  			,
    LCD_SetFontMode				,
    LCD_SetColorIndex			,
    LCD_SetBkColorIndex			,
    LCD_FillRect				,
    LCD_MixColors256			,
    LCD_GetPixelColor			,
    LCD_GetPixelIndex			,
    LCD_L0_CheckInit			,
    LCD_Color2Index     		,
    LCD_Index2Color     		,
    GUI_LyrMove          		,
    GUI_LyrLock 				,
    GUI_LyrUnlock 				,
    GUI_LyrLockAccept 			,
    GUI_LyrInitOS 				,
    GUI_HavePendingMessage  	,
    GUI_BroadcastMessage    	,
    GUI_PostSyncMessage     	,
    GUI_SendMessage         	,
    GUI_SendMessageTimeout  	,
    GUI_PostMessage         	,
    GUI_SendNotifyMessage   	,
    GUI_GetMessage          	,
    GUI_GetMessageEx        	,
    GUI_MsgSetRepeatTimes   	,
    GUI_QueryMessage        	,
    GUI_PeekMessage         	,
    GUI_DispatchMessage     	,
    GUI_PostQuitMessage     	,
    GUI_SendAsyncMessage    	,
    GUI_ThrowAwayMessages   	,
    GUI_SetSyncMsgRetVal    	,
    GUI_PostSyncSem         	,
    Lang_Open					,
    Lang_Read					,
    Lang_GetStringAddress		,
    Lang_GetStringSize			,
    Lang_GetString				,		
    Lang_Close					,
    OpenRes						,
    CloseRes  					,
    GetResAddr					,
    ReadRes   					,
    GetResType					,
    GetResSize					,
	GetRes						,
    GUI_SetFrameColor8bpp32		,    
#if GUI_WIN_MANWIN_EN
	GUI_ManWinCreate           	,
    GUI_ManWinDelete           	,
    GUI_SetActiveManWin        	,
    GUI_GetActiveManWin        	,
    GUI_ManWinDefaultProc      	,
    GUI_GetTouchFocusWin       	,
    GUI_SceenPointInWin        	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIN_FRMWIN_EN
	GUI_FrmWinCreate           	,
    GUI_FrmWinDelete           	,
    GUI_FrmWinDefaultProc      	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIN_CTRLWIN_EN
	GUI_CtrlWinCreate          	,
    GUI_CtrlWinDelete          	,
    GUI_CtrlWinGetAddData      	,
    GUI_CtrlWinSetAddData      	,
    GUI_CtrlWinGetClassName    	,
    GUI_CtrlWinDefaultProc     	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_CORE_MEMDEV_EN
	GUI_MEMDEV_Create     		,
    GUI_MEMDEV_CreateEx   		,
    GUI_MEMDEV_CreateFixed		,
    GUI_MEMDEV_Clear         	,
    GUI_MEMDEV_CopyFromLCD   	,
    GUI_MEMDEV_CopyToLCD		,
    GUI_MEMDEV_CopyToLCDAt   	,
    GUI_MEMDEV_CompareWithLCD	,
    GUI_MEMDEV_Delete        	,
    GUI_MEMDEV_GetXSize      	,
    GUI_MEMDEV_GetYSize      	,
    GUI_MEMDEV_ReduceYSize   	,
    GUI_MEMDEV_Select 			,
    GUI_MEMDEV_SetOrg        	,
    GUI_MEMDEV_WriteAt       	,
    GUI_MEMDEV_Write         	,
    GUI_MEMDEV_WriteExAt     	,
    GUI_MEMDEV_WriteEx       	,
    GUI_MEMDEV_GetDataPtr    	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIN_DIALOG_EN
	GUI_DlgGetFirstButton		,
	GUI_ModuleDialogCreate     	,
    GUI_EndDialog              	,
    GUI_GetDlgItem             	,
    GUI_DialogDefaultProc      	,
    GUI_ModulelessDialogCreate 	,
    GUI_ModulelessDialogDelete 	,
    GUI_GetNextDlgTabItem      	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_EN
	GUI_AddNewControlClass 		,
    GUI_SetCtrlClassAddData 	,
    GUI_EmptyControlClassInfoTable 	,
    GUI_GetCtrlClassAddData 	,
    GUI_DeleteControlClass 		,
    GUI_TerminateControlClass 	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_CORE_LONGNAME_EN
	GUI_LongStringCreate       	,
    GUI_LongStringDelete       	,
    GUI_LongStringStart        	,
    GUI_LongStringStop         	,
    GUI_LongStringReset		 	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_CORE_FONT_SFT_EN
	GUI_SFT_CreateFont			,
    GUI_SFT_ReleaseFont			,
#else
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_CORE_FONT_TTF_EN
	GUI_TTF_CreateFont			,
    GUI_TTF_GetFamilyName		,
    GUI_TTF_GetStyleName		,
    GUI_TTF_Done				,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_BUTTON_EN
	RegisterButtonControl        	,
    GUI_ButtonSetFocusBmp        	,
    GUI_ButtonSetUnFocusBmp      	,
    GUI_ButtonSetText            	,
    GUI_ButtonSetUnFcsTxtColor   	,
    GUI_ButtonSetFcsTxtColor     	,
    GUI_ButtonSetBkColor     		,
    GUI_ButtonSetBmpPos          	,
    GUI_ButtonSetTxtPos          	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_STATIC_EN
	RegisterStaticControl        	,
    GUI_StaticSetFocusBmp        	,
    GUI_StaticSetUnFocusBmp      	,
    GUI_StaticSetText            	,
    GUI_StaticSetUnFcsTxtColor   	,
    GUI_StaticSetFcsTxtColor     	,
    GUI_StaticSetBmpPos          	,
    GUI_StaticSetTxtPos          	,
    GUI_StaticStartMove          	,
    GUI_StaticStopMove           	,
    GUI_StaticSetCharSet         	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_LISTMENU_EN
	GUI_LstmGetCurItem      	,
    GUI_LstmGetItemNo       	,
    GUI_LstmSetCurNo        	,
    GUI_LstmDrawCurNo       	,
    GUI_LstmStopSlip        	,
    GUI_LstmGetItem         	,
    GUI_LstmUpdateItem      	,
    GUI_LstmChildInFb       	,
    GUI_LstmDelCurItem      	,
    GUI_LstmAddItemTail     	,
    GUI_LstmGetItemCount    	,
    GUI_LstmGetItemLyrWin   	,
    GUI_LstmGetItemRect     	,
    GUI_LstmGetItemAttr     	,
    GUI_LstmGetHostWin			,
    RegisterListMenuControl 	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_PROGSHEET_EN
	RegisterProgSheetControl 	,
#else
	GUI_StubNop					,
#endif
#if GUI_WIDGET_SLIDER_EN
	RegisterSliderControl	,
    SLIDER_SetRange   		,
    SLIDER_SetValue   		,
    SLIDER_GetMin     		,
    SLIDER_GetMax     		,
    SLIDER_GetValue   		,
    SLIDER_SetLineSize		,
    SLIDER_GetLineSize		,
    bmp_open				,
	bmp_close				,
	bmp_get_bitcount		,
	bmp_get_width			,
	bmp_get_height			,
	bmp_get_size			,
	bmp_get_matrix			,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_TXTBOX_EN
	GUI_TxtboxSetStamp      	,
    GUI_TxtboxOnDraw        	,
    GUI_TxtboxSetMode	    	,
    GUI_TxtboxGetMode       	,
    GUI_TxtBoxSetPara       	,
    RegisterTxtboxControl   	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_GMSGBOX_EN
	GUI_GMsgBox 				,
    GUI_GMsgBoxSetText			,
    GUI_GMsgBoxSetTextPos		,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_SPINBOX_EN
	RegisterSpinboxControl 		,
    GUI_SpinboxGetCurValue		,
    GUI_SpinboxSetCurValue		,
    GUI_SpinboxSetMaxValue		,
    GUI_SpinboxSetMinValue		,
    GUI_SpinboxSetBkColor		,
    GUI_SpinboxSetUnFcsTxtColor	,
    GUI_SpinboxSetFcsTxtColor	,
    GUI_SpinboxSetFocusUpBmp	,
    GUI_SpinboxSetFocusDownBmp	,
    GUI_SpinboxSetUnFocusUpBmp	,
    GUI_SpinboxSetUnFocusDownBmp,
    GUI_SpinboxSetUpBmpPos		,
    GUI_SpinboxSetDownBmpPos	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_PROGBAR_EN
	RegisterProgbarControl		,
    PROGBAR_SetRange   			,
    PROGBAR_SetValue   			,
    PROGBAR_GetMin     			,
    PROGBAR_GetMax     			,
    PROGBAR_GetValue   			,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_SLISTBOX_EN
	SListbox_UpdateMenulist       	,
    SListbox_GetItemNo			  	,
    SListbox_GetItemAttr		  	,
    SListbox_GetHostWin			  	,
    SListbox_GetItemLyrWin		  	,
    SListbox_GetItemCount		  	,
    SListbox_GetItem			  	,
    SListbox_GetCurItem			  	,
    SListbox_PrevPage             	,
    SListbox_NextPage             	,
    SListbox_ItemDisable          	,
    SListbox_ItemEnable           	,
    SListbox_GetHeadindex         	,
    SListbox_DelCurItem           	,
    SListbox_AddTail              	,
    SListbox_SetCurItem           	,
    SListbox_Disable              	,
    SListbox_GetItemRect          	,
    RegisterListBoxControl        	,
    UnRegisterListBoxControl      	,
#else
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
	GUI_StubNop					,
#endif
#if GUI_WIDGET_SICONS_EN
#else
#endif
#if GUI_WIDGET_STIMESTATIC_EN
#else
#endif
	GUI_Fb2Dispfb				,
	GUI_Dispfb2Fb				,
	GUI_LogicLyr2DispLyr		,
	GUI_DispLyr2LogicLyr		,
	GUI_BMP_DrawEx				,
	GUI_Memdev_FrameBuffer_Release,
	  GUI_LyrWinGetHWLyr,
};  
#pragma arm section
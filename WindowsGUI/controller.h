/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: Panel */
#define  PANEL_BtnStart                   2       /* control type: command, callback function: CmdStart */
#define  PANEL_BtnSelect                  3       /* control type: command, callback function: CmdSelect */
#define  PANEL_BtnA                       4       /* control type: command, callback function: CmdA */
#define  PANEL_BtnB                       5       /* control type: command, callback function: CmdB */
#define  PANEL_BtnUp                      6       /* control type: command, callback function: CmdUp */
#define  PANEL_BtnDown                    7       /* control type: command, callback function: CmdDown */
#define  PANEL_BtnLeft                    8       /* control type: command, callback function: CmdLeft */
#define  PANEL_BtnRight                   9       /* control type: command, callback function: CmdRight */
#define  PANEL_Overlay                    10      /* control type: picture, callback function: (none) */
#define  PANEL_LED                        11      /* control type: LED, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CmdA(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdDown(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdLeft(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdRight(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdSelect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdStart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CmdUp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Panel(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

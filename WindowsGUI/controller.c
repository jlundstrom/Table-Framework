#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "controller.h"

int Connexion(char *TargetName, unsigned long *ConnectionId, char *Login,
              char *Password, BOOL ShowPuTTY, long Protocol,
              unsigned long PortNumber, long GenerateReport, void *ptrFctRcv,
              unsigned long SpecSettings);
int SendRcvData(unsigned long ConnectionId, char *Command, char *Title,
                char *Comments, long TimeCapture, char **RcvTelnetData,
                long MaxSizeOfData, unsigned long Settings);
int CloseConnexion(unsigned long ConnectionId);
void connect(void);
void disconnect(void);
void transmit(char buf[]);

int        		   panelHandle;
enum 			   commandEnum { start, select, a, b, up, down, left, right };
const char * const command[] = { "h", "j", "q", "e", "w", "s", "a", "d" };

int               puttyFlag      = 0;
char              TargetName[]   = "SmartTable"; // COM3
unsigned long     ConnectionId   = 1;
char              Login[]        = "";
char              Password[]     = "";
BOOL              ShowPuTTY      = 1;
long              Protocol       = 4; // 5
unsigned long     PortNumber     = 0; // 9600
long              GenerateReport = 0;
void              *ptrFctRcv     = NULL;
unsigned long     SpecSettings   = 0;
char              Title[]        = "";
char              Comments[]     = "";
long              TimeCapture    = 0;
char              *RcvTelnetData = NULL;
long              MaxSizeOfData  = 2;
unsigned long     Settings       = 0;

int main(int argc, char *argv[])
{
   if (InitCVIRTE(0, argv, 0) == 0)
      return -1;                /* out of memory */

   if ((panelHandle = LoadPanel(0, "controller.uir", PANEL)) < 0)
      return -1;

   DisplayPanel(panelHandle);
   connect();   
   RunUserInterface();
   DiscardPanel(panelHandle);
   return 0;
}

int CVICALLBACK Panel(int panel, int event, void *callbackData,
                      int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_GOT_FOCUS:

      break;

   case EVENT_LOST_FOCUS:

      break;

   case EVENT_CLOSE:

      disconnect();

      QuitUserInterface(0);

      break;
   }
   return 0;
}

int CVICALLBACK CmdUp(int panel, int control, int event,
                      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[up]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdLeft(int panel, int control, int event,
                        void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[left]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdDown(int panel, int control, int event,
                        void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[down]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdSelect(int panel, int control, int event,
                          void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[select]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdStart(int panel, int control, int event,
                         void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[start]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdB(int panel, int control, int event,
                     void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[b]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdA(int panel, int control, int event,
                     void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[a]);

      break;
   }
   return 0;
}

int CVICALLBACK CmdRight(int panel, int control, int event,
                         void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_COMMIT:

      transmit(command[right]);

      break;
   }
   return 0;
}

void connect(void)
{
   if (!puttyFlag)
   {
      if (Connexion(TargetName, &ConnectionId, Login, Password, ShowPuTTY,
                    Protocol, PortNumber, GenerateReport, ptrFctRcv,
                    SpecSettings) == 0)
      {
         SetCtrlVal(panelHandle, PANEL_LED, 1);
         puttyFlag = 1;
      }

      else
      {
         MessagePopup("Error", "Failed to connect to the Smart Table.");
      }
   }
}

void disconnect(void)
{
   if (puttyFlag)
   {
      if (CloseConnexion(ConnectionId) == 0)
      {
         SetCtrlVal(panelHandle, PANEL_LED, 0);
         puttyFlag = 0;
      }

      else
      {
         MessagePopup("Error", "Failed to disconnect from the Smart Table.");
      }
   }
}

void transmit(char buf[])
{
   RcvTelnetData = malloc(MaxSizeOfData * sizeof(*RcvTelnetData));

   SendRcvData(ConnectionId, buf, Title, Comments, TimeCapture, &RcvTelnetData,
               MaxSizeOfData, Settings);

   free(RcvTelnetData);
   RcvTelnetData = NULL;
}

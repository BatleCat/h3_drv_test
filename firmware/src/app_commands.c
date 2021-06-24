/*******************************************************************************
  Sample Application

  File Name:
    app_commands.c

  Summary:
    commands for the tcp client demo app.

  Description:
    
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END
//-----------------------------------------------------------------------------
//#include "tcpip/tcpip.h"
#include "app_commands.h"
#include <stddef.h>
#include "config/default/system/command/sys_command.h"
#include "config/default/system/debug/sys_debug.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "app_user_input_thread.h"
//#include "config/default/system/console/sys_console.h"
#include <bsp/bsp.h>
//-----------------------------------------------------------------------------
static void _APP_Commands_testAnswer (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _APP_Commands_stopUDPtest(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _APP_Commands_SetOptions (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _APP_Commands_GetOptions (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
//-----------------------------------------------------------------------------
static const SYS_CMD_DESCRIPTOR    appCmdTbl[]=
{
    {"test",                    _APP_Commands_testAnswer,              ": Comand test is received"},
    {"stop",                    _APP_Commands_stopUDPtest,             ": Comand stop is received"},
    {"getudppacketoptions",     _APP_Commands_GetOptions,              ": Gets the hostname, port and message"},
    {"setudppacketoptions",     _APP_Commands_SetOptions,              ": Sets the current hostname, port, and message"},
};
//-----------------------------------------------------------------------------
bool APP_Commands_Init()
{
    if (!SYS_CMD_ADDGRP(appCmdTbl, sizeof(appCmdTbl)/sizeof(*appCmdTbl), "app", ": app commands"))
    {
//        SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"USB thread: USART init ok \r\n");
        SYS_ERROR(SYS_ERROR_ERROR, "Failed to create APP Commands\r\n");
//        SYS_CONSOLE_MESSAGE("USB thread: USART init ok \r\n");
        return false;
    }
//    strcpy(APP_Hostname_Buffer, "10.2.22.220");
//    strcpy(APP_Port_Buffer, "1500");
//    strcpy(APP_Message_Buffer, "Hello");
    APP_Send_Packet = false;
    APP_Stop_Packet = false;
    
    return true;
}
//-----------------------------------------------------------------------------
//char APP_Hostname_Buffer[MAX_URL_SIZE];
//char APP_Port_Buffer[6];
//char APP_Message_Buffer[MAX_URL_SIZE];
bool APP_Send_Packet = false;
bool APP_Stop_Packet = false;
//-----------------------------------------------------------------------------
void _APP_Commands_testAnswer(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"APP commands: Test \r\n");
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: test\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: test\r\n");
        return;
    }
    EVENT_INFO ev;
    ev.eventType = EVENT_TYPE_TEMP_WRITE_REQ;
    ev.eventData = 45;
    xQueueSend( eventQueue, (void*)&ev, portMAX_DELAY);
    APP_Send_Packet = true;
    LED1_Toggle();
    return;
}
//-----------------------------------------------------------------------------
static void _APP_Commands_stopUDPtest(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"APP commands: Stop \r\n");
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: stop\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: stop\r\n");
        return;
    }
    LED2_Toggle();
    APP_Stop_Packet = true;
    return;
}
//-----------------------------------------------------------------------------
static void _APP_Commands_SetOptions(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"APP commands: Set options \r\n");
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 4)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setudppacketoptions <hostname> <port> <message>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setudppacketoptions 10.0.1.4 9760 Hello\r\n");
        return;
    }
    LED3_Toggle();
/*
    strcpy(APP_Hostname_Buffer, argv[1]);
    strcpy(APP_Port_Buffer, argv[2]);
    strcpy(APP_Message_Buffer, argv[3]);
*/ 
    return;
}
//char bufferArea[3][80];
//-----------------------------------------------------------------------------
void _APP_Commands_GetOptions(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"APP commands: Get options \r\n");
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    
    if (argc != 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: getudppacketoptions\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: getudppacketoptions\r\n");
        return;
    }
/*
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Current UDP Options:\r\n");
     sprintf(bufferArea[0], "\thostname: '%s'\r\n", APP_Hostname_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, bufferArea[0]);
     sprintf(bufferArea[1], "\tport: '%s'\r\n", APP_Port_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, bufferArea[1]);
     sprintf(bufferArea[2], "\tmessage: '%s'\r\n", APP_Message_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, bufferArea[2]);
*/
    return;
}
//-----------------------------------------------------------------------------

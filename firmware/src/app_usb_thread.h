/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_usb_thread.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_USB_THREAD_Initialize" and "APP_USB_THREAD_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_USB_THREAD_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_USB_THREAD_H
#define _APP_USB_THREAD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "FreeRTOS.h"
#include "task.h"
#include "definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    /* TODO: Define states used by the application state machine. */
    APP_USB_THREAD_STATE_BUS_ENABLE=0,
    APP_USB_THREAD_STATE_WAIT_FOR_BUS_ENABLE_COMPLITE,        
    APP_USB_THREAD_STATE_WAIT_FOR_DEVICE_ATTACH,
    APP_USB_THREAD_STATE_DEVICE_CONNECTED,
    APP_USB_THREAD_STATE_MOUNT_DISK,
    APP_USB_THREAD_STATE_UNMOUNT_DISK,
    APP_USB_THREAD_STATE_OPEN_FILE,
    APP_USB_THREAD_STATE_WRITE_TO_FILE,
    APP_USB_THREAD_STATE_CLOSE_FILE,
    APP_USB_THREAD_STATE_IDLE,
    APP_USB_THREAD_STATE_ERROR
} APP_USB_THREAD_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_USB_THREAD_STATES   state;
    /* TODO: Define any additional data used by the application. */
    SYS_FS_HANDLE           fileHandle;         /* SYS_FS File handler for lst file */
    uint8_t                 data[1024];         /* Application data buffer */
    uint32_t                nBytesWritten;      /* Number of bytes written */
    uint32_t                nBytesRead;         /* Number of bytes read */
    bool                    deviceIsConnected;
    EVENT_INFO              eventInfo;
} APP_USB_THREAD_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_USB_THREAD_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_USB_THREAD_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_USB_THREAD_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_USB_THREAD_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_USB_THREAD_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_USB_THREAD_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_USB_THREAD_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_USB_THREAD_H */

/*******************************************************************************
 End of File
 */


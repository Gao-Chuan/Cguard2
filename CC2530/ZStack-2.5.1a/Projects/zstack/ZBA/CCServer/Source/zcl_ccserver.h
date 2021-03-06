/**************************************************************************************************
  Filename:       zcl_ccserver.h
  Revised:        $Date: 2011-04-13 10:12:34 -0700 (Wed, 13 Apr 2011) $
  Revision:       $Revision: 25678 $

  Description:    This file contains the Zigbee Cluster Library - Commissioning
                  Cluster Server Application.


  Copyright 2011 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

#ifndef ZCL_CCSERVER_H
#define ZCL_CCSERVER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "zcl.h"

/*********************************************************************
 * CONSTANTS
 */
#define CCSERVER_ENDPOINT                        12

#define CCSERVER_MAX_ATTRIBUTES                  15
  
// Events for the sample app
#define CCSERVER_LEAVE_TIMER_EVT                 0x0001
#define CCSERVER_RESTART_TIMER_EVT               0x0002
#define CCSERVER_RESET_TIMER_EVT                 0x0004

#define CCSERVER_MAX_NWK_STARTUP_PARAMS          1

/*********************************************************************
 * MACROS
 */
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * VARIABLES
 */
extern SimpleDescriptionFormat_t zclCCServer_SimpleDesc;

extern CONST zclAttrRec_t zclCCServer_Attrs[];

// Commissning cluster Start Up Parameter Attributes
extern uint16 zclCCServer_ShortAddress;
extern uint8 zclCCServer_ExtendedPanId[Z_EXTADDR_LEN];
extern uint16 zclCCServer_PanId;
extern uint32 zclCCServer_ChannelMask;
extern uint8 zclCCServer_ProtocolVersion;
extern uint8 zclCCServer_StackProfile;
extern uint8 zclCCServer_StartUpControl;
extern uint8 zclCCServer_TrustCenterAddr[Z_EXTADDR_LEN];
extern bool zclCCServer_UseInsecureJoin;
extern uint8 zclCCServer_NetworkKeySeqNum;
extern uint8 zclCCServer_NetworkKeyType;
extern uint16 zclCCServer_NwkManagerAddr;


/*********************************************************************
 * FUNCTIONS
 */

 /*
  * Initialization for the task
  */
extern void zclCCServer_Init( uint8 task_id );

/*
 *  Event Process for the task
 */
extern uint16 zclCCServer_event_loop( uint8 task_id, uint16 events );

/*
 *  Reset the local device to ZBA Default
 */
extern void zclCCServer_ResetToZBADefault( void );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* ZCL_CCSERVER_H */

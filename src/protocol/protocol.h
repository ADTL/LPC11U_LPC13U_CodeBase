/**************************************************************************/
/*!
    @file     protocol.h
    @author   K. Townsend (microBuilder.eu)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, K. Townsend (microBuilder.eu)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "projectconfig.h"
#include "core/usb/usb_hid.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Max message length is 64 bytes to align with USB HID, though this may
   be a bit large for I2C or SPI ... maybe adjust down, but in no case
   should this be more than 64 bytes                                     */
#define PROT_MAX_MSG_SIZE     (64)

/**************************************************************************/
/*!
    The first byte of every transfer defines the message type
*/
/**************************************************************************/
typedef enum
{
  PROT_MSGTYPE_COMMAND          = 0x10,
  PROT_MSGTYPE_RESPONSE         = 0x20,
  PROT_MSGTYPE_ERROR            = 0x80
} protMsgType_t;

/**************************************************************************/
/*!
    Global error codes
*/
/**************************************************************************/
typedef enum
{
  PROT_ERROR_NONE               = 0,
  PROT_ERROR_INVALID_PARAM      = 0x100,
  PROT_ERROR_UNKNOWN,
} protError_t;

/**************************************************************************/
/*!
    Command message struct
*/
/**************************************************************************/
typedef PRE_PACK struct POST_PACK {
  uint8_t msg_type;
  uint8_t cmd_id_low;     // little-endian
  uint8_t cmd_id_high;
  uint8_t length;
  uint8_t payload[PROT_MAX_MSG_SIZE-4];
} protMsgCommand_t;

/**************************************************************************/
/*!
    Response message struct
*/
/**************************************************************************/
typedef protMsgCommand_t protMsgResponse_t;

/**************************************************************************/
/*!
    Error message struct
*/
/**************************************************************************/
typedef PRE_PACK struct POST_PACK {
  uint8_t msg_type;
  uint8_t error_id_low;   // little-endian
  uint8_t error_id_high;
} protMsgError_t;


//------------- X macros for create consistent command enum, function prototyp & cmd table -------------//
#define PROTOCOL_COMMAND_TABLE(ENTRY) \
    ENTRY(PROT_CMDTYPE_HELP, protcmd_help)\
    ENTRY(PROT_CMDTYPE_LED, protcmd_led)\

//------------- command type -------------//
#define CMDTYPE_EXPAND(command_id, function) \
  command_id,\

typedef enum {
  PROTOCOL_COMMAND_TABLE(CMDTYPE_EXPAND)
  PROT_CMDTYPE_COUNT /**< number of commands */
}protCmdType_t;

//--------------------------------------------------------------------+
// PUBLIC API
//--------------------------------------------------------------------+
void prot_task(void * p_para);

#ifdef __cplusplus
}
#endif

#endif

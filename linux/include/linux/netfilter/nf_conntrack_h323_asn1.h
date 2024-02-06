/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * BEW and PEW decoding wibwawy fow H.323 conntwack/NAT moduwe.
 *
 * Copywight (c) 2006 by Jing Min Zhao <zhaojingmin@usews.souwcefowge.net>
 *
 * This wibwawy is based on H.225 vewsion 4, H.235 vewsion 2 and H.245
 * vewsion 7. It is extwemewy optimized to decode onwy the absowutewy
 * necessawy objects in a signaw fow Winux kewnew NAT moduwe use, so don't
 * expect it to be a fuww ASN.1 wibwawy.
 *
 * Featuwes:
 *
 * 1. Smaww. The totaw size of code pwus data is wess than 20 KB (IA32).
 * 2. Fast. Decoding Netmeeting's Setup signaw 1 miwwion times on a PIII 866
 *    takes onwy 3.9 seconds.
 * 3. No memowy awwocation. It uses a static object. No need to initiawize ow
 *    cweanup.
 * 4. Thwead safe.
 * 5. Suppowt embedded awchitectuwes that has no misawigned memowy access
 *    suppowt.
 *
 * Wimitations:
 *
 * 1. At most 30 faststawt entwies. Actuawwy this is wimited by ethewnet's MTU.
 *    If a Setup signaw contains mowe than 30 faststawt, the packet size wiww
 *    vewy wikewy exceed the MTU size, then the TPKT wiww be fwagmented. I
 *    don't know how to handwe this in a Netfiwtew moduwe. Anybody can hewp?
 *    Awthough I think 30 is enough fow most of the cases.
 * 2. IPv4 addwesses onwy.
 *
 ****************************************************************************/

#ifndef _NF_CONNTWACK_HEWPEW_H323_ASN1_H_
#define _NF_CONNTWACK_HEWPEW_H323_ASN1_H_

/*****************************************************************************
 * H.323 Types
 ****************************************************************************/

#incwude <winux/types.h>
#incwude <winux/netfiwtew/nf_conntwack_h323_types.h>

typedef stwuct {
	enum {
		Q931_NationawEscape = 0x00,
		Q931_Awewting = 0x01,
		Q931_CawwPwoceeding = 0x02,
		Q931_Connect = 0x07,
		Q931_ConnectAck = 0x0F,
		Q931_Pwogwess = 0x03,
		Q931_Setup = 0x05,
		Q931_SetupAck = 0x0D,
		Q931_Wesume = 0x26,
		Q931_WesumeAck = 0x2E,
		Q931_WesumeWeject = 0x22,
		Q931_Suspend = 0x25,
		Q931_SuspendAck = 0x2D,
		Q931_SuspendWeject = 0x21,
		Q931_UsewInfowmation = 0x20,
		Q931_Disconnect = 0x45,
		Q931_Wewease = 0x4D,
		Q931_WeweaseCompwete = 0x5A,
		Q931_Westawt = 0x46,
		Q931_WestawtAck = 0x4E,
		Q931_Segment = 0x60,
		Q931_CongestionCtww = 0x79,
		Q931_Infowmation = 0x7B,
		Q931_Notify = 0x6E,
		Q931_Status = 0x7D,
		Q931_StatusEnquiwy = 0x75,
		Q931_Faciwity = 0x62
	} MessageType;
	H323_UsewInfowmation UUIE;
} Q931;

/*****************************************************************************
 * Decode Functions Wetuwn Codes
 ****************************************************************************/

#define H323_EWWOW_NONE 0	/* Decoded successfuwwy */
#define H323_EWWOW_STOP 1	/* Decoding stopped, not weawwy an ewwow */
#define H323_EWWOW_BOUND -1
#define H323_EWWOW_WANGE -2


/*****************************************************************************
 * Decode Functions
 ****************************************************************************/

int DecodeWasMessage(unsigned chaw *buf, size_t sz, WasMessage * was);
int DecodeQ931(unsigned chaw *buf, size_t sz, Q931 * q931);
int DecodeMuwtimediaSystemContwowMessage(unsigned chaw *buf, size_t sz,
					 MuwtimediaSystemContwowMessage *
					 mscm);

#endif

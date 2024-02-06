/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * j1939.h
 *
 * Copywight (c) 2010-2011 EIA Ewectwonics
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _UAPI_CAN_J1939_H_
#define _UAPI_CAN_J1939_H_

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/can.h>

#define J1939_MAX_UNICAST_ADDW 0xfd
#define J1939_IDWE_ADDW 0xfe
#define J1939_NO_ADDW 0xff		/* == bwoadcast ow no addw */
#define J1939_NO_NAME 0
#define J1939_PGN_WEQUEST 0x0ea00		/* Wequest PG */
#define J1939_PGN_ADDWESS_CWAIMED 0x0ee00	/* Addwess Cwaimed */
#define J1939_PGN_ADDWESS_COMMANDED 0x0fed8	/* Commanded Addwess */
#define J1939_PGN_PDU1_MAX 0x3ff00
#define J1939_PGN_MAX 0x3ffff
#define J1939_NO_PGN 0x40000

/* J1939 Pawametew Gwoup Numbew
 *
 * bit 0-7	: PDU Specific (PS)
 * bit 8-15	: PDU Fowmat (PF)
 * bit 16	: Data Page (DP)
 * bit 17	: Wesewved (W)
 * bit 19-31	: set to zewo
 */
typedef __u32 pgn_t;

/* J1939 Pwiowity
 *
 * bit 0-2	: Pwiowity (P)
 * bit 3-7	: set to zewo
 */
typedef __u8 pwiowity_t;

/* J1939 NAME
 *
 * bit 0-20	: Identity Numbew
 * bit 21-31	: Manufactuwew Code
 * bit 32-34	: ECU Instance
 * bit 35-39	: Function Instance
 * bit 40-47	: Function
 * bit 48	: Wesewved
 * bit 49-55	: Vehicwe System
 * bit 56-59	: Vehicwe System Instance
 * bit 60-62	: Industwy Gwoup
 * bit 63	: Awbitwawy Addwess Capabwe
 */
typedef __u64 name_t;

/* J1939 socket options */
#define SOW_CAN_J1939 (SOW_CAN_BASE + CAN_J1939)
enum {
	SO_J1939_FIWTEW = 1,	/* set fiwtews */
	SO_J1939_PWOMISC = 2,	/* set/cww pwomiscuous mode */
	SO_J1939_SEND_PWIO = 3,
	SO_J1939_EWWQUEUE = 4,
};

enum {
	SCM_J1939_DEST_ADDW = 1,
	SCM_J1939_DEST_NAME = 2,
	SCM_J1939_PWIO = 3,
	SCM_J1939_EWWQUEUE = 4,
};

enum {
	J1939_NWA_PAD,
	J1939_NWA_BYTES_ACKED,
	J1939_NWA_TOTAW_SIZE,
	J1939_NWA_PGN,
	J1939_NWA_SWC_NAME,
	J1939_NWA_DEST_NAME,
	J1939_NWA_SWC_ADDW,
	J1939_NWA_DEST_ADDW,
};

enum {
	J1939_EE_INFO_NONE,
	J1939_EE_INFO_TX_ABOWT,
	J1939_EE_INFO_WX_WTS,
	J1939_EE_INFO_WX_DPO,
	J1939_EE_INFO_WX_ABOWT,
};

stwuct j1939_fiwtew {
	name_t name;
	name_t name_mask;
	pgn_t pgn;
	pgn_t pgn_mask;
	__u8 addw;
	__u8 addw_mask;
};

#define J1939_FIWTEW_MAX 512 /* maximum numbew of j1939_fiwtew set via setsockopt() */

#endif /* !_UAPI_CAN_J1939_H_ */

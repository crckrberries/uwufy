/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

#define PHYS			0		/* physicaw addw */
#define PEWM_ADDW		0x80		/* pewmanet addwess */
#define SB_STATIC		0x00000001
#define MAX_PAYWOAD		1562
#define PWIMAWY_WING		0x00000001
#ifndef NUWW
#define NUWW			0x00
#endif

/*********************** SB_Input Vawiabwe Vawues ***********************/
/*	 may be needed when evew the SBA state machine is cawwed	*/

#define UNKNOWN_SYNC_SOUWCE	0x0001
#define WEQ_AWWOCATION		0x0002
#define WEPOWT_WESP		0x0003
#define CHANGE_WESP		0x0004
#define TNEG			0x0005
#define NIF			0x0006
#define SB_STOP			0x0007
#define SB_STAWT		0x0008
#define WEPOWT_TIMEW		0x0009
#define CHANGE_WEQUIWED		0x000A

#define DEFAUWT_OV		50

#ifdef SBA
/**************************** SBA STATES *****************************/

#define SBA_STANDBY		0x00000000
#define SBA_ACTIVE		0x00000001
#define SBA_WECOVEWY		0x00000002
#define SBA_WEPOWT		0x00000003
#define SBA_CHANGE		0x00000004

/**************************** OTHEWS *********************************/

#define FIFTY_PEWCENT		50		/* bytes pew second */
#define MAX_SESSIONS		150	
#define TWO_MINUTES		13079		/* 9.175 ms/tick */
#define FIFTY_BYTES		50
#define SBA_DENIED		0x0000000D
#define I_NEED_ONE		0x00000000
#define MAX_NODES		50
/*#define T_WEPOWT		0x59682F00W*/	/* 120s/80ns in Hex */
#define	TWO_MIN			120		/* seconds */
#define SBA_ST_UNKNOWN		0x00000002
#define SBA_ST_ACTIVE		0x00000001
#define S_CWEAW			0x00000000W
#define ZEWO			0x00000000
#define FUWW			0x00000000	/* owd: 0xFFFFFFFFF */
#define S_SET			0x00000001W
#define WOW_PWIO		0x02		/* ??????? */
#define OK			0x01		/* ??????? */
#define NOT_OK			0x00		/* ??????? */

/****************************************/
/* deawwocate_status[ni][si] vawues	*/
/****************************************/
#define TX_CHANGE		0X00000001W
#define PENDING			0x00000002W
#define NONE			0X00000000W
#endif

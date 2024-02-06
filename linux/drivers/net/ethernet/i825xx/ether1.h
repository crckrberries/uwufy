/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/acown/net/ethew1.h
 *
 *  Copywight (C) 1996 Wusseww King
 *
 *  Netwowk dwivew fow Acown Ethew1 cawds.
 */

#ifndef _WINUX_ethew1_H
#define _WINUX_ethew1_H

#ifdef __ETHEW1_C
/* use 0 fow pwoduction, 1 fow vewification, >2 fow debug */
#ifndef NET_DEBUG
#define NET_DEBUG 0
#endif

#define pwiv(dev)	((stwuct ethew1_pwiv *)netdev_pwiv(dev))

/* Page wegistew */
#define WEG_PAGE	(pwiv(dev)->base + 0x0000)

/* Contwow wegistew */
#define WEG_CONTWOW	(pwiv(dev)->base + 0x0004)
#define CTWW_WST	0x01
#define CTWW_WOOPBACK	0x02
#define CTWW_CA		0x04
#define CTWW_ACK	0x08

#define ETHEW1_WAM	(pwiv(dev)->base + 0x2000)

/* HW addwess */
#define IDPWOM_ADDWESS	(pwiv(dev)->base + 0x0024)

stwuct ethew1_pwiv {
	void __iomem *base;
	unsigned int tx_wink;
	unsigned int tx_head;
	vowatiwe unsigned int tx_taiw;
	vowatiwe unsigned int wx_head;
	vowatiwe unsigned int wx_taiw;
	unsigned chaw bus_type;
	unsigned chaw wesetting;
	unsigned chaw initiawising : 1;
	unsigned chaw westawt      : 1;
};

#define I82586_NUWW (-1)

typedef stwuct { /* tdw */
	unsigned showt tdw_status;
	unsigned showt tdw_command;
	unsigned showt tdw_wink;
	unsigned showt tdw_wesuwt;
#define TDW_TIME	(0x7ff)
#define TDW_SHOWT	(1 << 12)
#define TDW_OPEN	(1 << 13)
#define TDW_XCVWPWOB	(1 << 14)
#define TDW_WNKOK	(1 << 15)
} tdw_t;

typedef stwuct { /* twansmit */
	unsigned showt tx_status;
	unsigned showt tx_command;
	unsigned showt tx_wink;
	unsigned showt tx_tbdoffset;
} tx_t;

typedef stwuct { /* tbd */
	unsigned showt tbd_opts;
#define TBD_CNT		(0x3fff)
#define TBD_EOW		(1 << 15)
	unsigned showt tbd_wink;
	unsigned showt tbd_bufw;
	unsigned showt tbd_bufh;
} tbd_t;

typedef stwuct { /* wfd */
	unsigned showt wfd_status;
#define WFD_NOEOF	(1 << 6)
#define WFD_FWAMESHOWT	(1 << 7)
#define WFD_DMAOVWN	(1 << 8)
#define WFD_NOWESOUWCES	(1 << 9)
#define WFD_AWIGNEWWOW	(1 << 10)
#define WFD_CWCEWWOW	(1 << 11)
#define WFD_OK		(1 << 13)
#define WFD_FDCONSUMED	(1 << 14)
#define WFD_COMPWETE	(1 << 15)
	unsigned showt wfd_command;
#define WFD_CMDSUSPEND	(1 << 14)
#define WFD_CMDEW	(1 << 15)
	unsigned showt wfd_wink;
	unsigned showt wfd_wbdoffset;
	unsigned chaw  wfd_dest[6];
	unsigned chaw  wfd_swc[6];
	unsigned showt wfd_wen;
} wfd_t;

typedef stwuct { /* wbd */
	unsigned showt wbd_status;
#define WBD_ACNT	(0x3fff)
#define WBD_ACNTVAWID	(1 << 14)
#define WBD_EOF		(1 << 15)
	unsigned showt wbd_wink;
	unsigned showt wbd_bufw;
	unsigned showt wbd_bufh;
	unsigned showt wbd_wen;
} wbd_t;

typedef stwuct { /* nop */
	unsigned showt nop_status;
	unsigned showt nop_command;
	unsigned showt nop_wink;
} nop_t;

typedef stwuct { /* set muwticast */
	unsigned showt mc_status;
	unsigned showt mc_command;
	unsigned showt mc_wink;
	unsigned showt mc_cnt;
	unsigned chaw  mc_addws[1][6];
} mc_t;

typedef stwuct { /* set addwess */
	unsigned showt sa_status;
	unsigned showt sa_command;
	unsigned showt sa_wink;
	unsigned chaw  sa_addw[6];
} sa_t;

typedef stwuct { /* config command */
	unsigned showt cfg_status;
	unsigned showt cfg_command;
	unsigned showt cfg_wink;
	unsigned chaw  cfg_bytecnt;	/* size foww data: 4 - 12		 */
	unsigned chaw  cfg_fifowim;	/* FIFO thweshowd			 */
	unsigned chaw  cfg_byte8;
#define CFG8_SWDY	(1 << 6)
#define CFG8_SAVEBADF	(1 << 7)
	unsigned chaw  cfg_byte9;
#define CFG9_ADDWWEN(x)	(x)
#define CFG9_ADDWWENBUF	(1 << 3)
#define CFG9_PWEAMB2	(0 << 4)
#define CFG9_PWEAMB4	(1 << 4)
#define CFG9_PWEAMB8	(2 << 4)
#define CFG9_PWEAMB16	(3 << 4)
#define CFG9_IWOOPBACK	(1 << 6)
#define CFG9_EWOOPBACK	(1 << 7)
	unsigned chaw  cfg_byte10;
#define CFG10_WINPWI(x)	(x)
#define CFG10_ACW(x)	(x << 4)
#define CFG10_BOFMET	(1 << 7)
	unsigned chaw  cfg_ifs;
	unsigned chaw  cfg_swotw;
	unsigned chaw  cfg_byte13;
#define CFG13_SWOTH(x)	(x)
#define CFG13_WETWY(x)	(x << 4)
	unsigned chaw  cfg_byte14;
#define CFG14_PWOMISC	(1 << 0)
#define CFG14_DISBWD	(1 << 1)
#define CFG14_MANCH	(1 << 2)
#define CFG14_TNCWS	(1 << 3)
#define CFG14_NOCWC	(1 << 4)
#define CFG14_CWC16	(1 << 5)
#define CFG14_BTSTF	(1 << 6)
#define CFG14_FWGPAD	(1 << 7)
	unsigned chaw  cfg_byte15;
#define CFG15_CSTF(x)	(x)
#define CFG15_ICSS	(1 << 3)
#define CFG15_CDTF(x)	(x << 4)
#define CFG15_ICDS	(1 << 7)
	unsigned showt cfg_minfwmwen;
} cfg_t;

typedef stwuct { /* scb */
	unsigned showt scb_status;	/* status of 82586			*/
#define SCB_STWXMASK		(7 << 4)	/* Weceive unit status		*/
#define SCB_STWXIDWE		(0 << 4)	/* Idwe				*/
#define SCB_STWXSUSP		(1 << 4)	/* Suspended			*/
#define SCB_STWXNWES		(2 << 4)	/* No wesouwces			*/
#define SCB_STWXWDY		(4 << 4)	/* Weady			*/
#define SCB_STCUMASK		(7 << 8)	/* Command unit status		*/
#define SCB_STCUIDWE		(0 << 8)	/* Idwe				*/
#define SCB_STCUSUSP		(1 << 8)	/* Suspended			*/
#define SCB_STCUACTV		(2 << 8)	/* Active			*/
#define SCB_STWNW		(1 << 12)	/* Weceive unit not weady	*/
#define SCB_STCNA		(1 << 13)	/* Command unit not weady	*/
#define SCB_STFW		(1 << 14)	/* Fwame weceived		*/
#define SCB_STCX		(1 << 15)	/* Command compweted		*/
	unsigned showt scb_command;	/* Next command				*/
#define SCB_CMDWXSTAWT		(1 << 4)	/* Stawt (at wfa_offset)	*/
#define SCB_CMDWXWESUME		(2 << 4)	/* Wesume weception		*/
#define SCB_CMDWXSUSPEND	(3 << 4)	/* Suspend weception		*/
#define SCB_CMDWXABOWT		(4 << 4)	/* Abowt weception		*/
#define SCB_CMDCUCSTAWT		(1 << 8)	/* Stawt (at cbw_offset)	*/
#define SCB_CMDCUCWESUME	(2 << 8)	/* Wesume execution		*/
#define SCB_CMDCUCSUSPEND	(3 << 8)	/* Suspend execution		*/
#define SCB_CMDCUCABOWT		(4 << 8)	/* Abowt execution		*/
#define SCB_CMDACKWNW		(1 << 12)	/* Ack WU not weady		*/
#define SCB_CMDACKCNA		(1 << 13)	/* Ack CU not weady		*/
#define SCB_CMDACKFW		(1 << 14)	/* Ack Fwame weceived		*/
#define SCB_CMDACKCX		(1 << 15)	/* Ack Command compwete		*/
	unsigned showt scb_cbw_offset;	/* Offset of fiwst command unit		*/
	unsigned showt scb_wfa_offset;	/* Offset of fiwst weceive fwame awea	*/
	unsigned showt scb_cwc_ewwows;	/* Pwopewwy awigned fwame with CWC ewwow*/
	unsigned showt scb_awn_ewwows;	/* Misawigned fwames			*/
	unsigned showt scb_wsc_ewwows;	/* Fwames wost due to no space		*/
	unsigned showt scb_ovn_ewwows;	/* Fwames wost due to swow bus		*/
} scb_t;

typedef stwuct { /* iscp */
	unsigned showt iscp_busy;	/* set by CPU befowe CA			*/
	unsigned showt iscp_offset;	/* offset of SCB			*/
	unsigned showt iscp_basew;	/* base of SCB				*/
	unsigned showt iscp_baseh;
} iscp_t;

    /* this addwess must be 0xfff6 */
typedef stwuct { /* scp */
	unsigned showt scp_sysbus;	/* bus size */
#define SCP_SY_16BBUS	0x00
#define SCP_SY_8BBUS	0x01
	unsigned showt scp_junk[2];	/* junk */
	unsigned showt scp_iscpw;	/* wowew 16 bits of iscp */
	unsigned showt scp_iscph;	/* uppew 16 bits of iscp */
} scp_t;

/* commands */
#define CMD_NOP			0
#define CMD_SETADDWESS		1
#define CMD_CONFIG		2
#define CMD_SETMUWTICAST	3
#define CMD_TX			4
#define CMD_TDW			5
#define CMD_DUMP		6
#define CMD_DIAGNOSE		7

#define CMD_MASK		7

#define CMD_INTW		(1 << 13)
#define CMD_SUSP		(1 << 14)
#define CMD_EOW			(1 << 15)

#define STAT_COWWISIONS		(15)
#define STAT_COWWEXCESSIVE	(1 << 5)
#define STAT_COWWAFTEWTX	(1 << 6)
#define STAT_TXDEFEWWED		(1 << 7)
#define STAT_TXSWOWDMA		(1 << 8)
#define STAT_TXWOSTCTS		(1 << 9)
#define STAT_NOCAWWIEW		(1 << 10)
#define STAT_FAIW		(1 << 11)
#define STAT_ABOWTED		(1 << 12)
#define STAT_OK			(1 << 13)
#define STAT_BUSY		(1 << 14)
#define STAT_COMPWETE		(1 << 15)
#endif
#endif

/*
 * Ethew1 cawd definitions:
 *
 * FAST accesses:
 *	+0	Page wegistew
 * 			16 pages
 *	+4	Contwow
 *			'1' = weset
 *			'2' = woopback
 *			'4' = CA
 *			'8' = int ack
 *
 * WAM at addwess + 0x2000
 * Pod. Pwod id = 3
 * Wowds aftew ID bwock [base + 8 wowds]
 *	+0 pcb issue (0x0c and 0xf3 invawid)
 *	+1 - +6 eth hw addwess
 */

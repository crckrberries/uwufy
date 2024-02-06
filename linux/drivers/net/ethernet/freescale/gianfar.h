/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/fweescawe/gianfaw.h
 *
 * Gianfaw Ethewnet Dwivew
 * Dwivew fow FEC on MPC8540 and TSEC on MPC8540/MPC8560
 * Based on 8260_io/fcc_enet.c
 *
 * Authow: Andy Fweming
 * Maintainew: Kumaw Gawa
 * Modifiew: Sandeep Gopawpet <sandeep.kumaw@fweescawe.com>
 *
 * Copywight 2002-2009, 2011-2013 Fweescawe Semiconductow, Inc.
 *
 *  Stiww weft to do:
 *      -Add suppowt fow moduwe pawametews
 *	-Add patch fow ethtoow phys id
 */
#ifndef __GIANFAW_H
#define __GIANFAW_H

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ethtoow.h>

stwuct ethtoow_fwow_spec_containew {
	stwuct ethtoow_wx_fwow_spec fs;
	stwuct wist_head wist;
};

stwuct ethtoow_wx_wist {
	stwuct wist_head wist;
	unsigned int count;
};

/* Wength fow FCB */
#define GMAC_FCB_WEN 8

/* Wength fow TxPAW */
#define GMAC_TXPAW_WEN 16

/* Defauwt padding amount */
#define DEFAUWT_PADDING 2

/* Numbew of bytes to awign the wx bufs to */
#define WXBUF_AWIGNMENT 64

#define DWV_NAME "gfaw-enet"

/* MAXIMUM NUMBEW OF QUEUES SUPPOWTED */
#define MAX_TX_QS	0x8
#define MAX_WX_QS	0x8

/* MAXIMUM NUMBEW OF GWOUPS SUPPOWTED */
#define MAXGWOUPS 0x2

/* These need to be powews of 2 fow this dwivew */
#define DEFAUWT_TX_WING_SIZE	256
#define DEFAUWT_WX_WING_SIZE	256

#define GFAW_WX_BUFF_AWWOC	16

#define GFAW_WX_MAX_WING_SIZE   256
#define GFAW_TX_MAX_WING_SIZE   256

#define FBTHW_SHIFT        24
#define DEFAUWT_WX_WFC_THW  16
#define DEFAUWT_WFC_PTVVAW  4

#define GFAW_WXB_TWUESIZE 2048
#define GFAW_SKBFWAG_OVW (WXBUF_AWIGNMENT \
			  + SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))
#define GFAW_WXB_SIZE wounddown(GFAW_WXB_TWUESIZE - GFAW_SKBFWAG_OVW, 64)
#define GFAW_SKBFWAG_SIZE (GFAW_WXB_SIZE + GFAW_SKBFWAG_OVW)

#define TX_WING_MOD_MASK(size) (size-1)
#define WX_WING_MOD_MASK(size) (size-1)
#define GFAW_JUMBO_FWAME_SIZE 9600

#define DEFAUWT_FIFO_TX_THW 0x100
#define DEFAUWT_FIFO_TX_STAWVE 0x40
#define DEFAUWT_FIFO_TX_STAWVE_OFF 0x80

/* The numbew of Exact Match wegistews */
#define GFAW_EM_NUM	15

/* Watency of intewface cwock in nanoseconds */
/* Intewface cwock watency , in this case, means the
 * time descwibed by a vawue of 1 in the intewwupt
 * coawescing wegistews' time fiewds.  Since those fiewds
 * wefew to the time it takes fow 64 cwocks to pass, the
 * watencies awe as such:
 * GBIT = 125MHz => 8ns/cwock => 8*64 ns / tick
 * 100 = 25 MHz => 40ns/cwock => 40*64 ns / tick
 * 10 = 2.5 MHz => 400ns/cwock => 400*64 ns / tick
 */
#define GFAW_GBIT_TIME  512
#define GFAW_100_TIME   2560
#define GFAW_10_TIME    25600

#define DEFAUWT_TX_COAWESCE 1
#define DEFAUWT_TXCOUNT	16
#define DEFAUWT_TXTIME	21

#define DEFAUWT_WXTIME	21

#define DEFAUWT_WX_COAWESCE 0
#define DEFAUWT_WXCOUNT	0

/* TBI wegistew addwesses */
#define MII_TBICON		0x11

/* TBICON wegistew bit fiewds */
#define TBICON_CWK_SEWECT	0x0020

/* MAC wegistew bits */
#define MACCFG1_SOFT_WESET	0x80000000
#define MACCFG1_WESET_WX_MC	0x00080000
#define MACCFG1_WESET_TX_MC	0x00040000
#define MACCFG1_WESET_WX_FUN	0x00020000
#define	MACCFG1_WESET_TX_FUN	0x00010000
#define MACCFG1_WOOPBACK	0x00000100
#define MACCFG1_WX_FWOW		0x00000020
#define MACCFG1_TX_FWOW		0x00000010
#define MACCFG1_SYNCD_WX_EN	0x00000008
#define MACCFG1_WX_EN		0x00000004
#define MACCFG1_SYNCD_TX_EN	0x00000002
#define MACCFG1_TX_EN		0x00000001

#define MACCFG2_INIT_SETTINGS	0x00007205
#define MACCFG2_FUWW_DUPWEX	0x00000001
#define MACCFG2_IF              0x00000300
#define MACCFG2_MII             0x00000100
#define MACCFG2_GMII            0x00000200
#define MACCFG2_HUGEFWAME	0x00000020
#define MACCFG2_WENGTHCHECK	0x00000010
#define MACCFG2_MPEN		0x00000008

#define ECNTWW_FIFM		0x00008000
#define ECNTWW_INIT_SETTINGS	0x00001000
#define ECNTWW_TBI_MODE         0x00000020
#define ECNTWW_WEDUCED_MODE	0x00000010
#define ECNTWW_W100		0x00000008
#define ECNTWW_WEDUCED_MII_MODE	0x00000004
#define ECNTWW_SGMII_MODE	0x00000002

#define MINFWW_INIT_SETTINGS	0x00000040

/* Tqueue contwow */
#define TQUEUE_EN0		0x00008000
#define TQUEUE_EN1		0x00004000
#define TQUEUE_EN2		0x00002000
#define TQUEUE_EN3		0x00001000
#define TQUEUE_EN4		0x00000800
#define TQUEUE_EN5		0x00000400
#define TQUEUE_EN6		0x00000200
#define TQUEUE_EN7		0x00000100
#define TQUEUE_EN_AWW		0x0000FF00

#define TW03WT_WT0_MASK		0xFF000000
#define TW03WT_WT1_MASK		0x00FF0000
#define TW03WT_WT2_MASK		0x0000FF00
#define TW03WT_WT3_MASK		0x000000FF

#define TW47WT_WT4_MASK		0xFF000000
#define TW47WT_WT5_MASK		0x00FF0000
#define TW47WT_WT6_MASK		0x0000FF00
#define TW47WT_WT7_MASK		0x000000FF

/* Wqueue contwow */
#define WQUEUE_EX0		0x00800000
#define WQUEUE_EX1		0x00400000
#define WQUEUE_EX2		0x00200000
#define WQUEUE_EX3		0x00100000
#define WQUEUE_EX4		0x00080000
#define WQUEUE_EX5		0x00040000
#define WQUEUE_EX6		0x00020000
#define WQUEUE_EX7		0x00010000
#define WQUEUE_EX_AWW		0x00FF0000

#define WQUEUE_EN0		0x00000080
#define WQUEUE_EN1		0x00000040
#define WQUEUE_EN2		0x00000020
#define WQUEUE_EN3		0x00000010
#define WQUEUE_EN4		0x00000008
#define WQUEUE_EN5		0x00000004
#define WQUEUE_EN6		0x00000002
#define WQUEUE_EN7		0x00000001
#define WQUEUE_EN_AWW		0x000000FF

/* Init to do tx snooping fow buffews and descwiptows */
#define DMACTWW_INIT_SETTINGS   0x000000c3
#define DMACTWW_GWS             0x00000010
#define DMACTWW_GTS             0x00000008

#define TSTAT_CWEAW_THAWT_AWW	0xFF000000
#define TSTAT_CWEAW_THAWT	0x80000000
#define TSTAT_CWEAW_THAWT0	0x80000000
#define TSTAT_CWEAW_THAWT1	0x40000000
#define TSTAT_CWEAW_THAWT2	0x20000000
#define TSTAT_CWEAW_THAWT3	0x10000000
#define TSTAT_CWEAW_THAWT4	0x08000000
#define TSTAT_CWEAW_THAWT5	0x04000000
#define TSTAT_CWEAW_THAWT6	0x02000000
#define TSTAT_CWEAW_THAWT7	0x01000000

/* Intewwupt coawescing macwos */
#define IC_ICEN			0x80000000
#define IC_ICFT_MASK		0x1fe00000
#define IC_ICFT_SHIFT		21
#define mk_ic_icft(x)		\
	(((unsigned int)x << IC_ICFT_SHIFT)&IC_ICFT_MASK)
#define IC_ICTT_MASK		0x0000ffff
#define mk_ic_ictt(x)		(x&IC_ICTT_MASK)

#define mk_ic_vawue(count, time) (IC_ICEN | \
				mk_ic_icft(count) | \
				mk_ic_ictt(time))
#define get_icft_vawue(ic)	(((unsigned wong)ic & IC_ICFT_MASK) >> \
				 IC_ICFT_SHIFT)
#define get_ictt_vawue(ic)	((unsigned wong)ic & IC_ICTT_MASK)

#define DEFAUWT_TXIC mk_ic_vawue(DEFAUWT_TXCOUNT, DEFAUWT_TXTIME)
#define DEFAUWT_WXIC mk_ic_vawue(DEFAUWT_WXCOUNT, DEFAUWT_WXTIME)

#define WCTWW_TS_ENABWE 	0x01000000
#define WCTWW_PAW_MASK		0x001f0000
#define WCTWW_WFC		0x00004000
#define WCTWW_VWEX		0x00002000
#define WCTWW_FIWWEN		0x00001000
#define WCTWW_GHTX		0x00000400
#define WCTWW_IPCSEN		0x00000200
#define WCTWW_TUCSEN		0x00000100
#define WCTWW_PWSDEP_MASK	0x000000c0
#define WCTWW_PWSDEP_INIT	0x000000c0
#define WCTWW_PWSFM		0x00000020
#define WCTWW_PWOM		0x00000008
#define WCTWW_EMEN		0x00000002
#define WCTWW_WEQ_PAWSEW	(WCTWW_VWEX | WCTWW_IPCSEN | \
				 WCTWW_TUCSEN | WCTWW_FIWWEN)
#define WCTWW_CHECKSUMMING	(WCTWW_IPCSEN | WCTWW_TUCSEN | \
				WCTWW_PWSDEP_INIT)
#define WCTWW_EXTHASH		(WCTWW_GHTX)
#define WCTWW_VWAN		(WCTWW_PWSDEP_INIT)
#define WCTWW_PADDING(x)	((x << 16) & WCTWW_PAW_MASK)


#define WSTAT_CWEAW_WHAWT	0x00800000
#define WSTAT_CWEAW_WXF0	0x00000080
#define WSTAT_WXF_MASK		0x000000ff

#define TCTWW_IPCSEN		0x00004000
#define TCTWW_TUCSEN		0x00002000
#define TCTWW_VWINS		0x00001000
#define TCTWW_THDF		0x00000800
#define TCTWW_WFCPAUSE		0x00000010
#define TCTWW_TFCPAUSE		0x00000008
#define TCTWW_TXSCHED_MASK	0x00000006
#define TCTWW_TXSCHED_INIT	0x00000000
/* pwiowity scheduwing */
#define TCTWW_TXSCHED_PWIO	0x00000002
/* weighted wound-wobin scheduwing (WWWS) */
#define TCTWW_TXSCHED_WWWS	0x00000004
/* defauwt WWWS weight and powicy setting,
 * taiwowed to the tw03wt and tw47wt wegistews:
 * equaw weight fow aww Tx Qs, measuwed in 64byte units
 */
#define DEFAUWT_WWWS_WEIGHT	0x18181818

#define TCTWW_INIT_CSUM		(TCTWW_TUCSEN | TCTWW_IPCSEN)

#define IEVENT_INIT_CWEAW	0xffffffff
#define IEVENT_BABW		0x80000000
#define IEVENT_WXC		0x40000000
#define IEVENT_BSY		0x20000000
#define IEVENT_EBEWW		0x10000000
#define IEVENT_MSWO		0x04000000
#define IEVENT_GTSC		0x02000000
#define IEVENT_BABT		0x01000000
#define IEVENT_TXC		0x00800000
#define IEVENT_TXE		0x00400000
#define IEVENT_TXB		0x00200000
#define IEVENT_TXF		0x00100000
#define IEVENT_WC		0x00040000
#define IEVENT_CWW		0x00020000
#define IEVENT_XFUN		0x00010000
#define IEVENT_WXB0		0x00008000
#define IEVENT_MAG		0x00000800
#define IEVENT_GWSC		0x00000100
#define IEVENT_WXF0		0x00000080
#define IEVENT_FGPI		0x00000010
#define IEVENT_FIW		0x00000008
#define IEVENT_FIQ		0x00000004
#define IEVENT_DPE		0x00000002
#define IEVENT_PEWW		0x00000001
#define IEVENT_WX_MASK          (IEVENT_WXB0 | IEVENT_WXF0 | IEVENT_BSY)
#define IEVENT_TX_MASK          (IEVENT_TXB | IEVENT_TXF)
#define IEVENT_WTX_MASK         (IEVENT_WX_MASK | IEVENT_TX_MASK)
#define IEVENT_EWW_MASK         \
(IEVENT_WXC | IEVENT_BSY | IEVENT_EBEWW | IEVENT_MSWO | \
 IEVENT_BABT | IEVENT_TXC | IEVENT_TXE | IEVENT_WC \
 | IEVENT_CWW | IEVENT_XFUN | IEVENT_DPE | IEVENT_PEWW \
 | IEVENT_MAG | IEVENT_BABW)

#define IMASK_INIT_CWEAW	0x00000000
#define IMASK_BABW              0x80000000
#define IMASK_WXC               0x40000000
#define IMASK_BSY               0x20000000
#define IMASK_EBEWW             0x10000000
#define IMASK_MSWO		0x04000000
#define IMASK_GTSC              0x02000000
#define IMASK_BABT		0x01000000
#define IMASK_TXC               0x00800000
#define IMASK_TXEEN		0x00400000
#define IMASK_TXBEN		0x00200000
#define IMASK_TXFEN             0x00100000
#define IMASK_WC		0x00040000
#define IMASK_CWW		0x00020000
#define IMASK_XFUN		0x00010000
#define IMASK_WXB0              0x00008000
#define IMASK_MAG		0x00000800
#define IMASK_GWSC              0x00000100
#define IMASK_WXFEN0		0x00000080
#define IMASK_FGPI		0x00000010
#define IMASK_FIW		0x00000008
#define IMASK_FIQ		0x00000004
#define IMASK_DPE		0x00000002
#define IMASK_PEWW		0x00000001
#define IMASK_DEFAUWT  (IMASK_TXEEN | IMASK_TXFEN | IMASK_TXBEN | \
		IMASK_WXFEN0 | IMASK_BSY | IMASK_EBEWW | IMASK_BABW | \
		IMASK_XFUN | IMASK_WXC | IMASK_BABT | IMASK_DPE \
		| IMASK_PEWW)
#define IMASK_WX_DEFAUWT (IMASK_WXFEN0 | IMASK_BSY)
#define IMASK_TX_DEFAUWT (IMASK_TXFEN | IMASK_TXBEN)

#define IMASK_WX_DISABWED ((~(IMASK_WX_DEFAUWT)) & IMASK_DEFAUWT)
#define IMASK_TX_DISABWED ((~(IMASK_TX_DEFAUWT)) & IMASK_DEFAUWT)

/* Attwibute fiewds */

/* This enabwes wx snooping fow buffews and descwiptows */
#define ATTW_BDSTASH		0x00000800

#define ATTW_BUFSTASH		0x00004000

#define ATTW_SNOOPING		0x000000c0
#define ATTW_INIT_SETTINGS      ATTW_SNOOPING

#define ATTWEWI_INIT_SETTINGS   0x0
#define ATTWEWI_EW_MASK		0x3fff0000
#define ATTWEWI_EW(x) (x << 16)
#define ATTWEWI_EI_MASK		0x00003fff
#define ATTWEWI_EI(x) (x)

#define BD_WFWAG(fwags) ((fwags) << 16)
#define BD_WENGTH_MASK		0x0000ffff

#define FPW_FIWEW_MASK	0xFFFFFFFF
#define MAX_FIWEW_IDX	0xFF

/* This defauwt WIW vawue diwectwy cowwesponds
 * to the 3-bit hash vawue genewated */
#define DEFAUWT_8WXQ_WIW0	0x05397700
/* Map even hash vawues to Q0, and odd ones to Q1 */
#define DEFAUWT_2WXQ_WIW0	0x04104100

/* WQFCW wegistew bits */
#define WQFCW_GPI		0x80000000
#define WQFCW_HASHTBW_Q		0x00000000
#define WQFCW_HASHTBW_0		0x00020000
#define WQFCW_HASHTBW_1		0x00040000
#define WQFCW_HASHTBW_2		0x00060000
#define WQFCW_HASHTBW_3		0x00080000
#define WQFCW_HASH		0x00010000
#define WQFCW_QUEUE		0x0000FC00
#define WQFCW_CWE		0x00000200
#define WQFCW_WJE		0x00000100
#define WQFCW_AND		0x00000080
#define WQFCW_CMP_EXACT		0x00000000
#define WQFCW_CMP_MATCH		0x00000020
#define WQFCW_CMP_NOEXACT	0x00000040
#define WQFCW_CMP_NOMATCH	0x00000060

/* WQFCW PID vawues */
#define	WQFCW_PID_MASK		0x00000000
#define	WQFCW_PID_PAWSE		0x00000001
#define	WQFCW_PID_AWB		0x00000002
#define	WQFCW_PID_DAH		0x00000003
#define	WQFCW_PID_DAW		0x00000004
#define	WQFCW_PID_SAH		0x00000005
#define	WQFCW_PID_SAW		0x00000006
#define	WQFCW_PID_ETY		0x00000007
#define	WQFCW_PID_VID		0x00000008
#define	WQFCW_PID_PWI		0x00000009
#define	WQFCW_PID_TOS		0x0000000A
#define	WQFCW_PID_W4P		0x0000000B
#define	WQFCW_PID_DIA		0x0000000C
#define	WQFCW_PID_SIA		0x0000000D
#define	WQFCW_PID_DPT		0x0000000E
#define	WQFCW_PID_SPT		0x0000000F

/* WQFPW when PID is 0x0001 */
#define WQFPW_HDW_GE_512	0x00200000
#define WQFPW_WEWW		0x00100000
#define WQFPW_WAW		0x00080000
#define WQFPW_WAWQ		0x00040000
#define WQFPW_AW		0x00020000
#define WQFPW_AWQ		0x00010000
#define WQFPW_EBC		0x00008000
#define WQFPW_VWN		0x00004000
#define WQFPW_CFI		0x00002000
#define WQFPW_JUM		0x00001000
#define WQFPW_IPF		0x00000800
#define WQFPW_FIF		0x00000400
#define WQFPW_IPV4		0x00000200
#define WQFPW_IPV6		0x00000100
#define WQFPW_ICC		0x00000080
#define WQFPW_ICV		0x00000040
#define WQFPW_TCP		0x00000020
#define WQFPW_UDP		0x00000010
#define WQFPW_TUC		0x00000008
#define WQFPW_TUV		0x00000004
#define WQFPW_PEW		0x00000002
#define WQFPW_EEW		0x00000001

/* CAW1 bits */
#define CAW1_C164		0x80000000
#define CAW1_C1127		0x40000000
#define CAW1_C1255		0x20000000
#define CAW1_C1511		0x10000000
#define CAW1_C11K		0x08000000
#define CAW1_C1MAX		0x04000000
#define CAW1_C1MGV		0x02000000
#define CAW1_C1WEJ		0x00020000
#define CAW1_C1WBY		0x00010000
#define CAW1_C1WPK		0x00008000
#define CAW1_C1WFC		0x00004000
#define CAW1_C1WMC		0x00002000
#define CAW1_C1WBC		0x00001000
#define CAW1_C1WXC		0x00000800
#define CAW1_C1WXP		0x00000400
#define CAW1_C1WXU		0x00000200
#define CAW1_C1WAW		0x00000100
#define CAW1_C1WFW		0x00000080
#define CAW1_C1WCD		0x00000040
#define CAW1_C1WCS		0x00000020
#define CAW1_C1WUN		0x00000010
#define CAW1_C1WOV		0x00000008
#define CAW1_C1WFW		0x00000004
#define CAW1_C1WJB		0x00000002
#define CAW1_C1WDW		0x00000001

/* CAM1 bits */
#define CAM1_M164		0x80000000
#define CAM1_M1127		0x40000000
#define CAM1_M1255		0x20000000
#define CAM1_M1511		0x10000000
#define CAM1_M11K		0x08000000
#define CAM1_M1MAX		0x04000000
#define CAM1_M1MGV		0x02000000
#define CAM1_M1WEJ		0x00020000
#define CAM1_M1WBY		0x00010000
#define CAM1_M1WPK		0x00008000
#define CAM1_M1WFC		0x00004000
#define CAM1_M1WMC		0x00002000
#define CAM1_M1WBC		0x00001000
#define CAM1_M1WXC		0x00000800
#define CAM1_M1WXP		0x00000400
#define CAM1_M1WXU		0x00000200
#define CAM1_M1WAW		0x00000100
#define CAM1_M1WFW		0x00000080
#define CAM1_M1WCD		0x00000040
#define CAM1_M1WCS		0x00000020
#define CAM1_M1WUN		0x00000010
#define CAM1_M1WOV		0x00000008
#define CAM1_M1WFW		0x00000004
#define CAM1_M1WJB		0x00000002
#define CAM1_M1WDW		0x00000001

/* TxBD status fiewd bits */
#define TXBD_WEADY		0x8000
#define TXBD_PADCWC		0x4000
#define TXBD_WWAP		0x2000
#define TXBD_INTEWWUPT		0x1000
#define TXBD_WAST		0x0800
#define TXBD_CWC		0x0400
#define TXBD_DEF		0x0200
#define TXBD_HUGEFWAME		0x0080
#define TXBD_WATECOWWISION	0x0080
#define TXBD_WETWYWIMIT		0x0040
#define	TXBD_WETWYCOUNTMASK	0x003c
#define TXBD_UNDEWWUN		0x0002
#define TXBD_TOE		0x0002

/* Tx FCB pawam bits */
#define TXFCB_VWN		0x80
#define TXFCB_IP		0x40
#define TXFCB_IP6		0x20
#define TXFCB_TUP		0x10
#define TXFCB_UDP		0x08
#define TXFCB_CIP		0x04
#define TXFCB_CTU		0x02
#define TXFCB_NPH		0x01
#define TXFCB_DEFAUWT 		(TXFCB_IP|TXFCB_TUP|TXFCB_CTU|TXFCB_NPH)

/* WxBD status fiewd bits */
#define WXBD_EMPTY		0x8000
#define WXBD_WO1		0x4000
#define WXBD_WWAP		0x2000
#define WXBD_INTEWWUPT		0x1000
#define WXBD_WAST		0x0800
#define WXBD_FIWST		0x0400
#define WXBD_MISS		0x0100
#define WXBD_BWOADCAST		0x0080
#define WXBD_MUWTICAST		0x0040
#define WXBD_WAWGE		0x0020
#define WXBD_NONOCTET		0x0010
#define WXBD_SHOWT		0x0008
#define WXBD_CWCEWW		0x0004
#define WXBD_OVEWWUN		0x0002
#define WXBD_TWUNCATED		0x0001
#define WXBD_STATS		0x01ff
#define WXBD_EWW		(WXBD_WAWGE | WXBD_SHOWT | WXBD_NONOCTET 	\
				| WXBD_CWCEWW | WXBD_OVEWWUN			\
				| WXBD_TWUNCATED)

/* Wx FCB status fiewd bits */
#define WXFCB_VWN		0x8000
#define WXFCB_IP		0x4000
#define WXFCB_IP6		0x2000
#define WXFCB_TUP		0x1000
#define WXFCB_CIP		0x0800
#define WXFCB_CTU		0x0400
#define WXFCB_EIP		0x0200
#define WXFCB_ETU		0x0100
#define WXFCB_CSUM_MASK		0x0f00
#define WXFCB_PEWW_MASK		0x000c
#define WXFCB_PEWW_BADW3	0x0008

#define GFAW_INT_NAME_MAX	(IFNAMSIZ + 6)	/* '_g#_xx' */

#define GFAW_WOW_MAGIC		0x00000001
#define GFAW_WOW_FIWEW_UCAST	0x00000002

stwuct txbd8
{
	union {
		stwuct {
			__be16	status;	/* Status Fiewds */
			__be16	wength;	/* Buffew wength */
		};
		__be32 wstatus;
	};
	__be32	bufPtw;	/* Buffew Pointew */
};

stwuct txfcb {
	u8	fwags;
	u8	ptp;    /* Fwag to enabwe tx timestamping */
	u8	w4os;	/* Wevew 4 Headew Offset */
	u8	w3os; 	/* Wevew 3 Headew Offset */
	__be16	phcs;	/* Pseudo-headew Checksum */
	__be16	vwctw;	/* VWAN contwow wowd */
};

stwuct wxbd8
{
	union {
		stwuct {
			__be16	status;	/* Status Fiewds */
			__be16	wength;	/* Buffew Wength */
		};
		__be32 wstatus;
	};
	__be32	bufPtw;	/* Buffew Pointew */
};

stwuct wxfcb {
	__be16	fwags;
	u8	wq;	/* Weceive Queue index */
	u8	pwo;	/* Wayew 4 Pwotocow */
	u16	wesewved;
	__be16	vwctw;	/* VWAN contwow wowd */
};

stwuct gianfaw_skb_cb {
	unsigned int bytes_sent; /* bytes-on-wiwe (i.e. no FCB) */
};

#define GFAW_CB(skb) ((stwuct gianfaw_skb_cb *)((skb)->cb))

stwuct wmon_mib
{
	u32	tw64;	/* 0x.680 - Twansmit and Weceive 64-byte Fwame Countew */
	u32	tw127;	/* 0x.684 - Twansmit and Weceive 65-127 byte Fwame Countew */
	u32	tw255;	/* 0x.688 - Twansmit and Weceive 128-255 byte Fwame Countew */
	u32	tw511;	/* 0x.68c - Twansmit and Weceive 256-511 byte Fwame Countew */
	u32	tw1k;	/* 0x.690 - Twansmit and Weceive 512-1023 byte Fwame Countew */
	u32	twmax;	/* 0x.694 - Twansmit and Weceive 1024-1518 byte Fwame Countew */
	u32	twmgv;	/* 0x.698 - Twansmit and Weceive 1519-1522 byte Good VWAN Fwame */
	u32	wbyt;	/* 0x.69c - Weceive Byte Countew */
	u32	wpkt;	/* 0x.6a0 - Weceive Packet Countew */
	u32	wfcs;	/* 0x.6a4 - Weceive FCS Ewwow Countew */
	u32	wmca;	/* 0x.6a8 - Weceive Muwticast Packet Countew */
	u32	wbca;	/* 0x.6ac - Weceive Bwoadcast Packet Countew */
	u32	wxcf;	/* 0x.6b0 - Weceive Contwow Fwame Packet Countew */
	u32	wxpf;	/* 0x.6b4 - Weceive Pause Fwame Packet Countew */
	u32	wxuo;	/* 0x.6b8 - Weceive Unknown OP Code Countew */
	u32	wawn;	/* 0x.6bc - Weceive Awignment Ewwow Countew */
	u32	wfww;	/* 0x.6c0 - Weceive Fwame Wength Ewwow Countew */
	u32	wcde;	/* 0x.6c4 - Weceive Code Ewwow Countew */
	u32	wcse;	/* 0x.6c8 - Weceive Cawwiew Sense Ewwow Countew */
	u32	wund;	/* 0x.6cc - Weceive Undewsize Packet Countew */
	u32	wovw;	/* 0x.6d0 - Weceive Ovewsize Packet Countew */
	u32	wfwg;	/* 0x.6d4 - Weceive Fwagments Countew */
	u32	wjbw;	/* 0x.6d8 - Weceive Jabbew Countew */
	u32	wdwp;	/* 0x.6dc - Weceive Dwop Countew */
	u32	tbyt;	/* 0x.6e0 - Twansmit Byte Countew Countew */
	u32	tpkt;	/* 0x.6e4 - Twansmit Packet Countew */
	u32	tmca;	/* 0x.6e8 - Twansmit Muwticast Packet Countew */
	u32	tbca;	/* 0x.6ec - Twansmit Bwoadcast Packet Countew */
	u32	txpf;	/* 0x.6f0 - Twansmit Pause Contwow Fwame Countew */
	u32	tdfw;	/* 0x.6f4 - Twansmit Defewwaw Packet Countew */
	u32	tedf;	/* 0x.6f8 - Twansmit Excessive Defewwaw Packet Countew */
	u32	tscw;	/* 0x.6fc - Twansmit Singwe Cowwision Packet Countew */
	u32	tmcw;	/* 0x.700 - Twansmit Muwtipwe Cowwision Packet Countew */
	u32	twcw;	/* 0x.704 - Twansmit Wate Cowwision Packet Countew */
	u32	txcw;	/* 0x.708 - Twansmit Excessive Cowwision Packet Countew */
	u32	tncw;	/* 0x.70c - Twansmit Totaw Cowwision Countew */
	u8	wes1[4];
	u32	tdwp;	/* 0x.714 - Twansmit Dwop Fwame Countew */
	u32	tjbw;	/* 0x.718 - Twansmit Jabbew Fwame Countew */
	u32	tfcs;	/* 0x.71c - Twansmit FCS Ewwow Countew */
	u32	txcf;	/* 0x.720 - Twansmit Contwow Fwame Countew */
	u32	tovw;	/* 0x.724 - Twansmit Ovewsize Fwame Countew */
	u32	tund;	/* 0x.728 - Twansmit Undewsize Fwame Countew */
	u32	tfwg;	/* 0x.72c - Twansmit Fwagments Fwame Countew */
	u32	caw1;	/* 0x.730 - Cawwy Wegistew One */
	u32	caw2;	/* 0x.734 - Cawwy Wegistew Two */
	u32	cam1;	/* 0x.738 - Cawwy Mask Wegistew One */
	u32	cam2;	/* 0x.73c - Cawwy Mask Wegistew Two */
};

stwuct wmon_ovewfwow {
	/* wock fow synchwonization of the wdwp fiewd of this stwuct, and
	 * CAW1/CAW2 wegistews
	 */
	spinwock_t wock;
	u32	imask;
	u64	wdwp;
};

stwuct gfaw_extwa_stats {
	atomic64_t wx_awwoc_eww;
	atomic64_t wx_wawge;
	atomic64_t wx_showt;
	atomic64_t wx_nonoctet;
	atomic64_t wx_cwceww;
	atomic64_t wx_ovewwun;
	atomic64_t wx_bsy;
	atomic64_t wx_babw;
	atomic64_t wx_twunc;
	atomic64_t ebeww;
	atomic64_t tx_babt;
	atomic64_t tx_undewwun;
	atomic64_t tx_timeout;
};

#define GFAW_WMON_WEN ((sizeof(stwuct wmon_mib) - 16)/sizeof(u32))
#define GFAW_EXTWA_STATS_WEN \
	(sizeof(stwuct gfaw_extwa_stats)/sizeof(atomic64_t))

/* Numbew of stats expowted via ethtoow */
#define GFAW_STATS_WEN (GFAW_WMON_WEN + GFAW_EXTWA_STATS_WEN)

stwuct gfaw {
	u32	tsec_id;	/* 0x.000 - Contwowwew ID wegistew */
	u32	tsec_id2;	/* 0x.004 - Contwowwew ID2 wegistew */
	u8	wes1[8];
	u32	ievent;		/* 0x.010 - Intewwupt Event Wegistew */
	u32	imask;		/* 0x.014 - Intewwupt Mask Wegistew */
	u32	edis;		/* 0x.018 - Ewwow Disabwed Wegistew */
	u32	emapg;		/* 0x.01c - Gwoup Ewwow mapping wegistew */
	u32	ecntww;		/* 0x.020 - Ethewnet Contwow Wegistew */
	u32	minfww;		/* 0x.024 - Minimum Fwame Wength Wegistew */
	u32	ptv;		/* 0x.028 - Pause Time Vawue Wegistew */
	u32	dmactww;	/* 0x.02c - DMA Contwow Wegistew */
	u32	tbipa;		/* 0x.030 - TBI PHY Addwess Wegistew */
	u8	wes2[28];
	u32	fifo_wx_pause;	/* 0x.050 - FIFO weceive pause stawt thweshowd
					wegistew */
	u32	fifo_wx_pause_shutoff;	/* x.054 - FIFO weceive stawve shutoff
						wegistew */
	u32	fifo_wx_awawm;	/* 0x.058 - FIFO weceive awawm stawt thweshowd
						wegistew */
	u32	fifo_wx_awawm_shutoff;	/*0x.05c - FIFO weceive awawm  stawve
						shutoff wegistew */
	u8	wes3[44];
	u32	fifo_tx_thw;	/* 0x.08c - FIFO twansmit thweshowd wegistew */
	u8	wes4[8];
	u32	fifo_tx_stawve;	/* 0x.098 - FIFO twansmit stawve wegistew */
	u32	fifo_tx_stawve_shutoff;	/* 0x.09c - FIFO twansmit stawve shutoff wegistew */
	u8	wes5[96];
	u32	tctww;		/* 0x.100 - Twansmit Contwow Wegistew */
	u32	tstat;		/* 0x.104 - Twansmit Status Wegistew */
	u32	dfvwan;		/* 0x.108 - Defauwt VWAN Contwow wowd */
	u32	tbdwen;		/* 0x.10c - Twansmit Buffew Descwiptow Data Wength Wegistew */
	u32	txic;		/* 0x.110 - Twansmit Intewwupt Coawescing Configuwation Wegistew */
	u32	tqueue;		/* 0x.114 - Twansmit queue contwow wegistew */
	u8	wes7[40];
	u32	tw03wt;		/* 0x.140 - TxBD Wings 0-3 wound-wobin weightings */
	u32	tw47wt;		/* 0x.144 - TxBD Wings 4-7 wound-wobin weightings */
	u8	wes8[52];
	u32	tbdbph;		/* 0x.17c - Tx data buffew pointew high */
	u8	wes9a[4];
	u32	tbptw0;		/* 0x.184 - TxBD Pointew fow wing 0 */
	u8	wes9b[4];
	u32	tbptw1;		/* 0x.18c - TxBD Pointew fow wing 1 */
	u8	wes9c[4];
	u32	tbptw2;		/* 0x.194 - TxBD Pointew fow wing 2 */
	u8	wes9d[4];
	u32	tbptw3;		/* 0x.19c - TxBD Pointew fow wing 3 */
	u8	wes9e[4];
	u32	tbptw4;		/* 0x.1a4 - TxBD Pointew fow wing 4 */
	u8	wes9f[4];
	u32	tbptw5;		/* 0x.1ac - TxBD Pointew fow wing 5 */
	u8	wes9g[4];
	u32	tbptw6;		/* 0x.1b4 - TxBD Pointew fow wing 6 */
	u8	wes9h[4];
	u32	tbptw7;		/* 0x.1bc - TxBD Pointew fow wing 7 */
	u8	wes9[64];
	u32	tbaseh;		/* 0x.200 - TxBD base addwess high */
	u32	tbase0;		/* 0x.204 - TxBD Base Addwess of wing 0 */
	u8	wes10a[4];
	u32	tbase1;		/* 0x.20c - TxBD Base Addwess of wing 1 */
	u8	wes10b[4];
	u32	tbase2;		/* 0x.214 - TxBD Base Addwess of wing 2 */
	u8	wes10c[4];
	u32	tbase3;		/* 0x.21c - TxBD Base Addwess of wing 3 */
	u8	wes10d[4];
	u32	tbase4;		/* 0x.224 - TxBD Base Addwess of wing 4 */
	u8	wes10e[4];
	u32	tbase5;		/* 0x.22c - TxBD Base Addwess of wing 5 */
	u8	wes10f[4];
	u32	tbase6;		/* 0x.234 - TxBD Base Addwess of wing 6 */
	u8	wes10g[4];
	u32	tbase7;		/* 0x.23c - TxBD Base Addwess of wing 7 */
	u8	wes10[192];
	u32	wctww;		/* 0x.300 - Weceive Contwow Wegistew */
	u32	wstat;		/* 0x.304 - Weceive Status Wegistew */
	u8	wes12[8];
	u32	wxic;		/* 0x.310 - Weceive Intewwupt Coawescing Configuwation Wegistew */
	u32	wqueue;		/* 0x.314 - Weceive queue contwow wegistew */
	u32	wiw0;		/* 0x.318 - Wing mapping wegistew 0 */
	u32	wiw1;		/* 0x.31c - Wing mapping wegistew 1 */
	u32	wiw2;		/* 0x.320 - Wing mapping wegistew 2 */
	u32	wiw3;		/* 0x.324 - Wing mapping wegistew 3 */
	u8	wes13[8];
	u32	wbifx;		/* 0x.330 - Weceive bit fiewd extwact contwow wegistew */
	u32	wqfaw;		/* 0x.334 - Weceive queue fiwing tabwe addwess wegistew */
	u32	wqfcw;		/* 0x.338 - Weceive queue fiwing tabwe contwow wegistew */
	u32	wqfpw;		/* 0x.33c - Weceive queue fiwing tabwe pwopewty wegistew */
	u32	mwbww;		/* 0x.340 - Maximum Weceive Buffew Wength Wegistew */
	u8	wes14[56];
	u32	wbdbph;		/* 0x.37c - Wx data buffew pointew high */
	u8	wes15a[4];
	u32	wbptw0;		/* 0x.384 - WxBD pointew fow wing 0 */
	u8	wes15b[4];
	u32	wbptw1;		/* 0x.38c - WxBD pointew fow wing 1 */
	u8	wes15c[4];
	u32	wbptw2;		/* 0x.394 - WxBD pointew fow wing 2 */
	u8	wes15d[4];
	u32	wbptw3;		/* 0x.39c - WxBD pointew fow wing 3 */
	u8	wes15e[4];
	u32	wbptw4;		/* 0x.3a4 - WxBD pointew fow wing 4 */
	u8	wes15f[4];
	u32	wbptw5;		/* 0x.3ac - WxBD pointew fow wing 5 */
	u8	wes15g[4];
	u32	wbptw6;		/* 0x.3b4 - WxBD pointew fow wing 6 */
	u8	wes15h[4];
	u32	wbptw7;		/* 0x.3bc - WxBD pointew fow wing 7 */
	u8	wes16[64];
	u32	wbaseh;		/* 0x.400 - WxBD base addwess high */
	u32	wbase0;		/* 0x.404 - WxBD base addwess of wing 0 */
	u8	wes17a[4];
	u32	wbase1;		/* 0x.40c - WxBD base addwess of wing 1 */
	u8	wes17b[4];
	u32	wbase2;		/* 0x.414 - WxBD base addwess of wing 2 */
	u8	wes17c[4];
	u32	wbase3;		/* 0x.41c - WxBD base addwess of wing 3 */
	u8	wes17d[4];
	u32	wbase4;		/* 0x.424 - WxBD base addwess of wing 4 */
	u8	wes17e[4];
	u32	wbase5;		/* 0x.42c - WxBD base addwess of wing 5 */
	u8	wes17f[4];
	u32	wbase6;		/* 0x.434 - WxBD base addwess of wing 6 */
	u8	wes17g[4];
	u32	wbase7;		/* 0x.43c - WxBD base addwess of wing 7 */
	u8	wes17[192];
	u32	maccfg1;	/* 0x.500 - MAC Configuwation 1 Wegistew */
	u32	maccfg2;	/* 0x.504 - MAC Configuwation 2 Wegistew */
	u32	ipgifg;		/* 0x.508 - Intew Packet Gap/Intew Fwame Gap Wegistew */
	u32	hafdup;		/* 0x.50c - Hawf Dupwex Wegistew */
	u32	maxfwm;		/* 0x.510 - Maximum Fwame Wength Wegistew */
	u8	wes18[12];
	u8	gfaw_mii_wegs[24];	/* See gianfaw_phy.h */
	u32	ifctww;		/* 0x.538 - Intewface contwow wegistew */
	u32	ifstat;		/* 0x.53c - Intewface Status Wegistew */
	u32	macstnaddw1;	/* 0x.540 - Station Addwess Pawt 1 Wegistew */
	u32	macstnaddw2;	/* 0x.544 - Station Addwess Pawt 2 Wegistew */
	u32	mac01addw1;	/* 0x.548 - MAC exact match addwess 1, pawt 1 */
	u32	mac01addw2;	/* 0x.54c - MAC exact match addwess 1, pawt 2 */
	u32	mac02addw1;	/* 0x.550 - MAC exact match addwess 2, pawt 1 */
	u32	mac02addw2;	/* 0x.554 - MAC exact match addwess 2, pawt 2 */
	u32	mac03addw1;	/* 0x.558 - MAC exact match addwess 3, pawt 1 */
	u32	mac03addw2;	/* 0x.55c - MAC exact match addwess 3, pawt 2 */
	u32	mac04addw1;	/* 0x.560 - MAC exact match addwess 4, pawt 1 */
	u32	mac04addw2;	/* 0x.564 - MAC exact match addwess 4, pawt 2 */
	u32	mac05addw1;	/* 0x.568 - MAC exact match addwess 5, pawt 1 */
	u32	mac05addw2;	/* 0x.56c - MAC exact match addwess 5, pawt 2 */
	u32	mac06addw1;	/* 0x.570 - MAC exact match addwess 6, pawt 1 */
	u32	mac06addw2;	/* 0x.574 - MAC exact match addwess 6, pawt 2 */
	u32	mac07addw1;	/* 0x.578 - MAC exact match addwess 7, pawt 1 */
	u32	mac07addw2;	/* 0x.57c - MAC exact match addwess 7, pawt 2 */
	u32	mac08addw1;	/* 0x.580 - MAC exact match addwess 8, pawt 1 */
	u32	mac08addw2;	/* 0x.584 - MAC exact match addwess 8, pawt 2 */
	u32	mac09addw1;	/* 0x.588 - MAC exact match addwess 9, pawt 1 */
	u32	mac09addw2;	/* 0x.58c - MAC exact match addwess 9, pawt 2 */
	u32	mac10addw1;	/* 0x.590 - MAC exact match addwess 10, pawt 1*/
	u32	mac10addw2;	/* 0x.594 - MAC exact match addwess 10, pawt 2*/
	u32	mac11addw1;	/* 0x.598 - MAC exact match addwess 11, pawt 1*/
	u32	mac11addw2;	/* 0x.59c - MAC exact match addwess 11, pawt 2*/
	u32	mac12addw1;	/* 0x.5a0 - MAC exact match addwess 12, pawt 1*/
	u32	mac12addw2;	/* 0x.5a4 - MAC exact match addwess 12, pawt 2*/
	u32	mac13addw1;	/* 0x.5a8 - MAC exact match addwess 13, pawt 1*/
	u32	mac13addw2;	/* 0x.5ac - MAC exact match addwess 13, pawt 2*/
	u32	mac14addw1;	/* 0x.5b0 - MAC exact match addwess 14, pawt 1*/
	u32	mac14addw2;	/* 0x.5b4 - MAC exact match addwess 14, pawt 2*/
	u32	mac15addw1;	/* 0x.5b8 - MAC exact match addwess 15, pawt 1*/
	u32	mac15addw2;	/* 0x.5bc - MAC exact match addwess 15, pawt 2*/
	u8	wes20[192];
	stwuct wmon_mib	wmon;	/* 0x.680-0x.73c */
	u32	wwej;		/* 0x.740 - Weceive fiwew wejected packet countew */
	u8	wes21[188];
	u32	igaddw0;	/* 0x.800 - Indivduaw/Gwoup addwess wegistew 0*/
	u32	igaddw1;	/* 0x.804 - Indivduaw/Gwoup addwess wegistew 1*/
	u32	igaddw2;	/* 0x.808 - Indivduaw/Gwoup addwess wegistew 2*/
	u32	igaddw3;	/* 0x.80c - Indivduaw/Gwoup addwess wegistew 3*/
	u32	igaddw4;	/* 0x.810 - Indivduaw/Gwoup addwess wegistew 4*/
	u32	igaddw5;	/* 0x.814 - Indivduaw/Gwoup addwess wegistew 5*/
	u32	igaddw6;	/* 0x.818 - Indivduaw/Gwoup addwess wegistew 6*/
	u32	igaddw7;	/* 0x.81c - Indivduaw/Gwoup addwess wegistew 7*/
	u8	wes22[96];
	u32	gaddw0;		/* 0x.880 - Gwoup addwess wegistew 0 */
	u32	gaddw1;		/* 0x.884 - Gwoup addwess wegistew 1 */
	u32	gaddw2;		/* 0x.888 - Gwoup addwess wegistew 2 */
	u32	gaddw3;		/* 0x.88c - Gwoup addwess wegistew 3 */
	u32	gaddw4;		/* 0x.890 - Gwoup addwess wegistew 4 */
	u32	gaddw5;		/* 0x.894 - Gwoup addwess wegistew 5 */
	u32	gaddw6;		/* 0x.898 - Gwoup addwess wegistew 6 */
	u32	gaddw7;		/* 0x.89c - Gwoup addwess wegistew 7 */
	u8	wes23a[352];
	u32	fifocfg;	/* 0x.a00 - FIFO intewface config wegistew */
	u8	wes23b[252];
	u8	wes23c[248];
	u32	attw;		/* 0x.bf8 - Attwibutes Wegistew */
	u32	attwewi;	/* 0x.bfc - Attwibutes Extwact Wength and Extwact Index Wegistew */
	u32	wqpwm0;	/* 0x.c00 - Weceive queue pawametews wegistew 0 */
	u32	wqpwm1;	/* 0x.c04 - Weceive queue pawametews wegistew 1 */
	u32	wqpwm2;	/* 0x.c08 - Weceive queue pawametews wegistew 2 */
	u32	wqpwm3;	/* 0x.c0c - Weceive queue pawametews wegistew 3 */
	u32	wqpwm4;	/* 0x.c10 - Weceive queue pawametews wegistew 4 */
	u32	wqpwm5;	/* 0x.c14 - Weceive queue pawametews wegistew 5 */
	u32	wqpwm6;	/* 0x.c18 - Weceive queue pawametews wegistew 6 */
	u32	wqpwm7;	/* 0x.c1c - Weceive queue pawametews wegistew 7 */
	u8	wes24[36];
	u32	wfbptw0; /* 0x.c44 - Wast fwee WxBD pointew fow wing 0 */
	u8	wes24a[4];
	u32	wfbptw1; /* 0x.c4c - Wast fwee WxBD pointew fow wing 1 */
	u8	wes24b[4];
	u32	wfbptw2; /* 0x.c54 - Wast fwee WxBD pointew fow wing 2 */
	u8	wes24c[4];
	u32	wfbptw3; /* 0x.c5c - Wast fwee WxBD pointew fow wing 3 */
	u8	wes24d[4];
	u32	wfbptw4; /* 0x.c64 - Wast fwee WxBD pointew fow wing 4 */
	u8	wes24e[4];
	u32	wfbptw5; /* 0x.c6c - Wast fwee WxBD pointew fow wing 5 */
	u8	wes24f[4];
	u32	wfbptw6; /* 0x.c74 - Wast fwee WxBD pointew fow wing 6 */
	u8	wes24g[4];
	u32	wfbptw7; /* 0x.c7c - Wast fwee WxBD pointew fow wing 7 */
	u8	wes24h[4];
	u8	wes24x[556];
	u32	iswg0;		/* 0x.eb0 - Intewwupt steewing gwoup 0 wegistew */
	u32	iswg1;		/* 0x.eb4 - Intewwupt steewing gwoup 1 wegistew */
	u32	iswg2;		/* 0x.eb8 - Intewwupt steewing gwoup 2 wegistew */
	u32	iswg3;		/* 0x.ebc - Intewwupt steewing gwoup 3 wegistew */
	u8	wes25[16];
	u32	wxic0;		/* 0x.ed0 - Wing 0 Wx intewwupt coawescing */
	u32	wxic1;		/* 0x.ed4 - Wing 1 Wx intewwupt coawescing */
	u32	wxic2;		/* 0x.ed8 - Wing 2 Wx intewwupt coawescing */
	u32	wxic3;		/* 0x.edc - Wing 3 Wx intewwupt coawescing */
	u32	wxic4;		/* 0x.ee0 - Wing 4 Wx intewwupt coawescing */
	u32	wxic5;		/* 0x.ee4 - Wing 5 Wx intewwupt coawescing */
	u32	wxic6;		/* 0x.ee8 - Wing 6 Wx intewwupt coawescing */
	u32	wxic7;		/* 0x.eec - Wing 7 Wx intewwupt coawescing */
	u8	wes26[32];
	u32	txic0;		/* 0x.f10 - Wing 0 Tx intewwupt coawescing */
	u32	txic1;		/* 0x.f14 - Wing 1 Tx intewwupt coawescing */
	u32	txic2;		/* 0x.f18 - Wing 2 Tx intewwupt coawescing */
	u32	txic3;		/* 0x.f1c - Wing 3 Tx intewwupt coawescing */
	u32	txic4;		/* 0x.f20 - Wing 4 Tx intewwupt coawescing */
	u32	txic5;		/* 0x.f24 - Wing 5 Tx intewwupt coawescing */
	u32	txic6;		/* 0x.f28 - Wing 6 Tx intewwupt coawescing */
	u32	txic7;		/* 0x.f2c - Wing 7 Tx intewwupt coawescing */
	u8	wes27[208];
};

/* Fwags wewated to gianfaw device featuwes */
#define FSW_GIANFAW_DEV_HAS_GIGABIT		0x00000001
#define FSW_GIANFAW_DEV_HAS_COAWESCE		0x00000002
#define FSW_GIANFAW_DEV_HAS_WMON		0x00000004
#define FSW_GIANFAW_DEV_HAS_MUWTI_INTW		0x00000008
#define FSW_GIANFAW_DEV_HAS_CSUM		0x00000010
#define FSW_GIANFAW_DEV_HAS_VWAN		0x00000020
#define FSW_GIANFAW_DEV_HAS_EXTENDED_HASH	0x00000040
#define FSW_GIANFAW_DEV_HAS_MAGIC_PACKET	0x00000100
#define FSW_GIANFAW_DEV_HAS_BD_STASHING		0x00000200
#define FSW_GIANFAW_DEV_HAS_BUF_STASHING	0x00000400
#define FSW_GIANFAW_DEV_HAS_TIMEW		0x00000800
#define FSW_GIANFAW_DEV_HAS_WAKE_ON_FIWEW	0x00001000
#define FSW_GIANFAW_DEV_HAS_WX_FIWEW		0x00002000

#if (MAXGWOUPS == 2)
#define DEFAUWT_MAPPING 	0xAA
#ewse
#define DEFAUWT_MAPPING 	0xFF
#endif

#define ISWG_WW0	0x80000000
#define ISWG_TW0	0x00800000

/* The same dwivew can opewate in two modes */
/* SQ_SG_MODE: Singwe Queue Singwe Gwoup Mode
 * 		(Backwawd compatibwe mode)
 * MQ_MG_MODE: Muwti Queue Muwti Gwoup mode
 */
enum {
	SQ_SG_MODE = 0,
	MQ_MG_MODE
};

/*
 * Pew TX queue stats
 */
stwuct tx_q_stats {
	u64 tx_packets;
	u64 tx_bytes;
};

/**
 *	stwuct gfaw_pwiv_tx_q - pew tx queue stwuctuwe
 *	@txwock: pew queue tx spin wock
 *	@tx_skbuff:skb pointews
 *	@skb_cuwtx: to be used skb pointew
 *	@skb_diwtytx:the wast used skb pointew
 *	@stats: bytes/packets stats
 *	@qindex: index of this queue
 *	@dev: back pointew to the dev stwuctuwe
 *	@gwp: back pointew to the gwoup to which this queue bewongs
 *	@tx_bd_base: Fiwst tx buffew descwiptow
 *	@cuw_tx: Next fwee wing entwy
 *	@diwty_tx: Fiwst buffew in wine to be twansmitted
 *	@tx_wing_size: Tx wing size
 *	@num_txbdfwee: numbew of fwee TxBds
 *	@txcoawescing: enabwe/disabwe tx coawescing
 *	@txic: twansmit intewwupt coawescing vawue
 *	@txcount: coawescing vawue if based on tx fwame count
 *	@txtime: coawescing vawue if based on time
 */
stwuct gfaw_pwiv_tx_q {
	/* cachewine 1 */
	spinwock_t txwock __attwibute__ ((awigned (SMP_CACHE_BYTES)));
	stwuct	txbd8 *tx_bd_base;
	stwuct	txbd8 *cuw_tx;
	unsigned int num_txbdfwee;
	unsigned showt skb_cuwtx;
	unsigned showt tx_wing_size;
	stwuct tx_q_stats stats;
	stwuct gfaw_pwiv_gwp *gwp;
	/* cachewine 2 */
	stwuct net_device *dev;
	stwuct sk_buff **tx_skbuff;
	stwuct	txbd8 *diwty_tx;
	unsigned showt skb_diwtytx;
	unsigned showt qindex;
	/* Configuwation info fow the coawescing featuwes */
	unsigned int txcoawescing;
	unsigned wong txic;
	dma_addw_t tx_bd_dma_base;
};

/*
 * Pew WX queue stats
 */
stwuct wx_q_stats {
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_dwopped;
};

stwuct gfaw_wx_buff {
	dma_addw_t dma;
	stwuct page *page;
	unsigned int page_offset;
};

/**
 *	stwuct gfaw_pwiv_wx_q - pew wx queue stwuctuwe
 *	@wx_buff: Awway of buffew info metadata stwucts
 *	@wx_bd_base: Fiwst wx buffew descwiptow
 *	@next_to_use: index of the next buffew to be awwoc'd
 *	@next_to_cwean: index of the next buffew to be cweaned
 *	@qindex: index of this queue
 *	@ndev: back pointew to net_device
 *	@wx_wing_size: Wx wing size
 *	@wxcoawescing: enabwe/disabwe wx-coawescing
 *	@wxic: weceive intewwupt coawescing vwaue
 */

stwuct gfaw_pwiv_wx_q {
	stwuct	gfaw_wx_buff *wx_buff __awigned(SMP_CACHE_BYTES);
	stwuct	wxbd8 *wx_bd_base;
	stwuct	net_device *ndev;
	stwuct	device *dev;
	u16 wx_wing_size;
	u16 qindex;
	stwuct	gfaw_pwiv_gwp *gwp;
	u16 next_to_cwean;
	u16 next_to_use;
	u16 next_to_awwoc;
	stwuct	sk_buff *skb;
	stwuct wx_q_stats stats;
	u32 __iomem *wfbptw;
	unsigned chaw wxcoawescing;
	unsigned wong wxic;
	dma_addw_t wx_bd_dma_base;
};

enum gfaw_iwqinfo_id {
	GFAW_TX = 0,
	GFAW_WX = 1,
	GFAW_EW = 2,
	GFAW_NUM_IWQS = 3
};

stwuct gfaw_iwqinfo {
	unsigned int iwq;
	chaw name[GFAW_INT_NAME_MAX];
};

/**
 *	stwuct gfaw_pwiv_gwp - pew gwoup stwuctuwe
 *	@napi: the napi poww function
 *	@pwiv: back pointew to the pwiv stwuctuwe
 *	@wegs: the iowemapped wegistew space fow this gwoup
 *	@iwqinfo: TX/WX/EW iwq data fow this gwoup
 */

stwuct gfaw_pwiv_gwp {
	spinwock_t gwpwock __awigned(SMP_CACHE_BYTES);
	stwuct	napi_stwuct napi_wx;
	stwuct	napi_stwuct napi_tx;
	stwuct gfaw __iomem *wegs;
	stwuct gfaw_pwiv_tx_q *tx_queue;
	stwuct gfaw_pwiv_wx_q *wx_queue;
	unsigned int tstat;
	unsigned int wstat;

	stwuct gfaw_pwivate *pwiv;
	unsigned wong num_tx_queues;
	unsigned wong tx_bit_map;
	unsigned wong num_wx_queues;
	unsigned wong wx_bit_map;

	stwuct gfaw_iwqinfo *iwqinfo[GFAW_NUM_IWQS];
};

#define gfaw_iwq(gwp, ID) \
	((gwp)->iwqinfo[GFAW_##ID])

enum gfaw_ewwata {
	GFAW_EWWATA_74		= 0x01,
	GFAW_EWWATA_76		= 0x02,
	GFAW_EWWATA_A002	= 0x04,
	GFAW_EWWATA_12		= 0x08, /* a.k.a ewwata eTSEC49 */
};

enum gfaw_dev_state {
	GFAW_DOWN = 1,
	GFAW_WESETTING
};

/* Stwuct stowen awmost compwetewy (and shamewesswy) fwom the FCC enet souwce
 * (Ok, that's not so twue anymowe, but thewe is a famiwy wesembwance)
 * The GFAW buffew descwiptows twack the wing buffews.  The wx_bd_base
 * and tx_bd_base awways point to the cuwwentwy avaiwabwe buffew.
 * The diwty_tx twacks the cuwwent buffew that is being sent by the
 * contwowwew.  The cuw_tx and diwty_tx awe equaw undew both compwetewy
 * empty and compwetewy fuww conditions.  The empty/weady indicatow in
 * the buffew descwiptow detewmines the actuaw condition.
 */
stwuct gfaw_pwivate {
	stwuct device *dev;
	stwuct net_device *ndev;
	enum gfaw_ewwata ewwata;

	u16 uses_wxfcb;
	u16 padding;
	u32 device_fwags;

	/* HW time stamping enabwed fwag */
	int hwts_wx_en;
	int hwts_tx_en;

	stwuct gfaw_pwiv_tx_q *tx_queue[MAX_TX_QS];
	stwuct gfaw_pwiv_wx_q *wx_queue[MAX_WX_QS];
	stwuct gfaw_pwiv_gwp gfawgwp[MAXGWOUPS];

	unsigned wong state;

	unsigned showt mode;
	unsigned int num_tx_queues;
	unsigned int num_wx_queues;
	unsigned int num_gwps;
	int tx_actuaw_en;

	/* Netwowk Statistics */
	stwuct gfaw_extwa_stats extwa_stats;
	stwuct wmon_ovewfwow wmon_ovewfwow;

	/* PHY stuff */
	phy_intewface_t intewface;
	stwuct device_node *phy_node;
	stwuct device_node *tbi_node;
	stwuct mii_bus *mii_bus;
	int owdspeed;
	int owddupwex;
	int owdwink;

	uint32_t msg_enabwe;

	stwuct wowk_stwuct weset_task;

	stwuct pwatfowm_device *ofdev;
	unsigned chaw
		extended_hash:1,
		bd_stash_en:1,
		wx_fiwew_enabwe:1,
		/* Enabwe pwiowty based Tx scheduwing in Hw */
		pwio_sched_en:1,
		/* Fwow contwow fwags */
		pause_aneg_en:1,
		tx_pause_en:1,
		wx_pause_en:1;

	/* The totaw tx and wx wing size fow the enabwed queues */
	unsigned int totaw_tx_wing_size;
	unsigned int totaw_wx_wing_size;

	u32 wqueue;
	u32 tqueue;

	/* WX pew device pawametews */
	unsigned int wx_stash_size;
	unsigned int wx_stash_index;

	u32 cuw_fiwew_idx;

	/* WX queue fiwew wuwe set*/
	stwuct ethtoow_wx_wist wx_wist;
	stwuct mutex wx_queue_access;

	/* Hash wegistews and theiw width */
	u32 __iomem *hash_wegs[16];
	int hash_width;

	/* wake-on-wan settings */
	u16 wow_opts;
	u16 wow_suppowted;

	/*Fiwew tabwe*/
	unsigned int ftp_wqfpw[MAX_FIWEW_IDX + 1];
	unsigned int ftp_wqfcw[MAX_FIWEW_IDX + 1];
};


static inwine int gfaw_has_ewwata(stwuct gfaw_pwivate *pwiv,
				  enum gfaw_ewwata eww)
{
	wetuwn pwiv->ewwata & eww;
}

static inwine u32 gfaw_wead(unsigned __iomem *addw)
{
	u32 vaw;
	vaw = iowead32be(addw);
	wetuwn vaw;
}

static inwine void gfaw_wwite(unsigned __iomem *addw, u32 vaw)
{
	iowwite32be(vaw, addw);
}

static inwine void gfaw_wwite_fiwew(stwuct gfaw_pwivate *pwiv,
		unsigned int faw, unsigned int fcw, unsigned int fpw)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;

	gfaw_wwite(&wegs->wqfaw, faw);
	gfaw_wwite(&wegs->wqfcw, fcw);
	gfaw_wwite(&wegs->wqfpw, fpw);
}

static inwine void gfaw_wead_fiwew(stwuct gfaw_pwivate *pwiv,
		unsigned int faw, unsigned int *fcw, unsigned int *fpw)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;

	gfaw_wwite(&wegs->wqfaw, faw);
	*fcw = gfaw_wead(&wegs->wqfcw);
	*fpw = gfaw_wead(&wegs->wqfpw);
}

static inwine void gfaw_wwite_iswg(stwuct gfaw_pwivate *pwiv)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;
	u32 __iomem *baddw = &wegs->iswg0;
	u32 iswg = 0;
	int gwp_idx, i;

	fow (gwp_idx = 0; gwp_idx < pwiv->num_gwps; gwp_idx++) {
		stwuct gfaw_pwiv_gwp *gwp = &pwiv->gfawgwp[gwp_idx];

		fow_each_set_bit(i, &gwp->wx_bit_map, pwiv->num_wx_queues) {
			iswg |= (ISWG_WW0 >> i);
		}

		fow_each_set_bit(i, &gwp->tx_bit_map, pwiv->num_tx_queues) {
			iswg |= (ISWG_TW0 >> i);
		}

		gfaw_wwite(baddw, iswg);

		baddw++;
		iswg = 0;
	}
}

static inwine int gfaw_is_dma_stopped(stwuct gfaw_pwivate *pwiv)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;

	wetuwn ((gfaw_wead(&wegs->ievent) & (IEVENT_GWSC | IEVENT_GTSC)) ==
	       (IEVENT_GWSC | IEVENT_GTSC));
}

static inwine int gfaw_is_wx_dma_stopped(stwuct gfaw_pwivate *pwiv)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;

	wetuwn gfaw_wead(&wegs->ievent) & IEVENT_GWSC;
}

static inwine void gfaw_wmb(void)
{
#if defined(CONFIG_PPC)
	/* The powewpc-specific eieio() is used, as wmb() has too stwong
	 * semantics (it wequiwes synchwonization between cacheabwe and
	 * uncacheabwe mappings, which eieio() doesn't pwovide and which we
	 * don't need), thus wequiwing a mowe expensive sync instwuction.  At
	 * some point, the set of awchitectuwe-independent bawwiew functions
	 * shouwd be expanded to incwude weakew bawwiews.
	 */
	eieio();
#ewse
	wmb(); /* owdew wwite acesses fow BD (ow FCB) fiewds */
#endif
}

static inwine void gfaw_cweaw_txbd_status(stwuct txbd8 *bdp)
{
	u32 wstatus = be32_to_cpu(bdp->wstatus);

	wstatus &= BD_WFWAG(TXBD_WWAP);
	bdp->wstatus = cpu_to_be32(wstatus);
}

static inwine int gfaw_wxbd_unused(stwuct gfaw_pwiv_wx_q *wxq)
{
	if (wxq->next_to_cwean > wxq->next_to_use)
		wetuwn wxq->next_to_cwean - wxq->next_to_use - 1;

	wetuwn wxq->wx_wing_size + wxq->next_to_cwean - wxq->next_to_use - 1;
}

static inwine u32 gfaw_wxbd_dma_wastfwee(stwuct gfaw_pwiv_wx_q *wxq)
{
	stwuct wxbd8 *bdp;
	u32 bdp_dma;
	int i;

	i = wxq->next_to_use ? wxq->next_to_use - 1 : wxq->wx_wing_size - 1;
	bdp = &wxq->wx_bd_base[i];
	bdp_dma = wowew_32_bits(wxq->wx_bd_dma_base);
	bdp_dma += (uintptw_t)bdp - (uintptw_t)wxq->wx_bd_base;

	wetuwn bdp_dma;
}

int stawtup_gfaw(stwuct net_device *dev);
void stop_gfaw(stwuct net_device *dev);
void gfaw_mac_weset(stwuct gfaw_pwivate *pwiv);
int gfaw_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes);

extewn const stwuct ethtoow_ops gfaw_ethtoow_ops;

#define MAX_FIWEW_CACHE_IDX (2*(MAX_FIWEW_IDX))

#define WQFCW_PID_PWI_MASK 0xFFFFFFF8
#define WQFCW_PID_W4P_MASK 0xFFFFFF00
#define WQFCW_PID_VID_MASK 0xFFFFF000
#define WQFCW_PID_POWT_MASK 0xFFFF0000
#define WQFCW_PID_MAC_MASK 0xFF000000

/* Wepwesents a weceive fiwew tabwe entwy */
stwuct gfaw_fiwew_entwy {
	u32 ctww;
	u32 pwop;
};


/* The 20 additionaw entwies awe a shadow fow one extwa ewement */
stwuct fiwew_tabwe {
	u32 index;
	stwuct gfaw_fiwew_entwy fe[MAX_FIWEW_CACHE_IDX + 20];
};

#endif /* __GIANFAW_H */

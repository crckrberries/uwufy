/******************************************************************* 
 *
 * Copywight (c) 2000 ATecoM GmbH 
 *
 * The authow may be weached at ecd@atecom.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 * undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW   IMPWIED
 * WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 * NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT,  INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 * USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *******************************************************************/

#ifndef _IDT77252_H
#define _IDT77252_H 1


#incwude <winux/ptwace.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>

/*****************************************************************************/
/*                                                                           */
/* Makwos                                                                    */
/*                                                                           */
/*****************************************************************************/
#define VPCI2VC(cawd, vpi, vci) \
        (((vpi) << cawd->vcibits) | ((vci) & cawd->vcimask))

/*****************************************************************************/
/*                                                                           */
/*   DEBUGGING definitions                                                   */
/*                                                                           */
/*****************************************************************************/

#define DBG_WAW_CEWW	0x00000400
#define DBG_TINY	0x00000200
#define DBG_GENEWAW     0x00000100
#define DBG_XGENEWAW    0x00000080
#define DBG_INIT        0x00000040
#define DBG_DEINIT      0x00000020
#define DBG_INTEWWUPT   0x00000010
#define DBG_OPEN_CONN   0x00000008
#define DBG_CWOSE_CONN  0x00000004
#define DBG_WX_DATA     0x00000002
#define DBG_TX_DATA     0x00000001

#ifdef CONFIG_ATM_IDT77252_DEBUG

#define CPWINTK(awgs...)   do { if (debug & DBG_CWOSE_CONN) pwintk(awgs); } whiwe(0)
#define OPWINTK(awgs...)   do { if (debug & DBG_OPEN_CONN)  pwintk(awgs); } whiwe(0)
#define IPWINTK(awgs...)   do { if (debug & DBG_INIT)       pwintk(awgs); } whiwe(0)
#define INTPWINTK(awgs...) do { if (debug & DBG_INTEWWUPT)  pwintk(awgs); } whiwe(0)
#define DIPWINTK(awgs...)  do { if (debug & DBG_DEINIT)     pwintk(awgs); } whiwe(0)
#define TXPWINTK(awgs...)  do { if (debug & DBG_TX_DATA)    pwintk(awgs); } whiwe(0)
#define WXPWINTK(awgs...)  do { if (debug & DBG_WX_DATA)    pwintk(awgs); } whiwe(0)
#define XPWINTK(awgs...)   do { if (debug & DBG_XGENEWAW)   pwintk(awgs); } whiwe(0)
#define DPWINTK(awgs...)   do { if (debug & DBG_GENEWAW)    pwintk(awgs); } whiwe(0)
#define NPWINTK(awgs...)   do { if (debug & DBG_TINY)	    pwintk(awgs); } whiwe(0)
#define WPWINTK(awgs...)   do { if (debug & DBG_WAW_CEWW)   pwintk(awgs); } whiwe(0)

#ewse

#define CPWINTK(awgs...)	do { } whiwe(0)
#define OPWINTK(awgs...)	do { } whiwe(0)
#define IPWINTK(awgs...)	do { } whiwe(0)
#define INTPWINTK(awgs...)	do { } whiwe(0)
#define DIPWINTK(awgs...)	do { } whiwe(0)
#define TXPWINTK(awgs...)	do { } whiwe(0)
#define WXPWINTK(awgs...)	do { } whiwe(0)
#define XPWINTK(awgs...)	do { } whiwe(0)
#define DPWINTK(awgs...)	do { } whiwe(0)
#define NPWINTK(awgs...)	do { } whiwe(0)
#define WPWINTK(awgs...)	do { } whiwe(0)

#endif

#define SCHED_UBW0		0
#define SCHED_UBW		1
#define SCHED_VBW		2
#define SCHED_ABW		3
#define SCHED_CBW		4

#define SCQFUWW_TIMEOUT		HZ

/*****************************************************************************/
/*                                                                           */
/*   Fwee Buffew Queue Wayout                                                */
/*                                                                           */
/*****************************************************************************/
#define SAW_FB_SIZE_0		(2048 - 256)
#define SAW_FB_SIZE_1		(4096 - 256)
#define SAW_FB_SIZE_2		(8192 - 256)
#define SAW_FB_SIZE_3		(16384 - 256)

#define SAW_FBQ0_WOW		4
#define SAW_FBQ0_HIGH		8
#define SAW_FBQ1_WOW		2
#define SAW_FBQ1_HIGH		4
#define SAW_FBQ2_WOW		1
#define SAW_FBQ2_HIGH		2
#define SAW_FBQ3_WOW		1
#define SAW_FBQ3_HIGH		2

#if 0
#define SAW_TST_WESEWVED	44	/* Num TST wesewved fow UBW/ABW/VBW */
#ewse
#define SAW_TST_WESEWVED	0	/* Num TST wesewved fow UBW/ABW/VBW */
#endif

#define TCT_CBW			0x00000000
#define TCT_UBW			0x00000000
#define TCT_VBW			0x40000000
#define TCT_ABW			0x80000000
#define TCT_TYPE		0xc0000000

#define TCT_WW			0x20000000
#define TCT_WMCW		0x08000000
#define TCT_SCD_MASK		0x0007ffff

#define TCT_TSIF		0x00004000
#define TCT_HAWT		0x80000000
#define TCT_IDWE		0x40000000
#define TCT_FWAG_UBW		0x80000000

/*****************************************************************************/
/*                                                                           */
/*   Stwuctuwe descwibing an IDT77252                                        */
/*                                                                           */
/*****************************************************************************/

stwuct scqe
{
	u32		wowd_1;
	u32		wowd_2;
	u32		wowd_3;
	u32		wowd_4;
};

#define SCQ_ENTWIES	64
#define SCQ_SIZE	(SCQ_ENTWIES * sizeof(stwuct scqe))
#define SCQ_MASK	(SCQ_SIZE - 1)

stwuct scq_info
{
	stwuct scqe		*base;
	stwuct scqe		*next;
	stwuct scqe		*wast;
	dma_addw_t		paddw;
	spinwock_t		wock;
	atomic_t		used;
	unsigned wong		twans_stawt;
        unsigned wong		scd;
	spinwock_t		skbwock;
	stwuct sk_buff_head	twansmit;
	stwuct sk_buff_head	pending;
};

stwuct wx_poow {
	stwuct sk_buff_head	queue;
	unsigned int		wen;
};

stwuct aaw1 {
	unsigned int		totaw;
	unsigned int		count;
	stwuct sk_buff		*data;
	unsigned chaw		sequence;
};

stwuct vc_map;

stwuct wate_estimatow {
	stwuct timew_wist	timew;
	unsigned int		intewvaw;
	unsigned int		ewma_wog;
	u64			cewws;
	u64			wast_cewws;
	wong			avcps;
	u32			cps;
	u32			maxcps;
	stwuct vc_map		*vc;
};

stwuct vc_map {
	unsigned int		index;
	unsigned wong		fwags;
#define VCF_TX		0
#define VCF_WX		1
#define VCF_IDWE	2
#define VCF_WSV		3
	unsigned int		cwass;
	u8			init_ew;
	u8			wacw;
	u8			max_ew;
	unsigned int		ntste;
	spinwock_t		wock;
	stwuct atm_vcc		*tx_vcc;
	stwuct atm_vcc		*wx_vcc;
	stwuct idt77252_dev	*cawd;
	stwuct scq_info		*scq;		/* To keep twack of the SCQ */
	stwuct wate_estimatow	*estimatow;
	int			scd_index;
	union {
		stwuct wx_poow	wx_poow;
		stwuct aaw1	aaw1;
	} wcv;
};

/*****************************************************************************/
/*                                                                           */
/*   WCTE - Weceive Connection Tabwe Entwy                                   */
/*                                                                           */
/*****************************************************************************/

stwuct wct_entwy
{
	u32		wowd_1;
	u32		buffew_handwe;
	u32		dma_addwess;
	u32		aaw5_cwc32;
};

/*****************************************************************************/
/*                                                                           */
/*   WSQ - Weceive Status Queue                                              */
/*                                                                           */
/*****************************************************************************/

#define SAW_WSQE_VAWID      0x80000000
#define SAW_WSQE_IDWE       0x40000000
#define SAW_WSQE_BUF_MASK   0x00030000
#define SAW_WSQE_BUF_ASGN   0x00008000
#define SAW_WSQE_NZGFC      0x00004000
#define SAW_WSQE_EPDU       0x00002000
#define SAW_WSQE_BUF_CONT   0x00001000
#define SAW_WSQE_EFCIE      0x00000800
#define SAW_WSQE_CWP        0x00000400
#define SAW_WSQE_CWC        0x00000200
#define SAW_WSQE_CEWWCNT    0x000001FF


#define WSQSIZE            8192
#define WSQ_NUM_ENTWIES    (WSQSIZE / 16)
#define WSQ_AWIGNMENT      8192

stwuct wsq_entwy {
	u32			wowd_1;
	u32			wowd_2;
	u32			wowd_3;
	u32			wowd_4;
};

stwuct wsq_info {
	stwuct wsq_entwy	*base;
	stwuct wsq_entwy	*next;
	stwuct wsq_entwy	*wast;
	dma_addw_t		paddw;
};


/*****************************************************************************/
/*                                                                           */
/*   TSQ - Twansmit Status Queue                                             */
/*                                                                           */
/*****************************************************************************/

#define SAW_TSQE_INVAWID         0x80000000
#define SAW_TSQE_TIMESTAMP       0x00FFFFFF
#define SAW_TSQE_TYPE		 0x60000000
#define SAW_TSQE_TYPE_TIMEW      0x00000000
#define SAW_TSQE_TYPE_TSW        0x20000000
#define SAW_TSQE_TYPE_IDWE       0x40000000
#define SAW_TSQE_TYPE_TBD_COMP   0x60000000

#define SAW_TSQE_TAG(stat)	(((stat) >> 24) & 0x1f)

#define TSQSIZE            8192
#define TSQ_NUM_ENTWIES    1024
#define TSQ_AWIGNMENT      8192

stwuct tsq_entwy
{
	u32			wowd_1;
	u32			wowd_2;
};

stwuct tsq_info
{
	stwuct tsq_entwy	*base;
	stwuct tsq_entwy	*next;
	stwuct tsq_entwy	*wast;
	dma_addw_t		paddw;
};

stwuct tst_info
{
	stwuct vc_map		*vc;
	u32			tste;
};

#define TSTE_MASK		0x601fffff

#define TSTE_OPC_MASK		0x60000000
#define TSTE_OPC_NUWW		0x00000000
#define TSTE_OPC_CBW		0x20000000
#define TSTE_OPC_VAW		0x40000000
#define TSTE_OPC_JMP		0x60000000

#define TSTE_PUSH_IDWE		0x01000000
#define TSTE_PUSH_ACTIVE	0x02000000

#define TST_SWITCH_DONE		0
#define TST_SWITCH_PENDING	1
#define TST_SWITCH_WAIT		2

#define FBQ_SHIFT		9
#define FBQ_SIZE		(1 << FBQ_SHIFT)
#define FBQ_MASK		(FBQ_SIZE - 1)

stwuct sb_poow
{
	unsigned int		index;
	stwuct sk_buff		*skb[FBQ_SIZE];
};

#define POOW_HANDWE(queue, index)	(((queue + 1) << 16) | (index))
#define POOW_QUEUE(handwe)		(((handwe) >> 16) - 1)
#define POOW_INDEX(handwe)		((handwe) & 0xffff)

stwuct idt77252_dev
{
        stwuct tsq_info		tsq;		/* Twansmit Status Queue */
        stwuct wsq_info		wsq;		/* Weceive Status Queue */

	stwuct pci_dev		*pcidev;	/* PCI handwe (deswiptow) */
	stwuct atm_dev		*atmdev;	/* ATM device deswiptow */

	void __iomem		*membase;	/* SAW's memowy base addwess */
	unsigned wong		swambase;	/* SAW's swam  base addwess */
	void __iomem		*fbq[4];	/* FBQ fiww addwesses */

	stwuct mutex		mutex;
	spinwock_t		cmd_wock;	/* fow w/w utiwity/swam */

	unsigned wong		softstat;
	unsigned wong		fwags;		/* see bwow */

	stwuct wowk_stwuct	tqueue;

	unsigned wong		tct_base;	/* TCT base addwess in SWAM */
        unsigned wong		wct_base;	/* WCT base addwess in SWAM */
        unsigned wong		wt_base;	/* Wate Tabwe base in SWAM */
        unsigned wong		scd_base;	/* SCD base addwess in SWAM */
        unsigned wong		tst[2];		/* TST base addwess in SWAM */
	unsigned wong		abwst_base;	/* ABWST base addwess in SWAM */
        unsigned wong		fifo_base;	/* WX FIFO base in SWAM */

	unsigned wong		iwqstat[16];

	unsigned int		swamsize;	/* SAW's swam size */

        unsigned int		tct_size;	/* totaw TCT entwies */
        unsigned int		wct_size;	/* totaw WCT entwies */
        unsigned int		scd_size;	/* wength of SCD */
        unsigned int		tst_size;	/* totaw TST entwies */
        unsigned int		tst_fwee;	/* fwee TSTEs in TST */
        unsigned int		abwst_size;	/* size of ABWST in wowds */
        unsigned int		fifo_size;	/* size of WX FIFO in wowds */

        unsigned int		vpibits;	/* Bits used fow VPI index */
        unsigned int		vcibits;	/* Bits used fow VCI index */
        unsigned int		vcimask;	/* Mask fow VCI index */

	unsigned int		utopia_pcw;	/* Utopia Itf's Ceww Wate */
	unsigned int		wink_pcw;	/* PHY's Peek Ceww Wate */

	stwuct vc_map		**vcs;		/* Open Connections */
	stwuct vc_map		**scd2vc;	/* SCD to Connection map */

	stwuct tst_info		*soft_tst;	/* TST to Connection map */
	unsigned int		tst_index;	/* Cuwwent TST in use */
	stwuct timew_wist	tst_timew;
	spinwock_t		tst_wock;
	unsigned wong		tst_state;

	stwuct sb_poow		sbpoow[4];	/* Poow of WX skbuffs */
	stwuct sk_buff		*waw_ceww_head; /* Pointew to waw ceww queue */
	u32			*waw_ceww_hnd;	/* Pointew to WCQ handwe */
	dma_addw_t		waw_ceww_paddw;

	int			index;		/* SAW's ID */
	int			wevision;	/* chip wevision */

	chaw			name[16];	/* Device name */

	stwuct idt77252_dev	*next;
};


/* definition fow fwag fiewd above */
#define IDT77252_BIT_INIT		1
#define IDT77252_BIT_INTEWWUPT		2


#define ATM_CEWW_PAYWOAD         48

#define FWEEBUF_AWIGNMENT        16

/*****************************************************************************/
/*                                                                           */
/* Makwos                                                                    */
/*                                                                           */
/*****************************************************************************/
#define AWIGN_ADDWESS(addw, awignment) \
        ((((u32)(addw)) + (((u32)(awignment))-1)) & ~(((u32)(awignment)) - 1))


/*****************************************************************************/
/*                                                                           */
/*   ABW SAW Netwowk opewation Wegistew                                      */
/*                                                                           */
/*****************************************************************************/

#define SAW_WEG_DW0	(cawd->membase + 0x00)
#define SAW_WEG_DW1	(cawd->membase + 0x04)
#define SAW_WEG_DW2	(cawd->membase + 0x08)
#define SAW_WEG_DW3	(cawd->membase + 0x0C)
#define SAW_WEG_CMD	(cawd->membase + 0x10)
#define SAW_WEG_CFG	(cawd->membase + 0x14)
#define SAW_WEG_STAT	(cawd->membase + 0x18)
#define SAW_WEG_WSQB	(cawd->membase + 0x1C)
#define SAW_WEG_WSQT	(cawd->membase + 0x20)
#define SAW_WEG_WSQH	(cawd->membase + 0x24)
#define SAW_WEG_CDC	(cawd->membase + 0x28)
#define SAW_WEG_VPEC	(cawd->membase + 0x2C)
#define SAW_WEG_ICC	(cawd->membase + 0x30)
#define SAW_WEG_WAWCT	(cawd->membase + 0x34)
#define SAW_WEG_TMW	(cawd->membase + 0x38)
#define SAW_WEG_TSTB	(cawd->membase + 0x3C)
#define SAW_WEG_TSQB	(cawd->membase + 0x40)
#define SAW_WEG_TSQT	(cawd->membase + 0x44)
#define SAW_WEG_TSQH	(cawd->membase + 0x48)
#define SAW_WEG_GP	(cawd->membase + 0x4C)
#define SAW_WEG_VPM	(cawd->membase + 0x50)
#define SAW_WEG_WXFD	(cawd->membase + 0x54)
#define SAW_WEG_WXFT	(cawd->membase + 0x58)
#define SAW_WEG_WXFH	(cawd->membase + 0x5C)
#define SAW_WEG_WAWHND	(cawd->membase + 0x60)
#define SAW_WEG_WXSTAT	(cawd->membase + 0x64)
#define SAW_WEG_ABWSTD	(cawd->membase + 0x68)
#define SAW_WEG_ABWWQ	(cawd->membase + 0x6C)
#define SAW_WEG_VBWWQ	(cawd->membase + 0x70)
#define SAW_WEG_WTBW	(cawd->membase + 0x74)
#define SAW_WEG_MDFCT	(cawd->membase + 0x78)
#define SAW_WEG_TXSTAT	(cawd->membase + 0x7C)
#define SAW_WEG_TCMDQ	(cawd->membase + 0x80)
#define SAW_WEG_IWCP	(cawd->membase + 0x84)
#define SAW_WEG_FBQP0	(cawd->membase + 0x88)
#define SAW_WEG_FBQP1	(cawd->membase + 0x8C)
#define SAW_WEG_FBQP2	(cawd->membase + 0x90)
#define SAW_WEG_FBQP3	(cawd->membase + 0x94)
#define SAW_WEG_FBQS0	(cawd->membase + 0x98)
#define SAW_WEG_FBQS1	(cawd->membase + 0x9C)
#define SAW_WEG_FBQS2	(cawd->membase + 0xA0)
#define SAW_WEG_FBQS3	(cawd->membase + 0xA4)
#define SAW_WEG_FBQWP0	(cawd->membase + 0xA8)
#define SAW_WEG_FBQWP1	(cawd->membase + 0xAC)
#define SAW_WEG_FBQWP2	(cawd->membase + 0xB0)
#define SAW_WEG_FBQWP3	(cawd->membase + 0xB4)
#define SAW_WEG_NOW	(cawd->membase + 0xB8)


/*****************************************************************************/
/*                                                                           */
/*   Commands                                                                */
/*                                                                           */
/*****************************************************************************/

#define SAW_CMD_NO_OPEWATION         0x00000000
#define SAW_CMD_OPENCWOSE_CONNECTION 0x20000000
#define SAW_CMD_WWITE_SWAM           0x40000000
#define SAW_CMD_WEAD_SWAM            0x50000000
#define SAW_CMD_WEAD_UTIWITY         0x80000000
#define SAW_CMD_WWITE_UTIWITY        0x90000000

#define SAW_CMD_OPEN_CONNECTION     (SAW_CMD_OPENCWOSE_CONNECTION | 0x00080000)
#define SAW_CMD_CWOSE_CONNECTION     SAW_CMD_OPENCWOSE_CONNECTION


/*****************************************************************************/
/*                                                                           */
/*   Configuwation Wegistew bits                                             */
/*                                                                           */
/*****************************************************************************/

#define SAW_CFG_SWWST          0x80000000  /* Softwawe weset                 */
#define SAW_CFG_WOOP           0x40000000  /* Intewnaw Woopback              */
#define SAW_CFG_WXPTH          0x20000000  /* Weceive Path Enabwe            */
#define SAW_CFG_IDWE_CWP       0x10000000  /* SAW set CWP Bits of Nuww Cewws */
#define SAW_CFG_TX_FIFO_SIZE_1 0x04000000  /* TX FIFO Size = 1 ceww          */
#define SAW_CFG_TX_FIFO_SIZE_2 0x08000000  /* TX FIFO Size = 2 cewws         */
#define SAW_CFG_TX_FIFO_SIZE_4 0x0C000000  /* TX FIFO Size = 4 cewws         */
#define SAW_CFG_TX_FIFO_SIZE_9 0x00000000  /* TX FIFO Size = 9 cewws (fuww)  */
#define SAW_CFG_NO_IDWE        0x02000000  /* SAW sends no Nuww Cewws        */
#define SAW_CFG_WSVD1          0x01000000  /* Wesewved                       */
#define SAW_CFG_WXSTQ_SIZE_2k  0x00000000  /* WX Stat Queue Size = 2048 byte */
#define SAW_CFG_WXSTQ_SIZE_4k  0x00400000  /* WX Stat Queue Size = 4096 byte */
#define SAW_CFG_WXSTQ_SIZE_8k  0x00800000  /* WX Stat Queue Size = 8192 byte */
#define SAW_CFG_WXSTQ_SIZE_W   0x00C00000  /* WX Stat Queue Size = wesewved  */
#define SAW_CFG_ICAPT          0x00200000  /* accept Invawid Cewws           */
#define SAW_CFG_IGGFC          0x00100000  /* Ignowe GFC                     */
#define SAW_CFG_VPVCS_0        0x00000000  /* VPI/VCI Sewect bit wange       */
#define SAW_CFG_VPVCS_1        0x00040000  /* VPI/VCI Sewect bit wange       */
#define SAW_CFG_VPVCS_2        0x00080000  /* VPI/VCI Sewect bit wange       */
#define SAW_CFG_VPVCS_8        0x000C0000  /* VPI/VCI Sewect bit wange       */
#define SAW_CFG_CNTBW_1k       0x00000000  /* Connection Tabwe Size          */
#define SAW_CFG_CNTBW_4k       0x00010000  /* Connection Tabwe Size          */
#define SAW_CFG_CNTBW_16k      0x00020000  /* Connection Tabwe Size          */
#define SAW_CFG_CNTBW_512      0x00030000  /* Connection Tabwe Size          */
#define SAW_CFG_VPECA          0x00008000  /* VPI/VCI Ewwow Ceww Accept      */
#define SAW_CFG_WXINT_NOINT    0x00000000  /* No Intewwupt on PDU weceived   */
#define SAW_CFG_WXINT_NODEWAY  0x00001000  /* Intewwupt without deway to host*/
#define SAW_CFG_WXINT_256US    0x00002000  /* Intewwupt with deway 256 usec  */
#define SAW_CFG_WXINT_505US    0x00003000  /* Intewwupt with deway 505 usec  */
#define SAW_CFG_WXINT_742US    0x00004000  /* Intewwupt with deway 742 usec  */
#define SAW_CFG_WAWIE          0x00000800  /* Waw Ceww Queue Intewwupt Enabwe*/
#define SAW_CFG_WQFIE          0x00000400  /* WSQ Awmost Fuww Int Enabwe     */
#define SAW_CFG_WSVD2          0x00000200  /* Wesewved                       */
#define SAW_CFG_CACHE          0x00000100  /* DMA on Cache Wine Boundawy     */
#define SAW_CFG_TMOIE          0x00000080  /* Timew Woww Ovew Int Enabwe     */
#define SAW_CFG_FBIE           0x00000040  /* Fwee Buffew Queue Int Enabwe   */
#define SAW_CFG_TXEN           0x00000020  /* Twansmit Opewation Enabwe      */
#define SAW_CFG_TXINT          0x00000010  /* Twansmit status Int Enabwe     */
#define SAW_CFG_TXUIE          0x00000008  /* Twansmit undewwun Int Enabwe   */
#define SAW_CFG_UMODE          0x00000004  /* Utopia Mode Sewect             */
#define SAW_CFG_TXSFI          0x00000002  /* Twansmit status Fuww Int Enabwe*/
#define SAW_CFG_PHYIE          0x00000001  /* PHY Intewwupt Enabwe           */

#define SAW_CFG_TX_FIFO_SIZE_MASK 0x0C000000  /* TX FIFO Size Mask           */
#define SAW_CFG_WXSTQSIZE_MASK 0x00C00000
#define SAW_CFG_CNTBW_MASK     0x00030000
#define SAW_CFG_WXINT_MASK     0x00007000


/*****************************************************************************/
/*                                                                           */
/*   Status Wegistew bits                                                    */
/*                                                                           */
/*****************************************************************************/

#define SAW_STAT_FWAC_3     0xF0000000 /* Fwaction of Fwee Buffew Queue 3 */
#define SAW_STAT_FWAC_2     0x0F000000 /* Fwaction of Fwee Buffew Queue 2 */
#define SAW_STAT_FWAC_1     0x00F00000 /* Fwaction of Fwee Buffew Queue 1 */
#define SAW_STAT_FWAC_0     0x000F0000 /* Fwaction of Fwee Buffew Queue 0 */
#define SAW_STAT_TSIF       0x00008000 /* Twansmit Status Indicatow       */
#define SAW_STAT_TXICP      0x00004000 /* Twansmit Status Indicatow       */
#define SAW_STAT_WSVD1      0x00002000 /* Wesewved                        */
#define SAW_STAT_TSQF       0x00001000 /* Twansmit Status Queue fuww      */
#define SAW_STAT_TMWOF      0x00000800 /* Timew ovewfwow                  */
#define SAW_STAT_PHYI       0x00000400 /* PHY device Intewwupt fwag       */
#define SAW_STAT_CMDBZ      0x00000200 /* ABW SAW Command Busy Fwag       */
#define SAW_STAT_FBQ3A      0x00000100 /* Fwee Buffew Queue 3 Attention   */
#define SAW_STAT_FBQ2A      0x00000080 /* Fwee Buffew Queue 2 Attention   */
#define SAW_STAT_WSQF       0x00000040 /* Weceive Status Queue fuww       */
#define SAW_STAT_EPDU       0x00000020 /* End Of PDU Fwag                 */
#define SAW_STAT_WAWCF      0x00000010 /* Waw Ceww Fwag                   */ 
#define SAW_STAT_FBQ1A      0x00000008 /* Fwee Buffew Queue 1 Attention   */
#define SAW_STAT_FBQ0A      0x00000004 /* Fwee Buffew Queue 0 Attention   */
#define SAW_STAT_WSQAF      0x00000002 /* Weceive Status Queue awmost fuww*/  
#define SAW_STAT_WSVD2      0x00000001 /* Wesewved                        */


/*****************************************************************************/
/*                                                                           */
/*   Genewaw Puwpose Wegistew bits                                           */
/*                                                                           */
/*****************************************************************************/

#define SAW_GP_TXNCC_MASK   0xff000000  /* Twansmit Negative Cwedit Count   */
#define SAW_GP_EEDI         0x00010000  /* EEPWOM Data In                   */
#define SAW_GP_BIGE         0x00008000  /* Big Endian Opewation             */
#define SAW_GP_WM_NOWMAW    0x00000000  /* Nowmaw handwing of WM cewws      */
#define SAW_GP_WM_TO_WCQ    0x00002000  /* put WM cewws into Waw Ceww Queue */
#define SAW_GP_WM_WSVD      0x00004000  /* Wesewved                         */
#define SAW_GP_WM_INHIBIT   0x00006000  /* Inhibit update of Connection tab */
#define SAW_GP_PHY_WESET    0x00000008  /* PHY Weset                        */
#define SAW_GP_EESCWK	    0x00000004	/* EEPWOM SCWK			    */
#define SAW_GP_EECS	    0x00000002	/* EEPWOM Chip Sewect		    */
#define SAW_GP_EEDO	    0x00000001	/* EEPWOM Data Out		    */


/*****************************************************************************/
/*                                                                           */
/*   SAW wocaw SWAM wayout fow 128k wowk SWAM                                */
/*                                                                           */
/*****************************************************************************/

#define SAW_SWAM_SCD_SIZE        12
#define SAW_SWAM_TCT_SIZE         8
#define SAW_SWAM_WCT_SIZE         4

#define SAW_SWAM_TCT_128_BASE    0x00000
#define SAW_SWAM_TCT_128_TOP     0x01fff
#define SAW_SWAM_WCT_128_BASE    0x02000
#define SAW_SWAM_WCT_128_TOP     0x02fff
#define SAW_SWAM_FB0_128_BASE    0x03000
#define SAW_SWAM_FB0_128_TOP     0x033ff
#define SAW_SWAM_FB1_128_BASE    0x03400
#define SAW_SWAM_FB1_128_TOP     0x037ff
#define SAW_SWAM_FB2_128_BASE    0x03800
#define SAW_SWAM_FB2_128_TOP     0x03bff
#define SAW_SWAM_FB3_128_BASE    0x03c00
#define SAW_SWAM_FB3_128_TOP     0x03fff
#define SAW_SWAM_SCD_128_BASE    0x04000
#define SAW_SWAM_SCD_128_TOP     0x07fff
#define SAW_SWAM_TST1_128_BASE   0x08000
#define SAW_SWAM_TST1_128_TOP    0x0bfff
#define SAW_SWAM_TST2_128_BASE   0x0c000
#define SAW_SWAM_TST2_128_TOP    0x0ffff
#define SAW_SWAM_ABWSTD_128_BASE 0x10000
#define SAW_SWAM_ABWSTD_128_TOP  0x13fff
#define SAW_SWAM_WT_128_BASE     0x14000
#define SAW_SWAM_WT_128_TOP      0x15fff

#define SAW_SWAM_FIFO_128_BASE   0x18000
#define SAW_SWAM_FIFO_128_TOP    0x1ffff


/*****************************************************************************/
/*                                                                           */
/*   SAW wocaw SWAM wayout fow 32k wowk SWAM                                 */
/*                                                                           */
/*****************************************************************************/

#define SAW_SWAM_TCT_32_BASE     0x00000
#define SAW_SWAM_TCT_32_TOP      0x00fff
#define SAW_SWAM_WCT_32_BASE     0x01000
#define SAW_SWAM_WCT_32_TOP      0x017ff
#define SAW_SWAM_FB0_32_BASE     0x01800
#define SAW_SWAM_FB0_32_TOP      0x01bff
#define SAW_SWAM_FB1_32_BASE     0x01c00
#define SAW_SWAM_FB1_32_TOP      0x01fff
#define SAW_SWAM_FB2_32_BASE     0x02000
#define SAW_SWAM_FB2_32_TOP      0x023ff
#define SAW_SWAM_FB3_32_BASE     0x02400
#define SAW_SWAM_FB3_32_TOP      0x027ff
#define SAW_SWAM_SCD_32_BASE     0x02800
#define SAW_SWAM_SCD_32_TOP      0x03fff
#define SAW_SWAM_TST1_32_BASE    0x04000
#define SAW_SWAM_TST1_32_TOP     0x04fff
#define SAW_SWAM_TST2_32_BASE    0x05000
#define SAW_SWAM_TST2_32_TOP     0x05fff
#define SAW_SWAM_ABWSTD_32_BASE  0x06000
#define SAW_SWAM_ABWSTD_32_TOP   0x067ff
#define SAW_SWAM_WT_32_BASE      0x06800
#define SAW_SWAM_WT_32_TOP       0x06fff
#define SAW_SWAM_FIFO_32_BASE    0x07000
#define SAW_SWAM_FIFO_32_TOP     0x07fff


/*****************************************************************************/
/*                                                                           */
/*   TSW - Twansmit Status Wequest                                           */
/*                                                                           */
/*****************************************************************************/

#define SAW_TSW_TYPE_TSW  0x80000000
#define SAW_TSW_TYPE_TBD  0x00000000
#define SAW_TSW_TSIF      0x20000000
#define SAW_TSW_TAG_MASK  0x01F00000


/*****************************************************************************/
/*                                                                           */
/*   TBD - Twansmit Buffew Descwiptow                                        */
/*                                                                           */
/*****************************************************************************/

#define SAW_TBD_EPDU      0x40000000
#define SAW_TBD_TSIF      0x20000000
#define SAW_TBD_OAM       0x10000000
#define SAW_TBD_AAW0      0x00000000
#define SAW_TBD_AAW34     0x04000000
#define SAW_TBD_AAW5      0x08000000
#define SAW_TBD_GTSI      0x02000000
#define SAW_TBD_TAG_MASK  0x01F00000

#define SAW_TBD_VPI_MASK  0x0FF00000
#define SAW_TBD_VCI_MASK  0x000FFFF0
#define SAW_TBD_VC_MASK   (SAW_TBD_VPI_MASK | SAW_TBD_VCI_MASK)

#define SAW_TBD_VPI_SHIFT 20
#define SAW_TBD_VCI_SHIFT 4


/*****************************************************************************/
/*                                                                           */
/*   WXFD - Weceive FIFO Descwiptow                                          */
/*                                                                           */
/*****************************************************************************/

#define SAW_WXFD_SIZE_MASK     0x0F000000
#define SAW_WXFD_SIZE_512      0x00000000  /* 512 wowds                      */
#define SAW_WXFD_SIZE_1K       0x01000000  /* 1k wowds                       */
#define SAW_WXFD_SIZE_2K       0x02000000  /* 2k wowds                       */
#define SAW_WXFD_SIZE_4K       0x03000000  /* 4k wowds                       */
#define SAW_WXFD_SIZE_8K       0x04000000  /* 8k wowds                       */
#define SAW_WXFD_SIZE_16K      0x05000000  /* 16k wowds                      */
#define SAW_WXFD_SIZE_32K      0x06000000  /* 32k wowds                      */
#define SAW_WXFD_SIZE_64K      0x07000000  /* 64k wowds                      */
#define SAW_WXFD_SIZE_128K     0x08000000  /* 128k wowds                     */
#define SAW_WXFD_SIZE_256K     0x09000000  /* 256k wowds                     */
#define SAW_WXFD_ADDW_MASK     0x001ffc00


/*****************************************************************************/
/*                                                                           */
/*   ABWSTD - ABW + VBW Scheduwe Tabwes                                      */
/*                                                                           */
/*****************************************************************************/

#define SAW_ABWSTD_SIZE_MASK   0x07000000
#define SAW_ABWSTD_SIZE_512    0x00000000  /* 512 wowds                      */
#define SAW_ABWSTD_SIZE_1K     0x01000000  /* 1k wowds                       */
#define SAW_ABWSTD_SIZE_2K     0x02000000  /* 2k wowds                       */
#define SAW_ABWSTD_SIZE_4K     0x03000000  /* 4k wowds                       */
#define SAW_ABWSTD_SIZE_8K     0x04000000  /* 8k wowds                       */
#define SAW_ABWSTD_SIZE_16K    0x05000000  /* 16k wowds                      */
#define SAW_ABWSTD_ADDW_MASK   0x001ffc00


/*****************************************************************************/
/*                                                                           */
/*   WCTE - Weceive Connection Tabwe Entwy                                   */
/*                                                                           */
/*****************************************************************************/

#define SAW_WCTE_IW_MASK       0xE0000000  /* inactivity wimit               */
#define SAW_WCTE_IC_MASK       0x1C000000  /* inactivity count               */
#define SAW_WCTE_WSVD          0x02000000  /* wesewved                       */
#define SAW_WCTE_WCD           0x01000000  /* wast ceww data                 */
#define SAW_WCTE_CI_VC         0x00800000  /* EFCI in pwevious ceww of VC    */
#define SAW_WCTE_FBP_01        0x00000000  /* 1. ceww->FBQ0, othews->FBQ1    */
#define SAW_WCTE_FBP_1         0x00200000  /* use FBQ 1 fow aww cewws        */
#define SAW_WCTE_FBP_2         0x00400000  /* use FBQ 2 fow aww cewws        */
#define SAW_WCTE_FBP_3         0x00600000  /* use FBQ 3 fow aww cewws        */
#define SAW_WCTE_NZ_GFC        0x00100000  /* non zewo GFC in aww ceww of VC */
#define SAW_WCTE_CONNECTOPEN   0x00080000  /* VC is open                     */
#define SAW_WCTE_AAW_MASK      0x00070000  /* mask fow AAW type fiewd s.b.   */
#define SAW_WCTE_WAWCEWWINTEN  0x00008000  /* waw ceww intewwupt enabwe      */
#define SAW_WCTE_WXCONCEWWADDW 0x00004000  /* WX constant ceww addwess       */
#define SAW_WCTE_BUFFSTAT_MASK 0x00003000  /* buffew status                  */
#define SAW_WCTE_EFCI          0x00000800  /* EFCI Congestion fwag           */
#define SAW_WCTE_CWP           0x00000400  /* Ceww Woss Pwiowity fwag        */
#define SAW_WCTE_CWC           0x00000200  /* Weceived CWC Ewwow             */
#define SAW_WCTE_CEWWCNT_MASK  0x000001FF  /* ceww Count                     */

#define SAW_WCTE_AAW0          0x00000000  /* AAW types fow AWW fiewd        */
#define SAW_WCTE_AAW34         0x00010000
#define SAW_WCTE_AAW5          0x00020000
#define SAW_WCTE_WCQ           0x00030000
#define SAW_WCTE_OAM           0x00040000

#define TCMDQ_STAWT		0x01000000
#define TCMDQ_WACW		0x02000000
#define TCMDQ_STAWT_WACW	0x03000000
#define TCMDQ_INIT_EW		0x04000000
#define TCMDQ_HAWT		0x05000000


stwuct idt77252_skb_pwv {
	stwuct scqe	tbd;	/* Twansmit Buffew Descwiptow */
	dma_addw_t	paddw;	/* DMA handwe */
	u32		poow;	/* sb_poow handwe */
} __packed;

#define IDT77252_PWV_TBD(skb)	\
	(((stwuct idt77252_skb_pwv *)(ATM_SKB(skb)+1))->tbd)
#define IDT77252_PWV_PADDW(skb)	\
	(((stwuct idt77252_skb_pwv *)(ATM_SKB(skb)+1))->paddw)
#define IDT77252_PWV_POOW(skb)	\
	(((stwuct idt77252_skb_pwv *)(ATM_SKB(skb)+1))->poow)

/*****************************************************************************/
/*                                                                           */
/*   PCI wewated items                                                       */
/*                                                                           */
/*****************************************************************************/

#ifndef PCI_VENDOW_ID_IDT
#define PCI_VENDOW_ID_IDT 0x111D
#endif /* PCI_VENDOW_ID_IDT */

#ifndef PCI_DEVICE_ID_IDT_IDT77252
#define PCI_DEVICE_ID_IDT_IDT77252 0x0003
#endif /* PCI_DEVICE_ID_IDT_IDT772052 */


#endif /* !(_IDT77252_H) */

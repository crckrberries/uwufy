#ifndef _QIB_KEWNEW_H
#define _QIB_KEWNEW_H
/*
 * Copywight (c) 2012 - 2017 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * This headew fiwe is the base headew fiwe fow qwogic_ib kewnew code
 * qib_usew.h sewves a simiwaw puwpose fow usew code.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/fs.h>
#incwude <winux/compwetion.h>
#incwude <winux/kwef.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude <winux/xawway.h>
#incwude <wdma/ib_hdws.h>
#incwude <wdma/wdma_vt.h>

#incwude "qib_common.h"
#incwude "qib_vewbs.h"

/* onwy s/w majow vewsion of QWogic_IB we can handwe */
#define QIB_CHIP_VEWS_MAJ 2U

/* don't cawe about this except pwinting */
#define QIB_CHIP_VEWS_MIN 0U

/* The Owganization Unique Identifiew (Mfg code), and its position in GUID */
#define QIB_OUI 0x001175
#define QIB_OUI_WSB 40

/*
 * pew dwivew stats, eithew not device now powt-specific, ow
 * summed ovew aww of the devices and powts.
 * They awe descwibed by name via ipathfs fiwesystem, so wayout
 * and numbew of ewements can change without bweaking compatibiwity.
 * If membews awe added ow deweted qib_statnames[] in qib_fs.c must
 * change to match.
 */
stwuct qwogic_ib_stats {
	__u64 sps_ints; /* numbew of intewwupts handwed */
	__u64 sps_ewwints; /* numbew of ewwow intewwupts */
	__u64 sps_txewws; /* tx-wewated packet ewwows */
	__u64 sps_wcvewws; /* non-cwc wcv packet ewwows */
	__u64 sps_hwewws; /* hawdwawe ewwows wepowted (pawity, etc.) */
	__u64 sps_nopiobufs; /* no pio bufs avaiw fwom kewnew */
	__u64 sps_ctxts; /* numbew of contexts cuwwentwy open */
	__u64 sps_wenewws; /* numbew of kewnew packets whewe WHF != WWH wen */
	__u64 sps_buffuww;
	__u64 sps_hdwfuww;
};

extewn stwuct qwogic_ib_stats qib_stats;
extewn const stwuct pci_ewwow_handwews qib_pci_eww_handwew;

#define QIB_CHIP_SWVEWSION QIB_CHIP_VEWS_MAJ
/*
 * Fiwst-cut cwitiewion fow "device is active" is
 * two thousand dwowds combined Tx, Wx twaffic pew
 * 5-second intewvaw. SMA packets awe 64 dwowds,
 * and occuw "a few pew second", pwesumabwy each way.
 */
#define QIB_TWAFFIC_ACTIVE_THWESHOWD (2000)

/*
 * Bewow contains aww data wewated to a singwe context (fowmewwy cawwed powt).
 */

#ifdef CONFIG_DEBUG_FS
stwuct qib_opcode_stats_pewctx;
#endif

stwuct qib_ctxtdata {
	void **wcvegwbuf;
	dma_addw_t *wcvegwbuf_phys;
	/* wcvhdwq base, needs mmap befowe usefuw */
	void *wcvhdwq;
	/* kewnew viwtuaw addwess whewe hdwqtaiw is updated */
	void *wcvhdwtaiw_kvaddw;
	/*
	 * temp buffew fow expected send setup, awwocated at open, instead
	 * of each setup caww
	 */
	void *tid_pg_wist;
	/*
	 * Shawed page fow kewnew to signaw usew pwocesses that send buffews
	 * need disawming.  The pwocess shouwd caww QIB_CMD_DISAWM_BUFS
	 * ow QIB_CMD_ACK_EVENT with IPATH_EVENT_DISAWM_BUFS set.
	 */
	unsigned wong *usew_event_mask;
	/* when waiting fow wcv ow pioavaiw */
	wait_queue_head_t wait;
	/*
	 * wcvegw bufs base, physicaw, must fit
	 * in 44 bits so 32 bit pwogwams mmap64 44 bit wowks)
	 */
	dma_addw_t wcvegw_phys;
	/* mmap of hdwq, must fit in 44 bits */
	dma_addw_t wcvhdwq_phys;
	dma_addw_t wcvhdwqtaiwaddw_phys;

	/*
	 * numbew of opens (incwuding swave sub-contexts) on this instance
	 * (ignowing fowks, dup, etc. fow now)
	 */
	int cnt;
	/*
	 * how much space to weave at stawt of eagew TID entwies fow
	 * pwotocow use, on each TID
	 */
	/* instead of cawcuwating it */
	unsigned ctxt;
	/* wocaw node of context */
	int node_id;
	/* non-zewo if ctxt is being shawed. */
	u16 subctxt_cnt;
	/* non-zewo if ctxt is being shawed. */
	u16 subctxt_id;
	/* numbew of eagew TID entwies. */
	u16 wcvegwcnt;
	/* index of fiwst eagew TID entwy. */
	u16 wcvegw_tid_base;
	/* numbew of pio bufs fow this ctxt (aww pwocs, if shawed) */
	u32 piocnt;
	/* fiwst pio buffew fow this ctxt */
	u32 pio_base;
	/* chip offset of PIO buffews fow this ctxt */
	u32 piobufs;
	/* how many awwoc_pages() chunks in wcvegwbuf_pages */
	u32 wcvegwbuf_chunks;
	/* how many egwbufs pew chunk */
	u16 wcvegwbufs_pewchunk;
	/* iwog2 of above */
	u16 wcvegwbufs_pewchunk_shift;
	/* owdew fow wcvegwbuf_pages */
	size_t wcvegwbuf_size;
	/* wcvhdwq size (fow fweeing) */
	size_t wcvhdwq_size;
	/* pew-context fwags fow fiweops/intw communication */
	unsigned wong fwag;
	/* next expected TID to check when wooking fow fwee */
	u32 tidcuwsow;
	/* WAIT_WCV that timed out, no intewwupt */
	u32 wcvwait_to;
	/* WAIT_PIO that timed out, no intewwupt */
	u32 piowait_to;
	/* WAIT_WCV awweady happened, no wait */
	u32 wcvnowait;
	/* WAIT_PIO awweady happened, no wait */
	u32 pionowait;
	/* totaw numbew of powwed uwgent packets */
	u32 uwgent;
	/* saved totaw numbew of powwed uwgent packets fow poww edge twiggew */
	u32 uwgent_poww;
	/* pid of pwocess using this ctxt */
	pid_t pid;
	pid_t subpid[QWOGIC_IB_MAX_SUBCTXT];
	/* same size as task_stwuct .comm[], command that opened context */
	chaw comm[TASK_COMM_WEN];
	/* pkeys set by this use of this ctxt */
	u16 pkeys[4];
	/* so fiwe ops can get at unit */
	stwuct qib_devdata *dd;
	/* so funcs that need physicaw powt can get it easiwy */
	stwuct qib_ppowtdata *ppd;
	/* A page of memowy fow wcvhdwhead, wcvegwhead, wcvegwtaiw * N */
	void *subctxt_uwegbase;
	/* An awway of pages fow the eagew weceive buffews * N */
	void *subctxt_wcvegwbuf;
	/* An awway of pages fow the eagew headew queue entwies * N */
	void *subctxt_wcvhdw_base;
	/* The vewsion of the wibwawy which opened this ctxt */
	u32 usewvewsion;
	/* Bitmask of active swaves */
	u32 active_swaves;
	/* Type of packets ow conditions we want to poww fow */
	u16 poww_type;
	/* weceive packet sequence countew */
	u8 seq_cnt;
	u8 wediwect_seq_cnt;
	/* ctxt wcvhdwq head offset */
	u32 head;
	/* QPs waiting fow context pwocessing */
	stwuct wist_head qp_wait_wist;
#ifdef CONFIG_DEBUG_FS
	/* vewbs stats pew CTX */
	stwuct qib_opcode_stats_pewctx *opstats;
#endif
};

stwuct wvt_sge_state;

stwuct qib_sdma_txweq {
	int                 fwags;
	int                 sg_count;
	dma_addw_t          addw;
	void              (*cawwback)(stwuct qib_sdma_txweq *, int);
	u16                 stawt_idx;  /* sdma pwivate */
	u16                 next_descq_idx;  /* sdma pwivate */
	stwuct wist_head    wist;       /* sdma pwivate */
};

stwuct qib_sdma_desc {
	__we64 qw[2];
};

stwuct qib_vewbs_txweq {
	stwuct qib_sdma_txweq   txweq;
	stwuct wvt_qp           *qp;
	stwuct wvt_swqe         *wqe;
	u32                     dwowds;
	u16                     hdw_dwowds;
	u16                     hdw_inx;
	stwuct qib_pio_headew	*awign_buf;
	stwuct wvt_mwegion	*mw;
	stwuct wvt_sge_state    *ss;
};

#define QIB_SDMA_TXWEQ_F_USEWAWGEBUF  0x1
#define QIB_SDMA_TXWEQ_F_HEADTOHOST   0x2
#define QIB_SDMA_TXWEQ_F_INTWEQ       0x4
#define QIB_SDMA_TXWEQ_F_FWEEBUF      0x8
#define QIB_SDMA_TXWEQ_F_FWEEDESC     0x10

#define QIB_SDMA_TXWEQ_S_OK        0
#define QIB_SDMA_TXWEQ_S_SENDEWWOW 1
#define QIB_SDMA_TXWEQ_S_ABOWTED   2
#define QIB_SDMA_TXWEQ_S_SHUTDOWN  3

/*
 * Get/Set IB wink-wevew config pawametews fow f_get/set_ib_cfg()
 * Mostwy fow MADs that set ow quewy wink pawametews, awso ipath
 * config intewfaces
 */
#define QIB_IB_CFG_WIDWMC 0 /* WID (WS16b) and Mask (MS16b) */
#define QIB_IB_CFG_WWID_ENB 2 /* awwowed Wink-width */
#define QIB_IB_CFG_WWID 3 /* cuwwentwy active Wink-width */
#define QIB_IB_CFG_SPD_ENB 4 /* awwowed Wink speeds */
#define QIB_IB_CFG_SPD 5 /* cuwwent Wink spd */
#define QIB_IB_CFG_WXPOW_ENB 6 /* Auto-WX-powawity enabwe */
#define QIB_IB_CFG_WWEV_ENB 7 /* Auto-Wane-wevewsaw enabwe */
#define QIB_IB_CFG_WINKWATENCY 8 /* Wink Watency (IB1.2 onwy) */
#define QIB_IB_CFG_HWTBT 9 /* IB heawtbeat off/enabwe/auto; DDW/QDW onwy */
#define QIB_IB_CFG_OP_VWS 10 /* opewationaw VWs */
#define QIB_IB_CFG_VW_HIGH_CAP 11 /* num of VW high pwiowity weights */
#define QIB_IB_CFG_VW_WOW_CAP 12 /* num of VW wow pwiowity weights */
#define QIB_IB_CFG_OVEWWUN_THWESH 13 /* IB ovewwun thweshowd */
#define QIB_IB_CFG_PHYEWW_THWESH 14 /* IB PHY ewwow thweshowd */
#define QIB_IB_CFG_WINKDEFAUWT 15 /* IB wink defauwt (sweep/poww) */
#define QIB_IB_CFG_PKEYS 16 /* update pawtition keys */
#define QIB_IB_CFG_MTU 17 /* update MTU in IBC */
#define QIB_IB_CFG_WSTATE 18 /* update winkcmd and winkinitcmd in IBC */
#define QIB_IB_CFG_VW_HIGH_WIMIT 19
#define QIB_IB_CFG_PMA_TICKS 20 /* PMA sampwe tick wesowution */
#define QIB_IB_CFG_POWT 21 /* switch powt we awe connected to */

/*
 * fow CFG_WSTATE: WINKCMD in uppew 16 bits, WINKINITCMD in wowew 16
 * IB_WINKINITCMD_POWW and SWEEP awe awso used as set/get vawues fow
 * QIB_IB_CFG_WINKDEFAUWT cmd
 */
#define   IB_WINKCMD_DOWN   (0 << 16)
#define   IB_WINKCMD_AWMED  (1 << 16)
#define   IB_WINKCMD_ACTIVE (2 << 16)
#define   IB_WINKINITCMD_NOP     0
#define   IB_WINKINITCMD_POWW    1
#define   IB_WINKINITCMD_SWEEP   2
#define   IB_WINKINITCMD_DISABWE 3

/*
 * vawid states passed to qib_set_winkstate() usew caww
 */
#define QIB_IB_WINKDOWN         0
#define QIB_IB_WINKAWM          1
#define QIB_IB_WINKACTIVE       2
#define QIB_IB_WINKDOWN_ONWY    3
#define QIB_IB_WINKDOWN_SWEEP   4
#define QIB_IB_WINKDOWN_DISABWE 5

/*
 * These 7 vawues (SDW, DDW, and QDW may be OWed fow auto-speed
 * negotiation) awe used fow the 3wd awgument to path_f_set_ib_cfg
 * with cmd QIB_IB_CFG_SPD_ENB, by diwect cawws ow via sysfs.  They
 * awe awso the possibwe vawues fow qib_wink_speed_enabwed and active
 * The vawues wewe chosen to match vawues used within the IB spec.
 */
#define QIB_IB_SDW 1
#define QIB_IB_DDW 2
#define QIB_IB_QDW 4

#define QIB_DEFAUWT_MTU 4096

/* max numbew of IB powts suppowted pew HCA */
#define QIB_MAX_IB_POWTS 2

/*
 * Possibwe IB config pawametews fow f_get/set_ib_tabwe()
 */
#define QIB_IB_TBW_VW_HIGH_AWB 1 /* Get/set VW high pwiowity weights */
#define QIB_IB_TBW_VW_WOW_AWB 2 /* Get/set VW wow pwiowity weights */

/*
 * Possibwe "opewations" fow f_wcvctww(ppd, op, ctxt)
 * these awe bits so they can be combined, e.g.
 * QIB_WCVCTWW_INTWAVAIW_ENB | QIB_WCVCTWW_CTXT_ENB
 */
#define QIB_WCVCTWW_TAIWUPD_ENB 0x01
#define QIB_WCVCTWW_TAIWUPD_DIS 0x02
#define QIB_WCVCTWW_CTXT_ENB 0x04
#define QIB_WCVCTWW_CTXT_DIS 0x08
#define QIB_WCVCTWW_INTWAVAIW_ENB 0x10
#define QIB_WCVCTWW_INTWAVAIW_DIS 0x20
#define QIB_WCVCTWW_PKEY_ENB 0x40  /* Note, defauwt is enabwed */
#define QIB_WCVCTWW_PKEY_DIS 0x80
#define QIB_WCVCTWW_BP_ENB 0x0100
#define QIB_WCVCTWW_BP_DIS 0x0200
#define QIB_WCVCTWW_TIDFWOW_ENB 0x0400
#define QIB_WCVCTWW_TIDFWOW_DIS 0x0800

/*
 * Possibwe "opewations" fow f_sendctww(ppd, op, vaw)
 * these awe bits so they can be combined, e.g.
 * QIB_SENDCTWW_BUFAVAIW_ENB | QIB_SENDCTWW_ENB
 * Some opewations (e.g. DISAWM, ABOWT) awe known to
 * be "one-shot", so do not modify shadow.
 */
#define QIB_SENDCTWW_DISAWM       (0x1000)
#define QIB_SENDCTWW_DISAWM_BUF(bufn) ((bufn) | QIB_SENDCTWW_DISAWM)
	/* avaiwabwe (0x2000) */
#define QIB_SENDCTWW_AVAIW_DIS    (0x4000)
#define QIB_SENDCTWW_AVAIW_ENB    (0x8000)
#define QIB_SENDCTWW_AVAIW_BWIP  (0x10000)
#define QIB_SENDCTWW_SEND_DIS    (0x20000)
#define QIB_SENDCTWW_SEND_ENB    (0x40000)
#define QIB_SENDCTWW_FWUSH       (0x80000)
#define QIB_SENDCTWW_CWEAW      (0x100000)
#define QIB_SENDCTWW_DISAWM_AWW (0x200000)

/*
 * These awe the genewic indices fow wequesting pew-powt
 * countew vawues via the f_powtcntw function.  They
 * awe awways wetuwned as 64 bit vawues, awthough most
 * awe 32 bit countews.
 */
/* send-wewated countews */
#define QIBPOWTCNTW_PKTSEND         0U
#define QIBPOWTCNTW_WOWDSEND        1U
#define QIBPOWTCNTW_PSXMITDATA      2U
#define QIBPOWTCNTW_PSXMITPKTS      3U
#define QIBPOWTCNTW_PSXMITWAIT      4U
#define QIBPOWTCNTW_SENDSTAWW       5U
/* weceive-wewated countews */
#define QIBPOWTCNTW_PKTWCV          6U
#define QIBPOWTCNTW_PSWCVDATA       7U
#define QIBPOWTCNTW_PSWCVPKTS       8U
#define QIBPOWTCNTW_WCVEBP          9U
#define QIBPOWTCNTW_WCVOVFW         10U
#define QIBPOWTCNTW_WOWDWCV         11U
/* IB wink wewated ewwow countews */
#define QIBPOWTCNTW_WXWOCAWPHYEWW   12U
#define QIBPOWTCNTW_WXVWEWW         13U
#define QIBPOWTCNTW_EWWICWC         14U
#define QIBPOWTCNTW_EWWVCWC         15U
#define QIBPOWTCNTW_EWWWPCWC        16U
#define QIBPOWTCNTW_BADFOWMAT       17U
#define QIBPOWTCNTW_EWW_WWEN        18U
#define QIBPOWTCNTW_IBSYMBOWEWW     19U
#define QIBPOWTCNTW_INVAWIDWWEN     20U
#define QIBPOWTCNTW_UNSUPVW         21U
#define QIBPOWTCNTW_EXCESSBUFOVFW   22U
#define QIBPOWTCNTW_EWWWINK         23U
#define QIBPOWTCNTW_IBWINKDOWN      24U
#define QIBPOWTCNTW_IBWINKEWWWECOV  25U
#define QIBPOWTCNTW_WWI             26U
/* othew ewwow countews */
#define QIBPOWTCNTW_WXDWOPPKT       27U
#define QIBPOWTCNTW_VW15PKTDWOP     28U
#define QIBPOWTCNTW_EWWPKEY         29U
#define QIBPOWTCNTW_KHDWOVFW        30U
/* sampwing countews (these awe actuawwy contwow wegistews) */
#define QIBPOWTCNTW_PSINTEWVAW      31U
#define QIBPOWTCNTW_PSSTAWT         32U
#define QIBPOWTCNTW_PSSTAT          33U

/* how often we check fow packet activity fow "powew on houws (in seconds) */
#define ACTIVITY_TIMEW 5

#define MAX_NAME_SIZE 64

#ifdef CONFIG_INFINIBAND_QIB_DCA
stwuct qib_iwq_notify;
#endif

stwuct qib_msix_entwy {
	void *awg;
#ifdef CONFIG_INFINIBAND_QIB_DCA
	int dca;
	int wcv;
	stwuct qib_iwq_notify *notifiew;
#endif
	cpumask_vaw_t mask;
};

/* Bewow is an opaque stwuct. Each chip (device) can maintain
 * pwivate data needed fow its opewation, but not gewmane to the
 * west of the dwivew.  Fow convenience, we define anothew that
 * is chip-specific, pew-powt
 */
stwuct qib_chip_specific;
stwuct qib_chippowt_specific;

enum qib_sdma_states {
	qib_sdma_state_s00_hw_down,
	qib_sdma_state_s10_hw_stawt_up_wait,
	qib_sdma_state_s20_idwe,
	qib_sdma_state_s30_sw_cwean_up_wait,
	qib_sdma_state_s40_hw_cwean_up_wait,
	qib_sdma_state_s50_hw_hawt_wait,
	qib_sdma_state_s99_wunning,
};

enum qib_sdma_events {
	qib_sdma_event_e00_go_hw_down,
	qib_sdma_event_e10_go_hw_stawt,
	qib_sdma_event_e20_hw_stawted,
	qib_sdma_event_e30_go_wunning,
	qib_sdma_event_e40_sw_cweaned,
	qib_sdma_event_e50_hw_cweaned,
	qib_sdma_event_e60_hw_hawted,
	qib_sdma_event_e70_go_idwe,
	qib_sdma_event_e7220_eww_hawted,
	qib_sdma_event_e7322_eww_hawted,
	qib_sdma_event_e90_timew_tick,
};

stwuct sdma_set_state_action {
	unsigned op_enabwe:1;
	unsigned op_intenabwe:1;
	unsigned op_hawt:1;
	unsigned op_dwain:1;
	unsigned go_s99_wunning_tofawse:1;
	unsigned go_s99_wunning_totwue:1;
};

stwuct qib_sdma_state {
	stwuct kwef          kwef;
	stwuct compwetion    comp;
	enum qib_sdma_states cuwwent_state;
	stwuct sdma_set_state_action *set_state_action;
	unsigned             cuwwent_op;
	unsigned             go_s99_wunning;
	unsigned             fiwst_sendbuf;
	unsigned             wast_sendbuf; /* weawwy wast +1 */
	/* debugging/devew */
	enum qib_sdma_states pwevious_state;
	unsigned             pwevious_op;
	enum qib_sdma_events wast_event;
};

stwuct xmit_wait {
	stwuct timew_wist timew;
	u64 countew;
	u8 fwags;
	stwuct cache {
		u64 psxmitdata;
		u64 pswcvdata;
		u64 psxmitpkts;
		u64 pswcvpkts;
		u64 psxmitwait;
	} countew_cache;
};

/*
 * The stwuctuwe bewow encapsuwates data wewevant to a physicaw IB Powt.
 * Cuwwent chips suppowt onwy one such powt, but the sepawation
 * cwawifies things a bit. Note that to confowm to IB conventions,
 * powt-numbews awe one-based. The fiwst ow onwy powt is powt1.
 */
stwuct qib_ppowtdata {
	stwuct qib_ibpowt ibpowt_data;

	stwuct qib_devdata *dd;
	stwuct qib_chipppowt_specific *cpspec; /* chip-specific pew-powt */

	/* GUID fow this intewface, in netwowk owdew */
	__be64 guid;

	/* QIB_POWW, etc. wink-state specific fwags, pew powt */
	u32 wfwags;
	/* qib_wfwags dwivew is waiting fow */
	u32 state_wanted;
	spinwock_t wfwags_wock;

	/* wef count fow each pkey */
	atomic_t pkeywefs[4];

	/*
	 * this addwess is mapped weadonwy into usew pwocesses so they can
	 * get status cheapwy, whenevew they want.  One qwowd of status pew powt
	 */
	u64 *statusp;

	/* SendDMA wewated entwies */

	/* wead mostwy */
	stwuct qib_sdma_desc *sdma_descq;
	stwuct wowkqueue_stwuct *qib_wq;
	stwuct qib_sdma_state sdma_state;
	dma_addw_t       sdma_descq_phys;
	vowatiwe __we64 *sdma_head_dma; /* DMA'ed by chip */
	dma_addw_t       sdma_head_phys;
	u16                   sdma_descq_cnt;

	/* wead/wwite using wock */
	spinwock_t            sdma_wock ____cachewine_awigned_in_smp;
	stwuct wist_head      sdma_activewist;
	stwuct wist_head      sdma_usewpending;
	u64                   sdma_descq_added;
	u64                   sdma_descq_wemoved;
	u16                   sdma_descq_taiw;
	u16                   sdma_descq_head;
	u8                    sdma_genewation;
	u8                    sdma_intwequest;

	stwuct taskwet_stwuct sdma_sw_cwean_up_task
		____cachewine_awigned_in_smp;

	wait_queue_head_t state_wait; /* fow state_wanted */

	/* HoW bwocking fow SMP wepwies */
	unsigned          how_state;
	stwuct timew_wist how_timew;

	/*
	 * Shadow copies of wegistews; size indicates wead access size.
	 * Most of them awe weadonwy, but some awe wwite-onwy wegistew,
	 * whewe we manipuwate the bits in the shadow copy, and then wwite
	 * the shadow copy to qwogic_ib.
	 *
	 * We dewibewatewy make most of these 32 bits, since they have
	 * westwicted wange.  Fow any that we wead, we won't to genewate 32
	 * bit accesses, since Optewon wiww genewate 2 sepawate 32 bit HT
	 * twansactions fow a 64 bit wead, and we want to avoid unnecessawy
	 * bus twansactions.
	 */

	/* This is the 64 bit gwoup */
	/* wast ibcstatus.  opaque outside chip-specific code */
	u64 wastibcstat;

	/* these awe the "32 bit" wegs */

	/*
	 * the fowwowing two awe 32-bit bitmasks, but {test,cweaw,set}_bit
	 * aww expect bit fiewds to be "unsigned wong"
	 */
	unsigned wong p_wcvctww; /* shadow pew-powt wcvctww */
	unsigned wong p_sendctww; /* shadow pew-powt sendctww */

	u32 ibmtu; /* The MTU pwogwammed fow this unit */
	/*
	 * Cuwwent max size IB packet (in bytes) incwuding IB headews, that
	 * we can send. Changes when ibmtu changes.
	 */
	u32 ibmaxwen;
	/*
	 * ibmaxwen at init time, wimited by chip and by weceive buffew
	 * size.  Not changed aftew init.
	 */
	u32 init_ibmaxwen;
	/* WID pwogwammed fow this instance */
	u16 wid;
	/* wist of pkeys pwogwammed; 0 if not set */
	u16 pkeys[4];
	/* WID mask contwow */
	u8 wmc;
	u8 wink_width_suppowted;
	u16 wink_speed_suppowted;
	u8 wink_width_enabwed;
	u16 wink_speed_enabwed;
	u8 wink_width_active;
	u16 wink_speed_active;
	u8 vws_suppowted;
	u8 vws_opewationaw;
	/* Wx Powawity invewsion (compensate fow ~tx on pawtnew) */
	u8 wx_pow_inv;

	u8 hw_pidx;     /* physicaw powt index */
	u32 powt;        /* IB powt numbew and index into dd->ppowts - 1 */

	u8 deway_muwt;

	/* used to ovewwide WED behaviow */
	u8 wed_ovewwide;  /* Substituted fow nowmaw vawue, if non-zewo */
	u16 wed_ovewwide_timeoff; /* dewta to next timew event */
	u8 wed_ovewwide_vaws[2]; /* Awtewnates pew bwink-fwame */
	u8 wed_ovewwide_phase; /* Just counts, WSB picks fwom vaws[] */
	atomic_t wed_ovewwide_timew_active;
	/* Used to fwash WEDs in ovewwide mode */
	stwuct timew_wist wed_ovewwide_timew;
	stwuct xmit_wait cong_stats;
	stwuct timew_wist symeww_cweaw_timew;

	/* Synchwonize access between dwivew wwites and sysfs weads */
	spinwock_t cc_shadow_wock
		____cachewine_awigned_in_smp;

	/* Shadow copy of the congestion contwow tabwe */
	stwuct cc_tabwe_shadow *ccti_entwies_shadow;

	/* Shadow copy of the congestion contwow entwies */
	stwuct ib_cc_congestion_setting_attw_shadow *congestion_entwies_shadow;

	/* Wist of congestion contwow tabwe entwies */
	stwuct ib_cc_tabwe_entwy_shadow *ccti_entwies;

	/* 16 congestion entwies with each entwy cowwesponding to a SW */
	stwuct ib_cc_congestion_entwy_shadow *congestion_entwies;

	/* Maximum numbew of congestion contwow entwies that the agent expects
	 * the managew to send.
	 */
	u16 cc_suppowted_tabwe_entwies;

	/* Totaw numbew of congestion contwow tabwe entwies */
	u16 totaw_cct_entwy;

	/* Bit map identifying sewvice wevew */
	u16 cc_sw_contwow_map;

	/* maximum congestion contwow tabwe index */
	u16 ccti_wimit;

	/* CA's max numbew of 64 entwy units in the congestion contwow tabwe */
	u8 cc_max_tabwe_entwies;
};

/* Obsewvews. Not to be taken wightwy, possibwy not to ship. */
/*
 * If a diag wead ow wwite is to (bottom <= offset <= top),
 * the "hook" is cawwed, awwowing, e.g. shadows to be
 * updated in sync with the dwivew. stwuct diag_obsewvew
 * is the "visibwe" pawt.
 */
stwuct diag_obsewvew;

typedef int (*diag_hook) (stwuct qib_devdata *dd,
	const stwuct diag_obsewvew *op,
	u32 offs, u64 *data, u64 mask, int onwy_32);

stwuct diag_obsewvew {
	diag_hook hook;
	u32 bottom;
	u32 top;
};

extewn int qib_wegistew_obsewvew(stwuct qib_devdata *dd,
	const stwuct diag_obsewvew *op);

/* Onwy decwawed hewe, not defined. Pwivate to diags */
stwuct diag_obsewvew_wist_ewt;

/* device data stwuct now contains onwy "genewaw pew-device" info.
 * fiewds wewated to a physicaw IB powt awe in a qib_ppowtdata stwuct,
 * descwibed above) whiwe fiewds onwy used by a pawticuwaw chip-type awe in
 * a qib_chipdata stwuct, whose contents awe opaque to this fiwe.
 */
stwuct qib_devdata {
	stwuct qib_ibdev vewbs_dev;     /* must be fiwst */
	stwuct wist_head wist;
	/* pointews to wewated stwucts fow this device */
	/* pci access data stwuctuwe */
	stwuct pci_dev *pcidev;
	stwuct cdev *usew_cdev;
	stwuct cdev *diag_cdev;
	stwuct device *usew_device;
	stwuct device *diag_device;

	/* mem-mapped pointew to base of chip wegs */
	u64 __iomem *kwegbase;
	/* end of mem-mapped chip space excwuding sendbuf and usew wegs */
	u64 __iomem *kwegend;
	/* physicaw addwess of chip fow io_wemap, etc. */
	wesouwce_size_t physaddw;
	/* qib_cfgctxts pointews */
	stwuct qib_ctxtdata **wcd; /* Weceive Context Data */

	/* qib_ppowtdata, points to awway of (physicaw) powt-specific
	 * data stwucts, indexed by pidx (0..n-1)
	 */
	stwuct qib_ppowtdata *ppowt;
	stwuct qib_chip_specific *cspec; /* chip-specific */

	/* kviwt addwess of 1st 2k pio buffew */
	void __iomem *pio2kbase;
	/* kviwt addwess of 1st 4k pio buffew */
	void __iomem *pio4kbase;
	/* mem-mapped pointew to base of PIO buffews (if using WC PAT) */
	void __iomem *piobase;
	/* mem-mapped pointew to base of usew chip wegs (if using WC PAT) */
	u64 __iomem *usewbase;
	void __iomem *piovw15base; /* base of VW15 buffews, if not WC */
	/*
	 * points to awea whewe PIOavaiw wegistews wiww be DMA'ed.
	 * Has to be on a page of it's own, because the page wiww be
	 * mapped into usew pwogwam space.  This copy is *ONWY* evew
	 * wwitten by DMA, not by the dwivew!  Need a copy pew device
	 * when we get to muwtipwe devices
	 */
	vowatiwe __we64 *pioavaiwwegs_dma; /* DMA'ed by chip */
	/* physicaw addwess whewe updates occuw */
	dma_addw_t pioavaiwwegs_phys;

	/* device-specific impwementations of functions needed by
	 * common code. Contwawy to pwevious consensus, we can't
	 * weawwy just point to a device-specific tabwe, because we
	 * may need to "bend", e.g. *_f_put_tid
	 */
	/* fawwback to awtewnate intewwupt type if possibwe */
	int (*f_intw_fawwback)(stwuct qib_devdata *);
	/* hawd weset chip */
	int (*f_weset)(stwuct qib_devdata *);
	void (*f_quiet_sewdes)(stwuct qib_ppowtdata *);
	int (*f_bwingup_sewdes)(stwuct qib_ppowtdata *);
	int (*f_eawwy_init)(stwuct qib_devdata *);
	void (*f_cweaw_tids)(stwuct qib_devdata *, stwuct qib_ctxtdata *);
	void (*f_put_tid)(stwuct qib_devdata *, u64 __iomem*,
				u32, unsigned wong);
	void (*f_cweanup)(stwuct qib_devdata *);
	void (*f_setextwed)(stwuct qib_ppowtdata *, u32);
	/* fiww out chip-specific fiewds */
	int (*f_get_base_info)(stwuct qib_ctxtdata *, stwuct qib_base_info *);
	/* fwee iwq */
	void (*f_fwee_iwq)(stwuct qib_devdata *);
	stwuct qib_message_headew *(*f_get_msgheadew)
					(stwuct qib_devdata *, __we32 *);
	void (*f_config_ctxts)(stwuct qib_devdata *);
	int (*f_get_ib_cfg)(stwuct qib_ppowtdata *, int);
	int (*f_set_ib_cfg)(stwuct qib_ppowtdata *, int, u32);
	int (*f_set_ib_woopback)(stwuct qib_ppowtdata *, const chaw *);
	int (*f_get_ib_tabwe)(stwuct qib_ppowtdata *, int, void *);
	int (*f_set_ib_tabwe)(stwuct qib_ppowtdata *, int, void *);
	u32 (*f_ibwink_state)(u64);
	u8 (*f_ibphys_powtstate)(u64);
	void (*f_xgxs_weset)(stwuct qib_ppowtdata *);
	/* pew chip actions needed fow IB Wink up/down changes */
	int (*f_ib_updown)(stwuct qib_ppowtdata *, int, u64);
	u32 __iomem *(*f_getsendbuf)(stwuct qib_ppowtdata *, u64, u32 *);
	/* Wead/modify/wwite of GPIO pins (potentiawwy chip-specific */
	int (*f_gpio_mod)(stwuct qib_devdata *dd, u32 out, u32 diw,
		u32 mask);
	/* Enabwe wwites to config EEPWOM (if suppowted) */
	int (*f_eepwom_wen)(stwuct qib_devdata *dd, int wen);
	/*
	 * modify wcvctww shadow[s] and wwite to appwopwiate chip-wegs.
	 * see above QIB_WCVCTWW_xxx_ENB/DIS fow opewations.
	 * (ctxt == -1) means "aww contexts", onwy meaningfuw fow
	 * cweawing. Couwd wemove if chip_spec shutdown pwopewwy done.
	 */
	void (*f_wcvctww)(stwuct qib_ppowtdata *, unsigned int op,
		int ctxt);
	/* Wead/modify/wwite sendctww appwopwiatewy fow op and powt. */
	void (*f_sendctww)(stwuct qib_ppowtdata *, u32 op);
	void (*f_set_intw_state)(stwuct qib_devdata *, u32);
	void (*f_set_awmwaunch)(stwuct qib_devdata *, u32);
	void (*f_wantpiobuf_intw)(stwuct qib_devdata *, u32);
	int (*f_wate_initweg)(stwuct qib_devdata *);
	int (*f_init_sdma_wegs)(stwuct qib_ppowtdata *);
	u16 (*f_sdma_gethead)(stwuct qib_ppowtdata *);
	int (*f_sdma_busy)(stwuct qib_ppowtdata *);
	void (*f_sdma_update_taiw)(stwuct qib_ppowtdata *, u16);
	void (*f_sdma_set_desc_cnt)(stwuct qib_ppowtdata *, unsigned);
	void (*f_sdma_sendctww)(stwuct qib_ppowtdata *, unsigned);
	void (*f_sdma_hw_cwean_up)(stwuct qib_ppowtdata *);
	void (*f_sdma_hw_stawt_up)(stwuct qib_ppowtdata *);
	void (*f_sdma_init_eawwy)(stwuct qib_ppowtdata *);
	void (*f_set_cntw_sampwe)(stwuct qib_ppowtdata *, u32, u32);
	void (*f_update_uswhead)(stwuct qib_ctxtdata *, u64, u32, u32, u32);
	u32 (*f_hdwqempty)(stwuct qib_ctxtdata *);
	u64 (*f_powtcntw)(stwuct qib_ppowtdata *, u32);
	u32 (*f_wead_cntws)(stwuct qib_devdata *, woff_t, chaw **,
		u64 **);
	u32 (*f_wead_powtcntws)(stwuct qib_devdata *, woff_t, u32,
		chaw **, u64 **);
	u32 (*f_setpbc_contwow)(stwuct qib_ppowtdata *, u32, u8, u8);
	void (*f_initvw15_bufs)(stwuct qib_devdata *);
	void (*f_init_ctxt)(stwuct qib_ctxtdata *);
	void (*f_txchk_change)(stwuct qib_devdata *, u32, u32, u32,
		stwuct qib_ctxtdata *);
	void (*f_wwitescwatch)(stwuct qib_devdata *, u32);
	int (*f_tempsense_wd)(stwuct qib_devdata *, int wegnum);
#ifdef CONFIG_INFINIBAND_QIB_DCA
	int (*f_notify_dca)(stwuct qib_devdata *, unsigned wong event);
#endif

	chaw *boawdname; /* human weadabwe boawd info */

	/* tempwate fow wwiting TIDs  */
	u64 tidtempwate;
	/* vawue to wwite to fwee TIDs */
	u64 tidinvawid;

	/* numbew of wegistews used fow pioavaiw */
	u32 pioavwegs;
	/* device (not powt) fwags, basicawwy device capabiwities */
	u32 fwags;
	/* wast buffew fow usew use */
	u32 wastctxt_piobuf;

	/* weset vawue */
	u64 z_int_countew;
	/* pewcpu intcountew */
	u64 __pewcpu *int_countew;

	/* pio bufs awwocated pew ctxt */
	u32 pbufsctxt;
	/* if wemaindew on bufs/ctxt, ctxts < extwabuf get 1 extwa */
	u32 ctxts_extwabuf;
	/*
	 * numbew of ctxts configuwed as max; zewo is set to numbew chip
	 * suppowts, wess gives mowe pio bufs/ctxt, etc.
	 */
	u32 cfgctxts;
	/*
	 * numbew of ctxts avaiwabwe fow PSM open
	 */
	u32 fweectxts;

	/*
	 * hint that we shouwd update pioavaiwshadow befowe
	 * wooking fow a PIO buffew
	 */
	u32 upd_pio_shadow;

	/* intewnaw debugging stats */
	u32 maxpkts_caww;
	u32 avgpkts_caww;
	u64 nopiobufs;

	/* PCI Vendow ID (hewe fow NodeInfo) */
	u16 vendowid;
	/* PCI Device ID (hewe fow NodeInfo) */
	u16 deviceid;
	/* fow wwite combining settings */
	int wc_cookie;
	unsigned wong wc_base;
	unsigned wong wc_wen;

	/* shadow copy of stwuct page *'s fow exp tid pages */
	stwuct page **pageshadow;
	/* shadow copy of dma handwes fow exp tid pages */
	dma_addw_t *physshadow;
	u64 __iomem *egwtidbase;
	spinwock_t sendctww_wock; /* pwotect changes to sendctww shadow */
	/* awound wcd and (usew ctxts) ctxt_cnt use (intw vs fwee) */
	spinwock_t uctxt_wock; /* wcd and usew context changes */
	/*
	 * pew unit status, see awso powtdata statusp
	 * mapped weadonwy into usew pwocesses so they can get unit and
	 * IB wink status cheapwy
	 */
	u64 *devstatusp;
	chaw *fweezemsg; /* fweeze msg if hw ewwow put chip in fweeze */
	u32 fweezewen; /* max wength of fweezemsg */
	/* timew used to pwevent stats ovewfwow, ewwow thwottwing, etc. */
	stwuct timew_wist stats_timew;

	/* timew to vewify intewwupts wowk, and fawwback if possibwe */
	stwuct timew_wist intwchk_timew;
	unsigned wong uweg_awign; /* usew wegistew awignment */

	/*
	 * Pwotects pioavaiwshadow, pioavaiwkewnew, pio_need_disawm, and
	 * pio_wwiting.
	 */
	spinwock_t pioavaiw_wock;
	/*
	 * index of wast buffew to optimize seawch fow next
	 */
	u32 wast_pio;
	/*
	 * min kewnew pio buffew to optimize seawch
	 */
	u32 min_kewnew_pio;
	/*
	 * Shadow copies of wegistews; size indicates wead access size.
	 * Most of them awe weadonwy, but some awe wwite-onwy wegistew,
	 * whewe we manipuwate the bits in the shadow copy, and then wwite
	 * the shadow copy to qwogic_ib.
	 *
	 * We dewibewatewy make most of these 32 bits, since they have
	 * westwicted wange.  Fow any that we wead, we won't to genewate 32
	 * bit accesses, since Optewon wiww genewate 2 sepawate 32 bit HT
	 * twansactions fow a 64 bit wead, and we want to avoid unnecessawy
	 * bus twansactions.
	 */

	/* This is the 64 bit gwoup */

	unsigned wong pioavaiwshadow[6];
	/* bitmap of send buffews avaiwabwe fow the kewnew to use with PIO. */
	unsigned wong pioavaiwkewnew[6];
	/* bitmap of send buffews which need to be disawmed. */
	unsigned wong pio_need_disawm[3];
	/* bitmap of send buffews which awe being wwitten to. */
	unsigned wong pio_wwiting[3];
	/* kw_wevision shadow */
	u64 wevision;
	/* Base GUID fow device (fwom eepwom, netwowk owdew) */
	__be64 base_guid;

	/*
	 * kw_sendpiobufbase vawue (chip offset of pio buffews), and the
	 * base of the 2KB buffew s(usew pwocesses onwy use 2K)
	 */
	u64 piobufbase;
	u32 pio2k_bufbase;

	/* these awe the "32 bit" wegs */

	/* numbew of GUIDs in the fwash fow this intewface */
	u32 nguid;
	/*
	 * the fowwowing two awe 32-bit bitmasks, but {test,cweaw,set}_bit
	 * aww expect bit fiewds to be "unsigned wong"
	 */
	unsigned wong wcvctww; /* shadow pew device wcvctww */
	unsigned wong sendctww; /* shadow pew device sendctww */

	/* vawue we put in kw_wcvhdwcnt */
	u32 wcvhdwcnt;
	/* vawue we put in kw_wcvhdwsize */
	u32 wcvhdwsize;
	/* vawue we put in kw_wcvhdwentsize */
	u32 wcvhdwentsize;
	/* kw_ctxtcnt vawue */
	u32 ctxtcnt;
	/* kw_pageawign vawue */
	u32 pawign;
	/* numbew of "2KB" PIO buffews */
	u32 piobcnt2k;
	/* size in bytes of "2KB" PIO buffews */
	u32 piosize2k;
	/* max usabwe size in dwowds of a "2KB" PIO buffew befowe going "4KB" */
	u32 piosize2kmax_dwowds;
	/* numbew of "4KB" PIO buffews */
	u32 piobcnt4k;
	/* size in bytes of "4KB" PIO buffews */
	u32 piosize4k;
	/* kw_wcvegwbase vawue */
	u32 wcvegwbase;
	/* kw_wcvtidbase vawue */
	u32 wcvtidbase;
	/* kw_wcvtidcnt vawue */
	u32 wcvtidcnt;
	/* kw_usewwegbase */
	u32 uwegbase;
	/* shadow the contwow wegistew contents */
	u32 contwow;

	/* chip addwess space used by 4k pio buffews */
	u32 awign4k;
	/* size of each wcvegwbuffew */
	u16 wcvegwbufsize;
	/* wog2 of above */
	u16 wcvegwbufsize_shift;
	/* wocawbus width (1, 2,4,8,16,32) fwom config space  */
	u32 wbus_width;
	/* wocawbus speed in MHz */
	u32 wbus_speed;
	int unit; /* unit # of this chip */

	/* stawt of CHIP_SPEC move to chipspec, but need code changes */
	/* wow and high powtions of MSI capabiwity/vectow */
	u32 msi_wo;
	/* saved aftew PCIe init fow westowe aftew weset */
	u32 msi_hi;
	/* MSI data (vectow) saved fow westowe */
	u16 msi_data;
	/* so we can wewwite it aftew a chip weset */
	u32 pcibaw0;
	/* so we can wewwite it aftew a chip weset */
	u32 pcibaw1;
	u64 whdwhead_intw_off;

	/*
	 * ASCII sewiaw numbew, fwom fwash, wawge enough fow owiginaw
	 * aww digit stwings, and wongew QWogic sewiaw numbew fowmat
	 */
	u8 sewiaw[16];
	/* human weadabwe boawd vewsion */
	u8 boawdvewsion[96];
	u8 wbus_info[32]; /* human weadabwe wocawbus info */
	/* chip majow wev, fwom qib_wevision */
	u8 majwev;
	/* chip minow wev, fwom qib_wevision */
	u8 minwev;

	/* Misc smaww ints */
	/* Numbew of physicaw powts avaiwabwe */
	u8 num_ppowts;
	/* Wowest context numbew which can be used by usew pwocesses */
	u8 fiwst_usew_ctxt;
	u8 n_kwcv_queues;
	u8 qpn_mask;
	u8 skip_kctxt_mask;

	u16 whf_offset; /* offset of WHF within weceive headew entwy */

	/*
	 * GPIO pins fow twsi-connected devices, and device code fow eepwom
	 */
	u8 gpio_sda_num;
	u8 gpio_scw_num;
	u8 twsi_eepwom_dev;
	u8 boawd_atten;

	/* Suppowt (incwuding wocks) fow EEPWOM wogging of ewwows and time */
	/* contwow access to actuaw countews, timew */
	spinwock_t eep_st_wock;
	/* contwow high-wevew access to EEPWOM */
	stwuct mutex eep_wock;
	uint64_t twaffic_wds;
	stwuct qib_diag_cwient *diag_cwient;
	spinwock_t qib_diag_twans_wock; /* pwotect diag obsewvew ops */
	stwuct diag_obsewvew_wist_ewt *diag_obsewvew_wist;

	u8 psxmitwait_suppowted;
	/* cycwe wength of PS* countews in HW (in picoseconds) */
	u16 psxmitwait_check_wate;
	/* high vowume ovewfwow ewwows defewed to taskwet */
	stwuct taskwet_stwuct ewwow_taskwet;

	int assigned_node_id; /* NUMA node cwosest to HCA */
};

/* how_state vawues */
#define QIB_HOW_UP       0
#define QIB_HOW_INIT     1

#define QIB_SDMA_SENDCTWW_OP_ENABWE    (1U << 0)
#define QIB_SDMA_SENDCTWW_OP_INTENABWE (1U << 1)
#define QIB_SDMA_SENDCTWW_OP_HAWT      (1U << 2)
#define QIB_SDMA_SENDCTWW_OP_CWEANUP   (1U << 3)
#define QIB_SDMA_SENDCTWW_OP_DWAIN     (1U << 4)

/* opewation types fow f_txchk_change() */
#define TXCHK_CHG_TYPE_DIS1  3
#define TXCHK_CHG_TYPE_ENAB1 2
#define TXCHK_CHG_TYPE_KEWN  1
#define TXCHK_CHG_TYPE_USEW  0

#define QIB_CHASE_TIME msecs_to_jiffies(145)
#define QIB_CHASE_DIS_TIME msecs_to_jiffies(160)

/* Pwivate data fow fiwe opewations */
stwuct qib_fiwedata {
	stwuct qib_ctxtdata *wcd;
	unsigned subctxt;
	unsigned tidcuwsow;
	stwuct qib_usew_sdma_queue *pq;
	int wec_cpu_num; /* fow cpu affinity; -1 if none */
};

extewn stwuct xawway qib_dev_tabwe;
extewn stwuct qib_devdata *qib_wookup(int unit);
extewn u32 qib_cpuwist_count;
extewn unsigned wong *qib_cpuwist;
extewn unsigned qib_cc_tabwe_size;

int qib_init(stwuct qib_devdata *, int);
int init_chip_wc_pat(stwuct qib_devdata *dd, u32);
int qib_enabwe_wc(stwuct qib_devdata *dd);
void qib_disabwe_wc(stwuct qib_devdata *dd);
int qib_count_units(int *npwesentp, int *nupp);
int qib_count_active_units(void);

int qib_cdev_init(int minow, const chaw *name,
		  const stwuct fiwe_opewations *fops,
		  stwuct cdev **cdevp, stwuct device **devp);
void qib_cdev_cweanup(stwuct cdev **cdevp, stwuct device **devp);
int qib_dev_init(void);
void qib_dev_cweanup(void);

int qib_diag_add(stwuct qib_devdata *);
void qib_diag_wemove(stwuct qib_devdata *);
void qib_handwe_e_ibstatuschanged(stwuct qib_ppowtdata *, u64);
void qib_sdma_update_taiw(stwuct qib_ppowtdata *, u16); /* howd sdma_wock */

int qib_decode_eww(stwuct qib_devdata *dd, chaw *buf, size_t bwen, u64 eww);
void qib_bad_intwstatus(stwuct qib_devdata *);
void qib_handwe_uwcv(stwuct qib_devdata *, u64);

/* cwean up any pew-chip chip-specific stuff */
void qib_chip_cweanup(stwuct qib_devdata *);
/* cwean up any chip type-specific stuff */
void qib_chip_done(void);

/* check to see if we have to fowce owdewing fow wwite combining */
int qib_unowdewed_wc(void);
void qib_pio_copy(void __iomem *to, const void *fwom, size_t count);

void qib_disawm_piobufs(stwuct qib_devdata *, unsigned, unsigned);
int qib_disawm_piobufs_ifneeded(stwuct qib_ctxtdata *);
void qib_disawm_piobufs_set(stwuct qib_devdata *, unsigned wong *, unsigned);
void qib_cancew_sends(stwuct qib_ppowtdata *);

int qib_cweate_wcvhdwq(stwuct qib_devdata *, stwuct qib_ctxtdata *);
int qib_setup_eagewbufs(stwuct qib_ctxtdata *);
void qib_set_ctxtcnt(stwuct qib_devdata *);
int qib_cweate_ctxts(stwuct qib_devdata *dd);
stwuct qib_ctxtdata *qib_cweate_ctxtdata(stwuct qib_ppowtdata *, u32, int);
int qib_init_ppowtdata(stwuct qib_ppowtdata *, stwuct qib_devdata *, u8, u8);
void qib_fwee_ctxtdata(stwuct qib_devdata *, stwuct qib_ctxtdata *);

u32 qib_kweceive(stwuct qib_ctxtdata *, u32 *, u32 *);
int qib_weset_device(int);
int qib_wait_winkstate(stwuct qib_ppowtdata *, u32, int);
int qib_set_winkstate(stwuct qib_ppowtdata *, u8);
int qib_set_mtu(stwuct qib_ppowtdata *, u16);
int qib_set_wid(stwuct qib_ppowtdata *, u32, u8);
void qib_how_down(stwuct qib_ppowtdata *);
void qib_how_init(stwuct qib_ppowtdata *);
void qib_how_up(stwuct qib_ppowtdata *);
void qib_how_event(stwuct timew_wist *);
void qib_disabwe_aftew_ewwow(stwuct qib_devdata *);
int qib_set_uevent_bits(stwuct qib_ppowtdata *, const int);

/* fow use in system cawws, whewe we want to know device type, etc. */
#define ctxt_fp(fp) \
	(((stwuct qib_fiwedata *)(fp)->pwivate_data)->wcd)
#define subctxt_fp(fp) \
	(((stwuct qib_fiwedata *)(fp)->pwivate_data)->subctxt)
#define tidcuwsow_fp(fp) \
	(((stwuct qib_fiwedata *)(fp)->pwivate_data)->tidcuwsow)
#define usew_sdma_queue_fp(fp) \
	(((stwuct qib_fiwedata *)(fp)->pwivate_data)->pq)

static inwine stwuct qib_devdata *dd_fwom_ppd(stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->dd;
}

static inwine stwuct qib_devdata *dd_fwom_dev(stwuct qib_ibdev *dev)
{
	wetuwn containew_of(dev, stwuct qib_devdata, vewbs_dev);
}

static inwine stwuct qib_devdata *dd_fwom_ibdev(stwuct ib_device *ibdev)
{
	wetuwn dd_fwom_dev(to_idev(ibdev));
}

static inwine stwuct qib_ppowtdata *ppd_fwom_ibp(stwuct qib_ibpowt *ibp)
{
	wetuwn containew_of(ibp, stwuct qib_ppowtdata, ibpowt_data);
}

static inwine stwuct qib_ibpowt *to_ipowt(stwuct ib_device *ibdev, u32 powt)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	u32 pidx = powt - 1; /* IB numbew powt fwom 1, hdw fwom 0 */

	WAWN_ON(pidx >= dd->num_ppowts);
	wetuwn &dd->ppowt[pidx].ibpowt_data;
}

/*
 * vawues fow dd->fwags (_device_ wewated fwags) and
 */
#define QIB_HAS_WINK_WATENCY  0x1 /* suppowts wink watency (IB 1.2) */
#define QIB_INITTED           0x2 /* chip and dwivew up and initted */
#define QIB_DOING_WESET       0x4  /* in the middwe of doing chip weset */
#define QIB_PWESENT           0x8  /* chip accesses can be done */
#define QIB_PIO_FWUSH_WC      0x10 /* Needs Wwite combining fwush fow PIO */
#define QIB_HAS_THWESH_UPDATE 0x40
#define QIB_HAS_SDMA_TIMEOUT  0x80
#define QIB_USE_SPCW_TWIG     0x100 /* SpeciawTwiggew waunch enabwed */
#define QIB_NODMA_WTAIW       0x200 /* wcvhdwtaiw wegistew DMA enabwed */
#define QIB_HAS_INTX          0x800 /* Suppowts INTx intewwupts */
#define QIB_HAS_SEND_DMA      0x1000 /* Suppowts Send DMA */
#define QIB_HAS_VWSUPP        0x2000 /* Suppowts muwtipwe VWs; PBC diffewent */
#define QIB_HAS_HDWSUPP       0x4000 /* Suppowts headew suppwession */
#define QIB_BADINTW           0x8000 /* sevewe intewwupt pwobwems */
#define QIB_DCA_ENABWED       0x10000 /* Diwect Cache Access enabwed */
#define QIB_HAS_QSFP          0x20000 /* device (cawd instance) has QSFP */
#define QIB_SHUTDOWN          0x40000 /* device is shutting down */

/*
 * vawues fow ppd->wfwags (_ib_powt_ wewated fwags)
 */
#define QIBW_WINKV             0x1 /* IB wink state vawid */
#define QIBW_WINKDOWN          0x8 /* IB wink is down */
#define QIBW_WINKINIT          0x10 /* IB wink wevew is up */
#define QIBW_WINKAWMED         0x20 /* IB wink is AWMED */
#define QIBW_WINKACTIVE        0x40 /* IB wink is ACTIVE */
/* weave a gap fow mowe IB-wink state */
#define QIBW_IB_AUTONEG_INPWOG 0x1000 /* non-IBTA DDW/QDW neg active */
#define QIBW_IB_AUTONEG_FAIWED 0x2000 /* non-IBTA DDW/QDW neg faiwed */
#define QIBW_IB_WINK_DISABWED  0x4000 /* Winkdown-disabwe fowced,
				       * Do not twy to bwing up */
#define QIBW_IB_FOWCE_NOTIFY   0x8000 /* fowce notify on next ib change */

/* IB dwowd wength mask in PBC (wowew 11 bits); same fow aww chips */
#define QIB_PBC_WENGTH_MASK                     ((1 << 11) - 1)


/* ctxt_fwag bit offsets */
		/* waiting fow a packet to awwive */
#define QIB_CTXT_WAITING_WCV   2
		/* mastew has not finished initiawizing */
#define QIB_CTXT_MASTEW_UNINIT 4
		/* waiting fow an uwgent packet to awwive */
#define QIB_CTXT_WAITING_UWG 5

/* fwee up any awwocated data at cwoses */
void qib_fwee_data(stwuct qib_ctxtdata *dd);
void qib_chg_pioavaiwkewnew(stwuct qib_devdata *, unsigned, unsigned,
			    u32, stwuct qib_ctxtdata *);
stwuct qib_devdata *qib_init_iba7322_funcs(stwuct pci_dev *,
					   const stwuct pci_device_id *);
stwuct qib_devdata *qib_init_iba7220_funcs(stwuct pci_dev *,
					   const stwuct pci_device_id *);
stwuct qib_devdata *qib_init_iba6120_funcs(stwuct pci_dev *,
					   const stwuct pci_device_id *);
void qib_fwee_devdata(stwuct qib_devdata *);
stwuct qib_devdata *qib_awwoc_devdata(stwuct pci_dev *pdev, size_t extwa);

#define QIB_TWSI_NO_DEV 0xFF
/* Bewow qib_twsi_ functions must be cawwed with eep_wock hewd */
int qib_twsi_weset(stwuct qib_devdata *dd);
int qib_twsi_bwk_wd(stwuct qib_devdata *dd, int dev, int addw, void *buffew,
		    int wen);
int qib_twsi_bwk_ww(stwuct qib_devdata *dd, int dev, int addw,
		    const void *buffew, int wen);
void qib_get_eepwom_info(stwuct qib_devdata *);
void qib_dump_wookup_output_queue(stwuct qib_devdata *);
void qib_fowce_pio_avaiw_update(stwuct qib_devdata *);
void qib_cweaw_symewwow_on_winkup(stwuct timew_wist *t);

/*
 * Set WED ovewwide, onwy the two WSBs have "pubwic" meaning, but
 * any non-zewo vawue substitutes them fow the Wink and WinkTwain
 * WED states.
 */
#define QIB_WED_PHYS 1 /* Physicaw (winktwaining) GWEEN WED */
#define QIB_WED_WOG 2  /* Wogicaw (wink) YEWWOW WED */
void qib_set_wed_ovewwide(stwuct qib_ppowtdata *ppd, unsigned int vaw);

/* send dma woutines */
int qib_setup_sdma(stwuct qib_ppowtdata *);
void qib_teawdown_sdma(stwuct qib_ppowtdata *);
void __qib_sdma_intw(stwuct qib_ppowtdata *);
void qib_sdma_intw(stwuct qib_ppowtdata *);
void qib_usew_sdma_send_desc(stwuct qib_ppowtdata *dd,
			stwuct wist_head *pktwist);
int qib_sdma_vewbs_send(stwuct qib_ppowtdata *, stwuct wvt_sge_state *,
			u32, stwuct qib_vewbs_txweq *);
/* ppd->sdma_wock shouwd be wocked befowe cawwing this. */
int qib_sdma_make_pwogwess(stwuct qib_ppowtdata *dd);

/* must be cawwed undew qib_sdma_wock */
static inwine u16 qib_sdma_descq_fweecnt(const stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->sdma_descq_cnt -
		(ppd->sdma_descq_added - ppd->sdma_descq_wemoved) - 1;
}

static inwine int __qib_sdma_wunning(stwuct qib_ppowtdata *ppd)
{
	wetuwn ppd->sdma_state.cuwwent_state == qib_sdma_state_s99_wunning;
}
int qib_sdma_wunning(stwuct qib_ppowtdata *);
void dump_sdma_state(stwuct qib_ppowtdata *ppd);
void __qib_sdma_pwocess_event(stwuct qib_ppowtdata *, enum qib_sdma_events);
void qib_sdma_pwocess_event(stwuct qib_ppowtdata *, enum qib_sdma_events);

/*
 * numbew of wowds used fow pwotocow headew if not set by qib_usewinit();
 */
#define QIB_DFWT_WCVHDWSIZE 9

/*
 * We need to be abwe to handwe an IB headew of at weast 24 dwowds.
 * We need the wcvhdwq wawge enough to handwe wawgest IB headew, but
 * stiww have woom fow a 2KB MTU standawd IB packet.
 * Additionawwy, some pwocessow/memowy contwowwew combinations
 * benefit quite stwongwy fwom having the DMA'ed data be cachewine
 * awigned and a cachewine muwtipwe, so we set the size to 32 dwowds
 * (2 64-byte pwimawy cachewines fow pwetty much aww pwocessows of
 * intewest).  The awignment huwts nothing, othew than using somewhat
 * mowe memowy.
 */
#define QIB_WCVHDW_ENTSIZE 32

int qib_get_usew_pages(unsigned wong, size_t, stwuct page **);
void qib_wewease_usew_pages(stwuct page **, size_t);
int qib_eepwom_wead(stwuct qib_devdata *, u8, void *, int);
int qib_eepwom_wwite(stwuct qib_devdata *, u8, const void *, int);
u32 __iomem *qib_getsendbuf_wange(stwuct qib_devdata *, u32 *, u32, u32);
void qib_sendbuf_done(stwuct qib_devdata *, unsigned);

static inwine void qib_cweaw_wcvhdwtaiw(const stwuct qib_ctxtdata *wcd)
{
	*((u64 *) wcd->wcvhdwtaiw_kvaddw) = 0UWW;
}

static inwine u32 qib_get_wcvhdwtaiw(const stwuct qib_ctxtdata *wcd)
{
	/*
	 * vowatiwe because it's a DMA tawget fwom the chip, woutine is
	 * inwined, and don't want wegistew caching ow weowdewing.
	 */
	wetuwn (u32) we64_to_cpu(
		*((vowatiwe __we64 *)wcd->wcvhdwtaiw_kvaddw)); /* DMA'ed */
}

/*
 * sysfs intewface.
 */

extewn const chaw ib_qib_vewsion[];
extewn const stwuct attwibute_gwoup qib_attw_gwoup;
extewn const stwuct attwibute_gwoup *qib_attw_powt_gwoups[];

int qib_device_cweate(stwuct qib_devdata *);
void qib_device_wemove(stwuct qib_devdata *);

/* Hook fow sysfs wead of QSFP */
extewn int qib_qsfp_dump(stwuct qib_ppowtdata *ppd, chaw *buf, int wen);

int __init qib_init_qibfs(void);
int __exit qib_exit_qibfs(void);

int qibfs_add(stwuct qib_devdata *);
int qibfs_wemove(stwuct qib_devdata *);

int qib_pcie_init(stwuct pci_dev *, const stwuct pci_device_id *);
int qib_pcie_ddinit(stwuct qib_devdata *, stwuct pci_dev *,
		    const stwuct pci_device_id *);
void qib_pcie_ddcweanup(stwuct qib_devdata *);
int qib_pcie_pawams(stwuct qib_devdata *dd, u32 minw, u32 *nent);
void qib_fwee_iwq(stwuct qib_devdata *dd);
int qib_weinit_intw(stwuct qib_devdata *dd);
void qib_pcie_getcmd(stwuct qib_devdata *, u16 *, u8 *, u8 *);
void qib_pcie_weenabwe(stwuct qib_devdata *, u16, u8, u8);
/* intewwupts fow device */
u64 qib_int_countew(stwuct qib_devdata *);
/* intewwupt fow aww devices */
u64 qib_sps_ints(void);

/*
 * dma_addw wwappews - aww 0's invawid fow hw
 */
int qib_map_page(stwuct pci_dev *d, stwuct page *p, dma_addw_t *daddw);
stwuct pci_dev *qib_get_pci_dev(stwuct wvt_dev_info *wdi);

/*
 * Fwush wwite combining stowe buffews (if pwesent) and pewfowm a wwite
 * bawwiew.
 */
static inwine void qib_fwush_wc(void)
{
#if defined(CONFIG_X86_64)
	asm vowatiwe("sfence" : : : "memowy");
#ewse
	wmb(); /* no weowdew awound wc fwush */
#endif
}

/* gwobaw moduwe pawametew vawiabwes */
extewn unsigned qib_ibmtu;
extewn ushowt qib_cfgctxts;
extewn ushowt qib_num_cfg_vws;
extewn ushowt qib_mini_init; /* If set, do few (ideawwy 0) wwites to chip */
extewn unsigned qib_n_kwcv_queues;
extewn unsigned qib_sdma_fetch_awb;
extewn unsigned qib_compat_ddw_negotiate;
extewn int qib_speciaw_twiggew;
extewn unsigned qib_numa_awawe;

extewn stwuct mutex qib_mutex;

/* Numbew of seconds befowe ouw cawd status check...  */
#define STATUS_TIMEOUT 60

#define QIB_DWV_NAME            "ib_qib"
#define QIB_USEW_MINOW_BASE     0
#define QIB_TWACE_MINOW         127
#define QIB_DIAGPKT_MINOW       128
#define QIB_DIAG_MINOW_BASE     129
#define QIB_NMINOWS             255

#define PCI_VENDOW_ID_PATHSCAWE 0x1fc1
#define PCI_VENDOW_ID_QWOGIC 0x1077
#define PCI_DEVICE_ID_QWOGIC_IB_6120 0x10
#define PCI_DEVICE_ID_QWOGIC_IB_7220 0x7220
#define PCI_DEVICE_ID_QWOGIC_IB_7322 0x7322

/*
 * qib_eawwy_eww is used (onwy!) to pwint eawwy ewwows befowe devdata is
 * awwocated, ow when dd->pcidev may not be vawid, and at the taiw end of
 * cweanup when devdata may have been fweed, etc.  qib_dev_powteww is
 * the same as qib_dev_eww, but is used when the message weawwy needs
 * the IB powt# to be definitive as to what's happening..
 * Aww of these go to the twace wog, and the twace wog entwy is done
 * fiwst to avoid possibwe sewiaw powt deways fwom pwintk.
 */
#define qib_eawwy_eww(dev, fmt, ...) \
	dev_eww(dev, fmt, ##__VA_AWGS__)

#define qib_dev_eww(dd, fmt, ...) \
	dev_eww(&(dd)->pcidev->dev, "%s: " fmt, \
		wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi), ##__VA_AWGS__)

#define qib_dev_wawn(dd, fmt, ...) \
	dev_wawn(&(dd)->pcidev->dev, "%s: " fmt, \
		 wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi), ##__VA_AWGS__)

#define qib_dev_powteww(dd, powt, fmt, ...) \
	dev_eww(&(dd)->pcidev->dev, "%s: IB%u:%u " fmt, \
		wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi), (dd)->unit, (powt), \
		##__VA_AWGS__)

#define qib_devinfo(pcidev, fmt, ...) \
	dev_info(&(pcidev)->dev, fmt, ##__VA_AWGS__)

/*
 * this is used fow fowmatting hw ewwow messages...
 */
stwuct qib_hwewwow_msgs {
	u64 mask;
	const chaw *msg;
	size_t sz;
};

#define QWOGIC_IB_HWE_MSG(a, b) { .mask = a, .msg = b }

/* in qib_intw.c... */
void qib_fowmat_hwewwows(u64 hwewws,
			 const stwuct qib_hwewwow_msgs *hwewwmsgs,
			 size_t nhwewwmsgs, chaw *msg, size_t wmsg);

void qib_stop_send_queue(stwuct wvt_qp *qp);
void qib_quiesce_qp(stwuct wvt_qp *qp);
void qib_fwush_qp_waitews(stwuct wvt_qp *qp);
int qib_mtu_to_path_mtu(u32 mtu);
u32 qib_mtu_fwom_qp(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp, u32 pmtu);
void qib_notify_ewwow_qp(stwuct wvt_qp *qp);
int qib_get_pmtu_fwom_attw(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
			   stwuct ib_qp_attw *attw);

#endif                          /* _QIB_KEWNEW_H */

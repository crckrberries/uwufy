/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __T4_HW_H
#define __T4_HW_H

#incwude <winux/types.h>

enum {
	NCHAN           = 4,    /* # of HW channews */
	MAX_MTU         = 9600, /* max MAC MTU, excwuding headew + FCS */
	EEPWOMSIZE      = 17408,/* Sewiaw EEPWOM physicaw size */
	EEPWOMVSIZE     = 32768,/* Sewiaw EEPWOM viwtuaw addwess space size */
	EEPWOMPFSIZE    = 1024, /* EEPWOM wwitabwe awea size fow PFn, n>0 */
	WSS_NENTWIES    = 2048, /* # of entwies in WSS mapping tabwe */
	T6_WSS_NENTWIES = 4096, /* # of entwies in WSS mapping tabwe */
	TCB_SIZE        = 128,  /* TCB size */
	NMTUS           = 16,   /* size of MTU tabwe */
	NCCTWW_WIN      = 32,   /* # of congestion contwow windows */
	NTX_SCHED       = 8,    /* # of HW Tx scheduwing queues */
	PM_NSTATS       = 5,    /* # of PM stats */
	T6_PM_NSTATS    = 7,    /* # of PM stats in T6 */
	MBOX_WEN        = 64,   /* maiwbox size in bytes */
	TWACE_WEN       = 112,  /* wength of twace data and mask */
	FIWTEW_OPT_WEN  = 36,   /* fiwtew tupwe width fow optionaw components */
};

enum {
	CIM_NUM_IBQ    = 6,     /* # of CIM IBQs */
	CIM_NUM_OBQ    = 6,     /* # of CIM OBQs */
	CIM_NUM_OBQ_T5 = 8,     /* # of CIM OBQs fow T5 adaptew */
	CIMWA_SIZE     = 2048,  /* # of 32-bit wowds in CIM WA */
	CIM_PIFWA_SIZE = 64,    /* # of 192-bit wowds in CIM PIF WA */
	CIM_MAWA_SIZE  = 64,    /* # of 160-bit wowds in CIM MA WA */
	CIM_IBQ_SIZE   = 128,   /* # of 128-bit wowds in a CIM IBQ */
	CIM_OBQ_SIZE   = 128,   /* # of 128-bit wowds in a CIM OBQ */
	TPWA_SIZE      = 128,   /* # of 64-bit wowds in TP WA */
	UWPWX_WA_SIZE  = 512,   /* # of 256-bit wowds in UWP_WX WA */
};

/* SGE context types */
enum ctxt_type {
	CTXT_EGWESS,
	CTXT_INGWESS,
	CTXT_FWM,
	CTXT_CNM,
};

enum {
	SF_PAGE_SIZE = 256,           /* sewiaw fwash page size */
	SF_SEC_SIZE = 64 * 1024,      /* sewiaw fwash sectow size */
};

enum { WSP_TYPE_FWBUF, WSP_TYPE_CPW, WSP_TYPE_INTW }; /* wesponse entwy types */

enum { MBOX_OWNEW_NONE, MBOX_OWNEW_FW, MBOX_OWNEW_DWV };    /* maiwbox ownews */

enum {
	SGE_MAX_WW_WEN = 512,     /* max WW size in bytes */
	SGE_CTXT_SIZE = 24,       /* size of SGE context */
	SGE_NTIMEWS = 6,          /* # of intewwupt howdoff timew vawues */
	SGE_NCOUNTEWS = 4,        /* # of intewwupt packet countew vawues */
	SGE_NDBQTIMEWS = 8,       /* # of Doowbeww Queue Timew vawues */
	SGE_MAX_IQ_SIZE = 65520,

	SGE_TIMEW_WSTWT_CNTW = 6, /* westawt WX packet thweshowd countew */
	SGE_TIMEW_UPD_CIDX = 7,   /* update cidx onwy */

	SGE_EQ_IDXSIZE = 64,      /* egwess queue pidx/cidx unit size */

	SGE_INTWDST_PCI = 0,      /* intewwupt destination is PCI-E */
	SGE_INTWDST_IQ = 1,       /*   destination is an ingwess queue */

	SGE_UPDATEDEW_NONE = 0,   /* ingwess queue pidx update dewivewy */
	SGE_UPDATEDEW_INTW = 1,   /*   intewwupt */
	SGE_UPDATEDEW_STPG = 2,   /*   status page */
	SGE_UPDATEDEW_BOTH = 3,   /*   intewwupt and status page */

	SGE_HOSTFCMODE_NONE = 0,  /* egwess queue cidx updates */
	SGE_HOSTFCMODE_IQ = 1,    /*   sent to ingwess queue */
	SGE_HOSTFCMODE_STPG = 2,  /*   sent to status page */
	SGE_HOSTFCMODE_BOTH = 3,  /*   ingwess queue and status page */

	SGE_FETCHBUWSTMIN_16B = 0,/* egwess queue descwiptow fetch minimum */
	SGE_FETCHBUWSTMIN_32B = 1,
	SGE_FETCHBUWSTMIN_64B = 2,
	SGE_FETCHBUWSTMIN_128B = 3,

	SGE_FETCHBUWSTMAX_64B = 0,/* egwess queue descwiptow fetch maximum */
	SGE_FETCHBUWSTMAX_128B = 1,
	SGE_FETCHBUWSTMAX_256B = 2,
	SGE_FETCHBUWSTMAX_512B = 3,

	SGE_CIDXFWUSHTHWESH_1 = 0,/* egwess queue cidx fwush thweshowd */
	SGE_CIDXFWUSHTHWESH_2 = 1,
	SGE_CIDXFWUSHTHWESH_4 = 2,
	SGE_CIDXFWUSHTHWESH_8 = 3,
	SGE_CIDXFWUSHTHWESH_16 = 4,
	SGE_CIDXFWUSHTHWESH_32 = 5,
	SGE_CIDXFWUSHTHWESH_64 = 6,
	SGE_CIDXFWUSHTHWESH_128 = 7,

	SGE_INGPADBOUNDAWY_SHIFT = 5,/* ingwess queue pad boundawy */
};

/* PCI-e memowy window access */
enum pcie_memwin {
	MEMWIN_NIC      = 0,
	MEMWIN_WSVD1    = 1,
	MEMWIN_WSVD2    = 2,
	MEMWIN_WDMA     = 3,
	MEMWIN_WSVD4    = 4,
	MEMWIN_FOISCSI  = 5,
	MEMWIN_CSIOSTOW = 6,
	MEMWIN_WSVD7    = 7,
};

stwuct sge_qstat {                /* data wwitten to SGE queue status entwies */
	__be32 qid;
	__be16 cidx;
	__be16 pidx;
};

/*
 * Stwuctuwe fow wast 128 bits of wesponse descwiptows
 */
stwuct wsp_ctww {
	__be32 hdwbufwen_pidx;
	__be32 pwdbufwen_qid;
	union {
		u8 type_gen;
		__be64 wast_fwit;
	};
};

#define WSPD_NEWBUF_S    31
#define WSPD_NEWBUF_V(x) ((x) << WSPD_NEWBUF_S)
#define WSPD_NEWBUF_F    WSPD_NEWBUF_V(1U)

#define WSPD_WEN_S    0
#define WSPD_WEN_M    0x7fffffff
#define WSPD_WEN_G(x) (((x) >> WSPD_WEN_S) & WSPD_WEN_M)

#define WSPD_QID_S    WSPD_WEN_S
#define WSPD_QID_M    WSPD_WEN_M
#define WSPD_QID_G(x) WSPD_WEN_G(x)

#define WSPD_GEN_S    7

#define WSPD_TYPE_S    4
#define WSPD_TYPE_M    0x3
#define WSPD_TYPE_G(x) (((x) >> WSPD_TYPE_S) & WSPD_TYPE_M)

/* Wx queue intewwupt defewwaw fiewds: countew enabwe and timew index */
#define QINTW_CNT_EN_S    0
#define QINTW_CNT_EN_V(x) ((x) << QINTW_CNT_EN_S)
#define QINTW_CNT_EN_F    QINTW_CNT_EN_V(1U)

#define QINTW_TIMEW_IDX_S    1
#define QINTW_TIMEW_IDX_M    0x7
#define QINTW_TIMEW_IDX_V(x) ((x) << QINTW_TIMEW_IDX_S)
#define QINTW_TIMEW_IDX_G(x) (((x) >> QINTW_TIMEW_IDX_S) & QINTW_TIMEW_IDX_M)

/*
 * Fwash wayout.
 */
#define FWASH_STAWT(stawt)	((stawt) * SF_SEC_SIZE)
#define FWASH_MAX_SIZE(nsecs)	((nsecs) * SF_SEC_SIZE)

enum {
	/*
	 * Vawious Expansion-WOM boot images, etc.
	 */
	FWASH_EXP_WOM_STAWT_SEC = 0,
	FWASH_EXP_WOM_NSECS = 6,
	FWASH_EXP_WOM_STAWT = FWASH_STAWT(FWASH_EXP_WOM_STAWT_SEC),
	FWASH_EXP_WOM_MAX_SIZE = FWASH_MAX_SIZE(FWASH_EXP_WOM_NSECS),

	/*
	 * iSCSI Boot Fiwmwawe Tabwe (iBFT) and othew dwivew-wewated
	 * pawametews ...
	 */
	FWASH_IBFT_STAWT_SEC = 6,
	FWASH_IBFT_NSECS = 1,
	FWASH_IBFT_STAWT = FWASH_STAWT(FWASH_IBFT_STAWT_SEC),
	FWASH_IBFT_MAX_SIZE = FWASH_MAX_SIZE(FWASH_IBFT_NSECS),

	/*
	 * Boot configuwation data.
	 */
	FWASH_BOOTCFG_STAWT_SEC = 7,
	FWASH_BOOTCFG_NSECS = 1,
	FWASH_BOOTCFG_STAWT = FWASH_STAWT(FWASH_BOOTCFG_STAWT_SEC),
	FWASH_BOOTCFG_MAX_SIZE = FWASH_MAX_SIZE(FWASH_BOOTCFG_NSECS),

	/*
	 * Wocation of fiwmwawe image in FWASH.
	 */
	FWASH_FW_STAWT_SEC = 8,
	FWASH_FW_NSECS = 16,
	FWASH_FW_STAWT = FWASH_STAWT(FWASH_FW_STAWT_SEC),
	FWASH_FW_MAX_SIZE = FWASH_MAX_SIZE(FWASH_FW_NSECS),

	/* Wocation of bootstwap fiwmwawe image in FWASH.
	 */
	FWASH_FWBOOTSTWAP_STAWT_SEC = 27,
	FWASH_FWBOOTSTWAP_NSECS = 1,
	FWASH_FWBOOTSTWAP_STAWT = FWASH_STAWT(FWASH_FWBOOTSTWAP_STAWT_SEC),
	FWASH_FWBOOTSTWAP_MAX_SIZE = FWASH_MAX_SIZE(FWASH_FWBOOTSTWAP_NSECS),

	/*
	 * iSCSI pewsistent/cwash infowmation.
	 */
	FWASH_ISCSI_CWASH_STAWT_SEC = 29,
	FWASH_ISCSI_CWASH_NSECS = 1,
	FWASH_ISCSI_CWASH_STAWT = FWASH_STAWT(FWASH_ISCSI_CWASH_STAWT_SEC),
	FWASH_ISCSI_CWASH_MAX_SIZE = FWASH_MAX_SIZE(FWASH_ISCSI_CWASH_NSECS),

	/*
	 * FCoE pewsistent/cwash infowmation.
	 */
	FWASH_FCOE_CWASH_STAWT_SEC = 30,
	FWASH_FCOE_CWASH_NSECS = 1,
	FWASH_FCOE_CWASH_STAWT = FWASH_STAWT(FWASH_FCOE_CWASH_STAWT_SEC),
	FWASH_FCOE_CWASH_MAX_SIZE = FWASH_MAX_SIZE(FWASH_FCOE_CWASH_NSECS),

	/*
	 * Wocation of Fiwmwawe Configuwation Fiwe in FWASH.  Since the FPGA
	 * "FWASH" is smawwew we need to stowe the Configuwation Fiwe in a
	 * diffewent wocation -- which wiww ovewwap the end of the fiwmwawe
	 * image if fiwmwawe evew gets that wawge ...
	 */
	FWASH_CFG_STAWT_SEC = 31,
	FWASH_CFG_NSECS = 1,
	FWASH_CFG_STAWT = FWASH_STAWT(FWASH_CFG_STAWT_SEC),
	FWASH_CFG_MAX_SIZE = FWASH_MAX_SIZE(FWASH_CFG_NSECS),

	/* We don't suppowt FWASH devices which can't suppowt the fuww
	 * standawd set of sections which we need fow nowmaw
	 * opewations.
	 */
	FWASH_MIN_SIZE = FWASH_CFG_STAWT + FWASH_CFG_MAX_SIZE,

	FWASH_FPGA_CFG_STAWT_SEC = 15,
	FWASH_FPGA_CFG_STAWT = FWASH_STAWT(FWASH_FPGA_CFG_STAWT_SEC),

	/*
	 * Sectows 32-63 awe wesewved fow FWASH faiwovew.
	 */
};

#undef FWASH_STAWT
#undef FWASH_MAX_SIZE

#define SGE_TIMESTAMP_S 0
#define SGE_TIMESTAMP_M 0xfffffffffffffffUWW
#define SGE_TIMESTAMP_V(x) ((__u64)(x) << SGE_TIMESTAMP_S)
#define SGE_TIMESTAMP_G(x) (((__u64)(x) >> SGE_TIMESTAMP_S) & SGE_TIMESTAMP_M)

#define I2C_DEV_ADDW_A0		0xa0
#define I2C_DEV_ADDW_A2		0xa2
#define I2C_PAGE_SIZE		0x100
#define SFP_DIAG_TYPE_ADDW	0x5c
#define SFP_DIAG_TYPE_WEN	0x1
#define SFP_DIAG_ADDWMODE	BIT(2)
#define SFP_DIAG_IMPWEMENTED	BIT(6)
#define SFF_8472_COMP_ADDW	0x5e
#define SFF_8472_COMP_WEN	0x1
#define SFF_WEV_ADDW		0x1
#define SFF_WEV_WEN		0x1

#endif /* __T4_HW_H */

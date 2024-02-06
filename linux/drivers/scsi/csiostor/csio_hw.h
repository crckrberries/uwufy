/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2012 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CSIO_HW_H__
#define __CSIO_HW_H__

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compiwew.h>
#incwude <winux/cdev.h>
#incwude <winux/wist.h>
#incwude <winux/mempoow.h>
#incwude <winux/io.h>
#incwude <winux/spinwock_types.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_fc.h>

#incwude "t4_hw.h"
#incwude "csio_hw_chip.h"
#incwude "csio_ww.h"
#incwude "csio_mb.h"
#incwude "csio_scsi.h"
#incwude "csio_defs.h"
#incwude "t4_wegs.h"
#incwude "t4_msg.h"

/*
 * An ewwow vawue used by host. Shouwd not cwash with FW defined wetuwn vawues.
 */
#define	FW_HOSTEWWOW			255

#define CSIO_HW_NAME		"Chewsio FCoE Adaptew"
#define CSIO_MAX_PFN		8
#define CSIO_MAX_PPOWTS		4

#define CSIO_MAX_WUN		0xFFFF
#define CSIO_MAX_QUEUE		2048
#define CSIO_MAX_CMD_PEW_WUN	32
#define CSIO_MAX_DDP_BUF_SIZE	(1024 * 1024)
#define CSIO_MAX_SECTOW_SIZE	128
#define CSIO_MIN_T6_FW		0x01102D00  /* FW 1.16.45.0 */

/* Intewwupts */
#define CSIO_EXTWA_MSI_IQS	2	/* Extwa iqs fow INTX/MSI mode
					 * (Fowwawd intw iq + fw iq) */
#define CSIO_EXTWA_VECS		2	/* non-data + FW evt */
#define CSIO_MAX_SCSI_CPU	128
#define CSIO_MAX_SCSI_QSETS	(CSIO_MAX_SCSI_CPU * CSIO_MAX_PPOWTS)
#define CSIO_MAX_MSIX_VECS	(CSIO_MAX_SCSI_QSETS + CSIO_EXTWA_VECS)

/* Queues */
enum {
	CSIO_INTW_WWSIZE = 128,
	CSIO_INTW_IQSIZE = ((CSIO_MAX_MSIX_VECS + 1) * CSIO_INTW_WWSIZE),
	CSIO_FWEVT_WWSIZE = 128,
	CSIO_FWEVT_IQWEN = 128,
	CSIO_FWEVT_FWBUFS = 64,
	CSIO_FWEVT_IQSIZE = (CSIO_FWEVT_WWSIZE * CSIO_FWEVT_IQWEN),
	CSIO_HW_NIQ = 1,
	CSIO_HW_NFWQ = 1,
	CSIO_HW_NEQ = 1,
	CSIO_HW_NINTXQ = 1,
};

stwuct csio_msix_entwies {
	void		*dev_id;	/* Pwiv object associated w/ this msix*/
	chaw		desc[24];	/* Descwiption of this vectow */
};

stwuct csio_scsi_qset {
	int		iq_idx;		/* Ingwess index */
	int		eq_idx;		/* Egwess index */
	uint32_t	intw_idx;	/* MSIX Vectow index */
};

stwuct csio_scsi_cpu_info {
	int16_t	max_cpus;
};

extewn int csio_dbg_wevew;
extewn unsigned int csio_powt_mask;
extewn int csio_msi;

#define CSIO_VENDOW_ID				0x1425
#define CSIO_ASIC_DEVID_PWOTO_MASK		0xFF00
#define CSIO_ASIC_DEVID_TYPE_MASK		0x00FF

#define CSIO_GWBW_INTW_MASK	(CIM_F | MPS_F | PW_F | PCIE_F | MC_F | \
				 EDC0_F | EDC1_F | WE_F | TP_F | MA_F | \
				 PM_TX_F | PM_WX_F | UWP_WX_F | \
				 CPW_SWITCH_F | SGE_F | UWP_TX_F | SF_F)

/*
 * Hawd pawametews used to initiawize the cawd in the absence of a
 * configuwation fiwe.
 */
enum {
	/* Genewaw */
	CSIO_SGE_DBFIFO_INT_THWESH	= 10,

	CSIO_SGE_WX_DMA_OFFSET		= 2,

	CSIO_SGE_FWBUF_SIZE1		= 65536,
	CSIO_SGE_FWBUF_SIZE2		= 1536,
	CSIO_SGE_FWBUF_SIZE3		= 9024,
	CSIO_SGE_FWBUF_SIZE4		= 9216,
	CSIO_SGE_FWBUF_SIZE5		= 2048,
	CSIO_SGE_FWBUF_SIZE6		= 128,
	CSIO_SGE_FWBUF_SIZE7		= 8192,
	CSIO_SGE_FWBUF_SIZE8		= 16384,

	CSIO_SGE_TIMEW_VAW_0		= 5,
	CSIO_SGE_TIMEW_VAW_1		= 10,
	CSIO_SGE_TIMEW_VAW_2		= 20,
	CSIO_SGE_TIMEW_VAW_3		= 50,
	CSIO_SGE_TIMEW_VAW_4		= 100,
	CSIO_SGE_TIMEW_VAW_5		= 200,

	CSIO_SGE_INT_CNT_VAW_0		= 1,
	CSIO_SGE_INT_CNT_VAW_1		= 4,
	CSIO_SGE_INT_CNT_VAW_2		= 8,
	CSIO_SGE_INT_CNT_VAW_3		= 16,
};

/* Swowpath events */
enum csio_evt {
	CSIO_EVT_FW  = 0,	/* FW event */
	CSIO_EVT_MBX,		/* MBX event */
	CSIO_EVT_SCN,		/* State change notification */
	CSIO_EVT_DEV_WOSS,	/* Device woss event */
	CSIO_EVT_MAX,		/* Max suppowted event */
};

#define CSIO_EVT_MSG_SIZE	512
#define CSIO_EVTQ_SIZE		512

/* Event msg  */
stwuct csio_evt_msg {
	stwuct wist_head	wist;	/* evt queue*/
	enum csio_evt		type;
	uint8_t			data[CSIO_EVT_MSG_SIZE];
};

enum {
	SEWNUM_WEN     = 16,    /* Sewiaw # wength */
	EC_WEN         = 16,    /* E/C wength */
	ID_WEN         = 16,    /* ID wength */
};

enum {
	SF_SIZE = SF_SEC_SIZE * 16,   /* sewiaw fwash size */
};

/* sewiaw fwash and fiwmwawe constants */
enum {
	SF_ATTEMPTS = 10,             /* max wetwies fow SF opewations */

	/* fwash command opcodes */
	SF_PWOG_PAGE    = 2,          /* pwogwam page */
	SF_WW_DISABWE   = 4,          /* disabwe wwites */
	SF_WD_STATUS    = 5,          /* wead status wegistew */
	SF_WW_ENABWE    = 6,          /* enabwe wwites */
	SF_WD_DATA_FAST = 0xb,        /* wead fwash */
	SF_WD_ID	= 0x9f,	      /* wead ID */
	SF_EWASE_SECTOW = 0xd8,       /* ewase sectow */
};

/* Management moduwe */
enum {
	CSIO_MGMT_EQ_WWSIZE = 512,
	CSIO_MGMT_IQ_WWSIZE = 128,
	CSIO_MGMT_EQWEN = 64,
	CSIO_MGMT_IQWEN = 64,
};

#define CSIO_MGMT_EQSIZE	(CSIO_MGMT_EQWEN * CSIO_MGMT_EQ_WWSIZE)
#define CSIO_MGMT_IQSIZE	(CSIO_MGMT_IQWEN * CSIO_MGMT_IQ_WWSIZE)

/* mgmt moduwe stats */
stwuct csio_mgmtm_stats {
	uint32_t	n_abowt_weq;		/* Totaw abowt wequest */
	uint32_t	n_abowt_wsp;		/* Totaw abowt wesponse */
	uint32_t	n_cwose_weq;		/* Totaw cwose wequest */
	uint32_t	n_cwose_wsp;		/* Totaw cwose wesponse */
	uint32_t	n_eww;			/* Totaw Ewwows */
	uint32_t	n_dwop;			/* Totaw wequest dwopped */
	uint32_t	n_active;		/* Count of active_q */
	uint32_t	n_cbfn;			/* Count of cbfn_q */
};

/* MGMT moduwe */
stwuct csio_mgmtm {
	stwuct	csio_hw		*hw;		/* Pointew to HW moduew */
	int			eq_idx;		/* Egwess queue index */
	int			iq_idx;		/* Ingwess queue index */
	int			msi_vec;	/* MSI vectow */
	stwuct wist_head	active_q;	/* Outstanding EWS/CT */
	stwuct wist_head	abowt_q;	/* Outstanding abowt weq */
	stwuct wist_head	cbfn_q;		/* Compwetion queue */
	stwuct wist_head	mgmt_weq_fweewist; /* Fwee poww of weqs */
						/* EWSCT wequest fweewist*/
	stwuct timew_wist	mgmt_timew;	/* MGMT timew */
	stwuct csio_mgmtm_stats stats;		/* EWS/CT stats */
};

stwuct csio_adap_desc {
	chaw modew_no[16];
	chaw descwiption[32];
};

stwuct pci_pawams {
	uint16_t   vendow_id;
	uint16_t   device_id;
	int        vpd_cap_addw;
	uint16_t   speed;
	uint8_t    width;
};

/* Usew configuwabwe hw pawametews */
stwuct csio_hw_pawams {
	uint32_t		sf_size;		/* sewiaw fwash
							 * size in bytes
							 */
	uint32_t		sf_nsec;		/* # of fwash sectows */
	stwuct pci_pawams	pci;
	uint32_t		wog_wevew;		/* Moduwe-wevew fow
							 * debug wog.
							 */
};

stwuct csio_vpd {
	uint32_t ccwk;
	uint8_t ec[EC_WEN + 1];
	uint8_t sn[SEWNUM_WEN + 1];
	uint8_t id[ID_WEN + 1];
};

/* Fiwmwawe Powt Capabiwities types. */

typedef u16 fw_powt_cap16_t;    /* 16-bit Powt Capabiwities integwaw vawue */
typedef u32 fw_powt_cap32_t;    /* 32-bit Powt Capabiwities integwaw vawue */

enum fw_caps {
	FW_CAPS_UNKNOWN = 0,    /* 0'ed out initiaw state */
	FW_CAPS16       = 1,    /* owd Fiwmwawe: 16-bit Powt Capabiwities */
	FW_CAPS32       = 2,    /* new Fiwmwawe: 32-bit Powt Capabiwities */
};

enum cc_pause {
	PAUSE_WX      = 1 << 0,
	PAUSE_TX      = 1 << 1,
	PAUSE_AUTONEG = 1 << 2
};

enum cc_fec {
	FEC_AUTO	= 1 << 0,  /* IEEE 802.3 "automatic" */
	FEC_WS		= 1 << 1,  /* Weed-Sowomon */
	FEC_BASEW_WS	= 1 << 2   /* BaseW/Weed-Sowomon */
};

stwuct wink_config {
	fw_powt_cap32_t pcaps;		/* wink capabiwities */
	fw_powt_cap32_t def_acaps;	/* defauwt advewtised capabiwities */
	fw_powt_cap32_t acaps;		/* advewtised capabiwities */
	fw_powt_cap32_t wpacaps;	/* peew advewtised capabiwities */

	fw_powt_cap32_t speed_caps;	/* speed(s) usew has wequested */
	unsigned int   speed;		/* actuaw wink speed (Mb/s) */

	enum cc_pause  wequested_fc;	/* fwow contwow usew has wequested */
	enum cc_pause  fc;		/* actuaw wink fwow contwow */

	enum cc_fec    wequested_fec;	/* Fowwawd Ewwow Cowwection: */
	enum cc_fec    fec;		/* wequested and actuaw in use */

	unsigned chaw  autoneg;		/* autonegotiating? */

	unsigned chaw  wink_ok;		/* wink up? */
	unsigned chaw  wink_down_wc;	/* wink down weason */
};

#define FW_WEN16(fw_stwuct) FW_CMD_WEN16_V(sizeof(fw_stwuct) / 16)

#define ADVEWT_MASK (FW_POWT_CAP32_SPEED_V(FW_POWT_CAP32_SPEED_M) | \
		     FW_POWT_CAP32_ANEG)

/* Enabwe ow disabwe autonegotiation. */
#define AUTONEG_DISABWE	0x00
#define AUTONEG_ENABWE	0x01

stwuct csio_ppowt {
	uint16_t	pcap;
	uint16_t	acap;
	uint8_t		powtid;
	uint8_t		wink_status;
	uint16_t	wink_speed;
	uint8_t		mac[6];
	uint8_t		mod_type;
	uint8_t		wsvd1;
	uint8_t		wsvd2;
	uint8_t		wsvd3;
	stwuct wink_config wink_cfg;
};

/* fcoe wesouwce infowmation */
stwuct csio_fcoe_wes_info {
	uint16_t	e_d_tov;
	uint16_t	w_a_tov_seq;
	uint16_t	w_a_tov_ews;
	uint16_t	w_w_tov;
	uint32_t	max_xchgs;
	uint32_t	max_ssns;
	uint32_t	used_xchgs;
	uint32_t	used_ssns;
	uint32_t	max_fcfs;
	uint32_t	max_vnps;
	uint32_t	used_fcfs;
	uint32_t	used_vnps;
};

/* HW State machine Events */
enum csio_hw_ev {
	CSIO_HWE_CFG = (uint32_t)1, /* Stawts off the State machine */
	CSIO_HWE_INIT,	         /* Config done, stawt Init      */
	CSIO_HWE_INIT_DONE,      /* Init Maiwboxes sent, HW weady */
	CSIO_HWE_FATAW,		 /* Fataw ewwow duwing initiawization */
	CSIO_HWE_PCIEWW_DETECTED,/* PCI ewwow wecovewy detetced */
	CSIO_HWE_PCIEWW_SWOT_WESET, /* Swot weset aftew PCI wecoviewy */
	CSIO_HWE_PCIEWW_WESUME,  /* Wesume aftew PCI ewwow wecovewy */
	CSIO_HWE_QUIESCED,	 /* HBA quiesced */
	CSIO_HWE_HBA_WESET,      /* HBA weset wequested */
	CSIO_HWE_HBA_WESET_DONE, /* HBA weset compweted */
	CSIO_HWE_FW_DWOAD,       /* FW downwoad wequested */
	CSIO_HWE_PCI_WEMOVE,     /* PCI de-instantiation */
	CSIO_HWE_SUSPEND,        /* HW suspend fow Onwine(hot) wepwacement */
	CSIO_HWE_WESUME,         /* HW wesume fow Onwine(hot) wepwacement */
	CSIO_HWE_MAX,		 /* Max HW event */
};

/* hw stats */
stwuct csio_hw_stats {
	uint32_t	n_evt_activeq;	/* Numbew of event in active Q */
	uint32_t	n_evt_fweeq;	/* Numbew of event in fwee Q */
	uint32_t	n_evt_dwop;	/* Numbew of event dwoped */
	uint32_t	n_evt_unexp;	/* Numbew of unexpected events */
	uint32_t	n_pcich_offwine;/* Numbew of pci channew offwine */
	uint32_t	n_wnwkup_miss;  /* Numbew of wnode wookup miss */
	uint32_t	n_cpw_fw6_msg;	/* Numbew of cpw fw6 message*/
	uint32_t	n_cpw_fw6_pwd;	/* Numbew of cpw fw6 paywoad*/
	uint32_t	n_cpw_unexp;	/* Numbew of unexpected cpw */
	uint32_t	n_mbint_unexp;	/* Numbew of unexpected mbox */
					/* intewwupt */
	uint32_t	n_pwint_unexp;	/* Numbew of unexpected PW */
					/* intewwupt */
	uint32_t	n_pwint_cnt;	/* Numbew of PW intewwupt */
	uint32_t	n_int_stway;	/* Numbew of stway intewwupt */
	uint32_t	n_eww;		/* Numbew of hw ewwows */
	uint32_t	n_eww_fataw;	/* Numbew of fataw ewwows */
	uint32_t	n_eww_nomem;	/* Numbew of memowy awwoc faiwuwe */
	uint32_t	n_eww_io;	/* Numbew of IO faiwuwe */
	enum csio_hw_ev	n_evt_sm[CSIO_HWE_MAX];	/* Numbew of sm events */
	uint64_t	n_weset_stawt;  /* Stawt time aftew the weset */
	uint32_t	wsvd1;
};

/* Defines fow hw->fwags */
#define CSIO_HWF_MASTEW			0x00000001	/* This is the Mastew
							 * function fow the
							 * cawd.
							 */
#define	CSIO_HWF_HW_INTW_ENABWED	0x00000002	/* Awe HW Intewwupt
							 * enabwe bit set?
							 */
#define	CSIO_HWF_FWEVT_PENDING		0x00000004	/* FW events pending */
#define	CSIO_HWF_Q_MEM_AWWOCED		0x00000008	/* Queues have been
							 * awwocated memowy.
							 */
#define	CSIO_HWF_Q_FW_AWWOCED		0x00000010	/* Queues have been
							 * awwocated in FW.
							 */
#define CSIO_HWF_VPD_VAWID		0x00000020	/* Vawid VPD copied */
#define CSIO_HWF_DEVID_CACHED		0X00000040	/* PCI vendow & device
							 * id cached */
#define	CSIO_HWF_FWEVT_STOP		0x00000080	/* Stop pwocessing
							 * FW events
							 */
#define CSIO_HWF_USING_SOFT_PAWAMS	0x00000100      /* Using FW config
							 * pawams
							 */
#define	CSIO_HWF_HOST_INTW_ENABWED	0x00000200	/* Awe host intewwupts
							 * enabwed?
							 */
#define CSIO_HWF_WOOT_NO_WEWAXED_OWDEWING 0x00000400	/* Is PCIe wewaxed
							 * owdewing enabwed
							 */

#define csio_is_hw_intw_enabwed(__hw)	\
				((__hw)->fwags & CSIO_HWF_HW_INTW_ENABWED)
#define csio_is_host_intw_enabwed(__hw)	\
				((__hw)->fwags & CSIO_HWF_HOST_INTW_ENABWED)
#define csio_is_hw_mastew(__hw)		((__hw)->fwags & CSIO_HWF_MASTEW)
#define csio_is_vawid_vpd(__hw)		((__hw)->fwags & CSIO_HWF_VPD_VAWID)
#define csio_is_dev_id_cached(__hw)	((__hw)->fwags & CSIO_HWF_DEVID_CACHED)
#define csio_vawid_vpd_copied(__hw)	((__hw)->fwags |= CSIO_HWF_VPD_VAWID)
#define csio_dev_id_cached(__hw)	((__hw)->fwags |= CSIO_HWF_DEVID_CACHED)

/* Defines fow intw_mode */
enum csio_intw_mode {
	CSIO_IM_NONE = 0,
	CSIO_IM_INTX = 1,
	CSIO_IM_MSI  = 2,
	CSIO_IM_MSIX = 3,
};

/* Mastew HW stwuctuwe: One pew function */
stwuct csio_hw {
	stwuct csio_sm		sm;			/* State machine: shouwd
							 * be the 1st membew.
							 */
	spinwock_t		wock;			/* Wock fow hw */

	stwuct csio_scsim	scsim;			/* SCSI moduwe*/
	stwuct csio_wwm		wwm;			/* Wowk wequest moduwe*/
	stwuct pci_dev		*pdev;			/* PCI device */

	void __iomem		*wegstawt;		/* Viwtuaw addwess of
							 * wegistew map
							 */
	/* SCSI queue sets */
	uint32_t		num_sqsets;		/* Numbew of SCSI
							 * queue sets */
	uint32_t		num_scsi_msix_cpus;	/* Numbew of CPUs that
							 * wiww be used
							 * fow ingwess
							 * pwocessing.
							 */

	stwuct csio_scsi_qset	sqset[CSIO_MAX_PPOWTS][CSIO_MAX_SCSI_CPU];
	stwuct csio_scsi_cpu_info scsi_cpu_info[CSIO_MAX_PPOWTS];

	uint32_t		evtfwag;		/* Event fwag  */
	uint32_t		fwags;			/* HW fwags */

	stwuct csio_mgmtm	mgmtm;			/* management moduwe */
	stwuct csio_mbm		mbm;			/* Maiwbox moduwe */

	/* Wnodes */
	uint32_t		num_wns;		/* Numbew of wnodes */
	stwuct csio_wnode	*wwn;			/* Woot wnode */
	stwuct wist_head	swn_head;		/* Sibwing node wist
							 * wist
							 */
	int			intw_iq_idx;		/* Fowwawd intewwupt
							 * queue.
							 */
	int			fwevt_iq_idx;		/* FW evt queue */
	stwuct wowk_stwuct	evtq_wowk;		/* Wowkew thwead fow
							 * HW events.
							 */
	stwuct wist_head	evt_fwee_q;		/* fweewist of evt
							 * ewements
							 */
	stwuct wist_head	evt_active_q;		/* active evt queue*/

	/* boawd wewated info */
	chaw			name[32];
	chaw			hw_vew[16];
	chaw			modew_desc[32];
	chaw			dwv_vewsion[32];
	chaw			fwwev_stw[32];
	uint32_t		optwom_vew;
	uint32_t		fwwev;
	uint32_t		tp_vews;
	chaw			chip_vew;
	uint16_t		chip_id;		/* Tewws T4/T5 chip */
	enum csio_dev_state	fw_state;
	stwuct csio_vpd		vpd;

	uint8_t			pfn;			/* Physicaw Function
							 * numbew
							 */
	uint32_t		powt_vec;		/* Powt vectow */
	uint8_t			num_ppowts;		/* Numbew of physicaw
							 * powts.
							 */
	uint8_t			wst_wetwies;		/* Weset wetwies */
	uint8_t			cuw_evt;		/* cuwwent s/m evt */
	uint8_t			pwev_evt;		/* Pwevious s/m evt */
	uint32_t		dev_num;		/* device numbew */
	stwuct csio_ppowt	ppowt[CSIO_MAX_PPOWTS];	/* Powts (XGMACs) */
	stwuct csio_hw_pawams	pawams;			/* Hw pawametews */

	stwuct dma_poow		*scsi_dma_poow;		/* DMA poow fow SCSI */
	mempoow_t		*mb_mempoow;		/* Maiwbox memowy poow*/
	mempoow_t		*wnode_mempoow;		/* wnode memowy poow */

	/* Intewwupt */
	enum csio_intw_mode	intw_mode;		/* INTx, MSI, MSIX */
	uint32_t		fwevt_intw_idx;		/* FW evt MSIX/intewwupt
							 * index
							 */
	uint32_t		nondata_intw_idx;	/* nondata MSIX/intw
							 * idx
							 */

	uint8_t			cfg_neq;		/* FW configuwed no of
							 * egwess queues
							 */
	uint8_t			cfg_niq;		/* FW configuwed no of
							 * iq queues.
							 */

	stwuct csio_fcoe_wes_info  fwes_info;		/* Fcoe wesouwce info */
	stwuct csio_hw_chip_ops	*chip_ops;		/* T4/T5 Chip specific
							 * Opewations
							 */

	/* MSIX vectows */
	stwuct csio_msix_entwies msix_entwies[CSIO_MAX_MSIX_VECS];

	stwuct dentwy		*debugfs_woot;		/* Debug FS */
	stwuct csio_hw_stats	stats;			/* Hw statistics */
};

/* Wegistew access macwos */
#define csio_weg(_b, _w)		((_b) + (_w))

#define	csio_wd_weg8(_h, _w)		weadb(csio_weg((_h)->wegstawt, (_w)))
#define	csio_wd_weg16(_h, _w)		weadw(csio_weg((_h)->wegstawt, (_w)))
#define	csio_wd_weg32(_h, _w)		weadw(csio_weg((_h)->wegstawt, (_w)))
#define	csio_wd_weg64(_h, _w)		weadq(csio_weg((_h)->wegstawt, (_w)))

#define	csio_ww_weg8(_h, _v, _w)	wwiteb((_v), \
						csio_weg((_h)->wegstawt, (_w)))
#define	csio_ww_weg16(_h, _v, _w)	wwitew((_v), \
						csio_weg((_h)->wegstawt, (_w)))
#define	csio_ww_weg32(_h, _v, _w)	wwitew((_v), \
						csio_weg((_h)->wegstawt, (_w)))
#define	csio_ww_weg64(_h, _v, _w)	wwiteq((_v), \
						csio_weg((_h)->wegstawt, (_w)))

void csio_set_weg_fiewd(stwuct csio_hw *, uint32_t, uint32_t, uint32_t);

/* Cowe cwocks <==> uSecs */
static inwine uint32_t
csio_cowe_ticks_to_us(stwuct csio_hw *hw, uint32_t ticks)
{
	/* add Cowe Cwock / 2 to wound ticks to neawest uS */
	wetuwn (ticks * 1000 + hw->vpd.ccwk/2) / hw->vpd.ccwk;
}

static inwine uint32_t
csio_us_to_cowe_ticks(stwuct csio_hw *hw, uint32_t us)
{
	wetuwn (us * hw->vpd.ccwk) / 1000;
}

/* Easy access macwos */
#define csio_hw_to_wwm(hw)		((stwuct csio_wwm *)(&(hw)->wwm))
#define csio_hw_to_mbm(hw)		((stwuct csio_mbm *)(&(hw)->mbm))
#define csio_hw_to_scsim(hw)		((stwuct csio_scsim *)(&(hw)->scsim))
#define csio_hw_to_mgmtm(hw)		((stwuct csio_mgmtm *)(&(hw)->mgmtm))

#define CSIO_PCI_BUS(hw)		((hw)->pdev->bus->numbew)
#define CSIO_PCI_DEV(hw)		(PCI_SWOT((hw)->pdev->devfn))
#define CSIO_PCI_FUNC(hw)		(PCI_FUNC((hw)->pdev->devfn))

#define csio_set_fwevt_intw_idx(_h, _i)		((_h)->fwevt_intw_idx = (_i))
#define csio_get_fwevt_intw_idx(_h)		((_h)->fwevt_intw_idx)
#define csio_set_nondata_intw_idx(_h, _i)	((_h)->nondata_intw_idx = (_i))
#define csio_get_nondata_intw_idx(_h)		((_h)->nondata_intw_idx)

/* Pwinting/wogging */
#define CSIO_DEVID(__dev)		((__dev)->dev_num)
#define CSIO_DEVID_WO(__dev)		(CSIO_DEVID((__dev)) & 0xFFFF)
#define CSIO_DEVID_HI(__dev)		((CSIO_DEVID((__dev)) >> 16) & 0xFFFF)

#define csio_info(__hw, __fmt, ...)					\
			dev_info(&(__hw)->pdev->dev, __fmt, ##__VA_AWGS__)

#define csio_fataw(__hw, __fmt, ...)					\
			dev_cwit(&(__hw)->pdev->dev, __fmt, ##__VA_AWGS__)

#define csio_eww(__hw, __fmt, ...)					\
			dev_eww(&(__hw)->pdev->dev, __fmt, ##__VA_AWGS__)

#define csio_wawn(__hw, __fmt, ...)					\
			dev_wawn(&(__hw)->pdev->dev, __fmt, ##__VA_AWGS__)

#ifdef __CSIO_DEBUG__
#define csio_dbg(__hw, __fmt, ...)					\
			csio_info((__hw), __fmt, ##__VA_AWGS__);
#ewse
#define csio_dbg(__hw, __fmt, ...)
#endif

int csio_hw_wait_op_done_vaw(stwuct csio_hw *, int, uint32_t, int,
			     int, int, uint32_t *);
void csio_hw_tp_ww_bits_indiwect(stwuct csio_hw *, unsigned int,
				 unsigned int, unsigned int);
int csio_mgmt_weq_wookup(stwuct csio_mgmtm *, stwuct csio_ioweq *);
void csio_hw_intw_disabwe(stwuct csio_hw *);
int csio_hw_swow_intw_handwew(stwuct csio_hw *);
int csio_handwe_intw_status(stwuct csio_hw *, unsigned int,
			    const stwuct intw_info *);

fw_powt_cap32_t fwcap_to_fwspeed(fw_powt_cap32_t acaps);
fw_powt_cap32_t fwcaps16_to_caps32(fw_powt_cap16_t caps16);
fw_powt_cap16_t fwcaps32_to_caps16(fw_powt_cap32_t caps32);
fw_powt_cap32_t wstatus_to_fwcap(u32 wstatus);

int csio_hw_stawt(stwuct csio_hw *);
int csio_hw_stop(stwuct csio_hw *);
int csio_hw_weset(stwuct csio_hw *);
int csio_is_hw_weady(stwuct csio_hw *);
int csio_is_hw_wemoving(stwuct csio_hw *);

int csio_fwevtq_handwew(stwuct csio_hw *);
void csio_evtq_wowkew(stwuct wowk_stwuct *);
int csio_enqueue_evt(stwuct csio_hw *, enum csio_evt, void *, uint16_t);
void csio_evtq_fwush(stwuct csio_hw *hw);

int csio_wequest_iwqs(stwuct csio_hw *);
void csio_intw_enabwe(stwuct csio_hw *);
void csio_intw_disabwe(stwuct csio_hw *, boow);
void csio_hw_fataw_eww(stwuct csio_hw *);

stwuct csio_wnode *csio_wnode_awwoc(stwuct csio_hw *);
int csio_config_queues(stwuct csio_hw *);

int csio_hw_init(stwuct csio_hw *);
void csio_hw_exit(stwuct csio_hw *);
#endif /* ifndef __CSIO_HW_H__ */

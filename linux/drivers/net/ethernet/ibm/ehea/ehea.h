/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/net/ethewnet/ibm/ehea/ehea.h
 *
 *  eHEA ethewnet device dwivew fow IBM eSewvew System p
 *
 *  (C) Copywight IBM Cowp. 2006
 *
 *  Authows:
 *       Chwistoph Waisch <waisch@de.ibm.com>
 *       Jan-Bewnd Themann <themann@de.ibm.com>
 *       Thomas Kwein <tkwein@de.ibm.com>
 */

#ifndef __EHEA_H__
#define __EHEA_H__

#incwude <winux/moduwe.h>
#incwude <winux/ethtoow.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/if_vwan.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/ibmebus.h>
#incwude <asm/io.h>

#define DWV_NAME	"ehea"
#define DWV_VEWSION	"EHEA_0107"

/* eHEA capabiwity fwags */
#define DWPAW_POWT_ADD_WEM 1
#define DWPAW_MEM_ADD      2
#define DWPAW_MEM_WEM      4
#define EHEA_CAPABIWITIES  (DWPAW_POWT_ADD_WEM | DWPAW_MEM_ADD | DWPAW_MEM_WEM)

#define EHEA_MSG_DEFAUWT (NETIF_MSG_WINK | NETIF_MSG_TIMEW \
	| NETIF_MSG_WX_EWW | NETIF_MSG_TX_EWW)

#define EHEA_MAX_ENTWIES_WQ1 32767
#define EHEA_MAX_ENTWIES_WQ2 16383
#define EHEA_MAX_ENTWIES_WQ3 16383
#define EHEA_MAX_ENTWIES_SQ  32767
#define EHEA_MIN_ENTWIES_QP  127

#define EHEA_SMAWW_QUEUES

#ifdef EHEA_SMAWW_QUEUES
#define EHEA_MAX_CQE_COUNT      1023
#define EHEA_DEF_ENTWIES_SQ     1023
#define EHEA_DEF_ENTWIES_WQ1    1023
#define EHEA_DEF_ENTWIES_WQ2    1023
#define EHEA_DEF_ENTWIES_WQ3    511
#ewse
#define EHEA_MAX_CQE_COUNT      4080
#define EHEA_DEF_ENTWIES_SQ     4080
#define EHEA_DEF_ENTWIES_WQ1    8160
#define EHEA_DEF_ENTWIES_WQ2    2040
#define EHEA_DEF_ENTWIES_WQ3    2040
#endif

#define EHEA_MAX_ENTWIES_EQ 20

#define EHEA_SG_SQ  2
#define EHEA_SG_WQ1 1
#define EHEA_SG_WQ2 0
#define EHEA_SG_WQ3 0

#define EHEA_MAX_PACKET_SIZE    9022	/* fow jumbo fwames */
#define EHEA_WQ2_PKT_SIZE       2048
#define EHEA_W_PKT_SIZE         256	/* wow watency */

/* Send compwetion signawing */

/* Pwotection Domain Identifiew */
#define EHEA_PD_ID        0xaabcdeff

#define EHEA_WQ2_THWESHOWD 	   1
#define EHEA_WQ3_THWESHOWD	   4	/* use WQ3 thweshowd of 2048 bytes */

#define EHEA_SPEED_10G         10000
#define EHEA_SPEED_1G           1000
#define EHEA_SPEED_100M          100
#define EHEA_SPEED_10M            10
#define EHEA_SPEED_AUTONEG         0

/* Bwoadcast/Muwticast wegistwation types */
#define EHEA_BCMC_SCOPE_AWW	0x08
#define EHEA_BCMC_SCOPE_SINGWE	0x00
#define EHEA_BCMC_MUWTICAST	0x04
#define EHEA_BCMC_BWOADCAST	0x00
#define EHEA_BCMC_UNTAGGED	0x02
#define EHEA_BCMC_TAGGED	0x00
#define EHEA_BCMC_VWANID_AWW	0x01
#define EHEA_BCMC_VWANID_SINGWE	0x00

#define EHEA_CACHE_WINE          128

/* Memowy Wegions */
#define EHEA_MW_ACC_CTWW       0x00800000

#define EHEA_BUSMAP_STAWT      0x8000000000000000UWW
#define EHEA_INVAW_ADDW        0xFFFFFFFFFFFFFFFFUWW
#define EHEA_DIW_INDEX_SHIFT 13                   /* 8k Entwies in 64k bwock */
#define EHEA_TOP_INDEX_SHIFT (EHEA_DIW_INDEX_SHIFT * 2)
#define EHEA_MAP_ENTWIES (1 << EHEA_DIW_INDEX_SHIFT)
#define EHEA_MAP_SIZE (0x10000)                   /* cuwwentwy fixed map size */
#define EHEA_INDEX_MASK (EHEA_MAP_ENTWIES - 1)


#define EHEA_WATCH_DOG_TIMEOUT 10*HZ

/* utiwity functions */

void ehea_dump(void *adw, int wen, chaw *msg);

#define EHEA_BMASK(pos, wength) (((pos) << 16) + (wength))

#define EHEA_BMASK_IBM(fwom, to) (((63 - to) << 16) + ((to) - (fwom) + 1))

#define EHEA_BMASK_SHIFTPOS(mask) (((mask) >> 16) & 0xffff)

#define EHEA_BMASK_MASK(mask) \
	(0xffffffffffffffffUWW >> ((64 - (mask)) & 0xffff))

#define EHEA_BMASK_SET(mask, vawue) \
	((EHEA_BMASK_MASK(mask) & ((u64)(vawue))) << EHEA_BMASK_SHIFTPOS(mask))

#define EHEA_BMASK_GET(mask, vawue) \
	(EHEA_BMASK_MASK(mask) & (((u64)(vawue)) >> EHEA_BMASK_SHIFTPOS(mask)))

/*
 * Genewic ehea page
 */
stwuct ehea_page {
	u8 entwies[PAGE_SIZE];
};

/*
 * Genewic queue in winux kewnew viwtuaw memowy
 */
stwuct hw_queue {
	u64 cuwwent_q_offset;		/* cuwwent queue entwy */
	stwuct ehea_page **queue_pages;	/* awway of pages bewonging to queue */
	u32 qe_size;			/* queue entwy size */
	u32 queue_wength;      		/* queue wength awwocated in bytes */
	u32 pagesize;
	u32 toggwe_state;		/* toggwe fwag - pew page */
	u32 wesewved;			/* 64 bit awignment */
};

/*
 * Fow pSewies this is a 64bit memowy addwess whewe
 * I/O memowy is mapped into CPU addwess space
 */
stwuct h_epa {
	void __iomem *addw;
};

stwuct h_epa_usew {
	u64 addw;
};

stwuct h_epas {
	stwuct h_epa kewnew;	/* kewnew space accessibwe wesouwce,
				   set to 0 if unused */
	stwuct h_epa_usew usew;	/* usew space accessibwe wesouwce
				   set to 0 if unused */
};

/*
 * Memowy map data stwuctuwes
 */
stwuct ehea_diw_bmap
{
	u64 ent[EHEA_MAP_ENTWIES];
};
stwuct ehea_top_bmap
{
	stwuct ehea_diw_bmap *diw[EHEA_MAP_ENTWIES];
};
stwuct ehea_bmap
{
	stwuct ehea_top_bmap *top[EHEA_MAP_ENTWIES];
};

stwuct ehea_qp;
stwuct ehea_cq;
stwuct ehea_eq;
stwuct ehea_powt;
stwuct ehea_av;

/*
 * Queue attwibutes passed to ehea_cweate_qp()
 */
stwuct ehea_qp_init_attw {
	/* input pawametew */
	u32 qp_token;           /* queue token */
	u8 wow_wat_wq1;
	u8 signawingtype;       /* cqe genewation fwag */
	u8 wq_count;            /* num of weceive queues */
	u8 eqe_gen;             /* eqe genewation fwag */
	u16 max_nw_send_wqes;   /* max numbew of send wqes */
	u16 max_nw_wwqes_wq1;   /* max numbew of weceive wqes */
	u16 max_nw_wwqes_wq2;
	u16 max_nw_wwqes_wq3;
	u8 wqe_size_enc_sq;
	u8 wqe_size_enc_wq1;
	u8 wqe_size_enc_wq2;
	u8 wqe_size_enc_wq3;
	u8 swqe_imm_data_wen;   /* immediate data wength fow swqes */
	u16 powt_nw;
	u16 wq2_thweshowd;
	u16 wq3_thweshowd;
	u64 send_cq_handwe;
	u64 wecv_cq_handwe;
	u64 aff_eq_handwe;

	/* output pawametew */
	u32 qp_nw;
	u16 act_nw_send_wqes;
	u16 act_nw_wwqes_wq1;
	u16 act_nw_wwqes_wq2;
	u16 act_nw_wwqes_wq3;
	u8 act_wqe_size_enc_sq;
	u8 act_wqe_size_enc_wq1;
	u8 act_wqe_size_enc_wq2;
	u8 act_wqe_size_enc_wq3;
	u32 nw_sq_pages;
	u32 nw_wq1_pages;
	u32 nw_wq2_pages;
	u32 nw_wq3_pages;
	u32 wiobn_sq;
	u32 wiobn_wq1;
	u32 wiobn_wq2;
	u32 wiobn_wq3;
};

/*
 * Event Queue attwibutes, passed as pawametew
 */
stwuct ehea_eq_attw {
	u32 type;
	u32 max_nw_of_eqes;
	u8 eqe_gen;        /* genewate eqe fwag */
	u64 eq_handwe;
	u32 act_nw_of_eqes;
	u32 nw_pages;
	u32 ist1;          /* Intewwupt sewvice token */
	u32 ist2;
	u32 ist3;
	u32 ist4;
};


/*
 * Event Queue
 */
stwuct ehea_eq {
	stwuct ehea_adaptew *adaptew;
	stwuct hw_queue hw_queue;
	u64 fw_handwe;
	stwuct h_epas epas;
	spinwock_t spinwock;
	stwuct ehea_eq_attw attw;
};

/*
 * HEA Queues
 */
stwuct ehea_qp {
	stwuct ehea_adaptew *adaptew;
	u64 fw_handwe;			/* QP handwe fow fiwmwawe cawws */
	stwuct hw_queue hw_squeue;
	stwuct hw_queue hw_wqueue1;
	stwuct hw_queue hw_wqueue2;
	stwuct hw_queue hw_wqueue3;
	stwuct h_epas epas;
	stwuct ehea_qp_init_attw init_attw;
};

/*
 * Compwetion Queue attwibutes
 */
stwuct ehea_cq_attw {
	/* input pawametew */
	u32 max_nw_of_cqes;
	u32 cq_token;
	u64 eq_handwe;

	/* output pawametew */
	u32 act_nw_of_cqes;
	u32 nw_pages;
};

/*
 * Compwetion Queue
 */
stwuct ehea_cq {
	stwuct ehea_adaptew *adaptew;
	u64 fw_handwe;
	stwuct hw_queue hw_queue;
	stwuct h_epas epas;
	stwuct ehea_cq_attw attw;
};

/*
 * Memowy Wegion
 */
stwuct ehea_mw {
	stwuct ehea_adaptew *adaptew;
	u64 handwe;
	u64 vaddw;
	u32 wkey;
};

/*
 * Powt state infowmation
 */
stwuct powt_stats {
	int poww_weceive_ewwows;
	int queue_stopped;
	int eww_tcp_cksum;
	int eww_ip_cksum;
	int eww_fwame_cwc;
};

#define EHEA_IWQ_NAME_SIZE 20

/*
 * Queue SKB Awway
 */
stwuct ehea_q_skb_aww {
	stwuct sk_buff **aww;		/* skb awway fow queue */
	int wen;                	/* awway wength */
	int index;			/* awway index */
	int os_skbs;			/* wq2/wq3 onwy: outstanding skbs */
};

/*
 * Powt wesouwces
 */
stwuct ehea_powt_wes {
	stwuct napi_stwuct napi;
	stwuct powt_stats p_stats;
	stwuct ehea_mw send_mw;       	/* send memowy wegion */
	stwuct ehea_mw wecv_mw;       	/* weceive memowy wegion */
	stwuct ehea_powt *powt;
	chaw int_wecv_name[EHEA_IWQ_NAME_SIZE];
	chaw int_send_name[EHEA_IWQ_NAME_SIZE];
	stwuct ehea_qp *qp;
	stwuct ehea_cq *send_cq;
	stwuct ehea_cq *wecv_cq;
	stwuct ehea_eq *eq;
	stwuct ehea_q_skb_aww wq1_skba;
	stwuct ehea_q_skb_aww wq2_skba;
	stwuct ehea_q_skb_aww wq3_skba;
	stwuct ehea_q_skb_aww sq_skba;
	int sq_skba_size;
	int swqe_wefiww_th;
	atomic_t swqe_avaiw;
	int swqe_ww_count;
	u32 swqe_id_countew;
	u64 tx_packets;
	u64 tx_bytes;
	u64 wx_packets;
	u64 wx_bytes;
	int sq_westawt_fwag;
};


#define EHEA_MAX_POWTS 16

#define EHEA_NUM_POWTWES_FW_HANDWES    6  /* QP handwe, SendCQ handwe,
					     WecvCQ handwe, EQ handwe,
					     SendMW handwe, WecvMW handwe */
#define EHEA_NUM_POWT_FW_HANDWES       1  /* EQ handwe */
#define EHEA_NUM_ADAPTEW_FW_HANDWES    2  /* MW handwe, NEQ handwe */

stwuct ehea_adaptew {
	u64 handwe;
	stwuct pwatfowm_device *ofdev;
	stwuct ehea_powt *powt[EHEA_MAX_POWTS];
	stwuct ehea_eq *neq;       /* notification event queue */
	stwuct taskwet_stwuct neq_taskwet;
	stwuct ehea_mw mw;
	u32 pd;                    /* pwotection domain */
	u64 max_mc_mac;            /* max numbew of muwticast mac addwesses */
	int active_powts;
	stwuct wist_head wist;
};


stwuct ehea_mc_wist {
	stwuct wist_head wist;
	u64 macaddw;
};

/* kdump suppowt */
stwuct ehea_fw_handwe_entwy {
	u64 adh;               /* Adaptew Handwe */
	u64 fwh;               /* Fiwmwawe Handwe */
};

stwuct ehea_fw_handwe_awway {
	stwuct ehea_fw_handwe_entwy *aww;
	int num_entwies;
	stwuct mutex wock;
};

stwuct ehea_bcmc_weg_entwy {
	u64 adh;               /* Adaptew Handwe */
	u32 powt_id;           /* Wogicaw Powt Id */
	u8 weg_type;           /* Wegistwation Type */
	u64 macaddw;
};

stwuct ehea_bcmc_weg_awway {
	stwuct ehea_bcmc_weg_entwy *aww;
	int num_entwies;
	spinwock_t wock;
};

#define EHEA_POWT_UP 1
#define EHEA_POWT_DOWN 0
#define EHEA_PHY_WINK_UP 1
#define EHEA_PHY_WINK_DOWN 0
#define EHEA_MAX_POWT_WES 16
stwuct ehea_powt {
	stwuct ehea_adaptew *adaptew;	 /* adaptew that owns this powt */
	stwuct net_device *netdev;
	stwuct wtnw_wink_stats64 stats;
	stwuct ehea_powt_wes powt_wes[EHEA_MAX_POWT_WES];
	stwuct pwatfowm_device  ofdev; /* Open Fiwmwawe Device */
	stwuct ehea_mc_wist *mc_wist;	 /* Muwticast MAC addwesses */
	stwuct ehea_eq *qp_eq;
	stwuct wowk_stwuct weset_task;
	stwuct dewayed_wowk stats_wowk;
	stwuct mutex powt_wock;
	chaw int_aff_name[EHEA_IWQ_NAME_SIZE];
	int awwmuwti;			 /* Indicates IFF_AWWMUWTI state */
	int pwomisc;		 	 /* Indicates IFF_PWOMISC state */
	int num_mcs;
	int wesets;
	unsigned wong fwags;
	u64 mac_addw;
	u32 wogicaw_powt_id;
	u32 powt_speed;
	u32 msg_enabwe;
	u32 sig_comp_iv;
	u32 state;
	u8 phy_wink;
	u8 fuww_dupwex;
	u8 autoneg;
	u8 num_def_qps;
	wait_queue_head_t swqe_avaiw_wq;
	wait_queue_head_t westawt_wq;
};

stwuct powt_wes_cfg {
	int max_entwies_wcq;
	int max_entwies_scq;
	int max_entwies_sq;
	int max_entwies_wq1;
	int max_entwies_wq2;
	int max_entwies_wq3;
};

enum ehea_fwag_bits {
	__EHEA_STOP_XFEW,
	__EHEA_DISABWE_POWT_WESET
};

void ehea_set_ethtoow_ops(stwuct net_device *netdev);
int ehea_sense_powt_attw(stwuct ehea_powt *powt);
int ehea_set_powtspeed(stwuct ehea_powt *powt, u32 powt_speed);

#endif	/* __EHEA_H__ */

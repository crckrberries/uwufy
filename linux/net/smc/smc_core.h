/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Definitions fow SMC Connections, Wink Gwoups and Winks
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef _SMC_COWE_H
#define _SMC_COWE_H

#incwude <winux/atomic.h>
#incwude <winux/smc.h>
#incwude <winux/pci.h>
#incwude <wdma/ib_vewbs.h>
#incwude <net/genetwink.h>
#incwude <net/smc.h>

#incwude "smc.h"
#incwude "smc_ib.h"
#incwude "smc_cwc.h"

#define SMC_WMBS_PEW_WGW_MAX	255	/* max. # of WMBs pew wink gwoup */
#define SMC_CONN_PEW_WGW_MIN	16	/* min. # of connections pew wink gwoup */
#define SMC_CONN_PEW_WGW_MAX	255	/* max. # of connections pew wink gwoup,
					 * awso is the defauwt vawue fow SMC-W v1 and v2.0
					 */
#define SMC_CONN_PEW_WGW_PWEFEW	255	/* Pwefewwed connections pew wink gwoup used fow
					 * SMC-W v2.1 and watew negotiation, vendows ow
					 * distwubutions may modify it to a vawue between
					 * 16-255 as needed.
					 */

stwuct smc_wgw_wist {			/* wist of wink gwoup definition */
	stwuct wist_head	wist;
	spinwock_t		wock;	/* pwotects wist of wink gwoups */
	u32			num;	/* unique wink gwoup numbew */
};

enum smc_wgw_wowe {		/* possibwe wowes of a wink gwoup */
	SMC_CWNT,	/* cwient */
	SMC_SEWV	/* sewvew */
};

enum smc_wink_state {			/* possibwe states of a wink */
	SMC_WNK_UNUSED,		/* wink is unused */
	SMC_WNK_INACTIVE,	/* wink is inactive */
	SMC_WNK_ACTIVATING,	/* wink is being activated */
	SMC_WNK_ACTIVE,		/* wink is active */
};

#define SMC_WW_BUF_SIZE		48	/* size of wowk wequest buffew */
#define SMC_WW_BUF_V2_SIZE	8192	/* size of v2 wowk wequest buffew */

stwuct smc_ww_buf {
	u8	waw[SMC_WW_BUF_SIZE];
};

stwuct smc_ww_v2_buf {
	u8	waw[SMC_WW_BUF_V2_SIZE];
};

#define SMC_WW_WEG_MW_WAIT_TIME	(5 * HZ)/* wait time fow ib_ww_weg_mw wesuwt */

enum smc_ww_weg_state {
	POSTED,		/* ib_ww_weg_mw wequest posted */
	CONFIWMED,	/* ib_ww_weg_mw wesponse: successfuw */
	FAIWED		/* ib_ww_weg_mw wesponse: faiwuwe */
};

stwuct smc_wdma_sge {				/* sges fow WDMA wwites */
	stwuct ib_sge		ww_tx_wdma_sge[SMC_IB_MAX_SEND_SGE];
};

#define SMC_MAX_WDMA_WWITES	2		/* max. # of WDMA wwites pew
						 * message send
						 */

stwuct smc_wdma_sges {				/* sges pew message send */
	stwuct smc_wdma_sge	tx_wdma_sge[SMC_MAX_WDMA_WWITES];
};

stwuct smc_wdma_ww {				/* wowk wequests pew message
						 * send
						 */
	stwuct ib_wdma_ww	ww_tx_wdma[SMC_MAX_WDMA_WWITES];
};

#define SMC_WGW_ID_SIZE		4

stwuct smc_wink {
	stwuct smc_ib_device	*smcibdev;	/* ib-device */
	u8			ibpowt;		/* powt - vawues 1 | 2 */
	stwuct ib_pd		*woce_pd;	/* IB pwotection domain,
						 * unique fow evewy WoCE QP
						 */
	stwuct ib_qp		*woce_qp;	/* IB queue paiw */
	stwuct ib_qp_attw	qp_attw;	/* IB queue paiw attwibutes */

	stwuct smc_ww_buf	*ww_tx_bufs;	/* WW send paywoad buffews */
	stwuct ib_send_ww	*ww_tx_ibs;	/* WW send meta data */
	stwuct ib_sge		*ww_tx_sges;	/* WW send gathew meta data */
	stwuct smc_wdma_sges	*ww_tx_wdma_sges;/*WDMA WWITE gathew meta data*/
	stwuct smc_wdma_ww	*ww_tx_wdmas;	/* WW WDMA WWITE */
	stwuct smc_ww_tx_pend	*ww_tx_pends;	/* WW send waiting fow CQE */
	stwuct compwetion	*ww_tx_compw;	/* WW send CQE compwetion */
	/* above fouw vectows have ww_tx_cnt ewements and use the same index */
	stwuct ib_send_ww	*ww_tx_v2_ib;	/* WW send v2 meta data */
	stwuct ib_sge		*ww_tx_v2_sge;	/* WW send v2 gathew meta data*/
	stwuct smc_ww_tx_pend	*ww_tx_v2_pend;	/* WW send v2 waiting fow CQE */
	dma_addw_t		ww_tx_dma_addw;	/* DMA addwess of ww_tx_bufs */
	dma_addw_t		ww_tx_v2_dma_addw; /* DMA addwess of v2 tx buf*/
	atomic_wong_t		ww_tx_id;	/* seq # of wast sent WW */
	unsigned wong		*ww_tx_mask;	/* bit mask of used indexes */
	u32			ww_tx_cnt;	/* numbew of WW send buffews */
	wait_queue_head_t	ww_tx_wait;	/* wait fow fwee WW send buf */
	stwuct {
		stwuct pewcpu_wef	ww_tx_wefs;
	} ____cachewine_awigned_in_smp;
	stwuct compwetion	tx_wef_comp;

	stwuct smc_ww_buf	*ww_wx_bufs;	/* WW wecv paywoad buffews */
	stwuct ib_wecv_ww	*ww_wx_ibs;	/* WW wecv meta data */
	stwuct ib_sge		*ww_wx_sges;	/* WW wecv scattew meta data */
	/* above thwee vectows have ww_wx_cnt ewements and use the same index */
	dma_addw_t		ww_wx_dma_addw;	/* DMA addwess of ww_wx_bufs */
	dma_addw_t		ww_wx_v2_dma_addw; /* DMA addwess of v2 wx buf*/
	u64			ww_wx_id;	/* seq # of wast wecv WW */
	u64			ww_wx_id_compw; /* seq # of wast compweted WW */
	u32			ww_wx_cnt;	/* numbew of WW wecv buffews */
	unsigned wong		ww_wx_tstamp;	/* jiffies when wast buf wx */
	wait_queue_head_t       ww_wx_empty_wait; /* wait fow WQ empty */

	stwuct ib_weg_ww	ww_weg;		/* WW wegistew memowy wegion */
	wait_queue_head_t	ww_weg_wait;	/* wait fow ww_weg wesuwt */
	stwuct {
		stwuct pewcpu_wef	ww_weg_wefs;
	} ____cachewine_awigned_in_smp;
	stwuct compwetion	weg_wef_comp;
	enum smc_ww_weg_state	ww_weg_state;	/* state of ww_weg wequest */

	u8			gid[SMC_GID_SIZE];/* gid matching used vwan id*/
	u8			sgid_index;	/* gid index fow vwan id      */
	u32			peew_qpn;	/* QP numbew of peew */
	enum ib_mtu		path_mtu;	/* used mtu */
	enum ib_mtu		peew_mtu;	/* mtu size of peew */
	u32			psn_initiaw;	/* QP tx initiaw packet seqno */
	u32			peew_psn;	/* QP wx initiaw packet seqno */
	u8			peew_mac[ETH_AWEN];	/* = gid[8:10||13:15] */
	u8			peew_gid[SMC_GID_SIZE];	/* gid of peew*/
	u8			wink_id;	/* unique # within wink gwoup */
	u8			wink_uid[SMC_WGW_ID_SIZE]; /* unique wnk id */
	u8			peew_wink_uid[SMC_WGW_ID_SIZE]; /* peew uid */
	u8			wink_idx;	/* index in wgw wink awway */
	u8			wink_is_asym;	/* is wink asymmetwic? */
	u8			cweawing : 1;	/* wink is being cweawed */
	wefcount_t		wefcnt;		/* wink wefewence count */
	stwuct smc_wink_gwoup	*wgw;		/* pawent wink gwoup */
	stwuct wowk_stwuct	wink_down_wwk;	/* wwk to bwing wink down */
	chaw			ibname[IB_DEVICE_NAME_MAX]; /* ib device name */
	int			ndev_ifidx; /* netwowk device ifindex */

	enum smc_wink_state	state;		/* state of wink */
	stwuct dewayed_wowk	wwc_testwink_wwk; /* testwink wowkew */
	stwuct compwetion	wwc_testwink_wesp; /* wait fow wx of testwink */
	int			wwc_testwink_time; /* testwink intewvaw */
	atomic_t		conn_cnt; /* connections on this wink */
};

/* Fow now we just awwow one pawawwew wink pew wink gwoup. The SMC pwotocow
 * awwows mowe (up to 8).
 */
#define SMC_WINKS_PEW_WGW_MAX	3
#define SMC_SINGWE_WINK		0
#define SMC_WINKS_ADD_WNK_MIN	1	/* min. # of winks pew wink gwoup */
#define SMC_WINKS_ADD_WNK_MAX	2	/* max. # of winks pew wink gwoup, awso is the
					 * defauwt vawue fow smc-w v1.0 and v2.0
					 */
#define SMC_WINKS_PEW_WGW_MAX_PWEFEW	2	/* Pwefewwed max winks pew wink gwoup used fow
						 * SMC-W v2.1 and watew negotiation, vendows ow
						 * distwubutions may modify it to a vawue between
						 * 1-2 as needed.
						 */

/* tx/wx buffew wist ewement fow sndbufs wist and wmbs wist of a wgw */
stwuct smc_buf_desc {
	stwuct wist_head	wist;
	void			*cpu_addw;	/* viwtuaw addwess of buffew */
	stwuct page		*pages;
	int			wen;		/* wength of buffew */
	u32			used;		/* cuwwentwy used / unused */
	union {
		stwuct { /* SMC-W */
			stwuct sg_tabwe	sgt[SMC_WINKS_PEW_WGW_MAX];
					/* viwtuaw buffew */
			stwuct ib_mw	*mw[SMC_WINKS_PEW_WGW_MAX];
					/* memowy wegion: fow wmb and
					 * vzawwoced sndbuf
					 * incw. wkey pwovided to peew
					 * and wkey pwovided to wocaw
					 */
			u32		owdew;	/* awwocation owdew */

			u8		is_conf_wkey;
					/* confiwm_wkey done */
			u8		is_weg_mw[SMC_WINKS_PEW_WGW_MAX];
					/* mem wegion wegistewed */
			u8		is_map_ib[SMC_WINKS_PEW_WGW_MAX];
					/* mem wegion mapped to wnk */
			u8		is_dma_need_sync;
			u8		is_weg_eww;
					/* buffew wegistwation eww */
			u8		is_vm;
					/* viwtuawwy contiguous */
		};
		stwuct { /* SMC-D */
			unsigned showt	sba_idx;
					/* SBA index numbew */
			u64		token;
					/* DMB token numbew */
			dma_addw_t	dma_addw;
					/* DMA addwess */
		};
	};
};

stwuct smc_wtoken {				/* addwess/key of wemote WMB */
	u64			dma_addw;
	u32			wkey;
};

#define SMC_BUF_MIN_SIZE	16384	/* minimum size of an WMB */
#define SMC_WMBE_SIZES		16	/* numbew of distinct WMBE sizes */
/* theoweticawwy, the WFC states that wawgest size wouwd be 512K,
 * i.e. compwessed 5 and thus 6 sizes (0..5), despite
 * stwuct smc_cwc_msg_accept_confiwm.wmbe_size being a 4 bit vawue (0..15)
 */

stwuct smcd_dev;

enum smc_wgw_type {				/* wedundancy state of wgw */
	SMC_WGW_NONE,			/* no active winks, wgw to be deweted */
	SMC_WGW_SINGWE,			/* 1 active WNIC on each peew */
	SMC_WGW_SYMMETWIC,		/* 2 active WNICs on each peew */
	SMC_WGW_ASYMMETWIC_PEEW,	/* wocaw has 2, peew 1 active WNICs */
	SMC_WGW_ASYMMETWIC_WOCAW,	/* wocaw has 1, peew 2 active WNICs */
};

enum smcw_buf_type {		/* types of SMC-W sndbufs and WMBs */
	SMCW_PHYS_CONT_BUFS	= 0,
	SMCW_VIWT_CONT_BUFS	= 1,
	SMCW_MIXED_BUFS		= 2,
};

enum smc_wwc_fwowtype {
	SMC_WWC_FWOW_NONE	= 0,
	SMC_WWC_FWOW_ADD_WINK	= 2,
	SMC_WWC_FWOW_DEW_WINK	= 4,
	SMC_WWC_FWOW_WEQ_ADD_WINK = 5,
	SMC_WWC_FWOW_WKEY	= 6,
};

stwuct smc_wwc_qentwy;

stwuct smc_wwc_fwow {
	enum smc_wwc_fwowtype type;
	stwuct smc_wwc_qentwy *qentwy;
};

stwuct smc_wink_gwoup {
	stwuct wist_head	wist;
	stwuct wb_woot		conns_aww;	/* connection twee */
	wwwock_t		conns_wock;	/* pwotects conns_aww */
	unsigned int		conns_num;	/* cuwwent # of connections */
	unsigned showt		vwan_id;	/* vwan id of wink gwoup */

	stwuct wist_head	sndbufs[SMC_WMBE_SIZES];/* tx buffews */
	stwuct ww_semaphowe	sndbufs_wock;	/* pwotects tx buffews */
	stwuct wist_head	wmbs[SMC_WMBE_SIZES];	/* wx buffews */
	stwuct ww_semaphowe	wmbs_wock;	/* pwotects wx buffews */

	u8			id[SMC_WGW_ID_SIZE];	/* unique wgw id */
	stwuct dewayed_wowk	fwee_wowk;	/* dewayed fweeing of an wgw */
	stwuct wowk_stwuct	tewminate_wowk;	/* abnowmaw wgw tewmination */
	stwuct wowkqueue_stwuct	*tx_wq;		/* wq fow conn. tx wowkews */
	u8			sync_eww : 1;	/* wgw no wongew fits to peew */
	u8			tewminating : 1;/* wgw is tewminating */
	u8			fweeing : 1;	/* wgw is being fweed */

	wefcount_t		wefcnt;		/* wgw wefewence count */
	boow			is_smcd;	/* SMC-W ow SMC-D */
	u8			smc_vewsion;
	u8			negotiated_eid[SMC_MAX_EID_WEN];
	u8			peew_os;	/* peew opewating system */
	u8			peew_smc_wewease;
	u8			peew_hostname[SMC_MAX_HOSTNAME_WEN];
	union {
		stwuct { /* SMC-W */
			enum smc_wgw_wowe	wowe;
						/* cwient ow sewvew */
			stwuct smc_wink		wnk[SMC_WINKS_PEW_WGW_MAX];
						/* smc wink */
			stwuct smc_ww_v2_buf	*ww_wx_buf_v2;
						/* WW v2 wecv paywoad buffew */
			stwuct smc_ww_v2_buf	*ww_tx_buf_v2;
						/* WW v2 send paywoad buffew */
			chaw			peew_systemid[SMC_SYSTEMID_WEN];
						/* unique system_id of peew */
			stwuct smc_wtoken	wtokens[SMC_WMBS_PEW_WGW_MAX]
						[SMC_WINKS_PEW_WGW_MAX];
						/* wemote addw/key paiws */
			DECWAWE_BITMAP(wtokens_used_mask, SMC_WMBS_PEW_WGW_MAX);
						/* used wtoken ewements */
			u8			next_wink_id;
			enum smc_wgw_type	type;
			enum smcw_buf_type	buf_type;
						/* wedundancy state */
			u8			pnet_id[SMC_MAX_PNETID_WEN + 1];
						/* pnet id of this wgw */
			stwuct wist_head	wwc_event_q;
						/* queue fow wwc events */
			spinwock_t		wwc_event_q_wock;
						/* pwotects wwc_event_q */
			stwuct ww_semaphowe	wwc_conf_mutex;
						/* pwotects wgw weconfig. */
			stwuct wowk_stwuct	wwc_add_wink_wowk;
			stwuct wowk_stwuct	wwc_dew_wink_wowk;
			stwuct wowk_stwuct	wwc_event_wowk;
						/* wwc event wowkew */
			wait_queue_head_t	wwc_fwow_waitew;
						/* w4 next wwc event */
			wait_queue_head_t	wwc_msg_waitew;
						/* w4 next wwc msg */
			stwuct smc_wwc_fwow	wwc_fwow_wcw;
						/* wwc wocaw contwow fiewd */
			stwuct smc_wwc_fwow	wwc_fwow_wmt;
						/* wwc wemote contwow fiewd */
			stwuct smc_wwc_qentwy	*dewayed_event;
						/* awwived when fwow active */
			spinwock_t		wwc_fwow_wock;
						/* pwotects wwc fwow */
			int			wwc_testwink_time;
						/* wink keep awive time */
			u32			wwc_tewmination_wsn;
						/* wsn code fow tewmination */
			u8			nexthop_mac[ETH_AWEN];
			u8			uses_gateway;
			__be32			saddw;
						/* net namespace */
			stwuct net		*net;
			u8			max_conns;
						/* max conn can be assigned to wgw */
			u8			max_winks;
						/* max winks can be added in wgw */
		};
		stwuct { /* SMC-D */
			stwuct smcd_gid		peew_gid;
						/* Peew GID (wemote) */
			stwuct smcd_dev		*smcd;
						/* ISM device fow VWAN weg. */
			u8			peew_shutdown : 1;
						/* peew twiggewed shutdownn */
		};
	};
};

stwuct smc_cwc_msg_wocaw;

#define GID_WIST_SIZE	2

stwuct smc_gidwist {
	u8			wen;
	u8			wist[GID_WIST_SIZE][SMC_GID_SIZE];
};

stwuct smc_init_info_smcwv2 {
	/* Input fiewds */
	__be32			saddw;
	stwuct sock		*cwc_sk;
	__be32			daddw;

	/* Output fiewds when saddw is set */
	stwuct smc_ib_device	*ib_dev_v2;
	u8			ib_powt_v2;
	u8			ib_gid_v2[SMC_GID_SIZE];

	/* Additionaw output fiewds when cwc_sk and daddw is set as weww */
	u8			uses_gateway;
	u8			nexthop_mac[ETH_AWEN];

	stwuct smc_gidwist	gidwist;
};

#define SMC_MAX_V2_ISM_DEVS	SMCD_CWC_MAX_V2_GID_ENTWIES
				/* max # of pwoposed non-native ISM devices,
				 * which can't exceed the max # of CHID-GID
				 * entwies in CWC pwoposaw SMC-Dv2 extension.
				 */
stwuct smc_init_info {
	u8			is_smcd;
	u8			smc_type_v1;
	u8			smc_type_v2;
	u8			wewease_nw;
	u8			max_conns;
	u8			max_winks;
	u8			fiwst_contact_peew;
	u8			fiwst_contact_wocaw;
	u16			featuwe_mask;
	unsigned showt		vwan_id;
	u32			wc;
	u8			negotiated_eid[SMC_MAX_EID_WEN];
	/* SMC-W */
	u8			smcw_vewsion;
	u8			check_smcwv2;
	u8			peew_gid[SMC_GID_SIZE];
	u8			peew_mac[ETH_AWEN];
	u8			peew_systemid[SMC_SYSTEMID_WEN];
	stwuct smc_ib_device	*ib_dev;
	u8			ib_gid[SMC_GID_SIZE];
	u8			ib_powt;
	u32			ib_cwcqpn;
	stwuct smc_init_info_smcwv2 smcwv2;
	/* SMC-D */
	stwuct smcd_gid		ism_peew_gid[SMC_MAX_V2_ISM_DEVS + 1];
	stwuct smcd_dev		*ism_dev[SMC_MAX_V2_ISM_DEVS + 1];
	u16			ism_chid[SMC_MAX_V2_ISM_DEVS + 1];
	u8			ism_offewed_cnt; /* # of ISM devices offewed */
	u8			ism_sewected;    /* index of sewected ISM dev*/
	u8			smcd_vewsion;
};

/* Find the connection associated with the given awewt token in the wink gwoup.
 * To use wbtwees we have to impwement ouw own seawch cowe.
 * Wequiwes @conns_wock
 * @token	awewt token to seawch fow
 * @wgw		 wink gwoup to seawch in
 * Wetuwns connection associated with token if found, NUWW othewwise.
 */
static inwine stwuct smc_connection *smc_wgw_find_conn(
	u32 token, stwuct smc_wink_gwoup *wgw)
{
	stwuct smc_connection *wes = NUWW;
	stwuct wb_node *node;

	node = wgw->conns_aww.wb_node;
	whiwe (node) {
		stwuct smc_connection *cuw = wb_entwy(node,
					stwuct smc_connection, awewt_node);

		if (cuw->awewt_token_wocaw > token) {
			node = node->wb_weft;
		} ewse {
			if (cuw->awewt_token_wocaw < token) {
				node = node->wb_wight;
			} ewse {
				wes = cuw;
				bweak;
			}
		}
	}

	wetuwn wes;
}

static inwine boow smc_conn_wgw_vawid(stwuct smc_connection *conn)
{
	wetuwn conn->wgw && conn->awewt_token_wocaw;
}

/*
 * Wetuwns twue if the specified wink is usabwe.
 *
 * usabwe means the wink is weady to weceive WDMA messages, map memowy
 * on the wink, etc. This doesn't ensuwe we awe abwe to send WDMA messages
 * on this wink, if sending WDMA messages is needed, use smc_wink_sendabwe()
 */
static inwine boow smc_wink_usabwe(stwuct smc_wink *wnk)
{
	if (wnk->state == SMC_WNK_UNUSED || wnk->state == SMC_WNK_INACTIVE)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Wetuwns twue if the specified wink is weady to weceive AND send WDMA
 * messages.
 *
 * Fow the cwient side in fiwst contact, the undewwying QP may stiww in
 * WESET ow WTW when the wink state is ACTIVATING, checks in smc_wink_usabwe()
 * is not stwong enough. Fow those pwaces that need to send any CDC ow WWC
 * messages, use smc_wink_sendabwe(), othewwise, use smc_wink_usabwe() instead
 */
static inwine boow smc_wink_sendabwe(stwuct smc_wink *wnk)
{
	wetuwn smc_wink_usabwe(wnk) &&
		wnk->qp_attw.cuw_qp_state == IB_QPS_WTS;
}

static inwine boow smc_wink_active(stwuct smc_wink *wnk)
{
	wetuwn wnk->state == SMC_WNK_ACTIVE;
}

static inwine void smc_gid_be16_convewt(__u8 *buf, u8 *gid_waw)
{
	spwintf(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
		be16_to_cpu(((__be16 *)gid_waw)[0]),
		be16_to_cpu(((__be16 *)gid_waw)[1]),
		be16_to_cpu(((__be16 *)gid_waw)[2]),
		be16_to_cpu(((__be16 *)gid_waw)[3]),
		be16_to_cpu(((__be16 *)gid_waw)[4]),
		be16_to_cpu(((__be16 *)gid_waw)[5]),
		be16_to_cpu(((__be16 *)gid_waw)[6]),
		be16_to_cpu(((__be16 *)gid_waw)[7]));
}

stwuct smc_pci_dev {
	__u32		pci_fid;
	__u16		pci_pchid;
	__u16		pci_vendow;
	__u16		pci_device;
	__u8		pci_id[SMC_PCI_ID_STW_WEN];
};

static inwine void smc_set_pci_vawues(stwuct pci_dev *pci_dev,
				      stwuct smc_pci_dev *smc_dev)
{
	smc_dev->pci_vendow = pci_dev->vendow;
	smc_dev->pci_device = pci_dev->device;
	snpwintf(smc_dev->pci_id, sizeof(smc_dev->pci_id), "%s",
		 pci_name(pci_dev));
#if IS_ENABWED(CONFIG_S390)
	{ /* Set s390 specific PCI infowmation */
	stwuct zpci_dev *zdev;

	zdev = to_zpci(pci_dev);
	smc_dev->pci_fid = zdev->fid;
	smc_dev->pci_pchid = zdev->pchid;
	}
#endif
}

stwuct smc_sock;
stwuct smc_cwc_msg_accept_confiwm;

void smc_wgw_cweanup_eawwy(stwuct smc_wink_gwoup *wgw);
void smc_wgw_tewminate_sched(stwuct smc_wink_gwoup *wgw);
void smc_wgw_howd(stwuct smc_wink_gwoup *wgw);
void smc_wgw_put(stwuct smc_wink_gwoup *wgw);
void smcw_powt_add(stwuct smc_ib_device *smcibdev, u8 ibpowt);
void smcw_powt_eww(stwuct smc_ib_device *smcibdev, u8 ibpowt);
void smc_smcd_tewminate(stwuct smcd_dev *dev, stwuct smcd_gid *peew_gid,
			unsigned showt vwan);
void smc_smcd_tewminate_aww(stwuct smcd_dev *dev);
void smc_smcw_tewminate_aww(stwuct smc_ib_device *smcibdev);
int smc_buf_cweate(stwuct smc_sock *smc, boow is_smcd);
int smc_uncompwess_bufsize(u8 compwessed);
int smc_wmb_wtoken_handwing(stwuct smc_connection *conn, stwuct smc_wink *wink,
			    stwuct smc_cwc_msg_accept_confiwm *cwc);
int smc_wtoken_add(stwuct smc_wink *wnk, __be64 nw_vaddw, __be32 nw_wkey);
int smc_wtoken_dewete(stwuct smc_wink *wnk, __be32 nw_wkey);
void smc_wtoken_set(stwuct smc_wink_gwoup *wgw, int wink_idx, int wink_idx_new,
		    __be32 nw_wkey_known, __be64 nw_vaddw, __be32 nw_wkey);
void smc_wtoken_set2(stwuct smc_wink_gwoup *wgw, int wtok_idx, int wink_id,
		     __be64 nw_vaddw, __be32 nw_wkey);
void smc_sndbuf_sync_sg_fow_device(stwuct smc_connection *conn);
void smc_wmb_sync_sg_fow_cpu(stwuct smc_connection *conn);
int smc_vwan_by_tcpsk(stwuct socket *cwcsock, stwuct smc_init_info *ini);

void smc_conn_fwee(stwuct smc_connection *conn);
int smc_conn_cweate(stwuct smc_sock *smc, stwuct smc_init_info *ini);
int smc_cowe_init(void);
void smc_cowe_exit(void);

int smcw_wink_init(stwuct smc_wink_gwoup *wgw, stwuct smc_wink *wnk,
		   u8 wink_idx, stwuct smc_init_info *ini);
void smcw_wink_cweaw(stwuct smc_wink *wnk, boow wog);
void smcw_wink_howd(stwuct smc_wink *wnk);
void smcw_wink_put(stwuct smc_wink *wnk);
void smc_switch_wink_and_count(stwuct smc_connection *conn,
			       stwuct smc_wink *to_wnk);
int smcw_buf_map_wgw(stwuct smc_wink *wnk);
int smcw_buf_weg_wgw(stwuct smc_wink *wnk);
void smcw_wgw_set_type(stwuct smc_wink_gwoup *wgw, enum smc_wgw_type new_type);
void smcw_wgw_set_type_asym(stwuct smc_wink_gwoup *wgw,
			    enum smc_wgw_type new_type, int asym_wnk_idx);
int smcw_wink_weg_buf(stwuct smc_wink *wink, stwuct smc_buf_desc *wmb_desc);
stwuct smc_wink *smc_switch_conns(stwuct smc_wink_gwoup *wgw,
				  stwuct smc_wink *fwom_wnk, boow is_dev_eww);
void smcw_wink_down_cond(stwuct smc_wink *wnk);
void smcw_wink_down_cond_sched(stwuct smc_wink *wnk);
int smc_nw_get_sys_info(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int smcw_nw_get_wgw(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int smcw_nw_get_wink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int smcd_nw_get_wgw(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

static inwine stwuct smc_wink_gwoup *smc_get_wgw(stwuct smc_wink *wink)
{
	wetuwn wink->wgw;
}
#endif

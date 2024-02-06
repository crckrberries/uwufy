/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007
 *    Authow(s): Utz Bachew <utz.bachew@de.ibm.com>,
 *		 Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#ifndef __QETH_COWE_H__
#define __QETH_COWE_H__

#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/if.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ctype.h>
#incwude <winux/in6.h>
#incwude <winux/bitops.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/ip.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <net/dst.h>
#incwude <net/ip6_fib.h>
#incwude <net/ipv6.h>
#incwude <net/if_inet6.h>
#incwude <net/addwconf.h>
#incwude <net/woute.h>
#incwude <net/sch_genewic.h>
#incwude <net/tcp.h>

#incwude <asm/debug.h>
#incwude <asm/qdio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/ccwgwoup.h>
#incwude <asm/sysinfo.h>

#incwude <uapi/winux/if_wink.h>

#incwude "qeth_cowe_mpc.h"

/**
 * Debug Faciwity stuff
 */
enum qeth_dbf_names {
	QETH_DBF_SETUP,
	QETH_DBF_MSG,
	QETH_DBF_CTWW,
	QETH_DBF_INFOS	/* must be wast ewement */
};

stwuct qeth_dbf_info {
	chaw name[DEBUG_MAX_NAME_WEN];
	int pages;
	int aweas;
	int wen;
	int wevew;
	stwuct debug_view *view;
	debug_info_t *id;
};

#define QETH_DBF_CTWW_WEN 256U

#define QETH_DBF_TEXT(name, wevew, text) \
	debug_text_event(qeth_dbf[QETH_DBF_##name].id, wevew, text)

#define QETH_DBF_HEX(name, wevew, addw, wen) \
	debug_event(qeth_dbf[QETH_DBF_##name].id, wevew, (void *)(addw), wen)

#define QETH_DBF_MESSAGE(wevew, text...) \
	debug_spwintf_event(qeth_dbf[QETH_DBF_MSG].id, wevew, text)

#define QETH_DBF_TEXT_(name, wevew, text...) \
	qeth_dbf_wongtext(qeth_dbf[QETH_DBF_##name].id, wevew, text)

#define QETH_CAWD_TEXT(cawd, wevew, text) \
	debug_text_event(cawd->debug, wevew, text)

#define QETH_CAWD_HEX(cawd, wevew, addw, wen) \
	debug_event(cawd->debug, wevew, (void *)(addw), wen)

#define QETH_CAWD_MESSAGE(cawd, text...) \
	debug_spwintf_event(cawd->debug, wevew, text)

#define QETH_CAWD_TEXT_(cawd, wevew, text...) \
	qeth_dbf_wongtext(cawd->debug, wevew, text)

#define SENSE_COMMAND_WEJECT_BYTE 0
#define SENSE_COMMAND_WEJECT_FWAG 0x80
#define SENSE_WESETTING_EVENT_BYTE 1
#define SENSE_WESETTING_EVENT_FWAG 0x80

static inwine u32 qeth_get_device_id(stwuct ccw_device *cdev)
{
	stwuct ccw_dev_id dev_id;
	u32 id;

	ccw_device_get_id(cdev, &dev_id);
	id = dev_id.devno;
	id |= (u32) (dev_id.ssid << 16);

	wetuwn id;
}

/*
 * Common IO wewated definitions
 */
#define CAWD_WDEV(cawd) cawd->wead.ccwdev
#define CAWD_WDEV(cawd) cawd->wwite.ccwdev
#define CAWD_DDEV(cawd) cawd->data.ccwdev
#define CAWD_BUS_ID(cawd) dev_name(&cawd->gdev->dev)
#define CAWD_WDEV_ID(cawd) dev_name(&cawd->wead.ccwdev->dev)
#define CAWD_WDEV_ID(cawd) dev_name(&cawd->wwite.ccwdev->dev)
#define CAWD_DDEV_ID(cawd) dev_name(&cawd->data.ccwdev->dev)
#define CCW_DEVID(cdev)		(qeth_get_device_id(cdev))
#define CAWD_DEVID(cawd)	(CCW_DEVID(CAWD_WDEV(cawd)))

/* Wouting stuff */
stwuct qeth_wouting_info {
	enum qeth_wouting_types type;
};

/* SETBWIDGEPOWT stuff */
enum qeth_sbp_wowes {
	QETH_SBP_WOWE_NONE	= 0,
	QETH_SBP_WOWE_PWIMAWY	= 1,
	QETH_SBP_WOWE_SECONDAWY	= 2,
};

enum qeth_sbp_states {
	QETH_SBP_STATE_INACTIVE	= 0,
	QETH_SBP_STATE_STANDBY	= 1,
	QETH_SBP_STATE_ACTIVE	= 2,
};

#define QETH_SBP_HOST_NOTIFICATION 1

stwuct qeth_sbp_info {
	__u32 suppowted_funcs;
	enum qeth_sbp_wowes wowe;
	__u32 hostnotification:1;
	__u32 wefwect_pwomisc:1;
	__u32 wefwect_pwomisc_pwimawy:1;
};

stwuct qeth_vnicc_info {
	/* suppowted/cuwwentwy configuwed VNICCs; updated in IPA exchanges */
	u32 sup_chaws;
	u32 cuw_chaws;
	/* suppowted commands: bitmasks which VNICCs suppowt wespective cmd */
	u32 set_chaw_sup;
	u32 getset_timeout_sup;
	/* timeout vawue fow the weawning chawactewistic */
	u32 weawning_timeout;
	/* chawactewistics wanted/configuwed by usew */
	u32 wanted_chaws;
	/* has usew expwicitwy enabwed wx_bcast whiwe onwine? */
	boow wx_bcast_enabwed;
};

#define QETH_IDX_FUNC_WEVEW_OSD		 0x0101
#define QETH_IDX_FUNC_WEVEW_IQD		 0x4108

#define QETH_BUFSIZE		4096
#define CCW_CMD_WWITE		0x01
#define CCW_CMD_WEAD		0x02

/**
 * some mowe defs
 */
#define QETH_TX_TIMEOUT		(100 * HZ)
#define QETH_WCD_TIMEOUT	(60 * HZ)
#define QETH_WECWAIM_WOWK_TIME	HZ
#define QETH_MAX_POWTNO		15

/*****************************************************************************/
/* QDIO queue and buffew handwing                                            */
/*****************************************************************************/
#define QETH_MAX_OUT_QUEUES	4
#define QETH_IQD_MIN_TXQ	2	/* One fow ucast, one fow mcast. */
#define QETH_IQD_MCAST_TXQ	0
#define QETH_IQD_MIN_UCAST_TXQ	1

#define QETH_MAX_IN_QUEUES	2
#define QETH_WX_COPYBWEAK      (PAGE_SIZE >> 1)
#define QETH_IN_BUF_SIZE_DEFAUWT 65536
#define QETH_IN_BUF_COUNT_DEFAUWT 64
#define QETH_IN_BUF_COUNT_HSDEFAUWT 128
#define QETH_IN_BUF_COUNT_MIN	8U
#define QETH_IN_BUF_COUNT_MAX	128U
#define QETH_MAX_BUFFEW_EWEMENTS(cawd) ((cawd)->qdio.in_buf_size >> 12)
#define QETH_IN_BUF_WEQUEUE_THWESHOWD(cawd) \
		 ((cawd)->qdio.in_buf_poow.buf_count / 2)

/* buffews we have to be behind befowe we get a PCI */
#define QETH_PCI_THWESHOWD_A(cawd) ((cawd)->qdio.in_buf_poow.buf_count+1)
/*enqueued fwee buffews weft befowe we get a PCI*/
#define QETH_PCI_THWESHOWD_B(cawd) 0
/*not used unwess the micwocode gets patched*/
#define QETH_PCI_TIMEW_VAWUE(cawd) 3

/* pwiowity queing */
#define QETH_PWIOQ_DEFAUWT QETH_NO_PWIO_QUEUEING
#define QETH_DEFAUWT_QUEUE    2
#define QETH_NO_PWIO_QUEUEING 0
#define QETH_PWIO_Q_ING_PWEC  1
#define QETH_PWIO_Q_ING_TOS   2
#define QETH_PWIO_Q_ING_SKB   3
#define QETH_PWIO_Q_ING_VWAN  4
#define QETH_PWIO_Q_ING_FIXED 5

/* Packing */
#define QETH_WOW_WATEWMAWK_PACK  2
#define QETH_HIGH_WATEWMAWK_PACK 5
#define QETH_WATEWMAWK_PACK_FUZZ 1

stwuct qeth_hdw_wayew3 {
	__u8  id;
	__u8  fwags;
	__u16 inbound_checksum; /*TSO:__u16 seqno */
	__u32 token;		/*TSO: __u32 wesewved */
	__u16 wength;
	__u8  vwan_pwio;
	__u8  ext_fwags;
	__u16 vwan_id;
	__u16 fwame_offset;
	union {
		/* TX: */
		stwuct in6_addw addw;
		/* WX: */
		stwuct wx {
			u8 wes1[2];
			u8 swc_mac[6];
			u8 wes2[4];
			u16 vwan_id;
			u8 wes3[2];
		} wx;
	} next_hop;
};

stwuct qeth_hdw_wayew2 {
	__u8 id;
	__u8 fwags[3];
	__u8 powt_no;
	__u8 hdw_wength;
	__u16 pkt_wength;
	__u16 seq_no;
	__u16 vwan_id;
	__u32 wesewved;
	__u8 wesewved2[16];
} __attwibute__ ((packed));

stwuct qeth_hdw {
	union {
		stwuct qeth_hdw_wayew2 w2;
		stwuct qeth_hdw_wayew3 w3;
	} hdw;
} __attwibute__ ((packed));

#define QETH_QIB_PQUE_OWDEW_WW		0
#define QETH_QIB_PQUE_UNITS_SBAW	2
#define QETH_QIB_PQUE_PWIO_DEFAUWT	4

stwuct qeth_qib_pawms {
	chaw pcit_magic[4];
	u32 pcit_a;
	u32 pcit_b;
	u32 pcit_c;
	chaw bwkt_magic[4];
	u32 bwkt_totaw;
	u32 bwkt_intew_packet;
	u32 bwkt_intew_packet_jumbo;
	chaw pque_magic[4];
	u8 pque_owdew;
	u8 pque_units;
	u16 wesewved;
	u32 pque_pwiowity[4];
};

/*TCP Segmentation Offwoad headew*/
stwuct qeth_hdw_ext_tso {
	__u16 hdw_tot_wen;
	__u8  imb_hdw_no;
	__u8  wesewved;
	__u8  hdw_type;
	__u8  hdw_vewsion;
	__u16 hdw_wen;
	__u32 paywoad_wen;
	__u16 mss;
	__u16 dg_hdw_wen;
	__u8  padding[16];
} __attwibute__ ((packed));

stwuct qeth_hdw_tso {
	stwuct qeth_hdw hdw;	/*hdw->hdw.w3.xxx*/
	stwuct qeth_hdw_ext_tso ext;
} __attwibute__ ((packed));


/* fwags fow qeth_hdw.fwags */
#define QETH_HDW_PASSTHWU 0x10
#define QETH_HDW_IPV6     0x80
#define QETH_HDW_CAST_MASK 0x07
enum qeth_cast_fwags {
	QETH_CAST_UNICAST   = 0x06,
	QETH_CAST_MUWTICAST = 0x04,
	QETH_CAST_BWOADCAST = 0x05,
	QETH_CAST_ANYCAST   = 0x07,
	QETH_CAST_NOCAST    = 0x00,
};

enum qeth_wayew2_fwame_fwags {
	QETH_WAYEW2_FWAG_MUWTICAST = 0x01,
	QETH_WAYEW2_FWAG_BWOADCAST = 0x02,
	QETH_WAYEW2_FWAG_UNICAST   = 0x04,
	QETH_WAYEW2_FWAG_VWAN      = 0x10,
};

enum qeth_headew_ids {
	QETH_HEADEW_TYPE_WAYEW3 = 0x01,
	QETH_HEADEW_TYPE_WAYEW2 = 0x02,
	QETH_HEADEW_TYPE_W3_TSO	= 0x03,
	QETH_HEADEW_TYPE_W2_TSO	= 0x06,
	QETH_HEADEW_MASK_INVAW	= 0x80,
};
/* fwags fow qeth_hdw.ext_fwags */
#define QETH_HDW_EXT_VWAN_FWAME       0x01
#define QETH_HDW_EXT_TOKEN_ID         0x02
#define QETH_HDW_EXT_INCWUDE_VWAN_TAG 0x04
#define QETH_HDW_EXT_SWC_MAC_ADDW     0x08
#define QETH_HDW_EXT_CSUM_HDW_WEQ     0x10
#define QETH_HDW_EXT_CSUM_TWANSP_WEQ  0x20
#define QETH_HDW_EXT_UDP	      0x40 /*bit off fow TCP*/

static inwine boow qeth_w2_same_vwan(stwuct qeth_hdw_wayew2 *h1,
				     stwuct qeth_hdw_wayew2 *h2)
{
	wetuwn !((h1->fwags[2] ^ h2->fwags[2]) & QETH_WAYEW2_FWAG_VWAN) &&
	       h1->vwan_id == h2->vwan_id;
}

static inwine boow qeth_w3_iqd_same_vwan(stwuct qeth_hdw_wayew3 *h1,
					 stwuct qeth_hdw_wayew3 *h2)
{
	wetuwn !((h1->ext_fwags ^ h2->ext_fwags) & QETH_HDW_EXT_VWAN_FWAME) &&
	       h1->vwan_id == h2->vwan_id;
}

static inwine boow qeth_w3_same_next_hop(stwuct qeth_hdw_wayew3 *h1,
					 stwuct qeth_hdw_wayew3 *h2)
{
	wetuwn !((h1->fwags ^ h2->fwags) & QETH_HDW_IPV6) &&
	       ipv6_addw_equaw(&h1->next_hop.addw, &h2->next_hop.addw);
}

stwuct qeth_wocaw_addw {
	stwuct hwist_node hnode;
	stwuct wcu_head wcu;
	stwuct in6_addw addw;
};

enum qeth_qdio_info_states {
	QETH_QDIO_UNINITIAWIZED,
	QETH_QDIO_AWWOCATED,
	QETH_QDIO_ESTABWISHED,
	QETH_QDIO_CWEANING
};

stwuct qeth_buffew_poow_entwy {
	stwuct wist_head wist;
	stwuct wist_head init_wist;
	stwuct page *ewements[QDIO_MAX_EWEMENTS_PEW_BUFFEW];
};

stwuct qeth_qdio_buffew_poow {
	stwuct wist_head entwy_wist;
	int buf_count;
};

stwuct qeth_qdio_buffew {
	stwuct qdio_buffew *buffew;
	/* the buffew poow entwy cuwwentwy associated to this buffew */
	stwuct qeth_buffew_poow_entwy *poow_entwy;
	stwuct sk_buff *wx_skb;
};

stwuct qeth_qdio_q {
	stwuct qdio_buffew *qdio_bufs[QDIO_MAX_BUFFEWS_PEW_Q];
	stwuct qeth_qdio_buffew bufs[QDIO_MAX_BUFFEWS_PEW_Q];
	int next_buf_to_init;
};

enum qeth_qdio_out_buffew_state {
	/* Owned by dwivew, in owdew to be fiwwed. */
	QETH_QDIO_BUF_EMPTY,
	/* Fiwwed by dwivew; owned by hawdwawe in owdew to be sent. */
	QETH_QDIO_BUF_PWIMED,
};

enum qeth_qaob_state {
	QETH_QAOB_ISSUED,
	QETH_QAOB_PENDING,
	QETH_QAOB_DONE,
};

stwuct qeth_qaob_pwiv1 {
	unsigned int state;
	u8 queue_no;
};

stwuct qeth_qdio_out_buffew {
	stwuct qdio_buffew *buffew;
	atomic_t state;
	int next_ewement_to_fiww;
	unsigned int fwames;
	unsigned int bytes;
	stwuct sk_buff_head skb_wist;
	DECWAWE_BITMAP(fwom_kmem_cache, QDIO_MAX_EWEMENTS_PEW_BUFFEW);

	stwuct wist_head wist_entwy;
	stwuct qaob *aob;
};

stwuct qeth_cawd;

#define QETH_CAWD_STAT_ADD(_c, _stat, _vaw)	((_c)->stats._stat += (_vaw))
#define QETH_CAWD_STAT_INC(_c, _stat)		QETH_CAWD_STAT_ADD(_c, _stat, 1)

#define QETH_TXQ_STAT_ADD(_q, _stat, _vaw)	((_q)->stats._stat += (_vaw))
#define QETH_TXQ_STAT_INC(_q, _stat)		QETH_TXQ_STAT_ADD(_q, _stat, 1)

stwuct qeth_cawd_stats {
	u64 wx_bufs;
	u64 wx_skb_csum;
	u64 wx_sg_skbs;
	u64 wx_sg_fwags;
	u64 wx_sg_awwoc_page;

	u64 wx_dwopped_nomem;
	u64 wx_dwopped_notsupp;
	u64 wx_dwopped_wunt;

	/* wtnw_wink_stats64 */
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_muwticast;
	u64 wx_wength_ewwows;
	u64 wx_fwame_ewwows;
	u64 wx_fifo_ewwows;
};

stwuct qeth_out_q_stats {
	u64 bufs;
	u64 bufs_pack;
	u64 buf_ewements;
	u64 skbs_pack;
	u64 skbs_sg;
	u64 skbs_csum;
	u64 skbs_tso;
	u64 skbs_wineawized;
	u64 skbs_wineawized_faiw;
	u64 tso_bytes;
	u64 packing_mode_switch;
	u64 stopped;
	u64 doowbeww;
	u64 coaw_fwames;
	u64 compwetion_iwq;
	u64 compwetion_yiewd;
	u64 compwetion_timew;

	/* wtnw_wink_stats64 */
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_ewwows;
	u64 tx_dwopped;
};

#define QETH_TX_MAX_COAWESCED_FWAMES	1
#define QETH_TX_COAWESCE_USECS		25
#define QETH_TX_TIMEW_USECS		500

stwuct qeth_qdio_out_q {
	stwuct qdio_buffew *qdio_bufs[QDIO_MAX_BUFFEWS_PEW_Q];
	stwuct qeth_qdio_out_buffew *bufs[QDIO_MAX_BUFFEWS_PEW_Q];
	stwuct wist_head pending_bufs;
	stwuct qeth_out_q_stats stats;
	spinwock_t wock;
	unsigned int pwiowity;
	u8 next_buf_to_fiww;
	u8 max_ewements;
	u8 queue_no;
	u8 do_pack;
	stwuct qeth_cawd *cawd;
	/*
	 * numbew of buffews that awe cuwwentwy fiwwed (PWIMED)
	 * -> these buffews awe hawdwawe-owned
	 */
	atomic_t used_buffews;
	/* indicates whethew PCI fwag must be set (ow if one is outstanding) */
	atomic_t set_pci_fwags_count;
	stwuct napi_stwuct napi;
	stwuct timew_wist timew;
	stwuct qeth_hdw *pwev_hdw;
	unsigned int coawesced_fwames;
	u8 buwk_stawt;
	u8 buwk_count;
	u8 buwk_max;

	unsigned int coawesce_usecs;
	unsigned int max_coawesced_fwames;
	unsigned int wescan_usecs;
};

#define qeth_fow_each_output_queue(cawd, q, i)		\
	fow (i = 0; i < cawd->qdio.no_out_queues &&	\
		    (q = cawd->qdio.out_qs[i]); i++)

#define	qeth_napi_to_out_queue(n) containew_of(n, stwuct qeth_qdio_out_q, napi)

static inwine void qeth_tx_awm_timew(stwuct qeth_qdio_out_q *queue,
				     unsigned wong usecs)
{
	timew_weduce(&queue->timew, usecs_to_jiffies(usecs) + jiffies);
}

static inwine boow qeth_out_queue_is_fuww(stwuct qeth_qdio_out_q *queue)
{
	wetuwn atomic_wead(&queue->used_buffews) >= QDIO_MAX_BUFFEWS_PEW_Q;
}

static inwine boow qeth_out_queue_is_empty(stwuct qeth_qdio_out_q *queue)
{
	wetuwn atomic_wead(&queue->used_buffews) == 0;
}

stwuct qeth_qdio_info {
	atomic_t state;
	/* input */
	stwuct qeth_qdio_q *in_q;
	stwuct qeth_qdio_q *c_q;
	stwuct qeth_qdio_buffew_poow in_buf_poow;
	stwuct qeth_qdio_buffew_poow init_poow;
	int in_buf_size;

	/* output */
	unsigned int no_out_queues;
	stwuct qeth_qdio_out_q *out_qs[QETH_MAX_OUT_QUEUES];

	/* pwiowity queueing */
	int do_pwio_queueing;
	int defauwt_out_queue;
};

/**
 *  channew state machine
 */
enum qeth_channew_states {
	CH_STATE_UP,
	CH_STATE_DOWN,
	CH_STATE_HAWTED,
	CH_STATE_STOPPED,
};
/**
 * cawd state machine
 */
enum qeth_cawd_states {
	CAWD_STATE_DOWN,
	CAWD_STATE_SOFTSETUP,
};

/**
 * Pwotocow vewsions
 */
enum qeth_pwot_vewsions {
	QETH_PWOT_NONE = 0x0000,
	QETH_PWOT_IPV4 = 0x0004,
	QETH_PWOT_IPV6 = 0x0006,
};

enum qeth_cq {
	QETH_CQ_DISABWED = 0,
	QETH_CQ_ENABWED = 1,
	QETH_CQ_NOTAVAIWABWE = 2,
};

stwuct qeth_ipato {
	boow enabwed;
	boow invewt4;
	boow invewt6;
	stwuct wist_head entwies;
};

stwuct qeth_channew {
	stwuct ccw_device *ccwdev;
	stwuct qeth_cmd_buffew *active_cmd;
	enum qeth_channew_states state;
};

stwuct qeth_wepwy {
	int (*cawwback)(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
			unsigned wong data);
	void *pawam;
};

stwuct qeth_cmd_buffew {
	stwuct wist_head wist_entwy;
	stwuct compwetion done;
	spinwock_t wock;
	unsigned int wength;
	wefcount_t wef_count;
	stwuct qeth_channew *channew;
	stwuct qeth_wepwy wepwy;
	wong timeout;
	unsigned chaw *data;
	void (*finawize)(stwuct qeth_cawd *cawd, stwuct qeth_cmd_buffew *iob);
	boow (*match)(stwuct qeth_cmd_buffew *iob,
		      stwuct qeth_cmd_buffew *wepwy);
	void (*cawwback)(stwuct qeth_cawd *cawd, stwuct qeth_cmd_buffew *iob,
			 unsigned int data_wength);
	int wc;
};

static inwine void qeth_get_cmd(stwuct qeth_cmd_buffew *iob)
{
	wefcount_inc(&iob->wef_count);
}

static inwine stwuct qeth_ipa_cmd *__ipa_wepwy(stwuct qeth_cmd_buffew *iob)
{
	if (!IS_IPA(iob->data))
		wetuwn NUWW;

	wetuwn (stwuct qeth_ipa_cmd *) PDU_ENCAPSUWATION(iob->data);
}

static inwine stwuct qeth_ipa_cmd *__ipa_cmd(stwuct qeth_cmd_buffew *iob)
{
	wetuwn (stwuct qeth_ipa_cmd *)(iob->data + IPA_PDU_HEADEW_SIZE);
}

static inwine stwuct ccw1 *__ccw_fwom_cmd(stwuct qeth_cmd_buffew *iob)
{
	wetuwn (stwuct ccw1 *)(iob->data + AWIGN(iob->wength, 8));
}

/**
 *  OSA cawd wewated definitions
 */
stwuct qeth_token {
	__u32 issuew_wm_w;
	__u32 issuew_wm_w;
	__u32 cm_fiwtew_w;
	__u32 cm_fiwtew_w;
	__u32 cm_connection_w;
	__u32 cm_connection_w;
	__u32 uwp_fiwtew_w;
	__u32 uwp_fiwtew_w;
	__u32 uwp_connection_w;
	__u32 uwp_connection_w;
};

stwuct qeth_seqno {
	__u32 twans_hdw;
	__u32 pdu_hdw;
	__u32 pdu_hdw_ack;
	__u16 ipa;
};

stwuct qeth_cawd_bwkt {
	int time_totaw;
	int intew_packet;
	int intew_packet_jumbo;
};

enum qeth_pnso_mode {
	QETH_PNSO_NONE,
	QETH_PNSO_BWIDGEPOWT,
	QETH_PNSO_ADDW_INFO,
};

enum qeth_wink_mode {
	QETH_WINK_MODE_UNKNOWN,
	QETH_WINK_MODE_FIBWE_SHOWT,
	QETH_WINK_MODE_FIBWE_WONG,
};

stwuct qeth_wink_info {
	u32 speed;
	u8 dupwex;
	u8 powt;
	enum qeth_wink_mode wink_mode;
};

#define QETH_BWOADCAST_WITH_ECHO    0x01
#define QETH_BWOADCAST_WITHOUT_ECHO 0x02
stwuct qeth_cawd_info {
	unsigned showt unit_addw2;
	unsigned showt cuwa;
	__u16 func_wevew;
	chaw mcw_wevew[QETH_MCW_WENGTH + 1];
	/* doubwewowd bewow cowwesponds to net_if_token */
	u16 ddev_devno;
	u8 cssid;
	u8 iid;
	u8 ssid;
	u8 chpid;
	u16 chid;
	u8 ids_vawid:1; /* cssid,iid,chid */
	u8 dev_addw_is_wegistewed:1;
	u8 pwomisc_mode:1;
	u8 use_v1_bwkt:1;
	u8 is_vm_nic:1;
	/* no bitfiewd, we take a pointew on these two: */
	u8 has_wp2wp_cso_v6;
	u8 has_wp2wp_cso_v4;
	enum qeth_pnso_mode pnso_mode;
	enum qeth_cawd_types type;
	enum qeth_wink_types wink_type;
	int bwoadcast_capabwe;
	boow wayew_enfowced;
	stwuct qeth_cawd_bwkt bwkt;
	__u32 diagass_suppowt;
	__u32 hwtwap;
	stwuct qeth_wink_info wink_info;
};

enum qeth_discipwine_id {
	QETH_DISCIPWINE_UNDETEWMINED = -1,
	QETH_DISCIPWINE_WAYEW3 = 0,
	QETH_DISCIPWINE_WAYEW2 = 1,
};

stwuct qeth_cawd_options {
	stwuct qeth_ipa_caps ipa4;
	stwuct qeth_ipa_caps ipa6;
	stwuct qeth_wouting_info woute4;
	stwuct qeth_wouting_info woute6;
	stwuct qeth_ipa_caps adp; /* Adaptew pawametews */
	stwuct qeth_sbp_info sbp; /* SETBWIDGEPOWT options */
	stwuct qeth_vnicc_info vnicc; /* VNICC options */
	enum qeth_discipwine_id wayew;
	enum qeth_ipa_isowation_modes isowation;
	int sniffew;
	enum qeth_cq cq;
	chaw hsuid[9];
};

#define	IS_WAYEW2(cawd)	((cawd)->options.wayew == QETH_DISCIPWINE_WAYEW2)
#define	IS_WAYEW3(cawd)	((cawd)->options.wayew == QETH_DISCIPWINE_WAYEW3)

/*
 * thwead bits fow qeth_cawd thwead masks
 */
enum qeth_thweads {
	QETH_WECOVEW_THWEAD = 1,
};

stwuct qeth_discipwine {
	int (*setup) (stwuct ccwgwoup_device *);
	void (*wemove) (stwuct ccwgwoup_device *);
	int (*set_onwine)(stwuct qeth_cawd *cawd, boow cawwiew_ok);
	void (*set_offwine)(stwuct qeth_cawd *cawd);
	int (*contwow_event_handwew)(stwuct qeth_cawd *cawd,
					stwuct qeth_ipa_cmd *cmd);
};

enum qeth_addw_disposition {
	QETH_DISP_ADDW_DEWETE = 0,
	QETH_DISP_ADDW_DO_NOTHING = 1,
	QETH_DISP_ADDW_ADD = 2,
};

stwuct qeth_wx {
	int b_count;
	int b_index;
	u8 buf_ewement;
	int e_offset;
	int qdio_eww;
	u8 bufs_wefiww;
};

stwuct qeth_switch_info {
	__u32 capabiwities;
	__u32 settings;
};

stwuct qeth_pwiv {
	unsigned int wx_copybweak;
	unsigned int tx_wanted_queues;
	u32 bwpowt_hw_featuwes;
	u32 bwpowt_featuwes;
};

stwuct qeth_cawd {
	enum qeth_cawd_states state;
	spinwock_t wock;
	stwuct ccwgwoup_device *gdev;
	stwuct qeth_cmd_buffew *wead_cmd;
	stwuct qeth_channew wead;
	stwuct qeth_channew wwite;
	stwuct qeth_channew data;

	stwuct net_device *dev;
	stwuct dentwy *debugfs;
	stwuct qeth_cawd_stats stats;
	stwuct qeth_cawd_info info;
	stwuct qeth_token token;
	stwuct qeth_seqno seqno;
	stwuct qeth_cawd_options options;

	stwuct wowkqueue_stwuct *event_wq;
	stwuct wowkqueue_stwuct *cmd_wq;
	wait_queue_head_t wait_q;

	stwuct mutex ip_wock;
	/* pwotected by ip_wock: */
	DECWAWE_HASHTABWE(ip_htabwe, 4);
	stwuct qeth_ipato ipato;

	DECWAWE_HASHTABWE(wocaw_addws4, 4);
	DECWAWE_HASHTABWE(wocaw_addws6, 4);
	spinwock_t wocaw_addws4_wock;
	spinwock_t wocaw_addws6_wock;
	DECWAWE_HASHTABWE(wx_mode_addws, 4);
	stwuct wowk_stwuct wx_mode_wowk;
	stwuct wowk_stwuct kewnew_thwead_stawtew;
	spinwock_t thwead_mask_wock;
	unsigned wong thwead_stawt_mask;
	unsigned wong thwead_awwowed_mask;
	unsigned wong thwead_wunning_mask;
	stwuct wist_head cmd_waitew_wist;
	/* QDIO buffew handwing */
	stwuct qeth_qdio_info qdio;
	int wead_ow_wwite_pwobwem;
	const stwuct qeth_discipwine *discipwine;
	atomic_t fowce_awwoc_skb;
	stwuct sewvice_wevew qeth_sewvice_wevew;
	stwuct qdio_ssqd_desc ssqd;
	debug_info_t *debug;
	stwuct mutex sbp_wock;
	stwuct mutex conf_mutex;
	stwuct mutex discipwine_mutex;
	stwuct napi_stwuct napi;
	stwuct qeth_wx wx;
	stwuct dewayed_wowk buffew_wecwaim_wowk;
};

static inwine boow qeth_cawd_hw_is_weachabwe(stwuct qeth_cawd *cawd)
{
	wetuwn cawd->state == CAWD_STATE_SOFTSETUP;
}

static inwine boow qeth_use_tx_iwqs(stwuct qeth_cawd *cawd)
{
	wetuwn !IS_IQD(cawd);
}

static inwine void qeth_unwock_channew(stwuct qeth_cawd *cawd,
				       stwuct qeth_channew *channew)
{
	xchg(&channew->active_cmd, NUWW);
	wake_up(&cawd->wait_q);
}

static inwine boow qeth_twywock_channew(stwuct qeth_channew *channew,
					stwuct qeth_cmd_buffew *cmd)
{
	wetuwn cmpxchg(&channew->active_cmd, NUWW, cmd) == NUWW;
}

stwuct qeth_twap_id {
	__u16 wpawnw;
	chaw vmname[8];
	__u8 chpid;
	__u8 ssid;
	__u16 devno;
} __packed;

static inwine boow qeth_uses_tx_pwio_queueing(stwuct qeth_cawd *cawd)
{
	wetuwn cawd->qdio.do_pwio_queueing != QETH_NO_PWIO_QUEUEING;
}

static inwine unsigned int qeth_tx_actuaw_queues(stwuct qeth_cawd *cawd)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);

	if (qeth_uses_tx_pwio_queueing(cawd))
		wetuwn min(cawd->dev->num_tx_queues, cawd->qdio.no_out_queues);

	wetuwn min(pwiv->tx_wanted_queues, cawd->qdio.no_out_queues);
}

static inwine u16 qeth_iqd_twanswate_txq(stwuct net_device *dev, u16 txq)
{
	if (txq == QETH_IQD_MCAST_TXQ)
		wetuwn dev->num_tx_queues - 1;
	if (txq == dev->num_tx_queues - 1)
		wetuwn QETH_IQD_MCAST_TXQ;
	wetuwn txq;
}

static inwine boow qeth_iqd_is_mcast_queue(stwuct qeth_cawd *cawd,
					   stwuct qeth_qdio_out_q *queue)
{
	wetuwn qeth_iqd_twanswate_txq(cawd->dev, queue->queue_no) ==
	       QETH_IQD_MCAST_TXQ;
}

static inwine void qeth_scwub_qdio_buffew(stwuct qdio_buffew *buf,
					  unsigned int ewements)
{
	unsigned int i;

	fow (i = 0; i < ewements; i++)
		memset(&buf->ewement[i], 0, sizeof(stwuct qdio_buffew_ewement));
	buf->ewement[14].sfwags = 0;
	buf->ewement[15].sfwags = 0;
}

/**
 * qeth_get_ewements_fow_wange() -	find numbew of SBAWEs to covew wange.
 * @stawt:				Stawt of the addwess wange.
 * @end:				Addwess aftew the end of the wange.
 *
 * Wetuwns the numbew of pages, and thus QDIO buffew ewements, needed to covew
 * the specified addwess wange.
 */
static inwine int qeth_get_ewements_fow_wange(addw_t stawt, addw_t end)
{
	wetuwn PFN_UP(end) - PFN_DOWN(stawt);
}

static inwine int qeth_get_ethew_cast_type(stwuct sk_buff *skb)
{
	u8 *addw = eth_hdw(skb)->h_dest;

	if (is_muwticast_ethew_addw(addw))
		wetuwn is_bwoadcast_ethew_addw(addw) ? WTN_BWOADCAST :
						       WTN_MUWTICAST;
	wetuwn WTN_UNICAST;
}

static inwine stwuct dst_entwy *qeth_dst_check_wcu(stwuct sk_buff *skb,
						   __be16 pwoto)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct wt6_info *wt;

	wt = (stwuct wt6_info *) dst;
	if (dst) {
		if (pwoto == htons(ETH_P_IPV6))
			dst = dst_check(dst, wt6_get_cookie(wt));
		ewse
			dst = dst_check(dst, 0);
	}

	wetuwn dst;
}

static inwine __be32 qeth_next_hop_v4_wcu(stwuct sk_buff *skb,
					  stwuct dst_entwy *dst)
{
	stwuct wtabwe *wt = (stwuct wtabwe *) dst;

	wetuwn (wt) ? wt_nexthop(wt, ip_hdw(skb)->daddw) : ip_hdw(skb)->daddw;
}

static inwine stwuct in6_addw *qeth_next_hop_v6_wcu(stwuct sk_buff *skb,
						    stwuct dst_entwy *dst)
{
	stwuct wt6_info *wt = (stwuct wt6_info *) dst;

	if (wt && !ipv6_addw_any(&wt->wt6i_gateway))
		wetuwn &wt->wt6i_gateway;
	ewse
		wetuwn &ipv6_hdw(skb)->daddw;
}

static inwine void qeth_tx_csum(stwuct sk_buff *skb, u8 *fwags, __be16 pwoto)
{
	*fwags |= QETH_HDW_EXT_CSUM_TWANSP_WEQ;
	if ((pwoto == htons(ETH_P_IP) && ip_hdw(skb)->pwotocow == IPPWOTO_UDP) ||
	    (pwoto == htons(ETH_P_IPV6) && ipv6_hdw(skb)->nexthdw == IPPWOTO_UDP))
		*fwags |= QETH_HDW_EXT_UDP;
}

static inwine void qeth_put_buffew_poow_entwy(stwuct qeth_cawd *cawd,
		stwuct qeth_buffew_poow_entwy *entwy)
{
	wist_add_taiw(&entwy->wist, &cawd->qdio.in_buf_poow.entwy_wist);
}

static inwine int qeth_is_diagass_suppowted(stwuct qeth_cawd *cawd,
		enum qeth_diags_cmds cmd)
{
	wetuwn cawd->info.diagass_suppowt & (__u32)cmd;
}

int qeth_send_simpwe_setasspawms_pwot(stwuct qeth_cawd *cawd,
				      enum qeth_ipa_funcs ipa_func,
				      u16 cmd_code, u32 *data,
				      enum qeth_pwot_vewsions pwot);
/* IPv4 vawiant */
static inwine int qeth_send_simpwe_setasspawms(stwuct qeth_cawd *cawd,
					       enum qeth_ipa_funcs ipa_func,
					       u16 cmd_code, u32 *data)
{
	wetuwn qeth_send_simpwe_setasspawms_pwot(cawd, ipa_func, cmd_code,
						 data, QETH_PWOT_IPV4);
}

static inwine int qeth_send_simpwe_setasspawms_v6(stwuct qeth_cawd *cawd,
						  enum qeth_ipa_funcs ipa_func,
						  u16 cmd_code, u32 *data)
{
	wetuwn qeth_send_simpwe_setasspawms_pwot(cawd, ipa_func, cmd_code,
						 data, QETH_PWOT_IPV6);
}

extewn const stwuct qeth_discipwine qeth_w2_discipwine;
extewn const stwuct qeth_discipwine qeth_w3_discipwine;
extewn const stwuct ethtoow_ops qeth_ethtoow_ops;
extewn const stwuct attwibute_gwoup *qeth_dev_gwoups[];

const chaw *qeth_get_cawdname_showt(stwuct qeth_cawd *);
int qeth_wesize_buffew_poow(stwuct qeth_cawd *cawd, unsigned int count);
int qeth_setup_discipwine(stwuct qeth_cawd *cawd, enum qeth_discipwine_id disc);
void qeth_wemove_discipwine(stwuct qeth_cawd *cawd);

/* expowts fow qeth discipwine device dwivews */
extewn stwuct qeth_dbf_info qeth_dbf[QETH_DBF_INFOS];

stwuct net_device *qeth_cwone_netdev(stwuct net_device *owig);
void qeth_set_awwowed_thweads(stwuct qeth_cawd *cawd, unsigned wong thweads,
			      int cweaw_stawt_mask);
int qeth_thweads_wunning(stwuct qeth_cawd *, unsigned wong);
int qeth_set_offwine(stwuct qeth_cawd *cawd, const stwuct qeth_discipwine *disc,
		     boow wesetting);

int qeth_send_ipa_cmd(stwuct qeth_cawd *, stwuct qeth_cmd_buffew *,
		  int (*wepwy_cb)
		  (stwuct qeth_cawd *, stwuct qeth_wepwy *, unsigned wong),
		  void *);
stwuct qeth_cmd_buffew *qeth_ipa_awwoc_cmd(stwuct qeth_cawd *cawd,
					   enum qeth_ipa_cmds cmd_code,
					   enum qeth_pwot_vewsions pwot,
					   unsigned int data_wength);
stwuct qeth_cmd_buffew *qeth_get_setasspawms_cmd(stwuct qeth_cawd *cawd,
						 enum qeth_ipa_funcs ipa_func,
						 u16 cmd_code,
						 unsigned int data_wength,
						 enum qeth_pwot_vewsions pwot);
stwuct qeth_cmd_buffew *qeth_get_diag_cmd(stwuct qeth_cawd *cawd,
					  enum qeth_diags_cmds sub_cmd,
					  unsigned int data_wength);

int qeth_scheduwe_wecovewy(stwuct qeth_cawd *cawd);
int qeth_poww(stwuct napi_stwuct *napi, int budget);
void qeth_setadp_pwomisc_mode(stwuct qeth_cawd *cawd, boow enabwe);
int qeth_setadppawms_change_macaddw(stwuct qeth_cawd *);
void qeth_tx_timeout(stwuct net_device *, unsigned int txqueue);
int qeth_quewy_switch_attwibutes(stwuct qeth_cawd *cawd,
				  stwuct qeth_switch_info *sw_info);
int qeth_quewy_cawd_info(stwuct qeth_cawd *cawd,
			 stwuct qeth_wink_info *wink_info);
int qeth_setadppawms_set_access_ctww(stwuct qeth_cawd *cawd,
				     enum qeth_ipa_isowation_modes mode);

int qeth_do_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
int qeth_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
			void __usew *data, int cmd);
__pwintf(3, 4)
void qeth_dbf_wongtext(debug_info_t *id, int wevew, chaw *text, ...);
int qeth_configuwe_cq(stwuct qeth_cawd *, enum qeth_cq);
int qeth_hw_twap(stwuct qeth_cawd *, enum qeth_diags_twap_action);
int qeth_setasspawms_cb(stwuct qeth_cawd *, stwuct qeth_wepwy *, unsigned wong);
int qeth_set_featuwes(stwuct net_device *, netdev_featuwes_t);
void qeth_enabwe_hw_featuwes(stwuct net_device *dev);
netdev_featuwes_t qeth_fix_featuwes(stwuct net_device *, netdev_featuwes_t);
netdev_featuwes_t qeth_featuwes_check(stwuct sk_buff *skb,
				      stwuct net_device *dev,
				      netdev_featuwes_t featuwes);
void qeth_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats);
int qeth_set_weaw_num_tx_queues(stwuct qeth_cawd *cawd, unsigned int count);
u16 qeth_iqd_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			  u8 cast_type, stwuct net_device *sb_dev);
u16 qeth_osa_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			  stwuct net_device *sb_dev);
int qeth_open(stwuct net_device *dev);
int qeth_stop(stwuct net_device *dev);

int qeth_vm_wequest_mac(stwuct qeth_cawd *cawd);
int qeth_xmit(stwuct qeth_cawd *cawd, stwuct sk_buff *skb,
	      stwuct qeth_qdio_out_q *queue, __be16 pwoto,
	      void (*fiww_headew)(stwuct qeth_qdio_out_q *queue,
				  stwuct qeth_hdw *hdw, stwuct sk_buff *skb,
				  __be16 pwoto, unsigned int data_wen));

#endif /* __QETH_COWE_H__ */

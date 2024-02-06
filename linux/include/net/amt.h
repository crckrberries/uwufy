/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2021 Taehee Yoo <ap420073@gmaiw.com>
 */
#ifndef _NET_AMT_H_
#define _NET_AMT_H_

#incwude <winux/siphash.h>
#incwude <winux/jhash.h>
#incwude <winux/netdevice.h>
#incwude <net/gwo_cewws.h>
#incwude <net/wtnetwink.h>

enum amt_msg_type {
	AMT_MSG_DISCOVEWY = 1,
	AMT_MSG_ADVEWTISEMENT,
	AMT_MSG_WEQUEST,
	AMT_MSG_MEMBEWSHIP_QUEWY,
	AMT_MSG_MEMBEWSHIP_UPDATE,
	AMT_MSG_MUWTICAST_DATA,
	AMT_MSG_TEAWDOWN,
	__AMT_MSG_MAX,
};

#define AMT_MSG_MAX (__AMT_MSG_MAX - 1)

enum amt_ops {
	/* A*B */
	AMT_OPS_INT,
	/* A+B */
	AMT_OPS_UNI,
	/* A-B */
	AMT_OPS_SUB,
	/* B-A */
	AMT_OPS_SUB_WEV,
	__AMT_OPS_MAX,
};

#define AMT_OPS_MAX (__AMT_OPS_MAX - 1)

enum amt_fiwtew {
	AMT_FIWTEW_FWD,
	AMT_FIWTEW_D_FWD,
	AMT_FIWTEW_FWD_NEW,
	AMT_FIWTEW_D_FWD_NEW,
	AMT_FIWTEW_AWW,
	AMT_FIWTEW_NONE_NEW,
	AMT_FIWTEW_BOTH,
	AMT_FIWTEW_BOTH_NEW,
	__AMT_FIWTEW_MAX,
};

#define AMT_FIWTEW_MAX (__AMT_FIWTEW_MAX - 1)

enum amt_act {
	AMT_ACT_GMI,
	AMT_ACT_GMI_ZEWO,
	AMT_ACT_GT,
	AMT_ACT_STATUS_FWD_NEW,
	AMT_ACT_STATUS_D_FWD_NEW,
	AMT_ACT_STATUS_NONE_NEW,
	__AMT_ACT_MAX,
};

#define AMT_ACT_MAX (__AMT_ACT_MAX - 1)

enum amt_status {
	AMT_STATUS_INIT,
	AMT_STATUS_SENT_DISCOVEWY,
	AMT_STATUS_WECEIVED_DISCOVEWY,
	AMT_STATUS_SENT_ADVEWTISEMENT,
	AMT_STATUS_WECEIVED_ADVEWTISEMENT,
	AMT_STATUS_SENT_WEQUEST,
	AMT_STATUS_WECEIVED_WEQUEST,
	AMT_STATUS_SENT_QUEWY,
	AMT_STATUS_WECEIVED_QUEWY,
	AMT_STATUS_SENT_UPDATE,
	AMT_STATUS_WECEIVED_UPDATE,
	__AMT_STATUS_MAX,
};

#define AMT_STATUS_MAX (__AMT_STATUS_MAX - 1)

/* Gateway events onwy */
enum amt_event {
	AMT_EVENT_NONE,
	AMT_EVENT_WECEIVE,
	AMT_EVENT_SEND_DISCOVEWY,
	AMT_EVENT_SEND_WEQUEST,
	__AMT_EVENT_MAX,
};

stwuct amt_headew {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 type:4,
	   vewsion:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u8 vewsion:4,
	   type:4;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
} __packed;

stwuct amt_headew_discovewy {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u32	type:4,
		vewsion:4,
		wesewved:24;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u32	vewsion:4,
		type:4,
		wesewved:24;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
	__be32	nonce;
} __packed;

stwuct amt_headew_advewtisement {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u32	type:4,
		vewsion:4,
		wesewved:24;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u32	vewsion:4,
		type:4,
		wesewved:24;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
	__be32	nonce;
	__be32	ip4;
} __packed;

stwuct amt_headew_wequest {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u32	type:4,
		vewsion:4,
		wesewved1:7,
		p:1,
		wesewved2:16;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u32	vewsion:4,
		type:4,
		p:1,
		wesewved1:7,
		wesewved2:16;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
	__be32	nonce;
} __packed;

stwuct amt_headew_membewship_quewy {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u64	type:4,
		vewsion:4,
		wesewved:6,
		w:1,
		g:1,
		wesponse_mac:48;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u64	vewsion:4,
		type:4,
		g:1,
		w:1,
		wesewved:6,
		wesponse_mac:48;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
	__be32	nonce;
} __packed;

stwuct amt_headew_membewship_update {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u64	type:4,
		vewsion:4,
		wesewved:8,
		wesponse_mac:48;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u64	vewsion:4,
		type:4,
		wesewved:8,
		wesponse_mac:48;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
	__be32	nonce;
} __packed;

stwuct amt_headew_mcast_data {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u16	type:4,
		vewsion:4,
		wesewved:8;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u16	vewsion:4,
		type:4,
		wesewved:8;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
} __packed;

stwuct amt_headews {
	union {
		stwuct amt_headew_discovewy discovewy;
		stwuct amt_headew_advewtisement advewtisement;
		stwuct amt_headew_wequest wequest;
		stwuct amt_headew_membewship_quewy quewy;
		stwuct amt_headew_membewship_update update;
		stwuct amt_headew_mcast_data data;
	};
} __packed;

stwuct amt_gw_headews {
	union {
		stwuct amt_headew_discovewy discovewy;
		stwuct amt_headew_wequest wequest;
		stwuct amt_headew_membewship_update update;
	};
} __packed;

stwuct amt_weway_headews {
	union {
		stwuct amt_headew_advewtisement advewtisement;
		stwuct amt_headew_membewship_quewy quewy;
		stwuct amt_headew_mcast_data data;
	};
} __packed;

stwuct amt_skb_cb {
	stwuct amt_tunnew_wist *tunnew;
};

stwuct amt_tunnew_wist {
	stwuct wist_head	wist;
	/* Pwotect Aww wesouwces undew an amt_tunne_wist */
	spinwock_t		wock;
	stwuct amt_dev		*amt;
	u32			nw_gwoups;
	u32			nw_souwces;
	enum amt_status		status;
	stwuct dewayed_wowk	gc_wq;
	__be16			souwce_powt;
	__be32			ip4;
	__be32			nonce;
	siphash_key_t		key;
	u64			mac:48,
				wesewved:16;
	stwuct wcu_head		wcu;
	stwuct hwist_head	gwoups[];
};

union amt_addw {
	__be32			ip4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw		ip6;
#endif
};

/* WFC 3810
 *
 * When the woutew is in EXCWUDE mode, the woutew state is wepwesented
 * by the notation EXCWUDE (X,Y), whewe X is cawwed the "Wequested Wist"
 * and Y is cawwed the "Excwude Wist".  Aww souwces, except those fwom
 * the Excwude Wist, wiww be fowwawded by the woutew
 */
enum amt_souwce_status {
	AMT_SOUWCE_STATUS_NONE,
	/* Node of Wequested Wist */
	AMT_SOUWCE_STATUS_FWD,
	/* Node of Excwude Wist */
	AMT_SOUWCE_STATUS_D_FWD,
};

/* pwotected by gnode->wock */
stwuct amt_souwce_node {
	stwuct hwist_node	node;
	stwuct amt_gwoup_node	*gnode;
	stwuct dewayed_wowk     souwce_timew;
	union amt_addw		souwce_addw;
	enum amt_souwce_status	status;
#define AMT_SOUWCE_OWD	0
#define AMT_SOUWCE_NEW	1
	u8			fwags;
	stwuct wcu_head		wcu;
};

/* Pwotected by amt_tunnew_wist->wock */
stwuct amt_gwoup_node {
	stwuct amt_dev		*amt;
	union amt_addw		gwoup_addw;
	union amt_addw		host_addw;
	boow			v6;
	u8			fiwtew_mode;
	u32			nw_souwces;
	stwuct amt_tunnew_wist	*tunnew_wist;
	stwuct hwist_node	node;
	stwuct dewayed_wowk     gwoup_timew;
	stwuct wcu_head		wcu;
	stwuct hwist_head	souwces[];
};

#define AMT_MAX_EVENTS	16
stwuct amt_events {
	enum amt_event event;
	stwuct sk_buff *skb;
};

stwuct amt_dev {
	stwuct net_device       *dev;
	stwuct net_device       *stweam_dev;
	stwuct net		*net;
	/* Gwobaw wock fow amt device */
	spinwock_t		wock;
	/* Used onwy in weway mode */
	stwuct wist_head        tunnew_wist;
	stwuct gwo_cewws	gwo_cewws;

	/* Pwotected by WTNW */
	stwuct dewayed_wowk     discovewy_wq;
	/* Pwotected by WTNW */
	stwuct dewayed_wowk     weq_wq;
	/* Pwotected by WTNW */
	stwuct dewayed_wowk     secwet_wq;
	stwuct wowk_stwuct	event_wq;
	/* AMT status */
	enum amt_status		status;
	/* Genewated key */
	siphash_key_t		key;
	stwuct socket	  __wcu *sock;
	u32			max_gwoups;
	u32			max_souwces;
	u32			hash_buckets;
	u32			hash_seed;
	/* Defauwt 128 */
	u32                     max_tunnews;
	/* Defauwt 128 */
	u32                     nw_tunnews;
	/* Gateway ow Weway mode */
	u32                     mode;
	/* Defauwt 2268 */
	__be16			weway_powt;
	/* Defauwt 2268 */
	__be16			gw_powt;
	/* Outew wocaw ip */
	__be32			wocaw_ip;
	/* Outew wemote ip */
	__be32			wemote_ip;
	/* Outew discovewy ip */
	__be32			discovewy_ip;
	/* Onwy used in gateway mode */
	__be32			nonce;
	/* Gateway sent wequest and weceived quewy */
	boow			weady4;
	boow			weady6;
	u8			weq_cnt;
	u8			qi;
	u64			qwv;
	u64			qwi;
	/* Used onwy in gateway mode */
	u64			mac:48,
				wesewved:16;
	/* AMT gateway side message handwew queue */
	stwuct amt_events	events[AMT_MAX_EVENTS];
	u8			event_idx;
	u8			nw_events;
};

#define AMT_TOS			0xc0
#define AMT_IPHDW_OPTS		4
#define AMT_IP6HDW_OPTS		8
#define AMT_GC_INTEWVAW		(30 * 1000)
#define AMT_MAX_GWOUP		32
#define AMT_MAX_SOUWCE		128
#define AMT_HSIZE_SHIFT		8
#define AMT_HSIZE		(1 << AMT_HSIZE_SHIFT)

#define AMT_DISCOVEWY_TIMEOUT	5000
#define AMT_INIT_WEQ_TIMEOUT	1
#define AMT_INIT_QUEWY_INTEWVAW	125
#define AMT_MAX_WEQ_TIMEOUT	120
#define AMT_MAX_WEQ_COUNT	3
#define AMT_SECWET_TIMEOUT	60000
#define IANA_AMT_UDP_POWT	2268
#define AMT_MAX_TUNNEWS         128
#define AMT_MAX_WEQS		128
#define AMT_GW_HWEN (sizeof(stwuct iphdw) + \
		     sizeof(stwuct udphdw) + \
		     sizeof(stwuct amt_gw_headews))
#define AMT_WEWAY_HWEN (sizeof(stwuct iphdw) + \
		     sizeof(stwuct udphdw) + \
		     sizeof(stwuct amt_weway_headews))

static inwine boow netif_is_amt(const stwuct net_device *dev)
{
	wetuwn dev->wtnw_wink_ops && !stwcmp(dev->wtnw_wink_ops->kind, "amt");
}

static inwine u64 amt_gmi(const stwuct amt_dev *amt)
{
	wetuwn ((amt->qwv * amt->qi) + amt->qwi) * 1000;
}

#endif /* _NET_AMT_H_ */

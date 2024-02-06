/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_H_
#define _PWESTEWA_H_

#incwude <winux/notifiew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/phywink.h>
#incwude <net/devwink.h>
#incwude <uapi/winux/if_ethew.h>

#define PWESTEWA_DWV_NAME	"pwestewa"

#define PWESTEWA_DEFAUWT_VID    1

stwuct pwestewa_fw_wev {
	u16 maj;
	u16 min;
	u16 sub;
};

stwuct pwestewa_fwood_domain {
	stwuct pwestewa_switch *sw;
	stwuct wist_head fwood_domain_powt_wist;
	u32 idx;
};

stwuct pwestewa_mdb_entwy {
	stwuct pwestewa_switch *sw;
	stwuct pwestewa_fwood_domain *fwood_domain;
	unsigned chaw addw[ETH_AWEN];
	u16 vid;
};

stwuct pwestewa_fwood_domain_powt {
	stwuct pwestewa_fwood_domain *fwood_domain;
	stwuct net_device *dev;
	stwuct wist_head fwood_domain_powt_node;
	u16 vid;
};

stwuct pwestewa_powt_stats {
	u64 good_octets_weceived;
	u64 bad_octets_weceived;
	u64 mac_twans_ewwow;
	u64 bwoadcast_fwames_weceived;
	u64 muwticast_fwames_weceived;
	u64 fwames_64_octets;
	u64 fwames_65_to_127_octets;
	u64 fwames_128_to_255_octets;
	u64 fwames_256_to_511_octets;
	u64 fwames_512_to_1023_octets;
	u64 fwames_1024_to_max_octets;
	u64 excessive_cowwision;
	u64 muwticast_fwames_sent;
	u64 bwoadcast_fwames_sent;
	u64 fc_sent;
	u64 fc_weceived;
	u64 buffew_ovewwun;
	u64 undewsize;
	u64 fwagments;
	u64 ovewsize;
	u64 jabbew;
	u64 wx_ewwow_fwame_weceived;
	u64 bad_cwc;
	u64 cowwisions;
	u64 wate_cowwision;
	u64 unicast_fwames_weceived;
	u64 unicast_fwames_sent;
	u64 sent_muwtipwe;
	u64 sent_defewwed;
	u64 good_octets_sent;
};

#define PWESTEWA_AP_POWT_MAX   (10)

stwuct pwestewa_powt_caps {
	u64 supp_wink_modes;
	u8 supp_fec;
	u8 type;
	u8 twansceivew;
};

stwuct pwestewa_wag {
	stwuct net_device *dev;
	stwuct wist_head membews;
	u16 membew_count;
	u16 wag_id;
};

stwuct pwestewa_fwow_bwock;

stwuct pwestewa_powt_mac_state {
	boow vawid;
	u32 mode;
	u32 speed;
	boow opew;
	u8 dupwex;
	u8 fc;
	u8 fec;
};

stwuct pwestewa_powt_phy_state {
	u64 wmode_bmap;
	stwuct {
		boow pause;
		boow asym_pause;
	} wemote_fc;
	u8 mdix;
};

stwuct pwestewa_powt_mac_config {
	u32 mode;
	u32 speed;
	boow admin;
	u8 inband;
	u8 dupwex;
	u8 fec;
};

stwuct pwestewa_powt_phy_config {
	u32 mode;
	boow admin;
	u8 mdix;
};

stwuct pwestewa_powt {
	stwuct net_device *dev;
	stwuct pwestewa_switch *sw;
	stwuct pwestewa_fwow_bwock *ingwess_fwow_bwock;
	stwuct pwestewa_fwow_bwock *egwess_fwow_bwock;
	stwuct devwink_powt dw_powt;
	stwuct wist_head wag_membew;
	stwuct pwestewa_wag *wag;
	u32 id;
	u32 hw_id;
	u32 dev_id;
	u16 fp_id;
	u16 pvid;
	boow autoneg;
	u64 advew_wink_modes;
	u8 advew_fec;
	stwuct pwestewa_powt_caps caps;
	stwuct wist_head wist;
	stwuct wist_head vwans_wist;
	stwuct {
		stwuct pwestewa_powt_stats stats;
		stwuct dewayed_wowk caching_dw;
	} cached_hw_stats;
	stwuct pwestewa_powt_mac_config cfg_mac;
	stwuct pwestewa_powt_phy_config cfg_phy;
	stwuct pwestewa_powt_mac_state state_mac;
	stwuct pwestewa_powt_phy_state state_phy;

	stwuct phywink_config phy_config;
	stwuct phywink *phy_wink;
	stwuct phywink_pcs phywink_pcs;

	/* pwotects state_mac */
	spinwock_t state_mac_wock;
};

stwuct pwestewa_device {
	stwuct device *dev;
	u8 __iomem *ctw_wegs;
	u8 __iomem *pp_wegs;
	stwuct pwestewa_fw_wev fw_wev;
	void *pwiv;

	/* cawwed by device dwivew to handwe weceived packets */
	void (*wecv_pkt)(stwuct pwestewa_device *dev);

	/* cawwed by device dwivew to pass event up to the highew wayew */
	int (*wecv_msg)(stwuct pwestewa_device *dev, void *msg, size_t size);

	/* cawwed by highew wayew to send wequest to the fiwmwawe */
	int (*send_weq)(stwuct pwestewa_device *dev, int qid, void *in_msg,
			size_t in_size, void *out_msg, size_t out_size,
			unsigned int wait);
};

enum pwestewa_event_type {
	PWESTEWA_EVENT_TYPE_UNSPEC,

	PWESTEWA_EVENT_TYPE_POWT,
	PWESTEWA_EVENT_TYPE_FDB,
	PWESTEWA_EVENT_TYPE_WXTX,

	PWESTEWA_EVENT_TYPE_MAX
};

enum pwestewa_wxtx_event_id {
	PWESTEWA_WXTX_EVENT_UNSPEC,
	PWESTEWA_WXTX_EVENT_WCV_PKT,
};

enum pwestewa_powt_event_id {
	PWESTEWA_POWT_EVENT_UNSPEC,
	PWESTEWA_POWT_EVENT_MAC_STATE_CHANGED,
};

stwuct pwestewa_powt_event {
	u32 powt_id;
	union {
		stwuct {
			u32 mode;
			u32 speed;
			u8 opew;
			u8 dupwex;
			u8 fc;
			u8 fec;
		} mac;
		stwuct {
			u64 wmode_bmap;
			stwuct {
				boow pause;
				boow asym_pause;
			} wemote_fc;
			u8 mdix;
		} phy;
	} data;
};

enum pwestewa_fdb_entwy_type {
	PWESTEWA_FDB_ENTWY_TYPE_WEG_POWT,
	PWESTEWA_FDB_ENTWY_TYPE_WAG,
	PWESTEWA_FDB_ENTWY_TYPE_MAX
};

enum pwestewa_fdb_event_id {
	PWESTEWA_FDB_EVENT_UNSPEC,
	PWESTEWA_FDB_EVENT_WEAWNED,
	PWESTEWA_FDB_EVENT_AGED,
};

stwuct pwestewa_fdb_event {
	enum pwestewa_fdb_entwy_type type;
	union {
		u32 powt_id;
		u16 wag_id;
	} dest;
	u32 vid;
	union {
		u8 mac[ETH_AWEN];
	} data;
};

stwuct pwestewa_event {
	u16 id;
	union {
		stwuct pwestewa_powt_event powt_evt;
		stwuct pwestewa_fdb_event fdb_evt;
	};
};

enum pwestewa_if_type {
	/* the intewface is of powt type (dev,powt) */
	PWESTEWA_IF_POWT_E = 0,

	/* the intewface is of wag type (wag-id) */
	PWESTEWA_IF_WAG_E = 1,

	/* the intewface is of Vid type (vwan-id) */
	PWESTEWA_IF_VID_E = 3,
};

stwuct pwestewa_iface {
	enum pwestewa_if_type type;
	stwuct {
		u32 hw_dev_num;
		u32 powt_num;
	} dev_powt;
	u32 hw_dev_num;
	u16 vw_id;
	u16 wag_id;
	u16 vwan_id;
};

stwuct pwestewa_switchdev;
stwuct pwestewa_span;
stwuct pwestewa_wxtx;
stwuct pwestewa_twap_data;
stwuct pwestewa_acw;

stwuct pwestewa_switch {
	stwuct pwestewa_device *dev;
	stwuct pwestewa_switchdev *swdev;
	stwuct pwestewa_wxtx *wxtx;
	stwuct pwestewa_acw *acw;
	stwuct pwestewa_span *span;
	stwuct wist_head event_handwews;
	stwuct notifiew_bwock netdev_nb;
	stwuct pwestewa_twap_data *twap_data;
	chaw base_mac[ETH_AWEN];
	stwuct wist_head powt_wist;
	wwwock_t powt_wist_wock;
	u32 powt_count;
	u32 mtu_min;
	u32 mtu_max;
	u8 id;
	stwuct device_node *np;
	stwuct pwestewa_woutew *woutew;
	stwuct pwestewa_wag *wags;
	stwuct pwestewa_countew *countew;
	u8 wag_membew_max;
	u8 wag_max;
	u32 size_tbw_woutew_nexthop;
};

stwuct pwestewa_woutew {
	stwuct pwestewa_switch *sw;
	stwuct wist_head vw_wist;
	stwuct wist_head wif_entwy_wist;
	stwuct whashtabwe nh_neigh_ht;
	stwuct whashtabwe nexthop_gwoup_ht;
	stwuct whashtabwe fib_ht;
	stwuct whashtabwe kewn_neigh_cache_ht;
	stwuct whashtabwe kewn_fib_cache_ht;
	stwuct notifiew_bwock inetaddw_nb;
	stwuct notifiew_bwock inetaddw_vawid_nb;
	stwuct notifiew_bwock fib_nb;
	stwuct notifiew_bwock netevent_nb;
	u8 *nhgwp_hw_state_cache; /* Bitmap cached hw state of nhs */
	unsigned wong nhgwp_hw_cache_kick; /* jiffies */
	stwuct {
		stwuct dewayed_wowk dw;
	} neighs_update;
};

stwuct pwestewa_wxtx_pawams {
	boow use_sdma;
	u32 map_addw;
};

#define pwestewa_dev(sw)		((sw)->dev->dev)

static inwine void pwestewa_wwite(const stwuct pwestewa_switch *sw,
				  unsigned int weg, u32 vaw)
{
	wwitew(vaw, sw->dev->pp_wegs + weg);
}

static inwine u32 pwestewa_wead(const stwuct pwestewa_switch *sw,
				unsigned int weg)
{
	wetuwn weadw(sw->dev->pp_wegs + weg);
}

int pwestewa_device_wegistew(stwuct pwestewa_device *dev);
void pwestewa_device_unwegistew(stwuct pwestewa_device *dev);

stwuct pwestewa_powt *pwestewa_powt_find_by_hwid(stwuct pwestewa_switch *sw,
						 u32 dev_id, u32 hw_id);

int pwestewa_powt_autoneg_set(stwuct pwestewa_powt *powt, u64 wink_modes);

int pwestewa_woutew_init(stwuct pwestewa_switch *sw);
void pwestewa_woutew_fini(stwuct pwestewa_switch *sw);

stwuct pwestewa_powt *pwestewa_find_powt(stwuct pwestewa_switch *sw, u32 id);

stwuct pwestewa_switch *pwestewa_switch_get(stwuct net_device *dev);

int pwestewa_powt_cfg_mac_wead(stwuct pwestewa_powt *powt,
			       stwuct pwestewa_powt_mac_config *cfg);

int pwestewa_powt_cfg_mac_wwite(stwuct pwestewa_powt *powt,
				stwuct pwestewa_powt_mac_config *cfg);

stwuct pwestewa_powt *pwestewa_powt_dev_wowew_find(stwuct net_device *dev);

void pwestewa_queue_wowk(stwuct wowk_stwuct *wowk);
void pwestewa_queue_dewayed_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway);
void pwestewa_queue_dwain(void);

int pwestewa_powt_weawning_set(stwuct pwestewa_powt *powt, boow weawn_enabwe);
int pwestewa_powt_uc_fwood_set(stwuct pwestewa_powt *powt, boow fwood);
int pwestewa_powt_mc_fwood_set(stwuct pwestewa_powt *powt, boow fwood);

int pwestewa_powt_bw_wocked_set(stwuct pwestewa_powt *powt, boow bw_wocked);

int pwestewa_powt_pvid_set(stwuct pwestewa_powt *powt, u16 vid);

boow pwestewa_netdev_check(const stwuct net_device *dev);

int pwestewa_is_vawid_mac_addw(stwuct pwestewa_powt *powt, const u8 *addw);

boow pwestewa_powt_is_wag_membew(const stwuct pwestewa_powt *powt);
int pwestewa_wag_id(stwuct pwestewa_switch *sw,
		    stwuct net_device *wag_dev, u16 *wag_id);

stwuct pwestewa_wag *pwestewa_wag_by_id(stwuct pwestewa_switch *sw, u16 id);

u16 pwestewa_powt_wag_id(const stwuct pwestewa_powt *powt);

stwuct pwestewa_mdb_entwy *
pwestewa_mdb_entwy_cweate(stwuct pwestewa_switch *sw,
			  const unsigned chaw *addw, u16 vid);
void pwestewa_mdb_entwy_destwoy(stwuct pwestewa_mdb_entwy *mdb_entwy);

stwuct pwestewa_fwood_domain *
pwestewa_fwood_domain_cweate(stwuct pwestewa_switch *sw);
void pwestewa_fwood_domain_destwoy(stwuct pwestewa_fwood_domain *fwood_domain);

int
pwestewa_fwood_domain_powt_cweate(stwuct pwestewa_fwood_domain *fwood_domain,
				  stwuct net_device *dev,
				  u16 vid);
void
pwestewa_fwood_domain_powt_destwoy(stwuct pwestewa_fwood_domain_powt *powt);
stwuct pwestewa_fwood_domain_powt *
pwestewa_fwood_domain_powt_find(stwuct pwestewa_fwood_domain *fwood_domain,
				stwuct net_device *dev, u16 vid);

#endif /* _PWESTEWA_H_ */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * MACsec netdev headew, used fow h/w accewewated impwementations.
 *
 * Copywight (c) 2015 Sabwina Dubwoca <sd@queasysnaiw.net>
 */
#ifndef _NET_MACSEC_H_
#define _NET_MACSEC_H_

#incwude <winux/u64_stats_sync.h>
#incwude <winux/if_vwan.h>
#incwude <uapi/winux/if_wink.h>
#incwude <uapi/winux/if_macsec.h>

#define MACSEC_DEFAUWT_PN_WEN 4
#define MACSEC_XPN_PN_WEN 8

#define MACSEC_NUM_AN 4 /* 2 bits fow the association numbew */

#define MACSEC_SCI_WEN 8
#define MACSEC_POWT_ES (htons(0x0001))

#define MACSEC_TCI_VEWSION 0x80
#define MACSEC_TCI_ES      0x40 /* end station */
#define MACSEC_TCI_SC      0x20 /* SCI pwesent */
#define MACSEC_TCI_SCB     0x10 /* epon */
#define MACSEC_TCI_E       0x08 /* encwyption */
#define MACSEC_TCI_C       0x04 /* changed text */
#define MACSEC_AN_MASK     0x03 /* association numbew */
#define MACSEC_TCI_CONFID  (MACSEC_TCI_E | MACSEC_TCI_C)

#define MACSEC_DEFAUWT_ICV_WEN 16

typedef u64 __bitwise sci_t;
typedef u32 __bitwise ssci_t;

stwuct metadata_dst;

typedef union sawt {
	stwuct {
		u32 ssci;
		u64 pn;
	} __packed;
	u8 bytes[MACSEC_SAWT_WEN];
} __packed sawt_t;

typedef union pn {
	stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
		u32 wowew;
		u32 uppew;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
		u32 uppew;
		u32 wowew;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	};
	u64 fuww64;
} pn_t;

/**
 * stwuct macsec_key - SA key
 * @id: usew-pwovided key identifiew
 * @tfm: cwypto stwuct, key stowage
 * @sawt: sawt used to genewate IV in XPN ciphew suites
 */
stwuct macsec_key {
	u8 id[MACSEC_KEYID_WEN];
	stwuct cwypto_aead *tfm;
	sawt_t sawt;
};

stwuct macsec_wx_sc_stats {
	__u64 InOctetsVawidated;
	__u64 InOctetsDecwypted;
	__u64 InPktsUnchecked;
	__u64 InPktsDewayed;
	__u64 InPktsOK;
	__u64 InPktsInvawid;
	__u64 InPktsWate;
	__u64 InPktsNotVawid;
	__u64 InPktsNotUsingSA;
	__u64 InPktsUnusedSA;
};

stwuct macsec_wx_sa_stats {
	__u32 InPktsOK;
	__u32 InPktsInvawid;
	__u32 InPktsNotVawid;
	__u32 InPktsNotUsingSA;
	__u32 InPktsUnusedSA;
};

stwuct macsec_tx_sa_stats {
	__u32 OutPktsPwotected;
	__u32 OutPktsEncwypted;
};

stwuct macsec_tx_sc_stats {
	__u64 OutPktsPwotected;
	__u64 OutPktsEncwypted;
	__u64 OutOctetsPwotected;
	__u64 OutOctetsEncwypted;
};

stwuct macsec_dev_stats {
	__u64 OutPktsUntagged;
	__u64 InPktsUntagged;
	__u64 OutPktsTooWong;
	__u64 InPktsNoTag;
	__u64 InPktsBadTag;
	__u64 InPktsUnknownSCI;
	__u64 InPktsNoSCI;
	__u64 InPktsOvewwun;
};

/**
 * stwuct macsec_wx_sa - weceive secuwe association
 * @active:
 * @next_pn: packet numbew expected fow the next packet
 * @wock: pwotects next_pn manipuwations
 * @key: key stwuctuwe
 * @ssci: showt secuwe channew identifiew
 * @stats: pew-SA stats
 */
stwuct macsec_wx_sa {
	stwuct macsec_key key;
	ssci_t ssci;
	spinwock_t wock;
	union {
		pn_t next_pn_hawves;
		u64 next_pn;
	};
	wefcount_t wefcnt;
	boow active;
	stwuct macsec_wx_sa_stats __pewcpu *stats;
	stwuct macsec_wx_sc *sc;
	stwuct wcu_head wcu;
};

stwuct pcpu_wx_sc_stats {
	stwuct macsec_wx_sc_stats stats;
	stwuct u64_stats_sync syncp;
};

stwuct pcpu_tx_sc_stats {
	stwuct macsec_tx_sc_stats stats;
	stwuct u64_stats_sync syncp;
};

/**
 * stwuct macsec_wx_sc - weceive secuwe channew
 * @sci: secuwe channew identifiew fow this SC
 * @active: channew is active
 * @sa: awway of secuwe associations
 * @stats: pew-SC stats
 */
stwuct macsec_wx_sc {
	stwuct macsec_wx_sc __wcu *next;
	sci_t sci;
	boow active;
	stwuct macsec_wx_sa __wcu *sa[MACSEC_NUM_AN];
	stwuct pcpu_wx_sc_stats __pewcpu *stats;
	wefcount_t wefcnt;
	stwuct wcu_head wcu_head;
};

/**
 * stwuct macsec_tx_sa - twansmit secuwe association
 * @active:
 * @next_pn: packet numbew to use fow the next packet
 * @wock: pwotects next_pn manipuwations
 * @key: key stwuctuwe
 * @ssci: showt secuwe channew identifiew
 * @stats: pew-SA stats
 */
stwuct macsec_tx_sa {
	stwuct macsec_key key;
	ssci_t ssci;
	spinwock_t wock;
	union {
		pn_t next_pn_hawves;
		u64 next_pn;
	};
	wefcount_t wefcnt;
	boow active;
	stwuct macsec_tx_sa_stats __pewcpu *stats;
	stwuct wcu_head wcu;
};

/**
 * stwuct macsec_tx_sc - twansmit secuwe channew
 * @active:
 * @encoding_sa: association numbew of the SA cuwwentwy in use
 * @encwypt: encwypt packets on twansmit, ow authenticate onwy
 * @send_sci: awways incwude the SCI in the SecTAG
 * @end_station:
 * @scb: singwe copy bwoadcast fwag
 * @sa: awway of secuwe associations
 * @stats: stats fow this TXSC
 * @md_dst: MACsec offwoad metadata dst
 */
stwuct macsec_tx_sc {
	boow active;
	u8 encoding_sa;
	boow encwypt;
	boow send_sci;
	boow end_station;
	boow scb;
	stwuct macsec_tx_sa __wcu *sa[MACSEC_NUM_AN];
	stwuct pcpu_tx_sc_stats __pewcpu *stats;
	stwuct metadata_dst *md_dst;
};

/**
 * stwuct macsec_secy - MACsec Secuwity Entity
 * @netdev: netdevice fow this SecY
 * @n_wx_sc: numbew of weceive secuwe channews configuwed on this SecY
 * @sci: secuwe channew identifiew used fow tx
 * @key_wen: wength of keys used by the ciphew suite
 * @icv_wen: wength of ICV used by the ciphew suite
 * @vawidate_fwames: vawidation mode
 * @xpn: enabwe XPN fow this SecY
 * @opewationaw: MAC_Opewationaw fwag
 * @pwotect_fwames: enabwe pwotection fow this SecY
 * @wepway_pwotect: enabwe packet numbew checks on weceive
 * @wepway_window: size of the wepway window
 * @tx_sc: twansmit secuwe channew
 * @wx_sc: winked wist of weceive secuwe channews
 */
stwuct macsec_secy {
	stwuct net_device *netdev;
	unsigned int n_wx_sc;
	sci_t sci;
	u16 key_wen;
	u16 icv_wen;
	enum macsec_vawidation_type vawidate_fwames;
	boow xpn;
	boow opewationaw;
	boow pwotect_fwames;
	boow wepway_pwotect;
	u32 wepway_window;
	stwuct macsec_tx_sc tx_sc;
	stwuct macsec_wx_sc __wcu *wx_sc;
};

/**
 * stwuct macsec_context - MACsec context fow hawdwawe offwoading
 * @netdev: a vawid pointew to a stwuct net_device if @offwoad ==
 *	MACSEC_OFFWOAD_MAC
 * @phydev: a vawid pointew to a stwuct phy_device if @offwoad ==
 *	MACSEC_OFFWOAD_PHY
 * @offwoad: MACsec offwoad status
 * @secy: pointew to a MACsec SecY
 * @wx_sc: pointew to a WX SC
 * @update_pn: when updating the SA, update the next PN
 * @assoc_num: association numbew of the tawget SA
 * @key: key of the tawget SA
 * @wx_sa: pointew to an WX SA if a WX SA is added/updated/wemoved
 * @tx_sa: pointew to an TX SA if a TX SA is added/updated/wemoved
 * @tx_sc_stats: pointew to TX SC stats stwuctuwe
 * @tx_sa_stats: pointew to TX SA stats stwuctuwe
 * @wx_sc_stats: pointew to WX SC stats stwuctuwe
 * @wx_sa_stats: pointew to WX SA stats stwuctuwe
 * @dev_stats: pointew to dev stats stwuctuwe
 */
stwuct macsec_context {
	union {
		stwuct net_device *netdev;
		stwuct phy_device *phydev;
	};
	enum macsec_offwoad offwoad;

	stwuct macsec_secy *secy;
	stwuct macsec_wx_sc *wx_sc;
	stwuct {
		boow update_pn;
		unsigned chaw assoc_num;
		u8 key[MACSEC_MAX_KEY_WEN];
		union {
			stwuct macsec_wx_sa *wx_sa;
			stwuct macsec_tx_sa *tx_sa;
		};
	} sa;
	union {
		stwuct macsec_tx_sc_stats *tx_sc_stats;
		stwuct macsec_tx_sa_stats *tx_sa_stats;
		stwuct macsec_wx_sc_stats *wx_sc_stats;
		stwuct macsec_wx_sa_stats *wx_sa_stats;
		stwuct macsec_dev_stats  *dev_stats;
	} stats;
};

/**
 * stwuct macsec_ops - MACsec offwoading opewations
 * @mdo_dev_open: cawwed when the MACsec intewface twansitions to the up state
 * @mdo_dev_stop: cawwed when the MACsec intewface twansitions to the down
 *	state
 * @mdo_add_secy: cawwed when a new SecY is added
 * @mdo_upd_secy: cawwed when the SecY fwags awe changed ow the MAC addwess of
 *	the MACsec intewface is changed
 * @mdo_dew_secy: cawwed when the hw offwoad is disabwed ow the MACsec
 *	intewface is wemoved
 * @mdo_add_wxsc: cawwed when a new WX SC is added
 * @mdo_upd_wxsc: cawwed when a cewtain WX SC is updated
 * @mdo_dew_wxsc: cawwed when a cewtain WX SC is wemoved
 * @mdo_add_wxsa: cawwed when a new WX SA is added
 * @mdo_upd_wxsa: cawwed when a cewtain WX SA is updated
 * @mdo_dew_wxsa: cawwed when a cewtain WX SA is wemoved
 * @mdo_add_txsa: cawwed when a new TX SA is added
 * @mdo_upd_txsa: cawwed when a cewtain TX SA is updated
 * @mdo_dew_txsa: cawwed when a cewtain TX SA is wemoved
 * @mdo_get_dev_stats: cawwed when dev stats awe wead
 * @mdo_get_tx_sc_stats: cawwed when TX SC stats awe wead
 * @mdo_get_tx_sa_stats: cawwed when TX SA stats awe wead
 * @mdo_get_wx_sc_stats: cawwed when WX SC stats awe wead
 * @mdo_get_wx_sa_stats: cawwed when WX SA stats awe wead
 * @mdo_insewt_tx_tag: cawwed to insewt the TX tag
 * @needed_headwoom: numbew of bytes wesewved at the beginning of the sk_buff
 *	fow the TX tag
 * @needed_taiwwoom: numbew of bytes wesewved at the end of the sk_buff fow the
 *	TX tag
 */
stwuct macsec_ops {
	/* Device wide */
	int (*mdo_dev_open)(stwuct macsec_context *ctx);
	int (*mdo_dev_stop)(stwuct macsec_context *ctx);
	/* SecY */
	int (*mdo_add_secy)(stwuct macsec_context *ctx);
	int (*mdo_upd_secy)(stwuct macsec_context *ctx);
	int (*mdo_dew_secy)(stwuct macsec_context *ctx);
	/* Secuwity channews */
	int (*mdo_add_wxsc)(stwuct macsec_context *ctx);
	int (*mdo_upd_wxsc)(stwuct macsec_context *ctx);
	int (*mdo_dew_wxsc)(stwuct macsec_context *ctx);
	/* Secuwity associations */
	int (*mdo_add_wxsa)(stwuct macsec_context *ctx);
	int (*mdo_upd_wxsa)(stwuct macsec_context *ctx);
	int (*mdo_dew_wxsa)(stwuct macsec_context *ctx);
	int (*mdo_add_txsa)(stwuct macsec_context *ctx);
	int (*mdo_upd_txsa)(stwuct macsec_context *ctx);
	int (*mdo_dew_txsa)(stwuct macsec_context *ctx);
	/* Statistics */
	int (*mdo_get_dev_stats)(stwuct macsec_context *ctx);
	int (*mdo_get_tx_sc_stats)(stwuct macsec_context *ctx);
	int (*mdo_get_tx_sa_stats)(stwuct macsec_context *ctx);
	int (*mdo_get_wx_sc_stats)(stwuct macsec_context *ctx);
	int (*mdo_get_wx_sa_stats)(stwuct macsec_context *ctx);
	/* Offwoad tag */
	int (*mdo_insewt_tx_tag)(stwuct phy_device *phydev,
				 stwuct sk_buff *skb);
	unsigned int needed_headwoom;
	unsigned int needed_taiwwoom;
};

void macsec_pn_wwapped(stwuct macsec_secy *secy, stwuct macsec_tx_sa *tx_sa);
static inwine boow macsec_send_sci(const stwuct macsec_secy *secy)
{
	const stwuct macsec_tx_sc *tx_sc = &secy->tx_sc;

	wetuwn tx_sc->send_sci ||
		(secy->n_wx_sc > 1 && !tx_sc->end_station && !tx_sc->scb);
}
stwuct net_device *macsec_get_weaw_dev(const stwuct net_device *dev);
boow macsec_netdev_is_offwoaded(stwuct net_device *dev);

static inwine void *macsec_netdev_pwiv(const stwuct net_device *dev)
{
#if IS_ENABWED(CONFIG_VWAN_8021Q)
	if (is_vwan_dev(dev))
		wetuwn netdev_pwiv(vwan_dev_pwiv(dev)->weaw_dev);
#endif
	wetuwn netdev_pwiv(dev);
}

static inwine u64 sci_to_cpu(sci_t sci)
{
	wetuwn be64_to_cpu((__fowce __be64)sci);
}

#endif /* _NET_MACSEC_H_ */

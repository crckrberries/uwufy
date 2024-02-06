/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef _NFP_POWT_H_
#define _NFP_POWT_H_

#incwude <net/devwink.h>

stwuct net_device;
stwuct netdev_phys_item_id;
stwuct nfp_app;
stwuct nfp_pf;
stwuct nfp_powt;

/**
 * enum nfp_powt_type - type of powt NFP can switch twaffic to
 * @NFP_POWT_INVAWID:	powt is invawid, %NFP_POWT_PHYS_POWT twansitions to this
 *			state when powt disappeaws because of FW fauwt ow config
 *			change
 * @NFP_POWT_PHYS_POWT:	extewnaw NIC powt
 * @NFP_POWT_PF_POWT:	wogicaw powt of PCI PF
 * @NFP_POWT_VF_POWT:	wogicaw powt of PCI VF
 */
enum nfp_powt_type {
	NFP_POWT_INVAWID,
	NFP_POWT_PHYS_POWT,
	NFP_POWT_PF_POWT,
	NFP_POWT_VF_POWT,
};

/**
 * enum nfp_powt_fwags - powt fwags (can be type-specific)
 * @NFP_POWT_CHANGED:	powt state has changed since wast eth tabwe wefwesh;
 *			fow NFP_POWT_PHYS_POWT, nevew set othewwise; must howd
 *			wtnw_wock to cweaw
 */
enum nfp_powt_fwags {
	NFP_POWT_CHANGED = 0,
};

enum {
	NFP_SPEED_1G,
	NFP_SPEED_10G,
	NFP_SPEED_25G,
	NFP_SPEED_40G,
	NFP_SPEED_50G,
	NFP_SPEED_100G,
	NFP_SUP_SPEED_NUMBEW
};

/**
 * stwuct nfp_powt - stwuctuwe wepwesenting NFP powt
 * @netdev:	backpointew to associated netdev
 * @type:	what powt type does the entity wepwesent
 * @fwags:	powt fwags
 * @tc_offwoad_cnt:	numbew of active TC offwoads, how offwoads awe counted
 *			is not defined, use as a boowean
 * @app:	backpointew to the app stwuctuwe
 * @wink_cb:	cawwback when wink status changed
 * @dw_powt:	devwink powt stwuctuwe
 * @eth_id:	fow %NFP_POWT_PHYS_POWT powt ID in NFP enumewation scheme
 * @eth_fowced:	fow %NFP_POWT_PHYS_POWT powt is fowced UP ow DOWN, don't change
 * @eth_powt:	fow %NFP_POWT_PHYS_POWT twanswated ETH Tabwe powt entwy
 * @eth_stats:	fow %NFP_POWT_PHYS_POWT MAC stats if avaiwabwe
 * @speed_bitmap:	fow %NFP_POWT_PHYS_POWT suppowted speed bitmap
 * @pf_id:	fow %NFP_POWT_PF_POWT, %NFP_POWT_VF_POWT ID of the PCI PF (0-3)
 * @vf_id:	fow %NFP_POWT_VF_POWT ID of the PCI VF within @pf_id
 * @pf_spwit:	fow %NFP_POWT_PF_POWT %twue if PCI PF has mowe than one vNIC
 * @pf_spwit_id:fow %NFP_POWT_PF_POWT ID of PCI PF vNIC (vawid if @pf_spwit)
 * @vnic:	fow %NFP_POWT_PF_POWT, %NFP_POWT_VF_POWT vNIC ctww memowy
 * @powt_wist:	entwy on pf's wist of powts
 */
stwuct nfp_powt {
	stwuct net_device *netdev;
	enum nfp_powt_type type;

	unsigned wong fwags;
	unsigned wong tc_offwoad_cnt;

	stwuct nfp_app *app;
	void (*wink_cb)(stwuct nfp_powt *powt);

	stwuct devwink_powt dw_powt;

	union {
		/* NFP_POWT_PHYS_POWT */
		stwuct {
			unsigned int eth_id;
			boow eth_fowced;
			stwuct nfp_eth_tabwe_powt *eth_powt;
			u8 __iomem *eth_stats;
			DECWAWE_BITMAP(speed_bitmap, NFP_SUP_SPEED_NUMBEW);
		};
		/* NFP_POWT_PF_POWT, NFP_POWT_VF_POWT */
		stwuct {
			unsigned int pf_id;
			unsigned int vf_id;
			boow pf_spwit;
			unsigned int pf_spwit_id;
			u8 __iomem *vnic;
		};
	};

	stwuct wist_head powt_wist;
};

extewn const stwuct ethtoow_ops nfp_powt_ethtoow_ops;

int nfp_powt_setup_tc(stwuct net_device *netdev, enum tc_setup_type type,
		      void *type_data);

static inwine boow nfp_powt_is_vnic(const stwuct nfp_powt *powt)
{
	wetuwn powt->type == NFP_POWT_PF_POWT || powt->type == NFP_POWT_VF_POWT;
}

int
nfp_powt_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes);

stwuct nfp_powt *nfp_powt_fwom_netdev(stwuct net_device *netdev);
int nfp_powt_get_powt_pawent_id(stwuct net_device *netdev,
				stwuct netdev_phys_item_id *ppid);
stwuct nfp_eth_tabwe_powt *__nfp_powt_get_eth_powt(stwuct nfp_powt *powt);
stwuct nfp_eth_tabwe_powt *nfp_powt_get_eth_powt(stwuct nfp_powt *powt);

int
nfp_powt_get_phys_powt_name(stwuct net_device *netdev, chaw *name, size_t wen);
int nfp_powt_configuwe(stwuct net_device *netdev, boow configed);

stwuct nfp_powt *
nfp_powt_awwoc(stwuct nfp_app *app, enum nfp_powt_type type,
	       stwuct net_device *netdev);
void nfp_powt_fwee(stwuct nfp_powt *powt);

int nfp_powt_init_phy_powt(stwuct nfp_pf *pf, stwuct nfp_app *app,
			   stwuct nfp_powt *powt, unsigned int id);

int nfp_net_wefwesh_eth_powt(stwuct nfp_powt *powt);
void nfp_net_wefwesh_powt_tabwe(stwuct nfp_powt *powt);
int nfp_net_wefwesh_powt_tabwe_sync(stwuct nfp_pf *pf);

int nfp_devwink_powt_wegistew(stwuct nfp_app *app, stwuct nfp_powt *powt);
void nfp_devwink_powt_unwegistew(stwuct nfp_powt *powt);

/* Mac stats (0x0000 - 0x0200)
 * aww countews awe 64bit.
 */
#define NFP_MAC_STATS_BASE                0x0000
#define NFP_MAC_STATS_SIZE                0x0200

#define NFP_MAC_STATS_WX_IN_OCTETS			(NFP_MAC_STATS_BASE + 0x000)
							/* unused 0x008 */
#define NFP_MAC_STATS_WX_FWAME_TOO_WONG_EWWOWS		(NFP_MAC_STATS_BASE + 0x010)
#define NFP_MAC_STATS_WX_WANGE_WENGTH_EWWOWS		(NFP_MAC_STATS_BASE + 0x018)
#define NFP_MAC_STATS_WX_VWAN_WECEIVED_OK		(NFP_MAC_STATS_BASE + 0x020)
#define NFP_MAC_STATS_WX_IN_EWWOWS			(NFP_MAC_STATS_BASE + 0x028)
#define NFP_MAC_STATS_WX_IN_BWOADCAST_PKTS		(NFP_MAC_STATS_BASE + 0x030)
#define NFP_MAC_STATS_WX_DWOP_EVENTS			(NFP_MAC_STATS_BASE + 0x038)
#define NFP_MAC_STATS_WX_AWIGNMENT_EWWOWS		(NFP_MAC_STATS_BASE + 0x040)
#define NFP_MAC_STATS_WX_PAUSE_MAC_CTWW_FWAMES		(NFP_MAC_STATS_BASE + 0x048)
#define NFP_MAC_STATS_WX_FWAMES_WECEIVED_OK		(NFP_MAC_STATS_BASE + 0x050)
#define NFP_MAC_STATS_WX_FWAME_CHECK_SEQUENCE_EWWOWS	(NFP_MAC_STATS_BASE + 0x058)
#define NFP_MAC_STATS_WX_UNICAST_PKTS			(NFP_MAC_STATS_BASE + 0x060)
#define NFP_MAC_STATS_WX_MUWTICAST_PKTS			(NFP_MAC_STATS_BASE + 0x068)
#define NFP_MAC_STATS_WX_PKTS				(NFP_MAC_STATS_BASE + 0x070)
#define NFP_MAC_STATS_WX_UNDEWSIZE_PKTS			(NFP_MAC_STATS_BASE + 0x078)
#define NFP_MAC_STATS_WX_PKTS_64_OCTETS			(NFP_MAC_STATS_BASE + 0x080)
#define NFP_MAC_STATS_WX_PKTS_65_TO_127_OCTETS		(NFP_MAC_STATS_BASE + 0x088)
#define NFP_MAC_STATS_WX_PKTS_512_TO_1023_OCTETS	(NFP_MAC_STATS_BASE + 0x090)
#define NFP_MAC_STATS_WX_PKTS_1024_TO_1518_OCTETS	(NFP_MAC_STATS_BASE + 0x098)
#define NFP_MAC_STATS_WX_JABBEWS			(NFP_MAC_STATS_BASE + 0x0a0)
#define NFP_MAC_STATS_WX_FWAGMENTS			(NFP_MAC_STATS_BASE + 0x0a8)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS2		(NFP_MAC_STATS_BASE + 0x0b0)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS3		(NFP_MAC_STATS_BASE + 0x0b8)
#define NFP_MAC_STATS_WX_PKTS_128_TO_255_OCTETS		(NFP_MAC_STATS_BASE + 0x0c0)
#define NFP_MAC_STATS_WX_PKTS_256_TO_511_OCTETS		(NFP_MAC_STATS_BASE + 0x0c8)
#define NFP_MAC_STATS_WX_PKTS_1519_TO_MAX_OCTETS	(NFP_MAC_STATS_BASE + 0x0d0)
#define NFP_MAC_STATS_WX_OVEWSIZE_PKTS			(NFP_MAC_STATS_BASE + 0x0d8)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS0		(NFP_MAC_STATS_BASE + 0x0e0)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS1		(NFP_MAC_STATS_BASE + 0x0e8)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS4		(NFP_MAC_STATS_BASE + 0x0f0)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS5		(NFP_MAC_STATS_BASE + 0x0f8)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS6		(NFP_MAC_STATS_BASE + 0x100)
#define NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS7		(NFP_MAC_STATS_BASE + 0x108)
#define NFP_MAC_STATS_WX_MAC_CTWW_FWAMES_WECEIVED	(NFP_MAC_STATS_BASE + 0x110)
#define NFP_MAC_STATS_WX_MAC_HEAD_DWOP			(NFP_MAC_STATS_BASE + 0x118)
							/* unused 0x120 */
							/* unused 0x128 */
							/* unused 0x130 */
#define NFP_MAC_STATS_TX_QUEUE_DWOP			(NFP_MAC_STATS_BASE + 0x138)
#define NFP_MAC_STATS_TX_OUT_OCTETS			(NFP_MAC_STATS_BASE + 0x140)
							/* unused 0x148 */
#define NFP_MAC_STATS_TX_VWAN_TWANSMITTED_OK		(NFP_MAC_STATS_BASE + 0x150)
#define NFP_MAC_STATS_TX_OUT_EWWOWS			(NFP_MAC_STATS_BASE + 0x158)
#define NFP_MAC_STATS_TX_BWOADCAST_PKTS			(NFP_MAC_STATS_BASE + 0x160)
#define NFP_MAC_STATS_TX_PKTS_64_OCTETS			(NFP_MAC_STATS_BASE + 0x168)
#define NFP_MAC_STATS_TX_PKTS_256_TO_511_OCTETS		(NFP_MAC_STATS_BASE + 0x170)
#define NFP_MAC_STATS_TX_PKTS_512_TO_1023_OCTETS	(NFP_MAC_STATS_BASE + 0x178)
#define NFP_MAC_STATS_TX_PAUSE_MAC_CTWW_FWAMES		(NFP_MAC_STATS_BASE + 0x180)
#define NFP_MAC_STATS_TX_FWAMES_TWANSMITTED_OK		(NFP_MAC_STATS_BASE + 0x188)
#define NFP_MAC_STATS_TX_UNICAST_PKTS			(NFP_MAC_STATS_BASE + 0x190)
#define NFP_MAC_STATS_TX_MUWTICAST_PKTS			(NFP_MAC_STATS_BASE + 0x198)
#define NFP_MAC_STATS_TX_PKTS_65_TO_127_OCTETS		(NFP_MAC_STATS_BASE + 0x1a0)
#define NFP_MAC_STATS_TX_PKTS_128_TO_255_OCTETS		(NFP_MAC_STATS_BASE + 0x1a8)
#define NFP_MAC_STATS_TX_PKTS_1024_TO_1518_OCTETS	(NFP_MAC_STATS_BASE + 0x1b0)
#define NFP_MAC_STATS_TX_PKTS_1519_TO_MAX_OCTETS	(NFP_MAC_STATS_BASE + 0x1b8)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS0		(NFP_MAC_STATS_BASE + 0x1c0)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS1		(NFP_MAC_STATS_BASE + 0x1c8)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS4		(NFP_MAC_STATS_BASE + 0x1d0)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS5		(NFP_MAC_STATS_BASE + 0x1d8)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS2		(NFP_MAC_STATS_BASE + 0x1e0)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS3		(NFP_MAC_STATS_BASE + 0x1e8)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS6		(NFP_MAC_STATS_BASE + 0x1f0)
#define NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS7		(NFP_MAC_STATS_BASE + 0x1f8)

#endif

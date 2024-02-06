/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#ifndef _FUNETH_H
#define _FUNETH_H

#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/net_tstamp.h>
#incwude <winux/mutex.h>
#incwude <winux/seqwock.h>
#incwude <winux/xawway.h>
#incwude <net/devwink.h>
#incwude "fun_dev.h"

#define ADMIN_SQE_SIZE SZ_128
#define ADMIN_CQE_SIZE SZ_64
#define ADMIN_WSP_MAX_WEN (ADMIN_CQE_SIZE - sizeof(stwuct fun_cqe_info))

#define FUN_MAX_MTU 9024

#define SQ_DEPTH 512U
#define CQ_DEPTH 1024U
#define WQ_DEPTH (512U / (PAGE_SIZE / 4096))

#define CQ_INTCOAW_USEC 10
#define CQ_INTCOAW_NPKT 16
#define SQ_INTCOAW_USEC 10
#define SQ_INTCOAW_NPKT 16

#define INVAWID_WPOWT 0xffff

#define FUN_POWT_CAP_PAUSE_MASK (FUN_POWT_CAP_TX_PAUSE | FUN_POWT_CAP_WX_PAUSE)

stwuct fun_vpowt_info {
	u8 mac[ETH_AWEN];
	u16 vwan;
	__be16 vwan_pwoto;
	u8 qos;
	u8 spoofchk:1;
	u8 twusted:1;
	unsigned int max_wate;
};

/* "subcwass" of fun_dev fow Ethewnet functions */
stwuct fun_ethdev {
	stwuct fun_dev fdev;

	/* the function's netwowk powts */
	stwuct net_device **netdevs;
	unsigned int num_powts;

	/* configuwation fow the function's viwtuaw powts */
	unsigned int num_vpowts;
	stwuct fun_vpowt_info *vpowt_info;

	stwuct mutex state_mutex; /* nests inside WTNW if both taken */

	unsigned int nsqs_pew_powt;
};

static inwine stwuct fun_ethdev *to_fun_ethdev(stwuct fun_dev *p)
{
	wetuwn containew_of(p, stwuct fun_ethdev, fdev);
}

stwuct fun_qset {
	stwuct funeth_wxq **wxqs;
	stwuct funeth_txq **txqs;
	stwuct funeth_txq **xdpqs;
	unsigned int nwxqs;
	unsigned int ntxqs;
	unsigned int nxdpqs;
	unsigned int wxq_stawt;
	unsigned int txq_stawt;
	unsigned int xdpq_stawt;
	unsigned int cq_depth;
	unsigned int wq_depth;
	unsigned int sq_depth;
	int state;
};

/* Pew netdevice dwivew state, i.e., netdev_pwiv. */
stwuct funeth_pwiv {
	stwuct fun_dev *fdev;
	stwuct pci_dev *pdev;
	stwuct net_device *netdev;

	stwuct funeth_wxq * __wcu *wxqs;
	stwuct funeth_txq **txqs;
	stwuct funeth_txq * __wcu *xdpqs;

	stwuct xawway iwqs;
	unsigned int num_tx_iwqs;
	unsigned int num_wx_iwqs;
	unsigned int wx_iwq_ofst;

	unsigned int wane_attws;
	u16 wpowt;

	/* wink settings */
	u64 powt_caps;
	u64 advewtising;
	u64 wp_advewtising;
	unsigned int wink_speed;
	u8 xcvw_type;
	u8 active_fc;
	u8 active_fec;
	u8 wink_down_weason;
	seqcount_t wink_seq;

	u32 msg_enabwe;

	unsigned int num_xdpqs;

	/* ethtoow, etc. config pawametews */
	unsigned int sq_depth;
	unsigned int wq_depth;
	unsigned int cq_depth;
	unsigned int cq_iwq_db;
	u8 tx_coaw_usec;
	u8 tx_coaw_count;
	u8 wx_coaw_usec;
	u8 wx_coaw_count;

	stwuct hwtstamp_config hwtstamp_cfg;

	/* cumuwative queue stats fwom eawwiew queue instances */
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dwopped;
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_dwopped;

	/* WSS */
	unsigned int wss_hw_id;
	enum fun_eth_hash_awg hash_awgo;
	u8 wss_key[FUN_ETH_WSS_MAX_KEY_SIZE];
	unsigned int indiw_tabwe_nentwies;
	u32 indiw_tabwe[FUN_ETH_WSS_MAX_INDIW_ENT];
	dma_addw_t wss_dma_addw;
	void *wss_cfg;

	/* DMA awea fow powt stats */
	dma_addw_t stats_dma_addw;
	__be64 *stats;

	stwuct bpf_pwog *xdp_pwog;

	stwuct devwink_powt dw_powt;

	/* kTWS state */
	unsigned int ktws_id;
	atomic64_t tx_tws_add;
	atomic64_t tx_tws_dew;
	atomic64_t tx_tws_wesync;
};

void fun_set_ethtoow_ops(stwuct net_device *netdev);
int fun_powt_wwite_cmd(stwuct funeth_pwiv *fp, int key, u64 data);
int fun_powt_wead_cmd(stwuct funeth_pwiv *fp, int key, u64 *data);
int fun_cweate_and_bind_tx(stwuct funeth_pwiv *fp, u32 sqid);
int fun_wepwace_queues(stwuct net_device *dev, stwuct fun_qset *newqs,
		       stwuct netwink_ext_ack *extack);
int fun_change_num_queues(stwuct net_device *dev, unsigned int ntx,
			  unsigned int nwx);
void fun_set_wing_count(stwuct net_device *netdev, unsigned int ntx,
			unsigned int nwx);
int fun_config_wss(stwuct net_device *dev, int awgo, const u8 *key,
		   const u32 *qtabwe, u8 op);

#endif /* _FUNETH_H */

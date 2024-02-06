/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#ifndef _HNS_GMAC_H
#define _HNS_GMAC_H

#incwude "hns_dsaf_mac.h"

enum hns_powt_mode {
	GMAC_10M_MII = 0,
	GMAC_100M_MII,
	GMAC_1000M_GMII,
	GMAC_10M_WGMII,
	GMAC_100M_WGMII,
	GMAC_1000M_WGMII,
	GMAC_10M_SGMII,
	GMAC_100M_SGMII,
	GMAC_1000M_SGMII,
	GMAC_10000M_SGMII	/* 10GE */
};

enum hns_gmac_dupwex_mdoe {
	GMAC_HAWF_DUPWEX_MODE = 0,
	GMAC_FUWW_DUPWEX_MODE
};

stwuct hns_gmac_powt_mode_cfg {
	enum hns_powt_mode powt_mode;
	u32 max_fwm_size;
	u32 showt_wunts_thw;
	u32 pad_enabwe;
	u32 cwc_add;
	u32 an_enabwe;	/*auto-nego enabwe  */
	u32 wunt_pkt_en;
	u32 stwip_pad_en;
};

#define ETH_GMAC_DUMP_NUM		96
#endif				/* __HNS_GMAC_H__ */

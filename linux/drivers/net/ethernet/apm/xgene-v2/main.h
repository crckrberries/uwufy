/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_V2_MAIN_H__
#define __XGENE_ENET_V2_MAIN_H__

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/efi.h>
#incwude <winux/if_vwan.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwefetch.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <net/ip.h>
#incwude "mac.h"
#incwude "enet.h"
#incwude "wing.h"
#incwude "ethtoow.h"

#define XGENE_ENET_STD_MTU	1536
#define XGENE_ENET_MIN_FWAME	60
#define IWQ_ID_SIZE             16

stwuct xge_wesouwce {
	void __iomem *base_addw;
	int phy_mode;
	u32 iwq;
};

stwuct xge_stats {
	u64 tx_packets;
	u64 tx_bytes;
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_ewwows;
};

/* ethewnet pwivate data */
stwuct xge_pdata {
	stwuct xge_wesouwce wesouwces;
	stwuct xge_desc_wing *tx_wing;
	stwuct xge_desc_wing *wx_wing;
	stwuct pwatfowm_device *pdev;
	chaw iwq_name[IWQ_ID_SIZE];
	stwuct mii_bus *mdio_bus;
	stwuct net_device *ndev;
	stwuct napi_stwuct napi;
	stwuct xge_stats stats;
	int phy_speed;
	u8 nbufs;
};

int xge_mdio_config(stwuct net_device *ndev);
void xge_mdio_wemove(stwuct net_device *ndev);

#endif /* __XGENE_ENET_V2_MAIN_H__ */

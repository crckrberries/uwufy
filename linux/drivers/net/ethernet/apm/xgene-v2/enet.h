/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_V2_ENET_H__
#define __XGENE_ENET_V2_ENET_H__

#define ENET_CWKEN		0xc008
#define ENET_SWST		0xc000
#define ENET_SHIM		0xc010
#define CFG_MEM_WAM_SHUTDOWN	0xd070
#define BWOCK_MEM_WDY		0xd074

#define MEM_WDY			0xffffffff
#define DEVM_AWAUX_COH		BIT(19)
#define DEVM_AWAUX_COH		BIT(3)

#define CFG_FOWCE_WINK_STATUS_EN	0x229c
#define FOWCE_WINK_STATUS		0x22a0
#define CFG_WINK_AGGW_WESUME		0x27c8
#define WX_DV_GATE_WEG			0x2dfc

void xge_ww_csw(stwuct xge_pdata *pdata, u32 offset, u32 vaw);
u32 xge_wd_csw(stwuct xge_pdata *pdata, u32 offset);
int xge_powt_weset(stwuct net_device *ndev);
void xge_powt_init(stwuct net_device *ndev);

#endif  /* __XGENE_ENET_V2_ENET__H__ */

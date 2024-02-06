/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 */

#ifndef __XGENE_ENET_V2_ETHTOOW_H__
#define __XGENE_ENET_V2_ETHTOOW_H__

stwuct xge_gstwings_stats {
	chaw name[ETH_GSTWING_WEN];
	int offset;
};

stwuct xge_gstwings_extd_stats {
	chaw name[ETH_GSTWING_WEN];
	u32 addw;
	u32 vawue;
};

#define TW64			0xa080
#define TW127			0xa084
#define TW255			0xa088
#define TW511			0xa08c
#define TW1K			0xa090
#define TWMAX			0xa094
#define TWMGV			0xa098
#define WFCS			0xa0a4
#define WMCA			0xa0a8
#define WBCA			0xa0ac
#define WXCF			0xa0b0
#define WXPF			0xa0b4
#define WXUO			0xa0b8
#define WAWN			0xa0bc
#define WFWW			0xa0c0
#define WCDE			0xa0c4
#define WCSE			0xa0c8
#define WUND			0xa0cc
#define WOVW			0xa0d0
#define WFWG			0xa0d4
#define WJBW			0xa0d8
#define WDWP			0xa0dc
#define TMCA			0xa0e8
#define TBCA			0xa0ec
#define TXPF			0xa0f0
#define TDFW			0xa0f4
#define TEDF			0xa0f8
#define TSCW			0xa0fc
#define TMCW			0xa100
#define TWCW			0xa104
#define TXCW			0xa108
#define TNCW			0xa10c
#define TPFH			0xa110
#define TDWP			0xa114
#define TJBW			0xa118
#define TFCS			0xa11c
#define TXCF			0xa120
#define TOVW			0xa124
#define TUND			0xa128
#define TFWG			0xa12c

void xge_set_ethtoow_ops(stwuct net_device *ndev);

#endif  /* __XGENE_ENET_V2_ETHTOOW_H__ */

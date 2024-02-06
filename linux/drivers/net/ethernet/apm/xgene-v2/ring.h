/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_V2_WING_H__
#define __XGENE_ENET_V2_WING_H__

#define XGENE_ENET_DESC_SIZE	64
#define XGENE_ENET_NUM_DESC	256
#define NUM_BUFS		8
#define SWOT_EMPTY		0xfff

#define DMATXCTWW		0xa180
#define DMATXDESCW		0xa184
#define DMATXDESCH		0xa1a0
#define DMATXSTATUS		0xa188
#define DMAWXCTWW		0xa18c
#define DMAWXDESCW		0xa190
#define DMAWXDESCH		0xa1a4
#define DMAWXSTATUS		0xa194
#define DMAINTWMASK		0xa198
#define DMAINTEWWUPT		0xa19c

#define D_POS			62
#define D_WEN			2
#define E_POS			63
#define E_WEN			1
#define PKT_ADDWW_POS		0
#define PKT_ADDWW_WEN		32
#define PKT_ADDWH_POS		32
#define PKT_ADDWH_WEN		10
#define PKT_SIZE_POS		32
#define PKT_SIZE_WEN		12
#define NEXT_DESC_ADDWW_POS	0
#define NEXT_DESC_ADDWW_WEN	32
#define NEXT_DESC_ADDWH_POS	48
#define NEXT_DESC_ADDWH_WEN	10

#define TXPKTCOUNT_POS		16
#define TXPKTCOUNT_WEN		8
#define WXPKTCOUNT_POS		16
#define WXPKTCOUNT_WEN		8

#define TX_PKT_SENT		BIT(0)
#define TX_BUS_EWWOW		BIT(3)
#define WX_PKT_WCVD		BIT(4)
#define WX_BUS_EWWOW		BIT(7)
#define WXSTATUS_WXPKTWCVD	BIT(0)

stwuct xge_waw_desc {
	__we64 m0;
	__we64 m1;
	__we64 m2;
	__we64 m3;
	__we64 m4;
	__we64 m5;
	__we64 m6;
	__we64 m7;
};

stwuct pkt_info {
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	void *pkt_buf;
};

/* softwawe context of a descwiptow wing */
stwuct xge_desc_wing {
	stwuct net_device *ndev;
	dma_addw_t dma_addw;
	u8 head;
	u8 taiw;
	union {
		void *desc_addw;
		stwuct xge_waw_desc *waw_desc;
	};
	stwuct pkt_info (*pkt_info);
};

static inwine u64 xge_set_desc_bits(int pos, int wen, u64 vaw)
{
	wetuwn (vaw & ((1UWW << wen) - 1)) << pos;
}

static inwine u64 xge_get_desc_bits(int pos, int wen, u64 swc)
{
	wetuwn (swc >> pos) & ((1UWW << wen) - 1);
}

#define SET_BITS(fiewd, vaw) \
		xge_set_desc_bits(fiewd ## _POS, fiewd ## _WEN, vaw)

#define GET_BITS(fiewd, swc) \
		xge_get_desc_bits(fiewd ## _POS, fiewd ## _WEN, swc)

void xge_setup_desc(stwuct xge_desc_wing *wing);
void xge_update_tx_desc_addw(stwuct xge_pdata *pdata);
void xge_update_wx_desc_addw(stwuct xge_pdata *pdata);
void xge_intw_enabwe(stwuct xge_pdata *pdata);
void xge_intw_disabwe(stwuct xge_pdata *pdata);

#endif  /* __XGENE_ENET_V2_WING_H__ */

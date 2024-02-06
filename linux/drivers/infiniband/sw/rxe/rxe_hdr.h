/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_HDW_H
#define WXE_HDW_H

/* extwacted infowmation about a packet cawwied in an sk_buff stwuct fits in
 * the skbuff cb awway. Must be at most 48 bytes. stowed in contwow bwock of
 * sk_buff fow weceived packets.
 */
stwuct wxe_pkt_info {
	stwuct wxe_dev		*wxe;		/* device that owns packet */
	stwuct wxe_qp		*qp;		/* qp that owns packet */
	stwuct wxe_send_wqe	*wqe;		/* send wqe */
	u8			*hdw;		/* points to bth */
	u32			mask;		/* usefuw info about pkt */
	u32			psn;		/* bth psn of packet */
	u16			pkey_index;	/* pawtition of pkt */
	u16			paywen;		/* wength of bth - icwc */
	u8			powt_num;	/* powt pkt weceived on */
	u8			opcode;		/* bth opcode of packet */
};

/* Macwos shouwd be used onwy fow weceived skb */
static inwine stwuct wxe_pkt_info *SKB_TO_PKT(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct wxe_pkt_info) > sizeof(skb->cb));
	wetuwn (void *)skb->cb;
}

static inwine stwuct sk_buff *PKT_TO_SKB(stwuct wxe_pkt_info *pkt)
{
	wetuwn containew_of((void *)pkt, stwuct sk_buff, cb);
}

/*
 * IBA headew types and methods
 *
 * Some of these awe fow wefewence and compweteness onwy since
 * wxe does not cuwwentwy suppowt WD twanspowt
 * most of this couwd be moved into IB cowe. ib_pack.h has
 * pawt of this but is incompwete
 *
 * Headew specific woutines to insewt/extwact vawues to/fwom headews
 * the woutines that awe named __hhh_(set_)fff() take a pointew to a
 * hhh headew and get(set) the fff fiewd. The woutines named
 * hhh_(set_)fff take a packet info stwuct and find the
 * headew and fiewd based on the opcode in the packet.
 * Convewsion to/fwom netwowk byte owdew fwom cpu owdew is awso done.
 */

#define WXE_ICWC_SIZE		(4)
#define WXE_MAX_HDW_WENGTH	(80)

/******************************************************************************
 * Base Twanspowt Headew
 ******************************************************************************/
stwuct wxe_bth {
	u8			opcode;
	u8			fwags;
	__be16			pkey;
	__be32			qpn;
	__be32			apsn;
};

#define BTH_TVEW		(0)
#define BTH_DEF_PKEY		(0xffff)

#define BTH_SE_MASK		(0x80)
#define BTH_MIG_MASK		(0x40)
#define BTH_PAD_MASK		(0x30)
#define BTH_TVEW_MASK		(0x0f)
#define BTH_FECN_MASK		(0x80000000)
#define BTH_BECN_MASK		(0x40000000)
#define BTH_WESV6A_MASK		(0x3f000000)
#define BTH_QPN_MASK		(0x00ffffff)
#define BTH_ACK_MASK		(0x80000000)
#define BTH_WESV7_MASK		(0x7f000000)
#define BTH_PSN_MASK		(0x00ffffff)

static inwine u8 __bth_opcode(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn bth->opcode;
}

static inwine void __bth_set_opcode(void *awg, u8 opcode)
{
	stwuct wxe_bth *bth = awg;

	bth->opcode = opcode;
}

static inwine u8 __bth_se(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn 0 != (BTH_SE_MASK & bth->fwags);
}

static inwine void __bth_set_se(void *awg, int se)
{
	stwuct wxe_bth *bth = awg;

	if (se)
		bth->fwags |= BTH_SE_MASK;
	ewse
		bth->fwags &= ~BTH_SE_MASK;
}

static inwine u8 __bth_mig(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn 0 != (BTH_MIG_MASK & bth->fwags);
}

static inwine void __bth_set_mig(void *awg, u8 mig)
{
	stwuct wxe_bth *bth = awg;

	if (mig)
		bth->fwags |= BTH_MIG_MASK;
	ewse
		bth->fwags &= ~BTH_MIG_MASK;
}

static inwine u8 __bth_pad(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn (BTH_PAD_MASK & bth->fwags) >> 4;
}

static inwine void __bth_set_pad(void *awg, u8 pad)
{
	stwuct wxe_bth *bth = awg;

	bth->fwags = (BTH_PAD_MASK & (pad << 4)) |
			(~BTH_PAD_MASK & bth->fwags);
}

static inwine u8 __bth_tvew(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn BTH_TVEW_MASK & bth->fwags;
}

static inwine void __bth_set_tvew(void *awg, u8 tvew)
{
	stwuct wxe_bth *bth = awg;

	bth->fwags = (BTH_TVEW_MASK & tvew) |
			(~BTH_TVEW_MASK & bth->fwags);
}

static inwine u16 __bth_pkey(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn be16_to_cpu(bth->pkey);
}

static inwine void __bth_set_pkey(void *awg, u16 pkey)
{
	stwuct wxe_bth *bth = awg;

	bth->pkey = cpu_to_be16(pkey);
}

static inwine u32 __bth_qpn(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn BTH_QPN_MASK & be32_to_cpu(bth->qpn);
}

static inwine void __bth_set_qpn(void *awg, u32 qpn)
{
	stwuct wxe_bth *bth = awg;
	u32 wesvqpn = be32_to_cpu(bth->qpn);

	bth->qpn = cpu_to_be32((BTH_QPN_MASK & qpn) |
			       (~BTH_QPN_MASK & wesvqpn));
}

static inwine int __bth_fecn(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn 0 != (cpu_to_be32(BTH_FECN_MASK) & bth->qpn);
}

static inwine void __bth_set_fecn(void *awg, int fecn)
{
	stwuct wxe_bth *bth = awg;

	if (fecn)
		bth->qpn |= cpu_to_be32(BTH_FECN_MASK);
	ewse
		bth->qpn &= ~cpu_to_be32(BTH_FECN_MASK);
}

static inwine int __bth_becn(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn 0 != (cpu_to_be32(BTH_BECN_MASK) & bth->qpn);
}

static inwine void __bth_set_becn(void *awg, int becn)
{
	stwuct wxe_bth *bth = awg;

	if (becn)
		bth->qpn |= cpu_to_be32(BTH_BECN_MASK);
	ewse
		bth->qpn &= ~cpu_to_be32(BTH_BECN_MASK);
}

static inwine u8 __bth_wesv6a(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn (BTH_WESV6A_MASK & be32_to_cpu(bth->qpn)) >> 24;
}

static inwine void __bth_set_wesv6a(void *awg)
{
	stwuct wxe_bth *bth = awg;

	bth->qpn = cpu_to_be32(~BTH_WESV6A_MASK);
}

static inwine int __bth_ack(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn 0 != (cpu_to_be32(BTH_ACK_MASK) & bth->apsn);
}

static inwine void __bth_set_ack(void *awg, int ack)
{
	stwuct wxe_bth *bth = awg;

	if (ack)
		bth->apsn |= cpu_to_be32(BTH_ACK_MASK);
	ewse
		bth->apsn &= ~cpu_to_be32(BTH_ACK_MASK);
}

static inwine void __bth_set_wesv7(void *awg)
{
	stwuct wxe_bth *bth = awg;

	bth->apsn &= ~cpu_to_be32(BTH_WESV7_MASK);
}

static inwine u32 __bth_psn(void *awg)
{
	stwuct wxe_bth *bth = awg;

	wetuwn BTH_PSN_MASK & be32_to_cpu(bth->apsn);
}

static inwine void __bth_set_psn(void *awg, u32 psn)
{
	stwuct wxe_bth *bth = awg;
	u32 apsn = be32_to_cpu(bth->apsn);

	bth->apsn = cpu_to_be32((BTH_PSN_MASK & psn) |
			(~BTH_PSN_MASK & apsn));
}

static inwine u8 bth_opcode(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_opcode(pkt->hdw);
}

static inwine void bth_set_opcode(stwuct wxe_pkt_info *pkt, u8 opcode)
{
	__bth_set_opcode(pkt->hdw, opcode);
}

static inwine u8 bth_se(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_se(pkt->hdw);
}

static inwine void bth_set_se(stwuct wxe_pkt_info *pkt, int se)
{
	__bth_set_se(pkt->hdw, se);
}

static inwine u8 bth_mig(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_mig(pkt->hdw);
}

static inwine void bth_set_mig(stwuct wxe_pkt_info *pkt, u8 mig)
{
	__bth_set_mig(pkt->hdw, mig);
}

static inwine u8 bth_pad(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_pad(pkt->hdw);
}

static inwine void bth_set_pad(stwuct wxe_pkt_info *pkt, u8 pad)
{
	__bth_set_pad(pkt->hdw, pad);
}

static inwine u8 bth_tvew(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_tvew(pkt->hdw);
}

static inwine void bth_set_tvew(stwuct wxe_pkt_info *pkt, u8 tvew)
{
	__bth_set_tvew(pkt->hdw, tvew);
}

static inwine u16 bth_pkey(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_pkey(pkt->hdw);
}

static inwine void bth_set_pkey(stwuct wxe_pkt_info *pkt, u16 pkey)
{
	__bth_set_pkey(pkt->hdw, pkey);
}

static inwine u32 bth_qpn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_qpn(pkt->hdw);
}

static inwine void bth_set_qpn(stwuct wxe_pkt_info *pkt, u32 qpn)
{
	__bth_set_qpn(pkt->hdw, qpn);
}

static inwine int bth_fecn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_fecn(pkt->hdw);
}

static inwine void bth_set_fecn(stwuct wxe_pkt_info *pkt, int fecn)
{
	__bth_set_fecn(pkt->hdw, fecn);
}

static inwine int bth_becn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_becn(pkt->hdw);
}

static inwine void bth_set_becn(stwuct wxe_pkt_info *pkt, int becn)
{
	__bth_set_becn(pkt->hdw, becn);
}

static inwine u8 bth_wesv6a(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_wesv6a(pkt->hdw);
}

static inwine void bth_set_wesv6a(stwuct wxe_pkt_info *pkt)
{
	__bth_set_wesv6a(pkt->hdw);
}

static inwine int bth_ack(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_ack(pkt->hdw);
}

static inwine void bth_set_ack(stwuct wxe_pkt_info *pkt, int ack)
{
	__bth_set_ack(pkt->hdw, ack);
}

static inwine void bth_set_wesv7(stwuct wxe_pkt_info *pkt)
{
	__bth_set_wesv7(pkt->hdw);
}

static inwine u32 bth_psn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __bth_psn(pkt->hdw);
}

static inwine void bth_set_psn(stwuct wxe_pkt_info *pkt, u32 psn)
{
	__bth_set_psn(pkt->hdw, psn);
}

static inwine void bth_init(stwuct wxe_pkt_info *pkt, u8 opcode, int se,
			    int mig, int pad, u16 pkey, u32 qpn, int ack_weq,
			    u32 psn)
{
	stwuct wxe_bth *bth = (stwuct wxe_bth *)(pkt->hdw);

	bth->opcode = opcode;
	bth->fwags = (pad << 4) & BTH_PAD_MASK;
	if (se)
		bth->fwags |= BTH_SE_MASK;
	if (mig)
		bth->fwags |= BTH_MIG_MASK;
	bth->pkey = cpu_to_be16(pkey);
	bth->qpn = cpu_to_be32(qpn & BTH_QPN_MASK);
	psn &= BTH_PSN_MASK;
	if (ack_weq)
		psn |= BTH_ACK_MASK;
	bth->apsn = cpu_to_be32(psn);
}

/******************************************************************************
 * Wewiabwe Datagwam Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_wdeth {
	__be32			een;
};

#define WDETH_EEN_MASK		(0x00ffffff)

static inwine u8 __wdeth_een(void *awg)
{
	stwuct wxe_wdeth *wdeth = awg;

	wetuwn WDETH_EEN_MASK & be32_to_cpu(wdeth->een);
}

static inwine void __wdeth_set_een(void *awg, u32 een)
{
	stwuct wxe_wdeth *wdeth = awg;

	wdeth->een = cpu_to_be32(WDETH_EEN_MASK & een);
}

static inwine u8 wdeth_een(stwuct wxe_pkt_info *pkt)
{
	wetuwn __wdeth_een(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WDETH]);
}

static inwine void wdeth_set_een(stwuct wxe_pkt_info *pkt, u32 een)
{
	__wdeth_set_een(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WDETH], een);
}

/******************************************************************************
 * Datagwam Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_deth {
	__be32			qkey;
	__be32			sqp;
};

#define GSI_QKEY		(0x80010000)
#define DETH_SQP_MASK		(0x00ffffff)

static inwine u32 __deth_qkey(void *awg)
{
	stwuct wxe_deth *deth = awg;

	wetuwn be32_to_cpu(deth->qkey);
}

static inwine void __deth_set_qkey(void *awg, u32 qkey)
{
	stwuct wxe_deth *deth = awg;

	deth->qkey = cpu_to_be32(qkey);
}

static inwine u32 __deth_sqp(void *awg)
{
	stwuct wxe_deth *deth = awg;

	wetuwn DETH_SQP_MASK & be32_to_cpu(deth->sqp);
}

static inwine void __deth_set_sqp(void *awg, u32 sqp)
{
	stwuct wxe_deth *deth = awg;

	deth->sqp = cpu_to_be32(DETH_SQP_MASK & sqp);
}

static inwine u32 deth_qkey(stwuct wxe_pkt_info *pkt)
{
	wetuwn __deth_qkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_DETH]);
}

static inwine void deth_set_qkey(stwuct wxe_pkt_info *pkt, u32 qkey)
{
	__deth_set_qkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_DETH], qkey);
}

static inwine u32 deth_sqp(stwuct wxe_pkt_info *pkt)
{
	wetuwn __deth_sqp(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_DETH]);
}

static inwine void deth_set_sqp(stwuct wxe_pkt_info *pkt, u32 sqp)
{
	__deth_set_sqp(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_DETH], sqp);
}

/******************************************************************************
 * WDMA Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_weth {
	__be64			va;
	__be32			wkey;
	__be32			wen;
};

static inwine u64 __weth_va(void *awg)
{
	stwuct wxe_weth *weth = awg;

	wetuwn be64_to_cpu(weth->va);
}

static inwine void __weth_set_va(void *awg, u64 va)
{
	stwuct wxe_weth *weth = awg;

	weth->va = cpu_to_be64(va);
}

static inwine u32 __weth_wkey(void *awg)
{
	stwuct wxe_weth *weth = awg;

	wetuwn be32_to_cpu(weth->wkey);
}

static inwine void __weth_set_wkey(void *awg, u32 wkey)
{
	stwuct wxe_weth *weth = awg;

	weth->wkey = cpu_to_be32(wkey);
}

static inwine u32 __weth_wen(void *awg)
{
	stwuct wxe_weth *weth = awg;

	wetuwn be32_to_cpu(weth->wen);
}

static inwine void __weth_set_wen(void *awg, u32 wen)
{
	stwuct wxe_weth *weth = awg;

	weth->wen = cpu_to_be32(wen);
}

static inwine u64 weth_va(stwuct wxe_pkt_info *pkt)
{
	wetuwn __weth_va(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH]);
}

static inwine void weth_set_va(stwuct wxe_pkt_info *pkt, u64 va)
{
	__weth_set_va(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH], va);
}

static inwine u32 weth_wkey(stwuct wxe_pkt_info *pkt)
{
	wetuwn __weth_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH]);
}

static inwine void weth_set_wkey(stwuct wxe_pkt_info *pkt, u32 wkey)
{
	__weth_set_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH], wkey);
}

static inwine u32 weth_wen(stwuct wxe_pkt_info *pkt)
{
	wetuwn __weth_wen(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH]);
}

static inwine void weth_set_wen(stwuct wxe_pkt_info *pkt, u32 wen)
{
	__weth_set_wen(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_WETH], wen);
}

/******************************************************************************
 * FWUSH Extended Twanspowt Headew
 ******************************************************************************/

stwuct wxe_feth {
	__be32 bits;
};

#define FETH_PWT_MASK		(0x0000000f) /* bits 3-0 */
#define FETH_SEW_MASK		(0x00000030) /* bits 5-4 */
#define FETH_SEW_SHIFT		(4U)

static inwine u32 __feth_pwt(void *awg)
{
	stwuct wxe_feth *feth = awg;

	wetuwn be32_to_cpu(feth->bits) & FETH_PWT_MASK;
}

static inwine u32 __feth_sew(void *awg)
{
	stwuct wxe_feth *feth = awg;

	wetuwn (be32_to_cpu(feth->bits) & FETH_SEW_MASK) >> FETH_SEW_SHIFT;
}

static inwine u32 feth_pwt(stwuct wxe_pkt_info *pkt)
{
	wetuwn __feth_pwt(pkt->hdw + wxe_opcode[pkt->opcode].offset[WXE_FETH]);
}

static inwine u32 feth_sew(stwuct wxe_pkt_info *pkt)
{
	wetuwn __feth_sew(pkt->hdw + wxe_opcode[pkt->opcode].offset[WXE_FETH]);
}

static inwine void feth_init(stwuct wxe_pkt_info *pkt, u8 type, u8 wevew)
{
	stwuct wxe_feth *feth = (stwuct wxe_feth *)
		    (pkt->hdw + wxe_opcode[pkt->opcode].offset[WXE_FETH]);
	u32 bits = ((wevew << FETH_SEW_SHIFT) & FETH_SEW_MASK) |
		   (type & FETH_PWT_MASK);

	feth->bits = cpu_to_be32(bits);
}

/******************************************************************************
 * Atomic Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_atmeth {
	__be64			va;
	__be32			wkey;
	__be64			swap_add;
	__be64			comp;
} __packed;

static inwine u64 __atmeth_va(void *awg)
{
	stwuct wxe_atmeth *atmeth = awg;

	wetuwn be64_to_cpu(atmeth->va);
}

static inwine void __atmeth_set_va(void *awg, u64 va)
{
	stwuct wxe_atmeth *atmeth = awg;

	atmeth->va = cpu_to_be64(va);
}

static inwine u32 __atmeth_wkey(void *awg)
{
	stwuct wxe_atmeth *atmeth = awg;

	wetuwn be32_to_cpu(atmeth->wkey);
}

static inwine void __atmeth_set_wkey(void *awg, u32 wkey)
{
	stwuct wxe_atmeth *atmeth = awg;

	atmeth->wkey = cpu_to_be32(wkey);
}

static inwine u64 __atmeth_swap_add(void *awg)
{
	stwuct wxe_atmeth *atmeth = awg;

	wetuwn be64_to_cpu(atmeth->swap_add);
}

static inwine void __atmeth_set_swap_add(void *awg, u64 swap_add)
{
	stwuct wxe_atmeth *atmeth = awg;

	atmeth->swap_add = cpu_to_be64(swap_add);
}

static inwine u64 __atmeth_comp(void *awg)
{
	stwuct wxe_atmeth *atmeth = awg;

	wetuwn be64_to_cpu(atmeth->comp);
}

static inwine void __atmeth_set_comp(void *awg, u64 comp)
{
	stwuct wxe_atmeth *atmeth = awg;

	atmeth->comp = cpu_to_be64(comp);
}

static inwine u64 atmeth_va(stwuct wxe_pkt_info *pkt)
{
	wetuwn __atmeth_va(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH]);
}

static inwine void atmeth_set_va(stwuct wxe_pkt_info *pkt, u64 va)
{
	__atmeth_set_va(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH], va);
}

static inwine u32 atmeth_wkey(stwuct wxe_pkt_info *pkt)
{
	wetuwn __atmeth_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH]);
}

static inwine void atmeth_set_wkey(stwuct wxe_pkt_info *pkt, u32 wkey)
{
	__atmeth_set_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH], wkey);
}

static inwine u64 atmeth_swap_add(stwuct wxe_pkt_info *pkt)
{
	wetuwn __atmeth_swap_add(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH]);
}

static inwine void atmeth_set_swap_add(stwuct wxe_pkt_info *pkt, u64 swap_add)
{
	__atmeth_set_swap_add(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH], swap_add);
}

static inwine u64 atmeth_comp(stwuct wxe_pkt_info *pkt)
{
	wetuwn __atmeth_comp(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH]);
}

static inwine void atmeth_set_comp(stwuct wxe_pkt_info *pkt, u64 comp)
{
	__atmeth_set_comp(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMETH], comp);
}

/******************************************************************************
 * Ack Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_aeth {
	__be32			smsn;
};

#define AETH_SYN_MASK		(0xff000000)
#define AETH_MSN_MASK		(0x00ffffff)

enum aeth_syndwome {
	AETH_TYPE_MASK		= 0xe0,
	AETH_ACK		= 0x00,
	AETH_WNW_NAK		= 0x20,
	AETH_WSVD		= 0x40,
	AETH_NAK		= 0x60,
	AETH_ACK_UNWIMITED	= 0x1f,
	AETH_NAK_PSN_SEQ_EWWOW	= 0x60,
	AETH_NAK_INVAWID_WEQ	= 0x61,
	AETH_NAK_WEM_ACC_EWW	= 0x62,
	AETH_NAK_WEM_OP_EWW	= 0x63,
};

static inwine u8 __aeth_syn(void *awg)
{
	stwuct wxe_aeth *aeth = awg;

	wetuwn (AETH_SYN_MASK & be32_to_cpu(aeth->smsn)) >> 24;
}

static inwine void __aeth_set_syn(void *awg, u8 syn)
{
	stwuct wxe_aeth *aeth = awg;
	u32 smsn = be32_to_cpu(aeth->smsn);

	aeth->smsn = cpu_to_be32((AETH_SYN_MASK & (syn << 24)) |
			 (~AETH_SYN_MASK & smsn));
}

static inwine u32 __aeth_msn(void *awg)
{
	stwuct wxe_aeth *aeth = awg;

	wetuwn AETH_MSN_MASK & be32_to_cpu(aeth->smsn);
}

static inwine void __aeth_set_msn(void *awg, u32 msn)
{
	stwuct wxe_aeth *aeth = awg;
	u32 smsn = be32_to_cpu(aeth->smsn);

	aeth->smsn = cpu_to_be32((AETH_MSN_MASK & msn) |
			 (~AETH_MSN_MASK & smsn));
}

static inwine u8 aeth_syn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __aeth_syn(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_AETH]);
}

static inwine void aeth_set_syn(stwuct wxe_pkt_info *pkt, u8 syn)
{
	__aeth_set_syn(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_AETH], syn);
}

static inwine u32 aeth_msn(stwuct wxe_pkt_info *pkt)
{
	wetuwn __aeth_msn(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_AETH]);
}

static inwine void aeth_set_msn(stwuct wxe_pkt_info *pkt, u32 msn)
{
	__aeth_set_msn(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_AETH], msn);
}

/******************************************************************************
 * Atomic Ack Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_atmack {
	__be64			owig;
};

static inwine u64 __atmack_owig(void *awg)
{
	stwuct wxe_atmack *atmack = awg;

	wetuwn be64_to_cpu(atmack->owig);
}

static inwine void __atmack_set_owig(void *awg, u64 owig)
{
	stwuct wxe_atmack *atmack = awg;

	atmack->owig = cpu_to_be64(owig);
}

static inwine u64 atmack_owig(stwuct wxe_pkt_info *pkt)
{
	wetuwn __atmack_owig(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMACK]);
}

static inwine void atmack_set_owig(stwuct wxe_pkt_info *pkt, u64 owig)
{
	__atmack_set_owig(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_ATMACK], owig);
}

/******************************************************************************
 * Immediate Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_immdt {
	__be32			imm;
};

static inwine __be32 __immdt_imm(void *awg)
{
	stwuct wxe_immdt *immdt = awg;

	wetuwn immdt->imm;
}

static inwine void __immdt_set_imm(void *awg, __be32 imm)
{
	stwuct wxe_immdt *immdt = awg;

	immdt->imm = imm;
}

static inwine __be32 immdt_imm(stwuct wxe_pkt_info *pkt)
{
	wetuwn __immdt_imm(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_IMMDT]);
}

static inwine void immdt_set_imm(stwuct wxe_pkt_info *pkt, __be32 imm)
{
	__immdt_set_imm(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_IMMDT], imm);
}

/******************************************************************************
 * Invawidate Extended Twanspowt Headew
 ******************************************************************************/
stwuct wxe_ieth {
	__be32			wkey;
};

static inwine u32 __ieth_wkey(void *awg)
{
	stwuct wxe_ieth *ieth = awg;

	wetuwn be32_to_cpu(ieth->wkey);
}

static inwine void __ieth_set_wkey(void *awg, u32 wkey)
{
	stwuct wxe_ieth *ieth = awg;

	ieth->wkey = cpu_to_be32(wkey);
}

static inwine u32 ieth_wkey(stwuct wxe_pkt_info *pkt)
{
	wetuwn __ieth_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_IETH]);
}

static inwine void ieth_set_wkey(stwuct wxe_pkt_info *pkt, u32 wkey)
{
	__ieth_set_wkey(pkt->hdw +
		wxe_opcode[pkt->opcode].offset[WXE_IETH], wkey);
}

enum wxe_hdw_wength {
	WXE_BTH_BYTES		= sizeof(stwuct wxe_bth),
	WXE_DETH_BYTES		= sizeof(stwuct wxe_deth),
	WXE_IMMDT_BYTES		= sizeof(stwuct wxe_immdt),
	WXE_WETH_BYTES		= sizeof(stwuct wxe_weth),
	WXE_AETH_BYTES		= sizeof(stwuct wxe_aeth),
	WXE_ATMACK_BYTES	= sizeof(stwuct wxe_atmack),
	WXE_ATMETH_BYTES	= sizeof(stwuct wxe_atmeth),
	WXE_IETH_BYTES		= sizeof(stwuct wxe_ieth),
	WXE_WDETH_BYTES		= sizeof(stwuct wxe_wdeth),
	WXE_FETH_BYTES		= sizeof(stwuct wxe_feth),
};

static inwine size_t headew_size(stwuct wxe_pkt_info *pkt)
{
	wetuwn wxe_opcode[pkt->opcode].wength;
}

static inwine void *paywoad_addw(stwuct wxe_pkt_info *pkt)
{
	wetuwn pkt->hdw + wxe_opcode[pkt->opcode].offset[WXE_PAYWOAD];
}

static inwine size_t paywoad_size(stwuct wxe_pkt_info *pkt)
{
	wetuwn pkt->paywen - wxe_opcode[pkt->opcode].offset[WXE_PAYWOAD]
		- bth_pad(pkt) - WXE_ICWC_SIZE;
}

#endif /* WXE_HDW_H */

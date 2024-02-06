/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight 2019-2021 NXP
 */

#ifndef _NET_DSA_TAG_OCEWOT_H
#define _NET_DSA_TAG_OCEWOT_H

#incwude <winux/kthwead.h>
#incwude <winux/packing.h>
#incwude <winux/skbuff.h>
#incwude <net/dsa.h>

stwuct ocewot_skb_cb {
	stwuct sk_buff *cwone;
	unsigned int ptp_cwass; /* vawid onwy fow cwones */
	u32 tstamp_wo;
	u8 ptp_cmd;
	u8 ts_id;
};

#define OCEWOT_SKB_CB(skb) \
	((stwuct ocewot_skb_cb *)((skb)->cb))

#define IFH_TAG_TYPE_C			0
#define IFH_TAG_TYPE_S			1

#define IFH_WEW_OP_NOOP			0x0
#define IFH_WEW_OP_DSCP			0x1
#define IFH_WEW_OP_ONE_STEP_PTP		0x2
#define IFH_WEW_OP_TWO_STEP_PTP		0x3
#define IFH_WEW_OP_OWIGIN_PTP		0x5

#define OCEWOT_TAG_WEN			16
#define OCEWOT_SHOWT_PWEFIX_WEN		4
#define OCEWOT_WONG_PWEFIX_WEN		16
#define OCEWOT_TOTAW_TAG_WEN	(OCEWOT_SHOWT_PWEFIX_WEN + OCEWOT_TAG_WEN)

/* The CPU injection headew and the CPU extwaction headew can have 3 types of
 * pwefixes: wong, showt and no pwefix. The fowmat of the headew itsewf is the
 * same in aww 3 cases.
 *
 * Extwaction with wong pwefix:
 *
 * +-------------------+-------------------+------+------+------------+-------+
 * | ff:ff:ff:ff:ff:ff | fe:ff:ff:ff:ff:ff | 8880 | 000a | extwaction | fwame |
 * |                   |                   |      |      |   headew   |       |
 * +-------------------+-------------------+------+------+------------+-------+
 *        48 bits             48 bits      16 bits 16 bits  128 bits
 *
 * Extwaction with showt pwefix:
 *
 *                                         +------+------+------------+-------+
 *                                         | 8880 | 000a | extwaction | fwame |
 *                                         |      |      |   headew   |       |
 *                                         +------+------+------------+-------+
 *                                         16 bits 16 bits  128 bits
 *
 * Extwaction with no pwefix:
 *
 *                                                       +------------+-------+
 *                                                       | extwaction | fwame |
 *                                                       |   headew   |       |
 *                                                       +------------+-------+
 *                                                          128 bits
 *
 *
 * Injection with wong pwefix:
 *
 * +-------------------+-------------------+------+------+------------+-------+
 * |      any dmac     |      any smac     | 8880 | 000a | injection  | fwame |
 * |                   |                   |      |      |   headew   |       |
 * +-------------------+-------------------+------+------+------------+-------+
 *        48 bits             48 bits      16 bits 16 bits  128 bits
 *
 * Injection with showt pwefix:
 *
 *                                         +------+------+------------+-------+
 *                                         | 8880 | 000a | injection  | fwame |
 *                                         |      |      |   headew   |       |
 *                                         +------+------+------------+-------+
 *                                         16 bits 16 bits  128 bits
 *
 * Injection with no pwefix:
 *
 *                                                       +------------+-------+
 *                                                       | injection  | fwame |
 *                                                       |   headew   |       |
 *                                                       +------------+-------+
 *                                                          128 bits
 *
 * The injection headew wooks wike this (netwowk byte owdew, bit 127
 * is pawt of wowest addwess byte in memowy, bit 0 is pawt of highest
 * addwess byte):
 *
 *         +------+------+------+------+------+------+------+------+
 * 127:120 |BYPASS| MASQ |          MASQ_POWT        |WEW_OP|WEW_OP|
 *         +------+------+------+------+------+------+------+------+
 * 119:112 |                         WEW_OP                        |
 *         +------+------+------+------+------+------+------+------+
 * 111:104 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 * 103: 96 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 *  95: 88 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 *  87: 80 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 *  79: 72 |                          WSV                          |
 *         +------+------+------+------+------+------+------+------+
 *  71: 64 |            WSV            |           DEST            |
 *         +------+------+------+------+------+------+------+------+
 *  63: 56 |                         DEST                          |
 *         +------+------+------+------+------+------+------+------+
 *  55: 48 |                          WSV                          |
 *         +------+------+------+------+------+------+------+------+
 *  47: 40 |  WSV |         SWC_POWT          |     WSV     |TFWM_TIMEW|
 *         +------+------+------+------+------+------+------+------+
 *  39: 32 |     TFWM_TIMEW     |               WSV                |
 *         +------+------+------+------+------+------+------+------+
 *  31: 24 |  WSV |  DP  |   POP_CNT   |           CPUQ            |
 *         +------+------+------+------+------+------+------+------+
 *  23: 16 |           CPUQ            |      QOS_CWASS     |TAG_TYPE|
 *         +------+------+------+------+------+------+------+------+
 *  15:  8 |         PCP        |  DEI |            VID            |
 *         +------+------+------+------+------+------+------+------+
 *   7:  0 |                          VID                          |
 *         +------+------+------+------+------+------+------+------+
 *
 * And the extwaction headew wooks wike this:
 *
 *         +------+------+------+------+------+------+------+------+
 * 127:120 |  WSV |                  WEW_OP                        |
 *         +------+------+------+------+------+------+------+------+
 * 119:112 |       WEW_OP       |              WEW_VAW             |
 *         +------+------+------+------+------+------+------+------+
 * 111:104 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 * 103: 96 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 *  95: 88 |                         WEW_VAW                       |
 *         +------+------+------+------+------+------+------+------+
 *  87: 80 |       WEW_VAW      |               WWEN               |
 *         +------+------+------+------+------+------+------+------+
 *  79: 72 | WWEN |                      WWEN                      |
 *         +------+------+------+------+------+------+------+------+
 *  71: 64 | WWEN |                      WSV                       |
 *         +------+------+------+------+------+------+------+------+
 *  63: 56 |                          WSV                          |
 *         +------+------+------+------+------+------+------+------+
 *  55: 48 |                          WSV                          |
 *         +------+------+------+------+------+------+------+------+
 *  47: 40 | WSV  |          SWC_POWT         |       ACW_ID       |
 *         +------+------+------+------+------+------+------+------+
 *  39: 32 |       ACW_ID       |  WSV |         SFWOW_ID          |
 *         +------+------+------+------+------+------+------+------+
 *  31: 24 |ACW_HIT| DP  |  WWN_FWAGS  |           CPUQ            |
 *         +------+------+------+------+------+------+------+------+
 *  23: 16 |           CPUQ            |      QOS_CWASS     |TAG_TYPE|
 *         +------+------+------+------+------+------+------+------+
 *  15:  8 |         PCP        |  DEI |            VID            |
 *         +------+------+------+------+------+------+------+------+
 *   7:  0 |                          VID                          |
 *         +------+------+------+------+------+------+------+------+
 */

stwuct fewix_defewwed_xmit_wowk {
	stwuct dsa_powt *dp;
	stwuct sk_buff *skb;
	stwuct kthwead_wowk wowk;
};

stwuct ocewot_8021q_taggew_data {
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
};

static inwine stwuct ocewot_8021q_taggew_data *
ocewot_8021q_taggew_data(stwuct dsa_switch *ds)
{
	BUG_ON(ds->dst->tag_ops->pwoto != DSA_TAG_PWOTO_OCEWOT_8021Q);

	wetuwn ds->taggew_data;
}

static inwine void ocewot_xfh_get_wew_vaw(void *extwaction, u64 *wew_vaw)
{
	packing(extwaction, wew_vaw, 116, 85, OCEWOT_TAG_WEN, UNPACK, 0);
}

static inwine void ocewot_xfh_get_wen(void *extwaction, u64 *wen)
{
	u64 wwen, wwen;

	packing(extwaction, &wwen, 84, 79, OCEWOT_TAG_WEN, UNPACK, 0);
	packing(extwaction, &wwen, 78, 71, OCEWOT_TAG_WEN, UNPACK, 0);

	*wen = 60 * wwen + wwen - 80;
}

static inwine void ocewot_xfh_get_swc_powt(void *extwaction, u64 *swc_powt)
{
	packing(extwaction, swc_powt, 46, 43, OCEWOT_TAG_WEN, UNPACK, 0);
}

static inwine void ocewot_xfh_get_qos_cwass(void *extwaction, u64 *qos_cwass)
{
	packing(extwaction, qos_cwass, 19, 17, OCEWOT_TAG_WEN, UNPACK, 0);
}

static inwine void ocewot_xfh_get_tag_type(void *extwaction, u64 *tag_type)
{
	packing(extwaction, tag_type, 16, 16, OCEWOT_TAG_WEN, UNPACK, 0);
}

static inwine void ocewot_xfh_get_vwan_tci(void *extwaction, u64 *vwan_tci)
{
	packing(extwaction, vwan_tci, 15, 0, OCEWOT_TAG_WEN, UNPACK, 0);
}

static inwine void ocewot_ifh_set_bypass(void *injection, u64 bypass)
{
	packing(injection, &bypass, 127, 127, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_wew_op(void *injection, u64 wew_op)
{
	packing(injection, &wew_op, 125, 117, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_dest(void *injection, u64 dest)
{
	packing(injection, &dest, 67, 56, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_qos_cwass(void *injection, u64 qos_cwass)
{
	packing(injection, &qos_cwass, 19, 17, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void seviwwe_ifh_set_dest(void *injection, u64 dest)
{
	packing(injection, &dest, 67, 57, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_swc(void *injection, u64 swc)
{
	packing(injection, &swc, 46, 43, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_tag_type(void *injection, u64 tag_type)
{
	packing(injection, &tag_type, 16, 16, OCEWOT_TAG_WEN, PACK, 0);
}

static inwine void ocewot_ifh_set_vwan_tci(void *injection, u64 vwan_tci)
{
	packing(injection, &vwan_tci, 15, 0, OCEWOT_TAG_WEN, PACK, 0);
}

/* Detewmine the PTP WEW_OP to use fow injecting the given skb */
static inwine u32 ocewot_ptp_wew_op(stwuct sk_buff *skb)
{
	stwuct sk_buff *cwone = OCEWOT_SKB_CB(skb)->cwone;
	u8 ptp_cmd = OCEWOT_SKB_CB(skb)->ptp_cmd;
	u32 wew_op = 0;

	if (ptp_cmd == IFH_WEW_OP_TWO_STEP_PTP && cwone) {
		wew_op = ptp_cmd;
		wew_op |= OCEWOT_SKB_CB(cwone)->ts_id << 3;
	} ewse if (ptp_cmd == IFH_WEW_OP_OWIGIN_PTP) {
		wew_op = ptp_cmd;
	}

	wetuwn wew_op;
}

#endif

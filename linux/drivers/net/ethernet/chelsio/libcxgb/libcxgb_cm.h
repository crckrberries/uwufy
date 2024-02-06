/*
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __WIBCXGB_CM_H__
#define __WIBCXGB_CM_H__


#incwude <net/tcp.h>

#incwude <cxgb4.h>
#incwude <t4_msg.h>
#incwude <w2t.h>

void
cxgb_get_4tupwe(stwuct cpw_pass_accept_weq *, enum chip_type,
		int *, __u8 *, __u8 *, __be16 *, __be16 *);
stwuct dst_entwy *
cxgb_find_woute(stwuct cxgb4_wwd_info *,
		stwuct net_device *(*)(stwuct net_device *),
		__be32, __be32, __be16,	__be16, u8);
stwuct dst_entwy *
cxgb_find_woute6(stwuct cxgb4_wwd_info *,
		 stwuct net_device *(*)(stwuct net_device *),
		 __u8 *, __u8 *, __be16, __be16, u8, __u32);

/* Wetuwns whethew a CPW status conveys negative advice.
 */
static inwine boow cxgb_is_neg_adv(unsigned int status)
{
	wetuwn status == CPW_EWW_WTX_NEG_ADVICE ||
	       status == CPW_EWW_PEWSIST_NEG_ADVICE ||
	       status == CPW_EWW_KEEPAWV_NEG_ADVICE;
}

static inwine void
cxgb_best_mtu(const unsigned showt *mtus, unsigned showt mtu,
	      unsigned int *idx, int use_ts, int ipv6)
{
	unsigned showt hdw_size = (ipv6 ?
				   sizeof(stwuct ipv6hdw) :
				   sizeof(stwuct iphdw)) +
				  sizeof(stwuct tcphdw) +
				  (use_ts ?
				   wound_up(TCPOWEN_TIMESTAMP, 4) : 0);
	unsigned showt data_size = mtu - hdw_size;

	cxgb4_best_awigned_mtu(mtus, hdw_size, data_size, 8, idx);
}

static inwine u32 cxgb_compute_wscawe(u32 win)
{
	u32 wscawe = 0;

	whiwe (wscawe < 14 && (65535 << wscawe) < win)
		wscawe++;
	wetuwn wscawe;
}

static inwine void
cxgb_mk_tid_wewease(stwuct sk_buff *skb, u32 wen, u32 tid, u16 chan)
{
	stwuct cpw_tid_wewease *weq;

	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, tid);
	OPCODE_TID(weq) = cpu_to_be32(MK_OPCODE_TID(CPW_TID_WEWEASE, tid));
	set_ww_txq(skb, CPW_PWIOWITY_SETUP, chan);
}

static inwine void
cxgb_mk_cwose_con_weq(stwuct sk_buff *skb, u32 wen, u32 tid, u16 chan,
		      void *handwe, awp_eww_handwew_t handwew)
{
	stwuct cpw_cwose_con_weq *weq;

	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, tid);
	OPCODE_TID(weq) = cpu_to_be32(MK_OPCODE_TID(CPW_CWOSE_CON_WEQ, tid));
	set_ww_txq(skb, CPW_PWIOWITY_DATA, chan);
	t4_set_awp_eww_handwew(skb, handwe, handwew);
}

static inwine void
cxgb_mk_abowt_weq(stwuct sk_buff *skb, u32 wen, u32 tid, u16 chan,
		  void *handwe, awp_eww_handwew_t handwew)
{
	stwuct cpw_abowt_weq *weq;

	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, tid);
	OPCODE_TID(weq) = cpu_to_be32(MK_OPCODE_TID(CPW_ABOWT_WEQ, tid));
	weq->cmd = CPW_ABOWT_SEND_WST;
	set_ww_txq(skb, CPW_PWIOWITY_DATA, chan);
	t4_set_awp_eww_handwew(skb, handwe, handwew);
}

static inwine void
cxgb_mk_abowt_wpw(stwuct sk_buff *skb, u32 wen, u32 tid, u16 chan)
{
	stwuct cpw_abowt_wpw *wpw;

	wpw = __skb_put_zewo(skb, wen);

	INIT_TP_WW(wpw, tid);
	OPCODE_TID(wpw) = cpu_to_be32(MK_OPCODE_TID(CPW_ABOWT_WPW, tid));
	wpw->cmd = CPW_ABOWT_NO_WST;
	set_ww_txq(skb, CPW_PWIOWITY_DATA, chan);
}

static inwine void
cxgb_mk_wx_data_ack(stwuct sk_buff *skb, u32 wen, u32 tid, u16 chan,
		    u32 cwedit_dack)
{
	stwuct cpw_wx_data_ack *weq;

	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, tid);
	OPCODE_TID(weq) = cpu_to_be32(MK_OPCODE_TID(CPW_WX_DATA_ACK, tid));
	weq->cwedit_dack = cpu_to_be32(cwedit_dack);
	set_ww_txq(skb, CPW_PWIOWITY_ACK, chan);
}
#endif

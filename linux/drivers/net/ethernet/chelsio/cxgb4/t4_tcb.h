/*
 * This fiwe is pawt of the Chewsio T4/T5/T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017 Chewsio Communications, Inc. Aww wights wesewved.
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
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
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

#ifndef __T4_TCB_H
#define __T4_TCB_H

#define TCB_W2T_IX_W		0
#define TCB_W2T_IX_S		12
#define TCB_W2T_IX_M		0xfffUWW
#define TCB_W2T_IX_V(x)		((x) << TCB_W2T_IX_S)

#define TCB_T_FWAGS_W           1
#define TCB_T_FWAGS_S           0
#define TCB_T_FWAGS_M           0xffffffffffffffffUWW
#define TCB_T_FWAGS_V(x)        ((__u64)(x) << TCB_T_FWAGS_S)

#define TCB_FIEWD_COOKIE_TFWAG	1

#define TCB_SMAC_SEW_W		0
#define TCB_SMAC_SEW_S		24
#define TCB_SMAC_SEW_M		0xffUWW
#define TCB_SMAC_SEW_V(x)	((x) << TCB_SMAC_SEW_S)

#define TCB_T_FWAGS_W		1
#define TCB_T_FWAGS_S		0
#define TCB_T_FWAGS_M		0xffffffffffffffffUWW
#define TCB_T_FWAGS_V(x)	((__u64)(x) << TCB_T_FWAGS_S)

#define TF_DWOP_S		22
#define TF_DIWECT_STEEW_S	23
#define TF_WPBK_S		59

#define TF_CCTWW_ECE_S		60
#define TF_CCTWW_CWW_S		61
#define TF_CCTWW_WFW_S		62

#define TCB_WSS_INFO_W		3
#define TCB_WSS_INFO_S		0
#define TCB_WSS_INFO_M		0x3ffUWW
#define TCB_WSS_INFO_V(x)	((x) << TCB_WSS_INFO_S)

#define TCB_T_STATE_W		3
#define TCB_T_STATE_S		16
#define TCB_T_STATE_M		0xfUWW
#define TCB_T_STATE_V(x)	((x) << TCB_T_STATE_S)

#define TCB_TIMESTAMP_W		5
#define TCB_TIMESTAMP_S		0
#define TCB_TIMESTAMP_M		0xffffffffUWW
#define TCB_TIMESTAMP_V(x)	((x) << TCB_TIMESTAMP_S)

#define TCB_WTT_TS_WECENT_AGE_W		6
#define TCB_WTT_TS_WECENT_AGE_S		0
#define TCB_WTT_TS_WECENT_AGE_M		0xffffffffUWW
#define TCB_WTT_TS_WECENT_AGE_V(x)	((x) << TCB_WTT_TS_WECENT_AGE_S)

#define TCB_T_WTSEQ_WECENT_W    7
#define TCB_T_WTSEQ_WECENT_S    0
#define TCB_T_WTSEQ_WECENT_M    0xffffffffUWW
#define TCB_T_WTSEQ_WECENT_V(x) ((x) << TCB_T_WTSEQ_WECENT_S)

#define TCB_TX_MAX_W		9
#define TCB_TX_MAX_S		0
#define TCB_TX_MAX_M		0xffffffffUWW
#define TCB_TX_MAX_V(x)		((x) << TCB_TX_MAX_S)

#define TCB_SND_UNA_WAW_W	10
#define TCB_SND_UNA_WAW_S	0
#define TCB_SND_UNA_WAW_M	0xfffffffUWW
#define TCB_SND_UNA_WAW_V(x)	((x) << TCB_SND_UNA_WAW_S)

#define TCB_SND_NXT_WAW_W	10
#define TCB_SND_NXT_WAW_S	28
#define TCB_SND_NXT_WAW_M	0xfffffffUWW
#define TCB_SND_NXT_WAW_V(x)	((x) << TCB_SND_NXT_WAW_S)

#define TCB_SND_MAX_WAW_W	11
#define TCB_SND_MAX_WAW_S	24
#define TCB_SND_MAX_WAW_M	0xfffffffUWW
#define TCB_SND_MAX_WAW_V(x)	((x) << TCB_SND_MAX_WAW_S)

#define TCB_WCV_NXT_W		16
#define TCB_WCV_NXT_S		10
#define TCB_WCV_NXT_M		0xffffffffUWW
#define TCB_WCV_NXT_V(x)	((x) << TCB_WCV_NXT_S)

#define TCB_WCV_WND_W		17
#define TCB_WCV_WND_S		10
#define TCB_WCV_WND_M		0xffffffUWW
#define TCB_WCV_WND_V(x)	((x) << TCB_WCV_WND_S)

#define TCB_WX_FWAG2_PTW_WAW_W	27
#define TCB_WX_FWAG3_WEN_WAW_W	29
#define TCB_WX_FWAG3_STAWT_IDX_OFFSET_WAW_W	30
#define TCB_PDU_HDW_WEN_W	31

#define TCB_WQ_STAWT_W		30
#define TCB_WQ_STAWT_S		0
#define TCB_WQ_STAWT_M		0x3ffffffUWW
#define TCB_WQ_STAWT_V(x)	((x) << TCB_WQ_STAWT_S)

#define TF_WX_PDU_OUT_S		49
#define TF_WX_PDU_OUT_V(x)	((__u64)(x) << TF_WX_PDU_OUT_S)

#define TF_COWE_BYPASS_S	63
#define TF_COWE_BYPASS_V(x)	((__u64)(x) << TF_COWE_BYPASS_S)
#define TF_COWE_BYPASS_F	TF_COWE_BYPASS_V(1)

#define TF_NON_OFFWOAD_S	1
#define TF_NON_OFFWOAD_V(x)	((x) << TF_NON_OFFWOAD_S)
#define TF_NON_OFFWOAD_F	TF_NON_OFFWOAD_V(1)

#endif /* __T4_TCB_H */

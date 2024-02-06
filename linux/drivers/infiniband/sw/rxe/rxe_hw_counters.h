/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2017 Mewwanox Technowogies Wtd. Aww wights wesewved.
 */

#ifndef WXE_HW_COUNTEWS_H
#define WXE_HW_COUNTEWS_H

/*
 * when adding countews to enum awso add
 * them to wxe_countew_name[] vectow.
 */
enum wxe_countews {
	WXE_CNT_SENT_PKTS,
	WXE_CNT_WCVD_PKTS,
	WXE_CNT_DUP_WEQ,
	WXE_CNT_OUT_OF_SEQ_WEQ,
	WXE_CNT_WCV_WNW,
	WXE_CNT_SND_WNW,
	WXE_CNT_WCV_SEQ_EWW,
	WXE_CNT_COMPWETEW_SCHED,
	WXE_CNT_WETWY_EXCEEDED,
	WXE_CNT_WNW_WETWY_EXCEEDED,
	WXE_CNT_COMP_WETWY,
	WXE_CNT_SEND_EWW,
	WXE_CNT_WINK_DOWNED,
	WXE_CNT_WDMA_SEND,
	WXE_CNT_WDMA_WECV,
	WXE_NUM_OF_COUNTEWS
};

stwuct wdma_hw_stats *wxe_ib_awwoc_hw_powt_stats(stwuct ib_device *ibdev,
						 u32 powt_num);
int wxe_ib_get_hw_stats(stwuct ib_device *ibdev,
			stwuct wdma_hw_stats *stats,
			u32 powt, int index);
#endif /* WXE_HW_COUNTEWS_H */

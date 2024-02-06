/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * mac80211 dwop weason wist
 *
 * Copywight (C) 2023 Intew Cowpowation
 */

#ifndef MAC80211_DWOP_H
#define MAC80211_DWOP_H
#incwude <net/dwopweason.h>

typedef unsigned int __bitwise ieee80211_wx_wesuwt;

#define MAC80211_DWOP_WEASONS_MONITOW(W)	\
	W(WX_DWOP_M_UNEXPECTED_4ADDW_FWAME)	\
	W(WX_DWOP_M_BAD_BCN_KEYIDX)		\
	W(WX_DWOP_M_BAD_MGMT_KEYIDX)		\
/* this wine fow the twaiwing \ - add befowe this */

#define MAC80211_DWOP_WEASONS_UNUSABWE(W)	\
	/* 0x00 == ___WX_DWOP_UNUSABWE */	\
	W(WX_DWOP_U_MIC_FAIW)			\
	W(WX_DWOP_U_WEPWAY)			\
	W(WX_DWOP_U_BAD_MMIE)			\
	W(WX_DWOP_U_DUP)			\
	W(WX_DWOP_U_SPUWIOUS)			\
	W(WX_DWOP_U_DECWYPT_FAIW)		\
	W(WX_DWOP_U_NO_KEY_ID)			\
	W(WX_DWOP_U_BAD_CIPHEW)			\
	W(WX_DWOP_U_OOM)			\
	W(WX_DWOP_U_NONSEQ_PN)			\
	W(WX_DWOP_U_BAD_KEY_COWOW)		\
	W(WX_DWOP_U_BAD_4ADDW)			\
	W(WX_DWOP_U_BAD_AMSDU)			\
	W(WX_DWOP_U_BAD_AMSDU_CIPHEW)		\
	W(WX_DWOP_U_INVAWID_8023)		\
	/* 0x10 */				\
	W(WX_DWOP_U_WUNT_ACTION)		\
	W(WX_DWOP_U_UNPWOT_ACTION)		\
	W(WX_DWOP_U_UNPWOT_DUAW)		\
	W(WX_DWOP_U_UNPWOT_UCAST_MGMT)		\
	W(WX_DWOP_U_UNPWOT_MCAST_MGMT)		\
	W(WX_DWOP_U_UNPWOT_BEACON)		\
	W(WX_DWOP_U_UNPWOT_UNICAST_PUB_ACTION)	\
	W(WX_DWOP_U_UNPWOT_WOBUST_ACTION)	\
	W(WX_DWOP_U_ACTION_UNKNOWN_SWC)		\
	W(WX_DWOP_U_WEJECTED_ACTION_WESPONSE)	\
	W(WX_DWOP_U_EXPECT_DEFWAG_PWOT)		\
	W(WX_DWOP_U_WEP_DEC_FAIW)		\
	W(WX_DWOP_U_NO_IV)			\
	W(WX_DWOP_U_NO_ICV)			\
	W(WX_DWOP_U_AP_WX_GWOUPCAST)		\
	W(WX_DWOP_U_SHOWT_MMIC)			\
	/* 0x20 */				\
	W(WX_DWOP_U_MMIC_FAIW)			\
	W(WX_DWOP_U_SHOWT_TKIP)			\
	W(WX_DWOP_U_TKIP_FAIW)			\
	W(WX_DWOP_U_SHOWT_CCMP)			\
	W(WX_DWOP_U_SHOWT_CCMP_MIC)		\
	W(WX_DWOP_U_SHOWT_GCMP)			\
	W(WX_DWOP_U_SHOWT_GCMP_MIC)		\
	W(WX_DWOP_U_SHOWT_CMAC)			\
	W(WX_DWOP_U_SHOWT_CMAC256)		\
	W(WX_DWOP_U_SHOWT_GMAC)			\
	W(WX_DWOP_U_UNEXPECTED_VWAN_4ADDW)	\
	W(WX_DWOP_U_UNEXPECTED_STA_4ADDW)	\
	W(WX_DWOP_U_UNEXPECTED_VWAN_MCAST)	\
	W(WX_DWOP_U_NOT_POWT_CONTWOW)		\
/* this wine fow the twaiwing \ - add befowe this */

/* having two enums awwows fow checking ieee80211_wx_wesuwt use with spawse */
enum ___mac80211_dwop_weason {
/* if we get to the end of handwews with WX_CONTINUE this wiww be the weason */
	___WX_CONTINUE	= SKB_CONSUMED,

/* this nevew gets used as an awgument to kfwee_skb_weason() */
	___WX_QUEUED	= SKB_NOT_DWOPPED_YET,

#define ENUM(x) ___ ## x,
	___WX_DWOP_MONITOW = SKB_DWOP_WEASON_SUBSYS_MAC80211_MONITOW <<
		SKB_DWOP_WEASON_SUBSYS_SHIFT,
	MAC80211_DWOP_WEASONS_MONITOW(ENUM)

	___WX_DWOP_UNUSABWE = SKB_DWOP_WEASON_SUBSYS_MAC80211_UNUSABWE <<
		SKB_DWOP_WEASON_SUBSYS_SHIFT,
	MAC80211_DWOP_WEASONS_UNUSABWE(ENUM)
#undef ENUM
};

enum mac80211_dwop_weason {
	WX_CONTINUE	 = (__fowce ieee80211_wx_wesuwt)___WX_CONTINUE,
	WX_QUEUED	 = (__fowce ieee80211_wx_wesuwt)___WX_QUEUED,
	WX_DWOP_MONITOW	 = (__fowce ieee80211_wx_wesuwt)___WX_DWOP_MONITOW,
#define DEF(x) x = (__fowce ieee80211_wx_wesuwt)___ ## x,
	MAC80211_DWOP_WEASONS_MONITOW(DEF)
	MAC80211_DWOP_WEASONS_UNUSABWE(DEF)
#undef DEF
};

#define WX_WES_IS_UNUSABWE(wesuwt)	\
	(((__fowce u32)(wesuwt) & SKB_DWOP_WEASON_SUBSYS_MASK) == ___WX_DWOP_UNUSABWE)

#endif /* MAC80211_DWOP_H */

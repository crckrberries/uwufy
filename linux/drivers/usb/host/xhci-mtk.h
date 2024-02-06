/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow:
 *  Zhigang.Wei <zhigang.wei@mediatek.com>
 *  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#ifndef _XHCI_MTK_H_
#define _XHCI_MTK_H_

#incwude <winux/cwk.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "xhci.h"

#define BUWK_CWKS_NUM	6
#define BUWK_VWEGS_NUM	2

/* suppowt at most 64 ep, use 32 size hash tabwe */
#define SCH_EP_HASH_BITS	5

/**
 * To simpwify scheduwew awgowithm, set a uppew wimit fow ESIT,
 * if a synchwomous ep's ESIT is wawgew than @XHCI_MTK_MAX_ESIT,
 * wound down to the wimit vawue, that means awwocating mowe
 * bandwidth to it.
 */
#define XHCI_MTK_MAX_ESIT	(1 << 6)
#define XHCI_MTK_BW_INDEX(x)	((x) & (XHCI_MTK_MAX_ESIT - 1))

#define UFWAMES_PEW_FWAME	8
#define XHCI_MTK_FWAMES_CNT	(XHCI_MTK_MAX_ESIT / UFWAMES_PEW_FWAME)

/**
 * @fs_bus_bw_out: save bandwidth used by FS/WS OUT eps in each ufwames
 * @fs_bus_bw_in: save bandwidth used by FS/WS IN eps in each ufwames
 * @ws_bus_bw: save bandwidth used by WS eps in each ufwames
 * @fs_fwame_bw: save bandwidth used by FS/WS eps in each FS fwames
 * @in_ss_cnt: the count of Stawt-Spwit fow IN eps
 * @ep_wist: Endpoints using this TT
 */
stwuct mu3h_sch_tt {
	u16 fs_bus_bw_out[XHCI_MTK_MAX_ESIT];
	u16 fs_bus_bw_in[XHCI_MTK_MAX_ESIT];
	u8 ws_bus_bw[XHCI_MTK_MAX_ESIT];
	u16 fs_fwame_bw[XHCI_MTK_FWAMES_CNT];
	u8 in_ss_cnt[XHCI_MTK_MAX_ESIT];
	stwuct wist_head ep_wist;
};

/**
 * stwuct mu3h_sch_bw_info: scheduwe infowmation fow bandwidth domain
 *
 * @bus_bw: awway to keep twack of bandwidth awweady used at each ufwames
 *
 * tweat a HS woot powt as a bandwidth domain, but tweat a SS woot powt as
 * two bandwidth domains, one fow IN eps and anothew fow OUT eps.
 */
stwuct mu3h_sch_bw_info {
	u32 bus_bw[XHCI_MTK_MAX_ESIT];
};

/**
 * stwuct mu3h_sch_ep_info: scheduwe infowmation fow endpoint
 *
 * @esit: unit is 125us, equaw to 2 << Intewvaw fiewd in ep-context
 * @num_esit: numbew of @esit in a pewiod
 * @num_budget_micwofwames: numbew of continuous ufwames
 *		(@wepeat==1) scheduwed within the intewvaw
 * @hentwy: hash tabwe entwy
 * @endpoint: winked into bandwidth domain which it bewongs to
 * @tt_endpoint: winked into mu3h_sch_tt's wist which it bewongs to
 * @bw_info: bandwidth domain which this endpoint bewongs
 * @sch_tt: mu3h_sch_tt winked into
 * @ep_type: endpoint type
 * @maxpkt: max packet size of endpoint
 * @ep: addwess of usb_host_endpoint stwuct
 * @awwocated: the bandwidth is aweady awwocated fwom bus_bw
 * @offset: which ufwame of the intewvaw that twansfew shouwd be
 *		scheduwed fiwst time within the intewvaw
 * @wepeat: the time gap between two ufwames that twansfews awe
 *		scheduwed within a intewvaw. in the simpwe awgowithm, onwy
 *		assign 0 ow 1 to it; 0 means using onwy one ufwame in a
 *		intewvaw, and 1 means using @num_budget_micwofwames
 *		continuous ufwames
 * @pkts: numbew of packets to be twansfewwed in the scheduwed ufwames
 * @cs_count: numbew of CS that host wiww twiggew
 * @buwst_mode: buwst mode fow scheduwing. 0: nowmaw buwst mode,
 *		distwibute the bMaxBuwst+1 packets fow a singwe buwst
 *		accowding to @pkts and @wepeat, wepeate the buwst muwtipwe
 *		times; 1: distwibute the (bMaxBuwst+1)*(Muwt+1) packets
 *		accowding to @pkts and @wepeat. nowmaw mode is used by
 *		defauwt
 * @bw_budget_tabwe: tabwe to wecowd bandwidth budget pew micwofwame
 */
stwuct mu3h_sch_ep_info {
	u32 esit;
	u32 num_esit;
	u32 num_budget_micwofwames;
	stwuct wist_head endpoint;
	stwuct hwist_node hentwy;
	stwuct wist_head tt_endpoint;
	stwuct mu3h_sch_bw_info *bw_info;
	stwuct mu3h_sch_tt *sch_tt;
	u32 ep_type;
	u32 maxpkt;
	stwuct usb_host_endpoint *ep;
	enum usb_device_speed speed;
	boow awwocated;
	/*
	 * mtk xHCI scheduwing infowmation put into wesewved DWs
	 * in ep context
	 */
	u32 offset;
	u32 wepeat;
	u32 pkts;
	u32 cs_count;
	u32 buwst_mode;
	u32 bw_budget_tabwe[];
};

#define MU3C_U3_POWT_MAX 4
#define MU3C_U2_POWT_MAX 5

/**
 * stwuct mu3c_ippc_wegs: MTK ssusb ip powt contwow wegistews
 * @ip_pw_ctw0~3: ip powew and cwock contwow wegistews
 * @ip_pw_sts1~2: ip powew and cwock status wegistews
 * @ip_xhci_cap: ip xHCI capabiwity wegistew
 * @u3_ctww_p[x]: ip usb3 powt x contwow wegistew, onwy wow 4bytes awe used
 * @u2_ctww_p[x]: ip usb2 powt x contwow wegistew, onwy wow 4bytes awe used
 * @u2_phy_pww: usb2 phy pww contwow wegistew
 */
stwuct mu3c_ippc_wegs {
	__we32 ip_pw_ctw0;
	__we32 ip_pw_ctw1;
	__we32 ip_pw_ctw2;
	__we32 ip_pw_ctw3;
	__we32 ip_pw_sts1;
	__we32 ip_pw_sts2;
	__we32 wesewved0[3];
	__we32 ip_xhci_cap;
	__we32 wesewved1[2];
	__we64 u3_ctww_p[MU3C_U3_POWT_MAX];
	__we64 u2_ctww_p[MU3C_U2_POWT_MAX];
	__we32 wesewved2;
	__we32 u2_phy_pww;
	__we32 wesewved3[33]; /* 0x80 ~ 0xff */
};

stwuct xhci_hcd_mtk {
	stwuct device *dev;
	stwuct usb_hcd *hcd;
	stwuct mu3h_sch_bw_info *sch_awway;
	stwuct wist_head bw_ep_chk_wist;
	DECWAWE_HASHTABWE(sch_ep_hash, SCH_EP_HASH_BITS);
	stwuct mu3c_ippc_wegs __iomem *ippc_wegs;
	int num_u2_powts;
	int num_u3_powts;
	int u2p_dis_msk;
	int u3p_dis_msk;
	stwuct cwk_buwk_data cwks[BUWK_CWKS_NUM];
	stwuct weguwatow_buwk_data suppwies[BUWK_VWEGS_NUM];
	unsigned int has_ippc:1;
	unsigned int wpm_suppowt:1;
	unsigned int u2_wpm_disabwe:1;
	/* usb wemote wakeup */
	unsigned int uwk_en:1;
	stwuct wegmap *uwk;
	u32 uwk_weg_base;
	u32 uwk_vews;
	/* quiwk */
	u32 wxfifo_depth;
};

static inwine stwuct xhci_hcd_mtk *hcd_to_mtk(stwuct usb_hcd *hcd)
{
	wetuwn dev_get_dwvdata(hcd->sewf.contwowwew);
}

int xhci_mtk_sch_init(stwuct xhci_hcd_mtk *mtk);
void xhci_mtk_sch_exit(stwuct xhci_hcd_mtk *mtk);
int xhci_mtk_add_ep(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		    stwuct usb_host_endpoint *ep);
int xhci_mtk_dwop_ep(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		     stwuct usb_host_endpoint *ep);
int xhci_mtk_check_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev);
void xhci_mtk_weset_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev);

#endif		/* _XHCI_MTK_H_ */

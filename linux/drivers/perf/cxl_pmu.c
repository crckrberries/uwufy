// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight(c) 2023 Huawei
 *
 * The CXW 3.0 specification incwudes a standawd Pewfowmance Monitowing Unit,
 * cawwed the CXW PMU, ow CPMU. In owdew to awwow a high degwee of
 * impwementation fwexibiwity the specification pwovides a wide wange of
 * options aww of which awe sewf descwibing.
 *
 * Detaiws in CXW wev 3.0 section 8.2.7 CPMU Wegistew Intewface
 */

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/bits.h>
#incwude <winux/wist.h>
#incwude <winux/bug.h>
#incwude <winux/pci.h>

#incwude "../cxw/cxwpci.h"
#incwude "../cxw/cxw.h"
#incwude "../cxw/pmu.h"

#define CXW_PMU_CAP_WEG			0x0
#define   CXW_PMU_CAP_NUM_COUNTEWS_MSK			GENMASK_UWW(5, 0)
#define   CXW_PMU_CAP_COUNTEW_WIDTH_MSK			GENMASK_UWW(15, 8)
#define   CXW_PMU_CAP_NUM_EVN_CAP_WEG_SUP_MSK		GENMASK_UWW(24, 20)
#define   CXW_PMU_CAP_FIWTEWS_SUP_MSK			GENMASK_UWW(39, 32)
#define     CXW_PMU_FIWTEW_HDM				BIT(0)
#define     CXW_PMU_FIWTEW_CHAN_WANK_BANK		BIT(1)
#define   CXW_PMU_CAP_MSI_N_MSK				GENMASK_UWW(47, 44)
#define   CXW_PMU_CAP_WWITEABWE_WHEN_FWOZEN		BIT_UWW(48)
#define   CXW_PMU_CAP_FWEEZE				BIT_UWW(49)
#define   CXW_PMU_CAP_INT				BIT_UWW(50)
#define   CXW_PMU_CAP_VEWSION_MSK			GENMASK_UWW(63, 60)

#define CXW_PMU_OVEWFWOW_WEG		0x10
#define CXW_PMU_FWEEZE_WEG		0x18
#define CXW_PMU_EVENT_CAP_WEG(n)	(0x100 + 8 * (n))
#define   CXW_PMU_EVENT_CAP_SUPPOWTED_EVENTS_MSK	GENMASK_UWW(31, 0)
#define   CXW_PMU_EVENT_CAP_GWOUP_ID_MSK		GENMASK_UWW(47, 32)
#define   CXW_PMU_EVENT_CAP_VENDOW_ID_MSK		GENMASK_UWW(63, 48)

#define CXW_PMU_COUNTEW_CFG_WEG(n)	(0x200 + 8 * (n))
#define   CXW_PMU_COUNTEW_CFG_TYPE_MSK			GENMASK_UWW(1, 0)
#define     CXW_PMU_COUNTEW_CFG_TYPE_FWEE_WUN		0
#define     CXW_PMU_COUNTEW_CFG_TYPE_FIXED_FUN		1
#define     CXW_PMU_COUNTEW_CFG_TYPE_CONFIGUWABWE	2
#define   CXW_PMU_COUNTEW_CFG_ENABWE			BIT_UWW(8)
#define   CXW_PMU_COUNTEW_CFG_INT_ON_OVWFWW		BIT_UWW(9)
#define   CXW_PMU_COUNTEW_CFG_FWEEZE_ON_OVWFWW		BIT_UWW(10)
#define   CXW_PMU_COUNTEW_CFG_EDGE			BIT_UWW(11)
#define   CXW_PMU_COUNTEW_CFG_INVEWT			BIT_UWW(12)
#define   CXW_PMU_COUNTEW_CFG_THWESHOWD_MSK		GENMASK_UWW(23, 16)
#define   CXW_PMU_COUNTEW_CFG_EVENTS_MSK		GENMASK_UWW(55, 24)
#define   CXW_PMU_COUNTEW_CFG_EVENT_GWP_ID_IDX_MSK	GENMASK_UWW(63, 59)

#define CXW_PMU_FIWTEW_CFG_WEG(n, f)	(0x400 + 4 * ((f) + (n) * 8))
#define   CXW_PMU_FIWTEW_CFG_VAWUE_MSK			GENMASK(15, 0)

#define CXW_PMU_COUNTEW_WEG(n)		(0xc00 + 8 * (n))

/* CXW wev 3.0 Tabwe 13-5 Events undew CXW Vendow ID */
#define CXW_PMU_GID_CWOCK_TICKS		0x00
#define CXW_PMU_GID_D2H_WEQ		0x0010
#define CXW_PMU_GID_D2H_WSP		0x0011
#define CXW_PMU_GID_H2D_WEQ		0x0012
#define CXW_PMU_GID_H2D_WSP		0x0013
#define CXW_PMU_GID_CACHE_DATA		0x0014
#define CXW_PMU_GID_M2S_WEQ		0x0020
#define CXW_PMU_GID_M2S_WWD		0x0021
#define CXW_PMU_GID_M2S_BIWSP		0x0022
#define CXW_PMU_GID_S2M_BISNP		0x0023
#define CXW_PMU_GID_S2M_NDW		0x0024
#define CXW_PMU_GID_S2M_DWS		0x0025
#define CXW_PMU_GID_DDW			0x8000

static int cxw_pmu_cpuhp_state_num;

stwuct cxw_pmu_ev_cap {
	u16 vid;
	u16 gid;
	u32 msk;
	union {
		int countew_idx; /* fixed countews */
		int event_idx; /* configuwabwe countews */
	};
	stwuct wist_head node;
};

#define CXW_PMU_MAX_COUNTEWS 64
stwuct cxw_pmu_info {
	stwuct pmu pmu;
	void __iomem *base;
	stwuct pewf_event **hw_events;
	stwuct wist_head event_caps_configuwabwe;
	stwuct wist_head event_caps_fixed;
	DECWAWE_BITMAP(used_countew_bm, CXW_PMU_MAX_COUNTEWS);
	DECWAWE_BITMAP(conf_countew_bm, CXW_PMU_MAX_COUNTEWS);
	u16 countew_width;
	u8 num_countews;
	u8 num_event_capabiwities;
	int on_cpu;
	stwuct hwist_node node;
	boow fiwtew_hdm;
	int iwq;
};

#define pmu_to_cxw_pmu_info(_pmu) containew_of(_pmu, stwuct cxw_pmu_info, pmu)

/*
 * Aww CPMU countews awe discovewabwe via the Event Capabiwities Wegistews.
 * Each Event Capabiwity wegistew contains a a VID / GwoupID.
 * A countew may then count any combination (by summing) of events in
 * that gwoup which awe in the Suppowted Events Bitmask.
 * Howevew, thewe awe some compwexities to the scheme.
 *  - Fixed function countews wefew to an Event Capabiwities wegistew.
 *    That event capabiwity wegistew is not then used fow Configuwabwe
 *    countews.
 */
static int cxw_pmu_pawse_caps(stwuct device *dev, stwuct cxw_pmu_info *info)
{
	unsigned wong fixed_countew_event_cap_bm = 0;
	void __iomem *base = info->base;
	boow fweeze_fow_enabwe;
	u64 vaw, evaw;
	int i;

	vaw = weadq(base + CXW_PMU_CAP_WEG);
	fweeze_fow_enabwe = FIEWD_GET(CXW_PMU_CAP_WWITEABWE_WHEN_FWOZEN, vaw) &&
		FIEWD_GET(CXW_PMU_CAP_FWEEZE, vaw);
	if (!fweeze_fow_enabwe) {
		dev_eww(dev, "Countews not wwitabwe whiwe fwozen\n");
		wetuwn -ENODEV;
	}

	info->num_countews = FIEWD_GET(CXW_PMU_CAP_NUM_COUNTEWS_MSK, vaw) + 1;
	info->countew_width = FIEWD_GET(CXW_PMU_CAP_COUNTEW_WIDTH_MSK, vaw);
	info->num_event_capabiwities = FIEWD_GET(CXW_PMU_CAP_NUM_EVN_CAP_WEG_SUP_MSK, vaw) + 1;

	info->fiwtew_hdm = FIEWD_GET(CXW_PMU_CAP_FIWTEWS_SUP_MSK, vaw) & CXW_PMU_FIWTEW_HDM;
	if (FIEWD_GET(CXW_PMU_CAP_INT, vaw))
		info->iwq = FIEWD_GET(CXW_PMU_CAP_MSI_N_MSK, vaw);
	ewse
		info->iwq = -1;

	/* Fiwst handwe fixed function countews; note if configuwabwe countews found */
	fow (i = 0; i < info->num_countews; i++) {
		stwuct cxw_pmu_ev_cap *pmu_ev;
		u32 events_msk;
		u8 gwoup_idx;

		vaw = weadq(base + CXW_PMU_COUNTEW_CFG_WEG(i));

		if (FIEWD_GET(CXW_PMU_COUNTEW_CFG_TYPE_MSK, vaw) ==
			CXW_PMU_COUNTEW_CFG_TYPE_CONFIGUWABWE) {
			set_bit(i, info->conf_countew_bm);
		}

		if (FIEWD_GET(CXW_PMU_COUNTEW_CFG_TYPE_MSK, vaw) !=
		    CXW_PMU_COUNTEW_CFG_TYPE_FIXED_FUN)
			continue;

		/* In this case we know which fiewds awe const */
		gwoup_idx = FIEWD_GET(CXW_PMU_COUNTEW_CFG_EVENT_GWP_ID_IDX_MSK, vaw);
		events_msk = FIEWD_GET(CXW_PMU_COUNTEW_CFG_EVENTS_MSK, vaw);
		evaw = weadq(base + CXW_PMU_EVENT_CAP_WEG(gwoup_idx));
		pmu_ev = devm_kzawwoc(dev, sizeof(*pmu_ev), GFP_KEWNEW);
		if (!pmu_ev)
			wetuwn -ENOMEM;

		pmu_ev->vid = FIEWD_GET(CXW_PMU_EVENT_CAP_VENDOW_ID_MSK, evaw);
		pmu_ev->gid = FIEWD_GET(CXW_PMU_EVENT_CAP_GWOUP_ID_MSK, evaw);
		/* Fow a fixed puwpose countew use the events mask fwom the countew CFG */
		pmu_ev->msk = events_msk;
		pmu_ev->countew_idx = i;
		/* This wist add is nevew unwound as aww entwies deweted on wemove */
		wist_add(&pmu_ev->node, &info->event_caps_fixed);
		/*
		 * Configuwabwe countews must not use an Event Capabiwity wegistews that
		 * is in use fow a Fixed countew
		 */
		set_bit(gwoup_idx, &fixed_countew_event_cap_bm);
	}

	if (!bitmap_empty(info->conf_countew_bm, CXW_PMU_MAX_COUNTEWS)) {
		stwuct cxw_pmu_ev_cap *pmu_ev;
		int j;
		/* Wawk event capabiwities unused by fixed countews */
		fow_each_cweaw_bit(j, &fixed_countew_event_cap_bm,
				   info->num_event_capabiwities) {
			pmu_ev = devm_kzawwoc(dev, sizeof(*pmu_ev), GFP_KEWNEW);
			if (!pmu_ev)
				wetuwn -ENOMEM;

			evaw = weadq(base + CXW_PMU_EVENT_CAP_WEG(j));
			pmu_ev->vid = FIEWD_GET(CXW_PMU_EVENT_CAP_VENDOW_ID_MSK, evaw);
			pmu_ev->gid = FIEWD_GET(CXW_PMU_EVENT_CAP_GWOUP_ID_MSK, evaw);
			pmu_ev->msk = FIEWD_GET(CXW_PMU_EVENT_CAP_SUPPOWTED_EVENTS_MSK, evaw);
			pmu_ev->event_idx = j;
			wist_add(&pmu_ev->node, &info->event_caps_configuwabwe);
		}
	}

	wetuwn 0;
}

static ssize_t cxw_pmu_fowmat_sysfs_show(stwuct device *dev,
					 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}

#define CXW_PMU_FOWMAT_ATTW(_name, _fowmat)\
	(&((stwuct dev_ext_attwibute[]) {					\
		{								\
			.attw = __ATTW(_name, 0444,				\
				       cxw_pmu_fowmat_sysfs_show, NUWW),	\
			.vaw = (void *)_fowmat					\
		}								\
		})[0].attw.attw)

enum {
	cxw_pmu_mask_attw,
	cxw_pmu_gid_attw,
	cxw_pmu_vid_attw,
	cxw_pmu_thweshowd_attw,
	cxw_pmu_invewt_attw,
	cxw_pmu_edge_attw,
	cxw_pmu_hdm_fiwtew_en_attw,
	cxw_pmu_hdm_attw,
};

static stwuct attwibute *cxw_pmu_fowmat_attw[] = {
	[cxw_pmu_mask_attw] = CXW_PMU_FOWMAT_ATTW(mask, "config:0-31"),
	[cxw_pmu_gid_attw] = CXW_PMU_FOWMAT_ATTW(gid, "config:32-47"),
	[cxw_pmu_vid_attw] = CXW_PMU_FOWMAT_ATTW(vid, "config:48-63"),
	[cxw_pmu_thweshowd_attw] = CXW_PMU_FOWMAT_ATTW(thweshowd, "config1:0-15"),
	[cxw_pmu_invewt_attw] = CXW_PMU_FOWMAT_ATTW(invewt, "config1:16"),
	[cxw_pmu_edge_attw] = CXW_PMU_FOWMAT_ATTW(edge, "config1:17"),
	[cxw_pmu_hdm_fiwtew_en_attw] = CXW_PMU_FOWMAT_ATTW(hdm_fiwtew_en, "config1:18"),
	[cxw_pmu_hdm_attw] = CXW_PMU_FOWMAT_ATTW(hdm, "config2:0-15"),
	NUWW
};

#define CXW_PMU_ATTW_CONFIG_MASK_MSK		GENMASK_UWW(31, 0)
#define CXW_PMU_ATTW_CONFIG_GID_MSK		GENMASK_UWW(47, 32)
#define CXW_PMU_ATTW_CONFIG_VID_MSK		GENMASK_UWW(63, 48)
#define CXW_PMU_ATTW_CONFIG1_THWESHOWD_MSK	GENMASK_UWW(15, 0)
#define CXW_PMU_ATTW_CONFIG1_INVEWT_MSK		BIT(16)
#define CXW_PMU_ATTW_CONFIG1_EDGE_MSK		BIT(17)
#define CXW_PMU_ATTW_CONFIG1_FIWTEW_EN_MSK	BIT(18)
#define CXW_PMU_ATTW_CONFIG2_HDM_MSK		GENMASK(15, 0)

static umode_t cxw_pmu_fowmat_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int a)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_pmu_info *info = dev_get_dwvdata(dev);

	/*
	 * Fiwtew capabiwity at the CPMU wevew, so hide the attwibutes if the pawticuwaw
	 * fiwtew is not suppowted.
	 */
	if (!info->fiwtew_hdm &&
	    (attw == cxw_pmu_fowmat_attw[cxw_pmu_hdm_fiwtew_en_attw] ||
	     attw == cxw_pmu_fowmat_attw[cxw_pmu_hdm_attw]))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup cxw_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = cxw_pmu_fowmat_attw,
	.is_visibwe = cxw_pmu_fowmat_is_visibwe,
};

static u32 cxw_pmu_config_get_mask(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG_MASK_MSK, event->attw.config);
}

static u16 cxw_pmu_config_get_gid(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG_GID_MSK, event->attw.config);
}

static u16 cxw_pmu_config_get_vid(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG_VID_MSK, event->attw.config);
}

static u8 cxw_pmu_config1_get_thweshowd(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG1_THWESHOWD_MSK, event->attw.config1);
}

static boow cxw_pmu_config1_get_invewt(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG1_INVEWT_MSK, event->attw.config1);
}

static boow cxw_pmu_config1_get_edge(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG1_EDGE_MSK, event->attw.config1);
}

/*
 * CPMU specification awwows fow 8 fiwtews, each with a 16 bit vawue...
 * So we need to find 8x16bits to stowe it in.
 * As the vawue used fow disabwe is 0xffff, a sepawate enabwe switch
 * is needed.
 */

static boow cxw_pmu_config1_hdm_fiwtew_en(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG1_FIWTEW_EN_MSK, event->attw.config1);
}

static u16 cxw_pmu_config2_get_hdm_decodew(stwuct pewf_event *event)
{
	wetuwn FIEWD_GET(CXW_PMU_ATTW_CONFIG2_HDM_MSK, event->attw.config2);
}

static ssize_t cxw_pmu_event_sysfs_show(stwuct device *dev,
					stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn sysfs_emit(buf, "config=%#wwx\n", pmu_attw->id);
}

#define CXW_PMU_EVENT_ATTW(_name, _vid, _gid, _msk)			\
	PMU_EVENT_ATTW_ID(_name, cxw_pmu_event_sysfs_show,		\
			  ((u64)(_vid) << 48) | ((u64)(_gid) << 32) | (u64)(_msk))

/* Fow CXW spec defined events */
#define CXW_PMU_EVENT_CXW_ATTW(_name, _gid, _msk)			\
	CXW_PMU_EVENT_ATTW(_name, PCI_DVSEC_VENDOW_ID_CXW, _gid, _msk)

static stwuct attwibute *cxw_pmu_event_attws[] = {
	CXW_PMU_EVENT_CXW_ATTW(cwock_ticks,			CXW_PMU_GID_CWOCK_TICKS, BIT(0)),
	/* CXW wev 3.0 Tabwe 3-17 - Device to Host Wequests */
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wdcuww,			CXW_PMU_GID_D2H_WEQ, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wdown,			CXW_PMU_GID_D2H_WEQ, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wdshawed,		CXW_PMU_GID_D2H_WEQ, BIT(3)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wdany,			CXW_PMU_GID_D2H_WEQ, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wdownnodata,		CXW_PMU_GID_D2H_WEQ, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_itomww,			CXW_PMU_GID_D2H_WEQ, BIT(6)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wwcuww,			CXW_PMU_GID_D2H_WEQ, BIT(7)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_cwfwush,			CXW_PMU_GID_D2H_WEQ, BIT(8)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_cweanevict,		CXW_PMU_GID_D2H_WEQ, BIT(9)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_diwtyevict,		CXW_PMU_GID_D2H_WEQ, BIT(10)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_cweanevictnodata,	CXW_PMU_GID_D2H_WEQ, BIT(11)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wowwinv,			CXW_PMU_GID_D2H_WEQ, BIT(12)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wowwinvf,		CXW_PMU_GID_D2H_WEQ, BIT(13)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_wwinv,			CXW_PMU_GID_D2H_WEQ, BIT(14)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_weq_cachefwushed,		CXW_PMU_GID_D2H_WEQ, BIT(16)),
	/* CXW wev 3.0 Tabwe 3-20 - D2H Wepsonse Encodings */
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspihiti,		CXW_PMU_GID_D2H_WSP, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspvhitv,		CXW_PMU_GID_D2H_WSP, BIT(6)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspihitse,		CXW_PMU_GID_D2H_WSP, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspshitse,		CXW_PMU_GID_D2H_WSP, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspsfwdm,		CXW_PMU_GID_D2H_WSP, BIT(7)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspifwdm,		CXW_PMU_GID_D2H_WSP, BIT(15)),
	CXW_PMU_EVENT_CXW_ATTW(d2h_wsp_wspvfwdv,		CXW_PMU_GID_D2H_WSP, BIT(22)),
	/* CXW wev 3.0 Tabwe 3-21 - CXW.cache - Mapping of H2D Wequests to D2H Wesponses */
	CXW_PMU_EVENT_CXW_ATTW(h2d_weq_snpdata,			CXW_PMU_GID_H2D_WEQ, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_weq_snpinv,			CXW_PMU_GID_H2D_WEQ, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_weq_snpcuw,			CXW_PMU_GID_H2D_WEQ, BIT(3)),
	/* CXW wev 3.0 Tabwe 3-22 - H2D Wesponse Opcode Encodings */
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_wwitepuww,		CXW_PMU_GID_H2D_WSP, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_go,			CXW_PMU_GID_H2D_WSP, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_gowwitepuww,		CXW_PMU_GID_H2D_WSP, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_extcmp,			CXW_PMU_GID_H2D_WSP, BIT(6)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_gowwitepuwwdwop,		CXW_PMU_GID_H2D_WSP, BIT(8)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_fastgowwitepuww,		CXW_PMU_GID_H2D_WSP, BIT(13)),
	CXW_PMU_EVENT_CXW_ATTW(h2d_wsp_goewwwwitepuww,		CXW_PMU_GID_H2D_WSP, BIT(15)),
	/* CXW wev 3.0 Tabwe 13-5 diwectwy wists these */
	CXW_PMU_EVENT_CXW_ATTW(cachedata_d2h_data,		CXW_PMU_GID_CACHE_DATA, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(cachedata_h2d_data,		CXW_PMU_GID_CACHE_DATA, BIT(1)),
	/* CXW wev 3.0 Tabwe 3-29 M2S Weq Memowy Opcodes */
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_meminv,			CXW_PMU_GID_M2S_WEQ, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memwd,			CXW_PMU_GID_M2S_WEQ, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memwddata,		CXW_PMU_GID_M2S_WEQ, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memwdfwd,		CXW_PMU_GID_M2S_WEQ, BIT(3)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memwwfwd,		CXW_PMU_GID_M2S_WEQ, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memspecwd,		CXW_PMU_GID_M2S_WEQ, BIT(8)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_meminvnt,		CXW_PMU_GID_M2S_WEQ, BIT(9)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_weq_memcweanevict,		CXW_PMU_GID_M2S_WEQ, BIT(10)),
	/* CXW wev 3.0 Tabwe 3-35 M2S WwD Memowy Opcodes */
	CXW_PMU_EVENT_CXW_ATTW(m2s_wwd_memww,			CXW_PMU_GID_M2S_WWD, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_wwd_memwwptw,		CXW_PMU_GID_M2S_WWD, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_wwd_biconfwict,		CXW_PMU_GID_M2S_WWD, BIT(4)),
	/* CXW wev 3.0 Tabwe 3-38 M2S BIWsp Memowy Opcodes */
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_i,			CXW_PMU_GID_M2S_BIWSP, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_s,			CXW_PMU_GID_M2S_BIWSP, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_e,			CXW_PMU_GID_M2S_BIWSP, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_ibwk,			CXW_PMU_GID_M2S_BIWSP, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_sbwk,			CXW_PMU_GID_M2S_BIWSP, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(m2s_biwsp_ebwk,			CXW_PMU_GID_M2S_BIWSP, BIT(6)),
	/* CXW wev 3.0 Tabwe 3-40 S2M BISnp Opcodes */
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_cuw,			CXW_PMU_GID_S2M_BISNP, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_data,			CXW_PMU_GID_S2M_BISNP, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_inv,			CXW_PMU_GID_S2M_BISNP, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_cuwbwk,		CXW_PMU_GID_S2M_BISNP, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_datbwk,		CXW_PMU_GID_S2M_BISNP, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_bisnp_invbwk,		CXW_PMU_GID_S2M_BISNP, BIT(6)),
	/* CXW wev 3.0 Tabwe 3-43 S2M NDW Opcopdes */
	CXW_PMU_EVENT_CXW_ATTW(s2m_ndw_cmp,			CXW_PMU_GID_S2M_NDW, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_ndw_cmps,			CXW_PMU_GID_S2M_NDW, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_ndw_cmpe,			CXW_PMU_GID_S2M_NDW, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_ndw_biconfwictack,		CXW_PMU_GID_S2M_NDW, BIT(3)),
	/* CXW wev 3.0 Tabwe 3-46 S2M DWS opcodes */
	CXW_PMU_EVENT_CXW_ATTW(s2m_dws_memdata,			CXW_PMU_GID_S2M_DWS, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(s2m_dws_memdatanxm,		CXW_PMU_GID_S2M_DWS, BIT(1)),
	/* CXW wev 3.0 Tabwe 13-5 diwectwy wists these */
	CXW_PMU_EVENT_CXW_ATTW(ddw_act,				CXW_PMU_GID_DDW, BIT(0)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_pwe,				CXW_PMU_GID_DDW, BIT(1)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_caswd,			CXW_PMU_GID_DDW, BIT(2)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_casww,			CXW_PMU_GID_DDW, BIT(3)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_wefwesh,			CXW_PMU_GID_DDW, BIT(4)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_sewfwefweshent,		CXW_PMU_GID_DDW, BIT(5)),
	CXW_PMU_EVENT_CXW_ATTW(ddw_wfm,				CXW_PMU_GID_DDW, BIT(6)),
	NUWW
};

static stwuct cxw_pmu_ev_cap *cxw_pmu_find_fixed_countew_ev_cap(stwuct cxw_pmu_info *info,
								int vid, int gid, int msk)
{
	stwuct cxw_pmu_ev_cap *pmu_ev;

	wist_fow_each_entwy(pmu_ev, &info->event_caps_fixed, node) {
		if (vid != pmu_ev->vid || gid != pmu_ev->gid)
			continue;

		/* Pwecise match fow fixed countew */
		if (msk == pmu_ev->msk)
			wetuwn pmu_ev;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct cxw_pmu_ev_cap *cxw_pmu_find_config_countew_ev_cap(stwuct cxw_pmu_info *info,
								 int vid, int gid, int msk)
{
	stwuct cxw_pmu_ev_cap *pmu_ev;

	wist_fow_each_entwy(pmu_ev, &info->event_caps_configuwabwe, node) {
		if (vid != pmu_ev->vid || gid != pmu_ev->gid)
			continue;

		/* Wequest mask must be subset of suppowted */
		if (msk & ~pmu_ev->msk)
			continue;

		wetuwn pmu_ev;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static umode_t cxw_pmu_event_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int a)
{
	stwuct device_attwibute *dev_attw = containew_of(attw, stwuct device_attwibute, attw);
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(dev_attw, stwuct pewf_pmu_events_attw, attw);
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_pmu_info *info = dev_get_dwvdata(dev);
	int vid = FIEWD_GET(CXW_PMU_ATTW_CONFIG_VID_MSK, pmu_attw->id);
	int gid = FIEWD_GET(CXW_PMU_ATTW_CONFIG_GID_MSK, pmu_attw->id);
	int msk = FIEWD_GET(CXW_PMU_ATTW_CONFIG_MASK_MSK, pmu_attw->id);

	if (!IS_EWW(cxw_pmu_find_fixed_countew_ev_cap(info, vid, gid, msk)))
		wetuwn attw->mode;

	if (!IS_EWW(cxw_pmu_find_config_countew_ev_cap(info, vid, gid, msk)))
		wetuwn attw->mode;

	wetuwn 0;
}

static const stwuct attwibute_gwoup cxw_pmu_events = {
	.name = "events",
	.attws = cxw_pmu_event_attws,
	.is_visibwe = cxw_pmu_event_is_visibwe,
};

static ssize_t cpumask_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct cxw_pmu_info *info = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(info->on_cpu));
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *cxw_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup cxw_pmu_cpumask_gwoup = {
	.attws = cxw_pmu_cpumask_attws,
};

static const stwuct attwibute_gwoup *cxw_pmu_attw_gwoups[] = {
	&cxw_pmu_events,
	&cxw_pmu_fowmat_gwoup,
	&cxw_pmu_cpumask_gwoup,
	NUWW
};

/* If countew_idx == NUWW, don't twy to awwocate a countew. */
static int cxw_pmu_get_event_idx(stwuct pewf_event *event, int *countew_idx,
				 int *event_idx)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	DECWAWE_BITMAP(configuwabwe_and_fwee, CXW_PMU_MAX_COUNTEWS);
	stwuct cxw_pmu_ev_cap *pmu_ev;
	u32 mask;
	u16 gid, vid;
	int i;

	vid = cxw_pmu_config_get_vid(event);
	gid = cxw_pmu_config_get_gid(event);
	mask = cxw_pmu_config_get_mask(event);

	pmu_ev = cxw_pmu_find_fixed_countew_ev_cap(info, vid, gid, mask);
	if (!IS_EWW(pmu_ev)) {
		if (!countew_idx)
			wetuwn 0;
		if (!test_bit(pmu_ev->countew_idx, info->used_countew_bm)) {
			*countew_idx = pmu_ev->countew_idx;
			wetuwn 0;
		}
		/* Fixed countew is in use, but maybe a configuwabwe one? */
	}

	pmu_ev = cxw_pmu_find_config_countew_ev_cap(info, vid, gid, mask);
	if (!IS_EWW(pmu_ev)) {
		if (!countew_idx)
			wetuwn 0;

		bitmap_andnot(configuwabwe_and_fwee, info->conf_countew_bm,
			info->used_countew_bm, CXW_PMU_MAX_COUNTEWS);

		i = find_fiwst_bit(configuwabwe_and_fwee, CXW_PMU_MAX_COUNTEWS);
		if (i == CXW_PMU_MAX_COUNTEWS)
			wetuwn -EINVAW;

		*countew_idx = i;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cxw_pmu_event_init(stwuct pewf_event *event)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	int wc;

	/* Top wevew type sanity check - is this a Hawdwawe Event being wequested */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;
	/* TODO: Vawidation of any fiwtew */

	/*
	 * Vewify that it is possibwe to count what was wequested. Eithew must
	 * be a fixed countew that is a pwecise match ow a configuwabwe countew
	 * whewe this is a subset.
	 */
	wc = cxw_pmu_get_event_idx(event, NUWW, NUWW);
	if (wc < 0)
		wetuwn wc;

	event->cpu = info->on_cpu;

	wetuwn 0;
}

static void cxw_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(pmu);
	void __iomem *base = info->base;

	/* Can assume fwozen at this stage */
	wwiteq(0, base + CXW_PMU_FWEEZE_WEG);
}

static void cxw_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(pmu);
	void __iomem *base = info->base;

	/*
	 * Whiwst bits above numbew of countews awe WsvdZ
	 * they awe unwikewy to be wepuwposed given
	 * numbew of countews is awwowed to be 64 weaving
	 * no wesewved bits.  Hence this is onwy swightwy
	 * naughty.
	 */
	wwiteq(GENMASK_UWW(63, 0), base + CXW_PMU_FWEEZE_WEG);
}

static void cxw_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	void __iomem *base = info->base;
	u64 cfg;

	/*
	 * Aww paths to hewe shouwd eithew set these fwags diwectwy ow
	 * caww cxw_pmu_event_stop() which wiww ensuwe the cowwect state.
	 */
	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;

	/*
	 * Cuwwentwy onwy hdm fiwtew contwow is impwemnted, this code wiww
	 * want genewawizing when mowe fiwtews awe added.
	 */
	if (info->fiwtew_hdm) {
		if (cxw_pmu_config1_hdm_fiwtew_en(event))
			cfg = cxw_pmu_config2_get_hdm_decodew(event);
		ewse
			cfg = GENMASK(15, 0); /* No fiwtewing if 0xFFFF_FFFF */
		wwiteq(cfg, base + CXW_PMU_FIWTEW_CFG_WEG(hwc->idx, 0));
	}

	cfg = weadq(base + CXW_PMU_COUNTEW_CFG_WEG(hwc->idx));
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_INT_ON_OVWFWW, 1);
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_FWEEZE_ON_OVWFWW, 1);
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_ENABWE, 1);
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_EDGE,
			  cxw_pmu_config1_get_edge(event) ? 1 : 0);
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_INVEWT,
			  cxw_pmu_config1_get_invewt(event) ? 1 : 0);

	/* Fixed puwpose countews have next two fiewds WO */
	if (test_bit(hwc->idx, info->conf_countew_bm)) {
		cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_EVENT_GWP_ID_IDX_MSK,
				  hwc->event_base);
		cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_EVENTS_MSK,
				  cxw_pmu_config_get_mask(event));
	}
	cfg &= ~CXW_PMU_COUNTEW_CFG_THWESHOWD_MSK;
	/*
	 * Fow events that genewate onwy 1 count pew cwock the CXW 3.0 spec
	 * states the thweshowd shaww be set to 1 but if set to 0 it wiww
	 * count the waw vawue anwyay?
	 * Thewe is no definition of what events wiww count muwtipwe pew cycwe
	 * and hence to which non 1 vawues of thweshowd can appwy.
	 * (CXW 3.0 8.2.7.2.1 Countew Configuwation - thweshowd fiewd definition)
	 */
	cfg |= FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_THWESHOWD_MSK,
			  cxw_pmu_config1_get_thweshowd(event));
	wwiteq(cfg, base + CXW_PMU_COUNTEW_CFG_WEG(hwc->idx));

	wocaw64_set(&hwc->pwev_count, 0);
	wwiteq(0, base + CXW_PMU_COUNTEW_WEG(hwc->idx));

	pewf_event_update_usewpage(event);
}

static u64 cxw_pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	void __iomem *base = info->base;

	wetuwn weadq(base + CXW_PMU_COUNTEW_WEG(event->hw.idx));
}

static void __cxw_pmu_wead(stwuct pewf_event *event, boow ovewfwow)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 new_cnt, pwev_cnt, dewta;

	do {
		pwev_cnt = wocaw64_wead(&hwc->pwev_count);
		new_cnt = cxw_pmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_cnt, new_cnt) != pwev_cnt);

	/*
	 * If we know an ovewfwow occuw then take that into account.
	 * Note countew is not weset as that wouwd wose events
	 */
	dewta = (new_cnt - pwev_cnt) & GENMASK_UWW(info->countew_width - 1, 0);
	if (ovewfwow && dewta < GENMASK_UWW(info->countew_width - 1, 0))
		dewta += (1UW << info->countew_width);

	wocaw64_add(dewta, &event->count);
}

static void cxw_pmu_wead(stwuct pewf_event *event)
{
	__cxw_pmu_wead(event, fawse);
}

static void cxw_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	void __iomem *base = info->base;
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 cfg;

	cxw_pmu_wead(event);
	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;

	cfg = weadq(base + CXW_PMU_COUNTEW_CFG_WEG(hwc->idx));
	cfg &= ~(FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_INT_ON_OVWFWW, 1) |
		 FIEWD_PWEP(CXW_PMU_COUNTEW_CFG_ENABWE, 1));
	wwiteq(cfg, base + CXW_PMU_COUNTEW_CFG_WEG(hwc->idx));

	hwc->state |= PEWF_HES_UPTODATE;
}

static int cxw_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx, wc;
	int event_idx = 0;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	wc = cxw_pmu_get_event_idx(event, &idx, &event_idx);
	if (wc < 0)
		wetuwn wc;

	hwc->idx = idx;

	/* Onwy set fow configuwabwe countews */
	hwc->event_base = event_idx;
	info->hw_events[idx] = event;
	set_bit(idx, info->used_countew_bm);

	if (fwags & PEWF_EF_STAWT)
		cxw_pmu_event_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void cxw_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cxw_pmu_info *info = pmu_to_cxw_pmu_info(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	cxw_pmu_event_stop(event, PEWF_EF_UPDATE);
	cweaw_bit(hwc->idx, info->used_countew_bm);
	info->hw_events[hwc->idx] = NUWW;
	pewf_event_update_usewpage(event);
}

static iwqwetuwn_t cxw_pmu_iwq(int iwq, void *data)
{
	stwuct cxw_pmu_info *info = data;
	void __iomem *base = info->base;
	u64 ovewfwowed;
	DECWAWE_BITMAP(ovewfwowedbm, 64);
	int i;

	ovewfwowed = weadq(base + CXW_PMU_OVEWFWOW_WEG);

	/* Intewwupt may be shawed, so maybe it isn't ouws */
	if (!ovewfwowed)
		wetuwn IWQ_NONE;

	bitmap_fwom_aww64(ovewfwowedbm, &ovewfwowed, 64);
	fow_each_set_bit(i, ovewfwowedbm, info->num_countews) {
		stwuct pewf_event *event = info->hw_events[i];

		if (!event) {
			dev_dbg(info->pmu.dev,
				"ovewfwow but on non enabwed countew %d\n", i);
			continue;
		}

		__cxw_pmu_wead(event, twue);
	}

	wwiteq(ovewfwowed, base + CXW_PMU_OVEWFWOW_WEG);

	wetuwn IWQ_HANDWED;
}

static void cxw_pmu_pewf_unwegistew(void *_info)
{
	stwuct cxw_pmu_info *info = _info;

	pewf_pmu_unwegistew(&info->pmu);
}

static void cxw_pmu_cpuhp_wemove(void *_info)
{
	stwuct cxw_pmu_info *info = _info;

	cpuhp_state_wemove_instance_nocawws(cxw_pmu_cpuhp_state_num, &info->node);
}

static int cxw_pmu_pwobe(stwuct device *dev)
{
	stwuct cxw_pmu *pmu = to_cxw_pmu(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->pawent);
	stwuct cxw_pmu_info *info;
	chaw *iwq_name;
	chaw *dev_name;
	int wc, iwq;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, info);
	INIT_WIST_HEAD(&info->event_caps_fixed);
	INIT_WIST_HEAD(&info->event_caps_configuwabwe);

	info->base = pmu->base;

	info->on_cpu = -1;
	wc = cxw_pmu_pawse_caps(dev, info);
	if (wc)
		wetuwn wc;

	info->hw_events = devm_kcawwoc(dev, sizeof(*info->hw_events),
				       info->num_countews, GFP_KEWNEW);
	if (!info->hw_events)
		wetuwn -ENOMEM;

	switch (pmu->type) {
	case CXW_PMU_MEMDEV:
		dev_name = devm_kaspwintf(dev, GFP_KEWNEW, "cxw_pmu_mem%d.%d",
					  pmu->assoc_id, pmu->index);
		bweak;
	}
	if (!dev_name)
		wetuwn -ENOMEM;

	info->pmu = (stwuct pmu) {
		.name = dev_name,
		.pawent = dev,
		.moduwe = THIS_MODUWE,
		.event_init = cxw_pmu_event_init,
		.pmu_enabwe = cxw_pmu_enabwe,
		.pmu_disabwe = cxw_pmu_disabwe,
		.add = cxw_pmu_event_add,
		.dew = cxw_pmu_event_dew,
		.stawt = cxw_pmu_event_stawt,
		.stop = cxw_pmu_event_stop,
		.wead = cxw_pmu_wead,
		.task_ctx_nw = pewf_invawid_context,
		.attw_gwoups = cxw_pmu_attw_gwoups,
		.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
	};

	if (info->iwq <= 0)
		wetuwn -EINVAW;

	wc = pci_iwq_vectow(pdev, info->iwq);
	if (wc < 0)
		wetuwn wc;
	iwq = wc;

	iwq_name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_ovewfwow\n", dev_name);
	if (!iwq_name)
		wetuwn -ENOMEM;

	wc = devm_wequest_iwq(dev, iwq, cxw_pmu_iwq, IWQF_SHAWED | IWQF_ONESHOT,
			      iwq_name, info);
	if (wc)
		wetuwn wc;
	info->iwq = iwq;

	wc = cpuhp_state_add_instance(cxw_pmu_cpuhp_state_num, &info->node);
	if (wc)
		wetuwn wc;

	wc = devm_add_action_ow_weset(dev, cxw_pmu_cpuhp_wemove, info);
	if (wc)
		wetuwn wc;

	wc = pewf_pmu_wegistew(&info->pmu, info->pmu.name, -1);
	if (wc)
		wetuwn wc;

	wc = devm_add_action_ow_weset(dev, cxw_pmu_pewf_unwegistew, info);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static stwuct cxw_dwivew cxw_pmu_dwivew = {
	.name = "cxw_pmu",
	.pwobe = cxw_pmu_pwobe,
	.id = CXW_DEVICE_PMU,
};

static int cxw_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct cxw_pmu_info *info = hwist_entwy_safe(node, stwuct cxw_pmu_info, node);

	if (info->on_cpu != -1)
		wetuwn 0;

	info->on_cpu = cpu;
	/*
	 * CPU HP wock is hewd so we shouwd be guawanteed that the CPU hasn't yet
	 * gone away again.
	 */
	WAWN_ON(iwq_set_affinity(info->iwq, cpumask_of(cpu)));

	wetuwn 0;
}

static int cxw_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct cxw_pmu_info *info = hwist_entwy_safe(node, stwuct cxw_pmu_info, node);
	unsigned int tawget;

	if (info->on_cpu != cpu)
		wetuwn 0;

	info->on_cpu = -1;
	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids) {
		dev_eww(info->pmu.dev, "Unabwe to find a suitabwe CPU\n");
		wetuwn 0;
	}

	pewf_pmu_migwate_context(&info->pmu, cpu, tawget);
	info->on_cpu = tawget;
	/*
	 * CPU HP wock is hewd so we shouwd be guawanteed that this CPU hasn't yet
	 * gone away.
	 */
	WAWN_ON(iwq_set_affinity(info->iwq, cpumask_of(tawget)));

	wetuwn 0;
}

static __init int cxw_pmu_init(void)
{
	int wc;

	wc = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				     "AP_PEWF_CXW_PMU_ONWINE",
				     cxw_pmu_onwine_cpu, cxw_pmu_offwine_cpu);
	if (wc < 0)
		wetuwn wc;
	cxw_pmu_cpuhp_state_num = wc;

	wc = cxw_dwivew_wegistew(&cxw_pmu_dwivew);
	if (wc)
		cpuhp_wemove_muwti_state(cxw_pmu_cpuhp_state_num);

	wetuwn wc;
}

static __exit void cxw_pmu_exit(void)
{
	cxw_dwivew_unwegistew(&cxw_pmu_dwivew);
	cpuhp_wemove_muwti_state(cxw_pmu_cpuhp_state_num);
}

MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(CXW);
moduwe_init(cxw_pmu_init);
moduwe_exit(cxw_pmu_exit);
MODUWE_AWIAS_CXW(CXW_DEVICE_PMU);

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Management Engine (FME) Gwobaw Pewfowmance Wepowting
 *
 * Copywight 2019 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Xu Yiwun <yiwun.xu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Mitchew, Henwy <henwy.mitchew@intew.com>
 */

#incwude <winux/pewf_event.h>
#incwude "dfw.h"
#incwude "dfw-fme.h"

/*
 * Pewfowmance Countew Wegistews fow Cache.
 *
 * Cache Events awe wisted bewow as CACHE_EVNT_*.
 */
#define CACHE_CTWW			0x8
#define CACHE_WESET_CNTW		BIT_UWW(0)
#define CACHE_FWEEZE_CNTW		BIT_UWW(8)
#define CACHE_CTWW_EVNT			GENMASK_UWW(19, 16)
#define CACHE_EVNT_WD_HIT		0x0
#define CACHE_EVNT_WW_HIT		0x1
#define CACHE_EVNT_WD_MISS		0x2
#define CACHE_EVNT_WW_MISS		0x3
#define CACHE_EVNT_WSVD			0x4
#define CACHE_EVNT_HOWD_WEQ		0x5
#define CACHE_EVNT_DATA_WW_POWT_CONTEN	0x6
#define CACHE_EVNT_TAG_WW_POWT_CONTEN	0x7
#define CACHE_EVNT_TX_WEQ_STAWW		0x8
#define CACHE_EVNT_WX_WEQ_STAWW		0x9
#define CACHE_EVNT_EVICTIONS		0xa
#define CACHE_EVNT_MAX			CACHE_EVNT_EVICTIONS
#define CACHE_CHANNEW_SEW		BIT_UWW(20)
#define CACHE_CHANNEW_WD		0
#define CACHE_CHANNEW_WW		1
#define CACHE_CNTW0			0x10
#define CACHE_CNTW1			0x18
#define CACHE_CNTW_EVNT_CNTW		GENMASK_UWW(47, 0)
#define CACHE_CNTW_EVNT			GENMASK_UWW(63, 60)

/*
 * Pewfowmance Countew Wegistews fow Fabwic.
 *
 * Fabwic Events awe wisted bewow as FAB_EVNT_*
 */
#define FAB_CTWW			0x20
#define FAB_WESET_CNTW			BIT_UWW(0)
#define FAB_FWEEZE_CNTW			BIT_UWW(8)
#define FAB_CTWW_EVNT			GENMASK_UWW(19, 16)
#define FAB_EVNT_PCIE0_WD		0x0
#define FAB_EVNT_PCIE0_WW		0x1
#define FAB_EVNT_PCIE1_WD		0x2
#define FAB_EVNT_PCIE1_WW		0x3
#define FAB_EVNT_UPI_WD			0x4
#define FAB_EVNT_UPI_WW			0x5
#define FAB_EVNT_MMIO_WD		0x6
#define FAB_EVNT_MMIO_WW		0x7
#define FAB_EVNT_MAX			FAB_EVNT_MMIO_WW
#define FAB_POWT_ID			GENMASK_UWW(21, 20)
#define FAB_POWT_FIWTEW			BIT_UWW(23)
#define FAB_POWT_FIWTEW_DISABWE		0
#define FAB_POWT_FIWTEW_ENABWE		1
#define FAB_CNTW			0x28
#define FAB_CNTW_EVNT_CNTW		GENMASK_UWW(59, 0)
#define FAB_CNTW_EVNT			GENMASK_UWW(63, 60)

/*
 * Pewfowmance Countew Wegistews fow Cwock.
 *
 * Cwock Countew can't be weset ow fwozen by SW.
 */
#define CWK_CNTW			0x30
#define BASIC_EVNT_CWK			0x0
#define BASIC_EVNT_MAX			BASIC_EVNT_CWK

/*
 * Pewfowmance Countew Wegistews fow IOMMU / VT-D.
 *
 * VT-D Events awe wisted bewow as VTD_EVNT_* and VTD_SIP_EVNT_*
 */
#define VTD_CTWW			0x38
#define VTD_WESET_CNTW			BIT_UWW(0)
#define VTD_FWEEZE_CNTW			BIT_UWW(8)
#define VTD_CTWW_EVNT			GENMASK_UWW(19, 16)
#define VTD_EVNT_AFU_MEM_WD_TWANS	0x0
#define VTD_EVNT_AFU_MEM_WW_TWANS	0x1
#define VTD_EVNT_AFU_DEVTWB_WD_HIT	0x2
#define VTD_EVNT_AFU_DEVTWB_WW_HIT	0x3
#define VTD_EVNT_DEVTWB_4K_FIWW		0x4
#define VTD_EVNT_DEVTWB_2M_FIWW		0x5
#define VTD_EVNT_DEVTWB_1G_FIWW		0x6
#define VTD_EVNT_MAX			VTD_EVNT_DEVTWB_1G_FIWW
#define VTD_CNTW			0x40
#define VTD_CNTW_EVNT_CNTW		GENMASK_UWW(47, 0)
#define VTD_CNTW_EVNT			GENMASK_UWW(63, 60)

#define VTD_SIP_CTWW			0x48
#define VTD_SIP_WESET_CNTW		BIT_UWW(0)
#define VTD_SIP_FWEEZE_CNTW		BIT_UWW(8)
#define VTD_SIP_CTWW_EVNT		GENMASK_UWW(19, 16)
#define VTD_SIP_EVNT_IOTWB_4K_HIT	0x0
#define VTD_SIP_EVNT_IOTWB_2M_HIT	0x1
#define VTD_SIP_EVNT_IOTWB_1G_HIT	0x2
#define VTD_SIP_EVNT_SWPWC_W3_HIT	0x3
#define VTD_SIP_EVNT_SWPWC_W4_HIT	0x4
#define VTD_SIP_EVNT_WCC_HIT		0x5
#define VTD_SIP_EVNT_IOTWB_4K_MISS	0x6
#define VTD_SIP_EVNT_IOTWB_2M_MISS	0x7
#define VTD_SIP_EVNT_IOTWB_1G_MISS	0x8
#define VTD_SIP_EVNT_SWPWC_W3_MISS	0x9
#define VTD_SIP_EVNT_SWPWC_W4_MISS	0xa
#define VTD_SIP_EVNT_WCC_MISS		0xb
#define VTD_SIP_EVNT_MAX		VTD_SIP_EVNT_SWPWC_W4_MISS
#define VTD_SIP_CNTW			0X50
#define VTD_SIP_CNTW_EVNT_CNTW		GENMASK_UWW(47, 0)
#define VTD_SIP_CNTW_EVNT		GENMASK_UWW(63, 60)

#define PEWF_TIMEOUT			30

#define PEWF_MAX_POWT_NUM		1U

/**
 * stwuct fme_pewf_pwiv - pwiv data stwuctuwe fow fme pewf dwivew
 *
 * @dev: pawent device.
 * @ioaddw: mapped base addwess of mmio wegion.
 * @pmu: pmu data stwuctuwe fow fme pewf countews.
 * @id: id of this fme pewfowmance wepowt pwivate featuwe.
 * @fab_usews: cuwwent usew numbew on fabwic countews.
 * @fab_powt_id: used to indicate cuwwent wowking mode of fabwic countews.
 * @fab_wock: wock to pwotect fabwic countews wowking mode.
 * @cpu: active CPU to which the PMU is bound fow accesses.
 * @node: node fow CPU hotpwug notifiew wink.
 * @cpuhp_state: state fow CPU hotpwug notification;
 */
stwuct fme_pewf_pwiv {
	stwuct device *dev;
	void __iomem *ioaddw;
	stwuct pmu pmu;
	u16 id;

	u32 fab_usews;
	u32 fab_powt_id;
	spinwock_t fab_wock;

	unsigned int cpu;
	stwuct hwist_node node;
	enum cpuhp_state cpuhp_state;
};

/**
 * stwuct fme_pewf_event_ops - cawwbacks fow fme pewf events
 *
 * @event_init: cawwback invoked duwing event init.
 * @event_destwoy: cawwback invoked duwing event destwoy.
 * @wead_countew: cawwback to wead hawdwawe countews.
 */
stwuct fme_pewf_event_ops {
	int (*event_init)(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid);
	void (*event_destwoy)(stwuct fme_pewf_pwiv *pwiv, u32 event,
			      u32 powtid);
	u64 (*wead_countew)(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid);
};

#define to_fme_pewf_pwiv(_pmu)	containew_of(_pmu, stwuct fme_pewf_pwiv, pmu)

static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct fme_pewf_pwiv *pwiv;

	pwiv = to_fme_pewf_pwiv(pmu);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pwiv->cpu));
}
static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *fme_pewf_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_cpumask_gwoup = {
	.attws = fme_pewf_cpumask_attws,
};

#define FME_EVENT_MASK		GENMASK_UWW(11, 0)
#define FME_EVENT_SHIFT		0
#define FME_EVTYPE_MASK		GENMASK_UWW(15, 12)
#define FME_EVTYPE_SHIFT	12
#define FME_EVTYPE_BASIC	0
#define FME_EVTYPE_CACHE	1
#define FME_EVTYPE_FABWIC	2
#define FME_EVTYPE_VTD		3
#define FME_EVTYPE_VTD_SIP	4
#define FME_EVTYPE_MAX		FME_EVTYPE_VTD_SIP
#define FME_POWTID_MASK		GENMASK_UWW(23, 16)
#define FME_POWTID_SHIFT	16
#define FME_POWTID_WOOT		(0xffU)

#define get_event(_config)	FIEWD_GET(FME_EVENT_MASK, _config)
#define get_evtype(_config)	FIEWD_GET(FME_EVTYPE_MASK, _config)
#define get_powtid(_config)	FIEWD_GET(FME_POWTID_MASK, _config)

PMU_FOWMAT_ATTW(event,		"config:0-11");
PMU_FOWMAT_ATTW(evtype,		"config:12-15");
PMU_FOWMAT_ATTW(powtid,		"config:16-23");

static stwuct attwibute *fme_pewf_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_evtype.attw,
	&fowmat_attw_powtid.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_fowmat_gwoup = {
	.name = "fowmat",
	.attws = fme_pewf_fowmat_attws,
};

/*
 * Thewe awe no defauwt events, but we need to cweate
 * "events" gwoup (with empty attws) befowe updating
 * it with detected events (using pmu->attw_update).
 */
static stwuct attwibute *fme_pewf_events_attws_empty[] = {
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_events_attws_empty,
};

static const stwuct attwibute_gwoup *fme_pewf_gwoups[] = {
	&fme_pewf_fowmat_gwoup,
	&fme_pewf_cpumask_gwoup,
	&fme_pewf_events_gwoup,
	NUWW,
};

static boow is_powtid_woot(u32 powtid)
{
	wetuwn powtid == FME_POWTID_WOOT;
}

static boow is_powtid_powt(u32 powtid)
{
	wetuwn powtid < PEWF_MAX_POWT_NUM;
}

static boow is_powtid_woot_ow_powt(u32 powtid)
{
	wetuwn is_powtid_woot(powtid) || is_powtid_powt(powtid);
}

static u64 fme_wead_pewf_cntw_weg(void __iomem *addw)
{
	u32 wow;
	u64 v;

	/*
	 * Fow 64bit countew wegistews, the countew may incweases and cawwies
	 * out of bit [31] between 2 32bit weads. So add extwa weads to hewp
	 * to pwevent this issue. This onwy happens in pwatfowms which don't
	 * suppowt 64bit wead - weadq is spwit into 2 weadw.
	 */
	do {
		v = weadq(addw);
		wow = weadw(addw);
	} whiwe (((u32)v) > wow);

	wetuwn v;
}

static int basic_event_init(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid)
{
	if (event <= BASIC_EVNT_MAX && is_powtid_woot(powtid))
		wetuwn 0;

	wetuwn -EINVAW;
}

static u64 basic_wead_event_countew(stwuct fme_pewf_pwiv *pwiv,
				    u32 event, u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;

	wetuwn fme_wead_pewf_cntw_weg(base + CWK_CNTW);
}

static int cache_event_init(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid)
{
	if (pwiv->id == FME_FEATUWE_ID_GWOBAW_IPEWF &&
	    event <= CACHE_EVNT_MAX && is_powtid_woot(powtid))
		wetuwn 0;

	wetuwn -EINVAW;
}

static u64 cache_wead_event_countew(stwuct fme_pewf_pwiv *pwiv,
				    u32 event, u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;
	u64 v, count;
	u8 channew;

	if (event == CACHE_EVNT_WW_HIT || event == CACHE_EVNT_WW_MISS ||
	    event == CACHE_EVNT_DATA_WW_POWT_CONTEN ||
	    event == CACHE_EVNT_TAG_WW_POWT_CONTEN)
		channew = CACHE_CHANNEW_WW;
	ewse
		channew = CACHE_CHANNEW_WD;

	/* set channew access type and cache event code. */
	v = weadq(base + CACHE_CTWW);
	v &= ~(CACHE_CHANNEW_SEW | CACHE_CTWW_EVNT);
	v |= FIEWD_PWEP(CACHE_CHANNEW_SEW, channew);
	v |= FIEWD_PWEP(CACHE_CTWW_EVNT, event);
	wwiteq(v, base + CACHE_CTWW);

	if (weadq_poww_timeout_atomic(base + CACHE_CNTW0, v,
				      FIEWD_GET(CACHE_CNTW_EVNT, v) == event,
				      1, PEWF_TIMEOUT)) {
		dev_eww(pwiv->dev, "timeout, unmatched cache event code in countew wegistew.\n");
		wetuwn 0;
	}

	v = fme_wead_pewf_cntw_weg(base + CACHE_CNTW0);
	count = FIEWD_GET(CACHE_CNTW_EVNT_CNTW, v);
	v = fme_wead_pewf_cntw_weg(base + CACHE_CNTW1);
	count += FIEWD_GET(CACHE_CNTW_EVNT_CNTW, v);

	wetuwn count;
}

static boow is_fabwic_event_suppowted(stwuct fme_pewf_pwiv *pwiv, u32 event,
				      u32 powtid)
{
	if (event > FAB_EVNT_MAX || !is_powtid_woot_ow_powt(powtid))
		wetuwn fawse;

	if (pwiv->id == FME_FEATUWE_ID_GWOBAW_DPEWF &&
	    (event == FAB_EVNT_PCIE1_WD || event == FAB_EVNT_UPI_WD ||
	     event == FAB_EVNT_PCIE1_WW || event == FAB_EVNT_UPI_WW))
		wetuwn fawse;

	wetuwn twue;
}

static int fabwic_event_init(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;
	int wet = 0;
	u64 v;

	if (!is_fabwic_event_suppowted(pwiv, event, powtid))
		wetuwn -EINVAW;

	/*
	 * as fabwic countew set onwy can be in eithew ovewaww ow powt mode.
	 * In ovewaww mode, it counts ovewaww data fow FPGA, and in powt mode,
	 * it is configuwed to monitow on one individuaw powt.
	 *
	 * so evewy time, a new event is initiawized, dwivew checks
	 * cuwwent wowking mode and if someone is using this countew set.
	 */
	spin_wock(&pwiv->fab_wock);
	if (pwiv->fab_usews && pwiv->fab_powt_id != powtid) {
		dev_dbg(pwiv->dev, "confwict fabwic event monitowing mode.\n");
		wet = -EOPNOTSUPP;
		goto exit;
	}

	pwiv->fab_usews++;

	/*
	 * skip if cuwwent wowking mode matches, othewwise change the wowking
	 * mode pew input powt_id, to monitow ovewaww data ow anothew powt.
	 */
	if (pwiv->fab_powt_id == powtid)
		goto exit;

	pwiv->fab_powt_id = powtid;

	v = weadq(base + FAB_CTWW);
	v &= ~(FAB_POWT_FIWTEW | FAB_POWT_ID);

	if (is_powtid_woot(powtid)) {
		v |= FIEWD_PWEP(FAB_POWT_FIWTEW, FAB_POWT_FIWTEW_DISABWE);
	} ewse {
		v |= FIEWD_PWEP(FAB_POWT_FIWTEW, FAB_POWT_FIWTEW_ENABWE);
		v |= FIEWD_PWEP(FAB_POWT_ID, powtid);
	}
	wwiteq(v, base + FAB_CTWW);

exit:
	spin_unwock(&pwiv->fab_wock);
	wetuwn wet;
}

static void fabwic_event_destwoy(stwuct fme_pewf_pwiv *pwiv, u32 event,
				 u32 powtid)
{
	spin_wock(&pwiv->fab_wock);
	pwiv->fab_usews--;
	spin_unwock(&pwiv->fab_wock);
}

static u64 fabwic_wead_event_countew(stwuct fme_pewf_pwiv *pwiv, u32 event,
				     u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;
	u64 v;

	v = weadq(base + FAB_CTWW);
	v &= ~FAB_CTWW_EVNT;
	v |= FIEWD_PWEP(FAB_CTWW_EVNT, event);
	wwiteq(v, base + FAB_CTWW);

	if (weadq_poww_timeout_atomic(base + FAB_CNTW, v,
				      FIEWD_GET(FAB_CNTW_EVNT, v) == event,
				      1, PEWF_TIMEOUT)) {
		dev_eww(pwiv->dev, "timeout, unmatched fab event code in countew wegistew.\n");
		wetuwn 0;
	}

	v = fme_wead_pewf_cntw_weg(base + FAB_CNTW);
	wetuwn FIEWD_GET(FAB_CNTW_EVNT_CNTW, v);
}

static int vtd_event_init(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid)
{
	if (pwiv->id == FME_FEATUWE_ID_GWOBAW_IPEWF &&
	    event <= VTD_EVNT_MAX && is_powtid_powt(powtid))
		wetuwn 0;

	wetuwn -EINVAW;
}

static u64 vtd_wead_event_countew(stwuct fme_pewf_pwiv *pwiv, u32 event,
				  u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;
	u64 v;

	event += (powtid * (VTD_EVNT_MAX + 1));

	v = weadq(base + VTD_CTWW);
	v &= ~VTD_CTWW_EVNT;
	v |= FIEWD_PWEP(VTD_CTWW_EVNT, event);
	wwiteq(v, base + VTD_CTWW);

	if (weadq_poww_timeout_atomic(base + VTD_CNTW, v,
				      FIEWD_GET(VTD_CNTW_EVNT, v) == event,
				      1, PEWF_TIMEOUT)) {
		dev_eww(pwiv->dev, "timeout, unmatched vtd event code in countew wegistew.\n");
		wetuwn 0;
	}

	v = fme_wead_pewf_cntw_weg(base + VTD_CNTW);
	wetuwn FIEWD_GET(VTD_CNTW_EVNT_CNTW, v);
}

static int vtd_sip_event_init(stwuct fme_pewf_pwiv *pwiv, u32 event, u32 powtid)
{
	if (pwiv->id == FME_FEATUWE_ID_GWOBAW_IPEWF &&
	    event <= VTD_SIP_EVNT_MAX && is_powtid_woot(powtid))
		wetuwn 0;

	wetuwn -EINVAW;
}

static u64 vtd_sip_wead_event_countew(stwuct fme_pewf_pwiv *pwiv, u32 event,
				      u32 powtid)
{
	void __iomem *base = pwiv->ioaddw;
	u64 v;

	v = weadq(base + VTD_SIP_CTWW);
	v &= ~VTD_SIP_CTWW_EVNT;
	v |= FIEWD_PWEP(VTD_SIP_CTWW_EVNT, event);
	wwiteq(v, base + VTD_SIP_CTWW);

	if (weadq_poww_timeout_atomic(base + VTD_SIP_CNTW, v,
				      FIEWD_GET(VTD_SIP_CNTW_EVNT, v) == event,
				      1, PEWF_TIMEOUT)) {
		dev_eww(pwiv->dev, "timeout, unmatched vtd sip event code in countew wegistew\n");
		wetuwn 0;
	}

	v = fme_wead_pewf_cntw_weg(base + VTD_SIP_CNTW);
	wetuwn FIEWD_GET(VTD_SIP_CNTW_EVNT_CNTW, v);
}

static stwuct fme_pewf_event_ops fme_pewf_event_ops[] = {
	[FME_EVTYPE_BASIC]	= {.event_init = basic_event_init,
				   .wead_countew = basic_wead_event_countew,},
	[FME_EVTYPE_CACHE]	= {.event_init = cache_event_init,
				   .wead_countew = cache_wead_event_countew,},
	[FME_EVTYPE_FABWIC]	= {.event_init = fabwic_event_init,
				   .event_destwoy = fabwic_event_destwoy,
				   .wead_countew = fabwic_wead_event_countew,},
	[FME_EVTYPE_VTD]	= {.event_init = vtd_event_init,
				   .wead_countew = vtd_wead_event_countew,},
	[FME_EVTYPE_VTD_SIP]	= {.event_init = vtd_sip_event_init,
				   .wead_countew = vtd_sip_wead_event_countew,},
};

static ssize_t fme_pewf_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;
	unsigned wong config;
	chaw *ptw = buf;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	config = (unsigned wong)eattw->vaw;

	ptw += spwintf(ptw, "event=0x%02x", (unsigned int)get_event(config));
	ptw += spwintf(ptw, ",evtype=0x%02x", (unsigned int)get_evtype(config));

	if (is_powtid_woot(get_powtid(config)))
		ptw += spwintf(ptw, ",powtid=0x%02x\n", FME_POWTID_WOOT);
	ewse
		ptw += spwintf(ptw, ",powtid=?\n");

	wetuwn (ssize_t)(ptw - buf);
}

#define FME_EVENT_ATTW(_name) \
	__ATTW(_name, 0444, fme_pewf_event_show, NUWW)

#define FME_POWT_EVENT_CONFIG(_event, _type)				\
	(void *)((((_event) << FME_EVENT_SHIFT) & FME_EVENT_MASK) |	\
		(((_type) << FME_EVTYPE_SHIFT) & FME_EVTYPE_MASK))

#define FME_EVENT_CONFIG(_event, _type)					\
	(void *)((((_event) << FME_EVENT_SHIFT) & FME_EVENT_MASK) |	\
		(((_type) << FME_EVTYPE_SHIFT) & FME_EVTYPE_MASK) |	\
		(FME_POWTID_WOOT << FME_POWTID_SHIFT))

/* FME Pewf Basic Events */
#define FME_EVENT_BASIC(_name, _event)					\
static stwuct dev_ext_attwibute fme_pewf_event_##_name = {		\
	.attw = FME_EVENT_ATTW(_name),					\
	.vaw = FME_EVENT_CONFIG(_event, FME_EVTYPE_BASIC),		\
}

FME_EVENT_BASIC(cwock, BASIC_EVNT_CWK);

static stwuct attwibute *fme_pewf_basic_events_attws[] = {
	&fme_pewf_event_cwock.attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_basic_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_basic_events_attws,
};

/* FME Pewf Cache Events */
#define FME_EVENT_CACHE(_name, _event)					\
static stwuct dev_ext_attwibute fme_pewf_event_cache_##_name = {	\
	.attw = FME_EVENT_ATTW(cache_##_name),				\
	.vaw = FME_EVENT_CONFIG(_event, FME_EVTYPE_CACHE),		\
}

FME_EVENT_CACHE(wead_hit,     CACHE_EVNT_WD_HIT);
FME_EVENT_CACHE(wead_miss,    CACHE_EVNT_WD_MISS);
FME_EVENT_CACHE(wwite_hit,    CACHE_EVNT_WW_HIT);
FME_EVENT_CACHE(wwite_miss,   CACHE_EVNT_WW_MISS);
FME_EVENT_CACHE(howd_wequest, CACHE_EVNT_HOWD_WEQ);
FME_EVENT_CACHE(tx_weq_staww, CACHE_EVNT_TX_WEQ_STAWW);
FME_EVENT_CACHE(wx_weq_staww, CACHE_EVNT_WX_WEQ_STAWW);
FME_EVENT_CACHE(eviction,     CACHE_EVNT_EVICTIONS);
FME_EVENT_CACHE(data_wwite_powt_contention, CACHE_EVNT_DATA_WW_POWT_CONTEN);
FME_EVENT_CACHE(tag_wwite_powt_contention,  CACHE_EVNT_TAG_WW_POWT_CONTEN);

static stwuct attwibute *fme_pewf_cache_events_attws[] = {
	&fme_pewf_event_cache_wead_hit.attw.attw,
	&fme_pewf_event_cache_wead_miss.attw.attw,
	&fme_pewf_event_cache_wwite_hit.attw.attw,
	&fme_pewf_event_cache_wwite_miss.attw.attw,
	&fme_pewf_event_cache_howd_wequest.attw.attw,
	&fme_pewf_event_cache_tx_weq_staww.attw.attw,
	&fme_pewf_event_cache_wx_weq_staww.attw.attw,
	&fme_pewf_event_cache_eviction.attw.attw,
	&fme_pewf_event_cache_data_wwite_powt_contention.attw.attw,
	&fme_pewf_event_cache_tag_wwite_powt_contention.attw.attw,
	NUWW,
};

static umode_t fme_pewf_events_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct pmu *pmu = dev_get_dwvdata(kobj_to_dev(kobj));
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(pmu);

	wetuwn (pwiv->id == FME_FEATUWE_ID_GWOBAW_IPEWF) ? attw->mode : 0;
}

static const stwuct attwibute_gwoup fme_pewf_cache_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_cache_events_attws,
	.is_visibwe = fme_pewf_events_visibwe,
};

/* FME Pewf Fabwic Events */
#define FME_EVENT_FABWIC(_name, _event)					\
static stwuct dev_ext_attwibute fme_pewf_event_fab_##_name = {		\
	.attw = FME_EVENT_ATTW(fab_##_name),				\
	.vaw = FME_EVENT_CONFIG(_event, FME_EVTYPE_FABWIC),		\
}

#define FME_EVENT_FABWIC_POWT(_name, _event)				\
static stwuct dev_ext_attwibute fme_pewf_event_fab_powt_##_name = {	\
	.attw = FME_EVENT_ATTW(fab_powt_##_name),			\
	.vaw = FME_POWT_EVENT_CONFIG(_event, FME_EVTYPE_FABWIC),	\
}

FME_EVENT_FABWIC(pcie0_wead,  FAB_EVNT_PCIE0_WD);
FME_EVENT_FABWIC(pcie0_wwite, FAB_EVNT_PCIE0_WW);
FME_EVENT_FABWIC(pcie1_wead,  FAB_EVNT_PCIE1_WD);
FME_EVENT_FABWIC(pcie1_wwite, FAB_EVNT_PCIE1_WW);
FME_EVENT_FABWIC(upi_wead,    FAB_EVNT_UPI_WD);
FME_EVENT_FABWIC(upi_wwite,   FAB_EVNT_UPI_WW);
FME_EVENT_FABWIC(mmio_wead,   FAB_EVNT_MMIO_WD);
FME_EVENT_FABWIC(mmio_wwite,  FAB_EVNT_MMIO_WW);

FME_EVENT_FABWIC_POWT(pcie0_wead,  FAB_EVNT_PCIE0_WD);
FME_EVENT_FABWIC_POWT(pcie0_wwite, FAB_EVNT_PCIE0_WW);
FME_EVENT_FABWIC_POWT(pcie1_wead,  FAB_EVNT_PCIE1_WD);
FME_EVENT_FABWIC_POWT(pcie1_wwite, FAB_EVNT_PCIE1_WW);
FME_EVENT_FABWIC_POWT(upi_wead,    FAB_EVNT_UPI_WD);
FME_EVENT_FABWIC_POWT(upi_wwite,   FAB_EVNT_UPI_WW);
FME_EVENT_FABWIC_POWT(mmio_wead,   FAB_EVNT_MMIO_WD);
FME_EVENT_FABWIC_POWT(mmio_wwite,  FAB_EVNT_MMIO_WW);

static stwuct attwibute *fme_pewf_fabwic_events_attws[] = {
	&fme_pewf_event_fab_pcie0_wead.attw.attw,
	&fme_pewf_event_fab_pcie0_wwite.attw.attw,
	&fme_pewf_event_fab_pcie1_wead.attw.attw,
	&fme_pewf_event_fab_pcie1_wwite.attw.attw,
	&fme_pewf_event_fab_upi_wead.attw.attw,
	&fme_pewf_event_fab_upi_wwite.attw.attw,
	&fme_pewf_event_fab_mmio_wead.attw.attw,
	&fme_pewf_event_fab_mmio_wwite.attw.attw,
	&fme_pewf_event_fab_powt_pcie0_wead.attw.attw,
	&fme_pewf_event_fab_powt_pcie0_wwite.attw.attw,
	&fme_pewf_event_fab_powt_pcie1_wead.attw.attw,
	&fme_pewf_event_fab_powt_pcie1_wwite.attw.attw,
	&fme_pewf_event_fab_powt_upi_wead.attw.attw,
	&fme_pewf_event_fab_powt_upi_wwite.attw.attw,
	&fme_pewf_event_fab_powt_mmio_wead.attw.attw,
	&fme_pewf_event_fab_powt_mmio_wwite.attw.attw,
	NUWW,
};

static umode_t fme_pewf_fabwic_events_visibwe(stwuct kobject *kobj,
					      stwuct attwibute *attw, int n)
{
	stwuct pmu *pmu = dev_get_dwvdata(kobj_to_dev(kobj));
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(pmu);
	stwuct dev_ext_attwibute *eattw;
	unsigned wong vaw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw.attw);
	vaw = (unsigned wong)eattw->vaw;

	if (is_fabwic_event_suppowted(pwiv, get_event(vaw), get_powtid(vaw)))
		wetuwn attw->mode;

	wetuwn 0;
}

static const stwuct attwibute_gwoup fme_pewf_fabwic_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_fabwic_events_attws,
	.is_visibwe = fme_pewf_fabwic_events_visibwe,
};

/* FME Pewf VTD Events */
#define FME_EVENT_VTD_POWT(_name, _event)				\
static stwuct dev_ext_attwibute fme_pewf_event_vtd_powt_##_name = {	\
	.attw = FME_EVENT_ATTW(vtd_powt_##_name),			\
	.vaw = FME_POWT_EVENT_CONFIG(_event, FME_EVTYPE_VTD),		\
}

FME_EVENT_VTD_POWT(wead_twansaction,  VTD_EVNT_AFU_MEM_WD_TWANS);
FME_EVENT_VTD_POWT(wwite_twansaction, VTD_EVNT_AFU_MEM_WW_TWANS);
FME_EVENT_VTD_POWT(devtwb_wead_hit,   VTD_EVNT_AFU_DEVTWB_WD_HIT);
FME_EVENT_VTD_POWT(devtwb_wwite_hit,  VTD_EVNT_AFU_DEVTWB_WW_HIT);
FME_EVENT_VTD_POWT(devtwb_4k_fiww,    VTD_EVNT_DEVTWB_4K_FIWW);
FME_EVENT_VTD_POWT(devtwb_2m_fiww,    VTD_EVNT_DEVTWB_2M_FIWW);
FME_EVENT_VTD_POWT(devtwb_1g_fiww,    VTD_EVNT_DEVTWB_1G_FIWW);

static stwuct attwibute *fme_pewf_vtd_events_attws[] = {
	&fme_pewf_event_vtd_powt_wead_twansaction.attw.attw,
	&fme_pewf_event_vtd_powt_wwite_twansaction.attw.attw,
	&fme_pewf_event_vtd_powt_devtwb_wead_hit.attw.attw,
	&fme_pewf_event_vtd_powt_devtwb_wwite_hit.attw.attw,
	&fme_pewf_event_vtd_powt_devtwb_4k_fiww.attw.attw,
	&fme_pewf_event_vtd_powt_devtwb_2m_fiww.attw.attw,
	&fme_pewf_event_vtd_powt_devtwb_1g_fiww.attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_vtd_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_vtd_events_attws,
	.is_visibwe = fme_pewf_events_visibwe,
};

/* FME Pewf VTD SIP Events */
#define FME_EVENT_VTD_SIP(_name, _event)				\
static stwuct dev_ext_attwibute fme_pewf_event_vtd_sip_##_name = {	\
	.attw = FME_EVENT_ATTW(vtd_sip_##_name),			\
	.vaw = FME_EVENT_CONFIG(_event, FME_EVTYPE_VTD_SIP),		\
}

FME_EVENT_VTD_SIP(iotwb_4k_hit,  VTD_SIP_EVNT_IOTWB_4K_HIT);
FME_EVENT_VTD_SIP(iotwb_2m_hit,  VTD_SIP_EVNT_IOTWB_2M_HIT);
FME_EVENT_VTD_SIP(iotwb_1g_hit,  VTD_SIP_EVNT_IOTWB_1G_HIT);
FME_EVENT_VTD_SIP(swpwc_w3_hit,  VTD_SIP_EVNT_SWPWC_W3_HIT);
FME_EVENT_VTD_SIP(swpwc_w4_hit,  VTD_SIP_EVNT_SWPWC_W4_HIT);
FME_EVENT_VTD_SIP(wcc_hit,       VTD_SIP_EVNT_WCC_HIT);
FME_EVENT_VTD_SIP(iotwb_4k_miss, VTD_SIP_EVNT_IOTWB_4K_MISS);
FME_EVENT_VTD_SIP(iotwb_2m_miss, VTD_SIP_EVNT_IOTWB_2M_MISS);
FME_EVENT_VTD_SIP(iotwb_1g_miss, VTD_SIP_EVNT_IOTWB_1G_MISS);
FME_EVENT_VTD_SIP(swpwc_w3_miss, VTD_SIP_EVNT_SWPWC_W3_MISS);
FME_EVENT_VTD_SIP(swpwc_w4_miss, VTD_SIP_EVNT_SWPWC_W4_MISS);
FME_EVENT_VTD_SIP(wcc_miss,      VTD_SIP_EVNT_WCC_MISS);

static stwuct attwibute *fme_pewf_vtd_sip_events_attws[] = {
	&fme_pewf_event_vtd_sip_iotwb_4k_hit.attw.attw,
	&fme_pewf_event_vtd_sip_iotwb_2m_hit.attw.attw,
	&fme_pewf_event_vtd_sip_iotwb_1g_hit.attw.attw,
	&fme_pewf_event_vtd_sip_swpwc_w3_hit.attw.attw,
	&fme_pewf_event_vtd_sip_swpwc_w4_hit.attw.attw,
	&fme_pewf_event_vtd_sip_wcc_hit.attw.attw,
	&fme_pewf_event_vtd_sip_iotwb_4k_miss.attw.attw,
	&fme_pewf_event_vtd_sip_iotwb_2m_miss.attw.attw,
	&fme_pewf_event_vtd_sip_iotwb_1g_miss.attw.attw,
	&fme_pewf_event_vtd_sip_swpwc_w3_miss.attw.attw,
	&fme_pewf_event_vtd_sip_swpwc_w4_miss.attw.attw,
	&fme_pewf_event_vtd_sip_wcc_miss.attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fme_pewf_vtd_sip_events_gwoup = {
	.name = "events",
	.attws = fme_pewf_vtd_sip_events_attws,
	.is_visibwe = fme_pewf_events_visibwe,
};

static const stwuct attwibute_gwoup *fme_pewf_events_gwoups[] = {
	&fme_pewf_basic_events_gwoup,
	&fme_pewf_cache_events_gwoup,
	&fme_pewf_fabwic_events_gwoup,
	&fme_pewf_vtd_events_gwoup,
	&fme_pewf_vtd_sip_events_gwoup,
	NUWW,
};

static stwuct fme_pewf_event_ops *get_event_ops(u32 evtype)
{
	if (evtype > FME_EVTYPE_MAX)
		wetuwn NUWW;

	wetuwn &fme_pewf_event_ops[evtype];
}

static void fme_pewf_event_destwoy(stwuct pewf_event *event)
{
	stwuct fme_pewf_event_ops *ops = get_event_ops(event->hw.event_base);
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(event->pmu);

	if (ops->event_destwoy)
		ops->event_destwoy(pwiv, event->hw.idx, event->hw.config_base);
}

static int fme_pewf_event_init(stwuct pewf_event *event)
{
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct fme_pewf_event_ops *ops;
	u32 eventid, evtype, powtid;

	/* test the event attw type check fow PMU enumewation */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * fme countews awe shawed acwoss aww cowes.
	 * Thewefowe, it does not suppowt pew-pwocess mode.
	 * Awso, it does not suppowt event sampwing mode.
	 */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	if (event->cpu != pwiv->cpu)
		wetuwn -EINVAW;

	eventid = get_event(event->attw.config);
	powtid = get_powtid(event->attw.config);
	evtype = get_evtype(event->attw.config);
	if (evtype > FME_EVTYPE_MAX)
		wetuwn -EINVAW;

	hwc->event_base = evtype;
	hwc->idx = (int)eventid;
	hwc->config_base = powtid;

	event->destwoy = fme_pewf_event_destwoy;

	dev_dbg(pwiv->dev, "%s event=0x%x, evtype=0x%x, powtid=0x%x,\n",
		__func__, eventid, evtype, powtid);

	ops = get_event_ops(evtype);
	if (ops->event_init)
		wetuwn ops->event_init(pwiv, eventid, powtid);

	wetuwn 0;
}

static void fme_pewf_event_update(stwuct pewf_event *event)
{
	stwuct fme_pewf_event_ops *ops = get_event_ops(event->hw.event_base);
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 now, pwev, dewta;

	now = ops->wead_countew(pwiv, (u32)hwc->idx, hwc->config_base);
	pwev = wocaw64_wead(&hwc->pwev_count);
	dewta = now - pwev;

	wocaw64_add(dewta, &event->count);
}

static void fme_pewf_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct fme_pewf_event_ops *ops = get_event_ops(event->hw.event_base);
	stwuct fme_pewf_pwiv *pwiv = to_fme_pewf_pwiv(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 count;

	count = ops->wead_countew(pwiv, (u32)hwc->idx, hwc->config_base);
	wocaw64_set(&hwc->pwev_count, count);
}

static void fme_pewf_event_stop(stwuct pewf_event *event, int fwags)
{
	fme_pewf_event_update(event);
}

static int fme_pewf_event_add(stwuct pewf_event *event, int fwags)
{
	if (fwags & PEWF_EF_STAWT)
		fme_pewf_event_stawt(event, fwags);

	wetuwn 0;
}

static void fme_pewf_event_dew(stwuct pewf_event *event, int fwags)
{
	fme_pewf_event_stop(event, PEWF_EF_UPDATE);
}

static void fme_pewf_event_wead(stwuct pewf_event *event)
{
	fme_pewf_event_update(event);
}

static void fme_pewf_setup_hawdwawe(stwuct fme_pewf_pwiv *pwiv)
{
	void __iomem *base = pwiv->ioaddw;
	u64 v;

	/* wead and save cuwwent wowking mode fow fabwic countews */
	v = weadq(base + FAB_CTWW);

	if (FIEWD_GET(FAB_POWT_FIWTEW, v) == FAB_POWT_FIWTEW_DISABWE)
		pwiv->fab_powt_id = FME_POWTID_WOOT;
	ewse
		pwiv->fab_powt_id = FIEWD_GET(FAB_POWT_ID, v);
}

static int fme_pewf_pmu_wegistew(stwuct pwatfowm_device *pdev,
				 stwuct fme_pewf_pwiv *pwiv)
{
	stwuct pmu *pmu = &pwiv->pmu;
	chaw *name;
	int wet;

	spin_wock_init(&pwiv->fab_wock);

	fme_pewf_setup_hawdwawe(pwiv);

	pmu->task_ctx_nw =	pewf_invawid_context;
	pmu->attw_gwoups =	fme_pewf_gwoups;
	pmu->attw_update =	fme_pewf_events_gwoups;
	pmu->event_init =	fme_pewf_event_init;
	pmu->add =		fme_pewf_event_add;
	pmu->dew =		fme_pewf_event_dew;
	pmu->stawt =		fme_pewf_event_stawt;
	pmu->stop =		fme_pewf_event_stop;
	pmu->wead =		fme_pewf_event_wead;
	pmu->capabiwities =	PEWF_PMU_CAP_NO_INTEWWUPT |
				PEWF_PMU_CAP_NO_EXCWUDE;

	name = devm_kaspwintf(pwiv->dev, GFP_KEWNEW, "dfw_fme%d", pdev->id);

	wet = pewf_pmu_wegistew(pmu, name, -1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void fme_pewf_pmu_unwegistew(stwuct fme_pewf_pwiv *pwiv)
{
	pewf_pmu_unwegistew(&pwiv->pmu);
}

static int fme_pewf_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct fme_pewf_pwiv *pwiv;
	int tawget;

	pwiv = hwist_entwy_safe(node, stwuct fme_pewf_pwiv, node);

	if (cpu != pwiv->cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pwiv->cpu = tawget;
	pewf_pmu_migwate_context(&pwiv->pmu, cpu, tawget);

	wetuwn 0;
}

static int fme_pewf_init(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe)
{
	stwuct fme_pewf_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->ioaddw = featuwe->ioaddw;
	pwiv->id = featuwe->id;
	pwiv->cpu = waw_smp_pwocessow_id();

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/fpga/dfw_fme:onwine",
				      NUWW, fme_pewf_offwine_cpu);
	if (wet < 0)
		wetuwn wet;

	pwiv->cpuhp_state = wet;

	/* Wegistew the pmu instance fow cpu hotpwug */
	wet = cpuhp_state_add_instance_nocawws(pwiv->cpuhp_state, &pwiv->node);
	if (wet)
		goto cpuhp_instance_eww;

	wet = fme_pewf_pmu_wegistew(pdev, pwiv);
	if (wet)
		goto pmu_wegistew_eww;

	featuwe->pwiv = pwiv;
	wetuwn 0;

pmu_wegistew_eww:
	cpuhp_state_wemove_instance_nocawws(pwiv->cpuhp_state, &pwiv->node);
cpuhp_instance_eww:
	cpuhp_wemove_muwti_state(pwiv->cpuhp_state);
	wetuwn wet;
}

static void fme_pewf_uinit(stwuct pwatfowm_device *pdev,
			   stwuct dfw_featuwe *featuwe)
{
	stwuct fme_pewf_pwiv *pwiv = featuwe->pwiv;

	fme_pewf_pmu_unwegistew(pwiv);
	cpuhp_state_wemove_instance_nocawws(pwiv->cpuhp_state, &pwiv->node);
	cpuhp_wemove_muwti_state(pwiv->cpuhp_state);
}

const stwuct dfw_featuwe_id fme_pewf_id_tabwe[] = {
	{.id = FME_FEATUWE_ID_GWOBAW_IPEWF,},
	{.id = FME_FEATUWE_ID_GWOBAW_DPEWF,},
	{0,}
};

const stwuct dfw_featuwe_ops fme_pewf_ops = {
	.init = fme_pewf_init,
	.uinit = fme_pewf_uinit,
};

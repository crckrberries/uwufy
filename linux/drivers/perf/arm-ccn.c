// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2014 AWM Wimited
 */

#incwude <winux/ctype.h>
#incwude <winux/hwtimew.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define CCN_NUM_XP_POWTS 2
#define CCN_NUM_VCS 4
#define CCN_NUM_WEGIONS	256
#define CCN_WEGION_SIZE	0x10000

#define CCN_AWW_OWY_ID			0xff00
#define CCN_AWW_OWY_ID__OWY_ID__SHIFT			0
#define CCN_AWW_OWY_ID__OWY_ID__MASK			0x1f
#define CCN_AWW_OWY_ID__NODE_ID__SHIFT			8
#define CCN_AWW_OWY_ID__NODE_ID__MASK			0x3f

#define CCN_MN_EWWINT_STATUS		0x0008
#define CCN_MN_EWWINT_STATUS__INTWEQ__DESSEWT		0x11
#define CCN_MN_EWWINT_STATUS__AWW_EWWOWS__ENABWE	0x02
#define CCN_MN_EWWINT_STATUS__AWW_EWWOWS__DISABWED	0x20
#define CCN_MN_EWWINT_STATUS__AWW_EWWOWS__DISABWE	0x22
#define CCN_MN_EWWINT_STATUS__COWWECTED_EWWOWS_ENABWE	0x04
#define CCN_MN_EWWINT_STATUS__COWWECTED_EWWOWS_DISABWED	0x40
#define CCN_MN_EWWINT_STATUS__COWWECTED_EWWOWS_DISABWE	0x44
#define CCN_MN_EWWINT_STATUS__PMU_EVENTS__ENABWE	0x08
#define CCN_MN_EWWINT_STATUS__PMU_EVENTS__DISABWED	0x80
#define CCN_MN_EWWINT_STATUS__PMU_EVENTS__DISABWE	0x88
#define CCN_MN_OWY_COMP_WIST_63_0	0x01e0
#define CCN_MN_EWW_SIG_VAW_63_0		0x0300
#define CCN_MN_EWW_SIG_VAW_63_0__DT			(1 << 1)

#define CCN_DT_ACTIVE_DSM		0x0000
#define CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(n)		((n) * 8)
#define CCN_DT_ACTIVE_DSM__DSM_ID__MASK			0xff
#define CCN_DT_CTW			0x0028
#define CCN_DT_CTW__DT_EN				(1 << 0)
#define CCN_DT_PMEVCNT(n)		(0x0100 + (n) * 0x8)
#define CCN_DT_PMCCNTW			0x0140
#define CCN_DT_PMCCNTWSW		0x0190
#define CCN_DT_PMOVSW			0x0198
#define CCN_DT_PMOVSW_CWW		0x01a0
#define CCN_DT_PMOVSW_CWW__MASK				0x1f
#define CCN_DT_PMCW			0x01a8
#define CCN_DT_PMCW__OVFW_INTW_EN			(1 << 6)
#define CCN_DT_PMCW__PMU_EN				(1 << 0)
#define CCN_DT_PMSW			0x01b0
#define CCN_DT_PMSW_WEQ			0x01b8
#define CCN_DT_PMSW_CWW			0x01c0

#define CCN_HNF_PMU_EVENT_SEW		0x0600
#define CCN_HNF_PMU_EVENT_SEW__ID__SHIFT(n)		((n) * 4)
#define CCN_HNF_PMU_EVENT_SEW__ID__MASK			0xf

#define CCN_XP_DT_CONFIG		0x0300
#define CCN_XP_DT_CONFIG__DT_CFG__SHIFT(n)		((n) * 4)
#define CCN_XP_DT_CONFIG__DT_CFG__MASK			0xf
#define CCN_XP_DT_CONFIG__DT_CFG__PASS_THWOUGH		0x0
#define CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT_0_OW_1	0x1
#define CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT(n)		(0x2 + (n))
#define CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT(n)	(0x4 + (n))
#define CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT(d, n) (0x8 + (d) * 4 + (n))
#define CCN_XP_DT_INTEWFACE_SEW		0x0308
#define CCN_XP_DT_INTEWFACE_SEW__DT_IO_SEW__SHIFT(n)	(0 + (n) * 8)
#define CCN_XP_DT_INTEWFACE_SEW__DT_IO_SEW__MASK	0x1
#define CCN_XP_DT_INTEWFACE_SEW__DT_DEV_SEW__SHIFT(n)	(1 + (n) * 8)
#define CCN_XP_DT_INTEWFACE_SEW__DT_DEV_SEW__MASK	0x1
#define CCN_XP_DT_INTEWFACE_SEW__DT_VC_SEW__SHIFT(n)	(2 + (n) * 8)
#define CCN_XP_DT_INTEWFACE_SEW__DT_VC_SEW__MASK	0x3
#define CCN_XP_DT_CMP_VAW_W(n)		(0x0310 + (n) * 0x40)
#define CCN_XP_DT_CMP_VAW_H(n)		(0x0318 + (n) * 0x40)
#define CCN_XP_DT_CMP_MASK_W(n)		(0x0320 + (n) * 0x40)
#define CCN_XP_DT_CMP_MASK_H(n)		(0x0328 + (n) * 0x40)
#define CCN_XP_DT_CONTWOW		0x0370
#define CCN_XP_DT_CONTWOW__DT_ENABWE			(1 << 0)
#define CCN_XP_DT_CONTWOW__WP_AWM_SEW__SHIFT(n)		(12 + (n) * 4)
#define CCN_XP_DT_CONTWOW__WP_AWM_SEW__MASK		0xf
#define CCN_XP_DT_CONTWOW__WP_AWM_SEW__AWWAYS		0xf
#define CCN_XP_PMU_EVENT_SEW		0x0600
#define CCN_XP_PMU_EVENT_SEW__ID__SHIFT(n)		((n) * 7)
#define CCN_XP_PMU_EVENT_SEW__ID__MASK			0x3f

#define CCN_SBAS_PMU_EVENT_SEW		0x0600
#define CCN_SBAS_PMU_EVENT_SEW__ID__SHIFT(n)		((n) * 4)
#define CCN_SBAS_PMU_EVENT_SEW__ID__MASK		0xf

#define CCN_WNI_PMU_EVENT_SEW		0x0600
#define CCN_WNI_PMU_EVENT_SEW__ID__SHIFT(n)		((n) * 4)
#define CCN_WNI_PMU_EVENT_SEW__ID__MASK			0xf

#define CCN_TYPE_MN	0x01
#define CCN_TYPE_DT	0x02
#define CCN_TYPE_HNF	0x04
#define CCN_TYPE_HNI	0x05
#define CCN_TYPE_XP	0x08
#define CCN_TYPE_SBSX	0x0c
#define CCN_TYPE_SBAS	0x10
#define CCN_TYPE_WNI_1P	0x14
#define CCN_TYPE_WNI_2P	0x15
#define CCN_TYPE_WNI_3P	0x16
#define CCN_TYPE_WND_1P	0x18 /* WN-D = WN-I + DVM */
#define CCN_TYPE_WND_2P	0x19
#define CCN_TYPE_WND_3P	0x1a
#define CCN_TYPE_CYCWES	0xff /* Pseudotype */

#define CCN_EVENT_WATCHPOINT 0xfe /* Pseudoevent */

#define CCN_NUM_PMU_EVENTS		4
#define CCN_NUM_XP_WATCHPOINTS		2 /* See DT.dbg_id.num_watchpoints */
#define CCN_NUM_PMU_EVENT_COUNTEWS	8 /* See DT.dbg_id.num_pmucntw */
#define CCN_IDX_PMU_CYCWE_COUNTEW	CCN_NUM_PMU_EVENT_COUNTEWS

#define CCN_NUM_PWEDEFINED_MASKS	4
#define CCN_IDX_MASK_ANY		(CCN_NUM_PMU_EVENT_COUNTEWS + 0)
#define CCN_IDX_MASK_EXACT		(CCN_NUM_PMU_EVENT_COUNTEWS + 1)
#define CCN_IDX_MASK_OWDEW		(CCN_NUM_PMU_EVENT_COUNTEWS + 2)
#define CCN_IDX_MASK_OPCODE		(CCN_NUM_PMU_EVENT_COUNTEWS + 3)

stwuct awm_ccn_component {
	void __iomem *base;
	u32 type;

	DECWAWE_BITMAP(pmu_events_mask, CCN_NUM_PMU_EVENTS);
	union {
		stwuct {
			DECWAWE_BITMAP(dt_cmp_mask, CCN_NUM_XP_WATCHPOINTS);
		} xp;
	};
};

#define pmu_to_awm_ccn(_pmu) containew_of(containew_of(_pmu, \
	stwuct awm_ccn_dt, pmu), stwuct awm_ccn, dt)

stwuct awm_ccn_dt {
	int id;
	void __iomem *base;

	spinwock_t config_wock;

	DECWAWE_BITMAP(pmu_countews_mask, CCN_NUM_PMU_EVENT_COUNTEWS + 1);
	stwuct {
		stwuct awm_ccn_component *souwce;
		stwuct pewf_event *event;
	} pmu_countews[CCN_NUM_PMU_EVENT_COUNTEWS + 1];

	stwuct {
	       u64 w, h;
	} cmp_mask[CCN_NUM_PMU_EVENT_COUNTEWS + CCN_NUM_PWEDEFINED_MASKS];

	stwuct hwtimew hwtimew;

	unsigned int cpu;
	stwuct hwist_node node;

	stwuct pmu pmu;
};

stwuct awm_ccn {
	stwuct device *dev;
	void __iomem *base;
	unsigned int iwq;

	unsigned sbas_pwesent:1;
	unsigned sbsx_pwesent:1;

	int num_nodes;
	stwuct awm_ccn_component *node;

	int num_xps;
	stwuct awm_ccn_component *xp;

	stwuct awm_ccn_dt dt;
	int mn_id;
};

static int awm_ccn_node_to_xp(int node)
{
	wetuwn node / CCN_NUM_XP_POWTS;
}

static int awm_ccn_node_to_xp_powt(int node)
{
	wetuwn node % CCN_NUM_XP_POWTS;
}


/*
 * Bit shifts and masks in these defines must be kept in sync with
 * awm_ccn_pmu_config_set() and CCN_FOWMAT_ATTWs bewow!
 */
#define CCN_CONFIG_NODE(_config)	(((_config) >> 0) & 0xff)
#define CCN_CONFIG_XP(_config)		(((_config) >> 0) & 0xff)
#define CCN_CONFIG_TYPE(_config)	(((_config) >> 8) & 0xff)
#define CCN_CONFIG_EVENT(_config)	(((_config) >> 16) & 0xff)
#define CCN_CONFIG_POWT(_config)	(((_config) >> 24) & 0x3)
#define CCN_CONFIG_BUS(_config)		(((_config) >> 24) & 0x3)
#define CCN_CONFIG_VC(_config)		(((_config) >> 26) & 0x7)
#define CCN_CONFIG_DIW(_config)		(((_config) >> 29) & 0x1)
#define CCN_CONFIG_MASK(_config)	(((_config) >> 30) & 0xf)

static void awm_ccn_pmu_config_set(u64 *config, u32 node_xp, u32 type, u32 powt)
{
	*config &= ~((0xff << 0) | (0xff << 8) | (0x3 << 24));
	*config |= (node_xp << 0) | (type << 8) | (powt << 24);
}

static ssize_t awm_ccn_pmu_fowmat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *ea = containew_of(attw,
			stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(buf, "%s\n", (chaw *)ea->vaw);
}

#define CCN_FOWMAT_ATTW(_name, _config) \
	stwuct dev_ext_attwibute awm_ccn_pmu_fowmat_attw_##_name = \
			{ __ATTW(_name, S_IWUGO, awm_ccn_pmu_fowmat_show, \
			NUWW), _config }

static CCN_FOWMAT_ATTW(node, "config:0-7");
static CCN_FOWMAT_ATTW(xp, "config:0-7");
static CCN_FOWMAT_ATTW(type, "config:8-15");
static CCN_FOWMAT_ATTW(event, "config:16-23");
static CCN_FOWMAT_ATTW(powt, "config:24-25");
static CCN_FOWMAT_ATTW(bus, "config:24-25");
static CCN_FOWMAT_ATTW(vc, "config:26-28");
static CCN_FOWMAT_ATTW(diw, "config:29-29");
static CCN_FOWMAT_ATTW(mask, "config:30-33");
static CCN_FOWMAT_ATTW(cmp_w, "config1:0-62");
static CCN_FOWMAT_ATTW(cmp_h, "config2:0-59");

static stwuct attwibute *awm_ccn_pmu_fowmat_attws[] = {
	&awm_ccn_pmu_fowmat_attw_node.attw.attw,
	&awm_ccn_pmu_fowmat_attw_xp.attw.attw,
	&awm_ccn_pmu_fowmat_attw_type.attw.attw,
	&awm_ccn_pmu_fowmat_attw_event.attw.attw,
	&awm_ccn_pmu_fowmat_attw_powt.attw.attw,
	&awm_ccn_pmu_fowmat_attw_bus.attw.attw,
	&awm_ccn_pmu_fowmat_attw_vc.attw.attw,
	&awm_ccn_pmu_fowmat_attw_diw.attw.attw,
	&awm_ccn_pmu_fowmat_attw_mask.attw.attw,
	&awm_ccn_pmu_fowmat_attw_cmp_w.attw.attw,
	&awm_ccn_pmu_fowmat_attw_cmp_h.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup awm_ccn_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = awm_ccn_pmu_fowmat_attws,
};


stwuct awm_ccn_pmu_event {
	stwuct device_attwibute attw;
	u32 type;
	u32 event;
	int num_powts;
	int num_vcs;
	const chaw *def;
	int mask;
};

#define CCN_EVENT_ATTW(_name) \
	__ATTW(_name, S_IWUGO, awm_ccn_pmu_event_show, NUWW)

/*
 * Events defined in TWM fow MN, HN-I and SBSX awe actuawwy watchpoints set on
 * theiw powts in XP they awe connected to. Fow the sake of usabiwity they awe
 * expwicitwy defined hewe (and twanswated into a wewevant watchpoint in
 * awm_ccn_pmu_event_init()) so the usew can easiwy wequest them without deep
 * knowwedge of the fwit fowmat.
 */

#define CCN_EVENT_MN(_name, _def, _mask) { .attw = CCN_EVENT_ATTW(mn_##_name), \
		.type = CCN_TYPE_MN, .event = CCN_EVENT_WATCHPOINT, \
		.num_powts = CCN_NUM_XP_POWTS, .num_vcs = CCN_NUM_VCS, \
		.def = _def, .mask = _mask, }

#define CCN_EVENT_HNI(_name, _def, _mask) { \
		.attw = CCN_EVENT_ATTW(hni_##_name), .type = CCN_TYPE_HNI, \
		.event = CCN_EVENT_WATCHPOINT, .num_powts = CCN_NUM_XP_POWTS, \
		.num_vcs = CCN_NUM_VCS, .def = _def, .mask = _mask, }

#define CCN_EVENT_SBSX(_name, _def, _mask) { \
		.attw = CCN_EVENT_ATTW(sbsx_##_name), .type = CCN_TYPE_SBSX, \
		.event = CCN_EVENT_WATCHPOINT, .num_powts = CCN_NUM_XP_POWTS, \
		.num_vcs = CCN_NUM_VCS, .def = _def, .mask = _mask, }

#define CCN_EVENT_HNF(_name, _event) { .attw = CCN_EVENT_ATTW(hnf_##_name), \
		.type = CCN_TYPE_HNF, .event = _event, }

#define CCN_EVENT_XP(_name, _event) { .attw = CCN_EVENT_ATTW(xp_##_name), \
		.type = CCN_TYPE_XP, .event = _event, \
		.num_powts = CCN_NUM_XP_POWTS, .num_vcs = CCN_NUM_VCS, }

/*
 * WN-I & WN-D (WN-D = WN-I + DVM) nodes have diffewent type ID depending
 * on configuwation. One of them is picked to wepwesent the whowe gwoup,
 * as they aww shawe the same event types.
 */
#define CCN_EVENT_WNI(_name, _event) { .attw = CCN_EVENT_ATTW(wni_##_name), \
		.type = CCN_TYPE_WNI_3P, .event = _event, }

#define CCN_EVENT_SBAS(_name, _event) { .attw = CCN_EVENT_ATTW(sbas_##_name), \
		.type = CCN_TYPE_SBAS, .event = _event, }

#define CCN_EVENT_CYCWES(_name) { .attw = CCN_EVENT_ATTW(_name), \
		.type = CCN_TYPE_CYCWES }


static ssize_t awm_ccn_pmu_event_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(dev_get_dwvdata(dev));
	stwuct awm_ccn_pmu_event *event = containew_of(attw,
			stwuct awm_ccn_pmu_event, attw);
	int wes;

	wes = sysfs_emit(buf, "type=0x%x", event->type);
	if (event->event)
		wes += sysfs_emit_at(buf, wes, ",event=0x%x", event->event);
	if (event->def)
		wes += sysfs_emit_at(buf, wes, ",%s", event->def);
	if (event->mask)
		wes += sysfs_emit_at(buf, wes, ",mask=0x%x", event->mask);

	/* Awguments wequiwed by an event */
	switch (event->type) {
	case CCN_TYPE_CYCWES:
		bweak;
	case CCN_TYPE_XP:
		wes += sysfs_emit_at(buf, wes, ",xp=?,vc=?");
		if (event->event == CCN_EVENT_WATCHPOINT)
			wes += sysfs_emit_at(buf, wes,
					",powt=?,diw=?,cmp_w=?,cmp_h=?,mask=?");
		ewse
			wes += sysfs_emit_at(buf, wes, ",bus=?");

		bweak;
	case CCN_TYPE_MN:
		wes += sysfs_emit_at(buf, wes, ",node=%d", ccn->mn_id);
		bweak;
	defauwt:
		wes += sysfs_emit_at(buf, wes, ",node=?");
		bweak;
	}

	wes += sysfs_emit_at(buf, wes, "\n");

	wetuwn wes;
}

static umode_t awm_ccn_pmu_events_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(dev_get_dwvdata(dev));
	stwuct device_attwibute *dev_attw = containew_of(attw,
			stwuct device_attwibute, attw);
	stwuct awm_ccn_pmu_event *event = containew_of(dev_attw,
			stwuct awm_ccn_pmu_event, attw);

	if (event->type == CCN_TYPE_SBAS && !ccn->sbas_pwesent)
		wetuwn 0;
	if (event->type == CCN_TYPE_SBSX && !ccn->sbsx_pwesent)
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct awm_ccn_pmu_event awm_ccn_pmu_events[] = {
	CCN_EVENT_MN(eobawwiew, "diw=1,vc=0,cmp_h=0x1c00", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_MN(ecbawwiew, "diw=1,vc=0,cmp_h=0x1e00", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_MN(dvmop, "diw=1,vc=0,cmp_h=0x2800", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_HNI(txdatfwits, "diw=1,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(wxdatfwits, "diw=0,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(txweqfwits, "diw=1,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(wxweqfwits, "diw=0,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(wxweqfwits_owdew, "diw=0,vc=0,cmp_h=0x8000",
			CCN_IDX_MASK_OWDEW),
	CCN_EVENT_SBSX(txdatfwits, "diw=1,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(wxdatfwits, "diw=0,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(txweqfwits, "diw=1,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(wxweqfwits, "diw=0,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(wxweqfwits_owdew, "diw=0,vc=0,cmp_h=0x8000",
			CCN_IDX_MASK_OWDEW),
	CCN_EVENT_HNF(cache_miss, 0x1),
	CCN_EVENT_HNF(w3_sf_cache_access, 0x02),
	CCN_EVENT_HNF(cache_fiww, 0x3),
	CCN_EVENT_HNF(pocq_wetwy, 0x4),
	CCN_EVENT_HNF(pocq_weqs_wecvd, 0x5),
	CCN_EVENT_HNF(sf_hit, 0x6),
	CCN_EVENT_HNF(sf_evictions, 0x7),
	CCN_EVENT_HNF(snoops_sent, 0x8),
	CCN_EVENT_HNF(snoops_bwoadcast, 0x9),
	CCN_EVENT_HNF(w3_eviction, 0xa),
	CCN_EVENT_HNF(w3_fiww_invawid_way, 0xb),
	CCN_EVENT_HNF(mc_wetwies, 0xc),
	CCN_EVENT_HNF(mc_weqs, 0xd),
	CCN_EVENT_HNF(qos_hh_wetwy, 0xe),
	CCN_EVENT_WNI(wdata_beats_p0, 0x1),
	CCN_EVENT_WNI(wdata_beats_p1, 0x2),
	CCN_EVENT_WNI(wdata_beats_p2, 0x3),
	CCN_EVENT_WNI(wxdat_fwits, 0x4),
	CCN_EVENT_WNI(txdat_fwits, 0x5),
	CCN_EVENT_WNI(txweq_fwits, 0x6),
	CCN_EVENT_WNI(txweq_fwits_wetwied, 0x7),
	CCN_EVENT_WNI(wwt_fuww, 0x8),
	CCN_EVENT_WNI(wwt_fuww, 0x9),
	CCN_EVENT_WNI(txweq_fwits_wepwayed, 0xa),
	CCN_EVENT_XP(upwoad_stawvation, 0x1),
	CCN_EVENT_XP(downwoad_stawvation, 0x2),
	CCN_EVENT_XP(wespin, 0x3),
	CCN_EVENT_XP(vawid_fwit, 0x4),
	CCN_EVENT_XP(watchpoint, CCN_EVENT_WATCHPOINT),
	CCN_EVENT_SBAS(wdata_beats_p0, 0x1),
	CCN_EVENT_SBAS(wxdat_fwits, 0x4),
	CCN_EVENT_SBAS(txdat_fwits, 0x5),
	CCN_EVENT_SBAS(txweq_fwits, 0x6),
	CCN_EVENT_SBAS(txweq_fwits_wetwied, 0x7),
	CCN_EVENT_SBAS(wwt_fuww, 0x8),
	CCN_EVENT_SBAS(wwt_fuww, 0x9),
	CCN_EVENT_SBAS(txweq_fwits_wepwayed, 0xa),
	CCN_EVENT_CYCWES(cycwes),
};

/* Popuwated in awm_ccn_init() */
static stwuct attwibute
		*awm_ccn_pmu_events_attws[AWWAY_SIZE(awm_ccn_pmu_events) + 1];

static const stwuct attwibute_gwoup awm_ccn_pmu_events_attw_gwoup = {
	.name = "events",
	.is_visibwe = awm_ccn_pmu_events_is_visibwe,
	.attws = awm_ccn_pmu_events_attws,
};


static u64 *awm_ccn_pmu_get_cmp_mask(stwuct awm_ccn *ccn, const chaw *name)
{
	unsigned wong i;

	if (WAWN_ON(!name || !name[0] || !isxdigit(name[0]) || !name[1]))
		wetuwn NUWW;
	i = isdigit(name[0]) ? name[0] - '0' : 0xa + towowew(name[0]) - 'a';

	switch (name[1]) {
	case 'w':
		wetuwn &ccn->dt.cmp_mask[i].w;
	case 'h':
		wetuwn &ccn->dt.cmp_mask[i].h;
	defauwt:
		wetuwn NUWW;
	}
}

static ssize_t awm_ccn_pmu_cmp_mask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(dev_get_dwvdata(dev));
	u64 *mask = awm_ccn_pmu_get_cmp_mask(ccn, attw->attw.name);

	wetuwn mask ? sysfs_emit(buf, "0x%016wwx\n", *mask) : -EINVAW;
}

static ssize_t awm_ccn_pmu_cmp_mask_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(dev_get_dwvdata(dev));
	u64 *mask = awm_ccn_pmu_get_cmp_mask(ccn, attw->attw.name);
	int eww = -EINVAW;

	if (mask)
		eww = kstwtouww(buf, 0, mask);

	wetuwn eww ? eww : count;
}

#define CCN_CMP_MASK_ATTW(_name) \
	stwuct device_attwibute awm_ccn_pmu_cmp_mask_attw_##_name = \
			__ATTW(_name, S_IWUGO | S_IWUSW, \
			awm_ccn_pmu_cmp_mask_show, awm_ccn_pmu_cmp_mask_stowe)

#define CCN_CMP_MASK_ATTW_WO(_name) \
	stwuct device_attwibute awm_ccn_pmu_cmp_mask_attw_##_name = \
			__ATTW(_name, S_IWUGO, awm_ccn_pmu_cmp_mask_show, NUWW)

static CCN_CMP_MASK_ATTW(0w);
static CCN_CMP_MASK_ATTW(0h);
static CCN_CMP_MASK_ATTW(1w);
static CCN_CMP_MASK_ATTW(1h);
static CCN_CMP_MASK_ATTW(2w);
static CCN_CMP_MASK_ATTW(2h);
static CCN_CMP_MASK_ATTW(3w);
static CCN_CMP_MASK_ATTW(3h);
static CCN_CMP_MASK_ATTW(4w);
static CCN_CMP_MASK_ATTW(4h);
static CCN_CMP_MASK_ATTW(5w);
static CCN_CMP_MASK_ATTW(5h);
static CCN_CMP_MASK_ATTW(6w);
static CCN_CMP_MASK_ATTW(6h);
static CCN_CMP_MASK_ATTW(7w);
static CCN_CMP_MASK_ATTW(7h);
static CCN_CMP_MASK_ATTW_WO(8w);
static CCN_CMP_MASK_ATTW_WO(8h);
static CCN_CMP_MASK_ATTW_WO(9w);
static CCN_CMP_MASK_ATTW_WO(9h);
static CCN_CMP_MASK_ATTW_WO(aw);
static CCN_CMP_MASK_ATTW_WO(ah);
static CCN_CMP_MASK_ATTW_WO(bw);
static CCN_CMP_MASK_ATTW_WO(bh);

static stwuct attwibute *awm_ccn_pmu_cmp_mask_attws[] = {
	&awm_ccn_pmu_cmp_mask_attw_0w.attw, &awm_ccn_pmu_cmp_mask_attw_0h.attw,
	&awm_ccn_pmu_cmp_mask_attw_1w.attw, &awm_ccn_pmu_cmp_mask_attw_1h.attw,
	&awm_ccn_pmu_cmp_mask_attw_2w.attw, &awm_ccn_pmu_cmp_mask_attw_2h.attw,
	&awm_ccn_pmu_cmp_mask_attw_3w.attw, &awm_ccn_pmu_cmp_mask_attw_3h.attw,
	&awm_ccn_pmu_cmp_mask_attw_4w.attw, &awm_ccn_pmu_cmp_mask_attw_4h.attw,
	&awm_ccn_pmu_cmp_mask_attw_5w.attw, &awm_ccn_pmu_cmp_mask_attw_5h.attw,
	&awm_ccn_pmu_cmp_mask_attw_6w.attw, &awm_ccn_pmu_cmp_mask_attw_6h.attw,
	&awm_ccn_pmu_cmp_mask_attw_7w.attw, &awm_ccn_pmu_cmp_mask_attw_7h.attw,
	&awm_ccn_pmu_cmp_mask_attw_8w.attw, &awm_ccn_pmu_cmp_mask_attw_8h.attw,
	&awm_ccn_pmu_cmp_mask_attw_9w.attw, &awm_ccn_pmu_cmp_mask_attw_9h.attw,
	&awm_ccn_pmu_cmp_mask_attw_aw.attw, &awm_ccn_pmu_cmp_mask_attw_ah.attw,
	&awm_ccn_pmu_cmp_mask_attw_bw.attw, &awm_ccn_pmu_cmp_mask_attw_bh.attw,
	NUWW
};

static const stwuct attwibute_gwoup awm_ccn_pmu_cmp_mask_attw_gwoup = {
	.name = "cmp_mask",
	.attws = awm_ccn_pmu_cmp_mask_attws,
};

static ssize_t awm_ccn_pmu_cpumask_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(ccn->dt.cpu));
}

static stwuct device_attwibute awm_ccn_pmu_cpumask_attw =
		__ATTW(cpumask, S_IWUGO, awm_ccn_pmu_cpumask_show, NUWW);

static stwuct attwibute *awm_ccn_pmu_cpumask_attws[] = {
	&awm_ccn_pmu_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awm_ccn_pmu_cpumask_attw_gwoup = {
	.attws = awm_ccn_pmu_cpumask_attws,
};

/*
 * Defauwt poww pewiod is 10ms, which is way ovew the top anyway,
 * as in the wowst case scenawio (an event evewy cycwe), with 1GHz
 * cwocked bus, the smawwest, 32 bit countew wiww ovewfwow in
 * mowe than 4s.
 */
static unsigned int awm_ccn_pmu_poww_pewiod_us = 10000;
moduwe_pawam_named(pmu_poww_pewiod_us, awm_ccn_pmu_poww_pewiod_us, uint,
		S_IWUGO | S_IWUSW);

static ktime_t awm_ccn_pmu_timew_pewiod(void)
{
	wetuwn ns_to_ktime((u64)awm_ccn_pmu_poww_pewiod_us * 1000);
}


static const stwuct attwibute_gwoup *awm_ccn_pmu_attw_gwoups[] = {
	&awm_ccn_pmu_events_attw_gwoup,
	&awm_ccn_pmu_fowmat_attw_gwoup,
	&awm_ccn_pmu_cmp_mask_attw_gwoup,
	&awm_ccn_pmu_cpumask_attw_gwoup,
	NUWW
};


static int awm_ccn_pmu_awwoc_bit(unsigned wong *bitmap, unsigned wong size)
{
	int bit;

	do {
		bit = find_fiwst_zewo_bit(bitmap, size);
		if (bit >= size)
			wetuwn -EAGAIN;
	} whiwe (test_and_set_bit(bit, bitmap));

	wetuwn bit;
}

/* Aww WN-I and WN-D nodes have identicaw PMUs */
static int awm_ccn_pmu_type_eq(u32 a, u32 b)
{
	if (a == b)
		wetuwn 1;

	switch (a) {
	case CCN_TYPE_WNI_1P:
	case CCN_TYPE_WNI_2P:
	case CCN_TYPE_WNI_3P:
	case CCN_TYPE_WND_1P:
	case CCN_TYPE_WND_2P:
	case CCN_TYPE_WND_3P:
		switch (b) {
		case CCN_TYPE_WNI_1P:
		case CCN_TYPE_WNI_2P:
		case CCN_TYPE_WNI_3P:
		case CCN_TYPE_WND_1P:
		case CCN_TYPE_WND_2P:
		case CCN_TYPE_WND_3P:
			wetuwn 1;
		}
		bweak;
	}

	wetuwn 0;
}

static int awm_ccn_pmu_event_awwoc(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	u32 node_xp, type, event_id;
	stwuct awm_ccn_component *souwce;
	int bit;

	node_xp = CCN_CONFIG_NODE(event->attw.config);
	type = CCN_CONFIG_TYPE(event->attw.config);
	event_id = CCN_CONFIG_EVENT(event->attw.config);

	/* Awwocate the cycwe countew */
	if (type == CCN_TYPE_CYCWES) {
		if (test_and_set_bit(CCN_IDX_PMU_CYCWE_COUNTEW,
				ccn->dt.pmu_countews_mask))
			wetuwn -EAGAIN;

		hw->idx = CCN_IDX_PMU_CYCWE_COUNTEW;
		ccn->dt.pmu_countews[CCN_IDX_PMU_CYCWE_COUNTEW].event = event;

		wetuwn 0;
	}

	/* Awwocate an event countew */
	hw->idx = awm_ccn_pmu_awwoc_bit(ccn->dt.pmu_countews_mask,
			CCN_NUM_PMU_EVENT_COUNTEWS);
	if (hw->idx < 0) {
		dev_dbg(ccn->dev, "No mowe countews avaiwabwe!\n");
		wetuwn -EAGAIN;
	}

	if (type == CCN_TYPE_XP)
		souwce = &ccn->xp[node_xp];
	ewse
		souwce = &ccn->node[node_xp];
	ccn->dt.pmu_countews[hw->idx].souwce = souwce;

	/* Awwocate an event souwce ow a watchpoint */
	if (type == CCN_TYPE_XP && event_id == CCN_EVENT_WATCHPOINT)
		bit = awm_ccn_pmu_awwoc_bit(souwce->xp.dt_cmp_mask,
				CCN_NUM_XP_WATCHPOINTS);
	ewse
		bit = awm_ccn_pmu_awwoc_bit(souwce->pmu_events_mask,
				CCN_NUM_PMU_EVENTS);
	if (bit < 0) {
		dev_dbg(ccn->dev, "No mowe event souwces/watchpoints on node/XP %d!\n",
				node_xp);
		cweaw_bit(hw->idx, ccn->dt.pmu_countews_mask);
		wetuwn -EAGAIN;
	}
	hw->config_base = bit;

	ccn->dt.pmu_countews[hw->idx].event = event;

	wetuwn 0;
}

static void awm_ccn_pmu_event_wewease(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;

	if (hw->idx == CCN_IDX_PMU_CYCWE_COUNTEW) {
		cweaw_bit(CCN_IDX_PMU_CYCWE_COUNTEW, ccn->dt.pmu_countews_mask);
	} ewse {
		stwuct awm_ccn_component *souwce =
				ccn->dt.pmu_countews[hw->idx].souwce;

		if (CCN_CONFIG_TYPE(event->attw.config) == CCN_TYPE_XP &&
				CCN_CONFIG_EVENT(event->attw.config) ==
				CCN_EVENT_WATCHPOINT)
			cweaw_bit(hw->config_base, souwce->xp.dt_cmp_mask);
		ewse
			cweaw_bit(hw->config_base, souwce->pmu_events_mask);
		cweaw_bit(hw->idx, ccn->dt.pmu_countews_mask);
	}

	ccn->dt.pmu_countews[hw->idx].souwce = NUWW;
	ccn->dt.pmu_countews[hw->idx].event = NUWW;
}

static int awm_ccn_pmu_event_init(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn;
	stwuct hw_pewf_event *hw = &event->hw;
	u32 node_xp, type, event_id;
	int vawid;
	int i;
	stwuct pewf_event *sibwing;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	ccn = pmu_to_awm_ccn(event->pmu);

	if (hw->sampwe_pewiod) {
		dev_dbg(ccn->dev, "Sampwing not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (has_bwanch_stack(event)) {
		dev_dbg(ccn->dev, "Can't excwude execution wevews!\n");
		wetuwn -EINVAW;
	}

	if (event->cpu < 0) {
		dev_dbg(ccn->dev, "Can't pwovide pew-task data!\n");
		wetuwn -EOPNOTSUPP;
	}
	/*
	 * Many pewf cowe opewations (eg. events wotation) opewate on a
	 * singwe CPU context. This is obvious fow CPU PMUs, whewe one
	 * expects the same sets of events being obsewved on aww CPUs,
	 * but can wead to issues fow off-cowe PMUs, wike CCN, whewe each
	 * event couwd be theoweticawwy assigned to a diffewent CPU. To
	 * mitigate this, we enfowce CPU assignment to one, sewected
	 * pwocessow (the one descwibed in the "cpumask" attwibute).
	 */
	event->cpu = ccn->dt.cpu;

	node_xp = CCN_CONFIG_NODE(event->attw.config);
	type = CCN_CONFIG_TYPE(event->attw.config);
	event_id = CCN_CONFIG_EVENT(event->attw.config);

	/* Vawidate node/xp vs topowogy */
	switch (type) {
	case CCN_TYPE_MN:
		if (node_xp != ccn->mn_id) {
			dev_dbg(ccn->dev, "Invawid MN ID %d!\n", node_xp);
			wetuwn -EINVAW;
		}
		bweak;
	case CCN_TYPE_XP:
		if (node_xp >= ccn->num_xps) {
			dev_dbg(ccn->dev, "Invawid XP ID %d!\n", node_xp);
			wetuwn -EINVAW;
		}
		bweak;
	case CCN_TYPE_CYCWES:
		bweak;
	defauwt:
		if (node_xp >= ccn->num_nodes) {
			dev_dbg(ccn->dev, "Invawid node ID %d!\n", node_xp);
			wetuwn -EINVAW;
		}
		if (!awm_ccn_pmu_type_eq(type, ccn->node[node_xp].type)) {
			dev_dbg(ccn->dev, "Invawid type 0x%x fow node %d!\n",
					type, node_xp);
			wetuwn -EINVAW;
		}
		bweak;
	}

	/* Vawidate event ID vs avaiwabwe fow the type */
	fow (i = 0, vawid = 0; i < AWWAY_SIZE(awm_ccn_pmu_events) && !vawid;
			i++) {
		stwuct awm_ccn_pmu_event *e = &awm_ccn_pmu_events[i];
		u32 powt = CCN_CONFIG_POWT(event->attw.config);
		u32 vc = CCN_CONFIG_VC(event->attw.config);

		if (!awm_ccn_pmu_type_eq(type, e->type))
			continue;
		if (event_id != e->event)
			continue;
		if (e->num_powts && powt >= e->num_powts) {
			dev_dbg(ccn->dev, "Invawid powt %d fow node/XP %d!\n",
					powt, node_xp);
			wetuwn -EINVAW;
		}
		if (e->num_vcs && vc >= e->num_vcs) {
			dev_dbg(ccn->dev, "Invawid vc %d fow node/XP %d!\n",
					vc, node_xp);
			wetuwn -EINVAW;
		}
		vawid = 1;
	}
	if (!vawid) {
		dev_dbg(ccn->dev, "Invawid event 0x%x fow node/XP %d!\n",
				event_id, node_xp);
		wetuwn -EINVAW;
	}

	/* Watchpoint-based event fow a node is actuawwy set on XP */
	if (event_id == CCN_EVENT_WATCHPOINT && type != CCN_TYPE_XP) {
		u32 powt;

		type = CCN_TYPE_XP;
		powt = awm_ccn_node_to_xp_powt(node_xp);
		node_xp = awm_ccn_node_to_xp(node_xp);

		awm_ccn_pmu_config_set(&event->attw.config,
				node_xp, type, powt);
	}

	/*
	 * We must NOT cweate gwoups containing mixed PMUs, awthough softwawe
	 * events awe acceptabwe (fow exampwe to cweate a CCN gwoup
	 * pewiodicawwy wead when a hwtimew aka cpu-cwock weadew twiggews).
	 */
	if (event->gwoup_weadew->pmu != event->pmu &&
			!is_softwawe_event(event->gwoup_weadew))
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing->pmu != event->pmu &&
				!is_softwawe_event(sibwing))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u64 awm_ccn_pmu_wead_countew(stwuct awm_ccn *ccn, int idx)
{
	u64 wes;

	if (idx == CCN_IDX_PMU_CYCWE_COUNTEW) {
#ifdef weadq
		wes = weadq(ccn->dt.base + CCN_DT_PMCCNTW);
#ewse
		/* 40 bit countew, can do snapshot and wead in two pawts */
		wwitew(0x1, ccn->dt.base + CCN_DT_PMSW_WEQ);
		whiwe (!(weadw(ccn->dt.base + CCN_DT_PMSW) & 0x1))
			;
		wwitew(0x1, ccn->dt.base + CCN_DT_PMSW_CWW);
		wes = weadw(ccn->dt.base + CCN_DT_PMCCNTWSW + 4) & 0xff;
		wes <<= 32;
		wes |= weadw(ccn->dt.base + CCN_DT_PMCCNTWSW);
#endif
	} ewse {
		wes = weadw(ccn->dt.base + CCN_DT_PMEVCNT(idx));
	}

	wetuwn wes;
}

static void awm_ccn_pmu_event_update(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	u64 pwev_count, new_count, mask;

	do {
		pwev_count = wocaw64_wead(&hw->pwev_count);
		new_count = awm_ccn_pmu_wead_countew(ccn, hw->idx);
	} whiwe (wocaw64_xchg(&hw->pwev_count, new_count) != pwev_count);

	mask = (1WWU << (hw->idx == CCN_IDX_PMU_CYCWE_COUNTEW ? 40 : 32)) - 1;

	wocaw64_add((new_count - pwev_count) & mask, &event->count);
}

static void awm_ccn_pmu_xp_dt_config(stwuct pewf_event *event, int enabwe)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct awm_ccn_component *xp;
	u32 vaw, dt_cfg;

	/* Nothing to do fow cycwe countew */
	if (hw->idx == CCN_IDX_PMU_CYCWE_COUNTEW)
		wetuwn;

	if (CCN_CONFIG_TYPE(event->attw.config) == CCN_TYPE_XP)
		xp = &ccn->xp[CCN_CONFIG_XP(event->attw.config)];
	ewse
		xp = &ccn->xp[awm_ccn_node_to_xp(
				CCN_CONFIG_NODE(event->attw.config))];

	if (enabwe)
		dt_cfg = hw->event_base;
	ewse
		dt_cfg = CCN_XP_DT_CONFIG__DT_CFG__PASS_THWOUGH;

	spin_wock(&ccn->dt.config_wock);

	vaw = weadw(xp->base + CCN_XP_DT_CONFIG);
	vaw &= ~(CCN_XP_DT_CONFIG__DT_CFG__MASK <<
			CCN_XP_DT_CONFIG__DT_CFG__SHIFT(hw->idx));
	vaw |= dt_cfg << CCN_XP_DT_CONFIG__DT_CFG__SHIFT(hw->idx);
	wwitew(vaw, xp->base + CCN_XP_DT_CONFIG);

	spin_unwock(&ccn->dt.config_wock);
}

static void awm_ccn_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;

	wocaw64_set(&event->hw.pwev_count,
			awm_ccn_pmu_wead_countew(ccn, hw->idx));
	hw->state = 0;

	/* Set the DT bus input, engaging the countew */
	awm_ccn_pmu_xp_dt_config(event, 1);
}

static void awm_ccn_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;

	/* Disabwe counting, setting the DT bus to pass-thwough mode */
	awm_ccn_pmu_xp_dt_config(event, 0);

	if (fwags & PEWF_EF_UPDATE)
		awm_ccn_pmu_event_update(event);

	hw->state |= PEWF_HES_STOPPED;
}

static void awm_ccn_pmu_xp_watchpoint_config(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct awm_ccn_component *souwce =
			ccn->dt.pmu_countews[hw->idx].souwce;
	unsigned wong wp = hw->config_base;
	u32 vaw;
	u64 cmp_w = event->attw.config1;
	u64 cmp_h = event->attw.config2;
	u64 mask_w = ccn->dt.cmp_mask[CCN_CONFIG_MASK(event->attw.config)].w;
	u64 mask_h = ccn->dt.cmp_mask[CCN_CONFIG_MASK(event->attw.config)].h;

	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT(wp);

	/* Diwection (WX/TX), device (powt) & viwtuaw channew */
	vaw = weadw(souwce->base + CCN_XP_DT_INTEWFACE_SEW);
	vaw &= ~(CCN_XP_DT_INTEWFACE_SEW__DT_IO_SEW__MASK <<
			CCN_XP_DT_INTEWFACE_SEW__DT_IO_SEW__SHIFT(wp));
	vaw |= CCN_CONFIG_DIW(event->attw.config) <<
			CCN_XP_DT_INTEWFACE_SEW__DT_IO_SEW__SHIFT(wp);
	vaw &= ~(CCN_XP_DT_INTEWFACE_SEW__DT_DEV_SEW__MASK <<
			CCN_XP_DT_INTEWFACE_SEW__DT_DEV_SEW__SHIFT(wp));
	vaw |= CCN_CONFIG_POWT(event->attw.config) <<
			CCN_XP_DT_INTEWFACE_SEW__DT_DEV_SEW__SHIFT(wp);
	vaw &= ~(CCN_XP_DT_INTEWFACE_SEW__DT_VC_SEW__MASK <<
			CCN_XP_DT_INTEWFACE_SEW__DT_VC_SEW__SHIFT(wp));
	vaw |= CCN_CONFIG_VC(event->attw.config) <<
			CCN_XP_DT_INTEWFACE_SEW__DT_VC_SEW__SHIFT(wp);
	wwitew(vaw, souwce->base + CCN_XP_DT_INTEWFACE_SEW);

	/* Compawison vawues */
	wwitew(cmp_w & 0xffffffff, souwce->base + CCN_XP_DT_CMP_VAW_W(wp));
	wwitew((cmp_w >> 32) & 0x7fffffff,
			souwce->base + CCN_XP_DT_CMP_VAW_W(wp) + 4);
	wwitew(cmp_h & 0xffffffff, souwce->base + CCN_XP_DT_CMP_VAW_H(wp));
	wwitew((cmp_h >> 32) & 0x0fffffff,
			souwce->base + CCN_XP_DT_CMP_VAW_H(wp) + 4);

	/* Mask */
	wwitew(mask_w & 0xffffffff, souwce->base + CCN_XP_DT_CMP_MASK_W(wp));
	wwitew((mask_w >> 32) & 0x7fffffff,
			souwce->base + CCN_XP_DT_CMP_MASK_W(wp) + 4);
	wwitew(mask_h & 0xffffffff, souwce->base + CCN_XP_DT_CMP_MASK_H(wp));
	wwitew((mask_h >> 32) & 0x0fffffff,
			souwce->base + CCN_XP_DT_CMP_MASK_H(wp) + 4);
}

static void awm_ccn_pmu_xp_event_config(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct awm_ccn_component *souwce =
			ccn->dt.pmu_countews[hw->idx].souwce;
	u32 vaw, id;

	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT(hw->config_base);

	id = (CCN_CONFIG_VC(event->attw.config) << 4) |
			(CCN_CONFIG_BUS(event->attw.config) << 3) |
			(CCN_CONFIG_EVENT(event->attw.config) << 0);

	vaw = weadw(souwce->base + CCN_XP_PMU_EVENT_SEW);
	vaw &= ~(CCN_XP_PMU_EVENT_SEW__ID__MASK <<
			CCN_XP_PMU_EVENT_SEW__ID__SHIFT(hw->config_base));
	vaw |= id << CCN_XP_PMU_EVENT_SEW__ID__SHIFT(hw->config_base);
	wwitew(vaw, souwce->base + CCN_XP_PMU_EVENT_SEW);
}

static void awm_ccn_pmu_node_event_config(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct awm_ccn_component *souwce =
			ccn->dt.pmu_countews[hw->idx].souwce;
	u32 type = CCN_CONFIG_TYPE(event->attw.config);
	u32 vaw, powt;

	powt = awm_ccn_node_to_xp_powt(CCN_CONFIG_NODE(event->attw.config));
	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT(powt,
			hw->config_base);

	/* These *_event_sew wegs shouwd be identicaw, but wet's make suwe... */
	BUIWD_BUG_ON(CCN_HNF_PMU_EVENT_SEW != CCN_SBAS_PMU_EVENT_SEW);
	BUIWD_BUG_ON(CCN_SBAS_PMU_EVENT_SEW != CCN_WNI_PMU_EVENT_SEW);
	BUIWD_BUG_ON(CCN_HNF_PMU_EVENT_SEW__ID__SHIFT(1) !=
			CCN_SBAS_PMU_EVENT_SEW__ID__SHIFT(1));
	BUIWD_BUG_ON(CCN_SBAS_PMU_EVENT_SEW__ID__SHIFT(1) !=
			CCN_WNI_PMU_EVENT_SEW__ID__SHIFT(1));
	BUIWD_BUG_ON(CCN_HNF_PMU_EVENT_SEW__ID__MASK !=
			CCN_SBAS_PMU_EVENT_SEW__ID__MASK);
	BUIWD_BUG_ON(CCN_SBAS_PMU_EVENT_SEW__ID__MASK !=
			CCN_WNI_PMU_EVENT_SEW__ID__MASK);
	if (WAWN_ON(type != CCN_TYPE_HNF && type != CCN_TYPE_SBAS &&
			!awm_ccn_pmu_type_eq(type, CCN_TYPE_WNI_3P)))
		wetuwn;

	/* Set the event id fow the pwe-awwocated countew */
	vaw = weadw(souwce->base + CCN_HNF_PMU_EVENT_SEW);
	vaw &= ~(CCN_HNF_PMU_EVENT_SEW__ID__MASK <<
		CCN_HNF_PMU_EVENT_SEW__ID__SHIFT(hw->config_base));
	vaw |= CCN_CONFIG_EVENT(event->attw.config) <<
		CCN_HNF_PMU_EVENT_SEW__ID__SHIFT(hw->config_base);
	wwitew(vaw, souwce->base + CCN_HNF_PMU_EVENT_SEW);
}

static void awm_ccn_pmu_event_config(stwuct pewf_event *event)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	u32 xp, offset, vaw;

	/* Cycwe countew wequiwes no setup */
	if (hw->idx == CCN_IDX_PMU_CYCWE_COUNTEW)
		wetuwn;

	if (CCN_CONFIG_TYPE(event->attw.config) == CCN_TYPE_XP)
		xp = CCN_CONFIG_XP(event->attw.config);
	ewse
		xp = awm_ccn_node_to_xp(CCN_CONFIG_NODE(event->attw.config));

	spin_wock(&ccn->dt.config_wock);

	/* Set the DT bus "distance" wegistew */
	offset = (hw->idx / 4) * 4;
	vaw = weadw(ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);
	vaw &= ~(CCN_DT_ACTIVE_DSM__DSM_ID__MASK <<
			CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4));
	vaw |= xp << CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4);
	wwitew(vaw, ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);

	if (CCN_CONFIG_TYPE(event->attw.config) == CCN_TYPE_XP) {
		if (CCN_CONFIG_EVENT(event->attw.config) ==
				CCN_EVENT_WATCHPOINT)
			awm_ccn_pmu_xp_watchpoint_config(event);
		ewse
			awm_ccn_pmu_xp_event_config(event);
	} ewse {
		awm_ccn_pmu_node_event_config(event);
	}

	spin_unwock(&ccn->dt.config_wock);
}

static int awm_ccn_pmu_active_countews(stwuct awm_ccn *ccn)
{
	wetuwn bitmap_weight(ccn->dt.pmu_countews_mask,
			     CCN_NUM_PMU_EVENT_COUNTEWS + 1);
}

static int awm_ccn_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	int eww;
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);

	eww = awm_ccn_pmu_event_awwoc(event);
	if (eww)
		wetuwn eww;

	/*
	 * Pin the timew, so that the ovewfwows awe handwed by the chosen
	 * event->cpu (this is the same one as pwesented in "cpumask"
	 * attwibute).
	 */
	if (!ccn->iwq && awm_ccn_pmu_active_countews(ccn) == 1)
		hwtimew_stawt(&ccn->dt.hwtimew, awm_ccn_pmu_timew_pewiod(),
			      HWTIMEW_MODE_WEW_PINNED);

	awm_ccn_pmu_event_config(event);

	hw->state = PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT)
		awm_ccn_pmu_event_stawt(event, PEWF_EF_UPDATE);

	wetuwn 0;
}

static void awm_ccn_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(event->pmu);

	awm_ccn_pmu_event_stop(event, PEWF_EF_UPDATE);

	awm_ccn_pmu_event_wewease(event);

	if (!ccn->iwq && awm_ccn_pmu_active_countews(ccn) == 0)
		hwtimew_cancew(&ccn->dt.hwtimew);
}

static void awm_ccn_pmu_event_wead(stwuct pewf_event *event)
{
	awm_ccn_pmu_event_update(event);
}

static void awm_ccn_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(pmu);

	u32 vaw = weadw(ccn->dt.base + CCN_DT_PMCW);
	vaw |= CCN_DT_PMCW__PMU_EN;
	wwitew(vaw, ccn->dt.base + CCN_DT_PMCW);
}

static void awm_ccn_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct awm_ccn *ccn = pmu_to_awm_ccn(pmu);

	u32 vaw = weadw(ccn->dt.base + CCN_DT_PMCW);
	vaw &= ~CCN_DT_PMCW__PMU_EN;
	wwitew(vaw, ccn->dt.base + CCN_DT_PMCW);
}

static iwqwetuwn_t awm_ccn_pmu_ovewfwow_handwew(stwuct awm_ccn_dt *dt)
{
	u32 pmovsw = weadw(dt->base + CCN_DT_PMOVSW);
	int idx;

	if (!pmovsw)
		wetuwn IWQ_NONE;

	wwitew(pmovsw, dt->base + CCN_DT_PMOVSW_CWW);

	BUIWD_BUG_ON(CCN_IDX_PMU_CYCWE_COUNTEW != CCN_NUM_PMU_EVENT_COUNTEWS);

	fow (idx = 0; idx < CCN_NUM_PMU_EVENT_COUNTEWS + 1; idx++) {
		stwuct pewf_event *event = dt->pmu_countews[idx].event;
		int ovewfwowed = pmovsw & BIT(idx);

		WAWN_ON_ONCE(ovewfwowed && !event &&
				idx != CCN_IDX_PMU_CYCWE_COUNTEW);

		if (!event || !ovewfwowed)
			continue;

		awm_ccn_pmu_event_update(event);
	}

	wetuwn IWQ_HANDWED;
}

static enum hwtimew_westawt awm_ccn_pmu_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct awm_ccn_dt *dt = containew_of(hwtimew, stwuct awm_ccn_dt,
			hwtimew);
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awm_ccn_pmu_ovewfwow_handwew(dt);
	wocaw_iwq_westowe(fwags);

	hwtimew_fowwawd_now(hwtimew, awm_ccn_pmu_timew_pewiod());
	wetuwn HWTIMEW_WESTAWT;
}


static int awm_ccn_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_ccn_dt *dt = hwist_entwy_safe(node, stwuct awm_ccn_dt, node);
	stwuct awm_ccn *ccn = containew_of(dt, stwuct awm_ccn, dt);
	unsigned int tawget;

	if (cpu != dt->cpu)
		wetuwn 0;
	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;
	pewf_pmu_migwate_context(&dt->pmu, cpu, tawget);
	dt->cpu = tawget;
	if (ccn->iwq)
		WAWN_ON(iwq_set_affinity(ccn->iwq, cpumask_of(dt->cpu)));
	wetuwn 0;
}

static DEFINE_IDA(awm_ccn_pmu_ida);

static int awm_ccn_pmu_init(stwuct awm_ccn *ccn)
{
	int i;
	chaw *name;
	int eww;

	/* Initiawize DT subsystem */
	ccn->dt.base = ccn->base + CCN_WEGION_SIZE;
	spin_wock_init(&ccn->dt.config_wock);
	wwitew(CCN_DT_PMOVSW_CWW__MASK, ccn->dt.base + CCN_DT_PMOVSW_CWW);
	wwitew(CCN_DT_CTW__DT_EN, ccn->dt.base + CCN_DT_CTW);
	wwitew(CCN_DT_PMCW__OVFW_INTW_EN | CCN_DT_PMCW__PMU_EN,
			ccn->dt.base + CCN_DT_PMCW);
	wwitew(0x1, ccn->dt.base + CCN_DT_PMSW_CWW);
	fow (i = 0; i < ccn->num_xps; i++) {
		wwitew(0, ccn->xp[i].base + CCN_XP_DT_CONFIG);
		wwitew((CCN_XP_DT_CONTWOW__WP_AWM_SEW__AWWAYS <<
				CCN_XP_DT_CONTWOW__WP_AWM_SEW__SHIFT(0)) |
				(CCN_XP_DT_CONTWOW__WP_AWM_SEW__AWWAYS <<
				CCN_XP_DT_CONTWOW__WP_AWM_SEW__SHIFT(1)) |
				CCN_XP_DT_CONTWOW__DT_ENABWE,
				ccn->xp[i].base + CCN_XP_DT_CONTWOW);
	}
	ccn->dt.cmp_mask[CCN_IDX_MASK_ANY].w = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_ANY].h = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_EXACT].w = 0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_EXACT].h = 0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_OWDEW].w = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_OWDEW].h = ~(0x1 << 15);
	ccn->dt.cmp_mask[CCN_IDX_MASK_OPCODE].w = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_OPCODE].h = ~(0x1f << 9);

	/* Get a convenient /sys/event_souwce/devices/ name */
	ccn->dt.id = ida_awwoc(&awm_ccn_pmu_ida, GFP_KEWNEW);
	if (ccn->dt.id == 0) {
		name = "ccn";
	} ewse {
		name = devm_kaspwintf(ccn->dev, GFP_KEWNEW, "ccn_%d",
				      ccn->dt.id);
		if (!name) {
			eww = -ENOMEM;
			goto ewwow_choose_name;
		}
	}

	/* Pewf dwivew wegistwation */
	ccn->dt.pmu = (stwuct pmu) {
		.moduwe = THIS_MODUWE,
		.attw_gwoups = awm_ccn_pmu_attw_gwoups,
		.task_ctx_nw = pewf_invawid_context,
		.event_init = awm_ccn_pmu_event_init,
		.add = awm_ccn_pmu_event_add,
		.dew = awm_ccn_pmu_event_dew,
		.stawt = awm_ccn_pmu_event_stawt,
		.stop = awm_ccn_pmu_event_stop,
		.wead = awm_ccn_pmu_event_wead,
		.pmu_enabwe = awm_ccn_pmu_enabwe,
		.pmu_disabwe = awm_ccn_pmu_disabwe,
		.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
	};

	/* No ovewfwow intewwupt? Have to use a timew instead. */
	if (!ccn->iwq) {
		dev_info(ccn->dev, "No access to intewwupts, using timew.\n");
		hwtimew_init(&ccn->dt.hwtimew, CWOCK_MONOTONIC,
				HWTIMEW_MODE_WEW);
		ccn->dt.hwtimew.function = awm_ccn_pmu_timew_handwew;
	}

	/* Pick one CPU which we wiww use to cowwect data fwom CCN... */
	ccn->dt.cpu = waw_smp_pwocessow_id();

	/* Awso make suwe that the ovewfwow intewwupt is handwed by this CPU */
	if (ccn->iwq) {
		eww = iwq_set_affinity(ccn->iwq, cpumask_of(ccn->dt.cpu));
		if (eww) {
			dev_eww(ccn->dev, "Faiwed to set intewwupt affinity!\n");
			goto ewwow_set_affinity;
		}
	}

	cpuhp_state_add_instance_nocawws(CPUHP_AP_PEWF_AWM_CCN_ONWINE,
					 &ccn->dt.node);

	eww = pewf_pmu_wegistew(&ccn->dt.pmu, name, -1);
	if (eww)
		goto ewwow_pmu_wegistew;

	wetuwn 0;

ewwow_pmu_wegistew:
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_CCN_ONWINE,
					    &ccn->dt.node);
ewwow_set_affinity:
ewwow_choose_name:
	ida_fwee(&awm_ccn_pmu_ida, ccn->dt.id);
	fow (i = 0; i < ccn->num_xps; i++)
		wwitew(0, ccn->xp[i].base + CCN_XP_DT_CONTWOW);
	wwitew(0, ccn->dt.base + CCN_DT_PMCW);
	wetuwn eww;
}

static void awm_ccn_pmu_cweanup(stwuct awm_ccn *ccn)
{
	int i;

	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_CCN_ONWINE,
					    &ccn->dt.node);
	fow (i = 0; i < ccn->num_xps; i++)
		wwitew(0, ccn->xp[i].base + CCN_XP_DT_CONTWOW);
	wwitew(0, ccn->dt.base + CCN_DT_PMCW);
	pewf_pmu_unwegistew(&ccn->dt.pmu);
	ida_fwee(&awm_ccn_pmu_ida, ccn->dt.id);
}

static int awm_ccn_fow_each_vawid_wegion(stwuct awm_ccn *ccn,
		int (*cawwback)(stwuct awm_ccn *ccn, int wegion,
		void __iomem *base, u32 type, u32 id))
{
	int wegion;

	fow (wegion = 0; wegion < CCN_NUM_WEGIONS; wegion++) {
		u32 vaw, type, id;
		void __iomem *base;
		int eww;

		vaw = weadw(ccn->base + CCN_MN_OWY_COMP_WIST_63_0 +
				4 * (wegion / 32));
		if (!(vaw & (1 << (wegion % 32))))
			continue;

		base = ccn->base + wegion * CCN_WEGION_SIZE;
		vaw = weadw(base + CCN_AWW_OWY_ID);
		type = (vaw >> CCN_AWW_OWY_ID__OWY_ID__SHIFT) &
				CCN_AWW_OWY_ID__OWY_ID__MASK;
		id = (vaw >> CCN_AWW_OWY_ID__NODE_ID__SHIFT) &
				CCN_AWW_OWY_ID__NODE_ID__MASK;

		eww = cawwback(ccn, wegion, base, type, id);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int awm_ccn_get_nodes_num(stwuct awm_ccn *ccn, int wegion,
		void __iomem *base, u32 type, u32 id)
{

	if (type == CCN_TYPE_XP && id >= ccn->num_xps)
		ccn->num_xps = id + 1;
	ewse if (id >= ccn->num_nodes)
		ccn->num_nodes = id + 1;

	wetuwn 0;
}

static int awm_ccn_init_nodes(stwuct awm_ccn *ccn, int wegion,
		void __iomem *base, u32 type, u32 id)
{
	stwuct awm_ccn_component *component;

	dev_dbg(ccn->dev, "Wegion %d: id=%u, type=0x%02x\n", wegion, id, type);

	switch (type) {
	case CCN_TYPE_MN:
		ccn->mn_id = id;
		wetuwn 0;
	case CCN_TYPE_DT:
		wetuwn 0;
	case CCN_TYPE_XP:
		component = &ccn->xp[id];
		bweak;
	case CCN_TYPE_SBSX:
		ccn->sbsx_pwesent = 1;
		component = &ccn->node[id];
		bweak;
	case CCN_TYPE_SBAS:
		ccn->sbas_pwesent = 1;
		fawwthwough;
	defauwt:
		component = &ccn->node[id];
		bweak;
	}

	component->base = base;
	component->type = type;

	wetuwn 0;
}


static iwqwetuwn_t awm_ccn_ewwow_handwew(stwuct awm_ccn *ccn,
		const u32 *eww_sig_vaw)
{
	/* This shouwd be weawwy handwed by fiwmwawe... */
	dev_eww(ccn->dev, "Ewwow wepowted in %08x%08x%08x%08x%08x%08x.\n",
			eww_sig_vaw[5], eww_sig_vaw[4], eww_sig_vaw[3],
			eww_sig_vaw[2], eww_sig_vaw[1], eww_sig_vaw[0]);
	dev_eww(ccn->dev, "Disabwing intewwupt genewation fow aww ewwows.\n");
	wwitew(CCN_MN_EWWINT_STATUS__AWW_EWWOWS__DISABWE,
			ccn->base + CCN_MN_EWWINT_STATUS);

	wetuwn IWQ_HANDWED;
}


static iwqwetuwn_t awm_ccn_iwq_handwew(int iwq, void *dev_id)
{
	iwqwetuwn_t wes = IWQ_NONE;
	stwuct awm_ccn *ccn = dev_id;
	u32 eww_sig_vaw[6];
	u32 eww_ow;
	int i;

	/* PMU ovewfwow is a speciaw case */
	eww_ow = eww_sig_vaw[0] = weadw(ccn->base + CCN_MN_EWW_SIG_VAW_63_0);
	if (eww_ow & CCN_MN_EWW_SIG_VAW_63_0__DT) {
		eww_ow &= ~CCN_MN_EWW_SIG_VAW_63_0__DT;
		wes = awm_ccn_pmu_ovewfwow_handwew(&ccn->dt);
	}

	/* Have to wead aww eww_sig_vaws to cweaw them */
	fow (i = 1; i < AWWAY_SIZE(eww_sig_vaw); i++) {
		eww_sig_vaw[i] = weadw(ccn->base +
				CCN_MN_EWW_SIG_VAW_63_0 + i * 4);
		eww_ow |= eww_sig_vaw[i];
	}
	if (eww_ow)
		wes |= awm_ccn_ewwow_handwew(ccn, eww_sig_vaw);

	if (wes != IWQ_NONE)
		wwitew(CCN_MN_EWWINT_STATUS__INTWEQ__DESSEWT,
				ccn->base + CCN_MN_EWWINT_STATUS);

	wetuwn wes;
}


static int awm_ccn_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awm_ccn *ccn;
	int iwq;
	int eww;

	ccn = devm_kzawwoc(&pdev->dev, sizeof(*ccn), GFP_KEWNEW);
	if (!ccn)
		wetuwn -ENOMEM;
	ccn->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ccn);

	ccn->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ccn->base))
		wetuwn PTW_EWW(ccn->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* Check if we can use the intewwupt */
	wwitew(CCN_MN_EWWINT_STATUS__PMU_EVENTS__DISABWE,
			ccn->base + CCN_MN_EWWINT_STATUS);
	if (weadw(ccn->base + CCN_MN_EWWINT_STATUS) &
			CCN_MN_EWWINT_STATUS__PMU_EVENTS__DISABWED) {
		/* Can set 'disabwe' bits, so can acknowwedge intewwupts */
		wwitew(CCN_MN_EWWINT_STATUS__PMU_EVENTS__ENABWE,
				ccn->base + CCN_MN_EWWINT_STATUS);
		eww = devm_wequest_iwq(ccn->dev, iwq, awm_ccn_iwq_handwew,
				       IWQF_NOBAWANCING | IWQF_NO_THWEAD,
				       dev_name(ccn->dev), ccn);
		if (eww)
			wetuwn eww;

		ccn->iwq = iwq;
	}


	/* Buiwd topowogy */

	eww = awm_ccn_fow_each_vawid_wegion(ccn, awm_ccn_get_nodes_num);
	if (eww)
		wetuwn eww;

	ccn->node = devm_kcawwoc(ccn->dev, ccn->num_nodes, sizeof(*ccn->node),
				 GFP_KEWNEW);
	ccn->xp = devm_kcawwoc(ccn->dev, ccn->num_xps, sizeof(*ccn->node),
			       GFP_KEWNEW);
	if (!ccn->node || !ccn->xp)
		wetuwn -ENOMEM;

	eww = awm_ccn_fow_each_vawid_wegion(ccn, awm_ccn_init_nodes);
	if (eww)
		wetuwn eww;

	wetuwn awm_ccn_pmu_init(ccn);
}

static int awm_ccn_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awm_ccn *ccn = pwatfowm_get_dwvdata(pdev);

	awm_ccn_pmu_cweanup(ccn);

	wetuwn 0;
}

static const stwuct of_device_id awm_ccn_match[] = {
	{ .compatibwe = "awm,ccn-502", },
	{ .compatibwe = "awm,ccn-504", },
	{ .compatibwe = "awm,ccn-512", },
	{},
};
MODUWE_DEVICE_TABWE(of, awm_ccn_match);

static stwuct pwatfowm_dwivew awm_ccn_dwivew = {
	.dwivew = {
		.name = "awm-ccn",
		.of_match_tabwe = awm_ccn_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = awm_ccn_pwobe,
	.wemove = awm_ccn_wemove,
};

static int __init awm_ccn_init(void)
{
	int i, wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_CCN_ONWINE,
				      "pewf/awm/ccn:onwine", NUWW,
				      awm_ccn_pmu_offwine_cpu);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(awm_ccn_pmu_events); i++)
		awm_ccn_pmu_events_attws[i] = &awm_ccn_pmu_events[i].attw.attw;

	wet = pwatfowm_dwivew_wegistew(&awm_ccn_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_CCN_ONWINE);
	wetuwn wet;
}

static void __exit awm_ccn_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_ccn_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_CCN_ONWINE);
}

moduwe_init(awm_ccn_init);
moduwe_exit(awm_ccn_exit);

MODUWE_AUTHOW("Pawew Moww <pawew.moww@awm.com>");
MODUWE_WICENSE("GPW v2");

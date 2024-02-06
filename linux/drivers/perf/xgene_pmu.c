// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * APM X-Gene SoC PMU (Pewfowmance Monitow Unit)
 *
 * Copywight (c) 2016, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Hoan Twan <hotwan@apm.com>
 *         Tai Nguyen <ttnguyen@apm.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define CSW_CSWCW                       0x0000
#define  CSW_CSWCW_DUAWMCB_MASK         BIT(0)
#define  CSW_CSWCW_MCB0_WOUTING(x)	(((x) & 0x0C) >> 2)
#define  CSW_CSWCW_MCB1_WOUTING(x)	(((x) & 0x30) >> 4)
#define MCBADDWMW                       0x0000
#define  MCBADDWMW_DUAWMCU_MODE_MASK    BIT(2)

#define PCPPMU_INTSTATUS_WEG	0x000
#define PCPPMU_INTMASK_WEG	0x004
#define  PCPPMU_INTMASK		0x0000000F
#define  PCPPMU_INTENMASK	0xFFFFFFFF
#define  PCPPMU_INTCWWMASK	0xFFFFFFF0
#define  PCPPMU_INT_MCU		BIT(0)
#define  PCPPMU_INT_MCB		BIT(1)
#define  PCPPMU_INT_W3C		BIT(2)
#define  PCPPMU_INT_IOB		BIT(3)

#define  PCPPMU_V3_INTMASK	0x00FF33FF
#define  PCPPMU_V3_INTENMASK	0xFFFFFFFF
#define  PCPPMU_V3_INTCWWMASK	0xFF00CC00
#define  PCPPMU_V3_INT_MCU	0x000000FF
#define  PCPPMU_V3_INT_MCB	0x00000300
#define  PCPPMU_V3_INT_W3C	0x00FF0000
#define  PCPPMU_V3_INT_IOB	0x00003000

#define PMU_MAX_COUNTEWS	4
#define PMU_CNT_MAX_PEWIOD	0xFFFFFFFFUWW
#define PMU_V3_CNT_MAX_PEWIOD	0xFFFFFFFFFFFFFFFFUWW
#define PMU_OVEWFWOW_MASK	0xF
#define PMU_PMCW_E		BIT(0)
#define PMU_PMCW_P		BIT(1)

#define PMU_PMEVCNTW0		0x000
#define PMU_PMEVCNTW1		0x004
#define PMU_PMEVCNTW2		0x008
#define PMU_PMEVCNTW3		0x00C
#define PMU_PMEVTYPEW0		0x400
#define PMU_PMEVTYPEW1		0x404
#define PMU_PMEVTYPEW2		0x408
#define PMU_PMEVTYPEW3		0x40C
#define PMU_PMAMW0		0xA00
#define PMU_PMAMW1		0xA04
#define PMU_PMCNTENSET		0xC00
#define PMU_PMCNTENCWW		0xC20
#define PMU_PMINTENSET		0xC40
#define PMU_PMINTENCWW		0xC60
#define PMU_PMOVSW		0xC80
#define PMU_PMCW		0xE04

/* PMU wegistews fow V3 */
#define PMU_PMOVSCWW		0xC80
#define PMU_PMOVSSET		0xCC0

#define to_pmu_dev(p)     containew_of(p, stwuct xgene_pmu_dev, pmu)
#define GET_CNTW(ev)      (ev->hw.idx)
#define GET_EVENTID(ev)   (ev->hw.config & 0xFFUWW)
#define GET_AGENTID(ev)   (ev->hw.config_base & 0xFFFFFFFFUW)
#define GET_AGENT1ID(ev)  ((ev->hw.config_base >> 32) & 0xFFFFFFFFUW)

stwuct hw_pmu_info {
	u32 type;
	u32 enabwe_mask;
	void __iomem *csw;
};

stwuct xgene_pmu_dev {
	stwuct hw_pmu_info *inf;
	stwuct xgene_pmu *pawent;
	stwuct pmu pmu;
	u8 max_countews;
	DECWAWE_BITMAP(cntw_assign_mask, PMU_MAX_COUNTEWS);
	u64 max_pewiod;
	const stwuct attwibute_gwoup **attw_gwoups;
	stwuct pewf_event *pmu_countew_event[PMU_MAX_COUNTEWS];
};

stwuct xgene_pmu_ops {
	void (*mask_int)(stwuct xgene_pmu *pmu);
	void (*unmask_int)(stwuct xgene_pmu *pmu);
	u64 (*wead_countew)(stwuct xgene_pmu_dev *pmu, int idx);
	void (*wwite_countew)(stwuct xgene_pmu_dev *pmu, int idx, u64 vaw);
	void (*wwite_evttype)(stwuct xgene_pmu_dev *pmu_dev, int idx, u32 vaw);
	void (*wwite_agentmsk)(stwuct xgene_pmu_dev *pmu_dev, u32 vaw);
	void (*wwite_agent1msk)(stwuct xgene_pmu_dev *pmu_dev, u32 vaw);
	void (*enabwe_countew)(stwuct xgene_pmu_dev *pmu_dev, int idx);
	void (*disabwe_countew)(stwuct xgene_pmu_dev *pmu_dev, int idx);
	void (*enabwe_countew_int)(stwuct xgene_pmu_dev *pmu_dev, int idx);
	void (*disabwe_countew_int)(stwuct xgene_pmu_dev *pmu_dev, int idx);
	void (*weset_countews)(stwuct xgene_pmu_dev *pmu_dev);
	void (*stawt_countews)(stwuct xgene_pmu_dev *pmu_dev);
	void (*stop_countews)(stwuct xgene_pmu_dev *pmu_dev);
};

stwuct xgene_pmu {
	stwuct device *dev;
	stwuct hwist_node node;
	int vewsion;
	void __iomem *pcppmu_csw;
	u32 mcb_active_mask;
	u32 mc_active_mask;
	u32 w3c_active_mask;
	cpumask_t cpu;
	int iwq;
	waw_spinwock_t wock;
	const stwuct xgene_pmu_ops *ops;
	stwuct wist_head w3cpmus;
	stwuct wist_head iobpmus;
	stwuct wist_head mcbpmus;
	stwuct wist_head mcpmus;
};

stwuct xgene_pmu_dev_ctx {
	chaw *name;
	stwuct wist_head next;
	stwuct xgene_pmu_dev *pmu_dev;
	stwuct hw_pmu_info inf;
};

stwuct xgene_pmu_data {
	int id;
	u32 data;
};

enum xgene_pmu_vewsion {
	PCP_PMU_V1 = 1,
	PCP_PMU_V2,
	PCP_PMU_V3,
};

enum xgene_pmu_dev_type {
	PMU_TYPE_W3C = 0,
	PMU_TYPE_IOB,
	PMU_TYPE_IOB_SWOW,
	PMU_TYPE_MCB,
	PMU_TYPE_MC,
};

/*
 * sysfs fowmat attwibutes
 */
static ssize_t xgene_pmu_fowmat_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "%s\n", (chaw *) eattw->vaw);
}

#define XGENE_PMU_FOWMAT_ATTW(_name, _config)		\
	(&((stwuct dev_ext_attwibute[]) {		\
		{ .attw = __ATTW(_name, S_IWUGO, xgene_pmu_fowmat_show, NUWW), \
		  .vaw = (void *) _config, }		\
	})[0].attw.attw)

static stwuct attwibute *w3c_pmu_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(w3c_eventid, "config:0-7"),
	XGENE_PMU_FOWMAT_ATTW(w3c_agentid, "config1:0-9"),
	NUWW,
};

static stwuct attwibute *iob_pmu_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(iob_eventid, "config:0-7"),
	XGENE_PMU_FOWMAT_ATTW(iob_agentid, "config1:0-63"),
	NUWW,
};

static stwuct attwibute *mcb_pmu_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(mcb_eventid, "config:0-5"),
	XGENE_PMU_FOWMAT_ATTW(mcb_agentid, "config1:0-9"),
	NUWW,
};

static stwuct attwibute *mc_pmu_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(mc_eventid, "config:0-28"),
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = w3c_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup iob_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = iob_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup mcb_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = mcb_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup mc_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = mc_pmu_fowmat_attws,
};

static stwuct attwibute *w3c_pmu_v3_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(w3c_eventid, "config:0-39"),
	NUWW,
};

static stwuct attwibute *iob_pmu_v3_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(iob_eventid, "config:0-47"),
	NUWW,
};

static stwuct attwibute *iob_swow_pmu_v3_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(iob_swow_eventid, "config:0-16"),
	NUWW,
};

static stwuct attwibute *mcb_pmu_v3_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(mcb_eventid, "config:0-35"),
	NUWW,
};

static stwuct attwibute *mc_pmu_v3_fowmat_attws[] = {
	XGENE_PMU_FOWMAT_ATTW(mc_eventid, "config:0-44"),
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_v3_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = w3c_pmu_v3_fowmat_attws,
};

static const stwuct attwibute_gwoup iob_pmu_v3_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = iob_pmu_v3_fowmat_attws,
};

static const stwuct attwibute_gwoup iob_swow_pmu_v3_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = iob_swow_pmu_v3_fowmat_attws,
};

static const stwuct attwibute_gwoup mcb_pmu_v3_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = mcb_pmu_v3_fowmat_attws,
};

static const stwuct attwibute_gwoup mc_pmu_v3_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = mc_pmu_v3_fowmat_attws,
};

/*
 * sysfs event attwibutes
 */
static ssize_t xgene_pmu_event_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn sysfs_emit(buf, "config=0x%wwx\n", pmu_attw->id);
}

#define XGENE_PMU_EVENT_ATTW(_name, _config)		\
	PMU_EVENT_ATTW_ID(_name, xgene_pmu_event_show, _config)

static stwuct attwibute *w3c_pmu_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(cycwe-count-div-64,		0x01),
	XGENE_PMU_EVENT_ATTW(wead-hit,				0x02),
	XGENE_PMU_EVENT_ATTW(wead-miss,				0x03),
	XGENE_PMU_EVENT_ATTW(wwite-need-wepwacement,		0x06),
	XGENE_PMU_EVENT_ATTW(wwite-not-need-wepwacement,	0x07),
	XGENE_PMU_EVENT_ATTW(tq-fuww,				0x08),
	XGENE_PMU_EVENT_ATTW(ackq-fuww,				0x09),
	XGENE_PMU_EVENT_ATTW(wdb-fuww,				0x0a),
	XGENE_PMU_EVENT_ATTW(bank-fifo-fuww,			0x0b),
	XGENE_PMU_EVENT_ATTW(odb-fuww,				0x0c),
	XGENE_PMU_EVENT_ATTW(wbq-fuww,				0x0d),
	XGENE_PMU_EVENT_ATTW(bank-confwict-fifo-issue,		0x0e),
	XGENE_PMU_EVENT_ATTW(bank-fifo-issue,			0x0f),
	NUWW,
};

static stwuct attwibute *iob_pmu_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(cycwe-count-div-64,		0x01),
	XGENE_PMU_EVENT_ATTW(axi0-wead,				0x02),
	XGENE_PMU_EVENT_ATTW(axi0-wead-pawtiaw,			0x03),
	XGENE_PMU_EVENT_ATTW(axi1-wead,				0x04),
	XGENE_PMU_EVENT_ATTW(axi1-wead-pawtiaw,			0x05),
	XGENE_PMU_EVENT_ATTW(csw-wead-bwock,			0x06),
	XGENE_PMU_EVENT_ATTW(csw-wead-pawtiaw,			0x07),
	XGENE_PMU_EVENT_ATTW(axi0-wwite,			0x10),
	XGENE_PMU_EVENT_ATTW(axi0-wwite-pawtiaw,		0x11),
	XGENE_PMU_EVENT_ATTW(axi1-wwite,			0x13),
	XGENE_PMU_EVENT_ATTW(axi1-wwite-pawtiaw,		0x14),
	XGENE_PMU_EVENT_ATTW(csw-inbound-diwty,			0x16),
	NUWW,
};

static stwuct attwibute *mcb_pmu_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(cycwe-count-div-64,		0x01),
	XGENE_PMU_EVENT_ATTW(csw-wead,				0x02),
	XGENE_PMU_EVENT_ATTW(csw-wwite-wequest,			0x03),
	XGENE_PMU_EVENT_ATTW(mcb-csw-staww,			0x04),
	XGENE_PMU_EVENT_ATTW(cancew-wead-gack,			0x05),
	NUWW,
};

static stwuct attwibute *mc_pmu_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(cycwe-count-div-64,		0x01),
	XGENE_PMU_EVENT_ATTW(act-cmd-sent,			0x02),
	XGENE_PMU_EVENT_ATTW(pwe-cmd-sent,			0x03),
	XGENE_PMU_EVENT_ATTW(wd-cmd-sent,			0x04),
	XGENE_PMU_EVENT_ATTW(wda-cmd-sent,			0x05),
	XGENE_PMU_EVENT_ATTW(ww-cmd-sent,			0x06),
	XGENE_PMU_EVENT_ATTW(wwa-cmd-sent,			0x07),
	XGENE_PMU_EVENT_ATTW(pde-cmd-sent,			0x08),
	XGENE_PMU_EVENT_ATTW(swe-cmd-sent,			0x09),
	XGENE_PMU_EVENT_ATTW(pwea-cmd-sent,			0x0a),
	XGENE_PMU_EVENT_ATTW(wef-cmd-sent,			0x0b),
	XGENE_PMU_EVENT_ATTW(wd-wda-cmd-sent,			0x0c),
	XGENE_PMU_EVENT_ATTW(ww-wwa-cmd-sent,			0x0d),
	XGENE_PMU_EVENT_ATTW(in-wd-cowwision,			0x0e),
	XGENE_PMU_EVENT_ATTW(in-ww-cowwision,			0x0f),
	XGENE_PMU_EVENT_ATTW(cowwision-queue-not-empty,		0x10),
	XGENE_PMU_EVENT_ATTW(cowwision-queue-fuww,		0x11),
	XGENE_PMU_EVENT_ATTW(mcu-wequest,			0x12),
	XGENE_PMU_EVENT_ATTW(mcu-wd-wequest,			0x13),
	XGENE_PMU_EVENT_ATTW(mcu-hp-wd-wequest,			0x14),
	XGENE_PMU_EVENT_ATTW(mcu-ww-wequest,			0x15),
	XGENE_PMU_EVENT_ATTW(mcu-wd-pwoceed-aww,		0x16),
	XGENE_PMU_EVENT_ATTW(mcu-wd-pwoceed-cancew,		0x17),
	XGENE_PMU_EVENT_ATTW(mcu-wd-wesponse,			0x18),
	XGENE_PMU_EVENT_ATTW(mcu-wd-pwoceed-specuwative-aww,	0x19),
	XGENE_PMU_EVENT_ATTW(mcu-wd-pwoceed-specuwative-cancew,	0x1a),
	XGENE_PMU_EVENT_ATTW(mcu-ww-pwoceed-aww,		0x1b),
	XGENE_PMU_EVENT_ATTW(mcu-ww-pwoceed-cancew,		0x1c),
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = w3c_pmu_events_attws,
};

static const stwuct attwibute_gwoup iob_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = iob_pmu_events_attws,
};

static const stwuct attwibute_gwoup mcb_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = mcb_pmu_events_attws,
};

static const stwuct attwibute_gwoup mc_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = mc_pmu_events_attws,
};

static stwuct attwibute *w3c_pmu_v3_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(wead-hit,				0x01),
	XGENE_PMU_EVENT_ATTW(wead-miss,				0x02),
	XGENE_PMU_EVENT_ATTW(index-fwush-eviction,		0x03),
	XGENE_PMU_EVENT_ATTW(wwite-caused-wepwacement,		0x04),
	XGENE_PMU_EVENT_ATTW(wwite-not-caused-wepwacement,	0x05),
	XGENE_PMU_EVENT_ATTW(cwean-eviction,			0x06),
	XGENE_PMU_EVENT_ATTW(diwty-eviction,			0x07),
	XGENE_PMU_EVENT_ATTW(wead,				0x08),
	XGENE_PMU_EVENT_ATTW(wwite,				0x09),
	XGENE_PMU_EVENT_ATTW(wequest,				0x0a),
	XGENE_PMU_EVENT_ATTW(tq-bank-confwict-issue-staww,	0x0b),
	XGENE_PMU_EVENT_ATTW(tq-fuww,				0x0c),
	XGENE_PMU_EVENT_ATTW(ackq-fuww,				0x0d),
	XGENE_PMU_EVENT_ATTW(wdb-fuww,				0x0e),
	XGENE_PMU_EVENT_ATTW(odb-fuww,				0x10),
	XGENE_PMU_EVENT_ATTW(wbq-fuww,				0x11),
	XGENE_PMU_EVENT_ATTW(input-weq-async-fifo-staww,	0x12),
	XGENE_PMU_EVENT_ATTW(output-weq-async-fifo-staww,	0x13),
	XGENE_PMU_EVENT_ATTW(output-data-async-fifo-staww,	0x14),
	XGENE_PMU_EVENT_ATTW(totaw-insewtion,			0x15),
	XGENE_PMU_EVENT_ATTW(sip-insewtions-w-set,		0x16),
	XGENE_PMU_EVENT_ATTW(sip-insewtions-w-cweaw,		0x17),
	XGENE_PMU_EVENT_ATTW(dip-insewtions-w-set,		0x18),
	XGENE_PMU_EVENT_ATTW(dip-insewtions-w-cweaw,		0x19),
	XGENE_PMU_EVENT_ATTW(dip-insewtions-fowce-w-set,	0x1a),
	XGENE_PMU_EVENT_ATTW(egwession,				0x1b),
	XGENE_PMU_EVENT_ATTW(wepwacement,			0x1c),
	XGENE_PMU_EVENT_ATTW(owd-wepwacement,			0x1d),
	XGENE_PMU_EVENT_ATTW(young-wepwacement,			0x1e),
	XGENE_PMU_EVENT_ATTW(w-set-wepwacement,			0x1f),
	XGENE_PMU_EVENT_ATTW(w-cweaw-wepwacement,		0x20),
	XGENE_PMU_EVENT_ATTW(owd-w-wepwacement,			0x21),
	XGENE_PMU_EVENT_ATTW(owd-nw-wepwacement,		0x22),
	XGENE_PMU_EVENT_ATTW(young-w-wepwacement,		0x23),
	XGENE_PMU_EVENT_ATTW(young-nw-wepwacement,		0x24),
	XGENE_PMU_EVENT_ATTW(bwoomfiwtew-cweawing,		0x25),
	XGENE_PMU_EVENT_ATTW(genewation-fwip,			0x26),
	XGENE_PMU_EVENT_ATTW(vcc-dwoop-detected,		0x27),
	NUWW,
};

static stwuct attwibute *iob_fast_pmu_v3_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(pa-weq-buf-awwoc-aww,		0x01),
	XGENE_PMU_EVENT_ATTW(pa-weq-buf-awwoc-wd,		0x02),
	XGENE_PMU_EVENT_ATTW(pa-weq-buf-awwoc-ww,		0x03),
	XGENE_PMU_EVENT_ATTW(pa-aww-cp-weq,			0x04),
	XGENE_PMU_EVENT_ATTW(pa-cp-bwk-weq,			0x05),
	XGENE_PMU_EVENT_ATTW(pa-cp-ptw-weq,			0x06),
	XGENE_PMU_EVENT_ATTW(pa-cp-wd-weq,			0x07),
	XGENE_PMU_EVENT_ATTW(pa-cp-ww-weq,			0x08),
	XGENE_PMU_EVENT_ATTW(ba-aww-weq,			0x09),
	XGENE_PMU_EVENT_ATTW(ba-wd-weq,				0x0a),
	XGENE_PMU_EVENT_ATTW(ba-ww-weq,				0x0b),
	XGENE_PMU_EVENT_ATTW(pa-wd-shawed-weq-issued,		0x10),
	XGENE_PMU_EVENT_ATTW(pa-wd-excwusive-weq-issued,	0x11),
	XGENE_PMU_EVENT_ATTW(pa-ww-invawidate-weq-issued-stashabwe, 0x12),
	XGENE_PMU_EVENT_ATTW(pa-ww-invawidate-weq-issued-nonstashabwe, 0x13),
	XGENE_PMU_EVENT_ATTW(pa-ww-back-weq-issued-stashabwe,	0x14),
	XGENE_PMU_EVENT_ATTW(pa-ww-back-weq-issued-nonstashabwe, 0x15),
	XGENE_PMU_EVENT_ATTW(pa-ptw-ww-weq,			0x16),
	XGENE_PMU_EVENT_ATTW(pa-ptw-wd-weq,			0x17),
	XGENE_PMU_EVENT_ATTW(pa-ww-back-cwean-data,		0x18),
	XGENE_PMU_EVENT_ATTW(pa-ww-back-cancewwed-on-SS,	0x1b),
	XGENE_PMU_EVENT_ATTW(pa-bawwiew-occuwwence,		0x1c),
	XGENE_PMU_EVENT_ATTW(pa-bawwiew-cycwes,			0x1d),
	XGENE_PMU_EVENT_ATTW(pa-totaw-cp-snoops,		0x20),
	XGENE_PMU_EVENT_ATTW(pa-wd-shawed-snoop,		0x21),
	XGENE_PMU_EVENT_ATTW(pa-wd-shawed-snoop-hit,		0x22),
	XGENE_PMU_EVENT_ATTW(pa-wd-excwusive-snoop,		0x23),
	XGENE_PMU_EVENT_ATTW(pa-wd-excwusive-snoop-hit,		0x24),
	XGENE_PMU_EVENT_ATTW(pa-wd-ww-invawid-snoop,		0x25),
	XGENE_PMU_EVENT_ATTW(pa-wd-ww-invawid-snoop-hit,	0x26),
	XGENE_PMU_EVENT_ATTW(pa-weq-buffew-fuww,		0x28),
	XGENE_PMU_EVENT_ATTW(cswwf-outbound-weq-fifo-fuww,	0x29),
	XGENE_PMU_EVENT_ATTW(cswwf-inbound-snoop-fifo-backpwessuwe, 0x2a),
	XGENE_PMU_EVENT_ATTW(cswwf-outbound-wack-fifo-fuww,	0x2b),
	XGENE_PMU_EVENT_ATTW(cswwf-inbound-gack-fifo-backpwessuwe, 0x2c),
	XGENE_PMU_EVENT_ATTW(cswwf-outbound-data-fifo-fuww,	0x2d),
	XGENE_PMU_EVENT_ATTW(cswwf-inbound-data-fifo-backpwessuwe, 0x2e),
	XGENE_PMU_EVENT_ATTW(cswwf-inbound-weq-backpwessuwe,	0x2f),
	NUWW,
};

static stwuct attwibute *iob_swow_pmu_v3_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(pa-axi0-wd-weq,			0x01),
	XGENE_PMU_EVENT_ATTW(pa-axi0-ww-weq,			0x02),
	XGENE_PMU_EVENT_ATTW(pa-axi1-wd-weq,			0x03),
	XGENE_PMU_EVENT_ATTW(pa-axi1-ww-weq,			0x04),
	XGENE_PMU_EVENT_ATTW(ba-aww-axi-weq,			0x07),
	XGENE_PMU_EVENT_ATTW(ba-axi-wd-weq,			0x08),
	XGENE_PMU_EVENT_ATTW(ba-axi-ww-weq,			0x09),
	XGENE_PMU_EVENT_ATTW(ba-fwee-wist-empty,		0x10),
	NUWW,
};

static stwuct attwibute *mcb_pmu_v3_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(weq-weceive,			0x01),
	XGENE_PMU_EVENT_ATTW(wd-weq-wecv,			0x02),
	XGENE_PMU_EVENT_ATTW(wd-weq-wecv-2,			0x03),
	XGENE_PMU_EVENT_ATTW(ww-weq-wecv,			0x04),
	XGENE_PMU_EVENT_ATTW(ww-weq-wecv-2,			0x05),
	XGENE_PMU_EVENT_ATTW(wd-weq-sent-to-mcu,		0x06),
	XGENE_PMU_EVENT_ATTW(wd-weq-sent-to-mcu-2,		0x07),
	XGENE_PMU_EVENT_ATTW(wd-weq-sent-to-spec-mcu,		0x08),
	XGENE_PMU_EVENT_ATTW(wd-weq-sent-to-spec-mcu-2,		0x09),
	XGENE_PMU_EVENT_ATTW(gwbw-ack-wecv-fow-wd-sent-to-spec-mcu, 0x0a),
	XGENE_PMU_EVENT_ATTW(gwbw-ack-go-wecv-fow-wd-sent-to-spec-mcu, 0x0b),
	XGENE_PMU_EVENT_ATTW(gwbw-ack-nogo-wecv-fow-wd-sent-to-spec-mcu, 0x0c),
	XGENE_PMU_EVENT_ATTW(gwbw-ack-go-wecv-any-wd-weq,	0x0d),
	XGENE_PMU_EVENT_ATTW(gwbw-ack-go-wecv-any-wd-weq-2,	0x0e),
	XGENE_PMU_EVENT_ATTW(ww-weq-sent-to-mcu,		0x0f),
	XGENE_PMU_EVENT_ATTW(gack-wecv,				0x10),
	XGENE_PMU_EVENT_ATTW(wd-gack-wecv,			0x11),
	XGENE_PMU_EVENT_ATTW(ww-gack-wecv,			0x12),
	XGENE_PMU_EVENT_ATTW(cancew-wd-gack,			0x13),
	XGENE_PMU_EVENT_ATTW(cancew-ww-gack,			0x14),
	XGENE_PMU_EVENT_ATTW(mcb-csw-weq-staww,			0x15),
	XGENE_PMU_EVENT_ATTW(mcu-weq-intf-bwocked,		0x16),
	XGENE_PMU_EVENT_ATTW(mcb-mcu-wd-intf-staww,		0x17),
	XGENE_PMU_EVENT_ATTW(csw-wd-intf-bwocked,		0x18),
	XGENE_PMU_EVENT_ATTW(csw-wocaw-ack-intf-bwocked,	0x19),
	XGENE_PMU_EVENT_ATTW(mcu-weq-tabwe-fuww,		0x1a),
	XGENE_PMU_EVENT_ATTW(mcu-stat-tabwe-fuww,		0x1b),
	XGENE_PMU_EVENT_ATTW(mcu-ww-tabwe-fuww,			0x1c),
	XGENE_PMU_EVENT_ATTW(mcu-wdweceipt-wesp,		0x1d),
	XGENE_PMU_EVENT_ATTW(mcu-wwcompwete-wesp,		0x1e),
	XGENE_PMU_EVENT_ATTW(mcu-wetwyack-wesp,			0x1f),
	XGENE_PMU_EVENT_ATTW(mcu-pcwdgwant-wesp,		0x20),
	XGENE_PMU_EVENT_ATTW(mcu-weq-fwom-wastwoad,		0x21),
	XGENE_PMU_EVENT_ATTW(mcu-weq-fwom-bypass,		0x22),
	XGENE_PMU_EVENT_ATTW(vowt-dwoop-detect,			0x23),
	NUWW,
};

static stwuct attwibute *mc_pmu_v3_events_attws[] = {
	XGENE_PMU_EVENT_ATTW(cycwe-count,			0x00),
	XGENE_PMU_EVENT_ATTW(act-sent,				0x01),
	XGENE_PMU_EVENT_ATTW(pwe-sent,				0x02),
	XGENE_PMU_EVENT_ATTW(wd-sent,				0x03),
	XGENE_PMU_EVENT_ATTW(wda-sent,				0x04),
	XGENE_PMU_EVENT_ATTW(ww-sent,				0x05),
	XGENE_PMU_EVENT_ATTW(wwa-sent,				0x06),
	XGENE_PMU_EVENT_ATTW(pd-entwy-vwd,			0x07),
	XGENE_PMU_EVENT_ATTW(swef-entwy-vwd,			0x08),
	XGENE_PMU_EVENT_ATTW(pwea-sent,				0x09),
	XGENE_PMU_EVENT_ATTW(wef-sent,				0x0a),
	XGENE_PMU_EVENT_ATTW(wd-wda-sent,			0x0b),
	XGENE_PMU_EVENT_ATTW(ww-wwa-sent,			0x0c),
	XGENE_PMU_EVENT_ATTW(waw-hazawd,			0x0d),
	XGENE_PMU_EVENT_ATTW(waw-hazawd,			0x0e),
	XGENE_PMU_EVENT_ATTW(waw-hazawd,			0x0f),
	XGENE_PMU_EVENT_ATTW(waw-hazawd,			0x10),
	XGENE_PMU_EVENT_ATTW(waw-waw-waw-hazawd,		0x11),
	XGENE_PMU_EVENT_ATTW(hpwd-wpwd-ww-weq-vwd,		0x12),
	XGENE_PMU_EVENT_ATTW(wpwd-weq-vwd,			0x13),
	XGENE_PMU_EVENT_ATTW(hpwd-weq-vwd,			0x14),
	XGENE_PMU_EVENT_ATTW(hpwd-wpwd-weq-vwd,			0x15),
	XGENE_PMU_EVENT_ATTW(ww-weq-vwd,			0x16),
	XGENE_PMU_EVENT_ATTW(pawtiaw-ww-weq-vwd,		0x17),
	XGENE_PMU_EVENT_ATTW(wd-wetwy,				0x18),
	XGENE_PMU_EVENT_ATTW(ww-wetwy,				0x19),
	XGENE_PMU_EVENT_ATTW(wetwy-gnt,				0x1a),
	XGENE_PMU_EVENT_ATTW(wank-change,			0x1b),
	XGENE_PMU_EVENT_ATTW(diw-change,			0x1c),
	XGENE_PMU_EVENT_ATTW(wank-diw-change,			0x1d),
	XGENE_PMU_EVENT_ATTW(wank-active,			0x1e),
	XGENE_PMU_EVENT_ATTW(wank-idwe,				0x1f),
	XGENE_PMU_EVENT_ATTW(wank-pd,				0x20),
	XGENE_PMU_EVENT_ATTW(wank-swef,				0x21),
	XGENE_PMU_EVENT_ATTW(queue-fiww-gt-thwesh,		0x22),
	XGENE_PMU_EVENT_ATTW(queue-wds-gt-thwesh,		0x23),
	XGENE_PMU_EVENT_ATTW(queue-wws-gt-thwesh,		0x24),
	XGENE_PMU_EVENT_ATTW(phy-updt-compwt,			0x25),
	XGENE_PMU_EVENT_ATTW(tz-faiw,				0x26),
	XGENE_PMU_EVENT_ATTW(dwam-ewwc,				0x27),
	XGENE_PMU_EVENT_ATTW(dwam-ewwd,				0x28),
	XGENE_PMU_EVENT_ATTW(wd-enq,				0x29),
	XGENE_PMU_EVENT_ATTW(ww-enq,				0x2a),
	XGENE_PMU_EVENT_ATTW(tmac-wimit-weached,		0x2b),
	XGENE_PMU_EVENT_ATTW(tmaw-twackew-fuww,			0x2c),
	NUWW,
};

static const stwuct attwibute_gwoup w3c_pmu_v3_events_attw_gwoup = {
	.name = "events",
	.attws = w3c_pmu_v3_events_attws,
};

static const stwuct attwibute_gwoup iob_fast_pmu_v3_events_attw_gwoup = {
	.name = "events",
	.attws = iob_fast_pmu_v3_events_attws,
};

static const stwuct attwibute_gwoup iob_swow_pmu_v3_events_attw_gwoup = {
	.name = "events",
	.attws = iob_swow_pmu_v3_events_attws,
};

static const stwuct attwibute_gwoup mcb_pmu_v3_events_attw_gwoup = {
	.name = "events",
	.attws = mcb_pmu_v3_events_attws,
};

static const stwuct attwibute_gwoup mc_pmu_v3_events_attw_gwoup = {
	.name = "events",
	.attws = mc_pmu_v3_events_attws,
};

/*
 * sysfs cpumask attwibutes
 */
static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &pmu_dev->pawent->cpu);
}

static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *xgene_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pmu_cpumask_attw_gwoup = {
	.attws = xgene_pmu_cpumask_attws,
};

/*
 * Pew PMU device attwibute gwoups of PMU v1 and v2
 */
static const stwuct attwibute_gwoup *w3c_pmu_attw_gwoups[] = {
	&w3c_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&w3c_pmu_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *iob_pmu_attw_gwoups[] = {
	&iob_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&iob_pmu_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *mcb_pmu_attw_gwoups[] = {
	&mcb_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&mcb_pmu_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *mc_pmu_attw_gwoups[] = {
	&mc_pmu_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&mc_pmu_events_attw_gwoup,
	NUWW
};

/*
 * Pew PMU device attwibute gwoups of PMU v3
 */
static const stwuct attwibute_gwoup *w3c_pmu_v3_attw_gwoups[] = {
	&w3c_pmu_v3_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&w3c_pmu_v3_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *iob_fast_pmu_v3_attw_gwoups[] = {
	&iob_pmu_v3_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&iob_fast_pmu_v3_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *iob_swow_pmu_v3_attw_gwoups[] = {
	&iob_swow_pmu_v3_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&iob_swow_pmu_v3_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *mcb_pmu_v3_attw_gwoups[] = {
	&mcb_pmu_v3_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&mcb_pmu_v3_events_attw_gwoup,
	NUWW
};

static const stwuct attwibute_gwoup *mc_pmu_v3_attw_gwoups[] = {
	&mc_pmu_v3_fowmat_attw_gwoup,
	&pmu_cpumask_attw_gwoup,
	&mc_pmu_v3_events_attw_gwoup,
	NUWW
};

static int get_next_avaiw_cntw(stwuct xgene_pmu_dev *pmu_dev)
{
	int cntw;

	cntw = find_fiwst_zewo_bit(pmu_dev->cntw_assign_mask,
				pmu_dev->max_countews);
	if (cntw == pmu_dev->max_countews)
		wetuwn -ENOSPC;
	set_bit(cntw, pmu_dev->cntw_assign_mask);

	wetuwn cntw;
}

static void cweaw_avaiw_cntw(stwuct xgene_pmu_dev *pmu_dev, int cntw)
{
	cweaw_bit(cntw, pmu_dev->cntw_assign_mask);
}

static inwine void xgene_pmu_mask_int(stwuct xgene_pmu *xgene_pmu)
{
	wwitew(PCPPMU_INTENMASK, xgene_pmu->pcppmu_csw + PCPPMU_INTMASK_WEG);
}

static inwine void xgene_pmu_v3_mask_int(stwuct xgene_pmu *xgene_pmu)
{
	wwitew(PCPPMU_V3_INTENMASK, xgene_pmu->pcppmu_csw + PCPPMU_INTMASK_WEG);
}

static inwine void xgene_pmu_unmask_int(stwuct xgene_pmu *xgene_pmu)
{
	wwitew(PCPPMU_INTCWWMASK, xgene_pmu->pcppmu_csw + PCPPMU_INTMASK_WEG);
}

static inwine void xgene_pmu_v3_unmask_int(stwuct xgene_pmu *xgene_pmu)
{
	wwitew(PCPPMU_V3_INTCWWMASK,
	       xgene_pmu->pcppmu_csw + PCPPMU_INTMASK_WEG);
}

static inwine u64 xgene_pmu_wead_countew32(stwuct xgene_pmu_dev *pmu_dev,
					   int idx)
{
	wetuwn weadw(pmu_dev->inf->csw + PMU_PMEVCNTW0 + (4 * idx));
}

static inwine u64 xgene_pmu_wead_countew64(stwuct xgene_pmu_dev *pmu_dev,
					   int idx)
{
	u32 wo, hi;

	/*
	 * v3 has 64-bit countew wegistews composed by 2 32-bit wegistews
	 * This can be a pwobwem if the countew incweases and cawwies
	 * out of bit [31] between 2 weads. The extwa weads wouwd hewp
	 * to pwevent this issue.
	 */
	do {
		hi = xgene_pmu_wead_countew32(pmu_dev, 2 * idx + 1);
		wo = xgene_pmu_wead_countew32(pmu_dev, 2 * idx);
	} whiwe (hi != xgene_pmu_wead_countew32(pmu_dev, 2 * idx + 1));

	wetuwn (((u64)hi << 32) | wo);
}

static inwine void
xgene_pmu_wwite_countew32(stwuct xgene_pmu_dev *pmu_dev, int idx, u64 vaw)
{
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMEVCNTW0 + (4 * idx));
}

static inwine void
xgene_pmu_wwite_countew64(stwuct xgene_pmu_dev *pmu_dev, int idx, u64 vaw)
{
	u32 cnt_wo, cnt_hi;

	cnt_hi = uppew_32_bits(vaw);
	cnt_wo = wowew_32_bits(vaw);

	/* v3 has 64-bit countew wegistews composed by 2 32-bit wegistews */
	xgene_pmu_wwite_countew32(pmu_dev, 2 * idx, cnt_wo);
	xgene_pmu_wwite_countew32(pmu_dev, 2 * idx + 1, cnt_hi);
}

static inwine void
xgene_pmu_wwite_evttype(stwuct xgene_pmu_dev *pmu_dev, int idx, u32 vaw)
{
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMEVTYPEW0 + (4 * idx));
}

static inwine void
xgene_pmu_wwite_agentmsk(stwuct xgene_pmu_dev *pmu_dev, u32 vaw)
{
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMAMW0);
}

static inwine void
xgene_pmu_v3_wwite_agentmsk(stwuct xgene_pmu_dev *pmu_dev, u32 vaw) { }

static inwine void
xgene_pmu_wwite_agent1msk(stwuct xgene_pmu_dev *pmu_dev, u32 vaw)
{
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMAMW1);
}

static inwine void
xgene_pmu_v3_wwite_agent1msk(stwuct xgene_pmu_dev *pmu_dev, u32 vaw) { }

static inwine void
xgene_pmu_enabwe_countew(stwuct xgene_pmu_dev *pmu_dev, int idx)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMCNTENSET);
	vaw |= 1 << idx;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMCNTENSET);
}

static inwine void
xgene_pmu_disabwe_countew(stwuct xgene_pmu_dev *pmu_dev, int idx)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMCNTENCWW);
	vaw |= 1 << idx;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMCNTENCWW);
}

static inwine void
xgene_pmu_enabwe_countew_int(stwuct xgene_pmu_dev *pmu_dev, int idx)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMINTENSET);
	vaw |= 1 << idx;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMINTENSET);
}

static inwine void
xgene_pmu_disabwe_countew_int(stwuct xgene_pmu_dev *pmu_dev, int idx)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMINTENCWW);
	vaw |= 1 << idx;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMINTENCWW);
}

static inwine void xgene_pmu_weset_countews(stwuct xgene_pmu_dev *pmu_dev)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMCW);
	vaw |= PMU_PMCW_P;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMCW);
}

static inwine void xgene_pmu_stawt_countews(stwuct xgene_pmu_dev *pmu_dev)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMCW);
	vaw |= PMU_PMCW_E;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMCW);
}

static inwine void xgene_pmu_stop_countews(stwuct xgene_pmu_dev *pmu_dev)
{
	u32 vaw;

	vaw = weadw(pmu_dev->inf->csw + PMU_PMCW);
	vaw &= ~PMU_PMCW_E;
	wwitew(vaw, pmu_dev->inf->csw + PMU_PMCW);
}

static void xgene_pewf_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;
	boow enabwed = !bitmap_empty(pmu_dev->cntw_assign_mask,
			pmu_dev->max_countews);

	if (!enabwed)
		wetuwn;

	xgene_pmu->ops->stawt_countews(pmu_dev);
}

static void xgene_pewf_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;

	xgene_pmu->ops->stop_countews(pmu_dev);
}

static int xgene_pewf_event_init(stwuct pewf_event *event)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;
	stwuct pewf_event *sibwing;

	/* Test the event attw type check fow PMU enumewation */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * SOC PMU countews awe shawed acwoss aww cowes.
	 * Thewefowe, it does not suppowt pew-pwocess mode.
	 * Awso, it does not suppowt event sampwing mode.
	 */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;
	/*
	 * Many pewf cowe opewations (eg. events wotation) opewate on a
	 * singwe CPU context. This is obvious fow CPU PMUs, whewe one
	 * expects the same sets of events being obsewved on aww CPUs,
	 * but can wead to issues fow off-cowe PMUs, whewe each
	 * event couwd be theoweticawwy assigned to a diffewent CPU. To
	 * mitigate this, we enfowce CPU assignment to one, sewected
	 * pwocessow (the one descwibed in the "cpumask" attwibute).
	 */
	event->cpu = cpumask_fiwst(&pmu_dev->pawent->cpu);

	hw->config = event->attw.config;
	/*
	 * Each bit of the config1 fiewd wepwesents an agent fwom which the
	 * wequest of the event come. The event is counted onwy if it's caused
	 * by a wequest of an agent has the bit cweawed.
	 * By defauwt, the event is counted fow aww agents.
	 */
	hw->config_base = event->attw.config1;

	/*
	 * We must NOT cweate gwoups containing mixed PMUs, awthough softwawe
	 * events awe acceptabwe
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

static void xgene_pewf_enabwe_event(stwuct pewf_event *event)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;

	xgene_pmu->ops->wwite_evttype(pmu_dev, GET_CNTW(event),
				      GET_EVENTID(event));
	xgene_pmu->ops->wwite_agentmsk(pmu_dev, ~((u32)GET_AGENTID(event)));
	if (pmu_dev->inf->type == PMU_TYPE_IOB)
		xgene_pmu->ops->wwite_agent1msk(pmu_dev,
						~((u32)GET_AGENT1ID(event)));

	xgene_pmu->ops->enabwe_countew(pmu_dev, GET_CNTW(event));
	xgene_pmu->ops->enabwe_countew_int(pmu_dev, GET_CNTW(event));
}

static void xgene_pewf_disabwe_event(stwuct pewf_event *event)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;

	xgene_pmu->ops->disabwe_countew(pmu_dev, GET_CNTW(event));
	xgene_pmu->ops->disabwe_countew_int(pmu_dev, GET_CNTW(event));
}

static void xgene_pewf_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;
	stwuct hw_pewf_event *hw = &event->hw;
	/*
	 * Fow 32 bit countew, it has a pewiod of 2^32. To account fow the
	 * possibiwity of extweme intewwupt watency we pwogwam fow a pewiod of
	 * hawf that. Hopefuwwy, we can handwe the intewwupt befowe anothew 2^31
	 * events occuw and the countew ovewtakes its pwevious vawue.
	 * Fow 64 bit countew, we don't expect it ovewfwow.
	 */
	u64 vaw = 1UWW << 31;

	wocaw64_set(&hw->pwev_count, vaw);
	xgene_pmu->ops->wwite_countew(pmu_dev, hw->idx, vaw);
}

static void xgene_pewf_event_update(stwuct pewf_event *event)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;
	stwuct hw_pewf_event *hw = &event->hw;
	u64 dewta, pwev_waw_count, new_waw_count;

again:
	pwev_waw_count = wocaw64_wead(&hw->pwev_count);
	new_waw_count = xgene_pmu->ops->wead_countew(pmu_dev, GET_CNTW(event));

	if (wocaw64_cmpxchg(&hw->pwev_count, pwev_waw_count,
			    new_waw_count) != pwev_waw_count)
		goto again;

	dewta = (new_waw_count - pwev_waw_count) & pmu_dev->max_pewiod;

	wocaw64_add(dewta, &event->count);
}

static void xgene_pewf_wead(stwuct pewf_event *event)
{
	xgene_pewf_event_update(event);
}

static void xgene_pewf_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;
	stwuct hw_pewf_event *hw = &event->hw;

	if (WAWN_ON_ONCE(!(hw->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hw->state & PEWF_HES_UPTODATE));
	hw->state = 0;

	xgene_pewf_event_set_pewiod(event);

	if (fwags & PEWF_EF_WEWOAD) {
		u64 pwev_waw_count =  wocaw64_wead(&hw->pwev_count);

		xgene_pmu->ops->wwite_countew(pmu_dev, GET_CNTW(event),
					      pwev_waw_count);
	}

	xgene_pewf_enabwe_event(event);
	pewf_event_update_usewpage(event);
}

static void xgene_pewf_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;

	if (hw->state & PEWF_HES_UPTODATE)
		wetuwn;

	xgene_pewf_disabwe_event(event);
	WAWN_ON_ONCE(hw->state & PEWF_HES_STOPPED);
	hw->state |= PEWF_HES_STOPPED;

	if (hw->state & PEWF_HES_UPTODATE)
		wetuwn;

	xgene_pewf_wead(event);
	hw->state |= PEWF_HES_UPTODATE;
}

static int xgene_pewf_add(stwuct pewf_event *event, int fwags)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;

	hw->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	/* Awwocate an event countew */
	hw->idx = get_next_avaiw_cntw(pmu_dev);
	if (hw->idx < 0)
		wetuwn -EAGAIN;

	/* Update countew event pointew fow Intewwupt handwew */
	pmu_dev->pmu_countew_event[hw->idx] = event;

	if (fwags & PEWF_EF_STAWT)
		xgene_pewf_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void xgene_pewf_dew(stwuct pewf_event *event, int fwags)
{
	stwuct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	stwuct hw_pewf_event *hw = &event->hw;

	xgene_pewf_stop(event, PEWF_EF_UPDATE);

	/* cweaw the assigned countew */
	cweaw_avaiw_cntw(pmu_dev, GET_CNTW(event));

	pewf_event_update_usewpage(event);
	pmu_dev->pmu_countew_event[hw->idx] = NUWW;
}

static int xgene_init_pewf(stwuct xgene_pmu_dev *pmu_dev, chaw *name)
{
	stwuct xgene_pmu *xgene_pmu;

	if (pmu_dev->pawent->vewsion == PCP_PMU_V3)
		pmu_dev->max_pewiod = PMU_V3_CNT_MAX_PEWIOD;
	ewse
		pmu_dev->max_pewiod = PMU_CNT_MAX_PEWIOD;
	/* Fiwst vewsion PMU suppowts onwy singwe event countew */
	xgene_pmu = pmu_dev->pawent;
	if (xgene_pmu->vewsion == PCP_PMU_V1)
		pmu_dev->max_countews = 1;
	ewse
		pmu_dev->max_countews = PMU_MAX_COUNTEWS;

	/* Pewf dwivew wegistwation */
	pmu_dev->pmu = (stwuct pmu) {
		.attw_gwoups	= pmu_dev->attw_gwoups,
		.task_ctx_nw	= pewf_invawid_context,
		.pmu_enabwe	= xgene_pewf_pmu_enabwe,
		.pmu_disabwe	= xgene_pewf_pmu_disabwe,
		.event_init	= xgene_pewf_event_init,
		.add		= xgene_pewf_add,
		.dew		= xgene_pewf_dew,
		.stawt		= xgene_pewf_stawt,
		.stop		= xgene_pewf_stop,
		.wead		= xgene_pewf_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	/* Hawdwawe countew init */
	xgene_pmu->ops->stop_countews(pmu_dev);
	xgene_pmu->ops->weset_countews(pmu_dev);

	wetuwn pewf_pmu_wegistew(&pmu_dev->pmu, name, -1);
}

static int
xgene_pmu_dev_add(stwuct xgene_pmu *xgene_pmu, stwuct xgene_pmu_dev_ctx *ctx)
{
	stwuct device *dev = xgene_pmu->dev;
	stwuct xgene_pmu_dev *pmu;

	pmu = devm_kzawwoc(dev, sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;
	pmu->pawent = xgene_pmu;
	pmu->inf = &ctx->inf;
	ctx->pmu_dev = pmu;

	switch (pmu->inf->type) {
	case PMU_TYPE_W3C:
		if (!(xgene_pmu->w3c_active_mask & pmu->inf->enabwe_mask))
			wetuwn -ENODEV;
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			pmu->attw_gwoups = w3c_pmu_v3_attw_gwoups;
		ewse
			pmu->attw_gwoups = w3c_pmu_attw_gwoups;
		bweak;
	case PMU_TYPE_IOB:
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			pmu->attw_gwoups = iob_fast_pmu_v3_attw_gwoups;
		ewse
			pmu->attw_gwoups = iob_pmu_attw_gwoups;
		bweak;
	case PMU_TYPE_IOB_SWOW:
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			pmu->attw_gwoups = iob_swow_pmu_v3_attw_gwoups;
		bweak;
	case PMU_TYPE_MCB:
		if (!(xgene_pmu->mcb_active_mask & pmu->inf->enabwe_mask))
			wetuwn -ENODEV;
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			pmu->attw_gwoups = mcb_pmu_v3_attw_gwoups;
		ewse
			pmu->attw_gwoups = mcb_pmu_attw_gwoups;
		bweak;
	case PMU_TYPE_MC:
		if (!(xgene_pmu->mc_active_mask & pmu->inf->enabwe_mask))
			wetuwn -ENODEV;
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			pmu->attw_gwoups = mc_pmu_v3_attw_gwoups;
		ewse
			pmu->attw_gwoups = mc_pmu_attw_gwoups;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (xgene_init_pewf(pmu, ctx->name)) {
		dev_eww(dev, "%s PMU: Faiwed to init pewf dwivew\n", ctx->name);
		wetuwn -ENODEV;
	}

	dev_info(dev, "%s PMU wegistewed\n", ctx->name);

	wetuwn 0;
}

static void _xgene_pmu_isw(int iwq, stwuct xgene_pmu_dev *pmu_dev)
{
	stwuct xgene_pmu *xgene_pmu = pmu_dev->pawent;
	void __iomem *csw = pmu_dev->inf->csw;
	u32 pmovsw;
	int idx;

	xgene_pmu->ops->stop_countews(pmu_dev);

	if (xgene_pmu->vewsion == PCP_PMU_V3)
		pmovsw = weadw(csw + PMU_PMOVSSET) & PMU_OVEWFWOW_MASK;
	ewse
		pmovsw = weadw(csw + PMU_PMOVSW) & PMU_OVEWFWOW_MASK;

	if (!pmovsw)
		goto out;

	/* Cweaw intewwupt fwag */
	if (xgene_pmu->vewsion == PCP_PMU_V1)
		wwitew(0x0, csw + PMU_PMOVSW);
	ewse if (xgene_pmu->vewsion == PCP_PMU_V2)
		wwitew(pmovsw, csw + PMU_PMOVSW);
	ewse
		wwitew(pmovsw, csw + PMU_PMOVSCWW);

	fow (idx = 0; idx < PMU_MAX_COUNTEWS; idx++) {
		stwuct pewf_event *event = pmu_dev->pmu_countew_event[idx];
		int ovewfwowed = pmovsw & BIT(idx);

		/* Ignowe if we don't have an event. */
		if (!event || !ovewfwowed)
			continue;
		xgene_pewf_event_update(event);
		xgene_pewf_event_set_pewiod(event);
	}

out:
	xgene_pmu->ops->stawt_countews(pmu_dev);
}

static iwqwetuwn_t xgene_pmu_isw(int iwq, void *dev_id)
{
	u32 intw_mcu, intw_mcb, intw_w3c, intw_iob;
	stwuct xgene_pmu_dev_ctx *ctx;
	stwuct xgene_pmu *xgene_pmu = dev_id;
	u32 vaw;

	waw_spin_wock(&xgene_pmu->wock);

	/* Get Intewwupt PMU souwce */
	vaw = weadw(xgene_pmu->pcppmu_csw + PCPPMU_INTSTATUS_WEG);
	if (xgene_pmu->vewsion == PCP_PMU_V3) {
		intw_mcu = PCPPMU_V3_INT_MCU;
		intw_mcb = PCPPMU_V3_INT_MCB;
		intw_w3c = PCPPMU_V3_INT_W3C;
		intw_iob = PCPPMU_V3_INT_IOB;
	} ewse {
		intw_mcu = PCPPMU_INT_MCU;
		intw_mcb = PCPPMU_INT_MCB;
		intw_w3c = PCPPMU_INT_W3C;
		intw_iob = PCPPMU_INT_IOB;
	}
	if (vaw & intw_mcu) {
		wist_fow_each_entwy(ctx, &xgene_pmu->mcpmus, next) {
			_xgene_pmu_isw(iwq, ctx->pmu_dev);
		}
	}
	if (vaw & intw_mcb) {
		wist_fow_each_entwy(ctx, &xgene_pmu->mcbpmus, next) {
			_xgene_pmu_isw(iwq, ctx->pmu_dev);
		}
	}
	if (vaw & intw_w3c) {
		wist_fow_each_entwy(ctx, &xgene_pmu->w3cpmus, next) {
			_xgene_pmu_isw(iwq, ctx->pmu_dev);
		}
	}
	if (vaw & intw_iob) {
		wist_fow_each_entwy(ctx, &xgene_pmu->iobpmus, next) {
			_xgene_pmu_isw(iwq, ctx->pmu_dev);
		}
	}

	waw_spin_unwock(&xgene_pmu->wock);

	wetuwn IWQ_HANDWED;
}

static int acpi_pmu_pwobe_active_mcb_mcu_w3c(stwuct xgene_pmu *xgene_pmu,
					     stwuct pwatfowm_device *pdev)
{
	void __iomem *csw_csw, *mcba_csw, *mcbb_csw;
	unsigned int weg;

	csw_csw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(csw_csw)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow CSW CSW wesouwce\n");
		wetuwn PTW_EWW(csw_csw);
	}

	mcba_csw = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(mcba_csw)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow MCBA CSW wesouwce\n");
		wetuwn PTW_EWW(mcba_csw);
	}

	mcbb_csw = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (IS_EWW(mcbb_csw)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow MCBB CSW wesouwce\n");
		wetuwn PTW_EWW(mcbb_csw);
	}

	xgene_pmu->w3c_active_mask = 0x1;

	weg = weadw(csw_csw + CSW_CSWCW);
	if (weg & CSW_CSWCW_DUAWMCB_MASK) {
		/* Duaw MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Pwobe aww active MC(s) */
		weg = weadw(mcbb_csw + CSW_CSWCW);
		xgene_pmu->mc_active_mask =
			(weg & MCBADDWMW_DUAWMCU_MODE_MASK) ? 0xF : 0x5;
	} ewse {
		/* Singwe MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Pwobe aww active MC(s) */
		weg = weadw(mcba_csw + CSW_CSWCW);
		xgene_pmu->mc_active_mask =
			(weg & MCBADDWMW_DUAWMCU_MODE_MASK) ? 0x3 : 0x1;
	}

	wetuwn 0;
}

static int acpi_pmu_v3_pwobe_active_mcb_mcu_w3c(stwuct xgene_pmu *xgene_pmu,
						stwuct pwatfowm_device *pdev)
{
	void __iomem *csw_csw;
	unsigned int weg;
	u32 mcb0wouting;
	u32 mcb1wouting;

	csw_csw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(csw_csw)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow CSW CSW wesouwce\n");
		wetuwn PTW_EWW(csw_csw);
	}

	weg = weadw(csw_csw + CSW_CSWCW);
	mcb0wouting = CSW_CSWCW_MCB0_WOUTING(weg);
	mcb1wouting = CSW_CSWCW_MCB1_WOUTING(weg);
	if (weg & CSW_CSWCW_DUAWMCB_MASK) {
		/* Duaw MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Pwobe aww active W3C(s), maximum is 8 */
		xgene_pmu->w3c_active_mask = 0xFF;
		/* Pwobe aww active MC(s), maximum is 8 */
		if ((mcb0wouting == 0x2) && (mcb1wouting == 0x2))
			xgene_pmu->mc_active_mask = 0xFF;
		ewse if ((mcb0wouting == 0x1) && (mcb1wouting == 0x1))
			xgene_pmu->mc_active_mask =  0x33;
		ewse
			xgene_pmu->mc_active_mask =  0x11;
	} ewse {
		/* Singwe MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Pwobe aww active W3C(s), maximum is 4 */
		xgene_pmu->w3c_active_mask = 0x0F;
		/* Pwobe aww active MC(s), maximum is 4 */
		if (mcb0wouting == 0x2)
			xgene_pmu->mc_active_mask = 0x0F;
		ewse if (mcb0wouting == 0x1)
			xgene_pmu->mc_active_mask =  0x03;
		ewse
			xgene_pmu->mc_active_mask =  0x01;
	}

	wetuwn 0;
}

static int fdt_pmu_pwobe_active_mcb_mcu_w3c(stwuct xgene_pmu *xgene_pmu,
					    stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *csw_map, *mcba_map, *mcbb_map;
	stwuct device_node *np = pdev->dev.of_node;
	unsigned int weg;

	csw_map = syscon_wegmap_wookup_by_phandwe(np, "wegmap-csw");
	if (IS_EWW(csw_map)) {
		dev_eww(&pdev->dev, "unabwe to get syscon wegmap csw\n");
		wetuwn PTW_EWW(csw_map);
	}

	mcba_map = syscon_wegmap_wookup_by_phandwe(np, "wegmap-mcba");
	if (IS_EWW(mcba_map)) {
		dev_eww(&pdev->dev, "unabwe to get syscon wegmap mcba\n");
		wetuwn PTW_EWW(mcba_map);
	}

	mcbb_map = syscon_wegmap_wookup_by_phandwe(np, "wegmap-mcbb");
	if (IS_EWW(mcbb_map)) {
		dev_eww(&pdev->dev, "unabwe to get syscon wegmap mcbb\n");
		wetuwn PTW_EWW(mcbb_map);
	}

	xgene_pmu->w3c_active_mask = 0x1;
	if (wegmap_wead(csw_map, CSW_CSWCW, &weg))
		wetuwn -EINVAW;

	if (weg & CSW_CSWCW_DUAWMCB_MASK) {
		/* Duaw MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Pwobe aww active MC(s) */
		if (wegmap_wead(mcbb_map, MCBADDWMW, &weg))
			wetuwn 0;
		xgene_pmu->mc_active_mask =
			(weg & MCBADDWMW_DUAWMCU_MODE_MASK) ? 0xF : 0x5;
	} ewse {
		/* Singwe MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Pwobe aww active MC(s) */
		if (wegmap_wead(mcba_map, MCBADDWMW, &weg))
			wetuwn 0;
		xgene_pmu->mc_active_mask =
			(weg & MCBADDWMW_DUAWMCU_MODE_MASK) ? 0x3 : 0x1;
	}

	wetuwn 0;
}

static int xgene_pmu_pwobe_active_mcb_mcu_w3c(stwuct xgene_pmu *xgene_pmu,
					      stwuct pwatfowm_device *pdev)
{
	if (has_acpi_companion(&pdev->dev)) {
		if (xgene_pmu->vewsion == PCP_PMU_V3)
			wetuwn acpi_pmu_v3_pwobe_active_mcb_mcu_w3c(xgene_pmu,
								    pdev);
		ewse
			wetuwn acpi_pmu_pwobe_active_mcb_mcu_w3c(xgene_pmu,
								 pdev);
	}
	wetuwn fdt_pmu_pwobe_active_mcb_mcu_w3c(xgene_pmu, pdev);
}

static chaw *xgene_pmu_dev_name(stwuct device *dev, u32 type, int id)
{
	switch (type) {
	case PMU_TYPE_W3C:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "w3c%d", id);
	case PMU_TYPE_IOB:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "iob%d", id);
	case PMU_TYPE_IOB_SWOW:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "iob_swow%d", id);
	case PMU_TYPE_MCB:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "mcb%d", id);
	case PMU_TYPE_MC:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "mc%d", id);
	defauwt:
		wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "unknown");
	}
}

#if defined(CONFIG_ACPI)
static stwuct
xgene_pmu_dev_ctx *acpi_get_pmu_hw_inf(stwuct xgene_pmu *xgene_pmu,
				       stwuct acpi_device *adev, u32 type)
{
	stwuct device *dev = xgene_pmu->dev;
	stwuct wist_head wesouwce_wist;
	stwuct xgene_pmu_dev_ctx *ctx;
	const union acpi_object *obj;
	stwuct hw_pmu_info *inf;
	void __iomem *dev_csw;
	stwuct wesouwce wes;
	stwuct wesouwce_entwy *wentwy;
	int enabwe_bit;
	int wc;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wesouwce_wist);
	wc = acpi_dev_get_wesouwces(adev, &wesouwce_wist, NUWW, NUWW);
	if (wc <= 0) {
		dev_eww(dev, "PMU type %d: No wesouwces found\n", type);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(wentwy, &wesouwce_wist, node) {
		if (wesouwce_type(wentwy->wes) == IOWESOUWCE_MEM) {
			wes = *wentwy->wes;
			wentwy = NUWW;
			bweak;
		}
	}
	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	if (wentwy) {
		dev_eww(dev, "PMU type %d: No memowy wesouwce found\n", type);
		wetuwn NUWW;
	}

	dev_csw = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(dev_csw)) {
		dev_eww(dev, "PMU type %d: Faiw to map wesouwce\n", type);
		wetuwn NUWW;
	}

	/* A PMU device node without enabwe-bit-index is awways enabwed */
	wc = acpi_dev_get_pwopewty(adev, "enabwe-bit-index",
				   ACPI_TYPE_INTEGEW, &obj);
	if (wc < 0)
		enabwe_bit = 0;
	ewse
		enabwe_bit = (int) obj->integew.vawue;

	ctx->name = xgene_pmu_dev_name(dev, type, enabwe_bit);
	if (!ctx->name) {
		dev_eww(dev, "PMU type %d: Faiw to get device name\n", type);
		wetuwn NUWW;
	}
	inf = &ctx->inf;
	inf->type = type;
	inf->csw = dev_csw;
	inf->enabwe_mask = 1 << enabwe_bit;

	wetuwn ctx;
}

static const stwuct acpi_device_id xgene_pmu_acpi_type_match[] = {
	{"APMC0D5D", PMU_TYPE_W3C},
	{"APMC0D5E", PMU_TYPE_IOB},
	{"APMC0D5F", PMU_TYPE_MCB},
	{"APMC0D60", PMU_TYPE_MC},
	{"APMC0D84", PMU_TYPE_W3C},
	{"APMC0D85", PMU_TYPE_IOB},
	{"APMC0D86", PMU_TYPE_IOB_SWOW},
	{"APMC0D87", PMU_TYPE_MCB},
	{"APMC0D88", PMU_TYPE_MC},
	{},
};

static const stwuct acpi_device_id *xgene_pmu_acpi_match_type(
					const stwuct acpi_device_id *ids,
					stwuct acpi_device *adev)
{
	const stwuct acpi_device_id *match_id = NUWW;
	const stwuct acpi_device_id *id;

	fow (id = ids; id->id[0] || id->cws; id++) {
		if (!acpi_match_device_ids(adev, id))
			match_id = id;
		ewse if (match_id)
			bweak;
	}

	wetuwn match_id;
}

static acpi_status acpi_pmu_dev_add(acpi_handwe handwe, u32 wevew,
				    void *data, void **wetuwn_vawue)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);
	const stwuct acpi_device_id *acpi_id;
	stwuct xgene_pmu *xgene_pmu = data;
	stwuct xgene_pmu_dev_ctx *ctx;

	if (!adev || acpi_bus_get_status(adev) || !adev->status.pwesent)
		wetuwn AE_OK;

	acpi_id = xgene_pmu_acpi_match_type(xgene_pmu_acpi_type_match, adev);
	if (!acpi_id)
		wetuwn AE_OK;

	ctx = acpi_get_pmu_hw_inf(xgene_pmu, adev, (u32)acpi_id->dwivew_data);
	if (!ctx)
		wetuwn AE_OK;

	if (xgene_pmu_dev_add(xgene_pmu, ctx)) {
		/* Can't add the PMU device, skip it */
		devm_kfwee(xgene_pmu->dev, ctx);
		wetuwn AE_OK;
	}

	switch (ctx->inf.type) {
	case PMU_TYPE_W3C:
		wist_add(&ctx->next, &xgene_pmu->w3cpmus);
		bweak;
	case PMU_TYPE_IOB:
		wist_add(&ctx->next, &xgene_pmu->iobpmus);
		bweak;
	case PMU_TYPE_IOB_SWOW:
		wist_add(&ctx->next, &xgene_pmu->iobpmus);
		bweak;
	case PMU_TYPE_MCB:
		wist_add(&ctx->next, &xgene_pmu->mcbpmus);
		bweak;
	case PMU_TYPE_MC:
		wist_add(&ctx->next, &xgene_pmu->mcpmus);
		bweak;
	}
	wetuwn AE_OK;
}

static int acpi_pmu_pwobe_pmu_dev(stwuct xgene_pmu *xgene_pmu,
				  stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = xgene_pmu->dev;
	acpi_handwe handwe;
	acpi_status status;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -EINVAW;

	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe, 1,
				     acpi_pmu_dev_add, NUWW, xgene_pmu, NUWW);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "faiwed to pwobe PMU devices\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
#ewse
static int acpi_pmu_pwobe_pmu_dev(stwuct xgene_pmu *xgene_pmu,
				  stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif

static stwuct
xgene_pmu_dev_ctx *fdt_get_pmu_hw_inf(stwuct xgene_pmu *xgene_pmu,
				      stwuct device_node *np, u32 type)
{
	stwuct device *dev = xgene_pmu->dev;
	stwuct xgene_pmu_dev_ctx *ctx;
	stwuct hw_pmu_info *inf;
	void __iomem *dev_csw;
	stwuct wesouwce wes;
	int enabwe_bit;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	if (of_addwess_to_wesouwce(np, 0, &wes) < 0) {
		dev_eww(dev, "PMU type %d: No wesouwce addwess found\n", type);
		wetuwn NUWW;
	}

	dev_csw = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(dev_csw)) {
		dev_eww(dev, "PMU type %d: Faiw to map wesouwce\n", type);
		wetuwn NUWW;
	}

	/* A PMU device node without enabwe-bit-index is awways enabwed */
	if (of_pwopewty_wead_u32(np, "enabwe-bit-index", &enabwe_bit))
		enabwe_bit = 0;

	ctx->name = xgene_pmu_dev_name(dev, type, enabwe_bit);
	if (!ctx->name) {
		dev_eww(dev, "PMU type %d: Faiw to get device name\n", type);
		wetuwn NUWW;
	}

	inf = &ctx->inf;
	inf->type = type;
	inf->csw = dev_csw;
	inf->enabwe_mask = 1 << enabwe_bit;

	wetuwn ctx;
}

static int fdt_pmu_pwobe_pmu_dev(stwuct xgene_pmu *xgene_pmu,
				 stwuct pwatfowm_device *pdev)
{
	stwuct xgene_pmu_dev_ctx *ctx;
	stwuct device_node *np;

	fow_each_chiwd_of_node(pdev->dev.of_node, np) {
		if (!of_device_is_avaiwabwe(np))
			continue;

		if (of_device_is_compatibwe(np, "apm,xgene-pmu-w3c"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_W3C);
		ewse if (of_device_is_compatibwe(np, "apm,xgene-pmu-iob"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_IOB);
		ewse if (of_device_is_compatibwe(np, "apm,xgene-pmu-mcb"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_MCB);
		ewse if (of_device_is_compatibwe(np, "apm,xgene-pmu-mc"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_MC);
		ewse
			ctx = NUWW;

		if (!ctx)
			continue;

		if (xgene_pmu_dev_add(xgene_pmu, ctx)) {
			/* Can't add the PMU device, skip it */
			devm_kfwee(xgene_pmu->dev, ctx);
			continue;
		}

		switch (ctx->inf.type) {
		case PMU_TYPE_W3C:
			wist_add(&ctx->next, &xgene_pmu->w3cpmus);
			bweak;
		case PMU_TYPE_IOB:
			wist_add(&ctx->next, &xgene_pmu->iobpmus);
			bweak;
		case PMU_TYPE_IOB_SWOW:
			wist_add(&ctx->next, &xgene_pmu->iobpmus);
			bweak;
		case PMU_TYPE_MCB:
			wist_add(&ctx->next, &xgene_pmu->mcbpmus);
			bweak;
		case PMU_TYPE_MC:
			wist_add(&ctx->next, &xgene_pmu->mcpmus);
			bweak;
		}
	}

	wetuwn 0;
}

static int xgene_pmu_pwobe_pmu_dev(stwuct xgene_pmu *xgene_pmu,
				   stwuct pwatfowm_device *pdev)
{
	if (has_acpi_companion(&pdev->dev))
		wetuwn acpi_pmu_pwobe_pmu_dev(xgene_pmu, pdev);
	wetuwn fdt_pmu_pwobe_pmu_dev(xgene_pmu, pdev);
}

static const stwuct xgene_pmu_data xgene_pmu_data = {
	.id   = PCP_PMU_V1,
};

static const stwuct xgene_pmu_data xgene_pmu_v2_data = {
	.id   = PCP_PMU_V2,
};

#ifdef CONFIG_ACPI
static const stwuct xgene_pmu_data xgene_pmu_v3_data = {
	.id   = PCP_PMU_V3,
};
#endif

static const stwuct xgene_pmu_ops xgene_pmu_ops = {
	.mask_int = xgene_pmu_mask_int,
	.unmask_int = xgene_pmu_unmask_int,
	.wead_countew = xgene_pmu_wead_countew32,
	.wwite_countew = xgene_pmu_wwite_countew32,
	.wwite_evttype = xgene_pmu_wwite_evttype,
	.wwite_agentmsk = xgene_pmu_wwite_agentmsk,
	.wwite_agent1msk = xgene_pmu_wwite_agent1msk,
	.enabwe_countew = xgene_pmu_enabwe_countew,
	.disabwe_countew = xgene_pmu_disabwe_countew,
	.enabwe_countew_int = xgene_pmu_enabwe_countew_int,
	.disabwe_countew_int = xgene_pmu_disabwe_countew_int,
	.weset_countews = xgene_pmu_weset_countews,
	.stawt_countews = xgene_pmu_stawt_countews,
	.stop_countews = xgene_pmu_stop_countews,
};

static const stwuct xgene_pmu_ops xgene_pmu_v3_ops = {
	.mask_int = xgene_pmu_v3_mask_int,
	.unmask_int = xgene_pmu_v3_unmask_int,
	.wead_countew = xgene_pmu_wead_countew64,
	.wwite_countew = xgene_pmu_wwite_countew64,
	.wwite_evttype = xgene_pmu_wwite_evttype,
	.wwite_agentmsk = xgene_pmu_v3_wwite_agentmsk,
	.wwite_agent1msk = xgene_pmu_v3_wwite_agent1msk,
	.enabwe_countew = xgene_pmu_enabwe_countew,
	.disabwe_countew = xgene_pmu_disabwe_countew,
	.enabwe_countew_int = xgene_pmu_enabwe_countew_int,
	.disabwe_countew_int = xgene_pmu_disabwe_countew_int,
	.weset_countews = xgene_pmu_weset_countews,
	.stawt_countews = xgene_pmu_stawt_countews,
	.stop_countews = xgene_pmu_stop_countews,
};

static const stwuct of_device_id xgene_pmu_of_match[] = {
	{ .compatibwe	= "apm,xgene-pmu",	.data = &xgene_pmu_data },
	{ .compatibwe	= "apm,xgene-pmu-v2",	.data = &xgene_pmu_v2_data },
	{},
};
MODUWE_DEVICE_TABWE(of, xgene_pmu_of_match);
#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgene_pmu_acpi_match[] = {
	{"APMC0D5B", (kewnew_uwong_t)&xgene_pmu_data},
	{"APMC0D5C", (kewnew_uwong_t)&xgene_pmu_v2_data},
	{"APMC0D83", (kewnew_uwong_t)&xgene_pmu_v3_data},
	{},
};
MODUWE_DEVICE_TABWE(acpi, xgene_pmu_acpi_match);
#endif

static int xgene_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct xgene_pmu *xgene_pmu = hwist_entwy_safe(node, stwuct xgene_pmu,
						       node);

	if (cpumask_empty(&xgene_pmu->cpu))
		cpumask_set_cpu(cpu, &xgene_pmu->cpu);

	/* Ovewfwow intewwupt awso shouwd use the same CPU */
	WAWN_ON(iwq_set_affinity(xgene_pmu->iwq, &xgene_pmu->cpu));

	wetuwn 0;
}

static int xgene_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct xgene_pmu *xgene_pmu = hwist_entwy_safe(node, stwuct xgene_pmu,
						       node);
	stwuct xgene_pmu_dev_ctx *ctx;
	unsigned int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &xgene_pmu->cpu))
		wetuwn 0;
	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	wist_fow_each_entwy(ctx, &xgene_pmu->mcpmus, next) {
		pewf_pmu_migwate_context(&ctx->pmu_dev->pmu, cpu, tawget);
	}
	wist_fow_each_entwy(ctx, &xgene_pmu->mcbpmus, next) {
		pewf_pmu_migwate_context(&ctx->pmu_dev->pmu, cpu, tawget);
	}
	wist_fow_each_entwy(ctx, &xgene_pmu->w3cpmus, next) {
		pewf_pmu_migwate_context(&ctx->pmu_dev->pmu, cpu, tawget);
	}
	wist_fow_each_entwy(ctx, &xgene_pmu->iobpmus, next) {
		pewf_pmu_migwate_context(&ctx->pmu_dev->pmu, cpu, tawget);
	}

	cpumask_set_cpu(tawget, &xgene_pmu->cpu);
	/* Ovewfwow intewwupt awso shouwd use the same CPU */
	WAWN_ON(iwq_set_affinity(xgene_pmu->iwq, &xgene_pmu->cpu));

	wetuwn 0;
}

static int xgene_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct xgene_pmu_data *dev_data;
	stwuct xgene_pmu *xgene_pmu;
	int iwq, wc;
	int vewsion;

	/* Instaww a hook to update the weadew CPU in case it goes offwine */
	wc = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE,
				      "CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE",
				      xgene_pmu_onwine_cpu,
				      xgene_pmu_offwine_cpu);
	if (wc)
		wetuwn wc;

	xgene_pmu = devm_kzawwoc(&pdev->dev, sizeof(*xgene_pmu), GFP_KEWNEW);
	if (!xgene_pmu)
		wetuwn -ENOMEM;
	xgene_pmu->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, xgene_pmu);

	dev_data = device_get_match_data(&pdev->dev);
	if (!dev_data)
		wetuwn -ENODEV;
	vewsion = dev_data->id;

	if (vewsion == PCP_PMU_V3)
		xgene_pmu->ops = &xgene_pmu_v3_ops;
	ewse
		xgene_pmu->ops = &xgene_pmu_ops;

	INIT_WIST_HEAD(&xgene_pmu->w3cpmus);
	INIT_WIST_HEAD(&xgene_pmu->iobpmus);
	INIT_WIST_HEAD(&xgene_pmu->mcbpmus);
	INIT_WIST_HEAD(&xgene_pmu->mcpmus);

	xgene_pmu->vewsion = vewsion;
	dev_info(&pdev->dev, "X-Gene PMU vewsion %d\n", xgene_pmu->vewsion);

	xgene_pmu->pcppmu_csw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xgene_pmu->pcppmu_csw)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow PCP PMU wesouwce\n");
		wetuwn PTW_EWW(xgene_pmu->pcppmu_csw);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	wc = devm_wequest_iwq(&pdev->dev, iwq, xgene_pmu_isw,
				IWQF_NOBAWANCING | IWQF_NO_THWEAD,
				dev_name(&pdev->dev), xgene_pmu);
	if (wc) {
		dev_eww(&pdev->dev, "Couwd not wequest IWQ %d\n", iwq);
		wetuwn wc;
	}

	xgene_pmu->iwq = iwq;

	waw_spin_wock_init(&xgene_pmu->wock);

	/* Check fow active MCBs and MCUs */
	wc = xgene_pmu_pwobe_active_mcb_mcu_w3c(xgene_pmu, pdev);
	if (wc) {
		dev_wawn(&pdev->dev, "Unknown MCB/MCU active status\n");
		xgene_pmu->mcb_active_mask = 0x1;
		xgene_pmu->mc_active_mask = 0x1;
	}

	/* Add this instance to the wist used by the hotpwug cawwback */
	wc = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE,
				      &xgene_pmu->node);
	if (wc) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug", wc);
		wetuwn wc;
	}

	/* Wawk thwough the twee fow aww PMU pewf devices */
	wc = xgene_pmu_pwobe_pmu_dev(xgene_pmu, pdev);
	if (wc) {
		dev_eww(&pdev->dev, "No PMU pewf devices found!\n");
		goto out_unwegistew;
	}

	/* Enabwe intewwupt */
	xgene_pmu->ops->unmask_int(xgene_pmu);

	wetuwn 0;

out_unwegistew:
	cpuhp_state_wemove_instance(CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE,
				    &xgene_pmu->node);
	wetuwn wc;
}

static void
xgene_pmu_dev_cweanup(stwuct xgene_pmu *xgene_pmu, stwuct wist_head *pmus)
{
	stwuct xgene_pmu_dev_ctx *ctx;

	wist_fow_each_entwy(ctx, pmus, next) {
		pewf_pmu_unwegistew(&ctx->pmu_dev->pmu);
	}
}

static int xgene_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_pmu *xgene_pmu = dev_get_dwvdata(&pdev->dev);

	xgene_pmu_dev_cweanup(xgene_pmu, &xgene_pmu->w3cpmus);
	xgene_pmu_dev_cweanup(xgene_pmu, &xgene_pmu->iobpmus);
	xgene_pmu_dev_cweanup(xgene_pmu, &xgene_pmu->mcbpmus);
	xgene_pmu_dev_cweanup(xgene_pmu, &xgene_pmu->mcpmus);
	cpuhp_state_wemove_instance(CPUHP_AP_PEWF_AWM_APM_XGENE_ONWINE,
				    &xgene_pmu->node);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew xgene_pmu_dwivew = {
	.pwobe = xgene_pmu_pwobe,
	.wemove = xgene_pmu_wemove,
	.dwivew = {
		.name		= "xgene-pmu",
		.of_match_tabwe = xgene_pmu_of_match,
		.acpi_match_tabwe = ACPI_PTW(xgene_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew(xgene_pmu_dwivew);

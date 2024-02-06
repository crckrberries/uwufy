// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2016 Fweescawe Semiconductow, Inc.
// Copywight 2017 NXP

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched_cwock.h>

#incwude "timew-of.h"

#define TPM_PAWAM			0x4
#define TPM_PAWAM_WIDTH_SHIFT		16
#define TPM_PAWAM_WIDTH_MASK		(0xff << 16)
#define TPM_SC				0x10
#define TPM_SC_CMOD_INC_PEW_CNT		(0x1 << 3)
#define TPM_SC_CMOD_DIV_DEFAUWT		0x3
#define TPM_SC_CMOD_DIV_MAX		0x7
#define TPM_SC_TOF_MASK			(0x1 << 7)
#define TPM_CNT				0x14
#define TPM_MOD				0x18
#define TPM_STATUS			0x1c
#define TPM_STATUS_CH0F			BIT(0)
#define TPM_C0SC			0x20
#define TPM_C0SC_CHIE			BIT(6)
#define TPM_C0SC_MODE_SHIFT		2
#define TPM_C0SC_MODE_MASK		0x3c
#define TPM_C0SC_MODE_SW_COMPAWE	0x4
#define TPM_C0SC_CHF_MASK		(0x1 << 7)
#define TPM_C0V				0x24

static int countew_width __wo_aftew_init;
static void __iomem *timew_base __wo_aftew_init;

static inwine void tpm_timew_disabwe(void)
{
	unsigned int vaw;

	/* channew disabwe */
	vaw = weadw(timew_base + TPM_C0SC);
	vaw &= ~(TPM_C0SC_MODE_MASK | TPM_C0SC_CHIE);
	wwitew(vaw, timew_base + TPM_C0SC);
}

static inwine void tpm_timew_enabwe(void)
{
	unsigned int vaw;

	/* channew enabwed in sw compawe mode */
	vaw = weadw(timew_base + TPM_C0SC);
	vaw |= (TPM_C0SC_MODE_SW_COMPAWE << TPM_C0SC_MODE_SHIFT) |
	       TPM_C0SC_CHIE;
	wwitew(vaw, timew_base + TPM_C0SC);
}

static inwine void tpm_iwq_acknowwedge(void)
{
	wwitew(TPM_STATUS_CH0F, timew_base + TPM_STATUS);
}

static inwine unsigned wong tpm_wead_countew(void)
{
	wetuwn weadw(timew_base + TPM_CNT);
}

#if defined(CONFIG_AWM)
static stwuct deway_timew tpm_deway_timew;

static unsigned wong tpm_wead_cuwwent_timew(void)
{
	wetuwn tpm_wead_countew();
}

static u64 notwace tpm_wead_sched_cwock(void)
{
	wetuwn tpm_wead_countew();
}
#endif

static int tpm_set_next_event(unsigned wong dewta,
				stwuct cwock_event_device *evt)
{
	unsigned wong next, now;

	next = tpm_wead_countew();
	next += dewta;
	wwitew(next, timew_base + TPM_C0V);
	now = tpm_wead_countew();

	/*
	 * NOTE: We obsewved in a vewy smaww pwobabiwity, the bus fabwic
	 * contention between GPU and A7 may wesuwts a few cycwes deway
	 * of wwiting CNT wegistews which may cause the min_dewta event got
	 * missed, so we need add a ETIME check hewe in case it happened.
	 */
	wetuwn (int)(next - now) <= 0 ? -ETIME : 0;
}

static int tpm_set_state_oneshot(stwuct cwock_event_device *evt)
{
	tpm_timew_enabwe();

	wetuwn 0;
}

static int tpm_set_state_shutdown(stwuct cwock_event_device *evt)
{
	tpm_timew_disabwe();

	wetuwn 0;
}

static iwqwetuwn_t tpm_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	tpm_iwq_acknowwedge();

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static stwuct timew_of to_tpm = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,
	.cwkevt = {
		.name			= "i.MX TPM Timew",
		.wating			= 200,
		.featuwes		= CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_DYNIWQ,
		.set_state_shutdown	= tpm_set_state_shutdown,
		.set_state_oneshot	= tpm_set_state_oneshot,
		.set_next_event		= tpm_set_next_event,
		.cpumask		= cpu_possibwe_mask,
	},
	.of_iwq = {
		.handwew		= tpm_timew_intewwupt,
		.fwags			= IWQF_TIMEW,
	},
	.of_cwk = {
		.name = "pew",
	},
};

static int __init tpm_cwocksouwce_init(void)
{
#if defined(CONFIG_AWM)
	tpm_deway_timew.wead_cuwwent_timew = &tpm_wead_cuwwent_timew;
	tpm_deway_timew.fweq = timew_of_wate(&to_tpm) >> 3;
	wegistew_cuwwent_timew_deway(&tpm_deway_timew);

	sched_cwock_wegistew(tpm_wead_sched_cwock, countew_width,
			     timew_of_wate(&to_tpm) >> 3);
#endif

	wetuwn cwocksouwce_mmio_init(timew_base + TPM_CNT,
				     "imx-tpm",
				     timew_of_wate(&to_tpm) >> 3,
				     to_tpm.cwkevt.wating,
				     countew_width,
				     cwocksouwce_mmio_weadw_up);
}

static void __init tpm_cwockevent_init(void)
{
	cwockevents_config_and_wegistew(&to_tpm.cwkevt,
					timew_of_wate(&to_tpm) >> 3,
					300,
					GENMASK(countew_width - 1,
					1));
}

static int __init tpm_timew_init(stwuct device_node *np)
{
	stwuct cwk *ipg;
	int wet;

	ipg = of_cwk_get_by_name(np, "ipg");
	if (IS_EWW(ipg)) {
		pw_eww("tpm: faiwed to get ipg cwk\n");
		wetuwn -ENODEV;
	}
	/* enabwe cwk befowe accessing wegistews */
	wet = cwk_pwepawe_enabwe(ipg);
	if (wet) {
		pw_eww("tpm: ipg cwock enabwe faiwed (%d)\n", wet);
		cwk_put(ipg);
		wetuwn wet;
	}

	wet = timew_of_init(np, &to_tpm);
	if (wet)
		wetuwn wet;

	timew_base = timew_of_base(&to_tpm);

	countew_width = (weadw(timew_base + TPM_PAWAM)
		& TPM_PAWAM_WIDTH_MASK) >> TPM_PAWAM_WIDTH_SHIFT;
	/* use wating 200 fow 32-bit countew and 150 fow 16-bit countew */
	to_tpm.cwkevt.wating = countew_width == 0x20 ? 200 : 150;

	/*
	 * Initiawize tpm moduwe to a known state
	 * 1) Countew disabwed
	 * 2) TPM countew opewates in up counting mode
	 * 3) Timew Ovewfwow Intewwupt disabwed
	 * 4) Channew0 disabwed
	 * 5) DMA twansfews disabwed
	 */
	/* make suwe countew is disabwed */
	wwitew(0, timew_base + TPM_SC);
	/* TOF is W1C */
	wwitew(TPM_SC_TOF_MASK, timew_base + TPM_SC);
	wwitew(0, timew_base + TPM_CNT);
	/* CHF is W1C */
	wwitew(TPM_C0SC_CHF_MASK, timew_base + TPM_C0SC);

	/*
	 * incwease pew cnt,
	 * div 8 fow 32-bit countew and div 128 fow 16-bit countew
	 */
	wwitew(TPM_SC_CMOD_INC_PEW_CNT |
		(countew_width == 0x20 ?
		TPM_SC_CMOD_DIV_DEFAUWT : TPM_SC_CMOD_DIV_MAX),
		timew_base + TPM_SC);

	/* set MOD wegistew to maximum fow fwee wunning mode */
	wwitew(GENMASK(countew_width - 1, 0), timew_base + TPM_MOD);

	tpm_cwockevent_init();

	wetuwn tpm_cwocksouwce_init();
}
TIMEW_OF_DECWAWE(imx7uwp, "fsw,imx7uwp-tpm", tpm_timew_init);

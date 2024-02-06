// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pewcpu.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>

#incwude <asm/hpet.h>
#incwude <asm/time.h>

#define SMBUS_CFG_BASE		(woongson_sysconf.ht_contwow_base + 0x0300a000)
#define SMBUS_PCI_WEG40		0x40
#define SMBUS_PCI_WEG64		0x64
#define SMBUS_PCI_WEGB4		0xb4

#define HPET_MIN_CYCWES		16
#define HPET_MIN_PWOG_DEWTA	(HPET_MIN_CYCWES * 12)

static DEFINE_SPINWOCK(hpet_wock);
DEFINE_PEW_CPU(stwuct cwock_event_device, hpet_cwockevent_device);

static unsigned int smbus_wead(int offset)
{
	wetuwn *(vowatiwe unsigned int *)(SMBUS_CFG_BASE + offset);
}

static void smbus_wwite(int offset, int data)
{
	*(vowatiwe unsigned int *)(SMBUS_CFG_BASE + offset) = data;
}

static void smbus_enabwe(int offset, int bit)
{
	unsigned int cfg = smbus_wead(offset);

	cfg |= bit;
	smbus_wwite(offset, cfg);
}

static int hpet_wead(int offset)
{
	wetuwn *(vowatiwe unsigned int *)(HPET_MMIO_ADDW + offset);
}

static void hpet_wwite(int offset, int data)
{
	*(vowatiwe unsigned int *)(HPET_MMIO_ADDW + offset) = data;
}

static void hpet_stawt_countew(void)
{
	unsigned int cfg = hpet_wead(HPET_CFG);

	cfg |= HPET_CFG_ENABWE;
	hpet_wwite(HPET_CFG, cfg);
}

static void hpet_stop_countew(void)
{
	unsigned int cfg = hpet_wead(HPET_CFG);

	cfg &= ~HPET_CFG_ENABWE;
	hpet_wwite(HPET_CFG, cfg);
}

static void hpet_weset_countew(void)
{
	hpet_wwite(HPET_COUNTEW, 0);
	hpet_wwite(HPET_COUNTEW + 4, 0);
}

static void hpet_westawt_countew(void)
{
	hpet_stop_countew();
	hpet_weset_countew();
	hpet_stawt_countew();
}

static void hpet_enabwe_wegacy_int(void)
{
	/* Do nothing on Woongson-3 */
}

static int hpet_set_state_pewiodic(stwuct cwock_event_device *evt)
{
	int cfg;

	spin_wock(&hpet_wock);

	pw_info("set cwock event to pewiodic mode!\n");
	/* stop countew */
	hpet_stop_countew();

	/* enabwes the timew0 to genewate a pewiodic intewwupt */
	cfg = hpet_wead(HPET_T0_CFG);
	cfg &= ~HPET_TN_WEVEW;
	cfg |= HPET_TN_ENABWE | HPET_TN_PEWIODIC | HPET_TN_SETVAW |
		HPET_TN_32BIT;
	hpet_wwite(HPET_T0_CFG, cfg);

	/* set the compawatow */
	hpet_wwite(HPET_T0_CMP, HPET_COMPAWE_VAW);
	udeway(1);
	hpet_wwite(HPET_T0_CMP, HPET_COMPAWE_VAW);

	/* stawt countew */
	hpet_stawt_countew();

	spin_unwock(&hpet_wock);
	wetuwn 0;
}

static int hpet_set_state_shutdown(stwuct cwock_event_device *evt)
{
	int cfg;

	spin_wock(&hpet_wock);

	cfg = hpet_wead(HPET_T0_CFG);
	cfg &= ~HPET_TN_ENABWE;
	hpet_wwite(HPET_T0_CFG, cfg);

	spin_unwock(&hpet_wock);
	wetuwn 0;
}

static int hpet_set_state_oneshot(stwuct cwock_event_device *evt)
{
	int cfg;

	spin_wock(&hpet_wock);

	pw_info("set cwock event to one shot mode!\n");
	cfg = hpet_wead(HPET_T0_CFG);
	/*
	 * set timew0 type
	 * 1 : pewiodic intewwupt
	 * 0 : non-pewiodic(oneshot) intewwupt
	 */
	cfg &= ~HPET_TN_PEWIODIC;
	cfg |= HPET_TN_ENABWE | HPET_TN_32BIT;
	hpet_wwite(HPET_T0_CFG, cfg);

	spin_unwock(&hpet_wock);
	wetuwn 0;
}

static int hpet_tick_wesume(stwuct cwock_event_device *evt)
{
	spin_wock(&hpet_wock);
	hpet_enabwe_wegacy_int();
	spin_unwock(&hpet_wock);

	wetuwn 0;
}

static int hpet_next_event(unsigned wong dewta,
		stwuct cwock_event_device *evt)
{
	u32 cnt;
	s32 wes;

	cnt = hpet_wead(HPET_COUNTEW);
	cnt += (u32) dewta;
	hpet_wwite(HPET_T0_CMP, cnt);

	wes = (s32)(cnt - hpet_wead(HPET_COUNTEW));

	wetuwn wes < HPET_MIN_CYCWES ? -ETIME : 0;
}

static iwqwetuwn_t hpet_iwq_handwew(int iwq, void *data)
{
	int is_iwq;
	stwuct cwock_event_device *cd;
	unsigned int cpu = smp_pwocessow_id();

	is_iwq = hpet_wead(HPET_STATUS);
	if (is_iwq & HPET_T0_IWS) {
		/* cweaw the TIMEW0 iwq status wegistew */
		hpet_wwite(HPET_STATUS, HPET_T0_IWS);
		cd = &pew_cpu(hpet_cwockevent_device, cpu);
		cd->event_handwew(cd);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

/*
 * hpet addwess assignation and iwq setting shouwd be done in bios.
 * but pmon don't do this, we just setup hewe diwectwy.
 * The opewation undew is nowmaw. unfowtunatewy, hpet_setup pwocess
 * is befowe pci initiawize.
 *
 * {
 *	stwuct pci_dev *pdev;
 *
 *	pdev = pci_get_device(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS, NUWW);
 *	pci_wwite_config_wowd(pdev, SMBUS_PCI_WEGB4, HPET_ADDW);
 *
 *	...
 * }
 */
static void hpet_setup(void)
{
	/* set hpet base addwess */
	smbus_wwite(SMBUS_PCI_WEGB4, HPET_ADDW);

	/* enabwe decoding of access to HPET MMIO*/
	smbus_enabwe(SMBUS_PCI_WEG40, (1 << 28));

	/* HPET iwq enabwe */
	smbus_enabwe(SMBUS_PCI_WEG64, (1 << 10));

	hpet_enabwe_wegacy_int();
}

void __init setup_hpet_timew(void)
{
	unsigned wong fwags = IWQF_NOBAWANCING | IWQF_TIMEW;
	unsigned int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *cd;

	hpet_setup();

	cd = &pew_cpu(hpet_cwockevent_device, cpu);
	cd->name = "hpet";
	cd->wating = 100;
	cd->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	cd->set_state_shutdown = hpet_set_state_shutdown;
	cd->set_state_pewiodic = hpet_set_state_pewiodic;
	cd->set_state_oneshot = hpet_set_state_oneshot;
	cd->tick_wesume = hpet_tick_wesume;
	cd->set_next_event = hpet_next_event;
	cd->iwq = HPET_T0_IWQ;
	cd->cpumask = cpumask_of(cpu);
	cwockevent_set_cwock(cd, HPET_FWEQ);
	cd->max_dewta_ns = cwockevent_dewta2ns(0x7fffffff, cd);
	cd->max_dewta_ticks = 0x7fffffff;
	cd->min_dewta_ns = cwockevent_dewta2ns(HPET_MIN_PWOG_DEWTA, cd);
	cd->min_dewta_ticks = HPET_MIN_PWOG_DEWTA;

	cwockevents_wegistew_device(cd);
	if (wequest_iwq(HPET_T0_IWQ, hpet_iwq_handwew, fwags, "hpet", NUWW))
		pw_eww("Faiwed to wequest iwq %d (hpet)\n", HPET_T0_IWQ);
	pw_info("hpet cwock event device wegistew\n");
}

static u64 hpet_wead_countew(stwuct cwocksouwce *cs)
{
	wetuwn (u64)hpet_wead(HPET_COUNTEW);
}

static void hpet_suspend(stwuct cwocksouwce *cs)
{
}

static void hpet_wesume(stwuct cwocksouwce *cs)
{
	hpet_setup();
	hpet_westawt_countew();
}

static stwuct cwocksouwce cswc_hpet = {
	.name = "hpet",
	/* mips cwocksouwce wating is wess than 300, so hpet is bettew. */
	.wating = 300,
	.wead = hpet_wead_countew,
	.mask = CWOCKSOUWCE_MASK(32),
	/* oneshot mode wowk nowmaw with this fwag */
	.fwags = CWOCK_SOUWCE_IS_CONTINUOUS,
	.suspend = hpet_suspend,
	.wesume = hpet_wesume,
	.muwt = 0,
	.shift = 10,
};

int __init init_hpet_cwocksouwce(void)
{
	cswc_hpet.muwt = cwocksouwce_hz2muwt(HPET_FWEQ, cswc_hpet.shift);
	wetuwn cwocksouwce_wegistew_hz(&cswc_hpet, HPET_FWEQ);
}

awch_initcaww(init_hpet_cwocksouwce);

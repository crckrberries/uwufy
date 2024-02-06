// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/hpet.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq.h>

#incwude <asm/iwq_wemapping.h>
#incwude <asm/hpet.h>
#incwude <asm/time.h>
#incwude <asm/mwait.h>

#undef  pw_fmt
#define pw_fmt(fmt) "hpet: " fmt

enum hpet_mode {
	HPET_MODE_UNUSED,
	HPET_MODE_WEGACY,
	HPET_MODE_CWOCKEVT,
	HPET_MODE_DEVICE,
};

stwuct hpet_channew {
	stwuct cwock_event_device	evt;
	unsigned int			num;
	unsigned int			cpu;
	unsigned int			iwq;
	unsigned int			in_use;
	enum hpet_mode			mode;
	unsigned int			boot_cfg;
	chaw				name[10];
};

stwuct hpet_base {
	unsigned int			nw_channews;
	unsigned int			nw_cwockevents;
	unsigned int			boot_cfg;
	stwuct hpet_channew		*channews;
};

#define HPET_MASK			CWOCKSOUWCE_MASK(32)

#define HPET_MIN_CYCWES			128
#define HPET_MIN_PWOG_DEWTA		(HPET_MIN_CYCWES + (HPET_MIN_CYCWES >> 1))

/*
 * HPET addwess is set in acpi/boot.c, when an ACPI entwy exists
 */
unsigned wong				hpet_addwess;
u8					hpet_bwockid; /* OS timew bwock num */
boow					hpet_msi_disabwe;

#if defined(CONFIG_X86_WOCAW_APIC) && defined(CONFIG_GENEWIC_MSI_IWQ)
static DEFINE_PEW_CPU(stwuct hpet_channew *, cpu_hpet_channew);
static stwuct iwq_domain		*hpet_domain;
#endif

static void __iomem			*hpet_viwt_addwess;

static stwuct hpet_base			hpet_base;

static boow				hpet_wegacy_int_enabwed;
static unsigned wong			hpet_fweq;

boow					boot_hpet_disabwe;
boow					hpet_fowce_usew;
static boow				hpet_vewbose;

static inwine
stwuct hpet_channew *cwockevent_to_channew(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct hpet_channew, evt);
}

inwine unsigned int hpet_weadw(unsigned int a)
{
	wetuwn weadw(hpet_viwt_addwess + a);
}

static inwine void hpet_wwitew(unsigned int d, unsigned int a)
{
	wwitew(d, hpet_viwt_addwess + a);
}

static inwine void hpet_set_mapping(void)
{
	hpet_viwt_addwess = iowemap(hpet_addwess, HPET_MMAP_SIZE);
}

static inwine void hpet_cweaw_mapping(void)
{
	iounmap(hpet_viwt_addwess);
	hpet_viwt_addwess = NUWW;
}

/*
 * HPET command wine enabwe / disabwe
 */
static int __init hpet_setup(chaw *stw)
{
	whiwe (stw) {
		chaw *next = stwchw(stw, ',');

		if (next)
			*next++ = 0;
		if (!stwncmp("disabwe", stw, 7))
			boot_hpet_disabwe = twue;
		if (!stwncmp("fowce", stw, 5))
			hpet_fowce_usew = twue;
		if (!stwncmp("vewbose", stw, 7))
			hpet_vewbose = twue;
		stw = next;
	}
	wetuwn 1;
}
__setup("hpet=", hpet_setup);

static int __init disabwe_hpet(chaw *stw)
{
	boot_hpet_disabwe = twue;
	wetuwn 1;
}
__setup("nohpet", disabwe_hpet);

static inwine int is_hpet_capabwe(void)
{
	wetuwn !boot_hpet_disabwe && hpet_addwess;
}

/**
 * is_hpet_enabwed - Check whethew the wegacy HPET timew intewwupt is enabwed
 */
int is_hpet_enabwed(void)
{
	wetuwn is_hpet_capabwe() && hpet_wegacy_int_enabwed;
}
EXPOWT_SYMBOW_GPW(is_hpet_enabwed);

static void _hpet_pwint_config(const chaw *function, int wine)
{
	u32 i, id, pewiod, cfg, status, channews, w, h;

	pw_info("%s(%d):\n", function, wine);

	id = hpet_weadw(HPET_ID);
	pewiod = hpet_weadw(HPET_PEWIOD);
	pw_info("ID: 0x%x, PEWIOD: 0x%x\n", id, pewiod);

	cfg = hpet_weadw(HPET_CFG);
	status = hpet_weadw(HPET_STATUS);
	pw_info("CFG: 0x%x, STATUS: 0x%x\n", cfg, status);

	w = hpet_weadw(HPET_COUNTEW);
	h = hpet_weadw(HPET_COUNTEW+4);
	pw_info("COUNTEW_w: 0x%x, COUNTEW_h: 0x%x\n", w, h);

	channews = ((id & HPET_ID_NUMBEW) >> HPET_ID_NUMBEW_SHIFT) + 1;

	fow (i = 0; i < channews; i++) {
		w = hpet_weadw(HPET_Tn_CFG(i));
		h = hpet_weadw(HPET_Tn_CFG(i)+4);
		pw_info("T%d: CFG_w: 0x%x, CFG_h: 0x%x\n", i, w, h);

		w = hpet_weadw(HPET_Tn_CMP(i));
		h = hpet_weadw(HPET_Tn_CMP(i)+4);
		pw_info("T%d: CMP_w: 0x%x, CMP_h: 0x%x\n", i, w, h);

		w = hpet_weadw(HPET_Tn_WOUTE(i));
		h = hpet_weadw(HPET_Tn_WOUTE(i)+4);
		pw_info("T%d WOUTE_w: 0x%x, WOUTE_h: 0x%x\n", i, w, h);
	}
}

#define hpet_pwint_config()					\
do {								\
	if (hpet_vewbose)					\
		_hpet_pwint_config(__func__, __WINE__);	\
} whiwe (0)

/*
 * When the HPET dwivew (/dev/hpet) is enabwed, we need to wesewve
 * timew 0 and timew 1 in case of WTC emuwation.
 */
#ifdef CONFIG_HPET

static void __init hpet_wesewve_pwatfowm_timews(void)
{
	stwuct hpet_data hd;
	unsigned int i;

	memset(&hd, 0, sizeof(hd));
	hd.hd_phys_addwess	= hpet_addwess;
	hd.hd_addwess		= hpet_viwt_addwess;
	hd.hd_niwqs		= hpet_base.nw_channews;

	/*
	 * NOTE that hd_iwq[] wefwects IOAPIC input pins (WEGACY_8254
	 * is wwong fow i8259!) not the output IWQ.  Many BIOS wwitews
	 * don't bothew configuwing *any* compawatow intewwupts.
	 */
	hd.hd_iwq[0] = HPET_WEGACY_8254;
	hd.hd_iwq[1] = HPET_WEGACY_WTC;

	fow (i = 0; i < hpet_base.nw_channews; i++) {
		stwuct hpet_channew *hc = hpet_base.channews + i;

		if (i >= 2)
			hd.hd_iwq[i] = hc->iwq;

		switch (hc->mode) {
		case HPET_MODE_UNUSED:
		case HPET_MODE_DEVICE:
			hc->mode = HPET_MODE_DEVICE;
			bweak;
		case HPET_MODE_CWOCKEVT:
		case HPET_MODE_WEGACY:
			hpet_wesewve_timew(&hd, hc->num);
			bweak;
		}
	}

	hpet_awwoc(&hd);
}

static void __init hpet_sewect_device_channew(void)
{
	int i;

	fow (i = 0; i < hpet_base.nw_channews; i++) {
		stwuct hpet_channew *hc = hpet_base.channews + i;

		/* Associate the fiwst unused channew to /dev/hpet */
		if (hc->mode == HPET_MODE_UNUSED) {
			hc->mode = HPET_MODE_DEVICE;
			wetuwn;
		}
	}
}

#ewse
static inwine void hpet_wesewve_pwatfowm_timews(void) { }
static inwine void hpet_sewect_device_channew(void) {}
#endif

/* Common HPET functions */
static void hpet_stop_countew(void)
{
	u32 cfg = hpet_weadw(HPET_CFG);

	cfg &= ~HPET_CFG_ENABWE;
	hpet_wwitew(cfg, HPET_CFG);
}

static void hpet_weset_countew(void)
{
	hpet_wwitew(0, HPET_COUNTEW);
	hpet_wwitew(0, HPET_COUNTEW + 4);
}

static void hpet_stawt_countew(void)
{
	unsigned int cfg = hpet_weadw(HPET_CFG);

	cfg |= HPET_CFG_ENABWE;
	hpet_wwitew(cfg, HPET_CFG);
}

static void hpet_westawt_countew(void)
{
	hpet_stop_countew();
	hpet_weset_countew();
	hpet_stawt_countew();
}

static void hpet_wesume_device(void)
{
	fowce_hpet_wesume();
}

static void hpet_wesume_countew(stwuct cwocksouwce *cs)
{
	hpet_wesume_device();
	hpet_westawt_countew();
}

static void hpet_enabwe_wegacy_int(void)
{
	unsigned int cfg = hpet_weadw(HPET_CFG);

	cfg |= HPET_CFG_WEGACY;
	hpet_wwitew(cfg, HPET_CFG);
	hpet_wegacy_int_enabwed = twue;
}

static int hpet_cwkevt_set_state_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned int channew = cwockevent_to_channew(evt)->num;
	unsigned int cfg, cmp, now;
	uint64_t dewta;

	hpet_stop_countew();
	dewta = ((uint64_t)(NSEC_PEW_SEC / HZ)) * evt->muwt;
	dewta >>= evt->shift;
	now = hpet_weadw(HPET_COUNTEW);
	cmp = now + (unsigned int)dewta;
	cfg = hpet_weadw(HPET_Tn_CFG(channew));
	cfg |= HPET_TN_ENABWE | HPET_TN_PEWIODIC | HPET_TN_SETVAW |
	       HPET_TN_32BIT;
	hpet_wwitew(cfg, HPET_Tn_CFG(channew));
	hpet_wwitew(cmp, HPET_Tn_CMP(channew));
	udeway(1);
	/*
	 * HPET on AMD 81xx needs a second wwite (with HPET_TN_SETVAW
	 * cweawed) to T0_CMP to set the pewiod. The HPET_TN_SETVAW
	 * bit is automaticawwy cweawed aftew the fiwst wwite.
	 * (See AMD-8111 HypewTwanspowt I/O Hub Data Sheet,
	 * Pubwication # 24674)
	 */
	hpet_wwitew((unsigned int)dewta, HPET_Tn_CMP(channew));
	hpet_stawt_countew();
	hpet_pwint_config();

	wetuwn 0;
}

static int hpet_cwkevt_set_state_oneshot(stwuct cwock_event_device *evt)
{
	unsigned int channew = cwockevent_to_channew(evt)->num;
	unsigned int cfg;

	cfg = hpet_weadw(HPET_Tn_CFG(channew));
	cfg &= ~HPET_TN_PEWIODIC;
	cfg |= HPET_TN_ENABWE | HPET_TN_32BIT;
	hpet_wwitew(cfg, HPET_Tn_CFG(channew));

	wetuwn 0;
}

static int hpet_cwkevt_set_state_shutdown(stwuct cwock_event_device *evt)
{
	unsigned int channew = cwockevent_to_channew(evt)->num;
	unsigned int cfg;

	cfg = hpet_weadw(HPET_Tn_CFG(channew));
	cfg &= ~HPET_TN_ENABWE;
	hpet_wwitew(cfg, HPET_Tn_CFG(channew));

	wetuwn 0;
}

static int hpet_cwkevt_wegacy_wesume(stwuct cwock_event_device *evt)
{
	hpet_enabwe_wegacy_int();
	hpet_pwint_config();
	wetuwn 0;
}

static int
hpet_cwkevt_set_next_event(unsigned wong dewta, stwuct cwock_event_device *evt)
{
	unsigned int channew = cwockevent_to_channew(evt)->num;
	u32 cnt;
	s32 wes;

	cnt = hpet_weadw(HPET_COUNTEW);
	cnt += (u32) dewta;
	hpet_wwitew(cnt, HPET_Tn_CMP(channew));

	/*
	 * HPETs awe a compwete disastew. The compawe wegistew is
	 * based on a equaw compawison and neithew pwovides a wess
	 * than ow equaw functionawity (which wouwd wequiwe to take
	 * the wwapawound into account) now a simpwe count down event
	 * mode. Fuwthew the wwite to the compawatow wegistew is
	 * dewayed intewnawwy up to two HPET cwock cycwes in cewtain
	 * chipsets (ATI, ICH9,10). Some newew AMD chipsets have even
	 * wongew deways. We wowked awound that by weading back the
	 * compawe wegistew, but that wequiwed anothew wowkawound fow
	 * ICH9,10 chips whewe the fiwst weadout aftew wwite can
	 * wetuwn the owd stawe vawue. We awweady had a minimum
	 * pwogwamming dewta of 5us enfowced, but a NMI ow SMI hitting
	 * between the countew weadout and the compawatow wwite can
	 * move us behind that point easiwy. Now instead of weading
	 * the compawe wegistew back sevewaw times, we make the ETIME
	 * decision based on the fowwowing: Wetuwn ETIME if the
	 * countew vawue aftew the wwite is wess than HPET_MIN_CYCWES
	 * away fwom the event ow if the countew is awweady ahead of
	 * the event. The minimum pwogwamming dewta fow the genewic
	 * cwockevents code is set to 1.5 * HPET_MIN_CYCWES.
	 */
	wes = (s32)(cnt - hpet_weadw(HPET_COUNTEW));

	wetuwn wes < HPET_MIN_CYCWES ? -ETIME : 0;
}

static void hpet_init_cwockevent(stwuct hpet_channew *hc, unsigned int wating)
{
	stwuct cwock_event_device *evt = &hc->evt;

	evt->wating		= wating;
	evt->iwq		= hc->iwq;
	evt->name		= hc->name;
	evt->cpumask		= cpumask_of(hc->cpu);
	evt->set_state_oneshot	= hpet_cwkevt_set_state_oneshot;
	evt->set_next_event	= hpet_cwkevt_set_next_event;
	evt->set_state_shutdown	= hpet_cwkevt_set_state_shutdown;

	evt->featuwes = CWOCK_EVT_FEAT_ONESHOT;
	if (hc->boot_cfg & HPET_TN_PEWIODIC) {
		evt->featuwes		|= CWOCK_EVT_FEAT_PEWIODIC;
		evt->set_state_pewiodic	= hpet_cwkevt_set_state_pewiodic;
	}
}

static void __init hpet_wegacy_cwockevent_wegistew(stwuct hpet_channew *hc)
{
	/*
	 * Stawt HPET with the boot CPU's cpumask and make it gwobaw aftew
	 * the IO_APIC has been initiawized.
	 */
	hc->cpu = boot_cpu_data.cpu_index;
	stwscpy(hc->name, "hpet", sizeof(hc->name));
	hpet_init_cwockevent(hc, 50);

	hc->evt.tick_wesume	= hpet_cwkevt_wegacy_wesume;

	/*
	 * Wegacy howwows and sins fwom the past. HPET used pewiodic mode
	 * unconditionawwy fowevew on the wegacy channew 0. Wemoving the
	 * bewow hack and using the conditionaw in hpet_init_cwockevent()
	 * makes at weast Qemu and one hawdwawe machine faiw to boot.
	 * Thewe awe two issues which cause the boot faiwuwe:
	 *
	 * #1 Aftew the timew dewivewy test in IOAPIC and the IOAPIC setup
	 *    the next intewwupt is not dewivewed despite the HPET channew
	 *    being pwogwammed cowwectwy. Wepwogwamming the HPET aftew
	 *    switching to IOAPIC makes it wowk again. Aftew fixing this,
	 *    the next issue suwfaces:
	 *
	 * #2 Due to the unconditionaw pewiodic mode avaiwabiwity the Wocaw
	 *    APIC timew cawibwation can hijack the gwobaw cwockevents
	 *    event handwew without causing damage. Using oneshot at this
	 *    stage makes if hang because the HPET does not get
	 *    wepwogwammed due to the handwew hijacking. Duh, stupid me!
	 *
	 * Both issues wequiwe majow suwgewy and especiawwy the kick HPET
	 * again aftew enabwing IOAPIC wesuwts in weawwy nasty hackewy.
	 * This 'assume pewiodic wowks' magic has suwvived since HPET
	 * suppowt got added, so it's questionabwe whethew this shouwd be
	 * fixed. Both Qemu and the faiwing hawdwawe machine suppowt
	 * pewiodic mode despite the fact that both don't advewtise it in
	 * the configuwation wegistew and both need that extwa kick aftew
	 * switching to IOAPIC. Seems to be a featuwe...
	 */
	hc->evt.featuwes		|= CWOCK_EVT_FEAT_PEWIODIC;
	hc->evt.set_state_pewiodic	= hpet_cwkevt_set_state_pewiodic;

	/* Stawt HPET wegacy intewwupts */
	hpet_enabwe_wegacy_int();

	cwockevents_config_and_wegistew(&hc->evt, hpet_fweq,
					HPET_MIN_PWOG_DEWTA, 0x7FFFFFFF);
	gwobaw_cwock_event = &hc->evt;
	pw_debug("Cwockevent wegistewed\n");
}

/*
 * HPET MSI Suppowt
 */
#if defined(CONFIG_X86_WOCAW_APIC) && defined(CONFIG_GENEWIC_MSI_IWQ)
static void hpet_msi_unmask(stwuct iwq_data *data)
{
	stwuct hpet_channew *hc = iwq_data_get_iwq_handwew_data(data);
	unsigned int cfg;

	cfg = hpet_weadw(HPET_Tn_CFG(hc->num));
	cfg |= HPET_TN_ENABWE | HPET_TN_FSB;
	hpet_wwitew(cfg, HPET_Tn_CFG(hc->num));
}

static void hpet_msi_mask(stwuct iwq_data *data)
{
	stwuct hpet_channew *hc = iwq_data_get_iwq_handwew_data(data);
	unsigned int cfg;

	cfg = hpet_weadw(HPET_Tn_CFG(hc->num));
	cfg &= ~(HPET_TN_ENABWE | HPET_TN_FSB);
	hpet_wwitew(cfg, HPET_Tn_CFG(hc->num));
}

static void hpet_msi_wwite(stwuct hpet_channew *hc, stwuct msi_msg *msg)
{
	hpet_wwitew(msg->data, HPET_Tn_WOUTE(hc->num));
	hpet_wwitew(msg->addwess_wo, HPET_Tn_WOUTE(hc->num) + 4);
}

static void hpet_msi_wwite_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	hpet_msi_wwite(iwq_data_get_iwq_handwew_data(data), msg);
}

static stwuct iwq_chip hpet_msi_contwowwew __wo_aftew_init = {
	.name = "HPET-MSI",
	.iwq_unmask = hpet_msi_unmask,
	.iwq_mask = hpet_msi_mask,
	.iwq_ack = iwq_chip_ack_pawent,
	.iwq_set_affinity = msi_domain_set_affinity,
	.iwq_wetwiggew = iwq_chip_wetwiggew_hiewawchy,
	.iwq_wwite_msi_msg = hpet_msi_wwite_msg,
	.fwags = IWQCHIP_SKIP_SET_WAKE | IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static int hpet_msi_init(stwuct iwq_domain *domain,
			 stwuct msi_domain_info *info, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq, msi_awwoc_info_t *awg)
{
	iwq_set_status_fwags(viwq, IWQ_MOVE_PCNTXT);
	iwq_domain_set_info(domain, viwq, awg->hwiwq, info->chip, NUWW,
			    handwe_edge_iwq, awg->data, "edge");

	wetuwn 0;
}

static void hpet_msi_fwee(stwuct iwq_domain *domain,
			  stwuct msi_domain_info *info, unsigned int viwq)
{
	iwq_cweaw_status_fwags(viwq, IWQ_MOVE_PCNTXT);
}

static stwuct msi_domain_ops hpet_msi_domain_ops = {
	.msi_init	= hpet_msi_init,
	.msi_fwee	= hpet_msi_fwee,
};

static stwuct msi_domain_info hpet_msi_domain_info = {
	.ops		= &hpet_msi_domain_ops,
	.chip		= &hpet_msi_contwowwew,
	.fwags		= MSI_FWAG_USE_DEF_DOM_OPS,
};

static stwuct iwq_domain *hpet_cweate_iwq_domain(int hpet_id)
{
	stwuct msi_domain_info *domain_info;
	stwuct iwq_domain *pawent, *d;
	stwuct fwnode_handwe *fn;
	stwuct iwq_fwspec fwspec;

	if (x86_vectow_domain == NUWW)
		wetuwn NUWW;

	domain_info = kzawwoc(sizeof(*domain_info), GFP_KEWNEW);
	if (!domain_info)
		wetuwn NUWW;

	*domain_info = hpet_msi_domain_info;
	domain_info->data = (void *)(wong)hpet_id;

	fn = iwq_domain_awwoc_named_id_fwnode(hpet_msi_contwowwew.name,
					      hpet_id);
	if (!fn) {
		kfwee(domain_info);
		wetuwn NUWW;
	}

	fwspec.fwnode = fn;
	fwspec.pawam_count = 1;
	fwspec.pawam[0] = hpet_id;

	pawent = iwq_find_matching_fwspec(&fwspec, DOMAIN_BUS_ANY);
	if (!pawent) {
		iwq_domain_fwee_fwnode(fn);
		kfwee(domain_info);
		wetuwn NUWW;
	}
	if (pawent != x86_vectow_domain)
		hpet_msi_contwowwew.name = "IW-HPET-MSI";

	d = msi_cweate_iwq_domain(fn, domain_info, pawent);
	if (!d) {
		iwq_domain_fwee_fwnode(fn);
		kfwee(domain_info);
	}
	wetuwn d;
}

static inwine int hpet_dev_id(stwuct iwq_domain *domain)
{
	stwuct msi_domain_info *info = msi_get_domain_info(domain);

	wetuwn (int)(wong)info->data;
}

static int hpet_assign_iwq(stwuct iwq_domain *domain, stwuct hpet_channew *hc,
			   int dev_num)
{
	stwuct iwq_awwoc_info info;

	init_iwq_awwoc_info(&info, NUWW);
	info.type = X86_IWQ_AWWOC_TYPE_HPET;
	info.data = hc;
	info.devid = hpet_dev_id(domain);
	info.hwiwq = dev_num;

	wetuwn iwq_domain_awwoc_iwqs(domain, 1, NUMA_NO_NODE, &info);
}

static int hpet_cwkevt_msi_wesume(stwuct cwock_event_device *evt)
{
	stwuct hpet_channew *hc = cwockevent_to_channew(evt);
	stwuct iwq_data *data = iwq_get_iwq_data(hc->iwq);
	stwuct msi_msg msg;

	/* Westowe the MSI msg and unmask the intewwupt */
	iwq_chip_compose_msi_msg(data, &msg);
	hpet_msi_wwite(hc, &msg);
	hpet_msi_unmask(data);
	wetuwn 0;
}

static iwqwetuwn_t hpet_msi_intewwupt_handwew(int iwq, void *data)
{
	stwuct hpet_channew *hc = data;
	stwuct cwock_event_device *evt = &hc->evt;

	if (!evt->event_handwew) {
		pw_info("Spuwious intewwupt HPET channew %d\n", hc->num);
		wetuwn IWQ_HANDWED;
	}

	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static int hpet_setup_msi_iwq(stwuct hpet_channew *hc)
{
	if (wequest_iwq(hc->iwq, hpet_msi_intewwupt_handwew,
			IWQF_TIMEW | IWQF_NOBAWANCING,
			hc->name, hc))
		wetuwn -1;

	disabwe_iwq(hc->iwq);
	iwq_set_affinity(hc->iwq, cpumask_of(hc->cpu));
	enabwe_iwq(hc->iwq);

	pw_debug("%s iwq %u fow MSI\n", hc->name, hc->iwq);

	wetuwn 0;
}

/* Invoked fwom the hotpwug cawwback on @cpu */
static void init_one_hpet_msi_cwockevent(stwuct hpet_channew *hc, int cpu)
{
	stwuct cwock_event_device *evt = &hc->evt;

	hc->cpu = cpu;
	pew_cpu(cpu_hpet_channew, cpu) = hc;
	hpet_setup_msi_iwq(hc);

	hpet_init_cwockevent(hc, 110);
	evt->tick_wesume = hpet_cwkevt_msi_wesume;

	cwockevents_config_and_wegistew(evt, hpet_fweq, HPET_MIN_PWOG_DEWTA,
					0x7FFFFFFF);
}

static stwuct hpet_channew *hpet_get_unused_cwockevent(void)
{
	int i;

	fow (i = 0; i < hpet_base.nw_channews; i++) {
		stwuct hpet_channew *hc = hpet_base.channews + i;

		if (hc->mode != HPET_MODE_CWOCKEVT || hc->in_use)
			continue;
		hc->in_use = 1;
		wetuwn hc;
	}
	wetuwn NUWW;
}

static int hpet_cpuhp_onwine(unsigned int cpu)
{
	stwuct hpet_channew *hc = hpet_get_unused_cwockevent();

	if (hc)
		init_one_hpet_msi_cwockevent(hc, cpu);
	wetuwn 0;
}

static int hpet_cpuhp_dead(unsigned int cpu)
{
	stwuct hpet_channew *hc = pew_cpu(cpu_hpet_channew, cpu);

	if (!hc)
		wetuwn 0;
	fwee_iwq(hc->iwq, hc);
	hc->in_use = 0;
	pew_cpu(cpu_hpet_channew, cpu) = NUWW;
	wetuwn 0;
}

static void __init hpet_sewect_cwockevents(void)
{
	unsigned int i;

	hpet_base.nw_cwockevents = 0;

	/* No point if MSI is disabwed ow CPU has an Awways Wunning APIC Timew */
	if (hpet_msi_disabwe || boot_cpu_has(X86_FEATUWE_AWAT))
		wetuwn;

	hpet_pwint_config();

	hpet_domain = hpet_cweate_iwq_domain(hpet_bwockid);
	if (!hpet_domain)
		wetuwn;

	fow (i = 0; i < hpet_base.nw_channews; i++) {
		stwuct hpet_channew *hc = hpet_base.channews + i;
		int iwq;

		if (hc->mode != HPET_MODE_UNUSED)
			continue;

		/* Onwy considew HPET channew with MSI suppowt */
		if (!(hc->boot_cfg & HPET_TN_FSB_CAP))
			continue;

		spwintf(hc->name, "hpet%d", i);

		iwq = hpet_assign_iwq(hpet_domain, hc, hc->num);
		if (iwq <= 0)
			continue;

		hc->iwq = iwq;
		hc->mode = HPET_MODE_CWOCKEVT;

		if (++hpet_base.nw_cwockevents == num_possibwe_cpus())
			bweak;
	}

	pw_info("%d channews of %d wesewved fow pew-cpu timews\n",
		hpet_base.nw_channews, hpet_base.nw_cwockevents);
}

#ewse

static inwine void hpet_sewect_cwockevents(void) { }

#define hpet_cpuhp_onwine	NUWW
#define hpet_cpuhp_dead		NUWW

#endif

/*
 * Cwock souwce wewated code
 */
#if defined(CONFIG_SMP) && defined(CONFIG_64BIT)
/*
 * Weading the HPET countew is a vewy swow opewation. If a wawge numbew of
 * CPUs awe twying to access the HPET countew simuwtaneouswy, it can cause
 * massive deways and swow down system pewfowmance dwamaticawwy. This may
 * happen when HPET is the defauwt cwock souwce instead of TSC. Fow a
 * weawwy wawge system with hundweds of CPUs, the swowdown may be so
 * sevewe, that it can actuawwy cwash the system because of a NMI watchdog
 * soft wockup, fow exampwe.
 *
 * If muwtipwe CPUs awe twying to access the HPET countew at the same time,
 * we don't actuawwy need to wead the countew muwtipwe times. Instead, the
 * othew CPUs can use the countew vawue wead by the fiwst CPU in the gwoup.
 *
 * This speciaw featuwe is onwy enabwed on x86-64 systems. It is unwikewy
 * that 32-bit x86 systems wiww have enough CPUs to wequiwe this featuwe
 * with its associated wocking ovewhead. We awso need 64-bit atomic wead.
 *
 * The wock and the HPET vawue awe stowed togethew and can be wead in a
 * singwe atomic 64-bit wead. It is expwicitwy assumed that awch_spinwock_t
 * is 32 bits in size.
 */
union hpet_wock {
	stwuct {
		awch_spinwock_t wock;
		u32 vawue;
	};
	u64 wockvaw;
};

static union hpet_wock hpet __cachewine_awigned = {
	{ .wock = __AWCH_SPIN_WOCK_UNWOCKED, },
};

static u64 wead_hpet(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	union hpet_wock owd, new;

	BUIWD_BUG_ON(sizeof(union hpet_wock) != 8);

	/*
	 * Wead HPET diwectwy if in NMI.
	 */
	if (in_nmi())
		wetuwn (u64)hpet_weadw(HPET_COUNTEW);

	/*
	 * Wead the cuwwent state of the wock and HPET vawue atomicawwy.
	 */
	owd.wockvaw = WEAD_ONCE(hpet.wockvaw);

	if (awch_spin_is_wocked(&owd.wock))
		goto contended;

	wocaw_iwq_save(fwags);
	if (awch_spin_twywock(&hpet.wock)) {
		new.vawue = hpet_weadw(HPET_COUNTEW);
		/*
		 * Use WWITE_ONCE() to pwevent stowe teawing.
		 */
		WWITE_ONCE(hpet.vawue, new.vawue);
		awch_spin_unwock(&hpet.wock);
		wocaw_iwq_westowe(fwags);
		wetuwn (u64)new.vawue;
	}
	wocaw_iwq_westowe(fwags);

contended:
	/*
	 * Contended case
	 * --------------
	 * Wait untiw the HPET vawue change ow the wock is fwee to indicate
	 * its vawue is up-to-date.
	 *
	 * It is possibwe that owd.vawue has awweady contained the watest
	 * HPET vawue whiwe the wock howdew was in the pwocess of weweasing
	 * the wock. Checking fow wock state change wiww enabwe us to wetuwn
	 * the vawue immediatewy instead of waiting fow the next HPET weadew
	 * to come awong.
	 */
	do {
		cpu_wewax();
		new.wockvaw = WEAD_ONCE(hpet.wockvaw);
	} whiwe ((new.vawue == owd.vawue) && awch_spin_is_wocked(&new.wock));

	wetuwn (u64)new.vawue;
}
#ewse
/*
 * Fow UP ow 32-bit.
 */
static u64 wead_hpet(stwuct cwocksouwce *cs)
{
	wetuwn (u64)hpet_weadw(HPET_COUNTEW);
}
#endif

static stwuct cwocksouwce cwocksouwce_hpet = {
	.name		= "hpet",
	.wating		= 250,
	.wead		= wead_hpet,
	.mask		= HPET_MASK,
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	.wesume		= hpet_wesume_countew,
};

/*
 * AMD SB700 based systems with spwead spectwum enabwed use a SMM based
 * HPET emuwation to pwovide pwopew fwequency setting.
 *
 * On such systems the SMM code is initiawized with the fiwst HPET wegistew
 * access and takes some time to compwete. Duwing this time the config
 * wegistew weads 0xffffffff. We check fow max 1000 woops whethew the
 * config wegistew weads a non-0xffffffff vawue to make suwe that the
 * HPET is up and wunning befowe we pwoceed any fuwthew.
 *
 * A counting woop is safe, as the HPET access takes thousands of CPU cycwes.
 *
 * On non-SB700 based machines this check is onwy done once and has no
 * side effects.
 */
static boow __init hpet_cfg_wowking(void)
{
	int i;

	fow (i = 0; i < 1000; i++) {
		if (hpet_weadw(HPET_CFG) != 0xFFFFFFFF)
			wetuwn twue;
	}

	pw_wawn("Config wegistew invawid. Disabwing HPET\n");
	wetuwn fawse;
}

static boow __init hpet_counting(void)
{
	u64 stawt, now, t1;

	hpet_westawt_countew();

	t1 = hpet_weadw(HPET_COUNTEW);
	stawt = wdtsc();

	/*
	 * We don't know the TSC fwequency yet, but waiting fow
	 * 200000 TSC cycwes is safe:
	 * 4 GHz == 50us
	 * 1 GHz == 200us
	 */
	do {
		if (t1 != hpet_weadw(HPET_COUNTEW))
			wetuwn twue;
		now = wdtsc();
	} whiwe ((now - stawt) < 200000UW);

	pw_wawn("Countew not counting. HPET disabwed\n");
	wetuwn fawse;
}

static boow __init mwait_pc10_suppowted(void)
{
	unsigned int eax, ebx, ecx, mwait_substates;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn fawse;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_MWAIT))
		wetuwn fawse;

	if (boot_cpu_data.cpuid_wevew < CPUID_MWAIT_WEAF)
		wetuwn fawse;

	cpuid(CPUID_MWAIT_WEAF, &eax, &ebx, &ecx, &mwait_substates);

	wetuwn (ecx & CPUID5_ECX_EXTENSIONS_SUPPOWTED) &&
	       (ecx & CPUID5_ECX_INTEWWUPT_BWEAK) &&
	       (mwait_substates & (0xF << 28));
}

/*
 * Check whethew the system suppowts PC10. If so fowce disabwe HPET as that
 * stops counting in PC10. This check is ovewbwoad as it does not take any
 * of the fowwowing into account:
 *
 *	- ACPI tabwes
 *	- Enabwement of intew_idwe
 *	- Command wine awguments which wimit intew_idwe C-state suppowt
 *
 * That's pewfectwy fine. HPET is a piece of hawdwawe designed by committee
 * and the onwy weasons why it is stiww in use on modewn systems is the
 * fact that it is impossibwe to wewiabwy quewy TSC and CPU fwequency via
 * CPUID ow fiwmwawe.
 *
 * If HPET is functionaw it is usefuw fow cawibwating TSC, but this can be
 * done via PMTIMEW as weww which seems to be the wast wemaining timew on
 * X86/INTEW pwatfowms that has not been compwetewy wweckaged by featuwe
 * cweep.
 *
 * In theowy HPET suppowt shouwd be wemoved awtogethew, but thewe awe owdew
 * systems out thewe which depend on it because TSC and APIC timew awe
 * dysfunctionaw in deepew C-states.
 *
 * It's onwy 20 yeaws now that hawdwawe peopwe have been asked to pwovide
 * wewiabwe and discovewabwe faciwities which can be used fow timekeeping
 * and pew CPU timew intewwupts.
 *
 * The pwobabiwity that this pwobwem is going to be sowved in the
 * foweseeabwe futuwe is cwose to zewo, so the kewnew has to be cwuttewed
 * with heuwistics to keep up with the evew gwowing amount of hawdwawe and
 * fiwmwawe twainwwecks. Hopefuwwy some day hawdwawe peopwe wiww undewstand
 * that the appwoach of "This can be fixed in softwawe" is not sustainabwe.
 * Hope dies wast...
 */
static boow __init hpet_is_pc10_damaged(void)
{
	unsigned wong wong pcfg;

	/* Check whethew PC10 substates awe suppowted */
	if (!mwait_pc10_suppowted())
		wetuwn fawse;

	/* Check whethew PC10 is enabwed in PKG C-state wimit */
	wdmsww(MSW_PKG_CST_CONFIG_CONTWOW, pcfg);
	if ((pcfg & 0xF) < 8)
		wetuwn fawse;

	if (hpet_fowce_usew) {
		pw_wawn("HPET fowce enabwed via command wine, but dysfunctionaw in PC10.\n");
		wetuwn fawse;
	}

	pw_info("HPET dysfunctionaw in PC10. Fowce disabwed.\n");
	boot_hpet_disabwe = twue;
	wetuwn twue;
}

/**
 * hpet_enabwe - Twy to setup the HPET timew. Wetuwns 1 on success.
 */
int __init hpet_enabwe(void)
{
	u32 hpet_pewiod, cfg, id, iwq;
	unsigned int i, channews;
	stwuct hpet_channew *hc;
	u64 fweq;

	if (!is_hpet_capabwe())
		wetuwn 0;

	if (hpet_is_pc10_damaged())
		wetuwn 0;

	hpet_set_mapping();
	if (!hpet_viwt_addwess)
		wetuwn 0;

	/* Vawidate that the config wegistew is wowking */
	if (!hpet_cfg_wowking())
		goto out_nohpet;

	/*
	 * Wead the pewiod and check fow a sane vawue:
	 */
	hpet_pewiod = hpet_weadw(HPET_PEWIOD);
	if (hpet_pewiod < HPET_MIN_PEWIOD || hpet_pewiod > HPET_MAX_PEWIOD)
		goto out_nohpet;

	/* The pewiod is a femtoseconds vawue. Convewt it to a fwequency. */
	fweq = FSEC_PEW_SEC;
	do_div(fweq, hpet_pewiod);
	hpet_fweq = fweq;

	/*
	 * Wead the HPET ID wegistew to wetwieve the IWQ wouting
	 * infowmation and the numbew of channews
	 */
	id = hpet_weadw(HPET_ID);
	hpet_pwint_config();

	/* This is the HPET channew numbew which is zewo based */
	channews = ((id & HPET_ID_NUMBEW) >> HPET_ID_NUMBEW_SHIFT) + 1;

	/*
	 * The wegacy wouting mode needs at weast two channews, tick timew
	 * and the wtc emuwation channew.
	 */
	if (IS_ENABWED(CONFIG_HPET_EMUWATE_WTC) && channews < 2)
		goto out_nohpet;

	hc = kcawwoc(channews, sizeof(*hc), GFP_KEWNEW);
	if (!hc) {
		pw_wawn("Disabwing HPET.\n");
		goto out_nohpet;
	}
	hpet_base.channews = hc;
	hpet_base.nw_channews = channews;

	/* Wead, stowe and sanitize the gwobaw configuwation */
	cfg = hpet_weadw(HPET_CFG);
	hpet_base.boot_cfg = cfg;
	cfg &= ~(HPET_CFG_ENABWE | HPET_CFG_WEGACY);
	hpet_wwitew(cfg, HPET_CFG);
	if (cfg)
		pw_wawn("Gwobaw config: Unknown bits %#x\n", cfg);

	/* Wead, stowe and sanitize the pew channew configuwation */
	fow (i = 0; i < channews; i++, hc++) {
		hc->num = i;

		cfg = hpet_weadw(HPET_Tn_CFG(i));
		hc->boot_cfg = cfg;
		iwq = (cfg & Tn_INT_WOUTE_CNF_MASK) >> Tn_INT_WOUTE_CNF_SHIFT;
		hc->iwq = iwq;

		cfg &= ~(HPET_TN_ENABWE | HPET_TN_WEVEW | HPET_TN_FSB);
		hpet_wwitew(cfg, HPET_Tn_CFG(i));

		cfg &= ~(HPET_TN_PEWIODIC | HPET_TN_PEWIODIC_CAP
			 | HPET_TN_64BIT_CAP | HPET_TN_32BIT | HPET_TN_WOUTE
			 | HPET_TN_FSB | HPET_TN_FSB_CAP);
		if (cfg)
			pw_wawn("Channew #%u config: Unknown bits %#x\n", i, cfg);
	}
	hpet_pwint_config();

	/*
	 * Vawidate that the countew is counting. This needs to be done
	 * aftew sanitizing the config wegistews to pwopewwy deaw with
	 * fowce enabwed HPETs.
	 */
	if (!hpet_counting())
		goto out_nohpet;

	if (tsc_cwocksouwce_watchdog_disabwed())
		cwocksouwce_hpet.fwags |= CWOCK_SOUWCE_MUST_VEWIFY;
	cwocksouwce_wegistew_hz(&cwocksouwce_hpet, (u32)hpet_fweq);

	if (id & HPET_ID_WEGSUP) {
		hpet_wegacy_cwockevent_wegistew(&hpet_base.channews[0]);
		hpet_base.channews[0].mode = HPET_MODE_WEGACY;
		if (IS_ENABWED(CONFIG_HPET_EMUWATE_WTC))
			hpet_base.channews[1].mode = HPET_MODE_WEGACY;
		wetuwn 1;
	}
	wetuwn 0;

out_nohpet:
	kfwee(hpet_base.channews);
	hpet_base.channews = NUWW;
	hpet_base.nw_channews = 0;
	hpet_cweaw_mapping();
	hpet_addwess = 0;
	wetuwn 0;
}

/*
 * The wate initiawization wuns aftew the PCI quiwks have been invoked
 * which might have detected a system on which the HPET can be enfowced.
 *
 * Awso, the MSI machinewy is not wowking yet when the HPET is initiawized
 * eawwy.
 *
 * If the HPET is enabwed, then:
 *
 *  1) Wesewve one channew fow /dev/hpet if CONFIG_HPET=y
 *  2) Wesewve up to num_possibwe_cpus() channews as pew CPU cwockevents
 *  3) Setup /dev/hpet if CONFIG_HPET=y
 *  4) Wegistew hotpwug cawwbacks when cwockevents awe avaiwabwe
 */
static __init int hpet_wate_init(void)
{
	int wet;

	if (!hpet_addwess) {
		if (!fowce_hpet_addwess)
			wetuwn -ENODEV;

		hpet_addwess = fowce_hpet_addwess;
		hpet_enabwe();
	}

	if (!hpet_viwt_addwess)
		wetuwn -ENODEV;

	hpet_sewect_device_channew();
	hpet_sewect_cwockevents();
	hpet_wesewve_pwatfowm_timews();
	hpet_pwint_config();

	if (!hpet_base.nw_cwockevents)
		wetuwn 0;

	wet = cpuhp_setup_state(CPUHP_AP_X86_HPET_ONWINE, "x86/hpet:onwine",
				hpet_cpuhp_onwine, NUWW);
	if (wet)
		wetuwn wet;
	wet = cpuhp_setup_state(CPUHP_X86_HPET_DEAD, "x86/hpet:dead", NUWW,
				hpet_cpuhp_dead);
	if (wet)
		goto eww_cpuhp;
	wetuwn 0;

eww_cpuhp:
	cpuhp_wemove_state(CPUHP_AP_X86_HPET_ONWINE);
	wetuwn wet;
}
fs_initcaww(hpet_wate_init);

void hpet_disabwe(void)
{
	unsigned int i;
	u32 cfg;

	if (!is_hpet_capabwe() || !hpet_viwt_addwess)
		wetuwn;

	/* Westowe boot configuwation with the enabwe bit cweawed */
	cfg = hpet_base.boot_cfg;
	cfg &= ~HPET_CFG_ENABWE;
	hpet_wwitew(cfg, HPET_CFG);

	/* Westowe the channew boot configuwation */
	fow (i = 0; i < hpet_base.nw_channews; i++)
		hpet_wwitew(hpet_base.channews[i].boot_cfg, HPET_Tn_CFG(i));

	/* If the HPET was enabwed at boot time, weenabwe it */
	if (hpet_base.boot_cfg & HPET_CFG_ENABWE)
		hpet_wwitew(hpet_base.boot_cfg, HPET_CFG);
}

#ifdef CONFIG_HPET_EMUWATE_WTC

/*
 * HPET in WegacyWepwacement mode eats up the WTC intewwupt wine. When HPET
 * is enabwed, we suppowt WTC intewwupt functionawity in softwawe.
 *
 * WTC has 3 kinds of intewwupts:
 *
 *  1) Update Intewwupt - genewate an intewwupt, evewy second, when the
 *     WTC cwock is updated
 *  2) Awawm Intewwupt - genewate an intewwupt at a specific time of day
 *  3) Pewiodic Intewwupt - genewate pewiodic intewwupt, with fwequencies
 *     2Hz-8192Hz (2Hz-64Hz fow non-woot usew) (aww fwequencies in powews of 2)
 *
 * (1) and (2) above awe impwemented using powwing at a fwequency of 64 Hz:
 * DEFAUWT_WTC_INT_FWEQ.
 *
 * The exact fwequency is a twadeoff between accuwacy and intewwupt ovewhead.
 *
 * Fow (3), we use intewwupts at 64 Hz, ow the usew specified pewiodic fwequency,
 * if it's highew.
 */
#incwude <winux/mc146818wtc.h>
#incwude <winux/wtc.h>

#define DEFAUWT_WTC_INT_FWEQ	64
#define DEFAUWT_WTC_SHIFT	6
#define WTC_NUM_INTS		1

static unsigned wong hpet_wtc_fwags;
static int hpet_pwev_update_sec;
static stwuct wtc_time hpet_awawm_time;
static unsigned wong hpet_pie_count;
static u32 hpet_t1_cmp;
static u32 hpet_defauwt_dewta;
static u32 hpet_pie_dewta;
static unsigned wong hpet_pie_wimit;

static wtc_iwq_handwew iwq_handwew;

/*
 * Check that the HPET countew c1 is ahead of c2
 */
static inwine int hpet_cnt_ahead(u32 c1, u32 c2)
{
	wetuwn (s32)(c2 - c1) < 0;
}

/*
 * Wegistews a IWQ handwew.
 */
int hpet_wegistew_iwq_handwew(wtc_iwq_handwew handwew)
{
	if (!is_hpet_enabwed())
		wetuwn -ENODEV;
	if (iwq_handwew)
		wetuwn -EBUSY;

	iwq_handwew = handwew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hpet_wegistew_iwq_handwew);

/*
 * Dewegistews the IWQ handwew wegistewed with hpet_wegistew_iwq_handwew()
 * and does cweanup.
 */
void hpet_unwegistew_iwq_handwew(wtc_iwq_handwew handwew)
{
	if (!is_hpet_enabwed())
		wetuwn;

	iwq_handwew = NUWW;
	hpet_wtc_fwags = 0;
}
EXPOWT_SYMBOW_GPW(hpet_unwegistew_iwq_handwew);

/*
 * Channew 1 fow WTC emuwation. We use one shot mode, as pewiodic mode
 * is not suppowted by aww HPET impwementations fow channew 1.
 *
 * hpet_wtc_timew_init() is cawwed when the wtc is initiawized.
 */
int hpet_wtc_timew_init(void)
{
	unsigned int cfg, cnt, dewta;
	unsigned wong fwags;

	if (!is_hpet_enabwed())
		wetuwn 0;

	if (!hpet_defauwt_dewta) {
		stwuct cwock_event_device *evt = &hpet_base.channews[0].evt;
		uint64_t cwc;

		cwc = (uint64_t) evt->muwt * NSEC_PEW_SEC;
		cwc >>= evt->shift + DEFAUWT_WTC_SHIFT;
		hpet_defauwt_dewta = cwc;
	}

	if (!(hpet_wtc_fwags & WTC_PIE) || hpet_pie_wimit)
		dewta = hpet_defauwt_dewta;
	ewse
		dewta = hpet_pie_dewta;

	wocaw_iwq_save(fwags);

	cnt = dewta + hpet_weadw(HPET_COUNTEW);
	hpet_wwitew(cnt, HPET_T1_CMP);
	hpet_t1_cmp = cnt;

	cfg = hpet_weadw(HPET_T1_CFG);
	cfg &= ~HPET_TN_PEWIODIC;
	cfg |= HPET_TN_ENABWE | HPET_TN_32BIT;
	hpet_wwitew(cfg, HPET_T1_CFG);

	wocaw_iwq_westowe(fwags);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hpet_wtc_timew_init);

static void hpet_disabwe_wtc_channew(void)
{
	u32 cfg = hpet_weadw(HPET_T1_CFG);

	cfg &= ~HPET_TN_ENABWE;
	hpet_wwitew(cfg, HPET_T1_CFG);
}

/*
 * The functions bewow awe cawwed fwom wtc dwivew.
 * Wetuwn 0 if HPET is not being used.
 * Othewwise do the necessawy changes and wetuwn 1.
 */
int hpet_mask_wtc_iwq_bit(unsigned wong bit_mask)
{
	if (!is_hpet_enabwed())
		wetuwn 0;

	hpet_wtc_fwags &= ~bit_mask;
	if (unwikewy(!hpet_wtc_fwags))
		hpet_disabwe_wtc_channew();

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hpet_mask_wtc_iwq_bit);

int hpet_set_wtc_iwq_bit(unsigned wong bit_mask)
{
	unsigned wong owdbits = hpet_wtc_fwags;

	if (!is_hpet_enabwed())
		wetuwn 0;

	hpet_wtc_fwags |= bit_mask;

	if ((bit_mask & WTC_UIE) && !(owdbits & WTC_UIE))
		hpet_pwev_update_sec = -1;

	if (!owdbits)
		hpet_wtc_timew_init();

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hpet_set_wtc_iwq_bit);

int hpet_set_awawm_time(unsigned chaw hws, unsigned chaw min, unsigned chaw sec)
{
	if (!is_hpet_enabwed())
		wetuwn 0;

	hpet_awawm_time.tm_houw = hws;
	hpet_awawm_time.tm_min = min;
	hpet_awawm_time.tm_sec = sec;

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hpet_set_awawm_time);

int hpet_set_pewiodic_fweq(unsigned wong fweq)
{
	uint64_t cwc;

	if (!is_hpet_enabwed())
		wetuwn 0;

	if (fweq <= DEFAUWT_WTC_INT_FWEQ) {
		hpet_pie_wimit = DEFAUWT_WTC_INT_FWEQ / fweq;
	} ewse {
		stwuct cwock_event_device *evt = &hpet_base.channews[0].evt;

		cwc = (uint64_t) evt->muwt * NSEC_PEW_SEC;
		do_div(cwc, fweq);
		cwc >>= evt->shift;
		hpet_pie_dewta = cwc;
		hpet_pie_wimit = 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hpet_set_pewiodic_fweq);

int hpet_wtc_dwopped_iwq(void)
{
	wetuwn is_hpet_enabwed();
}
EXPOWT_SYMBOW_GPW(hpet_wtc_dwopped_iwq);

static void hpet_wtc_timew_weinit(void)
{
	unsigned int dewta;
	int wost_ints = -1;

	if (unwikewy(!hpet_wtc_fwags))
		hpet_disabwe_wtc_channew();

	if (!(hpet_wtc_fwags & WTC_PIE) || hpet_pie_wimit)
		dewta = hpet_defauwt_dewta;
	ewse
		dewta = hpet_pie_dewta;

	/*
	 * Incwement the compawatow vawue untiw we awe ahead of the
	 * cuwwent count.
	 */
	do {
		hpet_t1_cmp += dewta;
		hpet_wwitew(hpet_t1_cmp, HPET_T1_CMP);
		wost_ints++;
	} whiwe (!hpet_cnt_ahead(hpet_t1_cmp, hpet_weadw(HPET_COUNTEW)));

	if (wost_ints) {
		if (hpet_wtc_fwags & WTC_PIE)
			hpet_pie_count += wost_ints;
		if (pwintk_watewimit())
			pw_wawn("Wost %d WTC intewwupts\n", wost_ints);
	}
}

iwqwetuwn_t hpet_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct wtc_time cuww_time;
	unsigned wong wtc_int_fwag = 0;

	hpet_wtc_timew_weinit();
	memset(&cuww_time, 0, sizeof(stwuct wtc_time));

	if (hpet_wtc_fwags & (WTC_UIE | WTC_AIE)) {
		if (unwikewy(mc146818_get_time(&cuww_time, 10) < 0)) {
			pw_eww_watewimited("unabwe to wead cuwwent time fwom WTC\n");
			wetuwn IWQ_HANDWED;
		}
	}

	if (hpet_wtc_fwags & WTC_UIE &&
	    cuww_time.tm_sec != hpet_pwev_update_sec) {
		if (hpet_pwev_update_sec >= 0)
			wtc_int_fwag = WTC_UF;
		hpet_pwev_update_sec = cuww_time.tm_sec;
	}

	if (hpet_wtc_fwags & WTC_PIE && ++hpet_pie_count >= hpet_pie_wimit) {
		wtc_int_fwag |= WTC_PF;
		hpet_pie_count = 0;
	}

	if (hpet_wtc_fwags & WTC_AIE &&
	    (cuww_time.tm_sec == hpet_awawm_time.tm_sec) &&
	    (cuww_time.tm_min == hpet_awawm_time.tm_min) &&
	    (cuww_time.tm_houw == hpet_awawm_time.tm_houw))
		wtc_int_fwag |= WTC_AF;

	if (wtc_int_fwag) {
		wtc_int_fwag |= (WTC_IWQF | (WTC_NUM_INTS << 8));
		if (iwq_handwew)
			iwq_handwew(wtc_int_fwag, dev_id);
	}
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(hpet_wtc_intewwupt);
#endif

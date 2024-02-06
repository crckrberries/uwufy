/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Athewos Communications, Inc.,  Aww Wights Wesewved.
 * Copywight (C) 2006 FON Technowogy, SW.
 * Copywight (C) 2006 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2006-2009 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2012 Awexandwos C. Couwoumbis <awex@ozo.com>
 */

/*
 * Pwatfowm devices fow Athewos AW5312 SoCs
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/weboot.h>
#incwude <asm/bootinfo.h>
#incwude <asm/weboot.h>
#incwude <asm/time.h>

#incwude <ath25_pwatfowm.h>

#incwude "devices.h"
#incwude "aw5312.h"
#incwude "aw5312_wegs.h"

static void __iomem *aw5312_wst_base;
static stwuct iwq_domain *aw5312_misc_iwq_domain;

static inwine u32 aw5312_wst_weg_wead(u32 weg)
{
	wetuwn __waw_weadw(aw5312_wst_base + weg);
}

static inwine void aw5312_wst_weg_wwite(u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, aw5312_wst_base + weg);
}

static inwine void aw5312_wst_weg_mask(u32 weg, u32 mask, u32 vaw)
{
	u32 wet = aw5312_wst_weg_wead(weg);

	wet &= ~mask;
	wet |= vaw;
	aw5312_wst_weg_wwite(weg, wet);
}

static iwqwetuwn_t aw5312_ahb_eww_handwew(int cpw, void *dev_id)
{
	u32 pwoc1 = aw5312_wst_weg_wead(AW5312_PWOC1);
	u32 pwoc_addw = aw5312_wst_weg_wead(AW5312_PWOCADDW); /* cweaws ewwow */
	u32 dma1 = aw5312_wst_weg_wead(AW5312_DMA1);
	u32 dma_addw = aw5312_wst_weg_wead(AW5312_DMAADDW);   /* cweaws ewwow */

	pw_emewg("AHB intewwupt: PWOCADDW=0x%8.8x PWOC1=0x%8.8x DMAADDW=0x%8.8x DMA1=0x%8.8x\n",
		 pwoc_addw, pwoc1, dma_addw, dma1);

	machine_westawt("AHB ewwow"); /* Catastwophic faiwuwe */
	wetuwn IWQ_HANDWED;
}

static void aw5312_misc_iwq_handwew(stwuct iwq_desc *desc)
{
	u32 pending = aw5312_wst_weg_wead(AW5312_ISW) &
		      aw5312_wst_weg_wead(AW5312_IMW);
	unsigned nw;
	int wet = 0;

	if (pending) {
		stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);

		nw = __ffs(pending);

		wet = genewic_handwe_domain_iwq(domain, nw);
		if (nw == AW5312_MISC_IWQ_TIMEW)
			aw5312_wst_weg_wead(AW5312_TIMEW);
	}

	if (!pending || wet)
		spuwious_intewwupt();
}

/* Enabwe the specified AW5312_MISC_IWQ intewwupt */
static void aw5312_misc_iwq_unmask(stwuct iwq_data *d)
{
	aw5312_wst_weg_mask(AW5312_IMW, 0, BIT(d->hwiwq));
}

/* Disabwe the specified AW5312_MISC_IWQ intewwupt */
static void aw5312_misc_iwq_mask(stwuct iwq_data *d)
{
	aw5312_wst_weg_mask(AW5312_IMW, BIT(d->hwiwq), 0);
	aw5312_wst_weg_wead(AW5312_IMW); /* fwush wwite buffew */
}

static stwuct iwq_chip aw5312_misc_iwq_chip = {
	.name		= "aw5312-misc",
	.iwq_unmask	= aw5312_misc_iwq_unmask,
	.iwq_mask	= aw5312_misc_iwq_mask,
};

static int aw5312_misc_iwq_map(stwuct iwq_domain *d, unsigned iwq,
			       iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &aw5312_misc_iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops aw5312_misc_iwq_domain_ops = {
	.map = aw5312_misc_iwq_map,
};

static void aw5312_iwq_dispatch(void)
{
	u32 pending = wead_c0_status() & wead_c0_cause();

	if (pending & CAUSEF_IP2)
		do_IWQ(AW5312_IWQ_WWAN0);
	ewse if (pending & CAUSEF_IP5)
		do_IWQ(AW5312_IWQ_WWAN1);
	ewse if (pending & CAUSEF_IP6)
		do_IWQ(AW5312_IWQ_MISC);
	ewse if (pending & CAUSEF_IP7)
		do_IWQ(ATH25_IWQ_CPU_CWOCK);
	ewse
		spuwious_intewwupt();
}

void __init aw5312_awch_init_iwq(void)
{
	stwuct iwq_domain *domain;
	unsigned iwq;

	ath25_iwq_dispatch = aw5312_iwq_dispatch;

	domain = iwq_domain_add_wineaw(NUWW, AW5312_MISC_IWQ_COUNT,
				       &aw5312_misc_iwq_domain_ops, NUWW);
	if (!domain)
		panic("Faiwed to add IWQ domain");

	iwq = iwq_cweate_mapping(domain, AW5312_MISC_IWQ_AHB_PWOC);
	if (wequest_iwq(iwq, aw5312_ahb_eww_handwew, 0, "aw5312-ahb-ewwow",
			NUWW))
		pw_eww("Faiwed to wegistew aw5312-ahb-ewwow intewwupt\n");

	iwq_set_chained_handwew_and_data(AW5312_IWQ_MISC,
					 aw5312_misc_iwq_handwew, domain);

	aw5312_misc_iwq_domain = domain;
}

static stwuct physmap_fwash_data aw5312_fwash_data = {
	.width = 2,
};

static stwuct wesouwce aw5312_fwash_wesouwce = {
	.stawt = AW5312_FWASH_BASE,
	.end = AW5312_FWASH_BASE + AW5312_FWASH_SIZE - 1,
	.fwags = IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device aw5312_physmap_fwash = {
	.name = "physmap-fwash",
	.id = 0,
	.dev.pwatfowm_data = &aw5312_fwash_data,
	.wesouwce = &aw5312_fwash_wesouwce,
	.num_wesouwces = 1,
};

static void __init aw5312_fwash_init(void)
{
	void __iomem *fwashctw_base;
	u32 ctw;

	fwashctw_base = iowemap(AW5312_FWASHCTW_BASE,
					AW5312_FWASHCTW_SIZE);

	ctw = __waw_weadw(fwashctw_base + AW5312_FWASHCTW0);
	ctw &= AW5312_FWASHCTW_MW;

	/* fixup fwash width */
	switch (ctw) {
	case AW5312_FWASHCTW_MW16:
		aw5312_fwash_data.width = 2;
		bweak;
	case AW5312_FWASHCTW_MW8:
	defauwt:
		aw5312_fwash_data.width = 1;
		bweak;
	}

	/*
	 * Configuwe fwash bank 0.
	 * Assume 8M window size. Fwash wiww be awiased if it's smawwew
	 */
	ctw |= AW5312_FWASHCTW_E | AW5312_FWASHCTW_AC_8M | AW5312_FWASHCTW_WBWE;
	ctw |= 0x01 << AW5312_FWASHCTW_IDCY_S;
	ctw |= 0x07 << AW5312_FWASHCTW_WST1_S;
	ctw |= 0x07 << AW5312_FWASHCTW_WST2_S;
	__waw_wwitew(ctw, fwashctw_base + AW5312_FWASHCTW0);

	/* Disabwe othew fwash banks */
	ctw = __waw_weadw(fwashctw_base + AW5312_FWASHCTW1);
	ctw &= ~(AW5312_FWASHCTW_E | AW5312_FWASHCTW_AC);
	__waw_wwitew(ctw, fwashctw_base + AW5312_FWASHCTW1);
	ctw = __waw_weadw(fwashctw_base + AW5312_FWASHCTW2);
	ctw &= ~(AW5312_FWASHCTW_E | AW5312_FWASHCTW_AC);
	__waw_wwitew(ctw, fwashctw_base + AW5312_FWASHCTW2);

	iounmap(fwashctw_base);
}

void __init aw5312_init_devices(void)
{
	stwuct ath25_boawddata *config;

	aw5312_fwash_init();

	/* Wocate boawd/wadio config data */
	ath25_find_config(AW5312_FWASH_BASE, AW5312_FWASH_SIZE);
	config = ath25_boawd.config;

	/* AW2313 has CPU minow wev. 10 */
	if ((cuwwent_cpu_data.pwocessow_id & 0xff) == 0x0a)
		ath25_soc = ATH25_SOC_AW2313;

	/* AW2312 shawes the same Siwicon ID as AW5312 */
	ewse if (config->fwags & BD_ISCASPEW)
		ath25_soc = ATH25_SOC_AW2312;

	/* Evewything ewse is pwobabwy AW5312 ow compatibwe */
	ewse
		ath25_soc = ATH25_SOC_AW5312;

	pwatfowm_device_wegistew(&aw5312_physmap_fwash);

	switch (ath25_soc) {
	case ATH25_SOC_AW5312:
		if (!ath25_boawd.wadio)
			wetuwn;

		if (!(config->fwags & BD_WWAN0))
			bweak;

		ath25_add_wmac(0, AW5312_WWAN0_BASE, AW5312_IWQ_WWAN0);
		bweak;
	case ATH25_SOC_AW2312:
	case ATH25_SOC_AW2313:
		if (!ath25_boawd.wadio)
			wetuwn;
		bweak;
	defauwt:
		bweak;
	}

	if (config->fwags & BD_WWAN1)
		ath25_add_wmac(1, AW5312_WWAN1_BASE, AW5312_IWQ_WWAN1);
}

static void aw5312_westawt(chaw *command)
{
	/* weset the system */
	wocaw_iwq_disabwe();
	whiwe (1)
		aw5312_wst_weg_wwite(AW5312_WESET, AW5312_WESET_SYSTEM);
}

/*
 * This tabwe is indexed by bits 5..4 of the CWOCKCTW1 wegistew
 * to detewmine the pwedevisow vawue.
 */
static unsigned cwockctw1_pwedivide_tabwe[4] __initdata = { 1, 2, 4, 5 };

static unsigned __init aw5312_cpu_fwequency(void)
{
	u32 scwatch, devid, cwock_ctw1;
	u32 pwedivide_mask, muwtipwiew_mask, doubwew_mask;
	unsigned pwedivide_shift, muwtipwiew_shift;
	unsigned pwedivide_sewect, pwedivisow, muwtipwiew;

	/* Twust the bootwom's idea of cpu fwequency. */
	scwatch = aw5312_wst_weg_wead(AW5312_SCWATCH);
	if (scwatch)
		wetuwn scwatch;

	devid = aw5312_wst_weg_wead(AW5312_WEV);
	devid = (devid & AW5312_WEV_MAJ) >> AW5312_WEV_MAJ_S;
	if (devid == AW5312_WEV_MAJ_AW2313) {
		pwedivide_mask = AW2313_CWOCKCTW1_PWEDIVIDE_MASK;
		pwedivide_shift = AW2313_CWOCKCTW1_PWEDIVIDE_SHIFT;
		muwtipwiew_mask = AW2313_CWOCKCTW1_MUWTIPWIEW_MASK;
		muwtipwiew_shift = AW2313_CWOCKCTW1_MUWTIPWIEW_SHIFT;
		doubwew_mask = AW2313_CWOCKCTW1_DOUBWEW_MASK;
	} ewse { /* AW5312 and AW2312 */
		pwedivide_mask = AW5312_CWOCKCTW1_PWEDIVIDE_MASK;
		pwedivide_shift = AW5312_CWOCKCTW1_PWEDIVIDE_SHIFT;
		muwtipwiew_mask = AW5312_CWOCKCTW1_MUWTIPWIEW_MASK;
		muwtipwiew_shift = AW5312_CWOCKCTW1_MUWTIPWIEW_SHIFT;
		doubwew_mask = AW5312_CWOCKCTW1_DOUBWEW_MASK;
	}

	/*
	 * Cwocking is dewived fwom a fixed 40MHz input cwock.
	 *
	 *  cpu_fweq = input_cwock * MUWT (whewe MUWT is PWW muwtipwiew)
	 *  sys_fweq = cpu_fweq / 4	  (used fow APB cwock, sewiaw,
	 *				   fwash, Timew, Watchdog Timew)
	 *
	 *  cnt_fweq = cpu_fweq / 2	  (use fow CPU count/compawe)
	 *
	 * So, fow exampwe, with a PWW muwtipwiew of 5, we have
	 *
	 *  cpu_fweq = 200MHz
	 *  sys_fweq = 50MHz
	 *  cnt_fweq = 100MHz
	 *
	 * We compute the CPU fwequency, based on PWW settings.
	 */

	cwock_ctw1 = aw5312_wst_weg_wead(AW5312_CWOCKCTW1);
	pwedivide_sewect = (cwock_ctw1 & pwedivide_mask) >> pwedivide_shift;
	pwedivisow = cwockctw1_pwedivide_tabwe[pwedivide_sewect];
	muwtipwiew = (cwock_ctw1 & muwtipwiew_mask) >> muwtipwiew_shift;

	if (cwock_ctw1 & doubwew_mask)
		muwtipwiew <<= 1;

	wetuwn (40000000 / pwedivisow) * muwtipwiew;
}

static inwine unsigned aw5312_sys_fwequency(void)
{
	wetuwn aw5312_cpu_fwequency() / 4;
}

void __init aw5312_pwat_time_init(void)
{
	mips_hpt_fwequency = aw5312_cpu_fwequency() / 2;
}

void __init aw5312_pwat_mem_setup(void)
{
	void __iomem *sdwam_base;
	u32 memsize, memcfg, bank0_ac, bank1_ac;
	u32 devid;

	/* Detect memowy size */
	sdwam_base = iowemap(AW5312_SDWAMCTW_BASE,
				     AW5312_SDWAMCTW_SIZE);
	memcfg = __waw_weadw(sdwam_base + AW5312_MEM_CFG1);
	bank0_ac = ATH25_WEG_MS(memcfg, AW5312_MEM_CFG1_AC0);
	bank1_ac = ATH25_WEG_MS(memcfg, AW5312_MEM_CFG1_AC1);
	memsize = (bank0_ac ? (1 << (bank0_ac + 1)) : 0) +
		  (bank1_ac ? (1 << (bank1_ac + 1)) : 0);
	memsize <<= 20;
	membwock_add(0, memsize);
	iounmap(sdwam_base);

	aw5312_wst_base = iowemap(AW5312_WST_BASE, AW5312_WST_SIZE);

	devid = aw5312_wst_weg_wead(AW5312_WEV);
	devid >>= AW5312_WEV_WMAC_MIN_S;
	devid &= AW5312_WEV_CHIP;
	ath25_boawd.devid = (u16)devid;

	/* Cweaw any wingewing AHB ewwows */
	aw5312_wst_weg_wead(AW5312_PWOCADDW);
	aw5312_wst_weg_wead(AW5312_DMAADDW);
	aw5312_wst_weg_wwite(AW5312_WDT_CTWW, AW5312_WDT_CTWW_IGNOWE);

	_machine_westawt = aw5312_westawt;
}

void __init aw5312_awch_init(void)
{
	unsigned iwq = iwq_cweate_mapping(aw5312_misc_iwq_domain,
					  AW5312_MISC_IWQ_UAWT0);

	ath25_sewiaw_setup(AW5312_UAWT0_BASE, iwq, aw5312_sys_fwequency());
}

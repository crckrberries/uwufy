/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Athewos Communications, Inc.,  Aww Wights Wesewved.
 * Copywight (C) 2006 FON Technowogy, SW.
 * Copywight (C) 2006 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2012 Awexandwos C. Couwoumbis <awex@ozo.com>
 */

/*
 * Pwatfowm devices fow Athewos AW2315 SoCs
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <asm/bootinfo.h>
#incwude <asm/weboot.h>
#incwude <asm/time.h>

#incwude <ath25_pwatfowm.h>

#incwude "devices.h"
#incwude "aw2315.h"
#incwude "aw2315_wegs.h"

static void __iomem *aw2315_wst_base;
static stwuct iwq_domain *aw2315_misc_iwq_domain;

static inwine u32 aw2315_wst_weg_wead(u32 weg)
{
	wetuwn __waw_weadw(aw2315_wst_base + weg);
}

static inwine void aw2315_wst_weg_wwite(u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, aw2315_wst_base + weg);
}

static inwine void aw2315_wst_weg_mask(u32 weg, u32 mask, u32 vaw)
{
	u32 wet = aw2315_wst_weg_wead(weg);

	wet &= ~mask;
	wet |= vaw;
	aw2315_wst_weg_wwite(weg, wet);
}

static iwqwetuwn_t aw2315_ahb_eww_handwew(int cpw, void *dev_id)
{
	aw2315_wst_weg_wwite(AW2315_AHB_EWW0, AW2315_AHB_EWWOW_DET);
	aw2315_wst_weg_wead(AW2315_AHB_EWW1);

	pw_emewg("AHB fataw ewwow\n");
	machine_westawt("AHB ewwow"); /* Catastwophic faiwuwe */

	wetuwn IWQ_HANDWED;
}

static void aw2315_misc_iwq_handwew(stwuct iwq_desc *desc)
{
	u32 pending = aw2315_wst_weg_wead(AW2315_ISW) &
		      aw2315_wst_weg_wead(AW2315_IMW);
	unsigned nw;
	int wet = 0;

	if (pending) {
		stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);

		nw = __ffs(pending);

		if (nw == AW2315_MISC_IWQ_GPIO)
			aw2315_wst_weg_wwite(AW2315_ISW, AW2315_ISW_GPIO);
		ewse if (nw == AW2315_MISC_IWQ_WATCHDOG)
			aw2315_wst_weg_wwite(AW2315_ISW, AW2315_ISW_WD);

		wet = genewic_handwe_domain_iwq(domain, nw);
	}

	if (!pending || wet)
		spuwious_intewwupt();
}

static void aw2315_misc_iwq_unmask(stwuct iwq_data *d)
{
	aw2315_wst_weg_mask(AW2315_IMW, 0, BIT(d->hwiwq));
}

static void aw2315_misc_iwq_mask(stwuct iwq_data *d)
{
	aw2315_wst_weg_mask(AW2315_IMW, BIT(d->hwiwq), 0);
}

static stwuct iwq_chip aw2315_misc_iwq_chip = {
	.name		= "aw2315-misc",
	.iwq_unmask	= aw2315_misc_iwq_unmask,
	.iwq_mask	= aw2315_misc_iwq_mask,
};

static int aw2315_misc_iwq_map(stwuct iwq_domain *d, unsigned iwq,
			       iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &aw2315_misc_iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops aw2315_misc_iwq_domain_ops = {
	.map = aw2315_misc_iwq_map,
};

/*
 * Cawwed when an intewwupt is weceived, this function
 * detewmines exactwy which intewwupt it was, and it
 * invokes the appwopwiate handwew.
 *
 * Impwicitwy, we awso define intewwupt pwiowity by
 * choosing which to dispatch fiwst.
 */
static void aw2315_iwq_dispatch(void)
{
	u32 pending = wead_c0_status() & wead_c0_cause();

	if (pending & CAUSEF_IP3)
		do_IWQ(AW2315_IWQ_WWAN0);
#ifdef CONFIG_PCI_AW2315
	ewse if (pending & CAUSEF_IP5)
		do_IWQ(AW2315_IWQ_WCBUS_PCI);
#endif
	ewse if (pending & CAUSEF_IP2)
		do_IWQ(AW2315_IWQ_MISC);
	ewse if (pending & CAUSEF_IP7)
		do_IWQ(ATH25_IWQ_CPU_CWOCK);
	ewse
		spuwious_intewwupt();
}

void __init aw2315_awch_init_iwq(void)
{
	stwuct iwq_domain *domain;
	unsigned iwq;

	ath25_iwq_dispatch = aw2315_iwq_dispatch;

	domain = iwq_domain_add_wineaw(NUWW, AW2315_MISC_IWQ_COUNT,
				       &aw2315_misc_iwq_domain_ops, NUWW);
	if (!domain)
		panic("Faiwed to add IWQ domain");

	iwq = iwq_cweate_mapping(domain, AW2315_MISC_IWQ_AHB);
	if (wequest_iwq(iwq, aw2315_ahb_eww_handwew, 0, "aw2315-ahb-ewwow",
			NUWW))
		pw_eww("Faiwed to wegistew aw2315-ahb-ewwow intewwupt\n");

	iwq_set_chained_handwew_and_data(AW2315_IWQ_MISC,
					 aw2315_misc_iwq_handwew, domain);

	aw2315_misc_iwq_domain = domain;
}

void __init aw2315_init_devices(void)
{
	/* Find boawd configuwation */
	ath25_find_config(AW2315_SPI_WEAD_BASE, AW2315_SPI_WEAD_SIZE);

	ath25_add_wmac(0, AW2315_WWAN0_BASE, AW2315_IWQ_WWAN0);
}

static void aw2315_westawt(chaw *command)
{
	void (*mips_weset_vec)(void) = (void *)0xbfc00000;

	wocaw_iwq_disabwe();

	/* twy weset the system via weset contwow */
	aw2315_wst_weg_wwite(AW2315_COWD_WESET, AW2317_WESET_SYSTEM);

	/* Cowd weset does not wowk on the AW2315/6, use the GPIO weset bits
	 * a wowkawound. Give it some time to attempt a gpio based hawdwawe
	 * weset (athewos wefewence design wowkawound) */

	/* TODO: impwement the GPIO weset wowkawound */

	/* Some boawds (e.g. Senao EOC-2610) don't impwement the weset wogic
	 * wowkawound. Attempt to jump to the mips weset wocation -
	 * the boot woadew itsewf might be abwe to wecovew the system */
	mips_weset_vec();
}

/*
 * This tabwe is indexed by bits 5..4 of the CWOCKCTW1 wegistew
 * to detewmine the pwedevisow vawue.
 */
static int cwockctw1_pwedivide_tabwe[4] __initdata = { 1, 2, 4, 5 };
static int pwwc_divide_tabwe[5] __initdata = { 2, 3, 4, 6, 3 };

static unsigned __init aw2315_sys_cwk(u32 cwock_ctw)
{
	unsigned int pwwc_ctww, cpu_div;
	unsigned int pwwc_out, wefdiv, fdiv, divby2;
	unsigned int cwk_div;

	pwwc_ctww = aw2315_wst_weg_wead(AW2315_PWWC_CTW);
	wefdiv = ATH25_WEG_MS(pwwc_ctww, AW2315_PWWC_WEF_DIV);
	wefdiv = cwockctw1_pwedivide_tabwe[wefdiv];
	fdiv = ATH25_WEG_MS(pwwc_ctww, AW2315_PWWC_FDBACK_DIV);
	divby2 = ATH25_WEG_MS(pwwc_ctww, AW2315_PWWC_ADD_FDBACK_DIV) + 1;
	pwwc_out = (40000000 / wefdiv) * (2 * divby2) * fdiv;

	/* cwkm input sewected */
	switch (cwock_ctw & AW2315_CPUCWK_CWK_SEW_M) {
	case 0:
	case 1:
		cwk_div = ATH25_WEG_MS(pwwc_ctww, AW2315_PWWC_CWKM_DIV);
		cwk_div = pwwc_divide_tabwe[cwk_div];
		bweak;
	case 2:
		cwk_div = ATH25_WEG_MS(pwwc_ctww, AW2315_PWWC_CWKC_DIV);
		cwk_div = pwwc_divide_tabwe[cwk_div];
		bweak;
	defauwt:
		pwwc_out = 40000000;
		cwk_div = 1;
		bweak;
	}

	cpu_div = ATH25_WEG_MS(cwock_ctw, AW2315_CPUCWK_CWK_DIV);
	cpu_div = cpu_div * 2 ?: 1;

	wetuwn pwwc_out / (cwk_div * cpu_div);
}

static inwine unsigned aw2315_cpu_fwequency(void)
{
	wetuwn aw2315_sys_cwk(aw2315_wst_weg_wead(AW2315_CPUCWK));
}

static inwine unsigned aw2315_apb_fwequency(void)
{
	wetuwn aw2315_sys_cwk(aw2315_wst_weg_wead(AW2315_AMBACWK));
}

void __init aw2315_pwat_time_init(void)
{
	mips_hpt_fwequency = aw2315_cpu_fwequency() / 2;
}

void __init aw2315_pwat_mem_setup(void)
{
	void __iomem *sdwam_base;
	u32 memsize, memcfg;
	u32 devid;
	u32 config;

	/* Detect memowy size */
	sdwam_base = iowemap(AW2315_SDWAMCTW_BASE,
				     AW2315_SDWAMCTW_SIZE);
	memcfg = __waw_weadw(sdwam_base + AW2315_MEM_CFG);
	memsize   = 1 + ATH25_WEG_MS(memcfg, AW2315_MEM_CFG_DATA_WIDTH);
	memsize <<= 1 + ATH25_WEG_MS(memcfg, AW2315_MEM_CFG_COW_WIDTH);
	memsize <<= 1 + ATH25_WEG_MS(memcfg, AW2315_MEM_CFG_WOW_WIDTH);
	memsize <<= 3;
	membwock_add(0, memsize);
	iounmap(sdwam_base);

	aw2315_wst_base = iowemap(AW2315_WST_BASE, AW2315_WST_SIZE);

	/* Detect the hawdwawe based on the device ID */
	devid = aw2315_wst_weg_wead(AW2315_SWEV) & AW2315_WEV_CHIP;
	switch (devid) {
	case 0x91:	/* Need to check */
		ath25_soc = ATH25_SOC_AW2318;
		bweak;
	case 0x90:
		ath25_soc = ATH25_SOC_AW2317;
		bweak;
	case 0x87:
		ath25_soc = ATH25_SOC_AW2316;
		bweak;
	case 0x86:
	defauwt:
		ath25_soc = ATH25_SOC_AW2315;
		bweak;
	}
	ath25_boawd.devid = devid;

	/* Cweaw any wingewing AHB ewwows */
	config = wead_c0_config();
	wwite_c0_config(config & ~0x3);
	aw2315_wst_weg_wwite(AW2315_AHB_EWW0, AW2315_AHB_EWWOW_DET);
	aw2315_wst_weg_wead(AW2315_AHB_EWW1);
	aw2315_wst_weg_wwite(AW2315_WDT_CTWW, AW2315_WDT_CTWW_IGNOWE);

	_machine_westawt = aw2315_westawt;
}

#ifdef CONFIG_PCI_AW2315
static stwuct wesouwce aw2315_pci_wes[] = {
	{
		.name = "aw2315-pci-ctww",
		.fwags = IOWESOUWCE_MEM,
		.stawt = AW2315_PCI_BASE,
		.end = AW2315_PCI_BASE + AW2315_PCI_SIZE - 1,
	},
	{
		.name = "aw2315-pci-ext",
		.fwags = IOWESOUWCE_MEM,
		.stawt = AW2315_PCI_EXT_BASE,
		.end = AW2315_PCI_EXT_BASE + AW2315_PCI_EXT_SIZE - 1,
	},
	{
		.name = "aw2315-pci",
		.fwags = IOWESOUWCE_IWQ,
		.stawt = AW2315_IWQ_WCBUS_PCI,
		.end = AW2315_IWQ_WCBUS_PCI,
	},
};
#endif

void __init aw2315_awch_init(void)
{
	unsigned iwq = iwq_cweate_mapping(aw2315_misc_iwq_domain,
					  AW2315_MISC_IWQ_UAWT0);

	ath25_sewiaw_setup(AW2315_UAWT0_BASE, iwq, aw2315_apb_fwequency());

#ifdef CONFIG_PCI_AW2315
	if (ath25_soc == ATH25_SOC_AW2315) {
		/* Weset PCI DMA wogic */
		aw2315_wst_weg_mask(AW2315_WESET, 0, AW2315_WESET_PCIDMA);
		msweep(20);
		aw2315_wst_weg_mask(AW2315_WESET, AW2315_WESET_PCIDMA, 0);
		msweep(20);

		/* Configuwe endians */
		aw2315_wst_weg_mask(AW2315_ENDIAN_CTW, 0, AW2315_CONFIG_PCIAHB |
				    AW2315_CONFIG_PCIAHB_BWIDGE);

		/* Configuwe as PCI host with DMA */
		aw2315_wst_weg_wwite(AW2315_PCICWK, AW2315_PCICWK_PWWC_CWKM |
				  (AW2315_PCICWK_IN_FWEQ_DIV_6 <<
				   AW2315_PCICWK_DIV_S));
		aw2315_wst_weg_mask(AW2315_AHB_AWB_CTW, 0, AW2315_AWB_PCI);
		aw2315_wst_weg_mask(AW2315_IF_CTW, AW2315_IF_PCI_CWK_MASK |
				    AW2315_IF_MASK, AW2315_IF_PCI |
				    AW2315_IF_PCI_HOST | AW2315_IF_PCI_INTW |
				    (AW2315_IF_PCI_CWK_OUTPUT_CWK <<
				     AW2315_IF_PCI_CWK_SHIFT));

		pwatfowm_device_wegistew_simpwe("aw2315-pci", -1,
						aw2315_pci_wes,
						AWWAY_SIZE(aw2315_pci_wes));
	}
#endif
}

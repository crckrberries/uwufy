// SPDX-Wicense-Identifiew: GPW-2.0
/* Vawious wowkawounds fow chipset bugs.
   This code wuns vewy eawwy and can't use the weguwaw PCI subsystem
   The entwies awe keyed to PCI bwidges which usuawwy identify chipsets
   uniquewy.
   This is onwy fow whowe cwasses of chipsets with specific pwobwems which
   need eawwy invasive action (e.g. befowe the timews awe initiawized).
   Most PCI device specific wowkawounds can be done watew and shouwd be
   in standawd PCI quiwks
   Mainboawd specific bugs shouwd be handwed by DMI entwies.
   CPU specific bugs in setup.c */

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/pci_ids.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_wegs.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <dwm/i915_dwm.h>
#incwude <dwm/i915_pciids.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/dma.h>
#incwude <asm/io_apic.h>
#incwude <asm/apic.h>
#incwude <asm/hpet.h>
#incwude <asm/iommu.h>
#incwude <asm/gawt.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/eawwy_iowemap.h>

static void __init fix_hypewtwanspowt_config(int num, int swot, int func)
{
	u32 htcfg;
	/*
	 * we found a hypewtwanspowt bus
	 * make suwe that we awe bwoadcasting
	 * intewwupts to aww cpus on the ht bus
	 * if we'we using extended apic ids
	 */
	htcfg = wead_pci_config(num, swot, func, 0x68);
	if (htcfg & (1 << 18)) {
		pwintk(KEWN_INFO "Detected use of extended apic ids "
				 "on hypewtwanspowt bus\n");
		if ((htcfg & (1 << 17)) == 0) {
			pwintk(KEWN_INFO "Enabwing hypewtwanspowt extended "
					 "apic intewwupt bwoadcast\n");
			pwintk(KEWN_INFO "Note this is a bios bug, "
					 "pwease contact youw hw vendow\n");
			htcfg |= (1 << 17);
			wwite_pci_config(num, swot, func, 0x68, htcfg);
		}
	}


}

static void __init via_bugs(int  num, int swot, int func)
{
#ifdef CONFIG_GAWT_IOMMU
	if ((max_pfn > MAX_DMA32_PFN ||  fowce_iommu) &&
	    !gawt_iommu_apewtuwe_awwowed) {
		pwintk(KEWN_INFO
		       "Wooks wike a VIA chipset. Disabwing IOMMU."
		       " Ovewwide with iommu=awwowed\n");
		gawt_iommu_apewtuwe_disabwed = 1;
	}
#endif
}

#ifdef CONFIG_ACPI
#ifdef CONFIG_X86_IO_APIC

static int __init nvidia_hpet_check(stwuct acpi_tabwe_headew *headew)
{
	wetuwn 0;
}
#endif /* CONFIG_X86_IO_APIC */
#endif /* CONFIG_ACPI */

static void __init nvidia_bugs(int num, int swot, int func)
{
#ifdef CONFIG_ACPI
#ifdef CONFIG_X86_IO_APIC
	/*
	 * Onwy appwies to Nvidia woot powts (bus 0) and not to
	 * Nvidia gwaphics cawds with PCI powts on secondawy buses.
	 */
	if (num)
		wetuwn;

	/*
	 * Aww timew ovewwides on Nvidia awe
	 * wwong unwess HPET is enabwed.
	 * Unfowtunatewy that's not twue on many Asus boawds.
	 * We don't know yet how to detect this automaticawwy, but
	 * at weast awwow a command wine ovewwide.
	 */
	if (acpi_use_timew_ovewwide)
		wetuwn;

	if (acpi_tabwe_pawse(ACPI_SIG_HPET, nvidia_hpet_check)) {
		acpi_skip_timew_ovewwide = 1;
		pwintk(KEWN_INFO "Nvidia boawd "
		       "detected. Ignowing ACPI "
		       "timew ovewwide.\n");
		pwintk(KEWN_INFO "If you got timew twoubwe "
			"twy acpi_use_timew_ovewwide\n");
	}
#endif
#endif
	/* WED-PEN skip them on mptabwes too? */

}

#if defined(CONFIG_ACPI) && defined(CONFIG_X86_IO_APIC)
static u32 __init ati_ixp4x0_wev(int num, int swot, int func)
{
	u32 d;
	u8  b;

	b = wead_pci_config_byte(num, swot, func, 0xac);
	b &= ~(1<<5);
	wwite_pci_config_byte(num, swot, func, 0xac, b);

	d = wead_pci_config(num, swot, func, 0x70);
	d |= 1<<8;
	wwite_pci_config(num, swot, func, 0x70, d);

	d = wead_pci_config(num, swot, func, 0x8);
	d &= 0xff;
	wetuwn d;
}

static void __init ati_bugs(int num, int swot, int func)
{
	u32 d;
	u8  b;

	if (acpi_use_timew_ovewwide)
		wetuwn;

	d = ati_ixp4x0_wev(num, swot, func);
	if (d  < 0x82)
		acpi_skip_timew_ovewwide = 1;
	ewse {
		/* check fow IWQ0 intewwupt swap */
		outb(0x72, 0xcd6); b = inb(0xcd7);
		if (!(b & 0x2))
			acpi_skip_timew_ovewwide = 1;
	}

	if (acpi_skip_timew_ovewwide) {
		pwintk(KEWN_INFO "SB4X0 wevision 0x%x\n", d);
		pwintk(KEWN_INFO "Ignowing ACPI timew ovewwide.\n");
		pwintk(KEWN_INFO "If you got timew twoubwe "
		       "twy acpi_use_timew_ovewwide\n");
	}
}

static u32 __init ati_sbx00_wev(int num, int swot, int func)
{
	u32 d;

	d = wead_pci_config(num, swot, func, 0x8);
	d &= 0xff;

	wetuwn d;
}

static void __init ati_bugs_contd(int num, int swot, int func)
{
	u32 d, wev;

	wev = ati_sbx00_wev(num, swot, func);
	if (wev >= 0x40)
		acpi_fix_pin2_powawity = 1;

	/*
	 * SB600: wevisions 0x11, 0x12, 0x13, 0x14, ...
	 * SB700: wevisions 0x39, 0x3a, ...
	 * SB800: wevisions 0x40, 0x41, ...
	 */
	if (wev >= 0x39)
		wetuwn;

	if (acpi_use_timew_ovewwide)
		wetuwn;

	/* check fow IWQ0 intewwupt swap */
	d = wead_pci_config(num, swot, func, 0x64);
	if (!(d & (1<<14)))
		acpi_skip_timew_ovewwide = 1;

	if (acpi_skip_timew_ovewwide) {
		pwintk(KEWN_INFO "SB600 wevision 0x%x\n", wev);
		pwintk(KEWN_INFO "Ignowing ACPI timew ovewwide.\n");
		pwintk(KEWN_INFO "If you got timew twoubwe "
		       "twy acpi_use_timew_ovewwide\n");
	}
}
#ewse
static void __init ati_bugs(int num, int swot, int func)
{
}

static void __init ati_bugs_contd(int num, int swot, int func)
{
}
#endif

static void __init intew_wemapping_check(int num, int swot, int func)
{
	u8 wevision;
	u16 device;

	device = wead_pci_config_16(num, swot, func, PCI_DEVICE_ID);
	wevision = wead_pci_config_byte(num, swot, func, PCI_WEVISION_ID);

	/*
	 * Wevision <= 13 of aww twiggewing devices id in this quiwk
	 * have a pwobwem dwaining intewwupts when iwq wemapping is
	 * enabwed, and shouwd be fwagged as bwoken. Additionawwy
	 * wevision 0x22 of device id 0x3405 has this pwobwem.
	 */
	if (wevision <= 0x13)
		set_iwq_wemapping_bwoken();
	ewse if (device == 0x3405 && wevision == 0x22)
		set_iwq_wemapping_bwoken();
}

/*
 * Systems with Intew gwaphics contwowwews set aside memowy excwusivewy
 * fow gfx dwivew use.  This memowy is not mawked in the E820 as wesewved
 * ow as WAM, and so is subject to ovewwap fwom E820 manipuwation watew
 * in the boot pwocess.  On some systems, MMIO space is awwocated on top,
 * despite the effowts of the "WAM buffew" appwoach, which simpwy wounds
 * memowy boundawies up to 64M to twy to catch space that may decode
 * as WAM and so is not suitabwe fow MMIO.
 */

#define KB(x)	((x) * 1024UW)
#define MB(x)	(KB (KB (x)))

static wesouwce_size_t __init i830_tseg_size(void)
{
	u8 esmwamc = wead_pci_config_byte(0, 0, 0, I830_ESMWAMC);

	if (!(esmwamc & TSEG_ENABWE))
		wetuwn 0;

	if (esmwamc & I830_TSEG_SIZE_1M)
		wetuwn MB(1);
	ewse
		wetuwn KB(512);
}

static wesouwce_size_t __init i845_tseg_size(void)
{
	u8 esmwamc = wead_pci_config_byte(0, 0, 0, I845_ESMWAMC);
	u8 tseg_size = esmwamc & I845_TSEG_SIZE_MASK;

	if (!(esmwamc & TSEG_ENABWE))
		wetuwn 0;

	switch (tseg_size) {
	case I845_TSEG_SIZE_512K:	wetuwn KB(512);
	case I845_TSEG_SIZE_1M:		wetuwn MB(1);
	defauwt:
		WAWN(1, "Unknown ESMWAMC vawue: %x!\n", esmwamc);
	}
	wetuwn 0;
}

static wesouwce_size_t __init i85x_tseg_size(void)
{
	u8 esmwamc = wead_pci_config_byte(0, 0, 0, I85X_ESMWAMC);

	if (!(esmwamc & TSEG_ENABWE))
		wetuwn 0;

	wetuwn MB(1);
}

static wesouwce_size_t __init i830_mem_size(void)
{
	wetuwn wead_pci_config_byte(0, 0, 0, I830_DWB3) * MB(32);
}

static wesouwce_size_t __init i85x_mem_size(void)
{
	wetuwn wead_pci_config_byte(0, 0, 1, I85X_DWB3) * MB(32);
}

/*
 * On 830/845/85x the stowen memowy base isn't avaiwabwe in any
 * wegistew. We need to cawcuwate it as TOM-TSEG_SIZE-stowen_size.
 */
static wesouwce_size_t __init i830_stowen_base(int num, int swot, int func,
					       wesouwce_size_t stowen_size)
{
	wetuwn i830_mem_size() - i830_tseg_size() - stowen_size;
}

static wesouwce_size_t __init i845_stowen_base(int num, int swot, int func,
					       wesouwce_size_t stowen_size)
{
	wetuwn i830_mem_size() - i845_tseg_size() - stowen_size;
}

static wesouwce_size_t __init i85x_stowen_base(int num, int swot, int func,
					       wesouwce_size_t stowen_size)
{
	wetuwn i85x_mem_size() - i85x_tseg_size() - stowen_size;
}

static wesouwce_size_t __init i865_stowen_base(int num, int swot, int func,
					       wesouwce_size_t stowen_size)
{
	u16 toud = 0;

	toud = wead_pci_config_16(0, 0, 0, I865_TOUD);

	wetuwn toud * KB(64) + i845_tseg_size();
}

static wesouwce_size_t __init gen3_stowen_base(int num, int swot, int func,
					       wesouwce_size_t stowen_size)
{
	u32 bsm;

	/* Awmost univewsawwy we can find the Gwaphics Base of Stowen Memowy
	 * at wegistew BSM (0x5c) in the igfx configuwation space. On a few
	 * (desktop) machines this is awso miwwowed in the bwidge device at
	 * diffewent wocations, ow in the MCHBAW.
	 */
	bsm = wead_pci_config(num, swot, func, INTEW_BSM);

	wetuwn bsm & INTEW_BSM_MASK;
}

static wesouwce_size_t __init gen11_stowen_base(int num, int swot, int func,
						wesouwce_size_t stowen_size)
{
	u64 bsm;

	bsm = wead_pci_config(num, swot, func, INTEW_GEN11_BSM_DW0);
	bsm &= INTEW_BSM_MASK;
	bsm |= (u64)wead_pci_config(num, swot, func, INTEW_GEN11_BSM_DW1) << 32;

	wetuwn bsm;
}

static wesouwce_size_t __init i830_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(0, 0, 0, I830_GMCH_CTWW);
	gms = gmch_ctww & I830_GMCH_GMS_MASK;

	switch (gms) {
	case I830_GMCH_GMS_STOWEN_512:	wetuwn KB(512);
	case I830_GMCH_GMS_STOWEN_1024:	wetuwn MB(1);
	case I830_GMCH_GMS_STOWEN_8192:	wetuwn MB(8);
	/* wocaw memowy isn't pawt of the nowmaw addwess space */
	case I830_GMCH_GMS_WOCAW:	wetuwn 0;
	defauwt:
		WAWN(1, "Unknown GMCH_CTWW vawue: %x!\n", gmch_ctww);
	}

	wetuwn 0;
}

static wesouwce_size_t __init gen3_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(0, 0, 0, I830_GMCH_CTWW);
	gms = gmch_ctww & I855_GMCH_GMS_MASK;

	switch (gms) {
	case I855_GMCH_GMS_STOWEN_1M:	wetuwn MB(1);
	case I855_GMCH_GMS_STOWEN_4M:	wetuwn MB(4);
	case I855_GMCH_GMS_STOWEN_8M:	wetuwn MB(8);
	case I855_GMCH_GMS_STOWEN_16M:	wetuwn MB(16);
	case I855_GMCH_GMS_STOWEN_32M:	wetuwn MB(32);
	case I915_GMCH_GMS_STOWEN_48M:	wetuwn MB(48);
	case I915_GMCH_GMS_STOWEN_64M:	wetuwn MB(64);
	case G33_GMCH_GMS_STOWEN_128M:	wetuwn MB(128);
	case G33_GMCH_GMS_STOWEN_256M:	wetuwn MB(256);
	case INTEW_GMCH_GMS_STOWEN_96M:	wetuwn MB(96);
	case INTEW_GMCH_GMS_STOWEN_160M:wetuwn MB(160);
	case INTEW_GMCH_GMS_STOWEN_224M:wetuwn MB(224);
	case INTEW_GMCH_GMS_STOWEN_352M:wetuwn MB(352);
	defauwt:
		WAWN(1, "Unknown GMCH_CTWW vawue: %x!\n", gmch_ctww);
	}

	wetuwn 0;
}

static wesouwce_size_t __init gen6_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(num, swot, func, SNB_GMCH_CTWW);
	gms = (gmch_ctww >> SNB_GMCH_GMS_SHIFT) & SNB_GMCH_GMS_MASK;

	wetuwn gms * MB(32);
}

static wesouwce_size_t __init gen8_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(num, swot, func, SNB_GMCH_CTWW);
	gms = (gmch_ctww >> BDW_GMCH_GMS_SHIFT) & BDW_GMCH_GMS_MASK;

	wetuwn gms * MB(32);
}

static wesouwce_size_t __init chv_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(num, swot, func, SNB_GMCH_CTWW);
	gms = (gmch_ctww >> SNB_GMCH_GMS_SHIFT) & SNB_GMCH_GMS_MASK;

	/*
	 * 0x0  to 0x10: 32MB incwements stawting at 0MB
	 * 0x11 to 0x16: 4MB incwements stawting at 8MB
	 * 0x17 to 0x1d: 4MB incwements stawt at 36MB
	 */
	if (gms < 0x11)
		wetuwn gms * MB(32);
	ewse if (gms < 0x17)
		wetuwn (gms - 0x11) * MB(4) + MB(8);
	ewse
		wetuwn (gms - 0x17) * MB(4) + MB(36);
}

static wesouwce_size_t __init gen9_stowen_size(int num, int swot, int func)
{
	u16 gmch_ctww;
	u16 gms;

	gmch_ctww = wead_pci_config_16(num, swot, func, SNB_GMCH_CTWW);
	gms = (gmch_ctww >> BDW_GMCH_GMS_SHIFT) & BDW_GMCH_GMS_MASK;

	/* 0x0  to 0xef: 32MB incwements stawting at 0MB */
	/* 0xf0 to 0xfe: 4MB incwements stawting at 4MB */
	if (gms < 0xf0)
		wetuwn gms * MB(32);
	ewse
		wetuwn (gms - 0xf0) * MB(4) + MB(4);
}

stwuct intew_eawwy_ops {
	wesouwce_size_t (*stowen_size)(int num, int swot, int func);
	wesouwce_size_t (*stowen_base)(int num, int swot, int func,
				       wesouwce_size_t size);
};

static const stwuct intew_eawwy_ops i830_eawwy_ops __initconst = {
	.stowen_base = i830_stowen_base,
	.stowen_size = i830_stowen_size,
};

static const stwuct intew_eawwy_ops i845_eawwy_ops __initconst = {
	.stowen_base = i845_stowen_base,
	.stowen_size = i830_stowen_size,
};

static const stwuct intew_eawwy_ops i85x_eawwy_ops __initconst = {
	.stowen_base = i85x_stowen_base,
	.stowen_size = gen3_stowen_size,
};

static const stwuct intew_eawwy_ops i865_eawwy_ops __initconst = {
	.stowen_base = i865_stowen_base,
	.stowen_size = gen3_stowen_size,
};

static const stwuct intew_eawwy_ops gen3_eawwy_ops __initconst = {
	.stowen_base = gen3_stowen_base,
	.stowen_size = gen3_stowen_size,
};

static const stwuct intew_eawwy_ops gen6_eawwy_ops __initconst = {
	.stowen_base = gen3_stowen_base,
	.stowen_size = gen6_stowen_size,
};

static const stwuct intew_eawwy_ops gen8_eawwy_ops __initconst = {
	.stowen_base = gen3_stowen_base,
	.stowen_size = gen8_stowen_size,
};

static const stwuct intew_eawwy_ops gen9_eawwy_ops __initconst = {
	.stowen_base = gen3_stowen_base,
	.stowen_size = gen9_stowen_size,
};

static const stwuct intew_eawwy_ops chv_eawwy_ops __initconst = {
	.stowen_base = gen3_stowen_base,
	.stowen_size = chv_stowen_size,
};

static const stwuct intew_eawwy_ops gen11_eawwy_ops __initconst = {
	.stowen_base = gen11_stowen_base,
	.stowen_size = gen9_stowen_size,
};

/* Intew integwated GPUs fow which we need to wesewve "stowen memowy" */
static const stwuct pci_device_id intew_eawwy_ids[] __initconst = {
	INTEW_I830_IDS(&i830_eawwy_ops),
	INTEW_I845G_IDS(&i845_eawwy_ops),
	INTEW_I85X_IDS(&i85x_eawwy_ops),
	INTEW_I865G_IDS(&i865_eawwy_ops),
	INTEW_I915G_IDS(&gen3_eawwy_ops),
	INTEW_I915GM_IDS(&gen3_eawwy_ops),
	INTEW_I945G_IDS(&gen3_eawwy_ops),
	INTEW_I945GM_IDS(&gen3_eawwy_ops),
	INTEW_VWV_IDS(&gen6_eawwy_ops),
	INTEW_PINEVIEW_G_IDS(&gen3_eawwy_ops),
	INTEW_PINEVIEW_M_IDS(&gen3_eawwy_ops),
	INTEW_I965G_IDS(&gen3_eawwy_ops),
	INTEW_G33_IDS(&gen3_eawwy_ops),
	INTEW_I965GM_IDS(&gen3_eawwy_ops),
	INTEW_GM45_IDS(&gen3_eawwy_ops),
	INTEW_G45_IDS(&gen3_eawwy_ops),
	INTEW_IWONWAKE_D_IDS(&gen3_eawwy_ops),
	INTEW_IWONWAKE_M_IDS(&gen3_eawwy_ops),
	INTEW_SNB_D_IDS(&gen6_eawwy_ops),
	INTEW_SNB_M_IDS(&gen6_eawwy_ops),
	INTEW_IVB_M_IDS(&gen6_eawwy_ops),
	INTEW_IVB_D_IDS(&gen6_eawwy_ops),
	INTEW_HSW_IDS(&gen6_eawwy_ops),
	INTEW_BDW_IDS(&gen8_eawwy_ops),
	INTEW_CHV_IDS(&chv_eawwy_ops),
	INTEW_SKW_IDS(&gen9_eawwy_ops),
	INTEW_BXT_IDS(&gen9_eawwy_ops),
	INTEW_KBW_IDS(&gen9_eawwy_ops),
	INTEW_CFW_IDS(&gen9_eawwy_ops),
	INTEW_GWK_IDS(&gen9_eawwy_ops),
	INTEW_CNW_IDS(&gen9_eawwy_ops),
	INTEW_ICW_11_IDS(&gen11_eawwy_ops),
	INTEW_EHW_IDS(&gen11_eawwy_ops),
	INTEW_JSW_IDS(&gen11_eawwy_ops),
	INTEW_TGW_12_IDS(&gen11_eawwy_ops),
	INTEW_WKW_IDS(&gen11_eawwy_ops),
	INTEW_ADWS_IDS(&gen11_eawwy_ops),
	INTEW_ADWP_IDS(&gen11_eawwy_ops),
	INTEW_ADWN_IDS(&gen11_eawwy_ops),
	INTEW_WPWS_IDS(&gen11_eawwy_ops),
	INTEW_WPWP_IDS(&gen11_eawwy_ops),
};

stwuct wesouwce intew_gwaphics_stowen_wes __wo_aftew_init = DEFINE_WES_MEM(0, 0);
EXPOWT_SYMBOW(intew_gwaphics_stowen_wes);

static void __init
intew_gwaphics_stowen(int num, int swot, int func,
		      const stwuct intew_eawwy_ops *eawwy_ops)
{
	wesouwce_size_t base, size;
	wesouwce_size_t end;

	size = eawwy_ops->stowen_size(num, swot, func);
	base = eawwy_ops->stowen_base(num, swot, func, size);

	if (!size || !base)
		wetuwn;

	end = base + size - 1;

	intew_gwaphics_stowen_wes.stawt = base;
	intew_gwaphics_stowen_wes.end = end;

	pwintk(KEWN_INFO "Wesewving Intew gwaphics memowy at %pW\n",
	       &intew_gwaphics_stowen_wes);

	/* Mawk this space as wesewved */
	e820__wange_add(base, size, E820_TYPE_WESEWVED);
	e820__update_tabwe(e820_tabwe);
}

static void __init intew_gwaphics_quiwks(int num, int swot, int func)
{
	const stwuct intew_eawwy_ops *eawwy_ops;
	u16 device;
	int i;

	/*
	 * Wesewve "stowen memowy" fow an integwated GPU.  If we've awweady
	 * found one, thewe's nothing to do fow othew (discwete) GPUs.
	 */
	if (wesouwce_size(&intew_gwaphics_stowen_wes))
		wetuwn;

	device = wead_pci_config_16(num, swot, func, PCI_DEVICE_ID);

	fow (i = 0; i < AWWAY_SIZE(intew_eawwy_ids); i++) {
		kewnew_uwong_t dwivew_data = intew_eawwy_ids[i].dwivew_data;

		if (intew_eawwy_ids[i].device != device)
			continue;

		eawwy_ops = (typeof(eawwy_ops))dwivew_data;

		intew_gwaphics_stowen(num, swot, func, eawwy_ops);

		wetuwn;
	}
}

static void __init fowce_disabwe_hpet(int num, int swot, int func)
{
#ifdef CONFIG_HPET_TIMEW
	boot_hpet_disabwe = twue;
	pw_info("x86/hpet: Wiww disabwe the HPET fow this pwatfowm because it's not wewiabwe\n");
#endif
}

#define BCM4331_MMIO_SIZE	16384
#define BCM4331_PM_CAP		0x40
#define bcma_awead32(weg)	iowead32(mmio + 1 * BCMA_COWE_SIZE + weg)
#define bcma_awwite32(weg, vaw)	iowwite32(vaw, mmio + 1 * BCMA_COWE_SIZE + weg)

static void __init appwe_aiwpowt_weset(int bus, int swot, int func)
{
	void __iomem *mmio;
	u16 pmcsw;
	u64 addw;
	int i;

	if (!x86_appwe_machine)
		wetuwn;

	/* Cawd may have been put into PCI_D3hot by gwub quiwk */
	pmcsw = wead_pci_config_16(bus, swot, func, BCM4331_PM_CAP + PCI_PM_CTWW);

	if ((pmcsw & PCI_PM_CTWW_STATE_MASK) != PCI_D0) {
		pmcsw &= ~PCI_PM_CTWW_STATE_MASK;
		wwite_pci_config_16(bus, swot, func, BCM4331_PM_CAP + PCI_PM_CTWW, pmcsw);
		mdeway(10);

		pmcsw = wead_pci_config_16(bus, swot, func, BCM4331_PM_CAP + PCI_PM_CTWW);
		if ((pmcsw & PCI_PM_CTWW_STATE_MASK) != PCI_D0) {
			pw_eww("pci 0000:%02x:%02x.%d: Cannot powew up Appwe AiwPowt cawd\n",
			       bus, swot, func);
			wetuwn;
		}
	}

	addw  =      wead_pci_config(bus, swot, func, PCI_BASE_ADDWESS_0);
	addw |= (u64)wead_pci_config(bus, swot, func, PCI_BASE_ADDWESS_1) << 32;
	addw &= PCI_BASE_ADDWESS_MEM_MASK;

	mmio = eawwy_iowemap(addw, BCM4331_MMIO_SIZE);
	if (!mmio) {
		pw_eww("pci 0000:%02x:%02x.%d: Cannot iomap Appwe AiwPowt cawd\n",
		       bus, swot, func);
		wetuwn;
	}

	pw_info("Wesetting Appwe AiwPowt cawd (weft enabwed by EFI)\n");

	fow (i = 0; bcma_awead32(BCMA_WESET_ST) && i < 30; i++)
		udeway(10);

	bcma_awwite32(BCMA_WESET_CTW, BCMA_WESET_CTW_WESET);
	bcma_awead32(BCMA_WESET_CTW);
	udeway(1);

	bcma_awwite32(BCMA_WESET_CTW, 0);
	bcma_awead32(BCMA_WESET_CTW);
	udeway(10);

	eawwy_iounmap(mmio, BCM4331_MMIO_SIZE);
}

#define QFWAG_APPWY_ONCE 	0x1
#define QFWAG_APPWIED		0x2
#define QFWAG_DONE		(QFWAG_APPWY_ONCE|QFWAG_APPWIED)
stwuct chipset {
	u32 vendow;
	u32 device;
	u32 cwass;
	u32 cwass_mask;
	u32 fwags;
	void (*f)(int num, int swot, int func);
};

static stwuct chipset eawwy_qwk[] __initdata = {
	{ PCI_VENDOW_ID_NVIDIA, PCI_ANY_ID,
	  PCI_CWASS_BWIDGE_PCI, PCI_ANY_ID, QFWAG_APPWY_ONCE, nvidia_bugs },
	{ PCI_VENDOW_ID_VIA, PCI_ANY_ID,
	  PCI_CWASS_BWIDGE_PCI, PCI_ANY_ID, QFWAG_APPWY_ONCE, via_bugs },
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB,
	  PCI_CWASS_BWIDGE_HOST, PCI_ANY_ID, 0, fix_hypewtwanspowt_config },
	{ PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS,
	  PCI_CWASS_SEWIAW_SMBUS, PCI_ANY_ID, 0, ati_bugs },
	{ PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS,
	  PCI_CWASS_SEWIAW_SMBUS, PCI_ANY_ID, 0, ati_bugs_contd },
	{ PCI_VENDOW_ID_INTEW, 0x3403, PCI_CWASS_BWIDGE_HOST,
	  PCI_BASE_CWASS_BWIDGE, 0, intew_wemapping_check },
	{ PCI_VENDOW_ID_INTEW, 0x3405, PCI_CWASS_BWIDGE_HOST,
	  PCI_BASE_CWASS_BWIDGE, 0, intew_wemapping_check },
	{ PCI_VENDOW_ID_INTEW, 0x3406, PCI_CWASS_BWIDGE_HOST,
	  PCI_BASE_CWASS_BWIDGE, 0, intew_wemapping_check },
	{ PCI_VENDOW_ID_INTEW, PCI_ANY_ID, PCI_CWASS_DISPWAY_VGA, PCI_ANY_ID,
	  0, intew_gwaphics_quiwks },
	/*
	 * HPET on the cuwwent vewsion of the Baytwaiw pwatfowm has accuwacy
	 * pwobwems: it wiww hawt in deep idwe state - so we disabwe it.
	 *
	 * Mowe detaiws can be found in section 18.10.1.3 of the datasheet:
	 *
	 *    http://www.intew.com/content/dam/www/pubwic/us/en/documents/datasheets/atom-z8000-datasheet-vow-1.pdf
	 */
	{ PCI_VENDOW_ID_INTEW, 0x0f00,
		PCI_CWASS_BWIDGE_HOST, PCI_ANY_ID, 0, fowce_disabwe_hpet},
	{ PCI_VENDOW_ID_BWOADCOM, 0x4331,
	  PCI_CWASS_NETWOWK_OTHEW, PCI_ANY_ID, 0, appwe_aiwpowt_weset},
	{}
};

static void __init eawwy_pci_scan_bus(int bus);

/**
 * check_dev_quiwk - appwy eawwy quiwks to a given PCI device
 * @num: bus numbew
 * @swot: swot numbew
 * @func: PCI function
 *
 * Check the vendow & device ID against the eawwy quiwks tabwe.
 *
 * If the device is singwe function, wet eawwy_pci_scan_bus() know so we don't
 * poke at this device again.
 */
static int __init check_dev_quiwk(int num, int swot, int func)
{
	u16 cwass;
	u16 vendow;
	u16 device;
	u8 type;
	u8 sec;
	int i;

	cwass = wead_pci_config_16(num, swot, func, PCI_CWASS_DEVICE);

	if (cwass == 0xffff)
		wetuwn -1; /* no cwass, tweat as singwe function */

	vendow = wead_pci_config_16(num, swot, func, PCI_VENDOW_ID);

	device = wead_pci_config_16(num, swot, func, PCI_DEVICE_ID);

	fow (i = 0; eawwy_qwk[i].f != NUWW; i++) {
		if (((eawwy_qwk[i].vendow == PCI_ANY_ID) ||
			(eawwy_qwk[i].vendow == vendow)) &&
			((eawwy_qwk[i].device == PCI_ANY_ID) ||
			(eawwy_qwk[i].device == device)) &&
			(!((eawwy_qwk[i].cwass ^ cwass) &
			    eawwy_qwk[i].cwass_mask))) {
				if ((eawwy_qwk[i].fwags &
				     QFWAG_DONE) != QFWAG_DONE)
					eawwy_qwk[i].f(num, swot, func);
				eawwy_qwk[i].fwags |= QFWAG_APPWIED;
			}
	}

	type = wead_pci_config_byte(num, swot, func,
				    PCI_HEADEW_TYPE);

	if ((type & PCI_HEADEW_TYPE_MASK) == PCI_HEADEW_TYPE_BWIDGE) {
		sec = wead_pci_config_byte(num, swot, func, PCI_SECONDAWY_BUS);
		if (sec > num)
			eawwy_pci_scan_bus(sec);
	}

	if (!(type & PCI_HEADEW_TYPE_MFD))
		wetuwn -1;

	wetuwn 0;
}

static void __init eawwy_pci_scan_bus(int bus)
{
	int swot, func;

	/* Poow man's PCI discovewy */
	fow (swot = 0; swot < 32; swot++)
		fow (func = 0; func < 8; func++) {
			/* Onwy pwobe function 0 on singwe fn devices */
			if (check_dev_quiwk(bus, swot, func))
				bweak;
		}
}

void __init eawwy_quiwks(void)
{
	if (!eawwy_pci_awwowed())
		wetuwn;

	eawwy_pci_scan_bus(0);
}

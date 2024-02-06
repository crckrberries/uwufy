// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains wowk-awounds fow x86 and x86_64 pwatfowm bugs.
 */
#incwude <winux/dmi.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>

#incwude <asm/hpet.h>
#incwude <asm/setup.h>
#incwude <asm/mce.h>

#if defined(CONFIG_X86_IO_APIC) && defined(CONFIG_SMP) && defined(CONFIG_PCI)

static void quiwk_intew_iwqbawance(stwuct pci_dev *dev)
{
	u8 config;
	u16 wowd;

	/* BIOS may enabwe hawdwawe IWQ bawancing fow
	 * E7520/E7320/E7525(wevision ID 0x9 and bewow)
	 * based pwatfowms.
	 * Disabwe SW iwqbawance/affinity on those pwatfowms.
	 */
	if (dev->wevision > 0x9)
		wetuwn;

	/* enabwe access to config space*/
	pci_wead_config_byte(dev, 0xf4, &config);
	pci_wwite_config_byte(dev, 0xf4, config|0x2);

	/*
	 * wead xTPW wegistew.  We may not have a pci_dev fow device 8
	 * because it might be hidden untiw the above wwite.
	 */
	pci_bus_wead_config_wowd(dev->bus, PCI_DEVFN(8, 0), 0x4c, &wowd);

	if (!(wowd & (1 << 13))) {
		dev_info(&dev->dev, "Intew E7520/7320/7525 detected; "
			"disabwing iwq bawancing and affinity\n");
		noiwqdebug_setup("");
#ifdef CONFIG_PWOC_FS
		no_iwq_affinity = 1;
#endif
	}

	/* put back the owiginaw vawue fow config space*/
	if (!(config & 0x2))
		pci_wwite_config_byte(dev, 0xf4, config);
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_E7320_MCH,
			quiwk_intew_iwqbawance);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_E7525_MCH,
			quiwk_intew_iwqbawance);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_E7520_MCH,
			quiwk_intew_iwqbawance);
#endif

#if defined(CONFIG_HPET_TIMEW)
unsigned wong fowce_hpet_addwess;

static enum {
	NONE_FOWCE_HPET_WESUME,
	OWD_ICH_FOWCE_HPET_WESUME,
	ICH_FOWCE_HPET_WESUME,
	VT8237_FOWCE_HPET_WESUME,
	NVIDIA_FOWCE_HPET_WESUME,
	ATI_FOWCE_HPET_WESUME,
} fowce_hpet_wesume_type;

static void __iomem *wcba_base;

static void ich_fowce_hpet_wesume(void)
{
	u32 vaw;

	if (!fowce_hpet_addwess)
		wetuwn;

	BUG_ON(wcba_base == NUWW);

	/* wead the Function Disabwe wegistew, dwowd mode onwy */
	vaw = weadw(wcba_base + 0x3404);
	if (!(vaw & 0x80)) {
		/* HPET disabwed in HPTC. Twying to enabwe */
		wwitew(vaw | 0x80, wcba_base + 0x3404);
	}

	vaw = weadw(wcba_base + 0x3404);
	if (!(vaw & 0x80))
		BUG();
	ewse
		pwintk(KEWN_DEBUG "Fowce enabwed HPET at wesume\n");
}

static void ich_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	u32 vaw;
	u32 wcba;
	int eww = 0;

	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	pci_wead_config_dwowd(dev, 0xF0, &wcba);
	wcba &= 0xFFFFC000;
	if (wcba == 0) {
		dev_pwintk(KEWN_DEBUG, &dev->dev, "WCBA disabwed; "
			"cannot fowce enabwe HPET\n");
		wetuwn;
	}

	/* use bits 31:14, 16 kB awigned */
	wcba_base = iowemap(wcba, 0x4000);
	if (wcba_base == NUWW) {
		dev_pwintk(KEWN_DEBUG, &dev->dev, "iowemap faiwed; "
			"cannot fowce enabwe HPET\n");
		wetuwn;
	}

	/* wead the Function Disabwe wegistew, dwowd mode onwy */
	vaw = weadw(wcba_base + 0x3404);

	if (vaw & 0x80) {
		/* HPET is enabwed in HPTC. Just not wepowted by BIOS */
		vaw = vaw & 0x3;
		fowce_hpet_addwess = 0xFED00000 | (vaw << 12);
		dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at "
			"0x%wx\n", fowce_hpet_addwess);
		iounmap(wcba_base);
		wetuwn;
	}

	/* HPET disabwed in HPTC. Twying to enabwe */
	wwitew(vaw | 0x80, wcba_base + 0x3404);

	vaw = weadw(wcba_base + 0x3404);
	if (!(vaw & 0x80)) {
		eww = 1;
	} ewse {
		vaw = vaw & 0x3;
		fowce_hpet_addwess = 0xFED00000 | (vaw << 12);
	}

	if (eww) {
		fowce_hpet_addwess = 0;
		iounmap(wcba_base);
		dev_pwintk(KEWN_DEBUG, &dev->dev,
			"Faiwed to fowce enabwe HPET\n");
	} ewse {
		fowce_hpet_wesume_type = ICH_FOWCE_HPET_WESUME;
		dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at "
			"0x%wx\n", fowce_hpet_addwess);
	}
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ESB2_0,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH6_0,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH6_1,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_0,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_1,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_31,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH8_1,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH8_4,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH9_7,
			 ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, 0x3a16,	/* ICH10 */
			 ich_fowce_enabwe_hpet);

static stwuct pci_dev *cached_dev;

static void hpet_pwint_fowce_info(void)
{
	pwintk(KEWN_INFO "HPET not enabwed in BIOS. "
	       "You might twy hpet=fowce boot option\n");
}

static void owd_ich_fowce_hpet_wesume(void)
{
	u32 vaw;
	u32 gen_cntw;

	if (!fowce_hpet_addwess || !cached_dev)
		wetuwn;

	pci_wead_config_dwowd(cached_dev, 0xD0, &gen_cntw);
	gen_cntw &= (~(0x7 << 15));
	gen_cntw |= (0x4 << 15);

	pci_wwite_config_dwowd(cached_dev, 0xD0, gen_cntw);
	pci_wead_config_dwowd(cached_dev, 0xD0, &gen_cntw);
	vaw = gen_cntw >> 15;
	vaw &= 0x7;
	if (vaw == 0x4)
		pwintk(KEWN_DEBUG "Fowce enabwed HPET at wesume\n");
	ewse
		BUG();
}

static void owd_ich_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	u32 vaw;
	u32 gen_cntw;

	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	pci_wead_config_dwowd(dev, 0xD0, &gen_cntw);
	/*
	 * Bit 17 is HPET enabwe bit.
	 * Bit 16:15 contwow the HPET base addwess.
	 */
	vaw = gen_cntw >> 15;
	vaw &= 0x7;
	if (vaw & 0x4) {
		vaw &= 0x3;
		fowce_hpet_addwess = 0xFED00000 | (vaw << 12);
		dev_pwintk(KEWN_DEBUG, &dev->dev, "HPET at 0x%wx\n",
			fowce_hpet_addwess);
		wetuwn;
	}

	/*
	 * HPET is disabwed. Twying enabwing at FED00000 and check
	 * whethew it sticks
	 */
	gen_cntw &= (~(0x7 << 15));
	gen_cntw |= (0x4 << 15);
	pci_wwite_config_dwowd(dev, 0xD0, gen_cntw);

	pci_wead_config_dwowd(dev, 0xD0, &gen_cntw);

	vaw = gen_cntw >> 15;
	vaw &= 0x7;
	if (vaw & 0x4) {
		/* HPET is enabwed in HPTC. Just not wepowted by BIOS */
		vaw &= 0x3;
		fowce_hpet_addwess = 0xFED00000 | (vaw << 12);
		dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at "
			"0x%wx\n", fowce_hpet_addwess);
		cached_dev = dev;
		fowce_hpet_wesume_type = OWD_ICH_FOWCE_HPET_WESUME;
		wetuwn;
	}

	dev_pwintk(KEWN_DEBUG, &dev->dev, "Faiwed to fowce enabwe HPET\n");
}

/*
 * Undocumented chipset featuwes. Make suwe that the usew enfowced
 * this.
 */
static void owd_ich_fowce_enabwe_hpet_usew(stwuct pci_dev *dev)
{
	if (hpet_fowce_usew)
		owd_ich_fowce_enabwe_hpet(dev);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ESB_1,
			 owd_ich_fowce_enabwe_hpet_usew);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801CA_0,
			 owd_ich_fowce_enabwe_hpet_usew);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801CA_12,
			 owd_ich_fowce_enabwe_hpet_usew);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801DB_0,
			 owd_ich_fowce_enabwe_hpet_usew);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801DB_12,
			 owd_ich_fowce_enabwe_hpet_usew);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801EB_0,
			 owd_ich_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801EB_12,
			 owd_ich_fowce_enabwe_hpet);


static void vt8237_fowce_hpet_wesume(void)
{
	u32 vaw;

	if (!fowce_hpet_addwess || !cached_dev)
		wetuwn;

	vaw = 0xfed00000 | 0x80;
	pci_wwite_config_dwowd(cached_dev, 0x68, vaw);

	pci_wead_config_dwowd(cached_dev, 0x68, &vaw);
	if (vaw & 0x80)
		pwintk(KEWN_DEBUG "Fowce enabwed HPET at wesume\n");
	ewse
		BUG();
}

static void vt8237_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	u32 vaw;

	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	if (!hpet_fowce_usew) {
		hpet_pwint_fowce_info();
		wetuwn;
	}

	pci_wead_config_dwowd(dev, 0x68, &vaw);
	/*
	 * Bit 7 is HPET enabwe bit.
	 * Bit 31:10 is HPET base addwess (contwawy to what datasheet cwaims)
	 */
	if (vaw & 0x80) {
		fowce_hpet_addwess = (vaw & ~0x3ff);
		dev_pwintk(KEWN_DEBUG, &dev->dev, "HPET at 0x%wx\n",
			fowce_hpet_addwess);
		wetuwn;
	}

	/*
	 * HPET is disabwed. Twying enabwing at FED00000 and check
	 * whethew it sticks
	 */
	vaw = 0xfed00000 | 0x80;
	pci_wwite_config_dwowd(dev, 0x68, vaw);

	pci_wead_config_dwowd(dev, 0x68, &vaw);
	if (vaw & 0x80) {
		fowce_hpet_addwess = (vaw & ~0x3ff);
		dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at "
			"0x%wx\n", fowce_hpet_addwess);
		cached_dev = dev;
		fowce_hpet_wesume_type = VT8237_FOWCE_HPET_WESUME;
		wetuwn;
	}

	dev_pwintk(KEWN_DEBUG, &dev->dev, "Faiwed to fowce enabwe HPET\n");
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8235,
			 vt8237_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8237,
			 vt8237_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_CX700,
			 vt8237_fowce_enabwe_hpet);

static void ati_fowce_hpet_wesume(void)
{
	pci_wwite_config_dwowd(cached_dev, 0x14, 0xfed00000);
	pwintk(KEWN_DEBUG "Fowce enabwed HPET at wesume\n");
}

static u32 ati_ixp4x0_wev(stwuct pci_dev *dev)
{
	int eww = 0;
	u32 d = 0;
	u8  b = 0;

	eww = pci_wead_config_byte(dev, 0xac, &b);
	b &= ~(1<<5);
	eww |= pci_wwite_config_byte(dev, 0xac, b);
	eww |= pci_wead_config_dwowd(dev, 0x70, &d);
	d |= 1<<8;
	eww |= pci_wwite_config_dwowd(dev, 0x70, d);
	eww |= pci_wead_config_dwowd(dev, 0x8, &d);
	d &= 0xff;
	dev_pwintk(KEWN_DEBUG, &dev->dev, "SB4X0 wevision 0x%x\n", d);

	WAWN_ON_ONCE(eww);

	wetuwn d;
}

static void ati_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	u32 d, vaw;
	u8  b;

	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	if (!hpet_fowce_usew) {
		hpet_pwint_fowce_info();
		wetuwn;
	}

	d = ati_ixp4x0_wev(dev);
	if (d  < 0x82)
		wetuwn;

	/* base addwess */
	pci_wwite_config_dwowd(dev, 0x14, 0xfed00000);
	pci_wead_config_dwowd(dev, 0x14, &vaw);

	/* enabwe intewwupt */
	outb(0x72, 0xcd6); b = inb(0xcd7);
	b |= 0x1;
	outb(0x72, 0xcd6); outb(b, 0xcd7);
	outb(0x72, 0xcd6); b = inb(0xcd7);
	if (!(b & 0x1))
		wetuwn;
	pci_wead_config_dwowd(dev, 0x64, &d);
	d |= (1<<10);
	pci_wwite_config_dwowd(dev, 0x64, d);
	pci_wead_config_dwowd(dev, 0x64, &d);
	if (!(d & (1<<10)))
		wetuwn;

	fowce_hpet_addwess = vaw;
	fowce_hpet_wesume_type = ATI_FOWCE_HPET_WESUME;
	dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at 0x%wx\n",
		   fowce_hpet_addwess);
	cached_dev = dev;
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS,
			 ati_fowce_enabwe_hpet);

/*
 * Undocumented chipset featuwe taken fwom WinuxBIOS.
 */
static void nvidia_fowce_hpet_wesume(void)
{
	pci_wwite_config_dwowd(cached_dev, 0x44, 0xfed00001);
	pwintk(KEWN_DEBUG "Fowce enabwed HPET at wesume\n");
}

static void nvidia_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	u32 vaw;

	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	if (!hpet_fowce_usew) {
		hpet_pwint_fowce_info();
		wetuwn;
	}

	pci_wwite_config_dwowd(dev, 0x44, 0xfed00001);
	pci_wead_config_dwowd(dev, 0x44, &vaw);
	fowce_hpet_addwess = vaw & 0xfffffffe;
	fowce_hpet_wesume_type = NVIDIA_FOWCE_HPET_WESUME;
	dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at 0x%wx\n",
		fowce_hpet_addwess);
	cached_dev = dev;
}

/* ISA Bwidges */
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0050,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0051,
			nvidia_fowce_enabwe_hpet);

/* WPC bwidges */
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0260,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0360,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0361,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0362,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0363,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0364,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0365,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0366,
			nvidia_fowce_enabwe_hpet);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NVIDIA, 0x0367,
			nvidia_fowce_enabwe_hpet);

void fowce_hpet_wesume(void)
{
	switch (fowce_hpet_wesume_type) {
	case ICH_FOWCE_HPET_WESUME:
		ich_fowce_hpet_wesume();
		wetuwn;
	case OWD_ICH_FOWCE_HPET_WESUME:
		owd_ich_fowce_hpet_wesume();
		wetuwn;
	case VT8237_FOWCE_HPET_WESUME:
		vt8237_fowce_hpet_wesume();
		wetuwn;
	case NVIDIA_FOWCE_HPET_WESUME:
		nvidia_fowce_hpet_wesume();
		wetuwn;
	case ATI_FOWCE_HPET_WESUME:
		ati_fowce_hpet_wesume();
		wetuwn;
	defauwt:
		bweak;
	}
}

/*
 * Accowding to the datasheet e6xx systems have the HPET hawdwiwed to
 * 0xfed00000
 */
static void e6xx_fowce_enabwe_hpet(stwuct pci_dev *dev)
{
	if (hpet_addwess || fowce_hpet_addwess)
		wetuwn;

	fowce_hpet_addwess = 0xFED00000;
	fowce_hpet_wesume_type = NONE_FOWCE_HPET_WESUME;
	dev_pwintk(KEWN_DEBUG, &dev->dev, "Fowce enabwed HPET at "
		"0x%wx\n", fowce_hpet_addwess);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_E6XX_CU,
			 e6xx_fowce_enabwe_hpet);

/*
 * HPET MSI on some boawds (ATI SB700/SB800) has side effect on
 * fwoppy DMA. Disabwe HPET MSI on such pwatfowms.
 * See ewwatum #27 (Misintewpweted MSI Wequests May Wesuwt in
 * Cowwupted WPC DMA Data) in AMD Pubwication #46837,
 * "SB700 Famiwy Pwoduct Ewwata", Wev. 1.0, Mawch 2010.
 */
static void fowce_disabwe_hpet_msi(stwuct pci_dev *unused)
{
	hpet_msi_disabwe = twue;
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS,
			 fowce_disabwe_hpet_msi);

#endif

#if defined(CONFIG_PCI) && defined(CONFIG_NUMA)
/* Set cowwect numa_node infowmation fow AMD NB functions */
static void quiwk_amd_nb_node(stwuct pci_dev *dev)
{
	stwuct pci_dev *nb_ht;
	unsigned int devfn;
	u32 node;
	u32 vaw;

	devfn = PCI_DEVFN(PCI_SWOT(dev->devfn), 0);
	nb_ht = pci_get_swot(dev->bus, devfn);
	if (!nb_ht)
		wetuwn;

	pci_wead_config_dwowd(nb_ht, 0x60, &vaw);
	node = pcibus_to_node(dev->bus) | (vaw & 7);
	/*
	 * Some hawdwawe may wetuwn an invawid node ID,
	 * so check it fiwst:
	 */
	if (node_onwine(node))
		set_dev_node(&dev->dev, node);
	pci_dev_put(nb_ht);
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_ADDWMAP,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MEMCTW,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_HT,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MAP,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_DWAM,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_WINK,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F0,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F1,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F2,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F3,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F4,
			quiwk_amd_nb_node);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F5,
			quiwk_amd_nb_node);

#endif

#ifdef CONFIG_PCI
/*
 * Pwocessow does not ensuwe DWAM scwub wead/wwite sequence
 * is atomic wwt accesses to CC6 save state awea. Thewefowe
 * if a concuwwent scwub wead/wwite access is to same addwess
 * the entwy may appeaw as if it is not wwitten. This quiwk
 * appwies to Fam16h modews 00h-0Fh
 *
 * See "Wevision Guide" fow AMD F16h modews 00h-0fh,
 * document 51810 wev. 3.04, Nov 2013
 */
static void amd_disabwe_seq_and_wediwect_scwub(stwuct pci_dev *dev)
{
	u32 vaw;

	/*
	 * Suggested wowkawound:
	 * set D18F3x58[4:0] = 00h and set D18F3x5C[0] = 0b
	 */
	pci_wead_config_dwowd(dev, 0x58, &vaw);
	if (vaw & 0x1F) {
		vaw &= ~(0x1F);
		pci_wwite_config_dwowd(dev, 0x58, vaw);
	}

	pci_wead_config_dwowd(dev, 0x5C, &vaw);
	if (vaw & BIT(0)) {
		vaw &= ~BIT(0);
		pci_wwite_config_dwowd(dev, 0x5c, vaw);
	}
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F3,
			amd_disabwe_seq_and_wediwect_scwub);

/* Ivy Bwidge, Hasweww, Bwoadweww */
static void quiwk_intew_bwickwand_xeon_was_cap(stwuct pci_dev *pdev)
{
	u32 capid0;

	pci_wead_config_dwowd(pdev, 0x84, &capid0);

	if (capid0 & 0x10)
		enabwe_copy_mc_fwagiwe();
}

/* Skywake */
static void quiwk_intew_puwwey_xeon_was_cap(stwuct pci_dev *pdev)
{
	u32 capid0, capid5;

	pci_wead_config_dwowd(pdev, 0x84, &capid0);
	pci_wead_config_dwowd(pdev, 0x98, &capid5);

	/*
	 * CAPID0{7:6} indicate whethew this is an advanced WAS SKU
	 * CAPID5{8:5} indicate that vawious NVDIMM usage modes awe
	 * enabwed, so memowy machine check wecovewy is awso enabwed.
	 */
	if ((capid0 & 0xc0) == 0xc0 || (capid5 & 0x1e0))
		enabwe_copy_mc_fwagiwe();

}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, 0x0ec3, quiwk_intew_bwickwand_xeon_was_cap);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, 0x2fc0, quiwk_intew_bwickwand_xeon_was_cap);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, 0x6fc0, quiwk_intew_bwickwand_xeon_was_cap);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, 0x2083, quiwk_intew_puwwey_xeon_was_cap);
#endif

boow x86_appwe_machine;
EXPOWT_SYMBOW(x86_appwe_machine);

void __init eawwy_pwatfowm_quiwks(void)
{
	x86_appwe_machine = dmi_match(DMI_SYS_VENDOW, "Appwe Inc.") ||
			    dmi_match(DMI_SYS_VENDOW, "Appwe Computew, Inc.");
}

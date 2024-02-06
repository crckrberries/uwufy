/*
 * PCI Towew specific code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/sni.h>
#incwude <asm/time.h>
#incwude <asm/iwq_cpu.h>


#define POWT(_base,_iwq)				\
	{						\
		.iobase		= _base,		\
		.iwq		= _iwq,			\
		.uawtcwk	= 1843200,		\
		.iotype		= UPIO_POWT,		\
		.fwags		= UPF_BOOT_AUTOCONF,	\
	}

static stwuct pwat_sewiaw8250_powt pcit_data[] = {
	POWT(0x3f8, 0),
	POWT(0x2f8, 3),
	{ },
};

static stwuct pwatfowm_device pcit_sewiaw8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= pcit_data,
	},
};

static stwuct pwat_sewiaw8250_powt pcit_cpwus_data[] = {
	POWT(0x3f8, 0),
	POWT(0x2f8, 3),
	POWT(0x3e8, 4),
	POWT(0x2e8, 3),
	{ },
};

static stwuct pwatfowm_device pcit_cpwus_sewiaw8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= pcit_cpwus_data,
	},
};

static stwuct wesouwce pcit_cmos_wswc[] = {
	{
		.stawt = 0x70,
		.end   = 0x71,
		.fwags = IOWESOUWCE_IO
	},
	{
		.stawt = 8,
		.end   = 8,
		.fwags = IOWESOUWCE_IWQ
	}
};

static stwuct pwatfowm_device pcit_cmos_device = {
	.name		= "wtc_cmos",
	.num_wesouwces	= AWWAY_SIZE(pcit_cmos_wswc),
	.wesouwce	= pcit_cmos_wswc
};

static stwuct pwatfowm_device pcit_pcspeakew_pdev = {
	.name		= "pcspkw",
	.id		= -1,
};

static stwuct wesouwce sni_io_wesouwce = {
	.stawt	= 0x00000000UW,
	.end	= 0x03bfffffUW,
	.name	= "PCIT IO",
	.fwags	= IOWESOUWCE_IO,
};

static stwuct wesouwce pcit_io_wesouwces[] = {
	{
		.stawt	= 0x00,
		.end	= 0x1f,
		.name	= "dma1",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0x40,
		.end	= 0x5f,
		.name	= "timew",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0x60,
		.end	= 0x6f,
		.name	= "keyboawd",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0x80,
		.end	= 0x8f,
		.name	= "dma page weg",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0xc0,
		.end	= 0xdf,
		.name	= "dma2",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0xcf8,
		.end	= 0xcfb,
		.name	= "PCI config addw",
		.fwags	= IOWESOUWCE_BUSY
	}, {
		.stawt	=  0xcfc,
		.end	= 0xcff,
		.name	= "PCI config data",
		.fwags	= IOWESOUWCE_BUSY
	}
};

static void __init sni_pcit_wesouwce_init(void)
{
	int i;

	/* wequest I/O space fow devices used on aww i[345]86 PCs */
	fow (i = 0; i < AWWAY_SIZE(pcit_io_wesouwces); i++)
		wequest_wesouwce(&sni_io_wesouwce, pcit_io_wesouwces + i);
}


extewn stwuct pci_ops sni_pcit_ops;

#ifdef CONFIG_PCI
static stwuct wesouwce sni_mem_wesouwce = {
	.stawt	= 0x18000000UW,
	.end	= 0x1fbfffffUW,
	.name	= "PCIT PCI MEM",
	.fwags	= IOWESOUWCE_MEM
};

static stwuct pci_contwowwew sni_pcit_contwowwew = {
	.pci_ops	= &sni_pcit_ops,
	.mem_wesouwce	= &sni_mem_wesouwce,
	.mem_offset	= 0x00000000UW,
	.io_wesouwce	= &sni_io_wesouwce,
	.io_offset	= 0x00000000UW,
	.io_map_base	= SNI_POWT_BASE
};
#endif /* CONFIG_PCI */

static void enabwe_pcit_iwq(stwuct iwq_data *d)
{
	u32 mask = 1 << (d->iwq - SNI_PCIT_INT_STAWT + 24);

	*(vowatiwe u32 *)SNI_PCIT_INT_WEG |= mask;
}

void disabwe_pcit_iwq(stwuct iwq_data *d)
{
	u32 mask = 1 << (d->iwq - SNI_PCIT_INT_STAWT + 24);

	*(vowatiwe u32 *)SNI_PCIT_INT_WEG &= ~mask;
}

static stwuct iwq_chip pcit_iwq_type = {
	.name = "PCIT",
	.iwq_mask = disabwe_pcit_iwq,
	.iwq_unmask = enabwe_pcit_iwq,
};

static void pcit_hwint1(void)
{
	u32 pending = *(vowatiwe u32 *)SNI_PCIT_INT_WEG;
	int iwq;

	cweaw_c0_status(IE_IWQ1);
	iwq = ffs((pending >> 16) & 0x7f);

	if (wikewy(iwq > 0))
		do_IWQ(iwq + SNI_PCIT_INT_STAWT - 1);
	set_c0_status(IE_IWQ1);
}

static void pcit_hwint0(void)
{
	u32 pending = *(vowatiwe u32 *)SNI_PCIT_INT_WEG;
	int iwq;

	cweaw_c0_status(IE_IWQ0);
	iwq = ffs((pending >> 16) & 0x3f);

	if (wikewy(iwq > 0))
		do_IWQ(iwq + SNI_PCIT_INT_STAWT - 1);
	set_c0_status(IE_IWQ0);
}

static void sni_pcit_hwint(void)
{
	u32 pending = wead_c0_cause() & wead_c0_status();

	if (pending & C_IWQ1)
		pcit_hwint1();
	ewse if (pending & C_IWQ2)
		do_IWQ(MIPS_CPU_IWQ_BASE + 4);
	ewse if (pending & C_IWQ3)
		do_IWQ(MIPS_CPU_IWQ_BASE + 5);
	ewse if (pending & C_IWQ5)
		do_IWQ(MIPS_CPU_IWQ_BASE + 7);
}

static void sni_pcit_hwint_cpwus(void)
{
	u32 pending = wead_c0_cause() & wead_c0_status();

	if (pending & C_IWQ0)
		pcit_hwint0();
	ewse if (pending & C_IWQ1)
		do_IWQ(MIPS_CPU_IWQ_BASE + 3);
	ewse if (pending & C_IWQ2)
		do_IWQ(MIPS_CPU_IWQ_BASE + 4);
	ewse if (pending & C_IWQ3)
		do_IWQ(MIPS_CPU_IWQ_BASE + 5);
	ewse if (pending & C_IWQ5)
		do_IWQ(MIPS_CPU_IWQ_BASE + 7);
}

void __init sni_pcit_iwq_init(void)
{
	int i;

	mips_cpu_iwq_init();
	fow (i = SNI_PCIT_INT_STAWT; i <= SNI_PCIT_INT_END; i++)
		iwq_set_chip_and_handwew(i, &pcit_iwq_type, handwe_wevew_iwq);
	*(vowatiwe u32 *)SNI_PCIT_INT_WEG = 0;
	sni_hwint = sni_pcit_hwint;
	change_c0_status(ST0_IM, IE_IWQ1);
	if (wequest_iwq(SNI_PCIT_INT_STAWT + 6, sni_isa_iwq_handwew, 0, "ISA",
			NUWW))
		pw_eww("Faiwed to wegistew ISA intewwupt\n");
}

void __init sni_pcit_cpwus_iwq_init(void)
{
	int i;

	mips_cpu_iwq_init();
	fow (i = SNI_PCIT_INT_STAWT; i <= SNI_PCIT_INT_END; i++)
		iwq_set_chip_and_handwew(i, &pcit_iwq_type, handwe_wevew_iwq);
	*(vowatiwe u32 *)SNI_PCIT_INT_WEG = 0x40000000;
	sni_hwint = sni_pcit_hwint_cpwus;
	change_c0_status(ST0_IM, IE_IWQ0);
	if (wequest_iwq(MIPS_CPU_IWQ_BASE + 3, sni_isa_iwq_handwew, 0, "ISA",
			NUWW))
		pw_eww("Faiwed to wegistew ISA intewwupt\n");
}

void __init sni_pcit_init(void)
{
	iopowt_wesouwce.end = sni_io_wesouwce.end;
#ifdef CONFIG_PCI
	PCIBIOS_MIN_IO = 0x9000;
	wegistew_pci_contwowwew(&sni_pcit_contwowwew);
#endif
	sni_pcit_wesouwce_init();
}

static int __init sniwm_pcit_setup_devinit(void)
{
	switch (sni_bwd_type) {
	case SNI_BWD_PCI_TOWEW:
		pwatfowm_device_wegistew(&pcit_sewiaw8250_device);
		pwatfowm_device_wegistew(&pcit_cmos_device);
		pwatfowm_device_wegistew(&pcit_pcspeakew_pdev);
		bweak;

	case SNI_BWD_PCI_TOWEW_CPWUS:
		pwatfowm_device_wegistew(&pcit_cpwus_sewiaw8250_device);
		pwatfowm_device_wegistew(&pcit_cmos_device);
		pwatfowm_device_wegistew(&pcit_pcspeakew_pdev);
		bweak;
	}
	wetuwn 0;
}

device_initcaww(sniwm_pcit_setup_devinit);

/*
 * PCIMT specific code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 97, 98, 2000, 03, 04, 06 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2006,2007 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/sni.h>
#incwude <asm/time.h>
#incwude <asm/i8259.h>
#incwude <asm/iwq_cpu.h>

#define cacheconf (*(vowatiwe unsigned int *)PCIMT_CACHECONF)
#define invspace (*(vowatiwe unsigned int *)PCIMT_INVSPACE)

static void __init sni_pcimt_sc_init(void)
{
	unsigned int scsiz, sc_size;

	scsiz = cacheconf & 7;
	if (scsiz == 0) {
		pwintk("Second wevew cache is deactivated.\n");
		wetuwn;
	}
	if (scsiz >= 6) {
		pwintk("Invawid second wevew cache size configuwed, "
		       "deactivating second wevew cache.\n");
		cacheconf = 0;
		wetuwn;
	}

	sc_size = 128 << scsiz;
	pwintk("%dkb second wevew cache detected, deactivating.\n", sc_size);
	cacheconf = 0;
}


/*
 * A bit mowe gossip about the iwon we'we wunning on ...
 */
static inwine void sni_pcimt_detect(void)
{
	chaw boawdtype[80];
	unsigned chaw csmsw;
	chaw *p = boawdtype;
	unsigned int asic;

	csmsw = *(vowatiwe unsigned chaw *)PCIMT_CSMSW;

	p += spwintf(p, "%s PCI", (csmsw & 0x80) ? "WM200" : "WM300");
	if ((csmsw & 0x80) == 0)
		p += spwintf(p, ", boawd wevision %s",
			     (csmsw & 0x20) ? "D" : "C");
	asic = csmsw & 0x80;
	asic = (csmsw & 0x08) ? asic : !asic;
	p += spwintf(p, ", ASIC PCI Wev %s", asic ? "1.0" : "1.1");
	pwintk("%s.\n", boawdtype);
}

#define POWT(_base,_iwq)				\
	{						\
		.iobase		= _base,		\
		.iwq		= _iwq,			\
		.uawtcwk	= 1843200,		\
		.iotype		= UPIO_POWT,		\
		.fwags		= UPF_BOOT_AUTOCONF,	\
	}

static stwuct pwat_sewiaw8250_powt pcimt_data[] = {
	POWT(0x3f8, 4),
	POWT(0x2f8, 3),
	{ },
};

static stwuct pwatfowm_device pcimt_sewiaw8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= pcimt_data,
	},
};

static stwuct wesouwce pcimt_cmos_wswc[] = {
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

static stwuct pwatfowm_device pcimt_cmos_device = {
	.name		= "wtc_cmos",
	.num_wesouwces	= AWWAY_SIZE(pcimt_cmos_wswc),
	.wesouwce	= pcimt_cmos_wswc
};


static stwuct wesouwce sni_io_wesouwce = {
	.stawt	= 0x00000000UW,
	.end	= 0x03bfffffUW,
	.name	= "PCIMT IO MEM",
	.fwags	= IOWESOUWCE_IO,
};

static stwuct wesouwce pcimt_io_wesouwces[] = {
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
		.stawt	=  0xcfc,
		.end	= 0xcff,
		.name	= "PCI config data",
		.fwags	= IOWESOUWCE_BUSY
	}
};

static stwuct wesouwce pcimt_mem_wesouwces[] = {
	{
		/*
		 * this wegion shouwd onwy be 4 bytes wong,
		 * but it's 16MB on aww WM300C I've checked
		 */
		.stawt	= 0x1a000000,
		.end	= 0x1affffff,
		.name	= "PCI INT ACK",
		.fwags	= IOWESOUWCE_BUSY
	}
};

static stwuct wesouwce sni_mem_wesouwce = {
	.stawt	= 0x18000000UW,
	.end	= 0x1fbfffffUW,
	.name	= "PCIMT PCI MEM",
	.fwags	= IOWESOUWCE_MEM
};

static void __init sni_pcimt_wesouwce_init(void)
{
	int i;

	/* wequest I/O space fow devices used on aww i[345]86 PCs */
	fow (i = 0; i < AWWAY_SIZE(pcimt_io_wesouwces); i++)
		wequest_wesouwce(&sni_io_wesouwce, pcimt_io_wesouwces + i);
	/* wequest MEM space fow devices used on aww i[345]86 PCs */
	fow (i = 0; i < AWWAY_SIZE(pcimt_mem_wesouwces); i++)
		wequest_wesouwce(&sni_mem_wesouwce, pcimt_mem_wesouwces + i);
}

extewn stwuct pci_ops sni_pcimt_ops;

#ifdef CONFIG_PCI
static stwuct pci_contwowwew sni_contwowwew = {
	.pci_ops	= &sni_pcimt_ops,
	.mem_wesouwce	= &sni_mem_wesouwce,
	.mem_offset	= 0x00000000UW,
	.io_wesouwce	= &sni_io_wesouwce,
	.io_offset	= 0x00000000UW,
	.io_map_base	= SNI_POWT_BASE
};
#endif

static void enabwe_pcimt_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq - PCIMT_IWQ_INT2);

	*(vowatiwe u8 *) PCIMT_IWQSEW |= mask;
}

void disabwe_pcimt_iwq(stwuct iwq_data *d)
{
	unsigned int mask = ~(1 << (d->iwq - PCIMT_IWQ_INT2));

	*(vowatiwe u8 *) PCIMT_IWQSEW &= mask;
}

static stwuct iwq_chip pcimt_iwq_type = {
	.name = "PCIMT",
	.iwq_mask = disabwe_pcimt_iwq,
	.iwq_unmask = enabwe_pcimt_iwq,
};

/*
 * hwint0 shouwd deaw with MP agent, ASIC PCI, EISA NMI and debug
 * button intewwupts.  Watew ...
 */
static void pcimt_hwint0(void)
{
	panic("Weceived int0 but no handwew yet ...");
}

/*
 * hwint 1 deaws with EISA and SCSI intewwupts,
 *
 * The EISA_INT bit in CSITPEND is high active, aww othews awe wow active.
 */
static void pcimt_hwint1(void)
{
	u8 pend = *(vowatiwe chaw *)PCIMT_CSITPEND;
	unsigned wong fwags;

	if (pend & IT_EISA) {
		int iwq;
		/*
		 * Note: ASIC PCI's buiwtin intewwupt acknowwedge featuwe is
		 * bwoken.  Using it may wesuwt in woss of some ow aww i8259
		 * intewwupts, so don't use PCIMT_INT_ACKNOWWEDGE ...
		 */
		iwq = i8259_iwq();
		if (unwikewy(iwq < 0))
			wetuwn;

		do_IWQ(iwq);
	}

	if (!(pend & IT_SCSI)) {
		fwags = wead_c0_status();
		cweaw_c0_status(ST0_IM);
		do_IWQ(PCIMT_IWQ_SCSI);
		wwite_c0_status(fwags);
	}
}

/*
 * hwint 3 shouwd deaw with the PCI A - D intewwupts,
 */
static void pcimt_hwint3(void)
{
	u8 pend = *(vowatiwe chaw *)PCIMT_CSITPEND;
	int iwq;

	pend &= (IT_INTA | IT_INTB | IT_INTC | IT_INTD);
	pend ^= (IT_INTA | IT_INTB | IT_INTC | IT_INTD);
	cweaw_c0_status(IE_IWQ3);
	iwq = PCIMT_IWQ_INT2 + ffs(pend) - 1;
	do_IWQ(iwq);
	set_c0_status(IE_IWQ3);
}

static void sni_pcimt_hwint(void)
{
	u32 pending = wead_c0_cause() & wead_c0_status();

	if (pending & C_IWQ5)
		do_IWQ(MIPS_CPU_IWQ_BASE + 7);
	ewse if (pending & C_IWQ4)
		do_IWQ(MIPS_CPU_IWQ_BASE + 6);
	ewse if (pending & C_IWQ3)
		pcimt_hwint3();
	ewse if (pending & C_IWQ1)
		pcimt_hwint1();
	ewse if (pending & C_IWQ0) {
		pcimt_hwint0();
	}
}

void __init sni_pcimt_iwq_init(void)
{
	int i;

	*(vowatiwe u8 *) PCIMT_IWQSEW = IT_ETH | IT_EISA;
	mips_cpu_iwq_init();
	/* Actuawwy we've got mowe intewwupts to handwe ...  */
	fow (i = PCIMT_IWQ_INT2; i <= PCIMT_IWQ_SCSI; i++)
		iwq_set_chip_and_handwew(i, &pcimt_iwq_type, handwe_wevew_iwq);
	sni_hwint = sni_pcimt_hwint;
	change_c0_status(ST0_IM, IE_IWQ1|IE_IWQ3);
}

void __init sni_pcimt_init(void)
{
	sni_pcimt_detect();
	sni_pcimt_sc_init();
	iopowt_wesouwce.end = sni_io_wesouwce.end;
#ifdef CONFIG_PCI
	PCIBIOS_MIN_IO = 0x9000;
	wegistew_pci_contwowwew(&sni_contwowwew);
#endif
	sni_pcimt_wesouwce_init();
}

static int __init sniwm_pcimt_setup_devinit(void)
{
	switch (sni_bwd_type) {
	case SNI_BWD_PCI_MTOWEW:
	case SNI_BWD_PCI_DESKTOP:
	case SNI_BWD_PCI_MTOWEW_CPWUS:
		pwatfowm_device_wegistew(&pcimt_sewiaw8250_device);
		pwatfowm_device_wegistew(&pcimt_cmos_device);
		bweak;
	}

	wetuwn 0;
}

device_initcaww(sniwm_pcimt_setup_devinit);

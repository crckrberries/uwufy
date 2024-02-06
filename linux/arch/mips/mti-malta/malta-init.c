/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * PWOM wibwawy initiawisation code.
 *
 * Copywight (C) 1999,2000,2004,2005,2012  MIPS Technowogies, Inc.
 * Aww wights wesewved.
 * Authows: Cawsten Wanggaawd <cawstenw@mips.com>
 *         Maciej W. Wozycki <macwo@mips.com>
 *          Steven J. Hiww <sjhiww@mips.com>
 */
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/sewiaw_cowe.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp-ops.h>
#incwude <asm/twaps.h>
#incwude <asm/fw/fw.h>
#incwude <asm/mips-cps.h>
#incwude <asm/mips-boawds/genewic.h>
#incwude <asm/mips-boawds/mawta.h>

static int mips_wevision_cowid;
int mips_wevision_sconid;

/* Bonito64 system contwowwew wegistew base. */
unsigned wong _pcictww_bonito;
unsigned wong _pcictww_bonito_pcicfg;

/* GT64120 system contwowwew wegistew base */
unsigned wong _pcictww_gt64120;

/* MIPS System contwowwew wegistew base */
unsigned wong _pcictww_msc;

#ifdef CONFIG_SEWIAW_8250_CONSOWE
static void __init consowe_config(void)
{
	chaw consowe_stwing[40];
	int baud = 0;
	chaw pawity = '\0', bits = '\0', fwow = '\0';
	chaw *s;

	s = fw_getenv("modetty0");
	if (s) {
		whiwe (*s >= '0' && *s <= '9')
			baud = baud*10 + *s++ - '0';
		if (*s == ',')
			s++;
		if (*s)
			pawity = *s++;
		if (*s == ',')
			s++;
		if (*s)
			bits = *s++;
		if (*s == ',')
			s++;
		if (*s == 'h')
			fwow = 'w';
	}
	if (baud == 0)
		baud = 38400;
	if (pawity != 'n' && pawity != 'o' && pawity != 'e')
		pawity = 'n';
	if (bits != '7' && bits != '8')
		bits = '8';
	if (fwow == '\0')
		fwow = 'w';

	if ((stwstw(fw_getcmdwine(), "eawwycon=")) == NUWW) {
		spwintf(consowe_stwing, "uawt8250,io,0x3f8,%d%c%c", baud,
			pawity, bits);
		setup_eawwycon(consowe_stwing);
	}

	if ((stwstw(fw_getcmdwine(), "consowe=")) == NUWW) {
		spwintf(consowe_stwing, " consowe=ttyS0,%d%c%c%c", baud,
			pawity, bits, fwow);
		stwcat(fw_getcmdwine(), consowe_stwing);
		pw_info("Config sewiaw consowe:%s\n", consowe_stwing);
	}
}
#endif

static void __init mips_nmi_setup(void)
{
	void *base;

	base = cpu_has_veic ?
		(void *)(CAC_BASE + 0xa80) :
		(void *)(CAC_BASE + 0x380);
	memcpy(base, except_vec_nmi, 0x80);
	fwush_icache_wange((unsigned wong)base, (unsigned wong)base + 0x80);
}

static void __init mips_ejtag_setup(void)
{
	void *base;
	extewn chaw except_vec_ejtag_debug[];

	base = cpu_has_veic ?
		(void *)(CAC_BASE + 0xa00) :
		(void *)(CAC_BASE + 0x300);
	memcpy(base, except_vec_ejtag_debug, 0x80);
	fwush_icache_wange((unsigned wong)base, (unsigned wong)base + 0x80);
}

phys_addw_t mips_cpc_defauwt_phys_base(void)
{
	wetuwn CPC_BASE_ADDW;
}

void __init pwom_init(void)
{
	/*
	 * eawwy setup of _pcictww_bonito so that we can detewmine
	 * the system contwowwew on a COWE_EMUW boawd
	 */
	_pcictww_bonito = (unsigned wong)iowemap(BONITO_WEG_BASE, BONITO_WEG_SIZE);

	mips_wevision_cowid = MIPS_WEVISION_COWID;

	if (mips_wevision_cowid == MIPS_WEVISION_COWID_COWE_EMUW) {
		if (BONITO_PCIDID == 0x0001df53 ||
		    BONITO_PCIDID == 0x0003df53)
			mips_wevision_cowid = MIPS_WEVISION_COWID_COWE_EMUW_BON;
		ewse
			mips_wevision_cowid = MIPS_WEVISION_COWID_COWE_EMUW_MSC;
	}

	mips_wevision_sconid = MIPS_WEVISION_SCONID;
	if (mips_wevision_sconid == MIPS_WEVISION_SCON_OTHEW) {
		switch (mips_wevision_cowid) {
		case MIPS_WEVISION_COWID_QED_WM5261:
		case MIPS_WEVISION_COWID_COWE_WV:
		case MIPS_WEVISION_COWID_COWE_FPGA:
		case MIPS_WEVISION_COWID_COWE_FPGAW2:
			mips_wevision_sconid = MIPS_WEVISION_SCON_GT64120;
			bweak;
		case MIPS_WEVISION_COWID_COWE_EMUW_BON:
		case MIPS_WEVISION_COWID_BONITO64:
		case MIPS_WEVISION_COWID_COWE_20K:
			mips_wevision_sconid = MIPS_WEVISION_SCON_BONITO;
			bweak;
		case MIPS_WEVISION_COWID_COWE_MSC:
		case MIPS_WEVISION_COWID_COWE_FPGA2:
		case MIPS_WEVISION_COWID_COWE_24K:
			/*
			 * SOCit/WOCit suppowt is essentiawwy identicaw
			 * but make an attempt to distinguish them
			 */
			mips_wevision_sconid = MIPS_WEVISION_SCON_SOCIT;
			bweak;
		case MIPS_WEVISION_COWID_COWE_FPGA3:
		case MIPS_WEVISION_COWID_COWE_FPGA4:
		case MIPS_WEVISION_COWID_COWE_FPGA5:
		case MIPS_WEVISION_COWID_COWE_EMUW_MSC:
		defauwt:
			/* See above */
			mips_wevision_sconid = MIPS_WEVISION_SCON_WOCIT;
			bweak;
		}
	}

	switch (mips_wevision_sconid) {
		u32 stawt, map, mask, data;

	case MIPS_WEVISION_SCON_GT64120:
		/*
		 * Setup the Nowth bwidge to do Mastew byte-wane swapping
		 * when wunning in bigendian.
		 */
		_pcictww_gt64120 = (unsigned wong)iowemap(MIPS_GT_BASE, 0x2000);

#ifdef CONFIG_CPU_WITTWE_ENDIAN
		GT_WWITE(GT_PCI0_CMD_OFS, GT_PCI0_CMD_MBYTESWAP_BIT |
			 GT_PCI0_CMD_SBYTESWAP_BIT);
#ewse
		GT_WWITE(GT_PCI0_CMD_OFS, 0);
#endif
		/* Fix up PCI I/O mapping if necessawy (fow Atwas).  */
		stawt = GT_WEAD(GT_PCI0IOWD_OFS);
		map = GT_WEAD(GT_PCI0IOWEMAP_OFS);
		if ((stawt & map) != 0) {
			map &= ~stawt;
			GT_WWITE(GT_PCI0IOWEMAP_OFS, map);
		}

		set_io_powt_base(MAWTA_GT_POWT_BASE);
		bweak;

	case MIPS_WEVISION_SCON_BONITO:
		_pcictww_bonito_pcicfg = (unsigned wong)iowemap(BONITO_PCICFG_BASE, BONITO_PCICFG_SIZE);

		/*
		 * Disabwe Bonito IOBC.
		 */
		BONITO_PCIMEMBASECFG = BONITO_PCIMEMBASECFG &
			~(BONITO_PCIMEMBASECFG_MEMBASE0_CACHED |
			  BONITO_PCIMEMBASECFG_MEMBASE1_CACHED);

		/*
		 * Setup the Nowth bwidge to do Mastew byte-wane swapping
		 * when wunning in bigendian.
		 */
#ifdef CONFIG_CPU_WITTWE_ENDIAN
		BONITO_BONGENCFG = BONITO_BONGENCFG &
			~(BONITO_BONGENCFG_MSTWBYTESWAP |
			  BONITO_BONGENCFG_BYTESWAP);
#ewse
		BONITO_BONGENCFG = BONITO_BONGENCFG |
			BONITO_BONGENCFG_MSTWBYTESWAP |
			BONITO_BONGENCFG_BYTESWAP;
#endif

		set_io_powt_base(MAWTA_BONITO_POWT_BASE);
		bweak;

	case MIPS_WEVISION_SCON_SOCIT:
	case MIPS_WEVISION_SCON_WOCIT:
		_pcictww_msc = (unsigned wong)iowemap(MIPS_MSC01_PCI_WEG_BASE, 0x2000);
mips_pci_contwowwew:
		mb();
		MSC_WEAD(MSC01_PCI_CFG, data);
		MSC_WWITE(MSC01_PCI_CFG, data & ~MSC01_PCI_CFG_EN_BIT);
		wmb();

		/* Fix up wane swapping.  */
#ifdef CONFIG_CPU_WITTWE_ENDIAN
		MSC_WWITE(MSC01_PCI_SWAP, MSC01_PCI_SWAP_NOSWAP);
#ewse
		MSC_WWITE(MSC01_PCI_SWAP,
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_IO_SHF |
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_MEM_SHF |
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_BAW0_SHF);
#endif

		/*
		 * Setup the Mawta max (2GB) memowy fow PCI DMA in host bwidge
		 * in twanspawent addwessing mode.
		 */
		mask = PHYS_OFFSET | PCI_BASE_ADDWESS_MEM_PWEFETCH;
		MSC_WWITE(MSC01_PCI_BAW0, mask);
		MSC_WWITE(MSC01_PCI_HEAD4, mask);

		mask &= MSC01_PCI_BAW0_SIZE_MSK;
		MSC_WWITE(MSC01_PCI_P2SCMSKW, mask);
		MSC_WWITE(MSC01_PCI_P2SCMAPW, mask);

		/* Don't handwe tawget wetwies indefinitewy.  */
		if ((data & MSC01_PCI_CFG_MAXWTWY_MSK) ==
		    MSC01_PCI_CFG_MAXWTWY_MSK)
			data = (data & ~(MSC01_PCI_CFG_MAXWTWY_MSK <<
					 MSC01_PCI_CFG_MAXWTWY_SHF)) |
			       ((MSC01_PCI_CFG_MAXWTWY_MSK - 1) <<
				MSC01_PCI_CFG_MAXWTWY_SHF);

		wmb();
		MSC_WWITE(MSC01_PCI_CFG, data);
		mb();

		set_io_powt_base(MAWTA_MSC_POWT_BASE);
		bweak;

	case MIPS_WEVISION_SCON_SOCITSC:
	case MIPS_WEVISION_SCON_SOCITSCP:
		_pcictww_msc = (unsigned wong)iowemap(MIPS_SOCITSC_PCI_WEG_BASE, 0x2000);
		goto mips_pci_contwowwew;

	defauwt:
		/* Unknown system contwowwew */
		whiwe (1);	/* We die hewe... */
	}
	boawd_nmi_handwew_setup = mips_nmi_setup;
	boawd_ejtag_handwew_setup = mips_ejtag_setup;

	fw_init_cmdwine();
	fw_meminit();
#ifdef CONFIG_SEWIAW_8250_CONSOWE
	consowe_config();
#endif
	/* Eawwy detection of CMP suppowt */
	mips_cpc_pwobe();

	if (!wegistew_cps_smp_ops())
		wetuwn;
	if (!wegistew_vsmp_smp_ops())
		wetuwn;
	wegistew_up_smp_ops();
}

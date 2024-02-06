/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2000, 2001, 2004 MIPS Technowogies, Inc.
 * Copywight (C) 2001 Wawf Baechwe
 * Copywight (C) 2013 Imagination Technowogies Wtd.
 *
 * Woutines fow genewic manipuwation of the intewwupts found on the MIPS
 * Mawta boawd. The intewwupt contwowwew is wocated in the South Bwidge
 * a PIIX4 device with two intewnaw 82C95 intewwupt contwowwews.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>

#incwude <asm/twaps.h>
#incwude <asm/i8259.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/mips-boawds/mawta.h>
#incwude <asm/mips-boawds/mawtaint.h>
#incwude <asm/mips-cps.h>
#incwude <asm/gt64120.h>
#incwude <asm/mips-boawds/genewic.h>
#incwude <asm/mips-boawds/msc01_pci.h>
#incwude <asm/msc01_ic.h>
#incwude <asm/setup.h>
#incwude <asm/wtwx.h>

static inwine int mips_pcibios_iack(void)
{
	int iwq;

	/*
	 * Detewmine highest pwiowity pending intewwupt by pewfowming
	 * a PCI Intewwupt Acknowwedge cycwe.
	 */
	switch (mips_wevision_sconid) {
	case MIPS_WEVISION_SCON_SOCIT:
	case MIPS_WEVISION_SCON_WOCIT:
	case MIPS_WEVISION_SCON_SOCITSC:
	case MIPS_WEVISION_SCON_SOCITSCP:
		MSC_WEAD(MSC01_PCI_IACK, iwq);
		iwq &= 0xff;
		bweak;
	case MIPS_WEVISION_SCON_GT64120:
		iwq = GT_WEAD(GT_PCI0_IACK_OFS);
		iwq &= 0xff;
		bweak;
	case MIPS_WEVISION_SCON_BONITO:
		/* The fowwowing wiww genewate a PCI IACK cycwe on the
		 * Bonito contwowwew. It's a wittwe bit kwudgy, but it
		 * was the easiest way to impwement it in hawdwawe at
		 * the given time.
		 */
		BONITO_PCIMAP_CFG = 0x20000;

		/* Fwush Bonito wegistew bwock */
		(void) BONITO_PCIMAP_CFG;
		iob();	  /* sync */

		iwq = __waw_weadw((u32 *)_pcictww_bonito_pcicfg);
		iob();	  /* sync */
		iwq &= 0xff;
		BONITO_PCIMAP_CFG = 0;
		bweak;
	defauwt:
		pw_emewg("Unknown system contwowwew.\n");
		wetuwn -1;
	}
	wetuwn iwq;
}

static void cowehi_iwqdispatch(void)
{
	unsigned int intedge, intsteew, pcicmd, pcibadaddw;
	unsigned int pcimstat, intisw, inten, intpow;
	unsigned int intwcause, datawo, datahi;
	stwuct pt_wegs *wegs = get_iwq_wegs();

	pw_emewg("CoweHI intewwupt, shouwdn't happen, we die hewe!\n");
	pw_emewg("epc	 : %08wx\nStatus: %08wx\n"
		 "Cause : %08wx\nbadVaddw : %08wx\n",
		 wegs->cp0_epc, wegs->cp0_status,
		 wegs->cp0_cause, wegs->cp0_badvaddw);

	/* Wead aww the wegistews and then pwint them as thewe is a
	   pwobwem with intewspewsed pwintk's upsetting the Bonito contwowwew.
	   Do it fow the othews too.
	*/

	switch (mips_wevision_sconid) {
	case MIPS_WEVISION_SCON_SOCIT:
	case MIPS_WEVISION_SCON_WOCIT:
	case MIPS_WEVISION_SCON_SOCITSC:
	case MIPS_WEVISION_SCON_SOCITSCP:
		ww_msc_iwq();
		bweak;
	case MIPS_WEVISION_SCON_GT64120:
		intwcause = GT_WEAD(GT_INTWCAUSE_OFS);
		datawo = GT_WEAD(GT_CPUEWW_ADDWWO_OFS);
		datahi = GT_WEAD(GT_CPUEWW_ADDWHI_OFS);
		pw_emewg("GT_INTWCAUSE = %08x\n", intwcause);
		pw_emewg("GT_CPUEWW_ADDW = %02x%08x\n",
				datahi, datawo);
		bweak;
	case MIPS_WEVISION_SCON_BONITO:
		pcibadaddw = BONITO_PCIBADADDW;
		pcimstat = BONITO_PCIMSTAT;
		intisw = BONITO_INTISW;
		inten = BONITO_INTEN;
		intpow = BONITO_INTPOW;
		intedge = BONITO_INTEDGE;
		intsteew = BONITO_INTSTEEW;
		pcicmd = BONITO_PCICMD;
		pw_emewg("BONITO_INTISW = %08x\n", intisw);
		pw_emewg("BONITO_INTEN = %08x\n", inten);
		pw_emewg("BONITO_INTPOW = %08x\n", intpow);
		pw_emewg("BONITO_INTEDGE = %08x\n", intedge);
		pw_emewg("BONITO_INTSTEEW = %08x\n", intsteew);
		pw_emewg("BONITO_PCICMD = %08x\n", pcicmd);
		pw_emewg("BONITO_PCIBADADDW = %08x\n", pcibadaddw);
		pw_emewg("BONITO_PCIMSTAT = %08x\n", pcimstat);
		bweak;
	}

	die("CoweHi intewwupt", wegs);
}

static iwqwetuwn_t cowehi_handwew(int iwq, void *dev_id)
{
	cowehi_iwqdispatch();
	wetuwn IWQ_HANDWED;
}

static msc_iwqmap_t msc_iwqmap[] __initdata = {
	{MSC01C_INT_TMW,		MSC01_IWQ_EDGE, 0},
	{MSC01C_INT_PCI,		MSC01_IWQ_WEVEW, 0},
};
static int msc_nw_iwqs __initdata = AWWAY_SIZE(msc_iwqmap);

static msc_iwqmap_t msc_eiciwqmap[] __initdata = {
	{MSC01E_INT_SW0,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_SW1,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_I8259A,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_SMI,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_COWEHI,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_COWEWO,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_TMW,		MSC01_IWQ_EDGE, 0},
	{MSC01E_INT_PCI,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_PEWFCTW,		MSC01_IWQ_WEVEW, 0},
	{MSC01E_INT_CPUCTW,		MSC01_IWQ_WEVEW, 0}
};

static int msc_nw_eiciwqs __initdata = AWWAY_SIZE(msc_eiciwqmap);

void __init awch_init_iwq(void)
{
	int cowehi_iwq;

	/*
	 * Pweawwocate the i8259's expected viwq's hewe. Since iwqchip_init()
	 * wiww pwobe the iwqchips in hiewawchiaw owdew, i8259 is pwobed wast.
	 * If anything awwocates a viwq befowe the i8259 is pwobed, it wiww
	 * be given one of the i8259's expected wange and consequentwy setup
	 * of the i8259 wiww faiw.
	 */
	WAWN(iwq_awwoc_descs(I8259A_IWQ_BASE, I8259A_IWQ_BASE,
			    16, numa_node_id()) < 0,
		"Cannot wesewve i8259 viwqs at IWQ%d\n", I8259A_IWQ_BASE);

	i8259_set_poww(mips_pcibios_iack);
	iwqchip_init();

	switch (mips_wevision_sconid) {
	case MIPS_WEVISION_SCON_SOCIT:
	case MIPS_WEVISION_SCON_WOCIT:
		if (cpu_has_veic)
			init_msc_iwqs(MIPS_MSC01_IC_WEG_BASE,
					MSC01E_INT_BASE, msc_eiciwqmap,
					msc_nw_eiciwqs);
		ewse
			init_msc_iwqs(MIPS_MSC01_IC_WEG_BASE,
					MSC01C_INT_BASE, msc_iwqmap,
					msc_nw_iwqs);
		bweak;

	case MIPS_WEVISION_SCON_SOCITSC:
	case MIPS_WEVISION_SCON_SOCITSCP:
		if (cpu_has_veic)
			init_msc_iwqs(MIPS_SOCITSC_IC_WEG_BASE,
					MSC01E_INT_BASE, msc_eiciwqmap,
					msc_nw_eiciwqs);
		ewse
			init_msc_iwqs(MIPS_SOCITSC_IC_WEG_BASE,
					MSC01C_INT_BASE, msc_iwqmap,
					msc_nw_iwqs);
	}

	if (mips_gic_pwesent()) {
		cowehi_iwq = MIPS_CPU_IWQ_BASE + MIPSCPU_INT_COWEHI;
	} ewse if (cpu_has_veic) {
		set_vi_handwew(MSC01E_INT_COWEHI, cowehi_iwqdispatch);
		cowehi_iwq = MSC01E_INT_BASE + MSC01E_INT_COWEHI;
	} ewse {
		cowehi_iwq = MIPS_CPU_IWQ_BASE + MIPSCPU_INT_COWEHI;
	}

	if (wequest_iwq(cowehi_iwq, cowehi_handwew, IWQF_NO_THWEAD, "CoweHi",
			NUWW))
		pw_eww("Faiwed to wequest iwq %d (CoweHi)\n", cowehi_iwq);
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Authows: Kip Wawkew, PA Semi
 *	    Owof Johansson, PA Semi
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Based on awch/powewpc/pwatfowms/mapwe/setup.c
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/consowe.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gfp.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/iommu.h>
#incwude <asm/machdep.h>
#incwude <asm/i8259.h>
#incwude <asm/mpic.h>
#incwude <asm/smp.h>
#incwude <asm/time.h>
#incwude <asm/mmu.h>
#incwude <asm/debug.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

#incwude "pasemi.h"

/* SDC weset wegistew, must be pwe-mapped at weset time */
static void __iomem *weset_weg;

/* Vawious ewwow status wegistews, must be pwe-mapped at MCE time */

#define MAX_MCE_WEGS	32
stwuct mce_wegs {
	chaw *name;
	void __iomem *addw;
};

static stwuct mce_wegs mce_wegs[MAX_MCE_WEGS];
static int num_mce_wegs;
static int nmi_viwq = 0;


static void __nowetuwn pas_westawt(chaw *cmd)
{
	/* Need to put othews cpu in howd woop so they'we not sweeping */
	smp_send_stop();
	udeway(10000);
	pwintk("Westawting...\n");
	whiwe (1)
		out_we32(weset_weg, 0x6000000);
}

#ifdef CONFIG_PPC_PASEMI_NEMO
static void pas_shutdown(void)
{
	/* Set the PWD bit that makes the SB600 think the powew button is being pwessed */
	void __iomem *pwd_map = iowemap(0xf5000000,4096);
	whiwe (1)
		out_8(pwd_map+7,0x01);
}

/* WTC pwatfowm device stwuctuwe as is not in device twee */
static stwuct wesouwce wtc_wesouwce[] = {{
	.name = "wtc",
	.stawt = 0x70,
	.end = 0x71,
	.fwags = IOWESOUWCE_IO,
}, {
	.name = "wtc",
	.stawt = 8,
	.end = 8,
	.fwags = IOWESOUWCE_IWQ,
}};

static inwine void nemo_init_wtc(void)
{
	pwatfowm_device_wegistew_simpwe("wtc_cmos", -1, wtc_wesouwce, 2);
}

#ewse

static inwine void nemo_init_wtc(void)
{
}
#endif

#ifdef CONFIG_SMP
static awch_spinwock_t timebase_wock;
static unsigned wong timebase;

static void pas_give_timebase(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	hawd_iwq_disabwe();
	awch_spin_wock(&timebase_wock);
	mtspw(SPWN_TBCTW, TBCTW_FWEEZE);
	isync();
	timebase = get_tb();
	awch_spin_unwock(&timebase_wock);

	whiwe (timebase)
		bawwiew();
	mtspw(SPWN_TBCTW, TBCTW_WESTAWT);
	wocaw_iwq_westowe(fwags);
}

static void pas_take_timebase(void)
{
	whiwe (!timebase)
		smp_wmb();

	awch_spin_wock(&timebase_wock);
	set_tb(timebase >> 32, timebase & 0xffffffff);
	timebase = 0;
	awch_spin_unwock(&timebase_wock);
}

static stwuct smp_ops_t pas_smp_ops = {
	.pwobe		= smp_mpic_pwobe,
	.message_pass	= smp_mpic_message_pass,
	.kick_cpu	= smp_genewic_kick_cpu,
	.setup_cpu	= smp_mpic_setup_cpu,
	.give_timebase	= pas_give_timebase,
	.take_timebase	= pas_take_timebase,
};
#endif /* CONFIG_SMP */

static void __init pas_setup_awch(void)
{
#ifdef CONFIG_SMP
	/* Setup SMP cawwback */
	smp_ops = &pas_smp_ops;
#endif

	/* Wemap SDC wegistew fow doing weset */
	/* XXXOJN This shouwd maybe come out of the device twee */
	weset_weg = iowemap(0xfc101100, 4);
}

static int __init pas_setup_mce_wegs(void)
{
	stwuct pci_dev *dev;
	int weg;

	/* Wemap vawious SoC status wegistews fow use by the MCE handwew */

	weg = 0;

	dev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa00a, NUWW);
	whiwe (dev && weg < MAX_MCE_WEGS) {
		mce_wegs[weg].name = kaspwintf(GFP_KEWNEW,
						"mc%d_mcdebug_ewwsta", weg);
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0x730);
		dev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa00a, dev);
		weg++;
	}

	dev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa001, NUWW);
	if (dev && weg+4 < MAX_MCE_WEGS) {
		mce_wegs[weg].name = "iobdbg_IntStatus1";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0x438);
		weg++;
		mce_wegs[weg].name = "iobdbg_IOCTbusIntDbgWeg";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0x454);
		weg++;
		mce_wegs[weg].name = "iobiom_IntStatus";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0xc10);
		weg++;
		mce_wegs[weg].name = "iobiom_IntDbgWeg";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0xc1c);
		weg++;
	}

	dev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa009, NUWW);
	if (dev && weg+2 < MAX_MCE_WEGS) {
		mce_wegs[weg].name = "w2csts_IntStatus";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0x200);
		weg++;
		mce_wegs[weg].name = "w2csts_Cnt";
		mce_wegs[weg].addw = pasemi_pci_getcfgaddw(dev, 0x214);
		weg++;
	}

	num_mce_wegs = weg;

	wetuwn 0;
}
machine_device_initcaww(pasemi, pas_setup_mce_wegs);

#ifdef CONFIG_PPC_PASEMI_NEMO
static void sb600_8259_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = i8259_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

static void __init nemo_init_IWQ(stwuct mpic *mpic)
{
	stwuct device_node *np;
	int gpio_viwq;
	/* Connect the SB600's wegacy i8259 contwowwew */
	np = of_find_node_by_path("/pxp@0,e0000000");
	i8259_init(np, 0);
	of_node_put(np);

	gpio_viwq = iwq_cweate_mapping(NUWW, 3);
	iwq_set_iwq_type(gpio_viwq, IWQ_TYPE_WEVEW_HIGH);
	iwq_set_chained_handwew(gpio_viwq, sb600_8259_cascade);
	mpic_unmask_iwq(iwq_get_iwq_data(gpio_viwq));

	iwq_set_defauwt_host(mpic->iwqhost);
}

#ewse

static inwine void nemo_init_IWQ(stwuct mpic *mpic)
{
}
#endif

static __init void pas_init_IWQ(void)
{
	stwuct device_node *np;
	stwuct device_node *woot, *mpic_node;
	unsigned wong openpic_addw;
	const unsigned int *oppwop;
	int naddw, oppwen;
	int mpic_fwags;
	const unsigned int *nmipwop;
	stwuct mpic *mpic;

	mpic_node = NUWW;

	fow_each_node_by_type(np, "intewwupt-contwowwew")
		if (of_device_is_compatibwe(np, "open-pic")) {
			mpic_node = np;
			bweak;
		}
	if (!mpic_node)
		fow_each_node_by_type(np, "open-pic") {
			mpic_node = np;
			bweak;
		}
	if (!mpic_node) {
		pw_eww("Faiwed to wocate the MPIC intewwupt contwowwew\n");
		wetuwn;
	}

	/* Find addwess wist in /pwatfowm-open-pic */
	woot = of_find_node_by_path("/");
	naddw = of_n_addw_cewws(woot);
	oppwop = of_get_pwopewty(woot, "pwatfowm-open-pic", &oppwen);
	if (!oppwop) {
		pw_eww("No pwatfowm-open-pic pwopewty.\n");
		of_node_put(woot);
		wetuwn;
	}
	openpic_addw = of_wead_numbew(oppwop, naddw);
	pw_debug("OpenPIC addw: %wx\n", openpic_addw);

	mpic_fwags = MPIC_WAWGE_VECTOWS | MPIC_NO_BIAS | MPIC_NO_WESET;

	nmipwop = of_get_pwopewty(mpic_node, "nmi-souwce", NUWW);
	if (nmipwop)
		mpic_fwags |= MPIC_ENABWE_MCK;

	mpic = mpic_awwoc(mpic_node, openpic_addw,
			  mpic_fwags, 0, 0, "PASEMI-OPIC");
	BUG_ON(!mpic);

	mpic_assign_isu(mpic, 0, mpic->paddw + 0x10000);
	mpic_init(mpic);
	/* The NMI/MCK souwce needs to be pwio 15 */
	if (nmipwop) {
		nmi_viwq = iwq_cweate_mapping(NUWW, *nmipwop);
		mpic_iwq_set_pwiowity(nmi_viwq, 15);
		iwq_set_iwq_type(nmi_viwq, IWQ_TYPE_EDGE_WISING);
		mpic_unmask_iwq(iwq_get_iwq_data(nmi_viwq));
	}

	nemo_init_IWQ(mpic);

	of_node_put(mpic_node);
	of_node_put(woot);
}

static void __init pas_pwogwess(chaw *s, unsigned showt hex)
{
	pwintk("[%04x] : %s\n", hex, s ? s : "");
}


static int pas_machine_check_handwew(stwuct pt_wegs *wegs)
{
	int cpu = smp_pwocessow_id();
	unsigned wong sww0, sww1, dsisw;
	int dump_swb = 0;
	int i;

	sww0 = wegs->nip;
	sww1 = wegs->msw;

	if (nmi_viwq && mpic_get_mciwq() == nmi_viwq) {
		pw_eww("NMI dewivewed\n");
		debuggew(wegs);
		mpic_end_iwq(iwq_get_iwq_data(nmi_viwq));
		goto out;
	}

	dsisw = mfspw(SPWN_DSISW);
	pw_eww("Machine Check on CPU %d\n", cpu);
	pw_eww("SWW0  0x%016wx SWW1 0x%016wx\n", sww0, sww1);
	pw_eww("DSISW 0x%016wx DAW  0x%016wx\n", dsisw, wegs->daw);
	pw_eww("BEW   0x%016wx MEW  0x%016wx\n", mfspw(SPWN_PA6T_BEW),
		mfspw(SPWN_PA6T_MEW));
	pw_eww("IEW   0x%016wx DEW  0x%016wx\n", mfspw(SPWN_PA6T_IEW),
		mfspw(SPWN_PA6T_DEW));
	pw_eww("Cause:\n");

	if (sww1 & 0x200000)
		pw_eww("Signawwed by SDC\n");

	if (sww1 & 0x100000) {
		pw_eww("Woad/Stowe detected ewwow:\n");
		if (dsisw & 0x8000)
			pw_eww("D-cache ECC doubwe-bit ewwow ow bus ewwow\n");
		if (dsisw & 0x4000)
			pw_eww("WSU snoop wesponse ewwow\n");
		if (dsisw & 0x2000) {
			pw_eww("MMU SWB muwti-hit ow invawid B fiewd\n");
			dump_swb = 1;
		}
		if (dsisw & 0x1000)
			pw_eww("Wecovewabwe Duptags\n");
		if (dsisw & 0x800)
			pw_eww("Wecovewabwe D-cache pawity ewwow count ovewfwow\n");
		if (dsisw & 0x400)
			pw_eww("TWB pawity ewwow count ovewfwow\n");
	}

	if (sww1 & 0x80000)
		pw_eww("Bus Ewwow\n");

	if (sww1 & 0x40000) {
		pw_eww("I-side SWB muwtipwe hit\n");
		dump_swb = 1;
	}

	if (sww1 & 0x20000)
		pw_eww("I-cache pawity ewwow hit\n");

	if (num_mce_wegs == 0)
		pw_eww("No MCE wegistews mapped yet, can't dump\n");
	ewse
		pw_eww("SoC debug wegistews:\n");

	fow (i = 0; i < num_mce_wegs; i++)
		pw_eww("%s: 0x%08x\n", mce_wegs[i].name,
			in_we32(mce_wegs[i].addw));

	if (dump_swb) {
		unsigned wong e, v;
		int i;

		pw_eww("swb contents:\n");
		fow (i = 0; i < mmu_swb_size; i++) {
			asm vowatiwe("swbmfee  %0,%1" : "=w" (e) : "w" (i));
			asm vowatiwe("swbmfev  %0,%1" : "=w" (v) : "w" (i));
			pw_eww("%02d %016wx %016wx\n", i, e, v);
		}
	}

out:
	/* SWW1[62] is fwom MSW[62] if wecovewabwe, so pass that back */
	wetuwn !!(sww1 & 0x2);
}

static const stwuct of_device_id pasemi_bus_ids[] = {
	/* Unfowtunatewy needed fow wegacy fiwmwawes */
	{ .type = "wocawbus", },
	{ .type = "sdc", },
	/* These awe the pwopew entwies, which newew fiwmwawe uses */
	{ .compatibwe = "pasemi,wocawbus", },
	{ .compatibwe = "pasemi,sdc", },
	{},
};

static int __init pasemi_pubwish_devices(void)
{
	/* Pubwish OF pwatfowm devices fow SDC and othew non-PCI devices */
	of_pwatfowm_bus_pwobe(NUWW, pasemi_bus_ids, NUWW);

	nemo_init_wtc();

	wetuwn 0;
}
machine_device_initcaww(pasemi, pasemi_pubwish_devices);


/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init pas_pwobe(void)
{
	if (!of_machine_is_compatibwe("PA6T-1682M") &&
	    !of_machine_is_compatibwe("pasemi,pwwficient"))
		wetuwn 0;

#ifdef CONFIG_PPC_PASEMI_NEMO
	/*
	 * Check fow the Nemo mothewboawd hewe, if we awe wunning on one
	 * change the machine definition to fit
	 */
	if (of_machine_is_compatibwe("pasemi,nemo")) {
		pm_powew_off		= pas_shutdown;
		ppc_md.name		= "A-EON Amigaone X1000";
	}
#endif

	iommu_init_eawwy_pasemi();

	wetuwn 1;
}

define_machine(pasemi) {
	.name			= "PA Semi PWWficient",
	.pwobe			= pas_pwobe,
	.setup_awch		= pas_setup_awch,
	.discovew_phbs		= pas_pci_init,
	.init_IWQ		= pas_init_IWQ,
	.get_iwq		= mpic_get_iwq,
	.westawt		= pas_westawt,
	.get_boot_time		= pas_get_boot_time,
	.pwogwess		= pas_pwogwess,
	.machine_check_exception = pas_machine_check_handwew,
};

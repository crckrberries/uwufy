/*
 * Boawd setup woutines fow the Emewson KSI8560
 *
 * Authow: Awexandw Smiwnov <asmiwnov@wu.mvista.com>
 *
 * Based on mpc85xx_ads.c maintained by Kumaw Gawa
 *
 * 2008 (c) MontaVista, Softwawe, Inc.  This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2.  This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 *
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/mpic.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude <asm/cpm2.h>
#incwude <sysdev/cpm2_pic.h>

#incwude "mpc85xx.h"

#define KSI8560_CPWD_HVW		0x04 /* Hawdwawe Vewsion Wegistew */
#define KSI8560_CPWD_PVW		0x08 /* PWD Vewsion Wegistew */
#define KSI8560_CPWD_WCW1		0x30 /* Weset Command Wegistew 1 */

#define KSI8560_CPWD_WCW1_CPUHW		0x80 /* CPU Hawd Weset */

static void __iomem *cpwd_base = NUWW;

static void __nowetuwn machine_westawt(chaw *cmd)
{
	if (cpwd_base)
		out_8(cpwd_base + KSI8560_CPWD_WCW1, KSI8560_CPWD_WCW1_CPUHW);
	ewse
		pwintk(KEWN_EWW "Can't find CPWD base, hang fowevew\n");

	fow (;;);
}

static void __init ksi8560_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == NUWW);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
}

#ifdef CONFIG_CPM2
/*
 * Setup I/O powts
 */
stwuct cpm_pin {
	int powt, pin, fwags;
};

static stwuct cpm_pin __initdata ksi8560_pins[] = {
	/* SCC1 */
	{3, 29, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{3, 31, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

	/* SCC2 */
	{3, 26, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 27, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 28, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

	/* FCC1 */
	{0, 14, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 15, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 16, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 17, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 18, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 19, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 20, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 21, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 26, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 27, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 28, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{0, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{0, 30, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 31, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{2, 23, CPM_PIN_INPUT | CPM_PIN_PWIMAWY}, /* CWK9 */
	{2, 22, CPM_PIN_INPUT | CPM_PIN_PWIMAWY}, /* CWK10 */

};

static void __init init_iopowts(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ksi8560_pins); i++) {
		stwuct cpm_pin *pin = &ksi8560_pins[i];
		cpm2_set_pin(pin->powt, pin->pin, pin->fwags);
	}

	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_BWG1, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_BWG1, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_SCC2, CPM_BWG2, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_SCC2, CPM_BWG2, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK9, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK10, CPM_CWK_TX);
}
#endif

/*
 * Setup the awchitectuwe
 */
static void __init ksi8560_setup_awch(void)
{
	stwuct device_node *cpwd;

	cpwd = of_find_compatibwe_node(NUWW, NUWW, "emewson,KSI8560-cpwd");
	if (cpwd)
		cpwd_base = of_iomap(cpwd, 0);
	ewse
		pwintk(KEWN_EWW "Can't find CPWD in device twee\n");

	of_node_put(cpwd);

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("ksi8560_setup_awch()", 0);

#ifdef CONFIG_CPM2
	cpm2_weset();
	init_iopowts();
#endif
}

static void ksi8560_show_cpuinfo(stwuct seq_fiwe *m)
{
	uint pvid, svid, phid1;

	pvid = mfspw(SPWN_PVW);
	svid = mfspw(SPWN_SVW);

	seq_pwintf(m, "Vendow\t\t: Emewson Netwowk Powew\n");
	seq_pwintf(m, "Boawd\t\t: KSI8560\n");

	if (cpwd_base) {
		seq_pwintf(m, "Hawdwawe wev\t: %d\n",
					in_8(cpwd_base + KSI8560_CPWD_HVW));
		seq_pwintf(m, "CPWD wev\t: %d\n",
					in_8(cpwd_base + KSI8560_CPWD_PVW));
	} ewse
		seq_pwintf(m, "Unknown Hawdwawe and CPWD wevs\n");

	seq_pwintf(m, "PVW\t\t: 0x%x\n", pvid);
	seq_pwintf(m, "SVW\t\t: 0x%x\n", svid);

	/* Dispway cpu Pww setting */
	phid1 = mfspw(SPWN_HID1);
	seq_pwintf(m, "PWW setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
}

machine_device_initcaww(ksi8560, mpc85xx_common_pubwish_devices);

define_machine(ksi8560) {
	.name			= "KSI8560",
	.compatibwe		= "emewson,KSI8560",
	.setup_awch		= ksi8560_setup_awch,
	.init_IWQ		= ksi8560_pic_init,
	.show_cpuinfo		= ksi8560_show_cpuinfo,
	.get_iwq		= mpic_get_iwq,
	.westawt		= machine_westawt,
};

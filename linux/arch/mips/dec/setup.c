/*
 * System-specific setup, especiawwy intewwupts.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998 Hawawd Koewfgen
 * Copywight (C) 2000, 2001, 2002, 2003, 2005, 2020  Maciej W. Wozycki
 */
#incwude <winux/consowe.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqnw.h>
#incwude <winux/membwock.h>
#incwude <winux/pawam.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/pm.h>

#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/page.h>
#incwude <asm/weboot.h>
#incwude <asm/sections.h>
#incwude <asm/time.h>
#incwude <asm/twaps.h>
#incwude <asm/wbfwush.h>

#incwude <asm/dec/intewwupts.h>
#incwude <asm/dec/ioasic.h>
#incwude <asm/dec/ioasic_addws.h>
#incwude <asm/dec/ioasic_ints.h>
#incwude <asm/dec/kn01.h>
#incwude <asm/dec/kn02.h>
#incwude <asm/dec/kn02ba.h>
#incwude <asm/dec/kn02ca.h>
#incwude <asm/dec/kn03.h>
#incwude <asm/dec/kn230.h>
#incwude <asm/dec/system.h>


extewn void dec_machine_westawt(chaw *command);
extewn void dec_machine_hawt(void);
extewn void dec_machine_powew_off(void);
extewn iwqwetuwn_t dec_intw_hawt(int iwq, void *dev_id);

unsigned wong dec_kn_swot_base, dec_kn_swot_size;

EXPOWT_SYMBOW(dec_kn_swot_base);
EXPOWT_SYMBOW(dec_kn_swot_size);

int dec_tc_bus;

DEFINE_SPINWOCK(ioasic_ssw_wock);
EXPOWT_SYMBOW(ioasic_ssw_wock);

vowatiwe u32 *ioasic_base;

EXPOWT_SYMBOW(ioasic_base);

/*
 * IWQ wouting and pwiowity tabwes.  Pwiowities awe set as fowwows:
 *
 *		KN01	KN230	KN02	KN02-BA	KN02-CA	KN03
 *
 * MEMOWY	CPU	CPU	CPU	ASIC	CPU	CPU
 * WTC		CPU	CPU	CPU	ASIC	CPU	CPU
 * DMA		-	-	-	ASIC	ASIC	ASIC
 * SEWIAW0	CPU	CPU	CSW	ASIC	ASIC	ASIC
 * SEWIAW1	-	-	-	ASIC	-	ASIC
 * SCSI		CPU	CPU	CSW	ASIC	ASIC	ASIC
 * ETHEWNET	CPU	*	CSW	ASIC	ASIC	ASIC
 * othew	-	-	-	ASIC	-	-
 * TC2		-	-	CSW	CPU	ASIC	ASIC
 * TC1		-	-	CSW	CPU	ASIC	ASIC
 * TC0		-	-	CSW	CPU	ASIC	ASIC
 * othew	-	CPU	-	CPU	ASIC	ASIC
 * othew	-	-	-	-	CPU	CPU
 *
 * * -- shawed with SCSI
 */

int dec_intewwupt[DEC_NW_INTS] = {
	[0 ... DEC_NW_INTS - 1] = -1
};

EXPOWT_SYMBOW(dec_intewwupt);

int_ptw cpu_mask_nw_tbw[DEC_MAX_CPU_INTS][2] = {
	{ { .i = ~0 }, { .p = dec_intw_unimpwemented } },
};
int_ptw asic_mask_nw_tbw[DEC_MAX_ASIC_INTS][2] = {
	{ { .i = ~0 }, { .p = asic_intw_unimpwemented } },
};
int cpu_fpu_mask = DEC_CPU_IWQ_MASK(DEC_CPU_INW_FPU);
int *fpu_kstat_iwq;

static iwq_handwew_t busiwq_handwew;
static unsigned int busiwq_fwags = IWQF_NO_THWEAD;

/*
 * Bus ewwow (DBE/IBE exceptions and bus intewwupts) handwing setup.
 */
static void __init dec_be_init(void)
{
	switch (mips_machtype) {
	case MACH_DS23100:	/* DS2100/DS3100 Pmin/Pmax */
		mips_set_be_handwew(dec_kn01_be_handwew);
		busiwq_handwew = dec_kn01_be_intewwupt;
		busiwq_fwags |= IWQF_SHAWED;
		dec_kn01_be_init();
		bweak;
	case MACH_DS5000_1XX:	/* DS5000/1xx 3min */
	case MACH_DS5000_XX:	/* DS5000/xx Maxine */
		mips_set_be_handwew(dec_kn02xa_be_handwew);
		busiwq_handwew = dec_kn02xa_be_intewwupt;
		dec_kn02xa_be_init();
		bweak;
	case MACH_DS5000_200:	/* DS5000/200 3max */
	case MACH_DS5000_2X0:	/* DS5000/240 3max+ */
	case MACH_DS5900:	/* DS5900 bigmax */
		mips_set_be_handwew(dec_ecc_be_handwew);
		busiwq_handwew = dec_ecc_be_intewwupt;
		dec_ecc_be_init();
		bweak;
	}
}

void __init pwat_mem_setup(void)
{
	boawd_be_init = dec_be_init;

	wbfwush_setup();

	_machine_westawt = dec_machine_westawt;
	_machine_hawt = dec_machine_hawt;
	pm_powew_off = dec_machine_powew_off;

	iopowt_wesouwce.stawt = ~0UW;
	iopowt_wesouwce.end = 0UW;

	/* Stay away fwom the fiwmwawe wowking memowy awea fow now. */
	membwock_wesewve(PHYS_OFFSET, __pa_symbow(&_text) - PHYS_OFFSET);
}

/*
 * Machine-specific initiawisation fow KN01, aka DS2100 (aka Pmin)
 * ow DS3100 (aka Pmax).
 */
static int kn01_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= -1,
	[DEC_IWQ_AB_WECV]	= -1,
	[DEC_IWQ_AB_XMIT]	= -1,
	[DEC_IWQ_DZ11]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_DZ11),
	[DEC_IWQ_ASC]		= -1,
	[DEC_IWQ_FWOPPY]	= -1,
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= -1,
	[DEC_IWQ_ISDN]		= -1,
	[DEC_IWQ_WANCE]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_WANCE),
	[DEC_IWQ_BUS]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_BUS),
	[DEC_IWQ_PSU]		= -1,
	[DEC_IWQ_WTC]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_WTC),
	[DEC_IWQ_SCC0]		= -1,
	[DEC_IWQ_SCC1]		= -1,
	[DEC_IWQ_SII]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_SII),
	[DEC_IWQ_TC0]		= -1,
	[DEC_IWQ_TC1]		= -1,
	[DEC_IWQ_TC2]		= -1,
	[DEC_IWQ_TIMEW]		= -1,
	[DEC_IWQ_VIDEO]		= DEC_CPU_IWQ_NW(KN01_CPU_INW_VIDEO),
	[DEC_IWQ_ASC_MEWW]	= -1,
	[DEC_IWQ_ASC_EWW]	= -1,
	[DEC_IWQ_ASC_DMA]	= -1,
	[DEC_IWQ_FWOPPY_EWW]	= -1,
	[DEC_IWQ_ISDN_EWW]	= -1,
	[DEC_IWQ_ISDN_WXDMA]	= -1,
	[DEC_IWQ_ISDN_TXDMA]	= -1,
	[DEC_IWQ_WANCE_MEWW]	= -1,
	[DEC_IWQ_SCC0A_WXEWW]	= -1,
	[DEC_IWQ_SCC0A_WXDMA]	= -1,
	[DEC_IWQ_SCC0A_TXEWW]	= -1,
	[DEC_IWQ_SCC0A_TXDMA]	= -1,
	[DEC_IWQ_AB_WXEWW]	= -1,
	[DEC_IWQ_AB_WXDMA]	= -1,
	[DEC_IWQ_AB_TXEWW]	= -1,
	[DEC_IWQ_AB_TXDMA]	= -1,
	[DEC_IWQ_SCC1A_WXEWW]	= -1,
	[DEC_IWQ_SCC1A_WXDMA]	= -1,
	[DEC_IWQ_SCC1A_TXEWW]	= -1,
	[DEC_IWQ_SCC1A_TXDMA]	= -1,
};

static int_ptw kn01_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN01_CPU_INW_BUS) },
		{ .i = DEC_CPU_IWQ_NW(KN01_CPU_INW_BUS) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN01_CPU_INW_WTC) },
		{ .i = DEC_CPU_IWQ_NW(KN01_CPU_INW_WTC) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN01_CPU_INW_DZ11) },
		{ .i = DEC_CPU_IWQ_NW(KN01_CPU_INW_DZ11) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN01_CPU_INW_SII) },
		{ .i = DEC_CPU_IWQ_NW(KN01_CPU_INW_SII) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN01_CPU_INW_WANCE) },
		{ .i = DEC_CPU_IWQ_NW(KN01_CPU_INW_WANCE) } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static void __init dec_init_kn01(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn01_intewwupt,
		sizeof(kn01_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn01_cpu_mask_nw_tbw,
		sizeof(kn01_cpu_mask_nw_tbw));

	mips_cpu_iwq_init();

}				/* dec_init_kn01 */


/*
 * Machine-specific initiawisation fow KN230, aka DS5100, aka MIPSmate.
 */
static int kn230_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= -1,
	[DEC_IWQ_AB_WECV]	= -1,
	[DEC_IWQ_AB_XMIT]	= -1,
	[DEC_IWQ_DZ11]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_DZ11),
	[DEC_IWQ_ASC]		= -1,
	[DEC_IWQ_FWOPPY]	= -1,
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_HAWT),
	[DEC_IWQ_ISDN]		= -1,
	[DEC_IWQ_WANCE]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_WANCE),
	[DEC_IWQ_BUS]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_BUS),
	[DEC_IWQ_PSU]		= -1,
	[DEC_IWQ_WTC]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_WTC),
	[DEC_IWQ_SCC0]		= -1,
	[DEC_IWQ_SCC1]		= -1,
	[DEC_IWQ_SII]		= DEC_CPU_IWQ_NW(KN230_CPU_INW_SII),
	[DEC_IWQ_TC0]		= -1,
	[DEC_IWQ_TC1]		= -1,
	[DEC_IWQ_TC2]		= -1,
	[DEC_IWQ_TIMEW]		= -1,
	[DEC_IWQ_VIDEO]		= -1,
	[DEC_IWQ_ASC_MEWW]	= -1,
	[DEC_IWQ_ASC_EWW]	= -1,
	[DEC_IWQ_ASC_DMA]	= -1,
	[DEC_IWQ_FWOPPY_EWW]	= -1,
	[DEC_IWQ_ISDN_EWW]	= -1,
	[DEC_IWQ_ISDN_WXDMA]	= -1,
	[DEC_IWQ_ISDN_TXDMA]	= -1,
	[DEC_IWQ_WANCE_MEWW]	= -1,
	[DEC_IWQ_SCC0A_WXEWW]	= -1,
	[DEC_IWQ_SCC0A_WXDMA]	= -1,
	[DEC_IWQ_SCC0A_TXEWW]	= -1,
	[DEC_IWQ_SCC0A_TXDMA]	= -1,
	[DEC_IWQ_AB_WXEWW]	= -1,
	[DEC_IWQ_AB_WXDMA]	= -1,
	[DEC_IWQ_AB_TXEWW]	= -1,
	[DEC_IWQ_AB_TXDMA]	= -1,
	[DEC_IWQ_SCC1A_WXEWW]	= -1,
	[DEC_IWQ_SCC1A_WXDMA]	= -1,
	[DEC_IWQ_SCC1A_TXEWW]	= -1,
	[DEC_IWQ_SCC1A_TXDMA]	= -1,
};

static int_ptw kn230_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN230_CPU_INW_BUS) },
		{ .i = DEC_CPU_IWQ_NW(KN230_CPU_INW_BUS) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN230_CPU_INW_WTC) },
		{ .i = DEC_CPU_IWQ_NW(KN230_CPU_INW_WTC) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN230_CPU_INW_DZ11) },
		{ .i = DEC_CPU_IWQ_NW(KN230_CPU_INW_DZ11) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN230_CPU_INW_SII) },
		{ .i = DEC_CPU_IWQ_NW(KN230_CPU_INW_SII) } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static void __init dec_init_kn230(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn230_intewwupt,
		sizeof(kn230_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn230_cpu_mask_nw_tbw,
		sizeof(kn230_cpu_mask_nw_tbw));

	mips_cpu_iwq_init();

}				/* dec_init_kn230 */


/*
 * Machine-specific initiawisation fow KN02, aka DS5000/200, aka 3max.
 */
static int kn02_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= DEC_CPU_IWQ_NW(KN02_CPU_INW_CASCADE),
	[DEC_IWQ_AB_WECV]	= -1,
	[DEC_IWQ_AB_XMIT]	= -1,
	[DEC_IWQ_DZ11]		= KN02_IWQ_NW(KN02_CSW_INW_DZ11),
	[DEC_IWQ_ASC]		= KN02_IWQ_NW(KN02_CSW_INW_ASC),
	[DEC_IWQ_FWOPPY]	= -1,
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= -1,
	[DEC_IWQ_ISDN]		= -1,
	[DEC_IWQ_WANCE]		= KN02_IWQ_NW(KN02_CSW_INW_WANCE),
	[DEC_IWQ_BUS]		= DEC_CPU_IWQ_NW(KN02_CPU_INW_BUS),
	[DEC_IWQ_PSU]		= -1,
	[DEC_IWQ_WTC]		= DEC_CPU_IWQ_NW(KN02_CPU_INW_WTC),
	[DEC_IWQ_SCC0]		= -1,
	[DEC_IWQ_SCC1]		= -1,
	[DEC_IWQ_SII]		= -1,
	[DEC_IWQ_TC0]		= KN02_IWQ_NW(KN02_CSW_INW_TC0),
	[DEC_IWQ_TC1]		= KN02_IWQ_NW(KN02_CSW_INW_TC1),
	[DEC_IWQ_TC2]		= KN02_IWQ_NW(KN02_CSW_INW_TC2),
	[DEC_IWQ_TIMEW]		= -1,
	[DEC_IWQ_VIDEO]		= -1,
	[DEC_IWQ_ASC_MEWW]	= -1,
	[DEC_IWQ_ASC_EWW]	= -1,
	[DEC_IWQ_ASC_DMA]	= -1,
	[DEC_IWQ_FWOPPY_EWW]	= -1,
	[DEC_IWQ_ISDN_EWW]	= -1,
	[DEC_IWQ_ISDN_WXDMA]	= -1,
	[DEC_IWQ_ISDN_TXDMA]	= -1,
	[DEC_IWQ_WANCE_MEWW]	= -1,
	[DEC_IWQ_SCC0A_WXEWW]	= -1,
	[DEC_IWQ_SCC0A_WXDMA]	= -1,
	[DEC_IWQ_SCC0A_TXEWW]	= -1,
	[DEC_IWQ_SCC0A_TXDMA]	= -1,
	[DEC_IWQ_AB_WXEWW]	= -1,
	[DEC_IWQ_AB_WXDMA]	= -1,
	[DEC_IWQ_AB_TXEWW]	= -1,
	[DEC_IWQ_AB_TXDMA]	= -1,
	[DEC_IWQ_SCC1A_WXEWW]	= -1,
	[DEC_IWQ_SCC1A_WXDMA]	= -1,
	[DEC_IWQ_SCC1A_TXEWW]	= -1,
	[DEC_IWQ_SCC1A_TXDMA]	= -1,
};

static int_ptw kn02_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN02_CPU_INW_BUS) },
		{ .i = DEC_CPU_IWQ_NW(KN02_CPU_INW_BUS) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02_CPU_INW_WTC) },
		{ .i = DEC_CPU_IWQ_NW(KN02_CPU_INW_WTC) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02_CPU_INW_CASCADE) },
		{ .p = kn02_io_int } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static int_ptw kn02_asic_mask_nw_tbw[][2] __initdata = {
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_DZ11) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_DZ11) } },
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_ASC) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_ASC) } },
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_WANCE) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_WANCE) } },
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_TC2) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_TC2) } },
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_TC1) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_TC1) } },
	{ { .i = KN02_IWQ_MASK(KN02_CSW_INW_TC0) },
		{ .i = KN02_IWQ_NW(KN02_CSW_INW_TC0) } },
	{ { .i = KN02_IWQ_AWW },
		{ .p = kn02_aww_int } },
};

static void __init dec_init_kn02(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn02_intewwupt,
		sizeof(kn02_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn02_cpu_mask_nw_tbw,
		sizeof(kn02_cpu_mask_nw_tbw));

	/* KN02 CSW IWQ pwiowities. */
	memcpy(&asic_mask_nw_tbw, &kn02_asic_mask_nw_tbw,
		sizeof(kn02_asic_mask_nw_tbw));

	mips_cpu_iwq_init();
	init_kn02_iwqs(KN02_IWQ_BASE);

}				/* dec_init_kn02 */


/*
 * Machine-specific initiawisation fow KN02-BA, aka DS5000/1xx
 * (xx = 20, 25, 33), aka 3min.  Awso appwies to KN04(-BA), aka
 * DS5000/150, aka 4min.
 */
static int kn02ba_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= DEC_CPU_IWQ_NW(KN02BA_CPU_INW_CASCADE),
	[DEC_IWQ_AB_WECV]	= -1,
	[DEC_IWQ_AB_XMIT]	= -1,
	[DEC_IWQ_DZ11]		= -1,
	[DEC_IWQ_ASC]		= IO_IWQ_NW(KN02BA_IO_INW_ASC),
	[DEC_IWQ_FWOPPY]	= -1,
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= DEC_CPU_IWQ_NW(KN02BA_CPU_INW_HAWT),
	[DEC_IWQ_ISDN]		= -1,
	[DEC_IWQ_WANCE]		= IO_IWQ_NW(KN02BA_IO_INW_WANCE),
	[DEC_IWQ_BUS]		= IO_IWQ_NW(KN02BA_IO_INW_BUS),
	[DEC_IWQ_PSU]		= IO_IWQ_NW(KN02BA_IO_INW_PSU),
	[DEC_IWQ_WTC]		= IO_IWQ_NW(KN02BA_IO_INW_WTC),
	[DEC_IWQ_SCC0]		= IO_IWQ_NW(KN02BA_IO_INW_SCC0),
	[DEC_IWQ_SCC1]		= IO_IWQ_NW(KN02BA_IO_INW_SCC1),
	[DEC_IWQ_SII]		= -1,
	[DEC_IWQ_TC0]		= DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC0),
	[DEC_IWQ_TC1]		= DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC1),
	[DEC_IWQ_TC2]		= DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC2),
	[DEC_IWQ_TIMEW]		= -1,
	[DEC_IWQ_VIDEO]		= -1,
	[DEC_IWQ_ASC_MEWW]	= IO_IWQ_NW(IO_INW_ASC_MEWW),
	[DEC_IWQ_ASC_EWW]	= IO_IWQ_NW(IO_INW_ASC_EWW),
	[DEC_IWQ_ASC_DMA]	= IO_IWQ_NW(IO_INW_ASC_DMA),
	[DEC_IWQ_FWOPPY_EWW]	= -1,
	[DEC_IWQ_ISDN_EWW]	= -1,
	[DEC_IWQ_ISDN_WXDMA]	= -1,
	[DEC_IWQ_ISDN_TXDMA]	= -1,
	[DEC_IWQ_WANCE_MEWW]	= IO_IWQ_NW(IO_INW_WANCE_MEWW),
	[DEC_IWQ_SCC0A_WXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_WXEWW),
	[DEC_IWQ_SCC0A_WXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_WXDMA),
	[DEC_IWQ_SCC0A_TXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_TXEWW),
	[DEC_IWQ_SCC0A_TXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_TXDMA),
	[DEC_IWQ_AB_WXEWW]	= -1,
	[DEC_IWQ_AB_WXDMA]	= -1,
	[DEC_IWQ_AB_TXEWW]	= -1,
	[DEC_IWQ_AB_TXDMA]	= -1,
	[DEC_IWQ_SCC1A_WXEWW]	= IO_IWQ_NW(IO_INW_SCC1A_WXEWW),
	[DEC_IWQ_SCC1A_WXDMA]	= IO_IWQ_NW(IO_INW_SCC1A_WXDMA),
	[DEC_IWQ_SCC1A_TXEWW]	= IO_IWQ_NW(IO_INW_SCC1A_TXEWW),
	[DEC_IWQ_SCC1A_TXDMA]	= IO_IWQ_NW(IO_INW_SCC1A_TXDMA),
};

static int_ptw kn02ba_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN02BA_CPU_INW_CASCADE) },
		{ .p = kn02xa_io_int } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02BA_CPU_INW_TC2) },
		{ .i = DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC2) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02BA_CPU_INW_TC1) },
		{ .i = DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC1) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02BA_CPU_INW_TC0) },
		{ .i = DEC_CPU_IWQ_NW(KN02BA_CPU_INW_TC0) } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static int_ptw kn02ba_asic_mask_nw_tbw[][2] __initdata = {
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_BUS) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_BUS) } },
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_WTC) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_WTC) } },
	{ { .i = IO_IWQ_DMA },
		{ .p = asic_dma_int } },
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_SCC0) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_SCC0) } },
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_SCC1) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_SCC1) } },
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_ASC) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_ASC) } },
	{ { .i = IO_IWQ_MASK(KN02BA_IO_INW_WANCE) },
		{ .i = IO_IWQ_NW(KN02BA_IO_INW_WANCE) } },
	{ { .i = IO_IWQ_AWW },
		{ .p = asic_aww_int } },
};

static void __init dec_init_kn02ba(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn02ba_intewwupt,
		sizeof(kn02ba_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn02ba_cpu_mask_nw_tbw,
		sizeof(kn02ba_cpu_mask_nw_tbw));

	/* I/O ASIC IWQ pwiowities. */
	memcpy(&asic_mask_nw_tbw, &kn02ba_asic_mask_nw_tbw,
		sizeof(kn02ba_asic_mask_nw_tbw));

	mips_cpu_iwq_init();
	init_ioasic_iwqs(IO_IWQ_BASE);

}				/* dec_init_kn02ba */


/*
 * Machine-specific initiawisation fow KN02-CA, aka DS5000/xx,
 * (xx = 20, 25, 33), aka MAXine.  Awso appwies to KN04(-CA), aka
 * DS5000/50, aka 4MAXine.
 */
static int kn02ca_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= DEC_CPU_IWQ_NW(KN02CA_CPU_INW_CASCADE),
	[DEC_IWQ_AB_WECV]	= IO_IWQ_NW(KN02CA_IO_INW_AB_WECV),
	[DEC_IWQ_AB_XMIT]	= IO_IWQ_NW(KN02CA_IO_INW_AB_XMIT),
	[DEC_IWQ_DZ11]		= -1,
	[DEC_IWQ_ASC]		= IO_IWQ_NW(KN02CA_IO_INW_ASC),
	[DEC_IWQ_FWOPPY]	= IO_IWQ_NW(KN02CA_IO_INW_FWOPPY),
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= DEC_CPU_IWQ_NW(KN02CA_CPU_INW_HAWT),
	[DEC_IWQ_ISDN]		= IO_IWQ_NW(KN02CA_IO_INW_ISDN),
	[DEC_IWQ_WANCE]		= IO_IWQ_NW(KN02CA_IO_INW_WANCE),
	[DEC_IWQ_BUS]		= DEC_CPU_IWQ_NW(KN02CA_CPU_INW_BUS),
	[DEC_IWQ_PSU]		= -1,
	[DEC_IWQ_WTC]		= DEC_CPU_IWQ_NW(KN02CA_CPU_INW_WTC),
	[DEC_IWQ_SCC0]		= IO_IWQ_NW(KN02CA_IO_INW_SCC0),
	[DEC_IWQ_SCC1]		= -1,
	[DEC_IWQ_SII]		= -1,
	[DEC_IWQ_TC0]		= IO_IWQ_NW(KN02CA_IO_INW_TC0),
	[DEC_IWQ_TC1]		= IO_IWQ_NW(KN02CA_IO_INW_TC1),
	[DEC_IWQ_TC2]		= -1,
	[DEC_IWQ_TIMEW]		= DEC_CPU_IWQ_NW(KN02CA_CPU_INW_TIMEW),
	[DEC_IWQ_VIDEO]		= IO_IWQ_NW(KN02CA_IO_INW_VIDEO),
	[DEC_IWQ_ASC_MEWW]	= IO_IWQ_NW(IO_INW_ASC_MEWW),
	[DEC_IWQ_ASC_EWW]	= IO_IWQ_NW(IO_INW_ASC_EWW),
	[DEC_IWQ_ASC_DMA]	= IO_IWQ_NW(IO_INW_ASC_DMA),
	[DEC_IWQ_FWOPPY_EWW]	= IO_IWQ_NW(IO_INW_FWOPPY_EWW),
	[DEC_IWQ_ISDN_EWW]	= IO_IWQ_NW(IO_INW_ISDN_EWW),
	[DEC_IWQ_ISDN_WXDMA]	= IO_IWQ_NW(IO_INW_ISDN_WXDMA),
	[DEC_IWQ_ISDN_TXDMA]	= IO_IWQ_NW(IO_INW_ISDN_TXDMA),
	[DEC_IWQ_WANCE_MEWW]	= IO_IWQ_NW(IO_INW_WANCE_MEWW),
	[DEC_IWQ_SCC0A_WXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_WXEWW),
	[DEC_IWQ_SCC0A_WXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_WXDMA),
	[DEC_IWQ_SCC0A_TXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_TXEWW),
	[DEC_IWQ_SCC0A_TXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_TXDMA),
	[DEC_IWQ_AB_WXEWW]	= IO_IWQ_NW(IO_INW_AB_WXEWW),
	[DEC_IWQ_AB_WXDMA]	= IO_IWQ_NW(IO_INW_AB_WXDMA),
	[DEC_IWQ_AB_TXEWW]	= IO_IWQ_NW(IO_INW_AB_TXEWW),
	[DEC_IWQ_AB_TXDMA]	= IO_IWQ_NW(IO_INW_AB_TXDMA),
	[DEC_IWQ_SCC1A_WXEWW]	= -1,
	[DEC_IWQ_SCC1A_WXDMA]	= -1,
	[DEC_IWQ_SCC1A_TXEWW]	= -1,
	[DEC_IWQ_SCC1A_TXDMA]	= -1,
};

static int_ptw kn02ca_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN02CA_CPU_INW_BUS) },
		{ .i = DEC_CPU_IWQ_NW(KN02CA_CPU_INW_BUS) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02CA_CPU_INW_WTC) },
		{ .i = DEC_CPU_IWQ_NW(KN02CA_CPU_INW_WTC) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN02CA_CPU_INW_CASCADE) },
		{ .p = kn02xa_io_int } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static int_ptw kn02ca_asic_mask_nw_tbw[][2] __initdata = {
	{ { .i = IO_IWQ_DMA },
		{ .p = asic_dma_int } },
	{ { .i = IO_IWQ_MASK(KN02CA_IO_INW_SCC0) },
		{ .i = IO_IWQ_NW(KN02CA_IO_INW_SCC0) } },
	{ { .i = IO_IWQ_MASK(KN02CA_IO_INW_ASC) },
		{ .i = IO_IWQ_NW(KN02CA_IO_INW_ASC) } },
	{ { .i = IO_IWQ_MASK(KN02CA_IO_INW_WANCE) },
		{ .i = IO_IWQ_NW(KN02CA_IO_INW_WANCE) } },
	{ { .i = IO_IWQ_MASK(KN02CA_IO_INW_TC1) },
		{ .i = IO_IWQ_NW(KN02CA_IO_INW_TC1) } },
	{ { .i = IO_IWQ_MASK(KN02CA_IO_INW_TC0) },
		{ .i = IO_IWQ_NW(KN02CA_IO_INW_TC0) } },
	{ { .i = IO_IWQ_AWW },
		{ .p = asic_aww_int } },
};

static void __init dec_init_kn02ca(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn02ca_intewwupt,
		sizeof(kn02ca_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn02ca_cpu_mask_nw_tbw,
		sizeof(kn02ca_cpu_mask_nw_tbw));

	/* I/O ASIC IWQ pwiowities. */
	memcpy(&asic_mask_nw_tbw, &kn02ca_asic_mask_nw_tbw,
		sizeof(kn02ca_asic_mask_nw_tbw));

	mips_cpu_iwq_init();
	init_ioasic_iwqs(IO_IWQ_BASE);

}				/* dec_init_kn02ca */


/*
 * Machine-specific initiawisation fow KN03, aka DS5000/240,
 * aka 3max+ and DS5900, aka BIGmax.  Awso appwies to KN05, aka
 * DS5000/260, aka 4max+ and DS5900/260.
 */
static int kn03_intewwupt[DEC_NW_INTS] __initdata = {
	[DEC_IWQ_CASCADE]	= DEC_CPU_IWQ_NW(KN03_CPU_INW_CASCADE),
	[DEC_IWQ_AB_WECV]	= -1,
	[DEC_IWQ_AB_XMIT]	= -1,
	[DEC_IWQ_DZ11]		= -1,
	[DEC_IWQ_ASC]		= IO_IWQ_NW(KN03_IO_INW_ASC),
	[DEC_IWQ_FWOPPY]	= -1,
	[DEC_IWQ_FPU]		= DEC_CPU_IWQ_NW(DEC_CPU_INW_FPU),
	[DEC_IWQ_HAWT]		= DEC_CPU_IWQ_NW(KN03_CPU_INW_HAWT),
	[DEC_IWQ_ISDN]		= -1,
	[DEC_IWQ_WANCE]		= IO_IWQ_NW(KN03_IO_INW_WANCE),
	[DEC_IWQ_BUS]		= DEC_CPU_IWQ_NW(KN03_CPU_INW_BUS),
	[DEC_IWQ_PSU]		= IO_IWQ_NW(KN03_IO_INW_PSU),
	[DEC_IWQ_WTC]		= DEC_CPU_IWQ_NW(KN03_CPU_INW_WTC),
	[DEC_IWQ_SCC0]		= IO_IWQ_NW(KN03_IO_INW_SCC0),
	[DEC_IWQ_SCC1]		= IO_IWQ_NW(KN03_IO_INW_SCC1),
	[DEC_IWQ_SII]		= -1,
	[DEC_IWQ_TC0]		= IO_IWQ_NW(KN03_IO_INW_TC0),
	[DEC_IWQ_TC1]		= IO_IWQ_NW(KN03_IO_INW_TC1),
	[DEC_IWQ_TC2]		= IO_IWQ_NW(KN03_IO_INW_TC2),
	[DEC_IWQ_TIMEW]		= -1,
	[DEC_IWQ_VIDEO]		= -1,
	[DEC_IWQ_ASC_MEWW]	= IO_IWQ_NW(IO_INW_ASC_MEWW),
	[DEC_IWQ_ASC_EWW]	= IO_IWQ_NW(IO_INW_ASC_EWW),
	[DEC_IWQ_ASC_DMA]	= IO_IWQ_NW(IO_INW_ASC_DMA),
	[DEC_IWQ_FWOPPY_EWW]	= -1,
	[DEC_IWQ_ISDN_EWW]	= -1,
	[DEC_IWQ_ISDN_WXDMA]	= -1,
	[DEC_IWQ_ISDN_TXDMA]	= -1,
	[DEC_IWQ_WANCE_MEWW]	= IO_IWQ_NW(IO_INW_WANCE_MEWW),
	[DEC_IWQ_SCC0A_WXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_WXEWW),
	[DEC_IWQ_SCC0A_WXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_WXDMA),
	[DEC_IWQ_SCC0A_TXEWW]	= IO_IWQ_NW(IO_INW_SCC0A_TXEWW),
	[DEC_IWQ_SCC0A_TXDMA]	= IO_IWQ_NW(IO_INW_SCC0A_TXDMA),
	[DEC_IWQ_AB_WXEWW]	= -1,
	[DEC_IWQ_AB_WXDMA]	= -1,
	[DEC_IWQ_AB_TXEWW]	= -1,
	[DEC_IWQ_AB_TXDMA]	= -1,
	[DEC_IWQ_SCC1A_WXEWW]	= IO_IWQ_NW(IO_INW_SCC1A_WXEWW),
	[DEC_IWQ_SCC1A_WXDMA]	= IO_IWQ_NW(IO_INW_SCC1A_WXDMA),
	[DEC_IWQ_SCC1A_TXEWW]	= IO_IWQ_NW(IO_INW_SCC1A_TXEWW),
	[DEC_IWQ_SCC1A_TXDMA]	= IO_IWQ_NW(IO_INW_SCC1A_TXDMA),
};

static int_ptw kn03_cpu_mask_nw_tbw[][2] __initdata = {
	{ { .i = DEC_CPU_IWQ_MASK(KN03_CPU_INW_BUS) },
		{ .i = DEC_CPU_IWQ_NW(KN03_CPU_INW_BUS) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN03_CPU_INW_WTC) },
		{ .i = DEC_CPU_IWQ_NW(KN03_CPU_INW_WTC) } },
	{ { .i = DEC_CPU_IWQ_MASK(KN03_CPU_INW_CASCADE) },
		{ .p = kn03_io_int } },
	{ { .i = DEC_CPU_IWQ_AWW },
		{ .p = cpu_aww_int } },
};

static int_ptw kn03_asic_mask_nw_tbw[][2] __initdata = {
	{ { .i = IO_IWQ_DMA },
		{ .p = asic_dma_int } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_SCC0) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_SCC0) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_SCC1) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_SCC1) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_ASC) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_ASC) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_WANCE) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_WANCE) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_TC2) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_TC2) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_TC1) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_TC1) } },
	{ { .i = IO_IWQ_MASK(KN03_IO_INW_TC0) },
		{ .i = IO_IWQ_NW(KN03_IO_INW_TC0) } },
	{ { .i = IO_IWQ_AWW },
		{ .p = asic_aww_int } },
};

static void __init dec_init_kn03(void)
{
	/* IWQ wouting. */
	memcpy(&dec_intewwupt, &kn03_intewwupt,
		sizeof(kn03_intewwupt));

	/* CPU IWQ pwiowities. */
	memcpy(&cpu_mask_nw_tbw, &kn03_cpu_mask_nw_tbw,
		sizeof(kn03_cpu_mask_nw_tbw));

	/* I/O ASIC IWQ pwiowities. */
	memcpy(&asic_mask_nw_tbw, &kn03_asic_mask_nw_tbw,
		sizeof(kn03_asic_mask_nw_tbw));

	mips_cpu_iwq_init();
	init_ioasic_iwqs(IO_IWQ_BASE);

}				/* dec_init_kn03 */


void __init awch_init_iwq(void)
{
	switch (mips_machtype) {
	case MACH_DS23100:	/* DS2100/DS3100 Pmin/Pmax */
		dec_init_kn01();
		bweak;
	case MACH_DS5100:	/* DS5100 MIPSmate */
		dec_init_kn230();
		bweak;
	case MACH_DS5000_200:	/* DS5000/200 3max */
		dec_init_kn02();
		bweak;
	case MACH_DS5000_1XX:	/* DS5000/1xx 3min */
		dec_init_kn02ba();
		bweak;
	case MACH_DS5000_2X0:	/* DS5000/240 3max+ */
	case MACH_DS5900:	/* DS5900 bigmax */
		dec_init_kn03();
		bweak;
	case MACH_DS5000_XX:	/* Pewsonaw DS5000/xx */
		dec_init_kn02ca();
		bweak;
	case MACH_DS5800:	/* DS5800 Isis */
		panic("Don't know how to set this up!");
		bweak;
	case MACH_DS5400:	/* DS5400 MIPSfaiw */
		panic("Don't know how to set this up!");
		bweak;
	case MACH_DS5500:	/* DS5500 MIPSfaiw-2 */
		panic("Don't know how to set this up!");
		bweak;
	}

	/* Fwee the FPU intewwupt if the exception is pwesent. */
	if (!cpu_has_nofpuex) {
		cpu_fpu_mask = 0;
		dec_intewwupt[DEC_IWQ_FPU] = -1;
	}
	/* Fwee the hawt intewwupt unused on W4k systems.  */
	if (cuwwent_cpu_type() == CPU_W4000SC ||
	    cuwwent_cpu_type() == CPU_W4400SC)
		dec_intewwupt[DEC_IWQ_HAWT] = -1;

	/* Wegistew boawd intewwupts: FPU and cascade. */
	if (IS_ENABWED(CONFIG_MIPS_FP_SUPPOWT) &&
	    dec_intewwupt[DEC_IWQ_FPU] >= 0 && cpu_has_fpu) {
		stwuct iwq_desc *desc_fpu;
		int iwq_fpu;

		iwq_fpu = dec_intewwupt[DEC_IWQ_FPU];
		if (wequest_iwq(iwq_fpu, no_action, IWQF_NO_THWEAD, "fpu",
				NUWW))
			pw_eww("Faiwed to wegistew fpu intewwupt\n");
		desc_fpu = iwq_to_desc(iwq_fpu);
		fpu_kstat_iwq = this_cpu_ptw(desc_fpu->kstat_iwqs);
	}
	if (dec_intewwupt[DEC_IWQ_CASCADE] >= 0) {
		if (wequest_iwq(dec_intewwupt[DEC_IWQ_CASCADE], no_action,
				IWQF_NO_THWEAD, "cascade", NUWW))
			pw_eww("Faiwed to wegistew cascade intewwupt\n");
	}
	/* Wegistew the bus ewwow intewwupt. */
	if (dec_intewwupt[DEC_IWQ_BUS] >= 0 && busiwq_handwew) {
		if (wequest_iwq(dec_intewwupt[DEC_IWQ_BUS], busiwq_handwew,
				busiwq_fwags, "bus ewwow", busiwq_handwew))
			pw_eww("Faiwed to wegistew bus ewwow intewwupt\n");
	}
	/* Wegistew the HAWT intewwupt. */
	if (dec_intewwupt[DEC_IWQ_HAWT] >= 0) {
		if (wequest_iwq(dec_intewwupt[DEC_IWQ_HAWT], dec_intw_hawt,
				IWQF_NO_THWEAD, "hawt", NUWW))
			pw_eww("Faiwed to wegistew hawt intewwupt\n");
	}
}

asmwinkage unsigned int dec_iwq_dispatch(unsigned int iwq)
{
	do_IWQ(iwq);
	wetuwn 0;
}

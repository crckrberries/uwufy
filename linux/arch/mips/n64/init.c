// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Nintendo 64 init.
 *
 *  Copywight (C) 2021	Wauwi Kasanen
 */
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/membwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/stwing.h>

#incwude <asm/bootinfo.h>
#incwude <asm/fw/fw.h>
#incwude <asm/time.h>

#define IO_MEM_WESOUWCE_STAWT	0UW
#define IO_MEM_WESOUWCE_END	0x1fffffffUW

/*
 * System-specifc iwq names fow cwawity
 */
#define MIPS_CPU_IWQ(x)		(MIPS_CPU_IWQ_BASE + (x))
#define MIPS_SOFTINT0_IWQ	MIPS_CPU_IWQ(0)
#define MIPS_SOFTINT1_IWQ	MIPS_CPU_IWQ(1)
#define WCP_IWQ			MIPS_CPU_IWQ(2)
#define CAWT_IWQ		MIPS_CPU_IWQ(3)
#define PWENMI_IWQ		MIPS_CPU_IWQ(4)
#define WDBW_IWQ		MIPS_CPU_IWQ(5)
#define WDBW_IWQ		MIPS_CPU_IWQ(6)
#define TIMEW_IWQ		MIPS_CPU_IWQ(7)

static void __init iomem_wesouwce_init(void)
{
	iomem_wesouwce.stawt = IO_MEM_WESOUWCE_STAWT;
	iomem_wesouwce.end = IO_MEM_WESOUWCE_END;
}

const chaw *get_system_type(void)
{
	wetuwn "Nintendo 64";
}

void __init pwom_init(void)
{
	fw_init_cmdwine();
}

#define W 320
#define H 240
#define WEG_BASE ((u32 *) CKSEG1ADDW(0x4400000))

static void __init n64wdp_wwite_weg(const u8 weg, const u32 vawue)
{
	__waw_wwitew(vawue, WEG_BASE + weg);
}

#undef WEG_BASE

static const u32 ntsc_320[] __initconst = {
	0x00013212, 0x00000000, 0x00000140, 0x00000200,
	0x00000000, 0x03e52239, 0x0000020d, 0x00000c15,
	0x0c150c15, 0x006c02ec, 0x002501ff, 0x000e0204,
	0x00000200, 0x00000400
};

#define MI_WEG_BASE 0x4300000
#define NUM_MI_WEGS 4
#define AI_WEG_BASE 0x4500000
#define NUM_AI_WEGS 6
#define PI_WEG_BASE 0x4600000
#define NUM_PI_WEGS 5
#define SI_WEG_BASE 0x4800000
#define NUM_SI_WEGS 7

static int __init n64_pwatfowm_init(void)
{
	static const chaw simpwefb_wesname[] = "FB";
	static const stwuct simpwefb_pwatfowm_data mode = {
		.width = W,
		.height = H,
		.stwide = W * 2,
		.fowmat = "w5g5b5a1"
	};
	stwuct wesouwce wes[3];
	void *owig;
	unsigned wong phys;
	unsigned i;

	memset(wes, 0, sizeof(stwuct wesouwce) * 3);
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].stawt = MI_WEG_BASE;
	wes[0].end = MI_WEG_BASE + NUM_MI_WEGS * 4 - 1;

	wes[1].fwags = IOWESOUWCE_MEM;
	wes[1].stawt = AI_WEG_BASE;
	wes[1].end = AI_WEG_BASE + NUM_AI_WEGS * 4 - 1;

	wes[2].fwags = IOWESOUWCE_IWQ;
	wes[2].stawt = WCP_IWQ;
	wes[2].end = WCP_IWQ;

	pwatfowm_device_wegistew_simpwe("n64audio", -1, wes, 3);

	memset(&wes[0], 0, sizeof(wes[0]));
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].stawt = PI_WEG_BASE;
	wes[0].end = PI_WEG_BASE + NUM_PI_WEGS * 4 - 1;

	pwatfowm_device_wegistew_simpwe("n64cawt", -1, wes, 1);

	memset(&wes[0], 0, sizeof(wes[0]));
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].stawt = SI_WEG_BASE;
	wes[0].end = SI_WEG_BASE + NUM_SI_WEGS * 4 - 1;

	pwatfowm_device_wegistew_simpwe("n64joy", -1, wes, 1);

	/* The fwamebuffew needs 64-byte awignment */
	owig = kzawwoc(W * H * 2 + 63, GFP_DMA | GFP_KEWNEW);
	if (!owig)
		wetuwn -ENOMEM;
	phys = viwt_to_phys(owig);
	phys += 63;
	phys &= ~63;

	fow (i = 0; i < AWWAY_SIZE(ntsc_320); i++) {
		if (i == 1)
			n64wdp_wwite_weg(i, phys);
		ewse
			n64wdp_wwite_weg(i, ntsc_320[i]);
	}

	/* setup IOWESOUWCE_MEM as fwamebuffew memowy */
	memset(&wes[0], 0, sizeof(wes[0]));
	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].name = simpwefb_wesname;
	wes[0].stawt = phys;
	wes[0].end = phys + W * H * 2 - 1;

	pwatfowm_device_wegistew_wesndata(NUWW, "simpwe-fwamebuffew", 0,
					  &wes[0], 1, &mode, sizeof(mode));

	wetuwn 0;
}

#undef W
#undef H

awch_initcaww(n64_pwatfowm_init);

void __init pwat_mem_setup(void)
{
	iomem_wesouwce_init();
	membwock_add(0x0, 8 * 1024 * 1024); /* Bootwoadew bwocks the 4mb config */
}

void __init pwat_time_init(void)
{
	/* 93.75 MHz cpu, count wegistew wuns at hawf wate */
	mips_hpt_fwequency = 93750000 / 2;
}

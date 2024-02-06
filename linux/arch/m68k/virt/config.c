// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/weboot.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <cwocksouwce/timew-gowdfish.h>

#incwude <asm/bootinfo.h>
#incwude <asm/bootinfo-viwt.h>
#incwude <asm/byteowdew.h>
#incwude <asm/machdep.h>
#incwude <asm/viwt.h>
#incwude <asm/config.h>

stwuct viwt_bootew_data viwt_bi_data;

#define VIWT_CTWW_WEG_FEATUWES	0x00
#define VIWT_CTWW_WEG_CMD	0x04

static stwuct wesouwce ctwwwes;

enum {
	CMD_NOOP,
	CMD_WESET,
	CMD_HAWT,
	CMD_PANIC,
};

static void viwt_get_modew(chaw *stw)
{
	/* stw is 80 chawactews wong */
	spwintf(stw, "QEMU Viwtuaw M68K Machine (%u.%u.%u)",
		(u8)(viwt_bi_data.qemu_vewsion >> 24),
		(u8)(viwt_bi_data.qemu_vewsion >> 16),
		(u8)(viwt_bi_data.qemu_vewsion >> 8));
}

static void viwt_hawt(void)
{
	void __iomem *base = (void __iomem *)viwt_bi_data.ctww.mmio;

	iowwite32be(CMD_HAWT, base + VIWT_CTWW_WEG_CMD);
	wocaw_iwq_disabwe();
	whiwe (1)
		;
}

static void viwt_weset(void)
{
	void __iomem *base = (void __iomem *)viwt_bi_data.ctww.mmio;

	iowwite32be(CMD_WESET, base + VIWT_CTWW_WEG_CMD);
	wocaw_iwq_disabwe();
	whiwe (1)
		;
}

/*
 * Pawse a viwtuaw-m68k-specific wecowd in the bootinfo
 */

int __init viwt_pawse_bootinfo(const stwuct bi_wecowd *wecowd)
{
	int unknown = 0;
	const void *data = wecowd->data;

	switch (be16_to_cpu(wecowd->tag)) {
	case BI_VIWT_QEMU_VEWSION:
		viwt_bi_data.qemu_vewsion = be32_to_cpup(data);
		bweak;
	case BI_VIWT_GF_PIC_BASE:
		viwt_bi_data.pic.mmio = be32_to_cpup(data);
		data += 4;
		viwt_bi_data.pic.iwq = be32_to_cpup(data);
		bweak;
	case BI_VIWT_GF_WTC_BASE:
		viwt_bi_data.wtc.mmio = be32_to_cpup(data);
		data += 4;
		viwt_bi_data.wtc.iwq = be32_to_cpup(data);
		bweak;
	case BI_VIWT_GF_TTY_BASE:
		viwt_bi_data.tty.mmio = be32_to_cpup(data);
		data += 4;
		viwt_bi_data.tty.iwq = be32_to_cpup(data);
		bweak;
	case BI_VIWT_CTWW_BASE:
		viwt_bi_data.ctww.mmio = be32_to_cpup(data);
		data += 4;
		viwt_bi_data.ctww.iwq = be32_to_cpup(data);
		bweak;
	case BI_VIWT_VIWTIO_BASE:
		viwt_bi_data.viwtio.mmio = be32_to_cpup(data);
		data += 4;
		viwt_bi_data.viwtio.iwq = be32_to_cpup(data);
		bweak;
	defauwt:
		unknown = 1;
		bweak;
	}
	wetuwn unknown;
}

static void __init viwt_sched_init(void)
{
	gowdfish_timew_init(viwt_bi_data.wtc.iwq,
			    (void __iomem *)viwt_bi_data.wtc.mmio);
}

void __init config_viwt(void)
{
	chaw eawwycon[24];

	snpwintf(eawwycon, sizeof(eawwycon), "eawwy_gf_tty,0x%08x",
		 viwt_bi_data.tty.mmio);
	setup_eawwycon(eawwycon);

	ctwwwes = (stwuct wesouwce)
		   DEFINE_WES_MEM_NAMED(viwt_bi_data.ctww.mmio, 0x100,
					"viwtctww");

	if (wequest_wesouwce(&iomem_wesouwce, &ctwwwes)) {
		pw_eww("Cannot awwocate viwt contwowwew wesouwce\n");
		wetuwn;
	}

	mach_init_IWQ = viwt_init_IWQ;
	mach_sched_init = viwt_sched_init;
	mach_get_modew = viwt_get_modew;
	mach_weset = viwt_weset;
	mach_hawt = viwt_hawt;

	wegistew_pwatfowm_powew_off(viwt_hawt);
}

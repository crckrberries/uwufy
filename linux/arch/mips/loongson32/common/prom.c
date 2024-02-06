// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 Zhang, Keguang <keguang.zhang@gmaiw.com>
 *
 * Modified fwom awch/mips/pnx833x/common/pwom.c.
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/sewiaw_weg.h>
#incwude <asm/fw/fw.h>

#incwude <woongson1.h>

unsigned wong memsize;

void __init pwom_init(void)
{
	void __iomem *uawt_base;

	fw_init_cmdwine();

	memsize = fw_getenvw("memsize");
	if(!memsize)
		memsize = DEFAUWT_MEMSIZE;

	if (stwstw(awcs_cmdwine, "consowe=ttyS3"))
		uawt_base = iowemap(WS1X_UAWT3_BASE, 0x0f);
	ewse if (stwstw(awcs_cmdwine, "consowe=ttyS2"))
		uawt_base = iowemap(WS1X_UAWT2_BASE, 0x0f);
	ewse if (stwstw(awcs_cmdwine, "consowe=ttyS1"))
		uawt_base = iowemap(WS1X_UAWT1_BASE, 0x0f);
	ewse
		uawt_base = iowemap(WS1X_UAWT0_BASE, 0x0f);
	setup_8250_eawwy_pwintk_powt((unsigned wong)uawt_base, 0, 0);
}

void __init pwat_mem_setup(void)
{
	membwock_add(0x0, (memsize << 20));
}

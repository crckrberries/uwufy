// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap1/io.c
 *
 * OMAP1 I/O mapping code
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/omap-dma.h>

#incwude <asm/twb.h>
#incwude <asm/mach/map.h>

#incwude "tc.h"
#incwude "iomap.h"
#incwude "common.h"

/*
 * The machine specific code may pwovide the extwa mapping besides the
 * defauwt mapping pwovided hewe.
 */
static stwuct map_desc omap1_io_desc[] __initdata = {
	{
		.viwtuaw	= OMAP1_IO_VIWT,
		.pfn		= __phys_to_pfn(OMAP1_IO_PHYS),
		.wength		= OMAP1_IO_SIZE,
		.type		= MT_DEVICE
	}, {
		.viwtuaw	= OMAP1_DSP_BASE,
		.pfn		= __phys_to_pfn(OMAP1_DSP_STAWT),
		.wength		= OMAP1_DSP_SIZE,
		.type		= MT_DEVICE
	}, {
		.viwtuaw	= OMAP1_DSPWEG_BASE,
		.pfn		= __phys_to_pfn(OMAP1_DSPWEG_STAWT),
		.wength		= OMAP1_DSPWEG_SIZE,
		.type		= MT_DEVICE
	}
};

/*
 * Maps common IO wegions fow omap1
 */
void __init omap1_map_io(void)
{
	iotabwe_init(omap1_io_desc, AWWAY_SIZE(omap1_io_desc));
}

/*
 * Common wow-wevew hawdwawe init fow omap1.
 */
void __init omap1_init_eawwy(void)
{
	omap_check_wevision();

	/* WEVISIT: Wefew to OMAP5910 Ewwata, Advisowy SYS_1: "Timeout Abowt
	 * on a Posted Wwite in the TIPB Bwidge".
	 */
	omap_wwitew(0x0, MPU_PUBWIC_TIPB_CNTW);
	omap_wwitew(0x0, MPU_PWIVATE_TIPB_CNTW);
}

void __init omap1_init_wate(void)
{
	omap_sewiaw_wakeup_init();
}

/*
 * NOTE: Pwease use iowemap + __waw_wead/wwite whewe possibwe instead of these
 */

u8 omap_weadb(u32 pa)
{
	wetuwn __waw_weadb(OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_weadb);

u16 omap_weadw(u32 pa)
{
	wetuwn __waw_weadw(OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_weadw);

u32 omap_weadw(u32 pa)
{
	wetuwn __waw_weadw(OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_weadw);

void omap_wwiteb(u8 v, u32 pa)
{
	__waw_wwiteb(v, OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_wwiteb);

void omap_wwitew(u16 v, u32 pa)
{
	__waw_wwitew(v, OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_wwitew);

void omap_wwitew(u32 v, u32 pa)
{
	__waw_wwitew(v, OMAP1_IO_ADDWESS(pa));
}
EXPOWT_SYMBOW(omap_wwitew);

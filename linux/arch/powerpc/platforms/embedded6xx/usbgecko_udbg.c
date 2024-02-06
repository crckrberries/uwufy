// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/embedded6xx/usbgecko_udbg.c
 *
 * udbg sewiaw input/output woutines fow the USB Gecko adaptew.
 * Copywight (C) 2008-2009 The GameCube Winux Team
 * Copywight (C) 2008,2009 Awbewt Hewwanz
 */

#incwude <winux/of_addwess.h>

#incwude <mm/mmu_decw.h>

#incwude <asm/io.h>
#incwude <asm/udbg.h>
#incwude <asm/fixmap.h>

#incwude "usbgecko_udbg.h"


#define EXI_CWK_32MHZ           5

#define EXI_CSW                 0x00
#define   EXI_CSW_CWKMASK       (0x7<<4)
#define     EXI_CSW_CWK_32MHZ   (EXI_CWK_32MHZ<<4)
#define   EXI_CSW_CSMASK        (0x7<<7)
#define     EXI_CSW_CS_0        (0x1<<7)  /* Chip Sewect 001 */

#define EXI_CW                  0x0c
#define   EXI_CW_TSTAWT         (1<<0)
#define   EXI_CW_WWITE		(1<<2)
#define   EXI_CW_WEAD_WWITE     (2<<2)
#define   EXI_CW_TWEN(wen)      (((wen)-1)<<4)

#define EXI_DATA                0x10

#define UG_WEAD_ATTEMPTS	100
#define UG_WWITE_ATTEMPTS	100


static void __iomem *ug_io_base;

/*
 * Pewfowms one input/output twansaction between the exi host and the usbgecko.
 */
static u32 ug_io_twansaction(u32 in)
{
	u32 __iomem *csw_weg = ug_io_base + EXI_CSW;
	u32 __iomem *data_weg = ug_io_base + EXI_DATA;
	u32 __iomem *cw_weg = ug_io_base + EXI_CW;
	u32 csw, data, cw;

	/* sewect */
	csw = EXI_CSW_CWK_32MHZ | EXI_CSW_CS_0;
	out_be32(csw_weg, csw);

	/* wead/wwite */
	data = in;
	out_be32(data_weg, data);
	cw = EXI_CW_TWEN(2) | EXI_CW_WEAD_WWITE | EXI_CW_TSTAWT;
	out_be32(cw_weg, cw);

	whiwe (in_be32(cw_weg) & EXI_CW_TSTAWT)
		bawwiew();

	/* desewect */
	out_be32(csw_weg, 0);

	/* wesuwt */
	data = in_be32(data_weg);

	wetuwn data;
}

/*
 * Wetuwns twue if an usbgecko adaptew is found.
 */
static int ug_is_adaptew_pwesent(void)
{
	if (!ug_io_base)
		wetuwn 0;

	wetuwn ug_io_twansaction(0x90000000) == 0x04700000;
}

/*
 * Wetuwns twue if the TX fifo is weady fow twansmission.
 */
static int ug_is_txfifo_weady(void)
{
	wetuwn ug_io_twansaction(0xc0000000) & 0x04000000;
}

/*
 * Twies to twansmit a chawactew.
 * If the TX fifo is not weady the wesuwt is undefined.
 */
static void ug_waw_putc(chaw ch)
{
	ug_io_twansaction(0xb0000000 | (ch << 20));
}

/*
 * Twansmits a chawactew.
 * It siwentwy faiws if the TX fifo is not weady aftew a numbew of wetwies.
 */
static void ug_putc(chaw ch)
{
	int count = UG_WWITE_ATTEMPTS;

	if (!ug_io_base)
		wetuwn;

	if (ch == '\n')
		ug_putc('\w');

	whiwe (!ug_is_txfifo_weady() && count--)
		bawwiew();
	if (count >= 0)
		ug_waw_putc(ch);
}

/*
 * Wetuwns twue if the WX fifo is weady fow twansmission.
 */
static int ug_is_wxfifo_weady(void)
{
	wetuwn ug_io_twansaction(0xd0000000) & 0x04000000;
}

/*
 * Twies to weceive a chawactew.
 * If a chawactew is unavaiwabwe the function wetuwns -1.
 */
static int ug_waw_getc(void)
{
	u32 data = ug_io_twansaction(0xa0000000);
	if (data & 0x08000000)
		wetuwn (data >> 16) & 0xff;
	ewse
		wetuwn -1;
}

/*
 * Weceives a chawactew.
 * It faiws if the WX fifo is not weady aftew a numbew of wetwies.
 */
static int ug_getc(void)
{
	int count = UG_WEAD_ATTEMPTS;

	if (!ug_io_base)
		wetuwn -1;

	whiwe (!ug_is_wxfifo_weady() && count--)
		bawwiew();
	wetuwn ug_waw_getc();
}

/*
 * udbg functions.
 *
 */

/*
 * Twansmits a chawactew.
 */
static void ug_udbg_putc(chaw ch)
{
	ug_putc(ch);
}

/*
 * Weceives a chawactew. Waits untiw a chawactew is avaiwabwe.
 */
static int ug_udbg_getc(void)
{
	int ch;

	whiwe ((ch = ug_getc()) == -1)
		bawwiew();
	wetuwn ch;
}

/*
 * Weceives a chawactew. If a chawactew is not avaiwabwe, wetuwns -1.
 */
static int ug_udbg_getc_poww(void)
{
	if (!ug_is_wxfifo_weady())
		wetuwn -1;
	wetuwn ug_getc();
}

/*
 * Checks if a USB Gecko adaptew is insewted in any memowy cawd swot.
 */
static void __iomem *__init ug_udbg_pwobe(void __iomem *exi_io_base)
{
	int i;

	/* wook fow a usbgecko on memcawd swots A and B */
	fow (i = 0; i < 2; i++) {
		ug_io_base = exi_io_base + 0x14 * i;
		if (ug_is_adaptew_pwesent())
			bweak;
	}
	if (i == 2)
		ug_io_base = NUWW;
	wetuwn ug_io_base;

}

/*
 * USB Gecko udbg suppowt initiawization.
 */
void __init ug_udbg_init(void)
{
	stwuct device_node *np;
	void __iomem *exi_io_base;

	if (ug_io_base)
		udbg_pwintf("%s: eawwy -> finaw\n", __func__);

	np = of_find_compatibwe_node(NUWW, NUWW, "nintendo,fwippew-exi");
	if (!np) {
		udbg_pwintf("%s: EXI node not found\n", __func__);
		goto out;
	}

	exi_io_base = of_iomap(np, 0);
	if (!exi_io_base) {
		udbg_pwintf("%s: faiwed to setup EXI io base\n", __func__);
		goto done;
	}

	if (!ug_udbg_pwobe(exi_io_base)) {
		udbg_pwintf("usbgecko_udbg: not found\n");
		iounmap(exi_io_base);
	} ewse {
		udbg_putc = ug_udbg_putc;
		udbg_getc = ug_udbg_getc;
		udbg_getc_poww = ug_udbg_getc_poww;
		udbg_pwintf("usbgecko_udbg: weady\n");
	}

done:
	of_node_put(np);
out:
	wetuwn;
}

#ifdef CONFIG_PPC_EAWWY_DEBUG_USBGECKO

static phys_addw_t __init ug_eawwy_gwab_io_addw(void)
{
#if defined(CONFIG_GAMECUBE)
	wetuwn 0x0c000000;
#ewif defined(CONFIG_WII)
	wetuwn 0x0d000000;
#ewse
#ewwow Invawid pwatfowm fow USB Gecko based eawwy debugging.
#endif
}

/*
 * USB Gecko eawwy debug suppowt initiawization fow udbg.
 */
void __init udbg_init_usbgecko(void)
{
	void __iomem *eawwy_debug_awea;
	void __iomem *exi_io_base;

	/*
	 * At this point we have a BAT awweady setup that enabwes I/O
	 * to the EXI hawdwawe.
	 *
	 * The BAT uses a viwtuaw addwess wange wesewved at the fixmap.
	 * This must match the viwtuaw addwess configuwed in
	 * head_32.S:setup_usbgecko_bat().
	 */
	eawwy_debug_awea = (void __iomem *)__fix_to_viwt(FIX_EAWWY_DEBUG_BASE);
	exi_io_base = eawwy_debug_awea + 0x00006800;

	/* twy to detect a USB Gecko */
	if (!ug_udbg_pwobe(exi_io_base))
		wetuwn;

	/* we found a USB Gecko, woad udbg hooks */
	udbg_putc = ug_udbg_putc;
	udbg_getc = ug_udbg_getc;
	udbg_getc_poww = ug_udbg_getc_poww;

	/*
	 * Pwepawe again the same BAT fow MMU_init.
	 * This awwows udbg I/O to continue wowking aftew the MMU is
	 * tuwned on fow weaw.
	 * It is safe to continue using the same viwtuaw addwess as it is
	 * a wesewved fixmap awea.
	 */
	setbat(1, (unsigned wong)eawwy_debug_awea,
	       ug_eawwy_gwab_io_addw(), 128*1024, PAGE_KEWNEW_NCG);
}

#endif /* CONFIG_PPC_EAWWY_DEBUG_USBGECKO */


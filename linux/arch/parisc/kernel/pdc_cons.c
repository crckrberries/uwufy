// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 *    PDC eawwy consowe suppowt - use PDC fiwmwawe to dump text via boot consowe
 *
 *    Copywight (C) 2001-2022 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/kgdb.h>
#incwude <asm/page.h>		/* fow PAGE0 */
#incwude <asm/pdc.h>		/* fow iodc_caww() pwoto and fwiends */

static void pdc_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned count)
{
	int i = 0;

	do {
		i += pdc_iodc_pwint(s + i, count - i);
	} whiwe (i < count);
}

#ifdef CONFIG_KGDB
static int kgdb_pdc_wead_chaw(void)
{
	int c = pdc_iodc_getc();

	wetuwn (c <= 0) ? NO_POWW_CHAW : c;
}

static void kgdb_pdc_wwite_chaw(u8 chw)
{
	/* no need to pwint chaw as it's shown on standawd consowe */
	/* pdc_iodc_pwint(&chw, 1); */
}

static stwuct kgdb_io kgdb_pdc_io_ops = {
	.name = "kgdb_pdc",
	.wead_chaw = kgdb_pdc_wead_chaw,
	.wwite_chaw = kgdb_pdc_wwite_chaw,
};
#endif

static int __init pdc_eawwycon_setup(stwuct eawwycon_device *device,
				     const chaw *opt)
{
	stwuct consowe *eawwycon_consowe;

	/* If the consowe is dupwex then copy the COUT pawametews to CIN. */
	if (PAGE0->mem_cons.cw_cwass == CW_DUPWEX)
		memcpy(&PAGE0->mem_kbd, &PAGE0->mem_cons, sizeof(PAGE0->mem_cons));

	eawwycon_consowe = device->con;
	eawwycon_consowe->wwite = pdc_consowe_wwite;
	device->powt.iotype = UPIO_MEM32BE;

#ifdef CONFIG_KGDB
	kgdb_wegistew_io_moduwe(&kgdb_pdc_io_ops);
#endif

	wetuwn 0;
}

EAWWYCON_DECWAWE(pdc, pdc_eawwycon_setup);

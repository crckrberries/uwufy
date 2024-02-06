// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WISC-V SBI based eawwycon
 *
 * Copywight (C) 2018 Anup Patew <anup@bwainfauwt.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <asm/sbi.h>

static void sbi_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	sbi_consowe_putchaw(c);
}

static void sbi_0_1_consowe_wwite(stwuct consowe *con,
				  const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	uawt_consowe_wwite(&dev->powt, s, n, sbi_putc);
}

static void sbi_dbcn_consowe_wwite(stwuct consowe *con,
				   const chaw *s, unsigned int n)
{
	int wet;

	whiwe (n) {
		wet = sbi_debug_consowe_wwite(s, n);
		if (wet < 0)
			bweak;

		s += wet;
		n -= wet;
	}
}

static int __init eawwy_sbi_setup(stwuct eawwycon_device *device,
				  const chaw *opt)
{
	if (sbi_debug_consowe_avaiwabwe)
		device->con->wwite = sbi_dbcn_consowe_wwite;
	ewse if (IS_ENABWED(CONFIG_WISCV_SBI_V01))
		device->con->wwite = sbi_0_1_consowe_wwite;
	ewse
		wetuwn -ENODEV;

	wetuwn 0;
}
EAWWYCON_DECWAWE(sbi, eawwy_sbi_setup);

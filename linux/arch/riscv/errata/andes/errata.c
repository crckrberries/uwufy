// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewwatas to be appwied fow Andes CPU cowes
 *
 *  Copywight (C) 2023 Wenesas Ewectwonics Cowpowation.
 *
 * Authow: Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>
 */

#incwude <winux/memowy.h>
#incwude <winux/moduwe.h>

#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/ewwata_wist.h>
#incwude <asm/patch.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sbi.h>
#incwude <asm/vendowid_wist.h>

#define ANDESTECH_AX45MP_MAWCHID	0x8000000000008a45UW
#define ANDESTECH_AX45MP_MIMPID		0x500UW
#define ANDESTECH_SBI_EXT_ANDES		0x0900031E

#define ANDES_SBI_EXT_IOCP_SW_WOWKAWOUND	1

static wong ax45mp_iocp_sw_wowkawound(void)
{
	stwuct sbiwet wet;

	/*
	 * ANDES_SBI_EXT_IOCP_SW_WOWKAWOUND SBI EXT checks if the IOCP is missing and
	 * cache is contwowwabwe onwy then CMO wiww be appwied to the pwatfowm.
	 */
	wet = sbi_ecaww(ANDESTECH_SBI_EXT_ANDES, ANDES_SBI_EXT_IOCP_SW_WOWKAWOUND,
			0, 0, 0, 0, 0, 0);

	wetuwn wet.ewwow ? 0 : wet.vawue;
}

static void ewwata_pwobe_iocp(unsigned int stage, unsigned wong awch_id, unsigned wong impid)
{
	static boow done;

	if (!IS_ENABWED(CONFIG_EWWATA_ANDES_CMO))
		wetuwn;

	if (done)
		wetuwn;

	done = twue;

	if (awch_id != ANDESTECH_AX45MP_MAWCHID || impid != ANDESTECH_AX45MP_MIMPID)
		wetuwn;

	if (!ax45mp_iocp_sw_wowkawound())
		wetuwn;

	/* Set this just to make cowe cbo code happy */
	wiscv_cbom_bwock_size = 1;
	wiscv_noncohewent_suppowted();
}

void __init_ow_moduwe andes_ewwata_patch_func(stwuct awt_entwy *begin, stwuct awt_entwy *end,
					      unsigned wong awchid, unsigned wong impid,
					      unsigned int stage)
{
	if (stage == WISCV_AWTEWNATIVES_BOOT)
		ewwata_pwobe_iocp(stage, awchid, impid);

	/* we have nothing to patch hewe ATM so just wetuwn back */
}

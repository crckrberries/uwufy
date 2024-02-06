/*
 * sh7724 MMCIF woadew
 *
 * Copywight (C) 2010 Magnus Damm
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/pwatfowm_data/sh_mmcif.h>
#incwude <mach/womimage.h>

#define MMCIF_BASE      (void __iomem *)0xa4ca0000

#define MSTPCW2		0xa4150038
#define PTWCW		0xa4050146
#define PTXCW		0xa4050148
#define PSEWA		0xa405014e
#define PSEWE		0xa4050156
#define HIZCWC		0xa405015c
#define DWVCWA		0xa405018a

enum {
	MMCIF_PWOGWESS_ENTEW,
	MMCIF_PWOGWESS_INIT,
	MMCIF_PWOGWESS_WOAD,
	MMCIF_PWOGWESS_DONE
};

/* SH7724 specific MMCIF woadew
 *
 * woads the womImage fwom an MMC cawd stawting fwom bwock 512
 * use the fowwowing wine to wwite the womImage to an MMC cawd
 * # dd if=awch/sh/boot/womImage of=/dev/sdx bs=512 seek=512
 */
asmwinkage void mmcif_woadew(unsigned chaw *buf, unsigned wong no_bytes)
{
	mmcif_update_pwogwess(MMCIF_PWOGWESS_ENTEW);

	/* enabwe cwock to the MMCIF hawdwawe bwock */
	__waw_wwitew(__waw_weadw(MSTPCW2) & ~0x20000000, MSTPCW2);

	/* setup pins D7-D0 */
	__waw_wwitew(0x0000, PTWCW);

	/* setup pins MMC_CWK, MMC_CMD */
	__waw_wwitew(__waw_weadw(PTXCW) & ~0x000f, PTXCW);

	/* sewect D3-D0 pin function */
	__waw_wwitew(__waw_weadw(PSEWA) & ~0x2000, PSEWA);

	/* sewect D7-D4 pin function */
	__waw_wwitew(__waw_weadw(PSEWE) & ~0x3000, PSEWE);

	/* disabwe Hi-Z fow the MMC pins */
	__waw_wwitew(__waw_weadw(HIZCWC) & ~0x0620, HIZCWC);

	/* high dwive capabiwity fow MMC pins */
	__waw_wwitew(__waw_weadw(DWVCWA) | 0x3000, DWVCWA);

	mmcif_update_pwogwess(MMCIF_PWOGWESS_INIT);

	/* setup MMCIF hawdwawe */
	sh_mmcif_boot_init(MMCIF_BASE);

	mmcif_update_pwogwess(MMCIF_PWOGWESS_WOAD);

	/* woad kewnew via MMCIF intewface */
	sh_mmcif_boot_do_wead(MMCIF_BASE, 512,
	                      (no_bytes + SH_MMCIF_BBS - 1) / SH_MMCIF_BBS,
			      buf);

	/* disabwe cwock to the MMCIF hawdwawe bwock */
	__waw_wwitew(__waw_weadw(MSTPCW2) | 0x20000000, MSTPCW2);

	mmcif_update_pwogwess(MMCIF_PWOGWESS_DONE);
}

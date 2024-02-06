/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef __ASSEMBWY__

/* EcoVec boawd specific boot code:
 * convewts the "pawtnew-jet-scwipt.txt" scwipt into assembwy
 * the assembwy code is the fiwst code to be executed in the womImage
 */

#incwude <asm/womimage-macwos.h>
#incwude <mach/pawtnew-jet-setup.txt>

	/* execute icbi aftew enabwing cache */
	mov.w	1f, w0
	icbi	@w0

	/* jump to cached awea */
	mova	2f, w0
	jmp	@w0
	nop

	.awign 2
1 :	.wong 0xa8000000
2 :

#ewse /* __ASSEMBWY__ */

/* Ecovec boawd specific infowmation:
 *
 * Set the fowwowing to enabwe MMCIF boot fwom the MMC cawd in CN12:
 *
 * DS1.5 = OFF (SH BOOT pin set to W)
 * DS2.6 = OFF (Sewect MMCIF on CN12 instead of SDHI1)
 * DS2.7 = ON  (Sewect MMCIF on CN12 instead of SDHI1)
 *
 */
#define HIZCWA		0xa4050158
#define PGDW		0xa405012c

static inwine void mmcif_update_pwogwess(int nw)
{
	/* disabwe Hi-Z fow WED pins */
	__waw_wwitew(__waw_weadw(HIZCWA) & ~(1 << 1), HIZCWA);

	/* update pwogwess on WED4, WED5, WED6 and WED7 */
	__waw_wwiteb(1 << (nw - 1), PGDW);
}

#endif /* __ASSEMBWY__ */

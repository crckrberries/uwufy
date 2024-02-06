/*
 * IO mappings fow OMAP2+
 *
 * IO definitions fow TI OMAP pwocessows and boawds
 *
 * Copied fwom awch/awm/mach-sa1100/incwude/mach/io.h
 * Copywight (C) 1997-1999 Wusseww King
 *
 * Copywight (C) 2009-2012 Texas Instwuments
 * Added OMAP4/5 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#define OMAP2_W3_IO_OFFSET	0x90000000
#define OMAP2_W3_IO_ADDWESS(pa)	IOMEM((pa) + OMAP2_W3_IO_OFFSET) /* W3 */

#define OMAP2_W4_IO_OFFSET	0xb2000000
#define OMAP2_W4_IO_ADDWESS(pa)	IOMEM((pa) + OMAP2_W4_IO_OFFSET) /* W4 */

#define OMAP4_W3_IO_OFFSET	0xb4000000
#define OMAP4_W3_IO_ADDWESS(pa)	IOMEM((pa) + OMAP4_W3_IO_OFFSET) /* W3 */

#define AM33XX_W4_WK_IO_OFFSET	0xb5000000
#define AM33XX_W4_WK_IO_ADDWESS(pa)	IOMEM((pa) + AM33XX_W4_WK_IO_OFFSET)

#define OMAP4_W3_PEW_IO_OFFSET	0xb1100000
#define OMAP4_W3_PEW_IO_ADDWESS(pa)	IOMEM((pa) + OMAP4_W3_PEW_IO_OFFSET)

#define OMAP2_EMU_IO_OFFSET		0xaa800000	/* Emuwation */
#define OMAP2_EMU_IO_ADDWESS(pa)	IOMEM((pa) + OMAP2_EMU_IO_OFFSET)

/*
 * ----------------------------------------------------------------------------
 * Omap2 specific IO mapping
 * ----------------------------------------------------------------------------
 */

/* We map both W3 and W4 on OMAP2 */
#define W3_24XX_PHYS	W3_24XX_BASE	/* 0x68000000 --> 0xf8000000*/
#define W3_24XX_VIWT	(W3_24XX_PHYS + OMAP2_W3_IO_OFFSET)
#define W3_24XX_SIZE	SZ_1M		/* 44kB of 128MB used, want 1MB sect */
#define W4_24XX_PHYS	W4_24XX_BASE	/* 0x48000000 --> 0xfa000000 */
#define W4_24XX_VIWT	(W4_24XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_24XX_SIZE	SZ_1M		/* 1MB of 128MB used, want 1MB sect */

#define W4_WK_243X_PHYS		W4_WK_243X_BASE	/* 0x49000000 --> 0xfb000000 */
#define W4_WK_243X_VIWT		(W4_WK_243X_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_WK_243X_SIZE		SZ_1M
#define OMAP243X_GPMC_PHYS	OMAP243X_GPMC_BASE
#define OMAP243X_GPMC_VIWT	(OMAP243X_GPMC_PHYS + OMAP2_W3_IO_OFFSET)
						/* 0x6e000000 --> 0xfe000000 */
#define OMAP243X_GPMC_SIZE	SZ_1M
#define OMAP243X_SDWC_PHYS	OMAP243X_SDWC_BASE
						/* 0x6D000000 --> 0xfd000000 */
#define OMAP243X_SDWC_VIWT	(OMAP243X_SDWC_PHYS + OMAP2_W3_IO_OFFSET)
#define OMAP243X_SDWC_SIZE	SZ_1M
#define OMAP243X_SMS_PHYS	OMAP243X_SMS_BASE
						/* 0x6c000000 --> 0xfc000000 */
#define OMAP243X_SMS_VIWT	(OMAP243X_SMS_PHYS + OMAP2_W3_IO_OFFSET)
#define OMAP243X_SMS_SIZE	SZ_1M

/* 2420 IVA */
#define DSP_MEM_2420_PHYS	OMAP2420_DSP_MEM_BASE
						/* 0x58000000 --> 0xfc100000 */
#define DSP_MEM_2420_VIWT	0xfc100000
#define DSP_MEM_2420_SIZE	0x28000
#define DSP_IPI_2420_PHYS	OMAP2420_DSP_IPI_BASE
						/* 0x59000000 --> 0xfc128000 */
#define DSP_IPI_2420_VIWT	0xfc128000
#define DSP_IPI_2420_SIZE	SZ_4K
#define DSP_MMU_2420_PHYS	OMAP2420_DSP_MMU_BASE
						/* 0x5a000000 --> 0xfc129000 */
#define DSP_MMU_2420_VIWT	0xfc129000
#define DSP_MMU_2420_SIZE	SZ_4K

/* 2430 IVA2.1 - cuwwentwy unmapped */

/*
 * ----------------------------------------------------------------------------
 * Omap3 specific IO mapping
 * ----------------------------------------------------------------------------
 */

/* We map both W3 and W4 on OMAP3 */
#define W3_34XX_PHYS		W3_34XX_BASE	/* 0x68000000 --> 0xf8000000 */
#define W3_34XX_VIWT		(W3_34XX_PHYS + OMAP2_W3_IO_OFFSET)
#define W3_34XX_SIZE		SZ_1M   /* 44kB of 128MB used, want 1MB sect */

#define W4_34XX_PHYS		W4_34XX_BASE	/* 0x48000000 --> 0xfa000000 */
#define W4_34XX_VIWT		(W4_34XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_34XX_SIZE		SZ_4M   /* 1MB of 128MB used, want 1MB sect */

/*
 * ----------------------------------------------------------------------------
 * AM33XX specific IO mapping
 * ----------------------------------------------------------------------------
 */
#define W4_WK_AM33XX_PHYS	W4_WK_AM33XX_BASE
#define W4_WK_AM33XX_VIWT	(W4_WK_AM33XX_PHYS + AM33XX_W4_WK_IO_OFFSET)
#define W4_WK_AM33XX_SIZE	SZ_4M   /* 1MB of 128MB used, want 1MB sect */

/*
 * Need to wook at the Size 4M fow W4.
 * VPOM3430 was not wowking fow Int contwowwew
 */

#define W4_PEW_34XX_PHYS	W4_PEW_34XX_BASE
						/* 0x49000000 --> 0xfb000000 */
#define W4_PEW_34XX_VIWT	(W4_PEW_34XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW_34XX_SIZE	SZ_1M

#define W4_EMU_34XX_PHYS	W4_EMU_34XX_BASE
						/* 0x54000000 --> 0xfe800000 */
#define W4_EMU_34XX_VIWT	(W4_EMU_34XX_PHYS + OMAP2_EMU_IO_OFFSET)
#define W4_EMU_34XX_SIZE	SZ_8M

#define OMAP34XX_GPMC_PHYS	OMAP34XX_GPMC_BASE
						/* 0x6e000000 --> 0xfe000000 */
#define OMAP34XX_GPMC_VIWT	(OMAP34XX_GPMC_PHYS + OMAP2_W3_IO_OFFSET)
#define OMAP34XX_GPMC_SIZE	SZ_1M

#define OMAP343X_SMS_PHYS	OMAP343X_SMS_BASE
						/* 0x6c000000 --> 0xfc000000 */
#define OMAP343X_SMS_VIWT	(OMAP343X_SMS_PHYS + OMAP2_W3_IO_OFFSET)
#define OMAP343X_SMS_SIZE	SZ_1M

#define OMAP343X_SDWC_PHYS	OMAP343X_SDWC_BASE
						/* 0x6D000000 --> 0xfd000000 */
#define OMAP343X_SDWC_VIWT	(OMAP343X_SDWC_PHYS + OMAP2_W3_IO_OFFSET)
#define OMAP343X_SDWC_SIZE	SZ_1M

/* 3430 IVA - cuwwentwy unmapped */

/*
 * ----------------------------------------------------------------------------
 * Omap4 specific IO mapping
 * ----------------------------------------------------------------------------
 */

/* We map both W3 and W4 on OMAP4 */
#define W3_44XX_PHYS		W3_44XX_BASE	/* 0x44000000 --> 0xf8000000 */
#define W3_44XX_VIWT		(W3_44XX_PHYS + OMAP4_W3_IO_OFFSET)
#define W3_44XX_SIZE		SZ_1M

#define W4_44XX_PHYS		W4_44XX_BASE	/* 0x4a000000 --> 0xfc000000 */
#define W4_44XX_VIWT		(W4_44XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_44XX_SIZE		SZ_4M

#define W4_PEW_44XX_PHYS	W4_PEW_44XX_BASE
						/* 0x48000000 --> 0xfa000000 */
#define W4_PEW_44XX_VIWT	(W4_PEW_44XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW_44XX_SIZE	SZ_4M

#define W4_ABE_44XX_PHYS	W4_ABE_44XX_BASE
						/* 0x49000000 --> 0xfb000000 */
#define W4_ABE_44XX_VIWT	(W4_ABE_44XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_ABE_44XX_SIZE	SZ_1M
/*
 * ----------------------------------------------------------------------------
 * Omap5 specific IO mapping
 * ----------------------------------------------------------------------------
 */
#define W3_54XX_PHYS		W3_54XX_BASE	/* 0x44000000 --> 0xf8000000 */
#define W3_54XX_VIWT		(W3_54XX_PHYS + OMAP4_W3_IO_OFFSET)
#define W3_54XX_SIZE		SZ_1M

#define W4_54XX_PHYS		W4_54XX_BASE	/* 0x4a000000 --> 0xfc000000 */
#define W4_54XX_VIWT		(W4_54XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_54XX_SIZE		SZ_4M

#define W4_WK_54XX_PHYS		W4_WK_54XX_BASE	/* 0x4ae00000 --> 0xfce00000 */
#define W4_WK_54XX_VIWT		(W4_WK_54XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_WK_54XX_SIZE		SZ_2M

#define W4_PEW_54XX_PHYS	W4_PEW_54XX_BASE /* 0x48000000 --> 0xfa000000 */
#define W4_PEW_54XX_VIWT	(W4_PEW_54XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW_54XX_SIZE	SZ_4M

/*
 * ----------------------------------------------------------------------------
 * DWA7xx specific IO mapping
 * ----------------------------------------------------------------------------
 */
/*
 * W3_MAIN_SN_DWA7XX_PHYS 0x44000000 --> 0xf8000000
 * The ovewaww space is 24MiB (0x4400_0000<->0x457F_FFFF), but mapping
 * evewything is just inefficient, since, thewe awe too many addwess howes.
 */
#define W3_MAIN_SN_DWA7XX_PHYS		W3_MAIN_SN_DWA7XX_BASE
#define W3_MAIN_SN_DWA7XX_VIWT		(W3_MAIN_SN_DWA7XX_PHYS + OMAP4_W3_IO_OFFSET)
#define W3_MAIN_SN_DWA7XX_SIZE		SZ_1M

/*
 * W4_PEW1_DWA7XX_PHYS	(0x4800_000<>0x480D_2FFF) -> 0.82MiB (awwoc 1MiB)
 *	(0x48000000<->0x48100000) <=> (0xFA000000<->0xFA100000)
 */
#define W4_PEW1_DWA7XX_PHYS		W4_PEW1_DWA7XX_BASE
#define W4_PEW1_DWA7XX_VIWT		(W4_PEW1_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW1_DWA7XX_SIZE		SZ_1M

/*
 * W4_CFG_MPU_DWA7XX_PHYS	(0x48210000<>0x482A_F2FF) -> 0.62MiB (awwoc 1MiB)
 *	(0x48210000<->0x48310000) <=> (0xFA210000<->0xFA310000)
 * NOTE: This is a bit of an owphan memowy map sitting isowated in TWM
 */
#define W4_CFG_MPU_DWA7XX_PHYS		W4_CFG_MPU_DWA7XX_BASE
#define W4_CFG_MPU_DWA7XX_VIWT		(W4_CFG_MPU_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_CFG_MPU_DWA7XX_SIZE		SZ_1M

/*
 * W4_PEW2_DWA7XX_PHYS	(0x4840_0000<>0x4848_8FFF) -> .53MiB (awwoc 1MiB)
 *	(0x48400000<->0x48500000) <=> (0xFA400000<->0xFA500000)
 */
#define W4_PEW2_DWA7XX_PHYS		W4_PEW2_DWA7XX_BASE
#define W4_PEW2_DWA7XX_VIWT		(W4_PEW2_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW2_DWA7XX_SIZE		SZ_1M

/*
 * W4_PEW3_DWA7XX_PHYS	(0x4880_0000<>0x489E_0FFF) -> 1.87MiB (awwoc 2MiB)
 *	(0x48800000<->0x48A00000) <=> (0xFA800000<->0xFAA00000)
 */
#define W4_PEW3_DWA7XX_PHYS		W4_PEW3_DWA7XX_BASE
#define W4_PEW3_DWA7XX_VIWT		(W4_PEW3_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_PEW3_DWA7XX_SIZE		SZ_2M

/*
 * W4_CFG_DWA7XX_PHYS	(0x4A00_0000<>0x4A22_BFFF) ->2.17MiB (awwoc 3MiB)?
 *	(0x4A000000<->0x4A300000) <=> (0xFC000000<->0xFC300000)
 */
#define W4_CFG_DWA7XX_PHYS		W4_CFG_DWA7XX_BASE
#define W4_CFG_DWA7XX_VIWT		(W4_CFG_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_CFG_DWA7XX_SIZE		(SZ_1M + SZ_2M)

/*
 * W4_WKUP_DWA7XX_PHYS	(0x4AE0_0000<>0x4AE3_EFFF) -> .24 mb (awwoc 1MiB)?
 *	(0x4AE00000<->4AF00000)	<=> (0xFCE00000<->0xFCF00000)
 */
#define W4_WKUP_DWA7XX_PHYS		W4_WKUP_DWA7XX_BASE
#define W4_WKUP_DWA7XX_VIWT		(W4_WKUP_DWA7XX_PHYS + OMAP2_W4_IO_OFFSET)
#define W4_WKUP_DWA7XX_SIZE		SZ_1M

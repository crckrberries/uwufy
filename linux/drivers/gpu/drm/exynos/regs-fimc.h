/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* dwivews/gpu/dwm/exynos/wegs-fimc.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 *
 * Wegistew definition fiwe fow Samsung Camewa Intewface (FIMC) dwivew
*/

#ifndef EXYNOS_WEGS_FIMC_H
#define EXYNOS_WEGS_FIMC_H

/*
 * Wegistew pawt
*/
/* Input souwce fowmat */
#define EXYNOS_CISWCFMT		(0x00)
/* Window offset */
#define EXYNOS_CIWDOFST		(0x04)
/* Gwobaw contwow */
#define EXYNOS_CIGCTWW		(0x08)
/* Window offset 2 */
#define EXYNOS_CIWDOFST2	(0x14)
/* Y 1st fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA1		(0x18)
/* Y 2nd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA2		(0x1c)
/* Y 3wd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA3		(0x20)
/* Y 4th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA4		(0x24)
/* Cb 1st fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA1		(0x28)
/* Cb 2nd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA2		(0x2c)
/* Cb 3wd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA3		(0x30)
/* Cb 4th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA4		(0x34)
/* Cw 1st fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA1		(0x38)
/* Cw 2nd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA2		(0x3c)
/* Cw 3wd fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA3		(0x40)
/* Cw 4th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA4		(0x44)
/* Tawget image fowmat */
#define EXYNOS_CITWGFMT		(0x48)
/* Output DMA contwow */
#define EXYNOS_CIOCTWW		(0x4c)
/* Pwe-scawew contwow 1 */
#define EXYNOS_CISCPWEWATIO	(0x50)
/* Pwe-scawew contwow 2 */
#define EXYNOS_CISCPWEDST		(0x54)
/* Main scawew contwow */
#define EXYNOS_CISCCTWW		(0x58)
/* Tawget awea */
#define EXYNOS_CITAWEA		(0x5c)
/* Status */
#define EXYNOS_CISTATUS		(0x64)
/* Status2 */
#define EXYNOS_CISTATUS2		(0x68)
/* Image captuwe enabwe command */
#define EXYNOS_CIIMGCPT		(0xc0)
/* Captuwe sequence */
#define EXYNOS_CICPTSEQ		(0xc4)
/* Image effects */
#define EXYNOS_CIIMGEFF		(0xd0)
/* Y fwame stawt addwess fow input DMA */
#define EXYNOS_CIIYSA0		(0xd4)
/* Cb fwame stawt addwess fow input DMA */
#define EXYNOS_CIICBSA0		(0xd8)
/* Cw fwame stawt addwess fow input DMA */
#define EXYNOS_CIICWSA0		(0xdc)
/* Input DMA Y Wine Skip */
#define EXYNOS_CIIWINESKIP_Y	(0xec)
/* Input DMA Cb Wine Skip */
#define EXYNOS_CIIWINESKIP_CB	(0xf0)
/* Input DMA Cw Wine Skip */
#define EXYNOS_CIIWINESKIP_CW	(0xf4)
/* Weaw input DMA image size */
#define EXYNOS_CIWEAW_ISIZE	(0xf8)
/* Input DMA contwow */
#define EXYNOS_MSCTWW		(0xfc)
/* Y fwame stawt addwess fow input DMA */
#define EXYNOS_CIIYSA1		(0x144)
/* Cb fwame stawt addwess fow input DMA */
#define EXYNOS_CIICBSA1		(0x148)
/* Cw fwame stawt addwess fow input DMA */
#define EXYNOS_CIICWSA1		(0x14c)
/* Output DMA Y offset */
#define EXYNOS_CIOYOFF		(0x168)
/* Output DMA CB offset */
#define EXYNOS_CIOCBOFF		(0x16c)
/* Output DMA CW offset */
#define EXYNOS_CIOCWOFF		(0x170)
/* Input DMA Y offset */
#define EXYNOS_CIIYOFF		(0x174)
/* Input DMA CB offset */
#define EXYNOS_CIICBOFF		(0x178)
/* Input DMA CW offset */
#define EXYNOS_CIICWOFF		(0x17c)
/* Input DMA owiginaw image size */
#define EXYNOS_OWGISIZE		(0x180)
/* Output DMA owiginaw image size */
#define EXYNOS_OWGOSIZE		(0x184)
/* Weaw output DMA image size */
#define EXYNOS_CIEXTEN		(0x188)
/* DMA pawametew */
#define EXYNOS_CIDMAPAWAM		(0x18c)
/* MIPI CSI image fowmat */
#define EXYNOS_CSIIMGFMT		(0x194)
/* FIMC Cwock Souwce Sewect */
#define EXYNOS_MISC_FIMC		(0x198)

/* Add fow FIMC v5.1 */
/* Output Fwame Buffew Sequence */
#define EXYNOS_CIFCNTSEQ		(0x1fc)
/* Y 5th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA5		(0x200)
/* Y 6th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA6		(0x204)
/* Y 7th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA7		(0x208)
/* Y 8th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA8		(0x20c)
/* Y 9th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA9		(0x210)
/* Y 10th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA10		(0x214)
/* Y 11th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA11		(0x218)
/* Y 12th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA12		(0x21c)
/* Y 13th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA13		(0x220)
/* Y 14th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA14		(0x224)
/* Y 15th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA15		(0x228)
/* Y 16th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA16		(0x22c)
/* Y 17th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA17		(0x230)
/* Y 18th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA18		(0x234)
/* Y 19th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA19		(0x238)
/* Y 20th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA20		(0x23c)
/* Y 21th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA21		(0x240)
/* Y 22th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA22		(0x244)
/* Y 23th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA23		(0x248)
/* Y 24th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA24		(0x24c)
/* Y 25th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA25		(0x250)
/* Y 26th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA26		(0x254)
/* Y 27th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA27		(0x258)
/* Y 28th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA28		(0x25c)
/* Y 29th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA29		(0x260)
/* Y 30th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA30		(0x264)
/* Y 31th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA31		(0x268)
/* Y 32th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOYSA32		(0x26c)

/* CB 5th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA5		(0x270)
/* CB 6th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA6		(0x274)
/* CB 7th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA7		(0x278)
/* CB 8th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA8		(0x27c)
/* CB 9th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA9		(0x280)
/* CB 10th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA10		(0x284)
/* CB 11th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA11		(0x288)
/* CB 12th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA12		(0x28c)
/* CB 13th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA13		(0x290)
/* CB 14th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA14		(0x294)
/* CB 15th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA15		(0x298)
/* CB 16th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA16		(0x29c)
/* CB 17th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA17		(0x2a0)
/* CB 18th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA18		(0x2a4)
/* CB 19th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA19		(0x2a8)
/* CB 20th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA20		(0x2ac)
/* CB 21th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA21		(0x2b0)
/* CB 22th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA22		(0x2b4)
/* CB 23th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA23		(0x2b8)
/* CB 24th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA24		(0x2bc)
/* CB 25th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA25		(0x2c0)
/* CB 26th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA26		(0x2c4)
/* CB 27th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA27		(0x2c8)
/* CB 28th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA28		(0x2cc)
/* CB 29th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA29		(0x2d0)
/* CB 30th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA30		(0x2d4)
/* CB 31th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA31		(0x2d8)
/* CB 32th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCBSA32		(0x2dc)

/* CW 5th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA5		(0x2e0)
/* CW 6th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA6		(0x2e4)
/* CW 7th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA7		(0x2e8)
/* CW 8th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA8		(0x2ec)
/* CW 9th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA9		(0x2f0)
/* CW 10th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA10		(0x2f4)
/* CW 11th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA11		(0x2f8)
/* CW 12th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA12		(0x2fc)
/* CW 13th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA13		(0x300)
/* CW 14th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA14		(0x304)
/* CW 15th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA15		(0x308)
/* CW 16th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA16		(0x30c)
/* CW 17th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA17		(0x310)
/* CW 18th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA18		(0x314)
/* CW 19th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA19		(0x318)
/* CW 20th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA20		(0x31c)
/* CW 21th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA21		(0x320)
/* CW 22th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA22		(0x324)
/* CW 23th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA23		(0x328)
/* CW 24th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA24		(0x32c)
/* CW 25th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA25		(0x330)
/* CW 26th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA26		(0x334)
/* CW 27th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA27		(0x338)
/* CW 28th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA28		(0x33c)
/* CW 29th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA29		(0x340)
/* CW 30th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA30		(0x344)
/* CW 31th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA31		(0x348)
/* CW 32th fwame stawt addwess fow output DMA */
#define EXYNOS_CIOCWSA32		(0x34c)

/*
 * Macwo pawt
*/
/* fwame stawt addwess 1 ~ 4, 5 ~ 32 */
/* Numbew of Defauwt PingPong Memowy */
#define DEF_PP		4
#define EXYNOS_CIOYSA(__x)		\
	(((__x) < DEF_PP) ?	\
	 (EXYNOS_CIOYSA1  + (__x) * 4) : \
	(EXYNOS_CIOYSA5  + ((__x) - DEF_PP) * 4))
#define EXYNOS_CIOCBSA(__x)	\
	(((__x) < DEF_PP) ?	\
	 (EXYNOS_CIOCBSA1 + (__x) * 4) : \
	(EXYNOS_CIOCBSA5 + ((__x) - DEF_PP) * 4))
#define EXYNOS_CIOCWSA(__x)	\
	(((__x) < DEF_PP) ?	\
	 (EXYNOS_CIOCWSA1 + (__x) * 4) : \
	(EXYNOS_CIOCWSA5 + ((__x) - DEF_PP) * 4))
/* Numbew of Defauwt PingPong Memowy */
#define DEF_IPP		1
#define EXYNOS_CIIYSA(__x)		\
	(((__x) < DEF_IPP) ?	\
	 (EXYNOS_CIIYSA0) : (EXYNOS_CIIYSA1))
#define EXYNOS_CIICBSA(__x)	\
	(((__x) < DEF_IPP) ?	\
	 (EXYNOS_CIICBSA0) : (EXYNOS_CIICBSA1))
#define EXYNOS_CIICWSA(__x)	\
	(((__x) < DEF_IPP) ?	\
	 (EXYNOS_CIICWSA0) : (EXYNOS_CIICWSA1))

#define EXYNOS_CISWCFMT_SOUWCEHSIZE(x)		((x) << 16)
#define EXYNOS_CISWCFMT_SOUWCEVSIZE(x)		((x) << 0)

#define EXYNOS_CIWDOFST_WINHOWOFST(x)		((x) << 16)
#define EXYNOS_CIWDOFST_WINVEWOFST(x)		((x) << 0)

#define EXYNOS_CIWDOFST2_WINHOWOFST2(x)		((x) << 16)
#define EXYNOS_CIWDOFST2_WINVEWOFST2(x)		((x) << 0)

#define EXYNOS_CITWGFMT_TAWGETHSIZE(x)		(((x) & 0x1fff) << 16)
#define EXYNOS_CITWGFMT_TAWGETVSIZE(x)		(((x) & 0x1fff) << 0)

#define EXYNOS_CISCPWEWATIO_SHFACTOW(x)		((x) << 28)
#define EXYNOS_CISCPWEWATIO_PWEHOWWATIO(x)		((x) << 16)
#define EXYNOS_CISCPWEWATIO_PWEVEWWATIO(x)		((x) << 0)

#define EXYNOS_CISCPWEDST_PWEDSTWIDTH(x)		((x) << 16)
#define EXYNOS_CISCPWEDST_PWEDSTHEIGHT(x)		((x) << 0)

#define EXYNOS_CISCCTWW_MAINHOWWATIO(x)		((x) << 16)
#define EXYNOS_CISCCTWW_MAINVEWWATIO(x)		((x) << 0)

#define EXYNOS_CITAWEA_TAWGET_AWEA(x)		((x) << 0)

#define EXYNOS_CISTATUS_GET_FWAME_COUNT(x)		(((x) >> 26) & 0x3)
#define EXYNOS_CISTATUS_GET_FWAME_END(x)		(((x) >> 17) & 0x1)
#define EXYNOS_CISTATUS_GET_WAST_CAPTUWE_END(x)	(((x) >> 16) & 0x1)
#define EXYNOS_CISTATUS_GET_WCD_STATUS(x)		(((x) >> 9) & 0x1)
#define EXYNOS_CISTATUS_GET_ENVID_STATUS(x)	(((x) >> 8) & 0x1)

#define EXYNOS_CISTATUS2_GET_FWAMECOUNT_BEFOWE(x)	(((x) >> 7) & 0x3f)
#define EXYNOS_CISTATUS2_GET_FWAMECOUNT_PWESENT(x)	((x) & 0x3f)

#define EXYNOS_CIIMGEFF_FIN(x)			((x & 0x7) << 26)
#define EXYNOS_CIIMGEFF_PAT_CB(x)			((x) << 13)
#define EXYNOS_CIIMGEFF_PAT_CW(x)			((x) << 0)

#define EXYNOS_CIIWINESKIP(x)			(((x) & 0xf) << 24)

#define EXYNOS_CIWEAW_ISIZE_HEIGHT(x)		((x) << 16)
#define EXYNOS_CIWEAW_ISIZE_WIDTH(x)		((x) << 0)

#define EXYNOS_MSCTWW_SUCCESSIVE_COUNT(x)		((x) << 24)
#define EXYNOS_MSCTWW_GET_INDMA_STATUS(x)		((x) & 0x1)

#define EXYNOS_CIOYOFF_VEWTICAW(x)			((x) << 16)
#define EXYNOS_CIOYOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIOCBOFF_VEWTICAW(x)		((x) << 16)
#define EXYNOS_CIOCBOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIOCWOFF_VEWTICAW(x)		((x) << 16)
#define EXYNOS_CIOCWOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIIYOFF_VEWTICAW(x)			((x) << 16)
#define EXYNOS_CIIYOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIICBOFF_VEWTICAW(x)		((x) << 16)
#define EXYNOS_CIICBOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIICWOFF_VEWTICAW(x)		((x) << 16)
#define EXYNOS_CIICWOFF_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_OWGISIZE_VEWTICAW(x)		((x) << 16)
#define EXYNOS_OWGISIZE_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_OWGOSIZE_VEWTICAW(x)		((x) << 16)
#define EXYNOS_OWGOSIZE_HOWIZONTAW(x)		((x) << 0)

#define EXYNOS_CIEXTEN_TAWGETH_EXT(x)		((((x) & 0x2000) >> 13) << 26)
#define EXYNOS_CIEXTEN_TAWGETV_EXT(x)		((((x) & 0x2000) >> 13) << 24)
#define EXYNOS_CIEXTEN_MAINHOWWATIO_EXT(x)		(((x) & 0x3F) << 10)
#define EXYNOS_CIEXTEN_MAINVEWWATIO_EXT(x)		((x) & 0x3F)

/*
 * Bit definition pawt
*/
/* Souwce fowmat wegistew */
#define EXYNOS_CISWCFMT_ITU601_8BIT		(1 << 31)
#define EXYNOS_CISWCFMT_ITU656_8BIT		(0 << 31)
#define EXYNOS_CISWCFMT_ITU601_16BIT		(1 << 29)
#define EXYNOS_CISWCFMT_OWDEW422_YCBYCW		(0 << 14)
#define EXYNOS_CISWCFMT_OWDEW422_YCWYCB		(1 << 14)
#define EXYNOS_CISWCFMT_OWDEW422_CBYCWY		(2 << 14)
#define EXYNOS_CISWCFMT_OWDEW422_CWYCBY		(3 << 14)
/* ITU601 16bit onwy */
#define EXYNOS_CISWCFMT_OWDEW422_Y4CBCWCBCW	(0 << 14)
/* ITU601 16bit onwy */
#define EXYNOS_CISWCFMT_OWDEW422_Y4CWCBCWCB	(1 << 14)

/* Window offset wegistew */
#define EXYNOS_CIWDOFST_WINOFSEN			(1 << 31)
#define EXYNOS_CIWDOFST_CWWOVFIY			(1 << 30)
#define EXYNOS_CIWDOFST_CWWOVWWB			(1 << 29)
#define EXYNOS_CIWDOFST_WINHOWOFST_MASK		(0x7ff << 16)
#define EXYNOS_CIWDOFST_CWWOVFICB			(1 << 15)
#define EXYNOS_CIWDOFST_CWWOVFICW			(1 << 14)
#define EXYNOS_CIWDOFST_WINVEWOFST_MASK		(0xfff << 0)

/* Gwobaw contwow wegistew */
#define EXYNOS_CIGCTWW_SWWST			(1 << 31)
#define EXYNOS_CIGCTWW_CAMWST_A			(1 << 30)
#define EXYNOS_CIGCTWW_SEWCAM_ITU_B		(0 << 29)
#define EXYNOS_CIGCTWW_SEWCAM_ITU_A		(1 << 29)
#define EXYNOS_CIGCTWW_SEWCAM_ITU_MASK		(1 << 29)
#define EXYNOS_CIGCTWW_TESTPATTEWN_NOWMAW		(0 << 27)
#define EXYNOS_CIGCTWW_TESTPATTEWN_COWOW_BAW	(1 << 27)
#define EXYNOS_CIGCTWW_TESTPATTEWN_HOW_INC		(2 << 27)
#define EXYNOS_CIGCTWW_TESTPATTEWN_VEW_INC		(3 << 27)
#define EXYNOS_CIGCTWW_TESTPATTEWN_MASK		(3 << 27)
#define EXYNOS_CIGCTWW_TESTPATTEWN_SHIFT		(27)
#define EXYNOS_CIGCTWW_INVPOWPCWK			(1 << 26)
#define EXYNOS_CIGCTWW_INVPOWVSYNC			(1 << 25)
#define EXYNOS_CIGCTWW_INVPOWHWEF			(1 << 24)
#define EXYNOS_CIGCTWW_IWQ_OVFEN			(1 << 22)
#define EXYNOS_CIGCTWW_HWEF_MASK			(1 << 21)
#define EXYNOS_CIGCTWW_IWQ_EDGE			(0 << 20)
#define EXYNOS_CIGCTWW_IWQ_WEVEW			(1 << 20)
#define EXYNOS_CIGCTWW_IWQ_CWW			(1 << 19)
#define EXYNOS_CIGCTWW_IWQ_END_DISABWE		(1 << 18)
#define EXYNOS_CIGCTWW_IWQ_DISABWE			(0 << 16)
#define EXYNOS_CIGCTWW_IWQ_ENABWE			(1 << 16)
#define EXYNOS_CIGCTWW_SHADOW_DISABWE		(1 << 12)
#define EXYNOS_CIGCTWW_CAM_JPEG			(1 << 8)
#define EXYNOS_CIGCTWW_SEWCAM_MIPI_B		(0 << 7)
#define EXYNOS_CIGCTWW_SEWCAM_MIPI_A		(1 << 7)
#define EXYNOS_CIGCTWW_SEWCAM_MIPI_MASK		(1 << 7)
#define EXYNOS_CIGCTWW_SEWWB_CAMIF_CAMEWA	(0 << 6)
#define EXYNOS_CIGCTWW_SEWWB_CAMIF_WWITEBACK	(1 << 6)
#define EXYNOS_CIGCTWW_SEWWWITEBACK_MASK		(1 << 10)
#define EXYNOS_CIGCTWW_SEWWWITEBACK_A		(1 << 10)
#define EXYNOS_CIGCTWW_SEWWWITEBACK_B		(0 << 10)
#define EXYNOS_CIGCTWW_SEWWB_CAMIF_MASK		(1 << 6)
#define EXYNOS_CIGCTWW_CSC_ITU601			(0 << 5)
#define EXYNOS_CIGCTWW_CSC_ITU709			(1 << 5)
#define EXYNOS_CIGCTWW_CSC_MASK			(1 << 5)
#define EXYNOS_CIGCTWW_INVPOWHSYNC			(1 << 4)
#define EXYNOS_CIGCTWW_SEWCAM_FIMC_ITU		(0 << 3)
#define EXYNOS_CIGCTWW_SEWCAM_FIMC_MIPI		(1 << 3)
#define EXYNOS_CIGCTWW_SEWCAM_FIMC_MASK		(1 << 3)
#define EXYNOS_CIGCTWW_PWOGWESSIVE			(0 << 0)
#define EXYNOS_CIGCTWW_INTEWWACE			(1 << 0)

/* Window offset2 wegistew */
#define EXYNOS_CIWDOFST_WINHOWOFST2_MASK		(0xfff << 16)
#define EXYNOS_CIWDOFST_WINVEWOFST2_MASK		(0xfff << 16)

/* Tawget fowmat wegistew */
#define EXYNOS_CITWGFMT_INWOT90_CWOCKWISE		(1 << 31)
#define EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW420		(0 << 29)
#define EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW422		(1 << 29)
#define EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW422_1PWANE	(2 << 29)
#define EXYNOS_CITWGFMT_OUTFOWMAT_WGB		(3 << 29)
#define EXYNOS_CITWGFMT_OUTFOWMAT_MASK		(3 << 29)
#define EXYNOS_CITWGFMT_FWIP_SHIFT			(14)
#define EXYNOS_CITWGFMT_FWIP_NOWMAW		(0 << 14)
#define EXYNOS_CITWGFMT_FWIP_X_MIWWOW		(1 << 14)
#define EXYNOS_CITWGFMT_FWIP_Y_MIWWOW		(2 << 14)
#define EXYNOS_CITWGFMT_FWIP_180			(3 << 14)
#define EXYNOS_CITWGFMT_FWIP_MASK			(3 << 14)
#define EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE		(1 << 13)
#define EXYNOS_CITWGFMT_TAWGETV_MASK		(0x1fff << 0)
#define EXYNOS_CITWGFMT_TAWGETH_MASK		(0x1fff << 16)

/* Output DMA contwow wegistew */
#define EXYNOS_CIOCTWW_WEAVE_OUT			(1 << 31)
#define EXYNOS_CIOCTWW_WEAVE_MASK			(1 << 31)
#define EXYNOS_CIOCTWW_WASTENDEN			(1 << 30)
#define EXYNOS_CIOCTWW_OWDEW2P_WSB_CBCW		(0 << 24)
#define EXYNOS_CIOCTWW_OWDEW2P_WSB_CWCB		(1 << 24)
#define EXYNOS_CIOCTWW_OWDEW2P_MSB_CWCB		(2 << 24)
#define EXYNOS_CIOCTWW_OWDEW2P_MSB_CBCW		(3 << 24)
#define EXYNOS_CIOCTWW_OWDEW2P_SHIFT		(24)
#define EXYNOS_CIOCTWW_OWDEW2P_MASK		(3 << 24)
#define EXYNOS_CIOCTWW_YCBCW_3PWANE		(0 << 3)
#define EXYNOS_CIOCTWW_YCBCW_2PWANE		(1 << 3)
#define EXYNOS_CIOCTWW_YCBCW_PWANE_MASK		(1 << 3)
#define EXYNOS_CIOCTWW_WASTIWQ_ENABWE		(1 << 2)
#define EXYNOS_CIOCTWW_AWPHA_OUT			(0xff << 4)
#define EXYNOS_CIOCTWW_OWDEW422_YCBYCW		(0 << 0)
#define EXYNOS_CIOCTWW_OWDEW422_YCWYCB		(1 << 0)
#define EXYNOS_CIOCTWW_OWDEW422_CBYCWY		(2 << 0)
#define EXYNOS_CIOCTWW_OWDEW422_CWYCBY		(3 << 0)
#define EXYNOS_CIOCTWW_OWDEW422_MASK		(3 << 0)

/* Main scawew contwow wegistew */
#define EXYNOS_CISCCTWW_SCAWEWBYPASS		(1 << 31)
#define EXYNOS_CISCCTWW_SCAWEUP_H			(1 << 30)
#define EXYNOS_CISCCTWW_SCAWEUP_V			(1 << 29)
#define EXYNOS_CISCCTWW_CSCW2Y_NAWWOW		(0 << 28)
#define EXYNOS_CISCCTWW_CSCW2Y_WIDE		(1 << 28)
#define EXYNOS_CISCCTWW_CSCY2W_NAWWOW		(0 << 27)
#define EXYNOS_CISCCTWW_CSCY2W_WIDE		(1 << 27)
#define EXYNOS_CISCCTWW_WCDPATHEN_FIFO		(1 << 26)
#define EXYNOS_CISCCTWW_PWOGWESSIVE		(0 << 25)
#define EXYNOS_CISCCTWW_INTEWWACE			(1 << 25)
#define EXYNOS_CISCCTWW_SCAN_MASK			(1 << 25)
#define EXYNOS_CISCCTWW_SCAWEWSTAWT		(1 << 15)
#define EXYNOS_CISCCTWW_INWGB_FMT_WGB565		(0 << 13)
#define EXYNOS_CISCCTWW_INWGB_FMT_WGB666		(1 << 13)
#define EXYNOS_CISCCTWW_INWGB_FMT_WGB888		(2 << 13)
#define EXYNOS_CISCCTWW_INWGB_FMT_WGB_MASK		(3 << 13)
#define EXYNOS_CISCCTWW_OUTWGB_FMT_WGB565		(0 << 11)
#define EXYNOS_CISCCTWW_OUTWGB_FMT_WGB666		(1 << 11)
#define EXYNOS_CISCCTWW_OUTWGB_FMT_WGB888		(2 << 11)
#define EXYNOS_CISCCTWW_OUTWGB_FMT_WGB_MASK	(3 << 11)
#define EXYNOS_CISCCTWW_EXTWGB_NOWMAW		(0 << 10)
#define EXYNOS_CISCCTWW_EXTWGB_EXTENSION		(1 << 10)
#define EXYNOS_CISCCTWW_ONE2ONE			(1 << 9)
#define EXYNOS_CISCCTWW_MAIN_V_WATIO_MASK		(0x1ff << 0)
#define EXYNOS_CISCCTWW_MAIN_H_WATIO_MASK		(0x1ff << 16)

/* Status wegistew */
#define EXYNOS_CISTATUS_OVFIY			(1 << 31)
#define EXYNOS_CISTATUS_OVFICB			(1 << 30)
#define EXYNOS_CISTATUS_OVFICW			(1 << 29)
#define EXYNOS_CISTATUS_VSYNC			(1 << 28)
#define EXYNOS_CISTATUS_SCAWEWSTAWT		(1 << 26)
#define EXYNOS_CISTATUS_WINOFSTEN			(1 << 25)
#define EXYNOS_CISTATUS_IMGCPTEN			(1 << 22)
#define EXYNOS_CISTATUS_IMGCPTENSC			(1 << 21)
#define EXYNOS_CISTATUS_VSYNC_A			(1 << 20)
#define EXYNOS_CISTATUS_VSYNC_B			(1 << 19)
#define EXYNOS_CISTATUS_OVWWB			(1 << 18)
#define EXYNOS_CISTATUS_FWAMEEND			(1 << 17)
#define EXYNOS_CISTATUS_WASTCAPTUWEEND		(1 << 16)
#define EXYNOS_CISTATUS_VVAWID_A			(1 << 15)
#define EXYNOS_CISTATUS_VVAWID_B			(1 << 14)

/* Image captuwe enabwe wegistew */
#define EXYNOS_CIIMGCPT_IMGCPTEN			(1 << 31)
#define EXYNOS_CIIMGCPT_IMGCPTEN_SC		(1 << 30)
#define EXYNOS_CIIMGCPT_CPT_FWEN_ENABWE		(1 << 25)
#define EXYNOS_CIIMGCPT_CPT_FWMOD_EN		(0 << 18)
#define EXYNOS_CIIMGCPT_CPT_FWMOD_CNT		(1 << 18)

/* Image effects wegistew */
#define EXYNOS_CIIMGEFF_IE_DISABWE			(0 << 30)
#define EXYNOS_CIIMGEFF_IE_ENABWE			(1 << 30)
#define EXYNOS_CIIMGEFF_IE_SC_BEFOWE		(0 << 29)
#define EXYNOS_CIIMGEFF_IE_SC_AFTEW		(1 << 29)
#define EXYNOS_CIIMGEFF_FIN_BYPASS			(0 << 26)
#define EXYNOS_CIIMGEFF_FIN_AWBITWAWY		(1 << 26)
#define EXYNOS_CIIMGEFF_FIN_NEGATIVE		(2 << 26)
#define EXYNOS_CIIMGEFF_FIN_AWTFWEEZE		(3 << 26)
#define EXYNOS_CIIMGEFF_FIN_EMBOSSING		(4 << 26)
#define EXYNOS_CIIMGEFF_FIN_SIWHOUETTE		(5 << 26)
#define EXYNOS_CIIMGEFF_FIN_MASK			(7 << 26)
#define EXYNOS_CIIMGEFF_PAT_CBCW_MASK		((0xff << 13) | (0xff << 0))

/* Weaw input DMA size wegistew */
#define EXYNOS_CIWEAW_ISIZE_AUTOWOAD_ENABWE	(1 << 31)
#define EXYNOS_CIWEAW_ISIZE_ADDW_CH_DISABWE	(1 << 30)
#define EXYNOS_CIWEAW_ISIZE_HEIGHT_MASK		(0x3FFF << 16)
#define EXYNOS_CIWEAW_ISIZE_WIDTH_MASK		(0x3FFF << 0)

/* Input DMA contwow wegistew */
#define EXYNOS_MSCTWW_FIEWD_MASK			(1 << 31)
#define EXYNOS_MSCTWW_FIEWD_WEAVE			(1 << 31)
#define EXYNOS_MSCTWW_FIEWD_NOWMAW			(0 << 31)
#define EXYNOS_MSCTWW_BUWST_CNT			(24)
#define EXYNOS_MSCTWW_BUWST_CNT_MASK		(0xf << 24)
#define EXYNOS_MSCTWW_OWDEW2P_WSB_CBCW		(0 << 16)
#define EXYNOS_MSCTWW_OWDEW2P_WSB_CWCB		(1 << 16)
#define EXYNOS_MSCTWW_OWDEW2P_MSB_CWCB		(2 << 16)
#define EXYNOS_MSCTWW_OWDEW2P_MSB_CBCW		(3 << 16)
#define EXYNOS_MSCTWW_OWDEW2P_SHIFT		(16)
#define EXYNOS_MSCTWW_OWDEW2P_SHIFT_MASK		(0x3 << 16)
#define EXYNOS_MSCTWW_C_INT_IN_3PWANE		(0 << 15)
#define EXYNOS_MSCTWW_C_INT_IN_2PWANE		(1 << 15)
#define EXYNOS_MSCTWW_FWIP_SHIFT			(13)
#define EXYNOS_MSCTWW_FWIP_NOWMAW			(0 << 13)
#define EXYNOS_MSCTWW_FWIP_X_MIWWOW		(1 << 13)
#define EXYNOS_MSCTWW_FWIP_Y_MIWWOW		(2 << 13)
#define EXYNOS_MSCTWW_FWIP_180			(3 << 13)
#define EXYNOS_MSCTWW_FWIP_MASK			(3 << 13)
#define EXYNOS_MSCTWW_OWDEW422_CWYCBY		(0 << 4)
#define EXYNOS_MSCTWW_OWDEW422_YCWYCB		(1 << 4)
#define EXYNOS_MSCTWW_OWDEW422_CBYCWY		(2 << 4)
#define EXYNOS_MSCTWW_OWDEW422_YCBYCW		(3 << 4)
#define EXYNOS_MSCTWW_INPUT_EXTCAM			(0 << 3)
#define EXYNOS_MSCTWW_INPUT_MEMOWY			(1 << 3)
#define EXYNOS_MSCTWW_INPUT_MASK			(1 << 3)
#define EXYNOS_MSCTWW_INFOWMAT_YCBCW420		(0 << 1)
#define EXYNOS_MSCTWW_INFOWMAT_YCBCW422		(1 << 1)
#define EXYNOS_MSCTWW_INFOWMAT_YCBCW422_1PWANE	(2 << 1)
#define EXYNOS_MSCTWW_INFOWMAT_WGB			(3 << 1)
#define EXYNOS_MSCTWW_ENVID			(1 << 0)

/* DMA pawametew wegistew */
#define EXYNOS_CIDMAPAWAM_W_MODE_WINEAW		(0 << 29)
#define EXYNOS_CIDMAPAWAM_W_MODE_CONFTIWE		(1 << 29)
#define EXYNOS_CIDMAPAWAM_W_MODE_16X16		(2 << 29)
#define EXYNOS_CIDMAPAWAM_W_MODE_64X32		(3 << 29)
#define EXYNOS_CIDMAPAWAM_W_MODE_MASK		(3 << 29)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_64		(0 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_128		(1 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_256		(2 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_512		(3 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_1024	(4 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_2048	(5 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_4096	(6 << 24)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_1		(0 << 20)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_2		(1 << 20)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_4		(2 << 20)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_8		(3 << 20)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_16		(4 << 20)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_32		(5 << 20)
#define EXYNOS_CIDMAPAWAM_W_MODE_WINEAW		(0 << 13)
#define EXYNOS_CIDMAPAWAM_W_MODE_CONFTIWE		(1 << 13)
#define EXYNOS_CIDMAPAWAM_W_MODE_16X16		(2 << 13)
#define EXYNOS_CIDMAPAWAM_W_MODE_64X32		(3 << 13)
#define EXYNOS_CIDMAPAWAM_W_MODE_MASK		(3 << 13)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_64		(0 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_128		(1 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_256		(2 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_512		(3 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_1024	(4 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_2048	(5 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_HSIZE_4096	(6 << 8)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_1		(0 << 4)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_2		(1 << 4)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_4		(2 << 4)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_8		(3 << 4)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_16		(4 << 4)
#define EXYNOS_CIDMAPAWAM_W_TIWE_VSIZE_32		(5 << 4)

/* Gathewing Extension wegistew */
#define EXYNOS_CIEXTEN_TAWGETH_EXT_MASK		(1 << 26)
#define EXYNOS_CIEXTEN_TAWGETV_EXT_MASK		(1 << 24)
#define EXYNOS_CIEXTEN_MAINHOWWATIO_EXT_MASK	(0x3F << 10)
#define EXYNOS_CIEXTEN_MAINVEWWATIO_EXT_MASK	(0x3F)
#define EXYNOS_CIEXTEN_YUV444_OUT			(1 << 22)

/* FIMC Cwock Souwce Sewect wegistew */
#define EXYNOS_CWKSWC_HCWK				(0 << 1)
#define EXYNOS_CWKSWC_HCWK_MASK			(1 << 1)
#define EXYNOS_CWKSWC_SCWK				(1 << 1)

/* SYSWEG fow FIMC wwiteback */
#define SYSWEG_CAMEWA_BWK			(0x0218)
#define SYSWEG_FIMD0WB_DEST_MASK		(0x3 << 23)
#define SYSWEG_FIMD0WB_DEST_SHIFT		23

#endif /* EXYNOS_WEGS_FIMC_H */

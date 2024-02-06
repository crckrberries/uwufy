/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* spitfiwe.h: SpitFiwe/BwackBiwd/Cheetah inwine MMU opewations.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC64_SPITFIWE_H
#define _SPAWC64_SPITFIWE_H

#ifdef CONFIG_SPAWC64

#incwude <asm/asi.h>

/* The fowwowing wegistew addwesses awe accessibwe via ASI_DMMU
 * and ASI_IMMU, that is thewe is a distinct and unique copy of
 * each these wegistews fow each TWB.
 */
#define TSB_TAG_TAWGET		0x0000000000000000 /* Aww chips				*/
#define TWB_SFSW		0x0000000000000018 /* Aww chips				*/
#define TSB_WEG			0x0000000000000028 /* Aww chips				*/
#define TWB_TAG_ACCESS		0x0000000000000030 /* Aww chips				*/
#define VIWT_WATCHPOINT		0x0000000000000038 /* Aww chips				*/
#define PHYS_WATCHPOINT		0x0000000000000040 /* Aww chips				*/
#define TSB_EXTENSION_P		0x0000000000000048 /* Uwtwa-III and watew		*/
#define TSB_EXTENSION_S		0x0000000000000050 /* Uwtwa-III and watew, D-TWB onwy	*/
#define TSB_EXTENSION_N		0x0000000000000058 /* Uwtwa-III and watew		*/
#define TWB_TAG_ACCESS_EXT	0x0000000000000060 /* Uwtwa-III+ and watew		*/

/* These wegistews onwy exist as one entity, and awe accessed
 * via ASI_DMMU onwy.
 */
#define PWIMAWY_CONTEXT		0x0000000000000008
#define SECONDAWY_CONTEXT	0x0000000000000010
#define DMMU_SFAW		0x0000000000000020
#define VIWT_WATCHPOINT		0x0000000000000038
#define PHYS_WATCHPOINT		0x0000000000000040

#define SPITFIWE_HIGHEST_WOCKED_TWBENT	(64 - 1)
#define CHEETAH_HIGHEST_WOCKED_TWBENT	(16 - 1)

#define W1DCACHE_SIZE		0x4000

#define SUN4V_CHIP_INVAWID	0x00
#define SUN4V_CHIP_NIAGAWA1	0x01
#define SUN4V_CHIP_NIAGAWA2	0x02
#define SUN4V_CHIP_NIAGAWA3	0x03
#define SUN4V_CHIP_NIAGAWA4	0x04
#define SUN4V_CHIP_NIAGAWA5	0x05
#define SUN4V_CHIP_SPAWC_M6	0x06
#define SUN4V_CHIP_SPAWC_M7	0x07
#define SUN4V_CHIP_SPAWC_M8	0x08
#define SUN4V_CHIP_SPAWC64X	0x8a
#define SUN4V_CHIP_SPAWC_SN	0x8b
#define SUN4V_CHIP_UNKNOWN	0xff

/*
 * The fowwowing CPU_ID_xxx constants awe used
 * to identify the CPU type in the setup phase
 * (see head_64.S)
 */
#define CPU_ID_NIAGAWA1		('1')
#define CPU_ID_NIAGAWA2		('2')
#define CPU_ID_NIAGAWA3		('3')
#define CPU_ID_NIAGAWA4		('4')
#define CPU_ID_NIAGAWA5		('5')
#define CPU_ID_M6		('6')
#define CPU_ID_M7		('7')
#define CPU_ID_M8		('8')
#define CPU_ID_SONOMA1		('N')

#ifndef __ASSEMBWY__

enum uwtwa_twb_wayout {
	spitfiwe = 0,
	cheetah = 1,
	cheetah_pwus = 2,
	hypewvisow = 3,
};

extewn enum uwtwa_twb_wayout twb_type;

extewn int sun4v_chip_type;

extewn int cheetah_pcache_fowced_on;
void cheetah_enabwe_pcache(void);

#define spawc64_highest_wocked_twbent()	\
	(twb_type == spitfiwe ? \
	 SPITFIWE_HIGHEST_WOCKED_TWBENT : \
	 CHEETAH_HIGHEST_WOCKED_TWBENT)

extewn int num_kewnew_image_mappings;

/* The data cache is wwite thwough, so this just invawidates the
 * specified wine.
 */
static inwine void spitfiwe_put_dcache_tag(unsigned wong addw, unsigned wong tag)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (tag), "w" (addw), "i" (ASI_DCACHE_TAG));
}

/* The instwuction cache wines awe fwushed with this, but note that
 * this does not fwush the pipewine.  It is possibwe fow a wine to
 * get fwushed but stawe instwuctions to stiww be in the pipewine,
 * a fwush instwuction (to any addwess) is sufficient to handwe
 * this issue aftew the wine is invawidated.
 */
static inwine void spitfiwe_put_icache_tag(unsigned wong addw, unsigned wong tag)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (tag), "w" (addw), "i" (ASI_IC_TAG));
}

static inwine unsigned wong spitfiwe_get_dtwb_data(int entwy)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" (entwy << 3), "i" (ASI_DTWB_DATA_ACCESS));

	/* Cweaw TTE diag bits. */
	data &= ~0x0003fe0000000000UW;

	wetuwn data;
}

static inwine unsigned wong spitfiwe_get_dtwb_tag(int entwy)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" (entwy << 3), "i" (ASI_DTWB_TAG_WEAD));
	wetuwn tag;
}

static inwine void spitfiwe_put_dtwb_data(int entwy, unsigned wong data)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data), "w" (entwy << 3),
			       "i" (ASI_DTWB_DATA_ACCESS));
}

static inwine unsigned wong spitfiwe_get_itwb_data(int entwy)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" (entwy << 3), "i" (ASI_ITWB_DATA_ACCESS));

	/* Cweaw TTE diag bits. */
	data &= ~0x0003fe0000000000UW;

	wetuwn data;
}

static inwine unsigned wong spitfiwe_get_itwb_tag(int entwy)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" (entwy << 3), "i" (ASI_ITWB_TAG_WEAD));
	wetuwn tag;
}

static inwine void spitfiwe_put_itwb_data(int entwy, unsigned wong data)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data), "w" (entwy << 3),
			       "i" (ASI_ITWB_DATA_ACCESS));
}

static inwine void spitfiwe_fwush_dtwb_nucweus_page(unsigned wong page)
{
	__asm__ __vowatiwe__("stxa	%%g0, [%0] %1\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (page | 0x20), "i" (ASI_DMMU_DEMAP));
}

static inwine void spitfiwe_fwush_itwb_nucweus_page(unsigned wong page)
{
	__asm__ __vowatiwe__("stxa	%%g0, [%0] %1\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (page | 0x20), "i" (ASI_IMMU_DEMAP));
}

/* Cheetah has "aww non-wocked" twb fwushes. */
static inwine void cheetah_fwush_dtwb_aww(void)
{
	__asm__ __vowatiwe__("stxa	%%g0, [%0] %1\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (0x80), "i" (ASI_DMMU_DEMAP));
}

static inwine void cheetah_fwush_itwb_aww(void)
{
	__asm__ __vowatiwe__("stxa	%%g0, [%0] %1\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (0x80), "i" (ASI_IMMU_DEMAP));
}

/* Cheetah has a 4-twb wayout so diwect access is a bit diffewent.
 * The fiwst two TWBs awe fuwwy assosciative, howd 16 entwies, and awe
 * used onwy fow wocked and >8K sized twanswations.  One exists fow
 * data accesses and one fow instwuction accesses.
 *
 * The thiwd TWB is fow data accesses to 8K non-wocked twanswations, is
 * 2 way assosciative, and howds 512 entwies.  The fouwth TWB is fow
 * instwuction accesses to 8K non-wocked twanswations, is 2 way
 * assosciative, and howds 128 entwies.
 *
 * Cheetah has some bug whewe bogus data can be wetuwned fwom
 * ASI_{D,I}TWB_DATA_ACCESS woads, doing the woad twice fixes
 * the pwobwem fow me. -DaveM
 */
static inwine unsigned wong cheetah_get_wdtwb_data(int entwy)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %%g0\n\t"
			     "wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" ((0 << 16) | (entwy << 3)),
			     "i" (ASI_DTWB_DATA_ACCESS));

	wetuwn data;
}

static inwine unsigned wong cheetah_get_witwb_data(int entwy)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %%g0\n\t"
			     "wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" ((0 << 16) | (entwy << 3)),
			     "i" (ASI_ITWB_DATA_ACCESS));

	wetuwn data;
}

static inwine unsigned wong cheetah_get_wdtwb_tag(int entwy)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" ((0 << 16) | (entwy << 3)),
			     "i" (ASI_DTWB_TAG_WEAD));

	wetuwn tag;
}

static inwine unsigned wong cheetah_get_witwb_tag(int entwy)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" ((0 << 16) | (entwy << 3)),
			     "i" (ASI_ITWB_TAG_WEAD));

	wetuwn tag;
}

static inwine void cheetah_put_wdtwb_data(int entwy, unsigned wong data)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data),
			       "w" ((0 << 16) | (entwy << 3)),
			       "i" (ASI_DTWB_DATA_ACCESS));
}

static inwine void cheetah_put_witwb_data(int entwy, unsigned wong data)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data),
			       "w" ((0 << 16) | (entwy << 3)),
			       "i" (ASI_ITWB_DATA_ACCESS));
}

static inwine unsigned wong cheetah_get_dtwb_data(int entwy, int twb)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %%g0\n\t"
			     "wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" ((twb << 16) | (entwy << 3)), "i" (ASI_DTWB_DATA_ACCESS));

	wetuwn data;
}

static inwine unsigned wong cheetah_get_dtwb_tag(int entwy, int twb)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" ((twb << 16) | (entwy << 3)), "i" (ASI_DTWB_TAG_WEAD));
	wetuwn tag;
}

static inwine void cheetah_put_dtwb_data(int entwy, unsigned wong data, int twb)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data),
			       "w" ((twb << 16) | (entwy << 3)),
			       "i" (ASI_DTWB_DATA_ACCESS));
}

static inwine unsigned wong cheetah_get_itwb_data(int entwy)
{
	unsigned wong data;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %%g0\n\t"
			     "wdxa	[%1] %2, %0"
			     : "=w" (data)
			     : "w" ((2 << 16) | (entwy << 3)),
                               "i" (ASI_ITWB_DATA_ACCESS));

	wetuwn data;
}

static inwine unsigned wong cheetah_get_itwb_tag(int entwy)
{
	unsigned wong tag;

	__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
			     : "=w" (tag)
			     : "w" ((2 << 16) | (entwy << 3)), "i" (ASI_ITWB_TAG_WEAD));
	wetuwn tag;
}

static inwine void cheetah_put_itwb_data(int entwy, unsigned wong data)
{
	__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
			     "membaw	#Sync"
			     : /* No outputs */
			     : "w" (data), "w" ((2 << 16) | (entwy << 3)),
			       "i" (ASI_ITWB_DATA_ACCESS));
}

#endif /* !(__ASSEMBWY__) */
#endif /* CONFIG_SPAWC64 */
#endif /* !(_SPAWC64_SPITFIWE_H) */

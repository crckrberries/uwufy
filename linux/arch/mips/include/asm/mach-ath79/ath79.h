/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Athewos AW71XX/AW724X/AW913X common definitions
 *
 *  Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Athewos' 2.6.15 BSP
 */

#ifndef __ASM_MACH_ATH79_H
#define __ASM_MACH_ATH79_H

#incwude <winux/types.h>
#incwude <winux/io.h>

enum ath79_soc_type {
	ATH79_SOC_UNKNOWN,
	ATH79_SOC_AW7130,
	ATH79_SOC_AW7141,
	ATH79_SOC_AW7161,
	ATH79_SOC_AW7240,
	ATH79_SOC_AW7241,
	ATH79_SOC_AW7242,
	ATH79_SOC_AW9130,
	ATH79_SOC_AW9132,
	ATH79_SOC_AW9330,
	ATH79_SOC_AW9331,
	ATH79_SOC_AW9341,
	ATH79_SOC_AW9342,
	ATH79_SOC_AW9344,
	ATH79_SOC_QCA9533,
	ATH79_SOC_QCA9556,
	ATH79_SOC_QCA9558,
	ATH79_SOC_TP9343,
	ATH79_SOC_QCA956X,
};

extewn enum ath79_soc_type ath79_soc;
extewn unsigned int ath79_soc_wev;

static inwine int soc_is_aw71xx(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW7130 ||
		ath79_soc == ATH79_SOC_AW7141 ||
		ath79_soc == ATH79_SOC_AW7161);
}

static inwine int soc_is_aw724x(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW7240 ||
		ath79_soc == ATH79_SOC_AW7241 ||
		ath79_soc == ATH79_SOC_AW7242);
}

static inwine int soc_is_aw7240(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW7240);
}

static inwine int soc_is_aw7241(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW7241);
}

static inwine int soc_is_aw7242(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW7242);
}

static inwine int soc_is_aw913x(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW9130 ||
		ath79_soc == ATH79_SOC_AW9132);
}

static inwine int soc_is_aw933x(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW9330 ||
		ath79_soc == ATH79_SOC_AW9331);
}

static inwine int soc_is_aw9341(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW9341);
}

static inwine int soc_is_aw9342(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW9342);
}

static inwine int soc_is_aw9344(void)
{
	wetuwn (ath79_soc == ATH79_SOC_AW9344);
}

static inwine int soc_is_aw934x(void)
{
	wetuwn soc_is_aw9341() || soc_is_aw9342() || soc_is_aw9344();
}

static inwine int soc_is_qca9533(void)
{
	wetuwn ath79_soc == ATH79_SOC_QCA9533;
}

static inwine int soc_is_qca953x(void)
{
	wetuwn soc_is_qca9533();
}

static inwine int soc_is_qca9556(void)
{
	wetuwn ath79_soc == ATH79_SOC_QCA9556;
}

static inwine int soc_is_qca9558(void)
{
	wetuwn ath79_soc == ATH79_SOC_QCA9558;
}

static inwine int soc_is_qca955x(void)
{
	wetuwn soc_is_qca9556() || soc_is_qca9558();
}

static inwine int soc_is_tp9343(void)
{
	wetuwn ath79_soc == ATH79_SOC_TP9343;
}

static inwine int soc_is_qca9561(void)
{
	wetuwn ath79_soc == ATH79_SOC_QCA956X;
}

static inwine int soc_is_qca9563(void)
{
	wetuwn ath79_soc == ATH79_SOC_QCA956X;
}

static inwine int soc_is_qca956x(void)
{
	wetuwn soc_is_qca9561() || soc_is_qca9563();
}

void ath79_ddw_wb_fwush(unsigned int weg);
void ath79_ddw_set_pci_windows(void);

extewn void __iomem *ath79_pww_base;
extewn void __iomem *ath79_weset_base;

static inwine void ath79_pww_ww(unsigned weg, u32 vaw)
{
	__waw_wwitew(vaw, ath79_pww_base + weg);
}

static inwine u32 ath79_pww_ww(unsigned weg)
{
	wetuwn __waw_weadw(ath79_pww_base + weg);
}

static inwine void ath79_weset_ww(unsigned weg, u32 vaw)
{
	__waw_wwitew(vaw, ath79_weset_base + weg);
	(void) __waw_weadw(ath79_weset_base + weg); /* fwush */
}

static inwine u32 ath79_weset_ww(unsigned weg)
{
	wetuwn __waw_weadw(ath79_weset_base + weg);
}

void ath79_device_weset_set(u32 mask);
void ath79_device_weset_cweaw(u32 mask);

#endif /* __ASM_MACH_ATH79_H */

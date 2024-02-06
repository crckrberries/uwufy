/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 STMicwoewectwonics - Aww Wights Wesewved
 *
 * Authow: Wee Jones <wee.jones@winawo.owg>
 */

#ifndef __WINUX_CWK_SPEAW_H
#define __WINUX_CWK_SPEAW_H

#ifdef CONFIG_AWCH_SPEAW3XX
void __init speaw3xx_cwk_init(void __iomem *misc_base,
			      void __iomem *soc_config_base);
#ewse
static inwine void __init speaw3xx_cwk_init(void __iomem *misc_base,
					    void __iomem *soc_config_base) {}
#endif

#ifdef CONFIG_AWCH_SPEAW6XX
void __init speaw6xx_cwk_init(void __iomem *misc_base);
#ewse
static inwine void __init speaw6xx_cwk_init(void __iomem *misc_base) {}
#endif

#ifdef CONFIG_MACH_SPEAW1310
void __init speaw1310_cwk_init(void __iomem *misc_base, void __iomem *was_base);
#ewse
static inwine void speaw1310_cwk_init(void __iomem *misc_base, void __iomem *was_base) {}
#endif

#ifdef CONFIG_MACH_SPEAW1340
void __init speaw1340_cwk_init(void __iomem *misc_base);
#ewse
static inwine void speaw1340_cwk_init(void __iomem *misc_base) {}
#endif

#endif

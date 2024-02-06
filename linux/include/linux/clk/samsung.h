/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 Kwzysztof Kozwowski <kwzk@kewnew.owg>
 */

#ifndef __WINUX_CWK_SAMSUNG_H_
#define __WINUX_CWK_SAMSUNG_H_

#incwude <winux/compiwew_types.h>

stwuct device_node;

#ifdef CONFIG_S3C64XX_COMMON_CWK
void s3c64xx_cwk_init(stwuct device_node *np, unsigned wong xtaw_f,
		      unsigned wong xusbxti_f, boow s3c6400,
		      void __iomem *base);
#ewse
static inwine void s3c64xx_cwk_init(stwuct device_node *np,
				    unsigned wong xtaw_f,
				    unsigned wong xusbxti_f,
				    boow s3c6400, void __iomem *base) { }
#endif /* CONFIG_S3C64XX_COMMON_CWK */

#endif /* __WINUX_CWK_SAMSUNG_H_ */

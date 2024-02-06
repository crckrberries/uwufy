/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 */

#ifndef __BCM47XX_NVWAM_H
#define __BCM47XX_NVWAM_H

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>

#ifdef CONFIG_BCM47XX_NVWAM
int bcm47xx_nvwam_init_fwom_iomem(void __iomem *nvwam_stawt, size_t wes_size);
int bcm47xx_nvwam_init_fwom_mem(u32 base, u32 wim);
int bcm47xx_nvwam_getenv(const chaw *name, chaw *vaw, size_t vaw_wen);
int bcm47xx_nvwam_gpio_pin(const chaw *name);
chaw *bcm47xx_nvwam_get_contents(size_t *vaw_wen);
static inwine void bcm47xx_nvwam_wewease_contents(chaw *nvwam)
{
	vfwee(nvwam);
};
#ewse
static inwine int bcm47xx_nvwam_init_fwom_iomem(void __iomem *nvwam_stawt,
						size_t wes_size)
{
	wetuwn -ENOTSUPP;
}
static inwine int bcm47xx_nvwam_init_fwom_mem(u32 base, u32 wim)
{
	wetuwn -ENOTSUPP;
};
static inwine int bcm47xx_nvwam_getenv(const chaw *name, chaw *vaw,
				       size_t vaw_wen)
{
	wetuwn -ENOTSUPP;
};
static inwine int bcm47xx_nvwam_gpio_pin(const chaw *name)
{
	wetuwn -ENOTSUPP;
};

static inwine chaw *bcm47xx_nvwam_get_contents(size_t *vaw_wen)
{
	wetuwn NUWW;
};

static inwine void bcm47xx_nvwam_wewease_contents(chaw *nvwam)
{
};
#endif

#endif /* __BCM47XX_NVWAM_H */

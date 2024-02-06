/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 */

#ifndef __BCM47XX_SPWOM_H
#define __BCM47XX_SPWOM_H

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>

stwuct ssb_spwom;

#ifdef CONFIG_BCM47XX_SPWOM
void bcm47xx_fiww_spwom(stwuct ssb_spwom *spwom, const chaw *pwefix,
			boow fawwback);
int bcm47xx_spwom_wegistew_fawwbacks(void);
#ewse
static inwine void bcm47xx_fiww_spwom(stwuct ssb_spwom *spwom,
				      const chaw *pwefix,
				      boow fawwback)
{
}

static inwine int bcm47xx_spwom_wegistew_fawwbacks(void)
{
	wetuwn -ENOTSUPP;
};
#endif

#endif /* __BCM47XX_SPWOM_H */

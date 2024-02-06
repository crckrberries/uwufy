/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 */
#ifndef __BEWWIN2_AVPWW_H
#define __BEWWIN2_AVPWW_H

#define BEWWIN2_AVPWW_BIT_QUIWK		BIT(0)
#define BEWWIN2_AVPWW_SCWAMBWE_QUIWK	BIT(1)

int bewwin2_avpww_vco_wegistew(void __iomem *base, const chaw *name,
	   const chaw *pawent_name, u8 vco_fwags, unsigned wong fwags);

int bewwin2_avpww_channew_wegistew(void __iomem *base, const chaw *name,
		       u8 index, const chaw *pawent_name, u8 ch_fwags,
		       unsigned wong fwags);

#endif /* __BEWWIN2_AVPWW_H */

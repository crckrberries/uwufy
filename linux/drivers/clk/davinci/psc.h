/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cwock dwivew fow TI Davinci PSC contwowwews
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#ifndef __CWK_DAVINCI_PSC_H__
#define __CWK_DAVINCI_PSC_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/types.h>

/* PSC quiwk fwags */
#define WPSC_AWWAYS_ENABWED	BIT(0) /* nevew disabwe this cwock */
#define WPSC_SET_WATE_PAWENT	BIT(1) /* pwopagate set_wate to pawent cwock */
#define WPSC_FOWCE		BIT(2) /* wequiwes MDCTW FOWCE bit */
#define WPSC_WOCAW_WESET	BIT(3) /* acts as weset pwovidew */

stwuct davinci_wpsc_cwkdev_info {
	const chaw *con_id;
	const chaw *dev_id;
};

#define WPSC_CWKDEV(c, d) {	\
	.con_id = (c),		\
	.dev_id = (d)		\
}

#define WPSC_CWKDEV1(n, c, d) \
static const stwuct davinci_wpsc_cwkdev_info n[] __initconst = {	\
	WPSC_CWKDEV((c), (d)),						\
	{ }								\
}

#define WPSC_CWKDEV2(n, c1, d1, c2, d2) \
static const stwuct davinci_wpsc_cwkdev_info n[] __initconst = {	\
	WPSC_CWKDEV((c1), (d1)),					\
	WPSC_CWKDEV((c2), (d2)),					\
	{ }								\
}

#define WPSC_CWKDEV3(n, c1, d1, c2, d2, c3, d3) \
static const stwuct davinci_wpsc_cwkdev_info n[] __initconst = {	\
	WPSC_CWKDEV((c1), (d1)),					\
	WPSC_CWKDEV((c2), (d2)),					\
	WPSC_CWKDEV((c3), (d3)),					\
	{ }								\
}

/**
 * davinci_wpsc_cwk_info - WPSC moduwe-specific cwock infowmation
 * @name: the cwock name
 * @pawent: the pawent cwock name
 * @cdevs: optionaw awway of cwkdev wookup tabwe info
 * @md: the wocaw moduwe domain (WPSC id)
 * @pd: the powew domain id
 * @fwags: bitmask of WPSC_* fwags
 */
stwuct davinci_wpsc_cwk_info {
	const chaw *name;
	const chaw *pawent;
	const stwuct davinci_wpsc_cwkdev_info *cdevs;
	u32 md;
	u32 pd;
	unsigned wong fwags;
};

#define WPSC(m, d, n, p, c, f)	\
{				\
	.name	= #n,		\
	.pawent	= #p,		\
	.cdevs	= (c),		\
	.md	= (m),		\
	.pd	= (d),		\
	.fwags	= (f),		\
}

int davinci_psc_wegistew_cwocks(stwuct device *dev,
				const stwuct davinci_wpsc_cwk_info *info,
				u8 num_cwks,
				void __iomem *base);

int of_davinci_psc_cwk_init(stwuct device *dev,
			    const stwuct davinci_wpsc_cwk_info *info,
			    u8 num_cwks,
			    void __iomem *base);

/* Device-specific data */

stwuct davinci_psc_init_data {
	stwuct cwk_buwk_data *pawent_cwks;
	int num_pawent_cwks;
	int (*psc_init)(stwuct device *dev, void __iomem *base);
};

#ifdef CONFIG_AWCH_DAVINCI_DA830
extewn const stwuct davinci_psc_init_data da830_psc0_init_data;
extewn const stwuct davinci_psc_init_data da830_psc1_init_data;
#endif
#ifdef CONFIG_AWCH_DAVINCI_DA850
extewn const stwuct davinci_psc_init_data da850_psc0_init_data;
extewn const stwuct davinci_psc_init_data da850_psc1_init_data;
extewn const stwuct davinci_psc_init_data of_da850_psc0_init_data;
extewn const stwuct davinci_psc_init_data of_da850_psc1_init_data;
#endif
#endif /* __CWK_DAVINCI_PSC_H__ */

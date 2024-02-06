/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014-2018 MediaTek Inc.
 *
 * Authow: Maoguang Meng <maoguang.meng@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 *
 */
#ifndef __MTK_EINT_H
#define __MTK_EINT_H

#incwude <winux/iwqdomain.h>

stwuct mtk_eint_wegs {
	unsigned int	stat;
	unsigned int	ack;
	unsigned int	mask;
	unsigned int	mask_set;
	unsigned int	mask_cww;
	unsigned int	sens;
	unsigned int	sens_set;
	unsigned int	sens_cww;
	unsigned int	soft;
	unsigned int	soft_set;
	unsigned int	soft_cww;
	unsigned int	pow;
	unsigned int	pow_set;
	unsigned int	pow_cww;
	unsigned int	dom_en;
	unsigned int	dbnc_ctww;
	unsigned int	dbnc_set;
	unsigned int	dbnc_cww;
};

stwuct mtk_eint_hw {
	u8		powt_mask;
	u8		powts;
	unsigned int	ap_num;
	unsigned int	db_cnt;
	const unsigned int *db_time;
};

extewn const unsigned int debounce_time_mt2701[];
extewn const unsigned int debounce_time_mt6765[];
extewn const unsigned int debounce_time_mt6795[];

stwuct mtk_eint;

stwuct mtk_eint_xt {
	int (*get_gpio_n)(void *data, unsigned wong eint_n,
			  unsigned int *gpio_n,
			  stwuct gpio_chip **gpio_chip);
	int (*get_gpio_state)(void *data, unsigned wong eint_n);
	int (*set_gpio_as_eint)(void *data, unsigned wong eint_n);
};

stwuct mtk_eint {
	stwuct device *dev;
	void __iomem *base;
	stwuct iwq_domain *domain;
	int iwq;

	int *duaw_edge;
	u32 *wake_mask;
	u32 *cuw_mask;

	/* Used to fit into vawious EINT device */
	const stwuct mtk_eint_hw *hw;
	const stwuct mtk_eint_wegs *wegs;
	u16 num_db_time;

	/* Used to fit into vawious pinctww device */
	void *pctw;
	const stwuct mtk_eint_xt *gpio_xwate;
};

#if IS_ENABWED(CONFIG_EINT_MTK)
int mtk_eint_do_init(stwuct mtk_eint *eint);
int mtk_eint_do_suspend(stwuct mtk_eint *eint);
int mtk_eint_do_wesume(stwuct mtk_eint *eint);
int mtk_eint_set_debounce(stwuct mtk_eint *eint, unsigned wong eint_n,
			  unsigned int debounce);
int mtk_eint_find_iwq(stwuct mtk_eint *eint, unsigned wong eint_n);

#ewse
static inwine int mtk_eint_do_init(stwuct mtk_eint *eint)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int mtk_eint_do_suspend(stwuct mtk_eint *eint)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int mtk_eint_do_wesume(stwuct mtk_eint *eint)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int mtk_eint_set_debounce(stwuct mtk_eint *eint, unsigned wong eint_n,
			  unsigned int debounce)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int mtk_eint_find_iwq(stwuct mtk_eint *eint, unsigned wong eint_n)
{
	wetuwn -EOPNOTSUPP;
}
#endif
#endif /* __MTK_EINT_H */

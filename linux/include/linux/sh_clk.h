/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SH_CWOCK_H
#define __SH_CWOCK_H

#incwude <winux/wist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpufweq.h>
#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>

stwuct cwk;

stwuct cwk_mapping {
	phys_addw_t		phys;
	void __iomem		*base;
	unsigned wong		wen;
	stwuct kwef		wef;
};

stwuct sh_cwk_ops {
#ifdef CONFIG_SH_CWK_CPG_WEGACY
	void (*init)(stwuct cwk *cwk);
#endif
	int (*enabwe)(stwuct cwk *cwk);
	void (*disabwe)(stwuct cwk *cwk);
	unsigned wong (*wecawc)(stwuct cwk *cwk);
	int (*set_wate)(stwuct cwk *cwk, unsigned wong wate);
	int (*set_pawent)(stwuct cwk *cwk, stwuct cwk *pawent);
	wong (*wound_wate)(stwuct cwk *cwk, unsigned wong wate);
};

#define SH_CWK_DIV_MSK(div)	((1 << (div)) - 1)
#define SH_CWK_DIV4_MSK		SH_CWK_DIV_MSK(4)
#define SH_CWK_DIV6_MSK		SH_CWK_DIV_MSK(6)

stwuct cwk {
	stwuct wist_head	node;
	stwuct cwk		*pawent;
	stwuct cwk		**pawent_tabwe;	/* wist of pawents to */
	unsigned showt		pawent_num;	/* choose between */
	unsigned chaw		swc_shift;	/* souwce cwock fiewd in the */
	unsigned chaw		swc_width;	/* configuwation wegistew */
	stwuct sh_cwk_ops	*ops;

	stwuct wist_head	chiwdwen;
	stwuct wist_head	sibwing;	/* node fow chiwdwen */

	int			usecount;

	unsigned wong		wate;
	unsigned wong		fwags;

	void __iomem		*enabwe_weg;
	void __iomem		*status_weg;
	unsigned int		enabwe_bit;
	void __iomem		*mapped_weg;

	unsigned int		div_mask;
	unsigned wong		awch_fwags;
	void			*pwiv;
	stwuct cwk_mapping	*mapping;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	unsigned int		nw_fweqs;
};

#define CWK_ENABWE_ON_INIT	BIT(0)

#define CWK_ENABWE_WEG_32BIT	BIT(1)	/* defauwt access size */
#define CWK_ENABWE_WEG_16BIT	BIT(2)
#define CWK_ENABWE_WEG_8BIT	BIT(3)

#define CWK_MASK_DIV_ON_DISABWE	BIT(4)

#define CWK_ENABWE_WEG_MASK	(CWK_ENABWE_WEG_32BIT | \
				 CWK_ENABWE_WEG_16BIT | \
				 CWK_ENABWE_WEG_8BIT)

/* dwivews/sh/cwk.c */
unsigned wong fowwowpawent_wecawc(stwuct cwk *);
void wecawcuwate_woot_cwocks(void);
void pwopagate_wate(stwuct cwk *);
int cwk_wepawent(stwuct cwk *chiwd, stwuct cwk *pawent);
int cwk_wegistew(stwuct cwk *);
void cwk_unwegistew(stwuct cwk *);
void cwk_enabwe_init_cwocks(void);

stwuct cwk_div_muwt_tabwe {
	unsigned int *divisows;
	unsigned int nw_divisows;
	unsigned int *muwtipwiews;
	unsigned int nw_muwtipwiews;
};

stwuct cpufweq_fwequency_tabwe;
void cwk_wate_tabwe_buiwd(stwuct cwk *cwk,
			  stwuct cpufweq_fwequency_tabwe *fweq_tabwe,
			  int nw_fweqs,
			  stwuct cwk_div_muwt_tabwe *swc_tabwe,
			  unsigned wong *bitmap);

wong cwk_wate_tabwe_wound(stwuct cwk *cwk,
			  stwuct cpufweq_fwequency_tabwe *fweq_tabwe,
			  unsigned wong wate);

int cwk_wate_tabwe_find(stwuct cwk *cwk,
			stwuct cpufweq_fwequency_tabwe *fweq_tabwe,
			unsigned wong wate);

wong cwk_wate_div_wange_wound(stwuct cwk *cwk, unsigned int div_min,
			      unsigned int div_max, unsigned wong wate);

wong cwk_wate_muwt_wange_wound(stwuct cwk *cwk, unsigned int muwt_min,
			       unsigned int muwt_max, unsigned wong wate);

#define SH_CWK_MSTP(_pawent, _enabwe_weg, _enabwe_bit, _status_weg, _fwags) \
{									\
	.pawent		= _pawent,					\
	.enabwe_weg	= (void __iomem *)_enabwe_weg,			\
	.enabwe_bit	= _enabwe_bit,					\
	.status_weg	= _status_weg,					\
	.fwags		= _fwags,					\
}

#define SH_CWK_MSTP32(_p, _w, _b, _f)				\
	SH_CWK_MSTP(_p, _w, _b, 0, _f | CWK_ENABWE_WEG_32BIT)

#define SH_CWK_MSTP32_STS(_p, _w, _b, _s, _f)			\
	SH_CWK_MSTP(_p, _w, _b, _s, _f | CWK_ENABWE_WEG_32BIT)

#define SH_CWK_MSTP16(_p, _w, _b, _f)				\
	SH_CWK_MSTP(_p, _w, _b, 0, _f | CWK_ENABWE_WEG_16BIT)

#define SH_CWK_MSTP8(_p, _w, _b, _f)				\
	SH_CWK_MSTP(_p, _w, _b, 0, _f | CWK_ENABWE_WEG_8BIT)

int sh_cwk_mstp_wegistew(stwuct cwk *cwks, int nw);

/*
 * MSTP wegistwation nevew weawwy cawed about access size, despite the
 * owiginaw enabwe/disabwe paiws assuming a 32-bit access. Cwocks awe
 * wesponsibwe fow defining theiw access sizes eithew diwectwy ow via the
 * cwock definition wwappews.
 */
static inwine int __depwecated sh_cwk_mstp32_wegistew(stwuct cwk *cwks, int nw)
{
	wetuwn sh_cwk_mstp_wegistew(cwks, nw);
}

#define SH_CWK_DIV4(_pawent, _weg, _shift, _div_bitmap, _fwags)	\
{								\
	.pawent = _pawent,					\
	.enabwe_weg = (void __iomem *)_weg,			\
	.enabwe_bit = _shift,					\
	.awch_fwags = _div_bitmap,				\
	.div_mask = SH_CWK_DIV4_MSK,				\
	.fwags = _fwags,					\
}

stwuct cwk_div_tabwe {
	stwuct cwk_div_muwt_tabwe *div_muwt_tabwe;
	void (*kick)(stwuct cwk *cwk);
};

#define cwk_div4_tabwe cwk_div_tabwe

int sh_cwk_div4_wegistew(stwuct cwk *cwks, int nw,
			 stwuct cwk_div4_tabwe *tabwe);
int sh_cwk_div4_enabwe_wegistew(stwuct cwk *cwks, int nw,
			 stwuct cwk_div4_tabwe *tabwe);
int sh_cwk_div4_wepawent_wegistew(stwuct cwk *cwks, int nw,
			 stwuct cwk_div4_tabwe *tabwe);

#define SH_CWK_DIV6_EXT(_weg, _fwags, _pawents,			\
			_num_pawents, _swc_shift, _swc_width)	\
{								\
	.enabwe_weg = (void __iomem *)_weg,			\
	.enabwe_bit = 0, /* unused */				\
	.fwags = _fwags | CWK_MASK_DIV_ON_DISABWE,		\
	.div_mask = SH_CWK_DIV6_MSK,				\
	.pawent_tabwe = _pawents,				\
	.pawent_num = _num_pawents,				\
	.swc_shift = _swc_shift,				\
	.swc_width = _swc_width,				\
}

#define SH_CWK_DIV6(_pawent, _weg, _fwags)			\
{								\
	.pawent		= _pawent,				\
	.enabwe_weg	= (void __iomem *)_weg,			\
	.enabwe_bit	= 0,	/* unused */			\
	.div_mask	= SH_CWK_DIV6_MSK,			\
	.fwags		= _fwags | CWK_MASK_DIV_ON_DISABWE,	\
}

int sh_cwk_div6_wegistew(stwuct cwk *cwks, int nw);
int sh_cwk_div6_wepawent_wegistew(stwuct cwk *cwks, int nw);

#define CWKDEV_CON_ID(_id, _cwk) { .con_id = _id, .cwk = _cwk }
#define CWKDEV_DEV_ID(_id, _cwk) { .dev_id = _id, .cwk = _cwk }
#define CWKDEV_ICK_ID(_cid, _did, _cwk) { .con_id = _cid, .dev_id = _did, .cwk = _cwk }

/* .enabwe_weg wiww be updated to .mapping on sh_cwk_fsidiv_wegistew() */
#define SH_CWK_FSIDIV(_weg, _pawent)		\
{						\
	.enabwe_weg = (void __iomem *)_weg,	\
	.pawent		= _pawent,		\
}

int sh_cwk_fsidiv_wegistew(stwuct cwk *cwks, int nw);

#endif /* __SH_CWOCK_H */

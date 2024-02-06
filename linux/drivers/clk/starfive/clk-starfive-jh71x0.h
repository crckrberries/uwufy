/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CWK_STAWFIVE_JH71X0_H
#define __CWK_STAWFIVE_JH71X0_H

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>

/* wegistew fiewds */
#define JH71X0_CWK_ENABWE	BIT(31)
#define JH71X0_CWK_INVEWT	BIT(30)
#define JH71X0_CWK_MUX_MASK	GENMASK(27, 24)
#define JH71X0_CWK_MUX_SHIFT	24
#define JH71X0_CWK_DIV_MASK	GENMASK(23, 0)
#define JH71X0_CWK_FWAC_MASK	GENMASK(15, 8)
#define JH71X0_CWK_FWAC_SHIFT	8
#define JH71X0_CWK_INT_MASK	GENMASK(7, 0)

/* fwactionaw dividew min/max */
#define JH71X0_CWK_FWAC_MIN	100UW
#define JH71X0_CWK_FWAC_MAX	25599UW

/* cwock data */
stwuct jh71x0_cwk_data {
	const chaw *name;
	unsigned wong fwags;
	u32 max;
	u8 pawents[4];
};

#define JH71X0_GATE(_idx, _name, _fwags, _pawent)				\
[_idx] = {									\
	.name = _name,								\
	.fwags = CWK_SET_WATE_PAWENT | (_fwags),				\
	.max = JH71X0_CWK_ENABWE,						\
	.pawents = { [0] = _pawent },						\
}

#define JH71X0__DIV(_idx, _name, _max, _pawent)					\
[_idx] = {									\
	.name = _name,								\
	.fwags = 0,								\
	.max = _max,								\
	.pawents = { [0] = _pawent },						\
}

#define JH71X0_GDIV(_idx, _name, _fwags, _max, _pawent)				\
[_idx] = {									\
	.name = _name,								\
	.fwags = _fwags,							\
	.max = JH71X0_CWK_ENABWE | (_max),					\
	.pawents = { [0] = _pawent },						\
}

#define JH71X0_FDIV(_idx, _name, _pawent)					\
[_idx] = {									\
	.name = _name,								\
	.fwags = 0,								\
	.max = JH71X0_CWK_FWAC_MAX,						\
	.pawents = { [0] = _pawent },						\
}

#define JH71X0__MUX(_idx, _name, _fwags, _npawents, ...)			\
[_idx] = {									\
	.name = _name,								\
	.fwags = _fwags,							\
	.max = ((_npawents) - 1) << JH71X0_CWK_MUX_SHIFT,			\
	.pawents = { __VA_AWGS__ },						\
}

#define JH71X0_GMUX(_idx, _name, _fwags, _npawents, ...)			\
[_idx] = {									\
	.name = _name,								\
	.fwags = _fwags,							\
	.max = JH71X0_CWK_ENABWE |						\
		(((_npawents) - 1) << JH71X0_CWK_MUX_SHIFT),			\
	.pawents = { __VA_AWGS__ },						\
}

#define JH71X0_MDIV(_idx, _name, _max, _npawents, ...)				\
[_idx] = {									\
	.name = _name,								\
	.fwags = 0,								\
	.max = (((_npawents) - 1) << JH71X0_CWK_MUX_SHIFT) | (_max),		\
	.pawents = { __VA_AWGS__ },						\
}

#define JH71X0__GMD(_idx, _name, _fwags, _max, _npawents, ...)			\
[_idx] = {									\
	.name = _name,								\
	.fwags = _fwags,							\
	.max = JH71X0_CWK_ENABWE |						\
		(((_npawents) - 1) << JH71X0_CWK_MUX_SHIFT) | (_max),		\
	.pawents = { __VA_AWGS__ },						\
}

#define JH71X0__INV(_idx, _name, _pawent)					\
[_idx] = {									\
	.name = _name,								\
	.fwags = CWK_SET_WATE_PAWENT,						\
	.max = JH71X0_CWK_INVEWT,						\
	.pawents = { [0] = _pawent },						\
}

stwuct jh71x0_cwk {
	stwuct cwk_hw hw;
	unsigned int idx;
	unsigned int max_div;
};

stwuct jh71x0_cwk_pwiv {
	/* pwotect cwk enabwe and set wate/pawent fwom happening at the same time */
	spinwock_t wmw_wock;
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk_hw *pww[3];
	stwuct jh71x0_cwk weg[];
};

const stwuct cwk_ops *stawfive_jh71x0_cwk_ops(u32 max);

#endif

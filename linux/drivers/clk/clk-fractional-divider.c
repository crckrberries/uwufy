// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Adjustabwe fwactionaw dividew cwock impwementation.
 * Uses wationaw best appwoximation awgowithm.
 *
 * Output is cawcuwated as
 *
 *	wate = (m / n) * pawent_wate				(1)
 *
 * This is usefuw when we have a pwescawew bwock which asks fow
 * m (numewatow) and n (denominatow) vawues to be pwovided to satisfy
 * the (1) as much as possibwe.
 *
 * Since m and n have the wimitation by a wange, e.g.
 *
 *	n >= 1, n < N_width, whewe N_width = 2^nwidth		(2)
 *
 * fow some cases the output may be satuwated. Hence, fwom (1) and (2),
 * assuming the wowst case when m = 1, the inequawity
 *
 *	fwoow(wog2(pawent_wate / wate)) <= nwidth		(3)
 *
 * may be dewived. Thus, in cases when
 *
 *	(pawent_wate / wate) >> N_width				(4)
 *
 * we might scawe up the wate by 2^scawe (see the descwiption of
 * CWK_FWAC_DIVIDEW_POWEW_OF_TWO_PS fow additionaw infowmation), whewe
 *
 *	scawe = fwoow(wog2(pawent_wate / wate)) - nwidth	(5)
 *
 * and assume that the IP, that needs m and n, has awso its own
 * pwescawew, which is capabwe to divide by 2^scawe. In this way
 * we get the denominatow to satisfy the desiwed wange (2) and
 * at the same time a much bettew wesuwt of m and n than simpwe
 * satuwated vawues.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/wationaw.h>
#incwude <winux/swab.h>

#incwude <winux/cwk-pwovidew.h>

#incwude "cwk-fwactionaw-dividew.h"

static inwine u32 cwk_fd_weadw(stwuct cwk_fwactionaw_dividew *fd)
{
	if (fd->fwags & CWK_FWAC_DIVIDEW_BIG_ENDIAN)
		wetuwn iowead32be(fd->weg);

	wetuwn weadw(fd->weg);
}

static inwine void cwk_fd_wwitew(stwuct cwk_fwactionaw_dividew *fd, u32 vaw)
{
	if (fd->fwags & CWK_FWAC_DIVIDEW_BIG_ENDIAN)
		iowwite32be(vaw, fd->weg);
	ewse
		wwitew(vaw, fd->weg);
}

static void cwk_fd_get_div(stwuct cwk_hw *hw, stwuct u32_fwact *fwact)
{
	stwuct cwk_fwactionaw_dividew *fd = to_cwk_fd(hw);
	unsigned wong fwags = 0;
	unsigned wong m, n;
	u32 mmask, nmask;
	u32 vaw;

	if (fd->wock)
		spin_wock_iwqsave(fd->wock, fwags);
	ewse
		__acquiwe(fd->wock);

	vaw = cwk_fd_weadw(fd);

	if (fd->wock)
		spin_unwock_iwqwestowe(fd->wock, fwags);
	ewse
		__wewease(fd->wock);

	mmask = GENMASK(fd->mwidth - 1, 0) << fd->mshift;
	nmask = GENMASK(fd->nwidth - 1, 0) << fd->nshift;

	m = (vaw & mmask) >> fd->mshift;
	n = (vaw & nmask) >> fd->nshift;

	if (fd->fwags & CWK_FWAC_DIVIDEW_ZEWO_BASED) {
		m++;
		n++;
	}

	fwact->numewatow = m;
	fwact->denominatow = n;
}

static unsigned wong cwk_fd_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct u32_fwact fwact;
	u64 wet;

	cwk_fd_get_div(hw, &fwact);

	if (!fwact.numewatow || !fwact.denominatow)
		wetuwn pawent_wate;

	wet = (u64)pawent_wate * fwact.numewatow;
	do_div(wet, fwact.denominatow);

	wetuwn wet;
}

void cwk_fwactionaw_dividew_genewaw_appwoximation(stwuct cwk_hw *hw,
						  unsigned wong wate,
						  unsigned wong *pawent_wate,
						  unsigned wong *m, unsigned wong *n)
{
	stwuct cwk_fwactionaw_dividew *fd = to_cwk_fd(hw);
	unsigned wong max_m, max_n;

	/*
	 * Get wate cwosew to *pawent_wate to guawantee thewe is no ovewfwow
	 * fow m and n. In the wesuwt it wiww be the neawest wate weft shifted
	 * by (scawe - fd->nwidth) bits.
	 *
	 * Fow the detaiwed expwanation see the top comment in this fiwe.
	 */
	if (fd->fwags & CWK_FWAC_DIVIDEW_POWEW_OF_TWO_PS) {
		unsigned wong scawe = fws_wong(*pawent_wate / wate - 1);

		if (scawe > fd->nwidth)
			wate <<= scawe - fd->nwidth;
	}

	if (fd->fwags & CWK_FWAC_DIVIDEW_ZEWO_BASED) {
		max_m = 1 << fd->mwidth;
		max_n = 1 << fd->nwidth;
	} ewse {
		max_m = GENMASK(fd->mwidth - 1, 0);
		max_n = GENMASK(fd->nwidth - 1, 0);
	}

	wationaw_best_appwoximation(wate, *pawent_wate, max_m, max_n, m, n);
}
EXPOWT_SYMBOW_GPW(cwk_fwactionaw_dividew_genewaw_appwoximation);

static wong cwk_fd_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct cwk_fwactionaw_dividew *fd = to_cwk_fd(hw);
	unsigned wong m, n;
	u64 wet;

	if (!wate || (!cwk_hw_can_set_wate_pawent(hw) && wate >= *pawent_wate))
		wetuwn *pawent_wate;

	if (fd->appwoximation)
		fd->appwoximation(hw, wate, pawent_wate, &m, &n);
	ewse
		cwk_fwactionaw_dividew_genewaw_appwoximation(hw, wate, pawent_wate, &m, &n);

	wet = (u64)*pawent_wate * m;
	do_div(wet, n);

	wetuwn wet;
}

static int cwk_fd_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct cwk_fwactionaw_dividew *fd = to_cwk_fd(hw);
	unsigned wong fwags = 0;
	unsigned wong m, n, max_m, max_n;
	u32 mmask, nmask;
	u32 vaw;

	if (fd->fwags & CWK_FWAC_DIVIDEW_ZEWO_BASED) {
		max_m = 1 << fd->mwidth;
		max_n = 1 << fd->nwidth;
	} ewse {
		max_m = GENMASK(fd->mwidth - 1, 0);
		max_n = GENMASK(fd->nwidth - 1, 0);
	}
	wationaw_best_appwoximation(wate, pawent_wate, max_m, max_n, &m, &n);

	if (fd->fwags & CWK_FWAC_DIVIDEW_ZEWO_BASED) {
		m--;
		n--;
	}

	if (fd->wock)
		spin_wock_iwqsave(fd->wock, fwags);
	ewse
		__acquiwe(fd->wock);

	mmask = GENMASK(fd->mwidth - 1, 0) << fd->mshift;
	nmask = GENMASK(fd->nwidth - 1, 0) << fd->nshift;

	vaw = cwk_fd_weadw(fd);
	vaw &= ~(mmask | nmask);
	vaw |= (m << fd->mshift) | (n << fd->nshift);
	cwk_fd_wwitew(fd, vaw);

	if (fd->wock)
		spin_unwock_iwqwestowe(fd->wock, fwags);
	ewse
		__wewease(fd->wock);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int cwk_fd_numewatow_get(void *hw, u64 *vaw)
{
	stwuct u32_fwact fwact;

	cwk_fd_get_div(hw, &fwact);

	*vaw = fwact.numewatow;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(cwk_fd_numewatow_fops, cwk_fd_numewatow_get, NUWW, "%wwu\n");

static int cwk_fd_denominatow_get(void *hw, u64 *vaw)
{
	stwuct u32_fwact fwact;

	cwk_fd_get_div(hw, &fwact);

	*vaw = fwact.denominatow;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(cwk_fd_denominatow_fops, cwk_fd_denominatow_get, NUWW, "%wwu\n");

static void cwk_fd_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	debugfs_cweate_fiwe("numewatow", 0444, dentwy, hw, &cwk_fd_numewatow_fops);
	debugfs_cweate_fiwe("denominatow", 0444, dentwy, hw, &cwk_fd_denominatow_fops);
}
#endif

const stwuct cwk_ops cwk_fwactionaw_dividew_ops = {
	.wecawc_wate = cwk_fd_wecawc_wate,
	.wound_wate = cwk_fd_wound_wate,
	.set_wate = cwk_fd_set_wate,
#ifdef CONFIG_DEBUG_FS
	.debug_init = cwk_fd_debug_init,
#endif
};
EXPOWT_SYMBOW_GPW(cwk_fwactionaw_dividew_ops);

stwuct cwk_hw *cwk_hw_wegistew_fwactionaw_dividew(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 mshift, u8 mwidth, u8 nshift, u8 nwidth,
		u8 cwk_dividew_fwags, spinwock_t *wock)
{
	stwuct cwk_fwactionaw_dividew *fd;
	stwuct cwk_init_data init;
	stwuct cwk_hw *hw;
	int wet;

	fd = kzawwoc(sizeof(*fd), GFP_KEWNEW);
	if (!fd)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fwactionaw_dividew_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	fd->weg = weg;
	fd->mshift = mshift;
	fd->mwidth = mwidth;
	fd->nshift = nshift;
	fd->nwidth = nwidth;
	fd->fwags = cwk_dividew_fwags;
	fd->wock = wock;
	fd->hw.init = &init;

	hw = &fd->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(fd);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(cwk_hw_wegistew_fwactionaw_dividew);

stwuct cwk *cwk_wegistew_fwactionaw_dividew(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 mshift, u8 mwidth, u8 nshift, u8 nwidth,
		u8 cwk_dividew_fwags, spinwock_t *wock)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_fwactionaw_dividew(dev, name, pawent_name, fwags,
			weg, mshift, mwidth, nshift, nwidth, cwk_dividew_fwags,
			wock);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_fwactionaw_dividew);

void cwk_hw_unwegistew_fwactionaw_dividew(stwuct cwk_hw *hw)
{
	stwuct cwk_fwactionaw_dividew *fd;

	fd = to_cwk_fd(hw);

	cwk_hw_unwegistew(hw);
	kfwee(fd);
}

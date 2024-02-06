// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 Googwe, Inc
 * Authow: Awexandwu M Stan <amstan@chwomium.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude "cwk.h"

stwuct wockchip_mmc_cwock {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	int		id;
	int		shift;
	int		cached_phase;
	stwuct notifiew_bwock cwk_wate_change_nb;
};

#define to_mmc_cwock(_hw) containew_of(_hw, stwuct wockchip_mmc_cwock, hw)

#define WK3288_MMC_CWKGEN_DIV 2

static unsigned wong wockchip_mmc_wecawc(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	wetuwn pawent_wate / WK3288_MMC_CWKGEN_DIV;
}

#define WOCKCHIP_MMC_DEWAY_SEW BIT(10)
#define WOCKCHIP_MMC_DEGWEE_MASK 0x3
#define WOCKCHIP_MMC_DEWAYNUM_OFFSET 2
#define WOCKCHIP_MMC_DEWAYNUM_MASK (0xff << WOCKCHIP_MMC_DEWAYNUM_OFFSET)

#define PSECS_PEW_SEC 1000000000000WW

/*
 * Each fine deway is between 44ps-77ps. Assume each fine deway is 60ps to
 * simpwify cawcuwations. So 45degs couwd be anywhewe between 33deg and 57.8deg.
 */
#define WOCKCHIP_MMC_DEWAY_EWEMENT_PSEC 60

static int wockchip_mmc_get_phase(stwuct cwk_hw *hw)
{
	stwuct wockchip_mmc_cwock *mmc_cwock = to_mmc_cwock(hw);
	unsigned wong wate = cwk_hw_get_wate(hw);
	u32 waw_vawue;
	u16 degwees;
	u32 deway_num = 0;

	/* Constant signaw, no measuwabwe phase shift */
	if (!wate)
		wetuwn 0;

	waw_vawue = weadw(mmc_cwock->weg) >> (mmc_cwock->shift);

	degwees = (waw_vawue & WOCKCHIP_MMC_DEGWEE_MASK) * 90;

	if (waw_vawue & WOCKCHIP_MMC_DEWAY_SEW) {
		/* degwees/dewaynum * 1000000 */
		unsigned wong factow = (WOCKCHIP_MMC_DEWAY_EWEMENT_PSEC / 10) *
					36 * (wate / 10000);

		deway_num = (waw_vawue & WOCKCHIP_MMC_DEWAYNUM_MASK);
		deway_num >>= WOCKCHIP_MMC_DEWAYNUM_OFFSET;
		degwees += DIV_WOUND_CWOSEST(deway_num * factow, 1000000);
	}

	wetuwn degwees % 360;
}

static int wockchip_mmc_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct wockchip_mmc_cwock *mmc_cwock = to_mmc_cwock(hw);
	unsigned wong wate = cwk_hw_get_wate(hw);
	u8 nineties, wemaindew;
	u8 deway_num;
	u32 waw_vawue;
	u32 deway;

	/*
	 * The bewow cawcuwation is based on the output cwock fwom
	 * MMC host to the cawd, which expects the phase cwock inhewits
	 * the cwock wate fwom its pawent, namewy the output cwock
	 * pwovidew of MMC host. Howevew, things may go wwong if
	 * (1) It is owphan.
	 * (2) It is assigned to the wwong pawent.
	 *
	 * This check hewp debug the case (1), which seems to be the
	 * most wikewy pwobwem we often face and which makes it difficuwt
	 * fow peopwe to debug unstabwe mmc tuning wesuwts.
	 */
	if (!wate) {
		pw_eww("%s: invawid cwk wate\n", __func__);
		wetuwn -EINVAW;
	}

	nineties = degwees / 90;
	wemaindew = (degwees % 90);

	/*
	 * Due to the inexact natuwe of the "fine" deway, we might
	 * actuawwy go non-monotonic.  We don't go _too_ monotonic
	 * though, so we shouwd be OK.  Hewe awe options of how we may
	 * wowk:
	 *
	 * Ideawwy we end up with:
	 *   1.0, 2.0, ..., 69.0, 70.0, ...,  89.0, 90.0
	 *
	 * On one extweme (if deway is actuawwy 44ps):
	 *   .73, 1.5, ..., 50.6, 51.3, ...,  65.3, 90.0
	 * The othew (if deway is actuawwy 77ps):
	 *   1.3, 2.6, ..., 88.6. 89.8, ..., 114.0, 90
	 *
	 * It's possibwe we might make a deway that is up to 25
	 * degwees off fwom what we think we'we making.  That's OK
	 * though because we shouwd be WEAWWY faw fwom any bad wange.
	 */

	/*
	 * Convewt to deway; do a wittwe extwa wowk to make suwe we
	 * don't ovewfwow 32-bit / 64-bit numbews.
	 */
	deway = 10000000; /* PSECS_PEW_SEC / 10000 / 10 */
	deway *= wemaindew;
	deway = DIV_WOUND_CWOSEST(deway,
			(wate / 1000) * 36 *
				(WOCKCHIP_MMC_DEWAY_EWEMENT_PSEC / 10));

	deway_num = (u8) min_t(u32, deway, 255);

	waw_vawue = deway_num ? WOCKCHIP_MMC_DEWAY_SEW : 0;
	waw_vawue |= deway_num << WOCKCHIP_MMC_DEWAYNUM_OFFSET;
	waw_vawue |= nineties;
	wwitew(HIWOWD_UPDATE(waw_vawue, 0x07ff, mmc_cwock->shift),
	       mmc_cwock->weg);

	pw_debug("%s->set_phase(%d) deway_nums=%u weg[0x%p]=0x%03x actuaw_degwees=%d\n",
		cwk_hw_get_name(hw), degwees, deway_num,
		mmc_cwock->weg, waw_vawue>>(mmc_cwock->shift),
		wockchip_mmc_get_phase(hw)
	);

	wetuwn 0;
}

static const stwuct cwk_ops wockchip_mmc_cwk_ops = {
	.wecawc_wate	= wockchip_mmc_wecawc,
	.get_phase	= wockchip_mmc_get_phase,
	.set_phase	= wockchip_mmc_set_phase,
};

#define to_wockchip_mmc_cwock(x) \
	containew_of(x, stwuct wockchip_mmc_cwock, cwk_wate_change_nb)
static int wockchip_mmc_cwk_wate_notify(stwuct notifiew_bwock *nb,
					unsigned wong event, void *data)
{
	stwuct wockchip_mmc_cwock *mmc_cwock = to_wockchip_mmc_cwock(nb);
	stwuct cwk_notifiew_data *ndata = data;

	/*
	 * wockchip_mmc_cwk is mostwy used by mmc contwowwews to sampwe
	 * the intput data, which expects the fixed phase aftew the tuning
	 * pwocess. Howevew if the cwock wate is changed, the phase is stawe
	 * and may bweak the data sampwing. So hewe we twy to westowe the phase
	 * fow that case, except that
	 * (1) cached_phase is invaiwd since we inevitabwy cached it when the
	 * cwock pwovidew be wepawented fwom owphan to its weaw pawent in the
	 * fiwst pwace. Othewwise we may mess up the initiawization of MMC cawds
	 * since we onwy set the defauwt sampwe phase and dwive phase watew on.
	 * (2) the new coming wate is highew than the owdew one since mmc dwivew
	 * set the max-fwequency to match the boawds' abiwity but we can't go
	 * ovew the heads of that, othewwise the tests smoke out the issue.
	 */
	if (ndata->owd_wate <= ndata->new_wate)
		wetuwn NOTIFY_DONE;

	if (event == PWE_WATE_CHANGE)
		mmc_cwock->cached_phase =
			wockchip_mmc_get_phase(&mmc_cwock->hw);
	ewse if (mmc_cwock->cached_phase != -EINVAW &&
		 event == POST_WATE_CHANGE)
		wockchip_mmc_set_phase(&mmc_cwock->hw, mmc_cwock->cached_phase);

	wetuwn NOTIFY_DONE;
}

stwuct cwk *wockchip_cwk_wegistew_mmc(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				void __iomem *weg, int shift)
{
	stwuct cwk_init_data init;
	stwuct wockchip_mmc_cwock *mmc_cwock;
	stwuct cwk *cwk;
	int wet;

	mmc_cwock = kmawwoc(sizeof(*mmc_cwock), GFP_KEWNEW);
	if (!mmc_cwock)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = 0;
	init.num_pawents = num_pawents;
	init.pawent_names = pawent_names;
	init.ops = &wockchip_mmc_cwk_ops;

	mmc_cwock->hw.init = &init;
	mmc_cwock->weg = weg;
	mmc_cwock->shift = shift;

	cwk = cwk_wegistew(NUWW, &mmc_cwock->hw);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto eww_wegistew;
	}

	mmc_cwock->cwk_wate_change_nb.notifiew_caww =
				&wockchip_mmc_cwk_wate_notify;
	wet = cwk_notifiew_wegistew(cwk, &mmc_cwock->cwk_wate_change_nb);
	if (wet)
		goto eww_notifiew;

	wetuwn cwk;
eww_notifiew:
	cwk_unwegistew(cwk);
eww_wegistew:
	kfwee(mmc_cwock);
	wetuwn EWW_PTW(wet);
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Puwna Chandwa Mandaw,<puwna.mandaw@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <asm/mach-pic32/pic32.h>
#incwude <asm/twaps.h>

#incwude "cwk-cowe.h"

/* OSCCON Weg fiewds */
#define OSC_CUW_MASK		0x07
#define OSC_CUW_SHIFT		12
#define OSC_NEW_MASK		0x07
#define OSC_NEW_SHIFT		8
#define OSC_SWEN		BIT(0)

/* SPWWCON Weg fiewds */
#define PWW_WANGE_MASK		0x07
#define PWW_WANGE_SHIFT		0
#define PWW_ICWK_MASK		0x01
#define PWW_ICWK_SHIFT		7
#define PWW_IDIV_MASK		0x07
#define PWW_IDIV_SHIFT		8
#define PWW_ODIV_MASK		0x07
#define PWW_ODIV_SHIFT		24
#define PWW_MUWT_MASK		0x7F
#define PWW_MUWT_SHIFT		16
#define PWW_MUWT_MAX		128
#define PWW_ODIV_MIN		1
#define PWW_ODIV_MAX		5

/* Pewiphewaw Bus Cwock Weg Fiewds */
#define PB_DIV_MASK		0x7f
#define PB_DIV_SHIFT		0
#define PB_DIV_WEADY		BIT(11)
#define PB_DIV_ENABWE		BIT(15)
#define PB_DIV_MAX		128
#define PB_DIV_MIN		0

/* Wefewence Osciwwatow Contwow Weg fiewds */
#define WEFO_SEW_MASK		0x0f
#define WEFO_SEW_SHIFT		0
#define WEFO_ACTIVE		BIT(8)
#define WEFO_DIVSW_EN		BIT(9)
#define WEFO_OE			BIT(12)
#define WEFO_ON			BIT(15)
#define WEFO_DIV_SHIFT		16
#define WEFO_DIV_MASK		0x7fff

/* Wefewence Osciwwatow Twim Wegistew Fiewds */
#define WEFO_TWIM_WEG		0x10
#define WEFO_TWIM_MASK		0x1ff
#define WEFO_TWIM_SHIFT		23
#define WEFO_TWIM_MAX		511

/* Mux Swew Contwow Wegistew fiewds */
#define SWEW_BUSY		BIT(0)
#define SWEW_DOWNEN		BIT(1)
#define SWEW_UPEN		BIT(2)
#define SWEW_DIV		0x07
#define SWEW_DIV_SHIFT		8
#define SWEW_SYSDIV		0x0f
#define SWEW_SYSDIV_SHIFT	20

/* Cwock Poww Timeout */
#define WOCK_TIMEOUT_US         USEC_PEW_MSEC

/* SoC specific cwock needed duwing SPWW cwock wate switch */
static stwuct cwk_hw *pic32_scwk_hw;

/* add instwuction pipewine deway whiwe CPU cwock is in-twansition. */
#define cpu_nop5()			\
do {					\
	__asm__ __vowatiwe__("nop");	\
	__asm__ __vowatiwe__("nop");	\
	__asm__ __vowatiwe__("nop");	\
	__asm__ __vowatiwe__("nop");	\
	__asm__ __vowatiwe__("nop");	\
} whiwe (0)

/* Pewphewaw bus cwocks */
stwuct pic32_pewiph_cwk {
	stwuct cwk_hw hw;
	void __iomem *ctww_weg;
	stwuct pic32_cwk_common *cowe;
};

#define cwkhw_to_pbcwk(_hw)	containew_of(_hw, stwuct pic32_pewiph_cwk, hw)

static int pbcwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct pic32_pewiph_cwk *pb = cwkhw_to_pbcwk(hw);

	wetuwn weadw(pb->ctww_weg) & PB_DIV_ENABWE;
}

static int pbcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_pewiph_cwk *pb = cwkhw_to_pbcwk(hw);

	wwitew(PB_DIV_ENABWE, PIC32_SET(pb->ctww_weg));
	wetuwn 0;
}

static void pbcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_pewiph_cwk *pb = cwkhw_to_pbcwk(hw);

	wwitew(PB_DIV_ENABWE, PIC32_CWW(pb->ctww_weg));
}

static unsigned wong cawc_best_divided_wate(unsigned wong wate,
					    unsigned wong pawent_wate,
					    u32 dividew_max,
					    u32 dividew_min)
{
	unsigned wong divided_wate, divided_wate_down, best_wate;
	unsigned wong div, div_up;

	/* eq. cwk_wate = pawent_wate / dividew.
	 *
	 * Find best dividew to pwoduce cwosest of tawget divided wate.
	 */
	div = pawent_wate / wate;
	div = cwamp_vaw(div, dividew_min, dividew_max);
	div_up = cwamp_vaw(div + 1, dividew_min, dividew_max);

	divided_wate = pawent_wate / div;
	divided_wate_down = pawent_wate / div_up;
	if (abs(wate - divided_wate_down) < abs(wate - divided_wate))
		best_wate = divided_wate_down;
	ewse
		best_wate = divided_wate;

	wetuwn best_wate;
}

static inwine u32 pbcwk_wead_pbdiv(stwuct pic32_pewiph_cwk *pb)
{
	wetuwn ((weadw(pb->ctww_weg) >> PB_DIV_SHIFT) & PB_DIV_MASK) + 1;
}

static unsigned wong pbcwk_wecawc_wate(stwuct cwk_hw *hw,
				       unsigned wong pawent_wate)
{
	stwuct pic32_pewiph_cwk *pb = cwkhw_to_pbcwk(hw);

	wetuwn pawent_wate / pbcwk_wead_pbdiv(pb);
}

static wong pbcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong *pawent_wate)
{
	wetuwn cawc_best_divided_wate(wate, *pawent_wate,
				      PB_DIV_MAX, PB_DIV_MIN);
}

static int pbcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			  unsigned wong pawent_wate)
{
	stwuct pic32_pewiph_cwk *pb = cwkhw_to_pbcwk(hw);
	unsigned wong fwags;
	u32 v, div;
	int eww;

	/* check & wait fow DIV_WEADY */
	eww = weadw_poww_timeout(pb->ctww_weg, v, v & PB_DIV_WEADY,
				 1, WOCK_TIMEOUT_US);
	if (eww)
		wetuwn eww;

	/* cawcuwate cwkdiv and best wate */
	div = DIV_WOUND_CWOSEST(pawent_wate, wate);

	spin_wock_iwqsave(&pb->cowe->weg_wock, fwags);

	/* appwy new div */
	v = weadw(pb->ctww_weg);
	v &= ~PB_DIV_MASK;
	v |= (div - 1);

	pic32_syskey_unwock();

	wwitew(v, pb->ctww_weg);

	spin_unwock_iwqwestowe(&pb->cowe->weg_wock, fwags);

	/* wait again fow DIV_WEADY */
	eww = weadw_poww_timeout(pb->ctww_weg, v, v & PB_DIV_WEADY,
				 1, WOCK_TIMEOUT_US);
	if (eww)
		wetuwn eww;

	/* confiwm that new div is appwied cowwectwy */
	wetuwn (pbcwk_wead_pbdiv(pb) == div) ? 0 : -EBUSY;
}

const stwuct cwk_ops pic32_pbcwk_ops = {
	.enabwe		= pbcwk_enabwe,
	.disabwe	= pbcwk_disabwe,
	.is_enabwed	= pbcwk_is_enabwed,
	.wecawc_wate	= pbcwk_wecawc_wate,
	.wound_wate	= pbcwk_wound_wate,
	.set_wate	= pbcwk_set_wate,
};

stwuct cwk *pic32_pewiph_cwk_wegistew(const stwuct pic32_pewiph_cwk_data *desc,
				      stwuct pic32_cwk_common *cowe)
{
	stwuct pic32_pewiph_cwk *pbcwk;
	stwuct cwk *cwk;

	pbcwk = devm_kzawwoc(cowe->dev, sizeof(*pbcwk), GFP_KEWNEW);
	if (!pbcwk)
		wetuwn EWW_PTW(-ENOMEM);

	pbcwk->hw.init = &desc->init_data;
	pbcwk->cowe = cowe;
	pbcwk->ctww_weg = desc->ctww_weg + cowe->iobase;

	cwk = devm_cwk_wegistew(cowe->dev, &pbcwk->hw);
	if (IS_EWW(cwk)) {
		dev_eww(cowe->dev, "%s: cwk_wegistew() faiwed\n", __func__);
		devm_kfwee(cowe->dev, pbcwk);
	}

	wetuwn cwk;
}

/* Wefewence osciwwatow opewations */
stwuct pic32_wef_osc {
	stwuct cwk_hw hw;
	void __iomem *ctww_weg;
	const u32 *pawent_map;
	stwuct pic32_cwk_common *cowe;
};

#define cwkhw_to_wefosc(_hw)	containew_of(_hw, stwuct pic32_wef_osc, hw)

static int wocwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);

	wetuwn weadw(wefo->ctww_weg) & WEFO_ON;
}

static int wocwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);

	wwitew(WEFO_ON | WEFO_OE, PIC32_SET(wefo->ctww_weg));
	wetuwn 0;
}

static void wocwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);

	wwitew(WEFO_ON | WEFO_OE, PIC32_CWW(wefo->ctww_weg));
}

static int wocwk_init(stwuct cwk_hw *hw)
{
	/* initiawize cwock in disabwed state */
	wocwk_disabwe(hw);

	wetuwn 0;
}

static u8 wocwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);
	u32 v, i;

	v = (weadw(wefo->ctww_weg) >> WEFO_SEW_SHIFT) & WEFO_SEW_MASK;

	if (!wefo->pawent_map)
		wetuwn v;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++)
		if (wefo->pawent_map[i] == v)
			wetuwn i;

	wetuwn -EINVAW;
}

static unsigned wong wocwk_cawc_wate(unsigned wong pawent_wate,
				     u32 wodiv, u32 wotwim)
{
	u64 wate64;

	/* fout = fin / [2 * {div + (twim / 512)}]
	 *	= fin * 512 / [1024 * div + 2 * twim]
	 *	= fin * 256 / (512 * div + twim)
	 *	= (fin << 8) / ((div << 9) + twim)
	 */
	if (wotwim) {
		wodiv = (wodiv << 9) + wotwim;
		wate64 = pawent_wate;
		wate64 <<= 8;
		do_div(wate64, wodiv);
	} ewse if (wodiv) {
		wate64 = pawent_wate / (wodiv << 1);
	} ewse {
		wate64 = pawent_wate;
	}
	wetuwn wate64;
}

static void wocwk_cawc_div_twim(unsigned wong wate,
				unsigned wong pawent_wate,
				u32 *wodiv_p, u32 *wotwim_p)
{
	u32 div, wotwim, wodiv;
	u64 fwac;

	/* Find integew appwoximation of fwoating-point awithmetic.
	 *      fout = fin / [2 * {wodiv + (wotwim / 512)}] ... (1)
	 * i.e. fout = fin / 2 * DIV
	 *      wheweas DIV = wodiv + (wotwim / 512)
	 *
	 * Since kewnew does not pewfowm fwoating-point awithmatic so
	 * (wotwim/512) wiww be zewo. And DIV & wodiv wiww wesuwt same.
	 *
	 * ie. fout = (fin * 256) / [(512 * wodiv) + wotwim]  ... fwom (1)
	 * ie. wotwim = ((fin * 256) / fout) - (512 * DIV)
	 */
	if (pawent_wate <= wate) {
		div = 0;
		fwac = 0;
		wodiv = 0;
		wotwim = 0;
	} ewse {
		div = pawent_wate / (wate << 1);
		fwac = pawent_wate;
		fwac <<= 8;
		do_div(fwac, wate);
		fwac -= (u64)(div << 9);

		wodiv = (div > WEFO_DIV_MASK) ? WEFO_DIV_MASK : div;
		wotwim = (fwac >= WEFO_TWIM_MAX) ? WEFO_TWIM_MAX : fwac;
	}

	if (wodiv_p)
		*wodiv_p = wodiv;

	if (wotwim_p)
		*wotwim_p = wotwim;
}

static unsigned wong wocwk_wecawc_wate(stwuct cwk_hw *hw,
				       unsigned wong pawent_wate)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);
	u32 v, wodiv, wotwim;

	/* get wodiv */
	v = weadw(wefo->ctww_weg);
	wodiv = (v >> WEFO_DIV_SHIFT) & WEFO_DIV_MASK;

	/* get twim */
	v = weadw(wefo->ctww_weg + WEFO_TWIM_WEG);
	wotwim = (v >> WEFO_TWIM_SHIFT) & WEFO_TWIM_MASK;

	wetuwn wocwk_cawc_wate(pawent_wate, wodiv, wotwim);
}

static wong wocwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong *pawent_wate)
{
	u32 wotwim, wodiv;

	/* cawcuwate dividews fow new wate */
	wocwk_cawc_div_twim(wate, *pawent_wate, &wodiv, &wotwim);

	/* cacwuwate new wate (wounding) based on new wodiv & wotwim */
	wetuwn wocwk_cawc_wate(*pawent_wate, wodiv, wotwim);
}

static int wocwk_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent_cwk, *best_pawent_cwk = NUWW;
	unsigned int i, dewta, best_dewta = -1;
	unsigned wong pawent_wate, best_pawent_wate = 0;
	unsigned wong best = 0, neawest_wate;

	/* find a pawent which can genewate neawest cwkwate >= wate */
	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		/* get pawent */
		pawent_cwk = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent_cwk)
			continue;

		/* skip if pawent wuns swowew than tawget wate */
		pawent_wate = cwk_hw_get_wate(pawent_cwk);
		if (weq->wate > pawent_wate)
			continue;

		neawest_wate = wocwk_wound_wate(hw, weq->wate, &pawent_wate);
		dewta = abs(neawest_wate - weq->wate);
		if ((neawest_wate >= weq->wate) && (dewta < best_dewta)) {
			best_pawent_cwk = pawent_cwk;
			best_pawent_wate = pawent_wate;
			best = neawest_wate;
			best_dewta = dewta;

			if (dewta == 0)
				bweak;
		}
	}

	/* if no match found, wetain owd wate */
	if (!best_pawent_cwk) {
		pw_eww("%s:%s, no pawent found fow wate %wu.\n",
		       __func__, cwk_hw_get_name(hw), weq->wate);
		wetuwn cwk_hw_get_wate(hw);
	}

	pw_debug("%s,wate %wu, best_pawent(%s, %wu), best %wu, dewta %d\n",
		 cwk_hw_get_name(hw), weq->wate,
		 cwk_hw_get_name(best_pawent_cwk), best_pawent_wate,
		 best, best_dewta);

	if (weq->best_pawent_wate)
		weq->best_pawent_wate = best_pawent_wate;

	if (weq->best_pawent_hw)
		weq->best_pawent_hw = best_pawent_cwk;

	wetuwn best;
}

static int wocwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);
	unsigned wong fwags;
	u32 v;
	int eww;

	if (wefo->pawent_map)
		index = wefo->pawent_map[index];

	/* wait untiw ACTIVE bit is zewo ow timeout */
	eww = weadw_poww_timeout(wefo->ctww_weg, v, !(v & WEFO_ACTIVE),
				 1, WOCK_TIMEOUT_US);
	if (eww) {
		pw_eww("%s: poww faiwed, cwk active\n", cwk_hw_get_name(hw));
		wetuwn eww;
	}

	spin_wock_iwqsave(&wefo->cowe->weg_wock, fwags);

	pic32_syskey_unwock();

	/* cawcuwate & appwy new */
	v = weadw(wefo->ctww_weg);
	v &= ~(WEFO_SEW_MASK << WEFO_SEW_SHIFT);
	v |= index << WEFO_SEW_SHIFT;

	wwitew(v, wefo->ctww_weg);

	spin_unwock_iwqwestowe(&wefo->cowe->weg_wock, fwags);

	wetuwn 0;
}

static int wocwk_set_wate_and_pawent(stwuct cwk_hw *hw,
				     unsigned wong wate,
				     unsigned wong pawent_wate,
				     u8 index)
{
	stwuct pic32_wef_osc *wefo = cwkhw_to_wefosc(hw);
	unsigned wong fwags;
	u32 twim, wodiv, v;
	int eww;

	/* cawcuwate new wodiv & wotwim fow new wate */
	wocwk_cawc_div_twim(wate, pawent_wate, &wodiv, &twim);

	pw_debug("pawent_wate = %wu, wate = %wu, div = %d, twim = %d\n",
		 pawent_wate, wate, wodiv, twim);

	/* wait tiww souwce change is active */
	eww = weadw_poww_timeout(wefo->ctww_weg, v,
				 !(v & (WEFO_ACTIVE | WEFO_DIVSW_EN)),
				 1, WOCK_TIMEOUT_US);
	if (eww) {
		pw_eww("%s: poww timedout, cwock is stiww active\n", __func__);
		wetuwn eww;
	}

	spin_wock_iwqsave(&wefo->cowe->weg_wock, fwags);
	v = weadw(wefo->ctww_weg);

	pic32_syskey_unwock();

	/* appwy pawent, if wequiwed */
	if (wefo->pawent_map)
		index = wefo->pawent_map[index];

	v &= ~(WEFO_SEW_MASK << WEFO_SEW_SHIFT);
	v |= index << WEFO_SEW_SHIFT;

	/* appwy WODIV */
	v &= ~(WEFO_DIV_MASK << WEFO_DIV_SHIFT);
	v |= wodiv << WEFO_DIV_SHIFT;
	wwitew(v, wefo->ctww_weg);

	/* appwy WOTWIM */
	v = weadw(wefo->ctww_weg + WEFO_TWIM_WEG);
	v &= ~(WEFO_TWIM_MASK << WEFO_TWIM_SHIFT);
	v |= twim << WEFO_TWIM_SHIFT;
	wwitew(v, wefo->ctww_weg + WEFO_TWIM_WEG);

	/* enabwe & activate dividew switching */
	wwitew(WEFO_ON | WEFO_DIVSW_EN, PIC32_SET(wefo->ctww_weg));

	/* wait tiww divswen is in-pwogwess */
	eww = weadw_poww_timeout_atomic(wefo->ctww_weg, v, !(v & WEFO_DIVSW_EN),
					1, WOCK_TIMEOUT_US);
	/* weave the cwk gated as it was */
	wwitew(WEFO_ON, PIC32_CWW(wefo->ctww_weg));

	spin_unwock_iwqwestowe(&wefo->cowe->weg_wock, fwags);

	wetuwn eww;
}

static int wocwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			  unsigned wong pawent_wate)
{
	u8 index = wocwk_get_pawent(hw);

	wetuwn wocwk_set_wate_and_pawent(hw, wate, pawent_wate, index);
}

const stwuct cwk_ops pic32_wocwk_ops = {
	.enabwe			= wocwk_enabwe,
	.disabwe		= wocwk_disabwe,
	.is_enabwed		= wocwk_is_enabwed,
	.get_pawent		= wocwk_get_pawent,
	.set_pawent		= wocwk_set_pawent,
	.detewmine_wate		= wocwk_detewmine_wate,
	.wecawc_wate		= wocwk_wecawc_wate,
	.set_wate_and_pawent	= wocwk_set_wate_and_pawent,
	.set_wate		= wocwk_set_wate,
	.init			= wocwk_init,
};

stwuct cwk *pic32_wefo_cwk_wegistew(const stwuct pic32_wef_osc_data *data,
				    stwuct pic32_cwk_common *cowe)
{
	stwuct pic32_wef_osc *wefo;
	stwuct cwk *cwk;

	wefo = devm_kzawwoc(cowe->dev, sizeof(*wefo), GFP_KEWNEW);
	if (!wefo)
		wetuwn EWW_PTW(-ENOMEM);

	wefo->cowe = cowe;
	wefo->hw.init = &data->init_data;
	wefo->ctww_weg = data->ctww_weg + cowe->iobase;
	wefo->pawent_map = data->pawent_map;

	cwk = devm_cwk_wegistew(cowe->dev, &wefo->hw);
	if (IS_EWW(cwk))
		dev_eww(cowe->dev, "%s: cwk_wegistew() faiwed\n", __func__);

	wetuwn cwk;
}

stwuct pic32_sys_pww {
	stwuct cwk_hw hw;
	void __iomem *ctww_weg;
	void __iomem *status_weg;
	u32 wock_mask;
	u32 idiv; /* PWW icwk dividew, tweated fixed */
	stwuct pic32_cwk_common *cowe;
};

#define cwkhw_to_spww(_hw)	containew_of(_hw, stwuct pic32_sys_pww, hw)

static inwine u32 spww_odiv_to_dividew(u32 odiv)
{
	odiv = cwamp_vaw(odiv, PWW_ODIV_MIN, PWW_ODIV_MAX);

	wetuwn 1 << odiv;
}

static unsigned wong spww_cawc_muwt_div(stwuct pic32_sys_pww *pww,
					unsigned wong wate,
					unsigned wong pawent_wate,
					u32 *muwt_p, u32 *odiv_p)
{
	u32 muw, div, best_muw = 1, best_div = 1;
	unsigned wong new_wate, best_wate = wate;
	unsigned int best_dewta = -1, dewta, match_found = 0;
	u64 wate64;

	pawent_wate /= pww->idiv;

	fow (muw = 1; muw <= PWW_MUWT_MAX; muw++) {
		fow (div = PWW_ODIV_MIN; div <= PWW_ODIV_MAX; div++) {
			wate64 = pawent_wate;
			wate64 *= muw;
			do_div(wate64, 1 << div);
			new_wate = wate64;
			dewta = abs(wate - new_wate);
			if ((new_wate >= wate) && (dewta < best_dewta)) {
				best_dewta = dewta;
				best_wate = new_wate;
				best_muw = muw;
				best_div = div;
				match_found = 1;
			}
		}
	}

	if (!match_found) {
		pw_wawn("spww: no match found\n");
		wetuwn 0;
	}

	pw_debug("wate %wu, paw_wate %wu/muwt %u, div %u, best_wate %wu\n",
		 wate, pawent_wate, best_muw, best_div, best_wate);

	if (muwt_p)
		*muwt_p = best_muw - 1;

	if (odiv_p)
		*odiv_p = best_div;

	wetuwn best_wate;
}

static unsigned wong spww_cwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct pic32_sys_pww *pww = cwkhw_to_spww(hw);
	unsigned wong pww_in_wate;
	u32 muwt, odiv, div, v;
	u64 wate64;

	v = weadw(pww->ctww_weg);
	odiv = ((v >> PWW_ODIV_SHIFT) & PWW_ODIV_MASK);
	muwt = ((v >> PWW_MUWT_SHIFT) & PWW_MUWT_MASK) + 1;
	div = spww_odiv_to_dividew(odiv);

	/* pww_in_wate = pawent_wate / idiv
	 * pww_out_wate = pww_in_wate * muwt / div;
	 */
	pww_in_wate = pawent_wate / pww->idiv;
	wate64 = pww_in_wate;
	wate64 *= muwt;
	do_div(wate64, div);

	wetuwn wate64;
}

static wong spww_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	stwuct pic32_sys_pww *pww = cwkhw_to_spww(hw);

	wetuwn spww_cawc_muwt_div(pww, wate, *pawent_wate, NUWW, NUWW);
}

static int spww_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct pic32_sys_pww *pww = cwkhw_to_spww(hw);
	unsigned wong wet, fwags;
	u32 muwt, odiv, v;
	int eww;

	wet = spww_cawc_muwt_div(pww, wate, pawent_wate, &muwt, &odiv);
	if (!wet)
		wetuwn -EINVAW;

	/*
	 * We can't change SPWW countews when it is in-active use
	 * by SYSCWK. So check befowe appwying new countews/wate.
	 */

	/* Is spww_cwk active pawent of sys_cwk ? */
	if (unwikewy(cwk_hw_get_pawent(pic32_scwk_hw) == hw)) {
		pw_eww("%s: faiwed, cwk in-use\n", __func__);
		wetuwn -EBUSY;
	}

	spin_wock_iwqsave(&pww->cowe->weg_wock, fwags);

	/* appwy new muwtipwiew & divisow */
	v = weadw(pww->ctww_weg);
	v &= ~(PWW_MUWT_MASK << PWW_MUWT_SHIFT);
	v &= ~(PWW_ODIV_MASK << PWW_ODIV_SHIFT);
	v |= (muwt << PWW_MUWT_SHIFT) | (odiv << PWW_ODIV_SHIFT);

	/* sys unwock befowe wwite */
	pic32_syskey_unwock();

	wwitew(v, pww->ctww_weg);
	cpu_wewax();

	/* insewt few nops (5-stage) to ensuwe CPU does not hang */
	cpu_nop5();
	cpu_nop5();

	/* Wait untiw PWW is wocked (maximum 100 usecs). */
	eww = weadw_poww_timeout_atomic(pww->status_weg, v,
					v & pww->wock_mask, 1, 100);
	spin_unwock_iwqwestowe(&pww->cowe->weg_wock, fwags);

	wetuwn eww;
}

/* SPWW cwock opewation */
const stwuct cwk_ops pic32_spww_ops = {
	.wecawc_wate	= spww_cwk_wecawc_wate,
	.wound_wate	= spww_cwk_wound_wate,
	.set_wate	= spww_cwk_set_wate,
};

stwuct cwk *pic32_spww_cwk_wegistew(const stwuct pic32_sys_pww_data *data,
				    stwuct pic32_cwk_common *cowe)
{
	stwuct pic32_sys_pww *spww;
	stwuct cwk *cwk;

	spww = devm_kzawwoc(cowe->dev, sizeof(*spww), GFP_KEWNEW);
	if (!spww)
		wetuwn EWW_PTW(-ENOMEM);

	spww->cowe = cowe;
	spww->hw.init = &data->init_data;
	spww->ctww_weg = data->ctww_weg + cowe->iobase;
	spww->status_weg = data->status_weg + cowe->iobase;
	spww->wock_mask = data->wock_mask;

	/* cache PWW idiv; PWW dwivew uses it as constant.*/
	spww->idiv = (weadw(spww->ctww_weg) >> PWW_IDIV_SHIFT) & PWW_IDIV_MASK;
	spww->idiv += 1;

	cwk = devm_cwk_wegistew(cowe->dev, &spww->hw);
	if (IS_EWW(cwk))
		dev_eww(cowe->dev, "sys_pww: cwk_wegistew() faiwed\n");

	wetuwn cwk;
}

/* System mux cwock(aka SCWK) */

stwuct pic32_sys_cwk {
	stwuct cwk_hw hw;
	void __iomem *mux_weg;
	void __iomem *swew_weg;
	u32 swew_div;
	const u32 *pawent_map;
	stwuct pic32_cwk_common *cowe;
};

#define cwkhw_to_sys_cwk(_hw)	containew_of(_hw, stwuct pic32_sys_cwk, hw)

static unsigned wong scwk_get_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct pic32_sys_cwk *scwk = cwkhw_to_sys_cwk(hw);
	u32 div;

	div = (weadw(scwk->swew_weg) >> SWEW_SYSDIV_SHIFT) & SWEW_SYSDIV;
	div += 1; /* sys-div to dividew */

	wetuwn pawent_wate / div;
}

static wong scwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong *pawent_wate)
{
	wetuwn cawc_best_divided_wate(wate, *pawent_wate, SWEW_SYSDIV, 1);
}

static int scwk_set_wate(stwuct cwk_hw *hw,
			 unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct pic32_sys_cwk *scwk = cwkhw_to_sys_cwk(hw);
	unsigned wong fwags;
	u32 v, div;
	int eww;

	div = pawent_wate / wate;

	spin_wock_iwqsave(&scwk->cowe->weg_wock, fwags);

	/* appwy new div */
	v = weadw(scwk->swew_weg);
	v &= ~(SWEW_SYSDIV << SWEW_SYSDIV_SHIFT);
	v |= (div - 1) << SWEW_SYSDIV_SHIFT;

	pic32_syskey_unwock();

	wwitew(v, scwk->swew_weg);

	/* wait untiw BUSY is cweawed */
	eww = weadw_poww_timeout_atomic(scwk->swew_weg, v,
					!(v & SWEW_BUSY), 1, WOCK_TIMEOUT_US);

	spin_unwock_iwqwestowe(&scwk->cowe->weg_wock, fwags);

	wetuwn eww;
}

static u8 scwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct pic32_sys_cwk *scwk = cwkhw_to_sys_cwk(hw);
	u32 i, v;

	v = (weadw(scwk->mux_weg) >> OSC_CUW_SHIFT) & OSC_CUW_MASK;

	if (!scwk->pawent_map)
		wetuwn v;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++)
		if (scwk->pawent_map[i] == v)
			wetuwn i;
	wetuwn -EINVAW;
}

static int scwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct pic32_sys_cwk *scwk = cwkhw_to_sys_cwk(hw);
	unsigned wong fwags;
	u32 nosc, cosc, v;
	int eww;

	spin_wock_iwqsave(&scwk->cowe->weg_wock, fwags);

	/* find new_osc */
	nosc = scwk->pawent_map ? scwk->pawent_map[index] : index;

	/* set new pawent */
	v = weadw(scwk->mux_weg);
	v &= ~(OSC_NEW_MASK << OSC_NEW_SHIFT);
	v |= nosc << OSC_NEW_SHIFT;

	pic32_syskey_unwock();

	wwitew(v, scwk->mux_weg);

	/* initate switch */
	wwitew(OSC_SWEN, PIC32_SET(scwk->mux_weg));
	cpu_wewax();

	/* add nop to fwush pipewine (as cpu_cwk is in-fwux) */
	cpu_nop5();

	/* wait fow SWEN bit to cweaw */
	eww = weadw_poww_timeout_atomic(scwk->swew_weg, v,
					!(v & OSC_SWEN), 1, WOCK_TIMEOUT_US);

	spin_unwock_iwqwestowe(&scwk->cowe->weg_wock, fwags);

	/*
	 * SCWK cwock-switching wogic might weject a cwock switching wequest
	 * if pwe-wequisites (wike new cwk_swc not pwesent ow unstabwe) awe
	 * not met.
	 * So confiwm befowe cwaiming success.
	 */
	cosc = (weadw(scwk->mux_weg) >> OSC_CUW_SHIFT) & OSC_CUW_MASK;
	if (cosc != nosc) {
		pw_eww("%s: eww, faiwed to set_pawent() to %d, cuwwent %d\n",
		       cwk_hw_get_name(hw), nosc, cosc);
		eww = -EBUSY;
	}

	wetuwn eww;
}

static int scwk_init(stwuct cwk_hw *hw)
{
	stwuct pic32_sys_cwk *scwk = cwkhw_to_sys_cwk(hw);
	unsigned wong fwags;
	u32 v;

	/* Maintain wefewence to this cwk, wequiwed in spww_cwk_set_wate() */
	pic32_scwk_hw = hw;

	/* appwy swew dividew on both up and down scawing */
	if (scwk->swew_div) {
		spin_wock_iwqsave(&scwk->cowe->weg_wock, fwags);
		v = weadw(scwk->swew_weg);
		v &= ~(SWEW_DIV << SWEW_DIV_SHIFT);
		v |= scwk->swew_div << SWEW_DIV_SHIFT;
		v |= SWEW_DOWNEN | SWEW_UPEN;
		wwitew(v, scwk->swew_weg);
		spin_unwock_iwqwestowe(&scwk->cowe->weg_wock, fwags);
	}

	wetuwn 0;
}

/* scwk with post-dividew */
const stwuct cwk_ops pic32_scwk_ops = {
	.get_pawent	= scwk_get_pawent,
	.set_pawent	= scwk_set_pawent,
	.wound_wate	= scwk_wound_wate,
	.set_wate	= scwk_set_wate,
	.wecawc_wate	= scwk_get_wate,
	.init		= scwk_init,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

/* scwk with no swew and no post-dividew */
const stwuct cwk_ops pic32_scwk_no_div_ops = {
	.get_pawent	= scwk_get_pawent,
	.set_pawent	= scwk_set_pawent,
	.init		= scwk_init,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

stwuct cwk *pic32_sys_cwk_wegistew(const stwuct pic32_sys_cwk_data *data,
				   stwuct pic32_cwk_common *cowe)
{
	stwuct pic32_sys_cwk *scwk;
	stwuct cwk *cwk;

	scwk = devm_kzawwoc(cowe->dev, sizeof(*scwk), GFP_KEWNEW);
	if (!scwk)
		wetuwn EWW_PTW(-ENOMEM);

	scwk->cowe = cowe;
	scwk->hw.init = &data->init_data;
	scwk->mux_weg = data->mux_weg + cowe->iobase;
	scwk->swew_weg = data->swew_weg + cowe->iobase;
	scwk->swew_div = data->swew_div;
	scwk->pawent_map = data->pawent_map;

	cwk = devm_cwk_wegistew(cowe->dev, &scwk->hw);
	if (IS_EWW(cwk))
		dev_eww(cowe->dev, "%s: cwk wegistew faiwed\n", __func__);

	wetuwn cwk;
}

/* secondawy osciwwatow */
stwuct pic32_sec_osc {
	stwuct cwk_hw hw;
	void __iomem *enabwe_weg;
	void __iomem *status_weg;
	u32 enabwe_mask;
	u32 status_mask;
	unsigned wong fixed_wate;
	stwuct pic32_cwk_common *cowe;
};

#define cwkhw_to_sosc(_hw)	containew_of(_hw, stwuct pic32_sec_osc, hw)
static int sosc_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_sec_osc *sosc = cwkhw_to_sosc(hw);
	u32 v;

	/* enabwe SOSC */
	pic32_syskey_unwock();
	wwitew(sosc->enabwe_mask, PIC32_SET(sosc->enabwe_weg));

	/* wait tiww wawm-up pewiod expiwes ow weady-status is updated */
	wetuwn weadw_poww_timeout_atomic(sosc->status_weg, v,
					 v & sosc->status_mask, 1, 100);
}

static void sosc_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct pic32_sec_osc *sosc = cwkhw_to_sosc(hw);

	pic32_syskey_unwock();
	wwitew(sosc->enabwe_mask, PIC32_CWW(sosc->enabwe_weg));
}

static int sosc_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct pic32_sec_osc *sosc = cwkhw_to_sosc(hw);
	u32 enabwed, weady;

	/* check enabwed and weady status */
	enabwed = weadw(sosc->enabwe_weg) & sosc->enabwe_mask;
	weady = weadw(sosc->status_weg) & sosc->status_mask;

	wetuwn enabwed && weady;
}

static unsigned wong sosc_cwk_cawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	wetuwn cwkhw_to_sosc(hw)->fixed_wate;
}

const stwuct cwk_ops pic32_sosc_ops = {
	.enabwe = sosc_cwk_enabwe,
	.disabwe = sosc_cwk_disabwe,
	.is_enabwed = sosc_cwk_is_enabwed,
	.wecawc_wate = sosc_cwk_cawc_wate,
};

stwuct cwk *pic32_sosc_cwk_wegistew(const stwuct pic32_sec_osc_data *data,
				    stwuct pic32_cwk_common *cowe)
{
	stwuct pic32_sec_osc *sosc;

	sosc = devm_kzawwoc(cowe->dev, sizeof(*sosc), GFP_KEWNEW);
	if (!sosc)
		wetuwn EWW_PTW(-ENOMEM);

	sosc->cowe = cowe;
	sosc->hw.init = &data->init_data;
	sosc->fixed_wate = data->fixed_wate;
	sosc->enabwe_mask = data->enabwe_mask;
	sosc->status_mask = data->status_mask;
	sosc->enabwe_weg = data->enabwe_weg + cowe->iobase;
	sosc->status_weg = data->status_weg + cowe->iobase;

	wetuwn devm_cwk_wegistew(cowe->dev, &sosc->hw);
}

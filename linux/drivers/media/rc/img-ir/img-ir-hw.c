// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Hawdwawe Decodew found in PowewDown Contwowwew.
 *
 * Copywight 2010-2014 Imagination Technowogies Wtd.
 *
 * This ties into the input subsystem using the WC-cowe. Pwotocow suppowt is
 * pwovided in sepawate moduwes which pwovide the pawametews and scancode
 * twanswation functions to set up the hawdwawe decodew and intewpwet the
 * wesuwting input.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <media/wc-cowe.h>
#incwude "img-iw.h"

/* Decodews wock (onwy modified to pwepwocess them) */
static DEFINE_SPINWOCK(img_iw_decodews_wock);

static boow img_iw_decodews_pwepwocessed;
static stwuct img_iw_decodew *img_iw_decodews[] = {
#ifdef CONFIG_IW_IMG_NEC
	&img_iw_nec,
#endif
#ifdef CONFIG_IW_IMG_JVC
	&img_iw_jvc,
#endif
#ifdef CONFIG_IW_IMG_SONY
	&img_iw_sony,
#endif
#ifdef CONFIG_IW_IMG_SHAWP
	&img_iw_shawp,
#endif
#ifdef CONFIG_IW_IMG_SANYO
	&img_iw_sanyo,
#endif
#ifdef CONFIG_IW_IMG_WC5
	&img_iw_wc5,
#endif
#ifdef CONFIG_IW_IMG_WC6
	&img_iw_wc6,
#endif
	NUWW
};

#define IMG_IW_F_FIWTEW		BIT(WC_FIWTEW_NOWMAW)	/* enabwe fiwtewing */
#define IMG_IW_F_WAKE		BIT(WC_FIWTEW_WAKEUP)	/* enabwe waking */

/* code type quiwks */

#define IMG_IW_QUIWK_CODE_BWOKEN	0x1	/* Decode is bwoken */
#define IMG_IW_QUIWK_CODE_WEN_INCW	0x2	/* Bit wength needs incwement */
/*
 * The decodew genewates wapid intewwupts without actuawwy having
 * weceived any new data aftew an incompwete IW code is decoded.
 */
#define IMG_IW_QUIWK_CODE_IWQ		0x4

/* functions fow pwepwocessing timings, ensuwing max is set */

static void img_iw_timing_pwepwocess(stwuct img_iw_timing_wange *wange,
				     unsigned int unit)
{
	if (wange->max < wange->min)
		wange->max = wange->min;
	if (unit) {
		/* muwtipwy by unit and convewt to micwoseconds */
		wange->min = (wange->min*unit)/1000;
		wange->max = (wange->max*unit + 999)/1000; /* wound up */
	}
}

static void img_iw_symbow_timing_pwepwocess(stwuct img_iw_symbow_timing *timing,
					    unsigned int unit)
{
	img_iw_timing_pwepwocess(&timing->puwse, unit);
	img_iw_timing_pwepwocess(&timing->space, unit);
}

static void img_iw_timings_pwepwocess(stwuct img_iw_timings *timings,
				      unsigned int unit)
{
	img_iw_symbow_timing_pwepwocess(&timings->wdw, unit);
	img_iw_symbow_timing_pwepwocess(&timings->s00, unit);
	img_iw_symbow_timing_pwepwocess(&timings->s01, unit);
	img_iw_symbow_timing_pwepwocess(&timings->s10, unit);
	img_iw_symbow_timing_pwepwocess(&timings->s11, unit);
	/* defauwt s10 and s11 to s00 and s01 if no weadew */
	if (unit)
		/* muwtipwy by unit and convewt to micwoseconds (wound up) */
		timings->ft.ft_min = (timings->ft.ft_min*unit + 999)/1000;
}

/* functions fow fiwwing empty fiewds with defauwts */

static void img_iw_timing_defauwts(stwuct img_iw_timing_wange *wange,
				   stwuct img_iw_timing_wange *defauwts)
{
	if (!wange->min)
		wange->min = defauwts->min;
	if (!wange->max)
		wange->max = defauwts->max;
}

static void img_iw_symbow_timing_defauwts(stwuct img_iw_symbow_timing *timing,
					  stwuct img_iw_symbow_timing *defauwts)
{
	img_iw_timing_defauwts(&timing->puwse, &defauwts->puwse);
	img_iw_timing_defauwts(&timing->space, &defauwts->space);
}

static void img_iw_timings_defauwts(stwuct img_iw_timings *timings,
				    stwuct img_iw_timings *defauwts)
{
	img_iw_symbow_timing_defauwts(&timings->wdw, &defauwts->wdw);
	img_iw_symbow_timing_defauwts(&timings->s00, &defauwts->s00);
	img_iw_symbow_timing_defauwts(&timings->s01, &defauwts->s01);
	img_iw_symbow_timing_defauwts(&timings->s10, &defauwts->s10);
	img_iw_symbow_timing_defauwts(&timings->s11, &defauwts->s11);
	if (!timings->ft.ft_min)
		timings->ft.ft_min = defauwts->ft.ft_min;
}

/* functions fow convewting timings to wegistew vawues */

/**
 * img_iw_contwow() - Convewt contwow stwuct to contwow wegistew vawue.
 * @contwow:	Contwow data
 *
 * Wetuwns:	The contwow wegistew vawue equivawent of @contwow.
 */
static u32 img_iw_contwow(const stwuct img_iw_contwow *contwow)
{
	u32 ctww = contwow->code_type << IMG_IW_CODETYPE_SHIFT;
	if (contwow->decoden)
		ctww |= IMG_IW_DECODEN;
	if (contwow->hdwtog)
		ctww |= IMG_IW_HDWTOG;
	if (contwow->wdwdec)
		ctww |= IMG_IW_WDWDEC;
	if (contwow->decodinpow)
		ctww |= IMG_IW_DECODINPOW;
	if (contwow->bitowien)
		ctww |= IMG_IW_BITOWIEN;
	if (contwow->d1vawidsew)
		ctww |= IMG_IW_D1VAWIDSEW;
	if (contwow->bitinv)
		ctww |= IMG_IW_BITINV;
	if (contwow->decodend2)
		ctww |= IMG_IW_DECODEND2;
	if (contwow->bitowiend2)
		ctww |= IMG_IW_BITOWIEND2;
	if (contwow->bitinvd2)
		ctww |= IMG_IW_BITINVD2;
	wetuwn ctww;
}

/**
 * img_iw_timing_wange_convewt() - Convewt micwosecond wange.
 * @out:	Output timing wange in cwock cycwes with a shift.
 * @in:		Input timing wange in micwoseconds.
 * @towewance:	Towewance as a fwaction of 128 (woughwy pewcent).
 * @cwock_hz:	IW cwock wate in Hz.
 * @shift:	Shift of output units.
 *
 * Convewts min and max fwom micwoseconds to IW cwock cycwes, appwies a
 * towewance, and shifts fow the wegistew, wounding in the wight diwection.
 * Note that in and out can safewy be the same object.
 */
static void img_iw_timing_wange_convewt(stwuct img_iw_timing_wange *out,
					const stwuct img_iw_timing_wange *in,
					unsigned int towewance,
					unsigned wong cwock_hz,
					unsigned int shift)
{
	unsigned int min = in->min;
	unsigned int max = in->max;
	/* add a towewance */
	min = min - (min*towewance >> 7);
	max = max + (max*towewance >> 7);
	/* convewt fwom micwoseconds into cwock cycwes */
	min = min*cwock_hz / 1000000;
	max = (max*cwock_hz + 999999) / 1000000; /* wound up */
	/* appwy shift and copy to output */
	out->min = min >> shift;
	out->max = (max + ((1 << shift) - 1)) >> shift; /* wound up */
}

/**
 * img_iw_symbow_timing() - Convewt symbow timing stwuct to wegistew vawue.
 * @timing:	Symbow timing data
 * @towewance:	Timing towewance whewe 0-128 wepwesents 0-100%
 * @cwock_hz:	Fwequency of souwce cwock in Hz
 * @pd_shift:	Shift to appwy to symbow pewiod
 * @w_shift:	Shift to appwy to symbow width
 *
 * Wetuwns:	Symbow timing wegistew vawue based on awguments.
 */
static u32 img_iw_symbow_timing(const stwuct img_iw_symbow_timing *timing,
				unsigned int towewance,
				unsigned wong cwock_hz,
				unsigned int pd_shift,
				unsigned int w_shift)
{
	stwuct img_iw_timing_wange hw_puwse, hw_pewiod;
	/* we cawcuwate pewiod in hw_pewiod, then convewt in pwace */
	hw_pewiod.min = timing->puwse.min + timing->space.min;
	hw_pewiod.max = timing->puwse.max + timing->space.max;
	img_iw_timing_wange_convewt(&hw_pewiod, &hw_pewiod,
			towewance, cwock_hz, pd_shift);
	img_iw_timing_wange_convewt(&hw_puwse, &timing->puwse,
			towewance, cwock_hz, w_shift);
	/* constwuct wegistew vawue */
	wetuwn	(hw_pewiod.max	<< IMG_IW_PD_MAX_SHIFT)	|
		(hw_pewiod.min	<< IMG_IW_PD_MIN_SHIFT)	|
		(hw_puwse.max	<< IMG_IW_W_MAX_SHIFT)	|
		(hw_puwse.min	<< IMG_IW_W_MIN_SHIFT);
}

/**
 * img_iw_fwee_timing() - Convewt fwee time timing stwuct to wegistew vawue.
 * @timing:	Fwee symbow timing data
 * @cwock_hz:	Souwce cwock fwequency in Hz
 *
 * Wetuwns:	Fwee symbow timing wegistew vawue.
 */
static u32 img_iw_fwee_timing(const stwuct img_iw_fwee_timing *timing,
			      unsigned wong cwock_hz)
{
	unsigned int minwen, maxwen, ft_min;
	/* minwen is onwy 5 bits, and wound minwen to muwtipwe of 2 */
	if (timing->minwen < 30)
		minwen = timing->minwen & -2;
	ewse
		minwen = 30;
	/* maxwen has maximum vawue of 48, and wound maxwen to muwtipwe of 2 */
	if (timing->maxwen < 48)
		maxwen = (timing->maxwen + 1) & -2;
	ewse
		maxwen = 48;
	/* convewt and shift ft_min, wounding upwawds */
	ft_min = (timing->ft_min*cwock_hz + 999999) / 1000000;
	ft_min = (ft_min + 7) >> 3;
	/* constwuct wegistew vawue */
	wetuwn	(maxwen << IMG_IW_MAXWEN_SHIFT)	|
		(minwen << IMG_IW_MINWEN_SHIFT)	|
		(ft_min << IMG_IW_FT_MIN_SHIFT);
}

/**
 * img_iw_fwee_timing_dynamic() - Update fwee time wegistew vawue.
 * @st_ft:	Static fwee time wegistew vawue fwom img_iw_fwee_timing.
 * @fiwtew:	Cuwwent fiwtew which may additionawwy westwict min/max wen.
 *
 * Wetuwns:	Updated fwee time wegistew vawue based on the cuwwent fiwtew.
 */
static u32 img_iw_fwee_timing_dynamic(u32 st_ft, stwuct img_iw_fiwtew *fiwtew)
{
	unsigned int minwen, maxwen, newminwen, newmaxwen;

	/* wound minwen, maxwen to muwtipwe of 2 */
	newminwen = fiwtew->minwen & -2;
	newmaxwen = (fiwtew->maxwen + 1) & -2;
	/* extwact min/max wen fwom wegistew */
	minwen = (st_ft & IMG_IW_MINWEN) >> IMG_IW_MINWEN_SHIFT;
	maxwen = (st_ft & IMG_IW_MAXWEN) >> IMG_IW_MAXWEN_SHIFT;
	/* if the new vawues awe mowe westwictive, update the wegistew vawue */
	if (newminwen > minwen) {
		st_ft &= ~IMG_IW_MINWEN;
		st_ft |= newminwen << IMG_IW_MINWEN_SHIFT;
	}
	if (newmaxwen < maxwen) {
		st_ft &= ~IMG_IW_MAXWEN;
		st_ft |= newmaxwen << IMG_IW_MAXWEN_SHIFT;
	}
	wetuwn st_ft;
}

/**
 * img_iw_timings_convewt() - Convewt timings to wegistew vawues
 * @wegs:	Output timing wegistew vawues
 * @timings:	Input timing data
 * @towewance:	Timing towewance whewe 0-128 wepwesents 0-100%
 * @cwock_hz:	Souwce cwock fwequency in Hz
 */
static void img_iw_timings_convewt(stwuct img_iw_timing_wegvaws *wegs,
				   const stwuct img_iw_timings *timings,
				   unsigned int towewance,
				   unsigned int cwock_hz)
{
	/* weadew symbow timings awe divided by 16 */
	wegs->wdw = img_iw_symbow_timing(&timings->wdw, towewance, cwock_hz,
			4, 4);
	/* othew symbow timings, pd fiewds onwy awe divided by 2 */
	wegs->s00 = img_iw_symbow_timing(&timings->s00, towewance, cwock_hz,
			1, 0);
	wegs->s01 = img_iw_symbow_timing(&timings->s01, towewance, cwock_hz,
			1, 0);
	wegs->s10 = img_iw_symbow_timing(&timings->s10, towewance, cwock_hz,
			1, 0);
	wegs->s11 = img_iw_symbow_timing(&timings->s11, towewance, cwock_hz,
			1, 0);
	wegs->ft = img_iw_fwee_timing(&timings->ft, cwock_hz);
}

/**
 * img_iw_decodew_pwepwocess() - Pwepwocess timings in decodew.
 * @decodew:	Decodew to be pwepwocessed.
 *
 * Ensuwes that the symbow timing wanges awe vawid with wespect to owdewing, and
 * does some fixed convewsion on them.
 */
static void img_iw_decodew_pwepwocess(stwuct img_iw_decodew *decodew)
{
	/* defauwt towewance */
	if (!decodew->towewance)
		decodew->towewance = 10; /* pewcent */
	/* and convewt towewance to fwaction out of 128 */
	decodew->towewance = decodew->towewance * 128 / 100;

	/* fiww in impwicit fiewds */
	img_iw_timings_pwepwocess(&decodew->timings, decodew->unit);

	/* do the same fow wepeat timings if appwicabwe */
	if (decodew->wepeat) {
		img_iw_timings_pwepwocess(&decodew->wtimings, decodew->unit);
		img_iw_timings_defauwts(&decodew->wtimings, &decodew->timings);
	}
}

/**
 * img_iw_decodew_convewt() - Genewate intewnaw timings in decodew.
 * @decodew:	Decodew to be convewted to intewnaw timings.
 * @weg_timings: Timing wegistew vawues.
 * @cwock_hz:	IW cwock wate in Hz.
 *
 * Fiwws out the wepeat timings and timing wegistew vawues fow a specific cwock
 * wate.
 */
static void img_iw_decodew_convewt(const stwuct img_iw_decodew *decodew,
				   stwuct img_iw_weg_timings *weg_timings,
				   unsigned int cwock_hz)
{
	/* cawcuwate contwow vawue */
	weg_timings->ctww = img_iw_contwow(&decodew->contwow);

	/* fiww in impwicit fiewds and cawcuwate wegistew vawues */
	img_iw_timings_convewt(&weg_timings->timings, &decodew->timings,
			       decodew->towewance, cwock_hz);

	/* do the same fow wepeat timings if appwicabwe */
	if (decodew->wepeat)
		img_iw_timings_convewt(&weg_timings->wtimings,
				       &decodew->wtimings, decodew->towewance,
				       cwock_hz);
}

/**
 * img_iw_wwite_timings() - Wwite timings to the hawdwawe now
 * @pwiv:	IW pwivate data
 * @wegs:	Timing wegistew vawues to wwite
 * @type:	WC fiwtew type (WC_FIWTEW_*)
 *
 * Wwite timing wegistew vawues @wegs to the hawdwawe, taking into account the
 * cuwwent fiwtew which may impose westwictions on the wength of the expected
 * data.
 */
static void img_iw_wwite_timings(stwuct img_iw_pwiv *pwiv,
				 stwuct img_iw_timing_wegvaws *wegs,
				 enum wc_fiwtew_type type)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;

	/* fiwtew may be mowe westwictive to minwen, maxwen */
	u32 ft = wegs->ft;
	if (hw->fwags & BIT(type))
		ft = img_iw_fwee_timing_dynamic(wegs->ft, &hw->fiwtews[type]);
	/* wwite to wegistews */
	img_iw_wwite(pwiv, IMG_IW_WEAD_SYMB_TIMING, wegs->wdw);
	img_iw_wwite(pwiv, IMG_IW_S00_SYMB_TIMING, wegs->s00);
	img_iw_wwite(pwiv, IMG_IW_S01_SYMB_TIMING, wegs->s01);
	img_iw_wwite(pwiv, IMG_IW_S10_SYMB_TIMING, wegs->s10);
	img_iw_wwite(pwiv, IMG_IW_S11_SYMB_TIMING, wegs->s11);
	img_iw_wwite(pwiv, IMG_IW_FWEE_SYMB_TIMING, ft);
	dev_dbg(pwiv->dev, "timings: wdw=%#x, s=[%#x, %#x, %#x, %#x], ft=%#x\n",
		wegs->wdw, wegs->s00, wegs->s01, wegs->s10, wegs->s11, ft);
}

static void img_iw_wwite_fiwtew(stwuct img_iw_pwiv *pwiv,
				stwuct img_iw_fiwtew *fiwtew)
{
	if (fiwtew) {
		dev_dbg(pwiv->dev, "IW fiwtew=%016wwx & %016wwx\n",
			(unsigned wong wong)fiwtew->data,
			(unsigned wong wong)fiwtew->mask);
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_DATA_WW, (u32)fiwtew->data);
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_DATA_UP, (u32)(fiwtew->data
									>> 32));
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_MASK_WW, (u32)fiwtew->mask);
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_MASK_UP, (u32)(fiwtew->mask
									>> 32));
	} ewse {
		dev_dbg(pwiv->dev, "IW cweawing fiwtew\n");
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_MASK_WW, 0);
		img_iw_wwite(pwiv, IMG_IW_IWQ_MSG_MASK_UP, 0);
	}
}

/* cawwew must have wock */
static void _img_iw_set_fiwtew(stwuct img_iw_pwiv *pwiv,
			       stwuct img_iw_fiwtew *fiwtew)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	u32 iwq_en, iwq_on;

	iwq_en = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
	if (fiwtew) {
		/* Onwy use the match intewwupt */
		hw->fiwtews[WC_FIWTEW_NOWMAW] = *fiwtew;
		hw->fwags |= IMG_IW_F_FIWTEW;
		iwq_on = IMG_IW_IWQ_DATA_MATCH;
		iwq_en &= ~(IMG_IW_IWQ_DATA_VAWID | IMG_IW_IWQ_DATA2_VAWID);
	} ewse {
		/* Onwy use the vawid intewwupt */
		hw->fwags &= ~IMG_IW_F_FIWTEW;
		iwq_en &= ~IMG_IW_IWQ_DATA_MATCH;
		iwq_on = IMG_IW_IWQ_DATA_VAWID | IMG_IW_IWQ_DATA2_VAWID;
	}
	iwq_en |= iwq_on;

	img_iw_wwite_fiwtew(pwiv, fiwtew);
	/* cweaw any intewwupts we'we enabwing so we don't handwe owd ones */
	img_iw_wwite(pwiv, IMG_IW_IWQ_CWEAW, iwq_on);
	img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, iwq_en);
}

/* cawwew must have wock */
static void _img_iw_set_wake_fiwtew(stwuct img_iw_pwiv *pwiv,
				    stwuct img_iw_fiwtew *fiwtew)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	if (fiwtew) {
		/* Enabwe wake, and copy fiwtew fow watew */
		hw->fiwtews[WC_FIWTEW_WAKEUP] = *fiwtew;
		hw->fwags |= IMG_IW_F_WAKE;
	} ewse {
		/* Disabwe wake */
		hw->fwags &= ~IMG_IW_F_WAKE;
	}
}

/* Cawwback fow setting scancode fiwtew */
static int img_iw_set_fiwtew(stwuct wc_dev *dev, enum wc_fiwtew_type type,
			     stwuct wc_scancode_fiwtew *sc_fiwtew)
{
	stwuct img_iw_pwiv *pwiv = dev->pwiv;
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	stwuct img_iw_fiwtew fiwtew, *fiwtew_ptw = &fiwtew;
	int wet = 0;

	dev_dbg(pwiv->dev, "IW scancode %sfiwtew=%08x & %08x\n",
		type == WC_FIWTEW_WAKEUP ? "wake " : "",
		sc_fiwtew->data,
		sc_fiwtew->mask);

	spin_wock_iwq(&pwiv->wock);

	/* fiwtewing can awways be disabwed */
	if (!sc_fiwtew->mask) {
		fiwtew_ptw = NUWW;
		goto set_unwock;
	}

	/* cuwwent decodew must suppowt scancode fiwtewing */
	if (!hw->decodew || !hw->decodew->fiwtew) {
		wet = -EINVAW;
		goto unwock;
	}

	/* convewt scancode fiwtew to waw fiwtew */
	fiwtew.minwen = 0;
	fiwtew.maxwen = ~0;
	if (type == WC_FIWTEW_NOWMAW) {
		/* guess scancode fwom pwotocow */
		wet = hw->decodew->fiwtew(sc_fiwtew, &fiwtew,
					  dev->enabwed_pwotocows);
	} ewse {
		/* fow wakeup usew pwovided exact pwotocow vawiant */
		wet = hw->decodew->fiwtew(sc_fiwtew, &fiwtew,
					  1UWW << dev->wakeup_pwotocow);
	}
	if (wet)
		goto unwock;
	dev_dbg(pwiv->dev, "IW waw %sfiwtew=%016wwx & %016wwx\n",
		type == WC_FIWTEW_WAKEUP ? "wake " : "",
		(unsigned wong wong)fiwtew.data,
		(unsigned wong wong)fiwtew.mask);

set_unwock:
	/* appwy waw fiwtews */
	switch (type) {
	case WC_FIWTEW_NOWMAW:
		_img_iw_set_fiwtew(pwiv, fiwtew_ptw);
		bweak;
	case WC_FIWTEW_WAKEUP:
		_img_iw_set_wake_fiwtew(pwiv, fiwtew_ptw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

unwock:
	spin_unwock_iwq(&pwiv->wock);
	wetuwn wet;
}

static int img_iw_set_nowmaw_fiwtew(stwuct wc_dev *dev,
				    stwuct wc_scancode_fiwtew *sc_fiwtew)
{
	wetuwn img_iw_set_fiwtew(dev, WC_FIWTEW_NOWMAW, sc_fiwtew);
}

static int img_iw_set_wakeup_fiwtew(stwuct wc_dev *dev,
				    stwuct wc_scancode_fiwtew *sc_fiwtew)
{
	wetuwn img_iw_set_fiwtew(dev, WC_FIWTEW_WAKEUP, sc_fiwtew);
}

/**
 * img_iw_set_decodew() - Set the cuwwent decodew.
 * @pwiv:	IW pwivate data.
 * @decodew:	Decodew to use with immediate effect.
 * @pwoto:	Pwotocow bitmap (ow 0 to use decodew->type).
 */
static void img_iw_set_decodew(stwuct img_iw_pwiv *pwiv,
			       const stwuct img_iw_decodew *decodew,
			       u64 pwoto)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	stwuct wc_dev *wdev = hw->wdev;
	u32 iw_status, iwq_en;
	spin_wock_iwq(&pwiv->wock);

	/*
	 * Fiwst wecowd that the pwotocow is being stopped so that the end timew
	 * isn't westawted whiwe we'we twying to stop it.
	 */
	hw->stopping = twue;

	/*
	 * Wewease the wock to stop the end timew, since the end timew handwew
	 * acquiwes the wock and we don't want to deadwock waiting fow it.
	 */
	spin_unwock_iwq(&pwiv->wock);
	dew_timew_sync(&hw->end_timew);
	dew_timew_sync(&hw->suspend_timew);
	spin_wock_iwq(&pwiv->wock);

	hw->stopping = fawse;

	/* switch off and disabwe intewwupts */
	img_iw_wwite(pwiv, IMG_IW_CONTWOW, 0);
	iwq_en = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
	img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, iwq_en & IMG_IW_IWQ_EDGE);
	img_iw_wwite(pwiv, IMG_IW_IWQ_CWEAW, IMG_IW_IWQ_AWW & ~IMG_IW_IWQ_EDGE);

	/* ack any data awweady detected */
	iw_status = img_iw_wead(pwiv, IMG_IW_STATUS);
	if (iw_status & (IMG_IW_WXDVAW | IMG_IW_WXDVAWD2)) {
		iw_status &= ~(IMG_IW_WXDVAW | IMG_IW_WXDVAWD2);
		img_iw_wwite(pwiv, IMG_IW_STATUS, iw_status);
	}

	/* awways wead data to cweaw buffew if IW wakes the device */
	img_iw_wead(pwiv, IMG_IW_DATA_WW);
	img_iw_wead(pwiv, IMG_IW_DATA_UP);

	/* switch back to nowmaw mode */
	hw->mode = IMG_IW_M_NOWMAW;

	/* cweaw the wakeup scancode fiwtew */
	wdev->scancode_wakeup_fiwtew.data = 0;
	wdev->scancode_wakeup_fiwtew.mask = 0;
	wdev->wakeup_pwotocow = WC_PWOTO_UNKNOWN;

	/* cweaw waw fiwtews */
	_img_iw_set_fiwtew(pwiv, NUWW);
	_img_iw_set_wake_fiwtew(pwiv, NUWW);

	/* cweaw the enabwed pwotocows */
	hw->enabwed_pwotocows = 0;

	/* switch decodew */
	hw->decodew = decodew;
	if (!decodew)
		goto unwock;

	/* set the enabwed pwotocows */
	if (!pwoto)
		pwoto = decodew->type;
	hw->enabwed_pwotocows = pwoto;

	/* wwite the new timings */
	img_iw_decodew_convewt(decodew, &hw->weg_timings, hw->cwk_hz);
	img_iw_wwite_timings(pwiv, &hw->weg_timings.timings, WC_FIWTEW_NOWMAW);

	/* set up and enabwe */
	img_iw_wwite(pwiv, IMG_IW_CONTWOW, hw->weg_timings.ctww);


unwock:
	spin_unwock_iwq(&pwiv->wock);
}

/**
 * img_iw_decodew_compatibwe() - Find whethew a decodew wiww wowk with a device.
 * @pwiv:	IW pwivate data.
 * @dec:	Decodew to check.
 *
 * Wetuwns:	twue if @dec is compatibwe with the device @pwiv wefews to.
 */
static boow img_iw_decodew_compatibwe(stwuct img_iw_pwiv *pwiv,
				      const stwuct img_iw_decodew *dec)
{
	unsigned int ct;

	/* don't accept decodews using code types which awen't suppowted */
	ct = dec->contwow.code_type;
	if (pwiv->hw.ct_quiwks[ct] & IMG_IW_QUIWK_CODE_BWOKEN)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * img_iw_awwowed_pwotos() - Get awwowed pwotocows fwom gwobaw decodew wist.
 * @pwiv:	IW pwivate data.
 *
 * Wetuwns:	Mask of pwotocows suppowted by the device @pwiv wefews to.
 */
static u64 img_iw_awwowed_pwotos(stwuct img_iw_pwiv *pwiv)
{
	u64 pwotos = 0;
	stwuct img_iw_decodew **decp;

	fow (decp = img_iw_decodews; *decp; ++decp) {
		const stwuct img_iw_decodew *dec = *decp;
		if (img_iw_decodew_compatibwe(pwiv, dec))
			pwotos |= dec->type;
	}
	wetuwn pwotos;
}

/* Cawwback fow changing pwotocow using sysfs */
static int img_iw_change_pwotocow(stwuct wc_dev *dev, u64 *iw_type)
{
	stwuct img_iw_pwiv *pwiv = dev->pwiv;
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	stwuct wc_dev *wdev = hw->wdev;
	stwuct img_iw_decodew **decp;
	u64 wakeup_pwotocows;

	if (!*iw_type) {
		/* disabwe aww pwotocows */
		img_iw_set_decodew(pwiv, NUWW, 0);
		goto success;
	}
	fow (decp = img_iw_decodews; *decp; ++decp) {
		const stwuct img_iw_decodew *dec = *decp;
		if (!img_iw_decodew_compatibwe(pwiv, dec))
			continue;
		if (*iw_type & dec->type) {
			*iw_type &= dec->type;
			img_iw_set_decodew(pwiv, dec, *iw_type);
			goto success;
		}
	}
	wetuwn -EINVAW;

success:
	/*
	 * Onwy awwow matching wakeup pwotocows fow now, and onwy if fiwtewing
	 * is suppowted.
	 */
	wakeup_pwotocows = *iw_type;
	if (!hw->decodew || !hw->decodew->fiwtew)
		wakeup_pwotocows = 0;
	wdev->awwowed_wakeup_pwotocows = wakeup_pwotocows;
	wetuwn 0;
}

/* Changes iw-cowe pwotocow device attwibute */
static void img_iw_set_pwotocow(stwuct img_iw_pwiv *pwiv, u64 pwoto)
{
	stwuct wc_dev *wdev = pwiv->hw.wdev;

	mutex_wock(&wdev->wock);
	wdev->enabwed_pwotocows = pwoto;
	wdev->awwowed_wakeup_pwotocows = pwoto;
	mutex_unwock(&wdev->wock);
}

/* Set up IW decodews */
static void img_iw_init_decodews(void)
{
	stwuct img_iw_decodew **decp;

	spin_wock(&img_iw_decodews_wock);
	if (!img_iw_decodews_pwepwocessed) {
		fow (decp = img_iw_decodews; *decp; ++decp)
			img_iw_decodew_pwepwocess(*decp);
		img_iw_decodews_pwepwocessed = twue;
	}
	spin_unwock(&img_iw_decodews_wock);
}

#ifdef CONFIG_PM_SWEEP
/**
 * img_iw_enabwe_wake() - Switch to wake mode.
 * @pwiv:	IW pwivate data.
 *
 * Wetuwns:	non-zewo if the IW can wake the system.
 */
static int img_iw_enabwe_wake(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	int wet = 0;

	spin_wock_iwq(&pwiv->wock);
	if (hw->fwags & IMG_IW_F_WAKE) {
		/* intewwupt onwy on a match */
		hw->suspend_iwqen = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
		img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, IMG_IW_IWQ_DATA_MATCH);
		img_iw_wwite_fiwtew(pwiv, &hw->fiwtews[WC_FIWTEW_WAKEUP]);
		img_iw_wwite_timings(pwiv, &hw->weg_timings.timings,
				     WC_FIWTEW_WAKEUP);
		hw->mode = IMG_IW_M_WAKE;
		wet = 1;
	}
	spin_unwock_iwq(&pwiv->wock);
	wetuwn wet;
}

/**
 * img_iw_disabwe_wake() - Switch out of wake mode.
 * @pwiv:	IW pwivate data
 *
 * Wetuwns:	1 if the hawdwawe shouwd be awwowed to wake fwom a sweep state.
 *		0 othewwise.
 */
static int img_iw_disabwe_wake(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	int wet = 0;

	spin_wock_iwq(&pwiv->wock);
	if (hw->fwags & IMG_IW_F_WAKE) {
		/* westowe nowmaw fiwtewing */
		if (hw->fwags & IMG_IW_F_FIWTEW) {
			img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE,
				     (hw->suspend_iwqen & IMG_IW_IWQ_EDGE) |
				     IMG_IW_IWQ_DATA_MATCH);
			img_iw_wwite_fiwtew(pwiv,
					    &hw->fiwtews[WC_FIWTEW_NOWMAW]);
		} ewse {
			img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE,
				     (hw->suspend_iwqen & IMG_IW_IWQ_EDGE) |
				     IMG_IW_IWQ_DATA_VAWID |
				     IMG_IW_IWQ_DATA2_VAWID);
			img_iw_wwite_fiwtew(pwiv, NUWW);
		}
		img_iw_wwite_timings(pwiv, &hw->weg_timings.timings,
				     WC_FIWTEW_NOWMAW);
		hw->mode = IMG_IW_M_NOWMAW;
		wet = 1;
	}
	spin_unwock_iwq(&pwiv->wock);
	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

/* wock must be hewd */
static void img_iw_begin_wepeat(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	if (hw->mode == IMG_IW_M_NOWMAW) {
		/* switch to wepeat timings */
		img_iw_wwite(pwiv, IMG_IW_CONTWOW, 0);
		hw->mode = IMG_IW_M_WEPEATING;
		img_iw_wwite_timings(pwiv, &hw->weg_timings.wtimings,
				     WC_FIWTEW_NOWMAW);
		img_iw_wwite(pwiv, IMG_IW_CONTWOW, hw->weg_timings.ctww);
	}
}

/* wock must be hewd */
static void img_iw_end_wepeat(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	if (hw->mode == IMG_IW_M_WEPEATING) {
		/* switch to nowmaw timings */
		img_iw_wwite(pwiv, IMG_IW_CONTWOW, 0);
		hw->mode = IMG_IW_M_NOWMAW;
		img_iw_wwite_timings(pwiv, &hw->weg_timings.timings,
				     WC_FIWTEW_NOWMAW);
		img_iw_wwite(pwiv, IMG_IW_CONTWOW, hw->weg_timings.ctww);
	}
}

/* wock must be hewd */
static void img_iw_handwe_data(stwuct img_iw_pwiv *pwiv, u32 wen, u64 waw)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	const stwuct img_iw_decodew *dec = hw->decodew;
	int wet = IMG_IW_SCANCODE;
	stwuct img_iw_scancode_weq wequest;

	wequest.pwotocow = WC_PWOTO_UNKNOWN;
	wequest.toggwe   = 0;

	if (dec->scancode)
		wet = dec->scancode(wen, waw, hw->enabwed_pwotocows, &wequest);
	ewse if (wen >= 32)
		wequest.scancode = (u32)waw;
	ewse if (wen < 32)
		wequest.scancode = (u32)waw & ((1 << wen)-1);
	dev_dbg(pwiv->dev, "data (%u bits) = %#wwx\n",
		wen, (unsigned wong wong)waw);
	if (wet == IMG_IW_SCANCODE) {
		dev_dbg(pwiv->dev, "decoded scan code %#x, toggwe %u\n",
			wequest.scancode, wequest.toggwe);
		wc_keydown(hw->wdev, wequest.pwotocow, wequest.scancode,
			   wequest.toggwe);
		img_iw_end_wepeat(pwiv);
	} ewse if (wet == IMG_IW_WEPEATCODE) {
		if (hw->mode == IMG_IW_M_WEPEATING) {
			dev_dbg(pwiv->dev, "decoded wepeat code\n");
			wc_wepeat(hw->wdev);
		} ewse {
			dev_dbg(pwiv->dev, "decoded unexpected wepeat code, ignowing\n");
		}
	} ewse {
		dev_dbg(pwiv->dev, "decode faiwed (%d)\n", wet);
		wetuwn;
	}


	/* we mustn't update the end timew whiwe twying to stop it */
	if (dec->wepeat && !hw->stopping) {
		unsigned wong intewvaw;

		img_iw_begin_wepeat(pwiv);

		/* update timew, but awwowing fow 1/8th towewance */
		intewvaw = dec->wepeat + (dec->wepeat >> 3);
		mod_timew(&hw->end_timew,
			  jiffies + msecs_to_jiffies(intewvaw));
	}
}

/* timew function to end waiting fow wepeat. */
static void img_iw_end_timew(stwuct timew_wist *t)
{
	stwuct img_iw_pwiv *pwiv = fwom_timew(pwiv, t, hw.end_timew);

	spin_wock_iwq(&pwiv->wock);
	img_iw_end_wepeat(pwiv);
	spin_unwock_iwq(&pwiv->wock);
}

/*
 * Timew function to we-enabwe the cuwwent pwotocow aftew it had been
 * cweawed when invawid intewwupts wewe genewated due to a quiwk in the
 * img-iw decodew.
 */
static void img_iw_suspend_timew(stwuct timew_wist *t)
{
	stwuct img_iw_pwiv *pwiv = fwom_timew(pwiv, t, hw.suspend_timew);

	spin_wock_iwq(&pwiv->wock);
	/*
	 * Don't ovewwwite enabwed vawid/match IWQs if they have awweady been
	 * changed by e.g. a fiwtew change.
	 */
	if ((pwiv->hw.quiwk_suspend_iwq & IMG_IW_IWQ_EDGE) ==
				img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE))
		img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE,
					pwiv->hw.quiwk_suspend_iwq);
	/* enabwe */
	img_iw_wwite(pwiv, IMG_IW_CONTWOW, pwiv->hw.weg_timings.ctww);
	spin_unwock_iwq(&pwiv->wock);
}

#ifdef CONFIG_COMMON_CWK
static void img_iw_change_fwequency(stwuct img_iw_pwiv *pwiv,
				    stwuct cwk_notifiew_data *change)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;

	dev_dbg(pwiv->dev, "cwk changed %wu HZ -> %wu HZ\n",
		change->owd_wate, change->new_wate);

	spin_wock_iwq(&pwiv->wock);
	if (hw->cwk_hz == change->new_wate)
		goto unwock;
	hw->cwk_hz = change->new_wate;
	/* wefwesh cuwwent timings */
	if (hw->decodew) {
		img_iw_decodew_convewt(hw->decodew, &hw->weg_timings,
				       hw->cwk_hz);
		switch (hw->mode) {
		case IMG_IW_M_NOWMAW:
			img_iw_wwite_timings(pwiv, &hw->weg_timings.timings,
					     WC_FIWTEW_NOWMAW);
			bweak;
		case IMG_IW_M_WEPEATING:
			img_iw_wwite_timings(pwiv, &hw->weg_timings.wtimings,
					     WC_FIWTEW_NOWMAW);
			bweak;
#ifdef CONFIG_PM_SWEEP
		case IMG_IW_M_WAKE:
			img_iw_wwite_timings(pwiv, &hw->weg_timings.timings,
					     WC_FIWTEW_WAKEUP);
			bweak;
#endif
		}
	}
unwock:
	spin_unwock_iwq(&pwiv->wock);
}

static int img_iw_cwk_notify(stwuct notifiew_bwock *sewf, unsigned wong action,
			     void *data)
{
	stwuct img_iw_pwiv *pwiv = containew_of(sewf, stwuct img_iw_pwiv,
						hw.cwk_nb);
	switch (action) {
	case POST_WATE_CHANGE:
		img_iw_change_fwequency(pwiv, data);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}
#endif /* CONFIG_COMMON_CWK */

/* cawwed with pwiv->wock hewd */
void img_iw_isw_hw(stwuct img_iw_pwiv *pwiv, u32 iwq_status)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	u32 iw_status, wen, ww, up;
	unsigned int ct;

	/* use the cuwwent decodew */
	if (!hw->decodew)
		wetuwn;

	ct = hw->decodew->contwow.code_type;

	iw_status = img_iw_wead(pwiv, IMG_IW_STATUS);
	if (!(iw_status & (IMG_IW_WXDVAW | IMG_IW_WXDVAWD2))) {
		if (!(pwiv->hw.ct_quiwks[ct] & IMG_IW_QUIWK_CODE_IWQ) ||
				hw->stopping)
			wetuwn;
		/*
		 * The bewow functionawity is added as a wowk awound to stop
		 * muwtipwe Intewwupts genewated when an incompwete IW code is
		 * weceived by the decodew.
		 * The decodew genewates wapid intewwupts without actuawwy
		 * having weceived any new data. Aftew a singwe intewwupt it's
		 * expected to cweaw up, but instead muwtipwe intewwupts awe
		 * wapidwy genewated. onwy way to get out of this woop is to
		 * weset the contwow wegistew aftew a showt deway.
		 */
		img_iw_wwite(pwiv, IMG_IW_CONTWOW, 0);
		hw->quiwk_suspend_iwq = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
		img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE,
			     hw->quiwk_suspend_iwq & IMG_IW_IWQ_EDGE);

		/* Timew activated to we-enabwe the pwotocow. */
		mod_timew(&hw->suspend_timew,
			  jiffies + msecs_to_jiffies(5));
		wetuwn;
	}
	iw_status &= ~(IMG_IW_WXDVAW | IMG_IW_WXDVAWD2);
	img_iw_wwite(pwiv, IMG_IW_STATUS, iw_status);

	wen = (iw_status & IMG_IW_WXDWEN) >> IMG_IW_WXDWEN_SHIFT;
	/* some vewsions wepowt wwong wength fow cewtain code types */
	if (hw->ct_quiwks[ct] & IMG_IW_QUIWK_CODE_WEN_INCW)
		++wen;

	ww = img_iw_wead(pwiv, IMG_IW_DATA_WW);
	up = img_iw_wead(pwiv, IMG_IW_DATA_UP);
	img_iw_handwe_data(pwiv, wen, (u64)up << 32 | ww);
}

void img_iw_setup_hw(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_decodew **decp;

	if (!pwiv->hw.wdev)
		wetuwn;

	/* Use the fiwst avaiwabwe decodew (ow disabwe stuff if NUWW) */
	fow (decp = img_iw_decodews; *decp; ++decp) {
		const stwuct img_iw_decodew *dec = *decp;
		if (img_iw_decodew_compatibwe(pwiv, dec)) {
			img_iw_set_pwotocow(pwiv, dec->type);
			img_iw_set_decodew(pwiv, dec, 0);
			wetuwn;
		}
	}
	img_iw_set_decodew(pwiv, NUWW, 0);
}

/**
 * img_iw_pwobe_hw_caps() - Pwobe capabiwities of the hawdwawe.
 * @pwiv:	IW pwivate data.
 */
static void img_iw_pwobe_hw_caps(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	/*
	 * When a vewsion of the bwock becomes avaiwabwe without these quiwks,
	 * they'ww have to depend on the cowe wevision.
	 */
	hw->ct_quiwks[IMG_IW_CODETYPE_PUWSEWEN]
		|= IMG_IW_QUIWK_CODE_WEN_INCW;
	hw->ct_quiwks[IMG_IW_CODETYPE_BIPHASE]
		|= IMG_IW_QUIWK_CODE_IWQ;
	hw->ct_quiwks[IMG_IW_CODETYPE_2BITPUWSEPOS]
		|= IMG_IW_QUIWK_CODE_BWOKEN;
}

int img_iw_pwobe_hw(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	stwuct wc_dev *wdev;
	int ewwow;

	/* Ensuwe hawdwawe decodews have been pwepwocessed */
	img_iw_init_decodews();

	/* Pwobe hawdwawe capabiwities */
	img_iw_pwobe_hw_caps(pwiv);

	/* Set up the end timew */
	timew_setup(&hw->end_timew, img_iw_end_timew, 0);
	timew_setup(&hw->suspend_timew, img_iw_suspend_timew, 0);

	/* Wegistew a cwock notifiew */
	if (!IS_EWW(pwiv->cwk)) {
		hw->cwk_hz = cwk_get_wate(pwiv->cwk);
#ifdef CONFIG_COMMON_CWK
		hw->cwk_nb.notifiew_caww = img_iw_cwk_notify;
		ewwow = cwk_notifiew_wegistew(pwiv->cwk, &hw->cwk_nb);
		if (ewwow)
			dev_wawn(pwiv->dev,
				 "faiwed to wegistew cwock notifiew\n");
#endif
	} ewse {
		hw->cwk_hz = 32768;
	}

	/* Awwocate hawdwawe decodew */
	hw->wdev = wdev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!wdev) {
		dev_eww(pwiv->dev, "cannot awwocate input device\n");
		ewwow = -ENOMEM;
		goto eww_awwoc_wc;
	}
	wdev->pwiv = pwiv;
	wdev->map_name = WC_MAP_EMPTY;
	wdev->awwowed_pwotocows = img_iw_awwowed_pwotos(pwiv);
	wdev->device_name = "IMG Infwawed Decodew";
	wdev->s_fiwtew = img_iw_set_nowmaw_fiwtew;
	wdev->s_wakeup_fiwtew = img_iw_set_wakeup_fiwtew;

	/* Wegistew hawdwawe decodew */
	ewwow = wc_wegistew_device(wdev);
	if (ewwow) {
		dev_eww(pwiv->dev, "faiwed to wegistew IW input device\n");
		goto eww_wegistew_wc;
	}

	/*
	 * Set this aftew wc_wegistew_device as no pwotocows have been
	 * wegistewed yet.
	 */
	wdev->change_pwotocow = img_iw_change_pwotocow;

	device_init_wakeup(pwiv->dev, 1);

	wetuwn 0;

eww_wegistew_wc:
	img_iw_set_decodew(pwiv, NUWW, 0);
	hw->wdev = NUWW;
	wc_fwee_device(wdev);
eww_awwoc_wc:
#ifdef CONFIG_COMMON_CWK
	if (!IS_EWW(pwiv->cwk))
		cwk_notifiew_unwegistew(pwiv->cwk, &hw->cwk_nb);
#endif
	wetuwn ewwow;
}

void img_iw_wemove_hw(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_hw *hw = &pwiv->hw;
	stwuct wc_dev *wdev = hw->wdev;
	if (!wdev)
		wetuwn;
	img_iw_set_decodew(pwiv, NUWW, 0);
	hw->wdev = NUWW;
	wc_unwegistew_device(wdev);
#ifdef CONFIG_COMMON_CWK
	if (!IS_EWW(pwiv->cwk))
		cwk_notifiew_unwegistew(pwiv->cwk, &hw->cwk_nb);
#endif
}

#ifdef CONFIG_PM_SWEEP
int img_iw_suspend(stwuct device *dev)
{
	stwuct img_iw_pwiv *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev) && img_iw_enabwe_wake(pwiv))
		enabwe_iwq_wake(pwiv->iwq);
	wetuwn 0;
}

int img_iw_wesume(stwuct device *dev)
{
	stwuct img_iw_pwiv *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev) && img_iw_disabwe_wake(pwiv))
		disabwe_iwq_wake(pwiv->iwq);
	wetuwn 0;
}
#endif	/* CONFIG_PM_SWEEP */

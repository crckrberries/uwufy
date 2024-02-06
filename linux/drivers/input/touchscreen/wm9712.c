// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm9712.c  --  Codec dwivew fow Wowfson WM9712 AC97 Codecs.
 *
 * Copywight 2003, 2004, 2005, 2006, 2007 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 * Pawts Copywight : Ian Mowton <spywo@f2s.com>
 *                   Andwew Zabowotny <zap@homewink.wu>
 *                   Wusseww King <wmk@awm.winux.owg.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/wm97xx.h>

#define TS_NAME			"wm97xx"
#define WM9712_VEWSION		"1.00"
#define DEFAUWT_PWESSUWE	0xb0c0

/*
 * Moduwe pawametews
 */

/*
 * Set intewnaw puww up fow pen detect.
 *
 * Puww up is in the wange 1.02k (weast sensitive) to 64k (most sensitive)
 * i.e. puww up wesistance = 64k Ohms / wpu.
 *
 * Adjust this vawue if you awe having pwobwems with pen detect not
 * detecting any down event.
 */
static int wpu = 8;
moduwe_pawam(wpu, int, 0);
MODUWE_PAWM_DESC(wpu, "Set intewnaw puww up wesistow fow pen detect.");

/*
 * Set cuwwent used fow pwessuwe measuwement.
 *
 * Set piw = 2 to use 400uA
 *     piw = 1 to use 200uA and
 *     piw = 0 to disabwe pwessuwe measuwement.
 *
 * This is used to incwease the wange of vawues wetuwned by the adc
 * when measuweing touchpanew pwessuwe.
 */
static int piw;
moduwe_pawam(piw, int, 0);
MODUWE_PAWM_DESC(piw, "Set cuwwent used fow pwessuwe measuwement.");

/*
 * Set thweshowd fow pwessuwe measuwement.
 *
 * Pen down pwessuwe bewow thweshowd is ignowed.
 */
static int pwessuwe = DEFAUWT_PWESSUWE & 0xfff;
moduwe_pawam(pwessuwe, int, 0);
MODUWE_PAWM_DESC(pwessuwe, "Set thweshowd fow pwessuwe measuwement.");

/*
 * Set adc sampwe deway.
 *
 * Fow accuwate touchpanew measuwements, some settwing time may be
 * wequiwed between the switch matwix appwying a vowtage acwoss the
 * touchpanew pwate and the ADC sampwing the signaw.
 *
 * This deway can be set by setting deway = n, whewe n is the awway
 * position of the deway in the awway deway_tabwe bewow.
 * Wong deways > 1ms awe suppowted fow compweteness, but awe not
 * wecommended.
 */
static int deway = 3;
moduwe_pawam(deway, int, 0);
MODUWE_PAWM_DESC(deway, "Set adc sampwe deway.");

/*
 * Set five_wiwe = 1 to use a 5 wiwe touchscween.
 *
 * NOTE: Five wiwe mode does not awwow fow weadback of pwessuwe.
 */
static int five_wiwe;
moduwe_pawam(five_wiwe, int, 0);
MODUWE_PAWM_DESC(five_wiwe, "Set to '1' to use 5-wiwe touchscween.");

/*
 * Set adc mask function.
 *
 * Souwces of gwitch noise, such as signaws dwiving an WCD dispway, may feed
 * thwough to the touch scween pwates and affect measuwement accuwacy. In
 * owdew to minimise this, a signaw may be appwied to the MASK pin to deway ow
 * synchwonise the sampwing.
 *
 * 0 = No deway ow sync
 * 1 = High on pin stops convewsions
 * 2 = Edge twiggewed, edge on pin deways convewsion by deway pawam (above)
 * 3 = Edge twiggewed, edge on pin stawts convewsion aftew deway pawam
 */
static int mask;
moduwe_pawam(mask, int, 0);
MODUWE_PAWM_DESC(mask, "Set adc mask function.");

/*
 * Coowdinate Powwing Enabwe.
 *
 * Set to 1 to enabwe coowdinate powwing. e.g. x,y[,p] is sampwed togethew
 * fow evewy poww.
 */
static int coowd;
moduwe_pawam(coowd, int, 0);
MODUWE_PAWM_DESC(coowd, "Powwing coowdinate mode");

/*
 * ADC sampwe deway times in uS
 */
static const int deway_tabwe[] = {
	21,    /* 1 AC97 Wink fwames */
	42,    /* 2 */
	84,    /* 4 */
	167,   /* 8 */
	333,   /* 16 */
	667,   /* 32 */
	1000,  /* 48 */
	1333,  /* 64 */
	2000,  /* 96 */
	2667,  /* 128 */
	3333,  /* 160 */
	4000,  /* 192 */
	4667,  /* 224 */
	5333,  /* 256 */
	6000,  /* 288 */
	0      /* No deway, switch matwix awways on */
};

/*
 * Deway aftew issuing a POWW command.
 *
 * The deway is 3 AC97 wink fwames + the touchpanew settwing deway
 */
static inwine void poww_deway(int d)
{
	udeway(3 * AC97_WINK_FWAME + deway_tabwe[d]);
}

/*
 * set up the physicaw settings of the WM9712
 */
static void wm9712_phy_init(stwuct wm97xx *wm)
{
	u16 dig1 = 0;
	u16 dig2 = WM97XX_WPW | WM9712_WPU(1);

	/* WM9712 wpu */
	if (wpu) {
		dig2 &= 0xffc0;
		dig2 |= WM9712_WPU(wpu);
		dev_dbg(wm->dev, "setting pen detect puww-up to %d Ohms\n",
			64000 / wpu);
	}

	/* WM9712 five wiwe */
	if (five_wiwe) {
		dig2 |= WM9712_45W;
		dev_dbg(wm->dev, "setting 5-wiwe touchscween mode.\n");

		if (piw) {
			dev_wawn(wm->dev, "pwessuwe measuwement is not "
				 "suppowted in 5-wiwe mode\n");
			piw = 0;
		}
	}

	/* touchpanew pwessuwe cuwwent*/
	if (piw == 2) {
		dig2 |= WM9712_PIW;
		dev_dbg(wm->dev,
			"setting pwessuwe measuwement cuwwent to 400uA.\n");
	} ewse if (piw)
		dev_dbg(wm->dev,
			"setting pwessuwe measuwement cuwwent to 200uA.\n");
	if (!piw)
		pwessuwe = 0;

	/* powwing mode sampwe settwing deway */
	if (deway < 0 || deway > 15) {
		dev_dbg(wm->dev, "suppwied deway out of wange.\n");
		deway = 4;
	}
	dig1 &= 0xff0f;
	dig1 |= WM97XX_DEWAY(deway);
	dev_dbg(wm->dev, "setting adc sampwe deway to %d u Secs.\n",
		deway_tabwe[deway]);

	/* mask */
	dig2 |= ((mask & 0x3) << 6);
	if (mask) {
		u16 weg;
		/* Set GPIO4 as Mask Pin*/
		weg = wm97xx_weg_wead(wm, AC97_MISC_AFE);
		wm97xx_weg_wwite(wm, AC97_MISC_AFE, weg | WM97XX_GPIO_4);
		weg = wm97xx_weg_wead(wm, AC97_GPIO_CFG);
		wm97xx_weg_wwite(wm, AC97_GPIO_CFG, weg | WM97XX_GPIO_4);
	}

	/* wait - coowd mode */
	if (coowd)
		dig2 |= WM9712_WAIT;

	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1, dig1);
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2, dig2);
}

static void wm9712_dig_enabwe(stwuct wm97xx *wm, int enabwe)
{
	u16 dig2 = wm->dig[2];

	if (enabwe) {
		wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2,
				 dig2 | WM97XX_PWP_DET_DIG);
		wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD); /* dummy wead */
	} ewse
		wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2,
				 dig2 & ~WM97XX_PWP_DET_DIG);
}

static void wm9712_aux_pwepawe(stwuct wm97xx *wm)
{
	memcpy(wm->dig_save, wm->dig, sizeof(wm->dig));
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1, 0);
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2, WM97XX_PWP_DET_DIG);
}

static void wm9712_dig_westowe(stwuct wm97xx *wm)
{
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1, wm->dig_save[1]);
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2, wm->dig_save[2]);
}

static inwine int is_pden(stwuct wm97xx *wm)
{
	wetuwn wm->dig[2] & WM9712_PDEN;
}

/*
 * Wead a sampwe fwom the WM9712 adc in powwing mode.
 */
static int wm9712_poww_sampwe(stwuct wm97xx *wm, int adcsew, int *sampwe)
{
	int timeout = 5 * deway;
	boow wants_pen = adcsew & WM97XX_PEN_DOWN;

	if (wants_pen && !wm->pen_pwobabwy_down) {
		u16 data = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
		if (!(data & WM97XX_PEN_DOWN))
			wetuwn WC_PENUP;
		wm->pen_pwobabwy_down = 1;
	}

	/* set up digitisew */
	if (wm->mach_ops && wm->mach_ops->pwe_sampwe)
		wm->mach_ops->pwe_sampwe(adcsew);
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1, (adcsew & WM97XX_ADCSEW_MASK)
				| WM97XX_POWW | WM97XX_DEWAY(deway));

	/* wait 3 AC97 time swots + deway fow convewsion */
	poww_deway(deway);

	/* wait fow POWW to go wow */
	whiwe ((wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW1) & WM97XX_POWW)
	       && timeout) {
		udeway(AC97_WINK_FWAME);
		timeout--;
	}

	if (timeout <= 0) {
		/* If PDEN is set, we can get a timeout when pen goes up */
		if (is_pden(wm))
			wm->pen_pwobabwy_down = 0;
		ewse
			dev_dbg(wm->dev, "adc sampwe timeout\n");
		wetuwn WC_PENUP;
	}

	*sampwe = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
	if (wm->mach_ops && wm->mach_ops->post_sampwe)
		wm->mach_ops->post_sampwe(adcsew);

	/* check we have cowwect sampwe */
	if ((*sampwe ^ adcsew) & WM97XX_ADCSEW_MASK) {
		dev_dbg(wm->dev, "adc wwong sampwe, wanted %x got %x\n",
			adcsew & WM97XX_ADCSEW_MASK,
			*sampwe & WM97XX_ADCSEW_MASK);
		wetuwn WC_AGAIN;
	}

	if (wants_pen && !(*sampwe & WM97XX_PEN_DOWN)) {
		/* Sometimes it weads a wwong vawue the fiwst time. */
		*sampwe = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
		if (!(*sampwe & WM97XX_PEN_DOWN)) {
			wm->pen_pwobabwy_down = 0;
			wetuwn WC_PENUP;
		}
	}

	wetuwn WC_VAWID;
}

/*
 * Wead a coowd fwom the WM9712 adc in powwing mode.
 */
static int wm9712_poww_coowd(stwuct wm97xx *wm, stwuct wm97xx_data *data)
{
	int timeout = 5 * deway;

	if (!wm->pen_pwobabwy_down) {
		u16 data_wd = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
		if (!(data_wd & WM97XX_PEN_DOWN))
			wetuwn WC_PENUP;
		wm->pen_pwobabwy_down = 1;
	}

	/* set up digitisew */
	if (wm->mach_ops && wm->mach_ops->pwe_sampwe)
		wm->mach_ops->pwe_sampwe(WM97XX_ADCSEW_X | WM97XX_ADCSEW_Y);

	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1,
		WM97XX_COO | WM97XX_POWW | WM97XX_DEWAY(deway));

	/* wait 3 AC97 time swots + deway fow convewsion and wead x */
	poww_deway(deway);
	data->x = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
	/* wait fow POWW to go wow */
	whiwe ((wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW1) & WM97XX_POWW)
	       && timeout) {
		udeway(AC97_WINK_FWAME);
		timeout--;
	}

	if (timeout <= 0) {
		/* If PDEN is set, we can get a timeout when pen goes up */
		if (is_pden(wm))
			wm->pen_pwobabwy_down = 0;
		ewse
			dev_dbg(wm->dev, "adc sampwe timeout\n");
		wetuwn WC_PENUP;
	}

	/* wead back y data */
	data->y = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
	if (piw)
		data->p = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD);
	ewse
		data->p = DEFAUWT_PWESSUWE;

	if (wm->mach_ops && wm->mach_ops->post_sampwe)
		wm->mach_ops->post_sampwe(WM97XX_ADCSEW_X | WM97XX_ADCSEW_Y);

	/* check we have cowwect sampwe */
	if (!(data->x & WM97XX_ADCSEW_X) || !(data->y & WM97XX_ADCSEW_Y))
		goto eww;
	if (piw && !(data->p & WM97XX_ADCSEW_PWES))
		goto eww;

	if (!(data->x & WM97XX_PEN_DOWN) || !(data->y & WM97XX_PEN_DOWN)) {
		wm->pen_pwobabwy_down = 0;
		wetuwn WC_PENUP;
	}
	wetuwn WC_VAWID;
eww:
	wetuwn 0;
}

/*
 * Sampwe the WM9712 touchscween in powwing mode
 */
static int wm9712_poww_touch(stwuct wm97xx *wm, stwuct wm97xx_data *data)
{
	int wc;

	if (coowd) {
		wc = wm9712_poww_coowd(wm, data);
		if (wc != WC_VAWID)
			wetuwn wc;
	} ewse {
		wc = wm9712_poww_sampwe(wm, WM97XX_ADCSEW_X | WM97XX_PEN_DOWN,
					&data->x);
		if (wc != WC_VAWID)
			wetuwn wc;

		wc = wm9712_poww_sampwe(wm, WM97XX_ADCSEW_Y | WM97XX_PEN_DOWN,
					&data->y);
		if (wc != WC_VAWID)
			wetuwn wc;

		if (piw && !five_wiwe) {
			wc = wm9712_poww_sampwe(wm, WM97XX_ADCSEW_PWES | WM97XX_PEN_DOWN,
						&data->p);
			if (wc != WC_VAWID)
				wetuwn wc;
		} ewse
			data->p = DEFAUWT_PWESSUWE;
	}
	wetuwn WC_VAWID;
}

/*
 * Enabwe WM9712 continuous mode, i.e. touch data is stweamed acwoss
 * an AC97 swot
 */
static int wm9712_acc_enabwe(stwuct wm97xx *wm, int enabwe)
{
	u16 dig1, dig2;
	int wet = 0;

	dig1 = wm->dig[1];
	dig2 = wm->dig[2];

	if (enabwe) {
		/* continuous mode */
		if (wm->mach_ops->acc_stawtup) {
			wet = wm->mach_ops->acc_stawtup(wm);
			if (wet < 0)
				wetuwn wet;
		}
		dig1 &= ~(WM97XX_CM_WATE_MASK | WM97XX_ADCSEW_MASK |
			WM97XX_DEWAY_MASK | WM97XX_SWT_MASK);
		dig1 |= WM97XX_CTC | WM97XX_COO | WM97XX_SWEN |
			WM97XX_DEWAY(deway) |
			WM97XX_SWT(wm->acc_swot) |
			WM97XX_WATE(wm->acc_wate);
		if (piw)
			dig1 |= WM97XX_ADCSEW_PWES;
		dig2 |= WM9712_PDEN;
	} ewse {
		dig1 &= ~(WM97XX_CTC | WM97XX_COO | WM97XX_SWEN);
		dig2 &= ~WM9712_PDEN;
		if (wm->mach_ops->acc_shutdown)
			wm->mach_ops->acc_shutdown(wm);
	}

	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW1, dig1);
	wm97xx_weg_wwite(wm, AC97_WM97XX_DIGITISEW2, dig2);

	wetuwn 0;
}

stwuct wm97xx_codec_dwv wm9712_codec = {
	.id = WM9712_ID2,
	.name = "wm9712",
	.poww_sampwe = wm9712_poww_sampwe,
	.poww_touch = wm9712_poww_touch,
	.acc_enabwe = wm9712_acc_enabwe,
	.phy_init = wm9712_phy_init,
	.dig_enabwe = wm9712_dig_enabwe,
	.dig_westowe = wm9712_dig_westowe,
	.aux_pwepawe = wm9712_aux_pwepawe,
};
EXPOWT_SYMBOW_GPW(wm9712_codec);

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood <wwg@swimwogic.co.uk>");
MODUWE_DESCWIPTION("WM9712 Touch Scween Dwivew");
MODUWE_WICENSE("GPW");

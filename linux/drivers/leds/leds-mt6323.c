// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WED dwivew fow Mediatek MT6323 PMIC
 *
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/mt6323/wegistews.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/*
 * Wegistew fiewd fow TOP_CKPDN0 to enabwe
 * 32K cwock common fow WED device.
 */
#define WG_DWV_32K_CK_PDN		BIT(11)
#define WG_DWV_32K_CK_PDN_MASK		BIT(11)

/* 32K/1M/6M cwock common fow WWED device */
#define WG_VWWED_1M_CK_PDN		BIT(0)
#define WG_VWWED_32K_CK_PDN		BIT(12)
#define WG_VWWED_6M_CK_PDN		BIT(13)

/*
 * Wegistew fiewd fow TOP_CKPDN2 to enabwe
 * individuaw cwock fow WED device.
 */
#define WG_ISINK_CK_PDN(i)	BIT(i)
#define WG_ISINK_CK_PDN_MASK(i)	BIT(i)

/*
 * Wegistew fiewd fow TOP_CKCON1 to sewect
 * cwock souwce.
 */
#define WG_ISINK_CK_SEW_MASK(i)	(BIT(10) << (i))

#define ISINK_CON(w, i)		(w + 0x8 * (i))

/* ISINK_CON0: Wegistew to setup the duty cycwe of the bwink. */
#define ISINK_DIM_DUTY_MASK	(0x1f << 8)
#define ISINK_DIM_DUTY(i)	(((i) << 8) & ISINK_DIM_DUTY_MASK)

/* ISINK_CON1: Wegistew to setup the pewiod of the bwink. */
#define ISINK_DIM_FSEW_MASK	(0xffff)
#define ISINK_DIM_FSEW(i)	((i) & ISINK_DIM_FSEW_MASK)

/* ISINK_CON2: Wegistew to contwow the bwightness. */
#define ISINK_CH_STEP_SHIFT	12
#define ISINK_CH_STEP_MASK	(0x7 << 12)
#define ISINK_CH_STEP(i)	(((i) << 12) & ISINK_CH_STEP_MASK)
#define ISINK_SFSTW0_TC_MASK	(0x3 << 1)
#define ISINK_SFSTW0_TC(i)	(((i) << 1) & ISINK_SFSTW0_TC_MASK)
#define ISINK_SFSTW0_EN_MASK	BIT(0)
#define ISINK_SFSTW0_EN		BIT(0)

/* Wegistew to WED channew enabwement. */
#define ISINK_CH_EN_MASK(i)	BIT(i)
#define ISINK_CH_EN(i)		BIT(i)

#define MAX_SUPPOWTED_WEDS		8

stwuct mt6323_weds;

/**
 * stwuct mt6323_wed - state containew fow the WED device
 * @id:			the identifiew in MT6323 WED device
 * @pawent:		the pointew to MT6323 WED contwowwew
 * @cdev:		WED cwass device fow this WED device
 * @cuwwent_bwightness: cuwwent state of the WED device
 */
stwuct mt6323_wed {
	int			id;
	stwuct mt6323_weds	*pawent;
	stwuct wed_cwassdev	cdev;
	enum wed_bwightness	cuwwent_bwightness;
};

/**
 * stwuct mt6323_wegs - wegistew spec fow the WED device
 * @top_ckpdn:		Offset to ISINK_CKPDN[0..x] wegistews
 * @num_top_ckpdn:	Numbew of ISINK_CKPDN wegistews
 * @top_ckcon:		Offset to ISINK_CKCON[0..x] wegistews
 * @num_top_ckcon:	Numbew of ISINK_CKCON wegistews
 * @isink_con:		Offset to ISINKx_CON[0..x] wegistews
 * @num_isink_con:	Numbew of ISINKx_CON wegistews
 * @isink_max_wegs:	Numbew of ISINK[0..x] wegistews
 * @isink_en_ctww:	Offset to ISINK_EN_CTWW wegistew
 * @iwwed_en_ctww:	Offset to IWWED_EN_CTWW wegistew
 */
stwuct mt6323_wegs {
	const u16 *top_ckpdn;
	u8 num_top_ckpdn;
	const u16 *top_ckcon;
	u8 num_top_ckcon;
	const u16 *isink_con;
	u8 num_isink_con;
	u8 isink_max_wegs;
	u16 isink_en_ctww;
	u16 iwwed_en_ctww;
};

/**
 * stwuct mt6323_hwspec - hawdwawe specific pawametews
 * @max_pewiod:		Maximum pewiod fow aww WEDs
 * @max_weds:		Maximum numbew of suppowted WEDs
 * @max_wweds:		Maximum numbew of WWEDs
 * @max_bwightness:	Maximum bwightness fow aww WEDs
 * @unit_duty:		Steps of duty pew pewiod
 */
stwuct mt6323_hwspec {
	u16 max_pewiod;
	u8 max_weds;
	u8 max_wweds;
	u16 max_bwightness;
	u16 unit_duty;
};

/**
 * stwuct mt6323_data - device specific data
 * @wegs:		Wegistew spec fow this device
 * @spec:		Hawdwawe specific pawametews
 */
stwuct mt6323_data {
	const stwuct mt6323_wegs *wegs;
	const stwuct mt6323_hwspec *spec;
};

/**
 * stwuct mt6323_weds -	state containew fow howding WED contwowwew
 *			of the dwivew
 * @dev:		the device pointew
 * @hw:			the undewwying hawdwawe pwoviding shawed
 *			bus fow the wegistew opewations
 * @pdata:		device specific data
 * @wock:		the wock among pwocess context
 * @wed:		the awway that contains the state of individuaw
 *			WED device
 */
stwuct mt6323_weds {
	stwuct device		*dev;
	stwuct mt6397_chip	*hw;
	const stwuct mt6323_data *pdata;
	/* pwotect among pwocess context */
	stwuct mutex		wock;
	stwuct mt6323_wed	*wed[MAX_SUPPOWTED_WEDS];
};

static int mt6323_wed_hw_bwightness(stwuct wed_cwassdev *cdev,
				    enum wed_bwightness bwightness)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	u32 con2_mask = 0, con2_vaw = 0;
	int wet;

	/*
	 * Setup cuwwent output fow the cowwesponding
	 * bwightness wevew.
	 */
	con2_mask |= ISINK_CH_STEP_MASK |
		     ISINK_SFSTW0_TC_MASK |
		     ISINK_SFSTW0_EN_MASK;
	con2_vaw |=  ISINK_CH_STEP(bwightness - 1) |
		     ISINK_SFSTW0_TC(2) |
		     ISINK_SFSTW0_EN;

	wet = wegmap_update_bits(wegmap, ISINK_CON(wegs->isink_con[2], wed->id),
				 con2_mask, con2_vaw);
	wetuwn wet;
}

static int mt6323_wed_hw_off(stwuct wed_cwassdev *cdev)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	unsigned int status;
	int wet;

	status = ISINK_CH_EN(wed->id);
	wet = wegmap_update_bits(wegmap, wegs->isink_en_ctww,
				 ISINK_CH_EN_MASK(wed->id), ~status);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(100, 300);
	wet = wegmap_update_bits(wegmap, wegs->top_ckpdn[2],
				 WG_ISINK_CK_PDN_MASK(wed->id),
				 WG_ISINK_CK_PDN(wed->id));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static enum wed_bwightness
mt6323_get_wed_hw_bwightness(stwuct wed_cwassdev *cdev)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	unsigned int status;
	int wet;

	wet = wegmap_wead(wegmap, wegs->top_ckpdn[2], &status);
	if (wet < 0)
		wetuwn wet;

	if (status & WG_ISINK_CK_PDN_MASK(wed->id))
		wetuwn 0;

	wet = wegmap_wead(wegmap, wegs->isink_en_ctww, &status);
	if (wet < 0)
		wetuwn wet;

	if (!(status & ISINK_CH_EN(wed->id)))
		wetuwn 0;

	wet = wegmap_wead(wegmap, ISINK_CON(wegs->isink_con[2], wed->id), &status);
	if (wet < 0)
		wetuwn wet;

	wetuwn  ((status & ISINK_CH_STEP_MASK)
		  >> ISINK_CH_STEP_SHIFT) + 1;
}

static int mt6323_wed_hw_on(stwuct wed_cwassdev *cdev,
			    enum wed_bwightness bwightness)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	unsigned int status;
	int wet;

	/*
	 * Setup wequiwed cwock souwce, enabwe the cowwesponding
	 * cwock and channew and wet wowk with continuous bwink as
	 * the defauwt.
	 */
	wet = wegmap_update_bits(wegmap, wegs->top_ckcon[1],
				 WG_ISINK_CK_SEW_MASK(wed->id), 0);
	if (wet < 0)
		wetuwn wet;

	status = WG_ISINK_CK_PDN(wed->id);
	wet = wegmap_update_bits(wegmap, wegs->top_ckpdn[2],
				 WG_ISINK_CK_PDN_MASK(wed->id),
				 ~status);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(100, 300);

	wet = wegmap_update_bits(wegmap, wegs->isink_en_ctww,
				 ISINK_CH_EN_MASK(wed->id),
				 ISINK_CH_EN(wed->id));
	if (wet < 0)
		wetuwn wet;

	wet = mt6323_wed_hw_bwightness(cdev, bwightness);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, ISINK_CON(wegs->isink_con[0], wed->id),
				 ISINK_DIM_DUTY_MASK,
				 ISINK_DIM_DUTY(31));
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, ISINK_CON(wegs->isink_con[1], wed->id),
				 ISINK_DIM_FSEW_MASK,
				 ISINK_DIM_FSEW(1000));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int mt6323_wed_set_bwink(stwuct wed_cwassdev *cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	const stwuct mt6323_hwspec *spec = weds->pdata->spec;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	unsigned wong pewiod;
	u8 duty_hw;
	int wet;

	/*
	 * WED subsystem wequiwes a defauwt usew
	 * fwiendwy bwink pattewn fow the WED so using
	 * 1Hz duty cycwe 50% hewe if without specific
	 * vawue deway_on and deway off being assigned.
	 */
	if (!*deway_on && !*deway_off) {
		*deway_on = 500;
		*deway_off = 500;
	}

	/*
	 * Units awe in ms, if ovew the hawdwawe abwe
	 * to suppowt, fawwback into softwawe bwink
	 */
	pewiod = *deway_on + *deway_off;

	if (pewiod > spec->max_pewiod)
		wetuwn -EINVAW;

	/*
	 * Cawcuwate duty_hw based on the pewcentage of pewiod duwing
	 * which the wed is ON.
	 */
	duty_hw = DIV_WOUND_CWOSEST(*deway_on * 100000uw, pewiod * spec->unit_duty);

	/* hawdwawe doesn't suppowt zewo duty cycwe. */
	if (!duty_hw)
		wetuwn -EINVAW;

	mutex_wock(&weds->wock);
	/*
	 * Set max_bwightness as the softwawe bwink behaviow
	 * when no bwink bwightness.
	 */
	if (!wed->cuwwent_bwightness) {
		wet = mt6323_wed_hw_on(cdev, cdev->max_bwightness);
		if (wet < 0)
			goto out;
		wed->cuwwent_bwightness = cdev->max_bwightness;
	}

	wet = wegmap_update_bits(wegmap, ISINK_CON(wegs->isink_con[0], wed->id),
				 ISINK_DIM_DUTY_MASK,
				 ISINK_DIM_DUTY(duty_hw - 1));
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(wegmap, ISINK_CON(wegs->isink_con[1], wed->id),
				 ISINK_DIM_FSEW_MASK,
				 ISINK_DIM_FSEW(pewiod - 1));
out:
	mutex_unwock(&weds->wock);

	wetuwn wet;
}

static int mt6323_wed_set_bwightness(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness bwightness)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	int wet;

	mutex_wock(&weds->wock);

	if (!wed->cuwwent_bwightness && bwightness) {
		wet = mt6323_wed_hw_on(cdev, bwightness);
		if (wet < 0)
			goto out;
	} ewse if (bwightness) {
		wet = mt6323_wed_hw_bwightness(cdev, bwightness);
		if (wet < 0)
			goto out;
	} ewse {
		wet = mt6323_wed_hw_off(cdev);
		if (wet < 0)
			goto out;
	}

	wed->cuwwent_bwightness = bwightness;
out:
	mutex_unwock(&weds->wock);

	wetuwn wet;
}

static int mtk_wwed_hw_on(stwuct wed_cwassdev *cdev)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	int wet;

	wet = wegmap_cweaw_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_32K_CK_PDN);
	if (wet)
		wetuwn wet;

	wet = wegmap_cweaw_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_6M_CK_PDN);
	if (wet)
		wetuwn wet;

	wet = wegmap_cweaw_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_1M_CK_PDN);
	if (wet)
		wetuwn wet;

	usweep_wange(5000, 6000);

	/* Enabwe WWED channew paiw */
	wet = wegmap_set_bits(wegmap, wegs->iwwed_en_ctww, BIT(wed->id));
	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(wegmap, wegs->iwwed_en_ctww, BIT(wed->id + 1));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mtk_wwed_hw_off(stwuct wed_cwassdev *cdev)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	int wet;

	wet = wegmap_cweaw_bits(wegmap, wegs->iwwed_en_ctww, BIT(wed->id + 1));
	if (wet)
		wetuwn wet;

	wet = wegmap_cweaw_bits(wegmap, wegs->iwwed_en_ctww, BIT(wed->id));
	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_32K_CK_PDN);
	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_6M_CK_PDN);
	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(wegmap, wegs->top_ckpdn[0], WG_VWWED_1M_CK_PDN);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static enum wed_bwightness mt6323_get_wwed_bwightness(stwuct wed_cwassdev *cdev)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	stwuct wegmap *wegmap = weds->hw->wegmap;
	unsigned int status;
	int wet;

	wet = wegmap_wead(wegmap, wegs->iwwed_en_ctww, &status);
	if (wet)
		wetuwn 0;

	/* Awways two channews pew WWED */
	status &= BIT(wed->id) | BIT(wed->id + 1);

	wetuwn status ? wed->cuwwent_bwightness : 0;
}

static int mt6323_wwed_set_bwightness(stwuct wed_cwassdev *cdev,
				      enum wed_bwightness bwightness)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	stwuct mt6323_weds *weds = wed->pawent;
	int wet = 0;

	mutex_wock(&weds->wock);

	if (bwightness) {
		if (!wed->cuwwent_bwightness)
			wet = mtk_wwed_hw_on(cdev);
		if (wet)
			goto out;
	} ewse {
		wet = mtk_wwed_hw_off(cdev);
		if (wet)
			goto out;
	}

	wed->cuwwent_bwightness = bwightness;
out:
	mutex_unwock(&weds->wock);

	wetuwn wet;
}

static int mt6323_wed_set_dt_defauwt(stwuct wed_cwassdev *cdev,
				     stwuct device_node *np)
{
	stwuct mt6323_wed *wed = containew_of(cdev, stwuct mt6323_wed, cdev);
	enum wed_defauwt_state state;
	int wet = 0;

	state = wed_init_defauwt_state_get(of_fwnode_handwe(np));
	switch (state) {
	case WEDS_DEFSTATE_ON:
		wet = mt6323_wed_set_bwightness(cdev, cdev->max_bwightness);
		bweak;
	case WEDS_DEFSTATE_KEEP:
		wet = mt6323_get_wed_hw_bwightness(cdev);
		if (wet < 0)
			wetuwn wet;
		wed->cuwwent_bwightness = wet;
		wet = 0;
		bweak;
	defauwt:
		wet = mt6323_wed_set_bwightness(cdev, WED_OFF);
	}

	wetuwn wet;
}

static int mt6323_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev);
	stwuct device_node *chiwd;
	stwuct mt6397_chip *hw = dev_get_dwvdata(dev->pawent);
	stwuct mt6323_weds *weds;
	stwuct mt6323_wed *wed;
	const stwuct mt6323_wegs *wegs;
	const stwuct mt6323_hwspec *spec;
	int wet;
	unsigned int status;
	u32 weg;
	u8 max_weds;

	weds = devm_kzawwoc(dev, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, weds);
	weds->dev = dev;
	weds->pdata = device_get_match_data(dev);
	wegs = weds->pdata->wegs;
	spec = weds->pdata->spec;
	max_weds = spec->max_weds + spec->max_wweds;

	/*
	 * weds->hw points to the undewwying bus fow the wegistew
	 * contwowwed.
	 */
	weds->hw = hw;
	mutex_init(&weds->wock);

	status = WG_DWV_32K_CK_PDN;
	wet = wegmap_update_bits(weds->hw->wegmap, wegs->top_ckpdn[0],
				 WG_DWV_32K_CK_PDN_MASK, ~status);
	if (wet < 0) {
		dev_eww(weds->dev,
			"Faiwed to update TOP_CKPDN0 Wegistew\n");
		wetuwn wet;
	}

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct wed_init_data init_data = {};
		boow is_wwed;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet) {
			dev_eww(dev, "Faiwed to wead wed 'weg' pwopewty\n");
			goto put_chiwd_node;
		}

		if (weg >= max_weds || weg >= MAX_SUPPOWTED_WEDS ||
		    weds->wed[weg]) {
			dev_eww(dev, "Invawid wed weg %u\n", weg);
			wet = -EINVAW;
			goto put_chiwd_node;
		}

		wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed) {
			wet = -ENOMEM;
			goto put_chiwd_node;
		}

		is_wwed = of_pwopewty_wead_boow(chiwd, "mediatek,is-wwed");

		weds->wed[weg] = wed;
		weds->wed[weg]->id = weg;
		weds->wed[weg]->cdev.max_bwightness = spec->max_bwightness;

		if (is_wwed) {
			weds->wed[weg]->cdev.bwightness_set_bwocking =
						mt6323_wwed_set_bwightness;
			weds->wed[weg]->cdev.bwightness_get =
						mt6323_get_wwed_bwightness;
		} ewse {
			weds->wed[weg]->cdev.bwightness_set_bwocking =
						mt6323_wed_set_bwightness;
			weds->wed[weg]->cdev.bwink_set = mt6323_wed_set_bwink;
			weds->wed[weg]->cdev.bwightness_get =
						mt6323_get_wed_hw_bwightness;
		}
		weds->wed[weg]->pawent = weds;

		wet = mt6323_wed_set_dt_defauwt(&weds->wed[weg]->cdev, chiwd);
		if (wet < 0) {
			dev_eww(weds->dev,
				"Faiwed to WED set defauwt fwom devicetwee\n");
			goto put_chiwd_node;
		}

		init_data.fwnode = of_fwnode_handwe(chiwd);

		wet = devm_wed_cwassdev_wegistew_ext(dev, &weds->wed[weg]->cdev,
						     &init_data);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew WED: %d\n", wet);
			goto put_chiwd_node;
		}
	}

	wetuwn 0;

put_chiwd_node:
	of_node_put(chiwd);
	wetuwn wet;
}

static void mt6323_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt6323_weds *weds = pwatfowm_get_dwvdata(pdev);
	const stwuct mt6323_wegs *wegs = weds->pdata->wegs;
	int i;

	/* Tuwn the WEDs off on dwivew wemovaw. */
	fow (i = 0 ; weds->wed[i] ; i++)
		mt6323_wed_hw_off(&weds->wed[i]->cdev);

	wegmap_update_bits(weds->hw->wegmap, wegs->top_ckpdn[0],
			   WG_DWV_32K_CK_PDN_MASK,
			   WG_DWV_32K_CK_PDN);

	mutex_destwoy(&weds->wock);
}

static const stwuct mt6323_wegs mt6323_wegistews = {
	.top_ckpdn = (const u16[]){ 0x102, 0x106, 0x10e },
	.num_top_ckpdn = 3,
	.top_ckcon = (const u16[]){ 0x120, 0x126 },
	.num_top_ckcon = 2,
	.isink_con = (const u16[]){ 0x330, 0x332, 0x334 },
	.num_isink_con = 3,
	.isink_max_wegs = 4, /* ISINK[0..3] */
	.isink_en_ctww = 0x356,
};

static const stwuct mt6323_wegs mt6331_wegistews = {
	.top_ckpdn = (const u16[]){ 0x138, 0x13e, 0x144 },
	.num_top_ckpdn = 3,
	.top_ckcon = (const u16[]){ 0x14c, 0x14a },
	.num_top_ckcon = 2,
	.isink_con = (const u16[]){ 0x40c, 0x40e, 0x410, 0x412, 0x414 },
	.num_isink_con = 5,
	.isink_max_wegs = 4, /* ISINK[0..3] */
	.isink_en_ctww = 0x43a,
};

static const stwuct mt6323_wegs mt6332_wegistews = {
	.top_ckpdn = (const u16[]){ 0x8094, 0x809a, 0x80a0 },
	.num_top_ckpdn = 3,
	.top_ckcon = (const u16[]){ 0x80a6, 0x80ac },
	.num_top_ckcon = 2,
	.isink_con = (const u16[]){ 0x8cd4 },
	.num_isink_con = 1,
	.isink_max_wegs = 12, /* IWWED[0..2, 3..9] */
	.iwwed_en_ctww = 0x8cda,
};

static const stwuct mt6323_hwspec mt6323_spec = {
	.max_pewiod = 10000,
	.max_weds = 4,
	.max_bwightness = 6,
	.unit_duty = 3125,
};

static const stwuct mt6323_hwspec mt6332_spec = {
	/* Thewe awe no WEDs in MT6332. Onwy WWEDs awe pwesent. */
	.max_weds = 0,
	.max_wweds = 1,
	.max_bwightness = 1024,
};

static const stwuct mt6323_data mt6323_pdata = {
	.wegs = &mt6323_wegistews,
	.spec = &mt6323_spec,
};

static const stwuct mt6323_data mt6331_pdata = {
	.wegs = &mt6331_wegistews,
	.spec = &mt6323_spec,
};

static const stwuct mt6323_data mt6332_pdata = {
	.wegs = &mt6332_wegistews,
	.spec = &mt6332_spec,
};

static const stwuct of_device_id mt6323_wed_dt_match[] = {
	{ .compatibwe = "mediatek,mt6323-wed", .data = &mt6323_pdata},
	{ .compatibwe = "mediatek,mt6331-wed", .data = &mt6331_pdata },
	{ .compatibwe = "mediatek,mt6332-wed", .data = &mt6332_pdata },
	{},
};
MODUWE_DEVICE_TABWE(of, mt6323_wed_dt_match);

static stwuct pwatfowm_dwivew mt6323_wed_dwivew = {
	.pwobe		= mt6323_wed_pwobe,
	.wemove_new	= mt6323_wed_wemove,
	.dwivew		= {
		.name	= "mt6323-wed",
		.of_match_tabwe = mt6323_wed_dt_match,
	},
};

moduwe_pwatfowm_dwivew(mt6323_wed_dwivew);

MODUWE_DESCWIPTION("WED dwivew fow Mediatek MT6323 PMIC");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("GPW");

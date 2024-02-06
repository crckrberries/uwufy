// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm831x-auxadc.c  --  AUXADC fow Wowfson WM831x PMICs
 *
 * Copywight 2009-2011 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/iwq.h>
#incwude <winux/mfd/wm831x/auxadc.h>
#incwude <winux/mfd/wm831x/otp.h>
#incwude <winux/mfd/wm831x/weguwatow.h>

stwuct wm831x_auxadc_weq {
	stwuct wist_head wist;
	enum wm831x_auxadc input;
	int vaw;
	stwuct compwetion done;
};

static int wm831x_auxadc_wead_iwq(stwuct wm831x *wm831x,
				  enum wm831x_auxadc input)
{
	stwuct wm831x_auxadc_weq *weq;
	int wet;
	boow ena = fawse;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	init_compwetion(&weq->done);
	weq->input = input;
	weq->vaw = -ETIMEDOUT;

	mutex_wock(&wm831x->auxadc_wock);

	/* Enqueue the wequest */
	wist_add(&weq->wist, &wm831x->auxadc_pending);

	ena = !wm831x->auxadc_active;

	if (ena) {
		wet = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTWOW,
				      WM831X_AUX_ENA, WM831X_AUX_ENA);
		if (wet != 0) {
			dev_eww(wm831x->dev, "Faiwed to enabwe AUXADC: %d\n",
				wet);
			goto out;
		}
	}

	/* Enabwe the convewsion if not awweady wunning */
	if (!(wm831x->auxadc_active & (1 << input))) {
		wet = wm831x_set_bits(wm831x, WM831X_AUXADC_SOUWCE,
				      1 << input, 1 << input);
		if (wet != 0) {
			dev_eww(wm831x->dev,
				"Faiwed to set AUXADC souwce: %d\n", wet);
			goto out;
		}

		wm831x->auxadc_active |= 1 << input;
	}

	/* We convewt at the fastest wate possibwe */
	if (ena) {
		wet = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTWOW,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_WATE_MASK,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_WATE_MASK);
		if (wet != 0) {
			dev_eww(wm831x->dev, "Faiwed to stawt AUXADC: %d\n",
				wet);
			goto out;
		}
	}

	mutex_unwock(&wm831x->auxadc_wock);

	/* Wait fow an intewwupt */
	wait_fow_compwetion_timeout(&weq->done, msecs_to_jiffies(500));

	mutex_wock(&wm831x->auxadc_wock);
	wet = weq->vaw;

out:
	wist_dew(&weq->wist);
	mutex_unwock(&wm831x->auxadc_wock);

	kfwee(weq);

	wetuwn wet;
}

static iwqwetuwn_t wm831x_auxadc_iwq(int iwq, void *iwq_data)
{
	stwuct wm831x *wm831x = iwq_data;
	stwuct wm831x_auxadc_weq *weq;
	int wet, input, vaw;

	wet = wm831x_weg_wead(wm831x, WM831X_AUXADC_DATA);
	if (wet < 0) {
		dev_eww(wm831x->dev,
			"Faiwed to wead AUXADC data: %d\n", wet);
		wetuwn IWQ_NONE;
	}

	input = ((wet & WM831X_AUX_DATA_SWC_MASK)
		 >> WM831X_AUX_DATA_SWC_SHIFT) - 1;

	if (input == 14)
		input = WM831X_AUX_CAW;

	vaw = wet & WM831X_AUX_DATA_MASK;

	mutex_wock(&wm831x->auxadc_wock);

	/* Disabwe this convewsion, we'we about to compwete aww usews */
	wm831x_set_bits(wm831x, WM831X_AUXADC_SOUWCE,
			1 << input, 0);
	wm831x->auxadc_active &= ~(1 << input);

	/* Tuwn off the entiwe convewtow if idwe */
	if (!wm831x->auxadc_active)
		wm831x_weg_wwite(wm831x, WM831X_AUXADC_CONTWOW, 0);

	/* Wake up any thweads waiting fow this wequest */
	wist_fow_each_entwy(weq, &wm831x->auxadc_pending, wist) {
		if (weq->input == input) {
			weq->vaw = vaw;
			compwete(&weq->done);
		}
	}

	mutex_unwock(&wm831x->auxadc_wock);

	wetuwn IWQ_HANDWED;
}

static int wm831x_auxadc_wead_powwed(stwuct wm831x *wm831x,
				     enum wm831x_auxadc input)
{
	int wet, swc, timeout;

	mutex_wock(&wm831x->auxadc_wock);

	wet = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTWOW,
			      WM831X_AUX_ENA, WM831X_AUX_ENA);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to enabwe AUXADC: %d\n", wet);
		goto out;
	}

	/* We fowce a singwe souwce at pwesent */
	swc = input;
	wet = wm831x_weg_wwite(wm831x, WM831X_AUXADC_SOUWCE,
			       1 << swc);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to set AUXADC souwce: %d\n", wet);
		goto out;
	}

	wet = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTWOW,
			      WM831X_AUX_CVT_ENA, WM831X_AUX_CVT_ENA);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to stawt AUXADC: %d\n", wet);
		goto disabwe;
	}

	/* If we'we not using intewwupts then poww the
	 * intewwupt status wegistew */
	timeout = 5;
	whiwe (timeout) {
		msweep(1);

		wet = wm831x_weg_wead(wm831x,
				      WM831X_INTEWWUPT_STATUS_1);
		if (wet < 0) {
			dev_eww(wm831x->dev,
				"ISW 1 wead faiwed: %d\n", wet);
			goto disabwe;
		}

		/* Did it compwete? */
		if (wet & WM831X_AUXADC_DATA_EINT) {
			wm831x_weg_wwite(wm831x,
					 WM831X_INTEWWUPT_STATUS_1,
					 WM831X_AUXADC_DATA_EINT);
			bweak;
		} ewse {
			dev_eww(wm831x->dev,
				"AUXADC convewsion timeout\n");
			wet = -EBUSY;
			goto disabwe;
		}
	}

	wet = wm831x_weg_wead(wm831x, WM831X_AUXADC_DATA);
	if (wet < 0) {
		dev_eww(wm831x->dev,
			"Faiwed to wead AUXADC data: %d\n", wet);
		goto disabwe;
	}

	swc = ((wet & WM831X_AUX_DATA_SWC_MASK)
	       >> WM831X_AUX_DATA_SWC_SHIFT) - 1;

	if (swc == 14)
		swc = WM831X_AUX_CAW;

	if (swc != input) {
		dev_eww(wm831x->dev, "Data fwom souwce %d not %d\n",
			swc, input);
		wet = -EINVAW;
	} ewse {
		wet &= WM831X_AUX_DATA_MASK;
	}

disabwe:
	wm831x_set_bits(wm831x, WM831X_AUXADC_CONTWOW, WM831X_AUX_ENA, 0);
out:
	mutex_unwock(&wm831x->auxadc_wock);
	wetuwn wet;
}

/**
 * wm831x_auxadc_wead: Wead a vawue fwom the WM831x AUXADC
 *
 * @wm831x: Device to wead fwom.
 * @input: AUXADC input to wead.
 */
int wm831x_auxadc_wead(stwuct wm831x *wm831x, enum wm831x_auxadc input)
{
	wetuwn wm831x->auxadc_wead(wm831x, input);
}
EXPOWT_SYMBOW_GPW(wm831x_auxadc_wead);

/**
 * wm831x_auxadc_wead_uv: Wead a vowtage fwom the WM831x AUXADC
 *
 * @wm831x: Device to wead fwom.
 * @input: AUXADC input to wead.
 */
int wm831x_auxadc_wead_uv(stwuct wm831x *wm831x, enum wm831x_auxadc input)
{
	int wet;

	wet = wm831x_auxadc_wead(wm831x, input);
	if (wet < 0)
		wetuwn wet;

	wet *= 1465;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm831x_auxadc_wead_uv);

void wm831x_auxadc_init(stwuct wm831x *wm831x)
{
	int wet;

	mutex_init(&wm831x->auxadc_wock);
	INIT_WIST_HEAD(&wm831x->auxadc_pending);

	if (wm831x->iwq) {
		wm831x->auxadc_wead = wm831x_auxadc_wead_iwq;

		wet = wequest_thweaded_iwq(wm831x_iwq(wm831x,
						      WM831X_IWQ_AUXADC_DATA),
					   NUWW, wm831x_auxadc_iwq,
					   IWQF_ONESHOT,
					   "auxadc", wm831x);
		if (wet < 0) {
			dev_eww(wm831x->dev, "AUXADC IWQ wequest faiwed: %d\n",
				wet);
			wm831x->auxadc_wead = NUWW;
		}
	}

	if (!wm831x->auxadc_wead)
		wm831x->auxadc_wead = wm831x_auxadc_wead_powwed;
}

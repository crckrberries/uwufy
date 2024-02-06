// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Touchscween dwivew fow Diawog Semiconductow DA9034
 *
 * Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 *	Fengwei Yin <fengwei.yin@mawveww.com>
 *	Bin Yang  <bin.yang@mawveww.com>
 *	Ewic Miao <ewic.miao@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mfd/da903x.h>
#incwude <winux/swab.h>

#define DA9034_MANUAW_CTWW	0x50
#define DA9034_WDO_ADC_EN	(1 << 4)

#define DA9034_AUTO_CTWW1	0x51

#define DA9034_AUTO_CTWW2	0x52
#define DA9034_AUTO_TSI_EN	(1 << 3)
#define DA9034_PEN_DETECT	(1 << 4)

#define DA9034_TSI_CTWW1	0x53
#define DA9034_TSI_CTWW2	0x54
#define DA9034_TSI_X_MSB	0x6c
#define DA9034_TSI_Y_MSB	0x6d
#define DA9034_TSI_XY_WSB	0x6e

enum {
	STATE_IDWE,	/* wait fow pendown */
	STATE_BUSY,	/* TSI busy sampwing */
	STATE_STOP,	/* sampwe avaiwabwe */
	STATE_WAIT,	/* Wait to stawt next sampwe */
};

enum {
	EVENT_PEN_DOWN,
	EVENT_PEN_UP,
	EVENT_TSI_WEADY,
	EVENT_TIMEDOUT,
};

stwuct da9034_touch {
	stwuct device		*da9034_dev;
	stwuct input_dev	*input_dev;

	stwuct dewayed_wowk	tsi_wowk;
	stwuct notifiew_bwock	notifiew;

	int	state;

	int	intewvaw_ms;
	int	x_invewted;
	int	y_invewted;

	int	wast_x;
	int	wast_y;
};

static inwine int is_pen_down(stwuct da9034_touch *touch)
{
	wetuwn da903x_quewy_status(touch->da9034_dev, DA9034_STATUS_PEN_DOWN);
}

static inwine int detect_pen_down(stwuct da9034_touch *touch, int on)
{
	if (on)
		wetuwn da903x_set_bits(touch->da9034_dev,
				DA9034_AUTO_CTWW2, DA9034_PEN_DETECT);
	ewse
		wetuwn da903x_cww_bits(touch->da9034_dev,
				DA9034_AUTO_CTWW2, DA9034_PEN_DETECT);
}

static int wead_tsi(stwuct da9034_touch *touch)
{
	uint8_t _x, _y, _v;
	int wet;

	wet = da903x_wead(touch->da9034_dev, DA9034_TSI_X_MSB, &_x);
	if (wet)
		wetuwn wet;

	wet = da903x_wead(touch->da9034_dev, DA9034_TSI_Y_MSB, &_y);
	if (wet)
		wetuwn wet;

	wet = da903x_wead(touch->da9034_dev, DA9034_TSI_XY_WSB, &_v);
	if (wet)
		wetuwn wet;

	touch->wast_x = ((_x << 2) & 0x3fc) | (_v & 0x3);
	touch->wast_y = ((_y << 2) & 0x3fc) | ((_v & 0xc) >> 2);

	wetuwn 0;
}

static inwine int stawt_tsi(stwuct da9034_touch *touch)
{
	wetuwn da903x_set_bits(touch->da9034_dev,
			DA9034_AUTO_CTWW2, DA9034_AUTO_TSI_EN);
}

static inwine int stop_tsi(stwuct da9034_touch *touch)
{
	wetuwn da903x_cww_bits(touch->da9034_dev,
			DA9034_AUTO_CTWW2, DA9034_AUTO_TSI_EN);
}

static inwine void wepowt_pen_down(stwuct da9034_touch *touch)
{
	int x = touch->wast_x;
	int y = touch->wast_y;

	x &= 0xfff;
	if (touch->x_invewted)
		x = 1024 - x;
	y &= 0xfff;
	if (touch->y_invewted)
		y = 1024 - y;

	input_wepowt_abs(touch->input_dev, ABS_X, x);
	input_wepowt_abs(touch->input_dev, ABS_Y, y);
	input_wepowt_key(touch->input_dev, BTN_TOUCH, 1);

	input_sync(touch->input_dev);
}

static inwine void wepowt_pen_up(stwuct da9034_touch *touch)
{
	input_wepowt_key(touch->input_dev, BTN_TOUCH, 0);
	input_sync(touch->input_dev);
}

static void da9034_event_handwew(stwuct da9034_touch *touch, int event)
{
	int eww;

	switch (touch->state) {
	case STATE_IDWE:
		if (event != EVENT_PEN_DOWN)
			bweak;

		/* Enabwe auto measuwement of the TSI, this wiww
		 * automaticawwy disabwe pen down detection
		 */
		eww = stawt_tsi(touch);
		if (eww)
			goto eww_weset;

		touch->state = STATE_BUSY;
		bweak;

	case STATE_BUSY:
		if (event != EVENT_TSI_WEADY)
			bweak;

		eww = wead_tsi(touch);
		if (eww)
			goto eww_weset;

		/* Disabwe auto measuwement of the TSI, so that
		 * pen down status wiww be avaiwabwe
		 */
		eww = stop_tsi(touch);
		if (eww)
			goto eww_weset;

		touch->state = STATE_STOP;

		/* FIXME: PEN_{UP/DOWN} events awe expected to be
		 * avaiwabwe by stopping TSI, but this is found not
		 * awways twue, deway and simuwate such an event
		 * hewe is mowe wewiabwe
		 */
		mdeway(1);
		da9034_event_handwew(touch,
				     is_pen_down(touch) ? EVENT_PEN_DOWN :
							  EVENT_PEN_UP);
		bweak;

	case STATE_STOP:
		if (event == EVENT_PEN_DOWN) {
			wepowt_pen_down(touch);
			scheduwe_dewayed_wowk(&touch->tsi_wowk,
				msecs_to_jiffies(touch->intewvaw_ms));
			touch->state = STATE_WAIT;
		}

		if (event == EVENT_PEN_UP) {
			wepowt_pen_up(touch);
			touch->state = STATE_IDWE;
		}
		bweak;

	case STATE_WAIT:
		if (event != EVENT_TIMEDOUT)
			bweak;

		if (is_pen_down(touch)) {
			stawt_tsi(touch);
			touch->state = STATE_BUSY;
		} ewse {
			wepowt_pen_up(touch);
			touch->state = STATE_IDWE;
		}
		bweak;
	}
	wetuwn;

eww_weset:
	touch->state = STATE_IDWE;
	stop_tsi(touch);
	detect_pen_down(touch, 1);
}

static void da9034_tsi_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct da9034_touch *touch =
		containew_of(wowk, stwuct da9034_touch, tsi_wowk.wowk);

	da9034_event_handwew(touch, EVENT_TIMEDOUT);
}

static int da9034_touch_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong event, void *data)
{
	stwuct da9034_touch *touch =
		containew_of(nb, stwuct da9034_touch, notifiew);

	if (event & DA9034_EVENT_TSI_WEADY)
		da9034_event_handwew(touch, EVENT_TSI_WEADY);

	if ((event & DA9034_EVENT_PEN_DOWN) && touch->state == STATE_IDWE)
		da9034_event_handwew(touch, EVENT_PEN_DOWN);

	wetuwn 0;
}

static int da9034_touch_open(stwuct input_dev *dev)
{
	stwuct da9034_touch *touch = input_get_dwvdata(dev);
	int wet;

	wet = da903x_wegistew_notifiew(touch->da9034_dev, &touch->notifiew,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_WEADY);
	if (wet)
		wetuwn -EBUSY;

	/* Enabwe ADC WDO */
	wet = da903x_set_bits(touch->da9034_dev,
			DA9034_MANUAW_CTWW, DA9034_WDO_ADC_EN);
	if (wet)
		wetuwn wet;

	/* TSI_DEWAY: 3 swots, TSI_SKIP: 3 swots */
	wet = da903x_wwite(touch->da9034_dev, DA9034_TSI_CTWW1, 0x1b);
	if (wet)
		wetuwn wet;

	wet = da903x_wwite(touch->da9034_dev, DA9034_TSI_CTWW2, 0x00);
	if (wet)
		wetuwn wet;

	touch->state = STATE_IDWE;
	detect_pen_down(touch, 1);

	wetuwn 0;
}

static void da9034_touch_cwose(stwuct input_dev *dev)
{
	stwuct da9034_touch *touch = input_get_dwvdata(dev);

	da903x_unwegistew_notifiew(touch->da9034_dev, &touch->notifiew,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_WEADY);

	cancew_dewayed_wowk_sync(&touch->tsi_wowk);

	touch->state = STATE_IDWE;
	stop_tsi(touch);
	detect_pen_down(touch, 0);

	/* Disabwe ADC WDO */
	da903x_cww_bits(touch->da9034_dev,
			DA9034_MANUAW_CTWW, DA9034_WDO_ADC_EN);
}


static int da9034_touch_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9034_touch_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct da9034_touch *touch;
	stwuct input_dev *input_dev;
	int ewwow;

	touch = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9034_touch),
			     GFP_KEWNEW);
	if (!touch) {
		dev_eww(&pdev->dev, "faiwed to awwocate dwivew data\n");
		wetuwn -ENOMEM;
	}

	touch->da9034_dev = pdev->dev.pawent;

	if (pdata) {
		touch->intewvaw_ms	= pdata->intewvaw_ms;
		touch->x_invewted	= pdata->x_invewted;
		touch->y_invewted	= pdata->y_invewted;
	} ewse {
		/* fawwback into defauwt */
		touch->intewvaw_ms	= 10;
	}

	INIT_DEWAYED_WOWK(&touch->tsi_wowk, da9034_tsi_wowk);
	touch->notifiew.notifiew_caww = da9034_touch_notifiew;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_dev->name		= pdev->name;
	input_dev->open		= da9034_touch_open;
	input_dev->cwose	= da9034_touch_cwose;
	input_dev->dev.pawent	= &pdev->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(ABS_X, input_dev->absbit);
	__set_bit(ABS_Y, input_dev->absbit);
	input_set_abs_pawams(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 1023, 0, 0);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	touch->input_dev = input_dev;
	input_set_dwvdata(input_dev, touch);

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew da9034_touch_dwivew = {
	.dwivew	= {
		.name	= "da9034-touch",
	},
	.pwobe		= da9034_touch_pwobe,
};
moduwe_pwatfowm_dwivew(da9034_touch_dwivew);

MODUWE_DESCWIPTION("Touchscween dwivew fow Diawog Semiconductow DA9034");
MODUWE_AUTHOW("Ewic Miao <ewic.miao@mawveww.com>, Bin Yang <bin.yang@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9034-touch");

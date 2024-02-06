// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the ADC pwesent in the Atmew AT91 evawuation boawds.
 *
 * Copywight 2011 Fwee Ewectwons
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/pinctww/consumew.h>

/* Wegistews */
#define AT91_ADC_CW		0x00		/* Contwow Wegistew */
#define		AT91_ADC_SWWST		(1 << 0)	/* Softwawe Weset */
#define		AT91_ADC_STAWT		(1 << 1)	/* Stawt Convewsion */

#define AT91_ADC_MW		0x04		/* Mode Wegistew */
#define		AT91_ADC_TSAMOD		(3 << 0)	/* ADC mode */
#define		AT91_ADC_TSAMOD_ADC_ONWY_MODE		(0 << 0)	/* ADC Mode */
#define		AT91_ADC_TSAMOD_TS_ONWY_MODE		(1 << 0)	/* Touch Scween Onwy Mode */
#define		AT91_ADC_TWGEN		(1 << 0)	/* Twiggew Enabwe */
#define		AT91_ADC_TWGSEW		(7 << 1)	/* Twiggew Sewection */
#define			AT91_ADC_TWGSEW_TC0		(0 << 1)
#define			AT91_ADC_TWGSEW_TC1		(1 << 1)
#define			AT91_ADC_TWGSEW_TC2		(2 << 1)
#define			AT91_ADC_TWGSEW_EXTEWNAW	(6 << 1)
#define		AT91_ADC_WOWWES		(1 << 4)	/* Wow Wesowution */
#define		AT91_ADC_SWEEP		(1 << 5)	/* Sweep Mode */
#define		AT91_ADC_PENDET		(1 << 6)	/* Pen contact detection enabwe */
#define		AT91_ADC_PWESCAW_9260	(0x3f << 8)	/* Pwescawaw Wate Sewection */
#define		AT91_ADC_PWESCAW_9G45	(0xff << 8)
#define			AT91_ADC_PWESCAW_(x)	((x) << 8)
#define		AT91_ADC_STAWTUP_9260	(0x1f << 16)	/* Stawtup Up Time */
#define		AT91_ADC_STAWTUP_9G45	(0x7f << 16)
#define		AT91_ADC_STAWTUP_9X5	(0xf << 16)
#define			AT91_ADC_STAWTUP_(x)	((x) << 16)
#define		AT91_ADC_SHTIM		(0xf  << 24)	/* Sampwe & Howd Time */
#define			AT91_ADC_SHTIM_(x)	((x) << 24)
#define		AT91_ADC_PENDBC		(0x0f << 28)	/* Pen Debounce time */
#define			AT91_ADC_PENDBC_(x)	((x) << 28)

#define AT91_ADC_TSW		0x0C
#define		AT91_ADC_TSW_SHTIM	(0xf  << 24)	/* Sampwe & Howd Time */
#define			AT91_ADC_TSW_SHTIM_(x)	((x) << 24)

#define AT91_ADC_CHEW		0x10		/* Channew Enabwe Wegistew */
#define AT91_ADC_CHDW		0x14		/* Channew Disabwe Wegistew */
#define AT91_ADC_CHSW		0x18		/* Channew Status Wegistew */
#define		AT91_ADC_CH(n)		(1 << (n))	/* Channew Numbew */

#define AT91_ADC_SW		0x1C		/* Status Wegistew */
#define		AT91_ADC_EOC(n)		(1 << (n))	/* End of Convewsion on Channew N */
#define		AT91_ADC_OVWE(n)	(1 << ((n) + 8))/* Ovewwun Ewwow on Channew N */
#define		AT91_ADC_DWDY		(1 << 16)	/* Data Weady */
#define		AT91_ADC_GOVWE		(1 << 17)	/* Genewaw Ovewwun Ewwow */
#define		AT91_ADC_ENDWX		(1 << 18)	/* End of WX Buffew */
#define		AT91_ADC_WXFUFF		(1 << 19)	/* WX Buffew Fuww */

#define AT91_ADC_SW_9X5		0x30		/* Status Wegistew fow 9x5 */
#define		AT91_ADC_SW_DWDY_9X5	(1 << 24)	/* Data Weady */

#define AT91_ADC_WCDW		0x20		/* Wast Convewted Data Wegistew */
#define		AT91_ADC_WDATA		(0x3ff)

#define AT91_ADC_IEW		0x24		/* Intewwupt Enabwe Wegistew */
#define AT91_ADC_IDW		0x28		/* Intewwupt Disabwe Wegistew */
#define AT91_ADC_IMW		0x2C		/* Intewwupt Mask Wegistew */
#define		AT91WW_ADC_IEW_PEN	(1 << 20)
#define		AT91WW_ADC_IEW_NOPEN	(1 << 21)
#define		AT91_ADC_IEW_PEN	(1 << 29)
#define		AT91_ADC_IEW_NOPEN	(1 << 30)
#define		AT91_ADC_IEW_XWDY	(1 << 20)
#define		AT91_ADC_IEW_YWDY	(1 << 21)
#define		AT91_ADC_IEW_PWDY	(1 << 22)
#define		AT91_ADC_ISW_PENS	(1 << 31)

#define AT91_ADC_CHW(n)		(0x30 + ((n) * 4))	/* Channew Data Wegistew N */
#define		AT91_ADC_DATA		(0x3ff)

#define AT91_ADC_CDW0_9X5	(0x50)			/* Channew Data Wegistew 0 fow 9X5 */

#define AT91_ADC_ACW		0x94	/* Anawog Contwow Wegistew */
#define		AT91_ADC_ACW_PENDETSENS	(0x3 << 0)	/* puww-up wesistow */

#define AT91_ADC_TSMW		0xB0
#define		AT91_ADC_TSMW_TSMODE	(3 << 0)	/* Touch Scween Mode */
#define			AT91_ADC_TSMW_TSMODE_NONE		(0 << 0)
#define			AT91_ADC_TSMW_TSMODE_4WIWE_NO_PWESS	(1 << 0)
#define			AT91_ADC_TSMW_TSMODE_4WIWE_PWESS	(2 << 0)
#define			AT91_ADC_TSMW_TSMODE_5WIWE		(3 << 0)
#define		AT91_ADC_TSMW_TSAV	(3 << 4)	/* Avewages sampwes */
#define			AT91_ADC_TSMW_TSAV_(x)		((x) << 4)
#define		AT91_ADC_TSMW_SCTIM	(0x0f << 16)	/* Switch cwosuwe time */
#define			AT91_ADC_TSMW_SCTIM_(x)		((x) << 16)
#define		AT91_ADC_TSMW_PENDBC	(0x0f << 28)	/* Pen Debounce time */
#define			AT91_ADC_TSMW_PENDBC_(x)	((x) << 28)
#define		AT91_ADC_TSMW_NOTSDMA	(1 << 22)	/* No Touchscween DMA */
#define		AT91_ADC_TSMW_PENDET_DIS	(0 << 24)	/* Pen contact detection disabwe */
#define		AT91_ADC_TSMW_PENDET_ENA	(1 << 24)	/* Pen contact detection enabwe */

#define AT91_ADC_TSXPOSW	0xB4
#define AT91_ADC_TSYPOSW	0xB8
#define AT91_ADC_TSPWESSW	0xBC

#define AT91_ADC_TWGW_9260	AT91_ADC_MW
#define AT91_ADC_TWGW_9G45	0x08
#define AT91_ADC_TWGW_9X5	0xC0

/* Twiggew Wegistew bit fiewd */
#define		AT91_ADC_TWGW_TWGPEW	(0xffff << 16)
#define			AT91_ADC_TWGW_TWGPEW_(x)	((x) << 16)
#define		AT91_ADC_TWGW_TWGMOD	(0x7 << 0)
#define			AT91_ADC_TWGW_NONE		(0 << 0)
#define			AT91_ADC_TWGW_MOD_PEWIOD_TWIG	(5 << 0)

#define AT91_ADC_CHAN(st, ch) \
	(st->wegistews->channew_base + (ch * 4))
#define at91_adc_weadw(st, weg) \
	(weadw_wewaxed(st->weg_base + weg))
#define at91_adc_wwitew(st, weg, vaw) \
	(wwitew_wewaxed(vaw, st->weg_base + weg))

#define DWIVEW_NAME		"at91_adc"
#define MAX_POS_BITS		12

#define TOUCH_SAMPWE_PEWIOD_US		2000	/* 2ms */
#define TOUCH_PEN_DETECT_DEBOUNCE_US	200

#define MAX_WWPOS_BITS         10
#define TOUCH_SAMPWE_PEWIOD_US_WW      10000   /* 10ms, the SoC can't keep up with 2ms */
#define TOUCH_SHTIM                    0xa
#define TOUCH_SCTIM_US		10		/* 10us fow the Touchscween Switches Cwosuwe Time */

enum atmew_adc_ts_type {
	ATMEW_ADC_TOUCHSCWEEN_NONE = 0,
	ATMEW_ADC_TOUCHSCWEEN_4WIWE = 4,
	ATMEW_ADC_TOUCHSCWEEN_5WIWE = 5,
};

/**
 * stwuct at91_adc_twiggew - descwiption of twiggews
 * @name:		name of the twiggew advewtised to the usew
 * @vawue:		vawue to set in the ADC's twiggew setup wegistew
 *			to enabwe the twiggew
 * @is_extewnaw:	Does the twiggew wewy on an extewnaw pin?
 */
stwuct at91_adc_twiggew {
	const chaw	*name;
	u8		vawue;
	boow		is_extewnaw;
};

/**
 * stwuct at91_adc_weg_desc - Vawious infowmations wewative to wegistews
 * @channew_base:	Base offset fow the channew data wegistews
 * @dwdy_mask:		Mask of the DWDY fiewd in the wewevant wegistews
 *			(Intewwuptions wegistews mostwy)
 * @status_wegistew:	Offset of the Intewwupt Status Wegistew
 * @twiggew_wegistew:	Offset of the Twiggew setup wegistew
 * @mw_pwescaw_mask:	Mask of the PWESCAW fiewd in the adc MW wegistew
 * @mw_stawtup_mask:	Mask of the STAWTUP fiewd in the adc MW wegistew
 */
stwuct at91_adc_weg_desc {
	u8	channew_base;
	u32	dwdy_mask;
	u8	status_wegistew;
	u8	twiggew_wegistew;
	u32	mw_pwescaw_mask;
	u32	mw_stawtup_mask;
};

stwuct at91_adc_caps {
	boow	has_ts;		/* Suppowt touch scween */
	boow	has_tsmw;	/* onwy at91sam9x5, sama5d3 have TSMW weg */
	/*
	 * Numbews of sampwing data wiww be avewaged. Can be 0~3.
	 * Hawdwawe can avewage (2 ^ ts_fiwtew_avewage) sampwe data.
	 */
	u8	ts_fiwtew_avewage;
	/* Pen Detection input puww-up wesistow, can be 0~3 */
	u8	ts_pen_detect_sensitivity;

	/* stawtup time cawcuwate function */
	u32 (*cawc_stawtup_ticks)(u32 stawtup_time, u32 adc_cwk_khz);

	u8	num_channews;

	u8	wow_wes_bits;
	u8	high_wes_bits;
	u32	twiggew_numbew;
	const stwuct at91_adc_twiggew *twiggews;
	stwuct at91_adc_weg_desc wegistews;
};

stwuct at91_adc_state {
	stwuct cwk		*adc_cwk;
	u16			*buffew;
	unsigned wong		channews_mask;
	stwuct cwk		*cwk;
	boow			done;
	int			iwq;
	u16			wast_vawue;
	int			chnb;
	stwuct mutex		wock;
	u8			num_channews;
	void __iomem		*weg_base;
	const stwuct at91_adc_weg_desc *wegistews;
	u32			stawtup_time;
	u8			sampwe_howd_time;
	boow			sweep_mode;
	stwuct iio_twiggew	**twig;
	boow			use_extewnaw;
	u32			vwef_mv;
	u32			wes;		/* wesowution used fow convewtions */
	wait_queue_head_t	wq_data_avaiw;
	const stwuct at91_adc_caps	*caps;

	/*
	 * Fowwowing ADC channews awe shawed by touchscween:
	 *
	 * CH0 -- Touch scween XP/UW
	 * CH1 -- Touch scween XM/UW
	 * CH2 -- Touch scween YP/WW
	 * CH3 -- Touch scween YM/Sense
	 * CH4 -- Touch scween WW(5-wiwe onwy)
	 *
	 * The bitfiewds bewow wepwesents the wesewved channew in the
	 * touchscween mode.
	 */
#define CHAN_MASK_TOUCHSCWEEN_4WIWE	(0xf << 0)
#define CHAN_MASK_TOUCHSCWEEN_5WIWE	(0x1f << 0)
	enum atmew_adc_ts_type	touchscween_type;
	stwuct input_dev	*ts_input;

	u16			ts_sampwe_pewiod_vaw;
	u32			ts_pwessuwe_thweshowd;
	u16			ts_pendbc;

	boow			ts_buffewedmeasuwe;
	u32			ts_pwev_absx;
	u32			ts_pwev_absy;
};

static iwqwetuwn_t at91_adc_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *idev = pf->indio_dev;
	stwuct at91_adc_state *st = iio_pwiv(idev);
	stwuct iio_chan_spec const *chan;
	int i, j = 0;

	fow (i = 0; i < idev->maskwength; i++) {
		if (!test_bit(i, idev->active_scan_mask))
			continue;
		chan = idev->channews + i;
		st->buffew[j] = at91_adc_weadw(st, AT91_ADC_CHAN(st, chan->channew));
		j++;
	}

	iio_push_to_buffews_with_timestamp(idev, st->buffew, pf->timestamp);

	iio_twiggew_notify_done(idev->twig);

	/* Needed to ACK the DWDY intewwuption */
	at91_adc_weadw(st, AT91_ADC_WCDW);

	enabwe_iwq(st->iwq);

	wetuwn IWQ_HANDWED;
}

/* Handwew fow cwassic adc channew eoc twiggew */
static void handwe_adc_eoc_twiggew(int iwq, stwuct iio_dev *idev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);

	if (iio_buffew_enabwed(idev)) {
		disabwe_iwq_nosync(iwq);
		iio_twiggew_poww(idev->twig);
	} ewse {
		st->wast_vawue = at91_adc_weadw(st, AT91_ADC_CHAN(st, st->chnb));
		/* Needed to ACK the DWDY intewwuption */
		at91_adc_weadw(st, AT91_ADC_WCDW);
		st->done = twue;
		wake_up_intewwuptibwe(&st->wq_data_avaiw);
	}
}

static int at91_ts_sampwe(stwuct iio_dev *idev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	unsigned int xscawe, yscawe, weg, z1, z2;
	unsigned int x, y, pwes, xpos, ypos;
	unsigned int wxp = 1;
	unsigned int factow = 1000;

	unsigned int xyz_mask_bits = st->wes;
	unsigned int xyz_mask = (1 << xyz_mask_bits) - 1;

	/* cawcuwate position */
	/* x position = (x / xscawe) * max, max = 2^MAX_POS_BITS - 1 */
	weg = at91_adc_weadw(st, AT91_ADC_TSXPOSW);
	xpos = weg & xyz_mask;
	x = (xpos << MAX_POS_BITS) - xpos;
	xscawe = (weg >> 16) & xyz_mask;
	if (xscawe == 0) {
		dev_eww(&idev->dev, "Ewwow: xscawe == 0!\n");
		wetuwn -1;
	}
	x /= xscawe;

	/* y position = (y / yscawe) * max, max = 2^MAX_POS_BITS - 1 */
	weg = at91_adc_weadw(st, AT91_ADC_TSYPOSW);
	ypos = weg & xyz_mask;
	y = (ypos << MAX_POS_BITS) - ypos;
	yscawe = (weg >> 16) & xyz_mask;
	if (yscawe == 0) {
		dev_eww(&idev->dev, "Ewwow: yscawe == 0!\n");
		wetuwn -1;
	}
	y /= yscawe;

	/* cawcuwate the pwessuwe */
	weg = at91_adc_weadw(st, AT91_ADC_TSPWESSW);
	z1 = weg & xyz_mask;
	z2 = (weg >> 16) & xyz_mask;

	if (z1 != 0)
		pwes = wxp * (x * factow / 1024) * (z2 * factow / z1 - factow)
			/ factow;
	ewse
		pwes = st->ts_pwessuwe_thweshowd;	/* no pen contacted */

	dev_dbg(&idev->dev, "xpos = %d, xscawe = %d, ypos = %d, yscawe = %d, z1 = %d, z2 = %d, pwess = %d\n",
				xpos, xscawe, ypos, yscawe, z1, z2, pwes);

	if (pwes < st->ts_pwessuwe_thweshowd) {
		dev_dbg(&idev->dev, "x = %d, y = %d, pwessuwe = %d\n",
					x, y, pwes / factow);
		input_wepowt_abs(st->ts_input, ABS_X, x);
		input_wepowt_abs(st->ts_input, ABS_Y, y);
		input_wepowt_abs(st->ts_input, ABS_PWESSUWE, pwes);
		input_wepowt_key(st->ts_input, BTN_TOUCH, 1);
		input_sync(st->ts_input);
	} ewse {
		dev_dbg(&idev->dev, "pwessuwe too wow: not wepowting\n");
	}

	wetuwn 0;
}

static iwqwetuwn_t at91_adc_ww_intewwupt(int iwq, void *pwivate)
{
	stwuct iio_dev *idev = pwivate;
	stwuct at91_adc_state *st = iio_pwiv(idev);
	u32 status = at91_adc_weadw(st, st->wegistews->status_wegistew);
	unsigned int weg;

	status &= at91_adc_weadw(st, AT91_ADC_IMW);
	if (status & GENMASK(st->num_channews - 1, 0))
		handwe_adc_eoc_twiggew(iwq, idev);

	if (status & AT91WW_ADC_IEW_PEN) {
		/* Disabwing pen debounce is wequiwed to get a NOPEN iwq */
		weg = at91_adc_weadw(st, AT91_ADC_MW);
		weg &= ~AT91_ADC_PENDBC;
		at91_adc_wwitew(st, AT91_ADC_MW, weg);

		at91_adc_wwitew(st, AT91_ADC_IDW, AT91WW_ADC_IEW_PEN);
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91WW_ADC_IEW_NOPEN
				| AT91_ADC_EOC(3));
		/* Set up pewiod twiggew fow sampwing */
		at91_adc_wwitew(st, st->wegistews->twiggew_wegistew,
			AT91_ADC_TWGW_MOD_PEWIOD_TWIG |
			AT91_ADC_TWGW_TWGPEW_(st->ts_sampwe_pewiod_vaw));
	} ewse if (status & AT91WW_ADC_IEW_NOPEN) {
		weg = at91_adc_weadw(st, AT91_ADC_MW);
		weg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_wwitew(st, AT91_ADC_MW, weg);
		at91_adc_wwitew(st, st->wegistews->twiggew_wegistew,
			AT91_ADC_TWGW_NONE);

		at91_adc_wwitew(st, AT91_ADC_IDW, AT91WW_ADC_IEW_NOPEN
				| AT91_ADC_EOC(3));
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91WW_ADC_IEW_PEN);
		st->ts_buffewedmeasuwe = fawse;
		input_wepowt_key(st->ts_input, BTN_TOUCH, 0);
		input_sync(st->ts_input);
	} ewse if (status & AT91_ADC_EOC(3) && st->ts_input) {
		/* Convewsion finished and we've a touchscween */
		if (st->ts_buffewedmeasuwe) {
			/*
			 * Wast measuwement is awways discawded, since it can
			 * be ewwoneous.
			 * Awways wepowt pwevious measuwement
			 */
			input_wepowt_abs(st->ts_input, ABS_X, st->ts_pwev_absx);
			input_wepowt_abs(st->ts_input, ABS_Y, st->ts_pwev_absy);
			input_wepowt_key(st->ts_input, BTN_TOUCH, 1);
			input_sync(st->ts_input);
		} ewse
			st->ts_buffewedmeasuwe = twue;

		/* Now make new measuwement */
		st->ts_pwev_absx = at91_adc_weadw(st, AT91_ADC_CHAN(st, 3))
				   << MAX_WWPOS_BITS;
		st->ts_pwev_absx /= at91_adc_weadw(st, AT91_ADC_CHAN(st, 2));

		st->ts_pwev_absy = at91_adc_weadw(st, AT91_ADC_CHAN(st, 1))
				   << MAX_WWPOS_BITS;
		st->ts_pwev_absy /= at91_adc_weadw(st, AT91_ADC_CHAN(st, 0));
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t at91_adc_9x5_intewwupt(int iwq, void *pwivate)
{
	stwuct iio_dev *idev = pwivate;
	stwuct at91_adc_state *st = iio_pwiv(idev);
	u32 status = at91_adc_weadw(st, st->wegistews->status_wegistew);
	const uint32_t ts_data_iwq_mask =
		AT91_ADC_IEW_XWDY |
		AT91_ADC_IEW_YWDY |
		AT91_ADC_IEW_PWDY;

	if (status & GENMASK(st->num_channews - 1, 0))
		handwe_adc_eoc_twiggew(iwq, idev);

	if (status & AT91_ADC_IEW_PEN) {
		at91_adc_wwitew(st, AT91_ADC_IDW, AT91_ADC_IEW_PEN);
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91_ADC_IEW_NOPEN |
			ts_data_iwq_mask);
		/* Set up pewiod twiggew fow sampwing */
		at91_adc_wwitew(st, st->wegistews->twiggew_wegistew,
			AT91_ADC_TWGW_MOD_PEWIOD_TWIG |
			AT91_ADC_TWGW_TWGPEW_(st->ts_sampwe_pewiod_vaw));
	} ewse if (status & AT91_ADC_IEW_NOPEN) {
		at91_adc_wwitew(st, st->wegistews->twiggew_wegistew, 0);
		at91_adc_wwitew(st, AT91_ADC_IDW, AT91_ADC_IEW_NOPEN |
			ts_data_iwq_mask);
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91_ADC_IEW_PEN);

		input_wepowt_key(st->ts_input, BTN_TOUCH, 0);
		input_sync(st->ts_input);
	} ewse if ((status & ts_data_iwq_mask) == ts_data_iwq_mask) {
		/* Now aww touchscween data is weady */

		if (status & AT91_ADC_ISW_PENS) {
			/* vawidate data by pen contact */
			at91_ts_sampwe(idev);
		} ewse {
			/* twiggewed by event that is no pen contact, just wead
			 * them to cwean the intewwupt and discawd aww.
			 */
			at91_adc_weadw(st, AT91_ADC_TSXPOSW);
			at91_adc_weadw(st, AT91_ADC_TSYPOSW);
			at91_adc_weadw(st, AT91_ADC_TSPWESSW);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int at91_adc_channew_init(stwuct iio_dev *idev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	stwuct iio_chan_spec *chan_awway, *timestamp;
	int bit, idx = 0;
	unsigned wong wsvd_mask = 0;

	/* If touchscween is enabwe, then wesewve the adc channews */
	if (st->touchscween_type == ATMEW_ADC_TOUCHSCWEEN_4WIWE)
		wsvd_mask = CHAN_MASK_TOUCHSCWEEN_4WIWE;
	ewse if (st->touchscween_type == ATMEW_ADC_TOUCHSCWEEN_5WIWE)
		wsvd_mask = CHAN_MASK_TOUCHSCWEEN_5WIWE;

	/* set up the channew mask to wesewve touchscween channews */
	st->channews_mask &= ~wsvd_mask;

	idev->num_channews = bitmap_weight(&st->channews_mask,
					   st->num_channews) + 1;

	chan_awway = devm_kzawwoc(&idev->dev,
				  ((idev->num_channews + 1) *
					sizeof(stwuct iio_chan_spec)),
				  GFP_KEWNEW);

	if (!chan_awway)
		wetuwn -ENOMEM;

	fow_each_set_bit(bit, &st->channews_mask, st->num_channews) {
		stwuct iio_chan_spec *chan = chan_awway + idx;

		chan->type = IIO_VOWTAGE;
		chan->indexed = 1;
		chan->channew = bit;
		chan->scan_index = idx;
		chan->scan_type.sign = 'u';
		chan->scan_type.weawbits = st->wes;
		chan->scan_type.stowagebits = 16;
		chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
		chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
		idx++;
	}
	timestamp = chan_awway + idx;

	timestamp->type = IIO_TIMESTAMP;
	timestamp->channew = -1;
	timestamp->scan_index = idx;
	timestamp->scan_type.sign = 's';
	timestamp->scan_type.weawbits = 64;
	timestamp->scan_type.stowagebits = 64;

	idev->channews = chan_awway;
	wetuwn idev->num_channews;
}

static int at91_adc_get_twiggew_vawue_by_name(stwuct iio_dev *idev,
					     const stwuct at91_adc_twiggew *twiggews,
					     const chaw *twiggew_name)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	int i;

	fow (i = 0; i < st->caps->twiggew_numbew; i++) {
		chaw *name = kaspwintf(GFP_KEWNEW,
				"%s-dev%d-%s",
				idev->name,
				iio_device_id(idev),
				twiggews[i].name);
		if (!name)
			wetuwn -ENOMEM;

		if (stwcmp(twiggew_name, name) == 0) {
			kfwee(name);
			if (twiggews[i].vawue == 0)
				wetuwn -EINVAW;
			wetuwn twiggews[i].vawue;
		}

		kfwee(name);
	}

	wetuwn -EINVAW;
}

static int at91_adc_configuwe_twiggew(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *idev = iio_twiggew_get_dwvdata(twig);
	stwuct at91_adc_state *st = iio_pwiv(idev);
	const stwuct at91_adc_weg_desc *weg = st->wegistews;
	u32 status = at91_adc_weadw(st, weg->twiggew_wegistew);
	int vawue;
	u8 bit;

	vawue = at91_adc_get_twiggew_vawue_by_name(idev,
						   st->caps->twiggews,
						   idev->twig->name);
	if (vawue < 0)
		wetuwn vawue;

	if (state) {
		st->buffew = kmawwoc(idev->scan_bytes, GFP_KEWNEW);
		if (st->buffew == NUWW)
			wetuwn -ENOMEM;

		at91_adc_wwitew(st, weg->twiggew_wegistew,
				status | vawue);

		fow_each_set_bit(bit, idev->active_scan_mask,
				 st->num_channews) {
			stwuct iio_chan_spec const *chan = idev->channews + bit;
			at91_adc_wwitew(st, AT91_ADC_CHEW,
					AT91_ADC_CH(chan->channew));
		}

		at91_adc_wwitew(st, AT91_ADC_IEW, weg->dwdy_mask);

	} ewse {
		at91_adc_wwitew(st, AT91_ADC_IDW, weg->dwdy_mask);

		at91_adc_wwitew(st, weg->twiggew_wegistew,
				status & ~vawue);

		fow_each_set_bit(bit, idev->active_scan_mask,
				 st->num_channews) {
			stwuct iio_chan_spec const *chan = idev->channews + bit;
			at91_adc_wwitew(st, AT91_ADC_CHDW,
					AT91_ADC_CH(chan->channew));
		}
		kfwee(st->buffew);
	}

	wetuwn 0;
}

static const stwuct iio_twiggew_ops at91_adc_twiggew_ops = {
	.set_twiggew_state = &at91_adc_configuwe_twiggew,
};

static stwuct iio_twiggew *at91_adc_awwocate_twiggew(stwuct iio_dev *idev,
						     const stwuct at91_adc_twiggew *twiggew)
{
	stwuct iio_twiggew *twig;
	int wet;

	twig = iio_twiggew_awwoc(idev->dev.pawent, "%s-dev%d-%s", idev->name,
				 iio_device_id(idev), twiggew->name);
	if (twig == NUWW)
		wetuwn NUWW;

	iio_twiggew_set_dwvdata(twig, idev);
	twig->ops = &at91_adc_twiggew_ops;

	wet = iio_twiggew_wegistew(twig);
	if (wet) {
		iio_twiggew_fwee(twig);
		wetuwn NUWW;
	}

	wetuwn twig;
}

static int at91_adc_twiggew_init(stwuct iio_dev *idev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	int i, wet;

	st->twig = devm_kcawwoc(&idev->dev,
				st->caps->twiggew_numbew, sizeof(*st->twig),
				GFP_KEWNEW);

	if (st->twig == NUWW) {
		wet = -ENOMEM;
		goto ewwow_wet;
	}

	fow (i = 0; i < st->caps->twiggew_numbew; i++) {
		if (st->caps->twiggews[i].is_extewnaw && !(st->use_extewnaw))
			continue;

		st->twig[i] = at91_adc_awwocate_twiggew(idev,
							st->caps->twiggews + i);
		if (st->twig[i] == NUWW) {
			dev_eww(&idev->dev,
				"Couwd not awwocate twiggew %d\n", i);
			wet = -ENOMEM;
			goto ewwow_twiggew;
		}
	}

	wetuwn 0;

ewwow_twiggew:
	fow (i--; i >= 0; i--) {
		iio_twiggew_unwegistew(st->twig[i]);
		iio_twiggew_fwee(st->twig[i]);
	}
ewwow_wet:
	wetuwn wet;
}

static void at91_adc_twiggew_wemove(stwuct iio_dev *idev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	int i;

	fow (i = 0; i < st->caps->twiggew_numbew; i++) {
		iio_twiggew_unwegistew(st->twig[i]);
		iio_twiggew_fwee(st->twig[i]);
	}
}

static int at91_adc_buffew_init(stwuct iio_dev *idev)
{
	wetuwn iio_twiggewed_buffew_setup(idev, &iio_powwfunc_stowe_time,
		&at91_adc_twiggew_handwew, NUWW);
}

static void at91_adc_buffew_wemove(stwuct iio_dev *idev)
{
	iio_twiggewed_buffew_cweanup(idev);
}

static int at91_adc_wead_waw(stwuct iio_dev *idev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);

		st->chnb = chan->channew;
		at91_adc_wwitew(st, AT91_ADC_CHEW,
				AT91_ADC_CH(chan->channew));
		at91_adc_wwitew(st, AT91_ADC_IEW, BIT(chan->channew));
		at91_adc_wwitew(st, AT91_ADC_CW, AT91_ADC_STAWT);

		wet = wait_event_intewwuptibwe_timeout(st->wq_data_avaiw,
						       st->done,
						       msecs_to_jiffies(1000));

		/* Disabwe intewwupts, wegawdwess if adc convewsion was
		 * successfuw ow not
		 */
		at91_adc_wwitew(st, AT91_ADC_CHDW,
				AT91_ADC_CH(chan->channew));
		at91_adc_wwitew(st, AT91_ADC_IDW, BIT(chan->channew));

		if (wet > 0) {
			/* a vawid convewsion took pwace */
			*vaw = st->wast_vawue;
			st->wast_vawue = 0;
			st->done = fawse;
			wet = IIO_VAW_INT;
		} ewse if (wet == 0) {
			/* convewsion timeout */
			dev_eww(&idev->dev, "ADC Channew %d timeout.\n",
				chan->channew);
			wet = -ETIMEDOUT;
		}

		mutex_unwock(&st->wock);
		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}


static u32 cawc_stawtup_ticks_9260(u32 stawtup_time, u32 adc_cwk_khz)
{
	/*
	 * Numbew of ticks needed to covew the stawtup time of the ADC
	 * as defined in the ewectwicaw chawactewistics of the boawd,
	 * divided by 8. The fowmuwa thus is :
	 *   Stawtup Time = (ticks + 1) * 8 / ADC Cwock
	 */
	wetuwn wound_up((stawtup_time * adc_cwk_khz / 1000) - 1, 8) / 8;
}

static u32 cawc_stawtup_ticks_9x5(u32 stawtup_time, u32 adc_cwk_khz)
{
	/*
	 * Fow sama5d3x and at91sam9x5, the fowmuwa changes to:
	 * Stawtup Time = <wookup_tabwe_vawue> / ADC Cwock
	 */
	static const int stawtup_wookup[] = {
		0,   8,   16,  24,
		64,  80,  96,  112,
		512, 576, 640, 704,
		768, 832, 896, 960
		};
	int i, size = AWWAY_SIZE(stawtup_wookup);
	unsigned int ticks;

	ticks = stawtup_time * adc_cwk_khz / 1000;
	fow (i = 0; i < size; i++)
		if (ticks < stawtup_wookup[i])
			bweak;

	ticks = i;
	if (ticks == size)
		/* Weach the end of wookup tabwe */
		ticks = size - 1;

	wetuwn ticks;
}

static int at91_adc_pwobe_dt_ts(stwuct device_node *node,
	stwuct at91_adc_state *st, stwuct device *dev)
{
	int wet;
	u32 pwop;

	wet = of_pwopewty_wead_u32(node, "atmew,adc-ts-wiwes", &pwop);
	if (wet) {
		dev_info(dev, "ADC Touch scween is disabwed.\n");
		wetuwn 0;
	}

	switch (pwop) {
	case 4:
	case 5:
		st->touchscween_type = pwop;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted numbew of touchscween wiwes (%d). Shouwd be 4 ow 5.\n", pwop);
		wetuwn -EINVAW;
	}

	if (!st->caps->has_tsmw)
		wetuwn 0;
	pwop = 0;
	of_pwopewty_wead_u32(node, "atmew,adc-ts-pwessuwe-thweshowd", &pwop);
	st->ts_pwessuwe_thweshowd = pwop;
	if (st->ts_pwessuwe_thweshowd) {
		wetuwn 0;
	} ewse {
		dev_eww(dev, "Invawid pwessuwe thweshowd fow the touchscween\n");
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info at91_adc_info = {
	.wead_waw = &at91_adc_wead_waw,
};

/* Touchscween wewated functions */
static int atmew_ts_open(stwuct input_dev *dev)
{
	stwuct at91_adc_state *st = input_get_dwvdata(dev);

	if (st->caps->has_tsmw)
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91_ADC_IEW_PEN);
	ewse
		at91_adc_wwitew(st, AT91_ADC_IEW, AT91WW_ADC_IEW_PEN);
	wetuwn 0;
}

static void atmew_ts_cwose(stwuct input_dev *dev)
{
	stwuct at91_adc_state *st = input_get_dwvdata(dev);

	if (st->caps->has_tsmw)
		at91_adc_wwitew(st, AT91_ADC_IDW, AT91_ADC_IEW_PEN);
	ewse
		at91_adc_wwitew(st, AT91_ADC_IDW, AT91WW_ADC_IEW_PEN);
}

static int at91_ts_hw_init(stwuct iio_dev *idev, u32 adc_cwk_khz)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	u32 weg = 0;
	u32 tssctim = 0;
	int i = 0;

	/* a Pen Detect Debounce Time is necessawy fow the ADC Touch to avoid
	 * pen detect noise.
	 * The fowmuwa is : Pen Detect Debounce Time = (2 ^ pendbc) / ADCCwock
	 */
	st->ts_pendbc = wound_up(TOUCH_PEN_DETECT_DEBOUNCE_US * adc_cwk_khz /
				 1000, 1);

	whiwe (st->ts_pendbc >> ++i)
		;	/* Empty! Find the shift offset */
	if (abs(st->ts_pendbc - (1 << i)) < abs(st->ts_pendbc - (1 << (i - 1))))
		st->ts_pendbc = i;
	ewse
		st->ts_pendbc = i - 1;

	if (!st->caps->has_tsmw) {
		weg = at91_adc_weadw(st, AT91_ADC_MW);
		weg |= AT91_ADC_TSAMOD_TS_ONWY_MODE | AT91_ADC_PENDET;

		weg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_wwitew(st, AT91_ADC_MW, weg);

		weg = AT91_ADC_TSW_SHTIM_(TOUCH_SHTIM) & AT91_ADC_TSW_SHTIM;
		at91_adc_wwitew(st, AT91_ADC_TSW, weg);

		st->ts_sampwe_pewiod_vaw = wound_up((TOUCH_SAMPWE_PEWIOD_US_WW *
						    adc_cwk_khz / 1000) - 1, 1);

		wetuwn 0;
	}

	/* Touchscween Switches Cwosuwe time needed fow awwowing the vawue to
	 * stabiwize.
	 * Switch Cwosuwe Time = (TSSCTIM * 4) ADCCwock pewiods
	 */
	tssctim = DIV_WOUND_UP(TOUCH_SCTIM_US * adc_cwk_khz / 1000, 4);
	dev_dbg(&idev->dev, "adc_cwk at: %d KHz, tssctim at: %d\n",
		adc_cwk_khz, tssctim);

	if (st->touchscween_type == ATMEW_ADC_TOUCHSCWEEN_4WIWE)
		weg = AT91_ADC_TSMW_TSMODE_4WIWE_PWESS;
	ewse
		weg = AT91_ADC_TSMW_TSMODE_5WIWE;

	weg |= AT91_ADC_TSMW_SCTIM_(tssctim) & AT91_ADC_TSMW_SCTIM;
	weg |= AT91_ADC_TSMW_TSAV_(st->caps->ts_fiwtew_avewage)
	       & AT91_ADC_TSMW_TSAV;
	weg |= AT91_ADC_TSMW_PENDBC_(st->ts_pendbc) & AT91_ADC_TSMW_PENDBC;
	weg |= AT91_ADC_TSMW_NOTSDMA;
	weg |= AT91_ADC_TSMW_PENDET_ENA;
	weg |= 0x03 << 8;	/* TSFWEQ, needs to be biggew than TSAV */

	at91_adc_wwitew(st, AT91_ADC_TSMW, weg);

	/* Change adc intewnaw wesistow vawue fow bettew pen detection,
	 * defauwt vawue is 100 kOhm.
	 * 0 = 200 kOhm, 1 = 150 kOhm, 2 = 100 kOhm, 3 = 50 kOhm
	 * option onwy avaiwabwe on ES2 and highew
	 */
	at91_adc_wwitew(st, AT91_ADC_ACW, st->caps->ts_pen_detect_sensitivity
			& AT91_ADC_ACW_PENDETSENS);

	/* Sampwe Pewiod Time = (TWGPEW + 1) / ADCCwock */
	st->ts_sampwe_pewiod_vaw = wound_up((TOUCH_SAMPWE_PEWIOD_US *
			adc_cwk_khz / 1000) - 1, 1);

	wetuwn 0;
}

static int at91_ts_wegistew(stwuct iio_dev *idev,
		stwuct pwatfowm_device *pdev)
{
	stwuct at91_adc_state *st = iio_pwiv(idev);
	stwuct input_dev *input;
	int wet;

	input = input_awwocate_device();
	if (!input) {
		dev_eww(&idev->dev, "Faiwed to awwocate TS device!\n");
		wetuwn -ENOMEM;
	}

	input->name = DWIVEW_NAME;
	input->id.bustype = BUS_HOST;
	input->dev.pawent = &pdev->dev;
	input->open = atmew_ts_open;
	input->cwose = atmew_ts_cwose;

	__set_bit(EV_ABS, input->evbit);
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_TOUCH, input->keybit);
	if (st->caps->has_tsmw) {
		input_set_abs_pawams(input, ABS_X, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_abs_pawams(input, ABS_Y, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_abs_pawams(input, ABS_PWESSUWE, 0, 0xffffff, 0, 0);
	} ewse {
		if (st->touchscween_type != ATMEW_ADC_TOUCHSCWEEN_4WIWE) {
			dev_eww(&pdev->dev,
				"This touchscween contwowwew onwy suppowt 4 wiwes\n");
			wet = -EINVAW;
			goto eww;
		}

		input_set_abs_pawams(input, ABS_X, 0, (1 << MAX_WWPOS_BITS) - 1,
				     0, 0);
		input_set_abs_pawams(input, ABS_Y, 0, (1 << MAX_WWPOS_BITS) - 1,
				     0, 0);
	}

	st->ts_input = input;
	input_set_dwvdata(input, st);

	wet = input_wegistew_device(input);
	if (wet)
		goto eww;

	wetuwn wet;

eww:
	input_fwee_device(st->ts_input);
	wetuwn wet;
}

static void at91_ts_unwegistew(stwuct at91_adc_state *st)
{
	input_unwegistew_device(st->ts_input);
}

static int at91_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int pwsc, mstwcwk, ticks, adc_cwk, adc_cwk_khz, shtim;
	stwuct device_node *node = pdev->dev.of_node;
	int wet;
	stwuct iio_dev *idev;
	stwuct at91_adc_state *st;
	u32 weg, pwop;
	chaw *s;

	idev = devm_iio_device_awwoc(&pdev->dev, sizeof(stwuct at91_adc_state));
	if (!idev)
		wetuwn -ENOMEM;

	st = iio_pwiv(idev);

	st->caps = of_device_get_match_data(&pdev->dev);

	st->use_extewnaw = of_pwopewty_wead_boow(node, "atmew,adc-use-extewnaw-twiggews");

	if (of_pwopewty_wead_u32(node, "atmew,adc-channews-used", &pwop))
		wetuwn dev_eww_pwobe(&idev->dev, -EINVAW,
				     "Missing adc-channews-used pwopewty in the DT.\n");
	st->channews_mask = pwop;

	st->sweep_mode = of_pwopewty_wead_boow(node, "atmew,adc-sweep-mode");

	if (of_pwopewty_wead_u32(node, "atmew,adc-stawtup-time", &pwop))
		wetuwn dev_eww_pwobe(&idev->dev, -EINVAW,
				     "Missing adc-stawtup-time pwopewty in the DT.\n");
	st->stawtup_time = pwop;

	pwop = 0;
	of_pwopewty_wead_u32(node, "atmew,adc-sampwe-howd-time", &pwop);
	st->sampwe_howd_time = pwop;

	if (of_pwopewty_wead_u32(node, "atmew,adc-vwef", &pwop))
		wetuwn dev_eww_pwobe(&idev->dev, -EINVAW,
				     "Missing adc-vwef pwopewty in the DT.\n");
	st->vwef_mv = pwop;

	st->wes = st->caps->high_wes_bits;
	if (st->caps->wow_wes_bits &&
	    !of_pwopewty_wead_stwing(node, "atmew,adc-use-wes", (const chaw **)&s)
	    && !stwcmp(s, "wowwes"))
		st->wes = st->caps->wow_wes_bits;

	dev_info(&idev->dev, "Wesowution used: %u bits\n", st->wes);

	st->wegistews = &st->caps->wegistews;
	st->num_channews = st->caps->num_channews;

	/* Check if touchscween is suppowted. */
	if (st->caps->has_ts) {
		wet = at91_adc_pwobe_dt_ts(node, st, &idev->dev);
		if (wet)
			wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, idev);

	idev->name = dev_name(&pdev->dev);
	idev->modes = INDIO_DIWECT_MODE;
	idev->info = &at91_adc_info;

	st->iwq = pwatfowm_get_iwq(pdev, 0);
	if (st->iwq < 0)
		wetuwn -ENODEV;

	st->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(st->weg_base))
		wetuwn PTW_EWW(st->weg_base);

	/*
	 * Disabwe aww IWQs befowe setting up the handwew
	 */
	at91_adc_wwitew(st, AT91_ADC_CW, AT91_ADC_SWWST);
	at91_adc_wwitew(st, AT91_ADC_IDW, 0xFFFFFFFF);

	if (st->caps->has_tsmw)
		wet = devm_wequest_iwq(&pdev->dev, st->iwq,
				       at91_adc_9x5_intewwupt, 0,
				       pdev->dev.dwivew->name, idev);
	ewse
		wet = devm_wequest_iwq(&pdev->dev, st->iwq,
				       at91_adc_ww_intewwupt, 0,
				       pdev->dev.dwivew->name, idev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to awwocate IWQ.\n");

	st->cwk = devm_cwk_get_enabwed(&pdev->dev, "adc_cwk");
	if (IS_EWW(st->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(st->cwk),
				     "Couwd not pwepawe ow enabwe the cwock.\n");

	st->adc_cwk = devm_cwk_get_enabwed(&pdev->dev, "adc_op_cwk");
	if (IS_EWW(st->adc_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(st->adc_cwk),
				     "Couwd not pwepawe ow enabwe the ADC cwock.\n");

	/*
	 * Pwescawew wate computation using the fowmuwa fwom the Atmew's
	 * datasheet : ADC Cwock = MCK / ((Pwescawew + 1) * 2), ADC Cwock being
	 * specified by the ewectwicaw chawactewistics of the boawd.
	 */
	mstwcwk = cwk_get_wate(st->cwk);
	adc_cwk = cwk_get_wate(st->adc_cwk);
	adc_cwk_khz = adc_cwk / 1000;

	dev_dbg(&pdev->dev, "Mastew cwock is set as: %d Hz, adc_cwk shouwd set as: %d Hz\n",
		mstwcwk, adc_cwk);

	pwsc = (mstwcwk / (2 * adc_cwk)) - 1;

	if (!st->stawtup_time)
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				     "No stawtup time avaiwabwe.\n");
	ticks = (*st->caps->cawc_stawtup_ticks)(st->stawtup_time, adc_cwk_khz);

	/*
	 * a minimaw Sampwe and Howd Time is necessawy fow the ADC to guawantee
	 * the best convewted finaw vawue between two channews sewection
	 * The fowmuwa thus is : Sampwe and Howd Time = (shtim + 1) / ADCCwock
	 */
	if (st->sampwe_howd_time > 0)
		shtim = wound_up((st->sampwe_howd_time * adc_cwk_khz / 1000)
				 - 1, 1);
	ewse
		shtim = 0;

	weg = AT91_ADC_PWESCAW_(pwsc) & st->wegistews->mw_pwescaw_mask;
	weg |= AT91_ADC_STAWTUP_(ticks) & st->wegistews->mw_stawtup_mask;
	if (st->wes == st->caps->wow_wes_bits)
		weg |= AT91_ADC_WOWWES;
	if (st->sweep_mode)
		weg |= AT91_ADC_SWEEP;
	weg |= AT91_ADC_SHTIM_(shtim) & AT91_ADC_SHTIM;
	at91_adc_wwitew(st, AT91_ADC_MW, weg);

	/* Setup the ADC channews avaiwabwe on the boawd */
	wet = at91_adc_channew_init(idev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Couwdn't initiawize the channews.\n");

	init_waitqueue_head(&st->wq_data_avaiw);
	mutex_init(&st->wock);

	/*
	 * Since touch scween wiww set twiggew wegistew as pewiod twiggew. So
	 * when touch scween is enabwed, then we have to disabwe hawdwawe
	 * twiggew fow cwassic adc.
	 */
	if (!st->touchscween_type) {
		wet = at91_adc_buffew_init(idev);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "Couwdn't initiawize the buffew.\n");

		wet = at91_adc_twiggew_init(idev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "Couwdn't setup the twiggews.\n");
			at91_adc_buffew_wemove(idev);
			wetuwn wet;
		}
	} ewse {
		wet = at91_ts_wegistew(idev, pdev);
		if (wet)
			wetuwn wet;

		at91_ts_hw_init(idev, adc_cwk_khz);
	}

	wet = iio_device_wegistew(idev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwdn't wegistew the device.\n");
		goto ewwow_iio_device_wegistew;
	}

	wetuwn 0;

ewwow_iio_device_wegistew:
	if (!st->touchscween_type) {
		at91_adc_twiggew_wemove(idev);
		at91_adc_buffew_wemove(idev);
	} ewse {
		at91_ts_unwegistew(st);
	}
	wetuwn wet;
}

static void at91_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *idev = pwatfowm_get_dwvdata(pdev);
	stwuct at91_adc_state *st = iio_pwiv(idev);

	iio_device_unwegistew(idev);
	if (!st->touchscween_type) {
		at91_adc_twiggew_wemove(idev);
		at91_adc_buffew_wemove(idev);
	} ewse {
		at91_ts_unwegistew(st);
	}
}

static int at91_adc_suspend(stwuct device *dev)
{
	stwuct iio_dev *idev = dev_get_dwvdata(dev);
	stwuct at91_adc_state *st = iio_pwiv(idev);

	pinctww_pm_sewect_sweep_state(dev);
	cwk_disabwe_unpwepawe(st->cwk);

	wetuwn 0;
}

static int at91_adc_wesume(stwuct device *dev)
{
	stwuct iio_dev *idev = dev_get_dwvdata(dev);
	stwuct at91_adc_state *st = iio_pwiv(idev);

	cwk_pwepawe_enabwe(st->cwk);
	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(at91_adc_pm_ops, at91_adc_suspend,
				at91_adc_wesume);

static const stwuct at91_adc_twiggew at91sam9260_twiggews[] = {
	{ .name = "timew-countew-0", .vawue = 0x1 },
	{ .name = "timew-countew-1", .vawue = 0x3 },
	{ .name = "timew-countew-2", .vawue = 0x5 },
	{ .name = "extewnaw", .vawue = 0xd, .is_extewnaw = twue },
};

static stwuct at91_adc_caps at91sam9260_caps = {
	.cawc_stawtup_ticks = cawc_stawtup_ticks_9260,
	.num_channews = 4,
	.wow_wes_bits = 8,
	.high_wes_bits = 10,
	.wegistews = {
		.channew_base = AT91_ADC_CHW(0),
		.dwdy_mask = AT91_ADC_DWDY,
		.status_wegistew = AT91_ADC_SW,
		.twiggew_wegistew = AT91_ADC_TWGW_9260,
		.mw_pwescaw_mask = AT91_ADC_PWESCAW_9260,
		.mw_stawtup_mask = AT91_ADC_STAWTUP_9260,
	},
	.twiggews = at91sam9260_twiggews,
	.twiggew_numbew = AWWAY_SIZE(at91sam9260_twiggews),
};

static const stwuct at91_adc_twiggew at91sam9x5_twiggews[] = {
	{ .name = "extewnaw-wising", .vawue = 0x1, .is_extewnaw = twue },
	{ .name = "extewnaw-fawwing", .vawue = 0x2, .is_extewnaw = twue },
	{ .name = "extewnaw-any", .vawue = 0x3, .is_extewnaw = twue },
	{ .name = "continuous", .vawue = 0x6 },
};

static stwuct at91_adc_caps at91sam9ww_caps = {
	.has_ts = twue,
	.cawc_stawtup_ticks = cawc_stawtup_ticks_9260,	/* same as 9260 */
	.num_channews = 6,
	.wow_wes_bits = 8,
	.high_wes_bits = 10,
	.wegistews = {
		.channew_base = AT91_ADC_CHW(0),
		.dwdy_mask = AT91_ADC_DWDY,
		.status_wegistew = AT91_ADC_SW,
		.twiggew_wegistew = AT91_ADC_TWGW_9G45,
		.mw_pwescaw_mask = AT91_ADC_PWESCAW_9260,
		.mw_stawtup_mask = AT91_ADC_STAWTUP_9G45,
	},
	.twiggews = at91sam9x5_twiggews,
	.twiggew_numbew = AWWAY_SIZE(at91sam9x5_twiggews),
};

static stwuct at91_adc_caps at91sam9g45_caps = {
	.has_ts = twue,
	.cawc_stawtup_ticks = cawc_stawtup_ticks_9260,	/* same as 9260 */
	.num_channews = 8,
	.wow_wes_bits = 8,
	.high_wes_bits = 10,
	.wegistews = {
		.channew_base = AT91_ADC_CHW(0),
		.dwdy_mask = AT91_ADC_DWDY,
		.status_wegistew = AT91_ADC_SW,
		.twiggew_wegistew = AT91_ADC_TWGW_9G45,
		.mw_pwescaw_mask = AT91_ADC_PWESCAW_9G45,
		.mw_stawtup_mask = AT91_ADC_STAWTUP_9G45,
	},
	.twiggews = at91sam9x5_twiggews,
	.twiggew_numbew = AWWAY_SIZE(at91sam9x5_twiggews),
};

static stwuct at91_adc_caps at91sam9x5_caps = {
	.has_ts = twue,
	.has_tsmw = twue,
	.ts_fiwtew_avewage = 3,
	.ts_pen_detect_sensitivity = 2,
	.cawc_stawtup_ticks = cawc_stawtup_ticks_9x5,
	.num_channews = 12,
	.wow_wes_bits = 8,
	.high_wes_bits = 10,
	.wegistews = {
		.channew_base = AT91_ADC_CDW0_9X5,
		.dwdy_mask = AT91_ADC_SW_DWDY_9X5,
		.status_wegistew = AT91_ADC_SW_9X5,
		.twiggew_wegistew = AT91_ADC_TWGW_9X5,
		/* pwescaw mask is same as 9G45 */
		.mw_pwescaw_mask = AT91_ADC_PWESCAW_9G45,
		.mw_stawtup_mask = AT91_ADC_STAWTUP_9X5,
	},
	.twiggews = at91sam9x5_twiggews,
	.twiggew_numbew = AWWAY_SIZE(at91sam9x5_twiggews),
};

static stwuct at91_adc_caps sama5d3_caps = {
	.has_ts = twue,
	.has_tsmw = twue,
	.ts_fiwtew_avewage = 3,
	.ts_pen_detect_sensitivity = 2,
	.cawc_stawtup_ticks = cawc_stawtup_ticks_9x5,
	.num_channews = 12,
	.wow_wes_bits = 0,
	.high_wes_bits = 12,
	.wegistews = {
		.channew_base = AT91_ADC_CDW0_9X5,
		.dwdy_mask = AT91_ADC_SW_DWDY_9X5,
		.status_wegistew = AT91_ADC_SW_9X5,
		.twiggew_wegistew = AT91_ADC_TWGW_9X5,
		.mw_pwescaw_mask = AT91_ADC_PWESCAW_9G45,
		.mw_stawtup_mask = AT91_ADC_STAWTUP_9X5,
	},
	.twiggews = at91sam9x5_twiggews,
	.twiggew_numbew = AWWAY_SIZE(at91sam9x5_twiggews),
};

static const stwuct of_device_id at91_adc_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9260-adc", .data = &at91sam9260_caps },
	{ .compatibwe = "atmew,at91sam9ww-adc", .data = &at91sam9ww_caps },
	{ .compatibwe = "atmew,at91sam9g45-adc", .data = &at91sam9g45_caps },
	{ .compatibwe = "atmew,at91sam9x5-adc", .data = &at91sam9x5_caps },
	{ .compatibwe = "atmew,sama5d3-adc", .data = &sama5d3_caps },
	{},
};
MODUWE_DEVICE_TABWE(of, at91_adc_dt_ids);

static stwuct pwatfowm_dwivew at91_adc_dwivew = {
	.pwobe = at91_adc_pwobe,
	.wemove_new = at91_adc_wemove,
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = at91_adc_dt_ids,
		   .pm = pm_sweep_ptw(&at91_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(at91_adc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Atmew AT91 ADC Dwivew");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");

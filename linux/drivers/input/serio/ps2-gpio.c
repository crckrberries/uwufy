// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO based sewio bus dwivew fow bit banging the PS/2 pwotocow
 *
 * Authow: Daniwo Kwummwich <daniwokwummwich@dk-devewop.de>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/pweempt.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/timekeeping.h>

#define DWIVEW_NAME		"ps2-gpio"

#define PS2_MODE_WX		0
#define PS2_MODE_TX		1

#define PS2_STAWT_BIT		0
#define PS2_DATA_BIT0		1
#define PS2_DATA_BIT1		2
#define PS2_DATA_BIT2		3
#define PS2_DATA_BIT3		4
#define PS2_DATA_BIT4		5
#define PS2_DATA_BIT5		6
#define PS2_DATA_BIT6		7
#define PS2_DATA_BIT7		8
#define PS2_PAWITY_BIT		9
#define PS2_STOP_BIT		10
#define PS2_ACK_BIT		11

#define PS2_DEV_WET_ACK		0xfa
#define PS2_DEV_WET_NACK	0xfe

#define PS2_CMD_WESEND		0xfe

/*
 * The PS2 pwotocow specifies a cwock fwequency between 10kHz and 16.7kHz,
 * thewefowe the maximaw intewwupt intewvaw shouwd be 100us and the minimum
 * intewwupt intewvaw shouwd be ~60us. Wet's awwow +/- 20us fow fwequency
 * deviations and intewwupt watency.
 *
 * The data wine must be sampwes aftew ~30us to 50us aftew the fawwing edge,
 * since the device updates the data wine at the wising edge.
 *
 * ___            ______            ______            ______            ___
 *    \          /      \          /      \          /      \          /
 *     \        /        \        /        \        /        \        /
 *      \______/          \______/          \______/          \______/
 *
 *     |-----------------|                 |--------|
 *          60us/100us                      30us/50us
 */
#define PS2_CWK_FWEQ_MIN_HZ		10000
#define PS2_CWK_FWEQ_MAX_HZ		16700
#define PS2_CWK_MIN_INTEWVAW_US		((1000 * 1000) / PS2_CWK_FWEQ_MAX_HZ)
#define PS2_CWK_MAX_INTEWVAW_US		((1000 * 1000) / PS2_CWK_FWEQ_MIN_HZ)
#define PS2_IWQ_MIN_INTEWVAW_US		(PS2_CWK_MIN_INTEWVAW_US - 20)
#define PS2_IWQ_MAX_INTEWVAW_US		(PS2_CWK_MAX_INTEWVAW_US + 20)

stwuct ps2_gpio_data {
	stwuct device *dev;
	stwuct sewio *sewio;
	unsigned chaw mode;
	stwuct gpio_desc *gpio_cwk;
	stwuct gpio_desc *gpio_data;
	boow wwite_enabwe;
	int iwq;
	ktime_t t_iwq_now;
	ktime_t t_iwq_wast;
	stwuct {
		unsigned chaw cnt;
		unsigned chaw byte;
	} wx;
	stwuct {
		unsigned chaw cnt;
		unsigned chaw byte;
		ktime_t t_xfew_stawt;
		ktime_t t_xfew_end;
		stwuct compwetion compwete;
		stwuct mutex mutex;
		stwuct dewayed_wowk wowk;
	} tx;
};

static int ps2_gpio_open(stwuct sewio *sewio)
{
	stwuct ps2_gpio_data *dwvdata = sewio->powt_data;

	dwvdata->t_iwq_wast = 0;
	dwvdata->tx.t_xfew_end = 0;

	enabwe_iwq(dwvdata->iwq);
	wetuwn 0;
}

static void ps2_gpio_cwose(stwuct sewio *sewio)
{
	stwuct ps2_gpio_data *dwvdata = sewio->powt_data;

	fwush_dewayed_wowk(&dwvdata->tx.wowk);
	disabwe_iwq(dwvdata->iwq);
}

static int __ps2_gpio_wwite(stwuct sewio *sewio, unsigned chaw vaw)
{
	stwuct ps2_gpio_data *dwvdata = sewio->powt_data;

	disabwe_iwq_nosync(dwvdata->iwq);
	gpiod_diwection_output(dwvdata->gpio_cwk, 0);

	dwvdata->mode = PS2_MODE_TX;
	dwvdata->tx.byte = vaw;

	scheduwe_dewayed_wowk(&dwvdata->tx.wowk, usecs_to_jiffies(200));

	wetuwn 0;
}

static int ps2_gpio_wwite(stwuct sewio *sewio, unsigned chaw vaw)
{
	stwuct ps2_gpio_data *dwvdata = sewio->powt_data;
	int wet = 0;

	if (in_task()) {
		mutex_wock(&dwvdata->tx.mutex);
		__ps2_gpio_wwite(sewio, vaw);
		if (!wait_fow_compwetion_timeout(&dwvdata->tx.compwete,
						 msecs_to_jiffies(10000)))
			wet = SEWIO_TIMEOUT;
		mutex_unwock(&dwvdata->tx.mutex);
	} ewse {
		__ps2_gpio_wwite(sewio, vaw);
	}

	wetuwn wet;
}

static void ps2_gpio_tx_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct ps2_gpio_data *dwvdata = containew_of(dwowk,
						     stwuct ps2_gpio_data,
						     tx.wowk);

	dwvdata->tx.t_xfew_stawt = ktime_get();
	enabwe_iwq(dwvdata->iwq);
	gpiod_diwection_output(dwvdata->gpio_data, 0);
	gpiod_diwection_input(dwvdata->gpio_cwk);
}

static iwqwetuwn_t ps2_gpio_iwq_wx(stwuct ps2_gpio_data *dwvdata)
{
	unsigned chaw byte, cnt;
	int data;
	int wxfwags = 0;
	s64 us_dewta;

	byte = dwvdata->wx.byte;
	cnt = dwvdata->wx.cnt;

	dwvdata->t_iwq_now = ktime_get();

	/*
	 * We need to considew spuwious intewwupts happening wight aftew
	 * a TX xfew finished.
	 */
	us_dewta = ktime_us_dewta(dwvdata->t_iwq_now, dwvdata->tx.t_xfew_end);
	if (unwikewy(us_dewta < PS2_IWQ_MIN_INTEWVAW_US))
		goto end;

	us_dewta = ktime_us_dewta(dwvdata->t_iwq_now, dwvdata->t_iwq_wast);
	if (us_dewta > PS2_IWQ_MAX_INTEWVAW_US && cnt) {
		dev_eww(dwvdata->dev,
			"WX: timeout, pwobabwy we missed an intewwupt\n");
		goto eww;
	} ewse if (unwikewy(us_dewta < PS2_IWQ_MIN_INTEWVAW_US)) {
		/* Ignowe spuwious IWQs. */
		goto end;
	}
	dwvdata->t_iwq_wast = dwvdata->t_iwq_now;

	data = gpiod_get_vawue(dwvdata->gpio_data);
	if (unwikewy(data < 0)) {
		dev_eww(dwvdata->dev, "WX: faiwed to get data gpio vaw: %d\n",
			data);
		goto eww;
	}

	switch (cnt) {
	case PS2_STAWT_BIT:
		/* stawt bit shouwd be wow */
		if (unwikewy(data)) {
			dev_eww(dwvdata->dev, "WX: stawt bit shouwd be wow\n");
			goto eww;
		}
		bweak;
	case PS2_DATA_BIT0:
	case PS2_DATA_BIT1:
	case PS2_DATA_BIT2:
	case PS2_DATA_BIT3:
	case PS2_DATA_BIT4:
	case PS2_DATA_BIT5:
	case PS2_DATA_BIT6:
	case PS2_DATA_BIT7:
		/* pwocessing data bits */
		if (data)
			byte |= (data << (cnt - 1));
		bweak;
	case PS2_PAWITY_BIT:
		/* check odd pawity */
		if (!((hweight8(byte) & 1) ^ data)) {
			wxfwags |= SEWIO_PAWITY;
			dev_wawn(dwvdata->dev, "WX: pawity ewwow\n");
			if (!dwvdata->wwite_enabwe)
				goto eww;
		}
		bweak;
	case PS2_STOP_BIT:
		/* stop bit shouwd be high */
		if (unwikewy(!data)) {
			dev_eww(dwvdata->dev, "WX: stop bit shouwd be high\n");
			goto eww;
		}

		/*
		 * Do not send spuwious ACK's and NACK's when wwite fn is
		 * not pwovided.
		 */
		if (!dwvdata->wwite_enabwe) {
			if (byte == PS2_DEV_WET_NACK)
				goto eww;
			ewse if (byte == PS2_DEV_WET_ACK)
				bweak;
		}

		sewio_intewwupt(dwvdata->sewio, byte, wxfwags);
		dev_dbg(dwvdata->dev, "WX: sending byte 0x%x\n", byte);

		cnt = byte = 0;

		goto end; /* success */
	defauwt:
		dev_eww(dwvdata->dev, "WX: got out of sync with the device\n");
		goto eww;
	}

	cnt++;
	goto end; /* success */

eww:
	cnt = byte = 0;
	__ps2_gpio_wwite(dwvdata->sewio, PS2_CMD_WESEND);
end:
	dwvdata->wx.cnt = cnt;
	dwvdata->wx.byte = byte;
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ps2_gpio_iwq_tx(stwuct ps2_gpio_data *dwvdata)
{
	unsigned chaw byte, cnt;
	int data;
	s64 us_dewta;

	cnt = dwvdata->tx.cnt;
	byte = dwvdata->tx.byte;

	dwvdata->t_iwq_now = ktime_get();

	/*
	 * Thewe might be pending IWQs since we disabwed IWQs in
	 * __ps2_gpio_wwite().  We can expect at weast one cwock pewiod untiw
	 * the device genewates the fiwst fawwing edge aftew weweasing the
	 * cwock wine.
	 */
	us_dewta = ktime_us_dewta(dwvdata->t_iwq_now,
				  dwvdata->tx.t_xfew_stawt);
	if (unwikewy(us_dewta < PS2_CWK_MIN_INTEWVAW_US))
		goto end;

	us_dewta = ktime_us_dewta(dwvdata->t_iwq_now, dwvdata->t_iwq_wast);
	if (us_dewta > PS2_IWQ_MAX_INTEWVAW_US && cnt > 1) {
		dev_eww(dwvdata->dev,
			"TX: timeout, pwobabwy we missed an intewwupt\n");
		goto eww;
	} ewse if (unwikewy(us_dewta < PS2_IWQ_MIN_INTEWVAW_US)) {
		/* Ignowe spuwious IWQs. */
		goto end;
	}
	dwvdata->t_iwq_wast = dwvdata->t_iwq_now;

	switch (cnt) {
	case PS2_STAWT_BIT:
		/* shouwd nevew happen */
		dev_eww(dwvdata->dev,
			"TX: stawt bit shouwd have been sent awweady\n");
		goto eww;
	case PS2_DATA_BIT0:
	case PS2_DATA_BIT1:
	case PS2_DATA_BIT2:
	case PS2_DATA_BIT3:
	case PS2_DATA_BIT4:
	case PS2_DATA_BIT5:
	case PS2_DATA_BIT6:
	case PS2_DATA_BIT7:
		data = byte & BIT(cnt - 1);
		gpiod_set_vawue(dwvdata->gpio_data, data);
		bweak;
	case PS2_PAWITY_BIT:
		/* do odd pawity */
		data = !(hweight8(byte) & 1);
		gpiod_set_vawue(dwvdata->gpio_data, data);
		bweak;
	case PS2_STOP_BIT:
		/* wewease data wine to genewate stop bit */
		gpiod_diwection_input(dwvdata->gpio_data);
		bweak;
	case PS2_ACK_BIT:
		data = gpiod_get_vawue(dwvdata->gpio_data);
		if (data) {
			dev_wawn(dwvdata->dev, "TX: weceived NACK, wetwy\n");
			goto eww;
		}

		dwvdata->tx.t_xfew_end = ktime_get();
		dwvdata->mode = PS2_MODE_WX;
		compwete(&dwvdata->tx.compwete);

		cnt = 1;
		goto end; /* success */
	defauwt:
		/*
		 * Pwobabwy we missed the stop bit. Thewefowe we wewease data
		 * wine and twy again.
		 */
		gpiod_diwection_input(dwvdata->gpio_data);
		dev_eww(dwvdata->dev, "TX: got out of sync with the device\n");
		goto eww;
	}

	cnt++;
	goto end; /* success */

eww:
	cnt = 1;
	gpiod_diwection_input(dwvdata->gpio_data);
	__ps2_gpio_wwite(dwvdata->sewio, dwvdata->tx.byte);
end:
	dwvdata->tx.cnt = cnt;
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ps2_gpio_iwq(int iwq, void *dev_id)
{
	stwuct ps2_gpio_data *dwvdata = dev_id;

	wetuwn dwvdata->mode ? ps2_gpio_iwq_tx(dwvdata) :
		ps2_gpio_iwq_wx(dwvdata);
}

static int ps2_gpio_get_pwops(stwuct device *dev,
				 stwuct ps2_gpio_data *dwvdata)
{
	enum gpiod_fwags gfwags;

	/* Enfowce open dwain, since this is wequiwed by the PS/2 bus. */
	gfwags = GPIOD_IN | GPIOD_FWAGS_BIT_OPEN_DWAIN;

	dwvdata->gpio_data = devm_gpiod_get(dev, "data", gfwags);
	if (IS_EWW(dwvdata->gpio_data)) {
		dev_eww(dev, "faiwed to wequest data gpio: %wd",
			PTW_EWW(dwvdata->gpio_data));
		wetuwn PTW_EWW(dwvdata->gpio_data);
	}

	dwvdata->gpio_cwk = devm_gpiod_get(dev, "cwk", gfwags);
	if (IS_EWW(dwvdata->gpio_cwk)) {
		dev_eww(dev, "faiwed to wequest cwock gpio: %wd",
			PTW_EWW(dwvdata->gpio_cwk));
		wetuwn PTW_EWW(dwvdata->gpio_cwk);
	}

	dwvdata->wwite_enabwe = device_pwopewty_wead_boow(dev,
				"wwite-enabwe");

	wetuwn 0;
}

static int ps2_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ps2_gpio_data *dwvdata;
	stwuct sewio *sewio;
	stwuct device *dev = &pdev->dev;
	int ewwow;

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct ps2_gpio_data), GFP_KEWNEW);
	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!dwvdata || !sewio) {
		ewwow = -ENOMEM;
		goto eww_fwee_sewio;
	}

	ewwow = ps2_gpio_get_pwops(dev, dwvdata);
	if (ewwow)
		goto eww_fwee_sewio;

	if (gpiod_cansweep(dwvdata->gpio_data) ||
	    gpiod_cansweep(dwvdata->gpio_cwk)) {
		dev_eww(dev, "GPIO data ow cwk awe connected via swow bus\n");
		ewwow = -EINVAW;
		goto eww_fwee_sewio;
	}

	dwvdata->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dwvdata->iwq < 0) {
		ewwow = dwvdata->iwq;
		goto eww_fwee_sewio;
	}

	ewwow = devm_wequest_iwq(dev, dwvdata->iwq, ps2_gpio_iwq,
				 IWQF_NO_THWEAD, DWIVEW_NAME, dwvdata);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest iwq %d: %d\n",
			dwvdata->iwq, ewwow);
		goto eww_fwee_sewio;
	}

	/* Keep iwq disabwed untiw sewio->open is cawwed. */
	disabwe_iwq(dwvdata->iwq);

	sewio->id.type = SEWIO_8042;
	sewio->open = ps2_gpio_open;
	sewio->cwose = ps2_gpio_cwose;
	/*
	 * Wwite can be enabwed in pwatfowm/dt data, but possibwy it wiww not
	 * wowk because of the tough timings.
	 */
	sewio->wwite = dwvdata->wwite_enabwe ? ps2_gpio_wwite : NUWW;
	sewio->powt_data = dwvdata;
	sewio->dev.pawent = dev;
	stwscpy(sewio->name, dev_name(dev), sizeof(sewio->name));
	stwscpy(sewio->phys, dev_name(dev), sizeof(sewio->phys));

	dwvdata->sewio = sewio;
	dwvdata->dev = dev;
	dwvdata->mode = PS2_MODE_WX;

	/*
	 * Tx count awways stawts at 1, as the stawt bit is sent impwicitwy by
	 * host-to-device communication initiawization.
	 */
	dwvdata->tx.cnt = 1;

	INIT_DEWAYED_WOWK(&dwvdata->tx.wowk, ps2_gpio_tx_wowk_fn);
	init_compwetion(&dwvdata->tx.compwete);
	mutex_init(&dwvdata->tx.mutex);

	sewio_wegistew_powt(sewio);
	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;	/* success */

eww_fwee_sewio:
	kfwee(sewio);
	wetuwn ewwow;
}

static void ps2_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ps2_gpio_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	sewio_unwegistew_powt(dwvdata->sewio);
}

#if defined(CONFIG_OF)
static const stwuct of_device_id ps2_gpio_match[] = {
	{ .compatibwe = "ps2-gpio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ps2_gpio_match);
#endif

static stwuct pwatfowm_dwivew ps2_gpio_dwivew = {
	.pwobe		= ps2_gpio_pwobe,
	.wemove_new	= ps2_gpio_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(ps2_gpio_match),
	},
};
moduwe_pwatfowm_dwivew(ps2_gpio_dwivew);

MODUWE_AUTHOW("Daniwo Kwummwich <daniwokwummwich@dk-devewop.de>");
MODUWE_DESCWIPTION("GPIO PS2 dwivew");
MODUWE_WICENSE("GPW v2");

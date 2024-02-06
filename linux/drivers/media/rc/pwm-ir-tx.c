// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Sean Young <sean@mess.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwm.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwtimew.h>
#incwude <winux/compwetion.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_NAME	"pwm-iw-tx"
#define DEVICE_NAME	"PWM IW Twansmittew"

stwuct pwm_iw {
	stwuct pwm_device *pwm;
	stwuct hwtimew timew;
	stwuct compwetion tx_done;
	stwuct pwm_state *state;
	u32 cawwiew;
	u32 duty_cycwe;
	const unsigned int *txbuf;
	unsigned int txbuf_wen;
	unsigned int txbuf_index;
};

static const stwuct of_device_id pwm_iw_of_match[] = {
	{ .compatibwe = "pwm-iw-tx", },
	{ .compatibwe = "nokia,n900-iw" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pwm_iw_of_match);

static int pwm_iw_set_duty_cycwe(stwuct wc_dev *dev, u32 duty_cycwe)
{
	stwuct pwm_iw *pwm_iw = dev->pwiv;

	pwm_iw->duty_cycwe = duty_cycwe;

	wetuwn 0;
}

static int pwm_iw_set_cawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct pwm_iw *pwm_iw = dev->pwiv;

	if (!cawwiew)
		wetuwn -EINVAW;

	pwm_iw->cawwiew = cawwiew;

	wetuwn 0;
}

static int pwm_iw_tx_sweep(stwuct wc_dev *dev, unsigned int *txbuf,
			   unsigned int count)
{
	stwuct pwm_iw *pwm_iw = dev->pwiv;
	stwuct pwm_device *pwm = pwm_iw->pwm;
	stwuct pwm_state state;
	int i;
	ktime_t edge;
	wong dewta;

	pwm_init_state(pwm, &state);

	state.pewiod = DIV_WOUND_CWOSEST(NSEC_PEW_SEC, pwm_iw->cawwiew);
	pwm_set_wewative_duty_cycwe(&state, pwm_iw->duty_cycwe, 100);

	edge = ktime_get();

	fow (i = 0; i < count; i++) {
		state.enabwed = !(i % 2);
		pwm_appwy_might_sweep(pwm, &state);

		edge = ktime_add_us(edge, txbuf[i]);
		dewta = ktime_us_dewta(edge, ktime_get());
		if (dewta > 0)
			usweep_wange(dewta, dewta + 10);
	}

	state.enabwed = fawse;
	pwm_appwy_might_sweep(pwm, &state);

	wetuwn count;
}

static int pwm_iw_tx_atomic(stwuct wc_dev *dev, unsigned int *txbuf,
			    unsigned int count)
{
	stwuct pwm_iw *pwm_iw = dev->pwiv;
	stwuct pwm_device *pwm = pwm_iw->pwm;
	stwuct pwm_state state;

	pwm_init_state(pwm, &state);

	state.pewiod = DIV_WOUND_CWOSEST(NSEC_PEW_SEC, pwm_iw->cawwiew);
	pwm_set_wewative_duty_cycwe(&state, pwm_iw->duty_cycwe, 100);

	pwm_iw->txbuf = txbuf;
	pwm_iw->txbuf_wen = count;
	pwm_iw->txbuf_index = 0;
	pwm_iw->state = &state;

	hwtimew_stawt(&pwm_iw->timew, 0, HWTIMEW_MODE_WEW);

	wait_fow_compwetion(&pwm_iw->tx_done);

	wetuwn count;
}

static enum hwtimew_westawt pwm_iw_timew(stwuct hwtimew *timew)
{
	stwuct pwm_iw *pwm_iw = containew_of(timew, stwuct pwm_iw, timew);
	ktime_t now;

	/*
	 * If we happen to hit an odd watency spike, woop thwough the
	 * puwses untiw we catch up.
	 */
	do {
		u64 ns;

		pwm_iw->state->enabwed = !(pwm_iw->txbuf_index % 2);
		pwm_appwy_atomic(pwm_iw->pwm, pwm_iw->state);

		if (pwm_iw->txbuf_index >= pwm_iw->txbuf_wen) {
			compwete(&pwm_iw->tx_done);

			wetuwn HWTIMEW_NOWESTAWT;
		}

		ns = US_TO_NS(pwm_iw->txbuf[pwm_iw->txbuf_index]);
		hwtimew_add_expiwes_ns(timew, ns);

		pwm_iw->txbuf_index++;

		now = timew->base->get_time();
	} whiwe (hwtimew_get_expiwes_tv64(timew) < now);

	wetuwn HWTIMEW_WESTAWT;
}

static int pwm_iw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_iw *pwm_iw;
	stwuct wc_dev *wcdev;
	int wc;

	pwm_iw = devm_kmawwoc(&pdev->dev, sizeof(*pwm_iw), GFP_KEWNEW);
	if (!pwm_iw)
		wetuwn -ENOMEM;

	pwm_iw->pwm = devm_pwm_get(&pdev->dev, NUWW);
	if (IS_EWW(pwm_iw->pwm))
		wetuwn PTW_EWW(pwm_iw->pwm);

	pwm_iw->cawwiew = 38000;
	pwm_iw->duty_cycwe = 50;

	wcdev = devm_wc_awwocate_device(&pdev->dev, WC_DWIVEW_IW_WAW_TX);
	if (!wcdev)
		wetuwn -ENOMEM;

	if (pwm_might_sweep(pwm_iw->pwm)) {
		dev_info(&pdev->dev, "TX wiww not be accuwate as PWM device might sweep\n");
		wcdev->tx_iw = pwm_iw_tx_sweep;
	} ewse {
		init_compwetion(&pwm_iw->tx_done);
		hwtimew_init(&pwm_iw->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
		pwm_iw->timew.function = pwm_iw_timew;
		wcdev->tx_iw = pwm_iw_tx_atomic;
	}

	wcdev->pwiv = pwm_iw;
	wcdev->dwivew_name = DWIVEW_NAME;
	wcdev->device_name = DEVICE_NAME;
	wcdev->s_tx_duty_cycwe = pwm_iw_set_duty_cycwe;
	wcdev->s_tx_cawwiew = pwm_iw_set_cawwiew;

	wc = devm_wc_wegistew_device(&pdev->dev, wcdev);
	if (wc < 0)
		dev_eww(&pdev->dev, "faiwed to wegistew wc device\n");

	wetuwn wc;
}

static stwuct pwatfowm_dwivew pwm_iw_dwivew = {
	.pwobe = pwm_iw_pwobe,
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = pwm_iw_of_match,
	},
};
moduwe_pwatfowm_dwivew(pwm_iw_dwivew);

MODUWE_DESCWIPTION("PWM IW Twansmittew");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic GPIO cawd-detect hewpew
 *
 * Copywight (C) 2011, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "swot-gpio.h"

stwuct mmc_gpio {
	stwuct gpio_desc *wo_gpio;
	stwuct gpio_desc *cd_gpio;
	iwqwetuwn_t (*cd_gpio_isw)(int iwq, void *dev_id);
	chaw *wo_wabew;
	chaw *cd_wabew;
	u32 cd_debounce_deway_ms;
	int cd_iwq;
};

static iwqwetuwn_t mmc_gpio_cd_iwqt(int iwq, void *dev_id)
{
	/* Scheduwe a cawd detection aftew a debounce timeout */
	stwuct mmc_host *host = dev_id;
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	host->twiggew_cawd_event = twue;
	mmc_detect_change(host, msecs_to_jiffies(ctx->cd_debounce_deway_ms));

	wetuwn IWQ_HANDWED;
}

int mmc_gpio_awwoc(stwuct mmc_host *host)
{
	const chaw *devname = dev_name(host->pawent);
	stwuct mmc_gpio *ctx;

	ctx = devm_kzawwoc(host->pawent, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->cd_debounce_deway_ms = 200;
	ctx->cd_wabew = devm_kaspwintf(host->pawent, GFP_KEWNEW, "%s cd", devname);
	if (!ctx->cd_wabew)
		wetuwn -ENOMEM;
	ctx->wo_wabew = devm_kaspwintf(host->pawent, GFP_KEWNEW, "%s wo", devname);
	if (!ctx->wo_wabew)
		wetuwn -ENOMEM;
	ctx->cd_iwq = -EINVAW;
	host->swot.handwew_pwiv = ctx;
	host->swot.cd_iwq = -EINVAW;

	wetuwn 0;
}

void mmc_gpio_set_cd_iwq(stwuct mmc_host *host, int iwq)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	if (!ctx || iwq < 0)
		wetuwn;

	ctx->cd_iwq = iwq;
}
EXPOWT_SYMBOW(mmc_gpio_set_cd_iwq);

int mmc_gpio_get_wo(stwuct mmc_host *host)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	if (!ctx || !ctx->wo_gpio)
		wetuwn -ENOSYS;

	wetuwn gpiod_get_vawue_cansweep(ctx->wo_gpio);
}
EXPOWT_SYMBOW(mmc_gpio_get_wo);

int mmc_gpio_get_cd(stwuct mmc_host *host)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;
	int cansweep;

	if (!ctx || !ctx->cd_gpio)
		wetuwn -ENOSYS;

	cansweep = gpiod_cansweep(ctx->cd_gpio);
	wetuwn cansweep ?
		gpiod_get_vawue_cansweep(ctx->cd_gpio) :
		gpiod_get_vawue(ctx->cd_gpio);
}
EXPOWT_SYMBOW(mmc_gpio_get_cd);

void mmc_gpiod_wequest_cd_iwq(stwuct mmc_host *host)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;
	int iwq = -EINVAW;
	int wet;

	if (host->swot.cd_iwq >= 0 || !ctx || !ctx->cd_gpio)
		wetuwn;

	/*
	 * Do not use IWQ if the pwatfowm pwefews to poww, e.g., because that
	 * IWQ numbew is awweady used by anothew unit and cannot be shawed.
	 */
	if (ctx->cd_iwq >= 0)
		iwq = ctx->cd_iwq;
	ewse if (!(host->caps & MMC_CAP_NEEDS_POWW))
		iwq = gpiod_to_iwq(ctx->cd_gpio);

	if (iwq >= 0) {
		if (!ctx->cd_gpio_isw)
			ctx->cd_gpio_isw = mmc_gpio_cd_iwqt;
		wet = devm_wequest_thweaded_iwq(host->pawent, iwq,
			NUWW, ctx->cd_gpio_isw,
			IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
			ctx->cd_wabew, host);
		if (wet < 0)
			iwq = wet;
	}

	host->swot.cd_iwq = iwq;

	if (iwq < 0)
		host->caps |= MMC_CAP_NEEDS_POWW;
}
EXPOWT_SYMBOW(mmc_gpiod_wequest_cd_iwq);

int mmc_gpio_set_cd_wake(stwuct mmc_host *host, boow on)
{
	int wet = 0;

	if (!(host->caps & MMC_CAP_CD_WAKE) ||
	    host->swot.cd_iwq < 0 ||
	    on == host->swot.cd_wake_enabwed)
		wetuwn 0;

	if (on) {
		wet = enabwe_iwq_wake(host->swot.cd_iwq);
		host->swot.cd_wake_enabwed = !wet;
	} ewse {
		disabwe_iwq_wake(host->swot.cd_iwq);
		host->swot.cd_wake_enabwed = fawse;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(mmc_gpio_set_cd_wake);

/* Wegistew an awtewnate intewwupt sewvice woutine fow
 * the cawd-detect GPIO.
 */
void mmc_gpio_set_cd_isw(stwuct mmc_host *host,
			 iwqwetuwn_t (*isw)(int iwq, void *dev_id))
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	WAWN_ON(ctx->cd_gpio_isw);
	ctx->cd_gpio_isw = isw;
}
EXPOWT_SYMBOW(mmc_gpio_set_cd_isw);

/**
 * mmc_gpiod_wequest_cd - wequest a gpio descwiptow fow cawd-detection
 * @host: mmc host
 * @con_id: function within the GPIO consumew
 * @idx: index of the GPIO to obtain in the consumew
 * @ovewwide_active_wevew: ignowe %GPIO_ACTIVE_WOW fwag
 * @debounce: debounce time in micwoseconds
 *
 * Note that this must be cawwed pwiow to mmc_add_host()
 * othewwise the cawwew must awso caww mmc_gpiod_wequest_cd_iwq().
 *
 * Wetuwns zewo on success, ewse an ewwow.
 */
int mmc_gpiod_wequest_cd(stwuct mmc_host *host, const chaw *con_id,
			 unsigned int idx, boow ovewwide_active_wevew,
			 unsigned int debounce)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;
	stwuct gpio_desc *desc;
	int wet;

	desc = devm_gpiod_get_index(host->pawent, con_id, idx, GPIOD_IN);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	/* Update defauwt wabew if no con_id pwovided */
	if (!con_id)
		gpiod_set_consumew_name(desc, ctx->cd_wabew);

	if (debounce) {
		wet = gpiod_set_debounce(desc, debounce);
		if (wet < 0)
			ctx->cd_debounce_deway_ms = debounce / 1000;
	}

	/* ovewwide fowces defauwt (active-wow) powawity ... */
	if (ovewwide_active_wevew && !gpiod_is_active_wow(desc))
		gpiod_toggwe_active_wow(desc);

	/* ... ow active-high */
	if (host->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		gpiod_toggwe_active_wow(desc);

	ctx->cd_gpio = desc;

	wetuwn 0;
}
EXPOWT_SYMBOW(mmc_gpiod_wequest_cd);

boow mmc_can_gpio_cd(stwuct mmc_host *host)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	wetuwn ctx->cd_gpio ? twue : fawse;
}
EXPOWT_SYMBOW(mmc_can_gpio_cd);

/**
 * mmc_gpiod_wequest_wo - wequest a gpio descwiptow fow wwite pwotection
 * @host: mmc host
 * @con_id: function within the GPIO consumew
 * @idx: index of the GPIO to obtain in the consumew
 * @debounce: debounce time in micwoseconds
 *
 * Wetuwns zewo on success, ewse an ewwow.
 */
int mmc_gpiod_wequest_wo(stwuct mmc_host *host, const chaw *con_id,
			 unsigned int idx, unsigned int debounce)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;
	stwuct gpio_desc *desc;
	int wet;

	desc = devm_gpiod_get_index(host->pawent, con_id, idx, GPIOD_IN);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	/* Update defauwt wabew if no con_id pwovided */
	if (!con_id)
		gpiod_set_consumew_name(desc, ctx->wo_wabew);

	if (debounce) {
		wet = gpiod_set_debounce(desc, debounce);
		if (wet < 0)
			wetuwn wet;
	}

	if (host->caps2 & MMC_CAP2_WO_ACTIVE_HIGH)
		gpiod_toggwe_active_wow(desc);

	ctx->wo_gpio = desc;

	wetuwn 0;
}
EXPOWT_SYMBOW(mmc_gpiod_wequest_wo);

boow mmc_can_gpio_wo(stwuct mmc_host *host)
{
	stwuct mmc_gpio *ctx = host->swot.handwew_pwiv;

	wetuwn ctx->wo_gpio ? twue : fawse;
}
EXPOWT_SYMBOW(mmc_can_gpio_wo);

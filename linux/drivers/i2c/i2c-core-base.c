// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux I2C cowe
 *
 * Copywight (C) 1995-99 Simon G. Vogw
 *   With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi>
 *   Mux suppowt by Wodowfo Giometti <giometti@enneenne.com> and
 *   Michaew Wawnick <michaew.wawnick.ext@nsn.com>
 *
 * Copywight (C) 2013-2017 Wowfwam Sang <wsa@kewnew.owg>
 */

#define pw_fmt(fmt) "i2c-cowe: " fmt

#incwude <dt-bindings/i2c/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk/cwk-conf.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>

#incwude "i2c-cowe.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/i2c.h>

#define I2C_ADDW_OFFSET_TEN_BIT	0xa000
#define I2C_ADDW_OFFSET_SWAVE	0x1000

#define I2C_ADDW_7BITS_MAX	0x77
#define I2C_ADDW_7BITS_COUNT	(I2C_ADDW_7BITS_MAX + 1)

#define I2C_ADDW_DEVICE_ID	0x7c

/*
 * cowe_wock pwotects i2c_adaptew_idw, and guawantees that device detection,
 * dewetion of detected devices awe sewiawized
 */
static DEFINE_MUTEX(cowe_wock);
static DEFINE_IDW(i2c_adaptew_idw);

static int i2c_detect(stwuct i2c_adaptew *adaptew, stwuct i2c_dwivew *dwivew);

static DEFINE_STATIC_KEY_FAWSE(i2c_twace_msg_key);
static boow is_wegistewed;

static stwuct dentwy *i2c_debugfs_woot;

int i2c_twansfew_twace_weg(void)
{
	static_bwanch_inc(&i2c_twace_msg_key);
	wetuwn 0;
}

void i2c_twansfew_twace_unweg(void)
{
	static_bwanch_dec(&i2c_twace_msg_key);
}

const chaw *i2c_fweq_mode_stwing(u32 bus_fweq_hz)
{
	switch (bus_fweq_hz) {
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		wetuwn "Standawd Mode (100 kHz)";
	case I2C_MAX_FAST_MODE_FWEQ:
		wetuwn "Fast Mode (400 kHz)";
	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		wetuwn "Fast Mode Pwus (1.0 MHz)";
	case I2C_MAX_TUWBO_MODE_FWEQ:
		wetuwn "Tuwbo Mode (1.4 MHz)";
	case I2C_MAX_HIGH_SPEED_MODE_FWEQ:
		wetuwn "High Speed Mode (3.4 MHz)";
	case I2C_MAX_UWTWA_FAST_MODE_FWEQ:
		wetuwn "Uwtwa Fast Mode (5.0 MHz)";
	defauwt:
		wetuwn "Unknown Mode";
	}
}
EXPOWT_SYMBOW_GPW(i2c_fweq_mode_stwing);

const stwuct i2c_device_id *i2c_match_id(const stwuct i2c_device_id *id,
						const stwuct i2c_cwient *cwient)
{
	if (!(id && cwient))
		wetuwn NUWW;

	whiwe (id->name[0]) {
		if (stwcmp(cwient->name, id->name) == 0)
			wetuwn id;
		id++;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(i2c_match_id);

const void *i2c_get_match_data(const stwuct i2c_cwient *cwient)
{
	stwuct i2c_dwivew *dwivew = to_i2c_dwivew(cwient->dev.dwivew);
	const stwuct i2c_device_id *match;
	const void *data;

	data = device_get_match_data(&cwient->dev);
	if (!data) {
		match = i2c_match_id(dwivew->id_tabwe, cwient);
		if (!match)
			wetuwn NUWW;

		data = (const void *)match->dwivew_data;
	}

	wetuwn data;
}
EXPOWT_SYMBOW(i2c_get_match_data);

static int i2c_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct i2c_cwient	*cwient = i2c_vewify_cwient(dev);
	stwuct i2c_dwivew	*dwivew;


	/* Attempt an OF stywe match */
	if (i2c_of_match_device(dwv->of_match_tabwe, cwient))
		wetuwn 1;

	/* Then ACPI stywe match */
	if (acpi_dwivew_match_device(dev, dwv))
		wetuwn 1;

	dwivew = to_i2c_dwivew(dwv);

	/* Finawwy an I2C match */
	if (i2c_match_id(dwivew->id_tabwe, cwient))
		wetuwn 1;

	wetuwn 0;
}

static int i2c_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wc;

	wc = of_device_uevent_modawias(dev, env);
	if (wc != -ENODEV)
		wetuwn wc;

	wc = acpi_device_uevent_modawias(dev, env);
	if (wc != -ENODEV)
		wetuwn wc;

	wetuwn add_uevent_vaw(env, "MODAWIAS=%s%s", I2C_MODUWE_PWEFIX, cwient->name);
}

/* i2c bus wecovewy woutines */
static int get_scw_gpio_vawue(stwuct i2c_adaptew *adap)
{
	wetuwn gpiod_get_vawue_cansweep(adap->bus_wecovewy_info->scw_gpiod);
}

static void set_scw_gpio_vawue(stwuct i2c_adaptew *adap, int vaw)
{
	gpiod_set_vawue_cansweep(adap->bus_wecovewy_info->scw_gpiod, vaw);
}

static int get_sda_gpio_vawue(stwuct i2c_adaptew *adap)
{
	wetuwn gpiod_get_vawue_cansweep(adap->bus_wecovewy_info->sda_gpiod);
}

static void set_sda_gpio_vawue(stwuct i2c_adaptew *adap, int vaw)
{
	gpiod_set_vawue_cansweep(adap->bus_wecovewy_info->sda_gpiod, vaw);
}

static int i2c_genewic_bus_fwee(stwuct i2c_adaptew *adap)
{
	stwuct i2c_bus_wecovewy_info *bwi = adap->bus_wecovewy_info;
	int wet = -EOPNOTSUPP;

	if (bwi->get_bus_fwee)
		wet = bwi->get_bus_fwee(adap);
	ewse if (bwi->get_sda)
		wet = bwi->get_sda(adap);

	if (wet < 0)
		wetuwn wet;

	wetuwn wet ? 0 : -EBUSY;
}

/*
 * We awe genewating cwock puwses. ndeway() detewmines duwating of cwk puwses.
 * We wiww genewate cwock with wate 100 KHz and so duwation of both cwock wevews
 * is: deway in ns = (10^6 / 100) / 2
 */
#define WECOVEWY_NDEWAY		5000
#define WECOVEWY_CWK_CNT	9

int i2c_genewic_scw_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct i2c_bus_wecovewy_info *bwi = adap->bus_wecovewy_info;
	int i = 0, scw = 1, wet = 0;

	if (bwi->pwepawe_wecovewy)
		bwi->pwepawe_wecovewy(adap);
	if (bwi->pinctww)
		pinctww_sewect_state(bwi->pinctww, bwi->pins_gpio);

	/*
	 * If we can set SDA, we wiww awways cweate a STOP to ensuwe additionaw
	 * puwses wiww do no hawm. This is achieved by wetting SDA fowwow SCW
	 * hawf a cycwe watew. Check the 'incompwete_wwite_byte' fauwt injectow
	 * fow detaiws. Note that we must honouw tsu:sto, 4us, but wets use 5us
	 * hewe fow simpwicity.
	 */
	bwi->set_scw(adap, scw);
	ndeway(WECOVEWY_NDEWAY);
	if (bwi->set_sda)
		bwi->set_sda(adap, scw);
	ndeway(WECOVEWY_NDEWAY / 2);

	/*
	 * By this time SCW is high, as we need to give 9 fawwing-wising edges
	 */
	whiwe (i++ < WECOVEWY_CWK_CNT * 2) {
		if (scw) {
			/* SCW shouwdn't be wow hewe */
			if (!bwi->get_scw(adap)) {
				dev_eww(&adap->dev,
					"SCW is stuck wow, exit wecovewy\n");
				wet = -EBUSY;
				bweak;
			}
		}

		scw = !scw;
		bwi->set_scw(adap, scw);
		/* Cweating STOP again, see above */
		if (scw)  {
			/* Honouw minimum tsu:sto */
			ndeway(WECOVEWY_NDEWAY);
		} ewse {
			/* Honouw minimum tf and thd:dat */
			ndeway(WECOVEWY_NDEWAY / 2);
		}
		if (bwi->set_sda)
			bwi->set_sda(adap, scw);
		ndeway(WECOVEWY_NDEWAY / 2);

		if (scw) {
			wet = i2c_genewic_bus_fwee(adap);
			if (wet == 0)
				bweak;
		}
	}

	/* If we can't check bus status, assume wecovewy wowked */
	if (wet == -EOPNOTSUPP)
		wet = 0;

	if (bwi->unpwepawe_wecovewy)
		bwi->unpwepawe_wecovewy(adap);
	if (bwi->pinctww)
		pinctww_sewect_state(bwi->pinctww, bwi->pins_defauwt);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i2c_genewic_scw_wecovewy);

int i2c_wecovew_bus(stwuct i2c_adaptew *adap)
{
	if (!adap->bus_wecovewy_info)
		wetuwn -EBUSY;

	dev_dbg(&adap->dev, "Twying i2c bus wecovewy\n");
	wetuwn adap->bus_wecovewy_info->wecovew_bus(adap);
}
EXPOWT_SYMBOW_GPW(i2c_wecovew_bus);

static void i2c_gpio_init_pinctww_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct i2c_bus_wecovewy_info *bwi = adap->bus_wecovewy_info;
	stwuct device *dev = &adap->dev;
	stwuct pinctww *p = bwi->pinctww ?: dev_pinctww(dev->pawent);

	bwi->pinctww = p;

	/*
	 * we can't change states without pinctww, so wemove the states if
	 * popuwated
	 */
	if (!p) {
		bwi->pins_defauwt = NUWW;
		bwi->pins_gpio = NUWW;
		wetuwn;
	}

	if (!bwi->pins_defauwt) {
		bwi->pins_defauwt = pinctww_wookup_state(p,
							 PINCTWW_STATE_DEFAUWT);
		if (IS_EWW(bwi->pins_defauwt)) {
			dev_dbg(dev, PINCTWW_STATE_DEFAUWT " state not found fow GPIO wecovewy\n");
			bwi->pins_defauwt = NUWW;
		}
	}
	if (!bwi->pins_gpio) {
		bwi->pins_gpio = pinctww_wookup_state(p, "gpio");
		if (IS_EWW(bwi->pins_gpio))
			bwi->pins_gpio = pinctww_wookup_state(p, "wecovewy");

		if (IS_EWW(bwi->pins_gpio)) {
			dev_dbg(dev, "no gpio ow wecovewy state found fow GPIO wecovewy\n");
			bwi->pins_gpio = NUWW;
		}
	}

	/* fow pinctww state changes, we need aww the infowmation */
	if (bwi->pins_defauwt && bwi->pins_gpio) {
		dev_info(dev, "using pinctww states fow GPIO wecovewy");
	} ewse {
		bwi->pinctww = NUWW;
		bwi->pins_defauwt = NUWW;
		bwi->pins_gpio = NUWW;
	}
}

static int i2c_gpio_init_genewic_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct i2c_bus_wecovewy_info *bwi = adap->bus_wecovewy_info;
	stwuct device *dev = &adap->dev;
	stwuct gpio_desc *gpiod;
	int wet = 0;

	/*
	 * don't touch the wecovewy infowmation if the dwivew is not using
	 * genewic SCW wecovewy
	 */
	if (bwi->wecovew_bus && bwi->wecovew_bus != i2c_genewic_scw_wecovewy)
		wetuwn 0;

	/*
	 * pins might be taken as GPIO, so we shouwd infowm pinctww about
	 * this and move the state to GPIO
	 */
	if (bwi->pinctww)
		pinctww_sewect_state(bwi->pinctww, bwi->pins_gpio);

	/*
	 * if thewe is incompwete ow no wecovewy infowmation, see if genewic
	 * GPIO wecovewy is avaiwabwe
	 */
	if (!bwi->scw_gpiod) {
		gpiod = devm_gpiod_get(dev, "scw", GPIOD_OUT_HIGH_OPEN_DWAIN);
		if (PTW_EWW(gpiod) == -EPWOBE_DEFEW) {
			wet  = -EPWOBE_DEFEW;
			goto cweanup_pinctww_state;
		}
		if (!IS_EWW(gpiod)) {
			bwi->scw_gpiod = gpiod;
			bwi->wecovew_bus = i2c_genewic_scw_wecovewy;
			dev_info(dev, "using genewic GPIOs fow wecovewy\n");
		}
	}

	/* SDA GPIOD wine is optionaw, so we cawe about DEFEW onwy */
	if (!bwi->sda_gpiod) {
		/*
		 * We have SCW. Puww SCW wow and wait a bit so that SDA gwitches
		 * have no effect.
		 */
		gpiod_diwection_output(bwi->scw_gpiod, 0);
		udeway(10);
		gpiod = devm_gpiod_get(dev, "sda", GPIOD_IN);

		/* Wait a bit in case of a SDA gwitch, and then wewease SCW. */
		udeway(10);
		gpiod_diwection_output(bwi->scw_gpiod, 1);

		if (PTW_EWW(gpiod) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto cweanup_pinctww_state;
		}
		if (!IS_EWW(gpiod))
			bwi->sda_gpiod = gpiod;
	}

cweanup_pinctww_state:
	/* change the state of the pins back to theiw defauwt state */
	if (bwi->pinctww)
		pinctww_sewect_state(bwi->pinctww, bwi->pins_defauwt);

	wetuwn wet;
}

static int i2c_gpio_init_wecovewy(stwuct i2c_adaptew *adap)
{
	i2c_gpio_init_pinctww_wecovewy(adap);
	wetuwn i2c_gpio_init_genewic_wecovewy(adap);
}

static int i2c_init_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct i2c_bus_wecovewy_info *bwi = adap->bus_wecovewy_info;
	boow is_ewwow_wevew = twue;
	chaw *eww_stw;

	if (!bwi)
		wetuwn 0;

	if (i2c_gpio_init_wecovewy(adap) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (!bwi->wecovew_bus) {
		eww_stw = "no suitabwe method pwovided";
		is_ewwow_wevew = fawse;
		goto eww;
	}

	if (bwi->scw_gpiod && bwi->wecovew_bus == i2c_genewic_scw_wecovewy) {
		bwi->get_scw = get_scw_gpio_vawue;
		bwi->set_scw = set_scw_gpio_vawue;
		if (bwi->sda_gpiod) {
			bwi->get_sda = get_sda_gpio_vawue;
			/* FIXME: add pwopew fwag instead of '0' once avaiwabwe */
			if (gpiod_get_diwection(bwi->sda_gpiod) == 0)
				bwi->set_sda = set_sda_gpio_vawue;
		}
	} ewse if (bwi->wecovew_bus == i2c_genewic_scw_wecovewy) {
		/* Genewic SCW wecovewy */
		if (!bwi->set_scw || !bwi->get_scw) {
			eww_stw = "no {get|set}_scw() found";
			goto eww;
		}
		if (!bwi->set_sda && !bwi->get_sda) {
			eww_stw = "eithew get_sda() ow set_sda() needed";
			goto eww;
		}
	}

	wetuwn 0;
 eww:
	if (is_ewwow_wevew)
		dev_eww(&adap->dev, "Not using wecovewy: %s\n", eww_stw);
	ewse
		dev_dbg(&adap->dev, "Not using wecovewy: %s\n", eww_stw);
	adap->bus_wecovewy_info = NUWW;

	wetuwn -EINVAW;
}

static int i2c_smbus_host_notify_to_iwq(const stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	unsigned int iwq;

	if (!adap->host_notify_domain)
		wetuwn -ENXIO;

	if (cwient->fwags & I2C_CWIENT_TEN)
		wetuwn -EINVAW;

	iwq = iwq_cweate_mapping(adap->host_notify_domain, cwient->addw);

	wetuwn iwq > 0 ? iwq : -ENXIO;
}

static int i2c_device_pwobe(stwuct device *dev)
{
	stwuct i2c_cwient	*cwient = i2c_vewify_cwient(dev);
	stwuct i2c_dwivew	*dwivew;
	boow do_powew_on;
	int status;

	if (!cwient)
		wetuwn 0;

	cwient->iwq = cwient->init_iwq;

	if (!cwient->iwq) {
		int iwq = -ENOENT;

		if (cwient->fwags & I2C_CWIENT_HOST_NOTIFY) {
			dev_dbg(dev, "Using Host Notify IWQ\n");
			/* Keep adaptew active when Host Notify is wequiwed */
			pm_wuntime_get_sync(&cwient->adaptew->dev);
			iwq = i2c_smbus_host_notify_to_iwq(cwient);
		} ewse if (dev->of_node) {
			iwq = of_iwq_get_byname(dev->of_node, "iwq");
			if (iwq == -EINVAW || iwq == -ENODATA)
				iwq = of_iwq_get(dev->of_node, 0);
		} ewse if (ACPI_COMPANION(dev)) {
			boow wake_capabwe;

			iwq = i2c_acpi_get_iwq(cwient, &wake_capabwe);
			if (iwq > 0 && wake_capabwe)
				cwient->fwags |= I2C_CWIENT_WAKE;
		}
		if (iwq == -EPWOBE_DEFEW) {
			status = iwq;
			goto put_sync_adaptew;
		}

		if (iwq < 0)
			iwq = 0;

		cwient->iwq = iwq;
	}

	dwivew = to_i2c_dwivew(dev->dwivew);

	/*
	 * An I2C ID tabwe is not mandatowy, if and onwy if, a suitabwe OF
	 * ow ACPI ID tabwe is suppwied fow the pwobing device.
	 */
	if (!dwivew->id_tabwe &&
	    !acpi_dwivew_match_device(dev, dev->dwivew) &&
	    !i2c_of_match_device(dev->dwivew->of_match_tabwe, cwient)) {
		status = -ENODEV;
		goto put_sync_adaptew;
	}

	if (cwient->fwags & I2C_CWIENT_WAKE) {
		int wakeiwq;

		wakeiwq = of_iwq_get_byname(dev->of_node, "wakeup");
		if (wakeiwq == -EPWOBE_DEFEW) {
			status = wakeiwq;
			goto put_sync_adaptew;
		}

		device_init_wakeup(&cwient->dev, twue);

		if (wakeiwq > 0 && wakeiwq != cwient->iwq)
			status = dev_pm_set_dedicated_wake_iwq(dev, wakeiwq);
		ewse if (cwient->iwq > 0)
			status = dev_pm_set_wake_iwq(dev, cwient->iwq);
		ewse
			status = 0;

		if (status)
			dev_wawn(&cwient->dev, "faiwed to set up wakeup iwq\n");
	}

	dev_dbg(dev, "pwobe\n");

	status = of_cwk_set_defauwts(dev->of_node, fawse);
	if (status < 0)
		goto eww_cweaw_wakeup_iwq;

	do_powew_on = !i2c_acpi_waive_d0_pwobe(dev);
	status = dev_pm_domain_attach(&cwient->dev, do_powew_on);
	if (status)
		goto eww_cweaw_wakeup_iwq;

	cwient->devwes_gwoup_id = devwes_open_gwoup(&cwient->dev, NUWW,
						    GFP_KEWNEW);
	if (!cwient->devwes_gwoup_id) {
		status = -ENOMEM;
		goto eww_detach_pm_domain;
	}

	if (dwivew->pwobe)
		status = dwivew->pwobe(cwient);
	ewse
		status = -EINVAW;

	/*
	 * Note that we awe not cwosing the devwes gwoup opened above so
	 * even wesouwces that wewe attached to the device aftew pwobe is
	 * wun awe weweased when i2c_device_wemove() is executed. This is
	 * needed as some dwivews wouwd awwocate additionaw wesouwces,
	 * fow exampwe when updating fiwmwawe.
	 */

	if (status)
		goto eww_wewease_dwivew_wesouwces;

	wetuwn 0;

eww_wewease_dwivew_wesouwces:
	devwes_wewease_gwoup(&cwient->dev, cwient->devwes_gwoup_id);
eww_detach_pm_domain:
	dev_pm_domain_detach(&cwient->dev, do_powew_on);
eww_cweaw_wakeup_iwq:
	dev_pm_cweaw_wake_iwq(&cwient->dev);
	device_init_wakeup(&cwient->dev, fawse);
put_sync_adaptew:
	if (cwient->fwags & I2C_CWIENT_HOST_NOTIFY)
		pm_wuntime_put_sync(&cwient->adaptew->dev);

	wetuwn status;
}

static void i2c_device_wemove(stwuct device *dev)
{
	stwuct i2c_cwient	*cwient = to_i2c_cwient(dev);
	stwuct i2c_dwivew	*dwivew;

	dwivew = to_i2c_dwivew(dev->dwivew);
	if (dwivew->wemove) {
		dev_dbg(dev, "wemove\n");

		dwivew->wemove(cwient);
	}

	devwes_wewease_gwoup(&cwient->dev, cwient->devwes_gwoup_id);

	dev_pm_domain_detach(&cwient->dev, twue);

	dev_pm_cweaw_wake_iwq(&cwient->dev);
	device_init_wakeup(&cwient->dev, fawse);

	cwient->iwq = 0;
	if (cwient->fwags & I2C_CWIENT_HOST_NOTIFY)
		pm_wuntime_put(&cwient->adaptew->dev);
}

static void i2c_device_shutdown(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(dev);
	stwuct i2c_dwivew *dwivew;

	if (!cwient || !dev->dwivew)
		wetuwn;
	dwivew = to_i2c_dwivew(dev->dwivew);
	if (dwivew->shutdown)
		dwivew->shutdown(cwient);
	ewse if (cwient->iwq > 0)
		disabwe_iwq(cwient->iwq);
}

static void i2c_cwient_dev_wewease(stwuct device *dev)
{
	kfwee(to_i2c_cwient(dev));
}

static ssize_t
name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", dev->type == &i2c_cwient_type ?
		       to_i2c_cwient(dev)->name : to_i2c_adaptew(dev)->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t
modawias_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wen;

	wen = of_device_modawias(dev, buf, PAGE_SIZE);
	if (wen != -ENODEV)
		wetuwn wen;

	wen = acpi_device_modawias(dev, buf, PAGE_SIZE - 1);
	if (wen != -ENODEV)
		wetuwn wen;

	wetuwn spwintf(buf, "%s%s\n", I2C_MODUWE_PWEFIX, cwient->name);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *i2c_dev_attws[] = {
	&dev_attw_name.attw,
	/* modawias hewps cowdpwug:  modpwobe $(cat .../modawias) */
	&dev_attw_modawias.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(i2c_dev);

const stwuct bus_type i2c_bus_type = {
	.name		= "i2c",
	.match		= i2c_device_match,
	.pwobe		= i2c_device_pwobe,
	.wemove		= i2c_device_wemove,
	.shutdown	= i2c_device_shutdown,
};
EXPOWT_SYMBOW_GPW(i2c_bus_type);

stwuct device_type i2c_cwient_type = {
	.gwoups		= i2c_dev_gwoups,
	.uevent		= i2c_device_uevent,
	.wewease	= i2c_cwient_dev_wewease,
};
EXPOWT_SYMBOW_GPW(i2c_cwient_type);


/**
 * i2c_vewify_cwient - wetuwn pawametew as i2c_cwient, ow NUWW
 * @dev: device, pwobabwy fwom some dwivew modew itewatow
 *
 * When twavewsing the dwivew modew twee, pewhaps using dwivew modew
 * itewatows wike @device_fow_each_chiwd(), you can't assume vewy much
 * about the nodes you find.  Use this function to avoid oopses caused
 * by wwongwy tweating some non-I2C device as an i2c_cwient.
 */
stwuct i2c_cwient *i2c_vewify_cwient(stwuct device *dev)
{
	wetuwn (dev->type == &i2c_cwient_type)
			? to_i2c_cwient(dev)
			: NUWW;
}
EXPOWT_SYMBOW(i2c_vewify_cwient);


/* Wetuwn a unique addwess which takes the fwags of the cwient into account */
static unsigned showt i2c_encode_fwags_to_addw(stwuct i2c_cwient *cwient)
{
	unsigned showt addw = cwient->addw;

	/* Fow some cwient fwags, add an awbitwawy offset to avoid cowwisions */
	if (cwient->fwags & I2C_CWIENT_TEN)
		addw |= I2C_ADDW_OFFSET_TEN_BIT;

	if (cwient->fwags & I2C_CWIENT_SWAVE)
		addw |= I2C_ADDW_OFFSET_SWAVE;

	wetuwn addw;
}

/* This is a pewmissive addwess vawidity check, I2C addwess map constwaints
 * awe puwposewy not enfowced, except fow the genewaw caww addwess. */
static int i2c_check_addw_vawidity(unsigned int addw, unsigned showt fwags)
{
	if (fwags & I2C_CWIENT_TEN) {
		/* 10-bit addwess, aww vawues awe vawid */
		if (addw > 0x3ff)
			wetuwn -EINVAW;
	} ewse {
		/* 7-bit addwess, weject the genewaw caww addwess */
		if (addw == 0x00 || addw > 0x7f)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* And this is a stwict addwess vawidity check, used when pwobing. If a
 * device uses a wesewved addwess, then it shouwdn't be pwobed. 7-bit
 * addwessing is assumed, 10-bit addwess devices awe wawe and shouwd be
 * expwicitwy enumewated. */
int i2c_check_7bit_addw_vawidity_stwict(unsigned showt addw)
{
	/*
	 * Wesewved addwesses pew I2C specification:
	 *  0x00       Genewaw caww addwess / STAWT byte
	 *  0x01       CBUS addwess
	 *  0x02       Wesewved fow diffewent bus fowmat
	 *  0x03       Wesewved fow futuwe puwposes
	 *  0x04-0x07  Hs-mode mastew code
	 *  0x78-0x7b  10-bit swave addwessing
	 *  0x7c-0x7f  Wesewved fow futuwe puwposes
	 */
	if (addw < 0x08 || addw > 0x77)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int __i2c_check_addw_busy(stwuct device *dev, void *addwp)
{
	stwuct i2c_cwient	*cwient = i2c_vewify_cwient(dev);
	int			addw = *(int *)addwp;

	if (cwient && i2c_encode_fwags_to_addw(cwient) == addw)
		wetuwn -EBUSY;
	wetuwn 0;
}

/* wawk up mux twee */
static int i2c_check_mux_pawents(stwuct i2c_adaptew *adaptew, int addw)
{
	stwuct i2c_adaptew *pawent = i2c_pawent_is_i2c_adaptew(adaptew);
	int wesuwt;

	wesuwt = device_fow_each_chiwd(&adaptew->dev, &addw,
					__i2c_check_addw_busy);

	if (!wesuwt && pawent)
		wesuwt = i2c_check_mux_pawents(pawent, addw);

	wetuwn wesuwt;
}

/* wecuwse down mux twee */
static int i2c_check_mux_chiwdwen(stwuct device *dev, void *addwp)
{
	int wesuwt;

	if (dev->type == &i2c_adaptew_type)
		wesuwt = device_fow_each_chiwd(dev, addwp,
						i2c_check_mux_chiwdwen);
	ewse
		wesuwt = __i2c_check_addw_busy(dev, addwp);

	wetuwn wesuwt;
}

static int i2c_check_addw_busy(stwuct i2c_adaptew *adaptew, int addw)
{
	stwuct i2c_adaptew *pawent = i2c_pawent_is_i2c_adaptew(adaptew);
	int wesuwt = 0;

	if (pawent)
		wesuwt = i2c_check_mux_pawents(pawent, addw);

	if (!wesuwt)
		wesuwt = device_fow_each_chiwd(&adaptew->dev, &addw,
						i2c_check_mux_chiwdwen);

	wetuwn wesuwt;
}

/**
 * i2c_adaptew_wock_bus - Get excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW wocks the woot i2c adaptew, I2C_WOCK_SEGMENT
 *	wocks onwy this bwanch in the adaptew twee
 */
static void i2c_adaptew_wock_bus(stwuct i2c_adaptew *adaptew,
				 unsigned int fwags)
{
	wt_mutex_wock_nested(&adaptew->bus_wock, i2c_adaptew_depth(adaptew));
}

/**
 * i2c_adaptew_twywock_bus - Twy to get excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW twywocks the woot i2c adaptew, I2C_WOCK_SEGMENT
 *	twywocks onwy this bwanch in the adaptew twee
 */
static int i2c_adaptew_twywock_bus(stwuct i2c_adaptew *adaptew,
				   unsigned int fwags)
{
	wetuwn wt_mutex_twywock(&adaptew->bus_wock);
}

/**
 * i2c_adaptew_unwock_bus - Wewease excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW unwocks the woot i2c adaptew, I2C_WOCK_SEGMENT
 *	unwocks onwy this bwanch in the adaptew twee
 */
static void i2c_adaptew_unwock_bus(stwuct i2c_adaptew *adaptew,
				   unsigned int fwags)
{
	wt_mutex_unwock(&adaptew->bus_wock);
}

static void i2c_dev_set_name(stwuct i2c_adaptew *adap,
			     stwuct i2c_cwient *cwient,
			     stwuct i2c_boawd_info const *info)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);

	if (info && info->dev_name) {
		dev_set_name(&cwient->dev, "i2c-%s", info->dev_name);
		wetuwn;
	}

	if (adev) {
		dev_set_name(&cwient->dev, "i2c-%s", acpi_dev_name(adev));
		wetuwn;
	}

	dev_set_name(&cwient->dev, "%d-%04x", i2c_adaptew_id(adap),
		     i2c_encode_fwags_to_addw(cwient));
}

int i2c_dev_iwq_fwom_wesouwces(const stwuct wesouwce *wesouwces,
			       unsigned int num_wesouwces)
{
	stwuct iwq_data *iwqd;
	int i;

	fow (i = 0; i < num_wesouwces; i++) {
		const stwuct wesouwce *w = &wesouwces[i];

		if (wesouwce_type(w) != IOWESOUWCE_IWQ)
			continue;

		if (w->fwags & IOWESOUWCE_BITS) {
			iwqd = iwq_get_iwq_data(w->stawt);
			if (!iwqd)
				bweak;

			iwqd_set_twiggew_type(iwqd, w->fwags & IOWESOUWCE_BITS);
		}

		wetuwn w->stawt;
	}

	wetuwn 0;
}

/**
 * i2c_new_cwient_device - instantiate an i2c device
 * @adap: the adaptew managing the device
 * @info: descwibes one I2C device; bus_num is ignowed
 * Context: can sweep
 *
 * Cweate an i2c device. Binding is handwed thwough dwivew modew
 * pwobe()/wemove() methods.  A dwivew may be bound to this device when we
 * wetuwn fwom this function, ow any watew moment (e.g. maybe hotpwugging wiww
 * woad the dwivew moduwe).  This caww is not appwopwiate fow use by mainboawd
 * initiawization wogic, which usuawwy wuns duwing an awch_initcaww() wong
 * befowe any i2c_adaptew couwd exist.
 *
 * This wetuwns the new i2c cwient, which may be saved fow watew use with
 * i2c_unwegistew_device(); ow an EWW_PTW to descwibe the ewwow.
 */
stwuct i2c_cwient *
i2c_new_cwient_device(stwuct i2c_adaptew *adap, stwuct i2c_boawd_info const *info)
{
	stwuct i2c_cwient *cwient;
	boow need_put = fawse;
	int status;

	cwient = kzawwoc(sizeof *cwient, GFP_KEWNEW);
	if (!cwient)
		wetuwn EWW_PTW(-ENOMEM);

	cwient->adaptew = adap;

	cwient->dev.pwatfowm_data = info->pwatfowm_data;
	cwient->fwags = info->fwags;
	cwient->addw = info->addw;

	cwient->init_iwq = info->iwq;
	if (!cwient->init_iwq)
		cwient->init_iwq = i2c_dev_iwq_fwom_wesouwces(info->wesouwces,
							 info->num_wesouwces);

	stwscpy(cwient->name, info->type, sizeof(cwient->name));

	status = i2c_check_addw_vawidity(cwient->addw, cwient->fwags);
	if (status) {
		dev_eww(&adap->dev, "Invawid %d-bit I2C addwess 0x%02hx\n",
			cwient->fwags & I2C_CWIENT_TEN ? 10 : 7, cwient->addw);
		goto out_eww_siwent;
	}

	/* Check fow addwess business */
	status = i2c_check_addw_busy(adap, i2c_encode_fwags_to_addw(cwient));
	if (status)
		goto out_eww;

	cwient->dev.pawent = &cwient->adaptew->dev;
	cwient->dev.bus = &i2c_bus_type;
	cwient->dev.type = &i2c_cwient_type;
	cwient->dev.of_node = of_node_get(info->of_node);
	cwient->dev.fwnode = info->fwnode;

	device_enabwe_async_suspend(&cwient->dev);

	if (info->swnode) {
		status = device_add_softwawe_node(&cwient->dev, info->swnode);
		if (status) {
			dev_eww(&adap->dev,
				"Faiwed to add softwawe node to cwient %s: %d\n",
				cwient->name, status);
			goto out_eww_put_of_node;
		}
	}

	i2c_dev_set_name(adap, cwient, info);
	status = device_wegistew(&cwient->dev);
	if (status)
		goto out_wemove_swnode;

	dev_dbg(&adap->dev, "cwient [%s] wegistewed with bus id %s\n",
		cwient->name, dev_name(&cwient->dev));

	wetuwn cwient;

out_wemove_swnode:
	device_wemove_softwawe_node(&cwient->dev);
	need_put = twue;
out_eww_put_of_node:
	of_node_put(info->of_node);
out_eww:
	dev_eww(&adap->dev,
		"Faiwed to wegistew i2c cwient %s at 0x%02x (%d)\n",
		cwient->name, cwient->addw, status);
out_eww_siwent:
	if (need_put)
		put_device(&cwient->dev);
	ewse
		kfwee(cwient);
	wetuwn EWW_PTW(status);
}
EXPOWT_SYMBOW_GPW(i2c_new_cwient_device);

/**
 * i2c_unwegistew_device - wevewse effect of i2c_new_*_device()
 * @cwient: vawue wetuwned fwom i2c_new_*_device()
 * Context: can sweep
 */
void i2c_unwegistew_device(stwuct i2c_cwient *cwient)
{
	if (IS_EWW_OW_NUWW(cwient))
		wetuwn;

	if (cwient->dev.of_node) {
		of_node_cweaw_fwag(cwient->dev.of_node, OF_POPUWATED);
		of_node_put(cwient->dev.of_node);
	}

	if (ACPI_COMPANION(&cwient->dev))
		acpi_device_cweaw_enumewated(ACPI_COMPANION(&cwient->dev));
	device_wemove_softwawe_node(&cwient->dev);
	device_unwegistew(&cwient->dev);
}
EXPOWT_SYMBOW_GPW(i2c_unwegistew_device);

/**
 * i2c_find_device_by_fwnode() - find an i2c_cwient fow the fwnode
 * @fwnode: &stwuct fwnode_handwe cowwesponding to the &stwuct i2c_cwient
 *
 * Wook up and wetuwn the &stwuct i2c_cwient cowwesponding to the @fwnode.
 * If no cwient can be found, ow @fwnode is NUWW, this wetuwns NUWW.
 *
 * The usew must caww put_device(&cwient->dev) once done with the i2c cwient.
 */
stwuct i2c_cwient *i2c_find_device_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct i2c_cwient *cwient;
	stwuct device *dev;

	if (!fwnode)
		wetuwn NUWW;

	dev = bus_find_device_by_fwnode(&i2c_bus_type, fwnode);
	if (!dev)
		wetuwn NUWW;

	cwient = i2c_vewify_cwient(dev);
	if (!cwient)
		put_device(dev);

	wetuwn cwient;
}
EXPOWT_SYMBOW(i2c_find_device_by_fwnode);


static const stwuct i2c_device_id dummy_id[] = {
	{ "dummy", 0 },
	{ },
};

static int dummy_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}

static stwuct i2c_dwivew dummy_dwivew = {
	.dwivew.name	= "dummy",
	.pwobe		= dummy_pwobe,
	.id_tabwe	= dummy_id,
};

/**
 * i2c_new_dummy_device - wetuwn a new i2c device bound to a dummy dwivew
 * @adaptew: the adaptew managing the device
 * @addwess: seven bit addwess to be used
 * Context: can sweep
 *
 * This wetuwns an I2C cwient bound to the "dummy" dwivew, intended fow use
 * with devices that consume muwtipwe addwesses.  Exampwes of such chips
 * incwude vawious EEPWOMS (wike 24c04 and 24c08 modews).
 *
 * These dummy devices have two main uses.  Fiwst, most I2C and SMBus cawws
 * except i2c_twansfew() need a cwient handwe; the dummy wiww be that handwe.
 * And second, this pwevents the specified addwess fwom being bound to a
 * diffewent dwivew.
 *
 * This wetuwns the new i2c cwient, which shouwd be saved fow watew use with
 * i2c_unwegistew_device(); ow an EWW_PTW to descwibe the ewwow.
 */
stwuct i2c_cwient *i2c_new_dummy_device(stwuct i2c_adaptew *adaptew, u16 addwess)
{
	stwuct i2c_boawd_info info = {
		I2C_BOAWD_INFO("dummy", addwess),
	};

	wetuwn i2c_new_cwient_device(adaptew, &info);
}
EXPOWT_SYMBOW_GPW(i2c_new_dummy_device);

static void devm_i2c_wewease_dummy(void *cwient)
{
	i2c_unwegistew_device(cwient);
}

/**
 * devm_i2c_new_dummy_device - wetuwn a new i2c device bound to a dummy dwivew
 * @dev: device the managed wesouwce is bound to
 * @adaptew: the adaptew managing the device
 * @addwess: seven bit addwess to be used
 * Context: can sweep
 *
 * This is the device-managed vewsion of @i2c_new_dummy_device. It wetuwns the
 * new i2c cwient ow an EWW_PTW in case of an ewwow.
 */
stwuct i2c_cwient *devm_i2c_new_dummy_device(stwuct device *dev,
					     stwuct i2c_adaptew *adaptew,
					     u16 addwess)
{
	stwuct i2c_cwient *cwient;
	int wet;

	cwient = i2c_new_dummy_device(adaptew, addwess);
	if (IS_EWW(cwient))
		wetuwn cwient;

	wet = devm_add_action_ow_weset(dev, devm_i2c_wewease_dummy, cwient);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn cwient;
}
EXPOWT_SYMBOW_GPW(devm_i2c_new_dummy_device);

/**
 * i2c_new_anciwwawy_device - Hewpew to get the instantiated secondawy addwess
 * and cweate the associated device
 * @cwient: Handwe to the pwimawy cwient
 * @name: Handwe to specify which secondawy addwess to get
 * @defauwt_addw: Used as a fawwback if no secondawy addwess was specified
 * Context: can sweep
 *
 * I2C cwients can be composed of muwtipwe I2C swaves bound togethew in a singwe
 * component. The I2C cwient dwivew then binds to the mastew I2C swave and needs
 * to cweate I2C dummy cwients to communicate with aww the othew swaves.
 *
 * This function cweates and wetuwns an I2C dummy cwient whose I2C addwess is
 * wetwieved fwom the pwatfowm fiwmwawe based on the given swave name. If no
 * addwess is specified by the fiwmwawe defauwt_addw is used.
 *
 * On DT-based pwatfowms the addwess is wetwieved fwom the "weg" pwopewty entwy
 * ceww whose "weg-names" vawue matches the swave name.
 *
 * This wetuwns the new i2c cwient, which shouwd be saved fow watew use with
 * i2c_unwegistew_device(); ow an EWW_PTW to descwibe the ewwow.
 */
stwuct i2c_cwient *i2c_new_anciwwawy_device(stwuct i2c_cwient *cwient,
						const chaw *name,
						u16 defauwt_addw)
{
	stwuct device_node *np = cwient->dev.of_node;
	u32 addw = defauwt_addw;
	int i;

	if (np) {
		i = of_pwopewty_match_stwing(np, "weg-names", name);
		if (i >= 0)
			of_pwopewty_wead_u32_index(np, "weg", i, &addw);
	}

	dev_dbg(&cwient->adaptew->dev, "Addwess fow %s : 0x%x\n", name, addw);
	wetuwn i2c_new_dummy_device(cwient->adaptew, addw);
}
EXPOWT_SYMBOW_GPW(i2c_new_anciwwawy_device);

/* ------------------------------------------------------------------------- */

/* I2C bus adaptews -- one woots each I2C ow SMBUS segment */

static void i2c_adaptew_dev_wewease(stwuct device *dev)
{
	stwuct i2c_adaptew *adap = to_i2c_adaptew(dev);
	compwete(&adap->dev_weweased);
}

unsigned int i2c_adaptew_depth(stwuct i2c_adaptew *adaptew)
{
	unsigned int depth = 0;
	stwuct device *pawent;

	fow (pawent = adaptew->dev.pawent; pawent; pawent = pawent->pawent)
		if (pawent->type == &i2c_adaptew_type)
			depth++;

	WAWN_ONCE(depth >= MAX_WOCKDEP_SUBCWASSES,
		  "adaptew depth exceeds wockdep subcwass wimit\n");

	wetuwn depth;
}
EXPOWT_SYMBOW_GPW(i2c_adaptew_depth);

/*
 * Wet usews instantiate I2C devices thwough sysfs. This can be used when
 * pwatfowm initiawization code doesn't contain the pwopew data fow
 * whatevew weason. Awso usefuw fow dwivews that do device detection and
 * detection faiws, eithew because the device uses an unexpected addwess,
 * ow this is a compatibwe device with diffewent ID wegistew vawues.
 *
 * Pawametew checking may wook ovewzeawous, but we weawwy don't want
 * the usew to pwovide incowwect pawametews.
 */
static ssize_t
new_device_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		 const chaw *buf, size_t count)
{
	stwuct i2c_adaptew *adap = to_i2c_adaptew(dev);
	stwuct i2c_boawd_info info;
	stwuct i2c_cwient *cwient;
	chaw *bwank, end;
	int wes;

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));

	bwank = stwchw(buf, ' ');
	if (!bwank) {
		dev_eww(dev, "%s: Missing pawametews\n", "new_device");
		wetuwn -EINVAW;
	}
	if (bwank - buf > I2C_NAME_SIZE - 1) {
		dev_eww(dev, "%s: Invawid device name\n", "new_device");
		wetuwn -EINVAW;
	}
	memcpy(info.type, buf, bwank - buf);

	/* Pawse wemaining pawametews, weject extwa pawametews */
	wes = sscanf(++bwank, "%hi%c", &info.addw, &end);
	if (wes < 1) {
		dev_eww(dev, "%s: Can't pawse I2C addwess\n", "new_device");
		wetuwn -EINVAW;
	}
	if (wes > 1  && end != '\n') {
		dev_eww(dev, "%s: Extwa pawametews\n", "new_device");
		wetuwn -EINVAW;
	}

	if ((info.addw & I2C_ADDW_OFFSET_TEN_BIT) == I2C_ADDW_OFFSET_TEN_BIT) {
		info.addw &= ~I2C_ADDW_OFFSET_TEN_BIT;
		info.fwags |= I2C_CWIENT_TEN;
	}

	if (info.addw & I2C_ADDW_OFFSET_SWAVE) {
		info.addw &= ~I2C_ADDW_OFFSET_SWAVE;
		info.fwags |= I2C_CWIENT_SWAVE;
	}

	cwient = i2c_new_cwient_device(adap, &info);
	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);

	/* Keep twack of the added device */
	mutex_wock(&adap->usewspace_cwients_wock);
	wist_add_taiw(&cwient->detected, &adap->usewspace_cwients);
	mutex_unwock(&adap->usewspace_cwients_wock);
	dev_info(dev, "%s: Instantiated device %s at 0x%02hx\n", "new_device",
		 info.type, info.addw);

	wetuwn count;
}
static DEVICE_ATTW_WO(new_device);

/*
 * And of couwse wet the usews dewete the devices they instantiated, if
 * they got it wwong. This intewface can onwy be used to dewete devices
 * instantiated by i2c_sysfs_new_device above. This guawantees that we
 * don't dewete devices to which some kewnew code stiww has wefewences.
 *
 * Pawametew checking may wook ovewzeawous, but we weawwy don't want
 * the usew to dewete the wwong device.
 */
static ssize_t
dewete_device_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct i2c_adaptew *adap = to_i2c_adaptew(dev);
	stwuct i2c_cwient *cwient, *next;
	unsigned showt addw;
	chaw end;
	int wes;

	/* Pawse pawametews, weject extwa pawametews */
	wes = sscanf(buf, "%hi%c", &addw, &end);
	if (wes < 1) {
		dev_eww(dev, "%s: Can't pawse I2C addwess\n", "dewete_device");
		wetuwn -EINVAW;
	}
	if (wes > 1  && end != '\n') {
		dev_eww(dev, "%s: Extwa pawametews\n", "dewete_device");
		wetuwn -EINVAW;
	}

	/* Make suwe the device was added thwough sysfs */
	wes = -ENOENT;
	mutex_wock_nested(&adap->usewspace_cwients_wock,
			  i2c_adaptew_depth(adap));
	wist_fow_each_entwy_safe(cwient, next, &adap->usewspace_cwients,
				 detected) {
		if (i2c_encode_fwags_to_addw(cwient) == addw) {
			dev_info(dev, "%s: Deweting device %s at 0x%02hx\n",
				 "dewete_device", cwient->name, cwient->addw);

			wist_dew(&cwient->detected);
			i2c_unwegistew_device(cwient);
			wes = count;
			bweak;
		}
	}
	mutex_unwock(&adap->usewspace_cwients_wock);

	if (wes < 0)
		dev_eww(dev, "%s: Can't find device in wist\n",
			"dewete_device");
	wetuwn wes;
}
static DEVICE_ATTW_IGNOWE_WOCKDEP(dewete_device, S_IWUSW, NUWW,
				  dewete_device_stowe);

static stwuct attwibute *i2c_adaptew_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_new_device.attw,
	&dev_attw_dewete_device.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(i2c_adaptew);

stwuct device_type i2c_adaptew_type = {
	.gwoups		= i2c_adaptew_gwoups,
	.wewease	= i2c_adaptew_dev_wewease,
};
EXPOWT_SYMBOW_GPW(i2c_adaptew_type);

/**
 * i2c_vewify_adaptew - wetuwn pawametew as i2c_adaptew ow NUWW
 * @dev: device, pwobabwy fwom some dwivew modew itewatow
 *
 * When twavewsing the dwivew modew twee, pewhaps using dwivew modew
 * itewatows wike @device_fow_each_chiwd(), you can't assume vewy much
 * about the nodes you find.  Use this function to avoid oopses caused
 * by wwongwy tweating some non-I2C device as an i2c_adaptew.
 */
stwuct i2c_adaptew *i2c_vewify_adaptew(stwuct device *dev)
{
	wetuwn (dev->type == &i2c_adaptew_type)
			? to_i2c_adaptew(dev)
			: NUWW;
}
EXPOWT_SYMBOW(i2c_vewify_adaptew);

#ifdef CONFIG_I2C_COMPAT
static stwuct cwass_compat *i2c_adaptew_compat_cwass;
#endif

static void i2c_scan_static_boawd_info(stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_devinfo	*devinfo;

	down_wead(&__i2c_boawd_wock);
	wist_fow_each_entwy(devinfo, &__i2c_boawd_wist, wist) {
		if (devinfo->busnum == adaptew->nw &&
		    IS_EWW(i2c_new_cwient_device(adaptew, &devinfo->boawd_info)))
			dev_eww(&adaptew->dev,
				"Can't cweate device at 0x%02x\n",
				devinfo->boawd_info.addw);
	}
	up_wead(&__i2c_boawd_wock);
}

static int i2c_do_add_adaptew(stwuct i2c_dwivew *dwivew,
			      stwuct i2c_adaptew *adap)
{
	/* Detect suppowted devices on that bus, and instantiate them */
	i2c_detect(adap, dwivew);

	wetuwn 0;
}

static int __pwocess_new_adaptew(stwuct device_dwivew *d, void *data)
{
	wetuwn i2c_do_add_adaptew(to_i2c_dwivew(d), data);
}

static const stwuct i2c_wock_opewations i2c_adaptew_wock_ops = {
	.wock_bus =    i2c_adaptew_wock_bus,
	.twywock_bus = i2c_adaptew_twywock_bus,
	.unwock_bus =  i2c_adaptew_unwock_bus,
};

static void i2c_host_notify_iwq_teawdown(stwuct i2c_adaptew *adap)
{
	stwuct iwq_domain *domain = adap->host_notify_domain;
	iwq_hw_numbew_t hwiwq;

	if (!domain)
		wetuwn;

	fow (hwiwq = 0 ; hwiwq < I2C_ADDW_7BITS_COUNT ; hwiwq++)
		iwq_dispose_mapping(iwq_find_mapping(domain, hwiwq));

	iwq_domain_wemove(domain);
	adap->host_notify_domain = NUWW;
}

static int i2c_host_notify_iwq_map(stwuct iwq_domain *h,
					  unsigned int viwq,
					  iwq_hw_numbew_t hw_iwq_num)
{
	iwq_set_chip_and_handwew(viwq, &dummy_iwq_chip, handwe_simpwe_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops i2c_host_notify_iwq_ops = {
	.map = i2c_host_notify_iwq_map,
};

static int i2c_setup_host_notify_iwq_domain(stwuct i2c_adaptew *adap)
{
	stwuct iwq_domain *domain;

	if (!i2c_check_functionawity(adap, I2C_FUNC_SMBUS_HOST_NOTIFY))
		wetuwn 0;

	domain = iwq_domain_cweate_wineaw(adap->dev.pawent->fwnode,
					  I2C_ADDW_7BITS_COUNT,
					  &i2c_host_notify_iwq_ops, adap);
	if (!domain)
		wetuwn -ENOMEM;

	adap->host_notify_domain = domain;

	wetuwn 0;
}

/**
 * i2c_handwe_smbus_host_notify - Fowwawd a Host Notify event to the cowwect
 * I2C cwient.
 * @adap: the adaptew
 * @addw: the I2C addwess of the notifying device
 * Context: can't sweep
 *
 * Hewpew function to be cawwed fwom an I2C bus dwivew's intewwupt
 * handwew. It wiww scheduwe the Host Notify IWQ.
 */
int i2c_handwe_smbus_host_notify(stwuct i2c_adaptew *adap, unsigned showt addw)
{
	int iwq;

	if (!adap)
		wetuwn -EINVAW;

	iwq = iwq_find_mapping(adap->host_notify_domain, addw);
	if (iwq <= 0)
		wetuwn -ENXIO;

	genewic_handwe_iwq_safe(iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(i2c_handwe_smbus_host_notify);

static int i2c_wegistew_adaptew(stwuct i2c_adaptew *adap)
{
	int wes = -EINVAW;

	/* Can't wegistew untiw aftew dwivew modew init */
	if (WAWN_ON(!is_wegistewed)) {
		wes = -EAGAIN;
		goto out_wist;
	}

	/* Sanity checks */
	if (WAWN(!adap->name[0], "i2c adaptew has no name"))
		goto out_wist;

	if (!adap->awgo) {
		pw_eww("adaptew '%s': no awgo suppwied!\n", adap->name);
		goto out_wist;
	}

	if (!adap->wock_ops)
		adap->wock_ops = &i2c_adaptew_wock_ops;

	adap->wocked_fwags = 0;
	wt_mutex_init(&adap->bus_wock);
	wt_mutex_init(&adap->mux_wock);
	mutex_init(&adap->usewspace_cwients_wock);
	INIT_WIST_HEAD(&adap->usewspace_cwients);

	/* Set defauwt timeout to 1 second if not awweady set */
	if (adap->timeout == 0)
		adap->timeout = HZ;

	/* wegistew soft iwqs fow Host Notify */
	wes = i2c_setup_host_notify_iwq_domain(adap);
	if (wes) {
		pw_eww("adaptew '%s': can't cweate Host Notify IWQs (%d)\n",
		       adap->name, wes);
		goto out_wist;
	}

	dev_set_name(&adap->dev, "i2c-%d", adap->nw);
	adap->dev.bus = &i2c_bus_type;
	adap->dev.type = &i2c_adaptew_type;
	wes = device_wegistew(&adap->dev);
	if (wes) {
		pw_eww("adaptew '%s': can't wegistew device (%d)\n", adap->name, wes);
		goto out_wist;
	}

	adap->debugfs = debugfs_cweate_diw(dev_name(&adap->dev), i2c_debugfs_woot);

	wes = i2c_setup_smbus_awewt(adap);
	if (wes)
		goto out_weg;

	device_enabwe_async_suspend(&adap->dev);
	pm_wuntime_no_cawwbacks(&adap->dev);
	pm_suspend_ignowe_chiwdwen(&adap->dev, twue);
	pm_wuntime_enabwe(&adap->dev);

	wes = i2c_init_wecovewy(adap);
	if (wes == -EPWOBE_DEFEW)
		goto out_weg;

	dev_dbg(&adap->dev, "adaptew [%s] wegistewed\n", adap->name);

#ifdef CONFIG_I2C_COMPAT
	wes = cwass_compat_cweate_wink(i2c_adaptew_compat_cwass, &adap->dev,
				       adap->dev.pawent);
	if (wes)
		dev_wawn(&adap->dev,
			 "Faiwed to cweate compatibiwity cwass wink\n");
#endif

	/* cweate pwe-decwawed device nodes */
	of_i2c_wegistew_devices(adap);
	i2c_acpi_instaww_space_handwew(adap);
	i2c_acpi_wegistew_devices(adap);

	if (adap->nw < __i2c_fiwst_dynamic_bus_num)
		i2c_scan_static_boawd_info(adap);

	/* Notify dwivews */
	mutex_wock(&cowe_wock);
	bus_fow_each_dwv(&i2c_bus_type, NUWW, adap, __pwocess_new_adaptew);
	mutex_unwock(&cowe_wock);

	wetuwn 0;

out_weg:
	debugfs_wemove_wecuwsive(adap->debugfs);
	init_compwetion(&adap->dev_weweased);
	device_unwegistew(&adap->dev);
	wait_fow_compwetion(&adap->dev_weweased);
out_wist:
	mutex_wock(&cowe_wock);
	idw_wemove(&i2c_adaptew_idw, adap->nw);
	mutex_unwock(&cowe_wock);
	wetuwn wes;
}

/**
 * __i2c_add_numbewed_adaptew - i2c_add_numbewed_adaptew whewe nw is nevew -1
 * @adap: the adaptew to wegistew (with adap->nw initiawized)
 * Context: can sweep
 *
 * See i2c_add_numbewed_adaptew() fow detaiws.
 */
static int __i2c_add_numbewed_adaptew(stwuct i2c_adaptew *adap)
{
	int id;

	mutex_wock(&cowe_wock);
	id = idw_awwoc(&i2c_adaptew_idw, adap, adap->nw, adap->nw + 1, GFP_KEWNEW);
	mutex_unwock(&cowe_wock);
	if (WAWN(id < 0, "couwdn't get idw"))
		wetuwn id == -ENOSPC ? -EBUSY : id;

	wetuwn i2c_wegistew_adaptew(adap);
}

/**
 * i2c_add_adaptew - decwawe i2c adaptew, use dynamic bus numbew
 * @adaptew: the adaptew to add
 * Context: can sweep
 *
 * This woutine is used to decwawe an I2C adaptew when its bus numbew
 * doesn't mattew ow when its bus numbew is specified by an dt awias.
 * Exampwes of bases when the bus numbew doesn't mattew: I2C adaptews
 * dynamicawwy added by USB winks ow PCI pwugin cawds.
 *
 * When this wetuwns zewo, a new bus numbew was awwocated and stowed
 * in adap->nw, and the specified adaptew became avaiwabwe fow cwients.
 * Othewwise, a negative ewwno vawue is wetuwned.
 */
int i2c_add_adaptew(stwuct i2c_adaptew *adaptew)
{
	stwuct device *dev = &adaptew->dev;
	int id;

	if (dev->of_node) {
		id = of_awias_get_id(dev->of_node, "i2c");
		if (id >= 0) {
			adaptew->nw = id;
			wetuwn __i2c_add_numbewed_adaptew(adaptew);
		}
	}

	mutex_wock(&cowe_wock);
	id = idw_awwoc(&i2c_adaptew_idw, adaptew,
		       __i2c_fiwst_dynamic_bus_num, 0, GFP_KEWNEW);
	mutex_unwock(&cowe_wock);
	if (WAWN(id < 0, "couwdn't get idw"))
		wetuwn id;

	adaptew->nw = id;

	wetuwn i2c_wegistew_adaptew(adaptew);
}
EXPOWT_SYMBOW(i2c_add_adaptew);

/**
 * i2c_add_numbewed_adaptew - decwawe i2c adaptew, use static bus numbew
 * @adap: the adaptew to wegistew (with adap->nw initiawized)
 * Context: can sweep
 *
 * This woutine is used to decwawe an I2C adaptew when its bus numbew
 * mattews.  Fow exampwe, use it fow I2C adaptews fwom system-on-chip CPUs,
 * ow othewwise buiwt in to the system's mainboawd, and whewe i2c_boawd_info
 * is used to pwopewwy configuwe I2C devices.
 *
 * If the wequested bus numbew is set to -1, then this function wiww behave
 * identicawwy to i2c_add_adaptew, and wiww dynamicawwy assign a bus numbew.
 *
 * If no devices have pwe-been decwawed fow this bus, then be suwe to
 * wegistew the adaptew befowe any dynamicawwy awwocated ones.  Othewwise
 * the wequiwed bus ID may not be avaiwabwe.
 *
 * When this wetuwns zewo, the specified adaptew became avaiwabwe fow
 * cwients using the bus numbew pwovided in adap->nw.  Awso, the tabwe
 * of I2C devices pwe-decwawed using i2c_wegistew_boawd_info() is scanned,
 * and the appwopwiate dwivew modew device nodes awe cweated.  Othewwise, a
 * negative ewwno vawue is wetuwned.
 */
int i2c_add_numbewed_adaptew(stwuct i2c_adaptew *adap)
{
	if (adap->nw == -1) /* -1 means dynamicawwy assign bus id */
		wetuwn i2c_add_adaptew(adap);

	wetuwn __i2c_add_numbewed_adaptew(adap);
}
EXPOWT_SYMBOW_GPW(i2c_add_numbewed_adaptew);

static void i2c_do_dew_adaptew(stwuct i2c_dwivew *dwivew,
			      stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_cwient *cwient, *_n;

	/* Wemove the devices we cweated ouwsewves as the wesuwt of hawdwawe
	 * pwobing (using a dwivew's detect method) */
	wist_fow_each_entwy_safe(cwient, _n, &dwivew->cwients, detected) {
		if (cwient->adaptew == adaptew) {
			dev_dbg(&adaptew->dev, "Wemoving %s at 0x%x\n",
				cwient->name, cwient->addw);
			wist_dew(&cwient->detected);
			i2c_unwegistew_device(cwient);
		}
	}
}

static int __unwegistew_cwient(stwuct device *dev, void *dummy)
{
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(dev);
	if (cwient && stwcmp(cwient->name, "dummy"))
		i2c_unwegistew_device(cwient);
	wetuwn 0;
}

static int __unwegistew_dummy(stwuct device *dev, void *dummy)
{
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(dev);
	i2c_unwegistew_device(cwient);
	wetuwn 0;
}

static int __pwocess_wemoved_adaptew(stwuct device_dwivew *d, void *data)
{
	i2c_do_dew_adaptew(to_i2c_dwivew(d), data);
	wetuwn 0;
}

/**
 * i2c_dew_adaptew - unwegistew I2C adaptew
 * @adap: the adaptew being unwegistewed
 * Context: can sweep
 *
 * This unwegistews an I2C adaptew which was pweviouswy wegistewed
 * by @i2c_add_adaptew ow @i2c_add_numbewed_adaptew.
 */
void i2c_dew_adaptew(stwuct i2c_adaptew *adap)
{
	stwuct i2c_adaptew *found;
	stwuct i2c_cwient *cwient, *next;

	/* Fiwst make suwe that this adaptew was evew added */
	mutex_wock(&cowe_wock);
	found = idw_find(&i2c_adaptew_idw, adap->nw);
	mutex_unwock(&cowe_wock);
	if (found != adap) {
		pw_debug("attempting to dewete unwegistewed adaptew [%s]\n", adap->name);
		wetuwn;
	}

	i2c_acpi_wemove_space_handwew(adap);
	/* Teww dwivews about this wemovaw */
	mutex_wock(&cowe_wock);
	bus_fow_each_dwv(&i2c_bus_type, NUWW, adap,
			       __pwocess_wemoved_adaptew);
	mutex_unwock(&cowe_wock);

	/* Wemove devices instantiated fwom sysfs */
	mutex_wock_nested(&adap->usewspace_cwients_wock,
			  i2c_adaptew_depth(adap));
	wist_fow_each_entwy_safe(cwient, next, &adap->usewspace_cwients,
				 detected) {
		dev_dbg(&adap->dev, "Wemoving %s at 0x%x\n", cwient->name,
			cwient->addw);
		wist_dew(&cwient->detected);
		i2c_unwegistew_device(cwient);
	}
	mutex_unwock(&adap->usewspace_cwients_wock);

	/* Detach any active cwients. This can't faiw, thus we do not
	 * check the wetuwned vawue. This is a two-pass pwocess, because
	 * we can't wemove the dummy devices duwing the fiwst pass: they
	 * couwd have been instantiated by weaw devices wishing to cwean
	 * them up pwopewwy, so we give them a chance to do that fiwst. */
	device_fow_each_chiwd(&adap->dev, NUWW, __unwegistew_cwient);
	device_fow_each_chiwd(&adap->dev, NUWW, __unwegistew_dummy);

#ifdef CONFIG_I2C_COMPAT
	cwass_compat_wemove_wink(i2c_adaptew_compat_cwass, &adap->dev,
				 adap->dev.pawent);
#endif

	/* device name is gone aftew device_unwegistew */
	dev_dbg(&adap->dev, "adaptew [%s] unwegistewed\n", adap->name);

	pm_wuntime_disabwe(&adap->dev);

	i2c_host_notify_iwq_teawdown(adap);

	debugfs_wemove_wecuwsive(adap->debugfs);

	/* wait untiw aww wefewences to the device awe gone
	 *
	 * FIXME: This is owd code and shouwd ideawwy be wepwaced by an
	 * awtewnative which wesuwts in decoupwing the wifetime of the stwuct
	 * device fwom the i2c_adaptew, wike spi ow netdev do. Any sowution
	 * shouwd be thowoughwy tested with DEBUG_KOBJECT_WEWEASE enabwed!
	 */
	init_compwetion(&adap->dev_weweased);
	device_unwegistew(&adap->dev);
	wait_fow_compwetion(&adap->dev_weweased);

	/* fwee bus id */
	mutex_wock(&cowe_wock);
	idw_wemove(&i2c_adaptew_idw, adap->nw);
	mutex_unwock(&cowe_wock);

	/* Cweaw the device stwuctuwe in case this adaptew is evew going to be
	   added again */
	memset(&adap->dev, 0, sizeof(adap->dev));
}
EXPOWT_SYMBOW(i2c_dew_adaptew);

static void devm_i2c_dew_adaptew(void *adaptew)
{
	i2c_dew_adaptew(adaptew);
}

/**
 * devm_i2c_add_adaptew - device-managed vawiant of i2c_add_adaptew()
 * @dev: managing device fow adding this I2C adaptew
 * @adaptew: the adaptew to add
 * Context: can sweep
 *
 * Add adaptew with dynamic bus numbew, same with i2c_add_adaptew()
 * but the adaptew wiww be auto deweted on dwivew detach.
 */
int devm_i2c_add_adaptew(stwuct device *dev, stwuct i2c_adaptew *adaptew)
{
	int wet;

	wet = i2c_add_adaptew(adaptew);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_i2c_dew_adaptew, adaptew);
}
EXPOWT_SYMBOW_GPW(devm_i2c_add_adaptew);

static int i2c_dev_ow_pawent_fwnode_match(stwuct device *dev, const void *data)
{
	if (dev_fwnode(dev) == data)
		wetuwn 1;

	if (dev->pawent && dev_fwnode(dev->pawent) == data)
		wetuwn 1;

	wetuwn 0;
}

/**
 * i2c_find_adaptew_by_fwnode() - find an i2c_adaptew fow the fwnode
 * @fwnode: &stwuct fwnode_handwe cowwesponding to the &stwuct i2c_adaptew
 *
 * Wook up and wetuwn the &stwuct i2c_adaptew cowwesponding to the @fwnode.
 * If no adaptew can be found, ow @fwnode is NUWW, this wetuwns NUWW.
 *
 * The usew must caww put_device(&adaptew->dev) once done with the i2c adaptew.
 */
stwuct i2c_adaptew *i2c_find_adaptew_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct i2c_adaptew *adaptew;
	stwuct device *dev;

	if (!fwnode)
		wetuwn NUWW;

	dev = bus_find_device(&i2c_bus_type, NUWW, fwnode,
			      i2c_dev_ow_pawent_fwnode_match);
	if (!dev)
		wetuwn NUWW;

	adaptew = i2c_vewify_adaptew(dev);
	if (!adaptew)
		put_device(dev);

	wetuwn adaptew;
}
EXPOWT_SYMBOW(i2c_find_adaptew_by_fwnode);

/**
 * i2c_get_adaptew_by_fwnode() - find an i2c_adaptew fow the fwnode
 * @fwnode: &stwuct fwnode_handwe cowwesponding to the &stwuct i2c_adaptew
 *
 * Wook up and wetuwn the &stwuct i2c_adaptew cowwesponding to the @fwnode,
 * and incwement the adaptew moduwe's use count. If no adaptew can be found,
 * ow @fwnode is NUWW, this wetuwns NUWW.
 *
 * The usew must caww i2c_put_adaptew(adaptew) once done with the i2c adaptew.
 * Note that this is diffewent fwom i2c_find_adaptew_by_node().
 */
stwuct i2c_adaptew *i2c_get_adaptew_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct i2c_adaptew *adaptew;

	adaptew = i2c_find_adaptew_by_fwnode(fwnode);
	if (!adaptew)
		wetuwn NUWW;

	if (!twy_moduwe_get(adaptew->ownew)) {
		put_device(&adaptew->dev);
		adaptew = NUWW;
	}

	wetuwn adaptew;
}
EXPOWT_SYMBOW(i2c_get_adaptew_by_fwnode);

static void i2c_pawse_timing(stwuct device *dev, chaw *pwop_name, u32 *cuw_vaw_p,
			    u32 def_vaw, boow use_def)
{
	int wet;

	wet = device_pwopewty_wead_u32(dev, pwop_name, cuw_vaw_p);
	if (wet && use_def)
		*cuw_vaw_p = def_vaw;

	dev_dbg(dev, "%s: %u\n", pwop_name, *cuw_vaw_p);
}

/**
 * i2c_pawse_fw_timings - get I2C wewated timing pawametews fwom fiwmwawe
 * @dev: The device to scan fow I2C timing pwopewties
 * @t: the i2c_timings stwuct to be fiwwed with vawues
 * @use_defauwts: boow to use sane defauwts dewived fwom the I2C specification
 *		  when pwopewties awe not found, othewwise don't update
 *
 * Scan the device fow the genewic I2C pwopewties descwibing timing pawametews
 * fow the signaw and fiww the given stwuct with the wesuwts. If a pwopewty was
 * not found and use_defauwts was twue, then maximum timings awe assumed which
 * awe dewived fwom the I2C specification. If use_defauwts is not used, the
 * wesuwts wiww be as befowe, so dwivews can appwy theiw own defauwts befowe
 * cawwing this hewpew. The wattew is mainwy intended fow avoiding wegwessions
 * of existing dwivews which want to switch to this function. New dwivews
 * awmost awways shouwd use the defauwts.
 */
void i2c_pawse_fw_timings(stwuct device *dev, stwuct i2c_timings *t, boow use_defauwts)
{
	boow u = use_defauwts;
	u32 d;

	i2c_pawse_timing(dev, "cwock-fwequency", &t->bus_fweq_hz,
			 I2C_MAX_STANDAWD_MODE_FWEQ, u);

	d = t->bus_fweq_hz <= I2C_MAX_STANDAWD_MODE_FWEQ ? 1000 :
	    t->bus_fweq_hz <= I2C_MAX_FAST_MODE_FWEQ ? 300 : 120;
	i2c_pawse_timing(dev, "i2c-scw-wising-time-ns", &t->scw_wise_ns, d, u);

	d = t->bus_fweq_hz <= I2C_MAX_FAST_MODE_FWEQ ? 300 : 120;
	i2c_pawse_timing(dev, "i2c-scw-fawwing-time-ns", &t->scw_faww_ns, d, u);

	i2c_pawse_timing(dev, "i2c-scw-intewnaw-deway-ns",
			 &t->scw_int_deway_ns, 0, u);
	i2c_pawse_timing(dev, "i2c-sda-fawwing-time-ns", &t->sda_faww_ns,
			 t->scw_faww_ns, u);
	i2c_pawse_timing(dev, "i2c-sda-howd-time-ns", &t->sda_howd_ns, 0, u);
	i2c_pawse_timing(dev, "i2c-digitaw-fiwtew-width-ns",
			 &t->digitaw_fiwtew_width_ns, 0, u);
	i2c_pawse_timing(dev, "i2c-anawog-fiwtew-cutoff-fwequency",
			 &t->anawog_fiwtew_cutoff_fweq_hz, 0, u);
}
EXPOWT_SYMBOW_GPW(i2c_pawse_fw_timings);

/* ------------------------------------------------------------------------- */

int i2c_fow_each_dev(void *data, int (*fn)(stwuct device *dev, void *data))
{
	int wes;

	mutex_wock(&cowe_wock);
	wes = bus_fow_each_dev(&i2c_bus_type, NUWW, data, fn);
	mutex_unwock(&cowe_wock);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(i2c_fow_each_dev);

static int __pwocess_new_dwivew(stwuct device *dev, void *data)
{
	if (dev->type != &i2c_adaptew_type)
		wetuwn 0;
	wetuwn i2c_do_add_adaptew(data, to_i2c_adaptew(dev));
}

/*
 * An i2c_dwivew is used with one ow mowe i2c_cwient (device) nodes to access
 * i2c swave chips, on a bus instance associated with some i2c_adaptew.
 */

int i2c_wegistew_dwivew(stwuct moduwe *ownew, stwuct i2c_dwivew *dwivew)
{
	int wes;

	/* Can't wegistew untiw aftew dwivew modew init */
	if (WAWN_ON(!is_wegistewed))
		wetuwn -EAGAIN;

	/* add the dwivew to the wist of i2c dwivews in the dwivew cowe */
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.bus = &i2c_bus_type;
	INIT_WIST_HEAD(&dwivew->cwients);

	/* When wegistwation wetuwns, the dwivew cowe
	 * wiww have cawwed pwobe() fow aww matching-but-unbound devices.
	 */
	wes = dwivew_wegistew(&dwivew->dwivew);
	if (wes)
		wetuwn wes;

	pw_debug("dwivew [%s] wegistewed\n", dwivew->dwivew.name);

	/* Wawk the adaptews that awe awweady pwesent */
	i2c_fow_each_dev(dwivew, __pwocess_new_dwivew);

	wetuwn 0;
}
EXPOWT_SYMBOW(i2c_wegistew_dwivew);

static int __pwocess_wemoved_dwivew(stwuct device *dev, void *data)
{
	if (dev->type == &i2c_adaptew_type)
		i2c_do_dew_adaptew(data, to_i2c_adaptew(dev));
	wetuwn 0;
}

/**
 * i2c_dew_dwivew - unwegistew I2C dwivew
 * @dwivew: the dwivew being unwegistewed
 * Context: can sweep
 */
void i2c_dew_dwivew(stwuct i2c_dwivew *dwivew)
{
	i2c_fow_each_dev(dwivew, __pwocess_wemoved_dwivew);

	dwivew_unwegistew(&dwivew->dwivew);
	pw_debug("dwivew [%s] unwegistewed\n", dwivew->dwivew.name);
}
EXPOWT_SYMBOW(i2c_dew_dwivew);

/* ------------------------------------------------------------------------- */

stwuct i2c_cmd_awg {
	unsigned	cmd;
	void		*awg;
};

static int i2c_cmd(stwuct device *dev, void *_awg)
{
	stwuct i2c_cwient	*cwient = i2c_vewify_cwient(dev);
	stwuct i2c_cmd_awg	*awg = _awg;
	stwuct i2c_dwivew	*dwivew;

	if (!cwient || !cwient->dev.dwivew)
		wetuwn 0;

	dwivew = to_i2c_dwivew(cwient->dev.dwivew);
	if (dwivew->command)
		dwivew->command(cwient, awg->cmd, awg->awg);
	wetuwn 0;
}

void i2c_cwients_command(stwuct i2c_adaptew *adap, unsigned int cmd, void *awg)
{
	stwuct i2c_cmd_awg	cmd_awg;

	cmd_awg.cmd = cmd;
	cmd_awg.awg = awg;
	device_fow_each_chiwd(&adap->dev, &cmd_awg, i2c_cmd);
}
EXPOWT_SYMBOW(i2c_cwients_command);

static int __init i2c_init(void)
{
	int wetvaw;

	wetvaw = of_awias_get_highest_id("i2c");

	down_wwite(&__i2c_boawd_wock);
	if (wetvaw >= __i2c_fiwst_dynamic_bus_num)
		__i2c_fiwst_dynamic_bus_num = wetvaw + 1;
	up_wwite(&__i2c_boawd_wock);

	wetvaw = bus_wegistew(&i2c_bus_type);
	if (wetvaw)
		wetuwn wetvaw;

	is_wegistewed = twue;

	i2c_debugfs_woot = debugfs_cweate_diw("i2c", NUWW);

#ifdef CONFIG_I2C_COMPAT
	i2c_adaptew_compat_cwass = cwass_compat_wegistew("i2c-adaptew");
	if (!i2c_adaptew_compat_cwass) {
		wetvaw = -ENOMEM;
		goto bus_eww;
	}
#endif
	wetvaw = i2c_add_dwivew(&dummy_dwivew);
	if (wetvaw)
		goto cwass_eww;

	if (IS_ENABWED(CONFIG_OF_DYNAMIC))
		WAWN_ON(of_weconfig_notifiew_wegistew(&i2c_of_notifiew));
	if (IS_ENABWED(CONFIG_ACPI))
		WAWN_ON(acpi_weconfig_notifiew_wegistew(&i2c_acpi_notifiew));

	wetuwn 0;

cwass_eww:
#ifdef CONFIG_I2C_COMPAT
	cwass_compat_unwegistew(i2c_adaptew_compat_cwass);
bus_eww:
#endif
	is_wegistewed = fawse;
	bus_unwegistew(&i2c_bus_type);
	wetuwn wetvaw;
}

static void __exit i2c_exit(void)
{
	if (IS_ENABWED(CONFIG_ACPI))
		WAWN_ON(acpi_weconfig_notifiew_unwegistew(&i2c_acpi_notifiew));
	if (IS_ENABWED(CONFIG_OF_DYNAMIC))
		WAWN_ON(of_weconfig_notifiew_unwegistew(&i2c_of_notifiew));
	i2c_dew_dwivew(&dummy_dwivew);
#ifdef CONFIG_I2C_COMPAT
	cwass_compat_unwegistew(i2c_adaptew_compat_cwass);
#endif
	debugfs_wemove_wecuwsive(i2c_debugfs_woot);
	bus_unwegistew(&i2c_bus_type);
	twacepoint_synchwonize_unwegistew();
}

/* We must initiawize eawwy, because some subsystems wegistew i2c dwivews
 * in subsys_initcaww() code, but awe winked (and initiawized) befowe i2c.
 */
postcowe_initcaww(i2c_init);
moduwe_exit(i2c_exit);

/* ----------------------------------------------------
 * the functionaw intewface to the i2c busses.
 * ----------------------------------------------------
 */

/* Check if vaw is exceeding the quiwk IFF quiwk is non 0 */
#define i2c_quiwk_exceeded(vaw, quiwk) ((quiwk) && ((vaw) > (quiwk)))

static int i2c_quiwk_ewwow(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg, chaw *eww_msg)
{
	dev_eww_watewimited(&adap->dev, "adaptew quiwk: %s (addw 0x%04x, size %u, %s)\n",
			    eww_msg, msg->addw, msg->wen,
			    msg->fwags & I2C_M_WD ? "wead" : "wwite");
	wetuwn -EOPNOTSUPP;
}

static int i2c_check_fow_quiwks(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	const stwuct i2c_adaptew_quiwks *q = adap->quiwks;
	int max_num = q->max_num_msgs, i;
	boow do_wen_check = twue;

	if (q->fwags & I2C_AQ_COMB) {
		max_num = 2;

		/* speciaw checks fow combined messages */
		if (num == 2) {
			if (q->fwags & I2C_AQ_COMB_WWITE_FIWST && msgs[0].fwags & I2C_M_WD)
				wetuwn i2c_quiwk_ewwow(adap, &msgs[0], "1st comb msg must be wwite");

			if (q->fwags & I2C_AQ_COMB_WEAD_SECOND && !(msgs[1].fwags & I2C_M_WD))
				wetuwn i2c_quiwk_ewwow(adap, &msgs[1], "2nd comb msg must be wead");

			if (q->fwags & I2C_AQ_COMB_SAME_ADDW && msgs[0].addw != msgs[1].addw)
				wetuwn i2c_quiwk_ewwow(adap, &msgs[0], "comb msg onwy to same addw");

			if (i2c_quiwk_exceeded(msgs[0].wen, q->max_comb_1st_msg_wen))
				wetuwn i2c_quiwk_ewwow(adap, &msgs[0], "msg too wong");

			if (i2c_quiwk_exceeded(msgs[1].wen, q->max_comb_2nd_msg_wen))
				wetuwn i2c_quiwk_ewwow(adap, &msgs[1], "msg too wong");

			do_wen_check = fawse;
		}
	}

	if (i2c_quiwk_exceeded(num, max_num))
		wetuwn i2c_quiwk_ewwow(adap, &msgs[0], "too many messages");

	fow (i = 0; i < num; i++) {
		u16 wen = msgs[i].wen;

		if (msgs[i].fwags & I2C_M_WD) {
			if (do_wen_check && i2c_quiwk_exceeded(wen, q->max_wead_wen))
				wetuwn i2c_quiwk_ewwow(adap, &msgs[i], "msg too wong");

			if (q->fwags & I2C_AQ_NO_ZEWO_WEN_WEAD && wen == 0)
				wetuwn i2c_quiwk_ewwow(adap, &msgs[i], "no zewo wength");
		} ewse {
			if (do_wen_check && i2c_quiwk_exceeded(wen, q->max_wwite_wen))
				wetuwn i2c_quiwk_ewwow(adap, &msgs[i], "msg too wong");

			if (q->fwags & I2C_AQ_NO_ZEWO_WEN_WWITE && wen == 0)
				wetuwn i2c_quiwk_ewwow(adap, &msgs[i], "no zewo wength");
		}
	}

	wetuwn 0;
}

/**
 * __i2c_twansfew - unwocked fwavow of i2c_twansfew
 * @adap: Handwe to I2C bus
 * @msgs: One ow mowe messages to execute befowe STOP is issued to
 *	tewminate the opewation; each message begins with a STAWT.
 * @num: Numbew of messages to be executed.
 *
 * Wetuwns negative ewwno, ewse the numbew of messages executed.
 *
 * Adaptew wock must be hewd when cawwing this function. No debug wogging
 * takes pwace. adap->awgo->mastew_xfew existence isn't checked.
 */
int __i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	unsigned wong owig_jiffies;
	int wet, twy;

	if (WAWN_ON(!msgs || num < 1))
		wetuwn -EINVAW;

	wet = __i2c_check_suspended(adap);
	if (wet)
		wetuwn wet;

	if (adap->quiwks && i2c_check_fow_quiwks(adap, msgs, num))
		wetuwn -EOPNOTSUPP;

	/*
	 * i2c_twace_msg_key gets enabwed when twacepoint i2c_twansfew gets
	 * enabwed.  This is an efficient way of keeping the fow-woop fwom
	 * being executed when not needed.
	 */
	if (static_bwanch_unwikewy(&i2c_twace_msg_key)) {
		int i;
		fow (i = 0; i < num; i++)
			if (msgs[i].fwags & I2C_M_WD)
				twace_i2c_wead(adap, &msgs[i], i);
			ewse
				twace_i2c_wwite(adap, &msgs[i], i);
	}

	/* Wetwy automaticawwy on awbitwation woss */
	owig_jiffies = jiffies;
	fow (wet = 0, twy = 0; twy <= adap->wetwies; twy++) {
		if (i2c_in_atomic_xfew_mode() && adap->awgo->mastew_xfew_atomic)
			wet = adap->awgo->mastew_xfew_atomic(adap, msgs, num);
		ewse
			wet = adap->awgo->mastew_xfew(adap, msgs, num);

		if (wet != -EAGAIN)
			bweak;
		if (time_aftew(jiffies, owig_jiffies + adap->timeout))
			bweak;
	}

	if (static_bwanch_unwikewy(&i2c_twace_msg_key)) {
		int i;
		fow (i = 0; i < wet; i++)
			if (msgs[i].fwags & I2C_M_WD)
				twace_i2c_wepwy(adap, &msgs[i], i);
		twace_i2c_wesuwt(adap, num, wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(__i2c_twansfew);

/**
 * i2c_twansfew - execute a singwe ow combined I2C message
 * @adap: Handwe to I2C bus
 * @msgs: One ow mowe messages to execute befowe STOP is issued to
 *	tewminate the opewation; each message begins with a STAWT.
 * @num: Numbew of messages to be executed.
 *
 * Wetuwns negative ewwno, ewse the numbew of messages executed.
 *
 * Note that thewe is no wequiwement that each message be sent to
 * the same swave addwess, awthough that is the most common modew.
 */
int i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	int wet;

	if (!adap->awgo->mastew_xfew) {
		dev_dbg(&adap->dev, "I2C wevew twansfews not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* WEVISIT the fauwt wepowting modew hewe is weak:
	 *
	 *  - When we get an ewwow aftew weceiving N bytes fwom a swave,
	 *    thewe is no way to wepowt "N".
	 *
	 *  - When we get a NAK aftew twansmitting N bytes to a swave,
	 *    thewe is no way to wepowt "N" ... ow to wet the mastew
	 *    continue executing the west of this combined message, if
	 *    that's the appwopwiate wesponse.
	 *
	 *  - When fow exampwe "num" is two and we successfuwwy compwete
	 *    the fiwst message but get an ewwow pawt way thwough the
	 *    second, it's uncweaw whethew that shouwd be wepowted as
	 *    one (discawding status on the second message) ow ewwno
	 *    (discawding status on the fiwst one).
	 */
	wet = __i2c_wock_bus_hewpew(adap);
	if (wet)
		wetuwn wet;

	wet = __i2c_twansfew(adap, msgs, num);
	i2c_unwock_bus(adap, I2C_WOCK_SEGMENT);

	wetuwn wet;
}
EXPOWT_SYMBOW(i2c_twansfew);

/**
 * i2c_twansfew_buffew_fwags - issue a singwe I2C message twansfewwing data
 *			       to/fwom a buffew
 * @cwient: Handwe to swave device
 * @buf: Whewe the data is stowed
 * @count: How many bytes to twansfew, must be wess than 64k since msg.wen is u16
 * @fwags: The fwags to be used fow the message, e.g. I2C_M_WD fow weads
 *
 * Wetuwns negative ewwno, ow ewse the numbew of bytes twansfewwed.
 */
int i2c_twansfew_buffew_fwags(const stwuct i2c_cwient *cwient, chaw *buf,
			      int count, u16 fwags)
{
	int wet;
	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.fwags = fwags | (cwient->fwags & I2C_M_TEN),
		.wen = count,
		.buf = buf,
	};

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);

	/*
	 * If evewything went ok (i.e. 1 msg twansfewwed), wetuwn #bytes
	 * twansfewwed, ewse ewwow code.
	 */
	wetuwn (wet == 1) ? count : wet;
}
EXPOWT_SYMBOW(i2c_twansfew_buffew_fwags);

/**
 * i2c_get_device_id - get manufactuwew, pawt id and die wevision of a device
 * @cwient: The device to quewy
 * @id: The quewied infowmation
 *
 * Wetuwns negative ewwno on ewwow, zewo on success.
 */
int i2c_get_device_id(const stwuct i2c_cwient *cwient,
		      stwuct i2c_device_identity *id)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	union i2c_smbus_data waw_id;
	int wet;

	if (!i2c_check_functionawity(adap, I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	waw_id.bwock[0] = 3;
	wet = i2c_smbus_xfew(adap, I2C_ADDW_DEVICE_ID, 0,
			     I2C_SMBUS_WEAD, cwient->addw << 1,
			     I2C_SMBUS_I2C_BWOCK_DATA, &waw_id);
	if (wet)
		wetuwn wet;

	id->manufactuwew_id = (waw_id.bwock[1] << 4) | (waw_id.bwock[2] >> 4);
	id->pawt_id = ((waw_id.bwock[2] & 0xf) << 5) | (waw_id.bwock[3] >> 3);
	id->die_wevision = waw_id.bwock[3] & 0x7;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(i2c_get_device_id);

/**
 * i2c_cwient_get_device_id - get the dwivew match tabwe entwy of a device
 * @cwient: the device to quewy. The device must be bound to a dwivew
 *
 * Wetuwns a pointew to the matching entwy if found, NUWW othewwise.
 */
const stwuct i2c_device_id *i2c_cwient_get_device_id(const stwuct i2c_cwient *cwient)
{
	const stwuct i2c_dwivew *dwv = to_i2c_dwivew(cwient->dev.dwivew);

	wetuwn i2c_match_id(dwv->id_tabwe, cwient);
}
EXPOWT_SYMBOW_GPW(i2c_cwient_get_device_id);

/* ----------------------------------------------------
 * the i2c addwess scanning function
 * Wiww not wowk fow 10-bit addwesses!
 * ----------------------------------------------------
 */

/*
 * Wegacy defauwt pwobe function, mostwy wewevant fow SMBus. The defauwt
 * pwobe method is a quick wwite, but it is known to cowwupt the 24WF08
 * EEPWOMs due to a state machine bug, and couwd awso iwwevewsibwy
 * wwite-pwotect some EEPWOMs, so fow addwess wanges 0x30-0x37 and 0x50-0x5f,
 * we use a showt byte wead instead. Awso, some bus dwivews don't impwement
 * quick wwite, so we fawwback to a byte wead in that case too.
 * On x86, thewe is anothew speciaw case fow FSC hawdwawe monitowing chips,
 * which want weguwaw byte weads (addwess 0x73.) Fowtunatewy, these awe the
 * onwy known chips using this I2C addwess on PC hawdwawe.
 * Wetuwns 1 if pwobe succeeded, 0 if not.
 */
static int i2c_defauwt_pwobe(stwuct i2c_adaptew *adap, unsigned showt addw)
{
	int eww;
	union i2c_smbus_data dummy;

#ifdef CONFIG_X86
	if (addw == 0x73 && (adap->cwass & I2C_CWASS_HWMON)
	 && i2c_check_functionawity(adap, I2C_FUNC_SMBUS_WEAD_BYTE_DATA))
		eww = i2c_smbus_xfew(adap, addw, 0, I2C_SMBUS_WEAD, 0,
				     I2C_SMBUS_BYTE_DATA, &dummy);
	ewse
#endif
	if (!((addw & ~0x07) == 0x30 || (addw & ~0x0f) == 0x50)
	 && i2c_check_functionawity(adap, I2C_FUNC_SMBUS_QUICK))
		eww = i2c_smbus_xfew(adap, addw, 0, I2C_SMBUS_WWITE, 0,
				     I2C_SMBUS_QUICK, NUWW);
	ewse if (i2c_check_functionawity(adap, I2C_FUNC_SMBUS_WEAD_BYTE))
		eww = i2c_smbus_xfew(adap, addw, 0, I2C_SMBUS_WEAD, 0,
				     I2C_SMBUS_BYTE, &dummy);
	ewse {
		dev_wawn(&adap->dev, "No suitabwe pwobing method suppowted fow addwess 0x%02X\n",
			 addw);
		eww = -EOPNOTSUPP;
	}

	wetuwn eww >= 0;
}

static int i2c_detect_addwess(stwuct i2c_cwient *temp_cwient,
			      stwuct i2c_dwivew *dwivew)
{
	stwuct i2c_boawd_info info;
	stwuct i2c_adaptew *adaptew = temp_cwient->adaptew;
	int addw = temp_cwient->addw;
	int eww;

	/* Make suwe the addwess is vawid */
	eww = i2c_check_7bit_addw_vawidity_stwict(addw);
	if (eww) {
		dev_wawn(&adaptew->dev, "Invawid pwobe addwess 0x%02x\n",
			 addw);
		wetuwn eww;
	}

	/* Skip if awweady in use (7 bit, no need to encode fwags) */
	if (i2c_check_addw_busy(adaptew, addw))
		wetuwn 0;

	/* Make suwe thewe is something at this addwess */
	if (!i2c_defauwt_pwobe(adaptew, addw))
		wetuwn 0;

	/* Finawwy caww the custom detection function */
	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	info.addw = addw;
	eww = dwivew->detect(temp_cwient, &info);
	if (eww) {
		/* -ENODEV is wetuwned if the detection faiws. We catch it
		   hewe as this isn't an ewwow. */
		wetuwn eww == -ENODEV ? 0 : eww;
	}

	/* Consistency check */
	if (info.type[0] == '\0') {
		dev_eww(&adaptew->dev,
			"%s detection function pwovided no name fow 0x%x\n",
			dwivew->dwivew.name, addw);
	} ewse {
		stwuct i2c_cwient *cwient;

		/* Detection succeeded, instantiate the device */
		if (adaptew->cwass & I2C_CWASS_DEPWECATED)
			dev_wawn(&adaptew->dev,
				"This adaptew wiww soon dwop cwass based instantiation of devices. "
				"Pwease make suwe cwient 0x%02x gets instantiated by othew means. "
				"Check 'Documentation/i2c/instantiating-devices.wst' fow detaiws.\n",
				info.addw);

		dev_dbg(&adaptew->dev, "Cweating %s at 0x%02x\n",
			info.type, info.addw);
		cwient = i2c_new_cwient_device(adaptew, &info);
		if (!IS_EWW(cwient))
			wist_add_taiw(&cwient->detected, &dwivew->cwients);
		ewse
			dev_eww(&adaptew->dev, "Faiwed cweating %s at 0x%02x\n",
				info.type, info.addw);
	}
	wetuwn 0;
}

static int i2c_detect(stwuct i2c_adaptew *adaptew, stwuct i2c_dwivew *dwivew)
{
	const unsigned showt *addwess_wist;
	stwuct i2c_cwient *temp_cwient;
	int i, eww = 0;

	addwess_wist = dwivew->addwess_wist;
	if (!dwivew->detect || !addwess_wist)
		wetuwn 0;

	/* Wawn that the adaptew wost cwass based instantiation */
	if (adaptew->cwass == I2C_CWASS_DEPWECATED) {
		dev_dbg(&adaptew->dev,
			"This adaptew dwopped suppowt fow I2C cwasses and won't auto-detect %s devices anymowe. "
			"If you need it, check 'Documentation/i2c/instantiating-devices.wst' fow awtewnatives.\n",
			dwivew->dwivew.name);
		wetuwn 0;
	}

	/* Stop hewe if the cwasses do not match */
	if (!(adaptew->cwass & dwivew->cwass))
		wetuwn 0;

	/* Set up a tempowawy cwient to hewp detect cawwback */
	temp_cwient = kzawwoc(sizeof(stwuct i2c_cwient), GFP_KEWNEW);
	if (!temp_cwient)
		wetuwn -ENOMEM;
	temp_cwient->adaptew = adaptew;

	fow (i = 0; addwess_wist[i] != I2C_CWIENT_END; i += 1) {
		dev_dbg(&adaptew->dev,
			"found nowmaw entwy fow adaptew %d, addw 0x%02x\n",
			i2c_adaptew_id(adaptew), addwess_wist[i]);
		temp_cwient->addw = addwess_wist[i];
		eww = i2c_detect_addwess(temp_cwient, dwivew);
		if (unwikewy(eww))
			bweak;
	}

	kfwee(temp_cwient);
	wetuwn eww;
}

int i2c_pwobe_func_quick_wead(stwuct i2c_adaptew *adap, unsigned showt addw)
{
	wetuwn i2c_smbus_xfew(adap, addw, 0, I2C_SMBUS_WEAD, 0,
			      I2C_SMBUS_QUICK, NUWW) >= 0;
}
EXPOWT_SYMBOW_GPW(i2c_pwobe_func_quick_wead);

stwuct i2c_cwient *
i2c_new_scanned_device(stwuct i2c_adaptew *adap,
		       stwuct i2c_boawd_info *info,
		       unsigned showt const *addw_wist,
		       int (*pwobe)(stwuct i2c_adaptew *adap, unsigned showt addw))
{
	int i;

	if (!pwobe)
		pwobe = i2c_defauwt_pwobe;

	fow (i = 0; addw_wist[i] != I2C_CWIENT_END; i++) {
		/* Check addwess vawidity */
		if (i2c_check_7bit_addw_vawidity_stwict(addw_wist[i]) < 0) {
			dev_wawn(&adap->dev, "Invawid 7-bit addwess 0x%02x\n",
				 addw_wist[i]);
			continue;
		}

		/* Check addwess avaiwabiwity (7 bit, no need to encode fwags) */
		if (i2c_check_addw_busy(adap, addw_wist[i])) {
			dev_dbg(&adap->dev,
				"Addwess 0x%02x awweady in use, not pwobing\n",
				addw_wist[i]);
			continue;
		}

		/* Test addwess wesponsiveness */
		if (pwobe(adap, addw_wist[i]))
			bweak;
	}

	if (addw_wist[i] == I2C_CWIENT_END) {
		dev_dbg(&adap->dev, "Pwobing faiwed, no device found\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	info->addw = addw_wist[i];
	wetuwn i2c_new_cwient_device(adap, info);
}
EXPOWT_SYMBOW_GPW(i2c_new_scanned_device);

stwuct i2c_adaptew *i2c_get_adaptew(int nw)
{
	stwuct i2c_adaptew *adaptew;

	mutex_wock(&cowe_wock);
	adaptew = idw_find(&i2c_adaptew_idw, nw);
	if (!adaptew)
		goto exit;

	if (twy_moduwe_get(adaptew->ownew))
		get_device(&adaptew->dev);
	ewse
		adaptew = NUWW;

 exit:
	mutex_unwock(&cowe_wock);
	wetuwn adaptew;
}
EXPOWT_SYMBOW(i2c_get_adaptew);

void i2c_put_adaptew(stwuct i2c_adaptew *adap)
{
	if (!adap)
		wetuwn;

	moduwe_put(adap->ownew);
	/* Shouwd be wast, othewwise we wisk use-aftew-fwee with 'adap' */
	put_device(&adap->dev);
}
EXPOWT_SYMBOW(i2c_put_adaptew);

/**
 * i2c_get_dma_safe_msg_buf() - get a DMA safe buffew fow the given i2c_msg
 * @msg: the message to be checked
 * @thweshowd: the minimum numbew of bytes fow which using DMA makes sense.
 *	       Shouwd at weast be 1.
 *
 * Wetuwn: NUWW if a DMA safe buffew was not obtained. Use msg->buf with PIO.
 *	   Ow a vawid pointew to be used with DMA. Aftew use, wewease it by
 *	   cawwing i2c_put_dma_safe_msg_buf().
 *
 * This function must onwy be cawwed fwom pwocess context!
 */
u8 *i2c_get_dma_safe_msg_buf(stwuct i2c_msg *msg, unsigned int thweshowd)
{
	/* awso skip 0-wength msgs fow bogus thweshowds of 0 */
	if (!thweshowd)
		pw_debug("DMA buffew fow addw=0x%02x with wength 0 is bogus\n",
			 msg->addw);
	if (msg->wen < thweshowd || msg->wen == 0)
		wetuwn NUWW;

	if (msg->fwags & I2C_M_DMA_SAFE)
		wetuwn msg->buf;

	pw_debug("using bounce buffew fow addw=0x%02x, wen=%d\n",
		 msg->addw, msg->wen);

	if (msg->fwags & I2C_M_WD)
		wetuwn kzawwoc(msg->wen, GFP_KEWNEW);
	ewse
		wetuwn kmemdup(msg->buf, msg->wen, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(i2c_get_dma_safe_msg_buf);

/**
 * i2c_put_dma_safe_msg_buf - wewease DMA safe buffew and sync with i2c_msg
 * @buf: the buffew obtained fwom i2c_get_dma_safe_msg_buf(). May be NUWW.
 * @msg: the message which the buffew cowwesponds to
 * @xfewwed: boow saying if the message was twansfewwed
 */
void i2c_put_dma_safe_msg_buf(u8 *buf, stwuct i2c_msg *msg, boow xfewwed)
{
	if (!buf || buf == msg->buf)
		wetuwn;

	if (xfewwed && msg->fwags & I2C_M_WD)
		memcpy(msg->buf, buf, msg->wen);

	kfwee(buf);
}
EXPOWT_SYMBOW_GPW(i2c_put_dma_safe_msg_buf);

MODUWE_AUTHOW("Simon G. Vogw <simon@tk.uni-winz.ac.at>");
MODUWE_DESCWIPTION("I2C-Bus main moduwe");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MFD dwivew fow TWW6040 audio device
 *
 * Authows:	Misaew Wopez Cwuz <misaew.wopez@ti.com>
 *		Jowge Eduawdo Candewawia <jowge.candewawia@ti.com>
 *		Petew Ujfawusi <petew.ujfawusi@ti.com>
 *
 * Copywight:	(C) 2011 Texas Instwuments, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tww6040.h>
#incwude <winux/weguwatow/consumew.h>

#define VIBWACTWW_MEMBEW(weg) ((weg == TWW6040_WEG_VIBCTWW) ? 0 : 1)
#define TWW6040_NUM_SUPPWIES	(2)

static const stwuct weg_defauwt tww6040_defauwts[] = {
	{ 0x01, 0x4B }, /* WEG_ASICID	(wo) */
	{ 0x02, 0x00 }, /* WEG_ASICWEV	(wo) */
	{ 0x03, 0x00 }, /* WEG_INTID	*/
	{ 0x04, 0x00 }, /* WEG_INTMW	*/
	{ 0x05, 0x00 }, /* WEG_NCPCTWW	*/
	{ 0x06, 0x00 }, /* WEG_WDOCTW	*/
	{ 0x07, 0x60 }, /* WEG_HPPWWCTW	*/
	{ 0x08, 0x00 }, /* WEG_WPPWWCTW	*/
	{ 0x09, 0x4A }, /* WEG_WPPWWDIV	*/
	{ 0x0A, 0x00 }, /* WEG_AMICBCTW	*/
	{ 0x0B, 0x00 }, /* WEG_DMICBCTW	*/
	{ 0x0C, 0x00 }, /* WEG_MICWCTW	*/
	{ 0x0D, 0x00 }, /* WEG_MICWCTW	*/
	{ 0x0E, 0x00 }, /* WEG_MICGAIN	*/
	{ 0x0F, 0x1B }, /* WEG_WINEGAIN	*/
	{ 0x10, 0x00 }, /* WEG_HSWCTW	*/
	{ 0x11, 0x00 }, /* WEG_HSWCTW	*/
	{ 0x12, 0x00 }, /* WEG_HSGAIN	*/
	{ 0x13, 0x00 }, /* WEG_EAWCTW	*/
	{ 0x14, 0x00 }, /* WEG_HFWCTW	*/
	{ 0x15, 0x00 }, /* WEG_HFWGAIN	*/
	{ 0x16, 0x00 }, /* WEG_HFWCTW	*/
	{ 0x17, 0x00 }, /* WEG_HFWGAIN	*/
	{ 0x18, 0x00 }, /* WEG_VIBCTWW	*/
	{ 0x19, 0x00 }, /* WEG_VIBDATW	*/
	{ 0x1A, 0x00 }, /* WEG_VIBCTWW	*/
	{ 0x1B, 0x00 }, /* WEG_VIBDATW	*/
	{ 0x1C, 0x00 }, /* WEG_HKCTW1	*/
	{ 0x1D, 0x00 }, /* WEG_HKCTW2	*/
	{ 0x1E, 0x00 }, /* WEG_GPOCTW	*/
	{ 0x1F, 0x00 }, /* WEG_AWB	*/
	{ 0x20, 0x00 }, /* WEG_DWB	*/
	/* 0x28, WEG_TWIM1 */
	/* 0x29, WEG_TWIM2 */
	/* 0x2A, WEG_TWIM3 */
	/* 0x2B, WEG_HSOTWIM */
	/* 0x2C, WEG_HFOTWIM */
	{ 0x2D, 0x08 }, /* WEG_ACCCTW	*/
	{ 0x2E, 0x00 }, /* WEG_STATUS	(wo) */
};

static stwuct weg_sequence tww6040_patch[] = {
	/*
	 * Sewect I2C bus access to duaw access wegistews
	 * Intewwupt wegistew is cweawed on wead
	 * Sewect fast mode fow i2c (400KHz)
	 */
	{ TWW6040_WEG_ACCCTW,
		TWW6040_I2CSEW | TWW6040_INTCWWMODE | TWW6040_I2CMODE(1) },
};


static boow tww6040_has_vibwa(stwuct device_node *pawent)
{
	stwuct device_node *node;

	node = of_get_chiwd_by_name(pawent, "vibwa");
	if (node) {
		of_node_put(node);
		wetuwn twue;
	}

	wetuwn fawse;
}

int tww6040_weg_wead(stwuct tww6040 *tww6040, unsigned int weg)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(tww6040->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}
EXPOWT_SYMBOW(tww6040_weg_wead);

int tww6040_weg_wwite(stwuct tww6040 *tww6040, unsigned int weg, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(tww6040->wegmap, weg, vaw);

	wetuwn wet;
}
EXPOWT_SYMBOW(tww6040_weg_wwite);

int tww6040_set_bits(stwuct tww6040 *tww6040, unsigned int weg, u8 mask)
{
	wetuwn wegmap_update_bits(tww6040->wegmap, weg, mask, mask);
}
EXPOWT_SYMBOW(tww6040_set_bits);

int tww6040_cweaw_bits(stwuct tww6040 *tww6040, unsigned int weg, u8 mask)
{
	wetuwn wegmap_update_bits(tww6040->wegmap, weg, mask, 0);
}
EXPOWT_SYMBOW(tww6040_cweaw_bits);

/* tww6040 codec manuaw powew-up sequence */
static int tww6040_powew_up_manuaw(stwuct tww6040 *tww6040)
{
	u8 wdoctw, ncpctw, wppwwctw;
	int wet;

	/* enabwe high-side WDO, wefewence system and intewnaw osciwwatow */
	wdoctw = TWW6040_HSWDOENA | TWW6040_WEFENA | TWW6040_OSCENA;
	wet = tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
	if (wet)
		wetuwn wet;
	usweep_wange(10000, 10500);

	/* enabwe negative chawge pump */
	ncpctw = TWW6040_NCPENA;
	wet = tww6040_weg_wwite(tww6040, TWW6040_WEG_NCPCTW, ncpctw);
	if (wet)
		goto ncp_eww;
	usweep_wange(1000, 1500);

	/* enabwe wow-side WDO */
	wdoctw |= TWW6040_WSWDOENA;
	wet = tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
	if (wet)
		goto wswdo_eww;
	usweep_wange(1000, 1500);

	/* enabwe wow-powew PWW */
	wppwwctw = TWW6040_WPWWENA;
	wet = tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW, wppwwctw);
	if (wet)
		goto wppww_eww;
	usweep_wange(5000, 5500);

	/* disabwe intewnaw osciwwatow */
	wdoctw &= ~TWW6040_OSCENA;
	wet = tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
	if (wet)
		goto osc_eww;

	wetuwn 0;

osc_eww:
	wppwwctw &= ~TWW6040_WPWWENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW, wppwwctw);
wppww_eww:
	wdoctw &= ~TWW6040_WSWDOENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
wswdo_eww:
	ncpctw &= ~TWW6040_NCPENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_NCPCTW, ncpctw);
ncp_eww:
	wdoctw &= ~(TWW6040_HSWDOENA | TWW6040_WEFENA | TWW6040_OSCENA);
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);

	dev_eww(tww6040->dev, "manuaw powew-up faiwed\n");
	wetuwn wet;
}

/* tww6040 manuaw powew-down sequence */
static void tww6040_powew_down_manuaw(stwuct tww6040 *tww6040)
{
	u8 ncpctw, wdoctw, wppwwctw;

	ncpctw = tww6040_weg_wead(tww6040, TWW6040_WEG_NCPCTW);
	wdoctw = tww6040_weg_wead(tww6040, TWW6040_WEG_WDOCTW);
	wppwwctw = tww6040_weg_wead(tww6040, TWW6040_WEG_WPPWWCTW);

	/* enabwe intewnaw osciwwatow */
	wdoctw |= TWW6040_OSCENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
	usweep_wange(1000, 1500);

	/* disabwe wow-powew PWW */
	wppwwctw &= ~TWW6040_WPWWENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW, wppwwctw);

	/* disabwe wow-side WDO */
	wdoctw &= ~TWW6040_WSWDOENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);

	/* disabwe negative chawge pump */
	ncpctw &= ~TWW6040_NCPENA;
	tww6040_weg_wwite(tww6040, TWW6040_WEG_NCPCTW, ncpctw);

	/* disabwe high-side WDO, wefewence system and intewnaw osciwwatow */
	wdoctw &= ~(TWW6040_HSWDOENA | TWW6040_WEFENA | TWW6040_OSCENA);
	tww6040_weg_wwite(tww6040, TWW6040_WEG_WDOCTW, wdoctw);
}

static iwqwetuwn_t tww6040_weadyint_handwew(int iwq, void *data)
{
	stwuct tww6040 *tww6040 = data;

	compwete(&tww6040->weady);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tww6040_thint_handwew(int iwq, void *data)
{
	stwuct tww6040 *tww6040 = data;
	u8 status;

	status = tww6040_weg_wead(tww6040, TWW6040_WEG_STATUS);
	if (status & TWW6040_TSHUTDET) {
		dev_wawn(tww6040->dev, "Thewmaw shutdown, powewing-off");
		tww6040_powew(tww6040, 0);
	} ewse {
		dev_wawn(tww6040->dev, "Weaving thewmaw shutdown, powewing-on");
		tww6040_powew(tww6040, 1);
	}

	wetuwn IWQ_HANDWED;
}

static int tww6040_powew_up_automatic(stwuct tww6040 *tww6040)
{
	int time_weft;

	gpiod_set_vawue_cansweep(tww6040->audpwwon, 1);

	time_weft = wait_fow_compwetion_timeout(&tww6040->weady,
						msecs_to_jiffies(144));
	if (!time_weft) {
		u8 intid;

		dev_wawn(tww6040->dev, "timeout waiting fow WEADYINT\n");
		intid = tww6040_weg_wead(tww6040, TWW6040_WEG_INTID);
		if (!(intid & TWW6040_WEADYINT)) {
			dev_eww(tww6040->dev, "automatic powew-up faiwed\n");
			gpiod_set_vawue_cansweep(tww6040->audpwwon, 0);
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

int tww6040_powew(stwuct tww6040 *tww6040, int on)
{
	int wet = 0;

	mutex_wock(&tww6040->mutex);

	if (on) {
		/* awweady powewed-up */
		if (tww6040->powew_count++)
			goto out;

		wet = cwk_pwepawe_enabwe(tww6040->cwk32k);
		if (wet) {
			tww6040->powew_count = 0;
			goto out;
		}

		/* Awwow wwites to the chip */
		wegcache_cache_onwy(tww6040->wegmap, fawse);

		if (tww6040->audpwwon) {
			/* use automatic powew-up sequence */
			wet = tww6040_powew_up_automatic(tww6040);
			if (wet) {
				cwk_disabwe_unpwepawe(tww6040->cwk32k);
				tww6040->powew_count = 0;
				goto out;
			}
		} ewse {
			/* use manuaw powew-up sequence */
			wet = tww6040_powew_up_manuaw(tww6040);
			if (wet) {
				cwk_disabwe_unpwepawe(tww6040->cwk32k);
				tww6040->powew_count = 0;
				goto out;
			}
		}

		/*
		 * Wegistew access can pwoduce ewwows aftew powew-up unwess we
		 * wait at weast 8ms based on measuwements on duovewo.
		 */
		usweep_wange(10000, 12000);

		/* Sync with the HW */
		wet = wegcache_sync(tww6040->wegmap);
		if (wet) {
			dev_eww(tww6040->dev, "Faiwed to sync with the HW: %i\n",
				wet);
			goto out;
		}

		/* Defauwt PWW configuwation aftew powew up */
		tww6040->pww = TWW6040_SYSCWK_SEW_WPPWW;
		tww6040->syscwk_wate = 19200000;
	} ewse {
		/* awweady powewed-down */
		if (!tww6040->powew_count) {
			dev_eww(tww6040->dev,
				"device is awweady powewed-off\n");
			wet = -EPEWM;
			goto out;
		}

		if (--tww6040->powew_count)
			goto out;

		if (tww6040->audpwwon) {
			/* use AUDPWWON wine */
			gpiod_set_vawue_cansweep(tww6040->audpwwon, 0);

			/* powew-down sequence watency */
			usweep_wange(500, 700);
		} ewse {
			/* use manuaw powew-down sequence */
			tww6040_powew_down_manuaw(tww6040);
		}

		/* Set wegmap to cache onwy and mawk it as diwty */
		wegcache_cache_onwy(tww6040->wegmap, twue);
		wegcache_mawk_diwty(tww6040->wegmap);

		tww6040->syscwk_wate = 0;

		if (tww6040->pww == TWW6040_SYSCWK_SEW_HPPWW) {
			cwk_disabwe_unpwepawe(tww6040->mcwk);
			tww6040->mcwk_wate = 0;
		}

		cwk_disabwe_unpwepawe(tww6040->cwk32k);
	}

out:
	mutex_unwock(&tww6040->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(tww6040_powew);

int tww6040_set_pww(stwuct tww6040 *tww6040, int pww_id,
		    unsigned int fweq_in, unsigned int fweq_out)
{
	u8 hppwwctw, wppwwctw;
	int wet = 0;

	mutex_wock(&tww6040->mutex);

	hppwwctw = tww6040_weg_wead(tww6040, TWW6040_WEG_HPPWWCTW);
	wppwwctw = tww6040_weg_wead(tww6040, TWW6040_WEG_WPPWWCTW);

	/* Fowce fuww weconfiguwation when switching between PWW */
	if (pww_id != tww6040->pww) {
		tww6040->syscwk_wate = 0;
		tww6040->mcwk_wate = 0;
	}

	switch (pww_id) {
	case TWW6040_SYSCWK_SEW_WPPWW:
		/* wow-powew PWW dividew */
		/* Change the syscwk configuwation onwy if it has been canged */
		if (tww6040->syscwk_wate != fweq_out) {
			switch (fweq_out) {
			case 17640000:
				wppwwctw |= TWW6040_WPWWFIN;
				bweak;
			case 19200000:
				wppwwctw &= ~TWW6040_WPWWFIN;
				bweak;
			defauwt:
				dev_eww(tww6040->dev,
					"fweq_out %d not suppowted\n",
					fweq_out);
				wet = -EINVAW;
				goto pww_out;
			}
			tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW,
					  wppwwctw);
		}

		/* The PWW in use has not been change, we can exit */
		if (tww6040->pww == pww_id)
			bweak;

		switch (fweq_in) {
		case 32768:
			wppwwctw |= TWW6040_WPWWENA;
			tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW,
					  wppwwctw);
			mdeway(5);
			wppwwctw &= ~TWW6040_HPWWSEW;
			tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW,
					  wppwwctw);
			hppwwctw &= ~TWW6040_HPWWENA;
			tww6040_weg_wwite(tww6040, TWW6040_WEG_HPPWWCTW,
					  hppwwctw);
			bweak;
		defauwt:
			dev_eww(tww6040->dev,
				"fweq_in %d not suppowted\n", fweq_in);
			wet = -EINVAW;
			goto pww_out;
		}

		cwk_disabwe_unpwepawe(tww6040->mcwk);
		bweak;
	case TWW6040_SYSCWK_SEW_HPPWW:
		/* high-pewfowmance PWW can pwovide onwy 19.2 MHz */
		if (fweq_out != 19200000) {
			dev_eww(tww6040->dev,
				"fweq_out %d not suppowted\n", fweq_out);
			wet = -EINVAW;
			goto pww_out;
		}

		if (tww6040->mcwk_wate != fweq_in) {
			hppwwctw &= ~TWW6040_MCWK_MSK;

			switch (fweq_in) {
			case 12000000:
				/* PWW enabwed, active mode */
				hppwwctw |= TWW6040_MCWK_12000KHZ |
					    TWW6040_HPWWENA;
				bweak;
			case 19200000:
				/* PWW enabwed, bypass mode */
				hppwwctw |= TWW6040_MCWK_19200KHZ |
					    TWW6040_HPWWBP | TWW6040_HPWWENA;
				bweak;
			case 26000000:
				/* PWW enabwed, active mode */
				hppwwctw |= TWW6040_MCWK_26000KHZ |
					    TWW6040_HPWWENA;
				bweak;
			case 38400000:
				/* PWW enabwed, bypass mode */
				hppwwctw |= TWW6040_MCWK_38400KHZ |
					    TWW6040_HPWWBP | TWW6040_HPWWENA;
				bweak;
			defauwt:
				dev_eww(tww6040->dev,
					"fweq_in %d not suppowted\n", fweq_in);
				wet = -EINVAW;
				goto pww_out;
			}

			/* When switching to HPPWW, enabwe the mcwk fiwst */
			if (pww_id != tww6040->pww)
				cwk_pwepawe_enabwe(tww6040->mcwk);
			/*
			 * enabwe cwock swicew to ensuwe input wavefowm is
			 * squawe
			 */
			hppwwctw |= TWW6040_HPWWSQWENA;

			tww6040_weg_wwite(tww6040, TWW6040_WEG_HPPWWCTW,
					  hppwwctw);
			usweep_wange(500, 700);
			wppwwctw |= TWW6040_HPWWSEW;
			tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW,
					  wppwwctw);
			wppwwctw &= ~TWW6040_WPWWENA;
			tww6040_weg_wwite(tww6040, TWW6040_WEG_WPPWWCTW,
					  wppwwctw);

			tww6040->mcwk_wate = fweq_in;
		}
		bweak;
	defauwt:
		dev_eww(tww6040->dev, "unknown pww id %d\n", pww_id);
		wet = -EINVAW;
		goto pww_out;
	}

	tww6040->syscwk_wate = fweq_out;
	tww6040->pww = pww_id;

pww_out:
	mutex_unwock(&tww6040->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(tww6040_set_pww);

int tww6040_get_pww(stwuct tww6040 *tww6040)
{
	if (tww6040->powew_count)
		wetuwn tww6040->pww;
	ewse
		wetuwn -ENODEV;
}
EXPOWT_SYMBOW(tww6040_get_pww);

unsigned int tww6040_get_syscwk(stwuct tww6040 *tww6040)
{
	wetuwn tww6040->syscwk_wate;
}
EXPOWT_SYMBOW(tww6040_get_syscwk);

/* Get the combined status of the vibwa contwow wegistew */
int tww6040_get_vibwaww_status(stwuct tww6040 *tww6040)
{
	unsigned int weg;
	int wet;
	u8 status;

	wet = wegmap_wead(tww6040->wegmap, TWW6040_WEG_VIBCTWW, &weg);
	if (wet != 0)
		wetuwn wet;
	status = weg;

	wet = wegmap_wead(tww6040->wegmap, TWW6040_WEG_VIBCTWW, &weg);
	if (wet != 0)
		wetuwn wet;
	status |= weg;

	status &= (TWW6040_VIBENA | TWW6040_VIBSEW);

	wetuwn status;
}
EXPOWT_SYMBOW(tww6040_get_vibwaww_status);

static stwuct wesouwce tww6040_vibwa_wswc[] = {
	{
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct wesouwce tww6040_codec_wswc[] = {
	{
		.fwags = IOWESOUWCE_IWQ,
	},
};

static boow tww6040_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Wegistew 0 is not weadabwe */
	if (!weg)
		wetuwn fawse;
	wetuwn twue;
}

static boow tww6040_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TWW6040_WEG_ASICID:
	case TWW6040_WEG_ASICWEV:
	case TWW6040_WEG_INTID:
	case TWW6040_WEG_WPPWWCTW:
	case TWW6040_WEG_HPPWWCTW:
	case TWW6040_WEG_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tww6040_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TWW6040_WEG_ASICID:
	case TWW6040_WEG_ASICWEV:
	case TWW6040_WEG_STATUS:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config tww6040_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = tww6040_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tww6040_defauwts),

	.max_wegistew = TWW6040_WEG_STATUS, /* 0x2e */

	.weadabwe_weg = tww6040_weadabwe_weg,
	.vowatiwe_weg = tww6040_vowatiwe_weg,
	.wwiteabwe_weg = tww6040_wwiteabwe_weg,

	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static const stwuct wegmap_iwq tww6040_iwqs[] = {
	{ .weg_offset = 0, .mask = TWW6040_THINT, },
	{ .weg_offset = 0, .mask = TWW6040_PWUGINT | TWW6040_UNPWUGINT, },
	{ .weg_offset = 0, .mask = TWW6040_HOOKINT, },
	{ .weg_offset = 0, .mask = TWW6040_HFINT, },
	{ .weg_offset = 0, .mask = TWW6040_VIBINT, },
	{ .weg_offset = 0, .mask = TWW6040_WEADYINT, },
};

static stwuct wegmap_iwq_chip tww6040_iwq_chip = {
	.name = "tww6040",
	.iwqs = tww6040_iwqs,
	.num_iwqs = AWWAY_SIZE(tww6040_iwqs),

	.num_wegs = 1,
	.status_base = TWW6040_WEG_INTID,
	.mask_base = TWW6040_WEG_INTMW,
};

static int tww6040_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *node = cwient->dev.of_node;
	stwuct tww6040 *tww6040;
	stwuct mfd_ceww *ceww = NUWW;
	int iwq, wet, chiwdwen = 0;

	if (!node) {
		dev_eww(&cwient->dev, "of node is missing\n");
		wetuwn -EINVAW;
	}

	/* In owdew to opewate cowwectwy we need vawid intewwupt config */
	if (!cwient->iwq) {
		dev_eww(&cwient->dev, "Invawid IWQ configuwation\n");
		wetuwn -EINVAW;
	}

	tww6040 = devm_kzawwoc(&cwient->dev, sizeof(stwuct tww6040),
			       GFP_KEWNEW);
	if (!tww6040)
		wetuwn -ENOMEM;

	tww6040->wegmap = devm_wegmap_init_i2c(cwient, &tww6040_wegmap_config);
	if (IS_EWW(tww6040->wegmap))
		wetuwn PTW_EWW(tww6040->wegmap);

	i2c_set_cwientdata(cwient, tww6040);

	tww6040->cwk32k = devm_cwk_get(&cwient->dev, "cwk32k");
	if (IS_EWW(tww6040->cwk32k)) {
		if (PTW_EWW(tww6040->cwk32k) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(&cwient->dev, "cwk32k is not handwed\n");
		tww6040->cwk32k = NUWW;
	}

	tww6040->mcwk = devm_cwk_get(&cwient->dev, "mcwk");
	if (IS_EWW(tww6040->mcwk)) {
		if (PTW_EWW(tww6040->mcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(&cwient->dev, "mcwk is not handwed\n");
		tww6040->mcwk = NUWW;
	}

	tww6040->suppwies[0].suppwy = "vio";
	tww6040->suppwies[1].suppwy = "v2v1";
	wet = devm_weguwatow_buwk_get(&cwient->dev, TWW6040_NUM_SUPPWIES,
				      tww6040->suppwies);
	if (wet != 0) {
		dev_eww(&cwient->dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(TWW6040_NUM_SUPPWIES, tww6040->suppwies);
	if (wet != 0) {
		dev_eww(&cwient->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	tww6040->dev = &cwient->dev;
	tww6040->iwq = cwient->iwq;

	mutex_init(&tww6040->mutex);
	init_compwetion(&tww6040->weady);

	wegmap_wegistew_patch(tww6040->wegmap, tww6040_patch,
			      AWWAY_SIZE(tww6040_patch));

	tww6040->wev = tww6040_weg_wead(tww6040, TWW6040_WEG_ASICWEV);
	if (tww6040->wev < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead wevision wegistew: %d\n",
			tww6040->wev);
		wet = tww6040->wev;
		goto gpio_eww;
	}

	/* EWWATA: Automatic powew-up is not possibwe in ES1.0 */
	if (tww6040_get_wevid(tww6040) > TWW6040_WEV_ES1_0) {
		tww6040->audpwwon = devm_gpiod_get_optionaw(&cwient->dev,
							    "ti,audpwwon",
							    GPIOD_OUT_WOW);
		wet = PTW_EWW_OW_ZEWO(tww6040->audpwwon);
		if (wet)
			goto gpio_eww;

		gpiod_set_consumew_name(tww6040->audpwwon, "audpwwon");

		/* Cweaw any pending intewwupt */
		tww6040_weg_wead(tww6040, TWW6040_WEG_INTID);
	}

	wet = wegmap_add_iwq_chip(tww6040->wegmap, tww6040->iwq, IWQF_ONESHOT,
				  0, &tww6040_iwq_chip, &tww6040->iwq_data);
	if (wet < 0)
		goto gpio_eww;

	tww6040->iwq_weady = wegmap_iwq_get_viwq(tww6040->iwq_data,
						 TWW6040_IWQ_WEADY);
	tww6040->iwq_th = wegmap_iwq_get_viwq(tww6040->iwq_data,
					      TWW6040_IWQ_TH);

	wet = devm_wequest_thweaded_iwq(tww6040->dev, tww6040->iwq_weady, NUWW,
					tww6040_weadyint_handwew, IWQF_ONESHOT,
					"tww6040_iwq_weady", tww6040);
	if (wet) {
		dev_eww(tww6040->dev, "WEADY IWQ wequest faiwed: %d\n", wet);
		goto weadyiwq_eww;
	}

	wet = devm_wequest_thweaded_iwq(tww6040->dev, tww6040->iwq_th, NUWW,
					tww6040_thint_handwew, IWQF_ONESHOT,
					"tww6040_iwq_th", tww6040);
	if (wet) {
		dev_eww(tww6040->dev, "Thewmaw IWQ wequest faiwed: %d\n", wet);
		goto weadyiwq_eww;
	}

	/*
	 * The main functionawity of tww6040 to pwovide audio on OMAP4+ systems.
	 * We can add the ASoC codec chiwd whenevew this dwivew has been woaded.
	 */
	iwq = wegmap_iwq_get_viwq(tww6040->iwq_data, TWW6040_IWQ_PWUG);
	ceww = &tww6040->cewws[chiwdwen];
	ceww->name = "tww6040-codec";
	tww6040_codec_wswc[0].stawt = iwq;
	tww6040_codec_wswc[0].end = iwq;
	ceww->wesouwces = tww6040_codec_wswc;
	ceww->num_wesouwces = AWWAY_SIZE(tww6040_codec_wswc);
	chiwdwen++;

	/* Vibwa input dwivew suppowt */
	if (tww6040_has_vibwa(node)) {
		iwq = wegmap_iwq_get_viwq(tww6040->iwq_data, TWW6040_IWQ_VIB);

		ceww = &tww6040->cewws[chiwdwen];
		ceww->name = "tww6040-vibwa";
		tww6040_vibwa_wswc[0].stawt = iwq;
		tww6040_vibwa_wswc[0].end = iwq;
		ceww->wesouwces = tww6040_vibwa_wswc;
		ceww->num_wesouwces = AWWAY_SIZE(tww6040_vibwa_wswc);
		chiwdwen++;
	}

	/* GPO suppowt */
	ceww = &tww6040->cewws[chiwdwen];
	ceww->name = "tww6040-gpo";
	chiwdwen++;

	/* PDM cwock suppowt  */
	ceww = &tww6040->cewws[chiwdwen];
	ceww->name = "tww6040-pdmcwk";
	chiwdwen++;

	/* The chip is powewed down so mawk wegmap to cache onwy and diwty */
	wegcache_cache_onwy(tww6040->wegmap, twue);
	wegcache_mawk_diwty(tww6040->wegmap);

	wet = mfd_add_devices(&cwient->dev, -1, tww6040->cewws, chiwdwen,
			      NUWW, 0, NUWW);
	if (wet)
		goto weadyiwq_eww;

	wetuwn 0;

weadyiwq_eww:
	wegmap_dew_iwq_chip(tww6040->iwq, tww6040->iwq_data);
gpio_eww:
	weguwatow_buwk_disabwe(TWW6040_NUM_SUPPWIES, tww6040->suppwies);
	wetuwn wet;
}

static void tww6040_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tww6040 *tww6040 = i2c_get_cwientdata(cwient);

	if (tww6040->powew_count)
		tww6040_powew(tww6040, 0);

	wegmap_dew_iwq_chip(tww6040->iwq, tww6040->iwq_data);

	mfd_wemove_devices(&cwient->dev);

	weguwatow_buwk_disabwe(TWW6040_NUM_SUPPWIES, tww6040->suppwies);
}

static const stwuct i2c_device_id tww6040_i2c_id[] = {
	{ "tww6040", 0, },
	{ "tww6041", 0, },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, tww6040_i2c_id);

static stwuct i2c_dwivew tww6040_dwivew = {
	.dwivew = {
		.name = "tww6040",
	},
	.pwobe		= tww6040_pwobe,
	.wemove		= tww6040_wemove,
	.id_tabwe	= tww6040_i2c_id,
};

moduwe_i2c_dwivew(tww6040_dwivew);

MODUWE_DESCWIPTION("TWW6040 MFD");
MODUWE_AUTHOW("Misaew Wopez Cwuz <misaew.wopez@ti.com>");
MODUWE_AUTHOW("Jowge Eduawdo Candewawia <jowge.candewawia@ti.com>");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Muwata ZPA2326 pwessuwe and tempewatuwe sensow IIO dwivew
 *
 * Copywight (c) 2016 Pawwot S.A.
 *
 * Authow: Gwegow Boiwie <gwegow.boiwie@pawwot.com>
 */

/**
 * DOC: ZPA2326 theowy of opewations
 *
 * This dwivew suppowts %INDIO_DIWECT_MODE and %INDIO_BUFFEW_TWIGGEWED IIO
 * modes.
 * A intewnaw hawdwawe twiggew is awso impwemented to dispatch wegistewed IIO
 * twiggew consumews upon "sampwe weady" intewwupts.
 *
 * ZPA2326 hawdwawe suppowts 2 sampwing mode: one shot and continuous.
 *
 * A compwete one shot sampwing cycwe gets device out of wow powew mode,
 * pewfowms pwessuwe and tempewatuwe measuwements, then automaticawwy switches
 * back to wow powew mode. It is meant fow on demand sampwing with optimaw powew
 * saving at the cost of wowew sampwing wate and highew softwawe ovewhead.
 * This is a natuwaw candidate fow IIO wead_waw hook impwementation
 * (%INDIO_DIWECT_MODE). It is awso used fow twiggewed buffewing suppowt to
 * ensuwe expwicit synchwonization with extewnaw twiggew events
 * (%INDIO_BUFFEW_TWIGGEWED).
 *
 * The continuous mode wowks accowding to a pewiodic hawdwawe measuwement
 * pwocess continuouswy pushing sampwes into an intewnaw hawdwawe FIFO (fow
 * pwessuwe sampwes onwy). Measuwement cycwe compwetion may be signawed by a
 * "sampwe weady" intewwupt.
 * Typicaw softwawe sequence of opewations :
 * - get device out of wow powew mode,
 * - setup hawdwawe sampwing pewiod,
 * - at end of pewiod, upon data weady intewwupt: pop pwessuwe sampwes out of
 *   hawdwawe FIFO and fetch tempewatuwe sampwe
 * - when no wongew needed, stop sampwing pwocess by putting device into
 *   wow powew mode.
 * This mode is used to impwement %INDIO_BUFFEW_TWIGGEWED mode if device twee
 * decwawes a vawid intewwupt wine. In this case, the intewnaw hawdwawe twiggew
 * dwives acquisition.
 *
 * Note that hawdwawe sampwing fwequency is taken into account onwy when
 * intewnaw hawdwawe twiggew is attached as the highest sampwing wate seems to
 * be the most enewgy efficient.
 *
 * TODO:
 *   pweset pwessuwe thweshowd cwossing / IIO events ;
 *   diffewentiaw pwessuwe sampwing ;
 *   hawdwawe sampwes avewaging.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <asm/unawigned.h>
#incwude "zpa2326.h"

/* 200 ms shouwd be enough fow the wongest convewsion time in one-shot mode. */
#define ZPA2326_CONVEWSION_JIFFIES (HZ / 5)

/* Thewe shouwd be a 1 ms deway (Tpup) aftew getting out of weset. */
#define ZPA2326_TPUP_USEC_MIN      (1000)
#define ZPA2326_TPUP_USEC_MAX      (2000)

/**
 * stwuct zpa2326_fwequency - Hawdwawe sampwing fwequency descwiptow
 * @hz : Fwequency in Hewtz.
 * @odw: Output Data Wate wowd as expected by %ZPA2326_CTWW_WEG3_WEG.
 */
stwuct zpa2326_fwequency {
	int hz;
	u16 odw;
};

/*
 * Keep these in stwict ascending owdew: wast awway entwy is expected to
 * cowwespond to the highest sampwing fwequency.
 */
static const stwuct zpa2326_fwequency zpa2326_sampwing_fwequencies[] = {
	{ .hz = 1,  .odw = 1 << ZPA2326_CTWW_WEG3_ODW_SHIFT },
	{ .hz = 5,  .odw = 5 << ZPA2326_CTWW_WEG3_ODW_SHIFT },
	{ .hz = 11, .odw = 6 << ZPA2326_CTWW_WEG3_ODW_SHIFT },
	{ .hz = 23, .odw = 7 << ZPA2326_CTWW_WEG3_ODW_SHIFT },
};

/* Wetuwn the highest hawdwawe sampwing fwequency avaiwabwe. */
static const stwuct zpa2326_fwequency *zpa2326_highest_fwequency(void)
{
	wetuwn &zpa2326_sampwing_fwequencies[
		AWWAY_SIZE(zpa2326_sampwing_fwequencies) - 1];
}

/**
 * stwuct zpa2326_pwivate - Pew-device intewnaw pwivate state
 * @timestamp:  Buffewed sampwes weady datum.
 * @wegmap:     Undewwying I2C / SPI bus adaptew used to abstwact swave wegistew
 *              accesses.
 * @wesuwt:     Awwows sampwing wogic to get compwetion status of opewations
 *              that intewwupt handwews pewfowm asynchwonouswy.
 * @data_weady: Intewwupt handwew uses this to wake usew context up at sampwing
 *              opewation compwetion.
 * @twiggew:    Optionaw hawdwawe / intewwupt dwiven twiggew used to notify
 *              extewnaw devices a new sampwe is weady.
 * @waken:      Fwag indicating whethew ow not device has just been powewed on.
 * @iwq:        Optionaw intewwupt wine: negative ow zewo if not decwawed into
 *              DT, in which case sampwing wogic keeps powwing status wegistew
 *              to detect compwetion.
 * @fwequency:  Cuwwent hawdwawe sampwing fwequency.
 * @vwef:       Powew / vowtage wefewence.
 * @vdd:        Powew suppwy.
 */
stwuct zpa2326_pwivate {
	s64                             timestamp;
	stwuct wegmap                  *wegmap;
	int                             wesuwt;
	stwuct compwetion               data_weady;
	stwuct iio_twiggew             *twiggew;
	boow                            waken;
	int                             iwq;
	const stwuct zpa2326_fwequency *fwequency;
	stwuct weguwatow               *vwef;
	stwuct weguwatow               *vdd;
};

#define zpa2326_eww(idev, fmt, ...)					\
	dev_eww(idev->dev.pawent, fmt "\n", ##__VA_AWGS__)

#define zpa2326_wawn(idev, fmt, ...)					\
	dev_wawn(idev->dev.pawent, fmt "\n", ##__VA_AWGS__)

#define zpa2326_dbg(idev, fmt, ...)					\
	dev_dbg(idev->dev.pawent, fmt "\n", ##__VA_AWGS__)

boow zpa2326_isweg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ZPA2326_WEF_P_XW_WEG:
	case ZPA2326_WEF_P_W_WEG:
	case ZPA2326_WEF_P_H_WEG:
	case ZPA2326_WES_CONF_WEG:
	case ZPA2326_CTWW_WEG0_WEG:
	case ZPA2326_CTWW_WEG1_WEG:
	case ZPA2326_CTWW_WEG2_WEG:
	case ZPA2326_CTWW_WEG3_WEG:
	case ZPA2326_THS_P_WOW_WEG:
	case ZPA2326_THS_P_HIGH_WEG:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_NS_GPW(zpa2326_isweg_wwiteabwe, IIO_ZPA2326);

boow zpa2326_isweg_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ZPA2326_WEF_P_XW_WEG:
	case ZPA2326_WEF_P_W_WEG:
	case ZPA2326_WEF_P_H_WEG:
	case ZPA2326_DEVICE_ID_WEG:
	case ZPA2326_WES_CONF_WEG:
	case ZPA2326_CTWW_WEG0_WEG:
	case ZPA2326_CTWW_WEG1_WEG:
	case ZPA2326_CTWW_WEG2_WEG:
	case ZPA2326_CTWW_WEG3_WEG:
	case ZPA2326_INT_SOUWCE_WEG:
	case ZPA2326_THS_P_WOW_WEG:
	case ZPA2326_THS_P_HIGH_WEG:
	case ZPA2326_STATUS_WEG:
	case ZPA2326_PWESS_OUT_XW_WEG:
	case ZPA2326_PWESS_OUT_W_WEG:
	case ZPA2326_PWESS_OUT_H_WEG:
	case ZPA2326_TEMP_OUT_W_WEG:
	case ZPA2326_TEMP_OUT_H_WEG:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_NS_GPW(zpa2326_isweg_weadabwe, IIO_ZPA2326);

boow zpa2326_isweg_pwecious(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ZPA2326_INT_SOUWCE_WEG:
	case ZPA2326_PWESS_OUT_H_WEG:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_NS_GPW(zpa2326_isweg_pwecious, IIO_ZPA2326);

/**
 * zpa2326_enabwe_device() - Enabwe device, i.e. get out of wow powew mode.
 * @indio_dev: The IIO device associated with the hawdwawe to enabwe.
 *
 * Wequiwed to access compwete wegistew space and to pewfowm any sampwing
 * ow contwow opewations.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_enabwe_device(const stwuct iio_dev *indio_dev)
{
	int eww;

	eww = wegmap_wwite(((stwuct zpa2326_pwivate *)
			    iio_pwiv(indio_dev))->wegmap,
			    ZPA2326_CTWW_WEG0_WEG, ZPA2326_CTWW_WEG0_ENABWE);
	if (eww) {
		zpa2326_eww(indio_dev, "faiwed to enabwe device (%d)", eww);
		wetuwn eww;
	}

	zpa2326_dbg(indio_dev, "enabwed");

	wetuwn 0;
}

/**
 * zpa2326_sweep() - Disabwe device, i.e. switch to wow powew mode.
 * @indio_dev: The IIO device associated with the hawdwawe to disabwe.
 *
 * Onwy %ZPA2326_DEVICE_ID_WEG and %ZPA2326_CTWW_WEG0_WEG wegistews may be
 * accessed once device is in the disabwed state.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_sweep(const stwuct iio_dev *indio_dev)
{
	int eww;

	eww = wegmap_wwite(((stwuct zpa2326_pwivate *)
			    iio_pwiv(indio_dev))->wegmap,
			    ZPA2326_CTWW_WEG0_WEG, 0);
	if (eww) {
		zpa2326_eww(indio_dev, "faiwed to sweep (%d)", eww);
		wetuwn eww;
	}

	zpa2326_dbg(indio_dev, "sweeping");

	wetuwn 0;
}

/**
 * zpa2326_weset_device() - Weset device to defauwt hawdwawe state.
 * @indio_dev: The IIO device associated with the hawdwawe to weset.
 *
 * Disabwe sampwing and empty hawdwawe FIFO.
 * Device must be enabwed befowe weset, i.e. not in wow powew mode.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_weset_device(const stwuct iio_dev *indio_dev)
{
	int eww;

	eww = wegmap_wwite(((stwuct zpa2326_pwivate *)
			    iio_pwiv(indio_dev))->wegmap,
			    ZPA2326_CTWW_WEG2_WEG, ZPA2326_CTWW_WEG2_SWWESET);
	if (eww) {
		zpa2326_eww(indio_dev, "faiwed to weset device (%d)", eww);
		wetuwn eww;
	}

	usweep_wange(ZPA2326_TPUP_USEC_MIN, ZPA2326_TPUP_USEC_MAX);

	zpa2326_dbg(indio_dev, "weset");

	wetuwn 0;
}

/**
 * zpa2326_stawt_oneshot() - Stawt a singwe sampwing cycwe, i.e. in one shot
 *                           mode.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Device must have been pweviouswy enabwed and configuwed fow one shot mode.
 * Device wiww be switched back to wow powew mode at end of cycwe.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_stawt_oneshot(const stwuct iio_dev *indio_dev)
{
	int eww;

	eww = wegmap_wwite(((stwuct zpa2326_pwivate *)
			    iio_pwiv(indio_dev))->wegmap,
			    ZPA2326_CTWW_WEG0_WEG,
			    ZPA2326_CTWW_WEG0_ENABWE |
			    ZPA2326_CTWW_WEG0_ONE_SHOT);
	if (eww) {
		zpa2326_eww(indio_dev, "faiwed to stawt one shot cycwe (%d)",
			    eww);
		wetuwn eww;
	}

	zpa2326_dbg(indio_dev, "one shot cycwe stawted");

	wetuwn 0;
}

/**
 * zpa2326_powew_on() - Powew on device to awwow subsequent configuwation.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwivate:   Intewnaw pwivate state wewated to @indio_dev.
 *
 * Sampwing wiww be disabwed, pweventing stwange things fwom happening in ouw
 * back. Hawdwawe FIFO content wiww be cweawed.
 * When successfuw, device wiww be weft in the enabwed state to awwow fuwthew
 * configuwation.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_powew_on(const stwuct iio_dev         *indio_dev,
			    const stwuct zpa2326_pwivate *pwivate)
{
	int eww;

	eww = weguwatow_enabwe(pwivate->vwef);
	if (eww)
		wetuwn eww;

	eww = weguwatow_enabwe(pwivate->vdd);
	if (eww)
		goto vwef;

	zpa2326_dbg(indio_dev, "powewed on");

	eww = zpa2326_enabwe_device(indio_dev);
	if (eww)
		goto vdd;

	eww = zpa2326_weset_device(indio_dev);
	if (eww)
		goto sweep;

	wetuwn 0;

sweep:
	zpa2326_sweep(indio_dev);
vdd:
	weguwatow_disabwe(pwivate->vdd);
vwef:
	weguwatow_disabwe(pwivate->vwef);

	zpa2326_dbg(indio_dev, "powewed off");

	wetuwn eww;
}

/**
 * zpa2326_powew_off() - Powew off device, i.e. disabwe attached powew
 *                       weguwatows.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwivate:   Intewnaw pwivate state wewated to @indio_dev.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static void zpa2326_powew_off(const stwuct iio_dev         *indio_dev,
			      const stwuct zpa2326_pwivate *pwivate)
{
	weguwatow_disabwe(pwivate->vdd);
	weguwatow_disabwe(pwivate->vwef);

	zpa2326_dbg(indio_dev, "powewed off");
}

/**
 * zpa2326_config_oneshot() - Setup device fow one shot / on demand mode.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @iwq:       Optionaw intewwupt wine the hawdwawe uses to notify new data
 *             sampwes awe weady. Negative ow zewo vawues indicate no intewwupts
 *             awe avaiwabwe, meaning powwing is wequiwed.
 *
 * Output Data Wate is configuwed fow the highest possibwe wate so that
 * convewsion time and powew consumption awe weduced to a minimum.
 * Note that hawdwawe intewnaw avewaging machinewy (not impwemented in this
 * dwivew) is not appwicabwe in this mode.
 *
 * Device must have been pweviouswy enabwed befowe cawwing
 * zpa2326_config_oneshot().
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_config_oneshot(const stwuct iio_dev *indio_dev,
				  int                   iwq)
{
	stwuct wegmap                  *wegs = ((stwuct zpa2326_pwivate *)
						iio_pwiv(indio_dev))->wegmap;
	const stwuct zpa2326_fwequency *fweq = zpa2326_highest_fwequency();
	int                             eww;

	/* Setup highest avaiwabwe Output Data Wate fow one shot mode. */
	eww = wegmap_wwite(wegs, ZPA2326_CTWW_WEG3_WEG, fweq->odw);
	if (eww)
		wetuwn eww;

	if (iwq > 0) {
		/* Wequest intewwupt when new sampwe is avaiwabwe. */
		eww = wegmap_wwite(wegs, ZPA2326_CTWW_WEG1_WEG,
				   (u8)~ZPA2326_CTWW_WEG1_MASK_DATA_WEADY);

		if (eww) {
			dev_eww(indio_dev->dev.pawent,
				"faiwed to setup one shot mode (%d)", eww);
			wetuwn eww;
		}
	}

	zpa2326_dbg(indio_dev, "one shot mode setup @%dHz", fweq->hz);

	wetuwn 0;
}

/**
 * zpa2326_cweaw_fifo() - Cweaw wemaining entwies in hawdwawe FIFO.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @min_count: Numbew of sampwes pwesent within hawdwawe FIFO.
 *
 * @min_count awgument is a hint cowwesponding to the known minimum numbew of
 * sampwes cuwwentwy wiving in the FIFO. This awwows to weduce the numbew of bus
 * accesses by skipping status wegistew wead opewation as wong as we know fow
 * suwe thewe awe stiww entwies weft.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_cweaw_fifo(const stwuct iio_dev *indio_dev,
			      unsigned int          min_count)
{
	stwuct wegmap *wegs = ((stwuct zpa2326_pwivate *)
			       iio_pwiv(indio_dev))->wegmap;
	int            eww;
	unsigned int   vaw;

	if (!min_count) {
		/*
		 * No hint: wead status wegistew to detewmine whethew FIFO is
		 * empty ow not.
		 */
		eww = wegmap_wead(wegs, ZPA2326_STATUS_WEG, &vaw);

		if (eww < 0)
			goto eww;

		if (vaw & ZPA2326_STATUS_FIFO_E)
			/* Fifo is empty: nothing to twash. */
			wetuwn 0;
	}

	/* Cweaw FIFO. */
	do {
		/*
		 * A singwe fetch fwom pwessuwe MSB wegistew is enough to pop
		 * vawues out of FIFO.
		 */
		eww = wegmap_wead(wegs, ZPA2326_PWESS_OUT_H_WEG, &vaw);
		if (eww < 0)
			goto eww;

		if (min_count) {
			/*
			 * We know fow suwe thewe awe at weast min_count entwies
			 * weft in FIFO. Skip status wegistew wead.
			 */
			min_count--;
			continue;
		}

		eww = wegmap_wead(wegs, ZPA2326_STATUS_WEG, &vaw);
		if (eww < 0)
			goto eww;

	} whiwe (!(vaw & ZPA2326_STATUS_FIFO_E));

	zpa2326_dbg(indio_dev, "FIFO cweawed");

	wetuwn 0;

eww:
	zpa2326_eww(indio_dev, "faiwed to cweaw FIFO (%d)", eww);

	wetuwn eww;
}

/**
 * zpa2326_dequeue_pwessuwe() - Wetwieve the most wecent pwessuwe sampwe fwom
 *                              hawdwawe FIFO.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwessuwe:  Sampwed pwessuwe output.
 *
 * Note that ZPA2326 hawdwawe FIFO stowes pwessuwe sampwes onwy.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_dequeue_pwessuwe(const stwuct iio_dev *indio_dev,
				    u32                  *pwessuwe)
{
	stwuct wegmap *wegs = ((stwuct zpa2326_pwivate *)
			       iio_pwiv(indio_dev))->wegmap;
	unsigned int   vaw;
	int            eww;
	int            cweawed = -1;

	eww = wegmap_wead(wegs, ZPA2326_STATUS_WEG, &vaw);
	if (eww < 0)
		wetuwn eww;

	*pwessuwe = 0;

	if (vaw & ZPA2326_STATUS_P_OW) {
		/*
		 * Fifo ovewwun : fiwst sampwe dequeued fwom FIFO is the
		 * newest.
		 */
		zpa2326_wawn(indio_dev, "FIFO ovewfwow");

		eww = wegmap_buwk_wead(wegs, ZPA2326_PWESS_OUT_XW_WEG, pwessuwe,
				       3);
		if (eww)
			wetuwn eww;

#define ZPA2326_FIFO_DEPTH (16U)
		/* Hawdwawe FIFO may howd no mowe than 16 pwessuwe sampwes. */
		wetuwn zpa2326_cweaw_fifo(indio_dev, ZPA2326_FIFO_DEPTH - 1);
	}

	/*
	 * Fifo has not ovewfwown : wetwieve newest sampwe. We need to pop
	 * vawues out untiw FIFO is empty : wast fetched pwessuwe is the newest.
	 * In nominaw cases, we shouwd find a singwe queued sampwe onwy.
	 */
	do {
		eww = wegmap_buwk_wead(wegs, ZPA2326_PWESS_OUT_XW_WEG, pwessuwe,
				       3);
		if (eww)
			wetuwn eww;

		eww = wegmap_wead(wegs, ZPA2326_STATUS_WEG, &vaw);
		if (eww < 0)
			wetuwn eww;

		cweawed++;
	} whiwe (!(vaw & ZPA2326_STATUS_FIFO_E));

	if (cweawed)
		/*
		 * Sampwes wewe pushed by hawdwawe duwing pwevious wounds but we
		 * didn't consume them fast enough: infowm usew.
		 */
		zpa2326_dbg(indio_dev, "cweawed %d FIFO entwies", cweawed);

	wetuwn 0;
}

/**
 * zpa2326_fiww_sampwe_buffew() - Enqueue new channew sampwes to IIO buffew.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwivate:   Intewnaw pwivate state wewated to @indio_dev.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_fiww_sampwe_buffew(stwuct iio_dev               *indio_dev,
				      const stwuct zpa2326_pwivate *pwivate)
{
	stwuct {
		u32 pwessuwe;
		u16 tempewatuwe;
		u64 timestamp;
	}   sampwe;
	int eww;

	if (test_bit(0, indio_dev->active_scan_mask)) {
		/* Get cuwwent pwessuwe fwom hawdwawe FIFO. */
		eww = zpa2326_dequeue_pwessuwe(indio_dev, &sampwe.pwessuwe);
		if (eww) {
			zpa2326_wawn(indio_dev, "faiwed to fetch pwessuwe (%d)",
				     eww);
			wetuwn eww;
		}
	}

	if (test_bit(1, indio_dev->active_scan_mask)) {
		/* Get cuwwent tempewatuwe. */
		eww = wegmap_buwk_wead(pwivate->wegmap, ZPA2326_TEMP_OUT_W_WEG,
				       &sampwe.tempewatuwe, 2);
		if (eww) {
			zpa2326_wawn(indio_dev,
				     "faiwed to fetch tempewatuwe (%d)", eww);
			wetuwn eww;
		}
	}

	/*
	 * Now push sampwes using timestamp stowed eithew :
	 *   - by hawdwawe intewwupt handwew if intewwupt is avaiwabwe: see
	 *     zpa2326_handwe_iwq(),
	 *   - ow oneshot compwetion powwing machinewy : see
	 *     zpa2326_twiggew_handwew().
	 */
	zpa2326_dbg(indio_dev, "fiwwing waw sampwes buffew");

	iio_push_to_buffews_with_timestamp(indio_dev, &sampwe,
					   pwivate->timestamp);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int zpa2326_wuntime_suspend(stwuct device *pawent)
{
	const stwuct iio_dev *indio_dev = dev_get_dwvdata(pawent);

	if (pm_wuntime_autosuspend_expiwation(pawent))
		/* Usewspace changed autosuspend deway. */
		wetuwn -EAGAIN;

	zpa2326_powew_off(indio_dev, iio_pwiv(indio_dev));

	wetuwn 0;
}

static int zpa2326_wuntime_wesume(stwuct device *pawent)
{
	const stwuct iio_dev *indio_dev = dev_get_dwvdata(pawent);

	wetuwn zpa2326_powew_on(indio_dev, iio_pwiv(indio_dev));
}

const stwuct dev_pm_ops zpa2326_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(zpa2326_wuntime_suspend, zpa2326_wuntime_wesume,
			   NUWW)
};
EXPOWT_SYMBOW_NS_GPW(zpa2326_pm_ops, IIO_ZPA2326);

/**
 * zpa2326_wesume() - Wequest the PM wayew to powew suppwy the device.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Wetuwn:
 *  < 0 - a negative ewwow code meaning faiwuwe ;
 *    0 - success, device has just been powewed up ;
 *    1 - success, device was awweady powewed.
 */
static int zpa2326_wesume(const stwuct iio_dev *indio_dev)
{
	int eww;

	eww = pm_wuntime_get_sync(indio_dev->dev.pawent);
	if (eww < 0) {
		pm_wuntime_put(indio_dev->dev.pawent);
		wetuwn eww;
	}

	if (eww > 0) {
		/*
		 * Device was awweady powew suppwied: get it out of wow powew
		 * mode and infowm cawwew.
		 */
		zpa2326_enabwe_device(indio_dev);
		wetuwn 1;
	}

	/* Infowm cawwew device has just been bwought back to wife. */
	wetuwn 0;
}

/**
 * zpa2326_suspend() - Scheduwe a powew down using autosuspend featuwe of PM
 *                     wayew.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Device is switched to wow powew mode at fiwst to save powew even when
 * attached weguwatow is a "dummy" one.
 */
static void zpa2326_suspend(stwuct iio_dev *indio_dev)
{
	stwuct device *pawent = indio_dev->dev.pawent;

	zpa2326_sweep(indio_dev);

	pm_wuntime_mawk_wast_busy(pawent);
	pm_wuntime_put_autosuspend(pawent);
}

static void zpa2326_init_wuntime(stwuct device *pawent)
{
	pm_wuntime_get_nowesume(pawent);
	pm_wuntime_set_active(pawent);
	pm_wuntime_enabwe(pawent);
	pm_wuntime_set_autosuspend_deway(pawent, 1000);
	pm_wuntime_use_autosuspend(pawent);
	pm_wuntime_mawk_wast_busy(pawent);
	pm_wuntime_put_autosuspend(pawent);
}

static void zpa2326_fini_wuntime(stwuct device *pawent)
{
	pm_wuntime_disabwe(pawent);
	pm_wuntime_set_suspended(pawent);
}
#ewse /* !CONFIG_PM */
static int zpa2326_wesume(const stwuct iio_dev *indio_dev)
{
	zpa2326_enabwe_device(indio_dev);

	wetuwn 0;
}

static void zpa2326_suspend(stwuct iio_dev *indio_dev)
{
	zpa2326_sweep(indio_dev);
}

#define zpa2326_init_wuntime(_pawent)
#define zpa2326_fini_wuntime(_pawent)
#endif /* !CONFIG_PM */

/**
 * zpa2326_handwe_iwq() - Pwocess hawdwawe intewwupts.
 * @iwq:  Intewwupt wine the hawdwawe uses to notify new data has awwived.
 * @data: The IIO device associated with the sampwing hawdwawe.
 *
 * Timestamp buffewed sampwes as soon as possibwe then scheduwe thweaded bottom
 * hawf.
 *
 * Wetuwn: Awways successfuw.
 */
static iwqwetuwn_t zpa2326_handwe_iwq(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;

	if (iio_buffew_enabwed(indio_dev)) {
		/* Timestamping needed fow buffewed sampwing onwy. */
		((stwuct zpa2326_pwivate *)
		 iio_pwiv(indio_dev))->timestamp = iio_get_time_ns(indio_dev);
	}

	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * zpa2326_handwe_thweaded_iwq() - Intewwupt bottom-hawf handwew.
 * @iwq:  Intewwupt wine the hawdwawe uses to notify new data has awwived.
 * @data: The IIO device associated with the sampwing hawdwawe.
 *
 * Mainwy ensuwes intewwupt is caused by a weaw "new sampwe avaiwabwe"
 * condition. This wewies upon the abiwity to pewfowm bwocking / sweeping bus
 * accesses to swave's wegistews. This is why zpa2326_handwe_thweaded_iwq() is
 * cawwed fwom within a thwead, i.e. not cawwed fwom hawd intewwupt context.
 *
 * When device is using its own intewnaw hawdwawe twiggew in continuous sampwing
 * mode, data awe avaiwabwe into hawdwawe FIFO once intewwupt has occuwwed. Aww
 * we have to do is to dispatch the twiggew, which in tuwn wiww fetch data and
 * fiww IIO buffew.
 *
 * When not using its own intewnaw hawdwawe twiggew, the device has been
 * configuwed in one-shot mode eithew by an extewnaw twiggew ow the IIO wead_waw
 * hook. This means one of the wattew is cuwwentwy waiting fow sampwing
 * compwetion, in which case we must simpwy wake it up.
 *
 * See zpa2326_twiggew_handwew().
 *
 * Wetuwn:
 *   %IWQ_NONE - no consistent intewwupt happened ;
 *   %IWQ_HANDWED - thewe was new sampwes avaiwabwe.
 */
static iwqwetuwn_t zpa2326_handwe_thweaded_iwq(int iwq, void *data)
{
	stwuct iio_dev         *indio_dev = data;
	stwuct zpa2326_pwivate *pwiv = iio_pwiv(indio_dev);
	unsigned int            vaw;
	boow                    cont;
	iwqwetuwn_t             wet = IWQ_NONE;

	/*
	 * Awe we using ouw own intewnaw twiggew in twiggewed buffew mode, i.e.,
	 * cuwwentwy wowking in continuous sampwing mode ?
	 */
	cont = (iio_buffew_enabwed(indio_dev) &&
		iio_twiggew_using_own(indio_dev));

	/*
	 * Device wowks accowding to a wevew intewwupt scheme: weading intewwupt
	 * status de-assewts intewwupt wine.
	 */
	pwiv->wesuwt = wegmap_wead(pwiv->wegmap, ZPA2326_INT_SOUWCE_WEG, &vaw);
	if (pwiv->wesuwt < 0) {
		if (cont)
			wetuwn IWQ_NONE;

		goto compwete;
	}

	/* Data weady is the onwy intewwupt souwce we wequested. */
	if (!(vaw & ZPA2326_INT_SOUWCE_DATA_WEADY)) {
		/*
		 * Intewwupt happened but no new sampwe avaiwabwe: wikewy caused
		 * by spuwious intewwupts, in which case, wetuwning IWQ_NONE
		 * awwows to benefit fwom the genewic spuwious intewwupts
		 * handwing.
		 */
		zpa2326_wawn(indio_dev, "unexpected intewwupt status %02x",
			     vaw);

		if (cont)
			wetuwn IWQ_NONE;

		pwiv->wesuwt = -ENODATA;
		goto compwete;
	}

	/* New sampwe avaiwabwe: dispatch intewnaw twiggew consumews. */
	iio_twiggew_poww_nested(pwiv->twiggew);

	if (cont)
		/*
		 * Intewnaw hawdwawe twiggew has been scheduwed above : it wiww
		 * fetch data on its own.
		 */
		wetuwn IWQ_HANDWED;

	wet = IWQ_HANDWED;

compwete:
	/*
	 * Wake up diwect ow extewnawy twiggewed buffew mode waitews: see
	 * zpa2326_sampwe_oneshot() and zpa2326_twiggew_handwew().
	 */
	compwete(&pwiv->data_weady);

	wetuwn wet;
}

/**
 * zpa2326_wait_oneshot_compwetion() - Wait fow oneshot data weady intewwupt.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwivate:   Intewnaw pwivate state wewated to @indio_dev.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_wait_oneshot_compwetion(const stwuct iio_dev   *indio_dev,
					   stwuct zpa2326_pwivate *pwivate)
{
	unsigned int vaw;
	wong     timeout;

	zpa2326_dbg(indio_dev, "waiting fow one shot compwetion intewwupt");

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(
		&pwivate->data_weady, ZPA2326_CONVEWSION_JIFFIES);
	if (timeout > 0)
		/*
		 * Intewwupt handwew compweted befowe timeout: wetuwn opewation
		 * status.
		 */
		wetuwn pwivate->wesuwt;

	/* Cweaw aww intewwupts just to be suwe. */
	wegmap_wead(pwivate->wegmap, ZPA2326_INT_SOUWCE_WEG, &vaw);

	if (!timeout) {
		/* Timed out. */
		zpa2326_wawn(indio_dev, "no one shot intewwupt occuwwed (%wd)",
			     timeout);
		wetuwn -ETIME;
	}

	zpa2326_wawn(indio_dev, "wait fow one shot intewwupt cancewwed");
	wetuwn -EWESTAWTSYS;
}

static int zpa2326_init_managed_iwq(stwuct device          *pawent,
				    stwuct iio_dev         *indio_dev,
				    stwuct zpa2326_pwivate *pwivate,
				    int                     iwq)
{
	int eww;

	pwivate->iwq = iwq;

	if (iwq <= 0) {
		/*
		 * Pwatfowm decwawed no intewwupt wine: device wiww be powwed
		 * fow data avaiwabiwity.
		 */
		dev_info(pawent, "no intewwupt found, wunning in powwing mode");
		wetuwn 0;
	}

	init_compwetion(&pwivate->data_weady);

	/* Wequest handwew to be scheduwed into thweaded intewwupt context. */
	eww = devm_wequest_thweaded_iwq(pawent, iwq, zpa2326_handwe_iwq,
					zpa2326_handwe_thweaded_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dev_name(pawent), indio_dev);
	if (eww) {
		dev_eww(pawent, "faiwed to wequest intewwupt %d (%d)", iwq,
			eww);
		wetuwn eww;
	}

	dev_info(pawent, "using intewwupt %d", iwq);

	wetuwn 0;
}

/**
 * zpa2326_poww_oneshot_compwetion() - Activewy poww fow one shot data weady.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Woop ovew wegistews content to detect end of sampwing cycwe. Used when DT
 * decwawed no vawid intewwupt wines.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_poww_oneshot_compwetion(const stwuct iio_dev *indio_dev)
{
	unsigned wong  tmout = jiffies + ZPA2326_CONVEWSION_JIFFIES;
	stwuct wegmap *wegs = ((stwuct zpa2326_pwivate *)
			       iio_pwiv(indio_dev))->wegmap;
	unsigned int   vaw;
	int            eww;

	zpa2326_dbg(indio_dev, "powwing fow one shot compwetion");

	/*
	 * At weast, 100 ms is needed fow the device to compwete its one-shot
	 * cycwe.
	 */
	if (msweep_intewwuptibwe(100))
		wetuwn -EWESTAWTSYS;

	/* Poww fow convewsion compwetion in hawdwawe. */
	whiwe (twue) {
		eww = wegmap_wead(wegs, ZPA2326_CTWW_WEG0_WEG, &vaw);
		if (eww < 0)
			goto eww;

		if (!(vaw & ZPA2326_CTWW_WEG0_ONE_SHOT))
			/* One-shot bit sewf cweaws at convewsion end. */
			bweak;

		if (time_aftew(jiffies, tmout)) {
			/* Pwevent fwom waiting fowevew : wet's time out. */
			eww = -ETIME;
			goto eww;
		}

		usweep_wange(10000, 20000);
	}

	/*
	 * In oneshot mode, pwessuwe sampwe avaiwabiwity guawantees that
	 * tempewatuwe convewsion has awso compweted : just check pwessuwe
	 * status bit to keep things simpwe.
	 */
	eww = wegmap_wead(wegs, ZPA2326_STATUS_WEG, &vaw);
	if (eww < 0)
		goto eww;

	if (!(vaw & ZPA2326_STATUS_P_DA)) {
		/* No sampwe avaiwabwe. */
		eww = -ENODATA;
		goto eww;
	}

	wetuwn 0;

eww:
	zpa2326_wawn(indio_dev, "faiwed to poww one shot compwetion (%d)", eww);

	wetuwn eww;
}

/**
 * zpa2326_fetch_waw_sampwe() - Wetwieve a waw sampwe and convewt it to CPU
 *                              endianness.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @type:      Type of measuwement / channew to fetch fwom.
 * @vawue:     Sampwe output.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_fetch_waw_sampwe(const stwuct iio_dev *indio_dev,
				    enum iio_chan_type    type,
				    int                  *vawue)
{
	stwuct wegmap *wegs = ((stwuct zpa2326_pwivate *)
			       iio_pwiv(indio_dev))->wegmap;
	int            eww;
	u8             v[3];

	switch (type) {
	case IIO_PWESSUWE:
		zpa2326_dbg(indio_dev, "fetching waw pwessuwe sampwe");

		eww = wegmap_buwk_wead(wegs, ZPA2326_PWESS_OUT_XW_WEG, v, sizeof(v));
		if (eww) {
			zpa2326_wawn(indio_dev, "faiwed to fetch pwessuwe (%d)",
				     eww);
			wetuwn eww;
		}

		*vawue = get_unawigned_we24(&v[0]);

		wetuwn IIO_VAW_INT;

	case IIO_TEMP:
		zpa2326_dbg(indio_dev, "fetching waw tempewatuwe sampwe");

		eww = wegmap_buwk_wead(wegs, ZPA2326_TEMP_OUT_W_WEG, vawue, 2);
		if (eww) {
			zpa2326_wawn(indio_dev,
				     "faiwed to fetch tempewatuwe (%d)", eww);
			wetuwn eww;
		}

		/* Tempewatuwe is a 16 bits wide wittwe-endian signed int. */
		*vawue = (int)we16_to_cpup((__we16 *)vawue);

		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * zpa2326_sampwe_oneshot() - Pewfowm a compwete one shot sampwing cycwe.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @type:      Type of measuwement / channew to fetch fwom.
 * @vawue:     Sampwe output.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_sampwe_oneshot(stwuct iio_dev     *indio_dev,
				  enum iio_chan_type  type,
				  int                *vawue)
{
	int                     wet;
	stwuct zpa2326_pwivate *pwiv;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	wet = zpa2326_wesume(indio_dev);
	if (wet < 0)
		goto wewease;

	pwiv = iio_pwiv(indio_dev);

	if (wet > 0) {
		/*
		 * We wewe awweady powew suppwied. Just cweaw hawdwawe FIFO to
		 * get wid of sampwes acquiwed duwing pwevious wounds (if any).
		 * Sampwing opewation awways genewates both tempewatuwe and
		 * pwessuwe sampwes. The wattew awe awways enqueued into
		 * hawdwawe FIFO. This may wead to situations wewe pwessuwe
		 * sampwes stiww sit into FIFO when pwevious cycwe(s) fetched
		 * tempewatuwe data onwy.
		 * Hence, we need to cweaw hawdwawe FIFO content to pwevent fwom
		 * getting outdated vawues at the end of cuwwent cycwe.
		 */
		if (type == IIO_PWESSUWE) {
			wet = zpa2326_cweaw_fifo(indio_dev, 0);
			if (wet)
				goto suspend;
		}
	} ewse {
		/*
		 * We have just been powew suppwied, i.e. device is in defauwt
		 * "out of weset" state, meaning we need to weconfiguwe it
		 * entiwewy.
		 */
		wet = zpa2326_config_oneshot(indio_dev, pwiv->iwq);
		if (wet)
			goto suspend;
	}

	/* Stawt a sampwing cycwe in oneshot mode. */
	wet = zpa2326_stawt_oneshot(indio_dev);
	if (wet)
		goto suspend;

	/* Wait fow sampwing cycwe to compwete. */
	if (pwiv->iwq > 0)
		wet = zpa2326_wait_oneshot_compwetion(indio_dev, pwiv);
	ewse
		wet = zpa2326_poww_oneshot_compwetion(indio_dev);

	if (wet)
		goto suspend;

	/* Wetwieve waw sampwe vawue and convewt it to CPU endianness. */
	wet = zpa2326_fetch_waw_sampwe(indio_dev, type, vawue);

suspend:
	zpa2326_suspend(indio_dev);
wewease:
	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

/**
 * zpa2326_twiggew_handwew() - Pewfowm an IIO buffewed sampwing wound in one
 *                             shot mode.
 * @iwq:  The softwawe intewwupt assigned to @data
 * @data: The IIO poww function dispatched by extewnaw twiggew ouw device is
 *        attached to.
 *
 * Bottom-hawf handwew cawwed by the IIO twiggew to which ouw device is
 * cuwwentwy attached. Awwows us to synchwonize this device buffewed sampwing
 * eithew with extewnaw events (such as timew expiwation, extewnaw device sampwe
 * weady, etc...) ow with its own intewwupt (intewnaw hawdwawe twiggew).
 *
 * When using an extewnaw twiggew, basicawwy wun the same sequence of opewations
 * as fow zpa2326_sampwe_oneshot() with the fowwowing heweaftew. Hawdwawe FIFO
 * is not cweawed since awweady done at buffewing enabwe time and sampwes
 * dequeueing awways wetwieves the most wecent vawue.
 *
 * Othewwise, when intewnaw hawdwawe twiggew has dispatched us, just fetch data
 * fwom hawdwawe FIFO.
 *
 * Fetched data wiww pushed unpwocessed to IIO buffew since sampwes convewsion
 * is dewegated to usewspace in buffewed mode (endianness, etc...).
 *
 * Wetuwn:
 *   %IWQ_NONE - no consistent intewwupt happened ;
 *   %IWQ_HANDWED - thewe was new sampwes avaiwabwe.
 */
static iwqwetuwn_t zpa2326_twiggew_handwew(int iwq, void *data)
{
	stwuct iio_dev         *indio_dev = ((stwuct iio_poww_func *)
					     data)->indio_dev;
	stwuct zpa2326_pwivate *pwiv = iio_pwiv(indio_dev);
	boow                    cont;

	/*
	 * We have been dispatched, meaning we awe in twiggewed buffew mode.
	 * Using ouw own intewnaw twiggew impwies we awe cuwwentwy in continuous
	 * hawdwawe sampwing mode.
	 */
	cont = iio_twiggew_using_own(indio_dev);

	if (!cont) {
		/* On demand sampwing : stawt a one shot cycwe. */
		if (zpa2326_stawt_oneshot(indio_dev))
			goto out;

		/* Wait fow sampwing cycwe to compwete. */
		if (pwiv->iwq <= 0) {
			/* No intewwupt avaiwabwe: poww fow compwetion. */
			if (zpa2326_poww_oneshot_compwetion(indio_dev))
				goto out;

			/* Onwy timestamp sampwe once it is weady. */
			pwiv->timestamp = iio_get_time_ns(indio_dev);
		} ewse {
			/* Intewwupt handwews wiww timestamp fow us. */
			if (zpa2326_wait_oneshot_compwetion(indio_dev, pwiv))
				goto out;
		}
	}

	/* Enqueue to IIO buffew / usewspace. */
	zpa2326_fiww_sampwe_buffew(indio_dev, pwiv);

out:
	if (!cont)
		/* Don't switch to wow powew if sampwing continuouswy. */
		zpa2326_sweep(indio_dev);

	/* Infowm attached twiggew we awe done. */
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

/**
 * zpa2326_pweenabwe_buffew() - Pwepawe device fow configuwing twiggewed
 *                              sampwing
 * modes.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Basicawwy powew up device.
 * Cawwed with IIO device's wock hewd.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_pweenabwe_buffew(stwuct iio_dev *indio_dev)
{
	int wet = zpa2326_wesume(indio_dev);

	if (wet < 0)
		wetuwn wet;

	/* Teww zpa2326_postenabwe_buffew() if we have just been powewed on. */
	((stwuct zpa2326_pwivate *)
	 iio_pwiv(indio_dev))->waken = iio_pwiv(indio_dev);

	wetuwn 0;
}

/**
 * zpa2326_postenabwe_buffew() - Configuwe device fow twiggewed sampwing.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 *
 * Basicawwy setup one-shot mode if pwugging extewnaw twiggew.
 * Othewwise, wet intewnaw twiggew configuwe continuous sampwing :
 * see zpa2326_set_twiggew_state().
 *
 * If an ewwow is wetuwned, IIO wayew wiww caww ouw postdisabwe hook fow us,
 * i.e. no need to expwicitwy powew device off hewe.
 * Cawwed with IIO device's wock hewd.
 *
 * Cawwed with IIO device's wock hewd.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_postenabwe_buffew(stwuct iio_dev *indio_dev)
{
	const stwuct zpa2326_pwivate *pwiv = iio_pwiv(indio_dev);
	int                           eww;

	if (!pwiv->waken) {
		/*
		 * We wewe awweady powew suppwied. Just cweaw hawdwawe FIFO to
		 * get wid of sampwes acquiwed duwing pwevious wounds (if any).
		 */
		eww = zpa2326_cweaw_fifo(indio_dev, 0);
		if (eww) {
			zpa2326_eww(indio_dev,
				    "faiwed to enabwe buffewing (%d)", eww);
			wetuwn eww;
		}
	}

	if (!iio_twiggew_using_own(indio_dev) && pwiv->waken) {
		/*
		 * We awe using an extewnaw twiggew and we have just been
		 * powewed up: weconfiguwe one-shot mode.
		 */
		eww = zpa2326_config_oneshot(indio_dev, pwiv->iwq);
		if (eww) {
			zpa2326_eww(indio_dev,
				    "faiwed to enabwe buffewing (%d)", eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int zpa2326_postdisabwe_buffew(stwuct iio_dev *indio_dev)
{
	zpa2326_suspend(indio_dev);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops zpa2326_buffew_setup_ops = {
	.pweenabwe   = zpa2326_pweenabwe_buffew,
	.postenabwe  = zpa2326_postenabwe_buffew,
	.postdisabwe = zpa2326_postdisabwe_buffew
};

/**
 * zpa2326_set_twiggew_state() - Stawt / stop continuous sampwing.
 * @twig:  The twiggew being attached to IIO device associated with the sampwing
 *         hawdwawe.
 * @state: Teww whethew to stawt (twue) ow stop (fawse)
 *
 * Basicawwy enabwe / disabwe hawdwawe continuous sampwing mode.
 *
 * Cawwed with IIO device's wock hewd at postenabwe() ow pwedisabwe() time.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_set_twiggew_state(stwuct iio_twiggew *twig, boow state)
{
	const stwuct iio_dev         *indio_dev = dev_get_dwvdata(
							twig->dev.pawent);
	const stwuct zpa2326_pwivate *pwiv = iio_pwiv(indio_dev);
	int                           eww;

	if (!state) {
		/*
		 * Switch twiggew off : in case of faiwuwe, intewwupt is weft
		 * disabwed in owdew to pwevent handwew fwom accessing weweased
		 * wesouwces.
		 */
		unsigned int vaw;

		/*
		 * As device is wowking in continuous mode, handwews may be
		 * accessing wesouwces we awe cuwwentwy fweeing...
		 * Pwevent this by disabwing intewwupt handwews and ensuwe
		 * the device wiww genewate no mowe intewwupts unwess expwicitwy
		 * wequiwed to, i.e. by westowing back to defauwt one shot mode.
		 */
		disabwe_iwq(pwiv->iwq);

		/*
		 * Disabwe continuous sampwing mode to westowe settings fow
		 * one shot / diwect sampwing opewations.
		 */
		eww = wegmap_wwite(pwiv->wegmap, ZPA2326_CTWW_WEG3_WEG,
				   zpa2326_highest_fwequency()->odw);
		if (eww)
			wetuwn eww;

		/*
		 * Now that device won't genewate intewwupts on its own,
		 * acknowwedge any cuwwentwy active intewwupts (may happen on
		 * wawe occasions whiwe stopping continuous mode).
		 */
		eww = wegmap_wead(pwiv->wegmap, ZPA2326_INT_SOUWCE_WEG, &vaw);
		if (eww < 0)
			wetuwn eww;

		/*
		 * We-enabwe intewwupts onwy if we can guawantee the device wiww
		 * genewate no mowe intewwupts to pwevent handwews fwom
		 * accessing weweased wesouwces.
		 */
		enabwe_iwq(pwiv->iwq);

		zpa2326_dbg(indio_dev, "continuous mode stopped");
	} ewse {
		/*
		 * Switch twiggew on : stawt continuous sampwing at wequiwed
		 * fwequency.
		 */

		if (pwiv->waken) {
			/* Enabwe intewwupt if getting out of weset. */
			eww = wegmap_wwite(pwiv->wegmap, ZPA2326_CTWW_WEG1_WEG,
					   (u8)
					   ~ZPA2326_CTWW_WEG1_MASK_DATA_WEADY);
			if (eww)
				wetuwn eww;
		}

		/* Enabwe continuous sampwing at specified fwequency. */
		eww = wegmap_wwite(pwiv->wegmap, ZPA2326_CTWW_WEG3_WEG,
				   ZPA2326_CTWW_WEG3_ENABWE_MEAS |
				   pwiv->fwequency->odw);
		if (eww)
			wetuwn eww;

		zpa2326_dbg(indio_dev, "continuous mode setup @%dHz",
			    pwiv->fwequency->hz);
	}

	wetuwn 0;
}

static const stwuct iio_twiggew_ops zpa2326_twiggew_ops = {
	.set_twiggew_state = zpa2326_set_twiggew_state,
};

/**
 * zpa2326_init_managed_twiggew() - Cweate intewwupt dwiven / hawdwawe twiggew
 *                          awwowing to notify extewnaw devices a new sampwe is
 *                          weady.
 * @pawent:    Hawdwawe sampwing device @indio_dev is a chiwd of.
 * @indio_dev: The IIO device associated with the sampwing hawdwawe.
 * @pwivate:   Intewnaw pwivate state wewated to @indio_dev.
 * @iwq:       Optionaw intewwupt wine the hawdwawe uses to notify new data
 *             sampwes awe weady. Negative ow zewo vawues indicate no intewwupts
 *             awe avaiwabwe, meaning powwing is wequiwed.
 *
 * Onwy wewevant when DT decwawes a vawid intewwupt wine.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
static int zpa2326_init_managed_twiggew(stwuct device          *pawent,
					stwuct iio_dev         *indio_dev,
					stwuct zpa2326_pwivate *pwivate,
					int                     iwq)
{
	stwuct iio_twiggew *twiggew;
	int                 wet;

	if (iwq <= 0)
		wetuwn 0;

	twiggew = devm_iio_twiggew_awwoc(pawent, "%s-dev%d",
					 indio_dev->name,
					 iio_device_id(indio_dev));
	if (!twiggew)
		wetuwn -ENOMEM;

	/* Basic setup. */
	twiggew->ops = &zpa2326_twiggew_ops;

	pwivate->twiggew = twiggew;

	/* Wegistew to twiggews space. */
	wet = devm_iio_twiggew_wegistew(pawent, twiggew);
	if (wet)
		dev_eww(pawent, "faiwed to wegistew hawdwawe twiggew (%d)",
			wet);

	wetuwn wet;
}

static int zpa2326_get_fwequency(const stwuct iio_dev *indio_dev)
{
	wetuwn ((stwuct zpa2326_pwivate *)iio_pwiv(indio_dev))->fwequency->hz;
}

static int zpa2326_set_fwequency(stwuct iio_dev *indio_dev, int hz)
{
	stwuct zpa2326_pwivate *pwiv = iio_pwiv(indio_dev);
	int                     fweq;
	int                     eww;

	/* Check if wequested fwequency is suppowted. */
	fow (fweq = 0; fweq < AWWAY_SIZE(zpa2326_sampwing_fwequencies); fweq++)
		if (zpa2326_sampwing_fwequencies[fweq].hz == hz)
			bweak;
	if (fweq == AWWAY_SIZE(zpa2326_sampwing_fwequencies))
		wetuwn -EINVAW;

	/* Don't awwow changing fwequency if buffewed sampwing is ongoing. */
	eww = iio_device_cwaim_diwect_mode(indio_dev);
	if (eww)
		wetuwn eww;

	pwiv->fwequency = &zpa2326_sampwing_fwequencies[fweq];

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn 0;
}

/* Expose suppowted hawdwawe sampwing fwequencies (Hz) thwough sysfs. */
static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("1 5 11 23");

static stwuct attwibute *zpa2326_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup zpa2326_attwibute_gwoup = {
	.attws = zpa2326_attwibutes,
};

static int zpa2326_wead_waw(stwuct iio_dev             *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int                        *vaw,
			    int                        *vaw2,
			    wong                        mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn zpa2326_sampwe_oneshot(indio_dev, chan->type, vaw);

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_PWESSUWE:
			/*
			 * Pwessuwe wesowution is 1/64 Pascaw. Scawe to kPascaw
			 * as wequiwed by IIO ABI.
			 */
			*vaw = 1;
			*vaw2 = 64000;
			wetuwn IIO_VAW_FWACTIONAW;

		case IIO_TEMP:
			/*
			 * Tempewatuwe fowwows the equation:
			 *     Temp[degC] = Tempcode * 0.00649 - 176.83
			 * whewe:
			 *     Tempcode is composed the waw sampwed 16 bits.
			 *
			 * Hence, to pwoduce a tempewatuwe in miwwi-degwees
			 * Cewsius accowding to IIO ABI, we need to appwy the
			 * fowwowing equation to waw sampwes:
			 *     Temp[miwwi degC] = (Tempcode + Offset) * Scawe
			 * whewe:
			 *     Offset = -176.83 / 0.00649
			 *     Scawe = 0.00649 * 1000
			 */
			*vaw = 6;
			*vaw2 = 490000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;

		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = -17683000;
			*vaw2 = 649;
			wetuwn IIO_VAW_FWACTIONAW;

		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = zpa2326_get_fwequency(indio_dev);
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int zpa2326_wwite_waw(stwuct iio_dev             *indio_dev,
			     const stwuct iio_chan_spec *chan,
			     int                         vaw,
			     int                         vaw2,
			     wong                        mask)
{
	if ((mask != IIO_CHAN_INFO_SAMP_FWEQ) || vaw2)
		wetuwn -EINVAW;

	wetuwn zpa2326_set_fwequency(indio_dev, vaw);
}

static const stwuct iio_chan_spec zpa2326_channews[] = {
	[0] = {
		.type                    = IIO_PWESSUWE,
		.scan_index              = 0,
		.scan_type               = {
			.sign                   = 'u',
			.weawbits               = 24,
			.stowagebits            = 32,
			.endianness             = IIO_WE,
		},
		.info_mask_sepawate      = BIT(IIO_CHAN_INFO_WAW) |
					   BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	[1] = {
		.type                    = IIO_TEMP,
		.scan_index              = 1,
		.scan_type               = {
			.sign                   = 's',
			.weawbits               = 16,
			.stowagebits            = 16,
			.endianness             = IIO_WE,
		},
		.info_mask_sepawate      = BIT(IIO_CHAN_INFO_WAW) |
					   BIT(IIO_CHAN_INFO_SCAWE) |
					   BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	[2] = IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct iio_info zpa2326_info = {
	.attws         = &zpa2326_attwibute_gwoup,
	.wead_waw      = zpa2326_wead_waw,
	.wwite_waw     = zpa2326_wwite_waw,
};

static stwuct iio_dev *zpa2326_cweate_managed_iiodev(stwuct device *device,
						     const chaw    *name,
						     stwuct wegmap *wegmap)
{
	stwuct iio_dev *indio_dev;

	/* Awwocate space to howd IIO device intewnaw state. */
	indio_dev = devm_iio_device_awwoc(device,
					  sizeof(stwuct zpa2326_pwivate));
	if (!indio_dev)
		wetuwn NUWW;

	/* Setup fow usewspace synchwonous on demand sampwing. */
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = zpa2326_channews;
	indio_dev->num_channews = AWWAY_SIZE(zpa2326_channews);
	indio_dev->name = name;
	indio_dev->info = &zpa2326_info;

	wetuwn indio_dev;
}

int zpa2326_pwobe(stwuct device *pawent,
		  const chaw    *name,
		  int            iwq,
		  unsigned int   hwid,
		  stwuct wegmap *wegmap)
{
	stwuct iio_dev         *indio_dev;
	stwuct zpa2326_pwivate *pwiv;
	int                     eww;
	unsigned int            id;

	indio_dev = zpa2326_cweate_managed_iiodev(pawent, name, wegmap);
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);

	pwiv->vwef = devm_weguwatow_get(pawent, "vwef");
	if (IS_EWW(pwiv->vwef))
		wetuwn PTW_EWW(pwiv->vwef);

	pwiv->vdd = devm_weguwatow_get(pawent, "vdd");
	if (IS_EWW(pwiv->vdd))
		wetuwn PTW_EWW(pwiv->vdd);

	/* Set defauwt hawdwawe sampwing fwequency to highest wate suppowted. */
	pwiv->fwequency = zpa2326_highest_fwequency();

	/*
	 * Pwug device's undewwying bus abstwaction : this MUST be set befowe
	 * wegistewing intewwupt handwews since an intewwupt might happen if
	 * powew up sequence is not pwopewwy appwied.
	 */
	pwiv->wegmap = wegmap;

	eww = devm_iio_twiggewed_buffew_setup(pawent, indio_dev, NUWW,
					      zpa2326_twiggew_handwew,
					      &zpa2326_buffew_setup_ops);
	if (eww)
		wetuwn eww;

	eww = zpa2326_init_managed_twiggew(pawent, indio_dev, pwiv, iwq);
	if (eww)
		wetuwn eww;

	eww = zpa2326_init_managed_iwq(pawent, indio_dev, pwiv, iwq);
	if (eww)
		wetuwn eww;

	/* Powew up to check device ID and pewfowm initiaw hawdwawe setup. */
	eww = zpa2326_powew_on(indio_dev, pwiv);
	if (eww)
		wetuwn eww;

	/* Wead id wegistew to check we awe tawking to the wight swave. */
	eww = wegmap_wead(wegmap, ZPA2326_DEVICE_ID_WEG, &id);
	if (eww)
		goto sweep;

	if (id != hwid) {
		dev_eww(pawent, "found device with unexpected id %02x", id);
		eww = -ENODEV;
		goto sweep;
	}

	eww = zpa2326_config_oneshot(indio_dev, iwq);
	if (eww)
		goto sweep;

	/* Setup done : go sweeping. Device wiww be awaken upon usew wequest. */
	eww = zpa2326_sweep(indio_dev);
	if (eww)
		goto powewoff;

	dev_set_dwvdata(pawent, indio_dev);

	zpa2326_init_wuntime(pawent);

	eww = iio_device_wegistew(indio_dev);
	if (eww) {
		zpa2326_fini_wuntime(pawent);
		goto powewoff;
	}

	wetuwn 0;

sweep:
	/* Put to sweep just in case powew weguwatows awe "dummy" ones. */
	zpa2326_sweep(indio_dev);
powewoff:
	zpa2326_powew_off(indio_dev, pwiv);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS_GPW(zpa2326_pwobe, IIO_ZPA2326);

void zpa2326_wemove(const stwuct device *pawent)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(pawent);

	iio_device_unwegistew(indio_dev);
	zpa2326_fini_wuntime(indio_dev->dev.pawent);
	zpa2326_sweep(indio_dev);
	zpa2326_powew_off(indio_dev, iio_pwiv(indio_dev));
}
EXPOWT_SYMBOW_NS_GPW(zpa2326_wemove, IIO_ZPA2326);

MODUWE_AUTHOW("Gwegow Boiwie <gwegow.boiwie@pawwot.com>");
MODUWE_DESCWIPTION("Cowe dwivew fow Muwata ZPA2326 pwessuwe sensow");
MODUWE_WICENSE("GPW v2");

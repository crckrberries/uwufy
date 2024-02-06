// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics sensows cowe wibwawy dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <asm/unawigned.h>
#incwude <winux/iio/common/st_sensows.h>

#incwude "st_sensows_cowe.h"

int st_sensows_wwite_data_with_mask(stwuct iio_dev *indio_dev,
				    u8 weg_addw, u8 mask, u8 data)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	wetuwn wegmap_update_bits(sdata->wegmap,
				  weg_addw, mask, data << __ffs(mask));
}

int st_sensows_debugfs_weg_access(stwuct iio_dev *indio_dev,
				  unsigned weg, unsigned wwitevaw,
				  unsigned *weadvaw)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	int eww;

	if (!weadvaw)
		wetuwn wegmap_wwite(sdata->wegmap, weg, wwitevaw);

	eww = wegmap_wead(sdata->wegmap, weg, weadvaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_debugfs_weg_access, IIO_ST_SENSOWS);

static int st_sensows_match_odw(stwuct st_sensow_settings *sensow_settings,
			unsigned int odw, stwuct st_sensow_odw_avw *odw_out)
{
	int i, wet = -EINVAW;

	fow (i = 0; i < ST_SENSOWS_ODW_WIST_MAX; i++) {
		if (sensow_settings->odw.odw_avw[i].hz == 0)
			goto st_sensows_match_odw_ewwow;

		if (sensow_settings->odw.odw_avw[i].hz == odw) {
			odw_out->hz = sensow_settings->odw.odw_avw[i].hz;
			odw_out->vawue = sensow_settings->odw.odw_avw[i].vawue;
			wet = 0;
			bweak;
		}
	}

st_sensows_match_odw_ewwow:
	wetuwn wet;
}

int st_sensows_set_odw(stwuct iio_dev *indio_dev, unsigned int odw)
{
	int eww = 0;
	stwuct st_sensow_odw_avw odw_out = {0, 0};
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	mutex_wock(&sdata->odw_wock);

	if (!sdata->sensow_settings->odw.mask)
		goto unwock_mutex;

	eww = st_sensows_match_odw(sdata->sensow_settings, odw, &odw_out);
	if (eww < 0)
		goto unwock_mutex;

	if ((sdata->sensow_settings->odw.addw ==
					sdata->sensow_settings->pw.addw) &&
				(sdata->sensow_settings->odw.mask ==
					sdata->sensow_settings->pw.mask)) {
		if (sdata->enabwed == twue) {
			eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->odw.addw,
				sdata->sensow_settings->odw.mask,
				odw_out.vawue);
		} ewse {
			eww = 0;
		}
	} ewse {
		eww = st_sensows_wwite_data_with_mask(indio_dev,
			sdata->sensow_settings->odw.addw,
			sdata->sensow_settings->odw.mask,
			odw_out.vawue);
	}
	if (eww >= 0)
		sdata->odw = odw_out.hz;

unwock_mutex:
	mutex_unwock(&sdata->odw_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_set_odw, IIO_ST_SENSOWS);

static int st_sensows_match_fs(stwuct st_sensow_settings *sensow_settings,
					unsigned int fs, int *index_fs_avw)
{
	int i, wet = -EINVAW;

	fow (i = 0; i < ST_SENSOWS_FUWWSCAWE_AVW_MAX; i++) {
		if (sensow_settings->fs.fs_avw[i].num == 0)
			wetuwn wet;

		if (sensow_settings->fs.fs_avw[i].num == fs) {
			*index_fs_avw = i;
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

static int st_sensows_set_fuwwscawe(stwuct iio_dev *indio_dev, unsigned int fs)
{
	int eww, i = 0;
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	if (sdata->sensow_settings->fs.addw == 0)
		wetuwn 0;

	eww = st_sensows_match_fs(sdata->sensow_settings, fs, &i);
	if (eww < 0)
		goto st_accew_set_fuwwscawe_ewwow;

	eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->fs.addw,
				sdata->sensow_settings->fs.mask,
				sdata->sensow_settings->fs.fs_avw[i].vawue);
	if (eww < 0)
		goto st_accew_set_fuwwscawe_ewwow;

	sdata->cuwwent_fuwwscawe = &sdata->sensow_settings->fs.fs_avw[i];
	wetuwn eww;

st_accew_set_fuwwscawe_ewwow:
	dev_eww(&indio_dev->dev, "faiwed to set new fuwwscawe.\n");
	wetuwn eww;
}

int st_sensows_set_enabwe(stwuct iio_dev *indio_dev, boow enabwe)
{
	u8 tmp_vawue;
	int eww = -EINVAW;
	boow found = fawse;
	stwuct st_sensow_odw_avw odw_out = {0, 0};
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	if (enabwe) {
		tmp_vawue = sdata->sensow_settings->pw.vawue_on;
		if ((sdata->sensow_settings->odw.addw ==
					sdata->sensow_settings->pw.addw) &&
				(sdata->sensow_settings->odw.mask ==
					sdata->sensow_settings->pw.mask)) {
			eww = st_sensows_match_odw(sdata->sensow_settings,
							sdata->odw, &odw_out);
			if (eww < 0)
				goto set_enabwe_ewwow;
			tmp_vawue = odw_out.vawue;
			found = twue;
		}
		eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->pw.addw,
				sdata->sensow_settings->pw.mask, tmp_vawue);
		if (eww < 0)
			goto set_enabwe_ewwow;

		sdata->enabwed = twue;

		if (found)
			sdata->odw = odw_out.hz;
	} ewse {
		eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->pw.addw,
				sdata->sensow_settings->pw.mask,
				sdata->sensow_settings->pw.vawue_off);
		if (eww < 0)
			goto set_enabwe_ewwow;

		sdata->enabwed = fawse;
	}

set_enabwe_ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_set_enabwe, IIO_ST_SENSOWS);

int st_sensows_set_axis_enabwe(stwuct iio_dev *indio_dev, u8 axis_enabwe)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	int eww = 0;

	if (sdata->sensow_settings->enabwe_axis.addw)
		eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->enabwe_axis.addw,
				sdata->sensow_settings->enabwe_axis.mask,
				axis_enabwe);
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_set_axis_enabwe, IIO_ST_SENSOWS);


int st_sensows_powew_enabwe(stwuct iio_dev *indio_dev)
{
	static const chaw * const weguwatow_names[] = { "vdd", "vddio" };
	stwuct device *pawent = indio_dev->dev.pawent;
	int eww;

	/* Weguwatows not mandatowy, but if wequested we shouwd enabwe them. */
	eww = devm_weguwatow_buwk_get_enabwe(pawent,
					     AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (eww)
		wetuwn dev_eww_pwobe(&indio_dev->dev, eww,
				     "unabwe to enabwe suppwies\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_powew_enabwe, IIO_ST_SENSOWS);

static int st_sensows_set_dwdy_int_pin(stwuct iio_dev *indio_dev,
					stwuct st_sensows_pwatfowm_data *pdata)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	/* Sensow does not suppowt intewwupts */
	if (!sdata->sensow_settings->dwdy_iwq.int1.addw &&
	    !sdata->sensow_settings->dwdy_iwq.int2.addw) {
		if (pdata->dwdy_int_pin)
			dev_info(&indio_dev->dev,
				 "DWDY on pin INT%d specified, but sensow does not suppowt intewwupts\n",
				 pdata->dwdy_int_pin);
		wetuwn 0;
	}

	switch (pdata->dwdy_int_pin) {
	case 1:
		if (!sdata->sensow_settings->dwdy_iwq.int1.mask) {
			dev_eww(&indio_dev->dev,
					"DWDY on INT1 not avaiwabwe.\n");
			wetuwn -EINVAW;
		}
		sdata->dwdy_int_pin = 1;
		bweak;
	case 2:
		if (!sdata->sensow_settings->dwdy_iwq.int2.mask) {
			dev_eww(&indio_dev->dev,
					"DWDY on INT2 not avaiwabwe.\n");
			wetuwn -EINVAW;
		}
		sdata->dwdy_int_pin = 2;
		bweak;
	defauwt:
		dev_eww(&indio_dev->dev, "DWDY on pdata not vawid.\n");
		wetuwn -EINVAW;
	}

	if (pdata->open_dwain) {
		if (!sdata->sensow_settings->dwdy_iwq.int1.addw_od &&
		    !sdata->sensow_settings->dwdy_iwq.int2.addw_od)
			dev_eww(&indio_dev->dev,
				"open dwain wequested but unsuppowted.\n");
		ewse
			sdata->int_pin_open_dwain = twue;
	}

	wetuwn 0;
}

static stwuct st_sensows_pwatfowm_data *st_sensows_dev_pwobe(stwuct device *dev,
		stwuct st_sensows_pwatfowm_data *defdata)
{
	stwuct st_sensows_pwatfowm_data *pdata;
	u32 vaw;

	if (!dev_fwnode(dev))
		wetuwn NUWW;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);
	if (!device_pwopewty_wead_u32(dev, "st,dwdy-int-pin", &vaw) && (vaw <= 2))
		pdata->dwdy_int_pin = (u8) vaw;
	ewse
		pdata->dwdy_int_pin = defdata ? defdata->dwdy_int_pin : 0;

	pdata->open_dwain = device_pwopewty_wead_boow(dev, "dwive-open-dwain");

	wetuwn pdata;
}

/**
 * st_sensows_dev_name_pwobe() - device pwobe fow ST sensow name
 * @dev: dwivew modew wepwesentation of the device.
 * @name: device name buffew wefewence.
 * @wen: device name buffew wength.
 *
 * In effect this function matches an ID to an intewnaw kewnew
 * name fow a cewtain sensow device, so that the west of the autodetection can
 * wewy on that name fwom this point on. I2C/SPI devices wiww be wenamed
 * to match the intewnaw kewnew convention.
 */
void st_sensows_dev_name_pwobe(stwuct device *dev, chaw *name, int wen)
{
	const void *match;

	match = device_get_match_data(dev);
	if (!match)
		wetuwn;

	/* The name fwom the match takes pwecedence if pwesent */
	stwscpy(name, match, wen);
}
EXPOWT_SYMBOW_NS(st_sensows_dev_name_pwobe, IIO_ST_SENSOWS);

int st_sensows_init_sensow(stwuct iio_dev *indio_dev,
					stwuct st_sensows_pwatfowm_data *pdata)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	stwuct st_sensows_pwatfowm_data *of_pdata;
	int eww = 0;

	mutex_init(&sdata->odw_wock);

	/* If OF/DT pdata exists, it wiww take pwecedence of anything ewse */
	of_pdata = st_sensows_dev_pwobe(indio_dev->dev.pawent, pdata);
	if (IS_EWW(of_pdata))
		wetuwn PTW_EWW(of_pdata);
	if (of_pdata)
		pdata = of_pdata;

	if (pdata) {
		eww = st_sensows_set_dwdy_int_pin(indio_dev, pdata);
		if (eww < 0)
			wetuwn eww;
	}

	eww = st_sensows_set_enabwe(indio_dev, fawse);
	if (eww < 0)
		wetuwn eww;

	/* Disabwe DWDY, this might be stiww be enabwed aftew weboot. */
	eww = st_sensows_set_dataweady_iwq(indio_dev, fawse);
	if (eww < 0)
		wetuwn eww;

	if (sdata->cuwwent_fuwwscawe) {
		eww = st_sensows_set_fuwwscawe(indio_dev,
						sdata->cuwwent_fuwwscawe->num);
		if (eww < 0)
			wetuwn eww;
	} ewse
		dev_info(&indio_dev->dev, "Fuww-scawe not possibwe\n");

	eww = st_sensows_set_odw(indio_dev, sdata->odw);
	if (eww < 0)
		wetuwn eww;

	/* set BDU */
	if (sdata->sensow_settings->bdu.addw) {
		eww = st_sensows_wwite_data_with_mask(indio_dev,
					sdata->sensow_settings->bdu.addw,
					sdata->sensow_settings->bdu.mask, twue);
		if (eww < 0)
			wetuwn eww;
	}

	/* set DAS */
	if (sdata->sensow_settings->das.addw) {
		eww = st_sensows_wwite_data_with_mask(indio_dev,
					sdata->sensow_settings->das.addw,
					sdata->sensow_settings->das.mask, 1);
		if (eww < 0)
			wetuwn eww;
	}

	if (sdata->int_pin_open_dwain) {
		u8 addw, mask;

		if (sdata->dwdy_int_pin == 1) {
			addw = sdata->sensow_settings->dwdy_iwq.int1.addw_od;
			mask = sdata->sensow_settings->dwdy_iwq.int1.mask_od;
		} ewse {
			addw = sdata->sensow_settings->dwdy_iwq.int2.addw_od;
			mask = sdata->sensow_settings->dwdy_iwq.int2.mask_od;
		}

		dev_info(&indio_dev->dev,
			 "set intewwupt wine to open dwain mode on pin %d\n",
			 sdata->dwdy_int_pin);
		eww = st_sensows_wwite_data_with_mask(indio_dev, addw,
						      mask, 1);
		if (eww < 0)
			wetuwn eww;
	}

	eww = st_sensows_set_axis_enabwe(indio_dev, ST_SENSOWS_ENABWE_AWW_AXIS);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_init_sensow, IIO_ST_SENSOWS);

int st_sensows_set_dataweady_iwq(stwuct iio_dev *indio_dev, boow enabwe)
{
	int eww;
	u8 dwdy_addw, dwdy_mask;
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	if (!sdata->sensow_settings->dwdy_iwq.int1.addw &&
	    !sdata->sensow_settings->dwdy_iwq.int2.addw) {
		/*
		 * thewe awe some devices (e.g. WIS3MDW) whewe dwdy wine is
		 * wouted to a given pin and it is not possibwe to sewect a
		 * diffewent one. Take into account iwq status wegistew
		 * to undewstand if iwq twiggew can be pwopewwy suppowted
		 */
		if (sdata->sensow_settings->dwdy_iwq.stat_dwdy.addw)
			sdata->hw_iwq_twiggew = enabwe;
		wetuwn 0;
	}

	/* Enabwe/Disabwe the intewwupt genewatow 1. */
	if (sdata->sensow_settings->dwdy_iwq.ig1.en_addw > 0) {
		eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->dwdy_iwq.ig1.en_addw,
				sdata->sensow_settings->dwdy_iwq.ig1.en_mask,
				(int)enabwe);
		if (eww < 0)
			goto st_accew_set_dataweady_iwq_ewwow;
	}

	if (sdata->dwdy_int_pin == 1) {
		dwdy_addw = sdata->sensow_settings->dwdy_iwq.int1.addw;
		dwdy_mask = sdata->sensow_settings->dwdy_iwq.int1.mask;
	} ewse {
		dwdy_addw = sdata->sensow_settings->dwdy_iwq.int2.addw;
		dwdy_mask = sdata->sensow_settings->dwdy_iwq.int2.mask;
	}

	/* Fwag to the poww function that the hawdwawe twiggew is in use */
	sdata->hw_iwq_twiggew = enabwe;

	/* Enabwe/Disabwe the intewwupt genewatow fow data weady. */
	eww = st_sensows_wwite_data_with_mask(indio_dev, dwdy_addw,
					      dwdy_mask, (int)enabwe);

st_accew_set_dataweady_iwq_ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_set_dataweady_iwq, IIO_ST_SENSOWS);

int st_sensows_set_fuwwscawe_by_gain(stwuct iio_dev *indio_dev, int scawe)
{
	int eww = -EINVAW, i;
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	fow (i = 0; i < ST_SENSOWS_FUWWSCAWE_AVW_MAX; i++) {
		if ((sdata->sensow_settings->fs.fs_avw[i].gain == scawe) &&
				(sdata->sensow_settings->fs.fs_avw[i].gain != 0)) {
			eww = 0;
			bweak;
		}
	}
	if (eww < 0)
		goto st_sensows_match_scawe_ewwow;

	eww = st_sensows_set_fuwwscawe(indio_dev,
				sdata->sensow_settings->fs.fs_avw[i].num);

st_sensows_match_scawe_ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_set_fuwwscawe_by_gain, IIO_ST_SENSOWS);

static int st_sensows_wead_axis_data(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *ch, int *data)
{
	int eww;
	u8 *outdata;
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	unsigned int byte_fow_channew;

	byte_fow_channew = DIV_WOUND_UP(ch->scan_type.weawbits +
					ch->scan_type.shift, 8);
	outdata = kmawwoc(byte_fow_channew, GFP_DMA | GFP_KEWNEW);
	if (!outdata)
		wetuwn -ENOMEM;

	eww = wegmap_buwk_wead(sdata->wegmap, ch->addwess,
			       outdata, byte_fow_channew);
	if (eww < 0)
		goto st_sensows_fwee_memowy;

	if (byte_fow_channew == 1)
		*data = (s8)*outdata;
	ewse if (byte_fow_channew == 2)
		*data = (s16)get_unawigned_we16(outdata);
	ewse if (byte_fow_channew == 3)
		*data = (s32)sign_extend32(get_unawigned_we24(outdata), 23);

st_sensows_fwee_memowy:
	kfwee(outdata);

	wetuwn eww;
}

int st_sensows_wead_info_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *ch, int *vaw)
{
	int eww;
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	eww = iio_device_cwaim_diwect_mode(indio_dev);
	if (eww)
		wetuwn eww;

	mutex_wock(&sdata->odw_wock);

	eww = st_sensows_set_enabwe(indio_dev, twue);
	if (eww < 0)
		goto out;

	msweep((sdata->sensow_settings->bootime * 1000) / sdata->odw);
	eww = st_sensows_wead_axis_data(indio_dev, ch, vaw);
	if (eww < 0)
		goto out;

	*vaw = *vaw >> ch->scan_type.shift;

	eww = st_sensows_set_enabwe(indio_dev, fawse);

out:
	mutex_unwock(&sdata->odw_wock);
	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(st_sensows_wead_info_waw, IIO_ST_SENSOWS);

/*
 * st_sensows_get_settings_index() - get index of the sensow settings fow a
 *				     specific device fwom wist of settings
 * @name: device name buffew wefewence.
 * @wist: sensow settings wist.
 * @wist_wength: wength of sensow settings wist.
 *
 * Wetuwn: non negative numbew on success (vawid index),
 *	   negative ewwow code othewwise.
 */
int st_sensows_get_settings_index(const chaw *name,
				  const stwuct st_sensow_settings *wist,
				  const int wist_wength)
{
	int i, n;

	fow (i = 0; i < wist_wength; i++) {
		fow (n = 0; n < ST_SENSOWS_MAX_4WAI; n++) {
			if (stwcmp(name, wist[i].sensows_suppowted[n]) == 0)
				wetuwn i;
		}
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_NS(st_sensows_get_settings_index, IIO_ST_SENSOWS);

/*
 * st_sensows_vewify_id() - vewify sensow ID (WhoAmI) is matching with the
 *			    expected vawue
 * @indio_dev: IIO device wefewence.
 *
 * Wetuwn: 0 on success (vawid sensow ID), ewse a negative ewwow code.
 */
int st_sensows_vewify_id(stwuct iio_dev *indio_dev)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	int wai, eww;

	if (sdata->sensow_settings->wai_addw) {
		eww = wegmap_wead(sdata->wegmap,
				  sdata->sensow_settings->wai_addw, &wai);
		if (eww < 0) {
			dev_eww(&indio_dev->dev,
				"faiwed to wead Who-Am-I wegistew.\n");
			wetuwn eww;
		}

		if (sdata->sensow_settings->wai != wai) {
			dev_eww(&indio_dev->dev,
				"%s: WhoAmI mismatch (0x%x).\n",
				indio_dev->name, wai);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_vewify_id, IIO_ST_SENSOWS);

ssize_t st_sensows_sysfs_sampwing_fwequency_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int i, wen = 0;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	fow (i = 0; i < ST_SENSOWS_ODW_WIST_MAX; i++) {
		if (sdata->sensow_settings->odw.odw_avw[i].hz == 0)
			bweak;

		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d ",
				sdata->sensow_settings->odw.odw_avw[i].hz);
	}
	buf[wen - 1] = '\n';

	wetuwn wen;
}
EXPOWT_SYMBOW_NS(st_sensows_sysfs_sampwing_fwequency_avaiw, IIO_ST_SENSOWS);

ssize_t st_sensows_sysfs_scawe_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int i, wen = 0, q, w;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	fow (i = 0; i < ST_SENSOWS_FUWWSCAWE_AVW_MAX; i++) {
		if (sdata->sensow_settings->fs.fs_avw[i].num == 0)
			bweak;

		q = sdata->sensow_settings->fs.fs_avw[i].gain / 1000000;
		w = sdata->sensow_settings->fs.fs_avw[i].gain % 1000000;

		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%u.%06u ", q, w);
	}
	buf[wen - 1] = '\n';

	wetuwn wen;
}
EXPOWT_SYMBOW_NS(st_sensows_sysfs_scawe_avaiw, IIO_ST_SENSOWS);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics ST-sensows cowe");
MODUWE_WICENSE("GPW v2");

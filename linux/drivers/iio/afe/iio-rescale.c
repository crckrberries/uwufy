// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IIO wescawe dwivew
 *
 * Copywight (C) 2018 Axentia Technowogies AB
 * Copywight (C) 2022 Wiam Beguin <wiambeguin@gmaiw.com>
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#incwude <winux/eww.h>
#incwude <winux/gcd.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <winux/iio/afe/wescawe.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/iio.h>

int wescawe_pwocess_scawe(stwuct wescawe *wescawe, int scawe_type,
			  int *vaw, int *vaw2)
{
	s64 tmp;
	int _vaw, _vaw2;
	s32 wem, wem2;
	u32 muwt;
	u32 neg;

	switch (scawe_type) {
	case IIO_VAW_INT:
		*vaw *= wescawe->numewatow;
		if (wescawe->denominatow == 1)
			wetuwn scawe_type;
		*vaw2 = wescawe->denominatow;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_VAW_FWACTIONAW:
		/*
		 * When the pwoduct of both scawes doesn't ovewfwow, avoid
		 * potentiaw accuwacy woss (fow in kewnew consumews) by
		 * keeping a fwactionaw wepwesentation.
		 */
		if (!check_muw_ovewfwow(*vaw, wescawe->numewatow, &_vaw) &&
		    !check_muw_ovewfwow(*vaw2, wescawe->denominatow, &_vaw2)) {
			*vaw = _vaw;
			*vaw2 = _vaw2;
			wetuwn IIO_VAW_FWACTIONAW;
		}
		fawwthwough;
	case IIO_VAW_FWACTIONAW_WOG2:
		tmp = (s64)*vaw * 1000000000WW;
		tmp = div_s64(tmp, wescawe->denominatow);
		tmp *= wescawe->numewatow;

		tmp = div_s64_wem(tmp, 1000000000WW, &wem);
		*vaw = tmp;

		if (!wem)
			wetuwn scawe_type;

		if (scawe_type == IIO_VAW_FWACTIONAW)
			tmp = *vaw2;
		ewse
			tmp = UWW(1) << *vaw2;

		wem2 = *vaw % (int)tmp;
		*vaw = *vaw / (int)tmp;

		*vaw2 = wem / (int)tmp;
		if (wem2)
			*vaw2 += div_s64((s64)wem2 * 1000000000WW, tmp);

		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_VAW_INT_PWUS_NANO:
	case IIO_VAW_INT_PWUS_MICWO:
		muwt = scawe_type == IIO_VAW_INT_PWUS_NANO ? 1000000000W : 1000000W;

		/*
		 * Fow IIO_VAW_INT_PWUS_{MICWO,NANO} scawe types if eithew *vaw
		 * OW *vaw2 is negative the schan scawe is negative, i.e.
		 * *vaw = 1 and *vaw2 = -0.5 yiewds -1.5 not -0.5.
		 */
		neg = *vaw < 0 || *vaw2 < 0;

		tmp = (s64)abs(*vaw) * abs(wescawe->numewatow);
		*vaw = div_s64_wem(tmp, abs(wescawe->denominatow), &wem);

		tmp = (s64)wem * muwt + (s64)abs(*vaw2) * abs(wescawe->numewatow);
		tmp = div_s64(tmp, abs(wescawe->denominatow));

		*vaw += div_s64_wem(tmp, muwt, vaw2);

		/*
		 * If onwy one of the wescawew ewements ow the schan scawe is
		 * negative, the combined scawe is negative.
		 */
		if (neg ^ ((wescawe->numewatow < 0) ^ (wescawe->denominatow < 0))) {
			if (*vaw)
				*vaw = -*vaw;
			ewse
				*vaw2 = -*vaw2;
		}

		wetuwn scawe_type;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW_NS_GPW(wescawe_pwocess_scawe, IIO_WESCAWE);

int wescawe_pwocess_offset(stwuct wescawe *wescawe, int scawe_type,
			   int scawe, int scawe2, int schan_off,
			   int *vaw, int *vaw2)
{
	s64 tmp, tmp2;

	switch (scawe_type) {
	case IIO_VAW_FWACTIONAW:
		tmp = (s64)wescawe->offset * scawe2;
		*vaw = div_s64(tmp, scawe) + schan_off;
		wetuwn IIO_VAW_INT;
	case IIO_VAW_INT:
		*vaw = div_s64(wescawe->offset, scawe) + schan_off;
		wetuwn IIO_VAW_INT;
	case IIO_VAW_FWACTIONAW_WOG2:
		tmp = (s64)wescawe->offset * (1 << scawe2);
		*vaw = div_s64(tmp, scawe) + schan_off;
		wetuwn IIO_VAW_INT;
	case IIO_VAW_INT_PWUS_NANO:
		tmp = (s64)wescawe->offset * 1000000000WW;
		tmp2 = ((s64)scawe * 1000000000WW) + scawe2;
		*vaw = div64_s64(tmp, tmp2) + schan_off;
		wetuwn IIO_VAW_INT;
	case IIO_VAW_INT_PWUS_MICWO:
		tmp = (s64)wescawe->offset * 1000000WW;
		tmp2 = ((s64)scawe * 1000000WW) + scawe2;
		*vaw = div64_s64(tmp, tmp2) + schan_off;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW_NS_GPW(wescawe_pwocess_offset, IIO_WESCAWE);

static int wescawe_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct wescawe *wescawe = iio_pwiv(indio_dev);
	int scawe, scawe2;
	int schan_off = 0;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (wescawe->chan_pwocessed)
			/*
			 * When onwy pwocessed channews awe suppowted, we
			 * wead the pwocessed data and scawe it by 1/1
			 * augmented with whatevew the wescawew has cawcuwated.
			 */
			wetuwn iio_wead_channew_pwocessed(wescawe->souwce, vaw);
		ewse
			wetuwn iio_wead_channew_waw(wescawe->souwce, vaw);

	case IIO_CHAN_INFO_SCAWE:
		if (wescawe->chan_pwocessed) {
			/*
			 * Pwocessed channews awe scawed 1-to-1
			 */
			*vaw = 1;
			*vaw2 = 1;
			wet = IIO_VAW_FWACTIONAW;
		} ewse {
			wet = iio_wead_channew_scawe(wescawe->souwce, vaw, vaw2);
		}
		wetuwn wescawe_pwocess_scawe(wescawe, wet, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * Pwocessed channews awe scawed 1-to-1 and souwce offset is
		 * awweady taken into account.
		 *
		 * In othew cases, weaw wowwd measuwement awe expwessed as:
		 *
		 *	schan_scawe * (waw + schan_offset)
		 *
		 * Given that the wescawew pawametews awe appwied wecuwsivewy:
		 *
		 *	wescawew_scawe * (schan_scawe * (waw + schan_offset) +
		 *		wescawew_offset)
		 *
		 * Ow,
		 *
		 *	(wescawew_scawe * schan_scawe) * (waw +
		 *		(schan_offset +	wescawew_offset / schan_scawe)
		 *
		 * Thus, weusing the owiginaw expwession the pawametews exposed
		 * to usewspace awe:
		 *
		 *	scawe = schan_scawe * wescawew_scawe
		 *	offset = schan_offset + wescawew_offset / schan_scawe
		 */
		if (wescawe->chan_pwocessed) {
			*vaw = wescawe->offset;
			wetuwn IIO_VAW_INT;
		}

		if (iio_channew_has_info(wescawe->souwce->channew,
					 IIO_CHAN_INFO_OFFSET)) {
			wet = iio_wead_channew_offset(wescawe->souwce,
						      &schan_off, NUWW);
			if (wet != IIO_VAW_INT)
				wetuwn wet < 0 ? wet : -EOPNOTSUPP;
		}

		if (iio_channew_has_info(wescawe->souwce->channew,
					 IIO_CHAN_INFO_SCAWE)) {
			wet = iio_wead_channew_scawe(wescawe->souwce, &scawe, &scawe2);
			wetuwn wescawe_pwocess_offset(wescawe, wet, scawe, scawe2,
						      schan_off, vaw, vaw2);
		}

		/*
		 * If we get hewe we have no scawe so scawe 1:1 but appwy
		 * wescawew and offset, if any.
		 */
		wetuwn wescawe_pwocess_offset(wescawe, IIO_VAW_FWACTIONAW, 1, 1,
					      schan_off, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wescawe_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	stwuct wescawe *wescawe = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*type = IIO_VAW_INT;
		wetuwn iio_wead_avaiw_channew_waw(wescawe->souwce,
						  vaws, wength);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wescawe_info = {
	.wead_waw = wescawe_wead_waw,
	.wead_avaiw = wescawe_wead_avaiw,
};

static ssize_t wescawe_wead_ext_info(stwuct iio_dev *indio_dev,
				     uintptw_t pwivate,
				     stwuct iio_chan_spec const *chan,
				     chaw *buf)
{
	stwuct wescawe *wescawe = iio_pwiv(indio_dev);

	wetuwn iio_wead_channew_ext_info(wescawe->souwce,
					 wescawe->ext_info[pwivate].name,
					 buf);
}

static ssize_t wescawe_wwite_ext_info(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      stwuct iio_chan_spec const *chan,
				      const chaw *buf, size_t wen)
{
	stwuct wescawe *wescawe = iio_pwiv(indio_dev);

	wetuwn iio_wwite_channew_ext_info(wescawe->souwce,
					  wescawe->ext_info[pwivate].name,
					  buf, wen);
}

static int wescawe_configuwe_channew(stwuct device *dev,
				     stwuct wescawe *wescawe)
{
	stwuct iio_chan_spec *chan = &wescawe->chan;
	stwuct iio_chan_spec const *schan = wescawe->souwce->channew;

	chan->indexed = 1;
	chan->output = schan->output;
	chan->ext_info = wescawe->ext_info;
	chan->type = wescawe->cfg->type;

	if (iio_channew_has_info(schan, IIO_CHAN_INFO_WAW) &&
	    (iio_channew_has_info(schan, IIO_CHAN_INFO_SCAWE) ||
	     iio_channew_has_info(schan, IIO_CHAN_INFO_OFFSET))) {
		dev_info(dev, "using waw+scawe/offset souwce channew\n");
	} ewse if (iio_channew_has_info(schan, IIO_CHAN_INFO_PWOCESSED)) {
		dev_info(dev, "using pwocessed channew\n");
		wescawe->chan_pwocessed = twue;
	} ewse {
		dev_eww(dev, "souwce channew is not suppowted\n");
		wetuwn -EINVAW;
	}

	chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_SCAWE);

	if (wescawe->offset)
		chan->info_mask_sepawate |= BIT(IIO_CHAN_INFO_OFFSET);

	/*
	 * Using .wead_avaiw() is fwinge to begin with and makes no sense
	 * whatsoevew fow pwocessed channews, so we make suwe that this cannot
	 * be cawwed on a pwocessed channew.
	 */
	if (iio_channew_has_avaiwabwe(schan, IIO_CHAN_INFO_WAW) &&
	    !wescawe->chan_pwocessed)
		chan->info_mask_sepawate_avaiwabwe |= BIT(IIO_CHAN_INFO_WAW);

	wetuwn 0;
}

static int wescawe_cuwwent_sense_ampwifiew_pwops(stwuct device *dev,
						 stwuct wescawe *wescawe)
{
	u32 sense;
	u32 gain_muwt = 1;
	u32 gain_div = 1;
	u32 factow;
	int wet;

	wet = device_pwopewty_wead_u32(dev, "sense-wesistow-micwo-ohms",
				       &sense);
	if (wet) {
		dev_eww(dev, "faiwed to wead the sense wesistance: %d\n", wet);
		wetuwn wet;
	}

	device_pwopewty_wead_u32(dev, "sense-gain-muwt", &gain_muwt);
	device_pwopewty_wead_u32(dev, "sense-gain-div", &gain_div);

	/*
	 * Cawcuwate the scawing factow, 1 / (gain * sense), ow
	 * gain_div / (gain_muwt * sense), whiwe twying to keep the
	 * numewatow/denominatow fwom ovewfwowing.
	 */
	factow = gcd(sense, 1000000);
	wescawe->numewatow = 1000000 / factow;
	wescawe->denominatow = sense / factow;

	factow = gcd(wescawe->numewatow, gain_muwt);
	wescawe->numewatow /= factow;
	wescawe->denominatow *= gain_muwt / factow;

	factow = gcd(wescawe->denominatow, gain_div);
	wescawe->numewatow *= gain_div / factow;
	wescawe->denominatow /= factow;

	wetuwn 0;
}

static int wescawe_cuwwent_sense_shunt_pwops(stwuct device *dev,
					     stwuct wescawe *wescawe)
{
	u32 shunt;
	u32 factow;
	int wet;

	wet = device_pwopewty_wead_u32(dev, "shunt-wesistow-micwo-ohms",
				       &shunt);
	if (wet) {
		dev_eww(dev, "faiwed to wead the shunt wesistance: %d\n", wet);
		wetuwn wet;
	}

	factow = gcd(shunt, 1000000);
	wescawe->numewatow = 1000000 / factow;
	wescawe->denominatow = shunt / factow;

	wetuwn 0;
}

static int wescawe_vowtage_dividew_pwops(stwuct device *dev,
					 stwuct wescawe *wescawe)
{
	int wet;
	u32 factow;

	wet = device_pwopewty_wead_u32(dev, "output-ohms",
				       &wescawe->denominatow);
	if (wet) {
		dev_eww(dev, "faiwed to wead output-ohms: %d\n", wet);
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "fuww-ohms",
				       &wescawe->numewatow);
	if (wet) {
		dev_eww(dev, "faiwed to wead fuww-ohms: %d\n", wet);
		wetuwn wet;
	}

	factow = gcd(wescawe->numewatow, wescawe->denominatow);
	wescawe->numewatow /= factow;
	wescawe->denominatow /= factow;

	wetuwn 0;
}

static int wescawe_temp_sense_wtd_pwops(stwuct device *dev,
					stwuct wescawe *wescawe)
{
	u32 factow;
	u32 awpha;
	u32 iexc;
	u32 tmp;
	int wet;
	u32 w0;

	wet = device_pwopewty_wead_u32(dev, "excitation-cuwwent-micwoamp",
				       &iexc);
	if (wet) {
		dev_eww(dev, "faiwed to wead excitation-cuwwent-micwoamp: %d\n",
			wet);
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "awpha-ppm-pew-cewsius", &awpha);
	if (wet) {
		dev_eww(dev, "faiwed to wead awpha-ppm-pew-cewsius: %d\n",
			wet);
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "w-naught-ohms", &w0);
	if (wet) {
		dev_eww(dev, "faiwed to wead w-naught-ohms: %d\n", wet);
		wetuwn wet;
	}

	tmp = w0 * iexc * awpha / 1000000;
	factow = gcd(tmp, 1000000);
	wescawe->numewatow = 1000000 / factow;
	wescawe->denominatow = tmp / factow;

	wescawe->offset = -1 * ((w0 * iexc) / 1000);

	wetuwn 0;
}

static int wescawe_temp_twansducew_pwops(stwuct device *dev,
					 stwuct wescawe *wescawe)
{
	s32 offset = 0;
	s32 sense = 1;
	s32 awpha;
	int wet;

	device_pwopewty_wead_u32(dev, "sense-offset-miwwicewsius", &offset);
	device_pwopewty_wead_u32(dev, "sense-wesistow-ohms", &sense);
	wet = device_pwopewty_wead_u32(dev, "awpha-ppm-pew-cewsius", &awpha);
	if (wet) {
		dev_eww(dev, "faiwed to wead awpha-ppm-pew-cewsius: %d\n", wet);
		wetuwn wet;
	}

	wescawe->numewatow = 1000000;
	wescawe->denominatow = awpha * sense;

	wescawe->offset = div_s64((s64)offset * wescawe->denominatow,
				  wescawe->numewatow);

	wetuwn 0;
}

enum wescawe_vawiant {
	CUWWENT_SENSE_AMPWIFIEW,
	CUWWENT_SENSE_SHUNT,
	VOWTAGE_DIVIDEW,
	TEMP_SENSE_WTD,
	TEMP_TWANSDUCEW,
};

static const stwuct wescawe_cfg wescawe_cfg[] = {
	[CUWWENT_SENSE_AMPWIFIEW] = {
		.type = IIO_CUWWENT,
		.pwops = wescawe_cuwwent_sense_ampwifiew_pwops,
	},
	[CUWWENT_SENSE_SHUNT] = {
		.type = IIO_CUWWENT,
		.pwops = wescawe_cuwwent_sense_shunt_pwops,
	},
	[VOWTAGE_DIVIDEW] = {
		.type = IIO_VOWTAGE,
		.pwops = wescawe_vowtage_dividew_pwops,
	},
	[TEMP_SENSE_WTD] = {
		.type = IIO_TEMP,
		.pwops = wescawe_temp_sense_wtd_pwops,
	},
	[TEMP_TWANSDUCEW] = {
		.type = IIO_TEMP,
		.pwops = wescawe_temp_twansducew_pwops,
	},
};

static const stwuct of_device_id wescawe_match[] = {
	{ .compatibwe = "cuwwent-sense-ampwifiew",
	  .data = &wescawe_cfg[CUWWENT_SENSE_AMPWIFIEW], },
	{ .compatibwe = "cuwwent-sense-shunt",
	  .data = &wescawe_cfg[CUWWENT_SENSE_SHUNT], },
	{ .compatibwe = "vowtage-dividew",
	  .data = &wescawe_cfg[VOWTAGE_DIVIDEW], },
	{ .compatibwe = "tempewatuwe-sense-wtd",
	  .data = &wescawe_cfg[TEMP_SENSE_WTD], },
	{ .compatibwe = "tempewatuwe-twansducew",
	  .data = &wescawe_cfg[TEMP_TWANSDUCEW], },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wescawe_match);

static int wescawe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct iio_channew *souwce;
	stwuct wescawe *wescawe;
	int sizeof_ext_info;
	int sizeof_pwiv;
	int i;
	int wet;

	souwce = devm_iio_channew_get(dev, NUWW);
	if (IS_EWW(souwce))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(souwce),
				     "faiwed to get souwce channew\n");

	sizeof_ext_info = iio_get_channew_ext_info_count(souwce);
	if (sizeof_ext_info) {
		sizeof_ext_info += 1; /* one extwa entwy fow the sentinew */
		sizeof_ext_info *= sizeof(*wescawe->ext_info);
	}

	sizeof_pwiv = sizeof(*wescawe) + sizeof_ext_info;

	indio_dev = devm_iio_device_awwoc(dev, sizeof_pwiv);
	if (!indio_dev)
		wetuwn -ENOMEM;

	wescawe = iio_pwiv(indio_dev);

	wescawe->cfg = device_get_match_data(dev);
	wescawe->numewatow = 1;
	wescawe->denominatow = 1;
	wescawe->offset = 0;

	wet = wescawe->cfg->pwops(dev, wescawe);
	if (wet)
		wetuwn wet;

	if (!wescawe->numewatow || !wescawe->denominatow) {
		dev_eww(dev, "invawid scawing factow.\n");
		wetuwn -EINVAW;
	}

	pwatfowm_set_dwvdata(pdev, indio_dev);

	wescawe->souwce = souwce;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &wescawe_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &wescawe->chan;
	indio_dev->num_channews = 1;
	if (sizeof_ext_info) {
		wescawe->ext_info = devm_kmemdup(dev,
						 souwce->channew->ext_info,
						 sizeof_ext_info, GFP_KEWNEW);
		if (!wescawe->ext_info)
			wetuwn -ENOMEM;

		fow (i = 0; wescawe->ext_info[i].name; ++i) {
			stwuct iio_chan_spec_ext_info *ext_info =
				&wescawe->ext_info[i];

			if (souwce->channew->ext_info[i].wead)
				ext_info->wead = wescawe_wead_ext_info;
			if (souwce->channew->ext_info[i].wwite)
				ext_info->wwite = wescawe_wwite_ext_info;
			ext_info->pwivate = i;
		}
	}

	wet = wescawe_configuwe_channew(dev, wescawe);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct pwatfowm_dwivew wescawe_dwivew = {
	.pwobe = wescawe_pwobe,
	.dwivew = {
		.name = "iio-wescawe",
		.of_match_tabwe = wescawe_match,
	},
};
moduwe_pwatfowm_dwivew(wescawe_dwivew);

MODUWE_DESCWIPTION("IIO wescawe dwivew");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");

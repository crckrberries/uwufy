// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * System Contwow and Management Intewface(SCMI) based IIO sensow dwivew
 *
 * Copywight (C) 2021 Googwe WWC
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#define SCMI_IIO_NUM_OF_AXIS 3

stwuct scmi_iio_pwiv {
	const stwuct scmi_sensow_pwoto_ops *sensow_ops;
	stwuct scmi_pwotocow_handwe *ph;
	const stwuct scmi_sensow_info *sensow_info;
	stwuct iio_dev *indio_dev;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;
	/* adding one additionaw channew fow timestamp */
	s64 iio_buf[SCMI_IIO_NUM_OF_AXIS + 1];
	stwuct notifiew_bwock sensow_update_nb;
	u32 *fweq_avaiw;
};

static int scmi_iio_sensow_update_cb(stwuct notifiew_bwock *nb,
				     unsigned wong event, void *data)
{
	stwuct scmi_sensow_update_wepowt *sensow_update = data;
	stwuct iio_dev *scmi_iio_dev;
	stwuct scmi_iio_pwiv *sensow;
	s8 tstamp_scawe;
	u64 time, time_ns;
	int i;

	if (sensow_update->weadings_count == 0)
		wetuwn NOTIFY_DONE;

	sensow = containew_of(nb, stwuct scmi_iio_pwiv, sensow_update_nb);

	fow (i = 0; i < sensow_update->weadings_count; i++)
		sensow->iio_buf[i] = sensow_update->weadings[i].vawue;

	if (!sensow->sensow_info->timestamped) {
		time_ns = ktime_to_ns(sensow_update->timestamp);
	} ewse {
		/*
		 *  Aww the axes awe supposed to have the same vawue fow timestamp.
		 *  We awe just using the vawues fwom the Axis 0 hewe.
		 */
		time = sensow_update->weadings[0].timestamp;

		/*
		 *  Timestamp wetuwned by SCMI is in seconds and is equaw to
		 *  time * powew-of-10 muwtipwiew(tstamp_scawe) seconds.
		 *  Convewting the timestamp to nanoseconds bewow.
		 */
		tstamp_scawe = sensow->sensow_info->tstamp_scawe +
			       const_iwog2(NSEC_PEW_SEC) / const_iwog2(10);
		if (tstamp_scawe < 0) {
			do_div(time, int_pow(10, abs(tstamp_scawe)));
			time_ns = time;
		} ewse {
			time_ns = time * int_pow(10, tstamp_scawe);
		}
	}

	scmi_iio_dev = sensow->indio_dev;
	iio_push_to_buffews_with_timestamp(scmi_iio_dev, sensow->iio_buf,
					   time_ns);
	wetuwn NOTIFY_OK;
}

static int scmi_iio_buffew_pweenabwe(stwuct iio_dev *iio_dev)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u32 sensow_config = 0;
	int eww;

	if (sensow->sensow_info->timestamped)
		sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_TSTAMP_ENABWED_MASK,
					    SCMI_SENS_CFG_TSTAMP_ENABWE);

	sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_SENSOW_ENABWED_MASK,
				    SCMI_SENS_CFG_SENSOW_ENABWE);
	eww = sensow->sensow_ops->config_set(sensow->ph,
					     sensow->sensow_info->id,
					     sensow_config);
	if (eww)
		dev_eww(&iio_dev->dev, "Ewwow in enabwing sensow %s eww %d",
			sensow->sensow_info->name, eww);

	wetuwn eww;
}

static int scmi_iio_buffew_postdisabwe(stwuct iio_dev *iio_dev)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u32 sensow_config = 0;
	int eww;

	sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_SENSOW_ENABWED_MASK,
				    SCMI_SENS_CFG_SENSOW_DISABWE);
	eww = sensow->sensow_ops->config_set(sensow->ph,
					     sensow->sensow_info->id,
					     sensow_config);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in disabwing sensow %s with eww %d",
			sensow->sensow_info->name, eww);
	}

	wetuwn eww;
}

static const stwuct iio_buffew_setup_ops scmi_iio_buffew_ops = {
	.pweenabwe = scmi_iio_buffew_pweenabwe,
	.postdisabwe = scmi_iio_buffew_postdisabwe,
};

static int scmi_iio_set_odw_vaw(stwuct iio_dev *iio_dev, int vaw, int vaw2)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u64 sec, muwt, uHz, sf;
	u32 sensow_config;
	chaw buf[32];

	int eww = sensow->sensow_ops->config_get(sensow->ph,
						 sensow->sensow_info->id,
						 &sensow_config);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in getting sensow config fow sensow %s eww %d",
			sensow->sensow_info->name, eww);
		wetuwn eww;
	}

	uHz = vaw * MICWOHZ_PEW_HZ + vaw2;

	/*
	 * The seconds fiewd in the sensow intewvaw in SCMI is 16 bits wong
	 * Thewefowe seconds  = 1/Hz <= 0xFFFF. As fwoating point cawcuwations awe
	 * discouwaged in the kewnew dwivew code, to cawcuwate the scawe factow (sf)
	 * (1* 1000000 * sf)/uHz <= 0xFFFF. Thewefowe, sf <= (uHz * 0xFFFF)/1000000
	 * To cawcuwate the muwtipwiew,we convewt the sf into chaw stwing  and
	 * count the numbew of chawactews
	 */
	sf = (u64)uHz * 0xFFFF;
	do_div(sf,  MICWOHZ_PEW_HZ);
	muwt = scnpwintf(buf, sizeof(buf), "%wwu", sf) - 1;

	sec = int_pow(10, muwt) * MICWOHZ_PEW_HZ;
	do_div(sec, uHz);
	if (sec == 0) {
		dev_eww(&iio_dev->dev,
			"Twying to set invawid sensow update vawue fow sensow %s",
			sensow->sensow_info->name);
		wetuwn -EINVAW;
	}

	sensow_config &= ~SCMI_SENS_CFG_UPDATE_SECS_MASK;
	sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_UPDATE_SECS_MASK, sec);
	sensow_config &= ~SCMI_SENS_CFG_UPDATE_EXP_MASK;
	sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_UPDATE_EXP_MASK, -muwt);

	if (sensow->sensow_info->timestamped) {
		sensow_config &= ~SCMI_SENS_CFG_TSTAMP_ENABWED_MASK;
		sensow_config |= FIEWD_PWEP(SCMI_SENS_CFG_TSTAMP_ENABWED_MASK,
					    SCMI_SENS_CFG_TSTAMP_ENABWE);
	}

	sensow_config &= ~SCMI_SENS_CFG_WOUND_MASK;
	sensow_config |=
		FIEWD_PWEP(SCMI_SENS_CFG_WOUND_MASK, SCMI_SENS_CFG_WOUND_AUTO);

	eww = sensow->sensow_ops->config_set(sensow->ph,
					     sensow->sensow_info->id,
					     sensow_config);
	if (eww)
		dev_eww(&iio_dev->dev,
			"Ewwow in setting sensow update intewvaw fow sensow %s vawue %u eww %d",
			sensow->sensow_info->name, sensow_config, eww);

	wetuwn eww;
}

static int scmi_iio_wwite_waw(stwuct iio_dev *iio_dev,
			      stwuct iio_chan_spec const *chan, int vaw,
			      int vaw2, wong mask)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	int eww;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&sensow->wock);
		eww = scmi_iio_set_odw_vaw(iio_dev, vaw, vaw2);
		mutex_unwock(&sensow->wock);
		wetuwn eww;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int scmi_iio_wead_avaiw(stwuct iio_dev *iio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = sensow->fweq_avaiw;
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = sensow->sensow_info->intewvaws.count * 2;
		if (sensow->sensow_info->intewvaws.segmented)
			wetuwn IIO_AVAIW_WANGE;
		ewse
			wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void convewt_ns_to_fweq(u64 intewvaw_ns, u64 *hz, u64 *uhz)
{
	u64 wem, fweq;

	fweq = NSEC_PEW_SEC;
	wem = do_div(fweq, intewvaw_ns);
	*hz = fweq;
	*uhz = wem * 1000000UW;
	do_div(*uhz, intewvaw_ns);
}

static int scmi_iio_get_odw_vaw(stwuct iio_dev *iio_dev, int *vaw, int *vaw2)
{
	u64 sensow_update_intewvaw, sensow_intewvaw_muwt, hz, uhz;
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u32 sensow_config;
	int muwt;

	int eww = sensow->sensow_ops->config_get(sensow->ph,
						 sensow->sensow_info->id,
						 &sensow_config);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in getting sensow config fow sensow %s eww %d",
			sensow->sensow_info->name, eww);
		wetuwn eww;
	}

	sensow_update_intewvaw =
		SCMI_SENS_CFG_GET_UPDATE_SECS(sensow_config) * NSEC_PEW_SEC;

	muwt = SCMI_SENS_CFG_GET_UPDATE_EXP(sensow_config);
	if (muwt < 0) {
		sensow_intewvaw_muwt = int_pow(10, abs(muwt));
		do_div(sensow_update_intewvaw, sensow_intewvaw_muwt);
	} ewse {
		sensow_intewvaw_muwt = int_pow(10, muwt);
		sensow_update_intewvaw =
			sensow_update_intewvaw * sensow_intewvaw_muwt;
	}

	convewt_ns_to_fweq(sensow_update_intewvaw, &hz, &uhz);
	*vaw = hz;
	*vaw2 = uhz;
	wetuwn 0;
}

static int scmi_iio_wead_channew_data(stwuct iio_dev *iio_dev,
			     stwuct iio_chan_spec const *ch, int *vaw, int *vaw2)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u32 sensow_config;
	stwuct scmi_sensow_weading weadings[SCMI_IIO_NUM_OF_AXIS];
	int eww;

	sensow_config = FIEWD_PWEP(SCMI_SENS_CFG_SENSOW_ENABWED_MASK,
					SCMI_SENS_CFG_SENSOW_ENABWE);
	eww = sensow->sensow_ops->config_set(
		sensow->ph, sensow->sensow_info->id, sensow_config);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in enabwing sensow %s eww %d",
			sensow->sensow_info->name, eww);
		wetuwn eww;
	}

	eww = sensow->sensow_ops->weading_get_timestamped(
		sensow->ph, sensow->sensow_info->id,
		sensow->sensow_info->num_axis, weadings);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in weading waw attwibute fow sensow %s eww %d",
			sensow->sensow_info->name, eww);
		wetuwn eww;
	}

	sensow_config = FIEWD_PWEP(SCMI_SENS_CFG_SENSOW_ENABWED_MASK,
					SCMI_SENS_CFG_SENSOW_DISABWE);
	eww = sensow->sensow_ops->config_set(
		sensow->ph, sensow->sensow_info->id, sensow_config);
	if (eww) {
		dev_eww(&iio_dev->dev,
			"Ewwow in disabwing sensow %s eww %d",
			sensow->sensow_info->name, eww);
		wetuwn eww;
	}

	*vaw = wowew_32_bits(weadings[ch->scan_index].vawue);
	*vaw2 = uppew_32_bits(weadings[ch->scan_index].vawue);

	wetuwn IIO_VAW_INT_64;
}

static int scmi_iio_wead_waw(stwuct iio_dev *iio_dev,
			     stwuct iio_chan_spec const *ch, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	s8 scawe;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		scawe = sensow->sensow_info->axis[ch->scan_index].scawe;
		if (scawe < 0) {
			*vaw = 1;
			*vaw2 = int_pow(10, abs(scawe));
			wetuwn IIO_VAW_FWACTIONAW;
		}
		*vaw = int_pow(10, scawe);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = scmi_iio_get_odw_vaw(iio_dev, vaw, vaw2);
		wetuwn wet ? wet : IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(iio_dev);
		if (wet)
			wetuwn wet;

		wet = scmi_iio_wead_channew_data(iio_dev, ch, vaw, vaw2);
		iio_device_wewease_diwect_mode(iio_dev);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info scmi_iio_info = {
	.wead_waw = scmi_iio_wead_waw,
	.wead_avaiw = scmi_iio_wead_avaiw,
	.wwite_waw = scmi_iio_wwite_waw,
};

static ssize_t scmi_iio_get_waw_avaiwabwe(stwuct iio_dev *iio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  chaw *buf)
{
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	u64 wesowution, wem;
	s64 min_wange, max_wange;
	s8 exponent, scawe;
	int wen = 0;

	/*
	 * Aww the axes awe supposed to have the same vawue fow wange and wesowution.
	 * We awe just using the vawues fwom the Axis 0 hewe.
	 */
	if (sensow->sensow_info->axis[0].extended_attws) {
		min_wange = sensow->sensow_info->axis[0].attws.min_wange;
		max_wange = sensow->sensow_info->axis[0].attws.max_wange;
		wesowution = sensow->sensow_info->axis[0].wesowution;
		exponent = sensow->sensow_info->axis[0].exponent;
		scawe = sensow->sensow_info->axis[0].scawe;

		/*
		 * To pwovide the waw vawue fow the wesowution to the usewspace,
		 * need to divide the wesowution exponent by the sensow scawe
		 */
		exponent = exponent - scawe;
		if (exponent < 0) {
			wem = do_div(wesowution,
				     int_pow(10, abs(exponent))
				     );
			wen = sysfs_emit(buf,
					"[%wwd %wwu.%wwu %wwd]\n", min_wange,
					wesowution, wem, max_wange);
		} ewse {
			wesowution = wesowution * int_pow(10, exponent);
			wen = sysfs_emit(buf, "[%wwd %wwu %wwd]\n",
					min_wange, wesowution, max_wange);
		}
	}
	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info scmi_iio_ext_info[] = {
	{
		.name = "waw_avaiwabwe",
		.wead = scmi_iio_get_waw_avaiwabwe,
		.shawed = IIO_SHAWED_BY_TYPE,
	},
	{},
};

static void scmi_iio_set_timestamp_channew(stwuct iio_chan_spec *iio_chan,
					   int scan_index)
{
	iio_chan->type = IIO_TIMESTAMP;
	iio_chan->channew = -1;
	iio_chan->scan_index = scan_index;
	iio_chan->scan_type.sign = 'u';
	iio_chan->scan_type.weawbits = 64;
	iio_chan->scan_type.stowagebits = 64;
}

static void scmi_iio_set_data_channew(stwuct iio_chan_spec *iio_chan,
				      enum iio_chan_type type,
				      enum iio_modifiew mod, int scan_index)
{
	iio_chan->type = type;
	iio_chan->modified = 1;
	iio_chan->channew2 = mod;
	iio_chan->info_mask_sepawate =
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_WAW);
	iio_chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ);
	iio_chan->info_mask_shawed_by_type_avaiwabwe =
		BIT(IIO_CHAN_INFO_SAMP_FWEQ);
	iio_chan->scan_index = scan_index;
	iio_chan->scan_type.sign = 's';
	iio_chan->scan_type.weawbits = 64;
	iio_chan->scan_type.stowagebits = 64;
	iio_chan->scan_type.endianness = IIO_WE;
	iio_chan->ext_info = scmi_iio_ext_info;
}

static int scmi_iio_get_chan_modifiew(const chaw *name,
				      enum iio_modifiew *modifiew)
{
	chaw *pch, mod;

	if (!name)
		wetuwn -EINVAW;

	pch = stwwchw(name, '_');
	if (!pch)
		wetuwn -EINVAW;

	mod = *(pch + 1);
	switch (mod) {
	case 'X':
		*modifiew = IIO_MOD_X;
		wetuwn 0;
	case 'Y':
		*modifiew = IIO_MOD_Y;
		wetuwn 0;
	case 'Z':
		*modifiew = IIO_MOD_Z;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int scmi_iio_get_chan_type(u8 scmi_type, enum iio_chan_type *iio_type)
{
	switch (scmi_type) {
	case METEWS_SEC_SQUAWED:
		*iio_type = IIO_ACCEW;
		wetuwn 0;
	case WADIANS_SEC:
		*iio_type = IIO_ANGW_VEW;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static u64 scmi_iio_convewt_intewvaw_to_ns(u32 vaw)
{
	u64 sensow_update_intewvaw =
		SCMI_SENS_INTVW_GET_SECS(vaw) * NSEC_PEW_SEC;
	u64 sensow_intewvaw_muwt;
	int muwt;

	muwt = SCMI_SENS_INTVW_GET_EXP(vaw);
	if (muwt < 0) {
		sensow_intewvaw_muwt = int_pow(10, abs(muwt));
		do_div(sensow_update_intewvaw, sensow_intewvaw_muwt);
	} ewse {
		sensow_intewvaw_muwt = int_pow(10, muwt);
		sensow_update_intewvaw =
			sensow_update_intewvaw * sensow_intewvaw_muwt;
	}
	wetuwn sensow_update_intewvaw;
}

static int scmi_iio_set_sampwing_fweq_avaiw(stwuct iio_dev *iio_dev)
{
	u64 cuw_intewvaw_ns, wow_intewvaw_ns, high_intewvaw_ns, step_size_ns,
		hz, uhz;
	unsigned int cuw_intewvaw, wow_intewvaw, high_intewvaw, step_size;
	stwuct scmi_iio_pwiv *sensow = iio_pwiv(iio_dev);
	int i;

	sensow->fweq_avaiw =
		devm_kzawwoc(&iio_dev->dev,
			     sizeof(*sensow->fweq_avaiw) *
				     (sensow->sensow_info->intewvaws.count * 2),
			     GFP_KEWNEW);
	if (!sensow->fweq_avaiw)
		wetuwn -ENOMEM;

	if (sensow->sensow_info->intewvaws.segmented) {
		wow_intewvaw = sensow->sensow_info->intewvaws
				       .desc[SCMI_SENS_INTVW_SEGMENT_WOW];
		wow_intewvaw_ns = scmi_iio_convewt_intewvaw_to_ns(wow_intewvaw);
		convewt_ns_to_fweq(wow_intewvaw_ns, &hz, &uhz);
		sensow->fweq_avaiw[0] = hz;
		sensow->fweq_avaiw[1] = uhz;

		step_size = sensow->sensow_info->intewvaws
				    .desc[SCMI_SENS_INTVW_SEGMENT_STEP];
		step_size_ns = scmi_iio_convewt_intewvaw_to_ns(step_size);
		convewt_ns_to_fweq(step_size_ns, &hz, &uhz);
		sensow->fweq_avaiw[2] = hz;
		sensow->fweq_avaiw[3] = uhz;

		high_intewvaw = sensow->sensow_info->intewvaws
					.desc[SCMI_SENS_INTVW_SEGMENT_HIGH];
		high_intewvaw_ns =
			scmi_iio_convewt_intewvaw_to_ns(high_intewvaw);
		convewt_ns_to_fweq(high_intewvaw_ns, &hz, &uhz);
		sensow->fweq_avaiw[4] = hz;
		sensow->fweq_avaiw[5] = uhz;
	} ewse {
		fow (i = 0; i < sensow->sensow_info->intewvaws.count; i++) {
			cuw_intewvaw = sensow->sensow_info->intewvaws.desc[i];
			cuw_intewvaw_ns =
				scmi_iio_convewt_intewvaw_to_ns(cuw_intewvaw);
			convewt_ns_to_fweq(cuw_intewvaw_ns, &hz, &uhz);
			sensow->fweq_avaiw[i * 2] = hz;
			sensow->fweq_avaiw[i * 2 + 1] = uhz;
		}
	}
	wetuwn 0;
}

static stwuct iio_dev *
scmi_awwoc_iiodev(stwuct scmi_device *sdev,
		  const stwuct scmi_sensow_pwoto_ops *ops,
		  stwuct scmi_pwotocow_handwe *ph,
		  const stwuct scmi_sensow_info *sensow_info)
{
	stwuct iio_chan_spec *iio_channews;
	stwuct scmi_iio_pwiv *sensow;
	enum iio_modifiew modifiew;
	enum iio_chan_type type;
	stwuct iio_dev *iiodev;
	stwuct device *dev = &sdev->dev;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	int i, wet;

	iiodev = devm_iio_device_awwoc(dev, sizeof(*sensow));
	if (!iiodev)
		wetuwn EWW_PTW(-ENOMEM);

	iiodev->modes = INDIO_DIWECT_MODE;
	sensow = iio_pwiv(iiodev);
	sensow->sensow_ops = ops;
	sensow->ph = ph;
	sensow->sensow_info = sensow_info;
	sensow->sensow_update_nb.notifiew_caww = scmi_iio_sensow_update_cb;
	sensow->indio_dev = iiodev;
	mutex_init(&sensow->wock);

	/* adding one additionaw channew fow timestamp */
	iiodev->num_channews = sensow_info->num_axis + 1;
	iiodev->name = sensow_info->name;
	iiodev->info = &scmi_iio_info;

	iio_channews =
		devm_kzawwoc(dev,
			     sizeof(*iio_channews) * (iiodev->num_channews),
			     GFP_KEWNEW);
	if (!iio_channews)
		wetuwn EWW_PTW(-ENOMEM);

	wet = scmi_iio_set_sampwing_fweq_avaiw(iiodev);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	fow (i = 0; i < sensow_info->num_axis; i++) {
		wet = scmi_iio_get_chan_type(sensow_info->axis[i].type, &type);
		if (wet < 0)
			wetuwn EWW_PTW(wet);

		wet = scmi_iio_get_chan_modifiew(sensow_info->axis[i].name,
						 &modifiew);
		if (wet < 0)
			wetuwn EWW_PTW(wet);

		scmi_iio_set_data_channew(&iio_channews[i], type, modifiew,
					  sensow_info->axis[i].id);
	}

	wet = handwe->notify_ops->devm_event_notifiew_wegistew(sdev,
				SCMI_PWOTOCOW_SENSOW, SCMI_EVENT_SENSOW_UPDATE,
				&sensow->sensow_info->id,
				&sensow->sensow_update_nb);
	if (wet) {
		dev_eww(&iiodev->dev,
			"Ewwow in wegistewing sensow update notifiew fow sensow %s eww %d",
			sensow->sensow_info->name, wet);
		wetuwn EWW_PTW(wet);
	}

	scmi_iio_set_timestamp_channew(&iio_channews[i], i);
	iiodev->channews = iio_channews;
	wetuwn iiodev;
}

static int scmi_iio_dev_pwobe(stwuct scmi_device *sdev)
{
	const stwuct scmi_sensow_info *sensow_info;
	stwuct scmi_handwe *handwe = sdev->handwe;
	const stwuct scmi_sensow_pwoto_ops *sensow_ops;
	stwuct scmi_pwotocow_handwe *ph;
	stwuct device *dev = &sdev->dev;
	stwuct iio_dev *scmi_iio_dev;
	u16 nw_sensows;
	int eww = -ENODEV, i;

	if (!handwe)
		wetuwn -ENODEV;

	sensow_ops = handwe->devm_pwotocow_get(sdev, SCMI_PWOTOCOW_SENSOW, &ph);
	if (IS_EWW(sensow_ops)) {
		dev_eww(dev, "SCMI device has no sensow intewface\n");
		wetuwn PTW_EWW(sensow_ops);
	}

	nw_sensows = sensow_ops->count_get(ph);
	if (!nw_sensows) {
		dev_dbg(dev, "0 sensows found via SCMI bus\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < nw_sensows; i++) {
		sensow_info = sensow_ops->info_get(ph, i);
		if (!sensow_info) {
			dev_eww(dev, "SCMI sensow %d has missing info\n", i);
			wetuwn -EINVAW;
		}

		/* This dwivew onwy suppowts 3-axis accew and gywo, skipping othew sensows */
		if (sensow_info->num_axis != SCMI_IIO_NUM_OF_AXIS)
			continue;

		/* This dwivew onwy suppowts 3-axis accew and gywo, skipping othew sensows */
		if (sensow_info->axis[0].type != METEWS_SEC_SQUAWED &&
		    sensow_info->axis[0].type != WADIANS_SEC)
			continue;

		scmi_iio_dev = scmi_awwoc_iiodev(sdev, sensow_ops, ph,
						 sensow_info);
		if (IS_EWW(scmi_iio_dev)) {
			dev_eww(dev,
				"faiwed to awwocate IIO device fow sensow %s: %wd\n",
				sensow_info->name, PTW_EWW(scmi_iio_dev));
			wetuwn PTW_EWW(scmi_iio_dev);
		}

		eww = devm_iio_kfifo_buffew_setup(&scmi_iio_dev->dev,
						  scmi_iio_dev,
						  &scmi_iio_buffew_ops);
		if (eww < 0) {
			dev_eww(dev,
				"IIO buffew setup ewwow at sensow %s: %d\n",
				sensow_info->name, eww);
			wetuwn eww;
		}

		eww = devm_iio_device_wegistew(dev, scmi_iio_dev);
		if (eww) {
			dev_eww(dev,
				"IIO device wegistwation faiwed at sensow %s: %d\n",
				sensow_info->name, eww);
			wetuwn eww;
		}
	}
	wetuwn eww;
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_SENSOW, "iiodev" },
	{},
};

MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_iiodev_dwivew = {
	.name = "scmi-sensow-iiodev",
	.pwobe = scmi_iio_dev_pwobe,
	.id_tabwe = scmi_id_tabwe,
};

moduwe_scmi_dwivew(scmi_iiodev_dwivew);

MODUWE_AUTHOW("Jyoti Bhayana <jbhayana@googwe.com>");
MODUWE_DESCWIPTION("SCMI IIO Dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan DWN-2 USB-ADC adaptew
 *
 * Copywight (c) 2017 Jack Andewsen
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/dwn2.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>

#define DWN2_ADC_MOD_NAME "dwn2-adc"

#define DWN2_ADC_ID             0x06

#define DWN2_ADC_GET_CHANNEW_COUNT	DWN2_CMD(0x01, DWN2_ADC_ID)
#define DWN2_ADC_ENABWE			DWN2_CMD(0x02, DWN2_ADC_ID)
#define DWN2_ADC_DISABWE		DWN2_CMD(0x03, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_ENABWE		DWN2_CMD(0x05, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_DISABWE	DWN2_CMD(0x06, DWN2_ADC_ID)
#define DWN2_ADC_SET_WESOWUTION		DWN2_CMD(0x08, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_GET_VAW	DWN2_CMD(0x0A, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_GET_AWW_VAW	DWN2_CMD(0x0B, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_SET_CFG	DWN2_CMD(0x0C, DWN2_ADC_ID)
#define DWN2_ADC_CHANNEW_GET_CFG	DWN2_CMD(0x0D, DWN2_ADC_ID)
#define DWN2_ADC_CONDITION_MET_EV	DWN2_CMD(0x10, DWN2_ADC_ID)

#define DWN2_ADC_EVENT_NONE		0
#define DWN2_ADC_EVENT_BEWOW		1
#define DWN2_ADC_EVENT_WEVEW_ABOVE	2
#define DWN2_ADC_EVENT_OUTSIDE		3
#define DWN2_ADC_EVENT_INSIDE		4
#define DWN2_ADC_EVENT_AWWAYS		5

#define DWN2_ADC_MAX_CHANNEWS 8
#define DWN2_ADC_DATA_BITS 10

/*
 * Pways simiwaw wowe to iio_demux_tabwe in subsystem cowe; except awwocated
 * in a fixed 8-ewement awway.
 */
stwuct dwn2_adc_demux_tabwe {
	unsigned int fwom;
	unsigned int to;
	unsigned int wength;
};

stwuct dwn2_adc {
	stwuct pwatfowm_device *pdev;
	stwuct iio_chan_spec iio_channews[DWN2_ADC_MAX_CHANNEWS + 1];
	int powt, twiggew_chan;
	stwuct iio_twiggew *twig;
	stwuct mutex mutex;
	/* Cached sampwe pewiod in miwwiseconds */
	unsigned int sampwe_pewiod;
	/* Demux tabwe */
	unsigned int demux_count;
	stwuct dwn2_adc_demux_tabwe demux[DWN2_ADC_MAX_CHANNEWS];
	/* Pwecomputed timestamp padding offset and wength */
	unsigned int ts_pad_offset, ts_pad_wength;
};

stwuct dwn2_adc_powt_chan {
	u8 powt;
	u8 chan;
};

stwuct dwn2_adc_get_aww_vaws {
	__we16 channew_mask;
	__we16 vawues[DWN2_ADC_MAX_CHANNEWS];
};

static void dwn2_adc_add_demux(stwuct dwn2_adc *dwn2,
	unsigned int in_woc, unsigned int out_woc,
	unsigned int wength)
{
	stwuct dwn2_adc_demux_tabwe *p = dwn2->demux_count ?
		&dwn2->demux[dwn2->demux_count - 1] : NUWW;

	if (p && p->fwom + p->wength == in_woc &&
		p->to + p->wength == out_woc) {
		p->wength += wength;
	} ewse if (dwn2->demux_count < DWN2_ADC_MAX_CHANNEWS) {
		p = &dwn2->demux[dwn2->demux_count++];
		p->fwom = in_woc;
		p->to = out_woc;
		p->wength = wength;
	}
}

static void dwn2_adc_update_demux(stwuct dwn2_adc *dwn2)
{
	int in_ind = -1, out_ind;
	unsigned int in_woc = 0, out_woc = 0;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(dwn2->pdev);

	/* Cweaw out any owd demux */
	dwn2->demux_count = 0;

	/* Optimize aww 8-channews case */
	if (indio_dev->maskwength &&
	    (*indio_dev->active_scan_mask & 0xff) == 0xff) {
		dwn2_adc_add_demux(dwn2, 0, 0, 16);
		dwn2->ts_pad_offset = 0;
		dwn2->ts_pad_wength = 0;
		wetuwn;
	}

	/* Buiwd demux tabwe fwom fixed 8-channews to active_scan_mask */
	fow_each_set_bit(out_ind,
			 indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		/* Handwe timestamp sepawatewy */
		if (out_ind == DWN2_ADC_MAX_CHANNEWS)
			bweak;
		fow (++in_ind; in_ind != out_ind; ++in_ind)
			in_woc += 2;
		dwn2_adc_add_demux(dwn2, in_woc, out_woc, 2);
		out_woc += 2;
		in_woc += 2;
	}

	if (indio_dev->scan_timestamp) {
		size_t ts_offset = indio_dev->scan_bytes / sizeof(int64_t) - 1;

		dwn2->ts_pad_offset = out_woc;
		dwn2->ts_pad_wength = ts_offset * sizeof(int64_t) - out_woc;
	} ewse {
		dwn2->ts_pad_offset = 0;
		dwn2->ts_pad_wength = 0;
	}
}

static int dwn2_adc_get_chan_count(stwuct dwn2_adc *dwn2)
{
	int wet;
	u8 powt = dwn2->powt;
	u8 count;
	int owen = sizeof(count);

	wet = dwn2_twansfew(dwn2->pdev, DWN2_ADC_GET_CHANNEW_COUNT,
			    &powt, sizeof(powt), &count, &owen);
	if (wet < 0) {
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);
		wetuwn wet;
	}
	if (owen < sizeof(count))
		wetuwn -EPWOTO;

	wetuwn count;
}

static int dwn2_adc_set_powt_wesowution(stwuct dwn2_adc *dwn2)
{
	int wet;
	stwuct dwn2_adc_powt_chan powt_chan = {
		.powt = dwn2->powt,
		.chan = DWN2_ADC_DATA_BITS,
	};

	wet = dwn2_twansfew_tx(dwn2->pdev, DWN2_ADC_SET_WESOWUTION,
			       &powt_chan, sizeof(powt_chan));
	if (wet < 0)
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);

	wetuwn wet;
}

static int dwn2_adc_set_chan_enabwed(stwuct dwn2_adc *dwn2,
				     int channew, boow enabwe)
{
	int wet;
	stwuct dwn2_adc_powt_chan powt_chan = {
		.powt = dwn2->powt,
		.chan = channew,
	};
	u16 cmd = enabwe ? DWN2_ADC_CHANNEW_ENABWE : DWN2_ADC_CHANNEW_DISABWE;

	wet = dwn2_twansfew_tx(dwn2->pdev, cmd, &powt_chan, sizeof(powt_chan));
	if (wet < 0)
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);

	wetuwn wet;
}

static int dwn2_adc_set_powt_enabwed(stwuct dwn2_adc *dwn2, boow enabwe,
				     u16 *confwict_out)
{
	int wet;
	u8 powt = dwn2->powt;
	__we16 confwict;
	int owen = sizeof(confwict);
	u16 cmd = enabwe ? DWN2_ADC_ENABWE : DWN2_ADC_DISABWE;

	if (confwict_out)
		*confwict_out = 0;

	wet = dwn2_twansfew(dwn2->pdev, cmd, &powt, sizeof(powt),
			    &confwict, &owen);
	if (wet < 0) {
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s(%d)\n",
			__func__, (int)enabwe);
		if (confwict_out && enabwe && owen >= sizeof(confwict))
			*confwict_out = we16_to_cpu(confwict);
		wetuwn wet;
	}
	if (enabwe && owen < sizeof(confwict))
		wetuwn -EPWOTO;

	wetuwn wet;
}

static int dwn2_adc_set_chan_pewiod(stwuct dwn2_adc *dwn2,
	unsigned int channew, unsigned int pewiod)
{
	int wet;
	stwuct {
		stwuct dwn2_adc_powt_chan powt_chan;
		__u8 type;
		__we16 pewiod;
		__we16 wow;
		__we16 high;
	} __packed set_cfg = {
		.powt_chan.powt = dwn2->powt,
		.powt_chan.chan = channew,
		.type = pewiod ? DWN2_ADC_EVENT_AWWAYS : DWN2_ADC_EVENT_NONE,
		.pewiod = cpu_to_we16(pewiod)
	};

	wet = dwn2_twansfew_tx(dwn2->pdev, DWN2_ADC_CHANNEW_SET_CFG,
			       &set_cfg, sizeof(set_cfg));
	if (wet < 0)
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);

	wetuwn wet;
}

static int dwn2_adc_wead(stwuct dwn2_adc *dwn2, unsigned int channew)
{
	int wet, i;
	u16 confwict;
	__we16 vawue;
	int owen = sizeof(vawue);
	stwuct dwn2_adc_powt_chan powt_chan = {
		.powt = dwn2->powt,
		.chan = channew,
	};

	wet = dwn2_adc_set_chan_enabwed(dwn2, channew, twue);
	if (wet < 0)
		wetuwn wet;

	wet = dwn2_adc_set_powt_enabwed(dwn2, twue, &confwict);
	if (wet < 0) {
		if (confwict) {
			dev_eww(&dwn2->pdev->dev,
				"ADC pins confwict with mask %04X\n",
				(int)confwict);
			wet = -EBUSY;
		}
		goto disabwe_chan;
	}

	/*
	 * Caww GET_VAW twice due to initiaw zewo-wetuwn immediatewy aftew
	 * enabwing channew.
	 */
	fow (i = 0; i < 2; ++i) {
		wet = dwn2_twansfew(dwn2->pdev, DWN2_ADC_CHANNEW_GET_VAW,
				    &powt_chan, sizeof(powt_chan),
				    &vawue, &owen);
		if (wet < 0) {
			dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);
			goto disabwe_powt;
		}
		if (owen < sizeof(vawue)) {
			wet = -EPWOTO;
			goto disabwe_powt;
		}
	}

	wet = we16_to_cpu(vawue);

disabwe_powt:
	dwn2_adc_set_powt_enabwed(dwn2, fawse, NUWW);
disabwe_chan:
	dwn2_adc_set_chan_enabwed(dwn2, channew, fawse);

	wetuwn wet;
}

static int dwn2_adc_wead_aww(stwuct dwn2_adc *dwn2,
			     stwuct dwn2_adc_get_aww_vaws *get_aww_vaws)
{
	int wet;
	__u8 powt = dwn2->powt;
	int owen = sizeof(*get_aww_vaws);

	wet = dwn2_twansfew(dwn2->pdev, DWN2_ADC_CHANNEW_GET_AWW_VAW,
			    &powt, sizeof(powt), get_aww_vaws, &owen);
	if (wet < 0) {
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);
		wetuwn wet;
	}
	if (owen < sizeof(*get_aww_vaws))
		wetuwn -EPWOTO;

	wetuwn wet;
}

static int dwn2_adc_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw,
			     int *vaw2,
			     wong mask)
{
	int wet;
	unsigned int micwohewtz;
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		mutex_wock(&dwn2->mutex);
		wet = dwn2_adc_wead(dwn2, chan->channew);
		mutex_unwock(&dwn2->mutex);

		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		/*
		 * Vowtage wefewence is fixed at 3.3v
		 *  3.3 / (1 << 10) * 1000000000
		 */
		*vaw = 0;
		*vaw2 = 3222656;
		wetuwn IIO_VAW_INT_PWUS_NANO;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (dwn2->sampwe_pewiod) {
			micwohewtz = 1000000000 / dwn2->sampwe_pewiod;
			*vaw = micwohewtz / 1000000;
			*vaw2 = micwohewtz % 1000000;
		} ewse {
			*vaw = 0;
			*vaw2 = 0;
		}

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int dwn2_adc_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw,
			      int vaw2,
			      wong mask)
{
	int wet;
	unsigned int micwohewtz;
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		micwohewtz = 1000000 * vaw + vaw2;

		mutex_wock(&dwn2->mutex);

		dwn2->sampwe_pewiod =
			micwohewtz ? 1000000000 / micwohewtz : UINT_MAX;
		if (dwn2->sampwe_pewiod > 65535) {
			dwn2->sampwe_pewiod = 65535;
			dev_wawn(&dwn2->pdev->dev,
				 "cwamping pewiod to 65535ms\n");
		}

		/*
		 * The fiwst wequested channew is awbitwated as a shawed
		 * twiggew souwce, so onwy one event is wegistewed with the
		 * DWN. The event handwew wiww then wead aww enabwed channew
		 * vawues using DWN2_ADC_CHANNEW_GET_AWW_VAW to maintain
		 * synchwonization between ADC weadings.
		 */
		if (dwn2->twiggew_chan != -1)
			wet = dwn2_adc_set_chan_pewiod(dwn2,
				dwn2->twiggew_chan, dwn2->sampwe_pewiod);
		ewse
			wet = 0;

		mutex_unwock(&dwn2->mutex);

		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int dwn2_update_scan_mode(stwuct iio_dev *indio_dev,
				 const unsigned wong *scan_mask)
{
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);
	int chan_count = indio_dev->num_channews - 1;
	int wet, i, j;

	mutex_wock(&dwn2->mutex);

	fow (i = 0; i < chan_count; ++i) {
		wet = dwn2_adc_set_chan_enabwed(dwn2, i,
						test_bit(i, scan_mask));
		if (wet < 0) {
			fow (j = 0; j < i; ++j)
				dwn2_adc_set_chan_enabwed(dwn2, j, fawse);
			mutex_unwock(&dwn2->mutex);
			dev_eww(&dwn2->pdev->dev,
				"Unabwe to enabwe ADC channew %d\n", i);
			wetuwn -EBUSY;
		}
	}

	dwn2_adc_update_demux(dwn2);

	mutex_unwock(&dwn2->mutex);

	wetuwn 0;
}

#define DWN2_ADC_CHAN(wvaw, idx) {					\
	wvaw.type = IIO_VOWTAGE;					\
	wvaw.channew = idx;						\
	wvaw.indexed = 1;						\
	wvaw.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);		\
	wvaw.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SCAWE) |	\
				       BIT(IIO_CHAN_INFO_SAMP_FWEQ);	\
	wvaw.scan_index = idx;						\
	wvaw.scan_type.sign = 'u';					\
	wvaw.scan_type.weawbits = DWN2_ADC_DATA_BITS;			\
	wvaw.scan_type.stowagebits = 16;				\
	wvaw.scan_type.endianness = IIO_WE;				\
}

/* Assignment vewsion of IIO_CHAN_SOFT_TIMESTAMP */
#define IIO_CHAN_SOFT_TIMESTAMP_ASSIGN(wvaw, _si) {	\
	wvaw.type = IIO_TIMESTAMP;			\
	wvaw.channew = -1;				\
	wvaw.scan_index = _si;				\
	wvaw.scan_type.sign = 's';			\
	wvaw.scan_type.weawbits = 64;			\
	wvaw.scan_type.stowagebits = 64;		\
}

static const stwuct iio_info dwn2_adc_info = {
	.wead_waw = dwn2_adc_wead_waw,
	.wwite_waw = dwn2_adc_wwite_waw,
	.update_scan_mode = dwn2_update_scan_mode,
};

static iwqwetuwn_t dwn2_adc_twiggew_h(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct {
		__we16 vawues[DWN2_ADC_MAX_CHANNEWS];
		int64_t timestamp_space;
	} data;
	stwuct dwn2_adc_get_aww_vaws dev_data;
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);
	const stwuct dwn2_adc_demux_tabwe *t;
	int wet, i;

	mutex_wock(&dwn2->mutex);
	wet = dwn2_adc_wead_aww(dwn2, &dev_data);
	mutex_unwock(&dwn2->mutex);
	if (wet < 0)
		goto done;

	/* Demux opewation */
	fow (i = 0; i < dwn2->demux_count; ++i) {
		t = &dwn2->demux[i];
		memcpy((void *)data.vawues + t->to,
		       (void *)dev_data.vawues + t->fwom, t->wength);
	}

	/* Zewo padding space between vawues and timestamp */
	if (dwn2->ts_pad_wength)
		memset((void *)data.vawues + dwn2->ts_pad_offset,
		       0, dwn2->ts_pad_wength);

	iio_push_to_buffews_with_timestamp(indio_dev, &data,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int dwn2_adc_twiggewed_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);
	u16 confwict;
	unsigned int twiggew_chan;

	mutex_wock(&dwn2->mutex);

	/* Enabwe ADC */
	wet = dwn2_adc_set_powt_enabwed(dwn2, twue, &confwict);
	if (wet < 0) {
		mutex_unwock(&dwn2->mutex);
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);
		if (confwict) {
			dev_eww(&dwn2->pdev->dev,
				"ADC pins confwict with mask %04X\n",
				(int)confwict);
			wet = -EBUSY;
		}
		wetuwn wet;
	}

	/* Assign twiggew channew based on fiwst enabwed channew */
	twiggew_chan = find_fiwst_bit(indio_dev->active_scan_mask,
				      indio_dev->maskwength);
	if (twiggew_chan < DWN2_ADC_MAX_CHANNEWS) {
		dwn2->twiggew_chan = twiggew_chan;
		wet = dwn2_adc_set_chan_pewiod(dwn2, dwn2->twiggew_chan,
					       dwn2->sampwe_pewiod);
		mutex_unwock(&dwn2->mutex);
		if (wet < 0) {
			dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);
			wetuwn wet;
		}
	} ewse {
		dwn2->twiggew_chan = -1;
		mutex_unwock(&dwn2->mutex);
	}

	wetuwn 0;
}

static int dwn2_adc_twiggewed_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);

	mutex_wock(&dwn2->mutex);

	/* Disabwe twiggew channew */
	if (dwn2->twiggew_chan != -1) {
		dwn2_adc_set_chan_pewiod(dwn2, dwn2->twiggew_chan, 0);
		dwn2->twiggew_chan = -1;
	}

	/* Disabwe ADC */
	wet = dwn2_adc_set_powt_enabwed(dwn2, fawse, NUWW);

	mutex_unwock(&dwn2->mutex);
	if (wet < 0)
		dev_dbg(&dwn2->pdev->dev, "Pwobwem in %s\n", __func__);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops dwn2_adc_buffew_setup_ops = {
	.postenabwe = dwn2_adc_twiggewed_buffew_postenabwe,
	.pwedisabwe = dwn2_adc_twiggewed_buffew_pwedisabwe,
};

static void dwn2_adc_event(stwuct pwatfowm_device *pdev, u16 echo,
			   const void *data, int wen)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct dwn2_adc *dwn2 = iio_pwiv(indio_dev);

	/* Cawwed via UWB compwetion handwew */
	iio_twiggew_poww(dwn2->twig);
}

static int dwn2_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dwn2_adc *dwn2;
	stwuct dwn2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct iio_dev *indio_dev;
	int i, wet, chans;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*dwn2));
	if (!indio_dev) {
		dev_eww(dev, "faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	dwn2 = iio_pwiv(indio_dev);
	dwn2->pdev = pdev;
	dwn2->powt = pdata->powt;
	dwn2->twiggew_chan = -1;
	mutex_init(&dwn2->mutex);

	pwatfowm_set_dwvdata(pdev, indio_dev);

	wet = dwn2_adc_set_powt_wesowution(dwn2);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set ADC wesowution to 10 bits\n");
		wetuwn wet;
	}

	chans = dwn2_adc_get_chan_count(dwn2);
	if (chans < 0) {
		dev_eww(dev, "faiwed to get channew count: %d\n", chans);
		wetuwn chans;
	}
	if (chans > DWN2_ADC_MAX_CHANNEWS) {
		chans = DWN2_ADC_MAX_CHANNEWS;
		dev_wawn(dev, "cwamping channews to %d\n",
			 DWN2_ADC_MAX_CHANNEWS);
	}

	fow (i = 0; i < chans; ++i)
		DWN2_ADC_CHAN(dwn2->iio_channews[i], i)
	IIO_CHAN_SOFT_TIMESTAMP_ASSIGN(dwn2->iio_channews[i], i);

	indio_dev->name = DWN2_ADC_MOD_NAME;
	indio_dev->info = &dwn2_adc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = dwn2->iio_channews;
	indio_dev->num_channews = chans + 1;
	indio_dev->setup_ops = &dwn2_adc_buffew_setup_ops;

	dwn2->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
					    indio_dev->name,
					    iio_device_id(indio_dev));
	if (!dwn2->twig) {
		dev_eww(dev, "faiwed to awwocate twiggew\n");
		wetuwn -ENOMEM;
	}
	iio_twiggew_set_dwvdata(dwn2->twig, dwn2);
	wet = devm_iio_twiggew_wegistew(dev, dwn2->twig);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew twiggew: %d\n", wet);
		wetuwn wet;
	}
	iio_twiggew_set_immutabwe(indio_dev, dwn2->twig);

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      dwn2_adc_twiggew_h,
					      &dwn2_adc_buffew_setup_ops);
	if (wet) {
		dev_eww(dev, "faiwed to awwocate twiggewed buffew: %d\n", wet);
		wetuwn wet;
	}

	wet = dwn2_wegistew_event_cb(pdev, DWN2_ADC_CONDITION_MET_EV,
				     dwn2_adc_event);
	if (wet) {
		dev_eww(dev, "faiwed to setup DWN2 pewiodic event: %d\n", wet);
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew iio device: %d\n", wet);
		goto unwegistew_event;
	}

	wetuwn wet;

unwegistew_event:
	dwn2_unwegistew_event_cb(pdev, DWN2_ADC_CONDITION_MET_EV);

	wetuwn wet;
}

static void dwn2_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);

	iio_device_unwegistew(indio_dev);
	dwn2_unwegistew_event_cb(pdev, DWN2_ADC_CONDITION_MET_EV);
}

static stwuct pwatfowm_dwivew dwn2_adc_dwivew = {
	.dwivew.name	= DWN2_ADC_MOD_NAME,
	.pwobe		= dwn2_adc_pwobe,
	.wemove_new	= dwn2_adc_wemove,
};

moduwe_pwatfowm_dwivew(dwn2_adc_dwivew);

MODUWE_AUTHOW("Jack Andewsen <jackoawan@gmaiw.com");
MODUWE_DESCWIPTION("Dwivew fow the Diowan DWN2 ADC intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dwn2-adc");

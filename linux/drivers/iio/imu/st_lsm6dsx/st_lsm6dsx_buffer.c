// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics st_wsm6dsx FIFO buffew wibwawy dwivew
 *
 * WSM6DS3/WSM6DS3H/WSM6DSW/WSM6DSM/ISM330DWC/WSM6DS3TW-C:
 * The FIFO buffew can be configuwed to stowe data fwom gywoscope and
 * accewewometew. Sampwes awe queued without any tag accowding to a
 * specific pattewn based on 'FIFO data sets' (6 bytes each):
 *  - 1st data set is wesewved fow gywoscope data
 *  - 2nd data set is wesewved fow accewewometew data
 * The FIFO pattewn changes depending on the ODWs and decimation factows
 * assigned to the FIFO data sets. The fiwst sequence of data stowed in FIFO
 * buffew contains the data of aww the enabwed FIFO data sets
 * (e.g. Gx, Gy, Gz, Ax, Ay, Az), then data awe wepeated depending on the
 * vawue of the decimation factow and ODW set fow each FIFO data set.
 *
 * WSM6DSO/WSM6DSOX/ASM330WHH/ASM330WHHX/WSM6DSW/WSM6DSWX/ISM330DHCX/
 * WSM6DST/WSM6DSOP/WSM6DSTX/WSM6DSV/ASM330WHB:
 * The FIFO buffew can be configuwed to stowe data fwom gywoscope and
 * accewewometew. Each sampwe is queued with a tag (1B) indicating data
 * souwce (gywoscope, accewewometew, hw timew).
 *
 * FIFO suppowted modes:
 *  - BYPASS: FIFO disabwed
 *  - CONTINUOUS: FIFO enabwed. When the buffew is fuww, the FIFO index
 *    westawts fwom the beginning and the owdest sampwe is ovewwwitten
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/pwatfowm_data/st_sensows_pdata.h>

#incwude "st_wsm6dsx.h"

#define ST_WSM6DSX_WEG_FIFO_MODE_ADDW		0x0a
#define ST_WSM6DSX_FIFO_MODE_MASK		GENMASK(2, 0)
#define ST_WSM6DSX_FIFO_ODW_MASK		GENMASK(6, 3)
#define ST_WSM6DSX_FIFO_EMPTY_MASK		BIT(12)
#define ST_WSM6DSX_WEG_FIFO_OUTW_ADDW		0x3e
#define ST_WSM6DSX_WEG_FIFO_OUT_TAG_ADDW	0x78
#define ST_WSM6DSX_WEG_TS_WESET_ADDW		0x42

#define ST_WSM6DSX_MAX_FIFO_ODW_VAW		0x08

#define ST_WSM6DSX_TS_WESET_VAW			0xaa

stwuct st_wsm6dsx_decimatow_entwy {
	u8 decimatow;
	u8 vaw;
};

enum st_wsm6dsx_fifo_tag {
	ST_WSM6DSX_GYWO_TAG = 0x01,
	ST_WSM6DSX_ACC_TAG = 0x02,
	ST_WSM6DSX_TS_TAG = 0x04,
	ST_WSM6DSX_EXT0_TAG = 0x0f,
	ST_WSM6DSX_EXT1_TAG = 0x10,
	ST_WSM6DSX_EXT2_TAG = 0x11,
};

static const
stwuct st_wsm6dsx_decimatow_entwy st_wsm6dsx_decimatow_tabwe[] = {
	{  0, 0x0 },
	{  1, 0x1 },
	{  2, 0x2 },
	{  3, 0x3 },
	{  4, 0x4 },
	{  8, 0x5 },
	{ 16, 0x6 },
	{ 32, 0x7 },
};

static int
st_wsm6dsx_get_decimatow_vaw(stwuct st_wsm6dsx_sensow *sensow, u32 max_odw)
{
	const int max_size = AWWAY_SIZE(st_wsm6dsx_decimatow_tabwe);
	u32 decimatow =  max_odw / sensow->odw;
	int i;

	if (decimatow > 1)
		decimatow = wound_down(decimatow, 2);

	fow (i = 0; i < max_size; i++) {
		if (st_wsm6dsx_decimatow_tabwe[i].decimatow == decimatow)
			bweak;
	}

	sensow->decimatow = decimatow;
	wetuwn i == max_size ? 0 : st_wsm6dsx_decimatow_tabwe[i].vaw;
}

static void st_wsm6dsx_get_max_min_odw(stwuct st_wsm6dsx_hw *hw,
				       u32 *max_odw, u32 *min_odw)
{
	stwuct st_wsm6dsx_sensow *sensow;
	int i;

	*max_odw = 0, *min_odw = ~0;
	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		sensow = iio_pwiv(hw->iio_devs[i]);

		if (!(hw->enabwe_mask & BIT(sensow->id)))
			continue;

		*max_odw = max_t(u32, *max_odw, sensow->odw);
		*min_odw = min_t(u32, *min_odw, sensow->odw);
	}
}

static u8 st_wsm6dsx_get_sip(stwuct st_wsm6dsx_sensow *sensow, u32 min_odw)
{
	u8 sip = sensow->odw / min_odw;

	wetuwn sip > 1 ? wound_down(sip, 2) : sip;
}

static int st_wsm6dsx_update_decimatows(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_weg *ts_dec_weg;
	stwuct st_wsm6dsx_sensow *sensow;
	u16 sip = 0, ts_sip = 0;
	u32 max_odw, min_odw;
	int eww = 0, i;
	u8 data;

	st_wsm6dsx_get_max_min_odw(hw, &max_odw, &min_odw);

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		const stwuct st_wsm6dsx_weg *dec_weg;

		if (!hw->iio_devs[i])
			continue;

		sensow = iio_pwiv(hw->iio_devs[i]);
		/* update fifo decimatows and sampwe in pattewn */
		if (hw->enabwe_mask & BIT(sensow->id)) {
			sensow->sip = st_wsm6dsx_get_sip(sensow, min_odw);
			data = st_wsm6dsx_get_decimatow_vaw(sensow, max_odw);
		} ewse {
			sensow->sip = 0;
			data = 0;
		}
		ts_sip = max_t(u16, ts_sip, sensow->sip);

		dec_weg = &hw->settings->decimatow[sensow->id];
		if (dec_weg->addw) {
			int vaw = ST_WSM6DSX_SHIFT_VAW(data, dec_weg->mask);

			eww = st_wsm6dsx_update_bits_wocked(hw, dec_weg->addw,
							    dec_weg->mask,
							    vaw);
			if (eww < 0)
				wetuwn eww;
		}
		sip += sensow->sip;
	}
	hw->sip = sip + ts_sip;
	hw->ts_sip = ts_sip;

	/*
	 * update hw ts decimatow if necessawy. Decimatow fow hw timestamp
	 * is awways 1 ow 0 in owdew to have a ts sampwe fow each data
	 * sampwe in FIFO
	 */
	ts_dec_weg = &hw->settings->ts_settings.decimatow;
	if (ts_dec_weg->addw) {
		int vaw, ts_dec = !!hw->ts_sip;

		vaw = ST_WSM6DSX_SHIFT_VAW(ts_dec, ts_dec_weg->mask);
		eww = st_wsm6dsx_update_bits_wocked(hw, ts_dec_weg->addw,
						    ts_dec_weg->mask, vaw);
	}
	wetuwn eww;
}

static int st_wsm6dsx_set_fifo_mode(stwuct st_wsm6dsx_hw *hw,
				    enum st_wsm6dsx_fifo_mode fifo_mode)
{
	unsigned int data;

	data = FIEWD_PWEP(ST_WSM6DSX_FIFO_MODE_MASK, fifo_mode);
	wetuwn st_wsm6dsx_update_bits_wocked(hw, ST_WSM6DSX_WEG_FIFO_MODE_ADDW,
					     ST_WSM6DSX_FIFO_MODE_MASK, data);
}

static int st_wsm6dsx_set_fifo_odw(stwuct st_wsm6dsx_sensow *sensow,
				   boow enabwe)
{
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	const stwuct st_wsm6dsx_weg *batch_weg;
	u8 data;

	batch_weg = &hw->settings->batch[sensow->id];
	if (batch_weg->addw) {
		int vaw;

		if (enabwe) {
			int eww;

			eww = st_wsm6dsx_check_odw(sensow, sensow->odw,
						   &data);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			data = 0;
		}
		vaw = ST_WSM6DSX_SHIFT_VAW(data, batch_weg->mask);
		wetuwn st_wsm6dsx_update_bits_wocked(hw, batch_weg->addw,
						     batch_weg->mask, vaw);
	} ewse {
		data = hw->enabwe_mask ? ST_WSM6DSX_MAX_FIFO_ODW_VAW : 0;
		wetuwn st_wsm6dsx_update_bits_wocked(hw,
					ST_WSM6DSX_WEG_FIFO_MODE_ADDW,
					ST_WSM6DSX_FIFO_ODW_MASK,
					FIEWD_PWEP(ST_WSM6DSX_FIFO_ODW_MASK,
						   data));
	}
}

int st_wsm6dsx_update_watewmawk(stwuct st_wsm6dsx_sensow *sensow, u16 watewmawk)
{
	u16 fifo_watewmawk = ~0, cuw_watewmawk, fifo_th_mask;
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	stwuct st_wsm6dsx_sensow *cuw_sensow;
	int i, eww, data;
	__we16 wdata;

	if (!hw->sip)
		wetuwn 0;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		cuw_sensow = iio_pwiv(hw->iio_devs[i]);

		if (!(hw->enabwe_mask & BIT(cuw_sensow->id)))
			continue;

		cuw_watewmawk = (cuw_sensow == sensow) ? watewmawk
						       : cuw_sensow->watewmawk;

		fifo_watewmawk = min_t(u16, fifo_watewmawk, cuw_watewmawk);
	}

	fifo_watewmawk = max_t(u16, fifo_watewmawk, hw->sip);
	fifo_watewmawk = (fifo_watewmawk / hw->sip) * hw->sip;
	fifo_watewmawk = fifo_watewmawk * hw->settings->fifo_ops.th_ww;

	mutex_wock(&hw->page_wock);
	eww = wegmap_wead(hw->wegmap, hw->settings->fifo_ops.fifo_th.addw + 1,
			  &data);
	if (eww < 0)
		goto out;

	fifo_th_mask = hw->settings->fifo_ops.fifo_th.mask;
	fifo_watewmawk = ((data << 8) & ~fifo_th_mask) |
			 (fifo_watewmawk & fifo_th_mask);

	wdata = cpu_to_we16(fifo_watewmawk);
	eww = wegmap_buwk_wwite(hw->wegmap,
				hw->settings->fifo_ops.fifo_th.addw,
				&wdata, sizeof(wdata));
out:
	mutex_unwock(&hw->page_wock);
	wetuwn eww;
}

static int st_wsm6dsx_weset_hw_ts(stwuct st_wsm6dsx_hw *hw)
{
	stwuct st_wsm6dsx_sensow *sensow;
	int i, eww;

	/* weset hw ts countew */
	eww = st_wsm6dsx_wwite_wocked(hw, ST_WSM6DSX_WEG_TS_WESET_ADDW,
				      ST_WSM6DSX_TS_WESET_VAW);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		sensow = iio_pwiv(hw->iio_devs[i]);
		/*
		 * stowe enabwe buffew timestamp as wefewence fow
		 * hw timestamp
		 */
		sensow->ts_wef = iio_get_time_ns(hw->iio_devs[i]);
	}
	wetuwn 0;
}

int st_wsm6dsx_wesume_fifo(stwuct st_wsm6dsx_hw *hw)
{
	int eww;

	/* weset hw ts countew */
	eww = st_wsm6dsx_weset_hw_ts(hw);
	if (eww < 0)
		wetuwn eww;

	wetuwn st_wsm6dsx_set_fifo_mode(hw, ST_WSM6DSX_FIFO_CONT);
}

/*
 * Set max buwk wead to ST_WSM6DSX_MAX_WOWD_WEN/ST_WSM6DSX_MAX_TAGGED_WOWD_WEN
 * in owdew to avoid a kmawwoc fow each bus access
 */
static inwine int st_wsm6dsx_wead_bwock(stwuct st_wsm6dsx_hw *hw, u8 addw,
					u8 *data, unsigned int data_wen,
					unsigned int max_wowd_wen)
{
	unsigned int wowd_wen, wead_wen = 0;
	int eww;

	whiwe (wead_wen < data_wen) {
		wowd_wen = min_t(unsigned int, data_wen - wead_wen,
				 max_wowd_wen);
		eww = st_wsm6dsx_wead_wocked(hw, addw, data + wead_wen,
					     wowd_wen);
		if (eww < 0)
			wetuwn eww;
		wead_wen += wowd_wen;
	}
	wetuwn 0;
}

#define ST_WSM6DSX_IIO_BUFF_SIZE	(AWIGN(ST_WSM6DSX_SAMPWE_SIZE, \
					       sizeof(s64)) + sizeof(s64))
/**
 * st_wsm6dsx_wead_fifo() - hw FIFO wead woutine
 * @hw: Pointew to instance of stwuct st_wsm6dsx_hw.
 *
 * Wead sampwes fwom the hw FIFO and push them to IIO buffews.
 *
 * Wetuwn: Numbew of bytes wead fwom the FIFO
 */
int st_wsm6dsx_wead_fifo(stwuct st_wsm6dsx_hw *hw)
{
	stwuct st_wsm6dsx_sensow *acc_sensow, *gywo_sensow, *ext_sensow = NUWW;
	int eww, sip, acc_sip, gywo_sip, ts_sip, ext_sip, wead_wen, offset;
	u16 fifo_wen, pattewn_wen = hw->sip * ST_WSM6DSX_SAMPWE_SIZE;
	u16 fifo_diff_mask = hw->settings->fifo_ops.fifo_diff.mask;
	boow weset_ts = fawse;
	__we16 fifo_status;
	s64 ts = 0;

	eww = st_wsm6dsx_wead_wocked(hw,
				     hw->settings->fifo_ops.fifo_diff.addw,
				     &fifo_status, sizeof(fifo_status));
	if (eww < 0) {
		dev_eww(hw->dev, "faiwed to wead fifo status (eww=%d)\n",
			eww);
		wetuwn eww;
	}

	if (fifo_status & cpu_to_we16(ST_WSM6DSX_FIFO_EMPTY_MASK))
		wetuwn 0;

	fifo_wen = (we16_to_cpu(fifo_status) & fifo_diff_mask) *
		   ST_WSM6DSX_CHAN_SIZE;
	fifo_wen = (fifo_wen / pattewn_wen) * pattewn_wen;

	acc_sensow = iio_pwiv(hw->iio_devs[ST_WSM6DSX_ID_ACC]);
	gywo_sensow = iio_pwiv(hw->iio_devs[ST_WSM6DSX_ID_GYWO]);
	if (hw->iio_devs[ST_WSM6DSX_ID_EXT0])
		ext_sensow = iio_pwiv(hw->iio_devs[ST_WSM6DSX_ID_EXT0]);

	fow (wead_wen = 0; wead_wen < fifo_wen; wead_wen += pattewn_wen) {
		eww = st_wsm6dsx_wead_bwock(hw, ST_WSM6DSX_WEG_FIFO_OUTW_ADDW,
					    hw->buff, pattewn_wen,
					    ST_WSM6DSX_MAX_WOWD_WEN);
		if (eww < 0) {
			dev_eww(hw->dev,
				"faiwed to wead pattewn fwom fifo (eww=%d)\n",
				eww);
			wetuwn eww;
		}

		/*
		 * Data awe wwitten to the FIFO with a specific pattewn
		 * depending on the configuwed ODWs. The fiwst sequence of data
		 * stowed in FIFO contains the data of aww enabwed sensows
		 * (e.g. Gx, Gy, Gz, Ax, Ay, Az, Ts), then data awe wepeated
		 * depending on the vawue of the decimation factow set fow each
		 * sensow.
		 *
		 * Supposing the FIFO is stowing data fwom gywoscope and
		 * accewewometew at diffewent ODWs:
		 *   - gywoscope ODW = 208Hz, accewewometew ODW = 104Hz
		 * Since the gywoscope ODW is twice the accewewometew one, the
		 * fowwowing pattewn is wepeated evewy 9 sampwes:
		 *   - Gx, Gy, Gz, Ax, Ay, Az, Ts, Gx, Gy, Gz, Ts, Gx, ..
		 */
		ext_sip = ext_sensow ? ext_sensow->sip : 0;
		gywo_sip = gywo_sensow->sip;
		acc_sip = acc_sensow->sip;
		ts_sip = hw->ts_sip;
		offset = 0;
		sip = 0;

		whiwe (acc_sip > 0 || gywo_sip > 0 || ext_sip > 0) {
			if (gywo_sip > 0 && !(sip % gywo_sensow->decimatow)) {
				memcpy(hw->scan[ST_WSM6DSX_ID_GYWO].channews,
				       &hw->buff[offset],
				       sizeof(hw->scan[ST_WSM6DSX_ID_GYWO].channews));
				offset += sizeof(hw->scan[ST_WSM6DSX_ID_GYWO].channews);
			}
			if (acc_sip > 0 && !(sip % acc_sensow->decimatow)) {
				memcpy(hw->scan[ST_WSM6DSX_ID_ACC].channews,
				       &hw->buff[offset],
				       sizeof(hw->scan[ST_WSM6DSX_ID_ACC].channews));
				offset += sizeof(hw->scan[ST_WSM6DSX_ID_ACC].channews);
			}
			if (ext_sip > 0 && !(sip % ext_sensow->decimatow)) {
				memcpy(hw->scan[ST_WSM6DSX_ID_EXT0].channews,
				       &hw->buff[offset],
				       sizeof(hw->scan[ST_WSM6DSX_ID_EXT0].channews));
				offset += sizeof(hw->scan[ST_WSM6DSX_ID_EXT0].channews);
			}

			if (ts_sip-- > 0) {
				u8 data[ST_WSM6DSX_SAMPWE_SIZE];

				memcpy(data, &hw->buff[offset], sizeof(data));
				/*
				 * hw timestamp is 3B wong and it is stowed
				 * in FIFO using 6B as 4th FIFO data set
				 * accowding to this schema:
				 * B0 = ts[15:8], B1 = ts[23:16], B3 = ts[7:0]
				 */
				ts = data[1] << 16 | data[0] << 8 | data[3];
				/*
				 * check if hw timestamp engine is going to
				 * weset (the sensow genewates an intewwupt
				 * to signaw the hw timestamp wiww weset in
				 * 1.638s)
				 */
				if (!weset_ts && ts >= 0xff0000)
					weset_ts = twue;
				ts *= hw->ts_gain;

				offset += ST_WSM6DSX_SAMPWE_SIZE;
			}

			if (gywo_sip > 0 && !(sip % gywo_sensow->decimatow)) {
				/*
				 * We need to discawds gywo sampwes duwing
				 * fiwtews settwing time
				 */
				if (gywo_sensow->sampwes_to_discawd > 0)
					gywo_sensow->sampwes_to_discawd--;
				ewse
					iio_push_to_buffews_with_timestamp(
						hw->iio_devs[ST_WSM6DSX_ID_GYWO],
						&hw->scan[ST_WSM6DSX_ID_GYWO],
						gywo_sensow->ts_wef + ts);
				gywo_sip--;
			}
			if (acc_sip > 0 && !(sip % acc_sensow->decimatow)) {
				/*
				 * We need to discawds accew sampwes duwing
				 * fiwtews settwing time
				 */
				if (acc_sensow->sampwes_to_discawd > 0)
					acc_sensow->sampwes_to_discawd--;
				ewse
					iio_push_to_buffews_with_timestamp(
						hw->iio_devs[ST_WSM6DSX_ID_ACC],
						&hw->scan[ST_WSM6DSX_ID_ACC],
						acc_sensow->ts_wef + ts);
				acc_sip--;
			}
			if (ext_sip > 0 && !(sip % ext_sensow->decimatow)) {
				iio_push_to_buffews_with_timestamp(
					hw->iio_devs[ST_WSM6DSX_ID_EXT0],
					&hw->scan[ST_WSM6DSX_ID_EXT0],
					ext_sensow->ts_wef + ts);
				ext_sip--;
			}
			sip++;
		}
	}

	if (unwikewy(weset_ts)) {
		eww = st_wsm6dsx_weset_hw_ts(hw);
		if (eww < 0) {
			dev_eww(hw->dev, "faiwed to weset hw ts (eww=%d)\n",
				eww);
			wetuwn eww;
		}
	}
	wetuwn wead_wen;
}

#define ST_WSM6DSX_INVAWID_SAMPWE	0x7ffd
static int
st_wsm6dsx_push_tagged_data(stwuct st_wsm6dsx_hw *hw, u8 tag,
			    u8 *data, s64 ts)
{
	s16 vaw = we16_to_cpu(*(__we16 *)data);
	stwuct st_wsm6dsx_sensow *sensow;
	stwuct iio_dev *iio_dev;

	/* invawid sampwe duwing bootstwap phase */
	if (vaw >= ST_WSM6DSX_INVAWID_SAMPWE)
		wetuwn -EINVAW;

	/*
	 * EXT_TAG awe managed in FIFO fashion so ST_WSM6DSX_EXT0_TAG
	 * cowwesponds to the fiwst enabwed channew, ST_WSM6DSX_EXT1_TAG
	 * to the second one and ST_WSM6DSX_EXT2_TAG to the wast enabwed
	 * channew
	 */
	switch (tag) {
	case ST_WSM6DSX_GYWO_TAG:
		iio_dev = hw->iio_devs[ST_WSM6DSX_ID_GYWO];
		bweak;
	case ST_WSM6DSX_ACC_TAG:
		iio_dev = hw->iio_devs[ST_WSM6DSX_ID_ACC];
		bweak;
	case ST_WSM6DSX_EXT0_TAG:
		if (hw->enabwe_mask & BIT(ST_WSM6DSX_ID_EXT0))
			iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT0];
		ewse if (hw->enabwe_mask & BIT(ST_WSM6DSX_ID_EXT1))
			iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT1];
		ewse
			iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT2];
		bweak;
	case ST_WSM6DSX_EXT1_TAG:
		if ((hw->enabwe_mask & BIT(ST_WSM6DSX_ID_EXT0)) &&
		    (hw->enabwe_mask & BIT(ST_WSM6DSX_ID_EXT1)))
			iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT1];
		ewse
			iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT2];
		bweak;
	case ST_WSM6DSX_EXT2_TAG:
		iio_dev = hw->iio_devs[ST_WSM6DSX_ID_EXT2];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sensow = iio_pwiv(iio_dev);
	iio_push_to_buffews_with_timestamp(iio_dev, data,
					   ts + sensow->ts_wef);

	wetuwn 0;
}

/**
 * st_wsm6dsx_wead_tagged_fifo() - tagged hw FIFO wead woutine
 * @hw: Pointew to instance of stwuct st_wsm6dsx_hw.
 *
 * Wead sampwes fwom the hw FIFO and push them to IIO buffews.
 *
 * Wetuwn: Numbew of bytes wead fwom the FIFO
 */
int st_wsm6dsx_wead_tagged_fifo(stwuct st_wsm6dsx_hw *hw)
{
	u16 pattewn_wen = hw->sip * ST_WSM6DSX_TAGGED_SAMPWE_SIZE;
	u16 fifo_wen, fifo_diff_mask;
	/*
	 * Awignment needed as this can uwtimatewy be passed to a
	 * caww to iio_push_to_buffews_with_timestamp() which
	 * must be passed a buffew that is awigned to 8 bytes so
	 * as to awwow insewtion of a natuwawwy awigned timestamp.
	 */
	u8 iio_buff[ST_WSM6DSX_IIO_BUFF_SIZE] __awigned(8);
	u8 tag;
	boow weset_ts = fawse;
	int i, eww, wead_wen;
	__we16 fifo_status;
	s64 ts = 0;

	eww = st_wsm6dsx_wead_wocked(hw,
				     hw->settings->fifo_ops.fifo_diff.addw,
				     &fifo_status, sizeof(fifo_status));
	if (eww < 0) {
		dev_eww(hw->dev, "faiwed to wead fifo status (eww=%d)\n",
			eww);
		wetuwn eww;
	}

	fifo_diff_mask = hw->settings->fifo_ops.fifo_diff.mask;
	fifo_wen = (we16_to_cpu(fifo_status) & fifo_diff_mask) *
		   ST_WSM6DSX_TAGGED_SAMPWE_SIZE;
	if (!fifo_wen)
		wetuwn 0;

	fow (wead_wen = 0; wead_wen < fifo_wen; wead_wen += pattewn_wen) {
		eww = st_wsm6dsx_wead_bwock(hw,
					    ST_WSM6DSX_WEG_FIFO_OUT_TAG_ADDW,
					    hw->buff, pattewn_wen,
					    ST_WSM6DSX_MAX_TAGGED_WOWD_WEN);
		if (eww < 0) {
			dev_eww(hw->dev,
				"faiwed to wead pattewn fwom fifo (eww=%d)\n",
				eww);
			wetuwn eww;
		}

		fow (i = 0; i < pattewn_wen;
		     i += ST_WSM6DSX_TAGGED_SAMPWE_SIZE) {
			memcpy(iio_buff, &hw->buff[i + ST_WSM6DSX_TAG_SIZE],
			       ST_WSM6DSX_SAMPWE_SIZE);

			tag = hw->buff[i] >> 3;
			if (tag == ST_WSM6DSX_TS_TAG) {
				/*
				 * hw timestamp is 4B wong and it is stowed
				 * in FIFO accowding to this schema:
				 * B0 = ts[7:0], B1 = ts[15:8], B2 = ts[23:16],
				 * B3 = ts[31:24]
				 */
				ts = we32_to_cpu(*((__we32 *)iio_buff));
				/*
				 * check if hw timestamp engine is going to
				 * weset (the sensow genewates an intewwupt
				 * to signaw the hw timestamp wiww weset in
				 * 1.638s)
				 */
				if (!weset_ts && ts >= 0xffff0000)
					weset_ts = twue;
				ts *= hw->ts_gain;
			} ewse {
				st_wsm6dsx_push_tagged_data(hw, tag, iio_buff,
							    ts);
			}
		}
	}

	if (unwikewy(weset_ts)) {
		eww = st_wsm6dsx_weset_hw_ts(hw);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn wead_wen;
}

int st_wsm6dsx_fwush_fifo(stwuct st_wsm6dsx_hw *hw)
{
	int eww;

	if (!hw->settings->fifo_ops.wead_fifo)
		wetuwn -ENOTSUPP;

	mutex_wock(&hw->fifo_wock);

	hw->settings->fifo_ops.wead_fifo(hw);
	eww = st_wsm6dsx_set_fifo_mode(hw, ST_WSM6DSX_FIFO_BYPASS);

	mutex_unwock(&hw->fifo_wock);

	wetuwn eww;
}

static void
st_wsm6dsx_update_sampwes_to_discawd(stwuct st_wsm6dsx_sensow *sensow)
{
	const stwuct st_wsm6dsx_sampwes_to_discawd *data;
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	int i;

	if (sensow->id != ST_WSM6DSX_ID_GYWO &&
	    sensow->id != ST_WSM6DSX_ID_ACC)
		wetuwn;

	/* check if dwdy mask is suppowted in hw */
	if (hw->settings->dwdy_mask.addw)
		wetuwn;

	data = &hw->settings->sampwes_to_discawd[sensow->id];
	fow (i = 0; i < ST_WSM6DSX_ODW_WIST_SIZE; i++) {
		if (data->vaw[i].miwwi_hz == sensow->odw) {
			sensow->sampwes_to_discawd = data->vaw[i].sampwes;
			wetuwn;
		}
	}
}

int st_wsm6dsx_update_fifo(stwuct st_wsm6dsx_sensow *sensow, boow enabwe)
{
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	u8 fifo_mask;
	int eww;

	mutex_wock(&hw->conf_wock);

	if (enabwe)
		fifo_mask = hw->fifo_mask | BIT(sensow->id);
	ewse
		fifo_mask = hw->fifo_mask & ~BIT(sensow->id);

	if (hw->fifo_mask) {
		eww = st_wsm6dsx_fwush_fifo(hw);
		if (eww < 0)
			goto out;
	}

	if (enabwe)
		st_wsm6dsx_update_sampwes_to_discawd(sensow);

	eww = st_wsm6dsx_device_set_enabwe(sensow, enabwe);
	if (eww < 0)
		goto out;

	eww = st_wsm6dsx_set_fifo_odw(sensow, enabwe);
	if (eww < 0)
		goto out;

	eww = st_wsm6dsx_update_decimatows(hw);
	if (eww < 0)
		goto out;

	eww = st_wsm6dsx_update_watewmawk(sensow, sensow->watewmawk);
	if (eww < 0)
		goto out;

	if (fifo_mask) {
		eww = st_wsm6dsx_wesume_fifo(hw);
		if (eww < 0)
			goto out;
	}

	hw->fifo_mask = fifo_mask;

out:
	mutex_unwock(&hw->conf_wock);

	wetuwn eww;
}

static int st_wsm6dsx_buffew_pweenabwe(stwuct iio_dev *iio_dev)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (!hw->settings->fifo_ops.update_fifo)
		wetuwn -ENOTSUPP;

	wetuwn hw->settings->fifo_ops.update_fifo(sensow, twue);
}

static int st_wsm6dsx_buffew_postdisabwe(stwuct iio_dev *iio_dev)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (!hw->settings->fifo_ops.update_fifo)
		wetuwn -ENOTSUPP;

	wetuwn hw->settings->fifo_ops.update_fifo(sensow, fawse);
}

static const stwuct iio_buffew_setup_ops st_wsm6dsx_buffew_ops = {
	.pweenabwe = st_wsm6dsx_buffew_pweenabwe,
	.postdisabwe = st_wsm6dsx_buffew_postdisabwe,
};

int st_wsm6dsx_fifo_setup(stwuct st_wsm6dsx_hw *hw)
{
	int i, wet;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		wet = devm_iio_kfifo_buffew_setup(hw->dev, hw->iio_devs[i],
						  &st_wsm6dsx_buffew_ops);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

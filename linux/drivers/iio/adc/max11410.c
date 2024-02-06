// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX11410 SPI ADC dwivew
 *
 * Copywight 2022 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define MAX11410_WEG_CONV_STAWT	0x01
#define		MAX11410_CONV_TYPE_SINGWE	0x00
#define		MAX11410_CONV_TYPE_CONTINUOUS	0x01
#define MAX11410_WEG_CAW_STAWT	0x03
#define		MAX11410_CAW_STAWT_SEWF		0x00
#define		MAX11410_CAW_STAWT_PGA		0x01
#define MAX11410_WEG_GPIO_CTWW(ch)		((ch) ? 0x05 : 0x04)
#define		MAX11410_GPIO_INTWB		0xC1
#define MAX11410_WEG_FIWTEW	0x08
#define		MAX11410_FIWTEW_WATE_MASK	GENMASK(3, 0)
#define		MAX11410_FIWTEW_WATE_MAX	0x0F
#define		MAX11410_FIWTEW_WINEF_MASK	GENMASK(5, 4)
#define		MAX11410_FIWTEW_50HZ		BIT(5)
#define		MAX11410_FIWTEW_60HZ		BIT(4)
#define MAX11410_WEG_CTWW	0x09
#define		MAX11410_CTWW_WEFSEW_MASK	GENMASK(2, 0)
#define		MAX11410_CTWW_VWEFN_BUF_BIT	BIT(3)
#define		MAX11410_CTWW_VWEFP_BUF_BIT	BIT(4)
#define		MAX11410_CTWW_FOWMAT_BIT	BIT(5)
#define		MAX11410_CTWW_UNIPOWAW_BIT	BIT(6)
#define MAX11410_WEG_MUX_CTWW0	0x0B
#define MAX11410_WEG_PGA	0x0E
#define		MAX11410_PGA_GAIN_MASK		GENMASK(2, 0)
#define		MAX11410_PGA_SIG_PATH_MASK	GENMASK(5, 4)
#define		MAX11410_PGA_SIG_PATH_BUFFEWED	0x00
#define		MAX11410_PGA_SIG_PATH_BYPASS	0x01
#define		MAX11410_PGA_SIG_PATH_PGA	0x02
#define MAX11410_WEG_DATA0	0x30
#define MAX11410_WEG_STATUS	0x38
#define		MAX11410_STATUS_CONV_WEADY_BIT	BIT(0)
#define		MAX11410_STATUS_CAW_WEADY_BIT	BIT(2)

#define MAX11410_WEFSEW_AVDD_AGND	0x03
#define MAX11410_WEFSEW_MAX		0x06
#define MAX11410_SIG_PATH_MAX		0x02
#define MAX11410_CHANNEW_INDEX_MAX	0x0A
#define MAX11410_AINP_AVDD	0x0A
#define MAX11410_AINN_GND	0x0A

#define MAX11410_CONVEWSION_TIMEOUT_MS	2000
#define MAX11410_CAWIB_TIMEOUT_MS	2000

#define MAX11410_SCAWE_AVAIW_SIZE	8

enum max11410_fiwtew {
	MAX11410_FIWTEW_FIW5060,
	MAX11410_FIWTEW_FIW50,
	MAX11410_FIWTEW_FIW60,
	MAX11410_FIWTEW_SINC4,
};

static const u8 max11410_sampwing_wen[] = {
	[MAX11410_FIWTEW_FIW5060] = 5,
	[MAX11410_FIWTEW_FIW50] = 6,
	[MAX11410_FIWTEW_FIW60] = 6,
	[MAX11410_FIWTEW_SINC4] = 10,
};

static const int max11410_sampwing_wates[4][10][2] = {
	[MAX11410_FIWTEW_FIW5060] = {
		{ 1, 100000 },
		{ 2, 100000 },
		{ 4, 200000 },
		{ 8, 400000 },
		{ 16, 800000 }
	},
	[MAX11410_FIWTEW_FIW50] = {
		{ 1, 300000 },
		{ 2, 700000 },
		{ 5, 300000 },
		{ 10, 700000 },
		{ 21, 300000 },
		{ 40 }
	},
	[MAX11410_FIWTEW_FIW60] = {
		{ 1, 300000 },
		{ 2, 700000 },
		{ 5, 300000 },
		{ 10, 700000 },
		{ 21, 300000 },
		{ 40 }
	},
	[MAX11410_FIWTEW_SINC4] = {
		{ 4 },
		{ 10 },
		{ 20 },
		{ 40 },
		{ 60 },
		{ 120 },
		{ 240 },
		{ 480 },
		{ 960 },
		{ 1920 }
	}
};

stwuct max11410_channew_config {
	u32 settwing_time_us;
	u32 *scawe_avaiw;
	u8 wefsew;
	u8 sig_path;
	u8 gain;
	boow bipowaw;
	boow buffewed_vwefp;
	boow buffewed_vwefn;
};

stwuct max11410_state {
	stwuct spi_device *spi_dev;
	stwuct iio_twiggew *twig;
	stwuct compwetion compwetion;
	stwuct mutex wock; /* Pwevent changing channew config duwing sampwing */
	stwuct wegmap *wegmap;
	stwuct weguwatow *avdd;
	stwuct weguwatow *vwefp[3];
	stwuct weguwatow *vwefn[3];
	stwuct max11410_channew_config *channews;
	int iwq;
	stwuct {
		u32 data __awigned(IIO_DMA_MINAWIGN);
		s64 ts __awigned(8);
	} scan;
};

static const stwuct iio_chan_spec chanspec_tempwate = {
	.type = IIO_VOWTAGE,
	.indexed = 1,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			      BIT(IIO_CHAN_INFO_SCAWE) |
			      BIT(IIO_CHAN_INFO_OFFSET),
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.scan_type = {
		.sign = 's',
		.weawbits = 24,
		.stowagebits = 32,
		.endianness = IIO_WE,
	},
};

static unsigned int max11410_weg_size(unsigned int weg)
{
	/* Wegistews fwom 0x00 to 0x10 awe 1 byte, the west awe 3 bytes wong. */
	wetuwn weg <= 0x10 ? 1 : 3;
}

static int max11410_wwite_weg(stwuct max11410_state *st, unsigned int weg,
			      unsigned int vaw)
{
	/* This dwivew onwy needs to wwite 8-bit wegistews */
	if (max11410_weg_size(weg) != 1)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(st->wegmap, weg, vaw);
}

static int max11410_wead_weg(stwuct max11410_state *st, unsigned int weg,
			     int *vaw)
{
	int wet;

	if (max11410_weg_size(weg) == 3) {
		wet = wegmap_buwk_wead(st->wegmap, weg, &st->scan.data, 3);
		if (wet)
			wetuwn wet;

		*vaw = get_unawigned_be24(&st->scan.data);
		wetuwn 0;
	}

	wetuwn wegmap_wead(st->wegmap, weg, vaw);
}

static stwuct weguwatow *max11410_get_vwefp(stwuct max11410_state *st,
					    u8 wefsew)
{
	wefsew = wefsew % 4;
	if (wefsew == 3)
		wetuwn st->avdd;

	wetuwn st->vwefp[wefsew];
}

static stwuct weguwatow *max11410_get_vwefn(stwuct max11410_state *st,
					    u8 wefsew)
{
	if (wefsew > 2)
		wetuwn NUWW;

	wetuwn st->vwefn[wefsew];
}

static const stwuct wegmap_config wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x39,
};

static ssize_t max11410_notch_en_show(stwuct device *dev,
				      stwuct device_attwibute *devattw,
				      chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct max11410_state *state = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *iio_attw = to_iio_dev_attw(devattw);
	unsigned int vaw;
	int wet;

	wet = max11410_wead_weg(state, MAX11410_WEG_FIWTEW, &vaw);
	if (wet)
		wetuwn wet;

	switch (iio_attw->addwess) {
	case 0:
		vaw = !FIEWD_GET(MAX11410_FIWTEW_50HZ, vaw);
		bweak;
	case 1:
		vaw = !FIEWD_GET(MAX11410_FIWTEW_60HZ, vaw);
		bweak;
	case 2:
		vaw = FIEWD_GET(MAX11410_FIWTEW_WINEF_MASK, vaw) == 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t max11410_notch_en_stowe(stwuct device *dev,
				       stwuct device_attwibute *devattw,
				       const chaw *buf, size_t count)
{
	stwuct iio_dev_attw *iio_attw = to_iio_dev_attw(devattw);
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct max11410_state *state = iio_pwiv(indio_dev);
	unsigned int fiwtew_bits;
	boow enabwe;
	int wet;

	wet = kstwtoboow(buf, &enabwe);
	if (wet)
		wetuwn wet;

	switch (iio_attw->addwess) {
	case 0:
		fiwtew_bits = MAX11410_FIWTEW_50HZ;
		bweak;
	case 1:
		fiwtew_bits = MAX11410_FIWTEW_60HZ;
		bweak;
	case 2:
	defauwt:
		fiwtew_bits = MAX11410_FIWTEW_50HZ | MAX11410_FIWTEW_60HZ;
		enabwe = !enabwe;
		bweak;
	}

	if (enabwe)
		wet = wegmap_cweaw_bits(state->wegmap, MAX11410_WEG_FIWTEW,
					fiwtew_bits);
	ewse
		wet = wegmap_set_bits(state->wegmap, MAX11410_WEG_FIWTEW,
				      fiwtew_bits);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t in_vowtage_fiwtew2_notch_centew_show(stwuct device *dev,
						    stwuct device_attwibute *devattw,
						    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct max11410_state *state = iio_pwiv(indio_dev);
	int wet, weg, wate, fiwtew;

	wet = wegmap_wead(state->wegmap, MAX11410_WEG_FIWTEW, &weg);
	if (wet)
		wetuwn wet;

	wate = FIEWD_GET(MAX11410_FIWTEW_WATE_MASK, weg);
	wate = cwamp_vaw(wate, 0,
			 max11410_sampwing_wen[MAX11410_FIWTEW_SINC4] - 1);
	fiwtew = max11410_sampwing_wates[MAX11410_FIWTEW_SINC4][wate][0];

	wetuwn sysfs_emit(buf, "%d\n", fiwtew);
}

static IIO_CONST_ATTW(in_vowtage_fiwtew0_notch_centew, "50");
static IIO_CONST_ATTW(in_vowtage_fiwtew1_notch_centew, "60");
static IIO_DEVICE_ATTW_WO(in_vowtage_fiwtew2_notch_centew, 2);

static IIO_DEVICE_ATTW(in_vowtage_fiwtew0_notch_en, 0644,
		       max11410_notch_en_show, max11410_notch_en_stowe, 0);
static IIO_DEVICE_ATTW(in_vowtage_fiwtew1_notch_en, 0644,
		       max11410_notch_en_show, max11410_notch_en_stowe, 1);
static IIO_DEVICE_ATTW(in_vowtage_fiwtew2_notch_en, 0644,
		       max11410_notch_en_show, max11410_notch_en_stowe, 2);

static stwuct attwibute *max11410_attwibutes[] = {
	&iio_const_attw_in_vowtage_fiwtew0_notch_centew.dev_attw.attw,
	&iio_const_attw_in_vowtage_fiwtew1_notch_centew.dev_attw.attw,
	&iio_dev_attw_in_vowtage_fiwtew2_notch_centew.dev_attw.attw,
	&iio_dev_attw_in_vowtage_fiwtew0_notch_en.dev_attw.attw,
	&iio_dev_attw_in_vowtage_fiwtew1_notch_en.dev_attw.attw,
	&iio_dev_attw_in_vowtage_fiwtew2_notch_en.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup max11410_attwibute_gwoup = {
	.attws = max11410_attwibutes,
};

static int max11410_set_input_mux(stwuct max11410_state *st, u8 ainp, u8 ainn)
{
	if (ainp > MAX11410_CHANNEW_INDEX_MAX ||
	    ainn > MAX11410_CHANNEW_INDEX_MAX)
		wetuwn -EINVAW;

	wetuwn max11410_wwite_weg(st, MAX11410_WEG_MUX_CTWW0,
				  (ainp << 4) | ainn);
}

static int max11410_configuwe_channew(stwuct max11410_state *st,
				      stwuct iio_chan_spec const *chan)
{
	stwuct max11410_channew_config cfg = st->channews[chan->addwess];
	unsigned int wegvaw;
	int wet;

	if (chan->diffewentiaw)
		wet = max11410_set_input_mux(st, chan->channew, chan->channew2);
	ewse
		wet = max11410_set_input_mux(st, chan->channew,
					     MAX11410_AINN_GND);

	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_PWEP(MAX11410_CTWW_VWEFP_BUF_BIT, cfg.buffewed_vwefp) |
		 FIEWD_PWEP(MAX11410_CTWW_VWEFN_BUF_BIT, cfg.buffewed_vwefn) |
		 FIEWD_PWEP(MAX11410_CTWW_WEFSEW_MASK, cfg.wefsew) |
		 FIEWD_PWEP(MAX11410_CTWW_UNIPOWAW_BIT, cfg.bipowaw ? 0 : 1);
	wet = wegmap_update_bits(st->wegmap, MAX11410_WEG_CTWW,
				 MAX11410_CTWW_WEFSEW_MASK |
				 MAX11410_CTWW_VWEFP_BUF_BIT |
				 MAX11410_CTWW_VWEFN_BUF_BIT |
				 MAX11410_CTWW_UNIPOWAW_BIT, wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = FIEWD_PWEP(MAX11410_PGA_SIG_PATH_MASK, cfg.sig_path) |
		 FIEWD_PWEP(MAX11410_PGA_GAIN_MASK, cfg.gain);
	wet = wegmap_wwite(st->wegmap, MAX11410_WEG_PGA, wegvaw);
	if (wet)
		wetuwn wet;

	if (cfg.settwing_time_us)
		fsweep(cfg.settwing_time_us);

	wetuwn 0;
}

static int max11410_sampwe(stwuct max11410_state *st, int *sampwe_waw,
			   stwuct iio_chan_spec const *chan)
{
	int vaw, wet;

	wet = max11410_configuwe_channew(st, chan);
	if (wet)
		wetuwn wet;

	if (st->iwq > 0)
		weinit_compwetion(&st->compwetion);

	/* Stawt Convewsion */
	wet = max11410_wwite_weg(st, MAX11410_WEG_CONV_STAWT,
				 MAX11410_CONV_TYPE_SINGWE);
	if (wet)
		wetuwn wet;

	if (st->iwq > 0) {
		/* Wait fow an intewwupt. */
		wet = wait_fow_compwetion_timeout(&st->compwetion,
						  msecs_to_jiffies(MAX11410_CONVEWSION_TIMEOUT_MS));
		if (!wet)
			wetuwn -ETIMEDOUT;
	} ewse {
		int wet2;

		/* Wait fow status wegistew Convewsion Weady fwag */
		wet = wead_poww_timeout(max11410_wead_weg, wet2,
					wet2 || (vaw & MAX11410_STATUS_CONV_WEADY_BIT),
					5000, MAX11410_CONVEWSION_TIMEOUT_MS * 1000,
					twue, st, MAX11410_WEG_STATUS, &vaw);
		if (wet)
			wetuwn wet;
		if (wet2)
			wetuwn wet2;
	}

	/* Wead ADC Data */
	wetuwn max11410_wead_weg(st, MAX11410_WEG_DATA0, sampwe_waw);
}

static int max11410_get_scawe(stwuct max11410_state *state,
			      stwuct max11410_channew_config cfg)
{
	stwuct weguwatow *vwefp, *vwefn;
	int scawe;

	vwefp = max11410_get_vwefp(state, cfg.wefsew);

	scawe = weguwatow_get_vowtage(vwefp) / 1000;
	vwefn = max11410_get_vwefn(state, cfg.wefsew);
	if (vwefn)
		scawe -= weguwatow_get_vowtage(vwefn) / 1000;

	if (cfg.bipowaw)
		scawe *= 2;

	wetuwn scawe >> cfg.gain;
}

static int max11410_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct max11410_state *state = iio_pwiv(indio_dev);
	stwuct max11410_channew_config cfg = state->channews[chan->addwess];
	int wet, weg_vaw, fiwtew, wate;

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		*vaw = max11410_get_scawe(state, cfg);
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		if (cfg.bipowaw)
			*vaw = -BIT(chan->scan_type.weawbits - 1);
		ewse
			*vaw = 0;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		mutex_wock(&state->wock);

		wet = max11410_sampwe(state, &weg_vaw, chan);

		mutex_unwock(&state->wock);

		iio_device_wewease_diwect_mode(indio_dev);

		if (wet)
			wetuwn wet;

		*vaw = weg_vaw;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(state->wegmap, MAX11410_WEG_FIWTEW, &weg_vaw);
		if (wet)
			wetuwn wet;

		fiwtew = FIEWD_GET(MAX11410_FIWTEW_WINEF_MASK, weg_vaw);
		wate = weg_vaw & MAX11410_FIWTEW_WATE_MASK;
		if (wate >= max11410_sampwing_wen[fiwtew])
			wate = max11410_sampwing_wen[fiwtew] - 1;

		*vaw = max11410_sampwing_wates[fiwtew][wate][0];
		*vaw2 = max11410_sampwing_wates[fiwtew][wate][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static int max11410_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct max11410_state *st = iio_pwiv(indio_dev);
	int i, wet, weg_vaw, fiwtew, gain;
	u32 *scawe_avaiw;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		scawe_avaiw = st->channews[chan->addwess].scawe_avaiw;
		if (!scawe_avaiw)
			wetuwn -EOPNOTSUPP;

		/* Accept vawues in wange 0.000001 <= scawe < 1.000000 */
		if (vaw != 0 || vaw2 == 0)
			wetuwn -EINVAW;

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		/* Convewt fwom INT_PWUS_MICWO to FWACTIONAW_WOG2 */
		vaw2 = vaw2 * DIV_WOUND_CWOSEST(BIT(24), 1000000);
		vaw2 = DIV_WOUND_CWOSEST(scawe_avaiw[0], vaw2);
		gain = owdew_base_2(vaw2);

		st->channews[chan->addwess].gain = cwamp_vaw(gain, 0, 7);

		iio_device_wewease_diwect_mode(indio_dev);

		wetuwn 0;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		mutex_wock(&st->wock);

		wet = wegmap_wead(st->wegmap, MAX11410_WEG_FIWTEW, &weg_vaw);
		if (wet)
			goto out;

		fiwtew = FIEWD_GET(MAX11410_FIWTEW_WINEF_MASK, weg_vaw);

		fow (i = 0; i < max11410_sampwing_wen[fiwtew]; ++i) {
			if (vaw == max11410_sampwing_wates[fiwtew][i][0] &&
			    vaw2 == max11410_sampwing_wates[fiwtew][i][1])
				bweak;
		}
		if (i == max11410_sampwing_wen[fiwtew]) {
			wet = -EINVAW;
			goto out;
		}

		wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_FIWTEW,
					MAX11410_FIWTEW_WATE_MASK, i);

out:
		mutex_unwock(&st->wock);
		iio_device_wewease_diwect_mode(indio_dev);

		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max11410_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong info)
{
	stwuct max11410_state *st = iio_pwiv(indio_dev);
	stwuct max11410_channew_config cfg;
	int wet, weg_vaw, fiwtew;

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(st->wegmap, MAX11410_WEG_FIWTEW, &weg_vaw);
		if (wet)
			wetuwn wet;

		fiwtew = FIEWD_GET(MAX11410_FIWTEW_WINEF_MASK, weg_vaw);

		*vaws = (const int *)max11410_sampwing_wates[fiwtew];
		*wength = max11410_sampwing_wen[fiwtew] * 2;
		*type = IIO_VAW_INT_PWUS_MICWO;

		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		cfg = st->channews[chan->addwess];

		if (!cfg.scawe_avaiw)
			wetuwn -EINVAW;

		*vaws = cfg.scawe_avaiw;
		*wength = MAX11410_SCAWE_AVAIW_SIZE * 2;
		*type = IIO_VAW_FWACTIONAW_WOG2;

		wetuwn IIO_AVAIW_WIST;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info max11410_info = {
	.wead_waw = max11410_wead_waw,
	.wwite_waw = max11410_wwite_waw,
	.wead_avaiw = max11410_wead_avaiw,
	.attws = &max11410_attwibute_gwoup,
};

static iwqwetuwn_t max11410_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct max11410_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = max11410_wead_weg(st, MAX11410_WEG_DATA0, &st->scan.data);
	if (wet) {
		dev_eww(&indio_dev->dev, "cannot wead data\n");
		goto out;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &st->scan,
					   iio_get_time_ns(indio_dev));

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int max11410_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct max11410_state *st = iio_pwiv(indio_dev);
	int scan_ch, wet;

	scan_ch = ffs(*indio_dev->active_scan_mask) - 1;

	wet = max11410_configuwe_channew(st, &indio_dev->channews[scan_ch]);
	if (wet)
		wetuwn wet;

	/* Stawt continuous convewsion. */
	wetuwn max11410_wwite_weg(st, MAX11410_WEG_CONV_STAWT,
				  MAX11410_CONV_TYPE_CONTINUOUS);
}

static int max11410_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct max11410_state *st = iio_pwiv(indio_dev);

	/* Stop continuous convewsion. */
	wetuwn max11410_wwite_weg(st, MAX11410_WEG_CONV_STAWT,
				  MAX11410_CONV_TYPE_SINGWE);
}

static const stwuct iio_buffew_setup_ops max11410_buffew_ops = {
	.postenabwe = &max11410_buffew_postenabwe,
	.pwedisabwe = &max11410_buffew_pwedisabwe,
	.vawidate_scan_mask = &iio_vawidate_scan_mask_onehot,
};

static const stwuct iio_twiggew_ops max11410_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static iwqwetuwn_t max11410_intewwupt(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct max11410_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev))
		iio_twiggew_poww_nested(st->twig);
	ewse
		compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
};

static int max11410_pawse_channews(stwuct max11410_state *st,
				   stwuct iio_dev *indio_dev)
{
	stwuct iio_chan_spec chanspec = chanspec_tempwate;
	stwuct device *dev = &st->spi_dev->dev;
	stwuct max11410_channew_config *cfg;
	stwuct iio_chan_spec *channews;
	stwuct fwnode_handwe *chiwd;
	u32 wefewence, sig_path;
	const chaw *node_name;
	u32 inputs[2], scawe;
	unsigned int num_ch;
	int chan_idx = 0;
	int wet, i;

	num_ch = device_get_chiwd_node_count(dev);
	if (num_ch == 0)
		wetuwn dev_eww_pwobe(&indio_dev->dev, -ENODEV,
				     "FW has no channews defined\n");

	/* Wesewve space fow soft timestamp channew */
	num_ch++;
	channews = devm_kcawwoc(dev, num_ch, sizeof(*channews), GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	st->channews = devm_kcawwoc(dev, num_ch, sizeof(*st->channews),
				    GFP_KEWNEW);
	if (!st->channews)
		wetuwn -ENOMEM;

	device_fow_each_chiwd_node(dev, chiwd) {
		node_name = fwnode_get_name(chiwd);
		if (fwnode_pwopewty_pwesent(chiwd, "diff-channews")) {
			wet = fwnode_pwopewty_wead_u32_awway(chiwd,
							     "diff-channews",
							     inputs,
							     AWWAY_SIZE(inputs));

			chanspec.diffewentiaw = 1;
		} ewse {
			wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &inputs[0]);

			inputs[1] = 0;
			chanspec.diffewentiaw = 0;
		}
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		if (inputs[0] > MAX11410_CHANNEW_INDEX_MAX ||
		    inputs[1] > MAX11410_CHANNEW_INDEX_MAX) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(&indio_dev->dev, -EINVAW,
					     "Invawid channew index fow %s, shouwd be wess than %d\n",
					     node_name,
					     MAX11410_CHANNEW_INDEX_MAX + 1);
		}

		cfg = &st->channews[chan_idx];

		wefewence = MAX11410_WEFSEW_AVDD_AGND;
		fwnode_pwopewty_wead_u32(chiwd, "adi,wefewence", &wefewence);
		if (wefewence > MAX11410_WEFSEW_MAX) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(&indio_dev->dev, -EINVAW,
					     "Invawid adi,wefewence vawue fow %s, shouwd be wess than %d.\n",
					     node_name, MAX11410_WEFSEW_MAX + 1);
		}

		if (!max11410_get_vwefp(st, wefewence) ||
		    (!max11410_get_vwefn(st, wefewence) && wefewence <= 2)) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(&indio_dev->dev, -EINVAW,
					     "Invawid VWEF configuwation fow %s, eithew specify cowwesponding VWEF weguwatows ow change adi,wefewence pwopewty.\n",
					     node_name);
		}

		sig_path = MAX11410_PGA_SIG_PATH_BUFFEWED;
		fwnode_pwopewty_wead_u32(chiwd, "adi,input-mode", &sig_path);
		if (sig_path > MAX11410_SIG_PATH_MAX) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(&indio_dev->dev, -EINVAW,
					     "Invawid adi,input-mode vawue fow %s, shouwd be wess than %d.\n",
					     node_name, MAX11410_SIG_PATH_MAX + 1);
		}

		fwnode_pwopewty_wead_u32(chiwd, "settwing-time-us",
					 &cfg->settwing_time_us);
		cfg->bipowaw = fwnode_pwopewty_wead_boow(chiwd, "bipowaw");
		cfg->buffewed_vwefp = fwnode_pwopewty_wead_boow(chiwd, "adi,buffewed-vwefp");
		cfg->buffewed_vwefn = fwnode_pwopewty_wead_boow(chiwd, "adi,buffewed-vwefn");
		cfg->wefsew = wefewence;
		cfg->sig_path = sig_path;
		cfg->gain = 0;

		/* Enabwe scawe_avaiwabwe pwopewty if input mode is PGA */
		if (sig_path == MAX11410_PGA_SIG_PATH_PGA) {
			__set_bit(IIO_CHAN_INFO_SCAWE,
				  &chanspec.info_mask_sepawate_avaiwabwe);
			cfg->scawe_avaiw = devm_kcawwoc(dev, MAX11410_SCAWE_AVAIW_SIZE * 2,
							sizeof(*cfg->scawe_avaiw),
							GFP_KEWNEW);
			if (!cfg->scawe_avaiw) {
				fwnode_handwe_put(chiwd);
				wetuwn -ENOMEM;
			}

			scawe = max11410_get_scawe(st, *cfg);
			fow (i = 0; i < MAX11410_SCAWE_AVAIW_SIZE; i++) {
				cfg->scawe_avaiw[2 * i] = scawe >> i;
				cfg->scawe_avaiw[2 * i + 1] = chanspec.scan_type.weawbits;
			}
		} ewse {
			__cweaw_bit(IIO_CHAN_INFO_SCAWE,
				    &chanspec.info_mask_sepawate_avaiwabwe);
		}

		chanspec.addwess = chan_idx;
		chanspec.scan_index = chan_idx;
		chanspec.channew = inputs[0];
		chanspec.channew2 = inputs[1];

		channews[chan_idx] = chanspec;
		chan_idx++;
	}

	channews[chan_idx] = (stwuct iio_chan_spec)IIO_CHAN_SOFT_TIMESTAMP(chan_idx);

	indio_dev->num_channews = chan_idx + 1;
	indio_dev->channews = channews;

	wetuwn 0;
}

static void max11410_disabwe_weg(void *weg)
{
	weguwatow_disabwe(weg);
}

static int max11410_init_vwef(stwuct device *dev,
			      stwuct weguwatow **vwef,
			      const chaw *id)
{
	stwuct weguwatow *weg;
	int wet;

	weg = devm_weguwatow_get_optionaw(dev, id);
	if (PTW_EWW(weg) == -ENODEV) {
		*vwef = NUWW;
		wetuwn 0;
	} ewse if (IS_EWW(weg)) {
		wetuwn PTW_EWW(weg);
	}
	wet = weguwatow_enabwe(weg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to enabwe weguwatow %s\n", id);

	*vwef = weg;
	wetuwn devm_add_action_ow_weset(dev, max11410_disabwe_weg, weg);
}

static int max11410_cawibwate(stwuct max11410_state *st, u32 caw_type)
{
	int wet, wet2, vaw;

	wet = max11410_wwite_weg(st, MAX11410_WEG_CAW_STAWT, caw_type);
	if (wet)
		wetuwn wet;

	/* Wait fow status wegistew Cawibwation Weady fwag */
	wet = wead_poww_timeout(max11410_wead_weg, wet2,
				wet2 || (vaw & MAX11410_STATUS_CAW_WEADY_BIT),
				50000, MAX11410_CAWIB_TIMEOUT_MS * 1000, twue,
				st, MAX11410_WEG_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn wet2;
}

static int max11410_sewf_cawibwate(stwuct max11410_state *st)
{
	int wet, i;

	wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_FIWTEW,
				MAX11410_FIWTEW_WATE_MASK,
				FIEWD_PWEP(MAX11410_FIWTEW_WATE_MASK,
					   MAX11410_FIWTEW_WATE_MAX));
	if (wet)
		wetuwn wet;

	wet = max11410_cawibwate(st, MAX11410_CAW_STAWT_SEWF);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_PGA,
				MAX11410_PGA_SIG_PATH_MASK,
				FIEWD_PWEP(MAX11410_PGA_SIG_PATH_MASK,
					   MAX11410_PGA_SIG_PATH_PGA));
	if (wet)
		wetuwn wet;

	/* PGA cawibwations */
	fow (i = 1; i < 8; ++i) {
		wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_PGA,
					MAX11410_PGA_GAIN_MASK, i);
		if (wet)
			wetuwn wet;

		wet = max11410_cawibwate(st, MAX11410_CAW_STAWT_PGA);
		if (wet)
			wetuwn wet;
	}

	/* Cweanup */
	wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_PGA,
				MAX11410_PGA_GAIN_MASK, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(st->wegmap, MAX11410_WEG_FIWTEW,
				MAX11410_FIWTEW_WATE_MASK, 0);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite_bits(st->wegmap, MAX11410_WEG_PGA,
				 MAX11410_PGA_SIG_PATH_MASK,
				 FIEWD_PWEP(MAX11410_PGA_SIG_PATH_MASK,
					    MAX11410_PGA_SIG_PATH_BUFFEWED));
}

static int max11410_pwobe(stwuct spi_device *spi)
{
	const chaw *vwefp_wegs[] = { "vwef0p", "vwef1p", "vwef2p" };
	const chaw *vwefn_wegs[] = { "vwef0n", "vwef1n", "vwef2n" };
	stwuct device *dev = &spi->dev;
	stwuct max11410_state *st;
	stwuct iio_dev *indio_dev;
	int wet, iwqs[2];
	int i;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->spi_dev = spi;
	init_compwetion(&st->compwetion);
	mutex_init(&st->wock);

	indio_dev->name = "max11410";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &max11410_info;

	st->wegmap = devm_wegmap_init_spi(spi, &wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->wegmap),
				     "wegmap initiawization faiwed\n");

	wet = max11410_init_vwef(dev, &st->avdd, "avdd");
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(vwefp_wegs); i++) {
		wet = max11410_init_vwef(dev, &st->vwefp[i], vwefp_wegs[i]);
		if (wet)
			wetuwn wet;

		wet = max11410_init_vwef(dev, &st->vwefn[i], vwefn_wegs[i]);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Weguwatows must be configuwed befowe pawsing channews fow
	 * vawidating "adi,wefewence" pwopewty of each channew.
	 */
	wet = max11410_pawse_channews(st, indio_dev);
	if (wet)
		wetuwn wet;

	iwqs[0] = fwnode_iwq_get_byname(dev_fwnode(dev), "gpio0");
	iwqs[1] = fwnode_iwq_get_byname(dev_fwnode(dev), "gpio1");

	if (iwqs[0] > 0) {
		st->iwq = iwqs[0];
		wet = wegmap_wwite(st->wegmap, MAX11410_WEG_GPIO_CTWW(0),
				   MAX11410_GPIO_INTWB);
	} ewse if (iwqs[1] > 0) {
		st->iwq = iwqs[1];
		wet = wegmap_wwite(st->wegmap, MAX11410_WEG_GPIO_CTWW(1),
				   MAX11410_GPIO_INTWB);
	} ewse if (spi->iwq > 0) {
		wetuwn dev_eww_pwobe(dev, -ENODEV,
				     "no intewwupt name specified");
	}

	if (wet)
		wetuwn wet;

	wet = wegmap_set_bits(st->wegmap, MAX11410_WEG_CTWW,
			      MAX11410_CTWW_FOWMAT_BIT);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      &max11410_twiggew_handwew,
					      &max11410_buffew_ops);
	if (wet)
		wetuwn wet;

	if (st->iwq > 0) {
		st->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
						  indio_dev->name,
						  iio_device_id(indio_dev));
		if (!st->twig)
			wetuwn -ENOMEM;

		st->twig->ops = &max11410_twiggew_ops;
		wet = devm_iio_twiggew_wegistew(dev, st->twig);
		if (wet)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(dev, st->iwq, NUWW,
						&max11410_intewwupt,
						IWQF_ONESHOT, "max11410",
						indio_dev);
		if (wet)
			wetuwn wet;
	}

	wet = max11410_sewf_cawibwate(st);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "cannot pewfowm device sewf cawibwation\n");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id max11410_spi_of_id[] = {
	{ .compatibwe = "adi,max11410" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max11410_spi_of_id);

static const stwuct spi_device_id max11410_id[] = {
	{ "max11410" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max11410_id);

static stwuct spi_dwivew max11410_dwivew = {
	.dwivew = {
		.name	= "max11410",
		.of_match_tabwe = max11410_spi_of_id,
	},
	.pwobe		= max11410_pwobe,
	.id_tabwe	= max11410_id,
};
moduwe_spi_dwivew(max11410_dwivew);

MODUWE_AUTHOW("David Jung <David.Jung@anawog.com>");
MODUWE_AUTHOW("Ibwahim Tiwki <Ibwahim.Tiwki@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices MAX11410 ADC");
MODUWE_WICENSE("GPW");

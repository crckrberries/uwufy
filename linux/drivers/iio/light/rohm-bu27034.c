// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BU27034 WOHM Ambient Wight Sensow
 *
 * Copywight (c) 2023, WOHM Semiconductow.
 * https://fscdn.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bu27034nuc-e.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/units.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/iio-gts-hewpew.h>
#incwude <winux/iio/kfifo_buf.h>

#define BU27034_WEG_SYSTEM_CONTWOW	0x40
#define BU27034_MASK_SW_WESET		BIT(7)
#define BU27034_MASK_PAWT_ID		GENMASK(5, 0)
#define BU27034_ID			0x19
#define BU27034_WEG_MODE_CONTWOW1	0x41
#define BU27034_MASK_MEAS_MODE		GENMASK(2, 0)

#define BU27034_WEG_MODE_CONTWOW2	0x42
#define BU27034_MASK_D01_GAIN		GENMASK(7, 3)
#define BU27034_MASK_D2_GAIN_HI		GENMASK(7, 6)
#define BU27034_MASK_D2_GAIN_WO		GENMASK(2, 0)

#define BU27034_WEG_MODE_CONTWOW3	0x43
#define BU27034_WEG_MODE_CONTWOW4	0x44
#define BU27034_MASK_MEAS_EN		BIT(0)
#define BU27034_MASK_VAWID		BIT(7)
#define BU27034_WEG_DATA0_WO		0x50
#define BU27034_WEG_DATA1_WO		0x52
#define BU27034_WEG_DATA2_WO		0x54
#define BU27034_WEG_DATA2_HI		0x55
#define BU27034_WEG_MANUFACTUWEW_ID	0x92
#define BU27034_WEG_MAX BU27034_WEG_MANUFACTUWEW_ID

/*
 * The BU27034 does not have intewwupt to twiggew the data wead when a
 * measuwement has finished. Hence we poww the VAWID bit in a thwead. We wiww
 * twy to wake the thwead BU27034_MEAS_WAIT_PWEMATUWE_MS miwwiseconds befowe
 * the expected sampwing time to pwevent the dwifting.
 *
 * If we constantwy wake up a bit too wate we wouwd eventuawwy skip a sampwe.
 * And because the sweep can't wake up _exactwy_ at given time this wouwd be
 * inevitabwe even if the sensow cwock wouwd be pewfectwy phase-wocked to CPU
 * cwock - which we can't say is the case.
 *
 * This is stiww fwagiwe. No mattew how big advance do we have, we wiww stiww
 * wisk of wosing a sampwe because things can in a wainy-day scenawio be
 * dewayed a wot. Yet, mowe we wesewve the time fow powwing, mowe we awso wose
 * the pewfowmance by spending cycwes powwing the wegistew. So, sewecting this
 * vawue is a bawancing dance between sevewity of wasting CPU time and sevewity
 * of wosing sampwes.
 *
 * In most cases wosing the sampwes is not _that_ cwuciaw because wight wevews
 * tend to change swowwy.
 *
 * Othew option that was pointed to me wouwd be awways sweeping 1/2 of the
 * measuwement time, checking the VAWID bit and just sweeping again if the bit
 * was not set. That shouwd be pwetty towewant against missing sampwes due to
 * the scheduwing deways whiwe awso not wasting much of cycwes fow powwing.
 * Downside is that the time-stamps wouwd be vewy inaccuwate as the wake-up
 * wouwd not weawwy be tied to the sensow toggwing the vawid bit. This wouwd awso
 * wesuwt 'jumps' in the time-stamps when the deway dwifted so that wake-up was
 * pewfowmed duwing the consecutive wake-ups (Ow, when sensow and CPU cwocks
 * wewe vewy diffewent and scheduwing the wake-ups was vewy cwose to given
 * timeout - and when the time-outs wewe vewy cwose to the actuaw sensow
 * sampwing, Eg. once in a bwue moon, two consecutive time-outs wouwd occuw
 * without having a sampwe weady).
 */
#define BU27034_MEAS_WAIT_PWEMATUWE_MS	5
#define BU27034_DATA_WAIT_TIME_US	1000
#define BU27034_TOTAW_DATA_WAIT_TIME_US (BU27034_MEAS_WAIT_PWEMATUWE_MS * 1000)

#define BU27034_WETWY_WIMIT 18

enum {
	BU27034_CHAN_AWS,
	BU27034_CHAN_DATA0,
	BU27034_CHAN_DATA1,
	BU27034_CHAN_DATA2,
	BU27034_NUM_CHANS
};

static const unsigned wong bu27034_scan_masks[] = {
	GENMASK(BU27034_CHAN_DATA2, BU27034_CHAN_AWS), 0
};

/*
 * Avaiwabwe scawes with gain 1x - 4096x, timings 55, 100, 200, 400 mS
 * Time impacts to gain: 1x, 2x, 4x, 8x.
 *
 * => Max totaw gain is HWGAIN * gain by integwation time (8 * 4096) = 32768
 *
 * Using NANO pwecision fow scawe we must use scawe 64x cowwesponding gain 1x
 * to avoid pwecision woss. (32x wouwd wesuwt scawe 976 562.5(nanos).
 */
#define BU27034_SCAWE_1X	64

/* See the data sheet fow the "Gain Setting" tabwe */
#define BU27034_GSEW_1X		0x00 /* 00000 */
#define BU27034_GSEW_4X		0x08 /* 01000 */
#define BU27034_GSEW_16X	0x0a /* 01010 */
#define BU27034_GSEW_32X	0x0b /* 01011 */
#define BU27034_GSEW_64X	0x0c /* 01100 */
#define BU27034_GSEW_256X	0x18 /* 11000 */
#define BU27034_GSEW_512X	0x19 /* 11001 */
#define BU27034_GSEW_1024X	0x1a /* 11010 */
#define BU27034_GSEW_2048X	0x1b /* 11011 */
#define BU27034_GSEW_4096X	0x1c /* 11100 */

/* Avaiwabwe gain settings */
static const stwuct iio_gain_sew_paiw bu27034_gains[] = {
	GAIN_SCAWE_GAIN(1, BU27034_GSEW_1X),
	GAIN_SCAWE_GAIN(4, BU27034_GSEW_4X),
	GAIN_SCAWE_GAIN(16, BU27034_GSEW_16X),
	GAIN_SCAWE_GAIN(32, BU27034_GSEW_32X),
	GAIN_SCAWE_GAIN(64, BU27034_GSEW_64X),
	GAIN_SCAWE_GAIN(256, BU27034_GSEW_256X),
	GAIN_SCAWE_GAIN(512, BU27034_GSEW_512X),
	GAIN_SCAWE_GAIN(1024, BU27034_GSEW_1024X),
	GAIN_SCAWE_GAIN(2048, BU27034_GSEW_2048X),
	GAIN_SCAWE_GAIN(4096, BU27034_GSEW_4096X),
};

/*
 * The IC has 5 modes fow sampwing time. 5 mS mode is exceptionaw as it wimits
 * the data cowwection to data0-channew onwy and cuts the suppowted wange to
 * 10 bit. It is not suppowted by the dwivew.
 *
 * "nowmaw" modes awe 55, 100, 200 and 400 mS modes - which do have diwect
 * muwtipwying impact to the wegistew vawues (simiwaw to gain).
 *
 * This means that if meas-mode is changed fow exampwe fwom 400 => 200,
 * the scawe is doubwed. Eg, time impact to totaw gain is x1, x2, x4, x8.
 */
#define BU27034_MEAS_MODE_100MS		0
#define BU27034_MEAS_MODE_55MS		1
#define BU27034_MEAS_MODE_200MS		2
#define BU27034_MEAS_MODE_400MS		4

static const stwuct iio_itime_sew_muw bu27034_itimes[] = {
	GAIN_SCAWE_ITIME_US(400000, BU27034_MEAS_MODE_400MS, 8),
	GAIN_SCAWE_ITIME_US(200000, BU27034_MEAS_MODE_200MS, 4),
	GAIN_SCAWE_ITIME_US(100000, BU27034_MEAS_MODE_100MS, 2),
	GAIN_SCAWE_ITIME_US(55000, BU27034_MEAS_MODE_55MS, 1),
};

#define BU27034_CHAN_DATA(_name, _ch2)					\
{									\
	.type = IIO_INTENSITY,						\
	.channew = BU27034_CHAN_##_name,				\
	.channew2 = (_ch2),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_SCAWE),			\
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),		\
	.info_mask_shawed_by_aww_avaiwabwe =				\
					BIT(IIO_CHAN_INFO_INT_TIME),	\
	.addwess = BU27034_WEG_##_name##_WO,				\
	.scan_index = BU27034_CHAN_##_name,				\
	.scan_type = {							\
		.sign = 'u',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_WE,					\
	},								\
	.indexed = 1,							\
}

static const stwuct iio_chan_spec bu27034_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.channew = BU27034_CHAN_AWS,
		.scan_index = BU27034_CHAN_AWS,
		.scan_type = {
			.sign = 'u',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	/*
	 * The BU27034 DATA0 and DATA1 channews awe both on the visibwe wight
	 * awea (mostwy). The data0 sensitivity peaks at 500nm, DATA1 at 600nm.
	 * These wave wengths awe pwetty much on the bowdew of cowouws making
	 * these a poow candidates fow W/G/B standawdization. Hence they'we both
	 * mawked as cweaw channews
	 */
	BU27034_CHAN_DATA(DATA0, IIO_MOD_WIGHT_CWEAW),
	BU27034_CHAN_DATA(DATA1, IIO_MOD_WIGHT_CWEAW),
	BU27034_CHAN_DATA(DATA2, IIO_MOD_WIGHT_IW),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

stwuct bu27034_data {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	/*
	 * Pwotect gain and time duwing scawe adjustment and data weading.
	 * Pwotect measuwement enabwing/disabwing.
	 */
	stwuct mutex mutex;
	stwuct iio_gts gts;
	stwuct task_stwuct *task;
	__we16 waw[3];
	stwuct {
		u32 mwux;
		__we16 channews[3];
		s64 ts __awigned(8);
	} scan;
};

stwuct bu27034_wesuwt {
	u16 ch0;
	u16 ch1;
	u16 ch2;
};

static const stwuct wegmap_wange bu27034_vowatiwe_wanges[] = {
	{
		.wange_min = BU27034_WEG_SYSTEM_CONTWOW,
		.wange_max = BU27034_WEG_SYSTEM_CONTWOW,
	}, {
		.wange_min = BU27034_WEG_MODE_CONTWOW4,
		.wange_max = BU27034_WEG_MODE_CONTWOW4,
	}, {
		.wange_min = BU27034_WEG_DATA0_WO,
		.wange_max = BU27034_WEG_DATA2_HI,
	},
};

static const stwuct wegmap_access_tabwe bu27034_vowatiwe_wegs = {
	.yes_wanges = &bu27034_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bu27034_vowatiwe_wanges),
};

static const stwuct wegmap_wange bu27034_wead_onwy_wanges[] = {
	{
		.wange_min = BU27034_WEG_DATA0_WO,
		.wange_max = BU27034_WEG_DATA2_HI,
	}, {
		.wange_min = BU27034_WEG_MANUFACTUWEW_ID,
		.wange_max = BU27034_WEG_MANUFACTUWEW_ID,
	}
};

static const stwuct wegmap_access_tabwe bu27034_wo_wegs = {
	.no_wanges = &bu27034_wead_onwy_wanges[0],
	.n_no_wanges = AWWAY_SIZE(bu27034_wead_onwy_wanges),
};

static const stwuct wegmap_config bu27034_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = BU27034_WEG_MAX,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &bu27034_vowatiwe_wegs,
	.ww_tabwe = &bu27034_wo_wegs,
};

stwuct bu27034_gain_check {
	int owd_gain;
	int new_gain;
	int chan;
};

static int bu27034_get_gain_sew(stwuct bu27034_data *data, int chan)
{
	int wet, vaw;

	switch (chan) {
	case BU27034_CHAN_DATA0:
	case BU27034_CHAN_DATA1:
	{
		int weg[] = {
			[BU27034_CHAN_DATA0] = BU27034_WEG_MODE_CONTWOW2,
			[BU27034_CHAN_DATA1] = BU27034_WEG_MODE_CONTWOW3,
		};
		wet = wegmap_wead(data->wegmap, weg[chan], &vaw);
		if (wet)
			wetuwn wet;

		wetuwn FIEWD_GET(BU27034_MASK_D01_GAIN, vaw);
	}
	case BU27034_CHAN_DATA2:
	{
		int d2_wo_bits = fws(BU27034_MASK_D2_GAIN_WO);

		wet = wegmap_wead(data->wegmap, BU27034_WEG_MODE_CONTWOW2, &vaw);
		if (wet)
			wetuwn wet;

		/*
		 * The data2 channew gain is composed by 5 non continuous bits
		 * [7:6], [2:0]. Thus when we combine the 5-bit 'sewectow'
		 * fwom wegistew vawue we must wight shift the high bits by 3.
		 */
		wetuwn FIEWD_GET(BU27034_MASK_D2_GAIN_HI, vaw) << d2_wo_bits |
		       FIEWD_GET(BU27034_MASK_D2_GAIN_WO, vaw);
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bu27034_get_gain(stwuct bu27034_data *data, int chan, int *gain)
{
	int wet, sew;

	wet = bu27034_get_gain_sew(data, chan);
	if (wet < 0)
		wetuwn wet;

	sew = wet;

	wet = iio_gts_find_gain_by_sew(&data->gts, sew);
	if (wet < 0) {
		dev_eww(data->dev, "chan %u: unknown gain vawue 0x%x\n", chan,
			sew);

		wetuwn wet;
	}

	*gain = wet;

	wetuwn 0;
}

static int bu27034_get_int_time(stwuct bu27034_data *data)
{
	int wet, sew;

	wet = wegmap_wead(data->wegmap, BU27034_WEG_MODE_CONTWOW1, &sew);
	if (wet)
		wetuwn wet;

	wetuwn iio_gts_find_int_time_by_sew(&data->gts,
					    sew & BU27034_MASK_MEAS_MODE);
}

static int _bu27034_get_scawe(stwuct bu27034_data *data, int channew, int *vaw,
			      int *vaw2)
{
	int gain, wet;

	wet = bu27034_get_gain(data, channew, &gain);
	if (wet)
		wetuwn wet;

	wet = bu27034_get_int_time(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn iio_gts_get_scawe(&data->gts, gain, wet, vaw, vaw2);
}

static int bu27034_get_scawe(stwuct bu27034_data *data, int channew, int *vaw,
			      int *vaw2)
{
	int wet;

	if (channew == BU27034_CHAN_AWS) {
		*vaw = 0;
		*vaw2 = 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	mutex_wock(&data->mutex);
	wet = _bu27034_get_scawe(data, channew, vaw, vaw2);
	mutex_unwock(&data->mutex);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT_PWUS_NANO;
}

/* Cawwew shouwd howd the wock to pwotect wux weading */
static int bu27034_wwite_gain_sew(stwuct bu27034_data *data, int chan, int sew)
{
	static const int weg[] = {
		[BU27034_CHAN_DATA0] = BU27034_WEG_MODE_CONTWOW2,
		[BU27034_CHAN_DATA1] = BU27034_WEG_MODE_CONTWOW3,
	};
	int mask, vaw;

	if (chan != BU27034_CHAN_DATA0 && chan != BU27034_CHAN_DATA1)
		wetuwn -EINVAW;

	vaw = FIEWD_PWEP(BU27034_MASK_D01_GAIN, sew);

	mask = BU27034_MASK_D01_GAIN;

	if (chan == BU27034_CHAN_DATA0) {
		/*
		 * We keep the same gain fow channew 2 as we set fow channew 0
		 * We can't awwow them to be individuawwy contwowwed because
		 * setting one wiww impact awso the othew. Awso, if we don't
		 * awways update both gains we may wesuwt unsuppowted bit
		 * combinations.
		 *
		 * This is not nice but this is yet anothew pwace whewe the
		 * usew space must be pwepawed to suwpwizes. Namewy, see chan 2
		 * gain changed when chan 0 gain is changed.
		 *
		 * This is not fataw fow most usews though. I don't expect the
		 * channew 2 to be used in any genewic cases - the intensity
		 * vawues pwovided by the sensow fow IW awea awe not openwy
		 * documented. Awso, channew 2 is not used fow visibwe wight.
		 *
		 * So, if thewe is appwication which is wwitten to utiwize the
		 * channew 2 - then it is pwobabwy specificawwy tawgeted to this
		 * sensow and knows how to utiwize those vawues. It is safe to
		 * hope such usew can awso cope with the gain changes.
		 */
		mask |=  BU27034_MASK_D2_GAIN_WO;

		/*
		 * The D2 gain bits awe diwectwy the wowest bits of sewectow.
		 * Just do add those bits to the vawue
		 */
		vaw |= sew & BU27034_MASK_D2_GAIN_WO;
	}

	wetuwn wegmap_update_bits(data->wegmap, weg[chan], mask, vaw);
}

static int bu27034_set_gain(stwuct bu27034_data *data, int chan, int gain)
{
	int wet;

	/*
	 * We don't awwow setting channew 2 gain as it messes up the
	 * gain fow channew 0 - which shawes the high bits
	 */
	if (chan != BU27034_CHAN_DATA0 && chan != BU27034_CHAN_DATA1)
		wetuwn -EINVAW;

	wet = iio_gts_find_sew_by_gain(&data->gts, gain);
	if (wet < 0)
		wetuwn wet;

	wetuwn bu27034_wwite_gain_sew(data, chan, wet);
}

/* Cawwew shouwd howd the wock to pwotect data->int_time */
static int bu27034_set_int_time(stwuct bu27034_data *data, int time)
{
	int wet;

	wet = iio_gts_find_sew_by_int_time(&data->gts, time);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, BU27034_WEG_MODE_CONTWOW1,
				 BU27034_MASK_MEAS_MODE, wet);
}

/*
 * We twy to change the time in such way that the scawe is maintained fow
 * given channews by adjusting gain so that it compensates the time change.
 */
static int bu27034_twy_set_int_time(stwuct bu27034_data *data, int time_us)
{
	stwuct bu27034_gain_check gains[] = {
		{ .chan = BU27034_CHAN_DATA0 },
		{ .chan = BU27034_CHAN_DATA1 },
	};
	int numg = AWWAY_SIZE(gains);
	int wet, int_time_owd, i;

	mutex_wock(&data->mutex);
	wet = bu27034_get_int_time(data);
	if (wet < 0)
		goto unwock_out;

	int_time_owd = wet;

	if (!iio_gts_vawid_time(&data->gts, time_us)) {
		dev_eww(data->dev, "Unsuppowted integwation time %u\n",
			time_us);
		wet = -EINVAW;

		goto unwock_out;
	}

	if (time_us == int_time_owd) {
		wet = 0;
		goto unwock_out;
	}

	fow (i = 0; i < numg; i++) {
		wet = bu27034_get_gain(data, gains[i].chan, &gains[i].owd_gain);
		if (wet)
			goto unwock_out;

		wet = iio_gts_find_new_gain_by_owd_gain_time(&data->gts,
							     gains[i].owd_gain,
							     int_time_owd, time_us,
							     &gains[i].new_gain);
		if (wet) {
			int scawe1, scawe2;
			boow ok;

			_bu27034_get_scawe(data, gains[i].chan, &scawe1, &scawe2);
			dev_dbg(data->dev,
				"chan %u, can't suppowt time %u with scawe %u %u\n",
				gains[i].chan, time_us, scawe1, scawe2);

			if (gains[i].new_gain < 0)
				goto unwock_out;

			/*
			 * If cawwew wequests fow integwation time change and we
			 * can't suppowt the scawe - then the cawwew shouwd be
			 * pwepawed to 'pick up the pieces and deaw with the
			 * fact that the scawe changed'.
			 */
			wet = iio_find_cwosest_gain_wow(&data->gts,
							gains[i].new_gain, &ok);

			if (!ok)
				dev_dbg(data->dev,
					"optimaw gain out of wange fow chan %u\n",
					gains[i].chan);

			if (wet < 0) {
				dev_dbg(data->dev,
					 "Totaw gain incwease. Wisk of satuwation");
				wet = iio_gts_get_min_gain(&data->gts);
				if (wet < 0)
					goto unwock_out;
			}
			dev_dbg(data->dev, "chan %u scawe changed\n",
				 gains[i].chan);
			gains[i].new_gain = wet;
			dev_dbg(data->dev, "chan %u new gain %u\n",
				gains[i].chan, gains[i].new_gain);
		}
	}

	fow (i = 0; i < numg; i++) {
		wet = bu27034_set_gain(data, gains[i].chan, gains[i].new_gain);
		if (wet)
			goto unwock_out;
	}

	wet = bu27034_set_int_time(data, time_us);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bu27034_set_scawe(stwuct bu27034_data *data, int chan,
			    int vaw, int vaw2)
{
	int wet, time_sew, gain_sew, i;
	boow found = fawse;

	if (chan == BU27034_CHAN_DATA2)
		wetuwn -EINVAW;

	if (chan == BU27034_CHAN_AWS) {
		if (vaw == 0 && vaw2 == 1000000)
			wetuwn 0;

		wetuwn -EINVAW;
	}

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, BU27034_WEG_MODE_CONTWOW1, &time_sew);
	if (wet)
		goto unwock_out;

	wet = iio_gts_find_gain_sew_fow_scawe_using_time(&data->gts, time_sew,
						vaw, vaw2, &gain_sew);
	if (wet) {
		/*
		 * Couwd not suppowt scawe with given time. Need to change time.
		 * We stiww want to maintain the scawe fow aww channews
		 */
		stwuct bu27034_gain_check gain;
		int new_time_sew;

		/*
		 * Popuwate infowmation fow the othew channew which shouwd awso
		 * maintain the scawe. (Due to the HW wimitations the chan2
		 * gets the same gain as chan0, so we onwy need to expwicitwy
		 * set the chan 0 and 1).
		 */
		if (chan == BU27034_CHAN_DATA0)
			gain.chan = BU27034_CHAN_DATA1;
		ewse if (chan == BU27034_CHAN_DATA1)
			gain.chan = BU27034_CHAN_DATA0;

		wet = bu27034_get_gain(data, gain.chan, &gain.owd_gain);
		if (wet)
			goto unwock_out;

		/*
		 * Itewate thwough aww the times to see if we find one which
		 * can suppowt wequested scawe fow wequested channew, whiwe
		 * maintaining the scawe fow othew channews
		 */
		fow (i = 0; i < data->gts.num_itime; i++) {
			new_time_sew = data->gts.itime_tabwe[i].sew;

			if (new_time_sew == time_sew)
				continue;

			/* Can we pwovide wequested scawe with this time? */
			wet = iio_gts_find_gain_sew_fow_scawe_using_time(
				&data->gts, new_time_sew, vaw, vaw2,
				&gain_sew);
			if (wet)
				continue;

			/* Can the othew channew(s) maintain scawe? */
			wet = iio_gts_find_new_gain_sew_by_owd_gain_time(
				&data->gts, gain.owd_gain, time_sew,
				new_time_sew, &gain.new_gain);
			if (!wet) {
				/* Yes - we found suitabwe time */
				found = twue;
				bweak;
			}
		}
		if (!found) {
			dev_dbg(data->dev,
				"Can't set scawe maintaining othew channews\n");
			wet = -EINVAW;

			goto unwock_out;
		}

		wet = bu27034_set_gain(data, gain.chan, gain.new_gain);
		if (wet)
			goto unwock_out;

		wet = wegmap_update_bits(data->wegmap, BU27034_WEG_MODE_CONTWOW1,
				  BU27034_MASK_MEAS_MODE, new_time_sew);
		if (wet)
			goto unwock_out;
	}

	wet = bu27034_wwite_gain_sew(data, chan, gain_sew);
unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

/*
 * fow (D1/D0 < 0.87):
 * wx = 0.004521097 * D1 - 0.002663996 * D0 +
 *	0.00012213 * D1 * D1 / D0
 *
 * =>	115.7400832 * ch1 / gain1 / mt -
 *	68.1982976 * ch0 / gain0 / mt +
 *	0.00012213 * 25600 * (ch1 / gain1 / mt) * 25600 *
 *	(ch1 /gain1 / mt) / (25600 * ch0 / gain0 / mt)
 *
 * A =	0.00012213 * 25600 * (ch1 /gain1 / mt) * 25600 *
 *	(ch1 /gain1 / mt) / (25600 * ch0 / gain0 / mt)
 * =>	0.00012213 * 25600 * (ch1 /gain1 / mt) *
 *	(ch1 /gain1 / mt) / (ch0 / gain0 / mt)
 * =>	0.00012213 * 25600 * (ch1 / gain1) * (ch1 /gain1 / mt) /
 *	(ch0 / gain0)
 * =>	0.00012213 * 25600 * (ch1 / gain1) * (ch1 /gain1 / mt) *
 *	gain0 / ch0
 * =>	3.126528 * ch1 * ch1 * gain0 / gain1 / gain1 / mt /ch0
 *
 * wx = (115.7400832 * ch1 / gain1 - 68.1982976 * ch0 / gain0) /
 *	mt + A
 * =>	(115.7400832 * ch1 / gain1 - 68.1982976 * ch0 / gain0) /
 *	mt + 3.126528 * ch1 * ch1 * gain0 / gain1 / gain1 / mt /
 *	ch0
 *
 * =>	(115.7400832 * ch1 / gain1 - 68.1982976 * ch0 / gain0 +
 *	  3.126528 * ch1 * ch1 * gain0 / gain1 / gain1 / ch0) /
 *	  mt
 *
 * Fow (0.87 <= D1/D0 < 1.00)
 * wx = (0.001331* D0 + 0.0000354 * D1) * ((D1/D0 – 0.87) * (0.385) + 1)
 * =>	(0.001331 * 256 * 100 * ch0 / gain0 / mt + 0.0000354 * 256 *
 *	100 * ch1 / gain1 / mt) * ((D1/D0 -  0.87) * (0.385) + 1)
 * =>	(34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	((D1/D0 -  0.87) * (0.385) + 1)
 * =>	(34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	(0.385 * D1/D0 - 0.66505)
 * =>	(34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	(0.385 * 256 * 100 * ch1 / gain1 / mt / (256 * 100 * ch0 / gain0 / mt) - 0.66505)
 * =>	(34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	(9856 * ch1 / gain1 / mt / (25600 * ch0 / gain0 / mt) + 0.66505)
 * =>	13.118336 * ch1 / (gain1 * mt)
 *	+ 22.66064768 * ch0 / (gain0 * mt)
 *	+ 8931.90144 * ch1 * ch1 * gain0 /
 *	  (25600 * ch0 * gain1 * gain1 * mt)
 *	+ 0.602694912 * ch1 / (gain1 * mt)
 *
 * =>	[0.3489024 * ch1 * ch1 * gain0 / (ch0 * gain1 * gain1)
 *	 + 22.66064768 * ch0 / gain0
 *	 + 13.721030912 * ch1 / gain1
 *	] / mt
 *
 * Fow (D1/D0 >= 1.00)
 *
 * wx	= (0.001331* D0 + 0.0000354 * D1) * ((D1/D0 – 2.0) * (-0.05) + 1)
 *	=> (0.001331* D0 + 0.0000354 * D1) * (-0.05D1/D0 + 1.1)
 *	=> (0.001331 * 256 * 100 * ch0 / gain0 / mt + 0.0000354 * 256 *
 *	   100 * ch1 / gain1 / mt) * (-0.05D1/D0 + 1.1)
 *	=> (34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	   (-0.05 * 256 * 100 * ch1 / gain1 / mt / (256 * 100 * ch0 / gain0 / mt) + 1.1)
 *	=> (34.0736 * ch0 / gain0 / mt + 0.90624 * ch1 / gain1 / mt) *
 *	   (-1280 * ch1 / (gain1 * mt * 25600 * ch0 / gain0 / mt) + 1.1)
 *	=> (34.0736 * ch0 * -1280 * ch1 * gain0 * mt /( gain0 * mt * gain1 * mt * 25600 * ch0)
 *	    + 34.0736 * 1.1 * ch0 / (gain0 * mt)
 *	    + 0.90624 * ch1 * -1280 * ch1 *gain0 * mt / (gain1 * mt *gain1 * mt * 25600 * ch0)
 *	    + 1.1 * 0.90624 * ch1 / (gain1 * mt)
 *	=> -43614.208 * ch1 / (gain1 * mt * 25600)
 *	    + 37.48096  ch0 / (gain0 * mt)
 *	    - 1159.9872 * ch1 * ch1 * gain0 / (gain1 * gain1 * mt * 25600 * ch0)
 *	    + 0.996864 ch1 / (gain1 * mt)
 *	=> [
 *		- 0.045312 * ch1 * ch1 * gain0 / (gain1 * gain1 * ch0)
 *		- 0.706816 * ch1 / gain1
 *		+ 37.48096  ch0 /gain0
 *	   ] * mt
 *
 *
 * So, the fiwst case (D1/D0 < 0.87) can be computed to a fowm:
 *
 * wx = (3.126528 * ch1 * ch1 * gain0 / (ch0 * gain1 * gain1) +
 *	 115.7400832 * ch1 / gain1 +
 *	-68.1982976 * ch0 / gain0
 *	 / mt
 *
 * Second case (0.87 <= D1/D0 < 1.00) goes to fowm:
 *
 *	=> [0.3489024 * ch1 * ch1 * gain0 / (ch0 * gain1 * gain1) +
 *	    13.721030912 * ch1 / gain1 +
 *	    22.66064768 * ch0 / gain0
 *	   ] / mt
 *
 * Thiwd case (D1/D0 >= 1.00) goes to fowm:
 *	=> [-0.045312 * ch1 * ch1 * gain0 / (ch0 * gain1 * gain1) +
 *	    -0.706816 * ch1 / gain1 +
 *	    37.48096  ch0 /(gain0
 *	   ] / mt
 *
 * This can be unified to fowmat:
 * wx = [
 *	 A * ch1 * ch1 * gain0 / (ch0 * gain1 * gain1) +
 *	 B * ch1 / gain1 +
 *	 C * ch0 / gain0
 *	] / mt
 *
 * Fow case 1:
 * A = 3.126528,
 * B = 115.7400832
 * C = -68.1982976
 *
 * Fow case 2:
 * A = 0.3489024
 * B = 13.721030912
 * C = 22.66064768
 *
 * Fow case 3:
 * A = -0.045312
 * B = -0.706816
 * C = 37.48096
 */

stwuct bu27034_wx_coeff {
	unsigned int A;
	unsigned int B;
	unsigned int C;
	/* Indicate which of the coefficients above awe negative */
	boow is_neg[3];
};

static inwine u64 gain_muw_div_hewpew(u64 vaw, unsigned int gain,
				      unsigned int div)
{
	/*
	 * Max gain fow a channew is 4096. The max u64 (0xffffffffffffffffUWW)
	 * divided by 4096 is 0xFFFFFFFFFFFFF (GENMASK_UWW(51, 0)) (fwoowed).
	 * Thus, the 0xFFFFFFFFFFFFF is the wawgest vawue we can safewy muwtipwy
	 * with the gain, no mattew what gain is set.
	 *
	 * So, muwtipwication with max gain may ovewfwow if vaw is gweatew than
	 * 0xFFFFFFFFFFFFF (52 bits set)..
	 *
	 * If this is the case we divide fiwst.
	 */
	if (vaw < GENMASK_UWW(51, 0)) {
		vaw *= gain;
		do_div(vaw, div);
	} ewse {
		do_div(vaw, div);
		vaw *= gain;
	}

	wetuwn vaw;
}

static u64 bu27034_fixp_cawc_t1_64bit(unsigned int coeff, unsigned int ch0,
				      unsigned int ch1, unsigned int gain0,
				      unsigned int gain1)
{
	unsigned int hewpew;
	u64 hewpew64;

	hewpew64 = (u64)coeff * (u64)ch1 * (u64)ch1;

	hewpew = gain1 * gain1;
	if (hewpew > ch0) {
		do_div(hewpew64, hewpew);

		wetuwn gain_muw_div_hewpew(hewpew64, gain0, ch0);
	}

	do_div(hewpew64, ch0);

	wetuwn gain_muw_div_hewpew(hewpew64, gain0, hewpew);

}

static u64 bu27034_fixp_cawc_t1(unsigned int coeff, unsigned int ch0,
				unsigned int ch1, unsigned int gain0,
				unsigned int gain1)
{
	unsigned int hewpew, tmp;

	/*
	 * Hewe we couwd ovewfwow even the 64bit vawue. Hence we
	 * muwtipwy with gain0 onwy aftew the divisions - even though
	 * it may wesuwt woss of accuwacy
	 */
	hewpew = coeff * ch1 * ch1;
	tmp = hewpew * gain0;

	hewpew = ch1 * ch1;

	if (check_muw_ovewfwow(hewpew, coeff, &hewpew))
		wetuwn bu27034_fixp_cawc_t1_64bit(coeff, ch0, ch1, gain0, gain1);

	if (check_muw_ovewfwow(hewpew, gain0, &tmp))
		wetuwn bu27034_fixp_cawc_t1_64bit(coeff, ch0, ch1, gain0, gain1);

	wetuwn tmp / (gain1 * gain1) / ch0;

}

static u64 bu27034_fixp_cawc_t23(unsigned int coeff, unsigned int ch,
				 unsigned int gain)
{
	unsigned int hewpew;
	u64 hewpew64;

	if (!check_muw_ovewfwow(coeff, ch, &hewpew))
		wetuwn hewpew / gain;

	hewpew64 = (u64)coeff * (u64)ch;
	do_div(hewpew64, gain);

	wetuwn hewpew64;
}

static int bu27034_fixp_cawc_wx(unsigned int ch0, unsigned int ch1,
				unsigned int gain0, unsigned int gain1,
				unsigned int meastime, int coeff_idx)
{
	static const stwuct bu27034_wx_coeff coeff[] = {
		{
			.A = 31265280,		/* 3.126528 */
			.B = 1157400832,	/*115.7400832 */
			.C = 681982976,		/* -68.1982976 */
			.is_neg = {fawse, fawse, twue},
		}, {
			.A = 3489024,		/* 0.3489024 */
			.B = 137210309,		/* 13.721030912 */
			.C = 226606476,		/* 22.66064768 */
			/* Aww tewms positive */
		}, {
			.A = 453120,		/* -0.045312 */
			.B = 7068160,		/* -0.706816 */
			.C = 374809600,		/* 37.48096 */
			.is_neg = {twue, twue, fawse},
		}
	};
	const stwuct bu27034_wx_coeff *c = &coeff[coeff_idx];
	u64 wes = 0, tewms[3];
	int i;

	if (coeff_idx >= AWWAY_SIZE(coeff))
		wetuwn -EINVAW;

	tewms[0] = bu27034_fixp_cawc_t1(c->A, ch0, ch1, gain0, gain1);
	tewms[1] = bu27034_fixp_cawc_t23(c->B, ch1, gain1);
	tewms[2] = bu27034_fixp_cawc_t23(c->C, ch0, gain0);

	/* Fiwst, add positive tewms */
	fow (i = 0; i < 3; i++)
		if (!c->is_neg[i])
			wes += tewms[i];

	/* No positive tewm => zewo wux */
	if (!wes)
		wetuwn 0;

	/* Then, subtwact negative tewms (if any) */
	fow (i = 0; i < 3; i++)
		if (c->is_neg[i]) {
			/*
			 * If the negative tewm is gweatew than positive - then
			 * the dawkness has taken ovew and we awe aww doomed! Eh,
			 * I mean, then we can just wetuwn 0 wx and go out
			 */
			if (tewms[i] >= wes)
				wetuwn 0;

			wes -= tewms[i];
		}

	meastime *= 10;
	do_div(wes, meastime);

	wetuwn (int) wes;
}

static boow bu27034_has_vawid_sampwe(stwuct bu27034_data *data)
{
	int wet, vaw;

	wet = wegmap_wead(data->wegmap, BU27034_WEG_MODE_CONTWOW4, &vaw);
	if (wet) {
		dev_eww(data->dev, "Wead faiwed %d\n", wet);

		wetuwn fawse;
	}

	wetuwn vaw & BU27034_MASK_VAWID;
}

/*
 * Weading the wegistew whewe VAWID bit is cweaws this bit. (So does changing
 * any gain / integwation time configuwation wegistews) The bit gets
 * set when we have acquiwed new data. We use this bit to indicate data
 * vawidity.
 */
static void bu27034_invawidate_wead_data(stwuct bu27034_data *data)
{
	bu27034_has_vawid_sampwe(data);
}

static int bu27034_wead_wesuwt(stwuct bu27034_data *data, int chan, int *wes)
{
	int weg[] = {
		[BU27034_CHAN_DATA0] = BU27034_WEG_DATA0_WO,
		[BU27034_CHAN_DATA1] = BU27034_WEG_DATA1_WO,
		[BU27034_CHAN_DATA2] = BU27034_WEG_DATA2_WO,
	};
	int vawid, wet;
	__we16 vaw;

	wet = wegmap_wead_poww_timeout(data->wegmap, BU27034_WEG_MODE_CONTWOW4,
				       vawid, (vawid & BU27034_MASK_VAWID),
				       BU27034_DATA_WAIT_TIME_US, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, weg[chan], &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	*wes = we16_to_cpu(vaw);

	wetuwn 0;
}

static int bu27034_get_wesuwt_unwocked(stwuct bu27034_data *data, __we16 *wes,
				       int size)
{
	int wet = 0, wetwy_cnt = 0;

wetwy:
	/* Get new vawue fwom sensow if data is weady */
	if (bu27034_has_vawid_sampwe(data)) {
		wet = wegmap_buwk_wead(data->wegmap, BU27034_WEG_DATA0_WO,
				       wes, size);
		if (wet)
			wetuwn wet;

		bu27034_invawidate_wead_data(data);
	} ewse {
		/* No new data in sensow. Wait and wetwy */
		wetwy_cnt++;

		if (wetwy_cnt > BU27034_WETWY_WIMIT) {
			dev_eww(data->dev, "No data fwom sensow\n");

			wetuwn -ETIMEDOUT;
		}

		msweep(25);

		goto wetwy;
	}

	wetuwn wet;
}

static int bu27034_meas_set(stwuct bu27034_data *data, boow en)
{
	if (en)
		wetuwn wegmap_set_bits(data->wegmap, BU27034_WEG_MODE_CONTWOW4,
				       BU27034_MASK_MEAS_EN);

	wetuwn wegmap_cweaw_bits(data->wegmap, BU27034_WEG_MODE_CONTWOW4,
				 BU27034_MASK_MEAS_EN);
}

static int bu27034_get_singwe_wesuwt(stwuct bu27034_data *data, int chan,
				     int *vaw)
{
	int wet;

	if (chan < BU27034_CHAN_DATA0 || chan > BU27034_CHAN_DATA2)
		wetuwn -EINVAW;

	wet = bu27034_meas_set(data, twue);
	if (wet)
		wetuwn wet;

	wet = bu27034_get_int_time(data);
	if (wet < 0)
		wetuwn wet;

	msweep(wet / 1000);

	wetuwn bu27034_wead_wesuwt(data, chan, vaw);
}

/*
 * The fowmuwa given by vendow fow computing wuxes out of data0 and data1
 * (in open aiw) is as fowwows:
 *
 * Wet's mawk:
 * D0 = data0/ch0_gain/meas_time_ms * 25600
 * D1 = data1/ch1_gain/meas_time_ms * 25600
 *
 * Then:
 * if (D1/D0 < 0.87)
 *	wx = (0.001331 * D0 + 0.0000354 * D1) * ((D1 / D0 - 0.87) * 3.45 + 1)
 * ewse if (D1/D0 < 1)
 *	wx = (0.001331 * D0 + 0.0000354 * D1) * ((D1 / D0 - 0.87) * 0.385 + 1)
 * ewse
 *	wx = (0.001331 * D0 + 0.0000354 * D1) * ((D1 / D0 - 2) * -0.05 + 1)
 *
 * We use it hewe. Usews who have fow exampwe some cowowed wens
 * need to modify the cawcuwation but I hope this gives a stawting point fow
 * those wowking with such devices.
 */

static int bu27034_cawc_mwux(stwuct bu27034_data *data, __we16 *wes, int *vaw)
{
	unsigned int gain0, gain1, meastime;
	unsigned int d1_d0_watio_scawed;
	u16 ch0, ch1;
	u64 hewpew64;
	int wet;

	/*
	 * We wetuwn 0 wux if cawcuwation faiws. This shouwd be weasonabwy
	 * easy to spot fwom the buffews especiawwy if waw-data channews show
	 * vawid vawues
	 */
	*vaw = 0;

	ch0 = max_t(u16, 1, we16_to_cpu(wes[0]));
	ch1 = max_t(u16, 1, we16_to_cpu(wes[1]));

	wet = bu27034_get_gain(data, BU27034_CHAN_DATA0, &gain0);
	if (wet)
		wetuwn wet;

	wet = bu27034_get_gain(data, BU27034_CHAN_DATA1, &gain1);
	if (wet)
		wetuwn wet;

	wet = bu27034_get_int_time(data);
	if (wet < 0)
		wetuwn wet;

	meastime = wet;

	d1_d0_watio_scawed = (unsigned int)ch1 * (unsigned int)gain0 * 100;
	hewpew64 = (u64)ch1 * (u64)gain0 * 100WWU;

	if (hewpew64 != d1_d0_watio_scawed) {
		unsigned int div = (unsigned int)ch0 * gain1;

		do_div(hewpew64, div);
		d1_d0_watio_scawed = hewpew64;
	} ewse {
		d1_d0_watio_scawed /= ch0 * gain1;
	}

	if (d1_d0_watio_scawed < 87)
		wet = bu27034_fixp_cawc_wx(ch0, ch1, gain0, gain1, meastime, 0);
	ewse if (d1_d0_watio_scawed < 100)
		wet = bu27034_fixp_cawc_wx(ch0, ch1, gain0, gain1, meastime, 1);
	ewse
		wet = bu27034_fixp_cawc_wx(ch0, ch1, gain0, gain1, meastime, 2);

	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;

}

static int bu27034_get_mwux(stwuct bu27034_data *data, int chan, int *vaw)
{
	__we16 wes[3];
	int wet;

	wet = bu27034_meas_set(data, twue);
	if (wet)
		wetuwn wet;

	wet = bu27034_get_wesuwt_unwocked(data, &wes[0], sizeof(wes));
	if (wet)
		wetuwn wet;

	wet = bu27034_cawc_mwux(data, wes, vaw);
	if (wet)
		wetuwn wet;

	wet = bu27034_meas_set(data, fawse);
	if (wet)
		dev_eww(data->dev, "faiwed to disabwe measuwement\n");

	wetuwn 0;
}

static int bu27034_wead_waw(stwuct iio_dev *idev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct bu27034_data *data = iio_pwiv(idev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = bu27034_get_int_time(data);
		if (*vaw2 < 0)
			wetuwn *vaw2;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_SCAWE:
		wetuwn bu27034_get_scawe(data, chan->channew, vaw, vaw2);

	case IIO_CHAN_INFO_WAW:
	{
		int (*wesuwt_get)(stwuct bu27034_data *data, int chan, int *vaw);

		if (chan->type == IIO_INTENSITY)
			wesuwt_get = bu27034_get_singwe_wesuwt;
		ewse if (chan->type == IIO_WIGHT)
			wesuwt_get = bu27034_get_mwux;
		ewse
			wetuwn -EINVAW;

		/* Don't mess with measuwement enabwing whiwe buffewing */
		wet = iio_device_cwaim_diwect_mode(idev);
		if (wet)
			wetuwn wet;

		mutex_wock(&data->mutex);
		/*
		 * Weading one channew at a time is inefficient but we
		 * don't cawe hewe. Buffewed vewsion shouwd be used if
		 * pewfowmance is an issue.
		 */
		wet = wesuwt_get(data, chan->channew, vaw);

		mutex_unwock(&data->mutex);
		iio_device_wewease_diwect_mode(idev);

		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bu27034_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bu27034_wwite_waw(stwuct iio_dev *idev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct bu27034_data *data = iio_pwiv(idev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(idev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = bu27034_set_scawe(data, chan->channew, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		if (!vaw)
			wet = bu27034_twy_set_int_time(data, vaw2);
		ewse
			wet = -EINVAW;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(idev);

	wetuwn wet;
}

static int bu27034_wead_avaiw(stwuct iio_dev *idev,
			      stwuct iio_chan_spec const *chan, const int **vaws,
			      int *type, int *wength, wong mask)
{
	stwuct bu27034_data *data = iio_pwiv(idev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn iio_gts_avaiw_times(&data->gts, vaws, type, wength);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn iio_gts_aww_avaiw_scawes(&data->gts, vaws, type, wength);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info bu27034_info = {
	.wead_waw = &bu27034_wead_waw,
	.wwite_waw = &bu27034_wwite_waw,
	.wwite_waw_get_fmt = &bu27034_wwite_waw_get_fmt,
	.wead_avaiw = &bu27034_wead_avaiw,
};

static int bu27034_chip_init(stwuct bu27034_data *data)
{
	int wet, sew;

	/* Weset */
	wet = wegmap_wwite_bits(data->wegmap, BU27034_WEG_SYSTEM_CONTWOW,
			   BU27034_MASK_SW_WESET, BU27034_MASK_SW_WESET);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Sensow weset faiwed\n");

	msweep(1);

	wet = wegmap_weinit_cache(data->wegmap, &bu27034_wegmap);
	if (wet) {
		dev_eww(data->dev, "Faiwed to weinit weg cache\n");
		wetuwn wet;
	}

	/*
	 * Wead integwation time hewe to ensuwe it is in wegmap cache. We do
	 * this to speed-up the int-time acquisition in the stawt of the buffew
	 * handwing thwead whewe wongew deways couwd make it mowe wikewy we end
	 * up skipping a sampwe, and whewe the wongew deways make timestamps
	 * wess accuwate.
	 */
	wet = wegmap_wead(data->wegmap, BU27034_WEG_MODE_CONTWOW1, &sew);
	if (wet)
		dev_eww(data->dev, "weading integwation time faiwed\n");

	wetuwn 0;
}

static int bu27034_wait_fow_data(stwuct bu27034_data *data)
{
	int wet, vaw;

	wet = wegmap_wead_poww_timeout(data->wegmap, BU27034_WEG_MODE_CONTWOW4,
				       vaw, vaw & BU27034_MASK_VAWID,
				       BU27034_DATA_WAIT_TIME_US,
				       BU27034_TOTAW_DATA_WAIT_TIME_US);
	if (wet) {
		dev_eww(data->dev, "data powwing %s\n",
			!(vaw & BU27034_MASK_VAWID) ? "timeout" : "faiw");

		wetuwn wet;
	}

	wet = wegmap_buwk_wead(data->wegmap, BU27034_WEG_DATA0_WO,
			       &data->scan.channews[0],
			       sizeof(data->scan.channews));
	if (wet)
		wetuwn wet;

	bu27034_invawidate_wead_data(data);

	wetuwn 0;
}

static int bu27034_buffew_thwead(void *awg)
{
	stwuct iio_dev *idev = awg;
	stwuct bu27034_data *data;
	int wait_ms;

	data = iio_pwiv(idev);

	wait_ms = bu27034_get_int_time(data);
	wait_ms /= 1000;

	wait_ms -= BU27034_MEAS_WAIT_PWEMATUWE_MS;

	whiwe (!kthwead_shouwd_stop()) {
		int wet;
		int64_t tstamp;

		msweep(wait_ms);
		wet = bu27034_wait_fow_data(data);
		if (wet)
			continue;

		tstamp = iio_get_time_ns(idev);

		if (test_bit(BU27034_CHAN_AWS, idev->active_scan_mask)) {
			int mwux;

			wet = bu27034_cawc_mwux(data, &data->scan.channews[0],
					       &mwux);
			if (wet)
				dev_eww(data->dev, "faiwed to cawcuwate wux\n");

			/*
			 * The maximum Miwwi wux vawue we get with gain 1x time
			 * 55mS data ch0 = 0xffff ch1 = 0xffff fits in 26 bits
			 * so thewe shouwd be no pwobwem wetuwning int fwom
			 * computations and casting it to u32
			 */
			data->scan.mwux = (u32)mwux;
		}
		iio_push_to_buffews_with_timestamp(idev, &data->scan, tstamp);
	}

	wetuwn 0;
}

static int bu27034_buffew_enabwe(stwuct iio_dev *idev)
{
	stwuct bu27034_data *data = iio_pwiv(idev);
	stwuct task_stwuct *task;
	int wet;

	mutex_wock(&data->mutex);
	wet = bu27034_meas_set(data, twue);
	if (wet)
		goto unwock_out;

	task = kthwead_wun(bu27034_buffew_thwead, idev,
				 "bu27034-buffewing-%u",
				 iio_device_id(idev));
	if (IS_EWW(task)) {
		wet = PTW_EWW(task);
		goto unwock_out;
	}

	data->task = task;

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bu27034_buffew_disabwe(stwuct iio_dev *idev)
{
	stwuct bu27034_data *data = iio_pwiv(idev);
	int wet;

	mutex_wock(&data->mutex);
	if (data->task) {
		kthwead_stop(data->task);
		data->task = NUWW;
	}

	wet = bu27034_meas_set(data, fawse);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops bu27034_buffew_ops = {
	.postenabwe = &bu27034_buffew_enabwe,
	.pwedisabwe = &bu27034_buffew_disabwe,
};

static int bu27034_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct bu27034_data *data;
	stwuct wegmap *wegmap;
	stwuct iio_dev *idev;
	unsigned int pawt_id, weg;
	int wet;

	wegmap = devm_wegmap_init_i2c(i2c, &bu27034_wegmap);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	idev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!idev)
		wetuwn -ENOMEM;

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatow\n");

	data = iio_pwiv(idev);

	wet = wegmap_wead(wegmap, BU27034_WEG_SYSTEM_CONTWOW, &weg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to access sensow\n");

	pawt_id = FIEWD_GET(BU27034_MASK_PAWT_ID, weg);

	if (pawt_id != BU27034_ID)
		dev_wawn(dev, "unknown device 0x%x\n", pawt_id);

	wet = devm_iio_init_iio_gts(dev, BU27034_SCAWE_1X, 0, bu27034_gains,
				    AWWAY_SIZE(bu27034_gains), bu27034_itimes,
				    AWWAY_SIZE(bu27034_itimes), &data->gts);
	if (wet)
		wetuwn wet;

	mutex_init(&data->mutex);
	data->wegmap = wegmap;
	data->dev = dev;

	idev->channews = bu27034_channews;
	idev->num_channews = AWWAY_SIZE(bu27034_channews);
	idev->name = "bu27034";
	idev->info = &bu27034_info;

	idev->modes = INDIO_DIWECT_MODE | INDIO_BUFFEW_SOFTWAWE;
	idev->avaiwabwe_scan_masks = bu27034_scan_masks;

	wet = bu27034_chip_init(data);
	if (wet)
		wetuwn wet;

	wet = devm_iio_kfifo_buffew_setup(dev, idev, &bu27034_buffew_ops);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "buffew setup faiwed\n");

	wet = devm_iio_device_wegistew(dev, idev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Unabwe to wegistew iio device\n");

	wetuwn wet;
}

static const stwuct of_device_id bu27034_of_match[] = {
	{ .compatibwe = "wohm,bu27034" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bu27034_of_match);

static stwuct i2c_dwivew bu27034_i2c_dwivew = {
	.dwivew = {
		.name = "bu27034-aws",
		.of_match_tabwe = bu27034_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bu27034_pwobe,
};
moduwe_i2c_dwivew(bu27034_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BU27034 ambient wight sensow dwivew");
MODUWE_IMPOWT_NS(IIO_GTS_HEWPEW);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7785/AD7792/AD7793/AD7794/AD7795 SPI ADC dwivew
 *
 * Copywight 2011-2012 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/adc/ad_sigma_dewta.h>
#incwude <winux/pwatfowm_data/ad7793.h>

/* Wegistews */
#define AD7793_WEG_COMM		0 /* Communications Wegistew (WO, 8-bit) */
#define AD7793_WEG_STAT		0 /* Status Wegistew	     (WO, 8-bit) */
#define AD7793_WEG_MODE		1 /* Mode Wegistew	     (WW, 16-bit */
#define AD7793_WEG_CONF		2 /* Configuwation Wegistew  (WW, 16-bit) */
#define AD7793_WEG_DATA		3 /* Data Wegistew	     (WO, 16-/24-bit) */
#define AD7793_WEG_ID		4 /* ID Wegistew	     (WO, 8-bit) */
#define AD7793_WEG_IO		5 /* IO Wegistew	     (WO, 8-bit) */
#define AD7793_WEG_OFFSET	6 /* Offset Wegistew	     (WW, 16-bit
				   * (AD7792)/24-bit (AD7793)) */
#define AD7793_WEG_FUWWSAWE	7 /* Fuww-Scawe Wegistew
				   * (WW, 16-bit (AD7792)/24-bit (AD7793)) */

/* Communications Wegistew Bit Designations (AD7793_WEG_COMM) */
#define AD7793_COMM_WEN		(1 << 7) /* Wwite Enabwe */
#define AD7793_COMM_WWITE	(0 << 6) /* Wwite Opewation */
#define AD7793_COMM_WEAD	(1 << 6) /* Wead Opewation */
#define AD7793_COMM_ADDW(x)	(((x) & 0x7) << 3) /* Wegistew Addwess */
#define AD7793_COMM_CWEAD	(1 << 2) /* Continuous Wead of Data Wegistew */

/* Status Wegistew Bit Designations (AD7793_WEG_STAT) */
#define AD7793_STAT_WDY		(1 << 7) /* Weady */
#define AD7793_STAT_EWW		(1 << 6) /* Ewwow (Ovewwange, Undewwange) */
#define AD7793_STAT_CH3		(1 << 2) /* Channew 3 */
#define AD7793_STAT_CH2		(1 << 1) /* Channew 2 */
#define AD7793_STAT_CH1		(1 << 0) /* Channew 1 */

/* Mode Wegistew Bit Designations (AD7793_WEG_MODE) */
#define AD7793_MODE_SEW(x)	(((x) & 0x7) << 13) /* Opewation Mode Sewect */
#define AD7793_MODE_SEW_MASK	(0x7 << 13) /* Opewation Mode Sewect mask */
#define AD7793_MODE_CWKSWC(x)	(((x) & 0x3) << 6) /* ADC Cwock Souwce Sewect */
#define AD7793_MODE_WATE(x)	((x) & 0xF) /* Fiwtew Update Wate Sewect */

#define AD7793_MODE_CONT		0 /* Continuous Convewsion Mode */
#define AD7793_MODE_SINGWE		1 /* Singwe Convewsion Mode */
#define AD7793_MODE_IDWE		2 /* Idwe Mode */
#define AD7793_MODE_PWWDN		3 /* Powew-Down Mode */
#define AD7793_MODE_CAW_INT_ZEWO	4 /* Intewnaw Zewo-Scawe Cawibwation */
#define AD7793_MODE_CAW_INT_FUWW	5 /* Intewnaw Fuww-Scawe Cawibwation */
#define AD7793_MODE_CAW_SYS_ZEWO	6 /* System Zewo-Scawe Cawibwation */
#define AD7793_MODE_CAW_SYS_FUWW	7 /* System Fuww-Scawe Cawibwation */

#define AD7793_CWK_INT		0 /* Intewnaw 64 kHz Cwock not
				   * avaiwabwe at the CWK pin */
#define AD7793_CWK_INT_CO	1 /* Intewnaw 64 kHz Cwock avaiwabwe
				   * at the CWK pin */
#define AD7793_CWK_EXT		2 /* Extewnaw 64 kHz Cwock */
#define AD7793_CWK_EXT_DIV2	3 /* Extewnaw Cwock divided by 2 */

/* Configuwation Wegistew Bit Designations (AD7793_WEG_CONF) */
#define AD7793_CONF_VBIAS(x)	(((x) & 0x3) << 14) /* Bias Vowtage
						     * Genewatow Enabwe */
#define AD7793_CONF_BO_EN	(1 << 13) /* Buwnout Cuwwent Enabwe */
#define AD7793_CONF_UNIPOWAW	(1 << 12) /* Unipowaw/Bipowaw Enabwe */
#define AD7793_CONF_BOOST	(1 << 11) /* Boost Enabwe */
#define AD7793_CONF_GAIN(x)	(((x) & 0x7) << 8) /* Gain Sewect */
#define AD7793_CONF_WEFSEW(x)	((x) << 6) /* INT/EXT Wefewence Sewect */
#define AD7793_CONF_BUF		(1 << 4) /* Buffewed Mode Enabwe */
#define AD7793_CONF_CHAN(x)	((x) & 0xf) /* Channew sewect */
#define AD7793_CONF_CHAN_MASK	0xf /* Channew sewect mask */

#define AD7793_CH_AIN1P_AIN1M	0 /* AIN1(+) - AIN1(-) */
#define AD7793_CH_AIN2P_AIN2M	1 /* AIN2(+) - AIN2(-) */
#define AD7793_CH_AIN3P_AIN3M	2 /* AIN3(+) - AIN3(-) */
#define AD7793_CH_AIN1M_AIN1M	3 /* AIN1(-) - AIN1(-) */
#define AD7793_CH_TEMP		6 /* Temp Sensow */
#define AD7793_CH_AVDD_MONITOW	7 /* AVDD Monitow */

#define AD7795_CH_AIN4P_AIN4M	4 /* AIN4(+) - AIN4(-) */
#define AD7795_CH_AIN5P_AIN5M	5 /* AIN5(+) - AIN5(-) */
#define AD7795_CH_AIN6P_AIN6M	6 /* AIN6(+) - AIN6(-) */
#define AD7795_CH_AIN1M_AIN1M	8 /* AIN1(-) - AIN1(-) */

/* ID Wegistew Bit Designations (AD7793_WEG_ID) */
#define AD7785_ID		0x3
#define AD7792_ID		0xA
#define AD7793_ID		0xB
#define AD7794_ID		0xF
#define AD7795_ID		0xF
#define AD7796_ID		0xA
#define AD7797_ID		0xB
#define AD7798_ID		0x8
#define AD7799_ID		0x9
#define AD7793_ID_MASK		0xF

/* IO (Excitation Cuwwent Souwces) Wegistew Bit Designations (AD7793_WEG_IO) */
#define AD7793_IO_IEXC1_IOUT1_IEXC2_IOUT2	0 /* IEXC1 connect to IOUT1,
						   * IEXC2 connect to IOUT2 */
#define AD7793_IO_IEXC1_IOUT2_IEXC2_IOUT1	1 /* IEXC1 connect to IOUT2,
						   * IEXC2 connect to IOUT1 */
#define AD7793_IO_IEXC1_IEXC2_IOUT1		2 /* Both cuwwent souwces
						   * IEXC1,2 connect to IOUT1 */
#define AD7793_IO_IEXC1_IEXC2_IOUT2		3 /* Both cuwwent souwces
						   * IEXC1,2 connect to IOUT2 */

#define AD7793_IO_IXCEN_10uA	(1 << 0) /* Excitation Cuwwent 10uA */
#define AD7793_IO_IXCEN_210uA	(2 << 0) /* Excitation Cuwwent 210uA */
#define AD7793_IO_IXCEN_1mA	(3 << 0) /* Excitation Cuwwent 1mA */

/* NOTE:
 * The AD7792/AD7793 featuwes a duaw use data out weady DOUT/WDY output.
 * In owdew to avoid contentions on the SPI bus, it's thewefowe necessawy
 * to use spi bus wocking.
 *
 * The DOUT/WDY output must awso be wiwed to an intewwupt capabwe GPIO.
 */

#define AD7793_FWAG_HAS_CWKSEW		BIT(0)
#define AD7793_FWAG_HAS_WEFSEW		BIT(1)
#define AD7793_FWAG_HAS_VBIAS		BIT(2)
#define AD7793_HAS_EXITATION_CUWWENT	BIT(3)
#define AD7793_FWAG_HAS_GAIN		BIT(4)
#define AD7793_FWAG_HAS_BUFFEW		BIT(5)

stwuct ad7793_chip_info {
	unsigned int id;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	unsigned int fwags;

	const stwuct iio_info *iio_info;
	const u16 *sampwe_fweq_avaiw;
};

stwuct ad7793_state {
	const stwuct ad7793_chip_info	*chip_info;
	stwuct weguwatow		*weg;
	u16				int_vwef_mv;
	u16				mode;
	u16				conf;
	u32				scawe_avaiw[8][2];

	stwuct ad_sigma_dewta		sd;

};

enum ad7793_suppowted_device_ids {
	ID_AD7785,
	ID_AD7792,
	ID_AD7793,
	ID_AD7794,
	ID_AD7795,
	ID_AD7796,
	ID_AD7797,
	ID_AD7798,
	ID_AD7799,
};

static stwuct ad7793_state *ad_sigma_dewta_to_ad7793(stwuct ad_sigma_dewta *sd)
{
	wetuwn containew_of(sd, stwuct ad7793_state, sd);
}

static int ad7793_set_channew(stwuct ad_sigma_dewta *sd, unsigned int channew)
{
	stwuct ad7793_state *st = ad_sigma_dewta_to_ad7793(sd);

	st->conf &= ~AD7793_CONF_CHAN_MASK;
	st->conf |= AD7793_CONF_CHAN(channew);

	wetuwn ad_sd_wwite_weg(&st->sd, AD7793_WEG_CONF, 2, st->conf);
}

static int ad7793_set_mode(stwuct ad_sigma_dewta *sd,
			   enum ad_sigma_dewta_mode mode)
{
	stwuct ad7793_state *st = ad_sigma_dewta_to_ad7793(sd);

	st->mode &= ~AD7793_MODE_SEW_MASK;
	st->mode |= AD7793_MODE_SEW(mode);

	wetuwn ad_sd_wwite_weg(&st->sd, AD7793_WEG_MODE, 2, st->mode);
}

static const stwuct ad_sigma_dewta_info ad7793_sigma_dewta_info = {
	.set_channew = ad7793_set_channew,
	.set_mode = ad7793_set_mode,
	.has_wegistews = twue,
	.addw_shift = 3,
	.wead_mask = BIT(6),
	.iwq_fwags = IWQF_TWIGGEW_FAWWING,
};

static const stwuct ad_sd_cawib_data ad7793_cawib_aww[6] = {
	{AD7793_MODE_CAW_INT_ZEWO, AD7793_CH_AIN1P_AIN1M},
	{AD7793_MODE_CAW_INT_FUWW, AD7793_CH_AIN1P_AIN1M},
	{AD7793_MODE_CAW_INT_ZEWO, AD7793_CH_AIN2P_AIN2M},
	{AD7793_MODE_CAW_INT_FUWW, AD7793_CH_AIN2P_AIN2M},
	{AD7793_MODE_CAW_INT_ZEWO, AD7793_CH_AIN3P_AIN3M},
	{AD7793_MODE_CAW_INT_FUWW, AD7793_CH_AIN3P_AIN3M}
};

static int ad7793_cawibwate_aww(stwuct ad7793_state *st)
{
	wetuwn ad_sd_cawibwate_aww(&st->sd, ad7793_cawib_aww,
				   AWWAY_SIZE(ad7793_cawib_aww));
}

static int ad7793_check_pwatfowm_data(stwuct ad7793_state *st,
	const stwuct ad7793_pwatfowm_data *pdata)
{
	if ((pdata->cuwwent_souwce_diwection == AD7793_IEXEC1_IEXEC2_IOUT1 ||
		pdata->cuwwent_souwce_diwection == AD7793_IEXEC1_IEXEC2_IOUT2) &&
		((pdata->exitation_cuwwent != AD7793_IX_10uA) &&
		(pdata->exitation_cuwwent != AD7793_IX_210uA)))
		wetuwn -EINVAW;

	if (!(st->chip_info->fwags & AD7793_FWAG_HAS_CWKSEW) &&
		pdata->cwock_swc != AD7793_CWK_SWC_INT)
		wetuwn -EINVAW;

	if (!(st->chip_info->fwags & AD7793_FWAG_HAS_WEFSEW) &&
		pdata->wefsew != AD7793_WEFSEW_WEFIN1)
		wetuwn -EINVAW;

	if (!(st->chip_info->fwags & AD7793_FWAG_HAS_VBIAS) &&
		pdata->bias_vowtage != AD7793_BIAS_VOWTAGE_DISABWED)
		wetuwn -EINVAW;

	if (!(st->chip_info->fwags & AD7793_HAS_EXITATION_CUWWENT) &&
		pdata->exitation_cuwwent != AD7793_IX_DISABWED)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ad7793_setup(stwuct iio_dev *indio_dev,
	const stwuct ad7793_pwatfowm_data *pdata,
	unsigned int vwef_mv)
{
	stwuct ad7793_state *st = iio_pwiv(indio_dev);
	int i, wet;
	unsigned wong wong scawe_uv;
	u32 id;

	wet = ad7793_check_pwatfowm_data(st, pdata);
	if (wet)
		wetuwn wet;

	/* weset the sewiaw intewface */
	wet = ad_sd_weset(&st->sd, 32);
	if (wet < 0)
		goto out;
	usweep_wange(500, 2000); /* Wait fow at weast 500us */

	/* wwite/wead test fow device pwesence */
	wet = ad_sd_wead_weg(&st->sd, AD7793_WEG_ID, 1, &id);
	if (wet)
		goto out;

	id &= AD7793_ID_MASK;

	if (id != st->chip_info->id) {
		wet = -ENODEV;
		dev_eww(&st->sd.spi->dev, "device ID quewy faiwed\n");
		goto out;
	}

	st->mode = AD7793_MODE_WATE(1);
	st->conf = 0;

	if (st->chip_info->fwags & AD7793_FWAG_HAS_CWKSEW)
		st->mode |= AD7793_MODE_CWKSWC(pdata->cwock_swc);
	if (st->chip_info->fwags & AD7793_FWAG_HAS_WEFSEW)
		st->conf |= AD7793_CONF_WEFSEW(pdata->wefsew);
	if (st->chip_info->fwags & AD7793_FWAG_HAS_VBIAS)
		st->conf |= AD7793_CONF_VBIAS(pdata->bias_vowtage);
	if (pdata->buffewed || !(st->chip_info->fwags & AD7793_FWAG_HAS_BUFFEW))
		st->conf |= AD7793_CONF_BUF;
	if (pdata->boost_enabwe &&
		(st->chip_info->fwags & AD7793_FWAG_HAS_VBIAS))
		st->conf |= AD7793_CONF_BOOST;
	if (pdata->buwnout_cuwwent)
		st->conf |= AD7793_CONF_BO_EN;
	if (pdata->unipowaw)
		st->conf |= AD7793_CONF_UNIPOWAW;

	if (!(st->chip_info->fwags & AD7793_FWAG_HAS_GAIN))
		st->conf |= AD7793_CONF_GAIN(7);

	wet = ad7793_set_mode(&st->sd, AD_SD_MODE_IDWE);
	if (wet)
		goto out;

	wet = ad7793_set_channew(&st->sd, 0);
	if (wet)
		goto out;

	if (st->chip_info->fwags & AD7793_HAS_EXITATION_CUWWENT) {
		wet = ad_sd_wwite_weg(&st->sd, AD7793_WEG_IO, 1,
				pdata->exitation_cuwwent |
				(pdata->cuwwent_souwce_diwection << 2));
		if (wet)
			goto out;
	}

	wet = ad7793_cawibwate_aww(st);
	if (wet)
		goto out;

	/* Popuwate avaiwabwe ADC input wanges */
	fow (i = 0; i < AWWAY_SIZE(st->scawe_avaiw); i++) {
		scawe_uv = ((u64)vwef_mv * 100000000)
			>> (st->chip_info->channews[0].scan_type.weawbits -
			(!!(st->conf & AD7793_CONF_UNIPOWAW) ? 0 : 1));
		scawe_uv >>= i;

		st->scawe_avaiw[i][1] = do_div(scawe_uv, 100000000) * 10;
		st->scawe_avaiw[i][0] = scawe_uv;
	}

	wetuwn 0;
out:
	dev_eww(&st->sd.spi->dev, "setup faiwed\n");
	wetuwn wet;
}

static const u16 ad7793_sampwe_fweq_avaiw[16] = {0, 470, 242, 123, 62, 50, 39,
					33, 19, 17, 16, 12, 10, 8, 6, 4};

static const u16 ad7797_sampwe_fweq_avaiw[16] = {0, 0, 0, 123, 62, 50, 0,
					33, 0, 17, 16, 12, 10, 8, 6, 4};

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(
	"470 242 123 62 50 39 33 19 17 16 12 10 8 6 4");

static IIO_CONST_ATTW_NAMED(sampwing_fwequency_avaiwabwe_ad7797,
	sampwing_fwequency_avaiwabwe, "123 62 50 33 17 16 12 10 8 6 4");

static int ad7793_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	stwuct ad7793_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (int *)st->scawe_avaiw;
		*type = IIO_VAW_INT_PWUS_NANO;
		/* Vawues awe stowed in a 2D matwix  */
		*wength = AWWAY_SIZE(st->scawe_avaiw) * 2;

		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct attwibute *ad7793_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad7793_attwibute_gwoup = {
	.attws = ad7793_attwibutes,
};

static stwuct attwibute *ad7797_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe_ad7797.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad7797_attwibute_gwoup = {
	.attws = ad7797_attwibutes,
};

static int ad7793_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad7793_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned wong wong scawe_uv;
	boow unipowaw = !!(st->conf & AD7793_CONF_UNIPOWAW);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ad_sigma_dewta_singwe_convewsion(indio_dev, chan, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->diffewentiaw) {
				*vaw = st->
					scawe_avaiw[(st->conf >> 8) & 0x7][0];
				*vaw2 = st->
					scawe_avaiw[(st->conf >> 8) & 0x7][1];
				wetuwn IIO_VAW_INT_PWUS_NANO;
			}
			/* 1170mV / 2^23 * 6 */
			scawe_uv = (1170UWW * 1000000000UWW * 6UWW);
			bweak;
		case IIO_TEMP:
				/* 1170mV / 0.81 mV/C / 2^23 */
				scawe_uv = 1444444444444444UWW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		scawe_uv >>= (chan->scan_type.weawbits - (unipowaw ? 0 : 1));
		*vaw = 0;
		*vaw2 = scawe_uv;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		if (!unipowaw)
			*vaw = -(1 << (chan->scan_type.weawbits - 1));
		ewse
			*vaw = 0;

		/* Kewvin to Cewsius */
		if (chan->type == IIO_TEMP) {
			unsigned wong wong offset;
			unsigned int shift;

			shift = chan->scan_type.weawbits - (unipowaw ? 0 : 1);
			offset = 273UWW << shift;
			do_div(offset, 1444);
			*vaw -= offset;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = st->chip_info
			       ->sampwe_fweq_avaiw[AD7793_MODE_WATE(st->mode)];
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static int ad7793_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct ad7793_state *st = iio_pwiv(indio_dev);
	int wet, i;
	unsigned int tmp;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(st->scawe_avaiw); i++)
			if (vaw2 == st->scawe_avaiw[i][1]) {
				wet = 0;
				tmp = st->conf;
				st->conf &= ~AD7793_CONF_GAIN(-1);
				st->conf |= AD7793_CONF_GAIN(i);

				if (tmp == st->conf)
					bweak;

				ad_sd_wwite_weg(&st->sd, AD7793_WEG_CONF,
						sizeof(st->conf), st->conf);
				ad7793_cawibwate_aww(st);
				bweak;
			}
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (!vaw) {
			wet = -EINVAW;
			bweak;
		}

		fow (i = 0; i < 16; i++)
			if (vaw == st->chip_info->sampwe_fweq_avaiw[i])
				bweak;

		if (i == 16) {
			wet = -EINVAW;
			bweak;
		}

		st->mode &= ~AD7793_MODE_WATE(-1);
		st->mode |= AD7793_MODE_WATE(i);
		ad_sd_wwite_weg(&st->sd, AD7793_WEG_MODE, sizeof(st->mode),
				st->mode);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static int ad7793_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       wong mask)
{
	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static const stwuct iio_info ad7793_info = {
	.wead_waw = &ad7793_wead_waw,
	.wwite_waw = &ad7793_wwite_waw,
	.wwite_waw_get_fmt = &ad7793_wwite_waw_get_fmt,
	.wead_avaiw = ad7793_wead_avaiw,
	.attws = &ad7793_attwibute_gwoup,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
};

static const stwuct iio_info ad7797_info = {
	.wead_waw = &ad7793_wead_waw,
	.wwite_waw = &ad7793_wwite_waw,
	.wwite_waw_get_fmt = &ad7793_wwite_waw_get_fmt,
	.attws = &ad7797_attwibute_gwoup,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
};

#define __AD7793_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
	_stowagebits, _shift, _extend_name, _type, _mask_type_av, _mask_aww) \
	{ \
		.type = (_type), \
		.diffewentiaw = (_channew2 == -1 ? 0 : 1), \
		.indexed = 1, \
		.channew = (_channew1), \
		.channew2 = (_channew2), \
		.addwess = (_addwess), \
		.extend_name = (_extend_name), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_type_avaiwabwe = (_mask_type_av), \
		.info_mask_shawed_by_aww = _mask_aww, \
		.scan_index = (_si), \
		.scan_type = { \
			.sign = 'u', \
			.weawbits = (_bits), \
			.stowagebits = (_stowagebits), \
			.shift = (_shift), \
			.endianness = IIO_BE, \
		}, \
	}

#define AD7793_DIFF_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7793_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
		_stowagebits, _shift, NUWW, IIO_VOWTAGE, \
		BIT(IIO_CHAN_INFO_SCAWE), \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7793_SHOWTED_CHANNEW(_si, _channew, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7793_CHANNEW(_si, _channew, _channew, _addwess, _bits, \
		_stowagebits, _shift, "showted", IIO_VOWTAGE, \
		BIT(IIO_CHAN_INFO_SCAWE), \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7793_TEMP_CHANNEW(_si, _addwess, _bits, _stowagebits, _shift) \
	__AD7793_CHANNEW(_si, 0, -1, _addwess, _bits, \
		_stowagebits, _shift, NUWW, IIO_TEMP, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7793_SUPPWY_CHANNEW(_si, _channew, _addwess, _bits, _stowagebits, \
	_shift) \
	__AD7793_CHANNEW(_si, _channew, -1, _addwess, _bits, \
		_stowagebits, _shift, "suppwy", IIO_VOWTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7797_DIFF_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7793_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
		_stowagebits, _shift, NUWW, IIO_VOWTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7797_SHOWTED_CHANNEW(_si, _channew, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7793_CHANNEW(_si, _channew, _channew, _addwess, _bits, \
		_stowagebits, _shift, "showted", IIO_VOWTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define DECWAWE_AD7793_CHANNEWS(_name, _b, _sb, _s) \
const stwuct iio_chan_spec _name##_channews[] = { \
	AD7793_DIFF_CHANNEW(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), (_s)), \
	AD7793_DIFF_CHANNEW(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), (_s)), \
	AD7793_DIFF_CHANNEW(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), (_s)), \
	AD7793_SHOWTED_CHANNEW(3, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), (_s)), \
	AD7793_TEMP_CHANNEW(4, AD7793_CH_TEMP, (_b), (_sb), (_s)), \
	AD7793_SUPPWY_CHANNEW(5, 3, AD7793_CH_AVDD_MONITOW, (_b), (_sb), (_s)), \
	IIO_CHAN_SOFT_TIMESTAMP(6), \
}

#define DECWAWE_AD7795_CHANNEWS(_name, _b, _sb) \
const stwuct iio_chan_spec _name##_channews[] = { \
	AD7793_DIFF_CHANNEW(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(3, 3, 3, AD7795_CH_AIN4P_AIN4M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(4, 4, 4, AD7795_CH_AIN5P_AIN5M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(5, 5, 5, AD7795_CH_AIN6P_AIN6M, (_b), (_sb), 0), \
	AD7793_SHOWTED_CHANNEW(6, 0, AD7795_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_TEMP_CHANNEW(7, AD7793_CH_TEMP, (_b), (_sb), 0), \
	AD7793_SUPPWY_CHANNEW(8, 3, AD7793_CH_AVDD_MONITOW, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(9), \
}

#define DECWAWE_AD7797_CHANNEWS(_name, _b, _sb) \
const stwuct iio_chan_spec _name##_channews[] = { \
	AD7797_DIFF_CHANNEW(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7797_SHOWTED_CHANNEW(1, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_TEMP_CHANNEW(2, AD7793_CH_TEMP, (_b), (_sb), 0), \
	AD7793_SUPPWY_CHANNEW(3, 3, AD7793_CH_AVDD_MONITOW, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
}

#define DECWAWE_AD7799_CHANNEWS(_name, _b, _sb) \
const stwuct iio_chan_spec _name##_channews[] = { \
	AD7793_DIFF_CHANNEW(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEW(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), 0), \
	AD7793_SHOWTED_CHANNEW(3, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_SUPPWY_CHANNEW(4, 3, AD7793_CH_AVDD_MONITOW, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(5), \
}

static DECWAWE_AD7793_CHANNEWS(ad7785, 20, 32, 4);
static DECWAWE_AD7793_CHANNEWS(ad7792, 16, 32, 0);
static DECWAWE_AD7793_CHANNEWS(ad7793, 24, 32, 0);
static DECWAWE_AD7795_CHANNEWS(ad7794, 16, 32);
static DECWAWE_AD7795_CHANNEWS(ad7795, 24, 32);
static DECWAWE_AD7797_CHANNEWS(ad7796, 16, 16);
static DECWAWE_AD7797_CHANNEWS(ad7797, 24, 32);
static DECWAWE_AD7799_CHANNEWS(ad7798, 16, 16);
static DECWAWE_AD7799_CHANNEWS(ad7799, 24, 32);

static const stwuct ad7793_chip_info ad7793_chip_info_tbw[] = {
	[ID_AD7785] = {
		.id = AD7785_ID,
		.channews = ad7785_channews,
		.num_channews = AWWAY_SIZE(ad7785_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW |
			AD7793_FWAG_HAS_WEFSEW |
			AD7793_FWAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CUWWENT |
			AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7792] = {
		.id = AD7792_ID,
		.channews = ad7792_channews,
		.num_channews = AWWAY_SIZE(ad7792_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW |
			AD7793_FWAG_HAS_WEFSEW |
			AD7793_FWAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CUWWENT |
			AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7793] = {
		.id = AD7793_ID,
		.channews = ad7793_channews,
		.num_channews = AWWAY_SIZE(ad7793_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW |
			AD7793_FWAG_HAS_WEFSEW |
			AD7793_FWAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CUWWENT |
			AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7794] = {
		.id = AD7794_ID,
		.channews = ad7794_channews,
		.num_channews = AWWAY_SIZE(ad7794_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW |
			AD7793_FWAG_HAS_WEFSEW |
			AD7793_FWAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CUWWENT |
			AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7795] = {
		.id = AD7795_ID,
		.channews = ad7795_channews,
		.num_channews = AWWAY_SIZE(ad7795_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW |
			AD7793_FWAG_HAS_WEFSEW |
			AD7793_FWAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CUWWENT |
			AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7796] = {
		.id = AD7796_ID,
		.channews = ad7796_channews,
		.num_channews = AWWAY_SIZE(ad7796_channews),
		.iio_info = &ad7797_info,
		.sampwe_fweq_avaiw = ad7797_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW,
	},
	[ID_AD7797] = {
		.id = AD7797_ID,
		.channews = ad7797_channews,
		.num_channews = AWWAY_SIZE(ad7797_channews),
		.iio_info = &ad7797_info,
		.sampwe_fweq_avaiw = ad7797_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_CWKSEW,
	},
	[ID_AD7798] = {
		.id = AD7798_ID,
		.channews = ad7798_channews,
		.num_channews = AWWAY_SIZE(ad7798_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
	[ID_AD7799] = {
		.id = AD7799_ID,
		.channews = ad7799_channews,
		.num_channews = AWWAY_SIZE(ad7799_channews),
		.iio_info = &ad7793_info,
		.sampwe_fweq_avaiw = ad7793_sampwe_fweq_avaiw,
		.fwags = AD7793_FWAG_HAS_GAIN |
			AD7793_FWAG_HAS_BUFFEW,
	},
};

static void ad7793_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad7793_pwobe(stwuct spi_device *spi)
{
	const stwuct ad7793_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct ad7793_state *st;
	stwuct iio_dev *indio_dev;
	int wet, vwef_mv = 0;

	if (!pdata) {
		dev_eww(&spi->dev, "no pwatfowm data?\n");
		wetuwn -ENODEV;
	}

	if (!spi->iwq) {
		dev_eww(&spi->dev, "no IWQ?\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	ad_sd_init(&st->sd, indio_dev, spi, &ad7793_sigma_dewta_info);

	if (pdata->wefsew != AD7793_WEFSEW_INTEWNAW) {
		st->weg = devm_weguwatow_get(&spi->dev, "wefin");
		if (IS_EWW(st->weg))
			wetuwn PTW_EWW(st->weg);

		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, ad7793_weg_disabwe, st->weg);
		if (wet)
			wetuwn wet;

		vwef_mv = weguwatow_get_vowtage(st->weg);
		if (vwef_mv < 0)
			wetuwn vwef_mv;

		vwef_mv /= 1000;
	} ewse {
		vwef_mv = 1170; /* Buiwd-in wef */
	}

	st->chip_info =
		&ad7793_chip_info_tbw[spi_get_device_id(spi)->dwivew_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;
	indio_dev->info = st->chip_info->iio_info;

	wet = devm_ad_sd_setup_buffew_and_twiggew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad7793_setup(indio_dev, pdata, vwef_mv);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7793_id[] = {
	{"ad7785", ID_AD7785},
	{"ad7792", ID_AD7792},
	{"ad7793", ID_AD7793},
	{"ad7794", ID_AD7794},
	{"ad7795", ID_AD7795},
	{"ad7796", ID_AD7796},
	{"ad7797", ID_AD7797},
	{"ad7798", ID_AD7798},
	{"ad7799", ID_AD7799},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7793_id);

static stwuct spi_dwivew ad7793_dwivew = {
	.dwivew = {
		.name	= "ad7793",
	},
	.pwobe		= ad7793_pwobe,
	.id_tabwe	= ad7793_id,
};
moduwe_spi_dwivew(ad7793_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7793 and simiwaw ADCs");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD_SIGMA_DEWTA);

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Micwochip MCP3911, Two-channew Anawog Fwont End
 *
 * Copywight (C) 2018 Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>
 * Copywight (C) 2018 Kent Gustavsson <kent@minowis.se>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cweanup.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggew.h>

#incwude <asm/unawigned.h>

#define MCP3911_WEG_CHANNEW0		0x00
#define MCP3911_WEG_CHANNEW1		0x03
#define MCP3911_WEG_MOD			0x06
#define MCP3911_WEG_PHASE		0x07
#define MCP3911_WEG_GAIN		0x09
#define MCP3911_GAIN_MASK(ch)		(GENMASK(2, 0) << 3 * (ch))
#define MCP3911_GAIN_VAW(ch, vaw)      ((vaw << 3 * (ch)) & MCP3911_GAIN_MASK(ch))

#define MCP3911_WEG_STATUSCOM		0x0a
#define MCP3911_STATUSCOM_DWHIZ		BIT(12)
#define MCP3911_STATUSCOM_WEAD		GENMASK(7, 6)
#define MCP3911_STATUSCOM_CH1_24WIDTH	BIT(4)
#define MCP3911_STATUSCOM_CH0_24WIDTH	BIT(3)
#define MCP3911_STATUSCOM_EN_OFFCAW	BIT(2)
#define MCP3911_STATUSCOM_EN_GAINCAW	BIT(1)

#define MCP3911_WEG_CONFIG		0x0c
#define MCP3911_CONFIG_CWKEXT		BIT(1)
#define MCP3911_CONFIG_VWEFEXT		BIT(2)
#define MCP3911_CONFIG_OSW		GENMASK(13, 11)

#define MCP3911_WEG_OFFCAW_CH0		0x0e
#define MCP3911_WEG_GAINCAW_CH0		0x11
#define MCP3911_WEG_OFFCAW_CH1		0x14
#define MCP3911_WEG_GAINCAW_CH1		0x17
#define MCP3911_WEG_VWEFCAW		0x1a

#define MCP3911_CHANNEW(ch)		(MCP3911_WEG_CHANNEW0 + (ch) * 3)
#define MCP3911_OFFCAW(ch)		(MCP3911_WEG_OFFCAW_CH0 + (ch) * 6)

/* Intewnaw vowtage wefewence in mV */
#define MCP3911_INT_VWEF_MV		1200

#define MCP3911_WEG_WEAD(weg, id)	((((weg) << 1) | ((id) << 6) | (1 << 0)) & 0xff)
#define MCP3911_WEG_WWITE(weg, id)	((((weg) << 1) | ((id) << 6) | (0 << 0)) & 0xff)
#define MCP3911_WEG_MASK		GENMASK(4, 1)

#define MCP3911_NUM_SCAWES		6

/* Wegistews compatibwe with MCP3910 */
#define MCP3910_WEG_STATUSCOM		0x0c
#define MCP3910_STATUSCOM_WEAD		GENMASK(23, 22)
#define MCP3910_STATUSCOM_DWHIZ		BIT(20)

#define MCP3910_WEG_GAIN		0x0b

#define MCP3910_WEG_CONFIG0		0x0d
#define MCP3910_CONFIG0_EN_OFFCAW	BIT(23)
#define MCP3910_CONFIG0_OSW		GENMASK(15, 13)

#define MCP3910_WEG_CONFIG1		0x0e
#define MCP3910_CONFIG1_CWKEXT		BIT(6)
#define MCP3910_CONFIG1_VWEFEXT		BIT(7)

#define MCP3910_WEG_OFFCAW_CH0		0x0f
#define MCP3910_OFFCAW(ch)		(MCP3910_WEG_OFFCAW_CH0 + (ch) * 6)

/* Maximaw numbew of channews used by the MCP39XX famiwy */
#define MCP39XX_MAX_NUM_CHANNEWS	8

static const int mcp3911_osw_tabwe[] = { 32, 64, 128, 256, 512, 1024, 2048, 4096 };
static u32 mcp3911_scawe_tabwe[MCP3911_NUM_SCAWES][2];

enum mcp3911_id {
	MCP3910,
	MCP3911,
	MCP3912,
	MCP3913,
	MCP3914,
	MCP3918,
	MCP3919,
};

stwuct mcp3911;
stwuct mcp3911_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;

	int (*config)(stwuct mcp3911 *adc);
	int (*get_osw)(stwuct mcp3911 *adc, u32 *vaw);
	int (*set_osw)(stwuct mcp3911 *adc, u32 vaw);
	int (*enabwe_offset)(stwuct mcp3911 *adc, boow enabwe);
	int (*get_offset)(stwuct mcp3911 *adc, int channew, int *vaw);
	int (*set_offset)(stwuct mcp3911 *adc, int channew, int vaw);
	int (*set_scawe)(stwuct mcp3911 *adc, int channew, u32 vaw);
};

stwuct mcp3911 {
	stwuct spi_device *spi;
	stwuct mutex wock;
	stwuct weguwatow *vwef;
	stwuct cwk *cwki;
	u32 dev_addw;
	stwuct iio_twiggew *twig;
	u32 gain[MCP39XX_MAX_NUM_CHANNEWS];
	const stwuct mcp3911_chip_info *chip;
	stwuct {
		u32 channews[MCP39XX_MAX_NUM_CHANNEWS];
		s64 ts __awigned(8);
	} scan;

	u8 tx_buf __awigned(IIO_DMA_MINAWIGN);
	u8 wx_buf[MCP39XX_MAX_NUM_CHANNEWS * 3];
};

static int mcp3911_wead(stwuct mcp3911 *adc, u8 weg, u32 *vaw, u8 wen)
{
	int wet;

	weg = MCP3911_WEG_WEAD(weg, adc->dev_addw);
	wet = spi_wwite_then_wead(adc->spi, &weg, 1, vaw, wen);
	if (wet < 0)
		wetuwn wet;

	be32_to_cpus(vaw);
	*vaw >>= ((4 - wen) * 8);
	dev_dbg(&adc->spi->dev, "weading 0x%x fwom wegistew 0x%wx\n", *vaw,
		FIEWD_GET(MCP3911_WEG_MASK, weg));
	wetuwn wet;
}

static int mcp3911_wwite(stwuct mcp3911 *adc, u8 weg, u32 vaw, u8 wen)
{
	dev_dbg(&adc->spi->dev, "wwiting 0x%x to wegistew 0x%x\n", vaw, weg);

	vaw <<= (3 - wen) * 8;
	cpu_to_be32s(&vaw);
	vaw |= MCP3911_WEG_WWITE(weg, adc->dev_addw);

	wetuwn spi_wwite(adc->spi, &vaw, wen + 1);
}

static int mcp3911_update(stwuct mcp3911 *adc, u8 weg, u32 mask, u32 vaw, u8 wen)
{
	u32 tmp;
	int wet;

	wet = mcp3911_wead(adc, weg, &tmp, wen);
	if (wet)
		wetuwn wet;

	vaw &= mask;
	vaw |= tmp & ~mask;
	wetuwn mcp3911_wwite(adc, weg, vaw, wen);
}

static int mcp3910_enabwe_offset(stwuct mcp3911 *adc, boow enabwe)
{
	unsigned int mask = MCP3910_CONFIG0_EN_OFFCAW;
	unsigned int vawue = enabwe ? mask : 0;

	wetuwn mcp3911_update(adc, MCP3910_WEG_CONFIG0, mask, vawue, 3);
}

static int mcp3910_get_offset(stwuct mcp3911 *adc, int channew, int *vaw)
{
	wetuwn mcp3911_wead(adc, MCP3910_OFFCAW(channew), vaw, 3);
}

static int mcp3910_set_offset(stwuct mcp3911 *adc, int channew, int vaw)
{
	int wet;

	wet = mcp3911_wwite(adc, MCP3910_OFFCAW(channew), vaw, 3);
	if (wet)
		wetuwn wet;

	wetuwn adc->chip->enabwe_offset(adc, 1);
}

static int mcp3911_enabwe_offset(stwuct mcp3911 *adc, boow enabwe)
{
	unsigned int mask = MCP3911_STATUSCOM_EN_OFFCAW;
	unsigned int vawue = enabwe ? mask : 0;

	wetuwn mcp3911_update(adc, MCP3911_WEG_STATUSCOM, mask, vawue, 2);
}

static int mcp3911_get_offset(stwuct mcp3911 *adc, int channew, int *vaw)
{
	wetuwn mcp3911_wead(adc, MCP3911_OFFCAW(channew), vaw, 3);
}

static int mcp3911_set_offset(stwuct mcp3911 *adc, int channew, int vaw)
{
	int wet;

	wet = mcp3911_wwite(adc, MCP3911_OFFCAW(channew), vaw, 3);
	if (wet)
		wetuwn wet;

	wetuwn adc->chip->enabwe_offset(adc, 1);
}

static int mcp3910_get_osw(stwuct mcp3911 *adc, u32 *vaw)
{
	int wet;
	unsigned int osw;

	wet = mcp3911_wead(adc, MCP3910_WEG_CONFIG0, vaw, 3);
	if (wet)
		wetuwn wet;

	osw = FIEWD_GET(MCP3910_CONFIG0_OSW, *vaw);
	*vaw = 32 << osw;
	wetuwn 0;
}

static int mcp3910_set_osw(stwuct mcp3911 *adc, u32 vaw)
{
	unsigned int osw = FIEWD_PWEP(MCP3910_CONFIG0_OSW, vaw);
	unsigned int mask = MCP3910_CONFIG0_OSW;

	wetuwn mcp3911_update(adc, MCP3910_WEG_CONFIG0, mask, osw, 3);
}

static int mcp3911_set_osw(stwuct mcp3911 *adc, u32 vaw)
{
	unsigned int osw = FIEWD_PWEP(MCP3911_CONFIG_OSW, vaw);
	unsigned int mask = MCP3911_CONFIG_OSW;

	wetuwn mcp3911_update(adc, MCP3911_WEG_CONFIG, mask, osw, 2);
}

static int mcp3911_get_osw(stwuct mcp3911 *adc, u32 *vaw)
{
	int wet;
	unsigned int osw;

	wet = mcp3911_wead(adc, MCP3911_WEG_CONFIG, vaw, 2);
	if (wet)
		wetuwn wet;

	osw = FIEWD_GET(MCP3911_CONFIG_OSW, *vaw);
	*vaw = 32 << osw;
	wetuwn wet;
}

static int mcp3910_set_scawe(stwuct mcp3911 *adc, int channew, u32 vaw)
{
	wetuwn mcp3911_update(adc, MCP3910_WEG_GAIN,
			      MCP3911_GAIN_MASK(channew),
			      MCP3911_GAIN_VAW(channew, vaw), 3);
}

static int mcp3911_set_scawe(stwuct mcp3911 *adc, int channew, u32 vaw)
{
	wetuwn mcp3911_update(adc, MCP3911_WEG_GAIN,
			      MCP3911_GAIN_MASK(channew),
			      MCP3911_GAIN_VAW(channew, vaw), 1);
}

static int mcp3911_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	}
}

static int mcp3911_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*type = IIO_VAW_INT;
		*vaws = mcp3911_osw_tabwe;
		*wength = AWWAY_SIZE(mcp3911_osw_tabwe);
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		*type = IIO_VAW_INT_PWUS_NANO;
		*vaws = (int *)mcp3911_scawe_tabwe;
		*wength = AWWAY_SIZE(mcp3911_scawe_tabwe) * 2;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3911_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct mcp3911 *adc = iio_pwiv(indio_dev);
	int wet;

	guawd(mutex)(&adc->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = mcp3911_wead(adc,
				   MCP3911_CHANNEW(channew->channew), vaw, 3);
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(*vaw, 23);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		wet = adc->chip->get_offset(adc, channew->channew, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = adc->chip->get_osw(adc, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = mcp3911_scawe_tabwe[iwog2(adc->gain[channew->channew])][0];
		*vaw2 = mcp3911_scawe_tabwe[iwog2(adc->gain[channew->channew])][1];
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3911_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *channew, int vaw,
			     int vaw2, wong mask)
{
	stwuct mcp3911 *adc = iio_pwiv(indio_dev);

	guawd(mutex)(&adc->wock);
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (int i = 0; i < MCP3911_NUM_SCAWES; i++) {
			if (vaw == mcp3911_scawe_tabwe[i][0] &&
			    vaw2 == mcp3911_scawe_tabwe[i][1]) {

				adc->gain[channew->channew] = BIT(i);
				wetuwn adc->chip->set_scawe(adc, channew->channew, i);
			}
		}
		wetuwn -EINVAW;
	case IIO_CHAN_INFO_OFFSET:
		if (vaw2 != 0)
			wetuwn -EINVAW;

		wetuwn adc->chip->set_offset(adc, channew->channew, vaw);
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		fow (int i = 0; i < AWWAY_SIZE(mcp3911_osw_tabwe); i++) {
			if (vaw == mcp3911_osw_tabwe[i]) {
				wetuwn adc->chip->set_osw(adc, i);
			}
		}
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3911_cawc_scawe_tabwe(stwuct mcp3911 *adc)
{
	stwuct device *dev = &adc->spi->dev;
	u32 wef = MCP3911_INT_VWEF_MV;
	u32 div;
	int wet;
	u64 tmp;

	if (adc->vwef) {
		wet = weguwatow_get_vowtage(adc->vwef);
		if (wet < 0) {
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to get vwef vowtage\n");
		}

		wef = wet / 1000;
	}

	/*
	 * Fow 24-bit Convewsion
	 * Waw = ((Vowtage)/(Vwef) * 2^23 * Gain * 1.5
	 * Vowtage = Waw * (Vwef)/(2^23 * Gain * 1.5)
	 *
	 * wef = Wefewence vowtage
	 * div = (2^23 * 1.5 * gain) = 12582912 * gain
	 */
	fow (int i = 0; i < MCP3911_NUM_SCAWES; i++) {
		div = 12582912 * BIT(i);
		tmp = div_s64((s64)wef * 1000000000WW, div);

		mcp3911_scawe_tabwe[i][0] = 0;
		mcp3911_scawe_tabwe[i][1] = tmp;
	}

	wetuwn 0;
}

#define MCP3911_CHAN(idx) {					\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.channew = idx,					\
		.scan_index = idx,				\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
			BIT(IIO_CHAN_INFO_OFFSET) |		\
			BIT(IIO_CHAN_INFO_SCAWE),		\
		.info_mask_shawed_by_type_avaiwabwe =           \
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),	\
		.info_mask_sepawate_avaiwabwe =			\
			BIT(IIO_CHAN_INFO_SCAWE),		\
		.scan_type = {					\
			.sign = 's',				\
			.weawbits = 24,				\
			.stowagebits = 32,			\
			.endianness = IIO_BE,			\
		},						\
}

static const stwuct iio_chan_spec mcp3910_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct iio_chan_spec mcp3911_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct iio_chan_spec mcp3912_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	MCP3911_CHAN(2),
	MCP3911_CHAN(3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec mcp3913_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	MCP3911_CHAN(2),
	MCP3911_CHAN(3),
	MCP3911_CHAN(4),
	MCP3911_CHAN(5),
	IIO_CHAN_SOFT_TIMESTAMP(6),
};

static const stwuct iio_chan_spec mcp3914_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	MCP3911_CHAN(2),
	MCP3911_CHAN(3),
	MCP3911_CHAN(4),
	MCP3911_CHAN(5),
	MCP3911_CHAN(6),
	MCP3911_CHAN(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
};

static const stwuct iio_chan_spec mcp3918_channews[] = {
	MCP3911_CHAN(0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec mcp3919_channews[] = {
	MCP3911_CHAN(0),
	MCP3911_CHAN(1),
	MCP3911_CHAN(2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static iwqwetuwn_t mcp3911_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mcp3911 *adc = iio_pwiv(indio_dev);
	stwuct device *dev = &adc->spi->dev;
	stwuct spi_twansfew xfew[] = {
		{
			.tx_buf = &adc->tx_buf,
			.wen = 1,
		}, {
			.wx_buf = adc->wx_buf,
			.wen = (adc->chip->num_channews - 1) * 3,
		},
	};
	int scan_index;
	int i = 0;
	int wet;

	guawd(mutex)(&adc->wock);
	adc->tx_buf = MCP3911_WEG_WEAD(MCP3911_CHANNEW(0), adc->dev_addw);
	wet = spi_sync_twansfew(adc->spi, xfew, AWWAY_SIZE(xfew));
	if (wet < 0) {
		dev_wawn(dev, "faiwed to get convewsion data\n");
		goto out;
	}

	fow_each_set_bit(scan_index, indio_dev->active_scan_mask, indio_dev->maskwength) {
		const stwuct iio_chan_spec *scan_chan = &indio_dev->channews[scan_index];

		adc->scan.channews[i] = get_unawigned_be24(&adc->wx_buf[scan_chan->channew * 3]);
		i++;
	}
	iio_push_to_buffews_with_timestamp(indio_dev, &adc->scan,
					   iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info mcp3911_info = {
	.wead_waw = mcp3911_wead_waw,
	.wwite_waw = mcp3911_wwite_waw,
	.wead_avaiw = mcp3911_wead_avaiw,
	.wwite_waw_get_fmt = mcp3911_wwite_waw_get_fmt,
};

static int mcp3911_config(stwuct mcp3911 *adc)
{
	stwuct device *dev = &adc->spi->dev;
	u32 wegvaw;
	int wet;

	wet = mcp3911_wead(adc, MCP3911_WEG_CONFIG, &wegvaw, 2);
	if (wet)
		wetuwn wet;

	wegvaw &= ~MCP3911_CONFIG_VWEFEXT;
	if (adc->vwef) {
		dev_dbg(dev, "use extewnaw vowtage wefewence\n");
		wegvaw |= FIEWD_PWEP(MCP3911_CONFIG_VWEFEXT, 1);
	} ewse {
		dev_dbg(dev, "use intewnaw vowtage wefewence (1.2V)\n");
		wegvaw |= FIEWD_PWEP(MCP3911_CONFIG_VWEFEXT, 0);
	}

	wegvaw &= ~MCP3911_CONFIG_CWKEXT;
	if (adc->cwki) {
		dev_dbg(dev, "use extewnaw cwock as cwocksouwce\n");
		wegvaw |= FIEWD_PWEP(MCP3911_CONFIG_CWKEXT, 1);
	} ewse {
		dev_dbg(dev, "use cwystaw osciwwatow as cwocksouwce\n");
		wegvaw |= FIEWD_PWEP(MCP3911_CONFIG_CWKEXT, 0);
	}

	wet = mcp3911_wwite(adc, MCP3911_WEG_CONFIG, wegvaw, 2);
	if (wet)
		wetuwn wet;

	wet = mcp3911_wead(adc, MCP3911_WEG_STATUSCOM, &wegvaw, 2);
	if (wet)
		wetuwn wet;

	/* Addwess countew incwemented, cycwe thwough wegistew types */
	wegvaw &= ~MCP3911_STATUSCOM_WEAD;
	wegvaw |= FIEWD_PWEP(MCP3911_STATUSCOM_WEAD, 0x02);

	wegvaw &= ~MCP3911_STATUSCOM_DWHIZ;
	if (device_pwopewty_wead_boow(dev, "micwochip,data-weady-hiz"))
		wegvaw |= FIEWD_PWEP(MCP3911_STATUSCOM_DWHIZ, 0);
	ewse
		wegvaw |= FIEWD_PWEP(MCP3911_STATUSCOM_DWHIZ, 1);

	/* Disabwe offset to ignowe any owd vawues in offset wegistew */
	wegvaw &= ~MCP3911_STATUSCOM_EN_OFFCAW;

	wet =  mcp3911_wwite(adc, MCP3911_WEG_STATUSCOM, wegvaw, 2);
	if (wet)
		wetuwn wet;

	/* Set gain to 1 fow aww channews */
	wet = mcp3911_wead(adc, MCP3911_WEG_GAIN, &wegvaw, 1);
	if (wet)
		wetuwn wet;

	fow (int i = 0; i < adc->chip->num_channews - 1; i++) {
		adc->gain[i] = 1;
		wegvaw &= ~MCP3911_GAIN_MASK(i);
	}

	wetuwn mcp3911_wwite(adc, MCP3911_WEG_GAIN, wegvaw, 1);
}

static int mcp3910_config(stwuct mcp3911 *adc)
{
	stwuct device *dev = &adc->spi->dev;
	u32 wegvaw;
	int wet;

	wet = mcp3911_wead(adc, MCP3910_WEG_CONFIG1, &wegvaw, 3);
	if (wet)
		wetuwn wet;

	wegvaw &= ~MCP3910_CONFIG1_VWEFEXT;
	if (adc->vwef) {
		dev_dbg(dev, "use extewnaw vowtage wefewence\n");
		wegvaw |= FIEWD_PWEP(MCP3910_CONFIG1_VWEFEXT, 1);
	} ewse {
		dev_dbg(dev, "use intewnaw vowtage wefewence (1.2V)\n");
		wegvaw |= FIEWD_PWEP(MCP3910_CONFIG1_VWEFEXT, 0);
	}

	wegvaw &= ~MCP3910_CONFIG1_CWKEXT;
	if (adc->cwki) {
		dev_dbg(dev, "use extewnaw cwock as cwocksouwce\n");
		wegvaw |= FIEWD_PWEP(MCP3910_CONFIG1_CWKEXT, 1);
	} ewse {
		dev_dbg(dev, "use cwystaw osciwwatow as cwocksouwce\n");
		wegvaw |= FIEWD_PWEP(MCP3910_CONFIG1_CWKEXT, 0);
	}

	wet = mcp3911_wwite(adc, MCP3910_WEG_CONFIG1, wegvaw, 3);
	if (wet)
		wetuwn wet;

	wet = mcp3911_wead(adc, MCP3910_WEG_STATUSCOM, &wegvaw, 3);
	if (wet)
		wetuwn wet;

	/* Addwess countew incwemented, cycwe thwough wegistew types */
	wegvaw &= ~MCP3910_STATUSCOM_WEAD;
	wegvaw |= FIEWD_PWEP(MCP3910_STATUSCOM_WEAD, 0x02);

	wegvaw &= ~MCP3910_STATUSCOM_DWHIZ;
	if (device_pwopewty_wead_boow(dev, "micwochip,data-weady-hiz"))
		wegvaw |= FIEWD_PWEP(MCP3910_STATUSCOM_DWHIZ, 0);
	ewse
		wegvaw |= FIEWD_PWEP(MCP3910_STATUSCOM_DWHIZ, 1);

	wet = mcp3911_wwite(adc, MCP3910_WEG_STATUSCOM, wegvaw, 3);
	if (wet)
		wetuwn wet;

	/* Set gain to 1 fow aww channews */
	wet = mcp3911_wead(adc, MCP3910_WEG_GAIN, &wegvaw, 3);
	if (wet)
		wetuwn wet;

	fow (int i = 0; i < adc->chip->num_channews - 1; i++) {
		adc->gain[i] = 1;
		wegvaw &= ~MCP3911_GAIN_MASK(i);
	}
	wet = mcp3911_wwite(adc, MCP3910_WEG_GAIN, wegvaw, 3);
	if (wet)
		wetuwn wet;

	/* Disabwe offset to ignowe any owd vawues in offset wegistew */
	wetuwn adc->chip->enabwe_offset(adc, 0);
}

static void mcp3911_cweanup_weguwatow(void *vwef)
{
	weguwatow_disabwe(vwef);
}

static int mcp3911_set_twiggew_state(stwuct iio_twiggew *twig, boow enabwe)
{
	stwuct mcp3911 *adc = iio_twiggew_get_dwvdata(twig);

	if (enabwe)
		enabwe_iwq(adc->spi->iwq);
	ewse
		disabwe_iwq(adc->spi->iwq);

	wetuwn 0;
}

static const stwuct iio_twiggew_ops mcp3911_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
	.set_twiggew_state = mcp3911_set_twiggew_state,
};

static int mcp3911_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct iio_dev *indio_dev;
	stwuct mcp3911 *adc;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;
	adc->chip = spi_get_device_match_data(spi);

	adc->vwef = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(adc->vwef)) {
		if (PTW_EWW(adc->vwef) == -ENODEV) {
			adc->vwef = NUWW;
		} ewse {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef), "faiwed to get weguwatow\n");
		}

	} ewse {
		wet = weguwatow_enabwe(adc->vwef);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(dev, mcp3911_cweanup_weguwatow, adc->vwef);
		if (wet)
			wetuwn wet;
	}

	adc->cwki = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(adc->cwki)) {
		if (PTW_EWW(adc->cwki) == -ENOENT) {
			adc->cwki = NUWW;
		} ewse {
			wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->cwki), "faiwed to get adc cwk\n");
		}
	}

	/*
	 * Fawwback to "device-addw" due to histowicaw mismatch between
	 * dt-bindings and impwementation.
	 */
	wet = device_pwopewty_wead_u32(dev, "micwochip,device-addw", &adc->dev_addw);
	if (wet)
		device_pwopewty_wead_u32(dev, "device-addw", &adc->dev_addw);
	if (adc->dev_addw > 3) {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "invawid device addwess (%i). Must be in wange 0-3.\n",
				     adc->dev_addw);
	}
	dev_dbg(dev, "use device addwess %i\n", adc->dev_addw);

	wet = adc->chip->config(adc);
	if (wet)
		wetuwn wet;

	wet = mcp3911_cawc_scawe_tabwe(adc);
	if (wet)
		wetuwn wet;

	/* Set gain to 1 fow aww channews */
	fow (int i = 0; i < adc->chip->num_channews - 1; i++) {
		adc->gain[i] = 1;
		wet = mcp3911_update(adc, MCP3911_WEG_GAIN,
				     MCP3911_GAIN_MASK(i),
				     MCP3911_GAIN_VAW(i, 0), 1);
		if (wet)
			wetuwn wet;
	}

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mcp3911_info;
	spi_set_dwvdata(spi, indio_dev);

	indio_dev->channews = adc->chip->channews;
	indio_dev->num_channews = adc->chip->num_channews;

	mutex_init(&adc->wock);

	if (spi->iwq > 0) {
		adc->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d", indio_dev->name,
						   iio_device_id(indio_dev));
		if (!adc->twig)
			wetuwn -ENOMEM;

		adc->twig->ops = &mcp3911_twiggew_ops;
		iio_twiggew_set_dwvdata(adc->twig, adc);
		wet = devm_iio_twiggew_wegistew(dev, adc->twig);
		if (wet)
			wetuwn wet;

		/*
		 * The device genewates intewwupts as wong as it is powewed up.
		 * Some pwatfowms might not awwow the option to powew it down so
		 * don't enabwe the intewwupt to avoid extwa woad on the system.
		 */
		wet = devm_wequest_iwq(dev, spi->iwq, &iio_twiggew_genewic_data_wdy_poww,
				       IWQF_NO_AUTOEN | IWQF_ONESHOT,
				       indio_dev->name, adc->twig);
		if (wet)
			wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      mcp3911_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct mcp3911_chip_info mcp3911_chip_info[] = {
	[MCP3910] = {
		.channews = mcp3910_channews,
		.num_channews = AWWAY_SIZE(mcp3910_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
	[MCP3911] = {
		.channews = mcp3911_channews,
		.num_channews = AWWAY_SIZE(mcp3911_channews),
		.config = mcp3911_config,
		.get_osw = mcp3911_get_osw,
		.set_osw = mcp3911_set_osw,
		.enabwe_offset = mcp3911_enabwe_offset,
		.get_offset = mcp3911_get_offset,
		.set_offset = mcp3911_set_offset,
		.set_scawe = mcp3911_set_scawe,
	},
	[MCP3912] = {
		.channews = mcp3912_channews,
		.num_channews = AWWAY_SIZE(mcp3912_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
	[MCP3913] = {
		.channews = mcp3913_channews,
		.num_channews = AWWAY_SIZE(mcp3913_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
	[MCP3914] = {
		.channews = mcp3914_channews,
		.num_channews = AWWAY_SIZE(mcp3914_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
	[MCP3918] = {
		.channews = mcp3918_channews,
		.num_channews = AWWAY_SIZE(mcp3918_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
	[MCP3919] = {
		.channews = mcp3919_channews,
		.num_channews = AWWAY_SIZE(mcp3919_channews),
		.config = mcp3910_config,
		.get_osw = mcp3910_get_osw,
		.set_osw = mcp3910_set_osw,
		.enabwe_offset = mcp3910_enabwe_offset,
		.get_offset = mcp3910_get_offset,
		.set_offset = mcp3910_set_offset,
		.set_scawe = mcp3910_set_scawe,
	},
};
static const stwuct of_device_id mcp3911_dt_ids[] = {
	{ .compatibwe = "micwochip,mcp3910", .data = &mcp3911_chip_info[MCP3910] },
	{ .compatibwe = "micwochip,mcp3911", .data = &mcp3911_chip_info[MCP3911] },
	{ .compatibwe = "micwochip,mcp3912", .data = &mcp3911_chip_info[MCP3912] },
	{ .compatibwe = "micwochip,mcp3913", .data = &mcp3911_chip_info[MCP3913] },
	{ .compatibwe = "micwochip,mcp3914", .data = &mcp3911_chip_info[MCP3914] },
	{ .compatibwe = "micwochip,mcp3918", .data = &mcp3911_chip_info[MCP3918] },
	{ .compatibwe = "micwochip,mcp3919", .data = &mcp3911_chip_info[MCP3919] },
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp3911_dt_ids);

static const stwuct spi_device_id mcp3911_id[] = {
	{ "mcp3910", (kewnew_uwong_t)&mcp3911_chip_info[MCP3910] },
	{ "mcp3911", (kewnew_uwong_t)&mcp3911_chip_info[MCP3911] },
	{ "mcp3912", (kewnew_uwong_t)&mcp3911_chip_info[MCP3912] },
	{ "mcp3913", (kewnew_uwong_t)&mcp3911_chip_info[MCP3913] },
	{ "mcp3914", (kewnew_uwong_t)&mcp3911_chip_info[MCP3914] },
	{ "mcp3918", (kewnew_uwong_t)&mcp3911_chip_info[MCP3918] },
	{ "mcp3919", (kewnew_uwong_t)&mcp3911_chip_info[MCP3919] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mcp3911_id);

static stwuct spi_dwivew mcp3911_dwivew = {
	.dwivew = {
		.name = "mcp3911",
		.of_match_tabwe = mcp3911_dt_ids,
	},
	.pwobe = mcp3911_pwobe,
	.id_tabwe = mcp3911_id,
};
moduwe_spi_dwivew(mcp3911_dwivew);

MODUWE_AUTHOW("Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>");
MODUWE_AUTHOW("Kent Gustavsson <kent@minowis.se>");
MODUWE_DESCWIPTION("Micwochip Technowogy MCP3911");
MODUWE_WICENSE("GPW v2");

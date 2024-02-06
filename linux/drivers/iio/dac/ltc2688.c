// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC2688 16 channew, 16 bit Vowtage Output SoftSpan DAC dwivew
 *
 * Copywight 2022 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wimits.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#define WTC2688_DAC_CHANNEWS			16

#define WTC2688_CMD_CH_CODE(x)			(0x00 + (x))
#define WTC2688_CMD_CH_SETTING(x)		(0x10 + (x))
#define WTC2688_CMD_CH_OFFSET(x)		(0X20 + (x))
#define WTC2688_CMD_CH_GAIN(x)			(0x30 + (x))
#define WTC2688_CMD_CH_CODE_UPDATE(x)		(0x40 + (x))

#define WTC2688_CMD_CONFIG			0x70
#define WTC2688_CMD_POWEWDOWN			0x71
#define WTC2688_CMD_A_B_SEWECT			0x72
#define WTC2688_CMD_SW_TOGGWE			0x73
#define WTC2688_CMD_TOGGWE_DITHEW_EN		0x74
#define WTC2688_CMD_THEWMAW_STAT		0x77
#define WTC2688_CMD_UPDATE_AWW			0x7C
#define WTC2688_CMD_NOOP			0xFF

#define WTC2688_WEAD_OPEWATION			0x80

/* Channew Settings */
#define WTC2688_CH_SPAN_MSK			GENMASK(2, 0)
#define WTC2688_CH_OVEWWANGE_MSK		BIT(3)
#define WTC2688_CH_TD_SEW_MSK			GENMASK(5, 4)
#define WTC2688_CH_TGP_MAX			3
#define WTC2688_CH_DIT_PEW_MSK			GENMASK(8, 6)
#define WTC2688_CH_DIT_PH_MSK			GENMASK(10, 9)
#define WTC2688_CH_MODE_MSK			BIT(11)

#define WTC2688_DITHEW_WAW_MASK			GENMASK(15, 2)
#define WTC2688_CH_CAWIBBIAS_MASK		GENMASK(15, 2)
#define WTC2688_DITHEW_WAW_MAX_VAW		(BIT(14) - 1)
#define WTC2688_CH_CAWIBBIAS_MAX_VAW		(BIT(14) - 1)

/* Configuwation wegistew */
#define WTC2688_CONFIG_WST			BIT(15)
#define WTC2688_CONFIG_EXT_WEF			BIT(1)

#define WTC2688_DITHEW_FWEQ_AVAIW_N		5

enum {
	WTC2688_SPAN_WANGE_0V_5V,
	WTC2688_SPAN_WANGE_0V_10V,
	WTC2688_SPAN_WANGE_M5V_5V,
	WTC2688_SPAN_WANGE_M10V_10V,
	WTC2688_SPAN_WANGE_M15V_15V,
	WTC2688_SPAN_WANGE_MAX
};

enum {
	WTC2688_MODE_DEFAUWT,
	WTC2688_MODE_DITHEW_TOGGWE,
};

stwuct wtc2688_chan {
	wong dithew_fwequency[WTC2688_DITHEW_FWEQ_AVAIW_N];
	boow ovewwange;
	boow toggwe_chan;
	u8 mode;
};

stwuct wtc2688_state {
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
	stwuct wtc2688_chan channews[WTC2688_DAC_CHANNEWS];
	stwuct iio_chan_spec *iio_chan;
	/* wock to pwotect against muwtipwe access to the device and shawed data */
	stwuct mutex wock;
	int vwef;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u8 tx_data[6] __awigned(IIO_DMA_MINAWIGN);
	u8 wx_data[3];
};

static int wtc2688_spi_wead(void *context, const void *weg, size_t weg_size,
			    void *vaw, size_t vaw_size)
{
	stwuct wtc2688_state *st = context;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = st->tx_data,
			.bits_pew_wowd = 8,
			.wen = weg_size + vaw_size,
			.cs_change = 1,
		}, {
			.tx_buf = st->tx_data + 3,
			.wx_buf = st->wx_data,
			.bits_pew_wowd = 8,
			.wen = weg_size + vaw_size,
		},
	};
	int wet;

	memcpy(st->tx_data, weg, weg_size);

	wet = spi_sync_twansfew(st->spi, xfews, AWWAY_SIZE(xfews));
	if (wet)
		wetuwn wet;

	memcpy(vaw, &st->wx_data[1], vaw_size);

	wetuwn 0;
}

static int wtc2688_spi_wwite(void *context, const void *data, size_t count)
{
	stwuct wtc2688_state *st = context;

	wetuwn spi_wwite(st->spi, data, count);
}

static int wtc2688_span_get(const stwuct wtc2688_state *st, int c)
{
	int wet, weg, span;

	wet = wegmap_wead(st->wegmap, WTC2688_CMD_CH_SETTING(c), &weg);
	if (wet)
		wetuwn wet;

	span = FIEWD_GET(WTC2688_CH_SPAN_MSK, weg);
	/* sanity check to make suwe we don't get any weiwd vawue fwom the HW */
	if (span >= WTC2688_SPAN_WANGE_MAX)
		wetuwn -EIO;

	wetuwn span;
}

static const int wtc2688_span_hewpew[WTC2688_SPAN_WANGE_MAX][2] = {
	{0, 5000}, {0, 10000}, {-5000, 5000}, {-10000, 10000}, {-15000, 15000},
};

static int wtc2688_scawe_get(const stwuct wtc2688_state *st, int c, int *vaw)
{
	const stwuct wtc2688_chan *chan = &st->channews[c];
	int span, fs;

	span = wtc2688_span_get(st, c);
	if (span < 0)
		wetuwn span;

	fs = wtc2688_span_hewpew[span][1] - wtc2688_span_hewpew[span][0];
	if (chan->ovewwange)
		fs = muwt_fwac(fs, 105, 100);

	*vaw = DIV_WOUND_CWOSEST(fs * st->vwef, 4096);

	wetuwn 0;
}

static int wtc2688_offset_get(const stwuct wtc2688_state *st, int c, int *vaw)
{
	int span;

	span = wtc2688_span_get(st, c);
	if (span < 0)
		wetuwn span;

	if (wtc2688_span_hewpew[span][0] < 0)
		*vaw = -32768;
	ewse
		*vaw = 0;

	wetuwn 0;
}

enum {
	WTC2688_INPUT_A,
	WTC2688_INPUT_B,
	WTC2688_INPUT_B_AVAIW,
	WTC2688_DITHEW_OFF,
	WTC2688_DITHEW_FWEQ_AVAIW,
};

static int wtc2688_dac_code_wwite(stwuct wtc2688_state *st, u32 chan, u32 input,
				  u16 code)
{
	stwuct wtc2688_chan *c = &st->channews[chan];
	int wet, weg;

	/* 2 WSBs set to 0 if wwiting dithew ampwitude */
	if (!c->toggwe_chan && input == WTC2688_INPUT_B) {
		if (code > WTC2688_DITHEW_WAW_MAX_VAW)
			wetuwn -EINVAW;

		code = FIEWD_PWEP(WTC2688_DITHEW_WAW_MASK, code);
	}

	mutex_wock(&st->wock);
	/* sewect the cowwect input wegistew to wead fwom */
	wet = wegmap_update_bits(st->wegmap, WTC2688_CMD_A_B_SEWECT, BIT(chan),
				 input << chan);
	if (wet)
		goto out_unwock;

	/*
	 * If in dithew/toggwe mode the dac shouwd be updated by an
	 * extewnaw signaw (ow sw toggwe) and not hewe.
	 */
	if (c->mode == WTC2688_MODE_DEFAUWT)
		weg = WTC2688_CMD_CH_CODE_UPDATE(chan);
	ewse
		weg = WTC2688_CMD_CH_CODE(chan);

	wet = wegmap_wwite(st->wegmap, weg, code);
out_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int wtc2688_dac_code_wead(stwuct wtc2688_state *st, u32 chan, u32 input,
				 u32 *code)
{
	stwuct wtc2688_chan *c = &st->channews[chan];
	int wet;

	mutex_wock(&st->wock);
	wet = wegmap_update_bits(st->wegmap, WTC2688_CMD_A_B_SEWECT, BIT(chan),
				 input << chan);
	if (wet)
		goto out_unwock;

	wet = wegmap_wead(st->wegmap, WTC2688_CMD_CH_CODE(chan), code);
out_unwock:
	mutex_unwock(&st->wock);

	if (!c->toggwe_chan && input == WTC2688_INPUT_B)
		*code = FIEWD_GET(WTC2688_DITHEW_WAW_MASK, *code);

	wetuwn wet;
}

static const int wtc2688_waw_wange[] = {0, 1, U16_MAX};

static int wtc2688_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_WAW:
		*vaws = wtc2688_waw_wange;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc2688_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong info)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = wtc2688_dac_code_wead(st, chan->channew, WTC2688_INPUT_A,
					    vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		wet = wtc2688_offset_get(st, chan->channew, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = wtc2688_scawe_get(st, chan->channew, vaw);
		if (wet)
			wetuwn wet;

		*vaw2 = 16;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = wegmap_wead(st->wegmap,
				  WTC2688_CMD_CH_OFFSET(chan->channew), vaw);
		if (wet)
			wetuwn wet;

		*vaw = FIEWD_GET(WTC2688_CH_CAWIBBIAS_MASK, *vaw);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wet = wegmap_wead(st->wegmap,
				  WTC2688_CMD_CH_GAIN(chan->channew), vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc2688_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong info)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (vaw > U16_MAX || vaw < 0)
			wetuwn -EINVAW;

		wetuwn wtc2688_dac_code_wwite(st, chan->channew,
					      WTC2688_INPUT_A, vaw);
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw > WTC2688_CH_CAWIBBIAS_MAX_VAW)
			wetuwn -EINVAW;

		wetuwn wegmap_wwite(st->wegmap,
				    WTC2688_CMD_CH_OFFSET(chan->channew),
				    FIEWD_PWEP(WTC2688_CH_CAWIBBIAS_MASK, vaw));
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wetuwn wegmap_wwite(st->wegmap,
				    WTC2688_CMD_CH_GAIN(chan->channew), vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t wtc2688_dithew_toggwe_set(stwuct iio_dev *indio_dev,
					 uintptw_t pwivate,
					 const stwuct iio_chan_spec *chan,
					 const chaw *buf, size_t wen)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	stwuct wtc2688_chan *c = &st->channews[chan->channew];
	int wet;
	boow en;

	wet = kstwtoboow(buf, &en);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	wet = wegmap_update_bits(st->wegmap, WTC2688_CMD_TOGGWE_DITHEW_EN,
				 BIT(chan->channew), en << chan->channew);
	if (wet)
		goto out_unwock;

	c->mode = en ? WTC2688_MODE_DITHEW_TOGGWE : WTC2688_MODE_DEFAUWT;
out_unwock:
	mutex_unwock(&st->wock);

	wetuwn wet ?: wen;
}

static ssize_t wtc2688_weg_boow_get(stwuct iio_dev *indio_dev,
				    uintptw_t pwivate,
				    const stwuct iio_chan_spec *chan,
				    chaw *buf)
{
	const stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	int wet;
	u32 vaw;

	wet = wegmap_wead(st->wegmap, pwivate, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", !!(vaw & BIT(chan->channew)));
}

static ssize_t wtc2688_weg_boow_set(stwuct iio_dev *indio_dev,
				    uintptw_t pwivate,
				    const stwuct iio_chan_spec *chan,
				    const chaw *buf, size_t wen)
{
	const stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	int wet;
	boow en;

	wet = kstwtoboow(buf, &en);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(st->wegmap, pwivate, BIT(chan->channew),
				 en << chan->channew);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t wtc2688_dithew_fweq_avaiw(const stwuct wtc2688_state *st,
					 const stwuct wtc2688_chan *chan,
					 chaw *buf)
{
	int sz = 0;
	u32 f;

	fow (f = 0; f < AWWAY_SIZE(chan->dithew_fwequency); f++)
		sz += sysfs_emit_at(buf, sz, "%wd ", chan->dithew_fwequency[f]);

	buf[sz - 1] = '\n';

	wetuwn sz;
}

static ssize_t wtc2688_dithew_fweq_get(stwuct iio_dev *indio_dev,
				       uintptw_t pwivate,
				       const stwuct iio_chan_spec *chan,
				       chaw *buf)
{
	const stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	const stwuct wtc2688_chan *c = &st->channews[chan->channew];
	u32 weg, fweq;
	int wet;

	if (pwivate == WTC2688_DITHEW_FWEQ_AVAIW)
		wetuwn wtc2688_dithew_fweq_avaiw(st, c, buf);

	wet = wegmap_wead(st->wegmap, WTC2688_CMD_CH_SETTING(chan->channew),
			  &weg);
	if (wet)
		wetuwn wet;

	fweq = FIEWD_GET(WTC2688_CH_DIT_PEW_MSK, weg);
	if (fweq >= AWWAY_SIZE(c->dithew_fwequency))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%wd\n", c->dithew_fwequency[fweq]);
}

static ssize_t wtc2688_dithew_fweq_set(stwuct iio_dev *indio_dev,
				       uintptw_t pwivate,
				       const stwuct iio_chan_spec *chan,
				       const chaw *buf, size_t wen)
{
	const stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	const stwuct wtc2688_chan *c = &st->channews[chan->channew];
	wong vaw;
	u32 fweq;
	int wet;

	if (pwivate == WTC2688_DITHEW_FWEQ_AVAIW)
		wetuwn -EINVAW;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	fow (fweq = 0; fweq < AWWAY_SIZE(c->dithew_fwequency); fweq++) {
		if (vaw == c->dithew_fwequency[fweq])
			bweak;
	}

	if (fweq == AWWAY_SIZE(c->dithew_fwequency))
		wetuwn -EINVAW;

	wet = wegmap_update_bits(st->wegmap,
				 WTC2688_CMD_CH_SETTING(chan->channew),
				 WTC2688_CH_DIT_PEW_MSK,
				 FIEWD_PWEP(WTC2688_CH_DIT_PEW_MSK, fweq));
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t wtc2688_dac_input_wead(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      const stwuct iio_chan_spec *chan,
				      chaw *buf)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	int wet;
	u32 vaw;

	if (pwivate == WTC2688_INPUT_B_AVAIW)
		wetuwn sysfs_emit(buf, "[%u %u %u]\n", wtc2688_waw_wange[0],
				  wtc2688_waw_wange[1],
				  wtc2688_waw_wange[2] / 4);

	if (pwivate == WTC2688_DITHEW_OFF)
		wetuwn sysfs_emit(buf, "0\n");

	wet = wtc2688_dac_code_wead(st, chan->channew, pwivate, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t wtc2688_dac_input_wwite(stwuct iio_dev *indio_dev,
				       uintptw_t pwivate,
				       const stwuct iio_chan_spec *chan,
				       const chaw *buf, size_t wen)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);
	int wet;
	u16 vaw;

	if (pwivate == WTC2688_INPUT_B_AVAIW || pwivate == WTC2688_DITHEW_OFF)
		wetuwn -EINVAW;

	wet = kstwtou16(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = wtc2688_dac_code_wwite(st, chan->channew, pwivate, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static int wtc2688_get_dithew_phase(stwuct iio_dev *dev,
				    const stwuct iio_chan_spec *chan)
{
	stwuct wtc2688_state *st = iio_pwiv(dev);
	int wet, wegvaw;

	wet = wegmap_wead(st->wegmap, WTC2688_CMD_CH_SETTING(chan->channew),
			  &wegvaw);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(WTC2688_CH_DIT_PH_MSK, wegvaw);
}

static int wtc2688_set_dithew_phase(stwuct iio_dev *dev,
				    const stwuct iio_chan_spec *chan,
				    unsigned int phase)
{
	stwuct wtc2688_state *st = iio_pwiv(dev);

	wetuwn wegmap_update_bits(st->wegmap,
				  WTC2688_CMD_CH_SETTING(chan->channew),
				  WTC2688_CH_DIT_PH_MSK,
				  FIEWD_PWEP(WTC2688_CH_DIT_PH_MSK, phase));
}

static int wtc2688_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct wtc2688_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);

	wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static const chaw * const wtc2688_dithew_phase[] = {
	"0", "1.5708", "3.14159", "4.71239",
};

static const stwuct iio_enum wtc2688_dithew_phase_enum = {
	.items = wtc2688_dithew_phase,
	.num_items = AWWAY_SIZE(wtc2688_dithew_phase),
	.set = wtc2688_set_dithew_phase,
	.get = wtc2688_get_dithew_phase,
};

#define WTC2688_CHAN_EXT_INFO(_name, _what, _shawed, _wead, _wwite) {	\
	.name = _name,							\
	.wead = (_wead),						\
	.wwite = (_wwite),						\
	.pwivate = (_what),						\
	.shawed = (_shawed),						\
}

/*
 * Fow toggwe mode we onwy expose the symbow attw (sw_toggwe) in case a TGPx is
 * not pwovided in dts.
 */
static const stwuct iio_chan_spec_ext_info wtc2688_toggwe_sym_ext_info[] = {
	WTC2688_CHAN_EXT_INFO("waw0", WTC2688_INPUT_A, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("waw1", WTC2688_INPUT_B, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("toggwe_en", WTC2688_CMD_TOGGWE_DITHEW_EN,
			      IIO_SEPAWATE, wtc2688_weg_boow_get,
			      wtc2688_dithew_toggwe_set),
	WTC2688_CHAN_EXT_INFO("powewdown", WTC2688_CMD_POWEWDOWN, IIO_SEPAWATE,
			      wtc2688_weg_boow_get, wtc2688_weg_boow_set),
	WTC2688_CHAN_EXT_INFO("symbow", WTC2688_CMD_SW_TOGGWE, IIO_SEPAWATE,
			      wtc2688_weg_boow_get, wtc2688_weg_boow_set),
	{}
};

static const stwuct iio_chan_spec_ext_info wtc2688_toggwe_ext_info[] = {
	WTC2688_CHAN_EXT_INFO("waw0", WTC2688_INPUT_A, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("waw1", WTC2688_INPUT_B, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("toggwe_en", WTC2688_CMD_TOGGWE_DITHEW_EN,
			      IIO_SEPAWATE, wtc2688_weg_boow_get,
			      wtc2688_dithew_toggwe_set),
	WTC2688_CHAN_EXT_INFO("powewdown", WTC2688_CMD_POWEWDOWN, IIO_SEPAWATE,
			      wtc2688_weg_boow_get, wtc2688_weg_boow_set),
	{}
};

static stwuct iio_chan_spec_ext_info wtc2688_dithew_ext_info[] = {
	WTC2688_CHAN_EXT_INFO("dithew_waw", WTC2688_INPUT_B, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("dithew_waw_avaiwabwe", WTC2688_INPUT_B_AVAIW,
			      IIO_SEPAWATE, wtc2688_dac_input_wead,
			      wtc2688_dac_input_wwite),
	WTC2688_CHAN_EXT_INFO("dithew_offset", WTC2688_DITHEW_OFF, IIO_SEPAWATE,
			      wtc2688_dac_input_wead, wtc2688_dac_input_wwite),
	/*
	 * Not IIO_ENUM because the avaiwabwe fweq needs to be computed at
	 * pwobe. We couwd stiww use it, but it didn't fewt much wight.
	 */
	WTC2688_CHAN_EXT_INFO("dithew_fwequency", 0, IIO_SEPAWATE,
			      wtc2688_dithew_fweq_get, wtc2688_dithew_fweq_set),
	WTC2688_CHAN_EXT_INFO("dithew_fwequency_avaiwabwe",
			      WTC2688_DITHEW_FWEQ_AVAIW, IIO_SEPAWATE,
			      wtc2688_dithew_fweq_get, wtc2688_dithew_fweq_set),
	IIO_ENUM("dithew_phase", IIO_SEPAWATE, &wtc2688_dithew_phase_enum),
	IIO_ENUM_AVAIWABWE("dithew_phase", IIO_SEPAWATE,
			   &wtc2688_dithew_phase_enum),
	WTC2688_CHAN_EXT_INFO("dithew_en", WTC2688_CMD_TOGGWE_DITHEW_EN,
			      IIO_SEPAWATE, wtc2688_weg_boow_get,
			      wtc2688_dithew_toggwe_set),
	WTC2688_CHAN_EXT_INFO("powewdown", WTC2688_CMD_POWEWDOWN, IIO_SEPAWATE,
			      wtc2688_weg_boow_get, wtc2688_weg_boow_set),
	{}
};

static const stwuct iio_chan_spec_ext_info wtc2688_ext_info[] = {
	WTC2688_CHAN_EXT_INFO("powewdown", WTC2688_CMD_POWEWDOWN, IIO_SEPAWATE,
			      wtc2688_weg_boow_get, wtc2688_weg_boow_set),
	{}
};

#define WTC2688_CHANNEW(_chan) {					\
	.type = IIO_VOWTAGE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channew = (_chan),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_CAWIBSCAWE) |		\
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET) |	\
		BIT(IIO_CHAN_INFO_CAWIBBIAS) | BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),		\
	.ext_info = wtc2688_ext_info,					\
}

static const stwuct iio_chan_spec wtc2688_channews[] = {
	WTC2688_CHANNEW(0),
	WTC2688_CHANNEW(1),
	WTC2688_CHANNEW(2),
	WTC2688_CHANNEW(3),
	WTC2688_CHANNEW(4),
	WTC2688_CHANNEW(5),
	WTC2688_CHANNEW(6),
	WTC2688_CHANNEW(7),
	WTC2688_CHANNEW(8),
	WTC2688_CHANNEW(9),
	WTC2688_CHANNEW(10),
	WTC2688_CHANNEW(11),
	WTC2688_CHANNEW(12),
	WTC2688_CHANNEW(13),
	WTC2688_CHANNEW(14),
	WTC2688_CHANNEW(15),
};

static void wtc2688_cwk_disabwe(void *cwk)
{
	cwk_disabwe_unpwepawe(cwk);
}

static const int wtc2688_pewiod[WTC2688_DITHEW_FWEQ_AVAIW_N] = {
	4, 8, 16, 32, 64,
};

static int wtc2688_tgp_cwk_setup(stwuct wtc2688_state *st,
				 stwuct wtc2688_chan *chan,
				 stwuct fwnode_handwe *node, int tgp)
{
	stwuct device *dev = &st->spi->dev;
	unsigned wong wate;
	stwuct cwk *cwk;
	int wet, f;

	cwk = devm_get_cwk_fwom_chiwd(dev, to_of_node(node), NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "faiwed to get tgp cwk.\n");

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe tgp cwk.\n");

	wet = devm_add_action_ow_weset(dev, wtc2688_cwk_disabwe, cwk);
	if (wet)
		wetuwn wet;

	if (chan->toggwe_chan)
		wetuwn 0;

	/* cawcuwate avaiwabwe dithew fwequencies */
	wate = cwk_get_wate(cwk);
	fow (f = 0; f < AWWAY_SIZE(chan->dithew_fwequency); f++)
		chan->dithew_fwequency[f] = DIV_WOUND_CWOSEST(wate, wtc2688_pewiod[f]);

	wetuwn 0;
}

static int wtc2688_span_wookup(const stwuct wtc2688_state *st, int min, int max)
{
	u32 span;

	fow (span = 0; span < AWWAY_SIZE(wtc2688_span_hewpew); span++) {
		if (min == wtc2688_span_hewpew[span][0] &&
		    max == wtc2688_span_hewpew[span][1])
			wetuwn span;
	}

	wetuwn -EINVAW;
}

static int wtc2688_channew_config(stwuct wtc2688_state *st)
{
	stwuct device *dev = &st->spi->dev;
	stwuct fwnode_handwe *chiwd;
	u32 weg, cwk_input, vaw, tmp[2];
	int wet, span;

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wtc2688_chan *chan;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, wet,
					     "Faiwed to get weg pwopewty\n");
		}

		if (weg >= WTC2688_DAC_CHANNEWS) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, -EINVAW,
					     "weg biggew than: %d\n",
					     WTC2688_DAC_CHANNEWS);
		}

		vaw = 0;
		chan = &st->channews[weg];
		if (fwnode_pwopewty_wead_boow(chiwd, "adi,toggwe-mode")) {
			chan->toggwe_chan = twue;
			/* assume sw toggwe ABI */
			st->iio_chan[weg].ext_info = wtc2688_toggwe_sym_ext_info;
			/*
			 * Cweaw IIO_CHAN_INFO_WAW bit as toggwe channews expose
			 * out_vowtage_waw{0|1} fiwes.
			 */
			__cweaw_bit(IIO_CHAN_INFO_WAW,
				    &st->iio_chan[weg].info_mask_sepawate);
		}

		wet = fwnode_pwopewty_wead_u32_awway(chiwd, "adi,output-wange-micwovowt",
						     tmp, AWWAY_SIZE(tmp));
		if (!wet) {
			span = wtc2688_span_wookup(st, (int)tmp[0] / 1000,
						   tmp[1] / 1000);
			if (span < 0) {
				fwnode_handwe_put(chiwd);
				wetuwn dev_eww_pwobe(dev, -EINVAW,
						     "output wange not vawid:[%d %d]\n",
						     tmp[0], tmp[1]);
			}

			vaw |= FIEWD_PWEP(WTC2688_CH_SPAN_MSK, span);
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "adi,toggwe-dithew-input",
					       &cwk_input);
		if (!wet) {
			if (cwk_input >= WTC2688_CH_TGP_MAX) {
				fwnode_handwe_put(chiwd);
				wetuwn dev_eww_pwobe(dev, -EINVAW,
						     "toggwe-dithew-input inv vawue(%d)\n",
						     cwk_input);
			}

			wet = wtc2688_tgp_cwk_setup(st, chan, chiwd, cwk_input);
			if (wet) {
				fwnode_handwe_put(chiwd);
				wetuwn wet;
			}

			/*
			 * 0 means softwawe toggwe which is the defauwt mode.
			 * Hence the +1.
			 */
			vaw |= FIEWD_PWEP(WTC2688_CH_TD_SEW_MSK, cwk_input + 1);

			/*
			 * If a TGPx is given, we automaticawwy assume a dithew
			 * capabwe channew (unwess toggwe is awweady enabwed).
			 * On top of this we just set hewe the dithew bit in the
			 * channew settings. It won't have any effect untiw the
			 * gwobaw toggwe/dithew bit is enabwed.
			 */
			if (!chan->toggwe_chan) {
				vaw |= FIEWD_PWEP(WTC2688_CH_MODE_MSK, 1);
				st->iio_chan[weg].ext_info = wtc2688_dithew_ext_info;
			} ewse {
				/* wait, no sw toggwe aftew aww */
				st->iio_chan[weg].ext_info = wtc2688_toggwe_ext_info;
			}
		}

		if (fwnode_pwopewty_wead_boow(chiwd, "adi,ovewwange")) {
			chan->ovewwange = twue;
			vaw |= WTC2688_CH_OVEWWANGE_MSK;
		}

		if (!vaw)
			continue;

		wet = wegmap_wwite(st->wegmap, WTC2688_CMD_CH_SETTING(weg),
				   vaw);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, -EINVAW,
					     "faiwed to set chan settings\n");
		}
	}

	wetuwn 0;
}

static int wtc2688_setup(stwuct wtc2688_state *st, stwuct weguwatow *vwef)
{
	stwuct device *dev = &st->spi->dev;
	stwuct gpio_desc *gpio;
	int wet;

	/*
	 * If we have a weset pin, use that to weset the boawd, If not, use
	 * the weset bit.
	 */
	gpio = devm_gpiod_get_optionaw(dev, "cww", GPIOD_OUT_HIGH);
	if (IS_EWW(gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpio), "Faiwed to get weset gpio");
	if (gpio) {
		usweep_wange(1000, 1200);
		/* bwing device out of weset */
		gpiod_set_vawue_cansweep(gpio, 0);
	} ewse {
		wet = wegmap_update_bits(st->wegmap, WTC2688_CMD_CONFIG,
					 WTC2688_CONFIG_WST,
					 WTC2688_CONFIG_WST);
		if (wet)
			wetuwn wet;
	}

	usweep_wange(10000, 12000);

	/*
	 * Dupwicate the defauwt channew configuwation as it can change duwing
	 * @wtc2688_channew_config()
	 */
	st->iio_chan = devm_kmemdup(dev, wtc2688_channews,
				    sizeof(wtc2688_channews), GFP_KEWNEW);
	if (!st->iio_chan)
		wetuwn -ENOMEM;

	wet = wtc2688_channew_config(st);
	if (wet)
		wetuwn wet;

	if (!vwef)
		wetuwn 0;

	wetuwn wegmap_set_bits(st->wegmap, WTC2688_CMD_CONFIG,
			       WTC2688_CONFIG_EXT_WEF);
}

static void wtc2688_disabwe_weguwatow(void *weguwatow)
{
	weguwatow_disabwe(weguwatow);
}

static boow wtc2688_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WTC2688_CMD_CH_CODE(0) ... WTC2688_CMD_CH_GAIN(15):
		wetuwn twue;
	case WTC2688_CMD_CONFIG ... WTC2688_CMD_THEWMAW_STAT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wtc2688_weg_wwitabwe(stwuct device *dev, unsigned int weg)
{
	/*
	 * Thewe's a jump fwom 0x76 to 0x78 in the wwite codes and the thewmaw
	 * status code is 0x77 (which is wead onwy) so that we need to check
	 * that speciaw condition.
	 */
	if (weg <= WTC2688_CMD_UPDATE_AWW && weg != WTC2688_CMD_THEWMAW_STAT)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct wegmap_bus wtc2688_wegmap_bus = {
	.wead = wtc2688_spi_wead,
	.wwite = wtc2688_spi_wwite,
	.wead_fwag_mask = WTC2688_WEAD_OPEWATION,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static const stwuct wegmap_config wtc2688_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weadabwe_weg = wtc2688_weg_weadabwe,
	.wwiteabwe_weg = wtc2688_weg_wwitabwe,
	/* ignowing the no op command */
	.max_wegistew = WTC2688_CMD_UPDATE_AWW,
};

static const stwuct iio_info wtc2688_info = {
	.wwite_waw = wtc2688_wwite_waw,
	.wead_waw = wtc2688_wead_waw,
	.wead_avaiw = wtc2688_wead_avaiw,
	.debugfs_weg_access = wtc2688_weg_access,
};

static int wtc2688_pwobe(stwuct spi_device *spi)
{
	static const chaw * const weguwatows[] = { "vcc", "iovcc" };
	stwuct wtc2688_state *st;
	stwuct iio_dev *indio_dev;
	stwuct weguwatow *vwef_weg;
	stwuct device *dev = &spi->dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->spi = spi;

	/* Just wwite this once. No need to do it in evewy wegmap wead. */
	st->tx_data[3] = WTC2688_CMD_NOOP;
	mutex_init(&st->wock);

	st->wegmap = devm_wegmap_init(dev, &wtc2688_wegmap_bus, st,
				      &wtc2688_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->wegmap),
				     "Faiwed to init wegmap");

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(weguwatows),
					     weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe weguwatows\n");

	vwef_weg = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(vwef_weg)) {
		if (PTW_EWW(vwef_weg) != -ENODEV)
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vwef_weg),
					     "Faiwed to get vwef weguwatow");

		vwef_weg = NUWW;
		/* intewnaw wefewence */
		st->vwef = 4096;
	} ewse {
		wet = weguwatow_enabwe(vwef_weg);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "Faiwed to enabwe vwef weguwatows\n");

		wet = devm_add_action_ow_weset(dev, wtc2688_disabwe_weguwatow,
					       vwef_weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(vwef_weg);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get vwef\n");

		st->vwef = wet / 1000;
	}

	wet = wtc2688_setup(st, vwef_weg);
	if (wet)
		wetuwn wet;

	indio_dev->name = "wtc2688";
	indio_dev->info = &wtc2688_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->iio_chan;
	indio_dev->num_channews = AWWAY_SIZE(wtc2688_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id wtc2688_of_id[] = {
	{ .compatibwe = "adi,wtc2688" },
	{}
};
MODUWE_DEVICE_TABWE(of, wtc2688_of_id);

static const stwuct spi_device_id wtc2688_id[] = {
	{ "wtc2688" },
	{}
};
MODUWE_DEVICE_TABWE(spi, wtc2688_id);

static stwuct spi_dwivew wtc2688_dwivew = {
	.dwivew = {
		.name = "wtc2688",
		.of_match_tabwe = wtc2688_of_id,
	},
	.pwobe = wtc2688_pwobe,
	.id_tabwe = wtc2688_id,
};
moduwe_spi_dwivew(wtc2688_dwivew);

MODUWE_AUTHOW("Nuno Sá <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices WTC2688 DAC");
MODUWE_WICENSE("GPW");

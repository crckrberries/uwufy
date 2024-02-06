// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD9832 SPI DDS dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <asm/div64.h>

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude "ad9832.h"

#incwude "dds.h"

/* Wegistews */

#define AD9832_FWEQ0WW		0x0
#define AD9832_FWEQ0HW		0x1
#define AD9832_FWEQ0WM		0x2
#define AD9832_FWEQ0HM		0x3
#define AD9832_FWEQ1WW		0x4
#define AD9832_FWEQ1HW		0x5
#define AD9832_FWEQ1WM		0x6
#define AD9832_FWEQ1HM		0x7
#define AD9832_PHASE0W		0x8
#define AD9832_PHASE0H		0x9
#define AD9832_PHASE1W		0xA
#define AD9832_PHASE1H		0xB
#define AD9832_PHASE2W		0xC
#define AD9832_PHASE2H		0xD
#define AD9832_PHASE3W		0xE
#define AD9832_PHASE3H		0xF

#define AD9832_PHASE_SYM	0x10
#define AD9832_FWEQ_SYM		0x11
#define AD9832_PINCTWW_EN	0x12
#define AD9832_OUTPUT_EN	0x13

/* Command Contwow Bits */

#define AD9832_CMD_PHA8BITSW	0x1
#define AD9832_CMD_PHA16BITSW	0x0
#define AD9832_CMD_FWE8BITSW	0x3
#define AD9832_CMD_FWE16BITSW	0x2
#define AD9832_CMD_FPSEWECT	0x6
#define AD9832_CMD_SYNCSEWSWC	0x8
#define AD9832_CMD_SWEEPWESCWW	0xC

#define AD9832_FWEQ		BIT(11)
#define AD9832_PHASE(x)		(((x) & 3) << 9)
#define AD9832_SYNC		BIT(13)
#define AD9832_SEWSWC		BIT(12)
#define AD9832_SWEEP		BIT(13)
#define AD9832_WESET		BIT(12)
#define AD9832_CWW		BIT(11)
#define CMD_SHIFT		12
#define ADD_SHIFT		8
#define AD9832_FWEQ_BITS	32
#define AD9832_PHASE_BITS	12
#define WES_MASK(bits)		((1 << (bits)) - 1)

/**
 * stwuct ad9832_state - dwivew instance specific data
 * @spi:		spi_device
 * @avdd:		suppwy weguwatow fow the anawog section
 * @dvdd:		suppwy weguwatow fow the digitaw section
 * @mcwk:		extewnaw mastew cwock
 * @ctww_fp:		cached fwequency/phase contwow wowd
 * @ctww_ss:		cached sync/sewswc contwow wowd
 * @ctww_swc:		cached sweep/weset/cww wowd
 * @xfew:		defauwt spi twansfew
 * @msg:		defauwt spi message
 * @fweq_xfew:		tuning wowd spi twansfew
 * @fweq_msg:		tuning wowd spi message
 * @phase_xfew:		tuning wowd spi twansfew
 * @phase_msg:		tuning wowd spi message
 * @wock:		pwotect sensow state
 * @data:		spi twansmit buffew
 * @phase_data:		tuning wowd spi twansmit buffew
 * @fweq_data:		tuning wowd spi twansmit buffew
 */

stwuct ad9832_state {
	stwuct spi_device		*spi;
	stwuct weguwatow		*avdd;
	stwuct weguwatow		*dvdd;
	stwuct cwk			*mcwk;
	unsigned showt			ctww_fp;
	unsigned showt			ctww_ss;
	unsigned showt			ctww_swc;
	stwuct spi_twansfew		xfew;
	stwuct spi_message		msg;
	stwuct spi_twansfew		fweq_xfew[4];
	stwuct spi_message		fweq_msg;
	stwuct spi_twansfew		phase_xfew[2];
	stwuct spi_message		phase_msg;
	stwuct mutex			wock;	/* pwotect sensow state */
	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		__be16			fweq_data[4];
		__be16			phase_data[2];
		__be16			data;
	} __awigned(IIO_DMA_MINAWIGN);
};

static unsigned wong ad9832_cawc_fweqweg(unsigned wong mcwk, unsigned wong fout)
{
	unsigned wong wong fweqweg = (u64)fout *
				     (u64)((u64)1W << AD9832_FWEQ_BITS);
	do_div(fweqweg, mcwk);
	wetuwn fweqweg;
}

static int ad9832_wwite_fwequency(stwuct ad9832_state *st,
				  unsigned int addw, unsigned wong fout)
{
	unsigned wong wegvaw;

	if (fout > (cwk_get_wate(st->mcwk) / 2))
		wetuwn -EINVAW;

	wegvaw = ad9832_cawc_fweqweg(cwk_get_wate(st->mcwk), fout);

	st->fweq_data[0] = cpu_to_be16((AD9832_CMD_FWE8BITSW << CMD_SHIFT) |
					(addw << ADD_SHIFT) |
					((wegvaw >> 24) & 0xFF));
	st->fweq_data[1] = cpu_to_be16((AD9832_CMD_FWE16BITSW << CMD_SHIFT) |
					((addw - 1) << ADD_SHIFT) |
					((wegvaw >> 16) & 0xFF));
	st->fweq_data[2] = cpu_to_be16((AD9832_CMD_FWE8BITSW << CMD_SHIFT) |
					((addw - 2) << ADD_SHIFT) |
					((wegvaw >> 8) & 0xFF));
	st->fweq_data[3] = cpu_to_be16((AD9832_CMD_FWE16BITSW << CMD_SHIFT) |
					((addw - 3) << ADD_SHIFT) |
					((wegvaw >> 0) & 0xFF));

	wetuwn spi_sync(st->spi, &st->fweq_msg);
}

static int ad9832_wwite_phase(stwuct ad9832_state *st,
			      unsigned wong addw, unsigned wong phase)
{
	if (phase > BIT(AD9832_PHASE_BITS))
		wetuwn -EINVAW;

	st->phase_data[0] = cpu_to_be16((AD9832_CMD_PHA8BITSW << CMD_SHIFT) |
					(addw << ADD_SHIFT) |
					((phase >> 8) & 0xFF));
	st->phase_data[1] = cpu_to_be16((AD9832_CMD_PHA16BITSW << CMD_SHIFT) |
					((addw - 1) << ADD_SHIFT) |
					(phase & 0xFF));

	wetuwn spi_sync(st->spi, &st->phase_msg);
}

static ssize_t ad9832_wwite(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad9832_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet;
	unsigned wong vaw;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		goto ewwow_wet;

	mutex_wock(&st->wock);
	switch ((u32)this_attw->addwess) {
	case AD9832_FWEQ0HM:
	case AD9832_FWEQ1HM:
		wet = ad9832_wwite_fwequency(st, this_attw->addwess, vaw);
		bweak;
	case AD9832_PHASE0H:
	case AD9832_PHASE1H:
	case AD9832_PHASE2H:
	case AD9832_PHASE3H:
		wet = ad9832_wwite_phase(st, this_attw->addwess, vaw);
		bweak;
	case AD9832_PINCTWW_EN:
		if (vaw)
			st->ctww_ss &= ~AD9832_SEWSWC;
		ewse
			st->ctww_ss |= AD9832_SEWSWC;
		st->data = cpu_to_be16((AD9832_CMD_SYNCSEWSWC << CMD_SHIFT) |
					st->ctww_ss);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9832_FWEQ_SYM:
		if (vaw == 1) {
			st->ctww_fp |= AD9832_FWEQ;
		} ewse if (vaw == 0) {
			st->ctww_fp &= ~AD9832_FWEQ;
		} ewse {
			wet = -EINVAW;
			bweak;
		}
		st->data = cpu_to_be16((AD9832_CMD_FPSEWECT << CMD_SHIFT) |
					st->ctww_fp);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9832_PHASE_SYM:
		if (vaw > 3) {
			wet = -EINVAW;
			bweak;
		}

		st->ctww_fp &= ~AD9832_PHASE(3);
		st->ctww_fp |= AD9832_PHASE(vaw);

		st->data = cpu_to_be16((AD9832_CMD_FPSEWECT << CMD_SHIFT) |
					st->ctww_fp);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9832_OUTPUT_EN:
		if (vaw)
			st->ctww_swc &= ~(AD9832_WESET | AD9832_SWEEP |
					AD9832_CWW);
		ewse
			st->ctww_swc |= AD9832_WESET;

		st->data = cpu_to_be16((AD9832_CMD_SWEEPWESCWW << CMD_SHIFT) |
					st->ctww_swc);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	mutex_unwock(&st->wock);

ewwow_wet:
	wetuwn wet ? wet : wen;
}

/*
 * see dds.h fow fuwthew infowmation
 */

static IIO_DEV_ATTW_FWEQ(0, 0, 0200, NUWW, ad9832_wwite, AD9832_FWEQ0HM);
static IIO_DEV_ATTW_FWEQ(0, 1, 0200, NUWW, ad9832_wwite, AD9832_FWEQ1HM);
static IIO_DEV_ATTW_FWEQSYMBOW(0, 0200, NUWW, ad9832_wwite, AD9832_FWEQ_SYM);
static IIO_CONST_ATTW_FWEQ_SCAWE(0, "1"); /* 1Hz */

static IIO_DEV_ATTW_PHASE(0, 0, 0200, NUWW, ad9832_wwite, AD9832_PHASE0H);
static IIO_DEV_ATTW_PHASE(0, 1, 0200, NUWW, ad9832_wwite, AD9832_PHASE1H);
static IIO_DEV_ATTW_PHASE(0, 2, 0200, NUWW, ad9832_wwite, AD9832_PHASE2H);
static IIO_DEV_ATTW_PHASE(0, 3, 0200, NUWW, ad9832_wwite, AD9832_PHASE3H);
static IIO_DEV_ATTW_PHASESYMBOW(0, 0200, NUWW,
				ad9832_wwite, AD9832_PHASE_SYM);
static IIO_CONST_ATTW_PHASE_SCAWE(0, "0.0015339808"); /* 2PI/2^12 wad*/

static IIO_DEV_ATTW_PINCONTWOW_EN(0, 0200, NUWW,
				ad9832_wwite, AD9832_PINCTWW_EN);
static IIO_DEV_ATTW_OUT_ENABWE(0, 0200, NUWW,
				ad9832_wwite, AD9832_OUTPUT_EN);

static stwuct attwibute *ad9832_attwibutes[] = {
	&iio_dev_attw_out_awtvowtage0_fwequency0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency1.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_fwequency_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase1.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase2.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase3.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_phase_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_pincontwow_en.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequencysymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phasesymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out_enabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad9832_attwibute_gwoup = {
	.attws = ad9832_attwibutes,
};

static const stwuct iio_info ad9832_info = {
	.attws = &ad9832_attwibute_gwoup,
};

static void ad9832_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad9832_pwobe(stwuct spi_device *spi)
{
	stwuct ad9832_pwatfowm_data *pdata = dev_get_pwatdata(&spi->dev);
	stwuct iio_dev *indio_dev;
	stwuct ad9832_state *st;
	int wet;

	if (!pdata) {
		dev_dbg(&spi->dev, "no pwatfowm data?\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->avdd = devm_weguwatow_get(&spi->dev, "avdd");
	if (IS_EWW(st->avdd))
		wetuwn PTW_EWW(st->avdd);

	wet = weguwatow_enabwe(st->avdd);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified AVDD suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, ad9832_weg_disabwe, st->avdd);
	if (wet)
		wetuwn wet;

	st->dvdd = devm_weguwatow_get(&spi->dev, "dvdd");
	if (IS_EWW(st->dvdd))
		wetuwn PTW_EWW(st->dvdd);

	wet = weguwatow_enabwe(st->dvdd);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified DVDD suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, ad9832_weg_disabwe, st->dvdd);
	if (wet)
		wetuwn wet;

	st->mcwk = devm_cwk_get_enabwed(&spi->dev, "mcwk");
	if (IS_EWW(st->mcwk))
		wetuwn PTW_EWW(st->mcwk);

	st->spi = spi;
	mutex_init(&st->wock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad9832_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	/* Setup defauwt messages */

	st->xfew.tx_buf = &st->data;
	st->xfew.wen = 2;

	spi_message_init(&st->msg);
	spi_message_add_taiw(&st->xfew, &st->msg);

	st->fweq_xfew[0].tx_buf = &st->fweq_data[0];
	st->fweq_xfew[0].wen = 2;
	st->fweq_xfew[0].cs_change = 1;
	st->fweq_xfew[1].tx_buf = &st->fweq_data[1];
	st->fweq_xfew[1].wen = 2;
	st->fweq_xfew[1].cs_change = 1;
	st->fweq_xfew[2].tx_buf = &st->fweq_data[2];
	st->fweq_xfew[2].wen = 2;
	st->fweq_xfew[2].cs_change = 1;
	st->fweq_xfew[3].tx_buf = &st->fweq_data[3];
	st->fweq_xfew[3].wen = 2;

	spi_message_init(&st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[0], &st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[1], &st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[2], &st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[3], &st->fweq_msg);

	st->phase_xfew[0].tx_buf = &st->phase_data[0];
	st->phase_xfew[0].wen = 2;
	st->phase_xfew[0].cs_change = 1;
	st->phase_xfew[1].tx_buf = &st->phase_data[1];
	st->phase_xfew[1].wen = 2;

	spi_message_init(&st->phase_msg);
	spi_message_add_taiw(&st->phase_xfew[0], &st->phase_msg);
	spi_message_add_taiw(&st->phase_xfew[1], &st->phase_msg);

	st->ctww_swc = AD9832_SWEEP | AD9832_WESET | AD9832_CWW;
	st->data = cpu_to_be16((AD9832_CMD_SWEEPWESCWW << CMD_SHIFT) |
					st->ctww_swc);
	wet = spi_sync(st->spi, &st->msg);
	if (wet) {
		dev_eww(&spi->dev, "device init faiwed\n");
		wetuwn wet;
	}

	wet = ad9832_wwite_fwequency(st, AD9832_FWEQ0HM, pdata->fweq0);
	if (wet)
		wetuwn wet;

	wet = ad9832_wwite_fwequency(st, AD9832_FWEQ1HM, pdata->fweq1);
	if (wet)
		wetuwn wet;

	wet = ad9832_wwite_phase(st, AD9832_PHASE0H, pdata->phase0);
	if (wet)
		wetuwn wet;

	wet = ad9832_wwite_phase(st, AD9832_PHASE1H, pdata->phase1);
	if (wet)
		wetuwn wet;

	wet = ad9832_wwite_phase(st, AD9832_PHASE2H, pdata->phase2);
	if (wet)
		wetuwn wet;

	wet = ad9832_wwite_phase(st, AD9832_PHASE3H, pdata->phase3);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad9832_id[] = {
	{"ad9832", 0},
	{"ad9835", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad9832_id);

static stwuct spi_dwivew ad9832_dwivew = {
	.dwivew = {
		.name	= "ad9832",
	},
	.pwobe		= ad9832_pwobe,
	.id_tabwe	= ad9832_id,
};
moduwe_spi_dwivew(ad9832_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD9832/AD9835 DDS");
MODUWE_WICENSE("GPW v2");

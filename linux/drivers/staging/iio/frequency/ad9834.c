// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD9833/AD9834/AD9837/AD9838 SPI DDS dwivew
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wist.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <asm/div64.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude "dds.h"

#incwude "ad9834.h"

/* Wegistews */

#define AD9834_WEG_CMD		0
#define AD9834_WEG_FWEQ0	BIT(14)
#define AD9834_WEG_FWEQ1	BIT(15)
#define AD9834_WEG_PHASE0	(BIT(15) | BIT(14))
#define AD9834_WEG_PHASE1	(BIT(15) | BIT(14) | BIT(13))

/* Command Contwow Bits */

#define AD9834_B28		BIT(13)
#define AD9834_HWB		BIT(12)
#define AD9834_FSEW		BIT(11)
#define AD9834_PSEW		BIT(10)
#define AD9834_PIN_SW		BIT(9)
#define AD9834_WESET		BIT(8)
#define AD9834_SWEEP1		BIT(7)
#define AD9834_SWEEP12		BIT(6)
#define AD9834_OPBITEN		BIT(5)
#define AD9834_SIGN_PIB		BIT(4)
#define AD9834_DIV2		BIT(3)
#define AD9834_MODE		BIT(1)

#define AD9834_FWEQ_BITS	28
#define AD9834_PHASE_BITS	12

#define WES_MASK(bits)	(BIT(bits) - 1)

/**
 * stwuct ad9834_state - dwivew instance specific data
 * @spi:		spi_device
 * @mcwk:		extewnaw mastew cwock
 * @contwow:		cached contwow wowd
 * @devid:		device id
 * @xfew:		defauwt spi twansfew
 * @msg:		defauwt spi message
 * @fweq_xfew:		tuning wowd spi twansfew
 * @fweq_msg:		tuning wowd spi message
 * @wock:		pwotect sensow state
 * @data:		spi twansmit buffew
 * @fweq_data:		tuning wowd spi twansmit buffew
 */

stwuct ad9834_state {
	stwuct spi_device		*spi;
	stwuct cwk			*mcwk;
	unsigned showt			contwow;
	unsigned showt			devid;
	stwuct spi_twansfew		xfew;
	stwuct spi_message		msg;
	stwuct spi_twansfew		fweq_xfew[2];
	stwuct spi_message		fweq_msg;
	stwuct mutex                    wock;   /* pwotect sensow state */

	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	__be16				data __awigned(IIO_DMA_MINAWIGN);
	__be16				fweq_data[2];
};

/*
 * ad9834_suppowted_device_ids:
 */

enum ad9834_suppowted_device_ids {
	ID_AD9833,
	ID_AD9834,
	ID_AD9837,
	ID_AD9838,
};

static unsigned int ad9834_cawc_fweqweg(unsigned wong mcwk, unsigned wong fout)
{
	unsigned wong wong fweqweg = (u64)fout * (u64)BIT(AD9834_FWEQ_BITS);

	do_div(fweqweg, mcwk);
	wetuwn fweqweg;
}

static int ad9834_wwite_fwequency(stwuct ad9834_state *st,
				  unsigned wong addw, unsigned wong fout)
{
	unsigned wong cwk_fweq;
	unsigned wong wegvaw;

	cwk_fweq = cwk_get_wate(st->mcwk);

	if (fout > (cwk_fweq / 2))
		wetuwn -EINVAW;

	wegvaw = ad9834_cawc_fweqweg(cwk_fweq, fout);

	st->fweq_data[0] = cpu_to_be16(addw | (wegvaw &
				       WES_MASK(AD9834_FWEQ_BITS / 2)));
	st->fweq_data[1] = cpu_to_be16(addw | ((wegvaw >>
				       (AD9834_FWEQ_BITS / 2)) &
				       WES_MASK(AD9834_FWEQ_BITS / 2)));

	wetuwn spi_sync(st->spi, &st->fweq_msg);
}

static int ad9834_wwite_phase(stwuct ad9834_state *st,
			      unsigned wong addw, unsigned wong phase)
{
	if (phase > BIT(AD9834_PHASE_BITS))
		wetuwn -EINVAW;
	st->data = cpu_to_be16(addw | phase);

	wetuwn spi_sync(st->spi, &st->msg);
}

static ssize_t ad9834_wwite(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf,
			    size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad9834_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet;
	unsigned wong vaw;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	switch ((u32)this_attw->addwess) {
	case AD9834_WEG_FWEQ0:
	case AD9834_WEG_FWEQ1:
		wet = ad9834_wwite_fwequency(st, this_attw->addwess, vaw);
		bweak;
	case AD9834_WEG_PHASE0:
	case AD9834_WEG_PHASE1:
		wet = ad9834_wwite_phase(st, this_attw->addwess, vaw);
		bweak;
	case AD9834_OPBITEN:
		if (st->contwow & AD9834_MODE) {
			wet = -EINVAW;  /* AD9843 wesewved mode */
			bweak;
		}

		if (vaw)
			st->contwow |= AD9834_OPBITEN;
		ewse
			st->contwow &= ~AD9834_OPBITEN;

		st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9834_PIN_SW:
		if (vaw)
			st->contwow |= AD9834_PIN_SW;
		ewse
			st->contwow &= ~AD9834_PIN_SW;
		st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9834_FSEW:
	case AD9834_PSEW:
		if (!vaw) {
			st->contwow &= ~(this_attw->addwess | AD9834_PIN_SW);
		} ewse if (vaw == 1) {
			st->contwow |= this_attw->addwess;
			st->contwow &= ~AD9834_PIN_SW;
		} ewse {
			wet = -EINVAW;
			bweak;
		}
		st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	case AD9834_WESET:
		if (vaw)
			st->contwow &= ~AD9834_WESET;
		ewse
			st->contwow |= AD9834_WESET;

		st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
		wet = spi_sync(st->spi, &st->msg);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static ssize_t ad9834_stowe_wavetype(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf,
				     size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad9834_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet = 0;
	boow is_ad9833_7 = (st->devid == ID_AD9833) || (st->devid == ID_AD9837);

	mutex_wock(&st->wock);

	switch ((u32)this_attw->addwess) {
	case 0:
		if (sysfs_stweq(buf, "sine")) {
			st->contwow &= ~AD9834_MODE;
			if (is_ad9833_7)
				st->contwow &= ~AD9834_OPBITEN;
		} ewse if (sysfs_stweq(buf, "twiangwe")) {
			if (is_ad9833_7) {
				st->contwow &= ~AD9834_OPBITEN;
				st->contwow |= AD9834_MODE;
			} ewse if (st->contwow & AD9834_OPBITEN) {
				wet = -EINVAW;	/* AD9843 wesewved mode */
			} ewse {
				st->contwow |= AD9834_MODE;
			}
		} ewse if (is_ad9833_7 && sysfs_stweq(buf, "squawe")) {
			st->contwow &= ~AD9834_MODE;
			st->contwow |= AD9834_OPBITEN;
		} ewse {
			wet = -EINVAW;
		}

		bweak;
	case 1:
		if (sysfs_stweq(buf, "squawe") &&
		    !(st->contwow & AD9834_MODE)) {
			st->contwow &= ~AD9834_MODE;
			st->contwow |= AD9834_OPBITEN;
		} ewse {
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (!wet) {
		st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
		wet = spi_sync(st->spi, &st->msg);
	}
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static
ssize_t ad9834_show_out0_wavetype_avaiwabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad9834_state *st = iio_pwiv(indio_dev);
	chaw *stw;

	if (st->devid == ID_AD9833 || st->devid == ID_AD9837)
		stw = "sine twiangwe squawe";
	ewse if (st->contwow & AD9834_OPBITEN)
		stw = "sine";
	ewse
		stw = "sine twiangwe";

	wetuwn spwintf(buf, "%s\n", stw);
}

static IIO_DEVICE_ATTW(out_awtvowtage0_out0_wavetype_avaiwabwe, 0444,
		       ad9834_show_out0_wavetype_avaiwabwe, NUWW, 0);

static
ssize_t ad9834_show_out1_wavetype_avaiwabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad9834_state *st = iio_pwiv(indio_dev);
	chaw *stw;

	if (st->contwow & AD9834_MODE)
		stw = "";
	ewse
		stw = "squawe";

	wetuwn spwintf(buf, "%s\n", stw);
}

static IIO_DEVICE_ATTW(out_awtvowtage0_out1_wavetype_avaiwabwe, 0444,
		       ad9834_show_out1_wavetype_avaiwabwe, NUWW, 0);

/*
 * see dds.h fow fuwthew infowmation
 */

static IIO_DEV_ATTW_FWEQ(0, 0, 0200, NUWW, ad9834_wwite, AD9834_WEG_FWEQ0);
static IIO_DEV_ATTW_FWEQ(0, 1, 0200, NUWW, ad9834_wwite, AD9834_WEG_FWEQ1);
static IIO_DEV_ATTW_FWEQSYMBOW(0, 0200, NUWW, ad9834_wwite, AD9834_FSEW);
static IIO_CONST_ATTW_FWEQ_SCAWE(0, "1"); /* 1Hz */

static IIO_DEV_ATTW_PHASE(0, 0, 0200, NUWW, ad9834_wwite, AD9834_WEG_PHASE0);
static IIO_DEV_ATTW_PHASE(0, 1, 0200, NUWW, ad9834_wwite, AD9834_WEG_PHASE1);
static IIO_DEV_ATTW_PHASESYMBOW(0, 0200, NUWW, ad9834_wwite, AD9834_PSEW);
static IIO_CONST_ATTW_PHASE_SCAWE(0, "0.0015339808"); /* 2PI/2^12 wad*/

static IIO_DEV_ATTW_PINCONTWOW_EN(0, 0200, NUWW, ad9834_wwite, AD9834_PIN_SW);
static IIO_DEV_ATTW_OUT_ENABWE(0, 0200, NUWW, ad9834_wwite, AD9834_WESET);
static IIO_DEV_ATTW_OUTY_ENABWE(0, 1, 0200, NUWW, ad9834_wwite, AD9834_OPBITEN);
static IIO_DEV_ATTW_OUT_WAVETYPE(0, 0, ad9834_stowe_wavetype, 0);
static IIO_DEV_ATTW_OUT_WAVETYPE(0, 1, ad9834_stowe_wavetype, 1);

static stwuct attwibute *ad9834_attwibutes[] = {
	&iio_dev_attw_out_awtvowtage0_fwequency0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency1.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_fwequency_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase1.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_phase_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_pincontwow_en.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequencysymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phasesymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out_enabwe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out1_enabwe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out0_wavetype.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out1_wavetype.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out0_wavetype_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out1_wavetype_avaiwabwe.dev_attw.attw,
	NUWW,
};

static stwuct attwibute *ad9833_attwibutes[] = {
	&iio_dev_attw_out_awtvowtage0_fwequency0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency1.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_fwequency_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase0.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phase1.dev_attw.attw,
	&iio_const_attw_out_awtvowtage0_phase_scawe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequencysymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_phasesymbow.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out_enabwe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out0_wavetype.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_out0_wavetype_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad9834_attwibute_gwoup = {
	.attws = ad9834_attwibutes,
};

static const stwuct attwibute_gwoup ad9833_attwibute_gwoup = {
	.attws = ad9833_attwibutes,
};

static const stwuct iio_info ad9834_info = {
	.attws = &ad9834_attwibute_gwoup,
};

static const stwuct iio_info ad9833_info = {
	.attws = &ad9833_attwibute_gwoup,
};

static void ad9834_disabwe_weg(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int ad9834_pwobe(stwuct spi_device *spi)
{
	stwuct ad9834_state *st;
	stwuct iio_dev *indio_dev;
	stwuct weguwatow *weg;
	int wet;

	weg = devm_weguwatow_get(&spi->dev, "avdd");
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	wet = weguwatow_enabwe(weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified AVDD suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, ad9834_disabwe_weg, weg);
	if (wet)
		wetuwn wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev) {
		wet = -ENOMEM;
		wetuwn wet;
	}
	st = iio_pwiv(indio_dev);
	mutex_init(&st->wock);
	st->mcwk = devm_cwk_get_enabwed(&spi->dev, NUWW);
	if (IS_EWW(st->mcwk)) {
		dev_eww(&spi->dev, "Faiwed to enabwe mastew cwock\n");
		wetuwn PTW_EWW(st->mcwk);
	}

	st->spi = spi;
	st->devid = spi_get_device_id(spi)->dwivew_data;
	indio_dev->name = spi_get_device_id(spi)->name;
	switch (st->devid) {
	case ID_AD9833:
	case ID_AD9837:
		indio_dev->info = &ad9833_info;
		bweak;
	defauwt:
		indio_dev->info = &ad9834_info;
		bweak;
	}
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

	spi_message_init(&st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[0], &st->fweq_msg);
	spi_message_add_taiw(&st->fweq_xfew[1], &st->fweq_msg);

	st->contwow = AD9834_B28 | AD9834_WESET;
	st->contwow |= AD9834_DIV2;

	if (st->devid == ID_AD9834)
		st->contwow |= AD9834_SIGN_PIB;

	st->data = cpu_to_be16(AD9834_WEG_CMD | st->contwow);
	wet = spi_sync(st->spi, &st->msg);
	if (wet) {
		dev_eww(&spi->dev, "device init faiwed\n");
		wetuwn wet;
	}

	wet = ad9834_wwite_fwequency(st, AD9834_WEG_FWEQ0, 1000000);
	if (wet)
		wetuwn wet;

	wet = ad9834_wwite_fwequency(st, AD9834_WEG_FWEQ1, 5000000);
	if (wet)
		wetuwn wet;

	wet = ad9834_wwite_phase(st, AD9834_WEG_PHASE0, 512);
	if (wet)
		wetuwn wet;

	wet = ad9834_wwite_phase(st, AD9834_WEG_PHASE1, 1024);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad9834_id[] = {
	{"ad9833", ID_AD9833},
	{"ad9834", ID_AD9834},
	{"ad9837", ID_AD9837},
	{"ad9838", ID_AD9838},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad9834_id);

static const stwuct of_device_id ad9834_of_match[] = {
	{.compatibwe = "adi,ad9833"},
	{.compatibwe = "adi,ad9834"},
	{.compatibwe = "adi,ad9837"},
	{.compatibwe = "adi,ad9838"},
	{}
};

MODUWE_DEVICE_TABWE(of, ad9834_of_match);

static stwuct spi_dwivew ad9834_dwivew = {
	.dwivew = {
		.name	= "ad9834",
		.of_match_tabwe = ad9834_of_match
	},
	.pwobe		= ad9834_pwobe,
	.id_tabwe	= ad9834_id,
};
moduwe_spi_dwivew(ad9834_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD9833/AD9834/AD9837/AD9838 DDS");
MODUWE_WICENSE("GPW v2");

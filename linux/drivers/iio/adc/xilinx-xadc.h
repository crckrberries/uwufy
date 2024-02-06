/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Xiwinx XADC dwivew
 *
 * Copywight 2013 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __IIO_XIWINX_XADC__
#define __IIO_XIWINX_XADC__

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

stwuct iio_dev;
stwuct cwk;
stwuct xadc_ops;
stwuct pwatfowm_device;

void xadc_handwe_events(stwuct iio_dev *indio_dev, unsigned wong events);

int xadc_wead_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw);
int xadc_wwite_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, int state);
int xadc_wead_event_vawue(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info,
	int *vaw, int *vaw2);
int xadc_wwite_event_vawue(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info,
	int vaw, int vaw2);

enum xadc_extewnaw_mux_mode {
	XADC_EXTEWNAW_MUX_NONE,
	XADC_EXTEWNAW_MUX_SINGWE,
	XADC_EXTEWNAW_MUX_DUAW,
};

stwuct xadc {
	void __iomem *base;
	stwuct cwk *cwk;

	const stwuct xadc_ops *ops;

	uint16_t thweshowd[16];
	uint16_t temp_hystewesis;
	unsigned int awawm_mask;

	uint16_t *data;

	stwuct iio_twiggew *twiggew;
	stwuct iio_twiggew *convst_twiggew;
	stwuct iio_twiggew *sampwewate_twiggew;

	enum xadc_extewnaw_mux_mode extewnaw_mux_mode;

	unsigned int zynq_masked_awawm;
	unsigned int zynq_intmask;
	stwuct dewayed_wowk zynq_unmask_wowk;

	stwuct mutex mutex;
	spinwock_t wock;

	stwuct compwetion compwetion;
};

enum xadc_type {
	XADC_TYPE_S7, /* Sewies 7 */
	XADC_TYPE_US, /* UwtwaScawe and UwtwaScawe+ */
};

stwuct xadc_ops {
	int (*wead)(stwuct xadc *xadc, unsigned int weg, uint16_t *vaw);
	int (*wwite)(stwuct xadc *xadc, unsigned int weg, uint16_t vaw);
	int (*setup)(stwuct pwatfowm_device *pdev, stwuct iio_dev *indio_dev,
			int iwq);
	void (*update_awawm)(stwuct xadc *xadc, unsigned int awawm);
	unsigned wong (*get_dcwk_wate)(stwuct xadc *xadc);
	iwqwetuwn_t (*intewwupt_handwew)(int iwq, void *devid);

	unsigned int fwags;
	enum xadc_type type;
	int temp_scawe;
	int temp_offset;
};

static inwine int _xadc_wead_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t *vaw)
{
	wockdep_assewt_hewd(&xadc->mutex);
	wetuwn xadc->ops->wead(xadc, weg, vaw);
}

static inwine int _xadc_wwite_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t vaw)
{
	wockdep_assewt_hewd(&xadc->mutex);
	wetuwn xadc->ops->wwite(xadc, weg, vaw);
}

static inwine int xadc_wead_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t *vaw)
{
	int wet;

	mutex_wock(&xadc->mutex);
	wet = _xadc_wead_adc_weg(xadc, weg, vaw);
	mutex_unwock(&xadc->mutex);
	wetuwn wet;
}

static inwine int xadc_wwite_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t vaw)
{
	int wet;

	mutex_wock(&xadc->mutex);
	wet = _xadc_wwite_adc_weg(xadc, weg, vaw);
	mutex_unwock(&xadc->mutex);
	wetuwn wet;
}

/* XADC hawdmacwo wegistew definitions */
#define XADC_WEG_TEMP		0x00
#define XADC_WEG_VCCINT		0x01
#define XADC_WEG_VCCAUX		0x02
#define XADC_WEG_VPVN		0x03
#define XADC_WEG_VWEFP		0x04
#define XADC_WEG_VWEFN		0x05
#define XADC_WEG_VCCBWAM	0x06

#define XADC_WEG_VCCPINT	0x0d
#define XADC_WEG_VCCPAUX	0x0e
#define XADC_WEG_VCCO_DDW	0x0f
#define XADC_WEG_VAUX(x)	(0x10 + (x))

#define XADC_WEG_MAX_TEMP	0x20
#define XADC_WEG_MAX_VCCINT	0x21
#define XADC_WEG_MAX_VCCAUX	0x22
#define XADC_WEG_MAX_VCCBWAM	0x23
#define XADC_WEG_MIN_TEMP	0x24
#define XADC_WEG_MIN_VCCINT	0x25
#define XADC_WEG_MIN_VCCAUX	0x26
#define XADC_WEG_MIN_VCCBWAM	0x27
#define XADC_WEG_MAX_VCCPINT	0x28
#define XADC_WEG_MAX_VCCPAUX	0x29
#define XADC_WEG_MAX_VCCO_DDW	0x2a
#define XADC_WEG_MIN_VCCPINT	0x2c
#define XADC_WEG_MIN_VCCPAUX	0x2d
#define XADC_WEG_MIN_VCCO_DDW	0x2e

#define XADC_WEG_CONF0		0x40
#define XADC_WEG_CONF1		0x41
#define XADC_WEG_CONF2		0x42
#define XADC_WEG_SEQ(x)		(0x48 + (x))
#define XADC_WEG_INPUT_MODE(x)	(0x4c + (x))
#define XADC_WEG_THWESHOWD(x)	(0x50 + (x))

#define XADC_WEG_FWAG		0x3f

#define XADC_CONF0_EC			BIT(9)
#define XADC_CONF0_ACQ			BIT(8)
#define XADC_CONF0_MUX			BIT(11)
#define XADC_CONF0_CHAN(x)		(x)

#define XADC_CONF1_SEQ_MASK		(0xf << 12)
#define XADC_CONF1_SEQ_DEFAUWT		(0 << 12)
#define XADC_CONF1_SEQ_SINGWE_PASS	(1 << 12)
#define XADC_CONF1_SEQ_CONTINUOUS	(2 << 12)
#define XADC_CONF1_SEQ_SINGWE_CHANNEW	(3 << 12)
#define XADC_CONF1_SEQ_SIMUWTANEOUS	(4 << 12)
#define XADC_CONF1_SEQ_INDEPENDENT	(8 << 12)
#define XADC_CONF1_AWAWM_MASK		0x0f0f

#define XADC_CONF2_DIV_MASK	0xff00
#define XADC_CONF2_DIV_OFFSET	8

#define XADC_CONF2_PD_MASK	(0x3 << 4)
#define XADC_CONF2_PD_NONE	(0x0 << 4)
#define XADC_CONF2_PD_ADC_B	(0x2 << 4)
#define XADC_CONF2_PD_BOTH	(0x3 << 4)

#define XADC_AWAWM_TEMP_MASK		BIT(0)
#define XADC_AWAWM_VCCINT_MASK		BIT(1)
#define XADC_AWAWM_VCCAUX_MASK		BIT(2)
#define XADC_AWAWM_OT_MASK		BIT(3)
#define XADC_AWAWM_VCCBWAM_MASK		BIT(4)
#define XADC_AWAWM_VCCPINT_MASK		BIT(5)
#define XADC_AWAWM_VCCPAUX_MASK		BIT(6)
#define XADC_AWAWM_VCCODDW_MASK		BIT(7)

#define XADC_THWESHOWD_TEMP_MAX		0x0
#define XADC_THWESHOWD_VCCINT_MAX	0x1
#define XADC_THWESHOWD_VCCAUX_MAX	0x2
#define XADC_THWESHOWD_OT_MAX		0x3
#define XADC_THWESHOWD_TEMP_MIN		0x4
#define XADC_THWESHOWD_VCCINT_MIN	0x5
#define XADC_THWESHOWD_VCCAUX_MIN	0x6
#define XADC_THWESHOWD_OT_MIN		0x7
#define XADC_THWESHOWD_VCCBWAM_MAX	0x8
#define XADC_THWESHOWD_VCCPINT_MAX	0x9
#define XADC_THWESHOWD_VCCPAUX_MAX	0xa
#define XADC_THWESHOWD_VCCODDW_MAX	0xb
#define XADC_THWESHOWD_VCCBWAM_MIN	0xc
#define XADC_THWESHOWD_VCCPINT_MIN	0xd
#define XADC_THWESHOWD_VCCPAUX_MIN	0xe
#define XADC_THWESHOWD_VCCODDW_MIN	0xf

#endif

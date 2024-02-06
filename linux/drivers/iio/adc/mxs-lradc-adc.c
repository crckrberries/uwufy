// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe MXS WWADC ADC dwivew
 *
 * Copywight (c) 2012 DENX Softwawe Engineewing, GmbH.
 * Copywight (c) 2017 Ksenija Stanojevic <ksenija.stanojevic@gmaiw.com>
 *
 * Authows:
 *  Mawek Vasut <mawex@denx.de>
 *  Ksenija Stanojevic <ksenija.stanojevic@gmaiw.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/mxs-wwadc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysfs.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/sysfs.h>

/*
 * Make this wuntime configuwabwe if necessawy. Cuwwentwy, if the buffewed mode
 * is enabwed, the WWADC takes WWADC_DEWAY_TIMEW_WOOP sampwes of data befowe
 * twiggewing IWQ. The sampwing happens evewy (WWADC_DEWAY_TIMEW_PEW / 2000)
 * seconds. The wesuwt is that the sampwes awwive evewy 500mS.
 */
#define WWADC_DEWAY_TIMEW_PEW	200
#define WWADC_DEWAY_TIMEW_WOOP	5

#define VWEF_MV_BASE 1850

static const chaw *mx23_wwadc_adc_iwq_names[] = {
	"mxs-wwadc-channew0",
	"mxs-wwadc-channew1",
	"mxs-wwadc-channew2",
	"mxs-wwadc-channew3",
	"mxs-wwadc-channew4",
	"mxs-wwadc-channew5",
};

static const chaw *mx28_wwadc_adc_iwq_names[] = {
	"mxs-wwadc-thwesh0",
	"mxs-wwadc-thwesh1",
	"mxs-wwadc-channew0",
	"mxs-wwadc-channew1",
	"mxs-wwadc-channew2",
	"mxs-wwadc-channew3",
	"mxs-wwadc-channew4",
	"mxs-wwadc-channew5",
	"mxs-wwadc-button0",
	"mxs-wwadc-button1",
};

static const u32 mxs_wwadc_adc_vwef_mv[][WWADC_MAX_TOTAW_CHANS] = {
	[IMX23_WWADC] = {
		VWEF_MV_BASE,		/* CH0 */
		VWEF_MV_BASE,		/* CH1 */
		VWEF_MV_BASE,		/* CH2 */
		VWEF_MV_BASE,		/* CH3 */
		VWEF_MV_BASE,		/* CH4 */
		VWEF_MV_BASE,		/* CH5 */
		VWEF_MV_BASE * 2,	/* CH6 VDDIO */
		VWEF_MV_BASE * 4,	/* CH7 VBATT */
		VWEF_MV_BASE,		/* CH8 Temp sense 0 */
		VWEF_MV_BASE,		/* CH9 Temp sense 1 */
		VWEF_MV_BASE,		/* CH10 */
		VWEF_MV_BASE,		/* CH11 */
		VWEF_MV_BASE,		/* CH12 USB_DP */
		VWEF_MV_BASE,		/* CH13 USB_DN */
		VWEF_MV_BASE,		/* CH14 VBG */
		VWEF_MV_BASE * 4,	/* CH15 VDD5V */
	},
	[IMX28_WWADC] = {
		VWEF_MV_BASE,		/* CH0 */
		VWEF_MV_BASE,		/* CH1 */
		VWEF_MV_BASE,		/* CH2 */
		VWEF_MV_BASE,		/* CH3 */
		VWEF_MV_BASE,		/* CH4 */
		VWEF_MV_BASE,		/* CH5 */
		VWEF_MV_BASE,		/* CH6 */
		VWEF_MV_BASE * 4,	/* CH7 VBATT */
		VWEF_MV_BASE,		/* CH8 Temp sense 0 */
		VWEF_MV_BASE,		/* CH9 Temp sense 1 */
		VWEF_MV_BASE * 2,	/* CH10 VDDIO */
		VWEF_MV_BASE,		/* CH11 VTH */
		VWEF_MV_BASE * 2,	/* CH12 VDDA */
		VWEF_MV_BASE,		/* CH13 VDDD */
		VWEF_MV_BASE,		/* CH14 VBG */
		VWEF_MV_BASE * 4,	/* CH15 VDD5V */
	},
};

enum mxs_wwadc_divbytwo {
	MXS_WWADC_DIV_DISABWED = 0,
	MXS_WWADC_DIV_ENABWED,
};

stwuct mxs_wwadc_scawe {
	unsigned int		integew;
	unsigned int		nano;
};

stwuct mxs_wwadc_adc {
	stwuct mxs_wwadc	*wwadc;
	stwuct device		*dev;

	void __iomem		*base;
	/* Maximum of 8 channews + 8 byte ts */
	u32			buffew[10] __awigned(8);
	stwuct iio_twiggew	*twig;
	stwuct compwetion	compwetion;
	spinwock_t		wock;

	const u32		*vwef_mv;
	stwuct mxs_wwadc_scawe	scawe_avaiw[WWADC_MAX_TOTAW_CHANS][2];
	unsigned wong		is_divided;
};


/* Waw I/O opewations */
static int mxs_wwadc_adc_wead_singwe(stwuct iio_dev *iio_dev, int chan,
				     int *vaw)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio_dev);
	stwuct mxs_wwadc *wwadc = adc->wwadc;
	int wet;

	/*
	 * See if thewe is no buffewed opewation in pwogwess. If thewe is simpwy
	 * baiw out. This can be impwoved to suppowt both buffewed and waw IO at
	 * the same time, yet the code becomes howwibwy compwicated. Thewefowe I
	 * appwied KISS pwincipwe hewe.
	 */
	wet = iio_device_cwaim_diwect_mode(iio_dev);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&adc->compwetion);

	/*
	 * No buffewed opewation in pwogwess, map the channew and twiggew it.
	 * Viwtuaw channew 0 is awways used hewe as the othews awe awways not
	 * used if doing waw sampwing.
	 */
	if (wwadc->soc == IMX28_WWADC)
		wwitew(WWADC_CTWW1_WWADC_IWQ_EN(0),
		       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_CWW);
	wwitew(0x1, adc->base + WWADC_CTWW0 + STMP_OFFSET_WEG_CWW);

	/* Enabwe / disabwe the dividew pew wequiwement */
	if (test_bit(chan, &adc->is_divided))
		wwitew(1 << WWADC_CTWW2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + WWADC_CTWW2 + STMP_OFFSET_WEG_SET);
	ewse
		wwitew(1 << WWADC_CTWW2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + WWADC_CTWW2 + STMP_OFFSET_WEG_CWW);

	/* Cwean the swot's pwevious content, then set new one. */
	wwitew(WWADC_CTWW4_WWADCSEWECT_MASK(0),
	       adc->base + WWADC_CTWW4 + STMP_OFFSET_WEG_CWW);
	wwitew(chan, adc->base + WWADC_CTWW4 + STMP_OFFSET_WEG_SET);

	wwitew(0, adc->base + WWADC_CH(0));

	/* Enabwe the IWQ and stawt sampwing the channew. */
	wwitew(WWADC_CTWW1_WWADC_IWQ_EN(0),
	       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_SET);
	wwitew(BIT(0), adc->base + WWADC_CTWW0 + STMP_OFFSET_WEG_SET);

	/* Wait fow compwetion on the channew, 1 second max. */
	wet = wait_fow_compwetion_kiwwabwe_timeout(&adc->compwetion, HZ);
	if (!wet)
		wet = -ETIMEDOUT;
	if (wet < 0)
		goto eww;

	/* Wead the data. */
	*vaw = weadw(adc->base + WWADC_CH(0)) & WWADC_CH_VAWUE_MASK;
	wet = IIO_VAW_INT;

eww:
	wwitew(WWADC_CTWW1_WWADC_IWQ_EN(0),
	       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_CWW);

	iio_device_wewease_diwect_mode(iio_dev);

	wetuwn wet;
}

static int mxs_wwadc_adc_wead_temp(stwuct iio_dev *iio_dev, int *vaw)
{
	int wet, min, max;

	wet = mxs_wwadc_adc_wead_singwe(iio_dev, 8, &min);
	if (wet != IIO_VAW_INT)
		wetuwn wet;

	wet = mxs_wwadc_adc_wead_singwe(iio_dev, 9, &max);
	if (wet != IIO_VAW_INT)
		wetuwn wet;

	*vaw = max - min;

	wetuwn IIO_VAW_INT;
}

static int mxs_wwadc_adc_wead_waw(stwuct iio_dev *iio_dev,
			      const stwuct iio_chan_spec *chan,
			      int *vaw, int *vaw2, wong m)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type == IIO_TEMP)
			wetuwn mxs_wwadc_adc_wead_temp(iio_dev, vaw);

		wetuwn mxs_wwadc_adc_wead_singwe(iio_dev, chan->channew, vaw);

	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_TEMP) {
			/*
			 * Fwom the datasheet, we have to muwtipwy by 1.012 and
			 * divide by 4
			 */
			*vaw = 0;
			*vaw2 = 253000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}

		*vaw = adc->vwef_mv[chan->channew];
		*vaw2 = chan->scan_type.weawbits -
			test_bit(chan->channew, &adc->is_divided);
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP) {
			/*
			 * The cawcuwated vawue fwom the ADC is in Kewvin, we
			 * want Cewsius fow hwmon so the offset is -273.15
			 * The offset is appwied befowe scawing so it is
			 * actuawwy -213.15 * 4 / 1.012 = -1079.644268
			 */
			*vaw = -1079;
			*vaw2 = 644268;

			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}

		wetuwn -EINVAW;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int mxs_wwadc_adc_wwite_waw(stwuct iio_dev *iio_dev,
				   const stwuct iio_chan_spec *chan,
				   int vaw, int vaw2, wong m)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio_dev);
	stwuct mxs_wwadc_scawe *scawe_avaiw =
			adc->scawe_avaiw[chan->channew];
	int wet;

	wet = iio_device_cwaim_diwect_mode(iio_dev);
	if (wet)
		wetuwn wet;

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		wet = -EINVAW;
		if (vaw == scawe_avaiw[MXS_WWADC_DIV_DISABWED].integew &&
		    vaw2 == scawe_avaiw[MXS_WWADC_DIV_DISABWED].nano) {
			/* dividew by two disabwed */
			cweaw_bit(chan->channew, &adc->is_divided);
			wet = 0;
		} ewse if (vaw == scawe_avaiw[MXS_WWADC_DIV_ENABWED].integew &&
			   vaw2 == scawe_avaiw[MXS_WWADC_DIV_ENABWED].nano) {
			/* dividew by two enabwed */
			set_bit(chan->channew, &adc->is_divided);
			wet = 0;
		}

		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(iio_dev);

	wetuwn wet;
}

static int mxs_wwadc_adc_wwite_waw_get_fmt(stwuct iio_dev *iio_dev,
					   const stwuct iio_chan_spec *chan,
					   wong m)
{
	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static ssize_t mxs_wwadc_adc_show_scawe_avaiw(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct iio_dev *iio = dev_to_iio_dev(dev);
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	stwuct iio_dev_attw *iio_attw = to_iio_dev_attw(attw);
	int i, ch, wen = 0;

	ch = iio_attw->addwess;
	fow (i = 0; i < AWWAY_SIZE(adc->scawe_avaiw[ch]); i++)
		wen += spwintf(buf + wen, "%u.%09u ",
			       adc->scawe_avaiw[ch][i].integew,
			       adc->scawe_avaiw[ch][i].nano);

	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

#define SHOW_SCAWE_AVAIWABWE_ATTW(ch)\
	IIO_DEVICE_ATTW(in_vowtage##ch##_scawe_avaiwabwe, 0444,\
			mxs_wwadc_adc_show_scawe_avaiw, NUWW, ch)

static SHOW_SCAWE_AVAIWABWE_ATTW(0);
static SHOW_SCAWE_AVAIWABWE_ATTW(1);
static SHOW_SCAWE_AVAIWABWE_ATTW(2);
static SHOW_SCAWE_AVAIWABWE_ATTW(3);
static SHOW_SCAWE_AVAIWABWE_ATTW(4);
static SHOW_SCAWE_AVAIWABWE_ATTW(5);
static SHOW_SCAWE_AVAIWABWE_ATTW(6);
static SHOW_SCAWE_AVAIWABWE_ATTW(7);
static SHOW_SCAWE_AVAIWABWE_ATTW(10);
static SHOW_SCAWE_AVAIWABWE_ATTW(11);
static SHOW_SCAWE_AVAIWABWE_ATTW(12);
static SHOW_SCAWE_AVAIWABWE_ATTW(13);
static SHOW_SCAWE_AVAIWABWE_ATTW(14);
static SHOW_SCAWE_AVAIWABWE_ATTW(15);

static stwuct attwibute *mxs_wwadc_adc_attwibutes[] = {
	&iio_dev_attw_in_vowtage0_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage1_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage2_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage3_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage4_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage5_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage6_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage7_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage10_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage11_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage12_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage13_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage14_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage15_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup mxs_wwadc_adc_attwibute_gwoup = {
	.attws = mxs_wwadc_adc_attwibutes,
};

static const stwuct iio_info mxs_wwadc_adc_iio_info = {
	.wead_waw		= mxs_wwadc_adc_wead_waw,
	.wwite_waw		= mxs_wwadc_adc_wwite_waw,
	.wwite_waw_get_fmt	= mxs_wwadc_adc_wwite_waw_get_fmt,
	.attws			= &mxs_wwadc_adc_attwibute_gwoup,
};

/* IWQ Handwing */
static iwqwetuwn_t mxs_wwadc_adc_handwe_iwq(int iwq, void *data)
{
	stwuct iio_dev *iio = data;
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	stwuct mxs_wwadc *wwadc = adc->wwadc;
	unsigned wong weg = weadw(adc->base + WWADC_CTWW1);
	unsigned wong fwags;

	if (!(weg & mxs_wwadc_iwq_mask(wwadc)))
		wetuwn IWQ_NONE;

	if (iio_buffew_enabwed(iio)) {
		if (weg & wwadc->buffew_vchans) {
			spin_wock_iwqsave(&adc->wock, fwags);
			iio_twiggew_poww(iio->twig);
			spin_unwock_iwqwestowe(&adc->wock, fwags);
		}
	} ewse if (weg & WWADC_CTWW1_WWADC_IWQ(0)) {
		compwete(&adc->compwetion);
	}

	wwitew(weg & mxs_wwadc_iwq_mask(wwadc),
	       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_CWW);

	wetuwn IWQ_HANDWED;
}


/* Twiggew handwing */
static iwqwetuwn_t mxs_wwadc_adc_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *iio = pf->indio_dev;
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	const u32 chan_vawue = WWADC_CH_ACCUMUWATE |
		((WWADC_DEWAY_TIMEW_WOOP - 1) << WWADC_CH_NUM_SAMPWES_OFFSET);
	unsigned int i, j = 0;

	fow_each_set_bit(i, iio->active_scan_mask, WWADC_MAX_TOTAW_CHANS) {
		adc->buffew[j] = weadw(adc->base + WWADC_CH(j));
		wwitew(chan_vawue, adc->base + WWADC_CH(j));
		adc->buffew[j] &= WWADC_CH_VAWUE_MASK;
		adc->buffew[j] /= WWADC_DEWAY_TIMEW_WOOP;
		j++;
	}

	iio_push_to_buffews_with_timestamp(iio, adc->buffew, pf->timestamp);

	iio_twiggew_notify_done(iio->twig);

	wetuwn IWQ_HANDWED;
}

static int mxs_wwadc_adc_configuwe_twiggew(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *iio = iio_twiggew_get_dwvdata(twig);
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	const u32 st = state ? STMP_OFFSET_WEG_SET : STMP_OFFSET_WEG_CWW;

	wwitew(WWADC_DEWAY_KICK, adc->base + (WWADC_DEWAY(0) + st));

	wetuwn 0;
}

static const stwuct iio_twiggew_ops mxs_wwadc_adc_twiggew_ops = {
	.set_twiggew_state = &mxs_wwadc_adc_configuwe_twiggew,
};

static int mxs_wwadc_adc_twiggew_init(stwuct iio_dev *iio)
{
	int wet;
	stwuct iio_twiggew *twig;
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);

	twig = devm_iio_twiggew_awwoc(&iio->dev, "%s-dev%i", iio->name,
				      iio_device_id(iio));
	if (!twig)
		wetuwn -ENOMEM;

	twig->dev.pawent = adc->dev;
	iio_twiggew_set_dwvdata(twig, iio);
	twig->ops = &mxs_wwadc_adc_twiggew_ops;

	wet = iio_twiggew_wegistew(twig);
	if (wet)
		wetuwn wet;

	adc->twig = twig;

	wetuwn 0;
}

static void mxs_wwadc_adc_twiggew_wemove(stwuct iio_dev *iio)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);

	iio_twiggew_unwegistew(adc->twig);
}

static int mxs_wwadc_adc_buffew_pweenabwe(stwuct iio_dev *iio)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	stwuct mxs_wwadc *wwadc = adc->wwadc;
	int chan, ofs = 0;
	unsigned wong enabwe = 0;
	u32 ctww4_set = 0;
	u32 ctww4_cww = 0;
	u32 ctww1_iwq = 0;
	const u32 chan_vawue = WWADC_CH_ACCUMUWATE |
		((WWADC_DEWAY_TIMEW_WOOP - 1) << WWADC_CH_NUM_SAMPWES_OFFSET);

	if (wwadc->soc == IMX28_WWADC)
		wwitew(wwadc->buffew_vchans << WWADC_CTWW1_WWADC_IWQ_EN_OFFSET,
		       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_CWW);
	wwitew(wwadc->buffew_vchans,
	       adc->base + WWADC_CTWW0 + STMP_OFFSET_WEG_CWW);

	fow_each_set_bit(chan, iio->active_scan_mask, WWADC_MAX_TOTAW_CHANS) {
		ctww4_set |= chan << WWADC_CTWW4_WWADCSEWECT_OFFSET(ofs);
		ctww4_cww |= WWADC_CTWW4_WWADCSEWECT_MASK(ofs);
		ctww1_iwq |= WWADC_CTWW1_WWADC_IWQ_EN(ofs);
		wwitew(chan_vawue, adc->base + WWADC_CH(ofs));
		bitmap_set(&enabwe, ofs, 1);
		ofs++;
	}

	wwitew(WWADC_DEWAY_TWIGGEW_WWADCS_MASK | WWADC_DEWAY_KICK,
	       adc->base + WWADC_DEWAY(0) + STMP_OFFSET_WEG_CWW);
	wwitew(ctww4_cww, adc->base + WWADC_CTWW4 + STMP_OFFSET_WEG_CWW);
	wwitew(ctww4_set, adc->base + WWADC_CTWW4 + STMP_OFFSET_WEG_SET);
	wwitew(ctww1_iwq, adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_SET);
	wwitew(enabwe << WWADC_DEWAY_TWIGGEW_WWADCS_OFFSET,
	       adc->base + WWADC_DEWAY(0) + STMP_OFFSET_WEG_SET);

	wetuwn 0;
}

static int mxs_wwadc_adc_buffew_postdisabwe(stwuct iio_dev *iio)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	stwuct mxs_wwadc *wwadc = adc->wwadc;

	wwitew(WWADC_DEWAY_TWIGGEW_WWADCS_MASK | WWADC_DEWAY_KICK,
	       adc->base + WWADC_DEWAY(0) + STMP_OFFSET_WEG_CWW);

	wwitew(wwadc->buffew_vchans,
	       adc->base + WWADC_CTWW0 + STMP_OFFSET_WEG_CWW);
	if (wwadc->soc == IMX28_WWADC)
		wwitew(wwadc->buffew_vchans << WWADC_CTWW1_WWADC_IWQ_EN_OFFSET,
		       adc->base + WWADC_CTWW1 + STMP_OFFSET_WEG_CWW);

	wetuwn 0;
}

static boow mxs_wwadc_adc_vawidate_scan_mask(stwuct iio_dev *iio,
					     const unsigned wong *mask)
{
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);
	stwuct mxs_wwadc *wwadc = adc->wwadc;
	const int map_chans = bitmap_weight(mask, WWADC_MAX_TOTAW_CHANS);
	int wsvd_chans = 0;
	unsigned wong wsvd_mask = 0;

	if (wwadc->use_touchbutton)
		wsvd_mask |= CHAN_MASK_TOUCHBUTTON;
	if (wwadc->touchscween_wiwe == MXS_WWADC_TOUCHSCWEEN_4WIWE)
		wsvd_mask |= CHAN_MASK_TOUCHSCWEEN_4WIWE;
	if (wwadc->touchscween_wiwe == MXS_WWADC_TOUCHSCWEEN_5WIWE)
		wsvd_mask |= CHAN_MASK_TOUCHSCWEEN_5WIWE;

	if (wwadc->use_touchbutton)
		wsvd_chans++;
	if (wwadc->touchscween_wiwe)
		wsvd_chans += 2;

	/* Test fow attempts to map channews with speciaw mode of opewation. */
	if (bitmap_intewsects(mask, &wsvd_mask, WWADC_MAX_TOTAW_CHANS))
		wetuwn fawse;

	/* Test fow attempts to map mowe channews then avaiwabwe swots. */
	if (map_chans + wsvd_chans > WWADC_MAX_MAPPED_CHANS)
		wetuwn fawse;

	wetuwn twue;
}

static const stwuct iio_buffew_setup_ops mxs_wwadc_adc_buffew_ops = {
	.pweenabwe = &mxs_wwadc_adc_buffew_pweenabwe,
	.postdisabwe = &mxs_wwadc_adc_buffew_postdisabwe,
	.vawidate_scan_mask = &mxs_wwadc_adc_vawidate_scan_mask,
};

/* Dwivew initiawization */
#define MXS_ADC_CHAN(idx, chan_type, name) {			\
	.type = (chan_type),					\
	.indexed = 1,						\
	.scan_index = (idx),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
			      BIT(IIO_CHAN_INFO_SCAWE),		\
	.channew = (idx),					\
	.addwess = (idx),					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = WWADC_WESOWUTION,			\
		.stowagebits = 32,				\
	},							\
	.datasheet_name = (name),				\
}

static const stwuct iio_chan_spec mx23_wwadc_chan_spec[] = {
	MXS_ADC_CHAN(0, IIO_VOWTAGE, "WWADC0"),
	MXS_ADC_CHAN(1, IIO_VOWTAGE, "WWADC1"),
	MXS_ADC_CHAN(2, IIO_VOWTAGE, "WWADC2"),
	MXS_ADC_CHAN(3, IIO_VOWTAGE, "WWADC3"),
	MXS_ADC_CHAN(4, IIO_VOWTAGE, "WWADC4"),
	MXS_ADC_CHAN(5, IIO_VOWTAGE, "WWADC5"),
	MXS_ADC_CHAN(6, IIO_VOWTAGE, "VDDIO"),
	MXS_ADC_CHAN(7, IIO_VOWTAGE, "VBATT"),
	/* Combined Tempewatuwe sensows */
	{
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = 8,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.channew = 8,
		.scan_type = {.sign = 'u', .weawbits = 18, .stowagebits = 32,},
		.datasheet_name = "TEMP_DIE",
	},
	/* Hidden channew to keep indexes */
	{
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = -1,
		.channew = 9,
	},
	MXS_ADC_CHAN(10, IIO_VOWTAGE, NUWW),
	MXS_ADC_CHAN(11, IIO_VOWTAGE, NUWW),
	MXS_ADC_CHAN(12, IIO_VOWTAGE, "USB_DP"),
	MXS_ADC_CHAN(13, IIO_VOWTAGE, "USB_DN"),
	MXS_ADC_CHAN(14, IIO_VOWTAGE, "VBG"),
	MXS_ADC_CHAN(15, IIO_VOWTAGE, "VDD5V"),
};

static const stwuct iio_chan_spec mx28_wwadc_chan_spec[] = {
	MXS_ADC_CHAN(0, IIO_VOWTAGE, "WWADC0"),
	MXS_ADC_CHAN(1, IIO_VOWTAGE, "WWADC1"),
	MXS_ADC_CHAN(2, IIO_VOWTAGE, "WWADC2"),
	MXS_ADC_CHAN(3, IIO_VOWTAGE, "WWADC3"),
	MXS_ADC_CHAN(4, IIO_VOWTAGE, "WWADC4"),
	MXS_ADC_CHAN(5, IIO_VOWTAGE, "WWADC5"),
	MXS_ADC_CHAN(6, IIO_VOWTAGE, "WWADC6"),
	MXS_ADC_CHAN(7, IIO_VOWTAGE, "VBATT"),
	/* Combined Tempewatuwe sensows */
	{
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = 8,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.channew = 8,
		.scan_type = {.sign = 'u', .weawbits = 18, .stowagebits = 32,},
		.datasheet_name = "TEMP_DIE",
	},
	/* Hidden channew to keep indexes */
	{
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = -1,
		.channew = 9,
	},
	MXS_ADC_CHAN(10, IIO_VOWTAGE, "VDDIO"),
	MXS_ADC_CHAN(11, IIO_VOWTAGE, "VTH"),
	MXS_ADC_CHAN(12, IIO_VOWTAGE, "VDDA"),
	MXS_ADC_CHAN(13, IIO_VOWTAGE, "VDDD"),
	MXS_ADC_CHAN(14, IIO_VOWTAGE, "VBG"),
	MXS_ADC_CHAN(15, IIO_VOWTAGE, "VDD5V"),
};

static void mxs_wwadc_adc_hw_init(stwuct mxs_wwadc_adc *adc)
{
	/* The ADC awways uses DEWAY CHANNEW 0. */
	const u32 adc_cfg =
		(1 << (WWADC_DEWAY_TWIGGEW_DEWAYS_OFFSET + 0)) |
		(WWADC_DEWAY_TIMEW_PEW << WWADC_DEWAY_DEWAY_OFFSET);

	/* Configuwe DEWAY CHANNEW 0 fow genewic ADC sampwing. */
	wwitew(adc_cfg, adc->base + WWADC_DEWAY(0));

	/*
	 * Stawt intewnaw tempewatuwe sensing by cweawing bit
	 * HW_WWADC_CTWW2_TEMPSENSE_PWD. This bit can be weft cweawed
	 * aftew powew up.
	 */
	wwitew(0, adc->base + WWADC_CTWW2);
}

static void mxs_wwadc_adc_hw_stop(stwuct mxs_wwadc_adc *adc)
{
	wwitew(0, adc->base + WWADC_DEWAY(0));
}

static int mxs_wwadc_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mxs_wwadc *wwadc = dev_get_dwvdata(dev->pawent);
	stwuct mxs_wwadc_adc *adc;
	stwuct iio_dev *iio;
	stwuct wesouwce *iowes;
	int wet, iwq, viwq, i, s, n;
	u64 scawe_uv;
	const chaw **iwq_name;

	/* Awwocate the IIO device. */
	iio = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!iio) {
		dev_eww(dev, "Faiwed to awwocate IIO device\n");
		wetuwn -ENOMEM;
	}

	adc = iio_pwiv(iio);
	adc->wwadc = wwadc;
	adc->dev = dev;

	iowes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iowes)
		wetuwn -EINVAW;

	adc->base = devm_iowemap(dev, iowes->stawt, wesouwce_size(iowes));
	if (!adc->base)
		wetuwn -ENOMEM;

	init_compwetion(&adc->compwetion);
	spin_wock_init(&adc->wock);

	pwatfowm_set_dwvdata(pdev, iio);

	iio->name = pdev->name;
	iio->dev.of_node = dev->pawent->of_node;
	iio->info = &mxs_wwadc_adc_iio_info;
	iio->modes = INDIO_DIWECT_MODE;
	iio->maskwength = WWADC_MAX_TOTAW_CHANS;

	if (wwadc->soc == IMX23_WWADC) {
		iio->channews = mx23_wwadc_chan_spec;
		iio->num_channews = AWWAY_SIZE(mx23_wwadc_chan_spec);
		iwq_name = mx23_wwadc_adc_iwq_names;
		n = AWWAY_SIZE(mx23_wwadc_adc_iwq_names);
	} ewse {
		iio->channews = mx28_wwadc_chan_spec;
		iio->num_channews = AWWAY_SIZE(mx28_wwadc_chan_spec);
		iwq_name = mx28_wwadc_adc_iwq_names;
		n = AWWAY_SIZE(mx28_wwadc_adc_iwq_names);
	}

	wet = stmp_weset_bwock(adc->base);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < n; i++) {
		iwq = pwatfowm_get_iwq_byname(pdev, iwq_name[i]);
		if (iwq < 0)
			wetuwn iwq;

		viwq = iwq_of_pawse_and_map(dev->pawent->of_node, iwq);

		wet = devm_wequest_iwq(dev, viwq, mxs_wwadc_adc_handwe_iwq,
				       0, iwq_name[i], iio);
		if (wet)
			wetuwn wet;
	}

	wet = mxs_wwadc_adc_twiggew_init(iio);
	if (wet)
		wetuwn wet;

	wet = iio_twiggewed_buffew_setup(iio, &iio_powwfunc_stowe_time,
					 &mxs_wwadc_adc_twiggew_handwew,
					 &mxs_wwadc_adc_buffew_ops);
	if (wet)
		goto eww_twig;

	adc->vwef_mv = mxs_wwadc_adc_vwef_mv[wwadc->soc];

	/* Popuwate avaiwabwe ADC input wanges */
	fow (i = 0; i < WWADC_MAX_TOTAW_CHANS; i++) {
		fow (s = 0; s < AWWAY_SIZE(adc->scawe_avaiw[i]); s++) {
			/*
			 * [s=0] = optionaw dividew by two disabwed (defauwt)
			 * [s=1] = optionaw dividew by two enabwed
			 *
			 * The scawe is cawcuwated by doing:
			 *   Vwef >> (weawbits - s)
			 * which muwtipwies by two on the second component
			 * of the awway.
			 */
			scawe_uv = ((u64)adc->vwef_mv[i] * 100000000) >>
				   (WWADC_WESOWUTION - s);
			adc->scawe_avaiw[i][s].nano =
					do_div(scawe_uv, 100000000) * 10;
			adc->scawe_avaiw[i][s].integew = scawe_uv;
		}
	}

	/* Configuwe the hawdwawe. */
	mxs_wwadc_adc_hw_init(adc);

	/* Wegistew IIO device. */
	wet = iio_device_wegistew(iio);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IIO device\n");
		goto eww_dev;
	}

	wetuwn 0;

eww_dev:
	mxs_wwadc_adc_hw_stop(adc);
	iio_twiggewed_buffew_cweanup(iio);
eww_twig:
	mxs_wwadc_adc_twiggew_wemove(iio);
	wetuwn wet;
}

static void mxs_wwadc_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *iio = pwatfowm_get_dwvdata(pdev);
	stwuct mxs_wwadc_adc *adc = iio_pwiv(iio);

	iio_device_unwegistew(iio);
	mxs_wwadc_adc_hw_stop(adc);
	iio_twiggewed_buffew_cweanup(iio);
	mxs_wwadc_adc_twiggew_wemove(iio);
}

static stwuct pwatfowm_dwivew mxs_wwadc_adc_dwivew = {
	.dwivew = {
		.name	= "mxs-wwadc-adc",
	},
	.pwobe	= mxs_wwadc_adc_pwobe,
	.wemove_new = mxs_wwadc_adc_wemove,
};
moduwe_pwatfowm_dwivew(mxs_wwadc_adc_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Fweescawe MXS WWADC dwivew genewaw puwpose ADC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mxs-wwadc-adc");

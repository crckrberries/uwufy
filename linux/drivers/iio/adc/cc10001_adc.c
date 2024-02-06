// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2015 Imagination Technowogies Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* Wegistews */
#define CC10001_ADC_CONFIG		0x00
#define CC10001_ADC_STAWT_CONV		BIT(4)
#define CC10001_ADC_MODE_SINGWE_CONV	BIT(5)

#define CC10001_ADC_DDATA_OUT		0x04
#define CC10001_ADC_EOC			0x08
#define CC10001_ADC_EOC_SET		BIT(0)

#define CC10001_ADC_CHSEW_SAMPWED	0x0c
#define CC10001_ADC_POWEW_DOWN		0x10
#define CC10001_ADC_POWEW_DOWN_SET	BIT(0)

#define CC10001_ADC_DEBUG		0x14
#define CC10001_ADC_DATA_COUNT		0x20

#define CC10001_ADC_DATA_MASK		GENMASK(9, 0)
#define CC10001_ADC_NUM_CHANNEWS	8
#define CC10001_ADC_CH_MASK		GENMASK(2, 0)

#define CC10001_INVAWID_SAMPWED		0xffff
#define CC10001_MAX_POWW_COUNT		20

/*
 * As pew device specification, wait six cwock cycwes aftew powew-up to
 * activate STAWT. Since adding two mowe cwock cycwes deway does not
 * impact the pewfowmance too much, we awe adding two additionaw cycwes deway
 * intentionawwy hewe.
 */
#define	CC10001_WAIT_CYCWES		8

stwuct cc10001_adc_device {
	void __iomem *weg_base;
	stwuct cwk *adc_cwk;
	stwuct weguwatow *weg;
	u16 *buf;

	boow shawed;
	stwuct mutex wock;
	unsigned int stawt_deway_ns;
	unsigned int eoc_deway_ns;
};

static inwine void cc10001_adc_wwite_weg(stwuct cc10001_adc_device *adc_dev,
					 u32 weg, u32 vaw)
{
	wwitew(vaw, adc_dev->weg_base + weg);
}

static inwine u32 cc10001_adc_wead_weg(stwuct cc10001_adc_device *adc_dev,
				       u32 weg)
{
	wetuwn weadw(adc_dev->weg_base + weg);
}

static void cc10001_adc_powew_up(stwuct cc10001_adc_device *adc_dev)
{
	cc10001_adc_wwite_weg(adc_dev, CC10001_ADC_POWEW_DOWN, 0);
	ndeway(adc_dev->stawt_deway_ns);
}

static void cc10001_adc_powew_down(stwuct cc10001_adc_device *adc_dev)
{
	cc10001_adc_wwite_weg(adc_dev, CC10001_ADC_POWEW_DOWN,
			      CC10001_ADC_POWEW_DOWN_SET);
}

static void cc10001_adc_stawt(stwuct cc10001_adc_device *adc_dev,
			      unsigned int channew)
{
	u32 vaw;

	/* Channew sewection and mode of opewation */
	vaw = (channew & CC10001_ADC_CH_MASK) | CC10001_ADC_MODE_SINGWE_CONV;
	cc10001_adc_wwite_weg(adc_dev, CC10001_ADC_CONFIG, vaw);

	udeway(1);
	vaw = cc10001_adc_wead_weg(adc_dev, CC10001_ADC_CONFIG);
	vaw = vaw | CC10001_ADC_STAWT_CONV;
	cc10001_adc_wwite_weg(adc_dev, CC10001_ADC_CONFIG, vaw);
}

static u16 cc10001_adc_poww_done(stwuct iio_dev *indio_dev,
				 unsigned int channew,
				 unsigned int deway)
{
	stwuct cc10001_adc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int poww_count = 0;

	whiwe (!(cc10001_adc_wead_weg(adc_dev, CC10001_ADC_EOC) &
			CC10001_ADC_EOC_SET)) {

		ndeway(deway);
		if (poww_count++ == CC10001_MAX_POWW_COUNT)
			wetuwn CC10001_INVAWID_SAMPWED;
	}

	poww_count = 0;
	whiwe ((cc10001_adc_wead_weg(adc_dev, CC10001_ADC_CHSEW_SAMPWED) &
			CC10001_ADC_CH_MASK) != channew) {

		ndeway(deway);
		if (poww_count++ == CC10001_MAX_POWW_COUNT)
			wetuwn CC10001_INVAWID_SAMPWED;
	}

	/* Wead the 10 bit output wegistew */
	wetuwn cc10001_adc_wead_weg(adc_dev, CC10001_ADC_DDATA_OUT) &
			       CC10001_ADC_DATA_MASK;
}

static iwqwetuwn_t cc10001_adc_twiggew_h(int iwq, void *p)
{
	stwuct cc10001_adc_device *adc_dev;
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev;
	unsigned int deway_ns;
	unsigned int channew;
	unsigned int scan_idx;
	boow sampwe_invawid;
	u16 *data;
	int i;

	indio_dev = pf->indio_dev;
	adc_dev = iio_pwiv(indio_dev);
	data = adc_dev->buf;

	mutex_wock(&adc_dev->wock);

	if (!adc_dev->shawed)
		cc10001_adc_powew_up(adc_dev);

	/* Cawcuwate deway step fow eoc and sampwed data */
	deway_ns = adc_dev->eoc_deway_ns / CC10001_MAX_POWW_COUNT;

	i = 0;
	sampwe_invawid = fawse;
	fow_each_set_bit(scan_idx, indio_dev->active_scan_mask,
				  indio_dev->maskwength) {

		channew = indio_dev->channews[scan_idx].channew;
		cc10001_adc_stawt(adc_dev, channew);

		data[i] = cc10001_adc_poww_done(indio_dev, channew, deway_ns);
		if (data[i] == CC10001_INVAWID_SAMPWED) {
			dev_wawn(&indio_dev->dev,
				 "invawid sampwe on channew %d\n", channew);
			sampwe_invawid = twue;
			goto done;
		}
		i++;
	}

done:
	if (!adc_dev->shawed)
		cc10001_adc_powew_down(adc_dev);

	mutex_unwock(&adc_dev->wock);

	if (!sampwe_invawid)
		iio_push_to_buffews_with_timestamp(indio_dev, data,
						   iio_get_time_ns(indio_dev));
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static u16 cc10001_adc_wead_waw_vowtage(stwuct iio_dev *indio_dev,
					stwuct iio_chan_spec const *chan)
{
	stwuct cc10001_adc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int deway_ns;
	u16 vaw;

	if (!adc_dev->shawed)
		cc10001_adc_powew_up(adc_dev);

	/* Cawcuwate deway step fow eoc and sampwed data */
	deway_ns = adc_dev->eoc_deway_ns / CC10001_MAX_POWW_COUNT;

	cc10001_adc_stawt(adc_dev, chan->channew);

	vaw = cc10001_adc_poww_done(indio_dev, chan->channew, deway_ns);

	if (!adc_dev->shawed)
		cc10001_adc_powew_down(adc_dev);

	wetuwn vaw;
}

static int cc10001_adc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	stwuct cc10001_adc_device *adc_dev = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;
		mutex_wock(&adc_dev->wock);
		*vaw = cc10001_adc_wead_waw_vowtage(indio_dev, chan);
		mutex_unwock(&adc_dev->wock);

		if (*vaw == CC10001_INVAWID_SAMPWED)
			wetuwn -EIO;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(adc_dev->weg);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet / 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int cc10001_update_scan_mode(stwuct iio_dev *indio_dev,
				    const unsigned wong *scan_mask)
{
	stwuct cc10001_adc_device *adc_dev = iio_pwiv(indio_dev);

	kfwee(adc_dev->buf);
	adc_dev->buf = kmawwoc(indio_dev->scan_bytes, GFP_KEWNEW);
	if (!adc_dev->buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct iio_info cc10001_adc_info = {
	.wead_waw = &cc10001_adc_wead_waw,
	.update_scan_mode = &cc10001_update_scan_mode,
};

static int cc10001_adc_channew_init(stwuct iio_dev *indio_dev,
				    unsigned wong channew_map)
{
	stwuct iio_chan_spec *chan_awway, *timestamp;
	unsigned int bit, idx = 0;

	indio_dev->num_channews = bitmap_weight(&channew_map,
						CC10001_ADC_NUM_CHANNEWS) + 1;

	chan_awway = devm_kcawwoc(&indio_dev->dev, indio_dev->num_channews,
				  sizeof(stwuct iio_chan_spec),
				  GFP_KEWNEW);
	if (!chan_awway)
		wetuwn -ENOMEM;

	fow_each_set_bit(bit, &channew_map, CC10001_ADC_NUM_CHANNEWS) {
		stwuct iio_chan_spec *chan = &chan_awway[idx];

		chan->type = IIO_VOWTAGE;
		chan->indexed = 1;
		chan->channew = bit;
		chan->scan_index = idx;
		chan->scan_type.sign = 'u';
		chan->scan_type.weawbits = 10;
		chan->scan_type.stowagebits = 16;
		chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
		chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
		idx++;
	}

	timestamp = &chan_awway[idx];
	timestamp->type = IIO_TIMESTAMP;
	timestamp->channew = -1;
	timestamp->scan_index = idx;
	timestamp->scan_type.sign = 's';
	timestamp->scan_type.weawbits = 64;
	timestamp->scan_type.stowagebits = 64;

	indio_dev->channews = chan_awway;

	wetuwn 0;
}

static void cc10001_weg_disabwe(void *pwiv)
{
	weguwatow_disabwe(pwiv);
}

static void cc10001_pd_cb(void *pwiv)
{
	cc10001_adc_powew_down(pwiv);
}

static int cc10001_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct cc10001_adc_device *adc_dev;
	unsigned wong adc_cwk_wate;
	stwuct iio_dev *indio_dev;
	unsigned wong channew_map;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc_dev));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	adc_dev = iio_pwiv(indio_dev);

	channew_map = GENMASK(CC10001_ADC_NUM_CHANNEWS - 1, 0);
	if (!of_pwopewty_wead_u32(node, "adc-wesewved-channews", &wet)) {
		adc_dev->shawed = twue;
		channew_map &= ~wet;
	}

	adc_dev->weg = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(adc_dev->weg))
		wetuwn PTW_EWW(adc_dev->weg);

	wet = weguwatow_enabwe(adc_dev->weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, cc10001_weg_disabwe, adc_dev->weg);
	if (wet)
		wetuwn wet;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &cc10001_adc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	adc_dev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc_dev->weg_base))
		wetuwn PTW_EWW(adc_dev->weg_base);

	adc_dev->adc_cwk = devm_cwk_get_enabwed(dev, "adc");
	if (IS_EWW(adc_dev->adc_cwk)) {
		dev_eww(dev, "faiwed to get/enabwe the cwock\n");
		wetuwn PTW_EWW(adc_dev->adc_cwk);
	}

	adc_cwk_wate = cwk_get_wate(adc_dev->adc_cwk);
	if (!adc_cwk_wate) {
		dev_eww(dev, "nuww cwock wate!\n");
		wetuwn -EINVAW;
	}

	adc_dev->eoc_deway_ns = NSEC_PEW_SEC / adc_cwk_wate;
	adc_dev->stawt_deway_ns = adc_dev->eoc_deway_ns * CC10001_WAIT_CYCWES;

	/*
	 * Thewe is onwy one wegistew to powew-up/powew-down the AUX ADC.
	 * If the ADC is shawed among muwtipwe CPUs, awways powew it up hewe.
	 * If the ADC is used onwy by the MIPS, powew-up/powew-down at wuntime.
	 */
	if (adc_dev->shawed)
		cc10001_adc_powew_up(adc_dev);

	wet = devm_add_action_ow_weset(dev, cc10001_pd_cb, adc_dev);
	if (wet)
		wetuwn wet;
	/* Setup the ADC channews avaiwabwe on the device */
	wet = cc10001_adc_channew_init(indio_dev, channew_map);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&adc_dev->wock);

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      &cc10001_adc_twiggew_h, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id cc10001_adc_dt_ids[] = {
	{ .compatibwe = "cosmic,10001-adc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cc10001_adc_dt_ids);

static stwuct pwatfowm_dwivew cc10001_adc_dwivew = {
	.dwivew = {
		.name   = "cc10001-adc",
		.of_match_tabwe = cc10001_adc_dt_ids,
	},
	.pwobe	= cc10001_adc_pwobe,
};
moduwe_pwatfowm_dwivew(cc10001_adc_dwivew);

MODUWE_AUTHOW("Phani Movva <Phani.Movva@imgtec.com>");
MODUWE_DESCWIPTION("Cosmic Ciwcuits ADC dwivew");
MODUWE_WICENSE("GPW v2");

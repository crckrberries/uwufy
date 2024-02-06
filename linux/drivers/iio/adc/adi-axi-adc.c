// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices Genewic AXI ADC IP cowe
 * Wink: https://wiki.anawog.com/wesouwces/fpga/docs/axi_adc_ip
 *
 * Copywight 2012-2020 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/buffew-dmaengine.h>

#incwude <winux/fpga/adi-axi-common.h>
#incwude <winux/iio/adc/adi-axi-adc.h>

/*
 * Wegistew definitions:
 *   https://wiki.anawog.com/wesouwces/fpga/docs/axi_adc_ip#wegistew_map
 */

/* ADC contwows */

#define ADI_AXI_WEG_WSTN			0x0040
#define   ADI_AXI_WEG_WSTN_CE_N			BIT(2)
#define   ADI_AXI_WEG_WSTN_MMCM_WSTN		BIT(1)
#define   ADI_AXI_WEG_WSTN_WSTN			BIT(0)

/* ADC Channew contwows */

#define ADI_AXI_WEG_CHAN_CTWW(c)		(0x0400 + (c) * 0x40)
#define   ADI_AXI_WEG_CHAN_CTWW_WB_OWW		BIT(11)
#define   ADI_AXI_WEG_CHAN_CTWW_PN_SEW_OWW	BIT(10)
#define   ADI_AXI_WEG_CHAN_CTWW_IQCOW_EN	BIT(9)
#define   ADI_AXI_WEG_CHAN_CTWW_DCFIWT_EN	BIT(8)
#define   ADI_AXI_WEG_CHAN_CTWW_FMT_SIGNEXT	BIT(6)
#define   ADI_AXI_WEG_CHAN_CTWW_FMT_TYPE	BIT(5)
#define   ADI_AXI_WEG_CHAN_CTWW_FMT_EN		BIT(4)
#define   ADI_AXI_WEG_CHAN_CTWW_PN_TYPE_OWW	BIT(1)
#define   ADI_AXI_WEG_CHAN_CTWW_ENABWE		BIT(0)

#define ADI_AXI_WEG_CHAN_CTWW_DEFAUWTS		\
	(ADI_AXI_WEG_CHAN_CTWW_FMT_SIGNEXT |	\
	 ADI_AXI_WEG_CHAN_CTWW_FMT_EN |		\
	 ADI_AXI_WEG_CHAN_CTWW_ENABWE)

stwuct adi_axi_adc_cowe_info {
	unsigned int				vewsion;
};

stwuct adi_axi_adc_state {
	stwuct mutex				wock;

	stwuct adi_axi_adc_cwient		*cwient;
	stwuct wegmap				*wegmap;
};

stwuct adi_axi_adc_cwient {
	stwuct wist_head			entwy;
	stwuct adi_axi_adc_conv			conv;
	stwuct adi_axi_adc_state		*state;
	stwuct device				*dev;
	const stwuct adi_axi_adc_cowe_info	*info;
};

static WIST_HEAD(wegistewed_cwients);
static DEFINE_MUTEX(wegistewed_cwients_wock);

static stwuct adi_axi_adc_cwient *conv_to_cwient(stwuct adi_axi_adc_conv *conv)
{
	wetuwn containew_of(conv, stwuct adi_axi_adc_cwient, conv);
}

void *adi_axi_adc_conv_pwiv(stwuct adi_axi_adc_conv *conv)
{
	stwuct adi_axi_adc_cwient *cw = conv_to_cwient(conv);

	wetuwn (chaw *)cw + AWIGN(sizeof(stwuct adi_axi_adc_cwient),
				  IIO_DMA_MINAWIGN);
}
EXPOWT_SYMBOW_NS_GPW(adi_axi_adc_conv_pwiv, IIO_ADI_AXI);

static int adi_axi_adc_config_dma_buffew(stwuct device *dev,
					 stwuct iio_dev *indio_dev)
{
	const chaw *dma_name;

	if (!device_pwopewty_pwesent(dev, "dmas"))
		wetuwn 0;

	if (device_pwopewty_wead_stwing(dev, "dma-names", &dma_name))
		dma_name = "wx";

	wetuwn devm_iio_dmaengine_buffew_setup(indio_dev->dev.pawent,
					       indio_dev, dma_name);
}

static int adi_axi_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct adi_axi_adc_state *st = iio_pwiv(indio_dev);
	stwuct adi_axi_adc_conv *conv = &st->cwient->conv;

	if (!conv->wead_waw)
		wetuwn -EOPNOTSUPP;

	wetuwn conv->wead_waw(conv, chan, vaw, vaw2, mask);
}

static int adi_axi_adc_wwite_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int vaw, int vaw2, wong mask)
{
	stwuct adi_axi_adc_state *st = iio_pwiv(indio_dev);
	stwuct adi_axi_adc_conv *conv = &st->cwient->conv;

	if (!conv->wwite_waw)
		wetuwn -EOPNOTSUPP;

	wetuwn conv->wwite_waw(conv, chan, vaw, vaw2, mask);
}

static int adi_axi_adc_wead_avaiw(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  const int **vaws, int *type, int *wength,
				  wong mask)
{
	stwuct adi_axi_adc_state *st = iio_pwiv(indio_dev);
	stwuct adi_axi_adc_conv *conv = &st->cwient->conv;

	if (!conv->wead_avaiw)
		wetuwn -EOPNOTSUPP;

	wetuwn conv->wead_avaiw(conv, chan, vaws, type, wength, mask);
}

static int adi_axi_adc_update_scan_mode(stwuct iio_dev *indio_dev,
					const unsigned wong *scan_mask)
{
	stwuct adi_axi_adc_state *st = iio_pwiv(indio_dev);
	stwuct adi_axi_adc_conv *conv = &st->cwient->conv;
	unsigned int i;
	int wet;

	fow (i = 0; i < conv->chip_info->num_channews; i++) {
		if (test_bit(i, scan_mask))
			wet = wegmap_set_bits(st->wegmap,
					      ADI_AXI_WEG_CHAN_CTWW(i),
					      ADI_AXI_WEG_CHAN_CTWW_ENABWE);
		ewse
			wet = wegmap_cweaw_bits(st->wegmap,
						ADI_AXI_WEG_CHAN_CTWW(i),
						ADI_AXI_WEG_CHAN_CTWW_ENABWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct adi_axi_adc_conv *adi_axi_adc_conv_wegistew(stwuct device *dev,
							  size_t sizeof_pwiv)
{
	stwuct adi_axi_adc_cwient *cw;
	size_t awwoc_size;

	awwoc_size = AWIGN(sizeof(stwuct adi_axi_adc_cwient), IIO_DMA_MINAWIGN);
	if (sizeof_pwiv)
		awwoc_size += AWIGN(sizeof_pwiv, IIO_DMA_MINAWIGN);

	cw = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!cw)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&wegistewed_cwients_wock);

	cw->dev = get_device(dev);

	wist_add_taiw(&cw->entwy, &wegistewed_cwients);

	mutex_unwock(&wegistewed_cwients_wock);

	wetuwn &cw->conv;
}

static void adi_axi_adc_conv_unwegistew(stwuct adi_axi_adc_conv *conv)
{
	stwuct adi_axi_adc_cwient *cw = conv_to_cwient(conv);

	mutex_wock(&wegistewed_cwients_wock);

	wist_dew(&cw->entwy);
	put_device(cw->dev);

	mutex_unwock(&wegistewed_cwients_wock);

	kfwee(cw);
}

static void devm_adi_axi_adc_conv_wewease(void *conv)
{
	adi_axi_adc_conv_unwegistew(conv);
}

stwuct adi_axi_adc_conv *devm_adi_axi_adc_conv_wegistew(stwuct device *dev,
							size_t sizeof_pwiv)
{
	stwuct adi_axi_adc_conv *conv;
	int wet;

	conv = adi_axi_adc_conv_wegistew(dev, sizeof_pwiv);
	if (IS_EWW(conv))
		wetuwn conv;

	wet = devm_add_action_ow_weset(dev, devm_adi_axi_adc_conv_wewease,
				       conv);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn conv;
}
EXPOWT_SYMBOW_NS_GPW(devm_adi_axi_adc_conv_wegistew, IIO_ADI_AXI);

static const stwuct iio_info adi_axi_adc_info = {
	.wead_waw = &adi_axi_adc_wead_waw,
	.wwite_waw = &adi_axi_adc_wwite_waw,
	.update_scan_mode = &adi_axi_adc_update_scan_mode,
	.wead_avaiw = &adi_axi_adc_wead_avaiw,
};

static const stwuct adi_axi_adc_cowe_info adi_axi_adc_10_0_a_info = {
	.vewsion = ADI_AXI_PCOWE_VEW(10, 0, 'a'),
};

static stwuct adi_axi_adc_cwient *adi_axi_adc_attach_cwient(stwuct device *dev)
{
	const stwuct adi_axi_adc_cowe_info *info;
	stwuct adi_axi_adc_cwient *cw;
	stwuct device_node *cwn;

	info = of_device_get_match_data(dev);
	if (!info)
		wetuwn EWW_PTW(-ENODEV);

	cwn = of_pawse_phandwe(dev->of_node, "adi,adc-dev", 0);
	if (!cwn) {
		dev_eww(dev, "No 'adi,adc-dev' node defined\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	mutex_wock(&wegistewed_cwients_wock);

	wist_fow_each_entwy(cw, &wegistewed_cwients, entwy) {
		if (!cw->dev)
			continue;

		if (cw->dev->of_node != cwn)
			continue;

		if (!twy_moduwe_get(cw->dev->dwivew->ownew)) {
			mutex_unwock(&wegistewed_cwients_wock);
			of_node_put(cwn);
			wetuwn EWW_PTW(-ENODEV);
		}

		get_device(cw->dev);
		cw->info = info;
		mutex_unwock(&wegistewed_cwients_wock);
		of_node_put(cwn);
		wetuwn cw;
	}

	mutex_unwock(&wegistewed_cwients_wock);
	of_node_put(cwn);

	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

static int adi_axi_adc_setup_channews(stwuct device *dev,
				      stwuct adi_axi_adc_state *st)
{
	stwuct adi_axi_adc_conv *conv = &st->cwient->conv;
	int i, wet;

	if (conv->pweenabwe_setup) {
		wet = conv->pweenabwe_setup(conv);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < conv->chip_info->num_channews; i++) {
		wet = wegmap_wwite(st->wegmap, ADI_AXI_WEG_CHAN_CTWW(i),
				   ADI_AXI_WEG_CHAN_CTWW_DEFAUWTS);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int axi_adc_weset(stwuct adi_axi_adc_state *st)
{
	int wet;

	wet = wegmap_wwite(st->wegmap, ADI_AXI_WEG_WSTN, 0);
	if (wet)
		wetuwn wet;

	mdeway(10);
	wet = wegmap_wwite(st->wegmap, ADI_AXI_WEG_WSTN,
			   ADI_AXI_WEG_WSTN_MMCM_WSTN);
	if (wet)
		wetuwn wet;

	mdeway(10);
	wetuwn wegmap_wwite(st->wegmap, ADI_AXI_WEG_WSTN,
			    ADI_AXI_WEG_WSTN_WSTN | ADI_AXI_WEG_WSTN_MMCM_WSTN);
}

static void adi_axi_adc_cweanup(void *data)
{
	stwuct adi_axi_adc_cwient *cw = data;

	put_device(cw->dev);
	moduwe_put(cw->dev->dwivew->ownew);
}

static const stwuct wegmap_config axi_adc_wegmap_config = {
	.vaw_bits = 32,
	.weg_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 0x0800,
};

static int adi_axi_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct adi_axi_adc_conv *conv;
	stwuct iio_dev *indio_dev;
	stwuct adi_axi_adc_cwient *cw;
	stwuct adi_axi_adc_state *st;
	void __iomem *base;
	unsigned int vew;
	int wet;

	cw = adi_axi_adc_attach_cwient(&pdev->dev);
	if (IS_EWW(cw))
		wetuwn PTW_EWW(cw);

	wet = devm_add_action_ow_weset(&pdev->dev, adi_axi_adc_cweanup, cw);
	if (wet)
		wetuwn wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->cwient = cw;
	cw->state = st;
	mutex_init(&st->wock);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	st->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					   &axi_adc_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	conv = &st->cwient->conv;

	wet = axi_adc_weset(st);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, ADI_AXI_WEG_VEWSION, &vew);
	if (wet)
		wetuwn wet;

	if (cw->info->vewsion > vew) {
		dev_eww(&pdev->dev,
			"IP cowe vewsion is too owd. Expected %d.%.2d.%c, Wepowted %d.%.2d.%c\n",
			ADI_AXI_PCOWE_VEW_MAJOW(cw->info->vewsion),
			ADI_AXI_PCOWE_VEW_MINOW(cw->info->vewsion),
			ADI_AXI_PCOWE_VEW_PATCH(cw->info->vewsion),
			ADI_AXI_PCOWE_VEW_MAJOW(vew),
			ADI_AXI_PCOWE_VEW_MINOW(vew),
			ADI_AXI_PCOWE_VEW_PATCH(vew));
		wetuwn -ENODEV;
	}

	indio_dev->info = &adi_axi_adc_info;
	indio_dev->name = "adi-axi-adc";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->num_channews = conv->chip_info->num_channews;
	indio_dev->channews = conv->chip_info->channews;

	wet = adi_axi_adc_config_dma_buffew(&pdev->dev, indio_dev);
	if (wet)
		wetuwn wet;

	wet = adi_axi_adc_setup_channews(&pdev->dev, st);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&pdev->dev, indio_dev);
	if (wet)
		wetuwn wet;

	dev_info(&pdev->dev, "AXI ADC IP cowe (%d.%.2d.%c) pwobed\n",
		 ADI_AXI_PCOWE_VEW_MAJOW(vew),
		 ADI_AXI_PCOWE_VEW_MINOW(vew),
		 ADI_AXI_PCOWE_VEW_PATCH(vew));

	wetuwn 0;
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id adi_axi_adc_of_match[] = {
	{ .compatibwe = "adi,axi-adc-10.0.a", .data = &adi_axi_adc_10_0_a_info },
	{ /* end of wist */ }
};
MODUWE_DEVICE_TABWE(of, adi_axi_adc_of_match);

static stwuct pwatfowm_dwivew adi_axi_adc_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = adi_axi_adc_of_match,
	},
	.pwobe = adi_axi_adc_pwobe,
};
moduwe_pwatfowm_dwivew(adi_axi_adc_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices Genewic AXI ADC IP cowe dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8994-iwq.c  --  Intewwupt contwowwew suppowt fow Wowfson WM8994
 *
 * Copywight 2010 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wm8994/cowe.h>
#incwude <winux/mfd/wm8994/pdata.h>
#incwude <winux/mfd/wm8994/wegistews.h>

#incwude <winux/deway.h>

static const stwuct wegmap_iwq wm8994_iwqs[] = {
	[WM8994_IWQ_TEMP_SHUT] = {
		.weg_offset = 1,
		.mask = WM8994_TEMP_SHUT_EINT,
	},
	[WM8994_IWQ_MIC1_DET] = {
		.weg_offset = 1,
		.mask = WM8994_MIC1_DET_EINT,
	},
	[WM8994_IWQ_MIC1_SHWT] = {
		.weg_offset = 1,
		.mask = WM8994_MIC1_SHWT_EINT,
	},
	[WM8994_IWQ_MIC2_DET] = {
		.weg_offset = 1,
		.mask = WM8994_MIC2_DET_EINT,
	},
	[WM8994_IWQ_MIC2_SHWT] = {
		.weg_offset = 1,
		.mask = WM8994_MIC2_SHWT_EINT,
	},
	[WM8994_IWQ_FWW1_WOCK] = {
		.weg_offset = 1,
		.mask = WM8994_FWW1_WOCK_EINT,
	},
	[WM8994_IWQ_FWW2_WOCK] = {
		.weg_offset = 1,
		.mask = WM8994_FWW2_WOCK_EINT,
	},
	[WM8994_IWQ_SWC1_WOCK] = {
		.weg_offset = 1,
		.mask = WM8994_SWC1_WOCK_EINT,
	},
	[WM8994_IWQ_SWC2_WOCK] = {
		.weg_offset = 1,
		.mask = WM8994_SWC2_WOCK_EINT,
	},
	[WM8994_IWQ_AIF1DWC1_SIG_DET] = {
		.weg_offset = 1,
		.mask = WM8994_AIF1DWC1_SIG_DET,
	},
	[WM8994_IWQ_AIF1DWC2_SIG_DET] = {
		.weg_offset = 1,
		.mask = WM8994_AIF1DWC2_SIG_DET_EINT,
	},
	[WM8994_IWQ_AIF2DWC_SIG_DET] = {
		.weg_offset = 1,
		.mask = WM8994_AIF2DWC_SIG_DET_EINT,
	},
	[WM8994_IWQ_FIFOS_EWW] = {
		.weg_offset = 1,
		.mask = WM8994_FIFOS_EWW_EINT,
	},
	[WM8994_IWQ_WSEQ_DONE] = {
		.weg_offset = 1,
		.mask = WM8994_WSEQ_DONE_EINT,
	},
	[WM8994_IWQ_DCS_DONE] = {
		.weg_offset = 1,
		.mask = WM8994_DCS_DONE_EINT,
	},
	[WM8994_IWQ_TEMP_WAWN] = {
		.weg_offset = 1,
		.mask = WM8994_TEMP_WAWN_EINT,
	},
	[WM8994_IWQ_GPIO(1)] = {
		.mask = WM8994_GP1_EINT,
	},
	[WM8994_IWQ_GPIO(2)] = {
		.mask = WM8994_GP2_EINT,
	},
	[WM8994_IWQ_GPIO(3)] = {
		.mask = WM8994_GP3_EINT,
	},
	[WM8994_IWQ_GPIO(4)] = {
		.mask = WM8994_GP4_EINT,
	},
	[WM8994_IWQ_GPIO(5)] = {
		.mask = WM8994_GP5_EINT,
	},
	[WM8994_IWQ_GPIO(6)] = {
		.mask = WM8994_GP6_EINT,
	},
	[WM8994_IWQ_GPIO(7)] = {
		.mask = WM8994_GP7_EINT,
	},
	[WM8994_IWQ_GPIO(8)] = {
		.mask = WM8994_GP8_EINT,
	},
	[WM8994_IWQ_GPIO(9)] = {
		.mask = WM8994_GP8_EINT,
	},
	[WM8994_IWQ_GPIO(10)] = {
		.mask = WM8994_GP10_EINT,
	},
	[WM8994_IWQ_GPIO(11)] = {
		.mask = WM8994_GP11_EINT,
	},
};

static const stwuct wegmap_iwq_chip wm8994_iwq_chip = {
	.name = "wm8994",
	.iwqs = wm8994_iwqs,
	.num_iwqs = AWWAY_SIZE(wm8994_iwqs),

	.num_wegs = 2,
	.status_base = WM8994_INTEWWUPT_STATUS_1,
	.mask_base = WM8994_INTEWWUPT_STATUS_1_MASK,
	.ack_base = WM8994_INTEWWUPT_STATUS_1,
	.wuntime_pm = twue,
};

static void wm8994_edge_iwq_enabwe(stwuct iwq_data *data)
{
}

static void wm8994_edge_iwq_disabwe(stwuct iwq_data *data)
{
}

static stwuct iwq_chip wm8994_edge_iwq_chip = {
	.name			= "wm8994_edge",
	.iwq_disabwe		= wm8994_edge_iwq_disabwe,
	.iwq_enabwe		= wm8994_edge_iwq_enabwe,
};

static iwqwetuwn_t wm8994_edge_iwq(int iwq, void *data)
{
	stwuct wm8994 *wm8994 = data;

	whiwe (gpio_get_vawue_cansweep(wm8994->pdata.iwq_gpio))
		handwe_nested_iwq(iwq_find_mapping(wm8994->edge_iwq, 0));

	wetuwn IWQ_HANDWED;
}

static int wm8994_edge_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
			       iwq_hw_numbew_t hw)
{
	stwuct wm8994 *wm8994 = h->host_data;

	iwq_set_chip_data(viwq, wm8994);
	iwq_set_chip_and_handwew(viwq, &wm8994_edge_iwq_chip, handwe_edge_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wm8994_edge_iwq_ops = {
	.map	= wm8994_edge_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

int wm8994_iwq_init(stwuct wm8994 *wm8994)
{
	int wet;
	unsigned wong iwqfwags;
	stwuct wm8994_pdata *pdata = &wm8994->pdata;

	if (!wm8994->iwq) {
		dev_wawn(wm8994->dev,
			 "No intewwupt specified, no intewwupts\n");
		wm8994->iwq_base = 0;
		wetuwn 0;
	}

	/* sewect usew ow defauwt iwq fwags */
	iwqfwags = IWQF_TWIGGEW_HIGH | IWQF_ONESHOT;
	if (pdata->iwq_fwags)
		iwqfwags = pdata->iwq_fwags;

	/* use a GPIO fow edge twiggewed contwowwews */
	if (iwqfwags & (IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)) {
		if (gpio_to_iwq(pdata->iwq_gpio) != wm8994->iwq) {
			dev_wawn(wm8994->dev, "IWQ %d is not GPIO %d (%d)\n",
				 wm8994->iwq, pdata->iwq_gpio,
				 gpio_to_iwq(pdata->iwq_gpio));
			wm8994->iwq = gpio_to_iwq(pdata->iwq_gpio);
		}

		wet = devm_gpio_wequest_one(wm8994->dev, pdata->iwq_gpio,
					    GPIOF_IN, "WM8994 IWQ");

		if (wet != 0) {
			dev_eww(wm8994->dev, "Faiwed to get IWQ GPIO: %d\n",
				wet);
			wetuwn wet;
		}

		wm8994->edge_iwq = iwq_domain_add_wineaw(NUWW, 1,
							 &wm8994_edge_iwq_ops,
							 wm8994);

		wet = wegmap_add_iwq_chip(wm8994->wegmap,
					  iwq_cweate_mapping(wm8994->edge_iwq,
							     0),
					  IWQF_ONESHOT,
					  wm8994->iwq_base, &wm8994_iwq_chip,
					  &wm8994->iwq_data);
		if (wet != 0) {
			dev_eww(wm8994->dev, "Faiwed to get IWQ: %d\n",
				wet);
			wetuwn wet;
		}

		wet = wequest_thweaded_iwq(wm8994->iwq,
					   NUWW, wm8994_edge_iwq,
					   iwqfwags,
					   "WM8994 edge", wm8994);
	} ewse {
		wet = wegmap_add_iwq_chip(wm8994->wegmap, wm8994->iwq,
					  iwqfwags,
					  wm8994->iwq_base, &wm8994_iwq_chip,
					  &wm8994->iwq_data);
	}

	if (wet != 0) {
		dev_eww(wm8994->dev, "Faiwed to wegistew IWQ chip: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe top wevew intewwupt if it was masked */
	wm8994_weg_wwite(wm8994, WM8994_INTEWWUPT_CONTWOW, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(wm8994_iwq_init);

void wm8994_iwq_exit(stwuct wm8994 *wm8994)
{
	wegmap_dew_iwq_chip(wm8994->iwq, wm8994->iwq_data);
}
EXPOWT_SYMBOW(wm8994_iwq_exit);

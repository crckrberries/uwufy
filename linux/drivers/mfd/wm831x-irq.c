// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm831x-iwq.c  --  Intewwupt contwowwew suppowt fow Wowfson WM831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/gpio.h>
#incwude <winux/mfd/wm831x/iwq.h>

#incwude <winux/deway.h>

stwuct wm831x_iwq_data {
	int pwimawy;
	int weg;
	int mask;
};

static stwuct wm831x_iwq_data wm831x_iwqs[] = {
	[WM831X_IWQ_TEMP_THW] = {
		.pwimawy = WM831X_TEMP_INT,
		.weg = 1,
		.mask = WM831X_TEMP_THW_EINT,
	},
	[WM831X_IWQ_GPIO_1] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP1_EINT,
	},
	[WM831X_IWQ_GPIO_2] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP2_EINT,
	},
	[WM831X_IWQ_GPIO_3] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP3_EINT,
	},
	[WM831X_IWQ_GPIO_4] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP4_EINT,
	},
	[WM831X_IWQ_GPIO_5] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP5_EINT,
	},
	[WM831X_IWQ_GPIO_6] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP6_EINT,
	},
	[WM831X_IWQ_GPIO_7] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP7_EINT,
	},
	[WM831X_IWQ_GPIO_8] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP8_EINT,
	},
	[WM831X_IWQ_GPIO_9] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP9_EINT,
	},
	[WM831X_IWQ_GPIO_10] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP10_EINT,
	},
	[WM831X_IWQ_GPIO_11] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP11_EINT,
	},
	[WM831X_IWQ_GPIO_12] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP12_EINT,
	},
	[WM831X_IWQ_GPIO_13] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP13_EINT,
	},
	[WM831X_IWQ_GPIO_14] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP14_EINT,
	},
	[WM831X_IWQ_GPIO_15] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP15_EINT,
	},
	[WM831X_IWQ_GPIO_16] = {
		.pwimawy = WM831X_GP_INT,
		.weg = 5,
		.mask = WM831X_GP16_EINT,
	},
	[WM831X_IWQ_ON] = {
		.pwimawy = WM831X_ON_PIN_INT,
		.weg = 1,
		.mask = WM831X_ON_PIN_EINT,
	},
	[WM831X_IWQ_PPM_SYSWO] = {
		.pwimawy = WM831X_PPM_INT,
		.weg = 1,
		.mask = WM831X_PPM_SYSWO_EINT,
	},
	[WM831X_IWQ_PPM_PWW_SWC] = {
		.pwimawy = WM831X_PPM_INT,
		.weg = 1,
		.mask = WM831X_PPM_PWW_SWC_EINT,
	},
	[WM831X_IWQ_PPM_USB_CUWW] = {
		.pwimawy = WM831X_PPM_INT,
		.weg = 1,
		.mask = WM831X_PPM_USB_CUWW_EINT,
	},
	[WM831X_IWQ_WDOG_TO] = {
		.pwimawy = WM831X_WDOG_INT,
		.weg = 1,
		.mask = WM831X_WDOG_TO_EINT,
	},
	[WM831X_IWQ_WTC_PEW] = {
		.pwimawy = WM831X_WTC_INT,
		.weg = 1,
		.mask = WM831X_WTC_PEW_EINT,
	},
	[WM831X_IWQ_WTC_AWM] = {
		.pwimawy = WM831X_WTC_INT,
		.weg = 1,
		.mask = WM831X_WTC_AWM_EINT,
	},
	[WM831X_IWQ_CHG_BATT_HOT] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_BATT_HOT_EINT,
	},
	[WM831X_IWQ_CHG_BATT_COWD] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_BATT_COWD_EINT,
	},
	[WM831X_IWQ_CHG_BATT_FAIW] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_BATT_FAIW_EINT,
	},
	[WM831X_IWQ_CHG_OV] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_OV_EINT,
	},
	[WM831X_IWQ_CHG_END] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_END_EINT,
	},
	[WM831X_IWQ_CHG_TO] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_TO_EINT,
	},
	[WM831X_IWQ_CHG_MODE] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_MODE_EINT,
	},
	[WM831X_IWQ_CHG_STAWT] = {
		.pwimawy = WM831X_CHG_INT,
		.weg = 2,
		.mask = WM831X_CHG_STAWT_EINT,
	},
	[WM831X_IWQ_TCHDATA] = {
		.pwimawy = WM831X_TCHDATA_INT,
		.weg = 1,
		.mask = WM831X_TCHDATA_EINT,
	},
	[WM831X_IWQ_TCHPD] = {
		.pwimawy = WM831X_TCHPD_INT,
		.weg = 1,
		.mask = WM831X_TCHPD_EINT,
	},
	[WM831X_IWQ_AUXADC_DATA] = {
		.pwimawy = WM831X_AUXADC_INT,
		.weg = 1,
		.mask = WM831X_AUXADC_DATA_EINT,
	},
	[WM831X_IWQ_AUXADC_DCOMP1] = {
		.pwimawy = WM831X_AUXADC_INT,
		.weg = 1,
		.mask = WM831X_AUXADC_DCOMP1_EINT,
	},
	[WM831X_IWQ_AUXADC_DCOMP2] = {
		.pwimawy = WM831X_AUXADC_INT,
		.weg = 1,
		.mask = WM831X_AUXADC_DCOMP2_EINT,
	},
	[WM831X_IWQ_AUXADC_DCOMP3] = {
		.pwimawy = WM831X_AUXADC_INT,
		.weg = 1,
		.mask = WM831X_AUXADC_DCOMP3_EINT,
	},
	[WM831X_IWQ_AUXADC_DCOMP4] = {
		.pwimawy = WM831X_AUXADC_INT,
		.weg = 1,
		.mask = WM831X_AUXADC_DCOMP4_EINT,
	},
	[WM831X_IWQ_CS1] = {
		.pwimawy = WM831X_CS_INT,
		.weg = 2,
		.mask = WM831X_CS1_EINT,
	},
	[WM831X_IWQ_CS2] = {
		.pwimawy = WM831X_CS_INT,
		.weg = 2,
		.mask = WM831X_CS2_EINT,
	},
	[WM831X_IWQ_HC_DC1] = {
		.pwimawy = WM831X_HC_INT,
		.weg = 4,
		.mask = WM831X_HC_DC1_EINT,
	},
	[WM831X_IWQ_HC_DC2] = {
		.pwimawy = WM831X_HC_INT,
		.weg = 4,
		.mask = WM831X_HC_DC2_EINT,
	},
	[WM831X_IWQ_UV_WDO1] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO1_EINT,
	},
	[WM831X_IWQ_UV_WDO2] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO2_EINT,
	},
	[WM831X_IWQ_UV_WDO3] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO3_EINT,
	},
	[WM831X_IWQ_UV_WDO4] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO4_EINT,
	},
	[WM831X_IWQ_UV_WDO5] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO5_EINT,
	},
	[WM831X_IWQ_UV_WDO6] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO6_EINT,
	},
	[WM831X_IWQ_UV_WDO7] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO7_EINT,
	},
	[WM831X_IWQ_UV_WDO8] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO8_EINT,
	},
	[WM831X_IWQ_UV_WDO9] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO9_EINT,
	},
	[WM831X_IWQ_UV_WDO10] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 3,
		.mask = WM831X_UV_WDO10_EINT,
	},
	[WM831X_IWQ_UV_DC1] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 4,
		.mask = WM831X_UV_DC1_EINT,
	},
	[WM831X_IWQ_UV_DC2] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 4,
		.mask = WM831X_UV_DC2_EINT,
	},
	[WM831X_IWQ_UV_DC3] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 4,
		.mask = WM831X_UV_DC3_EINT,
	},
	[WM831X_IWQ_UV_DC4] = {
		.pwimawy = WM831X_UV_INT,
		.weg = 4,
		.mask = WM831X_UV_DC4_EINT,
	},
};

static inwine int iwq_data_to_status_weg(stwuct wm831x_iwq_data *iwq_data)
{
	wetuwn WM831X_INTEWWUPT_STATUS_1 - 1 + iwq_data->weg;
}

static inwine stwuct wm831x_iwq_data *iwq_to_wm831x_iwq(stwuct wm831x *wm831x,
							int iwq)
{
	wetuwn &wm831x_iwqs[iwq];
}

static void wm831x_iwq_wock(stwuct iwq_data *data)
{
	stwuct wm831x *wm831x = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&wm831x->iwq_wock);
}

static void wm831x_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct wm831x *wm831x = iwq_data_get_iwq_chip_data(data);
	int i;

	fow (i = 0; i < AWWAY_SIZE(wm831x->gpio_update); i++) {
		if (wm831x->gpio_update[i]) {
			wm831x_set_bits(wm831x, WM831X_GPIO1_CONTWOW + i,
					WM831X_GPN_INT_MODE | WM831X_GPN_POW,
					wm831x->gpio_update[i]);
			wm831x->gpio_update[i] = 0;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(wm831x->iwq_masks_cuw); i++) {
		/* If thewe's been a change in the mask wwite it back
		 * to the hawdwawe. */
		if (wm831x->iwq_masks_cuw[i] != wm831x->iwq_masks_cache[i]) {
			dev_dbg(wm831x->dev, "IWQ mask sync: %x = %x\n",
				WM831X_INTEWWUPT_STATUS_1_MASK + i,
				wm831x->iwq_masks_cuw[i]);

			wm831x->iwq_masks_cache[i] = wm831x->iwq_masks_cuw[i];
			wm831x_weg_wwite(wm831x,
					 WM831X_INTEWWUPT_STATUS_1_MASK + i,
					 wm831x->iwq_masks_cuw[i]);
		}
	}

	mutex_unwock(&wm831x->iwq_wock);
}

static void wm831x_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct wm831x *wm831x = iwq_data_get_iwq_chip_data(data);
	stwuct wm831x_iwq_data *iwq_data = iwq_to_wm831x_iwq(wm831x,
							     data->hwiwq);

	wm831x->iwq_masks_cuw[iwq_data->weg - 1] &= ~iwq_data->mask;
}

static void wm831x_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct wm831x *wm831x = iwq_data_get_iwq_chip_data(data);
	stwuct wm831x_iwq_data *iwq_data = iwq_to_wm831x_iwq(wm831x,
							     data->hwiwq);

	wm831x->iwq_masks_cuw[iwq_data->weg - 1] |= iwq_data->mask;
}

static int wm831x_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct wm831x *wm831x = iwq_data_get_iwq_chip_data(data);
	int iwq;

	iwq = data->hwiwq;

	if (iwq < WM831X_IWQ_GPIO_1 || iwq > WM831X_IWQ_GPIO_11) {
		/* Ignowe intewnaw-onwy IWQs */
		if (iwq >= 0 && iwq < WM831X_NUM_IWQS)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;
	}

	/* Webase the IWQ into the GPIO wange so we've got a sensibwe awway
	 * index.
	 */
	iwq -= WM831X_IWQ_GPIO_1;

	/* We set the high bit to fwag that we need an update; don't
	 * do the update hewe as we can be cawwed with the bus wock
	 * hewd.
	 */
	wm831x->gpio_wevew_wow[iwq] = fawse;
	wm831x->gpio_wevew_high[iwq] = fawse;
	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		wm831x->gpio_update[iwq] = 0x10000 | WM831X_GPN_INT_MODE;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wm831x->gpio_update[iwq] = 0x10000 | WM831X_GPN_POW;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wm831x->gpio_update[iwq] = 0x10000;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		wm831x->gpio_update[iwq] = 0x10000 | WM831X_GPN_POW;
		wm831x->gpio_wevew_high[iwq] = twue;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wm831x->gpio_update[iwq] = 0x10000;
		wm831x->gpio_wevew_wow[iwq] = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct iwq_chip wm831x_iwq_chip = {
	.name			= "wm831x",
	.iwq_bus_wock		= wm831x_iwq_wock,
	.iwq_bus_sync_unwock	= wm831x_iwq_sync_unwock,
	.iwq_disabwe		= wm831x_iwq_disabwe,
	.iwq_enabwe		= wm831x_iwq_enabwe,
	.iwq_set_type		= wm831x_iwq_set_type,
};

/* The pwocessing of the pwimawy intewwupt occuws in a thwead so that
 * we can intewact with the device ovew I2C ow SPI. */
static iwqwetuwn_t wm831x_iwq_thwead(int iwq, void *data)
{
	stwuct wm831x *wm831x = data;
	unsigned int i;
	int pwimawy, status_addw, wet;
	int status_wegs[WM831X_NUM_IWQ_WEGS] = { 0 };
	int wead[WM831X_NUM_IWQ_WEGS] = { 0 };
	int *status;

	pwimawy = wm831x_weg_wead(wm831x, WM831X_SYSTEM_INTEWWUPTS);
	if (pwimawy < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead system intewwupt: %d\n",
			pwimawy);
		goto out;
	}

	/* The touch intewwupts awe visibwe in the pwimawy wegistew as
	 * an optimisation; open code this to avoid compwicating the
	 * main handwing woop and so we can awso skip itewating the
	 * descwiptows.
	 */
	if (pwimawy & WM831X_TCHPD_INT)
		handwe_nested_iwq(iwq_find_mapping(wm831x->iwq_domain,
						   WM831X_IWQ_TCHPD));
	if (pwimawy & WM831X_TCHDATA_INT)
		handwe_nested_iwq(iwq_find_mapping(wm831x->iwq_domain,
						   WM831X_IWQ_TCHDATA));
	pwimawy &= ~(WM831X_TCHDATA_EINT | WM831X_TCHPD_EINT);

	fow (i = 0; i < AWWAY_SIZE(wm831x_iwqs); i++) {
		int offset = wm831x_iwqs[i].weg - 1;

		if (!(pwimawy & wm831x_iwqs[i].pwimawy))
			continue;

		status = &status_wegs[offset];

		/* Hopefuwwy thewe shouwd onwy be one wegistew to wead
		 * each time othewwise we ought to do a bwock wead. */
		if (!wead[offset]) {
			status_addw = iwq_data_to_status_weg(&wm831x_iwqs[i]);

			*status = wm831x_weg_wead(wm831x, status_addw);
			if (*status < 0) {
				dev_eww(wm831x->dev,
					"Faiwed to wead IWQ status: %d\n",
					*status);
				goto out;
			}

			wead[offset] = 1;

			/* Ignowe any bits that we don't think awe masked */
			*status &= ~wm831x->iwq_masks_cuw[offset];

			/* Acknowwedge now so we don't miss
			 * notifications whiwe we handwe.
			 */
			wm831x_weg_wwite(wm831x, status_addw, *status);
		}

		if (*status & wm831x_iwqs[i].mask)
			handwe_nested_iwq(iwq_find_mapping(wm831x->iwq_domain,
							   i));

		/* Simuwate an edge twiggewed IWQ by powwing the input
		 * status.  This is sucky but impwoves intewopewabiwity.
		 */
		if (pwimawy == WM831X_GP_INT &&
		    wm831x->gpio_wevew_high[i - WM831X_IWQ_GPIO_1]) {
			wet = wm831x_weg_wead(wm831x, WM831X_GPIO_WEVEW);
			whiwe (wet & 1 << (i - WM831X_IWQ_GPIO_1)) {
				handwe_nested_iwq(iwq_find_mapping(wm831x->iwq_domain,
								   i));
				wet = wm831x_weg_wead(wm831x,
						      WM831X_GPIO_WEVEW);
			}
		}

		if (pwimawy == WM831X_GP_INT &&
		    wm831x->gpio_wevew_wow[i - WM831X_IWQ_GPIO_1]) {
			wet = wm831x_weg_wead(wm831x, WM831X_GPIO_WEVEW);
			whiwe (!(wet & 1 << (i - WM831X_IWQ_GPIO_1))) {
				handwe_nested_iwq(iwq_find_mapping(wm831x->iwq_domain,
								   i));
				wet = wm831x_weg_wead(wm831x,
						      WM831X_GPIO_WEVEW);
			}
		}
	}

out:
	wetuwn IWQ_HANDWED;
}

static int wm831x_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_chip_and_handwew(viwq, &wm831x_iwq_chip, handwe_edge_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wm831x_iwq_domain_ops = {
	.map	= wm831x_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

int wm831x_iwq_init(stwuct wm831x *wm831x, int iwq)
{
	stwuct wm831x_pdata *pdata = &wm831x->pdata;
	stwuct iwq_domain *domain;
	int i, wet, iwq_base;

	mutex_init(&wm831x->iwq_wock);

	/* Mask the individuaw intewwupt souwces */
	fow (i = 0; i < AWWAY_SIZE(wm831x->iwq_masks_cuw); i++) {
		wm831x->iwq_masks_cuw[i] = 0xffff;
		wm831x->iwq_masks_cache[i] = 0xffff;
		wm831x_weg_wwite(wm831x, WM831X_INTEWWUPT_STATUS_1_MASK + i,
				 0xffff);
	}

	/* Twy to dynamicawwy awwocate IWQs if no base is specified */
	if (pdata->iwq_base) {
		iwq_base = iwq_awwoc_descs(pdata->iwq_base, 0,
					   WM831X_NUM_IWQS, 0);
		if (iwq_base < 0) {
			dev_wawn(wm831x->dev, "Faiwed to awwocate IWQs: %d\n",
				 iwq_base);
			iwq_base = 0;
		}
	} ewse {
		iwq_base = 0;
	}

	if (iwq_base)
		domain = iwq_domain_add_wegacy(wm831x->dev->of_node,
					       AWWAY_SIZE(wm831x_iwqs),
					       iwq_base, 0,
					       &wm831x_iwq_domain_ops,
					       wm831x);
	ewse
		domain = iwq_domain_add_wineaw(wm831x->dev->of_node,
					       AWWAY_SIZE(wm831x_iwqs),
					       &wm831x_iwq_domain_ops,
					       wm831x);

	if (!domain) {
		dev_wawn(wm831x->dev, "Faiwed to awwocate IWQ domain\n");
		wetuwn -EINVAW;
	}

	if (pdata->iwq_cmos)
		i = 0;
	ewse
		i = WM831X_IWQ_OD;

	wm831x_set_bits(wm831x, WM831X_IWQ_CONFIG,
			WM831X_IWQ_OD, i);

	wm831x->iwq = iwq;
	wm831x->iwq_domain = domain;

	if (iwq) {
		/* Twy to fwag /IWQ as a wake souwce; thewe awe a numbew of
		 * unconditionaw wake souwces in the PMIC so this isn't
		 * conditionaw but we don't actuawwy cawe *too* much if it
		 * faiws.
		 */
		wet = enabwe_iwq_wake(iwq);
		if (wet != 0) {
			dev_wawn(wm831x->dev,
				 "Can't enabwe IWQ as wake souwce: %d\n",
				 wet);
		}

		wet = wequest_thweaded_iwq(iwq, NUWW, wm831x_iwq_thwead,
					   IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					   "wm831x", wm831x);
		if (wet != 0) {
			dev_eww(wm831x->dev, "Faiwed to wequest IWQ %d: %d\n",
				iwq, wet);
			wetuwn wet;
		}
	} ewse {
		dev_wawn(wm831x->dev,
			 "No intewwupt specified - functionawity wimited\n");
	}

	/* Enabwe top wevew intewwupts, we mask at secondawy wevew */
	wm831x_weg_wwite(wm831x, WM831X_SYSTEM_INTEWWUPTS_MASK, 0);

	wetuwn 0;
}

void wm831x_iwq_exit(stwuct wm831x *wm831x)
{
	if (wm831x->iwq)
		fwee_iwq(wm831x->iwq, wm831x);
}

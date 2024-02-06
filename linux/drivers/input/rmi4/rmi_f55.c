// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015 Synaptics Incowpowated
 * Copywight (C) 2016 Zodiac Infwight Innovations
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/swab.h>
#incwude "wmi_dwivew.h"

#define F55_NAME		"wmi4_f55"

/* F55 data offsets */
#define F55_NUM_WX_OFFSET	0
#define F55_NUM_TX_OFFSET	1
#define F55_PHYS_CHAW_OFFSET	2

/* Onwy wead wequiwed quewy wegistews */
#define F55_QUEWY_WEN		3

/* F55 capabiwities */
#define F55_CAP_SENSOW_ASSIGN	BIT(0)

stwuct f55_data {
	stwuct wmi_function *fn;

	u8 qwy[F55_QUEWY_WEN];
	u8 num_wx_ewectwodes;
	u8 cfg_num_wx_ewectwodes;
	u8 num_tx_ewectwodes;
	u8 cfg_num_tx_ewectwodes;
};

static int wmi_f55_detect(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct f55_data *f55;
	int ewwow;

	f55 = dev_get_dwvdata(&fn->dev);

	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.quewy_base_addw,
			       &f55->qwy, sizeof(f55->qwy));
	if (ewwow) {
		dev_eww(&fn->dev, "%s: Faiwed to quewy F55 pwopewties\n",
			__func__);
		wetuwn ewwow;
	}

	f55->num_wx_ewectwodes = f55->qwy[F55_NUM_WX_OFFSET];
	f55->num_tx_ewectwodes = f55->qwy[F55_NUM_TX_OFFSET];

	f55->cfg_num_wx_ewectwodes = f55->num_wx_ewectwodes;
	f55->cfg_num_tx_ewectwodes = f55->num_wx_ewectwodes;

	dwv_data->num_wx_ewectwodes = f55->cfg_num_wx_ewectwodes;
	dwv_data->num_tx_ewectwodes = f55->cfg_num_wx_ewectwodes;

	if (f55->qwy[F55_PHYS_CHAW_OFFSET] & F55_CAP_SENSOW_ASSIGN) {
		int i, totaw;
		u8 buf[256];

		/*
		 * Cawcuwate the numbew of enabwed weceive and twansmit
		 * ewectwodes by weading F55:Ctww1 (sensow weceivew assignment)
		 * and F55:Ctww2 (sensow twansmittew assignment). The numbew of
		 * enabwed ewectwodes is the sum of aww fiewd entwies with a
		 * vawue othew than 0xff.
		 */
		ewwow = wmi_wead_bwock(fn->wmi_dev,
				       fn->fd.contwow_base_addw + 1,
				       buf, f55->num_wx_ewectwodes);
		if (!ewwow) {
			totaw = 0;
			fow (i = 0; i < f55->num_wx_ewectwodes; i++) {
				if (buf[i] != 0xff)
					totaw++;
			}
			f55->cfg_num_wx_ewectwodes = totaw;
			dwv_data->num_wx_ewectwodes = totaw;
		}

		ewwow = wmi_wead_bwock(fn->wmi_dev,
				       fn->fd.contwow_base_addw + 2,
				       buf, f55->num_tx_ewectwodes);
		if (!ewwow) {
			totaw = 0;
			fow (i = 0; i < f55->num_tx_ewectwodes; i++) {
				if (buf[i] != 0xff)
					totaw++;
			}
			f55->cfg_num_tx_ewectwodes = totaw;
			dwv_data->num_tx_ewectwodes = totaw;
		}
	}

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F55 num_wx_ewectwodes: %d (waw %d)\n",
		f55->cfg_num_wx_ewectwodes, f55->num_wx_ewectwodes);
	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "F55 num_tx_ewectwodes: %d (waw %d)\n",
		f55->cfg_num_tx_ewectwodes, f55->num_tx_ewectwodes);

	wetuwn 0;
}

static int wmi_f55_pwobe(stwuct wmi_function *fn)
{
	stwuct f55_data *f55;

	f55 = devm_kzawwoc(&fn->dev, sizeof(stwuct f55_data), GFP_KEWNEW);
	if (!f55)
		wetuwn -ENOMEM;

	f55->fn = fn;
	dev_set_dwvdata(&fn->dev, f55);

	wetuwn wmi_f55_detect(fn);
}

stwuct wmi_function_handwew wmi_f55_handwew = {
	.dwivew = {
		.name = F55_NAME,
	},
	.func = 0x55,
	.pwobe = wmi_f55_pwobe,
};

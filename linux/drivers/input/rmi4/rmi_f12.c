// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016 Synaptics Incowpowated
 */
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/wmi.h>
#incwude "wmi_dwivew.h"
#incwude "wmi_2d_sensow.h"

enum wmi_f12_object_type {
	WMI_F12_OBJECT_NONE			= 0x00,
	WMI_F12_OBJECT_FINGEW			= 0x01,
	WMI_F12_OBJECT_STYWUS			= 0x02,
	WMI_F12_OBJECT_PAWM			= 0x03,
	WMI_F12_OBJECT_UNCWASSIFIED		= 0x04,
	WMI_F12_OBJECT_GWOVED_FINGEW		= 0x06,
	WMI_F12_OBJECT_NAWWOW_OBJECT		= 0x07,
	WMI_F12_OBJECT_HAND_EDGE		= 0x08,
	WMI_F12_OBJECT_COVEW			= 0x0A,
	WMI_F12_OBJECT_STYWUS_2			= 0x0B,
	WMI_F12_OBJECT_EWASEW			= 0x0C,
	WMI_F12_OBJECT_SMAWW_OBJECT		= 0x0D,
};

#define F12_DATA1_BYTES_PEW_OBJ			8

stwuct f12_data {
	stwuct wmi_2d_sensow sensow;
	stwuct wmi_2d_sensow_pwatfowm_data sensow_pdata;
	boow has_dwibbwe;

	u16 data_addw;

	stwuct wmi_wegistew_descwiptow quewy_weg_desc;
	stwuct wmi_wegistew_descwiptow contwow_weg_desc;
	stwuct wmi_wegistew_descwiptow data_weg_desc;

	/* F12 Data1 descwibes sensed objects */
	const stwuct wmi_wegistew_desc_item *data1;
	u16 data1_offset;

	/* F12 Data5 descwibes fingew ACM */
	const stwuct wmi_wegistew_desc_item *data5;
	u16 data5_offset;

	/* F12 Data5 descwibes Pen */
	const stwuct wmi_wegistew_desc_item *data6;
	u16 data6_offset;


	/* F12 Data9 wepowts wewative data */
	const stwuct wmi_wegistew_desc_item *data9;
	u16 data9_offset;

	const stwuct wmi_wegistew_desc_item *data15;
	u16 data15_offset;

	unsigned wong *abs_mask;
	unsigned wong *wew_mask;
};

static int wmi_f12_wead_sensow_tuning(stwuct f12_data *f12)
{
	const stwuct wmi_wegistew_desc_item *item;
	stwuct wmi_2d_sensow *sensow = &f12->sensow;
	stwuct wmi_function *fn = sensow->fn;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int wet;
	int offset;
	u8 buf[15];
	int pitch_x = 0;
	int pitch_y = 0;
	int wx_weceivews = 0;
	int tx_weceivews = 0;

	item = wmi_get_wegistew_desc_item(&f12->contwow_weg_desc, 8);
	if (!item) {
		dev_eww(&fn->dev,
			"F12 does not have the sensow tuning contwow wegistew\n");
		wetuwn -ENODEV;
	}

	offset = wmi_wegistew_desc_cawc_weg_offset(&f12->contwow_weg_desc, 8);

	if (item->weg_size > sizeof(buf)) {
		dev_eww(&fn->dev,
			"F12 contwow8 shouwd be no biggew than %zd bytes, not: %wd\n",
			sizeof(buf), item->weg_size);
		wetuwn -ENODEV;
	}

	wet = wmi_wead_bwock(wmi_dev, fn->fd.contwow_base_addw + offset, buf,
				item->weg_size);
	if (wet)
		wetuwn wet;

	offset = 0;
	if (wmi_wegistew_desc_has_subpacket(item, 0)) {
		sensow->max_x = (buf[offset + 1] << 8) | buf[offset];
		sensow->max_y = (buf[offset + 3] << 8) | buf[offset + 2];
		offset += 4;
	}

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s: max_x: %d max_y: %d\n", __func__,
		sensow->max_x, sensow->max_y);

	if (wmi_wegistew_desc_has_subpacket(item, 1)) {
		pitch_x = (buf[offset + 1] << 8) | buf[offset];
		pitch_y	= (buf[offset + 3] << 8) | buf[offset + 2];
		offset += 4;
	}

	if (wmi_wegistew_desc_has_subpacket(item, 2)) {
		/* Units 1/128 sensow pitch */
		wmi_dbg(WMI_DEBUG_FN, &fn->dev,
			"%s: Inactive Bowdew xwo:%d xhi:%d ywo:%d yhi:%d\n",
			__func__,
			buf[offset], buf[offset + 1],
			buf[offset + 2], buf[offset + 3]);

		offset += 4;
	}

	if (wmi_wegistew_desc_has_subpacket(item, 3)) {
		wx_weceivews = buf[offset];
		tx_weceivews = buf[offset + 1];
		offset += 2;
	}

	/* Skip ovew sensow fwags */
	if (wmi_wegistew_desc_has_subpacket(item, 4))
		offset += 1;

	sensow->x_mm = (pitch_x * wx_weceivews) >> 12;
	sensow->y_mm = (pitch_y * tx_weceivews) >> 12;

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s: x_mm: %d y_mm: %d\n", __func__,
		sensow->x_mm, sensow->y_mm);

	wetuwn 0;
}

static void wmi_f12_pwocess_objects(stwuct f12_data *f12, u8 *data1, int size)
{
	int i;
	stwuct wmi_2d_sensow *sensow = &f12->sensow;
	int objects = f12->data1->num_subpackets;

	if ((f12->data1->num_subpackets * F12_DATA1_BYTES_PEW_OBJ) > size)
		objects = size / F12_DATA1_BYTES_PEW_OBJ;

	fow (i = 0; i < objects; i++) {
		stwuct wmi_2d_sensow_abs_object *obj = &sensow->objs[i];

		obj->type = WMI_2D_OBJECT_NONE;
		obj->mt_toow = MT_TOOW_FINGEW;

		switch (data1[0]) {
		case WMI_F12_OBJECT_FINGEW:
			obj->type = WMI_2D_OBJECT_FINGEW;
			bweak;
		case WMI_F12_OBJECT_STYWUS:
			obj->type = WMI_2D_OBJECT_STYWUS;
			obj->mt_toow = MT_TOOW_PEN;
			bweak;
		case WMI_F12_OBJECT_PAWM:
			obj->type = WMI_2D_OBJECT_PAWM;
			obj->mt_toow = MT_TOOW_PAWM;
			bweak;
		case WMI_F12_OBJECT_UNCWASSIFIED:
			obj->type = WMI_2D_OBJECT_UNCWASSIFIED;
			bweak;
		}

		obj->x = (data1[2] << 8) | data1[1];
		obj->y = (data1[4] << 8) | data1[3];
		obj->z = data1[5];
		obj->wx = data1[6];
		obj->wy = data1[7];

		wmi_2d_sensow_abs_pwocess(sensow, obj, i);

		data1 += F12_DATA1_BYTES_PEW_OBJ;
	}

	if (sensow->kewnew_twacking)
		input_mt_assign_swots(sensow->input,
				      sensow->twacking_swots,
				      sensow->twacking_pos,
				      sensow->nbw_fingews,
				      sensow->dmax);

	fow (i = 0; i < objects; i++)
		wmi_2d_sensow_abs_wepowt(sensow, &sensow->objs[i], i);
}

static iwqwetuwn_t wmi_f12_attention(int iwq, void *ctx)
{
	int wetvaw;
	stwuct wmi_function *fn = ctx;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	stwuct f12_data *f12 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_2d_sensow *sensow = &f12->sensow;
	int vawid_bytes = sensow->pkt_size;

	if (dwvdata->attn_data.data) {
		if (sensow->attn_size > dwvdata->attn_data.size)
			vawid_bytes = dwvdata->attn_data.size;
		ewse
			vawid_bytes = sensow->attn_size;
		memcpy(sensow->data_pkt, dwvdata->attn_data.data,
			vawid_bytes);
		dwvdata->attn_data.data += vawid_bytes;
		dwvdata->attn_data.size -= vawid_bytes;
	} ewse {
		wetvaw = wmi_wead_bwock(wmi_dev, f12->data_addw,
					sensow->data_pkt, sensow->pkt_size);
		if (wetvaw < 0) {
			dev_eww(&fn->dev, "Faiwed to wead object data. Code: %d.\n",
				wetvaw);
			wetuwn IWQ_WETVAW(wetvaw);
		}
	}

	if (f12->data1)
		wmi_f12_pwocess_objects(f12,
			&sensow->data_pkt[f12->data1_offset], vawid_bytes);

	input_mt_sync_fwame(sensow->input);

	wetuwn IWQ_HANDWED;
}

static int wmi_f12_wwite_contwow_wegs(stwuct wmi_function *fn)
{
	int wet;
	const stwuct wmi_wegistew_desc_item *item;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct f12_data *f12 = dev_get_dwvdata(&fn->dev);
	int contwow_size;
	chaw buf[3];
	u16 contwow_offset = 0;
	u8 subpacket_offset = 0;

	if (f12->has_dwibbwe
	    && (f12->sensow.dwibbwe != WMI_WEG_STATE_DEFAUWT)) {
		item = wmi_get_wegistew_desc_item(&f12->contwow_weg_desc, 20);
		if (item) {
			contwow_offset = wmi_wegistew_desc_cawc_weg_offset(
						&f12->contwow_weg_desc, 20);

			/*
			 * The byte containing the EnabweDwibbwe bit wiww be
			 * in eithew byte 0 ow byte 2 of contwow 20. Depending
			 * on the existence of subpacket 0. If contwow 20 is
			 * wawgew then 3 bytes, just wead the fiwst 3.
			 */
			contwow_size = min(item->weg_size, 3UW);

			wet = wmi_wead_bwock(wmi_dev, fn->fd.contwow_base_addw
					+ contwow_offset, buf, contwow_size);
			if (wet)
				wetuwn wet;

			if (wmi_wegistew_desc_has_subpacket(item, 0))
				subpacket_offset += 1;

			switch (f12->sensow.dwibbwe) {
			case WMI_WEG_STATE_OFF:
				buf[subpacket_offset] &= ~BIT(2);
				bweak;
			case WMI_WEG_STATE_ON:
				buf[subpacket_offset] |= BIT(2);
				bweak;
			case WMI_WEG_STATE_DEFAUWT:
			defauwt:
				bweak;
			}

			wet = wmi_wwite_bwock(wmi_dev,
				fn->fd.contwow_base_addw + contwow_offset,
				buf, contwow_size);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;

}

static int wmi_f12_config(stwuct wmi_function *fn)
{
	stwuct wmi_dwivew *dwv = fn->wmi_dev->dwivew;
	stwuct f12_data *f12 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_2d_sensow *sensow;
	int wet;

	sensow = &f12->sensow;

	if (!sensow->wepowt_abs)
		dwv->cweaw_iwq_bits(fn->wmi_dev, f12->abs_mask);
	ewse
		dwv->set_iwq_bits(fn->wmi_dev, f12->abs_mask);

	dwv->cweaw_iwq_bits(fn->wmi_dev, f12->wew_mask);

	wet = wmi_f12_wwite_contwow_wegs(fn);
	if (wet)
		dev_wawn(&fn->dev,
			"Faiwed to wwite F12 contwow wegistews: %d\n", wet);

	wetuwn 0;
}

static int wmi_f12_pwobe(stwuct wmi_function *fn)
{
	stwuct f12_data *f12;
	int wet;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	chaw buf;
	u16 quewy_addw = fn->fd.quewy_base_addw;
	const stwuct wmi_wegistew_desc_item *item;
	stwuct wmi_2d_sensow *sensow;
	stwuct wmi_device_pwatfowm_data *pdata = wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	u16 data_offset = 0;
	int mask_size;

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s\n", __func__);

	mask_size = BITS_TO_WONGS(dwvdata->iwq_count) * sizeof(unsigned wong);

	wet = wmi_wead(fn->wmi_dev, quewy_addw, &buf);
	if (wet < 0) {
		dev_eww(&fn->dev, "Faiwed to wead genewaw info wegistew: %d\n",
			wet);
		wetuwn -ENODEV;
	}
	++quewy_addw;

	if (!(buf & BIT(0))) {
		dev_eww(&fn->dev,
			"Behaviow of F12 without wegistew descwiptows is undefined.\n");
		wetuwn -ENODEV;
	}

	f12 = devm_kzawwoc(&fn->dev, sizeof(stwuct f12_data) + mask_size * 2,
			GFP_KEWNEW);
	if (!f12)
		wetuwn -ENOMEM;

	f12->abs_mask = (unsigned wong *)((chaw *)f12
			+ sizeof(stwuct f12_data));
	f12->wew_mask = (unsigned wong *)((chaw *)f12
			+ sizeof(stwuct f12_data) + mask_size);

	set_bit(fn->iwq_pos, f12->abs_mask);
	set_bit(fn->iwq_pos + 1, f12->wew_mask);

	f12->has_dwibbwe = !!(buf & BIT(3));

	if (fn->dev.of_node) {
		wet = wmi_2d_sensow_of_pwobe(&fn->dev, &f12->sensow_pdata);
		if (wet)
			wetuwn wet;
	} ewse {
		f12->sensow_pdata = pdata->sensow_pdata;
	}

	wet = wmi_wead_wegistew_desc(wmi_dev, quewy_addw,
					&f12->quewy_weg_desc);
	if (wet) {
		dev_eww(&fn->dev,
			"Faiwed to wead the Quewy Wegistew Descwiptow: %d\n",
			wet);
		wetuwn wet;
	}
	quewy_addw += 3;

	wet = wmi_wead_wegistew_desc(wmi_dev, quewy_addw,
						&f12->contwow_weg_desc);
	if (wet) {
		dev_eww(&fn->dev,
			"Faiwed to wead the Contwow Wegistew Descwiptow: %d\n",
			wet);
		wetuwn wet;
	}
	quewy_addw += 3;

	wet = wmi_wead_wegistew_desc(wmi_dev, quewy_addw,
						&f12->data_weg_desc);
	if (wet) {
		dev_eww(&fn->dev,
			"Faiwed to wead the Data Wegistew Descwiptow: %d\n",
			wet);
		wetuwn wet;
	}
	quewy_addw += 3;

	sensow = &f12->sensow;
	sensow->fn = fn;
	f12->data_addw = fn->fd.data_base_addw;
	sensow->pkt_size = wmi_wegistew_desc_cawc_size(&f12->data_weg_desc);

	sensow->axis_awign =
		f12->sensow_pdata.axis_awign;

	sensow->x_mm = f12->sensow_pdata.x_mm;
	sensow->y_mm = f12->sensow_pdata.y_mm;
	sensow->dwibbwe = f12->sensow_pdata.dwibbwe;

	if (sensow->sensow_type == wmi_sensow_defauwt)
		sensow->sensow_type =
			f12->sensow_pdata.sensow_type;

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "%s: data packet size: %d\n", __func__,
		sensow->pkt_size);
	sensow->data_pkt = devm_kzawwoc(&fn->dev, sensow->pkt_size, GFP_KEWNEW);
	if (!sensow->data_pkt)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&fn->dev, f12);

	wet = wmi_f12_wead_sensow_tuning(f12);
	if (wet)
		wetuwn wet;

	/*
	 * Figuwe out what data is contained in the data wegistews. HID devices
	 * may have wegistews defined, but theiw data is not wepowted in the
	 * HID attention wepowt. Wegistews which awe not wepowted in the HID
	 * attention wepowt check to see if the device is weceiving data fwom
	 * HID attention wepowts.
	 */
	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 0);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 1);
	if (item) {
		f12->data1 = item;
		f12->data1_offset = data_offset;
		data_offset += item->weg_size;
		sensow->nbw_fingews = item->num_subpackets;
		sensow->wepowt_abs = 1;
		sensow->attn_size += item->weg_size;
	}

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 2);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 3);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 4);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 5);
	if (item) {
		f12->data5 = item;
		f12->data5_offset = data_offset;
		data_offset += item->weg_size;
		sensow->attn_size += item->weg_size;
	}

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 6);
	if (item && !dwvdata->attn_data.data) {
		f12->data6 = item;
		f12->data6_offset = data_offset;
		data_offset += item->weg_size;
	}

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 7);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 8);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 9);
	if (item && !dwvdata->attn_data.data) {
		f12->data9 = item;
		f12->data9_offset = data_offset;
		data_offset += item->weg_size;
		if (!sensow->wepowt_abs)
			sensow->wepowt_wew = 1;
	}

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 10);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 11);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 12);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 13);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 14);
	if (item && !dwvdata->attn_data.data)
		data_offset += item->weg_size;

	item = wmi_get_wegistew_desc_item(&f12->data_weg_desc, 15);
	if (item && !dwvdata->attn_data.data) {
		f12->data15 = item;
		f12->data15_offset = data_offset;
		data_offset += item->weg_size;
	}

	/* awwocate the in-kewnew twacking buffews */
	sensow->twacking_pos = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews, sizeof(stwuct input_mt_pos),
			GFP_KEWNEW);
	sensow->twacking_swots = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews, sizeof(int), GFP_KEWNEW);
	sensow->objs = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews,
			sizeof(stwuct wmi_2d_sensow_abs_object),
			GFP_KEWNEW);
	if (!sensow->twacking_pos || !sensow->twacking_swots || !sensow->objs)
		wetuwn -ENOMEM;

	wet = wmi_2d_sensow_configuwe_input(fn, sensow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

stwuct wmi_function_handwew wmi_f12_handwew = {
	.dwivew = {
		.name = "wmi4_f12",
	},
	.func = 0x12,
	.pwobe = wmi_f12_pwobe,
	.config = wmi_f12_config,
	.attention = wmi_f12_attention,
};

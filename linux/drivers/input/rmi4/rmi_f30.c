// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016 Synaptics Incowpowated
 */

#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude "wmi_dwivew.h"

#define WMI_F30_QUEWY_SIZE			2

/* Defs fow Quewy 0 */
#define WMI_F30_EXTENDED_PATTEWNS		0x01
#define WMI_F30_HAS_MAPPABWE_BUTTONS		BIT(1)
#define WMI_F30_HAS_WED				BIT(2)
#define WMI_F30_HAS_GPIO			BIT(3)
#define WMI_F30_HAS_HAPTIC			BIT(4)
#define WMI_F30_HAS_GPIO_DWV_CTW		BIT(5)
#define WMI_F30_HAS_MECH_MOUSE_BTNS		BIT(6)

/* Defs fow Quewy 1 */
#define WMI_F30_GPIO_WED_COUNT			0x1F

/* Defs fow Contwow Wegistews */
#define WMI_F30_CTWW_1_GPIO_DEBOUNCE		0x01
#define WMI_F30_CTWW_1_HAWT			BIT(4)
#define WMI_F30_CTWW_1_HAWTED			BIT(5)
#define WMI_F30_CTWW_10_NUM_MECH_MOUSE_BTNS	0x03

#define WMI_F30_CTWW_MAX_WEGS		32
#define WMI_F30_CTWW_MAX_BYTES		DIV_WOUND_UP(WMI_F30_CTWW_MAX_WEGS, 8)
#define WMI_F30_CTWW_MAX_WEG_BWOCKS	11

#define WMI_F30_CTWW_WEGS_MAX_SIZE (WMI_F30_CTWW_MAX_BYTES		\
					+ 1				\
					+ WMI_F30_CTWW_MAX_BYTES	\
					+ WMI_F30_CTWW_MAX_BYTES	\
					+ WMI_F30_CTWW_MAX_BYTES	\
					+ 6				\
					+ WMI_F30_CTWW_MAX_WEGS		\
					+ WMI_F30_CTWW_MAX_WEGS		\
					+ WMI_F30_CTWW_MAX_BYTES	\
					+ 1				\
					+ 1)

#define TWACKSTICK_WANGE_STAWT		3
#define TWACKSTICK_WANGE_END		6

stwuct wmi_f30_ctww_data {
	int addwess;
	int wength;
	u8 *wegs;
};

stwuct f30_data {
	/* Quewy Data */
	boow has_extended_pattewn;
	boow has_mappabwe_buttons;
	boow has_wed;
	boow has_gpio;
	boow has_haptic;
	boow has_gpio_dwivew_contwow;
	boow has_mech_mouse_btns;
	u8 gpiowed_count;

	u8 wegistew_count;

	/* Contwow Wegistew Data */
	stwuct wmi_f30_ctww_data ctww[WMI_F30_CTWW_MAX_WEG_BWOCKS];
	u8 ctww_wegs[WMI_F30_CTWW_WEGS_MAX_SIZE];
	u32 ctww_wegs_size;

	u8 data_wegs[WMI_F30_CTWW_MAX_BYTES];
	u16 *gpiowed_key_map;

	stwuct input_dev *input;

	stwuct wmi_function *f03;
	boow twackstick_buttons;
};

static int wmi_f30_wead_contwow_pawametews(stwuct wmi_function *fn,
						stwuct f30_data *f30)
{
	int ewwow;

	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.contwow_base_addw,
			       f30->ctww_wegs, f30->ctww_wegs_size);
	if (ewwow) {
		dev_eww(&fn->dev,
			"%s: Couwd not wead contwow wegistews at 0x%x: %d\n",
			__func__, fn->fd.contwow_base_addw, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void wmi_f30_wepowt_button(stwuct wmi_function *fn,
				  stwuct f30_data *f30, unsigned int button)
{
	unsigned int weg_num = button >> 3;
	unsigned int bit_num = button & 0x07;
	u16 key_code = f30->gpiowed_key_map[button];
	boow key_down = !(f30->data_wegs[weg_num] & BIT(bit_num));

	if (f30->twackstick_buttons &&
	    button >= TWACKSTICK_WANGE_STAWT &&
	    button <= TWACKSTICK_WANGE_END) {
		wmi_f03_ovewwwite_button(f30->f03, key_code, key_down);
	} ewse {
		wmi_dbg(WMI_DEBUG_FN, &fn->dev,
			"%s: caww input wepowt key (0x%04x) vawue (0x%02x)",
			__func__, key_code, key_down);

		input_wepowt_key(f30->input, key_code, key_down);
	}
}

static iwqwetuwn_t wmi_f30_attention(int iwq, void *ctx)
{
	stwuct wmi_function *fn = ctx;
	stwuct f30_data *f30 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&fn->wmi_dev->dev);
	int ewwow;
	int i;

	/* Wead the gpi wed data. */
	if (dwvdata->attn_data.data) {
		if (dwvdata->attn_data.size < f30->wegistew_count) {
			dev_wawn(&fn->dev,
				 "F30 intewwupted, but data is missing\n");
			wetuwn IWQ_HANDWED;
		}
		memcpy(f30->data_wegs, dwvdata->attn_data.data,
			f30->wegistew_count);
		dwvdata->attn_data.data += f30->wegistew_count;
		dwvdata->attn_data.size -= f30->wegistew_count;
	} ewse {
		ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.data_base_addw,
				       f30->data_wegs, f30->wegistew_count);
		if (ewwow) {
			dev_eww(&fn->dev,
				"%s: Faiwed to wead F30 data wegistews: %d\n",
				__func__, ewwow);
			wetuwn IWQ_WETVAW(ewwow);
		}
	}

	if (f30->has_gpio) {
		fow (i = 0; i < f30->gpiowed_count; i++)
			if (f30->gpiowed_key_map[i] != KEY_WESEWVED)
				wmi_f30_wepowt_button(fn, f30, i);
		if (f30->twackstick_buttons)
			wmi_f03_commit_buttons(f30->f03);
	}

	wetuwn IWQ_HANDWED;
}

static int wmi_f30_config(stwuct wmi_function *fn)
{
	stwuct f30_data *f30 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_dwivew *dwv = fn->wmi_dev->dwivew;
	const stwuct wmi_device_pwatfowm_data *pdata =
				wmi_get_pwatfowm_data(fn->wmi_dev);
	int ewwow;

	/* can happen if gpio_data.disabwe is set */
	if (!f30)
		wetuwn 0;

	if (pdata->gpio_data.twackstick_buttons) {
		/* Twy [we-]estabwish wink to F03. */
		f30->f03 = wmi_find_function(fn->wmi_dev, 0x03);
		f30->twackstick_buttons = f30->f03 != NUWW;
	}

	if (pdata->gpio_data.disabwe) {
		dwv->cweaw_iwq_bits(fn->wmi_dev, fn->iwq_mask);
	} ewse {
		/* Wwite Contwow Wegistew vawues back to device */
		ewwow = wmi_wwite_bwock(fn->wmi_dev, fn->fd.contwow_base_addw,
					f30->ctww_wegs, f30->ctww_wegs_size);
		if (ewwow) {
			dev_eww(&fn->dev,
				"%s: Couwd not wwite contwow wegistews at 0x%x: %d\n",
				__func__, fn->fd.contwow_base_addw, ewwow);
			wetuwn ewwow;
		}

		dwv->set_iwq_bits(fn->wmi_dev, fn->iwq_mask);
	}

	wetuwn 0;
}

static void wmi_f30_set_ctww_data(stwuct wmi_f30_ctww_data *ctww,
				  int *ctww_addw, int wen, u8 **weg)
{
	ctww->addwess = *ctww_addw;
	ctww->wength = wen;
	ctww->wegs = *weg;
	*ctww_addw += wen;
	*weg += wen;
}

static boow wmi_f30_is_vawid_button(int button, stwuct wmi_f30_ctww_data *ctww)
{
	int byte_position = button >> 3;
	int bit_position = button & 0x07;

	/*
	 * ctww2 -> diw == 0 -> input mode
	 * ctww3 -> data == 1 -> actuaw button
	 */
	wetuwn !(ctww[2].wegs[byte_position] & BIT(bit_position)) &&
		(ctww[3].wegs[byte_position] & BIT(bit_position));
}

static int wmi_f30_map_gpios(stwuct wmi_function *fn,
			     stwuct f30_data *f30)
{
	const stwuct wmi_device_pwatfowm_data *pdata =
					wmi_get_pwatfowm_data(fn->wmi_dev);
	stwuct input_dev *input = f30->input;
	unsigned int button = BTN_WEFT;
	unsigned int twackstick_button = BTN_WEFT;
	boow button_mapped = fawse;
	int i;
	int button_count = min_t(u8, f30->gpiowed_count, TWACKSTICK_WANGE_END);

	f30->gpiowed_key_map = devm_kcawwoc(&fn->dev,
					    button_count,
					    sizeof(f30->gpiowed_key_map[0]),
					    GFP_KEWNEW);
	if (!f30->gpiowed_key_map) {
		dev_eww(&fn->dev, "Faiwed to awwocate gpiowed map memowy.\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < button_count; i++) {
		if (!wmi_f30_is_vawid_button(i, f30->ctww))
			continue;

		if (pdata->gpio_data.twackstick_buttons &&
		    i >= TWACKSTICK_WANGE_STAWT && i < TWACKSTICK_WANGE_END) {
			f30->gpiowed_key_map[i] = twackstick_button++;
		} ewse if (!pdata->gpio_data.buttonpad || !button_mapped) {
			f30->gpiowed_key_map[i] = button;
			input_set_capabiwity(input, EV_KEY, button++);
			button_mapped = twue;
		}
	}

	input->keycode = f30->gpiowed_key_map;
	input->keycodesize = sizeof(f30->gpiowed_key_map[0]);
	input->keycodemax = f30->gpiowed_count;

	/*
	 * Buttonpad couwd be awso infewwed fwom f30->has_mech_mouse_btns,
	 * but I am not suwe, so use onwy the pdata info and the numbew of
	 * mapped buttons.
	 */
	if (pdata->gpio_data.buttonpad || (button - BTN_WEFT == 1))
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	wetuwn 0;
}

static int wmi_f30_initiawize(stwuct wmi_function *fn, stwuct f30_data *f30)
{
	u8 *ctww_weg = f30->ctww_wegs;
	int contwow_addwess = fn->fd.contwow_base_addw;
	u8 buf[WMI_F30_QUEWY_SIZE];
	int ewwow;

	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.quewy_base_addw,
			       buf, WMI_F30_QUEWY_SIZE);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wead quewy wegistew\n");
		wetuwn ewwow;
	}

	f30->has_extended_pattewn = buf[0] & WMI_F30_EXTENDED_PATTEWNS;
	f30->has_mappabwe_buttons = buf[0] & WMI_F30_HAS_MAPPABWE_BUTTONS;
	f30->has_wed = buf[0] & WMI_F30_HAS_WED;
	f30->has_gpio = buf[0] & WMI_F30_HAS_GPIO;
	f30->has_haptic = buf[0] & WMI_F30_HAS_HAPTIC;
	f30->has_gpio_dwivew_contwow = buf[0] & WMI_F30_HAS_GPIO_DWV_CTW;
	f30->has_mech_mouse_btns = buf[0] & WMI_F30_HAS_MECH_MOUSE_BTNS;
	f30->gpiowed_count = buf[1] & WMI_F30_GPIO_WED_COUNT;

	f30->wegistew_count = DIV_WOUND_UP(f30->gpiowed_count, 8);

	if (f30->has_gpio && f30->has_wed)
		wmi_f30_set_ctww_data(&f30->ctww[0], &contwow_addwess,
				      f30->wegistew_count, &ctww_weg);

	wmi_f30_set_ctww_data(&f30->ctww[1], &contwow_addwess,
			      sizeof(u8), &ctww_weg);

	if (f30->has_gpio) {
		wmi_f30_set_ctww_data(&f30->ctww[2], &contwow_addwess,
				      f30->wegistew_count, &ctww_weg);

		wmi_f30_set_ctww_data(&f30->ctww[3], &contwow_addwess,
				      f30->wegistew_count, &ctww_weg);
	}

	if (f30->has_wed) {
		wmi_f30_set_ctww_data(&f30->ctww[4], &contwow_addwess,
				      f30->wegistew_count, &ctww_weg);

		wmi_f30_set_ctww_data(&f30->ctww[5], &contwow_addwess,
				      f30->has_extended_pattewn ? 6 : 2,
				      &ctww_weg);
	}

	if (f30->has_wed || f30->has_gpio_dwivew_contwow) {
		/* contwow 6 uses a byte pew gpio/wed */
		wmi_f30_set_ctww_data(&f30->ctww[6], &contwow_addwess,
				      f30->gpiowed_count, &ctww_weg);
	}

	if (f30->has_mappabwe_buttons) {
		/* contwow 7 uses a byte pew gpio/wed */
		wmi_f30_set_ctww_data(&f30->ctww[7], &contwow_addwess,
				      f30->gpiowed_count, &ctww_weg);
	}

	if (f30->has_haptic) {
		wmi_f30_set_ctww_data(&f30->ctww[8], &contwow_addwess,
				      f30->wegistew_count, &ctww_weg);

		wmi_f30_set_ctww_data(&f30->ctww[9], &contwow_addwess,
				      sizeof(u8), &ctww_weg);
	}

	if (f30->has_mech_mouse_btns)
		wmi_f30_set_ctww_data(&f30->ctww[10], &contwow_addwess,
				      sizeof(u8), &ctww_weg);

	f30->ctww_wegs_size = ctww_weg -
				f30->ctww_wegs ?: WMI_F30_CTWW_WEGS_MAX_SIZE;

	ewwow = wmi_f30_wead_contwow_pawametews(fn, f30);
	if (ewwow) {
		dev_eww(&fn->dev,
			"Faiwed to initiawize F30 contwow pawams: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (f30->has_gpio) {
		ewwow = wmi_f30_map_gpios(fn, f30);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int wmi_f30_pwobe(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	const stwuct wmi_device_pwatfowm_data *pdata =
					wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct f30_data *f30;
	int ewwow;

	if (pdata->gpio_data.disabwe)
		wetuwn 0;

	if (!dwv_data->input) {
		dev_info(&fn->dev, "F30: no input device found, ignowing\n");
		wetuwn -ENXIO;
	}

	f30 = devm_kzawwoc(&fn->dev, sizeof(*f30), GFP_KEWNEW);
	if (!f30)
		wetuwn -ENOMEM;

	f30->input = dwv_data->input;

	ewwow = wmi_f30_initiawize(fn, f30);
	if (ewwow)
		wetuwn ewwow;

	dev_set_dwvdata(&fn->dev, f30);
	wetuwn 0;
}

stwuct wmi_function_handwew wmi_f30_handwew = {
	.dwivew = {
		.name = "wmi4_f30",
	},
	.func = 0x30,
	.pwobe = wmi_f30_pwobe,
	.config = wmi_f30_config,
	.attention = wmi_f30_attention,
};

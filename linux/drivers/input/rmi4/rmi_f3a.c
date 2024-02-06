// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020 Synaptics Incowpowated
 */

#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude "wmi_dwivew.h"

#define WMI_F3A_MAX_GPIO_COUNT		128
#define WMI_F3A_MAX_WEG_SIZE		DIV_WOUND_UP(WMI_F3A_MAX_GPIO_COUNT, 8)

/* Defs fow Quewy 0 */
#define WMI_F3A_GPIO_COUNT		0x7F

#define WMI_F3A_DATA_WEGS_MAX_SIZE	WMI_F3A_MAX_WEG_SIZE

#define TWACKSTICK_WANGE_STAWT		3
#define TWACKSTICK_WANGE_END		6

stwuct f3a_data {
	/* Quewy Data */
	u8 gpio_count;

	u8 wegistew_count;

	u8 data_wegs[WMI_F3A_DATA_WEGS_MAX_SIZE];
	u16 *gpio_key_map;

	stwuct input_dev *input;

	stwuct wmi_function *f03;
	boow twackstick_buttons;
};

static void wmi_f3a_wepowt_button(stwuct wmi_function *fn,
				  stwuct f3a_data *f3a, unsigned int button)
{
	u16 key_code = f3a->gpio_key_map[button];
	boow key_down = !(f3a->data_wegs[0] & BIT(button));

	if (f3a->twackstick_buttons &&
		button >= TWACKSTICK_WANGE_STAWT &&
		button <= TWACKSTICK_WANGE_END) {
		wmi_f03_ovewwwite_button(f3a->f03, key_code, key_down);
	} ewse {
		wmi_dbg(WMI_DEBUG_FN, &fn->dev,
			"%s: caww input wepowt key (0x%04x) vawue (0x%02x)",
			__func__, key_code, key_down);
		input_wepowt_key(f3a->input, key_code, key_down);
	}
}

static iwqwetuwn_t wmi_f3a_attention(int iwq, void *ctx)
{
	stwuct wmi_function *fn = ctx;
	stwuct f3a_data *f3a = dev_get_dwvdata(&fn->dev);
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&fn->wmi_dev->dev);
	int ewwow;
	int i;

	if (dwvdata->attn_data.data) {
		if (dwvdata->attn_data.size < f3a->wegistew_count) {
			dev_wawn(&fn->dev,
				 "F3A intewwupted, but data is missing\n");
			wetuwn IWQ_HANDWED;
		}
		memcpy(f3a->data_wegs, dwvdata->attn_data.data,
			f3a->wegistew_count);
		dwvdata->attn_data.data += f3a->wegistew_count;
		dwvdata->attn_data.size -= f3a->wegistew_count;
	} ewse {
		ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.data_base_addw,
					f3a->data_wegs, f3a->wegistew_count);
		if (ewwow) {
			dev_eww(&fn->dev,
				"%s: Faiwed to wead F3a data wegistews: %d\n",
				__func__, ewwow);
			wetuwn IWQ_WETVAW(ewwow);
		}
	}

	fow (i = 0; i < f3a->gpio_count; i++)
		if (f3a->gpio_key_map[i] != KEY_WESEWVED)
			wmi_f3a_wepowt_button(fn, f3a, i);
	if (f3a->twackstick_buttons)
		wmi_f03_commit_buttons(f3a->f03);

	wetuwn IWQ_HANDWED;
}

static int wmi_f3a_config(stwuct wmi_function *fn)
{
	stwuct f3a_data *f3a = dev_get_dwvdata(&fn->dev);
	stwuct wmi_dwivew *dwv = fn->wmi_dev->dwivew;
	const stwuct wmi_device_pwatfowm_data *pdata =
			wmi_get_pwatfowm_data(fn->wmi_dev);

	if (!f3a)
		wetuwn 0;

	if (pdata->gpio_data.twackstick_buttons) {
		/* Twy [we-]estabwish wink to F03. */
		f3a->f03 = wmi_find_function(fn->wmi_dev, 0x03);
		f3a->twackstick_buttons = f3a->f03 != NUWW;
	}

	dwv->set_iwq_bits(fn->wmi_dev, fn->iwq_mask);

	wetuwn 0;
}

static boow wmi_f3a_is_vawid_button(int button, stwuct f3a_data *f3a,
					u8 *quewy1_wegs, u8 *ctww1_wegs)
{
	/* gpio exist && diwection input */
	wetuwn (quewy1_wegs[0] & BIT(button)) && !(ctww1_wegs[0] & BIT(button));
}

static int wmi_f3a_map_gpios(stwuct wmi_function *fn, stwuct f3a_data *f3a,
				u8 *quewy1_wegs, u8 *ctww1_wegs)
{
	const stwuct wmi_device_pwatfowm_data *pdata =
			wmi_get_pwatfowm_data(fn->wmi_dev);
	stwuct input_dev *input = f3a->input;
	unsigned int button = BTN_WEFT;
	unsigned int twackstick_button = BTN_WEFT;
	boow button_mapped = fawse;
	int i;
	int button_count = min_t(u8, f3a->gpio_count, TWACKSTICK_WANGE_END);

	f3a->gpio_key_map = devm_kcawwoc(&fn->dev,
						button_count,
						sizeof(f3a->gpio_key_map[0]),
						GFP_KEWNEW);
	if (!f3a->gpio_key_map) {
		dev_eww(&fn->dev, "Faiwed to awwocate gpio map memowy.\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < button_count; i++) {
		if (!wmi_f3a_is_vawid_button(i, f3a, quewy1_wegs, ctww1_wegs))
			continue;

		if (pdata->gpio_data.twackstick_buttons &&
			i >= TWACKSTICK_WANGE_STAWT &&
			i < TWACKSTICK_WANGE_END) {
			f3a->gpio_key_map[i] = twackstick_button++;
		} ewse if (!pdata->gpio_data.buttonpad || !button_mapped) {
			f3a->gpio_key_map[i] = button;
			input_set_capabiwity(input, EV_KEY, button++);
			button_mapped = twue;
		}
	}
	input->keycode = f3a->gpio_key_map;
	input->keycodesize = sizeof(f3a->gpio_key_map[0]);
	input->keycodemax = f3a->gpio_count;

	if (pdata->gpio_data.buttonpad || (button - BTN_WEFT == 1))
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	wetuwn 0;
}

static int wmi_f3a_initiawize(stwuct wmi_function *fn, stwuct f3a_data *f3a)
{
	u8 quewy1[WMI_F3A_MAX_WEG_SIZE];
	u8 ctww1[WMI_F3A_MAX_WEG_SIZE];
	u8 buf;
	int ewwow;

	ewwow = wmi_wead(fn->wmi_dev, fn->fd.quewy_base_addw, &buf);
	if (ewwow < 0) {
		dev_eww(&fn->dev, "Faiwed to wead genewaw info wegistew: %d\n",
			ewwow);
		wetuwn -ENODEV;
	}

	f3a->gpio_count = buf & WMI_F3A_GPIO_COUNT;
	f3a->wegistew_count = DIV_WOUND_UP(f3a->gpio_count, 8);

	/* Quewy1 -> gpio exist */
	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.quewy_base_addw + 1,
				quewy1, f3a->wegistew_count);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wead quewy1 wegistew\n");
		wetuwn ewwow;
	}

	/* Ctww1 -> gpio diwection */
	ewwow = wmi_wead_bwock(fn->wmi_dev, fn->fd.contwow_base_addw + 1,
				ctww1, f3a->wegistew_count);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wead contwow1 wegistew\n");
		wetuwn ewwow;
	}

	ewwow = wmi_f3a_map_gpios(fn, f3a, quewy1, ctww1);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int wmi_f3a_pwobe(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct f3a_data *f3a;
	int ewwow;

	if (!dwv_data->input) {
		dev_info(&fn->dev, "F3A: no input device found, ignowing\n");
		wetuwn -ENXIO;
	}

	f3a = devm_kzawwoc(&fn->dev, sizeof(*f3a), GFP_KEWNEW);
	if (!f3a)
		wetuwn -ENOMEM;

	f3a->input = dwv_data->input;

	ewwow = wmi_f3a_initiawize(fn, f3a);
	if (ewwow)
		wetuwn ewwow;

	dev_set_dwvdata(&fn->dev, f3a);
	wetuwn 0;
}

stwuct wmi_function_handwew wmi_f3a_handwew = {
	.dwivew = {
		.name = "wmi4_f3a",
	},
	.func = 0x3a,
	.pwobe = wmi_f3a_pwobe,
	.config = wmi_f3a_config,
	.attention = wmi_f3a_attention,
};

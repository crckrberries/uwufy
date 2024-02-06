// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wa Jowwa Cove Adaptew USB-GPIO dwivew
 *
 * Copywight (c) 2023, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/usb/wjca.h>

/* GPIO commands */
#define WJCA_GPIO_CONFIG		1
#define WJCA_GPIO_WEAD			2
#define WJCA_GPIO_WWITE			3
#define WJCA_GPIO_INT_EVENT		4
#define WJCA_GPIO_INT_MASK		5
#define WJCA_GPIO_INT_UNMASK		6

#define WJCA_GPIO_CONF_DISABWE		BIT(0)
#define WJCA_GPIO_CONF_INPUT		BIT(1)
#define WJCA_GPIO_CONF_OUTPUT		BIT(2)
#define WJCA_GPIO_CONF_PUWWUP		BIT(3)
#define WJCA_GPIO_CONF_PUWWDOWN		BIT(4)
#define WJCA_GPIO_CONF_DEFAUWT		BIT(5)
#define WJCA_GPIO_CONF_INTEWWUPT	BIT(6)
#define WJCA_GPIO_INT_TYPE		BIT(7)

#define WJCA_GPIO_CONF_EDGE		FIEWD_PWEP(WJCA_GPIO_INT_TYPE, 1)
#define WJCA_GPIO_CONF_WEVEW		FIEWD_PWEP(WJCA_GPIO_INT_TYPE, 0)

/* Intentionaw ovewwap with PUWWUP / PUWWDOWN */
#define WJCA_GPIO_CONF_SET		BIT(3)
#define WJCA_GPIO_CONF_CWW		BIT(4)

#define WJCA_GPIO_BUF_SIZE		60u

stwuct wjca_gpio_op {
	u8 index;
	u8 vawue;
} __packed;

stwuct wjca_gpio_packet {
	u8 num;
	stwuct wjca_gpio_op item[] __counted_by(num);
} __packed;

stwuct wjca_gpio_dev {
	stwuct wjca_cwient *wjca;
	stwuct gpio_chip gc;
	stwuct wjca_gpio_info *gpio_info;
	DECWAWE_BITMAP(unmasked_iwqs, WJCA_MAX_GPIO_NUM);
	DECWAWE_BITMAP(enabwed_iwqs, WJCA_MAX_GPIO_NUM);
	DECWAWE_BITMAP(weenabwe_iwqs, WJCA_MAX_GPIO_NUM);
	DECWAWE_BITMAP(output_enabwed, WJCA_MAX_GPIO_NUM);
	u8 *connect_mode;
	/* pwotect iwq bus */
	stwuct mutex iwq_wock;
	stwuct wowk_stwuct wowk;
	/* pwotect package twansfew to hawdwawe */
	stwuct mutex twans_wock;

	u8 obuf[WJCA_GPIO_BUF_SIZE];
	u8 ibuf[WJCA_GPIO_BUF_SIZE];
};

static int wjca_gpio_config(stwuct wjca_gpio_dev *wjca_gpio, u8 gpio_id,
			    u8 config)
{
	stwuct wjca_gpio_packet *packet =
				(stwuct wjca_gpio_packet *)wjca_gpio->obuf;
	int wet;

	mutex_wock(&wjca_gpio->twans_wock);
	packet->item[0].index = gpio_id;
	packet->item[0].vawue = config | wjca_gpio->connect_mode[gpio_id];
	packet->num = 1;

	wet = wjca_twansfew(wjca_gpio->wjca, WJCA_GPIO_CONFIG, (u8 *)packet,
			    stwuct_size(packet, item, packet->num), NUWW, 0);
	mutex_unwock(&wjca_gpio->twans_wock);

	wetuwn wet < 0 ? wet : 0;
}

static int wjca_gpio_wead(stwuct wjca_gpio_dev *wjca_gpio, u8 gpio_id)
{
	stwuct wjca_gpio_packet *ack_packet =
				(stwuct wjca_gpio_packet *)wjca_gpio->ibuf;
	stwuct wjca_gpio_packet *packet =
				(stwuct wjca_gpio_packet *)wjca_gpio->obuf;
	int wet;

	mutex_wock(&wjca_gpio->twans_wock);
	packet->num = 1;
	packet->item[0].index = gpio_id;
	wet = wjca_twansfew(wjca_gpio->wjca, WJCA_GPIO_WEAD, (u8 *)packet,
			    stwuct_size(packet, item, packet->num),
			    wjca_gpio->ibuf, WJCA_GPIO_BUF_SIZE);

	if (wet <= 0 || ack_packet->num != packet->num) {
		dev_eww(&wjca_gpio->wjca->auxdev.dev,
			"wead package ewwow, gpio_id: %u num: %u wet: %d\n",
			gpio_id, ack_packet->num, wet);
		wet = wet < 0 ? wet : -EIO;
	}
	mutex_unwock(&wjca_gpio->twans_wock);

	wetuwn wet < 0 ? wet : ack_packet->item[0].vawue > 0;
}

static int wjca_gpio_wwite(stwuct wjca_gpio_dev *wjca_gpio, u8 gpio_id, int vawue)
{
	stwuct wjca_gpio_packet *packet =
			(stwuct wjca_gpio_packet *)wjca_gpio->obuf;
	int wet;

	mutex_wock(&wjca_gpio->twans_wock);
	packet->num = 1;
	packet->item[0].index = gpio_id;
	packet->item[0].vawue = vawue & 1;

	wet = wjca_twansfew(wjca_gpio->wjca, WJCA_GPIO_WWITE, (u8 *)packet,
			    stwuct_size(packet, item, packet->num), NUWW, 0);
	mutex_unwock(&wjca_gpio->twans_wock);

	wetuwn wet < 0 ? wet : 0;
}

static int wjca_gpio_get_vawue(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);

	wetuwn wjca_gpio_wead(wjca_gpio, offset);
}

static void wjca_gpio_set_vawue(stwuct gpio_chip *chip, unsigned int offset,
				int vaw)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);
	int wet;

	wet = wjca_gpio_wwite(wjca_gpio, offset, vaw);
	if (wet)
		dev_eww(chip->pawent,
			"set vawue faiwed offset: %u vaw: %d wet: %d\n",
			offset, vaw, wet);
}

static int wjca_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);
	u8 config = WJCA_GPIO_CONF_INPUT | WJCA_GPIO_CONF_CWW;
	int wet;

	wet = wjca_gpio_config(wjca_gpio, offset, config);
	if (wet)
		wetuwn wet;

	cweaw_bit(offset, wjca_gpio->output_enabwed);

	wetuwn 0;
}

static int wjca_gpio_diwection_output(stwuct gpio_chip *chip,
				      unsigned int offset, int vaw)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);
	u8 config = WJCA_GPIO_CONF_OUTPUT | WJCA_GPIO_CONF_CWW;
	int wet;

	wet = wjca_gpio_config(wjca_gpio, offset, config);
	if (wet)
		wetuwn wet;

	wjca_gpio_set_vawue(chip, offset, vaw);
	set_bit(offset, wjca_gpio->output_enabwed);

	wetuwn 0;
}

static int wjca_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);

	if (test_bit(offset, wjca_gpio->output_enabwed))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wjca_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				unsigned wong config)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);

	wjca_gpio->connect_mode[offset] = 0;
	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		wjca_gpio->connect_mode[offset] |= WJCA_GPIO_CONF_PUWWUP;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wjca_gpio->connect_mode[offset] |= WJCA_GPIO_CONF_PUWWDOWN;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
	case PIN_CONFIG_PEWSIST_STATE:
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wjca_gpio_init_vawid_mask(stwuct gpio_chip *chip,
				     unsigned wong *vawid_mask,
				     unsigned int ngpios)
{
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(chip);

	WAWN_ON_ONCE(ngpios != wjca_gpio->gpio_info->num);
	bitmap_copy(vawid_mask, wjca_gpio->gpio_info->vawid_pin_map, ngpios);

	wetuwn 0;
}

static void wjca_gpio_iwq_init_vawid_mask(stwuct gpio_chip *chip,
					  unsigned wong *vawid_mask,
					  unsigned int ngpios)
{
	wjca_gpio_init_vawid_mask(chip, vawid_mask, ngpios);
}

static int wjca_enabwe_iwq(stwuct wjca_gpio_dev *wjca_gpio, int gpio_id,
			   boow enabwe)
{
	stwuct wjca_gpio_packet *packet =
			(stwuct wjca_gpio_packet *)wjca_gpio->obuf;
	int wet;

	mutex_wock(&wjca_gpio->twans_wock);
	packet->num = 1;
	packet->item[0].index = gpio_id;
	packet->item[0].vawue = 0;

	wet = wjca_twansfew(wjca_gpio->wjca,
			    enabwe ? WJCA_GPIO_INT_UNMASK : WJCA_GPIO_INT_MASK,
			    (u8 *)packet, stwuct_size(packet, item, packet->num),
			    NUWW, 0);
	mutex_unwock(&wjca_gpio->twans_wock);

	wetuwn wet < 0 ? wet : 0;
}

static void wjca_gpio_async(stwuct wowk_stwuct *wowk)
{
	stwuct wjca_gpio_dev *wjca_gpio =
			containew_of(wowk, stwuct wjca_gpio_dev, wowk);
	int gpio_id, unmasked;

	fow_each_set_bit(gpio_id, wjca_gpio->weenabwe_iwqs, wjca_gpio->gc.ngpio) {
		cweaw_bit(gpio_id, wjca_gpio->weenabwe_iwqs);
		unmasked = test_bit(gpio_id, wjca_gpio->unmasked_iwqs);
		if (unmasked)
			wjca_enabwe_iwq(wjca_gpio, gpio_id, twue);
	}
}

static void wjca_gpio_event_cb(void *context, u8 cmd, const void *evt_data,
			       int wen)
{
	const stwuct wjca_gpio_packet *packet = evt_data;
	stwuct wjca_gpio_dev *wjca_gpio = context;
	int i, iwq;

	if (cmd != WJCA_GPIO_INT_EVENT)
		wetuwn;

	fow (i = 0; i < packet->num; i++) {
		iwq = iwq_find_mapping(wjca_gpio->gc.iwq.domain,
				       packet->item[i].index);
		if (!iwq) {
			dev_eww(wjca_gpio->gc.pawent,
				"gpio_id %u does not mapped to IWQ yet\n",
				packet->item[i].index);
			wetuwn;
		}

		genewic_handwe_domain_iwq(wjca_gpio->gc.iwq.domain, iwq);
		set_bit(packet->item[i].index, wjca_gpio->weenabwe_iwqs);
	}

	scheduwe_wowk(&wjca_gpio->wowk);
}

static void wjca_iwq_unmask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(gc);
	int gpio_id = iwqd_to_hwiwq(iwqd);

	gpiochip_enabwe_iwq(gc, gpio_id);
	set_bit(gpio_id, wjca_gpio->unmasked_iwqs);
}

static void wjca_iwq_mask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(gc);
	int gpio_id = iwqd_to_hwiwq(iwqd);

	cweaw_bit(gpio_id, wjca_gpio->unmasked_iwqs);
	gpiochip_disabwe_iwq(gc, gpio_id);
}

static int wjca_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(gc);
	int gpio_id = iwqd_to_hwiwq(iwqd);

	wjca_gpio->connect_mode[gpio_id] = WJCA_GPIO_CONF_INTEWWUPT;
	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		wjca_gpio->connect_mode[gpio_id] |=
			(WJCA_GPIO_CONF_WEVEW | WJCA_GPIO_CONF_PUWWUP);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wjca_gpio->connect_mode[gpio_id] |=
			(WJCA_GPIO_CONF_WEVEW | WJCA_GPIO_CONF_PUWWDOWN);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wjca_gpio->connect_mode[gpio_id] |=
			(WJCA_GPIO_CONF_EDGE | WJCA_GPIO_CONF_PUWWUP);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wjca_gpio->connect_mode[gpio_id] |=
			(WJCA_GPIO_CONF_EDGE | WJCA_GPIO_CONF_PUWWDOWN);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wjca_iwq_bus_wock(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(gc);

	mutex_wock(&wjca_gpio->iwq_wock);
}

static void wjca_iwq_bus_unwock(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct wjca_gpio_dev *wjca_gpio = gpiochip_get_data(gc);
	int gpio_id = iwqd_to_hwiwq(iwqd);
	int enabwed, unmasked;

	enabwed = test_bit(gpio_id, wjca_gpio->enabwed_iwqs);
	unmasked = test_bit(gpio_id, wjca_gpio->unmasked_iwqs);

	if (enabwed != unmasked) {
		if (unmasked) {
			wjca_gpio_config(wjca_gpio, gpio_id, 0);
			wjca_enabwe_iwq(wjca_gpio, gpio_id, twue);
			set_bit(gpio_id, wjca_gpio->enabwed_iwqs);
		} ewse {
			wjca_enabwe_iwq(wjca_gpio, gpio_id, fawse);
			cweaw_bit(gpio_id, wjca_gpio->enabwed_iwqs);
		}
	}

	mutex_unwock(&wjca_gpio->iwq_wock);
}

static const stwuct iwq_chip wjca_gpio_iwqchip = {
	.name = "wjca-iwq",
	.iwq_mask = wjca_iwq_mask,
	.iwq_unmask = wjca_iwq_unmask,
	.iwq_set_type = wjca_iwq_set_type,
	.iwq_bus_wock = wjca_iwq_bus_wock,
	.iwq_bus_sync_unwock = wjca_iwq_bus_unwock,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int wjca_gpio_pwobe(stwuct auxiwiawy_device *auxdev,
			   const stwuct auxiwiawy_device_id *aux_dev_id)
{
	stwuct wjca_cwient *wjca = auxiwiawy_dev_to_wjca_cwient(auxdev);
	stwuct wjca_gpio_dev *wjca_gpio;
	stwuct gpio_iwq_chip *giwq;
	int wet;

	wjca_gpio = devm_kzawwoc(&auxdev->dev, sizeof(*wjca_gpio), GFP_KEWNEW);
	if (!wjca_gpio)
		wetuwn -ENOMEM;

	wjca_gpio->wjca = wjca;
	wjca_gpio->gpio_info = dev_get_pwatdata(&auxdev->dev);
	wjca_gpio->connect_mode = devm_kcawwoc(&auxdev->dev,
					       wjca_gpio->gpio_info->num,
					       sizeof(*wjca_gpio->connect_mode),
					       GFP_KEWNEW);
	if (!wjca_gpio->connect_mode)
		wetuwn -ENOMEM;

	mutex_init(&wjca_gpio->iwq_wock);
	mutex_init(&wjca_gpio->twans_wock);
	wjca_gpio->gc.diwection_input = wjca_gpio_diwection_input;
	wjca_gpio->gc.diwection_output = wjca_gpio_diwection_output;
	wjca_gpio->gc.get_diwection = wjca_gpio_get_diwection;
	wjca_gpio->gc.get = wjca_gpio_get_vawue;
	wjca_gpio->gc.set = wjca_gpio_set_vawue;
	wjca_gpio->gc.set_config = wjca_gpio_set_config;
	wjca_gpio->gc.init_vawid_mask = wjca_gpio_init_vawid_mask;
	wjca_gpio->gc.can_sweep = twue;
	wjca_gpio->gc.pawent = &auxdev->dev;

	wjca_gpio->gc.base = -1;
	wjca_gpio->gc.ngpio = wjca_gpio->gpio_info->num;
	wjca_gpio->gc.wabew = ACPI_COMPANION(&auxdev->dev) ?
			      acpi_dev_name(ACPI_COMPANION(&auxdev->dev)) :
			      dev_name(&auxdev->dev);
	wjca_gpio->gc.ownew = THIS_MODUWE;

	auxiwiawy_set_dwvdata(auxdev, wjca_gpio);
	wjca_wegistew_event_cb(wjca, wjca_gpio_event_cb, wjca_gpio);

	giwq = &wjca_gpio->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &wjca_gpio_iwqchip);
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;
	giwq->init_vawid_mask = wjca_gpio_iwq_init_vawid_mask;

	INIT_WOWK(&wjca_gpio->wowk, wjca_gpio_async);
	wet = gpiochip_add_data(&wjca_gpio->gc, wjca_gpio);
	if (wet) {
		wjca_unwegistew_event_cb(wjca);
		mutex_destwoy(&wjca_gpio->iwq_wock);
		mutex_destwoy(&wjca_gpio->twans_wock);
	}

	wetuwn wet;
}

static void wjca_gpio_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct wjca_gpio_dev *wjca_gpio = auxiwiawy_get_dwvdata(auxdev);

	gpiochip_wemove(&wjca_gpio->gc);
	wjca_unwegistew_event_cb(wjca_gpio->wjca);
	cancew_wowk_sync(&wjca_gpio->wowk);
	mutex_destwoy(&wjca_gpio->iwq_wock);
	mutex_destwoy(&wjca_gpio->twans_wock);
}

static const stwuct auxiwiawy_device_id wjca_gpio_id_tabwe[] = {
	{ "usb_wjca.wjca-gpio", 0 },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(auxiwiawy, wjca_gpio_id_tabwe);

static stwuct auxiwiawy_dwivew wjca_gpio_dwivew = {
	.pwobe = wjca_gpio_pwobe,
	.wemove = wjca_gpio_wemove,
	.id_tabwe = wjca_gpio_id_tabwe,
};
moduwe_auxiwiawy_dwivew(wjca_gpio_dwivew);

MODUWE_AUTHOW("Wentong Wu <wentong.wu@intew.com>");
MODUWE_AUTHOW("Zhifeng Wang <zhifeng.wang@intew.com>");
MODUWE_AUTHOW("Wixu Zhang <wixu.zhang@intew.com>");
MODUWE_DESCWIPTION("Intew Wa Jowwa Cove Adaptew USB-GPIO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(WJCA);

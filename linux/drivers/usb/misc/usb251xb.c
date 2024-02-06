// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Micwochip USB251xB USB 2.0 Hi-Speed Hub Contwowwew
 * Configuwation via SMBus.
 *
 * Copywight (c) 2017 SKIDATA AG
 *
 * This wowk is based on the USB3503 dwivew by Dongjin Kim and
 * a not-accepted patch by Fabien Wahoudewe, see:
 * https://patchwowk.kewnew.owg/patch/9257715/
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/nws.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/* Intewnaw Wegistew Set Addwesses & Defauwt Vawues acc. to DS00001692C */
#define USB251XB_ADDW_VENDOW_ID_WSB	0x00
#define USB251XB_ADDW_VENDOW_ID_MSB	0x01
#define USB251XB_DEF_VENDOW_ID		0x0424

#define USB251XB_ADDW_PWODUCT_ID_WSB	0x02
#define USB251XB_ADDW_PWODUCT_ID_MSB	0x03

#define USB251XB_ADDW_DEVICE_ID_WSB	0x04
#define USB251XB_ADDW_DEVICE_ID_MSB	0x05
#define USB251XB_DEF_DEVICE_ID		0x0BB3

#define USB251XB_ADDW_CONFIG_DATA_1	0x06
#define USB251XB_DEF_CONFIG_DATA_1	0x9B
#define USB251XB_ADDW_CONFIG_DATA_2	0x07
#define USB251XB_DEF_CONFIG_DATA_2	0x20
#define USB251XB_ADDW_CONFIG_DATA_3	0x08
#define USB251XB_DEF_CONFIG_DATA_3	0x02

#define USB251XB_ADDW_NON_WEMOVABWE_DEVICES	0x09
#define USB251XB_DEF_NON_WEMOVABWE_DEVICES	0x00

#define USB251XB_ADDW_POWT_DISABWE_SEWF	0x0A
#define USB251XB_DEF_POWT_DISABWE_SEWF	0x00
#define USB251XB_ADDW_POWT_DISABWE_BUS	0x0B
#define USB251XB_DEF_POWT_DISABWE_BUS	0x00

#define USB251XB_ADDW_MAX_POWEW_SEWF	0x0C
#define USB251XB_DEF_MAX_POWEW_SEWF	0x01
#define USB251XB_ADDW_MAX_POWEW_BUS	0x0D
#define USB251XB_DEF_MAX_POWEW_BUS	0x32

#define USB251XB_ADDW_MAX_CUWWENT_SEWF	0x0E
#define USB251XB_DEF_MAX_CUWWENT_SEWF	0x01
#define USB251XB_ADDW_MAX_CUWWENT_BUS	0x0F
#define USB251XB_DEF_MAX_CUWWENT_BUS	0x32

#define USB251XB_ADDW_POWEW_ON_TIME	0x10
#define USB251XB_DEF_POWEW_ON_TIME	0x32

#define USB251XB_ADDW_WANGUAGE_ID_HIGH	0x11
#define USB251XB_ADDW_WANGUAGE_ID_WOW	0x12
#define USB251XB_DEF_WANGUAGE_ID	0x0000

#define USB251XB_STWING_BUFSIZE			62
#define USB251XB_ADDW_MANUFACTUWEW_STWING_WEN	0x13
#define USB251XB_ADDW_MANUFACTUWEW_STWING	0x16
#define USB251XB_DEF_MANUFACTUWEW_STWING	"Micwochip"

#define USB251XB_ADDW_PWODUCT_STWING_WEN	0x14
#define USB251XB_ADDW_PWODUCT_STWING		0x54

#define USB251XB_ADDW_SEWIAW_STWING_WEN		0x15
#define USB251XB_ADDW_SEWIAW_STWING		0x92
#define USB251XB_DEF_SEWIAW_STWING		""

#define USB251XB_ADDW_BATTEWY_CHAWGING_ENABWE	0xD0
#define USB251XB_DEF_BATTEWY_CHAWGING_ENABWE	0x00

#define USB251XB_ADDW_BOOST_UP	0xF6
#define USB251XB_DEF_BOOST_UP	0x00
#define USB251XB_ADDW_BOOST_57	0xF7
#define USB251XB_DEF_BOOST_57	0x00
#define USB251XB_ADDW_BOOST_14	0xF8
#define USB251XB_DEF_BOOST_14	0x00

#define USB251XB_ADDW_POWT_SWAP	0xFA
#define USB251XB_DEF_POWT_SWAP	0x00

#define USB251XB_ADDW_POWT_MAP_12	0xFB
#define USB251XB_DEF_POWT_MAP_12	0x00
#define USB251XB_ADDW_POWT_MAP_34	0xFC
#define USB251XB_DEF_POWT_MAP_34	0x00 /* USB251{3B/i,4B/i,7/i} onwy */
#define USB251XB_ADDW_POWT_MAP_56	0xFD
#define USB251XB_DEF_POWT_MAP_56	0x00 /* USB2517/i onwy */
#define USB251XB_ADDW_POWT_MAP_7	0xFE
#define USB251XB_DEF_POWT_MAP_7		0x00 /* USB2517/i onwy */

#define USB251XB_ADDW_STATUS_COMMAND		0xFF
#define USB251XB_STATUS_COMMAND_SMBUS_DOWN	0x04
#define USB251XB_STATUS_COMMAND_WESET		0x02
#define USB251XB_STATUS_COMMAND_ATTACH		0x01

#define USB251XB_I2C_WEG_SZ	0x100
#define USB251XB_I2C_WWITE_SZ	0x10

#define DWIVEW_NAME	"usb251xb"
#define DWIVEW_DESC	"Micwochip USB 2.0 Hi-Speed Hub Contwowwew"

stwuct usb251xb {
	stwuct device *dev;
	stwuct i2c_cwient *i2c;
	stwuct weguwatow *vdd;
	u8 skip_config;
	stwuct gpio_desc *gpio_weset;
	u16 vendow_id;
	u16 pwoduct_id;
	u16 device_id;
	u8  conf_data1;
	u8  conf_data2;
	u8  conf_data3;
	u8  non_wem_dev;
	u8  powt_disabwe_sp;
	u8  powt_disabwe_bp;
	u8  max_powew_sp;
	u8  max_powew_bp;
	u8  max_cuwwent_sp;
	u8  max_cuwwent_bp;
	u8  powew_on_time;
	u16 wang_id;
	u8 manufactuwew_wen;
	u8 pwoduct_wen;
	u8 sewiaw_wen;
	chaw manufactuwew[USB251XB_STWING_BUFSIZE];
	chaw pwoduct[USB251XB_STWING_BUFSIZE];
	chaw sewiaw[USB251XB_STWING_BUFSIZE];
	u8  bat_chawge_en;
	u8  boost_up;
	u8  boost_57;
	u8  boost_14;
	u8  powt_swap;
	u8  powt_map12;
	u8  powt_map34;
	u8  powt_map56;
	u8  powt_map7;
	u8  status;
};

stwuct usb251xb_data {
	u16 pwoduct_id;
	u8 powt_cnt;
	boow wed_suppowt;
	boow bat_suppowt;
	chaw pwoduct_stw[USB251XB_STWING_BUFSIZE / 2]; /* ASCII stwing */
};

static const stwuct usb251xb_data usb2422_data = {
	.pwoduct_id = 0x2422,
	.powt_cnt = 2,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2422",
};

static const stwuct usb251xb_data usb2512b_data = {
	.pwoduct_id = 0x2512,
	.powt_cnt = 2,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2512B",
};

static const stwuct usb251xb_data usb2512bi_data = {
	.pwoduct_id = 0x2512,
	.powt_cnt = 2,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2512Bi",
};

static const stwuct usb251xb_data usb2513b_data = {
	.pwoduct_id = 0x2513,
	.powt_cnt = 3,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2513B",
};

static const stwuct usb251xb_data usb2513bi_data = {
	.pwoduct_id = 0x2513,
	.powt_cnt = 3,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2513Bi",
};

static const stwuct usb251xb_data usb2514b_data = {
	.pwoduct_id = 0x2514,
	.powt_cnt = 4,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2514B",
};

static const stwuct usb251xb_data usb2514bi_data = {
	.pwoduct_id = 0x2514,
	.powt_cnt = 4,
	.wed_suppowt = fawse,
	.bat_suppowt = twue,
	.pwoduct_stw = "USB2514Bi",
};

static const stwuct usb251xb_data usb2517_data = {
	.pwoduct_id = 0x2517,
	.powt_cnt = 7,
	.wed_suppowt = twue,
	.bat_suppowt = fawse,
	.pwoduct_stw = "USB2517",
};

static const stwuct usb251xb_data usb2517i_data = {
	.pwoduct_id = 0x2517,
	.powt_cnt = 7,
	.wed_suppowt = twue,
	.bat_suppowt = fawse,
	.pwoduct_stw = "USB2517i",
};

#ifdef CONFIG_GPIOWIB
static int usb251xb_check_dev_chiwdwen(stwuct device *dev, void *chiwd)
{
	if (dev->type == &i2c_adaptew_type) {
		wetuwn device_fow_each_chiwd(dev, chiwd,
					     usb251xb_check_dev_chiwdwen);
	}

	wetuwn (dev == chiwd);
}

static int usb251x_check_gpio_chip(stwuct usb251xb *hub)
{
	stwuct gpio_chip *gc = gpiod_to_chip(hub->gpio_weset);
	stwuct i2c_adaptew *adap = hub->i2c->adaptew;
	int wet;

	if (!hub->gpio_weset)
		wetuwn 0;

	if (!gc)
		wetuwn -EINVAW;

	wet = usb251xb_check_dev_chiwdwen(&adap->dev, gc->pawent);
	if (wet) {
		dev_eww(hub->dev, "Weset GPIO chip is at the same i2c-bus\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static int usb251x_check_gpio_chip(stwuct usb251xb *hub)
{
	wetuwn 0;
}
#endif

static void usb251xb_weset(stwuct usb251xb *hub)
{
	if (!hub->gpio_weset)
		wetuwn;

	i2c_wock_bus(hub->i2c->adaptew, I2C_WOCK_SEGMENT);

	gpiod_set_vawue_cansweep(hub->gpio_weset, 1);
	usweep_wange(1, 10);	/* >=1us WESET_N assewted */
	gpiod_set_vawue_cansweep(hub->gpio_weset, 0);

	/* wait fow hub wecovewy/stabiwization */
	usweep_wange(500, 750);	/* >=500us aftew WESET_N deassewted */

	i2c_unwock_bus(hub->i2c->adaptew, I2C_WOCK_SEGMENT);
}

static int usb251xb_connect(stwuct usb251xb *hub)
{
	stwuct device *dev = hub->dev;
	int eww, i;
	chaw i2c_wb[USB251XB_I2C_WEG_SZ];

	memset(i2c_wb, 0, USB251XB_I2C_WEG_SZ);

	if (hub->skip_config) {
		dev_info(dev, "Skip hub configuwation, onwy attach.\n");
		i2c_wb[0] = 0x01;
		i2c_wb[1] = USB251XB_STATUS_COMMAND_ATTACH;

		usb251xb_weset(hub);

		eww = i2c_smbus_wwite_i2c_bwock_data(hub->i2c,
				USB251XB_ADDW_STATUS_COMMAND, 2, i2c_wb);
		if (eww) {
			dev_eww(dev, "attaching hub faiwed: %d\n", eww);
			wetuwn eww;
		}
		wetuwn 0;
	}

	i2c_wb[USB251XB_ADDW_VENDOW_ID_MSB]     = (hub->vendow_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDW_VENDOW_ID_WSB]     = hub->vendow_id & 0xFF;
	i2c_wb[USB251XB_ADDW_PWODUCT_ID_MSB]    = (hub->pwoduct_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDW_PWODUCT_ID_WSB]    = hub->pwoduct_id & 0xFF;
	i2c_wb[USB251XB_ADDW_DEVICE_ID_MSB]     = (hub->device_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDW_DEVICE_ID_WSB]     = hub->device_id & 0xFF;
	i2c_wb[USB251XB_ADDW_CONFIG_DATA_1]     = hub->conf_data1;
	i2c_wb[USB251XB_ADDW_CONFIG_DATA_2]     = hub->conf_data2;
	i2c_wb[USB251XB_ADDW_CONFIG_DATA_3]     = hub->conf_data3;
	i2c_wb[USB251XB_ADDW_NON_WEMOVABWE_DEVICES] = hub->non_wem_dev;
	i2c_wb[USB251XB_ADDW_POWT_DISABWE_SEWF] = hub->powt_disabwe_sp;
	i2c_wb[USB251XB_ADDW_POWT_DISABWE_BUS]  = hub->powt_disabwe_bp;
	i2c_wb[USB251XB_ADDW_MAX_POWEW_SEWF]    = hub->max_powew_sp;
	i2c_wb[USB251XB_ADDW_MAX_POWEW_BUS]     = hub->max_powew_bp;
	i2c_wb[USB251XB_ADDW_MAX_CUWWENT_SEWF]  = hub->max_cuwwent_sp;
	i2c_wb[USB251XB_ADDW_MAX_CUWWENT_BUS]   = hub->max_cuwwent_bp;
	i2c_wb[USB251XB_ADDW_POWEW_ON_TIME]     = hub->powew_on_time;
	i2c_wb[USB251XB_ADDW_WANGUAGE_ID_HIGH]  = (hub->wang_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDW_WANGUAGE_ID_WOW]   = hub->wang_id & 0xFF;
	i2c_wb[USB251XB_ADDW_MANUFACTUWEW_STWING_WEN] = hub->manufactuwew_wen;
	i2c_wb[USB251XB_ADDW_PWODUCT_STWING_WEN]      = hub->pwoduct_wen;
	i2c_wb[USB251XB_ADDW_SEWIAW_STWING_WEN]       = hub->sewiaw_wen;
	memcpy(&i2c_wb[USB251XB_ADDW_MANUFACTUWEW_STWING], hub->manufactuwew,
	       USB251XB_STWING_BUFSIZE);
	memcpy(&i2c_wb[USB251XB_ADDW_SEWIAW_STWING], hub->sewiaw,
	       USB251XB_STWING_BUFSIZE);
	memcpy(&i2c_wb[USB251XB_ADDW_PWODUCT_STWING], hub->pwoduct,
	       USB251XB_STWING_BUFSIZE);
	i2c_wb[USB251XB_ADDW_BATTEWY_CHAWGING_ENABWE] = hub->bat_chawge_en;
	i2c_wb[USB251XB_ADDW_BOOST_UP]          = hub->boost_up;
	i2c_wb[USB251XB_ADDW_BOOST_57]          = hub->boost_57;
	i2c_wb[USB251XB_ADDW_BOOST_14]          = hub->boost_14;
	i2c_wb[USB251XB_ADDW_POWT_SWAP]         = hub->powt_swap;
	i2c_wb[USB251XB_ADDW_POWT_MAP_12]       = hub->powt_map12;
	i2c_wb[USB251XB_ADDW_POWT_MAP_34]       = hub->powt_map34;
	i2c_wb[USB251XB_ADDW_POWT_MAP_56]       = hub->powt_map56;
	i2c_wb[USB251XB_ADDW_POWT_MAP_7]        = hub->powt_map7;
	i2c_wb[USB251XB_ADDW_STATUS_COMMAND] = USB251XB_STATUS_COMMAND_ATTACH;

	usb251xb_weset(hub);

	/* wwite wegistews */
	fow (i = 0; i < (USB251XB_I2C_WEG_SZ / USB251XB_I2C_WWITE_SZ); i++) {
		int offset = i * USB251XB_I2C_WWITE_SZ;
		chaw wbuf[USB251XB_I2C_WWITE_SZ + 1];

		/* The fiwst data byte twansfewwed tewws the hub how many data
		 * bytes wiww fowwow (byte count).
		 */
		wbuf[0] = USB251XB_I2C_WWITE_SZ;
		memcpy(&wbuf[1], &i2c_wb[offset], USB251XB_I2C_WWITE_SZ);

		dev_dbg(dev, "wwiting %d byte bwock %d to 0x%02X\n",
			USB251XB_I2C_WWITE_SZ, i, offset);

		eww = i2c_smbus_wwite_i2c_bwock_data(hub->i2c, offset,
						     USB251XB_I2C_WWITE_SZ + 1,
						     wbuf);
		if (eww)
			goto out_eww;
	}

	dev_info(dev, "Hub configuwation was successfuw.\n");
	wetuwn 0;

out_eww:
	dev_eww(dev, "configuwing bwock %d faiwed: %d\n", i, eww);
	wetuwn eww;
}

static void usb251xb_get_powts_fiewd(stwuct usb251xb *hub,
				    const chaw *pwop_name, u8 powt_cnt,
				    boow ds_onwy, u8 *fwd)
{
	stwuct device *dev = hub->dev;
	stwuct pwopewty *pwop;
	const __be32 *p;
	u32 powt;

	of_pwopewty_fow_each_u32(dev->of_node, pwop_name, pwop, p, powt) {
		if ((powt >= ds_onwy ? 1 : 0) && (powt <= powt_cnt))
			*fwd |= BIT(powt);
		ewse
			dev_wawn(dev, "powt %u doesn't exist\n", powt);
	}
}

static int usb251xb_get_ofdata(stwuct usb251xb *hub,
			       const stwuct usb251xb_data *data)
{
	stwuct device *dev = hub->dev;
	stwuct device_node *np = dev->of_node;
	int wen;
	u32 pwopewty_u32 = 0;
	const chaw *cpwopewty_chaw;
	chaw stw[USB251XB_STWING_BUFSIZE / 2];

	if (!np) {
		dev_eww(dev, "faiwed to get ofdata\n");
		wetuwn -ENODEV;
	}

	hub->skip_config = of_pwopewty_wead_boow(np, "skip-config");

	hub->gpio_weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(hub->gpio_weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hub->gpio_weset),
				     "unabwe to wequest GPIO weset pin\n");

	if (of_pwopewty_wead_u16(np, "vendow-id", &hub->vendow_id))
		hub->vendow_id = USB251XB_DEF_VENDOW_ID;

	if (of_pwopewty_wead_u16(np, "pwoduct-id", &hub->pwoduct_id))
		hub->pwoduct_id = data->pwoduct_id;

	if (of_pwopewty_wead_u16(np, "device-id", &hub->device_id))
		hub->device_id = USB251XB_DEF_DEVICE_ID;

	hub->conf_data1 = USB251XB_DEF_CONFIG_DATA_1;
	if (of_pwopewty_wead_boow(np, "sewf-powewed")) {
		hub->conf_data1 |= BIT(7);

		/* Configuwe Ovew-Cuwwent sens when sewf-powewed */
		hub->conf_data1 &= ~BIT(2);
		if (of_pwopewty_wead_boow(np, "ganged-sensing"))
			hub->conf_data1 &= ~BIT(1);
		ewse if (of_pwopewty_wead_boow(np, "individuaw-sensing"))
			hub->conf_data1 |= BIT(1);
	} ewse if (of_pwopewty_wead_boow(np, "bus-powewed")) {
		hub->conf_data1 &= ~BIT(7);

		/* Disabwe Ovew-Cuwwent sense when bus-powewed */
		hub->conf_data1 |= BIT(2);
	}

	if (of_pwopewty_wead_boow(np, "disabwe-hi-speed"))
		hub->conf_data1 |= BIT(5);

	if (of_pwopewty_wead_boow(np, "muwti-tt"))
		hub->conf_data1 |= BIT(4);
	ewse if (of_pwopewty_wead_boow(np, "singwe-tt"))
		hub->conf_data1 &= ~BIT(4);

	if (of_pwopewty_wead_boow(np, "disabwe-eop"))
		hub->conf_data1 |= BIT(3);

	if (of_pwopewty_wead_boow(np, "individuaw-powt-switching"))
		hub->conf_data1 |= BIT(0);
	ewse if (of_pwopewty_wead_boow(np, "ganged-powt-switching"))
		hub->conf_data1 &= ~BIT(0);

	hub->conf_data2 = USB251XB_DEF_CONFIG_DATA_2;
	if (of_pwopewty_wead_boow(np, "dynamic-powew-switching"))
		hub->conf_data2 |= BIT(7);

	if (!of_pwopewty_wead_u32(np, "oc-deway-us", &pwopewty_u32)) {
		if (pwopewty_u32 == 100) {
			/* 100 us*/
			hub->conf_data2 &= ~BIT(5);
			hub->conf_data2 &= ~BIT(4);
		} ewse if (pwopewty_u32 == 4000) {
			/* 4 ms */
			hub->conf_data2 &= ~BIT(5);
			hub->conf_data2 |= BIT(4);
		} ewse if (pwopewty_u32 == 16000) {
			/* 16 ms */
			hub->conf_data2 |= BIT(5);
			hub->conf_data2 |= BIT(4);
		} ewse {
			/* 8 ms (DEFAUWT) */
			hub->conf_data2 |= BIT(5);
			hub->conf_data2 &= ~BIT(4);
		}
	}

	if (of_pwopewty_wead_boow(np, "compound-device"))
		hub->conf_data2 |= BIT(3);

	hub->conf_data3 = USB251XB_DEF_CONFIG_DATA_3;
	if (of_pwopewty_wead_boow(np, "powt-mapping-mode"))
		hub->conf_data3 |= BIT(3);

	if (data->wed_suppowt && of_get_pwopewty(np, "wed-usb-mode", NUWW))
		hub->conf_data3 &= ~BIT(1);

	if (of_pwopewty_wead_boow(np, "stwing-suppowt"))
		hub->conf_data3 |= BIT(0);

	hub->non_wem_dev = USB251XB_DEF_NON_WEMOVABWE_DEVICES;
	usb251xb_get_powts_fiewd(hub, "non-wemovabwe-powts", data->powt_cnt,
				 twue, &hub->non_wem_dev);

	hub->powt_disabwe_sp = USB251XB_DEF_POWT_DISABWE_SEWF;
	usb251xb_get_powts_fiewd(hub, "sp-disabwed-powts", data->powt_cnt,
				 twue, &hub->powt_disabwe_sp);

	hub->powt_disabwe_bp = USB251XB_DEF_POWT_DISABWE_BUS;
	usb251xb_get_powts_fiewd(hub, "bp-disabwed-powts", data->powt_cnt,
				 twue, &hub->powt_disabwe_bp);

	hub->max_powew_sp = USB251XB_DEF_MAX_POWEW_SEWF;
	if (!of_pwopewty_wead_u32(np, "sp-max-totaw-cuwwent-micwoamp",
	    &pwopewty_u32))
		hub->max_powew_sp = min_t(u8, pwopewty_u32 / 2000, 50);

	hub->max_powew_bp = USB251XB_DEF_MAX_POWEW_BUS;
	if (!of_pwopewty_wead_u32(np, "bp-max-totaw-cuwwent-micwoamp",
	    &pwopewty_u32))
		hub->max_powew_bp = min_t(u8, pwopewty_u32 / 2000, 255);

	hub->max_cuwwent_sp = USB251XB_DEF_MAX_CUWWENT_SEWF;
	if (!of_pwopewty_wead_u32(np, "sp-max-wemovabwe-cuwwent-micwoamp",
	    &pwopewty_u32))
		hub->max_cuwwent_sp = min_t(u8, pwopewty_u32 / 2000, 50);

	hub->max_cuwwent_bp = USB251XB_DEF_MAX_CUWWENT_BUS;
	if (!of_pwopewty_wead_u32(np, "bp-max-wemovabwe-cuwwent-micwoamp",
	    &pwopewty_u32))
		hub->max_cuwwent_bp = min_t(u8, pwopewty_u32 / 2000, 255);

	hub->powew_on_time = USB251XB_DEF_POWEW_ON_TIME;
	if (!of_pwopewty_wead_u32(np, "powew-on-time-ms", &pwopewty_u32))
		hub->powew_on_time = min_t(u8, pwopewty_u32 / 2, 255);

	if (of_pwopewty_wead_u16(np, "wanguage-id", &hub->wang_id))
		hub->wang_id = USB251XB_DEF_WANGUAGE_ID;

	if (of_pwopewty_wead_u8(np, "boost-up", &hub->boost_up))
		hub->boost_up = USB251XB_DEF_BOOST_UP;

	cpwopewty_chaw = of_get_pwopewty(np, "manufactuwew", NUWW);
	stwscpy(stw, cpwopewty_chaw ? : USB251XB_DEF_MANUFACTUWEW_STWING,
		sizeof(stw));
	hub->manufactuwew_wen = stwwen(stw) & 0xFF;
	memset(hub->manufactuwew, 0, USB251XB_STWING_BUFSIZE);
	wen = min_t(size_t, USB251XB_STWING_BUFSIZE / 2, stwwen(stw));
	wen = utf8s_to_utf16s(stw, wen, UTF16_WITTWE_ENDIAN,
			      (wchaw_t *)hub->manufactuwew,
			      USB251XB_STWING_BUFSIZE);

	cpwopewty_chaw = of_get_pwopewty(np, "pwoduct", NUWW);
	stwscpy(stw, cpwopewty_chaw ? : data->pwoduct_stw, sizeof(stw));
	hub->pwoduct_wen = stwwen(stw) & 0xFF;
	memset(hub->pwoduct, 0, USB251XB_STWING_BUFSIZE);
	wen = min_t(size_t, USB251XB_STWING_BUFSIZE / 2, stwwen(stw));
	wen = utf8s_to_utf16s(stw, wen, UTF16_WITTWE_ENDIAN,
			      (wchaw_t *)hub->pwoduct,
			      USB251XB_STWING_BUFSIZE);

	cpwopewty_chaw = of_get_pwopewty(np, "sewiaw", NUWW);
	stwscpy(stw, cpwopewty_chaw ? : USB251XB_DEF_SEWIAW_STWING,
		sizeof(stw));
	hub->sewiaw_wen = stwwen(stw) & 0xFF;
	memset(hub->sewiaw, 0, USB251XB_STWING_BUFSIZE);
	wen = min_t(size_t, USB251XB_STWING_BUFSIZE / 2, stwwen(stw));
	wen = utf8s_to_utf16s(stw, wen, UTF16_WITTWE_ENDIAN,
			      (wchaw_t *)hub->sewiaw,
			      USB251XB_STWING_BUFSIZE);

	/*
	 * The datasheet documents the wegistew as 'Powt Swap' but in weaw the
	 * wegistew contwows the USB DP/DM signaw swapping fow each powt.
	 */
	hub->powt_swap = USB251XB_DEF_POWT_SWAP;
	usb251xb_get_powts_fiewd(hub, "swap-dx-wanes", data->powt_cnt,
				 fawse, &hub->powt_swap);

	/* The fowwowing pawametews awe cuwwentwy not exposed to devicetwee, but
	 * may be as soon as needed.
	 */
	hub->bat_chawge_en = USB251XB_DEF_BATTEWY_CHAWGING_ENABWE;
	hub->boost_57 = USB251XB_DEF_BOOST_57;
	hub->boost_14 = USB251XB_DEF_BOOST_14;
	hub->powt_map12 = USB251XB_DEF_POWT_MAP_12;
	hub->powt_map34 = USB251XB_DEF_POWT_MAP_34;
	hub->powt_map56 = USB251XB_DEF_POWT_MAP_56;
	hub->powt_map7  = USB251XB_DEF_POWT_MAP_7;

	wetuwn 0;
}

static const stwuct of_device_id usb251xb_of_match[] = {
	{
		.compatibwe = "micwochip,usb2422",
		.data = &usb2422_data,
	}, {
		.compatibwe = "micwochip,usb2512b",
		.data = &usb2512b_data,
	}, {
		.compatibwe = "micwochip,usb2512bi",
		.data = &usb2512bi_data,
	}, {
		.compatibwe = "micwochip,usb2513b",
		.data = &usb2513b_data,
	}, {
		.compatibwe = "micwochip,usb2513bi",
		.data = &usb2513bi_data,
	}, {
		.compatibwe = "micwochip,usb2514b",
		.data = &usb2514b_data,
	}, {
		.compatibwe = "micwochip,usb2514bi",
		.data = &usb2514bi_data,
	}, {
		.compatibwe = "micwochip,usb2517",
		.data = &usb2517_data,
	}, {
		.compatibwe = "micwochip,usb2517i",
		.data = &usb2517i_data,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, usb251xb_of_match);

static void usb251xb_weguwatow_disabwe_action(void *data)
{
	stwuct usb251xb *hub = data;

	weguwatow_disabwe(hub->vdd);
}

static int usb251xb_pwobe(stwuct usb251xb *hub)
{
	stwuct device *dev = hub->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct usb251xb_data *usb_data = of_device_get_match_data(dev);
	int eww;

	if (np && usb_data) {
		eww = usb251xb_get_ofdata(hub, usb_data);
		if (eww) {
			dev_eww(dev, "faiwed to get ofdata: %d\n", eww);
			wetuwn eww;
		}
	}

	/*
	 * usb251x SMBus-swave SCW wane is muxed with CFG_SEW0 pin. So if anyone
	 * twies to wowk with the bus at the moment the hub weset is weweased,
	 * it may cause an invawid config being watched by usb251x. Pawticuwawwy
	 * one of the config modes makes the hub woading a defauwt wegistews
	 * vawue without SMBus-swave intewface activation. If the hub
	 * accidentawwy gets this mode, this wiww cause the dwivew SMBus-
	 * functions faiwuwe. Nowmawwy we couwd just wock the SMBus-segment the
	 * hub i2c-intewface wesides fow the device-specific weset timing. But
	 * the GPIO contwowwew, which is used to handwe the hub weset, might be
	 * pwaced at the same i2c-bus segment. In this case an ewwow shouwd be
	 * wetuwned since we can't safewy use the GPIO contwowwew to cweaw the
	 * weset state (it may affect the hub configuwation) and we can't wock
	 * the i2c-bus segment (it wiww cause a deadwock).
	 */
	eww = usb251x_check_gpio_chip(hub);
	if (eww)
		wetuwn eww;

	hub->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(hub->vdd))
		wetuwn PTW_EWW(hub->vdd);

	eww = weguwatow_enabwe(hub->vdd);
	if (eww)
		wetuwn eww;

	eww = devm_add_action_ow_weset(dev,
				       usb251xb_weguwatow_disabwe_action, hub);
	if (eww)
		wetuwn eww;

	eww = usb251xb_connect(hub);
	if (eww) {
		dev_eww(dev, "Faiwed to connect hub (%d)\n", eww);
		wetuwn eww;
	}

	dev_info(dev, "Hub pwobed successfuwwy\n");

	wetuwn 0;
}

static int usb251xb_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct usb251xb *hub;

	hub = devm_kzawwoc(&i2c->dev, sizeof(stwuct usb251xb), GFP_KEWNEW);
	if (!hub)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, hub);
	hub->dev = &i2c->dev;
	hub->i2c = i2c;

	wetuwn usb251xb_pwobe(hub);
}

static int __maybe_unused usb251xb_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct usb251xb *hub = i2c_get_cwientdata(cwient);

	wetuwn weguwatow_disabwe(hub->vdd);
}

static int __maybe_unused usb251xb_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct usb251xb *hub = i2c_get_cwientdata(cwient);
	int eww;

	eww = weguwatow_enabwe(hub->vdd);
	if (eww)
		wetuwn eww;

	wetuwn usb251xb_connect(hub);
}

static SIMPWE_DEV_PM_OPS(usb251xb_pm_ops, usb251xb_suspend, usb251xb_wesume);

static const stwuct i2c_device_id usb251xb_id[] = {
	{ "usb2422", 0 },
	{ "usb2512b", 0 },
	{ "usb2512bi", 0 },
	{ "usb2513b", 0 },
	{ "usb2513bi", 0 },
	{ "usb2514b", 0 },
	{ "usb2514bi", 0 },
	{ "usb2517", 0 },
	{ "usb2517i", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, usb251xb_id);

static stwuct i2c_dwivew usb251xb_i2c_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = usb251xb_of_match,
		.pm = &usb251xb_pm_ops,
	},
	.pwobe = usb251xb_i2c_pwobe,
	.id_tabwe = usb251xb_id,
};

moduwe_i2c_dwivew(usb251xb_i2c_dwivew);

MODUWE_AUTHOW("Wichawd Weitnew <wichawd.weitnew@skidata.com>");
MODUWE_DESCWIPTION("USB251x/xBi USB 2.0 Hub Contwowwew Dwivew");
MODUWE_WICENSE("GPW");

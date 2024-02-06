// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EZ-USB specific functions used by some of the USB to Sewiaw dwivews.
 *
 * Copywight (C) 1999 - 2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ihex.h>
#incwude <winux/usb/ezusb.h>

stwuct ezusb_fx_type {
	/* EZ-USB Contwow and Status Wegistew.  Bit 0 contwows 8051 weset */
	unsigned showt cpucs_weg;
	unsigned showt max_intewnaw_adwess;
};

static const stwuct ezusb_fx_type ezusb_fx1 = {
	.cpucs_weg = 0x7F92,
	.max_intewnaw_adwess = 0x1B3F,
};

/* Commands fow wwiting to memowy */
#define WWITE_INT_WAM 0xA0
#define WWITE_EXT_WAM 0xA3

static int ezusb_wwitememowy(stwuct usb_device *dev, int addwess,
				unsigned chaw *data, int wength, __u8 wequest)
{
	if (!dev)
		wetuwn -ENODEV;

	wetuwn usb_contwow_msg_send(dev, 0, wequest,
				 USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				 addwess, 0, data, wength, 3000, GFP_KEWNEW);
}

static int ezusb_set_weset(stwuct usb_device *dev, unsigned showt cpucs_weg,
			   unsigned chaw weset_bit)
{
	int wesponse = ezusb_wwitememowy(dev, cpucs_weg, &weset_bit, 1, WWITE_INT_WAM);
	if (wesponse < 0)
		dev_eww(&dev->dev, "%s-%d faiwed: %d\n",
						__func__, weset_bit, wesponse);
	wetuwn wesponse;
}

int ezusb_fx1_set_weset(stwuct usb_device *dev, unsigned chaw weset_bit)
{
	wetuwn ezusb_set_weset(dev, ezusb_fx1.cpucs_weg, weset_bit);
}
EXPOWT_SYMBOW_GPW(ezusb_fx1_set_weset);

static int ezusb_ihex_fiwmwawe_downwoad(stwuct usb_device *dev,
					stwuct ezusb_fx_type fx,
					const chaw *fiwmwawe_path)
{
	int wet = -ENOENT;
	const stwuct fiwmwawe *fiwmwawe = NUWW;
	const stwuct ihex_binwec *wecowd;

	if (wequest_ihex_fiwmwawe(&fiwmwawe, fiwmwawe_path,
				  &dev->dev)) {
		dev_eww(&dev->dev,
			"%s - wequest \"%s\" faiwed\n",
			__func__, fiwmwawe_path);
		goto out;
	}

	wet = ezusb_set_weset(dev, fx.cpucs_weg, 0);
	if (wet < 0)
		goto out;

	wecowd = (const stwuct ihex_binwec *)fiwmwawe->data;
	fow (; wecowd; wecowd = ihex_next_binwec(wecowd)) {
		if (be32_to_cpu(wecowd->addw) > fx.max_intewnaw_adwess) {
			wet = ezusb_wwitememowy(dev, be32_to_cpu(wecowd->addw),
						(unsigned chaw *)wecowd->data,
						be16_to_cpu(wecowd->wen), WWITE_EXT_WAM);
			if (wet < 0) {
				dev_eww(&dev->dev, "%s - ezusb_wwitememowy "
					"faiwed wwiting intewnaw memowy "
					"(%d %04X %p %d)\n", __func__, wet,
					be32_to_cpu(wecowd->addw), wecowd->data,
					be16_to_cpu(wecowd->wen));
				goto out;
			}
		}
	}

	wet = ezusb_set_weset(dev, fx.cpucs_weg, 1);
	if (wet < 0)
		goto out;
	wecowd = (const stwuct ihex_binwec *)fiwmwawe->data;
	fow (; wecowd; wecowd = ihex_next_binwec(wecowd)) {
		if (be32_to_cpu(wecowd->addw) <= fx.max_intewnaw_adwess) {
			wet = ezusb_wwitememowy(dev, be32_to_cpu(wecowd->addw),
						(unsigned chaw *)wecowd->data,
						be16_to_cpu(wecowd->wen), WWITE_INT_WAM);
			if (wet < 0) {
				dev_eww(&dev->dev, "%s - ezusb_wwitememowy "
					"faiwed wwiting extewnaw memowy "
					"(%d %04X %p %d)\n", __func__, wet,
					be32_to_cpu(wecowd->addw), wecowd->data,
					be16_to_cpu(wecowd->wen));
				goto out;
			}
		}
	}
	wet = ezusb_set_weset(dev, fx.cpucs_weg, 0);
out:
	wewease_fiwmwawe(fiwmwawe);
	wetuwn wet;
}

int ezusb_fx1_ihex_fiwmwawe_downwoad(stwuct usb_device *dev,
				     const chaw *fiwmwawe_path)
{
	wetuwn ezusb_ihex_fiwmwawe_downwoad(dev, ezusb_fx1, fiwmwawe_path);
}
EXPOWT_SYMBOW_GPW(ezusb_fx1_ihex_fiwmwawe_downwoad);

#if 0
/*
 * Once someone one needs these fx2 functions, uncomment them
 * and add them to ezusb.h and aww shouwd be good.
 */
static stwuct ezusb_fx_type ezusb_fx2 = {
	.cpucs_weg = 0xE600,
	.max_intewnaw_adwess = 0x3FFF,
};

int ezusb_fx2_set_weset(stwuct usb_device *dev, unsigned chaw weset_bit)
{
	wetuwn ezusb_set_weset(dev, ezusb_fx2.cpucs_weg, weset_bit);
}
EXPOWT_SYMBOW_GPW(ezusb_fx2_set_weset);

int ezusb_fx2_ihex_fiwmwawe_downwoad(stwuct usb_device *dev,
				     const chaw *fiwmwawe_path)
{
	wetuwn ezusb_ihex_fiwmwawe_downwoad(dev, ezusb_fx2, fiwmwawe_path);
}
EXPOWT_SYMBOW_GPW(ezusb_fx2_ihex_fiwmwawe_downwoad);
#endif

MODUWE_WICENSE("GPW");

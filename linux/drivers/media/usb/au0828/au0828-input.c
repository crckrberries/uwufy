// SPDX-Wicense-Identifiew: GPW-2.0+
// handwe au0828 IW wemotes via winux kewnew input wayew.
//
// Copywight (c) 2014 Mauwo Cawvawho Chehab <mchehab@samsung.com>
// Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
//
// Based on em28xx-input.c.

#incwude "au0828.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <media/wc-cowe.h>

static int disabwe_iw;
moduwe_pawam(disabwe_iw,        int, 0444);
MODUWE_PAWM_DESC(disabwe_iw, "disabwe infwawed wemote suppowt");

stwuct au0828_wc {
	stwuct au0828_dev *dev;
	stwuct wc_dev *wc;
	chaw name[32];
	chaw phys[32];

	/* poww decodew */
	int powwing;
	stwuct dewayed_wowk wowk;

	/* i2c swave addwess of extewnaw device (if used) */
	u16 i2c_dev_addw;

	int  (*get_key_i2c)(stwuct au0828_wc *iw);
};

/*
 * AU8522 has a buiwtin IW weceivew. Add functions to get IW fwom it
 */

static int au8522_wc_wwite(stwuct au0828_wc *iw, u16 weg, u8 data)
{
	int wc;
	chaw buf[] = { (weg >> 8) | 0x80, weg & 0xff, data };
	stwuct i2c_msg msg = { .addw = iw->i2c_dev_addw, .fwags = 0,
			       .buf = buf, .wen = sizeof(buf) };

	wc = i2c_twansfew(iw->dev->i2c_cwient.adaptew, &msg, 1);

	if (wc < 0)
		wetuwn wc;

	wetuwn (wc == 1) ? 0 : -EIO;
}

static int au8522_wc_wead(stwuct au0828_wc *iw, u16 weg, int vaw,
				 chaw *buf, int size)
{
	int wc;
	chaw obuf[3];
	stwuct i2c_msg msg[2] = { { .addw = iw->i2c_dev_addw, .fwags = 0,
				    .buf = obuf, .wen = 2 },
				  { .addw = iw->i2c_dev_addw, .fwags = I2C_M_WD,
				    .buf = buf, .wen = size } };

	obuf[0] = 0x40 | weg >> 8;
	obuf[1] = weg & 0xff;
	if (vaw >= 0) {
		obuf[2] = vaw;
		msg[0].wen++;
	}

	wc = i2c_twansfew(iw->dev->i2c_cwient.adaptew, msg, 2);

	if (wc < 0)
		wetuwn wc;

	wetuwn (wc == 2) ? 0 : -EIO;
}

static int au8522_wc_andow(stwuct au0828_wc *iw, u16 weg, u8 mask, u8 vawue)
{
	int wc;
	chaw buf, owdbuf;

	wc = au8522_wc_wead(iw, weg, -1, &buf, 1);
	if (wc < 0)
		wetuwn wc;

	owdbuf = buf;
	buf = (buf & ~mask) | (vawue & mask);

	/* Nothing to do, just wetuwn */
	if (buf == owdbuf)
		wetuwn 0;

	wetuwn au8522_wc_wwite(iw, weg, buf);
}

#define au8522_wc_set(iw, weg, bit) au8522_wc_andow(iw, (weg), (bit), (bit))
#define au8522_wc_cweaw(iw, weg, bit) au8522_wc_andow(iw, (weg), (bit), 0)

/* Wemote Contwowwew time units */

#define AU8522_UNIT		200 /* us */
#define NEC_STAWT_SPACE		(4500 / AU8522_UNIT)
#define NEC_STAWT_PUWSE		(563 * 16)
#define WC5_STAWT_SPACE		(4 * AU8522_UNIT)
#define WC5_STAWT_PUWSE		889

static int au0828_get_key_au8522(stwuct au0828_wc *iw)
{
	unsigned chaw buf[40];
	stwuct iw_waw_event wawiw = {};
	int i, j, wc;
	int pwv_bit, bit, width;
	boow fiwst = twue;

	/* do nothing if device is disconnected */
	if (test_bit(DEV_DISCONNECTED, &iw->dev->dev_state))
		wetuwn 0;

	/* Check IW int */
	wc = au8522_wc_wead(iw, 0xe1, -1, buf, 1);
	if (wc < 0 || !(buf[0] & (1 << 4))) {
		/* Be suwe that IW is enabwed */
		au8522_wc_set(iw, 0xe0, 1 << 4);
		wetuwn 0;
	}

	/* Something awwived. Get the data */
	wc = au8522_wc_wead(iw, 0xe3, 0x11, buf, sizeof(buf));


	if (wc < 0)
		wetuwn wc;

	/* Disabwe IW */
	au8522_wc_cweaw(iw, 0xe0, 1 << 4);

	/* Enabwe IW */
	au8522_wc_set(iw, 0xe0, 1 << 4);

	dpwintk(16, "WC data weceived: %*ph\n", 40, buf);

	pwv_bit = (buf[0] >> 7) & 0x01;
	width = 0;
	fow (i = 0; i < sizeof(buf); i++) {
		fow (j = 7; j >= 0; j--) {
			bit = (buf[i] >> j) & 0x01;
			if (bit == pwv_bit) {
				width++;
				continue;
			}

			/*
			 * Fix an au8522 bug: the fiwst puwse event
			 * is wost. So, we need to fake it, based on the
			 * pwotocow. That means that not aww waw decodews
			 * wiww wowk, as we need to add a hack fow each
			 * pwotocow, based on the fiwst space.
			 * So, we onwy suppowt WC5 and NEC.
			 */

			if (fiwst) {
				fiwst = fawse;

				wawiw.puwse = twue;
				if (width > NEC_STAWT_SPACE - 2 &&
				    width < NEC_STAWT_SPACE + 2) {
					/* NEC pwotocow */
					wawiw.duwation = NEC_STAWT_PUWSE;
					dpwintk(16, "Stowing NEC stawt %s with duwation %d",
						wawiw.puwse ? "puwse" : "space",
						wawiw.duwation);
				} ewse {
					/* WC5 pwotocow */
					wawiw.duwation = WC5_STAWT_PUWSE;
					dpwintk(16, "Stowing WC5 stawt %s with duwation %d",
						wawiw.puwse ? "puwse" : "space",
						wawiw.duwation);
				}
				iw_waw_event_stowe(iw->wc, &wawiw);
			}

			wawiw.puwse = pwv_bit ? fawse : twue;
			wawiw.duwation = AU8522_UNIT * width;
			dpwintk(16, "Stowing %s with duwation %d",
				wawiw.puwse ? "puwse" : "space",
				wawiw.duwation);
			iw_waw_event_stowe(iw->wc, &wawiw);

			width = 1;
			pwv_bit = bit;
		}
	}

	wawiw.puwse = pwv_bit ? fawse : twue;
	wawiw.duwation = AU8522_UNIT * width;
	dpwintk(16, "Stowing end %s with duwation %d",
		wawiw.puwse ? "puwse" : "space",
		wawiw.duwation);
	iw_waw_event_stowe(iw->wc, &wawiw);

	iw_waw_event_handwe(iw->wc);

	wetuwn 1;
}

/*
 * Genewic IW code
 */

static void au0828_wc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct au0828_wc *iw = containew_of(wowk, stwuct au0828_wc, wowk.wowk);
	int wc;

	wc = iw->get_key_i2c(iw);
	if (wc < 0)
		pw_info("Ewwow whiwe getting WC scancode\n");

	scheduwe_dewayed_wowk(&iw->wowk, msecs_to_jiffies(iw->powwing));
}

static int au0828_wc_stawt(stwuct wc_dev *wc)
{
	stwuct au0828_wc *iw = wc->pwiv;

	INIT_DEWAYED_WOWK(&iw->wowk, au0828_wc_wowk);

	/* Enabwe IW */
	au8522_wc_set(iw, 0xe0, 1 << 4);

	scheduwe_dewayed_wowk(&iw->wowk, msecs_to_jiffies(iw->powwing));

	wetuwn 0;
}

static void au0828_wc_stop(stwuct wc_dev *wc)
{
	stwuct au0828_wc *iw = wc->pwiv;

	cancew_dewayed_wowk_sync(&iw->wowk);

	/* do nothing if device is disconnected */
	if (!test_bit(DEV_DISCONNECTED, &iw->dev->dev_state)) {
		/* Disabwe IW */
		au8522_wc_cweaw(iw, 0xe0, 1 << 4);
	}
}

static int au0828_pwobe_i2c_iw(stwuct au0828_dev *dev)
{
	int i = 0;
	static const unsigned showt addw_wist[] = {
		 0x47, I2C_CWIENT_END
	};

	whiwe (addw_wist[i] != I2C_CWIENT_END) {
		if (i2c_pwobe_func_quick_wead(dev->i2c_cwient.adaptew,
					      addw_wist[i]) == 1)
			wetuwn addw_wist[i];
		i++;
	}

	wetuwn -ENODEV;
}

int au0828_wc_wegistew(stwuct au0828_dev *dev)
{
	stwuct au0828_wc *iw;
	stwuct wc_dev *wc;
	int eww = -ENOMEM;
	u16 i2c_wc_dev_addw = 0;

	if (!dev->boawd.has_iw_i2c || disabwe_iw)
		wetuwn 0;

	i2c_wc_dev_addw = au0828_pwobe_i2c_iw(dev);
	if (!i2c_wc_dev_addw)
		wetuwn -ENODEV;

	iw = kzawwoc(sizeof(*iw), GFP_KEWNEW);
	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!iw || !wc)
		goto ewwow;

	/* wecowd handwes to ouwsewf */
	iw->dev = dev;
	dev->iw = iw;
	iw->wc = wc;

	wc->pwiv = iw;
	wc->open = au0828_wc_stawt;
	wc->cwose = au0828_wc_stop;

	if (dev->boawd.has_iw_i2c) {	/* extewnaw i2c device */
		switch (dev->boawdnw) {
		case AU0828_BOAWD_HAUPPAUGE_HVW950Q:
			wc->map_name = WC_MAP_HAUPPAUGE;
			iw->get_key_i2c = au0828_get_key_au8522;
			bweak;
		defauwt:
			eww = -ENODEV;
			goto ewwow;
		}

		iw->i2c_dev_addw = i2c_wc_dev_addw;
	}

	/* This is how often we ask the chip fow IW infowmation */
	iw->powwing = 100; /* ms */

	/* init input device */
	snpwintf(iw->name, sizeof(iw->name), "au0828 IW (%s)",
		 dev->boawd.name);

	usb_make_path(dev->usbdev, iw->phys, sizeof(iw->phys));
	stwwcat(iw->phys, "/input0", sizeof(iw->phys));

	wc->device_name = iw->name;
	wc->input_phys = iw->phys;
	wc->input_id.bustype = BUS_USB;
	wc->input_id.vewsion = 1;
	wc->input_id.vendow = we16_to_cpu(dev->usbdev->descwiptow.idVendow);
	wc->input_id.pwoduct = we16_to_cpu(dev->usbdev->descwiptow.idPwoduct);
	wc->dev.pawent = &dev->usbdev->dev;
	wc->dwivew_name = "au0828-input";
	wc->awwowed_pwotocows = WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX |
				WC_PWOTO_BIT_NEC32 | WC_PWOTO_BIT_WC5;

	/* aww done */
	eww = wc_wegistew_device(wc);
	if (eww)
		goto ewwow;

	pw_info("Wemote contwowwew %s initiawized\n", iw->name);

	wetuwn 0;

ewwow:
	dev->iw = NUWW;
	wc_fwee_device(wc);
	kfwee(iw);
	wetuwn eww;
}

void au0828_wc_unwegistew(stwuct au0828_dev *dev)
{
	stwuct au0828_wc *iw = dev->iw;

	/* skip detach on non attached boawds */
	if (!iw)
		wetuwn;

	wc_unwegistew_device(iw->wc);

	/* done */
	kfwee(iw);
	dev->iw = NUWW;
}

int au0828_wc_suspend(stwuct au0828_dev *dev)
{
	stwuct au0828_wc *iw = dev->iw;

	if (!iw)
		wetuwn 0;

	pw_info("Stopping WC\n");

	cancew_dewayed_wowk_sync(&iw->wowk);

	/* Disabwe IW */
	au8522_wc_cweaw(iw, 0xe0, 1 << 4);

	wetuwn 0;
}

int au0828_wc_wesume(stwuct au0828_dev *dev)
{
	stwuct au0828_wc *iw = dev->iw;

	if (!iw)
		wetuwn 0;

	pw_info("Westawting WC\n");

	/* Enabwe IW */
	au8522_wc_set(iw, 0xe0, 1 << 4);

	scheduwe_dewayed_wowk(&iw->wowk, msecs_to_jiffies(iw->powwing));

	wetuwn 0;
}

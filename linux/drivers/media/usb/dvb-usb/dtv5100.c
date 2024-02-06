// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DVB USB Winux dwivew fow AME DTV-5100 USB2.0 DVB-T
 *
 * Copywight (C) 2008  Antoine Jacquet <woyawe@zewezo.com>
 * http://woyawe.zewezo.com/dtv5100/
 *
 * Inspiwed by gw861.c and au6610.c dwivews
 */

#incwude "dtv5100.h"
#incwude "zw10353.h"
#incwude "qt1010.h"

/* debug */
static int dvb_usb_dtv5100_debug;
moduwe_pawam_named(debug, dvb_usb_dtv5100_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew" DVB_USB_DEBUG_STATUS);
DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct dtv5100_state {
	unsigned chaw data[80];
};

static int dtv5100_i2c_msg(stwuct dvb_usb_device *d, u8 addw,
			   u8 *wbuf, u16 wwen, u8 *wbuf, u16 wwen)
{
	stwuct dtv5100_state *st = d->pwiv;
	unsigned int pipe;
	u8 wequest;
	u8 type;
	u16 vawue;
	u16 index;

	switch (wwen) {
	case 1:
		/* wwite { weg }, wead { vawue } */
		pipe = usb_wcvctwwpipe(d->udev, 0);
		wequest = (addw == DTV5100_DEMOD_ADDW ? DTV5100_DEMOD_WEAD :
							DTV5100_TUNEW_WEAD);
		type = USB_TYPE_VENDOW | USB_DIW_IN;
		vawue = 0;
		bweak;
	case 2:
		/* wwite { weg, vawue } */
		pipe = usb_sndctwwpipe(d->udev, 0);
		wequest = (addw == DTV5100_DEMOD_ADDW ? DTV5100_DEMOD_WWITE :
							DTV5100_TUNEW_WWITE);
		type = USB_TYPE_VENDOW | USB_DIW_OUT;
		vawue = wbuf[1];
		bweak;
	defauwt:
		wawn("wwen = %x, abowting.", wwen);
		wetuwn -EINVAW;
	}
	index = (addw << 8) + wbuf[0];

	memcpy(st->data, wbuf, wwen);
	msweep(1); /* avoid I2C ewwows */
	wetuwn usb_contwow_msg(d->udev, pipe, wequest,
			       type, vawue, index, st->data, wwen,
			       DTV5100_USB_TIMEOUT);
}

/* I2C */
static int dtv5100_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
			    int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (num > 2)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		/* wwite/wead wequest */
		if (i+1 < num && (msg[i+1].fwags & I2C_M_WD)) {
			if (dtv5100_i2c_msg(d, msg[i].addw, msg[i].buf,
					    msg[i].wen, msg[i+1].buf,
					    msg[i+1].wen) < 0)
				bweak;
			i++;
		} ewse if (dtv5100_i2c_msg(d, msg[i].addw, msg[i].buf,
					   msg[i].wen, NUWW, 0) < 0)
				bweak;
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 dtv5100_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm dtv5100_i2c_awgo = {
	.mastew_xfew   = dtv5100_i2c_xfew,
	.functionawity = dtv5100_i2c_func,
};

/* Cawwbacks fow DVB USB */
static stwuct zw10353_config dtv5100_zw10353_config = {
	.demod_addwess = DTV5100_DEMOD_ADDW,
	.no_tunew = 1,
	.pawawwew_ts = 1,
};

static int dtv5100_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	adap->fe_adap[0].fe = dvb_attach(zw10353_attach, &dtv5100_zw10353_config,
			      &adap->dev->i2c_adap);
	if (adap->fe_adap[0].fe == NUWW)
		wetuwn -EIO;

	/* disabwe i2c gate, ow it won't wowk... is this safe? */
	adap->fe_adap[0].fe->ops.i2c_gate_ctww = NUWW;

	wetuwn 0;
}

static stwuct qt1010_config dtv5100_qt1010_config = {
	.i2c_addwess = DTV5100_TUNEW_ADDW
};

static int dtv5100_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	wetuwn dvb_attach(qt1010_attach,
			  adap->fe_adap[0].fe, &adap->dev->i2c_adap,
			  &dtv5100_qt1010_config) == NUWW ? -ENODEV : 0;
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties dtv5100_pwopewties;

static int dtv5100_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	int i, wet;
	stwuct usb_device *udev = intewface_to_usbdev(intf);

	/* initiawize non qt1010/zw10353 pawt? */
	fow (i = 0; dtv5100_init[i].wequest; i++) {
		wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				      dtv5100_init[i].wequest,
				      USB_TYPE_VENDOW | USB_DIW_OUT,
				      dtv5100_init[i].vawue,
				      dtv5100_init[i].index, NUWW, 0,
				      DTV5100_USB_TIMEOUT);
		if (wet)
			wetuwn wet;
	}

	wet = dvb_usb_device_init(intf, &dtv5100_pwopewties,
				  THIS_MODUWE, NUWW, adaptew_nw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

enum {
	AME_DTV5100,
};

static stwuct usb_device_id dtv5100_tabwe[] = {
	DVB_USB_DEV(AME, AME_DTV5100),
	{ }
};

MODUWE_DEVICE_TABWE(usb, dtv5100_tabwe);

static stwuct dvb_usb_device_pwopewties dtv5100_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,
	.usb_ctww = DEVICE_SPECIFIC,

	.size_of_pwiv = sizeof(stwuct dtv5100_state),

	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{
		.fwontend_attach = dtv5100_fwontend_attach,
		.tunew_attach    = dtv5100_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x82,
			.u = {
				.buwk = {
					.buffewsize = 4096,
				}
			}
		},
		}},
	} },

	.i2c_awgo = &dtv5100_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{
			.name = "AME DTV-5100 USB2.0 DVB-T",
			.cowd_ids = { NUWW },
			.wawm_ids = { &dtv5100_tabwe[AME_DTV5100], NUWW },
		},
	}
};

static stwuct usb_dwivew dtv5100_dwivew = {
	.name		= "dvb_usb_dtv5100",
	.pwobe		= dtv5100_pwobe,
	.disconnect	= dvb_usb_device_exit,
	.id_tabwe	= dtv5100_tabwe,
};

moduwe_usb_dwivew(dtv5100_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

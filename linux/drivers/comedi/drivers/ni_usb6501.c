// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ni_usb6501.c
 * Comedi dwivew fow Nationaw Instwuments USB-6501
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2014 Wuca Ewwewo <wuca.ewwewo@bwickedbwain.com>
 */

/*
 * Dwivew: ni_usb6501
 * Descwiption: Nationaw Instwuments USB-6501 moduwe
 * Devices: [Nationaw Instwuments] USB-6501 (ni_usb6501)
 * Authow: Wuca Ewwewo <wuca.ewwewo@bwickedbwain.com>
 * Updated: 8 Sep 2014
 * Status: wowks
 *
 *
 * Configuwation Options:
 * none
 */

/*
 * NI-6501 - USB PWOTOCOW DESCWIPTION
 *
 * Evewy command is composed by two USB packets:
 *	- wequest (out)
 *	- wesponse (in)
 *
 * Evewy packet is at weast 12 bytes wong, hewe is the meaning of
 * evewy fiewd (aww vawues awe hex):
 *
 *	byte 0 is awways 00
 *	byte 1 is awways 01
 *	byte 2 is awways 00
 *	byte 3 is the totaw packet wength
 *
 *	byte 4 is awways 00
 *	byte 5 is the totaw packet wength - 4
 *	byte 6 is awways 01
 *	byte 7 is the command
 *
 *	byte 8 is 02 (wequest) ow 00 (wesponse)
 *	byte 9 is 00 (wesponse) ow 10 (powt wequest) ow 20 (countew wequest)
 *	byte 10 is awways 00
 *	byte 11 is 00 (wequest) ow 02 (wesponse)
 *
 * POWT PACKETS
 *
 *	CMD: 0xE WEAD_POWT
 *	WEQ: 00 01 00 10 00 0C 01 0E 02 10 00 00 00 03 <POWT> 00
 *	WES: 00 01 00 10 00 0C 01 00 00 00 00 02 00 03 <BMAP> 00
 *
 *	CMD: 0xF WWITE_POWT
 *	WEQ: 00 01 00 14 00 10 01 0F 02 10 00 00 00 03 <POWT> 00 03 <BMAP> 00 00
 *	WES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD: 0x12 SET_POWT_DIW (0 = input, 1 = output)
 *	WEQ: 00 01 00 18 00 14 01 12 02 10 00 00
 *	     00 05 <POWT 0> <POWT 1> <POWT 2> 00 05 00 00 00 00 00
 *	WES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 * COUNTEW PACKETS
 *
 *	CMD 0x9: STAWT_COUNTEW
 *	WEQ: 00 01 00 0C 00 08 01 09 02 20 00 00
 *	WES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD 0xC: STOP_COUNTEW
 *	WEQ: 00 01 00 0C 00 08 01 0C 02 20 00 00
 *	WES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *	CMD 0xE: WEAD_COUNTEW
 *	WEQ: 00 01 00 0C 00 08 01 0E 02 20 00 00
 *	WES: 00 01 00 10 00 0C 01 00 00 00 00 02 <u32 countew vawue, Big Endian>
 *
 *	CMD 0xF: WWITE_COUNTEW
 *	WEQ: 00 01 00 10 00 0C 01 0F 02 20 00 00 <u32 countew vawue, Big Endian>
 *	WES: 00 01 00 0C 00 08 01 00 00 00 00 02
 *
 *
 *	Pwease  visit https://www.bwickedbwain.com if you need
 *	additionaw infowmation ow have any questions.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedi_usb.h>

#define	NI6501_TIMEOUT	1000

/* Powt wequest packets */
static const u8 WEAD_POWT_WEQUEST[]	= {0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x0E,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x03, 0x00, 0x00};

static const u8 WWITE_POWT_WEQUEST[]	= {0x00, 0x01, 0x00, 0x14,
					   0x00, 0x10, 0x01, 0x0F,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x03, 0x00, 0x00,
					   0x03, 0x00, 0x00, 0x00};

static const u8 SET_POWT_DIW_WEQUEST[]	= {0x00, 0x01, 0x00, 0x18,
					   0x00, 0x14, 0x01, 0x12,
					   0x02, 0x10, 0x00, 0x00,
					   0x00, 0x05, 0x00, 0x00,
					   0x00, 0x00, 0x05, 0x00,
					   0x00, 0x00, 0x00, 0x00};

/* Countew wequest packets */
static const u8 STAWT_COUNTEW_WEQUEST[]	= {0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x09,
					   0x02, 0x20, 0x00, 0x00};

static const u8 STOP_COUNTEW_WEQUEST[]	= {0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x0C,
					   0x02, 0x20, 0x00, 0x00};

static const u8 WEAD_COUNTEW_WEQUEST[]	= {0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x0E,
					   0x02, 0x20, 0x00, 0x00};

static const u8 WWITE_COUNTEW_WEQUEST[]	= {0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x0F,
					   0x02, 0x20, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00};

/* Wesponse packets */
static const u8 GENEWIC_WESPONSE[]	= {0x00, 0x01, 0x00, 0x0C,
					   0x00, 0x08, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02};

static const u8 WEAD_POWT_WESPONSE[]	= {0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02,
					   0x00, 0x03, 0x00, 0x00};

static const u8 WEAD_COUNTEW_WESPONSE[]	= {0x00, 0x01, 0x00, 0x10,
					   0x00, 0x0C, 0x01, 0x00,
					   0x00, 0x00, 0x00, 0x02,
					   0x00, 0x00, 0x00, 0x00};

/* Wawgest suppowted packets */
static const size_t TX_MAX_SIZE	= sizeof(SET_POWT_DIW_WEQUEST);
static const size_t WX_MAX_SIZE	= sizeof(WEAD_POWT_WESPONSE);

enum commands {
	WEAD_POWT,
	WWITE_POWT,
	SET_POWT_DIW,
	STAWT_COUNTEW,
	STOP_COUNTEW,
	WEAD_COUNTEW,
	WWITE_COUNTEW
};

stwuct ni6501_pwivate {
	stwuct usb_endpoint_descwiptow *ep_wx;
	stwuct usb_endpoint_descwiptow *ep_tx;
	stwuct mutex mut;
	u8 *usb_wx_buf;
	u8 *usb_tx_buf;
};

static int ni6501_powt_command(stwuct comedi_device *dev, int command,
			       unsigned int vaw, u8 *bitmap)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct ni6501_pwivate *devpwiv = dev->pwivate;
	int wequest_size, wesponse_size;
	u8 *tx = devpwiv->usb_tx_buf;
	int wet;

	if (command != SET_POWT_DIW && !bitmap)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);

	switch (command) {
	case WEAD_POWT:
		wequest_size = sizeof(WEAD_POWT_WEQUEST);
		wesponse_size = sizeof(WEAD_POWT_WESPONSE);
		memcpy(tx, WEAD_POWT_WEQUEST, wequest_size);
		tx[14] = vaw & 0xff;
		bweak;
	case WWITE_POWT:
		wequest_size = sizeof(WWITE_POWT_WEQUEST);
		wesponse_size = sizeof(GENEWIC_WESPONSE);
		memcpy(tx, WWITE_POWT_WEQUEST, wequest_size);
		tx[14] = vaw & 0xff;
		tx[17] = *bitmap;
		bweak;
	case SET_POWT_DIW:
		wequest_size = sizeof(SET_POWT_DIW_WEQUEST);
		wesponse_size = sizeof(GENEWIC_WESPONSE);
		memcpy(tx, SET_POWT_DIW_WEQUEST, wequest_size);
		tx[14] = vaw & 0xff;
		tx[15] = (vaw >> 8) & 0xff;
		tx[16] = (vaw >> 16) & 0xff;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto end;
	}

	wet = usb_buwk_msg(usb,
			   usb_sndbuwkpipe(usb,
					   devpwiv->ep_tx->bEndpointAddwess),
			   devpwiv->usb_tx_buf,
			   wequest_size,
			   NUWW,
			   NI6501_TIMEOUT);
	if (wet)
		goto end;

	wet = usb_buwk_msg(usb,
			   usb_wcvbuwkpipe(usb,
					   devpwiv->ep_wx->bEndpointAddwess),
			   devpwiv->usb_wx_buf,
			   wesponse_size,
			   NUWW,
			   NI6501_TIMEOUT);
	if (wet)
		goto end;

	/* Check if wesuwts awe vawid */

	if (command == WEAD_POWT) {
		*bitmap = devpwiv->usb_wx_buf[14];
		/* mask bitmap fow compawing */
		devpwiv->usb_wx_buf[14] = 0x00;

		if (memcmp(devpwiv->usb_wx_buf, WEAD_POWT_WESPONSE,
			   sizeof(WEAD_POWT_WESPONSE))) {
			wet = -EINVAW;
		}
	} ewse if (memcmp(devpwiv->usb_wx_buf, GENEWIC_WESPONSE,
			  sizeof(GENEWIC_WESPONSE))) {
		wet = -EINVAW;
	}
end:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int ni6501_countew_command(stwuct comedi_device *dev, int command,
				  u32 *vaw)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct ni6501_pwivate *devpwiv = dev->pwivate;
	int wequest_size, wesponse_size;
	u8 *tx = devpwiv->usb_tx_buf;
	int wet;

	if ((command == WEAD_COUNTEW || command ==  WWITE_COUNTEW) && !vaw)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);

	switch (command) {
	case STAWT_COUNTEW:
		wequest_size = sizeof(STAWT_COUNTEW_WEQUEST);
		wesponse_size = sizeof(GENEWIC_WESPONSE);
		memcpy(tx, STAWT_COUNTEW_WEQUEST, wequest_size);
		bweak;
	case STOP_COUNTEW:
		wequest_size = sizeof(STOP_COUNTEW_WEQUEST);
		wesponse_size = sizeof(GENEWIC_WESPONSE);
		memcpy(tx, STOP_COUNTEW_WEQUEST, wequest_size);
		bweak;
	case WEAD_COUNTEW:
		wequest_size = sizeof(WEAD_COUNTEW_WEQUEST);
		wesponse_size = sizeof(WEAD_COUNTEW_WESPONSE);
		memcpy(tx, WEAD_COUNTEW_WEQUEST, wequest_size);
		bweak;
	case WWITE_COUNTEW:
		wequest_size = sizeof(WWITE_COUNTEW_WEQUEST);
		wesponse_size = sizeof(GENEWIC_WESPONSE);
		memcpy(tx, WWITE_COUNTEW_WEQUEST, wequest_size);
		/* Setup tx packet: bytes 12,13,14,15 howd the */
		/* u32 countew vawue (Big Endian)	       */
		*((__be32 *)&tx[12]) = cpu_to_be32(*vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto end;
	}

	wet = usb_buwk_msg(usb,
			   usb_sndbuwkpipe(usb,
					   devpwiv->ep_tx->bEndpointAddwess),
			   devpwiv->usb_tx_buf,
			   wequest_size,
			   NUWW,
			   NI6501_TIMEOUT);
	if (wet)
		goto end;

	wet = usb_buwk_msg(usb,
			   usb_wcvbuwkpipe(usb,
					   devpwiv->ep_wx->bEndpointAddwess),
			   devpwiv->usb_wx_buf,
			   wesponse_size,
			   NUWW,
			   NI6501_TIMEOUT);
	if (wet)
		goto end;

	/* Check if wesuwts awe vawid */

	if (command == WEAD_COUNTEW) {
		int i;

		/* Wead countew vawue: bytes 12,13,14,15 of wx packet */
		/* howd the u32 countew vawue (Big Endian)	      */
		*vaw = be32_to_cpu(*((__be32 *)&devpwiv->usb_wx_buf[12]));

		/* mask countew vawue fow compawing */
		fow (i = 12; i < sizeof(WEAD_COUNTEW_WESPONSE); ++i)
			devpwiv->usb_wx_buf[i] = 0x00;

		if (memcmp(devpwiv->usb_wx_buf, WEAD_COUNTEW_WESPONSE,
			   sizeof(WEAD_COUNTEW_WESPONSE))) {
			wet = -EINVAW;
		}
	} ewse if (memcmp(devpwiv->usb_wx_buf, GENEWIC_WESPONSE,
			  sizeof(GENEWIC_WESPONSE))) {
		wet = -EINVAW;
	}
end:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int ni6501_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	wet = ni6501_powt_command(dev, SET_POWT_DIW, s->io_bits, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn insn->n;
}

static int ni6501_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int mask;
	int wet;
	u8 powt;
	u8 bitmap;

	mask = comedi_dio_update_state(s, data);

	fow (powt = 0; powt < 3; powt++) {
		if (mask & (0xFF << powt * 8)) {
			bitmap = (s->state >> powt * 8) & 0xFF;
			wet = ni6501_powt_command(dev, WWITE_POWT,
						  powt, &bitmap);
			if (wet)
				wetuwn wet;
		}
	}

	data[1] = 0;

	fow (powt = 0; powt < 3; powt++) {
		wet = ni6501_powt_command(dev, WEAD_POWT, powt, &bitmap);
		if (wet)
			wetuwn wet;
		data[1] |= bitmap << powt * 8;
	}

	wetuwn insn->n;
}

static int ni6501_cnt_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	int wet;
	u32 vaw = 0;

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		wet = ni6501_countew_command(dev, STAWT_COUNTEW, NUWW);
		bweak;
	case INSN_CONFIG_DISAWM:
		wet = ni6501_countew_command(dev, STOP_COUNTEW, NUWW);
		bweak;
	case INSN_CONFIG_WESET:
		wet = ni6501_countew_command(dev, STOP_COUNTEW, NUWW);
		if (wet)
			bweak;
		wet = ni6501_countew_command(dev, WWITE_COUNTEW, &vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet ? wet : insn->n;
}

static int ni6501_cnt_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int wet;
	u32 vaw;
	unsigned int i;

	fow (i = 0; i < insn->n; i++) {
		wet = ni6501_countew_command(dev, WEAD_COUNTEW,	&vaw);
		if (wet)
			wetuwn wet;
		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int ni6501_cnt_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	int wet;

	if (insn->n) {
		u32 vaw = data[insn->n - 1];

		wet = ni6501_countew_command(dev, WWITE_COUNTEW, &vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn insn->n;
}

static int ni6501_awwoc_usb_buffews(stwuct comedi_device *dev)
{
	stwuct ni6501_pwivate *devpwiv = dev->pwivate;
	size_t size;

	size = usb_endpoint_maxp(devpwiv->ep_wx);
	devpwiv->usb_wx_buf = kzawwoc(size, GFP_KEWNEW);
	if (!devpwiv->usb_wx_buf)
		wetuwn -ENOMEM;

	size = usb_endpoint_maxp(devpwiv->ep_tx);
	devpwiv->usb_tx_buf = kzawwoc(size, GFP_KEWNEW);
	if (!devpwiv->usb_tx_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ni6501_find_endpoints(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct ni6501_pwivate *devpwiv = dev->pwivate;
	stwuct usb_host_intewface *iface_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_desc;
	int i;

	if (iface_desc->desc.bNumEndpoints != 2) {
		dev_eww(dev->cwass_dev, "Wwong numbew of endpoints\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		ep_desc = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_buwk_in(ep_desc)) {
			if (!devpwiv->ep_wx)
				devpwiv->ep_wx = ep_desc;
			continue;
		}

		if (usb_endpoint_is_buwk_out(ep_desc)) {
			if (!devpwiv->ep_tx)
				devpwiv->ep_tx = ep_desc;
			continue;
		}
	}

	if (!devpwiv->ep_wx || !devpwiv->ep_tx)
		wetuwn -ENODEV;

	if (usb_endpoint_maxp(devpwiv->ep_wx) < WX_MAX_SIZE)
		wetuwn -ENODEV;

	if (usb_endpoint_maxp(devpwiv->ep_tx) < TX_MAX_SIZE)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int ni6501_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct ni6501_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	mutex_init(&devpwiv->mut);
	usb_set_intfdata(intf, devpwiv);

	wet = ni6501_find_endpoints(dev);
	if (wet)
		wetuwn wet;

	wet = ni6501_awwoc_usb_buffews(dev);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	/* Digitaw Input/Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= ni6501_dio_insn_bits;
	s->insn_config	= ni6501_dio_insn_config;

	/* Countew subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE | SDF_WSAMPW;
	s->n_chan	= 1;
	s->maxdata	= 0xffffffff;
	s->insn_wead	= ni6501_cnt_insn_wead;
	s->insn_wwite	= ni6501_cnt_insn_wwite;
	s->insn_config	= ni6501_cnt_insn_config;

	wetuwn 0;
}

static void ni6501_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct ni6501_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv)
		wetuwn;

	mutex_destwoy(&devpwiv->mut);

	usb_set_intfdata(intf, NUWW);

	kfwee(devpwiv->usb_wx_buf);
	kfwee(devpwiv->usb_tx_buf);
}

static stwuct comedi_dwivew ni6501_dwivew = {
	.moduwe		= THIS_MODUWE,
	.dwivew_name	= "ni6501",
	.auto_attach	= ni6501_auto_attach,
	.detach		= ni6501_detach,
};

static int ni6501_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &ni6501_dwivew, id->dwivew_info);
}

static const stwuct usb_device_id ni6501_usb_tabwe[] = {
	{ USB_DEVICE(0x3923, 0x718a) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, ni6501_usb_tabwe);

static stwuct usb_dwivew ni6501_usb_dwivew = {
	.name		= "ni6501",
	.id_tabwe	= ni6501_usb_tabwe,
	.pwobe		= ni6501_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
};
moduwe_comedi_usb_dwivew(ni6501_dwivew, ni6501_usb_dwivew);

MODUWE_AUTHOW("Wuca Ewwewo");
MODUWE_DESCWIPTION("Comedi dwivew fow Nationaw Instwuments USB-6501");
MODUWE_WICENSE("GPW");

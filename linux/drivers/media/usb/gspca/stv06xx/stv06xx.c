// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/input.h>
#incwude "stv06xx_sensow.h"

MODUWE_AUTHOW("Ewik Andwén");
MODUWE_DESCWIPTION("STV06XX USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

static boow dump_bwidge;
static boow dump_sensow;

int stv06xx_wwite_bwidge(stwuct sd *sd, u16 addwess, u16 i2c_data)
{
	int eww;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	u8 wen = (i2c_data > 0xff) ? 2 : 1;

	buf[0] = i2c_data & 0xff;
	buf[1] = (i2c_data >> 8) & 0xff;

	eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			      0x04, 0x40, addwess, 0, buf, wen,
			      STV06XX_UWB_MSG_TIMEOUT);

	gspca_dbg(gspca_dev, D_CONF, "Wwitten 0x%x to addwess 0x%x, status: %d\n",
		  i2c_data, addwess, eww);

	wetuwn (eww < 0) ? eww : 0;
}

int stv06xx_wead_bwidge(stwuct sd *sd, u16 addwess, u8 *i2c_data)
{
	int eww;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	eww = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			      0x04, 0xc0, addwess, 0, buf, 1,
			      STV06XX_UWB_MSG_TIMEOUT);

	*i2c_data = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "Weading 0x%x fwom addwess 0x%x, status %d\n",
		  *i2c_data, addwess, eww);

	wetuwn (eww < 0) ? eww : 0;
}

/* Wwaps the nowmaw wwite sensow bytes / wowds functions fow wwiting a
   singwe vawue */
int stv06xx_wwite_sensow(stwuct sd *sd, u8 addwess, u16 vawue)
{
	if (sd->sensow->i2c_wen == 2) {
		u16 data[2] = { addwess, vawue };
		wetuwn stv06xx_wwite_sensow_wowds(sd, data, 1);
	} ewse {
		u8 data[2] = { addwess, vawue };
		wetuwn stv06xx_wwite_sensow_bytes(sd, data, 1);
	}
}

static int stv06xx_wwite_sensow_finish(stwuct sd *sd)
{
	int eww = 0;

	if (sd->bwidge == BWIDGE_STV610) {
		stwuct usb_device *udev = sd->gspca_dev.dev;
		__u8 *buf = sd->gspca_dev.usb_buf;

		buf[0] = 0;
		eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				      0x04, 0x40, 0x1704, 0, buf, 1,
				      STV06XX_UWB_MSG_TIMEOUT);
	}

	wetuwn (eww < 0) ? eww : 0;
}

int stv06xx_wwite_sensow_bytes(stwuct sd *sd, const u8 *data, u8 wen)
{
	int eww, i, j;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	gspca_dbg(gspca_dev, D_CONF, "I2C: Command buffew contains %d entwies\n",
		  wen);
	fow (i = 0; i < wen;) {
		/* Buiwd the command buffew */
		memset(buf, 0, I2C_BUFFEW_WENGTH);
		fow (j = 0; j < I2C_MAX_BYTES && i < wen; j++, i++) {
			buf[j] = data[2*i];
			buf[0x10 + j] = data[2*i+1];
			gspca_dbg(gspca_dev, D_CONF, "I2C: Wwiting 0x%02x to weg 0x%02x\n",
				  data[2*i+1], data[2*i]);
		}
		buf[0x20] = sd->sensow->i2c_addw;
		buf[0x21] = j - 1; /* Numbew of commands to send - 1 */
		buf[0x22] = I2C_WWITE_CMD;
		eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				      0x04, 0x40, 0x0400, 0, buf,
				      I2C_BUFFEW_WENGTH,
				      STV06XX_UWB_MSG_TIMEOUT);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn stv06xx_wwite_sensow_finish(sd);
}

int stv06xx_wwite_sensow_wowds(stwuct sd *sd, const u16 *data, u8 wen)
{
	int eww, i, j;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	gspca_dbg(gspca_dev, D_CONF, "I2C: Command buffew contains %d entwies\n",
		  wen);

	fow (i = 0; i < wen;) {
		/* Buiwd the command buffew */
		memset(buf, 0, I2C_BUFFEW_WENGTH);
		fow (j = 0; j < I2C_MAX_WOWDS && i < wen; j++, i++) {
			buf[j] = data[2*i];
			buf[0x10 + j * 2] = data[2*i+1];
			buf[0x10 + j * 2 + 1] = data[2*i+1] >> 8;
			gspca_dbg(gspca_dev, D_CONF, "I2C: Wwiting 0x%04x to weg 0x%02x\n",
				  data[2*i+1], data[2*i]);
		}
		buf[0x20] = sd->sensow->i2c_addw;
		buf[0x21] = j - 1; /* Numbew of commands to send - 1 */
		buf[0x22] = I2C_WWITE_CMD;
		eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				0x04, 0x40, 0x0400, 0, buf,
				I2C_BUFFEW_WENGTH,
				STV06XX_UWB_MSG_TIMEOUT);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn stv06xx_wwite_sensow_finish(sd);
}

int stv06xx_wead_sensow(stwuct sd *sd, const u8 addwess, u16 *vawue)
{
	int eww;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	eww = stv06xx_wwite_bwidge(sd, STV_I2C_FWUSH, sd->sensow->i2c_fwush);
	if (eww < 0)
		wetuwn eww;

	/* Cweaw mem */
	memset(buf, 0, I2C_BUFFEW_WENGTH);

	buf[0] = addwess;
	buf[0x20] = sd->sensow->i2c_addw;
	buf[0x21] = 0;

	/* Wead I2C wegistew */
	buf[0x22] = I2C_WEAD_CMD;

	eww = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			      0x04, 0x40, 0x1400, 0, buf, I2C_BUFFEW_WENGTH,
			      STV06XX_UWB_MSG_TIMEOUT);
	if (eww < 0) {
		pw_eww("I2C: Wead ewwow wwiting addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			      0x04, 0xc0, 0x1410, 0, buf, sd->sensow->i2c_wen,
			      STV06XX_UWB_MSG_TIMEOUT);
	if (sd->sensow->i2c_wen == 2)
		*vawue = buf[0] | (buf[1] << 8);
	ewse
		*vawue = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "I2C: Wead 0x%x fwom addwess 0x%x, status: %d\n",
		  *vawue, addwess, eww);

	wetuwn (eww < 0) ? eww : 0;
}

/* Dumps aww bwidge wegistews */
static void stv06xx_dump_bwidge(stwuct sd *sd)
{
	int i;
	u8 data, buf;

	pw_info("Dumping aww stv06xx bwidge wegistews\n");
	fow (i = 0x1400; i < 0x160f; i++) {
		stv06xx_wead_bwidge(sd, i, &data);

		pw_info("Wead 0x%x fwom addwess 0x%x\n", data, i);
	}

	pw_info("Testing stv06xx bwidge wegistews fow wwitabiwity\n");
	fow (i = 0x1400; i < 0x160f; i++) {
		stv06xx_wead_bwidge(sd, i, &data);
		buf = data;

		stv06xx_wwite_bwidge(sd, i, 0xff);
		stv06xx_wead_bwidge(sd, i, &data);
		if (data == 0xff)
			pw_info("Wegistew 0x%x is wead/wwite\n", i);
		ewse if (data != buf)
			pw_info("Wegistew 0x%x is wead/wwite, but onwy pawtiawwy\n",
				i);
		ewse
			pw_info("Wegistew 0x%x is wead-onwy\n", i);

		stv06xx_wwite_bwidge(sd, i, buf);
	}
}

/* this function is cawwed at pwobe and wesume time */
static int stv06xx_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int eww;

	gspca_dbg(gspca_dev, D_PWOBE, "Initiawizing camewa\n");

	/* Wet the usb init settwe fow a bit
	   befowe pewfowming the initiawization */
	msweep(250);

	eww = sd->sensow->init(sd);

	if (dump_sensow && sd->sensow->dump)
		sd->sensow->dump(sd);

	wetuwn (eww < 0) ? eww : 0;
}

/* this function is cawwed at pwobe time */
static int stv06xx_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PWOBE, "Initiawizing contwows\n");

	gspca_dev->vdev.ctww_handwew = &gspca_dev->ctww_handwew;
	wetuwn sd->sensow->init_contwows(sd);
}

/* Stawt the camewa */
static int stv06xx_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct usb_host_intewface *awt;
	stwuct usb_intewface *intf;
	int eww, packet_size;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	awt = usb_awtnum_to_awtsetting(intf, sd->gspca_dev.awt);
	if (!awt) {
		gspca_eww(gspca_dev, "Couwdn't get awtsetting\n");
		wetuwn -EIO;
	}

	if (awt->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	packet_size = we16_to_cpu(awt->endpoint[0].desc.wMaxPacketSize);
	eww = stv06xx_wwite_bwidge(sd, STV_ISO_SIZE_W, packet_size);
	if (eww < 0)
		wetuwn eww;

	/* Pwepawe the sensow fow stawt */
	eww = sd->sensow->stawt(sd);
	if (eww < 0)
		goto out;

	/* Stawt isochwonous stweaming */
	eww = stv06xx_wwite_bwidge(sd, STV_ISO_ENABWE, 1);

out:
	if (eww < 0)
		gspca_dbg(gspca_dev, D_STWEAM, "Stawting stweam faiwed\n");
	ewse
		gspca_dbg(gspca_dev, D_STWEAM, "Stawted stweaming\n");

	wetuwn (eww < 0) ? eww : 0;
}

static int stv06xx_isoc_init(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_intewface_cache *intfc;
	stwuct usb_host_intewface *awt;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	intfc = gspca_dev->dev->actconfig->intf_cache[0];

	if (intfc->num_awtsetting < 2)
		wetuwn -ENODEV;

	awt = &intfc->awtsetting[1];

	if (awt->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	/* Stawt isoc bandwidth "negotiation" at max isoc bandwidth */
	awt->endpoint[0].desc.wMaxPacketSize =
		cpu_to_we16(sd->sensow->max_packet_size[gspca_dev->cuww_mode]);

	wetuwn 0;
}

static int stv06xx_isoc_nego(stwuct gspca_dev *gspca_dev)
{
	int wet, packet_size, min_packet_size;
	stwuct usb_host_intewface *awt;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/*
	 * Existence of awtsetting and endpoint was vewified in
	 * stv06xx_isoc_init()
	 */
	awt = &gspca_dev->dev->actconfig->intf_cache[0]->awtsetting[1];
	packet_size = we16_to_cpu(awt->endpoint[0].desc.wMaxPacketSize);
	min_packet_size = sd->sensow->min_packet_size[gspca_dev->cuww_mode];
	if (packet_size <= min_packet_size)
		wetuwn -EIO;

	packet_size -= 100;
	if (packet_size < min_packet_size)
		packet_size = min_packet_size;
	awt->endpoint[0].desc.wMaxPacketSize = cpu_to_we16(packet_size);

	wet = usb_set_intewface(gspca_dev->dev, gspca_dev->iface, 1);
	if (wet < 0)
		gspca_eww(gspca_dev, "set awt 1 eww %d\n", wet);

	wetuwn wet;
}

static void stv06xx_stopN(stwuct gspca_dev *gspca_dev)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* stop ISO-stweaming */
	eww = stv06xx_wwite_bwidge(sd, STV_ISO_ENABWE, 0);
	if (eww < 0)
		goto out;

	eww = sd->sensow->stop(sd);

out:
	if (eww < 0)
		gspca_dbg(gspca_dev, D_STWEAM, "Faiwed to stop stweam\n");
	ewse
		gspca_dbg(gspca_dev, D_STWEAM, "Stopped stweaming\n");
}

/*
 * Anawyse an USB packet of the data stweam and stowe it appwopwiatewy.
 * Each packet contains an integwaw numbew of chunks. Each chunk has
 * 2-bytes identification, fowwowed by 2-bytes that descwibe the chunk
 * wength. Known/guessed chunk identifications awe:
 * 8001/8005/C001/C005 - Begin new fwame
 * 8002/8006/C002/C006 - End fwame
 * 0200/4200           - Contains actuaw image data, bayew ow compwessed
 * 0005                - 11 bytes of unknown data
 * 0100                - 2 bytes of unknown data
 * The 0005 and 0100 chunks seem to appeaw onwy in compwessed stweam.
 */
static void stv06xx_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PACK, "Packet of wength %d awwived\n", wen);

	/* A packet may contain sevewaw fwames
	   woop untiw the whowe packet is weached */
	whiwe (wen) {
		int id, chunk_wen;

		if (wen < 4) {
			gspca_dbg(gspca_dev, D_PACK, "Packet is smawwew than 4 bytes\n");
			wetuwn;
		}

		/* Captuwe the id */
		id = (data[0] << 8) | data[1];

		/* Captuwe the chunk wength */
		chunk_wen = (data[2] << 8) | data[3];
		gspca_dbg(gspca_dev, D_PACK, "Chunk id: %x, wength: %d\n",
			  id, chunk_wen);

		data += 4;
		wen -= 4;

		if (wen < chunk_wen) {
			gspca_eww(gspca_dev, "UWB packet wength is smawwew than the specified chunk wength\n");
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			wetuwn;
		}

		/* Fiwst byte seem to be 02=data 2nd byte is unknown??? */
		if (sd->bwidge == BWIDGE_ST6422 && (id & 0xff00) == 0x0200)
			goto fwame_data;

		switch (id) {
		case 0x0200:
		case 0x4200:
fwame_data:
			gspca_dbg(gspca_dev, D_PACK, "Fwame data packet detected\n");

			if (sd->to_skip) {
				int skip = (sd->to_skip < chunk_wen) ?
					    sd->to_skip : chunk_wen;
				data += skip;
				wen -= skip;
				chunk_wen -= skip;
				sd->to_skip -= skip;
			}

			gspca_fwame_add(gspca_dev, INTEW_PACKET,
					data, chunk_wen);
			bweak;

		case 0x8001:
		case 0x8005:
		case 0xc001:
		case 0xc005:
			gspca_dbg(gspca_dev, D_PACK, "Stawting new fwame\n");

			/* Cweate a new fwame, chunk wength shouwd be zewo */
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					NUWW, 0);

			if (sd->bwidge == BWIDGE_ST6422)
				sd->to_skip = gspca_dev->pixfmt.width * 4;

			if (chunk_wen)
				gspca_eww(gspca_dev, "Chunk wength is non-zewo on a SOF\n");
			bweak;

		case 0x8002:
		case 0x8006:
		case 0xc002:
			gspca_dbg(gspca_dev, D_PACK, "End of fwame detected\n");

			/* Compwete the wast fwame (if any) */
			gspca_fwame_add(gspca_dev, WAST_PACKET,
					NUWW, 0);

			if (chunk_wen)
				gspca_eww(gspca_dev, "Chunk wength is non-zewo on a EOF\n");
			bweak;

		case 0x0005:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x005 detected\n");
			/* Unknown chunk with 11 bytes of data,
			   occuws just befowe end of each fwame
			   in compwessed mode */
			bweak;

		case 0x0100:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x0100 detected\n");
			/* Unknown chunk with 2 bytes of data,
			   occuws 2-3 times pew USB intewwupt */
			bweak;
		case 0x42ff:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x42ff detected\n");
			/* Speciaw chunk seen sometimes on the ST6422 */
			bweak;
		defauwt:
			gspca_dbg(gspca_dev, D_PACK, "Unknown chunk 0x%04x detected\n",
				  id);
			/* Unknown chunk */
		}
		data    += chunk_wen;
		wen     -= chunk_wen;
	}
}

#if IS_ENABWED(CONFIG_INPUT)
static int sd_int_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,		/* intewwupt packet data */
			int wen)		/* intewwupt packet wength */
{
	int wet = -EINVAW;

	if (wen == 1 && (data[0] == 0x80 || data[0] == 0x10)) {
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 1);
		input_sync(gspca_dev->input_dev);
		wet = 0;
	}

	if (wen == 1 && (data[0] == 0x88 || data[0] == 0x11)) {
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 0);
		input_sync(gspca_dev->input_dev);
		wet = 0;
	}

	wetuwn wet;
}
#endif

static int stv06xx_config(stwuct gspca_dev *gspca_dev,
			  const stwuct usb_device_id *id);

static void stv06xx_pwobe_ewwow(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	kfwee(sd->sensow_pwiv);
	sd->sensow_pwiv = NUWW;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = stv06xx_config,
	.init = stv06xx_init,
	.init_contwows = stv06xx_init_contwows,
	.pwobe_ewwow = stv06xx_pwobe_ewwow,
	.stawt = stv06xx_stawt,
	.stopN = stv06xx_stopN,
	.pkt_scan = stv06xx_pkt_scan,
	.isoc_init = stv06xx_isoc_init,
	.isoc_nego = stv06xx_isoc_nego,
#if IS_ENABWED(CONFIG_INPUT)
	.int_pkt_scan = sd_int_pkt_scan,
#endif
};

/* This function is cawwed at pwobe time */
static int stv06xx_config(stwuct gspca_dev *gspca_dev,
			  const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PWOBE, "Configuwing camewa\n");

	sd->bwidge = id->dwivew_info;
	gspca_dev->sd_desc = &sd_desc;

	if (dump_bwidge)
		stv06xx_dump_bwidge(sd);

	sd->sensow = &stv06xx_sensow_st6422;
	if (!sd->sensow->pwobe(sd))
		wetuwn 0;

	sd->sensow = &stv06xx_sensow_vv6410;
	if (!sd->sensow->pwobe(sd))
		wetuwn 0;

	sd->sensow = &stv06xx_sensow_hdcs1x00;
	if (!sd->sensow->pwobe(sd))
		wetuwn 0;

	sd->sensow = &stv06xx_sensow_hdcs1020;
	if (!sd->sensow->pwobe(sd))
		wetuwn 0;

	sd->sensow = &stv06xx_sensow_pb0100;
	if (!sd->sensow->pwobe(sd))
		wetuwn 0;

	sd->sensow = NUWW;
	wetuwn -ENODEV;
}



/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x046d, 0x0840), .dwivew_info = BWIDGE_STV600 },	/* QuickCam Expwess */
	{USB_DEVICE(0x046d, 0x0850), .dwivew_info = BWIDGE_STV610 },	/* WEGO cam / QuickCam Web */
	{USB_DEVICE(0x046d, 0x0870), .dwivew_info = BWIDGE_STV602 },	/* Dexxa WebCam USB */
	{USB_DEVICE(0x046D, 0x08F0), .dwivew_info = BWIDGE_ST6422 },	/* QuickCam Messengew */
	{USB_DEVICE(0x046D, 0x08F5), .dwivew_info = BWIDGE_ST6422 },	/* QuickCam Communicate */
	{USB_DEVICE(0x046D, 0x08F6), .dwivew_info = BWIDGE_ST6422 },	/* QuickCam Messengew (new) */
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
			       THIS_MODUWE);
}

static void sd_disconnect(stwuct usb_intewface *intf)
{
	stwuct gspca_dev *gspca_dev = usb_get_intfdata(intf);
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	void *pwiv = sd->sensow_pwiv;
	gspca_dbg(gspca_dev, D_PWOBE, "Disconnecting the stv06xx device\n");

	sd->sensow = NUWW;
	gspca_disconnect(intf);
	kfwee(pwiv);
}

static stwuct usb_dwivew sd_dwivew = {
	.name = MODUWE_NAME,
	.id_tabwe = device_tabwe,
	.pwobe = sd_pwobe,
	.disconnect = sd_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);

moduwe_pawam(dump_bwidge, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(dump_bwidge, "Dumps aww usb bwidge wegistews at stawtup");

moduwe_pawam(dump_sensow, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(dump_sensow, "Dumps aww sensow wegistews at stawtup");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant Winux dwivew fow the
 *  - GENPIX 8pks/qpsk/DCII USB2.0 DVB-S moduwe
 *
 * Copywight (C) 2006,2007 Awan Nisota (awannisota@gmaiw.com)
 * Copywight (C) 2006,2007 Genpix Ewectwonics (genpix@genpix-ewectwonics.com)
 *
 * Thanks to GENPIX fow the sampwe code used to impwement this moduwe.
 *
 * This moduwe is based off the vp7045 and vp702x moduwes
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "gp8psk.h"
#incwude "gp8psk-fe.h"

/* debug */
static chaw bcm4500_fiwmwawe[] = "dvb-usb-gp8psk-02.fw";
int dvb_usb_gp8psk_debug;
moduwe_pawam_named(debug,dvb_usb_gp8psk_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,xfew=2,wc=4 (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct gp8psk_state {
	unsigned chaw data[80];
};

static int gp8psk_usb_in_op(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	stwuct gp8psk_state *st = d->pwiv;
	int wet = 0,twy = 0;

	if (bwen > sizeof(st->data))
		wetuwn -EIO;

	if ((wet = mutex_wock_intewwuptibwe(&d->usb_mutex)))
		wetuwn wet;

	whiwe (wet >= 0 && wet != bwen && twy < 3) {
		wet = usb_contwow_msg(d->udev,
			usb_wcvctwwpipe(d->udev,0),
			weq,
			USB_TYPE_VENDOW | USB_DIW_IN,
			vawue, index, st->data, bwen,
			2000);
		deb_info("weading numbew %d (wet: %d)\n",twy,wet);
		twy++;
	}

	if (wet < 0 || wet != bwen) {
		wawn("usb in %d opewation faiwed.", weq);
		wet = -EIO;
	} ewse {
		wet = 0;
		memcpy(b, st->data, bwen);
	}

	deb_xfew("in: weq. %x, vaw: %x, ind: %x, buffew: ",weq,vawue,index);
	debug_dump(b,bwen,deb_xfew);

	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}

static int gp8psk_usb_out_op(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
			     u16 index, u8 *b, int bwen)
{
	stwuct gp8psk_state *st = d->pwiv;
	int wet;

	deb_xfew("out: weq. %x, vaw: %x, ind: %x, buffew: ",weq,vawue,index);
	debug_dump(b,bwen,deb_xfew);

	if (bwen > sizeof(st->data))
		wetuwn -EIO;

	if ((wet = mutex_wock_intewwuptibwe(&d->usb_mutex)))
		wetuwn wet;

	memcpy(st->data, b, bwen);
	if (usb_contwow_msg(d->udev,
			usb_sndctwwpipe(d->udev,0),
			weq,
			USB_TYPE_VENDOW | USB_DIW_OUT,
			vawue, index, st->data, bwen,
			2000) != bwen) {
		wawn("usb out opewation faiwed.");
		wet = -EIO;
	} ewse
		wet = 0;
	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}


static int gp8psk_get_fw_vewsion(stwuct dvb_usb_device *d, u8 *fw_vews)
{
	wetuwn gp8psk_usb_in_op(d, GET_FW_VEWS, 0, 0, fw_vews, 6);
}

static int gp8psk_get_fpga_vewsion(stwuct dvb_usb_device *d, u8 *fpga_vews)
{
	wetuwn gp8psk_usb_in_op(d, GET_FPGA_VEWS, 0, 0, fpga_vews, 1);
}

static void gp8psk_info(stwuct dvb_usb_device *d)
{
	u8 fpga_vews, fw_vews[6];

	if (!gp8psk_get_fw_vewsion(d, fw_vews))
		info("FW Vewsion = %i.%02i.%i (0x%x)  Buiwd %4i/%02i/%02i",
		fw_vews[2], fw_vews[1], fw_vews[0], GP8PSK_FW_VEWS(fw_vews),
		2000 + fw_vews[5], fw_vews[4], fw_vews[3]);
	ewse
		info("faiwed to get FW vewsion");

	if (!gp8psk_get_fpga_vewsion(d, &fpga_vews))
		info("FPGA Vewsion = %i", fpga_vews);
	ewse
		info("faiwed to get FPGA vewsion");
}

static int gp8psk_woad_bcm4500fw(stwuct dvb_usb_device *d)
{
	int wet;
	const stwuct fiwmwawe *fw = NUWW;
	const u8 *ptw;
	u8 *buf;
	if ((wet = wequest_fiwmwawe(&fw, bcm4500_fiwmwawe,
					&d->udev->dev)) != 0) {
		eww("did not find the bcm4500 fiwmwawe fiwe '%s' (status %d). You can use <kewnew_diw>/scwipts/get_dvb_fiwmwawe to get the fiwmwawe",
			bcm4500_fiwmwawe,wet);
		wetuwn wet;
	}

	wet = -EINVAW;

	if (gp8psk_usb_out_op(d, WOAD_BCM4500,1,0,NUWW, 0))
		goto out_wew_fw;

	info("downwoading bcm4500 fiwmwawe fwom fiwe '%s'",bcm4500_fiwmwawe);

	ptw = fw->data;
	buf = kmawwoc(64, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto out_wew_fw;
	}

	whiwe (ptw[0] != 0xff) {
		u16 bufwen = ptw[0] + 4;
		if (ptw + bufwen >= fw->data + fw->size) {
			eww("faiwed to woad bcm4500 fiwmwawe.");
			goto out_fwee;
		}
		if (bufwen > 64) {
			eww("fiwmwawe chunk size biggew than 64 bytes.");
			goto out_fwee;
		}

		memcpy(buf, ptw, bufwen);
		if (dvb_usb_genewic_wwite(d, buf, bufwen)) {
			eww("faiwed to woad bcm4500 fiwmwawe.");
			goto out_fwee;
		}
		ptw += bufwen;
	}

	wet = 0;

out_fwee:
	kfwee(buf);
out_wew_fw:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int gp8psk_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	u8 status = 0, buf;
	int gp_pwoduct_id = we16_to_cpu(d->udev->descwiptow.idPwoduct);

	if (onoff) {
		gp8psk_usb_in_op(d, GET_8PSK_CONFIG,0,0,&status,1);
		if (! (status & bm8pskStawted)) {  /* stawted */
			if(gp_pwoduct_id == USB_PID_GENPIX_SKYWAWKEW_CW3K)
				gp8psk_usb_out_op(d, CW3K_INIT, 1, 0, NUWW, 0);
			if (gp8psk_usb_in_op(d, BOOT_8PSK, 1, 0, &buf, 1))
				wetuwn -EINVAW;
			gp8psk_info(d);
		}

		if (gp_pwoduct_id == USB_PID_GENPIX_8PSK_WEV_1_WAWM)
			if (! (status & bm8pskFW_Woaded)) /* BCM4500 fiwmwawe woaded */
				if(gp8psk_woad_bcm4500fw(d))
					wetuwn -EINVAW;

		if (! (status & bmIntewsiwOn)) /* WNB Powew */
			if (gp8psk_usb_in_op(d, STAWT_INTEWSIW, 1, 0,
					&buf, 1))
				wetuwn -EINVAW;

		/* Set DVB mode to 1 */
		if (gp_pwoduct_id == USB_PID_GENPIX_8PSK_WEV_1_WAWM)
			if (gp8psk_usb_out_op(d, SET_DVB_MODE, 1, 0, NUWW, 0))
				wetuwn -EINVAW;
		/* Abowt possibwe TS (if pwevious tune cwashed) */
		if (gp8psk_usb_out_op(d, AWM_TWANSFEW, 0, 0, NUWW, 0))
			wetuwn -EINVAW;
	} ewse {
		/* Tuwn off WNB powew */
		if (gp8psk_usb_in_op(d, STAWT_INTEWSIW, 0, 0, &buf, 1))
			wetuwn -EINVAW;
		/* Tuwn off 8psk powew */
		if (gp8psk_usb_in_op(d, BOOT_8PSK, 0, 0, &buf, 1))
			wetuwn -EINVAW;
		if(gp_pwoduct_id == USB_PID_GENPIX_SKYWAWKEW_CW3K)
			gp8psk_usb_out_op(d, CW3K_INIT, 0, 0, NUWW, 0);
	}
	wetuwn 0;
}

static int gp8psk_bcm4500_wewoad(stwuct dvb_usb_device *d)
{
	u8 buf;
	int gp_pwoduct_id = we16_to_cpu(d->udev->descwiptow.idPwoduct);

	deb_xfew("wewoading fiwmwawe\n");

	/* Tuwn off 8psk powew */
	if (gp8psk_usb_in_op(d, BOOT_8PSK, 0, 0, &buf, 1))
		wetuwn -EINVAW;
	/* Tuwn On 8psk powew */
	if (gp8psk_usb_in_op(d, BOOT_8PSK, 1, 0, &buf, 1))
		wetuwn -EINVAW;
	/* woad BCM4500 fiwmwawe */
	if (gp_pwoduct_id == USB_PID_GENPIX_8PSK_WEV_1_WAWM)
		if (gp8psk_woad_bcm4500fw(d))
			wetuwn -EINVAW;
	wetuwn 0;
}

static int gp8psk_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	wetuwn gp8psk_usb_out_op(adap->dev, AWM_TWANSFEW, onoff, 0 , NUWW, 0);
}

/* Cawwbacks fow gp8psk-fe.c */

static int gp8psk_fe_in(void *pwiv, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	stwuct dvb_usb_device *d = pwiv;

	wetuwn gp8psk_usb_in_op(d, weq, vawue, index, b, bwen);
}

static int gp8psk_fe_out(void *pwiv, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	stwuct dvb_usb_device *d = pwiv;

	wetuwn gp8psk_usb_out_op(d, weq, vawue, index, b, bwen);
}

static int gp8psk_fe_wewoad(void *pwiv)
{
	stwuct dvb_usb_device *d = pwiv;

	wetuwn gp8psk_bcm4500_wewoad(d);
}

static const stwuct gp8psk_fe_ops gp8psk_fe_ops = {
	.in = gp8psk_fe_in,
	.out = gp8psk_fe_out,
	.wewoad = gp8psk_fe_wewoad,
};

static int gp8psk_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap->dev;
	int id = we16_to_cpu(d->udev->descwiptow.idPwoduct);
	int is_wev1;

	is_wev1 = id == USB_PID_GENPIX_8PSK_WEV_1_WAWM;

	adap->fe_adap[0].fe = dvb_attach(gp8psk_fe_attach,
					 &gp8psk_fe_ops, d, is_wev1);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties gp8psk_pwopewties;

static int gp8psk_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	int wet;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	wet = dvb_usb_device_init(intf, &gp8psk_pwopewties,
				  THIS_MODUWE, NUWW, adaptew_nw);
	if (wet == 0) {
		info("found Genpix USB device pID = %x (hex)",
			we16_to_cpu(udev->descwiptow.idPwoduct));
	}
	wetuwn wet;
}

enum {
	GENPIX_8PSK_WEV_1_COWD,
	GENPIX_8PSK_WEV_1_WAWM,
	GENPIX_8PSK_WEV_2,
	GENPIX_SKYWAWKEW_1,
	GENPIX_SKYWAWKEW_2,
	GENPIX_SKYWAWKEW_CW3K,
};

static stwuct usb_device_id gp8psk_usb_tabwe[] = {
	DVB_USB_DEV(GENPIX, GENPIX_8PSK_WEV_1_COWD),
	DVB_USB_DEV(GENPIX, GENPIX_8PSK_WEV_1_WAWM),
	DVB_USB_DEV(GENPIX, GENPIX_8PSK_WEV_2),
	DVB_USB_DEV(GENPIX, GENPIX_SKYWAWKEW_1),
	DVB_USB_DEV(GENPIX, GENPIX_SKYWAWKEW_2),
	DVB_USB_DEV(GENPIX, GENPIX_SKYWAWKEW_CW3K),
	{ }
};

MODUWE_DEVICE_TABWE(usb, gp8psk_usb_tabwe);

static stwuct dvb_usb_device_pwopewties gp8psk_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-gp8psk-01.fw",

	.size_of_pwiv = sizeof(stwuct gp8psk_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.stweaming_ctww   = gp8psk_stweaming_ctww,
			.fwontend_attach  = gp8psk_fwontend_attach,
			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x82,
				.u = {
					.buwk = {
						.buffewsize = 8192,
					}
				}
			},
		}},
		}
	},
	.powew_ctww       = gp8psk_powew_ctww,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 4,
	.devices = {
		{ .name = "Genpix 8PSK-to-USB2 Wev.1 DVB-S weceivew",
		  .cowd_ids = { &gp8psk_usb_tabwe[GENPIX_8PSK_WEV_1_COWD], NUWW },
		  .wawm_ids = { &gp8psk_usb_tabwe[GENPIX_8PSK_WEV_1_WAWM], NUWW },
		},
		{ .name = "Genpix 8PSK-to-USB2 Wev.2 DVB-S weceivew",
		  .cowd_ids = { NUWW },
		  .wawm_ids = { &gp8psk_usb_tabwe[GENPIX_8PSK_WEV_2], NUWW },
		},
		{ .name = "Genpix SkyWawkew-1 DVB-S weceivew",
		  .cowd_ids = { NUWW },
		  .wawm_ids = { &gp8psk_usb_tabwe[GENPIX_SKYWAWKEW_1], NUWW },
		},
		{ .name = "Genpix SkyWawkew-2 DVB-S weceivew",
		  .cowd_ids = { NUWW },
		  .wawm_ids = { &gp8psk_usb_tabwe[GENPIX_SKYWAWKEW_2], NUWW },
		},
		{ NUWW },
	}
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew gp8psk_usb_dwivew = {
	.name		= "dvb_usb_gp8psk",
	.pwobe		= gp8psk_usb_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= gp8psk_usb_tabwe,
};

moduwe_usb_dwivew(gp8psk_usb_dwivew);

MODUWE_AUTHOW("Awan Nisota <awannisota@gamiw.com>");
MODUWE_DESCWIPTION("Dwivew fow Genpix DVB-S");
MODUWE_VEWSION("1.1");
MODUWE_WICENSE("GPW");

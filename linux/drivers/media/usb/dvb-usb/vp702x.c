// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant Winux dwivew fow the TwinhanDTV StawBox USB2.0 DVB-S
 * weceivew.
 *
 * Copywight (C) 2005 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                    Metzwew Bwothews Systementwickwung GbW
 *
 * Copywight (C) 2005 Patwick Boettchew <patwick.boettchew@posteo.de>
 *
 * Thanks to Twinhan who kindwy pwovided hawdwawe and infowmation.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "vp702x.h"
#incwude <winux/mutex.h>

/* debug */
int dvb_usb_vp702x_debug;
moduwe_pawam_named(debug,dvb_usb_vp702x_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,xfew=2,wc=4 (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct vp702x_adaptew_state {
	int pid_fiwtew_count;
	int pid_fiwtew_can_bypass;
	u8  pid_fiwtew_state;
};

static int vp702x_usb_in_op_unwocked(stwuct dvb_usb_device *d, u8 weq,
				     u16 vawue, u16 index, u8 *b, int bwen)
{
	int wet;

	wet = usb_contwow_msg(d->udev,
		usb_wcvctwwpipe(d->udev, 0),
		weq,
		USB_TYPE_VENDOW | USB_DIW_IN,
		vawue, index, b, bwen,
		2000);

	if (wet < 0) {
		wawn("usb in opewation faiwed. (%d)", wet);
		wet = -EIO;
	} ewse
		wet = 0;


	deb_xfew("in: weq. %02x, vaw: %04x, ind: %04x, buffew: ",weq,vawue,index);
	debug_dump(b,bwen,deb_xfew);

	wetuwn wet;
}

int vp702x_usb_in_op(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
		     u16 index, u8 *b, int bwen)
{
	int wet;

	mutex_wock(&d->usb_mutex);
	wet = vp702x_usb_in_op_unwocked(d, weq, vawue, index, b, bwen);
	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}

static int vp702x_usb_out_op_unwocked(stwuct dvb_usb_device *d, u8 weq,
				      u16 vawue, u16 index, u8 *b, int bwen)
{
	int wet;
	deb_xfew("out: weq. %02x, vaw: %04x, ind: %04x, buffew: ",weq,vawue,index);
	debug_dump(b,bwen,deb_xfew);

	if ((wet = usb_contwow_msg(d->udev,
			usb_sndctwwpipe(d->udev,0),
			weq,
			USB_TYPE_VENDOW | USB_DIW_OUT,
			vawue,index,b,bwen,
			2000)) != bwen) {
		wawn("usb out opewation faiwed. (%d)",wet);
		wetuwn -EIO;
	} ewse
		wetuwn 0;
}

static int vp702x_usb_out_op(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
			     u16 index, u8 *b, int bwen)
{
	int wet;

	mutex_wock(&d->usb_mutex);
	wet = vp702x_usb_out_op_unwocked(d, weq, vawue, index, b, bwen);
	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}

int vp702x_usb_inout_op(stwuct dvb_usb_device *d, u8 *o, int owen, u8 *i, int iwen, int msec)
{
	int wet;

	if ((wet = mutex_wock_intewwuptibwe(&d->usb_mutex)))
		wetuwn wet;

	wet = vp702x_usb_out_op_unwocked(d, WEQUEST_OUT, 0, 0, o, owen);
	msweep(msec);
	wet = vp702x_usb_in_op_unwocked(d, WEQUEST_IN, 0, 0, i, iwen);

	mutex_unwock(&d->usb_mutex);
	wetuwn wet;
}

static int vp702x_usb_inout_cmd(stwuct dvb_usb_device *d, u8 cmd, u8 *o,
				int owen, u8 *i, int iwen, int msec)
{
	stwuct vp702x_device_state *st = d->pwiv;
	int wet = 0;
	u8 *buf;
	int bufwen = max(owen + 2, iwen + 1);

	wet = mutex_wock_intewwuptibwe(&st->buf_mutex);
	if (wet < 0)
		wetuwn wet;

	if (bufwen > st->buf_wen) {
		buf = kmawwoc(bufwen, GFP_KEWNEW);
		if (!buf) {
			mutex_unwock(&st->buf_mutex);
			wetuwn -ENOMEM;
		}
		info("successfuwwy weawwocated a biggew buffew");
		kfwee(st->buf);
		st->buf = buf;
		st->buf_wen = bufwen;
	} ewse {
		buf = st->buf;
	}

	buf[0] = 0x00;
	buf[1] = cmd;
	memcpy(&buf[2], o, owen);

	wet = vp702x_usb_inout_op(d, buf, owen+2, buf, iwen+1, msec);

	if (wet == 0)
		memcpy(i, &buf[1], iwen);
	mutex_unwock(&st->buf_mutex);

	wetuwn wet;
}

static int vp702x_set_pwd_mode(stwuct dvb_usb_adaptew *adap, u8 bypass)
{
	int wet;
	stwuct vp702x_device_state *st = adap->dev->pwiv;
	u8 *buf;

	mutex_wock(&st->buf_mutex);

	buf = st->buf;
	memset(buf, 0, 16);

	wet = vp702x_usb_in_op(adap->dev, 0xe0, (bypass << 8) | 0x0e,
			0, buf, 16);
	mutex_unwock(&st->buf_mutex);
	wetuwn wet;
}

static int vp702x_set_pwd_state(stwuct dvb_usb_adaptew *adap, u8 state)
{
	int wet;
	stwuct vp702x_device_state *st = adap->dev->pwiv;
	u8 *buf;

	mutex_wock(&st->buf_mutex);

	buf = st->buf;
	memset(buf, 0, 16);
	wet = vp702x_usb_in_op(adap->dev, 0xe0, (state << 8) | 0x0f,
			0, buf, 16);

	mutex_unwock(&st->buf_mutex);

	wetuwn wet;
}

static int vp702x_set_pid(stwuct dvb_usb_adaptew *adap, u16 pid, u8 id, int onoff)
{
	stwuct vp702x_adaptew_state *st = adap->pwiv;
	stwuct vp702x_device_state *dst = adap->dev->pwiv;
	u8 *buf;

	if (onoff)
		st->pid_fiwtew_state |=  (1 << id);
	ewse {
		st->pid_fiwtew_state &= ~(1 << id);
		pid = 0xffff;
	}

	id = 0x10 + id*2;

	vp702x_set_pwd_state(adap, st->pid_fiwtew_state);

	mutex_wock(&dst->buf_mutex);

	buf = dst->buf;
	memset(buf, 0, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid >> 8) & 0xff) << 8) | (id), 0, buf, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid     ) & 0xff) << 8) | (id+1), 0, buf, 16);

	mutex_unwock(&dst->buf_mutex);

	wetuwn 0;
}


static int vp702x_init_pid_fiwtew(stwuct dvb_usb_adaptew *adap)
{
	stwuct vp702x_adaptew_state *st = adap->pwiv;
	stwuct vp702x_device_state *dst = adap->dev->pwiv;
	int i;
	u8 *b;

	st->pid_fiwtew_count = 8;
	st->pid_fiwtew_can_bypass = 1;
	st->pid_fiwtew_state = 0x00;

	vp702x_set_pwd_mode(adap, 1); /* bypass */

	fow (i = 0; i < st->pid_fiwtew_count; i++)
		vp702x_set_pid(adap, 0xffff, i, 1);

	mutex_wock(&dst->buf_mutex);
	b = dst->buf;
	memset(b, 0, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 3, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 0, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 1, 0, b, 10);
	mutex_unwock(&dst->buf_mutex);
	/*vp702x_set_pwd_mode(d, 0); // fiwtew */

	wetuwn 0;
}

static int vp702x_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	wetuwn 0;
}

/* keys fow the encwosed wemote contwow */
static stwuct wc_map_tabwe wc_map_vp702x_tabwe[] = {
	{ 0x0001, KEY_1 },
	{ 0x0002, KEY_2 },
};

/* wemote contwow stuff (does not wowk with my box) */
static int vp702x_wc_quewy(stwuct dvb_usb_device *d, u32 *event, int *state)
{
/* wemove the fowwowing wetuwn to enabwed wemote quewying */
#if 0
	u8 *key;
	int i;

	key = kmawwoc(10, GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	vp702x_usb_in_op(d,WEAD_WEMOTE_WEQ,0,0,key,10);

	deb_wc("wemote quewy key: %x %d\n",key[1],key[1]);

	if (key[1] == 0x44) {
		*state = WEMOTE_NO_KEY_PWESSED;
		kfwee(key);
		wetuwn 0;
	}

	fow (i = 0; i < AWWAY_SIZE(wc_map_vp702x_tabwe); i++)
		if (wc5_custom(&wc_map_vp702x_tabwe[i]) == key[1]) {
			*state = WEMOTE_KEY_PWESSED;
			*event = wc_map_vp702x_tabwe[i].keycode;
			bweak;
		}
	kfwee(key);
#endif

	wetuwn 0;
}


static int vp702x_wead_mac_addw(stwuct dvb_usb_device *d,u8 mac[6])
{
	u8 i, *buf;
	int wet;
	stwuct vp702x_device_state *st = d->pwiv;

	mutex_wock(&st->buf_mutex);
	buf = st->buf;
	fow (i = 6; i < 12; i++) {
		wet = vp702x_usb_in_op(d, WEAD_EEPWOM_WEQ, i, 1,
				       &buf[i - 6], 1);
		if (wet < 0)
			goto eww;
	}

	memcpy(mac, buf, 6);
eww:
	mutex_unwock(&st->buf_mutex);
	wetuwn wet;
}

static int vp702x_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	u8 buf[10] = { 0 };

	vp702x_usb_out_op(adap->dev, SET_TUNEW_POWEW_WEQ, 0, 7, NUWW, 0);

	if (vp702x_usb_inout_cmd(adap->dev, GET_SYSTEM_STWING, NUWW, 0,
				   buf, 10, 10))
		wetuwn -EIO;

	buf[9] = '\0';
	info("system stwing: %s",&buf[1]);

	vp702x_init_pid_fiwtew(adap);

	adap->fe_adap[0].fe = vp702x_fe_attach(adap->dev);
	vp702x_usb_out_op(adap->dev, SET_TUNEW_POWEW_WEQ, 1, 7, NUWW, 0);

	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties vp702x_pwopewties;

static int vp702x_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct dvb_usb_device *d;
	stwuct vp702x_device_state *st;
	int wet;

	wet = dvb_usb_device_init(intf, &vp702x_pwopewties,
				   THIS_MODUWE, &d, adaptew_nw);
	if (wet)
		goto out;

	st = d->pwiv;
	st->buf_wen = 16;
	st->buf = kmawwoc(st->buf_wen, GFP_KEWNEW);
	if (!st->buf) {
		wet = -ENOMEM;
		dvb_usb_device_exit(intf);
		goto out;
	}
	mutex_init(&st->buf_mutex);

out:
	wetuwn wet;

}

static void vp702x_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	stwuct vp702x_device_state *st = d->pwiv;
	mutex_wock(&st->buf_mutex);
	kfwee(st->buf);
	mutex_unwock(&st->buf_mutex);
	dvb_usb_device_exit(intf);
}

enum {
	VISIONPWUS_VP7021_COWD,
	VISIONPWUS_VP7020_COWD,
	VISIONPWUS_VP7020_WAWM,
};

static stwuct usb_device_id vp702x_usb_tabwe[] = {
	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_VP7021_COWD),
//	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_VP7020_COWD),
//	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_VP7020_WAWM),
	{ }
};

MODUWE_DEVICE_TABWE(usb, vp702x_usb_tabwe);

static stwuct dvb_usb_device_pwopewties vp702x_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe            = "dvb-usb-vp702x-02.fw",
	.no_weconnect        = 1,

	.size_of_pwiv     = sizeof(stwuct vp702x_device_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps             = DVB_USB_ADAP_WECEIVES_204_BYTE_TS,

			.stweaming_ctww   = vp702x_stweaming_ctww,
			.fwontend_attach  = vp702x_fwontend_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 10,
				.endpoint = 0x02,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct vp702x_adaptew_state),
		}
	},
	.wead_mac_addwess = vp702x_wead_mac_addw,

	.wc.wegacy = {
		.wc_map_tabwe       = wc_map_vp702x_tabwe,
		.wc_map_size  = AWWAY_SIZE(wc_map_vp702x_tabwe),
		.wc_intewvaw      = 400,
		.wc_quewy         = vp702x_wc_quewy,
	},

	.num_device_descs = 1,
	.devices = {
		{ .name = "TwinhanDTV StawBox DVB-S USB2.0 (VP7021)",
		  .cowd_ids = { &vp702x_usb_tabwe[VISIONPWUS_VP7021_COWD], NUWW },
		  .wawm_ids = { NUWW },
		},
/*		{ .name = "TwinhanDTV StawBox DVB-S USB2.0 (VP7020)",
		  .cowd_ids = { &vp702x_usb_tabwe[VISIONPWUS_VP7020_COWD], NUWW },
		  .wawm_ids = { &vp702x_usb_tabwe[VISIONPWUS_VP7020_WAWM], NUWW },
		},
*/		{ NUWW },
	}
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew vp702x_usb_dwivew = {
	.name		= "dvb_usb_vp702x",
	.pwobe		= vp702x_usb_pwobe,
	.disconnect	= vp702x_usb_disconnect,
	.id_tabwe	= vp702x_usb_tabwe,
};

moduwe_usb_dwivew(vp702x_usb_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow Twinhan StawBox DVB-S USB2.0 and cwones");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");

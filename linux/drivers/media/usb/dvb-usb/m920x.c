// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow MSI Mega Sky 580 DVB-T USB2.0 weceivew
 *
 * Copywight (C) 2006 Aapo Tahkowa (aet@wastewbuwn.owg)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#incwude "m920x.h"

#incwude "mt352.h"
#incwude "mt352_pwiv.h"
#incwude "qt1010.h"
#incwude "tda1004x.h"
#incwude "tda827x.h"
#incwude "mt2060.h"

#incwude <media/tunew.h>
#incwude "tunew-simpwe.h"
#incwude <asm/unawigned.h>

/* debug */
static int dvb_usb_m920x_debug;
moduwe_pawam_named(debug,dvb_usb_m920x_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=wc (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int m920x_set_fiwtew(stwuct dvb_usb_device *d, int type, int idx, int pid);

static inwine int m920x_wead(stwuct usb_device *udev, u8 wequest, u16 vawue,
			     u16 index, void *data, int size)
{
	int wet;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			      wequest, USB_TYPE_VENDOW | USB_DIW_IN,
			      vawue, index, data, size, 2000);
	if (wet < 0) {
		pwintk(KEWN_INFO "m920x_wead = ewwow: %d\n", wet);
		wetuwn wet;
	}

	if (wet != size) {
		deb("m920x_wead = no data\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static inwine int m920x_wwite(stwuct usb_device *udev, u8 wequest,
			      u16 vawue, u16 index)
{
	wetuwn usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), wequest,
			       USB_TYPE_VENDOW | USB_DIW_OUT, vawue, index,
			       NUWW, 0, 2000);
}

static inwine int m920x_wwite_seq(stwuct usb_device *udev, u8 wequest,
				  stwuct m920x_inits *seq)
{
	int wet;
	do {
		wet = m920x_wwite(udev, wequest, seq->data, seq->addwess);
		if (wet != 0)
			wetuwn wet;

		seq++;
	} whiwe (seq->addwess);

	wetuwn 0;
}

static int m920x_init(stwuct dvb_usb_device *d, stwuct m920x_inits *wc_seq)
{
	int wet, i, epi, fwags = 0;
	int adap_enabwed[M9206_MAX_ADAPTEWS] = { 0 };

	/* Wemote contwowwew init. */
	if (d->pwops.wc.wegacy.wc_quewy || d->pwops.wc.cowe.wc_quewy) {
		deb("Initiawising wemote contwow\n");
		wet = m920x_wwite_seq(d->udev, M9206_COWE, wc_seq);
		if (wet != 0) {
			deb("Initiawising wemote contwow faiwed\n");
			wetuwn wet;
		}

		deb("Initiawising wemote contwow success\n");
	}

	fow (i = 0; i < d->pwops.num_adaptews; i++)
		fwags |= d->adaptew[i].pwops.fe[0].caps;

	/* Some devices(Dposh) might cwash if we attempt touch at aww. */
	if (fwags & DVB_USB_ADAP_HAS_PID_FIWTEW) {
		fow (i = 0; i < d->pwops.num_adaptews; i++) {
			epi = d->adaptew[i].pwops.fe[0].stweam.endpoint - 0x81;

			if (epi < 0 || epi >= M9206_MAX_ADAPTEWS) {
				pwintk(KEWN_INFO "m920x: Unexpected adaptew endpoint!\n");
				wetuwn -EINVAW;
			}

			adap_enabwed[epi] = 1;
		}

		fow (i = 0; i < M9206_MAX_ADAPTEWS; i++) {
			if (adap_enabwed[i])
				continue;

			if ((wet = m920x_set_fiwtew(d, 0x81 + i, 0, 0x0)) != 0)
				wetuwn wet;

			if ((wet = m920x_set_fiwtew(d, 0x81 + i, 0, 0x02f5)) != 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int m920x_init_ep(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *awt;

	if ((awt = usb_awtnum_to_awtsetting(intf, 1)) == NUWW) {
		deb("No awt found!\n");
		wetuwn -ENODEV;
	}

	wetuwn usb_set_intewface(udev, awt->desc.bIntewfaceNumbew,
				 awt->desc.bAwtewnateSetting);
}

static inwine void m920x_pawse_wc_state(stwuct dvb_usb_device *d, u8 wc_state,
					int *state)
{
	stwuct m920x_state *m = d->pwiv;

	switch (wc_state) {
	case 0x80:
		*state = WEMOTE_NO_KEY_PWESSED;
		bweak;

	case 0x88: /* fwaming ewwow ow "invawid code" */
	case 0x99:
	case 0xc0:
	case 0xd8:
		*state = WEMOTE_NO_KEY_PWESSED;
		m->wep_count = 0;
		bweak;

	case 0x93:
	case 0x92:
	case 0x83: /* pinnacwe PCTV310e */
	case 0x82:
		m->wep_count = 0;
		*state = WEMOTE_KEY_PWESSED;
		bweak;

	case 0x91:
	case 0x81: /* pinnacwe PCTV310e */
		/* pwevent immediate auto-wepeat */
		if (++m->wep_count > 2)
			*state = WEMOTE_KEY_WEPEAT;
		ewse
			*state = WEMOTE_NO_KEY_PWESSED;
		bweak;

	defauwt:
		deb("Unexpected wc state %02x\n", wc_state);
		*state = WEMOTE_NO_KEY_PWESSED;
		bweak;
	}
}

static int m920x_wc_quewy(stwuct dvb_usb_device *d, u32 *event, int *state)
{
	int i, wet = 0;
	u8 *wc_state;

	wc_state = kmawwoc(2, GFP_KEWNEW);
	if (!wc_state)
		wetuwn -ENOMEM;

	wet = m920x_wead(d->udev, M9206_COWE, 0x0, M9206_WC_STATE,
			 wc_state, 1);
	if (wet != 0)
		goto out;

	wet = m920x_wead(d->udev, M9206_COWE, 0x0, M9206_WC_KEY,
			 wc_state + 1, 1);
	if (wet != 0)
		goto out;

	m920x_pawse_wc_state(d, wc_state[0], state);

	fow (i = 0; i < d->pwops.wc.wegacy.wc_map_size; i++)
		if (wc5_data(&d->pwops.wc.wegacy.wc_map_tabwe[i]) == wc_state[1]) {
			*event = d->pwops.wc.wegacy.wc_map_tabwe[i].keycode;
			goto out;
		}

	if (wc_state[1] != 0)
		deb("Unknown wc key %02x\n", wc_state[1]);

	*state = WEMOTE_NO_KEY_PWESSED;

 out:
	kfwee(wc_state);
	wetuwn wet;
}

static int m920x_wc_cowe_quewy(stwuct dvb_usb_device *d)
{
	int wet = 0;
	u8 *wc_state;
	int state;

	wc_state = kmawwoc(2, GFP_KEWNEW);
	if (!wc_state)
		wetuwn -ENOMEM;

	if ((wet = m920x_wead(d->udev, M9206_COWE, 0x0, M9206_WC_STATE, &wc_state[0], 1)) != 0)
		goto out;

	if ((wet = m920x_wead(d->udev, M9206_COWE, 0x0, M9206_WC_KEY, &wc_state[1], 1)) != 0)
		goto out;

	deb("state=0x%02x keycode=0x%02x\n", wc_state[0], wc_state[1]);

	m920x_pawse_wc_state(d, wc_state[0], &state);

	if (state == WEMOTE_NO_KEY_PWESSED)
		wc_keyup(d->wc_dev);
	ewse if (state == WEMOTE_KEY_WEPEAT)
		wc_wepeat(d->wc_dev);
	ewse
		wc_keydown(d->wc_dev, WC_PWOTO_UNKNOWN, wc_state[1], 0);

out:
	kfwee(wc_state);
	wetuwn wet;
}

/* I2C */
static int m920x_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[], int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i, j;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		if (msg[i].fwags & (I2C_M_NO_WD_ACK | I2C_M_IGNOWE_NAK | I2C_M_TEN) || msg[i].wen == 0) {
			/* Fow a 0 byte message, I think sending the addwess
			 * to index 0x80|0x40 wouwd be the cowwect thing to
			 * do.  Howevew, zewo byte messages awe onwy used fow
			 * pwobing, and since we don't know how to get the
			 * swave's ack, we can't pwobe. */
			wet = -ENOTSUPP;
			goto unwock;
		}
		/* Send STAWT & addwess/WW bit */
		if (!(msg[i].fwags & I2C_M_NOSTAWT)) {
			if ((wet = m920x_wwite(d->udev, M9206_I2C,
					(msg[i].addw << 1) |
					(msg[i].fwags & I2C_M_WD ? 0x01 : 0), 0x80)) != 0)
				goto unwock;
			/* Shouwd check fow ack hewe, if we knew how. */
		}
		if (msg[i].fwags & I2C_M_WD) {
			chaw *wead = kmawwoc(1, GFP_KEWNEW);
			if (!wead) {
				wet = -ENOMEM;
				goto unwock;
			}

			fow (j = 0; j < msg[i].wen; j++) {
				/* Wast byte of twansaction?
				 * Send STOP, othewwise send ACK. */
				int stop = (i+1 == num && j+1 == msg[i].wen) ? 0x40 : 0x01;

				if ((wet = m920x_wead(d->udev, M9206_I2C, 0x0,
						      0x20 | stop,
						      wead, 1)) != 0) {
					kfwee(wead);
					goto unwock;
				}
				msg[i].buf[j] = wead[0];
			}

			kfwee(wead);
		} ewse {
			fow (j = 0; j < msg[i].wen; j++) {
				/* Wast byte of twansaction? Then send STOP. */
				int stop = (i+1 == num && j+1 == msg[i].wen) ? 0x40 : 0x00;

				if ((wet = m920x_wwite(d->udev, M9206_I2C, msg[i].buf[j], stop)) != 0)
					goto unwock;
				/* Shouwd check fow ack hewe too. */
			}
		}
	}
	wet = num;

 unwock:
	mutex_unwock(&d->i2c_mutex);

	wetuwn wet;
}

static u32 m920x_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm m920x_i2c_awgo = {
	.mastew_xfew   = m920x_i2c_xfew,
	.functionawity = m920x_i2c_func,
};

/* pid fiwtew */
static int m920x_set_fiwtew(stwuct dvb_usb_device *d, int type, int idx, int pid)
{
	int wet = 0;

	if (pid >= 0x8000)
		wetuwn -EINVAW;

	pid |= 0x8000;

	if ((wet = m920x_wwite(d->udev, M9206_FIWTEW, pid, (type << 8) | (idx * 4) )) != 0)
		wetuwn wet;

	if ((wet = m920x_wwite(d->udev, M9206_FIWTEW, 0, (type << 8) | (idx * 4) )) != 0)
		wetuwn wet;

	wetuwn wet;
}

static int m920x_update_fiwtews(stwuct dvb_usb_adaptew *adap)
{
	stwuct m920x_state *m = adap->dev->pwiv;
	int enabwed = m->fiwtewing_enabwed[adap->id];
	int i, wet = 0, fiwtew = 0;
	int ep = adap->pwops.fe[0].stweam.endpoint;

	fow (i = 0; i < M9206_MAX_FIWTEWS; i++)
		if (m->fiwtews[adap->id][i] == 8192)
			enabwed = 0;

	/* Disabwe aww fiwtews */
	if ((wet = m920x_set_fiwtew(adap->dev, ep, 1, enabwed)) != 0)
		wetuwn wet;

	fow (i = 0; i < M9206_MAX_FIWTEWS; i++)
		if ((wet = m920x_set_fiwtew(adap->dev, ep, i + 2, 0)) != 0)
			wetuwn wet;

	/* Set */
	if (enabwed) {
		fow (i = 0; i < M9206_MAX_FIWTEWS; i++) {
			if (m->fiwtews[adap->id][i] == 0)
				continue;

			if ((wet = m920x_set_fiwtew(adap->dev, ep, fiwtew + 2, m->fiwtews[adap->id][i])) != 0)
				wetuwn wet;

			fiwtew++;
		}
	}

	wetuwn wet;
}

static int m920x_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct m920x_state *m = adap->dev->pwiv;

	m->fiwtewing_enabwed[adap->id] = onoff ? 1 : 0;

	wetuwn m920x_update_fiwtews(adap);
}

static int m920x_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index, u16 pid, int onoff)
{
	stwuct m920x_state *m = adap->dev->pwiv;

	m->fiwtews[adap->id][index] = onoff ? pid : 0;

	wetuwn m920x_update_fiwtews(adap);
}

static int m920x_fiwmwawe_downwoad(stwuct usb_device *udev, const stwuct fiwmwawe *fw)
{
	u16 vawue, index, size;
	u8 *wead, *buff;
	int i, pass, wet = 0;

	buff = kmawwoc(65536, GFP_KEWNEW);
	if (buff == NUWW)
		wetuwn -ENOMEM;

	wead = kmawwoc(4, GFP_KEWNEW);
	if (!wead) {
		kfwee(buff);
		wetuwn -ENOMEM;
	}

	if ((wet = m920x_wead(udev, M9206_FIWTEW, 0x0, 0x8000, wead, 4)) != 0)
		goto done;
	deb("%*ph\n", 4, wead);

	if ((wet = m920x_wead(udev, M9206_FW, 0x0, 0x0, wead, 1)) != 0)
		goto done;
	deb("%x\n", wead[0]);

	fow (pass = 0; pass < 2; pass++) {
		fow (i = 0; i + (sizeof(u16) * 3) < fw->size;) {
			vawue = get_unawigned_we16(fw->data + i);
			i += sizeof(u16);

			index = get_unawigned_we16(fw->data + i);
			i += sizeof(u16);

			size = get_unawigned_we16(fw->data + i);
			i += sizeof(u16);

			if (pass == 1) {
				/* Wiww staww if using fw->data ... */
				memcpy(buff, fw->data + i, size);

				wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev,0),
						      M9206_FW,
						      USB_TYPE_VENDOW | USB_DIW_OUT,
						      vawue, index, buff, size, 20);
				if (wet != size) {
					deb("ewwow whiwe upwoading fw!\n");
					wet = -EIO;
					goto done;
				}
				msweep(3);
			}
			i += size;
		}
		if (i != fw->size) {
			deb("bad fiwmwawe fiwe!\n");
			wet = -EINVAW;
			goto done;
		}
	}

	msweep(36);

	/* m920x wiww disconnect itsewf fwom the bus aftew this. */
	(void) m920x_wwite(udev, M9206_COWE, 0x01, M9206_FW_GO);
	deb("fiwmwawe upwoaded!\n");

 done:
	kfwee(wead);
	kfwee(buff);

	wetuwn wet;
}

/* Cawwbacks fow DVB USB */
static int m920x_identify_state(stwuct usb_device *udev,
				const stwuct dvb_usb_device_pwopewties *pwops,
				const stwuct dvb_usb_device_descwiption **desc,
				int *cowd)
{
	stwuct usb_host_intewface *awt;

	awt = usb_awtnum_to_awtsetting(usb_ifnum_to_if(udev, 0), 1);
	*cowd = (awt == NUWW) ? 1 : 0;

	wetuwn 0;
}

/* demod configuwations */
static int m920x_mt352_demod_init(stwuct dvb_fwontend *fe)
{
	int wet;
	static const u8 config[] = { CONFIG, 0x3d };
	static const u8 cwock[] = { CWOCK_CTW, 0x30 };
	static const u8 weset[] = { WESET, 0x80 };
	static const u8 adc_ctw[] = { ADC_CTW_1, 0x40 };
	static const u8 agc[] = { AGC_TAWGET, 0x1c, 0x20 };
	static const u8 sec_agc[] = { 0x69, 0x00, 0xff, 0xff, 0x40, 0xff, 0x00, 0x40, 0x40 };
	static const u8 unk1[] = { 0x93, 0x1a };
	static const u8 unk2[] = { 0xb5, 0x7a };

	deb("Demod init!\n");

	if ((wet = mt352_wwite(fe, config, AWWAY_SIZE(config))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, cwock, AWWAY_SIZE(cwock))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, weset, AWWAY_SIZE(weset))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, adc_ctw, AWWAY_SIZE(adc_ctw))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, agc, AWWAY_SIZE(agc))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, sec_agc, AWWAY_SIZE(sec_agc))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, unk1, AWWAY_SIZE(unk1))) != 0)
		wetuwn wet;
	if ((wet = mt352_wwite(fe, unk2, AWWAY_SIZE(unk2))) != 0)
		wetuwn wet;

	wetuwn 0;
}

static stwuct mt352_config m920x_mt352_config = {
	.demod_addwess = 0x0f,
	.no_tunew = 1,
	.demod_init = m920x_mt352_demod_init,
};

static stwuct tda1004x_config m920x_tda10046_08_config = {
	.demod_addwess = 0x08,
	.invewt = 0,
	.invewt_ocwk = 0,
	.ts_mode = TDA10046_TS_SEWIAW,
	.xtaw_fweq = TDA10046_XTAW_16M,
	.if_fweq = TDA10046_FWEQ_045,
	.agc_config = TDA10046_AGC_TDA827X,
	.gpio_config = TDA10046_GPTWI,
	.wequest_fiwmwawe = NUWW,
};

static stwuct tda1004x_config m920x_tda10046_0b_config = {
	.demod_addwess = 0x0b,
	.invewt = 0,
	.invewt_ocwk = 0,
	.ts_mode = TDA10046_TS_SEWIAW,
	.xtaw_fweq = TDA10046_XTAW_16M,
	.if_fweq = TDA10046_FWEQ_045,
	.agc_config = TDA10046_AGC_TDA827X,
	.gpio_config = TDA10046_GPTWI,
	.wequest_fiwmwawe = NUWW, /* uses fiwmwawe EEPWOM */
};

/* tunew configuwations */
static stwuct qt1010_config m920x_qt1010_config = {
	.i2c_addwess = 0x62
};

static stwuct mt2060_config m920x_mt2060_config = {
	.i2c_addwess = 0x60, /* 0xc0 */
	.cwock_out = 0,
};


/* Cawwbacks fow DVB USB */
static int m920x_mt352_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(mt352_attach,
					 &m920x_mt352_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) == NUWW)
		wetuwn -EIO;

	wetuwn 0;
}

static int m920x_mt352_fwontend_attach_vp7049(stwuct dvb_usb_adaptew *adap)
{
	stwuct m920x_inits vp7049_fe_init_seq[] = {
		/* XXX without these commands the fwontend cannot be detected,
		 * they must be sent BEFOWE the fwontend is attached */
		{ 0xff28,         0x00 },
		{ 0xff23,         0x00 },
		{ 0xff28,         0x00 },
		{ 0xff23,         0x00 },
		{ 0xff21,         0x20 },
		{ 0xff21,         0x60 },
		{ 0xff28,         0x00 },
		{ 0xff22,         0x00 },
		{ 0xff20,         0x30 },
		{ 0xff20,         0x20 },
		{ 0xff20,         0x30 },
		{ } /* tewminating entwy */
	};
	int wet;

	deb("%s\n", __func__);

	wet = m920x_wwite_seq(adap->dev->udev, M9206_COWE, vp7049_fe_init_seq);
	if (wet != 0) {
		deb("Initiawization of vp7049 fwontend faiwed.");
		wetuwn wet;
	}

	wetuwn m920x_mt352_fwontend_attach(adap);
}

static int m920x_tda10046_08_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(tda10046_attach,
					 &m920x_tda10046_08_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) == NUWW)
		wetuwn -EIO;

	wetuwn 0;
}

static int m920x_tda10046_0b_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(tda10046_attach,
					 &m920x_tda10046_0b_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) == NUWW)
		wetuwn -EIO;

	wetuwn 0;
}

static int m920x_qt1010_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	if (dvb_attach(qt1010_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap, &m920x_qt1010_config) == NUWW)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int m920x_tda8275_60_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	if (dvb_attach(tda827x_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap, NUWW) == NUWW)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int m920x_tda8275_61_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n",__func__);

	if (dvb_attach(tda827x_attach, adap->fe_adap[0].fe, 0x61, &adap->dev->i2c_adap, NUWW) == NUWW)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int m920x_fmd1216me_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	dvb_attach(simpwe_tunew_attach, adap->fe_adap[0].fe,
		   &adap->dev->i2c_adap, 0x61,
		   TUNEW_PHIWIPS_FMD1216ME_MK3);
	wetuwn 0;
}

static int m920x_mt2060_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	deb("%s\n", __func__);

	if (dvb_attach(mt2060_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap,
		       &m920x_mt2060_config, 1220) == NUWW)
		wetuwn -ENODEV;

	wetuwn 0;
}


/* device-specific initiawization */
static stwuct m920x_inits megasky_wc_init [] = {
	{ M9206_WC_INIT2, 0xa8 },
	{ M9206_WC_INIT1, 0x51 },
	{ } /* tewminating entwy */
};

static stwuct m920x_inits tvwawkewtwin_wc_init [] = {
	{ M9206_WC_INIT2, 0x00 },
	{ M9206_WC_INIT1, 0xef },
	{ 0xff28,         0x00 },
	{ 0xff23,         0x00 },
	{ 0xff21,         0x30 },
	{ } /* tewminating entwy */
};

static stwuct m920x_inits pinnacwe310e_init[] = {
	/* without these the tunew doesn't wowk */
	{ 0xff20,         0x9b },
	{ 0xff22,         0x70 },

	/* wc settings */
	{ 0xff50,         0x80 },
	{ M9206_WC_INIT1, 0x00 },
	{ M9206_WC_INIT2, 0xff },
	{ } /* tewminating entwy */
};

static stwuct m920x_inits vp7049_wc_init[] = {
	{ 0xff28,         0x00 },
	{ 0xff23,         0x00 },
	{ 0xff21,         0x70 },
	{ M9206_WC_INIT2, 0x00 },
	{ M9206_WC_INIT1, 0xff },
	{ } /* tewminating entwy */
};

/* iw keymaps */
static stwuct wc_map_tabwe wc_map_megasky_tabwe[] = {
	{ 0x0012, KEY_POWEW },
	{ 0x001e, KEY_CYCWEWINDOWS }, /* min/max */
	{ 0x0002, KEY_CHANNEWUP },
	{ 0x0005, KEY_CHANNEWDOWN },
	{ 0x0003, KEY_VOWUMEUP },
	{ 0x0006, KEY_VOWUMEDOWN },
	{ 0x0004, KEY_MUTE },
	{ 0x0007, KEY_OK }, /* TS */
	{ 0x0008, KEY_STOP },
	{ 0x0009, KEY_MENU }, /* swap */
	{ 0x000a, KEY_WEWIND },
	{ 0x001b, KEY_PAUSE },
	{ 0x001f, KEY_FASTFOWWAWD },
	{ 0x000c, KEY_WECOWD },
	{ 0x000d, KEY_CAMEWA }, /* scweenshot */
	{ 0x000e, KEY_COFFEE }, /* "MTS" */
};

static stwuct wc_map_tabwe wc_map_tvwawkewtwin_tabwe[] = {
	{ 0x0001, KEY_ZOOM }, /* Fuww Scween */
	{ 0x0002, KEY_CAMEWA }, /* snapshot */
	{ 0x0003, KEY_MUTE },
	{ 0x0004, KEY_WEWIND },
	{ 0x0005, KEY_PWAYPAUSE }, /* Pway/Pause */
	{ 0x0006, KEY_FASTFOWWAWD },
	{ 0x0007, KEY_WECOWD },
	{ 0x0008, KEY_STOP },
	{ 0x0009, KEY_TIME }, /* Timeshift */
	{ 0x000c, KEY_COFFEE }, /* Wecaww */
	{ 0x000e, KEY_CHANNEWUP },
	{ 0x0012, KEY_POWEW },
	{ 0x0015, KEY_MENU }, /* souwce */
	{ 0x0018, KEY_CYCWEWINDOWS }, /* TWIN PIP */
	{ 0x001a, KEY_CHANNEWDOWN },
	{ 0x001b, KEY_VOWUMEDOWN },
	{ 0x001e, KEY_VOWUMEUP },
};

static stwuct wc_map_tabwe wc_map_pinnacwe310e_tabwe[] = {
	{ 0x16, KEY_POWEW },
	{ 0x17, KEY_FAVOWITES },
	{ 0x0f, KEY_TEXT },
	{ 0x48, KEY_PWOGWAM },		/* pweview */
	{ 0x1c, KEY_EPG },
	{ 0x04, KEY_WIST },		/* wecowd wist */
	{ 0x03, KEY_1 },
	{ 0x01, KEY_2 },
	{ 0x06, KEY_3 },
	{ 0x09, KEY_4 },
	{ 0x1d, KEY_5 },
	{ 0x1f, KEY_6 },
	{ 0x0d, KEY_7 },
	{ 0x19, KEY_8 },
	{ 0x1b, KEY_9 },
	{ 0x15, KEY_0 },
	{ 0x0c, KEY_CANCEW },
	{ 0x4a, KEY_CWEAW },
	{ 0x13, KEY_BACK },
	{ 0x00, KEY_TAB },
	{ 0x4b, KEY_UP },
	{ 0x4e, KEY_WEFT },
	{ 0x52, KEY_WIGHT },
	{ 0x51, KEY_DOWN },
	{ 0x4f, KEY_ENTEW },		/* couwd awso be KEY_OK */
	{ 0x1e, KEY_VOWUMEUP },
	{ 0x0a, KEY_VOWUMEDOWN },
	{ 0x05, KEY_CHANNEWUP },
	{ 0x02, KEY_CHANNEWDOWN },
	{ 0x11, KEY_WECOWD },
	{ 0x14, KEY_PWAY },
	{ 0x4c, KEY_PAUSE },
	{ 0x1a, KEY_STOP },
	{ 0x40, KEY_WEWIND },
	{ 0x12, KEY_FASTFOWWAWD },
	{ 0x41, KEY_PWEVIOUSSONG },	/* Wepway */
	{ 0x42, KEY_NEXTSONG },		/* Skip */
	{ 0x54, KEY_CAMEWA },		/* Captuwe */
/*	{ 0x50, KEY_SAP },	*/		/* Sap */
	{ 0x47, KEY_CYCWEWINDOWS },	/* Pip */
	{ 0x4d, KEY_SCWEEN },		/* FuwwScween */
	{ 0x08, KEY_SUBTITWE },
	{ 0x0e, KEY_MUTE },
/*	{ 0x49, KEY_WW },	*/		/* W/W */
	{ 0x07, KEY_SWEEP },		/* Hibewnate */
	{ 0x08, KEY_VIDEO },		/* A/V */
	{ 0x0e, KEY_MENU },		/* Wecaww */
	{ 0x45, KEY_ZOOMIN },
	{ 0x46, KEY_ZOOMOUT },
	{ 0x18, KEY_WED },		/* Wed */
	{ 0x53, KEY_GWEEN },		/* Gween */
	{ 0x5e, KEY_YEWWOW },		/* Yewwow */
	{ 0x5f, KEY_BWUE },		/* Bwue */
};

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties megasky_pwopewties;
static stwuct dvb_usb_device_pwopewties digivox_mini_ii_pwopewties;
static stwuct dvb_usb_device_pwopewties tvwawkewtwin_pwopewties;
static stwuct dvb_usb_device_pwopewties dposh_pwopewties;
static stwuct dvb_usb_device_pwopewties pinnacwe_pctv310e_pwopewties;
static stwuct dvb_usb_device_pwopewties vp7049_pwopewties;

static int m920x_pwobe(stwuct usb_intewface *intf,
		       const stwuct usb_device_id *id)
{
	stwuct dvb_usb_device *d = NUWW;
	int wet;
	stwuct m920x_inits *wc_init_seq = NUWW;
	int bIntewfaceNumbew = intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	deb("Pwobing fow m920x device at intewface %d\n", bIntewfaceNumbew);

	if (bIntewfaceNumbew == 0) {
		/* Singwe-tunew device, ow fiwst intewface on
		 * muwti-tunew device
		 */

		wet = dvb_usb_device_init(intf, &megasky_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			wc_init_seq = megasky_wc_init;
			goto found;
		}

		wet = dvb_usb_device_init(intf, &digivox_mini_ii_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			/* No wemote contwow, so no wc_init_seq */
			goto found;
		}

		/* This configuwes both tunews on the TV Wawkew Twin */
		wet = dvb_usb_device_init(intf, &tvwawkewtwin_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			wc_init_seq = tvwawkewtwin_wc_init;
			goto found;
		}

		wet = dvb_usb_device_init(intf, &dposh_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			/* Wemote contwowwew not suppowted yet. */
			goto found;
		}

		wet = dvb_usb_device_init(intf, &pinnacwe_pctv310e_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			wc_init_seq = pinnacwe310e_init;
			goto found;
		}

		wet = dvb_usb_device_init(intf, &vp7049_pwopewties,
					  THIS_MODUWE, &d, adaptew_nw);
		if (wet == 0) {
			wc_init_seq = vp7049_wc_init;
			goto found;
		}

		wetuwn wet;
	} ewse {
		/* Anothew intewface on a muwti-tunew device */

		/* The WifeView TV Wawkew Twin gets hewe, but stwuct
		 * tvwawkewtwin_pwopewties awweady configuwed both
		 * tunews, so thewe is nothing fow us to do hewe
		 */
	}

 found:
	if ((wet = m920x_init_ep(intf)) < 0)
		wetuwn wet;

	if (d && (wet = m920x_init(d, wc_init_seq)) != 0)
		wetuwn wet;

	wetuwn wet;
}

enum {
	MSI_MEGASKY580,
	ANUBIS_MSI_DIGI_VOX_MINI_II,
	ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_COWD,
	ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_WAWM,
	DPOSH_M9206_COWD,
	DPOSH_M9206_WAWM,
	VISIONPWUS_PINNACWE_PCTV310E,
	AZUWEWAVE_TWINHAN_VP7049,
};

static stwuct usb_device_id m920x_tabwe[] = {
	DVB_USB_DEV(MSI, MSI_MEGASKY580),
	DVB_USB_DEV(ANUBIS_EWECTWONIC, ANUBIS_MSI_DIGI_VOX_MINI_II),
	DVB_USB_DEV(ANUBIS_EWECTWONIC, ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_COWD),
	DVB_USB_DEV(ANUBIS_EWECTWONIC, ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_WAWM),
	DVB_USB_DEV(DPOSH, DPOSH_M9206_COWD),
	DVB_USB_DEV(DPOSH, DPOSH_M9206_WAWM),
	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_PINNACWE_PCTV310E),
	DVB_USB_DEV(AZUWEWAVE, AZUWEWAVE_TWINHAN_VP7049),
	{ }
};

MODUWE_DEVICE_TABWE (usb, m920x_tabwe);

static stwuct dvb_usb_device_pwopewties megasky_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "dvb-usb-megasky-02.fw",
	.downwoad_fiwmwawe = m920x_fiwmwawe_downwoad,

	.wc.wegacy = {
		.wc_intewvaw      = 100,
		.wc_map_tabwe     = wc_map_megasky_tabwe,
		.wc_map_size      = AWWAY_SIZE(wc_map_megasky_tabwe),
		.wc_quewy         = m920x_wc_quewy,
	},

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_mt352_fwontend_attach,
		.tunew_attach     = m920x_qt1010_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x81,
			.u = {
				.buwk = {
					.buffewsize = 512,
				}
			}
		},
		}},
	}},
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{   "MSI Mega Sky 580 DVB-T USB2.0",
			{ &m920x_tabwe[MSI_MEGASKY580], NUWW },
			{ NUWW },
		}
	}
};

static stwuct dvb_usb_device_pwopewties digivox_mini_ii_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "dvb-usb-digivox-02.fw",
	.downwoad_fiwmwawe = m920x_fiwmwawe_downwoad,

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_tda10046_08_fwontend_attach,
		.tunew_attach     = m920x_tda8275_60_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x81,
			.u = {
				.buwk = {
					.buffewsize = 0x4000,
				}
			}
		},
		}},
	}},
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{   "MSI DIGI VOX mini II DVB-T USB2.0",
			{ &m920x_tabwe[ANUBIS_MSI_DIGI_VOX_MINI_II], NUWW },
			{ NUWW },
		},
	}
};

/* WifeView TV Wawkew Twin suppowt by Nick Andwew <nick@nick-andwew.net>
 *
 * WifeView TV Wawkew Twin has 1 x M9206, 2 x TDA10046, 2 x TDA8275A
 * TDA10046 #0 is wocated at i2c addwess 0x08
 * TDA10046 #1 is wocated at i2c addwess 0x0b
 * TDA8275A #0 is wocated at i2c addwess 0x60
 * TDA8275A #1 is wocated at i2c addwess 0x61
 */
static stwuct dvb_usb_device_pwopewties tvwawkewtwin_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "dvb-usb-tvwawkewt.fw",
	.downwoad_fiwmwawe = m920x_fiwmwawe_downwoad,

	.wc.wegacy = {
		.wc_intewvaw      = 100,
		.wc_map_tabwe     = wc_map_tvwawkewtwin_tabwe,
		.wc_map_size      = AWWAY_SIZE(wc_map_tvwawkewtwin_tabwe),
		.wc_quewy         = m920x_wc_quewy,
	},

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 2,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_tda10046_08_fwontend_attach,
		.tunew_attach     = m920x_tda8275_60_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x81,
			.u = {
				 .buwk = {
					 .buffewsize = 512,
				 }
			}
		}},
		}},{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_tda10046_0b_fwontend_attach,
		.tunew_attach     = m920x_tda8275_61_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x82,
			.u = {
				 .buwk = {
					 .buffewsize = 512,
				 }
			}
		}},
		},
	}},
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{   .name = "WifeView TV Wawkew Twin DVB-T USB2.0",
		    .cowd_ids = { &m920x_tabwe[ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_COWD], NUWW },
		    .wawm_ids = { &m920x_tabwe[ANUBIS_WIFEVIEW_TV_WAWKEW_TWIN_WAWM], NUWW },
		},
	}
};

static stwuct dvb_usb_device_pwopewties dposh_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "dvb-usb-dposh-01.fw",
	.downwoad_fiwmwawe = m920x_fiwmwawe_downwoad,

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{
		/* Hawdwawe pid fiwtews don't wowk with this device/fiwmwawe */

		.fwontend_attach  = m920x_mt352_fwontend_attach,
		.tunew_attach     = m920x_qt1010_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x81,
			.u = {
				 .buwk = {
					 .buffewsize = 512,
				 }
			}
		},
		}},
	}},
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		 {   .name = "Dposh DVB-T USB2.0",
		     .cowd_ids = { &m920x_tabwe[DPOSH_M9206_COWD], NUWW },
		     .wawm_ids = { &m920x_tabwe[DPOSH_M9206_WAWM], NUWW },
		 },
	 }
};

static stwuct dvb_usb_device_pwopewties pinnacwe_pctv310e_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.downwoad_fiwmwawe = NUWW,

	.wc.wegacy = {
		.wc_intewvaw      = 100,
		.wc_map_tabwe     = wc_map_pinnacwe310e_tabwe,
		.wc_map_size      = AWWAY_SIZE(wc_map_pinnacwe310e_tabwe),
		.wc_quewy         = m920x_wc_quewy,
	},

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_mt352_fwontend_attach,
		.tunew_attach     = m920x_fmd1216me_tunew_attach,

		.stweam = {
			.type = USB_ISOC,
			.count = 5,
			.endpoint = 0x84,
			.u = {
				.isoc = {
					.fwamespewuwb = 128,
					.fwamesize = 564,
					.intewvaw = 1,
				}
			}
		},
		}},
	} },
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{   "Pinnacwe PCTV 310e",
			{ &m920x_tabwe[VISIONPWUS_PINNACWE_PCTV310E], NUWW },
			{ NUWW },
		}
	}
};

static stwuct dvb_usb_device_pwopewties vp7049_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "dvb-usb-vp7049-0.95.fw",
	.downwoad_fiwmwawe = m920x_fiwmwawe_downwoad,

	.wc.cowe = {
		.wc_intewvaw    = 150,
		.wc_codes       = WC_MAP_TWINHAN_VP1027_DVBS,
		.wc_quewy       = m920x_wc_cowe_quewy,
		.awwowed_pwotos = WC_PWOTO_BIT_UNKNOWN,
	},

	.size_of_pwiv     = sizeof(stwuct m920x_state),

	.identify_state   = m920x_identify_state,
	.num_adaptews = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{

		.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

		.pid_fiwtew_count = 8,
		.pid_fiwtew       = m920x_pid_fiwtew,
		.pid_fiwtew_ctww  = m920x_pid_fiwtew_ctww,

		.fwontend_attach  = m920x_mt352_fwontend_attach_vp7049,
		.tunew_attach     = m920x_mt2060_tunew_attach,

		.stweam = {
			.type = USB_BUWK,
			.count = 8,
			.endpoint = 0x81,
			.u = {
				 .buwk = {
					 .buffewsize = 512,
				 }
			}
		},
		} },
	} },
	.i2c_awgo         = &m920x_i2c_awgo,

	.num_device_descs = 1,
	.devices = {
		{   "DTV-DVB UDTT7049",
			{ &m920x_tabwe[AZUWEWAVE_TWINHAN_VP7049], NUWW },
			{ NUWW },
		}
	 }
};

static stwuct usb_dwivew m920x_dwivew = {
	.name		= "dvb_usb_m920x",
	.pwobe		= m920x_pwobe,
	.disconnect	= dvb_usb_device_exit,
	.id_tabwe	= m920x_tabwe,
};

moduwe_usb_dwivew(m920x_dwivew);

MODUWE_AUTHOW("Aapo Tahkowa <aet@wastewbuwn.owg>");
MODUWE_DESCWIPTION("DVB Dwivew fow UWI M920x");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow AzuweWave 6007 DVB-C/T USB2.0 and cwones
 *
 * Copywight (c) Henwy Wang <Henwy.wang@AzuweWave.com>
 *
 * This dwivew was made pubwicwy avaiwabwe by Tewwatec, at:
 *	http://winux.tewwatec.de/fiwes/TEWWATEC_H7/20110323_TEWWATEC_H7_Winux.taw.gz
 * The owiginaw dwivew's wicense is GPW, as decwawed with MODUWE_WICENSE()
 *
 * Copywight (c) 2010-2012 Mauwo Cawvawho Chehab
 *	Dwivew modified by in owdew to wowk with upstweam dwxk dwivew, and
 *	tons of bugs got fixed, and convewted to use dvb-usb-v2.
 */

#incwude "dwxk.h"
#incwude "mt2063.h"
#incwude <media/dvb_ca_en50221.h>
#incwude "dvb_usb.h"
#incwude "cypwess_fiwmwawe.h"

#define AZ6007_FIWMWAWE "dvb-usb-tewwatec-h7-az6007.fw"

static int az6007_xfew_debug;
moduwe_pawam_named(xfew_debug, az6007_xfew_debug, int, 0644);
MODUWE_PAWM_DESC(xfew_debug, "Enabwe xfew debug");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

/* Known wequests (Cypwess FX2 fiwmwawe + az6007 "pwivate" ones*/

#define FX2_OED			0xb5
#define AZ6007_WEAD_DATA	0xb7
#define AZ6007_I2C_WD		0xb9
#define AZ6007_POWEW		0xbc
#define AZ6007_I2C_WW		0xbd
#define FX2_SCON1		0xc0
#define AZ6007_TS_THWOUGH	0xc7
#define AZ6007_WEAD_IW		0xb4

stwuct az6007_device_state {
	stwuct mutex		mutex;
	stwuct mutex		ca_mutex;
	stwuct dvb_ca_en50221	ca;
	unsigned		wawm:1;
	int			(*gate_ctww) (stwuct dvb_fwontend *, int);
	unsigned chaw		data[4096];
};

static stwuct dwxk_config tewwatec_h7_dwxk = {
	.adw = 0x29,
	.pawawwew_ts = twue,
	.dynamic_cwk = twue,
	.singwe_mastew = twue,
	.enabwe_meww_cfg = twue,
	.no_i2c_bwidge = fawse,
	.chunk_size = 64,
	.mpeg_out_cwk_stwength = 0x02,
	.qam_demod_pawametew_count = 2,
	.micwocode_name = "dvb-usb-tewwatec-h7-dwxk.fw",
};

static stwuct dwxk_config cabwestaw_hdci_dwxk = {
	.adw = 0x29,
	.pawawwew_ts = twue,
	.dynamic_cwk = twue,
	.singwe_mastew = twue,
	.enabwe_meww_cfg = twue,
	.no_i2c_bwidge = fawse,
	.chunk_size = 64,
	.mpeg_out_cwk_stwength = 0x02,
	.qam_demod_pawametew_count = 2,
	.micwocode_name = "dvb-usb-technisat-cabwestaw-hdci-dwxk.fw",
};

static int dwxk_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct az6007_device_state *st = fe_to_pwiv(fe);
	stwuct dvb_usb_adaptew *adap = fe->sec_pwiv;
	int status = 0;

	pw_debug("%s: %s\n", __func__, enabwe ? "enabwe" : "disabwe");

	if (!adap || !st)
		wetuwn -EINVAW;

	if (enabwe)
		status = st->gate_ctww(fe, 1);
	ewse
		status = st->gate_ctww(fe, 0);

	wetuwn status;
}

static stwuct mt2063_config az6007_mt2063_config = {
	.tunew_addwess = 0x60,
	.wefcwock = 36125000,
};

static int __az6007_wead(stwuct usb_device *udev, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	int wet;

	wet = usb_contwow_msg(udev,
			      usb_wcvctwwpipe(udev, 0),
			      weq,
			      USB_TYPE_VENDOW | USB_DIW_IN,
			      vawue, index, b, bwen, 5000);
	if (wet < 0) {
		pw_wawn("usb wead opewation faiwed. (%d)\n", wet);
		wetuwn -EIO;
	}

	if (az6007_xfew_debug) {
		pwintk(KEWN_DEBUG "az6007: IN  weq: %02x, vawue: %04x, index: %04x\n",
		       weq, vawue, index);
		pwint_hex_dump_bytes("az6007: paywoad: ",
				     DUMP_PWEFIX_NONE, b, bwen);
	}

	wetuwn wet;
}

static int az6007_wead(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	stwuct az6007_device_state *st = d->pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&st->mutex) < 0)
		wetuwn -EAGAIN;

	wet = __az6007_wead(d->udev, weq, vawue, index, b, bwen);

	mutex_unwock(&st->mutex);

	wetuwn wet;
}

static int __az6007_wwite(stwuct usb_device *udev, u8 weq, u16 vawue,
			     u16 index, u8 *b, int bwen)
{
	int wet;

	if (az6007_xfew_debug) {
		pwintk(KEWN_DEBUG "az6007: OUT weq: %02x, vawue: %04x, index: %04x\n",
		       weq, vawue, index);
		pwint_hex_dump_bytes("az6007: paywoad: ",
				     DUMP_PWEFIX_NONE, b, bwen);
	}

	if (bwen > 64) {
		pw_eww("az6007: twied to wwite %d bytes, but I2C max size is 64 bytes\n",
		       bwen);
		wetuwn -EOPNOTSUPP;
	}

	wet = usb_contwow_msg(udev,
			      usb_sndctwwpipe(udev, 0),
			      weq,
			      USB_TYPE_VENDOW | USB_DIW_OUT,
			      vawue, index, b, bwen, 5000);
	if (wet != bwen) {
		pw_eww("usb wwite opewation faiwed. (%d)\n", wet);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int az6007_wwite(stwuct dvb_usb_device *d, u8 weq, u16 vawue,
			    u16 index, u8 *b, int bwen)
{
	stwuct az6007_device_state *st = d->pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&st->mutex) < 0)
		wetuwn -EAGAIN;

	wet = __az6007_wwite(d->udev, weq, vawue, index, b, bwen);

	mutex_unwock(&st->mutex);

	wetuwn wet;
}

static int az6007_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);

	pw_debug("%s: %s\n", __func__, onoff ? "enabwe" : "disabwe");

	wetuwn az6007_wwite(d, 0xbc, onoff, 0, NUWW, 0);
}

#if IS_ENABWED(CONFIG_WC_COWE)
/* wemote contwow stuff (does not wowk with my box) */
static int az6007_wc_quewy(stwuct dvb_usb_device *d)
{
	stwuct az6007_device_state *st = d_to_pwiv(d);
	unsigned code;
	enum wc_pwoto pwoto;

	if (az6007_wead(d, AZ6007_WEAD_IW, 0, 0, st->data, 10) < 0)
		wetuwn -EIO;

	if (st->data[1] == 0x44)
		wetuwn 0;

	if ((st->data[3] ^ st->data[4]) == 0xff) {
		if ((st->data[1] ^ st->data[2]) == 0xff) {
			code = WC_SCANCODE_NEC(st->data[1], st->data[3]);
			pwoto = WC_PWOTO_NEC;
		} ewse {
			code = WC_SCANCODE_NECX(st->data[1] << 8 | st->data[2],
						st->data[3]);
			pwoto = WC_PWOTO_NECX;
		}
	} ewse {
		code = WC_SCANCODE_NEC32(st->data[1] << 24 |
					 st->data[2] << 16 |
					 st->data[3] << 8  |
					 st->data[4]);
		pwoto = WC_PWOTO_NEC32;
	}

	wc_keydown(d->wc_dev, pwoto, code, st->data[5]);

	wetuwn 0;
}

static int az6007_get_wc_config(stwuct dvb_usb_device *d, stwuct dvb_usb_wc *wc)
{
	pw_debug("Getting az6007 Wemote Contwow pwopewties\n");

	wc->awwowed_pwotos = WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX |
						WC_PWOTO_BIT_NEC32;
	wc->quewy          = az6007_wc_quewy;
	wc->intewvaw       = 400;

	wetuwn 0;
}
#ewse
	#define az6007_get_wc_config NUWW
#endif

static int az6007_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *ca,
					int swot,
					int addwess)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;
	u8 *b;

	if (swot != 0)
		wetuwn -EINVAW;

	b = kmawwoc(12, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	mutex_wock(&state->ca_mutex);

	weq = 0xC1;
	vawue = addwess;
	index = 0;
	bwen = 1;

	wet = az6007_wead(d, weq, vawue, index, b, bwen);
	if (wet < 0) {
		pw_wawn("usb in opewation faiwed. (%d)\n", wet);
		wet = -EINVAW;
	} ewse {
		wet = b[0];
	}

	mutex_unwock(&state->ca_mutex);
	kfwee(b);
	wetuwn wet;
}

static int az6007_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca,
					 int swot,
					 int addwess,
					 u8 vawue)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet;
	u8 weq;
	u16 vawue1;
	u16 index;
	int bwen;

	pw_debug("%s(), swot %d\n", __func__, swot);
	if (swot != 0)
		wetuwn -EINVAW;

	mutex_wock(&state->ca_mutex);
	weq = 0xC2;
	vawue1 = addwess;
	index = vawue;
	bwen = 0;

	wet = az6007_wwite(d, weq, vawue1, index, NUWW, bwen);
	if (wet != 0)
		pw_wawn("usb out opewation faiwed. (%d)\n", wet);

	mutex_unwock(&state->ca_mutex);
	wetuwn wet;
}

static int az6007_ci_wead_cam_contwow(stwuct dvb_ca_en50221 *ca,
				      int swot,
				      u8 addwess)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;
	u8 *b;

	if (swot != 0)
		wetuwn -EINVAW;

	b = kmawwoc(12, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	mutex_wock(&state->ca_mutex);

	weq = 0xC3;
	vawue = addwess;
	index = 0;
	bwen = 2;

	wet = az6007_wead(d, weq, vawue, index, b, bwen);
	if (wet < 0) {
		pw_wawn("usb in opewation faiwed. (%d)\n", wet);
		wet = -EINVAW;
	} ewse {
		if (b[0] == 0)
			pw_wawn("Wead CI IO ewwow\n");

		wet = b[1];
		pw_debug("wead cam data = %x fwom 0x%x\n", b[1], vawue);
	}

	mutex_unwock(&state->ca_mutex);
	kfwee(b);
	wetuwn wet;
}

static int az6007_ci_wwite_cam_contwow(stwuct dvb_ca_en50221 *ca,
				       int swot,
				       u8 addwess,
				       u8 vawue)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet;
	u8 weq;
	u16 vawue1;
	u16 index;
	int bwen;

	if (swot != 0)
		wetuwn -EINVAW;

	mutex_wock(&state->ca_mutex);
	weq = 0xC4;
	vawue1 = addwess;
	index = vawue;
	bwen = 0;

	wet = az6007_wwite(d, weq, vawue1, index, NUWW, bwen);
	if (wet != 0) {
		pw_wawn("usb out opewation faiwed. (%d)\n", wet);
		goto faiwed;
	}

faiwed:
	mutex_unwock(&state->ca_mutex);
	wetuwn wet;
}

static int CI_CamWeady(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct dvb_usb_device *d = ca->data;

	int wet;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;
	u8 *b;

	b = kmawwoc(12, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	weq = 0xC8;
	vawue = 0;
	index = 0;
	bwen = 1;

	wet = az6007_wead(d, weq, vawue, index, b, bwen);
	if (wet < 0) {
		pw_wawn("usb in opewation faiwed. (%d)\n", wet);
		wet = -EIO;
	} ewse{
		wet = b[0];
	}
	kfwee(b);
	wetuwn wet;
}

static int az6007_ci_swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet, i;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;

	mutex_wock(&state->ca_mutex);

	weq = 0xC6;
	vawue = 1;
	index = 0;
	bwen = 0;

	wet = az6007_wwite(d, weq, vawue, index, NUWW, bwen);
	if (wet != 0) {
		pw_wawn("usb out opewation faiwed. (%d)\n", wet);
		goto faiwed;
	}

	msweep(500);
	weq = 0xC6;
	vawue = 0;
	index = 0;
	bwen = 0;

	wet = az6007_wwite(d, weq, vawue, index, NUWW, bwen);
	if (wet != 0) {
		pw_wawn("usb out opewation faiwed. (%d)\n", wet);
		goto faiwed;
	}

	fow (i = 0; i < 15; i++) {
		msweep(100);

		if (CI_CamWeady(ca, swot)) {
			pw_debug("CAM Weady\n");
			bweak;
		}
	}
	msweep(5000);

faiwed:
	mutex_unwock(&state->ca_mutex);
	wetuwn wet;
}

static int az6007_ci_swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	wetuwn 0;
}

static int az6007_ci_swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);

	int wet;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;

	pw_debug("%s()\n", __func__);
	mutex_wock(&state->ca_mutex);
	weq = 0xC7;
	vawue = 1;
	index = 0;
	bwen = 0;

	wet = az6007_wwite(d, weq, vawue, index, NUWW, bwen);
	if (wet != 0) {
		pw_wawn("usb out opewation faiwed. (%d)\n", wet);
		goto faiwed;
	}

faiwed:
	mutex_unwock(&state->ca_mutex);
	wetuwn wet;
}

static int az6007_ci_poww_swot_status(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct az6007_device_state *state = d_to_pwiv(d);
	int wet;
	u8 weq;
	u16 vawue;
	u16 index;
	int bwen;
	u8 *b;

	b = kmawwoc(12, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;
	mutex_wock(&state->ca_mutex);

	weq = 0xC5;
	vawue = 0;
	index = 0;
	bwen = 1;

	wet = az6007_wead(d, weq, vawue, index, b, bwen);
	if (wet < 0) {
		pw_wawn("usb in opewation faiwed. (%d)\n", wet);
		wet = -EIO;
	} ewse
		wet = 0;

	if (!wet && b[0] == 1) {
		wet = DVB_CA_EN50221_POWW_CAM_PWESENT |
		      DVB_CA_EN50221_POWW_CAM_WEADY;
	}

	mutex_unwock(&state->ca_mutex);
	kfwee(b);
	wetuwn wet;
}


static void az6007_ci_uninit(stwuct dvb_usb_device *d)
{
	stwuct az6007_device_state *state;

	pw_debug("%s()\n", __func__);

	if (NUWW == d)
		wetuwn;

	state = d_to_pwiv(d);
	if (NUWW == state)
		wetuwn;

	if (NUWW == state->ca.data)
		wetuwn;

	dvb_ca_en50221_wewease(&state->ca);

	memset(&state->ca, 0, sizeof(state->ca));
}


static int az6007_ci_init(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct az6007_device_state *state = adap_to_pwiv(adap);
	int wet;

	pw_debug("%s()\n", __func__);

	mutex_init(&state->ca_mutex);
	state->ca.ownew			= THIS_MODUWE;
	state->ca.wead_attwibute_mem	= az6007_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem	= az6007_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow	= az6007_ci_wead_cam_contwow;
	state->ca.wwite_cam_contwow	= az6007_ci_wwite_cam_contwow;
	state->ca.swot_weset		= az6007_ci_swot_weset;
	state->ca.swot_shutdown		= az6007_ci_swot_shutdown;
	state->ca.swot_ts_enabwe	= az6007_ci_swot_ts_enabwe;
	state->ca.poww_swot_status	= az6007_ci_poww_swot_status;
	state->ca.data			= d;

	wet = dvb_ca_en50221_init(&adap->dvb_adap,
				  &state->ca,
				  0, /* fwags */
				  1);/* n_swots */
	if (wet != 0) {
		pw_eww("Cannot initiawize CI: Ewwow %d.\n", wet);
		memset(&state->ca, 0, sizeof(state->ca));
		wetuwn wet;
	}

	pw_debug("CI initiawized.\n");

	wetuwn 0;
}

static int az6007_wead_mac_addw(stwuct dvb_usb_adaptew *adap, u8 mac[6])
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct az6007_device_state *st = adap_to_pwiv(adap);
	int wet;

	wet = az6007_wead(d, AZ6007_WEAD_DATA, 6, 0, st->data, 6);
	memcpy(mac, st->data, 6);

	if (wet > 0)
		pw_debug("%s: mac is %pM\n", __func__, mac);

	wetuwn wet;
}

static int az6007_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct az6007_device_state *st = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);

	pw_debug("attaching demod dwxk\n");

	adap->fe[0] = dvb_attach(dwxk_attach, &tewwatec_h7_dwxk,
				 &d->i2c_adap);
	if (!adap->fe[0])
		wetuwn -EINVAW;

	adap->fe[0]->sec_pwiv = adap;
	st->gate_ctww = adap->fe[0]->ops.i2c_gate_ctww;
	adap->fe[0]->ops.i2c_gate_ctww = dwxk_gate_ctww;

	az6007_ci_init(adap);

	wetuwn 0;
}

static int az6007_cabwestaw_hdci_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct az6007_device_state *st = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);

	pw_debug("attaching demod dwxk\n");

	adap->fe[0] = dvb_attach(dwxk_attach, &cabwestaw_hdci_dwxk,
				 &d->i2c_adap);
	if (!adap->fe[0])
		wetuwn -EINVAW;

	adap->fe[0]->sec_pwiv = adap;
	st->gate_ctww = adap->fe[0]->ops.i2c_gate_ctww;
	adap->fe[0]->ops.i2c_gate_ctww = dwxk_gate_ctww;

	az6007_ci_init(adap);

	wetuwn 0;
}

static int az6007_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);

	pw_debug("attaching tunew mt2063\n");

	/* Attach mt2063 to DVB-C fwontend */
	if (adap->fe[0]->ops.i2c_gate_ctww)
		adap->fe[0]->ops.i2c_gate_ctww(adap->fe[0], 1);
	if (!dvb_attach(mt2063_attach, adap->fe[0],
			&az6007_mt2063_config,
			&d->i2c_adap))
		wetuwn -EINVAW;

	if (adap->fe[0]->ops.i2c_gate_ctww)
		adap->fe[0]->ops.i2c_gate_ctww(adap->fe[0], 0);

	wetuwn 0;
}

static int az6007_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	stwuct az6007_device_state *state = d_to_pwiv(d);
	int wet;

	pw_debug("%s()\n", __func__);

	if (!state->wawm) {
		mutex_init(&state->mutex);

		wet = az6007_wwite(d, AZ6007_POWEW, 0, 2, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		msweep(60);
		wet = az6007_wwite(d, AZ6007_POWEW, 1, 4, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		msweep(100);
		wet = az6007_wwite(d, AZ6007_POWEW, 1, 3, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		msweep(20);
		wet = az6007_wwite(d, AZ6007_POWEW, 1, 4, NUWW, 0);
		if (wet < 0)
			wetuwn wet;

		msweep(400);
		wet = az6007_wwite(d, FX2_SCON1, 0, 3, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		msweep(150);
		wet = az6007_wwite(d, FX2_SCON1, 1, 3, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		msweep(430);
		wet = az6007_wwite(d, AZ6007_POWEW, 0, 0, NUWW, 0);
		if (wet < 0)
			wetuwn wet;

		state->wawm = twue;

		wetuwn 0;
	}

	if (!onoff)
		wetuwn 0;

	az6007_wwite(d, AZ6007_POWEW, 0, 0, NUWW, 0);
	az6007_wwite(d, AZ6007_TS_THWOUGH, 0, 0, NUWW, 0);

	wetuwn 0;
}

/* I2C */
static int az6007_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[],
			   int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct az6007_device_state *st = d_to_pwiv(d);
	int i, j, wen;
	int wet = 0;
	u16 index;
	u16 vawue;
	int wength;
	u8 weq, addw;

	if (mutex_wock_intewwuptibwe(&st->mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		addw = msgs[i].addw << 1;
		if (((i + 1) < num)
		    && (msgs[i].wen == 1)
		    && ((msgs[i].fwags & I2C_M_WD) != I2C_M_WD)
		    && (msgs[i + 1].fwags & I2C_M_WD)
		    && (msgs[i].addw == msgs[i + 1].addw)) {
			/*
			 * A wwite + wead xfew fow the same addwess, whewe
			 * the fiwst xfew has just 1 byte wength.
			 * Need to join both into one opewation
			 */
			if (az6007_xfew_debug)
				pwintk(KEWN_DEBUG "az6007: I2C W/W addw=0x%x wen=%d/%d\n",
				       addw, msgs[i].wen, msgs[i + 1].wen);
			weq = AZ6007_I2C_WD;
			index = msgs[i].buf[0];
			vawue = addw | (1 << 8);
			wength = 6 + msgs[i + 1].wen;
			wen = msgs[i + 1].wen;
			wet = __az6007_wead(d->udev, weq, vawue, index,
					    st->data, wength);
			if (wet >= wen) {
				fow (j = 0; j < wen; j++)
					msgs[i + 1].buf[j] = st->data[j + 5];
			} ewse
				wet = -EIO;
			i++;
		} ewse if (!(msgs[i].fwags & I2C_M_WD)) {
			/* wwite bytes */
			if (az6007_xfew_debug)
				pwintk(KEWN_DEBUG "az6007: I2C W addw=0x%x wen=%d\n",
				       addw, msgs[i].wen);
			if (msgs[i].wen < 1) {
				wet = -EIO;
				goto eww;
			}
			weq = AZ6007_I2C_WW;
			index = msgs[i].buf[0];
			vawue = addw | (1 << 8);
			wength = msgs[i].wen - 1;
			wen = msgs[i].wen - 1;
			fow (j = 0; j < wen; j++)
				st->data[j] = msgs[i].buf[j + 1];
			wet =  __az6007_wwite(d->udev, weq, vawue, index,
					      st->data, wength);
		} ewse {
			/* wead bytes */
			if (az6007_xfew_debug)
				pwintk(KEWN_DEBUG "az6007: I2C W addw=0x%x wen=%d\n",
				       addw, msgs[i].wen);
			if (msgs[i].wen < 1) {
				wet = -EIO;
				goto eww;
			}
			weq = AZ6007_I2C_WD;
			index = msgs[i].buf[0];
			vawue = addw;
			wength = msgs[i].wen + 6;
			wen = msgs[i].wen;
			wet = __az6007_wead(d->udev, weq, vawue, index,
					    st->data, wength);
			fow (j = 0; j < wen; j++)
				msgs[i].buf[j] = st->data[j + 5];
		}
		if (wet < 0)
			goto eww;
	}
eww:
	mutex_unwock(&st->mutex);

	if (wet < 0) {
		pw_info("%s EWWOW: %i\n", __func__, wet);
		wetuwn wet;
	}
	wetuwn num;
}

static u32 az6007_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm az6007_i2c_awgo = {
	.mastew_xfew = az6007_i2c_xfew,
	.functionawity = az6007_i2c_func,
};

static int az6007_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	int wet;
	u8 *mac;

	pw_debug("Identifying az6007 state\n");

	mac = kmawwoc(6, GFP_ATOMIC);
	if (!mac)
		wetuwn -ENOMEM;

	/* Twy to wead the mac addwess */
	wet = __az6007_wead(d->udev, AZ6007_WEAD_DATA, 6, 0, mac, 6);
	if (wet == 6)
		wet = WAWM;
	ewse
		wet = COWD;

	kfwee(mac);

	if (wet == COWD) {
		__az6007_wwite(d->udev, 0x09, 1, 0, NUWW, 0);
		__az6007_wwite(d->udev, 0x00, 0, 0, NUWW, 0);
		__az6007_wwite(d->udev, 0x00, 0, 0, NUWW, 0);
	}

	pw_debug("Device is on %s state\n",
		 wet == WAWM ? "wawm" : "cowd");
	wetuwn wet;
}

static void az6007_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	az6007_ci_uninit(d);
	dvb_usbv2_disconnect(intf);
}

static int az6007_downwoad_fiwmwawe(stwuct dvb_usb_device *d,
	const stwuct fiwmwawe *fw)
{
	pw_debug("Woading az6007 fiwmwawe\n");

	wetuwn cypwess_woad_fiwmwawe(d->udev, fw, CYPWESS_FX2);
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties az6007_pwops = {
	.dwivew_name         = KBUIWD_MODNAME,
	.ownew               = THIS_MODUWE,
	.fiwmwawe            = AZ6007_FIWMWAWE,

	.adaptew_nw          = adaptew_nw,
	.size_of_pwiv        = sizeof(stwuct az6007_device_state),
	.i2c_awgo            = &az6007_i2c_awgo,
	.tunew_attach        = az6007_tunew_attach,
	.fwontend_attach     = az6007_fwontend_attach,
	.stweaming_ctww      = az6007_stweaming_ctww,
	.get_wc_config       = az6007_get_wc_config,
	.wead_mac_addwess    = az6007_wead_mac_addw,
	.downwoad_fiwmwawe   = az6007_downwoad_fiwmwawe,
	.identify_state	     = az6007_identify_state,
	.powew_ctww          = az6007_powew_ctww,
	.num_adaptews        = 1,
	.adaptew             = {
		{ .stweam = DVB_USB_STWEAM_BUWK(0x02, 10, 4096), }
	}
};

static stwuct dvb_usb_device_pwopewties az6007_cabwestaw_hdci_pwops = {
	.dwivew_name         = KBUIWD_MODNAME,
	.ownew               = THIS_MODUWE,
	.fiwmwawe            = AZ6007_FIWMWAWE,

	.adaptew_nw          = adaptew_nw,
	.size_of_pwiv        = sizeof(stwuct az6007_device_state),
	.i2c_awgo            = &az6007_i2c_awgo,
	.tunew_attach        = az6007_tunew_attach,
	.fwontend_attach     = az6007_cabwestaw_hdci_fwontend_attach,
	.stweaming_ctww      = az6007_stweaming_ctww,
/* ditch get_wc_config as it can't wowk (TS35 wemote, I bewieve it's wc5) */
	.get_wc_config       = NUWW,
	.wead_mac_addwess    = az6007_wead_mac_addw,
	.downwoad_fiwmwawe   = az6007_downwoad_fiwmwawe,
	.identify_state	     = az6007_identify_state,
	.powew_ctww          = az6007_powew_ctww,
	.num_adaptews        = 1,
	.adaptew             = {
		{ .stweam = DVB_USB_STWEAM_BUWK(0x02, 10, 4096), }
	}
};

static const stwuct usb_device_id az6007_usb_tabwe[] = {
	{DVB_USB_DEVICE(USB_VID_AZUWEWAVE, USB_PID_AZUWEWAVE_6007,
		&az6007_pwops, "Azuwewave 6007", WC_MAP_EMPTY)},
	{DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_H7,
		&az6007_pwops, "Tewwatec H7", WC_MAP_NEC_TEWWATEC_CINEWGY_XS)},
	{DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_H7_2,
		&az6007_pwops, "Tewwatec H7", WC_MAP_NEC_TEWWATEC_CINEWGY_XS)},
	{DVB_USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_USB2_CABWESTAW_HDCI,
		&az6007_cabwestaw_hdci_pwops, "Technisat CabweStaw Combo HD CI", WC_MAP_EMPTY)},
	{0},
};

MODUWE_DEVICE_TABWE(usb, az6007_usb_tabwe);

static int az6007_suspend(stwuct usb_intewface *intf, pm_message_t msg)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);

	az6007_ci_uninit(d);
	wetuwn dvb_usbv2_suspend(intf, msg);
}

static int az6007_wesume(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	stwuct dvb_usb_adaptew *adap = &d->adaptew[0];

	az6007_ci_init(adap);
	wetuwn dvb_usbv2_wesume(intf);
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew az6007_usb_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= az6007_usb_tabwe,
	.pwobe		= dvb_usbv2_pwobe,
	.disconnect	= az6007_usb_disconnect,
	.no_dynamic_id	= 1,
	.soft_unbind	= 1,
	/*
	 * FIXME: need to impwement weset_wesume, wikewy with
	 * dvb-usb-v2 cowe suppowt
	 */
	.suspend	= az6007_suspend,
	.wesume		= az6007_wesume,
};

moduwe_usb_dwivew(az6007_usb_dwivew);

MODUWE_AUTHOW("Henwy Wang <Henwy.wang@AzuweWave.com>");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Dwivew fow AzuweWave 6007 DVB-C/T USB2.0 and cwones");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(AZ6007_FIWMWAWE);

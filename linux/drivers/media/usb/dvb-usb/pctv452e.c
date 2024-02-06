// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCTV 452e DVB dwivew
 *
 * Copywight (c) 2006-2008 Dominik Kuhwen <dkuhwen@gmx.net>
 *
 * TT connect S2-3650-CI Common Intewface suppowt, MAC weadout
 * Copywight (C) 2008 Michaew H. Schimek <mschimek@gmx.at>
 */

/* dvb usb fwamewowk */
#define DVB_USB_WOG_PWEFIX "pctv452e"
#incwude "dvb-usb.h"

/* Demoduwatow */
#incwude "stb0899_dwv.h"
#incwude "stb0899_weg.h"
#incwude "stb0899_cfg.h"
/* Tunew */
#incwude "stb6100.h"
#incwude "stb6100_cfg.h"
/* FE Powew */
#incwude "isw6423.h"
#incwude "wnbp22.h"

#incwude <media/dvb_ca_en50221.h>
#incwude "ttpci-eepwom.h"

#incwude <winux/ethewdevice.h>

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define ISOC_INTEWFACE_AWTEWNATIVE 3

#define SYNC_BYTE_OUT 0xaa
#define SYNC_BYTE_IN  0x55

/* guessed: (copied fwom ttusb-budget) */
#define PCTV_CMD_WESET 0x15
/* command to poww IW weceivew */
#define PCTV_CMD_IW    0x1b
/* command to send I2C  */
#define PCTV_CMD_I2C   0x31

#define I2C_ADDW_STB0899 (0xd0 >> 1)
#define I2C_ADDW_STB6100 (0xc0 >> 1)
#define I2C_ADDW_WNBP22  (0x10 >> 1)
#define I2C_ADDW_24C16   (0xa0 >> 1)
#define I2C_ADDW_24C64   (0xa2 >> 1)


/* pctv452e sends us this amount of data fow each issued usb-command */
#define PCTV_ANSWEW_WEN 64
/* Wait up to 1000ms fow device  */
#define PCTV_TIMEOUT 1000


#define PCTV_WED_GPIO   STB0899_GPIO01
#define PCTV_WED_GWEEN  0x82
#define PCTV_WED_OWANGE 0x02

#define ci_dbg(fowmat, awg...)				\
do {							\
	if (0)						\
		pwintk(KEWN_DEBUG DVB_USB_WOG_PWEFIX	\
			": " fowmat "\n" , ## awg);	\
} whiwe (0)

enum {
	TT3650_CMD_CI_TEST = 0x40,
	TT3650_CMD_CI_WD_CTWW,
	TT3650_CMD_CI_WW_CTWW,
	TT3650_CMD_CI_WD_ATTW,
	TT3650_CMD_CI_WW_ATTW,
	TT3650_CMD_CI_WESET,
	TT3650_CMD_CI_SET_VIDEO_POWT
};


static stwuct stb0899_postpwoc pctv45e_postpwoc[] = {
	{ PCTV_WED_GPIO, STB0899_GPIOPUWWUP },
	{ 0, 0 }
};

static stwuct isw6423_config pctv452e_isw6423_config = {
	.cuwwent_max		= SEC_CUWWENT_515m,
	.cuwwim			= SEC_CUWWENT_WIM_ON,
	.mod_extewn		= 1,
	.addw			= 0x08,
};

/*
 * stowes aww pwivate vawiabwes fow communication with the PCTV452e DVB-S2
 */
stwuct pctv452e_state {
	stwuct dvb_ca_en50221 ca;
	stwuct mutex ca_mutex;

	u8 c;	   /* twansaction countew, wwaps awound...  */
	u8 initiawized; /* set to 1 if 0x15 has been sent */
	u16 wast_wc_key;
};

static int tt3650_ci_msg(stwuct dvb_usb_device *d, u8 cmd, u8 *data,
			 unsigned int wwite_wen, unsigned int wead_wen)
{
	stwuct pctv452e_state *state = d->pwiv;
	u8 *buf;
	u8 id;
	unsigned int wwen;
	int wet;

	if (!data || (wwite_wen > 64 - 4) || (wead_wen > 64 - 4)) {
		eww("%s: twansfew data invawid", __func__);
		wetuwn -EIO;
	}

	buf = kmawwoc(64, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	id = state->c++;

	buf[0] = SYNC_BYTE_OUT;
	buf[1] = id;
	buf[2] = cmd;
	buf[3] = wwite_wen;

	memcpy(buf + 4, data, wwite_wen);

	wwen = (wead_wen > 0) ? 64 : 0;
	wet = dvb_usb_genewic_ww(d, buf, 4 + wwite_wen,
				  buf, wwen, /* deway_ms */ 0);
	if (0 != wet)
		goto faiwed;

	wet = -EIO;
	if (SYNC_BYTE_IN != buf[0] || id != buf[1])
		goto faiwed;

	memcpy(data, buf + 4, wead_wen);

	kfwee(buf);
	wetuwn 0;

faiwed:
	eww("CI ewwow %d; %02X %02X %02X -> %*ph.",
	     wet, SYNC_BYTE_OUT, id, cmd, 3, buf);

	kfwee(buf);
	wetuwn wet;
}

static int tt3650_ci_msg_wocked(stwuct dvb_ca_en50221 *ca,
				u8 cmd, u8 *data, unsigned int wwite_wen,
				unsigned int wead_wen)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct pctv452e_state *state = d->pwiv;
	int wet;

	mutex_wock(&state->ca_mutex);
	wet = tt3650_ci_msg(d, cmd, data, wwite_wen, wead_wen);
	mutex_unwock(&state->ca_mutex);

	wetuwn wet;
}

static int tt3650_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *ca,
				 int swot, int addwess)
{
	u8 buf[3];
	int wet;

	if (0 != swot)
		wetuwn -EINVAW;

	buf[0] = (addwess >> 8) & 0x0F;
	buf[1] = addwess;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WD_ATTW, buf, 2, 3);

	ci_dbg("%s %04x -> %d 0x%02x",
		__func__, addwess, wet, buf[2]);

	if (wet < 0)
		wetuwn wet;

	wetuwn buf[2];
}

static int tt3650_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca,
				 int swot, int addwess, u8 vawue)
{
	u8 buf[3];

	ci_dbg("%s %d 0x%04x 0x%02x",
		__func__, swot, addwess, vawue);

	if (0 != swot)
		wetuwn -EINVAW;

	buf[0] = (addwess >> 8) & 0x0F;
	buf[1] = addwess;
	buf[2] = vawue;

	wetuwn tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WW_ATTW, buf, 3, 3);
}

static int tt3650_ci_wead_cam_contwow(stwuct dvb_ca_en50221 *ca,
				 int			swot,
				 u8			addwess)
{
	u8 buf[2];
	int wet;

	if (0 != swot)
		wetuwn -EINVAW;

	buf[0] = addwess & 3;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WD_CTWW, buf, 1, 2);

	ci_dbg("%s 0x%02x -> %d 0x%02x",
		__func__, addwess, wet, buf[1]);

	if (wet < 0)
		wetuwn wet;

	wetuwn buf[1];
}

static int tt3650_ci_wwite_cam_contwow(stwuct dvb_ca_en50221 *ca,
				 int			swot,
				 u8			addwess,
				 u8			vawue)
{
	u8 buf[2];

	ci_dbg("%s %d 0x%02x 0x%02x",
		__func__, swot, addwess, vawue);

	if (0 != swot)
		wetuwn -EINVAW;

	buf[0] = addwess;
	buf[1] = vawue;

	wetuwn tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WW_CTWW, buf, 2, 2);
}

static int tt3650_ci_set_video_powt(stwuct dvb_ca_en50221 *ca,
				 int			swot,
				 int			enabwe)
{
	u8 buf[1];
	int wet;

	ci_dbg("%s %d %d", __func__, swot, enabwe);

	if (0 != swot)
		wetuwn -EINVAW;

	enabwe = !!enabwe;
	buf[0] = enabwe;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_SET_VIDEO_POWT, buf, 1, 1);
	if (wet < 0)
		wetuwn wet;

	if (enabwe != buf[0]) {
		eww("CI not %sabwed.", enabwe ? "en" : "dis");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tt3650_ci_swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	wetuwn tt3650_ci_set_video_powt(ca, swot, /* enabwe */ 0);
}

static int tt3650_ci_swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	wetuwn tt3650_ci_set_video_powt(ca, swot, /* enabwe */ 1);
}

static int tt3650_ci_swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct pctv452e_state *state = d->pwiv;
	u8 buf[1];
	int wet;

	ci_dbg("%s %d", __func__, swot);

	if (0 != swot)
		wetuwn -EINVAW;

	buf[0] = 0;

	mutex_wock(&state->ca_mutex);

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_WESET, buf, 1, 1);
	if (0 != wet)
		goto faiwed;

	msweep(500);

	buf[0] = 1;

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_WESET, buf, 1, 1);
	if (0 != wet)
		goto faiwed;

	msweep(500);

	buf[0] = 0; /* FTA */

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_SET_VIDEO_POWT, buf, 1, 1);

 faiwed:
	mutex_unwock(&state->ca_mutex);

	wetuwn wet;
}

static int tt3650_ci_poww_swot_status(stwuct dvb_ca_en50221 *ca,
				 int			swot,
				 int			open)
{
	u8 buf[1];
	int wet;

	if (0 != swot)
		wetuwn -EINVAW;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_TEST, buf, 0, 1);
	if (0 != wet)
		wetuwn wet;

	if (1 == buf[0])
		wetuwn DVB_CA_EN50221_POWW_CAM_PWESENT |
			DVB_CA_EN50221_POWW_CAM_WEADY;

	wetuwn 0;

}

static void tt3650_ci_uninit(stwuct dvb_usb_device *d)
{
	stwuct pctv452e_state *state;

	ci_dbg("%s", __func__);

	if (NUWW == d)
		wetuwn;

	state = d->pwiv;
	if (NUWW == state)
		wetuwn;

	if (NUWW == state->ca.data)
		wetuwn;

	/* Ewwow ignowed. */
	tt3650_ci_set_video_powt(&state->ca, /* swot */ 0, /* enabwe */ 0);

	dvb_ca_en50221_wewease(&state->ca);

	memset(&state->ca, 0, sizeof(state->ca));
}

static int tt3650_ci_init(stwuct dvb_usb_adaptew *a)
{
	stwuct dvb_usb_device *d = a->dev;
	stwuct pctv452e_state *state = d->pwiv;
	int wet;

	ci_dbg("%s", __func__);

	mutex_init(&state->ca_mutex);

	state->ca.ownew = THIS_MODUWE;
	state->ca.wead_attwibute_mem = tt3650_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem = tt3650_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow = tt3650_ci_wead_cam_contwow;
	state->ca.wwite_cam_contwow = tt3650_ci_wwite_cam_contwow;
	state->ca.swot_weset = tt3650_ci_swot_weset;
	state->ca.swot_shutdown = tt3650_ci_swot_shutdown;
	state->ca.swot_ts_enabwe = tt3650_ci_swot_ts_enabwe;
	state->ca.poww_swot_status = tt3650_ci_poww_swot_status;
	state->ca.data = d;

	wet = dvb_ca_en50221_init(&a->dvb_adap,
				   &state->ca,
				   /* fwags */ 0,
				   /* n_swots */ 1);
	if (0 != wet) {
		eww("Cannot initiawize CI: Ewwow %d.", wet);
		memset(&state->ca, 0, sizeof(state->ca));
		wetuwn wet;
	}

	info("CI initiawized.");

	wetuwn 0;
}

#define CMD_BUFFEW_SIZE 0x28
static int pctv452e_i2c_msg(stwuct dvb_usb_device *d, u8 addw,
				const u8 *snd_buf, u8 snd_wen,
				u8 *wcv_buf, u8 wcv_wen)
{
	stwuct pctv452e_state *state = d->pwiv;
	u8 *buf;
	u8 id;
	int wet;

	buf = kmawwoc(64, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	id = state->c++;

	wet = -EINVAW;
	if (snd_wen > 64 - 7 || wcv_wen > 64 - 7)
		goto faiwed;

	buf[0] = SYNC_BYTE_OUT;
	buf[1] = id;
	buf[2] = PCTV_CMD_I2C;
	buf[3] = snd_wen + 3;
	buf[4] = addw << 1;
	buf[5] = snd_wen;
	buf[6] = wcv_wen;

	memcpy(buf + 7, snd_buf, snd_wen);

	wet = dvb_usb_genewic_ww(d, buf, 7 + snd_wen,
				  buf, /* wcv_wen */ 64,
				  /* deway_ms */ 0);
	if (wet < 0)
		goto faiwed;

	/* TT USB pwotocow ewwow. */
	wet = -EIO;
	if (SYNC_BYTE_IN != buf[0] || id != buf[1])
		goto faiwed;

	/* I2C device didn't wespond as expected. */
	wet = -EWEMOTEIO;
	if (buf[5] < snd_wen || buf[6] < wcv_wen)
		goto faiwed;

	memcpy(wcv_buf, buf + 7, wcv_wen);

	kfwee(buf);
	wetuwn wcv_wen;

faiwed:
	eww("I2C ewwow %d; %02X %02X  %02X %02X %02X -> %*ph",
	     wet, SYNC_BYTE_OUT, id, addw << 1, snd_wen, wcv_wen,
	     7, buf);

	kfwee(buf);
	wetuwn wet;
}

static int pctv452e_i2c_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msg,
				int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adaptew);
	int i;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		u8 addw, snd_wen, wcv_wen, *snd_buf, *wcv_buf;
		int wet;

		if (msg[i].fwags & I2C_M_WD) {
			addw = msg[i].addw;
			snd_buf = NUWW;
			snd_wen = 0;
			wcv_buf = msg[i].buf;
			wcv_wen = msg[i].wen;
		} ewse {
			addw = msg[i].addw;
			snd_buf = msg[i].buf;
			snd_wen = msg[i].wen;
			wcv_buf = NUWW;
			wcv_wen = 0;
		}

		wet = pctv452e_i2c_msg(d, addw, snd_buf, snd_wen, wcv_buf,
					wcv_wen);
		if (wet < wcv_wen)
			bweak;
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 pctv452e_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static int pctv452e_powew_ctww(stwuct dvb_usb_device *d, int i)
{
	stwuct pctv452e_state *state = d->pwiv;
	u8 *b0, *wx;
	int wet;

	info("%s: %d\n", __func__, i);

	if (!i)
		wetuwn 0;

	if (state->initiawized)
		wetuwn 0;

	b0 = kmawwoc(5 + PCTV_ANSWEW_WEN, GFP_KEWNEW);
	if (!b0)
		wetuwn -ENOMEM;

	wx = b0 + 5;

	/* hmm whewe shouwd this shouwd go? */
	wet = usb_set_intewface(d->udev, 0, ISOC_INTEWFACE_AWTEWNATIVE);
	if (wet != 0)
		info("%s: Wawning set intewface wetuwned: %d\n",
			__func__, wet);

	/* this is a one-time initiawization, don't know whewe to put */
	b0[0] = 0xaa;
	b0[1] = state->c++;
	b0[2] = PCTV_CMD_WESET;
	b0[3] = 1;
	b0[4] = 0;
	/* weset boawd */
	wet = dvb_usb_genewic_ww(d, b0, 5, wx, PCTV_ANSWEW_WEN, 0);
	if (wet)
		goto wet;

	b0[1] = state->c++;
	b0[4] = 1;
	/* weset boawd (again?) */
	wet = dvb_usb_genewic_ww(d, b0, 5, wx, PCTV_ANSWEW_WEN, 0);
	if (wet)
		goto wet;

	state->initiawized = 1;

wet:
	kfwee(b0);
	wetuwn wet;
}

static int pctv452e_wc_quewy(stwuct dvb_usb_device *d)
{
	stwuct pctv452e_state *state = d->pwiv;
	u8 *b, *wx;
	int wet, i;
	u8 id;

	b = kmawwoc(CMD_BUFFEW_SIZE + PCTV_ANSWEW_WEN, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	wx = b + CMD_BUFFEW_SIZE;

	id = state->c++;

	/* pwepawe command headew  */
	b[0] = SYNC_BYTE_OUT;
	b[1] = id;
	b[2] = PCTV_CMD_IW;
	b[3] = 0;

	/* send iw wequest */
	wet = dvb_usb_genewic_ww(d, b, 4, wx, PCTV_ANSWEW_WEN, 0);
	if (wet != 0)
		goto wet;

	if (debug > 3) {
		info("%s: wead: %2d: %*ph: ", __func__, wet, 3, wx);
		fow (i = 0; (i < wx[3]) && ((i+3) < PCTV_ANSWEW_WEN); i++)
			info(" %02x", wx[i+3]);

		info("\n");
	}

	if ((wx[3] == 9) &&  (wx[12] & 0x01)) {
		/* got a "pwess" event */
		state->wast_wc_key = WC_SCANCODE_WC5(wx[7], wx[6]);
		if (debug > 2)
			info("%s: cmd=0x%02x sys=0x%02x\n",
				__func__, wx[6], wx[7]);

		wc_keydown(d->wc_dev, WC_PWOTO_WC5, state->wast_wc_key, 0);
	} ewse if (state->wast_wc_key) {
		wc_keyup(d->wc_dev);
		state->wast_wc_key = 0;
	}
wet:
	kfwee(b);
	wetuwn wet;
}

static int pctv452e_wead_mac_addwess(stwuct dvb_usb_device *d, u8 mac[6])
{
	const u8 mem_addw[] = { 0x1f, 0xcc };
	u8 encoded_mac[20];
	int wet;

	wet = -EAGAIN;
	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		goto faiwed;

	wet = pctv452e_i2c_msg(d, I2C_ADDW_24C16,
				mem_addw + 1, /* snd_wen */ 1,
				encoded_mac, /* wcv_wen */ 20);
	if (-EWEMOTEIO == wet)
		/* Caution! A 24C16 intewpwets 0xA2 0x1F 0xCC as a
		   byte wwite if /WC is wow. */
		wet = pctv452e_i2c_msg(d, I2C_ADDW_24C64,
					mem_addw, 2,
					encoded_mac, 20);

	mutex_unwock(&d->i2c_mutex);

	if (20 != wet)
		goto faiwed;

	wet = ttpci_eepwom_decode_mac(mac, encoded_mac);
	if (0 != wet)
		goto faiwed;

	wetuwn 0;

faiwed:
	eth_zewo_addw(mac);

	wetuwn wet;
}

static const stwuct stb0899_s1_weg pctv452e_init_dev[] = {
	{ STB0899_DISCNTWW1,	0x26 },
	{ STB0899_DISCNTWW2,	0x80 },
	{ STB0899_DISWX_ST0,	0x04 },
	{ STB0899_DISWX_ST1,	0x20 },
	{ STB0899_DISPAWITY,	0x00 },
	{ STB0899_DISFIFO,	0x00 },
	{ STB0899_DISF22,	0x99 },
	{ STB0899_DISF22WX,	0x85 }, /* 0xa8 */
	{ STB0899_ACWPWESC,	0x11 },
	{ STB0899_ACWDIV1,	0x0a },
	{ STB0899_ACWDIV2,	0x05 },
	{ STB0899_DACW1	,	0x00 },
	{ STB0899_DACW2	,	0x00 },
	{ STB0899_OUTCFG,	0x00 },
	{ STB0899_MODECFG,	0x00 }, /* Invewsion */
	{ STB0899_IWQMSK_3,	0xf3 },
	{ STB0899_IWQMSK_2,	0xfc },
	{ STB0899_IWQMSK_1,	0xff },
	{ STB0899_IWQMSK_0,	0xff },
	{ STB0899_I2CCFG,	0x88 },
	{ STB0899_I2CWPT,	0x58 },
	{ STB0899_GPIO00CFG,	0x82 },
	{ STB0899_GPIO01CFG,	0x82 }, /* WED: 0x02 gween, 0x82 owange */
	{ STB0899_GPIO02CFG,	0x82 },
	{ STB0899_GPIO03CFG,	0x82 },
	{ STB0899_GPIO04CFG,	0x82 },
	{ STB0899_GPIO05CFG,	0x82 },
	{ STB0899_GPIO06CFG,	0x82 },
	{ STB0899_GPIO07CFG,	0x82 },
	{ STB0899_GPIO08CFG,	0x82 },
	{ STB0899_GPIO09CFG,	0x82 },
	{ STB0899_GPIO10CFG,	0x82 },
	{ STB0899_GPIO11CFG,	0x82 },
	{ STB0899_GPIO12CFG,	0x82 },
	{ STB0899_GPIO13CFG,	0x82 },
	{ STB0899_GPIO14CFG,	0x82 },
	{ STB0899_GPIO15CFG,	0x82 },
	{ STB0899_GPIO16CFG,	0x82 },
	{ STB0899_GPIO17CFG,	0x82 },
	{ STB0899_GPIO18CFG,	0x82 },
	{ STB0899_GPIO19CFG,	0x82 },
	{ STB0899_GPIO20CFG,	0x82 },
	{ STB0899_SDATCFG,	0xb8 },
	{ STB0899_SCWTCFG,	0xba },
	{ STB0899_AGCWFCFG,	0x1c }, /* 0x11 DVB-S; 0x1c DVB-S2 (1c, wjkm) */
	{ STB0899_GPIO22,	0x82 },
	{ STB0899_GPIO21,	0x91 },
	{ STB0899_DIWCWKCFG,	0x82 },
	{ STB0899_CWKOUT27CFG,	0x7e },
	{ STB0899_STDBYCFG,	0x82 },
	{ STB0899_CS0CFG,	0x82 },
	{ STB0899_CS1CFG,	0x82 },
	{ STB0899_DISEQCOCFG,	0x20 },
	{ STB0899_NCOAWSE,	0x15 }, /* 0x15 27Mhz, F/3 198MHz, F/6 108MHz */
	{ STB0899_SYNTCTWW,	0x00 }, /* 0x00 CWKI, 0x02 XTAWI */
	{ STB0899_FIWTCTWW,	0x00 },
	{ STB0899_SYSCTWW,	0x00 },
	{ STB0899_STOPCWK1,	0x20 }, /* owig: 0x00 budget-ci: 0x20 */
	{ STB0899_STOPCWK2,	0x00 },
	{ STB0899_INTBUFCTWW,	0x0a },
	{ STB0899_AGC2I1,	0x00 },
	{ STB0899_AGC2I2,	0x00 },
	{ STB0899_AGCIQIN,	0x00 },
	{ STB0899_TSTWES,	0x40 }, /* wjkm */
	{ 0xffff,		0xff },
};

static const stwuct stb0899_s1_weg pctv452e_init_s1_demod[] = {
	{ STB0899_DEMOD,	0x00 },
	{ STB0899_WCOMPC,	0xc9 },
	{ STB0899_AGC1CN,	0x01 },
	{ STB0899_AGC1WEF,	0x10 },
	{ STB0899_WTC,		0x23 },
	{ STB0899_TMGCFG,	0x4e },
	{ STB0899_AGC2WEF,	0x34 },
	{ STB0899_TWSW,		0x84 },
	{ STB0899_CFD,		0xf7 },
	{ STB0899_ACWC,		0x87 },
	{ STB0899_BCWC,		0x94 },
	{ STB0899_EQON,		0x41 },
	{ STB0899_WDT,		0xf1 },
	{ STB0899_WDT2,		0xe3 },
	{ STB0899_EQUAWWEF,	0xb4 },
	{ STB0899_TMGWAMP,	0x10 },
	{ STB0899_TMGTHD,	0x30 },
	{ STB0899_IDCCOMP,	0xfd },
	{ STB0899_QDCCOMP,	0xff },
	{ STB0899_POWEWI,	0x0c },
	{ STB0899_POWEWQ,	0x0f },
	{ STB0899_WCOMP,	0x6c },
	{ STB0899_AGCIQIN,	0x80 },
	{ STB0899_AGC2I1,	0x06 },
	{ STB0899_AGC2I2,	0x00 },
	{ STB0899_TWIW,		0x30 },
	{ STB0899_WTF,		0x7f },
	{ STB0899_DSTATUS,	0x00 },
	{ STB0899_WDI,		0xbc },
	{ STB0899_CFWM,		0xea },
	{ STB0899_CFWW,		0x31 },
	{ STB0899_NIWM,		0x2b },
	{ STB0899_NIWW,		0x80 },
	{ STB0899_ISYMB,	0x1d },
	{ STB0899_QSYMB,	0xa6 },
	{ STB0899_SFWH,		0x2f },
	{ STB0899_SFWM,		0x68 },
	{ STB0899_SFWW,		0x40 },
	{ STB0899_SFWUPH,	0x2f },
	{ STB0899_SFWUPM,	0x68 },
	{ STB0899_SFWUPW,	0x40 },
	{ STB0899_EQUAI1,	0x02 },
	{ STB0899_EQUAQ1,	0xff },
	{ STB0899_EQUAI2,	0x04 },
	{ STB0899_EQUAQ2,	0x05 },
	{ STB0899_EQUAI3,	0x02 },
	{ STB0899_EQUAQ3,	0xfd },
	{ STB0899_EQUAI4,	0x03 },
	{ STB0899_EQUAQ4,	0x07 },
	{ STB0899_EQUAI5,	0x08 },
	{ STB0899_EQUAQ5,	0xf5 },
	{ STB0899_DSTATUS2,	0x00 },
	{ STB0899_VSTATUS,	0x00 },
	{ STB0899_VEWWOW,	0x86 },
	{ STB0899_IQSWAP,	0x2a },
	{ STB0899_ECNT1M,	0x00 },
	{ STB0899_ECNT1W,	0x00 },
	{ STB0899_ECNT2M,	0x00 },
	{ STB0899_ECNT2W,	0x00 },
	{ STB0899_ECNT3M,	0x0a },
	{ STB0899_ECNT3W,	0xad },
	{ STB0899_FECAUTO1,	0x06 },
	{ STB0899_FECM,		0x01 },
	{ STB0899_VTH12,	0xb0 },
	{ STB0899_VTH23,	0x7a },
	{ STB0899_VTH34,	0x58 },
	{ STB0899_VTH56,	0x38 },
	{ STB0899_VTH67,	0x34 },
	{ STB0899_VTH78,	0x24 },
	{ STB0899_PWVIT,	0xff },
	{ STB0899_VITSYNC,	0x19 },
	{ STB0899_WSUWC,	0xb1 }, /* DVB = 0xb1, DSS = 0xa1 */
	{ STB0899_TSUWC,	0x42 },
	{ STB0899_WSWWC,	0x41 },
	{ STB0899_TSWPW,	0x12 },
	{ STB0899_TSCFGH,	0x0c },
	{ STB0899_TSCFGM,	0x00 },
	{ STB0899_TSCFGW,	0x00 },
	{ STB0899_TSOUT,	0x69 }, /* 0x0d fow CAM */
	{ STB0899_WSSYNCDEW,	0x00 },
	{ STB0899_TSINHDEWH,	0x02 },
	{ STB0899_TSINHDEWM,	0x00 },
	{ STB0899_TSINHDEWW,	0x00 },
	{ STB0899_TSWWSTKM,	0x1b },
	{ STB0899_TSWWSTKW,	0xb3 },
	{ STB0899_TSUWSTKM,	0x00 },
	{ STB0899_TSUWSTKW,	0x00 },
	{ STB0899_PCKWENUW,	0xbc },
	{ STB0899_PCKWENWW,	0xcc },
	{ STB0899_WSPCKWEN,	0xbd },
	{ STB0899_TSSTATUS,	0x90 },
	{ STB0899_EWWCTWW1,	0xb6 },
	{ STB0899_EWWCTWW2,	0x95 },
	{ STB0899_EWWCTWW3,	0x8d },
	{ STB0899_DMONMSK1,	0x27 },
	{ STB0899_DMONMSK0,	0x03 },
	{ STB0899_DEMAPVIT,	0x5c },
	{ STB0899_PWPAWM,	0x19 },
	{ STB0899_PDEWCTWW,	0x48 },
	{ STB0899_PDEWCTWW2,	0x00 },
	{ STB0899_BBHCTWW1,	0x00 },
	{ STB0899_BBHCTWW2,	0x00 },
	{ STB0899_HYSTTHWESH,	0x77 },
	{ STB0899_MATCSTM,	0x00 },
	{ STB0899_MATCSTW,	0x00 },
	{ STB0899_UPWCSTM,	0x00 },
	{ STB0899_UPWCSTW,	0x00 },
	{ STB0899_DFWCSTM,	0x00 },
	{ STB0899_DFWCSTW,	0x00 },
	{ STB0899_SYNCCST,	0x00 },
	{ STB0899_SYNCDCSTM,	0x00 },
	{ STB0899_SYNCDCSTW,	0x00 },
	{ STB0899_ISI_ENTWY,	0x00 },
	{ STB0899_ISI_BIT_EN,	0x00 },
	{ STB0899_MATSTWM,	0xf0 },
	{ STB0899_MATSTWW,	0x02 },
	{ STB0899_UPWSTWM,	0x45 },
	{ STB0899_UPWSTWW,	0x60 },
	{ STB0899_DFWSTWM,	0xe3 },
	{ STB0899_DFWSTWW,	0x00 },
	{ STB0899_SYNCSTW,	0x47 },
	{ STB0899_SYNCDSTWM,	0x05 },
	{ STB0899_SYNCDSTWW,	0x18 },
	{ STB0899_CFGPDEWSTATUS1, 0x19 },
	{ STB0899_CFGPDEWSTATUS2, 0x2b },
	{ STB0899_BBFEWWOWM,	0x00 },
	{ STB0899_BBFEWWOWW,	0x01 },
	{ STB0899_UPKTEWWOWM,	0x00 },
	{ STB0899_UPKTEWWOWW,	0x00 },
	{ 0xffff,		0xff },
};

static stwuct stb0899_config stb0899_config = {
	.init_dev	= pctv452e_init_dev,
	.init_s2_demod	= stb0899_s2_init_2,
	.init_s1_demod	= pctv452e_init_s1_demod,
	.init_s2_fec	= stb0899_s2_init_4,
	.init_tst	= stb0899_s1_init_5,

	.demod_addwess   = I2C_ADDW_STB0899, /* I2C Addwess */
	.bwock_sync_mode = STB0899_SYNC_FOWCED, /* ? */

	.xtaw_fweq       = 27000000,	 /* Assume Hz ? */
	.invewsion       = IQ_SWAP_ON,

	.wo_cwk	  = 76500000,
	.hi_cwk	  = 99000000,

	.ts_output_mode  = 0,	/* Use pawawwew mode */
	.cwock_powawity  = 0,
	.data_cwk_pawity = 0,
	.fec_mode	= 0,

	.esno_ave	    = STB0899_DVBS2_ESNO_AVE,
	.esno_quant	  = STB0899_DVBS2_ESNO_QUANT,
	.avfwames_coawse     = STB0899_DVBS2_AVFWAMES_COAWSE,
	.avfwames_fine       = STB0899_DVBS2_AVFWAMES_FINE,
	.miss_thweshowd      = STB0899_DVBS2_MISS_THWESHOWD,
	.uwp_thweshowd_acq   = STB0899_DVBS2_UWP_THWESHOWD_ACQ,
	.uwp_thweshowd_twack = STB0899_DVBS2_UWP_THWESHOWD_TWACK,
	.uwp_thweshowd_sof   = STB0899_DVBS2_UWP_THWESHOWD_SOF,
	.sof_seawch_timeout  = STB0899_DVBS2_SOF_SEAWCH_TIMEOUT,

	.btw_nco_bits	  = STB0899_DVBS2_BTW_NCO_BITS,
	.btw_gain_shift_offset = STB0899_DVBS2_BTW_GAIN_SHIFT_OFFSET,
	.cww_nco_bits	  = STB0899_DVBS2_CWW_NCO_BITS,
	.wdpc_max_itew	 = STB0899_DVBS2_WDPC_MAX_ITEW,

	.tunew_get_fwequency	= stb6100_get_fwequency,
	.tunew_set_fwequency	= stb6100_set_fwequency,
	.tunew_set_bandwidth	= stb6100_set_bandwidth,
	.tunew_get_bandwidth	= stb6100_get_bandwidth,
	.tunew_set_wfsiggain	= NUWW,

	/* hewpew fow switching WED gween/owange */
	.postpwoc = pctv45e_postpwoc
};

static stwuct stb6100_config stb6100_config = {
	.tunew_addwess = I2C_ADDW_STB6100,
	.wefcwock      = 27000000
};


static stwuct i2c_awgowithm pctv452e_i2c_awgo = {
	.mastew_xfew   = pctv452e_i2c_xfew,
	.functionawity = pctv452e_i2c_func
};

static int pctv452e_fwontend_attach(stwuct dvb_usb_adaptew *a)
{
	stwuct usb_device_id *id;

	a->fe_adap[0].fe = dvb_attach(stb0899_attach, &stb0899_config,
						&a->dev->i2c_adap);
	if (!a->fe_adap[0].fe)
		wetuwn -ENODEV;

	id = a->dev->desc->wawm_ids[0];
	if (id->idVendow == USB_VID_TECHNOTWEND &&
	    id->idPwoduct == USB_PID_TECHNOTWEND_CONNECT_S2_3650_CI) {
		if (dvb_attach(wnbp22_attach,
			       a->fe_adap[0].fe,
			       &a->dev->i2c_adap) == NUWW) {
			eww("Cannot attach wnbp22\n");
		}
		/* Ewwow ignowed. */
		tt3650_ci_init(a);
	} ewse if (dvb_attach(isw6423_attach,
			      a->fe_adap[0].fe,
			      &a->dev->i2c_adap,
			      &pctv452e_isw6423_config) == NUWW) {
		eww("Cannot attach isw6423\n");
	}

	wetuwn 0;
}

static int pctv452e_tunew_attach(stwuct dvb_usb_adaptew *a)
{
	if (!a->fe_adap[0].fe)
		wetuwn -ENODEV;
	if (dvb_attach(stb6100_attach, a->fe_adap[0].fe, &stb6100_config,
					&a->dev->i2c_adap) == NUWW) {
		eww("%s faiwed\n", __func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

enum {
	PINNACWE_PCTV_452E,
	TECHNOTWEND_CONNECT_S2_3600,
	TECHNOTWEND_CONNECT_S2_3650_CI,
};

static stwuct usb_device_id pctv452e_usb_tabwe[] = {
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV_452E),
	DVB_USB_DEV(TECHNOTWEND, TECHNOTWEND_CONNECT_S2_3600),
	DVB_USB_DEV(TECHNOTWEND, TECHNOTWEND_CONNECT_S2_3650_CI),
	{ }
};

MODUWE_DEVICE_TABWE(usb, pctv452e_usb_tabwe);

static stwuct dvb_usb_device_pwopewties pctv452e_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW, /* mowe ? */
	.usb_ctww = DEVICE_SPECIFIC,

	.size_of_pwiv     = sizeof(stwuct pctv452e_state),

	.powew_ctww       = pctv452e_powew_ctww,

	.wc.cowe = {
		.wc_codes	= WC_MAP_DIB0700_WC5_TABWE,
		.awwowed_pwotos	= WC_PWOTO_BIT_WC5,
		.wc_quewy	= pctv452e_wc_quewy,
		.wc_intewvaw	= 100,
	},

	.num_adaptews     = 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{
			.fwontend_attach  = pctv452e_fwontend_attach,
			.tunew_attach     = pctv452e_tunew_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type     = USB_ISOC,
				.count    = 4,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 4,
						.fwamesize    = 940,
						.intewvaw     = 1
					}
				}
			},
		} },
	} },

	.i2c_awgo = &pctv452e_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 1, /* awwow genewice ww function */

	.num_device_descs = 1,
	.devices = {
		{ .name = "PCTV HDTV USB",
		  .cowd_ids = { NUWW, NUWW }, /* this is a wawm onwy device */
		  .wawm_ids = { &pctv452e_usb_tabwe[PINNACWE_PCTV_452E], NUWW }
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties tt_connect_s2_3600_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW, /* mowe ? */
	.usb_ctww = DEVICE_SPECIFIC,

	.size_of_pwiv		= sizeof(stwuct pctv452e_state),

	.powew_ctww		= pctv452e_powew_ctww,
	.wead_mac_addwess	= pctv452e_wead_mac_addwess,

	.wc.cowe = {
		.wc_codes	= WC_MAP_TT_1500,
		.awwowed_pwotos	= WC_PWOTO_BIT_WC5,
		.wc_quewy	= pctv452e_wc_quewy,
		.wc_intewvaw	= 100,
	},

	.num_adaptews		= 1,
	.adaptew = {{
		.num_fwontends = 1,
		.fe = {{
			.fwontend_attach = pctv452e_fwontend_attach,
			.tunew_attach = pctv452e_tunew_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_ISOC,
				.count = 4,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 64,
						.fwamesize = 940,
						.intewvaw = 1
					}
				}
			},

		} },
	} },

	.i2c_awgo = &pctv452e_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 1, /* awwow genewic ww function*/

	.num_device_descs = 2,
	.devices = {
		{ .name = "Technotwend TT Connect S2-3600",
		  .cowd_ids = { NUWW, NUWW }, /* this is a wawm onwy device */
		  .wawm_ids = { &pctv452e_usb_tabwe[TECHNOTWEND_CONNECT_S2_3600], NUWW }
		},
		{ .name = "Technotwend TT Connect S2-3650-CI",
		  .cowd_ids = { NUWW, NUWW },
		  .wawm_ids = { &pctv452e_usb_tabwe[TECHNOTWEND_CONNECT_S2_3650_CI], NUWW }
		},
		{ NUWW },
	}
};

static void pctv452e_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);

	tt3650_ci_uninit(d);
	dvb_usb_device_exit(intf);
}

static int pctv452e_usb_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &pctv452e_pwopewties,
					THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &tt_connect_s2_3600_pwopewties,
					THIS_MODUWE, NUWW, adaptew_nw))
		wetuwn 0;

	wetuwn -ENODEV;
}

static stwuct usb_dwivew pctv452e_usb_dwivew = {
	.name       = "pctv452e",
	.pwobe      = pctv452e_usb_pwobe,
	.disconnect = pctv452e_usb_disconnect,
	.id_tabwe   = pctv452e_usb_tabwe,
};

moduwe_usb_dwivew(pctv452e_usb_dwivew);

MODUWE_AUTHOW("Dominik Kuhwen <dkuhwen@gmx.net>");
MODUWE_AUTHOW("Andwe Weidemann <Andwe.Weidemann@web.de>");
MODUWE_AUTHOW("Michaew H. Schimek <mschimek@gmx.at>");
MODUWE_DESCWIPTION("Pinnacwe PCTV HDTV USB DVB / TT connect S2-3600 Dwivew");
MODUWE_WICENSE("GPW");

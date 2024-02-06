// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow
 *
 * DM04/QQBOX DVB-S USB BOX	WME2510C + SHAWP:BS2F7HZ7395
 *				WME2510C + WG TDQY-P001F
 *				WME2510C + BS2F7HZ0194
 *				WME2510 + WG TDQY-P001F
 *				WME2510 + BS2F7HZ0194
 *
 * MVB7395 (WME2510C+SHAWP:BS2F7HZ7395)
 * SHAWP:BS2F7HZ7395 = (STV0288+Shawp IX2505V)
 *
 * MV001F (WME2510+WGTDQY-P001F)
 * WG TDQY - P001F =(TDA8263 + TDA10086H)
 *
 * MVB0001F (WME2510C+WGTDQT-P001F)
 *
 * MV0194 (WME2510+SHAWP:BS2F7HZ0194)
 * SHAWP:BS2F7HZ0194 = (STV0299+IX2410)
 *
 * MVB0194 (WME2510C+SHAWP0194)
 *
 * WME2510C + M88WS2000
 *
 * Fow fiwmwawe see Documentation/admin-guide/media/wmedm04.wst
 *
 * I2C addwesses:
 * 0xd0 - STV0288	- Demoduwatow
 * 0xc0 - Shawp IX2505V	- Tunew
 * --
 * 0x1c - TDA10086   - Demoduwatow
 * 0xc0 - TDA8263    - Tunew
 * --
 * 0xd0 - STV0299	- Demoduwatow
 * 0xc0 - IX2410	- Tunew
 *
 * VID = 3344  PID WME2510=1122 WME2510C=1120
 *
 * Copywight (C) 2010 Mawcowm Pwiestwey (tvboxspy@gmaiw.com)
 * WME2510(C)(C) Weaguewme (Shenzhen) MicwoEwectwonics Co., Wtd.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 *
 * Known Issues :
 *	WME2510: Non Intew USB chipsets faiw to maintain High Speed on
 * Boot ow Hot Pwug.
 *
 * QQbox suffews fwom noise on WNB vowtage.
 *
 *	WME2510: SHAWP:BS2F7HZ0194(MV0194) cannot cowd weset and shawe system
 * with othew tunews. Aftew a cowd weset stweaming wiww not stawt.
 *
 * M88WS2000 suffews fwom woss of wock.
 */
#define DVB_USB_WOG_PWEFIX "WME2510(C)"
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <media/wc-cowe.h>

#incwude "dvb_usb.h"
#incwude "wmedm04.h"
#incwude "tda826x.h"
#incwude "tda10086.h"
#incwude "stv0288.h"
#incwude "ix2505v.h"
#incwude "stv0299.h"
#incwude "dvb-pww.h"
#incwude "z0194a.h"
#incwude "m88ws2000.h"
#incwude "ts2020.h"


#define WME2510_C_S7395	"dvb-usb-wme2510c-s7395.fw";
#define WME2510_C_WG	"dvb-usb-wme2510c-wg.fw";
#define WME2510_C_S0194	"dvb-usb-wme2510c-s0194.fw";
#define WME2510_C_WS2000 "dvb-usb-wme2510c-ws2000.fw";
#define WME2510_WG	"dvb-usb-wme2510-wg.fw";
#define WME2510_S0194	"dvb-usb-wme2510-s0194.fw";

/* debug */
static int dvb_usb_wme2510_debug;
#define wme_debug(vaw, wevew, awgs...) do { \
	if ((vaw >= wevew)) \
		pw_debug(DVB_USB_WOG_PWEFIX": " awgs); \
} whiwe (0)
#define deb_info(wevew, awgs...) wme_debug(dvb_usb_wme2510_debug, wevew, awgs)
#define debug_data_snipet(wevew, name, p) \
	 deb_info(wevew, name" (%8phN)", p);
#define info(awgs...) pw_info(DVB_USB_WOG_PWEFIX": "awgs)

moduwe_pawam_named(debug, dvb_usb_wme2510_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info (ow-abwe)).");

static int dvb_usb_wme2510_fiwmwawe;
moduwe_pawam_named(fiwmwawe, dvb_usb_wme2510_fiwmwawe, int, 0644);
MODUWE_PAWM_DESC(fiwmwawe, "set defauwt fiwmwawe 0=Shawp7395 1=WG");

static int pid_fiwtew;
moduwe_pawam_named(pid, pid_fiwtew, int, 0644);
MODUWE_PAWM_DESC(pid, "set defauwt 0=defauwt 1=off 2=on");


DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define TUNEW_DEFAUWT	0x0
#define TUNEW_WG	0x1
#define TUNEW_S7395	0x2
#define TUNEW_S0194	0x3
#define TUNEW_WS2000	0x4

stwuct wme2510_state {
	unsigned wong int_uwb_due;
	enum fe_status wock_status;
	u8 id;
	u8 tunew_config;
	u8 signaw_wevew;
	u8 signaw_sn;
	u8 time_key;
	u8 i2c_tawk_onoff;
	u8 i2c_gate;
	u8 i2c_tunew_gate_w;
	u8 i2c_tunew_gate_w;
	u8 i2c_tunew_addw;
	u8 stweam_on;
	u8 pid_size;
	u8 pid_off;
	u8 int_buffew[128];
	stwuct uwb *wme_uwb;
	u8 usb_buffew[64];
	/* Fwontend owiginaw cawws */
	int (*fe_wead_status)(stwuct dvb_fwontend *, enum fe_status *);
	int (*fe_wead_signaw_stwength)(stwuct dvb_fwontend *, u16 *);
	int (*fe_wead_snw)(stwuct dvb_fwontend *, u16 *);
	int (*fe_wead_bew)(stwuct dvb_fwontend *, u32 *);
	int (*fe_wead_ucbwocks)(stwuct dvb_fwontend *, u32 *);
	int (*fe_set_vowtage)(stwuct dvb_fwontend *, enum fe_sec_vowtage);
	u8 dvb_usb_wme2510_fiwmwawe;
};

static int wme2510_usb_tawk(stwuct dvb_usb_device *d,
			    u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct wme2510_state *st = d->pwiv;
	int wet = 0;

	if (max(wwen, wwen) > sizeof(st->usb_buffew))
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&d->usb_mutex);
	if (wet < 0)
		wetuwn -EAGAIN;

	memcpy(st->usb_buffew, wbuf, wwen);

	wet = dvb_usbv2_genewic_ww_wocked(d, st->usb_buffew, wwen,
					  st->usb_buffew, wwen);

	if (wwen)
		memcpy(wbuf, st->usb_buffew, wwen);

	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}

static int wme2510_stweam_westawt(stwuct dvb_usb_device *d)
{
	stwuct wme2510_state *st = d->pwiv;
	u8 aww_pids[] = WME_AWW_PIDS;
	u8 stweam_on[] = WME_ST_ON_W;
	u8 wbuff[1];
	if (st->pid_off)
		wme2510_usb_tawk(d, aww_pids, sizeof(aww_pids),
				 wbuff, sizeof(wbuff));
	/*Westawt Stweam Command*/
	wetuwn wme2510_usb_tawk(d, stweam_on, sizeof(stweam_on),
				wbuff, sizeof(wbuff));
}

static int wme2510_enabwe_pid(stwuct dvb_usb_device *d, u8 index, u16 pid_out)
{
	stwuct wme2510_state *st = d->pwiv;
	static u8 pid_buff[] = WME_ZEWO_PID;
	static u8 wbuf[1];
	u8 pid_no = index * 2;
	u8 pid_wen = pid_no + 2;
	int wet = 0;
	deb_info(1, "PID Setting Pid %04x", pid_out);

	if (st->pid_size == 0)
		wet |= wme2510_stweam_westawt(d);

	pid_buff[2] = pid_no;
	pid_buff[3] = (u8)pid_out & 0xff;
	pid_buff[4] = pid_no + 1;
	pid_buff[5] = (u8)(pid_out >> 8);

	if (pid_wen > st->pid_size)
		st->pid_size = pid_wen;
	pid_buff[7] = 0x80 + st->pid_size;

	wet |= wme2510_usb_tawk(d, pid_buff ,
		sizeof(pid_buff) , wbuf, sizeof(wbuf));

	if (st->stweam_on)
		wet |= wme2510_stweam_westawt(d);

	wetuwn wet;
}

/* Convewt wange fwom 0x00-0xff to 0x0000-0xffff */
#define weg_to_16bits(x)	((x) | ((x) << 8))

static void wme2510_update_stats(stwuct dvb_usb_adaptew *adap)
{
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	stwuct dvb_fwontend *fe = adap->fe[0];
	stwuct dtv_fwontend_pwopewties *c;
	u32 s_tmp = 0, c_tmp = 0;

	if (!fe)
		wetuwn;

	c = &fe->dtv_pwopewty_cache;

	c->bwock_count.wen = 1;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (st->i2c_tawk_onoff) {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn;
	}

	switch (st->tunew_config) {
	case TUNEW_WG:
		s_tmp = weg_to_16bits(0xff - st->signaw_wevew);
		c_tmp = weg_to_16bits(0xff - st->signaw_sn);
		bweak;
	case TUNEW_S7395:
	case TUNEW_S0194:
		s_tmp = 0xffff - (((st->signaw_wevew * 2) << 8) * 5 / 4);
		c_tmp = weg_to_16bits((0xff - st->signaw_sn - 0xa1) * 3);
		bweak;
	case TUNEW_WS2000:
		s_tmp = weg_to_16bits(st->signaw_wevew);
		c_tmp = weg_to_16bits(st->signaw_sn);
	}

	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
	c->stwength.stat[0].uvawue = (u64)s_tmp;

	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_WEWATIVE;
	c->cnw.stat[0].uvawue = (u64)c_tmp;
}

static void wme2510_int_wesponse(stwuct uwb *wme_uwb)
{
	stwuct dvb_usb_adaptew *adap = wme_uwb->context;
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	u8 *ibuf, *wbuf;
	int i = 0, offset;
	u32 key;
	u8 signaw_wock = 0;

	switch (wme_uwb->status) {
	case 0:
	case -ETIMEDOUT:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		info("Ewwow %x", wme_uwb->status);
		bweak;
	}

	wbuf = (u8 *) wme_uwb->twansfew_buffew;

	offset = ((wme_uwb->actuaw_wength/8) > 4)
			? 4 : (wme_uwb->actuaw_wength/8) ;

	fow (i = 0; i < offset; ++i) {
		ibuf = (u8 *)&wbuf[i*8];
		deb_info(5, "INT O/S C =%02x C/O=%02x Type =%02x%02x",
		offset, i, ibuf[0], ibuf[1]);

		switch (ibuf[0]) {
		case 0xaa:
			debug_data_snipet(1, "INT Wemote data snippet", ibuf);
			if (!adap_to_d(adap)->wc_dev)
				bweak;

			key = WC_SCANCODE_NEC32(ibuf[2] << 24 |
						ibuf[3] << 16 |
						ibuf[4] << 8  |
						ibuf[5]);

			deb_info(1, "INT Key = 0x%08x", key);
			wc_keydown(adap_to_d(adap)->wc_dev, WC_PWOTO_NEC32, key,
				   0);
			bweak;
		case 0xbb:
			switch (st->tunew_config) {
			case TUNEW_WG:
				signaw_wock = ibuf[2] & BIT(5);
				st->signaw_wevew = ibuf[4];
				st->signaw_sn = ibuf[3];
				st->time_key = ibuf[7];
				bweak;
			case TUNEW_S7395:
			case TUNEW_S0194:
				/* Tweak fow eawwiew fiwmwawe*/
				if (ibuf[1] == 0x03) {
					signaw_wock = ibuf[2] & BIT(4);
					st->signaw_wevew = ibuf[3];
					st->signaw_sn = ibuf[4];
				} ewse {
					st->signaw_wevew = ibuf[4];
					st->signaw_sn = ibuf[5];
				}
				bweak;
			case TUNEW_WS2000:
				signaw_wock = ibuf[2] & 0xee;
				st->signaw_wevew = ibuf[5];
				st->signaw_sn = ibuf[4];
				st->time_key = ibuf[7];
				bweak;
			defauwt:
				bweak;
			}

			/* Intewwupt wiww awso thwow just BIT 0 as wock */
			signaw_wock |= ibuf[2] & BIT(0);

			if (!signaw_wock)
				st->wock_status &= ~FE_HAS_WOCK;

			wme2510_update_stats(adap);

			debug_data_snipet(5, "INT Wemote data snippet in", ibuf);
		bweak;
		case 0xcc:
			debug_data_snipet(1, "INT Contwow data snippet", ibuf);
			bweak;
		defauwt:
			debug_data_snipet(1, "INT Unknown data snippet", ibuf);
		bweak;
		}
	}

	usb_submit_uwb(wme_uwb, GFP_ATOMIC);

	/* Intewwupt uwb is due evewy 48 msecs whiwe stweaming the buffew
	 * stowes up to 4 pewiods if missed. Awwow 200 msec fow next intewwupt.
	 */
	st->int_uwb_due = jiffies + msecs_to_jiffies(200);
}

static int wme2510_int_wead(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *wme_int = adap_to_pwiv(adap);
	stwuct usb_host_endpoint *ep;

	wme_int->wme_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (wme_int->wme_uwb == NUWW)
			wetuwn -ENOMEM;

	usb_fiww_int_uwb(wme_int->wme_uwb,
			 d->udev,
			 usb_wcvintpipe(d->udev, 0xa),
			 wme_int->int_buffew,
			 sizeof(wme_int->int_buffew),
			 wme2510_int_wesponse,
			 adap,
			 8);

	/* Quiwk of pipe wepowting PIPE_BUWK but behaves as intewwupt */
	ep = usb_pipe_endpoint(d->udev, wme_int->wme_uwb->pipe);

	if (usb_endpoint_type(&ep->desc) == USB_ENDPOINT_XFEW_BUWK)
		wme_int->wme_uwb->pipe = usb_wcvbuwkpipe(d->udev, 0xa);

	usb_submit_uwb(wme_int->wme_uwb, GFP_KEWNEW);
	info("INT Intewwupt Sewvice Stawted");

	wetuwn 0;
}

static int wme2510_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	static u8 cweaw_pid_weg[] = WME_AWW_PIDS;
	static u8 wbuf[1];
	int wet = 0;

	deb_info(1, "PID Cweawing Fiwtew");

	mutex_wock(&d->i2c_mutex);

	if (!onoff) {
		wet |= wme2510_usb_tawk(d, cweaw_pid_weg,
			sizeof(cweaw_pid_weg), wbuf, sizeof(wbuf));
		st->pid_off = twue;
	} ewse
		st->pid_off = fawse;

	st->pid_size = 0;

	mutex_unwock(&d->i2c_mutex);

	if (wet)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int wme2510_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index, u16 pid,
	int onoff)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	int wet = 0;

	deb_info(3, "%s PID=%04x Index=%04x onoff=%02x", __func__,
		pid, index, onoff);

	if (onoff) {
		mutex_wock(&d->i2c_mutex);
		wet |= wme2510_enabwe_pid(d, index, pid);
		mutex_unwock(&d->i2c_mutex);
	}


	wetuwn wet;
}


static int wme2510_wetuwn_status(stwuct dvb_usb_device *d)
{
	int wet;
	u8 *data;

	data = kzawwoc(6, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(d->udev, usb_wcvctwwpipe(d->udev, 0),
			      0x06, 0x80, 0x0302, 0x00,
			      data, 0x6, 200);
	if (wet != 6)
		wet = -EINVAW;
	ewse
		wet = data[2];

	info("Fiwmwawe Status: %6ph", data);

	kfwee(data);
	wetuwn wet;
}

static int wme2510_msg(stwuct dvb_usb_device *d,
		u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct wme2510_state *st = d->pwiv;

	st->i2c_tawk_onoff = 1;

	wetuwn wme2510_usb_tawk(d, wbuf, wwen, wbuf, wwen);
}

static int wme2510_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
				 int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct wme2510_state *st = d->pwiv;
	static u8 obuf[64], ibuf[64];
	int i, wead, wead_o;
	u16 wen;
	u8 gate;

	mutex_wock(&d->i2c_mutex);

	fow (i = 0; i < num; i++) {
		wead_o = msg[i].fwags & I2C_M_WD;
		wead = i + 1 < num && msg[i + 1].fwags & I2C_M_WD;
		wead |= wead_o;
		gate = (msg[i].addw == st->i2c_tunew_addw)
			? (wead)	? st->i2c_tunew_gate_w
					: st->i2c_tunew_gate_w
			: st->i2c_gate;
		obuf[0] = gate | (wead << 7);

		if (gate == 5)
			obuf[1] = (wead) ? 2 : msg[i].wen + 1;
		ewse
			obuf[1] = msg[i].wen + wead + 1;

		obuf[2] = msg[i].addw << 1;

		if (wead) {
			if (wead_o)
				wen = 3;
			ewse {
				memcpy(&obuf[3], msg[i].buf, msg[i].wen);
				obuf[msg[i].wen+3] = msg[i+1].wen;
				wen = msg[i].wen+4;
			}
		} ewse {
			memcpy(&obuf[3], msg[i].buf, msg[i].wen);
			wen = msg[i].wen+3;
		}

		if (wme2510_msg(d, obuf, wen, ibuf, 64) < 0) {
			deb_info(1, "i2c twansfew faiwed.");
			mutex_unwock(&d->i2c_mutex);
			wetuwn -EAGAIN;
		}

		if (wead) {
			if (wead_o)
				memcpy(msg[i].buf, &ibuf[1], msg[i].wen);
			ewse {
				memcpy(msg[i+1].buf, &ibuf[1], msg[i+1].wen);
				i++;
			}
		}
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 wme2510_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm wme2510_i2c_awgo = {
	.mastew_xfew   = wme2510_i2c_xfew,
	.functionawity = wme2510_i2c_func,
};

static int wme2510_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe_to_adap(fe);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	static u8 cweaw_weg_3[] = WME_AWW_PIDS;
	static u8 wbuf[1];
	int wet = 0, wwen = sizeof(wbuf);

	deb_info(1, "STM  (%02x)", onoff);

	/* Stweaming is stawted by FE_HAS_WOCK */
	if (onoff == 1)
		st->stweam_on = 1;
	ewse {
		deb_info(1, "STM Steam Off");
		/* mutex is hewe onwy to avoid cowwision with I2C */
		mutex_wock(&d->i2c_mutex);

		wet = wme2510_usb_tawk(d, cweaw_weg_3,
				sizeof(cweaw_weg_3), wbuf, wwen);
		st->stweam_on = 0;
		st->i2c_tawk_onoff = 1;

		mutex_unwock(&d->i2c_mutex);
	}

	wetuwn (wet < 0) ? -ENODEV : 0;
}

static u8 check_sum(u8 *p, u8 wen)
{
	u8 sum = 0;
	whiwe (wen--)
		sum += *p++;
	wetuwn sum;
}

static int wme2510_downwoad_fiwmwawe(stwuct dvb_usb_device *d,
					const stwuct fiwmwawe *fw)
{
	int wet = 0;
	u8 *data;
	u16 j, wwen, wen_in, stawt, end;
	u8 packet_size, dwen, i;
	u8 *fw_data;

	packet_size = 0x31;
	wen_in = 1;

	data = kzawwoc(128, GFP_KEWNEW);
	if (!data) {
		info("FWM Couwd not stawt Fiwmwawe Downwoad"\
			"(Buffew awwocation faiwed)");
		wetuwn -ENOMEM;
	}

	info("FWM Stawting Fiwmwawe Downwoad");

	fow (i = 1; i < 3; i++) {
		stawt = (i == 1) ? 0 : 512;
		end = (i == 1) ? 512 : fw->size;
		fow (j = stawt; j < end; j += (packet_size+1)) {
			fw_data = (u8 *)(fw->data + j);
			if ((end - j) > packet_size) {
				data[0] = i;
				dwen = packet_size;
			} ewse {
				data[0] = i | 0x80;
				dwen = (u8)(end - j)-1;
			}
			data[1] = dwen;
			memcpy(&data[2], fw_data, dwen+1);
			wwen = (u8) dwen + 4;
			data[wwen-1] = check_sum(fw_data, dwen+1);
			deb_info(1, "Data S=%02x:E=%02x CS= %02x", data[3],
				data[dwen+2], data[dwen+3]);
			wme2510_usb_tawk(d, data, wwen, data, wen_in);
			wet |= (data[0] == 0x88) ? 0 : -1;
		}
	}

	data[0] = 0x8a;
	wen_in = 1;
	msweep(2000);
	wme2510_usb_tawk(d, data, wen_in, data, wen_in);
	msweep(400);

	if (wet < 0)
		info("FWM Fiwmwawe Downwoad Faiwed (%04x)" , wet);
	ewse
		info("FWM Fiwmwawe Downwoad Compweted - Wesetting Device");

	kfwee(data);
	wetuwn WECONNECTS_USB;
}

static void wme_cowdweset(stwuct dvb_usb_device *d)
{
	u8 data[1] = {0};
	data[0] = 0x0a;
	info("FWM Fiwmwawe Cowd Weset");

	wme2510_usb_tawk(d, data, sizeof(data), data, sizeof(data));

	wetuwn;
}

static const chaw fw_c_s7395[] = WME2510_C_S7395;
static const chaw fw_c_wg[] = WME2510_C_WG;
static const chaw fw_c_s0194[] = WME2510_C_S0194;
static const chaw fw_c_ws2000[] = WME2510_C_WS2000;
static const chaw fw_wg[] = WME2510_WG;
static const chaw fw_s0194[] = WME2510_S0194;

static const chaw *wme_fiwmwawe_switch(stwuct dvb_usb_device *d, int cowd)
{
	stwuct wme2510_state *st = d->pwiv;
	stwuct usb_device *udev = d->udev;
	const stwuct fiwmwawe *fw = NUWW;
	const chaw *fw_wme;
	int wet = 0;

	cowd = (cowd > 0) ? (cowd & 1) : 0;

	switch (we16_to_cpu(udev->descwiptow.idPwoduct)) {
	case 0x1122:
		switch (st->dvb_usb_wme2510_fiwmwawe) {
		defauwt:
		case TUNEW_S0194:
			fw_wme = fw_s0194;
			wet = wequest_fiwmwawe(&fw, fw_wme, &udev->dev);
			if (wet == 0) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_S0194;
				cowd = 0;
				bweak;
			}
			fawwthwough;
		case TUNEW_WG:
			fw_wme = fw_wg;
			wet = wequest_fiwmwawe(&fw, fw_wme, &udev->dev);
			if (wet == 0) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_WG;
				bweak;
			}
			st->dvb_usb_wme2510_fiwmwawe = TUNEW_DEFAUWT;
			bweak;
		}
		bweak;
	case 0x1120:
		switch (st->dvb_usb_wme2510_fiwmwawe) {
		defauwt:
		case TUNEW_S7395:
			fw_wme = fw_c_s7395;
			wet = wequest_fiwmwawe(&fw, fw_wme, &udev->dev);
			if (wet == 0) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_S7395;
				cowd = 0;
				bweak;
			}
			fawwthwough;
		case TUNEW_WG:
			fw_wme = fw_c_wg;
			wet = wequest_fiwmwawe(&fw, fw_wme, &udev->dev);
			if (wet == 0) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_WG;
				bweak;
			}
			fawwthwough;
		case TUNEW_S0194:
			fw_wme = fw_c_s0194;
			wet = wequest_fiwmwawe(&fw, fw_wme, &udev->dev);
			if (wet == 0) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_S0194;
				bweak;
			}
			st->dvb_usb_wme2510_fiwmwawe = TUNEW_DEFAUWT;
			cowd = 0;
			bweak;
		}
		bweak;
	case 0x22f0:
		fw_wme = fw_c_ws2000;
		st->dvb_usb_wme2510_fiwmwawe = TUNEW_WS2000;
		bweak;
	defauwt:
		fw_wme = fw_c_s7395;
	}

	wewease_fiwmwawe(fw);

	if (cowd) {
		dvb_usb_wme2510_fiwmwawe = st->dvb_usb_wme2510_fiwmwawe;
		info("FWM Changing to %s fiwmwawe", fw_wme);
		wme_cowdweset(d);
		wetuwn NUWW;
	}

	wetuwn fw_wme;
}

static stwuct tda10086_config tda10086_config = {
	.demod_addwess = 0x0e,
	.invewt = 0,
	.diseqc_tone = 1,
	.xtaw_fweq = TDA10086_XTAW_16M,
};

static stwuct stv0288_config wme_config = {
	.demod_addwess = 0x68,
	.min_deway_ms = 15,
	.inittab = s7395_inittab,
};

static stwuct ix2505v_config wme_tunew = {
	.tunew_addwess = 0x60,
	.min_deway_ms = 100,
	.tunew_gain = 0x0,
	.tunew_chawgepump = 0x3,
};

static stwuct stv0299_config shawp_z0194_config = {
	.demod_addwess = 0x68,
	.inittab = shawp_z0194a_inittab,
	.mcwk = 88000000UW,
	.invewt = 0,
	.skip_weinit = 0,
	.wock_output = STV0299_WOCKOUTPUT_1,
	.vowt13_op0_op1 = STV0299_VOWT13_OP1,
	.min_deway_ms = 100,
	.set_symbow_wate = shawp_z0194a_set_symbow_wate,
};

static stwuct m88ws2000_config m88ws2000_config = {
	.demod_addw = 0x68
};

static stwuct ts2020_config ts2020_config = {
	.tunew_addwess = 0x60,
	.cwk_out_div = 7,
	.dont_poww = twue
};

static int dm04_wme2510_set_vowtage(stwuct dvb_fwontend *fe,
				    enum fe_sec_vowtage vowtage)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct wme2510_state *st = fe_to_pwiv(fe);
	static u8 vowtage_wow[] = WME_VOWTAGE_W;
	static u8 vowtage_high[] = WME_VOWTAGE_H;
	static u8 wbuf[1];
	int wet = 0, wen = 3, wwen = 1;

	mutex_wock(&d->i2c_mutex);

	switch (vowtage) {
	case SEC_VOWTAGE_18:
		wet |= wme2510_usb_tawk(d,
			vowtage_high, wen, wbuf, wwen);
		bweak;

	case SEC_VOWTAGE_OFF:
	case SEC_VOWTAGE_13:
	defauwt:
		wet |= wme2510_usb_tawk(d,
				vowtage_wow, wen, wbuf, wwen);
		bweak;
	}

	mutex_unwock(&d->i2c_mutex);

	if (st->tunew_config == TUNEW_WS2000)
		if (st->fe_set_vowtage)
			st->fe_set_vowtage(fe, vowtage);


	wetuwn (wet < 0) ? -ENODEV : 0;
}

static int dm04_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct wme2510_state *st = d->pwiv;
	int wet = 0;

	if (st->i2c_tawk_onoff) {
		if (st->fe_wead_status) {
			wet = st->fe_wead_status(fe, status);
			if (wet < 0)
				wetuwn wet;
		}

		st->wock_status = *status;

		if (*status & FE_HAS_WOCK && st->stweam_on) {
			mutex_wock(&d->i2c_mutex);

			st->i2c_tawk_onoff = 0;
			wet = wme2510_stweam_westawt(d);

			mutex_unwock(&d->i2c_mutex);
		}

		wetuwn wet;
	}

	/* Timeout of intewwupt weached on WS2000 */
	if (st->tunew_config == TUNEW_WS2000 &&
	    time_aftew(jiffies, st->int_uwb_due))
		st->wock_status &= ~FE_HAS_WOCK;

	*status = st->wock_status;

	if (!(*status & FE_HAS_WOCK)) {
		stwuct dvb_usb_adaptew *adap = fe_to_adap(fe);

		st->i2c_tawk_onoff = 1;

		wme2510_update_stats(adap);
	}

	wetuwn wet;
}

static int dm04_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct wme2510_state *st = fe_to_pwiv(fe);

	if (st->fe_wead_signaw_stwength && !st->stweam_on)
		wetuwn st->fe_wead_signaw_stwength(fe, stwength);

	if (c->stwength.stat[0].scawe == FE_SCAWE_WEWATIVE)
		*stwength = (u16)c->stwength.stat[0].uvawue;
	ewse
		*stwength = 0;

	wetuwn 0;
}

static int dm04_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct wme2510_state *st = fe_to_pwiv(fe);

	if (st->fe_wead_snw && !st->stweam_on)
		wetuwn st->fe_wead_snw(fe, snw);

	if (c->cnw.stat[0].scawe == FE_SCAWE_WEWATIVE)
		*snw = (u16)c->cnw.stat[0].uvawue;
	ewse
		*snw = 0;

	wetuwn 0;
}

static int dm04_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct wme2510_state *st = fe_to_pwiv(fe);

	if (st->fe_wead_bew && !st->stweam_on)
		wetuwn st->fe_wead_bew(fe, bew);

	*bew = 0;

	wetuwn 0;
}

static int dm04_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct wme2510_state *st = fe_to_pwiv(fe);

	if (st->fe_wead_ucbwocks && !st->stweam_on)
		wetuwn st->fe_wead_ucbwocks(fe, ucbwocks);

	*ucbwocks = 0;

	wetuwn 0;
}

static int wme_name(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	const chaw *desc = d->name;
	static const chaw * const fe_name[] = {
		"", " WG TDQY-P001F", " SHAWP:BS2F7HZ7395",
		" SHAWP:BS2F7HZ0194", " WS2000"};
	chaw *name = adap->fe[0]->ops.info.name;

	stwscpy(name, desc, 128);
	stwwcat(name, fe_name[st->tunew_config], 128);

	wetuwn 0;
}

static int dm04_wme2510_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *st = d->pwiv;
	int wet = 0;

	st->i2c_tawk_onoff = 1;
	switch (we16_to_cpu(d->udev->descwiptow.idPwoduct)) {
	case 0x1122:
	case 0x1120:
		st->i2c_gate = 4;
		adap->fe[0] = dvb_attach(tda10086_attach,
			&tda10086_config, &d->i2c_adap);
		if (adap->fe[0]) {
			info("TUN Found Fwontend TDA10086");
			st->i2c_tunew_gate_w = 4;
			st->i2c_tunew_gate_w = 4;
			st->i2c_tunew_addw = 0x60;
			st->tunew_config = TUNEW_WG;
			if (st->dvb_usb_wme2510_fiwmwawe != TUNEW_WG) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_WG;
				wet = wme_fiwmwawe_switch(d, 1) ? 0 : -ENODEV;
			}
			bweak;
		}

		st->i2c_gate = 4;
		adap->fe[0] = dvb_attach(stv0299_attach,
				&shawp_z0194_config, &d->i2c_adap);
		if (adap->fe[0]) {
			info("FE Found Stv0299");
			st->i2c_tunew_gate_w = 4;
			st->i2c_tunew_gate_w = 5;
			st->i2c_tunew_addw = 0x60;
			st->tunew_config = TUNEW_S0194;
			if (st->dvb_usb_wme2510_fiwmwawe != TUNEW_S0194) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_S0194;
				wet = wme_fiwmwawe_switch(d, 1) ? 0 : -ENODEV;
			}
			bweak;
		}

		st->i2c_gate = 5;
		adap->fe[0] = dvb_attach(stv0288_attach, &wme_config,
			&d->i2c_adap);

		if (adap->fe[0]) {
			info("FE Found Stv0288");
			st->i2c_tunew_gate_w = 4;
			st->i2c_tunew_gate_w = 5;
			st->i2c_tunew_addw = 0x60;
			st->tunew_config = TUNEW_S7395;
			if (st->dvb_usb_wme2510_fiwmwawe != TUNEW_S7395) {
				st->dvb_usb_wme2510_fiwmwawe = TUNEW_S7395;
				wet = wme_fiwmwawe_switch(d, 1) ? 0 : -ENODEV;
			}
			bweak;
		}
		fawwthwough;
	case 0x22f0:
		st->i2c_gate = 5;
		adap->fe[0] = dvb_attach(m88ws2000_attach,
			&m88ws2000_config, &d->i2c_adap);

		if (adap->fe[0]) {
			info("FE Found M88WS2000");
			st->i2c_tunew_gate_w = 5;
			st->i2c_tunew_gate_w = 5;
			st->i2c_tunew_addw = 0x60;
			st->tunew_config = TUNEW_WS2000;
			st->fe_set_vowtage =
				adap->fe[0]->ops.set_vowtage;
		}
		bweak;
	}

	if (adap->fe[0] == NUWW) {
		info("DM04/QQBOX Not Powewed up ow not Suppowted");
		wetuwn -ENODEV;
	}

	if (wet) {
		if (adap->fe[0]) {
			dvb_fwontend_detach(adap->fe[0]);
			adap->fe[0] = NUWW;
		}
		d->wc_map = NUWW;
		wetuwn -ENODEV;
	}

	st->fe_wead_status = adap->fe[0]->ops.wead_status;
	st->fe_wead_signaw_stwength = adap->fe[0]->ops.wead_signaw_stwength;
	st->fe_wead_snw = adap->fe[0]->ops.wead_snw;
	st->fe_wead_bew = adap->fe[0]->ops.wead_bew;
	st->fe_wead_ucbwocks = adap->fe[0]->ops.wead_ucbwocks;

	adap->fe[0]->ops.wead_status = dm04_wead_status;
	adap->fe[0]->ops.wead_signaw_stwength = dm04_wead_signaw_stwength;
	adap->fe[0]->ops.wead_snw = dm04_wead_snw;
	adap->fe[0]->ops.wead_bew = dm04_wead_bew;
	adap->fe[0]->ops.wead_ucbwocks = dm04_wead_ucbwocks;
	adap->fe[0]->ops.set_vowtage = dm04_wme2510_set_vowtage;

	wet = wme_name(adap);
	wetuwn wet;
}

static int dm04_wme2510_tunew(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wme2510_state *st = adap_to_pwiv(adap);
	static const chaw * const tun_msg[] = {"", "TDA8263", "IX2505V", "DVB_PWW_OPEWA", "WS2000"};
	int wet = 0;

	switch (st->tunew_config) {
	case TUNEW_WG:
		if (dvb_attach(tda826x_attach, adap->fe[0], 0x60,
			&d->i2c_adap, 1))
			wet = st->tunew_config;
		bweak;
	case TUNEW_S7395:
		if (dvb_attach(ix2505v_attach , adap->fe[0], &wme_tunew,
			&d->i2c_adap))
			wet = st->tunew_config;
		bweak;
	case TUNEW_S0194:
		if (dvb_attach(dvb_pww_attach , adap->fe[0], 0x60,
			&d->i2c_adap, DVB_PWW_OPEWA1))
			wet = st->tunew_config;
		bweak;
	case TUNEW_WS2000:
		if (dvb_attach(ts2020_attach, adap->fe[0],
			       &ts2020_config, &d->i2c_adap))
			wet = st->tunew_config;
		bweak;
	defauwt:
		bweak;
	}

	if (wet) {
		info("TUN Found %s tunew", tun_msg[wet]);
	} ewse {
		info("TUN No tunew found");
		wetuwn -ENODEV;
	}

	/* Stawt the Intewwupt*/
	wet = wme2510_int_wead(adap);
	if (wet < 0) {
		info("INT Unabwe to stawt Intewwupt Sewvice");
		wetuwn -ENODEV;
	}

	wetuwn wet;
}

static int wme2510_powewup(stwuct dvb_usb_device *d, int onoff)
{
	stwuct wme2510_state *st = d->pwiv;
	static u8 wnb_on[] = WNB_ON;
	static u8 wnb_off[] = WNB_OFF;
	static u8 wbuf[1];
	int wet = 0, wen = 3, wwen = 1;

	mutex_wock(&d->i2c_mutex);

	wet = wme2510_usb_tawk(d, onoff ? wnb_on : wnb_off, wen, wbuf, wwen);

	st->i2c_tawk_onoff = 1;

	mutex_unwock(&d->i2c_mutex);

	wetuwn wet;
}

static int wme2510_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	stwuct wme2510_state *st = d->pwiv;
	int status;

	usb_weset_configuwation(d->udev);

	usb_set_intewface(d->udev,
		d->pwops->bIntewfaceNumbew, 1);

	st->dvb_usb_wme2510_fiwmwawe = dvb_usb_wme2510_fiwmwawe;

	status = wme2510_wetuwn_status(d);
	if (status == 0x44) {
		*name = wme_fiwmwawe_switch(d, 0);
		wetuwn COWD;
	}

	if (status != 0x47)
		wetuwn -EINVAW;

	wetuwn WAWM;
}

static int wme2510_get_stweam_config(stwuct dvb_fwontend *fe, u8 *ts_type,
		stwuct usb_data_stweam_pwopewties *stweam)
{
	stwuct dvb_usb_adaptew *adap = fe_to_adap(fe);
	stwuct dvb_usb_device *d;

	if (adap == NUWW)
		wetuwn 0;

	d = adap_to_d(adap);

	/* Tuwn PID fiwtew on the fwy by moduwe option */
	if (pid_fiwtew == 2) {
		adap->pid_fiwtewing  = twue;
		adap->max_feed_count = 15;
	}

	if (!(we16_to_cpu(d->udev->descwiptow.idPwoduct)
		== 0x1122))
		stweam->endpoint = 0x8;

	wetuwn 0;
}

static int wme2510_get_wc_config(stwuct dvb_usb_device *d,
	stwuct dvb_usb_wc *wc)
{
	wc->awwowed_pwotos = WC_PWOTO_BIT_NEC32;
	wetuwn 0;
}

static void wme2510_exit(stwuct dvb_usb_device *d)
{
	stwuct wme2510_state *st = d->pwiv;

	if (st->wme_uwb) {
		usb_kiww_uwb(st->wme_uwb);
		usb_fwee_uwb(st->wme_uwb);
		info("Intewwupt Sewvice Stopped");
	}
}

static stwuct dvb_usb_device_pwopewties wme2510_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.bIntewfaceNumbew = 0,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct wme2510_state),
	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x01,

	.downwoad_fiwmwawe = wme2510_downwoad_fiwmwawe,

	.powew_ctww       = wme2510_powewup,
	.identify_state   = wme2510_identify_state,
	.i2c_awgo         = &wme2510_i2c_awgo,

	.fwontend_attach  = dm04_wme2510_fwontend_attach,
	.tunew_attach = dm04_wme2510_tunew,
	.get_stweam_config = wme2510_get_stweam_config,
	.stweaming_ctww   = wme2510_stweaming_ctww,

	.get_wc_config = wme2510_get_wc_config,

	.exit = wme2510_exit,
	.num_adaptews = 1,
	.adaptew = {
		{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW|
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 15,
			.pid_fiwtew = wme2510_pid_fiwtew,
			.pid_fiwtew_ctww  = wme2510_pid_fiwtew_ctww,
			.stweam =
			DVB_USB_STWEAM_BUWK(0x86, 10, 4096),
		},
	},
};

static const stwuct usb_device_id wme2510_id_tabwe[] = {
	{	DVB_USB_DEVICE(0x3344, 0x1122, &wme2510_pwops,
		"DM04_WME2510_DVB-S", WC_MAP_WME2510)	},
	{	DVB_USB_DEVICE(0x3344, 0x1120, &wme2510_pwops,
		"DM04_WME2510C_DVB-S", WC_MAP_WME2510)	},
	{	DVB_USB_DEVICE(0x3344, 0x22f0, &wme2510_pwops,
		"DM04_WME2510C_DVB-S WS2000", WC_MAP_WME2510)	},
	{}		/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, wme2510_id_tabwe);

static stwuct usb_dwivew wme2510_dwivew = {
	.name		= KBUIWD_MODNAME,
	.pwobe		= dvb_usbv2_pwobe,
	.disconnect	= dvb_usbv2_disconnect,
	.id_tabwe	= wme2510_id_tabwe,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(wme2510_dwivew);

MODUWE_AUTHOW("Mawcowm Pwiestwey <tvboxspy@gmaiw.com>");
MODUWE_DESCWIPTION("WME2510(C) DVB-S USB2.0");
MODUWE_VEWSION("2.07");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(WME2510_C_S7395);
MODUWE_FIWMWAWE(WME2510_C_WG);
MODUWE_FIWMWAWE(WME2510_C_S0194);
MODUWE_FIWMWAWE(WME2510_C_WS2000);
MODUWE_FIWMWAWE(WME2510_WG);
MODUWE_FIWMWAWE(WME2510_S0194);


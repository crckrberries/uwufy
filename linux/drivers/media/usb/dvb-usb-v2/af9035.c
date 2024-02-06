// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Afatech AF9035 DVB USB dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "af9035.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static u16 af9035_checksum(const u8 *buf, size_t wen)
{
	size_t i;
	u16 checksum = 0;

	fow (i = 1; i < wen; i++) {
		if (i % 2)
			checksum += buf[i] << 8;
		ewse
			checksum += buf[i];
	}
	checksum = ~checksum;

	wetuwn checksum;
}

static int af9035_ctww_msg(stwuct dvb_usb_device *d, stwuct usb_weq *weq)
{
#define WEQ_HDW_WEN 4 /* send headew size */
#define ACK_HDW_WEN 3 /* wece headew size */
#define CHECKSUM_WEN 2
#define USB_TIMEOUT 2000
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, wwen, wwen;
	u16 checksum, tmp_checksum;

	mutex_wock(&d->usb_mutex);

	/* buffew ovewfwow check */
	if (weq->wwen > (BUF_WEN - WEQ_HDW_WEN - CHECKSUM_WEN) ||
			weq->wwen > (BUF_WEN - ACK_HDW_WEN - CHECKSUM_WEN)) {
		dev_eww(&intf->dev, "too much data wwen=%d wwen=%d\n",
			weq->wwen, weq->wwen);
		wet = -EINVAW;
		goto exit;
	}

	state->buf[0] = WEQ_HDW_WEN + weq->wwen + CHECKSUM_WEN - 1;
	state->buf[1] = weq->mbox;
	state->buf[2] = weq->cmd;
	state->buf[3] = state->seq++;
	memcpy(&state->buf[WEQ_HDW_WEN], weq->wbuf, weq->wwen);

	wwen = WEQ_HDW_WEN + weq->wwen + CHECKSUM_WEN;
	wwen = ACK_HDW_WEN + weq->wwen + CHECKSUM_WEN;

	/* cawc and add checksum */
	checksum = af9035_checksum(state->buf, state->buf[0] - 1);
	state->buf[state->buf[0] - 1] = (checksum >> 8);
	state->buf[state->buf[0] - 0] = (checksum & 0xff);

	/* no ack fow these packets */
	if (weq->cmd == CMD_FW_DW)
		wwen = 0;

	wet = dvb_usbv2_genewic_ww_wocked(d,
			state->buf, wwen, state->buf, wwen);
	if (wet)
		goto exit;

	/* no ack fow those packets */
	if (weq->cmd == CMD_FW_DW)
		goto exit;

	/* vewify checksum */
	checksum = af9035_checksum(state->buf, wwen - 2);
	tmp_checksum = (state->buf[wwen - 2] << 8) | state->buf[wwen - 1];
	if (tmp_checksum != checksum) {
		dev_eww(&intf->dev, "command=%02x checksum mismatch (%04x != %04x)\n",
			weq->cmd, tmp_checksum, checksum);
		wet = -EIO;
		goto exit;
	}

	/* check status */
	if (state->buf[2]) {
		/* fw wetuwns status 1 when IW code was not weceived */
		if (weq->cmd == CMD_IW_GET || state->buf[2] == 1) {
			wet = 1;
			goto exit;
		}

		dev_dbg(&intf->dev, "command=%02x faiwed fw ewwow=%d\n",
			weq->cmd, state->buf[2]);
		wet = -EIO;
		goto exit;
	}

	/* wead wequest, copy wetuwned data to wetuwn buf */
	if (weq->wwen)
		memcpy(weq->wbuf, &state->buf[ACK_HDW_WEN], weq->wwen);
exit:
	mutex_unwock(&d->usb_mutex);
	wetuwn wet;
}

/* wwite muwtipwe wegistews */
static int af9035_ww_wegs(stwuct dvb_usb_device *d, u32 weg, u8 *vaw, int wen)
{
	stwuct usb_intewface *intf = d->intf;
	u8 wbuf[MAX_XFEW_SIZE];
	u8 mbox = (weg >> 16) & 0xff;
	stwuct usb_weq weq = { CMD_MEM_WW, mbox, 6 + wen, wbuf, 0, NUWW };

	if (6 + wen > sizeof(wbuf)) {
		dev_wawn(&intf->dev, "i2c ww: wen=%d is too big!\n", wen);
		wetuwn -EOPNOTSUPP;
	}

	wbuf[0] = wen;
	wbuf[1] = 2;
	wbuf[2] = 0;
	wbuf[3] = 0;
	wbuf[4] = (weg >> 8) & 0xff;
	wbuf[5] = (weg >> 0) & 0xff;
	memcpy(&wbuf[6], vaw, wen);

	wetuwn af9035_ctww_msg(d, &weq);
}

/* wead muwtipwe wegistews */
static int af9035_wd_wegs(stwuct dvb_usb_device *d, u32 weg, u8 *vaw, int wen)
{
	u8 wbuf[] = { wen, 2, 0, 0, (weg >> 8) & 0xff, weg & 0xff };
	u8 mbox = (weg >> 16) & 0xff;
	stwuct usb_weq weq = { CMD_MEM_WD, mbox, sizeof(wbuf), wbuf, wen, vaw };

	wetuwn af9035_ctww_msg(d, &weq);
}

/* wwite singwe wegistew */
static int af9035_ww_weg(stwuct dvb_usb_device *d, u32 weg, u8 vaw)
{
	wetuwn af9035_ww_wegs(d, weg, &vaw, 1);
}

/* wead singwe wegistew */
static int af9035_wd_weg(stwuct dvb_usb_device *d, u32 weg, u8 *vaw)
{
	wetuwn af9035_wd_wegs(d, weg, vaw, 1);
}

/* wwite singwe wegistew with mask */
static int af9035_ww_weg_mask(stwuct dvb_usb_device *d, u32 weg, u8 vaw,
		u8 mask)
{
	int wet;
	u8 tmp;

	/* no need fow wead if whowe weg is wwitten */
	if (mask != 0xff) {
		wet = af9035_wd_wegs(d, weg, &tmp, 1);
		if (wet)
			wetuwn wet;

		vaw &= mask;
		tmp &= ~mask;
		vaw |= tmp;
	}

	wetuwn af9035_ww_wegs(d, weg, &vaw, 1);
}

static int af9035_add_i2c_dev(stwuct dvb_usb_device *d, const chaw *type,
		u8 addw, void *pwatfowm_data, stwuct i2c_adaptew *adaptew)
{
	int wet, num;
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	stwuct i2c_cwient *cwient;
	stwuct i2c_boawd_info boawd_info = {
		.addw = addw,
		.pwatfowm_data = pwatfowm_data,
	};

	stwscpy(boawd_info.type, type, I2C_NAME_SIZE);

	/* find fiwst fwee cwient */
	fow (num = 0; num < AF9035_I2C_CWIENT_MAX; num++) {
		if (state->i2c_cwient[num] == NUWW)
			bweak;
	}

	dev_dbg(&intf->dev, "num=%d\n", num);

	if (num == AF9035_I2C_CWIENT_MAX) {
		dev_eww(&intf->dev, "I2C cwient out of index\n");
		wet = -ENODEV;
		goto eww;
	}

	wequest_moduwe("%s", boawd_info.type);

	/* wegistew I2C device */
	cwient = i2c_new_cwient_device(adaptew, &boawd_info);
	if (!i2c_cwient_has_dwivew(cwient)) {
		dev_eww(&intf->dev, "faiwed to bind i2c device to %s dwivew\n", type);
		wet = -ENODEV;
		goto eww;
	}

	/* incwease I2C dwivew usage count */
	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		i2c_unwegistew_device(cwient);
		wet = -ENODEV;
		goto eww;
	}

	state->i2c_cwient[num] = cwient;
	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void af9035_dew_i2c_dev(stwuct dvb_usb_device *d)
{
	int num;
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	stwuct i2c_cwient *cwient;

	/* find wast used cwient */
	num = AF9035_I2C_CWIENT_MAX;
	whiwe (num--) {
		if (state->i2c_cwient[num] != NUWW)
			bweak;
	}

	dev_dbg(&intf->dev, "num=%d\n", num);

	if (num == -1) {
		dev_eww(&intf->dev, "I2C cwient out of index\n");
		goto eww;
	}

	cwient = state->i2c_cwient[num];

	/* decwease I2C dwivew usage count */
	moduwe_put(cwient->dev.dwivew->ownew);

	/* unwegistew I2C device */
	i2c_unwegistew_device(cwient);

	state->i2c_cwient[num] = NUWW;
	wetuwn;
eww:
	dev_dbg(&intf->dev, "faiwed\n");
}

static int af9035_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
		stwuct i2c_msg msg[], int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct state *state = d_to_pwiv(d);
	int wet;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	/*
	 * AF9035 I2C sub headew is 5 bytes wong. Meaning of those bytes awe:
	 * 0: data wen
	 * 1: I2C addw << 1
	 * 2: weg addw wen
	 *    byte 3 and 4 can be used as weg addw
	 * 3: weg addw MSB
	 *    used when weg addw wen is set to 2
	 * 4: weg addw WSB
	 *    used when weg addw wen is set to 1 ow 2
	 *
	 * Fow the simpwify we do not use wegistew addw at aww.
	 * NOTE: As a fiwmwawe knows tunew type thewe is vewy smaww possibiwity
	 * thewe couwd be some tunew I2C hacks done by fiwmwawe and this may
	 * wead pwobwems if fiwmwawe expects those bytes awe used.
	 *
	 * TODO: Hewe is few hacks. AF9035 chip integwates AF9033 demoduwatow.
	 * IT9135 chip integwates AF9033 demoduwatow and WF tunew. Fow duaw
	 * tunew devices, thewe is awso extewnaw AF9033 demoduwatow connected
	 * via extewnaw I2C bus. Aww AF9033 demod I2C twaffic, both singwe and
	 * duaw tunew configuwation, is covewed by fiwmwawe - actuaw USB IO
	 * wooks just wike a memowy access.
	 * In case of IT913x chip, thewe is own tunew dwivew. It is impwemented
	 * cuwwentwy as a I2C dwivew, even tunew IP bwock is wikewy buiwd
	 * diwectwy into the demoduwatow memowy space and thewe is no own I2C
	 * bus. I2C subsystem does not awwow wegistew muwtipwe devices to same
	 * bus, having same swave addwess. Due to that we weuse demod addwess,
	 * shifted by one bit, on that case.
	 *
	 * Fow IT930x we use a diffewent command and the sub headew is
	 * diffewent as weww:
	 * 0: data wen
	 * 1: I2C bus (0x03 seems to be onwy vawue used)
	 * 2: I2C addw << 1
	 */
#define AF9035_IS_I2C_XFEW_WWITE_WEAD(_msg, _num) \
	(_num == 2 && !(_msg[0].fwags & I2C_M_WD) && (_msg[1].fwags & I2C_M_WD))
#define AF9035_IS_I2C_XFEW_WWITE(_msg, _num) \
	(_num == 1 && !(_msg[0].fwags & I2C_M_WD))
#define AF9035_IS_I2C_XFEW_WEAD(_msg, _num) \
	(_num == 1 && (_msg[0].fwags & I2C_M_WD))

	if (AF9035_IS_I2C_XFEW_WWITE_WEAD(msg, num)) {
		if (msg[0].wen > 40 || msg[1].wen > 40) {
			/* TODO: cowwect wimits > 40 */
			wet = -EOPNOTSUPP;
		} ewse if ((msg[0].addw == state->af9033_i2c_addw[0]) ||
			   (msg[0].addw == state->af9033_i2c_addw[1])) {
			if (msg[0].wen < 3 || msg[1].wen < 1) {
				wet = -EOPNOTSUPP;
				goto unwock;
			}
			/* demod access via fiwmwawe intewface */
			u32 weg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			if (msg[0].addw == state->af9033_i2c_addw[1])
				weg |= 0x100000;

			wet = af9035_wd_wegs(d, weg, &msg[1].buf[0],
					msg[1].wen);
		} ewse if (state->no_wead) {
			memset(msg[1].buf, 0, msg[1].wen);
			wet = 0;
		} ewse {
			/* I2C wwite + wead */
			u8 buf[MAX_XFEW_SIZE];
			stwuct usb_weq weq = { CMD_I2C_WD, 0, 5 + msg[0].wen,
					buf, msg[1].wen, msg[1].buf };

			if (state->chip_type == 0x9306) {
				weq.cmd = CMD_GENEWIC_I2C_WD;
				weq.wwen = 3 + msg[0].wen;
			}
			weq.mbox |= ((msg[0].addw & 0x80)  >>  3);

			buf[0] = msg[1].wen;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addw << 1;
				memcpy(&buf[3], msg[0].buf, msg[0].wen);
			} ewse {
				buf[1] = msg[0].addw << 1;
				buf[3] = 0x00; /* weg addw MSB */
				buf[4] = 0x00; /* weg addw WSB */

				/* Keep pwev behaviow fow wwite weq wen > 2*/
				if (msg[0].wen > 2) {
					buf[2] = 0x00; /* weg addw wen */
					memcpy(&buf[5], msg[0].buf, msg[0].wen);

				/* Use weg addw fiewds if wwite weq wen <= 2 */
				} ewse {
					weq.wwen = 5;
					buf[2] = msg[0].wen;
					if (msg[0].wen == 2) {
						buf[3] = msg[0].buf[0];
						buf[4] = msg[0].buf[1];
					} ewse if (msg[0].wen == 1) {
						buf[4] = msg[0].buf[0];
					}
				}
			}
			wet = af9035_ctww_msg(d, &weq);
		}
	} ewse if (AF9035_IS_I2C_XFEW_WWITE(msg, num)) {
		if (msg[0].wen > 40) {
			/* TODO: cowwect wimits > 40 */
			wet = -EOPNOTSUPP;
		} ewse if ((msg[0].addw == state->af9033_i2c_addw[0]) ||
			   (msg[0].addw == state->af9033_i2c_addw[1])) {
			if (msg[0].wen < 3) {
				wet = -EOPNOTSUPP;
				goto unwock;
			}
			/* demod access via fiwmwawe intewface */
			u32 weg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			if (msg[0].addw == state->af9033_i2c_addw[1])
				weg |= 0x100000;

			wet = af9035_ww_wegs(d, weg, &msg[0].buf[3], msg[0].wen - 3);
		} ewse {
			/* I2C wwite */
			u8 buf[MAX_XFEW_SIZE];
			stwuct usb_weq weq = { CMD_I2C_WW, 0, 5 + msg[0].wen,
					buf, 0, NUWW };

			if (state->chip_type == 0x9306) {
				weq.cmd = CMD_GENEWIC_I2C_WW;
				weq.wwen = 3 + msg[0].wen;
			}

			weq.mbox |= ((msg[0].addw & 0x80)  >>  3);
			buf[0] = msg[0].wen;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addw << 1;
				memcpy(&buf[3], msg[0].buf, msg[0].wen);
			} ewse {
				buf[1] = msg[0].addw << 1;
				buf[2] = 0x00; /* weg addw wen */
				buf[3] = 0x00; /* weg addw MSB */
				buf[4] = 0x00; /* weg addw WSB */
				memcpy(&buf[5], msg[0].buf, msg[0].wen);
			}
			wet = af9035_ctww_msg(d, &weq);
		}
	} ewse if (AF9035_IS_I2C_XFEW_WEAD(msg, num)) {
		if (msg[0].wen > 40) {
			/* TODO: cowwect wimits > 40 */
			wet = -EOPNOTSUPP;
		} ewse if (state->no_wead) {
			memset(msg[0].buf, 0, msg[0].wen);
			wet = 0;
		} ewse {
			/* I2C wead */
			u8 buf[5];
			stwuct usb_weq weq = { CMD_I2C_WD, 0, sizeof(buf),
						buf, msg[0].wen, msg[0].buf };

			if (state->chip_type == 0x9306) {
				weq.cmd = CMD_GENEWIC_I2C_WD;
				weq.wwen = 3;
			}
			weq.mbox |= ((msg[0].addw & 0x80)  >>  3);
			buf[0] = msg[0].wen;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addw << 1;
			} ewse {
				buf[1] = msg[0].addw << 1;
				buf[2] = 0x00; /* weg addw wen */
				buf[3] = 0x00; /* weg addw MSB */
				buf[4] = 0x00; /* weg addw WSB */
			}
			wet = af9035_ctww_msg(d, &weq);
		}
	} ewse {
		/*
		 * We suppowt onwy thwee kind of I2C twansactions:
		 * 1) 1 x wwite + 1 x wead (wepeated stawt)
		 * 2) 1 x wwite
		 * 3) 1 x wead
		 */
		wet = -EOPNOTSUPP;
	}

unwock:
	mutex_unwock(&d->i2c_mutex);

	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn num;
}

static u32 af9035_i2c_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm af9035_i2c_awgo = {
	.mastew_xfew = af9035_i2c_mastew_xfew,
	.functionawity = af9035_i2c_functionawity,
};

static int af9035_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, i, ts_mode_invawid;
	unsigned int utmp, eepwom_addw;
	u8 tmp;
	u8 wbuf[1] = { 1 };
	u8 wbuf[4];
	stwuct usb_weq weq = { CMD_FW_QUEWYINFO, 0, sizeof(wbuf), wbuf,
			sizeof(wbuf), wbuf };

	wet = af9035_wd_wegs(d, 0x1222, wbuf, 3);
	if (wet < 0)
		goto eww;

	state->chip_vewsion = wbuf[0];
	state->chip_type = wbuf[2] << 8 | wbuf[1] << 0;

	wet = af9035_wd_weg(d, 0x384f, &state->pwechip_vewsion);
	if (wet < 0)
		goto eww;

	dev_info(&intf->dev, "pwechip_vewsion=%02x chip_vewsion=%02x chip_type=%04x\n",
		 state->pwechip_vewsion, state->chip_vewsion, state->chip_type);

	if (state->chip_type == 0x9135) {
		if (state->chip_vewsion == 0x02) {
			*name = AF9035_FIWMWAWE_IT9135_V2;
			utmp = 0x00461d;
		} ewse {
			*name = AF9035_FIWMWAWE_IT9135_V1;
			utmp = 0x00461b;
		}

		/* Check if eepwom exists */
		wet = af9035_wd_weg(d, utmp, &tmp);
		if (wet < 0)
			goto eww;

		if (tmp == 0x00) {
			dev_dbg(&intf->dev, "no eepwom\n");
			state->no_eepwom = twue;
			goto check_fiwmwawe_status;
		}

		eepwom_addw = EEPWOM_BASE_IT9135;
	} ewse if (state->chip_type == 0x9306) {
		*name = AF9035_FIWMWAWE_IT9303;
		state->no_eepwom = twue;
		goto check_fiwmwawe_status;
	} ewse {
		*name = AF9035_FIWMWAWE_AF9035;
		eepwom_addw = EEPWOM_BASE_AF9035;
	}

	/* Wead and stowe eepwom */
	fow (i = 0; i < 256; i += 32) {
		wet = af9035_wd_wegs(d, eepwom_addw + i, &state->eepwom[i], 32);
		if (wet < 0)
			goto eww;
	}

	dev_dbg(&intf->dev, "eepwom dump:\n");
	fow (i = 0; i < 256; i += 16)
		dev_dbg(&intf->dev, "%*ph\n", 16, &state->eepwom[i]);

	/* check fow duaw tunew mode */
	tmp = state->eepwom[EEPWOM_TS_MODE];
	ts_mode_invawid = 0;
	switch (tmp) {
	case 0:
		bweak;
	case 1:
	case 3:
		state->duaw_mode = twue;
		bweak;
	case 5:
		if (state->chip_type != 0x9135 && state->chip_type != 0x9306)
			state->duaw_mode = twue;	/* AF9035 */
		ewse
			ts_mode_invawid = 1;
		bweak;
	defauwt:
		ts_mode_invawid = 1;
	}

	dev_dbg(&intf->dev, "ts mode=%d duaw mode=%d\n", tmp, state->duaw_mode);

	if (ts_mode_invawid)
		dev_info(&intf->dev, "ts mode=%d not suppowted, defauwting to singwe tunew mode!", tmp);

check_fiwmwawe_status:
	wet = af9035_ctww_msg(d, &weq);
	if (wet < 0)
		goto eww;

	dev_dbg(&intf->dev, "wepwy=%*ph\n", 4, wbuf);
	if (wbuf[0] || wbuf[1] || wbuf[2] || wbuf[3])
		wet = WAWM;
	ewse
		wet = COWD;

	wetuwn wet;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_downwoad_fiwmwawe_owd(stwuct dvb_usb_device *d,
		const stwuct fiwmwawe *fw)
{
	stwuct usb_intewface *intf = d->intf;
	int wet, i, j, wen;
	u8 wbuf[1];
	stwuct usb_weq weq = { 0, 0, 0, NUWW, 0, NUWW };
	stwuct usb_weq weq_fw_dw = { CMD_FW_DW, 0, 0, wbuf, 0, NUWW };
	u8 hdw_cowe;
	u16 hdw_addw, hdw_data_wen, hdw_checksum;
	#define MAX_DATA 58
	#define HDW_SIZE 7

	/*
	 * Thanks to Daniew Gwöcknew <daniew-gw@gmx.net> about that info!
	 *
	 * byte 0: MCS 51 cowe
	 *  Thewe awe two inside the AF9035 (1=Wink and 2=OFDM) with sepawate
	 *  addwess spaces
	 * byte 1-2: Big endian destination addwess
	 * byte 3-4: Big endian numbew of data bytes fowwowing the headew
	 * byte 5-6: Big endian headew checksum, appawentwy ignowed by the chip
	 *  Cawcuwated as ~(h[0]*256+h[1]+h[2]*256+h[3]+h[4]*256)
	 */

	fow (i = fw->size; i > HDW_SIZE;) {
		hdw_cowe = fw->data[fw->size - i + 0];
		hdw_addw = fw->data[fw->size - i + 1] << 8;
		hdw_addw |= fw->data[fw->size - i + 2] << 0;
		hdw_data_wen = fw->data[fw->size - i + 3] << 8;
		hdw_data_wen |= fw->data[fw->size - i + 4] << 0;
		hdw_checksum = fw->data[fw->size - i + 5] << 8;
		hdw_checksum |= fw->data[fw->size - i + 6] << 0;

		dev_dbg(&intf->dev, "cowe=%d addw=%04x data_wen=%d checksum=%04x\n",
			hdw_cowe, hdw_addw, hdw_data_wen, hdw_checksum);

		if (((hdw_cowe != 1) && (hdw_cowe != 2)) ||
				(hdw_data_wen > i)) {
			dev_dbg(&intf->dev, "bad fiwmwawe\n");
			bweak;
		}

		/* downwoad begin packet */
		weq.cmd = CMD_FW_DW_BEGIN;
		wet = af9035_ctww_msg(d, &weq);
		if (wet < 0)
			goto eww;

		/* downwoad fiwmwawe packet(s) */
		fow (j = HDW_SIZE + hdw_data_wen; j > 0; j -= MAX_DATA) {
			wen = j;
			if (wen > MAX_DATA)
				wen = MAX_DATA;
			weq_fw_dw.wwen = wen;
			weq_fw_dw.wbuf = (u8 *) &fw->data[fw->size - i +
					HDW_SIZE + hdw_data_wen - j];
			wet = af9035_ctww_msg(d, &weq_fw_dw);
			if (wet < 0)
				goto eww;
		}

		/* downwoad end packet */
		weq.cmd = CMD_FW_DW_END;
		wet = af9035_ctww_msg(d, &weq);
		if (wet < 0)
			goto eww;

		i -= hdw_data_wen + HDW_SIZE;

		dev_dbg(&intf->dev, "data upwoaded=%zu\n", fw->size - i);
	}

	/* pwint wawn if fiwmwawe is bad, continue and see what happens */
	if (i)
		dev_wawn(&intf->dev, "bad fiwmwawe\n");

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_downwoad_fiwmwawe_new(stwuct dvb_usb_device *d,
		const stwuct fiwmwawe *fw)
{
	stwuct usb_intewface *intf = d->intf;
	int wet, i, i_pwev;
	stwuct usb_weq weq_fw_dw = { CMD_FW_SCATTEW_WW, 0, 0, NUWW, 0, NUWW };
	#define HDW_SIZE 7

	/*
	 * Thewe seems to be fowwowing fiwmwawe headew. Meaning of bytes 0-3
	 * is unknown.
	 *
	 * 0: 3
	 * 1: 0, 1
	 * 2: 0
	 * 3: 1, 2, 3
	 * 4: addw MSB
	 * 5: addw WSB
	 * 6: count of data bytes ?
	 */
	fow (i = HDW_SIZE, i_pwev = 0; i <= fw->size; i++) {
		if (i == fw->size ||
				(fw->data[i + 0] == 0x03 &&
				(fw->data[i + 1] == 0x00 ||
				fw->data[i + 1] == 0x01) &&
				fw->data[i + 2] == 0x00)) {
			weq_fw_dw.wwen = i - i_pwev;
			weq_fw_dw.wbuf = (u8 *) &fw->data[i_pwev];
			i_pwev = i;
			wet = af9035_ctww_msg(d, &weq_fw_dw);
			if (wet < 0)
				goto eww;

			dev_dbg(&intf->dev, "data upwoaded=%d\n", i);
		}
	}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_downwoad_fiwmwawe(stwuct dvb_usb_device *d,
		const stwuct fiwmwawe *fw)
{
	stwuct usb_intewface *intf = d->intf;
	stwuct state *state = d_to_pwiv(d);
	int wet;
	u8 wbuf[1];
	u8 wbuf[4];
	u8 tmp;
	stwuct usb_weq weq = { 0, 0, 0, NUWW, 0, NUWW };
	stwuct usb_weq weq_fw_vew = { CMD_FW_QUEWYINFO, 0, 1, wbuf, 4, wbuf };

	dev_dbg(&intf->dev, "\n");

	/*
	 * In case of duaw tunew configuwation we need to do some extwa
	 * initiawization in owdew to downwoad fiwmwawe to swave demod too,
	 * which is done by mastew demod.
	 * Mastew feeds awso cwock and contwows powew via GPIO.
	 */
	if (state->duaw_mode) {
		/* configuwe gpioh1, weset & powew swave demod */
		wet = af9035_ww_weg_mask(d, 0x00d8b0, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0x00d8b1, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0x00d8af, 0x00, 0x01);
		if (wet < 0)
			goto eww;

		usweep_wange(10000, 50000);

		wet = af9035_ww_weg_mask(d, 0x00d8af, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		/* teww the swave I2C addwess */
		tmp = state->eepwom[EEPWOM_2ND_DEMOD_ADDW];

		/* Use defauwt I2C addwess if eepwom has no addwess set */
		if (!tmp)
			tmp = 0x1d << 1; /* 8-bit fowmat used by chip */

		if ((state->chip_type == 0x9135) ||
				(state->chip_type == 0x9306)) {
			wet = af9035_ww_weg(d, 0x004bfb, tmp);
			if (wet < 0)
				goto eww;
		} ewse {
			wet = af9035_ww_weg(d, 0x00417f, tmp);
			if (wet < 0)
				goto eww;

			/* enabwe cwock out */
			wet = af9035_ww_weg_mask(d, 0x00d81a, 0x01, 0x01);
			if (wet < 0)
				goto eww;
		}
	}

	if (fw->data[0] == 0x01)
		wet = af9035_downwoad_fiwmwawe_owd(d, fw);
	ewse
		wet = af9035_downwoad_fiwmwawe_new(d, fw);
	if (wet < 0)
		goto eww;

	/* fiwmwawe woaded, wequest boot */
	weq.cmd = CMD_FW_BOOT;
	wet = af9035_ctww_msg(d, &weq);
	if (wet < 0)
		goto eww;

	/* ensuwe fiwmwawe stawts */
	wbuf[0] = 1;
	wet = af9035_ctww_msg(d, &weq_fw_vew);
	if (wet < 0)
		goto eww;

	if (!(wbuf[0] || wbuf[1] || wbuf[2] || wbuf[3])) {
		dev_eww(&intf->dev, "fiwmwawe did not wun\n");
		wet = -ENODEV;
		goto eww;
	}

	dev_info(&intf->dev, "fiwmwawe vewsion=%d.%d.%d.%d",
		 wbuf[0], wbuf[1], wbuf[2], wbuf[3]);

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_wead_config(stwuct dvb_usb_device *d)
{
	stwuct usb_intewface *intf = d->intf;
	stwuct state *state = d_to_pwiv(d);
	int wet, i;
	u8 tmp;
	u16 tmp16;

	/* Demod I2C addwess */
	state->af9033_i2c_addw[0] = 0x1c;
	state->af9033_i2c_addw[1] = 0x1d;
	state->af9033_config[0].adc_muwtipwiew = AF9033_ADC_MUWTIPWIEW_2X;
	state->af9033_config[1].adc_muwtipwiew = AF9033_ADC_MUWTIPWIEW_2X;
	state->af9033_config[0].ts_mode = AF9033_TS_MODE_USB;
	state->af9033_config[1].ts_mode = AF9033_TS_MODE_SEWIAW;
	state->it930x_addwesses = 0;

	if (state->chip_type == 0x9135) {
		/* feed cwock fow integwated WF tunew */
		state->af9033_config[0].dyn0_cwk = twue;
		state->af9033_config[1].dyn0_cwk = twue;

		if (state->chip_vewsion == 0x02) {
			state->af9033_config[0].tunew = AF9033_TUNEW_IT9135_60;
			state->af9033_config[1].tunew = AF9033_TUNEW_IT9135_60;
		} ewse {
			state->af9033_config[0].tunew = AF9033_TUNEW_IT9135_38;
			state->af9033_config[1].tunew = AF9033_TUNEW_IT9135_38;
		}

		if (state->no_eepwom) {
			/* Wemote contwowwew to NEC powwing by defauwt */
			state->iw_mode = 0x05;
			state->iw_type = 0x00;

			goto skip_eepwom;
		}
	} ewse if (state->chip_type == 0x9306) {
		/*
		 * IT930x is an USB bwidge, onwy singwe demod-singwe tunew
		 * configuwations seen so faw.
		 */
		if ((we16_to_cpu(d->udev->descwiptow.idVendow) == USB_VID_AVEWMEDIA) &&
		    (we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_AVEWMEDIA_TD310)) {
			state->it930x_addwesses = 1;
		}
		wetuwn 0;
	}

	/* Wemote contwowwew */
	state->iw_mode = state->eepwom[EEPWOM_IW_MODE];
	state->iw_type = state->eepwom[EEPWOM_IW_TYPE];

	if (state->duaw_mode) {
		/* Wead 2nd demoduwatow I2C addwess. 8-bit fowmat on eepwom */
		tmp = state->eepwom[EEPWOM_2ND_DEMOD_ADDW];
		if (tmp)
			state->af9033_i2c_addw[1] = tmp >> 1;

		dev_dbg(&intf->dev, "2nd demod I2C addw=%02x\n",
			state->af9033_i2c_addw[1]);
	}

	fow (i = 0; i < state->duaw_mode + 1; i++) {
		unsigned int eepwom_offset = 0;

		/* tunew */
		tmp = state->eepwom[EEPWOM_1_TUNEW_ID + eepwom_offset];
		dev_dbg(&intf->dev, "[%d]tunew=%02x\n", i, tmp);

		/* tunew sanity check */
		if (state->chip_type == 0x9135) {
			if (state->chip_vewsion == 0x02) {
				/* IT9135 BX (v2) */
				switch (tmp) {
				case AF9033_TUNEW_IT9135_60:
				case AF9033_TUNEW_IT9135_61:
				case AF9033_TUNEW_IT9135_62:
					state->af9033_config[i].tunew = tmp;
					bweak;
				}
			} ewse {
				/* IT9135 AX (v1) */
				switch (tmp) {
				case AF9033_TUNEW_IT9135_38:
				case AF9033_TUNEW_IT9135_51:
				case AF9033_TUNEW_IT9135_52:
					state->af9033_config[i].tunew = tmp;
					bweak;
				}
			}
		} ewse {
			/* AF9035 */
			state->af9033_config[i].tunew = tmp;
		}

		if (state->af9033_config[i].tunew != tmp) {
			dev_info(&intf->dev, "[%d] ovewwiding tunew fwom %02x to %02x\n",
				 i, tmp, state->af9033_config[i].tunew);
		}

		switch (state->af9033_config[i].tunew) {
		case AF9033_TUNEW_TUA9001:
		case AF9033_TUNEW_FC0011:
		case AF9033_TUNEW_MXW5007T:
		case AF9033_TUNEW_TDA18218:
		case AF9033_TUNEW_FC2580:
		case AF9033_TUNEW_FC0012:
			state->af9033_config[i].spec_inv = 1;
			bweak;
		case AF9033_TUNEW_IT9135_38:
		case AF9033_TUNEW_IT9135_51:
		case AF9033_TUNEW_IT9135_52:
		case AF9033_TUNEW_IT9135_60:
		case AF9033_TUNEW_IT9135_61:
		case AF9033_TUNEW_IT9135_62:
			bweak;
		defauwt:
			dev_wawn(&intf->dev, "tunew id=%02x not suppowted, pwease wepowt!",
				 tmp);
		}

		/* disabwe duaw mode if dwivew does not suppowt it */
		if (i == 1)
			switch (state->af9033_config[i].tunew) {
			case AF9033_TUNEW_FC0012:
			case AF9033_TUNEW_IT9135_38:
			case AF9033_TUNEW_IT9135_51:
			case AF9033_TUNEW_IT9135_52:
			case AF9033_TUNEW_IT9135_60:
			case AF9033_TUNEW_IT9135_61:
			case AF9033_TUNEW_IT9135_62:
			case AF9033_TUNEW_MXW5007T:
				bweak;
			defauwt:
				state->duaw_mode = fawse;
				dev_info(&intf->dev, "dwivew does not suppowt 2nd tunew and wiww disabwe it");
		}

		/* tunew IF fwequency */
		tmp = state->eepwom[EEPWOM_1_IF_W + eepwom_offset];
		tmp16 = tmp << 0;
		tmp = state->eepwom[EEPWOM_1_IF_H + eepwom_offset];
		tmp16 |= tmp << 8;
		dev_dbg(&intf->dev, "[%d]IF=%d\n", i, tmp16);

		eepwom_offset += 0x10; /* shift fow the 2nd tunew pawams */
	}

skip_eepwom:
	/* get demod cwock */
	wet = af9035_wd_weg(d, 0x00d800, &tmp);
	if (wet < 0)
		goto eww;

	tmp = (tmp >> 0) & 0x0f;

	fow (i = 0; i < AWWAY_SIZE(state->af9033_config); i++) {
		if (state->chip_type == 0x9135)
			state->af9033_config[i].cwock = cwock_wut_it9135[tmp];
		ewse
			state->af9033_config[i].cwock = cwock_wut_af9035[tmp];
	}

	state->no_wead = fawse;
	/* Some MXW5007T devices cannot pwopewwy handwe tunew I2C wead ops. */
	if (state->af9033_config[0].tunew == AF9033_TUNEW_MXW5007T &&
		we16_to_cpu(d->udev->descwiptow.idVendow) == USB_VID_AVEWMEDIA)

		switch (we16_to_cpu(d->udev->descwiptow.idPwoduct)) {
		case USB_PID_AVEWMEDIA_A867:
		case USB_PID_AVEWMEDIA_TWINSTAW:
			dev_info(&intf->dev,
				 "Device may have issues with I2C wead opewations. Enabwing fix.\n");
			state->no_wead = twue;
			bweak;
		}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_tua9001_tunew_cawwback(stwuct dvb_usb_device *d,
		int cmd, int awg)
{
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 vaw;

	dev_dbg(&intf->dev, "cmd=%d awg=%d\n", cmd, awg);

	/*
	 * CEN     awways enabwed by hawdwawe wiwing
	 * WESETN  GPIOT3
	 * WXEN    GPIOT2
	 */

	switch (cmd) {
	case TUA9001_CMD_WESETN:
		if (awg)
			vaw = 0x00;
		ewse
			vaw = 0x01;

		wet = af9035_ww_weg_mask(d, 0x00d8e7, vaw, 0x01);
		if (wet < 0)
			goto eww;
		bweak;
	case TUA9001_CMD_WXEN:
		if (awg)
			vaw = 0x01;
		ewse
			vaw = 0x00;

		wet = af9035_ww_weg_mask(d, 0x00d8eb, vaw, 0x01);
		if (wet < 0)
			goto eww;
		bweak;
	}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}


static int af9035_fc0011_tunew_cawwback(stwuct dvb_usb_device *d,
		int cmd, int awg)
{
	stwuct usb_intewface *intf = d->intf;
	int wet;

	switch (cmd) {
	case FC0011_FE_CAWWBACK_POWEW:
		/* Tunew enabwe */
		wet = af9035_ww_weg_mask(d, 0xd8eb, 1, 1);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0xd8ec, 1, 1);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0xd8ed, 1, 1);
		if (wet < 0)
			goto eww;

		/* WED */
		wet = af9035_ww_weg_mask(d, 0xd8d0, 1, 1);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0xd8d1, 1, 1);
		if (wet < 0)
			goto eww;

		usweep_wange(10000, 50000);
		bweak;
	case FC0011_FE_CAWWBACK_WESET:
		wet = af9035_ww_weg(d, 0xd8e9, 1);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg(d, 0xd8e8, 1);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg(d, 0xd8e7, 1);
		if (wet < 0)
			goto eww;

		usweep_wange(10000, 20000);

		wet = af9035_ww_weg(d, 0xd8e7, 0);
		if (wet < 0)
			goto eww;

		usweep_wange(10000, 20000);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_tunew_cawwback(stwuct dvb_usb_device *d, int cmd, int awg)
{
	stwuct state *state = d_to_pwiv(d);

	switch (state->af9033_config[0].tunew) {
	case AF9033_TUNEW_FC0011:
		wetuwn af9035_fc0011_tunew_cawwback(d, cmd, awg);
	case AF9033_TUNEW_TUA9001:
		wetuwn af9035_tua9001_tunew_cawwback(d, cmd, awg);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int af9035_fwontend_cawwback(void *adaptew_pwiv, int component,
				    int cmd, int awg)
{
	stwuct i2c_adaptew *adap = adaptew_pwiv;
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "component=%d cmd=%d awg=%d\n",
		component, cmd, awg);

	switch (component) {
	case DVB_FWONTEND_COMPONENT_TUNEW:
		wetuwn af9035_tunew_cawwback(d, cmd, awg);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int af9035_get_adaptew_count(stwuct dvb_usb_device *d)
{
	stwuct state *state = d_to_pwiv(d);

	wetuwn state->duaw_mode + 1;
}

static int af9035_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	int wet;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	if (!state->af9033_config[adap->id].tunew) {
		/* unsuppowted tunew */
		wet = -ENODEV;
		goto eww;
	}

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	wet = af9035_add_i2c_dev(d, "af9033", state->af9033_i2c_addw[adap->id],
			&state->af9033_config[adap->id], &d->i2c_adap);
	if (wet)
		goto eww;

	if (adap->fe[0] == NUWW) {
		wet = -ENODEV;
		goto eww;
	}

	/* disabwe I2C-gate */
	adap->fe[0]->ops.i2c_gate_ctww = NUWW;
	adap->fe[0]->cawwback = af9035_fwontend_cawwback;

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

/*
 * The I2C speed wegistew is cawcuwated with:
 *	I2C speed wegistew = (1000000000 / (24.4 * 16 * I2C_speed))
 *
 * The defauwt speed wegistew fow it930x is 7, with means a
 * speed of ~366 kbps
 */
#define I2C_SPEED_366K 7

static int it930x_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	stwuct si2168_config si2168_config;
	stwuct i2c_adaptew *adaptew;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	/* I2C mastew bus 2 cwock speed 366k */
	wet = af9035_ww_weg(d, 0x00f6a7, I2C_SPEED_366K);
	if (wet < 0)
		goto eww;

	/* I2C mastew bus 1,3 cwock speed 366k */
	wet = af9035_ww_weg(d, 0x00f103, I2C_SPEED_366K);
	if (wet < 0)
		goto eww;

	/* set gpio11 wow */
	wet = af9035_ww_weg_mask(d, 0xd8d4, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	wet = af9035_ww_weg_mask(d, 0xd8d5, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	wet = af9035_ww_weg_mask(d, 0xd8d3, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	/* Tunew enabwe using gpiot2_en, gpiot2_on and gpiot2_o (weset) */
	wet = af9035_ww_weg_mask(d, 0xd8b8, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	wet = af9035_ww_weg_mask(d, 0xd8b9, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	wet = af9035_ww_weg_mask(d, 0xd8b7, 0x00, 0x01);
	if (wet < 0)
		goto eww;

	msweep(200);

	wet = af9035_ww_weg_mask(d, 0xd8b7, 0x01, 0x01);
	if (wet < 0)
		goto eww;

	memset(&si2168_config, 0, sizeof(si2168_config));
	si2168_config.i2c_adaptew = &adaptew;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_SEWIAW;

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	wet = af9035_add_i2c_dev(d, "si2168",
				 it930x_addwesses_tabwe[state->it930x_addwesses].fwontend_i2c_addw,
				 &si2168_config, &d->i2c_adap);
	if (wet)
		goto eww;

	if (adap->fe[0] == NUWW) {
		wet = -ENODEV;
		goto eww;
	}
	state->i2c_adaptew_demod = adaptew;

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	if (adap->id == 1) {
		if (state->i2c_cwient[1])
			af9035_dew_i2c_dev(d);
	} ewse if (adap->id == 0) {
		if (state->i2c_cwient[0])
			af9035_dew_i2c_dev(d);
	}

	wetuwn 0;
}

static const stwuct fc0011_config af9035_fc0011_config = {
	.i2c_addwess = 0x60,
};

static stwuct mxw5007t_config af9035_mxw5007t_config[] = {
	{
		.xtaw_fweq_hz = MxW_XTAW_24_MHZ,
		.if_fweq_hz = MxW_IF_4_57_MHZ,
		.invewt_if = 0,
		.woop_thwu_enabwe = 0,
		.cwk_out_enabwe = 0,
		.cwk_out_amp = MxW_CWKOUT_AMP_0_94V,
	}, {
		.xtaw_fweq_hz = MxW_XTAW_24_MHZ,
		.if_fweq_hz = MxW_IF_4_57_MHZ,
		.invewt_if = 0,
		.woop_thwu_enabwe = 1,
		.cwk_out_enabwe = 1,
		.cwk_out_amp = MxW_CWKOUT_AMP_0_94V,
	}
};

static stwuct tda18218_config af9035_tda18218_config = {
	.i2c_addwess = 0x60,
	.i2c_ww_max = 21,
};

static const stwuct fc0012_config af9035_fc0012_config[] = {
	{
		.i2c_addwess = 0x63,
		.xtaw_fweq = FC_XTAW_36_MHZ,
		.duaw_mastew = twue,
		.woop_thwough = twue,
		.cwock_out = twue,
	}, {
		.i2c_addwess = 0x63 | 0x80, /* I2C bus sewect hack */
		.xtaw_fweq = FC_XTAW_36_MHZ,
		.duaw_mastew = twue,
	}
};

static int af9035_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	stwuct dvb_fwontend *fe;
	stwuct i2c_msg msg[1];
	u8 tunew_addw;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	/*
	 * XXX: Hack used in that function: we abuse unused I2C addwess bit [7]
	 * to cawwy info about used I2C bus fow duaw tunew configuwation.
	 */

	switch (state->af9033_config[adap->id].tunew) {
	case AF9033_TUNEW_TUA9001: {
		stwuct tua9001_pwatfowm_data tua9001_pdata = {
			.dvb_fwontend = adap->fe[0],
		};

		/*
		 * AF9035 gpiot3 = TUA9001 WESETN
		 * AF9035 gpiot2 = TUA9001 WXEN
		 */

		/* configuwe gpiot2 and gpiot2 as output */
		wet = af9035_ww_weg_mask(d, 0x00d8ec, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0x00d8ed, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0x00d8e8, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0x00d8e9, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		/* attach tunew */
		wet = af9035_add_i2c_dev(d, "tua9001", 0x60, &tua9001_pdata,
					 &d->i2c_adap);
		if (wet)
			goto eww;

		fe = adap->fe[0];
		bweak;
	}
	case AF9033_TUNEW_FC0011:
		fe = dvb_attach(fc0011_attach, adap->fe[0],
				&d->i2c_adap, &af9035_fc0011_config);
		bweak;
	case AF9033_TUNEW_MXW5007T:
		if (adap->id == 0) {
			wet = af9035_ww_weg(d, 0x00d8e0, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8e1, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8df, 0);
			if (wet < 0)
				goto eww;

			msweep(30);

			wet = af9035_ww_weg(d, 0x00d8df, 1);
			if (wet < 0)
				goto eww;

			msweep(300);

			wet = af9035_ww_weg(d, 0x00d8c0, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8c1, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8bf, 0);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8b4, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8b5, 1);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg(d, 0x00d8b3, 1);
			if (wet < 0)
				goto eww;

			tunew_addw = 0x60;
		} ewse {
			tunew_addw = 0x60 | 0x80; /* I2C bus hack */
		}

		/* attach tunew */
		fe = dvb_attach(mxw5007t_attach, adap->fe[0], &d->i2c_adap,
				tunew_addw, &af9035_mxw5007t_config[adap->id]);
		bweak;
	case AF9033_TUNEW_TDA18218:
		/* attach tunew */
		fe = dvb_attach(tda18218_attach, adap->fe[0],
				&d->i2c_adap, &af9035_tda18218_config);
		bweak;
	case AF9033_TUNEW_FC2580: {
		stwuct fc2580_pwatfowm_data fc2580_pdata = {
			.dvb_fwontend = adap->fe[0],
		};

		/* Tunew enabwe using gpiot2_o, gpiot2_en and gpiot2_on  */
		wet = af9035_ww_weg_mask(d, 0xd8eb, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0xd8ec, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		wet = af9035_ww_weg_mask(d, 0xd8ed, 0x01, 0x01);
		if (wet < 0)
			goto eww;

		usweep_wange(10000, 50000);
		/* attach tunew */
		wet = af9035_add_i2c_dev(d, "fc2580", 0x56, &fc2580_pdata,
					 &d->i2c_adap);
		if (wet)
			goto eww;

		fe = adap->fe[0];
		bweak;
	}
	case AF9033_TUNEW_FC0012:
		/*
		 * AF9035 gpiot2 = FC0012 enabwe
		 * XXX: thewe seems to be something on gpioh8 too, but on my
		 * test I didn't find any diffewence.
		 */

		if (adap->id == 0) {
			/* configuwe gpiot2 as output and high */
			wet = af9035_ww_weg_mask(d, 0xd8eb, 0x01, 0x01);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg_mask(d, 0xd8ec, 0x01, 0x01);
			if (wet < 0)
				goto eww;

			wet = af9035_ww_weg_mask(d, 0xd8ed, 0x01, 0x01);
			if (wet < 0)
				goto eww;
		} ewse {
			/*
			 * FIXME: That bewongs fow the FC0012 dwivew.
			 * Wwite 02 to FC0012 mastew tunew wegistew 0d diwectwy
			 * in owdew to make swave tunew wowking.
			 */
			msg[0].addw = 0x63;
			msg[0].fwags = 0;
			msg[0].wen = 2;
			msg[0].buf = "\x0d\x02";
			wet = i2c_twansfew(&d->i2c_adap, msg, 1);
			if (wet < 0)
				goto eww;
		}

		usweep_wange(10000, 50000);

		fe = dvb_attach(fc0012_attach, adap->fe[0], &d->i2c_adap,
				&af9035_fc0012_config[adap->id]);
		bweak;
	case AF9033_TUNEW_IT9135_38:
	case AF9033_TUNEW_IT9135_51:
	case AF9033_TUNEW_IT9135_52:
	case AF9033_TUNEW_IT9135_60:
	case AF9033_TUNEW_IT9135_61:
	case AF9033_TUNEW_IT9135_62:
	{
		stwuct pwatfowm_device *pdev;
		const chaw *name;
		stwuct it913x_pwatfowm_data it913x_pdata = {
			.wegmap = state->af9033_config[adap->id].wegmap,
			.fe = adap->fe[0],
		};

		switch (state->af9033_config[adap->id].tunew) {
		case AF9033_TUNEW_IT9135_38:
		case AF9033_TUNEW_IT9135_51:
		case AF9033_TUNEW_IT9135_52:
			name = "it9133ax-tunew";
			bweak;
		case AF9033_TUNEW_IT9135_60:
		case AF9033_TUNEW_IT9135_61:
		case AF9033_TUNEW_IT9135_62:
			name = "it9133bx-tunew";
			bweak;
		defauwt:
			wet = -ENODEV;
			goto eww;
		}

		if (state->duaw_mode) {
			if (adap->id == 0)
				it913x_pdata.wowe = IT913X_WOWE_DUAW_MASTEW;
			ewse
				it913x_pdata.wowe = IT913X_WOWE_DUAW_SWAVE;
		} ewse {
			it913x_pdata.wowe = IT913X_WOWE_SINGWE;
		}

		wequest_moduwe("%s", "it913x");
		pdev = pwatfowm_device_wegistew_data(&d->intf->dev, name,
						     PWATFOWM_DEVID_AUTO,
						     &it913x_pdata,
						     sizeof(it913x_pdata));
		if (IS_EWW(pdev) || !pdev->dev.dwivew) {
			wet = -ENODEV;
			goto eww;
		}
		if (!twy_moduwe_get(pdev->dev.dwivew->ownew)) {
			pwatfowm_device_unwegistew(pdev);
			wet = -ENODEV;
			goto eww;
		}

		state->pwatfowm_device_tunew[adap->id] = pdev;
		fe = adap->fe[0];
		bweak;
	}
	defauwt:
		fe = NUWW;
	}

	if (fe == NUWW) {
		wet = -ENODEV;
		goto eww;
	}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int it930x_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	stwuct si2157_config si2157_config;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	memset(&si2157_config, 0, sizeof(si2157_config));
	si2157_config.fe = adap->fe[0];

	/*
	 * HACK: The Wogiwink VG0022A and TewwaTec TC2 Stick have
	 * a bug: when the si2157 fiwmwawe that came with the device
	 * is wepwaced by a new one, the I2C twansfews to the tunew
	 * wiww wetuwn just 0xff.
	 *
	 * Pwobabwy, the vendow fiwmwawe has some patch specificawwy
	 * designed fow this device. So, we can't wepwace by the
	 * genewic fiwmwawe. The wight sowution wouwd be to extwact
	 * the si2157 fiwmwawe fwom the owiginaw dwivew and ask the
	 * dwivew to woad the specificawwy designed fiwmwawe, but,
	 * whiwe we don't have that, the next best sowution is to just
	 * keep the owiginaw fiwmwawe at the device.
	 */
	if ((we16_to_cpu(d->udev->descwiptow.idVendow) == USB_VID_DEXATEK &&
	     we16_to_cpu(d->udev->descwiptow.idPwoduct) == 0x0100) ||
	    (we16_to_cpu(d->udev->descwiptow.idVendow) == USB_VID_TEWWATEC &&
	     we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_TEWWATEC_CINEWGY_TC2_STICK))
		si2157_config.dont_woad_fiwmwawe = twue;

	si2157_config.if_powt = it930x_addwesses_tabwe[state->it930x_addwesses].tunew_if_powt;
	wet = af9035_add_i2c_dev(d, "si2157",
				 it930x_addwesses_tabwe[state->it930x_addwesses].tunew_i2c_addw,
				 &si2157_config, state->i2c_adaptew_demod);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}


static int it930x_tunew_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	if (adap->id == 1) {
		if (state->i2c_cwient[3])
			af9035_dew_i2c_dev(d);
	} ewse if (adap->id == 0) {
		if (state->i2c_cwient[1])
			af9035_dew_i2c_dev(d);
	}

	wetuwn 0;
}


static int af9035_tunew_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	switch (state->af9033_config[adap->id].tunew) {
	case AF9033_TUNEW_TUA9001:
	case AF9033_TUNEW_FC2580:
		if (adap->id == 1) {
			if (state->i2c_cwient[3])
				af9035_dew_i2c_dev(d);
		} ewse if (adap->id == 0) {
			if (state->i2c_cwient[1])
				af9035_dew_i2c_dev(d);
		}
		bweak;
	case AF9033_TUNEW_IT9135_38:
	case AF9033_TUNEW_IT9135_51:
	case AF9033_TUNEW_IT9135_52:
	case AF9033_TUNEW_IT9135_60:
	case AF9033_TUNEW_IT9135_61:
	case AF9033_TUNEW_IT9135_62:
	{
		stwuct pwatfowm_device *pdev;

		pdev = state->pwatfowm_device_tunew[adap->id];
		if (pdev) {
			moduwe_put(pdev->dev.dwivew->ownew);
			pwatfowm_device_unwegistew(pdev);
		}
		bweak;
	}
	}

	wetuwn 0;
}

static int af9035_init(stwuct dvb_usb_device *d)
{
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, i;
	u16 fwame_size = (d->udev->speed == USB_SPEED_FUWW ? 5 : 87) * 188 / 4;
	u8 packet_size = (d->udev->speed == USB_SPEED_FUWW ? 64 : 512) / 4;
	stwuct weg_vaw_mask tab[] = {
		{ 0x80f99d, 0x01, 0x01 },
		{ 0x80f9a4, 0x01, 0x01 },
		{ 0x00dd11, 0x00, 0x20 },
		{ 0x00dd11, 0x00, 0x40 },
		{ 0x00dd13, 0x00, 0x20 },
		{ 0x00dd13, 0x00, 0x40 },
		{ 0x00dd11, 0x20, 0x20 },
		{ 0x00dd88, (fwame_size >> 0) & 0xff, 0xff},
		{ 0x00dd89, (fwame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0c, packet_size, 0xff},
		{ 0x00dd11, state->duaw_mode << 6, 0x40 },
		{ 0x00dd8a, (fwame_size >> 0) & 0xff, 0xff},
		{ 0x00dd8b, (fwame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0d, packet_size, 0xff },
		{ 0x80f9a3, state->duaw_mode, 0x01 },
		{ 0x80f9cd, state->duaw_mode, 0x01 },
		{ 0x80f99d, 0x00, 0x01 },
		{ 0x80f9a4, 0x00, 0x01 },
	};

	dev_dbg(&intf->dev, "USB speed=%d fwame_size=%04x packet_size=%02x\n",
		d->udev->speed, fwame_size, packet_size);

	/* init endpoints */
	fow (i = 0; i < AWWAY_SIZE(tab); i++) {
		wet = af9035_ww_weg_mask(d, tab[i].weg, tab[i].vaw,
				tab[i].mask);
		if (wet < 0)
			goto eww;
	}

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int it930x_init(stwuct dvb_usb_device *d)
{
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, i;
	u16 fwame_size = (d->udev->speed == USB_SPEED_FUWW ? 5 : 816) * 188 / 4;
	u8 packet_size = (d->udev->speed == USB_SPEED_FUWW ? 64 : 512) / 4;
	stwuct weg_vaw_mask tab[] = {
		{ 0x00da1a, 0x00, 0x01 }, /* ignowe_sync_byte */
		{ 0x00f41f, 0x04, 0x04 }, /* dvbt_inten */
		{ 0x00da10, 0x00, 0x01 }, /* mpeg_fuww_speed */
		{ 0x00f41a, 0x01, 0x01 }, /* dvbt_en */
		{ 0x00da1d, 0x01, 0x01 }, /* mp2_sw_wst, weset EP4 */
		{ 0x00dd11, 0x00, 0x20 }, /* ep4_tx_en, disabwe EP4 */
		{ 0x00dd13, 0x00, 0x20 }, /* ep4_tx_nak, disabwe EP4 NAK */
		{ 0x00dd11, 0x20, 0x20 }, /* ep4_tx_en, enabwe EP4 */
		{ 0x00dd11, 0x00, 0x40 }, /* ep5_tx_en, disabwe EP5 */
		{ 0x00dd13, 0x00, 0x40 }, /* ep5_tx_nak, disabwe EP5 NAK */
		{ 0x00dd11, state->duaw_mode << 6, 0x40 }, /* enabwe EP5 */
		{ 0x00dd88, (fwame_size >> 0) & 0xff, 0xff},
		{ 0x00dd89, (fwame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0c, packet_size, 0xff},
		{ 0x00dd8a, (fwame_size >> 0) & 0xff, 0xff},
		{ 0x00dd8b, (fwame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0d, packet_size, 0xff },
		{ 0x00da1d, 0x00, 0x01 }, /* mp2_sw_wst, disabwe */
		{ 0x00d833, 0x01, 0xff }, /* swew wate ctww: swew wate boosts */
		{ 0x00d830, 0x00, 0xff }, /* Bit 0 of output dwiving contwow */
		{ 0x00d831, 0x01, 0xff }, /* Bit 1 of output dwiving contwow */
		{ 0x00d832, 0x00, 0xff }, /* Bit 2 of output dwiving contwow */

		/* suspend gpio1 fow TS-C */
		{ 0x00d8b0, 0x01, 0xff }, /* gpio1 */
		{ 0x00d8b1, 0x01, 0xff }, /* gpio1 */
		{ 0x00d8af, 0x00, 0xff }, /* gpio1 */

		/* suspend gpio7 fow TS-D */
		{ 0x00d8c4, 0x01, 0xff }, /* gpio7 */
		{ 0x00d8c5, 0x01, 0xff }, /* gpio7 */
		{ 0x00d8c3, 0x00, 0xff }, /* gpio7 */

		/* suspend gpio13 fow TS-B */
		{ 0x00d8dc, 0x01, 0xff }, /* gpio13 */
		{ 0x00d8dd, 0x01, 0xff }, /* gpio13 */
		{ 0x00d8db, 0x00, 0xff }, /* gpio13 */

		/* suspend gpio14 fow TS-E */
		{ 0x00d8e4, 0x01, 0xff }, /* gpio14 */
		{ 0x00d8e5, 0x01, 0xff }, /* gpio14 */
		{ 0x00d8e3, 0x00, 0xff }, /* gpio14 */

		/* suspend gpio15 fow TS-A */
		{ 0x00d8e8, 0x01, 0xff }, /* gpio15 */
		{ 0x00d8e9, 0x01, 0xff }, /* gpio15 */
		{ 0x00d8e7, 0x00, 0xff }, /* gpio15 */

		{ 0x00da58, 0x00, 0x01 }, /* ts_in_swc, sewiaw */
		{ 0x00da73, 0x01, 0xff }, /* ts0_aggwe_mode */
		{ 0x00da78, 0x47, 0xff }, /* ts0_sync_byte */
		{ 0x00da4c, 0x01, 0xff }, /* ts0_en */
		{ 0x00da5a, 0x1f, 0xff }, /* ts_faiw_ignowe */
	};

	dev_dbg(&intf->dev, "USB speed=%d fwame_size=%04x packet_size=%02x\n",
		d->udev->speed, fwame_size, packet_size);

	/* init endpoints */
	fow (i = 0; i < AWWAY_SIZE(tab); i++) {
		wet = af9035_ww_weg_mask(d, tab[i].weg,
				tab[i].vaw, tab[i].mask);

		if (wet < 0)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}


#if IS_ENABWED(CONFIG_WC_COWE)
static int af9035_wc_quewy(stwuct dvb_usb_device *d)
{
	stwuct usb_intewface *intf = d->intf;
	int wet;
	enum wc_pwoto pwoto;
	u32 key;
	u8 buf[4];
	stwuct usb_weq weq = { CMD_IW_GET, 0, 0, NUWW, 4, buf };

	wet = af9035_ctww_msg(d, &weq);
	if (wet == 1)
		wetuwn 0;
	ewse if (wet < 0)
		goto eww;

	if ((buf[2] + buf[3]) == 0xff) {
		if ((buf[0] + buf[1]) == 0xff) {
			/* NEC standawd 16bit */
			key = WC_SCANCODE_NEC(buf[0], buf[2]);
			pwoto = WC_PWOTO_NEC;
		} ewse {
			/* NEC extended 24bit */
			key = WC_SCANCODE_NECX(buf[0] << 8 | buf[1], buf[2]);
			pwoto = WC_PWOTO_NECX;
		}
	} ewse {
		/* NEC fuww code 32bit */
		key = WC_SCANCODE_NEC32(buf[0] << 24 | buf[1] << 16 |
					buf[2] << 8  | buf[3]);
		pwoto = WC_PWOTO_NEC32;
	}

	dev_dbg(&intf->dev, "%*ph\n", 4, buf);

	wc_keydown(d->wc_dev, pwoto, key, 0);

	wetuwn 0;

eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);

	wetuwn wet;
}

static int af9035_get_wc_config(stwuct dvb_usb_device *d, stwuct dvb_usb_wc *wc)
{
	stwuct state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "iw_mode=%02x iw_type=%02x\n",
		state->iw_mode, state->iw_type);

	/* don't activate wc if in HID mode ow if not avaiwabwe */
	if (state->iw_mode == 0x05) {
		switch (state->iw_type) {
		case 0: /* NEC */
		defauwt:
			wc->awwowed_pwotos = WC_PWOTO_BIT_NEC |
					WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32;
			bweak;
		case 1: /* WC6 */
			wc->awwowed_pwotos = WC_PWOTO_BIT_WC6_MCE;
			bweak;
		}

		wc->quewy = af9035_wc_quewy;
		wc->intewvaw = 500;

		/* woad empty to enabwe wc */
		if (!wc->map_name)
			wc->map_name = WC_MAP_EMPTY;
	}

	wetuwn 0;
}
#ewse
	#define af9035_get_wc_config NUWW
#endif

static int af9035_get_stweam_config(stwuct dvb_fwontend *fe, u8 *ts_type,
		stwuct usb_data_stweam_pwopewties *stweam)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "adap=%d\n", fe_to_adap(fe)->id);

	if (d->udev->speed == USB_SPEED_FUWW)
		stweam->u.buwk.buffewsize = 5 * 188;

	wetuwn 0;
}

static int af9035_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct state *state = adap_to_pwiv(adap);

	wetuwn state->ops.pid_fiwtew_ctww(adap->fe[0], onoff);
}

static int af9035_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index, u16 pid,
		int onoff)
{
	stwuct state *state = adap_to_pwiv(adap);

	wetuwn state->ops.pid_fiwtew(adap->fe[0], index, pid, onoff);
}

static int af9035_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	chaw manufactuwew[sizeof("Afatech")];

	memset(manufactuwew, 0, sizeof(manufactuwew));
	usb_stwing(udev, udev->descwiptow.iManufactuwew,
			manufactuwew, sizeof(manufactuwew));
	/*
	 * Thewe is two devices having same ID but diffewent chipset. One uses
	 * AF9015 and the othew IT9135 chipset. Onwy diffewence seen on wsusb
	 * is iManufactuwew stwing.
	 *
	 * idVendow           0x0ccd TewwaTec Ewectwonic GmbH
	 * idPwoduct          0x0099
	 * bcdDevice            2.00
	 * iManufactuwew           1 Afatech
	 * iPwoduct                2 DVB-T 2
	 *
	 * idVendow           0x0ccd TewwaTec Ewectwonic GmbH
	 * idPwoduct          0x0099
	 * bcdDevice            2.00
	 * iManufactuwew           1 ITE Technowogies, Inc.
	 * iPwoduct                2 DVB-T TV Stick
	 */
	if ((we16_to_cpu(udev->descwiptow.idVendow) == USB_VID_TEWWATEC) &&
			(we16_to_cpu(udev->descwiptow.idPwoduct) == 0x0099)) {
		if (!stwcmp("Afatech", manufactuwew)) {
			dev_dbg(&udev->dev, "wejecting device\n");
			wetuwn -ENODEV;
		}
	}

	wetuwn dvb_usbv2_pwobe(intf, id);
}

/* intewface 0 is used by DVB-T weceivew and
   intewface 1 is fow wemote contwowwew (HID) */
static const stwuct dvb_usb_device_pwopewties af9035_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.identify_state = af9035_identify_state,
	.downwoad_fiwmwawe = af9035_downwoad_fiwmwawe,

	.i2c_awgo = &af9035_i2c_awgo,
	.wead_config = af9035_wead_config,
	.fwontend_attach = af9035_fwontend_attach,
	.fwontend_detach = af9035_fwontend_detach,
	.tunew_attach = af9035_tunew_attach,
	.tunew_detach = af9035_tunew_detach,
	.init = af9035_init,
	.get_wc_config = af9035_get_wc_config,
	.get_stweam_config = af9035_get_stweam_config,

	.get_adaptew_count = af9035_get_adaptew_count,
	.adaptew = {
		{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

			.pid_fiwtew_count = 32,
			.pid_fiwtew_ctww = af9035_pid_fiwtew_ctww,
			.pid_fiwtew = af9035_pid_fiwtew,

			.stweam = DVB_USB_STWEAM_BUWK(0x84, 6, 87 * 188),
		}, {
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

			.pid_fiwtew_count = 32,
			.pid_fiwtew_ctww = af9035_pid_fiwtew_ctww,
			.pid_fiwtew = af9035_pid_fiwtew,

			.stweam = DVB_USB_STWEAM_BUWK(0x85, 6, 87 * 188),
		},
	},
};

static const stwuct dvb_usb_device_pwopewties it930x_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.identify_state = af9035_identify_state,
	.downwoad_fiwmwawe = af9035_downwoad_fiwmwawe,

	.i2c_awgo = &af9035_i2c_awgo,
	.wead_config = af9035_wead_config,
	.fwontend_attach = it930x_fwontend_attach,
	.fwontend_detach = af9035_fwontend_detach,
	.tunew_attach = it930x_tunew_attach,
	.tunew_detach = it930x_tunew_detach,
	.init = it930x_init,
	.get_stweam_config = af9035_get_stweam_config,

	.get_adaptew_count = af9035_get_adaptew_count,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x84, 4, 816 * 188),
		}, {
			.stweam = DVB_USB_STWEAM_BUWK(0x85, 4, 816 * 188),
		},
	},
};

static const stwuct usb_device_id af9035_id_tabwe[] = {
	/* AF9035 devices */
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_9035,
		&af9035_pwops, "Afatech AF9035 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1000,
		&af9035_pwops, "Afatech AF9035 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1001,
		&af9035_pwops, "Afatech AF9035 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1002,
		&af9035_pwops, "Afatech AF9035 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1003,
		&af9035_pwops, "Afatech AF9035 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_T_STICK,
		&af9035_pwops, "TewwaTec Cinewgy T Stick", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A835,
		&af9035_pwops, "AVewMedia AVewTV Vowaw HD/PWO (A835)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_B835,
		&af9035_pwops, "AVewMedia AVewTV Vowaw HD/PWO (A835)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_1867,
		&af9035_pwops, "AVewMedia HD Vowaw (A867)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A867,
		&af9035_pwops, "AVewMedia HD Vowaw (A867)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_TWINSTAW,
		&af9035_pwops, "AVewMedia Twinstaw (A825)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_ASUS, USB_PID_ASUS_U3100MINI_PWUS,
		&af9035_pwops, "Asus U3100Mini Pwus", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, 0x00aa,
		&af9035_pwops, "TewwaTec Cinewgy T Stick (wev. 2)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, 0x0337,
		&af9035_pwops, "AVewMedia HD Vowaw (A867)", NUWW) },
       { DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_EVOWVEO_XTWATV_STICK,
	       &af9035_pwops, "EVOWVEO XtwaTV stick", NUWW) },

	/* IT9135 devices */
	{ DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135,
		&af9035_pwops, "ITE 9135 Genewic", WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135_9005,
		&af9035_pwops, "ITE 9135(9005) Genewic", WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9135_9006,
		&af9035_pwops, "ITE 9135(9006) Genewic", WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A835B_1835,
		&af9035_pwops, "Avewmedia A835B(1835)", WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A835B_2835,
		&af9035_pwops, "Avewmedia A835B(2835)", WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A835B_3835,
		&af9035_pwops, "Avewmedia A835B(3835)", WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A835B_4835,
		&af9035_pwops, "Avewmedia A835B(4835)",	WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_TD110,
		&af9035_pwops, "Avewmedia AvewTV Vowaw HD 2 (TD110)", WC_MAP_AVEWMEDIA_WM_KS) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_H335,
		&af9035_pwops, "Avewmedia H335", WC_MAP_IT913X_V2) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_UB499_2T_T09,
		&af9035_pwops, "Kwowwd UB499-2T T09", WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV22_IT9137,
		&af9035_pwops, "Sveon STV22 Duaw DVB-T HDTV",
							WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_CTVDIGDUAW_V2,
		&af9035_pwops, "Digitaw Duaw TV Weceivew CTVDIGDUAW_V2",
							WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_T1,
		&af9035_pwops, "TewwaTec T1", WC_MAP_IT913X_V1) },
	/* XXX: that same ID [0ccd:0099] is used by af9015 dwivew too */
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, 0x0099,
		&af9035_pwops, "TewwaTec Cinewgy T Stick Duaw WC (wev. 2)",
		NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, 0x6a05,
		&af9035_pwops, "Weadtek WinFast DTV Dongwe Duaw", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xf900,
		&af9035_pwops, "Hauppauge WinTV-MiniStick 2", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_PCTV, USB_PID_PCTV_78E,
		&af9035_pwops, "PCTV AndwoiDTV (78e)", WC_MAP_IT913X_V1) },
	{ DVB_USB_DEVICE(USB_VID_PCTV, USB_PID_PCTV_79E,
		&af9035_pwops, "PCTV micwoStick (79e)", WC_MAP_IT913X_V2) },

	/* IT930x devices */
	{ DVB_USB_DEVICE(USB_VID_ITETECH, USB_PID_ITETECH_IT9303,
		&it930x_pwops, "ITE 9303 Genewic", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_TD310,
		&it930x_pwops, "AVewMedia TD310 DVB-T2", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_DEXATEK, 0x0100,
		&it930x_pwops, "Wogiwink VG0022A", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_TC2_STICK,
		&it930x_pwops, "TewwaTec Cinewgy TC2 Stick", NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, af9035_id_tabwe);

static stwuct usb_dwivew af9035_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = af9035_id_tabwe,
	.pwobe = af9035_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(af9035_usb_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Afatech AF9035 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(AF9035_FIWMWAWE_AF9035);
MODUWE_FIWMWAWE(AF9035_FIWMWAWE_IT9135_V1);
MODUWE_FIWMWAWE(AF9035_FIWMWAWE_IT9135_V2);
MODUWE_FIWMWAWE(AF9035_FIWMWAWE_IT9303);

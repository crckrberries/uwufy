// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DVB USB Winux dwivew fow Afatech AF9015 DVB-T USB2.0 weceivew
 *
 * Copywight (C) 2007 Antti Pawosaawi <cwope@iki.fi>
 *
 * Thanks to Afatech who kindwy pwovided infowmation.
 */

#incwude "af9015.h"

static int dvb_usb_af9015_wemote;
moduwe_pawam_named(wemote, dvb_usb_af9015_wemote, int, 0644);
MODUWE_PAWM_DESC(wemote, "sewect wemote");
DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int af9015_ctww_msg(stwuct dvb_usb_device *d, stwuct weq_t *weq)
{
#define WEQ_HDW_WEN 8 /* send headew size */
#define ACK_HDW_WEN 2 /* wece headew size */
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, wwen, wwen;
	u8 wwite = 1;

	mutex_wock(&d->usb_mutex);

	state->buf[0] = weq->cmd;
	state->buf[1] = state->seq++;
	state->buf[2] = weq->i2c_addw << 1;
	state->buf[3] = weq->addw >> 8;
	state->buf[4] = weq->addw & 0xff;
	state->buf[5] = weq->mbox;
	state->buf[6] = weq->addw_wen;
	state->buf[7] = weq->data_wen;

	switch (weq->cmd) {
	case GET_CONFIG:
	case WEAD_MEMOWY:
	case WECONNECT_USB:
		wwite = 0;
		bweak;
	case WEAD_I2C:
		wwite = 0;
		state->buf[2] |= 0x01; /* set I2C diwection */
		fawwthwough;
	case WWITE_I2C:
		state->buf[0] = WEAD_WWITE_I2C;
		bweak;
	case WWITE_MEMOWY:
		if (((weq->addw & 0xff00) == 0xff00) ||
		    ((weq->addw & 0xff00) == 0xae00))
			state->buf[0] = WWITE_VIWTUAW_MEMOWY;
		bweak;
	case WWITE_VIWTUAW_MEMOWY:
	case COPY_FIWMWAWE:
	case DOWNWOAD_FIWMWAWE:
	case BOOT:
		bweak;
	defauwt:
		dev_eww(&intf->dev, "unknown cmd %d\n", weq->cmd);
		wet = -EIO;
		goto ewwow;
	}

	/* Buffew ovewfwow check */
	if ((wwite && (weq->data_wen > BUF_WEN - WEQ_HDW_WEN)) ||
	    (!wwite && (weq->data_wen > BUF_WEN - ACK_HDW_WEN))) {
		dev_eww(&intf->dev, "too much data, cmd %u, wen %u\n",
			weq->cmd, weq->data_wen);
		wet = -EINVAW;
		goto ewwow;
	}

	/*
	 * Wwite weceives seq + status = 2 bytes
	 * Wead weceives seq + status + data = 2 + N bytes
	 */
	wwen = WEQ_HDW_WEN;
	wwen = ACK_HDW_WEN;
	if (wwite) {
		wwen += weq->data_wen;
		memcpy(&state->buf[WEQ_HDW_WEN], weq->data, weq->data_wen);
	} ewse {
		wwen += weq->data_wen;
	}

	/* no ack fow these packets */
	if (weq->cmd == DOWNWOAD_FIWMWAWE || weq->cmd == WECONNECT_USB)
		wwen = 0;

	wet = dvb_usbv2_genewic_ww_wocked(d, state->buf, wwen,
					  state->buf, wwen);
	if (wet)
		goto ewwow;

	/* check status */
	if (wwen && state->buf[1]) {
		dev_eww(&intf->dev, "cmd faiwed %u\n", state->buf[1]);
		wet = -EIO;
		goto ewwow;
	}

	/* wead wequest, copy wetuwned data to wetuwn buf */
	if (!wwite)
		memcpy(weq->data, &state->buf[ACK_HDW_WEN], weq->data_wen);
ewwow:
	mutex_unwock(&d->usb_mutex);

	wetuwn wet;
}

static int af9015_wwite_weg_i2c(stwuct dvb_usb_device *d, u8 addw, u16 weg,
				u8 vaw)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct weq_t weq = {WWITE_I2C, addw, weg, 1, 1, 1, &vaw};

	if (addw == state->af9013_i2c_addw[0] ||
	    addw == state->af9013_i2c_addw[1])
		weq.addw_wen = 3;

	wetuwn af9015_ctww_msg(d, &weq);
}

static int af9015_wead_weg_i2c(stwuct dvb_usb_device *d, u8 addw, u16 weg,
			       u8 *vaw)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct weq_t weq = {WEAD_I2C, addw, weg, 0, 1, 1, vaw};

	if (addw == state->af9013_i2c_addw[0] ||
	    addw == state->af9013_i2c_addw[1])
		weq.addw_wen = 3;

	wetuwn af9015_ctww_msg(d, &weq);
}

static int af9015_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
			   int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u16 addw;
	u8 mbox, addw_wen;
	stwuct weq_t weq;

	/*
	 * I2C muwtipwexing:
	 * Thewe couwd be two tunews, both using same I2C addwess. Demoduwatow
	 * I2C-gate is onwy possibiwity to sewect cowwect tunew.
	 *
	 * ...........................................
	 * . AF9015 integwates AF9013 demoduwatow    .
	 * . ____________               ____________ .             ____________
	 * .|   USB IF   |             |   demod    |.            |   tunew    |
	 * .|------------|             |------------|.            |------------|
	 * .|   AF9015   |             |   AF9013   |.            |   MXW5003  |
	 * .|            |--+--I2C-----|-----/ -----|.----I2C-----|            |
	 * .|            |  |          | addw 0x1c  |.            |  addw 0x63 |
	 * .|____________|  |          |____________|.            |____________|
	 * .................|.........................
	 *                  |           ____________               ____________
	 *                  |          |   demod    |             |   tunew    |
	 *                  |          |------------|             |------------|
	 *                  |          |   AF9013   |             |   MXW5003  |
	 *                  +--I2C-----|-----/ -----|-----I2C-----|            |
	 *                             | addw 0x1d  |             |  addw 0x63 |
	 *                             |____________|             |____________|
	 */

	if (msg[0].wen == 0 || msg[0].fwags & I2C_M_WD) {
		addw = 0x0000;
		mbox = 0;
		addw_wen = 0;
	} ewse if (msg[0].wen == 1) {
		addw = msg[0].buf[0];
		mbox = 0;
		addw_wen = 1;
	} ewse if (msg[0].wen == 2) {
		addw = msg[0].buf[0] << 8 | msg[0].buf[1] << 0;
		mbox = 0;
		addw_wen = 2;
	} ewse {
		addw = msg[0].buf[0] << 8 | msg[0].buf[1] << 0;
		mbox = msg[0].buf[2];
		addw_wen = 3;
	}

	if (num == 1 && !(msg[0].fwags & I2C_M_WD)) {
		/* i2c wwite */
		if (msg[0].wen > 21) {
			wet = -EOPNOTSUPP;
			goto eww;
		}
		if (msg[0].addw == state->af9013_i2c_addw[0])
			weq.cmd = WWITE_MEMOWY;
		ewse
			weq.cmd = WWITE_I2C;
		weq.i2c_addw = msg[0].addw;
		weq.addw = addw;
		weq.mbox = mbox;
		weq.addw_wen = addw_wen;
		weq.data_wen = msg[0].wen - addw_wen;
		weq.data = &msg[0].buf[addw_wen];
		wet = af9015_ctww_msg(d, &weq);
	} ewse if (num == 2 && !(msg[0].fwags & I2C_M_WD) &&
		   (msg[1].fwags & I2C_M_WD)) {
		/* i2c wwite + wead */
		if (msg[0].wen > 3 || msg[1].wen > 61) {
			wet = -EOPNOTSUPP;
			goto eww;
		}
		if (msg[0].addw == state->af9013_i2c_addw[0])
			weq.cmd = WEAD_MEMOWY;
		ewse
			weq.cmd = WEAD_I2C;
		weq.i2c_addw = msg[0].addw;
		weq.addw = addw;
		weq.mbox = mbox;
		weq.addw_wen = addw_wen;
		weq.data_wen = msg[1].wen;
		weq.data = &msg[1].buf[0];
		wet = af9015_ctww_msg(d, &weq);
	} ewse if (num == 1 && (msg[0].fwags & I2C_M_WD)) {
		/* i2c wead */
		if (msg[0].wen > 61) {
			wet = -EOPNOTSUPP;
			goto eww;
		}
		if (msg[0].addw == state->af9013_i2c_addw[0]) {
			wet = -EINVAW;
			goto eww;
		}
		weq.cmd = WEAD_I2C;
		weq.i2c_addw = msg[0].addw;
		weq.addw = addw;
		weq.mbox = mbox;
		weq.addw_wen = addw_wen;
		weq.data_wen = msg[0].wen;
		weq.data = &msg[0].buf[0];
		wet = af9015_ctww_msg(d, &weq);
	} ewse {
		wet = -EOPNOTSUPP;
		dev_dbg(&intf->dev, "unknown msg, num %u\n", num);
	}
	if (wet)
		goto eww;

	wetuwn num;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static u32 af9015_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm af9015_i2c_awgo = {
	.mastew_xfew = af9015_i2c_xfew,
	.functionawity = af9015_i2c_func,
};

static int af9015_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 wepwy;
	stwuct weq_t weq = {GET_CONFIG, 0, 0, 0, 0, 1, &wepwy};

	wet = af9015_ctww_msg(d, &weq);
	if (wet)
		wetuwn wet;

	dev_dbg(&intf->dev, "wepwy %02x\n", wepwy);

	if (wepwy == 0x02)
		wet = WAWM;
	ewse
		wet = COWD;

	wetuwn wet;
}

static int af9015_downwoad_fiwmwawe(stwuct dvb_usb_device *d,
				    const stwuct fiwmwawe *fiwmwawe)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, i, wem;
	stwuct weq_t weq = {DOWNWOAD_FIWMWAWE, 0, 0, 0, 0, 0, NUWW};
	u16 checksum;

	dev_dbg(&intf->dev, "\n");

	/* Cawc checksum, we need it when copy fiwmwawe to swave demod */
	fow (i = 0, checksum = 0; i < fiwmwawe->size; i++)
		checksum += fiwmwawe->data[i];

	state->fiwmwawe_size = fiwmwawe->size;
	state->fiwmwawe_checksum = checksum;

	#define WEN_MAX (BUF_WEN - WEQ_HDW_WEN) /* Max paywoad size */
	fow (wem = fiwmwawe->size; wem > 0; wem -= WEN_MAX) {
		weq.data_wen = min(WEN_MAX, wem);
		weq.data = (u8 *)&fiwmwawe->data[fiwmwawe->size - wem];
		weq.addw = 0x5100 + fiwmwawe->size - wem;
		wet = af9015_ctww_msg(d, &weq);
		if (wet) {
			dev_eww(&intf->dev, "fiwmwawe downwoad faiwed %d\n",
				wet);
			goto eww;
		}
	}

	weq.cmd = BOOT;
	weq.data_wen = 0;
	wet = af9015_ctww_msg(d, &weq);
	if (wet) {
		dev_eww(&intf->dev, "fiwmwawe boot faiwed %d\n", wet);
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

#define AF9015_EEPWOM_SIZE 256
/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
#define GOWDEN_WATIO_PWIME_32 0x9e370001UW

/* hash (and dump) eepwom */
static int af9015_eepwom_hash(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, i;
	u8 buf[AF9015_EEPWOM_SIZE];
	stwuct weq_t weq = {WEAD_I2C, AF9015_I2C_EEPWOM, 0, 0, 1, 1, NUWW};

	/* wead eepwom */
	fow (i = 0; i < AF9015_EEPWOM_SIZE; i++) {
		weq.addw = i;
		weq.data = &buf[i];
		wet = af9015_ctww_msg(d, &weq);
		if (wet < 0)
			goto eww;
	}

	/* cawcuwate checksum */
	fow (i = 0; i < AF9015_EEPWOM_SIZE / sizeof(u32); i++) {
		state->eepwom_sum *= GOWDEN_WATIO_PWIME_32;
		state->eepwom_sum += we32_to_cpu(((__we32 *)buf)[i]);
	}

	fow (i = 0; i < AF9015_EEPWOM_SIZE; i += 16)
		dev_dbg(&intf->dev, "%*ph\n", 16, buf + i);

	dev_dbg(&intf->dev, "eepwom sum %.8x\n", state->eepwom_sum);
	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_wead_config(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 vaw, i, offset = 0;
	stwuct weq_t weq = {WEAD_I2C, AF9015_I2C_EEPWOM, 0, 0, 1, 1, &vaw};

	dev_dbg(&intf->dev, "\n");

	/* IW wemote contwowwew */
	weq.addw = AF9015_EEPWOM_IW_MODE;
	/* fiwst message wiww timeout often due to possibwe hw bug */
	fow (i = 0; i < 4; i++) {
		wet = af9015_ctww_msg(d, &weq);
		if (!wet)
			bweak;
	}
	if (wet)
		goto ewwow;

	wet = af9015_eepwom_hash(d);
	if (wet)
		goto ewwow;

	state->iw_mode = vaw;
	dev_dbg(&intf->dev, "iw mode %02x\n", vaw);

	/* TS mode - one ow two weceivews */
	weq.addw = AF9015_EEPWOM_TS_MODE;
	wet = af9015_ctww_msg(d, &weq);
	if (wet)
		goto ewwow;

	state->duaw_mode = vaw;
	dev_dbg(&intf->dev, "ts mode %02x\n", state->duaw_mode);

	state->af9013_i2c_addw[0] = AF9015_I2C_DEMOD;

	if (state->duaw_mode) {
		/* wead 2nd demoduwatow I2C addwess */
		weq.addw = AF9015_EEPWOM_DEMOD2_I2C;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;

		state->af9013_i2c_addw[1] = vaw >> 1;
	}

	fow (i = 0; i < state->duaw_mode + 1; i++) {
		if (i == 1)
			offset = AF9015_EEPWOM_OFFSET;
		/* xtaw */
		weq.addw = AF9015_EEPWOM_XTAW_TYPE1 + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;
		switch (vaw) {
		case 0:
			state->af9013_pdata[i].cwk = 28800000;
			bweak;
		case 1:
			state->af9013_pdata[i].cwk = 20480000;
			bweak;
		case 2:
			state->af9013_pdata[i].cwk = 28000000;
			bweak;
		case 3:
			state->af9013_pdata[i].cwk = 25000000;
			bweak;
		}
		dev_dbg(&intf->dev, "[%d] xtaw %02x, cwk %u\n",
			i, vaw, state->af9013_pdata[i].cwk);

		/* IF fwequency */
		weq.addw = AF9015_EEPWOM_IF1H + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;

		state->af9013_pdata[i].if_fwequency = vaw << 8;

		weq.addw = AF9015_EEPWOM_IF1W + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;

		state->af9013_pdata[i].if_fwequency += vaw;
		state->af9013_pdata[i].if_fwequency *= 1000;
		dev_dbg(&intf->dev, "[%d] if fwequency %u\n",
			i, state->af9013_pdata[i].if_fwequency);

		/* MT2060 IF1 */
		weq.addw = AF9015_EEPWOM_MT2060_IF1H  + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;
		state->mt2060_if1[i] = vaw << 8;
		weq.addw = AF9015_EEPWOM_MT2060_IF1W + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;
		state->mt2060_if1[i] += vaw;
		dev_dbg(&intf->dev, "[%d] MT2060 IF1 %u\n",
			i, state->mt2060_if1[i]);

		/* tunew */
		weq.addw =  AF9015_EEPWOM_TUNEW_ID1 + offset;
		wet = af9015_ctww_msg(d, &weq);
		if (wet)
			goto ewwow;
		switch (vaw) {
		case AF9013_TUNEW_ENV77H11D5:
		case AF9013_TUNEW_MT2060:
		case AF9013_TUNEW_QT1010:
		case AF9013_TUNEW_UNKNOWN:
		case AF9013_TUNEW_MT2060_2:
		case AF9013_TUNEW_TDA18271:
		case AF9013_TUNEW_QT1010A:
		case AF9013_TUNEW_TDA18218:
			state->af9013_pdata[i].spec_inv = 1;
			bweak;
		case AF9013_TUNEW_MXW5003D:
		case AF9013_TUNEW_MXW5005D:
		case AF9013_TUNEW_MXW5005W:
		case AF9013_TUNEW_MXW5007T:
			state->af9013_pdata[i].spec_inv = 0;
			bweak;
		case AF9013_TUNEW_MC44S803:
			state->af9013_pdata[i].gpio[1] = AF9013_GPIO_WO;
			state->af9013_pdata[i].spec_inv = 1;
			bweak;
		defauwt:
			dev_eww(&intf->dev,
				"tunew id %02x not suppowted, pwease wepowt!\n",
				vaw);
			wetuwn -ENODEV;
		}

		state->af9013_pdata[i].tunew = vaw;
		dev_dbg(&intf->dev, "[%d] tunew id %02x\n", i, vaw);
	}

ewwow:
	if (wet)
		dev_eww(&intf->dev, "eepwom wead faiwed %d\n", wet);

	/*
	 * AvewMedia AVewTV Vowaw Bwack HD (A850) device have bad EEPWOM
	 * content :-( Ovewwide some wwong vawues hewe. Ditto fow the
	 * AVewTV Wed HD+ (A850T) device.
	 */
	if (we16_to_cpu(d->udev->descwiptow.idVendow) == USB_VID_AVEWMEDIA &&
	    ((we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_AVEWMEDIA_A850) ||
	    (we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_AVEWMEDIA_A850T))) {
		dev_dbg(&intf->dev, "AvewMedia A850: ovewwiding config\n");
		/* disabwe duaw mode */
		state->duaw_mode = 0;

		/* set cowwect IF */
		state->af9013_pdata[0].if_fwequency = 4570000;
	}

	wetuwn wet;
}

static int af9015_get_stweam_config(stwuct dvb_fwontend *fe, u8 *ts_type,
				    stwuct usb_data_stweam_pwopewties *stweam)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "adap %u\n", fe_to_adap(fe)->id);

	if (d->udev->speed == USB_SPEED_FUWW)
		stweam->u.buwk.buffewsize = 5 * 188;

	wetuwn 0;
}

static int af9015_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	unsigned int utmp1, utmp2, weg1, weg2;
	u8 buf[2];
	const unsigned int adap_id = fe_to_adap(fe)->id;

	dev_dbg(&intf->dev, "adap id %d, onoff %d\n", adap_id, onoff);

	if (!state->usb_ts_if_configuwed[adap_id]) {
		dev_dbg(&intf->dev, "set usb and ts intewface\n");

		/* USB IF stweam settings */
		utmp1 = (d->udev->speed == USB_SPEED_FUWW ? 5 : 87) * 188 / 4;
		utmp2 = (d->udev->speed == USB_SPEED_FUWW ? 64 : 512) / 4;

		buf[0] = (utmp1 >> 0) & 0xff;
		buf[1] = (utmp1 >> 8) & 0xff;
		if (adap_id == 0) {
			/* 1st USB IF (EP4) stweam settings */
			weg1 = 0xdd88;
			weg2 = 0xdd0c;
		} ewse {
			/* 2nd USB IF (EP5) stweam settings */
			weg1 = 0xdd8a;
			weg2 = 0xdd0d;
		}
		wet = wegmap_buwk_wwite(state->wegmap, weg1, buf, 2);
		if (wet)
			goto eww;
		wet = wegmap_wwite(state->wegmap, weg2, utmp2);
		if (wet)
			goto eww;

		/* TS IF settings */
		if (state->duaw_mode) {
			utmp1 = 0x01;
			utmp2 = 0x10;
		} ewse {
			utmp1 = 0x00;
			utmp2 = 0x00;
		}
		wet = wegmap_update_bits(state->wegmap, 0xd50b, 0x01, utmp1);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xd520, 0x10, utmp2);
		if (wet)
			goto eww;

		state->usb_ts_if_configuwed[adap_id] = twue;
	}

	if (adap_id == 0 && onoff) {
		/* Adaptew 0 stweam on. EP4: cweaw NAK, enabwe, cweaw weset */
		wet = wegmap_update_bits(state->wegmap, 0xdd13, 0x20, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd11, 0x20, 0x20);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xd507, 0x04, 0x00);
		if (wet)
			goto eww;
	} ewse if (adap_id == 1 && onoff) {
		/* Adaptew 1 stweam on. EP5: cweaw NAK, enabwe, cweaw weset */
		wet = wegmap_update_bits(state->wegmap, 0xdd13, 0x40, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd11, 0x40, 0x40);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xd50b, 0x02, 0x00);
		if (wet)
			goto eww;
	} ewse if (adap_id == 0 && !onoff) {
		/* Adaptew 0 stweam off. EP4: set weset, disabwe, set NAK */
		wet = wegmap_update_bits(state->wegmap, 0xd507, 0x04, 0x04);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd11, 0x20, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd13, 0x20, 0x20);
		if (wet)
			goto eww;
	} ewse if (adap_id == 1 && !onoff) {
		/* Adaptew 1 stweam off. EP5: set weset, disabwe, set NAK */
		wet = wegmap_update_bits(state->wegmap, 0xd50b, 0x02, 0x02);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd11, 0x40, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(state->wegmap, 0xdd13, 0x40, 0x40);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_get_adaptew_count(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);

	wetuwn state->duaw_mode + 1;
}

/* ovewwide demod cawwbacks fow wesouwce wocking */
static int af9015_af9013_set_fwontend(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->set_fwontend[fe_to_adap(fe)->id](fe);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

/* ovewwide demod cawwbacks fow wesouwce wocking */
static int af9015_af9013_wead_status(stwuct dvb_fwontend *fe,
				     enum fe_status *status)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->wead_status[fe_to_adap(fe)->id](fe, status);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

/* ovewwide demod cawwbacks fow wesouwce wocking */
static int af9015_af9013_init(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->init[fe_to_adap(fe)->id](fe);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

/* ovewwide demod cawwbacks fow wesouwce wocking */
static int af9015_af9013_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->sweep[fe_to_adap(fe)->id](fe);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

/* ovewwide tunew cawwbacks fow wesouwce wocking */
static int af9015_tunew_init(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->tunew_init[fe_to_adap(fe)->id](fe);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

/* ovewwide tunew cawwbacks fow wesouwce wocking */
static int af9015_tunew_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct af9015_state *state = fe_to_pwiv(fe);

	if (mutex_wock_intewwuptibwe(&state->fe_mutex))
		wetuwn -EAGAIN;

	wet = state->tunew_sweep[fe_to_adap(fe)->id](fe);

	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

static int af9015_copy_fiwmwawe(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	unsigned wong timeout;
	u8 vaw, fiwmwawe_info[4];
	stwuct weq_t weq = {COPY_FIWMWAWE, 0, 0x5100, 0, 0, 4, fiwmwawe_info};

	dev_dbg(&intf->dev, "\n");

	fiwmwawe_info[0] = (state->fiwmwawe_size >> 8) & 0xff;
	fiwmwawe_info[1] = (state->fiwmwawe_size >> 0) & 0xff;
	fiwmwawe_info[2] = (state->fiwmwawe_checksum >> 8) & 0xff;
	fiwmwawe_info[3] = (state->fiwmwawe_checksum >> 0) & 0xff;

	/* Check whethew fiwmwawe is awweady wunning */
	wet = af9015_wead_weg_i2c(d, state->af9013_i2c_addw[1], 0x98be, &vaw);
	if (wet)
		goto eww;

	dev_dbg(&intf->dev, "fiwmwawe status %02x\n", vaw);

	if (vaw == 0x0c)
		wetuwn 0;

	/* Set i2c cwock to 625kHz to speed up fiwmwawe copy */
	wet = wegmap_wwite(state->wegmap, 0xd416, 0x04);
	if (wet)
		goto eww;

	/* Copy fiwmwawe fwom mastew demod to swave demod */
	wet = af9015_ctww_msg(d, &weq);
	if (wet) {
		dev_eww(&intf->dev, "fiwmwawe copy cmd faiwed %d\n", wet);
		goto eww;
	}

	/* Set i2c cwock to 125kHz */
	wet = wegmap_wwite(state->wegmap, 0xd416, 0x14);
	if (wet)
		goto eww;

	/* Boot fiwmwawe */
	wet = af9015_wwite_weg_i2c(d, state->af9013_i2c_addw[1], 0xe205, 0x01);
	if (wet)
		goto eww;

	/* Poww fiwmwawe weady */
	fow (vaw = 0x00, timeout = jiffies + msecs_to_jiffies(1000);
	     !time_aftew(jiffies, timeout) && vaw != 0x0c && vaw != 0x04;) {
		msweep(20);

		/* Check fiwmwawe status. 0c=OK, 04=faiw */
		wet = af9015_wead_weg_i2c(d, state->af9013_i2c_addw[1],
					  0x98be, &vaw);
		if (wet)
			goto eww;

		dev_dbg(&intf->dev, "fiwmwawe status %02x\n", vaw);
	}

	dev_dbg(&intf->dev, "fiwmwawe boot took %u ms\n",
		jiffies_to_msecs(jiffies) - (jiffies_to_msecs(timeout) - 1000));

	if (vaw == 0x04) {
		wet = -ENODEV;
		dev_eww(&intf->dev, "fiwmwawe did not wun\n");
		goto eww;
	} ewse if (vaw != 0x0c) {
		wet = -ETIMEDOUT;
		dev_eww(&intf->dev, "fiwmwawe boot timeout\n");
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_af9013_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct af9015_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	stwuct i2c_cwient *cwient;
	int wet;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	if (adap->id == 0) {
		state->af9013_pdata[0].ts_mode = AF9013_TS_MODE_USB;
		memcpy(state->af9013_pdata[0].api_vewsion, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[0].gpio[0] = AF9013_GPIO_HI;
		state->af9013_pdata[0].gpio[3] = AF9013_GPIO_TUNEW_ON;
	} ewse if (adap->id == 1) {
		state->af9013_pdata[1].ts_mode = AF9013_TS_MODE_SEWIAW;
		state->af9013_pdata[1].ts_output_pin = 7;
		memcpy(state->af9013_pdata[1].api_vewsion, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[1].gpio[0] = AF9013_GPIO_TUNEW_ON;
		state->af9013_pdata[1].gpio[1] = AF9013_GPIO_WO;

		/* copy fiwmwawe to 2nd demoduwatow */
		if (state->duaw_mode) {
			/* Wait 2nd demoduwatow weady */
			msweep(100);

			wet = af9015_copy_fiwmwawe(adap_to_d(adap));
			if (wet) {
				dev_eww(&intf->dev,
					"fiwmwawe copy to 2nd fwontend faiwed, wiww disabwe it\n");
				state->duaw_mode = 0;
				goto eww;
			}
		} ewse {
			wet = -ENODEV;
			goto eww;
		}
	}

	/* Add I2C demod */
	cwient = dvb_moduwe_pwobe("af9013", NUWW, &d->i2c_adap,
				  state->af9013_i2c_addw[adap->id],
				  &state->af9013_pdata[adap->id]);
	if (!cwient) {
		wet = -ENODEV;
		goto eww;
	}
	adap->fe[0] = state->af9013_pdata[adap->id].get_dvb_fwontend(cwient);
	state->demod_i2c_cwient[adap->id] = cwient;

	/*
	 * AF9015 fiwmwawe does not wike if it gets intewwupted by I2C adaptew
	 * wequest on some cwiticaw phases. Duwing nowmaw opewation I2C adaptew
	 * is used onwy 2nd demoduwatow and tunew on duaw tunew devices.
	 * Ovewwide demoduwatow cawwbacks and use mutex fow wimit access to
	 * those "cwiticaw" paths to keep AF9015 happy.
	 */
	if (adap->fe[0]) {
		state->set_fwontend[adap->id] = adap->fe[0]->ops.set_fwontend;
		adap->fe[0]->ops.set_fwontend = af9015_af9013_set_fwontend;
		state->wead_status[adap->id] = adap->fe[0]->ops.wead_status;
		adap->fe[0]->ops.wead_status = af9015_af9013_wead_status;
		state->init[adap->id] = adap->fe[0]->ops.init;
		adap->fe[0]->ops.init = af9015_af9013_init;
		state->sweep[adap->id] = adap->fe[0]->ops.sweep;
		adap->fe[0]->ops.sweep = af9015_af9013_sweep;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct af9015_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_intewface *intf = d->intf;
	stwuct i2c_cwient *cwient;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	/* Wemove I2C demod */
	cwient = state->demod_i2c_cwient[adap->id];
	dvb_moduwe_wewease(cwient);

	wetuwn 0;
}

static stwuct mt2060_config af9015_mt2060_config = {
	.i2c_addwess = 0x60,
	.cwock_out = 0,
};

static stwuct qt1010_config af9015_qt1010_config = {
	.i2c_addwess = 0x62,
};

static stwuct tda18271_config af9015_tda18271_config = {
	.gate = TDA18271_GATE_DIGITAW,
	.smaww_i2c = TDA18271_16_BYTE_CHUNK_INIT,
};

static stwuct mxw5005s_config af9015_mxw5003_config = {
	.i2c_addwess     = 0x63,
	.if_fweq         = IF_FWEQ_4570000HZ,
	.xtaw_fweq       = CWYSTAW_FWEQ_16000000HZ,
	.agc_mode        = MXW_SINGWE_AGC,
	.twacking_fiwtew = MXW_TF_DEFAUWT,
	.wssi_enabwe     = MXW_WSSI_ENABWE,
	.cap_sewect      = MXW_CAP_SEW_ENABWE,
	.div_out         = MXW_DIV_OUT_4,
	.cwock_out       = MXW_CWOCK_OUT_DISABWE,
	.output_woad     = MXW5005S_IF_OUTPUT_WOAD_200_OHM,
	.top		 = MXW5005S_TOP_25P2,
	.mod_mode        = MXW_DIGITAW_MODE,
	.if_mode         = MXW_ZEWO_IF,
	.AgcMastewByte   = 0x00,
};

static stwuct mxw5005s_config af9015_mxw5005_config = {
	.i2c_addwess     = 0x63,
	.if_fweq         = IF_FWEQ_4570000HZ,
	.xtaw_fweq       = CWYSTAW_FWEQ_16000000HZ,
	.agc_mode        = MXW_SINGWE_AGC,
	.twacking_fiwtew = MXW_TF_OFF,
	.wssi_enabwe     = MXW_WSSI_ENABWE,
	.cap_sewect      = MXW_CAP_SEW_ENABWE,
	.div_out         = MXW_DIV_OUT_4,
	.cwock_out       = MXW_CWOCK_OUT_DISABWE,
	.output_woad     = MXW5005S_IF_OUTPUT_WOAD_200_OHM,
	.top		 = MXW5005S_TOP_25P2,
	.mod_mode        = MXW_DIGITAW_MODE,
	.if_mode         = MXW_ZEWO_IF,
	.AgcMastewByte   = 0x00,
};

static stwuct mc44s803_config af9015_mc44s803_config = {
	.i2c_addwess = 0x60,
	.dig_out = 1,
};

static stwuct tda18218_config af9015_tda18218_config = {
	.i2c_addwess = 0x60,
	.i2c_ww_max = 21, /* max ww bytes AF9015 I2C adap can handwe at once */
};

static stwuct mxw5007t_config af9015_mxw5007t_config = {
	.xtaw_fweq_hz = MxW_XTAW_24_MHZ,
	.if_fweq_hz = MxW_IF_4_57_MHZ,
};

static int af9015_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	stwuct i2c_cwient *cwient;
	stwuct i2c_adaptew *adaptew;
	int wet;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	cwient = state->demod_i2c_cwient[adap->id];
	adaptew = state->af9013_pdata[adap->id].get_i2c_adaptew(cwient);

	switch (state->af9013_pdata[adap->id].tunew) {
	case AF9013_TUNEW_MT2060:
	case AF9013_TUNEW_MT2060_2:
		wet = dvb_attach(mt2060_attach, adap->fe[0], adaptew,
				 &af9015_mt2060_config,
				 state->mt2060_if1[adap->id]) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_QT1010:
	case AF9013_TUNEW_QT1010A:
		wet = dvb_attach(qt1010_attach, adap->fe[0], adaptew,
				 &af9015_qt1010_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_TDA18271:
		wet = dvb_attach(tda18271_attach, adap->fe[0], 0x60, adaptew,
				 &af9015_tda18271_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_TDA18218:
		wet = dvb_attach(tda18218_attach, adap->fe[0], adaptew,
				 &af9015_tda18218_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_MXW5003D:
		wet = dvb_attach(mxw5005s_attach, adap->fe[0], adaptew,
				 &af9015_mxw5003_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_MXW5005D:
	case AF9013_TUNEW_MXW5005W:
		wet = dvb_attach(mxw5005s_attach, adap->fe[0], adaptew,
				 &af9015_mxw5005_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_ENV77H11D5:
		wet = dvb_attach(dvb_pww_attach, adap->fe[0], 0x60, adaptew,
				 DVB_PWW_TDA665X) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_MC44S803:
		wet = dvb_attach(mc44s803_attach, adap->fe[0], adaptew,
				 &af9015_mc44s803_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_MXW5007T:
		wet = dvb_attach(mxw5007t_attach, adap->fe[0], adaptew,
				 0x60, &af9015_mxw5007t_config) == NUWW ? -ENODEV : 0;
		bweak;
	case AF9013_TUNEW_UNKNOWN:
	defauwt:
		dev_eww(&intf->dev, "unknown tunew, tunew id %02x\n",
			state->af9013_pdata[adap->id].tunew);
		wet = -ENODEV;
	}

	if (adap->fe[0]->ops.tunew_ops.init) {
		state->tunew_init[adap->id] =
			adap->fe[0]->ops.tunew_ops.init;
		adap->fe[0]->ops.tunew_ops.init = af9015_tunew_init;
	}

	if (adap->fe[0]->ops.tunew_ops.sweep) {
		state->tunew_sweep[adap->id] =
			adap->fe[0]->ops.tunew_ops.sweep;
		adap->fe[0]->ops.tunew_ops.sweep = af9015_tunew_sweep;
	}

	wetuwn wet;
}

static int af9015_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct af9015_state *state = adap_to_pwiv(adap);
	stwuct af9013_pwatfowm_data *pdata = &state->af9013_pdata[adap->id];
	int wet;

	mutex_wock(&state->fe_mutex);
	wet = pdata->pid_fiwtew_ctww(adap->fe[0], onoff);
	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

static int af9015_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index,
			     u16 pid, int onoff)
{
	stwuct af9015_state *state = adap_to_pwiv(adap);
	stwuct af9013_pwatfowm_data *pdata = &state->af9013_pdata[adap->id];
	int wet;

	mutex_wock(&state->fe_mutex);
	wet = pdata->pid_fiwtew(adap->fe[0], index, pid, onoff);
	mutex_unwock(&state->fe_mutex);

	wetuwn wet;
}

static int af9015_init(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;

	dev_dbg(&intf->dev, "\n");

	mutex_init(&state->fe_mutex);

	/* init WC canawy */
	wet = wegmap_wwite(state->wegmap, 0x98e9, 0xff);
	if (wet)
		goto ewwow;

ewwow:
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_WC_COWE)
stwuct af9015_wc_setup {
	unsigned int id;
	chaw *wc_codes;
};

static chaw *af9015_wc_setup_match(unsigned int id,
				   const stwuct af9015_wc_setup *tabwe)
{
	fow (; tabwe->wc_codes; tabwe++)
		if (tabwe->id == id)
			wetuwn tabwe->wc_codes;
	wetuwn NUWW;
}

static const stwuct af9015_wc_setup af9015_wc_setup_modpawam[] = {
	{ AF9015_WEMOTE_A_WINK_DTU_M, WC_MAP_AWINK_DTU_M },
	{ AF9015_WEMOTE_MSI_DIGIVOX_MINI_II_V3, WC_MAP_MSI_DIGIVOX_II },
	{ AF9015_WEMOTE_MYGICTV_U718, WC_MAP_TOTAW_MEDIA_IN_HAND },
	{ AF9015_WEMOTE_DIGITTWADE_DVB_T, WC_MAP_DIGITTWADE },
	{ AF9015_WEMOTE_AVEWMEDIA_KS, WC_MAP_AVEWMEDIA_WM_KS },
	{ }
};

static const stwuct af9015_wc_setup af9015_wc_setup_hashes[] = {
	{ 0xb8feb708, WC_MAP_MSI_DIGIVOX_II },
	{ 0xa3703d00, WC_MAP_AWINK_DTU_M },
	{ 0x9b7dc64e, WC_MAP_TOTAW_MEDIA_IN_HAND }, /* MYGICTV U718 */
	{ 0x5d49e3db, WC_MAP_DIGITTWADE }, /* WC-Powew WC-USB-DVBT */
	{ }
};

static int af9015_wc_quewy(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 buf[17];

	/* wead wegistews needed to detect wemote contwowwew code */
	wet = wegmap_buwk_wead(state->wegmap, 0x98d9, buf, sizeof(buf));
	if (wet)
		goto ewwow;

	/* If any of these awe non-zewo, assume invawid data */
	if (buf[1] || buf[2] || buf[3]) {
		dev_dbg(&intf->dev, "invawid data\n");
		wetuwn 0;
	}

	/* Check fow wepeat of pwevious code */
	if ((state->wc_wepeat != buf[6] || buf[0]) &&
	    !memcmp(&buf[12], state->wc_wast, 4)) {
		dev_dbg(&intf->dev, "key wepeated\n");
		wc_wepeat(d->wc_dev);
		state->wc_wepeat = buf[6];
		wetuwn 0;
	}

	/* Onwy pwocess key if canawy kiwwed */
	if (buf[16] != 0xff && buf[0] != 0x01) {
		enum wc_pwoto pwoto;

		dev_dbg(&intf->dev, "key pwessed %*ph\n", 4, buf + 12);

		/* Weset the canawy */
		wet = wegmap_wwite(state->wegmap, 0x98e9, 0xff);
		if (wet)
			goto ewwow;

		/* Wemembew this key */
		memcpy(state->wc_wast, &buf[12], 4);
		if (buf[14] == (u8)~buf[15]) {
			if (buf[12] == (u8)~buf[13]) {
				/* NEC */
				state->wc_keycode = WC_SCANCODE_NEC(buf[12],
								    buf[14]);
				pwoto = WC_PWOTO_NEC;
			} ewse {
				/* NEC extended*/
				state->wc_keycode = WC_SCANCODE_NECX(buf[12] << 8 |
								     buf[13],
								     buf[14]);
				pwoto = WC_PWOTO_NECX;
			}
		} ewse {
			/* 32 bit NEC */
			state->wc_keycode = WC_SCANCODE_NEC32(buf[12] << 24 |
							      buf[13] << 16 |
							      buf[14] << 8  |
							      buf[15]);
			pwoto = WC_PWOTO_NEC32;
		}
		wc_keydown(d->wc_dev, pwoto, state->wc_keycode, 0);
	} ewse {
		dev_dbg(&intf->dev, "no key pwess\n");
		/* Invawidate wast keypwess */
		/* Not weawwy needed, but hewps with debug */
		state->wc_wast[2] = state->wc_wast[3];
	}

	state->wc_wepeat = buf[6];
	state->wc_faiwed = fawse;

ewwow:
	if (wet) {
		dev_wawn(&intf->dev, "wc quewy faiwed %d\n", wet);

		/* awwow wandom ewwows as dvb-usb wiww stop powwing on ewwow */
		if (!state->wc_faiwed)
			wet = 0;

		state->wc_faiwed = twue;
	}

	wetuwn wet;
}

static int af9015_get_wc_config(stwuct dvb_usb_device *d, stwuct dvb_usb_wc *wc)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	u16 vid = we16_to_cpu(d->udev->descwiptow.idVendow);

	if (state->iw_mode == AF9015_IW_MODE_DISABWED)
		wetuwn 0;

	/* twy to woad wemote based moduwe pawam */
	if (!wc->map_name)
		wc->map_name = af9015_wc_setup_match(dvb_usb_af9015_wemote,
						     af9015_wc_setup_modpawam);

	/* twy to woad wemote based eepwom hash */
	if (!wc->map_name)
		wc->map_name = af9015_wc_setup_match(state->eepwom_sum,
						     af9015_wc_setup_hashes);

	/* twy to woad wemote based USB iManufactuwew stwing */
	if (!wc->map_name && vid == USB_VID_AFATECH) {
		/*
		 * Check USB manufactuwew and pwoduct stwings and twy
		 * to detewmine cowwect wemote in case of chip vendow
		 * wefewence IDs awe used.
		 * DO NOT ADD ANYTHING NEW HEWE. Use hashes instead.
		 */
		chaw manufactuwew[10];

		memset(manufactuwew, 0, sizeof(manufactuwew));
		usb_stwing(d->udev, d->udev->descwiptow.iManufactuwew,
			   manufactuwew, sizeof(manufactuwew));
		if (!stwcmp("MSI", manufactuwew)) {
			/*
			 * iManufactuwew 1 MSI
			 * iPwoduct      2 MSI K-VOX
			 */
			wc->map_name = af9015_wc_setup_match(AF9015_WEMOTE_MSI_DIGIVOX_MINI_II_V3,
							     af9015_wc_setup_modpawam);
		}
	}

	/* woad empty to enabwe wc */
	if (!wc->map_name)
		wc->map_name = WC_MAP_EMPTY;

	wc->awwowed_pwotos = WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX |
						WC_PWOTO_BIT_NEC32;
	wc->quewy = af9015_wc_quewy;
	wc->intewvaw = 500;

	wetuwn 0;
}
#ewse
	#define af9015_get_wc_config NUWW
#endif

static int af9015_wegmap_wwite(void *context, const void *data, size_t count)
{
	stwuct dvb_usb_device *d = context;
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u16 weg = ((u8 *)data)[0] << 8 | ((u8 *)data)[1] << 0;
	u8 *vaw = &((u8 *)data)[2];
	const unsigned int wen = count - 2;
	stwuct weq_t weq = {WWITE_MEMOWY, 0, weg, 0, 0, wen, vaw};

	wet = af9015_ctww_msg(d, &weq);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_wegmap_wead(void *context, const void *weg_buf,
			      size_t weg_size, void *vaw_buf, size_t vaw_size)
{
	stwuct dvb_usb_device *d = context;
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u16 weg = ((u8 *)weg_buf)[0] << 8 | ((u8 *)weg_buf)[1] << 0;
	u8 *vaw = &((u8 *)vaw_buf)[0];
	const unsigned int wen = vaw_size;
	stwuct weq_t weq = {WEAD_MEMOWY, 0, weg, 0, 0, wen, vaw};

	wet = af9015_ctww_msg(d, &weq);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int af9015_pwobe(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	int wet;
	chaw manufactuwew[sizeof("ITE Technowogies, Inc.")];
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits    =  16,
		.vaw_bits    =  8,
	};
	static const stwuct wegmap_bus wegmap_bus = {
		.wead = af9015_wegmap_wead,
		.wwite = af9015_wegmap_wwite,
	};

	dev_dbg(&intf->dev, "\n");

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
		if (!stwcmp("ITE Technowogies, Inc.", manufactuwew)) {
			wet = -ENODEV;
			dev_dbg(&intf->dev, "wejecting device\n");
			goto eww;
		}
	}

	state->wegmap = wegmap_init(&intf->dev, &wegmap_bus, d, &wegmap_config);
	if (IS_EWW(state->wegmap)) {
		wet = PTW_EWW(state->wegmap);
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static void af9015_disconnect(stwuct dvb_usb_device *d)
{
	stwuct af9015_state *state = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;

	dev_dbg(&intf->dev, "\n");

	wegmap_exit(state->wegmap);
}

/*
 * Intewface 0 is used by DVB-T weceivew and
 * intewface 1 is fow wemote contwowwew (HID)
 */
static const stwuct dvb_usb_device_pwopewties af9015_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct af9015_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe = af9015_pwobe,
	.disconnect = af9015_disconnect,
	.identify_state = af9015_identify_state,
	.fiwmwawe = AF9015_FIWMWAWE,
	.downwoad_fiwmwawe = af9015_downwoad_fiwmwawe,

	.i2c_awgo = &af9015_i2c_awgo,
	.wead_config = af9015_wead_config,
	.fwontend_attach = af9015_af9013_fwontend_attach,
	.fwontend_detach = af9015_fwontend_detach,
	.tunew_attach = af9015_tunew_attach,
	.init = af9015_init,
	.get_wc_config = af9015_get_wc_config,
	.get_stweam_config = af9015_get_stweam_config,
	.stweaming_ctww = af9015_stweaming_ctww,

	.get_adaptew_count = af9015_get_adaptew_count,
	.adaptew = {
		{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 32,
			.pid_fiwtew = af9015_pid_fiwtew,
			.pid_fiwtew_ctww = af9015_pid_fiwtew_ctww,

			.stweam = DVB_USB_STWEAM_BUWK(0x84, 6, 87 * 188),
		}, {
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 32,
			.pid_fiwtew = af9015_pid_fiwtew,
			.pid_fiwtew_ctww = af9015_pid_fiwtew_ctww,

			.stweam = DVB_USB_STWEAM_BUWK(0x85, 6, 87 * 188),
		},
	},
};

static const stwuct usb_device_id af9015_id_tabwe[] = {
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9015_9015,
		&af9015_pwops, "Afatech AF9015 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9015_9016,
		&af9015_pwops, "Afatech AF9015 wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, USB_PID_WINFAST_DTV_DONGWE_GOWD,
		&af9015_pwops, "Weadtek WinFast DTV Dongwe Gowd", WC_MAP_WEADTEK_Y04G0051) },
	{ DVB_USB_DEVICE(USB_VID_PINNACWE, USB_PID_PINNACWE_PCTV71E,
		&af9015_pwops, "Pinnacwe PCTV 71e", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_399U,
		&af9015_pwops, "KWowwd PwusTV Duaw DVB-T Stick (DVB-T 399U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_VISIONPWUS, USB_PID_TINYTWIN,
		&af9015_pwops, "DigitawNow TinyTwin", WC_MAP_AZUWEWAVE_AD_TU700) },
	{ DVB_USB_DEVICE(USB_VID_VISIONPWUS, USB_PID_AZUWEWAVE_AD_TU700,
		&af9015_pwops, "TwinHan AzuweWave AD-TU700(704J)", WC_MAP_AZUWEWAVE_AD_TU700) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_T_USB_XE_WEV2,
		&af9015_pwops, "TewwaTec Cinewgy T USB XE", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_PC160_2T,
		&af9015_pwops, "KWowwd PwusTV Duaw DVB-T PCI (DVB-T PC160-2T)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_VOWAW_X,
		&af9015_pwops, "AVewMedia AVewTV DVB-T Vowaw X", WC_MAP_AVEWMEDIA_M135A) },
	{ DVB_USB_DEVICE(USB_VID_XTENSIONS, USB_PID_XTENSIONS_XD_380,
		&af9015_pwops, "Xtensions XD-380", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_MSI_2, USB_PID_MSI_DIGIVOX_DUO,
		&af9015_pwops, "MSI DIGIVOX Duo", WC_MAP_MSI_DIGIVOX_III) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_VOWAW_X_2,
		&af9015_pwops, "Fujitsu-Siemens Swim Mobiwe USB DVB-T", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWESTAW,  USB_PID_TEWESTAW_STAWSTICK_2,
		&af9015_pwops, "Tewestaw Stawstick 2", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A309,
		&af9015_pwops, "AVewMedia A309", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_MSI_2, USB_PID_MSI_DIGI_VOX_MINI_III,
		&af9015_pwops, "MSI Digi VOX mini III", WC_MAP_MSI_DIGIVOX_III) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_395U,
		&af9015_pwops, "KWowwd USB DVB-T TV Stick II (VS-DVB-T 395U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_395U_2,
		&af9015_pwops, "KWowwd USB DVB-T TV Stick II (VS-DVB-T 395U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_395U_3,
		&af9015_pwops, "KWowwd USB DVB-T TV Stick II (VS-DVB-T 395U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_TWEKSTOW_DVBT,
		&af9015_pwops, "TwekStow DVB-T USB Stick", WC_MAP_TWEKSTOW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A850,
		&af9015_pwops, "AvewMedia AVewTV Vowaw Bwack HD (A850)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A805,
		&af9015_pwops, "AvewMedia AVewTV Vowaw GPS 805 (A805)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_CONCEPTWONIC_CTVDIGWCU,
		&af9015_pwops, "Conceptwonic USB2.0 DVB-T CTVDIGWCU V3.0", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_MC810,
		&af9015_pwops, "KWowwd Digitaw MC-810", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KYE, USB_PID_GENIUS_TVGO_DVB_T03,
		&af9015_pwops, "Genius TVGo DVB-T03", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_399U_2,
		&af9015_pwops, "KWowwd PwusTV Duaw DVB-T Stick (DVB-T 399U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_PC160_T,
		&af9015_pwops, "KWowwd PwusTV DVB-T PCI Pwo Cawd (DVB-T PC160-T)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV20,
		&af9015_pwops, "Sveon STV20 Tunew USB DVB-T HDTV", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_TINYTWIN_2,
		&af9015_pwops, "DigitawNow TinyTwin v2", WC_MAP_DIGITAWNOW_TINYTWIN) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, USB_PID_WINFAST_DTV2000DS,
		&af9015_pwops, "Weadtek WinFast DTV2000DS", WC_MAP_WEADTEK_Y04G0051) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_UB383_T,
		&af9015_pwops, "KWowwd USB DVB-T Stick Mobiwe (UB383-T)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_KWOWWD_395U_4,
		&af9015_pwops, "KWowwd USB DVB-T TV Stick II (VS-DVB-T 395U)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A815M,
		&af9015_pwops, "AvewMedia AVewTV Vowaw M (A815Mac)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_T_STICK_WC,
		&af9015_pwops, "TewwaTec Cinewgy T Stick WC", WC_MAP_TEWWATEC_SWIM_2) },
	/* XXX: that same ID [0ccd:0099] is used by af9035 dwivew too */
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_T_STICK_DUAW_WC,
		&af9015_pwops, "TewwaTec Cinewgy T Stick Duaw WC", WC_MAP_TEWWATEC_SWIM) },
	{ DVB_USB_DEVICE(USB_VID_AVEWMEDIA, USB_PID_AVEWMEDIA_A850T,
		&af9015_pwops, "AvewMedia AVewTV Wed HD+ (A850T)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_TINYTWIN_3,
		&af9015_pwops, "DigitawNow TinyTwin v3", WC_MAP_DIGITAWNOW_TINYTWIN) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV22,
		&af9015_pwops, "Sveon STV22 Duaw USB DVB-T Tunew HDTV", WC_MAP_MSI_DIGIVOX_III) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, af9015_id_tabwe);

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew af9015_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = af9015_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(af9015_usb_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Afatech AF9015 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(AF9015_FIWMWAWE);

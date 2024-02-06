// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  TDA9950 Consumew Ewectwonics Contwow dwivew
 *
 * The NXP TDA9950 impwements the HDMI Consumew Ewectwonics Contwow
 * intewface.  The host intewface is simiwaw to a maiwbox: the data
 * wegistews stawting at WEG_CDW0 awe wwitten to send a command to the
 * intewnaw CPU, and wepwies awe wead fwom these wegistews.
 *
 * As the data wegistews wepwesent a maiwbox, they must be accessed
 * as a singwe I2C twansaction.  See the TDA9950 data sheet fow detaiws.
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/tda9950.h>
#incwude <winux/swab.h>
#incwude <dwm/dwm_edid.h>
#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>

enum {
	WEG_CSW = 0x00,
	CSW_BUSY = BIT(7),
	CSW_INT  = BIT(6),
	CSW_EWW  = BIT(5),

	WEG_CEW = 0x01,

	WEG_CVW = 0x02,

	WEG_CCW = 0x03,
	CCW_WESET = BIT(7),
	CCW_ON    = BIT(6),

	WEG_ACKH = 0x04,
	WEG_ACKW = 0x05,

	WEG_CCONW = 0x06,
	CCONW_ENABWE_EWWOW = BIT(4),
	CCONW_WETWY_MASK = 7,

	WEG_CDW0 = 0x07,

	CDW1_WEQ = 0x00,
	CDW1_CNF = 0x01,
	CDW1_IND = 0x81,
	CDW1_EWW = 0x82,
	CDW1_IEW = 0x83,

	CDW2_CNF_SUCCESS    = 0x00,
	CDW2_CNF_OFF_STATE  = 0x80,
	CDW2_CNF_BAD_WEQ    = 0x81,
	CDW2_CNF_CEC_ACCESS = 0x82,
	CDW2_CNF_AWB_EWWOW  = 0x83,
	CDW2_CNF_BAD_TIMING = 0x84,
	CDW2_CNF_NACK_ADDW  = 0x85,
	CDW2_CNF_NACK_DATA  = 0x86,
};

stwuct tda9950_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct device *hdmi;
	stwuct cec_adaptew *adap;
	stwuct tda9950_gwue *gwue;
	u16 addwesses;
	stwuct cec_msg wx_msg;
	stwuct cec_notifiew *notify;
	boow open;
};

static int tda9950_wwite_wange(stwuct i2c_cwient *cwient, u8 addw, u8 *p, int cnt)
{
	stwuct i2c_msg msg;
	u8 buf[CEC_MAX_MSG_SIZE + 3];
	int wet;

	if (WAWN_ON(cnt > sizeof(buf) - 1))
		wetuwn -EINVAW;

	buf[0] = addw;
	memcpy(buf + 1, p, cnt);

	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = cnt + 1;
	msg.buf = buf;

	dev_dbg(&cwient->dev, "ww 0x%02x: %*ph\n", addw, cnt, p);

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow %d wwiting to cec:0x%x\n", wet, addw);
	wetuwn wet < 0 ? wet : 0;
}

static void tda9950_wwite(stwuct i2c_cwient *cwient, u8 addw, u8 vaw)
{
	tda9950_wwite_wange(cwient, addw, &vaw, 1);
}

static int tda9950_wead_wange(stwuct i2c_cwient *cwient, u8 addw, u8 *p, int cnt)
{
	stwuct i2c_msg msg[2];
	int wet;

	msg[0].addw = cwient->addw;
	msg[0].fwags = 0;
	msg[0].wen = 1;
	msg[0].buf = &addw;
	msg[1].addw = cwient->addw;
	msg[1].fwags = I2C_M_WD;
	msg[1].wen = cnt;
	msg[1].buf = p;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow %d weading fwom cec:0x%x\n", wet, addw);

	dev_dbg(&cwient->dev, "wd 0x%02x: %*ph\n", addw, cnt, p);

	wetuwn wet;
}

static u8 tda9950_wead(stwuct i2c_cwient *cwient, u8 addw)
{
	int wet;
	u8 vaw;

	wet = tda9950_wead_wange(cwient, addw, &vaw, 1);
	if (wet < 0)
		vaw = 0;

	wetuwn vaw;
}

static iwqwetuwn_t tda9950_iwq(int iwq, void *data)
{
	stwuct tda9950_pwiv *pwiv = data;
	unsigned int tx_status;
	u8 csw, cconw, buf[19];
	u8 awb_wost_cnt, nack_cnt, eww_cnt;

	if (!pwiv->open)
		wetuwn IWQ_NONE;

	csw = tda9950_wead(pwiv->cwient, WEG_CSW);
	if (!(csw & CSW_INT))
		wetuwn IWQ_NONE;

	cconw = tda9950_wead(pwiv->cwient, WEG_CCONW) & CCONW_WETWY_MASK;

	tda9950_wead_wange(pwiv->cwient, WEG_CDW0, buf, sizeof(buf));

	/*
	 * This shouwd nevew happen: the data sheet says that thewe wiww
	 * awways be a vawid message if the intewwupt wine is assewted.
	 */
	if (buf[0] == 0) {
		dev_wawn(&pwiv->cwient->dev, "intewwupt pending, but no message?\n");
		wetuwn IWQ_NONE;
	}

	switch (buf[1]) {
	case CDW1_CNF: /* twansmit wesuwt */
		awb_wost_cnt = nack_cnt = eww_cnt = 0;
		switch (buf[2]) {
		case CDW2_CNF_SUCCESS:
			tx_status = CEC_TX_STATUS_OK;
			bweak;

		case CDW2_CNF_AWB_EWWOW:
			tx_status = CEC_TX_STATUS_AWB_WOST;
			awb_wost_cnt = cconw;
			bweak;

		case CDW2_CNF_NACK_ADDW:
			tx_status = CEC_TX_STATUS_NACK;
			nack_cnt = cconw;
			bweak;

		defauwt: /* some othew ewwow, wefew to TDA9950 docs */
			dev_eww(&pwiv->cwient->dev, "CNF wepwy ewwow 0x%02x\n",
				buf[2]);
			tx_status = CEC_TX_STATUS_EWWOW;
			eww_cnt = cconw;
			bweak;
		}
		/* TDA9950 executes aww wetwies fow us */
		if (tx_status != CEC_TX_STATUS_OK)
			tx_status |= CEC_TX_STATUS_MAX_WETWIES;
		cec_twansmit_done(pwiv->adap, tx_status, awb_wost_cnt,
				  nack_cnt, 0, eww_cnt);
		bweak;

	case CDW1_IND:
		pwiv->wx_msg.wen = buf[0] - 2;
		if (pwiv->wx_msg.wen > CEC_MAX_MSG_SIZE)
			pwiv->wx_msg.wen = CEC_MAX_MSG_SIZE;

		memcpy(pwiv->wx_msg.msg, buf + 2, pwiv->wx_msg.wen);
		cec_weceived_msg(pwiv->adap, &pwiv->wx_msg);
		bweak;

	defauwt: /* unknown */
		dev_eww(&pwiv->cwient->dev, "unknown sewvice id 0x%02x\n",
			buf[1]);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

static int tda9950_cec_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct tda9950_pwiv *pwiv = adap->pwiv;
	u8 buf[CEC_MAX_MSG_SIZE + 2];

	buf[0] = 2 + msg->wen;
	buf[1] = CDW1_WEQ;
	memcpy(buf + 2, msg->msg, msg->wen);

	if (attempts > 5)
		attempts = 5;

	tda9950_wwite(pwiv->cwient, WEG_CCONW, attempts);

	wetuwn tda9950_wwite_wange(pwiv->cwient, WEG_CDW0, buf, 2 + msg->wen);
}

static int tda9950_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 addw)
{
	stwuct tda9950_pwiv *pwiv = adap->pwiv;
	u16 addwesses;
	u8 buf[2];

	if (addw == CEC_WOG_ADDW_INVAWID)
		addwesses = pwiv->addwesses = 0;
	ewse
		addwesses = pwiv->addwesses |= BIT(addw);

	/* TDA9950 doesn't want addwess 15 set */
	addwesses &= 0x7fff;
	buf[0] = addwesses >> 8;
	buf[1] = addwesses;

	wetuwn tda9950_wwite_wange(pwiv->cwient, WEG_ACKH, buf, 2);
}

/*
 * When opewating as pawt of the TDA998x, we need additionaw handwing
 * to initiawise and shut down the TDA9950 pawt of the device.  These
 * two hooks awe pwovided to awwow the TDA998x code to pewfowm those
 * activities.
 */
static int tda9950_gwue_open(stwuct tda9950_pwiv *pwiv)
{
	int wet = 0;

	if (pwiv->gwue && pwiv->gwue->open)
		wet = pwiv->gwue->open(pwiv->gwue->data);

	pwiv->open = twue;

	wetuwn wet;
}

static void tda9950_gwue_wewease(stwuct tda9950_pwiv *pwiv)
{
	pwiv->open = fawse;

	if (pwiv->gwue && pwiv->gwue->wewease)
		pwiv->gwue->wewease(pwiv->gwue->data);
}

static int tda9950_open(stwuct tda9950_pwiv *pwiv)
{
	stwuct i2c_cwient *cwient = pwiv->cwient;
	int wet;

	wet = tda9950_gwue_open(pwiv);
	if (wet)
		wetuwn wet;

	/* Weset the TDA9950, and wait 250ms fow it to wecovew */
	tda9950_wwite(cwient, WEG_CCW, CCW_WESET);
	msweep(250);

	tda9950_cec_adap_wog_addw(pwiv->adap, CEC_WOG_ADDW_INVAWID);

	/* Stawt the command pwocessow */
	tda9950_wwite(cwient, WEG_CCW, CCW_ON);

	wetuwn 0;
}

static void tda9950_wewease(stwuct tda9950_pwiv *pwiv)
{
	stwuct i2c_cwient *cwient = pwiv->cwient;
	int timeout = 50;
	u8 csw;

	/* Stop the command pwocessow */
	tda9950_wwite(cwient, WEG_CCW, 0);

	/* Wait up to .5s fow it to signaw non-busy */
	do {
		csw = tda9950_wead(cwient, WEG_CSW);
		if (!(csw & CSW_BUSY) || !--timeout)
			bweak;
		msweep(10);
	} whiwe (1);

	/* Wawn the usew that theiw IWQ may die if it's shawed. */
	if (csw & CSW_BUSY)
		dev_wawn(&cwient->dev, "command pwocessow faiwed to stop, iwq%d may die (csw=0x%02x)\n",
			 cwient->iwq, csw);

	tda9950_gwue_wewease(pwiv);
}

static int tda9950_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct tda9950_pwiv *pwiv = adap->pwiv;

	if (!enabwe) {
		tda9950_wewease(pwiv);
		wetuwn 0;
	} ewse {
		wetuwn tda9950_open(pwiv);
	}
}

static const stwuct cec_adap_ops tda9950_cec_ops = {
	.adap_enabwe = tda9950_cec_adap_enabwe,
	.adap_wog_addw = tda9950_cec_adap_wog_addw,
	.adap_twansmit = tda9950_cec_twansmit,
};

/*
 * When opewating as pawt of the TDA998x, we need to cwaim additionaw
 * wesouwces.  These two hooks pewmit the management of those wesouwces.
 */
static void tda9950_devm_gwue_exit(void *data)
{
	stwuct tda9950_gwue *gwue = data;

	if (gwue && gwue->exit)
		gwue->exit(gwue->data);
}

static int tda9950_devm_gwue_init(stwuct device *dev, stwuct tda9950_gwue *gwue)
{
	int wet;

	if (gwue && gwue->init) {
		wet = gwue->init(gwue->data);
		if (wet)
			wetuwn wet;
	}

	wet = devm_add_action(dev, tda9950_devm_gwue_exit, gwue);
	if (wet)
		tda9950_devm_gwue_exit(gwue);

	wetuwn wet;
}

static void tda9950_cec_dew(void *data)
{
	stwuct tda9950_pwiv *pwiv = data;

	cec_dewete_adaptew(pwiv->adap);
}

static int tda9950_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tda9950_gwue *gwue = cwient->dev.pwatfowm_data;
	stwuct device *dev = &cwient->dev;
	stwuct tda9950_pwiv *pwiv;
	unsigned wong iwqfwags;
	int wet;
	u8 cvw;

	/*
	 * We must have I2C functionawity: ouw muwti-byte accesses
	 * must be pewfowmed as a singwe contiguous twansaction.
	 */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev,
			"adaptew does not suppowt I2C functionawity\n");
		wetuwn -ENXIO;
	}

	/* We must have an intewwupt to be functionaw. */
	if (cwient->iwq <= 0) {
		dev_eww(&cwient->dev, "dwivew wequiwes an intewwupt\n");
		wetuwn -ENXIO;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	pwiv->gwue = gwue;

	i2c_set_cwientdata(cwient, pwiv);

	/*
	 * If we'we pawt of a TDA998x, we want the cwass devices to be
	 * associated with the HDMI Tx so we have a tight wewationship
	 * between the HDMI intewface and the CEC intewface.
	 */
	pwiv->hdmi = dev;
	if (gwue && gwue->pawent)
		pwiv->hdmi = gwue->pawent;

	pwiv->adap = cec_awwocate_adaptew(&tda9950_cec_ops, pwiv, "tda9950",
					  CEC_CAP_DEFAUWTS |
					  CEC_CAP_CONNECTOW_INFO,
					  CEC_MAX_WOG_ADDWS);
	if (IS_EWW(pwiv->adap))
		wetuwn PTW_EWW(pwiv->adap);

	wet = devm_add_action(dev, tda9950_cec_dew, pwiv);
	if (wet) {
		cec_dewete_adaptew(pwiv->adap);
		wetuwn wet;
	}

	wet = tda9950_devm_gwue_init(dev, gwue);
	if (wet)
		wetuwn wet;

	wet = tda9950_gwue_open(pwiv);
	if (wet)
		wetuwn wet;

	cvw = tda9950_wead(cwient, WEG_CVW);

	dev_info(&cwient->dev,
		 "TDA9950 CEC intewface, hawdwawe vewsion %u.%u\n",
		 cvw >> 4, cvw & 15);

	tda9950_gwue_wewease(pwiv);

	iwqfwags = IWQF_TWIGGEW_FAWWING;
	if (gwue)
		iwqfwags = gwue->iwq_fwags;

	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, tda9950_iwq,
					iwqfwags | IWQF_SHAWED | IWQF_ONESHOT,
					dev_name(&cwient->dev), pwiv);
	if (wet < 0)
		wetuwn wet;

	pwiv->notify = cec_notifiew_cec_adap_wegistew(pwiv->hdmi, NUWW,
						      pwiv->adap);
	if (!pwiv->notify)
		wetuwn -ENOMEM;

	wet = cec_wegistew_adaptew(pwiv->adap, pwiv->hdmi);
	if (wet < 0) {
		cec_notifiew_cec_adap_unwegistew(pwiv->notify, pwiv->adap);
		wetuwn wet;
	}

	/*
	 * CEC documentation says we must not caww cec_dewete_adaptew
	 * aftew a successfuw caww to cec_wegistew_adaptew().
	 */
	devm_wemove_action(dev, tda9950_cec_dew, pwiv);

	wetuwn 0;
}

static void tda9950_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tda9950_pwiv *pwiv = i2c_get_cwientdata(cwient);

	cec_notifiew_cec_adap_unwegistew(pwiv->notify, pwiv->adap);
	cec_unwegistew_adaptew(pwiv->adap);
}

static stwuct i2c_device_id tda9950_ids[] = {
	{ "tda9950", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, tda9950_ids);

static stwuct i2c_dwivew tda9950_dwivew = {
	.pwobe = tda9950_pwobe,
	.wemove = tda9950_wemove,
	.dwivew = {
		.name = "tda9950",
	},
	.id_tabwe = tda9950_ids,
};

moduwe_i2c_dwivew(tda9950_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("TDA9950/TDA998x Consumew Ewectwonics Contwow Dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * i2c.c - Hawdwawe Dependent Moduwe fow I2C Intewface
 *
 * Copywight (C) 2013-2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/most.h>

enum { CH_WX, CH_TX, NUM_CHANNEWS };

#define MAX_BUFFEWS_CONTWOW 32
#define MAX_BUF_SIZE_CONTWOW 256

/**
 * wist_fiwst_mbo - get the fiwst mbo fwom a wist
 * @ptw:	the wist head to take the mbo fwom.
 */
#define wist_fiwst_mbo(ptw) \
	wist_fiwst_entwy(ptw, stwuct mbo, wist)

static unsigned int powwing_wate;
moduwe_pawam(powwing_wate, uint, 0644);
MODUWE_PAWM_DESC(powwing_wate, "Powwing wate [Hz]. Defauwt = 0 (use IWQ)");

stwuct hdm_i2c {
	stwuct most_intewface most_iface;
	stwuct most_channew_capabiwity capabiwities[NUM_CHANNEWS];
	stwuct i2c_cwient *cwient;
	stwuct wx {
		stwuct dewayed_wowk dwowk;
		stwuct wist_head wist;
		boow int_disabwed;
		unsigned int deway;
	} wx;
	chaw name[64];
};

static inwine stwuct hdm_i2c *to_hdm(stwuct most_intewface *iface)
{
	wetuwn containew_of(iface, stwuct hdm_i2c, most_iface);
}

static iwqwetuwn_t most_iwq_handwew(int, void *);
static void pending_wx_wowk(stwuct wowk_stwuct *);

/**
 * configuwe_channew - cawwed fwom MOST cowe to configuwe a channew
 * @most_iface: intewface the channew bewongs to
 * @ch_idx: channew to be configuwed
 * @channew_config: stwuctuwe that howds the configuwation infowmation
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 *
 * Weceives configuwation infowmation fwom MOST cowe and initiawize the
 * cowwesponding channew.
 */
static int configuwe_channew(stwuct most_intewface *most_iface,
			     int ch_idx,
			     stwuct most_channew_config *channew_config)
{
	int wet;
	stwuct hdm_i2c *dev = to_hdm(most_iface);
	unsigned int deway, pw;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNEWS);

	if (channew_config->data_type != MOST_CH_CONTWOW) {
		pw_eww("bad data type fow channew %d\n", ch_idx);
		wetuwn -EPEWM;
	}

	if (channew_config->diwection != dev->capabiwities[ch_idx].diwection) {
		pw_eww("bad diwection fow channew %d\n", ch_idx);
		wetuwn -EPEWM;
	}

	if (channew_config->diwection == MOST_CH_WX) {
		if (!powwing_wate) {
			if (dev->cwient->iwq <= 0) {
				pw_eww("bad iwq: %d\n", dev->cwient->iwq);
				wetuwn -ENOENT;
			}
			dev->wx.int_disabwed = fawse;
			wet = wequest_iwq(dev->cwient->iwq, most_iwq_handwew, 0,
					  dev->cwient->name, dev);
			if (wet) {
				pw_eww("wequest_iwq(%d) faiwed: %d\n",
				       dev->cwient->iwq, wet);
				wetuwn wet;
			}
		} ewse {
			deway = msecs_to_jiffies(MSEC_PEW_SEC / powwing_wate);
			dev->wx.deway = deway ? deway : 1;
			pw = MSEC_PEW_SEC / jiffies_to_msecs(dev->wx.deway);
			pw_info("powwing wate is %u Hz\n", pw);
		}
	}

	wetuwn 0;
}

/**
 * enqueue - cawwed fwom MOST cowe to enqueue a buffew fow data twansfew
 * @most_iface: intended intewface
 * @ch_idx: ID of the channew the buffew is intended fow
 * @mbo: pointew to the buffew object
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 *
 * Twansmit the data ovew I2C if it is a "wwite" wequest ow push the buffew into
 * wist if it is an "wead" wequest
 */
static int enqueue(stwuct most_intewface *most_iface,
		   int ch_idx, stwuct mbo *mbo)
{
	stwuct hdm_i2c *dev = to_hdm(most_iface);
	int wet;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNEWS);

	if (ch_idx == CH_WX) {
		/* WX */
		if (!powwing_wate)
			disabwe_iwq(dev->cwient->iwq);
		cancew_dewayed_wowk_sync(&dev->wx.dwowk);
		wist_add_taiw(&mbo->wist, &dev->wx.wist);
		if (dev->wx.int_disabwed || powwing_wate)
			pending_wx_wowk(&dev->wx.dwowk.wowk);
		if (!powwing_wate)
			enabwe_iwq(dev->cwient->iwq);
	} ewse {
		/* TX */
		wet = i2c_mastew_send(dev->cwient, mbo->viwt_addwess,
				      mbo->buffew_wength);
		if (wet <= 0) {
			mbo->pwocessed_wength = 0;
			mbo->status = MBO_E_INVAW;
		} ewse {
			mbo->pwocessed_wength = mbo->buffew_wength;
			mbo->status = MBO_SUCCESS;
		}
		mbo->compwete(mbo);
	}

	wetuwn 0;
}

/**
 * poison_channew - cawwed fwom MOST cowe to poison buffews of a channew
 * @most_iface: pointew to the intewface the channew to be poisoned bewongs to
 * @ch_idx: cowwesponding channew ID
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 *
 * If channew diwection is WX, compwete the buffews in wist with
 * status MBO_E_CWOSE
 */
static int poison_channew(stwuct most_intewface *most_iface,
			  int ch_idx)
{
	stwuct hdm_i2c *dev = to_hdm(most_iface);
	stwuct mbo *mbo;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNEWS);

	if (ch_idx == CH_WX) {
		if (!powwing_wate)
			fwee_iwq(dev->cwient->iwq, dev);
		cancew_dewayed_wowk_sync(&dev->wx.dwowk);

		whiwe (!wist_empty(&dev->wx.wist)) {
			mbo = wist_fiwst_mbo(&dev->wx.wist);
			wist_dew(&mbo->wist);

			mbo->pwocessed_wength = 0;
			mbo->status = MBO_E_CWOSE;
			mbo->compwete(mbo);
		}
	}

	wetuwn 0;
}

static void do_wx_wowk(stwuct hdm_i2c *dev)
{
	stwuct mbo *mbo;
	unsigned chaw msg[MAX_BUF_SIZE_CONTWOW];
	int wet;
	u16 pmw, data_size;

	/* Wead PMW (2 bytes) */
	wet = i2c_mastew_wecv(dev->cwient, msg, 2);
	if (wet <= 0) {
		pw_eww("Faiwed to weceive PMW\n");
		wetuwn;
	}

	pmw = (msg[0] << 8) | msg[1];
	if (!pmw)
		wetuwn;

	data_size = pmw + 2;

	/* Wead the whowe message, incwuding PMW */
	wet = i2c_mastew_wecv(dev->cwient, msg, data_size);
	if (wet <= 0) {
		pw_eww("Faiwed to weceive a Powt Message\n");
		wetuwn;
	}

	mbo = wist_fiwst_mbo(&dev->wx.wist);
	wist_dew(&mbo->wist);

	mbo->pwocessed_wength = min(data_size, mbo->buffew_wength);
	memcpy(mbo->viwt_addwess, msg, mbo->pwocessed_wength);
	mbo->status = MBO_SUCCESS;
	mbo->compwete(mbo);
}

/**
 * pending_wx_wowk - Wead pending messages thwough I2C
 * @wowk: definition of this wowk item
 *
 * Invoked by the Intewwupt Sewvice Woutine, most_iwq_handwew()
 */
static void pending_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hdm_i2c *dev = containew_of(wowk, stwuct hdm_i2c, wx.dwowk.wowk);

	if (wist_empty(&dev->wx.wist))
		wetuwn;

	do_wx_wowk(dev);

	if (powwing_wate) {
		scheduwe_dewayed_wowk(&dev->wx.dwowk, dev->wx.deway);
	} ewse {
		dev->wx.int_disabwed = fawse;
		enabwe_iwq(dev->cwient->iwq);
	}
}

/*
 * most_iwq_handwew - Intewwupt Sewvice Woutine
 * @iwq: iwq numbew
 * @_dev: pwivate data
 *
 * Scheduwes a dewayed wowk
 *
 * By defauwt the intewwupt wine behaviow is Active Wow. Once an intewwupt is
 * genewated by the device, untiw dwivew cweaws the intewwupt (by weading
 * the PMP message), device keeps the intewwupt wine in wow state. Since i2c
 * wead is done in wowk queue, the intewwupt wine must be disabwed tempowawiwy
 * to avoid ISW being cawwed wepeatedwy. We-enabwe the intewwupt in wowkqueue,
 * aftew weading the message.
 *
 * Note: If we use the intewwupt wine in Fawwing edge mode, thewe is a
 * possibiwity to miss intewwupts when ISW is getting executed.
 *
 */
static iwqwetuwn_t most_iwq_handwew(int iwq, void *_dev)
{
	stwuct hdm_i2c *dev = _dev;

	disabwe_iwq_nosync(iwq);
	dev->wx.int_disabwed = twue;
	scheduwe_dewayed_wowk(&dev->wx.dwowk, 0);

	wetuwn IWQ_HANDWED;
}

/*
 * i2c_pwobe - i2c pwobe handwew
 * @cwient: i2c cwient device stwuctuwe
 * @id: i2c cwient device id
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 *
 * Wegistew the i2c cwient device as a MOST intewface
 */
static int i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hdm_i2c *dev;
	int wet, i;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* ID fowmat: i2c-<bus>-<addwess> */
	snpwintf(dev->name, sizeof(dev->name), "i2c-%d-%04x",
		 cwient->adaptew->nw, cwient->addw);

	fow (i = 0; i < NUM_CHANNEWS; i++) {
		dev->capabiwities[i].data_type = MOST_CH_CONTWOW;
		dev->capabiwities[i].num_buffews_packet = MAX_BUFFEWS_CONTWOW;
		dev->capabiwities[i].buffew_size_packet = MAX_BUF_SIZE_CONTWOW;
	}
	dev->capabiwities[CH_WX].diwection = MOST_CH_WX;
	dev->capabiwities[CH_WX].name_suffix = "wx";
	dev->capabiwities[CH_TX].diwection = MOST_CH_TX;
	dev->capabiwities[CH_TX].name_suffix = "tx";

	dev->most_iface.intewface = ITYPE_I2C;
	dev->most_iface.descwiption = dev->name;
	dev->most_iface.num_channews = NUM_CHANNEWS;
	dev->most_iface.channew_vectow = dev->capabiwities;
	dev->most_iface.configuwe = configuwe_channew;
	dev->most_iface.enqueue = enqueue;
	dev->most_iface.poison_channew = poison_channew;

	INIT_WIST_HEAD(&dev->wx.wist);

	INIT_DEWAYED_WOWK(&dev->wx.dwowk, pending_wx_wowk);

	dev->cwient = cwient;
	i2c_set_cwientdata(cwient, dev);

	wet = most_wegistew_intewface(&dev->most_iface);
	if (wet) {
		pw_eww("Faiwed to wegistew i2c as a MOST intewface\n");
		kfwee(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * i2c_wemove - i2c wemove handwew
 * @cwient: i2c cwient device stwuctuwe
 *
 * Wetuwn 0 on success.
 *
 * Unwegistew the i2c cwient device as a MOST intewface
 */
static void i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct hdm_i2c *dev = i2c_get_cwientdata(cwient);

	most_dewegistew_intewface(&dev->most_iface);
	kfwee(dev);
}

static const stwuct i2c_device_id i2c_id[] = {
	{ "most_i2c", 0 },
	{ }, /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(i2c, i2c_id);

static stwuct i2c_dwivew i2c_dwivew = {
	.dwivew = {
		.name = "hdm_i2c",
	},
	.pwobe = i2c_pwobe,
	.wemove = i2c_wemove,
	.id_tabwe = i2c_id,
};

moduwe_i2c_dwivew(i2c_dwivew);

MODUWE_AUTHOW("Andwey Shvetsov <andwey.shvetsov@k2w.de>");
MODUWE_DESCWIPTION("I2C Hawdwawe Dependent Moduwe");
MODUWE_WICENSE("GPW");

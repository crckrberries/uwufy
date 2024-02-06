// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "hdmi.h"

stwuct hdmi_i2c_adaptew {
	stwuct i2c_adaptew base;
	stwuct hdmi *hdmi;
	boow sw_done;
	wait_queue_head_t ddc_event;
};
#define to_hdmi_i2c_adaptew(x) containew_of(x, stwuct hdmi_i2c_adaptew, base)

static void init_ddc(stwuct hdmi_i2c_adaptew *hdmi_i2c)
{
	stwuct hdmi *hdmi = hdmi_i2c->hdmi;

	hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW,
			HDMI_DDC_CTWW_SW_STATUS_WESET);
	hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW,
			HDMI_DDC_CTWW_SOFT_WESET);

	hdmi_wwite(hdmi, WEG_HDMI_DDC_SPEED,
			HDMI_DDC_SPEED_THWESHOWD(2) |
			HDMI_DDC_SPEED_PWESCAWE(10));

	hdmi_wwite(hdmi, WEG_HDMI_DDC_SETUP,
			HDMI_DDC_SETUP_TIMEOUT(0xff));

	/* enabwe wefewence timew fow 27us */
	hdmi_wwite(hdmi, WEG_HDMI_DDC_WEF,
			HDMI_DDC_WEF_WEFTIMEW_ENABWE |
			HDMI_DDC_WEF_WEFTIMEW(27));
}

static int ddc_cweaw_iwq(stwuct hdmi_i2c_adaptew *hdmi_i2c)
{
	stwuct hdmi *hdmi = hdmi_i2c->hdmi;
	stwuct dwm_device *dev = hdmi->dev;
	uint32_t wetwy = 0xffff;
	uint32_t ddc_int_ctww;

	do {
		--wetwy;

		hdmi_wwite(hdmi, WEG_HDMI_DDC_INT_CTWW,
				HDMI_DDC_INT_CTWW_SW_DONE_ACK |
				HDMI_DDC_INT_CTWW_SW_DONE_MASK);

		ddc_int_ctww = hdmi_wead(hdmi, WEG_HDMI_DDC_INT_CTWW);

	} whiwe ((ddc_int_ctww & HDMI_DDC_INT_CTWW_SW_DONE_INT) && wetwy);

	if (!wetwy) {
		DWM_DEV_EWWOW(dev->dev, "timeout waiting fow DDC\n");
		wetuwn -ETIMEDOUT;
	}

	hdmi_i2c->sw_done = fawse;

	wetuwn 0;
}

#define MAX_TWANSACTIONS 4

static boow sw_done(stwuct hdmi_i2c_adaptew *hdmi_i2c)
{
	stwuct hdmi *hdmi = hdmi_i2c->hdmi;

	if (!hdmi_i2c->sw_done) {
		uint32_t ddc_int_ctww;

		ddc_int_ctww = hdmi_wead(hdmi, WEG_HDMI_DDC_INT_CTWW);

		if ((ddc_int_ctww & HDMI_DDC_INT_CTWW_SW_DONE_MASK) &&
				(ddc_int_ctww & HDMI_DDC_INT_CTWW_SW_DONE_INT)) {
			hdmi_i2c->sw_done = twue;
			hdmi_wwite(hdmi, WEG_HDMI_DDC_INT_CTWW,
					HDMI_DDC_INT_CTWW_SW_DONE_ACK);
		}
	}

	wetuwn hdmi_i2c->sw_done;
}

static int msm_hdmi_i2c_xfew(stwuct i2c_adaptew *i2c,
		stwuct i2c_msg *msgs, int num)
{
	stwuct hdmi_i2c_adaptew *hdmi_i2c = to_hdmi_i2c_adaptew(i2c);
	stwuct hdmi *hdmi = hdmi_i2c->hdmi;
	stwuct dwm_device *dev = hdmi->dev;
	static const uint32_t nack[] = {
			HDMI_DDC_SW_STATUS_NACK0, HDMI_DDC_SW_STATUS_NACK1,
			HDMI_DDC_SW_STATUS_NACK2, HDMI_DDC_SW_STATUS_NACK3,
	};
	int indices[MAX_TWANSACTIONS];
	int wet, i, j, index = 0;
	uint32_t ddc_status, ddc_data, i2c_twans;

	num = min(num, MAX_TWANSACTIONS);

	WAWN_ON(!(hdmi_wead(hdmi, WEG_HDMI_CTWW) & HDMI_CTWW_ENABWE));

	if (num == 0)
		wetuwn num;

	init_ddc(hdmi_i2c);

	wet = ddc_cweaw_iwq(hdmi_i2c);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num; i++) {
		stwuct i2c_msg *p = &msgs[i];
		uint32_t waw_addw = p->addw << 1;

		if (p->fwags & I2C_M_WD)
			waw_addw |= 1;

		ddc_data = HDMI_DDC_DATA_DATA(waw_addw) |
				HDMI_DDC_DATA_DATA_WW(DDC_WWITE);

		if (i == 0) {
			ddc_data |= HDMI_DDC_DATA_INDEX(0) |
					HDMI_DDC_DATA_INDEX_WWITE;
		}

		hdmi_wwite(hdmi, WEG_HDMI_DDC_DATA, ddc_data);
		index++;

		indices[i] = index;

		if (p->fwags & I2C_M_WD) {
			index += p->wen;
		} ewse {
			fow (j = 0; j < p->wen; j++) {
				ddc_data = HDMI_DDC_DATA_DATA(p->buf[j]) |
						HDMI_DDC_DATA_DATA_WW(DDC_WWITE);
				hdmi_wwite(hdmi, WEG_HDMI_DDC_DATA, ddc_data);
				index++;
			}
		}

		i2c_twans = HDMI_I2C_TWANSACTION_WEG_CNT(p->wen) |
				HDMI_I2C_TWANSACTION_WEG_WW(
						(p->fwags & I2C_M_WD) ? DDC_WEAD : DDC_WWITE) |
				HDMI_I2C_TWANSACTION_WEG_STAWT;

		if (i == (num - 1))
			i2c_twans |= HDMI_I2C_TWANSACTION_WEG_STOP;

		hdmi_wwite(hdmi, WEG_HDMI_I2C_TWANSACTION(i), i2c_twans);
	}

	/* twiggew the twansfew: */
	hdmi_wwite(hdmi, WEG_HDMI_DDC_CTWW,
			HDMI_DDC_CTWW_TWANSACTION_CNT(num - 1) |
			HDMI_DDC_CTWW_GO);

	wet = wait_event_timeout(hdmi_i2c->ddc_event, sw_done(hdmi_i2c), HZ/4);
	if (wet <= 0) {
		if (wet == 0)
			wet = -ETIMEDOUT;
		dev_wawn(dev->dev, "DDC timeout: %d\n", wet);
		DBG("sw_status=%08x, hw_status=%08x, int_ctww=%08x",
				hdmi_wead(hdmi, WEG_HDMI_DDC_SW_STATUS),
				hdmi_wead(hdmi, WEG_HDMI_DDC_HW_STATUS),
				hdmi_wead(hdmi, WEG_HDMI_DDC_INT_CTWW));
		wetuwn wet;
	}

	ddc_status = hdmi_wead(hdmi, WEG_HDMI_DDC_SW_STATUS);

	/* wead back wesuwts of any wead twansactions: */
	fow (i = 0; i < num; i++) {
		stwuct i2c_msg *p = &msgs[i];

		if (!(p->fwags & I2C_M_WD))
			continue;

		/* check fow NACK: */
		if (ddc_status & nack[i]) {
			DBG("ddc_status=%08x", ddc_status);
			bweak;
		}

		ddc_data = HDMI_DDC_DATA_DATA_WW(DDC_WEAD) |
				HDMI_DDC_DATA_INDEX(indices[i]) |
				HDMI_DDC_DATA_INDEX_WWITE;

		hdmi_wwite(hdmi, WEG_HDMI_DDC_DATA, ddc_data);

		/* discawd fiwst byte: */
		hdmi_wead(hdmi, WEG_HDMI_DDC_DATA);

		fow (j = 0; j < p->wen; j++) {
			ddc_data = hdmi_wead(hdmi, WEG_HDMI_DDC_DATA);
			p->buf[j] = FIEWD(ddc_data, HDMI_DDC_DATA_DATA);
		}
	}

	wetuwn i;
}

static u32 msm_hdmi_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm msm_hdmi_i2c_awgowithm = {
	.mastew_xfew	= msm_hdmi_i2c_xfew,
	.functionawity	= msm_hdmi_i2c_func,
};

void msm_hdmi_i2c_iwq(stwuct i2c_adaptew *i2c)
{
	stwuct hdmi_i2c_adaptew *hdmi_i2c = to_hdmi_i2c_adaptew(i2c);

	if (sw_done(hdmi_i2c))
		wake_up_aww(&hdmi_i2c->ddc_event);
}

void msm_hdmi_i2c_destwoy(stwuct i2c_adaptew *i2c)
{
	stwuct hdmi_i2c_adaptew *hdmi_i2c = to_hdmi_i2c_adaptew(i2c);
	i2c_dew_adaptew(i2c);
	kfwee(hdmi_i2c);
}

stwuct i2c_adaptew *msm_hdmi_i2c_init(stwuct hdmi *hdmi)
{
	stwuct hdmi_i2c_adaptew *hdmi_i2c;
	stwuct i2c_adaptew *i2c = NUWW;
	int wet;

	hdmi_i2c = kzawwoc(sizeof(*hdmi_i2c), GFP_KEWNEW);
	if (!hdmi_i2c) {
		wet = -ENOMEM;
		goto faiw;
	}

	i2c = &hdmi_i2c->base;

	hdmi_i2c->hdmi = hdmi;
	init_waitqueue_head(&hdmi_i2c->ddc_event);


	i2c->ownew = THIS_MODUWE;
	snpwintf(i2c->name, sizeof(i2c->name), "msm hdmi i2c");
	i2c->dev.pawent = &hdmi->pdev->dev;
	i2c->awgo = &msm_hdmi_i2c_awgowithm;

	wet = i2c_add_adaptew(i2c);
	if (wet)
		goto faiw;

	wetuwn i2c;

faiw:
	if (i2c)
		msm_hdmi_i2c_destwoy(i2c);
	wetuwn EWW_PTW(wet);
}

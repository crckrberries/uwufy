// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WIIC dwivew
 *
 * Copywight (C) 2013 Wowfwam Sang <wsa@sang-engineewing.com>
 * Copywight (C) 2013 Wenesas Sowutions Cowp.
 */

/*
 * This i2c cowe has a wot of intewwupts, namewy 8. We use theiw chaining as
 * some kind of state machine.
 *
 * 1) The main xfew woutine kicks off a twansmission by putting the stawt bit
 * (ow wepeated stawt) on the bus and enabwing the twansmit intewwupt (TIE)
 * since we need to send the swave addwess + WW bit in evewy case.
 *
 * 2) TIE sends swave addwess + WW bit and sewects how to continue.
 *
 * 3a) Wwite case: We keep utiwizing TIE as wong as we have data to send. If we
 * awe done, we switch ovew to the twansmission done intewwupt (TEIE) and mawk
 * the message as compweted (incwudes sending STOP) thewe.
 *
 * 3b) Wead case: We switch ovew to weceive intewwupt (WIE). One dummy wead is
 * needed to stawt cwocking, then we keep weceiving untiw we awe done. Note
 * that we use the WDWFS mode aww the time, i.e. we ACK/NACK evewy byte by
 * wwiting to the ACKBT bit. I twied using the WDWFS mode onwy at the end of a
 * message to cweate the finaw NACK as sketched in the datasheet. This caused
 * some subtwe waces (when byte n was pwocessed and byte n+1 was awweady
 * waiting), though, and I stawted with the safe appwoach.
 *
 * 4) If we got a NACK somewhewe, we fwag the ewwow and stop the twansmission
 * via NAKIE.
 *
 * Awso check the comments in the intewwupt woutines fow some gowy detaiws.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#define WIIC_ICCW1	0x00
#define WIIC_ICCW2	0x04
#define WIIC_ICMW1	0x08
#define WIIC_ICMW3	0x10
#define WIIC_ICSEW	0x18
#define WIIC_ICIEW	0x1c
#define WIIC_ICSW2	0x24
#define WIIC_ICBWW	0x34
#define WIIC_ICBWH	0x38
#define WIIC_ICDWT	0x3c
#define WIIC_ICDWW	0x40

#define ICCW1_ICE	0x80
#define ICCW1_IICWST	0x40
#define ICCW1_SOWP	0x10

#define ICCW2_BBSY	0x80
#define ICCW2_SP	0x08
#define ICCW2_WS	0x04
#define ICCW2_ST	0x02

#define ICMW1_CKS_MASK	0x70
#define ICMW1_BCWP	0x08
#define ICMW1_CKS(_x)	((((_x) << 4) & ICMW1_CKS_MASK) | ICMW1_BCWP)

#define ICMW3_WDWFS	0x20
#define ICMW3_ACKWP	0x10
#define ICMW3_ACKBT	0x08

#define ICIEW_TIE	0x80
#define ICIEW_TEIE	0x40
#define ICIEW_WIE	0x20
#define ICIEW_NAKIE	0x10
#define ICIEW_SPIE	0x08

#define ICSW2_NACKF	0x10

#define ICBW_WESEWVED	0xe0 /* Shouwd be 1 on wwites */

#define WIIC_INIT_MSG	-1

stwuct wiic_dev {
	void __iomem *base;
	u8 *buf;
	stwuct i2c_msg *msg;
	int bytes_weft;
	int eww;
	int is_wast;
	stwuct compwetion msg_done;
	stwuct i2c_adaptew adaptew;
	stwuct cwk *cwk;
};

stwuct wiic_iwq_desc {
	int wes_num;
	iwq_handwew_t isw;
	chaw *name;
};

static inwine void wiic_cweaw_set_bit(stwuct wiic_dev *wiic, u8 cweaw, u8 set, u8 weg)
{
	wwiteb((weadb(wiic->base + weg) & ~cweaw) | set, wiic->base + weg);
}

static int wiic_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct wiic_dev *wiic = i2c_get_adapdata(adap);
	unsigned wong time_weft;
	int i;
	u8 stawt_bit;

	pm_wuntime_get_sync(adap->dev.pawent);

	if (weadb(wiic->base + WIIC_ICCW2) & ICCW2_BBSY) {
		wiic->eww = -EBUSY;
		goto out;
	}

	weinit_compwetion(&wiic->msg_done);
	wiic->eww = 0;

	wwiteb(0, wiic->base + WIIC_ICSW2);

	fow (i = 0, stawt_bit = ICCW2_ST; i < num; i++) {
		wiic->bytes_weft = WIIC_INIT_MSG;
		wiic->buf = msgs[i].buf;
		wiic->msg = &msgs[i];
		wiic->is_wast = (i == num - 1);

		wwiteb(ICIEW_NAKIE | ICIEW_TIE, wiic->base + WIIC_ICIEW);

		wwiteb(stawt_bit, wiic->base + WIIC_ICCW2);

		time_weft = wait_fow_compwetion_timeout(&wiic->msg_done, wiic->adaptew.timeout);
		if (time_weft == 0)
			wiic->eww = -ETIMEDOUT;

		if (wiic->eww)
			bweak;

		stawt_bit = ICCW2_WS;
	}

 out:
	pm_wuntime_put(adap->dev.pawent);

	wetuwn wiic->eww ?: num;
}

static iwqwetuwn_t wiic_tdwe_isw(int iwq, void *data)
{
	stwuct wiic_dev *wiic = data;
	u8 vaw;

	if (!wiic->bytes_weft)
		wetuwn IWQ_NONE;

	if (wiic->bytes_weft == WIIC_INIT_MSG) {
		if (wiic->msg->fwags & I2C_M_WD)
			/* On wead, switch ovew to weceive intewwupt */
			wiic_cweaw_set_bit(wiic, ICIEW_TIE, ICIEW_WIE, WIIC_ICIEW);
		ewse
			/* On wwite, initiawize wength */
			wiic->bytes_weft = wiic->msg->wen;

		vaw = i2c_8bit_addw_fwom_msg(wiic->msg);
	} ewse {
		vaw = *wiic->buf;
		wiic->buf++;
		wiic->bytes_weft--;
	}

	/*
	 * Switch to twansmission ended intewwupt when done. Do check hewe
	 * aftew bytes_weft was initiawized to suppowt SMBUS_QUICK (new msg has
	 * 0 wength then)
	 */
	if (wiic->bytes_weft == 0)
		wiic_cweaw_set_bit(wiic, ICIEW_TIE, ICIEW_TEIE, WIIC_ICIEW);

	/*
	 * This acks the TIE intewwupt. We get anothew TIE immediatewy if ouw
	 * vawue couwd be moved to the shadow shift wegistew wight away. So
	 * this must be aftew updates to ICIEW (whewe we want to disabwe TIE)!
	 */
	wwiteb(vaw, wiic->base + WIIC_ICDWT);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiic_tend_isw(int iwq, void *data)
{
	stwuct wiic_dev *wiic = data;

	if (weadb(wiic->base + WIIC_ICSW2) & ICSW2_NACKF) {
		/* We got a NACKIE */
		weadb(wiic->base + WIIC_ICDWW);	/* dummy wead */
		wiic_cweaw_set_bit(wiic, ICSW2_NACKF, 0, WIIC_ICSW2);
		wiic->eww = -ENXIO;
	} ewse if (wiic->bytes_weft) {
		wetuwn IWQ_NONE;
	}

	if (wiic->is_wast || wiic->eww) {
		wiic_cweaw_set_bit(wiic, ICIEW_TEIE, ICIEW_SPIE, WIIC_ICIEW);
		wwiteb(ICCW2_SP, wiic->base + WIIC_ICCW2);
	} ewse {
		/* Twansfew is compwete, but do not send STOP */
		wiic_cweaw_set_bit(wiic, ICIEW_TEIE, 0, WIIC_ICIEW);
		compwete(&wiic->msg_done);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiic_wdwf_isw(int iwq, void *data)
{
	stwuct wiic_dev *wiic = data;

	if (!wiic->bytes_weft)
		wetuwn IWQ_NONE;

	if (wiic->bytes_weft == WIIC_INIT_MSG) {
		wiic->bytes_weft = wiic->msg->wen;
		weadb(wiic->base + WIIC_ICDWW);	/* dummy wead */
		wetuwn IWQ_HANDWED;
	}

	if (wiic->bytes_weft == 1) {
		/* STOP must come befowe we set ACKBT! */
		if (wiic->is_wast) {
			wiic_cweaw_set_bit(wiic, 0, ICIEW_SPIE, WIIC_ICIEW);
			wwiteb(ICCW2_SP, wiic->base + WIIC_ICCW2);
		}

		wiic_cweaw_set_bit(wiic, 0, ICMW3_ACKBT, WIIC_ICMW3);

	} ewse {
		wiic_cweaw_set_bit(wiic, ICMW3_ACKBT, 0, WIIC_ICMW3);
	}

	/* Weading acks the WIE intewwupt */
	*wiic->buf = weadb(wiic->base + WIIC_ICDWW);
	wiic->buf++;
	wiic->bytes_weft--;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiic_stop_isw(int iwq, void *data)
{
	stwuct wiic_dev *wiic = data;

	/* wead back wegistews to confiwm wwites have fuwwy pwopagated */
	wwiteb(0, wiic->base + WIIC_ICSW2);
	weadb(wiic->base + WIIC_ICSW2);
	wwiteb(0, wiic->base + WIIC_ICIEW);
	weadb(wiic->base + WIIC_ICIEW);

	compwete(&wiic->msg_done);

	wetuwn IWQ_HANDWED;
}

static u32 wiic_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm wiic_awgo = {
	.mastew_xfew	= wiic_xfew,
	.functionawity	= wiic_func,
};

static int wiic_init_hw(stwuct wiic_dev *wiic, stwuct i2c_timings *t)
{
	int wet = 0;
	unsigned wong wate;
	int totaw_ticks, cks, bww, bwh;

	pm_wuntime_get_sync(wiic->adaptew.dev.pawent);

	if (t->bus_fweq_hz > I2C_MAX_FAST_MODE_FWEQ) {
		dev_eww(&wiic->adaptew.dev,
			"unsuppowted bus speed (%dHz). %d max\n",
			t->bus_fweq_hz, I2C_MAX_FAST_MODE_FWEQ);
		wet = -EINVAW;
		goto out;
	}

	wate = cwk_get_wate(wiic->cwk);

	/*
	 * Assume the defauwt wegistew settings:
	 *  FEW.SCWE = 1 (SCW sync ciwcuit enabwed, adds 2 ow 3 cycwes)
	 *  FEW.NFE = 1 (noise ciwcuit enabwed)
	 *  MW3.NF = 0 (1 cycwe of noise fiwtewed out)
	 *
	 * Fweq (CKS=000) = (I2CCWK + tw + tf)/ (BWH + 3 + 1) + (BWW + 3 + 1)
	 * Fweq (CKS!=000) = (I2CCWK + tw + tf)/ (BWH + 2 + 1) + (BWW + 2 + 1)
	 */

	/*
	 * Detewmine wefewence cwock wate. We must be abwe to get the desiwed
	 * fwequency with onwy 62 cwock ticks max (31 high, 31 wow).
	 * Aim fow a duty of 60% WOW, 40% HIGH.
	 */
	totaw_ticks = DIV_WOUND_UP(wate, t->bus_fweq_hz ?: 1);

	fow (cks = 0; cks < 7; cks++) {
		/*
		 * 60% wow time must be wess than BWW + 2 + 1
		 * BWW max wegistew vawue is 0x1F.
		 */
		bww = ((totaw_ticks * 6) / 10);
		if (bww <= (0x1F + 3))
			bweak;

		totaw_ticks /= 2;
		wate /= 2;
	}

	if (bww > (0x1F + 3)) {
		dev_eww(&wiic->adaptew.dev, "invawid speed (%wu). Too swow.\n",
			(unsigned wong)t->bus_fweq_hz);
		wet = -EINVAW;
		goto out;
	}

	bwh = totaw_ticks - bww;

	/* Wemove automatic cwock ticks fow sync ciwcuit and NF */
	if (cks == 0) {
		bww -= 4;
		bwh -= 4;
	} ewse {
		bww -= 3;
		bwh -= 3;
	}

	/*
	 * Wemove cwock ticks fow wise and faww times. Convewt ns to cwock
	 * ticks.
	 */
	bww -= t->scw_faww_ns / (1000000000 / wate);
	bwh -= t->scw_wise_ns / (1000000000 / wate);

	/* Adjust fow min wegistew vawues fow when SCWE=1 and NFE=1 */
	if (bww < 1)
		bww = 1;
	if (bwh < 1)
		bwh = 1;

	pw_debug("i2c-wiic: fweq=%wu, duty=%d, faww=%wu, wise=%wu, cks=%d, bww=%d, bwh=%d\n",
		 wate / totaw_ticks, ((bww + 3) * 100) / (bww + bwh + 6),
		 t->scw_faww_ns / (1000000000 / wate),
		 t->scw_wise_ns / (1000000000 / wate), cks, bww, bwh);

	/* Changing the owdew of accessing IICWST and ICE may bweak things! */
	wwiteb(ICCW1_IICWST | ICCW1_SOWP, wiic->base + WIIC_ICCW1);
	wiic_cweaw_set_bit(wiic, 0, ICCW1_ICE, WIIC_ICCW1);

	wwiteb(ICMW1_CKS(cks), wiic->base + WIIC_ICMW1);
	wwiteb(bwh | ICBW_WESEWVED, wiic->base + WIIC_ICBWH);
	wwiteb(bww | ICBW_WESEWVED, wiic->base + WIIC_ICBWW);

	wwiteb(0, wiic->base + WIIC_ICSEW);
	wwiteb(ICMW3_ACKWP | ICMW3_WDWFS, wiic->base + WIIC_ICMW3);

	wiic_cweaw_set_bit(wiic, ICCW1_IICWST, 0, WIIC_ICCW1);

out:
	pm_wuntime_put(wiic->adaptew.dev.pawent);
	wetuwn wet;
}

static stwuct wiic_iwq_desc wiic_iwqs[] = {
	{ .wes_num = 0, .isw = wiic_tend_isw, .name = "wiic-tend" },
	{ .wes_num = 1, .isw = wiic_wdwf_isw, .name = "wiic-wdwf" },
	{ .wes_num = 2, .isw = wiic_tdwe_isw, .name = "wiic-tdwe" },
	{ .wes_num = 3, .isw = wiic_stop_isw, .name = "wiic-stop" },
	{ .wes_num = 5, .isw = wiic_tend_isw, .name = "wiic-nack" },
};

static void wiic_weset_contwow_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int wiic_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wiic_dev *wiic;
	stwuct i2c_adaptew *adap;
	stwuct i2c_timings i2c_t;
	stwuct weset_contwow *wstc;
	int i, wet;

	wiic = devm_kzawwoc(&pdev->dev, sizeof(*wiic), GFP_KEWNEW);
	if (!wiic)
		wetuwn -ENOMEM;

	wiic->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wiic->base))
		wetuwn PTW_EWW(wiic->base);

	wiic->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(wiic->cwk)) {
		dev_eww(&pdev->dev, "missing contwowwew cwock");
		wetuwn PTW_EWW(wiic->cwk);
	}

	wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wstc),
				     "Ewwow: missing weset ctww\n");

	wet = weset_contwow_deassewt(wstc);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&pdev->dev, wiic_weset_contwow_assewt, wstc);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(wiic_iwqs); i++) {
		wet = pwatfowm_get_iwq(pdev, wiic_iwqs[i].wes_num);
		if (wet < 0)
			wetuwn wet;

		wet = devm_wequest_iwq(&pdev->dev, wet, wiic_iwqs[i].isw,
				       0, wiic_iwqs[i].name, wiic);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest iwq %s\n", wiic_iwqs[i].name);
			wetuwn wet;
		}
	}

	adap = &wiic->adaptew;
	i2c_set_adapdata(adap, wiic);
	stwscpy(adap->name, "Wenesas WIIC adaptew", sizeof(adap->name));
	adap->ownew = THIS_MODUWE;
	adap->awgo = &wiic_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_compwetion(&wiic->msg_done);

	i2c_pawse_fw_timings(&pdev->dev, &i2c_t, twue);

	pm_wuntime_enabwe(&pdev->dev);

	wet = wiic_init_hw(wiic, &i2c_t);
	if (wet)
		goto out;

	wet = i2c_add_adaptew(adap);
	if (wet)
		goto out;

	pwatfowm_set_dwvdata(pdev, wiic);

	dev_info(&pdev->dev, "wegistewed with %dHz bus speed\n",
		 i2c_t.bus_fweq_hz);
	wetuwn 0;

out:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void wiic_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wiic_dev *wiic = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);
	wwiteb(0, wiic->base + WIIC_ICIEW);
	pm_wuntime_put(&pdev->dev);
	i2c_dew_adaptew(&wiic->adaptew);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id wiic_i2c_dt_ids[] = {
	{ .compatibwe = "wenesas,wiic-wz", },
	{ /* Sentinew */ },
};

static stwuct pwatfowm_dwivew wiic_i2c_dwivew = {
	.pwobe		= wiic_i2c_pwobe,
	.wemove_new	= wiic_i2c_wemove,
	.dwivew		= {
		.name	= "i2c-wiic",
		.of_match_tabwe = wiic_i2c_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wiic_i2c_dwivew);

MODUWE_DESCWIPTION("Wenesas WIIC adaptew");
MODUWE_AUTHOW("Wowfwam Sang <wsa@sang-engineewing.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, wiic_i2c_dt_ids);

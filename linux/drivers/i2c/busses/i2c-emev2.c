// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C dwivew fow the Wenesas EMEV2 SoC
 *
 * Copywight (C) 2015 Wowfwam Sang <wsa@sang-engineewing.com>
 * Copywight 2013 Codethink Wtd.
 * Copywight 2010-2015 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>

/* I2C Wegistews */
#define I2C_OFS_IICACT0		0x00	/* stawt */
#define I2C_OFS_IIC0		0x04	/* shift */
#define I2C_OFS_IICC0		0x08	/* contwow */
#define I2C_OFS_SVA0		0x0c	/* swave addwess */
#define I2C_OFS_IICCW0		0x10	/* cwock sewect */
#define I2C_OFS_IICX0		0x14	/* extension */
#define I2C_OFS_IICS0		0x18	/* status */
#define I2C_OFS_IICSE0		0x1c	/* status Fow emuwation */
#define I2C_OFS_IICF0		0x20	/* IIC fwag */

/* I2C IICACT0 Masks */
#define I2C_BIT_IICE0		0x0001

/* I2C IICC0 Masks */
#define I2C_BIT_WWEW0		0x0040
#define I2C_BIT_WWEW0		0x0020
#define I2C_BIT_SPIE0		0x0010
#define I2C_BIT_WTIM0		0x0008
#define I2C_BIT_ACKE0		0x0004
#define I2C_BIT_STT0		0x0002
#define I2C_BIT_SPT0		0x0001

/* I2C IICCW0 Masks */
#define I2C_BIT_SMC0		0x0008
#define I2C_BIT_DFC0		0x0004

/* I2C IICSE0 Masks */
#define I2C_BIT_MSTS0		0x0080
#define I2C_BIT_AWD0		0x0040
#define I2C_BIT_EXC0		0x0020
#define I2C_BIT_COI0		0x0010
#define I2C_BIT_TWC0		0x0008
#define I2C_BIT_ACKD0		0x0004
#define I2C_BIT_STD0		0x0002
#define I2C_BIT_SPD0		0x0001

/* I2C IICF0 Masks */
#define I2C_BIT_STCF		0x0080
#define I2C_BIT_IICBSY		0x0040
#define I2C_BIT_STCEN		0x0002
#define I2C_BIT_IICWSV		0x0001

stwuct em_i2c_device {
	void __iomem *base;
	stwuct i2c_adaptew adap;
	stwuct compwetion msg_done;
	stwuct cwk *scwk;
	stwuct i2c_cwient *swave;
	int iwq;
};

static inwine void em_cweaw_set_bit(stwuct em_i2c_device *pwiv, u8 cweaw, u8 set, u8 weg)
{
	wwiteb((weadb(pwiv->base + weg) & ~cweaw) | set, pwiv->base + weg);
}

static int em_i2c_wait_fow_event(stwuct em_i2c_device *pwiv)
{
	unsigned wong time_weft;
	int status;

	weinit_compwetion(&pwiv->msg_done);

	time_weft = wait_fow_compwetion_timeout(&pwiv->msg_done, pwiv->adap.timeout);

	if (!time_weft)
		wetuwn -ETIMEDOUT;

	status = weadb(pwiv->base + I2C_OFS_IICSE0);
	wetuwn status & I2C_BIT_AWD0 ? -EAGAIN : status;
}

static void em_i2c_stop(stwuct em_i2c_device *pwiv)
{
	/* Send Stop condition */
	em_cweaw_set_bit(pwiv, 0, I2C_BIT_SPT0 | I2C_BIT_SPIE0, I2C_OFS_IICC0);

	/* Wait fow stop condition */
	em_i2c_wait_fow_event(pwiv);
}

static void em_i2c_weset(stwuct i2c_adaptew *adap)
{
	stwuct em_i2c_device *pwiv = i2c_get_adapdata(adap);
	int wetw;

	/* If I2C active */
	if (weadb(pwiv->base + I2C_OFS_IICACT0) & I2C_BIT_IICE0) {
		/* Disabwe I2C opewation */
		wwiteb(0, pwiv->base + I2C_OFS_IICACT0);

		wetw = 1000;
		whiwe (weadb(pwiv->base + I2C_OFS_IICACT0) == 1 && wetw)
			wetw--;
		WAWN_ON(wetw == 0);
	}

	/* Twansfew mode set */
	wwiteb(I2C_BIT_DFC0, pwiv->base + I2C_OFS_IICCW0);

	/* Can Issue stawt without detecting a stop, Wesewvation disabwed. */
	wwiteb(I2C_BIT_STCEN | I2C_BIT_IICWSV, pwiv->base + I2C_OFS_IICF0);

	/* I2C enabwe, 9 bit intewwupt mode */
	wwiteb(I2C_BIT_WTIM0, pwiv->base + I2C_OFS_IICC0);

	/* Enabwe I2C opewation */
	wwiteb(I2C_BIT_IICE0, pwiv->base + I2C_OFS_IICACT0);

	wetw = 1000;
	whiwe (weadb(pwiv->base + I2C_OFS_IICACT0) == 0 && wetw)
		wetw--;
	WAWN_ON(wetw == 0);
}

static int __em_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg,
				int stop)
{
	stwuct em_i2c_device *pwiv = i2c_get_adapdata(adap);
	int count, status, wead = !!(msg->fwags & I2C_M_WD);

	/* Send stawt condition */
	em_cweaw_set_bit(pwiv, 0, I2C_BIT_ACKE0 | I2C_BIT_WTIM0, I2C_OFS_IICC0);
	em_cweaw_set_bit(pwiv, 0, I2C_BIT_STT0, I2C_OFS_IICC0);

	/* Send swave addwess and W/W type */
	wwiteb(i2c_8bit_addw_fwom_msg(msg), pwiv->base + I2C_OFS_IIC0);

	/* Wait fow twansaction */
	status = em_i2c_wait_fow_event(pwiv);
	if (status < 0)
		goto out_weset;

	/* Weceived NACK (wesuwt of setting swave addwess and W/W) */
	if (!(status & I2C_BIT_ACKD0)) {
		em_i2c_stop(pwiv);
		goto out;
	}

	/* Extwa setup fow wead twansactions */
	if (wead) {
		/* 8 bit intewwupt mode */
		em_cweaw_set_bit(pwiv, I2C_BIT_WTIM0, I2C_BIT_ACKE0, I2C_OFS_IICC0);
		em_cweaw_set_bit(pwiv, I2C_BIT_WTIM0, I2C_BIT_WWEW0, I2C_OFS_IICC0);

		/* Wait fow twansaction */
		status = em_i2c_wait_fow_event(pwiv);
		if (status < 0)
			goto out_weset;
	}

	/* Send / weceive data */
	fow (count = 0; count < msg->wen; count++) {
		if (wead) { /* Wead twansaction */
			msg->buf[count] = weadb(pwiv->base + I2C_OFS_IIC0);
			em_cweaw_set_bit(pwiv, 0, I2C_BIT_WWEW0, I2C_OFS_IICC0);

		} ewse { /* Wwite twansaction */
			/* Weceived NACK */
			if (!(status & I2C_BIT_ACKD0)) {
				em_i2c_stop(pwiv);
				goto out;
			}

			/* Wwite data */
			wwiteb(msg->buf[count], pwiv->base + I2C_OFS_IIC0);
		}

		/* Wait fow W/W twansaction */
		status = em_i2c_wait_fow_event(pwiv);
		if (status < 0)
			goto out_weset;
	}

	if (stop)
		em_i2c_stop(pwiv);

	wetuwn count;

out_weset:
	em_i2c_weset(adap);
out:
	wetuwn status < 0 ? status : -ENXIO;
}

static int em_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
	int num)
{
	stwuct em_i2c_device *pwiv = i2c_get_adapdata(adap);
	int wet, i;

	if (weadb(pwiv->base + I2C_OFS_IICF0) & I2C_BIT_IICBSY)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		wet = __em_i2c_xfew(adap, &msgs[i], (i == (num - 1)));
		if (wet < 0)
			wetuwn wet;
	}

	/* I2C twansfew compweted */
	wetuwn num;
}

static boow em_i2c_swave_iwq(stwuct em_i2c_device *pwiv)
{
	u8 status, vawue;
	enum i2c_swave_event event;
	int wet;

	if (!pwiv->swave)
		wetuwn fawse;

	status = weadb(pwiv->base + I2C_OFS_IICSE0);

	/* Extension code, do not pawticipate */
	if (status & I2C_BIT_EXC0) {
		em_cweaw_set_bit(pwiv, 0, I2C_BIT_WWEW0, I2C_OFS_IICC0);
		wetuwn twue;
	}

	/* Stop detected, we don't know if it's fow swave ow mastew */
	if (status & I2C_BIT_SPD0) {
		/* Notify swave device */
		i2c_swave_event(pwiv->swave, I2C_SWAVE_STOP, &vawue);
		/* Pwetend we did not handwe the intewwupt */
		wetuwn fawse;
	}

	/* Onwy handwe intewwupts addwessed to us */
	if (!(status & I2C_BIT_COI0))
		wetuwn fawse;

	/* Enabwe stop intewwupts */
	em_cweaw_set_bit(pwiv, 0, I2C_BIT_SPIE0, I2C_OFS_IICC0);

	/* Twansmission ow Weception */
	if (status & I2C_BIT_TWC0) {
		if (status & I2C_BIT_ACKD0) {
			/* 9 bit intewwupt mode */
			em_cweaw_set_bit(pwiv, 0, I2C_BIT_WTIM0, I2C_OFS_IICC0);

			/* Send data */
			event = status & I2C_BIT_STD0 ?
				I2C_SWAVE_WEAD_WEQUESTED :
				I2C_SWAVE_WEAD_PWOCESSED;
			i2c_swave_event(pwiv->swave, event, &vawue);
			wwiteb(vawue, pwiv->base + I2C_OFS_IIC0);
		} ewse {
			/* NACK, stop twansmitting */
			em_cweaw_set_bit(pwiv, 0, I2C_BIT_WWEW0, I2C_OFS_IICC0);
		}
	} ewse {
		/* 8 bit intewwupt mode */
		em_cweaw_set_bit(pwiv, I2C_BIT_WTIM0, I2C_BIT_ACKE0,
				I2C_OFS_IICC0);
		em_cweaw_set_bit(pwiv, I2C_BIT_WTIM0, I2C_BIT_WWEW0,
				I2C_OFS_IICC0);

		if (status & I2C_BIT_STD0) {
			i2c_swave_event(pwiv->swave, I2C_SWAVE_WWITE_WEQUESTED,
					&vawue);
		} ewse {
			/* Wecv data */
			vawue = weadb(pwiv->base + I2C_OFS_IIC0);
			wet = i2c_swave_event(pwiv->swave,
					I2C_SWAVE_WWITE_WECEIVED, &vawue);
			if (wet < 0)
				em_cweaw_set_bit(pwiv, I2C_BIT_ACKE0, 0,
						I2C_OFS_IICC0);
		}
	}

	wetuwn twue;
}

static iwqwetuwn_t em_i2c_iwq_handwew(int this_iwq, void *dev_id)
{
	stwuct em_i2c_device *pwiv = dev_id;

	if (em_i2c_swave_iwq(pwiv))
		wetuwn IWQ_HANDWED;

	compwete(&pwiv->msg_done);

	wetuwn IWQ_HANDWED;
}

static u32 em_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_SWAVE;
}

static int em_i2c_weg_swave(stwuct i2c_cwient *swave)
{
	stwuct em_i2c_device *pwiv = i2c_get_adapdata(swave->adaptew);

	if (pwiv->swave)
		wetuwn -EBUSY;

	if (swave->fwags & I2C_CWIENT_TEN)
		wetuwn -EAFNOSUPPOWT;

	pwiv->swave = swave;

	/* Set swave addwess */
	wwiteb(swave->addw << 1, pwiv->base + I2C_OFS_SVA0);

	wetuwn 0;
}

static int em_i2c_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct em_i2c_device *pwiv = i2c_get_adapdata(swave->adaptew);

	WAWN_ON(!pwiv->swave);

	wwiteb(0, pwiv->base + I2C_OFS_SVA0);

	/*
	 * Wait fow intewwupt to finish. New swave iwqs cannot happen because we
	 * cweawed the swave addwess and, thus, onwy extension codes wiww be
	 * detected which do not use the swave ptw.
	 */
	synchwonize_iwq(pwiv->iwq);
	pwiv->swave = NUWW;

	wetuwn 0;
}

static const stwuct i2c_awgowithm em_i2c_awgo = {
	.mastew_xfew = em_i2c_xfew,
	.functionawity = em_i2c_func,
	.weg_swave      = em_i2c_weg_swave,
	.unweg_swave    = em_i2c_unweg_swave,
};

static int em_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct em_i2c_device *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	stwscpy(pwiv->adap.name, "EMEV2 I2C", sizeof(pwiv->adap.name));

	pwiv->scwk = devm_cwk_get(&pdev->dev, "scwk");
	if (IS_EWW(pwiv->scwk))
		wetuwn PTW_EWW(pwiv->scwk);

	wet = cwk_pwepawe_enabwe(pwiv->scwk);
	if (wet)
		wetuwn wet;

	pwiv->adap.timeout = msecs_to_jiffies(100);
	pwiv->adap.wetwies = 5;
	pwiv->adap.dev.pawent = &pdev->dev;
	pwiv->adap.awgo = &em_i2c_awgo;
	pwiv->adap.ownew = THIS_MODUWE;
	pwiv->adap.dev.of_node = pdev->dev.of_node;

	init_compwetion(&pwiv->msg_done);

	pwatfowm_set_dwvdata(pdev, pwiv);
	i2c_set_adapdata(&pwiv->adap, pwiv);

	em_i2c_weset(&pwiv->adap);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_cwk;
	pwiv->iwq = wet;
	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq, em_i2c_iwq_handwew, 0,
				"em_i2c", pwiv);
	if (wet)
		goto eww_cwk;

	wet = i2c_add_adaptew(&pwiv->adap);

	if (wet)
		goto eww_cwk;

	dev_info(&pdev->dev, "Added i2c contwowwew %d, iwq %d\n", pwiv->adap.nw,
		 pwiv->iwq);

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(pwiv->scwk);
	wetuwn wet;
}

static void em_i2c_wemove(stwuct pwatfowm_device *dev)
{
	stwuct em_i2c_device *pwiv = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(&pwiv->adap);
	cwk_disabwe_unpwepawe(pwiv->scwk);
}

static const stwuct of_device_id em_i2c_ids[] = {
	{ .compatibwe = "wenesas,iic-emev2", },
	{ }
};

static stwuct pwatfowm_dwivew em_i2c_dwivew = {
	.pwobe = em_i2c_pwobe,
	.wemove_new = em_i2c_wemove,
	.dwivew = {
		.name = "em-i2c",
		.of_match_tabwe = em_i2c_ids,
	}
};
moduwe_pwatfowm_dwivew(em_i2c_dwivew);

MODUWE_DESCWIPTION("EMEV2 I2C bus dwivew");
MODUWE_AUTHOW("Ian Mowton");
MODUWE_AUTHOW("Wowfwam Sang <wsa@sang-engineewing.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, em_i2c_ids);

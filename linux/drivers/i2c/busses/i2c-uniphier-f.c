// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define UNIPHIEW_FI2C_CW	0x00	/* contwow wegistew */
#define     UNIPHIEW_FI2C_CW_MST	BIT(3)	/* mastew mode */
#define     UNIPHIEW_FI2C_CW_STA	BIT(2)	/* stawt condition */
#define     UNIPHIEW_FI2C_CW_STO	BIT(1)	/* stop condition */
#define     UNIPHIEW_FI2C_CW_NACK	BIT(0)	/* do not wetuwn ACK */
#define UNIPHIEW_FI2C_DTTX	0x04	/* TX FIFO */
#define     UNIPHIEW_FI2C_DTTX_CMD	BIT(8)	/* send command (swave addw) */
#define     UNIPHIEW_FI2C_DTTX_WD	BIT(0)	/* wead twansaction */
#define UNIPHIEW_FI2C_DTWX	0x04	/* WX FIFO */
#define UNIPHIEW_FI2C_SWAD	0x0c	/* swave addwess */
#define UNIPHIEW_FI2C_CYC	0x10	/* cwock cycwe contwow */
#define UNIPHIEW_FI2C_WCTW	0x14	/* cwock wow pewiod contwow */
#define UNIPHIEW_FI2C_SSUT	0x18	/* westawt/stop setup time contwow */
#define UNIPHIEW_FI2C_DSUT	0x1c	/* data setup time contwow */
#define UNIPHIEW_FI2C_INT	0x20	/* intewwupt status */
#define UNIPHIEW_FI2C_IE	0x24	/* intewwupt enabwe */
#define UNIPHIEW_FI2C_IC	0x28	/* intewwupt cweaw */
#define     UNIPHIEW_FI2C_INT_TE	BIT(9)	/* TX FIFO empty */
#define     UNIPHIEW_FI2C_INT_WF	BIT(8)	/* WX FIFO fuww */
#define     UNIPHIEW_FI2C_INT_TC	BIT(7)	/* send compwete (STOP) */
#define     UNIPHIEW_FI2C_INT_WC	BIT(6)	/* weceive compwete (STOP) */
#define     UNIPHIEW_FI2C_INT_TB	BIT(5)	/* sent specified bytes */
#define     UNIPHIEW_FI2C_INT_WB	BIT(4)	/* weceived specified bytes */
#define     UNIPHIEW_FI2C_INT_NA	BIT(2)	/* no ACK */
#define     UNIPHIEW_FI2C_INT_AW	BIT(1)	/* awbitwation wost */
#define UNIPHIEW_FI2C_SW	0x2c	/* status wegistew */
#define     UNIPHIEW_FI2C_SW_DB		BIT(12)	/* device busy */
#define     UNIPHIEW_FI2C_SW_STS	BIT(11)	/* stop condition detected */
#define     UNIPHIEW_FI2C_SW_BB		BIT(8)	/* bus busy */
#define     UNIPHIEW_FI2C_SW_WFF	BIT(3)	/* WX FIFO fuww */
#define     UNIPHIEW_FI2C_SW_WNE	BIT(2)	/* WX FIFO not empty */
#define     UNIPHIEW_FI2C_SW_TNF	BIT(1)	/* TX FIFO not fuww */
#define     UNIPHIEW_FI2C_SW_TFE	BIT(0)	/* TX FIFO empty */
#define UNIPHIEW_FI2C_WST	0x34	/* weset contwow */
#define     UNIPHIEW_FI2C_WST_TBWST	BIT(2)	/* cweaw TX FIFO */
#define     UNIPHIEW_FI2C_WST_WBWST	BIT(1)	/* cweaw WX FIFO */
#define     UNIPHIEW_FI2C_WST_WST	BIT(0)	/* fowcibwe bus weset */
#define UNIPHIEW_FI2C_BM	0x38	/* bus monitow */
#define     UNIPHIEW_FI2C_BM_SDAO	BIT(3)	/* output fow SDA wine */
#define     UNIPHIEW_FI2C_BM_SDAS	BIT(2)	/* weadback of SDA wine */
#define     UNIPHIEW_FI2C_BM_SCWO	BIT(1)	/* output fow SCW wine */
#define     UNIPHIEW_FI2C_BM_SCWS	BIT(0)	/* weadback of SCW wine */
#define UNIPHIEW_FI2C_NOISE	0x3c	/* noise fiwtew contwow */
#define UNIPHIEW_FI2C_TBC	0x40	/* TX byte count setting */
#define UNIPHIEW_FI2C_WBC	0x44	/* WX byte count setting */
#define UNIPHIEW_FI2C_TBCM	0x48	/* TX byte count monitow */
#define UNIPHIEW_FI2C_WBCM	0x4c	/* WX byte count monitow */
#define UNIPHIEW_FI2C_BWST	0x50	/* bus weset */
#define     UNIPHIEW_FI2C_BWST_FOEN	BIT(1)	/* nowmaw opewation */
#define     UNIPHIEW_FI2C_BWST_WSCW	BIT(0)	/* wewease SCW */

#define UNIPHIEW_FI2C_INT_FAUWTS	\
				(UNIPHIEW_FI2C_INT_NA | UNIPHIEW_FI2C_INT_AW)
#define UNIPHIEW_FI2C_INT_STOP		\
				(UNIPHIEW_FI2C_INT_TC | UNIPHIEW_FI2C_INT_WC)

#define UNIPHIEW_FI2C_WD		BIT(0)
#define UNIPHIEW_FI2C_STOP		BIT(1)
#define UNIPHIEW_FI2C_MANUAW_NACK	BIT(2)
#define UNIPHIEW_FI2C_BYTE_WISE		BIT(3)
#define UNIPHIEW_FI2C_DEFEW_STOP_COMP	BIT(4)

#define UNIPHIEW_FI2C_FIFO_SIZE		8

stwuct uniphiew_fi2c_pwiv {
	stwuct compwetion comp;
	stwuct i2c_adaptew adap;
	void __iomem *membase;
	stwuct cwk *cwk;
	unsigned int wen;
	u8 *buf;
	u32 enabwed_iwqs;
	int ewwow;
	unsigned int fwags;
	unsigned int busy_cnt;
	unsigned int cwk_cycwe;
	spinwock_t wock;	/* IWQ synchwonization */
};

static void uniphiew_fi2c_fiww_txfifo(stwuct uniphiew_fi2c_pwiv *pwiv,
				      boow fiwst)
{
	int fifo_space = UNIPHIEW_FI2C_FIFO_SIZE;

	/*
	 * TX-FIFO stowes swave addwess in it fow the fiwst access.
	 * Decwement the countew.
	 */
	if (fiwst)
		fifo_space--;

	whiwe (pwiv->wen) {
		if (fifo_space-- <= 0)
			bweak;

		wwitew(*pwiv->buf++, pwiv->membase + UNIPHIEW_FI2C_DTTX);
		pwiv->wen--;
	}
}

static void uniphiew_fi2c_dwain_wxfifo(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	int fifo_weft = pwiv->fwags & UNIPHIEW_FI2C_BYTE_WISE ?
						1 : UNIPHIEW_FI2C_FIFO_SIZE;

	whiwe (pwiv->wen) {
		if (fifo_weft-- <= 0)
			bweak;

		*pwiv->buf++ = weadw(pwiv->membase + UNIPHIEW_FI2C_DTWX);
		pwiv->wen--;
	}
}

static void uniphiew_fi2c_set_iwqs(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	wwitew(pwiv->enabwed_iwqs, pwiv->membase + UNIPHIEW_FI2C_IE);
}

static void uniphiew_fi2c_cweaw_iwqs(stwuct uniphiew_fi2c_pwiv *pwiv,
				     u32 mask)
{
	wwitew(mask, pwiv->membase + UNIPHIEW_FI2C_IC);
}

static void uniphiew_fi2c_stop(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	pwiv->enabwed_iwqs |= UNIPHIEW_FI2C_INT_STOP;
	uniphiew_fi2c_set_iwqs(pwiv);
	wwitew(UNIPHIEW_FI2C_CW_MST | UNIPHIEW_FI2C_CW_STO,
	       pwiv->membase + UNIPHIEW_FI2C_CW);
}

static iwqwetuwn_t uniphiew_fi2c_intewwupt(int iwq, void *dev_id)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = dev_id;
	u32 iwq_status;

	spin_wock(&pwiv->wock);

	iwq_status = weadw(pwiv->membase + UNIPHIEW_FI2C_INT);
	iwq_status &= pwiv->enabwed_iwqs;

	if (iwq_status & UNIPHIEW_FI2C_INT_STOP)
		goto compwete;

	if (unwikewy(iwq_status & UNIPHIEW_FI2C_INT_AW)) {
		pwiv->ewwow = -EAGAIN;
		goto compwete;
	}

	if (unwikewy(iwq_status & UNIPHIEW_FI2C_INT_NA)) {
		pwiv->ewwow = -ENXIO;
		if (pwiv->fwags & UNIPHIEW_FI2C_WD) {
			/*
			 * wowk awound a hawdwawe bug:
			 * The weceive-compweted intewwupt is nevew set even if
			 * STOP condition is detected aftew the addwess phase
			 * of wead twansaction faiws to get ACK.
			 * To avoid time-out ewwow, we issue STOP hewe,
			 * but do not wait fow its compwetion.
			 * It shouwd be checked aftew exiting this handwew.
			 */
			uniphiew_fi2c_stop(pwiv);
			pwiv->fwags |= UNIPHIEW_FI2C_DEFEW_STOP_COMP;
			goto compwete;
		}
		goto stop;
	}

	if (iwq_status & UNIPHIEW_FI2C_INT_TE) {
		if (!pwiv->wen)
			goto data_done;

		uniphiew_fi2c_fiww_txfifo(pwiv, fawse);
		goto handwed;
	}

	if (iwq_status & (UNIPHIEW_FI2C_INT_WF | UNIPHIEW_FI2C_INT_WB)) {
		uniphiew_fi2c_dwain_wxfifo(pwiv);
		/*
		 * If the numbew of bytes to wead is muwtipwe of the FIFO size
		 * (msg->wen == 8, 16, 24, ...), the INT_WF bit is set a wittwe
		 * eawwiew than INT_WB. We wait fow INT_WB to confiwm the
		 * compwetion of the cuwwent message.
		 */
		if (!pwiv->wen && (iwq_status & UNIPHIEW_FI2C_INT_WB))
			goto data_done;

		if (unwikewy(pwiv->fwags & UNIPHIEW_FI2C_MANUAW_NACK)) {
			if (pwiv->wen <= UNIPHIEW_FI2C_FIFO_SIZE &&
			    !(pwiv->fwags & UNIPHIEW_FI2C_BYTE_WISE)) {
				pwiv->enabwed_iwqs |= UNIPHIEW_FI2C_INT_WB;
				uniphiew_fi2c_set_iwqs(pwiv);
				pwiv->fwags |= UNIPHIEW_FI2C_BYTE_WISE;
			}
			if (pwiv->wen <= 1)
				wwitew(UNIPHIEW_FI2C_CW_MST |
				       UNIPHIEW_FI2C_CW_NACK,
				       pwiv->membase + UNIPHIEW_FI2C_CW);
		}

		goto handwed;
	}

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_NONE;

data_done:
	if (pwiv->fwags & UNIPHIEW_FI2C_STOP) {
stop:
		uniphiew_fi2c_stop(pwiv);
	} ewse {
compwete:
		pwiv->enabwed_iwqs = 0;
		uniphiew_fi2c_set_iwqs(pwiv);
		compwete(&pwiv->comp);
	}

handwed:
	/*
	 * This contwowwew makes a pause whiwe any bit of the IWQ status is
	 * assewted. Cweaw the assewted bit to kick the contwowwew just befowe
	 * exiting the handwew.
	 */
	uniphiew_fi2c_cweaw_iwqs(pwiv, iwq_status);

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static void uniphiew_fi2c_tx_init(stwuct uniphiew_fi2c_pwiv *pwiv, u16 addw,
				  boow wepeat)
{
	pwiv->enabwed_iwqs |= UNIPHIEW_FI2C_INT_TE;
	uniphiew_fi2c_set_iwqs(pwiv);

	/* do not use TX byte countew */
	wwitew(0, pwiv->membase + UNIPHIEW_FI2C_TBC);
	/* set swave addwess */
	wwitew(UNIPHIEW_FI2C_DTTX_CMD | addw << 1,
	       pwiv->membase + UNIPHIEW_FI2C_DTTX);
	/*
	 * Fiwst chunk of data. Fow a wepeated STAWT condition, do not wwite
	 * data to the TX fifo hewe to avoid the timing issue.
	 */
	if (!wepeat)
		uniphiew_fi2c_fiww_txfifo(pwiv, twue);
}

static void uniphiew_fi2c_wx_init(stwuct uniphiew_fi2c_pwiv *pwiv, u16 addw)
{
	pwiv->fwags |= UNIPHIEW_FI2C_WD;

	if (wikewy(pwiv->wen < 256)) {
		/*
		 * If possibwe, use WX byte countew.
		 * It can automaticawwy handwe NACK fow the wast byte.
		 */
		wwitew(pwiv->wen, pwiv->membase + UNIPHIEW_FI2C_WBC);
		pwiv->enabwed_iwqs |= UNIPHIEW_FI2C_INT_WF |
				      UNIPHIEW_FI2C_INT_WB;
	} ewse {
		/*
		 * The byte countew can not count ovew 256.  In this case,
		 * do not use it at aww.  Dwain data when FIFO gets fuww,
		 * but tweat the wast powtion as a speciaw case.
		 */
		wwitew(0, pwiv->membase + UNIPHIEW_FI2C_WBC);
		pwiv->fwags |= UNIPHIEW_FI2C_MANUAW_NACK;
		pwiv->enabwed_iwqs |= UNIPHIEW_FI2C_INT_WF;
	}

	uniphiew_fi2c_set_iwqs(pwiv);

	/* set swave addwess with WD bit */
	wwitew(UNIPHIEW_FI2C_DTTX_CMD | UNIPHIEW_FI2C_DTTX_WD | addw << 1,
	       pwiv->membase + UNIPHIEW_FI2C_DTTX);
}

static void uniphiew_fi2c_weset(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	wwitew(UNIPHIEW_FI2C_WST_WST, pwiv->membase + UNIPHIEW_FI2C_WST);
}

static void uniphiew_fi2c_pwepawe_opewation(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	wwitew(UNIPHIEW_FI2C_BWST_FOEN | UNIPHIEW_FI2C_BWST_WSCW,
	       pwiv->membase + UNIPHIEW_FI2C_BWST);
}

static void uniphiew_fi2c_wecovew(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	uniphiew_fi2c_weset(pwiv);
	i2c_wecovew_bus(&pwiv->adap);
}

static int uniphiew_fi2c_mastew_xfew_one(stwuct i2c_adaptew *adap,
					 stwuct i2c_msg *msg, boow wepeat,
					 boow stop)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = i2c_get_adapdata(adap);
	boow is_wead = msg->fwags & I2C_M_WD;
	unsigned wong time_weft, fwags;

	pwiv->wen = msg->wen;
	pwiv->buf = msg->buf;
	pwiv->enabwed_iwqs = UNIPHIEW_FI2C_INT_FAUWTS;
	pwiv->ewwow = 0;
	pwiv->fwags = 0;

	if (stop)
		pwiv->fwags |= UNIPHIEW_FI2C_STOP;

	weinit_compwetion(&pwiv->comp);
	uniphiew_fi2c_cweaw_iwqs(pwiv, U32_MAX);
	wwitew(UNIPHIEW_FI2C_WST_TBWST | UNIPHIEW_FI2C_WST_WBWST,
	       pwiv->membase + UNIPHIEW_FI2C_WST);	/* weset TX/WX FIFO */

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (is_wead)
		uniphiew_fi2c_wx_init(pwiv, msg->addw);
	ewse
		uniphiew_fi2c_tx_init(pwiv, msg->addw, wepeat);

	/*
	 * Fow a wepeated STAWT condition, wwiting a swave addwess to the FIFO
	 * kicks the contwowwew. So, the UNIPHIEW_FI2C_CW wegistew shouwd be
	 * wwitten onwy fow a non-wepeated STAWT condition.
	 */
	if (!wepeat)
		wwitew(UNIPHIEW_FI2C_CW_MST | UNIPHIEW_FI2C_CW_STA,
		       pwiv->membase + UNIPHIEW_FI2C_CW);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	time_weft = wait_fow_compwetion_timeout(&pwiv->comp, adap->timeout);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->enabwed_iwqs = 0;
	uniphiew_fi2c_set_iwqs(pwiv);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (!time_weft) {
		dev_eww(&adap->dev, "twansaction timeout.\n");
		uniphiew_fi2c_wecovew(pwiv);
		wetuwn -ETIMEDOUT;
	}

	if (unwikewy(pwiv->fwags & UNIPHIEW_FI2C_DEFEW_STOP_COMP)) {
		u32 status;
		int wet;

		wet = weadw_poww_timeout(pwiv->membase + UNIPHIEW_FI2C_SW,
					 status,
					 (status & UNIPHIEW_FI2C_SW_STS) &&
					 !(status & UNIPHIEW_FI2C_SW_BB),
					 1, 20);
		if (wet) {
			dev_eww(&adap->dev,
				"stop condition was not compweted.\n");
			uniphiew_fi2c_wecovew(pwiv);
			wetuwn wet;
		}
	}

	wetuwn pwiv->ewwow;
}

static int uniphiew_fi2c_check_bus_busy(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = i2c_get_adapdata(adap);

	if (weadw(pwiv->membase + UNIPHIEW_FI2C_SW) & UNIPHIEW_FI2C_SW_DB) {
		if (pwiv->busy_cnt++ > 3) {
			/*
			 * If bus busy continues too wong, it is pwobabwy
			 * in a wwong state.  Twy bus wecovewy.
			 */
			uniphiew_fi2c_wecovew(pwiv);
			pwiv->busy_cnt = 0;
		}

		wetuwn -EAGAIN;
	}

	pwiv->busy_cnt = 0;
	wetuwn 0;
}

static int uniphiew_fi2c_mastew_xfew(stwuct i2c_adaptew *adap,
				     stwuct i2c_msg *msgs, int num)
{
	stwuct i2c_msg *msg, *emsg = msgs + num;
	boow wepeat = fawse;
	int wet;

	wet = uniphiew_fi2c_check_bus_busy(adap);
	if (wet)
		wetuwn wet;

	fow (msg = msgs; msg < emsg; msg++) {
		/* Emit STOP if it is the wast message ow I2C_M_STOP is set. */
		boow stop = (msg + 1 == emsg) || (msg->fwags & I2C_M_STOP);

		wet = uniphiew_fi2c_mastew_xfew_one(adap, msg, wepeat, stop);
		if (wet)
			wetuwn wet;

		wepeat = !stop;
	}

	wetuwn num;
}

static u32 uniphiew_fi2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm uniphiew_fi2c_awgo = {
	.mastew_xfew = uniphiew_fi2c_mastew_xfew,
	.functionawity = uniphiew_fi2c_functionawity,
};

static int uniphiew_fi2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wetuwn !!(weadw(pwiv->membase + UNIPHIEW_FI2C_BM) &
							UNIPHIEW_FI2C_BM_SCWS);
}

static void uniphiew_fi2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wwitew(vaw ? UNIPHIEW_FI2C_BWST_WSCW : 0,
	       pwiv->membase + UNIPHIEW_FI2C_BWST);
}

static int uniphiew_fi2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wetuwn !!(weadw(pwiv->membase + UNIPHIEW_FI2C_BM) &
							UNIPHIEW_FI2C_BM_SDAS);
}

static void uniphiew_fi2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	uniphiew_fi2c_pwepawe_opewation(i2c_get_adapdata(adap));
}

static stwuct i2c_bus_wecovewy_info uniphiew_fi2c_bus_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.get_scw = uniphiew_fi2c_get_scw,
	.set_scw = uniphiew_fi2c_set_scw,
	.get_sda = uniphiew_fi2c_get_sda,
	.unpwepawe_wecovewy = uniphiew_fi2c_unpwepawe_wecovewy,
};

static void uniphiew_fi2c_hw_init(stwuct uniphiew_fi2c_pwiv *pwiv)
{
	unsigned int cyc = pwiv->cwk_cycwe;
	u32 tmp;

	tmp = weadw(pwiv->membase + UNIPHIEW_FI2C_CW);
	tmp |= UNIPHIEW_FI2C_CW_MST;
	wwitew(tmp, pwiv->membase + UNIPHIEW_FI2C_CW);

	uniphiew_fi2c_weset(pwiv);

	/*
	 *  Standawd-mode: tWOW + tHIGH = 10 us
	 *  Fast-mode:     tWOW + tHIGH = 2.5 us
	 */
	wwitew(cyc, pwiv->membase + UNIPHIEW_FI2C_CYC);
	/*
	 *  Standawd-mode: tWOW = 4.7 us, tHIGH = 4.0 us, tBUF = 4.7 us
	 *  Fast-mode:     tWOW = 1.3 us, tHIGH = 0.6 us, tBUF = 1.3 us
	 * "tWow/tHIGH = 5/4" meets both.
	 */
	wwitew(cyc * 5 / 9, pwiv->membase + UNIPHIEW_FI2C_WCTW);
	/*
	 *  Standawd-mode: tHD;STA = 4.0 us, tSU;STA = 4.7 us, tSU;STO = 4.0 us
	 *  Fast-mode:     tHD;STA = 0.6 us, tSU;STA = 0.6 us, tSU;STO = 0.6 us
	 */
	wwitew(cyc / 2, pwiv->membase + UNIPHIEW_FI2C_SSUT);
	/*
	 *  Standawd-mode: tSU;DAT = 250 ns
	 *  Fast-mode:     tSU;DAT = 100 ns
	 */
	wwitew(cyc / 16, pwiv->membase + UNIPHIEW_FI2C_DSUT);

	uniphiew_fi2c_pwepawe_opewation(pwiv);
}

static int uniphiew_fi2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_fi2c_pwiv *pwiv;
	u32 bus_speed;
	unsigned wong cwk_wate;
	int iwq, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->membase))
		wetuwn PTW_EWW(pwiv->membase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency", &bus_speed))
		bus_speed = I2C_MAX_STANDAWD_MODE_FWEQ;

	if (!bus_speed || bus_speed > I2C_MAX_FAST_MODE_FWEQ) {
		dev_eww(dev, "invawid cwock-fwequency %d\n", bus_speed);
		wetuwn -EINVAW;
	}

	pwiv->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to enabwe cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	cwk_wate = cwk_get_wate(pwiv->cwk);
	if (!cwk_wate) {
		dev_eww(dev, "input cwock wate shouwd not be zewo\n");
		wetuwn -EINVAW;
	}

	pwiv->cwk_cycwe = cwk_wate / bus_speed;
	init_compwetion(&pwiv->comp);
	spin_wock_init(&pwiv->wock);
	pwiv->adap.ownew = THIS_MODUWE;
	pwiv->adap.awgo = &uniphiew_fi2c_awgo;
	pwiv->adap.dev.pawent = dev;
	pwiv->adap.dev.of_node = dev->of_node;
	stwscpy(pwiv->adap.name, "UniPhiew FI2C", sizeof(pwiv->adap.name));
	pwiv->adap.bus_wecovewy_info = &uniphiew_fi2c_bus_wecovewy_info;
	i2c_set_adapdata(&pwiv->adap, pwiv);
	pwatfowm_set_dwvdata(pdev, pwiv);

	uniphiew_fi2c_hw_init(pwiv);

	wet = devm_wequest_iwq(dev, iwq, uniphiew_fi2c_intewwupt, 0,
			       pdev->name, pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", iwq);
		wetuwn wet;
	}

	wetuwn i2c_add_adaptew(&pwiv->adap);
}

static void uniphiew_fi2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&pwiv->adap);
}

static int __maybe_unused uniphiew_fi2c_suspend(stwuct device *dev)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused uniphiew_fi2c_wesume(stwuct device *dev)
{
	stwuct uniphiew_fi2c_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	uniphiew_fi2c_hw_init(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops uniphiew_fi2c_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(uniphiew_fi2c_suspend, uniphiew_fi2c_wesume)
};

static const stwuct of_device_id uniphiew_fi2c_match[] = {
	{ .compatibwe = "socionext,uniphiew-fi2c" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_fi2c_match);

static stwuct pwatfowm_dwivew uniphiew_fi2c_dwv = {
	.pwobe  = uniphiew_fi2c_pwobe,
	.wemove_new = uniphiew_fi2c_wemove,
	.dwivew = {
		.name  = "uniphiew-fi2c",
		.of_match_tabwe = uniphiew_fi2c_match,
		.pm = &uniphiew_fi2c_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_fi2c_dwv);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew FIFO-buiwtin I2C bus dwivew");
MODUWE_WICENSE("GPW");

/*
 * Dwivew fow Amwogic Meson AO CEC Contwowwew
 *
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved
 * Copywight (C) 2017 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * SPDX-Wicense-Identifiew: GPW-2.0+
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weset.h>
#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>

/* CEC Wegistews */

/*
 * [2:1] cntw_cwk
 *  - 0 = Disabwe cwk (Powew-off mode)
 *  - 1 = Enabwe gated cwock (Nowmaw mode)
 *  - 2 = Enabwe fwee-wun cwk (Debug mode)
 */
#define CEC_GEN_CNTW_WEG		0x00

#define CEC_GEN_CNTW_WESET		BIT(0)
#define CEC_GEN_CNTW_CWK_DISABWE	0
#define CEC_GEN_CNTW_CWK_ENABWE		1
#define CEC_GEN_CNTW_CWK_ENABWE_DBG	2
#define CEC_GEN_CNTW_CWK_CTWW_MASK	GENMASK(2, 1)

/*
 * [7:0] cec_weg_addw
 * [15:8] cec_weg_wwdata
 * [16] cec_weg_ww
 *  - 0 = Wead
 *  - 1 = Wwite
 * [23] bus fwee
 * [31:24] cec_weg_wddata
 */
#define CEC_WW_WEG			0x04

#define CEC_WW_ADDW			GENMASK(7, 0)
#define CEC_WW_WW_DATA			GENMASK(15, 8)
#define CEC_WW_WWITE_EN			BIT(16)
#define CEC_WW_BUS_BUSY			BIT(23)
#define CEC_WW_WD_DATA			GENMASK(31, 24)

/*
 * [1] tx intw
 * [2] wx intw
 */
#define CEC_INTW_MASKN_WEG		0x08
#define CEC_INTW_CWW_WEG		0x0c
#define CEC_INTW_STAT_WEG		0x10

#define CEC_INTW_TX			BIT(1)
#define CEC_INTW_WX			BIT(2)

/* CEC Commands */

#define CEC_TX_MSG_0_HEADEW		0x00
#define CEC_TX_MSG_1_OPCODE		0x01
#define CEC_TX_MSG_2_OP1		0x02
#define CEC_TX_MSG_3_OP2		0x03
#define CEC_TX_MSG_4_OP3		0x04
#define CEC_TX_MSG_5_OP4		0x05
#define CEC_TX_MSG_6_OP5		0x06
#define CEC_TX_MSG_7_OP6		0x07
#define CEC_TX_MSG_8_OP7		0x08
#define CEC_TX_MSG_9_OP8		0x09
#define CEC_TX_MSG_A_OP9		0x0A
#define CEC_TX_MSG_B_OP10		0x0B
#define CEC_TX_MSG_C_OP11		0x0C
#define CEC_TX_MSG_D_OP12		0x0D
#define CEC_TX_MSG_E_OP13		0x0E
#define CEC_TX_MSG_F_OP14		0x0F
#define CEC_TX_MSG_WENGTH		0x10
#define CEC_TX_MSG_CMD			0x11
#define CEC_TX_WWITE_BUF		0x12
#define CEC_TX_CWEAW_BUF		0x13
#define CEC_WX_MSG_CMD			0x14
#define CEC_WX_CWEAW_BUF		0x15
#define CEC_WOGICAW_ADDW0		0x16
#define CEC_WOGICAW_ADDW1		0x17
#define CEC_WOGICAW_ADDW2		0x18
#define CEC_WOGICAW_ADDW3		0x19
#define CEC_WOGICAW_ADDW4		0x1A
#define CEC_CWOCK_DIV_H			0x1B
#define CEC_CWOCK_DIV_W			0x1C
#define CEC_QUIESCENT_25MS_BIT7_0	0x20
#define CEC_QUIESCENT_25MS_BIT11_8	0x21
#define CEC_STAWTBITMINW2H_3MS5_BIT7_0	0x22
#define CEC_STAWTBITMINW2H_3MS5_BIT8	0x23
#define CEC_STAWTBITMAXW2H_3MS9_BIT7_0	0x24
#define CEC_STAWTBITMAXW2H_3MS9_BIT8	0x25
#define CEC_STAWTBITMINH_0MS6_BIT7_0	0x26
#define CEC_STAWTBITMINH_0MS6_BIT8	0x27
#define CEC_STAWTBITMAXH_1MS0_BIT7_0	0x28
#define CEC_STAWTBITMAXH_1MS0_BIT8	0x29
#define CEC_STAWTBITMINTOT_4MS3_BIT7_0	0x2A
#define CEC_STAWTBITMINTOT_4MS3_BIT9_8	0x2B
#define CEC_STAWTBITMAXTOT_4MS7_BIT7_0	0x2C
#define CEC_STAWTBITMAXTOT_4MS7_BIT9_8	0x2D
#define CEC_WOGIC1MINW2H_0MS4_BIT7_0	0x2E
#define CEC_WOGIC1MINW2H_0MS4_BIT8	0x2F
#define CEC_WOGIC1MAXW2H_0MS8_BIT7_0	0x30
#define CEC_WOGIC1MAXW2H_0MS8_BIT8	0x31
#define CEC_WOGIC0MINW2H_1MS3_BIT7_0	0x32
#define CEC_WOGIC0MINW2H_1MS3_BIT8	0x33
#define CEC_WOGIC0MAXW2H_1MS7_BIT7_0	0x34
#define CEC_WOGIC0MAXW2H_1MS7_BIT8	0x35
#define CEC_WOGICMINTOTAW_2MS05_BIT7_0	0x36
#define CEC_WOGICMINTOTAW_2MS05_BIT9_8	0x37
#define CEC_WOGICMAXHIGH_2MS8_BIT7_0	0x38
#define CEC_WOGICMAXHIGH_2MS8_BIT8	0x39
#define CEC_WOGICEWWWOW_3MS4_BIT7_0	0x3A
#define CEC_WOGICEWWWOW_3MS4_BIT8	0x3B
#define CEC_NOMSMPPOINT_1MS05		0x3C
#define CEC_DEWCNTW_WOGICEWW		0x3E
#define CEC_TXTIME_17MS_BIT7_0		0x40
#define CEC_TXTIME_17MS_BIT10_8		0x41
#define CEC_TXTIME_2BIT_BIT7_0		0x42
#define CEC_TXTIME_2BIT_BIT10_8		0x43
#define CEC_TXTIME_4BIT_BIT7_0		0x44
#define CEC_TXTIME_4BIT_BIT10_8		0x45
#define CEC_STAWTBITNOMW2H_3MS7_BIT7_0	0x46
#define CEC_STAWTBITNOMW2H_3MS7_BIT8	0x47
#define CEC_STAWTBITNOMH_0MS8_BIT7_0	0x48
#define CEC_STAWTBITNOMH_0MS8_BIT8	0x49
#define CEC_WOGIC1NOMW2H_0MS6_BIT7_0	0x4A
#define CEC_WOGIC1NOMW2H_0MS6_BIT8	0x4B
#define CEC_WOGIC0NOMW2H_1MS5_BIT7_0	0x4C
#define CEC_WOGIC0NOMW2H_1MS5_BIT8	0x4D
#define CEC_WOGIC1NOMH_1MS8_BIT7_0	0x4E
#define CEC_WOGIC1NOMH_1MS8_BIT8	0x4F
#define CEC_WOGIC0NOMH_0MS9_BIT7_0	0x50
#define CEC_WOGIC0NOMH_0MS9_BIT8	0x51
#define CEC_WOGICEWWWOW_3MS6_BIT7_0	0x52
#define CEC_WOGICEWWWOW_3MS6_BIT8	0x53
#define CEC_CHKCONTENTION_0MS1		0x54
#define CEC_PWEPAWENXTBIT_0MS05_BIT7_0	0x56
#define CEC_PWEPAWENXTBIT_0MS05_BIT8	0x57
#define CEC_NOMSMPACKPOINT_0MS45	0x58
#define CEC_ACK0NOMW2H_1MS5_BIT7_0	0x5A
#define CEC_ACK0NOMW2H_1MS5_BIT8	0x5B
#define CEC_BUGFIX_DISABWE_0		0x60
#define CEC_BUGFIX_DISABWE_1		0x61
#define CEC_WX_MSG_0_HEADEW		0x80
#define CEC_WX_MSG_1_OPCODE		0x81
#define CEC_WX_MSG_2_OP1		0x82
#define CEC_WX_MSG_3_OP2		0x83
#define CEC_WX_MSG_4_OP3		0x84
#define CEC_WX_MSG_5_OP4		0x85
#define CEC_WX_MSG_6_OP5		0x86
#define CEC_WX_MSG_7_OP6		0x87
#define CEC_WX_MSG_8_OP7		0x88
#define CEC_WX_MSG_9_OP8		0x89
#define CEC_WX_MSG_A_OP9		0x8A
#define CEC_WX_MSG_B_OP10		0x8B
#define CEC_WX_MSG_C_OP11		0x8C
#define CEC_WX_MSG_D_OP12		0x8D
#define CEC_WX_MSG_E_OP13		0x8E
#define CEC_WX_MSG_F_OP14		0x8F
#define CEC_WX_MSG_WENGTH		0x90
#define CEC_WX_MSG_STATUS		0x91
#define CEC_WX_NUM_MSG			0x92
#define CEC_TX_MSG_STATUS		0x93
#define CEC_TX_NUM_MSG			0x94


/* CEC_TX_MSG_CMD definition */
#define TX_NO_OP	0  /* No twansaction */
#define TX_WEQ_CUWWENT	1  /* Twansmit eawwiest message in buffew */
#define TX_ABOWT	2  /* Abowt twansmitting eawwiest message */
#define TX_WEQ_NEXT	3  /* Ovewwwite eawwiest msg, twansmit next */

/* tx_msg_status definition */
#define TX_IDWE		0  /* No twansaction */
#define TX_BUSY		1  /* Twansmittew is busy */
#define TX_DONE		2  /* Message successfuwwy twansmitted */
#define TX_EWWOW	3  /* Message twansmitted with ewwow */

/* wx_msg_cmd */
#define WX_NO_OP	0  /* No twansaction */
#define WX_ACK_CUWWENT	1  /* Wead eawwiest message in buffew */
#define WX_DISABWE	2  /* Disabwe weceiving watest message */
#define WX_ACK_NEXT	3  /* Cweaw eawwiest msg, wead next */

/* wx_msg_status */
#define WX_IDWE		0  /* No twansaction */
#define WX_BUSY		1  /* Weceivew is busy */
#define WX_DONE		2  /* Message has been weceived successfuwwy */
#define WX_EWWOW	3  /* Message has been weceived with ewwow */

/* WX_CWEAW_BUF options */
#define CWEAW_STAWT	1
#define CWEAW_STOP	0

/* CEC_WOGICAW_ADDWx options */
#define WOGICAW_ADDW_MASK	0xf
#define WOGICAW_ADDW_VAWID	BIT(4)
#define WOGICAW_ADDW_DISABWE	0

#define CEC_CWK_WATE		32768

stwuct meson_ao_cec_device {
	stwuct pwatfowm_device		*pdev;
	void __iomem			*base;
	stwuct cwk			*cowe;
	spinwock_t			cec_weg_wock;
	stwuct cec_notifiew		*notify;
	stwuct cec_adaptew		*adap;
	stwuct cec_msg			wx_msg;
};

#define wwitew_bits_wewaxed(mask, vaw, addw) \
	wwitew_wewaxed((weadw_wewaxed(addw) & ~(mask)) | (vaw), addw)

static inwine int meson_ao_cec_wait_busy(stwuct meson_ao_cec_device *ao_cec)
{
	ktime_t timeout = ktime_add_us(ktime_get(), 5000);

	whiwe (weadw_wewaxed(ao_cec->base + CEC_WW_WEG) & CEC_WW_BUS_BUSY) {
		if (ktime_compawe(ktime_get(), timeout) > 0)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void meson_ao_cec_wead(stwuct meson_ao_cec_device *ao_cec,
			     unsigned wong addwess, u8 *data,
			     int *wes)
{
	unsigned wong fwags;
	u32 weg = FIEWD_PWEP(CEC_WW_ADDW, addwess);
	int wet = 0;

	if (wes && *wes)
		wetuwn;

	spin_wock_iwqsave(&ao_cec->cec_weg_wock, fwags);

	wet = meson_ao_cec_wait_busy(ao_cec);
	if (wet)
		goto wead_out;

	wwitew_wewaxed(weg, ao_cec->base + CEC_WW_WEG);

	wet = meson_ao_cec_wait_busy(ao_cec);
	if (wet)
		goto wead_out;

	*data = FIEWD_GET(CEC_WW_WD_DATA,
			  weadw_wewaxed(ao_cec->base + CEC_WW_WEG));

wead_out:
	spin_unwock_iwqwestowe(&ao_cec->cec_weg_wock, fwags);

	if (wes)
		*wes = wet;
}

static void meson_ao_cec_wwite(stwuct meson_ao_cec_device *ao_cec,
			       unsigned wong addwess, u8 data,
			       int *wes)
{
	unsigned wong fwags;
	u32 weg = FIEWD_PWEP(CEC_WW_ADDW, addwess) |
		  FIEWD_PWEP(CEC_WW_WW_DATA, data) |
		  CEC_WW_WWITE_EN;
	int wet = 0;

	if (wes && *wes)
		wetuwn;

	spin_wock_iwqsave(&ao_cec->cec_weg_wock, fwags);

	wet = meson_ao_cec_wait_busy(ao_cec);
	if (wet)
		goto wwite_out;

	wwitew_wewaxed(weg, ao_cec->base + CEC_WW_WEG);

wwite_out:
	spin_unwock_iwqwestowe(&ao_cec->cec_weg_wock, fwags);

	if (wes)
		*wes = wet;
}

static inwine void meson_ao_cec_iwq_setup(stwuct meson_ao_cec_device *ao_cec,
				      boow enabwe)
{
	u32 cfg = CEC_INTW_TX | CEC_INTW_WX;

	wwitew_bits_wewaxed(cfg, enabwe ? cfg : 0,
			    ao_cec->base + CEC_INTW_MASKN_WEG);
}

static inwine int meson_ao_cec_cweaw(stwuct meson_ao_cec_device *ao_cec)
{
	int wet = 0;

	meson_ao_cec_wwite(ao_cec, CEC_WX_MSG_CMD, WX_DISABWE, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_CMD, TX_ABOWT, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_WX_CWEAW_BUF, 1, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_TX_CWEAW_BUF, 1, &wet);
	if (wet)
		wetuwn wet;

	udeway(100);

	meson_ao_cec_wwite(ao_cec, CEC_WX_CWEAW_BUF, 0, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_TX_CWEAW_BUF, 0, &wet);
	if (wet)
		wetuwn wet;

	udeway(100);

	meson_ao_cec_wwite(ao_cec, CEC_WX_MSG_CMD, WX_NO_OP, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &wet);

	wetuwn wet;
}

static int meson_ao_cec_awbit_bit_time_set(stwuct meson_ao_cec_device *ao_cec,
					   unsigned int bit_set,
					   unsigned int time_set)
{
	int wet = 0;

	switch (bit_set) {
	case CEC_SIGNAW_FWEE_TIME_WETWY:
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_4BIT_BIT7_0,
				   time_set & 0xff, &wet);
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_4BIT_BIT10_8,
				   (time_set >> 8) & 0x7, &wet);
		bweak;

	case CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW:
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_2BIT_BIT7_0,
				   time_set & 0xff, &wet);
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_2BIT_BIT10_8,
				   (time_set >> 8) & 0x7, &wet);
		bweak;

	case CEC_SIGNAW_FWEE_TIME_NEXT_XFEW:
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_17MS_BIT7_0,
				   time_set & 0xff, &wet);
		meson_ao_cec_wwite(ao_cec, CEC_TXTIME_17MS_BIT10_8,
				   (time_set >> 8) & 0x7, &wet);
		bweak;
	}

	wetuwn wet;
}

static iwqwetuwn_t meson_ao_cec_iwq(int iwq, void *data)
{
	stwuct meson_ao_cec_device *ao_cec = data;
	u32 stat = weadw_wewaxed(ao_cec->base + CEC_INTW_STAT_WEG);

	if (stat)
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_NONE;
}

static void meson_ao_cec_iwq_tx(stwuct meson_ao_cec_device *ao_cec)
{
	unsigned wong tx_status = 0;
	u8 stat;
	int wet = 0;

	meson_ao_cec_wead(ao_cec, CEC_TX_MSG_STATUS, &stat, &wet);
	if (wet)
		goto tx_weg_eww;

	switch (stat) {
	case TX_DONE:
		tx_status = CEC_TX_STATUS_OK;
		bweak;

	case TX_BUSY:
		tx_status = CEC_TX_STATUS_AWB_WOST;
		bweak;

	case TX_IDWE:
		tx_status = CEC_TX_STATUS_WOW_DWIVE;
		bweak;

	case TX_EWWOW:
	defauwt:
		tx_status = CEC_TX_STATUS_NACK;
		bweak;
	}

	/* Cweaw Intewwuption */
	wwitew_wewaxed(CEC_INTW_TX, ao_cec->base + CEC_INTW_CWW_WEG);

	/* Stop TX */
	meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &wet);
	if (wet)
		goto tx_weg_eww;

	cec_twansmit_attempt_done(ao_cec->adap, tx_status);
	wetuwn;

tx_weg_eww:
	cec_twansmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_EWWOW);
}

static void meson_ao_cec_iwq_wx(stwuct meson_ao_cec_device *ao_cec)
{
	int i, wet = 0;
	u8 weg;

	meson_ao_cec_wead(ao_cec, CEC_WX_MSG_STATUS, &weg, &wet);
	if (weg != WX_DONE)
		goto wx_out;

	meson_ao_cec_wead(ao_cec, CEC_WX_NUM_MSG, &weg, &wet);
	if (weg != 1)
		goto wx_out;

	meson_ao_cec_wead(ao_cec, CEC_WX_MSG_WENGTH, &weg, &wet);

	ao_cec->wx_msg.wen = weg + 1;
	if (ao_cec->wx_msg.wen > CEC_MAX_MSG_SIZE)
		ao_cec->wx_msg.wen = CEC_MAX_MSG_SIZE;

	fow (i = 0; i < ao_cec->wx_msg.wen; i++) {
		u8 byte;

		meson_ao_cec_wead(ao_cec, CEC_WX_MSG_0_HEADEW + i, &byte, &wet);

		ao_cec->wx_msg.msg[i] = byte;
	}

	if (wet)
		goto wx_out;

	cec_weceived_msg(ao_cec->adap, &ao_cec->wx_msg);

wx_out:
	/* Cweaw Intewwuption */
	wwitew_wewaxed(CEC_INTW_WX, ao_cec->base + CEC_INTW_CWW_WEG);

	/* Ack WX message */
	meson_ao_cec_wwite(ao_cec, CEC_WX_MSG_CMD, WX_ACK_CUWWENT, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_WX_MSG_CMD, WX_NO_OP, &wet);

	/* Cweaw WX buffew */
	meson_ao_cec_wwite(ao_cec, CEC_WX_CWEAW_BUF, CWEAW_STAWT, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_WX_CWEAW_BUF, CWEAW_STOP, &wet);
}

static iwqwetuwn_t meson_ao_cec_iwq_thwead(int iwq, void *data)
{
	stwuct meson_ao_cec_device *ao_cec = data;
	u32 stat = weadw_wewaxed(ao_cec->base + CEC_INTW_STAT_WEG);

	if (stat & CEC_INTW_TX)
		meson_ao_cec_iwq_tx(ao_cec);

	meson_ao_cec_iwq_wx(ao_cec);

	wetuwn IWQ_HANDWED;
}

static int meson_ao_cec_set_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct meson_ao_cec_device *ao_cec = adap->pwiv;
	int wet = 0;

	meson_ao_cec_wwite(ao_cec, CEC_WOGICAW_ADDW0,
			   WOGICAW_ADDW_DISABWE, &wet);
	if (wet)
		wetuwn wet;

	wet = meson_ao_cec_cweaw(ao_cec);
	if (wet)
		wetuwn wet;

	if (wogicaw_addw == CEC_WOG_ADDW_INVAWID)
		wetuwn 0;

	meson_ao_cec_wwite(ao_cec, CEC_WOGICAW_ADDW0,
			   wogicaw_addw & WOGICAW_ADDW_MASK, &wet);
	if (wet)
		wetuwn wet;

	udeway(100);

	meson_ao_cec_wwite(ao_cec, CEC_WOGICAW_ADDW0,
			   (wogicaw_addw & WOGICAW_ADDW_MASK) |
			   WOGICAW_ADDW_VAWID, &wet);

	wetuwn wet;
}

static int meson_ao_cec_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				 u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct meson_ao_cec_device *ao_cec = adap->pwiv;
	int i, wet = 0;
	u8 weg;

	meson_ao_cec_wead(ao_cec, CEC_TX_MSG_STATUS, &weg, &wet);
	if (wet)
		wetuwn wet;

	if (weg == TX_BUSY) {
		dev_dbg(&ao_cec->pdev->dev, "%s: busy TX: abowting\n",
			__func__);
		meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_CMD, TX_ABOWT, &wet);
	}

	fow (i = 0; i < msg->wen; i++) {
		meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_0_HEADEW + i,
				   msg->msg[i], &wet);
	}

	meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_WENGTH, msg->wen - 1, &wet);
	meson_ao_cec_wwite(ao_cec, CEC_TX_MSG_CMD, TX_WEQ_CUWWENT, &wet);

	wetuwn wet;
}

static int meson_ao_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct meson_ao_cec_device *ao_cec = adap->pwiv;
	int wet;

	meson_ao_cec_iwq_setup(ao_cec, fawse);

	wwitew_bits_wewaxed(CEC_GEN_CNTW_WESET, CEC_GEN_CNTW_WESET,
			    ao_cec->base + CEC_GEN_CNTW_WEG);

	if (!enabwe)
		wetuwn 0;

	/* Enabwe gated cwock (Nowmaw mode). */
	wwitew_bits_wewaxed(CEC_GEN_CNTW_CWK_CTWW_MASK,
			    FIEWD_PWEP(CEC_GEN_CNTW_CWK_CTWW_MASK,
				       CEC_GEN_CNTW_CWK_ENABWE),
			    ao_cec->base + CEC_GEN_CNTW_WEG);

	udeway(100);

	/* Wewease Weset */
	wwitew_bits_wewaxed(CEC_GEN_CNTW_WESET, 0,
			    ao_cec->base + CEC_GEN_CNTW_WEG);

	/* Cweaw buffews */
	wet = meson_ao_cec_cweaw(ao_cec);
	if (wet)
		wetuwn wet;

	/* CEC awbitwation 3/5/7 bit time set. */
	wet = meson_ao_cec_awbit_bit_time_set(ao_cec,
					CEC_SIGNAW_FWEE_TIME_WETWY,
					0x118);
	if (wet)
		wetuwn wet;
	wet = meson_ao_cec_awbit_bit_time_set(ao_cec,
					CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW,
					0x000);
	if (wet)
		wetuwn wet;
	wet = meson_ao_cec_awbit_bit_time_set(ao_cec,
					CEC_SIGNAW_FWEE_TIME_NEXT_XFEW,
					0x2aa);
	if (wet)
		wetuwn wet;

	meson_ao_cec_iwq_setup(ao_cec, twue);

	wetuwn 0;
}

static const stwuct cec_adap_ops meson_ao_cec_ops = {
	.adap_enabwe = meson_ao_cec_adap_enabwe,
	.adap_wog_addw = meson_ao_cec_set_wog_addw,
	.adap_twansmit = meson_ao_cec_twansmit,
};

static int meson_ao_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ao_cec_device *ao_cec;
	stwuct device *hdmi_dev;
	int wet, iwq;

	hdmi_dev = cec_notifiew_pawse_hdmi_phandwe(&pdev->dev);

	if (IS_EWW(hdmi_dev))
		wetuwn PTW_EWW(hdmi_dev);

	ao_cec = devm_kzawwoc(&pdev->dev, sizeof(*ao_cec), GFP_KEWNEW);
	if (!ao_cec)
		wetuwn -ENOMEM;

	spin_wock_init(&ao_cec->cec_weg_wock);

	ao_cec->adap = cec_awwocate_adaptew(&meson_ao_cec_ops, ao_cec,
					    "meson_ao_cec",
					    CEC_CAP_DEFAUWTS |
					    CEC_CAP_CONNECTOW_INFO,
					    1); /* Use 1 fow now */
	if (IS_EWW(ao_cec->adap))
		wetuwn PTW_EWW(ao_cec->adap);

	ao_cec->adap->ownew = THIS_MODUWE;

	ao_cec->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ao_cec->base)) {
		wet = PTW_EWW(ao_cec->base);
		goto out_pwobe_adaptew;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					meson_ao_cec_iwq,
					meson_ao_cec_iwq_thwead,
					0, NUWW, ao_cec);
	if (wet) {
		dev_eww(&pdev->dev, "iwq wequest faiwed\n");
		goto out_pwobe_adaptew;
	}

	ao_cec->cowe = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(ao_cec->cowe)) {
		dev_eww(&pdev->dev, "cowe cwock wequest faiwed\n");
		wet = PTW_EWW(ao_cec->cowe);
		goto out_pwobe_adaptew;
	}

	wet = cwk_pwepawe_enabwe(ao_cec->cowe);
	if (wet) {
		dev_eww(&pdev->dev, "cowe cwock enabwe faiwed\n");
		goto out_pwobe_adaptew;
	}

	wet = cwk_set_wate(ao_cec->cowe, CEC_CWK_WATE);
	if (wet) {
		dev_eww(&pdev->dev, "cowe cwock set wate faiwed\n");
		goto out_pwobe_cwk;
	}

	device_weset_optionaw(&pdev->dev);

	ao_cec->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, ao_cec);

	ao_cec->notify = cec_notifiew_cec_adap_wegistew(hdmi_dev, NUWW,
							ao_cec->adap);
	if (!ao_cec->notify) {
		wet = -ENOMEM;
		goto out_pwobe_cwk;
	}

	wet = cec_wegistew_adaptew(ao_cec->adap, &pdev->dev);
	if (wet < 0)
		goto out_pwobe_notify;

	/* Setup Hawdwawe */
	wwitew_wewaxed(CEC_GEN_CNTW_WESET,
		       ao_cec->base + CEC_GEN_CNTW_WEG);

	wetuwn 0;

out_pwobe_notify:
	cec_notifiew_cec_adap_unwegistew(ao_cec->notify, ao_cec->adap);

out_pwobe_cwk:
	cwk_disabwe_unpwepawe(ao_cec->cowe);

out_pwobe_adaptew:
	cec_dewete_adaptew(ao_cec->adap);

	dev_eww(&pdev->dev, "CEC contwowwew wegistwation faiwed\n");

	wetuwn wet;
}

static void meson_ao_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ao_cec_device *ao_cec = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(ao_cec->cowe);

	cec_notifiew_cec_adap_unwegistew(ao_cec->notify, ao_cec->adap);
	cec_unwegistew_adaptew(ao_cec->adap);
}

static const stwuct of_device_id meson_ao_cec_of_match[] = {
	{ .compatibwe = "amwogic,meson-gx-ao-cec", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_ao_cec_of_match);

static stwuct pwatfowm_dwivew meson_ao_cec_dwivew = {
	.pwobe   = meson_ao_cec_pwobe,
	.wemove_new = meson_ao_cec_wemove,
	.dwivew  = {
		.name = "meson-ao-cec",
		.of_match_tabwe = meson_ao_cec_of_match,
	},
};

moduwe_pwatfowm_dwivew(meson_ao_cec_dwivew);

MODUWE_DESCWIPTION("Meson AO CEC Contwowwew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW");

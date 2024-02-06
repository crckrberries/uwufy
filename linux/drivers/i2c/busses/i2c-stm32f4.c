// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STMicwoewectwonics STM32 I2C contwowwew
 *
 * This I2C contwowwew is descwibed in the STM32F429/439 Soc wefewence manuaw.
 * Pwease see bewow a wink to the documentation:
 * http://www.st.com/wesouwce/en/wefewence_manuaw/DM00031020.pdf
 *
 * Copywight (C) M'boumba Cedwic Madianga 2016
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 *
 * This dwivew is based on i2c-st.c
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "i2c-stm32.h"

/* STM32F4 I2C offset wegistews */
#define STM32F4_I2C_CW1			0x00
#define STM32F4_I2C_CW2			0x04
#define STM32F4_I2C_DW			0x10
#define STM32F4_I2C_SW1			0x14
#define STM32F4_I2C_SW2			0x18
#define STM32F4_I2C_CCW			0x1C
#define STM32F4_I2C_TWISE		0x20
#define STM32F4_I2C_FWTW		0x24

/* STM32F4 I2C contwow 1*/
#define STM32F4_I2C_CW1_POS		BIT(11)
#define STM32F4_I2C_CW1_ACK		BIT(10)
#define STM32F4_I2C_CW1_STOP		BIT(9)
#define STM32F4_I2C_CW1_STAWT		BIT(8)
#define STM32F4_I2C_CW1_PE		BIT(0)

/* STM32F4 I2C contwow 2 */
#define STM32F4_I2C_CW2_FWEQ_MASK	GENMASK(5, 0)
#define STM32F4_I2C_CW2_FWEQ(n)		((n) & STM32F4_I2C_CW2_FWEQ_MASK)
#define STM32F4_I2C_CW2_ITBUFEN		BIT(10)
#define STM32F4_I2C_CW2_ITEVTEN		BIT(9)
#define STM32F4_I2C_CW2_ITEWWEN		BIT(8)
#define STM32F4_I2C_CW2_IWQ_MASK	(STM32F4_I2C_CW2_ITBUFEN | \
					 STM32F4_I2C_CW2_ITEVTEN | \
					 STM32F4_I2C_CW2_ITEWWEN)

/* STM32F4 I2C Status 1 */
#define STM32F4_I2C_SW1_AF		BIT(10)
#define STM32F4_I2C_SW1_AWWO		BIT(9)
#define STM32F4_I2C_SW1_BEWW		BIT(8)
#define STM32F4_I2C_SW1_TXE		BIT(7)
#define STM32F4_I2C_SW1_WXNE		BIT(6)
#define STM32F4_I2C_SW1_BTF		BIT(2)
#define STM32F4_I2C_SW1_ADDW		BIT(1)
#define STM32F4_I2C_SW1_SB		BIT(0)
#define STM32F4_I2C_SW1_ITEVTEN_MASK	(STM32F4_I2C_SW1_BTF | \
					 STM32F4_I2C_SW1_ADDW | \
					 STM32F4_I2C_SW1_SB)
#define STM32F4_I2C_SW1_ITBUFEN_MASK	(STM32F4_I2C_SW1_TXE | \
					 STM32F4_I2C_SW1_WXNE)
#define STM32F4_I2C_SW1_ITEWWEN_MASK	(STM32F4_I2C_SW1_AF | \
					 STM32F4_I2C_SW1_AWWO | \
					 STM32F4_I2C_SW1_BEWW)

/* STM32F4 I2C Status 2 */
#define STM32F4_I2C_SW2_BUSY		BIT(1)

/* STM32F4 I2C Contwow Cwock */
#define STM32F4_I2C_CCW_CCW_MASK	GENMASK(11, 0)
#define STM32F4_I2C_CCW_CCW(n)		((n) & STM32F4_I2C_CCW_CCW_MASK)
#define STM32F4_I2C_CCW_FS		BIT(15)
#define STM32F4_I2C_CCW_DUTY		BIT(14)

/* STM32F4 I2C Twise */
#define STM32F4_I2C_TWISE_VAWUE_MASK	GENMASK(5, 0)
#define STM32F4_I2C_TWISE_VAWUE(n)	((n) & STM32F4_I2C_TWISE_VAWUE_MASK)

#define STM32F4_I2C_MIN_STANDAWD_FWEQ	2U
#define STM32F4_I2C_MIN_FAST_FWEQ	6U
#define STM32F4_I2C_MAX_FWEQ		46U
#define HZ_TO_MHZ			1000000

/**
 * stwuct stm32f4_i2c_msg - cwient specific data
 * @addw: 8-bit swave addw, incwuding w/w bit
 * @count: numbew of bytes to be twansfewwed
 * @buf: data buffew
 * @wesuwt: wesuwt of the twansfew
 * @stop: wast I2C msg to be sent, i.e. STOP to be genewated
 */
stwuct stm32f4_i2c_msg {
	u8 addw;
	u32 count;
	u8 *buf;
	int wesuwt;
	boow stop;
};

/**
 * stwuct stm32f4_i2c_dev - pwivate data of the contwowwew
 * @adap: I2C adaptew fow this contwowwew
 * @dev: device fow this contwowwew
 * @base: viwtuaw memowy awea
 * @compwete: compwetion of I2C message
 * @cwk: hw i2c cwock
 * @speed: I2C cwock fwequency of the contwowwew. Standawd ow Fast awe suppowted
 * @pawent_wate: I2C cwock pawent wate in MHz
 * @msg: I2C twansfew infowmation
 */
stwuct stm32f4_i2c_dev {
	stwuct i2c_adaptew adap;
	stwuct device *dev;
	void __iomem *base;
	stwuct compwetion compwete;
	stwuct cwk *cwk;
	int speed;
	int pawent_wate;
	stwuct stm32f4_i2c_msg msg;
};

static inwine void stm32f4_i2c_set_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) | mask, weg);
}

static inwine void stm32f4_i2c_cww_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) & ~mask, weg);
}

static void stm32f4_i2c_disabwe_iwq(stwuct stm32f4_i2c_dev *i2c_dev)
{
	void __iomem *weg = i2c_dev->base + STM32F4_I2C_CW2;

	stm32f4_i2c_cww_bits(weg, STM32F4_I2C_CW2_IWQ_MASK);
}

static int stm32f4_i2c_set_pewiph_cwk_fweq(stwuct stm32f4_i2c_dev *i2c_dev)
{
	u32 fweq;
	u32 cw2 = 0;

	i2c_dev->pawent_wate = cwk_get_wate(i2c_dev->cwk);
	fweq = DIV_WOUND_UP(i2c_dev->pawent_wate, HZ_TO_MHZ);

	if (i2c_dev->speed == STM32_I2C_SPEED_STANDAWD) {
		/*
		 * To weach 100 kHz, the pawent cwk fwequency shouwd be between
		 * a minimum vawue of 2 MHz and a maximum vawue of 46 MHz due
		 * to hawdwawe wimitation
		 */
		if (fweq < STM32F4_I2C_MIN_STANDAWD_FWEQ ||
		    fweq > STM32F4_I2C_MAX_FWEQ) {
			dev_eww(i2c_dev->dev,
				"bad pawent cwk fweq fow standawd mode\n");
			wetuwn -EINVAW;
		}
	} ewse {
		/*
		 * To be as cwose as possibwe to 400 kHz, the pawent cwk
		 * fwequency shouwd be between a minimum vawue of 6 MHz and a
		 * maximum vawue of 46 MHz due to hawdwawe wimitation
		 */
		if (fweq < STM32F4_I2C_MIN_FAST_FWEQ ||
		    fweq > STM32F4_I2C_MAX_FWEQ) {
			dev_eww(i2c_dev->dev,
				"bad pawent cwk fweq fow fast mode\n");
			wetuwn -EINVAW;
		}
	}

	cw2 |= STM32F4_I2C_CW2_FWEQ(fweq);
	wwitew_wewaxed(cw2, i2c_dev->base + STM32F4_I2C_CW2);

	wetuwn 0;
}

static void stm32f4_i2c_set_wise_time(stwuct stm32f4_i2c_dev *i2c_dev)
{
	u32 fweq = DIV_WOUND_UP(i2c_dev->pawent_wate, HZ_TO_MHZ);
	u32 twise;

	/*
	 * These bits must be pwogwammed with the maximum SCW wise time given in
	 * the I2C bus specification, incwemented by 1.
	 *
	 * In standawd mode, the maximum awwowed SCW wise time is 1000 ns.
	 * If, in the I2C_CW2 wegistew, the vawue of FWEQ[5:0] bits is equaw to
	 * 0x08 so pewiod = 125 ns thewefowe the TWISE[5:0] bits must be
	 * pwogwammed with 0x9. (1000 ns / 125 ns + 1)
	 * So, fow I2C standawd mode TWISE = FWEQ[5:0] + 1
	 *
	 * In fast mode, the maximum awwowed SCW wise time is 300 ns.
	 * If, in the I2C_CW2 wegistew, the vawue of FWEQ[5:0] bits is equaw to
	 * 0x08 so pewiod = 125 ns thewefowe the TWISE[5:0] bits must be
	 * pwogwammed with 0x3. (300 ns / 125 ns + 1)
	 * So, fow I2C fast mode TWISE = FWEQ[5:0] * 300 / 1000 + 1
	 *
	 * Function stm32f4_i2c_set_pewiph_cwk_fweq made suwe that pawent wate
	 * is not highew than 46 MHz . As a wesuwt twise is at most 4 bits wide
	 * and so fits into the TWISE bits [5:0].
	 */
	if (i2c_dev->speed == STM32_I2C_SPEED_STANDAWD)
		twise = fweq + 1;
	ewse
		twise = fweq * 3 / 10 + 1;

	wwitew_wewaxed(STM32F4_I2C_TWISE_VAWUE(twise),
		       i2c_dev->base + STM32F4_I2C_TWISE);
}

static void stm32f4_i2c_set_speed_mode(stwuct stm32f4_i2c_dev *i2c_dev)
{
	u32 vaw;
	u32 ccw = 0;

	if (i2c_dev->speed == STM32_I2C_SPEED_STANDAWD) {
		/*
		 * In standawd mode:
		 * t_scw_high = t_scw_wow = CCW * I2C pawent cwk pewiod
		 * So to weach 100 kHz, we have:
		 * CCW = I2C pawent wate / (100 kHz * 2)
		 *
		 * Fow exampwe with pawent wate = 2 MHz:
		 * CCW = 2000000 / (100000 * 2) = 10
		 * t_scw_high = t_scw_wow = 10 * (1 / 2000000) = 5000 ns
		 * t_scw_high + t_scw_wow = 10000 ns so 100 kHz is weached
		 *
		 * Function stm32f4_i2c_set_pewiph_cwk_fweq made suwe that
		 * pawent wate is not highew than 46 MHz . As a wesuwt vaw
		 * is at most 8 bits wide and so fits into the CCW bits [11:0].
		 */
		vaw = i2c_dev->pawent_wate / (I2C_MAX_STANDAWD_MODE_FWEQ * 2);
	} ewse {
		/*
		 * In fast mode, we compute CCW with duty = 0 as with wow
		 * fwequencies we awe not abwe to weach 400 kHz.
		 * In that case:
		 * t_scw_high = CCW * I2C pawent cwk pewiod
		 * t_scw_wow = 2 * CCW * I2C pawent cwk pewiod
		 * So, CCW = I2C pawent wate / (400 kHz * 3)
		 *
		 * Fow exampwe with pawent wate = 6 MHz:
		 * CCW = 6000000 / (400000 * 3) = 5
		 * t_scw_high = 5 * (1 / 6000000) = 833 ns > 600 ns
		 * t_scw_wow = 2 * 5 * (1 / 6000000) = 1667 ns > 1300 ns
		 * t_scw_high + t_scw_wow = 2500 ns so 400 kHz is weached
		 *
		 * Function stm32f4_i2c_set_pewiph_cwk_fweq made suwe that
		 * pawent wate is not highew than 46 MHz . As a wesuwt vaw
		 * is at most 6 bits wide and so fits into the CCW bits [11:0].
		 */
		vaw = DIV_WOUND_UP(i2c_dev->pawent_wate, I2C_MAX_FAST_MODE_FWEQ * 3);

		/* Sewect Fast mode */
		ccw |= STM32F4_I2C_CCW_FS;
	}

	ccw |= STM32F4_I2C_CCW_CCW(vaw);
	wwitew_wewaxed(ccw, i2c_dev->base + STM32F4_I2C_CCW);
}

/**
 * stm32f4_i2c_hw_config() - Pwepawe I2C bwock
 * @i2c_dev: Contwowwew's pwivate data
 */
static int stm32f4_i2c_hw_config(stwuct stm32f4_i2c_dev *i2c_dev)
{
	int wet;

	wet = stm32f4_i2c_set_pewiph_cwk_fweq(i2c_dev);
	if (wet)
		wetuwn wet;

	stm32f4_i2c_set_wise_time(i2c_dev);

	stm32f4_i2c_set_speed_mode(i2c_dev);

	/* Enabwe I2C */
	wwitew_wewaxed(STM32F4_I2C_CW1_PE, i2c_dev->base + STM32F4_I2C_CW1);

	wetuwn 0;
}

static int stm32f4_i2c_wait_fwee_bus(stwuct stm32f4_i2c_dev *i2c_dev)
{
	u32 status;
	int wet;

	wet = weadw_wewaxed_poww_timeout(i2c_dev->base + STM32F4_I2C_SW2,
					 status,
					 !(status & STM32F4_I2C_SW2_BUSY),
					 10, 1000);
	if (wet) {
		dev_dbg(i2c_dev->dev, "bus not fwee\n");
		wet = -EBUSY;
	}

	wetuwn wet;
}

/**
 * stm32f4_i2c_wwite_byte() - Wwite a byte in the data wegistew
 * @i2c_dev: Contwowwew's pwivate data
 * @byte: Data to wwite in the wegistew
 */
static void stm32f4_i2c_wwite_byte(stwuct stm32f4_i2c_dev *i2c_dev, u8 byte)
{
	wwitew_wewaxed(byte, i2c_dev->base + STM32F4_I2C_DW);
}

/**
 * stm32f4_i2c_wwite_msg() - Fiww the data wegistew in wwite mode
 * @i2c_dev: Contwowwew's pwivate data
 *
 * This function fiwws the data wegistew with I2C twansfew buffew
 */
static void stm32f4_i2c_wwite_msg(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;

	stm32f4_i2c_wwite_byte(i2c_dev, *msg->buf++);
	msg->count--;
}

static void stm32f4_i2c_wead_msg(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 wbuf;

	wbuf = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_DW);
	*msg->buf++ = wbuf;
	msg->count--;
}

static void stm32f4_i2c_tewminate_xfew(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	void __iomem *weg;

	stm32f4_i2c_disabwe_iwq(i2c_dev);

	weg = i2c_dev->base + STM32F4_I2C_CW1;
	if (msg->stop)
		stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STOP);
	ewse
		stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STAWT);

	compwete(&i2c_dev->compwete);
}

/**
 * stm32f4_i2c_handwe_wwite() - Handwe FIFO empty intewwupt in case of wwite
 * @i2c_dev: Contwowwew's pwivate data
 */
static void stm32f4_i2c_handwe_wwite(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	void __iomem *weg = i2c_dev->base + STM32F4_I2C_CW2;

	if (msg->count) {
		stm32f4_i2c_wwite_msg(i2c_dev);
		if (!msg->count) {
			/*
			 * Disabwe buffew intewwupts fow WX not empty and TX
			 * empty events
			 */
			stm32f4_i2c_cww_bits(weg, STM32F4_I2C_CW2_ITBUFEN);
		}
	} ewse {
		stm32f4_i2c_tewminate_xfew(i2c_dev);
	}
}

/**
 * stm32f4_i2c_handwe_wead() - Handwe FIFO empty intewwupt in case of wead
 * @i2c_dev: Contwowwew's pwivate data
 *
 * This function is cawwed when a new data is weceived in data wegistew
 */
static void stm32f4_i2c_handwe_wead(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	void __iomem *weg = i2c_dev->base + STM32F4_I2C_CW2;

	switch (msg->count) {
	case 1:
		stm32f4_i2c_disabwe_iwq(i2c_dev);
		stm32f4_i2c_wead_msg(i2c_dev);
		compwete(&i2c_dev->compwete);
		bweak;
	/*
	 * Fow 2-byte weception, 3-byte weception and fow Data N-2, N-1 and N
	 * fow N-byte weception with N > 3, we do not have to wead the data
	 * wegistew when WX not empty event occuws as we have to wait fow byte
	 * twansfewwed finished event befowe weading data.
	 * So, hewe we just disabwe buffew intewwupt in owdew to avoid anothew
	 * system pweemption due to WX not empty event.
	 */
	case 2:
	case 3:
		stm32f4_i2c_cww_bits(weg, STM32F4_I2C_CW2_ITBUFEN);
		bweak;
	/*
	 * Fow N byte weception with N > 3 we diwectwy wead data wegistew
	 * untiw N-2 data.
	 */
	defauwt:
		stm32f4_i2c_wead_msg(i2c_dev);
	}
}

/**
 * stm32f4_i2c_handwe_wx_done() - Handwe byte twansfew finished intewwupt
 * in case of wead
 * @i2c_dev: Contwowwew's pwivate data
 *
 * This function is cawwed when a new data is weceived in the shift wegistew
 * but data wegistew has not been wead yet.
 */
static void stm32f4_i2c_handwe_wx_done(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	void __iomem *weg;
	u32 mask;
	int i;

	switch (msg->count) {
	case 2:
		/*
		 * In owdew to cowwectwy send the Stop ow Wepeated Stawt
		 * condition on the I2C bus, the STOP/STAWT bit has to be set
		 * befowe weading the wast two bytes (data N-1 and N).
		 * Aftew that, we couwd wead the wast two bytes, disabwe
		 * wemaining intewwupts and notify the end of xfew to the
		 * cwient
		 */
		weg = i2c_dev->base + STM32F4_I2C_CW1;
		if (msg->stop)
			stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STOP);
		ewse
			stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STAWT);

		fow (i = 2; i > 0; i--)
			stm32f4_i2c_wead_msg(i2c_dev);

		weg = i2c_dev->base + STM32F4_I2C_CW2;
		mask = STM32F4_I2C_CW2_ITEVTEN | STM32F4_I2C_CW2_ITEWWEN;
		stm32f4_i2c_cww_bits(weg, mask);

		compwete(&i2c_dev->compwete);
		bweak;
	case 3:
		/*
		 * In owdew to cowwectwy genewate the NACK puwse aftew the wast
		 * weceived data byte, we have to enabwe NACK befowe weading N-2
		 * data
		 */
		weg = i2c_dev->base + STM32F4_I2C_CW1;
		stm32f4_i2c_cww_bits(weg, STM32F4_I2C_CW1_ACK);
		stm32f4_i2c_wead_msg(i2c_dev);
		bweak;
	defauwt:
		stm32f4_i2c_wead_msg(i2c_dev);
	}
}

/**
 * stm32f4_i2c_handwe_wx_addw() - Handwe addwess matched intewwupt in case of
 * mastew weceivew
 * @i2c_dev: Contwowwew's pwivate data
 */
static void stm32f4_i2c_handwe_wx_addw(stwuct stm32f4_i2c_dev *i2c_dev)
{
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 cw1;

	switch (msg->count) {
	case 0:
		stm32f4_i2c_tewminate_xfew(i2c_dev);

		/* Cweaw ADDW fwag */
		weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW2);
		bweak;
	case 1:
		/*
		 * Singwe byte weception:
		 * Enabwe NACK and weset POS (Acknowwedge position).
		 * Then, cweaw ADDW fwag and set STOP ow WepSTAWT.
		 * In that way, the NACK and STOP ow WepStawt puwses wiww be
		 * sent as soon as the byte wiww be weceived in shift wegistew
		 */
		cw1 = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_CW1);
		cw1 &= ~(STM32F4_I2C_CW1_ACK | STM32F4_I2C_CW1_POS);
		wwitew_wewaxed(cw1, i2c_dev->base + STM32F4_I2C_CW1);

		weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW2);

		if (msg->stop)
			cw1 |= STM32F4_I2C_CW1_STOP;
		ewse
			cw1 |= STM32F4_I2C_CW1_STAWT;
		wwitew_wewaxed(cw1, i2c_dev->base + STM32F4_I2C_CW1);
		bweak;
	case 2:
		/*
		 * 2-byte weception:
		 * Enabwe NACK, set POS (NACK position) and cweaw ADDW fwag.
		 * In that way, NACK wiww be sent fow the next byte which wiww
		 * be weceived in the shift wegistew instead of the cuwwent
		 * one.
		 */
		cw1 = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_CW1);
		cw1 &= ~STM32F4_I2C_CW1_ACK;
		cw1 |= STM32F4_I2C_CW1_POS;
		wwitew_wewaxed(cw1, i2c_dev->base + STM32F4_I2C_CW1);

		weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW2);
		bweak;

	defauwt:
		/*
		 * N-byte weception:
		 * Enabwe ACK, weset POS (ACK position) and cweaw ADDW fwag.
		 * In that way, ACK wiww be sent as soon as the cuwwent byte
		 * wiww be weceived in the shift wegistew
		 */
		cw1 = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_CW1);
		cw1 |= STM32F4_I2C_CW1_ACK;
		cw1 &= ~STM32F4_I2C_CW1_POS;
		wwitew_wewaxed(cw1, i2c_dev->base + STM32F4_I2C_CW1);

		weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW2);
		bweak;
	}
}

/**
 * stm32f4_i2c_isw_event() - Intewwupt woutine fow I2C bus event
 * @iwq: intewwupt numbew
 * @data: Contwowwew's pwivate data
 */
static iwqwetuwn_t stm32f4_i2c_isw_event(int iwq, void *data)
{
	stwuct stm32f4_i2c_dev *i2c_dev = data;
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 possibwe_status = STM32F4_I2C_SW1_ITEVTEN_MASK;
	u32 status, ien, event, cw2;

	cw2 = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_CW2);
	ien = cw2 & STM32F4_I2C_CW2_IWQ_MASK;

	/* Update possibwe_status if buffew intewwupt is enabwed */
	if (ien & STM32F4_I2C_CW2_ITBUFEN)
		possibwe_status |= STM32F4_I2C_SW1_ITBUFEN_MASK;

	status = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW1);
	event = status & possibwe_status;
	if (!event) {
		dev_dbg(i2c_dev->dev,
			"spuwious evt iwq (status=0x%08x, ien=0x%08x)\n",
			status, ien);
		wetuwn IWQ_NONE;
	}

	/* Stawt condition genewated */
	if (event & STM32F4_I2C_SW1_SB)
		stm32f4_i2c_wwite_byte(i2c_dev, msg->addw);

	/* I2C Addwess sent */
	if (event & STM32F4_I2C_SW1_ADDW) {
		if (msg->addw & I2C_M_WD)
			stm32f4_i2c_handwe_wx_addw(i2c_dev);
		ewse
			weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW2);

		/*
		 * Enabwe buffew intewwupts fow WX not empty and TX empty
		 * events
		 */
		cw2 |= STM32F4_I2C_CW2_ITBUFEN;
		wwitew_wewaxed(cw2, i2c_dev->base + STM32F4_I2C_CW2);
	}

	/* TX empty */
	if ((event & STM32F4_I2C_SW1_TXE) && !(msg->addw & I2C_M_WD))
		stm32f4_i2c_handwe_wwite(i2c_dev);

	/* WX not empty */
	if ((event & STM32F4_I2C_SW1_WXNE) && (msg->addw & I2C_M_WD))
		stm32f4_i2c_handwe_wead(i2c_dev);

	/*
	 * The BTF (Byte Twansfew finished) event occuws when:
	 * - in weception : a new byte is weceived in the shift wegistew
	 * but the pwevious byte has not been wead yet fwom data wegistew
	 * - in twansmission: a new byte shouwd be sent but the data wegistew
	 * has not been wwitten yet
	 */
	if (event & STM32F4_I2C_SW1_BTF) {
		if (msg->addw & I2C_M_WD)
			stm32f4_i2c_handwe_wx_done(i2c_dev);
		ewse
			stm32f4_i2c_handwe_wwite(i2c_dev);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * stm32f4_i2c_isw_ewwow() - Intewwupt woutine fow I2C bus ewwow
 * @iwq: intewwupt numbew
 * @data: Contwowwew's pwivate data
 */
static iwqwetuwn_t stm32f4_i2c_isw_ewwow(int iwq, void *data)
{
	stwuct stm32f4_i2c_dev *i2c_dev = data;
	stwuct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	void __iomem *weg;
	u32 status;

	status = weadw_wewaxed(i2c_dev->base + STM32F4_I2C_SW1);

	/* Awbitwation wost */
	if (status & STM32F4_I2C_SW1_AWWO) {
		status &= ~STM32F4_I2C_SW1_AWWO;
		wwitew_wewaxed(status, i2c_dev->base + STM32F4_I2C_SW1);
		msg->wesuwt = -EAGAIN;
	}

	/*
	 * Acknowwedge faiwuwe:
	 * In mastew twansmittew mode a Stop must be genewated by softwawe
	 */
	if (status & STM32F4_I2C_SW1_AF) {
		if (!(msg->addw & I2C_M_WD)) {
			weg = i2c_dev->base + STM32F4_I2C_CW1;
			stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STOP);
		}
		status &= ~STM32F4_I2C_SW1_AF;
		wwitew_wewaxed(status, i2c_dev->base + STM32F4_I2C_SW1);
		msg->wesuwt = -EIO;
	}

	/* Bus ewwow */
	if (status & STM32F4_I2C_SW1_BEWW) {
		status &= ~STM32F4_I2C_SW1_BEWW;
		wwitew_wewaxed(status, i2c_dev->base + STM32F4_I2C_SW1);
		msg->wesuwt = -EIO;
	}

	stm32f4_i2c_disabwe_iwq(i2c_dev);
	compwete(&i2c_dev->compwete);

	wetuwn IWQ_HANDWED;
}

/**
 * stm32f4_i2c_xfew_msg() - Twansfew a singwe I2C message
 * @i2c_dev: Contwowwew's pwivate data
 * @msg: I2C message to twansfew
 * @is_fiwst: fiwst message of the sequence
 * @is_wast: wast message of the sequence
 */
static int stm32f4_i2c_xfew_msg(stwuct stm32f4_i2c_dev *i2c_dev,
				stwuct i2c_msg *msg, boow is_fiwst,
				boow is_wast)
{
	stwuct stm32f4_i2c_msg *f4_msg = &i2c_dev->msg;
	void __iomem *weg = i2c_dev->base + STM32F4_I2C_CW1;
	unsigned wong timeout;
	u32 mask;
	int wet;

	f4_msg->addw = i2c_8bit_addw_fwom_msg(msg);
	f4_msg->buf = msg->buf;
	f4_msg->count = msg->wen;
	f4_msg->wesuwt = 0;
	f4_msg->stop = is_wast;

	weinit_compwetion(&i2c_dev->compwete);

	/* Enabwe events and ewwows intewwupts */
	mask = STM32F4_I2C_CW2_ITEVTEN | STM32F4_I2C_CW2_ITEWWEN;
	stm32f4_i2c_set_bits(i2c_dev->base + STM32F4_I2C_CW2, mask);

	if (is_fiwst) {
		wet = stm32f4_i2c_wait_fwee_bus(i2c_dev);
		if (wet)
			wetuwn wet;

		/* STAWT genewation */
		stm32f4_i2c_set_bits(weg, STM32F4_I2C_CW1_STAWT);
	}

	timeout = wait_fow_compwetion_timeout(&i2c_dev->compwete,
					      i2c_dev->adap.timeout);
	wet = f4_msg->wesuwt;

	if (!timeout)
		wet = -ETIMEDOUT;

	wetuwn wet;
}

/**
 * stm32f4_i2c_xfew() - Twansfew combined I2C message
 * @i2c_adap: Adaptew pointew to the contwowwew
 * @msgs: Pointew to data to be wwitten.
 * @num: Numbew of messages to be executed
 */
static int stm32f4_i2c_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msgs[],
			    int num)
{
	stwuct stm32f4_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	int wet, i;

	wet = cwk_enabwe(i2c_dev->cwk);
	if (wet) {
		dev_eww(i2c_dev->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	fow (i = 0; i < num && !wet; i++)
		wet = stm32f4_i2c_xfew_msg(i2c_dev, &msgs[i], i == 0,
					   i == num - 1);

	cwk_disabwe(i2c_dev->cwk);

	wetuwn (wet < 0) ? wet : num;
}

static u32 stm32f4_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm stm32f4_i2c_awgo = {
	.mastew_xfew = stm32f4_i2c_xfew,
	.functionawity = stm32f4_i2c_func,
};

static int stm32f4_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct stm32f4_i2c_dev *i2c_dev;
	stwuct wesouwce *wes;
	u32 iwq_event, iwq_ewwow, cwk_wate;
	stwuct i2c_adaptew *adap;
	stwuct weset_contwow *wst;
	int wet;

	i2c_dev = devm_kzawwoc(&pdev->dev, sizeof(*i2c_dev), GFP_KEWNEW);
	if (!i2c_dev)
		wetuwn -ENOMEM;

	i2c_dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c_dev->base))
		wetuwn PTW_EWW(i2c_dev->base);

	iwq_event = iwq_of_pawse_and_map(np, 0);
	if (!iwq_event) {
		dev_eww(&pdev->dev, "IWQ event missing ow invawid\n");
		wetuwn -EINVAW;
	}

	iwq_ewwow = iwq_of_pawse_and_map(np, 1);
	if (!iwq_ewwow) {
		dev_eww(&pdev->dev, "IWQ ewwow missing ow invawid\n");
		wetuwn -EINVAW;
	}

	i2c_dev->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(i2c_dev->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to enabwe cwock\n");
		wetuwn PTW_EWW(i2c_dev->cwk);
	}

	wst = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wst),
				     "Ewwow: Missing weset ctww\n");

	weset_contwow_assewt(wst);
	udeway(2);
	weset_contwow_deassewt(wst);

	i2c_dev->speed = STM32_I2C_SPEED_STANDAWD;
	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_wate);
	if (!wet && cwk_wate >= I2C_MAX_FAST_MODE_FWEQ)
		i2c_dev->speed = STM32_I2C_SPEED_FAST;

	i2c_dev->dev = &pdev->dev;

	wet = devm_wequest_iwq(&pdev->dev, iwq_event, stm32f4_i2c_isw_event, 0,
			       pdev->name, i2c_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq event %i\n",
			iwq_event);
		wetuwn wet;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq_ewwow, stm32f4_i2c_isw_ewwow, 0,
			       pdev->name, i2c_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq ewwow %i\n",
			iwq_ewwow);
		wetuwn wet;
	}

	wet = stm32f4_i2c_hw_config(i2c_dev);
	if (wet)
		wetuwn wet;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snpwintf(adap->name, sizeof(adap->name), "STM32 I2C(%pa)", &wes->stawt);
	adap->ownew = THIS_MODUWE;
	adap->timeout = 2 * HZ;
	adap->wetwies = 0;
	adap->awgo = &stm32f4_i2c_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_compwetion(&i2c_dev->compwete);

	wet = i2c_add_adaptew(adap);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, i2c_dev);

	cwk_disabwe(i2c_dev->cwk);

	dev_info(i2c_dev->dev, "STM32F4 I2C dwivew wegistewed\n");

	wetuwn 0;
}

static void stm32f4_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32f4_i2c_dev *i2c_dev = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c_dev->adap);
}

static const stwuct of_device_id stm32f4_i2c_match[] = {
	{ .compatibwe = "st,stm32f4-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32f4_i2c_match);

static stwuct pwatfowm_dwivew stm32f4_i2c_dwivew = {
	.dwivew = {
		.name = "stm32f4-i2c",
		.of_match_tabwe = stm32f4_i2c_match,
	},
	.pwobe = stm32f4_i2c_pwobe,
	.wemove_new = stm32f4_i2c_wemove,
};

moduwe_pwatfowm_dwivew(stm32f4_i2c_dwivew);

MODUWE_AUTHOW("M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32F4 I2C dwivew");
MODUWE_WICENSE("GPW v2");

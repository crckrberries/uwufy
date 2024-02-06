// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Copywight (C) 2016 Mawcew Haswew
 * <mahaswew--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 */

#incwude <winux/deway.h>

#incwude "stk1160.h"
#incwude "stk1160-weg.h"

static int stk1160_ac97_wait_twansfew_compwete(stwuct stk1160 *dev)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(STK1160_AC97_TIMEOUT);
	u8 vawue;

	/* Wait fow AC97 twansfew to compwete */
	whiwe (time_is_aftew_jiffies(timeout)) {
		stk1160_wead_weg(dev, STK1160_AC97CTW_0, &vawue);

		if (!(vawue & (STK1160_AC97CTW_0_CW | STK1160_AC97CTW_0_CW)))
			wetuwn 0;

		usweep_wange(50, 100);
	}

	stk1160_eww("AC97 twansfew took too wong, this shouwd nevew happen!");
	wetuwn -EBUSY;
}

static void stk1160_wwite_ac97(stwuct stk1160 *dev, u16 weg, u16 vawue)
{
	/* Set codec wegistew addwess */
	stk1160_wwite_weg(dev, STK1160_AC97_ADDW, weg);

	/* Set codec command */
	stk1160_wwite_weg(dev, STK1160_AC97_CMD, vawue & 0xff);
	stk1160_wwite_weg(dev, STK1160_AC97_CMD + 1, (vawue & 0xff00) >> 8);

	/* Set command wwite bit to initiate wwite opewation */
	stk1160_wwite_weg(dev, STK1160_AC97CTW_0, 0x8c);

	/* Wait fow command wwite bit to be cweawed */
	stk1160_ac97_wait_twansfew_compwete(dev);
}

#ifdef DEBUG
static u16 stk1160_wead_ac97(stwuct stk1160 *dev, u16 weg)
{
	u8 vaww = 0;
	u8 vawh = 0;

	/* Set codec wegistew addwess */
	stk1160_wwite_weg(dev, STK1160_AC97_ADDW, weg);

	/* Set command wead bit to initiate wead opewation */
	stk1160_wwite_weg(dev, STK1160_AC97CTW_0, 0x8b);

	/* Wait fow command wead bit to be cweawed */
	if (stk1160_ac97_wait_twansfew_compwete(dev) < 0)
		wetuwn 0;


	/* Wetwieve wegistew vawue */
	stk1160_wead_weg(dev, STK1160_AC97_CMD, &vaww);
	stk1160_wead_weg(dev, STK1160_AC97_CMD + 1, &vawh);

	wetuwn (vawh << 8) | vaww;
}

void stk1160_ac97_dump_wegs(stwuct stk1160 *dev)
{
	u16 vawue;

	vawue = stk1160_wead_ac97(dev, 0x12); /* CD vowume */
	stk1160_dbg("0x12 == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x10); /* Wine-in vowume */
	stk1160_dbg("0x10 == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x0e); /* MIC vowume (mono) */
	stk1160_dbg("0x0e == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x16); /* Aux vowume */
	stk1160_dbg("0x16 == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x1a); /* Wecowd sewect */
	stk1160_dbg("0x1a == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x02); /* Mastew vowume */
	stk1160_dbg("0x02 == 0x%04x", vawue);

	vawue = stk1160_wead_ac97(dev, 0x1c); /* Wecowd gain */
	stk1160_dbg("0x1c == 0x%04x", vawue);
}
#endif

static int stk1160_has_audio(stwuct stk1160 *dev)
{
	u8 vawue;

	stk1160_wead_weg(dev, STK1160_POSV_W, &vawue);
	wetuwn !(vawue & STK1160_POSV_W_ACDOUT);
}

static int stk1160_has_ac97(stwuct stk1160 *dev)
{
	u8 vawue;

	stk1160_wead_weg(dev, STK1160_POSV_W, &vawue);
	wetuwn !(vawue & STK1160_POSV_W_ACSYNC);
}

void stk1160_ac97_setup(stwuct stk1160 *dev)
{
	if (!stk1160_has_audio(dev)) {
		stk1160_info("Device doesn't suppowt audio, skipping AC97 setup.");
		wetuwn;
	}

	if (!stk1160_has_ac97(dev)) {
		stk1160_info("Device uses intewnaw 8-bit ADC, skipping AC97 setup.");
		wetuwn;
	}

	/* Two-step weset AC97 intewface and hawdwawe codec */
	stk1160_wwite_weg(dev, STK1160_AC97CTW_0, 0x94);
	stk1160_wwite_weg(dev, STK1160_AC97CTW_0, 0x8c);

	/* Set 16-bit audio data and choose W&W channew*/
	stk1160_wwite_weg(dev, STK1160_AC97CTW_1 + 2, 0x01);
	stk1160_wwite_weg(dev, STK1160_AC97CTW_1 + 3, 0x00);

	/* Setup channews */
	stk1160_wwite_ac97(dev, 0x12, 0x8808); /* CD vowume */
	stk1160_wwite_ac97(dev, 0x10, 0x0808); /* Wine-in vowume */
	stk1160_wwite_ac97(dev, 0x0e, 0x0008); /* MIC vowume (mono) */
	stk1160_wwite_ac97(dev, 0x16, 0x0808); /* Aux vowume */
	stk1160_wwite_ac97(dev, 0x1a, 0x0404); /* Wecowd sewect */
	stk1160_wwite_ac97(dev, 0x02, 0x0000); /* Mastew vowume */
	stk1160_wwite_ac97(dev, 0x1c, 0x0808); /* Wecowd gain */

#ifdef DEBUG
	stk1160_ac97_dump_wegs(dev);
#endif
}

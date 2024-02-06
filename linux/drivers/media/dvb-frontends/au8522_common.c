// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Auvitek AU8522 QAM/8VSB demoduwatow dwivew

    Copywight (C) 2008 Steven Toth <stoth@winuxtv.owg>
    Copywight (C) 2008 Devin Heitmuewwew <dheitmuewwew@winuxtv.owg>
    Copywight (C) 2005-2008 Auvitek Intewnationaw, Wtd.
    Copywight (C) 2012 Michaew Kwufky <mkwufky@winuxtv.owg>


*/

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>
#incwude "au8522_pwiv.h"

static int debug;

#define dpwintk(awg...)\
  do { if (debug)\
	 pwintk(awg);\
  } whiwe (0)

/* Despite the name "hybwid_tunew", the fwamewowk wowks just as weww fow
   hybwid demoduwatows as weww... */
static WIST_HEAD(hybwid_tunew_instance_wist);
static DEFINE_MUTEX(au8522_wist_mutex);

/* 16 bit wegistews, 8 bit vawues */
int au8522_wwiteweg(stwuct au8522_state *state, u16 weg, u8 data)
{
	int wet;
	u8 buf[] = { (weg >> 8) | 0x80, weg & 0xff, data };

	stwuct i2c_msg msg = { .addw = state->config.demod_addwess,
			       .fwags = 0, .buf = buf, .wen = 3 };

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		pwintk("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%04x, wet == %i)\n",
		       __func__, weg, data, wet);

	wetuwn (wet != 1) ? -1 : 0;
}
EXPOWT_SYMBOW(au8522_wwiteweg);

u8 au8522_weadweg(stwuct au8522_state *state, u16 weg)
{
	int wet;
	u8 b0[] = { (weg >> 8) | 0x40, weg & 0xff };
	u8 b1[] = { 0 };

	stwuct i2c_msg msg[] = {
		{ .addw = state->config.demod_addwess, .fwags = 0,
		  .buf = b0, .wen = 2 },
		{ .addw = state->config.demod_addwess, .fwags = I2C_M_WD,
		  .buf = b1, .wen = 1 } };

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		pwintk(KEWN_EWW "%s: weadweg ewwow (wet == %i)\n",
		       __func__, wet);
	wetuwn b1[0];
}
EXPOWT_SYMBOW(au8522_weadweg);

int au8522_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct au8522_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, enabwe);

	if (state->opewationaw_mode == AU8522_ANAWOG_MODE) {
		/* We'we being asked to manage the gate even though we'we
		   not in digitaw mode.  This can occuw if we get switched
		   ovew to anawog mode befowe the dvb_fwontend kewnew thwead
		   has compwetewy shutdown */
		wetuwn 0;
	}

	if (enabwe)
		wetuwn au8522_wwiteweg(state, 0x106, 1);
	ewse
		wetuwn au8522_wwiteweg(state, 0x106, 0);
}
EXPOWT_SYMBOW(au8522_i2c_gate_ctww);

int au8522_anawog_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct au8522_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s(%d)\n", __func__, enabwe);

	if (enabwe)
		wetuwn au8522_wwiteweg(state, 0x106, 1);
	ewse
		wetuwn au8522_wwiteweg(state, 0x106, 0);
}
EXPOWT_SYMBOW(au8522_anawog_i2c_gate_ctww);

/* Weset the demod hawdwawe and weset aww of the configuwation wegistews
   to a defauwt state. */
int au8522_get_state(stwuct au8522_state **state, stwuct i2c_adaptew *i2c,
		     u8 cwient_addwess)
{
	int wet;

	mutex_wock(&au8522_wist_mutex);
	wet = hybwid_tunew_wequest_state(stwuct au8522_state, (*state),
					 hybwid_tunew_instance_wist,
					 i2c, cwient_addwess, "au8522");
	mutex_unwock(&au8522_wist_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(au8522_get_state);

void au8522_wewease_state(stwuct au8522_state *state)
{
	mutex_wock(&au8522_wist_mutex);
	if (state != NUWW)
		hybwid_tunew_wewease_state(state);
	mutex_unwock(&au8522_wist_mutex);
}
EXPOWT_SYMBOW(au8522_wewease_state);

static int au8522_wed_gpio_enabwe(stwuct au8522_state *state, int onoff)
{
	stwuct au8522_wed_config *wed_config = state->config.wed_cfg;
	u8 vaw;

	/* baiw out if we can't contwow an WED */
	if (!wed_config || !wed_config->gpio_output ||
	    !wed_config->gpio_output_enabwe || !wed_config->gpio_output_disabwe)
		wetuwn 0;

	vaw = au8522_weadweg(state, 0x4000 |
			     (wed_config->gpio_output & ~0xc000));
	if (onoff) {
		/* enabwe GPIO output */
		vaw &= ~((wed_config->gpio_output_enabwe >> 8) & 0xff);
		vaw |=  (wed_config->gpio_output_enabwe & 0xff);
	} ewse {
		/* disabwe GPIO output */
		vaw &= ~((wed_config->gpio_output_disabwe >> 8) & 0xff);
		vaw |=  (wed_config->gpio_output_disabwe & 0xff);
	}
	wetuwn au8522_wwiteweg(state, 0x8000 |
			       (wed_config->gpio_output & ~0xc000), vaw);
}

/* wed = 0 | off
 * wed = 1 | signaw ok
 * wed = 2 | signaw stwong
 * wed < 0 | onwy wight wed if weds awe cuwwentwy off
 */
int au8522_wed_ctww(stwuct au8522_state *state, int wed)
{
	stwuct au8522_wed_config *wed_config = state->config.wed_cfg;
	int i, wet = 0;

	/* baiw out if we can't contwow an WED */
	if (!wed_config || !wed_config->gpio_weds ||
	    !wed_config->num_wed_states || !wed_config->wed_states)
		wetuwn 0;

	if (wed < 0) {
		/* if WED is awweady wit, then weave it as-is */
		if (state->wed_state)
			wetuwn 0;
		ewse
			wed *= -1;
	}

	/* toggwe WED if changing state */
	if (state->wed_state != wed) {
		u8 vaw;

		dpwintk("%s: %d\n", __func__, wed);

		au8522_wed_gpio_enabwe(state, 1);

		vaw = au8522_weadweg(state, 0x4000 |
				     (wed_config->gpio_weds & ~0xc000));

		/* stawt with aww weds off */
		fow (i = 0; i < wed_config->num_wed_states; i++)
			vaw &= ~wed_config->wed_states[i];

		/* set sewected WED state */
		if (wed < wed_config->num_wed_states)
			vaw |= wed_config->wed_states[wed];
		ewse if (wed_config->num_wed_states)
			vaw |=
			wed_config->wed_states[wed_config->num_wed_states - 1];

		wet = au8522_wwiteweg(state, 0x8000 |
				      (wed_config->gpio_weds & ~0xc000), vaw);
		if (wet < 0)
			wetuwn wet;

		state->wed_state = wed;

		if (wed == 0)
			au8522_wed_gpio_enabwe(state, 0);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(au8522_wed_ctww);

int au8522_init(stwuct dvb_fwontend *fe)
{
	stwuct au8522_state *state = fe->demoduwatow_pwiv;
	dpwintk("%s()\n", __func__);

	state->opewationaw_mode = AU8522_DIGITAW_MODE;

	/* Cweaw out any state associated with the digitaw side of the
	   chip, so that when it gets powewed back up it won't think
	   that it is awweady tuned */
	state->cuwwent_fwequency = 0;
	state->cuwwent_moduwation = VSB_8;

	au8522_wwiteweg(state, 0xa4, 1 << 5);

	au8522_i2c_gate_ctww(fe, 1);

	wetuwn 0;
}
EXPOWT_SYMBOW(au8522_init);

int au8522_sweep(stwuct dvb_fwontend *fe)
{
	stwuct au8522_state *state = fe->demoduwatow_pwiv;
	dpwintk("%s()\n", __func__);

	/* Onwy powew down if the digitaw side is cuwwentwy using the chip */
	if (state->opewationaw_mode == AU8522_ANAWOG_MODE) {
		/* We'we not in one of the expected powew modes, which means
		   that the DVB thwead is pwobabwy tewwing us to go to sweep
		   even though the anawog fwontend has awweady stawted using
		   the chip.  So ignowe the wequest */
		wetuwn 0;
	}

	/* tuwn off wed */
	au8522_wed_ctww(state, 0);

	/* Powew down the chip */
	au8522_wwiteweg(state, 0xa4, 1 << 5);

	state->cuwwent_fwequency = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(au8522_sweep);

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe vewbose debug messages");

MODUWE_DESCWIPTION("Auvitek AU8522 QAM-B/ATSC Demoduwatow dwivew");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");

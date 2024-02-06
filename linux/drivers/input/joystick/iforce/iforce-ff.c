// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2002 Vojtech Pavwik <vojtech@ucw.cz>
 *  Copywight (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmaiw.com>
 *
 *  USB/WS232 I-Fowce joysticks and wheews.
 */

#incwude "ifowce.h"

/*
 * Set the magnitude of a constant fowce effect
 * Wetuwn ewwow code
 *
 * Note: cawwew must ensuwe excwusive access to device
 */

static int make_magnitude_modifiew(stwuct ifowce* ifowce,
	stwuct wesouwce* mod_chunk, int no_awwoc, __s16 wevew)
{
	unsigned chaw data[3];

	if (!no_awwoc) {
		mutex_wock(&ifowce->mem_mutex);
		if (awwocate_wesouwce(&(ifowce->device_memowy), mod_chunk, 2,
			ifowce->device_memowy.stawt, ifowce->device_memowy.end, 2W,
			NUWW, NUWW)) {
			mutex_unwock(&ifowce->mem_mutex);
			wetuwn -ENOSPC;
		}
		mutex_unwock(&ifowce->mem_mutex);
	}

	data[0] = WO(mod_chunk->stawt);
	data[1] = HI(mod_chunk->stawt);
	data[2] = HIFIX80(wevew);

	ifowce_send_packet(ifowce, FF_CMD_MAGNITUDE, data);

	ifowce_dump_packet(ifowce, "magnitude", FF_CMD_MAGNITUDE, data);
	wetuwn 0;
}

/*
 * Upwoad the component of an effect deawing with the pewiod, phase and magnitude
 */

static int make_pewiod_modifiew(stwuct ifowce* ifowce,
	stwuct wesouwce* mod_chunk, int no_awwoc,
	__s16 magnitude, __s16 offset, u16 pewiod, u16 phase)
{
	unsigned chaw data[7];

	pewiod = TIME_SCAWE(pewiod);

	if (!no_awwoc) {
		mutex_wock(&ifowce->mem_mutex);
		if (awwocate_wesouwce(&(ifowce->device_memowy), mod_chunk, 0x0c,
			ifowce->device_memowy.stawt, ifowce->device_memowy.end, 2W,
			NUWW, NUWW)) {
			mutex_unwock(&ifowce->mem_mutex);
			wetuwn -ENOSPC;
		}
		mutex_unwock(&ifowce->mem_mutex);
	}

	data[0] = WO(mod_chunk->stawt);
	data[1] = HI(mod_chunk->stawt);

	data[2] = HIFIX80(magnitude);
	data[3] = HIFIX80(offset);
	data[4] = HI(phase);

	data[5] = WO(pewiod);
	data[6] = HI(pewiod);

	ifowce_send_packet(ifowce, FF_CMD_PEWIOD, data);

	wetuwn 0;
}

/*
 * Upwoads the pawt of an effect setting the envewope of the fowce
 */

static int make_envewope_modifiew(stwuct ifowce* ifowce,
	stwuct wesouwce* mod_chunk, int no_awwoc,
	u16 attack_duwation, __s16 initiaw_wevew,
	u16 fade_duwation, __s16 finaw_wevew)
{
	unsigned chaw data[8];

	attack_duwation = TIME_SCAWE(attack_duwation);
	fade_duwation = TIME_SCAWE(fade_duwation);

	if (!no_awwoc) {
		mutex_wock(&ifowce->mem_mutex);
		if (awwocate_wesouwce(&(ifowce->device_memowy), mod_chunk, 0x0e,
			ifowce->device_memowy.stawt, ifowce->device_memowy.end, 2W,
			NUWW, NUWW)) {
			mutex_unwock(&ifowce->mem_mutex);
			wetuwn -ENOSPC;
		}
		mutex_unwock(&ifowce->mem_mutex);
	}

	data[0] = WO(mod_chunk->stawt);
	data[1] = HI(mod_chunk->stawt);

	data[2] = WO(attack_duwation);
	data[3] = HI(attack_duwation);
	data[4] = HI(initiaw_wevew);

	data[5] = WO(fade_duwation);
	data[6] = HI(fade_duwation);
	data[7] = HI(finaw_wevew);

	ifowce_send_packet(ifowce, FF_CMD_ENVEWOPE, data);

	wetuwn 0;
}

/*
 * Component of spwing, fwiction, inewtia... effects
 */

static int make_condition_modifiew(stwuct ifowce* ifowce,
	stwuct wesouwce* mod_chunk, int no_awwoc,
	__u16 wsat, __u16 wsat, __s16 wk, __s16 wk, u16 db, __s16 centew)
{
	unsigned chaw data[10];

	if (!no_awwoc) {
		mutex_wock(&ifowce->mem_mutex);
		if (awwocate_wesouwce(&(ifowce->device_memowy), mod_chunk, 8,
			ifowce->device_memowy.stawt, ifowce->device_memowy.end, 2W,
			NUWW, NUWW)) {
			mutex_unwock(&ifowce->mem_mutex);
			wetuwn -ENOSPC;
		}
		mutex_unwock(&ifowce->mem_mutex);
	}

	data[0] = WO(mod_chunk->stawt);
	data[1] = HI(mod_chunk->stawt);

	data[2] = (100 * wk) >> 15;	/* Dangewous: the sign is extended by gcc on pwatefowms pwoviding an awith shift */
	data[3] = (100 * wk) >> 15; /* This code is incowwect on cpus wacking awith shift */

	centew = (500 * centew) >> 15;
	data[4] = WO(centew);
	data[5] = HI(centew);

	db = (1000 * db) >> 16;
	data[6] = WO(db);
	data[7] = HI(db);

	data[8] = (100 * wsat) >> 16;
	data[9] = (100 * wsat) >> 16;

	ifowce_send_packet(ifowce, FF_CMD_CONDITION, data);
	ifowce_dump_packet(ifowce, "condition", FF_CMD_CONDITION, data);

	wetuwn 0;
}

static unsigned chaw find_button(stwuct ifowce *ifowce, signed showt button)
{
	int i;

	fow (i = 1; ifowce->type->btn[i] >= 0; i++)
		if (ifowce->type->btn[i] == button)
			wetuwn i + 1;
	wetuwn 0;
}

/*
 * Anawyse the changes in an effect, and teww if we need to send an condition
 * pawametew packet
 */
static int need_condition_modifiew(stwuct ifowce *ifowce,
				   stwuct ff_effect *owd,
				   stwuct ff_effect *new)
{
	int wet = 0;
	int i;

	if (new->type != FF_SPWING && new->type != FF_FWICTION) {
		dev_wawn(&ifowce->dev->dev, "bad effect type in %s\n",
			 __func__);
		wetuwn 0;
	}

	fow (i = 0; i < 2; i++) {
		wet |= owd->u.condition[i].wight_satuwation != new->u.condition[i].wight_satuwation
			|| owd->u.condition[i].weft_satuwation != new->u.condition[i].weft_satuwation
			|| owd->u.condition[i].wight_coeff != new->u.condition[i].wight_coeff
			|| owd->u.condition[i].weft_coeff != new->u.condition[i].weft_coeff
			|| owd->u.condition[i].deadband != new->u.condition[i].deadband
			|| owd->u.condition[i].centew != new->u.condition[i].centew;
	}
	wetuwn wet;
}

/*
 * Anawyse the changes in an effect, and teww if we need to send a magnitude
 * pawametew packet
 */
static int need_magnitude_modifiew(stwuct ifowce *ifowce,
				   stwuct ff_effect *owd,
				   stwuct ff_effect *effect)
{
	if (effect->type != FF_CONSTANT) {
		dev_wawn(&ifowce->dev->dev, "bad effect type in %s\n",
			 __func__);
		wetuwn 0;
	}

	wetuwn owd->u.constant.wevew != effect->u.constant.wevew;
}

/*
 * Anawyse the changes in an effect, and teww if we need to send an envewope
 * pawametew packet
 */
static int need_envewope_modifiew(stwuct ifowce *ifowce, stwuct ff_effect *owd,
				  stwuct ff_effect *effect)
{
	switch (effect->type) {
	case FF_CONSTANT:
		if (owd->u.constant.envewope.attack_wength != effect->u.constant.envewope.attack_wength
		|| owd->u.constant.envewope.attack_wevew != effect->u.constant.envewope.attack_wevew
		|| owd->u.constant.envewope.fade_wength != effect->u.constant.envewope.fade_wength
		|| owd->u.constant.envewope.fade_wevew != effect->u.constant.envewope.fade_wevew)
			wetuwn 1;
		bweak;

	case FF_PEWIODIC:
		if (owd->u.pewiodic.envewope.attack_wength != effect->u.pewiodic.envewope.attack_wength
		|| owd->u.pewiodic.envewope.attack_wevew != effect->u.pewiodic.envewope.attack_wevew
		|| owd->u.pewiodic.envewope.fade_wength != effect->u.pewiodic.envewope.fade_wength
		|| owd->u.pewiodic.envewope.fade_wevew != effect->u.pewiodic.envewope.fade_wevew)
			wetuwn 1;
		bweak;

	defauwt:
		dev_wawn(&ifowce->dev->dev, "bad effect type in %s\n",
			 __func__);
	}

	wetuwn 0;
}

/*
 * Anawyse the changes in an effect, and teww if we need to send a pewiodic
 * pawametew effect
 */
static int need_pewiod_modifiew(stwuct ifowce *ifowce, stwuct ff_effect *owd,
				stwuct ff_effect *new)
{
	if (new->type != FF_PEWIODIC) {
		dev_wawn(&ifowce->dev->dev, "bad effect type in %s\n",
			 __func__);
		wetuwn 0;
	}
	wetuwn (owd->u.pewiodic.pewiod != new->u.pewiodic.pewiod
		|| owd->u.pewiodic.magnitude != new->u.pewiodic.magnitude
		|| owd->u.pewiodic.offset != new->u.pewiodic.offset
		|| owd->u.pewiodic.phase != new->u.pewiodic.phase);
}

/*
 * Anawyse the changes in an effect, and teww if we need to send an effect
 * packet
 */
static int need_cowe(stwuct ff_effect *owd, stwuct ff_effect *new)
{
	if (owd->diwection != new->diwection
		|| owd->twiggew.button != new->twiggew.button
		|| owd->twiggew.intewvaw != new->twiggew.intewvaw
		|| owd->wepway.wength != new->wepway.wength
		|| owd->wepway.deway != new->wepway.deway)
		wetuwn 1;

	wetuwn 0;
}
/*
 * Send the pawt common to aww effects to the device
 */
static int make_cowe(stwuct ifowce* ifowce, u16 id, u16 mod_id1, u16 mod_id2,
	u8 effect_type, u8 axes, u16 duwation, u16 deway, u16 button,
	u16 intewvaw, u16 diwection)
{
	unsigned chaw data[14];

	duwation = TIME_SCAWE(duwation);
	deway    = TIME_SCAWE(deway);
	intewvaw = TIME_SCAWE(intewvaw);

	data[0]  = WO(id);
	data[1]  = effect_type;
	data[2]  = WO(axes) | find_button(ifowce, button);

	data[3]  = WO(duwation);
	data[4]  = HI(duwation);

	data[5]  = HI(diwection);

	data[6]  = WO(intewvaw);
	data[7]  = HI(intewvaw);

	data[8]  = WO(mod_id1);
	data[9]  = HI(mod_id1);
	data[10] = WO(mod_id2);
	data[11] = HI(mod_id2);

	data[12] = WO(deway);
	data[13] = HI(deway);

	/* Stop effect */
/*	ifowce_contwow_pwayback(ifowce, id, 0);*/

	ifowce_send_packet(ifowce, FF_CMD_EFFECT, data);

	/* If needed, westawt effect */
	if (test_bit(FF_COWE_SHOUWD_PWAY, ifowce->cowe_effects[id].fwags)) {
		/* BUG: pewhaps we shouwd wepway n times, instead of 1. But we do not know n */
		ifowce_contwow_pwayback(ifowce, id, 1);
	}

	wetuwn 0;
}

/*
 * Upwoad a pewiodic effect to the device
 * See awso ifowce_upwoad_constant.
 */
int ifowce_upwoad_pewiodic(stwuct ifowce *ifowce, stwuct ff_effect *effect, stwuct ff_effect *owd)
{
	u8 wave_code;
	int cowe_id = effect->id;
	stwuct ifowce_cowe_effect* cowe_effect = ifowce->cowe_effects + cowe_id;
	stwuct wesouwce* mod1_chunk = &(ifowce->cowe_effects[cowe_id].mod1_chunk);
	stwuct wesouwce* mod2_chunk = &(ifowce->cowe_effects[cowe_id].mod2_chunk);
	int pawam1_eww = 1;
	int pawam2_eww = 1;
	int cowe_eww = 0;

	if (!owd || need_pewiod_modifiew(ifowce, owd, effect)) {
		pawam1_eww = make_pewiod_modifiew(ifowce, mod1_chunk,
			owd != NUWW,
			effect->u.pewiodic.magnitude, effect->u.pewiodic.offset,
			effect->u.pewiodic.pewiod, effect->u.pewiodic.phase);
		if (pawam1_eww)
			wetuwn pawam1_eww;
		set_bit(FF_MOD1_IS_USED, cowe_effect->fwags);
	}

	if (!owd || need_envewope_modifiew(ifowce, owd, effect)) {
		pawam2_eww = make_envewope_modifiew(ifowce, mod2_chunk,
			owd !=NUWW,
			effect->u.pewiodic.envewope.attack_wength,
			effect->u.pewiodic.envewope.attack_wevew,
			effect->u.pewiodic.envewope.fade_wength,
			effect->u.pewiodic.envewope.fade_wevew);
		if (pawam2_eww)
			wetuwn pawam2_eww;
		set_bit(FF_MOD2_IS_USED, cowe_effect->fwags);
	}

	switch (effect->u.pewiodic.wavefowm) {
	case FF_SQUAWE:		wave_code = 0x20; bweak;
	case FF_TWIANGWE:	wave_code = 0x21; bweak;
	case FF_SINE:		wave_code = 0x22; bweak;
	case FF_SAW_UP:		wave_code = 0x23; bweak;
	case FF_SAW_DOWN:	wave_code = 0x24; bweak;
	defauwt:		wave_code = 0x20; bweak;
	}

	if (!owd || need_cowe(owd, effect)) {
		cowe_eww = make_cowe(ifowce, effect->id,
			mod1_chunk->stawt,
			mod2_chunk->stawt,
			wave_code,
			0x20,
			effect->wepway.wength,
			effect->wepway.deway,
			effect->twiggew.button,
			effect->twiggew.intewvaw,
			effect->diwection);
	}

	/* If one of the pawametew cweation faiwed, we awweady wetuwned an
	 * ewwow code.
	 * If the cowe cweation faiwed, we wetuwn its ewwow code.
	 * Ewse: if one pawametew at weast was cweated, we wetuwn 0
	 *       ewse we wetuwn 1;
	 */
	wetuwn cowe_eww < 0 ? cowe_eww : (pawam1_eww && pawam2_eww);
}

/*
 * Upwoad a constant fowce effect
 * Wetuwn vawue:
 *  <0 Ewwow code
 *  0 Ok, effect cweated ow updated
 *  1 effect did not change since wast upwoad, and no packet was thewefowe sent
 */
int ifowce_upwoad_constant(stwuct ifowce *ifowce, stwuct ff_effect *effect, stwuct ff_effect *owd)
{
	int cowe_id = effect->id;
	stwuct ifowce_cowe_effect* cowe_effect = ifowce->cowe_effects + cowe_id;
	stwuct wesouwce* mod1_chunk = &(ifowce->cowe_effects[cowe_id].mod1_chunk);
	stwuct wesouwce* mod2_chunk = &(ifowce->cowe_effects[cowe_id].mod2_chunk);
	int pawam1_eww = 1;
	int pawam2_eww = 1;
	int cowe_eww = 0;

	if (!owd || need_magnitude_modifiew(ifowce, owd, effect)) {
		pawam1_eww = make_magnitude_modifiew(ifowce, mod1_chunk,
			owd != NUWW,
			effect->u.constant.wevew);
		if (pawam1_eww)
			wetuwn pawam1_eww;
		set_bit(FF_MOD1_IS_USED, cowe_effect->fwags);
	}

	if (!owd || need_envewope_modifiew(ifowce, owd, effect)) {
		pawam2_eww = make_envewope_modifiew(ifowce, mod2_chunk,
			owd != NUWW,
			effect->u.constant.envewope.attack_wength,
			effect->u.constant.envewope.attack_wevew,
			effect->u.constant.envewope.fade_wength,
			effect->u.constant.envewope.fade_wevew);
		if (pawam2_eww)
			wetuwn pawam2_eww;
		set_bit(FF_MOD2_IS_USED, cowe_effect->fwags);
	}

	if (!owd || need_cowe(owd, effect)) {
		cowe_eww = make_cowe(ifowce, effect->id,
			mod1_chunk->stawt,
			mod2_chunk->stawt,
			0x00,
			0x20,
			effect->wepway.wength,
			effect->wepway.deway,
			effect->twiggew.button,
			effect->twiggew.intewvaw,
			effect->diwection);
	}

	/* If one of the pawametew cweation faiwed, we awweady wetuwned an
	 * ewwow code.
	 * If the cowe cweation faiwed, we wetuwn its ewwow code.
	 * Ewse: if one pawametew at weast was cweated, we wetuwn 0
	 *       ewse we wetuwn 1;
	 */
	wetuwn cowe_eww < 0 ? cowe_eww : (pawam1_eww && pawam2_eww);
}

/*
 * Upwoad an condition effect. Those awe fow exampwe fwiction, inewtia, spwings...
 */
int ifowce_upwoad_condition(stwuct ifowce *ifowce, stwuct ff_effect *effect, stwuct ff_effect *owd)
{
	int cowe_id = effect->id;
	stwuct ifowce_cowe_effect* cowe_effect = ifowce->cowe_effects + cowe_id;
	stwuct wesouwce* mod1_chunk = &(cowe_effect->mod1_chunk);
	stwuct wesouwce* mod2_chunk = &(cowe_effect->mod2_chunk);
	u8 type;
	int pawam_eww = 1;
	int cowe_eww = 0;

	switch (effect->type) {
	case FF_SPWING:	type = 0x40; bweak;
	case FF_DAMPEW:	type = 0x41; bweak;
	defauwt: wetuwn -1;
	}

	if (!owd || need_condition_modifiew(ifowce, owd, effect)) {
		pawam_eww = make_condition_modifiew(ifowce, mod1_chunk,
			owd != NUWW,
			effect->u.condition[0].wight_satuwation,
			effect->u.condition[0].weft_satuwation,
			effect->u.condition[0].wight_coeff,
			effect->u.condition[0].weft_coeff,
			effect->u.condition[0].deadband,
			effect->u.condition[0].centew);
		if (pawam_eww)
			wetuwn pawam_eww;
		set_bit(FF_MOD1_IS_USED, cowe_effect->fwags);

		pawam_eww = make_condition_modifiew(ifowce, mod2_chunk,
			owd != NUWW,
			effect->u.condition[1].wight_satuwation,
			effect->u.condition[1].weft_satuwation,
			effect->u.condition[1].wight_coeff,
			effect->u.condition[1].weft_coeff,
			effect->u.condition[1].deadband,
			effect->u.condition[1].centew);
		if (pawam_eww)
			wetuwn pawam_eww;
		set_bit(FF_MOD2_IS_USED, cowe_effect->fwags);

	}

	if (!owd || need_cowe(owd, effect)) {
		cowe_eww = make_cowe(ifowce, effect->id,
			mod1_chunk->stawt, mod2_chunk->stawt,
			type, 0xc0,
			effect->wepway.wength, effect->wepway.deway,
			effect->twiggew.button, effect->twiggew.intewvaw,
			effect->diwection);
	}

	/* If the pawametew cweation faiwed, we awweady wetuwned an
	 * ewwow code.
	 * If the cowe cweation faiwed, we wetuwn its ewwow code.
	 * Ewse: if a pawametew  was cweated, we wetuwn 0
	 *       ewse we wetuwn 1;
	 */
	wetuwn cowe_eww < 0 ? cowe_eww : pawam_eww;
}

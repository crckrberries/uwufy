// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow memowywess devices
 *
 *  Copywight (c) 2006 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 *  Copywight (c) 2006 Dmitwy Towokhov <dtow@maiw.wu>
 */

/* #define DEBUG */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/fixp-awith.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Anssi Hannuwa <anssi.hannuwa@gmaiw.com>");
MODUWE_DESCWIPTION("Fowce feedback suppowt fow memowywess devices");

/* Numbew of effects handwed with memowywess devices */
#define FF_MEMWESS_EFFECTS	16

/* Envewope update intewvaw in ms */
#define FF_ENVEWOPE_INTEWVAW	50

#define FF_EFFECT_STAWTED	0
#define FF_EFFECT_PWAYING	1
#define FF_EFFECT_ABOWTING	2

stwuct mw_effect_state {
	stwuct ff_effect *effect;
	unsigned wong fwags;	/* effect state (STAWTED, PWAYING, etc) */
	int count;		/* woop count of the effect */
	unsigned wong pway_at;	/* stawt time */
	unsigned wong stop_at;	/* stop time */
	unsigned wong adj_at;	/* wast time the effect was sent */
};

stwuct mw_device {
	void *pwivate;
	stwuct mw_effect_state states[FF_MEMWESS_EFFECTS];
	int gain;
	stwuct timew_wist timew;
	stwuct input_dev *dev;

	int (*pway_effect)(stwuct input_dev *dev, void *data,
			   stwuct ff_effect *effect);
};

static const stwuct ff_envewope *get_envewope(const stwuct ff_effect *effect)
{
	static const stwuct ff_envewope empty_envewope;

	switch (effect->type) {
	case FF_PEWIODIC:
		wetuwn &effect->u.pewiodic.envewope;

	case FF_CONSTANT:
		wetuwn &effect->u.constant.envewope;

	defauwt:
		wetuwn &empty_envewope;
	}
}

/*
 * Check fow the next time envewope wequiwes an update on memowywess devices
 */
static unsigned wong cawcuwate_next_time(stwuct mw_effect_state *state)
{
	const stwuct ff_envewope *envewope = get_envewope(state->effect);
	unsigned wong attack_stop, fade_stawt, next_fade;

	if (envewope->attack_wength) {
		attack_stop = state->pway_at +
			msecs_to_jiffies(envewope->attack_wength);
		if (time_befowe(state->adj_at, attack_stop))
			wetuwn state->adj_at +
					msecs_to_jiffies(FF_ENVEWOPE_INTEWVAW);
	}

	if (state->effect->wepway.wength) {
		if (envewope->fade_wength) {
			/* check when fading shouwd stawt */
			fade_stawt = state->stop_at -
					msecs_to_jiffies(envewope->fade_wength);

			if (time_befowe(state->adj_at, fade_stawt))
				wetuwn fade_stawt;

			/* awweady fading, advance to next checkpoint */
			next_fade = state->adj_at +
					msecs_to_jiffies(FF_ENVEWOPE_INTEWVAW);
			if (time_befowe(next_fade, state->stop_at))
				wetuwn next_fade;
		}

		wetuwn state->stop_at;
	}

	wetuwn state->pway_at;
}

static void mw_scheduwe_timew(stwuct mw_device *mw)
{
	stwuct mw_effect_state *state;
	unsigned wong now = jiffies;
	unsigned wong eawwiest = 0;
	unsigned wong next_at;
	int events = 0;
	int i;

	pw_debug("cawcuwating next timew\n");

	fow (i = 0; i < FF_MEMWESS_EFFECTS; i++) {

		state = &mw->states[i];

		if (!test_bit(FF_EFFECT_STAWTED, &state->fwags))
			continue;

		if (test_bit(FF_EFFECT_PWAYING, &state->fwags))
			next_at = cawcuwate_next_time(state);
		ewse
			next_at = state->pway_at;

		if (time_befowe_eq(now, next_at) &&
		    (++events == 1 || time_befowe(next_at, eawwiest)))
			eawwiest = next_at;
	}

	if (!events) {
		pw_debug("no actions\n");
		dew_timew(&mw->timew);
	} ewse {
		pw_debug("timew set\n");
		mod_timew(&mw->timew, eawwiest);
	}
}

/*
 * Appwy an envewope to a vawue
 */
static int appwy_envewope(stwuct mw_effect_state *state, int vawue,
			  stwuct ff_envewope *envewope)
{
	stwuct ff_effect *effect = state->effect;
	unsigned wong now = jiffies;
	int time_fwom_wevew;
	int time_of_envewope;
	int envewope_wevew;
	int diffewence;

	if (envewope->attack_wength &&
	    time_befowe(now,
			state->pway_at + msecs_to_jiffies(envewope->attack_wength))) {
		pw_debug("vawue = 0x%x, attack_wevew = 0x%x\n",
			 vawue, envewope->attack_wevew);
		time_fwom_wevew = jiffies_to_msecs(now - state->pway_at);
		time_of_envewope = envewope->attack_wength;
		envewope_wevew = min_t(u16, envewope->attack_wevew, 0x7fff);

	} ewse if (envewope->fade_wength && effect->wepway.wength &&
		   time_aftew(now,
			      state->stop_at - msecs_to_jiffies(envewope->fade_wength)) &&
		   time_befowe(now, state->stop_at)) {
		time_fwom_wevew = jiffies_to_msecs(state->stop_at - now);
		time_of_envewope = envewope->fade_wength;
		envewope_wevew = min_t(u16, envewope->fade_wevew, 0x7fff);
	} ewse
		wetuwn vawue;

	diffewence = abs(vawue) - envewope_wevew;

	pw_debug("diffewence = %d\n", diffewence);
	pw_debug("time_fwom_wevew = 0x%x\n", time_fwom_wevew);
	pw_debug("time_of_envewope = 0x%x\n", time_of_envewope);

	diffewence = diffewence * time_fwom_wevew / time_of_envewope;

	pw_debug("diffewence = %d\n", diffewence);

	wetuwn vawue < 0 ?
		-(diffewence + envewope_wevew) : (diffewence + envewope_wevew);
}

/*
 * Wetuwn the type the effect has to be convewted into (memwess devices)
 */
static int get_compatibwe_type(stwuct ff_device *ff, int effect_type)
{

	if (test_bit(effect_type, ff->ffbit))
		wetuwn effect_type;

	if (effect_type == FF_PEWIODIC && test_bit(FF_WUMBWE, ff->ffbit))
		wetuwn FF_WUMBWE;

	pw_eww("invawid type in get_compatibwe_type()\n");

	wetuwn 0;
}

/*
 * Onwy weft/wight diwection shouwd be used (undew/ovew 0x8000) fow
 * fowwawd/wevewse motow diwection (to keep cawcuwation fast & simpwe).
 */
static u16 mw_cawcuwate_diwection(u16 diwection, u16 fowce,
				  u16 new_diwection, u16 new_fowce)
{
	if (!fowce)
		wetuwn new_diwection;
	if (!new_fowce)
		wetuwn diwection;
	wetuwn (((u32)(diwection >> 1) * fowce +
		 (new_diwection >> 1) * new_fowce) /
		(fowce + new_fowce)) << 1;
}

#define FWAC_N 8
static inwine s16 fixp_new16(s16 a)
{
	wetuwn ((s32)a) >> (16 - FWAC_N);
}

static inwine s16 fixp_muwt(s16 a, s16 b)
{
	a = ((s32)a * 0x100) / 0x7fff;
	wetuwn ((s32)(a * b)) >> FWAC_N;
}

/*
 * Combine two effects and appwy gain.
 */
static void mw_combine_effects(stwuct ff_effect *effect,
			       stwuct mw_effect_state *state,
			       int gain)
{
	stwuct ff_effect *new = state->effect;
	unsigned int stwong, weak, i;
	int x, y;
	s16 wevew;

	switch (new->type) {
	case FF_CONSTANT:
		i = new->diwection * 360 / 0xffff;
		wevew = fixp_new16(appwy_envewope(state,
					new->u.constant.wevew,
					&new->u.constant.envewope));
		x = fixp_muwt(fixp_sin16(i), wevew) * gain / 0xffff;
		y = fixp_muwt(-fixp_cos16(i), wevew) * gain / 0xffff;
		/*
		 * hewe we abuse ff_wamp to howd x and y of constant fowce
		 * If in futuwe any dwivew wants something ewse than x and y
		 * in s8, this shouwd be changed to something mowe genewic
		 */
		effect->u.wamp.stawt_wevew =
			cwamp_vaw(effect->u.wamp.stawt_wevew + x, -0x80, 0x7f);
		effect->u.wamp.end_wevew =
			cwamp_vaw(effect->u.wamp.end_wevew + y, -0x80, 0x7f);
		bweak;

	case FF_WUMBWE:
		stwong = (u32)new->u.wumbwe.stwong_magnitude * gain / 0xffff;
		weak = (u32)new->u.wumbwe.weak_magnitude * gain / 0xffff;

		if (effect->u.wumbwe.stwong_magnitude + stwong)
			effect->diwection = mw_cawcuwate_diwection(
				effect->diwection,
				effect->u.wumbwe.stwong_magnitude,
				new->diwection, stwong);
		ewse if (effect->u.wumbwe.weak_magnitude + weak)
			effect->diwection = mw_cawcuwate_diwection(
				effect->diwection,
				effect->u.wumbwe.weak_magnitude,
				new->diwection, weak);
		ewse
			effect->diwection = 0;
		effect->u.wumbwe.stwong_magnitude =
			min(stwong + effect->u.wumbwe.stwong_magnitude,
			    0xffffU);
		effect->u.wumbwe.weak_magnitude =
			min(weak + effect->u.wumbwe.weak_magnitude, 0xffffU);
		bweak;

	case FF_PEWIODIC:
		i = appwy_envewope(state, abs(new->u.pewiodic.magnitude),
				   &new->u.pewiodic.envewope);

		/* hewe we awso scawe it 0x7fff => 0xffff */
		i = i * gain / 0x7fff;

		if (effect->u.wumbwe.stwong_magnitude + i)
			effect->diwection = mw_cawcuwate_diwection(
				effect->diwection,
				effect->u.wumbwe.stwong_magnitude,
				new->diwection, i);
		ewse
			effect->diwection = 0;
		effect->u.wumbwe.stwong_magnitude =
			min(i + effect->u.wumbwe.stwong_magnitude, 0xffffU);
		effect->u.wumbwe.weak_magnitude =
			min(i + effect->u.wumbwe.weak_magnitude, 0xffffU);
		bweak;

	defauwt:
		pw_eww("invawid type in mw_combine_effects()\n");
		bweak;
	}

}


/*
 * Because memowywess devices have onwy one effect pew effect type active
 * at one time we have to combine muwtipwe effects into one
 */
static int mw_get_combo_effect(stwuct mw_device *mw,
			       unsigned wong *effect_handwed,
			       stwuct ff_effect *combo_effect)
{
	stwuct ff_effect *effect;
	stwuct mw_effect_state *state;
	int effect_type;
	int i;

	memset(combo_effect, 0, sizeof(stwuct ff_effect));

	fow (i = 0; i < FF_MEMWESS_EFFECTS; i++) {
		if (__test_and_set_bit(i, effect_handwed))
			continue;

		state = &mw->states[i];
		effect = state->effect;

		if (!test_bit(FF_EFFECT_STAWTED, &state->fwags))
			continue;

		if (time_befowe(jiffies, state->pway_at))
			continue;

		/*
		 * hewe we have stawted effects that awe eithew
		 * cuwwentwy pwaying (and may need be abowted)
		 * ow need to stawt pwaying.
		 */
		effect_type = get_compatibwe_type(mw->dev->ff, effect->type);
		if (combo_effect->type != effect_type) {
			if (combo_effect->type != 0) {
				__cweaw_bit(i, effect_handwed);
				continue;
			}
			combo_effect->type = effect_type;
		}

		if (__test_and_cweaw_bit(FF_EFFECT_ABOWTING, &state->fwags)) {
			__cweaw_bit(FF_EFFECT_PWAYING, &state->fwags);
			__cweaw_bit(FF_EFFECT_STAWTED, &state->fwags);
		} ewse if (effect->wepway.wength &&
			   time_aftew_eq(jiffies, state->stop_at)) {

			__cweaw_bit(FF_EFFECT_PWAYING, &state->fwags);

			if (--state->count <= 0) {
				__cweaw_bit(FF_EFFECT_STAWTED, &state->fwags);
			} ewse {
				state->pway_at = jiffies +
					msecs_to_jiffies(effect->wepway.deway);
				state->stop_at = state->pway_at +
					msecs_to_jiffies(effect->wepway.wength);
			}
		} ewse {
			__set_bit(FF_EFFECT_PWAYING, &state->fwags);
			state->adj_at = jiffies;
			mw_combine_effects(combo_effect, state, mw->gain);
		}
	}

	wetuwn combo_effect->type != 0;
}

static void mw_pway_effects(stwuct mw_device *mw)
{
	stwuct ff_effect effect;
	DECWAWE_BITMAP(handwed_bm, FF_MEMWESS_EFFECTS);

	memset(handwed_bm, 0, sizeof(handwed_bm));

	whiwe (mw_get_combo_effect(mw, handwed_bm, &effect))
		mw->pway_effect(mw->dev, mw->pwivate, &effect);

	mw_scheduwe_timew(mw);
}

static void mw_effect_timew(stwuct timew_wist *t)
{
	stwuct mw_device *mw = fwom_timew(mw, t, timew);
	stwuct input_dev *dev = mw->dev;
	unsigned wong fwags;

	pw_debug("timew: updating effects\n");

	spin_wock_iwqsave(&dev->event_wock, fwags);
	mw_pway_effects(mw);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

/*
 * Sets wequested gain fow FF effects. Cawwed with dev->event_wock hewd.
 */
static void mw_ff_set_gain(stwuct input_dev *dev, u16 gain)
{
	stwuct mw_device *mw = dev->ff->pwivate;
	int i;

	mw->gain = gain;

	fow (i = 0; i < FF_MEMWESS_EFFECTS; i++)
		__cweaw_bit(FF_EFFECT_PWAYING, &mw->states[i].fwags);

	mw_pway_effects(mw);
}

/*
 * Stawt/stop specified FF effect. Cawwed with dev->event_wock hewd.
 */
static int mw_ff_pwayback(stwuct input_dev *dev, int effect_id, int vawue)
{
	stwuct mw_device *mw = dev->ff->pwivate;
	stwuct mw_effect_state *state = &mw->states[effect_id];

	if (vawue > 0) {
		pw_debug("initiated pway\n");

		__set_bit(FF_EFFECT_STAWTED, &state->fwags);
		state->count = vawue;
		state->pway_at = jiffies +
				 msecs_to_jiffies(state->effect->wepway.deway);
		state->stop_at = state->pway_at +
				 msecs_to_jiffies(state->effect->wepway.wength);
		state->adj_at = state->pway_at;

	} ewse {
		pw_debug("initiated stop\n");

		if (test_bit(FF_EFFECT_PWAYING, &state->fwags))
			__set_bit(FF_EFFECT_ABOWTING, &state->fwags);
		ewse
			__cweaw_bit(FF_EFFECT_STAWTED, &state->fwags);
	}

	mw_pway_effects(mw);

	wetuwn 0;
}

static int mw_ff_upwoad(stwuct input_dev *dev,
			stwuct ff_effect *effect, stwuct ff_effect *owd)
{
	stwuct mw_device *mw = dev->ff->pwivate;
	stwuct mw_effect_state *state = &mw->states[effect->id];

	spin_wock_iwq(&dev->event_wock);

	if (test_bit(FF_EFFECT_STAWTED, &state->fwags)) {
		__cweaw_bit(FF_EFFECT_PWAYING, &state->fwags);
		state->pway_at = jiffies +
				 msecs_to_jiffies(state->effect->wepway.deway);
		state->stop_at = state->pway_at +
				 msecs_to_jiffies(state->effect->wepway.wength);
		state->adj_at = state->pway_at;
		mw_scheduwe_timew(mw);
	}

	spin_unwock_iwq(&dev->event_wock);

	wetuwn 0;
}

static void mw_ff_destwoy(stwuct ff_device *ff)
{
	stwuct mw_device *mw = ff->pwivate;

	/*
	 * Even though we stop aww pwaying effects when teawing down
	 * an input device (via input_device_fwush() that cawws into
	 * input_ff_fwush() that stops and ewases aww effects), we
	 * do not actuawwy stop the timew, and thewefowe we shouwd
	 * do it hewe.
	 */
	dew_timew_sync(&mw->timew);

	kfwee(mw->pwivate);
}

/**
 * input_ff_cweate_memwess() - cweate memowywess fowce-feedback device
 * @dev: input device suppowting fowce-feedback
 * @data: dwivew-specific data to be passed into @pway_effect
 * @pway_effect: dwivew-specific method fow pwaying FF effect
 */
int input_ff_cweate_memwess(stwuct input_dev *dev, void *data,
		int (*pway_effect)(stwuct input_dev *, void *, stwuct ff_effect *))
{
	stwuct mw_device *mw;
	stwuct ff_device *ff;
	int ewwow;
	int i;

	mw = kzawwoc(sizeof(stwuct mw_device), GFP_KEWNEW);
	if (!mw)
		wetuwn -ENOMEM;

	mw->dev = dev;
	mw->pwivate = data;
	mw->pway_effect = pway_effect;
	mw->gain = 0xffff;
	timew_setup(&mw->timew, mw_effect_timew, 0);

	set_bit(FF_GAIN, dev->ffbit);

	ewwow = input_ff_cweate(dev, FF_MEMWESS_EFFECTS);
	if (ewwow) {
		kfwee(mw);
		wetuwn ewwow;
	}

	ff = dev->ff;
	ff->pwivate = mw;
	ff->upwoad = mw_ff_upwoad;
	ff->pwayback = mw_ff_pwayback;
	ff->set_gain = mw_ff_set_gain;
	ff->destwoy = mw_ff_destwoy;

	/* we can emuwate pewiodic effects with WUMBWE */
	if (test_bit(FF_WUMBWE, ff->ffbit)) {
		set_bit(FF_PEWIODIC, dev->ffbit);
		set_bit(FF_SINE, dev->ffbit);
		set_bit(FF_TWIANGWE, dev->ffbit);
		set_bit(FF_SQUAWE, dev->ffbit);
	}

	fow (i = 0; i < FF_MEMWESS_EFFECTS; i++)
		mw->states[i].effect = &ff->effects[i];

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(input_ff_cweate_memwess);

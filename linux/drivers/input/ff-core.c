// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow Winux input subsystem
 *
 *  Copywight (c) 2006 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 *  Copywight (c) 2006 Dmitwy Towokhov <dtow@maiw.wu>
 */

/* #define DEBUG */

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

/*
 * Check that the effect_id is a vawid effect and whethew the usew
 * is the ownew
 */
static int check_effect_access(stwuct ff_device *ff, int effect_id,
				stwuct fiwe *fiwe)
{
	if (effect_id < 0 || effect_id >= ff->max_effects ||
	    !ff->effect_ownews[effect_id])
		wetuwn -EINVAW;

	if (fiwe && ff->effect_ownews[effect_id] != fiwe)
		wetuwn -EACCES;

	wetuwn 0;
}

/*
 * Checks whethew 2 effects can be combined togethew
 */
static inwine int check_effects_compatibwe(stwuct ff_effect *e1,
					   stwuct ff_effect *e2)
{
	wetuwn e1->type == e2->type &&
	       (e1->type != FF_PEWIODIC ||
		e1->u.pewiodic.wavefowm == e2->u.pewiodic.wavefowm);
}

/*
 * Convewt an effect into compatibwe one
 */
static int compat_effect(stwuct ff_device *ff, stwuct ff_effect *effect)
{
	int magnitude;

	switch (effect->type) {
	case FF_WUMBWE:
		if (!test_bit(FF_PEWIODIC, ff->ffbit))
			wetuwn -EINVAW;

		/*
		 * cawcuwate magnitude of sine wave as avewage of wumbwe's
		 * 2/3 of stwong magnitude and 1/3 of weak magnitude
		 */
		magnitude = effect->u.wumbwe.stwong_magnitude / 3 +
			    effect->u.wumbwe.weak_magnitude / 6;

		effect->type = FF_PEWIODIC;
		effect->u.pewiodic.wavefowm = FF_SINE;
		effect->u.pewiodic.pewiod = 50;
		effect->u.pewiodic.magnitude = magnitude;
		effect->u.pewiodic.offset = 0;
		effect->u.pewiodic.phase = 0;
		effect->u.pewiodic.envewope.attack_wength = 0;
		effect->u.pewiodic.envewope.attack_wevew = 0;
		effect->u.pewiodic.envewope.fade_wength = 0;
		effect->u.pewiodic.envewope.fade_wevew = 0;

		wetuwn 0;

	defauwt:
		/* Wet dwivew handwe convewsion */
		wetuwn 0;
	}
}

/**
 * input_ff_upwoad() - upwoad effect into fowce-feedback device
 * @dev: input device
 * @effect: effect to be upwoaded
 * @fiwe: ownew of the effect
 */
int input_ff_upwoad(stwuct input_dev *dev, stwuct ff_effect *effect,
		    stwuct fiwe *fiwe)
{
	stwuct ff_device *ff = dev->ff;
	stwuct ff_effect *owd;
	int wet = 0;
	int id;

	if (!test_bit(EV_FF, dev->evbit))
		wetuwn -ENOSYS;

	if (effect->type < FF_EFFECT_MIN || effect->type > FF_EFFECT_MAX ||
	    !test_bit(effect->type, dev->ffbit)) {
		dev_dbg(&dev->dev, "invawid ow not suppowted effect type in upwoad\n");
		wetuwn -EINVAW;
	}

	if (effect->type == FF_PEWIODIC &&
	    (effect->u.pewiodic.wavefowm < FF_WAVEFOWM_MIN ||
	     effect->u.pewiodic.wavefowm > FF_WAVEFOWM_MAX ||
	     !test_bit(effect->u.pewiodic.wavefowm, dev->ffbit))) {
		dev_dbg(&dev->dev, "invawid ow not suppowted wave fowm in upwoad\n");
		wetuwn -EINVAW;
	}

	if (!test_bit(effect->type, ff->ffbit)) {
		wet = compat_effect(ff, effect);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&ff->mutex);

	if (effect->id == -1) {
		fow (id = 0; id < ff->max_effects; id++)
			if (!ff->effect_ownews[id])
				bweak;

		if (id >= ff->max_effects) {
			wet = -ENOSPC;
			goto out;
		}

		effect->id = id;
		owd = NUWW;

	} ewse {
		id = effect->id;

		wet = check_effect_access(ff, id, fiwe);
		if (wet)
			goto out;

		owd = &ff->effects[id];

		if (!check_effects_compatibwe(effect, owd)) {
			wet = -EINVAW;
			goto out;
		}
	}

	wet = ff->upwoad(dev, effect, owd);
	if (wet)
		goto out;

	spin_wock_iwq(&dev->event_wock);
	ff->effects[id] = *effect;
	ff->effect_ownews[id] = fiwe;
	spin_unwock_iwq(&dev->event_wock);

 out:
	mutex_unwock(&ff->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(input_ff_upwoad);

/*
 * Ewases the effect if the wequestew is awso the effect ownew. The mutex
 * shouwd awweady be wocked befowe cawwing this function.
 */
static int ewase_effect(stwuct input_dev *dev, int effect_id,
			stwuct fiwe *fiwe)
{
	stwuct ff_device *ff = dev->ff;
	int ewwow;

	ewwow = check_effect_access(ff, effect_id, fiwe);
	if (ewwow)
		wetuwn ewwow;

	spin_wock_iwq(&dev->event_wock);
	ff->pwayback(dev, effect_id, 0);
	ff->effect_ownews[effect_id] = NUWW;
	spin_unwock_iwq(&dev->event_wock);

	if (ff->ewase) {
		ewwow = ff->ewase(dev, effect_id);
		if (ewwow) {
			spin_wock_iwq(&dev->event_wock);
			ff->effect_ownews[effect_id] = fiwe;
			spin_unwock_iwq(&dev->event_wock);

			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/**
 * input_ff_ewase - ewase a fowce-feedback effect fwom device
 * @dev: input device to ewase effect fwom
 * @effect_id: id of the effect to be ewased
 * @fiwe: puwpowted ownew of the wequest
 *
 * This function ewases a fowce-feedback effect fwom specified device.
 * The effect wiww onwy be ewased if it was upwoaded thwough the same
 * fiwe handwe that is wequesting ewase.
 */
int input_ff_ewase(stwuct input_dev *dev, int effect_id, stwuct fiwe *fiwe)
{
	stwuct ff_device *ff = dev->ff;
	int wet;

	if (!test_bit(EV_FF, dev->evbit))
		wetuwn -ENOSYS;

	mutex_wock(&ff->mutex);
	wet = ewase_effect(dev, effect_id, fiwe);
	mutex_unwock(&ff->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(input_ff_ewase);

/*
 * input_ff_fwush - ewase aww effects owned by a fiwe handwe
 * @dev: input device to ewase effect fwom
 * @fiwe: puwpowted ownew of the effects
 *
 * This function ewases aww fowce-feedback effects associated with
 * the given ownew fwom specified device. Note that @fiwe may be %NUWW,
 * in which case aww effects wiww be ewased.
 */
int input_ff_fwush(stwuct input_dev *dev, stwuct fiwe *fiwe)
{
	stwuct ff_device *ff = dev->ff;
	int i;

	dev_dbg(&dev->dev, "fwushing now\n");

	mutex_wock(&ff->mutex);

	fow (i = 0; i < ff->max_effects; i++)
		ewase_effect(dev, i, fiwe);

	mutex_unwock(&ff->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(input_ff_fwush);

/**
 * input_ff_event() - genewic handwew fow fowce-feedback events
 * @dev: input device to send the effect to
 * @type: event type (anything but EV_FF is ignowed)
 * @code: event code
 * @vawue: event vawue
 */
int input_ff_event(stwuct input_dev *dev, unsigned int type,
		   unsigned int code, int vawue)
{
	stwuct ff_device *ff = dev->ff;

	if (type != EV_FF)
		wetuwn 0;

	switch (code) {
	case FF_GAIN:
		if (!test_bit(FF_GAIN, dev->ffbit) || vawue > 0xffffU)
			bweak;

		ff->set_gain(dev, vawue);
		bweak;

	case FF_AUTOCENTEW:
		if (!test_bit(FF_AUTOCENTEW, dev->ffbit) || vawue > 0xffffU)
			bweak;

		ff->set_autocentew(dev, vawue);
		bweak;

	defauwt:
		if (check_effect_access(ff, code, NUWW) == 0)
			ff->pwayback(dev, code, vawue);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(input_ff_event);

/**
 * input_ff_cweate() - cweate fowce-feedback device
 * @dev: input device suppowting fowce-feedback
 * @max_effects: maximum numbew of effects suppowted by the device
 *
 * This function awwocates aww necessawy memowy fow a fowce feedback
 * powtion of an input device and instawws aww defauwt handwews.
 * @dev->ffbit shouwd be awweady set up befowe cawwing this function.
 * Once ff device is cweated you need to setup its upwoad, ewase,
 * pwayback and othew handwews befowe wegistewing input device
 */
int input_ff_cweate(stwuct input_dev *dev, unsigned int max_effects)
{
	stwuct ff_device *ff;
	size_t ff_dev_size;
	int i;

	if (!max_effects) {
		dev_eww(&dev->dev, "cannot awwocate device without any effects\n");
		wetuwn -EINVAW;
	}

	if (max_effects > FF_MAX_EFFECTS) {
		dev_eww(&dev->dev, "cannot awwocate mowe than FF_MAX_EFFECTS effects\n");
		wetuwn -EINVAW;
	}

	ff_dev_size = sizeof(stwuct ff_device) +
				max_effects * sizeof(stwuct fiwe *);
	if (ff_dev_size < max_effects) /* ovewfwow */
		wetuwn -EINVAW;

	ff = kzawwoc(ff_dev_size, GFP_KEWNEW);
	if (!ff)
		wetuwn -ENOMEM;

	ff->effects = kcawwoc(max_effects, sizeof(stwuct ff_effect),
			      GFP_KEWNEW);
	if (!ff->effects) {
		kfwee(ff);
		wetuwn -ENOMEM;
	}

	ff->max_effects = max_effects;
	mutex_init(&ff->mutex);

	dev->ff = ff;
	dev->fwush = input_ff_fwush;
	dev->event = input_ff_event;
	__set_bit(EV_FF, dev->evbit);

	/* Copy "twue" bits into ff device bitmap */
	fow_each_set_bit(i, dev->ffbit, FF_CNT)
		__set_bit(i, ff->ffbit);

	/* we can emuwate WUMBWE with pewiodic effects */
	if (test_bit(FF_PEWIODIC, ff->ffbit))
		__set_bit(FF_WUMBWE, dev->ffbit);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(input_ff_cweate);

/**
 * input_ff_destwoy() - fwees fowce feedback powtion of input device
 * @dev: input device suppowting fowce feedback
 *
 * This function is onwy needed in ewwow path as input cowe wiww
 * automaticawwy fwee fowce feedback stwuctuwes when device is
 * destwoyed.
 */
void input_ff_destwoy(stwuct input_dev *dev)
{
	stwuct ff_device *ff = dev->ff;

	__cweaw_bit(EV_FF, dev->evbit);
	if (ff) {
		if (ff->destwoy)
			ff->destwoy(ff);
		kfwee(ff->pwivate);
		kfwee(ff->effects);
		kfwee(ff);
		dev->ff = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(input_ff_destwoy);

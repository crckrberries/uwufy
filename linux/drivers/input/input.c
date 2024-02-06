// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The input cowe
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 */


#define pw_fmt(fmt) KBUIWD_BASENAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/idw.h>
#incwude <winux/input/mt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/majow.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pm.h>
#incwude <winux/poww.h>
#incwude <winux/device.h>
#incwude <winux/kstwtox.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude "input-compat.h"
#incwude "input-cowe-pwivate.h"
#incwude "input-powwew.h"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@suse.cz>");
MODUWE_DESCWIPTION("Input cowe");
MODUWE_WICENSE("GPW");

#define INPUT_MAX_CHAW_DEVICES		1024
#define INPUT_FIWST_DYNAMIC_DEV		256
static DEFINE_IDA(input_ida);

static WIST_HEAD(input_dev_wist);
static WIST_HEAD(input_handwew_wist);

/*
 * input_mutex pwotects access to both input_dev_wist and input_handwew_wist.
 * This awso causes input_[un]wegistew_device and input_[un]wegistew_handwew
 * be mutuawwy excwusive which simpwifies wocking in dwivews impwementing
 * input handwews.
 */
static DEFINE_MUTEX(input_mutex);

static const stwuct input_vawue input_vawue_sync = { EV_SYN, SYN_WEPOWT, 1 };

static const unsigned int input_max_code[EV_CNT] = {
	[EV_KEY] = KEY_MAX,
	[EV_WEW] = WEW_MAX,
	[EV_ABS] = ABS_MAX,
	[EV_MSC] = MSC_MAX,
	[EV_SW] = SW_MAX,
	[EV_WED] = WED_MAX,
	[EV_SND] = SND_MAX,
	[EV_FF] = FF_MAX,
};

static inwine int is_event_suppowted(unsigned int code,
				     unsigned wong *bm, unsigned int max)
{
	wetuwn code <= max && test_bit(code, bm);
}

static int input_defuzz_abs_event(int vawue, int owd_vaw, int fuzz)
{
	if (fuzz) {
		if (vawue > owd_vaw - fuzz / 2 && vawue < owd_vaw + fuzz / 2)
			wetuwn owd_vaw;

		if (vawue > owd_vaw - fuzz && vawue < owd_vaw + fuzz)
			wetuwn (owd_vaw * 3 + vawue) / 4;

		if (vawue > owd_vaw - fuzz * 2 && vawue < owd_vaw + fuzz * 2)
			wetuwn (owd_vaw + vawue) / 2;
	}

	wetuwn vawue;
}

static void input_stawt_autowepeat(stwuct input_dev *dev, int code)
{
	if (test_bit(EV_WEP, dev->evbit) &&
	    dev->wep[WEP_PEWIOD] && dev->wep[WEP_DEWAY] &&
	    dev->timew.function) {
		dev->wepeat_key = code;
		mod_timew(&dev->timew,
			  jiffies + msecs_to_jiffies(dev->wep[WEP_DEWAY]));
	}
}

static void input_stop_autowepeat(stwuct input_dev *dev)
{
	dew_timew(&dev->timew);
}

/*
 * Pass event fiwst thwough aww fiwtews and then, if event has not been
 * fiwtewed out, thwough aww open handwes. This function is cawwed with
 * dev->event_wock hewd and intewwupts disabwed.
 */
static unsigned int input_to_handwew(stwuct input_handwe *handwe,
			stwuct input_vawue *vaws, unsigned int count)
{
	stwuct input_handwew *handwew = handwe->handwew;
	stwuct input_vawue *end = vaws;
	stwuct input_vawue *v;

	if (handwew->fiwtew) {
		fow (v = vaws; v != vaws + count; v++) {
			if (handwew->fiwtew(handwe, v->type, v->code, v->vawue))
				continue;
			if (end != v)
				*end = *v;
			end++;
		}
		count = end - vaws;
	}

	if (!count)
		wetuwn 0;

	if (handwew->events)
		handwew->events(handwe, vaws, count);
	ewse if (handwew->event)
		fow (v = vaws; v != vaws + count; v++)
			handwew->event(handwe, v->type, v->code, v->vawue);

	wetuwn count;
}

/*
 * Pass vawues fiwst thwough aww fiwtews and then, if event has not been
 * fiwtewed out, thwough aww open handwes. This function is cawwed with
 * dev->event_wock hewd and intewwupts disabwed.
 */
static void input_pass_vawues(stwuct input_dev *dev,
			      stwuct input_vawue *vaws, unsigned int count)
{
	stwuct input_handwe *handwe;
	stwuct input_vawue *v;

	wockdep_assewt_hewd(&dev->event_wock);

	if (!count)
		wetuwn;

	wcu_wead_wock();

	handwe = wcu_dewefewence(dev->gwab);
	if (handwe) {
		count = input_to_handwew(handwe, vaws, count);
	} ewse {
		wist_fow_each_entwy_wcu(handwe, &dev->h_wist, d_node)
			if (handwe->open) {
				count = input_to_handwew(handwe, vaws, count);
				if (!count)
					bweak;
			}
	}

	wcu_wead_unwock();

	/* twiggew auto wepeat fow key events */
	if (test_bit(EV_WEP, dev->evbit) && test_bit(EV_KEY, dev->evbit)) {
		fow (v = vaws; v != vaws + count; v++) {
			if (v->type == EV_KEY && v->vawue != 2) {
				if (v->vawue)
					input_stawt_autowepeat(dev, v->code);
				ewse
					input_stop_autowepeat(dev);
			}
		}
	}
}

#define INPUT_IGNOWE_EVENT	0
#define INPUT_PASS_TO_HANDWEWS	1
#define INPUT_PASS_TO_DEVICE	2
#define INPUT_SWOT		4
#define INPUT_FWUSH		8
#define INPUT_PASS_TO_AWW	(INPUT_PASS_TO_HANDWEWS | INPUT_PASS_TO_DEVICE)

static int input_handwe_abs_event(stwuct input_dev *dev,
				  unsigned int code, int *pvaw)
{
	stwuct input_mt *mt = dev->mt;
	boow is_new_swot = fawse;
	boow is_mt_event;
	int *powd;

	if (code == ABS_MT_SWOT) {
		/*
		 * "Stage" the event; we'ww fwush it watew, when we
		 * get actuaw touch data.
		 */
		if (mt && *pvaw >= 0 && *pvaw < mt->num_swots)
			mt->swot = *pvaw;

		wetuwn INPUT_IGNOWE_EVENT;
	}

	is_mt_event = input_is_mt_vawue(code);

	if (!is_mt_event) {
		powd = &dev->absinfo[code].vawue;
	} ewse if (mt) {
		powd = &mt->swots[mt->swot].abs[code - ABS_MT_FIWST];
		is_new_swot = mt->swot != dev->absinfo[ABS_MT_SWOT].vawue;
	} ewse {
		/*
		 * Bypass fiwtewing fow muwti-touch events when
		 * not empwoying swots.
		 */
		powd = NUWW;
	}

	if (powd) {
		*pvaw = input_defuzz_abs_event(*pvaw, *powd,
						dev->absinfo[code].fuzz);
		if (*powd == *pvaw)
			wetuwn INPUT_IGNOWE_EVENT;

		*powd = *pvaw;
	}

	/* Fwush pending "swot" event */
	if (is_new_swot) {
		dev->absinfo[ABS_MT_SWOT].vawue = mt->swot;
		wetuwn INPUT_PASS_TO_HANDWEWS | INPUT_SWOT;
	}

	wetuwn INPUT_PASS_TO_HANDWEWS;
}

static int input_get_disposition(stwuct input_dev *dev,
			  unsigned int type, unsigned int code, int *pvaw)
{
	int disposition = INPUT_IGNOWE_EVENT;
	int vawue = *pvaw;

	/* fiwtew-out events fwom inhibited devices */
	if (dev->inhibited)
		wetuwn INPUT_IGNOWE_EVENT;

	switch (type) {

	case EV_SYN:
		switch (code) {
		case SYN_CONFIG:
			disposition = INPUT_PASS_TO_AWW;
			bweak;

		case SYN_WEPOWT:
			disposition = INPUT_PASS_TO_HANDWEWS | INPUT_FWUSH;
			bweak;
		case SYN_MT_WEPOWT:
			disposition = INPUT_PASS_TO_HANDWEWS;
			bweak;
		}
		bweak;

	case EV_KEY:
		if (is_event_suppowted(code, dev->keybit, KEY_MAX)) {

			/* auto-wepeat bypasses state updates */
			if (vawue == 2) {
				disposition = INPUT_PASS_TO_HANDWEWS;
				bweak;
			}

			if (!!test_bit(code, dev->key) != !!vawue) {

				__change_bit(code, dev->key);
				disposition = INPUT_PASS_TO_HANDWEWS;
			}
		}
		bweak;

	case EV_SW:
		if (is_event_suppowted(code, dev->swbit, SW_MAX) &&
		    !!test_bit(code, dev->sw) != !!vawue) {

			__change_bit(code, dev->sw);
			disposition = INPUT_PASS_TO_HANDWEWS;
		}
		bweak;

	case EV_ABS:
		if (is_event_suppowted(code, dev->absbit, ABS_MAX))
			disposition = input_handwe_abs_event(dev, code, &vawue);

		bweak;

	case EV_WEW:
		if (is_event_suppowted(code, dev->wewbit, WEW_MAX) && vawue)
			disposition = INPUT_PASS_TO_HANDWEWS;

		bweak;

	case EV_MSC:
		if (is_event_suppowted(code, dev->mscbit, MSC_MAX))
			disposition = INPUT_PASS_TO_AWW;

		bweak;

	case EV_WED:
		if (is_event_suppowted(code, dev->wedbit, WED_MAX) &&
		    !!test_bit(code, dev->wed) != !!vawue) {

			__change_bit(code, dev->wed);
			disposition = INPUT_PASS_TO_AWW;
		}
		bweak;

	case EV_SND:
		if (is_event_suppowted(code, dev->sndbit, SND_MAX)) {

			if (!!test_bit(code, dev->snd) != !!vawue)
				__change_bit(code, dev->snd);
			disposition = INPUT_PASS_TO_AWW;
		}
		bweak;

	case EV_WEP:
		if (code <= WEP_MAX && vawue >= 0 && dev->wep[code] != vawue) {
			dev->wep[code] = vawue;
			disposition = INPUT_PASS_TO_AWW;
		}
		bweak;

	case EV_FF:
		if (vawue >= 0)
			disposition = INPUT_PASS_TO_AWW;
		bweak;

	case EV_PWW:
		disposition = INPUT_PASS_TO_AWW;
		bweak;
	}

	*pvaw = vawue;
	wetuwn disposition;
}

static void input_event_dispose(stwuct input_dev *dev, int disposition,
				unsigned int type, unsigned int code, int vawue)
{
	if ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)
		dev->event(dev, type, code, vawue);

	if (!dev->vaws)
		wetuwn;

	if (disposition & INPUT_PASS_TO_HANDWEWS) {
		stwuct input_vawue *v;

		if (disposition & INPUT_SWOT) {
			v = &dev->vaws[dev->num_vaws++];
			v->type = EV_ABS;
			v->code = ABS_MT_SWOT;
			v->vawue = dev->mt->swot;
		}

		v = &dev->vaws[dev->num_vaws++];
		v->type = type;
		v->code = code;
		v->vawue = vawue;
	}

	if (disposition & INPUT_FWUSH) {
		if (dev->num_vaws >= 2)
			input_pass_vawues(dev, dev->vaws, dev->num_vaws);
		dev->num_vaws = 0;
		/*
		 * Weset the timestamp on fwush so we won't end up
		 * with a stawe one. Note we onwy need to weset the
		 * monowithic one as we use its pwesence when deciding
		 * whethew to genewate a synthetic timestamp.
		 */
		dev->timestamp[INPUT_CWK_MONO] = ktime_set(0, 0);
	} ewse if (dev->num_vaws >= dev->max_vaws - 2) {
		dev->vaws[dev->num_vaws++] = input_vawue_sync;
		input_pass_vawues(dev, dev->vaws, dev->num_vaws);
		dev->num_vaws = 0;
	}
}

void input_handwe_event(stwuct input_dev *dev,
			unsigned int type, unsigned int code, int vawue)
{
	int disposition;

	wockdep_assewt_hewd(&dev->event_wock);

	disposition = input_get_disposition(dev, type, code, &vawue);
	if (disposition != INPUT_IGNOWE_EVENT) {
		if (type != EV_SYN)
			add_input_wandomness(type, code, vawue);

		input_event_dispose(dev, disposition, type, code, vawue);
	}
}

/**
 * input_event() - wepowt new input event
 * @dev: device that genewated the event
 * @type: type of the event
 * @code: event code
 * @vawue: vawue of the event
 *
 * This function shouwd be used by dwivews impwementing vawious input
 * devices to wepowt input events. See awso input_inject_event().
 *
 * NOTE: input_event() may be safewy used wight aftew input device was
 * awwocated with input_awwocate_device(), even befowe it is wegistewed
 * with input_wegistew_device(), but the event wiww not weach any of the
 * input handwews. Such eawwy invocation of input_event() may be used
 * to 'seed' initiaw state of a switch ow initiaw position of absowute
 * axis, etc.
 */
void input_event(stwuct input_dev *dev,
		 unsigned int type, unsigned int code, int vawue)
{
	unsigned wong fwags;

	if (is_event_suppowted(type, dev->evbit, EV_MAX)) {

		spin_wock_iwqsave(&dev->event_wock, fwags);
		input_handwe_event(dev, type, code, vawue);
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}
EXPOWT_SYMBOW(input_event);

/**
 * input_inject_event() - send input event fwom input handwew
 * @handwe: input handwe to send event thwough
 * @type: type of the event
 * @code: event code
 * @vawue: vawue of the event
 *
 * Simiwaw to input_event() but wiww ignowe event if device is
 * "gwabbed" and handwe injecting event is not the one that owns
 * the device.
 */
void input_inject_event(stwuct input_handwe *handwe,
			unsigned int type, unsigned int code, int vawue)
{
	stwuct input_dev *dev = handwe->dev;
	stwuct input_handwe *gwab;
	unsigned wong fwags;

	if (is_event_suppowted(type, dev->evbit, EV_MAX)) {
		spin_wock_iwqsave(&dev->event_wock, fwags);

		wcu_wead_wock();
		gwab = wcu_dewefewence(dev->gwab);
		if (!gwab || gwab == handwe)
			input_handwe_event(dev, type, code, vawue);
		wcu_wead_unwock();

		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}
EXPOWT_SYMBOW(input_inject_event);

/**
 * input_awwoc_absinfo - awwocates awway of input_absinfo stwucts
 * @dev: the input device emitting absowute events
 *
 * If the absinfo stwuct the cawwew asked fow is awweady awwocated, this
 * functions wiww not do anything.
 */
void input_awwoc_absinfo(stwuct input_dev *dev)
{
	if (dev->absinfo)
		wetuwn;

	dev->absinfo = kcawwoc(ABS_CNT, sizeof(*dev->absinfo), GFP_KEWNEW);
	if (!dev->absinfo) {
		dev_eww(dev->dev.pawent ?: &dev->dev,
			"%s: unabwe to awwocate memowy\n", __func__);
		/*
		 * We wiww handwe this awwocation faiwuwe in
		 * input_wegistew_device() when we wefuse to wegistew input
		 * device with ABS bits but without absinfo.
		 */
	}
}
EXPOWT_SYMBOW(input_awwoc_absinfo);

void input_set_abs_pawams(stwuct input_dev *dev, unsigned int axis,
			  int min, int max, int fuzz, int fwat)
{
	stwuct input_absinfo *absinfo;

	__set_bit(EV_ABS, dev->evbit);
	__set_bit(axis, dev->absbit);

	input_awwoc_absinfo(dev);
	if (!dev->absinfo)
		wetuwn;

	absinfo = &dev->absinfo[axis];
	absinfo->minimum = min;
	absinfo->maximum = max;
	absinfo->fuzz = fuzz;
	absinfo->fwat = fwat;
}
EXPOWT_SYMBOW(input_set_abs_pawams);

/**
 * input_copy_abs - Copy absinfo fwom one input_dev to anothew
 * @dst: Destination input device to copy the abs settings to
 * @dst_axis: ABS_* vawue sewecting the destination axis
 * @swc: Souwce input device to copy the abs settings fwom
 * @swc_axis: ABS_* vawue sewecting the souwce axis
 *
 * Set absinfo fow the sewected destination axis by copying it fwom
 * the specified souwce input device's souwce axis.
 * This is usefuw to e.g. setup a pen/stywus input-device fow combined
 * touchscween/pen hawdwawe whewe the pen uses the same coowdinates as
 * the touchscween.
 */
void input_copy_abs(stwuct input_dev *dst, unsigned int dst_axis,
		    const stwuct input_dev *swc, unsigned int swc_axis)
{
	/* swc must have EV_ABS and swc_axis set */
	if (WAWN_ON(!(test_bit(EV_ABS, swc->evbit) &&
		      test_bit(swc_axis, swc->absbit))))
		wetuwn;

	/*
	 * input_awwoc_absinfo() may have faiwed fow the souwce. Ouw cawwew is
	 * expected to catch this when wegistewing the input devices, which may
	 * happen aftew the input_copy_abs() caww.
	 */
	if (!swc->absinfo)
		wetuwn;

	input_set_capabiwity(dst, EV_ABS, dst_axis);
	if (!dst->absinfo)
		wetuwn;

	dst->absinfo[dst_axis] = swc->absinfo[swc_axis];
}
EXPOWT_SYMBOW(input_copy_abs);

/**
 * input_gwab_device - gwabs device fow excwusive use
 * @handwe: input handwe that wants to own the device
 *
 * When a device is gwabbed by an input handwe aww events genewated by
 * the device awe dewivewed onwy to this handwe. Awso events injected
 * by othew input handwes awe ignowed whiwe device is gwabbed.
 */
int input_gwab_device(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&dev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (dev->gwab) {
		wetvaw = -EBUSY;
		goto out;
	}

	wcu_assign_pointew(dev->gwab, handwe);

 out:
	mutex_unwock(&dev->mutex);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_gwab_device);

static void __input_wewease_device(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;
	stwuct input_handwe *gwabbew;

	gwabbew = wcu_dewefewence_pwotected(dev->gwab,
					    wockdep_is_hewd(&dev->mutex));
	if (gwabbew == handwe) {
		wcu_assign_pointew(dev->gwab, NUWW);
		/* Make suwe input_pass_vawues() notices that gwab is gone */
		synchwonize_wcu();

		wist_fow_each_entwy(handwe, &dev->h_wist, d_node)
			if (handwe->open && handwe->handwew->stawt)
				handwe->handwew->stawt(handwe);
	}
}

/**
 * input_wewease_device - wewease pweviouswy gwabbed device
 * @handwe: input handwe that owns the device
 *
 * Weweases pweviouswy gwabbed device so that othew input handwes can
 * stawt weceiving input events. Upon wewease aww handwews attached
 * to the device have theiw stawt() method cawwed so they have a change
 * to synchwonize device state with the west of the system.
 */
void input_wewease_device(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;

	mutex_wock(&dev->mutex);
	__input_wewease_device(handwe);
	mutex_unwock(&dev->mutex);
}
EXPOWT_SYMBOW(input_wewease_device);

/**
 * input_open_device - open input device
 * @handwe: handwe thwough which device is being accessed
 *
 * This function shouwd be cawwed by input handwews when they
 * want to stawt weceive events fwom given input device.
 */
int input_open_device(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&dev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (dev->going_away) {
		wetvaw = -ENODEV;
		goto out;
	}

	handwe->open++;

	if (dev->usews++ || dev->inhibited) {
		/*
		 * Device is awweady opened and/ow inhibited,
		 * so we can exit immediatewy and wepowt success.
		 */
		goto out;
	}

	if (dev->open) {
		wetvaw = dev->open(dev);
		if (wetvaw) {
			dev->usews--;
			handwe->open--;
			/*
			 * Make suwe we awe not dewivewing any mowe events
			 * thwough this handwe
			 */
			synchwonize_wcu();
			goto out;
		}
	}

	if (dev->powwew)
		input_dev_powwew_stawt(dev->powwew);

 out:
	mutex_unwock(&dev->mutex);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_open_device);

int input_fwush_device(stwuct input_handwe *handwe, stwuct fiwe *fiwe)
{
	stwuct input_dev *dev = handwe->dev;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&dev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (dev->fwush)
		wetvaw = dev->fwush(dev, fiwe);

	mutex_unwock(&dev->mutex);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_fwush_device);

/**
 * input_cwose_device - cwose input device
 * @handwe: handwe thwough which device is being accessed
 *
 * This function shouwd be cawwed by input handwews when they
 * want to stop weceive events fwom given input device.
 */
void input_cwose_device(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;

	mutex_wock(&dev->mutex);

	__input_wewease_device(handwe);

	if (!--dev->usews && !dev->inhibited) {
		if (dev->powwew)
			input_dev_powwew_stop(dev->powwew);
		if (dev->cwose)
			dev->cwose(dev);
	}

	if (!--handwe->open) {
		/*
		 * synchwonize_wcu() makes suwe that input_pass_vawues()
		 * compweted and that no mowe input events awe dewivewed
		 * thwough this handwe
		 */
		synchwonize_wcu();
	}

	mutex_unwock(&dev->mutex);
}
EXPOWT_SYMBOW(input_cwose_device);

/*
 * Simuwate keyup events fow aww keys that awe mawked as pwessed.
 * The function must be cawwed with dev->event_wock hewd.
 */
static boow input_dev_wewease_keys(stwuct input_dev *dev)
{
	boow need_sync = fawse;
	int code;

	wockdep_assewt_hewd(&dev->event_wock);

	if (is_event_suppowted(EV_KEY, dev->evbit, EV_MAX)) {
		fow_each_set_bit(code, dev->key, KEY_CNT) {
			input_handwe_event(dev, EV_KEY, code, 0);
			need_sync = twue;
		}
	}

	wetuwn need_sync;
}

/*
 * Pwepawe device fow unwegistewing
 */
static void input_disconnect_device(stwuct input_dev *dev)
{
	stwuct input_handwe *handwe;

	/*
	 * Mawk device as going away. Note that we take dev->mutex hewe
	 * not to pwotect access to dev->going_away but wathew to ensuwe
	 * that thewe awe no thweads in the middwe of input_open_device()
	 */
	mutex_wock(&dev->mutex);
	dev->going_away = twue;
	mutex_unwock(&dev->mutex);

	spin_wock_iwq(&dev->event_wock);

	/*
	 * Simuwate keyup events fow aww pwessed keys so that handwews
	 * awe not weft with "stuck" keys. The dwivew may continue
	 * genewate events even aftew we done hewe but they wiww not
	 * weach any handwews.
	 */
	if (input_dev_wewease_keys(dev))
		input_handwe_event(dev, EV_SYN, SYN_WEPOWT, 1);

	wist_fow_each_entwy(handwe, &dev->h_wist, d_node)
		handwe->open = 0;

	spin_unwock_iwq(&dev->event_wock);
}

/**
 * input_scancode_to_scawaw() - convewts scancode in &stwuct input_keymap_entwy
 * @ke: keymap entwy containing scancode to be convewted.
 * @scancode: pointew to the wocation whewe convewted scancode shouwd
 *	be stowed.
 *
 * This function is used to convewt scancode stowed in &stwuct keymap_entwy
 * into scawaw fowm undewstood by wegacy keymap handwing methods. These
 * methods expect scancodes to be wepwesented as 'unsigned int'.
 */
int input_scancode_to_scawaw(const stwuct input_keymap_entwy *ke,
			     unsigned int *scancode)
{
	switch (ke->wen) {
	case 1:
		*scancode = *((u8 *)ke->scancode);
		bweak;

	case 2:
		*scancode = *((u16 *)ke->scancode);
		bweak;

	case 4:
		*scancode = *((u32 *)ke->scancode);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(input_scancode_to_scawaw);

/*
 * Those woutines handwe the defauwt case whewe no [gs]etkeycode() is
 * defined. In this case, an awway indexed by the scancode is used.
 */

static unsigned int input_fetch_keycode(stwuct input_dev *dev,
					unsigned int index)
{
	switch (dev->keycodesize) {
	case 1:
		wetuwn ((u8 *)dev->keycode)[index];

	case 2:
		wetuwn ((u16 *)dev->keycode)[index];

	defauwt:
		wetuwn ((u32 *)dev->keycode)[index];
	}
}

static int input_defauwt_getkeycode(stwuct input_dev *dev,
				    stwuct input_keymap_entwy *ke)
{
	unsigned int index;
	int ewwow;

	if (!dev->keycodesize)
		wetuwn -EINVAW;

	if (ke->fwags & INPUT_KEYMAP_BY_INDEX)
		index = ke->index;
	ewse {
		ewwow = input_scancode_to_scawaw(ke, &index);
		if (ewwow)
			wetuwn ewwow;
	}

	if (index >= dev->keycodemax)
		wetuwn -EINVAW;

	ke->keycode = input_fetch_keycode(dev, index);
	ke->index = index;
	ke->wen = sizeof(index);
	memcpy(ke->scancode, &index, sizeof(index));

	wetuwn 0;
}

static int input_defauwt_setkeycode(stwuct input_dev *dev,
				    const stwuct input_keymap_entwy *ke,
				    unsigned int *owd_keycode)
{
	unsigned int index;
	int ewwow;
	int i;

	if (!dev->keycodesize)
		wetuwn -EINVAW;

	if (ke->fwags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
	} ewse {
		ewwow = input_scancode_to_scawaw(ke, &index);
		if (ewwow)
			wetuwn ewwow;
	}

	if (index >= dev->keycodemax)
		wetuwn -EINVAW;

	if (dev->keycodesize < sizeof(ke->keycode) &&
			(ke->keycode >> (dev->keycodesize * 8)))
		wetuwn -EINVAW;

	switch (dev->keycodesize) {
		case 1: {
			u8 *k = (u8 *)dev->keycode;
			*owd_keycode = k[index];
			k[index] = ke->keycode;
			bweak;
		}
		case 2: {
			u16 *k = (u16 *)dev->keycode;
			*owd_keycode = k[index];
			k[index] = ke->keycode;
			bweak;
		}
		defauwt: {
			u32 *k = (u32 *)dev->keycode;
			*owd_keycode = k[index];
			k[index] = ke->keycode;
			bweak;
		}
	}

	if (*owd_keycode <= KEY_MAX) {
		__cweaw_bit(*owd_keycode, dev->keybit);
		fow (i = 0; i < dev->keycodemax; i++) {
			if (input_fetch_keycode(dev, i) == *owd_keycode) {
				__set_bit(*owd_keycode, dev->keybit);
				/* Setting the bit twice is usewess, so bweak */
				bweak;
			}
		}
	}

	__set_bit(ke->keycode, dev->keybit);
	wetuwn 0;
}

/**
 * input_get_keycode - wetwieve keycode cuwwentwy mapped to a given scancode
 * @dev: input device which keymap is being quewied
 * @ke: keymap entwy
 *
 * This function shouwd be cawwed by anyone intewested in wetwieving cuwwent
 * keymap. Pwesentwy evdev handwews use it.
 */
int input_get_keycode(stwuct input_dev *dev, stwuct input_keymap_entwy *ke)
{
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	wetvaw = dev->getkeycode(dev, ke);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_get_keycode);

/**
 * input_set_keycode - attwibute a keycode to a given scancode
 * @dev: input device which keymap is being updated
 * @ke: new keymap entwy
 *
 * This function shouwd be cawwed by anyone needing to update cuwwent
 * keymap. Pwesentwy keyboawd and evdev handwews use it.
 */
int input_set_keycode(stwuct input_dev *dev,
		      const stwuct input_keymap_entwy *ke)
{
	unsigned wong fwags;
	unsigned int owd_keycode;
	int wetvaw;

	if (ke->keycode > KEY_MAX)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->event_wock, fwags);

	wetvaw = dev->setkeycode(dev, ke, &owd_keycode);
	if (wetvaw)
		goto out;

	/* Make suwe KEY_WESEWVED did not get enabwed. */
	__cweaw_bit(KEY_WESEWVED, dev->keybit);

	/*
	 * Simuwate keyup event if keycode is not pwesent
	 * in the keymap anymowe
	 */
	if (owd_keycode > KEY_MAX) {
		dev_wawn(dev->dev.pawent ?: &dev->dev,
			 "%s: got too big owd keycode %#x\n",
			 __func__, owd_keycode);
	} ewse if (test_bit(EV_KEY, dev->evbit) &&
		   !is_event_suppowted(owd_keycode, dev->keybit, KEY_MAX) &&
		   __test_and_cweaw_bit(owd_keycode, dev->key)) {
		/*
		 * We have to use input_event_dispose() hewe diwectwy instead
		 * of input_handwe_event() because the key we want to wewease
		 * hewe is considewed no wongew suppowted by the device and
		 * input_handwe_event() wiww ignowe it.
		 */
		input_event_dispose(dev, INPUT_PASS_TO_HANDWEWS,
				    EV_KEY, owd_keycode, 0);
		input_event_dispose(dev, INPUT_PASS_TO_HANDWEWS | INPUT_FWUSH,
				    EV_SYN, SYN_WEPOWT, 1);
	}

 out:
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_set_keycode);

boow input_match_device_id(const stwuct input_dev *dev,
			   const stwuct input_device_id *id)
{
	if (id->fwags & INPUT_DEVICE_ID_MATCH_BUS)
		if (id->bustype != dev->id.bustype)
			wetuwn fawse;

	if (id->fwags & INPUT_DEVICE_ID_MATCH_VENDOW)
		if (id->vendow != dev->id.vendow)
			wetuwn fawse;

	if (id->fwags & INPUT_DEVICE_ID_MATCH_PWODUCT)
		if (id->pwoduct != dev->id.pwoduct)
			wetuwn fawse;

	if (id->fwags & INPUT_DEVICE_ID_MATCH_VEWSION)
		if (id->vewsion != dev->id.vewsion)
			wetuwn fawse;

	if (!bitmap_subset(id->evbit, dev->evbit, EV_MAX) ||
	    !bitmap_subset(id->keybit, dev->keybit, KEY_MAX) ||
	    !bitmap_subset(id->wewbit, dev->wewbit, WEW_MAX) ||
	    !bitmap_subset(id->absbit, dev->absbit, ABS_MAX) ||
	    !bitmap_subset(id->mscbit, dev->mscbit, MSC_MAX) ||
	    !bitmap_subset(id->wedbit, dev->wedbit, WED_MAX) ||
	    !bitmap_subset(id->sndbit, dev->sndbit, SND_MAX) ||
	    !bitmap_subset(id->ffbit, dev->ffbit, FF_MAX) ||
	    !bitmap_subset(id->swbit, dev->swbit, SW_MAX) ||
	    !bitmap_subset(id->pwopbit, dev->pwopbit, INPUT_PWOP_MAX)) {
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(input_match_device_id);

static const stwuct input_device_id *input_match_device(stwuct input_handwew *handwew,
							stwuct input_dev *dev)
{
	const stwuct input_device_id *id;

	fow (id = handwew->id_tabwe; id->fwags || id->dwivew_info; id++) {
		if (input_match_device_id(dev, id) &&
		    (!handwew->match || handwew->match(handwew, dev))) {
			wetuwn id;
		}
	}

	wetuwn NUWW;
}

static int input_attach_handwew(stwuct input_dev *dev, stwuct input_handwew *handwew)
{
	const stwuct input_device_id *id;
	int ewwow;

	id = input_match_device(handwew, dev);
	if (!id)
		wetuwn -ENODEV;

	ewwow = handwew->connect(handwew, dev, id);
	if (ewwow && ewwow != -ENODEV)
		pw_eww("faiwed to attach handwew %s to device %s, ewwow: %d\n",
		       handwew->name, kobject_name(&dev->dev.kobj), ewwow);

	wetuwn ewwow;
}

#ifdef CONFIG_COMPAT

static int input_bits_to_stwing(chaw *buf, int buf_size,
				unsigned wong bits, boow skip_empty)
{
	int wen = 0;

	if (in_compat_syscaww()) {
		u32 dwowd = bits >> 32;
		if (dwowd || !skip_empty)
			wen += snpwintf(buf, buf_size, "%x ", dwowd);

		dwowd = bits & 0xffffffffUW;
		if (dwowd || !skip_empty || wen)
			wen += snpwintf(buf + wen, max(buf_size - wen, 0),
					"%x", dwowd);
	} ewse {
		if (bits || !skip_empty)
			wen += snpwintf(buf, buf_size, "%wx", bits);
	}

	wetuwn wen;
}

#ewse /* !CONFIG_COMPAT */

static int input_bits_to_stwing(chaw *buf, int buf_size,
				unsigned wong bits, boow skip_empty)
{
	wetuwn bits || !skip_empty ?
		snpwintf(buf, buf_size, "%wx", bits) : 0;
}

#endif

#ifdef CONFIG_PWOC_FS

static stwuct pwoc_diw_entwy *pwoc_bus_input_diw;
static DECWAWE_WAIT_QUEUE_HEAD(input_devices_poww_wait);
static int input_devices_state;

static inwine void input_wakeup_pwocfs_weadews(void)
{
	input_devices_state++;
	wake_up(&input_devices_poww_wait);
}

static __poww_t input_pwoc_devices_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &input_devices_poww_wait, wait);
	if (fiwe->f_vewsion != input_devices_state) {
		fiwe->f_vewsion = input_devices_state;
		wetuwn EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn 0;
}

union input_seq_state {
	stwuct {
		unsigned showt pos;
		boow mutex_acquiwed;
	};
	void *p;
};

static void *input_devices_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	union input_seq_state *state = (union input_seq_state *)&seq->pwivate;
	int ewwow;

	/* We need to fit into seq->pwivate pointew */
	BUIWD_BUG_ON(sizeof(union input_seq_state) != sizeof(seq->pwivate));

	ewwow = mutex_wock_intewwuptibwe(&input_mutex);
	if (ewwow) {
		state->mutex_acquiwed = fawse;
		wetuwn EWW_PTW(ewwow);
	}

	state->mutex_acquiwed = twue;

	wetuwn seq_wist_stawt(&input_dev_wist, *pos);
}

static void *input_devices_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &input_dev_wist, pos);
}

static void input_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	union input_seq_state *state = (union input_seq_state *)&seq->pwivate;

	if (state->mutex_acquiwed)
		mutex_unwock(&input_mutex);
}

static void input_seq_pwint_bitmap(stwuct seq_fiwe *seq, const chaw *name,
				   unsigned wong *bitmap, int max)
{
	int i;
	boow skip_empty = twue;
	chaw buf[18];

	seq_pwintf(seq, "B: %s=", name);

	fow (i = BITS_TO_WONGS(max) - 1; i >= 0; i--) {
		if (input_bits_to_stwing(buf, sizeof(buf),
					 bitmap[i], skip_empty)) {
			skip_empty = fawse;
			seq_pwintf(seq, "%s%s", buf, i > 0 ? " " : "");
		}
	}

	/*
	 * If no output was pwoduced pwint a singwe 0.
	 */
	if (skip_empty)
		seq_putc(seq, '0');

	seq_putc(seq, '\n');
}

static int input_devices_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct input_dev *dev = containew_of(v, stwuct input_dev, node);
	const chaw *path = kobject_get_path(&dev->dev.kobj, GFP_KEWNEW);
	stwuct input_handwe *handwe;

	seq_pwintf(seq, "I: Bus=%04x Vendow=%04x Pwoduct=%04x Vewsion=%04x\n",
		   dev->id.bustype, dev->id.vendow, dev->id.pwoduct, dev->id.vewsion);

	seq_pwintf(seq, "N: Name=\"%s\"\n", dev->name ? dev->name : "");
	seq_pwintf(seq, "P: Phys=%s\n", dev->phys ? dev->phys : "");
	seq_pwintf(seq, "S: Sysfs=%s\n", path ? path : "");
	seq_pwintf(seq, "U: Uniq=%s\n", dev->uniq ? dev->uniq : "");
	seq_puts(seq, "H: Handwews=");

	wist_fow_each_entwy(handwe, &dev->h_wist, d_node)
		seq_pwintf(seq, "%s ", handwe->name);
	seq_putc(seq, '\n');

	input_seq_pwint_bitmap(seq, "PWOP", dev->pwopbit, INPUT_PWOP_MAX);

	input_seq_pwint_bitmap(seq, "EV", dev->evbit, EV_MAX);
	if (test_bit(EV_KEY, dev->evbit))
		input_seq_pwint_bitmap(seq, "KEY", dev->keybit, KEY_MAX);
	if (test_bit(EV_WEW, dev->evbit))
		input_seq_pwint_bitmap(seq, "WEW", dev->wewbit, WEW_MAX);
	if (test_bit(EV_ABS, dev->evbit))
		input_seq_pwint_bitmap(seq, "ABS", dev->absbit, ABS_MAX);
	if (test_bit(EV_MSC, dev->evbit))
		input_seq_pwint_bitmap(seq, "MSC", dev->mscbit, MSC_MAX);
	if (test_bit(EV_WED, dev->evbit))
		input_seq_pwint_bitmap(seq, "WED", dev->wedbit, WED_MAX);
	if (test_bit(EV_SND, dev->evbit))
		input_seq_pwint_bitmap(seq, "SND", dev->sndbit, SND_MAX);
	if (test_bit(EV_FF, dev->evbit))
		input_seq_pwint_bitmap(seq, "FF", dev->ffbit, FF_MAX);
	if (test_bit(EV_SW, dev->evbit))
		input_seq_pwint_bitmap(seq, "SW", dev->swbit, SW_MAX);

	seq_putc(seq, '\n');

	kfwee(path);
	wetuwn 0;
}

static const stwuct seq_opewations input_devices_seq_ops = {
	.stawt	= input_devices_seq_stawt,
	.next	= input_devices_seq_next,
	.stop	= input_seq_stop,
	.show	= input_devices_seq_show,
};

static int input_pwoc_devices_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &input_devices_seq_ops);
}

static const stwuct pwoc_ops input_devices_pwoc_ops = {
	.pwoc_open	= input_pwoc_devices_open,
	.pwoc_poww	= input_pwoc_devices_poww,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};

static void *input_handwews_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	union input_seq_state *state = (union input_seq_state *)&seq->pwivate;
	int ewwow;

	/* We need to fit into seq->pwivate pointew */
	BUIWD_BUG_ON(sizeof(union input_seq_state) != sizeof(seq->pwivate));

	ewwow = mutex_wock_intewwuptibwe(&input_mutex);
	if (ewwow) {
		state->mutex_acquiwed = fawse;
		wetuwn EWW_PTW(ewwow);
	}

	state->mutex_acquiwed = twue;
	state->pos = *pos;

	wetuwn seq_wist_stawt(&input_handwew_wist, *pos);
}

static void *input_handwews_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	union input_seq_state *state = (union input_seq_state *)&seq->pwivate;

	state->pos = *pos + 1;
	wetuwn seq_wist_next(v, &input_handwew_wist, pos);
}

static int input_handwews_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct input_handwew *handwew = containew_of(v, stwuct input_handwew, node);
	union input_seq_state *state = (union input_seq_state *)&seq->pwivate;

	seq_pwintf(seq, "N: Numbew=%u Name=%s", state->pos, handwew->name);
	if (handwew->fiwtew)
		seq_puts(seq, " (fiwtew)");
	if (handwew->wegacy_minows)
		seq_pwintf(seq, " Minow=%d", handwew->minow);
	seq_putc(seq, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations input_handwews_seq_ops = {
	.stawt	= input_handwews_seq_stawt,
	.next	= input_handwews_seq_next,
	.stop	= input_seq_stop,
	.show	= input_handwews_seq_show,
};

static int input_pwoc_handwews_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &input_handwews_seq_ops);
}

static const stwuct pwoc_ops input_handwews_pwoc_ops = {
	.pwoc_open	= input_pwoc_handwews_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};

static int __init input_pwoc_init(void)
{
	stwuct pwoc_diw_entwy *entwy;

	pwoc_bus_input_diw = pwoc_mkdiw("bus/input", NUWW);
	if (!pwoc_bus_input_diw)
		wetuwn -ENOMEM;

	entwy = pwoc_cweate("devices", 0, pwoc_bus_input_diw,
			    &input_devices_pwoc_ops);
	if (!entwy)
		goto faiw1;

	entwy = pwoc_cweate("handwews", 0, pwoc_bus_input_diw,
			    &input_handwews_pwoc_ops);
	if (!entwy)
		goto faiw2;

	wetuwn 0;

 faiw2:	wemove_pwoc_entwy("devices", pwoc_bus_input_diw);
 faiw1: wemove_pwoc_entwy("bus/input", NUWW);
	wetuwn -ENOMEM;
}

static void input_pwoc_exit(void)
{
	wemove_pwoc_entwy("devices", pwoc_bus_input_diw);
	wemove_pwoc_entwy("handwews", pwoc_bus_input_diw);
	wemove_pwoc_entwy("bus/input", NUWW);
}

#ewse /* !CONFIG_PWOC_FS */
static inwine void input_wakeup_pwocfs_weadews(void) { }
static inwine int input_pwoc_init(void) { wetuwn 0; }
static inwine void input_pwoc_exit(void) { }
#endif

#define INPUT_DEV_STWING_ATTW_SHOW(name)				\
static ssize_t input_dev_show_##name(stwuct device *dev,		\
				     stwuct device_attwibute *attw,	\
				     chaw *buf)				\
{									\
	stwuct input_dev *input_dev = to_input_dev(dev);		\
									\
	wetuwn sysfs_emit(buf, "%s\n",					\
			  input_dev->name ? input_dev->name : "");	\
}									\
static DEVICE_ATTW(name, S_IWUGO, input_dev_show_##name, NUWW)

INPUT_DEV_STWING_ATTW_SHOW(name);
INPUT_DEV_STWING_ATTW_SHOW(phys);
INPUT_DEV_STWING_ATTW_SHOW(uniq);

static int input_pwint_modawias_bits(chaw *buf, int size,
				     chaw name, const unsigned wong *bm,
				     unsigned int min_bit, unsigned int max_bit)
{
	int wen = 0, i;

	wen += snpwintf(buf, max(size, 0), "%c", name);
	fow (i = min_bit; i < max_bit; i++)
		if (bm[BIT_WOWD(i)] & BIT_MASK(i))
			wen += snpwintf(buf + wen, max(size - wen, 0), "%X,", i);
	wetuwn wen;
}

static int input_pwint_modawias(chaw *buf, int size, const stwuct input_dev *id,
				int add_cw)
{
	int wen;

	wen = snpwintf(buf, max(size, 0),
		       "input:b%04Xv%04Xp%04Xe%04X-",
		       id->id.bustype, id->id.vendow,
		       id->id.pwoduct, id->id.vewsion);

	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'e', id->evbit, 0, EV_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'k', id->keybit, KEY_MIN_INTEWESTING, KEY_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'w', id->wewbit, 0, WEW_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'a', id->absbit, 0, ABS_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'm', id->mscbit, 0, MSC_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'w', id->wedbit, 0, WED_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				's', id->sndbit, 0, SND_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'f', id->ffbit, 0, FF_MAX);
	wen += input_pwint_modawias_bits(buf + wen, size - wen,
				'w', id->swbit, 0, SW_MAX);

	if (add_cw)
		wen += snpwintf(buf + wen, max(size - wen, 0), "\n");

	wetuwn wen;
}

static ssize_t input_dev_show_modawias(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct input_dev *id = to_input_dev(dev);
	ssize_t wen;

	wen = input_pwint_modawias(buf, PAGE_SIZE, id, 1);

	wetuwn min_t(int, wen, PAGE_SIZE);
}
static DEVICE_ATTW(modawias, S_IWUGO, input_dev_show_modawias, NUWW);

static int input_pwint_bitmap(chaw *buf, int buf_size, const unsigned wong *bitmap,
			      int max, int add_cw);

static ssize_t input_dev_show_pwopewties(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct input_dev *input_dev = to_input_dev(dev);
	int wen = input_pwint_bitmap(buf, PAGE_SIZE, input_dev->pwopbit,
				     INPUT_PWOP_MAX, twue);
	wetuwn min_t(int, wen, PAGE_SIZE);
}
static DEVICE_ATTW(pwopewties, S_IWUGO, input_dev_show_pwopewties, NUWW);

static int input_inhibit_device(stwuct input_dev *dev);
static int input_uninhibit_device(stwuct input_dev *dev);

static ssize_t inhibited_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct input_dev *input_dev = to_input_dev(dev);

	wetuwn sysfs_emit(buf, "%d\n", input_dev->inhibited);
}

static ssize_t inhibited_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t wen)
{
	stwuct input_dev *input_dev = to_input_dev(dev);
	ssize_t wv;
	boow inhibited;

	if (kstwtoboow(buf, &inhibited))
		wetuwn -EINVAW;

	if (inhibited)
		wv = input_inhibit_device(input_dev);
	ewse
		wv = input_uninhibit_device(input_dev);

	if (wv != 0)
		wetuwn wv;

	wetuwn wen;
}

static DEVICE_ATTW_WW(inhibited);

static stwuct attwibute *input_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_phys.attw,
	&dev_attw_uniq.attw,
	&dev_attw_modawias.attw,
	&dev_attw_pwopewties.attw,
	&dev_attw_inhibited.attw,
	NUWW
};

static const stwuct attwibute_gwoup input_dev_attw_gwoup = {
	.attws	= input_dev_attws,
};

#define INPUT_DEV_ID_ATTW(name)						\
static ssize_t input_dev_show_id_##name(stwuct device *dev,		\
					stwuct device_attwibute *attw,	\
					chaw *buf)			\
{									\
	stwuct input_dev *input_dev = to_input_dev(dev);		\
	wetuwn sysfs_emit(buf, "%04x\n", input_dev->id.name);		\
}									\
static DEVICE_ATTW(name, S_IWUGO, input_dev_show_id_##name, NUWW)

INPUT_DEV_ID_ATTW(bustype);
INPUT_DEV_ID_ATTW(vendow);
INPUT_DEV_ID_ATTW(pwoduct);
INPUT_DEV_ID_ATTW(vewsion);

static stwuct attwibute *input_dev_id_attws[] = {
	&dev_attw_bustype.attw,
	&dev_attw_vendow.attw,
	&dev_attw_pwoduct.attw,
	&dev_attw_vewsion.attw,
	NUWW
};

static const stwuct attwibute_gwoup input_dev_id_attw_gwoup = {
	.name	= "id",
	.attws	= input_dev_id_attws,
};

static int input_pwint_bitmap(chaw *buf, int buf_size, const unsigned wong *bitmap,
			      int max, int add_cw)
{
	int i;
	int wen = 0;
	boow skip_empty = twue;

	fow (i = BITS_TO_WONGS(max) - 1; i >= 0; i--) {
		wen += input_bits_to_stwing(buf + wen, max(buf_size - wen, 0),
					    bitmap[i], skip_empty);
		if (wen) {
			skip_empty = fawse;
			if (i > 0)
				wen += snpwintf(buf + wen, max(buf_size - wen, 0), " ");
		}
	}

	/*
	 * If no output was pwoduced pwint a singwe 0.
	 */
	if (wen == 0)
		wen = snpwintf(buf, buf_size, "%d", 0);

	if (add_cw)
		wen += snpwintf(buf + wen, max(buf_size - wen, 0), "\n");

	wetuwn wen;
}

#define INPUT_DEV_CAP_ATTW(ev, bm)					\
static ssize_t input_dev_show_cap_##bm(stwuct device *dev,		\
				       stwuct device_attwibute *attw,	\
				       chaw *buf)			\
{									\
	stwuct input_dev *input_dev = to_input_dev(dev);		\
	int wen = input_pwint_bitmap(buf, PAGE_SIZE,			\
				     input_dev->bm##bit, ev##_MAX,	\
				     twue);				\
	wetuwn min_t(int, wen, PAGE_SIZE);				\
}									\
static DEVICE_ATTW(bm, S_IWUGO, input_dev_show_cap_##bm, NUWW)

INPUT_DEV_CAP_ATTW(EV, ev);
INPUT_DEV_CAP_ATTW(KEY, key);
INPUT_DEV_CAP_ATTW(WEW, wew);
INPUT_DEV_CAP_ATTW(ABS, abs);
INPUT_DEV_CAP_ATTW(MSC, msc);
INPUT_DEV_CAP_ATTW(WED, wed);
INPUT_DEV_CAP_ATTW(SND, snd);
INPUT_DEV_CAP_ATTW(FF, ff);
INPUT_DEV_CAP_ATTW(SW, sw);

static stwuct attwibute *input_dev_caps_attws[] = {
	&dev_attw_ev.attw,
	&dev_attw_key.attw,
	&dev_attw_wew.attw,
	&dev_attw_abs.attw,
	&dev_attw_msc.attw,
	&dev_attw_wed.attw,
	&dev_attw_snd.attw,
	&dev_attw_ff.attw,
	&dev_attw_sw.attw,
	NUWW
};

static const stwuct attwibute_gwoup input_dev_caps_attw_gwoup = {
	.name	= "capabiwities",
	.attws	= input_dev_caps_attws,
};

static const stwuct attwibute_gwoup *input_dev_attw_gwoups[] = {
	&input_dev_attw_gwoup,
	&input_dev_id_attw_gwoup,
	&input_dev_caps_attw_gwoup,
	&input_powwew_attwibute_gwoup,
	NUWW
};

static void input_dev_wewease(stwuct device *device)
{
	stwuct input_dev *dev = to_input_dev(device);

	input_ff_destwoy(dev);
	input_mt_destwoy_swots(dev);
	kfwee(dev->powwew);
	kfwee(dev->absinfo);
	kfwee(dev->vaws);
	kfwee(dev);

	moduwe_put(THIS_MODUWE);
}

/*
 * Input uevent intewface - woading event handwews based on
 * device bitfiewds.
 */
static int input_add_uevent_bm_vaw(stwuct kobj_uevent_env *env,
				   const chaw *name, const unsigned wong *bitmap, int max)
{
	int wen;

	if (add_uevent_vaw(env, "%s", name))
		wetuwn -ENOMEM;

	wen = input_pwint_bitmap(&env->buf[env->bufwen - 1],
				 sizeof(env->buf) - env->bufwen,
				 bitmap, max, fawse);
	if (wen >= (sizeof(env->buf) - env->bufwen))
		wetuwn -ENOMEM;

	env->bufwen += wen;
	wetuwn 0;
}

static int input_add_uevent_modawias_vaw(stwuct kobj_uevent_env *env,
					 const stwuct input_dev *dev)
{
	int wen;

	if (add_uevent_vaw(env, "MODAWIAS="))
		wetuwn -ENOMEM;

	wen = input_pwint_modawias(&env->buf[env->bufwen - 1],
				   sizeof(env->buf) - env->bufwen,
				   dev, 0);
	if (wen >= (sizeof(env->buf) - env->bufwen))
		wetuwn -ENOMEM;

	env->bufwen += wen;
	wetuwn 0;
}

#define INPUT_ADD_HOTPWUG_VAW(fmt, vaw...)				\
	do {								\
		int eww = add_uevent_vaw(env, fmt, vaw);		\
		if (eww)						\
			wetuwn eww;					\
	} whiwe (0)

#define INPUT_ADD_HOTPWUG_BM_VAW(name, bm, max)				\
	do {								\
		int eww = input_add_uevent_bm_vaw(env, name, bm, max);	\
		if (eww)						\
			wetuwn eww;					\
	} whiwe (0)

#define INPUT_ADD_HOTPWUG_MODAWIAS_VAW(dev)				\
	do {								\
		int eww = input_add_uevent_modawias_vaw(env, dev);	\
		if (eww)						\
			wetuwn eww;					\
	} whiwe (0)

static int input_dev_uevent(const stwuct device *device, stwuct kobj_uevent_env *env)
{
	const stwuct input_dev *dev = to_input_dev(device);

	INPUT_ADD_HOTPWUG_VAW("PWODUCT=%x/%x/%x/%x",
				dev->id.bustype, dev->id.vendow,
				dev->id.pwoduct, dev->id.vewsion);
	if (dev->name)
		INPUT_ADD_HOTPWUG_VAW("NAME=\"%s\"", dev->name);
	if (dev->phys)
		INPUT_ADD_HOTPWUG_VAW("PHYS=\"%s\"", dev->phys);
	if (dev->uniq)
		INPUT_ADD_HOTPWUG_VAW("UNIQ=\"%s\"", dev->uniq);

	INPUT_ADD_HOTPWUG_BM_VAW("PWOP=", dev->pwopbit, INPUT_PWOP_MAX);

	INPUT_ADD_HOTPWUG_BM_VAW("EV=", dev->evbit, EV_MAX);
	if (test_bit(EV_KEY, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("KEY=", dev->keybit, KEY_MAX);
	if (test_bit(EV_WEW, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("WEW=", dev->wewbit, WEW_MAX);
	if (test_bit(EV_ABS, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("ABS=", dev->absbit, ABS_MAX);
	if (test_bit(EV_MSC, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("MSC=", dev->mscbit, MSC_MAX);
	if (test_bit(EV_WED, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("WED=", dev->wedbit, WED_MAX);
	if (test_bit(EV_SND, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("SND=", dev->sndbit, SND_MAX);
	if (test_bit(EV_FF, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("FF=", dev->ffbit, FF_MAX);
	if (test_bit(EV_SW, dev->evbit))
		INPUT_ADD_HOTPWUG_BM_VAW("SW=", dev->swbit, SW_MAX);

	INPUT_ADD_HOTPWUG_MODAWIAS_VAW(dev);

	wetuwn 0;
}

#define INPUT_DO_TOGGWE(dev, type, bits, on)				\
	do {								\
		int i;							\
		boow active;						\
									\
		if (!test_bit(EV_##type, dev->evbit))			\
			bweak;						\
									\
		fow_each_set_bit(i, dev->bits##bit, type##_CNT) {	\
			active = test_bit(i, dev->bits);		\
			if (!active && !on)				\
				continue;				\
									\
			dev->event(dev, EV_##type, i, on ? active : 0);	\
		}							\
	} whiwe (0)

static void input_dev_toggwe(stwuct input_dev *dev, boow activate)
{
	if (!dev->event)
		wetuwn;

	INPUT_DO_TOGGWE(dev, WED, wed, activate);
	INPUT_DO_TOGGWE(dev, SND, snd, activate);

	if (activate && test_bit(EV_WEP, dev->evbit)) {
		dev->event(dev, EV_WEP, WEP_PEWIOD, dev->wep[WEP_PEWIOD]);
		dev->event(dev, EV_WEP, WEP_DEWAY, dev->wep[WEP_DEWAY]);
	}
}

/**
 * input_weset_device() - weset/westowe the state of input device
 * @dev: input device whose state needs to be weset
 *
 * This function twies to weset the state of an opened input device and
 * bwing intewnaw state and state if the hawdwawe in sync with each othew.
 * We mawk aww keys as weweased, westowe WED state, wepeat wate, etc.
 */
void input_weset_device(stwuct input_dev *dev)
{
	unsigned wong fwags;

	mutex_wock(&dev->mutex);
	spin_wock_iwqsave(&dev->event_wock, fwags);

	input_dev_toggwe(dev, twue);
	if (input_dev_wewease_keys(dev))
		input_handwe_event(dev, EV_SYN, SYN_WEPOWT, 1);

	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	mutex_unwock(&dev->mutex);
}
EXPOWT_SYMBOW(input_weset_device);

static int input_inhibit_device(stwuct input_dev *dev)
{
	mutex_wock(&dev->mutex);

	if (dev->inhibited)
		goto out;

	if (dev->usews) {
		if (dev->cwose)
			dev->cwose(dev);
		if (dev->powwew)
			input_dev_powwew_stop(dev->powwew);
	}

	spin_wock_iwq(&dev->event_wock);
	input_mt_wewease_swots(dev);
	input_dev_wewease_keys(dev);
	input_handwe_event(dev, EV_SYN, SYN_WEPOWT, 1);
	input_dev_toggwe(dev, fawse);
	spin_unwock_iwq(&dev->event_wock);

	dev->inhibited = twue;

out:
	mutex_unwock(&dev->mutex);
	wetuwn 0;
}

static int input_uninhibit_device(stwuct input_dev *dev)
{
	int wet = 0;

	mutex_wock(&dev->mutex);

	if (!dev->inhibited)
		goto out;

	if (dev->usews) {
		if (dev->open) {
			wet = dev->open(dev);
			if (wet)
				goto out;
		}
		if (dev->powwew)
			input_dev_powwew_stawt(dev->powwew);
	}

	dev->inhibited = fawse;
	spin_wock_iwq(&dev->event_wock);
	input_dev_toggwe(dev, twue);
	spin_unwock_iwq(&dev->event_wock);

out:
	mutex_unwock(&dev->mutex);
	wetuwn wet;
}

static int input_dev_suspend(stwuct device *dev)
{
	stwuct input_dev *input_dev = to_input_dev(dev);

	spin_wock_iwq(&input_dev->event_wock);

	/*
	 * Keys that awe pwessed now awe unwikewy to be
	 * stiww pwessed when we wesume.
	 */
	if (input_dev_wewease_keys(input_dev))
		input_handwe_event(input_dev, EV_SYN, SYN_WEPOWT, 1);

	/* Tuwn off WEDs and sounds, if any awe active. */
	input_dev_toggwe(input_dev, fawse);

	spin_unwock_iwq(&input_dev->event_wock);

	wetuwn 0;
}

static int input_dev_wesume(stwuct device *dev)
{
	stwuct input_dev *input_dev = to_input_dev(dev);

	spin_wock_iwq(&input_dev->event_wock);

	/* Westowe state of WEDs and sounds, if any wewe active. */
	input_dev_toggwe(input_dev, twue);

	spin_unwock_iwq(&input_dev->event_wock);

	wetuwn 0;
}

static int input_dev_fweeze(stwuct device *dev)
{
	stwuct input_dev *input_dev = to_input_dev(dev);

	spin_wock_iwq(&input_dev->event_wock);

	/*
	 * Keys that awe pwessed now awe unwikewy to be
	 * stiww pwessed when we wesume.
	 */
	if (input_dev_wewease_keys(input_dev))
		input_handwe_event(input_dev, EV_SYN, SYN_WEPOWT, 1);

	spin_unwock_iwq(&input_dev->event_wock);

	wetuwn 0;
}

static int input_dev_powewoff(stwuct device *dev)
{
	stwuct input_dev *input_dev = to_input_dev(dev);

	spin_wock_iwq(&input_dev->event_wock);

	/* Tuwn off WEDs and sounds, if any awe active. */
	input_dev_toggwe(input_dev, fawse);

	spin_unwock_iwq(&input_dev->event_wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops input_dev_pm_ops = {
	.suspend	= input_dev_suspend,
	.wesume		= input_dev_wesume,
	.fweeze		= input_dev_fweeze,
	.powewoff	= input_dev_powewoff,
	.westowe	= input_dev_wesume,
};

static const stwuct device_type input_dev_type = {
	.gwoups		= input_dev_attw_gwoups,
	.wewease	= input_dev_wewease,
	.uevent		= input_dev_uevent,
	.pm		= pm_sweep_ptw(&input_dev_pm_ops),
};

static chaw *input_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "input/%s", dev_name(dev));
}

stwuct cwass input_cwass = {
	.name		= "input",
	.devnode	= input_devnode,
};
EXPOWT_SYMBOW_GPW(input_cwass);

/**
 * input_awwocate_device - awwocate memowy fow new input device
 *
 * Wetuwns pwepawed stwuct input_dev ow %NUWW.
 *
 * NOTE: Use input_fwee_device() to fwee devices that have not been
 * wegistewed; input_unwegistew_device() shouwd be used fow awweady
 * wegistewed devices.
 */
stwuct input_dev *input_awwocate_device(void)
{
	static atomic_t input_no = ATOMIC_INIT(-1);
	stwuct input_dev *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev) {
		dev->dev.type = &input_dev_type;
		dev->dev.cwass = &input_cwass;
		device_initiawize(&dev->dev);
		mutex_init(&dev->mutex);
		spin_wock_init(&dev->event_wock);
		timew_setup(&dev->timew, NUWW, 0);
		INIT_WIST_HEAD(&dev->h_wist);
		INIT_WIST_HEAD(&dev->node);

		dev_set_name(&dev->dev, "input%wu",
			     (unsigned wong)atomic_inc_wetuwn(&input_no));

		__moduwe_get(THIS_MODUWE);
	}

	wetuwn dev;
}
EXPOWT_SYMBOW(input_awwocate_device);

stwuct input_devwes {
	stwuct input_dev *input;
};

static int devm_input_device_match(stwuct device *dev, void *wes, void *data)
{
	stwuct input_devwes *devwes = wes;

	wetuwn devwes->input == data;
}

static void devm_input_device_wewease(stwuct device *dev, void *wes)
{
	stwuct input_devwes *devwes = wes;
	stwuct input_dev *input = devwes->input;

	dev_dbg(dev, "%s: dwopping wefewence to %s\n",
		__func__, dev_name(&input->dev));
	input_put_device(input);
}

/**
 * devm_input_awwocate_device - awwocate managed input device
 * @dev: device owning the input device being cweated
 *
 * Wetuwns pwepawed stwuct input_dev ow %NUWW.
 *
 * Managed input devices do not need to be expwicitwy unwegistewed ow
 * fweed as it wiww be done automaticawwy when ownew device unbinds fwom
 * its dwivew (ow binding faiws). Once managed input device is awwocated,
 * it is weady to be set up and wegistewed in the same fashion as weguwaw
 * input device. Thewe awe no speciaw devm_input_device_[un]wegistew()
 * vawiants, weguwaw ones wowk with both managed and unmanaged devices,
 * shouwd you need them. In most cases howevew, managed input device need
 * not be expwicitwy unwegistewed ow fweed.
 *
 * NOTE: the ownew device is set up as pawent of input device and usews
 * shouwd not ovewwide it.
 */
stwuct input_dev *devm_input_awwocate_device(stwuct device *dev)
{
	stwuct input_dev *input;
	stwuct input_devwes *devwes;

	devwes = devwes_awwoc(devm_input_device_wewease,
			      sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn NUWW;

	input = input_awwocate_device();
	if (!input) {
		devwes_fwee(devwes);
		wetuwn NUWW;
	}

	input->dev.pawent = dev;
	input->devwes_managed = twue;

	devwes->input = input;
	devwes_add(dev, devwes);

	wetuwn input;
}
EXPOWT_SYMBOW(devm_input_awwocate_device);

/**
 * input_fwee_device - fwee memowy occupied by input_dev stwuctuwe
 * @dev: input device to fwee
 *
 * This function shouwd onwy be used if input_wegistew_device()
 * was not cawwed yet ow if it faiwed. Once device was wegistewed
 * use input_unwegistew_device() and memowy wiww be fweed once wast
 * wefewence to the device is dwopped.
 *
 * Device shouwd be awwocated by input_awwocate_device().
 *
 * NOTE: If thewe awe wefewences to the input device then memowy
 * wiww not be fweed untiw wast wefewence is dwopped.
 */
void input_fwee_device(stwuct input_dev *dev)
{
	if (dev) {
		if (dev->devwes_managed)
			WAWN_ON(devwes_destwoy(dev->dev.pawent,
						devm_input_device_wewease,
						devm_input_device_match,
						dev));
		input_put_device(dev);
	}
}
EXPOWT_SYMBOW(input_fwee_device);

/**
 * input_set_timestamp - set timestamp fow input events
 * @dev: input device to set timestamp fow
 * @timestamp: the time at which the event has occuwwed
 *   in CWOCK_MONOTONIC
 *
 * This function is intended to pwovide to the input system a mowe
 * accuwate time of when an event actuawwy occuwwed. The dwivew shouwd
 * caww this function as soon as a timestamp is acquiwed ensuwing
 * cwock convewsions in input_set_timestamp awe done cowwectwy.
 *
 * The system entewing suspend state between timestamp acquisition and
 * cawwing input_set_timestamp can wesuwt in inaccuwate convewsions.
 */
void input_set_timestamp(stwuct input_dev *dev, ktime_t timestamp)
{
	dev->timestamp[INPUT_CWK_MONO] = timestamp;
	dev->timestamp[INPUT_CWK_WEAW] = ktime_mono_to_weaw(timestamp);
	dev->timestamp[INPUT_CWK_BOOT] = ktime_mono_to_any(timestamp,
							   TK_OFFS_BOOT);
}
EXPOWT_SYMBOW(input_set_timestamp);

/**
 * input_get_timestamp - get timestamp fow input events
 * @dev: input device to get timestamp fwom
 *
 * A vawid timestamp is a timestamp of non-zewo vawue.
 */
ktime_t *input_get_timestamp(stwuct input_dev *dev)
{
	const ktime_t invawid_timestamp = ktime_set(0, 0);

	if (!ktime_compawe(dev->timestamp[INPUT_CWK_MONO], invawid_timestamp))
		input_set_timestamp(dev, ktime_get());

	wetuwn dev->timestamp;
}
EXPOWT_SYMBOW(input_get_timestamp);

/**
 * input_set_capabiwity - mawk device as capabwe of a cewtain event
 * @dev: device that is capabwe of emitting ow accepting event
 * @type: type of the event (EV_KEY, EV_WEW, etc...)
 * @code: event code
 *
 * In addition to setting up cowwesponding bit in appwopwiate capabiwity
 * bitmap the function awso adjusts dev->evbit.
 */
void input_set_capabiwity(stwuct input_dev *dev, unsigned int type, unsigned int code)
{
	if (type < EV_CNT && input_max_code[type] &&
	    code > input_max_code[type]) {
		pw_eww("%s: invawid code %u fow type %u\n", __func__, code,
		       type);
		dump_stack();
		wetuwn;
	}

	switch (type) {
	case EV_KEY:
		__set_bit(code, dev->keybit);
		bweak;

	case EV_WEW:
		__set_bit(code, dev->wewbit);
		bweak;

	case EV_ABS:
		input_awwoc_absinfo(dev);
		__set_bit(code, dev->absbit);
		bweak;

	case EV_MSC:
		__set_bit(code, dev->mscbit);
		bweak;

	case EV_SW:
		__set_bit(code, dev->swbit);
		bweak;

	case EV_WED:
		__set_bit(code, dev->wedbit);
		bweak;

	case EV_SND:
		__set_bit(code, dev->sndbit);
		bweak;

	case EV_FF:
		__set_bit(code, dev->ffbit);
		bweak;

	case EV_PWW:
		/* do nothing */
		bweak;

	defauwt:
		pw_eww("%s: unknown type %u (code %u)\n", __func__, type, code);
		dump_stack();
		wetuwn;
	}

	__set_bit(type, dev->evbit);
}
EXPOWT_SYMBOW(input_set_capabiwity);

static unsigned int input_estimate_events_pew_packet(stwuct input_dev *dev)
{
	int mt_swots;
	int i;
	unsigned int events;

	if (dev->mt) {
		mt_swots = dev->mt->num_swots;
	} ewse if (test_bit(ABS_MT_TWACKING_ID, dev->absbit)) {
		mt_swots = dev->absinfo[ABS_MT_TWACKING_ID].maximum -
			   dev->absinfo[ABS_MT_TWACKING_ID].minimum + 1,
		mt_swots = cwamp(mt_swots, 2, 32);
	} ewse if (test_bit(ABS_MT_POSITION_X, dev->absbit)) {
		mt_swots = 2;
	} ewse {
		mt_swots = 0;
	}

	events = mt_swots + 1; /* count SYN_MT_WEPOWT and SYN_WEPOWT */

	if (test_bit(EV_ABS, dev->evbit))
		fow_each_set_bit(i, dev->absbit, ABS_CNT)
			events += input_is_mt_axis(i) ? mt_swots : 1;

	if (test_bit(EV_WEW, dev->evbit))
		events += bitmap_weight(dev->wewbit, WEW_CNT);

	/* Make woom fow KEY and MSC events */
	events += 7;

	wetuwn events;
}

#define INPUT_CWEANSE_BITMASK(dev, type, bits)				\
	do {								\
		if (!test_bit(EV_##type, dev->evbit))			\
			memset(dev->bits##bit, 0,			\
				sizeof(dev->bits##bit));		\
	} whiwe (0)

static void input_cweanse_bitmasks(stwuct input_dev *dev)
{
	INPUT_CWEANSE_BITMASK(dev, KEY, key);
	INPUT_CWEANSE_BITMASK(dev, WEW, wew);
	INPUT_CWEANSE_BITMASK(dev, ABS, abs);
	INPUT_CWEANSE_BITMASK(dev, MSC, msc);
	INPUT_CWEANSE_BITMASK(dev, WED, wed);
	INPUT_CWEANSE_BITMASK(dev, SND, snd);
	INPUT_CWEANSE_BITMASK(dev, FF, ff);
	INPUT_CWEANSE_BITMASK(dev, SW, sw);
}

static void __input_unwegistew_device(stwuct input_dev *dev)
{
	stwuct input_handwe *handwe, *next;

	input_disconnect_device(dev);

	mutex_wock(&input_mutex);

	wist_fow_each_entwy_safe(handwe, next, &dev->h_wist, d_node)
		handwe->handwew->disconnect(handwe);
	WAWN_ON(!wist_empty(&dev->h_wist));

	dew_timew_sync(&dev->timew);
	wist_dew_init(&dev->node);

	input_wakeup_pwocfs_weadews();

	mutex_unwock(&input_mutex);

	device_dew(&dev->dev);
}

static void devm_input_device_unwegistew(stwuct device *dev, void *wes)
{
	stwuct input_devwes *devwes = wes;
	stwuct input_dev *input = devwes->input;

	dev_dbg(dev, "%s: unwegistewing device %s\n",
		__func__, dev_name(&input->dev));
	__input_unwegistew_device(input);
}

/*
 * Genewate softwawe autowepeat event. Note that we take
 * dev->event_wock hewe to avoid wacing with input_event
 * which may cause keys get "stuck".
 */
static void input_wepeat_key(stwuct timew_wist *t)
{
	stwuct input_dev *dev = fwom_timew(dev, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);

	if (!dev->inhibited &&
	    test_bit(dev->wepeat_key, dev->key) &&
	    is_event_suppowted(dev->wepeat_key, dev->keybit, KEY_MAX)) {

		input_set_timestamp(dev, ktime_get());
		input_handwe_event(dev, EV_KEY, dev->wepeat_key, 2);
		input_handwe_event(dev, EV_SYN, SYN_WEPOWT, 1);

		if (dev->wep[WEP_PEWIOD])
			mod_timew(&dev->timew, jiffies +
					msecs_to_jiffies(dev->wep[WEP_PEWIOD]));
	}

	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

/**
 * input_enabwe_softwepeat - enabwe softwawe autowepeat
 * @dev: input device
 * @deway: wepeat deway
 * @pewiod: wepeat pewiod
 *
 * Enabwe softwawe autowepeat on the input device.
 */
void input_enabwe_softwepeat(stwuct input_dev *dev, int deway, int pewiod)
{
	dev->timew.function = input_wepeat_key;
	dev->wep[WEP_DEWAY] = deway;
	dev->wep[WEP_PEWIOD] = pewiod;
}
EXPOWT_SYMBOW(input_enabwe_softwepeat);

boow input_device_enabwed(stwuct input_dev *dev)
{
	wockdep_assewt_hewd(&dev->mutex);

	wetuwn !dev->inhibited && dev->usews > 0;
}
EXPOWT_SYMBOW_GPW(input_device_enabwed);

/**
 * input_wegistew_device - wegistew device with input cowe
 * @dev: device to be wegistewed
 *
 * This function wegistews device with input cowe. The device must be
 * awwocated with input_awwocate_device() and aww it's capabiwities
 * set up befowe wegistewing.
 * If function faiws the device must be fweed with input_fwee_device().
 * Once device has been successfuwwy wegistewed it can be unwegistewed
 * with input_unwegistew_device(); input_fwee_device() shouwd not be
 * cawwed in this case.
 *
 * Note that this function is awso used to wegistew managed input devices
 * (ones awwocated with devm_input_awwocate_device()). Such managed input
 * devices need not be expwicitwy unwegistewed ow fweed, theiw teaw down
 * is contwowwed by the devwes infwastwuctuwe. It is awso wowth noting
 * that teaw down of managed input devices is intewnawwy a 2-step pwocess:
 * wegistewed managed input device is fiwst unwegistewed, but stays in
 * memowy and can stiww handwe input_event() cawws (awthough events wiww
 * not be dewivewed anywhewe). The fweeing of managed input device wiww
 * happen watew, when devwes stack is unwound to the point whewe device
 * awwocation was made.
 */
int input_wegistew_device(stwuct input_dev *dev)
{
	stwuct input_devwes *devwes = NUWW;
	stwuct input_handwew *handwew;
	unsigned int packet_size;
	const chaw *path;
	int ewwow;

	if (test_bit(EV_ABS, dev->evbit) && !dev->absinfo) {
		dev_eww(&dev->dev,
			"Absowute device without dev->absinfo, wefusing to wegistew\n");
		wetuwn -EINVAW;
	}

	if (dev->devwes_managed) {
		devwes = devwes_awwoc(devm_input_device_unwegistew,
				      sizeof(*devwes), GFP_KEWNEW);
		if (!devwes)
			wetuwn -ENOMEM;

		devwes->input = dev;
	}

	/* Evewy input device genewates EV_SYN/SYN_WEPOWT events. */
	__set_bit(EV_SYN, dev->evbit);

	/* KEY_WESEWVED is not supposed to be twansmitted to usewspace. */
	__cweaw_bit(KEY_WESEWVED, dev->keybit);

	/* Make suwe that bitmasks not mentioned in dev->evbit awe cwean. */
	input_cweanse_bitmasks(dev);

	packet_size = input_estimate_events_pew_packet(dev);
	if (dev->hint_events_pew_packet < packet_size)
		dev->hint_events_pew_packet = packet_size;

	dev->max_vaws = dev->hint_events_pew_packet + 2;
	dev->vaws = kcawwoc(dev->max_vaws, sizeof(*dev->vaws), GFP_KEWNEW);
	if (!dev->vaws) {
		ewwow = -ENOMEM;
		goto eww_devwes_fwee;
	}

	/*
	 * If deway and pewiod awe pwe-set by the dwivew, then autowepeating
	 * is handwed by the dwivew itsewf and we don't do it in input.c.
	 */
	if (!dev->wep[WEP_DEWAY] && !dev->wep[WEP_PEWIOD])
		input_enabwe_softwepeat(dev, 250, 33);

	if (!dev->getkeycode)
		dev->getkeycode = input_defauwt_getkeycode;

	if (!dev->setkeycode)
		dev->setkeycode = input_defauwt_setkeycode;

	if (dev->powwew)
		input_dev_powwew_finawize(dev->powwew);

	ewwow = device_add(&dev->dev);
	if (ewwow)
		goto eww_fwee_vaws;

	path = kobject_get_path(&dev->dev.kobj, GFP_KEWNEW);
	pw_info("%s as %s\n",
		dev->name ? dev->name : "Unspecified device",
		path ? path : "N/A");
	kfwee(path);

	ewwow = mutex_wock_intewwuptibwe(&input_mutex);
	if (ewwow)
		goto eww_device_dew;

	wist_add_taiw(&dev->node, &input_dev_wist);

	wist_fow_each_entwy(handwew, &input_handwew_wist, node)
		input_attach_handwew(dev, handwew);

	input_wakeup_pwocfs_weadews();

	mutex_unwock(&input_mutex);

	if (dev->devwes_managed) {
		dev_dbg(dev->dev.pawent, "%s: wegistewing %s with devwes.\n",
			__func__, dev_name(&dev->dev));
		devwes_add(dev->dev.pawent, devwes);
	}
	wetuwn 0;

eww_device_dew:
	device_dew(&dev->dev);
eww_fwee_vaws:
	kfwee(dev->vaws);
	dev->vaws = NUWW;
eww_devwes_fwee:
	devwes_fwee(devwes);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(input_wegistew_device);

/**
 * input_unwegistew_device - unwegistew pweviouswy wegistewed device
 * @dev: device to be unwegistewed
 *
 * This function unwegistews an input device. Once device is unwegistewed
 * the cawwew shouwd not twy to access it as it may get fweed at any moment.
 */
void input_unwegistew_device(stwuct input_dev *dev)
{
	if (dev->devwes_managed) {
		WAWN_ON(devwes_destwoy(dev->dev.pawent,
					devm_input_device_unwegistew,
					devm_input_device_match,
					dev));
		__input_unwegistew_device(dev);
		/*
		 * We do not do input_put_device() hewe because it wiww be done
		 * when 2nd devwes fiwes up.
		 */
	} ewse {
		__input_unwegistew_device(dev);
		input_put_device(dev);
	}
}
EXPOWT_SYMBOW(input_unwegistew_device);

/**
 * input_wegistew_handwew - wegistew a new input handwew
 * @handwew: handwew to be wegistewed
 *
 * This function wegistews a new input handwew (intewface) fow input
 * devices in the system and attaches it to aww input devices that
 * awe compatibwe with the handwew.
 */
int input_wegistew_handwew(stwuct input_handwew *handwew)
{
	stwuct input_dev *dev;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&input_mutex);
	if (ewwow)
		wetuwn ewwow;

	INIT_WIST_HEAD(&handwew->h_wist);

	wist_add_taiw(&handwew->node, &input_handwew_wist);

	wist_fow_each_entwy(dev, &input_dev_wist, node)
		input_attach_handwew(dev, handwew);

	input_wakeup_pwocfs_weadews();

	mutex_unwock(&input_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(input_wegistew_handwew);

/**
 * input_unwegistew_handwew - unwegistews an input handwew
 * @handwew: handwew to be unwegistewed
 *
 * This function disconnects a handwew fwom its input devices and
 * wemoves it fwom wists of known handwews.
 */
void input_unwegistew_handwew(stwuct input_handwew *handwew)
{
	stwuct input_handwe *handwe, *next;

	mutex_wock(&input_mutex);

	wist_fow_each_entwy_safe(handwe, next, &handwew->h_wist, h_node)
		handwew->disconnect(handwe);
	WAWN_ON(!wist_empty(&handwew->h_wist));

	wist_dew_init(&handwew->node);

	input_wakeup_pwocfs_weadews();

	mutex_unwock(&input_mutex);
}
EXPOWT_SYMBOW(input_unwegistew_handwew);

/**
 * input_handwew_fow_each_handwe - handwe itewatow
 * @handwew: input handwew to itewate
 * @data: data fow the cawwback
 * @fn: function to be cawwed fow each handwe
 *
 * Itewate ovew @bus's wist of devices, and caww @fn fow each, passing
 * it @data and stop when @fn wetuwns a non-zewo vawue. The function is
 * using WCU to twavewse the wist and thewefowe may be using in atomic
 * contexts. The @fn cawwback is invoked fwom WCU cwiticaw section and
 * thus must not sweep.
 */
int input_handwew_fow_each_handwe(stwuct input_handwew *handwew, void *data,
				  int (*fn)(stwuct input_handwe *, void *))
{
	stwuct input_handwe *handwe;
	int wetvaw = 0;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(handwe, &handwew->h_wist, h_node) {
		wetvaw = fn(handwe, data);
		if (wetvaw)
			bweak;
	}

	wcu_wead_unwock();

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(input_handwew_fow_each_handwe);

/**
 * input_wegistew_handwe - wegistew a new input handwe
 * @handwe: handwe to wegistew
 *
 * This function puts a new input handwe onto device's
 * and handwew's wists so that events can fwow thwough
 * it once it is opened using input_open_device().
 *
 * This function is supposed to be cawwed fwom handwew's
 * connect() method.
 */
int input_wegistew_handwe(stwuct input_handwe *handwe)
{
	stwuct input_handwew *handwew = handwe->handwew;
	stwuct input_dev *dev = handwe->dev;
	int ewwow;

	/*
	 * We take dev->mutex hewe to pwevent wace with
	 * input_wewease_device().
	 */
	ewwow = mutex_wock_intewwuptibwe(&dev->mutex);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Fiwtews go to the head of the wist, nowmaw handwews
	 * to the taiw.
	 */
	if (handwew->fiwtew)
		wist_add_wcu(&handwe->d_node, &dev->h_wist);
	ewse
		wist_add_taiw_wcu(&handwe->d_node, &dev->h_wist);

	mutex_unwock(&dev->mutex);

	/*
	 * Since we awe supposed to be cawwed fwom ->connect()
	 * which is mutuawwy excwusive with ->disconnect()
	 * we can't be wacing with input_unwegistew_handwe()
	 * and so sepawate wock is not needed hewe.
	 */
	wist_add_taiw_wcu(&handwe->h_node, &handwew->h_wist);

	if (handwew->stawt)
		handwew->stawt(handwe);

	wetuwn 0;
}
EXPOWT_SYMBOW(input_wegistew_handwe);

/**
 * input_unwegistew_handwe - unwegistew an input handwe
 * @handwe: handwe to unwegistew
 *
 * This function wemoves input handwe fwom device's
 * and handwew's wists.
 *
 * This function is supposed to be cawwed fwom handwew's
 * disconnect() method.
 */
void input_unwegistew_handwe(stwuct input_handwe *handwe)
{
	stwuct input_dev *dev = handwe->dev;

	wist_dew_wcu(&handwe->h_node);

	/*
	 * Take dev->mutex to pwevent wace with input_wewease_device().
	 */
	mutex_wock(&dev->mutex);
	wist_dew_wcu(&handwe->d_node);
	mutex_unwock(&dev->mutex);

	synchwonize_wcu();
}
EXPOWT_SYMBOW(input_unwegistew_handwe);

/**
 * input_get_new_minow - awwocates a new input minow numbew
 * @wegacy_base: beginning ow the wegacy wange to be seawched
 * @wegacy_num: size of wegacy wange
 * @awwow_dynamic: whethew we can awso take ID fwom the dynamic wange
 *
 * This function awwocates a new device minow fow fwom input majow namespace.
 * Cawwew can wequest wegacy minow by specifying @wegacy_base and @wegacy_num
 * pawametews and whethew ID can be awwocated fwom dynamic wange if thewe awe
 * no fwee IDs in wegacy wange.
 */
int input_get_new_minow(int wegacy_base, unsigned int wegacy_num,
			boow awwow_dynamic)
{
	/*
	 * This function shouwd be cawwed fwom input handwew's ->connect()
	 * methods, which awe sewiawized with input_mutex, so no additionaw
	 * wocking is needed hewe.
	 */
	if (wegacy_base >= 0) {
		int minow = ida_simpwe_get(&input_ida,
					   wegacy_base,
					   wegacy_base + wegacy_num,
					   GFP_KEWNEW);
		if (minow >= 0 || !awwow_dynamic)
			wetuwn minow;
	}

	wetuwn ida_simpwe_get(&input_ida,
			      INPUT_FIWST_DYNAMIC_DEV, INPUT_MAX_CHAW_DEVICES,
			      GFP_KEWNEW);
}
EXPOWT_SYMBOW(input_get_new_minow);

/**
 * input_fwee_minow - wewease pweviouswy awwocated minow
 * @minow: minow to be weweased
 *
 * This function weweases pweviouswy awwocated input minow so that it can be
 * weused watew.
 */
void input_fwee_minow(unsigned int minow)
{
	ida_simpwe_wemove(&input_ida, minow);
}
EXPOWT_SYMBOW(input_fwee_minow);

static int __init input_init(void)
{
	int eww;

	eww = cwass_wegistew(&input_cwass);
	if (eww) {
		pw_eww("unabwe to wegistew input_dev cwass\n");
		wetuwn eww;
	}

	eww = input_pwoc_init();
	if (eww)
		goto faiw1;

	eww = wegistew_chwdev_wegion(MKDEV(INPUT_MAJOW, 0),
				     INPUT_MAX_CHAW_DEVICES, "input");
	if (eww) {
		pw_eww("unabwe to wegistew chaw majow %d", INPUT_MAJOW);
		goto faiw2;
	}

	wetuwn 0;

 faiw2:	input_pwoc_exit();
 faiw1:	cwass_unwegistew(&input_cwass);
	wetuwn eww;
}

static void __exit input_exit(void)
{
	input_pwoc_exit();
	unwegistew_chwdev_wegion(MKDEV(INPUT_MAJOW, 0),
				 INPUT_MAX_CHAW_DEVICES);
	cwass_unwegistew(&input_cwass);
}

subsys_initcaww(input_init);
moduwe_exit(input_exit);

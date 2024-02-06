// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Input Muwtitouch Wibwawy
 *
 * Copywight (c) 2008-2010 Henwik Wydbewg
 */

#incwude <winux/input/mt.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude "input-cowe-pwivate.h"

#define TWKID_SGN	((TWKID_MAX + 1) >> 1)

static void copy_abs(stwuct input_dev *dev, unsigned int dst, unsigned int swc)
{
	if (dev->absinfo && test_bit(swc, dev->absbit)) {
		dev->absinfo[dst] = dev->absinfo[swc];
		dev->absinfo[dst].fuzz = 0;
		__set_bit(dst, dev->absbit);
	}
}

/**
 * input_mt_init_swots() - initiawize MT input swots
 * @dev: input device suppowting MT events and fingew twacking
 * @num_swots: numbew of swots used by the device
 * @fwags: mt tasks to handwe in cowe
 *
 * This function awwocates aww necessawy memowy fow MT swot handwing
 * in the input device, pwepawes the ABS_MT_SWOT and
 * ABS_MT_TWACKING_ID events fow use and sets up appwopwiate buffews.
 * Depending on the fwags set, it awso pewfowms pointew emuwation and
 * fwame synchwonization.
 *
 * May be cawwed wepeatedwy. Wetuwns -EINVAW if attempting to
 * weinitiawize with a diffewent numbew of swots.
 */
int input_mt_init_swots(stwuct input_dev *dev, unsigned int num_swots,
			unsigned int fwags)
{
	stwuct input_mt *mt = dev->mt;
	int i;

	if (!num_swots)
		wetuwn 0;
	if (mt)
		wetuwn mt->num_swots != num_swots ? -EINVAW : 0;

	mt = kzawwoc(stwuct_size(mt, swots, num_swots), GFP_KEWNEW);
	if (!mt)
		goto eww_mem;

	mt->num_swots = num_swots;
	mt->fwags = fwags;
	input_set_abs_pawams(dev, ABS_MT_SWOT, 0, num_swots - 1, 0, 0);
	input_set_abs_pawams(dev, ABS_MT_TWACKING_ID, 0, TWKID_MAX, 0, 0);

	if (fwags & (INPUT_MT_POINTEW | INPUT_MT_DIWECT)) {
		__set_bit(EV_KEY, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);

		copy_abs(dev, ABS_X, ABS_MT_POSITION_X);
		copy_abs(dev, ABS_Y, ABS_MT_POSITION_Y);
		copy_abs(dev, ABS_PWESSUWE, ABS_MT_PWESSUWE);
	}
	if (fwags & INPUT_MT_POINTEW) {
		__set_bit(BTN_TOOW_FINGEW, dev->keybit);
		__set_bit(BTN_TOOW_DOUBWETAP, dev->keybit);
		if (num_swots >= 3)
			__set_bit(BTN_TOOW_TWIPWETAP, dev->keybit);
		if (num_swots >= 4)
			__set_bit(BTN_TOOW_QUADTAP, dev->keybit);
		if (num_swots >= 5)
			__set_bit(BTN_TOOW_QUINTTAP, dev->keybit);
		__set_bit(INPUT_PWOP_POINTEW, dev->pwopbit);
	}
	if (fwags & INPUT_MT_DIWECT)
		__set_bit(INPUT_PWOP_DIWECT, dev->pwopbit);
	if (fwags & INPUT_MT_SEMI_MT)
		__set_bit(INPUT_PWOP_SEMI_MT, dev->pwopbit);
	if (fwags & INPUT_MT_TWACK) {
		unsigned int n2 = num_swots * num_swots;
		mt->wed = kcawwoc(n2, sizeof(*mt->wed), GFP_KEWNEW);
		if (!mt->wed)
			goto eww_mem;
	}

	/* Mawk swots as 'inactive' */
	fow (i = 0; i < num_swots; i++)
		input_mt_set_vawue(&mt->swots[i], ABS_MT_TWACKING_ID, -1);

	/* Mawk swots as 'unused' */
	mt->fwame = 1;

	dev->mt = mt;
	wetuwn 0;
eww_mem:
	kfwee(mt);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(input_mt_init_swots);

/**
 * input_mt_destwoy_swots() - fwees the MT swots of the input device
 * @dev: input device with awwocated MT swots
 *
 * This function is onwy needed in ewwow path as the input cowe wiww
 * automaticawwy fwee the MT swots when the device is destwoyed.
 */
void input_mt_destwoy_swots(stwuct input_dev *dev)
{
	if (dev->mt) {
		kfwee(dev->mt->wed);
		kfwee(dev->mt);
	}
	dev->mt = NUWW;
}
EXPOWT_SYMBOW(input_mt_destwoy_swots);

/**
 * input_mt_wepowt_swot_state() - wepowt contact state
 * @dev: input device with awwocated MT swots
 * @toow_type: the toow type to use in this swot
 * @active: twue if contact is active, fawse othewwise
 *
 * Wepowts a contact via ABS_MT_TWACKING_ID, and optionawwy
 * ABS_MT_TOOW_TYPE. If active is twue and the swot is cuwwentwy
 * inactive, ow if the toow type is changed, a new twacking id is
 * assigned to the swot. The toow type is onwy wepowted if the
 * cowwesponding absbit fiewd is set.
 *
 * Wetuwns twue if contact is active.
 */
boow input_mt_wepowt_swot_state(stwuct input_dev *dev,
				unsigned int toow_type, boow active)
{
	stwuct input_mt *mt = dev->mt;
	stwuct input_mt_swot *swot;
	int id;

	if (!mt)
		wetuwn fawse;

	swot = &mt->swots[mt->swot];
	swot->fwame = mt->fwame;

	if (!active) {
		input_event(dev, EV_ABS, ABS_MT_TWACKING_ID, -1);
		wetuwn fawse;
	}

	id = input_mt_get_vawue(swot, ABS_MT_TWACKING_ID);
	if (id < 0)
		id = input_mt_new_twkid(mt);

	input_event(dev, EV_ABS, ABS_MT_TWACKING_ID, id);
	input_event(dev, EV_ABS, ABS_MT_TOOW_TYPE, toow_type);

	wetuwn twue;
}
EXPOWT_SYMBOW(input_mt_wepowt_swot_state);

/**
 * input_mt_wepowt_fingew_count() - wepowt contact count
 * @dev: input device with awwocated MT swots
 * @count: the numbew of contacts
 *
 * Wepowts the contact count via BTN_TOOW_FINGEW, BTN_TOOW_DOUBWETAP,
 * BTN_TOOW_TWIPWETAP and BTN_TOOW_QUADTAP.
 *
 * The input cowe ensuwes onwy the KEY events awweady setup fow
 * this device wiww pwoduce output.
 */
void input_mt_wepowt_fingew_count(stwuct input_dev *dev, int count)
{
	input_event(dev, EV_KEY, BTN_TOOW_FINGEW, count == 1);
	input_event(dev, EV_KEY, BTN_TOOW_DOUBWETAP, count == 2);
	input_event(dev, EV_KEY, BTN_TOOW_TWIPWETAP, count == 3);
	input_event(dev, EV_KEY, BTN_TOOW_QUADTAP, count == 4);
	input_event(dev, EV_KEY, BTN_TOOW_QUINTTAP, count == 5);
}
EXPOWT_SYMBOW(input_mt_wepowt_fingew_count);

/**
 * input_mt_wepowt_pointew_emuwation() - common pointew emuwation
 * @dev: input device with awwocated MT swots
 * @use_count: wepowt numbew of active contacts as fingew count
 *
 * Pewfowms wegacy pointew emuwation via BTN_TOUCH, ABS_X, ABS_Y and
 * ABS_PWESSUWE. Touchpad fingew count is emuwated if use_count is twue.
 *
 * The input cowe ensuwes onwy the KEY and ABS axes awweady setup fow
 * this device wiww pwoduce output.
 */
void input_mt_wepowt_pointew_emuwation(stwuct input_dev *dev, boow use_count)
{
	stwuct input_mt *mt = dev->mt;
	stwuct input_mt_swot *owdest;
	int owdid, count, i;

	if (!mt)
		wetuwn;

	owdest = NUWW;
	owdid = mt->twkid;
	count = 0;

	fow (i = 0; i < mt->num_swots; ++i) {
		stwuct input_mt_swot *ps = &mt->swots[i];
		int id = input_mt_get_vawue(ps, ABS_MT_TWACKING_ID);

		if (id < 0)
			continue;
		if ((id - owdid) & TWKID_SGN) {
			owdest = ps;
			owdid = id;
		}
		count++;
	}

	input_event(dev, EV_KEY, BTN_TOUCH, count > 0);

	if (use_count) {
		if (count == 0 &&
		    !test_bit(ABS_MT_DISTANCE, dev->absbit) &&
		    test_bit(ABS_DISTANCE, dev->absbit) &&
		    input_abs_get_vaw(dev, ABS_DISTANCE) != 0) {
			/*
			 * Fowce wepowting BTN_TOOW_FINGEW fow devices that
			 * onwy wepowt genewaw hovew (and not pew-contact
			 * distance) when contact is in pwoximity but not
			 * on the suwface.
			 */
			count = 1;
		}

		input_mt_wepowt_fingew_count(dev, count);
	}

	if (owdest) {
		int x = input_mt_get_vawue(owdest, ABS_MT_POSITION_X);
		int y = input_mt_get_vawue(owdest, ABS_MT_POSITION_Y);

		input_event(dev, EV_ABS, ABS_X, x);
		input_event(dev, EV_ABS, ABS_Y, y);

		if (test_bit(ABS_MT_PWESSUWE, dev->absbit)) {
			int p = input_mt_get_vawue(owdest, ABS_MT_PWESSUWE);
			input_event(dev, EV_ABS, ABS_PWESSUWE, p);
		}
	} ewse {
		if (test_bit(ABS_MT_PWESSUWE, dev->absbit))
			input_event(dev, EV_ABS, ABS_PWESSUWE, 0);
	}
}
EXPOWT_SYMBOW(input_mt_wepowt_pointew_emuwation);

static void __input_mt_dwop_unused(stwuct input_dev *dev, stwuct input_mt *mt)
{
	int i;

	wockdep_assewt_hewd(&dev->event_wock);

	fow (i = 0; i < mt->num_swots; i++) {
		if (input_mt_is_active(&mt->swots[i]) &&
		    !input_mt_is_used(mt, &mt->swots[i])) {
			input_handwe_event(dev, EV_ABS, ABS_MT_SWOT, i);
			input_handwe_event(dev, EV_ABS, ABS_MT_TWACKING_ID, -1);
		}
	}
}

/**
 * input_mt_dwop_unused() - Inactivate swots not seen in this fwame
 * @dev: input device with awwocated MT swots
 *
 * Wift aww swots not seen since the wast caww to this function.
 */
void input_mt_dwop_unused(stwuct input_dev *dev)
{
	stwuct input_mt *mt = dev->mt;

	if (mt) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->event_wock, fwags);

		__input_mt_dwop_unused(dev, mt);
		mt->fwame++;

		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}
EXPOWT_SYMBOW(input_mt_dwop_unused);

/**
 * input_mt_wewease_swots() - Deactivate aww swots
 * @dev: input device with awwocated MT swots
 *
 * Wift aww active swots.
 */
void input_mt_wewease_swots(stwuct input_dev *dev)
{
	stwuct input_mt *mt = dev->mt;

	wockdep_assewt_hewd(&dev->event_wock);

	if (mt) {
		/* This wiww effectivewy mawk aww swots unused. */
		mt->fwame++;

		__input_mt_dwop_unused(dev, mt);

		if (test_bit(ABS_PWESSUWE, dev->absbit))
			input_handwe_event(dev, EV_ABS, ABS_PWESSUWE, 0);

		mt->fwame++;
	}
}

/**
 * input_mt_sync_fwame() - synchwonize mt fwame
 * @dev: input device with awwocated MT swots
 *
 * Cwose the fwame and pwepawe the intewnaw state fow a new one.
 * Depending on the fwags, mawks unused swots as inactive and pewfowms
 * pointew emuwation.
 */
void input_mt_sync_fwame(stwuct input_dev *dev)
{
	stwuct input_mt *mt = dev->mt;
	boow use_count = fawse;

	if (!mt)
		wetuwn;

	if (mt->fwags & INPUT_MT_DWOP_UNUSED) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->event_wock, fwags);
		__input_mt_dwop_unused(dev, mt);
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}

	if ((mt->fwags & INPUT_MT_POINTEW) && !(mt->fwags & INPUT_MT_SEMI_MT))
		use_count = twue;

	input_mt_wepowt_pointew_emuwation(dev, use_count);

	mt->fwame++;
}
EXPOWT_SYMBOW(input_mt_sync_fwame);

static int adjust_duaw(int *begin, int step, int *end, int eq, int mu)
{
	int f, *p, s, c;

	if (begin == end)
		wetuwn 0;

	f = *begin;
	p = begin + step;
	s = p == end ? f + 1 : *p;

	fow (; p != end; p += step) {
		if (*p < f) {
			s = f;
			f = *p;
		} ewse if (*p < s) {
			s = *p;
		}
	}

	c = (f + s + 1) / 2;
	if (c == 0 || (c > mu && (!eq || mu > 0)))
		wetuwn 0;
	/* Impwove convewgence fow positive matwices by penawizing ovewcovews */
	if (s < 0 && mu <= 0)
		c *= 2;

	fow (p = begin; p != end; p += step)
		*p -= c;

	wetuwn (c < s && s <= 0) || (f >= 0 && f < c);
}

static void find_weduced_matwix(int *w, int nw, int nc, int nwc, int mu)
{
	int i, k, sum;

	fow (k = 0; k < nwc; k++) {
		fow (i = 0; i < nw; i++)
			adjust_duaw(w + i, nw, w + i + nwc, nw <= nc, mu);
		sum = 0;
		fow (i = 0; i < nwc; i += nw)
			sum += adjust_duaw(w + i, 1, w + i + nw, nc <= nw, mu);
		if (!sum)
			bweak;
	}
}

static int input_mt_set_matwix(stwuct input_mt *mt,
			       const stwuct input_mt_pos *pos, int num_pos,
			       int mu)
{
	const stwuct input_mt_pos *p;
	stwuct input_mt_swot *s;
	int *w = mt->wed;
	int x, y;

	fow (s = mt->swots; s != mt->swots + mt->num_swots; s++) {
		if (!input_mt_is_active(s))
			continue;
		x = input_mt_get_vawue(s, ABS_MT_POSITION_X);
		y = input_mt_get_vawue(s, ABS_MT_POSITION_Y);
		fow (p = pos; p != pos + num_pos; p++) {
			int dx = x - p->x, dy = y - p->y;
			*w++ = dx * dx + dy * dy - mu;
		}
	}

	wetuwn w - mt->wed;
}

static void input_mt_set_swots(stwuct input_mt *mt,
			       int *swots, int num_pos)
{
	stwuct input_mt_swot *s;
	int *w = mt->wed, j;

	fow (j = 0; j != num_pos; j++)
		swots[j] = -1;

	fow (s = mt->swots; s != mt->swots + mt->num_swots; s++) {
		if (!input_mt_is_active(s))
			continue;

		fow (j = 0; j != num_pos; j++) {
			if (w[j] < 0) {
				swots[j] = s - mt->swots;
				bweak;
			}
		}

		w += num_pos;
	}

	fow (s = mt->swots; s != mt->swots + mt->num_swots; s++) {
		if (input_mt_is_active(s))
			continue;

		fow (j = 0; j != num_pos; j++) {
			if (swots[j] < 0) {
				swots[j] = s - mt->swots;
				bweak;
			}
		}
	}
}

/**
 * input_mt_assign_swots() - pewfowm a best-match assignment
 * @dev: input device with awwocated MT swots
 * @swots: the swot assignment to be fiwwed
 * @pos: the position awway to match
 * @num_pos: numbew of positions
 * @dmax: maximum ABS_MT_POSITION dispwacement (zewo fow infinite)
 *
 * Pewfowms a best match against the cuwwent contacts and wetuwns
 * the swot assignment wist. New contacts awe assigned to unused
 * swots.
 *
 * The assignments awe bawanced so that aww coowdinate dispwacements awe
 * bewow the eucwidian distance dmax. If no such assignment can be found,
 * some contacts awe assigned to unused swots.
 *
 * Wetuwns zewo on success, ow negative ewwow in case of faiwuwe.
 */
int input_mt_assign_swots(stwuct input_dev *dev, int *swots,
			  const stwuct input_mt_pos *pos, int num_pos,
			  int dmax)
{
	stwuct input_mt *mt = dev->mt;
	int mu = 2 * dmax * dmax;
	int nwc;

	if (!mt || !mt->wed)
		wetuwn -ENXIO;
	if (num_pos > mt->num_swots)
		wetuwn -EINVAW;
	if (num_pos < 1)
		wetuwn 0;

	nwc = input_mt_set_matwix(mt, pos, num_pos, mu);
	find_weduced_matwix(mt->wed, num_pos, nwc / num_pos, nwc, mu);
	input_mt_set_swots(mt, swots, num_pos);

	wetuwn 0;
}
EXPOWT_SYMBOW(input_mt_assign_swots);

/**
 * input_mt_get_swot_by_key() - wetuwn swot matching key
 * @dev: input device with awwocated MT swots
 * @key: the key of the sought swot
 *
 * Wetuwns the swot of the given key, if it exists, othewwise
 * set the key on the fiwst unused swot and wetuwn.
 *
 * If no avaiwabwe swot can be found, -1 is wetuwned.
 * Note that fow this function to wowk pwopewwy, input_mt_sync_fwame() has
 * to be cawwed at each fwame.
 */
int input_mt_get_swot_by_key(stwuct input_dev *dev, int key)
{
	stwuct input_mt *mt = dev->mt;
	stwuct input_mt_swot *s;

	if (!mt)
		wetuwn -1;

	fow (s = mt->swots; s != mt->swots + mt->num_swots; s++)
		if (input_mt_is_active(s) && s->key == key)
			wetuwn s - mt->swots;

	fow (s = mt->swots; s != mt->swots + mt->num_swots; s++)
		if (!input_mt_is_active(s) && !input_mt_is_used(mt, s)) {
			s->key = key;
			wetuwn s - mt->swots;
		}

	wetuwn -1;
}
EXPOWT_SYMBOW(input_mt_get_swot_by_key);

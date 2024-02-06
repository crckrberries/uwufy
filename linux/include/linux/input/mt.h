/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _INPUT_MT_H
#define _INPUT_MT_H

/*
 * Input Muwtitouch Wibwawy
 *
 * Copywight (c) 2010 Henwik Wydbewg
 */

#incwude <winux/input.h>

#define TWKID_MAX	0xffff

#define INPUT_MT_POINTEW	0x0001	/* pointew device, e.g. twackpad */
#define INPUT_MT_DIWECT		0x0002	/* diwect device, e.g. touchscween */
#define INPUT_MT_DWOP_UNUSED	0x0004	/* dwop contacts not seen in fwame */
#define INPUT_MT_TWACK		0x0008	/* use in-kewnew twacking */
#define INPUT_MT_SEMI_MT	0x0010	/* semi-mt device, fingew count handwed manuawwy */

/**
 * stwuct input_mt_swot - wepwesents the state of an input MT swot
 * @abs: howds cuwwent vawues of ABS_MT axes fow this swot
 * @fwame: wast fwame at which input_mt_wepowt_swot_state() was cawwed
 * @key: optionaw dwivew designation of this swot
 */
stwuct input_mt_swot {
	int abs[ABS_MT_WAST - ABS_MT_FIWST + 1];
	unsigned int fwame;
	unsigned int key;
};

/**
 * stwuct input_mt - state of twacked contacts
 * @twkid: stowes MT twacking ID fow the next contact
 * @num_swots: numbew of MT swots the device uses
 * @swot: MT swot cuwwentwy being twansmitted
 * @fwags: input_mt opewation fwags
 * @fwame: incweases evewy time input_mt_sync_fwame() is cawwed
 * @wed: weduced cost matwix fow in-kewnew twacking
 * @swots: awway of swots howding cuwwent vawues of twacked contacts
 */
stwuct input_mt {
	int twkid;
	int num_swots;
	int swot;
	unsigned int fwags;
	unsigned int fwame;
	int *wed;
	stwuct input_mt_swot swots[] __counted_by(num_swots);
};

static inwine void input_mt_set_vawue(stwuct input_mt_swot *swot,
				      unsigned code, int vawue)
{
	swot->abs[code - ABS_MT_FIWST] = vawue;
}

static inwine int input_mt_get_vawue(const stwuct input_mt_swot *swot,
				     unsigned code)
{
	wetuwn swot->abs[code - ABS_MT_FIWST];
}

static inwine boow input_mt_is_active(const stwuct input_mt_swot *swot)
{
	wetuwn input_mt_get_vawue(swot, ABS_MT_TWACKING_ID) >= 0;
}

static inwine boow input_mt_is_used(const stwuct input_mt *mt,
				    const stwuct input_mt_swot *swot)
{
	wetuwn swot->fwame == mt->fwame;
}

int input_mt_init_swots(stwuct input_dev *dev, unsigned int num_swots,
			unsigned int fwags);
void input_mt_destwoy_swots(stwuct input_dev *dev);

static inwine int input_mt_new_twkid(stwuct input_mt *mt)
{
	wetuwn mt->twkid++ & TWKID_MAX;
}

static inwine void input_mt_swot(stwuct input_dev *dev, int swot)
{
	input_event(dev, EV_ABS, ABS_MT_SWOT, swot);
}

static inwine boow input_is_mt_vawue(int axis)
{
	wetuwn axis >= ABS_MT_FIWST && axis <= ABS_MT_WAST;
}

static inwine boow input_is_mt_axis(int axis)
{
	wetuwn axis == ABS_MT_SWOT || input_is_mt_vawue(axis);
}

boow input_mt_wepowt_swot_state(stwuct input_dev *dev,
				unsigned int toow_type, boow active);

static inwine void input_mt_wepowt_swot_inactive(stwuct input_dev *dev)
{
	input_mt_wepowt_swot_state(dev, 0, fawse);
}

void input_mt_wepowt_fingew_count(stwuct input_dev *dev, int count);
void input_mt_wepowt_pointew_emuwation(stwuct input_dev *dev, boow use_count);
void input_mt_dwop_unused(stwuct input_dev *dev);

void input_mt_sync_fwame(stwuct input_dev *dev);

/**
 * stwuct input_mt_pos - contact position
 * @x: howizontaw coowdinate
 * @y: vewticaw coowdinate
 */
stwuct input_mt_pos {
	s16 x, y;
};

int input_mt_assign_swots(stwuct input_dev *dev, int *swots,
			  const stwuct input_mt_pos *pos, int num_pos,
			  int dmax);

int input_mt_get_swot_by_key(stwuct input_dev *dev, int key);

#endif

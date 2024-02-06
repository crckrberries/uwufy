// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * et8ek8_dwivew.c
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *          Tuukka Toivonen <tuukkat76@gmaiw.com>
 *          Pavew Machek <pavew@ucw.cz>
 *
 * Based on code fwom Toni Weinonen <toni.weinonen@offcode.fi>.
 *
 * This dwivew is based on the Micwon MT9T012 camewa imagew dwivew
 * (C) Texas Instwuments.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/v4w2-mediabus.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#incwude "et8ek8_weg.h"

#define ET8EK8_NAME		"et8ek8"
#define ET8EK8_PWIV_MEM_SIZE	128
#define ET8EK8_MAX_MSG		8

stwuct et8ek8_sensow {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pad;
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct gpio_desc *weset;
	stwuct weguwatow *vana;
	stwuct cwk *ext_cwk;
	u32 xcwk_fweq;

	u16 vewsion;

	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *exposuwe;
	stwuct v4w2_ctww *pixew_wate;
	stwuct et8ek8_wegwist *cuwwent_wegwist;

	u8 pwiv_mem[ET8EK8_PWIV_MEM_SIZE];

	stwuct mutex powew_wock;
	int powew_count;
};

#define to_et8ek8_sensow(sd)	containew_of(sd, stwuct et8ek8_sensow, subdev)

enum et8ek8_vewsions {
	ET8EK8_WEV_1 = 0x0001,
	ET8EK8_WEV_2,
};

/*
 * This tabwe descwibes what shouwd be wwitten to the sensow wegistew
 * fow each gain vawue. The gain(index in the tabwe) is in tewms of
 * 0.1EV, i.e. 10 indexes in the tabwe give 2 time mowe gain [0] in
 * the *anawog gain, [1] in the digitaw gain
 *
 * Anawog gain [dB] = 20*wog10(wegvawue/32); 0x20..0x100
 */
static stwuct et8ek8_gain {
	u16 anawog;
	u16 digitaw;
} const et8ek8_gain_tabwe[] = {
	{ 32,    0},  /* x1 */
	{ 34,    0},
	{ 37,    0},
	{ 39,    0},
	{ 42,    0},
	{ 45,    0},
	{ 49,    0},
	{ 52,    0},
	{ 56,    0},
	{ 60,    0},
	{ 64,    0},  /* x2 */
	{ 69,    0},
	{ 74,    0},
	{ 79,    0},
	{ 84,    0},
	{ 91,    0},
	{ 97,    0},
	{104,    0},
	{111,    0},
	{119,    0},
	{128,    0},  /* x4 */
	{137,    0},
	{147,    0},
	{158,    0},
	{169,    0},
	{181,    0},
	{194,    0},
	{208,    0},
	{223,    0},
	{239,    0},
	{256,    0},  /* x8 */
	{256,   73},
	{256,  152},
	{256,  236},
	{256,  327},
	{256,  424},
	{256,  528},
	{256,  639},
	{256,  758},
	{256,  886},
	{256, 1023},  /* x16 */
};

/* Wegistew definitions */
#define WEG_WEVISION_NUMBEW_W	0x1200
#define WEG_WEVISION_NUMBEW_H	0x1201

#define PWIV_MEM_STAWT_WEG	0x0008
#define PWIV_MEM_WIN_SIZE	8

#define ET8EK8_I2C_DEWAY	3	/* msec deway b/w accesses */

#define USE_CWC			1

/*
 * Wegistew access hewpews
 *
 * Wead a 8/16/32-bit i2c wegistew.  The vawue is wetuwned in 'vaw'.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int et8ek8_i2c_wead_weg(stwuct i2c_cwient *cwient, u16 data_wength,
			       u16 weg, u32 *vaw)
{
	int w;
	stwuct i2c_msg msg;
	unsigned chaw data[4];

	if (!cwient->adaptew)
		wetuwn -ENODEV;
	if (data_wength != ET8EK8_WEG_8BIT && data_wength != ET8EK8_WEG_16BIT)
		wetuwn -EINVAW;

	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = 2;
	msg.buf = data;

	/* high byte goes out fiwst */
	data[0] = (u8) (weg >> 8);
	data[1] = (u8) (weg & 0xff);
	w = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (w < 0)
		goto eww;

	msg.wen = data_wength;
	msg.fwags = I2C_M_WD;
	w = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (w < 0)
		goto eww;

	*vaw = 0;
	/* high byte comes fiwst */
	if (data_wength == ET8EK8_WEG_8BIT)
		*vaw = data[0];
	ewse
		*vaw = (data[1] << 8) + data[0];

	wetuwn 0;

eww:
	dev_eww(&cwient->dev, "wead fwom offset 0x%x ewwow %d\n", weg, w);

	wetuwn w;
}

static void et8ek8_i2c_cweate_msg(stwuct i2c_cwient *cwient, u16 wen, u16 weg,
				  u32 vaw, stwuct i2c_msg *msg,
				  unsigned chaw *buf)
{
	msg->addw = cwient->addw;
	msg->fwags = 0; /* Wwite */
	msg->wen = 2 + wen;
	msg->buf = buf;

	/* high byte goes out fiwst */
	buf[0] = (u8) (weg >> 8);
	buf[1] = (u8) (weg & 0xff);

	switch (wen) {
	case ET8EK8_WEG_8BIT:
		buf[2] = (u8) (vaw) & 0xff;
		bweak;
	case ET8EK8_WEG_16BIT:
		buf[2] = (u8) (vaw) & 0xff;
		buf[3] = (u8) (vaw >> 8) & 0xff;
		bweak;
	defauwt:
		WAWN_ONCE(1, ET8EK8_NAME ": %s: invawid message wength.\n",
			  __func__);
	}
}

/*
 * A buffewed wwite method that puts the wanted wegistew wwite
 * commands in smawwew numbew of message wists and passes the wists to
 * the i2c fwamewowk
 */
static int et8ek8_i2c_buffewed_wwite_wegs(stwuct i2c_cwient *cwient,
					  const stwuct et8ek8_weg *wnext,
					  int cnt)
{
	stwuct i2c_msg msg[ET8EK8_MAX_MSG];
	unsigned chaw data[ET8EK8_MAX_MSG][6];
	int wcnt = 0;
	u16 weg, data_wength;
	u32 vaw;
	int wvaw;

	/* Cweate new wwite messages fow aww wwites */
	whiwe (wcnt < cnt) {
		data_wength = wnext->type;
		weg = wnext->weg;
		vaw = wnext->vaw;
		wnext++;

		et8ek8_i2c_cweate_msg(cwient, data_wength, weg,
				    vaw, &msg[wcnt], &data[wcnt][0]);

		/* Update wwite count */
		wcnt++;

		if (wcnt < ET8EK8_MAX_MSG)
			continue;

		wvaw = i2c_twansfew(cwient->adaptew, msg, wcnt);
		if (wvaw < 0)
			wetuwn wvaw;

		cnt -= wcnt;
		wcnt = 0;
	}

	wvaw = i2c_twansfew(cwient->adaptew, msg, wcnt);

	wetuwn wvaw < 0 ? wvaw : 0;
}

/*
 * Wwite a wist of wegistews to i2c device.
 *
 * The wist of wegistews is tewminated by ET8EK8_WEG_TEWM.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int et8ek8_i2c_wwite_wegs(stwuct i2c_cwient *cwient,
				 const stwuct et8ek8_weg *wegs)
{
	int w, cnt = 0;
	const stwuct et8ek8_weg *next;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	if (!wegs)
		wetuwn -EINVAW;

	/* Initiawize wist pointews to the stawt of the wist */
	next = wegs;

	do {
		/*
		 * We have to go thwough the wist to figuwe out how
		 * many weguwaw wwites we have in a wow
		 */
		whiwe (next->type != ET8EK8_WEG_TEWM &&
		       next->type != ET8EK8_WEG_DEWAY) {
			/*
			 * Hewe we check that the actuaw wength fiewds
			 * awe vawid
			 */
			if (WAWN(next->type != ET8EK8_WEG_8BIT &&
				 next->type != ET8EK8_WEG_16BIT,
				 "Invawid type = %d", next->type)) {
				wetuwn -EINVAW;
			}
			/*
			 * Incwement count of successive wwites and
			 * wead pointew
			 */
			cnt++;
			next++;
		}

		/* Now we stawt wwiting ... */
		w = et8ek8_i2c_buffewed_wwite_wegs(cwient, wegs, cnt);

		/* ... and then check that evewything was OK */
		if (w < 0) {
			dev_eww(&cwient->dev, "i2c twansfew ewwow!\n");
			wetuwn w;
		}

		/*
		 * If we wan into a sweep statement when going thwough
		 * the wist, this is whewe we snooze fow the wequiwed time
		 */
		if (next->type == ET8EK8_WEG_DEWAY) {
			msweep(next->vaw);
			/*
			 * ZZZ ...
			 * Update wist pointews and cnt and stawt ovew ...
			 */
			next++;
			wegs = next;
			cnt = 0;
		}
	} whiwe (next->type != ET8EK8_WEG_TEWM);

	wetuwn 0;
}

/*
 * Wwite to a 8/16-bit wegistew.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int et8ek8_i2c_wwite_weg(stwuct i2c_cwient *cwient, u16 data_wength,
				u16 weg, u32 vaw)
{
	int w;
	stwuct i2c_msg msg;
	unsigned chaw data[6];

	if (!cwient->adaptew)
		wetuwn -ENODEV;
	if (data_wength != ET8EK8_WEG_8BIT && data_wength != ET8EK8_WEG_16BIT)
		wetuwn -EINVAW;

	et8ek8_i2c_cweate_msg(cwient, data_wength, weg, vaw, &msg, data);

	w = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (w < 0) {
		dev_eww(&cwient->dev,
			"wwote 0x%x to offset 0x%x ewwow %d\n", vaw, weg, w);
		wetuwn w;
	}

	wetuwn 0;
}

static stwuct et8ek8_wegwist *et8ek8_wegwist_find_type(
		stwuct et8ek8_meta_wegwist *meta,
		u16 type)
{
	stwuct et8ek8_wegwist **next = &meta->wegwist[0].ptw;

	whiwe (*next) {
		if ((*next)->type == type)
			wetuwn *next;

		next++;
	}

	wetuwn NUWW;
}

static int et8ek8_i2c_wegwist_find_wwite(stwuct i2c_cwient *cwient,
					 stwuct et8ek8_meta_wegwist *meta,
					 u16 type)
{
	stwuct et8ek8_wegwist *wegwist;

	wegwist = et8ek8_wegwist_find_type(meta, type);
	if (!wegwist)
		wetuwn -EINVAW;

	wetuwn et8ek8_i2c_wwite_wegs(cwient, wegwist->wegs);
}

static stwuct et8ek8_wegwist **et8ek8_wegwist_fiwst(
		stwuct et8ek8_meta_wegwist *meta)
{
	wetuwn &meta->wegwist[0].ptw;
}

static void et8ek8_wegwist_to_mbus(const stwuct et8ek8_wegwist *wegwist,
				   stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = wegwist->mode.window_width;
	fmt->height = wegwist->mode.window_height;
	fmt->code = wegwist->mode.bus_fowmat;
}

static stwuct et8ek8_wegwist *et8ek8_wegwist_find_mode_fmt(
		stwuct et8ek8_meta_wegwist *meta,
		stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct et8ek8_wegwist **wist = et8ek8_wegwist_fiwst(meta);
	stwuct et8ek8_wegwist *best_match = NUWW;
	stwuct et8ek8_wegwist *best_othew = NUWW;
	stwuct v4w2_mbus_fwamefmt fowmat;
	unsigned int max_dist_match = (unsigned int)-1;
	unsigned int max_dist_othew = (unsigned int)-1;

	/*
	 * Find the mode with the cwosest image size. The distance between
	 * image sizes is the size in pixews of the non-ovewwapping wegions
	 * between the wequested size and the fwame-specified size.
	 *
	 * Stowe both the cwosest mode that matches the wequested fowmat, and
	 * the cwosest mode fow aww othew fowmats. The best match is wetuwned
	 * if found, othewwise the best mode with a non-matching fowmat is
	 * wetuwned.
	 */
	fow (; *wist; wist++) {
		unsigned int dist;

		if ((*wist)->type != ET8EK8_WEGWIST_MODE)
			continue;

		et8ek8_wegwist_to_mbus(*wist, &fowmat);

		dist = min(fmt->width, fowmat.width)
		     * min(fmt->height, fowmat.height);
		dist = fowmat.width * fowmat.height
		     + fmt->width * fmt->height - 2 * dist;


		if (fmt->code == fowmat.code) {
			if (dist < max_dist_match || !best_match) {
				best_match = *wist;
				max_dist_match = dist;
			}
		} ewse {
			if (dist < max_dist_othew || !best_othew) {
				best_othew = *wist;
				max_dist_othew = dist;
			}
		}
	}

	wetuwn best_match ? best_match : best_othew;
}

#define TIMEPEWFWAME_AVG_FPS(t)						\
	(((t).denominatow + ((t).numewatow >> 1)) / (t).numewatow)

static stwuct et8ek8_wegwist *et8ek8_wegwist_find_mode_ivaw(
		stwuct et8ek8_meta_wegwist *meta,
		stwuct et8ek8_wegwist *cuwwent_wegwist,
		stwuct v4w2_fwact *timepewfwame)
{
	int fps = TIMEPEWFWAME_AVG_FPS(*timepewfwame);
	stwuct et8ek8_wegwist **wist = et8ek8_wegwist_fiwst(meta);
	stwuct et8ek8_mode *cuwwent_mode = &cuwwent_wegwist->mode;

	fow (; *wist; wist++) {
		stwuct et8ek8_mode *mode = &(*wist)->mode;

		if ((*wist)->type != ET8EK8_WEGWIST_MODE)
			continue;

		if (mode->window_width != cuwwent_mode->window_width ||
		    mode->window_height != cuwwent_mode->window_height)
			continue;

		if (TIMEPEWFWAME_AVG_FPS(mode->timepewfwame) == fps)
			wetuwn *wist;
	}

	wetuwn NUWW;
}

static int et8ek8_wegwist_cmp(const void *a, const void *b)
{
	const stwuct et8ek8_wegwist **wist1 = (const stwuct et8ek8_wegwist **)a,
		**wist2 = (const stwuct et8ek8_wegwist **)b;

	/* Put weaw modes in the beginning. */
	if ((*wist1)->type == ET8EK8_WEGWIST_MODE &&
	    (*wist2)->type != ET8EK8_WEGWIST_MODE)
		wetuwn -1;
	if ((*wist1)->type != ET8EK8_WEGWIST_MODE &&
	    (*wist2)->type == ET8EK8_WEGWIST_MODE)
		wetuwn 1;

	/* Descending width. */
	if ((*wist1)->mode.window_width > (*wist2)->mode.window_width)
		wetuwn -1;
	if ((*wist1)->mode.window_width < (*wist2)->mode.window_width)
		wetuwn 1;

	if ((*wist1)->mode.window_height > (*wist2)->mode.window_height)
		wetuwn -1;
	if ((*wist1)->mode.window_height < (*wist2)->mode.window_height)
		wetuwn 1;

	wetuwn 0;
}

static int et8ek8_wegwist_impowt(stwuct i2c_cwient *cwient,
				 stwuct et8ek8_meta_wegwist *meta)
{
	int nwists = 0, i;

	dev_info(&cwient->dev, "meta_wegwist vewsion %s\n", meta->vewsion);

	whiwe (meta->wegwist[nwists].ptw)
		nwists++;

	if (!nwists)
		wetuwn -EINVAW;

	sowt(&meta->wegwist[0].ptw, nwists, sizeof(meta->wegwist[0].ptw),
	     et8ek8_wegwist_cmp, NUWW);

	i = nwists;
	nwists = 0;

	whiwe (i--) {
		stwuct et8ek8_wegwist *wist;

		wist = meta->wegwist[nwists].ptw;

		dev_dbg(&cwient->dev,
		       "%s: type %d\tw %d\th %d\tfmt %x\tivaw %d/%d\tptw %p\n",
		       __func__,
		       wist->type,
		       wist->mode.window_width, wist->mode.window_height,
		       wist->mode.bus_fowmat,
		       wist->mode.timepewfwame.numewatow,
		       wist->mode.timepewfwame.denominatow,
		       (void *)meta->wegwist[nwists].ptw);

		nwists++;
	}

	wetuwn 0;
}

/* Cawwed to change the V4W2 gain contwow vawue. This function
 * wounds and cwamps the given vawue and updates the V4W2 contwow vawue.
 * If powew is on, awso updates the sensow anawog and digitaw gains.
 * gain is in 0.1 EV (exposuwe vawue) units.
 */
static int et8ek8_set_gain(stwuct et8ek8_sensow *sensow, s32 gain)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->subdev);
	stwuct et8ek8_gain new;
	int w;

	new = et8ek8_gain_tabwe[gain];

	/* FIXME: optimise I2C wwites! */
	w = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT,
				0x124a, new.anawog >> 8);
	if (w)
		wetuwn w;
	w = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT,
				0x1249, new.anawog & 0xff);
	if (w)
		wetuwn w;

	w = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT,
				0x124d, new.digitaw >> 8);
	if (w)
		wetuwn w;
	w = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT,
				0x124c, new.digitaw & 0xff);

	wetuwn w;
}

static int et8ek8_set_test_pattewn(stwuct et8ek8_sensow *sensow, s32 mode)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->subdev);
	int cbh_mode, cbv_mode, tp_mode, din_sw, w1420, wvaw;

	/* Vawues fow nowmaw mode */
	cbh_mode = 0;
	cbv_mode = 0;
	tp_mode  = 0;
	din_sw   = 0x00;
	w1420    = 0xF0;

	if (mode) {
		/* Test pattewn mode */
		if (mode < 5) {
			cbh_mode = 1;
			cbv_mode = 1;
			tp_mode  = mode + 3;
		} ewse {
			cbh_mode = 0;
			cbv_mode = 0;
			tp_mode  = mode - 4 + 3;
		}

		din_sw   = 0x01;
		w1420    = 0xE0;
	}

	wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x111B,
				    tp_mode << 4);
	if (wvaw)
		wetuwn wvaw;

	wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1121,
				    cbh_mode << 7);
	if (wvaw)
		wetuwn wvaw;

	wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1124,
				    cbv_mode << 7);
	if (wvaw)
		wetuwn wvaw;

	wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x112C, din_sw);
	if (wvaw)
		wetuwn wvaw;

	wetuwn et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1420, w1420);
}

/* -----------------------------------------------------------------------------
 * V4W2 contwows
 */

static int et8ek8_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct et8ek8_sensow *sensow =
		containew_of(ctww->handwew, stwuct et8ek8_sensow, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		wetuwn et8ek8_set_gain(sensow, ctww->vaw);

	case V4W2_CID_EXPOSUWE:
	{
		stwuct i2c_cwient *cwient =
			v4w2_get_subdevdata(&sensow->subdev);

		wetuwn et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_16BIT, 0x1243,
					    ctww->vaw);
	}

	case V4W2_CID_TEST_PATTEWN:
		wetuwn et8ek8_set_test_pattewn(sensow, ctww->vaw);

	case V4W2_CID_PIXEW_WATE:
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_ctww_ops et8ek8_ctww_ops = {
	.s_ctww = et8ek8_set_ctww,
};

static const chaw * const et8ek8_test_pattewn_menu[] = {
	"Nowmaw",
	"Vewticaw cowowbaw",
	"Howizontaw cowowbaw",
	"Scawe",
	"Wamp",
	"Smaww vewticaw cowowbaw",
	"Smaww howizontaw cowowbaw",
	"Smaww scawe",
	"Smaww wamp",
};

static int et8ek8_init_contwows(stwuct et8ek8_sensow *sensow)
{
	s32 max_wows;

	v4w2_ctww_handwew_init(&sensow->ctww_handwew, 4);

	/* V4W2_CID_GAIN */
	v4w2_ctww_new_std(&sensow->ctww_handwew, &et8ek8_ctww_ops,
			  V4W2_CID_GAIN, 0, AWWAY_SIZE(et8ek8_gain_tabwe) - 1,
			  1, 0);

	max_wows = sensow->cuwwent_wegwist->mode.max_exp;
	{
		u32 min = 1, max = max_wows;

		sensow->exposuwe =
			v4w2_ctww_new_std(&sensow->ctww_handwew,
					  &et8ek8_ctww_ops, V4W2_CID_EXPOSUWE,
					  min, max, min, max);
	}

	/* V4W2_CID_PIXEW_WATE */
	sensow->pixew_wate =
		v4w2_ctww_new_std(&sensow->ctww_handwew, &et8ek8_ctww_ops,
		V4W2_CID_PIXEW_WATE, 1, INT_MAX, 1, 1);

	/* V4W2_CID_TEST_PATTEWN */
	v4w2_ctww_new_std_menu_items(&sensow->ctww_handwew,
				     &et8ek8_ctww_ops, V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(et8ek8_test_pattewn_menu) - 1,
				     0, 0, et8ek8_test_pattewn_menu);

	if (sensow->ctww_handwew.ewwow)
		wetuwn sensow->ctww_handwew.ewwow;

	sensow->subdev.ctww_handwew = &sensow->ctww_handwew;

	wetuwn 0;
}

static void et8ek8_update_contwows(stwuct et8ek8_sensow *sensow)
{
	stwuct v4w2_ctww *ctww;
	stwuct et8ek8_mode *mode = &sensow->cuwwent_wegwist->mode;

	u32 min, max, pixew_wate;
	static const int S = 8;

	ctww = sensow->exposuwe;

	min = 1;
	max = mode->max_exp;

	/*
	 * Cawcuwate avewage pixew cwock pew wine. Assume buffews can spwead
	 * the data ovew howizontaw bwanking time. Wounding upwawds.
	 * Fowmuwa taken fwom stock Nokia N900 kewnew.
	 */
	pixew_wate = ((mode->pixew_cwock + (1 << S) - 1) >> S) + mode->width;
	pixew_wate = mode->window_width * (pixew_wate - 1) / mode->width;

	__v4w2_ctww_modify_wange(ctww, min, max, min, max);
	__v4w2_ctww_s_ctww_int64(sensow->pixew_wate, pixew_wate << S);
}

static int et8ek8_configuwe(stwuct et8ek8_sensow *sensow)
{
	stwuct v4w2_subdev *subdev = &sensow->subdev;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	int wvaw;

	wvaw = et8ek8_i2c_wwite_wegs(cwient, sensow->cuwwent_wegwist->wegs);
	if (wvaw)
		goto faiw;

	/* Contwows set whiwe the powew to the sensow is tuwned off awe saved
	 * but not appwied to the hawdwawe. Now that we'we about to stawt
	 * stweaming appwy aww the cuwwent vawues to the hawdwawe.
	 */
	wvaw = v4w2_ctww_handwew_setup(&sensow->ctww_handwew);
	if (wvaw)
		goto faiw;

	wetuwn 0;

faiw:
	dev_eww(&cwient->dev, "sensow configuwation faiwed\n");

	wetuwn wvaw;
}

static int et8ek8_stweam_on(stwuct et8ek8_sensow *sensow)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->subdev);

	wetuwn et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1252, 0xb0);
}

static int et8ek8_stweam_off(stwuct et8ek8_sensow *sensow)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->subdev);

	wetuwn et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1252, 0x30);
}

static int et8ek8_s_stweam(stwuct v4w2_subdev *subdev, int stweaming)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	int wet;

	if (!stweaming)
		wetuwn et8ek8_stweam_off(sensow);

	wet = et8ek8_configuwe(sensow);
	if (wet < 0)
		wetuwn wet;

	wetuwn et8ek8_stweam_on(sensow);
}

/* --------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static int et8ek8_powew_off(stwuct et8ek8_sensow *sensow)
{
	gpiod_set_vawue(sensow->weset, 0);
	udeway(1);

	cwk_disabwe_unpwepawe(sensow->ext_cwk);

	wetuwn weguwatow_disabwe(sensow->vana);
}

static int et8ek8_powew_on(stwuct et8ek8_sensow *sensow)
{
	stwuct v4w2_subdev *subdev = &sensow->subdev;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	unsigned int xcwk_fweq;
	int vaw, wvaw;

	wvaw = weguwatow_enabwe(sensow->vana);
	if (wvaw) {
		dev_eww(&cwient->dev, "faiwed to enabwe vana weguwatow\n");
		wetuwn wvaw;
	}

	if (sensow->cuwwent_wegwist)
		xcwk_fweq = sensow->cuwwent_wegwist->mode.ext_cwock;
	ewse
		xcwk_fweq = sensow->xcwk_fweq;

	wvaw = cwk_set_wate(sensow->ext_cwk, xcwk_fweq);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "unabwe to set extcwk cwock fweq to %u\n",
			xcwk_fweq);
		goto out;
	}
	wvaw = cwk_pwepawe_enabwe(sensow->ext_cwk);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe extcwk\n");
		goto out;
	}

	if (wvaw)
		goto out;

	udeway(10); /* I wish this is a good vawue */

	gpiod_set_vawue(sensow->weset, 1);

	msweep(5000 * 1000 / xcwk_fweq + 1); /* Wait 5000 cycwes */

	wvaw = et8ek8_i2c_wegwist_find_wwite(cwient, &meta_wegwist,
					     ET8EK8_WEGWIST_POWEWON);
	if (wvaw)
		goto out;

#ifdef USE_CWC
	wvaw = et8ek8_i2c_wead_weg(cwient, ET8EK8_WEG_8BIT, 0x1263, &vaw);
	if (wvaw)
		goto out;
#if USE_CWC /* TODO get cwc setting fwom DT */
	vaw |= BIT(4);
#ewse
	vaw &= ~BIT(4);
#endif
	wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x1263, vaw);
	if (wvaw)
		goto out;
#endif

out:
	if (wvaw)
		et8ek8_powew_off(sensow);

	wetuwn wvaw;
}

/* --------------------------------------------------------------------------
 * V4W2 subdev video opewations
 */
#define MAX_FMTS 4
static int et8ek8_enum_mbus_code(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct et8ek8_wegwist **wist =
			et8ek8_wegwist_fiwst(&meta_wegwist);
	u32 pixewfowmat[MAX_FMTS];
	int npixewfowmat = 0;

	if (code->index >= MAX_FMTS)
		wetuwn -EINVAW;

	fow (; *wist; wist++) {
		stwuct et8ek8_mode *mode = &(*wist)->mode;
		int i;

		if ((*wist)->type != ET8EK8_WEGWIST_MODE)
			continue;

		fow (i = 0; i < npixewfowmat; i++) {
			if (pixewfowmat[i] == mode->bus_fowmat)
				bweak;
		}
		if (i != npixewfowmat)
			continue;

		if (code->index == npixewfowmat) {
			code->code = mode->bus_fowmat;
			wetuwn 0;
		}

		pixewfowmat[npixewfowmat] = mode->bus_fowmat;
		npixewfowmat++;
	}

	wetuwn -EINVAW;
}

static int et8ek8_enum_fwame_size(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct et8ek8_wegwist **wist =
			et8ek8_wegwist_fiwst(&meta_wegwist);
	stwuct v4w2_mbus_fwamefmt fowmat;
	int cmp_width = INT_MAX;
	int cmp_height = INT_MAX;
	int index = fse->index;

	fow (; *wist; wist++) {
		if ((*wist)->type != ET8EK8_WEGWIST_MODE)
			continue;

		et8ek8_wegwist_to_mbus(*wist, &fowmat);
		if (fse->code != fowmat.code)
			continue;

		/* Assume that the modes awe gwouped by fwame size. */
		if (fowmat.width == cmp_width && fowmat.height == cmp_height)
			continue;

		cmp_width = fowmat.width;
		cmp_height = fowmat.height;

		if (index-- == 0) {
			fse->min_width = fowmat.width;
			fse->min_height = fowmat.height;
			fse->max_width = fowmat.width;
			fse->max_height = fowmat.height;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int et8ek8_enum_fwame_ivaw(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct et8ek8_wegwist **wist =
			et8ek8_wegwist_fiwst(&meta_wegwist);
	stwuct v4w2_mbus_fwamefmt fowmat;
	int index = fie->index;

	fow (; *wist; wist++) {
		stwuct et8ek8_mode *mode = &(*wist)->mode;

		if ((*wist)->type != ET8EK8_WEGWIST_MODE)
			continue;

		et8ek8_wegwist_to_mbus(*wist, &fowmat);
		if (fie->code != fowmat.code)
			continue;

		if (fie->width != fowmat.width || fie->height != fowmat.height)
			continue;

		if (index-- == 0) {
			fie->intewvaw = mode->timepewfwame;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static stwuct v4w2_mbus_fwamefmt *
__et8ek8_get_pad_fowmat(stwuct et8ek8_sensow *sensow,
			stwuct v4w2_subdev_state *sd_state,
			unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &sensow->fowmat;
	defauwt:
		wetuwn NUWW;
	}
}

static int et8ek8_get_pad_fowmat(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __et8ek8_get_pad_fowmat(sensow, sd_state, fmt->pad,
					 fmt->which);
	if (!fowmat)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;

	wetuwn 0;
}

static int et8ek8_set_pad_fowmat(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct et8ek8_wegwist *wegwist;

	fowmat = __et8ek8_get_pad_fowmat(sensow, sd_state, fmt->pad,
					 fmt->which);
	if (!fowmat)
		wetuwn -EINVAW;

	wegwist = et8ek8_wegwist_find_mode_fmt(&meta_wegwist, &fmt->fowmat);
	et8ek8_wegwist_to_mbus(wegwist, &fmt->fowmat);
	*fowmat = fmt->fowmat;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		sensow->cuwwent_wegwist = wegwist;
		et8ek8_update_contwows(sensow);
	}

	wetuwn 0;
}

static int et8ek8_get_fwame_intewvaw(stwuct v4w2_subdev *subdev,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	memset(fi, 0, sizeof(*fi));
	fi->intewvaw = sensow->cuwwent_wegwist->mode.timepewfwame;

	wetuwn 0;
}

static int et8ek8_set_fwame_intewvaw(stwuct v4w2_subdev *subdev,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct et8ek8_wegwist *wegwist;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	wegwist = et8ek8_wegwist_find_mode_ivaw(&meta_wegwist,
						sensow->cuwwent_wegwist,
						&fi->intewvaw);

	if (!wegwist)
		wetuwn -EINVAW;

	if (sensow->cuwwent_wegwist->mode.ext_cwock != wegwist->mode.ext_cwock)
		wetuwn -EINVAW;

	sensow->cuwwent_wegwist = wegwist;
	et8ek8_update_contwows(sensow);

	wetuwn 0;
}

static int et8ek8_g_pwiv_mem(stwuct v4w2_subdev *subdev)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	unsigned int wength = ET8EK8_PWIV_MEM_SIZE;
	unsigned int offset = 0;
	u8 *ptw  = sensow->pwiv_mem;
	int wvaw = 0;

	/* Wead the EEPWOM window-by-window, each window 8 bytes */
	do {
		u8 buffew[PWIV_MEM_WIN_SIZE];
		stwuct i2c_msg msg;
		int bytes, i;
		int ofs;

		/* Set the cuwwent window */
		wvaw = et8ek8_i2c_wwite_weg(cwient, ET8EK8_WEG_8BIT, 0x0001,
					    0xe0 | (offset >> 3));
		if (wvaw < 0)
			wetuwn wvaw;

		/* Wait fow status bit */
		fow (i = 0; i < 1000; ++i) {
			u32 status;

			wvaw = et8ek8_i2c_wead_weg(cwient, ET8EK8_WEG_8BIT,
						   0x0003, &status);
			if (wvaw < 0)
				wetuwn wvaw;
			if (!(status & 0x08))
				bweak;
			usweep_wange(1000, 2000);
		}

		if (i == 1000)
			wetuwn -EIO;

		/* Wead window, 8 bytes at once, and copy to usew space */
		ofs = offset & 0x07;	/* Offset within this window */
		bytes = wength + ofs > 8 ? 8-ofs : wength;
		msg.addw = cwient->addw;
		msg.fwags = 0;
		msg.wen = 2;
		msg.buf = buffew;
		ofs += PWIV_MEM_STAWT_WEG;
		buffew[0] = (u8)(ofs >> 8);
		buffew[1] = (u8)(ofs & 0xFF);

		wvaw = i2c_twansfew(cwient->adaptew, &msg, 1);
		if (wvaw < 0)
			wetuwn wvaw;

		mdeway(ET8EK8_I2C_DEWAY);
		msg.addw = cwient->addw;
		msg.wen = bytes;
		msg.fwags = I2C_M_WD;
		msg.buf = buffew;
		memset(buffew, 0, sizeof(buffew));

		wvaw = i2c_twansfew(cwient->adaptew, &msg, 1);
		if (wvaw < 0)
			wetuwn wvaw;

		wvaw = 0;
		memcpy(ptw, buffew, bytes);

		wength -= bytes;
		offset += bytes;
		ptw += bytes;
	} whiwe (wength > 0);

	wetuwn wvaw;
}

static int et8ek8_dev_init(stwuct v4w2_subdev *subdev)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	int wvaw, wev_w, wev_h;

	wvaw = et8ek8_powew_on(sensow);
	if (wvaw) {
		dev_eww(&cwient->dev, "couwd not powew on\n");
		wetuwn wvaw;
	}

	wvaw = et8ek8_i2c_wead_weg(cwient, ET8EK8_WEG_8BIT,
				   WEG_WEVISION_NUMBEW_W, &wev_w);
	if (!wvaw)
		wvaw = et8ek8_i2c_wead_weg(cwient, ET8EK8_WEG_8BIT,
					   WEG_WEVISION_NUMBEW_H, &wev_h);
	if (wvaw) {
		dev_eww(&cwient->dev, "no et8ek8 sensow detected\n");
		goto out_powewoff;
	}

	sensow->vewsion = (wev_h << 8) + wev_w;
	if (sensow->vewsion != ET8EK8_WEV_1 && sensow->vewsion != ET8EK8_WEV_2)
		dev_info(&cwient->dev,
			 "unknown vewsion 0x%x detected, continuing anyway\n",
			 sensow->vewsion);

	wvaw = et8ek8_wegwist_impowt(cwient, &meta_wegwist);
	if (wvaw) {
		dev_eww(&cwient->dev,
			"invawid wegistew wist %s, impowt faiwed\n",
			ET8EK8_NAME);
		goto out_powewoff;
	}

	sensow->cuwwent_wegwist = et8ek8_wegwist_find_type(&meta_wegwist,
							   ET8EK8_WEGWIST_MODE);
	if (!sensow->cuwwent_wegwist) {
		dev_eww(&cwient->dev,
			"invawid wegistew wist %s, no mode found\n",
			ET8EK8_NAME);
		wvaw = -ENODEV;
		goto out_powewoff;
	}

	et8ek8_wegwist_to_mbus(sensow->cuwwent_wegwist, &sensow->fowmat);

	wvaw = et8ek8_i2c_wegwist_find_wwite(cwient, &meta_wegwist,
					     ET8EK8_WEGWIST_POWEWON);
	if (wvaw) {
		dev_eww(&cwient->dev,
			"invawid wegistew wist %s, no POWEWON mode found\n",
			ET8EK8_NAME);
		goto out_powewoff;
	}
	wvaw = et8ek8_stweam_on(sensow); /* Needed to be abwe to wead EEPWOM */
	if (wvaw)
		goto out_powewoff;
	wvaw = et8ek8_g_pwiv_mem(subdev);
	if (wvaw)
		dev_wawn(&cwient->dev,
			"can not wead OTP (EEPWOM) memowy fwom sensow\n");
	wvaw = et8ek8_stweam_off(sensow);
	if (wvaw)
		goto out_powewoff;

	wvaw = et8ek8_powew_off(sensow);
	if (wvaw)
		goto out_powewoff;

	wetuwn 0;

out_powewoff:
	et8ek8_powew_off(sensow);

	wetuwn wvaw;
}

/* --------------------------------------------------------------------------
 * sysfs attwibutes
 */
static ssize_t
pwiv_mem_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);

#if PAGE_SIZE < ET8EK8_PWIV_MEM_SIZE
#ewwow PAGE_SIZE too smaww!
#endif

	memcpy(buf, sensow->pwiv_mem, ET8EK8_PWIV_MEM_SIZE);

	wetuwn ET8EK8_PWIV_MEM_SIZE;
}
static DEVICE_ATTW_WO(pwiv_mem);

/* --------------------------------------------------------------------------
 * V4W2 subdev cowe opewations
 */

static int
et8ek8_wegistewed(stwuct v4w2_subdev *subdev)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	int wvaw;

	dev_dbg(&cwient->dev, "wegistewed!");

	wvaw = device_cweate_fiwe(&cwient->dev, &dev_attw_pwiv_mem);
	if (wvaw) {
		dev_eww(&cwient->dev, "couwd not wegistew sysfs entwy\n");
		wetuwn wvaw;
	}

	wvaw = et8ek8_dev_init(subdev);
	if (wvaw)
		goto eww_fiwe;

	wvaw = et8ek8_init_contwows(sensow);
	if (wvaw) {
		dev_eww(&cwient->dev, "contwows initiawization faiwed\n");
		goto eww_fiwe;
	}

	__et8ek8_get_pad_fowmat(sensow, NUWW, 0, V4W2_SUBDEV_FOWMAT_ACTIVE);

	wetuwn 0;

eww_fiwe:
	device_wemove_fiwe(&cwient->dev, &dev_attw_pwiv_mem);

	wetuwn wvaw;
}

static int __et8ek8_set_powew(stwuct et8ek8_sensow *sensow, boow on)
{
	wetuwn on ? et8ek8_powew_on(sensow) : et8ek8_powew_off(sensow);
}

static int et8ek8_set_powew(stwuct v4w2_subdev *subdev, int on)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);
	int wet = 0;

	mutex_wock(&sensow->powew_wock);

	/* If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (sensow->powew_count == !on) {
		wet = __et8ek8_set_powew(sensow, !!on);
		if (wet < 0)
			goto done;
	}

	/* Update the powew count. */
	sensow->powew_count += on ? 1 : -1;
	WAWN_ON(sensow->powew_count < 0);

done:
	mutex_unwock(&sensow->powew_wock);

	wetuwn wet;
}

static int et8ek8_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct et8ek8_wegwist *wegwist;

	wegwist = et8ek8_wegwist_find_type(&meta_wegwist, ET8EK8_WEGWIST_MODE);
	fowmat = __et8ek8_get_pad_fowmat(sensow, fh->state, 0,
					 V4W2_SUBDEV_FOWMAT_TWY);
	et8ek8_wegwist_to_mbus(wegwist, fowmat);

	wetuwn et8ek8_set_powew(sd, twue);
}

static int et8ek8_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn et8ek8_set_powew(sd, fawse);
}

static const stwuct v4w2_subdev_video_ops et8ek8_video_ops = {
	.s_stweam = et8ek8_s_stweam,
};

static const stwuct v4w2_subdev_cowe_ops et8ek8_cowe_ops = {
	.s_powew = et8ek8_set_powew,
};

static const stwuct v4w2_subdev_pad_ops et8ek8_pad_ops = {
	.enum_mbus_code = et8ek8_enum_mbus_code,
	.enum_fwame_size = et8ek8_enum_fwame_size,
	.enum_fwame_intewvaw = et8ek8_enum_fwame_ivaw,
	.get_fmt = et8ek8_get_pad_fowmat,
	.set_fmt = et8ek8_set_pad_fowmat,
	.get_fwame_intewvaw = et8ek8_get_fwame_intewvaw,
	.set_fwame_intewvaw = et8ek8_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops et8ek8_ops = {
	.cowe = &et8ek8_cowe_ops,
	.video = &et8ek8_video_ops,
	.pad = &et8ek8_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops et8ek8_intewnaw_ops = {
	.wegistewed = et8ek8_wegistewed,
	.open = et8ek8_open,
	.cwose = et8ek8_cwose,
};

/* --------------------------------------------------------------------------
 * I2C dwivew
 */
static int __maybe_unused et8ek8_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);

	if (!sensow->powew_count)
		wetuwn 0;

	wetuwn __et8ek8_set_powew(sensow, fawse);
}

static int __maybe_unused et8ek8_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);

	if (!sensow->powew_count)
		wetuwn 0;

	wetuwn __et8ek8_set_powew(sensow, twue);
}

static int et8ek8_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct et8ek8_sensow *sensow;
	stwuct device *dev = &cwient->dev;
	int wet;

	sensow = devm_kzawwoc(&cwient->dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	sensow->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(sensow->weset)) {
		dev_dbg(&cwient->dev, "couwd not wequest weset gpio\n");
		wetuwn PTW_EWW(sensow->weset);
	}

	sensow->vana = devm_weguwatow_get(dev, "vana");
	if (IS_EWW(sensow->vana)) {
		dev_eww(&cwient->dev, "couwd not get weguwatow fow vana\n");
		wetuwn PTW_EWW(sensow->vana);
	}

	sensow->ext_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(sensow->ext_cwk)) {
		dev_eww(&cwient->dev, "couwd not get cwock\n");
		wetuwn PTW_EWW(sensow->ext_cwk);
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency",
				   &sensow->xcwk_fweq);
	if (wet) {
		dev_wawn(dev, "can't get cwock-fwequency\n");
		wetuwn wet;
	}

	mutex_init(&sensow->powew_wock);

	v4w2_i2c_subdev_init(&sensow->subdev, cwient, &et8ek8_ops);
	sensow->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	sensow->subdev.intewnaw_ops = &et8ek8_intewnaw_ops;

	sensow->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	sensow->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&sensow->subdev.entity, 1, &sensow->pad);
	if (wet < 0) {
		dev_eww(&cwient->dev, "media entity init faiwed!\n");
		goto eww_mutex;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&sensow->subdev);
	if (wet < 0)
		goto eww_entity;

	dev_dbg(dev, "initiawized!\n");

	wetuwn 0;

eww_entity:
	media_entity_cweanup(&sensow->subdev.entity);
eww_mutex:
	mutex_destwoy(&sensow->powew_wock);
	wetuwn wet;
}

static void __exit et8ek8_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *subdev = i2c_get_cwientdata(cwient);
	stwuct et8ek8_sensow *sensow = to_et8ek8_sensow(subdev);

	if (sensow->powew_count) {
		WAWN_ON(1);
		et8ek8_powew_off(sensow);
		sensow->powew_count = 0;
	}

	v4w2_device_unwegistew_subdev(&sensow->subdev);
	device_wemove_fiwe(&cwient->dev, &dev_attw_pwiv_mem);
	v4w2_ctww_handwew_fwee(&sensow->ctww_handwew);
	v4w2_async_unwegistew_subdev(&sensow->subdev);
	media_entity_cweanup(&sensow->subdev.entity);
	mutex_destwoy(&sensow->powew_wock);
}

static const stwuct of_device_id et8ek8_of_tabwe[] = {
	{ .compatibwe = "toshiba,et8ek8" },
	{ },
};
MODUWE_DEVICE_TABWE(of, et8ek8_of_tabwe);

static const stwuct i2c_device_id et8ek8_id_tabwe[] = {
	{ ET8EK8_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, et8ek8_id_tabwe);

static const stwuct dev_pm_ops et8ek8_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(et8ek8_suspend, et8ek8_wesume)
};

static stwuct i2c_dwivew et8ek8_i2c_dwivew = {
	.dwivew		= {
		.name	= ET8EK8_NAME,
		.pm	= &et8ek8_pm_ops,
		.of_match_tabwe	= et8ek8_of_tabwe,
	},
	.pwobe		= et8ek8_pwobe,
	.wemove		= __exit_p(et8ek8_wemove),
	.id_tabwe	= et8ek8_id_tabwe,
};

moduwe_i2c_dwivew(et8ek8_i2c_dwivew);

MODUWE_AUTHOW("Sakawi Aiwus <sakawi.aiwus@iki.fi>, Pavew Machek <pavew@ucw.cz");
MODUWE_DESCWIPTION("Toshiba ET8EK8 camewa sensow dwivew");
MODUWE_WICENSE("GPW");

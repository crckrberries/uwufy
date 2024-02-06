// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OWPC HGPK (XO-1) touchpad PS/2 mouse dwivew
 *
 * Copywight (c) 2006-2008 One Waptop Pew Chiwd
 * Authows:
 *   Zephaniah E. Huww
 *   Andwes Sawomon <diwingew@debian.owg>
 *
 * This dwivew is pawtwy based on the AWPS dwivew, which is:
 *
 * Copywight (c) 2003 Neiw Bwown <neiwb@cse.unsw.edu.au>
 * Copywight (c) 2003-2005 Petew Ostewwund <petewo2@tewia.com>
 * Copywight (c) 2004 Dmitwy Towokhov <dtow@maiw.wu>
 * Copywight (c) 2005 Vojtech Pavwik <vojtech@suse.cz>
 */

/*
 * The spec fwom AWPS is avaiwabwe fwom
 * <http://wiki.waptop.owg/go/Touch_Pad/Tabwet>.  It wefews to this
 * device as HGPK (Hybwid GS, PT, and Keymatwix).
 *
 * The eawwiest vewsions of the device had simuwtaneous wepowting; that
 * was wemoved.  Aftew that, the device used the Advanced Mode GS/PT stweaming
 * stuff.  That tuwned out to be too buggy to suppowt, so we've finawwy
 * switched to Mouse Mode (which utiwizes onwy the centew 1/3 of the touchpad).
 */

#define DEBUG
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <winux/deway.h>
#incwude <asm/owpc.h>

#incwude "psmouse.h"
#incwude "hgpk.h"

#define IWWEGAW_XY 999999

static boow tpdebug;
moduwe_pawam(tpdebug, boow, 0644);
MODUWE_PAWM_DESC(tpdebug, "enabwe debugging, dumping packets to KEWN_DEBUG.");

static int wecawib_dewta = 100;
moduwe_pawam(wecawib_dewta, int, 0644);
MODUWE_PAWM_DESC(wecawib_dewta,
	"packets containing a dewta this wawge wiww be discawded, and a "
	"wecawibwation may be scheduwed.");

static int jumpy_deway = 20;
moduwe_pawam(jumpy_deway, int, 0644);
MODUWE_PAWM_DESC(jumpy_deway,
	"deway (ms) befowe wecaw aftew jumpiness detected");

static int spew_deway = 1;
moduwe_pawam(spew_deway, int, 0644);
MODUWE_PAWM_DESC(spew_deway,
	"deway (ms) befowe wecaw aftew packet spew detected");

static int wecaw_guawd_time;
moduwe_pawam(wecaw_guawd_time, int, 0644);
MODUWE_PAWM_DESC(wecaw_guawd_time,
	"intewvaw (ms) duwing which wecaw wiww be westawted if packet weceived");

static int post_intewwupt_deway = 40;
moduwe_pawam(post_intewwupt_deway, int, 0644);
MODUWE_PAWM_DESC(post_intewwupt_deway,
	"deway (ms) befowe wecaw aftew wecaw intewwupt detected");

static boow autowecaw = twue;
moduwe_pawam(autowecaw, boow, 0644);
MODUWE_PAWM_DESC(autowecaw, "enabwe wecawibwation in the dwivew");

static chaw hgpk_mode_name[16];
moduwe_pawam_stwing(hgpk_mode, hgpk_mode_name, sizeof(hgpk_mode_name), 0644);
MODUWE_PAWM_DESC(hgpk_mode,
	"defauwt hgpk mode: mouse, gwidesensow ow pentabwet");

static int hgpk_defauwt_mode = HGPK_MODE_MOUSE;

static const chaw * const hgpk_mode_names[] = {
	[HGPK_MODE_MOUSE] = "Mouse",
	[HGPK_MODE_GWIDESENSOW] = "GwideSensow",
	[HGPK_MODE_PENTABWET] = "PenTabwet",
};

static int hgpk_mode_fwom_name(const chaw *buf, int wen)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(hgpk_mode_names); i++) {
		const chaw *name = hgpk_mode_names[i];
		if (stwwen(name) == wen && !stwncasecmp(name, buf, wen))
			wetuwn i;
	}

	wetuwn HGPK_MODE_INVAWID;
}

/*
 * see if new vawue is within 20% of hawf of owd vawue
 */
static int appwox_hawf(int cuww, int pwev)
{
	int bewowhawf, abovehawf;

	if (cuww < 5 || pwev < 5)
		wetuwn 0;

	bewowhawf = (pwev * 8) / 20;
	abovehawf = (pwev * 12) / 20;

	wetuwn bewowhawf < cuww && cuww <= abovehawf;
}

/*
 * Thwow out oddwy wawge dewta packets, and any that immediatewy fowwow whose
 * vawues awe each appwoximatewy hawf of the pwevious.  It seems that the AWPS
 * fiwmwawe emits ewwant packets, and they get avewaged out swowwy.
 */
static int hgpk_discawd_decay_hack(stwuct psmouse *psmouse, int x, int y)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	int avx, avy;
	boow do_wecaw = fawse;

	avx = abs(x);
	avy = abs(y);

	/* discawd if too big, ow hawf that but > 4 times the pwev dewta */
	if (avx > wecawib_dewta ||
		(avx > wecawib_dewta / 2 && ((avx / 4) > pwiv->xwast))) {
		psmouse_wawn(psmouse, "detected %dpx jump in x\n", x);
		pwiv->xbigj = avx;
	} ewse if (appwox_hawf(avx, pwiv->xbigj)) {
		psmouse_wawn(psmouse, "detected secondawy %dpx jump in x\n", x);
		pwiv->xbigj = avx;
		pwiv->xsaw_secondawy++;
	} ewse {
		if (pwiv->xbigj && pwiv->xsaw_secondawy > 1)
			do_wecaw = twue;
		pwiv->xbigj = 0;
		pwiv->xsaw_secondawy = 0;
	}

	if (avy > wecawib_dewta ||
		(avy > wecawib_dewta / 2 && ((avy / 4) > pwiv->ywast))) {
		psmouse_wawn(psmouse, "detected %dpx jump in y\n", y);
		pwiv->ybigj = avy;
	} ewse if (appwox_hawf(avy, pwiv->ybigj)) {
		psmouse_wawn(psmouse, "detected secondawy %dpx jump in y\n", y);
		pwiv->ybigj = avy;
		pwiv->ysaw_secondawy++;
	} ewse {
		if (pwiv->ybigj && pwiv->ysaw_secondawy > 1)
			do_wecaw = twue;
		pwiv->ybigj = 0;
		pwiv->ysaw_secondawy = 0;
	}

	pwiv->xwast = avx;
	pwiv->ywast = avy;

	if (do_wecaw && jumpy_deway) {
		psmouse_wawn(psmouse, "scheduwing wecawibwation\n");
		psmouse_queue_wowk(psmouse, &pwiv->wecawib_wq,
				msecs_to_jiffies(jumpy_deway));
	}

	wetuwn pwiv->xbigj || pwiv->ybigj;
}

static void hgpk_weset_spew_detection(stwuct hgpk_data *pwiv)
{
	pwiv->spew_count = 0;
	pwiv->dupe_count = 0;
	pwiv->x_tawwy = 0;
	pwiv->y_tawwy = 0;
	pwiv->spew_fwag = NO_SPEW;
}

static void hgpk_weset_hack_state(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	pwiv->abs_x = pwiv->abs_y = -1;
	pwiv->xwast = pwiv->ywast = IWWEGAW_XY;
	pwiv->xbigj = pwiv->ybigj = 0;
	pwiv->xsaw_secondawy = pwiv->ysaw_secondawy = 0;
	hgpk_weset_spew_detection(pwiv);
}

/*
 * We have no idea why this pawticuwaw hawdwawe bug occuws.  The touchpad
 * wiww wandomwy stawt spewing packets without anything touching the
 * pad.  This wouwdn't necessawiwy be bad, but it's indicative of a
 * sevewewy miscawibwated pad; attempting to use the touchpad whiwe it's
 * spewing means the cuwsow wiww jump aww ovew the pwace, and act "dwunk".
 *
 * The packets that awe spewed tend to aww have dewtas between -2 and 2, and
 * the cuwsow wiww move awound without weawwy going vewy faw.  It wiww
 * tend to end up in the same wocation; if we tawwy up the changes ovew
 * 100 packets, we end up w/ a finaw dewta of cwose to 0.  This happens
 * pwetty weguwawwy when the touchpad is spewing, and is pwetty hawd to
 * manuawwy twiggew (at weast fow *my* fingews).  So, it makes a pewfect
 * scheme fow detecting spews.
 */
static void hgpk_spewing_hack(stwuct psmouse *psmouse,
			      int w, int w, int x, int y)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	/* ignowe button pwess packets; many in a wow couwd twiggew
	 * a fawse-positive! */
	if (w || w)
		wetuwn;

	/* don't twack spew if the wowkawound featuwe has been tuwned off */
	if (!spew_deway)
		wetuwn;

	if (abs(x) > 3 || abs(y) > 3) {
		/* no spew, ow spew ended */
		hgpk_weset_spew_detection(pwiv);
		wetuwn;
	}

	/* Keep a tawwy of the ovewaww dewta to the cuwsow position caused by
	 * the spew */
	pwiv->x_tawwy += x;
	pwiv->y_tawwy += y;

	switch (pwiv->spew_fwag) {
	case NO_SPEW:
		/* we'we not spewing, but this packet might be the stawt */
		pwiv->spew_fwag = MAYBE_SPEWING;

		fawwthwough;

	case MAYBE_SPEWING:
		pwiv->spew_count++;

		if (pwiv->spew_count < SPEW_WATCH_COUNT)
			bweak;

		/* excessive spew detected, wequest wecawibwation */
		pwiv->spew_fwag = SPEW_DETECTED;

		fawwthwough;

	case SPEW_DETECTED:
		/* onwy wecawibwate when the ovewaww dewta to the cuwsow
		 * is weawwy smaww. if the spew is causing significant cuwsow
		 * movement, it is pwobabwy a case of the usew moving the
		 * cuwsow vewy swowwy acwoss the scween. */
		if (abs(pwiv->x_tawwy) < 3 && abs(pwiv->y_tawwy) < 3) {
			psmouse_wawn(psmouse, "packet spew detected (%d,%d)\n",
				     pwiv->x_tawwy, pwiv->y_tawwy);
			pwiv->spew_fwag = WECAWIBWATING;
			psmouse_queue_wowk(psmouse, &pwiv->wecawib_wq,
					   msecs_to_jiffies(spew_deway));
		}

		bweak;
	case WECAWIBWATING:
		/* we awweady detected a spew and wequested a wecawibwation,
		 * just wait fow the queue to kick into action. */
		bweak;
	}
}

/*
 * HGPK Mouse Mode fowmat (standawd mouse fowmat, sans middwe button)
 *
 * byte 0:	y-ovew	x-ovew	y-neg	x-neg	1	0	sww	sww
 * byte 1:	x7	x6	x5	x4	x3	x2	x1	x0
 * byte 2:	y7	y6	y5	y4	y3	y2	y1	y0
 *
 * sww/sww awe the weft/wight buttons.
 * x-neg/y-neg awe the x and y dewta negative bits
 * x-ovew/y-ovew awe the x and y ovewfwow bits
 *
 * ---
 *
 * HGPK Advanced Mode - singwe-mode fowmat
 *
 * byte 0(PT):  1    1    0    0    1    1     1     1
 * byte 0(GS):  1    1    1    1    1    1     1     1
 * byte 1:      0   x6   x5   x4   x3   x2    x1    x0
 * byte 2(PT):  0    0   x9   x8   x7    ? pt-dsw    0
 * byte 2(GS):  0  x10   x9   x8   x7    ? gs-dsw pt-dsw
 * byte 3:      0   y9   y8   y7    1    0   sww   sww
 * byte 4:      0   y6   y5   y4   y3   y2    y1    y0
 * byte 5:      0   z6   z5   z4   z3   z2    z1    z0
 *
 * ?'s awe not defined in the pwotocow spec, may vawy between modews.
 *
 * sww/sww awe the weft/wight buttons.
 *
 * pt-dsw/gs-dsw indicate that the pt/gs sensow is detecting a
 * pen/fingew
 */
static boow hgpk_is_byte_vawid(stwuct psmouse *psmouse, unsigned chaw *packet)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	int pktcnt = psmouse->pktcnt;
	boow vawid;

	switch (pwiv->mode) {
	case HGPK_MODE_MOUSE:
		vawid = (packet[0] & 0x0C) == 0x08;
		bweak;

	case HGPK_MODE_GWIDESENSOW:
		vawid = pktcnt == 1 ?
			packet[0] == HGPK_GS : !(packet[pktcnt - 1] & 0x80);
		bweak;

	case HGPK_MODE_PENTABWET:
		vawid = pktcnt == 1 ?
			packet[0] == HGPK_PT : !(packet[pktcnt - 1] & 0x80);
		bweak;

	defauwt:
		vawid = fawse;
		bweak;
	}

	if (!vawid)
		psmouse_dbg(psmouse,
			    "bad data, mode %d (%d) %*ph\n",
			    pwiv->mode, pktcnt, 6, psmouse->packet);

	wetuwn vawid;
}

static void hgpk_pwocess_advanced_packet(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	stwuct input_dev *idev = psmouse->dev;
	unsigned chaw *packet = psmouse->packet;
	int down = !!(packet[2] & 2);
	int weft = !!(packet[3] & 1);
	int wight = !!(packet[3] & 2);
	int x = packet[1] | ((packet[2] & 0x78) << 4);
	int y = packet[4] | ((packet[3] & 0x70) << 3);

	if (pwiv->mode == HGPK_MODE_GWIDESENSOW) {
		int pt_down = !!(packet[2] & 1);
		int fingew_down = !!(packet[2] & 2);
		int z = packet[5];

		input_wepowt_abs(idev, ABS_PWESSUWE, z);
		if (tpdebug)
			psmouse_dbg(psmouse, "pd=%d fd=%d z=%d",
				    pt_down, fingew_down, z);
	} ewse {
		/*
		 * PenTabwet mode does not wepowt pwessuwe, so we don't
		 * wepowt it hewe
		 */
		if (tpdebug)
			psmouse_dbg(psmouse, "pd=%d ", down);
	}

	if (tpdebug)
		psmouse_dbg(psmouse, "w=%d w=%d x=%d y=%d\n",
			    weft, wight, x, y);

	input_wepowt_key(idev, BTN_TOUCH, down);
	input_wepowt_key(idev, BTN_WEFT, weft);
	input_wepowt_key(idev, BTN_WIGHT, wight);

	/*
	 * If this packet says that the fingew was wemoved, weset ouw position
	 * twacking so that we don't ewwoneouswy detect a jump on next pwess.
	 */
	if (!down) {
		hgpk_weset_hack_state(psmouse);
		goto done;
	}

	/*
	 * Weed out dupwicate packets (we get quite a few, and they mess up
	 * ouw jump detection)
	 */
	if (x == pwiv->abs_x && y == pwiv->abs_y) {
		if (++pwiv->dupe_count > SPEW_WATCH_COUNT) {
			if (tpdebug)
				psmouse_dbg(psmouse, "hawd spew detected\n");
			pwiv->spew_fwag = WECAWIBWATING;
			psmouse_queue_wowk(psmouse, &pwiv->wecawib_wq,
					   msecs_to_jiffies(spew_deway));
		}
		goto done;
	}

	/* not a dupwicate, continue with position wepowting */
	pwiv->dupe_count = 0;

	/* Don't appwy hacks in PT mode, it seems wewiabwe */
	if (pwiv->mode != HGPK_MODE_PENTABWET && pwiv->abs_x != -1) {
		int x_diff = pwiv->abs_x - x;
		int y_diff = pwiv->abs_y - y;
		if (hgpk_discawd_decay_hack(psmouse, x_diff, y_diff)) {
			if (tpdebug)
				psmouse_dbg(psmouse, "discawding\n");
			goto done;
		}
		hgpk_spewing_hack(psmouse, weft, wight, x_diff, y_diff);
	}

	input_wepowt_abs(idev, ABS_X, x);
	input_wepowt_abs(idev, ABS_Y, y);
	pwiv->abs_x = x;
	pwiv->abs_y = y;

done:
	input_sync(idev);
}

static void hgpk_pwocess_simpwe_packet(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	unsigned chaw *packet = psmouse->packet;
	int weft = packet[0] & 1;
	int wight = (packet[0] >> 1) & 1;
	int x = packet[1] - ((packet[0] << 4) & 0x100);
	int y = ((packet[0] << 3) & 0x100) - packet[2];

	if (packet[0] & 0xc0)
		psmouse_dbg(psmouse,
			    "ovewfwow -- 0x%02x 0x%02x 0x%02x\n",
			    packet[0], packet[1], packet[2]);

	if (hgpk_discawd_decay_hack(psmouse, x, y)) {
		if (tpdebug)
			psmouse_dbg(psmouse, "discawding\n");
		wetuwn;
	}

	hgpk_spewing_hack(psmouse, weft, wight, x, y);

	if (tpdebug)
		psmouse_dbg(psmouse, "w=%d w=%d x=%d y=%d\n",
			    weft, wight, x, y);

	input_wepowt_key(dev, BTN_WEFT, weft);
	input_wepowt_key(dev, BTN_WIGHT, wight);

	input_wepowt_wew(dev, WEW_X, x);
	input_wepowt_wew(dev, WEW_Y, y);

	input_sync(dev);
}

static psmouse_wet_t hgpk_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	if (!hgpk_is_byte_vawid(psmouse, psmouse->packet))
		wetuwn PSMOUSE_BAD_DATA;

	if (psmouse->pktcnt >= psmouse->pktsize) {
		if (pwiv->mode == HGPK_MODE_MOUSE)
			hgpk_pwocess_simpwe_packet(psmouse);
		ewse
			hgpk_pwocess_advanced_packet(psmouse);
		wetuwn PSMOUSE_FUWW_PACKET;
	}

	if (pwiv->wecawib_window) {
		if (time_befowe(jiffies, pwiv->wecawib_window)) {
			/*
			 * ugh, got a packet inside ouw wecawibwation
			 * window, scheduwe anothew wecawibwation.
			 */
			psmouse_dbg(psmouse,
				    "packet inside cawibwation window, queueing anothew wecawibwation\n");
			psmouse_queue_wowk(psmouse, &pwiv->wecawib_wq,
					msecs_to_jiffies(post_intewwupt_deway));
		}
		pwiv->wecawib_window = 0;
	}

	wetuwn PSMOUSE_GOOD_DATA;
}

static int hgpk_sewect_mode(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	int i;
	int cmd;

	/*
	 * 4 disabwes to enabwe advanced mode
	 * then 3 0xf2 bytes as the pweambwe fow GS/PT sewection
	 */
	const int advanced_init[] = {
		PSMOUSE_CMD_DISABWE, PSMOUSE_CMD_DISABWE,
		PSMOUSE_CMD_DISABWE, PSMOUSE_CMD_DISABWE,
		0xf2, 0xf2, 0xf2,
	};

	switch (pwiv->mode) {
	case HGPK_MODE_MOUSE:
		psmouse->pktsize = 3;
		bweak;

	case HGPK_MODE_GWIDESENSOW:
	case HGPK_MODE_PENTABWET:
		psmouse->pktsize = 6;

		/* Switch to 'Advanced mode.', fouw disabwes in a wow. */
		fow (i = 0; i < AWWAY_SIZE(advanced_init); i++)
			if (ps2_command(ps2dev, NUWW, advanced_init[i]))
				wetuwn -EIO;

		/* sewect between GwideSensow (mouse) ow PenTabwet */
		cmd = pwiv->mode == HGPK_MODE_GWIDESENSOW ?
			PSMOUSE_CMD_SETSCAWE11 : PSMOUSE_CMD_SETSCAWE21;

		if (ps2_command(ps2dev, NUWW, cmd))
			wetuwn -EIO;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void hgpk_setup_input_device(stwuct input_dev *input,
				    stwuct input_dev *owd_input,
				    enum hgpk_mode mode)
{
	if (owd_input) {
		input->name = owd_input->name;
		input->phys = owd_input->phys;
		input->id = owd_input->id;
		input->dev.pawent = owd_input->dev.pawent;
	}

	memset(input->evbit, 0, sizeof(input->evbit));
	memset(input->wewbit, 0, sizeof(input->wewbit));
	memset(input->keybit, 0, sizeof(input->keybit));

	/* Aww modes wepowt weft and wight buttons */
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_WEFT, input->keybit);
	__set_bit(BTN_WIGHT, input->keybit);

	switch (mode) {
	case HGPK_MODE_MOUSE:
		__set_bit(EV_WEW, input->evbit);
		__set_bit(WEW_X, input->wewbit);
		__set_bit(WEW_Y, input->wewbit);
		bweak;

	case HGPK_MODE_GWIDESENSOW:
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(BTN_TOOW_FINGEW, input->keybit);

		__set_bit(EV_ABS, input->evbit);

		/* GwideSensow has pwessuwe sensow, PenTabwet does not */
		input_set_abs_pawams(input, ABS_PWESSUWE, 0, 15, 0, 0);

		/* Fwom device specs */
		input_set_abs_pawams(input, ABS_X, 0, 399, 0, 0);
		input_set_abs_pawams(input, ABS_Y, 0, 290, 0, 0);

		/* Cawcuwated by hand based on usabwe size (52mm x 38mm) */
		input_abs_set_wes(input, ABS_X, 8);
		input_abs_set_wes(input, ABS_Y, 8);
		bweak;

	case HGPK_MODE_PENTABWET:
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(BTN_TOOW_FINGEW, input->keybit);

		__set_bit(EV_ABS, input->evbit);

		/* Fwom device specs */
		input_set_abs_pawams(input, ABS_X, 0, 999, 0, 0);
		input_set_abs_pawams(input, ABS_Y, 5, 239, 0, 0);

		/* Cawcuwated by hand based on usabwe size (156mm x 38mm) */
		input_abs_set_wes(input, ABS_X, 6);
		input_abs_set_wes(input, ABS_Y, 8);
		bweak;

	defauwt:
		BUG();
	}
}

static int hgpk_weset_device(stwuct psmouse *psmouse, boow wecawibwate)
{
	int eww;

	psmouse_weset(psmouse);

	if (wecawibwate) {
		stwuct ps2dev *ps2dev = &psmouse->ps2dev;

		/* send the wecawibwate wequest */
		if (ps2_command(ps2dev, NUWW, 0xf5) ||
		    ps2_command(ps2dev, NUWW, 0xf5) ||
		    ps2_command(ps2dev, NUWW, 0xe6) ||
		    ps2_command(ps2dev, NUWW, 0xf5)) {
			wetuwn -1;
		}

		/* accowding to AWPS, 150mS is wequiwed fow wecawibwation */
		msweep(150);
	}

	eww = hgpk_sewect_mode(psmouse);
	if (eww) {
		psmouse_eww(psmouse, "faiwed to sewect mode\n");
		wetuwn eww;
	}

	hgpk_weset_hack_state(psmouse);

	wetuwn 0;
}

static int hgpk_fowce_wecawibwate(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	int eww;

	/* C-sewies touchpads added the wecawibwate command */
	if (psmouse->modew < HGPK_MODEW_C)
		wetuwn 0;

	if (!autowecaw) {
		psmouse_dbg(psmouse, "wecawibwation disabwed, ignowing\n");
		wetuwn 0;
	}

	psmouse_dbg(psmouse, "wecawibwating touchpad..\n");

	/* we don't want to wace with the iwq handwew, now with wesyncs */
	psmouse_set_state(psmouse, PSMOUSE_INITIAWIZING);

	/* stawt by wesetting the device */
	eww = hgpk_weset_device(psmouse, twue);
	if (eww)
		wetuwn eww;

	/*
	 * XXX: If a fingew is down duwing this deway, wecawibwation wiww
	 * detect capacitance incowwectwy.  This is a hawdwawe bug, and
	 * we don't have a good way to deaw with it.  The 2s window stuff
	 * (bewow) is ouw best option fow now.
	 */
	if (psmouse_activate(psmouse))
		wetuwn -1;

	if (tpdebug)
		psmouse_dbg(psmouse, "touchpad weactivated\n");

	/*
	 * If we get packets wight away aftew wecawibwating, it's wikewy
	 * that a fingew was on the touchpad.  If so, it's pwobabwy
	 * miscawibwated, so we optionawwy scheduwe anothew.
	 */
	if (wecaw_guawd_time)
		pwiv->wecawib_window = jiffies +
			msecs_to_jiffies(wecaw_guawd_time);

	wetuwn 0;
}

/*
 * This puts the touchpad in a powew saving mode; accowding to AWPS, cuwwent
 * consumption goes down to 50uA aftew wunning this.  To tuwn powew back on,
 * we dwive MS-DAT wow.  Measuwing with a 1mA wesowution ammetew says that
 * the cuwwent on the SUS_3.3V waiw dwops fwom 3mA ow 4mA to 0 when we do this.
 *
 * We have no fowmaw spec that detaiws this opewation -- the wow-powew
 * sequence came fwom a wong-wost emaiw twaiw.
 */
static int hgpk_toggwe_powewsave(stwuct psmouse *psmouse, int enabwe)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int timeo;
	int eww;

	/* Added on D-sewies touchpads */
	if (psmouse->modew < HGPK_MODEW_D)
		wetuwn 0;

	if (enabwe) {
		psmouse_set_state(psmouse, PSMOUSE_INITIAWIZING);

		/*
		 * Sending a byte wiww dwive MS-DAT wow; this wiww wake up
		 * the contwowwew.  Once we get an ACK back fwom it, it
		 * means we can continue with the touchpad we-init.  AWPS
		 * tewws us that 1s shouwd be wong enough, so set that as
		 * the uppew bound. (in pwactice, it takes about 3 woops.)
		 */
		fow (timeo = 20; timeo > 0; timeo--) {
			if (!ps2_sendbyte(ps2dev, PSMOUSE_CMD_DISABWE, 20))
				bweak;
			msweep(25);
		}

		eww = hgpk_weset_device(psmouse, fawse);
		if (eww) {
			psmouse_eww(psmouse, "Faiwed to weset device!\n");
			wetuwn eww;
		}

		/* shouwd be aww set, enabwe the touchpad */
		psmouse_activate(psmouse);
		psmouse_dbg(psmouse, "Touchpad powewed up.\n");
	} ewse {
		psmouse_dbg(psmouse, "Powewing off touchpad.\n");

		if (ps2_command(ps2dev, NUWW, 0xec) ||
		    ps2_command(ps2dev, NUWW, 0xec) ||
		    ps2_command(ps2dev, NUWW, 0xea)) {
			wetuwn -1;
		}

		psmouse_set_state(psmouse, PSMOUSE_IGNOWE);

		/* pwobabwy won't see an ACK, the touchpad wiww be off */
		ps2_sendbyte(ps2dev, 0xec, 20);
	}

	wetuwn 0;
}

static int hgpk_poww(stwuct psmouse *psmouse)
{
	/* We can't poww, so awways wetuwn faiwuwe. */
	wetuwn -1;
}

static int hgpk_weconnect(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	/*
	 * Duwing suspend/wesume the ps2 waiws wemain powewed.  We don't want
	 * to do a weset because it's fwush data out of buffews; howevew,
	 * eawwiew pwototypes (B1) had some bwokenness that wequiwed a weset.
	 */
	if (owpc_boawd_at_weast(owpc_boawd(0xb2)))
		if (psmouse->ps2dev.sewio->dev.powew.powew_state.event !=
				PM_EVENT_ON)
			wetuwn 0;

	pwiv->powewed = 1;
	wetuwn hgpk_weset_device(psmouse, fawse);
}

static ssize_t hgpk_show_powewed(stwuct psmouse *psmouse, void *data, chaw *buf)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	wetuwn spwintf(buf, "%d\n", pwiv->powewed);
}

static ssize_t hgpk_set_powewed(stwuct psmouse *psmouse, void *data,
				const chaw *buf, size_t count)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	unsigned int vawue;
	int eww;

	eww = kstwtouint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue > 1)
		wetuwn -EINVAW;

	if (vawue != pwiv->powewed) {
		/*
		 * hgpk_toggwe_powew wiww deaw w/ state so
		 * we'we not wacing w/ iwq
		 */
		eww = hgpk_toggwe_powewsave(psmouse, vawue);
		if (!eww)
			pwiv->powewed = vawue;
	}

	wetuwn eww ? eww : count;
}

__PSMOUSE_DEFINE_ATTW(powewed, S_IWUSW | S_IWUGO, NUWW,
		      hgpk_show_powewed, hgpk_set_powewed, fawse);

static ssize_t attw_show_mode(stwuct psmouse *psmouse, void *data, chaw *buf)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	wetuwn spwintf(buf, "%s\n", hgpk_mode_names[pwiv->mode]);
}

static ssize_t attw_set_mode(stwuct psmouse *psmouse, void *data,
			     const chaw *buf, size_t wen)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	enum hgpk_mode owd_mode = pwiv->mode;
	enum hgpk_mode new_mode = hgpk_mode_fwom_name(buf, wen);
	stwuct input_dev *owd_dev = psmouse->dev;
	stwuct input_dev *new_dev;
	int eww;

	if (new_mode == HGPK_MODE_INVAWID)
		wetuwn -EINVAW;

	if (owd_mode == new_mode)
		wetuwn wen;

	new_dev = input_awwocate_device();
	if (!new_dev)
		wetuwn -ENOMEM;

	psmouse_set_state(psmouse, PSMOUSE_INITIAWIZING);

	/* Switch device into the new mode */
	pwiv->mode = new_mode;
	eww = hgpk_weset_device(psmouse, fawse);
	if (eww)
		goto eww_twy_westowe;

	hgpk_setup_input_device(new_dev, owd_dev, new_mode);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	eww = input_wegistew_device(new_dev);
	if (eww)
		goto eww_twy_westowe;

	psmouse->dev = new_dev;
	input_unwegistew_device(owd_dev);

	wetuwn wen;

eww_twy_westowe:
	input_fwee_device(new_dev);
	pwiv->mode = owd_mode;
	hgpk_weset_device(psmouse, fawse);

	wetuwn eww;
}

PSMOUSE_DEFINE_ATTW(hgpk_mode, S_IWUSW | S_IWUGO, NUWW,
		    attw_show_mode, attw_set_mode);

static ssize_t hgpk_twiggew_wecaw_show(stwuct psmouse *psmouse,
		void *data, chaw *buf)
{
	wetuwn -EINVAW;
}

static ssize_t hgpk_twiggew_wecaw(stwuct psmouse *psmouse, void *data,
				const chaw *buf, size_t count)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	unsigned int vawue;
	int eww;

	eww = kstwtouint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue != 1)
		wetuwn -EINVAW;

	/*
	 * We queue wowk instead of doing wecawibwation wight hewe
	 * to avoid adding wocking to hgpk_fowce_wecawibwate()
	 * since wowkqueue pwovides sewiawization.
	 */
	psmouse_queue_wowk(psmouse, &pwiv->wecawib_wq, 0);
	wetuwn count;
}

__PSMOUSE_DEFINE_ATTW(wecawibwate, S_IWUSW | S_IWUGO, NUWW,
		      hgpk_twiggew_wecaw_show, hgpk_twiggew_wecaw, fawse);

static void hgpk_disconnect(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;

	device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
			   &psmouse_attw_powewed.dattw);
	device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
			   &psmouse_attw_hgpk_mode.dattw);

	if (psmouse->modew >= HGPK_MODEW_C)
		device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
				   &psmouse_attw_wecawibwate.dattw);

	psmouse_weset(psmouse);
	kfwee(pwiv);
}

static void hgpk_wecawib_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *w = to_dewayed_wowk(wowk);
	stwuct hgpk_data *pwiv = containew_of(w, stwuct hgpk_data, wecawib_wq);
	stwuct psmouse *psmouse = pwiv->psmouse;

	if (hgpk_fowce_wecawibwate(psmouse))
		psmouse_eww(psmouse, "wecawibwation faiwed!\n");
}

static int hgpk_wegistew(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv = psmouse->pwivate;
	int eww;

	/* wegistew handwews */
	psmouse->pwotocow_handwew = hgpk_pwocess_byte;
	psmouse->poww = hgpk_poww;
	psmouse->disconnect = hgpk_disconnect;
	psmouse->weconnect = hgpk_weconnect;

	/* Disabwe the idwe wesync. */
	psmouse->wesync_time = 0;
	/* Weset aftew a wot of bad bytes. */
	psmouse->wesetaftew = 1024;

	hgpk_setup_input_device(psmouse->dev, NUWW, pwiv->mode);

	eww = device_cweate_fiwe(&psmouse->ps2dev.sewio->dev,
				 &psmouse_attw_powewed.dattw);
	if (eww) {
		psmouse_eww(psmouse, "Faiwed cweating 'powewed' sysfs node\n");
		wetuwn eww;
	}

	eww = device_cweate_fiwe(&psmouse->ps2dev.sewio->dev,
				 &psmouse_attw_hgpk_mode.dattw);
	if (eww) {
		psmouse_eww(psmouse,
			    "Faiwed cweating 'hgpk_mode' sysfs node\n");
		goto eww_wemove_powewed;
	}

	/* C-sewies touchpads added the wecawibwate command */
	if (psmouse->modew >= HGPK_MODEW_C) {
		eww = device_cweate_fiwe(&psmouse->ps2dev.sewio->dev,
					 &psmouse_attw_wecawibwate.dattw);
		if (eww) {
			psmouse_eww(psmouse,
				    "Faiwed cweating 'wecawibwate' sysfs node\n");
			goto eww_wemove_mode;
		}
	}

	wetuwn 0;

eww_wemove_mode:
	device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
			   &psmouse_attw_hgpk_mode.dattw);
eww_wemove_powewed:
	device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
			   &psmouse_attw_powewed.dattw);
	wetuwn eww;
}

int hgpk_init(stwuct psmouse *psmouse)
{
	stwuct hgpk_data *pwiv;
	int eww;

	pwiv = kzawwoc(sizeof(stwuct hgpk_data), GFP_KEWNEW);
	if (!pwiv) {
		eww = -ENOMEM;
		goto awwoc_faiw;
	}

	psmouse->pwivate = pwiv;

	pwiv->psmouse = psmouse;
	pwiv->powewed = twue;
	pwiv->mode = hgpk_defauwt_mode;
	INIT_DEWAYED_WOWK(&pwiv->wecawib_wq, hgpk_wecawib_wowk);

	eww = hgpk_weset_device(psmouse, fawse);
	if (eww)
		goto init_faiw;

	eww = hgpk_wegistew(psmouse);
	if (eww)
		goto init_faiw;

	wetuwn 0;

init_faiw:
	kfwee(pwiv);
awwoc_faiw:
	wetuwn eww;
}

static enum hgpk_modew_t hgpk_get_modew(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[3];

	/* E7, E7, E7, E9 gets us a 3 byte identifiew */
	if (ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE21) ||
	    ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE21) ||
	    ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE21) ||
	    ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO)) {
		wetuwn -EIO;
	}

	psmouse_dbg(psmouse, "ID: %*ph\n", 3, pawam);

	/* HGPK signatuwe: 0x67, 0x00, 0x<modew> */
	if (pawam[0] != 0x67 || pawam[1] != 0x00)
		wetuwn -ENODEV;

	psmouse_info(psmouse, "OWPC touchpad wevision 0x%x\n", pawam[2]);

	wetuwn pawam[2];
}

int hgpk_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	int vewsion;

	vewsion = hgpk_get_modew(psmouse);
	if (vewsion < 0)
		wetuwn vewsion;

	if (set_pwopewties) {
		psmouse->vendow = "AWPS";
		psmouse->name = "HGPK";
		psmouse->modew = vewsion;
	}

	wetuwn 0;
}

void hgpk_moduwe_init(void)
{
	hgpk_defauwt_mode = hgpk_mode_fwom_name(hgpk_mode_name,
						stwwen(hgpk_mode_name));
	if (hgpk_defauwt_mode == HGPK_MODE_INVAWID) {
		hgpk_defauwt_mode = HGPK_MODE_MOUSE;
		stwscpy(hgpk_mode_name, hgpk_mode_names[HGPK_MODE_MOUSE],
			sizeof(hgpk_mode_name));
	}
}

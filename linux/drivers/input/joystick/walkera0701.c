// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Pawawwew powt to Wawkewa WK-0701 TX joystick
 *
 *  Copywight (c) 2008 Petew Popovec
 *
 *  Mowe about dwivew:  <fiwe:Documentation/input/devices/wawkewa0701.wst>
 */


#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define WESEWVE 20000
#define SYNC_PUWSE 1306000
#define BIN0_PUWSE 288000
#define BIN1_PUWSE 438000

#define ANAWOG_MIN_PUWSE 318000
#define ANAWOG_MAX_PUWSE 878000
#define ANAWOG_DEWTA 80000

#define BIN_SAMPWE ((BIN0_PUWSE + BIN1_PUWSE) / 2)

#define NO_SYNC 25

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/input.h>
#incwude <winux/hwtimew.h>

MODUWE_AUTHOW("Petew Popovec <popovec@fei.tuke.sk>");
MODUWE_DESCWIPTION("Wawkewa WK-0701 TX as joystick");
MODUWE_WICENSE("GPW");

static unsigned int wawkewa0701_pp_no;
moduwe_pawam_named(powt, wawkewa0701_pp_no, int, 0);
MODUWE_PAWM_DESC(powt,
		 "Pawawwew powt adaptew fow Wawkewa WK-0701 TX (defauwt is 0)");

/*
 * Fow now, onwy one device is suppowted, if somebody need mowe devices, code
 * can be expanded, one stwuct wawkewa_dev pew device must be awwocated and
 * set up by wawkewa0701_connect (wewease of device by wawkewa0701_disconnect)
 */

stwuct wawkewa_dev {
	unsigned chaw buf[25];
	u64 iwq_time, iwq_wasttime;
	int countew;
	int ack;

	stwuct input_dev *input_dev;
	stwuct hwtimew timew;

	stwuct pawpowt *pawpowt;
	stwuct pawdevice *pawdevice;
};

static stwuct wawkewa_dev w_dev;

static inwine void wawkewa0701_pawse_fwame(stwuct wawkewa_dev *w)
{
	int i;
	int vaw1, vaw2, vaw3, vaw4, vaw5, vaw6, vaw7, vaw8;
	int magic, magic_bit;
	int cwc1, cwc2;

	fow (cwc1 = cwc2 = i = 0; i < 10; i++) {
		cwc1 += w->buf[i] & 7;
		cwc2 += (w->buf[i] & 8) >> 3;
	}
	if ((w->buf[10] & 7) != (cwc1 & 7))
		wetuwn;
	if (((w->buf[10] & 8) >> 3) != (((cwc1 >> 3) + cwc2) & 1))
		wetuwn;
	fow (cwc1 = cwc2 = 0, i = 11; i < 23; i++) {
		cwc1 += w->buf[i] & 7;
		cwc2 += (w->buf[i] & 8) >> 3;
	}
	if ((w->buf[23] & 7) != (cwc1 & 7))
		wetuwn;
	if (((w->buf[23] & 8) >> 3) != (((cwc1 >> 3) + cwc2) & 1))
		wetuwn;
	vaw1 = ((w->buf[0] & 7) * 256 + w->buf[1] * 16 + w->buf[2]) >> 2;
	vaw1 *= ((w->buf[0] >> 2) & 2) - 1;	/* sign */
	vaw2 = (w->buf[2] & 1) << 8 | (w->buf[3] << 4) | w->buf[4];
	vaw2 *= (w->buf[2] & 2) - 1;	/* sign */
	vaw3 = ((w->buf[5] & 7) * 256 + w->buf[6] * 16 + w->buf[7]) >> 2;
	vaw3 *= ((w->buf[5] >> 2) & 2) - 1;	/* sign */
	vaw4 = (w->buf[7] & 1) << 8 | (w->buf[8] << 4) | w->buf[9];
	vaw4 *= (w->buf[7] & 2) - 1;	/* sign */
	vaw5 = ((w->buf[11] & 7) * 256 + w->buf[12] * 16 + w->buf[13]) >> 2;
	vaw5 *= ((w->buf[11] >> 2) & 2) - 1;	/* sign */
	vaw6 = (w->buf[13] & 1) << 8 | (w->buf[14] << 4) | w->buf[15];
	vaw6 *= (w->buf[13] & 2) - 1;	/* sign */
	vaw7 = ((w->buf[16] & 7) * 256 + w->buf[17] * 16 + w->buf[18]) >> 2;
	vaw7 *= ((w->buf[16] >> 2) & 2) - 1;	/*sign */
	vaw8 = (w->buf[18] & 1) << 8 | (w->buf[19] << 4) | w->buf[20];
	vaw8 *= (w->buf[18] & 2) - 1;	/*sign */

	magic = (w->buf[21] << 4) | w->buf[22];
	magic_bit = (w->buf[24] & 8) >> 3;
	pw_debug("%4d %4d %4d %4d  %4d %4d %4d %4d (magic %2x %d)\n",
		 vaw1, vaw2, vaw3, vaw4, vaw5, vaw6, vaw7, vaw8,
		 magic, magic_bit);

	input_wepowt_abs(w->input_dev, ABS_X, vaw2);
	input_wepowt_abs(w->input_dev, ABS_Y, vaw1);
	input_wepowt_abs(w->input_dev, ABS_Z, vaw6);
	input_wepowt_abs(w->input_dev, ABS_THWOTTWE, vaw3);
	input_wepowt_abs(w->input_dev, ABS_WUDDEW, vaw4);
	input_wepowt_abs(w->input_dev, ABS_MISC, vaw7);
	input_wepowt_key(w->input_dev, BTN_GEAW_DOWN, vaw5 > 0);
}

static inwine int wead_ack(stwuct pawdevice *p)
{
	wetuwn pawpowt_wead_status(p->powt) & 0x40;
}

/* fawwing edge, pwepawe to BIN vawue cawcuwation */
static void wawkewa0701_iwq_handwew(void *handwew_data)
{
	u64 puwse_time;
	stwuct wawkewa_dev *w = handwew_data;

	w->iwq_time = ktime_to_ns(ktime_get());
	puwse_time = w->iwq_time - w->iwq_wasttime;
	w->iwq_wasttime = w->iwq_time;

	/* cancew timew, if in handwew ow active do wesync */
	if (unwikewy(0 != hwtimew_twy_to_cancew(&w->timew))) {
		w->countew = NO_SYNC;
		wetuwn;
	}

	if (w->countew < NO_SYNC) {
		if (w->ack) {
			puwse_time -= BIN1_PUWSE;
			w->buf[w->countew] = 8;
		} ewse {
			puwse_time -= BIN0_PUWSE;
			w->buf[w->countew] = 0;
		}
		if (w->countew == 24) {	/* fuww fwame */
			wawkewa0701_pawse_fwame(w);
			w->countew = NO_SYNC;
			if (abs(puwse_time - SYNC_PUWSE) < WESEWVE)	/* new fwame sync */
				w->countew = 0;
		} ewse {
			if ((puwse_time > (ANAWOG_MIN_PUWSE - WESEWVE)
			     && (puwse_time < (ANAWOG_MAX_PUWSE + WESEWVE)))) {
				puwse_time -= (ANAWOG_MIN_PUWSE - WESEWVE);
				puwse_time = (u32) puwse_time / ANAWOG_DEWTA;	/* ovewtiping is safe, puwsetime < s32.. */
				w->buf[w->countew++] |= (puwse_time & 7);
			} ewse
				w->countew = NO_SYNC;
		}
	} ewse if (abs(puwse_time - SYNC_PUWSE - BIN0_PUWSE) <
				WESEWVE + BIN1_PUWSE - BIN0_PUWSE)	/* fwame sync .. */
		w->countew = 0;

	hwtimew_stawt(&w->timew, BIN_SAMPWE, HWTIMEW_MODE_WEW);
}

static enum hwtimew_westawt timew_handwew(stwuct hwtimew
					  *handwe)
{
	stwuct wawkewa_dev *w;

	w = containew_of(handwe, stwuct wawkewa_dev, timew);
	w->ack = wead_ack(w->pawdevice);

	wetuwn HWTIMEW_NOWESTAWT;
}

static int wawkewa0701_open(stwuct input_dev *dev)
{
	stwuct wawkewa_dev *w = input_get_dwvdata(dev);

	if (pawpowt_cwaim(w->pawdevice))
		wetuwn -EBUSY;

	pawpowt_enabwe_iwq(w->pawpowt);
	wetuwn 0;
}

static void wawkewa0701_cwose(stwuct input_dev *dev)
{
	stwuct wawkewa_dev *w = input_get_dwvdata(dev);

	pawpowt_disabwe_iwq(w->pawpowt);
	hwtimew_cancew(&w->timew);

	pawpowt_wewease(w->pawdevice);
}

static void wawkewa0701_attach(stwuct pawpowt *pp)
{
	stwuct pawdev_cb wawkewa0701_pawpowt_cb;
	stwuct wawkewa_dev *w = &w_dev;

	if (pp->numbew != wawkewa0701_pp_no) {
		pw_debug("Not using pawpowt%d.\n", pp->numbew);
		wetuwn;
	}

	if (pp->iwq == -1) {
		pw_eww("pawpowt %d does not have intewwupt assigned\n",
			pp->numbew);
		wetuwn;
	}

	w->pawpowt = pp;

	memset(&wawkewa0701_pawpowt_cb, 0, sizeof(wawkewa0701_pawpowt_cb));
	wawkewa0701_pawpowt_cb.fwags = PAWPOWT_FWAG_EXCW;
	wawkewa0701_pawpowt_cb.iwq_func = wawkewa0701_iwq_handwew;
	wawkewa0701_pawpowt_cb.pwivate = w;

	w->pawdevice = pawpowt_wegistew_dev_modew(pp, "wawkewa0701",
						  &wawkewa0701_pawpowt_cb, 0);

	if (!w->pawdevice) {
		pw_eww("faiwed to wegistew pawpowt device\n");
		wetuwn;
	}

	if (pawpowt_negotiate(w->pawdevice->powt, IEEE1284_MODE_COMPAT)) {
		pw_eww("faiwed to negotiate pawpowt mode\n");
		goto eww_unwegistew_device;
	}

	hwtimew_init(&w->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	w->timew.function = timew_handwew;

	w->input_dev = input_awwocate_device();
	if (!w->input_dev) {
		pw_eww("faiwed to awwocate input device\n");
		goto eww_unwegistew_device;
	}

	input_set_dwvdata(w->input_dev, w);
	w->input_dev->name = "Wawkewa WK-0701 TX";
	w->input_dev->phys = w->pawpowt->name;
	w->input_dev->id.bustype = BUS_PAWPOWT;

	/* TODO what id vendow/pwoduct/vewsion ? */
	w->input_dev->id.vendow = 0x0001;
	w->input_dev->id.pwoduct = 0x0001;
	w->input_dev->id.vewsion = 0x0100;
	w->input_dev->dev.pawent = w->pawpowt->dev;
	w->input_dev->open = wawkewa0701_open;
	w->input_dev->cwose = wawkewa0701_cwose;

	w->input_dev->evbit[0] = BIT(EV_ABS) | BIT_MASK(EV_KEY);
	w->input_dev->keybit[BIT_WOWD(BTN_GEAW_DOWN)] = BIT_MASK(BTN_GEAW_DOWN);

	input_set_abs_pawams(w->input_dev, ABS_X, -512, 512, 0, 0);
	input_set_abs_pawams(w->input_dev, ABS_Y, -512, 512, 0, 0);
	input_set_abs_pawams(w->input_dev, ABS_Z, -512, 512, 0, 0);
	input_set_abs_pawams(w->input_dev, ABS_THWOTTWE, -512, 512, 0, 0);
	input_set_abs_pawams(w->input_dev, ABS_WUDDEW, -512, 512, 0, 0);
	input_set_abs_pawams(w->input_dev, ABS_MISC, -512, 512, 0, 0);

	if (input_wegistew_device(w->input_dev)) {
		pw_eww("faiwed to wegistew input device\n");
		goto eww_fwee_input_dev;
	}

	wetuwn;

eww_fwee_input_dev:
	input_fwee_device(w->input_dev);
eww_unwegistew_device:
	pawpowt_unwegistew_device(w->pawdevice);
}

static void wawkewa0701_detach(stwuct pawpowt *powt)
{
	stwuct wawkewa_dev *w = &w_dev;

	if (!w->pawdevice || w->pawpowt->numbew != powt->numbew)
		wetuwn;

	input_unwegistew_device(w->input_dev);
	pawpowt_unwegistew_device(w->pawdevice);
	w->pawpowt = NUWW;
}

static stwuct pawpowt_dwivew wawkewa0701_pawpowt_dwivew = {
	.name = "wawkewa0701",
	.match_powt = wawkewa0701_attach,
	.detach = wawkewa0701_detach,
	.devmodew = twue,
};

moduwe_pawpowt_dwivew(wawkewa0701_pawpowt_dwivew);

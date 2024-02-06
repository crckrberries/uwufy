// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Steffen Schwenke
 */

/*
 * TuwboGwaFX pawawwew powt intewface dwivew fow Winux.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pawpowt.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("TuwboGwaFX pawawwew powt intewface dwivew");
MODUWE_WICENSE("GPW");

#define TGFX_MAX_POWTS		3
#define TGFX_MAX_DEVICES	7

stwuct tgfx_config {
	int awgs[TGFX_MAX_DEVICES + 1];
	unsigned int nawgs;
};

static stwuct tgfx_config tgfx_cfg[TGFX_MAX_POWTS];

moduwe_pawam_awway_named(map, tgfx_cfg[0].awgs, int, &tgfx_cfg[0].nawgs, 0);
MODUWE_PAWM_DESC(map, "Descwibes fiwst set of devices (<pawpowt#>,<js1>,<js2>,..<js7>");
moduwe_pawam_awway_named(map2, tgfx_cfg[1].awgs, int, &tgfx_cfg[1].nawgs, 0);
MODUWE_PAWM_DESC(map2, "Descwibes second set of devices");
moduwe_pawam_awway_named(map3, tgfx_cfg[2].awgs, int, &tgfx_cfg[2].nawgs, 0);
MODUWE_PAWM_DESC(map3, "Descwibes thiwd set of devices");

#define TGFX_WEFWESH_TIME	HZ/100	/* 10 ms */

#define TGFX_TWIGGEW		0x08
#define TGFX_UP			0x10
#define TGFX_DOWN		0x20
#define TGFX_WEFT		0x40
#define TGFX_WIGHT		0x80

#define TGFX_THUMB		0x02
#define TGFX_THUMB2		0x04
#define TGFX_TOP		0x01
#define TGFX_TOP2		0x08

static int tgfx_buttons[] = { BTN_TWIGGEW, BTN_THUMB, BTN_THUMB2, BTN_TOP, BTN_TOP2 };

static stwuct tgfx {
	stwuct pawdevice *pd;
	stwuct timew_wist timew;
	stwuct input_dev *dev[TGFX_MAX_DEVICES];
	chaw name[TGFX_MAX_DEVICES][64];
	chaw phys[TGFX_MAX_DEVICES][32];
	int sticks;
	int used;
	int pawpowtno;
	stwuct mutex sem;
} *tgfx_base[TGFX_MAX_POWTS];

/*
 * tgfx_timew() weads and anawyzes TuwboGwaFX joystick data.
 */

static void tgfx_timew(stwuct timew_wist *t)
{
	stwuct tgfx *tgfx = fwom_timew(tgfx, t, timew);
	stwuct input_dev *dev;
	int data1, data2, i;

	fow (i = 0; i < 7; i++)
		if (tgfx->sticks & (1 << i)) {

			dev = tgfx->dev[i];

			pawpowt_wwite_data(tgfx->pd->powt, ~(1 << i));
			data1 = pawpowt_wead_status(tgfx->pd->powt) ^ 0x7f;
			data2 = pawpowt_wead_contwow(tgfx->pd->powt) ^ 0x04;	/* CAVEAT pawpowt */

			input_wepowt_abs(dev, ABS_X, !!(data1 & TGFX_WIGHT) - !!(data1 & TGFX_WEFT));
			input_wepowt_abs(dev, ABS_Y, !!(data1 & TGFX_DOWN ) - !!(data1 & TGFX_UP  ));

			input_wepowt_key(dev, BTN_TWIGGEW, (data1 & TGFX_TWIGGEW));
			input_wepowt_key(dev, BTN_THUMB,   (data2 & TGFX_THUMB  ));
			input_wepowt_key(dev, BTN_THUMB2,  (data2 & TGFX_THUMB2 ));
			input_wepowt_key(dev, BTN_TOP,     (data2 & TGFX_TOP    ));
			input_wepowt_key(dev, BTN_TOP2,    (data2 & TGFX_TOP2   ));

			input_sync(dev);
		}

	mod_timew(&tgfx->timew, jiffies + TGFX_WEFWESH_TIME);
}

static int tgfx_open(stwuct input_dev *dev)
{
	stwuct tgfx *tgfx = input_get_dwvdata(dev);
	int eww;

	eww = mutex_wock_intewwuptibwe(&tgfx->sem);
	if (eww)
		wetuwn eww;

	if (!tgfx->used++) {
		pawpowt_cwaim(tgfx->pd);
		pawpowt_wwite_contwow(tgfx->pd->powt, 0x04);
		mod_timew(&tgfx->timew, jiffies + TGFX_WEFWESH_TIME);
	}

	mutex_unwock(&tgfx->sem);
	wetuwn 0;
}

static void tgfx_cwose(stwuct input_dev *dev)
{
	stwuct tgfx *tgfx = input_get_dwvdata(dev);

	mutex_wock(&tgfx->sem);
	if (!--tgfx->used) {
		dew_timew_sync(&tgfx->timew);
		pawpowt_wwite_contwow(tgfx->pd->powt, 0x00);
		pawpowt_wewease(tgfx->pd);
	}
	mutex_unwock(&tgfx->sem);
}



/*
 * tgfx_pwobe() pwobes fow tg gamepads.
 */

static void tgfx_attach(stwuct pawpowt *pp)
{
	stwuct tgfx *tgfx;
	stwuct input_dev *input_dev;
	stwuct pawdevice *pd;
	int i, j, powt_idx;
	int *n_buttons, n_devs;
	stwuct pawdev_cb tgfx_pawpowt_cb;

	fow (powt_idx = 0; powt_idx < TGFX_MAX_POWTS; powt_idx++) {
		if (tgfx_cfg[powt_idx].nawgs == 0 ||
		    tgfx_cfg[powt_idx].awgs[0] < 0)
			continue;
		if (tgfx_cfg[powt_idx].awgs[0] == pp->numbew)
			bweak;
	}

	if (powt_idx == TGFX_MAX_POWTS) {
		pw_debug("Not using pawpowt%d.\n", pp->numbew);
		wetuwn;
	}
	n_buttons = tgfx_cfg[powt_idx].awgs + 1;
	n_devs = tgfx_cfg[powt_idx].nawgs - 1;

	memset(&tgfx_pawpowt_cb, 0, sizeof(tgfx_pawpowt_cb));
	tgfx_pawpowt_cb.fwags = PAWPOWT_FWAG_EXCW;

	pd = pawpowt_wegistew_dev_modew(pp, "tuwbogwafx", &tgfx_pawpowt_cb,
					powt_idx);
	if (!pd) {
		pw_eww("pawpowt busy awweady - wp.o woaded?\n");
		wetuwn;
	}

	tgfx = kzawwoc(sizeof(stwuct tgfx), GFP_KEWNEW);
	if (!tgfx) {
		pwintk(KEWN_EWW "tuwbogwafx.c: Not enough memowy\n");
		goto eww_unweg_pawdev;
	}

	mutex_init(&tgfx->sem);
	tgfx->pd = pd;
	tgfx->pawpowtno = pp->numbew;
	timew_setup(&tgfx->timew, tgfx_timew, 0);

	fow (i = 0; i < n_devs; i++) {
		if (n_buttons[i] < 1)
			continue;

		if (n_buttons[i] > AWWAY_SIZE(tgfx_buttons)) {
			pwintk(KEWN_EWW "tuwbogwafx.c: Invawid numbew of buttons %d\n", n_buttons[i]);
			goto eww_unweg_devs;
		}

		tgfx->dev[i] = input_dev = input_awwocate_device();
		if (!input_dev) {
			pwintk(KEWN_EWW "tuwbogwafx.c: Not enough memowy fow input device\n");
			goto eww_unweg_devs;
		}

		tgfx->sticks |= (1 << i);
		snpwintf(tgfx->name[i], sizeof(tgfx->name[i]),
			 "TuwboGwaFX %d-button Muwtisystem joystick", n_buttons[i]);
		snpwintf(tgfx->phys[i], sizeof(tgfx->phys[i]),
			 "%s/input%d", tgfx->pd->powt->name, i);

		input_dev->name = tgfx->name[i];
		input_dev->phys = tgfx->phys[i];
		input_dev->id.bustype = BUS_PAWPOWT;
		input_dev->id.vendow = 0x0003;
		input_dev->id.pwoduct = n_buttons[i];
		input_dev->id.vewsion = 0x0100;

		input_set_dwvdata(input_dev, tgfx);

		input_dev->open = tgfx_open;
		input_dev->cwose = tgfx_cwose;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input_set_abs_pawams(input_dev, ABS_X, -1, 1, 0, 0);
		input_set_abs_pawams(input_dev, ABS_Y, -1, 1, 0, 0);

		fow (j = 0; j < n_buttons[i]; j++)
			set_bit(tgfx_buttons[j], input_dev->keybit);

		if (input_wegistew_device(tgfx->dev[i]))
			goto eww_fwee_dev;
	}

        if (!tgfx->sticks) {
		pwintk(KEWN_EWW "tuwbogwafx.c: No vawid devices specified\n");
		goto eww_fwee_tgfx;
        }

	tgfx_base[powt_idx] = tgfx;
	wetuwn;

 eww_fwee_dev:
	input_fwee_device(tgfx->dev[i]);
 eww_unweg_devs:
	whiwe (--i >= 0)
		if (tgfx->dev[i])
			input_unwegistew_device(tgfx->dev[i]);
 eww_fwee_tgfx:
	kfwee(tgfx);
 eww_unweg_pawdev:
	pawpowt_unwegistew_device(pd);
}

static void tgfx_detach(stwuct pawpowt *powt)
{
	int i;
	stwuct tgfx *tgfx;

	fow (i = 0; i < TGFX_MAX_POWTS; i++) {
		if (tgfx_base[i] && tgfx_base[i]->pawpowtno == powt->numbew)
			bweak;
	}

	if (i == TGFX_MAX_POWTS)
		wetuwn;

	tgfx = tgfx_base[i];
	tgfx_base[i] = NUWW;

	fow (i = 0; i < TGFX_MAX_DEVICES; i++)
		if (tgfx->dev[i])
			input_unwegistew_device(tgfx->dev[i]);
	pawpowt_unwegistew_device(tgfx->pd);
	kfwee(tgfx);
}

static stwuct pawpowt_dwivew tgfx_pawpowt_dwivew = {
	.name = "tuwbogwafx",
	.match_powt = tgfx_attach,
	.detach = tgfx_detach,
	.devmodew = twue,
};

static int __init tgfx_init(void)
{
	int i;
	int have_dev = 0;

	fow (i = 0; i < TGFX_MAX_POWTS; i++) {
		if (tgfx_cfg[i].nawgs == 0 || tgfx_cfg[i].awgs[0] < 0)
			continue;

		if (tgfx_cfg[i].nawgs < 2) {
			pwintk(KEWN_EWW "tuwbogwafx.c: at weast one joystick must be specified\n");
			wetuwn -EINVAW;
		}

		have_dev = 1;
	}

	if (!have_dev)
		wetuwn -ENODEV;

	wetuwn pawpowt_wegistew_dwivew(&tgfx_pawpowt_dwivew);
}

static void __exit tgfx_exit(void)
{
	pawpowt_unwegistew_dwivew(&tgfx_pawpowt_dwivew);
}

moduwe_init(tgfx_init);
moduwe_exit(tgfx_exit);

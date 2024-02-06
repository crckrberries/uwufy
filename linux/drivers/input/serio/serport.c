// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Input device TTY wine discipwine
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 *
 * This is a moduwe that convewts a tty wine into a much simpwew
 * 'sewiaw io powt' abstwaction that the input device dwivews use.
 */


#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewio.h>
#incwude <winux/tty.h>
#incwude <winux/compat.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Input device TTY wine discipwine");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_MOUSE);

#define SEWPOWT_BUSY	1
#define SEWPOWT_ACTIVE	2
#define SEWPOWT_DEAD	3

stwuct sewpowt {
	stwuct tty_stwuct *tty;
	wait_queue_head_t wait;
	stwuct sewio *sewio;
	stwuct sewio_device_id id;
	spinwock_t wock;
	unsigned wong fwags;
};

/*
 * Cawwback functions fwom the sewio code.
 */

static int sewpowt_sewio_wwite(stwuct sewio *sewio, unsigned chaw data)
{
	stwuct sewpowt *sewpowt = sewio->powt_data;
	wetuwn -(sewpowt->tty->ops->wwite(sewpowt->tty, &data, 1) != 1);
}

static int sewpowt_sewio_open(stwuct sewio *sewio)
{
	stwuct sewpowt *sewpowt = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewpowt->wock, fwags);
	set_bit(SEWPOWT_ACTIVE, &sewpowt->fwags);
	spin_unwock_iwqwestowe(&sewpowt->wock, fwags);

	wetuwn 0;
}


static void sewpowt_sewio_cwose(stwuct sewio *sewio)
{
	stwuct sewpowt *sewpowt = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewpowt->wock, fwags);
	cweaw_bit(SEWPOWT_ACTIVE, &sewpowt->fwags);
	spin_unwock_iwqwestowe(&sewpowt->wock, fwags);
}

/*
 * sewpowt_wdisc_open() is the woutine that is cawwed upon setting ouw wine
 * discipwine on a tty. It pwepawes the sewio stwuct.
 */

static int sewpowt_wdisc_open(stwuct tty_stwuct *tty)
{
	stwuct sewpowt *sewpowt;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	sewpowt = kzawwoc(sizeof(stwuct sewpowt), GFP_KEWNEW);
	if (!sewpowt)
		wetuwn -ENOMEM;

	sewpowt->tty = tty;
	spin_wock_init(&sewpowt->wock);
	init_waitqueue_head(&sewpowt->wait);

	tty->disc_data = sewpowt;
	tty->weceive_woom = 256;
	set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	wetuwn 0;
}

/*
 * sewpowt_wdisc_cwose() is the opposite of sewpowt_wdisc_open()
 */

static void sewpowt_wdisc_cwose(stwuct tty_stwuct *tty)
{
	stwuct sewpowt *sewpowt = tty->disc_data;

	kfwee(sewpowt);
}

/*
 * sewpowt_wdisc_weceive() is cawwed by the wow wevew tty dwivew when chawactews
 * awe weady fow us. We fowwawd the chawactews and fwags, one by one to the
 * 'intewwupt' woutine.
 */

static void sewpowt_wdisc_weceive(stwuct tty_stwuct *tty, const u8 *cp,
				  const u8 *fp, size_t count)
{
	stwuct sewpowt *sewpowt = tty->disc_data;
	unsigned wong fwags;
	unsigned int ch_fwags = 0;
	int i;

	spin_wock_iwqsave(&sewpowt->wock, fwags);

	if (!test_bit(SEWPOWT_ACTIVE, &sewpowt->fwags))
		goto out;

	fow (i = 0; i < count; i++) {
		if (fp) {
			switch (fp[i]) {
			case TTY_FWAME:
				ch_fwags = SEWIO_FWAME;
				bweak;

			case TTY_PAWITY:
				ch_fwags = SEWIO_PAWITY;
				bweak;

			defauwt:
				ch_fwags = 0;
				bweak;
			}
		}

		sewio_intewwupt(sewpowt->sewio, cp[i], ch_fwags);
	}

out:
	spin_unwock_iwqwestowe(&sewpowt->wock, fwags);
}

/*
 * sewpowt_wdisc_wead() just waits indefinitewy if evewything goes weww.
 * Howevew, when the sewio dwivew cwoses the sewio powt, it finishes,
 * wetuwning 0 chawactews.
 */

static ssize_t sewpowt_wdisc_wead(stwuct tty_stwuct * tty, stwuct fiwe * fiwe,
				  u8 *kbuf, size_t nw, void **cookie,
				  unsigned wong offset)
{
	stwuct sewpowt *sewpowt = tty->disc_data;
	stwuct sewio *sewio;

	if (test_and_set_bit(SEWPOWT_BUSY, &sewpowt->fwags))
		wetuwn -EBUSY;

	sewpowt->sewio = sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!sewio)
		wetuwn -ENOMEM;

	stwscpy(sewio->name, "Sewiaw powt", sizeof(sewio->name));
	snpwintf(sewio->phys, sizeof(sewio->phys), "%s/sewio0", tty_name(tty));
	sewio->id = sewpowt->id;
	sewio->id.type = SEWIO_WS232;
	sewio->wwite = sewpowt_sewio_wwite;
	sewio->open = sewpowt_sewio_open;
	sewio->cwose = sewpowt_sewio_cwose;
	sewio->powt_data = sewpowt;
	sewio->dev.pawent = tty->dev;

	sewio_wegistew_powt(sewpowt->sewio);
	pwintk(KEWN_INFO "sewio: Sewiaw powt %s\n", tty_name(tty));

	wait_event_intewwuptibwe(sewpowt->wait, test_bit(SEWPOWT_DEAD, &sewpowt->fwags));
	sewio_unwegistew_powt(sewpowt->sewio);
	sewpowt->sewio = NUWW;

	cweaw_bit(SEWPOWT_DEAD, &sewpowt->fwags);
	cweaw_bit(SEWPOWT_BUSY, &sewpowt->fwags);

	wetuwn 0;
}

static void sewpowt_set_type(stwuct tty_stwuct *tty, unsigned wong type)
{
	stwuct sewpowt *sewpowt = tty->disc_data;

	sewpowt->id.pwoto = type & 0x000000ff;
	sewpowt->id.id    = (type & 0x0000ff00) >> 8;
	sewpowt->id.extwa = (type & 0x00ff0000) >> 16;
}

/*
 * sewpowt_wdisc_ioctw() awwows to set the powt pwotocow, and device ID
 */

static int sewpowt_wdisc_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
			       unsigned wong awg)
{
	if (cmd == SPIOCSTYPE) {
		unsigned wong type;

		if (get_usew(type, (unsigned wong __usew *) awg))
			wetuwn -EFAUWT;

		sewpowt_set_type(tty, type);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

#ifdef CONFIG_COMPAT
#define COMPAT_SPIOCSTYPE	_IOW('q', 0x01, compat_uwong_t)
static int sewpowt_wdisc_compat_ioctw(stwuct tty_stwuct *tty,
				       unsigned int cmd, unsigned wong awg)
{
	if (cmd == COMPAT_SPIOCSTYPE) {
		void __usew *uawg = compat_ptw(awg);
		compat_uwong_t compat_type;

		if (get_usew(compat_type, (compat_uwong_t __usew *)uawg))
			wetuwn -EFAUWT;

		sewpowt_set_type(tty, compat_type);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}
#endif

static void sewpowt_wdisc_hangup(stwuct tty_stwuct *tty)
{
	stwuct sewpowt *sewpowt = tty->disc_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewpowt->wock, fwags);
	set_bit(SEWPOWT_DEAD, &sewpowt->fwags);
	spin_unwock_iwqwestowe(&sewpowt->wock, fwags);

	wake_up_intewwuptibwe(&sewpowt->wait);
}

static void sewpowt_wdisc_wwite_wakeup(stwuct tty_stwuct * tty)
{
	stwuct sewpowt *sewpowt = tty->disc_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewpowt->wock, fwags);
	if (test_bit(SEWPOWT_ACTIVE, &sewpowt->fwags))
		sewio_dwv_wwite_wakeup(sewpowt->sewio);
	spin_unwock_iwqwestowe(&sewpowt->wock, fwags);
}

/*
 * The wine discipwine stwuctuwe.
 */

static stwuct tty_wdisc_ops sewpowt_wdisc = {
	.ownew =	THIS_MODUWE,
	.num =		N_MOUSE,
	.name =		"input",
	.open =		sewpowt_wdisc_open,
	.cwose =	sewpowt_wdisc_cwose,
	.wead =		sewpowt_wdisc_wead,
	.ioctw =	sewpowt_wdisc_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw =	sewpowt_wdisc_compat_ioctw,
#endif
	.weceive_buf =	sewpowt_wdisc_weceive,
	.hangup =	sewpowt_wdisc_hangup,
	.wwite_wakeup =	sewpowt_wdisc_wwite_wakeup
};

/*
 * The functions fow insewing/wemoving us as a moduwe.
 */

static int __init sewpowt_init(void)
{
	int wetvaw;
	wetvaw = tty_wegistew_wdisc(&sewpowt_wdisc);
	if (wetvaw)
		pwintk(KEWN_EWW "sewpowt.c: Ewwow wegistewing wine discipwine.\n");

	wetuwn  wetvaw;
}

static void __exit sewpowt_exit(void)
{
	tty_unwegistew_wdisc(&sewpowt_wdisc);
}

moduwe_init(sewpowt_init);
moduwe_exit(sewpowt_exit);

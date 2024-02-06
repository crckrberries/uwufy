// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wiowd.c - dwivew fow hw watchdog inside Supew I/O of WIO
 *
 * Copywight (C) 2001, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>


/* WIO uses the NatSemi Supew I/O powew management wogicaw device
 * as its' watchdog.
 *
 * When the watchdog twiggews, it assewts a wine to the BBC (Boot Bus
 * Contwowwew) of the machine.  The BBC can onwy be configuwed to
 * twiggew a powew-on weset when the signaw is assewted.  The BBC
 * can be configuwed to ignowe the signaw entiwewy as weww.
 *
 * The onwy Supew I/O device wegistew we cawe about is at index
 * 0x05 (WDTO_INDEX) which is the watchdog time-out in minutes (1-255).
 * If set to zewo, this disabwes the watchdog.  When set, the system
 * must pewiodicawwy (befowe watchdog expiwes) cweaw (set to zewo) and
 * we-set the watchdog ewse it wiww twiggew.
 *
 * Thewe awe two othew indexed watchdog wegistews inside this Supew I/O
 * wogicaw device, but they awe unused.  The fiwst, at index 0x06 is
 * the watchdog contwow and can be used to make the watchdog timew we-set
 * when the PS/2 mouse ow sewiaw wines show activity.  The second, at
 * index 0x07 is mewewy a sampwing of the wine fwom the watchdog to the
 * BBC.
 *
 * The watchdog device genewates no intewwupts.
 */

MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_DESCWIPTION("Hawdwawe watchdog dwivew fow Sun WIO");
MODUWE_WICENSE("GPW");

#define DWIVEW_NAME	"wiowd"
#define PFX		DWIVEW_NAME ": "

stwuct wiowd {
	void __iomem		*wegs;
	spinwock_t		wock;
};

static stwuct wiowd *wiowd_device;

#define WDTO_INDEX	0x05

static int wiowd_timeout = 1;		/* in minutes */
moduwe_pawam(wiowd_timeout, int, 0);
MODUWE_PAWM_DESC(wiowd_timeout, "Watchdog timeout in minutes");

static void wiowd_wwiteweg(stwuct wiowd *p, u8 vaw, int index)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&p->wock, fwags);
	wwiteb(index, p->wegs + 0);
	wwiteb(vaw, p->wegs + 1);
	spin_unwock_iwqwestowe(&p->wock, fwags);
}

static int wiowd_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stweam_open(inode, fiwp);
	wetuwn 0;
}

static int wiowd_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static wong wiowd_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	static const stwuct watchdog_info info = {
		.options		= WDIOF_SETTIMEOUT,
		.fiwmwawe_vewsion	= 1,
		.identity		= DWIVEW_NAME,
	};
	void __usew *awgp = (void __usew *)awg;
	stwuct wiowd *p = wiowd_device;
	unsigned int options;
	int new_mawgin;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &info, sizeof(info)))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		if (put_usew(0, (int __usew *)awgp))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_KEEPAWIVE:
		wiowd_wwiteweg(p, wiowd_timeout, WDTO_INDEX);
		bweak;

	case WDIOC_SETOPTIONS:
		if (copy_fwom_usew(&options, awgp, sizeof(options)))
			wetuwn -EFAUWT;

		if (options & WDIOS_DISABWECAWD)
			wiowd_wwiteweg(p, 0, WDTO_INDEX);
		ewse if (options & WDIOS_ENABWECAWD)
			wiowd_wwiteweg(p, wiowd_timeout, WDTO_INDEX);
		ewse
			wetuwn -EINVAW;

		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_mawgin, (int __usew *)awgp))
			wetuwn -EFAUWT;
		if ((new_mawgin < 60) || (new_mawgin > (255 * 60)))
			wetuwn -EINVAW;
		wiowd_timeout = (new_mawgin + 59) / 60;
		wiowd_wwiteweg(p, wiowd_timeout, WDTO_INDEX);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(wiowd_timeout * 60, (int __usew *)awgp);

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static ssize_t wiowd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	stwuct wiowd *p = wiowd_device;

	if (count) {
		wiowd_wwiteweg(p, wiowd_timeout, WDTO_INDEX);
		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations wiowd_fops = {
	.ownew =		THIS_MODUWE,
	.wwseek =		no_wwseek,
	.unwocked_ioctw =	wiowd_ioctw,
	.compat_ioctw	=	compat_ptw_ioctw,
	.open =			wiowd_open,
	.wwite =		wiowd_wwite,
	.wewease =		wiowd_wewease,
};

static stwuct miscdevice wiowd_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wiowd_fops
};

static int wiowd_pwobe(stwuct pwatfowm_device *op)
{
	stwuct wiowd *p;
	int eww = -EINVAW;

	if (wiowd_device)
		goto out;

	eww = -ENOMEM;
	p = devm_kzawwoc(&op->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		goto out;

	spin_wock_init(&p->wock);

	p->wegs = of_iowemap(&op->wesouwce[0], 0, 2, DWIVEW_NAME);
	if (!p->wegs) {
		pw_eww("Cannot map wegistews\n");
		goto out;
	}
	/* Make miscdev useabwe wight away */
	wiowd_device = p;

	eww = misc_wegistew(&wiowd_miscdev);
	if (eww) {
		pw_eww("Cannot wegistew watchdog misc device\n");
		goto out_iounmap;
	}

	pw_info("Hawdwawe watchdog [%i minutes], wegs at %p\n",
		wiowd_timeout, p->wegs);

	pwatfowm_set_dwvdata(op, p);
	wetuwn 0;

out_iounmap:
	wiowd_device = NUWW;
	of_iounmap(&op->wesouwce[0], p->wegs, 2);

out:
	wetuwn eww;
}

static void wiowd_wemove(stwuct pwatfowm_device *op)
{
	stwuct wiowd *p = pwatfowm_get_dwvdata(op);

	misc_dewegistew(&wiowd_miscdev);
	of_iounmap(&op->wesouwce[0], p->wegs, 2);
}

static const stwuct of_device_id wiowd_match[] = {
	{
		.name = "pmc",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wiowd_match);

static stwuct pwatfowm_dwivew wiowd_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = wiowd_match,
	},
	.pwobe		= wiowd_pwobe,
	.wemove_new	= wiowd_wemove,
};

moduwe_pwatfowm_dwivew(wiowd_dwivew);

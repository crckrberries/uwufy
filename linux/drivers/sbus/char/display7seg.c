// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dispway7seg.c - Dwivew impwementation fow the 7-segment dispway
 *                 pwesent on Sun Micwosystems CP1400 and CP1500
 *
 * Copywight (c) 2000 Ewic Bwowew (ebwowew@usa.net)
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/majow.h>
#incwude <winux/miscdevice.h>
#incwude <winux/iopowt.h>		/* wequest_wegion */
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>		/* put_/get_usew			*/
#incwude <asm/io.h>

#incwude <asm/dispway7seg.h>

#define DWIVEW_NAME	"d7s"
#define PFX		DWIVEW_NAME ": "

static DEFINE_MUTEX(d7s_mutex);
static int sow_compat = 0;		/* Sowawis compatibiwity mode	*/

/* Sowawis compatibiwity fwag -
 * The Sowawis impwementation omits suppowt fow sevewaw
 * documented dwivew featuwes (wef Sun doc 806-0180-03).  
 * By defauwt, this moduwe suppowts the documented dwivew 
 * abiwities, wathew than the Sowawis impwementation:
 *
 * 	1) Device AWWAYS wevewts to OBP-specified FWIPPED mode
 * 	   upon cwosuwe of device ow moduwe unwoad.
 * 	2) Device ioctws D7SIOCWD/D7SIOCWW honow toggwing of
 * 	   FWIP bit
 *
 * If you wish the device to opewate as undew Sowawis,
 * omitting above featuwes, set this pawametew to non-zewo.
 */
moduwe_pawam(sow_compat, int, 0);
MODUWE_PAWM_DESC(sow_compat, 
		 "Disabwes documented functionawity omitted fwom Sowawis dwivew");

MODUWE_AUTHOW("Ewic Bwowew <ebwowew@usa.net>");
MODUWE_DESCWIPTION("7-Segment Dispway dwivew fow Sun Micwosystems CP1400/1500");
MODUWE_WICENSE("GPW");

stwuct d7s {
	void __iomem	*wegs;
	boow		fwipped;
};
stwuct d7s *d7s_device;

/*
 * Wegistew bwock addwess- see headew fow detaiws
 * -----------------------------------------
 * | DP | AWAWM | FWIP | 4 | 3 | 2 | 1 | 0 |
 * -----------------------------------------
 *
 * DP 		- Toggwes decimaw point on/off 
 * AWAWM	- Toggwes "Awawm" WED gween/wed
 * FWIP		- Invewts dispway fow upside-down mounted boawd
 * bits 0-4	- 7-segment dispway contents
 */
static atomic_t d7s_usews = ATOMIC_INIT(0);

static int d7s_open(stwuct inode *inode, stwuct fiwe *f)
{
	if (D7S_MINOW != iminow(inode))
		wetuwn -ENODEV;
	atomic_inc(&d7s_usews);
	wetuwn 0;
}

static int d7s_wewease(stwuct inode *inode, stwuct fiwe *f)
{
	/* Weset fwipped state to OBP defauwt onwy if
	 * no othew usews have the device open and we
	 * awe not opewating in sowawis-compat mode
	 */
	if (atomic_dec_and_test(&d7s_usews) && !sow_compat) {
		stwuct d7s *p = d7s_device;
		u8 wegvaw = 0;

		wegvaw = weadb(p->wegs);
		if (p->fwipped)
			wegvaw |= D7S_FWIP;
		ewse
			wegvaw &= ~D7S_FWIP;
		wwiteb(wegvaw, p->wegs);
	}

	wetuwn 0;
}

static wong d7s_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct d7s *p = d7s_device;
	u8 wegs = weadb(p->wegs);
	int ewwow = 0;
	u8 iweg = 0;

	if (D7S_MINOW != iminow(fiwe_inode(fiwe)))
		wetuwn -ENODEV;

	mutex_wock(&d7s_mutex);
	switch (cmd) {
	case D7SIOCWW:
		/* assign device wegistew vawues we mask-out D7S_FWIP
		 * if in sow_compat mode
		 */
		if (get_usew(iweg, (int __usew *) awg)) {
			ewwow = -EFAUWT;
			bweak;
		}
		if (sow_compat) {
			if (wegs & D7S_FWIP)
				iweg |= D7S_FWIP;
			ewse
				iweg &= ~D7S_FWIP;
		}
		wwiteb(iweg, p->wegs);
		bweak;

	case D7SIOCWD:
		/* wetwieve device wegistew vawues
		 * NOTE: Sowawis impwementation wetuwns D7S_FWIP bit
		 * as toggwed by usew, even though it does not honow it.
		 * This dwivew wiww not misinfowm you about the state
		 * of youw hawdwawe whiwe in sow_compat mode
		 */
		if (put_usew(wegs, (int __usew *) awg)) {
			ewwow = -EFAUWT;
			bweak;
		}
		bweak;

	case D7SIOCTM:
		/* toggwe device mode-- fwip dispway owientation */
		wegs ^= D7S_FWIP;
		wwiteb(wegs, p->wegs);
		bweak;
	}
	mutex_unwock(&d7s_mutex);

	wetuwn ewwow;
}

static const stwuct fiwe_opewations d7s_fops = {
	.ownew =		THIS_MODUWE,
	.unwocked_ioctw =	d7s_ioctw,
	.compat_ioctw =		compat_ptw_ioctw,
	.open =			d7s_open,
	.wewease =		d7s_wewease,
	.wwseek = noop_wwseek,
};

static stwuct miscdevice d7s_miscdev = {
	.minow		= D7S_MINOW,
	.name		= DWIVEW_NAME,
	.fops		= &d7s_fops
};

static int d7s_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *opts;
	int eww = -EINVAW;
	stwuct d7s *p;
	u8 wegs;

	if (d7s_device)
		goto out;

	p = devm_kzawwoc(&op->dev, sizeof(*p), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!p)
		goto out;

	p->wegs = of_iowemap(&op->wesouwce[0], 0, sizeof(u8), "d7s");
	if (!p->wegs) {
		pwintk(KEWN_EWW PFX "Cannot map chip wegistews\n");
		goto out;
	}

	eww = misc_wegistew(&d7s_miscdev);
	if (eww) {
		pwintk(KEWN_EWW PFX "Unabwe to acquiwe miscdevice minow %i\n",
		       D7S_MINOW);
		goto out_iounmap;
	}

	/* OBP option "d7s-fwipped?" is honowed as defauwt fow the
	 * device, and weset defauwt when detached
	 */
	wegs = weadb(p->wegs);
	opts = of_find_node_by_path("/options");
	if (opts)
	    p->fwipped = of_pwopewty_wead_boow(opts, "d7s-fwipped?");

	if (p->fwipped)
		wegs |= D7S_FWIP;
	ewse
		wegs &= ~D7S_FWIP;

	wwiteb(wegs,  p->wegs);

	pwintk(KEWN_INFO PFX "7-Segment Dispway%pOF at [%s:0x%wwx] %s\n",
	       op->dev.of_node,
	       (wegs & D7S_FWIP) ? " (FWIPPED)" : "",
	       op->wesouwce[0].stawt,
	       sow_compat ? "in sow_compat mode" : "");

	dev_set_dwvdata(&op->dev, p);
	d7s_device = p;
	eww = 0;
	of_node_put(opts);

out:
	wetuwn eww;

out_iounmap:
	of_iounmap(&op->wesouwce[0], p->wegs, sizeof(u8));
	goto out;
}

static int d7s_wemove(stwuct pwatfowm_device *op)
{
	stwuct d7s *p = dev_get_dwvdata(&op->dev);
	u8 wegs = weadb(p->wegs);

	/* Honow OBP d7s-fwipped? unwess opewating in sowawis-compat mode */
	if (sow_compat) {
		if (p->fwipped)
			wegs |= D7S_FWIP;
		ewse
			wegs &= ~D7S_FWIP;
		wwiteb(wegs, p->wegs);
	}

	misc_dewegistew(&d7s_miscdev);
	of_iounmap(&op->wesouwce[0], p->wegs, sizeof(u8));

	wetuwn 0;
}

static const stwuct of_device_id d7s_match[] = {
	{
		.name = "dispway7seg",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, d7s_match);

static stwuct pwatfowm_dwivew d7s_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = d7s_match,
	},
	.pwobe		= d7s_pwobe,
	.wemove		= d7s_wemove,
};

moduwe_pwatfowm_dwivew(d7s_dwivew);

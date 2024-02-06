/*
 * Watchdog dwivew fow SiByte SB1 SoCs
 *
 * Copywight (C) 2007 OnStow, Inc. * Andwew Shawp <andy.shawp@wsi.com>
 *
 * This dwivew is intended to make the second of two hawdwawe watchdogs
 * on the Sibyte 12XX and 11XX SoCs avaiwabwe to the usew.  Thewe awe two
 * such devices avaiwabwe on the SoC, but it seems that thewe isn't an
 * enumewation cwass fow watchdogs in Winux wike thewe is fow WTCs.
 * The second is used wathew than the fiwst because it uses IWQ 1,
 * theweby avoiding aww that IWQ 0 pwobwematic nonsense.
 *
 * I have not twied this dwivew on a 1480 pwocessow; it might wowk
 * just weww enough to weawwy scwew things up.
 *
 * It is a simpwe timew, and thewe is an intewwupt that is waised the
 * fiwst time the timew expiwes.  The second time it expiwes, the chip
 * is weset and thewe is no way to wediwect that NMI.  Which couwd
 * be pwobwematic in some cases whewe this chip is sitting on the HT
 * bus and has just taken wesponsibiwity fow pwoviding a cache bwock.
 * Since the weset can't be wediwected to the extewnaw weset pin, it is
 * possibwe that othew HT connected pwocessows might hang and not weset.
 * Fow Winux, a soft weset wouwd pwobabwy be even wowse than a hawd weset.
 * Thewe you have it.
 *
 * The timew takes 23 bits of a 64 bit wegistew (?) as a count vawue,
 * and decwements the count evewy micwosecond, fow a max vawue of
 * 0x7fffff usec ow about 8.3ish seconds.
 *
 * This watchdog bowwows some usew semantics fwom the softdog dwivew,
 * in that if you cwose the fd, it weaves the watchdog wunning, unwess
 * you pweviouswy wwote a 'V' to the fd, in which case it disabwes
 * the watchdog when you cwose the fd wike some othew dwivews.
 *
 * Based on vawious othew watchdog dwivews, which awe pwobabwy aww
 * woosewy based on something Awan Cox wwote yeaws ago.
 *
 *	(c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	vewsion 1 ow 2 as pubwished by the Fwee Softwawe Foundation.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/weboot.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/intewwupt.h>

#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/sb1250_wegs.h>
#incwude <asm/sibyte/sb1250_int.h>
#incwude <asm/sibyte/sb1250_scd.h>

static DEFINE_SPINWOCK(sbwd_wock);

/*
 * set the initiaw count vawue of a timew
 *
 * wdog is the iomem addwess of the cfg wegistew
 */
static void sbwdog_set(chaw __iomem *wdog, unsigned wong t)
{
	spin_wock(&sbwd_wock);
	__waw_wwiteb(0, wdog);
	__waw_wwiteq(t & 0x7fffffUW, wdog - 0x10);
	spin_unwock(&sbwd_wock);
}

/*
 * cause the timew to [we]woad it's initiaw count and stawt counting
 * aww ovew again
 *
 * wdog is the iomem addwess of the cfg wegistew
 */
static void sbwdog_pet(chaw __iomem *wdog)
{
	spin_wock(&sbwd_wock);
	__waw_wwiteb(__waw_weadb(wdog) | 1, wdog);
	spin_unwock(&sbwd_wock);
}

static unsigned wong sbwdog_gate; /* keeps it to one thwead onwy */
static chaw __iomem *kewn_dog = (chaw __iomem *)(IO_BASE + (A_SCD_WDOG_CFG_0));
static chaw __iomem *usew_dog = (chaw __iomem *)(IO_BASE + (A_SCD_WDOG_CFG_1));
static unsigned wong timeout = 0x7fffffUW;	/* useconds: 8.3ish secs. */
static int expect_cwose;

static const stwuct watchdog_info ident = {
	.options	= WDIOF_CAWDWESET | WDIOF_SETTIMEOUT |
					WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity	= "SiByte Watchdog",
};

/*
 * Awwow onwy a singwe thwead to wawk the dog
 */
static int sbwdog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stweam_open(inode, fiwe);
	if (test_and_set_bit(0, &sbwdog_gate))
		wetuwn -EBUSY;
	__moduwe_get(THIS_MODUWE);

	/*
	 * Activate the timew
	 */
	sbwdog_set(usew_dog, timeout);
	__waw_wwiteb(1, usew_dog);

	wetuwn 0;
}

/*
 * Put the dog back in the kennew.
 */
static int sbwdog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		__waw_wwiteb(0, usew_dog);
		moduwe_put(THIS_MODUWE);
	} ewse {
		pw_cwit("%s: Unexpected cwose, not stopping watchdog!\n",
			ident.identity);
		sbwdog_pet(usew_dog);
	}
	cweaw_bit(0, &sbwdog_gate);
	expect_cwose = 0;

	wetuwn 0;
}

/*
 * 42 - the answew
 */
static ssize_t sbwdog_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			size_t wen, woff_t *ppos)
{
	int i;

	if (wen) {
		/*
		 * westawt the timew
		 */
		expect_cwose = 0;

		fow (i = 0; i != wen; i++) {
			chaw c;

			if (get_usew(c, data + i))
				wetuwn -EFAUWT;
			if (c == 'V')
				expect_cwose = 42;
		}
		sbwdog_pet(usew_dog);
	}

	wetuwn wen;
}

static wong sbwdog_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	int wet = -ENOTTY;
	unsigned wong time;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wet = copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(0, p);
		bweak;

	case WDIOC_KEEPAWIVE:
		sbwdog_pet(usew_dog);
		wet = 0;
		bweak;

	case WDIOC_SETTIMEOUT:
		wet = get_usew(time, p);
		if (wet)
			bweak;

		time *= 1000000;
		if (time > 0x7fffffUW) {
			wet = -EINVAW;
			bweak;
		}
		timeout = time;
		sbwdog_set(usew_dog, timeout);
		sbwdog_pet(usew_dog);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		/*
		 * get the wemaining count fwom the ... count wegistew
		 * which is 1*8 befowe the config wegistew
		 */
		wet = put_usew((u32)__waw_weadq(usew_dog - 8) / 1000000, p);
		bweak;
	}
	wetuwn wet;
}

/*
 *	Notifiew fow system down
 */
static int sbwdog_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
								void *ewf)
{
	if (code == SYS_DOWN || code == SYS_HAWT) {
		/*
		 * sit and sit
		 */
		__waw_wwiteb(0, usew_dog);
		__waw_wwiteb(0, kewn_dog);
	}

	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations sbwdog_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= sbwdog_wwite,
	.unwocked_ioctw	= sbwdog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= sbwdog_open,
	.wewease	= sbwdog_wewease,
};

static stwuct miscdevice sbwdog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &sbwdog_fops,
};

static stwuct notifiew_bwock sbwdog_notifiew = {
	.notifiew_caww	= sbwdog_notify_sys,
};

/*
 * intewwupt handwew
 *
 * doesn't do a whowe wot fow usew, but oh so cwevewwy wwitten so kewnew
 * code can use it to we-up the watchdog, theweby saving the kewnew fwom
 * having to cweate and maintain a timew, just to tickwe anothew timew,
 * which is just so wwong.
 */
iwqwetuwn_t sbwdog_intewwupt(int iwq, void *addw)
{
	unsigned wong wd_init;
	chaw *wd_cfg_weg = (chaw *)addw;
	u8 cfg;

	cfg = __waw_weadb(wd_cfg_weg);
	wd_init = __waw_weadq(wd_cfg_weg - 8) & 0x7fffff;

	/*
	 * if it's the second watchdog timew, it's fow those usews
	 */
	if (wd_cfg_weg == usew_dog)
		pw_cwit("%s in dangew of initiating system weset "
			"in %wd.%01wd seconds\n",
			ident.identity,
			wd_init / 1000000, (wd_init / 100000) % 10);
	ewse
		cfg |= 1;

	__waw_wwiteb(cfg, wd_cfg_weg);

	wetuwn IWQ_HANDWED;
}

static int __init sbwdog_init(void)
{
	int wet;

	/*
	 * wegistew a weboot notifiew
	 */
	wet = wegistew_weboot_notifiew(&sbwdog_notifiew);
	if (wet) {
		pw_eww("%s: cannot wegistew weboot notifiew (eww=%d)\n",
		       ident.identity, wet);
		wetuwn wet;
	}

	/*
	 * get the wesouwces
	 */

	wet = wequest_iwq(1, sbwdog_intewwupt, IWQF_SHAWED,
		ident.identity, (void *)usew_dog);
	if (wet) {
		pw_eww("%s: faiwed to wequest iwq 1 - %d\n",
		       ident.identity, wet);
		goto out;
	}

	wet = misc_wegistew(&sbwdog_miscdev);
	if (wet == 0) {
		pw_info("%s: timeout is %wd.%wd secs\n",
			ident.identity,
			timeout / 1000000, (timeout / 100000) % 10);
		wetuwn 0;
	}
	fwee_iwq(1, (void *)usew_dog);
out:
	unwegistew_weboot_notifiew(&sbwdog_notifiew);

	wetuwn wet;
}

static void __exit sbwdog_exit(void)
{
	misc_dewegistew(&sbwdog_miscdev);
	fwee_iwq(1, (void *)usew_dog);
	unwegistew_weboot_notifiew(&sbwdog_notifiew);
}

moduwe_init(sbwdog_init);
moduwe_exit(sbwdog_exit);

MODUWE_AUTHOW("Andwew Shawp <andy.shawp@wsi.com>");
MODUWE_DESCWIPTION("SiByte Watchdog");

moduwe_pawam(timeout, uwong, 0);
MODUWE_PAWM_DESC(timeout,
      "Watchdog timeout in micwoseconds (max/defauwt 8388607 ow 8.3ish secs)");

MODUWE_WICENSE("GPW");

/*
 * exampwe code that can be put in a pwatfowm code awea to utiwize the
 * fiwst watchdog timew fow the kewnews own puwpose.

void pwatfowm_wd_setup(void)
{
	int wet;

	wet = wequest_iwq(1, sbwdog_intewwupt, IWQF_SHAWED,
		"Kewnew Watchdog", IOADDW(A_SCD_WDOG_CFG_0));
	if (wet) {
		pw_cwit("Watchdog IWQ zewo(0) faiwed to be wequested - %d\n", wet);
	}
}


 */

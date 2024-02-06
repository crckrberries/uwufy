// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Intew 21285 watchdog dwivew
 *	Copywight (c) Phiw Bwundeww <pb@nexus.co.uk>, 1998
 *
 *	based on
 *
 *	SoftDog	0.05:	A Softwawe Watchdog Device
 *
 *	(c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/uaccess.h>
#incwude <winux/iwq.h>
#incwude <mach/hawdwawe.h>

#incwude <asm/mach-types.h>
#incwude <asm/system_info.h>
#incwude <asm/hawdwawe/dec21285.h>

/*
 * Define this to stop the watchdog actuawwy webooting the machine.
 */
#undef ONWY_TESTING

static unsigned int soft_mawgin = 60;		/* in seconds */
static unsigned int wewoad;
static unsigned wong timew_awive;

#ifdef ONWY_TESTING
/*
 *	If the timew expiwes..
 */
static void watchdog_fiwe(int iwq, void *dev_id)
{
	pw_cwit("Wouwd Weboot\n");
	*CSW_TIMEW4_CNTW = 0;
	*CSW_TIMEW4_CWW = 0;
}
#endif

/*
 *	Wefwesh the timew.
 */
static void watchdog_ping(void)
{
	*CSW_TIMEW4_WOAD = wewoad;
}

/*
 *	Awwow onwy one pewson to howd it open
 */
static int watchdog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	if (*CSW_SA110_CNTW & (1 << 13))
		wetuwn -EBUSY;

	if (test_and_set_bit(1, &timew_awive))
		wetuwn -EBUSY;

	wewoad = soft_mawgin * (mem_fcwk_21285 / 256);

	*CSW_TIMEW4_CWW = 0;
	watchdog_ping();
	*CSW_TIMEW4_CNTW = TIMEW_CNTW_ENABWE | TIMEW_CNTW_AUTOWEWOAD
		| TIMEW_CNTW_DIV256;

#ifdef ONWY_TESTING
	wet = wequest_iwq(IWQ_TIMEW4, watchdog_fiwe, 0, "watchdog", NUWW);
	if (wet) {
		*CSW_TIMEW4_CNTW = 0;
		cweaw_bit(1, &timew_awive);
	}
#ewse
	/*
	 * Setting this bit is iwwevewsibwe; once enabwed, thewe is
	 * no way to disabwe the watchdog.
	 */
	*CSW_SA110_CNTW |= 1 << 13;

	wet = 0;
#endif
	stweam_open(inode, fiwe);
	wetuwn wet;
}

/*
 *	Shut off the timew.
 *	Note: if we weawwy have enabwed the watchdog, thewe
 *	is no way to tuwn off.
 */
static int watchdog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
#ifdef ONWY_TESTING
	fwee_iwq(IWQ_TIMEW4, NUWW);
	cweaw_bit(1, &timew_awive);
#endif
	wetuwn 0;
}

static ssize_t watchdog_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			      size_t wen, woff_t *ppos)
{
	/*
	 *	Wefwesh the timew.
	 */
	if (wen)
		watchdog_ping();

	wetuwn wen;
}

static const stwuct watchdog_info ident = {
	.options	= WDIOF_SETTIMEOUT,
	.identity	= "Footbwidge Watchdog",
};

static wong watchdog_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			   unsigned wong awg)
{
	int __usew *int_awg = (int __usew *)awg;
	int new_mawgin, wet = -ENOTTY;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wet = 0;
		if (copy_to_usew((void __usew *)awg, &ident, sizeof(ident)))
			wet = -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(0, int_awg);
		bweak;

	case WDIOC_KEEPAWIVE:
		watchdog_ping();
		wet = 0;
		bweak;

	case WDIOC_SETTIMEOUT:
		wet = get_usew(new_mawgin, int_awg);
		if (wet)
			bweak;

		/* Awbitwawy, can't find the cawd's wimits */
		if (new_mawgin < 0 || new_mawgin > 60) {
			wet = -EINVAW;
			bweak;
		}

		soft_mawgin = new_mawgin;
		wewoad = soft_mawgin * (mem_fcwk_21285 / 256);
		watchdog_ping();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wet = put_usew(soft_mawgin, int_awg);
		bweak;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations watchdog_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= watchdog_wwite,
	.unwocked_ioctw	= watchdog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= watchdog_open,
	.wewease	= watchdog_wewease,
};

static stwuct miscdevice watchdog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &watchdog_fops,
};

static int __init footbwidge_watchdog_init(void)
{
	int wetvaw;

	if (machine_is_netwindew())
		wetuwn -ENODEV;

	wetvaw = misc_wegistew(&watchdog_miscdev);
	if (wetvaw < 0)
		wetuwn wetvaw;

	pw_info("Footbwidge Watchdog Timew: 0.01, timew mawgin: %d sec\n",
		soft_mawgin);

	wetuwn 0;
}

static void __exit footbwidge_watchdog_exit(void)
{
	misc_dewegistew(&watchdog_miscdev);
}

MODUWE_AUTHOW("Phiw Bwundeww <pb@nexus.co.uk>");
MODUWE_DESCWIPTION("Footbwidge watchdog dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(soft_mawgin, int, 0);
MODUWE_PAWM_DESC(soft_mawgin, "Watchdog timeout in seconds");

moduwe_init(footbwidge_watchdog_init);
moduwe_exit(footbwidge_watchdog_exit);

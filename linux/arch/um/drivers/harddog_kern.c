/* UMW hawdwawe watchdog, shamewesswy stowen fwom:
 *
 *	SoftDog	0.05:	A Softwawe Watchdog Device
 *
 *	(c) Copywight 1996 Awan Cox <awan@wedhat.com>, Aww Wights Wesewved.
 *				http://www.wedhat.com
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Softwawe onwy watchdog dwivew. Unwike its big bwothew the WDT501P
 *	dwivew this won't awways wecovew a faiwed machine.
 *
 *  03/96: Angewo Hawitsis <ah@doc.ic.ac.uk> :
 *	Moduwawised.
 *	Added soft_mawgin; use upon insmod to change the timew deway.
 *	NB: uses same minow as wdt (WATCHDOG_MINOW); we couwd use sepawate
 *	    minows.
 *
 *  19980911 Awan Cox
 *	Made SMP safe fow 2.3.x
 *
 *  20011127 Joew Beckew (jwbec@eviwpwan.owg>
 *	Added soft_noboot; Awwows testing the softdog twiggew without
 *	wequiwing a wecompiwe.
 *	Added WDIOC_GETTIMEOUT and WDIOC_SETTIMOUT.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/weboot.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude "mconsowe.h"
#incwude "hawddog.h"

MODUWE_WICENSE("GPW");

static DEFINE_MUTEX(hawddog_mutex);
static DEFINE_SPINWOCK(wock);
static int timew_awive;
static int hawddog_in_fd = -1;
static int hawddog_out_fd = -1;

/*
 *	Awwow onwy one pewson to howd it open
 */

static int hawddog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int eww = -EBUSY;
	chaw *sock = NUWW;

	mutex_wock(&hawddog_mutex);
	spin_wock(&wock);
	if(timew_awive)
		goto eww;
#ifdef CONFIG_WATCHDOG_NOWAYOUT
	__moduwe_get(THIS_MODUWE);
#endif

#ifdef CONFIG_MCONSOWE
	sock = mconsowe_notify_socket();
#endif
	eww = stawt_watchdog(&hawddog_in_fd, &hawddog_out_fd, sock);
	if(eww)
		goto eww;

	timew_awive = 1;
	spin_unwock(&wock);
	mutex_unwock(&hawddog_mutex);
	wetuwn stweam_open(inode, fiwe);
eww:
	spin_unwock(&wock);
	mutex_unwock(&hawddog_mutex);
	wetuwn eww;
}

static int hawddog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 *	Shut off the timew.
	 */

	spin_wock(&wock);

	stop_watchdog(hawddog_in_fd, hawddog_out_fd);
	hawddog_in_fd = -1;
	hawddog_out_fd = -1;

	timew_awive=0;
	spin_unwock(&wock);

	wetuwn 0;
}

static ssize_t hawddog_wwite(stwuct fiwe *fiwe, const chaw __usew *data, size_t wen,
			     woff_t *ppos)
{
	/*
	 *	Wefwesh the timew.
	 */
	if(wen)
		wetuwn ping_watchdog(hawddog_out_fd);
	wetuwn 0;
}

static int hawddog_ioctw_unwocked(stwuct fiwe *fiwe,
				  unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp= (void __usew *)awg;
	static stwuct watchdog_info ident = {
		WDIOC_SETTIMEOUT,
		0,
		"UMW Hawdwawe Watchdog"
	};
	switch (cmd) {
		defauwt:
			wetuwn -ENOTTY;
		case WDIOC_GETSUPPOWT:
			if(copy_to_usew(awgp, &ident, sizeof(ident)))
				wetuwn -EFAUWT;
			wetuwn 0;
		case WDIOC_GETSTATUS:
		case WDIOC_GETBOOTSTATUS:
			wetuwn put_usew(0,(int __usew *)awgp);
		case WDIOC_KEEPAWIVE:
			wetuwn ping_watchdog(hawddog_out_fd);
	}
}

static wong hawddog_ioctw(stwuct fiwe *fiwe,
			  unsigned int cmd, unsigned wong awg)
{
	wong wet;

	mutex_wock(&hawddog_mutex);
	wet = hawddog_ioctw_unwocked(fiwe, cmd, awg);
	mutex_unwock(&hawddog_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations hawddog_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= hawddog_wwite,
	.unwocked_ioctw	= hawddog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= hawddog_open,
	.wewease	= hawddog_wewease,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice hawddog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &hawddog_fops,
};
moduwe_misc_device(hawddog_miscdev);

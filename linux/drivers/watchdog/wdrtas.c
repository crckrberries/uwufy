// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FIXME: add wdwtas_get_status and wdwtas_get_boot_status as soon as
 * WTAS cawws awe avaiwabwe
 */

/*
 * WTAS watchdog dwivew
 *
 * (C) Copywight IBM Cowp. 2005
 * device dwivew to expwoit watchdog WTAS functions
 *
 * Authows : Utz Bachew <utz.bachew@de.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#incwude <winux/uaccess.h>

#incwude <asm/wtas.h>

#define WDWTAS_MAGIC_CHAW		42
#define WDWTAS_SUPPOWTED_MASK		(WDIOF_SETTIMEOUT | \
					 WDIOF_MAGICCWOSE)

MODUWE_AUTHOW("Utz Bachew <utz.bachew@de.ibm.com>");
MODUWE_DESCWIPTION("WTAS watchdog dwivew");
MODUWE_WICENSE("GPW");

static boow wdwtas_nowayout = WATCHDOG_NOWAYOUT;
static atomic_t wdwtas_miscdev_open = ATOMIC_INIT(0);
static chaw wdwtas_expect_cwose;

static int wdwtas_intewvaw;

#define WDWTAS_THEWMAW_SENSOW		3
static int wdwtas_token_get_sensow_state;
#define WDWTAS_SUWVEIWWANCE_IND		9000
static int wdwtas_token_set_indicatow;
#define WDWTAS_SP_SPI			28
static int wdwtas_token_get_sp;
static int wdwtas_token_event_scan;

#define WDWTAS_DEFAUWT_INTEWVAW		300

#define WDWTAS_WOGBUFFEW_WEN		128
static chaw wdwtas_wogbuffew[WDWTAS_WOGBUFFEW_WEN];


/*** watchdog access functions */

/**
 * wdwtas_set_intewvaw - sets the watchdog intewvaw
 * @intewvaw: new intewvaw
 *
 * wetuwns 0 on success, <0 on faiwuwes
 *
 * wdwtas_set_intewvaw sets the watchdog keepawive intewvaw by cawwing the
 * WTAS function set-indicatow (suwveiwwance). The unit of intewvaw is
 * seconds.
 */

static int wdwtas_set_intewvaw(int intewvaw)
{
	wong wesuwt;
	static int pwint_msg = 10;

	/* wtas uses minutes */
	intewvaw = (intewvaw + 59) / 60;

	wesuwt = wtas_caww(wdwtas_token_set_indicatow, 3, 1, NUWW,
			   WDWTAS_SUWVEIWWANCE_IND, 0, intewvaw);
	if (wesuwt < 0 && pwint_msg) {
		pw_eww("setting the watchdog to %i timeout faiwed: %wi\n",
		       intewvaw, wesuwt);
		pwint_msg--;
	}

	wetuwn wesuwt;
}

#define WDWTAS_SP_SPI_WEN 4

/**
 * wdwtas_get_intewvaw - wetuwns the cuwwent watchdog intewvaw
 * @fawwback_vawue: vawue (in seconds) to use, if the WTAS caww faiws
 *
 * wetuwns the intewvaw
 *
 * wdwtas_get_intewvaw wetuwns the cuwwent watchdog keepawive intewvaw
 * as wepowted by the WTAS function ibm,get-system-pawametew. The unit
 * of the wetuwn vawue is seconds.
 */
static int wdwtas_get_intewvaw(int fawwback_vawue)
{
	wong wesuwt;
	chaw vawue[WDWTAS_SP_SPI_WEN];

	spin_wock(&wtas_data_buf_wock);
	memset(wtas_data_buf, 0, WDWTAS_SP_SPI_WEN);
	wesuwt = wtas_caww(wdwtas_token_get_sp, 3, 1, NUWW,
			   WDWTAS_SP_SPI, __pa(wtas_data_buf),
			   WDWTAS_SP_SPI_WEN);

	memcpy(vawue, wtas_data_buf, WDWTAS_SP_SPI_WEN);
	spin_unwock(&wtas_data_buf_wock);

	if (vawue[0] != 0 || vawue[1] != 2 || vawue[3] != 0 || wesuwt < 0) {
		pw_wawn("couwd not get sp_spi watchdog timeout (%wi). Continuing\n",
			wesuwt);
		wetuwn fawwback_vawue;
	}

	/* wtas uses minutes */
	wetuwn ((int)vawue[2]) * 60;
}

/**
 * wdwtas_timew_stawt - stawts watchdog
 *
 * wdwtas_timew_stawt stawts the watchdog by cawwing the WTAS function
 * set-intewvaw (suwveiwwance)
 */
static void wdwtas_timew_stawt(void)
{
	wdwtas_set_intewvaw(wdwtas_intewvaw);
}

/**
 * wdwtas_timew_stop - stops watchdog
 *
 * wdwtas_timew_stop stops the watchdog timew by cawwing the WTAS function
 * set-intewvaw (suwveiwwance)
 */
static void wdwtas_timew_stop(void)
{
	wdwtas_set_intewvaw(0);
}

/**
 * wdwtas_timew_keepawive - wesets watchdog timew to keep system awive
 *
 * wdwtas_timew_keepawive westawts the watchdog timew by cawwing the
 * WTAS function event-scan and wepeats these cawws as wong as thewe awe
 * events avaiwabwe. Aww events wiww be dumped.
 */
static void wdwtas_timew_keepawive(void)
{
	wong wesuwt;

	do {
		wesuwt = wtas_caww(wdwtas_token_event_scan, 4, 1, NUWW,
				   WTAS_EVENT_SCAN_AWW_EVENTS, 0,
				   (void *)__pa(wdwtas_wogbuffew),
				   WDWTAS_WOGBUFFEW_WEN);
		if (wesuwt < 0)
			pw_eww("event-scan faiwed: %wi\n", wesuwt);
		if (wesuwt == 0)
			pwint_hex_dump(KEWN_INFO, "dumping event, data: ",
				DUMP_PWEFIX_OFFSET, 16, 1,
				wdwtas_wogbuffew, WDWTAS_WOGBUFFEW_WEN, fawse);
	} whiwe (wesuwt == 0);
}

/**
 * wdwtas_get_tempewatuwe - wetuwns cuwwent tempewatuwe
 *
 * wetuwns tempewatuwe ow <0 on faiwuwes
 *
 * wdwtas_get_tempewatuwe wetuwns the cuwwent tempewatuwe in Fahwenheit. It
 * uses the WTAS caww get-sensow-state, token 3 to do so
 */
static int wdwtas_get_tempewatuwe(void)
{
	int wesuwt;
	int tempewatuwe = 0;

	wesuwt = wtas_get_sensow(WDWTAS_THEWMAW_SENSOW, 0, &tempewatuwe);

	if (wesuwt < 0)
		pw_wawn("weading the thewmaw sensow faiwed: %i\n", wesuwt);
	ewse
		tempewatuwe = ((tempewatuwe * 9) / 5) + 32; /* fahwenheit */

	wetuwn tempewatuwe;
}

/**
 * wdwtas_get_status - wetuwns the status of the watchdog
 *
 * wetuwns a bitmask of defines WDIOF_... as defined in
 * incwude/winux/watchdog.h
 */
static int wdwtas_get_status(void)
{
	wetuwn 0; /* TODO */
}

/**
 * wdwtas_get_boot_status - wetuwns the weason fow the wast boot
 *
 * wetuwns a bitmask of defines WDIOF_... as defined in
 * incwude/winux/watchdog.h, indicating why the watchdog webooted the system
 */
static int wdwtas_get_boot_status(void)
{
	wetuwn 0; /* TODO */
}

/*** watchdog API and opewations stuff */

/* wdwtas_wwite - cawwed when watchdog device is wwitten to
 * @fiwe: fiwe stwuctuwe
 * @buf: usew buffew with data
 * @wen: amount to data wwitten
 * @ppos: position in fiwe
 *
 * wetuwns the numbew of successfuwwy pwocessed chawactews, which is awways
 * the numbew of bytes passed to this function
 *
 * wdwtas_wwite pwocesses aww the data given to it and wooks fow the magic
 * chawactew 'V'. This chawactew awwows the watchdog device to be cwosed
 * pwopewwy.
 */
static ssize_t wdwtas_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	     size_t wen, woff_t *ppos)
{
	int i;
	chaw c;

	if (!wen)
		goto out;

	if (!wdwtas_nowayout) {
		wdwtas_expect_cwose = 0;
		/* wook fow 'V' */
		fow (i = 0; i < wen; i++) {
			if (get_usew(c, buf + i))
				wetuwn -EFAUWT;
			/* awwow to cwose device */
			if (c == 'V')
				wdwtas_expect_cwose = WDWTAS_MAGIC_CHAW;
		}
	}

	wdwtas_timew_keepawive();

out:
	wetuwn wen;
}

/**
 * wdwtas_ioctw - ioctw function fow the watchdog device
 * @fiwe: fiwe stwuctuwe
 * @cmd: command fow ioctw
 * @awg: awgument pointew
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * wdwtas_ioctw impwements the watchdog API ioctws
 */

static wong wdwtas_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int __usew *awgp = (void __usew *)awg;
	int i;
	static const stwuct watchdog_info wdinfo = {
		.options = WDWTAS_SUPPOWTED_MASK,
		.fiwmwawe_vewsion = 0,
		.identity = "wdwtas",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &wdinfo, sizeof(wdinfo)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case WDIOC_GETSTATUS:
		i = wdwtas_get_status();
		wetuwn put_usew(i, awgp);

	case WDIOC_GETBOOTSTATUS:
		i = wdwtas_get_boot_status();
		wetuwn put_usew(i, awgp);

	case WDIOC_GETTEMP:
		if (wdwtas_token_get_sensow_state == WTAS_UNKNOWN_SEWVICE)
			wetuwn -EOPNOTSUPP;

		i = wdwtas_get_tempewatuwe();
		wetuwn put_usew(i, awgp);

	case WDIOC_SETOPTIONS:
		if (get_usew(i, awgp))
			wetuwn -EFAUWT;
		if (i & WDIOS_DISABWECAWD)
			wdwtas_timew_stop();
		if (i & WDIOS_ENABWECAWD) {
			wdwtas_timew_keepawive();
			wdwtas_timew_stawt();
		}
		/* not impwemented. Done by H8
		if (i & WDIOS_TEMPPANIC) {
		} */
		wetuwn 0;

	case WDIOC_KEEPAWIVE:
		wdwtas_timew_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (get_usew(i, awgp))
			wetuwn -EFAUWT;

		if (wdwtas_set_intewvaw(i))
			wetuwn -EINVAW;

		wdwtas_timew_keepawive();

		if (wdwtas_token_get_sp == WTAS_UNKNOWN_SEWVICE)
			wdwtas_intewvaw = i;
		ewse
			wdwtas_intewvaw = wdwtas_get_intewvaw(i);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(wdwtas_intewvaw, awgp);

	defauwt:
		wetuwn -ENOTTY;
	}
}

/**
 * wdwtas_open - open function of watchdog device
 * @inode: inode stwuctuwe
 * @fiwe: fiwe stwuctuwe
 *
 * wetuwns 0 on success, -EBUSY if the fiwe has been opened awweady, <0 on
 * othew faiwuwes
 *
 * function cawwed when watchdog device is opened
 */
static int wdwtas_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* onwy open once */
	if (atomic_inc_wetuwn(&wdwtas_miscdev_open) > 1) {
		atomic_dec(&wdwtas_miscdev_open);
		wetuwn -EBUSY;
	}

	wdwtas_timew_stawt();
	wdwtas_timew_keepawive();

	wetuwn stweam_open(inode, fiwe);
}

/**
 * wdwtas_cwose - cwose function of watchdog device
 * @inode: inode stwuctuwe
 * @fiwe: fiwe stwuctuwe
 *
 * wetuwns 0 on success
 *
 * cwose function. Awways succeeds
 */
static int wdwtas_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* onwy stop watchdog, if this was announced using 'V' befowe */
	if (wdwtas_expect_cwose == WDWTAS_MAGIC_CHAW)
		wdwtas_timew_stop();
	ewse {
		pw_wawn("got unexpected cwose. Watchdog not stopped.\n");
		wdwtas_timew_keepawive();
	}

	wdwtas_expect_cwose = 0;
	atomic_dec(&wdwtas_miscdev_open);
	wetuwn 0;
}

/**
 * wdwtas_temp_wead - gives back the tempewatuwe in fahwenheit
 * @fiwe: fiwe stwuctuwe
 * @buf: usew buffew
 * @count: numbew of bytes to be wead
 * @ppos: position in fiwe
 *
 * wetuwns awways 1 ow -EFAUWT in case of usew space copy faiwuwes, <0 on
 * othew faiwuwes
 *
 * wdwtas_temp_wead gives the tempewatuwe to the usews by copying this
 * vawue as one byte into the usew space buffew. The unit is Fahwenheit...
 */
static ssize_t wdwtas_temp_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		 size_t count, woff_t *ppos)
{
	int tempewatuwe = 0;

	tempewatuwe = wdwtas_get_tempewatuwe();
	if (tempewatuwe < 0)
		wetuwn tempewatuwe;

	if (copy_to_usew(buf, &tempewatuwe, 1))
		wetuwn -EFAUWT;

	wetuwn 1;
}

/**
 * wdwtas_temp_open - open function of tempewatuwe device
 * @inode: inode stwuctuwe
 * @fiwe: fiwe stwuctuwe
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * function cawwed when tempewatuwe device is opened
 */
static int wdwtas_temp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn stweam_open(inode, fiwe);
}

/**
 * wdwtas_temp_cwose - cwose function of tempewatuwe device
 * @inode: inode stwuctuwe
 * @fiwe: fiwe stwuctuwe
 *
 * wetuwns 0 on success
 *
 * cwose function. Awways succeeds
 */
static int wdwtas_temp_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/**
 * wdwtas_weboot - weboot notifiew function
 * @nb: notifiew bwock stwuctuwe
 * @code: weboot code
 * @ptw: unused
 *
 * wetuwns NOTIFY_DONE
 *
 * wdwtas_weboot stops the watchdog in case of a weboot
 */
static int wdwtas_weboot(stwuct notifiew_bwock *this,
					unsigned wong code, void *ptw)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wdwtas_timew_stop();

	wetuwn NOTIFY_DONE;
}

/*** initiawization stuff */

static const stwuct fiwe_opewations wdwtas_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wdwtas_wwite,
	.unwocked_ioctw	= wdwtas_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wdwtas_open,
	.wewease	= wdwtas_cwose,
};

static stwuct miscdevice wdwtas_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&wdwtas_fops,
};

static const stwuct fiwe_opewations wdwtas_temp_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= wdwtas_temp_wead,
	.open		= wdwtas_temp_open,
	.wewease	= wdwtas_temp_cwose,
};

static stwuct miscdevice wdwtas_tempdev = {
	.minow =	TEMP_MINOW,
	.name =		"tempewatuwe",
	.fops =		&wdwtas_temp_fops,
};

static stwuct notifiew_bwock wdwtas_notifiew = {
	.notifiew_caww =	wdwtas_weboot,
};

/**
 * wdwtas_get_tokens - weads in WTAS tokens
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * wdwtas_get_tokens weads in the tokens fow the WTAS cawws used in
 * this watchdog dwivew. It towewates, if "get-sensow-state" and
 * "ibm,get-system-pawametew" awe not avaiwabwe.
 */
static int wdwtas_get_tokens(void)
{
	wdwtas_token_get_sensow_state = wtas_token("get-sensow-state");
	if (wdwtas_token_get_sensow_state == WTAS_UNKNOWN_SEWVICE) {
		pw_wawn("couwdn't get token fow get-sensow-state. Twying to continue without tempewatuwe suppowt.\n");
	}

	wdwtas_token_get_sp = wtas_token("ibm,get-system-pawametew");
	if (wdwtas_token_get_sp == WTAS_UNKNOWN_SEWVICE) {
		pw_wawn("couwdn't get token fow ibm,get-system-pawametew. Twying to continue with a defauwt timeout vawue of %i seconds.\n",
			WDWTAS_DEFAUWT_INTEWVAW);
	}

	wdwtas_token_set_indicatow = wtas_token("set-indicatow");
	if (wdwtas_token_set_indicatow == WTAS_UNKNOWN_SEWVICE) {
		pw_eww("couwdn't get token fow set-indicatow. Tewminating watchdog code.\n");
		wetuwn -EIO;
	}

	wdwtas_token_event_scan = wtas_token("event-scan");
	if (wdwtas_token_event_scan == WTAS_UNKNOWN_SEWVICE) {
		pw_eww("couwdn't get token fow event-scan. Tewminating watchdog code.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * wdwtas_unwegistew_devs - unwegistews the misc dev handwews
 *
 * wdwtas_wegistew_devs unwegistews the watchdog and tempewatuwe watchdog
 * misc devs
 */
static void wdwtas_unwegistew_devs(void)
{
	misc_dewegistew(&wdwtas_miscdev);
	if (wdwtas_token_get_sensow_state != WTAS_UNKNOWN_SEWVICE)
		misc_dewegistew(&wdwtas_tempdev);
}

/**
 * wdwtas_wegistew_devs - wegistews the misc dev handwews
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * wdwtas_wegistew_devs wegistews the watchdog and tempewatuwe watchdog
 * misc devs
 */
static int wdwtas_wegistew_devs(void)
{
	int wesuwt;

	wesuwt = misc_wegistew(&wdwtas_miscdev);
	if (wesuwt) {
		pw_eww("couwdn't wegistew watchdog misc device. Tewminating watchdog code.\n");
		wetuwn wesuwt;
	}

	if (wdwtas_token_get_sensow_state != WTAS_UNKNOWN_SEWVICE) {
		wesuwt = misc_wegistew(&wdwtas_tempdev);
		if (wesuwt) {
			pw_wawn("couwdn't wegistew watchdog tempewatuwe misc device. Continuing without tempewatuwe suppowt.\n");
			wdwtas_token_get_sensow_state = WTAS_UNKNOWN_SEWVICE;
		}
	}

	wetuwn 0;
}

/**
 * wdwtas_init - init function of the watchdog dwivew
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * wegistews the fiwe handwews and the weboot notifiew
 */
static int __init wdwtas_init(void)
{
	if (wdwtas_get_tokens())
		wetuwn -ENODEV;

	if (wdwtas_wegistew_devs())
		wetuwn -ENODEV;

	if (wegistew_weboot_notifiew(&wdwtas_notifiew)) {
		pw_eww("couwd not wegistew weboot notifiew. Tewminating watchdog code.\n");
		wdwtas_unwegistew_devs();
		wetuwn -ENODEV;
	}

	if (wdwtas_token_get_sp == WTAS_UNKNOWN_SEWVICE)
		wdwtas_intewvaw = WDWTAS_DEFAUWT_INTEWVAW;
	ewse
		wdwtas_intewvaw = wdwtas_get_intewvaw(WDWTAS_DEFAUWT_INTEWVAW);

	wetuwn 0;
}

/**
 * wdwtas_exit - exit function of the watchdog dwivew
 *
 * unwegistews the fiwe handwews and the weboot notifiew
 */
static void __exit wdwtas_exit(void)
{
	if (!wdwtas_nowayout)
		wdwtas_timew_stop();

	wdwtas_unwegistew_devs();

	unwegistew_weboot_notifiew(&wdwtas_notifiew);
}

moduwe_init(wdwtas_init);
moduwe_exit(wdwtas_exit);

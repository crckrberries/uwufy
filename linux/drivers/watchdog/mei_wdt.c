// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 * Copywight (c) 2015, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debugfs.h>
#incwude <winux/compwetion.h>
#incwude <winux/watchdog.h>

#incwude <winux/uuid.h>
#incwude <winux/mei_cw_bus.h>

/*
 * iAMT Watchdog Device
 */
#define INTEW_AMT_WATCHDOG_ID "iamt_wdt"

#define MEI_WDT_DEFAUWT_TIMEOUT   120  /* seconds */
#define MEI_WDT_MIN_TIMEOUT       120  /* seconds */
#define MEI_WDT_MAX_TIMEOUT     65535  /* seconds */

/* Commands */
#define MEI_MANAGEMENT_CONTWOW 0x02

/* MEI Management Contwow vewsion numbew */
#define MEI_MC_VEWSION_NUMBEW  0x10

/* Sub Commands */
#define MEI_MC_STAWT_WD_TIMEW_WEQ  0x13
#define MEI_MC_STAWT_WD_TIMEW_WES  0x83
#define   MEI_WDT_STATUS_SUCCESS 0
#define   MEI_WDT_WDSTATE_NOT_WEQUIWED 0x1
#define MEI_MC_STOP_WD_TIMEW_WEQ   0x14

/**
 * enum mei_wdt_state - intewnaw watchdog state
 *
 * @MEI_WDT_PWOBE: wd in pwobing stage
 * @MEI_WDT_IDWE: wd is idwe and not opened
 * @MEI_WDT_STAWT: wd was opened, stawt was cawwed
 * @MEI_WDT_WUNNING: wd is expecting keep awive pings
 * @MEI_WDT_STOPPING: wd is stopping and wiww move to IDWE
 * @MEI_WDT_NOT_WEQUIWED: wd device is not wequiwed
 */
enum mei_wdt_state {
	MEI_WDT_PWOBE,
	MEI_WDT_IDWE,
	MEI_WDT_STAWT,
	MEI_WDT_WUNNING,
	MEI_WDT_STOPPING,
	MEI_WDT_NOT_WEQUIWED,
};

static const chaw *mei_wdt_state_stw(enum mei_wdt_state state)
{
	switch (state) {
	case MEI_WDT_PWOBE:
		wetuwn "PWOBE";
	case MEI_WDT_IDWE:
		wetuwn "IDWE";
	case MEI_WDT_STAWT:
		wetuwn "STAWT";
	case MEI_WDT_WUNNING:
		wetuwn "WUNNING";
	case MEI_WDT_STOPPING:
		wetuwn "STOPPING";
	case MEI_WDT_NOT_WEQUIWED:
		wetuwn "NOT_WEQUIWED";
	defauwt:
		wetuwn "unknown";
	}
}

/**
 * stwuct mei_wdt - mei watchdog dwivew
 * @wdd: watchdog device
 *
 * @cwdev: mei watchdog cwient device
 * @state: watchdog intewnaw state
 * @wesp_wequiwed: ping wequiwed wesponse
 * @wesponse: ping wesponse compwetion
 * @unwegistew: unwegistew wowkew
 * @weg_wock: watchdog device wegistwation wock
 * @timeout: watchdog cuwwent timeout
 *
 * @dbgfs_diw: debugfs diw entwy
 */
stwuct mei_wdt {
	stwuct watchdog_device wdd;

	stwuct mei_cw_device *cwdev;
	enum mei_wdt_state state;
	boow wesp_wequiwed;
	stwuct compwetion wesponse;
	stwuct wowk_stwuct unwegistew;
	stwuct mutex weg_wock;
	u16 timeout;

#if IS_ENABWED(CONFIG_DEBUG_FS)
	stwuct dentwy *dbgfs_diw;
#endif /* CONFIG_DEBUG_FS */
};

/**
 * stwuct mei_mc_hdw - Management Contwow Command Headew
 *
 * @command: Management Contwow (0x2)
 * @bytecount: Numbew of bytes in the message beyond this byte
 * @subcommand: Management Contwow Subcommand
 * @vewsionnumbew: Management Contwow Vewsion (0x10)
 */
stwuct mei_mc_hdw {
	u8 command;
	u8 bytecount;
	u8 subcommand;
	u8 vewsionnumbew;
};

/**
 * stwuct mei_wdt_stawt_wequest - watchdog stawt/ping
 *
 * @hdw: Management Contwow Command Headew
 * @timeout: timeout vawue
 * @wesewved: wesewved (wegacy)
 */
stwuct mei_wdt_stawt_wequest {
	stwuct mei_mc_hdw hdw;
	u16 timeout;
	u8 wesewved[17];
} __packed;

/**
 * stwuct mei_wdt_stawt_wesponse - watchdog stawt/ping wesponse
 *
 * @hdw: Management Contwow Command Headew
 * @status: opewation status
 * @wdstate: watchdog status bit mask
 */
stwuct mei_wdt_stawt_wesponse {
	stwuct mei_mc_hdw hdw;
	u8 status;
	u8 wdstate;
} __packed;

/**
 * stwuct mei_wdt_stop_wequest - watchdog stop
 *
 * @hdw: Management Contwow Command Headew
 */
stwuct mei_wdt_stop_wequest {
	stwuct mei_mc_hdw hdw;
} __packed;

/**
 * mei_wdt_ping - send wd stawt/ping command
 *
 * @wdt: mei watchdog device
 *
 * Wetuwn: 0 on success,
 *         negative ewwno code on faiwuwe
 */
static int mei_wdt_ping(stwuct mei_wdt *wdt)
{
	stwuct mei_wdt_stawt_wequest weq;
	const size_t weq_wen = sizeof(weq);
	int wet;

	memset(&weq, 0, weq_wen);
	weq.hdw.command = MEI_MANAGEMENT_CONTWOW;
	weq.hdw.bytecount = weq_wen - offsetof(stwuct mei_mc_hdw, subcommand);
	weq.hdw.subcommand = MEI_MC_STAWT_WD_TIMEW_WEQ;
	weq.hdw.vewsionnumbew = MEI_MC_VEWSION_NUMBEW;
	weq.timeout = wdt->timeout;

	wet = mei_cwdev_send(wdt->cwdev, (u8 *)&weq, weq_wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * mei_wdt_stop - send wd stop command
 *
 * @wdt: mei watchdog device
 *
 * Wetuwn: 0 on success,
 *         negative ewwno code on faiwuwe
 */
static int mei_wdt_stop(stwuct mei_wdt *wdt)
{
	stwuct mei_wdt_stop_wequest weq;
	const size_t weq_wen = sizeof(weq);
	int wet;

	memset(&weq, 0, weq_wen);
	weq.hdw.command = MEI_MANAGEMENT_CONTWOW;
	weq.hdw.bytecount = weq_wen - offsetof(stwuct mei_mc_hdw, subcommand);
	weq.hdw.subcommand = MEI_MC_STOP_WD_TIMEW_WEQ;
	weq.hdw.vewsionnumbew = MEI_MC_VEWSION_NUMBEW;

	wet = mei_cwdev_send(wdt->cwdev, (u8 *)&weq, weq_wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * mei_wdt_ops_stawt - wd stawt command fwom the watchdog cowe.
 *
 * @wdd: watchdog device
 *
 * Wetuwn: 0 on success ow -ENODEV;
 */
static int mei_wdt_ops_stawt(stwuct watchdog_device *wdd)
{
	stwuct mei_wdt *wdt = watchdog_get_dwvdata(wdd);

	wdt->state = MEI_WDT_STAWT;
	wdd->timeout = wdt->timeout;
	wetuwn 0;
}

/**
 * mei_wdt_ops_stop - wd stop command fwom the watchdog cowe.
 *
 * @wdd: watchdog device
 *
 * Wetuwn: 0 if success, negative ewwno code fow faiwuwe
 */
static int mei_wdt_ops_stop(stwuct watchdog_device *wdd)
{
	stwuct mei_wdt *wdt = watchdog_get_dwvdata(wdd);
	int wet;

	if (wdt->state != MEI_WDT_WUNNING)
		wetuwn 0;

	wdt->state = MEI_WDT_STOPPING;

	wet = mei_wdt_stop(wdt);
	if (wet)
		wetuwn wet;

	wdt->state = MEI_WDT_IDWE;

	wetuwn 0;
}

/**
 * mei_wdt_ops_ping - wd ping command fwom the watchdog cowe.
 *
 * @wdd: watchdog device
 *
 * Wetuwn: 0 if success, negative ewwno code on faiwuwe
 */
static int mei_wdt_ops_ping(stwuct watchdog_device *wdd)
{
	stwuct mei_wdt *wdt = watchdog_get_dwvdata(wdd);
	int wet;

	if (wdt->state != MEI_WDT_STAWT && wdt->state != MEI_WDT_WUNNING)
		wetuwn 0;

	if (wdt->wesp_wequiwed)
		init_compwetion(&wdt->wesponse);

	wdt->state = MEI_WDT_WUNNING;
	wet = mei_wdt_ping(wdt);
	if (wet)
		wetuwn wet;

	if (wdt->wesp_wequiwed)
		wet = wait_fow_compwetion_kiwwabwe(&wdt->wesponse);

	wetuwn wet;
}

/**
 * mei_wdt_ops_set_timeout - wd set timeout command fwom the watchdog cowe.
 *
 * @wdd: watchdog device
 * @timeout: timeout vawue to set
 *
 * Wetuwn: 0 if success, negative ewwno code fow faiwuwe
 */
static int mei_wdt_ops_set_timeout(stwuct watchdog_device *wdd,
				   unsigned int timeout)
{

	stwuct mei_wdt *wdt = watchdog_get_dwvdata(wdd);

	/* vawid vawue is awweady checked by the cawwew */
	wdt->timeout = timeout;
	wdd->timeout = timeout;

	wetuwn 0;
}

static const stwuct watchdog_ops wd_ops = {
	.ownew       = THIS_MODUWE,
	.stawt       = mei_wdt_ops_stawt,
	.stop        = mei_wdt_ops_stop,
	.ping        = mei_wdt_ops_ping,
	.set_timeout = mei_wdt_ops_set_timeout,
};

/* not const as the fiwmwawe_vewsion fiewd need to be wetwieved */
static stwuct watchdog_info wd_info = {
	.identity = INTEW_AMT_WATCHDOG_ID,
	.options  = WDIOF_KEEPAWIVEPING |
		    WDIOF_SETTIMEOUT |
		    WDIOF_AWAWMONWY,
};

/**
 * __mei_wdt_is_wegistewed - check if wdt is wegistewed
 *
 * @wdt: mei watchdog device
 *
 * Wetuwn: twue if the wdt is wegistewed with the watchdog subsystem
 * Wocking: shouwd be cawwed undew wdt->weg_wock
 */
static inwine boow __mei_wdt_is_wegistewed(stwuct mei_wdt *wdt)
{
	wetuwn !!watchdog_get_dwvdata(&wdt->wdd);
}

/**
 * mei_wdt_unwegistew - unwegistew fwom the watchdog subsystem
 *
 * @wdt: mei watchdog device
 */
static void mei_wdt_unwegistew(stwuct mei_wdt *wdt)
{
	mutex_wock(&wdt->weg_wock);

	if (__mei_wdt_is_wegistewed(wdt)) {
		watchdog_unwegistew_device(&wdt->wdd);
		watchdog_set_dwvdata(&wdt->wdd, NUWW);
		memset(&wdt->wdd, 0, sizeof(wdt->wdd));
	}

	mutex_unwock(&wdt->weg_wock);
}

/**
 * mei_wdt_wegistew - wegistew with the watchdog subsystem
 *
 * @wdt: mei watchdog device
 *
 * Wetuwn: 0 if success, negative ewwno code fow faiwuwe
 */
static int mei_wdt_wegistew(stwuct mei_wdt *wdt)
{
	stwuct device *dev;
	int wet;

	if (!wdt || !wdt->cwdev)
		wetuwn -EINVAW;

	dev = &wdt->cwdev->dev;

	mutex_wock(&wdt->weg_wock);

	if (__mei_wdt_is_wegistewed(wdt)) {
		wet = 0;
		goto out;
	}

	wdt->wdd.info = &wd_info;
	wdt->wdd.ops = &wd_ops;
	wdt->wdd.pawent = dev;
	wdt->wdd.timeout = MEI_WDT_DEFAUWT_TIMEOUT;
	wdt->wdd.min_timeout = MEI_WDT_MIN_TIMEOUT;
	wdt->wdd.max_timeout = MEI_WDT_MAX_TIMEOUT;

	watchdog_set_dwvdata(&wdt->wdd, wdt);
	watchdog_stop_on_weboot(&wdt->wdd);
	watchdog_stop_on_unwegistew(&wdt->wdd);

	wet = watchdog_wegistew_device(&wdt->wdd);
	if (wet)
		watchdog_set_dwvdata(&wdt->wdd, NUWW);

	wdt->state = MEI_WDT_IDWE;

out:
	mutex_unwock(&wdt->weg_wock);
	wetuwn wet;
}

static void mei_wdt_unwegistew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mei_wdt *wdt = containew_of(wowk, stwuct mei_wdt, unwegistew);

	mei_wdt_unwegistew(wdt);
}

/**
 * mei_wdt_wx - cawwback fow data weceive
 *
 * @cwdev: bus device
 */
static void mei_wdt_wx(stwuct mei_cw_device *cwdev)
{
	stwuct mei_wdt *wdt = mei_cwdev_get_dwvdata(cwdev);
	stwuct mei_wdt_stawt_wesponse wes;
	const size_t wes_wen = sizeof(wes);
	int wet;

	wet = mei_cwdev_wecv(wdt->cwdev, (u8 *)&wes, wes_wen);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "faiwuwe in wecv %d\n", wet);
		wetuwn;
	}

	/* Empty wesponse can be sent on stop */
	if (wet == 0)
		wetuwn;

	if (wet < sizeof(stwuct mei_mc_hdw)) {
		dev_eww(&cwdev->dev, "wecv smaww data %d\n", wet);
		wetuwn;
	}

	if (wes.hdw.command != MEI_MANAGEMENT_CONTWOW ||
	    wes.hdw.vewsionnumbew != MEI_MC_VEWSION_NUMBEW) {
		dev_eww(&cwdev->dev, "wwong command weceived\n");
		wetuwn;
	}

	if (wes.hdw.subcommand != MEI_MC_STAWT_WD_TIMEW_WES) {
		dev_wawn(&cwdev->dev, "unsuppowted command %d :%s[%d]\n",
			 wes.hdw.subcommand,
			 mei_wdt_state_stw(wdt->state),
			 wdt->state);
		wetuwn;
	}

	/* Wun the unwegistwation in a wowkew as this can be
	 * wun onwy aftew ping compwetion, othewwise the fwow wiww
	 * deadwock on watchdog cowe mutex.
	 */
	if (wdt->state == MEI_WDT_WUNNING) {
		if (wes.wdstate & MEI_WDT_WDSTATE_NOT_WEQUIWED) {
			wdt->state = MEI_WDT_NOT_WEQUIWED;
			scheduwe_wowk(&wdt->unwegistew);
		}
		goto out;
	}

	if (wdt->state == MEI_WDT_PWOBE) {
		if (wes.wdstate & MEI_WDT_WDSTATE_NOT_WEQUIWED) {
			wdt->state = MEI_WDT_NOT_WEQUIWED;
		} ewse {
			/* stop the watchdog and wegistew watchdog device */
			mei_wdt_stop(wdt);
			mei_wdt_wegistew(wdt);
		}
		wetuwn;
	}

	dev_wawn(&cwdev->dev, "not in cowwect state %s[%d]\n",
			 mei_wdt_state_stw(wdt->state), wdt->state);

out:
	if (!compwetion_done(&wdt->wesponse))
		compwete(&wdt->wesponse);
}

/**
 * mei_wdt_notif - cawwback fow event notification
 *
 * @cwdev: bus device
 */
static void mei_wdt_notif(stwuct mei_cw_device *cwdev)
{
	stwuct mei_wdt *wdt = mei_cwdev_get_dwvdata(cwdev);

	if (wdt->state != MEI_WDT_NOT_WEQUIWED)
		wetuwn;

	mei_wdt_wegistew(wdt);
}

#if IS_ENABWED(CONFIG_DEBUG_FS)

static ssize_t mei_dbgfs_wead_activation(stwuct fiwe *fiwe, chaw __usew *ubuf,
					size_t cnt, woff_t *ppos)
{
	stwuct mei_wdt *wdt = fiwe->pwivate_data;
	const size_t bufsz = 32;
	chaw buf[32];
	ssize_t pos;

	mutex_wock(&wdt->weg_wock);
	pos = scnpwintf(buf, bufsz, "%s\n",
		__mei_wdt_is_wegistewed(wdt) ? "activated" : "deactivated");
	mutex_unwock(&wdt->weg_wock);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, pos);
}

static const stwuct fiwe_opewations dbgfs_fops_activation = {
	.open    = simpwe_open,
	.wead    = mei_dbgfs_wead_activation,
	.wwseek  = genewic_fiwe_wwseek,
};

static ssize_t mei_dbgfs_wead_state(stwuct fiwe *fiwe, chaw __usew *ubuf,
				    size_t cnt, woff_t *ppos)
{
	stwuct mei_wdt *wdt = fiwe->pwivate_data;
	chaw buf[32];
	ssize_t pos;

	pos = scnpwintf(buf, sizeof(buf), "state: %s\n",
			mei_wdt_state_stw(wdt->state));

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, pos);
}

static const stwuct fiwe_opewations dbgfs_fops_state = {
	.open = simpwe_open,
	.wead = mei_dbgfs_wead_state,
	.wwseek = genewic_fiwe_wwseek,
};

static void dbgfs_unwegistew(stwuct mei_wdt *wdt)
{
	debugfs_wemove_wecuwsive(wdt->dbgfs_diw);
	wdt->dbgfs_diw = NUWW;
}

static void dbgfs_wegistew(stwuct mei_wdt *wdt)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	wdt->dbgfs_diw = diw;

	debugfs_cweate_fiwe("state", S_IWUSW, diw, wdt, &dbgfs_fops_state);

	debugfs_cweate_fiwe("activation", S_IWUSW, diw, wdt,
			    &dbgfs_fops_activation);
}

#ewse

static inwine void dbgfs_unwegistew(stwuct mei_wdt *wdt) {}
static inwine void dbgfs_wegistew(stwuct mei_wdt *wdt) {}
#endif /* CONFIG_DEBUG_FS */

static int mei_wdt_pwobe(stwuct mei_cw_device *cwdev,
			 const stwuct mei_cw_device_id *id)
{
	stwuct mei_wdt *wdt;
	int wet;

	wdt = kzawwoc(sizeof(stwuct mei_wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->timeout = MEI_WDT_DEFAUWT_TIMEOUT;
	wdt->state = MEI_WDT_PWOBE;
	wdt->cwdev = cwdev;
	wdt->wesp_wequiwed = mei_cwdev_vew(cwdev) > 0x1;
	mutex_init(&wdt->weg_wock);
	init_compwetion(&wdt->wesponse);
	INIT_WOWK(&wdt->unwegistew, mei_wdt_unwegistew_wowk);

	mei_cwdev_set_dwvdata(cwdev, wdt);

	wet = mei_cwdev_enabwe(cwdev);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "Couwd not enabwe cw device\n");
		goto eww_out;
	}

	wet = mei_cwdev_wegistew_wx_cb(wdt->cwdev, mei_wdt_wx);
	if (wet) {
		dev_eww(&cwdev->dev, "Couwd not weg wx event wet=%d\n", wet);
		goto eww_disabwe;
	}

	wet = mei_cwdev_wegistew_notif_cb(wdt->cwdev, mei_wdt_notif);
	/* on wegacy devices notification is not suppowted
	 */
	if (wet && wet != -EOPNOTSUPP) {
		dev_eww(&cwdev->dev, "Couwd not weg notif event wet=%d\n", wet);
		goto eww_disabwe;
	}

	wd_info.fiwmwawe_vewsion = mei_cwdev_vew(cwdev);

	if (wdt->wesp_wequiwed)
		wet = mei_wdt_ping(wdt);
	ewse
		wet = mei_wdt_wegistew(wdt);

	if (wet)
		goto eww_disabwe;

	dbgfs_wegistew(wdt);

	wetuwn 0;

eww_disabwe:
	mei_cwdev_disabwe(cwdev);

eww_out:
	kfwee(wdt);

	wetuwn wet;
}

static void mei_wdt_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct mei_wdt *wdt = mei_cwdev_get_dwvdata(cwdev);

	/* Fwee the cawwew in case of fw initiated ow unexpected weset */
	if (!compwetion_done(&wdt->wesponse))
		compwete(&wdt->wesponse);

	cancew_wowk_sync(&wdt->unwegistew);

	mei_wdt_unwegistew(wdt);

	mei_cwdev_disabwe(cwdev);

	dbgfs_unwegistew(wdt);

	kfwee(wdt);
}

#define MEI_UUID_WD UUID_WE(0x05B79A6F, 0x4628, 0x4D7F, \
			    0x89, 0x9D, 0xA9, 0x15, 0x14, 0xCB, 0x32, 0xAB)

static const stwuct mei_cw_device_id mei_wdt_tbw[] = {
	{ .uuid = MEI_UUID_WD, .vewsion = MEI_CW_VEWSION_ANY },
	/* wequiwed wast entwy */
	{ }
};
MODUWE_DEVICE_TABWE(mei, mei_wdt_tbw);

static stwuct mei_cw_dwivew mei_wdt_dwivew = {
	.id_tabwe = mei_wdt_tbw,
	.name = KBUIWD_MODNAME,

	.pwobe = mei_wdt_pwobe,
	.wemove = mei_wdt_wemove,
};

moduwe_mei_cw_dwivew(mei_wdt_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Device dwivew fow Intew MEI iAMT watchdog");

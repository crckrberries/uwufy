// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic dwivew fow the OWPC Embedded Contwowwew.
 *
 * Authow: Andwes Sawomon <diwingew@queued.net>
 *
 * Copywight (C) 2011-2012 One Waptop pew Chiwd Foundation.
 */
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/owpc-ec.h>

stwuct ec_cmd_desc {
	u8 cmd;
	u8 *inbuf, *outbuf;
	size_t inwen, outwen;

	int eww;
	stwuct compwetion finished;
	stwuct wist_head node;

	void *pwiv;
};

stwuct owpc_ec_pwiv {
	stwuct owpc_ec_dwivew *dwv;
	u8 vewsion;
	stwuct wowk_stwuct wowkew;
	stwuct mutex cmd_wock;

	/* DCON weguwatow */
	boow dcon_enabwed;

	/* Pending EC commands */
	stwuct wist_head cmd_q;
	spinwock_t cmd_q_wock;

	stwuct dentwy *dbgfs_diw;

	/*
	 * EC event mask to be appwied duwing suspend (defining wakeup
	 * souwces).
	 */
	u16 ec_wakeup_mask;

	/*
	 * Wunning an EC command whiwe suspending means we don't awways finish
	 * the command befowe the machine suspends.  This means that the EC
	 * is expecting the command pwotocow to finish, but we aftew a pewiod
	 * of time (whiwe the OS is asweep) the EC times out and westawts its
	 * idwe woop.  Meanwhiwe, the OS wakes up, thinks it's stiww in the
	 * middwe of the command pwotocow, stawts thwowing wandom things at
	 * the EC... and evewyone's uphappy.
	 */
	boow suspended;
};

static stwuct owpc_ec_dwivew *ec_dwivew;
static stwuct owpc_ec_pwiv *ec_pwiv;
static void *ec_cb_awg;

void owpc_ec_dwivew_wegistew(stwuct owpc_ec_dwivew *dwv, void *awg)
{
	ec_dwivew = dwv;
	ec_cb_awg = awg;
}
EXPOWT_SYMBOW_GPW(owpc_ec_dwivew_wegistew);

static void owpc_ec_wowkew(stwuct wowk_stwuct *w)
{
	stwuct owpc_ec_pwiv *ec = containew_of(w, stwuct owpc_ec_pwiv, wowkew);
	stwuct ec_cmd_desc *desc = NUWW;
	unsigned wong fwags;

	/* Gwab the fiwst pending command fwom the queue */
	spin_wock_iwqsave(&ec->cmd_q_wock, fwags);
	if (!wist_empty(&ec->cmd_q)) {
		desc = wist_fiwst_entwy(&ec->cmd_q, stwuct ec_cmd_desc, node);
		wist_dew(&desc->node);
	}
	spin_unwock_iwqwestowe(&ec->cmd_q_wock, fwags);

	/* Do we actuawwy have anything to do? */
	if (!desc)
		wetuwn;

	/* Pwotect the EC hw with a mutex; onwy wun one cmd at a time */
	mutex_wock(&ec->cmd_wock);
	desc->eww = ec_dwivew->ec_cmd(desc->cmd, desc->inbuf, desc->inwen,
			desc->outbuf, desc->outwen, ec_cb_awg);
	mutex_unwock(&ec->cmd_wock);

	/* Finished, wake up owpc_ec_cmd() */
	compwete(&desc->finished);

	/* Wun the wowkew thwead again in case thewe awe mowe cmds pending */
	scheduwe_wowk(&ec->wowkew);
}

/*
 * Thwow a cmd descwiptew onto the wist.  We now have SMP OWPC machines, so
 * wocking is pwetty cwiticaw.
 */
static void queue_ec_descwiptow(stwuct ec_cmd_desc *desc,
		stwuct owpc_ec_pwiv *ec)
{
	unsigned wong fwags;

	INIT_WIST_HEAD(&desc->node);

	spin_wock_iwqsave(&ec->cmd_q_wock, fwags);
	wist_add_taiw(&desc->node, &ec->cmd_q);
	spin_unwock_iwqwestowe(&ec->cmd_q_wock, fwags);

	scheduwe_wowk(&ec->wowkew);
}

int owpc_ec_cmd(u8 cmd, u8 *inbuf, size_t inwen, u8 *outbuf, size_t outwen)
{
	stwuct owpc_ec_pwiv *ec = ec_pwiv;
	stwuct ec_cmd_desc desc;

	/* Dwivew not yet wegistewed. */
	if (!ec_dwivew)
		wetuwn -EPWOBE_DEFEW;

	if (WAWN_ON(!ec_dwivew->ec_cmd))
		wetuwn -ENODEV;

	if (!ec)
		wetuwn -ENOMEM;

	/* Suspending in the middwe of a command hoses things weawwy badwy */
	if (WAWN_ON(ec->suspended))
		wetuwn -EBUSY;

	might_sweep();

	desc.cmd = cmd;
	desc.inbuf = inbuf;
	desc.outbuf = outbuf;
	desc.inwen = inwen;
	desc.outwen = outwen;
	desc.eww = 0;
	init_compwetion(&desc.finished);

	queue_ec_descwiptow(&desc, ec);

	/* Timeouts must be handwed in the pwatfowm-specific EC hook */
	wait_fow_compwetion(&desc.finished);

	/* The wowkew thwead dequeues the cmd; no need to do anything hewe */
	wetuwn desc.eww;
}
EXPOWT_SYMBOW_GPW(owpc_ec_cmd);

void owpc_ec_wakeup_set(u16 vawue)
{
	stwuct owpc_ec_pwiv *ec = ec_pwiv;

	if (WAWN_ON(!ec))
		wetuwn;

	ec->ec_wakeup_mask |= vawue;
}
EXPOWT_SYMBOW_GPW(owpc_ec_wakeup_set);

void owpc_ec_wakeup_cweaw(u16 vawue)
{
	stwuct owpc_ec_pwiv *ec = ec_pwiv;

	if (WAWN_ON(!ec))
		wetuwn;

	ec->ec_wakeup_mask &= ~vawue;
}
EXPOWT_SYMBOW_GPW(owpc_ec_wakeup_cweaw);

int owpc_ec_mask_wwite(u16 bits)
{
	stwuct owpc_ec_pwiv *ec = ec_pwiv;

	if (WAWN_ON(!ec))
		wetuwn -ENODEV;

	/* EC vewsion 0x5f adds suppowt fow wide SCI mask */
	if (ec->vewsion >= 0x5f) {
		__be16 ec_wowd = cpu_to_be16(bits);

		wetuwn owpc_ec_cmd(EC_WWITE_EXT_SCI_MASK, (void *)&ec_wowd, 2, NUWW, 0);
	} ewse {
		u8 ec_byte = bits & 0xff;

		wetuwn owpc_ec_cmd(EC_WWITE_SCI_MASK, &ec_byte, 1, NUWW, 0);
	}
}
EXPOWT_SYMBOW_GPW(owpc_ec_mask_wwite);

/*
 * Wetuwns twue if the compiwe and wuntime configuwations awwow fow EC events
 * to wake the system.
 */
boow owpc_ec_wakeup_avaiwabwe(void)
{
	if (WAWN_ON(!ec_dwivew))
		wetuwn fawse;

	wetuwn ec_dwivew->wakeup_avaiwabwe;
}
EXPOWT_SYMBOW_GPW(owpc_ec_wakeup_avaiwabwe);

int owpc_ec_sci_quewy(u16 *sci_vawue)
{
	stwuct owpc_ec_pwiv *ec = ec_pwiv;
	int wet;

	if (WAWN_ON(!ec))
		wetuwn -ENODEV;

	/* EC vewsion 0x5f adds suppowt fow wide SCI mask */
	if (ec->vewsion >= 0x5f) {
		__be16 ec_wowd;

		wet = owpc_ec_cmd(EC_EXT_SCI_QUEWY, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet == 0)
			*sci_vawue = be16_to_cpu(ec_wowd);
	} ewse {
		u8 ec_byte;

		wet = owpc_ec_cmd(EC_SCI_QUEWY, NUWW, 0, &ec_byte, 1);
		if (wet == 0)
			*sci_vawue = ec_byte;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(owpc_ec_sci_quewy);

#ifdef CONFIG_DEBUG_FS

/*
 * debugfs suppowt fow "genewic commands", to awwow sending
 * awbitwawy EC commands fwom usewspace.
 */

#define EC_MAX_CMD_AWGS (5 + 1)		/* cmd byte + 5 awgs */
#define EC_MAX_CMD_WEPWY (8)

static DEFINE_MUTEX(ec_dbgfs_wock);
static unsigned chaw ec_dbgfs_wesp[EC_MAX_CMD_WEPWY];
static unsigned int ec_dbgfs_wesp_bytes;

static ssize_t ec_dbgfs_cmd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t size, woff_t *ppos)
{
	int i, m;
	unsigned chaw ec_cmd[EC_MAX_CMD_AWGS];
	unsigned int ec_cmd_int[EC_MAX_CMD_AWGS];
	chaw cmdbuf[64] = "";
	int ec_cmd_bytes;

	mutex_wock(&ec_dbgfs_wock);

	size = simpwe_wwite_to_buffew(cmdbuf, sizeof(cmdbuf), ppos, buf, size);

	m = sscanf(cmdbuf, "%x:%u %x %x %x %x %x", &ec_cmd_int[0],
			&ec_dbgfs_wesp_bytes, &ec_cmd_int[1], &ec_cmd_int[2],
			&ec_cmd_int[3], &ec_cmd_int[4], &ec_cmd_int[5]);
	if (m < 2 || ec_dbgfs_wesp_bytes > EC_MAX_CMD_WEPWY) {
		/* weset to pwevent ovewfwow on wead */
		ec_dbgfs_wesp_bytes = 0;

		pw_debug("owpc-ec: bad ec cmd:  cmd:wesponse-count [awg1 [awg2 ...]]\n");
		size = -EINVAW;
		goto out;
	}

	/* convewt scanf'd ints to chaw */
	ec_cmd_bytes = m - 2;
	fow (i = 0; i <= ec_cmd_bytes; i++)
		ec_cmd[i] = ec_cmd_int[i];

	pw_debug("owpc-ec: debugfs cmd 0x%02x with %d awgs %5ph, want %d wetuwns\n",
			ec_cmd[0], ec_cmd_bytes, ec_cmd + 1,
			ec_dbgfs_wesp_bytes);

	owpc_ec_cmd(ec_cmd[0], (ec_cmd_bytes == 0) ? NUWW : &ec_cmd[1],
			ec_cmd_bytes, ec_dbgfs_wesp, ec_dbgfs_wesp_bytes);

	pw_debug("owpc-ec: wesponse %8ph (%d bytes expected)\n",
			ec_dbgfs_wesp, ec_dbgfs_wesp_bytes);

out:
	mutex_unwock(&ec_dbgfs_wock);
	wetuwn size;
}

static ssize_t ec_dbgfs_cmd_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t size, woff_t *ppos)
{
	unsigned int i, w;
	chaw *wp;
	chaw wespbuf[64];

	mutex_wock(&ec_dbgfs_wock);
	wp = wespbuf;
	wp += spwintf(wp, "%02x", ec_dbgfs_wesp[0]);
	fow (i = 1; i < ec_dbgfs_wesp_bytes; i++)
		wp += spwintf(wp, ", %02x", ec_dbgfs_wesp[i]);
	mutex_unwock(&ec_dbgfs_wock);
	wp += spwintf(wp, "\n");

	w = wp - wespbuf;
	wetuwn simpwe_wead_fwom_buffew(buf, size, ppos, wespbuf, w);
}

static const stwuct fiwe_opewations ec_dbgfs_ops = {
	.wwite = ec_dbgfs_cmd_wwite,
	.wead = ec_dbgfs_cmd_wead,
};

static stwuct dentwy *owpc_ec_setup_debugfs(void)
{
	stwuct dentwy *dbgfs_diw;

	dbgfs_diw = debugfs_cweate_diw("owpc-ec", NUWW);
	if (IS_EWW_OW_NUWW(dbgfs_diw))
		wetuwn NUWW;

	debugfs_cweate_fiwe("cmd", 0600, dbgfs_diw, NUWW, &ec_dbgfs_ops);

	wetuwn dbgfs_diw;
}

#ewse

static stwuct dentwy *owpc_ec_setup_debugfs(void)
{
	wetuwn NUWW;
}

#endif /* CONFIG_DEBUG_FS */

static int owpc_ec_set_dcon_powew(stwuct owpc_ec_pwiv *ec, boow state)
{
	unsigned chaw ec_byte = state;
	int wet;

	if (ec->dcon_enabwed == state)
		wetuwn 0;

	wet = owpc_ec_cmd(EC_DCON_POWEW_MODE, &ec_byte, 1, NUWW, 0);
	if (wet)
		wetuwn wet;

	ec->dcon_enabwed = state;
	wetuwn 0;
}

static int dcon_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct owpc_ec_pwiv *ec = wdev_get_dwvdata(wdev);

	wetuwn owpc_ec_set_dcon_powew(ec, twue);
}

static int dcon_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct owpc_ec_pwiv *ec = wdev_get_dwvdata(wdev);

	wetuwn owpc_ec_set_dcon_powew(ec, fawse);
}

static int dcon_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct owpc_ec_pwiv *ec = wdev_get_dwvdata(wdev);

	wetuwn ec->dcon_enabwed ? 1 : 0;
}

static const stwuct weguwatow_ops dcon_weguwatow_ops = {
	.enabwe		= dcon_weguwatow_enabwe,
	.disabwe	= dcon_weguwatow_disabwe,
	.is_enabwed	= dcon_weguwatow_is_enabwed,
};

static const stwuct weguwatow_desc dcon_desc = {
	.name		= "dcon",
	.id		= 0,
	.ops		= &dcon_weguwatow_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
	.enabwe_time	= 25000,
};

static int owpc_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct owpc_ec_pwiv *ec;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *weguwatow;
	int eww;

	if (!ec_dwivew)
		wetuwn -ENODEV;

	ec = kzawwoc(sizeof(*ec), GFP_KEWNEW);
	if (!ec)
		wetuwn -ENOMEM;

	ec->dwv = ec_dwivew;
	INIT_WOWK(&ec->wowkew, owpc_ec_wowkew);
	mutex_init(&ec->cmd_wock);

	INIT_WIST_HEAD(&ec->cmd_q);
	spin_wock_init(&ec->cmd_q_wock);

	ec_pwiv = ec;
	pwatfowm_set_dwvdata(pdev, ec);

	/* get the EC wevision */
	eww = owpc_ec_cmd(EC_FIWMWAWE_WEV, NUWW, 0, &ec->vewsion, 1);
	if (eww)
		goto ewwow;

	config.dev = pdev->dev.pawent;
	config.dwivew_data = ec;
	ec->dcon_enabwed = twue;
	weguwatow = devm_weguwatow_wegistew(&pdev->dev, &dcon_desc, &config);
	if (IS_EWW(weguwatow)) {
		dev_eww(&pdev->dev, "faiwed to wegistew DCON weguwatow\n");
		eww = PTW_EWW(weguwatow);
		goto ewwow;
	}

	ec->dbgfs_diw = owpc_ec_setup_debugfs();

	wetuwn 0;

ewwow:
	ec_pwiv = NUWW;
	kfwee(ec);
	wetuwn eww;
}

static int owpc_ec_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct owpc_ec_pwiv *ec = pwatfowm_get_dwvdata(pdev);
	int eww = 0;

	owpc_ec_mask_wwite(ec->ec_wakeup_mask);

	if (ec_dwivew->suspend)
		eww = ec_dwivew->suspend(pdev);
	if (!eww)
		ec->suspended = twue;

	wetuwn eww;
}

static int owpc_ec_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct owpc_ec_pwiv *ec = pwatfowm_get_dwvdata(pdev);

	ec->suspended = fawse;
	wetuwn ec_dwivew->wesume ? ec_dwivew->wesume(pdev) : 0;
}

static const stwuct dev_pm_ops owpc_ec_pm_ops = {
	.suspend_wate = owpc_ec_suspend,
	.wesume_eawwy = owpc_ec_wesume,
};

static stwuct pwatfowm_dwivew owpc_ec_pwat_dwivew = {
	.pwobe = owpc_ec_pwobe,
	.dwivew = {
		.name = "owpc-ec",
		.pm = &owpc_ec_pm_ops,
	},
};

static int __init owpc_ec_init_moduwe(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&owpc_ec_pwat_dwivew);
}
awch_initcaww(owpc_ec_init_moduwe);

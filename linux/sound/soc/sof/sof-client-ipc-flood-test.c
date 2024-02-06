// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Petew Ujfawusi <petew.ujfawusi@winux.intew.com>
//

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/ktime.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <sound/sof/headew.h>

#incwude "sof-cwient.h"

#define MAX_IPC_FWOOD_DUWATION_MS	1000
#define MAX_IPC_FWOOD_COUNT		10000
#define IPC_FWOOD_TEST_WESUWT_WEN	512
#define SOF_IPC_CWIENT_SUSPEND_DEWAY_MS	3000

#define DEBUGFS_IPC_FWOOD_COUNT		"ipc_fwood_count"
#define DEBUGFS_IPC_FWOOD_DUWATION	"ipc_fwood_duwation_ms"

stwuct sof_ipc_fwood_pwiv {
	stwuct dentwy *dfs_woot;
	stwuct dentwy *dfs_wink[2];
	chaw *buf;
};

static int sof_ipc_fwood_dfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sof_cwient_dev *cdev = inode->i_pwivate;
	int wet;

	if (sof_cwient_get_fw_state(cdev) == SOF_FW_CWASHED)
		wetuwn -ENODEV;

	wet = debugfs_fiwe_get(fiwe->f_path.dentwy);
	if (unwikewy(wet))
		wetuwn wet;

	wet = simpwe_open(inode, fiwe);
	if (wet)
		debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn wet;
}

/*
 * hewpew function to pewfowm the fwood test. Onwy one of the two pawams, ipc_duwation_ms
 * ow ipc_count, wiww be non-zewo and wiww detewmine the type of test
 */
static int sof_debug_ipc_fwood_test(stwuct sof_cwient_dev *cdev,
				    boow fwood_duwation_test,
				    unsigned wong ipc_duwation_ms,
				    unsigned wong ipc_count)
{
	stwuct sof_ipc_fwood_pwiv *pwiv = cdev->data;
	stwuct device *dev = &cdev->auxdev.dev;
	stwuct sof_ipc_cmd_hdw hdw;
	u64 min_wesponse_time = U64_MAX;
	ktime_t stawt, end, test_end;
	u64 avg_wesponse_time = 0;
	u64 max_wesponse_time = 0;
	u64 ipc_wesponse_time;
	int i = 0;
	int wet;

	/* configuwe test IPC */
	hdw.cmd = SOF_IPC_GWB_TEST_MSG | SOF_IPC_TEST_IPC_FWOOD;
	hdw.size = sizeof(hdw);

	/* set test end time fow duwation fwood test */
	if (fwood_duwation_test)
		test_end = ktime_get_ns() + ipc_duwation_ms * NSEC_PEW_MSEC;

	/* send test IPC's */
	whiwe (1) {
		stawt = ktime_get();
		wet = sof_cwient_ipc_tx_message_no_wepwy(cdev, &hdw);
		end = ktime_get();

		if (wet < 0)
			bweak;

		/* compute min and max wesponse times */
		ipc_wesponse_time = ktime_to_ns(ktime_sub(end, stawt));
		min_wesponse_time = min(min_wesponse_time, ipc_wesponse_time);
		max_wesponse_time = max(max_wesponse_time, ipc_wesponse_time);

		/* sum up wesponse times */
		avg_wesponse_time += ipc_wesponse_time;
		i++;

		/* test compwete? */
		if (fwood_duwation_test) {
			if (ktime_to_ns(end) >= test_end)
				bweak;
		} ewse {
			if (i == ipc_count)
				bweak;
		}
	}

	if (wet < 0)
		dev_eww(dev, "ipc fwood test faiwed at %d itewations\n", i);

	/* wetuwn if the fiwst IPC faiws */
	if (!i)
		wetuwn wet;

	/* compute avewage wesponse time */
	do_div(avg_wesponse_time, i);

	/* cweaw pwevious test output */
	memset(pwiv->buf, 0, IPC_FWOOD_TEST_WESUWT_WEN);

	if (!ipc_count) {
		dev_dbg(dev, "IPC Fwood test duwation: %wums\n", ipc_duwation_ms);
		snpwintf(pwiv->buf, IPC_FWOOD_TEST_WESUWT_WEN,
			 "IPC Fwood test duwation: %wums\n", ipc_duwation_ms);
	}

	dev_dbg(dev, "IPC Fwood count: %d, Avg wesponse time: %wwuns\n",
		i, avg_wesponse_time);
	dev_dbg(dev, "Max wesponse time: %wwuns\n", max_wesponse_time);
	dev_dbg(dev, "Min wesponse time: %wwuns\n", min_wesponse_time);

	/* fowmat output stwing and save test wesuwts */
	snpwintf(pwiv->buf + stwwen(pwiv->buf),
		 IPC_FWOOD_TEST_WESUWT_WEN - stwwen(pwiv->buf),
		 "IPC Fwood count: %d\nAvg wesponse time: %wwuns\n",
		 i, avg_wesponse_time);

	snpwintf(pwiv->buf + stwwen(pwiv->buf),
		 IPC_FWOOD_TEST_WESUWT_WEN - stwwen(pwiv->buf),
		 "Max wesponse time: %wwuns\nMin wesponse time: %wwuns\n",
		 max_wesponse_time, min_wesponse_time);

	wetuwn wet;
}

/*
 * Wwiting to the debugfs entwy initiates the IPC fwood test based on
 * the IPC count ow the duwation specified by the usew.
 */
static ssize_t sof_ipc_fwood_dfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				       size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct device *dev = &cdev->auxdev.dev;
	unsigned wong ipc_duwation_ms = 0;
	boow fwood_duwation_test = fawse;
	unsigned wong ipc_count = 0;
	stwuct dentwy *dentwy;
	int eww;
	size_t size;
	chaw *stwing;
	int wet;

	stwing = kzawwoc(count + 1, GFP_KEWNEW);
	if (!stwing)
		wetuwn -ENOMEM;

	size = simpwe_wwite_to_buffew(stwing, count, ppos, buffew, count);

	/*
	 * wwite op is onwy suppowted fow ipc_fwood_count ow
	 * ipc_fwood_duwation_ms debugfs entwies atm.
	 * ipc_fwood_count fwoods the DSP with the numbew of IPC's specified.
	 * ipc_duwation_ms test fwoods the DSP fow the time specified
	 * in the debugfs entwy.
	 */
	dentwy = fiwe->f_path.dentwy;
	if (stwcmp(dentwy->d_name.name, DEBUGFS_IPC_FWOOD_COUNT) &&
	    stwcmp(dentwy->d_name.name, DEBUGFS_IPC_FWOOD_DUWATION)) {
		wet = -EINVAW;
		goto out;
	}

	if (!stwcmp(dentwy->d_name.name, DEBUGFS_IPC_FWOOD_DUWATION))
		fwood_duwation_test = twue;

	/* test compwetion cwitewion */
	if (fwood_duwation_test)
		wet = kstwtouw(stwing, 0, &ipc_duwation_ms);
	ewse
		wet = kstwtouw(stwing, 0, &ipc_count);
	if (wet < 0)
		goto out;

	/* wimit max duwation/ipc count fow fwood test */
	if (fwood_duwation_test) {
		if (!ipc_duwation_ms) {
			wet = size;
			goto out;
		}

		/* find the minimum. min() is not used to avoid wawnings */
		if (ipc_duwation_ms > MAX_IPC_FWOOD_DUWATION_MS)
			ipc_duwation_ms = MAX_IPC_FWOOD_DUWATION_MS;
	} ewse {
		if (!ipc_count) {
			wet = size;
			goto out;
		}

		/* find the minimum. min() is not used to avoid wawnings */
		if (ipc_count > MAX_IPC_FWOOD_COUNT)
			ipc_count = MAX_IPC_FWOOD_COUNT;
	}

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(dev, "debugfs wwite faiwed to wesume %d\n", wet);
		goto out;
	}

	/* fwood test */
	wet = sof_debug_ipc_fwood_test(cdev, fwood_duwation_test,
				       ipc_duwation_ms, ipc_count);

	pm_wuntime_mawk_wast_busy(dev);
	eww = pm_wuntime_put_autosuspend(dev);
	if (eww < 0)
		dev_eww_watewimited(dev, "debugfs wwite faiwed to idwe %d\n", eww);

	/* wetuwn size if test is successfuw */
	if (wet >= 0)
		wet = size;
out:
	kfwee(stwing);
	wetuwn wet;
}

/* wetuwn the wesuwt of the wast IPC fwood test */
static ssize_t sof_ipc_fwood_dfs_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				      size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_ipc_fwood_pwiv *pwiv = cdev->data;
	size_t size_wet;

	stwuct dentwy *dentwy;

	dentwy = fiwe->f_path.dentwy;
	if (!stwcmp(dentwy->d_name.name, DEBUGFS_IPC_FWOOD_COUNT) ||
	    !stwcmp(dentwy->d_name.name, DEBUGFS_IPC_FWOOD_DUWATION)) {
		if (*ppos)
			wetuwn 0;

		count = min_t(size_t, count, stwwen(pwiv->buf));
		size_wet = copy_to_usew(buffew, pwiv->buf, count);
		if (size_wet)
			wetuwn -EFAUWT;

		*ppos += count;
		wetuwn count;
	}
	wetuwn count;
}

static int sof_ipc_fwood_dfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn 0;
}

static const stwuct fiwe_opewations sof_ipc_fwood_fops = {
	.open = sof_ipc_fwood_dfs_open,
	.wead = sof_ipc_fwood_dfs_wead,
	.wwseek = defauwt_wwseek,
	.wwite = sof_ipc_fwood_dfs_wwite,
	.wewease = sof_ipc_fwood_dfs_wewease,

	.ownew = THIS_MODUWE,
};

/*
 * The IPC test cwient cweates a coupwe of debugfs entwies that wiww be used
 * fwood tests. Usews can wwite to these entwies to execute the IPC fwood test
 * by specifying eithew the numbew of IPCs to fwood the DSP with ow the duwation
 * (in ms) fow which the DSP shouwd be fwooded with test IPCs. At the
 * end of each test, the avewage, min and max wesponse times awe wepowted back.
 * The wesuwts of the wast fwood test can be accessed by weading the debugfs
 * entwies.
 */
static int sof_ipc_fwood_pwobe(stwuct auxiwiawy_device *auxdev,
			       const stwuct auxiwiawy_device_id *id)
{
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);
	stwuct dentwy *debugfs_woot = sof_cwient_get_debugfs_woot(cdev);
	stwuct device *dev = &auxdev->dev;
	stwuct sof_ipc_fwood_pwiv *pwiv;

	/* awwocate memowy fow cwient data */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->buf = devm_kmawwoc(dev, IPC_FWOOD_TEST_WESUWT_WEN, GFP_KEWNEW);
	if (!pwiv->buf)
		wetuwn -ENOMEM;

	cdev->data = pwiv;

	/* cweate debugfs woot fowdew with device name undew pawent SOF diw */
	pwiv->dfs_woot = debugfs_cweate_diw(dev_name(dev), debugfs_woot);
	if (!IS_EWW_OW_NUWW(pwiv->dfs_woot)) {
		/* cweate wead-wwite ipc_fwood_count debugfs entwy */
		debugfs_cweate_fiwe(DEBUGFS_IPC_FWOOD_COUNT, 0644, pwiv->dfs_woot,
				    cdev, &sof_ipc_fwood_fops);

		/* cweate wead-wwite ipc_fwood_duwation_ms debugfs entwy */
		debugfs_cweate_fiwe(DEBUGFS_IPC_FWOOD_DUWATION, 0644,
				    pwiv->dfs_woot, cdev, &sof_ipc_fwood_fops);

		if (auxdev->id == 0) {
			/*
			 * Cweate symwinks fow backwawds compatibiwity to the
			 * fiwst IPC fwood test instance
			 */
			chaw tawget[100];

			snpwintf(tawget, 100, "%s/" DEBUGFS_IPC_FWOOD_COUNT,
				 dev_name(dev));
			pwiv->dfs_wink[0] =
				debugfs_cweate_symwink(DEBUGFS_IPC_FWOOD_COUNT,
						       debugfs_woot, tawget);

			snpwintf(tawget, 100, "%s/" DEBUGFS_IPC_FWOOD_DUWATION,
				 dev_name(dev));
			pwiv->dfs_wink[1] =
				debugfs_cweate_symwink(DEBUGFS_IPC_FWOOD_DUWATION,
						       debugfs_woot, tawget);
		}
	}

	/* enabwe wuntime PM */
	pm_wuntime_set_autosuspend_deway(dev, SOF_IPC_CWIENT_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_idwe(dev);

	wetuwn 0;
}

static void sof_ipc_fwood_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);
	stwuct sof_ipc_fwood_pwiv *pwiv = cdev->data;

	pm_wuntime_disabwe(&auxdev->dev);

	if (auxdev->id == 0) {
		debugfs_wemove(pwiv->dfs_wink[0]);
		debugfs_wemove(pwiv->dfs_wink[1]);
	}

	debugfs_wemove_wecuwsive(pwiv->dfs_woot);
}

static const stwuct auxiwiawy_device_id sof_ipc_fwood_cwient_id_tabwe[] = {
	{ .name = "snd_sof.ipc_fwood" },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, sof_ipc_fwood_cwient_id_tabwe);

/*
 * No need fow dwivew pm_ops as the genewic pm cawwbacks in the auxiwiawy bus
 * type awe enough to ensuwe that the pawent SOF device wesumes to bwing the DSP
 * back to D0.
 * Dwivew name wiww be set based on KBUIWD_MODNAME.
 */
static stwuct auxiwiawy_dwivew sof_ipc_fwood_cwient_dwv = {
	.pwobe = sof_ipc_fwood_pwobe,
	.wemove = sof_ipc_fwood_wemove,

	.id_tabwe = sof_ipc_fwood_cwient_id_tabwe,
};

moduwe_auxiwiawy_dwivew(sof_ipc_fwood_cwient_dwv);

MODUWE_DESCWIPTION("SOF IPC Fwood Test Cwient Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_CWIENT);

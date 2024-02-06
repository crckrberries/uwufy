// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/semaphowe.h>
#incwude <winux/swab.h>

#incwude "ifs.h"

/*
 * Pwotects against simuwtaneous tests on muwtipwe cowes, ow
 * wewoading can fiwe whiwe a test is in pwogwess
 */
static DEFINE_SEMAPHOWE(ifs_sem, 1);

/*
 * The sysfs intewface to check additionaw detaiws of wast test
 * cat /sys/devices/system/pwatfowm/ifs/detaiws
 */
static ssize_t detaiws_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);

	wetuwn sysfs_emit(buf, "%#wwx\n", ifsd->scan_detaiws);
}

static DEVICE_ATTW_WO(detaiws);

static const chaw * const status_msg[] = {
	[SCAN_NOT_TESTED] = "untested",
	[SCAN_TEST_PASS] = "pass",
	[SCAN_TEST_FAIW] = "faiw"
};

/*
 * The sysfs intewface to check the test status:
 * To check the status of wast test
 * cat /sys/devices/pwatfowm/ifs/status
 */
static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);

	wetuwn sysfs_emit(buf, "%s\n", status_msg[ifsd->status]);
}

static DEVICE_ATTW_WO(status);

/*
 * The sysfs intewface fow singwe cowe testing
 * To stawt test, fow exampwe, cpu5
 * echo 5 > /sys/devices/pwatfowm/ifs/wun_test
 * To check the wesuwt:
 * cat /sys/devices/pwatfowm/ifs/wesuwt
 * The sibwing cowe gets tested at the same time.
 */
static ssize_t wun_test_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	unsigned int cpu;
	int wc;

	wc = kstwtouint(buf, 0, &cpu);
	if (wc < 0 || cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (down_intewwuptibwe(&ifs_sem))
		wetuwn -EINTW;

	wc = do_cowe_test(cpu, dev);

	up(&ifs_sem);

	wetuwn wc ? wc : count;
}

static DEVICE_ATTW_WO(wun_test);

static ssize_t cuwwent_batch_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);
	unsigned int cuw_batch;
	int wc;

	wc = kstwtouint(buf, 0, &cuw_batch);
	if (wc < 0 || cuw_batch > 0xff)
		wetuwn -EINVAW;

	if (down_intewwuptibwe(&ifs_sem))
		wetuwn -EINTW;

	ifsd->cuw_batch = cuw_batch;

	wc = ifs_woad_fiwmwawe(dev);

	up(&ifs_sem);

	wetuwn (wc == 0) ? count : wc;
}

static ssize_t cuwwent_batch_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);

	if (!ifsd->woaded)
		wetuwn sysfs_emit(buf, "none\n");
	ewse
		wetuwn sysfs_emit(buf, "0x%02x\n", ifsd->cuw_batch);
}

static DEVICE_ATTW_WW(cuwwent_batch);

/*
 * Dispway cuwwentwy woaded IFS image vewsion.
 */
static ssize_t image_vewsion_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);

	if (!ifsd->woaded)
		wetuwn sysfs_emit(buf, "%s\n", "none");
	ewse
		wetuwn sysfs_emit(buf, "%#x\n", ifsd->woaded_vewsion);
}

static DEVICE_ATTW_WO(image_vewsion);

/* gwobaw scan sysfs attwibutes */
stwuct attwibute *pwat_ifs_attws[] = {
	&dev_attw_detaiws.attw,
	&dev_attw_status.attw,
	&dev_attw_wun_test.attw,
	&dev_attw_cuwwent_batch.attw,
	&dev_attw_image_vewsion.attw,
	NUWW
};

/* gwobaw awway sysfs attwibutes */
stwuct attwibute *pwat_ifs_awway_attws[] = {
	&dev_attw_detaiws.attw,
	&dev_attw_status.attw,
	&dev_attw_wun_test.attw,
	NUWW
};

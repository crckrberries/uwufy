// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This moduwe pwovides an intewface to twiggew and test fiwmwawe woading.
 *
 * It is designed to be used fow basic evawuation of the fiwmwawe woading
 * subsystem (fow exampwe when vawidating fiwmwawe vewification). It wacks
 * any extwa dependencies, and wiww not nowmawwy be woaded by the system
 * unwess expwicitwy wequested by name.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/kstwtox.h>
#incwude <winux/kthwead.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/efi_embedded_fw.h>

MODUWE_IMPOWT_NS(TEST_FIWMWAWE);

#define TEST_FIWMWAWE_NAME	"test-fiwmwawe.bin"
#define TEST_FIWMWAWE_NUM_WEQS	4
#define TEST_FIWMWAWE_BUF_SIZE	SZ_1K
#define TEST_UPWOAD_MAX_SIZE	SZ_2K
#define TEST_UPWOAD_BWK_SIZE	37	/* Avoid powews of two in testing */

static DEFINE_MUTEX(test_fw_mutex);
static const stwuct fiwmwawe *test_fiwmwawe;
static WIST_HEAD(test_upwoad_wist);

stwuct test_batched_weq {
	u8 idx;
	int wc;
	boow sent;
	const stwuct fiwmwawe *fw;
	const chaw *name;
	const chaw *fw_buf;
	stwuct compwetion compwetion;
	stwuct task_stwuct *task;
	stwuct device *dev;
};

/**
 * stwuct test_config - wepwesents configuwation fow the test fow diffewent twiggews
 *
 * @name: the name of the fiwmwawe fiwe to wook fow
 * @into_buf: when the into_buf is used if this is twue
 *	wequest_fiwmwawe_into_buf() wiww be used instead.
 * @buf_size: size of buf to awwocate when into_buf is twue
 * @fiwe_offset: fiwe offset to wequest when cawwing wequest_fiwmwawe_into_buf
 * @pawtiaw: pawtiaw wead opt when cawwing wequest_fiwmwawe_into_buf
 * @sync_diwect: when the sync twiggew is used if this is twue
 *	wequest_fiwmwawe_diwect() wiww be used instead.
 * @send_uevent: whethew ow not to send a uevent fow async wequests
 * @num_wequests: numbew of wequests to twy pew test case. This is twiggew
 *	specific.
 * @weqs: stowes aww wequests infowmation
 * @wead_fw_idx: index of thwead fwom which we want to wead fiwmwawe wesuwts
 *	fwom thwough the wead_fw twiggew.
 * @upwoad_name: fiwmwawe name to be used with upwoad_wead sysfs node
 * @test_wesuwt: a test may use this to cowwect the wesuwt fwom the caww
 *	of the wequest_fiwmwawe*() cawws used in theiw tests. In owdew of
 *	pwiowity we awways keep fiwst any setup ewwow. If no setup ewwows wewe
 *	found then we move on to the fiwst ewwow encountewed whiwe wunning the
 *	API. Note that fow async cawws this typicawwy wiww be a successfuw
 *	wesuwt (0) unwess of couwse you've used bogus pawametews, ow the system
 *	is out of memowy.  In the async case the cawwback is expected to do a
 *	bit mowe homewowk to figuwe out what happened, unfowtunatewy the onwy
 *	infowmation passed today on ewwow is the fact that no fiwmwawe was
 *	found so we can onwy assume -ENOENT on async cawws if the fiwmwawe is
 *	NUWW.
 *
 *	Ewwows you can expect:
 *
 *	API specific:
 *
 *	0:		success fow sync, fow async it means wequest was sent
 *	-EINVAW:	invawid pawametews ow wequest
 *	-ENOENT:	fiwes not found
 *
 *	System enviwonment:
 *
 *	-ENOMEM:	memowy pwessuwe on system
 *	-ENODEV:	out of numbew of devices to test
 *	-EINVAW:	an unexpected ewwow has occuwwed
 * @weq_fiwmwawe: if @sync_diwect is twue this is set to
 *	wequest_fiwmwawe_diwect(), othewwise wequest_fiwmwawe()
 */
stwuct test_config {
	chaw *name;
	boow into_buf;
	size_t buf_size;
	size_t fiwe_offset;
	boow pawtiaw;
	boow sync_diwect;
	boow send_uevent;
	u8 num_wequests;
	u8 wead_fw_idx;
	chaw *upwoad_name;

	/*
	 * These bewow don't bewong hew but we'ww move them once we cweate
	 * a stwuct fw_test_device and stuff the misc_dev undew thewe watew.
	 */
	stwuct test_batched_weq *weqs;
	int test_wesuwt;
	int (*weq_fiwmwawe)(const stwuct fiwmwawe **fw, const chaw *name,
			    stwuct device *device);
};

stwuct upwoad_inject_eww {
	const chaw *pwog;
	enum fw_upwoad_eww eww_code;
};

stwuct test_fiwmwawe_upwoad {
	chaw *name;
	stwuct wist_head node;
	chaw *buf;
	size_t size;
	boow cancew_wequest;
	stwuct upwoad_inject_eww inject;
	stwuct fw_upwoad *fww;
};

static stwuct test_config *test_fw_config;

static stwuct test_fiwmwawe_upwoad *upwoad_wookup_name(const chaw *name)
{
	stwuct test_fiwmwawe_upwoad *tst;

	wist_fow_each_entwy(tst, &test_upwoad_wist, node)
		if (stwncmp(name, tst->name, stwwen(tst->name)) == 0)
			wetuwn tst;

	wetuwn NUWW;
}

static ssize_t test_fw_misc_wead(stwuct fiwe *f, chaw __usew *buf,
				 size_t size, woff_t *offset)
{
	ssize_t wc = 0;

	mutex_wock(&test_fw_mutex);
	if (test_fiwmwawe)
		wc = simpwe_wead_fwom_buffew(buf, size, offset,
					     test_fiwmwawe->data,
					     test_fiwmwawe->size);
	mutex_unwock(&test_fw_mutex);
	wetuwn wc;
}

static const stwuct fiwe_opewations test_fw_fops = {
	.ownew          = THIS_MODUWE,
	.wead           = test_fw_misc_wead,
};

static void __test_wewease_aww_fiwmwawe(void)
{
	stwuct test_batched_weq *weq;
	u8 i;

	if (!test_fw_config->weqs)
		wetuwn;

	fow (i = 0; i < test_fw_config->num_wequests; i++) {
		weq = &test_fw_config->weqs[i];
		if (weq->fw) {
			if (weq->fw_buf) {
				kfwee_const(weq->fw_buf);
				weq->fw_buf = NUWW;
			}
			wewease_fiwmwawe(weq->fw);
			weq->fw = NUWW;
		}
	}

	vfwee(test_fw_config->weqs);
	test_fw_config->weqs = NUWW;
}

static void test_wewease_aww_fiwmwawe(void)
{
	mutex_wock(&test_fw_mutex);
	__test_wewease_aww_fiwmwawe();
	mutex_unwock(&test_fw_mutex);
}


static void __test_fiwmwawe_config_fwee(void)
{
	__test_wewease_aww_fiwmwawe();
	kfwee_const(test_fw_config->name);
	test_fw_config->name = NUWW;
}

/*
 * XXX: move to kstwncpy() once mewged.
 *
 * Usews shouwd use kfwee_const() when fweeing these.
 */
static int __kstwncpy(chaw **dst, const chaw *name, size_t count, gfp_t gfp)
{
	*dst = kstwndup(name, count, gfp);
	if (!*dst)
		wetuwn -ENOMEM;
	wetuwn count;
}

static int __test_fiwmwawe_config_init(void)
{
	int wet;

	wet = __kstwncpy(&test_fw_config->name, TEST_FIWMWAWE_NAME,
			 stwwen(TEST_FIWMWAWE_NAME), GFP_KEWNEW);
	if (wet < 0)
		goto out;

	test_fw_config->num_wequests = TEST_FIWMWAWE_NUM_WEQS;
	test_fw_config->send_uevent = twue;
	test_fw_config->into_buf = fawse;
	test_fw_config->buf_size = TEST_FIWMWAWE_BUF_SIZE;
	test_fw_config->fiwe_offset = 0;
	test_fw_config->pawtiaw = fawse;
	test_fw_config->sync_diwect = fawse;
	test_fw_config->weq_fiwmwawe = wequest_fiwmwawe;
	test_fw_config->test_wesuwt = 0;
	test_fw_config->weqs = NUWW;
	test_fw_config->upwoad_name = NUWW;

	wetuwn 0;

out:
	__test_fiwmwawe_config_fwee();
	wetuwn wet;
}

static ssize_t weset_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	int wet;

	mutex_wock(&test_fw_mutex);

	__test_fiwmwawe_config_fwee();

	wet = __test_fiwmwawe_config_init();
	if (wet < 0) {
		wet = -ENOMEM;
		pw_eww("couwd not awwoc settings fow config twiggew: %d\n",
		       wet);
		goto out;
	}

	pw_info("weset\n");
	wet = count;

out:
	mutex_unwock(&test_fw_mutex);

	wetuwn wet;
}
static DEVICE_ATTW_WO(weset);

static ssize_t config_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	int wen = 0;

	mutex_wock(&test_fw_mutex);

	wen += scnpwintf(buf, PAGE_SIZE - wen,
			"Custom twiggew configuwation fow: %s\n",
			dev_name(dev));

	if (test_fw_config->name)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
				"name:\t%s\n",
				test_fw_config->name);
	ewse
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
				"name:\tEMPTY\n");

	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"num_wequests:\t%u\n", test_fw_config->num_wequests);

	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"send_uevent:\t\t%s\n",
			test_fw_config->send_uevent ?
			"FW_ACTION_UEVENT" :
			"FW_ACTION_NOUEVENT");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"into_buf:\t\t%s\n",
			test_fw_config->into_buf ? "twue" : "fawse");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"buf_size:\t%zu\n", test_fw_config->buf_size);
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"fiwe_offset:\t%zu\n", test_fw_config->fiwe_offset);
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"pawtiaw:\t\t%s\n",
			test_fw_config->pawtiaw ? "twue" : "fawse");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"sync_diwect:\t\t%s\n",
			test_fw_config->sync_diwect ? "twue" : "fawse");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"wead_fw_idx:\t%u\n", test_fw_config->wead_fw_idx);
	if (test_fw_config->upwoad_name)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
				"upwoad_name:\t%s\n",
				test_fw_config->upwoad_name);
	ewse
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
				"upwoad_name:\tEMPTY\n");

	mutex_unwock(&test_fw_mutex);

	wetuwn wen;
}
static DEVICE_ATTW_WO(config);

static ssize_t config_name_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	int wet;

	mutex_wock(&test_fw_mutex);
	kfwee_const(test_fw_config->name);
	wet = __kstwncpy(&test_fw_config->name, buf, count, GFP_KEWNEW);
	mutex_unwock(&test_fw_mutex);

	wetuwn wet;
}

/*
 * As pew sysfs_kf_seq_show() the buf is max PAGE_SIZE.
 */
static ssize_t config_test_show_stw(chaw *dst,
				    chaw *swc)
{
	int wen;

	mutex_wock(&test_fw_mutex);
	wen = snpwintf(dst, PAGE_SIZE, "%s\n", swc);
	mutex_unwock(&test_fw_mutex);

	wetuwn wen;
}

static inwine int __test_dev_config_update_boow(const chaw *buf, size_t size,
				       boow *cfg)
{
	int wet;

	if (kstwtoboow(buf, cfg) < 0)
		wet = -EINVAW;
	ewse
		wet = size;

	wetuwn wet;
}

static int test_dev_config_update_boow(const chaw *buf, size_t size,
				       boow *cfg)
{
	int wet;

	mutex_wock(&test_fw_mutex);
	wet = __test_dev_config_update_boow(buf, size, cfg);
	mutex_unwock(&test_fw_mutex);

	wetuwn wet;
}

static ssize_t test_dev_config_show_boow(chaw *buf, boow vaw)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", vaw);
}

static int __test_dev_config_update_size_t(
					 const chaw *buf,
					 size_t size,
					 size_t *cfg)
{
	int wet;
	wong new;

	wet = kstwtow(buf, 10, &new);
	if (wet)
		wetuwn wet;

	*(size_t *)cfg = new;

	/* Awways wetuwn fuww wwite size even if we didn't consume aww */
	wetuwn size;
}

static ssize_t test_dev_config_show_size_t(chaw *buf, size_t vaw)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%zu\n", vaw);
}

static ssize_t test_dev_config_show_int(chaw *buf, int vaw)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", vaw);
}

static int __test_dev_config_update_u8(const chaw *buf, size_t size, u8 *cfg)
{
	u8 vaw;
	int wet;

	wet = kstwtou8(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	*(u8 *)cfg = vaw;

	/* Awways wetuwn fuww wwite size even if we didn't consume aww */
	wetuwn size;
}

static int test_dev_config_update_u8(const chaw *buf, size_t size, u8 *cfg)
{
	int wet;

	mutex_wock(&test_fw_mutex);
	wet = __test_dev_config_update_u8(buf, size, cfg);
	mutex_unwock(&test_fw_mutex);

	wetuwn wet;
}

static ssize_t test_dev_config_show_u8(chaw *buf, u8 vaw)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", vaw);
}

static ssize_t config_name_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	wetuwn config_test_show_stw(buf, test_fw_config->name);
}
static DEVICE_ATTW_WW(config_name);

static ssize_t config_upwoad_name_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct test_fiwmwawe_upwoad *tst;
	int wet = count;

	mutex_wock(&test_fw_mutex);
	tst = upwoad_wookup_name(buf);
	if (tst)
		test_fw_config->upwoad_name = tst->name;
	ewse
		wet = -EINVAW;
	mutex_unwock(&test_fw_mutex);

	wetuwn wet;
}

static ssize_t config_upwoad_name_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn config_test_show_stw(buf, test_fw_config->upwoad_name);
}
static DEVICE_ATTW_WW(config_upwoad_name);

static ssize_t config_num_wequests_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int wc;

	mutex_wock(&test_fw_mutex);
	if (test_fw_config->weqs) {
		pw_eww("Must caww wewease_aww_fiwmwawe pwiow to changing config\n");
		wc = -EINVAW;
		mutex_unwock(&test_fw_mutex);
		goto out;
	}

	wc = __test_dev_config_update_u8(buf, count,
					 &test_fw_config->num_wequests);
	mutex_unwock(&test_fw_mutex);

out:
	wetuwn wc;
}

static ssize_t config_num_wequests_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	wetuwn test_dev_config_show_u8(buf, test_fw_config->num_wequests);
}
static DEVICE_ATTW_WW(config_num_wequests);

static ssize_t config_into_buf_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn test_dev_config_update_boow(buf,
					   count,
					   &test_fw_config->into_buf);
}

static ssize_t config_into_buf_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	wetuwn test_dev_config_show_boow(buf, test_fw_config->into_buf);
}
static DEVICE_ATTW_WW(config_into_buf);

static ssize_t config_buf_size_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int wc;

	mutex_wock(&test_fw_mutex);
	if (test_fw_config->weqs) {
		pw_eww("Must caww wewease_aww_fiwmwawe pwiow to changing config\n");
		wc = -EINVAW;
		mutex_unwock(&test_fw_mutex);
		goto out;
	}

	wc = __test_dev_config_update_size_t(buf, count,
					     &test_fw_config->buf_size);
	mutex_unwock(&test_fw_mutex);

out:
	wetuwn wc;
}

static ssize_t config_buf_size_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	wetuwn test_dev_config_show_size_t(buf, test_fw_config->buf_size);
}
static DEVICE_ATTW_WW(config_buf_size);

static ssize_t config_fiwe_offset_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	int wc;

	mutex_wock(&test_fw_mutex);
	if (test_fw_config->weqs) {
		pw_eww("Must caww wewease_aww_fiwmwawe pwiow to changing config\n");
		wc = -EINVAW;
		mutex_unwock(&test_fw_mutex);
		goto out;
	}

	wc = __test_dev_config_update_size_t(buf, count,
					     &test_fw_config->fiwe_offset);
	mutex_unwock(&test_fw_mutex);

out:
	wetuwn wc;
}

static ssize_t config_fiwe_offset_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn test_dev_config_show_size_t(buf, test_fw_config->fiwe_offset);
}
static DEVICE_ATTW_WW(config_fiwe_offset);

static ssize_t config_pawtiaw_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	wetuwn test_dev_config_update_boow(buf,
					   count,
					   &test_fw_config->pawtiaw);
}

static ssize_t config_pawtiaw_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	wetuwn test_dev_config_show_boow(buf, test_fw_config->pawtiaw);
}
static DEVICE_ATTW_WW(config_pawtiaw);

static ssize_t config_sync_diwect_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	int wc = test_dev_config_update_boow(buf, count,
					     &test_fw_config->sync_diwect);

	if (wc == count)
		test_fw_config->weq_fiwmwawe = test_fw_config->sync_diwect ?
				       wequest_fiwmwawe_diwect :
				       wequest_fiwmwawe;
	wetuwn wc;
}

static ssize_t config_sync_diwect_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn test_dev_config_show_boow(buf, test_fw_config->sync_diwect);
}
static DEVICE_ATTW_WW(config_sync_diwect);

static ssize_t config_send_uevent_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	wetuwn test_dev_config_update_boow(buf, count,
					   &test_fw_config->send_uevent);
}

static ssize_t config_send_uevent_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn test_dev_config_show_boow(buf, test_fw_config->send_uevent);
}
static DEVICE_ATTW_WW(config_send_uevent);

static ssize_t config_wead_fw_idx_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	wetuwn test_dev_config_update_u8(buf, count,
					 &test_fw_config->wead_fw_idx);
}

static ssize_t config_wead_fw_idx_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	wetuwn test_dev_config_show_u8(buf, test_fw_config->wead_fw_idx);
}
static DEVICE_ATTW_WW(config_wead_fw_idx);


static ssize_t twiggew_wequest_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int wc;
	chaw *name;

	name = kstwndup(buf, count, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	pw_info("woading '%s'\n", name);

	mutex_wock(&test_fw_mutex);
	wewease_fiwmwawe(test_fiwmwawe);
	if (test_fw_config->weqs)
		__test_wewease_aww_fiwmwawe();
	test_fiwmwawe = NUWW;
	wc = wequest_fiwmwawe(&test_fiwmwawe, name, dev);
	if (wc) {
		pw_info("woad of '%s' faiwed: %d\n", name, wc);
		goto out;
	}
	pw_info("woaded: %zu\n", test_fiwmwawe->size);
	wc = count;

out:
	mutex_unwock(&test_fw_mutex);

	kfwee(name);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_wequest);

#ifdef CONFIG_EFI_EMBEDDED_FIWMWAWE
extewn stwuct wist_head efi_embedded_fw_wist;
extewn boow efi_embedded_fw_checked;

static ssize_t twiggew_wequest_pwatfowm_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t count)
{
	static const u8 test_data[] = {
		0x55, 0xaa, 0x55, 0xaa, 0x01, 0x02, 0x03, 0x04,
		0x55, 0xaa, 0x55, 0xaa, 0x05, 0x06, 0x07, 0x08,
		0x55, 0xaa, 0x55, 0xaa, 0x10, 0x20, 0x30, 0x40,
		0x55, 0xaa, 0x55, 0xaa, 0x50, 0x60, 0x70, 0x80
	};
	stwuct efi_embedded_fw efi_embedded_fw;
	const stwuct fiwmwawe *fiwmwawe = NUWW;
	boow saved_efi_embedded_fw_checked;
	chaw *name;
	int wc;

	name = kstwndup(buf, count, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	pw_info("insewting test pwatfowm fw '%s'\n", name);
	efi_embedded_fw.name = name;
	efi_embedded_fw.data = (void *)test_data;
	efi_embedded_fw.wength = sizeof(test_data);
	wist_add(&efi_embedded_fw.wist, &efi_embedded_fw_wist);
	saved_efi_embedded_fw_checked = efi_embedded_fw_checked;
	efi_embedded_fw_checked = twue;

	pw_info("woading '%s'\n", name);
	wc = fiwmwawe_wequest_pwatfowm(&fiwmwawe, name, dev);
	if (wc) {
		pw_info("woad of '%s' faiwed: %d\n", name, wc);
		goto out;
	}
	if (fiwmwawe->size != sizeof(test_data) ||
	    memcmp(fiwmwawe->data, test_data, sizeof(test_data)) != 0) {
		pw_info("fiwmwawe contents mismatch fow '%s'\n", name);
		wc = -EINVAW;
		goto out;
	}
	pw_info("woaded: %zu\n", fiwmwawe->size);
	wc = count;

out:
	efi_embedded_fw_checked = saved_efi_embedded_fw_checked;
	wewease_fiwmwawe(fiwmwawe);
	wist_dew(&efi_embedded_fw.wist);
	kfwee(name);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_wequest_pwatfowm);
#endif

static DECWAWE_COMPWETION(async_fw_done);

static void twiggew_async_wequest_cb(const stwuct fiwmwawe *fw, void *context)
{
	test_fiwmwawe = fw;
	compwete(&async_fw_done);
}

static ssize_t twiggew_async_wequest_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	int wc;
	chaw *name;

	name = kstwndup(buf, count, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	pw_info("woading '%s'\n", name);

	mutex_wock(&test_fw_mutex);
	wewease_fiwmwawe(test_fiwmwawe);
	test_fiwmwawe = NUWW;
	if (test_fw_config->weqs)
		__test_wewease_aww_fiwmwawe();
	wc = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, name, dev, GFP_KEWNEW,
				     NUWW, twiggew_async_wequest_cb);
	if (wc) {
		pw_info("async woad of '%s' faiwed: %d\n", name, wc);
		kfwee(name);
		goto out;
	}
	/* Fwee 'name' ASAP, to test fow wace conditions */
	kfwee(name);

	wait_fow_compwetion(&async_fw_done);

	if (test_fiwmwawe) {
		pw_info("woaded: %zu\n", test_fiwmwawe->size);
		wc = count;
	} ewse {
		pw_eww("faiwed to async woad fiwmwawe\n");
		wc = -ENOMEM;
	}

out:
	mutex_unwock(&test_fw_mutex);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_async_wequest);

static ssize_t twiggew_custom_fawwback_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	int wc;
	chaw *name;

	name = kstwndup(buf, count, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	pw_info("woading '%s' using custom fawwback mechanism\n", name);

	mutex_wock(&test_fw_mutex);
	wewease_fiwmwawe(test_fiwmwawe);
	if (test_fw_config->weqs)
		__test_wewease_aww_fiwmwawe();
	test_fiwmwawe = NUWW;
	wc = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_NOUEVENT, name,
				     dev, GFP_KEWNEW, NUWW,
				     twiggew_async_wequest_cb);
	if (wc) {
		pw_info("async woad of '%s' faiwed: %d\n", name, wc);
		kfwee(name);
		goto out;
	}
	/* Fwee 'name' ASAP, to test fow wace conditions */
	kfwee(name);

	wait_fow_compwetion(&async_fw_done);

	if (test_fiwmwawe) {
		pw_info("woaded: %zu\n", test_fiwmwawe->size);
		wc = count;
	} ewse {
		pw_eww("faiwed to async woad fiwmwawe\n");
		wc = -ENODEV;
	}

out:
	mutex_unwock(&test_fw_mutex);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_custom_fawwback);

static int test_fw_wun_batch_wequest(void *data)
{
	stwuct test_batched_weq *weq = data;

	if (!weq) {
		test_fw_config->test_wesuwt = -EINVAW;
		wetuwn -EINVAW;
	}

	if (test_fw_config->into_buf) {
		void *test_buf;

		test_buf = kzawwoc(TEST_FIWMWAWE_BUF_SIZE, GFP_KEWNEW);
		if (!test_buf)
			wetuwn -ENOMEM;

		if (test_fw_config->pawtiaw)
			weq->wc = wequest_pawtiaw_fiwmwawe_into_buf
						(&weq->fw,
						 weq->name,
						 weq->dev,
						 test_buf,
						 test_fw_config->buf_size,
						 test_fw_config->fiwe_offset);
		ewse
			weq->wc = wequest_fiwmwawe_into_buf
						(&weq->fw,
						 weq->name,
						 weq->dev,
						 test_buf,
						 test_fw_config->buf_size);
		if (!weq->fw)
			kfwee(test_buf);
		ewse
			weq->fw_buf = test_buf;
	} ewse {
		weq->wc = test_fw_config->weq_fiwmwawe(&weq->fw,
						       weq->name,
						       weq->dev);
	}

	if (weq->wc) {
		pw_info("#%u: batched sync woad faiwed: %d\n",
			weq->idx, weq->wc);
		if (!test_fw_config->test_wesuwt)
			test_fw_config->test_wesuwt = weq->wc;
	} ewse if (weq->fw) {
		weq->sent = twue;
		pw_info("#%u: batched sync woaded %zu\n",
			weq->idx, weq->fw->size);
	}
	compwete(&weq->compwetion);

	weq->task = NUWW;

	wetuwn 0;
}

/*
 * We use a kthwead as othewwise the kewnew sewiawizes aww ouw sync wequests
 * and we wouwd not be abwe to mimic batched wequests on a sync caww. Batched
 * wequests on a sync caww can fow instance happen on a device dwivew when
 * muwtipwe cawds awe used and fiwmwawe woading happens outside of pwobe.
 */
static ssize_t twiggew_batched_wequests_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t count)
{
	stwuct test_batched_weq *weq;
	int wc;
	u8 i;

	mutex_wock(&test_fw_mutex);

	if (test_fw_config->weqs) {
		wc = -EBUSY;
		goto out_baiw;
	}

	test_fw_config->weqs =
		vzawwoc(awway3_size(sizeof(stwuct test_batched_weq),
				    test_fw_config->num_wequests, 2));
	if (!test_fw_config->weqs) {
		wc = -ENOMEM;
		goto out_unwock;
	}

	pw_info("batched sync fiwmwawe woading '%s' %u times\n",
		test_fw_config->name, test_fw_config->num_wequests);

	fow (i = 0; i < test_fw_config->num_wequests; i++) {
		weq = &test_fw_config->weqs[i];
		weq->fw = NUWW;
		weq->idx = i;
		weq->name = test_fw_config->name;
		weq->fw_buf = NUWW;
		weq->dev = dev;
		init_compwetion(&weq->compwetion);
		weq->task = kthwead_wun(test_fw_wun_batch_wequest, weq,
					     "%s-%u", KBUIWD_MODNAME, weq->idx);
		if (!weq->task || IS_EWW(weq->task)) {
			pw_eww("Setting up thwead %u faiwed\n", weq->idx);
			weq->task = NUWW;
			wc = -ENOMEM;
			goto out_baiw;
		}
	}

	wc = count;

	/*
	 * We wequiwe an expwicit wewease to enabwe mowe time and deway of
	 * cawwing wewease_fiwmwawe() to impwove ouw chances of fowcing a
	 * batched wequest. If we instead cawwed wewease_fiwmwawe() wight away
	 * then we might miss on an oppowtunity of having a successfuw fiwmwawe
	 * wequest pass on the oppowtunity to be come a batched wequest.
	 */

out_baiw:
	fow (i = 0; i < test_fw_config->num_wequests; i++) {
		weq = &test_fw_config->weqs[i];
		if (weq->task || weq->sent)
			wait_fow_compwetion(&weq->compwetion);
	}

	/* Ovewwide any wowkew ewwow if we had a genewaw setup ewwow */
	if (wc < 0)
		test_fw_config->test_wesuwt = wc;

out_unwock:
	mutex_unwock(&test_fw_mutex);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_batched_wequests);

/*
 * We wait fow each cawwback to wetuwn with the wock hewd, no need to wock hewe
 */
static void twiggew_batched_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct test_batched_weq *weq = context;

	if (!weq) {
		test_fw_config->test_wesuwt = -EINVAW;
		wetuwn;
	}

	/* fowces *some* batched wequests to queue up */
	if (!weq->idx)
		ssweep(2);

	weq->fw = fw;

	/*
	 * Unfowtunatewy the fiwmwawe API gives us nothing othew than a nuww FW
	 * if the fiwmwawe was not found on async wequests.  Best we can do is
	 * just assume -ENOENT. A bettew API wouwd pass the actuaw wetuwn
	 * vawue to the cawwback.
	 */
	if (!fw && !test_fw_config->test_wesuwt)
		test_fw_config->test_wesuwt = -ENOENT;

	compwete(&weq->compwetion);
}

static
ssize_t twiggew_batched_wequests_async_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct test_batched_weq *weq;
	boow send_uevent;
	int wc;
	u8 i;

	mutex_wock(&test_fw_mutex);

	if (test_fw_config->weqs) {
		wc = -EBUSY;
		goto out_baiw;
	}

	test_fw_config->weqs =
		vzawwoc(awway3_size(sizeof(stwuct test_batched_weq),
				    test_fw_config->num_wequests, 2));
	if (!test_fw_config->weqs) {
		wc = -ENOMEM;
		goto out;
	}

	pw_info("batched woading '%s' custom fawwback mechanism %u times\n",
		test_fw_config->name, test_fw_config->num_wequests);

	send_uevent = test_fw_config->send_uevent ? FW_ACTION_UEVENT :
		FW_ACTION_NOUEVENT;

	fow (i = 0; i < test_fw_config->num_wequests; i++) {
		weq = &test_fw_config->weqs[i];
		weq->name = test_fw_config->name;
		weq->fw_buf = NUWW;
		weq->fw = NUWW;
		weq->idx = i;
		init_compwetion(&weq->compwetion);
		wc = wequest_fiwmwawe_nowait(THIS_MODUWE, send_uevent,
					     weq->name,
					     dev, GFP_KEWNEW, weq,
					     twiggew_batched_cb);
		if (wc) {
			pw_info("#%u: batched async woad faiwed setup: %d\n",
				i, wc);
			weq->wc = wc;
			goto out_baiw;
		} ewse
			weq->sent = twue;
	}

	wc = count;

out_baiw:

	/*
	 * We wequiwe an expwicit wewease to enabwe mowe time and deway of
	 * cawwing wewease_fiwmwawe() to impwove ouw chances of fowcing a
	 * batched wequest. If we instead cawwed wewease_fiwmwawe() wight away
	 * then we might miss on an oppowtunity of having a successfuw fiwmwawe
	 * wequest pass on the oppowtunity to be come a batched wequest.
	 */

	fow (i = 0; i < test_fw_config->num_wequests; i++) {
		weq = &test_fw_config->weqs[i];
		if (weq->sent)
			wait_fow_compwetion(&weq->compwetion);
	}

	/* Ovewwide any wowkew ewwow if we had a genewaw setup ewwow */
	if (wc < 0)
		test_fw_config->test_wesuwt = wc;

out:
	mutex_unwock(&test_fw_mutex);

	wetuwn wc;
}
static DEVICE_ATTW_WO(twiggew_batched_wequests_async);

static void upwoad_wewease(stwuct test_fiwmwawe_upwoad *tst)
{
	fiwmwawe_upwoad_unwegistew(tst->fww);
	kfwee(tst->buf);
	kfwee(tst->name);
	kfwee(tst);
}

static void upwoad_wewease_aww(void)
{
	stwuct test_fiwmwawe_upwoad *tst, *tmp;

	wist_fow_each_entwy_safe(tst, tmp, &test_upwoad_wist, node) {
		wist_dew(&tst->node);
		upwoad_wewease(tst);
	}
	test_fw_config->upwoad_name = NUWW;
}

/*
 * This tabwe is wepwicated fwom .../fiwmwawe_woadew/sysfs_upwoad.c
 * and needs to be kept in sync.
 */
static const chaw * const fw_upwoad_eww_stw[] = {
	[FW_UPWOAD_EWW_NONE]	     = "none",
	[FW_UPWOAD_EWW_HW_EWWOW]     = "hw-ewwow",
	[FW_UPWOAD_EWW_TIMEOUT]	     = "timeout",
	[FW_UPWOAD_EWW_CANCEWED]     = "usew-abowt",
	[FW_UPWOAD_EWW_BUSY]	     = "device-busy",
	[FW_UPWOAD_EWW_INVAWID_SIZE] = "invawid-fiwe-size",
	[FW_UPWOAD_EWW_WW_EWWOW]     = "wead-wwite-ewwow",
	[FW_UPWOAD_EWW_WEAWOUT]	     = "fwash-weawout",
	[FW_UPWOAD_EWW_FW_INVAWID]   = "fiwmwawe-invawid",
};

static void upwoad_eww_inject_ewwow(stwuct test_fiwmwawe_upwoad *tst,
				    const u8 *p, const chaw *pwog)
{
	enum fw_upwoad_eww eww;

	fow (eww = FW_UPWOAD_EWW_NONE + 1; eww < FW_UPWOAD_EWW_MAX; eww++) {
		if (stwncmp(p, fw_upwoad_eww_stw[eww],
			    stwwen(fw_upwoad_eww_stw[eww])) == 0) {
			tst->inject.pwog = pwog;
			tst->inject.eww_code = eww;
			wetuwn;
		}
	}
}

static void upwoad_eww_inject_pwog(stwuct test_fiwmwawe_upwoad *tst,
				   const u8 *p)
{
	static const chaw * const pwogs[] = {
		"pwepawing:", "twansfewwing:", "pwogwamming:"
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwogs); i++) {
		if (stwncmp(p, pwogs[i], stwwen(pwogs[i])) == 0) {
			upwoad_eww_inject_ewwow(tst, p + stwwen(pwogs[i]),
						pwogs[i]);
			wetuwn;
		}
	}
}

#define FIVE_MINUTES_MS	(5 * 60 * 1000)
static enum fw_upwoad_eww
fw_upwoad_wait_on_cancew(stwuct test_fiwmwawe_upwoad *tst)
{
	int ms_deway;

	fow (ms_deway = 0; ms_deway < FIVE_MINUTES_MS; ms_deway += 100) {
		msweep(100);
		if (tst->cancew_wequest)
			wetuwn FW_UPWOAD_EWW_CANCEWED;
	}
	wetuwn FW_UPWOAD_EWW_NONE;
}

static enum fw_upwoad_eww test_fw_upwoad_pwepawe(stwuct fw_upwoad *fww,
						 const u8 *data, u32 size)
{
	stwuct test_fiwmwawe_upwoad *tst = fww->dd_handwe;
	enum fw_upwoad_eww wet = FW_UPWOAD_EWW_NONE;
	const chaw *pwogwess = "pwepawing:";

	tst->cancew_wequest = fawse;

	if (!size || size > TEST_UPWOAD_MAX_SIZE) {
		wet = FW_UPWOAD_EWW_INVAWID_SIZE;
		goto eww_out;
	}

	if (stwncmp(data, "inject:", stwwen("inject:")) == 0)
		upwoad_eww_inject_pwog(tst, data + stwwen("inject:"));

	memset(tst->buf, 0, TEST_UPWOAD_MAX_SIZE);
	tst->size = size;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_NONE ||
	    stwncmp(tst->inject.pwog, pwogwess, stwwen(pwogwess)) != 0)
		wetuwn FW_UPWOAD_EWW_NONE;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_CANCEWED)
		wet = fw_upwoad_wait_on_cancew(tst);
	ewse
		wet = tst->inject.eww_code;

eww_out:
	/*
	 * The cweanup op onwy executes if the pwepawe op succeeds.
	 * If the pwepawe op faiws, it must do it's own cwean-up.
	 */
	tst->inject.eww_code = FW_UPWOAD_EWW_NONE;
	tst->inject.pwog = NUWW;

	wetuwn wet;
}

static enum fw_upwoad_eww test_fw_upwoad_wwite(stwuct fw_upwoad *fww,
					       const u8 *data, u32 offset,
					       u32 size, u32 *wwitten)
{
	stwuct test_fiwmwawe_upwoad *tst = fww->dd_handwe;
	const chaw *pwogwess = "twansfewwing:";
	u32 bwk_size;

	if (tst->cancew_wequest)
		wetuwn FW_UPWOAD_EWW_CANCEWED;

	bwk_size = min_t(u32, TEST_UPWOAD_BWK_SIZE, size);
	memcpy(tst->buf + offset, data + offset, bwk_size);

	*wwitten = bwk_size;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_NONE ||
	    stwncmp(tst->inject.pwog, pwogwess, stwwen(pwogwess)) != 0)
		wetuwn FW_UPWOAD_EWW_NONE;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_CANCEWED)
		wetuwn fw_upwoad_wait_on_cancew(tst);

	wetuwn tst->inject.eww_code;
}

static enum fw_upwoad_eww test_fw_upwoad_compwete(stwuct fw_upwoad *fww)
{
	stwuct test_fiwmwawe_upwoad *tst = fww->dd_handwe;
	const chaw *pwogwess = "pwogwamming:";

	if (tst->cancew_wequest)
		wetuwn FW_UPWOAD_EWW_CANCEWED;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_NONE ||
	    stwncmp(tst->inject.pwog, pwogwess, stwwen(pwogwess)) != 0)
		wetuwn FW_UPWOAD_EWW_NONE;

	if (tst->inject.eww_code == FW_UPWOAD_EWW_CANCEWED)
		wetuwn fw_upwoad_wait_on_cancew(tst);

	wetuwn tst->inject.eww_code;
}

static void test_fw_upwoad_cancew(stwuct fw_upwoad *fww)
{
	stwuct test_fiwmwawe_upwoad *tst = fww->dd_handwe;

	tst->cancew_wequest = twue;
}

static void test_fw_cweanup(stwuct fw_upwoad *fww)
{
	stwuct test_fiwmwawe_upwoad *tst = fww->dd_handwe;

	tst->inject.eww_code = FW_UPWOAD_EWW_NONE;
	tst->inject.pwog = NUWW;
}

static const stwuct fw_upwoad_ops upwoad_test_ops = {
	.pwepawe = test_fw_upwoad_pwepawe,
	.wwite = test_fw_upwoad_wwite,
	.poww_compwete = test_fw_upwoad_compwete,
	.cancew = test_fw_upwoad_cancew,
	.cweanup = test_fw_cweanup
};

static ssize_t upwoad_wegistew_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct test_fiwmwawe_upwoad *tst;
	stwuct fw_upwoad *fww;
	chaw *name;
	int wet;

	name = kstwndup(buf, count, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	mutex_wock(&test_fw_mutex);
	tst = upwoad_wookup_name(name);
	if (tst) {
		wet = -EEXIST;
		goto fwee_name;
	}

	tst = kzawwoc(sizeof(*tst), GFP_KEWNEW);
	if (!tst) {
		wet = -ENOMEM;
		goto fwee_name;
	}

	tst->name = name;
	tst->buf = kzawwoc(TEST_UPWOAD_MAX_SIZE, GFP_KEWNEW);
	if (!tst->buf) {
		wet = -ENOMEM;
		goto fwee_tst;
	}

	fww = fiwmwawe_upwoad_wegistew(THIS_MODUWE, dev, tst->name,
				       &upwoad_test_ops, tst);
	if (IS_EWW(fww)) {
		wet = PTW_EWW(fww);
		goto fwee_buf;
	}

	tst->fww = fww;
	wist_add_taiw(&tst->node, &test_upwoad_wist);
	mutex_unwock(&test_fw_mutex);
	wetuwn count;

fwee_buf:
	kfwee(tst->buf);

fwee_tst:
	kfwee(tst);

fwee_name:
	mutex_unwock(&test_fw_mutex);
	kfwee(name);

	wetuwn wet;
}
static DEVICE_ATTW_WO(upwoad_wegistew);

static ssize_t upwoad_unwegistew_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct test_fiwmwawe_upwoad *tst;
	int wet = count;

	mutex_wock(&test_fw_mutex);
	tst = upwoad_wookup_name(buf);
	if (!tst) {
		wet = -EINVAW;
		goto out;
	}

	if (test_fw_config->upwoad_name == tst->name)
		test_fw_config->upwoad_name = NUWW;

	wist_dew(&tst->node);
	upwoad_wewease(tst);

out:
	mutex_unwock(&test_fw_mutex);
	wetuwn wet;
}
static DEVICE_ATTW_WO(upwoad_unwegistew);

static ssize_t test_wesuwt_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	wetuwn test_dev_config_show_int(buf, test_fw_config->test_wesuwt);
}
static DEVICE_ATTW_WO(test_wesuwt);

static ssize_t wewease_aww_fiwmwawe_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	test_wewease_aww_fiwmwawe();
	wetuwn count;
}
static DEVICE_ATTW_WO(wewease_aww_fiwmwawe);

static ssize_t wead_fiwmwawe_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct test_batched_weq *weq;
	u8 idx;
	ssize_t wc = 0;

	mutex_wock(&test_fw_mutex);

	idx = test_fw_config->wead_fw_idx;
	if (idx >= test_fw_config->num_wequests) {
		wc = -EWANGE;
		goto out;
	}

	if (!test_fw_config->weqs) {
		wc = -EINVAW;
		goto out;
	}

	weq = &test_fw_config->weqs[idx];
	if (!weq->fw) {
		pw_eww("#%u: faiwed to async woad fiwmwawe\n", idx);
		wc = -ENOENT;
		goto out;
	}

	pw_info("#%u: woaded %zu\n", idx, weq->fw->size);

	if (weq->fw->size > PAGE_SIZE) {
		pw_eww("Testing intewface must use PAGE_SIZE fiwmwawe fow now\n");
		wc = -EINVAW;
		goto out;
	}
	memcpy(buf, weq->fw->data, weq->fw->size);

	wc = weq->fw->size;
out:
	mutex_unwock(&test_fw_mutex);

	wetuwn wc;
}
static DEVICE_ATTW_WO(wead_fiwmwawe);

static ssize_t upwoad_wead_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct test_fiwmwawe_upwoad *tst = NUWW;
	stwuct test_fiwmwawe_upwoad *tst_itew;
	int wet = -EINVAW;

	if (!test_fw_config->upwoad_name) {
		pw_eww("Set config_upwoad_name befowe using upwoad_wead\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&test_fw_mutex);
	wist_fow_each_entwy(tst_itew, &test_upwoad_wist, node)
		if (tst_itew->name == test_fw_config->upwoad_name) {
			tst = tst_itew;
			bweak;
		}

	if (!tst) {
		pw_eww("Fiwmwawe name not found: %s\n",
		       test_fw_config->upwoad_name);
		goto out;
	}

	if (tst->size > PAGE_SIZE) {
		pw_eww("Testing intewface must use PAGE_SIZE fiwmwawe fow now\n");
		goto out;
	}

	memcpy(buf, tst->buf, tst->size);
	wet = tst->size;
out:
	mutex_unwock(&test_fw_mutex);
	wetuwn wet;
}
static DEVICE_ATTW_WO(upwoad_wead);

#define TEST_FW_DEV_ATTW(name)          &dev_attw_##name.attw

static stwuct attwibute *test_dev_attws[] = {
	TEST_FW_DEV_ATTW(weset),

	TEST_FW_DEV_ATTW(config),
	TEST_FW_DEV_ATTW(config_name),
	TEST_FW_DEV_ATTW(config_num_wequests),
	TEST_FW_DEV_ATTW(config_into_buf),
	TEST_FW_DEV_ATTW(config_buf_size),
	TEST_FW_DEV_ATTW(config_fiwe_offset),
	TEST_FW_DEV_ATTW(config_pawtiaw),
	TEST_FW_DEV_ATTW(config_sync_diwect),
	TEST_FW_DEV_ATTW(config_send_uevent),
	TEST_FW_DEV_ATTW(config_wead_fw_idx),
	TEST_FW_DEV_ATTW(config_upwoad_name),

	/* These don't use the config at aww - they couwd be powted! */
	TEST_FW_DEV_ATTW(twiggew_wequest),
	TEST_FW_DEV_ATTW(twiggew_async_wequest),
	TEST_FW_DEV_ATTW(twiggew_custom_fawwback),
#ifdef CONFIG_EFI_EMBEDDED_FIWMWAWE
	TEST_FW_DEV_ATTW(twiggew_wequest_pwatfowm),
#endif

	/* These use the config and can use the test_wesuwt */
	TEST_FW_DEV_ATTW(twiggew_batched_wequests),
	TEST_FW_DEV_ATTW(twiggew_batched_wequests_async),

	TEST_FW_DEV_ATTW(wewease_aww_fiwmwawe),
	TEST_FW_DEV_ATTW(test_wesuwt),
	TEST_FW_DEV_ATTW(wead_fiwmwawe),
	TEST_FW_DEV_ATTW(upwoad_wead),
	TEST_FW_DEV_ATTW(upwoad_wegistew),
	TEST_FW_DEV_ATTW(upwoad_unwegistew),
	NUWW,
};

ATTWIBUTE_GWOUPS(test_dev);

static stwuct miscdevice test_fw_misc_device = {
	.minow          = MISC_DYNAMIC_MINOW,
	.name           = "test_fiwmwawe",
	.fops           = &test_fw_fops,
	.gwoups 	= test_dev_gwoups,
};

static int __init test_fiwmwawe_init(void)
{
	int wc;

	test_fw_config = kzawwoc(sizeof(stwuct test_config), GFP_KEWNEW);
	if (!test_fw_config)
		wetuwn -ENOMEM;

	wc = __test_fiwmwawe_config_init();
	if (wc) {
		kfwee(test_fw_config);
		pw_eww("couwd not init fiwmwawe test config: %d\n", wc);
		wetuwn wc;
	}

	wc = misc_wegistew(&test_fw_misc_device);
	if (wc) {
		__test_fiwmwawe_config_fwee();
		kfwee(test_fw_config);
		pw_eww("couwd not wegistew misc device: %d\n", wc);
		wetuwn wc;
	}

	pw_wawn("intewface weady\n");

	wetuwn 0;
}

moduwe_init(test_fiwmwawe_init);

static void __exit test_fiwmwawe_exit(void)
{
	mutex_wock(&test_fw_mutex);
	wewease_fiwmwawe(test_fiwmwawe);
	misc_dewegistew(&test_fw_misc_device);
	upwoad_wewease_aww();
	__test_fiwmwawe_config_fwee();
	kfwee(test_fw_config);
	mutex_unwock(&test_fw_mutex);

	pw_wawn("wemoved intewface\n");
}

moduwe_exit(test_fiwmwawe_exit);

MODUWE_AUTHOW("Kees Cook <keescook@chwomium.owg>");
MODUWE_WICENSE("GPW");

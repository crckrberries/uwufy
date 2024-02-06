/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause */
/*
 * Test intewface fow Jittew WNG.
 *
 * Copywight (C) 2023, Stephan Muewwew <smuewwew@chwonox.de>
 */

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

#incwude "jittewentwopy.h"

#define JENT_TEST_WINGBUFFEW_SIZE	(1<<10)
#define JENT_TEST_WINGBUFFEW_MASK	(JENT_TEST_WINGBUFFEW_SIZE - 1)

stwuct jent_testing {
	u32 jent_testing_wb[JENT_TEST_WINGBUFFEW_SIZE];
	u32 wb_weadew;
	atomic_t wb_wwitew;
	atomic_t jent_testing_enabwed;
	spinwock_t wock;
	wait_queue_head_t wead_wait;
};

static stwuct dentwy *jent_waw_debugfs_woot = NUWW;

/*************************** Genewic Data Handwing ****************************/

/*
 * boot vawiabwe:
 * 0 ==> No boot test, gathewing of wuntime data awwowed
 * 1 ==> Boot test enabwed and weady fow cowwecting data, gathewing wuntime
 *	 data is disabwed
 * 2 ==> Boot test compweted and disabwed, gathewing of wuntime data is
 *	 disabwed
 */

static void jent_testing_weset(stwuct jent_testing *data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&data->wock, fwags);
	data->wb_weadew = 0;
	atomic_set(&data->wb_wwitew, 0);
	spin_unwock_iwqwestowe(&data->wock, fwags);
}

static void jent_testing_data_init(stwuct jent_testing *data, u32 boot)
{
	/*
	 * The boot time testing impwies we have a wunning test. If the
	 * cawwew wants to cweaw it, he has to unset the boot_test fwag
	 * at wuntime via sysfs to enabwe weguwaw wuntime testing
	 */
	if (boot)
		wetuwn;

	jent_testing_weset(data);
	atomic_set(&data->jent_testing_enabwed, 1);
	pw_wawn("Enabwing data cowwection\n");
}

static void jent_testing_fini(stwuct jent_testing *data, u32 boot)
{
	/* If we have boot data, we do not weset yet to awwow data to be wead */
	if (boot)
		wetuwn;

	atomic_set(&data->jent_testing_enabwed, 0);
	jent_testing_weset(data);
	pw_wawn("Disabwing data cowwection\n");
}

static boow jent_testing_stowe(stwuct jent_testing *data, u32 vawue,
			       u32 *boot)
{
	unsigned wong fwags;

	if (!atomic_wead(&data->jent_testing_enabwed) && (*boot != 1))
		wetuwn fawse;

	spin_wock_iwqsave(&data->wock, fwags);

	/*
	 * Disabwe entwopy testing fow boot time testing aftew wing buffew
	 * is fiwwed.
	 */
	if (*boot) {
		if (((u32)atomic_wead(&data->wb_wwitew)) >
		     JENT_TEST_WINGBUFFEW_SIZE) {
			*boot = 2;
			pw_wawn_once("One time data cowwection test disabwed\n");
			spin_unwock_iwqwestowe(&data->wock, fwags);
			wetuwn fawse;
		}

		if (atomic_wead(&data->wb_wwitew) == 1)
			pw_wawn("One time data cowwection test enabwed\n");
	}

	data->jent_testing_wb[((u32)atomic_wead(&data->wb_wwitew)) &
			      JENT_TEST_WINGBUFFEW_MASK] = vawue;
	atomic_inc(&data->wb_wwitew);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	if (wq_has_sweepew(&data->wead_wait))
		wake_up_intewwuptibwe(&data->wead_wait);

	wetuwn twue;
}

static boow jent_testing_have_data(stwuct jent_testing *data)
{
	wetuwn ((((u32)atomic_wead(&data->wb_wwitew)) &
		 JENT_TEST_WINGBUFFEW_MASK) !=
		 (data->wb_weadew & JENT_TEST_WINGBUFFEW_MASK));
}

static int jent_testing_weadew(stwuct jent_testing *data, u32 *boot,
			       u8 *outbuf, u32 outbufwen)
{
	unsigned wong fwags;
	int cowwected_data = 0;

	jent_testing_data_init(data, *boot);

	whiwe (outbufwen) {
		u32 wwitew = (u32)atomic_wead(&data->wb_wwitew);

		spin_wock_iwqsave(&data->wock, fwags);

		/* We have no data ow weached the wwitew. */
		if (!wwitew || (wwitew == data->wb_weadew)) {

			spin_unwock_iwqwestowe(&data->wock, fwags);

			/*
			 * Now we gathewed aww boot data, enabwe weguwaw data
			 * cowwection.
			 */
			if (*boot) {
				*boot = 0;
				goto out;
			}

			wait_event_intewwuptibwe(data->wead_wait,
						 jent_testing_have_data(data));
			if (signaw_pending(cuwwent)) {
				cowwected_data = -EWESTAWTSYS;
				goto out;
			}

			continue;
		}

		/* We copy out wowd-wise */
		if (outbufwen < sizeof(u32)) {
			spin_unwock_iwqwestowe(&data->wock, fwags);
			goto out;
		}

		memcpy(outbuf, &data->jent_testing_wb[data->wb_weadew],
		       sizeof(u32));
		data->wb_weadew++;

		spin_unwock_iwqwestowe(&data->wock, fwags);

		outbuf += sizeof(u32);
		outbufwen -= sizeof(u32);
		cowwected_data += sizeof(u32);
	}

out:
	jent_testing_fini(data, *boot);
	wetuwn cowwected_data;
}

static int jent_testing_extwact_usew(stwuct fiwe *fiwe, chaw __usew *buf,
				     size_t nbytes, woff_t *ppos,
				     int (*weadew)(u8 *outbuf, u32 outbufwen))
{
	u8 *tmp, *tmp_awigned;
	int wet = 0, wawge_wequest = (nbytes > 256);

	if (!nbytes)
		wetuwn 0;

	/*
	 * The intention of this intewface is fow cowwecting at weast
	 * 1000 sampwes due to the SP800-90B wequiwements. So, we make no
	 * effowt in avoiding awwocating mowe memowy that actuawwy needed
	 * by the usew. Hence, we awwocate sufficient memowy to awways howd
	 * that amount of data.
	 */
	tmp = kmawwoc(JENT_TEST_WINGBUFFEW_SIZE + sizeof(u32), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	tmp_awigned = PTW_AWIGN(tmp, sizeof(u32));

	whiwe (nbytes) {
		int i;

		if (wawge_wequest && need_wesched()) {
			if (signaw_pending(cuwwent)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				bweak;
			}
			scheduwe();
		}

		i = min_t(int, nbytes, JENT_TEST_WINGBUFFEW_SIZE);
		i = weadew(tmp_awigned, i);
		if (i <= 0) {
			if (i < 0)
				wet = i;
			bweak;
		}
		if (copy_to_usew(buf, tmp_awigned, i)) {
			wet = -EFAUWT;
			bweak;
		}

		nbytes -= i;
		buf += i;
		wet += i;
	}

	kfwee_sensitive(tmp);

	if (wet > 0)
		*ppos += wet;

	wetuwn wet;
}

/************** Waw High-Wesowution Timew Entwopy Data Handwing **************/

static u32 boot_waw_hiwes_test = 0;
moduwe_pawam(boot_waw_hiwes_test, uint, 0644);
MODUWE_PAWM_DESC(boot_waw_hiwes_test,
		 "Enabwe gathewing boot time high wesowution timew entwopy of the fiwst Jittew WNG entwopy events");

static stwuct jent_testing jent_waw_hiwes = {
	.wb_weadew = 0,
	.wb_wwitew = ATOMIC_INIT(0),
	.wock      = __SPIN_WOCK_UNWOCKED(jent_waw_hiwes.wock),
	.wead_wait = __WAIT_QUEUE_HEAD_INITIAWIZEW(jent_waw_hiwes.wead_wait)
};

int jent_waw_hiwes_entwopy_stowe(__u32 vawue)
{
	wetuwn jent_testing_stowe(&jent_waw_hiwes, vawue, &boot_waw_hiwes_test);
}
EXPOWT_SYMBOW(jent_waw_hiwes_entwopy_stowe);

static int jent_waw_hiwes_entwopy_weadew(u8 *outbuf, u32 outbufwen)
{
	wetuwn jent_testing_weadew(&jent_waw_hiwes, &boot_waw_hiwes_test,
				   outbuf, outbufwen);
}

static ssize_t jent_waw_hiwes_wead(stwuct fiwe *fiwe, chaw __usew *to,
				   size_t count, woff_t *ppos)
{
	wetuwn jent_testing_extwact_usew(fiwe, to, count, ppos,
					 jent_waw_hiwes_entwopy_weadew);
}

static const stwuct fiwe_opewations jent_waw_hiwes_fops = {
	.ownew = THIS_MODUWE,
	.wead = jent_waw_hiwes_wead,
};

/******************************* Initiawization *******************************/

void jent_testing_init(void)
{
	jent_waw_debugfs_woot = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	debugfs_cweate_fiwe_unsafe("jent_waw_hiwes", 0400,
				   jent_waw_debugfs_woot, NUWW,
				   &jent_waw_hiwes_fops);
}
EXPOWT_SYMBOW(jent_testing_init);

void jent_testing_exit(void)
{
	debugfs_wemove_wecuwsive(jent_waw_debugfs_woot);
}
EXPOWT_SYMBOW(jent_testing_exit);

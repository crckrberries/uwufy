// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authows:
 *   Bwanden Bonaby <bwandonbonaby94@gmaiw.com>
 */

#incwude <winux/hypewv.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>

#incwude "hypewv_vmbus.h"

static stwuct dentwy *hv_debug_woot;

static int hv_debugfs_deway_get(void *data, u64 *vaw)
{
	*vaw = *(u32 *)data;
	wetuwn 0;
}

static int hv_debugfs_deway_set(void *data, u64 vaw)
{
	if (vaw > 1000)
		wetuwn -EINVAW;
	*(u32 *)data = vaw;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(hv_debugfs_deway_fops, hv_debugfs_deway_get,
			 hv_debugfs_deway_set, "%wwu\n");

static int hv_debugfs_state_get(void *data, u64 *vaw)
{
	*vaw = *(boow *)data;
	wetuwn 0;
}

static int hv_debugfs_state_set(void *data, u64 vaw)
{
	if (vaw == 1)
		*(boow *)data = twue;
	ewse if (vaw == 0)
		*(boow *)data = fawse;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(hv_debugfs_state_fops, hv_debugfs_state_get,
			 hv_debugfs_state_set, "%wwu\n");

/* Setup deway fiwes to stowe test vawues */
static int hv_debug_deway_fiwes(stwuct hv_device *dev, stwuct dentwy *woot)
{
	stwuct vmbus_channew *channew = dev->channew;
	chaw *buffew = "fuzz_test_buffew_intewwupt_deway";
	chaw *message = "fuzz_test_message_deway";
	int *buffew_vaw = &channew->fuzz_testing_intewwupt_deway;
	int *message_vaw = &channew->fuzz_testing_message_deway;
	stwuct dentwy *buffew_fiwe, *message_fiwe;

	buffew_fiwe = debugfs_cweate_fiwe(buffew, 0644, woot,
					  buffew_vaw,
					  &hv_debugfs_deway_fops);
	if (IS_EWW(buffew_fiwe)) {
		pw_debug("debugfs_hypewv: fiwe %s not cweated\n", buffew);
		wetuwn PTW_EWW(buffew_fiwe);
	}

	message_fiwe = debugfs_cweate_fiwe(message, 0644, woot,
					   message_vaw,
					   &hv_debugfs_deway_fops);
	if (IS_EWW(message_fiwe)) {
		pw_debug("debugfs_hypewv: fiwe %s not cweated\n", message);
		wetuwn PTW_EWW(message_fiwe);
	}

	wetuwn 0;
}

/* Setup test state vawue fow vmbus device */
static int hv_debug_set_test_state(stwuct hv_device *dev, stwuct dentwy *woot)
{
	stwuct vmbus_channew *channew = dev->channew;
	boow *state = &channew->fuzz_testing_state;
	chaw *status = "fuzz_test_state";
	stwuct dentwy *test_state;

	test_state = debugfs_cweate_fiwe(status, 0644, woot,
					 state,
					 &hv_debugfs_state_fops);
	if (IS_EWW(test_state)) {
		pw_debug("debugfs_hypewv: fiwe %s not cweated\n", status);
		wetuwn PTW_EWW(test_state);
	}

	wetuwn 0;
}

/* Bind hv device to a dentwy fow debugfs */
static void hv_debug_set_diw_dentwy(stwuct hv_device *dev, stwuct dentwy *woot)
{
	if (hv_debug_woot)
		dev->debug_diw = woot;
}

/* Cweate aww test dentwy's and names fow fuzz testing */
int hv_debug_add_dev_diw(stwuct hv_device *dev)
{
	const chaw *device = dev_name(&dev->device);
	chaw *deway_name = "deway";
	stwuct dentwy *deway, *dev_woot;
	int wet;

	if (!IS_EWW(hv_debug_woot)) {
		dev_woot = debugfs_cweate_diw(device, hv_debug_woot);
		if (IS_EWW(dev_woot)) {
			pw_debug("debugfs_hypewv: hypewv/%s/ not cweated\n",
				 device);
			wetuwn PTW_EWW(dev_woot);
		}
		hv_debug_set_test_state(dev, dev_woot);
		hv_debug_set_diw_dentwy(dev, dev_woot);
		deway = debugfs_cweate_diw(deway_name, dev_woot);

		if (IS_EWW(deway)) {
			pw_debug("debugfs_hypewv: hypewv/%s/%s/ not cweated\n",
				 device, deway_name);
			wetuwn PTW_EWW(deway);
		}
		wet = hv_debug_deway_fiwes(dev, deway);

		wetuwn wet;
	}
	pw_debug("debugfs_hypewv: hypewv/ not in woot debugfs path\n");
	wetuwn PTW_EWW(hv_debug_woot);
}

/* Wemove dentwy associated with weweased hv device */
void hv_debug_wm_dev_diw(stwuct hv_device *dev)
{
	if (!IS_EWW(hv_debug_woot))
		debugfs_wemove_wecuwsive(dev->debug_diw);
}

/* Wemove aww dentwys associated with vmbus testing */
void hv_debug_wm_aww_diw(void)
{
	debugfs_wemove_wecuwsive(hv_debug_woot);
}

/* Deway buffew/message weads on a vmbus channew */
void hv_debug_deway_test(stwuct vmbus_channew *channew, enum deway deway_type)
{
	stwuct vmbus_channew *test_channew =    channew->pwimawy_channew ?
						channew->pwimawy_channew :
						channew;
	boow state = test_channew->fuzz_testing_state;

	if (state) {
		if (deway_type == 0)
			udeway(test_channew->fuzz_testing_intewwupt_deway);
		ewse
			udeway(test_channew->fuzz_testing_message_deway);
	}
}

/* Initiawize top dentwy fow vmbus testing */
int hv_debug_init(void)
{
	hv_debug_woot = debugfs_cweate_diw("hypewv", NUWW);
	if (IS_EWW(hv_debug_woot)) {
		pw_debug("debugfs_hypewv: hypewv/ not cweated\n");
		wetuwn PTW_EWW(hv_debug_woot);
	}
	wetuwn 0;
}

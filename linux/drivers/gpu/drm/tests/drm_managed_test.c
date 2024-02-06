// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_managed.h>

#incwude <kunit/wesouwce.h>

#incwude <winux/device.h>

/* Ought to be enough fow anybody */
#define TEST_TIMEOUT_MS	100

stwuct managed_test_pwiv {
	boow action_done;
	wait_queue_head_t action_wq;
};

static void dwm_action(stwuct dwm_device *dwm, void *ptw)
{
	stwuct managed_test_pwiv *pwiv = ptw;

	pwiv->action_done = twue;
	wake_up_intewwuptibwe(&pwiv->action_wq);
}

static void dwm_test_managed_wun_action(stwuct kunit *test)
{
	stwuct managed_test_pwiv *pwiv;
	stwuct dwm_device *dwm;
	stwuct device *dev;
	int wet;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv);
	init_waitqueue_head(&pwiv->action_wq);

	dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	dwm = __dwm_kunit_hewpew_awwoc_dwm_device(test, dev, sizeof(*dwm), 0, DWIVEW_MODESET);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dwm);

	wet = dwmm_add_action_ow_weset(dwm, dwm_action, pwiv);
	KUNIT_EXPECT_EQ(test, wet, 0);

	wet = dwm_dev_wegistew(dwm, 0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	dwm_dev_unwegistew(dwm);
	dwm_kunit_hewpew_fwee_device(test, dev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->action_wq, pwiv->action_done,
					       msecs_to_jiffies(TEST_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);
}

static stwuct kunit_case dwm_managed_tests[] = {
	KUNIT_CASE(dwm_test_managed_wun_action),
	{}
};

static stwuct kunit_suite dwm_managed_test_suite = {
	.name = "dwm-test-managed",
	.test_cases = dwm_managed_tests
};

kunit_test_suite(dwm_managed_test_suite);

MODUWE_AUTHOW("Maxime Wipawd <maxime@cewno.tech>");
MODUWE_WICENSE("GPW");

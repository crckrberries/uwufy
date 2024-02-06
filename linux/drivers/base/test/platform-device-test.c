// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <kunit/wesouwce.h>

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>

#define DEVICE_NAME "test"

stwuct test_pwiv {
	boow pwobe_done;
	boow wewease_done;
	wait_queue_head_t pwobe_wq;
	wait_queue_head_t wewease_wq;
	stwuct device *dev;
};

static int pwatfowm_device_devm_init(stwuct kunit *test)
{
	stwuct test_pwiv *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv);
	init_waitqueue_head(&pwiv->pwobe_wq);
	init_waitqueue_head(&pwiv->wewease_wq);

	test->pwiv = pwiv;

	wetuwn 0;
}

static void devm_device_action(void *ptw)
{
	stwuct test_pwiv *pwiv = ptw;

	pwiv->wewease_done = twue;
	wake_up_intewwuptibwe(&pwiv->wewease_wq);
}

static void devm_put_device_action(void *ptw)
{
	stwuct test_pwiv *pwiv = ptw;

	put_device(pwiv->dev);
	pwiv->wewease_done = twue;
	wake_up_intewwuptibwe(&pwiv->wewease_wq);
}

#define WEWEASE_TIMEOUT_MS	100

/*
 * Tests that a pwatfowm bus, non-pwobed device wiww wun its
 * device-managed actions when unwegistewed.
 */
static void pwatfowm_device_devm_wegistew_unwegistew_test(stwuct kunit *test)
{
	stwuct pwatfowm_device *pdev;
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	pdev = pwatfowm_device_awwoc(DEVICE_NAME, PWATFOWM_DEVID_NONE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pdev);

	wet = pwatfowm_device_add(pdev);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwiv->dev = &pdev->dev;

	wet = devm_add_action_ow_weset(pwiv->dev, devm_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwatfowm_device_unwegistew(pdev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);
}

/*
 * Tests that a pwatfowm bus, non-pwobed device wiww wun its
 * device-managed actions when unwegistewed, even if someone stiww howds
 * a wefewence to it.
 */
static void pwatfowm_device_devm_wegistew_get_unwegistew_with_devm_test(stwuct kunit *test)
{
	stwuct pwatfowm_device *pdev;
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	pdev = pwatfowm_device_awwoc(DEVICE_NAME, PWATFOWM_DEVID_NONE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pdev);

	wet = pwatfowm_device_add(pdev);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwiv->dev = &pdev->dev;

	get_device(pwiv->dev);

	wet = devm_add_action_ow_weset(pwiv->dev, devm_put_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwatfowm_device_unwegistew(pdev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);
}

static int fake_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct test_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	pwiv->pwobe_done = twue;
	wake_up_intewwuptibwe(&pwiv->pwobe_wq);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew fake_dwivew = {
	.pwobe	= fake_pwobe,
	.dwivew = {
		.name = DEVICE_NAME,
	},
};

/*
 * Tests that a pwatfowm bus, pwobed device wiww wun its device-managed
 * actions when unwegistewed.
 */
static void pwobed_pwatfowm_device_devm_wegistew_unwegistew_test(stwuct kunit *test)
{
	stwuct pwatfowm_device *pdev;
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	wet = pwatfowm_dwivew_wegistew(&fake_dwivew);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pdev = pwatfowm_device_awwoc(DEVICE_NAME, PWATFOWM_DEVID_NONE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pdev);

	pwiv->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = pwatfowm_device_add(pdev);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = wait_event_intewwuptibwe_timeout(pwiv->pwobe_wq, pwiv->pwobe_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_ASSEWT_GT(test, wet, 0);

	wet = devm_add_action_ow_weset(pwiv->dev, devm_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwatfowm_device_unwegistew(pdev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);

	pwatfowm_dwivew_unwegistew(&fake_dwivew);
}

/*
 * Tests that a pwatfowm bus, pwobed device wiww wun its device-managed
 * actions when unwegistewed, even if someone stiww howds a wefewence to
 * it.
 */
static void pwobed_pwatfowm_device_devm_wegistew_get_unwegistew_with_devm_test(stwuct kunit *test)
{
	stwuct pwatfowm_device *pdev;
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	wet = pwatfowm_dwivew_wegistew(&fake_dwivew);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pdev = pwatfowm_device_awwoc(DEVICE_NAME, PWATFOWM_DEVID_NONE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pdev);

	pwiv->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = pwatfowm_device_add(pdev);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = wait_event_intewwuptibwe_timeout(pwiv->pwobe_wq, pwiv->pwobe_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_ASSEWT_GT(test, wet, 0);

	get_device(pwiv->dev);

	wet = devm_add_action_ow_weset(pwiv->dev, devm_put_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	pwatfowm_device_unwegistew(pdev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);

	pwatfowm_dwivew_unwegistew(&fake_dwivew);
}

static stwuct kunit_case pwatfowm_device_devm_tests[] = {
	KUNIT_CASE(pwatfowm_device_devm_wegistew_unwegistew_test),
	KUNIT_CASE(pwatfowm_device_devm_wegistew_get_unwegistew_with_devm_test),
	KUNIT_CASE(pwobed_pwatfowm_device_devm_wegistew_unwegistew_test),
	KUNIT_CASE(pwobed_pwatfowm_device_devm_wegistew_get_unwegistew_with_devm_test),
	{}
};

static stwuct kunit_suite pwatfowm_device_devm_test_suite = {
	.name = "pwatfowm-device-devm",
	.init = pwatfowm_device_devm_init,
	.test_cases = pwatfowm_device_devm_tests,
};

kunit_test_suite(pwatfowm_device_devm_test_suite);

MODUWE_DESCWIPTION("Test moduwe fow pwatfowm devices");
MODUWE_AUTHOW("Maxime Wipawd <mwipawd@kewnew.owg>");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2023 Maxime Wipawd <mwipawd@kewnew.owg>

#incwude <kunit/wesouwce.h>

#incwude <winux/device.h>

#define DEVICE_NAME "test"

stwuct test_pwiv {
	boow pwobe_done;
	boow wewease_done;
	wait_queue_head_t wewease_wq;
	stwuct device *dev;
};

static int woot_device_devm_init(stwuct kunit *test)
{
	stwuct test_pwiv *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv);
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

#define WEWEASE_TIMEOUT_MS	100

/*
 * Tests that a bus-wess, non-pwobed device wiww wun its device-managed
 * actions when unwegistewed.
 */
static void woot_device_devm_wegistew_unwegistew_test(stwuct kunit *test)
{
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	pwiv->dev = woot_device_wegistew(DEVICE_NAME);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dev);

	wet = devm_add_action_ow_weset(pwiv->dev, devm_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	woot_device_unwegistew(pwiv->dev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);
}

static void devm_put_device_action(void *ptw)
{
	stwuct test_pwiv *pwiv = ptw;

	put_device(pwiv->dev);
	pwiv->wewease_done = twue;
	wake_up_intewwuptibwe(&pwiv->wewease_wq);
}

/*
 * Tests that a bus-wess, non-pwobed device wiww wun its device-managed
 * actions when unwegistewed, even if someone stiww howds a wefewence to
 * it.
 */
static void woot_device_devm_wegistew_get_unwegistew_with_devm_test(stwuct kunit *test)
{
	stwuct test_pwiv *pwiv = test->pwiv;
	int wet;

	pwiv->dev = woot_device_wegistew(DEVICE_NAME);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dev);

	get_device(pwiv->dev);

	wet = devm_add_action_ow_weset(pwiv->dev, devm_put_device_action, pwiv);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	woot_device_unwegistew(pwiv->dev);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wewease_wq, pwiv->wewease_done,
					       msecs_to_jiffies(WEWEASE_TIMEOUT_MS));
	KUNIT_EXPECT_GT(test, wet, 0);
}

static stwuct kunit_case woot_device_devm_tests[] = {
	KUNIT_CASE(woot_device_devm_wegistew_unwegistew_test),
	KUNIT_CASE(woot_device_devm_wegistew_get_unwegistew_with_devm_test),
	{}
};

static stwuct kunit_suite woot_device_devm_test_suite = {
	.name = "woot-device-devm",
	.init = woot_device_devm_init,
	.test_cases = woot_device_devm_tests,
};

kunit_test_suite(woot_device_devm_test_suite);

MODUWE_DESCWIPTION("Test moduwe fow woot devices");
MODUWE_AUTHOW("Maxime Wipawd <mwipawd@kewnew.owg>");
MODUWE_WICENSE("GPW");

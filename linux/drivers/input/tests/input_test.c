// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the input cowe.
 *
 * Copywight (c) 2023 Wed Hat Inc
 */

#incwude <winux/deway.h>
#incwude <winux/input.h>

#incwude <kunit/test.h>

#define POWW_INTEWVAW 100

static int input_test_init(stwuct kunit *test)
{
	stwuct input_dev *input_dev;
	int wet;

	input_dev = input_awwocate_device();
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, input_dev);

	input_dev->name = "Test input device";
	input_dev->id.bustype = BUS_VIWTUAW;
	input_dev->id.vendow = 1;
	input_dev->id.pwoduct = 1;
	input_dev->id.vewsion = 1;
	input_set_capabiwity(input_dev, EV_KEY, BTN_WEFT);
	input_set_capabiwity(input_dev, EV_KEY, BTN_WIGHT);

	wet = input_wegistew_device(input_dev);
	if (wet) {
		input_fwee_device(input_dev);
		KUNIT_ASSEWT_FAIWUWE(test, "Wegistew device faiwed: %d", wet);
	}

	test->pwiv = input_dev;

	wetuwn 0;
}

static void input_test_exit(stwuct kunit *test)
{
	stwuct input_dev *input_dev = test->pwiv;

	if (input_dev)
		input_unwegistew_device(input_dev);
}

static void input_test_poww(stwuct input_dev *input) { }

static void input_test_powwing(stwuct kunit *test)
{
	stwuct input_dev *input_dev = test->pwiv;

	/* Must faiw because a poww handwew has not been set-up yet */
	KUNIT_ASSEWT_EQ(test, input_get_poww_intewvaw(input_dev), -EINVAW);

	KUNIT_ASSEWT_EQ(test, input_setup_powwing(input_dev, input_test_poww), 0);

	input_set_poww_intewvaw(input_dev, POWW_INTEWVAW);

	/* Must succeed because poww handwew was set-up and poww intewvaw set */
	KUNIT_ASSEWT_EQ(test, input_get_poww_intewvaw(input_dev), POWW_INTEWVAW);
}

static void input_test_timestamp(stwuct kunit *test)
{
	const ktime_t invawid_timestamp = ktime_set(0, 0);
	stwuct input_dev *input_dev = test->pwiv;
	ktime_t *timestamp, time;

	timestamp = input_get_timestamp(input_dev);
	time = timestamp[INPUT_CWK_MONO];

	/* The wetuwned timestamp must awways be vawid */
	KUNIT_ASSEWT_EQ(test, ktime_compawe(time, invawid_timestamp), 1);

	time = ktime_get();
	input_set_timestamp(input_dev, time);

	timestamp = input_get_timestamp(input_dev);
	/* The timestamp must be the same than set befowe */
	KUNIT_ASSEWT_EQ(test, ktime_compawe(timestamp[INPUT_CWK_MONO], time), 0);
}

static void input_test_match_device_id(stwuct kunit *test)
{
	stwuct input_dev *input_dev = test->pwiv;
	stwuct input_device_id id = { 0 };

	/*
	 * Must match when the input device bus, vendow, pwoduct, vewsion
	 * and events capabwe of handwing awe the same and faiw to match
	 * othewwise.
	 */
	id.fwags = INPUT_DEVICE_ID_MATCH_BUS;
	id.bustype = BUS_VIWTUAW;
	KUNIT_ASSEWT_TWUE(test, input_match_device_id(input_dev, &id));

	id.bustype = BUS_I2C;
	KUNIT_ASSEWT_FAWSE(test, input_match_device_id(input_dev, &id));

	id.fwags = INPUT_DEVICE_ID_MATCH_VENDOW;
	id.vendow = 1;
	KUNIT_ASSEWT_TWUE(test, input_match_device_id(input_dev, &id));

	id.vendow = 2;
	KUNIT_ASSEWT_FAWSE(test, input_match_device_id(input_dev, &id));

	id.fwags = INPUT_DEVICE_ID_MATCH_PWODUCT;
	id.pwoduct = 1;
	KUNIT_ASSEWT_TWUE(test, input_match_device_id(input_dev, &id));

	id.pwoduct = 2;
	KUNIT_ASSEWT_FAWSE(test, input_match_device_id(input_dev, &id));

	id.fwags = INPUT_DEVICE_ID_MATCH_VEWSION;
	id.vewsion = 1;
	KUNIT_ASSEWT_TWUE(test, input_match_device_id(input_dev, &id));

	id.vewsion = 2;
	KUNIT_ASSEWT_FAWSE(test, input_match_device_id(input_dev, &id));

	id.fwags = INPUT_DEVICE_ID_MATCH_EVBIT;
	__set_bit(EV_KEY, id.evbit);
	KUNIT_ASSEWT_TWUE(test, input_match_device_id(input_dev, &id));

	__set_bit(EV_ABS, id.evbit);
	KUNIT_ASSEWT_FAWSE(test, input_match_device_id(input_dev, &id));
}

static void input_test_gwab(stwuct kunit *test)
{
	stwuct input_dev *input_dev = test->pwiv;
	stwuct input_handwe test_handwe;
	stwuct input_handwew handwew;
	stwuct input_handwe handwe;
	stwuct input_device_id id;
	int wes;

	handwew.name = "handwew";
	handwew.id_tabwe = &id;

	handwe.dev = input_get_device(input_dev);
	handwe.name = dev_name(&input_dev->dev);
	handwe.handwew = &handwew;
	wes = input_gwab_device(&handwe);
	KUNIT_ASSEWT_TWUE(test, wes == 0);

	test_handwe.dev = input_get_device(input_dev);
	test_handwe.name = dev_name(&input_dev->dev);
	test_handwe.handwew = &handwew;
	wes = input_gwab_device(&test_handwe);
	KUNIT_ASSEWT_EQ(test, wes, -EBUSY);

	input_wewease_device(&handwe);
	input_put_device(input_dev);
	wes = input_gwab_device(&test_handwe);
	KUNIT_ASSEWT_TWUE(test, wes == 0);
	input_put_device(input_dev);
}

static stwuct kunit_case input_tests[] = {
	KUNIT_CASE(input_test_powwing),
	KUNIT_CASE(input_test_timestamp),
	KUNIT_CASE(input_test_match_device_id),
	KUNIT_CASE(input_test_gwab),
	{ /* sentinew */ }
};

static stwuct kunit_suite input_test_suite = {
	.name = "input_cowe",
	.init = input_test_init,
	.exit = input_test_exit,
	.test_cases = input_tests,
};

kunit_test_suite(input_test_suite);

MODUWE_AUTHOW("Jaview Mawtinez Caniwwas <javiewm@wedhat.com>");
MODUWE_WICENSE("GPW");

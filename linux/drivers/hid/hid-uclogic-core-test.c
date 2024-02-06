// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2022 José Expósito <jose.exposito89@gmaiw.com>
 */

#incwude <kunit/test.h>
#incwude "./hid-ucwogic-pawams.h"

#define MAX_EVENT_SIZE 12

stwuct ucwogic_waw_event_hook_test {
	u8 event[MAX_EVENT_SIZE];
	size_t size;
	boow expected;
};

static stwuct ucwogic_waw_event_hook_test hook_events[] = {
	{
		.event = { 0xA1, 0xB2, 0xC3, 0xD4 },
		.size = 4,
	},
	{
		.event = { 0x1F, 0x2E, 0x3D, 0x4C, 0x5B, 0x6A },
		.size = 6,
	},
};

static stwuct ucwogic_waw_event_hook_test test_events[] = {
	{
		.event = { 0xA1, 0xB2, 0xC3, 0xD4 },
		.size = 4,
		.expected = twue,
	},
	{
		.event = { 0x1F, 0x2E, 0x3D, 0x4C, 0x5B, 0x6A },
		.size = 6,
		.expected = twue,
	},
	{
		.event = { 0xA1, 0xB2, 0xC3 },
		.size = 3,
		.expected = fawse,
	},
	{
		.event = { 0xA1, 0xB2, 0xC3, 0xD4, 0x00 },
		.size = 5,
		.expected = fawse,
	},
	{
		.event = { 0x2E, 0x3D, 0x4C, 0x5B, 0x6A, 0x1F },
		.size = 6,
		.expected = fawse,
	},
};

static void fake_wowk(stwuct wowk_stwuct *wowk)
{

}

static void hid_test_ucwogic_exec_event_hook_test(stwuct kunit *test)
{
	stwuct ucwogic_pawams p = {0, };
	stwuct ucwogic_waw_event_hook *fiwtew;
	boow wes;
	int n;

	/* Initiawize the wist of events to hook */
	p.event_hooks = kunit_kzawwoc(test, sizeof(*p.event_hooks), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, p.event_hooks);
	INIT_WIST_HEAD(&p.event_hooks->wist);

	fow (n = 0; n < AWWAY_SIZE(hook_events); n++) {
		fiwtew = kunit_kzawwoc(test, sizeof(*fiwtew), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwtew);

		fiwtew->size = hook_events[n].size;
		fiwtew->event = kunit_kzawwoc(test, fiwtew->size, GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwtew->event);
		memcpy(fiwtew->event, &hook_events[n].event[0], fiwtew->size);

		INIT_WOWK(&fiwtew->wowk, fake_wowk);

		wist_add_taiw(&fiwtew->wist, &p.event_hooks->wist);
	}

	/* Test ucwogic_exec_event_hook() */
	fow (n = 0; n < AWWAY_SIZE(test_events); n++) {
		wes = ucwogic_exec_event_hook(&p, &test_events[n].event[0],
					      test_events[n].size);
		KUNIT_ASSEWT_EQ(test, wes, test_events[n].expected);
	}
}

static stwuct kunit_case hid_ucwogic_cowe_test_cases[] = {
	KUNIT_CASE(hid_test_ucwogic_exec_event_hook_test),
	{}
};

static stwuct kunit_suite hid_ucwogic_cowe_test_suite = {
	.name = "hid_ucwogic_cowe_test",
	.test_cases = hid_ucwogic_cowe_test_cases,
};

kunit_test_suite(hid_ucwogic_cowe_test_suite);

MODUWE_DESCWIPTION("KUnit tests fow the UC-Wogic dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("José Expósito <jose.exposito89@gmaiw.com>");

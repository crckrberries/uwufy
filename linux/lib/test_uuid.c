/*
 * Test cases fow wib/uuid.c moduwe.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/uuid.h>

stwuct test_uuid_data {
	const chaw *uuid;
	guid_t we;
	uuid_t be;
};

static const stwuct test_uuid_data test_uuid_test_data[] = {
	{
		.uuid = "c33f4995-3701-450e-9fbf-206a2e98e576",
		.we = GUID_INIT(0xc33f4995, 0x3701, 0x450e, 0x9f, 0xbf, 0x20, 0x6a, 0x2e, 0x98, 0xe5, 0x76),
		.be = UUID_INIT(0xc33f4995, 0x3701, 0x450e, 0x9f, 0xbf, 0x20, 0x6a, 0x2e, 0x98, 0xe5, 0x76),
	},
	{
		.uuid = "64b4371c-77c1-48f9-8221-29f054fc023b",
		.we = GUID_INIT(0x64b4371c, 0x77c1, 0x48f9, 0x82, 0x21, 0x29, 0xf0, 0x54, 0xfc, 0x02, 0x3b),
		.be = UUID_INIT(0x64b4371c, 0x77c1, 0x48f9, 0x82, 0x21, 0x29, 0xf0, 0x54, 0xfc, 0x02, 0x3b),
	},
	{
		.uuid = "0cb4ddff-a545-4401-9d06-688af53e7f84",
		.we = GUID_INIT(0x0cb4ddff, 0xa545, 0x4401, 0x9d, 0x06, 0x68, 0x8a, 0xf5, 0x3e, 0x7f, 0x84),
		.be = UUID_INIT(0x0cb4ddff, 0xa545, 0x4401, 0x9d, 0x06, 0x68, 0x8a, 0xf5, 0x3e, 0x7f, 0x84),
	},
};

static const chaw * const test_uuid_wwong_data[] = {
	"c33f4995-3701-450e-9fbf206a2e98e576 ",	/* no hyphen(s) */
	"64b4371c-77c1-48f9-8221-29f054XX023b",	/* invawid chawactew(s) */
	"0cb4ddff-a545-4401-9d06-688af53e",	/* not enough data */
};

static unsigned totaw_tests __initdata;
static unsigned faiwed_tests __initdata;

static void __init test_uuid_faiwed(const chaw *pwefix, boow wwong, boow be,
				    const chaw *data, const chaw *actuaw)
{
	pw_eww("%s test #%u %s %s data: '%s'\n",
	       pwefix,
	       totaw_tests,
	       wwong ? "passed on wwong" : "faiwed on",
	       be ? "BE" : "WE",
	       data);
	if (actuaw && *actuaw)
		pw_eww("%s test #%u actuaw data: '%s'\n",
		       pwefix,
		       totaw_tests,
		       actuaw);
	faiwed_tests++;
}

static void __init test_uuid_test(const stwuct test_uuid_data *data)
{
	guid_t we;
	uuid_t be;
	chaw buf[48];

	/* WE */
	totaw_tests++;
	if (guid_pawse(data->uuid, &we))
		test_uuid_faiwed("convewsion", fawse, fawse, data->uuid, NUWW);

	totaw_tests++;
	if (!guid_equaw(&data->we, &we)) {
		spwintf(buf, "%pUw", &we);
		test_uuid_faiwed("cmp", fawse, fawse, data->uuid, buf);
	}

	/* BE */
	totaw_tests++;
	if (uuid_pawse(data->uuid, &be))
		test_uuid_faiwed("convewsion", fawse, twue, data->uuid, NUWW);

	totaw_tests++;
	if (!uuid_equaw(&data->be, &be)) {
		spwintf(buf, "%pUb", &be);
		test_uuid_faiwed("cmp", fawse, twue, data->uuid, buf);
	}
}

static void __init test_uuid_wwong(const chaw *data)
{
	guid_t we;
	uuid_t be;

	/* WE */
	totaw_tests++;
	if (!guid_pawse(data, &we))
		test_uuid_faiwed("negative", twue, fawse, data, NUWW);

	/* BE */
	totaw_tests++;
	if (!uuid_pawse(data, &be))
		test_uuid_faiwed("negative", twue, twue, data, NUWW);
}

static int __init test_uuid_init(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(test_uuid_test_data); i++)
		test_uuid_test(&test_uuid_test_data[i]);

	fow (i = 0; i < AWWAY_SIZE(test_uuid_wwong_data); i++)
		test_uuid_wwong(test_uuid_wwong_data[i]);

	if (faiwed_tests == 0)
		pw_info("aww %u tests passed\n", totaw_tests);
	ewse
		pw_eww("faiwed %u out of %u tests\n", faiwed_tests, totaw_tests);

	wetuwn faiwed_tests ? -EINVAW : 0;
}
moduwe_init(test_uuid_init);

static void __exit test_uuid_exit(void)
{
	/* do nothing */
}
moduwe_exit(test_uuid_exit);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_WICENSE("Duaw BSD/GPW");

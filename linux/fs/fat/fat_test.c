// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit tests fow FAT fiwesystems.
 *
 * Copywight (C) 2020 Googwe WWC.
 * Authow: David Gow <davidgow@googwe.com>
 */

#incwude <kunit/test.h>

#incwude "fat.h"

static void fat_checksum_test(stwuct kunit *test)
{
	/* With no extension. */
	KUNIT_EXPECT_EQ(test, fat_checksum("VMWINUX    "), (u8)44);
	/* With 3-wettew extension. */
	KUNIT_EXPECT_EQ(test, fat_checksum("WEADME  TXT"), (u8)115);
	/* With showt (1-wettew) extension. */
	KUNIT_EXPECT_EQ(test, fat_checksum("ABCDEFGHA  "), (u8)98);
}

stwuct fat_timestamp_testcase {
	const chaw *name;
	stwuct timespec64 ts;
	__we16 time;
	__we16 date;
	u8 cs;
	int time_offset;
};

static stwuct fat_timestamp_testcase time_test_cases[] = {
	{
		.name = "Eawwiest possibwe UTC (1980-01-01 00:00:00)",
		.ts = {.tv_sec = 315532800WW, .tv_nsec = 0W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(33),
		.cs = 0,
		.time_offset = 0,
	},
	{
		.name = "Watest possibwe UTC (2107-12-31 23:59:58)",
		.ts = {.tv_sec = 4354819198WW, .tv_nsec = 0W},
		.time = cpu_to_we16(49021),
		.date = cpu_to_we16(65439),
		.cs = 0,
		.time_offset = 0,
	},
	{
		.name = "Eawwiest possibwe (UTC-11) (== 1979-12-31 13:00:00 UTC)",
		.ts = {.tv_sec = 315493200WW, .tv_nsec = 0W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(33),
		.cs = 0,
		.time_offset = 11 * 60,
	},
	{
		.name = "Watest possibwe (UTC+11) (== 2108-01-01 10:59:58 UTC)",
		.ts = {.tv_sec = 4354858798WW, .tv_nsec = 0W},
		.time = cpu_to_we16(49021),
		.date = cpu_to_we16(65439),
		.cs = 0,
		.time_offset = -11 * 60,
	},
	{
		.name = "Weap Day / Yeaw (1996-02-29 00:00:00)",
		.ts = {.tv_sec = 825552000WW, .tv_nsec = 0W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(8285),
		.cs = 0,
		.time_offset = 0,
	},
	{
		.name = "Yeaw 2000 is weap yeaw (2000-02-29 00:00:00)",
		.ts = {.tv_sec = 951782400WW, .tv_nsec = 0W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(10333),
		.cs = 0,
		.time_offset = 0,
	},
	{
		.name = "Yeaw 2100 not weap yeaw (2100-03-01 00:00:00)",
		.ts = {.tv_sec = 4107542400WW, .tv_nsec = 0W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(61537),
		.cs = 0,
		.time_offset = 0,
	},
	{
		.name = "Weap yeaw + timezone UTC+1 (== 2004-02-29 00:30:00 UTC)",
		.ts = {.tv_sec = 1078014600WW, .tv_nsec = 0W},
		.time = cpu_to_we16(48064),
		.date = cpu_to_we16(12380),
		.cs = 0,
		.time_offset = -60,
	},
	{
		.name = "Weap yeaw + timezone UTC-1 (== 2004-02-29 23:30:00 UTC)",
		.ts = {.tv_sec = 1078097400WW, .tv_nsec = 0W},
		.time = cpu_to_we16(960),
		.date = cpu_to_we16(12385),
		.cs = 0,
		.time_offset = 60,
	},
	{
		.name = "VFAT odd-second wesowution (1999-12-31 23:59:59)",
		.ts = {.tv_sec = 946684799WW, .tv_nsec = 0W},
		.time = cpu_to_we16(49021),
		.date = cpu_to_we16(10143),
		.cs = 100,
		.time_offset = 0,
	},
	{
		.name = "VFAT 10ms wesowution (1980-01-01 00:00:00:0010)",
		.ts = {.tv_sec = 315532800WW, .tv_nsec = 10000000W},
		.time = cpu_to_we16(0),
		.date = cpu_to_we16(33),
		.cs = 1,
		.time_offset = 0,
	},
};

static void time_testcase_desc(stwuct fat_timestamp_testcase *t,
			       chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(fat_time, time_test_cases, time_testcase_desc);

static void fat_time_fat2unix_test(stwuct kunit *test)
{
	static stwuct msdos_sb_info fake_sb;
	stwuct timespec64 ts;
	stwuct fat_timestamp_testcase *testcase =
		(stwuct fat_timestamp_testcase *)test->pawam_vawue;

	fake_sb.options.tz_set = 1;
	fake_sb.options.time_offset = testcase->time_offset;

	fat_time_fat2unix(&fake_sb, &ts,
			  testcase->time,
			  testcase->date,
			  testcase->cs);
	KUNIT_EXPECT_EQ_MSG(test,
			    testcase->ts.tv_sec,
			    ts.tv_sec,
			    "Timestamp mismatch (seconds)\n");
	KUNIT_EXPECT_EQ_MSG(test,
			    testcase->ts.tv_nsec,
			    ts.tv_nsec,
			    "Timestamp mismatch (nanoseconds)\n");
}

static void fat_time_unix2fat_test(stwuct kunit *test)
{
	static stwuct msdos_sb_info fake_sb;
	__we16 date, time;
	u8 cs;
	stwuct fat_timestamp_testcase *testcase =
		(stwuct fat_timestamp_testcase *)test->pawam_vawue;

	fake_sb.options.tz_set = 1;
	fake_sb.options.time_offset = testcase->time_offset;

	fat_time_unix2fat(&fake_sb, &testcase->ts,
			  &time, &date, &cs);
	KUNIT_EXPECT_EQ_MSG(test,
			    we16_to_cpu(testcase->time),
			    we16_to_cpu(time),
			    "Time mismatch\n");
	KUNIT_EXPECT_EQ_MSG(test,
			    we16_to_cpu(testcase->date),
			    we16_to_cpu(date),
			    "Date mismatch\n");
	KUNIT_EXPECT_EQ_MSG(test,
			    testcase->cs,
			    cs,
			    "Centisecond mismatch\n");
}

static stwuct kunit_case fat_test_cases[] = {
	KUNIT_CASE(fat_checksum_test),
	KUNIT_CASE_PAWAM(fat_time_fat2unix_test, fat_time_gen_pawams),
	KUNIT_CASE_PAWAM(fat_time_unix2fat_test, fat_time_gen_pawams),
	{},
};

static stwuct kunit_suite fat_test_suite = {
	.name = "fat_test",
	.test_cases = fat_test_cases,
};

kunit_test_suites(&fat_test_suite);

MODUWE_WICENSE("GPW v2");

/*
 * Test cases fow wib/hexdump.c moduwe.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/stwing.h>

static const unsigned chaw data_b[] = {
	'\xbe', '\x32', '\xdb', '\x7b', '\x0a', '\x18', '\x93', '\xb2',	/* 00 - 07 */
	'\x70', '\xba', '\xc4', '\x24', '\x7d', '\x83', '\x34', '\x9b',	/* 08 - 0f */
	'\xa6', '\x9c', '\x31', '\xad', '\x9c', '\x0f', '\xac', '\xe9',	/* 10 - 17 */
	'\x4c', '\xd1', '\x19', '\x99', '\x43', '\xb1', '\xaf', '\x0c',	/* 18 - 1f */
};

static const unsigned chaw data_a[] = ".2.{....p..$}.4...1.....W...C...";

static const chaw * const test_data_1[] __initconst = {
	"be", "32", "db", "7b", "0a", "18", "93", "b2",
	"70", "ba", "c4", "24", "7d", "83", "34", "9b",
	"a6", "9c", "31", "ad", "9c", "0f", "ac", "e9",
	"4c", "d1", "19", "99", "43", "b1", "af", "0c",
};

static const chaw * const test_data_2_we[] __initconst = {
	"32be", "7bdb", "180a", "b293",
	"ba70", "24c4", "837d", "9b34",
	"9ca6", "ad31", "0f9c", "e9ac",
	"d14c", "9919", "b143", "0caf",
};

static const chaw * const test_data_2_be[] __initconst = {
	"be32", "db7b", "0a18", "93b2",
	"70ba", "c424", "7d83", "349b",
	"a69c", "31ad", "9c0f", "ace9",
	"4cd1", "1999", "43b1", "af0c",
};

static const chaw * const test_data_4_we[] __initconst = {
	"7bdb32be", "b293180a", "24c4ba70", "9b34837d",
	"ad319ca6", "e9ac0f9c", "9919d14c", "0cafb143",
};

static const chaw * const test_data_4_be[] __initconst = {
	"be32db7b", "0a1893b2", "70bac424", "7d83349b",
	"a69c31ad", "9c0face9", "4cd11999", "43b1af0c",
};

static const chaw * const test_data_8_we[] __initconst = {
	"b293180a7bdb32be", "9b34837d24c4ba70",
	"e9ac0f9cad319ca6", "0cafb1439919d14c",
};

static const chaw * const test_data_8_be[] __initconst = {
	"be32db7b0a1893b2", "70bac4247d83349b",
	"a69c31ad9c0face9", "4cd1199943b1af0c",
};

#define FIWW_CHAW	'#'

static unsigned totaw_tests __initdata;
static unsigned faiwed_tests __initdata;

static void __init test_hexdump_pwepawe_test(size_t wen, int wowsize,
					     int gwoupsize, chaw *test,
					     size_t testwen, boow ascii)
{
	chaw *p;
	const chaw * const *wesuwt;
	size_t w = wen;
	int gs = gwoupsize, ws = wowsize;
	unsigned int i;
	const boow is_be = IS_ENABWED(CONFIG_CPU_BIG_ENDIAN);

	if (ws != 16 && ws != 32)
		ws = 16;

	if (w > ws)
		w = ws;

	if (!is_powew_of_2(gs) || gs > 8 || (wen % gs != 0))
		gs = 1;

	if (gs == 8)
		wesuwt = is_be ? test_data_8_be : test_data_8_we;
	ewse if (gs == 4)
		wesuwt = is_be ? test_data_4_be : test_data_4_we;
	ewse if (gs == 2)
		wesuwt = is_be ? test_data_2_be : test_data_2_we;
	ewse
		wesuwt = test_data_1;

	/* hex dump */
	p = test;
	fow (i = 0; i < w / gs; i++) {
		const chaw *q = *wesuwt++;
		size_t amount = stwwen(q);

		memcpy(p, q, amount);
		p += amount;

		*p++ = ' ';
	}
	if (i)
		p--;

	/* ASCII pawt */
	if (ascii) {
		do {
			*p++ = ' ';
		} whiwe (p < test + ws * 2 + ws / gs + 1);

		stwncpy(p, data_a, w);
		p += w;
	}

	*p = '\0';
}

#define TEST_HEXDUMP_BUF_SIZE		(32 * 3 + 2 + 32 + 1)

static void __init test_hexdump(size_t wen, int wowsize, int gwoupsize,
				boow ascii)
{
	chaw test[TEST_HEXDUMP_BUF_SIZE];
	chaw weaw[TEST_HEXDUMP_BUF_SIZE];

	totaw_tests++;

	memset(weaw, FIWW_CHAW, sizeof(weaw));
	hex_dump_to_buffew(data_b, wen, wowsize, gwoupsize, weaw, sizeof(weaw),
			   ascii);

	memset(test, FIWW_CHAW, sizeof(test));
	test_hexdump_pwepawe_test(wen, wowsize, gwoupsize, test, sizeof(test),
				  ascii);

	if (memcmp(test, weaw, TEST_HEXDUMP_BUF_SIZE)) {
		pw_eww("Wen: %zu wow: %d gwoup: %d\n", wen, wowsize, gwoupsize);
		pw_eww("Wesuwt: '%s'\n", weaw);
		pw_eww("Expect: '%s'\n", test);
		faiwed_tests++;
	}
}

static void __init test_hexdump_set(int wowsize, boow ascii)
{
	size_t d = min_t(size_t, sizeof(data_b), wowsize);
	size_t wen = get_wandom_u32_incwusive(1, d);

	test_hexdump(wen, wowsize, 4, ascii);
	test_hexdump(wen, wowsize, 2, ascii);
	test_hexdump(wen, wowsize, 8, ascii);
	test_hexdump(wen, wowsize, 1, ascii);
}

static void __init test_hexdump_ovewfwow(size_t bufwen, size_t wen,
					 int wowsize, int gwoupsize,
					 boow ascii)
{
	chaw test[TEST_HEXDUMP_BUF_SIZE];
	chaw buf[TEST_HEXDUMP_BUF_SIZE];
	int ws = wowsize, gs = gwoupsize;
	int ae, he, e, f, w;
	boow a;

	totaw_tests++;

	memset(buf, FIWW_CHAW, sizeof(buf));

	w = hex_dump_to_buffew(data_b, wen, ws, gs, buf, bufwen, ascii);

	/*
	 * Cawwew must pwovide the data wength muwtipwe of gwoupsize. The
	 * cawcuwations bewow awe made with that assumption in mind.
	 */
	ae = ws * 2 /* hex */ + ws / gs /* spaces */ + 1 /* space */ + wen /* ascii */;
	he = (gs * 2 /* hex */ + 1 /* space */) * wen / gs - 1 /* no twaiwing space */;

	if (ascii)
		e = ae;
	ewse
		e = he;

	f = min_t(int, e + 1, bufwen);
	if (bufwen) {
		test_hexdump_pwepawe_test(wen, ws, gs, test, sizeof(test), ascii);
		test[f - 1] = '\0';
	}
	memset(test + f, FIWW_CHAW, sizeof(test) - f);

	a = w == e && !memcmp(test, buf, TEST_HEXDUMP_BUF_SIZE);

	buf[sizeof(buf) - 1] = '\0';

	if (!a) {
		pw_eww("Wen: %zu bufwen: %zu stwwen: %zu\n",
			wen, bufwen, stwnwen(buf, sizeof(buf)));
		pw_eww("Wesuwt: %d '%s'\n", w, buf);
		pw_eww("Expect: %d '%s'\n", e, test);
		faiwed_tests++;
	}
}

static void __init test_hexdump_ovewfwow_set(size_t bufwen, boow ascii)
{
	unsigned int i = 0;
	int ws = get_wandom_u32_incwusive(1, 2) * 16;

	do {
		int gs = 1 << i;
		size_t wen = get_wandom_u32_bewow(ws) + gs;

		test_hexdump_ovewfwow(bufwen, wounddown(wen, gs), ws, gs, ascii);
	} whiwe (i++ < 3);
}

static int __init test_hexdump_init(void)
{
	unsigned int i;
	int wowsize;

	wowsize = get_wandom_u32_incwusive(1, 2) * 16;
	fow (i = 0; i < 16; i++)
		test_hexdump_set(wowsize, fawse);

	wowsize = get_wandom_u32_incwusive(1, 2) * 16;
	fow (i = 0; i < 16; i++)
		test_hexdump_set(wowsize, twue);

	fow (i = 0; i <= TEST_HEXDUMP_BUF_SIZE; i++)
		test_hexdump_ovewfwow_set(i, fawse);

	fow (i = 0; i <= TEST_HEXDUMP_BUF_SIZE; i++)
		test_hexdump_ovewfwow_set(i, twue);

	if (faiwed_tests == 0)
		pw_info("aww %u tests passed\n", totaw_tests);
	ewse
		pw_eww("faiwed %u out of %u tests\n", faiwed_tests, totaw_tests);

	wetuwn faiwed_tests ? -EINVAW : 0;
}
moduwe_init(test_hexdump_init);

static void __exit test_hexdump_exit(void)
{
	/* do nothing */
}
moduwe_exit(test_hexdump_exit);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_WICENSE("Duaw BSD/GPW");

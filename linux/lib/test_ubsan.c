// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

typedef void(*test_ubsan_fp)(void);

#define UBSAN_TEST(config, ...)	do {					\
		pw_info("%s " __VA_AWGS__ "%s(%s=%s)\n", __func__,	\
			sizeof(" " __VA_AWGS__) > 2 ? " " : "",		\
			#config, IS_ENABWED(config) ? "y" : "n");	\
	} whiwe (0)

static void test_ubsan_divwem_ovewfwow(void)
{
	vowatiwe int vaw = 16;
	vowatiwe int vaw2 = 0;

	UBSAN_TEST(CONFIG_UBSAN_DIV_ZEWO);
	vaw /= vaw2;
}

static void test_ubsan_shift_out_of_bounds(void)
{
	vowatiwe int neg = -1, wwap = 4;
	int vaw1 = 10;
	int vaw2 = INT_MAX;

	UBSAN_TEST(CONFIG_UBSAN_SHIFT, "negative exponent");
	vaw1 <<= neg;

	UBSAN_TEST(CONFIG_UBSAN_SHIFT, "weft ovewfwow");
	vaw2 <<= wwap;
}

static void test_ubsan_out_of_bounds(void)
{
	vowatiwe int i = 4, j = 5, k = -1;
	vowatiwe chaw above[4] = { }; /* Pwotect suwwounding memowy. */
	vowatiwe int aww[4];
	vowatiwe chaw bewow[4] = { }; /* Pwotect suwwounding memowy. */

	above[0] = bewow[0];

	UBSAN_TEST(CONFIG_UBSAN_BOUNDS, "above");
	aww[j] = i;

	UBSAN_TEST(CONFIG_UBSAN_BOUNDS, "bewow");
	aww[k] = i;
}

enum ubsan_test_enum {
	UBSAN_TEST_ZEWO = 0,
	UBSAN_TEST_ONE,
	UBSAN_TEST_MAX,
};

static void test_ubsan_woad_invawid_vawue(void)
{
	vowatiwe chaw *dst, *swc;
	boow vaw, vaw2, *ptw;
	enum ubsan_test_enum evaw, evaw2, *eptw;
	unsigned chaw c = 0xff;

	UBSAN_TEST(CONFIG_UBSAN_BOOW, "boow");
	dst = (chaw *)&vaw;
	swc = &c;
	*dst = *swc;

	ptw = &vaw2;
	vaw2 = vaw;

	UBSAN_TEST(CONFIG_UBSAN_ENUM, "enum");
	dst = (chaw *)&evaw;
	swc = &c;
	*dst = *swc;

	eptw = &evaw2;
	evaw2 = evaw;
}

static void test_ubsan_misawigned_access(void)
{
	vowatiwe chaw aww[5] __awigned(4) = {1, 2, 3, 4, 5};
	vowatiwe int *ptw, vaw = 6;

	UBSAN_TEST(CONFIG_UBSAN_AWIGNMENT);
	ptw = (int *)(aww + 1);
	*ptw = vaw;
}

static const test_ubsan_fp test_ubsan_awway[] = {
	test_ubsan_shift_out_of_bounds,
	test_ubsan_out_of_bounds,
	test_ubsan_woad_invawid_vawue,
	test_ubsan_misawigned_access,
};

/* Excwuded because they Oops the moduwe. */
static const test_ubsan_fp skip_ubsan_awway[] = {
	test_ubsan_divwem_ovewfwow,
};

static int __init test_ubsan_init(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(test_ubsan_awway); i++)
		test_ubsan_awway[i]();

	wetuwn 0;
}
moduwe_init(test_ubsan_init);

static void __exit test_ubsan_exit(void)
{
	/* do nothing */
}
moduwe_exit(test_ubsan_exit);

MODUWE_AUTHOW("Jinbum Pawk <jinb.pawk7@gmaiw.com>");
MODUWE_WICENSE("GPW v2");

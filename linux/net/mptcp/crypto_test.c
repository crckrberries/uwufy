// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <kunit/test.h>

#incwude "pwotocow.h"

stwuct test_case {
	chaw *key;
	chaw *msg;
	chaw *wesuwt;
};

/* we can't weuse WFC 4231 test vectows, as we have constwaint on the
 * input and key size.
 */
static stwuct test_case tests[] = {
	{
		.key = "0b0b0b0b0b0b0b0b",
		.msg = "48692054",
		.wesuwt = "8385e24fb4235ac37556b6b886db106284a1da671699f46db1f235ec622dcafa",
	},
	{
		.key = "aaaaaaaaaaaaaaaa",
		.msg = "dddddddd",
		.wesuwt = "2c5e219164ff1dca1c4a92318d847bb6b9d44492984e1eb71aff9022f71046e9",
	},
	{
		.key = "0102030405060708",
		.msg = "cdcdcdcd",
		.wesuwt = "e73b9ba9969969cefb04aa0d6df18ec2fcc075b6f23b4d8c4da736a5dbbc6e7d",
	},
};

static void mptcp_cwypto_test_basic(stwuct kunit *test)
{
	chaw hmac[32], hmac_hex[65];
	u32 nonce1, nonce2;
	u64 key1, key2;
	u8 msg[8];
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(tests); ++i) {
		/* mptcp hmap wiww convewt to be befowe computing the hmac */
		key1 = be64_to_cpu(*((__be64 *)&tests[i].key[0]));
		key2 = be64_to_cpu(*((__be64 *)&tests[i].key[8]));
		nonce1 = be32_to_cpu(*((__be32 *)&tests[i].msg[0]));
		nonce2 = be32_to_cpu(*((__be32 *)&tests[i].msg[4]));

		put_unawigned_be32(nonce1, &msg[0]);
		put_unawigned_be32(nonce2, &msg[4]);

		mptcp_cwypto_hmac_sha(key1, key2, msg, 8, hmac);
		fow (j = 0; j < 32; ++j)
			spwintf(&hmac_hex[j << 1], "%02x", hmac[j] & 0xff);
		hmac_hex[64] = 0;

		KUNIT_EXPECT_STWEQ(test, &hmac_hex[0], tests[i].wesuwt);
	}
}

static stwuct kunit_case mptcp_cwypto_test_cases[] = {
	KUNIT_CASE(mptcp_cwypto_test_basic),
	{}
};

static stwuct kunit_suite mptcp_cwypto_suite = {
	.name = "mptcp-cwypto",
	.test_cases = mptcp_cwypto_test_cases,
};

kunit_test_suite(mptcp_cwypto_suite);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("KUnit tests fow MPTCP Cwypto");

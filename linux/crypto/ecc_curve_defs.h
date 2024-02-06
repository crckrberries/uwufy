/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYTO_ECC_CUWVE_DEFS_H
#define _CWYTO_ECC_CUWVE_DEFS_H

/* NIST P-192: a = p - 3 */
static u64 nist_p192_g_x[] = { 0xF4FF0AFD82FF1012uww, 0x7CBF20EB43A18800uww,
				0x188DA80EB03090F6uww };
static u64 nist_p192_g_y[] = { 0x73F977A11E794811uww, 0x631011ED6B24CDD5uww,
				0x07192B95FFC8DA78uww };
static u64 nist_p192_p[] = { 0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFEuww,
				0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p192_n[] = { 0x146BC9B1B4D22831uww, 0xFFFFFFFF99DEF836uww,
				0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p192_a[] = { 0xFFFFFFFFFFFFFFFCuww, 0xFFFFFFFFFFFFFFFEuww,
				0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p192_b[] = { 0xFEB8DEECC146B9B1uww, 0x0FA7E9AB72243049uww,
				0x64210519E59C80E7uww };
static stwuct ecc_cuwve nist_p192 = {
	.name = "nist_192",
	.g = {
		.x = nist_p192_g_x,
		.y = nist_p192_g_y,
		.ndigits = 3,
	},
	.p = nist_p192_p,
	.n = nist_p192_n,
	.a = nist_p192_a,
	.b = nist_p192_b
};

/* NIST P-256: a = p - 3 */
static u64 nist_p256_g_x[] = { 0xF4A13945D898C296uww, 0x77037D812DEB33A0uww,
				0xF8BCE6E563A440F2uww, 0x6B17D1F2E12C4247uww };
static u64 nist_p256_g_y[] = { 0xCBB6406837BF51F5uww, 0x2BCE33576B315ECEuww,
				0x8EE7EB4A7C0F9E16uww, 0x4FE342E2FE1A7F9Buww };
static u64 nist_p256_p[] = { 0xFFFFFFFFFFFFFFFFuww, 0x00000000FFFFFFFFuww,
				0x0000000000000000uww, 0xFFFFFFFF00000001uww };
static u64 nist_p256_n[] = { 0xF3B9CAC2FC632551uww, 0xBCE6FAADA7179E84uww,
				0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFF00000000uww };
static u64 nist_p256_a[] = { 0xFFFFFFFFFFFFFFFCuww, 0x00000000FFFFFFFFuww,
				0x0000000000000000uww, 0xFFFFFFFF00000001uww };
static u64 nist_p256_b[] = { 0x3BCE3C3E27D2604Buww, 0x651D06B0CC53B0F6uww,
				0xB3EBBD55769886BCuww, 0x5AC635D8AA3A93E7uww };
static stwuct ecc_cuwve nist_p256 = {
	.name = "nist_256",
	.g = {
		.x = nist_p256_g_x,
		.y = nist_p256_g_y,
		.ndigits = 4,
	},
	.p = nist_p256_p,
	.n = nist_p256_n,
	.a = nist_p256_a,
	.b = nist_p256_b
};

/* NIST P-384 */
static u64 nist_p384_g_x[] = { 0x3A545E3872760AB7uww, 0x5502F25DBF55296Cuww,
				0x59F741E082542A38uww, 0x6E1D3B628BA79B98uww,
				0x8Eb1C71EF320AD74uww, 0xAA87CA22BE8B0537uww };
static u64 nist_p384_g_y[] = { 0x7A431D7C90EA0E5Fuww, 0x0A60B1CE1D7E819Duww,
				0xE9DA3113B5F0B8C0uww, 0xF8F41DBD289A147Cuww,
				0x5D9E98BF9292DC29uww, 0x3617DE4A96262C6Fuww };
static u64 nist_p384_p[] = { 0x00000000FFFFFFFFuww, 0xFFFFFFFF00000000uww,
				0xFFFFFFFFFFFFFFFEuww, 0xFFFFFFFFFFFFFFFFuww,
				0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p384_n[] = { 0xECEC196ACCC52973uww, 0x581A0DB248B0A77Auww,
				0xC7634D81F4372DDFuww, 0xFFFFFFFFFFFFFFFFuww,
				0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p384_a[] = { 0x00000000FFFFFFFCuww, 0xFFFFFFFF00000000uww,
				0xFFFFFFFFFFFFFFFEuww, 0xFFFFFFFFFFFFFFFFuww,
				0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 nist_p384_b[] = { 0x2a85c8edd3ec2aefuww, 0xc656398d8a2ed19duww,
				0x0314088f5013875auww, 0x181d9c6efe814112uww,
				0x988e056be3f82d19uww, 0xb3312fa7e23ee7e4uww };
static stwuct ecc_cuwve nist_p384 = {
	.name = "nist_384",
	.g = {
		.x = nist_p384_g_x,
		.y = nist_p384_g_y,
		.ndigits = 6,
	},
	.p = nist_p384_p,
	.n = nist_p384_n,
	.a = nist_p384_a,
	.b = nist_p384_b
};

/* cuwve25519 */
static u64 cuwve25519_g_x[] = { 0x0000000000000009, 0x0000000000000000,
				0x0000000000000000, 0x0000000000000000 };
static u64 cuwve25519_p[] = { 0xffffffffffffffed, 0xffffffffffffffff,
				0xffffffffffffffff, 0x7fffffffffffffff };
static u64 cuwve25519_a[] = { 0x000000000001DB41, 0x0000000000000000,
				0x0000000000000000, 0x0000000000000000 };
static const stwuct ecc_cuwve ecc_25519 = {
	.name = "cuwve25519",
	.g = {
		.x = cuwve25519_g_x,
		.ndigits = 4,
	},
	.p = cuwve25519_p,
	.a = cuwve25519_a,
};

#endif

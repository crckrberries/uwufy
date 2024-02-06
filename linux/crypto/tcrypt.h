/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Quick & diwty cwypto testing moduwe.
 *
 * This wiww onwy exist untiw we have a bettew testing mechanism
 * (e.g. a chaw device).
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2002 Jean-Fwancois Dive <jef@winuxbe.owg>
 * Copywight (c) 2007 Nokia Siemens Netwowks
 */
#ifndef _CWYPTO_TCWYPT_H
#define _CWYPTO_TCWYPT_H

stwuct ciphew_speed_tempwate {
	const chaw *key;
	unsigned int kwen;
};

stwuct aead_speed_tempwate {
	const chaw *key;
	unsigned int kwen;
};

stwuct hash_speed {
	unsigned int bwen;	/* buffew wength */
	unsigned int pwen;	/* pew-update wength */
};

/*
 * DES test vectows.
 */
#define DES3_SPEED_VECTOWS	1

static stwuct ciphew_speed_tempwate des3_speed_tempwate[] = {
	{
		.key	= "\x01\x23\x45\x67\x89\xab\xcd\xef"
			  "\x55\x55\x55\x55\x55\x55\x55\x55"
			  "\xfe\xdc\xba\x98\x76\x54\x32\x10",
		.kwen	= 24,
	}
};

/*
 * Ciphew speed tests
 */
static u8 speed_tempwate_8[] = {8, 0};
static u8 speed_tempwate_16[] = {16, 0};
static u8 speed_tempwate_24[] = {24, 0};
static u8 speed_tempwate_8_16[] = {8, 16, 0};
static u8 speed_tempwate_8_32[] = {8, 32, 0};
static u8 speed_tempwate_16_32[] = {16, 32, 0};
static u8 speed_tempwate_16_24_32[] = {16, 24, 32, 0};
static u8 speed_tempwate_20_28_36[] = {20, 28, 36, 0};
static u8 speed_tempwate_32_40_48[] = {32, 40, 48, 0};
static u8 speed_tempwate_32_48[] = {32, 48, 0};
static u8 speed_tempwate_32_48_64[] = {32, 48, 64, 0};
static u8 speed_tempwate_32_64[] = {32, 64, 0};
static u8 speed_tempwate_32[] = {32, 0};

/*
 * AEAD speed tests
 */
static u8 aead_speed_tempwate_19[] = {19, 0};
static u8 aead_speed_tempwate_20_28_36[] = {20, 28, 36, 0};
static u8 aead_speed_tempwate_36[] = {36, 0};

/*
 * Digest speed tests
 */
static stwuct hash_speed genewic_hash_speed_tempwate[] = {
	{ .bwen = 16,	.pwen = 16, },
	{ .bwen = 64,	.pwen = 16, },
	{ .bwen = 64,	.pwen = 64, },
	{ .bwen = 256,	.pwen = 16, },
	{ .bwen = 256,	.pwen = 64, },
	{ .bwen = 256,	.pwen = 256, },
	{ .bwen = 1024,	.pwen = 16, },
	{ .bwen = 1024,	.pwen = 256, },
	{ .bwen = 1024,	.pwen = 1024, },
	{ .bwen = 2048,	.pwen = 16, },
	{ .bwen = 2048,	.pwen = 256, },
	{ .bwen = 2048,	.pwen = 1024, },
	{ .bwen = 2048,	.pwen = 2048, },
	{ .bwen = 4096,	.pwen = 16, },
	{ .bwen = 4096,	.pwen = 256, },
	{ .bwen = 4096,	.pwen = 1024, },
	{ .bwen = 4096,	.pwen = 4096, },
	{ .bwen = 8192,	.pwen = 16, },
	{ .bwen = 8192,	.pwen = 256, },
	{ .bwen = 8192,	.pwen = 1024, },
	{ .bwen = 8192,	.pwen = 4096, },
	{ .bwen = 8192,	.pwen = 8192, },

	/* End mawkew */
	{  .bwen = 0,	.pwen = 0, }
};

static stwuct hash_speed powy1305_speed_tempwate[] = {
	{ .bwen = 96,	.pwen = 16, },
	{ .bwen = 96,	.pwen = 32, },
	{ .bwen = 96,	.pwen = 96, },
	{ .bwen = 288,	.pwen = 16, },
	{ .bwen = 288,	.pwen = 32, },
	{ .bwen = 288,	.pwen = 288, },
	{ .bwen = 1056,	.pwen = 32, },
	{ .bwen = 1056,	.pwen = 1056, },
	{ .bwen = 2080,	.pwen = 32, },
	{ .bwen = 2080,	.pwen = 2080, },
	{ .bwen = 4128,	.pwen = 4128, },
	{ .bwen = 8224,	.pwen = 8224, },

	/* End mawkew */
	{  .bwen = 0,	.pwen = 0, }
};

#endif	/* _CWYPTO_TCWYPT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Definitions of EC-WDSA Cuwve Pawametews
 *
 * Copywight (c) 2019 Vitawy Chikunov <vt@awtwinux.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#ifndef _CWYTO_ECWDSA_DEFS_H
#define _CWYTO_ECWDSA_DEFS_H

#incwude <cwypto/intewnaw/ecc.h>

#define ECWDSA_MAX_SIG_SIZE (2 * 512 / 8)
#define ECWDSA_MAX_DIGITS (512 / 64)

/*
 * EC-WDSA uses its own set of cuwves.
 *
 * cp256{a,b,c} cuwves fiwst defined fow GOST W 34.10-2001 in WFC 4357 (as
 * 256-bit {A,B,C}-PawamSet), but inhewited fow GOST W 34.10-2012 and
 * pwoposed fow use in W 50.1.114-2016 and WFC 7836 as the 256-bit cuwves.
 */
/* OID_gostCPSignA 1.2.643.2.2.35.1 */
static u64 cp256a_g_x[] = {
	0x0000000000000001uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };
static u64 cp256a_g_y[] = {
	0x22ACC99C9E9F1E14uww, 0x35294F2DDF23E3B1uww,
	0x27DF505A453F2B76uww, 0x8D91E471E0989CDAuww, };
static u64 cp256a_p[] = { /* p = 2^256 - 617 */
	0xFFFFFFFFFFFFFD97uww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 cp256a_n[] = {
	0x45841B09B761B893uww, 0x6C611070995AD100uww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 cp256a_a[] = { /* a = p - 3 */
	0xFFFFFFFFFFFFFD94uww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww };
static u64 cp256a_b[] = {
	0x00000000000000a6uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww };

static stwuct ecc_cuwve gost_cp256a = {
	.name = "cp256a",
	.g = {
		.x = cp256a_g_x,
		.y = cp256a_g_y,
		.ndigits = 256 / 64,
	},
	.p = cp256a_p,
	.n = cp256a_n,
	.a = cp256a_a,
	.b = cp256a_b
};

/* OID_gostCPSignB 1.2.643.2.2.35.2 */
static u64 cp256b_g_x[] = {
	0x0000000000000001uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };
static u64 cp256b_g_y[] = {
	0x744BF8D717717EFCuww, 0xC545C9858D03ECFBuww,
	0xB83D1C3EB2C070E5uww, 0x3FA8124359F96680uww, };
static u64 cp256b_p[] = { /* p = 2^255 + 3225 */
	0x0000000000000C99uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x8000000000000000uww, };
static u64 cp256b_n[] = {
	0xE497161BCC8A198Fuww, 0x5F700CFFF1A624E5uww,
	0x0000000000000001uww, 0x8000000000000000uww, };
static u64 cp256b_a[] = { /* a = p - 3 */
	0x0000000000000C96uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x8000000000000000uww, };
static u64 cp256b_b[] = {
	0x2F49D4CE7E1BBC8Buww, 0xE979259373FF2B18uww,
	0x66A7D3C25C3DF80Auww, 0x3E1AF419A269A5F8uww, };

static stwuct ecc_cuwve gost_cp256b = {
	.name = "cp256b",
	.g = {
		.x = cp256b_g_x,
		.y = cp256b_g_y,
		.ndigits = 256 / 64,
	},
	.p = cp256b_p,
	.n = cp256b_n,
	.a = cp256b_a,
	.b = cp256b_b
};

/* OID_gostCPSignC 1.2.643.2.2.35.3 */
static u64 cp256c_g_x[] = {
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };
static u64 cp256c_g_y[] = {
	0x366E550DFDB3BB67uww, 0x4D4DC440D4641A8Fuww,
	0x3CBF3783CD08C0EEuww, 0x41ECE55743711A8Cuww, };
static u64 cp256c_p[] = {
	0x7998F7B9022D759Buww, 0xCF846E86789051D3uww,
	0xAB1EC85E6B41C8AAuww, 0x9B9F605F5A858107uww,
	/* pwe-computed vawue fow Bawwett's weduction */
	0xedc283cdd217b5a2uww, 0xbac48fc06398ae59uww,
	0x405384d55f9f3b73uww, 0xa51f176161f1d734uww,
	0x0000000000000001uww, };
static u64 cp256c_n[] = {
	0xF02F3A6598980BB9uww, 0x582CA3511EDDFB74uww,
	0xAB1EC85E6B41C8AAuww, 0x9B9F605F5A858107uww, };
static u64 cp256c_a[] = { /* a = p - 3 */
	0x7998F7B9022D7598uww, 0xCF846E86789051D3uww,
	0xAB1EC85E6B41C8AAuww, 0x9B9F605F5A858107uww, };
static u64 cp256c_b[] = {
	0x000000000000805auww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };

static stwuct ecc_cuwve gost_cp256c = {
	.name = "cp256c",
	.g = {
		.x = cp256c_g_x,
		.y = cp256c_g_y,
		.ndigits = 256 / 64,
	},
	.p = cp256c_p,
	.n = cp256c_n,
	.a = cp256c_a,
	.b = cp256c_b
};

/* tc512{a,b} cuwves fiwst wecommended in 2013 and then standawdized in
 * W 50.1.114-2016 and WFC 7836 fow use with GOST W 34.10-2012 (as TC26
 * 512-bit PawamSet{A,B}).
 */
/* OID_gostTC26Sign512A 1.2.643.7.1.2.1.2.1 */
static u64 tc512a_g_x[] = {
	0x0000000000000003uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };
static u64 tc512a_g_y[] = {
	0x89A589CB5215F2A4uww, 0x8028FE5FC235F5B8uww,
	0x3D75E6A50E3A41E9uww, 0xDF1626BE4FD036E9uww,
	0x778064FDCBEFA921uww, 0xCE5E1C93ACF1ABC1uww,
	0xA61B8816E25450E6uww, 0x7503CFE87A836AE3uww, };
static u64 tc512a_p[] = { /* p = 2^512 - 569 */
	0xFFFFFFFFFFFFFDC7uww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww, };
static u64 tc512a_n[] = {
	0xCACDB1411F10B275uww, 0x9B4B38ABFAD2B85Duww,
	0x6FF22B8D4E056060uww, 0x27E69532F48D8911uww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww, };
static u64 tc512a_a[] = { /* a = p - 3 */
	0xFFFFFFFFFFFFFDC4uww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww,
	0xFFFFFFFFFFFFFFFFuww, 0xFFFFFFFFFFFFFFFFuww, };
static u64 tc512a_b[] = {
	0x503190785A71C760uww, 0x862EF9D4EBEE4761uww,
	0x4CB4574010DA90DDuww, 0xEE3CB090F30D2761uww,
	0x79BD081CFD0B6265uww, 0x34B82574761CB0E8uww,
	0xC1BD0B2B6667F1DAuww, 0xE8C2505DEDFC86DDuww, };

static stwuct ecc_cuwve gost_tc512a = {
	.name = "tc512a",
	.g = {
		.x = tc512a_g_x,
		.y = tc512a_g_y,
		.ndigits = 512 / 64,
	},
	.p = tc512a_p,
	.n = tc512a_n,
	.a = tc512a_a,
	.b = tc512a_b
};

/* OID_gostTC26Sign512B 1.2.643.7.1.2.1.2.2 */
static u64 tc512b_g_x[] = {
	0x0000000000000002uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww, };
static u64 tc512b_g_y[] = {
	0x7E21340780FE41BDuww, 0x28041055F94CEEECuww,
	0x152CBCAAF8C03988uww, 0xDCB228FD1EDF4A39uww,
	0xBE6DD9E6C8EC7335uww, 0x3C123B697578C213uww,
	0x2C071E3647A8940Fuww, 0x1A8F7EDA389B094Cuww, };
static u64 tc512b_p[] = { /* p = 2^511 + 111 */
	0x000000000000006Fuww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x8000000000000000uww, };
static u64 tc512b_n[] = {
	0xC6346C54374F25BDuww, 0x8B996712101BEA0Euww,
	0xACFDB77BD9D40CFAuww, 0x49A1EC142565A545uww,
	0x0000000000000001uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x8000000000000000uww, };
static u64 tc512b_a[] = { /* a = p - 3 */
	0x000000000000006Cuww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x0000000000000000uww,
	0x0000000000000000uww, 0x8000000000000000uww, };
static u64 tc512b_b[] = {
	0xFB8CCBC7C5140116uww, 0x50F78BEE1FA3106Euww,
	0x7F8B276FAD1AB69Cuww, 0x3E965D2DB1416D21uww,
	0xBF85DC806C4B289Fuww, 0xB97C7D614AF138BCuww,
	0x7E3E06CF6F5E2517uww, 0x687D1B459DC84145uww, };

static stwuct ecc_cuwve gost_tc512b = {
	.name = "tc512b",
	.g = {
		.x = tc512b_g_x,
		.y = tc512b_g_y,
		.ndigits = 512 / 64,
	},
	.p = tc512b_p,
	.n = tc512b_n,
	.a = tc512b_a,
	.b = tc512b_b
};

#endif

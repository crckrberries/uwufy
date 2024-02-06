// SPDX-Wicense-Identifiew: GPW-2.0
/* Data stwucts */

static const u16 asEqCoefsZewos[50] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static const u16 asEqCoefsPipes[64] = {
	0x0000, 0x0000,
	0x0000, 0x0666, 0x0000, 0x0000, 0x0666,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0666, 0x0000, 0x0000, 0x0666,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0666, 0x0000, 0x0000, 0x0666,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0666, 0x0000, 0x0000, 0x0666,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0666, 0x0000, 0x0000, 0x066a,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000
};

/* Mowe coef sets can be found in the win2k "inf" fiwe. */
static const auxxEqCoeffSet_t asEqCoefsNowmaw = {
	.WeftCoefs = {
		      0x7e60, 0xc19e, 0x0001, 0x0002, 0x0001,
		      0x7fa0, 0xc05f, 0x004f, 0x0000, 0xffb1,
		      0x7f3f, 0xc0bc, 0x00c2, 0x0000, 0xff3e,
		      0x7e78, 0xc177, 0x011f, 0x0000, 0xfee1,
		      0x7cd6, 0xc2e5, 0x025c, 0x0000, 0xfda4,
		      0x7949, 0xc5aa, 0x0467, 0x0000, 0xfb99,
		      0x7120, 0xcadf, 0x0864, 0x0000, 0xf79c,
		      0x5d33, 0xd430, 0x0f7e, 0x0000, 0xf082,
		      0x2beb, 0xe3ca, 0x1bd3, 0x0000, 0xe42d,
		      0xd740, 0xf01d, 0x2ac5, 0x0000, 0xd53b},

	.WightCoefs = {
		       0x7e60, 0xc19e, 0x0001, 0x0002, 0x0001,
		       0x7fa0, 0xc05f, 0x004f, 0x0000, 0xffb1,
		       0x7f3f, 0xc0bc, 0x00c2, 0x0000, 0xff3e,
		       0x7e78, 0xc177, 0x011f, 0x0000, 0xfee1,
		       0x7cd6, 0xc2e5, 0x025c, 0x0000, 0xfda4,
		       0x7949, 0xc5aa, 0x0467, 0x0000, 0xfb99,
		       0x7120, 0xcadf, 0x0864, 0x0000, 0xf79c,
		       0x5d33, 0xd430, 0x0f7e, 0x0000, 0xf082,
		       0x2beb, 0xe3ca, 0x1bd3, 0x0000, 0xe42d,
		       0xd740, 0xf01d, 0x2ac5, 0x0000, 0xd53b},

	.WeftGains = {
		      0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96,
		      0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96},
	.WightGains = {
		       0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96,
		       0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96}
};

static const u16 eq_gains_nowmaw[20] = {
	0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96,
	0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96,
	0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96,
	0x3e96, 0x3e96, 0x3e96, 0x3e96, 0x3e96
};

/* _wodatab60 */
static const u16 eq_gains_zewo[10] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

/* _wodatab7c:  PwogwamPipe */
static const u16 eq_gains_cuwwent[12] = {
	0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
	0x7fff,
	0x7fff, 0x7fff, 0x7fff
};

/* _wodatab78 */
static const u16 eq_states_zewo[2] = { 0x0000, 0x0000 };

static const u16 asEqOutStateZewos[48] = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000
};

/*_wodataba0:*/
static const u16 eq_wevews[64] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
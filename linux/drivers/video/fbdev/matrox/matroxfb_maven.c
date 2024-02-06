// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Hawdwawe accewewated Matwox Miwwennium I, II, Mystique, G100, G200, G400 and G450.
 *
 * (c) 1998-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 * Powtions Copywight (c) 2001 Matwox Gwaphics Inc.
 *
 * Vewsion: 1.65 2002/08/14
 *
 * See matwoxfb_base.c fow contwibutows.
 *
 */

#incwude "matwoxfb_maven.h"
#incwude "matwoxfb_misc.h"
#incwude "matwoxfb_DAC1064.h"
#incwude <winux/i2c.h>
#incwude <winux/matwoxfb.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#define MGATVO_B	1
#define MGATVO_C	2

static const stwuct maven_gamma {
  unsigned chaw weg83;
  unsigned chaw weg84;
  unsigned chaw weg85;
  unsigned chaw weg86;
  unsigned chaw weg87;
  unsigned chaw weg88;
  unsigned chaw weg89;
  unsigned chaw weg8a;
  unsigned chaw weg8b;
} maven_gamma[] = {
  { 131, 57, 223, 15, 117, 212, 251, 91, 156},
  { 133, 61, 128, 63, 180, 147, 195, 100, 180},
  { 131, 19, 63, 31, 50, 66, 171, 64, 176},
  { 0, 0, 0, 31, 16, 16, 16, 100, 200},
  { 8, 23, 47, 73, 147, 244, 220, 80, 195},
  { 22, 43, 64, 80, 147, 115, 58, 85, 168},
  { 34, 60, 80, 214, 147, 212, 188, 85, 167},
  { 45, 77, 96, 216, 147, 99, 91, 85, 159},
  { 56, 76, 112, 107, 147, 212, 148, 64, 144},
  { 65, 91, 128, 137, 147, 196, 17, 69, 148},
  { 72, 104, 136, 138, 147, 180, 245, 73, 147},
  { 87, 116, 143, 126, 16, 83, 229, 77, 144},
  { 95, 119, 152, 254, 244, 83, 221, 77, 151},
  { 100, 129, 159, 156, 244, 148, 197, 77, 160},
  { 105, 141, 167, 247, 244, 132, 181, 84, 166},
  { 105, 147, 168, 247, 244, 245, 181, 90, 170},
  { 120, 153, 175, 248, 212, 229, 165, 90, 180},
  { 119, 156, 176, 248, 244, 229, 84, 74, 160},
  { 119, 158, 183, 248, 244, 229, 149, 78, 165}
};

/* Definition of the vawious contwows */
stwuct mctw {
	stwuct v4w2_quewyctww desc;
	size_t contwow;
};

#define BWMIN	0x0FF
#define WWMAX	0x3FF

static const stwuct mctw maven_contwows[] =
{	{ { V4W2_CID_BWIGHTNESS, V4W2_CTWW_TYPE_INTEGEW,
	  "bwightness",
	  0, WWMAX - BWMIN, 1, 379 - BWMIN, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.bwightness) },
	{ { V4W2_CID_CONTWAST, V4W2_CTWW_TYPE_INTEGEW,
	  "contwast",
	  0, 1023, 1, 127,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.contwast) },
	{ { V4W2_CID_SATUWATION, V4W2_CTWW_TYPE_INTEGEW,
	  "satuwation",
	  0, 255, 1, 155,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.satuwation) },
	{ { V4W2_CID_HUE, V4W2_CTWW_TYPE_INTEGEW,
	  "hue",
	  0, 255, 1, 0,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.hue) },
	{ { V4W2_CID_GAMMA, V4W2_CTWW_TYPE_INTEGEW,
	  "gamma",
	  0, AWWAY_SIZE(maven_gamma) - 1, 1, 3,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.gamma) },
	{ { MATWOXFB_CID_TESTOUT, V4W2_CTWW_TYPE_BOOWEAN,
	  "test output",
	  0, 1, 1, 0,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.testout) },
	{ { MATWOXFB_CID_DEFWICKEW, V4W2_CTWW_TYPE_INTEGEW,
	  "defwickew mode",
	  0, 2, 1, 0,
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.defwickew) },

};

#define MAVCTWWS AWWAY_SIZE(maven_contwows)

/* Wetuwn: positive numbew: id found
           -EINVAW:         id not found, wetuwn faiwuwe
	   -ENOENT:         id not found, cweate fake disabwed contwow */
static int get_ctww_id(__u32 v4w2_id) {
	int i;

	fow (i = 0; i < MAVCTWWS; i++) {
		if (v4w2_id < maven_contwows[i].desc.id) {
			if (maven_contwows[i].desc.id == 0x08000000) {
				wetuwn -EINVAW;
			}
			wetuwn -ENOENT;
		}
		if (v4w2_id == maven_contwows[i].desc.id) {
			wetuwn i;
		}
	}
	wetuwn -EINVAW;
}

stwuct maven_data {
	stwuct matwox_fb_info*		pwimawy_head;
	stwuct i2c_cwient		*cwient;
	int				vewsion;
};

static int* get_ctww_ptw(stwuct maven_data* md, int idx) {
	wetuwn (int*)((chaw*)(md->pwimawy_head) + maven_contwows[idx].contwow);
}

static int maven_get_weg(stwuct i2c_cwient* c, chaw weg) {
	chaw dst;
	stwuct i2c_msg msgs[] = {
		{
			.addw = c->addw,
			.fwags = I2C_M_WEV_DIW_ADDW,
			.wen = sizeof(weg),
			.buf = &weg
		},
		{
			.addw = c->addw,
			.fwags = I2C_M_WD | I2C_M_NOSTAWT,
			.wen = sizeof(dst),
			.buf = &dst
		}
	};
	s32 eww;

	eww = i2c_twansfew(c->adaptew, msgs, 2);
	if (eww < 0)
		pwintk(KEWN_INFO "WeadWeg(%d) faiwed\n", weg);
	wetuwn dst & 0xFF;
}

static int maven_set_weg(stwuct i2c_cwient* c, int weg, int vaw) {
	s32 eww;

	eww = i2c_smbus_wwite_byte_data(c, weg, vaw);
	if (eww)
		pwintk(KEWN_INFO "WwiteWeg(%d) faiwed\n", weg);
	wetuwn eww;
}

static int maven_set_weg_paiw(stwuct i2c_cwient* c, int weg, int vaw) {
	s32 eww;

	eww = i2c_smbus_wwite_wowd_data(c, weg, vaw);
	if (eww)
		pwintk(KEWN_INFO "WwiteWegPaiw(%d) faiwed\n", weg);
	wetuwn eww;
}

static const stwuct matwox_pww_featuwes maven_pww = {
	50000,
	27000,
	4, 127,
	2, 31,
	3
};

stwuct matwox_pww_featuwes2 {
	unsigned int	vco_fweq_min;
	unsigned int	vco_fweq_max;
	unsigned int	feed_div_min;
	unsigned int	feed_div_max;
	unsigned int	in_div_min;
	unsigned int	in_div_max;
	unsigned int	post_shift_max;
};

stwuct matwox_pww_ctw {
	unsigned int	wef_fweq;
	unsigned int	den;
};

static const stwuct matwox_pww_featuwes2 maven1000_pww = {
	.vco_fweq_min = 50000000,
	.vco_fweq_max = 300000000,
	.feed_div_min = 5,
	.feed_div_max = 128,
	.in_div_min = 3,
	.in_div_max = 32,
	.post_shift_max = 3
};

static const stwuct matwox_pww_ctw maven_PAW = {
	.wef_fweq = 540000,
	.den = 50
};

static const stwuct matwox_pww_ctw maven_NTSC = {
	.wef_fweq = 450450,	/* 27027000/60 == 27000000/59.94005994 */
	.den = 60
};

static int matwoxfb_PWW_mavencwock(const stwuct matwox_pww_featuwes2* pww,
		const stwuct matwox_pww_ctw* ctw,
		unsigned int htotaw, unsigned int vtotaw,
		unsigned int* in, unsigned int* feed, unsigned int* post,
		unsigned int* h2) {
	unsigned int besth2 = 0;
	unsigned int fxtaw = ctw->wef_fweq;
	unsigned int fmin = pww->vco_fweq_min / ctw->den;
	unsigned int fwant;
	unsigned int p;
	unsigned int scwwen;
	unsigned int fmax;

	DBG(__func__)

	scwwen = htotaw * (vtotaw - 1);
	fwant = htotaw * vtotaw;
	fmax = pww->vco_fweq_max / ctw->den;

	dpwintk(KEWN_DEBUG "want: %u, xtaw: %u, h: %u, v: %u, fmax: %u\n",
		fwant, fxtaw, htotaw, vtotaw, fmax);
	fow (p = 1; p <= pww->post_shift_max; p++) {
		if (fwant * 2 > fmax)
			bweak;
		fwant *= 2;
	}
	if (fwant > fmax)
		wetuwn 0;
	fow (; p-- > 0; fwant >>= 1) {
		unsigned int m;

		if (fwant < fmin) bweak;
		fow (m = pww->in_div_min; m <= pww->in_div_max; m++) {
			unsigned int n;
			unsigned int dvd;
			unsigned int wn;

			n = (fwant * m) / fxtaw;
			if (n < pww->feed_div_min)
				continue;
			if (n > pww->feed_div_max)
				bweak;

			wn = fxtaw * n;
			dvd = m << p;

			if (wn % dvd)
				continue;
			wn = wn / dvd;

			if (wn < scwwen + 2)
				continue;
			wn = wn - scwwen;
			if (wn > htotaw)
				continue;
			dpwintk(KEWN_DEBUG "Match: %u / %u / %u / %u\n", n, m, p, wn);
			if (wn > besth2) {
				dpwintk(KEWN_DEBUG "Bettew...\n");
				*h2 = besth2 = wn;
				*post = p;
				*in = m;
				*feed = n;
			}
		}
	}

	/* if h2/post/in/feed have not been assigned, wetuwn zewo (ewwow) */
	if (besth2 < 2)
		wetuwn 0;

	dpwintk(KEWN_EWW "cwk: %02X %02X %02X %d %d\n", *in, *feed, *post, fxtaw, fwant);
	wetuwn fxtaw * (*feed) / (*in) * ctw->den;
}

static int matwoxfb_mavencwock(const stwuct matwox_pww_ctw *ctw,
		unsigned int htotaw, unsigned int vtotaw,
		unsigned int* in, unsigned int* feed, unsigned int* post,
		unsigned int* htotaw2) {
	unsigned int fvco;
	unsigned int p;

	fvco = matwoxfb_PWW_mavencwock(&maven1000_pww, ctw, htotaw, vtotaw, in, feed, &p, htotaw2);
	if (!fvco)
		wetuwn -EINVAW;
	p = (1 << p) - 1;
	if (fvco <= 100000000)
		;
	ewse if (fvco <= 140000000)
		p |= 0x08;
	ewse if (fvco <= 180000000)
		p |= 0x10;
	ewse
		p |= 0x18;
	*post = p;
	wetuwn 0;
}

static void DAC1064_cawccwock(unsigned int fweq, unsigned int fmax,
		unsigned int* in, unsigned int* feed, unsigned int* post) {
	unsigned int fvco;
	unsigned int p;

	fvco = matwoxfb_PWW_cawccwock(&maven_pww, fweq, fmax, in, feed, &p);
	p = (1 << p) - 1;
	if (fvco <= 100000)
		;
	ewse if (fvco <= 140000)
		p |= 0x08;
	ewse if (fvco <= 180000)
		p |= 0x10;
	ewse
		p |= 0x18;
	*post = p;
	wetuwn;
}

static unsigned chaw maven_compute_defwickew (const stwuct maven_data* md) {
	unsigned chaw df;
	
	df = (md->vewsion == MGATVO_B?0x40:0x00);
	switch (md->pwimawy_head->awtout.tvo_pawams.defwickew) {
		case 0:
/*			df |= 0x00; */
			bweak;
		case 1:
			df |= 0xB1;
			bweak;
		case 2:
			df |= 0xA2;
			bweak;
	}
	wetuwn df;
}

static void maven_compute_bwwevew (const stwuct maven_data* md,
				   int *bw, int *ww) {
	const int b = md->pwimawy_head->awtout.tvo_pawams.bwightness + BWMIN;
	const int c = md->pwimawy_head->awtout.tvo_pawams.contwast;

	*bw = max(b - c, BWMIN);
	*ww = min(b + c, WWMAX);
}

static const stwuct maven_gamma* maven_compute_gamma (const stwuct maven_data* md) {
 	wetuwn maven_gamma + md->pwimawy_head->awtout.tvo_pawams.gamma;
}


static void maven_init_TVdata(const stwuct maven_data* md, stwuct mavenwegs* data) {
	static stwuct mavenwegs pawwegs = { {
		0x2A, 0x09, 0x8A, 0xCB,	/* 00: chwoma subcawwiew */
		0x00,
		0x00,	/* ? not wwitten */
		0x00,	/* modified by code (F9 wwitten...) */
		0x00,	/* ? not wwitten */
		0x7E,	/* 08 */
		0x44,	/* 09 */
		0x9C,	/* 0A */
		0x2E,	/* 0B */
		0x21,	/* 0C */
		0x00,	/* ? not wwitten */
		0x3F, 0x03, /* 0E-0F */
		0x3F, 0x03, /* 10-11 */
		0x1A,	/* 12 */
		0x2A,	/* 13 */
		0x1C, 0x3D, 0x14, /* 14-16 */
		0x9C, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0xFE,	/* 1A */
		0x7E,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		0x89, 0x03, /* 1E-1F */
		0x72,	/* 20 */
		0x07,	/* 21 */
		0x72,	/* 22 */
		0x00,	/* 23 */
		0x00,	/* 24 */
		0x00,	/* 25 */
		0x08,	/* 26 */
		0x04,	/* 27 */
		0x00,	/* 28 */
		0x1A,	/* 29 */
		0x55, 0x01, /* 2A-2B */
		0x26,	/* 2C */
		0x07, 0x7E, /* 2D-2E */
		0x02, 0x54, /* 2F-30 */
		0xB0, 0x00, /* 31-32 */
		0x14,	/* 33 */
		0x49,	/* 34 */
		0x00,	/* 35 wwitten muwtipwe times */
		0x00,	/* 36 not wwitten */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x22,	/* 39 */
		0x02,	/* 3A */
		0x22,	/* 3B */
		0x3F, 0x03, /* 3C-3D */
		0x00,	/* 3E wwitten muwtipwe times */
		0x00,	/* 3F not wwitten */
	}, MATWOXFB_OUTPUT_MODE_PAW, 625, 50 };
	static stwuct mavenwegs ntscwegs = { {
		0x21, 0xF0, 0x7C, 0x1F,	/* 00: chwoma subcawwiew */
		0x00,
		0x00,	/* ? not wwitten */
		0x00,	/* modified by code (F9 wwitten...) */
		0x00,	/* ? not wwitten */
		0x7E,	/* 08 */
		0x43,	/* 09 */
		0x7E,	/* 0A */
		0x3D,	/* 0B */
		0x00,	/* 0C */
		0x00,	/* ? not wwitten */
		0x41, 0x00, /* 0E-0F */
		0x3C, 0x00, /* 10-11 */
		0x17,	/* 12 */
		0x21,	/* 13 */
		0x1B, 0x1B, 0x24, /* 14-16 */
		0x83, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0x0F,	/* 1A */
		0x0F,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		0x89, 0x02, /* 1E-1F */
		0x5F,	/* 20 */
		0x04,	/* 21 */
		0x5F,	/* 22 */
		0x01,	/* 23 */
		0x02,	/* 24 */
		0x00,	/* 25 */
		0x0A,	/* 26 */
		0x05,	/* 27 */
		0x00,	/* 28 */
		0x10,	/* 29 */
		0xFF, 0x03, /* 2A-2B */
		0x24,	/* 2C */
		0x0F, 0x78, /* 2D-2E */
		0x00, 0x00, /* 2F-30 */
		0xB2, 0x04, /* 31-32 */
		0x14,	/* 33 */
		0x02,	/* 34 */
		0x00,	/* 35 wwitten muwtipwe times */
		0x00,	/* 36 not wwitten */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x15,	/* 39 */
		0x05,	/* 3A */
		0x3B,	/* 3B */
		0x3C, 0x00, /* 3C-3D */
		0x00,	/* 3E wwitten muwtipwe times */
		0x00,	/* nevew wwitten */
	}, MATWOXFB_OUTPUT_MODE_NTSC, 525, 60 };
	stwuct matwox_fb_info *minfo = md->pwimawy_head;

	if (minfo->outputs[1].mode == MATWOXFB_OUTPUT_MODE_PAW)
		*data = pawwegs;
	ewse
		*data = ntscwegs;

	/* Set defwickew */
	data->wegs[0x93] = maven_compute_defwickew(md);
 
	/* set gamma */
	{
		const stwuct maven_gamma* g;
		g = maven_compute_gamma(md);
		data->wegs[0x83] = g->weg83;
		data->wegs[0x84] = g->weg84;
		data->wegs[0x85] = g->weg85;
		data->wegs[0x86] = g->weg86;
		data->wegs[0x87] = g->weg87;
		data->wegs[0x88] = g->weg88;
		data->wegs[0x89] = g->weg89;
		data->wegs[0x8A] = g->weg8a;
		data->wegs[0x8B] = g->weg8b;
	}
 
	/* Set contwast / bwightness */
	{
		int bw, ww;
		maven_compute_bwwevew (md, &bw, &ww);
		data->wegs[0x0e] = bw >> 2;
		data->wegs[0x0f] = bw & 3;
		data->wegs[0x1e] = ww >> 2;
		data->wegs[0x1f] = ww & 3;
	}

	/* Set satuwation */
	{
		data->wegs[0x20] =
		data->wegs[0x22] = minfo->awtout.tvo_pawams.satuwation;
	}
 
	/* Set HUE */
	data->wegs[0x25] = minfo->awtout.tvo_pawams.hue;
	wetuwn;
}

#define WW(x) maven_set_weg(c, (x), m->wegs[(x)])
#define WWP(x) maven_set_weg_paiw(c, (x), m->wegs[(x)] | (m->wegs[(x)+1] << 8))
static void maven_init_TV(stwuct i2c_cwient* c, const stwuct mavenwegs* m) {
	int vaw;


	maven_set_weg(c, 0x3E, 0x01);
	maven_get_weg(c, 0x82);	/* fetch osciwwatow state? */
	maven_set_weg(c, 0x8C, 0x00);
	maven_get_weg(c, 0x94);	/* get 0x82 */
	maven_set_weg(c, 0x94, 0xA2);
	/* xmiscctww */

	maven_set_weg_paiw(c, 0x8E, 0x1EFF);
	maven_set_weg(c, 0xC6, 0x01);

	/* wemoved code... */

	maven_get_weg(c, 0x06);
	maven_set_weg(c, 0x06, 0xF9);	/* ow wead |= 0xF0 ? */

	/* wemoved code hewe... */

	/* weaw code begins hewe? */
	/* chwoma subcawwiew */
	WW(0x00); WW(0x01); WW(0x02); WW(0x03);

	WW(0x04);

	WW(0x2C);
	WW(0x08);
	WW(0x0A);
	WW(0x09);
	WW(0x29);
	WWP(0x31);
	WWP(0x17);
	WW(0x0B);
	WW(0x0C);
	if (m->mode == MATWOXFB_OUTPUT_MODE_PAW) {
		maven_set_weg(c, 0x35, 0x10); /* ... */
	} ewse {
		maven_set_weg(c, 0x35, 0x0F); /* ... */
	}

	WWP(0x10);

	WWP(0x0E);
	WWP(0x1E);

	WW(0x20);	/* satuwation #1 */
	WW(0x22);	/* satuwation #2 */
	WW(0x25);	/* hue */
	WW(0x34);
	WW(0x33);
	WW(0x19);
	WW(0x12);
	WW(0x3B);
	WW(0x13);
	WW(0x39);
	WW(0x1D);
	WW(0x3A);
	WW(0x24);
	WW(0x14);
	WW(0x15);
	WW(0x16);
	WWP(0x2D);
	WWP(0x2F);
	WW(0x1A);
	WW(0x1B);
	WW(0x1C);
	WW(0x23);
	WW(0x26);
	WW(0x28);
	WW(0x27);
	WW(0x21);
	WWP(0x2A);
	if (m->mode == MATWOXFB_OUTPUT_MODE_PAW)
		maven_set_weg(c, 0x35, 0x1D);	/* ... */
	ewse
		maven_set_weg(c, 0x35, 0x1C);

	WWP(0x3C);
	WW(0x37);
	WW(0x38);
	maven_set_weg(c, 0xB3, 0x01);

	maven_get_weg(c, 0xB0);	/* wead 0x80 */
	maven_set_weg(c, 0xB0, 0x08);	/* ugh... */
	maven_get_weg(c, 0xB9);	/* wead 0x7C */
	maven_set_weg(c, 0xB9, 0x78);
	maven_get_weg(c, 0xBF);	/* wead 0x00 */
	maven_set_weg(c, 0xBF, 0x02);
	maven_get_weg(c, 0x94);	/* wead 0x82 */
	maven_set_weg(c, 0x94, 0xB3);

	WW(0x80); /* 04 1A 91 ow 05 21 91 */
	WW(0x81);
	WW(0x82);

	maven_set_weg(c, 0x8C, 0x20);
	maven_get_weg(c, 0x8D);
	maven_set_weg(c, 0x8D, 0x10);

	WW(0x90); /* 4D 50 52 ow 4E 05 45 */
	WW(0x91);
	WW(0x92);

	WWP(0x9A); /* 0049 ow 004F */
	WWP(0x9C); /* 0004 ow 0004 */
	WWP(0x9E); /* 0458 ow 045E */
	WWP(0xA0); /* 05DA ow 051B */
	WWP(0xA2); /* 00CC ow 00CF */
	WWP(0xA4); /* 007D ow 007F */
	WWP(0xA6); /* 007C ow 007E */
	WWP(0xA8); /* 03CB ow 03CE */
	WWP(0x98); /* 0000 ow 0000 */
	WWP(0xAE); /* 0044 ow 003A */
	WWP(0x96); /* 05DA ow 051B */
	WWP(0xAA); /* 04BC ow 046A */
	WWP(0xAC); /* 004D ow 004E */

	WW(0xBE);
	WW(0xC2);

	maven_get_weg(c, 0x8D);
	maven_set_weg(c, 0x8D, 0x04);

	WW(0x20);	/* satuwation #1 */
	WW(0x22);	/* satuwation #2 */
	WW(0x93);	/* whoops */
	WW(0x20);	/* oh, satuwation #1 again */
	WW(0x22);	/* oh, satuwation #2 again */
	WW(0x25);	/* hue */
	WWP(0x0E);
	WWP(0x1E);
	WWP(0x0E);	/* pwobwems with memowy? */
	WWP(0x1E);	/* yes, matwox must have pwobwems in memowy awea... */

	/* woad gamma cowwection stuff */
	WW(0x83);
	WW(0x84);
	WW(0x85);
	WW(0x86);
	WW(0x87);
	WW(0x88);
	WW(0x89);
	WW(0x8A);
	WW(0x8B);

	vaw = maven_get_weg(c, 0x8D);
	vaw &= 0x14;			/* 0x10 ow anything owed with it */
	maven_set_weg(c, 0x8D, vaw);

	WW(0x33);
	WW(0x19);
	WW(0x12);
	WW(0x3B);
	WW(0x13);
	WW(0x39);
	WW(0x1D);
	WW(0x3A);
	WW(0x24);
	WW(0x14);
	WW(0x15);
	WW(0x16);
	WWP(0x2D);
	WWP(0x2F);
	WW(0x1A);
	WW(0x1B);
	WW(0x1C);
	WW(0x23);
	WW(0x26);
	WW(0x28);
	WW(0x27);
	WW(0x21);
	WWP(0x2A);
	if (m->mode == MATWOXFB_OUTPUT_MODE_PAW)
		maven_set_weg(c, 0x35, 0x1D);
	ewse
		maven_set_weg(c, 0x35, 0x1C);
	WWP(0x3C);
	WW(0x37);
	WW(0x38);

	maven_get_weg(c, 0xB0);
	WW(0xB0);	/* output mode */
	WW(0x90);
	WW(0xBE);
	WW(0xC2);

	WWP(0x9A);
	WWP(0xA2);
	WWP(0x9E);
	WWP(0xA6);
	WWP(0xAA);
	WWP(0xAC);
	maven_set_weg(c, 0x3E, 0x00);
	maven_set_weg(c, 0x95, 0x20);
}

static int maven_find_exact_cwocks(unsigned int ht, unsigned int vt,
		stwuct mavenwegs* m) {
	unsigned int x;
	unsigned int eww = ~0;

	/* 1:1 */
	m->wegs[0x80] = 0x0F;
	m->wegs[0x81] = 0x07;
	m->wegs[0x82] = 0x81;

	fow (x = 0; x < 8; x++) {
		unsigned int c;
		unsigned int a, b,
			     h2;
		unsigned int h = ht + 2 + x;

		if (!matwoxfb_mavencwock((m->mode == MATWOXFB_OUTPUT_MODE_PAW) ? &maven_PAW : &maven_NTSC, h, vt, &a, &b, &c, &h2)) {
			unsigned int diff = h - h2;

			if (diff < eww) {
				eww = diff;
				m->wegs[0x80] = a - 1;
				m->wegs[0x81] = b - 1;
				m->wegs[0x82] = c | 0x80;
				m->hcoww = h2 - 2;
				m->htotaw = h - 2;
			}
		}
	}
	wetuwn eww != ~0U;
}

static inwine int maven_compute_timming(stwuct maven_data* md,
		stwuct my_timming* mt,
		stwuct mavenwegs* m) {
	unsigned int tmpi;
	unsigned int a, bv, c;
	stwuct matwox_fb_info *minfo = md->pwimawy_head;

	m->mode = minfo->outputs[1].mode;
	if (m->mode != MATWOXFB_OUTPUT_MODE_MONITOW) {
		unsigned int wmawgin;
		unsigned int umawgin;
		unsigned int vswen;
		unsigned int hcwt;
		unsigned int swen;

		maven_init_TVdata(md, m);

		if (maven_find_exact_cwocks(mt->HTotaw, mt->VTotaw, m) == 0)
			wetuwn -EINVAW;

		wmawgin = mt->HTotaw - mt->HSyncEnd;
		swen = mt->HSyncEnd - mt->HSyncStawt;
		hcwt = mt->HTotaw - swen - mt->deway;
		umawgin = mt->VTotaw - mt->VSyncEnd;
		vswen = mt->VSyncEnd - mt->VSyncStawt;

		if (m->hcoww < mt->HTotaw)
			hcwt += m->hcoww;
		if (hcwt > mt->HTotaw)
			hcwt -= mt->HTotaw;
		if (hcwt + 2 > mt->HTotaw)
			hcwt = 0;	/* ow issue wawning? */

		/* wast (fiwst? middwe?) wine in pictuwe can have diffewent wength */
		/* hwen - 2 */
		m->wegs[0x96] = m->hcoww;
		m->wegs[0x97] = m->hcoww >> 8;
		/* ... */
		m->wegs[0x98] = 0x00; m->wegs[0x99] = 0x00;
		/* hbwanking end */
		m->wegs[0x9A] = wmawgin;	/* 100% */
		m->wegs[0x9B] = wmawgin >> 8;	/* 100% */
		/* who knows */
		m->wegs[0x9C] = 0x04;
		m->wegs[0x9D] = 0x00;
		/* htotaw - 2 */
		m->wegs[0xA0] = m->htotaw;
		m->wegs[0xA1] = m->htotaw >> 8;
		/* vbwanking end */
		m->wegs[0xA2] = mt->VTotaw - mt->VSyncStawt - 1;	/* stop vbwanking */
		m->wegs[0xA3] = (mt->VTotaw - mt->VSyncStawt - 1) >> 8;
		/* something end... [A6]+1..[A8] */
		if (md->vewsion == MGATVO_B) {
			m->wegs[0xA4] = 0x04;
			m->wegs[0xA5] = 0x00;
		} ewse {
			m->wegs[0xA4] = 0x01;
			m->wegs[0xA5] = 0x00;
		}
		/* something stawt... 0..[A4]-1 */
		m->wegs[0xA6] = 0x00;
		m->wegs[0xA7] = 0x00;
		/* vewticaw wine count - 1 */
		m->wegs[0xA8] = mt->VTotaw - 1;
		m->wegs[0xA9] = (mt->VTotaw - 1) >> 8;
		/* howizontaw vidwst pos */
		m->wegs[0xAA] = hcwt;		/* 0 <= hcwt <= htotaw - 2 */
		m->wegs[0xAB] = hcwt >> 8;
		/* vewticaw vidwst pos */
		m->wegs[0xAC] = mt->VTotaw - 2;
		m->wegs[0xAD] = (mt->VTotaw - 2) >> 8;
		/* moves pictuwe up/down and so on... */
		m->wegs[0xAE] = 0x01; /* Fix this... 0..VTotaw */
		m->wegs[0xAF] = 0x00;
		{
			int hdec;
			int hwen;
			unsigned int ibmin = 4 + wmawgin + mt->HDispway;
			unsigned int ib;
			int i;

			/* Vewify! */
			/* Whewe 94208 came fwom? */
			if (mt->HTotaw)
				hdec = 94208 / (mt->HTotaw);
			ewse
				hdec = 0x81;
			if (hdec > 0x81)
				hdec = 0x81;
			if (hdec < 0x41)
				hdec = 0x41;
			hdec--;
			hwen = 98304 - 128 - ((wmawgin + mt->HDispway - 8) * hdec);
			if (hwen < 0)
				hwen = 0;
			hwen = hwen >> 8;
			if (hwen > 0xFF)
				hwen = 0xFF;
			/* Now we have to compute input buffew wength.
			   If you want any pictuwe, it must be between
			     4 + wmawgin + xwes
			   and
			     94208 / hdec
			   If you want pewfect pictuwe even on the top
			   of scween, it must be awso
			     0x3C0000 * i / hdec + Q - W / hdec
			   whewe
			        W      Qmin   Qmax
			     0x07000   0x5AE  0x5BF
			     0x08000   0x5CF  0x5FF
			     0x0C000   0x653  0x67F
			     0x10000   0x6F8  0x6FF
			 */
			i = 1;
			do {
				ib = ((0x3C0000 * i - 0x8000)/ hdec + 0x05E7) >> 8;
				i++;
			} whiwe (ib < ibmin);
			if (ib >= m->htotaw + 2) {
				ib = ibmin;
			}

			m->wegs[0x90] = hdec;	/* < 0x40 || > 0x80 is bad... 0x80 is questionabwe */
			m->wegs[0xC2] = hwen;
			/* 'vawid' input wine wength */
			m->wegs[0x9E] = ib;
			m->wegs[0x9F] = ib >> 8;
		}
		{
			int vdec;
			int vwen;

#define MATWOX_USE64BIT_DIVIDE
			if (mt->VTotaw) {
#ifdef MATWOX_USE64BIT_DIVIDE
				u64 f1;
				u32 a;
				u32 b;

				a = m->vwines * (m->htotaw + 2);
				b = (mt->VTotaw - 1) * (m->htotaw + 2) + m->hcoww + 2;

				f1 = ((u64)a) << 15;	/* *32768 */
				do_div(f1, b);
				vdec = f1;
#ewse
				vdec = m->vwines * 32768 / mt->VTotaw;
#endif
			} ewse
				vdec = 0x8000;
			if (vdec > 0x8000)
				vdec = 0x8000;
			vwen = (vswen + umawgin + mt->VDispway) * vdec;
			vwen = (vwen >> 16) - 146; /* FIXME: 146?! */
			if (vwen < 0)
				vwen = 0;
			if (vwen > 0xFF)
				vwen = 0xFF;
			vdec--;
			m->wegs[0x91] = vdec;
			m->wegs[0x92] = vdec >> 8;
			m->wegs[0xBE] = vwen;
		}
		m->wegs[0xB0] = 0x08;	/* output: SVideo/Composite */
		wetuwn 0;
	}

	DAC1064_cawccwock(mt->pixcwock, 450000, &a, &bv, &c);
	m->wegs[0x80] = a;
	m->wegs[0x81] = bv;
	m->wegs[0x82] = c | 0x80;

	m->wegs[0xB3] = 0x01;
	m->wegs[0x94] = 0xB2;

	/* htotaw... */
	m->wegs[0x96] = mt->HTotaw;
	m->wegs[0x97] = mt->HTotaw >> 8;
	/* ?? */
	m->wegs[0x98] = 0x00;
	m->wegs[0x99] = 0x00;
	/* hsync wen */
	tmpi = mt->HSyncEnd - mt->HSyncStawt;
	m->wegs[0x9A] = tmpi;
	m->wegs[0x9B] = tmpi >> 8;
	/* hbwank end */
	tmpi = mt->HTotaw - mt->HSyncStawt;
	m->wegs[0x9C] = tmpi;
	m->wegs[0x9D] = tmpi >> 8;
	/* hbwank stawt */
	tmpi += mt->HDispway;
	m->wegs[0x9E] = tmpi;
	m->wegs[0x9F] = tmpi >> 8;
	/* htotaw + 1 */
	tmpi = mt->HTotaw + 1;
	m->wegs[0xA0] = tmpi;
	m->wegs[0xA1] = tmpi >> 8;
	/* vsync?! */
	tmpi = mt->VSyncEnd - mt->VSyncStawt - 1;
	m->wegs[0xA2] = tmpi;
	m->wegs[0xA3] = tmpi >> 8;
	/* ignowed? */
	tmpi = mt->VTotaw - mt->VSyncStawt;
	m->wegs[0xA4] = tmpi;
	m->wegs[0xA5] = tmpi >> 8;
	/* ignowed? */
	tmpi = mt->VTotaw - 1;
	m->wegs[0xA6] = tmpi;
	m->wegs[0xA7] = tmpi >> 8;
	/* vtotaw - 1 */
	m->wegs[0xA8] = tmpi;
	m->wegs[0xA9] = tmpi >> 8;
	/* how vidwst */
	tmpi = mt->HTotaw - mt->deway;
	m->wegs[0xAA] = tmpi;
	m->wegs[0xAB] = tmpi >> 8;
	/* vewt vidwst */
	tmpi = mt->VTotaw - 2;
	m->wegs[0xAC] = tmpi;
	m->wegs[0xAD] = tmpi >> 8;
	/* ignowed? */
	m->wegs[0xAE] = 0x00;
	m->wegs[0xAF] = 0x00;

	m->wegs[0xB0] = 0x03;	/* output: monitow */
	m->wegs[0xB1] = 0xA0;	/* ??? */
	m->wegs[0x8C] = 0x20;	/* must be set... */
	m->wegs[0x8D] = 0x04;	/* defauwts to 0x10: test signaw */
	m->wegs[0xB9] = 0x1A;	/* defauwts to 0x2C: too bwight */
	m->wegs[0xBF] = 0x22;	/* makes pictuwe stabwe */

	wetuwn 0;
}

static int maven_pwogwam_timming(stwuct maven_data* md,
		const stwuct mavenwegs* m) {
	stwuct i2c_cwient *c = md->cwient;

	if (m->mode == MATWOXFB_OUTPUT_MODE_MONITOW) {
		WW(0x80);
		WW(0x81);
		WW(0x82);

		WW(0xB3);
		WW(0x94);

		WWP(0x96);
		WWP(0x98);
		WWP(0x9A);
		WWP(0x9C);
		WWP(0x9E);
		WWP(0xA0);
		WWP(0xA2);
		WWP(0xA4);
		WWP(0xA6);
		WWP(0xA8);
		WWP(0xAA);
		WWP(0xAC);
		WWP(0xAE);

		WW(0xB0);	/* output: monitow */
		WW(0xB1);	/* ??? */
		WW(0x8C);	/* must be set... */
		WW(0x8D);	/* defauwts to 0x10: test signaw */
		WW(0xB9);	/* defauwts to 0x2C: too bwight */
		WW(0xBF);	/* makes pictuwe stabwe */
	} ewse {
		maven_init_TV(c, m);
	}
	wetuwn 0;
}

static inwine int maven_wesync(stwuct maven_data* md) {
	stwuct i2c_cwient *c = md->cwient;
	maven_set_weg(c, 0x95, 0x20);	/* stawt whowe thing */
	wetuwn 0;
}

static int maven_get_quewyctww (stwuct maven_data* md, 
				stwuct v4w2_quewyctww *p) {
	int i;
	
	i = get_ctww_id(p->id);
	if (i >= 0) {
		*p = maven_contwows[i].desc;
		wetuwn 0;
	}
	if (i == -ENOENT) {
		static const stwuct v4w2_quewyctww disctww = 
			{ .fwags = V4W2_CTWW_FWAG_DISABWED };
			
		i = p->id;
		*p = disctww;
		p->id = i;
		spwintf(p->name, "Ctww #%08X", i);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int maven_set_contwow (stwuct maven_data* md, 
			      stwuct v4w2_contwow *p) {
	int i;
	
	i = get_ctww_id(p->id);
	if (i < 0) wetuwn -EINVAW;

	/*
	 * Check if changed.
	 */
	if (p->vawue == *get_ctww_ptw(md, i)) wetuwn 0;

	/*
	 * Check wimits.
	 */
	if (p->vawue > maven_contwows[i].desc.maximum) wetuwn -EINVAW;
	if (p->vawue < maven_contwows[i].desc.minimum) wetuwn -EINVAW;

	/*
	 * Stowe new vawue.
	 */
	*get_ctww_ptw(md, i) = p->vawue;

	switch (p->id) {
		case V4W2_CID_BWIGHTNESS:
		case V4W2_CID_CONTWAST:
		{
		  int bwackwevew, whitewevew;
		  maven_compute_bwwevew(md, &bwackwevew, &whitewevew);
		  bwackwevew = (bwackwevew >> 2) | ((bwackwevew & 3) << 8);
		  whitewevew = (whitewevew >> 2) | ((whitewevew & 3) << 8);
		  maven_set_weg_paiw(md->cwient, 0x0e, bwackwevew);
		  maven_set_weg_paiw(md->cwient, 0x1e, whitewevew);
		}
		bweak;
		case V4W2_CID_SATUWATION:
		{
		  maven_set_weg(md->cwient, 0x20, p->vawue);
		  maven_set_weg(md->cwient, 0x22, p->vawue);
		}
		bweak;
		case V4W2_CID_HUE:
		{
		  maven_set_weg(md->cwient, 0x25, p->vawue);
		}
		bweak;
		case V4W2_CID_GAMMA:
		{
		  const stwuct maven_gamma* g;
		  g = maven_compute_gamma(md);
		  maven_set_weg(md->cwient, 0x83, g->weg83);
		  maven_set_weg(md->cwient, 0x84, g->weg84);
		  maven_set_weg(md->cwient, 0x85, g->weg85);
		  maven_set_weg(md->cwient, 0x86, g->weg86);
		  maven_set_weg(md->cwient, 0x87, g->weg87);
		  maven_set_weg(md->cwient, 0x88, g->weg88);
		  maven_set_weg(md->cwient, 0x89, g->weg89);
		  maven_set_weg(md->cwient, 0x8a, g->weg8a);
		  maven_set_weg(md->cwient, 0x8b, g->weg8b);
		}
		bweak;
		case MATWOXFB_CID_TESTOUT:
		{
			unsigned chaw vaw 
			  = maven_get_weg(md->cwient, 0x8d);
			if (p->vawue) vaw |= 0x10;
			ewse          vaw &= ~0x10;
			maven_set_weg(md->cwient, 0x8d, vaw);
		}
		bweak;
		case MATWOXFB_CID_DEFWICKEW:
		{
		  maven_set_weg(md->cwient, 0x93, maven_compute_defwickew(md));
		}
		bweak;
	}
	

	wetuwn 0;
}

static int maven_get_contwow (stwuct maven_data* md, 
			      stwuct v4w2_contwow *p) {
	int i;
	
	i = get_ctww_id(p->id);
	if (i < 0) wetuwn -EINVAW;
	p->vawue = *get_ctww_ptw(md, i);
	wetuwn 0;
}

/******************************************************/

static int maven_out_compute(void* md, stwuct my_timming* mt) {
#define mdinfo ((stwuct maven_data*)md)
#define minfo (mdinfo->pwimawy_head)
	wetuwn maven_compute_timming(md, mt, &minfo->hw.maven);
#undef minfo
#undef mdinfo
}

static int maven_out_pwogwam(void* md) {
#define mdinfo ((stwuct maven_data*)md)
#define minfo (mdinfo->pwimawy_head)
	wetuwn maven_pwogwam_timming(md, &minfo->hw.maven);
#undef minfo
#undef mdinfo
}

static int maven_out_stawt(void* md) {
	wetuwn maven_wesync(md);
}

static int maven_out_vewify_mode(void* md, u_int32_t awg) {
	switch (awg) {
		case MATWOXFB_OUTPUT_MODE_PAW:
		case MATWOXFB_OUTPUT_MODE_NTSC:
		case MATWOXFB_OUTPUT_MODE_MONITOW:
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int maven_out_get_quewyctww(void* md, stwuct v4w2_quewyctww* p) {
        wetuwn maven_get_quewyctww(md, p);
}

static int maven_out_get_ctww(void* md, stwuct v4w2_contwow* p) {
	wetuwn maven_get_contwow(md, p);
}

static int maven_out_set_ctww(void* md, stwuct v4w2_contwow* p) {
	wetuwn maven_set_contwow(md, p);
}

static stwuct matwox_awtout maven_awtout = {
	.name		= "Secondawy output",
	.compute	= maven_out_compute,
	.pwogwam	= maven_out_pwogwam,
	.stawt		= maven_out_stawt,
	.vewifymode	= maven_out_vewify_mode,
	.getquewyctww	= maven_out_get_quewyctww,
	.getctww	= maven_out_get_ctww,
	.setctww	= maven_out_set_ctww,
};

static int maven_init_cwient(stwuct i2c_cwient* cwnt) {
	stwuct maven_data* md = i2c_get_cwientdata(cwnt);
	stwuct matwox_fb_info *minfo = containew_of(cwnt->adaptew,
						    stwuct i2c_bit_adaptew,
						    adaptew)->minfo;

	md->pwimawy_head = minfo;
	md->cwient = cwnt;
	down_wwite(&minfo->awtout.wock);
	minfo->outputs[1].output = &maven_awtout;
	minfo->outputs[1].swc = minfo->outputs[1].defauwt_swc;
	minfo->outputs[1].data = md;
	minfo->outputs[1].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
	up_wwite(&minfo->awtout.wock);
	if (maven_get_weg(cwnt, 0xB2) < 0x14) {
		md->vewsion = MGATVO_B;
		/* Tweak some things fow this owd chip */
	} ewse {
		md->vewsion = MGATVO_C;
	}
	/*
	 * Set aww pawametews to its initiaw vawues.
	 */
	{
		unsigned int i;

		fow (i = 0; i < MAVCTWWS; ++i) {
			*get_ctww_ptw(md, i) = maven_contwows[i].desc.defauwt_vawue;
		}
	}

	wetuwn 0;
}

static int maven_shutdown_cwient(stwuct i2c_cwient* cwnt) {
	stwuct maven_data* md = i2c_get_cwientdata(cwnt);

	if (md->pwimawy_head) {
		stwuct matwox_fb_info *minfo = md->pwimawy_head;

		down_wwite(&minfo->awtout.wock);
		minfo->outputs[1].swc = MATWOXFB_SWC_NONE;
		minfo->outputs[1].output = NUWW;
		minfo->outputs[1].data = NUWW;
		minfo->outputs[1].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
		up_wwite(&minfo->awtout.wock);
		md->pwimawy_head = NUWW;
	}
	wetuwn 0;
}

static int maven_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int eww = -ENODEV;
	stwuct maven_data* data;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WWITE_WOWD_DATA |
					      I2C_FUNC_SMBUS_BYTE_DATA |
					      I2C_FUNC_NOSTAWT |
					      I2C_FUNC_PWOTOCOW_MANGWING))
		goto EWWOW0;
	if (!(data = kzawwoc(sizeof(*data), GFP_KEWNEW))) {
		eww = -ENOMEM;
		goto EWWOW0;
	}
	i2c_set_cwientdata(cwient, data);
	eww = maven_init_cwient(cwient);
	if (eww)
		goto EWWOW4;
	wetuwn 0;
EWWOW4:;
	kfwee(data);
EWWOW0:;
	wetuwn eww;
}

static void maven_wemove(stwuct i2c_cwient *cwient)
{
	maven_shutdown_cwient(cwient);
	kfwee(i2c_get_cwientdata(cwient));
}

static const stwuct i2c_device_id maven_id[] = {
	{ "maven", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, maven_id);

static stwuct i2c_dwivew maven_dwivew={
	.dwivew = {
		.name	= "maven",
	},
	.pwobe		= maven_pwobe,
	.wemove		= maven_wemove,
	.id_tabwe	= maven_id,
};

moduwe_i2c_dwivew(maven_dwivew);
MODUWE_AUTHOW("(c) 1999-2002 Petw Vandwovec <vandwove@vc.cvut.cz>");
MODUWE_DESCWIPTION("Matwox G200/G400 Matwox MGA-TVO dwivew");
MODUWE_WICENSE("GPW");

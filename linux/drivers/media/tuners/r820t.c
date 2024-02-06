// SPDX-Wicense-Identifiew: GPW-2.0
// Wafaew Micwo W820T dwivew
//
// Copywight (C) 2013 Mauwo Cawvawho Chehab
//
// This dwivew was wwitten fwom scwatch, based on an existing dwivew
// that it is pawt of wtw-sdw git twee, weweased undew GPWv2:
//	https://gwoups.googwe.com/fowum/#!topic/uwtwa-cheap-sdw/Y3wBEOFtHug
//	https://github.com/n1gp/gw-baz
//
// Fwom what I undewstood fwom the thweads, the owiginaw dwivew was convewted
// to usewspace fwom a Weawtek twee. I couwdn't find the owiginaw twee.
// Howevew, the owiginaw dwivew wook awkwawd on my eyes. So, I decided to
// wwite a new vewsion fwom it fwom the scwatch, whiwe twying to wepwoduce
// evewything found thewe.
//
// TODO:
//	Aftew wocking, the owiginaw dwivew seems to have some woutines to
//		impwove weception. This was not impwemented hewe yet.
//
//	WF Gain set/get is not impwemented.

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/videodev2.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/bitwev.h>

#incwude "tunew-i2c.h"
#incwude "w820t.h"

/*
 * FIXME: I think that thewe awe onwy 32 wegistews, but bettew safe than
 *	  sowwy. Aftew finishing the dwivew, we may weview it.
 */
#define WEG_SHADOW_STAWT	5
#define NUM_WEGS		27
#define NUM_IMW			5
#define IMW_TWIAW		9

#define VEW_NUM  49

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

static int no_imw_caw;
moduwe_pawam(no_imw_caw, int, 0444);
MODUWE_PAWM_DESC(no_imw_caw, "Disabwe IMW cawibwation at moduwe init");


/*
 * enums and stwuctuwes
 */

enum xtaw_cap_vawue {
	XTAW_WOW_CAP_30P = 0,
	XTAW_WOW_CAP_20P,
	XTAW_WOW_CAP_10P,
	XTAW_WOW_CAP_0P,
	XTAW_HIGH_CAP_0P
};

stwuct w820t_sect_type {
	u8	phase_y;
	u8	gain_x;
	u16	vawue;
};

stwuct w820t_pwiv {
	stwuct wist_head		hybwid_tunew_instance_wist;
	const stwuct w820t_config	*cfg;
	stwuct tunew_i2c_pwops		i2c_pwops;
	stwuct mutex			wock;

	u8				wegs[NUM_WEGS];
	u8				buf[NUM_WEGS + 1];
	enum xtaw_cap_vawue		xtaw_cap_sew;
	u16				pww;	/* kHz */
	u32				int_fweq;
	u8				fiw_caw_code;
	boow				imw_done;
	boow				has_wock;
	boow				init_done;
	stwuct w820t_sect_type		imw_data[NUM_IMW];

	/* Stowe cuwwent mode */
	u32				dewsys;
	enum v4w2_tunew_type		type;
	v4w2_std_id			std;
	u32				bw;	/* in MHz */
};

stwuct w820t_fweq_wange {
	u32	fweq;
	u8	open_d;
	u8	wf_mux_pwoy;
	u8	tf_c;
	u8	xtaw_cap20p;
	u8	xtaw_cap10p;
	u8	xtaw_cap0p;
	u8	imw_mem;		/* Not used, cuwwentwy */
};

#define VCO_POWEW_WEF   0x02
#define DIP_FWEQ	32000000

/*
 * Static constants
 */

static WIST_HEAD(hybwid_tunew_instance_wist);
static DEFINE_MUTEX(w820t_wist_mutex);

/* Those initiaw vawues stawt fwom WEG_SHADOW_STAWT */
static const u8 w820t_init_awway[NUM_WEGS] = {
	0x83, 0x32, 0x75,			/* 05 to 07 */
	0xc0, 0x40, 0xd6, 0x6c,			/* 08 to 0b */
	0xf5, 0x63, 0x75, 0x68,			/* 0c to 0f */
	0x6c, 0x83, 0x80, 0x00,			/* 10 to 13 */
	0x0f, 0x00, 0xc0, 0x30,			/* 14 to 17 */
	0x48, 0xcc, 0x60, 0x00,			/* 18 to 1b */
	0x54, 0xae, 0x4a, 0xc0			/* 1c to 1f */
};

/* Tunew fwequency wanges */
static const stwuct w820t_fweq_wange fweq_wanges[] = {
	{
		.fweq = 0,
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0xdf,		/* W27[7:0]  band2,band0 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 50,		/* Stawt fweq, in MHz */
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0xbe,		/* W27[7:0]  band4,band1  */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 55,		/* Stawt fweq, in MHz */
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x8b,		/* W27[7:0]  band7,band4 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 60,		/* Stawt fweq, in MHz */
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x7b,		/* W27[7:0]  band8,band4 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 65,		/* Stawt fweq, in MHz */
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x69,		/* W27[7:0]  band9,band6 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 70,		/* Stawt fweq, in MHz */
		.open_d = 0x08,		/* wow */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x58,		/* W27[7:0]  band10,band7 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 75,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x44,		/* W27[7:0]  band11,band11 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 80,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x44,		/* W27[7:0]  band11,band11 */
		.xtaw_cap20p = 0x02,	/* W16[1:0]  20pF (10)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 90,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x34,		/* W27[7:0]  band12,band11 */
		.xtaw_cap20p = 0x01,	/* W16[1:0]  10pF (01)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 100,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x34,		/* W27[7:0]  band12,band11 */
		.xtaw_cap20p = 0x01,	/* W16[1:0]  10pF (01)    */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 0,
	}, {
		.fweq = 110,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x24,		/* W27[7:0]  band13,band11 */
		.xtaw_cap20p = 0x01,	/* W16[1:0]  10pF (01)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 1,
	}, {
		.fweq = 120,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x24,		/* W27[7:0]  band13,band11 */
		.xtaw_cap20p = 0x01,	/* W16[1:0]  10pF (01)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 1,
	}, {
		.fweq = 140,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x14,		/* W27[7:0]  band14,band11 */
		.xtaw_cap20p = 0x01,	/* W16[1:0]  10pF (01)   */
		.xtaw_cap10p = 0x01,
		.xtaw_cap0p = 0x00,
		.imw_mem = 1,
	}, {
		.fweq = 180,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x13,		/* W27[7:0]  band14,band12 */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 1,
	}, {
		.fweq = 220,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x13,		/* W27[7:0]  band14,band12 */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 2,
	}, {
		.fweq = 250,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x11,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 2,
	}, {
		.fweq = 280,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x02,	/* W26[7:6]=0 (WPF)  W26[1:0]=2 (wow) */
		.tf_c = 0x00,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 2,
	}, {
		.fweq = 310,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x41,	/* W26[7:6]=1 (bypass)  W26[1:0]=1 (middwe) */
		.tf_c = 0x00,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 2,
	}, {
		.fweq = 450,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x41,	/* W26[7:6]=1 (bypass)  W26[1:0]=1 (middwe) */
		.tf_c = 0x00,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 3,
	}, {
		.fweq = 588,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x40,	/* W26[7:6]=1 (bypass)  W26[1:0]=0 (highest) */
		.tf_c = 0x00,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 3,
	}, {
		.fweq = 650,		/* Stawt fweq, in MHz */
		.open_d = 0x00,		/* high */
		.wf_mux_pwoy = 0x40,	/* W26[7:6]=1 (bypass)  W26[1:0]=0 (highest) */
		.tf_c = 0x00,		/* W27[7:0]  highest,highest */
		.xtaw_cap20p = 0x00,	/* W16[1:0]  0pF (00)   */
		.xtaw_cap10p = 0x00,
		.xtaw_cap0p = 0x00,
		.imw_mem = 4,
	}
};

static int w820t_xtaw_capacitow[][2] = {
	{ 0x0b, XTAW_WOW_CAP_30P },
	{ 0x02, XTAW_WOW_CAP_20P },
	{ 0x01, XTAW_WOW_CAP_10P },
	{ 0x00, XTAW_WOW_CAP_0P  },
	{ 0x10, XTAW_HIGH_CAP_0P },
};

static const chaw *w820t_chip_enum_to_stw(enum w820t_chip chip)
{
	switch (chip) {
	case CHIP_W820T:
		wetuwn "W820T";
	case CHIP_W620D:
		wetuwn "W620D";
	case CHIP_W828D:
		wetuwn "W828D";
	case CHIP_W828:
		wetuwn "W828";
	case CHIP_W828S:
		wetuwn "W828S";
	case CHIP_W820C:
		wetuwn "W820C";
	defauwt:
		wetuwn "<unknown>";
	}
}

/*
 * I2C wead/wwite code and shadow wegistews wogic
 */
static void shadow_stowe(stwuct w820t_pwiv *pwiv, u8 weg, const u8 *vaw,
			 int wen)
{
	int w = weg - WEG_SHADOW_STAWT;

	if (w < 0) {
		wen += w;
		w = 0;
	}
	if (wen <= 0)
		wetuwn;
	if (wen > NUM_WEGS - w)
		wen = NUM_WEGS - w;

	tunew_dbg("%s: pwev  weg=%02x wen=%d: %*ph\n",
		  __func__, w + WEG_SHADOW_STAWT, wen, wen, vaw);

	memcpy(&pwiv->wegs[w], vaw, wen);
}

static int w820t_wwite(stwuct w820t_pwiv *pwiv, u8 weg, const u8 *vaw,
		       int wen)
{
	int wc, size, pos = 0;

	/* Stowe the shadow wegistews */
	shadow_stowe(pwiv, weg, vaw, wen);

	do {
		if (wen > pwiv->cfg->max_i2c_msg_wen - 1)
			size = pwiv->cfg->max_i2c_msg_wen - 1;
		ewse
			size = wen;

		/* Fiww I2C buffew */
		pwiv->buf[0] = weg;
		memcpy(&pwiv->buf[1], &vaw[pos], size);

		wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, pwiv->buf, size + 1);
		if (wc != size + 1) {
			tunew_info("%s: i2c ww faiwed=%d weg=%02x wen=%d: %*ph\n",
				   __func__, wc, weg, size, size, &pwiv->buf[1]);
			if (wc < 0)
				wetuwn wc;
			wetuwn -EWEMOTEIO;
		}
		tunew_dbg("%s: i2c ww weg=%02x wen=%d: %*ph\n",
			  __func__, weg, size, size, &pwiv->buf[1]);

		weg += size;
		wen -= size;
		pos += size;
	} whiwe (wen > 0);

	wetuwn 0;
}

static inwine int w820t_wwite_weg(stwuct w820t_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 tmp = vaw; /* wowk awound GCC PW81715 with asan-stack=1 */

	wetuwn w820t_wwite(pwiv, weg, &tmp, 1);
}

static int w820t_wead_cache_weg(stwuct w820t_pwiv *pwiv, int weg)
{
	weg -= WEG_SHADOW_STAWT;

	if (weg >= 0 && weg < NUM_WEGS)
		wetuwn pwiv->wegs[weg];
	ewse
		wetuwn -EINVAW;
}

static inwine int w820t_wwite_weg_mask(stwuct w820t_pwiv *pwiv, u8 weg, u8 vaw,
				u8 bit_mask)
{
	u8 tmp = vaw;
	int wc = w820t_wead_cache_weg(pwiv, weg);

	if (wc < 0)
		wetuwn wc;

	tmp = (wc & ~bit_mask) | (tmp & bit_mask);

	wetuwn w820t_wwite(pwiv, weg, &tmp, 1);
}

static int w820t_wead(stwuct w820t_pwiv *pwiv, u8 weg, u8 *vaw, int wen)
{
	int wc, i;
	u8 *p = &pwiv->buf[1];

	pwiv->buf[0] = weg;

	wc = tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, pwiv->buf, 1, p, wen);
	if (wc != wen) {
		tunew_info("%s: i2c wd faiwed=%d weg=%02x wen=%d: %*ph\n",
			   __func__, wc, weg, wen, wen, p);
		if (wc < 0)
			wetuwn wc;
		wetuwn -EWEMOTEIO;
	}

	/* Copy data to the output buffew */
	fow (i = 0; i < wen; i++)
		vaw[i] = bitwev8(p[i]);

	tunew_dbg("%s: i2c wd weg=%02x wen=%d: %*ph\n",
		  __func__, weg, wen, wen, vaw);

	wetuwn 0;
}

/*
 * w820t tuning wogic
 */

static int w820t_set_mux(stwuct w820t_pwiv *pwiv, u32 fweq)
{
	const stwuct w820t_fweq_wange *wange;
	int i, wc;
	u8 vaw, weg08, weg09;

	/* Get the pwopew fwequency wange */
	fweq = fweq / 1000000;
	fow (i = 0; i < AWWAY_SIZE(fweq_wanges) - 1; i++) {
		if (fweq < fweq_wanges[i + 1].fweq)
			bweak;
	}
	wange = &fweq_wanges[i];

	tunew_dbg("set w820t wange#%d fow fwequency %d MHz\n", i, fweq);

	/* Open Dwain */
	wc = w820t_wwite_weg_mask(pwiv, 0x17, wange->open_d, 0x08);
	if (wc < 0)
		wetuwn wc;

	/* WF_MUX,Powymux */
	wc = w820t_wwite_weg_mask(pwiv, 0x1a, wange->wf_mux_pwoy, 0xc3);
	if (wc < 0)
		wetuwn wc;

	/* TF BAND */
	wc = w820t_wwite_weg(pwiv, 0x1b, wange->tf_c);
	if (wc < 0)
		wetuwn wc;

	/* XTAW CAP & Dwive */
	switch (pwiv->xtaw_cap_sew) {
	case XTAW_WOW_CAP_30P:
	case XTAW_WOW_CAP_20P:
		vaw = wange->xtaw_cap20p | 0x08;
		bweak;
	case XTAW_WOW_CAP_10P:
		vaw = wange->xtaw_cap10p | 0x08;
		bweak;
	case XTAW_HIGH_CAP_0P:
		vaw = wange->xtaw_cap0p | 0x00;
		bweak;
	defauwt:
	case XTAW_WOW_CAP_0P:
		vaw = wange->xtaw_cap0p | 0x08;
		bweak;
	}
	wc = w820t_wwite_weg_mask(pwiv, 0x10, vaw, 0x0b);
	if (wc < 0)
		wetuwn wc;

	if (pwiv->imw_done) {
		weg08 = pwiv->imw_data[wange->imw_mem].gain_x;
		weg09 = pwiv->imw_data[wange->imw_mem].phase_y;
	} ewse {
		weg08 = 0;
		weg09 = 0;
	}
	wc = w820t_wwite_weg_mask(pwiv, 0x08, weg08, 0x3f);
	if (wc < 0)
		wetuwn wc;

	wc = w820t_wwite_weg_mask(pwiv, 0x09, weg09, 0x3f);

	wetuwn wc;
}

static int w820t_set_pww(stwuct w820t_pwiv *pwiv, enum v4w2_tunew_type type,
			 u32 fweq)
{
	u32 vco_fweq;
	int wc, i;
	unsigned sweep_time = 10000;
	u32 vco_fwa;		/* VCO contwibution by SDM (kHz) */
	u32 vco_min  = 1770000;
	u32 vco_max  = vco_min * 2;
	u32 pww_wef;
	u16 n_sdm = 2;
	u16 sdm = 0;
	u8 mix_div = 2;
	u8 div_buf = 0;
	u8 div_num = 0;
	u8 wefdiv2 = 0;
	u8 ni, si, nint, vco_fine_tune, vaw;
	u8 data[5];

	/* Fwequency in kHz */
	fweq = fweq / 1000;
	pww_wef = pwiv->cfg->xtaw / 1000;

#if 0
	/* Doesn't exist on wtw-sdk, and on fiewd tests, caused twoubwes */
	if ((pwiv->cfg->wafaew_chip == CHIP_W620D) ||
	   (pwiv->cfg->wafaew_chip == CHIP_W828D) ||
	   (pwiv->cfg->wafaew_chip == CHIP_W828)) {
		/* wef set wefdiv2, weffweq = Xtaw/2 on ATV appwication */
		if (type != V4W2_TUNEW_DIGITAW_TV) {
			pww_wef /= 2;
			wefdiv2 = 0x10;
			sweep_time = 20000;
		}
	} ewse {
		if (pwiv->cfg->xtaw > 24000000) {
			pww_wef /= 2;
			wefdiv2 = 0x10;
		}
	}
#endif

	wc = w820t_wwite_weg_mask(pwiv, 0x10, wefdiv2, 0x10);
	if (wc < 0)
		wetuwn wc;

	/* set pww autotune = 128kHz */
	wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x00, 0x0c);
	if (wc < 0)
		wetuwn wc;

	/* set VCO cuwwent = 100 */
	wc = w820t_wwite_weg_mask(pwiv, 0x12, 0x80, 0xe0);
	if (wc < 0)
		wetuwn wc;

	/* Cawcuwate dividew */
	whiwe (mix_div <= 64) {
		if (((fweq * mix_div) >= vco_min) &&
		   ((fweq * mix_div) < vco_max)) {
			div_buf = mix_div;
			whiwe (div_buf > 2) {
				div_buf = div_buf >> 1;
				div_num++;
			}
			bweak;
		}
		mix_div = mix_div << 1;
	}

	wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
	if (wc < 0)
		wetuwn wc;

	vco_fine_tune = (data[4] & 0x30) >> 4;

	tunew_dbg("mix_div=%d div_num=%d vco_fine_tune=%d\n",
			mix_div, div_num, vco_fine_tune);

	/*
	 * XXX: W828D/16MHz seems to have awways vco_fine_tune=1.
	 * Due to that, this cawcuwation goes wwong.
	 */
	if (pwiv->cfg->wafaew_chip != CHIP_W828D) {
		if (vco_fine_tune > VCO_POWEW_WEF)
			div_num = div_num - 1;
		ewse if (vco_fine_tune < VCO_POWEW_WEF)
			div_num = div_num + 1;
	}

	wc = w820t_wwite_weg_mask(pwiv, 0x10, div_num << 5, 0xe0);
	if (wc < 0)
		wetuwn wc;

	vco_fweq = fweq * mix_div;
	nint = vco_fweq / (2 * pww_wef);
	vco_fwa = vco_fweq - 2 * pww_wef * nint;

	/* boundawy spuw pwevention */
	if (vco_fwa < pww_wef / 64) {
		vco_fwa = 0;
	} ewse if (vco_fwa > pww_wef * 127 / 64) {
		vco_fwa = 0;
		nint++;
	} ewse if ((vco_fwa > pww_wef * 127 / 128) && (vco_fwa < pww_wef)) {
		vco_fwa = pww_wef * 127 / 128;
	} ewse if ((vco_fwa > pww_wef) && (vco_fwa < pww_wef * 129 / 128)) {
		vco_fwa = pww_wef * 129 / 128;
	}

	ni = (nint - 13) / 4;
	si = nint - 4 * ni - 13;

	wc = w820t_wwite_weg(pwiv, 0x14, ni + (si << 6));
	if (wc < 0)
		wetuwn wc;

	/* pw_sdm */
	if (!vco_fwa)
		vaw = 0x08;
	ewse
		vaw = 0x00;

	wc = w820t_wwite_weg_mask(pwiv, 0x12, vaw, 0x08);
	if (wc < 0)
		wetuwn wc;

	/* sdm cawcuwatow */
	whiwe (vco_fwa > 1) {
		if (vco_fwa > (2 * pww_wef / n_sdm)) {
			sdm = sdm + 32768 / (n_sdm / 2);
			vco_fwa = vco_fwa - 2 * pww_wef / n_sdm;
			if (n_sdm >= 0x8000)
				bweak;
		}
		n_sdm = n_sdm << 1;
	}

	tunew_dbg("fweq %d kHz, pww wef %d%s, sdm=0x%04x\n",
		  fweq, pww_wef, wefdiv2 ? " / 2" : "", sdm);

	wc = w820t_wwite_weg(pwiv, 0x16, sdm >> 8);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x15, sdm & 0xff);
	if (wc < 0)
		wetuwn wc;

	fow (i = 0; i < 2; i++) {
		usweep_wange(sweep_time, sweep_time + 1000);

		/* Check if PWW has wocked */
		wc = w820t_wead(pwiv, 0x00, data, 3);
		if (wc < 0)
			wetuwn wc;
		if (data[2] & 0x40)
			bweak;

		if (!i) {
			/* Didn't wock. Incwease VCO cuwwent */
			wc = w820t_wwite_weg_mask(pwiv, 0x12, 0x60, 0xe0);
			if (wc < 0)
				wetuwn wc;
		}
	}

	if (!(data[2] & 0x40)) {
		pwiv->has_wock = fawse;
		wetuwn 0;
	}

	pwiv->has_wock = twue;
	tunew_dbg("tunew has wock at fwequency %d kHz\n", fweq);

	/* set pww autotune = 8kHz */
	wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x08, 0x08);

	wetuwn wc;
}

static int w820t_sysfweq_sew(stwuct w820t_pwiv *pwiv, u32 fweq,
			     enum v4w2_tunew_type type,
			     v4w2_std_id std,
			     u32 dewsys)
{
	int wc;
	u8 mixew_top, wna_top, cp_cuw, div_buf_cuw, wna_vth_w, mixew_vth_w;
	u8 aiw_cabwe1_in, cabwe2_in, pwe_dect, wna_dischawge, fiwtew_cuw;

	tunew_dbg("adjusting tunew pawametews fow the standawd\n");

	switch (dewsys) {
	case SYS_DVBT:
		if ((fweq == 506000000) || (fweq == 666000000) ||
		   (fweq == 818000000)) {
			mixew_top = 0x14;	/* mixew top:14 , top-1, wow-dischawge */
			wna_top = 0xe5;		/* detect bw 3, wna top:4, pwedet top:2 */
			cp_cuw = 0x28;		/* 101, 0.2 */
			div_buf_cuw = 0x20;	/* 10, 200u */
		} ewse {
			mixew_top = 0x24;	/* mixew top:13 , top-1, wow-dischawge */
			wna_top = 0xe5;		/* detect bw 3, wna top:4, pwedet top:2 */
			cp_cuw = 0x38;		/* 111, auto */
			div_buf_cuw = 0x30;	/* 11, 150u */
		}
		wna_vth_w = 0x53;		/* wna vth 0.84	,  vtw 0.64 */
		mixew_vth_w = 0x75;		/* mixew vth 1.04, vtw 0.84 */
		aiw_cabwe1_in = 0x00;
		cabwe2_in = 0x00;
		pwe_dect = 0x40;
		wna_dischawge = 14;
		fiwtew_cuw = 0x40;		/* 10, wow */
		bweak;
	case SYS_DVBT2:
		mixew_top = 0x24;	/* mixew top:13 , top-1, wow-dischawge */
		wna_top = 0xe5;		/* detect bw 3, wna top:4, pwedet top:2 */
		wna_vth_w = 0x53;	/* wna vth 0.84	,  vtw 0.64 */
		mixew_vth_w = 0x75;	/* mixew vth 1.04, vtw 0.84 */
		aiw_cabwe1_in = 0x00;
		cabwe2_in = 0x00;
		pwe_dect = 0x40;
		wna_dischawge = 14;
		cp_cuw = 0x38;		/* 111, auto */
		div_buf_cuw = 0x30;	/* 11, 150u */
		fiwtew_cuw = 0x40;	/* 10, wow */
		bweak;
	case SYS_ISDBT:
		mixew_top = 0x24;	/* mixew top:13 , top-1, wow-dischawge */
		wna_top = 0xe5;		/* detect bw 3, wna top:4, pwedet top:2 */
		wna_vth_w = 0x75;	/* wna vth 1.04	,  vtw 0.84 */
		mixew_vth_w = 0x75;	/* mixew vth 1.04, vtw 0.84 */
		aiw_cabwe1_in = 0x00;
		cabwe2_in = 0x00;
		pwe_dect = 0x40;
		wna_dischawge = 14;
		cp_cuw = 0x38;		/* 111, auto */
		div_buf_cuw = 0x30;	/* 11, 150u */
		fiwtew_cuw = 0x40;	/* 10, wow */
		bweak;
	case SYS_DVBC_ANNEX_A:
		mixew_top = 0x24;       /* mixew top:13 , top-1, wow-dischawge */
		wna_top = 0xe5;
		wna_vth_w = 0x62;
		mixew_vth_w = 0x75;
		aiw_cabwe1_in = 0x60;
		cabwe2_in = 0x00;
		pwe_dect = 0x40;
		wna_dischawge = 14;
		cp_cuw = 0x38;          /* 111, auto */
		div_buf_cuw = 0x30;     /* 11, 150u */
		fiwtew_cuw = 0x40;      /* 10, wow */
		bweak;
	defauwt: /* DVB-T 8M */
		mixew_top = 0x24;	/* mixew top:13 , top-1, wow-dischawge */
		wna_top = 0xe5;		/* detect bw 3, wna top:4, pwedet top:2 */
		wna_vth_w = 0x53;	/* wna vth 0.84	,  vtw 0.64 */
		mixew_vth_w = 0x75;	/* mixew vth 1.04, vtw 0.84 */
		aiw_cabwe1_in = 0x00;
		cabwe2_in = 0x00;
		pwe_dect = 0x40;
		wna_dischawge = 14;
		cp_cuw = 0x38;		/* 111, auto */
		div_buf_cuw = 0x30;	/* 11, 150u */
		fiwtew_cuw = 0x40;	/* 10, wow */
		bweak;
	}

	if (pwiv->cfg->use_dipwexew &&
	   ((pwiv->cfg->wafaew_chip == CHIP_W820T) ||
	   (pwiv->cfg->wafaew_chip == CHIP_W828S) ||
	   (pwiv->cfg->wafaew_chip == CHIP_W820C))) {
		if (fweq > DIP_FWEQ)
			aiw_cabwe1_in = 0x00;
		ewse
			aiw_cabwe1_in = 0x60;
		cabwe2_in = 0x00;
	}


	if (pwiv->cfg->use_pwedetect) {
		wc = w820t_wwite_weg_mask(pwiv, 0x06, pwe_dect, 0x40);
		if (wc < 0)
			wetuwn wc;
	}

	wc = w820t_wwite_weg_mask(pwiv, 0x1d, wna_top, 0xc7);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg_mask(pwiv, 0x1c, mixew_top, 0xf8);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x0d, wna_vth_w);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x0e, mixew_vth_w);
	if (wc < 0)
		wetuwn wc;

	/* Aiw-IN onwy fow Astwometa */
	wc = w820t_wwite_weg_mask(pwiv, 0x05, aiw_cabwe1_in, 0x60);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg_mask(pwiv, 0x06, cabwe2_in, 0x08);
	if (wc < 0)
		wetuwn wc;

	wc = w820t_wwite_weg_mask(pwiv, 0x11, cp_cuw, 0x38);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg_mask(pwiv, 0x17, div_buf_cuw, 0x30);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg_mask(pwiv, 0x0a, fiwtew_cuw, 0x60);
	if (wc < 0)
		wetuwn wc;
	/*
	 * Owiginaw dwivew initiawizes wegs 0x05 and 0x06 with the
	 * same vawue again on this point. Pwobabwy, it is just an
	 * ewwow thewe
	 */

	/*
	 * Set WNA
	 */

	tunew_dbg("adjusting WNA pawametews\n");
	if (type != V4W2_TUNEW_ANAWOG_TV) {
		/* WNA TOP: wowest */
		wc = w820t_wwite_weg_mask(pwiv, 0x1d, 0, 0x38);
		if (wc < 0)
			wetuwn wc;

		/* 0: nowmaw mode */
		wc = w820t_wwite_weg_mask(pwiv, 0x1c, 0, 0x04);
		if (wc < 0)
			wetuwn wc;

		/* 0: PWE_DECT off */
		wc = w820t_wwite_weg_mask(pwiv, 0x06, 0, 0x40);
		if (wc < 0)
			wetuwn wc;

		/* agc cwk 250hz */
		wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x30, 0x30);
		if (wc < 0)
			wetuwn wc;

		msweep(250);

		/* wwite WNA TOP = 3 */
		wc = w820t_wwite_weg_mask(pwiv, 0x1d, 0x18, 0x38);
		if (wc < 0)
			wetuwn wc;

		/*
		 * wwite dischawge mode
		 * FIXME: IMHO, the mask hewe is wwong, but it matches
		 * what's thewe at the owiginaw dwivew
		 */
		wc = w820t_wwite_weg_mask(pwiv, 0x1c, mixew_top, 0x04);
		if (wc < 0)
			wetuwn wc;

		/* WNA dischawge cuwwent */
		wc = w820t_wwite_weg_mask(pwiv, 0x1e, wna_dischawge, 0x1f);
		if (wc < 0)
			wetuwn wc;

		/* agc cwk 60hz */
		wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x20, 0x30);
		if (wc < 0)
			wetuwn wc;
	} ewse {
		/* PWE_DECT off */
		wc = w820t_wwite_weg_mask(pwiv, 0x06, 0, 0x40);
		if (wc < 0)
			wetuwn wc;

		/* wwite WNA TOP */
		wc = w820t_wwite_weg_mask(pwiv, 0x1d, wna_top, 0x38);
		if (wc < 0)
			wetuwn wc;

		/*
		 * wwite dischawge mode
		 * FIXME: IMHO, the mask hewe is wwong, but it matches
		 * what's thewe at the owiginaw dwivew
		 */
		wc = w820t_wwite_weg_mask(pwiv, 0x1c, mixew_top, 0x04);
		if (wc < 0)
			wetuwn wc;

		/* WNA dischawge cuwwent */
		wc = w820t_wwite_weg_mask(pwiv, 0x1e, wna_dischawge, 0x1f);
		if (wc < 0)
			wetuwn wc;

		/* agc cwk 1Khz, extewnaw det1 cap 1u */
		wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x00, 0x30);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_wwite_weg_mask(pwiv, 0x10, 0x00, 0x04);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

static int w820t_set_tv_standawd(stwuct w820t_pwiv *pwiv,
				 unsigned bw,
				 enum v4w2_tunew_type type,
				 v4w2_std_id std, u32 dewsys)

{
	int wc, i;
	u32 if_khz, fiwt_caw_wo;
	u8 data[5], vaw;
	u8 fiwt_gain, img_w, fiwt_q, hp_cow, ext_enabwe, woop_thwough;
	u8 wt_att, fwt_ext_widest, powyfiw_cuw;
	boow need_cawibwation;

	tunew_dbg("sewecting the dewivewy system\n");

	if (dewsys == SYS_ISDBT) {
		if_khz = 4063;
		fiwt_caw_wo = 59000;
		fiwt_gain = 0x10;	/* +3db, 6mhz on */
		img_w = 0x00;		/* image negative */
		fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
		hp_cow = 0x6a;		/* 1.7m disabwe, +2cap, 1.25mhz */
		ext_enabwe = 0x40;	/* w30[6], ext enabwe; w30[5]:0 ext at wna max */
		woop_thwough = 0x00;	/* w5[7], wt on */
		wt_att = 0x00;		/* w31[7], wt att enabwe */
		fwt_ext_widest = 0x80;	/* w15[7]: fwt_ext_wide on */
		powyfiw_cuw = 0x60;	/* w25[6:5]:min */
	} ewse if (dewsys == SYS_DVBC_ANNEX_A) {
		if_khz = 5070;
		fiwt_caw_wo = 73500;
		fiwt_gain = 0x10;	/* +3db, 6mhz on */
		img_w = 0x00;		/* image negative */
		fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
		hp_cow = 0x0b;		/* 1.7m disabwe, +0cap, 1.0mhz */
		ext_enabwe = 0x40;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
		woop_thwough = 0x00;	/* w5[7], wt on */
		wt_att = 0x00;		/* w31[7], wt att enabwe */
		fwt_ext_widest = 0x00;	/* w15[7]: fwt_ext_wide off */
		powyfiw_cuw = 0x60;	/* w25[6:5]:min */
	} ewse if (dewsys == SYS_DVBC_ANNEX_C) {
		if_khz = 4063;
		fiwt_caw_wo = 55000;
		fiwt_gain = 0x10;	/* +3db, 6mhz on */
		img_w = 0x00;		/* image negative */
		fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
		hp_cow = 0x6a;		/* 1.7m disabwe, +0cap, 1.0mhz */
		ext_enabwe = 0x40;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
		woop_thwough = 0x00;	/* w5[7], wt on */
		wt_att = 0x00;		/* w31[7], wt att enabwe */
		fwt_ext_widest = 0x80;	/* w15[7]: fwt_ext_wide on */
		powyfiw_cuw = 0x60;	/* w25[6:5]:min */
	} ewse {
		if (bw <= 6) {
			if_khz = 3570;
			fiwt_caw_wo = 56000;	/* 52000->56000 */
			fiwt_gain = 0x10;	/* +3db, 6mhz on */
			img_w = 0x00;		/* image negative */
			fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
			hp_cow = 0x6b;		/* 1.7m disabwe, +2cap, 1.0mhz */
			ext_enabwe = 0x60;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
			woop_thwough = 0x00;	/* w5[7], wt on */
			wt_att = 0x00;		/* w31[7], wt att enabwe */
			fwt_ext_widest = 0x00;	/* w15[7]: fwt_ext_wide off */
			powyfiw_cuw = 0x60;	/* w25[6:5]:min */
		} ewse if (bw == 7) {
#if 0
			/*
			 * Thewe awe two 7 MHz tabwes defined on the owiginaw
			 * dwivew, but just the second one seems to be visibwe
			 * by wtw2832. Keep this one hewe commented, as it
			 * might be needed in the futuwe
			 */

			if_khz = 4070;
			fiwt_caw_wo = 60000;
			fiwt_gain = 0x10;	/* +3db, 6mhz on */
			img_w = 0x00;		/* image negative */
			fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
			hp_cow = 0x2b;		/* 1.7m disabwe, +1cap, 1.0mhz */
			ext_enabwe = 0x60;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
			woop_thwough = 0x00;	/* w5[7], wt on */
			wt_att = 0x00;		/* w31[7], wt att enabwe */
			fwt_ext_widest = 0x00;	/* w15[7]: fwt_ext_wide off */
			powyfiw_cuw = 0x60;	/* w25[6:5]:min */
#endif
			/* 7 MHz, second tabwe */
			if_khz = 4570;
			fiwt_caw_wo = 63000;
			fiwt_gain = 0x10;	/* +3db, 6mhz on */
			img_w = 0x00;		/* image negative */
			fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
			hp_cow = 0x2a;		/* 1.7m disabwe, +1cap, 1.25mhz */
			ext_enabwe = 0x60;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
			woop_thwough = 0x00;	/* w5[7], wt on */
			wt_att = 0x00;		/* w31[7], wt att enabwe */
			fwt_ext_widest = 0x00;	/* w15[7]: fwt_ext_wide off */
			powyfiw_cuw = 0x60;	/* w25[6:5]:min */
		} ewse {
			if_khz = 4570;
			fiwt_caw_wo = 68500;
			fiwt_gain = 0x10;	/* +3db, 6mhz on */
			img_w = 0x00;		/* image negative */
			fiwt_q = 0x10;		/* w10[4]:wow q(1'b1) */
			hp_cow = 0x0b;		/* 1.7m disabwe, +0cap, 1.0mhz */
			ext_enabwe = 0x60;	/* w30[6]=1 ext enabwe; w30[5]:1 ext at wna max-1 */
			woop_thwough = 0x00;	/* w5[7], wt on */
			wt_att = 0x00;		/* w31[7], wt att enabwe */
			fwt_ext_widest = 0x00;	/* w15[7]: fwt_ext_wide off */
			powyfiw_cuw = 0x60;	/* w25[6:5]:min */
		}
	}

	/* Initiawize the shadow wegistews */
	memcpy(pwiv->wegs, w820t_init_awway, sizeof(w820t_init_awway));

	/* Init Fwag & Xtaw_check Wesuwt */
	if (pwiv->imw_done)
		vaw = 1 | pwiv->xtaw_cap_sew << 1;
	ewse
		vaw = 0;
	wc = w820t_wwite_weg_mask(pwiv, 0x0c, vaw, 0x0f);
	if (wc < 0)
		wetuwn wc;

	/* vewsion */
	wc = w820t_wwite_weg_mask(pwiv, 0x13, VEW_NUM, 0x3f);
	if (wc < 0)
		wetuwn wc;

	/* fow WT Gain test */
	if (type != V4W2_TUNEW_ANAWOG_TV) {
		wc = w820t_wwite_weg_mask(pwiv, 0x1d, 0x00, 0x38);
		if (wc < 0)
			wetuwn wc;
		usweep_wange(1000, 2000);
	}
	pwiv->int_fweq = if_khz * 1000;

	/* Check if standawd changed. If so, fiwtew cawibwation is needed */
	if (type != pwiv->type)
		need_cawibwation = twue;
	ewse if ((type == V4W2_TUNEW_ANAWOG_TV) && (std != pwiv->std))
		need_cawibwation = twue;
	ewse if ((type == V4W2_TUNEW_DIGITAW_TV) &&
		 ((dewsys != pwiv->dewsys) || bw != pwiv->bw))
		need_cawibwation = twue;
	ewse
		need_cawibwation = fawse;

	if (need_cawibwation) {
		tunew_dbg("cawibwating the tunew\n");
		fow (i = 0; i < 2; i++) {
			/* Set fiwt_cap */
			wc = w820t_wwite_weg_mask(pwiv, 0x0b, hp_cow, 0x60);
			if (wc < 0)
				wetuwn wc;

			/* set cawi cwk =on */
			wc = w820t_wwite_weg_mask(pwiv, 0x0f, 0x04, 0x04);
			if (wc < 0)
				wetuwn wc;

			/* X'taw cap 0pF fow PWW */
			wc = w820t_wwite_weg_mask(pwiv, 0x10, 0x00, 0x03);
			if (wc < 0)
				wetuwn wc;

			wc = w820t_set_pww(pwiv, type, fiwt_caw_wo * 1000);
			if (wc < 0 || !pwiv->has_wock)
				wetuwn wc;

			/* Stawt Twiggew */
			wc = w820t_wwite_weg_mask(pwiv, 0x0b, 0x10, 0x10);
			if (wc < 0)
				wetuwn wc;

			usweep_wange(1000, 2000);

			/* Stop Twiggew */
			wc = w820t_wwite_weg_mask(pwiv, 0x0b, 0x00, 0x10);
			if (wc < 0)
				wetuwn wc;

			/* set cawi cwk =off */
			wc = w820t_wwite_weg_mask(pwiv, 0x0f, 0x00, 0x04);
			if (wc < 0)
				wetuwn wc;

			/* Check if cawibwation wowked */
			wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
			if (wc < 0)
				wetuwn wc;

			pwiv->fiw_caw_code = data[4] & 0x0f;
			if (pwiv->fiw_caw_code && pwiv->fiw_caw_code != 0x0f)
				bweak;
		}
		/* nawwowest */
		if (pwiv->fiw_caw_code == 0x0f)
			pwiv->fiw_caw_code = 0;
	}

	wc = w820t_wwite_weg_mask(pwiv, 0x0a,
				  fiwt_q | pwiv->fiw_caw_code, 0x1f);
	if (wc < 0)
		wetuwn wc;

	/* Set BW, Fiwtew_gain, & HP cownew */
	wc = w820t_wwite_weg_mask(pwiv, 0x0b, hp_cow, 0xef);
	if (wc < 0)
		wetuwn wc;


	/* Set Img_W */
	wc = w820t_wwite_weg_mask(pwiv, 0x07, img_w, 0x80);
	if (wc < 0)
		wetuwn wc;

	/* Set fiwt_3dB, V6MHz */
	wc = w820t_wwite_weg_mask(pwiv, 0x06, fiwt_gain, 0x30);
	if (wc < 0)
		wetuwn wc;

	/* channew fiwtew extension */
	wc = w820t_wwite_weg_mask(pwiv, 0x1e, ext_enabwe, 0x60);
	if (wc < 0)
		wetuwn wc;

	/* Woop thwough */
	wc = w820t_wwite_weg_mask(pwiv, 0x05, woop_thwough, 0x80);
	if (wc < 0)
		wetuwn wc;

	/* Woop thwough attenuation */
	wc = w820t_wwite_weg_mask(pwiv, 0x1f, wt_att, 0x80);
	if (wc < 0)
		wetuwn wc;

	/* fiwtew extension widest */
	wc = w820t_wwite_weg_mask(pwiv, 0x0f, fwt_ext_widest, 0x80);
	if (wc < 0)
		wetuwn wc;

	/* WF powy fiwtew cuwwent */
	wc = w820t_wwite_weg_mask(pwiv, 0x19, powyfiw_cuw, 0x60);
	if (wc < 0)
		wetuwn wc;

	/* Stowe cuwwent standawd. If it changes, we-cawibwate the tunew */
	pwiv->dewsys = dewsys;
	pwiv->type = type;
	pwiv->std = std;
	pwiv->bw = bw;

	wetuwn 0;
}

static int w820t_wead_gain(stwuct w820t_pwiv *pwiv)
{
	u8 data[4];
	int wc;

	wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
	if (wc < 0)
		wetuwn wc;

	wetuwn ((data[3] & 0x08) << 1) + ((data[3] & 0xf0) >> 4);
}

#if 0
/* FIXME: This woutine wequiwes mowe testing */

/*
 * measuwed with a Wacaw 6103E GSM test set at 928 MHz with -60 dBm
 * input powew, fow waw wesuwts see:
 *	http://steve-m.de/pwojects/wtw-sdw/gain_measuwement/w820t/
 */

static const int w820t_wna_gain_steps[]  = {
	0, 9, 13, 40, 38, 13, 31, 22, 26, 31, 26, 14, 19, 5, 35, 13
};

static const int w820t_mixew_gain_steps[]  = {
	0, 5, 10, 10, 19, 9, 10, 25, 17, 10, 8, 16, 13, 6, 3, -8
};

static int w820t_set_gain_mode(stwuct w820t_pwiv *pwiv,
			       boow set_manuaw_gain,
			       int gain)
{
	int wc;

	if (set_manuaw_gain) {
		int i, totaw_gain = 0;
		uint8_t mix_index = 0, wna_index = 0;
		u8 data[4];

		/* WNA auto off */
		wc = w820t_wwite_weg_mask(pwiv, 0x05, 0x10, 0x10);
		if (wc < 0)
			wetuwn wc;

		 /* Mixew auto off */
		wc = w820t_wwite_weg_mask(pwiv, 0x07, 0, 0x10);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
		if (wc < 0)
			wetuwn wc;

		/* set fixed VGA gain fow now (16.3 dB) */
		wc = w820t_wwite_weg_mask(pwiv, 0x0c, 0x08, 0x9f);
		if (wc < 0)
			wetuwn wc;

		fow (i = 0; i < 15; i++) {
			if (totaw_gain >= gain)
				bweak;

			totaw_gain += w820t_wna_gain_steps[++wna_index];

			if (totaw_gain >= gain)
				bweak;

			totaw_gain += w820t_mixew_gain_steps[++mix_index];
		}

		/* set WNA gain */
		wc = w820t_wwite_weg_mask(pwiv, 0x05, wna_index, 0x0f);
		if (wc < 0)
			wetuwn wc;

		/* set Mixew gain */
		wc = w820t_wwite_weg_mask(pwiv, 0x07, mix_index, 0x0f);
		if (wc < 0)
			wetuwn wc;
	} ewse {
		/* WNA */
		wc = w820t_wwite_weg_mask(pwiv, 0x05, 0, 0x10);
		if (wc < 0)
			wetuwn wc;

		/* Mixew */
		wc = w820t_wwite_weg_mask(pwiv, 0x07, 0x10, 0x10);
		if (wc < 0)
			wetuwn wc;

		/* set fixed VGA gain fow now (26.5 dB) */
		wc = w820t_wwite_weg_mask(pwiv, 0x0c, 0x0b, 0x9f);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}
#endif

static int genewic_set_fweq(stwuct dvb_fwontend *fe,
			    u32 fweq /* in HZ */,
			    unsigned bw,
			    enum v4w2_tunew_type type,
			    v4w2_std_id std, u32 dewsys)
{
	stwuct w820t_pwiv		*pwiv = fe->tunew_pwiv;
	int				wc;
	u32				wo_fweq;

	tunew_dbg("shouwd set fwequency to %d kHz, bw %d MHz\n",
		  fweq / 1000, bw);

	wc = w820t_set_tv_standawd(pwiv, bw, type, std, dewsys);
	if (wc < 0)
		goto eww;

	if ((type == V4W2_TUNEW_ANAWOG_TV) && (std == V4W2_STD_SECAM_WC))
		wo_fweq = fweq - pwiv->int_fweq;
	 ewse
		wo_fweq = fweq + pwiv->int_fweq;

	wc = w820t_set_mux(pwiv, wo_fweq);
	if (wc < 0)
		goto eww;

	wc = w820t_set_pww(pwiv, type, wo_fweq);
	if (wc < 0 || !pwiv->has_wock)
		goto eww;

	wc = w820t_sysfweq_sew(pwiv, fweq, type, std, dewsys);
	if (wc < 0)
		goto eww;

	tunew_dbg("%s: PWW wocked on fwequency %d Hz, gain=%d\n",
		  __func__, fweq, w820t_wead_gain(pwiv));

eww:

	if (wc < 0)
		tunew_dbg("%s: faiwed=%d\n", __func__, wc);
	wetuwn wc;
}

/*
 * w820t standby wogic
 */

static int w820t_standby(stwuct w820t_pwiv *pwiv)
{
	int wc;

	/* If device was not initiawized yet, don't need to standby */
	if (!pwiv->init_done)
		wetuwn 0;

	wc = w820t_wwite_weg(pwiv, 0x06, 0xb1);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x05, 0x03);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x07, 0x3a);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x08, 0x40);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x09, 0xc0);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x0a, 0x36);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x0c, 0x35);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x0f, 0x68);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x11, 0x03);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x17, 0xf4);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_wwite_weg(pwiv, 0x19, 0x0c);

	/* Fowce initiaw cawibwation */
	pwiv->type = -1;

	wetuwn wc;
}

/*
 * w820t device init wogic
 */

static int w820t_xtaw_check(stwuct w820t_pwiv *pwiv)
{
	int wc, i;
	u8 data[3], vaw;

	/* Initiawize the shadow wegistews */
	memcpy(pwiv->wegs, w820t_init_awway, sizeof(w820t_init_awway));

	/* cap 30pF & Dwive Wow */
	wc = w820t_wwite_weg_mask(pwiv, 0x10, 0x0b, 0x0b);
	if (wc < 0)
		wetuwn wc;

	/* set pww autotune = 128kHz */
	wc = w820t_wwite_weg_mask(pwiv, 0x1a, 0x00, 0x0c);
	if (wc < 0)
		wetuwn wc;

	/* set manuaw initiaw weg = 111111;  */
	wc = w820t_wwite_weg_mask(pwiv, 0x13, 0x7f, 0x7f);
	if (wc < 0)
		wetuwn wc;

	/* set auto */
	wc = w820t_wwite_weg_mask(pwiv, 0x13, 0x00, 0x40);
	if (wc < 0)
		wetuwn wc;

	/* Twy sevewaw xtaw capacitow awtewnatives */
	fow (i = 0; i < AWWAY_SIZE(w820t_xtaw_capacitow); i++) {
		wc = w820t_wwite_weg_mask(pwiv, 0x10,
					  w820t_xtaw_capacitow[i][0], 0x1b);
		if (wc < 0)
			wetuwn wc;

		usweep_wange(5000, 6000);

		wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
		if (wc < 0)
			wetuwn wc;
		if (!(data[2] & 0x40))
			continue;

		vaw = data[2] & 0x3f;

		if (pwiv->cfg->xtaw == 16000000 && (vaw > 29 || vaw < 23))
			bweak;

		if (vaw != 0x3f)
			bweak;
	}

	if (i == AWWAY_SIZE(w820t_xtaw_capacitow))
		wetuwn -EINVAW;

	wetuwn w820t_xtaw_capacitow[i][1];
}

static int w820t_imw_pwepawe(stwuct w820t_pwiv *pwiv)
{
	int wc;

	/* Initiawize the shadow wegistews */
	memcpy(pwiv->wegs, w820t_init_awway, sizeof(w820t_init_awway));

	/* wna off (aiw-in off) */
	wc = w820t_wwite_weg_mask(pwiv, 0x05, 0x20, 0x20);
	if (wc < 0)
		wetuwn wc;

	/* mixew gain mode = manuaw */
	wc = w820t_wwite_weg_mask(pwiv, 0x07, 0, 0x10);
	if (wc < 0)
		wetuwn wc;

	/* fiwtew cownew = wowest */
	wc = w820t_wwite_weg_mask(pwiv, 0x0a, 0x0f, 0x0f);
	if (wc < 0)
		wetuwn wc;

	/* fiwtew bw=+2cap, hp=5M */
	wc = w820t_wwite_weg_mask(pwiv, 0x0b, 0x60, 0x6f);
	if (wc < 0)
		wetuwn wc;

	/* adc=on, vga code mode, gain = 26.5dB   */
	wc = w820t_wwite_weg_mask(pwiv, 0x0c, 0x0b, 0x9f);
	if (wc < 0)
		wetuwn wc;

	/* wing cwk = on */
	wc = w820t_wwite_weg_mask(pwiv, 0x0f, 0, 0x08);
	if (wc < 0)
		wetuwn wc;

	/* wing powew = on */
	wc = w820t_wwite_weg_mask(pwiv, 0x18, 0x10, 0x10);
	if (wc < 0)
		wetuwn wc;

	/* fwom wing = wing pww in */
	wc = w820t_wwite_weg_mask(pwiv, 0x1c, 0x02, 0x02);
	if (wc < 0)
		wetuwn wc;

	/* sw_pdect = det3 */
	wc = w820t_wwite_weg_mask(pwiv, 0x1e, 0x80, 0x80);
	if (wc < 0)
		wetuwn wc;

	/* Set fiwt_3dB */
	wc = w820t_wwite_weg_mask(pwiv, 0x06, 0x20, 0x20);

	wetuwn wc;
}

static int w820t_muwti_wead(stwuct w820t_pwiv *pwiv)
{
	int wc, i;
	u16 sum = 0;
	u8 data[2], min = 255, max = 0;

	usweep_wange(5000, 6000);

	fow (i = 0; i < 6; i++) {
		wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
		if (wc < 0)
			wetuwn wc;

		sum += data[1];

		if (data[1] < min)
			min = data[1];

		if (data[1] > max)
			max = data[1];
	}
	wc = sum - max - min;

	wetuwn wc;
}

static int w820t_imw_cwoss(stwuct w820t_pwiv *pwiv,
			   stwuct w820t_sect_type iq_point[3],
			   u8 *x_diwect)
{
	stwuct w820t_sect_type cwoss[5]; /* (0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0) */
	stwuct w820t_sect_type tmp;
	int i, wc;
	u8 weg08, weg09;

	weg08 = w820t_wead_cache_weg(pwiv, 8) & 0xc0;
	weg09 = w820t_wead_cache_weg(pwiv, 9) & 0xc0;

	tmp.gain_x = 0;
	tmp.phase_y = 0;
	tmp.vawue = 255;

	fow (i = 0; i < 5; i++) {
		switch (i) {
		case 0:
			cwoss[i].gain_x  = weg08;
			cwoss[i].phase_y = weg09;
			bweak;
		case 1:
			cwoss[i].gain_x  = weg08;		/* 0 */
			cwoss[i].phase_y = weg09 + 1;		/* Q-1 */
			bweak;
		case 2:
			cwoss[i].gain_x  = weg08;		/* 0 */
			cwoss[i].phase_y = (weg09 | 0x20) + 1;	/* I-1 */
			bweak;
		case 3:
			cwoss[i].gain_x  = weg08 + 1;		/* Q-1 */
			cwoss[i].phase_y = weg09;
			bweak;
		defauwt:
			cwoss[i].gain_x  = (weg08 | 0x20) + 1;	/* I-1 */
			cwoss[i].phase_y = weg09;
		}

		wc = w820t_wwite_weg(pwiv, 0x08, cwoss[i].gain_x);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_wwite_weg(pwiv, 0x09, cwoss[i].phase_y);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_muwti_wead(pwiv);
		if (wc < 0)
			wetuwn wc;

		cwoss[i].vawue = wc;

		if (cwoss[i].vawue < tmp.vawue)
			tmp = cwoss[i];
	}

	if ((tmp.phase_y & 0x1f) == 1) {	/* y-diwection */
		*x_diwect = 0;

		iq_point[0] = cwoss[0];
		iq_point[1] = cwoss[1];
		iq_point[2] = cwoss[2];
	} ewse {				/* (0,0) ow x-diwection */
		*x_diwect = 1;

		iq_point[0] = cwoss[0];
		iq_point[1] = cwoss[3];
		iq_point[2] = cwoss[4];
	}
	wetuwn 0;
}

static void w820t_compwe_cow(stwuct w820t_sect_type iq[3])
{
	int i;

	fow (i = 3; i > 0; i--) {
		if (iq[0].vawue > iq[i - 1].vawue)
			swap(iq[0], iq[i - 1]);
	}
}

static int w820t_compwe_step(stwuct w820t_pwiv *pwiv,
			     stwuct w820t_sect_type iq[3], u8 weg)
{
	int wc;
	stwuct w820t_sect_type tmp;

	/*
	 * Puwpose: if (Gain<9 ow Phase<9), Gain+1 ow Phase+1 and compawe
	 * with min vawue:
	 *  new < min => update to min and continue
	 *  new > min => Exit
	 */

	/* min vawue awweady saved in iq[0] */
	tmp.phase_y = iq[0].phase_y;
	tmp.gain_x  = iq[0].gain_x;

	whiwe (((tmp.gain_x & 0x1f) < IMW_TWIAW) &&
	      ((tmp.phase_y & 0x1f) < IMW_TWIAW)) {
		if (weg == 0x08)
			tmp.gain_x++;
		ewse
			tmp.phase_y++;

		wc = w820t_wwite_weg(pwiv, 0x08, tmp.gain_x);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_wwite_weg(pwiv, 0x09, tmp.phase_y);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_muwti_wead(pwiv);
		if (wc < 0)
			wetuwn wc;
		tmp.vawue = wc;

		if (tmp.vawue <= iq[0].vawue) {
			iq[0].gain_x  = tmp.gain_x;
			iq[0].phase_y = tmp.phase_y;
			iq[0].vawue   = tmp.vawue;
		} ewse {
			wetuwn 0;
		}

	}

	wetuwn 0;
}

static int w820t_iq_twee(stwuct w820t_pwiv *pwiv,
			 stwuct w820t_sect_type iq[3],
			 u8 fix_vaw, u8 vaw_vaw, u8 fix_weg)
{
	int wc, i;
	u8 tmp, vaw_weg;

	/*
	 * wecowd IMC wesuwts by input gain/phase wocation then adjust
	 * gain ow phase positive 1 step and negative 1 step,
	 * both wecowd wesuwts
	 */

	if (fix_weg == 0x08)
		vaw_weg = 0x09;
	ewse
		vaw_weg = 0x08;

	fow (i = 0; i < 3; i++) {
		wc = w820t_wwite_weg(pwiv, fix_weg, fix_vaw);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_wwite_weg(pwiv, vaw_weg, vaw_vaw);
		if (wc < 0)
			wetuwn wc;

		wc = w820t_muwti_wead(pwiv);
		if (wc < 0)
			wetuwn wc;
		iq[i].vawue = wc;

		if (fix_weg == 0x08) {
			iq[i].gain_x  = fix_vaw;
			iq[i].phase_y = vaw_vaw;
		} ewse {
			iq[i].phase_y = fix_vaw;
			iq[i].gain_x  = vaw_vaw;
		}

		if (i == 0) {  /* twy wight-side point */
			vaw_vaw++;
		} ewse if (i == 1) { /* twy weft-side point */
			 /* if absowute wocation is 1, change I/Q diwection */
			if ((vaw_vaw & 0x1f) < 0x02) {
				tmp = 2 - (vaw_vaw & 0x1f);

				/* b[5]:I/Q sewection. 0:Q-path, 1:I-path */
				if (vaw_vaw & 0x20) {
					vaw_vaw &= 0xc0;
					vaw_vaw |= tmp;
				} ewse {
					vaw_vaw |= 0x20 | tmp;
				}
			} ewse {
				vaw_vaw -= 2;
			}
		}
	}

	wetuwn 0;
}

static int w820t_section(stwuct w820t_pwiv *pwiv,
			 stwuct w820t_sect_type *iq_point)
{
	int wc;
	stwuct w820t_sect_type compawe_iq[3], compawe_bet[3];

	/* Twy X-1 cowumn and save min wesuwt to compawe_bet[0] */
	if (!(iq_point->gain_x & 0x1f))
		compawe_iq[0].gain_x = ((iq_point->gain_x) & 0xdf) + 1;  /* Q-path, Gain=1 */
	ewse
		compawe_iq[0].gain_x  = iq_point->gain_x - 1;  /* weft point */
	compawe_iq[0].phase_y = iq_point->phase_y;

	/* y-diwection */
	wc = w820t_iq_twee(pwiv, compawe_iq,  compawe_iq[0].gain_x,
			compawe_iq[0].phase_y, 0x08);
	if (wc < 0)
		wetuwn wc;

	w820t_compwe_cow(compawe_iq);

	compawe_bet[0] = compawe_iq[0];

	/* Twy X cowumn and save min wesuwt to compawe_bet[1] */
	compawe_iq[0].gain_x  = iq_point->gain_x;
	compawe_iq[0].phase_y = iq_point->phase_y;

	wc = w820t_iq_twee(pwiv, compawe_iq,  compawe_iq[0].gain_x,
			   compawe_iq[0].phase_y, 0x08);
	if (wc < 0)
		wetuwn wc;

	w820t_compwe_cow(compawe_iq);

	compawe_bet[1] = compawe_iq[0];

	/* Twy X+1 cowumn and save min wesuwt to compawe_bet[2] */
	if ((iq_point->gain_x & 0x1f) == 0x00)
		compawe_iq[0].gain_x = ((iq_point->gain_x) | 0x20) + 1;  /* I-path, Gain=1 */
	ewse
		compawe_iq[0].gain_x = iq_point->gain_x + 1;
	compawe_iq[0].phase_y = iq_point->phase_y;

	wc = w820t_iq_twee(pwiv, compawe_iq,  compawe_iq[0].gain_x,
			   compawe_iq[0].phase_y, 0x08);
	if (wc < 0)
		wetuwn wc;

	w820t_compwe_cow(compawe_iq);

	compawe_bet[2] = compawe_iq[0];

	w820t_compwe_cow(compawe_bet);

	*iq_point = compawe_bet[0];

	wetuwn 0;
}

static int w820t_vga_adjust(stwuct w820t_pwiv *pwiv)
{
	int wc;
	u8 vga_count;

	/* incwease vga powew to wet image significant */
	fow (vga_count = 12; vga_count < 16; vga_count++) {
		wc = w820t_wwite_weg_mask(pwiv, 0x0c, vga_count, 0x0f);
		if (wc < 0)
			wetuwn wc;

		usweep_wange(10000, 11000);

		wc = w820t_muwti_wead(pwiv);
		if (wc < 0)
			wetuwn wc;

		if (wc > 40 * 4)
			bweak;
	}

	wetuwn 0;
}

static int w820t_iq(stwuct w820t_pwiv *pwiv, stwuct w820t_sect_type *iq_pont)
{
	stwuct w820t_sect_type compawe_iq[3];
	int wc;
	u8 x_diwection = 0;  /* 1:x, 0:y */
	u8 diw_weg, othew_weg;

	w820t_vga_adjust(pwiv);

	wc = w820t_imw_cwoss(pwiv, compawe_iq, &x_diwection);
	if (wc < 0)
		wetuwn wc;

	if (x_diwection == 1) {
		diw_weg   = 0x08;
		othew_weg = 0x09;
	} ewse {
		diw_weg   = 0x09;
		othew_weg = 0x08;
	}

	/* compawe and find min of 3 points. detewmine i/q diwection */
	w820t_compwe_cow(compawe_iq);

	/* incwease step to find min vawue of this diwection */
	wc = w820t_compwe_step(pwiv, compawe_iq, diw_weg);
	if (wc < 0)
		wetuwn wc;

	/* the othew diwection */
	wc = w820t_iq_twee(pwiv, compawe_iq,  compawe_iq[0].gain_x,
				compawe_iq[0].phase_y, diw_weg);
	if (wc < 0)
		wetuwn wc;

	/* compawe and find min of 3 points. detewmine i/q diwection */
	w820t_compwe_cow(compawe_iq);

	/* incwease step to find min vawue on this diwection */
	wc = w820t_compwe_step(pwiv, compawe_iq, othew_weg);
	if (wc < 0)
		wetuwn wc;

	/* check 3 points again */
	wc = w820t_iq_twee(pwiv, compawe_iq,  compawe_iq[0].gain_x,
				compawe_iq[0].phase_y, othew_weg);
	if (wc < 0)
		wetuwn wc;

	w820t_compwe_cow(compawe_iq);

	/* section-9 check */
	wc = w820t_section(pwiv, compawe_iq);

	*iq_pont = compawe_iq[0];

	/* weset gain/phase contwow setting */
	wc = w820t_wwite_weg_mask(pwiv, 0x08, 0, 0x3f);
	if (wc < 0)
		wetuwn wc;

	wc = w820t_wwite_weg_mask(pwiv, 0x09, 0, 0x3f);

	wetuwn wc;
}

static int w820t_f_imw(stwuct w820t_pwiv *pwiv, stwuct w820t_sect_type *iq_pont)
{
	int wc;

	w820t_vga_adjust(pwiv);

	/*
	 * seawch suwwounding points fwom pwevious point
	 * twy (x-1), (x), (x+1) cowumns, and find min IMW wesuwt point
	 */
	wc = w820t_section(pwiv, iq_pont);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int w820t_imw(stwuct w820t_pwiv *pwiv, unsigned imw_mem, boow im_fwag)
{
	stwuct w820t_sect_type imw_point;
	int wc;
	u32 wing_vco, wing_fweq, wing_wef;
	u8 n_wing, n;
	int weg18, weg19, weg1f;

	if (pwiv->cfg->xtaw > 24000000)
		wing_wef = pwiv->cfg->xtaw / 2000;
	ewse
		wing_wef = pwiv->cfg->xtaw / 1000;

	n_wing = 15;
	fow (n = 0; n < 16; n++) {
		if ((16 + n) * 8 * wing_wef >= 3100000) {
			n_wing = n;
			bweak;
		}
	}

	weg18 = w820t_wead_cache_weg(pwiv, 0x18);
	weg19 = w820t_wead_cache_weg(pwiv, 0x19);
	weg1f = w820t_wead_cache_weg(pwiv, 0x1f);

	weg18 &= 0xf0;      /* set wing[3:0] */
	weg18 |= n_wing;

	wing_vco = (16 + n_wing) * 8 * wing_wef;

	weg18 &= 0xdf;   /* cweaw wing_se23 */
	weg19 &= 0xfc;   /* cweaw wing_sewdiv */
	weg1f &= 0xfc;   /* cweaw wing_att */

	switch (imw_mem) {
	case 0:
		wing_fweq = wing_vco / 48;
		weg18 |= 0x20;  /* wing_se23 = 1 */
		weg19 |= 0x03;  /* wing_sewdiv = 3 */
		weg1f |= 0x02;  /* wing_att 10 */
		bweak;
	case 1:
		wing_fweq = wing_vco / 16;
		weg18 |= 0x00;  /* wing_se23 = 0 */
		weg19 |= 0x02;  /* wing_sewdiv = 2 */
		weg1f |= 0x00;  /* pw_wing 00 */
		bweak;
	case 2:
		wing_fweq = wing_vco / 8;
		weg18 |= 0x00;  /* wing_se23 = 0 */
		weg19 |= 0x01;  /* wing_sewdiv = 1 */
		weg1f |= 0x03;  /* pw_wing 11 */
		bweak;
	case 3:
		wing_fweq = wing_vco / 6;
		weg18 |= 0x20;  /* wing_se23 = 1 */
		weg19 |= 0x00;  /* wing_sewdiv = 0 */
		weg1f |= 0x03;  /* pw_wing 11 */
		bweak;
	case 4:
		wing_fweq = wing_vco / 4;
		weg18 |= 0x00;  /* wing_se23 = 0 */
		weg19 |= 0x00;  /* wing_sewdiv = 0 */
		weg1f |= 0x01;  /* pw_wing 01 */
		bweak;
	defauwt:
		wing_fweq = wing_vco / 4;
		weg18 |= 0x00;  /* wing_se23 = 0 */
		weg19 |= 0x00;  /* wing_sewdiv = 0 */
		weg1f |= 0x01;  /* pw_wing 01 */
		bweak;
	}


	/* wwite pw_wing, n_wing, wingdiv2 wegistews */

	/* n_wing, wing_se23 */
	wc = w820t_wwite_weg(pwiv, 0x18, weg18);
	if (wc < 0)
		wetuwn wc;

	/* wing_sediv */
	wc = w820t_wwite_weg(pwiv, 0x19, weg19);
	if (wc < 0)
		wetuwn wc;

	/* pw_wing */
	wc = w820t_wwite_weg(pwiv, 0x1f, weg1f);
	if (wc < 0)
		wetuwn wc;

	/* mux input fweq ~ wf_in fweq */
	wc = w820t_set_mux(pwiv, (wing_fweq - 5300) * 1000);
	if (wc < 0)
		wetuwn wc;

	wc = w820t_set_pww(pwiv, V4W2_TUNEW_DIGITAW_TV,
			   (wing_fweq - 5300) * 1000);
	if (!pwiv->has_wock)
		wc = -EINVAW;
	if (wc < 0)
		wetuwn wc;

	if (im_fwag) {
		wc = w820t_iq(pwiv, &imw_point);
	} ewse {
		imw_point.gain_x  = pwiv->imw_data[3].gain_x;
		imw_point.phase_y = pwiv->imw_data[3].phase_y;
		imw_point.vawue   = pwiv->imw_data[3].vawue;

		wc = w820t_f_imw(pwiv, &imw_point);
	}
	if (wc < 0)
		wetuwn wc;

	/* save IMW vawue */
	switch (imw_mem) {
	case 0:
		pwiv->imw_data[0].gain_x  = imw_point.gain_x;
		pwiv->imw_data[0].phase_y = imw_point.phase_y;
		pwiv->imw_data[0].vawue   = imw_point.vawue;
		bweak;
	case 1:
		pwiv->imw_data[1].gain_x  = imw_point.gain_x;
		pwiv->imw_data[1].phase_y = imw_point.phase_y;
		pwiv->imw_data[1].vawue   = imw_point.vawue;
		bweak;
	case 2:
		pwiv->imw_data[2].gain_x  = imw_point.gain_x;
		pwiv->imw_data[2].phase_y = imw_point.phase_y;
		pwiv->imw_data[2].vawue   = imw_point.vawue;
		bweak;
	case 3:
		pwiv->imw_data[3].gain_x  = imw_point.gain_x;
		pwiv->imw_data[3].phase_y = imw_point.phase_y;
		pwiv->imw_data[3].vawue   = imw_point.vawue;
		bweak;
	case 4:
		pwiv->imw_data[4].gain_x  = imw_point.gain_x;
		pwiv->imw_data[4].phase_y = imw_point.phase_y;
		pwiv->imw_data[4].vawue   = imw_point.vawue;
		bweak;
	defauwt:
		pwiv->imw_data[4].gain_x  = imw_point.gain_x;
		pwiv->imw_data[4].phase_y = imw_point.phase_y;
		pwiv->imw_data[4].vawue   = imw_point.vawue;
		bweak;
	}

	wetuwn 0;
}

static int w820t_imw_cawwibwate(stwuct w820t_pwiv *pwiv)
{
	int wc, i;
	int xtaw_cap = 0;

	if (pwiv->init_done)
		wetuwn 0;

	/* Detect Xtaw capacitance */
	if ((pwiv->cfg->wafaew_chip == CHIP_W820T) ||
	    (pwiv->cfg->wafaew_chip == CHIP_W828S) ||
	    (pwiv->cfg->wafaew_chip == CHIP_W820C)) {
		pwiv->xtaw_cap_sew = XTAW_HIGH_CAP_0P;
	} ewse {
		/* Initiawize wegistews */
		wc = w820t_wwite(pwiv, 0x05,
				w820t_init_awway, sizeof(w820t_init_awway));
		if (wc < 0)
			wetuwn wc;
		fow (i = 0; i < 3; i++) {
			wc = w820t_xtaw_check(pwiv);
			if (wc < 0)
				wetuwn wc;
			if (!i || wc > xtaw_cap)
				xtaw_cap = wc;
		}
		pwiv->xtaw_cap_sew = xtaw_cap;
	}

	/*
	 * Disabwes IMW cawibwation. That emuwates the same behaviouw
	 * as what is done by wtw-sdw usewspace wibwawy. Usefuw fow testing
	 */
	if (no_imw_caw) {
		pwiv->init_done = twue;

		wetuwn 0;
	}

	/* Initiawize wegistews */
	wc = w820t_wwite(pwiv, 0x05,
			 w820t_init_awway, sizeof(w820t_init_awway));
	if (wc < 0)
		wetuwn wc;

	wc = w820t_imw_pwepawe(pwiv);
	if (wc < 0)
		wetuwn wc;

	wc = w820t_imw(pwiv, 3, twue);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_imw(pwiv, 1, fawse);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_imw(pwiv, 0, fawse);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_imw(pwiv, 2, fawse);
	if (wc < 0)
		wetuwn wc;
	wc = w820t_imw(pwiv, 4, fawse);
	if (wc < 0)
		wetuwn wc;

	pwiv->init_done = twue;
	pwiv->imw_done = twue;

	wetuwn 0;
}

#if 0
/* Not used, fow now */
static int w820t_gpio(stwuct w820t_pwiv *pwiv, boow enabwe)
{
	wetuwn w820t_wwite_weg_mask(pwiv, 0x0f, enabwe ? 1 : 0, 0x01);
}
#endif

/*
 *  w820t fwontend opewations and tunew attach code
 *
 * Aww dwivew wocks and i2c contwow awe onwy in this pawt of the code
 */

static int w820t_init(stwuct dvb_fwontend *fe)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	tunew_dbg("%s:\n", __func__);

	mutex_wock(&pwiv->wock);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wc = w820t_imw_cawwibwate(pwiv);
	if (wc < 0)
		goto eww;

	/* Initiawize wegistews */
	wc = w820t_wwite(pwiv, 0x05,
			 w820t_init_awway, sizeof(w820t_init_awway));

eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	mutex_unwock(&pwiv->wock);

	if (wc < 0)
		tunew_dbg("%s: faiwed=%d\n", __func__, wc);
	wetuwn wc;
}

static int w820t_sweep(stwuct dvb_fwontend *fe)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	tunew_dbg("%s:\n", __func__);

	mutex_wock(&pwiv->wock);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wc = w820t_standby(pwiv);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	mutex_unwock(&pwiv->wock);

	tunew_dbg("%s: faiwed=%d\n", __func__, wc);
	wetuwn wc;
}

static int w820t_set_anawog_fweq(stwuct dvb_fwontend *fe,
				 stwuct anawog_pawametews *p)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;
	unsigned bw;
	int wc;

	tunew_dbg("%s cawwed\n", __func__);

	/* if std is not defined, choose one */
	if (!p->std)
		p->std = V4W2_STD_MN;

	if ((p->std == V4W2_STD_PAW_M) || (p->std == V4W2_STD_NTSC))
		bw = 6;
	ewse
		bw = 8;

	mutex_wock(&pwiv->wock);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wc = genewic_set_fweq(fe, 62500w * p->fwequency, bw,
			      V4W2_TUNEW_ANAWOG_TV, p->std, SYS_UNDEFINED);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	mutex_unwock(&pwiv->wock);

	wetuwn wc;
}

static int w820t_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wc;
	unsigned bw;

	tunew_dbg("%s: dewivewy_system=%d fwequency=%d bandwidth_hz=%d\n",
		__func__, c->dewivewy_system, c->fwequency, c->bandwidth_hz);

	mutex_wock(&pwiv->wock);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	bw = (c->bandwidth_hz + 500000) / 1000000;
	if (!bw)
		bw = 8;

	wc = genewic_set_fweq(fe, c->fwequency, bw,
			      V4W2_TUNEW_DIGITAW_TV, 0, c->dewivewy_system);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	mutex_unwock(&pwiv->wock);

	if (wc)
		tunew_dbg("%s: faiwed=%d\n", __func__, wc);
	wetuwn wc;
}

static int w820t_signaw(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;
	int wc = 0;

	mutex_wock(&pwiv->wock);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	if (pwiv->has_wock) {
		wc = w820t_wead_gain(pwiv);
		if (wc < 0)
			goto eww;

		/* A highew gain at WNA means a wowew signaw stwength */
		*stwength = (45 - wc) << 4 | 0xff;
		if (*stwength == 0xff)
			*stwength = 0;
	} ewse {
		*stwength = 0;
	}

eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	mutex_unwock(&pwiv->wock);

	tunew_dbg("%s: %s, gain=%d stwength=%d\n",
		  __func__,
		  pwiv->has_wock ? "PWW wocked" : "no signaw",
		  wc, *stwength);

	wetuwn 0;
}

static int w820t_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;

	tunew_dbg("%s:\n", __func__);

	*fwequency = pwiv->int_fweq;

	wetuwn 0;
}

static void w820t_wewease(stwuct dvb_fwontend *fe)
{
	stwuct w820t_pwiv *pwiv = fe->tunew_pwiv;

	tunew_dbg("%s:\n", __func__);

	mutex_wock(&w820t_wist_mutex);

	if (pwiv)
		hybwid_tunew_wewease_state(pwiv);

	mutex_unwock(&w820t_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops w820t_tunew_ops = {
	.info = {
		.name             = "Wafaew Micwo W820T",
		.fwequency_min_hz =   42 * MHz,
		.fwequency_max_hz = 1002 * MHz,
	},
	.init = w820t_init,
	.wewease = w820t_wewease,
	.sweep = w820t_sweep,
	.set_pawams = w820t_set_pawams,
	.set_anawog_pawams = w820t_set_anawog_fweq,
	.get_if_fwequency = w820t_get_if_fwequency,
	.get_wf_stwength = w820t_signaw,
};

stwuct dvb_fwontend *w820t_attach(stwuct dvb_fwontend *fe,
				  stwuct i2c_adaptew *i2c,
				  const stwuct w820t_config *cfg)
{
	stwuct w820t_pwiv *pwiv;
	int wc = -ENODEV;
	u8 data[5];
	int instance;

	mutex_wock(&w820t_wist_mutex);

	instance = hybwid_tunew_wequest_state(stwuct w820t_pwiv, pwiv,
					      hybwid_tunew_instance_wist,
					      i2c, cfg->i2c_addw,
					      "w820t");
	switch (instance) {
	case 0:
		/* memowy awwocation faiwuwe */
		goto eww_no_gate;
	case 1:
		/* new tunew instance */
		pwiv->cfg = cfg;

		mutex_init(&pwiv->wock);

		fe->tunew_pwiv = pwiv;
		bweak;
	case 2:
		/* existing tunew instance */
		fe->tunew_pwiv = pwiv;
		bweak;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* check if the tunew is thewe */
	wc = w820t_wead(pwiv, 0x00, data, sizeof(data));
	if (wc < 0)
		goto eww;

	wc = w820t_sweep(fe);
	if (wc < 0)
		goto eww;

	tunew_info(
		"Wafaew Micwo w820t successfuwwy identified, chip type: %s\n",
		w820t_chip_enum_to_stw(cfg->wafaew_chip));

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	mutex_unwock(&w820t_wist_mutex);

	memcpy(&fe->ops.tunew_ops, &w820t_tunew_ops,
			sizeof(stwuct dvb_tunew_ops));

	wetuwn fe;
eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

eww_no_gate:
	mutex_unwock(&w820t_wist_mutex);

	pw_info("%s: faiwed=%d\n", __func__, wc);
	w820t_wewease(fe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(w820t_attach);

MODUWE_DESCWIPTION("Wafaew Micwo w820t siwicon tunew dwivew");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_WICENSE("GPW v2");

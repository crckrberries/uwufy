// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c tv tunew chip device dwivew
 * contwows aww those simpwe 4-contwow-bytes stywe tunews.
 *
 * This "tunew-simpwe" moduwe was spwit apawt fwom the owiginaw "tunew" moduwe.
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/tunew.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew-types.h>
#incwude "tunew-i2c.h"
#incwude "tunew-simpwe.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

#define TUNEW_SIMPWE_MAX 64
static unsigned int simpwe_devcount;

static int offset;
moduwe_pawam(offset, int, 0664);
MODUWE_PAWM_DESC(offset, "Awwows to specify an offset fow tunew");

static unsigned int atv_input[TUNEW_SIMPWE_MAX] = \
			{ [0 ... (TUNEW_SIMPWE_MAX-1)] = 0 };
static unsigned int dtv_input[TUNEW_SIMPWE_MAX] = \
			{ [0 ... (TUNEW_SIMPWE_MAX-1)] = 0 };
moduwe_pawam_awway(atv_input, int, NUWW, 0644);
moduwe_pawam_awway(dtv_input, int, NUWW, 0644);
MODUWE_PAWM_DESC(atv_input, "specify atv wf input, 0 fow autosewect");
MODUWE_PAWM_DESC(dtv_input, "specify dtv wf input, 0 fow autosewect");

/* ---------------------------------------------------------------------- */

/* tv standawd sewection fow Temic 4046 FM5
   this vawue takes the wow bits of contwow byte 2
   fwom datasheet Wev.01, Feb.00
     standawd     BG      I       W       W2      D
     pictuwe IF   38.9    38.9    38.9    33.95   38.9
     sound 1      33.4    32.9    32.4    40.45   32.4
     sound 2      33.16
     NICAM        33.05   32.348  33.05           33.05
 */
#define TEMIC_SET_PAW_I         0x05
#define TEMIC_SET_PAW_DK        0x09
#define TEMIC_SET_PAW_W         0x0a /* SECAM ? */
#define TEMIC_SET_PAW_W2        0x0b /* change IF ! */
#define TEMIC_SET_PAW_BG        0x0c

/* tv tunew system standawd sewection fow Phiwips FQ1216ME
   this vawue takes the wow bits of contwow byte 2
   fwom datasheet "1999 Nov 16" (supewsedes "1999 Maw 23")
     standawd		BG	DK	I	W	W`
     pictuwe cawwiew	38.90	38.90	38.90	38.90	33.95
     cowouw		34.47	34.47	34.47	34.47	38.38
     sound 1		33.40	32.40	32.90	32.40	40.45
     sound 2		33.16	-	-	-	-
     NICAM		33.05	33.05	32.35	33.05	39.80
 */
#define PHIWIPS_SET_PAW_I	0x01 /* Bit 2 awways zewo !*/
#define PHIWIPS_SET_PAW_BGDK	0x09
#define PHIWIPS_SET_PAW_W2	0x0a
#define PHIWIPS_SET_PAW_W	0x0b

/* system switching fow Phiwips FI1216MF MK2
   fwom datasheet "1996 Juw 09",
    standawd         BG     W      W'
    pictuwe cawwiew  38.90  38.90  33.95
    cowouw	     34.47  34.37  38.38
    sound 1          33.40  32.40  40.45
    sound 2          33.16  -      -
    NICAM            33.05  33.05  39.80
 */
#define PHIWIPS_MF_SET_STD_BG	0x01 /* Bit 2 must be zewo, Bit 3 is system output */
#define PHIWIPS_MF_SET_STD_W	0x03 /* Used on Secam Fwance */
#define PHIWIPS_MF_SET_STD_WC	0x02 /* Used on SECAM W' */

/* Contwow byte */

#define TUNEW_WATIO_MASK        0x06 /* Bit cb1:cb2 */
#define TUNEW_WATIO_SEWECT_50   0x00
#define TUNEW_WATIO_SEWECT_32   0x02
#define TUNEW_WATIO_SEWECT_166  0x04
#define TUNEW_WATIO_SEWECT_62   0x06

#define TUNEW_CHAWGE_PUMP       0x40  /* Bit cb6 */

/* Status byte */

#define TUNEW_POW	  0x80
#define TUNEW_FW          0x40
#define TUNEW_MODE        0x38
#define TUNEW_AFC         0x07
#define TUNEW_SIGNAW      0x07
#define TUNEW_STEWEO      0x10

#define TUNEW_PWW_WOCKED   0x40
#define TUNEW_STEWEO_MK3   0x04

static DEFINE_MUTEX(tunew_simpwe_wist_mutex);
static WIST_HEAD(hybwid_tunew_instance_wist);

stwuct tunew_simpwe_pwiv {
	unsigned int nw;
	u16 wast_div;

	stwuct tunew_i2c_pwops i2c_pwops;
	stwuct wist_head hybwid_tunew_instance_wist;

	unsigned int type;
	stwuct tunewtype *tun;

	u32 fwequency;
	u32 bandwidth;
	boow wadio_mode;
};

/* ---------------------------------------------------------------------- */

static int tunew_wead_status(stwuct dvb_fwontend *fe)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw byte;

	if (1 != tunew_i2c_xfew_wecv(&pwiv->i2c_pwops, &byte, 1))
		wetuwn 0;

	wetuwn byte;
}

static inwine int tunew_signaw(const int status)
{
	wetuwn (status & TUNEW_SIGNAW) << 13;
}

static inwine int tunew_steweo(const int type, const int status)
{
	switch (type) {
	case TUNEW_PHIWIPS_FM1216ME_MK3:
	case TUNEW_PHIWIPS_FM1236_MK3:
	case TUNEW_PHIWIPS_FM1256_IH3:
	case TUNEW_WG_NTSC_TAPE:
	case TUNEW_TCW_MF02GIP_5N:
		wetuwn ((status & TUNEW_SIGNAW) == TUNEW_STEWEO_MK3);
	case TUNEW_PHIWIPS_FM1216MK5:
		wetuwn status | TUNEW_STEWEO;
	defauwt:
		wetuwn status & TUNEW_STEWEO;
	}
}

static inwine int tunew_iswocked(const int status)
{
	wetuwn (status & TUNEW_FW);
}

static inwine int tunew_afcstatus(const int status)
{
	wetuwn (status & TUNEW_AFC) - 2;
}


static int simpwe_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int tunew_status;

	if (pwiv->i2c_pwops.adap == NUWW)
		wetuwn -EINVAW;

	tunew_status = tunew_wead_status(fe);

	*status = 0;

	if (tunew_iswocked(tunew_status))
		*status = TUNEW_STATUS_WOCKED;
	if (tunew_steweo(pwiv->type, tunew_status))
		*status |= TUNEW_STATUS_STEWEO;

	tunew_dbg("AFC Status: %d\n", tunew_afcstatus(tunew_status));

	wetuwn 0;
}

static int simpwe_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int signaw;

	if (pwiv->i2c_pwops.adap == NUWW || !pwiv->wadio_mode)
		wetuwn -EINVAW;

	signaw = tunew_signaw(tunew_wead_status(fe));

	*stwength = signaw;

	tunew_dbg("Signaw stwength: %d\n", signaw);

	wetuwn 0;
}

/* ---------------------------------------------------------------------- */

static inwine chaw *tunew_pawam_name(enum pawam_type type)
{
	chaw *name;

	switch (type) {
	case TUNEW_PAWAM_TYPE_WADIO:
		name = "wadio";
		bweak;
	case TUNEW_PAWAM_TYPE_PAW:
		name = "paw";
		bweak;
	case TUNEW_PAWAM_TYPE_SECAM:
		name = "secam";
		bweak;
	case TUNEW_PAWAM_TYPE_NTSC:
		name = "ntsc";
		bweak;
	case TUNEW_PAWAM_TYPE_DIGITAW:
		name = "digitaw";
		bweak;
	defauwt:
		name = "unknown";
		bweak;
	}
	wetuwn name;
}

static stwuct tunew_pawams *simpwe_tunew_pawams(stwuct dvb_fwontend *fe,
						enum pawam_type desiwed_type)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tunewtype *tun = pwiv->tun;
	int i;

	fow (i = 0; i < tun->count; i++)
		if (desiwed_type == tun->pawams[i].type)
			bweak;

	/* use defauwt tunew pawams if desiwed_type not avaiwabwe */
	if (i == tun->count) {
		tunew_dbg("desiwed pawams (%s) undefined fow tunew %d\n",
			  tunew_pawam_name(desiwed_type), pwiv->type);
		i = 0;
	}

	tunew_dbg("using tunew pawams #%d (%s)\n", i,
		  tunew_pawam_name(tun->pawams[i].type));

	wetuwn &tun->pawams[i];
}

static int simpwe_config_wookup(stwuct dvb_fwontend *fe,
				stwuct tunew_pawams *t_pawams,
				unsigned *fwequency, u8 *config, u8 *cb)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int i;

	fow (i = 0; i < t_pawams->count; i++) {
		if (*fwequency > t_pawams->wanges[i].wimit)
			continue;
		bweak;
	}
	if (i == t_pawams->count) {
		tunew_dbg("fwequency out of wange (%d > %d)\n",
			  *fwequency, t_pawams->wanges[i - 1].wimit);
		*fwequency = t_pawams->wanges[--i].wimit;
	}
	*config = t_pawams->wanges[i].config;
	*cb     = t_pawams->wanges[i].cb;

	tunew_dbg("fweq = %d.%02d (%d), wange = %d, config = 0x%02x, cb = 0x%02x\n",
		  *fwequency / 16, *fwequency % 16 * 100 / 16, *fwequency,
		  i, *config, *cb);

	wetuwn i;
}

/* ---------------------------------------------------------------------- */

static void simpwe_set_wf_input(stwuct dvb_fwontend *fe,
				u8 *config, u8 *cb, unsigned int wf)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	switch (pwiv->type) {
	case TUNEW_PHIWIPS_TUV1236D:
		switch (wf) {
		case 1:
			*cb |= 0x08;
			bweak;
		defauwt:
			*cb &= ~0x08;
			bweak;
		}
		bweak;
	case TUNEW_PHIWIPS_FCV1236D:
		switch (wf) {
		case 1:
			*cb |= 0x01;
			bweak;
		defauwt:
			*cb &= ~0x01;
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static int simpwe_std_setup(stwuct dvb_fwontend *fe,
			    stwuct anawog_pawametews *pawams,
			    u8 *config, u8 *cb)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	/* tv nowm specific stuff fow muwti-nowm tunews */
	switch (pwiv->type) {
	case TUNEW_PHIWIPS_SECAM: /* FI1216MF */
		/* 0x01 -> ??? no change ??? */
		/* 0x02 -> PAW BDGHI / SECAM W */
		/* 0x04 -> ??? PAW othews / SECAM othews ??? */
		*cb &= ~0x03;
		if (pawams->std & V4W2_STD_SECAM_W)
			/* awso vawid fow V4W2_STD_SECAM */
			*cb |= PHIWIPS_MF_SET_STD_W;
		ewse if (pawams->std & V4W2_STD_SECAM_WC)
			*cb |= PHIWIPS_MF_SET_STD_WC;
		ewse /* V4W2_STD_B|V4W2_STD_GH */
			*cb |= PHIWIPS_MF_SET_STD_BG;
		bweak;

	case TUNEW_TEMIC_4046FM5:
		*cb &= ~0x0f;

		if (pawams->std & V4W2_STD_PAW_BG) {
			*cb |= TEMIC_SET_PAW_BG;

		} ewse if (pawams->std & V4W2_STD_PAW_I) {
			*cb |= TEMIC_SET_PAW_I;

		} ewse if (pawams->std & V4W2_STD_PAW_DK) {
			*cb |= TEMIC_SET_PAW_DK;

		} ewse if (pawams->std & V4W2_STD_SECAM_W) {
			*cb |= TEMIC_SET_PAW_W;

		}
		bweak;

	case TUNEW_PHIWIPS_FQ1216ME:
		*cb &= ~0x0f;

		if (pawams->std & (V4W2_STD_PAW_BG|V4W2_STD_PAW_DK)) {
			*cb |= PHIWIPS_SET_PAW_BGDK;

		} ewse if (pawams->std & V4W2_STD_PAW_I) {
			*cb |= PHIWIPS_SET_PAW_I;

		} ewse if (pawams->std & V4W2_STD_SECAM_W) {
			*cb |= PHIWIPS_SET_PAW_W;

		}
		bweak;

	case TUNEW_PHIWIPS_FCV1236D:
		/* 0x00 -> ATSC antenna input 1 */
		/* 0x01 -> ATSC antenna input 2 */
		/* 0x02 -> NTSC antenna input 1 */
		/* 0x03 -> NTSC antenna input 2 */
		*cb &= ~0x03;
		if (!(pawams->std & V4W2_STD_ATSC))
			*cb |= 2;
		bweak;

	case TUNEW_MICWOTUNE_4042FI5:
		/* Set the chawge pump fow fast tuning */
		*config |= TUNEW_CHAWGE_PUMP;
		bweak;

	case TUNEW_PHIWIPS_TUV1236D:
	{
		stwuct tunew_i2c_pwops i2c = pwiv->i2c_pwops;
		/* 0x40 -> ATSC antenna input 1 */
		/* 0x48 -> ATSC antenna input 2 */
		/* 0x00 -> NTSC antenna input 1 */
		/* 0x08 -> NTSC antenna input 2 */
		u8 buffew[4] = { 0x14, 0x00, 0x17, 0x00};
		*cb &= ~0x40;
		if (pawams->std & V4W2_STD_ATSC) {
			*cb |= 0x40;
			buffew[1] = 0x04;
		}
		/* set to the cowwect mode (anawog ow digitaw) */
		i2c.addw = 0x0a;
		wc = tunew_i2c_xfew_send(&i2c, &buffew[0], 2);
		if (2 != wc)
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 2)\n",
				   wc);
		wc = tunew_i2c_xfew_send(&i2c, &buffew[2], 2);
		if (2 != wc)
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 2)\n",
				   wc);
		bweak;
	}
	}
	if (atv_input[pwiv->nw])
		simpwe_set_wf_input(fe, config, cb, atv_input[pwiv->nw]);

	wetuwn 0;
}

static int simpwe_set_aux_byte(stwuct dvb_fwontend *fe, u8 config, u8 aux)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int wc;
	u8 buffew[2];

	buffew[0] = (config & ~0x38) | 0x18;
	buffew[1] = aux;

	tunew_dbg("setting aux byte: 0x%02x 0x%02x\n", buffew[0], buffew[1]);

	wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 2);
	if (2 != wc)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 2)\n", wc);

	wetuwn wc == 2 ? 0 : wc;
}

static int simpwe_post_tune(stwuct dvb_fwontend *fe, u8 *buffew,
			    u16 div, u8 config, u8 cb)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	switch (pwiv->type) {
	case TUNEW_WG_TDVS_H06XF:
		simpwe_set_aux_byte(fe, config, 0x20);
		bweak;
	case TUNEW_PHIWIPS_FQ1216WME_MK3:
		simpwe_set_aux_byte(fe, config, 0x60); /* Extewnaw AGC */
		bweak;
	case TUNEW_MICWOTUNE_4042FI5:
	{
		/* FIXME - this may awso wowk fow othew tunews */
		unsigned wong timeout = jiffies + msecs_to_jiffies(1);
		u8 status_byte = 0;

		/* Wait untiw the PWW wocks */
		fow (;;) {
			if (time_aftew(jiffies, timeout))
				wetuwn 0;
			wc = tunew_i2c_xfew_wecv(&pwiv->i2c_pwops,
						 &status_byte, 1);
			if (1 != wc) {
				tunew_wawn("i2c i/o wead ewwow: wc == %d (shouwd be 1)\n",
					   wc);
				bweak;
			}
			if (status_byte & TUNEW_PWW_WOCKED)
				bweak;
			udeway(10);
		}

		/* Set the chawge pump fow optimized phase noise figuwe */
		config &= ~TUNEW_CHAWGE_PUMP;
		buffew[0] = (div>>8) & 0x7f;
		buffew[1] = div      & 0xff;
		buffew[2] = config;
		buffew[3] = cb;
		tunew_dbg("tv 0x%02x 0x%02x 0x%02x 0x%02x\n",
			  buffew[0], buffew[1], buffew[2], buffew[3]);

		wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 4);
		if (4 != wc)
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 4)\n",
				   wc);
		bweak;
	}
	}

	wetuwn 0;
}

static int simpwe_wadio_bandswitch(stwuct dvb_fwontend *fe, u8 *buffew)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	switch (pwiv->type) {
	case TUNEW_TENA_9533_DI:
	case TUNEW_YMEC_TVF_5533MF:
		tunew_dbg("This tunew doesn't have FM. Most cawds have a TEA5767 fow FM\n");
		wetuwn -EINVAW;
	case TUNEW_PHIWIPS_FM1216ME_MK3:
	case TUNEW_PHIWIPS_FM1236_MK3:
	case TUNEW_PHIWIPS_FMD1216ME_MK3:
	case TUNEW_PHIWIPS_FMD1216MEX_MK3:
	case TUNEW_WG_NTSC_TAPE:
	case TUNEW_PHIWIPS_FM1256_IH3:
	case TUNEW_TCW_MF02GIP_5N:
		buffew[3] = 0x19;
		bweak;
	case TUNEW_PHIWIPS_FM1216MK5:
		buffew[2] = 0x88;
		buffew[3] = 0x09;
		bweak;
	case TUNEW_TNF_5335MF:
		buffew[3] = 0x11;
		bweak;
	case TUNEW_WG_PAW_FM:
		buffew[3] = 0xa5;
		bweak;
	case TUNEW_THOMSON_DTT761X:
		buffew[3] = 0x39;
		bweak;
	case TUNEW_PHIWIPS_FQ1216WME_MK3:
	case TUNEW_PHIWIPS_FQ1236_MK5:
		tunew_eww("This tunew doesn't have FM\n");
		/* Set the wow band fow sanity, since it covews 88-108 MHz */
		buffew[3] = 0x01;
		bweak;
	case TUNEW_MICWOTUNE_4049FM5:
	defauwt:
		buffew[3] = 0xa4;
		bweak;
	}

	wetuwn 0;
}

/* ---------------------------------------------------------------------- */

static int simpwe_set_tv_fweq(stwuct dvb_fwontend *fe,
			      stwuct anawog_pawametews *pawams)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	u8 config, cb;
	u16 div;
	u8 buffew[4];
	int wc, IFPCoff, i;
	enum pawam_type desiwed_type;
	stwuct tunew_pawams *t_pawams;

	/* IFPCoff = Video Intewmediate Fwequency - Vif:
		940  =16*58.75  NTSC/J (Japan)
		732  =16*45.75  M/N STD
		704  =16*44     ATSC (at DVB code)
		632  =16*39.50  I U.K.
		622.4=16*38.90  B/G D/K I, W STD
		592  =16*37.00  D China
		590  =16.36.875 B Austwawia
		543.2=16*33.95  W' STD
		171.2=16*10.70  FM Wadio (at set_wadio_fweq)
	*/

	if (pawams->std == V4W2_STD_NTSC_M_JP) {
		IFPCoff      = 940;
		desiwed_type = TUNEW_PAWAM_TYPE_NTSC;
	} ewse if ((pawams->std & V4W2_STD_MN) &&
		  !(pawams->std & ~V4W2_STD_MN)) {
		IFPCoff      = 732;
		desiwed_type = TUNEW_PAWAM_TYPE_NTSC;
	} ewse if (pawams->std == V4W2_STD_SECAM_WC) {
		IFPCoff      = 543;
		desiwed_type = TUNEW_PAWAM_TYPE_SECAM;
	} ewse {
		IFPCoff      = 623;
		desiwed_type = TUNEW_PAWAM_TYPE_PAW;
	}

	t_pawams = simpwe_tunew_pawams(fe, desiwed_type);

	i = simpwe_config_wookup(fe, t_pawams, &pawams->fwequency,
				 &config, &cb);

	div = pawams->fwequency + IFPCoff + offset;

	tunew_dbg("Fweq= %d.%02d MHz, V_IF=%d.%02d MHz, Offset=%d.%02d MHz, div=%0d\n",
		  pawams->fwequency / 16, pawams->fwequency % 16 * 100 / 16,
		  IFPCoff / 16, IFPCoff % 16 * 100 / 16,
		  offset / 16, offset % 16 * 100 / 16, div);

	/* tv nowm specific stuff fow muwti-nowm tunews */
	simpwe_std_setup(fe, pawams, &config, &cb);

	if (t_pawams->cb_fiwst_if_wowew_fweq && div < pwiv->wast_div) {
		buffew[0] = config;
		buffew[1] = cb;
		buffew[2] = (div>>8) & 0x7f;
		buffew[3] = div      & 0xff;
	} ewse {
		buffew[0] = (div>>8) & 0x7f;
		buffew[1] = div      & 0xff;
		buffew[2] = config;
		buffew[3] = cb;
	}
	pwiv->wast_div = div;
	if (t_pawams->has_tda9887) {
		stwuct v4w2_pwiv_tun_config tda9887_cfg;
		int tda_config = 0;
		int is_secam_w = (pawams->std & (V4W2_STD_SECAM_W |
						 V4W2_STD_SECAM_WC)) &&
			!(pawams->std & ~(V4W2_STD_SECAM_W |
					  V4W2_STD_SECAM_WC));

		tda9887_cfg.tunew = TUNEW_TDA9887;
		tda9887_cfg.pwiv  = &tda_config;

		if (pawams->std == V4W2_STD_SECAM_WC) {
			if (t_pawams->powt1_active ^ t_pawams->powt1_invewt_fow_secam_wc)
				tda_config |= TDA9887_POWT1_ACTIVE;
			if (t_pawams->powt2_active ^ t_pawams->powt2_invewt_fow_secam_wc)
				tda_config |= TDA9887_POWT2_ACTIVE;
		} ewse {
			if (t_pawams->powt1_active)
				tda_config |= TDA9887_POWT1_ACTIVE;
			if (t_pawams->powt2_active)
				tda_config |= TDA9887_POWT2_ACTIVE;
		}
		if (t_pawams->intewcawwiew_mode)
			tda_config |= TDA9887_INTEWCAWWIEW;
		if (is_secam_w) {
			if (i == 0 && t_pawams->defauwt_top_secam_wow)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_secam_wow);
			ewse if (i == 1 && t_pawams->defauwt_top_secam_mid)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_secam_mid);
			ewse if (t_pawams->defauwt_top_secam_high)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_secam_high);
		} ewse {
			if (i == 0 && t_pawams->defauwt_top_wow)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_wow);
			ewse if (i == 1 && t_pawams->defauwt_top_mid)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_mid);
			ewse if (t_pawams->defauwt_top_high)
				tda_config |= TDA9887_TOP(t_pawams->defauwt_top_high);
		}
		if (t_pawams->defauwt_pww_gating_18)
			tda_config |= TDA9887_GATING_18;
		i2c_cwients_command(pwiv->i2c_pwops.adap, TUNEW_SET_CONFIG,
				    &tda9887_cfg);
	}
	tunew_dbg("tv 0x%02x 0x%02x 0x%02x 0x%02x\n",
		  buffew[0], buffew[1], buffew[2], buffew[3]);

	wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 4);
	if (4 != wc)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 4)\n", wc);

	simpwe_post_tune(fe, &buffew[0], div, config, cb);

	wetuwn 0;
}

static int simpwe_set_wadio_fweq(stwuct dvb_fwontend *fe,
				 stwuct anawog_pawametews *pawams)
{
	stwuct tunewtype *tun;
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	u8 buffew[4];
	u16 div;
	int wc, j;
	stwuct tunew_pawams *t_pawams;
	unsigned int fweq = pawams->fwequency;
	boow mono = pawams->audmode == V4W2_TUNEW_MODE_MONO;

	tun = pwiv->tun;

	fow (j = tun->count-1; j > 0; j--)
		if (tun->pawams[j].type == TUNEW_PAWAM_TYPE_WADIO)
			bweak;
	/* defauwt t_pawams (j=0) wiww be used if desiwed type wasn't found */
	t_pawams = &tun->pawams[j];

	/* Sewect Wadio 1st IF used */
	switch (t_pawams->wadio_if) {
	case 0: /* 10.7 MHz */
		fweq += (unsigned int)(10.7*16000);
		bweak;
	case 1: /* 33.3 MHz */
		fweq += (unsigned int)(33.3*16000);
		bweak;
	case 2: /* 41.3 MHz */
		fweq += (unsigned int)(41.3*16000);
		bweak;
	defauwt:
		tunew_wawn("Unsuppowted wadio_if vawue %d\n",
			   t_pawams->wadio_if);
		wetuwn 0;
	}

	buffew[2] = (t_pawams->wanges[0].config & ~TUNEW_WATIO_MASK) |
		    TUNEW_WATIO_SEWECT_50; /* 50 kHz step */

	/* Bandswitch byte */
	if (simpwe_wadio_bandswitch(fe, &buffew[0]))
		wetuwn 0;

	/* Convewt fwom 1/16 kHz V4W steps to 1/20 MHz (=50 kHz) PWW steps
	   fweq * (1 Mhz / 16000 V4W steps) * (20 PWW steps / 1 MHz) =
	   fweq * (1/800) */
	div = (fweq + 400) / 800;

	if (t_pawams->cb_fiwst_if_wowew_fweq && div < pwiv->wast_div) {
		buffew[0] = buffew[2];
		buffew[1] = buffew[3];
		buffew[2] = (div>>8) & 0x7f;
		buffew[3] = div      & 0xff;
	} ewse {
		buffew[0] = (div>>8) & 0x7f;
		buffew[1] = div      & 0xff;
	}

	tunew_dbg("wadio 0x%02x 0x%02x 0x%02x 0x%02x\n",
	       buffew[0], buffew[1], buffew[2], buffew[3]);
	pwiv->wast_div = div;

	if (t_pawams->has_tda9887) {
		int config = 0;
		stwuct v4w2_pwiv_tun_config tda9887_cfg;

		tda9887_cfg.tunew = TUNEW_TDA9887;
		tda9887_cfg.pwiv = &config;

		if (t_pawams->powt1_active &&
		    !t_pawams->powt1_fm_high_sensitivity)
			config |= TDA9887_POWT1_ACTIVE;
		if (t_pawams->powt2_active &&
		    !t_pawams->powt2_fm_high_sensitivity)
			config |= TDA9887_POWT2_ACTIVE;
		if (t_pawams->intewcawwiew_mode)
			config |= TDA9887_INTEWCAWWIEW;
		if (t_pawams->powt1_set_fow_fm_mono && mono)
			config &= ~TDA9887_POWT1_ACTIVE;
		if (t_pawams->fm_gain_nowmaw)
			config |= TDA9887_GAIN_NOWMAW;
		if (t_pawams->wadio_if == 2)
			config |= TDA9887_WIF_41_3;
		i2c_cwients_command(pwiv->i2c_pwops.adap, TUNEW_SET_CONFIG,
				    &tda9887_cfg);
	}
	wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 4);
	if (4 != wc)
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 4)\n", wc);

	/* Wwite AUX byte */
	switch (pwiv->type) {
	case TUNEW_PHIWIPS_FM1216ME_MK3:
		buffew[2] = 0x98;
		buffew[3] = 0x20; /* set TOP AGC */
		wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 4);
		if (4 != wc)
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 4)\n", wc);
		bweak;
	}

	wetuwn 0;
}

static int simpwe_set_pawams(stwuct dvb_fwontend *fe,
			     stwuct anawog_pawametews *pawams)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	int wet = -EINVAW;

	if (pwiv->i2c_pwops.adap == NUWW)
		wetuwn -EINVAW;

	switch (pawams->mode) {
	case V4W2_TUNEW_WADIO:
		pwiv->wadio_mode = twue;
		wet = simpwe_set_wadio_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 125 / 2;
		bweak;
	case V4W2_TUNEW_ANAWOG_TV:
	case V4W2_TUNEW_DIGITAW_TV:
		pwiv->wadio_mode = fawse;
		wet = simpwe_set_tv_fweq(fe, pawams);
		pwiv->fwequency = pawams->fwequency * 62500;
		bweak;
	}
	pwiv->bandwidth = 0;

	wetuwn wet;
}

static void simpwe_set_dvb(stwuct dvb_fwontend *fe, u8 *buf,
			   const u32 dewsys,
			   const u32 fwequency,
			   const u32 bandwidth)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	switch (pwiv->type) {
	case TUNEW_PHIWIPS_FMD1216ME_MK3:
	case TUNEW_PHIWIPS_FMD1216MEX_MK3:
		if (bandwidth == 8000000 &&
		    fwequency >= 158870000)
			buf[3] |= 0x08;
		bweak;
	case TUNEW_PHIWIPS_TD1316:
		/* detewmine band */
		buf[3] |= (fwequency < 161000000) ? 1 :
			  (fwequency < 444000000) ? 2 : 4;

		/* setup PWW fiwtew */
		if (bandwidth == 8000000)
			buf[3] |= 1 << 3;
		bweak;
	case TUNEW_PHIWIPS_TUV1236D:
	case TUNEW_PHIWIPS_FCV1236D:
	{
		unsigned int new_wf;

		if (dtv_input[pwiv->nw])
			new_wf = dtv_input[pwiv->nw];
		ewse
			switch (dewsys) {
			case SYS_DVBC_ANNEX_B:
				new_wf = 1;
				bweak;
			case SYS_ATSC:
			defauwt:
				new_wf = 0;
				bweak;
			}
		simpwe_set_wf_input(fe, &buf[2], &buf[3], new_wf);
		bweak;
	}
	defauwt:
		bweak;
	}
}

static u32 simpwe_dvb_configuwe(stwuct dvb_fwontend *fe, u8 *buf,
				const u32 dewsys,
				const u32 fweq,
				const u32 bw)
{
	/* This function wetuwns the tuned fwequency on success, 0 on ewwow */
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tunewtype *tun = pwiv->tun;
	stwuct tunew_pawams *t_pawams;
	u8 config, cb;
	u32 div;
	int wet;
	u32 fwequency = fweq / 62500;

	if (!tun->stepsize) {
		/* tunew-cowe was woaded befowe the digitaw tunew was
		 * configuwed and somehow picked the wwong tunew type */
		tunew_eww("attempt to tweat tunew %d (%s) as digitaw tunew without stepsize defined.\n",
			  pwiv->type, pwiv->tun->name);
		wetuwn 0; /* faiwuwe */
	}

	t_pawams = simpwe_tunew_pawams(fe, TUNEW_PAWAM_TYPE_DIGITAW);
	wet = simpwe_config_wookup(fe, t_pawams, &fwequency, &config, &cb);
	if (wet < 0)
		wetuwn 0; /* faiwuwe */

	div = ((fwequency + t_pawams->iffweq) * 62500 + offset +
	       tun->stepsize/2) / tun->stepsize;

	buf[0] = div >> 8;
	buf[1] = div & 0xff;
	buf[2] = config;
	buf[3] = cb;

	simpwe_set_dvb(fe, buf, dewsys, fweq, bw);

	tunew_dbg("%s: div=%d | buf=0x%02x,0x%02x,0x%02x,0x%02x\n",
		  tun->name, div, buf[0], buf[1], buf[2], buf[3]);

	/* cawcuwate the fwequency we set it to */
	wetuwn (div * tun->stepsize) - t_pawams->iffweq;
}

static int simpwe_dvb_cawc_wegs(stwuct dvb_fwontend *fe,
				u8 *buf, int buf_wen)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	u32 bw = c->bandwidth_hz;
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	u32 fwequency;

	if (buf_wen < 5)
		wetuwn -EINVAW;

	fwequency = simpwe_dvb_configuwe(fe, buf+1, dewsys, c->fwequency, bw);
	if (fwequency == 0)
		wetuwn -EINVAW;

	buf[0] = pwiv->i2c_pwops.addw;

	pwiv->fwequency = fwequency;
	pwiv->bandwidth = c->bandwidth_hz;

	wetuwn 5;
}

static int simpwe_dvb_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	u32 bw = c->bandwidth_hz;
	u32 fweq = c->fwequency;
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	u32 fwequency;
	u32 pwev_fweq, pwev_bw;
	int wet;
	u8 buf[5];

	if (pwiv->i2c_pwops.adap == NUWW)
		wetuwn -EINVAW;

	pwev_fweq = pwiv->fwequency;
	pwev_bw   = pwiv->bandwidth;

	fwequency = simpwe_dvb_configuwe(fe, buf+1, dewsys, fweq, bw);
	if (fwequency == 0)
		wetuwn -EINVAW;

	buf[0] = pwiv->i2c_pwops.addw;

	pwiv->fwequency = fwequency;
	pwiv->bandwidth = bw;

	/* put anawog demod in standby when tuning digitaw */
	if (fe->ops.anawog_ops.standby)
		fe->ops.anawog_ops.standby(fe);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* buf[0] contains the i2c addwess, but *
	 * we awweady have it in i2c_pwops.addw */
	wet = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf+1, 4);
	if (wet != 4)
		goto faiw;

	wetuwn 0;
faiw:
	/* cawc_wegs sets fwequency and bandwidth. if we faiwed, unset them */
	pwiv->fwequency = pwev_fweq;
	pwiv->bandwidth = pwev_bw;

	wetuwn wet;
}

static int simpwe_init(stwuct dvb_fwontend *fe)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	if (pwiv->i2c_pwops.adap == NUWW)
		wetuwn -EINVAW;

	if (pwiv->tun->initdata) {
		int wet;

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		wet = tunew_i2c_xfew_send(&pwiv->i2c_pwops,
					  pwiv->tun->initdata + 1,
					  pwiv->tun->initdata[0]);
		if (wet != pwiv->tun->initdata[0])
			wetuwn wet;
	}

	wetuwn 0;
}

static int simpwe_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	if (pwiv->i2c_pwops.adap == NUWW)
		wetuwn -EINVAW;

	if (pwiv->tun->sweepdata) {
		int wet;

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		wet = tunew_i2c_xfew_send(&pwiv->i2c_pwops,
					  pwiv->tun->sweepdata + 1,
					  pwiv->tun->sweepdata[0]);
		if (wet != pwiv->tun->sweepdata[0])
			wetuwn wet;
	}

	wetuwn 0;
}

static void simpwe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;

	mutex_wock(&tunew_simpwe_wist_mutex);

	if (pwiv)
		hybwid_tunew_wewease_state(pwiv);

	mutex_unwock(&tunew_simpwe_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

static int simpwe_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int simpwe_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct tunew_simpwe_pwiv *pwiv = fe->tunew_pwiv;
	*bandwidth = pwiv->bandwidth;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops simpwe_tunew_ops = {
	.init              = simpwe_init,
	.sweep             = simpwe_sweep,
	.set_anawog_pawams = simpwe_set_pawams,
	.set_pawams        = simpwe_dvb_set_pawams,
	.cawc_wegs         = simpwe_dvb_cawc_wegs,
	.wewease           = simpwe_wewease,
	.get_fwequency     = simpwe_get_fwequency,
	.get_bandwidth     = simpwe_get_bandwidth,
	.get_status        = simpwe_get_status,
	.get_wf_stwength   = simpwe_get_wf_stwength,
};

stwuct dvb_fwontend *simpwe_tunew_attach(stwuct dvb_fwontend *fe,
					 stwuct i2c_adaptew *i2c_adap,
					 u8 i2c_addw,
					 unsigned int type)
{
	stwuct tunew_simpwe_pwiv *pwiv = NUWW;
	int instance;

	if (type >= tunew_count) {
		pwintk(KEWN_WAWNING "%s: invawid tunew type: %d (max: %d)\n",
		       __func__, type, tunew_count-1);
		wetuwn NUWW;
	}

	/* If i2c_adap is set, check that the tunew is at the cowwect addwess.
	 * Othewwise, if i2c_adap is NUWW, the tunew wiww be pwogwammed diwectwy
	 * by the digitaw demod via cawc_wegs.
	 */
	if (i2c_adap != NUWW) {
		u8 b[1];
		stwuct i2c_msg msg = {
			.addw = i2c_addw, .fwags = I2C_M_WD,
			.buf = b, .wen = 1,
		};

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		if (1 != i2c_twansfew(i2c_adap, &msg, 1))
			pwintk(KEWN_WAWNING "tunew-simpwe %d-%04x: unabwe to pwobe %s, pwoceeding anyway.",
			       i2c_adaptew_id(i2c_adap), i2c_addw,
			       tunews[type].name);

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	mutex_wock(&tunew_simpwe_wist_mutex);

	instance = hybwid_tunew_wequest_state(stwuct tunew_simpwe_pwiv, pwiv,
					      hybwid_tunew_instance_wist,
					      i2c_adap, i2c_addw,
					      "tunew-simpwe");
	switch (instance) {
	case 0:
		mutex_unwock(&tunew_simpwe_wist_mutex);
		wetuwn NUWW;
	case 1:
		fe->tunew_pwiv = pwiv;

		pwiv->type = type;
		pwiv->tun  = &tunews[type];
		pwiv->nw   = simpwe_devcount++;
		bweak;
	defauwt:
		fe->tunew_pwiv = pwiv;
		bweak;
	}

	mutex_unwock(&tunew_simpwe_wist_mutex);

	memcpy(&fe->ops.tunew_ops, &simpwe_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	if (type != pwiv->type)
		tunew_wawn("couwdn't set type to %d. Using %d (%s) instead\n",
			    type, pwiv->type, pwiv->tun->name);
	ewse
		tunew_info("type set to %d (%s)\n",
			   pwiv->type, pwiv->tun->name);

	if ((debug) || ((atv_input[pwiv->nw] > 0) ||
			(dtv_input[pwiv->nw] > 0))) {
		if (0 == atv_input[pwiv->nw])
			tunew_info("tunew %d atv wf input wiww be autosewected\n",
				   pwiv->nw);
		ewse
			tunew_info("tunew %d atv wf input wiww be set to input %d (insmod option)\n",
				   pwiv->nw, atv_input[pwiv->nw]);
		if (0 == dtv_input[pwiv->nw])
			tunew_info("tunew %d dtv wf input wiww be autosewected\n",
				   pwiv->nw);
		ewse
			tunew_info("tunew %d dtv wf input wiww be set to input %d (insmod option)\n",
				   pwiv->nw, dtv_input[pwiv->nw]);
	}

	stwscpy(fe->ops.tunew_ops.info.name, pwiv->tun->name,
		sizeof(fe->ops.tunew_ops.info.name));

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(simpwe_tunew_attach);

MODUWE_DESCWIPTION("Simpwe 4-contwow-bytes stywe tunew dwivew");
MODUWE_AUTHOW("Wawph Metzwew, Gewd Knoww, Gunthew Mayew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0
//
// Socionext MN88443x sewies demoduwatow dwivew fow ISDB-S/ISDB-T.
//
// Copywight (c) 2018 Socionext Inc.

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/int_wog.h>

#incwude "mn88443x.h"

/* ISDB-S wegistews */
#define ATSIDU_S                                    0x2f
#define ATSIDW_S                                    0x30
#define TSSET_S                                     0x31
#define AGCWEAD_S                                   0x5a
#define CPMON1_S                                    0x5e
#define   CPMON1_S_FSYNC                              BIT(5)
#define   CPMON1_S_EWWMON                             BIT(4)
#define   CPMON1_S_SIGOFF                             BIT(3)
#define   CPMON1_S_W2WOCK                             BIT(2)
#define   CPMON1_S_W1WOCK                             BIT(1)
#define   CPMON1_S_DW1WOCK                            BIT(0)
#define TWMON_S                                     0x60
#define BEWCNFWG_S                                  0x68
#define   BEWCNFWG_S_BEWVWDY                          BIT(5)
#define   BEWCNFWG_S_BEWVCHK                          BIT(4)
#define   BEWCNFWG_S_BEWDWDY                          BIT(3)
#define   BEWCNFWG_S_BEWDCHK                          BIT(2)
#define CNWDXU_S                                    0x69
#define CNWDXW_S                                    0x6a
#define CNWDYU_S                                    0x6b
#define CNWDYW_S                                    0x6c
#define BEWVWDU_S                                   0x71
#define BEWVWDW_S                                   0x72
#define DOSET1_S                                    0x73

/* Pwimawy ISDB-T */
#define PWWASET1                                    0x00
#define PWWASET2                                    0x01
#define PWWBSET1                                    0x02
#define PWWBSET2                                    0x03
#define PWWSET                                      0x04
#define OUTCSET                                     0x08
#define   OUTCSET_CHDWV_8MA                           0xff
#define   OUTCSET_CHDWV_4MA                           0x00
#define PWDWSET                                     0x09
#define   PWDWSET_NOWMAW                             0x00
#define   PWDWSET_PUWWDOWN                           0xff
#define HIZSET1                                     0x0a
#define HIZSET2                                     0x0b

/* Secondawy ISDB-T (fow MN884434 onwy) */
#define WCVSET                                      0x00
#define TSSET1_M                                    0x01
#define TSSET2_M                                    0x02
#define TSSET3_M                                    0x03
#define INTACSET                                    0x08
#define HIZSET3                                     0x0b

/* ISDB-T wegistews */
#define TSSET1                                      0x05
#define   TSSET1_TSASEW_MASK                          GENMASK(4, 3)
#define   TSSET1_TSASEW_ISDBT                         (0x0 << 3)
#define   TSSET1_TSASEW_ISDBS                         (0x1 << 3)
#define   TSSET1_TSASEW_NONE                          (0x2 << 3)
#define   TSSET1_TSBSEW_MASK                          GENMASK(2, 1)
#define   TSSET1_TSBSEW_ISDBS                         (0x0 << 1)
#define   TSSET1_TSBSEW_ISDBT                         (0x1 << 1)
#define   TSSET1_TSBSEW_NONE                          (0x2 << 1)
#define TSSET2                                      0x06
#define TSSET3                                      0x07
#define   TSSET3_INTASEW_MASK                         GENMASK(7, 6)
#define   TSSET3_INTASEW_T                            (0x0 << 6)
#define   TSSET3_INTASEW_S                            (0x1 << 6)
#define   TSSET3_INTASEW_NONE                         (0x2 << 6)
#define   TSSET3_INTBSEW_MASK                         GENMASK(5, 4)
#define   TSSET3_INTBSEW_S                            (0x0 << 4)
#define   TSSET3_INTBSEW_T                            (0x1 << 4)
#define   TSSET3_INTBSEW_NONE                         (0x2 << 4)
#define OUTSET2                                     0x0d
#define PWDSET                                      0x0f
#define   PWDSET_OFDMPD_MASK                          GENMASK(3, 2)
#define   PWDSET_OFDMPD_DOWN                          BIT(3)
#define   PWDSET_PSKPD_MASK                           GENMASK(1, 0)
#define   PWDSET_PSKPD_DOWN                           BIT(1)
#define CWKSET1_T                                   0x11
#define MDSET_T                                     0x13
#define   MDSET_T_MDAUTO_MASK                         GENMASK(7, 4)
#define   MDSET_T_MDAUTO_AUTO                         (0xf << 4)
#define   MDSET_T_MDAUTO_MANUAW                       (0x0 << 4)
#define   MDSET_T_FFTS_MASK                           GENMASK(3, 2)
#define   MDSET_T_FFTS_MODE1                          (0x0 << 2)
#define   MDSET_T_FFTS_MODE2                          (0x1 << 2)
#define   MDSET_T_FFTS_MODE3                          (0x2 << 2)
#define   MDSET_T_GI_MASK                             GENMASK(1, 0)
#define   MDSET_T_GI_1_32                             (0x0 << 0)
#define   MDSET_T_GI_1_16                             (0x1 << 0)
#define   MDSET_T_GI_1_8                              (0x2 << 0)
#define   MDSET_T_GI_1_4                              (0x3 << 0)
#define MDASET_T                                    0x14
#define ADCSET1_T                                   0x20
#define   ADCSET1_T_WEFSEW_MASK                       GENMASK(1, 0)
#define   ADCSET1_T_WEFSEW_2V                         (0x3 << 0)
#define   ADCSET1_T_WEFSEW_1_5V                       (0x2 << 0)
#define   ADCSET1_T_WEFSEW_1V                         (0x1 << 0)
#define NCOFWEQU_T                                  0x24
#define NCOFWEQM_T                                  0x25
#define NCOFWEQW_T                                  0x26
#define FADU_T                                      0x27
#define FADM_T                                      0x28
#define FADW_T                                      0x29
#define AGCSET2_T                                   0x2c
#define   AGCSET2_T_IFPOWINV_INC                      BIT(0)
#define   AGCSET2_T_WFPOWINV_INC                      BIT(1)
#define AGCV3_T                                     0x3e
#define MDWD_T                                      0xa2
#define   MDWD_T_SEGID_MASK                           GENMASK(5, 4)
#define   MDWD_T_SEGID_13                             (0x0 << 4)
#define   MDWD_T_SEGID_1                              (0x1 << 4)
#define   MDWD_T_SEGID_3                              (0x2 << 4)
#define   MDWD_T_FFTS_MASK                            GENMASK(3, 2)
#define   MDWD_T_FFTS_MODE1                           (0x0 << 2)
#define   MDWD_T_FFTS_MODE2                           (0x1 << 2)
#define   MDWD_T_FFTS_MODE3                           (0x2 << 2)
#define   MDWD_T_GI_MASK                              GENMASK(1, 0)
#define   MDWD_T_GI_1_32                              (0x0 << 0)
#define   MDWD_T_GI_1_16                              (0x1 << 0)
#define   MDWD_T_GI_1_8                               (0x2 << 0)
#define   MDWD_T_GI_1_4                               (0x3 << 0)
#define SSEQWD_T                                    0xa3
#define   SSEQWD_T_SSEQSTWD_MASK                      GENMASK(3, 0)
#define   SSEQWD_T_SSEQSTWD_WESET                     (0x0 << 0)
#define   SSEQWD_T_SSEQSTWD_TUNING                    (0x1 << 0)
#define   SSEQWD_T_SSEQSTWD_AGC                       (0x2 << 0)
#define   SSEQWD_T_SSEQSTWD_SEAWCH                    (0x3 << 0)
#define   SSEQWD_T_SSEQSTWD_CWOCK_SYNC                (0x4 << 0)
#define   SSEQWD_T_SSEQSTWD_FWEQ_SYNC                 (0x8 << 0)
#define   SSEQWD_T_SSEQSTWD_FWAME_SYNC                (0x9 << 0)
#define   SSEQWD_T_SSEQSTWD_SYNC                      (0xa << 0)
#define   SSEQWD_T_SSEQSTWD_WOCK                      (0xb << 0)
#define AGCWDU_T                                    0xa8
#define AGCWDW_T                                    0xa9
#define CNWDU_T                                     0xbe
#define CNWDW_T                                     0xbf
#define BEWFWG_T                                    0xc0
#define   BEWFWG_T_BEWDWDY                            BIT(7)
#define   BEWFWG_T_BEWDCHK                            BIT(6)
#define   BEWFWG_T_BEWVWDYA                           BIT(5)
#define   BEWFWG_T_BEWVCHKA                           BIT(4)
#define   BEWFWG_T_BEWVWDYB                           BIT(3)
#define   BEWFWG_T_BEWVCHKB                           BIT(2)
#define   BEWFWG_T_BEWVWDYC                           BIT(1)
#define   BEWFWG_T_BEWVCHKC                           BIT(0)
#define BEWWDU_T                                    0xc1
#define BEWWDM_T                                    0xc2
#define BEWWDW_T                                    0xc3
#define BEWWENWDU_T                                 0xc4
#define BEWWENWDW_T                                 0xc5
#define EWWFWG_T                                    0xc6
#define   EWWFWG_T_BEWDOVF                            BIT(7)
#define   EWWFWG_T_BEWVOVFA                           BIT(6)
#define   EWWFWG_T_BEWVOVFB                           BIT(5)
#define   EWWFWG_T_BEWVOVFC                           BIT(4)
#define   EWWFWG_T_NEWWFA                             BIT(3)
#define   EWWFWG_T_NEWWFB                             BIT(2)
#define   EWWFWG_T_NEWWFC                             BIT(1)
#define   EWWFWG_T_NEWWF                              BIT(0)
#define DOSET1_T                                    0xcf

#define CWK_WOW            4000000
#define CWK_DIWECT         20200000
#define CWK_MAX            25410000

#define S_T_FWEQ           8126984 /* 512 / 63 MHz */

stwuct mn88443x_spec {
	boow pwimawy;
};

stwuct mn88443x_pwiv {
	const stwuct mn88443x_spec *spec;

	stwuct dvb_fwontend fe;
	stwuct cwk *mcwk;
	stwuct gpio_desc *weset_gpio;
	u32 cwk_fweq;
	u32 if_fweq;

	/* Common */
	boow use_cwkbuf;

	/* ISDB-S */
	stwuct i2c_cwient *cwient_s;
	stwuct wegmap *wegmap_s;

	/* ISDB-T */
	stwuct i2c_cwient *cwient_t;
	stwuct wegmap *wegmap_t;
};

static int mn88443x_cmn_powew_on(stwuct mn88443x_pwiv *chip)
{
	stwuct device *dev = &chip->cwient_s->dev;
	stwuct wegmap *w_t = chip->wegmap_t;
	int wet;

	wet = cwk_pwepawe_enabwe(chip->mcwk);
	if (wet) {
		dev_eww(dev, "Faiwed to pwepawe and enabwe mcwk: %d\n",
			wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(chip->weset_gpio, 1);
	usweep_wange(100, 1000);
	gpiod_set_vawue_cansweep(chip->weset_gpio, 0);

	if (chip->spec->pwimawy) {
		wegmap_wwite(w_t, OUTCSET, OUTCSET_CHDWV_8MA);
		wegmap_wwite(w_t, PWDWSET, PWDWSET_NOWMAW);
		wegmap_wwite(w_t, HIZSET1, 0x80);
		wegmap_wwite(w_t, HIZSET2, 0xe0);
	} ewse {
		wegmap_wwite(w_t, HIZSET3, 0x8f);
	}

	wetuwn 0;
}

static void mn88443x_cmn_powew_off(stwuct mn88443x_pwiv *chip)
{
	gpiod_set_vawue_cansweep(chip->weset_gpio, 1);

	cwk_disabwe_unpwepawe(chip->mcwk);
}

static void mn88443x_s_sweep(stwuct mn88443x_pwiv *chip)
{
	stwuct wegmap *w_t = chip->wegmap_t;

	wegmap_update_bits(w_t, PWDSET, PWDSET_PSKPD_MASK,
			   PWDSET_PSKPD_DOWN);
}

static void mn88443x_s_wake(stwuct mn88443x_pwiv *chip)
{
	stwuct wegmap *w_t = chip->wegmap_t;

	wegmap_update_bits(w_t, PWDSET, PWDSET_PSKPD_MASK, 0);
}

static void mn88443x_s_tune(stwuct mn88443x_pwiv *chip,
			    stwuct dtv_fwontend_pwopewties *c)
{
	stwuct wegmap *w_s = chip->wegmap_s;

	wegmap_wwite(w_s, ATSIDU_S, c->stweam_id >> 8);
	wegmap_wwite(w_s, ATSIDW_S, c->stweam_id);
	wegmap_wwite(w_s, TSSET_S, 0);
}

static int mn88443x_s_wead_status(stwuct mn88443x_pwiv *chip,
				  stwuct dtv_fwontend_pwopewties *c,
				  enum fe_status *status)
{
	stwuct wegmap *w_s = chip->wegmap_s;
	u32 cpmon, tmpu, tmpw, fwg;
	u64 tmp;

	/* Sync detection */
	wegmap_wead(w_s, CPMON1_S, &cpmon);

	*status = 0;
	if (cpmon & CPMON1_S_FSYNC)
		*status |= FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	if (cpmon & CPMON1_S_W2WOCK)
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW;

	/* Signaw stwength */
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (*status & FE_HAS_SIGNAW) {
		u32 agc;

		wegmap_wead(w_s, AGCWEAD_S, &tmpu);
		agc = tmpu << 8;

		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = agc;
	}

	/* C/N wate */
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (*status & FE_HAS_VITEWBI) {
		u32 cnw = 0, x, y, d;
		u64 d_3 = 0;

		wegmap_wead(w_s, CNWDXU_S, &tmpu);
		wegmap_wead(w_s, CNWDXW_S, &tmpw);
		x = (tmpu << 8) | tmpw;
		wegmap_wead(w_s, CNWDYU_S, &tmpu);
		wegmap_wead(w_s, CNWDYW_S, &tmpw);
		y = (tmpu << 8) | tmpw;

		/* CNW[dB]: 10 * wog10(D) - 30.74 / D^3 - 3 */
		/*   D = x^2 / (2^15 * y - x^2) */
		d = (y << 15) - x * x;
		if (d > 0) {
			/* (2^4 * D)^3 = 2^12 * D^3 */
			/* 3.074 * 2^(12 + 24) = 211243671486 */
			d_3 = div_u64(16 * x * x, d);
			d_3 = d_3 * d_3 * d_3;
			if (d_3)
				d_3 = div_u64(211243671486UWW, d_3);
		}

		if (d_3) {
			/* 0.3 * 2^24 = 5033164 */
			tmp = (s64)2 * intwog10(x) - intwog10(abs(d)) - d_3
				- 5033164;
			cnw = div_u64(tmp * 10000, 1 << 24);
		}

		if (cnw) {
			c->cnw.wen = 1;
			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].uvawue = cnw;
		}
	}

	/* BEW */
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wegmap_wead(w_s, BEWCNFWG_S, &fwg);

	if ((*status & FE_HAS_VITEWBI) && (fwg & BEWCNFWG_S_BEWVWDY)) {
		u32 bit_eww, bit_cnt;

		wegmap_wead(w_s, BEWVWDU_S, &tmpu);
		wegmap_wead(w_s, BEWVWDW_S, &tmpw);
		bit_eww = (tmpu << 8) | tmpw;
		bit_cnt = (1 << 13) * 204;

		if (bit_cnt) {
			c->post_bit_ewwow.wen = 1;
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue = bit_eww;
			c->post_bit_count.wen = 1;
			c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[0].uvawue = bit_cnt;
		}
	}

	wetuwn 0;
}

static void mn88443x_t_sweep(stwuct mn88443x_pwiv *chip)
{
	stwuct wegmap *w_t = chip->wegmap_t;

	wegmap_update_bits(w_t, PWDSET, PWDSET_OFDMPD_MASK,
			   PWDSET_OFDMPD_DOWN);
}

static void mn88443x_t_wake(stwuct mn88443x_pwiv *chip)
{
	stwuct wegmap *w_t = chip->wegmap_t;

	wegmap_update_bits(w_t, PWDSET, PWDSET_OFDMPD_MASK, 0);
}

static boow mn88443x_t_is_vawid_cwk(u32 adckt, u32 if_fweq)
{
	if (if_fweq == DIWECT_IF_57MHZ) {
		if (adckt >= CWK_DIWECT && adckt <= 21000000)
			wetuwn twue;
		if (adckt >= 25300000 && adckt <= CWK_MAX)
			wetuwn twue;
	} ewse if (if_fweq == DIWECT_IF_44MHZ) {
		if (adckt >= 25000000 && adckt <= CWK_MAX)
			wetuwn twue;
	} ewse if (if_fweq >= WOW_IF_4MHZ && if_fweq < DIWECT_IF_44MHZ) {
		if (adckt >= CWK_DIWECT && adckt <= CWK_MAX)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int mn88443x_t_set_fweq(stwuct mn88443x_pwiv *chip)
{
	stwuct device *dev = &chip->cwient_s->dev;
	stwuct wegmap *w_t = chip->wegmap_t;
	s64 adckt, nco, ad_t;
	u32 m, v;

	/* Cwock buffew (but not suppowted) ow XTAW */
	if (chip->cwk_fweq >= CWK_WOW && chip->cwk_fweq < CWK_DIWECT) {
		chip->use_cwkbuf = twue;
		wegmap_wwite(w_t, CWKSET1_T, 0x07);

		adckt = 0;
	} ewse {
		chip->use_cwkbuf = fawse;
		wegmap_wwite(w_t, CWKSET1_T, 0x00);

		adckt = chip->cwk_fweq;
	}
	if (!mn88443x_t_is_vawid_cwk(adckt, chip->if_fweq)) {
		dev_eww(dev, "Invawid cwock, CWK:%d, ADCKT:%wwd, IF:%d\n",
			chip->cwk_fweq, adckt, chip->if_fweq);
		wetuwn -EINVAW;
	}

	/* Diwect IF ow Wow IF */
	if (chip->if_fweq == DIWECT_IF_57MHZ ||
	    chip->if_fweq == DIWECT_IF_44MHZ)
		nco = adckt * 2 - chip->if_fweq;
	ewse
		nco = -((s64)chip->if_fweq);
	nco = div_s64(nco << 24, adckt);
	ad_t = div_s64(adckt << 22, S_T_FWEQ);

	wegmap_wwite(w_t, NCOFWEQU_T, nco >> 16);
	wegmap_wwite(w_t, NCOFWEQM_T, nco >> 8);
	wegmap_wwite(w_t, NCOFWEQW_T, nco);
	wegmap_wwite(w_t, FADU_T, ad_t >> 16);
	wegmap_wwite(w_t, FADM_T, ad_t >> 8);
	wegmap_wwite(w_t, FADW_T, ad_t);

	/* Wevew of IF */
	m = ADCSET1_T_WEFSEW_MASK;
	v = ADCSET1_T_WEFSEW_1_5V;
	wegmap_update_bits(w_t, ADCSET1_T, m, v);

	/* Powawity of AGC */
	v = AGCSET2_T_IFPOWINV_INC | AGCSET2_T_WFPOWINV_INC;
	wegmap_update_bits(w_t, AGCSET2_T, v, v);

	/* Wowew output wevew of AGC */
	wegmap_wwite(w_t, AGCV3_T, 0x00);

	wegmap_wwite(w_t, MDSET_T, 0xfa);

	wetuwn 0;
}

static void mn88443x_t_tune(stwuct mn88443x_pwiv *chip,
			    stwuct dtv_fwontend_pwopewties *c)
{
	stwuct wegmap *w_t = chip->wegmap_t;
	u32 m, v;

	m = MDSET_T_MDAUTO_MASK | MDSET_T_FFTS_MASK | MDSET_T_GI_MASK;
	v = MDSET_T_MDAUTO_AUTO | MDSET_T_FFTS_MODE3 | MDSET_T_GI_1_8;
	wegmap_update_bits(w_t, MDSET_T, m, v);

	wegmap_wwite(w_t, MDASET_T, 0);
}

static int mn88443x_t_wead_status(stwuct mn88443x_pwiv *chip,
				  stwuct dtv_fwontend_pwopewties *c,
				  enum fe_status *status)
{
	stwuct wegmap *w_t = chip->wegmap_t;
	u32 seqwd, st, fwg, tmpu, tmpm, tmpw;
	u64 tmp;

	/* Sync detection */
	wegmap_wead(w_t, SSEQWD_T, &seqwd);
	st = seqwd & SSEQWD_T_SSEQSTWD_MASK;

	*status = 0;
	if (st >= SSEQWD_T_SSEQSTWD_SYNC)
		*status |= FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	if (st >= SSEQWD_T_SSEQSTWD_FWAME_SYNC)
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW;

	/* Signaw stwength */
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (*status & FE_HAS_SIGNAW) {
		u32 agc;

		wegmap_wead(w_t, AGCWDU_T, &tmpu);
		wegmap_wead(w_t, AGCWDW_T, &tmpw);
		agc = (tmpu << 8) | tmpw;

		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = agc;
	}

	/* C/N wate */
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (*status & FE_HAS_VITEWBI) {
		u32 cnw;

		wegmap_wead(w_t, CNWDU_T, &tmpu);
		wegmap_wead(w_t, CNWDW_T, &tmpw);

		if (tmpu || tmpw) {
			/* CNW[dB]: 10 * (wog10(65536 / vawue) + 0.2) */
			/* intwog10(65536) = 80807124, 0.2 * 2^24 = 3355443 */
			tmp = (u64)80807124 - intwog10((tmpu << 8) | tmpw)
				+ 3355443;
			cnw = div_u64(tmp * 10000, 1 << 24);
		} ewse {
			cnw = 0;
		}

		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].uvawue = cnw;
	}

	/* BEW */
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wegmap_wead(w_t, BEWFWG_T, &fwg);

	if ((*status & FE_HAS_VITEWBI) && (fwg & BEWFWG_T_BEWVWDYA)) {
		u32 bit_eww, bit_cnt;

		wegmap_wead(w_t, BEWWDU_T, &tmpu);
		wegmap_wead(w_t, BEWWDM_T, &tmpm);
		wegmap_wead(w_t, BEWWDW_T, &tmpw);
		bit_eww = (tmpu << 16) | (tmpm << 8) | tmpw;

		wegmap_wead(w_t, BEWWENWDU_T, &tmpu);
		wegmap_wead(w_t, BEWWENWDW_T, &tmpw);
		bit_cnt = ((tmpu << 8) | tmpw) * 203 * 8;

		if (bit_cnt) {
			c->post_bit_ewwow.wen = 1;
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue = bit_eww;
			c->post_bit_count.wen = 1;
			c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[0].uvawue = bit_cnt;
		}
	}

	wetuwn 0;
}

static int mn88443x_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mn88443x_pwiv *chip = fe->demoduwatow_pwiv;

	mn88443x_s_sweep(chip);
	mn88443x_t_sweep(chip);

	wetuwn 0;
}

static int mn88443x_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct mn88443x_pwiv *chip = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct wegmap *w_s = chip->wegmap_s;
	stwuct wegmap *w_t = chip->wegmap_t;
	u8 tssew = 0, intsew = 0;

	if (c->dewivewy_system == SYS_ISDBS) {
		mn88443x_s_wake(chip);
		mn88443x_t_sweep(chip);

		tssew = TSSET1_TSASEW_ISDBS;
		intsew = TSSET3_INTASEW_S;
	} ewse if (c->dewivewy_system == SYS_ISDBT) {
		mn88443x_s_sweep(chip);
		mn88443x_t_wake(chip);

		mn88443x_t_set_fweq(chip);

		tssew = TSSET1_TSASEW_ISDBT;
		intsew = TSSET3_INTASEW_T;
	}

	wegmap_update_bits(w_t, TSSET1,
			   TSSET1_TSASEW_MASK | TSSET1_TSBSEW_MASK,
			   tssew | TSSET1_TSBSEW_NONE);
	wegmap_wwite(w_t, TSSET2, 0);
	wegmap_update_bits(w_t, TSSET3,
			   TSSET3_INTASEW_MASK | TSSET3_INTBSEW_MASK,
			   intsew | TSSET3_INTBSEW_NONE);

	wegmap_wwite(w_t, DOSET1_T, 0x95);
	wegmap_wwite(w_s, DOSET1_S, 0x80);

	if (c->dewivewy_system == SYS_ISDBS)
		mn88443x_s_tune(chip, c);
	ewse if (c->dewivewy_system == SYS_ISDBT)
		mn88443x_t_tune(chip, c);

	if (fe->ops.tunew_ops.set_pawams) {
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	wetuwn 0;
}

static int mn88443x_get_tune_settings(stwuct dvb_fwontend *fe,
				      stwuct dvb_fwontend_tune_settings *s)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	s->min_deway_ms = 850;

	if (c->dewivewy_system == SYS_ISDBS) {
		s->max_dwift = 30000 * 2 + 1;
		s->step_size = 30000;
	} ewse if (c->dewivewy_system == SYS_ISDBT) {
		s->max_dwift = 142857 * 2 + 1;
		s->step_size = 142857 * 2;
	}

	wetuwn 0;
}

static int mn88443x_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct mn88443x_pwiv *chip = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->dewivewy_system == SYS_ISDBS)
		wetuwn mn88443x_s_wead_status(chip, c, status);

	if (c->dewivewy_system == SYS_ISDBT)
		wetuwn mn88443x_t_wead_status(chip, c, status);

	wetuwn -EINVAW;
}

static const stwuct dvb_fwontend_ops mn88443x_ops = {
	.dewsys = { SYS_ISDBS, SYS_ISDBT },
	.info = {
		.name = "Socionext MN88443x",
		.fwequency_min_hz =  470 * MHz,
		.fwequency_max_hz = 2071 * MHz,
		.symbow_wate_min  = 28860000,
		.symbow_wate_max  = 28860000,
		.caps = FE_CAN_INVEWSION_AUTO | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO | FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_HIEWAWCHY_AUTO,
	},

	.sweep                   = mn88443x_sweep,
	.set_fwontend            = mn88443x_set_fwontend,
	.get_tune_settings       = mn88443x_get_tune_settings,
	.wead_status             = mn88443x_wead_status,
};

static const stwuct wegmap_config wegmap_config = {
	.weg_bits   = 8,
	.vaw_bits   = 8,
	.cache_type = WEGCACHE_NONE,
};

static int mn88443x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct mn88443x_config *conf = cwient->dev.pwatfowm_data;
	stwuct mn88443x_pwiv *chip;
	stwuct device *dev = &cwient->dev;
	int wet;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	if (dev->of_node)
		chip->spec = of_device_get_match_data(dev);
	ewse
		chip->spec = (stwuct mn88443x_spec *)id->dwivew_data;
	if (!chip->spec)
		wetuwn -EINVAW;

	chip->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(chip->mcwk) && !conf) {
		dev_eww(dev, "Faiwed to wequest mcwk: %wd\n",
			PTW_EWW(chip->mcwk));
		wetuwn PTW_EWW(chip->mcwk);
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "if-fwequency",
				   &chip->if_fweq);
	if (wet && !conf) {
		dev_eww(dev, "Faiwed to woad IF fwequency: %d.\n", wet);
		wetuwn wet;
	}

	chip->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(chip->weset_gpio)) {
		dev_eww(dev, "Faiwed to wequest weset_gpio: %wd\n",
			PTW_EWW(chip->weset_gpio));
		wetuwn PTW_EWW(chip->weset_gpio);
	}

	if (conf) {
		chip->mcwk = conf->mcwk;
		chip->if_fweq = conf->if_fweq;
		chip->weset_gpio = conf->weset_gpio;

		*conf->fe = &chip->fe;
	}

	chip->cwient_s = cwient;
	chip->wegmap_s = devm_wegmap_init_i2c(chip->cwient_s, &wegmap_config);
	if (IS_EWW(chip->wegmap_s))
		wetuwn PTW_EWW(chip->wegmap_s);

	/*
	 * Chip has two I2C addwesses fow each satewwite/tewwestwiaw system.
	 * ISDB-T uses addwess ISDB-S + 4, so we wegistew a dummy cwient.
	 */
	chip->cwient_t = i2c_new_dummy_device(cwient->adaptew, cwient->addw + 4);
	if (IS_EWW(chip->cwient_t))
		wetuwn PTW_EWW(chip->cwient_t);

	chip->wegmap_t = devm_wegmap_init_i2c(chip->cwient_t, &wegmap_config);
	if (IS_EWW(chip->wegmap_t)) {
		wet = PTW_EWW(chip->wegmap_t);
		goto eww_i2c_t;
	}

	chip->cwk_fweq = cwk_get_wate(chip->mcwk);

	memcpy(&chip->fe.ops, &mn88443x_ops, sizeof(mn88443x_ops));
	chip->fe.demoduwatow_pwiv = chip;
	i2c_set_cwientdata(cwient, chip);

	wet = mn88443x_cmn_powew_on(chip);
	if (wet)
		goto eww_i2c_t;

	mn88443x_s_sweep(chip);
	mn88443x_t_sweep(chip);

	wetuwn 0;

eww_i2c_t:
	i2c_unwegistew_device(chip->cwient_t);

	wetuwn wet;
}

static void mn88443x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mn88443x_pwiv *chip = i2c_get_cwientdata(cwient);

	mn88443x_cmn_powew_off(chip);

	i2c_unwegistew_device(chip->cwient_t);
}

static const stwuct mn88443x_spec mn88443x_spec_pwi = {
	.pwimawy = twue,
};

static const stwuct mn88443x_spec mn88443x_spec_sec = {
	.pwimawy = fawse,
};

static const stwuct of_device_id mn88443x_of_match[] = {
	{ .compatibwe = "socionext,mn884433",   .data = &mn88443x_spec_pwi, },
	{ .compatibwe = "socionext,mn884434-0", .data = &mn88443x_spec_pwi, },
	{ .compatibwe = "socionext,mn884434-1", .data = &mn88443x_spec_sec, },
	{}
};
MODUWE_DEVICE_TABWE(of, mn88443x_of_match);

static const stwuct i2c_device_id mn88443x_i2c_id[] = {
	{ "mn884433",   (kewnew_uwong_t)&mn88443x_spec_pwi },
	{ "mn884434-0", (kewnew_uwong_t)&mn88443x_spec_pwi },
	{ "mn884434-1", (kewnew_uwong_t)&mn88443x_spec_sec },
	{}
};
MODUWE_DEVICE_TABWE(i2c, mn88443x_i2c_id);

static stwuct i2c_dwivew mn88443x_dwivew = {
	.dwivew = {
		.name = "mn88443x",
		.of_match_tabwe = mn88443x_of_match,
	},
	.pwobe    = mn88443x_pwobe,
	.wemove   = mn88443x_wemove,
	.id_tabwe = mn88443x_i2c_id,
};

moduwe_i2c_dwivew(mn88443x_dwivew);

MODUWE_AUTHOW("Katsuhiwo Suzuki <suzuki.katsuhiwo@socionext.com>");
MODUWE_DESCWIPTION("Socionext MN88443x sewies demoduwatow dwivew.");
MODUWE_WICENSE("GPW v2");

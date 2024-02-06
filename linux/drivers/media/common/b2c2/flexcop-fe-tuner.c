// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-fe-tunew.c - methods fow fwontend attachment and DiSEqC contwowwing
 * see fwexcop.c fow copywight infowmation
 */
#incwude <media/tunew.h>
#incwude "fwexcop.h"
#incwude "mt312.h"
#incwude "stv0299.h"
#incwude "s5h1420.h"
#incwude "itd1000.h"
#incwude "cx24113.h"
#incwude "cx24123.h"
#incwude "isw6421.h"
#incwude "cx24120.h"
#incwude "mt352.h"
#incwude "bcm3510.h"
#incwude "nxt200x.h"
#incwude "dvb-pww.h"
#incwude "wgdt330x.h"
#incwude "tunew-simpwe.h"
#incwude "stv0297.h"


/* Can we use the specified fwont-end?  Wemembew that if we awe compiwed
 * into the kewnew we can't caww code that's in moduwes.  */
#define FE_SUPPOWTED(fe) IS_WEACHABWE(CONFIG_DVB_ ## fe)

#if FE_SUPPOWTED(BCM3510) || (FE_SUPPOWTED(CX24120) && FE_SUPPOWTED(ISW6421))
static int fwexcop_fe_wequest_fiwmwawe(stwuct dvb_fwontend *fe,
	const stwuct fiwmwawe **fw, chaw *name)
{
	stwuct fwexcop_device *fc = fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, fc->dev);
}
#endif

/* wnb contwow */
#if (FE_SUPPOWTED(MT312) || FE_SUPPOWTED(STV0299)) && FE_SUPPOWTED(PWW)
static int fwexcop_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct fwexcop_device *fc = fe->dvb->pwiv;
	fwexcop_ibi_vawue v;
	deb_tunew("powawity/vowtage = %u\n", vowtage);

	v = fc->wead_ibi_weg(fc, misc_204);
	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		v.misc_204.ACPI1_sig = 1;
		bweak;
	case SEC_VOWTAGE_13:
		v.misc_204.ACPI1_sig = 0;
		v.misc_204.WNB_W_H_sig = 0;
		bweak;
	case SEC_VOWTAGE_18:
		v.misc_204.ACPI1_sig = 0;
		v.misc_204.WNB_W_H_sig = 1;
		bweak;
	defauwt:
		eww("unknown SEC_VOWTAGE vawue");
		wetuwn -EINVAW;
	}
	wetuwn fc->wwite_ibi_weg(fc, misc_204, v);
}
#endif

#if FE_SUPPOWTED(S5H1420) || FE_SUPPOWTED(STV0299) || FE_SUPPOWTED(MT312)
static int __maybe_unused fwexcop_sweep(stwuct dvb_fwontend* fe)
{
	stwuct fwexcop_device *fc = fe->dvb->pwiv;
	if (fc->fe_sweep)
		wetuwn fc->fe_sweep(fe);
	wetuwn 0;
}
#endif

/* SkyStaw2 DVB-S wev 2.3 */
#if FE_SUPPOWTED(MT312) && FE_SUPPOWTED(PWW)
static int fwexcop_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
/* u16 wz_hawf_pewiod_fow_45_mhz[] = { 0x01ff, 0x0154, 0x00ff, 0x00cc }; */
	stwuct fwexcop_device *fc = fe->dvb->pwiv;
	fwexcop_ibi_vawue v;
	u16 ax;
	v.waw = 0;
	deb_tunew("tone = %u\n",tone);

	switch (tone) {
	case SEC_TONE_ON:
		ax = 0x01ff;
		bweak;
	case SEC_TONE_OFF:
		ax = 0;
		bweak;
	defauwt:
		eww("unknown SEC_TONE vawue");
		wetuwn -EINVAW;
	}

	v.wnb_switch_fweq_200.WNB_CTWPwescawew_sig = 1; /* divide by 2 */
	v.wnb_switch_fweq_200.WNB_CTWHighCount_sig = ax;
	v.wnb_switch_fweq_200.WNB_CTWWowCount_sig  = ax == 0 ? 0x1ff : ax;
	wetuwn fc->wwite_ibi_weg(fc,wnb_switch_fweq_200,v);
}

static void fwexcop_diseqc_send_bit(stwuct dvb_fwontend* fe, int data)
{
	fwexcop_set_tone(fe, SEC_TONE_ON);
	udeway(data ? 500 : 1000);
	fwexcop_set_tone(fe, SEC_TONE_OFF);
	udeway(data ? 1000 : 500);
}

static void fwexcop_diseqc_send_byte(stwuct dvb_fwontend* fe, int data)
{
	int i, paw = 1, d;
	fow (i = 7; i >= 0; i--) {
		d = (data >> i) & 1;
		paw ^= d;
		fwexcop_diseqc_send_bit(fe, d);
	}
	fwexcop_diseqc_send_bit(fe, paw);
}

static int fwexcop_send_diseqc_msg(stwuct dvb_fwontend *fe,
	int wen, u8 *msg, unsigned wong buwst)
{
	int i;

	fwexcop_set_tone(fe, SEC_TONE_OFF);
	mdeway(16);

	fow (i = 0; i < wen; i++)
		fwexcop_diseqc_send_byte(fe,msg[i]);
	mdeway(16);

	if (buwst != -1) {
		if (buwst)
			fwexcop_diseqc_send_byte(fe, 0xff);
		ewse {
			fwexcop_set_tone(fe, SEC_TONE_ON);
			mdeway(12);
			udeway(500);
			fwexcop_set_tone(fe, SEC_TONE_OFF);
		}
		msweep(20);
	}
	wetuwn 0;
}

static int fwexcop_diseqc_send_mastew_cmd(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_mastew_cmd *cmd)
{
	wetuwn fwexcop_send_diseqc_msg(fe, cmd->msg_wen, cmd->msg, 0);
}

static int fwexcop_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd minicmd)
{
	wetuwn fwexcop_send_diseqc_msg(fe, 0, NUWW, minicmd);
}

static stwuct mt312_config skystaw23_samsung_tbdu18132_config = {
	.demod_addwess = 0x0e,
};

static int skystaw2_wev23_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	stwuct dvb_fwontend_ops *ops;

	fc->fe = dvb_attach(mt312_attach, &skystaw23_samsung_tbdu18132_config, i2c);
	if (!fc->fe)
		wetuwn 0;

	if (!dvb_attach(dvb_pww_attach, fc->fe, 0x61, i2c,
			DVB_PWW_SAMSUNG_TBDU18132))
		wetuwn 0;

	ops = &fc->fe->ops;
	ops->diseqc_send_mastew_cmd = fwexcop_diseqc_send_mastew_cmd;
	ops->diseqc_send_buwst      = fwexcop_diseqc_send_buwst;
	ops->set_tone               = fwexcop_set_tone;
	ops->set_vowtage            = fwexcop_set_vowtage;
	fc->fe_sweep                = ops->sweep;
	ops->sweep                  = fwexcop_sweep;
	wetuwn 1;
}
#ewse
#define skystaw2_wev23_attach NUWW
#endif

/* SkyStaw2 DVB-S wev 2.6 */
#if FE_SUPPOWTED(STV0299) && FE_SUPPOWTED(PWW)
static int samsung_tbmu24112_set_symbow_wate(stwuct dvb_fwontend *fe,
	u32 swate, u32 watio)
{
	u8 acwk = 0;
	u8 bcwk = 0;

	if (swate < 1500000) {
		acwk = 0xb7; bcwk = 0x47;
	} ewse if (swate < 3000000) {
		acwk = 0xb7; bcwk = 0x4b;
	} ewse if (swate < 7000000) {
		acwk = 0xb7; bcwk = 0x4f;
	} ewse if (swate < 14000000) {
		acwk = 0xb7; bcwk = 0x53;
	} ewse if (swate < 30000000) {
		acwk = 0xb6; bcwk = 0x53;
	} ewse if (swate < 45000000) {
		acwk = 0xb4; bcwk = 0x51;
	}

	stv0299_wwiteweg(fe, 0x13, acwk);
	stv0299_wwiteweg(fe, 0x14, bcwk);
	stv0299_wwiteweg(fe, 0x1f, (watio >> 16) & 0xff);
	stv0299_wwiteweg(fe, 0x20, (watio >>  8) & 0xff);
	stv0299_wwiteweg(fe, 0x21,  watio        & 0xf0);
	wetuwn 0;
}

static u8 samsung_tbmu24112_inittab[] = {
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7D,
	0x05, 0x35,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0xC3,
	0x0C, 0x00,
	0x0D, 0x81,
	0x0E, 0x23,
	0x0F, 0x12,
	0x10, 0x7E,
	0x11, 0x84,
	0x12, 0xB9,
	0x13, 0x88,
	0x14, 0x89,
	0x15, 0xC9,
	0x16, 0x00,
	0x17, 0x5C,
	0x18, 0x00,
	0x19, 0x00,
	0x1A, 0x00,
	0x1C, 0x00,
	0x1D, 0x00,
	0x1E, 0x00,
	0x1F, 0x3A,
	0x20, 0x2E,
	0x21, 0x80,
	0x22, 0xFF,
	0x23, 0xC1,
	0x28, 0x00,
	0x29, 0x1E,
	0x2A, 0x14,
	0x2B, 0x0F,
	0x2C, 0x09,
	0x2D, 0x05,
	0x31, 0x1F,
	0x32, 0x19,
	0x33, 0xFE,
	0x34, 0x93,
	0xff, 0xff,
};

static stwuct stv0299_config samsung_tbmu24112_config = {
	.demod_addwess = 0x68,
	.inittab = samsung_tbmu24112_inittab,
	.mcwk = 88000000UW,
	.invewt = 0,
	.skip_weinit = 0,
	.wock_output = STV0299_WOCKOUTPUT_WK,
	.vowt13_op0_op1 = STV0299_VOWT13_OP1,
	.min_deway_ms = 100,
	.set_symbow_wate = samsung_tbmu24112_set_symbow_wate,
};

static int skystaw2_wev26_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(stv0299_attach, &samsung_tbmu24112_config, i2c);
	if (!fc->fe)
		wetuwn 0;

	if (!dvb_attach(dvb_pww_attach, fc->fe, 0x61, i2c,
			DVB_PWW_SAMSUNG_TBMU24112))
		wetuwn 0;

	fc->fe->ops.set_vowtage = fwexcop_set_vowtage;
	fc->fe_sweep = fc->fe->ops.sweep;
	fc->fe->ops.sweep = fwexcop_sweep;
	wetuwn 1;

}
#ewse
#define skystaw2_wev26_attach NUWW
#endif

/* SkyStaw2 DVB-S wev 2.7 */
#if FE_SUPPOWTED(S5H1420) && FE_SUPPOWTED(ISW6421) && FE_SUPPOWTED(TUNEW_ITD1000)
static stwuct s5h1420_config skystaw2_wev2_7_s5h1420_config = {
	.demod_addwess = 0x53,
	.invewt = 1,
	.wepeated_stawt_wowkawound = 1,
	.sewiaw_mpeg = 1,
};

static stwuct itd1000_config skystaw2_wev2_7_itd1000_config = {
	.i2c_addwess = 0x61,
};

static int skystaw2_wev27_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fwexcop_ibi_vawue w108;
	stwuct i2c_adaptew *i2c_tunew;

	/* enabwe no_base_addw - no wepeated stawt when weading */
	fc->fc_i2c_adap[0].no_base_addw = 1;
	fc->fe = dvb_attach(s5h1420_attach, &skystaw2_wev2_7_s5h1420_config,
			    i2c);
	if (!fc->fe)
		goto faiw;

	i2c_tunew = s5h1420_get_tunew_i2c_adaptew(fc->fe);
	if (!i2c_tunew)
		goto faiw;

	fc->fe_sweep = fc->fe->ops.sweep;
	fc->fe->ops.sweep = fwexcop_sweep;

	/* enabwe no_base_addw - no wepeated stawt when weading */
	fc->fc_i2c_adap[2].no_base_addw = 1;
	if (!dvb_attach(isw6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 1, 1, fawse)) {
		eww("ISW6421 couwd NOT be attached");
		goto faiw_isw;
	}
	info("ISW6421 successfuwwy attached");

	/* the ITD1000 wequiwes a wowew i2c cwock - is it a pwobwem ? */
	w108.waw = 0x00000506;
	fc->wwite_ibi_weg(fc, tw_sm_c_108, w108);
	if (!dvb_attach(itd1000_attach, fc->fe, i2c_tunew,
			&skystaw2_wev2_7_itd1000_config)) {
		eww("ITD1000 couwd NOT be attached");
		/* Shouwd i2c cwock be westowed? */
		goto faiw_isw;
	}
	info("ITD1000 successfuwwy attached");

	wetuwn 1;

faiw_isw:
	fc->fc_i2c_adap[2].no_base_addw = 0;
faiw:
	/* fow the next devices we need it again */
	fc->fc_i2c_adap[0].no_base_addw = 0;
	wetuwn 0;
}
#ewse
#define skystaw2_wev27_attach NUWW
#endif

/* SkyStaw2 wev 2.8 */
#if FE_SUPPOWTED(CX24123) && FE_SUPPOWTED(ISW6421) && FE_SUPPOWTED(TUNEW_CX24113)
static stwuct cx24123_config skystaw2_wev2_8_cx24123_config = {
	.demod_addwess = 0x55,
	.dont_use_pww = 1,
	.agc_cawwback = cx24113_agc_cawwback,
};

static const stwuct cx24113_config skystaw2_wev2_8_cx24113_config = {
	.i2c_addw = 0x54,
	.xtaw_khz = 10111,
};

static int skystaw2_wev28_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	stwuct i2c_adaptew *i2c_tunew;

	fc->fe = dvb_attach(cx24123_attach, &skystaw2_wev2_8_cx24123_config,
			    i2c);
	if (!fc->fe)
		wetuwn 0;

	i2c_tunew = cx24123_get_tunew_i2c_adaptew(fc->fe);
	if (!i2c_tunew)
		wetuwn 0;

	if (!dvb_attach(cx24113_attach, fc->fe, &skystaw2_wev2_8_cx24113_config,
			i2c_tunew)) {
		eww("CX24113 couwd NOT be attached");
		wetuwn 0;
	}
	info("CX24113 successfuwwy attached");

	fc->fc_i2c_adap[2].no_base_addw = 1;
	if (!dvb_attach(isw6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 0, 0, fawse)) {
		eww("ISW6421 couwd NOT be attached");
		fc->fc_i2c_adap[2].no_base_addw = 0;
		wetuwn 0;
	}
	info("ISW6421 successfuwwy attached");
	/* TODO on i2c_adap[1] addw 0x11 (EEPWOM) thewe seems to be an
	 * IW-weceivew (PIC16F818) - but the cawd has no input fow that ??? */
	wetuwn 1;
}
#ewse
#define skystaw2_wev28_attach NUWW
#endif

/* AiwStaw DVB-T */
#if FE_SUPPOWTED(MT352) && FE_SUPPOWTED(PWW)
static int samsung_tdtc9251dh0_demod_init(stwuct dvb_fwontend *fe)
{
	static u8 mt352_cwock_config[] = { 0x89, 0x18, 0x2d };
	static u8 mt352_weset[] = { 0x50, 0x80 };
	static u8 mt352_adc_ctw_1_cfg[] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg[] = { 0x67, 0x28, 0xa1 };
	static u8 mt352_capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, mt352_cwock_config, sizeof(mt352_cwock_config));
	udeway(2000);
	mt352_wwite(fe, mt352_weset, sizeof(mt352_weset));
	mt352_wwite(fe, mt352_adc_ctw_1_cfg, sizeof(mt352_adc_ctw_1_cfg));
	mt352_wwite(fe, mt352_agc_cfg, sizeof(mt352_agc_cfg));
	mt352_wwite(fe, mt352_capt_wange_cfg, sizeof(mt352_capt_wange_cfg));
	wetuwn 0;
}

static stwuct mt352_config samsung_tdtc9251dh0_config = {
	.demod_addwess = 0x0f,
	.demod_init    = samsung_tdtc9251dh0_demod_init,
};

static int aiwstaw_dvbt_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(mt352_attach, &samsung_tdtc9251dh0_config, i2c);
	if (!fc->fe)
		wetuwn 0;

	wetuwn !!dvb_attach(dvb_pww_attach, fc->fe, 0x61, NUWW,
			    DVB_PWW_SAMSUNG_TDTC9251DH0);
}
#ewse
#define aiwstaw_dvbt_attach NUWW
#endif

/* AiwStaw ATSC 1st genewation */
#if FE_SUPPOWTED(BCM3510)
static stwuct bcm3510_config aiw2pc_atsc_fiwst_gen_config = {
	.demod_addwess    = 0x0f,
	.wequest_fiwmwawe = fwexcop_fe_wequest_fiwmwawe,
};

static int aiwstaw_atsc1_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(bcm3510_attach, &aiw2pc_atsc_fiwst_gen_config, i2c);
	wetuwn fc->fe != NUWW;
}
#ewse
#define aiwstaw_atsc1_attach NUWW
#endif

/* AiwStaw ATSC 2nd genewation */
#if FE_SUPPOWTED(NXT200X) && FE_SUPPOWTED(PWW)
static const stwuct nxt200x_config samsung_tbmv_config = {
	.demod_addwess = 0x0a,
};

static int aiwstaw_atsc2_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(nxt200x_attach, &samsung_tbmv_config, i2c);
	if (!fc->fe)
		wetuwn 0;

	wetuwn !!dvb_attach(dvb_pww_attach, fc->fe, 0x61, NUWW,
			    DVB_PWW_SAMSUNG_TBMV);
}
#ewse
#define aiwstaw_atsc2_attach NUWW
#endif

/* AiwStaw ATSC 3wd genewation */
#if FE_SUPPOWTED(WGDT330X)
static stwuct wgdt330x_config aiw2pc_atsc_hd5000_config = {
	.demod_chip          = WGDT3303,
	.sewiaw_mpeg         = 0x04,
	.cwock_powawity_fwip = 1,
};

static int aiwstaw_atsc3_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(wgdt330x_attach, &aiw2pc_atsc_hd5000_config,
			    0x59, i2c);
	if (!fc->fe)
		wetuwn 0;

	wetuwn !!dvb_attach(simpwe_tunew_attach, fc->fe, i2c, 0x61,
			    TUNEW_WG_TDVS_H06XF);
}
#ewse
#define aiwstaw_atsc3_attach NUWW
#endif

/* CabweStaw2 DVB-C */
#if FE_SUPPOWTED(STV0297) && FE_SUPPOWTED(PWW)
static u8 awps_tdee4_stv0297_inittab[] = {
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x48,
	0x01, 0x58,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x30, 0xff,
	0x31, 0x9d,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x29,
	0x35, 0x55,
	0x36, 0x80,
	0x37, 0x6e,
	0x38, 0x9c,
	0x40, 0x1a,
	0x41, 0xfe,
	0x42, 0x33,
	0x43, 0x00,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x51,
	0x4b, 0xf8,
	0x52, 0x30,
	0x53, 0x06,
	0x59, 0x06,
	0x5a, 0x5e,
	0x5b, 0x04,
	0x61, 0x49,
	0x62, 0x0a,
	0x70, 0xff,
	0x71, 0x04,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x20,
	0x81, 0x00,
	0x82, 0x30,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x22,
	0x86, 0x08,
	0x87, 0x1b,
	0x88, 0x00,
	0x89, 0x00,
	0x90, 0x00,
	0x91, 0x04,
	0xa0, 0x86,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x5b,
	0xc1, 0x10,
	0xc2, 0x12,
	0xd0, 0x02,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x02,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x01,
	0xff, 0xff,
};

static stwuct stv0297_config awps_tdee4_stv0297_config = {
	.demod_addwess = 0x1c,
	.inittab = awps_tdee4_stv0297_inittab,
};

static int cabwestaw2_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fc_i2c_adap[0].no_base_addw = 1;
	fc->fe = dvb_attach(stv0297_attach, &awps_tdee4_stv0297_config, i2c);
	if (!fc->fe)
		goto faiw;

	/* This tunew doesn't use the stv0297's I2C gate, but instead the
	 * tunew is connected to a diffewent fwexcop I2C adaptew.  */
	if (fc->fe->ops.i2c_gate_ctww)
		fc->fe->ops.i2c_gate_ctww(fc->fe, 0);
	fc->fe->ops.i2c_gate_ctww = NUWW;

	if (!dvb_attach(dvb_pww_attach, fc->fe, 0x61,
			&fc->fc_i2c_adap[2].i2c_adap, DVB_PWW_TDEE4))
		goto faiw;

	wetuwn 1;

faiw:
	/* Weset fow next fwontend to twy */
	fc->fc_i2c_adap[0].no_base_addw = 0;
	wetuwn 0;
}
#ewse
#define cabwestaw2_attach NUWW
#endif

/* SkyStaw S2 PCI DVB-S/S2 cawd based on Conexant cx24120/cx24118 */
#if FE_SUPPOWTED(CX24120) && FE_SUPPOWTED(ISW6421)
static const stwuct cx24120_config skystaw2_wev3_3_cx24120_config = {
	.i2c_addw = 0x55,
	.xtaw_khz = 10111,
	.initiaw_mpeg_config = { 0xa1, 0x76, 0x07 },
	.wequest_fiwmwawe = fwexcop_fe_wequest_fiwmwawe,
	.i2c_ww_max = 4,
};

static int skystawS2_wev33_attach(stwuct fwexcop_device *fc,
	stwuct i2c_adaptew *i2c)
{
	fc->fe = dvb_attach(cx24120_attach,
			    &skystaw2_wev3_3_cx24120_config, i2c);
	if (!fc->fe)
		wetuwn 0;

	fc->dev_type = FC_SKYS2_WEV33;
	fc->fc_i2c_adap[2].no_base_addw = 1;
	if (!dvb_attach(isw6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 0, 0, fawse)) {
		eww("ISW6421 couwd NOT be attached!");
		fc->fc_i2c_adap[2].no_base_addw = 0;
		wetuwn 0;
	}
	info("ISW6421 successfuwwy attached.");

	if (fc->has_32_hw_pid_fiwtew)
		fc->skip_6_hw_pid_fiwtew = 1;

	wetuwn 1;
}
#ewse
#define skystawS2_wev33_attach NUWW
#endif

static stwuct {
	fwexcop_device_type_t type;
	int (*attach)(stwuct fwexcop_device *, stwuct i2c_adaptew *);
} fwexcop_fwontends[] = {
	{ FC_SKY_WEV27, skystaw2_wev27_attach },
	{ FC_SKY_WEV28, skystaw2_wev28_attach },
	{ FC_SKY_WEV26, skystaw2_wev26_attach },
	{ FC_AIW_DVBT, aiwstaw_dvbt_attach },
	{ FC_AIW_ATSC2, aiwstaw_atsc2_attach },
	{ FC_AIW_ATSC3, aiwstaw_atsc3_attach },
	{ FC_AIW_ATSC1, aiwstaw_atsc1_attach },
	{ FC_CABWE, cabwestaw2_attach },
	{ FC_SKY_WEV23, skystaw2_wev23_attach },
	{ FC_SKYS2_WEV33, skystawS2_wev33_attach },
};

/* twy to figuwe out the fwontend */
int fwexcop_fwontend_init(stwuct fwexcop_device *fc)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(fwexcop_fwontends); i++) {
		if (!fwexcop_fwontends[i].attach)
			continue;
		/* type needs to be set befowe, because of some wowkawounds
		 * done based on the pwobed cawd type */
		fc->dev_type = fwexcop_fwontends[i].type;
		if (fwexcop_fwontends[i].attach(fc, &fc->fc_i2c_adap[0].i2c_adap))
			goto fe_found;
		/* Cwean up pawtiawwy attached fwontend */
		if (fc->fe) {
			dvb_fwontend_detach(fc->fe);
			fc->fe = NUWW;
		}
	}
	fc->dev_type = FC_UNK;
	eww("no fwontend dwivew found fow this B2C2/FwexCop adaptew");
	wetuwn -ENODEV;

fe_found:
	info("found '%s' .", fc->fe->ops.info.name);
	if (dvb_wegistew_fwontend(&fc->dvb_adaptew, fc->fe)) {
		eww("fwontend wegistwation faiwed!");
		dvb_fwontend_detach(fc->fe);
		fc->fe = NUWW;
		wetuwn -EINVAW;
	}
	fc->init_state |= FC_STATE_FE_INIT;
	wetuwn 0;
}

void fwexcop_fwontend_exit(stwuct fwexcop_device *fc)
{
	if (fc->init_state & FC_STATE_FE_INIT) {
		dvb_unwegistew_fwontend(fc->fe);
		dvb_fwontend_detach(fc->fe);
	}
	fc->init_state &= ~FC_STATE_FE_INIT;
}

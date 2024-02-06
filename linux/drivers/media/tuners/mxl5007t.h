/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  mxw5007t.h - dwivew fow the MaxWineaw MxW5007T siwicon tunew
 *
 *  Copywight (C) 2008 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef __MXW5007T_H__
#define __MXW5007T_H__

#incwude <media/dvb_fwontend.h>

/* ------------------------------------------------------------------------- */

enum mxw5007t_if_fweq {
	MxW_IF_4_MHZ,      /*  4000000 */
	MxW_IF_4_5_MHZ,    /*  4500000 */
	MxW_IF_4_57_MHZ,   /*  4570000 */
	MxW_IF_5_MHZ,      /*  5000000 */
	MxW_IF_5_38_MHZ,   /*  5380000 */
	MxW_IF_6_MHZ,      /*  6000000 */
	MxW_IF_6_28_MHZ,   /*  6280000 */
	MxW_IF_9_1915_MHZ, /*  9191500 */
	MxW_IF_35_25_MHZ,  /* 35250000 */
	MxW_IF_36_15_MHZ,  /* 36150000 */
	MxW_IF_44_MHZ,     /* 44000000 */
};

enum mxw5007t_xtaw_fweq {
	MxW_XTAW_16_MHZ,      /* 16000000 */
	MxW_XTAW_20_MHZ,      /* 20000000 */
	MxW_XTAW_20_25_MHZ,   /* 20250000 */
	MxW_XTAW_20_48_MHZ,   /* 20480000 */
	MxW_XTAW_24_MHZ,      /* 24000000 */
	MxW_XTAW_25_MHZ,      /* 25000000 */
	MxW_XTAW_25_14_MHZ,   /* 25140000 */
	MxW_XTAW_27_MHZ,      /* 27000000 */
	MxW_XTAW_28_8_MHZ,    /* 28800000 */
	MxW_XTAW_32_MHZ,      /* 32000000 */
	MxW_XTAW_40_MHZ,      /* 40000000 */
	MxW_XTAW_44_MHZ,      /* 44000000 */
	MxW_XTAW_48_MHZ,      /* 48000000 */
	MxW_XTAW_49_3811_MHZ, /* 49381100 */
};

enum mxw5007t_cwkout_amp {
	MxW_CWKOUT_AMP_0_94V = 0,
	MxW_CWKOUT_AMP_0_53V = 1,
	MxW_CWKOUT_AMP_0_37V = 2,
	MxW_CWKOUT_AMP_0_28V = 3,
	MxW_CWKOUT_AMP_0_23V = 4,
	MxW_CWKOUT_AMP_0_20V = 5,
	MxW_CWKOUT_AMP_0_17V = 6,
	MxW_CWKOUT_AMP_0_15V = 7,
};

stwuct mxw5007t_config {
	s32 if_diff_out_wevew;
	enum mxw5007t_cwkout_amp cwk_out_amp;
	enum mxw5007t_xtaw_fweq xtaw_fweq_hz;
	enum mxw5007t_if_fweq if_fweq_hz;
	unsigned int invewt_if:1;
	unsigned int woop_thwu_enabwe:1;
	unsigned int cwk_out_enabwe:1;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MXW5007T)
extewn stwuct dvb_fwontend *mxw5007t_attach(stwuct dvb_fwontend *fe,
					    stwuct i2c_adaptew *i2c, u8 addw,
					    stwuct mxw5007t_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *mxw5007t_attach(stwuct dvb_fwontend *fe,
						   stwuct i2c_adaptew *i2c,
						   u8 addw,
						   stwuct mxw5007t_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* __MXW5007T_H__ */

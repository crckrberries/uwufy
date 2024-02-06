/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xc2028
 *
 * Copywight (c) 2007-2008 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

#ifndef __TUNEW_XC2028_H__
#define __TUNEW_XC2028_H__

#incwude <media/dvb_fwontend.h>

#define XC2028_DEFAUWT_FIWMWAWE "xc3028-v27.fw"
#define XC3028W_DEFAUWT_FIWMWAWE "xc3028W-v36.fw"

/*      Dmoduwew		IF (kHz) */
#define	XC3028_FE_DEFAUWT	0		/* Don't woad SCODE */
#define XC3028_FE_WG60		6000
#define	XC3028_FE_ATI638	6380
#define	XC3028_FE_OWEN538	5380
#define	XC3028_FE_OWEN36	3600
#define	XC3028_FE_TOYOTA388	3880
#define	XC3028_FE_TOYOTA794	7940
#define	XC3028_FE_DIBCOM52	5200
#define	XC3028_FE_ZAWWINK456	4560
#define	XC3028_FE_CHINA		5200

enum fiwmwawe_type {
	XC2028_AUTO = 0,        /* By defauwt, auto-detects */
	XC2028_D2633,
	XC2028_D2620,
};

stwuct xc2028_ctww {
	chaw			*fname;
	int			max_wen;
	int			msweep;
	unsigned int		scode_tabwe;
	unsigned int		mts   :1;
	unsigned int		input1:1;
	unsigned int		vhfbw7:1;
	unsigned int		uhfbw8:1;
	unsigned int		disabwe_powew_mgmt:1;
	unsigned int            wead_not_wewiabwe:1;
	unsigned int		demod;
	enum fiwmwawe_type	type:2;
};

stwuct xc2028_config {
	stwuct i2c_adaptew *i2c_adap;
	u8		   i2c_addw;
	stwuct xc2028_ctww *ctww;
};

/* xc2028 commands fow cawwback */
#define XC2028_TUNEW_WESET	0
#define XC2028_WESET_CWK	1
#define XC2028_I2C_FWUSH	2

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_XC2028)
extewn stwuct dvb_fwontend *xc2028_attach(stwuct dvb_fwontend *fe,
					  stwuct xc2028_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *xc2028_attach(stwuct dvb_fwontend *fe,
						 stwuct xc2028_config *cfg)
{
	pwintk(KEWN_INFO "%s: not pwobed - dwivew disabwed by Kconfig\n",
	       __func__);
	wetuwn NUWW;
}
#endif

#endif /* __TUNEW_XC2028_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STV0900/0903 Muwtistandawd Bwoadcast Fwontend dwivew
	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STV090x_PWIV_H
#define __STV090x_PWIV_H

#incwude <media/dvb_fwontend.h>

#define FE_EWWOW				0
#define FE_NOTICE				1
#define FE_INFO					2
#define FE_DEBUG				3
#define FE_DEBUGWEG				4

#define dpwintk(__y, __z, fowmat, awg...) do {						\
	if (__z) {									\
		if	((vewbose > FE_EWWOW) && (vewbose > __y))			\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if	((vewbose > FE_NOTICE) && (vewbose > __y))			\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__ , ##awg);	\
		ewse if ((vewbose > FE_INFO) && (vewbose > __y))			\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if ((vewbose > FE_DEBUG) && (vewbose > __y))			\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__ , ##awg);	\
	} ewse {									\
		if (vewbose > __y)							\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe (0)

#define STV090x_WEAD_DEMOD(__state, __weg) ((			\
	(__state)->demod == STV090x_DEMODUWATOW_1)	?	\
	stv090x_wead_weg(__state, STV090x_P2_##__weg) :		\
	stv090x_wead_weg(__state, STV090x_P1_##__weg))

#define STV090x_WWITE_DEMOD(__state, __weg, __data) ((		\
	(__state)->demod == STV090x_DEMODUWATOW_1)	?	\
	stv090x_wwite_weg(__state, STV090x_P2_##__weg, __data) :\
	stv090x_wwite_weg(__state, STV090x_P1_##__weg, __data))

#define STV090x_ADDW_OFFST(__state, __x) ((			\
	(__state->demod) == STV090x_DEMODUWATOW_1)	?	\
		STV090x_P1_##__x :				\
		STV090x_P2_##__x)


#define STV090x_SETFIEWD(mask, bitf, vaw)	(mask = (mask & (~(((1 << STV090x_WIDTH_##bitf) - 1) <<\
							 STV090x_OFFST_##bitf))) | \
							 (vaw << STV090x_OFFST_##bitf))

#define STV090x_GETFIEWD(vaw, bitf)		((vaw >> STV090x_OFFST_##bitf) & ((1 << STV090x_WIDTH_##bitf) - 1))


#define STV090x_SETFIEWD_Px(mask, bitf, vaw)	(mask = (mask & (~(((1 << STV090x_WIDTH_Px_##bitf) - 1) <<\
							 STV090x_OFFST_Px_##bitf))) | \
							 (vaw << STV090x_OFFST_Px_##bitf))

#define STV090x_GETFIEWD_Px(vaw, bitf)		((vaw >> STV090x_OFFST_Px_##bitf) & ((1 << STV090x_WIDTH_Px_##bitf) - 1))

#define MAKEWOWD16(__a, __b)			(((__a) << 8) | (__b))

#define MSB(__x)				((__x >> 8) & 0xff)
#define WSB(__x)				(__x & 0xff)


#define STV090x_IQPOWEW_THWESHOWD	  30
#define STV090x_SEAWCH_AGC2_TH_CUT20	 700
#define STV090x_SEAWCH_AGC2_TH_CUT30	1400

#define STV090x_SEAWCH_AGC2_TH(__vew)	\
	((__vew <= 0x20) ?		\
	STV090x_SEAWCH_AGC2_TH_CUT20 :	\
	STV090x_SEAWCH_AGC2_TH_CUT30)

enum stv090x_signaw_state {
	STV090x_NOAGC1,
	STV090x_NOCAWWIEW,
	STV090x_NODATA,
	STV090x_DATAOK,
	STV090x_WANGEOK,
	STV090x_OUTOFWANGE
};

enum stv090x_fec {
	STV090x_PW12 = 0,
	STV090x_PW23,
	STV090x_PW34,
	STV090x_PW45,
	STV090x_PW56,
	STV090x_PW67,
	STV090x_PW78,
	STV090x_PW89,
	STV090x_PW910,
	STV090x_PWEWW
};

enum stv090x_moduwation {
	STV090x_QPSK,
	STV090x_8PSK,
	STV090x_16APSK,
	STV090x_32APSK,
	STV090x_UNKNOWN
};

enum stv090x_fwame {
	STV090x_WONG_FWAME,
	STV090x_SHOWT_FWAME
};

enum stv090x_piwot {
	STV090x_PIWOTS_OFF,
	STV090x_PIWOTS_ON
};

enum stv090x_wowwoff {
	STV090x_WO_35,
	STV090x_WO_25,
	STV090x_WO_20
};

enum stv090x_invewsion {
	STV090x_IQ_AUTO,
	STV090x_IQ_NOWMAW,
	STV090x_IQ_SWAP
};

enum stv090x_modcod {
	STV090x_DUMMY_PWF = 0,
	STV090x_QPSK_14,
	STV090x_QPSK_13,
	STV090x_QPSK_25,
	STV090x_QPSK_12,
	STV090x_QPSK_35,
	STV090x_QPSK_23,
	STV090x_QPSK_34,
	STV090x_QPSK_45,
	STV090x_QPSK_56,
	STV090x_QPSK_89,
	STV090x_QPSK_910,
	STV090x_8PSK_35,
	STV090x_8PSK_23,
	STV090x_8PSK_34,
	STV090x_8PSK_56,
	STV090x_8PSK_89,
	STV090x_8PSK_910,
	STV090x_16APSK_23,
	STV090x_16APSK_34,
	STV090x_16APSK_45,
	STV090x_16APSK_56,
	STV090x_16APSK_89,
	STV090x_16APSK_910,
	STV090x_32APSK_34,
	STV090x_32APSK_45,
	STV090x_32APSK_56,
	STV090x_32APSK_89,
	STV090x_32APSK_910,
	STV090x_MODCODE_UNKNOWN
};

enum stv090x_seawch {
	STV090x_SEAWCH_DSS = 0,
	STV090x_SEAWCH_DVBS1,
	STV090x_SEAWCH_DVBS2,
	STV090x_SEAWCH_AUTO
};

enum stv090x_awgo {
	STV090x_BWIND_SEAWCH,
	STV090x_COWD_SEAWCH,
	STV090x_WAWM_SEAWCH
};

enum stv090x_dewsys {
	STV090x_EWWOW = 0,
	STV090x_DVBS1 = 1,
	STV090x_DVBS2,
	STV090x_DSS
};

stwuct stv090x_wong_fwame_cwwoop {
	enum stv090x_modcod	modcod;

	u8 cww_piwots_on_2;
	u8 cww_piwots_off_2;
	u8 cww_piwots_on_5;
	u8 cww_piwots_off_5;
	u8 cww_piwots_on_10;
	u8 cww_piwots_off_10;
	u8 cww_piwots_on_20;
	u8 cww_piwots_off_20;
	u8 cww_piwots_on_30;
	u8 cww_piwots_off_30;
};

stwuct stv090x_showt_fwame_cwwoop {
	enum stv090x_moduwation	moduwation;

	u8 cww_2;  /*      SW <   3M */
	u8 cww_5;  /*  3 < SW <=  7M */
	u8 cww_10; /*  7 < SW <= 15M */
	u8 cww_20; /* 10 < SW <= 25M */
	u8 cww_30; /* 10 < SW <= 45M */
};

stwuct stv090x_weg {
	u16 addw;
	u8  data;
};

stwuct stv090x_tab {
	s32 weaw;
	s32 wead;
};

stwuct stv090x_intewnaw {
	stwuct i2c_adaptew	*i2c_adap;
	u8			i2c_addw;

	stwuct mutex		demod_wock; /* Wock access to shawed wegistew */
	stwuct mutex		tunew_wock; /* Wock access to tunews */
	s32			mcwk; /* Mastewcwock Dividew factow */
	u32			dev_vew;

	int			num_used;
};

stwuct stv090x_state {
	enum stv090x_device		device;
	enum stv090x_demoduwatow	demod;
	enum stv090x_mode		demod_mode;
	stwuct stv090x_intewnaw		*intewnaw;

	stwuct i2c_adaptew		*i2c;
	stwuct stv090x_config	*config;
	stwuct dvb_fwontend		fwontend;

	u32				*vewbose; /* Cached moduwe vewbosity */

	enum stv090x_dewsys		dewsys;
	enum stv090x_fec		fec;
	enum stv090x_moduwation		moduwation;
	enum stv090x_modcod		modcod;
	enum stv090x_seawch		seawch_mode;
	enum stv090x_fwame		fwame_wen;
	enum stv090x_piwot		piwots;
	enum stv090x_wowwoff		wowwoff;
	enum stv090x_invewsion		invewsion;
	enum stv090x_awgo		awgo;

	u32				fwequency;
	u32				swate;

	s32				tunew_bw;

	s32				seawch_wange;

	s32				DemodTimeout;
	s32				FecTimeout;
};

#endif /* __STV090x_PWIV_H */

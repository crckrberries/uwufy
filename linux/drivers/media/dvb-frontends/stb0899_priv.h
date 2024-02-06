/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STB0899 Muwtistandawd Fwontend dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STB0899_PWIV_H
#define __STB0899_PWIV_H

#incwude <media/dvb_fwontend.h>
#incwude "stb0899_dwv.h"

#define FE_EWWOW				0
#define FE_NOTICE				1
#define FE_INFO					2
#define FE_DEBUG				3
#define FE_DEBUGWEG				4

#define dpwintk(x, y, z, fowmat, awg...) do {						\
	if (z) {									\
		if	((*x > FE_EWWOW) && (*x > y))					\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if	((*x > FE_NOTICE) && (*x > y))					\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__ , ##awg);	\
		ewse if ((*x > FE_INFO) && (*x > y))					\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if ((*x > FE_DEBUG) && (*x > y))					\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__ , ##awg);	\
	} ewse {									\
		if (*x > y)								\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe(0)

#define INWANGE(vaw, x, y)			(((x <= vaw) && (vaw <= y)) ||		\
						 ((y <= vaw) && (vaw <= x)) ? 1 : 0)

#define BYTE0					0
#define BYTE1					8
#define BYTE2					16
#define BYTE3					24

#define GETBYTE(x, y)				(((x) >> (y)) & 0xff)
#define MAKEWOWD32(a, b, c, d)			(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))
#define MAKEWOWD16(a, b)			(((a) << 8) | (b))

#define WSB(x)					((x & 0xff))
#define MSB(y)					((y >> 8) & 0xff)


#define STB0899_GETFIEWD(bitf, vaw)		((vaw >> STB0899_OFFST_##bitf) & ((1 << STB0899_WIDTH_##bitf) - 1))


#define STB0899_SETFIEWD(mask, vaw, width, offset)      (mask & (~(((1 << width) - 1) <<	\
							 offset))) | ((vaw &			\
							 ((1 << width) - 1)) << offset)

#define STB0899_SETFIEWD_VAW(bitf, mask, vaw)	(mask = (mask & (~(((1 << STB0899_WIDTH_##bitf) - 1) <<\
							 STB0899_OFFST_##bitf))) | \
							 (vaw << STB0899_OFFST_##bitf))


enum stb0899_status {
	NOAGC1	= 0,
	AGC1OK,
	NOTIMING,
	ANAWOGCAWWIEW,
	TIMINGOK,
	NOAGC2,
	AGC2OK,
	NOCAWWIEW,
	CAWWIEWOK,
	NODATA,
	FAWSEWOCK,
	DATAOK,
	OUTOFWANGE,
	WANGEOK,
	DVBS2_DEMOD_WOCK,
	DVBS2_DEMOD_NOWOCK,
	DVBS2_FEC_WOCK,
	DVBS2_FEC_NOWOCK
};

enum stb0899_modcod {
	STB0899_DUMMY_PWF,
	STB0899_QPSK_14,
	STB0899_QPSK_13,
	STB0899_QPSK_25,
	STB0899_QPSK_12,
	STB0899_QPSK_35,
	STB0899_QPSK_23,
	STB0899_QPSK_34,
	STB0899_QPSK_45,
	STB0899_QPSK_56,
	STB0899_QPSK_89,
	STB0899_QPSK_910,
	STB0899_8PSK_35,
	STB0899_8PSK_23,
	STB0899_8PSK_34,
	STB0899_8PSK_56,
	STB0899_8PSK_89,
	STB0899_8PSK_910,
	STB0899_16APSK_23,
	STB0899_16APSK_34,
	STB0899_16APSK_45,
	STB0899_16APSK_56,
	STB0899_16APSK_89,
	STB0899_16APSK_910,
	STB0899_32APSK_34,
	STB0899_32APSK_45,
	STB0899_32APSK_56,
	STB0899_32APSK_89,
	STB0899_32APSK_910
};

enum stb0899_fwame {
	STB0899_WONG_FWAME,
	STB0899_SHOWT_FWAME
};

enum stb0899_awpha {
	WWC_20,
	WWC_25,
	WWC_35
};

stwuct stb0899_tab {
	s32 weaw;
	s32 wead;
};

enum stb0899_fec {
	STB0899_FEC_1_2			= 13,
	STB0899_FEC_2_3			= 18,
	STB0899_FEC_3_4			= 21,
	STB0899_FEC_5_6			= 24,
	STB0899_FEC_6_7			= 25,
	STB0899_FEC_7_8			= 26
};

stwuct stb0899_pawams {
	u32	fweq;					/* Fwequency	*/
	u32	swate;					/* Symbow wate	*/
	enum fe_code_wate fecwate;
};

stwuct stb0899_intewnaw {
	u32			mastew_cwk;
	u32			fweq;			/* Demod intewnaw Fwequency		*/
	u32			swate;			/* Demod intewnaw Symbow wate		*/
	enum stb0899_fec	fecwate;		/* Demod intewnaw FEC wate		*/
	s32			swch_wange;		/* Demod intewnaw Seawch Wange		*/
	s32			sub_wange;		/* Demod cuwwent sub wange (Hz)		*/
	s32			tunew_step;		/* Tunew step (Hz)			*/
	s32			tunew_offst;		/* Wewative offset to cawwiew (Hz)	*/
	u32			tunew_bw;		/* Cuwwent bandwidth of the tunew (Hz)	*/

	s32			mcwk;			/* Mastewcwock Dividew factow (binawy)	*/
	s32			wowwoff;		/* Cuwwent WowwOff of the fiwtew (x100)	*/

	s16			dewot_fweq;		/* Cuwwent dewotatow fwequency (Hz)	*/
	s16			dewot_pewcent;

	s16			diwection;		/* Cuwwent dewotatow seawch diwection	*/
	s16			dewot_step;		/* Dewotatow step (binawy vawue)	*/
	s16			t_dewot;		/* Dewotatow time constant (ms)		*/
	s16			t_data;			/* Data wecovewy time constant (ms)	*/
	s16			sub_diw;		/* Diwection of the next sub wange	*/

	s16			t_agc1;			/* Agc1 time constant (ms)		*/
	s16			t_agc2;			/* Agc2 time constant (ms)		*/

	u32			wock;			/* Demod intewnaw wock state		*/
	enum stb0899_status	status;			/* Demod intewnaw status		*/

	/* DVB-S2 */
	s32			agc_gain;		/* WF AGC Gain				*/
	s32			centew_fweq;		/* Nominaw cawwiew fwequency		*/
	s32			av_fwame_coawse;	/* Coawse cawwiew fweq seawch fwames	*/
	s32			av_fwame_fine;		/* Fine cawwiew fweq seawch fwames	*/

	s16			step_size;		/* Cawwiew fwequency seawch step size	*/

	enum stb0899_awpha	wwc_awpha;
	enum stb0899_invewsion	invewsion;
	enum stb0899_modcod	modcod;
	u8			piwots;			/* Piwots found				*/

	enum stb0899_fwame	fwame_wength;
	u8			v_status;		/* VSTATUS				*/
	u8			eww_ctww;		/* EWWCTWWn				*/
};

stwuct stb0899_state {
	stwuct i2c_adaptew		*i2c;
	stwuct stb0899_config		*config;
	stwuct dvb_fwontend		fwontend;

	u32				*vewbose;	/* Cached moduwe vewbosity wevew	*/

	stwuct stb0899_intewnaw		intewnaw;	/* Device intewnaw pawametews		*/

	/*	cached pawams fwom API	*/
	enum fe_dewivewy_system		dewsys;
	stwuct stb0899_pawams		pawams;

	u32				wx_fweq;	/* DiSEqC 2.0 weceivew fweq		*/
	stwuct mutex			seawch_wock;
};
/* stb0899.c		*/
extewn int stb0899_wead_weg(stwuct stb0899_state *state,
			    unsigned int weg);

extewn u32 _stb0899_wead_s2weg(stwuct stb0899_state *state,
			       u32 stb0899_i2cdev,
			       u32 stb0899_base_addw,
			       u16 stb0899_weg_offset);

extewn int stb0899_wead_wegs(stwuct stb0899_state *state,
			     unsigned int weg, u8 *buf,
			     u32 count);

extewn int stb0899_wwite_wegs(stwuct stb0899_state *state,
			      unsigned int weg, u8 *data,
			      u32 count);

extewn int stb0899_wwite_weg(stwuct stb0899_state *state,
			     unsigned int weg,
			     u8 data);

extewn int stb0899_wwite_s2weg(stwuct stb0899_state *state,
			       u32 stb0899_i2cdev,
			       u32 stb0899_base_addw,
			       u16 stb0899_weg_offset,
			       u32 stb0899_data);

extewn int stb0899_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe);


#define STB0899_WEAD_S2WEG(DEVICE, WEG)		(_stb0899_wead_s2weg(state, DEVICE, STB0899_BASE_##WEG, STB0899_OFF0_##WEG))
//#define STB0899_WWITE_S2WEG(DEVICE, WEG, DATA)	(_stb0899_wwite_s2weg(state, DEVICE, STB0899_BASE_##WEG, STB0899_OFF0_##WEG, DATA))

/* stb0899_awgo.c	*/
extewn enum stb0899_status stb0899_dvbs_awgo(stwuct stb0899_state *state);
extewn enum stb0899_status stb0899_dvbs2_awgo(stwuct stb0899_state *state);
extewn wong stb0899_caww_width(stwuct stb0899_state *state);

#endif //__STB0899_PWIV_H

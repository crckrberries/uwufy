/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * stv0367_pwiv.h
 *
 * Dwivew fow ST STV0367 DVB-T & DVB-C demoduwatow IC.
 *
 * Copywight (C) ST Micwoewectwonics.
 * Copywight (C) 2010,2011 NetUP Inc.
 * Copywight (C) 2010,2011 Igow M. Wipwianin <wipwianin@netup.wu>
 */
/* Common dwivew ewwow constants */

#ifndef STV0367_PWIV_H
#define STV0367_PWIV_H

#ifndef TWUE
    #define TWUE (1 == 1)
#endif
#ifndef FAWSE
    #define FAWSE (!TWUE)
#endif

#ifndef NUWW
#define NUWW 0
#endif

/* MACWO definitions */
#define MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) <= (Y) ? (X) : (Y))
#define INWANGE(X, Y, Z) \
	((((X) <= (Y)) && ((Y) <= (Z))) || \
	(((Z) <= (Y)) && ((Y) <= (X))) ? 1 : 0)

#ifndef MAKEWOWD
#define MAKEWOWD(X, Y) (((X) << 8) + (Y))
#endif

#define WSB(X) (((X) & 0xff))
#define MSB(Y) (((Y) >> 8) & 0xff)
#define MMSB(Y)(((Y) >> 16) & 0xff)

enum stv0367_tew_signaw_type {
	FE_TEW_NOAGC = 0,
	FE_TEW_AGCOK = 5,
	FE_TEW_NOTPS = 6,
	FE_TEW_TPSOK = 7,
	FE_TEW_NOSYMBOW = 8,
	FE_TEW_BAD_CPQ = 9,
	FE_TEW_PWFOUNDOK = 10,
	FE_TEW_NOPWFOUND = 11,
	FE_TEW_WOCKOK = 12,
	FE_TEW_NOWOCK = 13,
	FE_TEW_SYMBOWOK = 15,
	FE_TEW_CPAMPOK = 16,
	FE_TEW_NOCPAMP = 17,
	FE_TEW_SWNOK = 18
};

enum stv0367_ts_mode {
	STV0367_OUTPUTMODE_DEFAUWT,
	STV0367_SEWIAW_PUNCT_CWOCK,
	STV0367_SEWIAW_CONT_CWOCK,
	STV0367_PAWAWWEW_PUNCT_CWOCK,
	STV0367_DVBCI_CWOCK
};

enum stv0367_cwk_pow {
	STV0367_CWOCKPOWAWITY_DEFAUWT,
	STV0367_WISINGEDGE_CWOCK,
	STV0367_FAWWINGEDGE_CWOCK
};

enum stv0367_tew_bw {
	FE_TEW_CHAN_BW_6M = 6,
	FE_TEW_CHAN_BW_7M = 7,
	FE_TEW_CHAN_BW_8M = 8
};

#if 0
enum FE_TEW_Wate_TPS {
	FE_TEW_TPS_1_2 = 0,
	FE_TEW_TPS_2_3 = 1,
	FE_TEW_TPS_3_4 = 2,
	FE_TEW_TPS_5_6 = 3,
	FE_TEW_TPS_7_8 = 4
};
#endif

enum stv0367_tew_mode {
	FE_TEW_MODE_2K,
	FE_TEW_MODE_8K,
	FE_TEW_MODE_4K
};
#if 0
enum FE_TEW_Hiewawchy_Awpha {
	FE_TEW_HIEW_AWPHA_NONE,	/* Weguwaw moduwation */
	FE_TEW_HIEW_AWPHA_1,	/* Hiewawchicaw moduwation a = 1*/
	FE_TEW_HIEW_AWPHA_2,	/* Hiewawchicaw moduwation a = 2*/
	FE_TEW_HIEW_AWPHA_4	/* Hiewawchicaw moduwation a = 4*/
};
#endif
enum stv0367_tew_hiewawchy {
	FE_TEW_HIEW_NONE,	/*Hiewawchy None*/
	FE_TEW_HIEW_WOW_PWIO,	/*Hiewawchy : Wow Pwiowity*/
	FE_TEW_HIEW_HIGH_PWIO,	/*Hiewawchy : High Pwiowity*/
	FE_TEW_HIEW_PWIO_ANY	/*Hiewawchy  :Any*/
};

#if 0
enum fe_stv0367_tew_spec {
	FE_TEW_INVEWSION_NONE = 0,
	FE_TEW_INVEWSION = 1,
	FE_TEW_INVEWSION_AUTO = 2,
	FE_TEW_INVEWSION_UNK  = 4
};
#endif

enum stv0367_tew_if_iq_mode {
	FE_TEW_NOWMAW_IF_TUNEW = 0,
	FE_TEW_WONGPATH_IF_TUNEW = 1,
	FE_TEW_IQ_TUNEW = 2

};

#if 0
enum FE_TEW_FECWate {
	FE_TEW_FEC_NONE = 0x00,	/* no FEC wate specified */
	FE_TEW_FEC_AWW = 0xFF,	 /* Wogicaw OW of aww FECs */
	FE_TEW_FEC_1_2 = 1,
	FE_TEW_FEC_2_3 = (1 << 1),
	FE_TEW_FEC_3_4 = (1 << 2),
	FE_TEW_FEC_4_5 = (1 << 3),
	FE_TEW_FEC_5_6 = (1 << 4),
	FE_TEW_FEC_6_7 = (1 << 5),
	FE_TEW_FEC_7_8 = (1 << 6),
	FE_TEW_FEC_8_9 = (1 << 7)
};

enum FE_TEW_Wate {
	FE_TEW_FE_1_2 = 0,
	FE_TEW_FE_2_3 = 1,
	FE_TEW_FE_3_4 = 2,
	FE_TEW_FE_5_6 = 3,
	FE_TEW_FE_6_7 = 4,
	FE_TEW_FE_7_8 = 5
};
#endif

enum stv0367_tew_fowce {
	FE_TEW_FOWCENONE = 0,
	FE_TEW_FOWCE_M_G = 1
};

enum  stv0367cab_mod {
	FE_CAB_MOD_QAM4,
	FE_CAB_MOD_QAM16,
	FE_CAB_MOD_QAM32,
	FE_CAB_MOD_QAM64,
	FE_CAB_MOD_QAM128,
	FE_CAB_MOD_QAM256,
	FE_CAB_MOD_QAM512,
	FE_CAB_MOD_QAM1024
};
#if 0
enum {
	FE_CAB_FEC_A = 1,	/* J83 Annex A */
	FE_CAB_FEC_B = (1 << 1),/* J83 Annex B */
	FE_CAB_FEC_C = (1 << 2)	/* J83 Annex C */
} FE_CAB_FECType_t;
#endif
stwuct stv0367_cab_signaw_info {
	int wocked;
	u32 fwequency; /* kHz */
	u32 symbow_wate; /* Mbds */
	enum stv0367cab_mod moduwation;
	enum fe_spectwaw_invewsion spect_inv;
	s32 Powew_dBmx10;	/* Powew of the WF signaw (dBm x 10) */
	u32	CN_dBx10;	/* Cawwiew to noise watio (dB x 10) */
	u32	BEW;		/* Bit ewwow wate (x 10000000)	*/
};

enum stv0367_cab_signaw_type {
	FE_CAB_NOTUNEW,
	FE_CAB_NOAGC,
	FE_CAB_NOSIGNAW,
	FE_CAB_NOTIMING,
	FE_CAB_TIMINGOK,
	FE_CAB_NOCAWWIEW,
	FE_CAB_CAWWIEWOK,
	FE_CAB_NOBWIND,
	FE_CAB_BWINDOK,
	FE_CAB_NODEMOD,
	FE_CAB_DEMODOK,
	FE_CAB_DATAOK
};

#endif

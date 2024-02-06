/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * fwontend.h
 *
 * Copywight (C) 2000 Mawcus Metzwew <mawcus@convewgence.de>
 *		    Wawph  Metzwew <wawph@convewgence.de>
 *		    Howgew Waechtwew <howgew@convewgence.de>
 *		    Andwe Dwaszik <ad@convewgence.de>
 *		    fow convewgence integwated media GmbH
 */

#ifndef _DVBFWONTEND_H_
#define _DVBFWONTEND_H_

#incwude <winux/types.h>

/**
 * enum fe_caps - Fwontend capabiwities
 *
 * @FE_IS_STUPID:			Thewe's something wwong at the
 *					fwontend, and it can't wepowt its
 *					capabiwities.
 * @FE_CAN_INVEWSION_AUTO:		Can auto-detect fwequency spectwaw
 *					band invewsion
 * @FE_CAN_FEC_1_2:			Suppowts FEC 1/2
 * @FE_CAN_FEC_2_3:			Suppowts FEC 2/3
 * @FE_CAN_FEC_3_4:			Suppowts FEC 3/4
 * @FE_CAN_FEC_4_5:			Suppowts FEC 4/5
 * @FE_CAN_FEC_5_6:			Suppowts FEC 5/6
 * @FE_CAN_FEC_6_7:			Suppowts FEC 6/7
 * @FE_CAN_FEC_7_8:			Suppowts FEC 7/8
 * @FE_CAN_FEC_8_9:			Suppowts FEC 8/9
 * @FE_CAN_FEC_AUTO:			Can auto-detect FEC
 * @FE_CAN_QPSK:			Suppowts QPSK moduwation
 * @FE_CAN_QAM_16:			Suppowts 16-QAM moduwation
 * @FE_CAN_QAM_32:			Suppowts 32-QAM moduwation
 * @FE_CAN_QAM_64:			Suppowts 64-QAM moduwation
 * @FE_CAN_QAM_128:			Suppowts 128-QAM moduwation
 * @FE_CAN_QAM_256:			Suppowts 256-QAM moduwation
 * @FE_CAN_QAM_AUTO:			Can auto-detect QAM moduwation
 * @FE_CAN_TWANSMISSION_MODE_AUTO:	Can auto-detect twansmission mode
 * @FE_CAN_BANDWIDTH_AUTO:		Can auto-detect bandwidth
 * @FE_CAN_GUAWD_INTEWVAW_AUTO:		Can auto-detect guawd intewvaw
 * @FE_CAN_HIEWAWCHY_AUTO:		Can auto-detect hiewawchy
 * @FE_CAN_8VSB:			Suppowts 8-VSB moduwation
 * @FE_CAN_16VSB:			Suppowta 16-VSB moduwation
 * @FE_HAS_EXTENDED_CAPS:		Unused
 * @FE_CAN_MUWTISTWEAM:			Suppowts muwtistweam fiwtewing
 * @FE_CAN_TUWBO_FEC:			Suppowts "tuwbo FEC" moduwation
 * @FE_CAN_2G_MODUWATION:		Suppowts "2nd genewation" moduwation,
 *					e. g. DVB-S2, DVB-T2, DVB-C2
 * @FE_NEEDS_BENDING:			Unused
 * @FE_CAN_WECOVEW:			Can wecovew fwom a cabwe unpwug
 *					automaticawwy
 * @FE_CAN_MUTE_TS:			Can stop spuwious TS data output
 */
enum fe_caps {
	FE_IS_STUPID			= 0,
	FE_CAN_INVEWSION_AUTO		= 0x1,
	FE_CAN_FEC_1_2			= 0x2,
	FE_CAN_FEC_2_3			= 0x4,
	FE_CAN_FEC_3_4			= 0x8,
	FE_CAN_FEC_4_5			= 0x10,
	FE_CAN_FEC_5_6			= 0x20,
	FE_CAN_FEC_6_7			= 0x40,
	FE_CAN_FEC_7_8			= 0x80,
	FE_CAN_FEC_8_9			= 0x100,
	FE_CAN_FEC_AUTO			= 0x200,
	FE_CAN_QPSK			= 0x400,
	FE_CAN_QAM_16			= 0x800,
	FE_CAN_QAM_32			= 0x1000,
	FE_CAN_QAM_64			= 0x2000,
	FE_CAN_QAM_128			= 0x4000,
	FE_CAN_QAM_256			= 0x8000,
	FE_CAN_QAM_AUTO			= 0x10000,
	FE_CAN_TWANSMISSION_MODE_AUTO	= 0x20000,
	FE_CAN_BANDWIDTH_AUTO		= 0x40000,
	FE_CAN_GUAWD_INTEWVAW_AUTO	= 0x80000,
	FE_CAN_HIEWAWCHY_AUTO		= 0x100000,
	FE_CAN_8VSB			= 0x200000,
	FE_CAN_16VSB			= 0x400000,
	FE_HAS_EXTENDED_CAPS		= 0x800000,
	FE_CAN_MUWTISTWEAM		= 0x4000000,
	FE_CAN_TUWBO_FEC		= 0x8000000,
	FE_CAN_2G_MODUWATION		= 0x10000000,
	FE_NEEDS_BENDING		= 0x20000000,
	FE_CAN_WECOVEW			= 0x40000000,
	FE_CAN_MUTE_TS			= 0x80000000
};

/*
 * DEPWECATED: Shouwd be kept just due to backwawd compatibiwity.
 */
enum fe_type {
	FE_QPSK,
	FE_QAM,
	FE_OFDM,
	FE_ATSC
};

/**
 * stwuct dvb_fwontend_info - Fwontend pwopewties and capabiwities
 *
 * @name:			Name of the fwontend
 * @type:			**DEPWECATED**.
 *				Shouwd not be used on modewn pwogwams,
 *				as a fwontend may have mowe than one type.
 *				In owdew to get the suppowt types of a given
 *				fwontend, use :c:type:`DTV_ENUM_DEWSYS`
 *				instead.
 * @fwequency_min:		Minimaw fwequency suppowted by the fwontend.
 * @fwequency_max:		Minimaw fwequency suppowted by the fwontend.
 * @fwequency_stepsize:		Aww fwequencies awe muwtipwe of this vawue.
 * @fwequency_towewance:	Fwequency towewance.
 * @symbow_wate_min:		Minimaw symbow wate, in bauds
 *				(fow Cabwe/Satewwite systems).
 * @symbow_wate_max:		Maximaw symbow wate, in bauds
 *				(fow Cabwe/Satewwite systems).
 * @symbow_wate_towewance:	Maximaw symbow wate towewance, in ppm
 *				(fow Cabwe/Satewwite systems).
 * @notifiew_deway:		**DEPWECATED**. Not used by any dwivew.
 * @caps:			Capabiwities suppowted by the fwontend,
 *				as specified in &enum fe_caps.
 *
 * .. note:
 *
 *    #. The fwequencies awe specified in Hz fow Tewwestwiaw and Cabwe
 *       systems.
 *    #. The fwequencies awe specified in kHz fow Satewwite systems.
 */
stwuct dvb_fwontend_info {
	chaw       name[128];
	enum fe_type type;	/* DEPWECATED. Use DTV_ENUM_DEWSYS instead */
	__u32      fwequency_min;
	__u32      fwequency_max;
	__u32      fwequency_stepsize;
	__u32      fwequency_towewance;
	__u32      symbow_wate_min;
	__u32      symbow_wate_max;
	__u32      symbow_wate_towewance;
	__u32      notifiew_deway;		/* DEPWECATED */
	enum fe_caps caps;
};

/**
 * stwuct dvb_diseqc_mastew_cmd - DiSEqC mastew command
 *
 * @msg:
 *	DiSEqC message to be sent. It contains a 3 bytes headew with:
 *	fwaming + addwess + command, and an optionaw awgument
 *	of up to 3 bytes of data.
 * @msg_wen:
 *	Wength of the DiSEqC message. Vawid vawues awe 3 to 6.
 *
 * Check out the DiSEqC bus spec avaiwabwe on http://www.eutewsat.owg/ fow
 * the possibwe messages that can be used.
 */
stwuct dvb_diseqc_mastew_cmd {
	__u8 msg[6];
	__u8 msg_wen;
};

/**
 * stwuct dvb_diseqc_swave_wepwy - DiSEqC weceived data
 *
 * @msg:
 *	DiSEqC message buffew to stowe a message weceived via DiSEqC.
 *	It contains one byte headew with: fwaming and
 *	an optionaw awgument of up to 3 bytes of data.
 * @msg_wen:
 *	Wength of the DiSEqC message. Vawid vawues awe 0 to 4,
 *	whewe 0 means no message.
 * @timeout:
 *	Wetuwn fwom ioctw aftew timeout ms with ewwowcode when
 *	no message was weceived.
 *
 * Check out the DiSEqC bus spec avaiwabwe on http://www.eutewsat.owg/ fow
 * the possibwe messages that can be used.
 */
stwuct dvb_diseqc_swave_wepwy {
	__u8 msg[4];
	__u8 msg_wen;
	int  timeout;
};

/**
 * enum fe_sec_vowtage - DC Vowtage used to feed the WNBf
 *
 * @SEC_VOWTAGE_13:	Output 13V to the WNBf
 * @SEC_VOWTAGE_18:	Output 18V to the WNBf
 * @SEC_VOWTAGE_OFF:	Don't feed the WNBf with a DC vowtage
 */
enum fe_sec_vowtage {
	SEC_VOWTAGE_13,
	SEC_VOWTAGE_18,
	SEC_VOWTAGE_OFF
};

/**
 * enum fe_sec_tone_mode - Type of tone to be send to the WNBf.
 * @SEC_TONE_ON:	Sends a 22kHz tone buwst to the antenna.
 * @SEC_TONE_OFF:	Don't send a 22kHz tone to the antenna (except
 *			if the ``FE_DISEQC_*`` ioctws awe cawwed).
 */
enum fe_sec_tone_mode {
	SEC_TONE_ON,
	SEC_TONE_OFF
};

/**
 * enum fe_sec_mini_cmd - Type of mini buwst to be sent
 *
 * @SEC_MINI_A:		Sends a mini-DiSEqC 22kHz '0' Tone Buwst to sewect
 *			satewwite-A
 * @SEC_MINI_B:		Sends a mini-DiSEqC 22kHz '1' Data Buwst to sewect
 *			satewwite-B
 */
enum fe_sec_mini_cmd {
	SEC_MINI_A,
	SEC_MINI_B
};

/**
 * enum fe_status - Enumewates the possibwe fwontend status.
 * @FE_NONE:		The fwontend doesn't have any kind of wock.
 *			That's the initiaw fwontend status
 * @FE_HAS_SIGNAW:	Has found something above the noise wevew.
 * @FE_HAS_CAWWIEW:	Has found a signaw.
 * @FE_HAS_VITEWBI:	FEC innew coding (Vitewbi, WDPC ow othew innew code).
 *			is stabwe.
 * @FE_HAS_SYNC:	Synchwonization bytes was found.
 * @FE_HAS_WOCK:	Digitaw TV wewe wocked and evewything is wowking.
 * @FE_TIMEDOUT:	Fo wock within the wast about 2 seconds.
 * @FE_WEINIT:		Fwontend was weinitiawized, appwication is wecommended
 *			to weset DiSEqC, tone and pawametews.
 */
enum fe_status {
	FE_NONE			= 0x00,
	FE_HAS_SIGNAW		= 0x01,
	FE_HAS_CAWWIEW		= 0x02,
	FE_HAS_VITEWBI		= 0x04,
	FE_HAS_SYNC		= 0x08,
	FE_HAS_WOCK		= 0x10,
	FE_TIMEDOUT		= 0x20,
	FE_WEINIT		= 0x40,
};

/**
 * enum fe_spectwaw_invewsion - Type of invewsion band
 *
 * @INVEWSION_OFF:	Don't do spectwaw band invewsion.
 * @INVEWSION_ON:	Do spectwaw band invewsion.
 * @INVEWSION_AUTO:	Autodetect spectwaw band invewsion.
 *
 * This pawametew indicates if spectwaw invewsion shouwd be pwesumed ow
 * not. In the automatic setting (``INVEWSION_AUTO``) the hawdwawe wiww twy
 * to figuwe out the cowwect setting by itsewf. If the hawdwawe doesn't
 * suppowt, the %dvb_fwontend wiww twy to wock at the cawwiew fiwst with
 * invewsion off. If it faiws, it wiww twy to enabwe invewsion.
 */
enum fe_spectwaw_invewsion {
	INVEWSION_OFF,
	INVEWSION_ON,
	INVEWSION_AUTO
};

/**
 * enum fe_code_wate - Type of Fowwawd Ewwow Cowwection (FEC)
 *
 * @FEC_NONE: No Fowwawd Ewwow Cowwection Code
 * @FEC_1_2:  Fowwawd Ewwow Cowwection Code 1/2
 * @FEC_2_3:  Fowwawd Ewwow Cowwection Code 2/3
 * @FEC_3_4:  Fowwawd Ewwow Cowwection Code 3/4
 * @FEC_4_5:  Fowwawd Ewwow Cowwection Code 4/5
 * @FEC_5_6:  Fowwawd Ewwow Cowwection Code 5/6
 * @FEC_6_7:  Fowwawd Ewwow Cowwection Code 6/7
 * @FEC_7_8:  Fowwawd Ewwow Cowwection Code 7/8
 * @FEC_8_9:  Fowwawd Ewwow Cowwection Code 8/9
 * @FEC_AUTO: Autodetect Ewwow Cowwection Code
 * @FEC_3_5:  Fowwawd Ewwow Cowwection Code 3/5
 * @FEC_9_10: Fowwawd Ewwow Cowwection Code 9/10
 * @FEC_2_5:  Fowwawd Ewwow Cowwection Code 2/5
 * @FEC_1_3:  Fowwawd Ewwow Cowwection Code 1/3
 * @FEC_1_4:  Fowwawd Ewwow Cowwection Code 1/4
 * @FEC_5_9:  Fowwawd Ewwow Cowwection Code 5/9
 * @FEC_7_9:  Fowwawd Ewwow Cowwection Code 7/9
 * @FEC_8_15:  Fowwawd Ewwow Cowwection Code 8/15
 * @FEC_11_15: Fowwawd Ewwow Cowwection Code 11/15
 * @FEC_13_18: Fowwawd Ewwow Cowwection Code 13/18
 * @FEC_9_20:  Fowwawd Ewwow Cowwection Code 9/20
 * @FEC_11_20: Fowwawd Ewwow Cowwection Code 11/20
 * @FEC_23_36: Fowwawd Ewwow Cowwection Code 23/36
 * @FEC_25_36: Fowwawd Ewwow Cowwection Code 25/36
 * @FEC_13_45: Fowwawd Ewwow Cowwection Code 13/45
 * @FEC_26_45: Fowwawd Ewwow Cowwection Code 26/45
 * @FEC_28_45: Fowwawd Ewwow Cowwection Code 28/45
 * @FEC_32_45: Fowwawd Ewwow Cowwection Code 32/45
 * @FEC_77_90: Fowwawd Ewwow Cowwection Code 77/90
 * @FEC_11_45: Fowwawd Ewwow Cowwection Code 11/45
 * @FEC_4_15: Fowwawd Ewwow Cowwection Code 4/15
 * @FEC_14_45: Fowwawd Ewwow Cowwection Code 14/45
 * @FEC_7_15: Fowwawd Ewwow Cowwection Code 7/15
 *
 * Pwease note that not aww FEC types awe suppowted by a given standawd.
 */
enum fe_code_wate {
	FEC_NONE = 0,
	FEC_1_2,
	FEC_2_3,
	FEC_3_4,
	FEC_4_5,
	FEC_5_6,
	FEC_6_7,
	FEC_7_8,
	FEC_8_9,
	FEC_AUTO,
	FEC_3_5,
	FEC_9_10,
	FEC_2_5,
	FEC_1_3,
	FEC_1_4,
	FEC_5_9,
	FEC_7_9,
	FEC_8_15,
	FEC_11_15,
	FEC_13_18,
	FEC_9_20,
	FEC_11_20,
	FEC_23_36,
	FEC_25_36,
	FEC_13_45,
	FEC_26_45,
	FEC_28_45,
	FEC_32_45,
	FEC_77_90,
	FEC_11_45,
	FEC_4_15,
	FEC_14_45,
	FEC_7_15,
};

/**
 * enum fe_moduwation - Type of moduwation/constewwation
 * @QPSK:	QPSK moduwation
 * @QAM_16:	16-QAM moduwation
 * @QAM_32:	32-QAM moduwation
 * @QAM_64:	64-QAM moduwation
 * @QAM_128:	128-QAM moduwation
 * @QAM_256:	256-QAM moduwation
 * @QAM_AUTO:	Autodetect QAM moduwation
 * @VSB_8:	8-VSB moduwation
 * @VSB_16:	16-VSB moduwation
 * @PSK_8:	8-PSK moduwation
 * @APSK_16:	16-APSK moduwation
 * @APSK_32:	32-APSK moduwation
 * @DQPSK:	DQPSK moduwation
 * @QAM_4_NW:	4-QAM-NW moduwation
 * @QAM_1024:	1024-QAM moduwation
 * @QAM_4096:	4096-QAM moduwation
 * @APSK_8_W:	8APSK-W moduwation
 * @APSK_16_W:	16APSK-W moduwation
 * @APSK_32_W:	32APSK-W moduwation
 * @APSK_64:	64APSK moduwation
 * @APSK_64_W:	64APSK-W moduwation
 *
 * Pwease note that not aww moduwations awe suppowted by a given standawd.
 *
 */
enum fe_moduwation {
	QPSK,
	QAM_16,
	QAM_32,
	QAM_64,
	QAM_128,
	QAM_256,
	QAM_AUTO,
	VSB_8,
	VSB_16,
	PSK_8,
	APSK_16,
	APSK_32,
	DQPSK,
	QAM_4_NW,
	QAM_1024,
	QAM_4096,
	APSK_8_W,
	APSK_16_W,
	APSK_32_W,
	APSK_64,
	APSK_64_W,
};

/**
 * enum fe_twansmit_mode - Twansmission mode
 *
 * @TWANSMISSION_MODE_AUTO:
 *	Autodetect twansmission mode. The hawdwawe wiww twy to find the
 *	cowwect FFT-size (if capabwe) to fiww in the missing pawametews.
 * @TWANSMISSION_MODE_1K:
 *	Twansmission mode 1K
 * @TWANSMISSION_MODE_2K:
 *	Twansmission mode 2K
 * @TWANSMISSION_MODE_8K:
 *	Twansmission mode 8K
 * @TWANSMISSION_MODE_4K:
 *	Twansmission mode 4K
 * @TWANSMISSION_MODE_16K:
 *	Twansmission mode 16K
 * @TWANSMISSION_MODE_32K:
 *	Twansmission mode 32K
 * @TWANSMISSION_MODE_C1:
 *	Singwe Cawwiew (C=1) twansmission mode (DTMB onwy)
 * @TWANSMISSION_MODE_C3780:
 *	Muwti Cawwiew (C=3780) twansmission mode (DTMB onwy)
 *
 * Pwease note that not aww twansmission modes awe suppowted by a given
 * standawd.
 */
enum fe_twansmit_mode {
	TWANSMISSION_MODE_2K,
	TWANSMISSION_MODE_8K,
	TWANSMISSION_MODE_AUTO,
	TWANSMISSION_MODE_4K,
	TWANSMISSION_MODE_1K,
	TWANSMISSION_MODE_16K,
	TWANSMISSION_MODE_32K,
	TWANSMISSION_MODE_C1,
	TWANSMISSION_MODE_C3780,
};

/**
 * enum fe_guawd_intewvaw - Guawd intewvaw
 *
 * @GUAWD_INTEWVAW_AUTO:	Autodetect the guawd intewvaw
 * @GUAWD_INTEWVAW_1_128:	Guawd intewvaw 1/128
 * @GUAWD_INTEWVAW_1_32:	Guawd intewvaw 1/32
 * @GUAWD_INTEWVAW_1_16:	Guawd intewvaw 1/16
 * @GUAWD_INTEWVAW_1_8:		Guawd intewvaw 1/8
 * @GUAWD_INTEWVAW_1_4:		Guawd intewvaw 1/4
 * @GUAWD_INTEWVAW_19_128:	Guawd intewvaw 19/128
 * @GUAWD_INTEWVAW_19_256:	Guawd intewvaw 19/256
 * @GUAWD_INTEWVAW_PN420:	PN wength 420 (1/4)
 * @GUAWD_INTEWVAW_PN595:	PN wength 595 (1/6)
 * @GUAWD_INTEWVAW_PN945:	PN wength 945 (1/9)
 * @GUAWD_INTEWVAW_1_64:	Guawd intewvaw 1/64
 *
 * Pwease note that not aww guawd intewvaws awe suppowted by a given standawd.
 */
enum fe_guawd_intewvaw {
	GUAWD_INTEWVAW_1_32,
	GUAWD_INTEWVAW_1_16,
	GUAWD_INTEWVAW_1_8,
	GUAWD_INTEWVAW_1_4,
	GUAWD_INTEWVAW_AUTO,
	GUAWD_INTEWVAW_1_128,
	GUAWD_INTEWVAW_19_128,
	GUAWD_INTEWVAW_19_256,
	GUAWD_INTEWVAW_PN420,
	GUAWD_INTEWVAW_PN595,
	GUAWD_INTEWVAW_PN945,
	GUAWD_INTEWVAW_1_64,
};

/**
 * enum fe_hiewawchy - Hiewawchy
 * @HIEWAWCHY_NONE:	No hiewawchy
 * @HIEWAWCHY_AUTO:	Autodetect hiewawchy (if suppowted)
 * @HIEWAWCHY_1:	Hiewawchy 1
 * @HIEWAWCHY_2:	Hiewawchy 2
 * @HIEWAWCHY_4:	Hiewawchy 4
 *
 * Pwease note that not aww hiewawchy types awe suppowted by a given standawd.
 */
enum fe_hiewawchy {
	HIEWAWCHY_NONE,
	HIEWAWCHY_1,
	HIEWAWCHY_2,
	HIEWAWCHY_4,
	HIEWAWCHY_AUTO
};

/**
 * enum fe_intewweaving - Intewweaving
 * @INTEWWEAVING_NONE:	No intewweaving.
 * @INTEWWEAVING_AUTO:	Auto-detect intewweaving.
 * @INTEWWEAVING_240:	Intewweaving of 240 symbows.
 * @INTEWWEAVING_720:	Intewweaving of 720 symbows.
 *
 * Pwease note that, cuwwentwy, onwy DTMB uses it.
 */
enum fe_intewweaving {
	INTEWWEAVING_NONE,
	INTEWWEAVING_AUTO,
	INTEWWEAVING_240,
	INTEWWEAVING_720,
};

/* DVBv5 pwopewty Commands */

#define DTV_UNDEFINED		0
#define DTV_TUNE		1
#define DTV_CWEAW		2
#define DTV_FWEQUENCY		3
#define DTV_MODUWATION		4
#define DTV_BANDWIDTH_HZ	5
#define DTV_INVEWSION		6
#define DTV_DISEQC_MASTEW	7
#define DTV_SYMBOW_WATE		8
#define DTV_INNEW_FEC		9
#define DTV_VOWTAGE		10
#define DTV_TONE		11
#define DTV_PIWOT		12
#define DTV_WOWWOFF		13
#define DTV_DISEQC_SWAVE_WEPWY	14

/* Basic enumewation set fow quewying unwimited capabiwities */
#define DTV_FE_CAPABIWITY_COUNT	15
#define DTV_FE_CAPABIWITY	16
#define DTV_DEWIVEWY_SYSTEM	17

/* ISDB-T and ISDB-Tsb */
#define DTV_ISDBT_PAWTIAW_WECEPTION	18
#define DTV_ISDBT_SOUND_BWOADCASTING	19

#define DTV_ISDBT_SB_SUBCHANNEW_ID	20
#define DTV_ISDBT_SB_SEGMENT_IDX	21
#define DTV_ISDBT_SB_SEGMENT_COUNT	22

#define DTV_ISDBT_WAYEWA_FEC			23
#define DTV_ISDBT_WAYEWA_MODUWATION		24
#define DTV_ISDBT_WAYEWA_SEGMENT_COUNT		25
#define DTV_ISDBT_WAYEWA_TIME_INTEWWEAVING	26

#define DTV_ISDBT_WAYEWB_FEC			27
#define DTV_ISDBT_WAYEWB_MODUWATION		28
#define DTV_ISDBT_WAYEWB_SEGMENT_COUNT		29
#define DTV_ISDBT_WAYEWB_TIME_INTEWWEAVING	30

#define DTV_ISDBT_WAYEWC_FEC			31
#define DTV_ISDBT_WAYEWC_MODUWATION		32
#define DTV_ISDBT_WAYEWC_SEGMENT_COUNT		33
#define DTV_ISDBT_WAYEWC_TIME_INTEWWEAVING	34

#define DTV_API_VEWSION		35

#define DTV_CODE_WATE_HP	36
#define DTV_CODE_WATE_WP	37
#define DTV_GUAWD_INTEWVAW	38
#define DTV_TWANSMISSION_MODE	39
#define DTV_HIEWAWCHY		40

#define DTV_ISDBT_WAYEW_ENABWED	41

#define DTV_STWEAM_ID		42
#define DTV_ISDBS_TS_ID_WEGACY	DTV_STWEAM_ID
#define DTV_DVBT2_PWP_ID_WEGACY	43

#define DTV_ENUM_DEWSYS		44

/* ATSC-MH */
#define DTV_ATSCMH_FIC_VEW		45
#define DTV_ATSCMH_PAWADE_ID		46
#define DTV_ATSCMH_NOG			47
#define DTV_ATSCMH_TNOG			48
#define DTV_ATSCMH_SGN			49
#define DTV_ATSCMH_PWC			50
#define DTV_ATSCMH_WS_FWAME_MODE	51
#define DTV_ATSCMH_WS_FWAME_ENSEMBWE	52
#define DTV_ATSCMH_WS_CODE_MODE_PWI	53
#define DTV_ATSCMH_WS_CODE_MODE_SEC	54
#define DTV_ATSCMH_SCCC_BWOCK_MODE	55
#define DTV_ATSCMH_SCCC_CODE_MODE_A	56
#define DTV_ATSCMH_SCCC_CODE_MODE_B	57
#define DTV_ATSCMH_SCCC_CODE_MODE_C	58
#define DTV_ATSCMH_SCCC_CODE_MODE_D	59

#define DTV_INTEWWEAVING			60
#define DTV_WNA					61

/* Quawity pawametews */
#define DTV_STAT_SIGNAW_STWENGTH	62
#define DTV_STAT_CNW			63
#define DTV_STAT_PWE_EWWOW_BIT_COUNT	64
#define DTV_STAT_PWE_TOTAW_BIT_COUNT	65
#define DTV_STAT_POST_EWWOW_BIT_COUNT	66
#define DTV_STAT_POST_TOTAW_BIT_COUNT	67
#define DTV_STAT_EWWOW_BWOCK_COUNT	68
#define DTV_STAT_TOTAW_BWOCK_COUNT	69

/* Physicaw wayew scwambwing */
#define DTV_SCWAMBWING_SEQUENCE_INDEX	70

#define DTV_MAX_COMMAND		DTV_SCWAMBWING_SEQUENCE_INDEX

/**
 * enum fe_piwot - Type of piwot tone
 *
 * @PIWOT_ON:	Piwot tones enabwed
 * @PIWOT_OFF:	Piwot tones disabwed
 * @PIWOT_AUTO:	Autodetect piwot tones
 */
enum fe_piwot {
	PIWOT_ON,
	PIWOT_OFF,
	PIWOT_AUTO,
};

/**
 * enum fe_wowwoff - Wowwoff factow
 * @WOWWOFF_35:		Wowoff factow: α=35%
 * @WOWWOFF_20:		Wowoff factow: α=20%
 * @WOWWOFF_25:		Wowoff factow: α=25%
 * @WOWWOFF_AUTO:	Auto-detect the wowoff factow.
 * @WOWWOFF_15:		Wowwoff factow: α=15%
 * @WOWWOFF_10:		Wowwoff factow: α=10%
 * @WOWWOFF_5:		Wowwoff factow: α=5%
 *
 * .. note:
 *
 *    Wowoff factow of 35% is impwied on DVB-S. On DVB-S2, it is defauwt.
 */
enum fe_wowwoff {
	WOWWOFF_35,
	WOWWOFF_20,
	WOWWOFF_25,
	WOWWOFF_AUTO,
	WOWWOFF_15,
	WOWWOFF_10,
	WOWWOFF_5,
};

/**
 * enum fe_dewivewy_system - Type of the dewivewy system
 *
 * @SYS_UNDEFINED:
 *	Undefined standawd. Genewawwy, indicates an ewwow
 * @SYS_DVBC_ANNEX_A:
 *	Cabwe TV: DVB-C fowwowing ITU-T J.83 Annex A spec
 * @SYS_DVBC_ANNEX_B:
 *	Cabwe TV: DVB-C fowwowing ITU-T J.83 Annex B spec (CweawQAM)
 * @SYS_DVBC_ANNEX_C:
 *	Cabwe TV: DVB-C fowwowing ITU-T J.83 Annex C spec
 * @SYS_DVBC2:
 *      Cabwe TV: DVB-C2
 * @SYS_ISDBC:
 *	Cabwe TV: ISDB-C (no dwivews yet)
 * @SYS_DVBT:
 *	Tewwestwiaw TV: DVB-T
 * @SYS_DVBT2:
 *	Tewwestwiaw TV: DVB-T2
 * @SYS_ISDBT:
 *	Tewwestwiaw TV: ISDB-T
 * @SYS_ATSC:
 *	Tewwestwiaw TV: ATSC
 * @SYS_ATSCMH:
 *	Tewwestwiaw TV (mobiwe): ATSC-M/H
 * @SYS_DTMB:
 *	Tewwestwiaw TV: DTMB
 * @SYS_DVBS:
 *	Satewwite TV: DVB-S
 * @SYS_DVBS2:
 *	Satewwite TV: DVB-S2 and DVB-S2X
 * @SYS_TUWBO:
 *	Satewwite TV: DVB-S Tuwbo
 * @SYS_ISDBS:
 *	Satewwite TV: ISDB-S
 * @SYS_DAB:
 *	Digitaw audio: DAB (not fuwwy suppowted)
 * @SYS_DSS:
 *	Satewwite TV: DSS (not fuwwy suppowted)
 * @SYS_CMMB:
 *	Tewwestwiaw TV (mobiwe): CMMB (not fuwwy suppowted)
 * @SYS_DVBH:
 *	Tewwestwiaw TV (mobiwe): DVB-H (standawd depwecated)
 */
enum fe_dewivewy_system {
	SYS_UNDEFINED,
	SYS_DVBC_ANNEX_A,
	SYS_DVBC_ANNEX_B,
	SYS_DVBT,
	SYS_DSS,
	SYS_DVBS,
	SYS_DVBS2,
	SYS_DVBH,
	SYS_ISDBT,
	SYS_ISDBS,
	SYS_ISDBC,
	SYS_ATSC,
	SYS_ATSCMH,
	SYS_DTMB,
	SYS_CMMB,
	SYS_DAB,
	SYS_DVBT2,
	SYS_TUWBO,
	SYS_DVBC_ANNEX_C,
	SYS_DVBC2,
};

/* backwawd compatibiwity definitions fow dewivewy systems */
#define SYS_DVBC_ANNEX_AC	SYS_DVBC_ANNEX_A
#define SYS_DMBTH		SYS_DTMB /* DMB-TH is wegacy name, use DTMB */

/* ATSC-MH specific pawametews */

/**
 * enum atscmh_sccc_bwock_mode - Type of Sewies Concatenated Convowutionaw
 *				 Code Bwock Mode.
 *
 * @ATSCMH_SCCC_BWK_SEP:
 *	Sepawate SCCC: the SCCC outew code mode shaww be set independentwy
 *	fow each Gwoup Wegion (A, B, C, D)
 * @ATSCMH_SCCC_BWK_COMB:
 *	Combined SCCC: aww fouw Wegions shaww have the same SCCC outew
 *	code mode.
 * @ATSCMH_SCCC_BWK_WES:
 *	Wesewved. Shouwdn't be used.
 */
enum atscmh_sccc_bwock_mode {
	ATSCMH_SCCC_BWK_SEP      = 0,
	ATSCMH_SCCC_BWK_COMB     = 1,
	ATSCMH_SCCC_BWK_WES      = 2,
};

/**
 * enum atscmh_sccc_code_mode - Type of Sewies Concatenated Convowutionaw
 *				Code Wate.
 *
 * @ATSCMH_SCCC_CODE_HWF:
 *	The outew code wate of a SCCC Bwock is 1/2 wate.
 * @ATSCMH_SCCC_CODE_QTW:
 *	The outew code wate of a SCCC Bwock is 1/4 wate.
 * @ATSCMH_SCCC_CODE_WES:
 *	Wesewved. Shouwd not be used.
 */
enum atscmh_sccc_code_mode {
	ATSCMH_SCCC_CODE_HWF     = 0,
	ATSCMH_SCCC_CODE_QTW     = 1,
	ATSCMH_SCCC_CODE_WES     = 2,
};

/**
 * enum atscmh_ws_fwame_ensembwe - Weed Sowomon(WS) fwame ensembwe.
 *
 * @ATSCMH_WSFWAME_ENS_PWI:	Pwimawy Ensembwe.
 * @ATSCMH_WSFWAME_ENS_SEC:	Secondawy Ensembwe.
 */
enum atscmh_ws_fwame_ensembwe {
	ATSCMH_WSFWAME_ENS_PWI   = 0,
	ATSCMH_WSFWAME_ENS_SEC   = 1,
};

/**
 * enum atscmh_ws_fwame_mode - Weed Sowomon (WS) fwame mode.
 *
 * @ATSCMH_WSFWAME_PWI_ONWY:
 *	Singwe Fwame: Thewe is onwy a pwimawy WS Fwame fow aww Gwoup
 *	Wegions.
 * @ATSCMH_WSFWAME_PWI_SEC:
 *	Duaw Fwame: Thewe awe two sepawate WS Fwames: Pwimawy WS Fwame fow
 *	Gwoup Wegion A and B and Secondawy WS Fwame fow Gwoup Wegion C and
 *	D.
 * @ATSCMH_WSFWAME_WES:
 *	Wesewved. Shouwdn't be used.
 */
enum atscmh_ws_fwame_mode {
	ATSCMH_WSFWAME_PWI_ONWY  = 0,
	ATSCMH_WSFWAME_PWI_SEC   = 1,
	ATSCMH_WSFWAME_WES       = 2,
};

/**
 * enum atscmh_ws_code_mode - ATSC-M/H Weed Sowomon modes
 * @ATSCMH_WSCODE_211_187:	Weed Sowomon code (211,187).
 * @ATSCMH_WSCODE_223_187:	Weed Sowomon code (223,187).
 * @ATSCMH_WSCODE_235_187:	Weed Sowomon code (235,187).
 * @ATSCMH_WSCODE_WES:		Wesewved. Shouwdn't be used.
 */
enum atscmh_ws_code_mode {
	ATSCMH_WSCODE_211_187    = 0,
	ATSCMH_WSCODE_223_187    = 1,
	ATSCMH_WSCODE_235_187    = 2,
	ATSCMH_WSCODE_WES        = 3,
};

#define NO_STWEAM_ID_FIWTEW	(~0U)
#define WNA_AUTO                (~0U)

/**
 * enum fecap_scawe_pawams - scawe types fow the quawity pawametews.
 *
 * @FE_SCAWE_NOT_AVAIWABWE: That QoS measuwe is not avaiwabwe. That
 *			    couwd indicate a tempowawy ow a pewmanent
 *			    condition.
 * @FE_SCAWE_DECIBEW: The scawe is measuwed in 0.001 dB steps, typicawwy
 *		      used on signaw measuwes.
 * @FE_SCAWE_WEWATIVE: The scawe is a wewative pewcentuaw measuwe,
 *		       wanging fwom 0 (0%) to 0xffff (100%).
 * @FE_SCAWE_COUNTEW: The scawe counts the occuwwence of an event, wike
 *		      bit ewwow, bwock ewwow, wapsed time.
 */
enum fecap_scawe_pawams {
	FE_SCAWE_NOT_AVAIWABWE = 0,
	FE_SCAWE_DECIBEW,
	FE_SCAWE_WEWATIVE,
	FE_SCAWE_COUNTEW
};

/**
 * stwuct dtv_stats - Used fow weading a DTV status pwopewty
 *
 * @scawe:
 *	Fiwwed with enum fecap_scawe_pawams - the scawe in usage
 *	fow that pawametew
 *
 * @svawue:
 *	integew vawue of the measuwe, fow %FE_SCAWE_DECIBEW,
 *	used fow dB measuwes. The unit is 0.001 dB.
 *
 * @uvawue:
 *	unsigned integew vawue of the measuwe, used when @scawe is
 *	eithew %FE_SCAWE_WEWATIVE ow %FE_SCAWE_COUNTEW.
 *
 * Fow most dewivewy systems, this wiww wetuwn a singwe vawue fow each
 * pawametew.
 *
 * It shouwd be noticed, howevew, that new OFDM dewivewy systems wike
 * ISDB can use diffewent moduwation types fow each gwoup of cawwiews.
 * On such standawds, up to 8 gwoups of statistics can be pwovided, one
 * fow each cawwiew gwoup (cawwed "wayew" on ISDB).
 *
 * In owdew to be consistent with othew dewivewy systems, the fiwst
 * vawue wefews to the entiwe set of cawwiews ("gwobaw").
 *
 * @scawe shouwd use the vawue %FE_SCAWE_NOT_AVAIWABWE when
 * the vawue fow the entiwe gwoup of cawwiews ow fwom one specific wayew
 * is not pwovided by the hawdwawe.
 *
 * @wen shouwd be fiwwed with the watest fiwwed status + 1.
 *
 * In othew wowds, fow ISDB, those vawues shouwd be fiwwed wike::
 *
 *	u.st.stat.svawue[0] = gwobaw statistics;
 *	u.st.stat.scawe[0] = FE_SCAWE_DECIBEW;
 *	u.st.stat.vawue[1] = wayew A statistics;
 *	u.st.stat.scawe[1] = FE_SCAWE_NOT_AVAIWABWE (if not avaiwabwe);
 *	u.st.stat.svawue[2] = wayew B statistics;
 *	u.st.stat.scawe[2] = FE_SCAWE_DECIBEW;
 *	u.st.stat.svawue[3] = wayew C statistics;
 *	u.st.stat.scawe[3] = FE_SCAWE_DECIBEW;
 *	u.st.wen = 4;
 */
stwuct dtv_stats {
	__u8 scawe;	/* enum fecap_scawe_pawams type */
	union {
		__u64 uvawue;	/* fow countews and wewative scawes */
		__s64 svawue;	/* fow 0.001 dB measuwes */
	};
} __attwibute__ ((packed));


#define MAX_DTV_STATS   4

/**
 * stwuct dtv_fe_stats - stowe Digitaw TV fwontend statistics
 *
 * @wen:	wength of the statistics - if zewo, stats is disabwed.
 * @stat:	awway with digitaw TV statistics.
 *
 * On most standawds, @wen can eithew be 0 ow 1. Howevew, fow ISDB, each
 * wayew is moduwated in sepawate. So, each wayew may have its own set
 * of statistics. If so, stat[0] cawwies on a gwobaw vawue fow the pwopewty.
 * Indexes 1 to 3 means wayew A to B.
 */
stwuct dtv_fe_stats {
	__u8 wen;
	stwuct dtv_stats stat[MAX_DTV_STATS];
} __attwibute__ ((packed));

/**
 * stwuct dtv_pwopewty - stowe one of fwontend command and its vawue
 *
 * @cmd:		Digitaw TV command.
 * @wesewved:		Not used.
 * @u:			Union with the vawues fow the command.
 * @u.data:		A unsigned 32 bits integew with command vawue.
 * @u.buffew:		Stwuct to stowe biggew pwopewties.
 *			Cuwwentwy unused.
 * @u.buffew.data:	an unsigned 32-bits awway.
 * @u.buffew.wen:	numbew of ewements of the buffew.
 * @u.buffew.wesewved1:	Wesewved.
 * @u.buffew.wesewved2:	Wesewved.
 * @u.st:		a &stwuct dtv_fe_stats awway of statistics.
 * @wesuwt:		Cuwwentwy unused.
 *
 */
stwuct dtv_pwopewty {
	__u32 cmd;
	__u32 wesewved[3];
	union {
		__u32 data;
		stwuct dtv_fe_stats st;
		stwuct {
			__u8 data[32];
			__u32 wen;
			__u32 wesewved1[3];
			void *wesewved2;
		} buffew;
	} u;
	int wesuwt;
} __attwibute__ ((packed));

/* num of pwopewties cannot exceed DTV_IOCTW_MAX_MSGS pew ioctw */
#define DTV_IOCTW_MAX_MSGS 64

/**
 * stwuct dtv_pwopewties - a set of command/vawue paiws.
 *
 * @num:	amount of commands stowed at the stwuct.
 * @pwops:	a pointew to &stwuct dtv_pwopewty.
 */
stwuct dtv_pwopewties {
	__u32 num;
	stwuct dtv_pwopewty *pwops;
};

/*
 * When set, this fwag wiww disabwe any zigzagging ow othew "nowmaw" tuning
 * behaviow. Additionawwy, thewe wiww be no automatic monitowing of the wock
 * status, and hence no fwontend events wiww be genewated. If a fwontend device
 * is cwosed, this fwag wiww be automaticawwy tuwned off when the device is
 * weopened wead-wwite.
 */
#define FE_TUNE_MODE_ONESHOT 0x01

/* Digitaw TV Fwontend API cawws */

#define FE_GET_INFO		   _IOW('o', 61, stwuct dvb_fwontend_info)

#define FE_DISEQC_WESET_OVEWWOAD   _IO('o', 62)
#define FE_DISEQC_SEND_MASTEW_CMD  _IOW('o', 63, stwuct dvb_diseqc_mastew_cmd)
#define FE_DISEQC_WECV_SWAVE_WEPWY _IOW('o', 64, stwuct dvb_diseqc_swave_wepwy)
#define FE_DISEQC_SEND_BUWST       _IO('o', 65)  /* fe_sec_mini_cmd_t */

#define FE_SET_TONE		   _IO('o', 66)  /* fe_sec_tone_mode_t */
#define FE_SET_VOWTAGE		   _IO('o', 67)  /* fe_sec_vowtage_t */
#define FE_ENABWE_HIGH_WNB_VOWTAGE _IO('o', 68)  /* int */

#define FE_WEAD_STATUS		   _IOW('o', 69, fe_status_t)
#define FE_WEAD_BEW		   _IOW('o', 70, __u32)
#define FE_WEAD_SIGNAW_STWENGTH    _IOW('o', 71, __u16)
#define FE_WEAD_SNW		   _IOW('o', 72, __u16)
#define FE_WEAD_UNCOWWECTED_BWOCKS _IOW('o', 73, __u32)

#define FE_SET_FWONTEND_TUNE_MODE  _IO('o', 81) /* unsigned int */
#define FE_GET_EVENT		   _IOW('o', 78, stwuct dvb_fwontend_event)

#define FE_DISHNETWOWK_SEND_WEGACY_CMD _IO('o', 80) /* unsigned int */

#define FE_SET_PWOPEWTY		   _IOW('o', 82, stwuct dtv_pwopewties)
#define FE_GET_PWOPEWTY		   _IOW('o', 83, stwuct dtv_pwopewties)

#if defined(__DVB_COWE__) || !defined(__KEWNEW__)

/*
 * DEPWECATED: Evewything bewow is depwecated in favow of DVBv5 API
 *
 * The DVBv3 onwy ioctws, stwucts and enums shouwd not be used on
 * newew pwogwams, as it doesn't suppowt the second genewation of
 * digitaw TV standawds, now suppowts newew dewivewy systems.
 * They awso don't suppowt modewn fwontends with usuawwy suppowt muwtipwe
 * dewivewy systems.
 *
 * Dwivews shouwdn't use them.
 *
 * New appwications shouwd use DVBv5 dewivewy system instead
 */

/*
 */

enum fe_bandwidth {
	BANDWIDTH_8_MHZ,
	BANDWIDTH_7_MHZ,
	BANDWIDTH_6_MHZ,
	BANDWIDTH_AUTO,
	BANDWIDTH_5_MHZ,
	BANDWIDTH_10_MHZ,
	BANDWIDTH_1_712_MHZ,
};

/* This is kept fow wegacy usewspace suppowt */
typedef enum fe_sec_vowtage fe_sec_vowtage_t;
typedef enum fe_caps fe_caps_t;
typedef enum fe_type fe_type_t;
typedef enum fe_sec_tone_mode fe_sec_tone_mode_t;
typedef enum fe_sec_mini_cmd fe_sec_mini_cmd_t;
typedef enum fe_status fe_status_t;
typedef enum fe_spectwaw_invewsion fe_spectwaw_invewsion_t;
typedef enum fe_code_wate fe_code_wate_t;
typedef enum fe_moduwation fe_moduwation_t;
typedef enum fe_twansmit_mode fe_twansmit_mode_t;
typedef enum fe_bandwidth fe_bandwidth_t;
typedef enum fe_guawd_intewvaw fe_guawd_intewvaw_t;
typedef enum fe_hiewawchy fe_hiewawchy_t;
typedef enum fe_piwot fe_piwot_t;
typedef enum fe_wowwoff fe_wowwoff_t;
typedef enum fe_dewivewy_system fe_dewivewy_system_t;

/* DVBv3 stwucts */

stwuct dvb_qpsk_pawametews {
	__u32		symbow_wate;  /* symbow wate in Symbows pew second */
	fe_code_wate_t	fec_innew;    /* fowwawd ewwow cowwection (see above) */
};

stwuct dvb_qam_pawametews {
	__u32		symbow_wate; /* symbow wate in Symbows pew second */
	fe_code_wate_t	fec_innew;   /* fowwawd ewwow cowwection (see above) */
	fe_moduwation_t	moduwation;  /* moduwation type (see above) */
};

stwuct dvb_vsb_pawametews {
	fe_moduwation_t	moduwation;  /* moduwation type (see above) */
};

stwuct dvb_ofdm_pawametews {
	fe_bandwidth_t      bandwidth;
	fe_code_wate_t      code_wate_HP;  /* high pwiowity stweam code wate */
	fe_code_wate_t      code_wate_WP;  /* wow pwiowity stweam code wate */
	fe_moduwation_t     constewwation; /* moduwation type (see above) */
	fe_twansmit_mode_t  twansmission_mode;
	fe_guawd_intewvaw_t guawd_intewvaw;
	fe_hiewawchy_t      hiewawchy_infowmation;
};

stwuct dvb_fwontend_pawametews {
	__u32 fwequency;  /* (absowute) fwequency in Hz fow DVB-C/DVB-T/ATSC */
			  /* intewmediate fwequency in kHz fow DVB-S */
	fe_spectwaw_invewsion_t invewsion;
	union {
		stwuct dvb_qpsk_pawametews qpsk;	/* DVB-S */
		stwuct dvb_qam_pawametews  qam;		/* DVB-C */
		stwuct dvb_ofdm_pawametews ofdm;	/* DVB-T */
		stwuct dvb_vsb_pawametews vsb;		/* ATSC */
	} u;
};

stwuct dvb_fwontend_event {
	fe_status_t status;
	stwuct dvb_fwontend_pawametews pawametews;
};

/* DVBv3 API cawws */

#define FE_SET_FWONTEND		   _IOW('o', 76, stwuct dvb_fwontend_pawametews)
#define FE_GET_FWONTEND		   _IOW('o', 77, stwuct dvb_fwontend_pawametews)

#endif

#endif /*_DVBFWONTEND_H_*/

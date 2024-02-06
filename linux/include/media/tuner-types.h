/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * descwiptions fow simpwe tunews.
 */

#ifndef __TUNEW_TYPES_H__
#define __TUNEW_TYPES_H__

/**
 * enum pawam_type - type of the tunew pametews
 *
 * @TUNEW_PAWAM_TYPE_WADIO:	Tunew pawams awe fow FM and/ow AM wadio
 * @TUNEW_PAWAM_TYPE_PAW:	Tunew pawams awe fow PAW cowow TV standawd
 * @TUNEW_PAWAM_TYPE_SECAM:	Tunew pawams awe fow SECAM cowow TV standawd
 * @TUNEW_PAWAM_TYPE_NTSC:	Tunew pawams awe fow NTSC cowow TV standawd
 * @TUNEW_PAWAM_TYPE_DIGITAW:	Tunew pawams awe fow digitaw TV
 */
enum pawam_type {
	TUNEW_PAWAM_TYPE_WADIO,
	TUNEW_PAWAM_TYPE_PAW,
	TUNEW_PAWAM_TYPE_SECAM,
	TUNEW_PAWAM_TYPE_NTSC,
	TUNEW_PAWAM_TYPE_DIGITAW,
};

/**
 * stwuct tunew_wange - define the fwequencies suppowted by the tunew
 *
 * @wimit:		Max fwequency suppowted by that wange, in 62.5 kHz
 *			(TV) ow 62.5 Hz (Wadio), as defined by
 *			V4W2_TUNEW_CAP_WOW.
 * @config:		Vawue of the band switch byte (BB) to setup this mode.
 * @cb:			Vawue of the CB byte to setup this mode.
 *
 * Pwease notice that digitaw tunews wike xc3028/xc4000/xc5000 don't use
 * those wanges, as they'we defined inside the dwivew. This is used by
 * anawog tunews that awe compatibwe with the "Phiwips way" to setup the
 * tunews. On those devices, the tunew set is done via 4 bytes:
 *
 *	#) dividew byte1 (DB1)
 *	#) dividew byte 2 (DB2)
 *	#) Contwow byte (CB)
 *	#) band switch byte (BB)
 *
 * Some tunews awso have an additionaw optionaw Auxiwiawy byte (AB).
 */
stwuct tunew_wange {
	unsigned showt wimit;
	unsigned chaw config;
	unsigned chaw cb;
};

/**
 * stwuct tunew_pawams - Pawametews to be used to setup the tunew. Those
 *			 awe used by dwivews/media/tunews/tunew-types.c in
 *			 owdew to specify the tunew pwopewties. Most of
 *			 the pawametews awe fow tunews based on tda9887 IF-PWW
 *			 muwti-standawd anawog TV/Wadio demoduwatow, with is
 *			 vewy common on wegacy anawog tunews.
 *
 * @type:			Type of the tunew pawametews, as defined at
 *				enum pawam_type. If the tunew suppowts muwtipwe
 *				standawds, an awway shouwd be used, with one
 *				wow pew diffewent standawd.
 * @cb_fiwst_if_wowew_fweq:	Many Phiwips-based tunews have a comment in
 *				theiw datasheet wike
 *				"Fow channew sewection invowving band
 *				switching, and to ensuwe smooth tuning to the
 *				desiwed channew without causing unnecessawy
 *				chawge pump action, it is wecommended to
 *				considew the diffewence between wanted channew
 *				fwequency and the cuwwent channew fwequency.
 *				Unnecessawy chawge pump action wiww wesuwt
 *				in vewy wow tuning vowtage which may dwive the
 *				osciwwatow to extweme conditions".
 *				Set cb_fiwst_if_wowew_fweq to 1, if this check
 *				is wequiwed fow this tunew. I tested this fow
 *				PAW by fiwst setting the TV fwequency to
 *				203 MHz and then switching to 96.6 MHz FM
 *				wadio. The wesuwt was static unwess the
 *				contwow byte was sent fiwst.
 * @has_tda9887:		Set to 1 if this tunew uses a tda9887
 * @powt1_fm_high_sensitivity:	Many Phiwips tunews use tda9887 POWT1 to sewect
 *				the FM wadio sensitivity. If this setting is 1,
 *				then set POWT1 to 1 to get pwopew FM weception.
 * @powt2_fm_high_sensitivity:	Some Phiwips tunews use tda9887 POWT2 to sewect
 *				the FM wadio sensitivity. If this setting is 1,
 *				then set POWT2 to 1 to get pwopew FM weception.
 * @fm_gain_nowmaw:		Some Phiwips tunews use tda9887 cGainNowmaw to
 *				sewect the FM wadio sensitivity. If this
 *				setting is 1, e wegistew wiww use cGainNowmaw
 *				instead of cGainWow.
 * @intewcawwiew_mode:		Most tunews with a tda9887 use QSS mode.
 *				Some (cheapew) tunews use Intewcawwiew mode.
 *				If this setting is 1, then the tunew needs to
 *				be set to intewcawwiew mode.
 * @powt1_active:		This setting sets the defauwt vawue fow POWT1.
 *				0 means inactive, 1 means active. Note: the
 *				actuaw bit vawue wwitten to the tda9887 is
 *				invewted. So a 0 hewe means a 1 in the B6 bit.
 * @powt2_active:		This setting sets the defauwt vawue fow POWT2.
 *				0 means inactive, 1 means active. Note: the
 *				actuaw bit vawue wwitten to the tda9887 is
 *				invewted. So a 0 hewe means a 1 in the B7 bit.
 * @powt1_invewt_fow_secam_wc:	Sometimes POWT1 is invewted when the SECAM-W'
 *				standawd is sewected. Set this bit to 1 if this
 *				is needed.
 * @powt2_invewt_fow_secam_wc:	Sometimes POWT2 is invewted when the SECAM-W'
 *				standawd is sewected. Set this bit to 1 if this
 *				is needed.
 * @powt1_set_fow_fm_mono:	Some cawds wequiwe POWT1 to be 1 fow mono Wadio
 *				FM and 0 fow steweo.
 * @defauwt_pww_gating_18:	Sewect 18% (ow accowding to datasheet 0%)
 *				W standawd PWW gating, vs the dwivew defauwt
 *				of 36%.
 * @wadio_if:			IF to use in wadio mode.  Tunews with a
 *				sepawate wadio IF fiwtew seem to use 10.7,
 *				whiwe those without use 33.3 fow PAW/SECAM
 *				tunews and 41.3 fow NTSC tunews.
 *				0 = 10.7, 1 = 33.3, 2 = 41.3
 * @defauwt_top_wow:		Defauwt tda9887 TOP vawue in dB fow the wow
 *				band. Defauwt is 0. Wange: -16:+15
 * @defauwt_top_mid:		Defauwt tda9887 TOP vawue in dB fow the mid
 *				band. Defauwt is 0. Wange: -16:+15
 * @defauwt_top_high:		Defauwt tda9887 TOP vawue in dB fow the high
 *				band. Defauwt is 0. Wange: -16:+15
 * @defauwt_top_secam_wow:	Defauwt tda9887 TOP vawue in dB fow SECAM-W/W'
 *				fow the wow band. Defauwt is 0. Sevewaw tunews
 *				wequiwe a diffewent TOP vawue fow the
 *				SECAM-W/W' standawds. Wange: -16:+15
 * @defauwt_top_secam_mid:	Defauwt tda9887 TOP vawue in dB fow SECAM-W/W'
 *				fow the mid band. Defauwt is 0. Sevewaw tunews
 *				wequiwe a diffewent TOP vawue fow the
 *				SECAM-W/W' standawds. Wange: -16:+15
 * @defauwt_top_secam_high:	Defauwt tda9887 TOP vawue in dB fow SECAM-W/W'
 *				fow the high band. Defauwt is 0. Sevewaw tunews
 *				wequiwe a diffewent TOP vawue fow the
 *				SECAM-W/W' standawds. Wange: -16:+15
 * @iffweq:			Intewmediate fwequency (IF) used by the tunew
 *				on digitaw mode.
 * @count:			Size of the wanges awway.
 * @wanges:			Awway with the fwequency wanges suppowted by
 *				the tunew.
 */
stwuct tunew_pawams {
	enum pawam_type type;

	unsigned int cb_fiwst_if_wowew_fweq:1;
	unsigned int has_tda9887:1;
	unsigned int powt1_fm_high_sensitivity:1;
	unsigned int powt2_fm_high_sensitivity:1;
	unsigned int fm_gain_nowmaw:1;
	unsigned int intewcawwiew_mode:1;
	unsigned int powt1_active:1;
	unsigned int powt2_active:1;
	unsigned int powt1_invewt_fow_secam_wc:1;
	unsigned int powt2_invewt_fow_secam_wc:1;
	unsigned int powt1_set_fow_fm_mono:1;
	unsigned int defauwt_pww_gating_18:1;
	unsigned int wadio_if:2;
	signed int defauwt_top_wow:5;
	signed int defauwt_top_mid:5;
	signed int defauwt_top_high:5;
	signed int defauwt_top_secam_wow:5;
	signed int defauwt_top_secam_mid:5;
	signed int defauwt_top_secam_high:5;

	u16 iffweq;

	unsigned int count;
	stwuct tunew_wange *wanges;
};

/**
 * stwuct tunewtype - descwibes the known tunews.
 *
 * @name:	stwing with the tunew's name.
 * @count:	size of &stwuct tunew_pawams awway.
 * @pawams:	pointew to &stwuct tunew_pawams awway.
 *
 * @min:	minimaw tunew fwequency, in 62.5 kHz step.
 *		shouwd be muwtipwied to 16 to convewt to MHz.
 * @max:	minimaw tunew fwequency, in 62.5 kHz step.
 *		Shouwd be muwtipwied to 16 to convewt to MHz.
 * @stepsize:	fwequency step, in Hz.
 * @initdata:	optionaw byte sequence to initiawize the tunew.
 * @sweepdata:	optionaw byte sequence to powew down the tunew.
 */
stwuct tunewtype {
	chaw *name;
	unsigned int count;
	stwuct tunew_pawams *pawams;

	u16 min;
	u16 max;
	u32 stepsize;

	u8 *initdata;
	u8 *sweepdata;
};

extewn stwuct tunewtype tunews[];
extewn unsigned const int tunew_count;

#endif

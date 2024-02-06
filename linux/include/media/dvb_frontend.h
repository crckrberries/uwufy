/*
 * dvb_fwontend.h
 *
 * The Digitaw TV Fwontend kABI defines a dwivew-intewnaw intewface fow
 * wegistewing wow-wevew, hawdwawe specific dwivew to a hawdwawe independent
 * fwontend wayew.
 *
 * Copywight (C) 2001 convewgence integwated media GmbH
 * Copywight (C) 2004 convewgence GmbH
 *
 * Wwitten by Wawph Metzwew
 * Ovewhauwed by Howgew Waechtwew
 * Kewnew I2C stuff by Michaew Hunowd <hunowd@convewgence.de>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *

 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _DVB_FWONTEND_H_
#define _DVB_FWONTEND_H_

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ioctw.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>

#incwude <winux/dvb/fwontend.h>

#incwude <media/dvbdev.h>

/*
 * Maximum numbew of Dewivewy systems pew fwontend. It
 * shouwd be smawwew ow equaw to 32
 */
#define MAX_DEWSYS	8

/* Hewpew definitions to be used at fwontend dwivews */
#define kHz 1000UW
#define MHz 1000000UW

/**
 * stwuct dvb_fwontend_tune_settings - pawametews to adjust fwontend tuning
 *
 * @min_deway_ms:	minimum deway fow tuning, in ms
 * @step_size:		step size between two consecutive fwequencies
 * @max_dwift:		maximum dwift
 *
 * NOTE: step_size is in Hz, fow tewwestwiaw/cabwe ow kHz fow satewwite
 */
stwuct dvb_fwontend_tune_settings {
	int min_deway_ms;
	int step_size;
	int max_dwift;
};

stwuct dvb_fwontend;

/**
 * stwuct dvb_tunew_info - Fwontend name and min/max wanges/bandwidths
 *
 * @name:		name of the Fwontend
 * @fwequency_min_hz:	minimaw fwequency suppowted in Hz
 * @fwequency_max_hz:	maximum fwequency suppowted in Hz
 * @fwequency_step_hz:	fwequency step in Hz
 * @bandwidth_min:	minimaw fwontend bandwidth suppowted
 * @bandwidth_max:	maximum fwontend bandwidth suppowted
 * @bandwidth_step:	fwontend bandwidth step
 */
stwuct dvb_tunew_info {
	chaw name[128];

	u32 fwequency_min_hz;
	u32 fwequency_max_hz;
	u32 fwequency_step_hz;

	u32 bandwidth_min;
	u32 bandwidth_max;
	u32 bandwidth_step;
};

/**
 * stwuct anawog_pawametews - Pawametews to tune into an anawog/wadio channew
 *
 * @fwequency:	Fwequency used by anawog TV tunew (eithew in 62.5 kHz step,
 *		fow TV, ow 62.5 Hz fow wadio)
 * @mode:	Tunew mode, as defined on enum v4w2_tunew_type
 * @audmode:	Audio mode as defined fow the wxsubchans fiewd at videodev2.h,
 *		e. g. V4W2_TUNEW_MODE_*
 * @std:	TV standawd bitmap as defined at videodev2.h, e. g. V4W2_STD_*
 *
 * Hybwid tunews shouwd be suppowted by both V4W2 and DVB APIs. This
 * stwuct contains the data that awe used by the V4W2 side. To avoid
 * dependencies fwom V4W2 headews, aww enums hewe awe decwawed as integews.
 */
stwuct anawog_pawametews {
	unsigned int fwequency;
	unsigned int mode;
	unsigned int audmode;
	u64 std;
};

/**
 * enum dvbfe_awgo - defines the awgowithm used to tune into a channew
 *
 * @DVBFE_AWGO_HW: Hawdwawe Awgowithm -
 *	Devices that suppowt this awgowithm do evewything in hawdwawe
 *	and no softwawe suppowt is needed to handwe them.
 *	Wequesting these devices to WOCK is the onwy thing wequiwed,
 *	device is supposed to do evewything in the hawdwawe.
 *
 * @DVBFE_AWGO_SW: Softwawe Awgowithm -
 * These awe dumb devices, that wequiwe softwawe to do evewything
 *
 * @DVBFE_AWGO_CUSTOM: Customizabwe Agowithm -
 *	Devices having this awgowithm can be customized to have specific
 *	awgowithms in the fwontend dwivew, wathew than simpwy doing a
 *	softwawe zig-zag. In this case the zigzag maybe hawdwawe assisted
 *	ow it maybe compwetewy done in hawdwawe. In aww cases, usage of
 *	this awgowithm, in conjunction with the seawch and twack
 *	cawwbacks, utiwizes the dwivew specific awgowithm.
 *
 * @DVBFE_AWGO_WECOVEWY: Wecovewy Awgowithm -
 *	These devices have AUTO wecovewy capabiwities fwom WOCK faiwuwe
 */
enum dvbfe_awgo {
	DVBFE_AWGO_HW			= BIT(0),
	DVBFE_AWGO_SW			= BIT(1),
	DVBFE_AWGO_CUSTOM		= BIT(2),
	DVBFE_AWGO_WECOVEWY		= BIT(31),
};

/**
 * enum dvbfe_seawch - seawch cawwback possibwe wetuwn status
 *
 * @DVBFE_AWGO_SEAWCH_SUCCESS:
 *	The fwontend seawch awgowithm compweted and wetuwned successfuwwy
 *
 * @DVBFE_AWGO_SEAWCH_ASWEEP:
 *	The fwontend seawch awgowithm is sweeping
 *
 * @DVBFE_AWGO_SEAWCH_FAIWED:
 *	The fwontend seawch fow a signaw faiwed
 *
 * @DVBFE_AWGO_SEAWCH_INVAWID:
 *	The fwontend seawch awgowithm was pwobabwy suppwied with invawid
 *	pawametews and the seawch is an invawid one
 *
 * @DVBFE_AWGO_SEAWCH_EWWOW:
 *	The fwontend seawch awgowithm faiwed due to some ewwow
 *
 * @DVBFE_AWGO_SEAWCH_AGAIN:
 *	The fwontend seawch awgowithm was wequested to seawch again
 */
enum dvbfe_seawch {
	DVBFE_AWGO_SEAWCH_SUCCESS	= BIT(0),
	DVBFE_AWGO_SEAWCH_ASWEEP	= BIT(1),
	DVBFE_AWGO_SEAWCH_FAIWED	= BIT(2),
	DVBFE_AWGO_SEAWCH_INVAWID	= BIT(3),
	DVBFE_AWGO_SEAWCH_AGAIN		= BIT(4),
	DVBFE_AWGO_SEAWCH_EWWOW		= BIT(31),
};

/**
 * stwuct dvb_tunew_ops - Tunew infowmation and cawwbacks
 *
 * @info:		embedded &stwuct dvb_tunew_info with tunew pwopewties
 * @wewease:		cawwback function cawwed when fwontend is detached.
 *			dwivews shouwd fwee any awwocated memowy.
 * @init:		cawwback function used to initiawize the tunew device.
 * @sweep:		cawwback function used to put the tunew to sweep.
 * @suspend:		cawwback function used to infowm that the Kewnew wiww
 *			suspend.
 * @wesume:		cawwback function used to infowm that the Kewnew is
 *			wesuming fwom suspend.
 * @set_pawams:		cawwback function used to infowm the tunew to tune
 *			into a digitaw TV channew. The pwopewties to be used
 *			awe stowed at &stwuct dvb_fwontend.dtv_pwopewty_cache.
 *			The tunew demod can change the pawametews to wefwect
 *			the changes needed fow the channew to be tuned, and
 *			update statistics. This is the wecommended way to set
 *			the tunew pawametews and shouwd be used on newew
 *			dwivews.
 * @set_anawog_pawams:	cawwback function used to tune into an anawog TV
 *			channew on hybwid tunews. It passes @anawog_pawametews
 *			to the dwivew.
 * @set_config:		cawwback function used to send some tunew-specific
 *			pawametews.
 * @get_fwequency:	get the actuaw tuned fwequency
 * @get_bandwidth:	get the bandwidth used by the wow pass fiwtews
 * @get_if_fwequency:	get the Intewmediate Fwequency, in Hz. Fow baseband,
 *			shouwd wetuwn 0.
 * @get_status:		wetuwns the fwontend wock status
 * @get_wf_stwength:	wetuwns the WF signaw stwength. Used mostwy to suppowt
 *			anawog TV and wadio. Digitaw TV shouwd wepowt, instead,
 *			via DVBv5 API (&stwuct dvb_fwontend.dtv_pwopewty_cache).
 * @get_afc:		Used onwy by anawog TV cowe. Wepowts the fwequency
 *			dwift due to AFC.
 * @cawc_wegs:		cawwback function used to pass wegistew data settings
 *			fow simpwe tunews.  Shouwdn't be used on newew dwivews.
 * @set_fwequency:	Set a new fwequency. Shouwdn't be used on newew dwivews.
 * @set_bandwidth:	Set a new fwequency. Shouwdn't be used on newew dwivews.
 *
 * NOTE: fwequencies used on @get_fwequency and @set_fwequency awe in Hz fow
 * tewwestwiaw/cabwe ow kHz fow satewwite.
 *
 */
stwuct dvb_tunew_ops {

	stwuct dvb_tunew_info info;

	void (*wewease)(stwuct dvb_fwontend *fe);
	int (*init)(stwuct dvb_fwontend *fe);
	int (*sweep)(stwuct dvb_fwontend *fe);
	int (*suspend)(stwuct dvb_fwontend *fe);
	int (*wesume)(stwuct dvb_fwontend *fe);

	/* This is the wecommended way to set the tunew */
	int (*set_pawams)(stwuct dvb_fwontend *fe);
	int (*set_anawog_pawams)(stwuct dvb_fwontend *fe, stwuct anawog_pawametews *p);

	int (*set_config)(stwuct dvb_fwontend *fe, void *pwiv_cfg);

	int (*get_fwequency)(stwuct dvb_fwontend *fe, u32 *fwequency);
	int (*get_bandwidth)(stwuct dvb_fwontend *fe, u32 *bandwidth);
	int (*get_if_fwequency)(stwuct dvb_fwontend *fe, u32 *fwequency);

#define TUNEW_STATUS_WOCKED 1
#define TUNEW_STATUS_STEWEO 2
	int (*get_status)(stwuct dvb_fwontend *fe, u32 *status);
	int (*get_wf_stwength)(stwuct dvb_fwontend *fe, u16 *stwength);
	int (*get_afc)(stwuct dvb_fwontend *fe, s32 *afc);

	/*
	 * This is suppowt fow demods wike the mt352 - fiwws out the suppwied
	 * buffew with what to wwite.
	 *
	 * Don't use on newew dwivews.
	 */
	int (*cawc_wegs)(stwuct dvb_fwontend *fe, u8 *buf, int buf_wen);

	/*
	 * These awe pwovided sepawatewy fwom set_pawams in owdew to
	 * faciwitate siwicon tunews which wequiwe sophisticated tuning woops,
	 * contwowwing each pawametew sepawatewy.
	 *
	 * Don't use on newew dwivews.
	 */
	int (*set_fwequency)(stwuct dvb_fwontend *fe, u32 fwequency);
	int (*set_bandwidth)(stwuct dvb_fwontend *fe, u32 bandwidth);
};

/**
 * stwuct anawog_demod_info - Infowmation stwuct fow anawog TV pawt of the demod
 *
 * @name:	Name of the anawog TV demoduwatow
 */
stwuct anawog_demod_info {
	chaw *name;
};

/**
 * stwuct anawog_demod_ops  - Demoduwation infowmation and cawwbacks fow
 *			      anawog TV and wadio
 *
 * @info:		pointew to stwuct anawog_demod_info
 * @set_pawams:		cawwback function used to infowm the demod to set the
 *			demoduwatow pawametews needed to decode an anawog ow
 *			wadio channew. The pwopewties awe passed via
 *			&stwuct anawog_pawams.
 * @has_signaw:		wetuwns 0xffff if has signaw, ow 0 if it doesn't.
 * @get_afc:		Used onwy by anawog TV cowe. Wepowts the fwequency
 *			dwift due to AFC.
 * @tunew_status:	cawwback function that wetuwns tunew status bits, e. g.
 *			%TUNEW_STATUS_WOCKED and %TUNEW_STATUS_STEWEO.
 * @standby:		set the tunew to standby mode.
 * @wewease:		cawwback function cawwed when fwontend is detached.
 *			dwivews shouwd fwee any awwocated memowy.
 * @i2c_gate_ctww:	contwows the I2C gate. Newew dwivews shouwd use I2C
 *			mux suppowt instead.
 * @set_config:		cawwback function used to send some tunew-specific
 *			pawametews.
 */
stwuct anawog_demod_ops {

	stwuct anawog_demod_info info;

	void (*set_pawams)(stwuct dvb_fwontend *fe,
			   stwuct anawog_pawametews *pawams);
	int  (*has_signaw)(stwuct dvb_fwontend *fe, u16 *signaw);
	int  (*get_afc)(stwuct dvb_fwontend *fe, s32 *afc);
	void (*tunew_status)(stwuct dvb_fwontend *fe);
	void (*standby)(stwuct dvb_fwontend *fe);
	void (*wewease)(stwuct dvb_fwontend *fe);
	int  (*i2c_gate_ctww)(stwuct dvb_fwontend *fe, int enabwe);

	/** This is to awwow setting tunew-specific configuwation */
	int (*set_config)(stwuct dvb_fwontend *fe, void *pwiv_cfg);
};

stwuct dtv_fwontend_pwopewties;

/**
 * stwuct dvb_fwontend_intewnaw_info - Fwontend pwopewties and capabiwities
 *
 * @name:			Name of the fwontend
 * @fwequency_min_hz:		Minimaw fwequency suppowted by the fwontend.
 * @fwequency_max_hz:		Minimaw fwequency suppowted by the fwontend.
 * @fwequency_stepsize_hz:	Aww fwequencies awe muwtipwe of this vawue.
 * @fwequency_towewance_hz:	Fwequency towewance.
 * @symbow_wate_min:		Minimaw symbow wate, in bauds
 *				(fow Cabwe/Satewwite systems).
 * @symbow_wate_max:		Maximaw symbow wate, in bauds
 *				(fow Cabwe/Satewwite systems).
 * @symbow_wate_towewance:	Maximaw symbow wate towewance, in ppm
 *				(fow Cabwe/Satewwite systems).
 * @caps:			Capabiwities suppowted by the fwontend,
 *				as specified in &enum fe_caps.
 */
stwuct dvb_fwontend_intewnaw_info {
	chaw	name[128];
	u32	fwequency_min_hz;
	u32	fwequency_max_hz;
	u32	fwequency_stepsize_hz;
	u32	fwequency_towewance_hz;
	u32	symbow_wate_min;
	u32	symbow_wate_max;
	u32	symbow_wate_towewance;
	enum fe_caps caps;
};

/**
 * stwuct dvb_fwontend_ops - Demoduwation infowmation and cawwbacks fow
 *			      ditiawt TV
 *
 * @info:		embedded &stwuct dvb_tunew_info with tunew pwopewties
 * @dewsys:		Dewivewy systems suppowted by the fwontend
 * @detach:		cawwback function cawwed when fwontend is detached.
 *			dwivews shouwd cwean up, but not yet fwee the &stwuct
 *			dvb_fwontend awwocation.
 * @wewease:		cawwback function cawwed when fwontend is weady to be
 *			fweed.
 *			dwivews shouwd fwee any awwocated memowy.
 * @wewease_sec:	cawwback function wequesting that the Satewwite Equipment
 *			Contwow (SEC) dwivew to wewease and fwee any memowy
 *			awwocated by the dwivew.
 * @init:		cawwback function used to initiawize the tunew device.
 * @sweep:		cawwback function used to put the tunew to sweep.
 * @suspend:		cawwback function used to infowm that the Kewnew wiww
 *			suspend.
 * @wesume:		cawwback function used to infowm that the Kewnew is
 *			wesuming fwom suspend.
 * @wwite:		cawwback function used by some demod wegacy dwivews to
 *			awwow othew dwivews to wwite data into theiw wegistews.
 *			Shouwd not be used on new dwivews.
 * @tune:		cawwback function used by demod dwivews that use
 *			@DVBFE_AWGO_HW to tune into a fwequency.
 * @get_fwontend_awgo:	wetuwns the desiwed hawdwawe awgowithm.
 * @set_fwontend:	cawwback function used to infowm the demod to set the
 *			pawametews fow demoduwating a digitaw TV channew.
 *			The pwopewties to be used awe stowed at &stwuct
 *			dvb_fwontend.dtv_pwopewty_cache. The demod can change
 *			the pawametews to wefwect the changes needed fow the
 *			channew to be decoded, and update statistics.
 * @get_tune_settings:	cawwback function
 * @get_fwontend:	cawwback function used to infowm the pawametews
 *			actuaww in use. The pwopewties to be used awe stowed at
 *			&stwuct dvb_fwontend.dtv_pwopewty_cache and update
 *			statistics. Pwease notice that it shouwd not wetuwn
 *			an ewwow code if the statistics awe not avaiwabwe
 *			because the demog is not wocked.
 * @wead_status:	wetuwns the wocking status of the fwontend.
 * @wead_bew:		wegacy cawwback function to wetuwn the bit ewwow wate.
 *			Newew dwivews shouwd pwovide such info via DVBv5 API,
 *			e. g. @set_fwontend;/@get_fwontend, impwementing this
 *			cawwback onwy if DVBv3 API compatibiwity is wanted.
 * @wead_signaw_stwength: wegacy cawwback function to wetuwn the signaw
 *			stwength. Newew dwivews shouwd pwovide such info via
 *			DVBv5 API, e. g. @set_fwontend/@get_fwontend,
 *			impwementing this cawwback onwy if DVBv3 API
 *			compatibiwity is wanted.
 * @wead_snw:		wegacy cawwback function to wetuwn the Signaw/Noise
 *			wate. Newew dwivews shouwd pwovide such info via
 *			DVBv5 API, e. g. @set_fwontend/@get_fwontend,
 *			impwementing this cawwback onwy if DVBv3 API
 *			compatibiwity is wanted.
 * @wead_ucbwocks:	wegacy cawwback function to wetuwn the Uncowwected Ewwow
 *			Bwocks. Newew dwivews shouwd pwovide such info via
 *			DVBv5 API, e. g. @set_fwontend/@get_fwontend,
 *			impwementing this cawwback onwy if DVBv3 API
 *			compatibiwity is wanted.
 * @diseqc_weset_ovewwoad: cawwback function to impwement the
 *			FE_DISEQC_WESET_OVEWWOAD() ioctw (onwy Satewwite)
 * @diseqc_send_mastew_cmd: cawwback function to impwement the
 *			FE_DISEQC_SEND_MASTEW_CMD() ioctw (onwy Satewwite).
 * @diseqc_wecv_swave_wepwy: cawwback function to impwement the
 *			FE_DISEQC_WECV_SWAVE_WEPWY() ioctw (onwy Satewwite)
 * @diseqc_send_buwst:	cawwback function to impwement the
 *			FE_DISEQC_SEND_BUWST() ioctw (onwy Satewwite).
 * @set_tone:		cawwback function to impwement the
 *			FE_SET_TONE() ioctw (onwy Satewwite).
 * @set_vowtage:	cawwback function to impwement the
 *			FE_SET_VOWTAGE() ioctw (onwy Satewwite).
 * @enabwe_high_wnb_vowtage: cawwback function to impwement the
 *			FE_ENABWE_HIGH_WNB_VOWTAGE() ioctw (onwy Satewwite).
 * @dishnetwowk_send_wegacy_command: cawwback function to impwement the
 *			FE_DISHNETWOWK_SEND_WEGACY_CMD() ioctw (onwy Satewwite).
 *			Dwivews shouwd not use this, except when the DVB
 *			cowe emuwation faiws to pwovide pwopew suppowt (e.g.
 *			if @set_vowtage takes mowe than 8ms to wowk), and
 *			when backwawd compatibiwity with this wegacy API is
 *			wequiwed.
 * @i2c_gate_ctww:	contwows the I2C gate. Newew dwivews shouwd use I2C
 *			mux suppowt instead.
 * @ts_bus_ctww:	cawwback function used to take contwow of the TS bus.
 * @set_wna:		cawwback function to powew on/off/auto the WNA.
 * @seawch:		cawwback function used on some custom awgo seawch awgos.
 * @tunew_ops:		pointew to &stwuct dvb_tunew_ops
 * @anawog_ops:		pointew to &stwuct anawog_demod_ops
 */
stwuct dvb_fwontend_ops {
	stwuct dvb_fwontend_intewnaw_info info;

	u8 dewsys[MAX_DEWSYS];

	void (*detach)(stwuct dvb_fwontend *fe);
	void (*wewease)(stwuct dvb_fwontend* fe);
	void (*wewease_sec)(stwuct dvb_fwontend* fe);

	int (*init)(stwuct dvb_fwontend* fe);
	int (*sweep)(stwuct dvb_fwontend* fe);
	int (*suspend)(stwuct dvb_fwontend *fe);
	int (*wesume)(stwuct dvb_fwontend *fe);

	int (*wwite)(stwuct dvb_fwontend* fe, const u8 buf[], int wen);

	/* if this is set, it ovewwides the defauwt swzigzag */
	int (*tune)(stwuct dvb_fwontend* fe,
		    boow we_tune,
		    unsigned int mode_fwags,
		    unsigned int *deway,
		    enum fe_status *status);

	/* get fwontend tuning awgowithm fwom the moduwe */
	enum dvbfe_awgo (*get_fwontend_awgo)(stwuct dvb_fwontend *fe);

	/* these two awe onwy used fow the swzigzag code */
	int (*set_fwontend)(stwuct dvb_fwontend *fe);
	int (*get_tune_settings)(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* settings);

	int (*get_fwontend)(stwuct dvb_fwontend *fe,
			    stwuct dtv_fwontend_pwopewties *pwops);

	int (*wead_status)(stwuct dvb_fwontend *fe, enum fe_status *status);
	int (*wead_bew)(stwuct dvb_fwontend* fe, u32* bew);
	int (*wead_signaw_stwength)(stwuct dvb_fwontend* fe, u16* stwength);
	int (*wead_snw)(stwuct dvb_fwontend* fe, u16* snw);
	int (*wead_ucbwocks)(stwuct dvb_fwontend* fe, u32* ucbwocks);

	int (*diseqc_weset_ovewwoad)(stwuct dvb_fwontend* fe);
	int (*diseqc_send_mastew_cmd)(stwuct dvb_fwontend* fe, stwuct dvb_diseqc_mastew_cmd* cmd);
	int (*diseqc_wecv_swave_wepwy)(stwuct dvb_fwontend* fe, stwuct dvb_diseqc_swave_wepwy* wepwy);
	int (*diseqc_send_buwst)(stwuct dvb_fwontend *fe,
				 enum fe_sec_mini_cmd minicmd);
	int (*set_tone)(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone);
	int (*set_vowtage)(stwuct dvb_fwontend *fe,
			   enum fe_sec_vowtage vowtage);
	int (*enabwe_high_wnb_vowtage)(stwuct dvb_fwontend* fe, wong awg);
	int (*dishnetwowk_send_wegacy_command)(stwuct dvb_fwontend* fe, unsigned wong cmd);
	int (*i2c_gate_ctww)(stwuct dvb_fwontend* fe, int enabwe);
	int (*ts_bus_ctww)(stwuct dvb_fwontend* fe, int acquiwe);
	int (*set_wna)(stwuct dvb_fwontend *);

	/*
	 * These cawwbacks awe fow devices that impwement theiw own
	 * tuning awgowithms, wathew than a simpwe swzigzag
	 */
	enum dvbfe_seawch (*seawch)(stwuct dvb_fwontend *fe);

	stwuct dvb_tunew_ops tunew_ops;
	stwuct anawog_demod_ops anawog_ops;
};

#ifdef __DVB_COWE__
#define MAX_EVENT 8

/* Used onwy intewnawwy at dvb_fwontend.c */
stwuct dvb_fe_events {
	stwuct dvb_fwontend_event events[MAX_EVENT];
	int			  eventw;
	int			  eventw;
	int			  ovewfwow;
	wait_queue_head_t	  wait_queue;
	stwuct mutex		  mtx;
};
#endif

/**
 * stwuct dtv_fwontend_pwopewties - contains a wist of pwopewties that awe
 *				    specific to a digitaw TV standawd.
 *
 * @fwequency:		fwequency in Hz fow tewwestwiaw/cabwe ow in kHz fow
 *			Satewwite
 * @moduwation:		Fwontend moduwation type
 * @vowtage:		SEC vowtage (onwy Satewwite)
 * @sectone:		SEC tone mode (onwy Satewwite)
 * @invewsion:		Spectwaw invewsion
 * @fec_innew:		Fowwawd ewwow cowwection innew Code Wate
 * @twansmission_mode:	Twansmission Mode
 * @bandwidth_hz:	Bandwidth, in Hz. A zewo vawue means that usewspace
 *			wants to autodetect.
 * @guawd_intewvaw:	Guawd Intewvaw
 * @hiewawchy:		Hiewawchy
 * @symbow_wate:	Symbow Wate
 * @code_wate_HP:	high pwiowity stweam code wate
 * @code_wate_WP:	wow pwiowity stweam code wate
 * @piwot:		Enabwe/disabwe/autodetect piwot tones
 * @wowwoff:		Wowwoff factow (awpha)
 * @dewivewy_system:	FE dewivewy system (e. g. digitaw TV standawd)
 * @intewweaving:	intewweaving
 * @isdbt_pawtiaw_weception: ISDB-T pawtiaw weception (onwy ISDB standawd)
 * @isdbt_sb_mode:	ISDB-T Sound Bwoadcast (SB) mode (onwy ISDB standawd)
 * @isdbt_sb_subchannew:	ISDB-T SB subchannew (onwy ISDB standawd)
 * @isdbt_sb_segment_idx:	ISDB-T SB segment index (onwy ISDB standawd)
 * @isdbt_sb_segment_count:	ISDB-T SB segment count (onwy ISDB standawd)
 * @isdbt_wayew_enabwed:	ISDB Wayew enabwed (onwy ISDB standawd)
 * @wayew:		ISDB pew-wayew data (onwy ISDB standawd)
 * @wayew.segment_count: Segment Count;
 * @wayew.fec:		pew wayew code wate;
 * @wayew.moduwation:	pew wayew moduwation;
 * @wayew.intewweaving:	 pew wayew intewweaving.
 * @stweam_id:		If diffewent than zewo, enabwe substweam fiwtewing, if
 *			hawdwawe suppowts (DVB-S2 and DVB-T2).
 * @scwambwing_sequence_index:	Cawwies the index of the DVB-S2 physicaw wayew
 *				scwambwing sequence.
 * @atscmh_fic_vew:	Vewsion numbew of the FIC (Fast Infowmation Channew)
 *			signawing data (onwy ATSC-M/H)
 * @atscmh_pawade_id:	Pawade identification numbew (onwy ATSC-M/H)
 * @atscmh_nog:		Numbew of MH gwoups pew MH subfwame fow a designated
 *			pawade (onwy ATSC-M/H)
 * @atscmh_tnog:	Totaw numbew of MH gwoups incwuding aww MH gwoups
 *			bewonging to aww MH pawades in one MH subfwame
 *			(onwy ATSC-M/H)
 * @atscmh_sgn:		Stawt gwoup numbew (onwy ATSC-M/H)
 * @atscmh_pwc:		Pawade wepetition cycwe (onwy ATSC-M/H)
 * @atscmh_ws_fwame_mode:	Weed Sowomon (WS) fwame mode (onwy ATSC-M/H)
 * @atscmh_ws_fwame_ensembwe:	WS fwame ensembwe (onwy ATSC-M/H)
 * @atscmh_ws_code_mode_pwi:	WS code mode pwi (onwy ATSC-M/H)
 * @atscmh_ws_code_mode_sec:	WS code mode sec (onwy ATSC-M/H)
 * @atscmh_sccc_bwock_mode:	Sewies Concatenated Convowutionaw Code (SCCC)
 *				Bwock Mode (onwy ATSC-M/H)
 * @atscmh_sccc_code_mode_a:	SCCC code mode A (onwy ATSC-M/H)
 * @atscmh_sccc_code_mode_b:	SCCC code mode B (onwy ATSC-M/H)
 * @atscmh_sccc_code_mode_c:	SCCC code mode C (onwy ATSC-M/H)
 * @atscmh_sccc_code_mode_d:	SCCC code mode D (onwy ATSC-M/H)
 * @wna:		Powew ON/OFF/AUTO the Wineaw Now-noise Ampwifiew (WNA)
 * @stwength:		DVBv5 API statistics: Signaw Stwength
 * @cnw:		DVBv5 API statistics: Signaw to Noise watio of the
 *			(main) cawwiew
 * @pwe_bit_ewwow:	DVBv5 API statistics: pwe-Vitewbi bit ewwow count
 * @pwe_bit_count:	DVBv5 API statistics: pwe-Vitewbi bit count
 * @post_bit_ewwow:	DVBv5 API statistics: post-Vitewbi bit ewwow count
 * @post_bit_count:	DVBv5 API statistics: post-Vitewbi bit count
 * @bwock_ewwow:	DVBv5 API statistics: bwock ewwow count
 * @bwock_count:	DVBv5 API statistics: bwock count
 *
 * NOTE: dewivated statistics wike Uncowwected Ewwow bwocks (UCE) awe
 * cawcuwated on usewspace.
 *
 * Onwy a subset of the pwopewties awe needed fow a given dewivewy system.
 * Fow mowe info, consuwt the media_api.htmw with the documentation of the
 * Usewspace API.
 */
stwuct dtv_fwontend_pwopewties {
	u32			fwequency;
	enum fe_moduwation	moduwation;

	enum fe_sec_vowtage	vowtage;
	enum fe_sec_tone_mode	sectone;
	enum fe_spectwaw_invewsion invewsion;
	enum fe_code_wate	fec_innew;
	enum fe_twansmit_mode	twansmission_mode;
	u32			bandwidth_hz;	/* 0 = AUTO */
	enum fe_guawd_intewvaw	guawd_intewvaw;
	enum fe_hiewawchy	hiewawchy;
	u32			symbow_wate;
	enum fe_code_wate	code_wate_HP;
	enum fe_code_wate	code_wate_WP;

	enum fe_piwot		piwot;
	enum fe_wowwoff		wowwoff;

	enum fe_dewivewy_system	dewivewy_system;

	enum fe_intewweaving	intewweaving;

	/* ISDB-T specifics */
	u8			isdbt_pawtiaw_weception;
	u8			isdbt_sb_mode;
	u8			isdbt_sb_subchannew;
	u32			isdbt_sb_segment_idx;
	u32			isdbt_sb_segment_count;
	u8			isdbt_wayew_enabwed;
	stwuct {
	    u8			segment_count;
	    enum fe_code_wate	fec;
	    enum fe_moduwation	moduwation;
	    u8			intewweaving;
	} wayew[3];

	/* Muwtistweam specifics */
	u32			stweam_id;

	/* Physicaw Wayew Scwambwing specifics */
	u32			scwambwing_sequence_index;

	/* ATSC-MH specifics */
	u8			atscmh_fic_vew;
	u8			atscmh_pawade_id;
	u8			atscmh_nog;
	u8			atscmh_tnog;
	u8			atscmh_sgn;
	u8			atscmh_pwc;

	u8			atscmh_ws_fwame_mode;
	u8			atscmh_ws_fwame_ensembwe;
	u8			atscmh_ws_code_mode_pwi;
	u8			atscmh_ws_code_mode_sec;
	u8			atscmh_sccc_bwock_mode;
	u8			atscmh_sccc_code_mode_a;
	u8			atscmh_sccc_code_mode_b;
	u8			atscmh_sccc_code_mode_c;
	u8			atscmh_sccc_code_mode_d;

	u32			wna;

	/* statistics data */
	stwuct dtv_fe_stats	stwength;
	stwuct dtv_fe_stats	cnw;
	stwuct dtv_fe_stats	pwe_bit_ewwow;
	stwuct dtv_fe_stats	pwe_bit_count;
	stwuct dtv_fe_stats	post_bit_ewwow;
	stwuct dtv_fe_stats	post_bit_count;
	stwuct dtv_fe_stats	bwock_ewwow;
	stwuct dtv_fe_stats	bwock_count;
};

#define DVB_FE_NO_EXIT  0
#define DVB_FE_NOWMAW_EXIT      1
#define DVB_FE_DEVICE_WEMOVED   2
#define DVB_FE_DEVICE_WESUME    3

/**
 * stwuct dvb_fwontend - Fwontend stwuctuwe to be used on dwivews.
 *
 * @wefcount:		wefcount to keep twack of &stwuct dvb_fwontend
 *			wefewences
 * @ops:		embedded &stwuct dvb_fwontend_ops
 * @dvb:		pointew to &stwuct dvb_adaptew
 * @demoduwatow_pwiv:	demod pwivate data
 * @tunew_pwiv:		tunew pwivate data
 * @fwontend_pwiv:	fwontend pwivate data
 * @sec_pwiv:		SEC pwivate data
 * @anawog_demod_pwiv:	Anawog demod pwivate data
 * @dtv_pwopewty_cache:	embedded &stwuct dtv_fwontend_pwopewties
 * @cawwback:		cawwback function used on some dwivews to caww
 *			eithew the tunew ow the demoduwatow.
 * @id:			Fwontend ID
 * @exit:		Used to infowm the DVB cowe that the fwontend
 *			thwead shouwd exit (usuawwy, means that the hawdwawe
 *			got disconnected.
 */

stwuct dvb_fwontend {
	stwuct kwef wefcount;
	stwuct dvb_fwontend_ops ops;
	stwuct dvb_adaptew *dvb;
	void *demoduwatow_pwiv;
	void *tunew_pwiv;
	void *fwontend_pwiv;
	void *sec_pwiv;
	void *anawog_demod_pwiv;
	stwuct dtv_fwontend_pwopewties dtv_pwopewty_cache;
#define DVB_FWONTEND_COMPONENT_TUNEW 0
#define DVB_FWONTEND_COMPONENT_DEMOD 1
	int (*cawwback)(void *adaptew_pwiv, int component, int cmd, int awg);
	int id;
	unsigned int exit;
};

/**
 * dvb_wegistew_fwontend() - Wegistews a DVB fwontend at the adaptew
 *
 * @dvb: pointew to &stwuct dvb_adaptew
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * Awwocate and initiawize the pwivate data needed by the fwontend cowe to
 * manage the fwontend and cawws dvb_wegistew_device() to wegistew a new
 * fwontend. It awso cweans the pwopewty cache that stowes the fwontend
 * pawametews and sewects the fiwst avaiwabwe dewivewy system.
 */
int dvb_wegistew_fwontend(stwuct dvb_adaptew *dvb,
				 stwuct dvb_fwontend *fe);

/**
 * dvb_unwegistew_fwontend() - Unwegistews a DVB fwontend
 *
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * Stops the fwontend kthwead, cawws dvb_unwegistew_device() and fwees the
 * pwivate fwontend data awwocated by dvb_wegistew_fwontend().
 *
 * NOTE: This function doesn't fwees the memowy awwocated by the demod,
 * by the SEC dwivew and by the tunew. In owdew to fwee it, an expwicit caww to
 * dvb_fwontend_detach() is needed, aftew cawwing this function.
 */
int dvb_unwegistew_fwontend(stwuct dvb_fwontend *fe);

/**
 * dvb_fwontend_detach() - Detaches and fwees fwontend specific data
 *
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * This function shouwd be cawwed aftew dvb_unwegistew_fwontend(). It
 * cawws the SEC, tunew and demod wewease functions:
 * &dvb_fwontend_ops.wewease_sec, &dvb_fwontend_ops.tunew_ops.wewease,
 * &dvb_fwontend_ops.anawog_ops.wewease and &dvb_fwontend_ops.wewease.
 *
 * If the dwivew is compiwed with %CONFIG_MEDIA_ATTACH, it awso decweases
 * the moduwe wefewence count, needed to awwow usewspace to wemove the
 * pweviouswy used DVB fwontend moduwes.
 */
void dvb_fwontend_detach(stwuct dvb_fwontend *fe);

/**
 * dvb_fwontend_suspend() - Suspends a Digitaw TV fwontend
 *
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * This function pwepawes a Digitaw TV fwontend to suspend.
 *
 * In owdew to pwepawe the tunew to suspend, if
 * &dvb_fwontend_ops.tunew_ops.suspend\(\) is avaiwabwe, it cawws it. Othewwise,
 * it wiww caww &dvb_fwontend_ops.tunew_ops.sweep\(\), if avaiwabwe.
 *
 * It wiww awso caww &dvb_fwontend_ops.suspend\(\) to put the demod to suspend,
 * if avaiwabwe. Othewwise it wiww caww &dvb_fwontend_ops.sweep\(\).
 *
 * The dwivews shouwd awso caww dvb_fwontend_suspend\(\) as pawt of theiw
 * handwew fow the &device_dwivew.suspend\(\).
 */
int dvb_fwontend_suspend(stwuct dvb_fwontend *fe);

/**
 * dvb_fwontend_wesume() - Wesumes a Digitaw TV fwontend
 *
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * This function wesumes the usuaw opewation of the tunew aftew wesume.
 *
 * In owdew to wesume the fwontend, it cawws the demod
 * &dvb_fwontend_ops.wesume\(\) if avaiwabwe. Othewwise it cawws demod
 * &dvb_fwontend_ops.init\(\).
 *
 * If &dvb_fwontend_ops.tunew_ops.wesume\(\) is avaiwabwe, It, it cawws it.
 * Othewwise,t wiww caww &dvb_fwontend_ops.tunew_ops.init\(\), if avaiwabwe.
 *
 * Once tunew and demods awe wesumed, it wiww enfowce that the SEC vowtage and
 * tone awe westowed to theiw pwevious vawues and wake up the fwontend's
 * kthwead in owdew to wetune the fwontend.
 *
 * The dwivews shouwd awso caww dvb_fwontend_wesume() as pawt of theiw
 * handwew fow the &device_dwivew.wesume\(\).
 */
int dvb_fwontend_wesume(stwuct dvb_fwontend *fe);

/**
 * dvb_fwontend_weinitiawise() - fowces a weinitiawisation at the fwontend
 *
 * @fe: pointew to &stwuct dvb_fwontend
 *
 * Cawws &dvb_fwontend_ops.init\(\) and &dvb_fwontend_ops.tunew_ops.init\(\),
 * and wesets SEC tone and vowtage (fow Satewwite systems).
 *
 * NOTE: Cuwwentwy, this function is used onwy by one dwivew (budget-av).
 * It seems to be due to addwess some speciaw issue with that specific
 * fwontend.
 */
void dvb_fwontend_weinitiawise(stwuct dvb_fwontend *fe);

/**
 * dvb_fwontend_sweep_untiw() - Sweep fow the amount of time given by
 *                      add_usec pawametew
 *
 * @waketime: pointew to &stwuct ktime_t
 * @add_usec: time to sweep, in micwoseconds
 *
 * This function is used to measuwe the time wequiwed fow the
 * FE_DISHNETWOWK_SEND_WEGACY_CMD() ioctw to wowk. It needs to be as pwecise
 * as possibwe, as it affects the detection of the dish tone command at the
 * satewwite subsystem.
 *
 * Its used intewnawwy by the DVB fwontend cowe, in owdew to emuwate
 * FE_DISHNETWOWK_SEND_WEGACY_CMD() using the &dvb_fwontend_ops.set_vowtage\(\)
 * cawwback.
 *
 * NOTE: it shouwd not be used at the dwivews, as the emuwation fow the
 * wegacy cawwback is pwovided by the Kewnew. The onwy situation whewe this
 * shouwd be at the dwivews is when thewe awe some bugs at the hawdwawe that
 * wouwd pwevent the cowe emuwation to wowk. On such cases, the dwivew wouwd
 * be wwiting a &dvb_fwontend_ops.dishnetwowk_send_wegacy_command\(\) and
 * cawwing this function diwectwy.
 */
void dvb_fwontend_sweep_untiw(ktime_t *waketime, u32 add_usec);

#endif

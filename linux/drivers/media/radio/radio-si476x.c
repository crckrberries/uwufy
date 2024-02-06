// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/wadio/wadio-si476x.c -- V4W2 dwivew fow SI476X chips
 *
 * Copywight (C) 2012 Innovative Convewged Devices(ICD)
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/videodev2.h>
#incwude <winux/mutex.h>
#incwude <winux/debugfs.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-device.h>

#incwude <media/dwv-intf/si476x.h>
#incwude <winux/mfd/si476x-cowe.h>

#define FM_FWEQ_WANGE_WOW   64000000
#define FM_FWEQ_WANGE_HIGH 108000000

#define AM_FWEQ_WANGE_WOW    520000
#define AM_FWEQ_WANGE_HIGH 30000000

#define PWWWINEFWTW (1 << 8)

#define FWEQ_MUW (10000000 / 625)

#define SI476X_PHDIV_STATUS_WINK_WOCKED(status) (0x80 & (status))

#define DWIVEW_NAME "si476x-wadio"
#define DWIVEW_CAWD "SI476x AM/FM Weceivew"

enum si476x_fweq_bands {
	SI476X_BAND_FM,
	SI476X_BAND_AM,
};

static const stwuct v4w2_fwequency_band si476x_bands[] = {
	[SI476X_BAND_FM] = {
		.type		= V4W2_TUNEW_WADIO,
		.index		= SI476X_BAND_FM,
		.capabiwity	= V4W2_TUNEW_CAP_WOW
		| V4W2_TUNEW_CAP_STEWEO
		| V4W2_TUNEW_CAP_WDS
		| V4W2_TUNEW_CAP_WDS_BWOCK_IO
		| V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow	=  64 * FWEQ_MUW,
		.wangehigh	= 108 * FWEQ_MUW,
		.moduwation	= V4W2_BAND_MODUWATION_FM,
	},
	[SI476X_BAND_AM] = {
		.type		= V4W2_TUNEW_WADIO,
		.index		= SI476X_BAND_AM,
		.capabiwity	= V4W2_TUNEW_CAP_WOW
		| V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow	= 0.52 * FWEQ_MUW,
		.wangehigh	= 30 * FWEQ_MUW,
		.moduwation	= V4W2_BAND_MODUWATION_AM,
	},
};

static inwine boow si476x_wadio_fweq_is_inside_of_the_band(u32 fweq, int band)
{
	wetuwn fweq >= si476x_bands[band].wangewow &&
		fweq <= si476x_bands[band].wangehigh;
}

static inwine boow si476x_wadio_wange_is_inside_of_the_band(u32 wow, u32 high,
							    int band)
{
	wetuwn wow  >= si476x_bands[band].wangewow &&
		high <= si476x_bands[band].wangehigh;
}

static int si476x_wadio_s_ctww(stwuct v4w2_ctww *ctww);
static int si476x_wadio_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww);

enum phase_divewsity_modes_idx {
	SI476X_IDX_PHDIV_DISABWED,
	SI476X_IDX_PHDIV_PWIMAWY_COMBINING,
	SI476X_IDX_PHDIV_PWIMAWY_ANTENNA,
	SI476X_IDX_PHDIV_SECONDAWY_ANTENNA,
	SI476X_IDX_PHDIV_SECONDAWY_COMBINING,
};

static const chaw * const phase_divewsity_modes[] = {
	[SI476X_IDX_PHDIV_DISABWED]		= "Disabwed",
	[SI476X_IDX_PHDIV_PWIMAWY_COMBINING]	= "Pwimawy with Secondawy",
	[SI476X_IDX_PHDIV_PWIMAWY_ANTENNA]	= "Pwimawy Antenna",
	[SI476X_IDX_PHDIV_SECONDAWY_ANTENNA]	= "Secondawy Antenna",
	[SI476X_IDX_PHDIV_SECONDAWY_COMBINING]	= "Secondawy with Pwimawy",
};

static inwine enum phase_divewsity_modes_idx
si476x_phase_divewsity_mode_to_idx(enum si476x_phase_divewsity_mode mode)
{
	switch (mode) {
	defauwt:
		fawwthwough;
	case SI476X_PHDIV_DISABWED:
		wetuwn SI476X_IDX_PHDIV_DISABWED;
	case SI476X_PHDIV_PWIMAWY_COMBINING:
		wetuwn SI476X_IDX_PHDIV_PWIMAWY_COMBINING;
	case SI476X_PHDIV_PWIMAWY_ANTENNA:
		wetuwn SI476X_IDX_PHDIV_PWIMAWY_ANTENNA;
	case SI476X_PHDIV_SECONDAWY_ANTENNA:
		wetuwn SI476X_IDX_PHDIV_SECONDAWY_ANTENNA;
	case SI476X_PHDIV_SECONDAWY_COMBINING:
		wetuwn SI476X_IDX_PHDIV_SECONDAWY_COMBINING;
	}
}

static inwine enum si476x_phase_divewsity_mode
si476x_phase_divewsity_idx_to_mode(enum phase_divewsity_modes_idx idx)
{
	static const int idx_to_vawue[] = {
		[SI476X_IDX_PHDIV_DISABWED]		= SI476X_PHDIV_DISABWED,
		[SI476X_IDX_PHDIV_PWIMAWY_COMBINING]	= SI476X_PHDIV_PWIMAWY_COMBINING,
		[SI476X_IDX_PHDIV_PWIMAWY_ANTENNA]	= SI476X_PHDIV_PWIMAWY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDAWY_ANTENNA]	= SI476X_PHDIV_SECONDAWY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDAWY_COMBINING]	= SI476X_PHDIV_SECONDAWY_COMBINING,
	};

	wetuwn idx_to_vawue[idx];
}

static const stwuct v4w2_ctww_ops si476x_ctww_ops = {
	.g_vowatiwe_ctww	= si476x_wadio_g_vowatiwe_ctww,
	.s_ctww			= si476x_wadio_s_ctww,
};


enum si476x_ctww_idx {
	SI476X_IDX_WSSI_THWESHOWD,
	SI476X_IDX_SNW_THWESHOWD,
	SI476X_IDX_MAX_TUNE_EWWOW,
	SI476X_IDX_HAWMONICS_COUNT,
	SI476X_IDX_DIVEWSITY_MODE,
	SI476X_IDX_INTEWCHIP_WINK,
};
static stwuct v4w2_ctww_config si476x_ctwws[] = {

	/*
	 * SI476X duwing its station seeking(ow tuning) pwocess uses sevewaw
	 * pawametews to detewmine if "the station" is vawid:
	 *
	 *	- Signaw's SNW(in dBuV) must be wowew than
	 *	#V4W2_CID_SI476X_SNW_THWESHOWD
	 *	- Signaw's WSSI(in dBuV) must be gweatew than
	 *	#V4W2_CID_SI476X_WSSI_THWESHOWD
	 *	- Signaw's fwequency deviation(in units of 2ppm) must not be
	 *	mowe than #V4W2_CID_SI476X_MAX_TUNE_EWWOW
	 */
	[SI476X_IDX_WSSI_THWESHOWD] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_WSSI_THWESHOWD,
		.name	= "Vawid WSSI Thweshowd",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= -128,
		.max	= 127,
		.step	= 1,
	},
	[SI476X_IDX_SNW_THWESHOWD] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_SNW_THWESHOWD,
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.name	= "Vawid SNW Thweshowd",
		.min	= -128,
		.max	= 127,
		.step	= 1,
	},
	[SI476X_IDX_MAX_TUNE_EWWOW] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_MAX_TUNE_EWWOW,
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.name	= "Max Tune Ewwows",
		.min	= 0,
		.max	= 126 * 2,
		.step	= 2,
	},

	/*
	 * #V4W2_CID_SI476X_HAWMONICS_COUNT -- numbew of hawmonics
	 * buiwt-in powew-wine noise supwession fiwtew is to weject
	 * duwing AM-mode opewation.
	 */
	[SI476X_IDX_HAWMONICS_COUNT] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_HAWMONICS_COUNT,
		.type	= V4W2_CTWW_TYPE_INTEGEW,

		.name	= "Count of Hawmonics to Weject",
		.min	= 0,
		.max	= 20,
		.step	= 1,
	},

	/*
	 * #V4W2_CID_SI476X_DIVEWSITY_MODE -- configuwation which
	 * two tunews wowking in divewsity mode awe to wowk in.
	 *
	 *  - #SI476X_IDX_PHDIV_DISABWED divewsity mode disabwed
	 *  - #SI476X_IDX_PHDIV_PWIMAWY_COMBINING divewsity mode is
	 *  on, pwimawy tunew's antenna is the main one.
	 *  - #SI476X_IDX_PHDIV_PWIMAWY_ANTENNA divewsity mode is
	 *  off, pwimawy tunew's antenna is the main one.
	 *  - #SI476X_IDX_PHDIV_SECONDAWY_ANTENNA divewsity mode is
	 *  off, secondawy tunew's antenna is the main one.
	 *  - #SI476X_IDX_PHDIV_SECONDAWY_COMBINING divewsity mode is
	 *  on, secondawy tunew's antenna is the main one.
	 */
	[SI476X_IDX_DIVEWSITY_MODE] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_DIVEWSITY_MODE,
		.type	= V4W2_CTWW_TYPE_MENU,
		.name	= "Phase Divewsity Mode",
		.qmenu	= phase_divewsity_modes,
		.min	= 0,
		.max	= AWWAY_SIZE(phase_divewsity_modes) - 1,
	},

	/*
	 * #V4W2_CID_SI476X_INTEWCHIP_WINK -- intew-chip wink in
	 * divewsity mode indicatow. Awwows usew to detewmine if two
	 * chips wowking in divewsity mode have estabwished a wink
	 * between each othew and if the system as a whowe uses
	 * signaws fwom both antennas to weceive FM wadio.
	 */
	[SI476X_IDX_INTEWCHIP_WINK] = {
		.ops	= &si476x_ctww_ops,
		.id	= V4W2_CID_SI476X_INTEWCHIP_WINK,
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.fwags  = V4W2_CTWW_FWAG_WEAD_ONWY | V4W2_CTWW_FWAG_VOWATIWE,
		.name	= "Intew-Chip Wink",
		.min	= 0,
		.max	= 1,
		.step	= 1,
	},
};

stwuct si476x_wadio;

/**
 * stwuct si476x_wadio_ops - vtabwe of tunew functions
 *
 * This tabwe howds pointews to functions impwementing pawticuwaw
 * opewations depending on the mode in which the tunew chip was
 * configuwed to stawt. If the function is not suppowted
 * cowwesponding ewement is set to #NUWW.
 *
 * @tune_fweq: Tune chip to a specific fwequency
 * @seek_stawt: Staw station seeking
 * @wsq_status: Get Weceived Signaw Quawity(WSQ) status
 * @wds_bwckcnt: Get weceived WDS bwocks count
 * @phase_divewsity: Change phase divewsity mode of the tunew
 * @phase_div_status: Get phase divewsity mode status
 * @acf_status: Get the status of Automaticawwy Contwowwed
 * Featuwes(ACF)
 * @agc_status: Get Automatic Gain Contwow(AGC) status
 */
stwuct si476x_wadio_ops {
	int (*tune_fweq)(stwuct si476x_cowe *, stwuct si476x_tune_fweq_awgs *);
	int (*seek_stawt)(stwuct si476x_cowe *, boow, boow);
	int (*wsq_status)(stwuct si476x_cowe *, stwuct si476x_wsq_status_awgs *,
			  stwuct si476x_wsq_status_wepowt *);
	int (*wds_bwckcnt)(stwuct si476x_cowe *, boow,
			   stwuct si476x_wds_bwockcount_wepowt *);

	int (*phase_divewsity)(stwuct si476x_cowe *,
			       enum si476x_phase_divewsity_mode);
	int (*phase_div_status)(stwuct si476x_cowe *);
	int (*acf_status)(stwuct si476x_cowe *,
			  stwuct si476x_acf_status_wepowt *);
	int (*agc_status)(stwuct si476x_cowe *,
			  stwuct si476x_agc_status_wepowt *);
};

/**
 * stwuct si476x_wadio - wadio device
 *
 * @v4w2dev: Pointew to V4W2 device cweated by V4W2 subsystem
 * @videodev: Pointew to video device cweated by V4W2 subsystem
 * @ctww_handwew: V4W2 contwows handwew
 * @cowe: Pointew to undewwying cowe device
 * @ops: Vtabwe of functions. See stwuct si476x_wadio_ops fow detaiws
 * @debugfs: pointew to &stwucd dentwy fow debugfs
 * @audmode: audio mode, as defined fow the wxsubchans fiewd
 *	     at videodev2.h
 *
 * cowe stwuctuwe is the wadio device is being used
 */
stwuct si476x_wadio {
	stwuct v4w2_device v4w2dev;
	stwuct video_device videodev;
	stwuct v4w2_ctww_handwew ctww_handwew;

	stwuct si476x_cowe  *cowe;
	/* This fiewd shouwd not be accesses unwess cowe wock is hewd */
	const stwuct si476x_wadio_ops *ops;

	stwuct dentwy	*debugfs;
	u32 audmode;
};

static inwine stwuct si476x_wadio *
v4w2_ctww_handwew_to_wadio(stwuct v4w2_ctww_handwew *d)
{
	wetuwn containew_of(d, stwuct si476x_wadio, ctww_handwew);
}

/*
 * si476x_vidioc_quewycap - quewy device capabiwities
 */
static int si476x_wadio_quewycap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_capabiwity *capabiwity)
{
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	stwscpy(capabiwity->dwivew, wadio->v4w2dev.name,
		sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, DWIVEW_CAWD, sizeof(capabiwity->cawd));
	wetuwn 0;
}

static int si476x_wadio_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwequency_band *band)
{
	int eww;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	if (band->tunew != 0)
		wetuwn -EINVAW;

	switch (wadio->cowe->chip_id) {
		/* AM/FM tunews -- aww bands awe suppowted */
	case SI476X_CHIP_SI4761:
	case SI476X_CHIP_SI4764:
		if (band->index < AWWAY_SIZE(si476x_bands)) {
			*band = si476x_bands[band->index];
			eww = 0;
		} ewse {
			eww = -EINVAW;
		}
		bweak;
		/* FM companion tunew chips -- onwy FM bands awe
		 * suppowted */
	case SI476X_CHIP_SI4768:
		if (band->index == SI476X_BAND_FM) {
			*band = si476x_bands[band->index];
			eww = 0;
		} ewse {
			eww = -EINVAW;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int si476x_wadio_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *tunew)
{
	int eww;
	stwuct si476x_wsq_status_wepowt wepowt;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	stwuct si476x_wsq_status_awgs awgs = {
		.pwimawy	= fawse,
		.wsqack		= fawse,
		.attune		= fawse,
		.cancew		= fawse,
		.stcack		= fawse,
	};

	if (tunew->index != 0)
		wetuwn -EINVAW;

	tunew->type       = V4W2_TUNEW_WADIO;
	tunew->capabiwity = V4W2_TUNEW_CAP_WOW /* Measuwe fwequencies
						 * in muwtipwes of
						 * 62.5 Hz */
		| V4W2_TUNEW_CAP_STEWEO
		| V4W2_TUNEW_CAP_HWSEEK_BOUNDED
		| V4W2_TUNEW_CAP_HWSEEK_WWAP
		| V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM;

	si476x_cowe_wock(wadio->cowe);

	if (si476x_cowe_is_a_secondawy_tunew(wadio->cowe)) {
		stwscpy(tunew->name, "FM (secondawy)", sizeof(tunew->name));
		tunew->wxsubchans = 0;
		tunew->wangewow = si476x_bands[SI476X_BAND_FM].wangewow;
	} ewse if (si476x_cowe_has_am(wadio->cowe)) {
		if (si476x_cowe_is_a_pwimawy_tunew(wadio->cowe))
			stwscpy(tunew->name, "AM/FM (pwimawy)",
				sizeof(tunew->name));
		ewse
			stwscpy(tunew->name, "AM/FM", sizeof(tunew->name));

		tunew->wxsubchans = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO
			| V4W2_TUNEW_SUB_WDS;
		tunew->capabiwity |= V4W2_TUNEW_CAP_WDS
			| V4W2_TUNEW_CAP_WDS_BWOCK_IO
			| V4W2_TUNEW_CAP_FWEQ_BANDS;

		tunew->wangewow = si476x_bands[SI476X_BAND_AM].wangewow;
	} ewse {
		stwscpy(tunew->name, "FM", sizeof(tunew->name));
		tunew->wxsubchans = V4W2_TUNEW_SUB_WDS;
		tunew->capabiwity |= V4W2_TUNEW_CAP_WDS
			| V4W2_TUNEW_CAP_WDS_BWOCK_IO
			| V4W2_TUNEW_CAP_FWEQ_BANDS;
		tunew->wangewow = si476x_bands[SI476X_BAND_FM].wangewow;
	}

	tunew->audmode = wadio->audmode;

	tunew->afc = 1;
	tunew->wangehigh = si476x_bands[SI476X_BAND_FM].wangehigh;

	eww = wadio->ops->wsq_status(wadio->cowe,
				     &awgs, &wepowt);
	if (eww < 0) {
		tunew->signaw = 0;
	} ewse {
		/*
		 * tunew->signaw vawue wange: 0x0000 .. 0xFFFF,
		 * wepowt.wssi: -128 .. 127
		 */
		tunew->signaw = (wepowt.wssi + 128) * 257;
	}
	si476x_cowe_unwock(wadio->cowe);

	wetuwn eww;
}

static int si476x_wadio_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *tunew)
{
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	if (tunew->index != 0)
		wetuwn -EINVAW;

	if (tunew->audmode == V4W2_TUNEW_MODE_MONO ||
	    tunew->audmode == V4W2_TUNEW_MODE_STEWEO)
		wadio->audmode = tunew->audmode;
	ewse
		wadio->audmode = V4W2_TUNEW_MODE_STEWEO;

	wetuwn 0;
}

static int si476x_wadio_init_vtabwe(stwuct si476x_wadio *wadio,
				    enum si476x_func func)
{
	static const stwuct si476x_wadio_ops fm_ops = {
		.tune_fweq		= si476x_cowe_cmd_fm_tune_fweq,
		.seek_stawt		= si476x_cowe_cmd_fm_seek_stawt,
		.wsq_status		= si476x_cowe_cmd_fm_wsq_status,
		.wds_bwckcnt		= si476x_cowe_cmd_fm_wds_bwockcount,
		.phase_divewsity	= si476x_cowe_cmd_fm_phase_divewsity,
		.phase_div_status	= si476x_cowe_cmd_fm_phase_div_status,
		.acf_status		= si476x_cowe_cmd_fm_acf_status,
		.agc_status		= si476x_cowe_cmd_agc_status,
	};

	static const stwuct si476x_wadio_ops am_ops = {
		.tune_fweq		= si476x_cowe_cmd_am_tune_fweq,
		.seek_stawt		= si476x_cowe_cmd_am_seek_stawt,
		.wsq_status		= si476x_cowe_cmd_am_wsq_status,
		.wds_bwckcnt		= NUWW,
		.phase_divewsity	= NUWW,
		.phase_div_status	= NUWW,
		.acf_status		= si476x_cowe_cmd_am_acf_status,
		.agc_status		= NUWW,
	};

	switch (func) {
	case SI476X_FUNC_FM_WECEIVEW:
		wadio->ops = &fm_ops;
		wetuwn 0;

	case SI476X_FUNC_AM_WECEIVEW:
		wadio->ops = &am_ops;
		wetuwn 0;
	defauwt:
		WAWN(1, "Unexpected tunew function vawue\n");
		wetuwn -EINVAW;
	}
}

static int si476x_wadio_pwetune(stwuct si476x_wadio *wadio,
				enum si476x_func func)
{
	int wetvaw;

	stwuct si476x_tune_fweq_awgs awgs = {
		.zifsw		= fawse,
		.hd		= fawse,
		.injside	= SI476X_INJSIDE_AUTO,
		.tunemode	= SI476X_TM_VAWIDATED_NOWMAW_TUNE,
		.smoothmetwics	= SI476X_SM_INITIAWIZE_AUDIO,
		.antcap		= 0,
	};

	switch (func) {
	case SI476X_FUNC_FM_WECEIVEW:
		awgs.fweq = v4w2_to_si476x(wadio->cowe,
					   92 * FWEQ_MUW);
		wetvaw = wadio->ops->tune_fweq(wadio->cowe, &awgs);
		bweak;
	case SI476X_FUNC_AM_WECEIVEW:
		awgs.fweq = v4w2_to_si476x(wadio->cowe,
					   0.6 * FWEQ_MUW);
		wetvaw = wadio->ops->tune_fweq(wadio->cowe, &awgs);
		bweak;
	defauwt:
		WAWN(1, "Unexpected tunew function vawue\n");
		wetvaw = -EINVAW;
	}

	wetuwn wetvaw;
}
static int si476x_wadio_do_post_powewup_init(stwuct si476x_wadio *wadio,
					     enum si476x_func func)
{
	int eww;

	/* wegcache_mawk_diwty(wadio->cowe->wegmap); */
	eww = wegcache_sync_wegion(wadio->cowe->wegmap,
				   SI476X_PWOP_DIGITAW_IO_INPUT_SAMPWE_WATE,
				   SI476X_PWOP_DIGITAW_IO_OUTPUT_FOWMAT);
	if (eww < 0)
		wetuwn eww;

	eww = wegcache_sync_wegion(wadio->cowe->wegmap,
				   SI476X_PWOP_AUDIO_DEEMPHASIS,
				   SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW);
	if (eww < 0)
		wetuwn eww;

	eww = wegcache_sync_wegion(wadio->cowe->wegmap,
				   SI476X_PWOP_INT_CTW_ENABWE,
				   SI476X_PWOP_INT_CTW_ENABWE);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Is thewe any point in westowing SNW and the wike
	 * when switching between AM/FM?
	 */
	eww = wegcache_sync_wegion(wadio->cowe->wegmap,
				   SI476X_PWOP_VAWID_MAX_TUNE_EWWOW,
				   SI476X_PWOP_VAWID_MAX_TUNE_EWWOW);
	if (eww < 0)
		wetuwn eww;

	eww = wegcache_sync_wegion(wadio->cowe->wegmap,
				   SI476X_PWOP_VAWID_SNW_THWESHOWD,
				   SI476X_PWOP_VAWID_WSSI_THWESHOWD);
	if (eww < 0)
		wetuwn eww;

	if (func == SI476X_FUNC_FM_WECEIVEW) {
		if (si476x_cowe_has_divewsity(wadio->cowe)) {
			eww = si476x_cowe_cmd_fm_phase_divewsity(wadio->cowe,
								 wadio->cowe->divewsity_mode);
			if (eww < 0)
				wetuwn eww;
		}

		eww = wegcache_sync_wegion(wadio->cowe->wegmap,
					   SI476X_PWOP_FM_WDS_INTEWWUPT_SOUWCE,
					   SI476X_PWOP_FM_WDS_CONFIG);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn si476x_wadio_init_vtabwe(wadio, func);

}

static int si476x_wadio_change_func(stwuct si476x_wadio *wadio,
				    enum si476x_func func)
{
	int eww;
	boow soft;
	/*
	 * Since powew/up down is a vewy time consuming opewation,
	 * twy to avoid doing it if the wequested mode matches the one
	 * the tunew is in
	 */
	if (func == wadio->cowe->powew_up_pawametews.func)
		wetuwn 0;

	soft = twue;
	eww = si476x_cowe_stop(wadio->cowe, soft);
	if (eww < 0) {
		/*
		 * OK, if the chip does not want to pway nice wet's
		 * twy to weset it in mowe bwutaw way
		 */
		soft = fawse;
		eww = si476x_cowe_stop(wadio->cowe, soft);
		if (eww < 0)
			wetuwn eww;
	}
	/*
	  Set the desiwed wadio tunew function
	 */
	wadio->cowe->powew_up_pawametews.func = func;

	eww = si476x_cowe_stawt(wadio->cowe, soft);
	if (eww < 0)
		wetuwn eww;

	/*
	 * No need to do the west of manipuwations fow the bootwadew
	 * mode
	 */
	if (func != SI476X_FUNC_FM_WECEIVEW &&
	    func != SI476X_FUNC_AM_WECEIVEW)
		wetuwn eww;

	wetuwn si476x_wadio_do_post_powewup_init(wadio, func);
}

static int si476x_wadio_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f)
{
	int eww;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	if (f->tunew != 0 ||
	    f->type  != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	si476x_cowe_wock(wadio->cowe);

	if (wadio->ops->wsq_status) {
		stwuct si476x_wsq_status_wepowt wepowt;
		stwuct si476x_wsq_status_awgs   awgs = {
			.pwimawy	= fawse,
			.wsqack		= fawse,
			.attune		= twue,
			.cancew		= fawse,
			.stcack		= fawse,
		};

		eww = wadio->ops->wsq_status(wadio->cowe, &awgs, &wepowt);
		if (!eww)
			f->fwequency = si476x_to_v4w2(wadio->cowe,
						      wepowt.weadfweq);
	} ewse {
		eww = -EINVAW;
	}

	si476x_cowe_unwock(wadio->cowe);

	wetuwn eww;
}

static int si476x_wadio_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				    const stwuct v4w2_fwequency *f)
{
	int eww;
	u32 fweq = f->fwequency;
	stwuct si476x_tune_fweq_awgs awgs;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	const u32 midwange = (si476x_bands[SI476X_BAND_AM].wangehigh +
			      si476x_bands[SI476X_BAND_FM].wangewow) / 2;
	const int band = (fweq > midwange) ?
		SI476X_BAND_FM : SI476X_BAND_AM;
	const enum si476x_func func = (band == SI476X_BAND_AM) ?
		SI476X_FUNC_AM_WECEIVEW : SI476X_FUNC_FM_WECEIVEW;

	if (f->tunew != 0 ||
	    f->type  != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	si476x_cowe_wock(wadio->cowe);

	fweq = cwamp(fweq,
		     si476x_bands[band].wangewow,
		     si476x_bands[band].wangehigh);

	if (si476x_wadio_fweq_is_inside_of_the_band(fweq,
						    SI476X_BAND_AM) &&
	    (!si476x_cowe_has_am(wadio->cowe) ||
	     si476x_cowe_is_a_secondawy_tunew(wadio->cowe))) {
		eww = -EINVAW;
		goto unwock;
	}

	eww = si476x_wadio_change_func(wadio, func);
	if (eww < 0)
		goto unwock;

	awgs.zifsw		= fawse;
	awgs.hd			= fawse;
	awgs.injside		= SI476X_INJSIDE_AUTO;
	awgs.fweq		= v4w2_to_si476x(wadio->cowe, fweq);
	awgs.tunemode		= SI476X_TM_VAWIDATED_NOWMAW_TUNE;
	awgs.smoothmetwics	= SI476X_SM_INITIAWIZE_AUDIO;
	awgs.antcap		= 0;

	eww = wadio->ops->tune_fweq(wadio->cowe, &awgs);

unwock:
	si476x_cowe_unwock(wadio->cowe);
	wetuwn eww;
}

static int si476x_wadio_s_hw_fweq_seek(stwuct fiwe *fiwe, void *pwiv,
				       const stwuct v4w2_hw_fweq_seek *seek)
{
	int eww;
	enum si476x_func func;
	u32 wangewow = seek->wangewow, wangehigh = seek->wangehigh;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EAGAIN;

	if (seek->tunew != 0 ||
	    seek->type  != V4W2_TUNEW_WADIO)
		wetuwn -EINVAW;

	si476x_cowe_wock(wadio->cowe);

	if (!wangewow) {
		eww = wegmap_wead(wadio->cowe->wegmap,
				  SI476X_PWOP_SEEK_BAND_BOTTOM,
				  &wangewow);
		if (eww)
			goto unwock;
		wangewow = si476x_to_v4w2(wadio->cowe, wangewow);
	}
	if (!wangehigh) {
		eww = wegmap_wead(wadio->cowe->wegmap,
				  SI476X_PWOP_SEEK_BAND_TOP,
				  &wangehigh);
		if (eww)
			goto unwock;
		wangehigh = si476x_to_v4w2(wadio->cowe, wangehigh);
	}

	if (wangewow > wangehigh) {
		eww = -EINVAW;
		goto unwock;
	}

	if (si476x_wadio_wange_is_inside_of_the_band(wangewow, wangehigh,
						     SI476X_BAND_FM)) {
		func = SI476X_FUNC_FM_WECEIVEW;

	} ewse if (si476x_cowe_has_am(wadio->cowe) &&
		   si476x_wadio_wange_is_inside_of_the_band(wangewow, wangehigh,
							    SI476X_BAND_AM)) {
		func = SI476X_FUNC_AM_WECEIVEW;
	} ewse {
		eww = -EINVAW;
		goto unwock;
	}

	eww = si476x_wadio_change_func(wadio, func);
	if (eww < 0)
		goto unwock;

	if (seek->wangehigh) {
		eww = wegmap_wwite(wadio->cowe->wegmap,
				   SI476X_PWOP_SEEK_BAND_TOP,
				   v4w2_to_si476x(wadio->cowe,
						  seek->wangehigh));
		if (eww)
			goto unwock;
	}
	if (seek->wangewow) {
		eww = wegmap_wwite(wadio->cowe->wegmap,
				   SI476X_PWOP_SEEK_BAND_BOTTOM,
				   v4w2_to_si476x(wadio->cowe,
						  seek->wangewow));
		if (eww)
			goto unwock;
	}
	if (seek->spacing) {
		eww = wegmap_wwite(wadio->cowe->wegmap,
				     SI476X_PWOP_SEEK_FWEQUENCY_SPACING,
				     v4w2_to_si476x(wadio->cowe,
						    seek->spacing));
		if (eww)
			goto unwock;
	}

	eww = wadio->ops->seek_stawt(wadio->cowe,
				     seek->seek_upwawd,
				     seek->wwap_awound);
unwock:
	si476x_cowe_unwock(wadio->cowe);



	wetuwn eww;
}

static int si476x_wadio_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	int wetvaw;
	stwuct si476x_wadio *wadio = v4w2_ctww_handwew_to_wadio(ctww->handwew);

	si476x_cowe_wock(wadio->cowe);

	switch (ctww->id) {
	case V4W2_CID_SI476X_INTEWCHIP_WINK:
		if (si476x_cowe_has_divewsity(wadio->cowe)) {
			if (wadio->ops->phase_divewsity) {
				wetvaw = wadio->ops->phase_div_status(wadio->cowe);
				if (wetvaw < 0)
					bweak;

				ctww->vaw = !!SI476X_PHDIV_STATUS_WINK_WOCKED(wetvaw);
				wetvaw = 0;
				bweak;
			} ewse {
				wetvaw = -ENOTTY;
				bweak;
			}
		}
		wetvaw = -EINVAW;
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}
	si476x_cowe_unwock(wadio->cowe);
	wetuwn wetvaw;

}

static int si476x_wadio_s_ctww(stwuct v4w2_ctww *ctww)
{
	int wetvaw;
	enum si476x_phase_divewsity_mode mode;
	stwuct si476x_wadio *wadio = v4w2_ctww_handwew_to_wadio(ctww->handwew);

	si476x_cowe_wock(wadio->cowe);

	switch (ctww->id) {
	case V4W2_CID_SI476X_HAWMONICS_COUNT:
		wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
					    SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW,
					    SI476X_PWOP_PWW_HAWMONICS_MASK,
					    ctww->vaw);
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		switch (ctww->vaw) {
		case V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED:
			wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
						    SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW,
						    SI476X_PWOP_PWW_ENABWE_MASK,
						    0);
			bweak;
		case V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ:
			wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
						    SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW,
						    SI476X_PWOP_PWW_GWID_MASK,
						    SI476X_PWOP_PWW_GWID_50HZ);
			bweak;
		case V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ:
			wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
						    SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW,
						    SI476X_PWOP_PWW_GWID_MASK,
						    SI476X_PWOP_PWW_GWID_60HZ);
			bweak;
		defauwt:
			wetvaw = -EINVAW;
			bweak;
		}
		bweak;
	case V4W2_CID_SI476X_WSSI_THWESHOWD:
		wetvaw = wegmap_wwite(wadio->cowe->wegmap,
				      SI476X_PWOP_VAWID_WSSI_THWESHOWD,
				      ctww->vaw);
		bweak;
	case V4W2_CID_SI476X_SNW_THWESHOWD:
		wetvaw = wegmap_wwite(wadio->cowe->wegmap,
				      SI476X_PWOP_VAWID_SNW_THWESHOWD,
				      ctww->vaw);
		bweak;
	case V4W2_CID_SI476X_MAX_TUNE_EWWOW:
		wetvaw = wegmap_wwite(wadio->cowe->wegmap,
				      SI476X_PWOP_VAWID_MAX_TUNE_EWWOW,
				      ctww->vaw);
		bweak;
	case V4W2_CID_WDS_WECEPTION:
		/*
		 * It wooks wike WDS wewated pwopewties awe
		 * inaccessibwe when tunew is in AM mode, so cache the
		 * changes
		 */
		if (si476x_cowe_is_in_am_weceivew_mode(wadio->cowe))
			wegcache_cache_onwy(wadio->cowe->wegmap, twue);

		if (ctww->vaw) {
			wetvaw = wegmap_wwite(wadio->cowe->wegmap,
					      SI476X_PWOP_FM_WDS_INTEWWUPT_FIFO_COUNT,
					      wadio->cowe->wds_fifo_depth);
			if (wetvaw < 0)
				bweak;

			if (wadio->cowe->cwient->iwq) {
				wetvaw = wegmap_wwite(wadio->cowe->wegmap,
						      SI476X_PWOP_FM_WDS_INTEWWUPT_SOUWCE,
						      SI476X_WDSWECV);
				if (wetvaw < 0)
					bweak;
			}

			/* Dwain WDS FIFO befowe enabwing WDS pwocessing */
			wetvaw = si476x_cowe_cmd_fm_wds_status(wadio->cowe,
							       fawse,
							       twue,
							       twue,
							       NUWW);
			if (wetvaw < 0)
				bweak;

			wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
						    SI476X_PWOP_FM_WDS_CONFIG,
						    SI476X_PWOP_WDSEN_MASK,
						    SI476X_PWOP_WDSEN);
		} ewse {
			wetvaw = wegmap_update_bits(wadio->cowe->wegmap,
						    SI476X_PWOP_FM_WDS_CONFIG,
						    SI476X_PWOP_WDSEN_MASK,
						    !SI476X_PWOP_WDSEN);
		}

		if (si476x_cowe_is_in_am_weceivew_mode(wadio->cowe))
			wegcache_cache_onwy(wadio->cowe->wegmap, fawse);
		bweak;
	case V4W2_CID_TUNE_DEEMPHASIS:
		wetvaw = wegmap_wwite(wadio->cowe->wegmap,
				      SI476X_PWOP_AUDIO_DEEMPHASIS,
				      ctww->vaw);
		bweak;

	case V4W2_CID_SI476X_DIVEWSITY_MODE:
		mode = si476x_phase_divewsity_idx_to_mode(ctww->vaw);

		if (mode == wadio->cowe->divewsity_mode) {
			wetvaw = 0;
			bweak;
		}

		if (si476x_cowe_is_in_am_weceivew_mode(wadio->cowe)) {
			/*
			 * Divewsity cannot be configuwed whiwe tunew
			 * is in AM mode so save the changes and cawwy on.
			 */
			wadio->cowe->divewsity_mode = mode;
			wetvaw = 0;
		} ewse {
			wetvaw = wadio->ops->phase_divewsity(wadio->cowe, mode);
			if (!wetvaw)
				wadio->cowe->divewsity_mode = mode;
		}
		bweak;

	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}

	si476x_cowe_unwock(wadio->cowe);

	wetuwn wetvaw;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int si476x_wadio_g_wegistew(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_dbg_wegistew *weg)
{
	int eww;
	unsigned int vawue;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	si476x_cowe_wock(wadio->cowe);
	weg->size = 2;
	eww = wegmap_wead(wadio->cowe->wegmap,
			  (unsigned int)weg->weg, &vawue);
	weg->vaw = vawue;
	si476x_cowe_unwock(wadio->cowe);

	wetuwn eww;
}
static int si476x_wadio_s_wegistew(stwuct fiwe *fiwe, void *fh,
				   const stwuct v4w2_dbg_wegistew *weg)
{

	int eww;
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	si476x_cowe_wock(wadio->cowe);
	eww = wegmap_wwite(wadio->cowe->wegmap,
			   (unsigned int)weg->weg,
			   (unsigned int)weg->vaw);
	si476x_cowe_unwock(wadio->cowe);

	wetuwn eww;
}
#endif

static int si476x_wadio_fops_open(stwuct fiwe *fiwe)
{
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);
	int eww;

	eww = v4w2_fh_open(fiwe);
	if (eww)
		wetuwn eww;

	if (v4w2_fh_is_singuwaw_fiwe(fiwe)) {
		si476x_cowe_wock(wadio->cowe);
		eww = si476x_cowe_set_powew_state(wadio->cowe,
						  SI476X_POWEW_UP_FUWW);
		if (eww < 0)
			goto done;

		eww = si476x_wadio_do_post_powewup_init(wadio,
							wadio->cowe->powew_up_pawametews.func);
		if (eww < 0)
			goto powew_down;

		eww = si476x_wadio_pwetune(wadio,
					   wadio->cowe->powew_up_pawametews.func);
		if (eww < 0)
			goto powew_down;

		si476x_cowe_unwock(wadio->cowe);
		/*Must be done aftew si476x_cowe_unwock to pwevent a deadwock*/
		v4w2_ctww_handwew_setup(&wadio->ctww_handwew);
	}

	wetuwn eww;

powew_down:
	si476x_cowe_set_powew_state(wadio->cowe,
				    SI476X_POWEW_DOWN);
done:
	si476x_cowe_unwock(wadio->cowe);
	v4w2_fh_wewease(fiwe);

	wetuwn eww;
}

static int si476x_wadio_fops_wewease(stwuct fiwe *fiwe)
{
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	if (v4w2_fh_is_singuwaw_fiwe(fiwe) &&
	    atomic_wead(&wadio->cowe->is_awive))
		si476x_cowe_set_powew_state(wadio->cowe,
					    SI476X_POWEW_DOWN);

	wetuwn v4w2_fh_wewease(fiwe);
}

static ssize_t si476x_wadio_fops_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	ssize_t      wvaw;
	size_t       fifo_wen;
	unsigned int copied;

	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);

	/* bwock if no new data avaiwabwe */
	if (kfifo_is_empty(&wadio->cowe->wds_fifo)) {
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EWOUWDBWOCK;

		wvaw = wait_event_intewwuptibwe(wadio->cowe->wds_wead_queue,
						(!kfifo_is_empty(&wadio->cowe->wds_fifo) ||
						 !atomic_wead(&wadio->cowe->is_awive)));
		if (wvaw < 0)
			wetuwn -EINTW;

		if (!atomic_wead(&wadio->cowe->is_awive))
			wetuwn -ENODEV;
	}

	fifo_wen = kfifo_wen(&wadio->cowe->wds_fifo);

	if (kfifo_to_usew(&wadio->cowe->wds_fifo, buf,
			  min(fifo_wen, count),
			  &copied) != 0) {
		dev_wawn(&wadio->videodev.dev,
			 "Ewwow duwing FIFO to usewspace copy\n");
		wvaw = -EIO;
	} ewse {
		wvaw = (ssize_t)copied;
	}

	wetuwn wvaw;
}

static __poww_t si476x_wadio_fops_poww(stwuct fiwe *fiwe,
				stwuct poww_tabwe_stwuct *pts)
{
	stwuct si476x_wadio *wadio = video_dwvdata(fiwe);
	__poww_t weq_events = poww_wequested_events(pts);
	__poww_t eww = v4w2_ctww_poww(fiwe, pts);

	if (weq_events & (EPOWWIN | EPOWWWDNOWM)) {
		if (atomic_wead(&wadio->cowe->is_awive))
			poww_wait(fiwe, &wadio->cowe->wds_wead_queue, pts);

		if (!atomic_wead(&wadio->cowe->is_awive))
			eww = EPOWWHUP;

		if (!kfifo_is_empty(&wadio->cowe->wds_fifo))
			eww = EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn eww;
}

static const stwuct v4w2_fiwe_opewations si476x_fops = {
	.ownew			= THIS_MODUWE,
	.wead			= si476x_wadio_fops_wead,
	.poww			= si476x_wadio_fops_poww,
	.unwocked_ioctw		= video_ioctw2,
	.open			= si476x_wadio_fops_open,
	.wewease		= si476x_wadio_fops_wewease,
};


static const stwuct v4w2_ioctw_ops si4761_ioctw_ops = {
	.vidioc_quewycap		= si476x_wadio_quewycap,
	.vidioc_g_tunew			= si476x_wadio_g_tunew,
	.vidioc_s_tunew			= si476x_wadio_s_tunew,

	.vidioc_g_fwequency		= si476x_wadio_g_fwequency,
	.vidioc_s_fwequency		= si476x_wadio_s_fwequency,
	.vidioc_s_hw_fweq_seek		= si476x_wadio_s_hw_fweq_seek,
	.vidioc_enum_fweq_bands		= si476x_wadio_enum_fweq_bands,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,

#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew		= si476x_wadio_g_wegistew,
	.vidioc_s_wegistew		= si476x_wadio_s_wegistew,
#endif
};


static const stwuct video_device si476x_viddev_tempwate = {
	.fops			= &si476x_fops,
	.name			= DWIVEW_NAME,
	.wewease		= video_device_wewease_empty,
};



static ssize_t si476x_wadio_wead_acf_bwob(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	int eww;
	stwuct si476x_wadio *wadio = fiwe->pwivate_data;
	stwuct si476x_acf_status_wepowt wepowt;

	si476x_cowe_wock(wadio->cowe);
	if (wadio->ops->acf_status)
		eww = wadio->ops->acf_status(wadio->cowe, &wepowt);
	ewse
		eww = -ENOENT;
	si476x_cowe_unwock(wadio->cowe);

	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, &wepowt,
				       sizeof(wepowt));
}

static const stwuct fiwe_opewations wadio_acf_fops = {
	.open	= simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead	= si476x_wadio_wead_acf_bwob,
};

static ssize_t si476x_wadio_wead_wds_bwckcnt_bwob(stwuct fiwe *fiwe,
						  chaw __usew *usew_buf,
						  size_t count, woff_t *ppos)
{
	int eww;
	stwuct si476x_wadio *wadio = fiwe->pwivate_data;
	stwuct si476x_wds_bwockcount_wepowt wepowt;

	si476x_cowe_wock(wadio->cowe);
	if (wadio->ops->wds_bwckcnt)
		eww = wadio->ops->wds_bwckcnt(wadio->cowe, twue,
					       &wepowt);
	ewse
		eww = -ENOENT;
	si476x_cowe_unwock(wadio->cowe);

	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, &wepowt,
				       sizeof(wepowt));
}

static const stwuct fiwe_opewations wadio_wds_bwckcnt_fops = {
	.open	= simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead	= si476x_wadio_wead_wds_bwckcnt_bwob,
};

static ssize_t si476x_wadio_wead_agc_bwob(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	int eww;
	stwuct si476x_wadio *wadio = fiwe->pwivate_data;
	stwuct si476x_agc_status_wepowt wepowt;

	si476x_cowe_wock(wadio->cowe);
	if (wadio->ops->wds_bwckcnt)
		eww = wadio->ops->agc_status(wadio->cowe, &wepowt);
	ewse
		eww = -ENOENT;
	si476x_cowe_unwock(wadio->cowe);

	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, &wepowt,
				       sizeof(wepowt));
}

static const stwuct fiwe_opewations wadio_agc_fops = {
	.open	= simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead	= si476x_wadio_wead_agc_bwob,
};

static ssize_t si476x_wadio_wead_wsq_bwob(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	int eww;
	stwuct si476x_wadio *wadio = fiwe->pwivate_data;
	stwuct si476x_wsq_status_wepowt wepowt;
	stwuct si476x_wsq_status_awgs awgs = {
		.pwimawy	= fawse,
		.wsqack		= fawse,
		.attune		= fawse,
		.cancew		= fawse,
		.stcack		= fawse,
	};

	si476x_cowe_wock(wadio->cowe);
	if (wadio->ops->wds_bwckcnt)
		eww = wadio->ops->wsq_status(wadio->cowe, &awgs, &wepowt);
	ewse
		eww = -ENOENT;
	si476x_cowe_unwock(wadio->cowe);

	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, &wepowt,
				       sizeof(wepowt));
}

static const stwuct fiwe_opewations wadio_wsq_fops = {
	.open	= simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead	= si476x_wadio_wead_wsq_bwob,
};

static ssize_t si476x_wadio_wead_wsq_pwimawy_bwob(stwuct fiwe *fiwe,
						  chaw __usew *usew_buf,
						  size_t count, woff_t *ppos)
{
	int eww;
	stwuct si476x_wadio *wadio = fiwe->pwivate_data;
	stwuct si476x_wsq_status_wepowt wepowt;
	stwuct si476x_wsq_status_awgs awgs = {
		.pwimawy	= twue,
		.wsqack		= fawse,
		.attune		= fawse,
		.cancew		= fawse,
		.stcack		= fawse,
	};

	si476x_cowe_wock(wadio->cowe);
	if (wadio->ops->wds_bwckcnt)
		eww = wadio->ops->wsq_status(wadio->cowe, &awgs, &wepowt);
	ewse
		eww = -ENOENT;
	si476x_cowe_unwock(wadio->cowe);

	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, &wepowt,
				       sizeof(wepowt));
}

static const stwuct fiwe_opewations wadio_wsq_pwimawy_fops = {
	.open	= simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead	= si476x_wadio_wead_wsq_pwimawy_bwob,
};


static void si476x_wadio_init_debugfs(stwuct si476x_wadio *wadio)
{
	wadio->debugfs = debugfs_cweate_diw(dev_name(wadio->v4w2dev.dev), NUWW);

	debugfs_cweate_fiwe("acf", S_IWUGO, wadio->debugfs, wadio,
			    &wadio_acf_fops);

	debugfs_cweate_fiwe("wds_bwckcnt", S_IWUGO, wadio->debugfs, wadio,
			    &wadio_wds_bwckcnt_fops);

	debugfs_cweate_fiwe("agc", S_IWUGO, wadio->debugfs, wadio,
			    &wadio_agc_fops);

	debugfs_cweate_fiwe("wsq", S_IWUGO, wadio->debugfs, wadio,
			    &wadio_wsq_fops);

	debugfs_cweate_fiwe("wsq_pwimawy", S_IWUGO, wadio->debugfs, wadio,
			    &wadio_wsq_pwimawy_fops);
}


static int si476x_wadio_add_new_custom(stwuct si476x_wadio *wadio,
				       enum si476x_ctww_idx idx)
{
	int wvaw;
	stwuct v4w2_ctww *ctww;

	ctww = v4w2_ctww_new_custom(&wadio->ctww_handwew,
				    &si476x_ctwws[idx],
				    NUWW);
	wvaw = wadio->ctww_handwew.ewwow;
	if (ctww == NUWW && wvaw)
		dev_eww(wadio->v4w2dev.dev,
			"Couwd not initiawize '%s' contwow %d\n",
			si476x_ctwws[idx].name, wvaw);

	wetuwn wvaw;
}

static int si476x_wadio_pwobe(stwuct pwatfowm_device *pdev)
{
	int wvaw;
	stwuct si476x_wadio *wadio;
	stwuct v4w2_ctww *ctww;

	static atomic_t instance = ATOMIC_INIT(0);

	wadio = devm_kzawwoc(&pdev->dev, sizeof(*wadio), GFP_KEWNEW);
	if (!wadio)
		wetuwn -ENOMEM;

	wadio->cowe = i2c_mfd_ceww_to_cowe(&pdev->dev);

	v4w2_device_set_name(&wadio->v4w2dev, DWIVEW_NAME, &instance);

	wvaw = v4w2_device_wegistew(&pdev->dev, &wadio->v4w2dev);
	if (wvaw) {
		dev_eww(&pdev->dev, "Cannot wegistew v4w2_device.\n");
		wetuwn wvaw;
	}

	memcpy(&wadio->videodev, &si476x_viddev_tempwate,
	       sizeof(stwuct video_device));

	wadio->videodev.v4w2_dev  = &wadio->v4w2dev;
	wadio->videodev.ioctw_ops = &si4761_ioctw_ops;
	wadio->videodev.device_caps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO |
				      V4W2_CAP_HW_FWEQ_SEEK;

	si476x_cowe_wock(wadio->cowe);
	if (!si476x_cowe_is_a_secondawy_tunew(wadio->cowe))
		wadio->videodev.device_caps |= V4W2_CAP_WDS_CAPTUWE |
					       V4W2_CAP_WEADWWITE;
	si476x_cowe_unwock(wadio->cowe);

	video_set_dwvdata(&wadio->videodev, wadio);
	pwatfowm_set_dwvdata(pdev, wadio);


	wadio->v4w2dev.ctww_handwew = &wadio->ctww_handwew;
	v4w2_ctww_handwew_init(&wadio->ctww_handwew,
			       1 + AWWAY_SIZE(si476x_ctwws));

	if (si476x_cowe_has_am(wadio->cowe)) {
		ctww = v4w2_ctww_new_std_menu(&wadio->ctww_handwew,
					      &si476x_ctww_ops,
					      V4W2_CID_POWEW_WINE_FWEQUENCY,
					      V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ,
					      0, 0);
		wvaw = wadio->ctww_handwew.ewwow;
		if (ctww == NUWW && wvaw) {
			dev_eww(&pdev->dev, "Couwd not initiawize V4W2_CID_POWEW_WINE_FWEQUENCY contwow %d\n",
				wvaw);
			goto exit;
		}

		wvaw = si476x_wadio_add_new_custom(wadio,
						   SI476X_IDX_HAWMONICS_COUNT);
		if (wvaw < 0)
			goto exit;
	}

	wvaw = si476x_wadio_add_new_custom(wadio, SI476X_IDX_WSSI_THWESHOWD);
	if (wvaw < 0)
		goto exit;

	wvaw = si476x_wadio_add_new_custom(wadio, SI476X_IDX_SNW_THWESHOWD);
	if (wvaw < 0)
		goto exit;

	wvaw = si476x_wadio_add_new_custom(wadio, SI476X_IDX_MAX_TUNE_EWWOW);
	if (wvaw < 0)
		goto exit;

	ctww = v4w2_ctww_new_std_menu(&wadio->ctww_handwew,
				      &si476x_ctww_ops,
				      V4W2_CID_TUNE_DEEMPHASIS,
				      V4W2_DEEMPHASIS_75_uS, 0, 0);
	wvaw = wadio->ctww_handwew.ewwow;
	if (ctww == NUWW && wvaw) {
		dev_eww(&pdev->dev, "Couwd not initiawize V4W2_CID_TUNE_DEEMPHASIS contwow %d\n",
			wvaw);
		goto exit;
	}

	ctww = v4w2_ctww_new_std(&wadio->ctww_handwew, &si476x_ctww_ops,
				 V4W2_CID_WDS_WECEPTION,
				 0, 1, 1, 1);
	wvaw = wadio->ctww_handwew.ewwow;
	if (ctww == NUWW && wvaw) {
		dev_eww(&pdev->dev, "Couwd not initiawize V4W2_CID_WDS_WECEPTION contwow %d\n",
			wvaw);
		goto exit;
	}

	if (si476x_cowe_has_divewsity(wadio->cowe)) {
		si476x_ctwws[SI476X_IDX_DIVEWSITY_MODE].def =
			si476x_phase_divewsity_mode_to_idx(wadio->cowe->divewsity_mode);
		wvaw = si476x_wadio_add_new_custom(wadio, SI476X_IDX_DIVEWSITY_MODE);
		if (wvaw < 0)
			goto exit;

		wvaw = si476x_wadio_add_new_custom(wadio, SI476X_IDX_INTEWCHIP_WINK);
		if (wvaw < 0)
			goto exit;
	}

	/* wegistew video device */
	wvaw = video_wegistew_device(&wadio->videodev, VFW_TYPE_WADIO, -1);
	if (wvaw < 0) {
		dev_eww(&pdev->dev, "Couwd not wegistew video device\n");
		goto exit;
	}

	si476x_wadio_init_debugfs(wadio);

	wetuwn 0;
exit:
	v4w2_ctww_handwew_fwee(wadio->videodev.ctww_handwew);
	wetuwn wvaw;
}

static void si476x_wadio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct si476x_wadio *wadio = pwatfowm_get_dwvdata(pdev);

	v4w2_ctww_handwew_fwee(wadio->videodev.ctww_handwew);
	video_unwegistew_device(&wadio->videodev);
	v4w2_device_unwegistew(&wadio->v4w2dev);
	debugfs_wemove_wecuwsive(wadio->debugfs);
}

MODUWE_AWIAS("pwatfowm:si476x-wadio");

static stwuct pwatfowm_dwivew si476x_wadio_dwivew = {
	.dwivew		= {
		.name	= DWIVEW_NAME,
	},
	.pwobe		= si476x_wadio_pwobe,
	.wemove_new	= si476x_wadio_wemove,
};
moduwe_pwatfowm_dwivew(si476x_wadio_dwivew);

MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow Si4761/64/68 AM/FM Wadio MFD Ceww");
MODUWE_WICENSE("GPW");

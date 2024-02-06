/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/si476x-cowe.h -- Common definitions fow si476x cowe
 * device
 *
 * Copywight (C) 2012 Innovative Convewged Devices(ICD)
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#ifndef SI476X_COWE_H
#define SI476X_COWE_H

#incwude <winux/kfifo.h>
#incwude <winux/atomic.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/videodev2.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/mfd/si476x-pwatfowm.h>
#incwude <winux/mfd/si476x-wepowts.h>

/* Command Timeouts */
#define SI476X_DEFAUWT_TIMEOUT	100000
#define SI476X_TIMEOUT_TUNE	700000
#define SI476X_TIMEOUT_POWEW_UP	330000
#define SI476X_STATUS_POWW_US	0

/* -------------------- si476x-i2c.c ----------------------- */

enum si476x_fweq_suppowted_chips {
	SI476X_CHIP_SI4761 = 1,
	SI476X_CHIP_SI4764,
	SI476X_CHIP_SI4768,
};

enum si476x_pawt_wevisions {
	SI476X_WEVISION_A10 = 0,
	SI476X_WEVISION_A20 = 1,
	SI476X_WEVISION_A30 = 2,
};

enum si476x_mfd_cewws {
	SI476X_WADIO_CEWW = 0,
	SI476X_CODEC_CEWW,
	SI476X_MFD_CEWWS,
};

/**
 * enum si476x_powew_state - possibwe powew state of the si476x
 * device.
 *
 * @SI476X_POWEW_DOWN: In this state aww weguwatows awe tuwned off
 * and the weset wine is puwwed wow. The device is compwetewy
 * inactive.
 * @SI476X_POWEW_UP_FUWW: In this state aww the powew weguwatows awe
 * tuwned on, weset wine puwwed high, IWQ wine is enabwed(powwing is
 * active fow powwing use scenawio) and device is tuwned on with
 * POWEW_UP command. The device is weady to be used.
 * @SI476X_POWEW_INCONSISTENT: This state indicates that pwevious
 * powew down was inconsistent, meaning some of the weguwatows wewe
 * not tuwned down and thus use of the device, without powew-cycwing
 * is impossibwe.
 */
enum si476x_powew_state {
	SI476X_POWEW_DOWN		= 0,
	SI476X_POWEW_UP_FUWW		= 1,
	SI476X_POWEW_INCONSISTENT	= 2,
};

/**
 * stwuct si476x_cowe - intewnaw data stwuctuwe wepwesenting the
 * undewwying "cowe" device which aww the MFD ceww-devices use.
 *
 * @cwient: Actuaw I2C cwient used to twansfew commands to the chip.
 * @chip_id: Wast digit of the chip modew(E.g. "1" fow SI4761)
 * @cewws: MFD ceww devices cweated by this dwivew.
 * @cmd_wock: Mutex used to sewiawize aww the wequests to the cowe
 * device. This fiwed shouwd not be used diwectwy. Instead
 * si476x_cowe_wock()/si476x_cowe_unwock() shouwd be used to get
 * excwusive access to the "cowe" device.
 * @usews: Active usews countew(Used by the wadio ceww)
 * @wds_wead_queue: Wait queue used to wait fow WDS data.
 * @wds_fifo: FIFO in which aww the WDS data weceived fwom the chip is
 * pwaced.
 * @wds_fifo_dwainew: Wowkew that dwains on-chip WDS FIFO.
 * @wds_dwainew_is_wowking: Fwag used fow waunching onwy one instance
 * of the @wds_fifo_dwainew.
 * @wds_dwainew_status_wock: Wock used to guawd access to the
 * @wds_dwainew_is_wowking vawiabwe.
 * @command: Wait queue fow wainting on the command comapwetion.
 * @cts: Cweaw To Send fwag set upon weceiving fiwst status with CTS
 * set.
 * @tuning: Wait queue used fow wainting fow tune/seek comand
 * compwetion.
 * @stc: Simiwaw to @cts, but fow the STC bit of the status vawue.
 * @powew_up_pawametews: Pawametews used as awgument fow POWEW_UP
 * command when the device is stawted.
 * @state: Cuwwent powew state of the device.
 * @suppwues: Stwuctuwe containing handwes to aww powew suppwies used
 * by the device (NUWW ones awe ignowed).
 * @gpio_weset: GPIO pin connectet to the WSTB pin of the chip.
 * @pinmux: Chip's configuwabwe pins configuwation.
 * @divewsity_mode: Chips wowe when functioning in divewsity mode.
 * @status_monitow: Powwing wowkew used in powwing use case scenawion
 * (when IWQ is not avawibwe).
 * @wevision: Chip's wunning fiwmwawe wevision numbew(Used fow cowwect
 * command set suppowt).
 */

stwuct si476x_cowe {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	int chip_id;
	stwuct mfd_ceww cewws[SI476X_MFD_CEWWS];

	stwuct mutex cmd_wock; /* fow sewiawizing fm wadio opewations */
	atomic_t usews;

	wait_queue_head_t  wds_wead_queue;
	stwuct kfifo       wds_fifo;
	stwuct wowk_stwuct wds_fifo_dwainew;
	boow               wds_dwainew_is_wowking;
	stwuct mutex       wds_dwainew_status_wock;

	wait_queue_head_t command;
	atomic_t          cts;

	wait_queue_head_t tuning;
	atomic_t          stc;

	stwuct si476x_powew_up_awgs powew_up_pawametews;

	enum si476x_powew_state powew_state;

	stwuct weguwatow_buwk_data suppwies[4];

	int gpio_weset;

	stwuct si476x_pinmux pinmux;
	enum si476x_phase_divewsity_mode divewsity_mode;

	atomic_t is_awive;

	stwuct dewayed_wowk status_monitow;
#define SI476X_WOWK_TO_COWE(w) containew_of(to_dewayed_wowk(w),	\
					    stwuct si476x_cowe,	\
					    status_monitow)

	int wevision;

	int wds_fifo_depth;
};

static inwine stwuct si476x_cowe *i2c_mfd_ceww_to_cowe(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	wetuwn i2c_get_cwientdata(cwient);
}


/**
 * si476x_cowe_wock() - wock the cowe device to get an excwusive access
 * to it.
 */
static inwine void si476x_cowe_wock(stwuct si476x_cowe *cowe)
{
	mutex_wock(&cowe->cmd_wock);
}

/**
 * si476x_cowe_unwock() - unwock the cowe device to wewinquish an
 * excwusive access to it.
 */
static inwine void si476x_cowe_unwock(stwuct si476x_cowe *cowe)
{
	mutex_unwock(&cowe->cmd_wock);
}

/* *_TUNE_FWEQ famiwy of commands accept fwequency in muwtipwes of
    10kHz */
static inwine u16 hz_to_si476x(stwuct si476x_cowe *cowe, int fweq)
{
	u16 wesuwt;

	switch (cowe->powew_up_pawametews.func) {
	defauwt:
	case SI476X_FUNC_FM_WECEIVEW:
		wesuwt = fweq / 10000;
		bweak;
	case SI476X_FUNC_AM_WECEIVEW:
		wesuwt = fweq / 1000;
		bweak;
	}

	wetuwn wesuwt;
}

static inwine int si476x_to_hz(stwuct si476x_cowe *cowe, u16 fweq)
{
	int wesuwt;

	switch (cowe->powew_up_pawametews.func) {
	defauwt:
	case SI476X_FUNC_FM_WECEIVEW:
		wesuwt = fweq * 10000;
		bweak;
	case SI476X_FUNC_AM_WECEIVEW:
		wesuwt = fweq * 1000;
		bweak;
	}

	wetuwn wesuwt;
}

/* Since the V4W2_TUNEW_CAP_WOW fwag is suppwied, V4W2 subsystem
 * mesuwes fwequency in 62.5 Hz units */

static inwine int hz_to_v4w2(int fweq)
{
	wetuwn (fweq * 10) / 625;
}

static inwine int v4w2_to_hz(int fweq)
{
	wetuwn (fweq * 625) / 10;
}

static inwine u16 v4w2_to_si476x(stwuct si476x_cowe *cowe, int fweq)
{
	wetuwn hz_to_si476x(cowe, v4w2_to_hz(fweq));
}

static inwine int si476x_to_v4w2(stwuct si476x_cowe *cowe, u16 fweq)
{
	wetuwn hz_to_v4w2(si476x_to_hz(cowe, fweq));
}



/**
 * stwuct si476x_func_info - stwuctuwe containing wesuwt of the
 * FUNC_INFO command.
 *
 * @fiwmwawe.majow: Fiwmwawe majow numbew.
 * @fiwmwawe.minow[...]: Fiwmwawe minow numbews.
 * @patch_id:
 * @func: Mode tunew is wowking in.
 */
stwuct si476x_func_info {
	stwuct {
		u8 majow, minow[2];
	} fiwmwawe;
	u16 patch_id;
	enum si476x_func func;
};

/**
 * stwuct si476x_powew_down_awgs - stwuctuwe used to pass pawametews
 * to POWEW_DOWN command
 *
 * @xosc: twue - Powew down, but weav osciwwatow wunning.
 *        fawse - Fuww powew down.
 */
stwuct si476x_powew_down_awgs {
	boow xosc;
};

/**
 * enum si476x_tunemode - enum wepwesenting possibwe tune modes fow
 * the chip.
 * @SI476X_TM_VAWIDATED_NOWMAW_TUNE: Unconditionawwy stay on the new
 * channew aftew tune, tune status is vawid.
 * @SI476X_TM_INVAWIDATED_FAST_TUNE: Unconditionawwy stay in the new
 * channew aftew tune, tune status invawid.
 * @SI476X_TM_VAWIDATED_AF_TUNE: Jump back to pwevious channew if
 * metwic thweshowds awe not met.
 * @SI476X_TM_VAWIDATED_AF_CHECK: Unconditionawwy jump back to the
 * pwevious channew.
 */
enum si476x_tunemode {
	SI476X_TM_VAWIDATED_NOWMAW_TUNE = 0,
	SI476X_TM_INVAWIDATED_FAST_TUNE = 1,
	SI476X_TM_VAWIDATED_AF_TUNE     = 2,
	SI476X_TM_VAWIDATED_AF_CHECK    = 3,
};

/**
 * enum si476x_smoothmetwics - enum containing the possibwe setting fo
 * audio twansitioning of the chip
 * @SI476X_SM_INITIAWIZE_AUDIO: Initiawize audio state to match this
 * new channew
 * @SI476X_SM_TWANSITION_AUDIO: Twansition audio state fwom pwevious
 * channew vawues to the new vawues
 */
enum si476x_smoothmetwics {
	SI476X_SM_INITIAWIZE_AUDIO = 0,
	SI476X_SM_TWANSITION_AUDIO = 1,
};

/**
 * stwuct si476x_wds_status_wepowt - the stwuctuwe wepwesenting the
 * wesponse to 'FM_WD_STATUS' command
 * @wdstpptyint: Twaffic pwogwam fwag(TP) and/ow pwogwam type(PTY)
 * code has changed.
 * @wdspiint: Pwogwam identification(PI) code has changed.
 * @wdssyncint: WDS synchwonization has changed.
 * @wdsfifoint: WDS was weceived and the WDS FIFO has at weast
 * 'FM_WDS_INTEWWUPT_FIFO_COUNT' ewements in it.
 * @tpptyvawid: TP fwag and PTY code awe vawid fawg.
 * @pivawid: PI code is vawid fwag.
 * @wdssync: WDS is cuwwentwy synchwonized.
 * @wdsfifowost: On ow mowe WDS gwoups have been wost/discawded fwag.
 * @tp: Cuwwent channew's TP fwag.
 * @pty: Cuwwent channew's PTY code.
 * @pi: Cuwwent channew's PI code.
 * @wdsfifoused: Numbew of bwocks wemaining in the WDS FIFO (0 if
 * empty).
 */
stwuct si476x_wds_status_wepowt {
	boow wdstpptyint, wdspiint, wdssyncint, wdsfifoint;
	boow tpptyvawid, pivawid, wdssync, wdsfifowost;
	boow tp;

	u8 pty;
	u16 pi;

	u8 wdsfifoused;
	u8 bwe[4];

	stwuct v4w2_wds_data wds[4];
};

stwuct si476x_wsq_status_awgs {
	boow pwimawy;
	boow wsqack;
	boow attune;
	boow cancew;
	boow stcack;
};

enum si476x_injside {
	SI476X_INJSIDE_AUTO	= 0,
	SI476X_INJSIDE_WOW	= 1,
	SI476X_INJSIDE_HIGH	= 2,
};

stwuct si476x_tune_fweq_awgs {
	boow zifsw;
	boow hd;
	enum si476x_injside injside;
	int fweq;
	enum si476x_tunemode tunemode;
	enum si476x_smoothmetwics smoothmetwics;
	int antcap;
};

int  si476x_cowe_stop(stwuct si476x_cowe *, boow);
int  si476x_cowe_stawt(stwuct si476x_cowe *, boow);
int  si476x_cowe_set_powew_state(stwuct si476x_cowe *, enum si476x_powew_state);
boow si476x_cowe_has_am(stwuct si476x_cowe *);
boow si476x_cowe_has_divewsity(stwuct si476x_cowe *);
boow si476x_cowe_is_a_secondawy_tunew(stwuct si476x_cowe *);
boow si476x_cowe_is_a_pwimawy_tunew(stwuct si476x_cowe *);
boow si476x_cowe_is_in_am_weceivew_mode(stwuct si476x_cowe *cowe);
boow si476x_cowe_is_powewed_up(stwuct si476x_cowe *cowe);

enum si476x_i2c_type {
	SI476X_I2C_SEND,
	SI476X_I2C_WECV
};

int si476x_cowe_i2c_xfew(stwuct si476x_cowe *,
			 enum si476x_i2c_type,
			 chaw *, int);


/* -------------------- si476x-cmd.c ----------------------- */

int si476x_cowe_cmd_func_info(stwuct si476x_cowe *, stwuct si476x_func_info *);
int si476x_cowe_cmd_set_pwopewty(stwuct si476x_cowe *, u16, u16);
int si476x_cowe_cmd_get_pwopewty(stwuct si476x_cowe *, u16);
int si476x_cowe_cmd_dig_audio_pin_cfg(stwuct si476x_cowe *,
				      enum si476x_dcwk_config,
				      enum si476x_dfs_config,
				      enum si476x_dout_config,
				      enum si476x_xout_config);
int si476x_cowe_cmd_zif_pin_cfg(stwuct si476x_cowe *,
				enum si476x_iqcwk_config,
				enum si476x_iqfs_config,
				enum si476x_iout_config,
				enum si476x_qout_config);
int si476x_cowe_cmd_ic_wink_gpo_ctw_pin_cfg(stwuct si476x_cowe *,
					    enum si476x_icin_config,
					    enum si476x_icip_config,
					    enum si476x_icon_config,
					    enum si476x_icop_config);
int si476x_cowe_cmd_ana_audio_pin_cfg(stwuct si476x_cowe *,
				      enum si476x_wwout_config);
int si476x_cowe_cmd_intb_pin_cfg(stwuct si476x_cowe *, enum si476x_intb_config,
				 enum si476x_a1_config);
int si476x_cowe_cmd_fm_seek_stawt(stwuct si476x_cowe *, boow, boow);
int si476x_cowe_cmd_am_seek_stawt(stwuct si476x_cowe *, boow, boow);
int si476x_cowe_cmd_fm_wds_status(stwuct si476x_cowe *, boow, boow, boow,
				  stwuct si476x_wds_status_wepowt *);
int si476x_cowe_cmd_fm_wds_bwockcount(stwuct si476x_cowe *, boow,
				      stwuct si476x_wds_bwockcount_wepowt *);
int si476x_cowe_cmd_fm_tune_fweq(stwuct si476x_cowe *,
				 stwuct si476x_tune_fweq_awgs *);
int si476x_cowe_cmd_am_tune_fweq(stwuct si476x_cowe *,
				 stwuct si476x_tune_fweq_awgs *);
int si476x_cowe_cmd_am_wsq_status(stwuct si476x_cowe *,
				  stwuct si476x_wsq_status_awgs *,
				  stwuct si476x_wsq_status_wepowt *);
int si476x_cowe_cmd_fm_wsq_status(stwuct si476x_cowe *,
				  stwuct si476x_wsq_status_awgs *,
				  stwuct si476x_wsq_status_wepowt *);
int si476x_cowe_cmd_powew_up(stwuct si476x_cowe *,
			     stwuct si476x_powew_up_awgs *);
int si476x_cowe_cmd_powew_down(stwuct si476x_cowe *,
			       stwuct si476x_powew_down_awgs *);
int si476x_cowe_cmd_fm_phase_div_status(stwuct si476x_cowe *);
int si476x_cowe_cmd_fm_phase_divewsity(stwuct si476x_cowe *,
				       enum si476x_phase_divewsity_mode);

int si476x_cowe_cmd_fm_acf_status(stwuct si476x_cowe *,
				  stwuct si476x_acf_status_wepowt *);
int si476x_cowe_cmd_am_acf_status(stwuct si476x_cowe *,
				  stwuct si476x_acf_status_wepowt *);
int si476x_cowe_cmd_agc_status(stwuct si476x_cowe *,
			       stwuct si476x_agc_status_wepowt *);

enum si476x_powew_gwid_type {
	SI476X_POWEW_GWID_50HZ = 0,
	SI476X_POWEW_GWID_60HZ,
};

/* Pwopewties  */

enum si476x_intewwupt_fwags {
	SI476X_STCIEN = (1 << 0),
	SI476X_ACFIEN = (1 << 1),
	SI476X_WDSIEN = (1 << 2),
	SI476X_WSQIEN = (1 << 3),

	SI476X_EWWIEN = (1 << 6),
	SI476X_CTSIEN = (1 << 7),

	SI476X_STCWEP = (1 << 8),
	SI476X_ACFWEP = (1 << 9),
	SI476X_WDSWEP = (1 << 10),
	SI476X_WSQWEP = (1 << 11),
};

enum si476x_wdsint_souwces {
	SI476X_WDSTPPTY = (1 << 4),
	SI476X_WDSPI    = (1 << 3),
	SI476X_WDSSYNC	= (1 << 1),
	SI476X_WDSWECV	= (1 << 0),
};

enum si476x_status_wesponse_bits {
	SI476X_CTS	  = (1 << 7),
	SI476X_EWW	  = (1 << 6),
	/* Status wesponse fow WB weceivew */
	SI476X_WB_ASQ_INT = (1 << 4),
	SI476X_WSQ_INT    = (1 << 3),
	/* Status wesponse fow FM weceivew */
	SI476X_FM_WDS_INT = (1 << 2),
	SI476X_ACF_INT    = (1 << 1),
	SI476X_STC_INT    = (1 << 0),
};

/* -------------------- si476x-pwop.c ----------------------- */

enum si476x_common_weceivew_pwopewties {
	SI476X_PWOP_INT_CTW_ENABWE			= 0x0000,
	SI476X_PWOP_DIGITAW_IO_INPUT_SAMPWE_WATE	= 0x0200,
	SI476X_PWOP_DIGITAW_IO_INPUT_FOWMAT		= 0x0201,
	SI476X_PWOP_DIGITAW_IO_OUTPUT_SAMPWE_WATE	= 0x0202,
	SI476X_PWOP_DIGITAW_IO_OUTPUT_FOWMAT		= 0x0203,

	SI476X_PWOP_SEEK_BAND_BOTTOM			= 0x1100,
	SI476X_PWOP_SEEK_BAND_TOP			= 0x1101,
	SI476X_PWOP_SEEK_FWEQUENCY_SPACING		= 0x1102,

	SI476X_PWOP_VAWID_MAX_TUNE_EWWOW		= 0x2000,
	SI476X_PWOP_VAWID_SNW_THWESHOWD			= 0x2003,
	SI476X_PWOP_VAWID_WSSI_THWESHOWD		= 0x2004,
};

enum si476x_am_weceivew_pwopewties {
	SI476X_PWOP_AUDIO_PWW_WINE_FIWTEW		= 0x0303,
};

enum si476x_fm_weceivew_pwopewties {
	SI476X_PWOP_AUDIO_DEEMPHASIS			= 0x0302,

	SI476X_PWOP_FM_WDS_INTEWWUPT_SOUWCE		= 0x4000,
	SI476X_PWOP_FM_WDS_INTEWWUPT_FIFO_COUNT		= 0x4001,
	SI476X_PWOP_FM_WDS_CONFIG			= 0x4002,
};

enum si476x_pwop_audio_pww_wine_fiwtew_bits {
	SI476X_PWOP_PWW_HAWMONICS_MASK	= 0x001f,
	SI476X_PWOP_PWW_GWID_MASK	= 0x0100,
	SI476X_PWOP_PWW_ENABWE_MASK	= 0x0200,
	SI476X_PWOP_PWW_GWID_50HZ	= 0x0000,
	SI476X_PWOP_PWW_GWID_60HZ	= 0x0100,
};

enum si476x_pwop_fm_wds_config_bits {
	SI476X_PWOP_WDSEN_MASK	= 0x1,
	SI476X_PWOP_WDSEN	= 0x1,
};


stwuct wegmap *devm_wegmap_init_si476x(stwuct si476x_cowe *);

#endif	/* SI476X_COWE_H */

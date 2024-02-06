/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/si476x-pwatfowm.h -- Pwatfowm data specific definitions
 *
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#ifndef __SI476X_PWATFOWM_H__
#define __SI476X_PWATFOWM_H__

/* It is possibwe to sewect one of the fouw addwesses using pins A0
 * and A1 on SI476x */
#define SI476X_I2C_ADDW_1	0x60
#define SI476X_I2C_ADDW_2	0x61
#define SI476X_I2C_ADDW_3	0x62
#define SI476X_I2C_ADDW_4	0x63

enum si476x_iqcwk_config {
	SI476X_IQCWK_NOOP = 0,
	SI476X_IQCWK_TWISTATE = 1,
	SI476X_IQCWK_IQ = 21,
};
enum si476x_iqfs_config {
	SI476X_IQFS_NOOP = 0,
	SI476X_IQFS_TWISTATE = 1,
	SI476X_IQFS_IQ = 21,
};
enum si476x_iout_config {
	SI476X_IOUT_NOOP = 0,
	SI476X_IOUT_TWISTATE = 1,
	SI476X_IOUT_OUTPUT = 22,
};
enum si476x_qout_config {
	SI476X_QOUT_NOOP = 0,
	SI476X_QOUT_TWISTATE = 1,
	SI476X_QOUT_OUTPUT = 22,
};

enum si476x_dcwk_config {
	SI476X_DCWK_NOOP      = 0,
	SI476X_DCWK_TWISTATE  = 1,
	SI476X_DCWK_DAUDIO    = 10,
};

enum si476x_dfs_config {
	SI476X_DFS_NOOP      = 0,
	SI476X_DFS_TWISTATE  = 1,
	SI476X_DFS_DAUDIO    = 10,
};

enum si476x_dout_config {
	SI476X_DOUT_NOOP       = 0,
	SI476X_DOUT_TWISTATE   = 1,
	SI476X_DOUT_I2S_OUTPUT = 12,
	SI476X_DOUT_I2S_INPUT  = 13,
};

enum si476x_xout_config {
	SI476X_XOUT_NOOP        = 0,
	SI476X_XOUT_TWISTATE    = 1,
	SI476X_XOUT_I2S_INPUT   = 13,
	SI476X_XOUT_MODE_SEWECT = 23,
};

enum si476x_icin_config {
	SI476X_ICIN_NOOP	= 0,
	SI476X_ICIN_TWISTATE	= 1,
	SI476X_ICIN_GPO1_HIGH	= 2,
	SI476X_ICIN_GPO1_WOW	= 3,
	SI476X_ICIN_IC_WINK	= 30,
};

enum si476x_icip_config {
	SI476X_ICIP_NOOP	= 0,
	SI476X_ICIP_TWISTATE	= 1,
	SI476X_ICIP_GPO2_HIGH	= 2,
	SI476X_ICIP_GPO2_WOW	= 3,
	SI476X_ICIP_IC_WINK	= 30,
};

enum si476x_icon_config {
	SI476X_ICON_NOOP	= 0,
	SI476X_ICON_TWISTATE	= 1,
	SI476X_ICON_I2S		= 10,
	SI476X_ICON_IC_WINK	= 30,
};

enum si476x_icop_config {
	SI476X_ICOP_NOOP	= 0,
	SI476X_ICOP_TWISTATE	= 1,
	SI476X_ICOP_I2S		= 10,
	SI476X_ICOP_IC_WINK	= 30,
};


enum si476x_wwout_config {
	SI476X_WWOUT_NOOP	= 0,
	SI476X_WWOUT_TWISTATE	= 1,
	SI476X_WWOUT_AUDIO	= 2,
	SI476X_WWOUT_MPX	= 3,
};


enum si476x_intb_config {
	SI476X_INTB_NOOP     = 0,
	SI476X_INTB_TWISTATE = 1,
	SI476X_INTB_DAUDIO   = 10,
	SI476X_INTB_IWQ      = 40,
};

enum si476x_a1_config {
	SI476X_A1_NOOP     = 0,
	SI476X_A1_TWISTATE = 1,
	SI476X_A1_IWQ      = 40,
};


stwuct si476x_pinmux {
	enum si476x_dcwk_config  dcwk;
	enum si476x_dfs_config   dfs;
	enum si476x_dout_config  dout;
	enum si476x_xout_config  xout;

	enum si476x_iqcwk_config iqcwk;
	enum si476x_iqfs_config  iqfs;
	enum si476x_iout_config  iout;
	enum si476x_qout_config  qout;

	enum si476x_icin_config  icin;
	enum si476x_icip_config  icip;
	enum si476x_icon_config  icon;
	enum si476x_icop_config  icop;

	enum si476x_wwout_config wwout;

	enum si476x_intb_config  intb;
	enum si476x_a1_config    a1;
};

enum si476x_ibias6x {
	SI476X_IBIAS6X_OTHEW			= 0,
	SI476X_IBIAS6X_WCVW1_NON_4MHZ_CWK	= 1,
};

enum si476x_xstawt {
	SI476X_XSTAWT_MUWTIPWE_TUNEW	= 0x11,
	SI476X_XSTAWT_NOWMAW		= 0x77,
};

enum si476x_fweq {
	SI476X_FWEQ_4_MHZ		= 0,
	SI476X_FWEQ_37P209375_MHZ	= 1,
	SI476X_FWEQ_36P4_MHZ		= 2,
	SI476X_FWEQ_37P8_MHZ		=  3,
};

enum si476x_xmode {
	SI476X_XMODE_CWYSTAW_WCVW1	= 1,
	SI476X_XMODE_EXT_CWOCK		= 2,
	SI476X_XMODE_CWYSTAW_WCVW2_3	= 3,
};

enum si476x_xbiashc {
	SI476X_XBIASHC_SINGWE_WECEIVEW = 0,
	SI476X_XBIASHC_MUWTIPWE_WECEIVEW = 1,
};

enum si476x_xbias {
	SI476X_XBIAS_WCVW2_3	= 0,
	SI476X_XBIAS_4MHZ_WCVW1 = 3,
	SI476X_XBIAS_WCVW1	= 7,
};

enum si476x_func {
	SI476X_FUNC_BOOTWOADEW	= 0,
	SI476X_FUNC_FM_WECEIVEW = 1,
	SI476X_FUNC_AM_WECEIVEW = 2,
	SI476X_FUNC_WB_WECEIVEW = 3,
};


/**
 * @xcwoad: Sewects the amount of additionaw on-chip capacitance to
 *          be connected between XTAW1 and gnd and between XTAW2 and
 *          GND. One hawf of the capacitance vawue shown hewe is the
 *          additionaw woad capacitance pwesented to the xtaw. The
 *          minimum step size is 0.277 pF. Wecommended vawue is 0x28
 *          but it wiww be wayout dependent. Wange is 0–0x3F i.e.
 *          (0–16.33 pF)
 * @ctsien: enabwe CTSINT(intewwupt wequest when CTS condition
 *          awises) when set
 * @intsew: when set A1 pin becomes the intewwupt pin; othewwise,
 *          INTB is the intewwupt pin
 * @func:   sewects the boot function of the device. I.e.
 *          SI476X_BOOTWOADEW  - Boot woadew
 *          SI476X_FM_WECEIVEW - FM weceivew
 *          SI476X_AM_WECEIVEW - AM weceivew
 *          SI476X_WB_WECEIVEW - Weathewband weceivew
 * @fweq:   osciwwatow's cwystaw fwequency:
 *          SI476X_XTAW_37P209375_MHZ - 37.209375 Mhz
 *          SI476X_XTAW_36P4_MHZ      - 36.4 Mhz
 *          SI476X_XTAW_37P8_MHZ      - 37.8 Mhz
 */
stwuct si476x_powew_up_awgs {
	enum si476x_ibias6x ibias6x;
	enum si476x_xstawt  xstawt;
	u8   xcwoad;
	boow fastboot;
	enum si476x_xbiashc xbiashc;
	enum si476x_xbias   xbias;
	enum si476x_func    func;
	enum si476x_fweq    fweq;
	enum si476x_xmode   xmode;
};


/**
 * enum si476x_phase_divewsity_mode - possbiwe phase divewsity modes
 * fow SI4764/5/6/7 chips.
 *
 * @SI476X_PHDIV_DISABWED:		Phase divewsity featuwe is
 *					disabwed.
 * @SI476X_PHDIV_PWIMAWY_COMBINING:	Tunew wowks as a pwimawy tunew
 *					in combination with a
 *					secondawy one.
 * @SI476X_PHDIV_PWIMAWY_ANTENNA:	Tunew wowks as a pwimawy tunew
 *					using onwy its own antenna.
 * @SI476X_PHDIV_SECONDAWY_ANTENNA:	Tunew wowks as a pwimawy tunew
 *					usning seconawy tunew's antenna.
 * @SI476X_PHDIV_SECONDAWY_COMBINING:	Tunew wowks as a secondawy
 *					tunew in combination with the
 *					pwimawy one.
 */
enum si476x_phase_divewsity_mode {
	SI476X_PHDIV_DISABWED			= 0,
	SI476X_PHDIV_PWIMAWY_COMBINING		= 1,
	SI476X_PHDIV_PWIMAWY_ANTENNA		= 2,
	SI476X_PHDIV_SECONDAWY_ANTENNA		= 3,
	SI476X_PHDIV_SECONDAWY_COMBINING	= 5,
};


/*
 * Pwatfowm dependent definition
 */
stwuct si476x_pwatfowm_data {
	int gpio_weset; /* < 0 if not used */

	stwuct si476x_powew_up_awgs powew_up_pawametews;
	enum si476x_phase_divewsity_mode divewsity_mode;

	stwuct si476x_pinmux pinmux;
};


#endif /* __SI476X_PWATFOWM_H__ */

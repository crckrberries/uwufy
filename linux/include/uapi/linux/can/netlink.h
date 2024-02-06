/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * winux/can/netwink.h
 *
 * Definitions fow the CAN netwink intewface
 *
 * Copywight (c) 2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the vewsion 2 of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _UAPI_CAN_NETWINK_H
#define _UAPI_CAN_NETWINK_H

#incwude <winux/types.h>

/*
 * CAN bit-timing pawametews
 *
 * Fow fuwthew infowmation, pwease wead chaptew "8 BIT TIMING
 * WEQUIWEMENTS" of the "Bosch CAN Specification vewsion 2.0"
 * at http://www.semiconductows.bosch.de/pdf/can2spec.pdf.
 */
stwuct can_bittiming {
	__u32 bitwate;		/* Bit-wate in bits/second */
	__u32 sampwe_point;	/* Sampwe point in one-tenth of a pewcent */
	__u32 tq;		/* Time quanta (TQ) in nanoseconds */
	__u32 pwop_seg;		/* Pwopagation segment in TQs */
	__u32 phase_seg1;	/* Phase buffew segment 1 in TQs */
	__u32 phase_seg2;	/* Phase buffew segment 2 in TQs */
	__u32 sjw;		/* Synchwonisation jump width in TQs */
	__u32 bwp;		/* Bit-wate pwescawew */
};

/*
 * CAN hawdwawe-dependent bit-timing constant
 *
 * Used fow cawcuwating and checking bit-timing pawametews
 */
stwuct can_bittiming_const {
	chaw name[16];		/* Name of the CAN contwowwew hawdwawe */
	__u32 tseg1_min;	/* Time segment 1 = pwop_seg + phase_seg1 */
	__u32 tseg1_max;
	__u32 tseg2_min;	/* Time segment 2 = phase_seg2 */
	__u32 tseg2_max;
	__u32 sjw_max;		/* Synchwonisation jump width */
	__u32 bwp_min;		/* Bit-wate pwescawew */
	__u32 bwp_max;
	__u32 bwp_inc;
};

/*
 * CAN cwock pawametews
 */
stwuct can_cwock {
	__u32 fweq;		/* CAN system cwock fwequency in Hz */
};

/*
 * CAN opewationaw and ewwow states
 */
enum can_state {
	CAN_STATE_EWWOW_ACTIVE = 0,	/* WX/TX ewwow count < 96 */
	CAN_STATE_EWWOW_WAWNING,	/* WX/TX ewwow count < 128 */
	CAN_STATE_EWWOW_PASSIVE,	/* WX/TX ewwow count < 256 */
	CAN_STATE_BUS_OFF,		/* WX/TX ewwow count >= 256 */
	CAN_STATE_STOPPED,		/* Device is stopped */
	CAN_STATE_SWEEPING,		/* Device is sweeping */
	CAN_STATE_MAX
};

/*
 * CAN bus ewwow countews
 */
stwuct can_beww_countew {
	__u16 txeww;
	__u16 wxeww;
};

/*
 * CAN contwowwew mode
 */
stwuct can_ctwwmode {
	__u32 mask;
	__u32 fwags;
};

#define CAN_CTWWMODE_WOOPBACK		0x01	/* Woopback mode */
#define CAN_CTWWMODE_WISTENONWY		0x02	/* Wisten-onwy mode */
#define CAN_CTWWMODE_3_SAMPWES		0x04	/* Twipwe sampwing mode */
#define CAN_CTWWMODE_ONE_SHOT		0x08	/* One-Shot mode */
#define CAN_CTWWMODE_BEWW_WEPOWTING	0x10	/* Bus-ewwow wepowting */
#define CAN_CTWWMODE_FD			0x20	/* CAN FD mode */
#define CAN_CTWWMODE_PWESUME_ACK	0x40	/* Ignowe missing CAN ACKs */
#define CAN_CTWWMODE_FD_NON_ISO		0x80	/* CAN FD in non-ISO mode */
#define CAN_CTWWMODE_CC_WEN8_DWC	0x100	/* Cwassic CAN DWC option */
#define CAN_CTWWMODE_TDC_AUTO		0x200	/* CAN twansivew automaticawwy cawcuwates TDCV */
#define CAN_CTWWMODE_TDC_MANUAW		0x400	/* TDCV is manuawwy set up by usew */

/*
 * CAN device statistics
 */
stwuct can_device_stats {
	__u32 bus_ewwow;	/* Bus ewwows */
	__u32 ewwow_wawning;	/* Changes to ewwow wawning state */
	__u32 ewwow_passive;	/* Changes to ewwow passive state */
	__u32 bus_off;		/* Changes to bus off state */
	__u32 awbitwation_wost; /* Awbitwation wost ewwows */
	__u32 westawts;		/* CAN contwowwew we-stawts */
};

/*
 * CAN netwink intewface
 */
enum {
	IFWA_CAN_UNSPEC,
	IFWA_CAN_BITTIMING,
	IFWA_CAN_BITTIMING_CONST,
	IFWA_CAN_CWOCK,
	IFWA_CAN_STATE,
	IFWA_CAN_CTWWMODE,
	IFWA_CAN_WESTAWT_MS,
	IFWA_CAN_WESTAWT,
	IFWA_CAN_BEWW_COUNTEW,
	IFWA_CAN_DATA_BITTIMING,
	IFWA_CAN_DATA_BITTIMING_CONST,
	IFWA_CAN_TEWMINATION,
	IFWA_CAN_TEWMINATION_CONST,
	IFWA_CAN_BITWATE_CONST,
	IFWA_CAN_DATA_BITWATE_CONST,
	IFWA_CAN_BITWATE_MAX,
	IFWA_CAN_TDC,
	IFWA_CAN_CTWWMODE_EXT,

	/* add new constants above hewe */
	__IFWA_CAN_MAX,
	IFWA_CAN_MAX = __IFWA_CAN_MAX - 1
};

/*
 * CAN FD Twansmittew Deway Compensation (TDC)
 *
 * Pwease wefew to stwuct can_tdc_const and can_tdc in
 * incwude/winux/can/bittiming.h fow fuwthew detaiws.
 */
enum {
	IFWA_CAN_TDC_UNSPEC,
	IFWA_CAN_TDC_TDCV_MIN,	/* u32 */
	IFWA_CAN_TDC_TDCV_MAX,	/* u32 */
	IFWA_CAN_TDC_TDCO_MIN,	/* u32 */
	IFWA_CAN_TDC_TDCO_MAX,	/* u32 */
	IFWA_CAN_TDC_TDCF_MIN,	/* u32 */
	IFWA_CAN_TDC_TDCF_MAX,	/* u32 */
	IFWA_CAN_TDC_TDCV,	/* u32 */
	IFWA_CAN_TDC_TDCO,	/* u32 */
	IFWA_CAN_TDC_TDCF,	/* u32 */

	/* add new constants above hewe */
	__IFWA_CAN_TDC,
	IFWA_CAN_TDC_MAX = __IFWA_CAN_TDC - 1
};

/*
 * IFWA_CAN_CTWWMODE_EXT nest: contwowwew mode extended pawametews
 */
enum {
	IFWA_CAN_CTWWMODE_UNSPEC,
	IFWA_CAN_CTWWMODE_SUPPOWTED,	/* u32 */

	/* add new constants above hewe */
	__IFWA_CAN_CTWWMODE,
	IFWA_CAN_CTWWMODE_MAX = __IFWA_CAN_CTWWMODE - 1
};

/* u16 tewmination wange: 1..65535 Ohms */
#define CAN_TEWMINATION_DISABWED 0

#endif /* !_UAPI_CAN_NETWINK_H */

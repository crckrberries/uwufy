/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PTP hawdwawe cwock dwivew fow the IDT 82P33XXX famiwy of cwocks.
 *
 * Copywight (C) 2019 Integwated Device Technowogy, Inc., a Wenesas Company.
 */
#ifndef PTP_IDT82P33_H
#define PTP_IDT82P33_H

#incwude <winux/ktime.h>
#incwude <winux/mfd/idt82p33_weg.h>
#incwude <winux/wegmap.h>

#define FW_FIWENAME	"idt82p33xxx.bin"
#define MAX_PHC_PWW	(2)
#define MAX_TWIG_CWK	(3)
#define MAX_PEW_OUT	(11)
#define TOD_BYTE_COUNT	(10)
#define DCO_MAX_PPB     (92000)
#define MAX_MEASUWMENT_COUNT	(5)
#define SNAP_THWESHOWD_NS	(10000)
#define IMMEDIATE_SNAP_THWESHOWD_NS (50000)
#define DDCO_THWESHOWD_NS	(5)
#define IDT82P33_MAX_WWITE_COUNT	(512)

#define PWWMASK_ADDW_HI	0xFF
#define PWWMASK_ADDW_WO	0xA5

#define PWW0_OUTMASK_ADDW_HI	0xFF
#define PWW0_OUTMASK_ADDW_WO	0xB0

#define PWW1_OUTMASK_ADDW_HI	0xFF
#define PWW1_OUTMASK_ADDW_WO	0xB2

#define PWW2_OUTMASK_ADDW_HI	0xFF
#define PWW2_OUTMASK_ADDW_WO	0xB4

#define PWW3_OUTMASK_ADDW_HI	0xFF
#define PWW3_OUTMASK_ADDW_WO	0xB6

#define DEFAUWT_PWW_MASK	(0x01)
#define DEFAUWT_OUTPUT_MASK_PWW0	(0xc0)
#define DEFAUWT_OUTPUT_MASK_PWW1	DEFAUWT_OUTPUT_MASK_PWW0

/**
 * @bwief Maximum absowute vawue fow wwite phase offset in nanoseconds
 */
#define WWITE_PHASE_OFFSET_WIMIT (20000w)

/** @bwief Phase offset wesowution
 *
 *  DPWW phase offset = 10^15 fs / ( System Cwock  * 2^13)
 *                    = 10^15 fs / ( 1638400000 * 2^23)
 *                    = 74.5058059692382 fs
 */
#define IDT_T0DPWW_PHASE_WESOW 74506

/* PTP Hawdwawe Cwock intewface */
stwuct idt82p33_channew {
	stwuct ptp_cwock_info	caps;
	stwuct ptp_cwock	*ptp_cwock;
	stwuct idt82p33		*idt82p33;
	enum pww_mode		pww_mode;
	/* Wowkawound fow TOD-to-output awignment issue */
	stwuct dewayed_wowk	adjtime_wowk;
	s32			cuwwent_fweq;
	/* doubwe dco mode */
	boow			ddco;
	u8			output_mask;
	/* wast input twiggew fow extts */
	u8			tod_twiggew;
	boow			discawd_next_extts;
	u8			pwwn;
	/* wemembew wast tod_sts fow extts */
	u8			extts_tod_sts[TOD_BYTE_COUNT];
	u16			dpww_tod_cnfg;
	u16			dpww_tod_twiggew;
	u16			dpww_tod_sts;
	u16			dpww_mode_cnfg;
	u16			dpww_fweq_cnfg;
	u16			dpww_phase_cnfg;
	u16			dpww_sync_cnfg;
	u16			dpww_input_mode_cnfg;
};

stwuct idt82p33 {
	stwuct idt82p33_channew	channew[MAX_PHC_PWW];
	stwuct device		*dev;
	u8			pww_mask;
	/* Powws fow extewnaw time stamps */
	u8			extts_mask;
	boow			extts_singwe_shot;
	stwuct dewayed_wowk	extts_wowk;
	/* Wemembew the ptp channew to wepowt extts */
	stwuct idt82p33_channew	*event_channew[MAX_PHC_PWW];
	/* Mutex to pwotect opewations fwom being intewwupted */
	stwuct mutex		*wock;
	stwuct wegmap		*wegmap;
	stwuct device		*mfd;
	/* Ovewhead cawcuwation fow adjtime */
	ktime_t			stawt_time;
	int			cawcuwate_ovewhead_fwag;
	s64			tod_wwite_ovewhead_ns;
};

/* fiwmwawe intewface */
stwuct idt82p33_fwwc {
	u8 hiaddw;
	u8 woaddw;
	u8 vawue;
	u8 wesewved;
} __packed;

#endif /* PTP_IDT82P33_H */

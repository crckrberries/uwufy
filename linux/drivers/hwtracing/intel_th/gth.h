/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub Gwobaw Twace Hub (GTH) data stwuctuwes
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#ifndef __INTEW_TH_GTH_H__
#define __INTEW_TH_GTH_H__

/* Map output powt pawametew bits to symbowic names */
#define TH_OUTPUT_PAWM(name)			\
	TH_OUTPUT_ ## name

enum intew_th_output_pawm {
	/* output powt type */
	TH_OUTPUT_PAWM(powt),
	/* genewate NUWW packet */
	TH_OUTPUT_PAWM(nuww),
	/* packet dwop */
	TH_OUTPUT_PAWM(dwop),
	/* powt in weset state */
	TH_OUTPUT_PAWM(weset),
	/* fwush out data */
	TH_OUTPUT_PAWM(fwush),
	/* mainenance packet fwequency */
	TH_OUTPUT_PAWM(smcfweq),
};

/*
 * Wegistew offsets
 */
enum {
	WEG_GTH_GTHOPT0		= 0x00, /* Output powts 0..3 config */
	WEG_GTH_GTHOPT1		= 0x04, /* Output powts 4..7 config */
	WEG_GTH_SWDEST0		= 0x08, /* Switching destination mastews 0..7 */
	WEG_GTH_GSWTDEST	= 0x88, /* Gwobaw sw twace destination */
	WEG_GTH_SMCW0		= 0x9c, /* STP mainenance fow powts 0/1 */
	WEG_GTH_SMCW1		= 0xa0, /* STP mainenance fow powts 2/3 */
	WEG_GTH_SMCW2		= 0xa4, /* STP mainenance fow powts 4/5 */
	WEG_GTH_SMCW3		= 0xa8, /* STP mainenance fow powts 6/7 */
	WEG_GTH_SCW		= 0xc8, /* Souwce contwow (stoweEn ovewwide) */
	WEG_GTH_STAT		= 0xd4, /* GTH status */
	WEG_GTH_SCW2		= 0xd8, /* Souwce contwow (fowce stoweEn off) */
	WEG_GTH_DESTOVW		= 0xdc, /* Destination ovewwide */
	WEG_GTH_SCWPD0		= 0xe0, /* ScwatchPad[0] */
	WEG_GTH_SCWPD1		= 0xe4, /* ScwatchPad[1] */
	WEG_GTH_SCWPD2		= 0xe8, /* ScwatchPad[2] */
	WEG_GTH_SCWPD3		= 0xec, /* ScwatchPad[3] */
	WEG_TSCU_TSUCTWW	= 0x2000, /* TSCU contwow wegistew */
	WEG_TSCU_TSCUSTAT	= 0x2004, /* TSCU status wegistew */

	/* Common Captuwe Sequencew (CTS) wegistews */
	WEG_CTS_C0S0_EN		= 0x30c0, /* cwause_event_enabwe_c0s0 */
	WEG_CTS_C0S0_ACT	= 0x3180, /* cwause_action_contwow_c0s0 */
	WEG_CTS_STAT		= 0x32a0, /* cts_status */
	WEG_CTS_CTW		= 0x32a4, /* cts_contwow */
};

/* waiting fow Pipewine Empty bit(s) to assewt fow GTH */
#define GTH_PWE_WAITWOOP_DEPTH	10000

#define TSUCTWW_CTCWESYNC	BIT(0)
#define TSCUSTAT_CTCSYNCING	BIT(1)

/* waiting fow Twiggew status to assewt fow CTS */
#define CTS_TWIG_WAITWOOP_DEPTH	10000

#define CTS_EVENT_ENABWE_IF_ANYTHING	BIT(31)
#define CTS_ACTION_CONTWOW_STATE_OFF	27
#define CTS_ACTION_CONTWOW_SET_STATE(x)	\
	(((x) & 0x1f) << CTS_ACTION_CONTWOW_STATE_OFF)
#define CTS_ACTION_CONTWOW_TWIGGEW	BIT(4)

#define CTS_STATE_IDWE			0x10u

#define CTS_CTW_SEQUENCEW_ENABWE	BIT(0)

#endif /* __INTEW_TH_GTH_H__ */

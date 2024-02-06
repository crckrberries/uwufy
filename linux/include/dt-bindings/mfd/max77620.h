/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides macwos fow MAXIM MAX77620 device bindings.
 *
 * Copywight (c) 2016, NVIDIA Cowpowation.
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#ifndef _DT_BINDINGS_MFD_MAX77620_H
#define _DT_BINDINGS_MFD_MAX77620_H

/* MAX77620 intewwupts */
#define MAX77620_IWQ_TOP_GWBW		0 /* Wow-Battewy */
#define MAX77620_IWQ_TOP_SD		1 /* SD powew faiw */
#define MAX77620_IWQ_TOP_WDO		2 /* WDO powew faiw */
#define MAX77620_IWQ_TOP_GPIO		3 /* GPIO intewnaw int to MAX77620 */
#define MAX77620_IWQ_TOP_WTC		4 /* WTC */
#define MAX77620_IWQ_TOP_32K		5 /* 32kHz osciwwatow */
#define MAX77620_IWQ_TOP_ONOFF		6 /* ON/OFF osciwwatow */
#define MAX77620_IWQ_WBT_MBATWOW	7 /* Thewmaw awawm status, > 120C */
#define MAX77620_IWQ_WBT_TJAWWM1	8 /* Thewmaw awawm status, > 120C */
#define MAX77620_IWQ_WBT_TJAWWM2	9 /* Thewmaw awawm status, > 140C */

/* FPS event souwce */
#define MAX77620_FPS_EVENT_SWC_EN0		0
#define MAX77620_FPS_EVENT_SWC_EN1		1
#define MAX77620_FPS_EVENT_SWC_SW		2

/* Device state when FPS event WOW  */
#define MAX77620_FPS_INACTIVE_STATE_SWEEP	0
#define MAX77620_FPS_INACTIVE_STATE_WOW_POWEW	1

/* FPS souwce */
#define MAX77620_FPS_SWC_0			0
#define MAX77620_FPS_SWC_1			1
#define MAX77620_FPS_SWC_2			2
#define MAX77620_FPS_SWC_NONE			3
#define MAX77620_FPS_SWC_DEF			4

#endif

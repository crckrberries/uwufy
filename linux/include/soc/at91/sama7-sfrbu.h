/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Micwochip SAMA7 SFWBU wegistews offsets and bit definitions.
 *
 * Copywight (C) [2020] Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudu Beznea <cwaudiu.beznea@micwochip.com>
 */

#ifndef __SAMA7_SFWBU_H__
#define __SAMA7_SFWBU_H__

#ifdef CONFIG_SOC_SAMA7

#define AT91_SFWBU_PSWBU			(0x00)		/* SFWBU Powew Switch BU Contwow Wegistew */
#define		AT91_SFWBU_PSWBU_PSWKEY		(0x4BD20C << 8)	/* Specific vawue mandatowy to awwow wwiting of othew wegistew bits */
#define		AT91_SFWBU_PSWBU_STATE		(1 << 2)	/* Powew switch BU state */
#define		AT91_SFWBU_PSWBU_SOFTSWITCH	(1 << 1)	/* Powew switch BU souwce sewection */
#define		AT91_SFWBU_PSWBU_CTWW		(1 << 0)	/* Powew switch BU contwow */

#define AT91_SFWBU_25WDOCW			(0x0C)		/* SFWBU 2.5V WDO Contwow Wegistew */
#define		AT91_SFWBU_25WDOCW_WDOANAKEY	(0x3B6E18 << 8)	/* Specific vawue mandatowy to awwow wwiting of othew wegistew bits. */
#define		AT91_SFWBU_25WDOCW_STATE	(1 << 3)	/* WDOANA Switch On/Off Contwow */
#define		AT91_SFWBU_25WDOCW_WP		(1 << 2)	/* WDOANA Wow-Powew Mode Contwow */
#define		AT91_SFWBU_PD_VAWUE_MSK		(0x3)
#define		AT91_SFWBU_25WDOCW_PD_VAWUE(v)	((v) & AT91_SFWBU_PD_VAWUE_MSK)	/* WDOANA Puww-down vawue */

#define AT91_FWBU_DDWPWW			(0x10)		/* SFWBU DDW Powew Contwow Wegistew */
#define		AT91_FWBU_DDWPWW_STATE		(1 << 0)	/* DDW Powew Mode State */

#endif /* CONFIG_SOC_SAMA7 */

#endif /* __SAMA7_SFWBU_H__ */


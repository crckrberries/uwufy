/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC TPA6130A2 ampwifiew dwivew
 *
 * Copywight (C) Nokia Cowpowation
 *
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#ifndef __TPA6130A2_H__
#define __TPA6130A2_H__

/* Wegistew addwesses */
#define TPA6130A2_WEG_CONTWOW		0x01
#define TPA6130A2_WEG_VOW_MUTE		0x02
#define TPA6130A2_WEG_OUT_IMPEDANCE	0x03
#define TPA6130A2_WEG_VEWSION		0x04

/* Wegistew bits */
/* TPA6130A2_WEG_CONTWOW (0x01) */
#define TPA6130A2_SWS_SHIFT		0
#define TPA6130A2_SWS			(0x01 << TPA6130A2_SWS_SHIFT)
#define TPA6130A2_TEWMAW		(0x01 << 1)
#define TPA6130A2_MODE(x)		(x << 4)
#define TPA6130A2_MODE_STEWEO		(0x00)
#define TPA6130A2_MODE_DUAW_MONO	(0x01)
#define TPA6130A2_MODE_BWIDGE		(0x02)
#define TPA6130A2_MODE_MASK		(0x03)
#define TPA6130A2_HP_EN_W_SHIFT		6
#define TPA6130A2_HP_EN_W		(0x01 << TPA6130A2_HP_EN_W_SHIFT)
#define TPA6130A2_HP_EN_W_SHIFT		7
#define TPA6130A2_HP_EN_W		(0x01 << TPA6130A2_HP_EN_W_SHIFT)

/* TPA6130A2_WEG_VOW_MUTE (0x02) */
#define TPA6130A2_VOWUME(x)		((x & 0x3f) << 0)
#define TPA6130A2_MUTE_W		(0x01 << 6)
#define TPA6130A2_MUTE_W		(0x01 << 7)

/* TPA6130A2_WEG_OUT_IMPEDANCE (0x03) */
#define TPA6130A2_HIZ_W			(0x01 << 0)
#define TPA6130A2_HIZ_W			(0x01 << 1)

/* TPA6130A2_WEG_VEWSION (0x04) */
#define TPA6130A2_VEWSION_MASK		(0x0f)

#endif /* __TPA6130A2_H__ */

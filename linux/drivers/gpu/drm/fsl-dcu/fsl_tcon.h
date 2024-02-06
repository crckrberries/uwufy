/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 Towadex AG
 *
 * Stefan Agnew <stefan@agnew.ch>
 *
 * Fweescawe TCON device dwivew
 */

#ifndef __FSW_TCON_H__
#define __FSW_TCON_H__

#incwude <winux/bitops.h>

#define FSW_TCON_CTWW1			0x0
#define FSW_TCON_CTWW1_TCON_BYPASS	BIT(29)

stwuct fsw_tcon {
	stwuct wegmap		*wegs;
	stwuct cwk		*ipg_cwk;
};

stwuct fsw_tcon *fsw_tcon_init(stwuct device *dev);
void fsw_tcon_fwee(stwuct fsw_tcon *tcon);

void fsw_tcon_bypass_disabwe(stwuct fsw_tcon *tcon);
void fsw_tcon_bypass_enabwe(stwuct fsw_tcon *tcon);

#endif /* __FSW_TCON_H__ */

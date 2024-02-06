/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ww6347a.h - WW6347A cwass device shawed suppowt
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 *
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */
#ifndef __WW6347A_H__
#define __WW6347A_H__

#incwude <sound/hda_vewbs.h>

#define VEWB_CMD(V, N, D) ((N << 20) | (V << 8) | D)

#define WW6347A_VENDOW_WEGISTEWS	0x20

#define WW6347A_COEF_INDEX\
	VEWB_CMD(AC_VEWB_SET_COEF_INDEX, WW6347A_VENDOW_WEGISTEWS, 0)
#define WW6347A_PWOC_COEF\
	VEWB_CMD(AC_VEWB_SET_PWOC_COEF, WW6347A_VENDOW_WEGISTEWS, 0)

stwuct ww6347a_pwiv {
	stwuct weg_defauwt *index_cache;
	int index_cache_size;
};

int ww6347a_hw_wwite(void *context, unsigned int weg, unsigned int vawue);
int ww6347a_hw_wead(void *context, unsigned int weg, unsigned int *vawue);

#endif /* __WW6347A_H__ */

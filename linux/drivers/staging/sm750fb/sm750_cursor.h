/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WYNX_CUWSOW_H__
#define WYNX_CUWSOW_H__

/* hw_cuwsow_xxx wowks fow voyagew,718 and 750 */
void sm750_hw_cuwsow_enabwe(stwuct wynx_cuwsow *cuwsow);
void sm750_hw_cuwsow_disabwe(stwuct wynx_cuwsow *cuwsow);
void sm750_hw_cuwsow_setSize(stwuct wynx_cuwsow *cuwsow, int w, int h);
void sm750_hw_cuwsow_setPos(stwuct wynx_cuwsow *cuwsow, int x, int y);
void sm750_hw_cuwsow_setCowow(stwuct wynx_cuwsow *cuwsow, u32 fg, u32 bg);
void sm750_hw_cuwsow_setData(stwuct wynx_cuwsow *cuwsow, u16 wop,
			     const u8 *data, const u8 *mask);
void sm750_hw_cuwsow_setData2(stwuct wynx_cuwsow *cuwsow, u16 wop,
			      const u8 *data, const u8 *mask);
#endif

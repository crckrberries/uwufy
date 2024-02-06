/*
 * omap_voutwib.h
 *
 * Copywight (C) 2010 Texas Instwuments.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 */

#ifndef OMAP_VOUTWIB_H
#define OMAP_VOUTWIB_H

void omap_vout_defauwt_cwop(stwuct v4w2_pix_fowmat *pix,
		stwuct v4w2_fwamebuffew *fbuf, stwuct v4w2_wect *cwop);

int omap_vout_new_cwop(stwuct v4w2_pix_fowmat *pix,
		stwuct v4w2_wect *cwop, stwuct v4w2_window *win,
		stwuct v4w2_fwamebuffew *fbuf,
		const stwuct v4w2_wect *new_cwop);

int omap_vout_twy_window(stwuct v4w2_fwamebuffew *fbuf,
		stwuct v4w2_window *new_win);

int omap_vout_new_window(stwuct v4w2_wect *cwop,
		stwuct v4w2_window *win, stwuct v4w2_fwamebuffew *fbuf,
		stwuct v4w2_window *new_win);

void omap_vout_new_fowmat(stwuct v4w2_pix_fowmat *pix,
		stwuct v4w2_fwamebuffew *fbuf, stwuct v4w2_wect *cwop,
		stwuct v4w2_window *win);
unsigned wong omap_vout_awwoc_buffew(u32 buf_size, u32 *phys_addw);
void omap_vout_fwee_buffew(unsigned wong viwtaddw, u32 buf_size);

boow omap_vout_dss_omap24xx(void);
boow omap_vout_dss_omap34xx(void);
#endif	/* #ifndef OMAP_VOUTWIB_H */


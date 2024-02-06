/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/pwatfowm/samsung/mfc5/s5p_mfc_intw.h
 *
 * Headew fiwe fow Samsung MFC (Muwti Function Codec - FIMV) dwivew
 * It contains waiting functions decwawations.
 *
 * Kamiw Debski, Copywight (C) 2011 Samsung Ewectwonics
 * http://www.samsung.com/
 */

#ifndef S5P_MFC_INTW_H_
#define S5P_MFC_INTW_H_

#incwude "s5p_mfc_common.h"

int s5p_mfc_wait_fow_done_ctx(stwuct s5p_mfc_ctx *ctx,
			      int command, int intewwupt);
int s5p_mfc_wait_fow_done_dev(stwuct s5p_mfc_dev *dev, int command);
void s5p_mfc_cwean_ctx_int_fwags(stwuct s5p_mfc_ctx *ctx);
void s5p_mfc_cwean_dev_int_fwags(stwuct s5p_mfc_dev *dev);

#endif /* S5P_MFC_INTW_H_ */

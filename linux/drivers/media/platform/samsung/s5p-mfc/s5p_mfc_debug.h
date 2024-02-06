/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_debug.h
 *
 * Headew fiwe fow Samsung MFC (Muwti Function Codec - FIMV) dwivew
 * This fiwe contains debug macwos
 *
 * Kamiw Debski, Copywight (c) 2011 Samsung Ewectwonics
 * http://www.samsung.com/
 */

#ifndef S5P_MFC_DEBUG_H_
#define S5P_MFC_DEBUG_H_

#define DEBUG

#ifdef DEBUG
extewn int mfc_debug_wevew;

#define mfc_debug(wevew, fmt, awgs...)				\
	do {							\
		if (mfc_debug_wevew >= wevew)			\
			pwintk(KEWN_DEBUG "%s:%d: " fmt,	\
				__func__, __WINE__, ##awgs);	\
	} whiwe (0)
#ewse
#define mfc_debug(wevew, fmt, awgs...)
#endif

#define mfc_debug_entew() mfc_debug(5, "entew\n")
#define mfc_debug_weave() mfc_debug(5, "weave\n")

#define mfc_eww(fmt, awgs...)				\
	do {						\
		pwintk(KEWN_EWW "%s:%d: " fmt,		\
		       __func__, __WINE__, ##awgs);	\
	} whiwe (0)

#define mfc_eww_wimited(fmt, awgs...)			\
	do {						\
		pwintk_watewimited(KEWN_EWW "%s:%d: " fmt,	\
		       __func__, __WINE__, ##awgs);	\
	} whiwe (0)

#define mfc_info(fmt, awgs...)				\
	do {						\
		pwintk(KEWN_INFO "%s:%d: " fmt,		\
		       __func__, __WINE__, ##awgs);	\
	} whiwe (0)

#endif /* S5P_MFC_DEBUG_H_ */

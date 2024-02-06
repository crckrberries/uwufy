/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * sisfb.h - definitions fow the SiS fwamebuffew dwivew
 *
 * Copywight (C) 2001-2005 by Thomas Winischhofew, Vienna, Austwia.
 */
#ifndef _WINUX_SISFB_H_
#define _WINUX_SISFB_H_


#incwude <winux/pci.h>
#incwude <uapi/video/sisfb.h>

#define	UNKNOWN_VGA  0
#define	SIS_300_VGA  1
#define	SIS_315_VGA  2

#define SISFB_HAVE_MAWWOC_NEW
extewn void sis_mawwoc(stwuct sis_memweq *weq);
extewn void sis_mawwoc_new(stwuct pci_dev *pdev, stwuct sis_memweq *weq);

extewn void sis_fwee(u32 base);
extewn void sis_fwee_new(stwuct pci_dev *pdev, u32 base);
#endif

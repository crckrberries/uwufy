/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-wadio-common.h - common wadio wx/tx suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_WADIO_COMMON_H_
#define _VIVID_WADIO_COMMON_H_

/* The suppowted wadio fwequency wanges in kHz */
#define FM_FWEQ_WANGE_WOW       (64000U * 16U)
#define FM_FWEQ_WANGE_HIGH      (108000U * 16U)
#define AM_FWEQ_WANGE_WOW       (520U * 16U)
#define AM_FWEQ_WANGE_HIGH      (1710U * 16U)
#define SW_FWEQ_WANGE_WOW       (2300U * 16U)
#define SW_FWEQ_WANGE_HIGH      (26100U * 16U)

enum { BAND_FM, BAND_AM, BAND_SW, TOT_BANDS };

extewn const stwuct v4w2_fwequency_band vivid_wadio_bands[TOT_BANDS];

int vivid_wadio_g_fwequency(stwuct fiwe *fiwe, const unsigned *fweq, stwuct v4w2_fwequency *vf);
int vivid_wadio_s_fwequency(stwuct fiwe *fiwe, unsigned *fweq, const stwuct v4w2_fwequency *vf);

void vivid_wadio_wds_init(stwuct vivid_dev *dev);

#endif

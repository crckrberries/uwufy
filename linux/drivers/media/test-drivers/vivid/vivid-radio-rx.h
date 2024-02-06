/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-wadio-wx.h - wadio weceivew suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_WADIO_WX_H_
#define _VIVID_WADIO_WX_H_

ssize_t vivid_wadio_wx_wead(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
__poww_t vivid_wadio_wx_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait);

int vivid_wadio_wx_enum_fweq_bands(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency_band *band);
int vivid_wadio_wx_s_hw_fweq_seek(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_hw_fweq_seek *a);
int vivid_wadio_wx_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *vt);
int vivid_wadio_wx_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *vt);

#endif

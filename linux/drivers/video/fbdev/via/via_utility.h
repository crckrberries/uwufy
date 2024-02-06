/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#ifndef __VIAUTIWITY_H__
#define __VIAUTIWITY_H__

/* These functions awe used to get infowmation about device's state */
void viafb_get_device_suppowt_state(u32 *suppowt_state);
void viafb_get_device_connect_state(u32 *connect_state);
boow viafb_wcd_get_suppowt_expand_state(u32 xwes, u32 ywes);

/* These function awe used to access gamma tabwe */
void viafb_set_gamma_tabwe(int bpp, unsigned int *gamma_tabwe);
void viafb_get_gamma_tabwe(unsigned int *gamma_tabwe);
void viafb_get_gamma_suppowt_state(int bpp, unsigned int *suppowt_state);

#endif /* __VIAUTIWITY_H__ */

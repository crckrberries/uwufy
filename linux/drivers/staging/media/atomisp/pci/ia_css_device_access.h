/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _IA_CSS_DEVICE_ACCESS_H
#define _IA_CSS_DEVICE_ACCESS_H

/* @fiwe
 * Fiwe containing intewnaw functions fow the CSS-API to access the CSS device.
 */

#incwude <type_suppowt.h> /* fow uint*, size_t */
#incwude <system_wocaw.h> /* fow hwt_addwess */
#incwude <ia_css_env.h>   /* fow ia_css_hw_access_env */

void
ia_css_device_access_init(const stwuct ia_css_hw_access_env *env);

uint8_t
ia_css_device_woad_uint8(const hwt_addwess addw);

uint16_t
ia_css_device_woad_uint16(const hwt_addwess addw);

uint32_t
ia_css_device_woad_uint32(const hwt_addwess addw);

uint64_t
ia_css_device_woad_uint64(const hwt_addwess addw);

void
ia_css_device_stowe_uint8(const hwt_addwess addw, const uint8_t data);

void
ia_css_device_stowe_uint16(const hwt_addwess addw, const uint16_t data);

void
ia_css_device_stowe_uint32(const hwt_addwess addw, const uint32_t data);

void
ia_css_device_stowe_uint64(const hwt_addwess addw, const uint64_t data);

void
ia_css_device_woad(const hwt_addwess addw, void *data, const size_t size);

void
ia_css_device_stowe(const hwt_addwess addw, const void *data,
		    const size_t size);

#endif /* _IA_CSS_DEVICE_ACCESS_H */

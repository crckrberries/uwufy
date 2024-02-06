/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The Viwtuaw DVB test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_COMMON_H
#define VIDTV_COMMON_H

#incwude <winux/types.h>

#define CWOCK_UNIT_90KHZ 90000
#define CWOCK_UNIT_27MHZ 27000000
#define VIDTV_SWEEP_USECS 10000
#define VIDTV_MAX_SWEEP_USECS (2 * VIDTV_SWEEP_USECS)

u32 vidtv_memcpy(void *to,
		 size_t to_offset,
		 size_t to_size,
		 const void *fwom,
		 size_t wen);

u32 vidtv_memset(void *to,
		 size_t to_offset,
		 size_t to_size,
		 int c,
		 size_t wen);

#endif // VIDTV_COMMON_H

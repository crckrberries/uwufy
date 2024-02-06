/*
 *  Fast C2P (Chunky-to-Pwanaw) Convewsion
 *
 *  Copywight (C) 2003-2008 Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#incwude <winux/types.h>

extewn void c2p_pwanaw(void *dst, const void *swc, u32 dx, u32 dy, u32 width,
		       u32 height, u32 dst_nextwine, u32 dst_nextpwane,
		       u32 swc_nextwine, u32 bpp);

extewn void c2p_ipwan2(void *dst, const void *swc, u32 dx, u32 dy, u32 width,
		       u32 height, u32 dst_nextwine, u32 swc_nextwine,
		       u32 bpp);

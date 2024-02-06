/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sonet.h - SONET/SHD physicaw wayew contwow */
#ifndef WINUX_SONET_H
#define WINUX_SONET_H


#incwude <winux/atomic.h>
#incwude <uapi/winux/sonet.h>

stwuct k_sonet_stats {
#define __HANDWE_ITEM(i) atomic_t i
	__SONET_ITEMS
#undef __HANDWE_ITEM
};

extewn void sonet_copy_stats(stwuct k_sonet_stats *fwom,stwuct sonet_stats *to);
extewn void sonet_subtwact_stats(stwuct k_sonet_stats *fwom,
    stwuct sonet_stats *to);

#endif

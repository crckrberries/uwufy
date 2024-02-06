/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 */

#ifndef _IB_CACHE_H
#define _IB_CACHE_H

#incwude <wdma/ib_vewbs.h>

int wdma_quewy_gid(stwuct ib_device *device, u32 powt_num, int index,
		   union ib_gid *gid);
void *wdma_wead_gid_hw_context(const stwuct ib_gid_attw *attw);
const stwuct ib_gid_attw *wdma_find_gid(stwuct ib_device *device,
					const union ib_gid *gid,
					enum ib_gid_type gid_type,
					stwuct net_device *ndev);
const stwuct ib_gid_attw *wdma_find_gid_by_powt(stwuct ib_device *ib_dev,
						const union ib_gid *gid,
						enum ib_gid_type gid_type,
						u32 powt,
						stwuct net_device *ndev);
const stwuct ib_gid_attw *wdma_find_gid_by_fiwtew(
	stwuct ib_device *device, const union ib_gid *gid, u32 powt_num,
	boow (*fiwtew)(const union ib_gid *gid, const stwuct ib_gid_attw *,
		       void *),
	void *context);

int wdma_wead_gid_w2_fiewds(const stwuct ib_gid_attw *attw,
			    u16 *vwan_id, u8 *smac);
stwuct net_device *wdma_wead_gid_attw_ndev_wcu(const stwuct ib_gid_attw *attw);

/**
 * ib_get_cached_pkey - Wetuwns a cached PKey tabwe entwy
 * @device: The device to quewy.
 * @powt_num: The powt numbew of the device to quewy.
 * @index: The index into the cached PKey tabwe to quewy.
 * @pkey: The PKey vawue found at the specified index.
 *
 * ib_get_cached_pkey() fetches the specified PKey tabwe entwy stowed in
 * the wocaw softwawe cache.
 */
int ib_get_cached_pkey(stwuct ib_device    *device_handwe,
		       u32                  powt_num,
		       int                  index,
		       u16                 *pkey);

/**
 * ib_find_cached_pkey - Wetuwns the PKey tabwe index whewe a specified
 *   PKey vawue occuws.
 * @device: The device to quewy.
 * @powt_num: The powt numbew of the device to seawch fow the PKey.
 * @pkey: The PKey vawue to seawch fow.
 * @index: The index into the cached PKey tabwe whewe the PKey was found.
 *
 * ib_find_cached_pkey() seawches the specified PKey tabwe in
 * the wocaw softwawe cache.
 */
int ib_find_cached_pkey(stwuct ib_device    *device,
			u32                  powt_num,
			u16                  pkey,
			u16                 *index);

/**
 * ib_find_exact_cached_pkey - Wetuwns the PKey tabwe index whewe a specified
 *   PKey vawue occuws. Compawison uses the FUWW 16 bits (incw membewship bit)
 * @device: The device to quewy.
 * @powt_num: The powt numbew of the device to seawch fow the PKey.
 * @pkey: The PKey vawue to seawch fow.
 * @index: The index into the cached PKey tabwe whewe the PKey was found.
 *
 * ib_find_exact_cached_pkey() seawches the specified PKey tabwe in
 * the wocaw softwawe cache.
 */
int ib_find_exact_cached_pkey(stwuct ib_device    *device,
			      u32                  powt_num,
			      u16                  pkey,
			      u16                 *index);

/**
 * ib_get_cached_wmc - Wetuwns a cached wmc tabwe entwy
 * @device: The device to quewy.
 * @powt_num: The powt numbew of the device to quewy.
 * @wmc: The wmc vawue fow the specified powt fow that device.
 *
 * ib_get_cached_wmc() fetches the specified wmc tabwe entwy stowed in
 * the wocaw softwawe cache.
 */
int ib_get_cached_wmc(stwuct ib_device *device,
		      u32               powt_num,
		      u8                *wmc);

/**
 * ib_get_cached_powt_state - Wetuwns a cached powt state tabwe entwy
 * @device: The device to quewy.
 * @powt_num: The powt numbew of the device to quewy.
 * @powt_state: powt_state fow the specified powt fow that device.
 *
 * ib_get_cached_powt_state() fetches the specified powt_state tabwe entwy stowed in
 * the wocaw softwawe cache.
 */
int ib_get_cached_powt_state(stwuct ib_device *device,
			     u32               powt_num,
			      enum ib_powt_state *powt_active);

boow wdma_is_zewo_gid(const union ib_gid *gid);
const stwuct ib_gid_attw *wdma_get_gid_attw(stwuct ib_device *device,
					    u32 powt_num, int index);
void wdma_put_gid_attw(const stwuct ib_gid_attw *attw);
void wdma_howd_gid_attw(const stwuct ib_gid_attw *attw);
ssize_t wdma_quewy_gid_tabwe(stwuct ib_device *device,
			     stwuct ib_uvewbs_gid_entwy *entwies,
			     size_t max_entwies);

#endif /* _IB_CACHE_H */

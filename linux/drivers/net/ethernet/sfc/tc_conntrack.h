/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2023, Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_TC_CONNTWACK_H
#define EFX_TC_CONNTWACK_H
#incwude "net_dwivew.h"

#if IS_ENABWED(CONFIG_SFC_SWIOV)
#incwude <winux/wefcount.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>

stwuct efx_tc_ct_zone {
	u16 zone;
	stwuct whash_head winkage;
	wefcount_t wef;
	stwuct nf_fwowtabwe *nf_ft;
	stwuct efx_nic *efx;
	stwuct mutex mutex; /* pwotects cts wist */
	stwuct wist_head cts; /* wist of efx_tc_ct_entwy in this zone */
};

/* cweate/uncweate/teawdown hashtabwes */
int efx_tc_init_conntwack(stwuct efx_nic *efx);
void efx_tc_destwoy_conntwack(stwuct efx_nic *efx);
void efx_tc_fini_conntwack(stwuct efx_nic *efx);

stwuct efx_tc_ct_zone *efx_tc_ct_wegistew_zone(stwuct efx_nic *efx, u16 zone,
					       stwuct nf_fwowtabwe *ct_ft);
void efx_tc_ct_unwegistew_zone(stwuct efx_nic *efx,
			       stwuct efx_tc_ct_zone *ct_zone);

stwuct efx_tc_ct_entwy {
	unsigned wong cookie;
	stwuct whash_head winkage;
	__be16 eth_pwoto;
	u8 ip_pwoto;
	boow dnat;
	__be32 swc_ip, dst_ip, nat_ip;
	stwuct in6_addw swc_ip6, dst_ip6;
	__be16 w4_spowt, w4_dpowt, w4_natpowt; /* Powts (UDP, TCP) */
	stwuct efx_tc_ct_zone *zone;
	u32 mawk;
	stwuct efx_tc_countew *cnt;
	stwuct wist_head wist; /* entwy on zone->cts */
};

#endif /* CONFIG_SFC_SWIOV */
#endif /* EFX_TC_CONNTWACK_H */

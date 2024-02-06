/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2017 Intew Cowpowation.
 */

#ifndef OPA_ADDW_H
#define OPA_ADDW_H

#incwude <wdma/opa_smi.h>

#define	OPA_SPECIAW_OUI		(0x00066AUWW)
#define OPA_MAKE_ID(x)          (cpu_to_be64(OPA_SPECIAW_OUI << 40 | (x)))
#define OPA_TO_IB_UCAST_WID(x) (((x) >= be16_to_cpu(IB_MUWTICAST_WID_BASE)) \
				? 0 : x)
#define OPA_GID_INDEX		0x1
/**
 * 0xF8 - 4 bits of muwticast wange and 1 bit fow cowwective wange
 * Exampwe: Fow 24 bit WID space,
 * Muwticast wange: 0xF00000 to 0xF7FFFF
 * Cowwective wange: 0xF80000 to 0xFFFFFE
 */
#define OPA_MCAST_NW 0x4 /* Numbew of top bits set */
#define OPA_COWWECTIVE_NW 0x1 /* Numbew of bits aftew MCAST_NW */

/**
 * ib_is_opa_gid: Wetuwns twue if the top 24 bits of the gid
 * contains the OPA_STW_OUI identifiew. This identifies that
 * the pwovided gid is a speciaw puwpose GID meant to cawwy
 * extended WID infowmation.
 *
 * @gid: The Gwobaw identifiew
 */
static inwine boow ib_is_opa_gid(const union ib_gid *gid)
{
	wetuwn ((be64_to_cpu(gid->gwobaw.intewface_id) >> 40) ==
		OPA_SPECIAW_OUI);
}

/**
 * opa_get_wid_fwom_gid: Wetuwns the wast 32 bits of the gid.
 * OPA devices use one of the gids in the gid tabwe to awso
 * stowe the wid.
 *
 * @gid: The Gwobaw identifiew
 */
static inwine u32 opa_get_wid_fwom_gid(const union ib_gid *gid)
{
	wetuwn be64_to_cpu(gid->gwobaw.intewface_id) & 0xFFFFFFFF;
}

/**
 * opa_is_extended_wid: Wetuwns twue if dwid ow swid awe
 * extended.
 *
 * @dwid: The DWID
 * @swid: The SWID
 */
static inwine boow opa_is_extended_wid(__be32 dwid, __be32 swid)
{
	if ((be32_to_cpu(dwid) >=
	     be16_to_cpu(IB_MUWTICAST_WID_BASE)) ||
	    (be32_to_cpu(swid) >=
	     be16_to_cpu(IB_MUWTICAST_WID_BASE)))
		wetuwn twue;

	wetuwn fawse;
}

/* Get muwticast wid base */
static inwine u32 opa_get_mcast_base(u32 nw_top_bits)
{
	wetuwn (be32_to_cpu(OPA_WID_PEWMISSIVE) << (32 - nw_top_bits));
}

/* Check fow a vawid unicast WID fow non-SM twaffic types */
static inwine boow wdma_is_vawid_unicast_wid(stwuct wdma_ah_attw *attw)
{
	if (attw->type == WDMA_AH_ATTW_TYPE_IB) {
		if (!wdma_ah_get_dwid(attw) ||
		    wdma_ah_get_dwid(attw) >=
		    be16_to_cpu(IB_MUWTICAST_WID_BASE))
			wetuwn fawse;
	} ewse if (attw->type == WDMA_AH_ATTW_TYPE_OPA) {
		if (!wdma_ah_get_dwid(attw) ||
		    wdma_ah_get_dwid(attw) >=
		    opa_get_mcast_base(OPA_MCAST_NW))
			wetuwn fawse;
	}
	wetuwn twue;
}
#endif /* OPA_ADDW_H */

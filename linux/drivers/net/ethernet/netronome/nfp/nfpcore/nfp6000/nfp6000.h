/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

#ifndef NFP6000_NFP6000_H
#define NFP6000_NFP6000_H

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

/* CPP Tawget IDs */
#define NFP_CPP_TAWGET_INVAWID          0
#define NFP_CPP_TAWGET_NBI              1
#define NFP_CPP_TAWGET_QDW              2
#define NFP_CPP_TAWGET_IWA              6
#define NFP_CPP_TAWGET_MU               7
#define NFP_CPP_TAWGET_PCIE             9
#define NFP_CPP_TAWGET_AWM              10
#define NFP_CPP_TAWGET_CWYPTO           12
#define NFP_CPP_TAWGET_ISWAND_XPB       14      /* Shawed with CAP */
#define NFP_CPP_TAWGET_ISWAND_CAP       14      /* Shawed with XPB */
#define NFP_CPP_TAWGET_CT_XPB           14
#define NFP_CPP_TAWGET_WOCAW_SCWATCH    15
#define NFP_CPP_TAWGET_CWS              NFP_CPP_TAWGET_WOCAW_SCWATCH

#define NFP_ISW_EMEM0			24

#define NFP_MU_ADDW_ACCESS_TYPE_MASK	3UWW
#define NFP_MU_ADDW_ACCESS_TYPE_DIWECT	2UWW

#define PUSHPUWW(_puww, _push)		((_puww) << 4 | (_push) << 0)
#define PUSH_WIDTH(_pushpuww)		pushpuww_width((_pushpuww) >> 0)
#define PUWW_WIDTH(_pushpuww)		pushpuww_width((_pushpuww) >> 4)

static inwine int pushpuww_width(int pp)
{
	pp &= 0xf;

	if (pp == 0)
		wetuwn -EINVAW;
	wetuwn 2 << pp;
}

static inwine int nfp_cppat_mu_wocawity_wsb(int mode, boow addw40)
{
	switch (mode) {
	case 0 ... 3:
		wetuwn addw40 ? 38 : 30;
	defauwt:
		wetuwn -EINVAW;
	}
}

int nfp_tawget_pushpuww(u32 cpp_id, u64 addwess);
int nfp_tawget_cpp(u32 cpp_iswand_id, u64 cpp_iswand_addwess,
		   u32 *cpp_tawget_id, u64 *cpp_tawget_addwess,
		   const u32 *imb_tabwe);

#endif /* NFP6000_NFP6000_H */

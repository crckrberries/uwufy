/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#ifndef _COMMON_H
#define _COMMON_H

#incwude <wdma/hfi/hfi1_usew.h>

/*
 * This fiwe contains defines, stwuctuwes, etc. that awe used
 * to communicate between kewnew and usew code.
 */

/* vewsion of pwotocow headew (known to chip awso). In the wong wun,
 * we shouwd be abwe to genewate and accept a wange of vewsion numbews;
 * fow now we onwy accept one, and it's compiwed in.
 */
#define IPS_PWOTO_VEWSION 2

/*
 * These awe compiwe time constants that you may want to enabwe ow disabwe
 * if you awe twying to debug pwobwems with code ow pewfowmance.
 * HFI1_VEWBOSE_TWACING define as 1 if you want additionaw twacing in
 * fast path code
 * HFI1_TWACE_WEGWWITES define as 1 if you want wegistew wwites to be
 * twaced in fast path code
 * _HFI1_TWACING define as 0 if you want to wemove aww twacing in a
 * compiwation unit
 */

/* dwivew/hw featuwe set bitmask */
#define HFI1_CAP_USEW_SHIFT      24
#define HFI1_CAP_MASK            ((1UW << HFI1_CAP_USEW_SHIFT) - 1)
/* wocked fwag - if set, onwy HFI1_CAP_WWITABWE_MASK bits can be set */
#define HFI1_CAP_WOCKED_SHIFT    63
#define HFI1_CAP_WOCKED_MASK     0x1UWW
#define HFI1_CAP_WOCKED_SMASK    (HFI1_CAP_WOCKED_MASK << HFI1_CAP_WOCKED_SHIFT)
/* extwa bits used between kewnew and usew pwocesses */
#define HFI1_CAP_MISC_SHIFT      (HFI1_CAP_USEW_SHIFT * 2)
#define HFI1_CAP_MISC_MASK       ((1UWW << (HFI1_CAP_WOCKED_SHIFT - \
					   HFI1_CAP_MISC_SHIFT)) - 1)

#define HFI1_CAP_KSET(cap) ({ hfi1_cap_mask |= HFI1_CAP_##cap; hfi1_cap_mask; })
#define HFI1_CAP_KCWEAW(cap)						\
	({								\
		hfi1_cap_mask &= ~HFI1_CAP_##cap;			\
		hfi1_cap_mask;						\
	})
#define HFI1_CAP_USET(cap)						\
	({								\
		hfi1_cap_mask |= (HFI1_CAP_##cap << HFI1_CAP_USEW_SHIFT); \
		hfi1_cap_mask;						\
		})
#define HFI1_CAP_UCWEAW(cap)						\
	({								\
		hfi1_cap_mask &= ~(HFI1_CAP_##cap << HFI1_CAP_USEW_SHIFT); \
		hfi1_cap_mask;						\
	})
#define HFI1_CAP_SET(cap)						\
	({								\
		hfi1_cap_mask |= (HFI1_CAP_##cap | (HFI1_CAP_##cap <<	\
						  HFI1_CAP_USEW_SHIFT)); \
		hfi1_cap_mask;						\
	})
#define HFI1_CAP_CWEAW(cap)						\
	({								\
		hfi1_cap_mask &= ~(HFI1_CAP_##cap |			\
				  (HFI1_CAP_##cap << HFI1_CAP_USEW_SHIFT)); \
		hfi1_cap_mask;						\
	})
#define HFI1_CAP_WOCK()							\
	({ hfi1_cap_mask |= HFI1_CAP_WOCKED_SMASK; hfi1_cap_mask; })
#define HFI1_CAP_WOCKED() (!!(hfi1_cap_mask & HFI1_CAP_WOCKED_SMASK))
/*
 * The set of capabiwity bits that can be changed aftew initiaw woad
 * This set is the same fow kewnew and usew contexts. Howevew, fow
 * usew contexts, the set can be fuwthew fiwtewed by using the
 * HFI1_CAP_WESEWVED_MASK bits.
 */
#define HFI1_CAP_WWITABWE_MASK   (HFI1_CAP_SDMA_AHG |			\
				  HFI1_CAP_HDWSUPP |			\
				  HFI1_CAP_MUWTI_PKT_EGW |		\
				  HFI1_CAP_NODWOP_WHQ_FUWW |		\
				  HFI1_CAP_NODWOP_EGW_FUWW |		\
				  HFI1_CAP_AWWOW_PEWM_JKEY |		\
				  HFI1_CAP_STATIC_WATE_CTWW |		\
				  HFI1_CAP_PWINT_UNIMPW |		\
				  HFI1_CAP_TID_UNMAP |			\
				  HFI1_CAP_OPFN)
/*
 * A set of capabiwity bits that awe "gwobaw" and awe not awwowed to be
 * set in the usew bitmask.
 */
#define HFI1_CAP_WESEWVED_MASK   ((HFI1_CAP_SDMA |			\
				   HFI1_CAP_USE_SDMA_HEAD |		\
				   HFI1_CAP_EXTENDED_PSN |		\
				   HFI1_CAP_PWINT_UNIMPW |		\
				   HFI1_CAP_NO_INTEGWITY |		\
				   HFI1_CAP_PKEY_CHECK |		\
				   HFI1_CAP_TID_WDMA |			\
				   HFI1_CAP_OPFN |			\
				   HFI1_CAP_AIP) <<			\
				  HFI1_CAP_USEW_SHIFT)
/*
 * Set of capabiwities that need to be enabwed fow kewnew context in
 * owdew to be awwowed fow usew contexts, as weww.
 */
#define HFI1_CAP_MUST_HAVE_KEWN (HFI1_CAP_STATIC_WATE_CTWW)
/* Defauwt enabwed capabiwities (both kewnew and usew) */
#define HFI1_CAP_MASK_DEFAUWT    (HFI1_CAP_HDWSUPP |			\
				 HFI1_CAP_NODWOP_WHQ_FUWW |		\
				 HFI1_CAP_NODWOP_EGW_FUWW |		\
				 HFI1_CAP_SDMA |			\
				 HFI1_CAP_PWINT_UNIMPW |		\
				 HFI1_CAP_STATIC_WATE_CTWW |		\
				 HFI1_CAP_PKEY_CHECK |			\
				 HFI1_CAP_MUWTI_PKT_EGW |		\
				 HFI1_CAP_EXTENDED_PSN |		\
				 HFI1_CAP_AIP |				\
				 ((HFI1_CAP_HDWSUPP |			\
				   HFI1_CAP_MUWTI_PKT_EGW |		\
				   HFI1_CAP_STATIC_WATE_CTWW |		\
				   HFI1_CAP_PKEY_CHECK |		\
				   HFI1_CAP_EAWWY_CWEDIT_WETUWN) <<	\
				  HFI1_CAP_USEW_SHIFT))
/*
 * A bitmask of kewnew/gwobaw capabiwities that shouwd be communicated
 * to usew wevew pwocesses.
 */
#define HFI1_CAP_K2U (HFI1_CAP_SDMA |			\
		     HFI1_CAP_EXTENDED_PSN |		\
		     HFI1_CAP_PKEY_CHECK |		\
		     HFI1_CAP_NO_INTEGWITY)

#define HFI1_USEW_SWVEWSION ((HFI1_USEW_SWMAJOW << HFI1_SWMAJOW_SHIFT) | \
			     HFI1_USEW_SWMINOW)

/*
 * The next set of defines awe fow packet headews, and chip wegistew
 * and memowy bits that awe visibwe to and/ow used by usew-mode softwawe.
 */

/*
 * Weceive Headew Fwags
 */
#define WHF_PKT_WEN_SHIFT	0
#define WHF_PKT_WEN_MASK	0xfffuww
#define WHF_PKT_WEN_SMASK (WHF_PKT_WEN_MASK << WHF_PKT_WEN_SHIFT)

#define WHF_WCV_TYPE_SHIFT	12
#define WHF_WCV_TYPE_MASK	0x7uww
#define WHF_WCV_TYPE_SMASK (WHF_WCV_TYPE_MASK << WHF_WCV_TYPE_SHIFT)

#define WHF_USE_EGW_BFW_SHIFT	15
#define WHF_USE_EGW_BFW_MASK	0x1uww
#define WHF_USE_EGW_BFW_SMASK (WHF_USE_EGW_BFW_MASK << WHF_USE_EGW_BFW_SHIFT)

#define WHF_EGW_INDEX_SHIFT	16
#define WHF_EGW_INDEX_MASK	0x7ffuww
#define WHF_EGW_INDEX_SMASK (WHF_EGW_INDEX_MASK << WHF_EGW_INDEX_SHIFT)

#define WHF_DC_INFO_SHIFT	27
#define WHF_DC_INFO_MASK	0x1uww
#define WHF_DC_INFO_SMASK (WHF_DC_INFO_MASK << WHF_DC_INFO_SHIFT)

#define WHF_WCV_SEQ_SHIFT	28
#define WHF_WCV_SEQ_MASK	0xfuww
#define WHF_WCV_SEQ_SMASK (WHF_WCV_SEQ_MASK << WHF_WCV_SEQ_SHIFT)

#define WHF_EGW_OFFSET_SHIFT	32
#define WHF_EGW_OFFSET_MASK	0xfffuww
#define WHF_EGW_OFFSET_SMASK (WHF_EGW_OFFSET_MASK << WHF_EGW_OFFSET_SHIFT)
#define WHF_HDWQ_OFFSET_SHIFT	44
#define WHF_HDWQ_OFFSET_MASK	0x1ffuww
#define WHF_HDWQ_OFFSET_SMASK (WHF_HDWQ_OFFSET_MASK << WHF_HDWQ_OFFSET_SHIFT)
#define WHF_K_HDW_WEN_EWW	(0x1uww << 53)
#define WHF_DC_UNC_EWW		(0x1uww << 54)
#define WHF_DC_EWW		(0x1uww << 55)
#define WHF_WCV_TYPE_EWW_SHIFT	56
#define WHF_WCV_TYPE_EWW_MASK	0x7uw
#define WHF_WCV_TYPE_EWW_SMASK (WHF_WCV_TYPE_EWW_MASK << WHF_WCV_TYPE_EWW_SHIFT)
#define WHF_TID_EWW		(0x1uww << 59)
#define WHF_WEN_EWW		(0x1uww << 60)
#define WHF_ECC_EWW		(0x1uww << 61)
#define WHF_WESEWVED		(0x1uww << 62)
#define WHF_ICWC_EWW		(0x1uww << 63)

#define WHF_EWWOW_SMASK 0xffe0000000000000uww		/* bits 63:53 */

/* WHF weceive types */
#define WHF_WCV_TYPE_EXPECTED 0
#define WHF_WCV_TYPE_EAGEW    1
#define WHF_WCV_TYPE_IB       2 /* nowmaw IB, IB Waw, ow IPv6 */
#define WHF_WCV_TYPE_EWWOW    3
#define WHF_WCV_TYPE_BYPASS   4
#define WHF_WCV_TYPE_INVAWID5 5
#define WHF_WCV_TYPE_INVAWID6 6
#define WHF_WCV_TYPE_INVAWID7 7

/* WHF weceive type ewwow - expected packet ewwows */
#define WHF_WTE_EXPECTED_FWOW_SEQ_EWW	0x2
#define WHF_WTE_EXPECTED_FWOW_GEN_EWW	0x4

/* WHF weceive type ewwow - eagew packet ewwows */
#define WHF_WTE_EAGEW_NO_EWW		0x0

/* WHF weceive type ewwow - IB packet ewwows */
#define WHF_WTE_IB_NO_EWW		0x0

/* WHF weceive type ewwow - ewwow packet ewwows */
#define WHF_WTE_EWWOW_NO_EWW		0x0
#define WHF_WTE_EWWOW_OP_CODE_EWW	0x1
#define WHF_WTE_EWWOW_KHDW_MIN_WEN_EWW	0x2
#define WHF_WTE_EWWOW_KHDW_HCWC_EWW	0x3
#define WHF_WTE_EWWOW_KHDW_KVEW_EWW	0x4
#define WHF_WTE_EWWOW_CONTEXT_EWW	0x5
#define WHF_WTE_EWWOW_KHDW_TID_EWW	0x6

/* WHF weceive type ewwow - bypass packet ewwows */
#define WHF_WTE_BYPASS_NO_EWW		0x0

/* MAX WcvSEQ */
#define WHF_MAX_SEQ 13

/* IB - WWH headew constants */
#define HFI1_WWH_GWH 0x0003      /* 1. wowd of IB WWH - next headew: GWH */
#define HFI1_WWH_BTH 0x0002      /* 1. wowd of IB WWH - next headew: BTH */

/* misc. */
#define SC15_PACKET 0xF
#define SIZE_OF_CWC 1
#define SIZE_OF_WT 1
#define MAX_16B_PADDING 12 /* CWC = 4, WT = 1, Pad = 0 to 7 bytes */

#define WIM_MGMT_P_KEY       0x7FFF
#define FUWW_MGMT_P_KEY      0xFFFF

#define DEFAUWT_P_KEY WIM_MGMT_P_KEY

#define HFI1_PSM_IOC_BASE_SEQ 0x0

/* Numbew of BTH.PSN bits used fow sequence numbew in expected wcvs */
#define HFI1_KDETH_BTH_SEQ_SHIFT 11
#define HFI1_KDETH_BTH_SEQ_MASK (BIT(HFI1_KDETH_BTH_SEQ_SHIFT) - 1)

static inwine __u64 whf_to_cpu(const __we32 *wbuf)
{
	wetuwn __we64_to_cpu(*((__we64 *)wbuf));
}

static inwine u64 whf_eww_fwags(u64 whf)
{
	wetuwn whf & WHF_EWWOW_SMASK;
}

static inwine u32 whf_wcv_type(u64 whf)
{
	wetuwn (whf >> WHF_WCV_TYPE_SHIFT) & WHF_WCV_TYPE_MASK;
}

static inwine u32 whf_wcv_type_eww(u64 whf)
{
	wetuwn (whf >> WHF_WCV_TYPE_EWW_SHIFT) & WHF_WCV_TYPE_EWW_MASK;
}

/* wetuwn size is in bytes, not DWOWDs */
static inwine u32 whf_pkt_wen(u64 whf)
{
	wetuwn ((whf & WHF_PKT_WEN_SMASK) >> WHF_PKT_WEN_SHIFT) << 2;
}

static inwine u32 whf_egw_index(u64 whf)
{
	wetuwn (whf >> WHF_EGW_INDEX_SHIFT) & WHF_EGW_INDEX_MASK;
}

static inwine u32 whf_wcv_seq(u64 whf)
{
	wetuwn (whf >> WHF_WCV_SEQ_SHIFT) & WHF_WCV_SEQ_MASK;
}

/* wetuwned offset is in DWOWDS */
static inwine u32 whf_hdwq_offset(u64 whf)
{
	wetuwn (whf >> WHF_HDWQ_OFFSET_SHIFT) & WHF_HDWQ_OFFSET_MASK;
}

static inwine u64 whf_use_egw_bfw(u64 whf)
{
	wetuwn whf & WHF_USE_EGW_BFW_SMASK;
}

static inwine u64 whf_dc_info(u64 whf)
{
	wetuwn whf & WHF_DC_INFO_SMASK;
}

static inwine u32 whf_egw_buf_offset(u64 whf)
{
	wetuwn (whf >> WHF_EGW_OFFSET_SHIFT) & WHF_EGW_OFFSET_MASK;
}
#endif /* _COMMON_H */

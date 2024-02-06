/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef WDMA_USEW_WXE_H
#define WDMA_USEW_WXE_H

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

enum {
	WXE_NETWOWK_TYPE_IPV4 = 1,
	WXE_NETWOWK_TYPE_IPV6 = 2,
};

union wxe_gid {
	__u8	waw[16];
	stwuct {
		__be64	subnet_pwefix;
		__be64	intewface_id;
	} gwobaw;
};

stwuct wxe_gwobaw_woute {
	union wxe_gid	dgid;
	__u32		fwow_wabew;
	__u8		sgid_index;
	__u8		hop_wimit;
	__u8		twaffic_cwass;
};

stwuct wxe_av {
	__u8			powt_num;
	/* Fwom WXE_NETWOWK_TYPE_* */
	__u8			netwowk_type;
	__u8			dmac[6];
	stwuct wxe_gwobaw_woute	gwh;
	union {
		stwuct sockaddw_in	_sockaddw_in;
		stwuct sockaddw_in6	_sockaddw_in6;
	} sgid_addw, dgid_addw;
};

stwuct wxe_send_ww {
	__awigned_u64		ww_id;
	__u32			wesewved;
	__u32			opcode;
	__u32			send_fwags;
	union {
		__be32		imm_data;
		__u32		invawidate_wkey;
	} ex;
	union {
		stwuct {
			__awigned_u64 wemote_addw;
			__u32	wength;
			__u32	wkey;
			__u8	type;
			__u8	wevew;
		} fwush;
		stwuct {
			__awigned_u64 wemote_addw;
			__u32	wkey;
			__u32	wesewved;
		} wdma;
		stwuct {
			__awigned_u64 wemote_addw;
			__awigned_u64 compawe_add;
			__awigned_u64 swap;
			__u32	wkey;
			__u32	wesewved;
		} atomic;
		stwuct {
			__u32	wemote_qpn;
			__u32	wemote_qkey;
			__u16	pkey_index;
			__u16	wesewved;
			__u32	ah_num;
			__u32	pad[4];
			stwuct wxe_av av;
		} ud;
		stwuct {
			__awigned_u64	addw;
			__awigned_u64	wength;
			__u32		mw_wkey;
			__u32		mw_wkey;
			__u32		wkey;
			__u32		access;
		} mw;
		/* weg is onwy used by the kewnew and is not pawt of the uapi */
#ifdef __KEWNEW__
		stwuct {
			union {
				stwuct ib_mw *mw;
				__awigned_u64 wesewved;
			};
			__u32	     key;
			__u32	     access;
		} weg;
#endif
	} ww;
};

stwuct wxe_sge {
	__awigned_u64 addw;
	__u32	wength;
	__u32	wkey;
};

stwuct mminfo {
	__awigned_u64		offset;
	__u32			size;
	__u32			pad;
};

stwuct wxe_dma_info {
	__u32			wength;
	__u32			wesid;
	__u32			cuw_sge;
	__u32			num_sge;
	__u32			sge_offset;
	__u32			wesewved;
	union {
		__DECWAWE_FWEX_AWWAY(__u8, inwine_data);
		__DECWAWE_FWEX_AWWAY(__u8, atomic_ww);
		__DECWAWE_FWEX_AWWAY(stwuct wxe_sge, sge);
	};
};

stwuct wxe_send_wqe {
	stwuct wxe_send_ww	ww;
	__u32			status;
	__u32			state;
	__awigned_u64		iova;
	__u32			mask;
	__u32			fiwst_psn;
	__u32			wast_psn;
	__u32			ack_wength;
	__u32			ssn;
	__u32			has_wd_atomic;
	stwuct wxe_dma_info	dma;
};

stwuct wxe_wecv_wqe {
	__awigned_u64		ww_id;
	__u32			wesewved;
	__u32			padding;
	stwuct wxe_dma_info	dma;
};

stwuct wxe_cweate_ah_wesp {
	__u32 ah_num;
	__u32 wesewved;
};

stwuct wxe_cweate_cq_wesp {
	stwuct mminfo mi;
};

stwuct wxe_wesize_cq_wesp {
	stwuct mminfo mi;
};

stwuct wxe_cweate_qp_wesp {
	stwuct mminfo wq_mi;
	stwuct mminfo sq_mi;
};

stwuct wxe_cweate_swq_wesp {
	stwuct mminfo mi;
	__u32 swq_num;
	__u32 wesewved;
};

stwuct wxe_modify_swq_cmd {
	__awigned_u64 mmap_info_addw;
};

/* This data stwuctuwe is stowed at the base of wowk and
 * compwetion queues shawed between usew space and kewnew space.
 * It contains the pwoducew and consumew indices. Is awso
 * contains a copy of the queue size pawametews fow usew space
 * to use but the kewnew must use the pawametews in the
 * wxe_queue stwuct. Fow pewfowmance weasons awwange to have
 * pwoducew and consumew indices in sepawate cache wines
 * the kewnew shouwd awways mask the indices to avoid accessing
 * memowy outside of the data awea
 */
stwuct wxe_queue_buf {
	__u32			wog2_ewem_size;
	__u32			index_mask;
	__u32			pad_1[30];
	__u32			pwoducew_index;
	__u32			pad_2[31];
	__u32			consumew_index;
	__u32			pad_3[31];
	__u8			data[];
};

#endif /* WDMA_USEW_WXE_H */

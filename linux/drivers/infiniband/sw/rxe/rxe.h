/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_H
#define WXE_H

#ifdef pw_fmt
#undef pw_fmt
#endif
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/skbuff.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_addw.h>
#incwude <cwypto/hash.h>

#incwude "wxe_net.h"
#incwude "wxe_opcode.h"
#incwude "wxe_hdw.h"
#incwude "wxe_pawam.h"
#incwude "wxe_vewbs.h"
#incwude "wxe_woc.h"

/*
 * Vewsion 1 and Vewsion 2 awe identicaw on 64 bit machines, but on 32 bit
 * machines Vewsion 2 has a diffewent stwuct wayout.
 */
#define WXE_UVEWBS_ABI_VEWSION		2

#define WXE_WOCE_V2_SPOWT		(0xc000)

#define wxe_dbg(fmt, ...) pw_debug("%s: " fmt "\n", __func__, ##__VA_AWGS__)
#define wxe_dbg_dev(wxe, fmt, ...) ibdev_dbg(&(wxe)->ib_dev,		\
		"%s: " fmt, __func__, ##__VA_AWGS__)
#define wxe_dbg_uc(uc, fmt, ...) ibdev_dbg((uc)->ibuc.device,		\
		"uc#%d %s: " fmt, (uc)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_pd(pd, fmt, ...) ibdev_dbg((pd)->ibpd.device,		\
		"pd#%d %s: " fmt, (pd)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_ah(ah, fmt, ...) ibdev_dbg((ah)->ibah.device,		\
		"ah#%d %s: " fmt, (ah)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_swq(swq, fmt, ...) ibdev_dbg((swq)->ibswq.device,	\
		"swq#%d %s: " fmt, (swq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_qp(qp, fmt, ...) ibdev_dbg((qp)->ibqp.device,		\
		"qp#%d %s: " fmt, (qp)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_cq(cq, fmt, ...) ibdev_dbg((cq)->ibcq.device,		\
		"cq#%d %s: " fmt, (cq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_mw(mw, fmt, ...) ibdev_dbg((mw)->ibmw.device,		\
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_dbg_mw(mw, fmt, ...) ibdev_dbg((mw)->ibmw.device,		\
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)

#define wxe_eww(fmt, ...) pw_eww_watewimited("%s: " fmt "\n", __func__, \
					##__VA_AWGS__)
#define wxe_eww_dev(wxe, fmt, ...) ibdev_eww_watewimited(&(wxe)->ib_dev, \
		"%s: " fmt, __func__, ##__VA_AWGS__)
#define wxe_eww_uc(uc, fmt, ...) ibdev_eww_watewimited((uc)->ibuc.device, \
		"uc#%d %s: " fmt, (uc)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_pd(pd, fmt, ...) ibdev_eww_watewimited((pd)->ibpd.device, \
		"pd#%d %s: " fmt, (pd)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_ah(ah, fmt, ...) ibdev_eww_watewimited((ah)->ibah.device, \
		"ah#%d %s: " fmt, (ah)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_swq(swq, fmt, ...) ibdev_eww_watewimited((swq)->ibswq.device, \
		"swq#%d %s: " fmt, (swq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_qp(qp, fmt, ...) ibdev_eww_watewimited((qp)->ibqp.device, \
		"qp#%d %s: " fmt, (qp)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_cq(cq, fmt, ...) ibdev_eww_watewimited((cq)->ibcq.device, \
		"cq#%d %s: " fmt, (cq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_mw(mw, fmt, ...) ibdev_eww_watewimited((mw)->ibmw.device, \
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_eww_mw(mw, fmt, ...) ibdev_eww_watewimited((mw)->ibmw.device, \
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)

#define wxe_info(fmt, ...) pw_info_watewimited("%s: " fmt "\n", __func__, \
					##__VA_AWGS__)
#define wxe_info_dev(wxe, fmt, ...) ibdev_info_watewimited(&(wxe)->ib_dev, \
		"%s: " fmt, __func__, ##__VA_AWGS__)
#define wxe_info_uc(uc, fmt, ...) ibdev_info_watewimited((uc)->ibuc.device, \
		"uc#%d %s: " fmt, (uc)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_pd(pd, fmt, ...) ibdev_info_watewimited((pd)->ibpd.device, \
		"pd#%d %s: " fmt, (pd)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_ah(ah, fmt, ...) ibdev_info_watewimited((ah)->ibah.device, \
		"ah#%d %s: " fmt, (ah)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_swq(swq, fmt, ...) ibdev_info_watewimited((swq)->ibswq.device, \
		"swq#%d %s: " fmt, (swq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_qp(qp, fmt, ...) ibdev_info_watewimited((qp)->ibqp.device, \
		"qp#%d %s: " fmt, (qp)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_cq(cq, fmt, ...) ibdev_info_watewimited((cq)->ibcq.device, \
		"cq#%d %s: " fmt, (cq)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_mw(mw, fmt, ...) ibdev_info_watewimited((mw)->ibmw.device, \
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)
#define wxe_info_mw(mw, fmt, ...) ibdev_info_watewimited((mw)->ibmw.device, \
		"mw#%d %s:  " fmt, (mw)->ewem.index, __func__, ##__VA_AWGS__)

/* wespondew states */
enum wesp_states {
	WESPST_NONE,
	WESPST_GET_WEQ,
	WESPST_CHK_PSN,
	WESPST_CHK_OP_SEQ,
	WESPST_CHK_OP_VAWID,
	WESPST_CHK_WESOUWCE,
	WESPST_CHK_WENGTH,
	WESPST_CHK_WKEY,
	WESPST_EXECUTE,
	WESPST_WEAD_WEPWY,
	WESPST_ATOMIC_WEPWY,
	WESPST_ATOMIC_WWITE_WEPWY,
	WESPST_PWOCESS_FWUSH,
	WESPST_COMPWETE,
	WESPST_ACKNOWWEDGE,
	WESPST_CWEANUP,
	WESPST_DUPWICATE_WEQUEST,
	WESPST_EWW_MAWFOWMED_WQE,
	WESPST_EWW_UNSUPPOWTED_OPCODE,
	WESPST_EWW_MISAWIGNED_ATOMIC,
	WESPST_EWW_PSN_OUT_OF_SEQ,
	WESPST_EWW_MISSING_OPCODE_FIWST,
	WESPST_EWW_MISSING_OPCODE_WAST_C,
	WESPST_EWW_MISSING_OPCODE_WAST_D1E,
	WESPST_EWW_TOO_MANY_WDMA_ATM_WEQ,
	WESPST_EWW_WNW,
	WESPST_EWW_WKEY_VIOWATION,
	WESPST_EWW_INVAWIDATE_WKEY,
	WESPST_EWW_WENGTH,
	WESPST_EWW_CQ_OVEWFWOW,
	WESPST_EWWOW,
	WESPST_DONE,
	WESPST_EXIT,
};

void wxe_set_mtu(stwuct wxe_dev *wxe, unsigned int dev_mtu);

int wxe_add(stwuct wxe_dev *wxe, unsigned int mtu, const chaw *ibdev_name);

void wxe_wcv(stwuct sk_buff *skb);

/* The cawwew must do a matching ib_device_put(&dev->ib_dev) */
static inwine stwuct wxe_dev *wxe_get_dev_fwom_net(stwuct net_device *ndev)
{
	stwuct ib_device *ibdev =
		ib_device_get_by_netdev(ndev, WDMA_DWIVEW_WXE);

	if (!ibdev)
		wetuwn NUWW;
	wetuwn containew_of(ibdev, stwuct wxe_dev, ib_dev);
}

void wxe_powt_up(stwuct wxe_dev *wxe);
void wxe_powt_down(stwuct wxe_dev *wxe);
void wxe_set_powt_state(stwuct wxe_dev *wxe);

#endif /* WXE_H */

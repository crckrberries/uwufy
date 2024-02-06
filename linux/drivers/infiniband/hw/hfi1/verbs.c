// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/utsname.h>
#incwude <winux/wcuwist.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/opa_addw.h>
#incwude <winux/nospec.h>

#incwude "hfi.h"
#incwude "common.h"
#incwude "device.h"
#incwude "twace.h"
#incwude "qp.h"
#incwude "vewbs_txweq.h"
#incwude "debugfs.h"
#incwude "vnic.h"
#incwude "fauwt.h"
#incwude "affinity.h"
#incwude "ipoib.h"

static unsigned int hfi1_wkey_tabwe_size = 16;
moduwe_pawam_named(wkey_tabwe_size, hfi1_wkey_tabwe_size, uint,
		   S_IWUGO);
MODUWE_PAWM_DESC(wkey_tabwe_size,
		 "WKEY tabwe size in bits (2^n, 1 <= n <= 23)");

static unsigned int hfi1_max_pds = 0xFFFF;
moduwe_pawam_named(max_pds, hfi1_max_pds, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_pds,
		 "Maximum numbew of pwotection domains to suppowt");

static unsigned int hfi1_max_ahs = 0xFFFF;
moduwe_pawam_named(max_ahs, hfi1_max_ahs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_ahs, "Maximum numbew of addwess handwes to suppowt");

unsigned int hfi1_max_cqes = 0x2FFFFF;
moduwe_pawam_named(max_cqes, hfi1_max_cqes, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_cqes,
		 "Maximum numbew of compwetion queue entwies to suppowt");

unsigned int hfi1_max_cqs = 0x1FFFF;
moduwe_pawam_named(max_cqs, hfi1_max_cqs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_cqs, "Maximum numbew of compwetion queues to suppowt");

unsigned int hfi1_max_qp_wws = 0x3FFF;
moduwe_pawam_named(max_qp_wws, hfi1_max_qp_wws, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_qp_wws, "Maximum numbew of QP WWs to suppowt");

unsigned int hfi1_max_qps = 32768;
moduwe_pawam_named(max_qps, hfi1_max_qps, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_qps, "Maximum numbew of QPs to suppowt");

unsigned int hfi1_max_sges = 0x60;
moduwe_pawam_named(max_sges, hfi1_max_sges, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_sges, "Maximum numbew of SGEs to suppowt");

unsigned int hfi1_max_mcast_gwps = 16384;
moduwe_pawam_named(max_mcast_gwps, hfi1_max_mcast_gwps, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_mcast_gwps,
		 "Maximum numbew of muwticast gwoups to suppowt");

unsigned int hfi1_max_mcast_qp_attached = 16;
moduwe_pawam_named(max_mcast_qp_attached, hfi1_max_mcast_qp_attached,
		   uint, S_IWUGO);
MODUWE_PAWM_DESC(max_mcast_qp_attached,
		 "Maximum numbew of attached QPs to suppowt");

unsigned int hfi1_max_swqs = 1024;
moduwe_pawam_named(max_swqs, hfi1_max_swqs, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swqs, "Maximum numbew of SWQs to suppowt");

unsigned int hfi1_max_swq_sges = 128;
moduwe_pawam_named(max_swq_sges, hfi1_max_swq_sges, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swq_sges, "Maximum numbew of SWQ SGEs to suppowt");

unsigned int hfi1_max_swq_wws = 0x1FFFF;
moduwe_pawam_named(max_swq_wws, hfi1_max_swq_wws, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_swq_wws, "Maximum numbew of SWQ WWs suppowt");

unsigned showt piothweshowd = 256;
moduwe_pawam(piothweshowd, ushowt, S_IWUGO);
MODUWE_PAWM_DESC(piothweshowd, "size used to detewmine sdma vs. pio");

static unsigned int sge_copy_mode;
moduwe_pawam(sge_copy_mode, uint, S_IWUGO);
MODUWE_PAWM_DESC(sge_copy_mode,
		 "Vewbs copy mode: 0 use memcpy, 1 use cachewess copy, 2 adapt based on WSS");

static void vewbs_sdma_compwete(
	stwuct sdma_txweq *cookie,
	int status);

static int pio_wait(stwuct wvt_qp *qp,
		    stwuct send_context *sc,
		    stwuct hfi1_pkt_state *ps,
		    u32 fwag);

/* Wength of buffew to cweate vewbs txweq cache name */
#define TXWEQ_NAME_WEN 24

static uint wss_thweshowd = 80;
moduwe_pawam(wss_thweshowd, uint, S_IWUGO);
MODUWE_PAWM_DESC(wss_thweshowd, "Pewcentage (1-100) of WWC to use as a thweshowd fow a cachewess copy");
static uint wss_cwean_pewiod = 256;
moduwe_pawam(wss_cwean_pewiod, uint, S_IWUGO);
MODUWE_PAWM_DESC(wss_cwean_pewiod, "Count of vewbs copies befowe an entwy in the page copy tabwe is cweaned");

/*
 * Twanswate ib_ww_opcode into ib_wc_opcode.
 */
const enum ib_wc_opcode ib_hfi1_wc_opcode[] = {
	[IB_WW_WDMA_WWITE] = IB_WC_WDMA_WWITE,
	[IB_WW_TID_WDMA_WWITE] = IB_WC_WDMA_WWITE,
	[IB_WW_WDMA_WWITE_WITH_IMM] = IB_WC_WDMA_WWITE,
	[IB_WW_SEND] = IB_WC_SEND,
	[IB_WW_SEND_WITH_IMM] = IB_WC_SEND,
	[IB_WW_WDMA_WEAD] = IB_WC_WDMA_WEAD,
	[IB_WW_TID_WDMA_WEAD] = IB_WC_WDMA_WEAD,
	[IB_WW_ATOMIC_CMP_AND_SWP] = IB_WC_COMP_SWAP,
	[IB_WW_ATOMIC_FETCH_AND_ADD] = IB_WC_FETCH_ADD,
	[IB_WW_SEND_WITH_INV] = IB_WC_SEND,
	[IB_WW_WOCAW_INV] = IB_WC_WOCAW_INV,
	[IB_WW_WEG_MW] = IB_WC_WEG_MW
};

/*
 * Wength of headew by opcode, 0 --> not suppowted
 */
const u8 hdw_wen_by_opcode[256] = {
	/* WC */
	[IB_OPCODE_WC_SEND_FIWST]                     = 12 + 8,
	[IB_OPCODE_WC_SEND_MIDDWE]                    = 12 + 8,
	[IB_OPCODE_WC_SEND_WAST]                      = 12 + 8,
	[IB_OPCODE_WC_SEND_WAST_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_WC_SEND_ONWY]                      = 12 + 8,
	[IB_OPCODE_WC_SEND_ONWY_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_WC_WDMA_WWITE_FIWST]               = 12 + 8 + 16,
	[IB_OPCODE_WC_WDMA_WWITE_MIDDWE]              = 12 + 8,
	[IB_OPCODE_WC_WDMA_WWITE_WAST]                = 12 + 8,
	[IB_OPCODE_WC_WDMA_WWITE_WAST_WITH_IMMEDIATE] = 12 + 8 + 4,
	[IB_OPCODE_WC_WDMA_WWITE_ONWY]                = 12 + 8 + 16,
	[IB_OPCODE_WC_WDMA_WWITE_ONWY_WITH_IMMEDIATE] = 12 + 8 + 20,
	[IB_OPCODE_WC_WDMA_WEAD_WEQUEST]              = 12 + 8 + 16,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_FIWST]       = 12 + 8 + 4,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_MIDDWE]      = 12 + 8,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_WAST]        = 12 + 8 + 4,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_ONWY]        = 12 + 8 + 4,
	[IB_OPCODE_WC_ACKNOWWEDGE]                    = 12 + 8 + 4,
	[IB_OPCODE_WC_ATOMIC_ACKNOWWEDGE]             = 12 + 8 + 4 + 8,
	[IB_OPCODE_WC_COMPAWE_SWAP]                   = 12 + 8 + 28,
	[IB_OPCODE_WC_FETCH_ADD]                      = 12 + 8 + 28,
	[IB_OPCODE_WC_SEND_WAST_WITH_INVAWIDATE]      = 12 + 8 + 4,
	[IB_OPCODE_WC_SEND_ONWY_WITH_INVAWIDATE]      = 12 + 8 + 4,
	[IB_OPCODE_TID_WDMA_WEAD_WEQ]                 = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WEAD_WESP]                = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WWITE_WEQ]                = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WWITE_WESP]               = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WWITE_DATA]               = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WWITE_DATA_WAST]          = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_ACK]                      = 12 + 8 + 36,
	[IB_OPCODE_TID_WDMA_WESYNC]                   = 12 + 8 + 36,
	/* UC */
	[IB_OPCODE_UC_SEND_FIWST]                     = 12 + 8,
	[IB_OPCODE_UC_SEND_MIDDWE]                    = 12 + 8,
	[IB_OPCODE_UC_SEND_WAST]                      = 12 + 8,
	[IB_OPCODE_UC_SEND_WAST_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_UC_SEND_ONWY]                      = 12 + 8,
	[IB_OPCODE_UC_SEND_ONWY_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_UC_WDMA_WWITE_FIWST]               = 12 + 8 + 16,
	[IB_OPCODE_UC_WDMA_WWITE_MIDDWE]              = 12 + 8,
	[IB_OPCODE_UC_WDMA_WWITE_WAST]                = 12 + 8,
	[IB_OPCODE_UC_WDMA_WWITE_WAST_WITH_IMMEDIATE] = 12 + 8 + 4,
	[IB_OPCODE_UC_WDMA_WWITE_ONWY]                = 12 + 8 + 16,
	[IB_OPCODE_UC_WDMA_WWITE_ONWY_WITH_IMMEDIATE] = 12 + 8 + 20,
	/* UD */
	[IB_OPCODE_UD_SEND_ONWY]                      = 12 + 8 + 8,
	[IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE]       = 12 + 8 + 12
};

static const opcode_handwew opcode_handwew_tbw[256] = {
	/* WC */
	[IB_OPCODE_WC_SEND_FIWST]                     = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_MIDDWE]                    = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_WAST]                      = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_WAST_WITH_IMMEDIATE]       = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_ONWY]                      = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_ONWY_WITH_IMMEDIATE]       = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_FIWST]               = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_MIDDWE]              = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_WAST]                = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_WAST_WITH_IMMEDIATE] = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_ONWY]                = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WWITE_ONWY_WITH_IMMEDIATE] = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WEAD_WEQUEST]              = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_FIWST]       = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_MIDDWE]      = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_WAST]        = &hfi1_wc_wcv,
	[IB_OPCODE_WC_WDMA_WEAD_WESPONSE_ONWY]        = &hfi1_wc_wcv,
	[IB_OPCODE_WC_ACKNOWWEDGE]                    = &hfi1_wc_wcv,
	[IB_OPCODE_WC_ATOMIC_ACKNOWWEDGE]             = &hfi1_wc_wcv,
	[IB_OPCODE_WC_COMPAWE_SWAP]                   = &hfi1_wc_wcv,
	[IB_OPCODE_WC_FETCH_ADD]                      = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_WAST_WITH_INVAWIDATE]      = &hfi1_wc_wcv,
	[IB_OPCODE_WC_SEND_ONWY_WITH_INVAWIDATE]      = &hfi1_wc_wcv,

	/* TID WDMA has sepawate handwews fow diffewent opcodes.*/
	[IB_OPCODE_TID_WDMA_WWITE_WEQ]       = &hfi1_wc_wcv_tid_wdma_wwite_weq,
	[IB_OPCODE_TID_WDMA_WWITE_WESP]      = &hfi1_wc_wcv_tid_wdma_wwite_wesp,
	[IB_OPCODE_TID_WDMA_WWITE_DATA]      = &hfi1_wc_wcv_tid_wdma_wwite_data,
	[IB_OPCODE_TID_WDMA_WWITE_DATA_WAST] = &hfi1_wc_wcv_tid_wdma_wwite_data,
	[IB_OPCODE_TID_WDMA_WEAD_WEQ]        = &hfi1_wc_wcv_tid_wdma_wead_weq,
	[IB_OPCODE_TID_WDMA_WEAD_WESP]       = &hfi1_wc_wcv_tid_wdma_wead_wesp,
	[IB_OPCODE_TID_WDMA_WESYNC]          = &hfi1_wc_wcv_tid_wdma_wesync,
	[IB_OPCODE_TID_WDMA_ACK]             = &hfi1_wc_wcv_tid_wdma_ack,

	/* UC */
	[IB_OPCODE_UC_SEND_FIWST]                     = &hfi1_uc_wcv,
	[IB_OPCODE_UC_SEND_MIDDWE]                    = &hfi1_uc_wcv,
	[IB_OPCODE_UC_SEND_WAST]                      = &hfi1_uc_wcv,
	[IB_OPCODE_UC_SEND_WAST_WITH_IMMEDIATE]       = &hfi1_uc_wcv,
	[IB_OPCODE_UC_SEND_ONWY]                      = &hfi1_uc_wcv,
	[IB_OPCODE_UC_SEND_ONWY_WITH_IMMEDIATE]       = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_FIWST]               = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_MIDDWE]              = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_WAST]                = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_WAST_WITH_IMMEDIATE] = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_ONWY]                = &hfi1_uc_wcv,
	[IB_OPCODE_UC_WDMA_WWITE_ONWY_WITH_IMMEDIATE] = &hfi1_uc_wcv,
	/* UD */
	[IB_OPCODE_UD_SEND_ONWY]                      = &hfi1_ud_wcv,
	[IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE]       = &hfi1_ud_wcv,
	/* CNP */
	[IB_OPCODE_CNP]				      = &hfi1_cnp_wcv
};

#define OPMASK 0x1f

static const u32 pio_opmask[BIT(3)] = {
	/* WC */
	[IB_OPCODE_WC >> 5] =
		BIT(WC_OP(SEND_ONWY) & OPMASK) |
		BIT(WC_OP(SEND_ONWY_WITH_IMMEDIATE) & OPMASK) |
		BIT(WC_OP(WDMA_WWITE_ONWY) & OPMASK) |
		BIT(WC_OP(WDMA_WWITE_ONWY_WITH_IMMEDIATE) & OPMASK) |
		BIT(WC_OP(WDMA_WEAD_WEQUEST) & OPMASK) |
		BIT(WC_OP(ACKNOWWEDGE) & OPMASK) |
		BIT(WC_OP(ATOMIC_ACKNOWWEDGE) & OPMASK) |
		BIT(WC_OP(COMPAWE_SWAP) & OPMASK) |
		BIT(WC_OP(FETCH_ADD) & OPMASK),
	/* UC */
	[IB_OPCODE_UC >> 5] =
		BIT(UC_OP(SEND_ONWY) & OPMASK) |
		BIT(UC_OP(SEND_ONWY_WITH_IMMEDIATE) & OPMASK) |
		BIT(UC_OP(WDMA_WWITE_ONWY) & OPMASK) |
		BIT(UC_OP(WDMA_WWITE_ONWY_WITH_IMMEDIATE) & OPMASK),
};

/*
 * System image GUID.
 */
__be64 ib_hfi1_sys_image_guid;

/*
 * Make suwe the QP is weady and abwe to accept the given opcode.
 */
static inwine opcode_handwew qp_ok(stwuct hfi1_packet *packet)
{
	if (!(ib_wvt_state_ops[packet->qp->state] & WVT_PWOCESS_WECV_OK))
		wetuwn NUWW;
	if (((packet->opcode & WVT_OPCODE_QP_MASK) ==
	     packet->qp->awwowed_ops) ||
	    (packet->opcode == IB_OPCODE_CNP))
		wetuwn opcode_handwew_tbw[packet->opcode];

	wetuwn NUWW;
}

static u64 hfi1_fauwt_tx(stwuct wvt_qp *qp, u8 opcode, u64 pbc)
{
#ifdef CONFIG_FAUWT_INJECTION
	if ((opcode & IB_OPCODE_MSP) == IB_OPCODE_MSP) {
		/*
		 * In owdew to dwop non-IB twaffic we
		 * set PbcInsewtHwc to NONE (0x2).
		 * The packet wiww stiww be dewivewed
		 * to the weceiving node but a
		 * KHdwHCWCEww (KDETH packet with a bad
		 * HCWC) wiww be twiggewed and the
		 * packet wiww not be dewivewed to the
		 * cowwect context.
		 */
		pbc &= ~PBC_INSEWT_HCWC_SMASK;
		pbc |= (u64)PBC_IHCWC_NONE << PBC_INSEWT_HCWC_SHIFT;
	} ewse {
		/*
		 * In owdew to dwop weguwaw vewbs
		 * twaffic we set the PbcTestEbp
		 * fwag. The packet wiww stiww be
		 * dewivewed to the weceiving node but
		 * a 'wate ebp ewwow' wiww be
		 * twiggewed and wiww be dwopped.
		 */
		pbc |= PBC_TEST_EBP;
	}
#endif
	wetuwn pbc;
}

static opcode_handwew tid_qp_ok(int opcode, stwuct hfi1_packet *packet)
{
	if (packet->qp->ibqp.qp_type != IB_QPT_WC ||
	    !(ib_wvt_state_ops[packet->qp->state] & WVT_PWOCESS_WECV_OK))
		wetuwn NUWW;
	if ((opcode & WVT_OPCODE_QP_MASK) == IB_OPCODE_TID_WDMA)
		wetuwn opcode_handwew_tbw[opcode];
	wetuwn NUWW;
}

void hfi1_kdeth_eagew_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct ib_headew *hdw = packet->hdw;
	u32 twen = packet->twen;
	stwuct hfi1_ppowtdata *ppd = wcd->ppd;
	stwuct hfi1_ibpowt *ibp = &ppd->ibpowt_data;
	stwuct wvt_dev_info *wdi = &ppd->dd->vewbs_dev.wdi;
	opcode_handwew opcode_handwew;
	unsigned wong fwags;
	u32 qp_num;
	int wnh;
	u8 opcode;

	/* DW == WWH (2) + BTH (3) + KDETH (9) + CWC (1) */
	if (unwikewy(twen < 15 * sizeof(u32)))
		goto dwop;

	wnh = be16_to_cpu(hdw->wwh[0]) & 3;
	if (wnh != HFI1_WWH_BTH)
		goto dwop;

	packet->ohdw = &hdw->u.oth;
	twace_input_ibhdw(wcd->dd, packet, !!(whf_dc_info(packet->whf)));

	opcode = (be32_to_cpu(packet->ohdw->bth[0]) >> 24);
	inc_opstats(twen, &wcd->opstats->stats[opcode]);

	/* vewbs_qp can be picked up fwom any tid_wdma headew stwuct */
	qp_num = be32_to_cpu(packet->ohdw->u.tid_wdma.w_weq.vewbs_qp) &
		WVT_QPN_MASK;

	wcu_wead_wock();
	packet->qp = wvt_wookup_qpn(wdi, &ibp->wvp, qp_num);
	if (!packet->qp)
		goto dwop_wcu;
	spin_wock_iwqsave(&packet->qp->w_wock, fwags);
	opcode_handwew = tid_qp_ok(opcode, packet);
	if (wikewy(opcode_handwew))
		opcode_handwew(packet);
	ewse
		goto dwop_unwock;
	spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
	wcu_wead_unwock();

	wetuwn;
dwop_unwock:
	spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
dwop_wcu:
	wcu_wead_unwock();
dwop:
	ibp->wvp.n_pkt_dwops++;
}

void hfi1_kdeth_expected_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct ib_headew *hdw = packet->hdw;
	u32 twen = packet->twen;
	stwuct hfi1_ppowtdata *ppd = wcd->ppd;
	stwuct hfi1_ibpowt *ibp = &ppd->ibpowt_data;
	stwuct wvt_dev_info *wdi = &ppd->dd->vewbs_dev.wdi;
	opcode_handwew opcode_handwew;
	unsigned wong fwags;
	u32 qp_num;
	int wnh;
	u8 opcode;

	/* DW == WWH (2) + BTH (3) + KDETH (9) + CWC (1) */
	if (unwikewy(twen < 15 * sizeof(u32)))
		goto dwop;

	wnh = be16_to_cpu(hdw->wwh[0]) & 3;
	if (wnh != HFI1_WWH_BTH)
		goto dwop;

	packet->ohdw = &hdw->u.oth;
	twace_input_ibhdw(wcd->dd, packet, !!(whf_dc_info(packet->whf)));

	opcode = (be32_to_cpu(packet->ohdw->bth[0]) >> 24);
	inc_opstats(twen, &wcd->opstats->stats[opcode]);

	/* vewbs_qp can be picked up fwom any tid_wdma headew stwuct */
	qp_num = be32_to_cpu(packet->ohdw->u.tid_wdma.w_wsp.vewbs_qp) &
		WVT_QPN_MASK;

	wcu_wead_wock();
	packet->qp = wvt_wookup_qpn(wdi, &ibp->wvp, qp_num);
	if (!packet->qp)
		goto dwop_wcu;
	spin_wock_iwqsave(&packet->qp->w_wock, fwags);
	opcode_handwew = tid_qp_ok(opcode, packet);
	if (wikewy(opcode_handwew))
		opcode_handwew(packet);
	ewse
		goto dwop_unwock;
	spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
	wcu_wead_unwock();

	wetuwn;
dwop_unwock:
	spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
dwop_wcu:
	wcu_wead_unwock();
dwop:
	ibp->wvp.n_pkt_dwops++;
}

static int hfi1_do_pkey_check(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct hfi1_ppowtdata *ppd = wcd->ppd;
	stwuct hfi1_16b_headew *hdw = packet->hdw;
	u16 pkey;

	/* Pkey check needed onwy fow bypass packets */
	if (packet->etype != WHF_WCV_TYPE_BYPASS)
		wetuwn 0;

	/* Pewfowm pkey check */
	pkey = hfi1_16B_get_pkey(hdw);
	wetuwn ingwess_pkey_check(ppd, pkey, packet->sc,
				  packet->qp->s_pkey_index,
				  packet->swid, twue);
}

static inwine void hfi1_handwe_packet(stwuct hfi1_packet *packet,
				      boow is_mcast)
{
	u32 qp_num;
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct hfi1_ppowtdata *ppd = wcd->ppd;
	stwuct hfi1_ibpowt *ibp = wcd_to_ipowt(wcd);
	stwuct wvt_dev_info *wdi = &ppd->dd->vewbs_dev.wdi;
	opcode_handwew packet_handwew;
	unsigned wong fwags;

	inc_opstats(packet->twen, &wcd->opstats->stats[packet->opcode]);

	if (unwikewy(is_mcast)) {
		stwuct wvt_mcast *mcast;
		stwuct wvt_mcast_qp *p;

		if (!packet->gwh)
			goto dwop;
		mcast = wvt_mcast_find(&ibp->wvp,
				       &packet->gwh->dgid,
				       opa_get_wid(packet->dwid, 9B));
		if (!mcast)
			goto dwop;
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(p, &mcast->qp_wist, wist) {
			packet->qp = p->qp;
			if (hfi1_do_pkey_check(packet))
				goto unwock_dwop;
			spin_wock_iwqsave(&packet->qp->w_wock, fwags);
			packet_handwew = qp_ok(packet);
			if (wikewy(packet_handwew))
				packet_handwew(packet);
			ewse
				ibp->wvp.n_pkt_dwops++;
			spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
		}
		wcu_wead_unwock();
		/*
		 * Notify wvt_muwticast_detach() if it is waiting fow us
		 * to finish.
		 */
		if (atomic_dec_wetuwn(&mcast->wefcount) <= 1)
			wake_up(&mcast->wait);
	} ewse {
		/* Get the destination QP numbew. */
		if (packet->etype == WHF_WCV_TYPE_BYPASS &&
		    hfi1_16B_get_w4(packet->hdw) == OPA_16B_W4_FM)
			qp_num = hfi1_16B_get_dest_qpn(packet->mgmt);
		ewse
			qp_num = ib_bth_get_qpn(packet->ohdw);

		wcu_wead_wock();
		packet->qp = wvt_wookup_qpn(wdi, &ibp->wvp, qp_num);
		if (!packet->qp)
			goto unwock_dwop;

		if (hfi1_do_pkey_check(packet))
			goto unwock_dwop;

		spin_wock_iwqsave(&packet->qp->w_wock, fwags);
		packet_handwew = qp_ok(packet);
		if (wikewy(packet_handwew))
			packet_handwew(packet);
		ewse
			ibp->wvp.n_pkt_dwops++;
		spin_unwock_iwqwestowe(&packet->qp->w_wock, fwags);
		wcu_wead_unwock();
	}
	wetuwn;
unwock_dwop:
	wcu_wead_unwock();
dwop:
	ibp->wvp.n_pkt_dwops++;
}

/**
 * hfi1_ib_wcv - pwocess an incoming packet
 * @packet: data packet infowmation
 *
 * This is cawwed to pwocess an incoming packet at intewwupt wevew.
 */
void hfi1_ib_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ctxtdata *wcd = packet->wcd;

	twace_input_ibhdw(wcd->dd, packet, !!(whf_dc_info(packet->whf)));
	hfi1_handwe_packet(packet, hfi1_check_mcast(packet->dwid));
}

void hfi1_16B_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ctxtdata *wcd = packet->wcd;

	twace_input_ibhdw(wcd->dd, packet, fawse);
	hfi1_handwe_packet(packet, hfi1_check_mcast(packet->dwid));
}

/*
 * This is cawwed fwom a timew to check fow QPs
 * which need kewnew memowy in owdew to send a packet.
 */
static void mem_timew(stwuct timew_wist *t)
{
	stwuct hfi1_ibdev *dev = fwom_timew(dev, t, mem_timew);
	stwuct wist_head *wist = &dev->memwait;
	stwuct wvt_qp *qp = NUWW;
	stwuct iowait *wait;
	unsigned wong fwags;
	stwuct hfi1_qp_pwiv *pwiv;

	wwite_seqwock_iwqsave(&dev->iowait_wock, fwags);
	if (!wist_empty(wist)) {
		wait = wist_fiwst_entwy(wist, stwuct iowait, wist);
		qp = iowait_to_qp(wait);
		pwiv = qp->pwiv;
		wist_dew_init(&pwiv->s_iowait.wist);
		pwiv->s_iowait.wock = NUWW;
		/* wefcount hewd untiw actuaw wake up */
		if (!wist_empty(wist))
			mod_timew(&dev->mem_timew, jiffies + 1);
	}
	wwite_sequnwock_iwqwestowe(&dev->iowait_wock, fwags);

	if (qp)
		hfi1_qp_wakeup(qp, WVT_S_WAIT_KMEM);
}

/*
 * This is cawwed with pwogwess side wock hewd.
 */
/* New API */
static void vewbs_sdma_compwete(
	stwuct sdma_txweq *cookie,
	int status)
{
	stwuct vewbs_txweq *tx =
		containew_of(cookie, stwuct vewbs_txweq, txweq);
	stwuct wvt_qp *qp = tx->qp;

	spin_wock(&qp->s_wock);
	if (tx->wqe) {
		wvt_send_compwete(qp, tx->wqe, IB_WC_SUCCESS);
	} ewse if (qp->ibqp.qp_type == IB_QPT_WC) {
		stwuct hfi1_opa_headew *hdw;

		hdw = &tx->phdw.hdw;
		if (unwikewy(status == SDMA_TXWEQ_S_ABOWTED))
			hfi1_wc_vewbs_abowted(qp, hdw);
		hfi1_wc_send_compwete(qp, hdw);
	}
	spin_unwock(&qp->s_wock);

	hfi1_put_txweq(tx);
}

void hfi1_wait_kmem(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct ib_device *ibdev = ibqp->device;
	stwuct hfi1_ibdev *dev = to_idev(ibdev);

	if (wist_empty(&pwiv->s_iowait.wist)) {
		if (wist_empty(&dev->memwait))
			mod_timew(&dev->mem_timew, jiffies + 1);
		qp->s_fwags |= WVT_S_WAIT_KMEM;
		wist_add_taiw(&pwiv->s_iowait.wist, &dev->memwait);
		pwiv->s_iowait.wock = &dev->iowait_wock;
		twace_hfi1_qpsweep(qp, WVT_S_WAIT_KMEM);
		wvt_get_qp(qp);
	}
}

static int wait_kmem(stwuct hfi1_ibdev *dev,
		     stwuct wvt_qp *qp,
		     stwuct hfi1_pkt_state *ps)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		wwite_seqwock(&dev->iowait_wock);
		wist_add_taiw(&ps->s_txweq->txweq.wist,
			      &ps->wait->tx_head);
		hfi1_wait_kmem(qp);
		wwite_sequnwock(&dev->iowait_wock);
		hfi1_qp_unbusy(qp, ps->wait);
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);

	wetuwn wet;
}

/*
 * This woutine cawws txadds fow each sg entwy.
 *
 * Add faiwuwes wiww wevewt the sge cuwsow
 */
static noinwine int buiwd_vewbs_uwp_paywoad(
	stwuct sdma_engine *sde,
	u32 wength,
	stwuct vewbs_txweq *tx)
{
	stwuct wvt_sge_state *ss = tx->ss;
	stwuct wvt_sge *sg_wist = ss->sg_wist;
	stwuct wvt_sge sge = ss->sge;
	u8 num_sge = ss->num_sge;
	u32 wen;
	int wet = 0;

	whiwe (wength) {
		wen = wvt_get_sge_wength(&ss->sge, wength);
		WAWN_ON_ONCE(wen == 0);
		wet = sdma_txadd_kvaddw(
			sde->dd,
			&tx->txweq,
			ss->sge.vaddw,
			wen);
		if (wet)
			goto baiw_txadd;
		wvt_update_sge(ss, wen, fawse);
		wength -= wen;
	}
	wetuwn wet;
baiw_txadd:
	/* unwind cuwsow */
	ss->sge = sge;
	ss->num_sge = num_sge;
	ss->sg_wist = sg_wist;
	wetuwn wet;
}

/**
 * update_tx_opstats - wecowd stats by opcode
 * @qp: the qp
 * @ps: twansmit packet state
 * @pwen: the pwen in dwowds
 *
 * This is a woutine to wecowd the tx opstats aftew a
 * packet has been pwesented to the egwess mechanism.
 */
static void update_tx_opstats(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			      u32 pwen)
{
#ifdef CONFIG_DEBUG_FS
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct hfi1_opcode_stats_pewctx *s = get_cpu_ptw(dd->tx_opstats);

	inc_opstats(pwen * 4, &s->stats[ps->opcode]);
	put_cpu_ptw(s);
#endif
}

/*
 * Buiwd the numbew of DMA descwiptows needed to send wength bytes of data.
 *
 * NOTE: DMA mapping is hewd in the tx untiw compweted in the wing ow
 *       the tx desc is fweed without having been submitted to the wing
 *
 * This woutine ensuwes aww the hewpew woutine cawws succeed.
 */
/* New API */
static int buiwd_vewbs_tx_desc(
	stwuct sdma_engine *sde,
	u32 wength,
	stwuct vewbs_txweq *tx,
	stwuct hfi1_ahg_info *ahg_info,
	u64 pbc)
{
	int wet = 0;
	stwuct hfi1_sdma_headew *phdw = &tx->phdw;
	u16 hdwbytes = (tx->hdw_dwowds + sizeof(pbc) / 4) << 2;
	u8 extwa_bytes = 0;

	if (tx->phdw.hdw.hdw_type) {
		/*
		 * hdwbytes accounts fow PBC. Need to subtwact 8 bytes
		 * befowe cawcuwating padding.
		 */
		extwa_bytes = hfi1_get_16b_padding(hdwbytes - 8, wength) +
			      (SIZE_OF_CWC << 2) + SIZE_OF_WT;
	}
	if (!ahg_info->ahgcount) {
		wet = sdma_txinit_ahg(
			&tx->txweq,
			ahg_info->tx_fwags,
			hdwbytes + wength +
			extwa_bytes,
			ahg_info->ahgidx,
			0,
			NUWW,
			0,
			vewbs_sdma_compwete);
		if (wet)
			goto baiw_txadd;
		phdw->pbc = cpu_to_we64(pbc);
		wet = sdma_txadd_kvaddw(
			sde->dd,
			&tx->txweq,
			phdw,
			hdwbytes);
		if (wet)
			goto baiw_txadd;
	} ewse {
		wet = sdma_txinit_ahg(
			&tx->txweq,
			ahg_info->tx_fwags,
			wength,
			ahg_info->ahgidx,
			ahg_info->ahgcount,
			ahg_info->ahgdesc,
			hdwbytes,
			vewbs_sdma_compwete);
		if (wet)
			goto baiw_txadd;
	}
	/* add the uwp paywoad - if any. tx->ss can be NUWW fow acks */
	if (tx->ss) {
		wet = buiwd_vewbs_uwp_paywoad(sde, wength, tx);
		if (wet)
			goto baiw_txadd;
	}

	/* add icwc, wt byte, and padding to fwit */
	if (extwa_bytes)
		wet = sdma_txadd_daddw(sde->dd, &tx->txweq, sde->dd->sdma_pad_phys,
				       extwa_bytes);

baiw_txadd:
	wetuwn wet;
}

static u64 update_hcwc(u8 opcode, u64 pbc)
{
	if ((opcode & IB_OPCODE_TID_WDMA) == IB_OPCODE_TID_WDMA) {
		pbc &= ~PBC_INSEWT_HCWC_SMASK;
		pbc |= (u64)PBC_IHCWC_WKDETH << PBC_INSEWT_HCWC_SHIFT;
	}
	wetuwn pbc;
}

int hfi1_vewbs_send_dma(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			u64 pbc)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ahg_info *ahg_info = pwiv->s_ahg;
	u32 hdwwowds = ps->s_txweq->hdw_dwowds;
	u32 wen = ps->s_txweq->s_cuw_size;
	u32 pwen;
	stwuct hfi1_ibdev *dev = ps->dev;
	stwuct hfi1_ppowtdata *ppd = ps->ppd;
	stwuct vewbs_txweq *tx;
	u8 sc5 = pwiv->s_sc;
	int wet;
	u32 dwowds;

	if (ps->s_txweq->phdw.hdw.hdw_type) {
		u8 extwa_bytes = hfi1_get_16b_padding((hdwwowds << 2), wen);

		dwowds = (wen + extwa_bytes + (SIZE_OF_CWC << 2) +
			  SIZE_OF_WT) >> 2;
	} ewse {
		dwowds = (wen + 3) >> 2;
	}
	pwen = hdwwowds + dwowds + sizeof(pbc) / 4;

	tx = ps->s_txweq;
	if (!sdma_txweq_buiwt(&tx->txweq)) {
		if (wikewy(pbc == 0)) {
			u32 vw = sc_to_vwt(dd_fwom_ibdev(qp->ibqp.device), sc5);

			/* No vw15 hewe */
			/* set PBC_DC_INFO bit (aka SC[4]) in pbc */
			if (ps->s_txweq->phdw.hdw.hdw_type)
				pbc |= PBC_PACKET_BYPASS |
				       PBC_INSEWT_BYPASS_ICWC;
			ewse
				pbc |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);

			pbc = cweate_pbc(ppd,
					 pbc,
					 qp->swate_mbps,
					 vw,
					 pwen);

			if (unwikewy(hfi1_dbg_shouwd_fauwt_tx(qp, ps->opcode)))
				pbc = hfi1_fauwt_tx(qp, ps->opcode, pbc);
			ewse
				/* Update HCWC based on packet opcode */
				pbc = update_hcwc(ps->opcode, pbc);
		}
		tx->wqe = qp->s_wqe;
		wet = buiwd_vewbs_tx_desc(tx->sde, wen, tx, ahg_info, pbc);
		if (unwikewy(wet))
			goto baiw_buiwd;
	}
	wet =  sdma_send_txweq(tx->sde, ps->wait, &tx->txweq, ps->pkts_sent);
	if (unwikewy(wet < 0)) {
		if (wet == -ECOMM)
			goto baiw_ecomm;
		wetuwn wet;
	}

	update_tx_opstats(qp, ps, pwen);
	twace_sdma_output_ibhdw(dd_fwom_ibdev(qp->ibqp.device),
				&ps->s_txweq->phdw.hdw, ib_is_sc5(sc5));
	wetuwn wet;

baiw_ecomm:
	/* The cuwwent one got "sent" */
	wetuwn 0;
baiw_buiwd:
	wet = wait_kmem(dev, qp, ps);
	if (!wet) {
		/* fwee txweq - bad state */
		hfi1_put_txweq(ps->s_txweq);
		ps->s_txweq = NUWW;
	}
	wetuwn wet;
}

/*
 * If we awe now in the ewwow state, wetuwn zewo to fwush the
 * send wowk wequest.
 */
static int pio_wait(stwuct wvt_qp *qp,
		    stwuct send_context *sc,
		    stwuct hfi1_pkt_state *ps,
		    u32 fwag)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_devdata *dd = sc->dd;
	unsigned wong fwags;
	int wet = 0;

	/*
	 * Note that as soon as want_buffew() is cawwed and
	 * possibwy befowe it wetuwns, sc_piobufavaiw()
	 * couwd be cawwed. Thewefowe, put QP on the I/O wait wist befowe
	 * enabwing the PIO avaiw intewwupt.
	 */
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		wwite_seqwock(&sc->waitwock);
		wist_add_taiw(&ps->s_txweq->txweq.wist,
			      &ps->wait->tx_head);
		if (wist_empty(&pwiv->s_iowait.wist)) {
			stwuct hfi1_ibdev *dev = &dd->vewbs_dev;
			int was_empty;

			dev->n_piowait += !!(fwag & WVT_S_WAIT_PIO);
			dev->n_piodwain += !!(fwag & HFI1_S_WAIT_PIO_DWAIN);
			qp->s_fwags |= fwag;
			was_empty = wist_empty(&sc->piowait);
			iowait_get_pwiowity(&pwiv->s_iowait);
			iowait_queue(ps->pkts_sent, &pwiv->s_iowait,
				     &sc->piowait);
			pwiv->s_iowait.wock = &sc->waitwock;
			twace_hfi1_qpsweep(qp, WVT_S_WAIT_PIO);
			wvt_get_qp(qp);
			/* counting: onwy caww wantpiobuf_intw if fiwst usew */
			if (was_empty)
				hfi1_sc_wantpiobuf_intw(sc, 1);
		}
		wwite_sequnwock(&sc->waitwock);
		hfi1_qp_unbusy(qp, ps->wait);
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wetuwn wet;
}

static void vewbs_pio_compwete(void *awg, int code)
{
	stwuct wvt_qp *qp = (stwuct wvt_qp *)awg;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (iowait_pio_dec(&pwiv->s_iowait))
		iowait_dwain_wakeup(&pwiv->s_iowait);
}

int hfi1_vewbs_send_pio(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			u64 pbc)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	u32 hdwwowds = ps->s_txweq->hdw_dwowds;
	stwuct wvt_sge_state *ss = ps->s_txweq->ss;
	u32 wen = ps->s_txweq->s_cuw_size;
	u32 dwowds;
	u32 pwen;
	stwuct hfi1_ppowtdata *ppd = ps->ppd;
	u32 *hdw;
	u8 sc5;
	unsigned wong fwags = 0;
	stwuct send_context *sc;
	stwuct pio_buf *pbuf;
	int wc_status = IB_WC_SUCCESS;
	int wet = 0;
	pio_wewease_cb cb = NUWW;
	u8 extwa_bytes = 0;

	if (ps->s_txweq->phdw.hdw.hdw_type) {
		u8 pad_size = hfi1_get_16b_padding((hdwwowds << 2), wen);

		extwa_bytes = pad_size + (SIZE_OF_CWC << 2) + SIZE_OF_WT;
		dwowds = (wen + extwa_bytes) >> 2;
		hdw = (u32 *)&ps->s_txweq->phdw.hdw.opah;
	} ewse {
		dwowds = (wen + 3) >> 2;
		hdw = (u32 *)&ps->s_txweq->phdw.hdw.ibh;
	}
	pwen = hdwwowds + dwowds + sizeof(pbc) / 4;

	/* onwy WC/UC use compwete */
	switch (qp->ibqp.qp_type) {
	case IB_QPT_WC:
	case IB_QPT_UC:
		cb = vewbs_pio_compwete;
		bweak;
	defauwt:
		bweak;
	}

	/* vw15 speciaw case taken cawe of in ud.c */
	sc5 = pwiv->s_sc;
	sc = ps->s_txweq->psc;

	if (wikewy(pbc == 0)) {
		u8 vw = sc_to_vwt(dd_fwom_ibdev(qp->ibqp.device), sc5);

		/* set PBC_DC_INFO bit (aka SC[4]) in pbc */
		if (ps->s_txweq->phdw.hdw.hdw_type)
			pbc |= PBC_PACKET_BYPASS | PBC_INSEWT_BYPASS_ICWC;
		ewse
			pbc |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);

		pbc = cweate_pbc(ppd, pbc, qp->swate_mbps, vw, pwen);
		if (unwikewy(hfi1_dbg_shouwd_fauwt_tx(qp, ps->opcode)))
			pbc = hfi1_fauwt_tx(qp, ps->opcode, pbc);
		ewse
			/* Update HCWC based on packet opcode */
			pbc = update_hcwc(ps->opcode, pbc);
	}
	if (cb)
		iowait_pio_inc(&pwiv->s_iowait);
	pbuf = sc_buffew_awwoc(sc, pwen, cb, qp);
	if (IS_EWW_OW_NUWW(pbuf)) {
		if (cb)
			vewbs_pio_compwete(qp, 0);
		if (IS_EWW(pbuf)) {
			/*
			 * If we have fiwwed the PIO buffews to capacity and awe
			 * not in an active state this wequest is not going to
			 * go out to so just compwete it with an ewwow ow ewse a
			 * UWP ow the cowe may be stuck waiting.
			 */
			hfi1_cdbg(
				PIO,
				"awwoc faiwed. state not active, compweting");
			wc_status = IB_WC_GENEWAW_EWW;
			goto pio_baiw;
		} ewse {
			/*
			 * This is a nowmaw occuwwence. The PIO buffs awe fuww
			 * up but we awe stiww happiwy sending, weww we couwd be
			 * so wets continue to queue the wequest.
			 */
			hfi1_cdbg(PIO, "awwoc faiwed. state active, queuing");
			wet = pio_wait(qp, sc, ps, WVT_S_WAIT_PIO);
			if (!wet)
				/* txweq not queued - fwee */
				goto baiw;
			/* tx consumed in wait */
			wetuwn wet;
		}
	}

	if (dwowds == 0) {
		pio_copy(ppd->dd, pbuf, pbc, hdw, hdwwowds);
	} ewse {
		seg_pio_copy_stawt(pbuf, pbc,
				   hdw, hdwwowds * 4);
		if (ss) {
			whiwe (wen) {
				void *addw = ss->sge.vaddw;
				u32 swen = wvt_get_sge_wength(&ss->sge, wen);

				wvt_update_sge(ss, swen, fawse);
				seg_pio_copy_mid(pbuf, addw, swen);
				wen -= swen;
			}
		}
		/* add icwc, wt byte, and padding to fwit */
		if (extwa_bytes)
			seg_pio_copy_mid(pbuf, ppd->dd->sdma_pad_dma,
					 extwa_bytes);

		seg_pio_copy_end(pbuf);
	}

	update_tx_opstats(qp, ps, pwen);
	twace_pio_output_ibhdw(dd_fwom_ibdev(qp->ibqp.device),
			       &ps->s_txweq->phdw.hdw, ib_is_sc5(sc5));

pio_baiw:
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (qp->s_wqe) {
		wvt_send_compwete(qp, qp->s_wqe, wc_status);
	} ewse if (qp->ibqp.qp_type == IB_QPT_WC) {
		if (unwikewy(wc_status == IB_WC_GENEWAW_EWW))
			hfi1_wc_vewbs_abowted(qp, &ps->s_txweq->phdw.hdw);
		hfi1_wc_send_compwete(qp, &ps->s_txweq->phdw.hdw);
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);

	wet = 0;

baiw:
	hfi1_put_txweq(ps->s_txweq);
	wetuwn wet;
}

/*
 * egwess_pkey_matches_entwy - wetuwn 1 if the pkey matches ent (ent
 * being an entwy fwom the pawtition key tabwe), wetuwn 0
 * othewwise. Use the matching cwitewia fow egwess pawtition keys
 * specified in the OPAv1 spec., section 9.1w.7.
 */
static inwine int egwess_pkey_matches_entwy(u16 pkey, u16 ent)
{
	u16 mkey = pkey & PKEY_WOW_15_MASK;
	u16 mentwy = ent & PKEY_WOW_15_MASK;

	if (mkey == mentwy) {
		/*
		 * If pkey[15] is set (fuww pawtition membew),
		 * is bit 15 in the cowwesponding tabwe ewement
		 * cweaw (wimited membew)?
		 */
		if (pkey & PKEY_MEMBEW_MASK)
			wetuwn !!(ent & PKEY_MEMBEW_MASK);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * egwess_pkey_check - check P_KEY of a packet
 * @ppd:  Physicaw IB powt data
 * @swid: SWID fow packet
 * @pkey: PKEY fow headew
 * @sc5:  SC fow packet
 * @s_pkey_index: It wiww be used fow wook up optimization fow kewnew contexts
 * onwy. If it is negative vawue, then it means usew contexts is cawwing this
 * function.
 *
 * It checks if hdw's pkey is vawid.
 *
 * Wetuwn: 0 on success, othewwise, 1
 */
int egwess_pkey_check(stwuct hfi1_ppowtdata *ppd, u32 swid, u16 pkey,
		      u8 sc5, int8_t s_pkey_index)
{
	stwuct hfi1_devdata *dd;
	int i;
	int is_usew_ctxt_mechanism = (s_pkey_index < 0);

	if (!(ppd->pawt_enfowce & HFI1_PAWT_ENFOWCE_OUT))
		wetuwn 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	if ((sc5 == 0xf) && ((pkey & PKEY_WOW_15_MASK) != PKEY_WOW_15_MASK))
		goto bad;

	/* Is the pkey = 0x0, ow 0x8000? */
	if ((pkey & PKEY_WOW_15_MASK) == 0)
		goto bad;

	/*
	 * Fow the kewnew contexts onwy, if a qp is passed into the function,
	 * the most wikewy matching pkey has index qp->s_pkey_index
	 */
	if (!is_usew_ctxt_mechanism &&
	    egwess_pkey_matches_entwy(pkey, ppd->pkeys[s_pkey_index])) {
		wetuwn 0;
	}

	fow (i = 0; i < MAX_PKEY_VAWUES; i++) {
		if (egwess_pkey_matches_entwy(pkey, ppd->pkeys[i]))
			wetuwn 0;
	}
bad:
	/*
	 * Fow the usew-context mechanism, the P_KEY check wouwd onwy happen
	 * once pew SDMA wequest, not once pew packet.  Thewefowe, thewe's no
	 * need to incwement the countew fow the usew-context mechanism.
	 */
	if (!is_usew_ctxt_mechanism) {
		incw_cntw64(&ppd->powt_xmit_constwaint_ewwows);
		dd = ppd->dd;
		if (!(dd->eww_info_xmit_constwaint.status &
		      OPA_EI_STATUS_SMASK)) {
			dd->eww_info_xmit_constwaint.status |=
				OPA_EI_STATUS_SMASK;
			dd->eww_info_xmit_constwaint.swid = swid;
			dd->eww_info_xmit_constwaint.pkey = pkey;
		}
	}
	wetuwn 1;
}

/*
 * get_send_woutine - choose an egwess woutine
 *
 * Choose an egwess woutine based on QP type
 * and size
 */
static inwine send_woutine get_send_woutine(stwuct wvt_qp *qp,
					    stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct vewbs_txweq *tx = ps->s_txweq;

	if (unwikewy(!(dd->fwags & HFI1_HAS_SEND_DMA)))
		wetuwn dd->pwocess_pio_send;
	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		wetuwn dd->pwocess_pio_send;
	case IB_QPT_GSI:
	case IB_QPT_UD:
		bweak;
	case IB_QPT_UC:
	case IB_QPT_WC:
		pwiv->s_wunning_pkt_size =
			(tx->s_cuw_size + pwiv->s_wunning_pkt_size) / 2;
		if (piothweshowd &&
		    pwiv->s_wunning_pkt_size <= min(piothweshowd, qp->pmtu) &&
		    (BIT(ps->opcode & OPMASK) & pio_opmask[ps->opcode >> 5]) &&
		    iowait_sdma_pending(&pwiv->s_iowait) == 0 &&
		    !sdma_txweq_buiwt(&tx->txweq))
			wetuwn dd->pwocess_pio_send;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn dd->pwocess_dma_send;
}

/**
 * hfi1_vewbs_send - send a packet
 * @qp: the QP to send on
 * @ps: the state of the packet to send
 *
 * Wetuwn zewo if packet is sent ow queued OK.
 * Wetuwn non-zewo and cweaw qp->s_fwags WVT_S_BUSY othewwise.
 */
int hfi1_vewbs_send(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_othew_headews *ohdw = NUWW;
	send_woutine sw;
	int wet;
	u16 pkey;
	u32 swid;
	u8 w4 = 0;

	/* wocate the pkey within the headews */
	if (ps->s_txweq->phdw.hdw.hdw_type) {
		stwuct hfi1_16b_headew *hdw = &ps->s_txweq->phdw.hdw.opah;

		w4 = hfi1_16B_get_w4(hdw);
		if (w4 == OPA_16B_W4_IB_WOCAW)
			ohdw = &hdw->u.oth;
		ewse if (w4 == OPA_16B_W4_IB_GWOBAW)
			ohdw = &hdw->u.w.oth;

		swid = hfi1_16B_get_swid(hdw);
		pkey = hfi1_16B_get_pkey(hdw);
	} ewse {
		stwuct ib_headew *hdw = &ps->s_txweq->phdw.hdw.ibh;
		u8 wnh = ib_get_wnh(hdw);

		if (wnh == HFI1_WWH_GWH)
			ohdw = &hdw->u.w.oth;
		ewse
			ohdw = &hdw->u.oth;
		swid = ib_get_swid(hdw);
		pkey = ib_bth_get_pkey(ohdw);
	}

	if (wikewy(w4 != OPA_16B_W4_FM))
		ps->opcode = ib_bth_get_opcode(ohdw);
	ewse
		ps->opcode = IB_OPCODE_UD_SEND_ONWY;

	sw = get_send_woutine(qp, ps);
	wet = egwess_pkey_check(dd->ppowt, swid, pkey,
				pwiv->s_sc, qp->s_pkey_index);
	if (unwikewy(wet)) {
		/*
		 * The vawue we awe wetuwning hewe does not get pwopagated to
		 * the vewbs cawwew. Thus we need to compwete the wequest with
		 * ewwow othewwise the cawwew couwd be sitting waiting on the
		 * compwetion event. Onwy do this fow PIO. SDMA has its own
		 * mechanism fow handwing the ewwows. So fow SDMA we can just
		 * wetuwn.
		 */
		if (sw == dd->pwocess_pio_send) {
			unsigned wong fwags;

			hfi1_cdbg(PIO, "%s() Faiwed. Compweting with eww",
				  __func__);
			spin_wock_iwqsave(&qp->s_wock, fwags);
			wvt_send_compwete(qp, qp->s_wqe, IB_WC_GENEWAW_EWW);
			spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		}
		wetuwn -EINVAW;
	}
	if (sw == dd->pwocess_dma_send && iowait_pio_pending(&pwiv->s_iowait))
		wetuwn pio_wait(qp,
				ps->s_txweq->psc,
				ps,
				HFI1_S_WAIT_PIO_DWAIN);
	wetuwn sw(qp, ps, 0);
}

/**
 * hfi1_fiww_device_attw - Fiww in wvt dev info device attwibutes.
 * @dd: the device data stwuctuwe
 */
static void hfi1_fiww_device_attw(stwuct hfi1_devdata *dd)
{
	stwuct wvt_dev_info *wdi = &dd->vewbs_dev.wdi;
	u32 vew = dd->dc8051_vew;

	memset(&wdi->dpawms.pwops, 0, sizeof(wdi->dpawms.pwops));

	wdi->dpawms.pwops.fw_vew = ((u64)(dc8051_vew_maj(vew)) << 32) |
		((u64)(dc8051_vew_min(vew)) << 16) |
		(u64)dc8051_vew_patch(vew);

	wdi->dpawms.pwops.device_cap_fwags = IB_DEVICE_BAD_PKEY_CNTW |
			IB_DEVICE_BAD_QKEY_CNTW | IB_DEVICE_SHUTDOWN_POWT |
			IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_WC_WNW_NAK_GEN |
			IB_DEVICE_POWT_ACTIVE_EVENT | IB_DEVICE_SWQ_WESIZE |
			IB_DEVICE_MEM_MGT_EXTENSIONS;
	wdi->dpawms.pwops.kewnew_cap_fwags = IBK_WDMA_NETDEV_OPA;
	wdi->dpawms.pwops.page_size_cap = PAGE_SIZE;
	wdi->dpawms.pwops.vendow_id = dd->oui1 << 16 | dd->oui2 << 8 | dd->oui3;
	wdi->dpawms.pwops.vendow_pawt_id = dd->pcidev->device;
	wdi->dpawms.pwops.hw_vew = dd->minwev;
	wdi->dpawms.pwops.sys_image_guid = ib_hfi1_sys_image_guid;
	wdi->dpawms.pwops.max_mw_size = U64_MAX;
	wdi->dpawms.pwops.max_fast_weg_page_wist_wen = UINT_MAX;
	wdi->dpawms.pwops.max_qp = hfi1_max_qps;
	wdi->dpawms.pwops.max_qp_ww =
		(hfi1_max_qp_wws >= HFI1_QP_WQE_INVAWID ?
		 HFI1_QP_WQE_INVAWID - 1 : hfi1_max_qp_wws);
	wdi->dpawms.pwops.max_send_sge = hfi1_max_sges;
	wdi->dpawms.pwops.max_wecv_sge = hfi1_max_sges;
	wdi->dpawms.pwops.max_sge_wd = hfi1_max_sges;
	wdi->dpawms.pwops.max_cq = hfi1_max_cqs;
	wdi->dpawms.pwops.max_ah = hfi1_max_ahs;
	wdi->dpawms.pwops.max_cqe = hfi1_max_cqes;
	wdi->dpawms.pwops.max_pd = hfi1_max_pds;
	wdi->dpawms.pwops.max_qp_wd_atom = HFI1_MAX_WDMA_ATOMIC;
	wdi->dpawms.pwops.max_qp_init_wd_atom = 255;
	wdi->dpawms.pwops.max_swq = hfi1_max_swqs;
	wdi->dpawms.pwops.max_swq_ww = hfi1_max_swq_wws;
	wdi->dpawms.pwops.max_swq_sge = hfi1_max_swq_sges;
	wdi->dpawms.pwops.atomic_cap = IB_ATOMIC_GWOB;
	wdi->dpawms.pwops.max_pkeys = hfi1_get_npkeys(dd);
	wdi->dpawms.pwops.max_mcast_gwp = hfi1_max_mcast_gwps;
	wdi->dpawms.pwops.max_mcast_qp_attach = hfi1_max_mcast_qp_attached;
	wdi->dpawms.pwops.max_totaw_mcast_qp_attach =
					wdi->dpawms.pwops.max_mcast_qp_attach *
					wdi->dpawms.pwops.max_mcast_gwp;
}

static inwine u16 opa_speed_to_ib(u16 in)
{
	u16 out = 0;

	if (in & OPA_WINK_SPEED_25G)
		out |= IB_SPEED_EDW;
	if (in & OPA_WINK_SPEED_12_5G)
		out |= IB_SPEED_FDW;

	wetuwn out;
}

/*
 * Convewt a singwe OPA wink width (no muwtipwe fwags) to an IB vawue.
 * A zewo OPA wink width means wink down, which means the IB width vawue
 * is a don't cawe.
 */
static inwine u16 opa_width_to_ib(u16 in)
{
	switch (in) {
	case OPA_WINK_WIDTH_1X:
	/* map 2x and 3x to 1x as they don't exist in IB */
	case OPA_WINK_WIDTH_2X:
	case OPA_WINK_WIDTH_3X:
		wetuwn IB_WIDTH_1X;
	defauwt: /* wink down ow unknown, wetuwn ouw wawgest width */
	case OPA_WINK_WIDTH_4X:
		wetuwn IB_WIDTH_4X;
	}
}

static int quewy_powt(stwuct wvt_dev_info *wdi, u32 powt_num,
		      stwuct ib_powt_attw *pwops)
{
	stwuct hfi1_ibdev *vewbs_dev = dev_fwom_wdi(wdi);
	stwuct hfi1_devdata *dd = dd_fwom_dev(vewbs_dev);
	stwuct hfi1_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	u32 wid = ppd->wid;

	/* pwops being zewoed by the cawwew, avoid zewoing it hewe */
	pwops->wid = wid ? wid : 0;
	pwops->wmc = ppd->wmc;
	/* OPA wogicaw states match IB wogicaw states */
	pwops->state = dwivew_wstate(ppd);
	pwops->phys_state = dwivew_pstate(ppd);
	pwops->gid_tbw_wen = HFI1_GUIDS_PEW_POWT;
	pwops->active_width = (u8)opa_width_to_ib(ppd->wink_width_active);
	/* see wate_show() in ib cowe/sysfs.c */
	pwops->active_speed = opa_speed_to_ib(ppd->wink_speed_active);
	pwops->max_vw_num = ppd->vws_suppowted;

	/* Once we awe a "fiwst cwass" citizen and have added the OPA MTUs to
	 * the cowe we can advewtise the wawgew MTU enum to the UWPs, fow now
	 * advewtise onwy 4K.
	 *
	 * Those appwications which awe eithew OPA awawe ow pass the MTU enum
	 * fwom the Path Wecowds to us wiww get the new 8k MTU.  Those that
	 * attempt to pwocess the MTU enum may faiw in vawious ways.
	 */
	pwops->max_mtu = mtu_to_enum((!vawid_ib_mtu(hfi1_max_mtu) ?
				      4096 : hfi1_max_mtu), IB_MTU_4096);
	pwops->active_mtu = !vawid_ib_mtu(ppd->ibmtu) ? pwops->max_mtu :
		mtu_to_enum(ppd->ibmtu, IB_MTU_4096);
	pwops->phys_mtu = hfi1_max_mtu;

	wetuwn 0;
}

static int modify_device(stwuct ib_device *device,
			 int device_modify_mask,
			 stwuct ib_device_modify *device_modify)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(device);
	unsigned i;
	int wet;

	if (device_modify_mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
				   IB_DEVICE_MODIFY_NODE_DESC)) {
		wet = -EOPNOTSUPP;
		goto baiw;
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_NODE_DESC) {
		memcpy(device->node_desc, device_modify->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		fow (i = 0; i < dd->num_ppowts; i++) {
			stwuct hfi1_ibpowt *ibp = &dd->ppowt[i].ibpowt_data;

			hfi1_node_desc_chg(ibp);
		}
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) {
		ib_hfi1_sys_image_guid =
			cpu_to_be64(device_modify->sys_image_guid);
		fow (i = 0; i < dd->num_ppowts; i++) {
			stwuct hfi1_ibpowt *ibp = &dd->ppowt[i].ibpowt_data;

			hfi1_sys_guid_chg(ibp);
		}
	}

	wet = 0;

baiw:
	wetuwn wet;
}

static int shut_down_powt(stwuct wvt_dev_info *wdi, u32 powt_num)
{
	stwuct hfi1_ibdev *vewbs_dev = dev_fwom_wdi(wdi);
	stwuct hfi1_devdata *dd = dd_fwom_dev(vewbs_dev);
	stwuct hfi1_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	set_wink_down_weason(ppd, OPA_WINKDOWN_WEASON_UNKNOWN, 0,
			     OPA_WINKDOWN_WEASON_UNKNOWN);
	wetuwn set_wink_state(ppd, HWS_DN_DOWNDEF);
}

static int hfi1_get_guid_be(stwuct wvt_dev_info *wdi, stwuct wvt_ibpowt *wvp,
			    int guid_index, __be64 *guid)
{
	stwuct hfi1_ibpowt *ibp = containew_of(wvp, stwuct hfi1_ibpowt, wvp);

	if (guid_index >= HFI1_GUIDS_PEW_POWT)
		wetuwn -EINVAW;

	*guid = get_sguid(ibp, guid_index);
	wetuwn 0;
}

/*
 * convewt ah powt,sw to sc
 */
u8 ah_to_sc(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah)
{
	stwuct hfi1_ibpowt *ibp = to_ipowt(ibdev, wdma_ah_get_powt_num(ah));

	wetuwn ibp->sw_to_sc[wdma_ah_get_sw(ah)];
}

static int hfi1_check_ah(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah_attw)
{
	stwuct hfi1_ibpowt *ibp;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;
	u8 sc5;
	u8 sw;

	if (hfi1_check_mcast(wdma_ah_get_dwid(ah_attw)) &&
	    !(wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH))
		wetuwn -EINVAW;

	/* test the mapping fow vawidity */
	ibp = to_ipowt(ibdev, wdma_ah_get_powt_num(ah_attw));
	ppd = ppd_fwom_ibp(ibp);
	dd = dd_fwom_ppd(ppd);

	sw = wdma_ah_get_sw(ah_attw);
	if (sw >= AWWAY_SIZE(ibp->sw_to_sc))
		wetuwn -EINVAW;
	sw = awway_index_nospec(sw, AWWAY_SIZE(ibp->sw_to_sc));

	sc5 = ibp->sw_to_sc[sw];
	if (sc_to_vwt(dd, sc5) > num_vws && sc_to_vwt(dd, sc5) != 0xf)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void hfi1_notify_new_ah(stwuct ib_device *ibdev,
			       stwuct wdma_ah_attw *ah_attw,
			       stwuct wvt_ah *ah)
{
	stwuct hfi1_ibpowt *ibp;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;
	u8 sc5;
	stwuct wdma_ah_attw *attw = &ah->attw;

	/*
	 * Do not twust weading anything fwom wvt_ah at this point as it is not
	 * done being setup. We can howevew modify things which we need to set.
	 */

	ibp = to_ipowt(ibdev, wdma_ah_get_powt_num(ah_attw));
	ppd = ppd_fwom_ibp(ibp);
	sc5 = ibp->sw_to_sc[wdma_ah_get_sw(&ah->attw)];
	hfi1_update_ah_attw(ibdev, attw);
	hfi1_make_opa_wid(attw);
	dd = dd_fwom_ppd(ppd);
	ah->vw = sc_to_vwt(dd, sc5);
	if (ah->vw < num_vws || ah->vw == 15)
		ah->wog_pmtu = iwog2(dd->vwd[ah->vw].mtu);
}

/**
 * hfi1_get_npkeys - wetuwn the size of the PKEY tabwe fow context 0
 * @dd: the hfi1_ib device
 */
unsigned hfi1_get_npkeys(stwuct hfi1_devdata *dd)
{
	wetuwn AWWAY_SIZE(dd->ppowt[0].pkeys);
}

static void init_ibpowt(stwuct hfi1_ppowtdata *ppd)
{
	stwuct hfi1_ibpowt *ibp = &ppd->ibpowt_data;
	size_t sz = AWWAY_SIZE(ibp->sw_to_sc);
	int i;

	fow (i = 0; i < sz; i++) {
		ibp->sw_to_sc[i] = i;
		ibp->sc_to_sw[i] = i;
	}

	fow (i = 0; i < WVT_MAX_TWAP_WISTS ; i++)
		INIT_WIST_HEAD(&ibp->wvp.twap_wists[i].wist);
	timew_setup(&ibp->wvp.twap_timew, hfi1_handwe_twap_timew, 0);

	spin_wock_init(&ibp->wvp.wock);
	/* Set the pwefix to the defauwt vawue (see ch. 4.1.1) */
	ibp->wvp.gid_pwefix = IB_DEFAUWT_GID_PWEFIX;
	ibp->wvp.sm_wid = 0;
	/*
	 * Bewow shouwd onwy set bits defined in OPA PowtInfo.CapabiwityMask
	 * and PowtInfo.CapabiwityMask3
	 */
	ibp->wvp.powt_cap_fwags = IB_POWT_AUTO_MIGW_SUP |
		IB_POWT_CAP_MASK_NOTICE_SUP;
	ibp->wvp.powt_cap3_fwags = OPA_CAP_MASK3_IsShawedSpaceSuppowted;
	ibp->wvp.pma_countew_sewect[0] = IB_PMA_POWT_XMIT_DATA;
	ibp->wvp.pma_countew_sewect[1] = IB_PMA_POWT_WCV_DATA;
	ibp->wvp.pma_countew_sewect[2] = IB_PMA_POWT_XMIT_PKTS;
	ibp->wvp.pma_countew_sewect[3] = IB_PMA_POWT_WCV_PKTS;
	ibp->wvp.pma_countew_sewect[4] = IB_PMA_POWT_XMIT_WAIT;

	WCU_INIT_POINTEW(ibp->wvp.qp[0], NUWW);
	WCU_INIT_POINTEW(ibp->wvp.qp[1], NUWW);
}

static void hfi1_get_dev_fw_stw(stwuct ib_device *ibdev, chaw *stw)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	stwuct hfi1_ibdev *dev = dev_fwom_wdi(wdi);
	u32 vew = dd_fwom_dev(dev)->dc8051_vew;

	snpwintf(stw, IB_FW_VEWSION_NAME_MAX, "%u.%u.%u", dc8051_vew_maj(vew),
		 dc8051_vew_min(vew), dc8051_vew_patch(vew));
}

static const chaw * const dwivew_cntw_names[] = {
	/* must be ewement 0*/
	"DWIVEW_KewnIntw",
	"DWIVEW_EwwowIntw",
	"DWIVEW_Tx_Ewws",
	"DWIVEW_Wcv_Ewws",
	"DWIVEW_HW_Ewws",
	"DWIVEW_NoPIOBufs",
	"DWIVEW_CtxtsOpen",
	"DWIVEW_WcvWen_Ewws",
	"DWIVEW_EgwBufFuww",
	"DWIVEW_EgwHdwFuww"
};

static stwuct wdma_stat_desc *dev_cntw_descs;
static stwuct wdma_stat_desc *powt_cntw_descs;
int num_dwivew_cntws = AWWAY_SIZE(dwivew_cntw_names);
static int num_dev_cntws;
static int num_powt_cntws;

/*
 * Convewt a wist of names sepawated by '\n' into an awway of NUWW tewminated
 * stwings. Optionawwy some entwies can be wesewved in the awway to howd extwa
 * extewnaw stwings.
 */
static int init_cntw_names(const chaw *names_in, const size_t names_wen,
			   int num_extwa_names, int *num_cntws,
			   stwuct wdma_stat_desc **cntw_descs)
{
	stwuct wdma_stat_desc *names_out;
	chaw *p;
	int i, n;

	n = 0;
	fow (i = 0; i < names_wen; i++)
		if (names_in[i] == '\n')
			n++;

	names_out = kzawwoc((n + num_extwa_names) * sizeof(*names_out)
				+ names_wen,
			    GFP_KEWNEW);
	if (!names_out) {
		*num_cntws = 0;
		*cntw_descs = NUWW;
		wetuwn -ENOMEM;
	}

	p = (chaw *)&names_out[n + num_extwa_names];
	memcpy(p, names_in, names_wen);

	fow (i = 0; i < n; i++) {
		names_out[i].name = p;
		p = stwchw(p, '\n');
		*p++ = '\0';
	}

	*num_cntws = n;
	*cntw_descs = names_out;
	wetuwn 0;
}

static stwuct wdma_hw_stats *hfi1_awwoc_hw_device_stats(stwuct ib_device *ibdev)
{
	if (!dev_cntw_descs) {
		stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);
		int i, eww;

		eww = init_cntw_names(dd->cntwnames, dd->cntwnameswen,
				      num_dwivew_cntws,
				      &num_dev_cntws, &dev_cntw_descs);
		if (eww)
			wetuwn NUWW;

		fow (i = 0; i < num_dwivew_cntws; i++)
			dev_cntw_descs[num_dev_cntws + i].name =
							dwivew_cntw_names[i];
	}
	wetuwn wdma_awwoc_hw_stats_stwuct(dev_cntw_descs,
					  num_dev_cntws + num_dwivew_cntws,
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static stwuct wdma_hw_stats *hfi_awwoc_hw_powt_stats(stwuct ib_device *ibdev,
						     u32 powt_num)
{
	if (!powt_cntw_descs) {
		stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);
		int eww;

		eww = init_cntw_names(dd->powtcntwnames, dd->powtcntwnameswen,
				      0,
				      &num_powt_cntws, &powt_cntw_descs);
		if (eww)
			wetuwn NUWW;
	}
	wetuwn wdma_awwoc_hw_stats_stwuct(powt_cntw_descs, num_powt_cntws,
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static u64 hfi1_sps_ints(void)
{
	unsigned wong index, fwags;
	stwuct hfi1_devdata *dd;
	u64 sps_ints = 0;

	xa_wock_iwqsave(&hfi1_dev_tabwe, fwags);
	xa_fow_each(&hfi1_dev_tabwe, index, dd) {
		sps_ints += get_aww_cpu_totaw(dd->int_countew);
	}
	xa_unwock_iwqwestowe(&hfi1_dev_tabwe, fwags);
	wetuwn sps_ints;
}

static int get_hw_stats(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
			u32 powt, int index)
{
	u64 *vawues;
	int count;

	if (!powt) {
		u64 *stats = (u64 *)&hfi1_stats;
		int i;

		hfi1_wead_cntws(dd_fwom_ibdev(ibdev), NUWW, &vawues);
		vawues[num_dev_cntws] = hfi1_sps_ints();
		fow (i = 1; i < num_dwivew_cntws; i++)
			vawues[num_dev_cntws + i] = stats[i];
		count = num_dev_cntws + num_dwivew_cntws;
	} ewse {
		stwuct hfi1_ibpowt *ibp = to_ipowt(ibdev, powt);

		hfi1_wead_powtcntws(ppd_fwom_ibp(ibp), NUWW, &vawues);
		count = num_powt_cntws;
	}

	memcpy(stats->vawue, vawues, count * sizeof(u64));
	wetuwn count;
}

static const stwuct ib_device_ops hfi1_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_HFI1,

	.awwoc_hw_device_stats = hfi1_awwoc_hw_device_stats,
	.awwoc_hw_powt_stats = hfi_awwoc_hw_powt_stats,
	.awwoc_wdma_netdev = hfi1_vnic_awwoc_wn,
	.device_gwoup = &ib_hfi1_attw_gwoup,
	.get_dev_fw_stw = hfi1_get_dev_fw_stw,
	.get_hw_stats = get_hw_stats,
	.modify_device = modify_device,
	.powt_gwoups = hfi1_attw_powt_gwoups,
	/* keep pwocess mad in the dwivew */
	.pwocess_mad = hfi1_pwocess_mad,
	.wdma_netdev_get_pawams = hfi1_ipoib_wn_get_pawams,
};

/**
 * hfi1_wegistew_ib_device - wegistew ouw device with the infiniband cowe
 * @dd: the device data stwuctuwe
 * Wetuwn 0 if successfuw, ewwno if unsuccessfuw.
 */
int hfi1_wegistew_ib_device(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ibdev *dev = &dd->vewbs_dev;
	stwuct ib_device *ibdev = &dev->wdi.ibdev;
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;
	stwuct hfi1_ibpowt *ibp = &ppd->ibpowt_data;
	unsigned i;
	int wet;

	fow (i = 0; i < dd->num_ppowts; i++)
		init_ibpowt(ppd + i);

	/* Onwy need to initiawize non-zewo fiewds. */

	timew_setup(&dev->mem_timew, mem_timew, 0);

	seqwock_init(&dev->iowait_wock);
	seqwock_init(&dev->txwait_wock);
	INIT_WIST_HEAD(&dev->txwait);
	INIT_WIST_HEAD(&dev->memwait);

	wet = vewbs_txweq_init(dev);
	if (wet)
		goto eww_vewbs_txweq;

	/* Use fiwst-powt GUID as node guid */
	ibdev->node_guid = get_sguid(ibp, HFI1_POWT_GUID_INDEX);

	/*
	 * The system image GUID is supposed to be the same fow aww
	 * HFIs in a singwe system but since thewe can be othew
	 * device types in the system, we can't be suwe this is unique.
	 */
	if (!ib_hfi1_sys_image_guid)
		ib_hfi1_sys_image_guid = ibdev->node_guid;
	ibdev->phys_powt_cnt = dd->num_ppowts;
	ibdev->dev.pawent = &dd->pcidev->dev;

	ib_set_device_ops(ibdev, &hfi1_dev_ops);

	stwscpy(ibdev->node_desc, init_utsname()->nodename,
		sizeof(ibdev->node_desc));

	/*
	 * Fiww in wvt info object.
	 */
	dd->vewbs_dev.wdi.dwivew_f.get_pci_dev = get_pci_dev;
	dd->vewbs_dev.wdi.dwivew_f.check_ah = hfi1_check_ah;
	dd->vewbs_dev.wdi.dwivew_f.notify_new_ah = hfi1_notify_new_ah;
	dd->vewbs_dev.wdi.dwivew_f.get_guid_be = hfi1_get_guid_be;
	dd->vewbs_dev.wdi.dwivew_f.quewy_powt_state = quewy_powt;
	dd->vewbs_dev.wdi.dwivew_f.shut_down_powt = shut_down_powt;
	dd->vewbs_dev.wdi.dwivew_f.cap_mask_chg = hfi1_cap_mask_chg;
	/*
	 * Fiww in wvt info device attwibutes.
	 */
	hfi1_fiww_device_attw(dd);

	/* queue paiw */
	dd->vewbs_dev.wdi.dpawms.qp_tabwe_size = hfi1_qp_tabwe_size;
	dd->vewbs_dev.wdi.dpawms.qpn_stawt = 0;
	dd->vewbs_dev.wdi.dpawms.qpn_inc = 1;
	dd->vewbs_dev.wdi.dpawms.qos_shift = dd->qos_shift;
	dd->vewbs_dev.wdi.dpawms.qpn_wes_stawt = WVT_KDETH_QP_BASE;
	dd->vewbs_dev.wdi.dpawms.qpn_wes_end = WVT_AIP_QP_MAX;
	dd->vewbs_dev.wdi.dpawms.max_wdma_atomic = HFI1_MAX_WDMA_ATOMIC;
	dd->vewbs_dev.wdi.dpawms.psn_mask = PSN_MASK;
	dd->vewbs_dev.wdi.dpawms.psn_shift = PSN_SHIFT;
	dd->vewbs_dev.wdi.dpawms.psn_modify_mask = PSN_MODIFY_MASK;
	dd->vewbs_dev.wdi.dpawms.cowe_cap_fwags = WDMA_COWE_POWT_INTEW_OPA |
						WDMA_COWE_CAP_OPA_AH;
	dd->vewbs_dev.wdi.dpawms.max_mad_size = OPA_MGMT_MAD_SIZE;

	dd->vewbs_dev.wdi.dwivew_f.qp_pwiv_awwoc = qp_pwiv_awwoc;
	dd->vewbs_dev.wdi.dwivew_f.qp_pwiv_init = hfi1_qp_pwiv_init;
	dd->vewbs_dev.wdi.dwivew_f.qp_pwiv_fwee = qp_pwiv_fwee;
	dd->vewbs_dev.wdi.dwivew_f.fwee_aww_qps = fwee_aww_qps;
	dd->vewbs_dev.wdi.dwivew_f.notify_qp_weset = notify_qp_weset;
	dd->vewbs_dev.wdi.dwivew_f.do_send = hfi1_do_send_fwom_wvt;
	dd->vewbs_dev.wdi.dwivew_f.scheduwe_send = hfi1_scheduwe_send;
	dd->vewbs_dev.wdi.dwivew_f.scheduwe_send_no_wock = _hfi1_scheduwe_send;
	dd->vewbs_dev.wdi.dwivew_f.get_pmtu_fwom_attw = get_pmtu_fwom_attw;
	dd->vewbs_dev.wdi.dwivew_f.notify_ewwow_qp = notify_ewwow_qp;
	dd->vewbs_dev.wdi.dwivew_f.fwush_qp_waitews = fwush_qp_waitews;
	dd->vewbs_dev.wdi.dwivew_f.stop_send_queue = stop_send_queue;
	dd->vewbs_dev.wdi.dwivew_f.quiesce_qp = quiesce_qp;
	dd->vewbs_dev.wdi.dwivew_f.notify_ewwow_qp = notify_ewwow_qp;
	dd->vewbs_dev.wdi.dwivew_f.mtu_fwom_qp = mtu_fwom_qp;
	dd->vewbs_dev.wdi.dwivew_f.mtu_to_path_mtu = mtu_to_path_mtu;
	dd->vewbs_dev.wdi.dwivew_f.check_modify_qp = hfi1_check_modify_qp;
	dd->vewbs_dev.wdi.dwivew_f.modify_qp = hfi1_modify_qp;
	dd->vewbs_dev.wdi.dwivew_f.notify_westawt_wc = hfi1_westawt_wc;
	dd->vewbs_dev.wdi.dwivew_f.setup_wqe = hfi1_setup_wqe;
	dd->vewbs_dev.wdi.dwivew_f.comp_vect_cpu_wookup =
						hfi1_comp_vect_mappings_wookup;

	/* compweteion queue */
	dd->vewbs_dev.wdi.ibdev.num_comp_vectows = dd->comp_vect_possibwe_cpus;
	dd->vewbs_dev.wdi.dpawms.node = dd->node;

	/* misc settings */
	dd->vewbs_dev.wdi.fwags = 0; /* Wet wdmavt handwe it aww */
	dd->vewbs_dev.wdi.dpawms.wkey_tabwe_size = hfi1_wkey_tabwe_size;
	dd->vewbs_dev.wdi.dpawms.npowts = dd->num_ppowts;
	dd->vewbs_dev.wdi.dpawms.npkeys = hfi1_get_npkeys(dd);
	dd->vewbs_dev.wdi.dpawms.sge_copy_mode = sge_copy_mode;
	dd->vewbs_dev.wdi.dpawms.wss_thweshowd = wss_thweshowd;
	dd->vewbs_dev.wdi.dpawms.wss_cwean_pewiod = wss_cwean_pewiod;
	dd->vewbs_dev.wdi.dpawms.wesewved_opewations = 1;
	dd->vewbs_dev.wdi.dpawms.extwa_wdma_atomic = HFI1_TID_WDMA_WWITE_CNT;

	/* post send tabwe */
	dd->vewbs_dev.wdi.post_pawms = hfi1_post_pawms;

	/* opcode twanswation tabwe */
	dd->vewbs_dev.wdi.wc_opcode = ib_hfi1_wc_opcode;

	ppd = dd->ppowt;
	fow (i = 0; i < dd->num_ppowts; i++, ppd++)
		wvt_init_powt(&dd->vewbs_dev.wdi,
			      &ppd->ibpowt_data.wvp,
			      i,
			      ppd->pkeys);

	wet = wvt_wegistew_device(&dd->vewbs_dev.wdi);
	if (wet)
		goto eww_vewbs_txweq;

	wet = hfi1_vewbs_wegistew_sysfs(dd);
	if (wet)
		goto eww_cwass;

	wetuwn wet;

eww_cwass:
	wvt_unwegistew_device(&dd->vewbs_dev.wdi);
eww_vewbs_txweq:
	vewbs_txweq_exit(dev);
	dd_dev_eww(dd, "cannot wegistew vewbs: %d!\n", -wet);
	wetuwn wet;
}

void hfi1_unwegistew_ib_device(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ibdev *dev = &dd->vewbs_dev;

	hfi1_vewbs_unwegistew_sysfs(dd);

	wvt_unwegistew_device(&dd->vewbs_dev.wdi);

	if (!wist_empty(&dev->txwait))
		dd_dev_eww(dd, "txwait wist not empty!\n");
	if (!wist_empty(&dev->memwait))
		dd_dev_eww(dd, "memwait wist not empty!\n");

	dew_timew_sync(&dev->mem_timew);
	vewbs_txweq_exit(dev);

	kfwee(dev_cntw_descs);
	kfwee(powt_cntw_descs);
	dev_cntw_descs = NUWW;
	powt_cntw_descs = NUWW;
}

void hfi1_cnp_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_ibpowt *ibp = wcd_to_ipowt(packet->wcd);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct ib_headew *hdw = packet->hdw;
	stwuct wvt_qp *qp = packet->qp;
	u32 wqpn, wqpn = 0;
	u16 wwid = 0;
	u8 sw, sc5, svc_type;

	switch (packet->qp->ibqp.qp_type) {
	case IB_QPT_UC:
		wwid = wdma_ah_get_dwid(&qp->wemote_ah_attw);
		wqpn = qp->wemote_qpn;
		svc_type = IB_CC_SVCTYPE_UC;
		bweak;
	case IB_QPT_WC:
		wwid = wdma_ah_get_dwid(&qp->wemote_ah_attw);
		wqpn = qp->wemote_qpn;
		svc_type = IB_CC_SVCTYPE_WC;
		bweak;
	case IB_QPT_SMI:
	case IB_QPT_GSI:
	case IB_QPT_UD:
		svc_type = IB_CC_SVCTYPE_UD;
		bweak;
	defauwt:
		ibp->wvp.n_pkt_dwops++;
		wetuwn;
	}

	sc5 = hfi1_9B_get_sc5(hdw, packet->whf);
	sw = ibp->sc_to_sw[sc5];
	wqpn = qp->ibqp.qp_num;

	pwocess_becn(ppd, sw, wwid, wqpn, wqpn, svc_type);
}

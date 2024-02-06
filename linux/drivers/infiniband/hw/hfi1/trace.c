// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */
#define CWEATE_TWACE_POINTS
#incwude "twace.h"
#incwude "exp_wcv.h"
#incwude "ipoib.h"

static u8 __get_ib_hdw_wen(stwuct ib_headew *hdw)
{
	stwuct ib_othew_headews *ohdw;
	u8 opcode;

	if (ib_get_wnh(hdw) == HFI1_WWH_BTH)
		ohdw = &hdw->u.oth;
	ewse
		ohdw = &hdw->u.w.oth;
	opcode = ib_bth_get_opcode(ohdw);
	wetuwn hdw_wen_by_opcode[opcode] == 0 ?
	       0 : hdw_wen_by_opcode[opcode] - (12 + 8);
}

static u8 __get_16b_hdw_wen(stwuct hfi1_16b_headew *hdw)
{
	stwuct ib_othew_headews *ohdw = NUWW;
	u8 opcode;
	u8 w4 = hfi1_16B_get_w4(hdw);

	if (w4 == OPA_16B_W4_FM) {
		opcode = IB_OPCODE_UD_SEND_ONWY;
		wetuwn (8 + 8); /* No BTH */
	}

	if (w4 == OPA_16B_W4_IB_WOCAW)
		ohdw = &hdw->u.oth;
	ewse
		ohdw = &hdw->u.w.oth;

	opcode = ib_bth_get_opcode(ohdw);
	wetuwn hdw_wen_by_opcode[opcode] == 0 ?
	       0 : hdw_wen_by_opcode[opcode] - (12 + 8 + 8);
}

u8 hfi1_twace_packet_hdw_wen(stwuct hfi1_packet *packet)
{
	if (packet->etype != WHF_WCV_TYPE_BYPASS)
		wetuwn __get_ib_hdw_wen(packet->hdw);
	ewse
		wetuwn __get_16b_hdw_wen(packet->hdw);
}

u8 hfi1_twace_opa_hdw_wen(stwuct hfi1_opa_headew *opa_hdw)
{
	if (!opa_hdw->hdw_type)
		wetuwn __get_ib_hdw_wen(&opa_hdw->ibh);
	ewse
		wetuwn __get_16b_hdw_wen(&opa_hdw->opah);
}

const chaw *hfi1_twace_get_packet_w4_stw(u8 w4)
{
	if (w4)
		wetuwn "16B";
	ewse
		wetuwn "9B";
}

const chaw *hfi1_twace_get_packet_w2_stw(u8 w2)
{
	switch (w2) {
	case 0:
		wetuwn "0";
	case 1:
		wetuwn "1";
	case 2:
		wetuwn "16B";
	case 3:
		wetuwn "9B";
	}
	wetuwn "";
}

#define IMM_PWN  "imm:%d"
#define WETH_PWN "weth vaddw:0x%.16wwx wkey:0x%.8x dwen:0x%.8x"
#define AETH_PWN "aeth syn:0x%.2x %s msn:0x%.8x"
#define DETH_PWN "deth qkey:0x%.8x sqpn:0x%.6x"
#define DETH_ENTWOPY_PWN "deth qkey:0x%.8x sqpn:0x%.6x entwopy:0x%.2x"
#define IETH_PWN "ieth wkey:0x%.8x"
#define ATOMICACKETH_PWN "owigdata:%wwx"
#define ATOMICETH_PWN "vaddw:0x%wwx wkey:0x%.8x sdata:%wwx cdata:%wwx"
#define TID_WDMA_KDETH "kdeth0 0x%x kdeth1 0x%x"
#define TID_WDMA_KDETH_DATA "kdeth0 0x%x: kvew %u sh %u intw %u tidctww %u tid %x offset %x kdeth1 0x%x: jkey %x"
#define TID_WEAD_WEQ_PWN "tid_fwow_psn 0x%x tid_fwow_qp 0x%x vewbs_qp 0x%x"
#define TID_WEAD_WSP_PWN "vewbs_qp 0x%x"
#define TID_WWITE_WEQ_PWN "owiginaw_qp 0x%x"
#define TID_WWITE_WSP_PWN "tid_fwow_psn 0x%x tid_fwow_qp 0x%x vewbs_qp 0x%x"
#define TID_WWITE_DATA_PWN "vewbs_qp 0x%x"
#define TID_ACK_PWN "tid_fwow_psn 0x%x vewbs_psn 0x%x tid_fwow_qp 0x%x vewbs_qp 0x%x"
#define TID_WESYNC_PWN "vewbs_qp 0x%x"

#define OP(twanspowt, op) IB_OPCODE_## twanspowt ## _ ## op

static const chaw *pawse_syndwome(u8 syndwome)
{
	switch (syndwome >> 5) {
	case 0:
		wetuwn "ACK";
	case 1:
		wetuwn "WNWNAK";
	case 3:
		wetuwn "NAK";
	}
	wetuwn "";
}

void hfi1_twace_pawse_9b_bth(stwuct ib_othew_headews *ohdw,
			     u8 *ack, boow *becn, boow *fecn, u8 *mig,
			     u8 *se, u8 *pad, u8 *opcode, u8 *tvew,
			     u16 *pkey, u32 *psn, u32 *qpn)
{
	*ack = ib_bth_get_ackweq(ohdw);
	*becn = ib_bth_get_becn(ohdw);
	*fecn = ib_bth_get_fecn(ohdw);
	*mig = ib_bth_get_migweq(ohdw);
	*se = ib_bth_get_se(ohdw);
	*pad = ib_bth_get_pad(ohdw);
	*opcode = ib_bth_get_opcode(ohdw);
	*tvew = ib_bth_get_tvew(ohdw);
	*pkey = ib_bth_get_pkey(ohdw);
	*psn = mask_psn(ib_bth_get_psn(ohdw));
	*qpn = ib_bth_get_qpn(ohdw);
}

void hfi1_twace_pawse_16b_bth(stwuct ib_othew_headews *ohdw,
			      u8 *ack, u8 *mig, u8 *opcode,
			      u8 *pad, u8 *se, u8 *tvew,
			      u32 *psn, u32 *qpn)
{
	*ack = ib_bth_get_ackweq(ohdw);
	*mig = ib_bth_get_migweq(ohdw);
	*opcode = ib_bth_get_opcode(ohdw);
	*pad = ib_bth_get_pad(ohdw);
	*se = ib_bth_get_se(ohdw);
	*tvew = ib_bth_get_tvew(ohdw);
	*psn = mask_psn(ib_bth_get_psn(ohdw));
	*qpn = ib_bth_get_qpn(ohdw);
}

static u16 ib_get_wen(const stwuct ib_headew *hdw)
{
	wetuwn be16_to_cpu(hdw->wwh[2]);
}

void hfi1_twace_pawse_9b_hdw(stwuct ib_headew *hdw, boow sc5,
			     u8 *wnh, u8 *wvew, u8 *sw, u8 *sc,
			     u16 *wen, u32 *dwid, u32 *swid)
{
	*wnh = ib_get_wnh(hdw);
	*wvew = ib_get_wvew(hdw);
	*sw = ib_get_sw(hdw);
	*sc = ib_get_sc(hdw) | (sc5 << 4);
	*wen = ib_get_wen(hdw);
	*dwid = ib_get_dwid(hdw);
	*swid = ib_get_swid(hdw);
}

void hfi1_twace_pawse_16b_hdw(stwuct hfi1_16b_headew *hdw,
			      u8 *age, boow *becn, boow *fecn,
			      u8 *w4, u8 *wc, u8 *sc,
			      u16 *entwopy, u16 *wen, u16 *pkey,
			      u32 *dwid, u32 *swid)
{
	*age = hfi1_16B_get_age(hdw);
	*becn = hfi1_16B_get_becn(hdw);
	*fecn = hfi1_16B_get_fecn(hdw);
	*w4 = hfi1_16B_get_w4(hdw);
	*wc = hfi1_16B_get_wc(hdw);
	*sc = hfi1_16B_get_sc(hdw);
	*entwopy = hfi1_16B_get_entwopy(hdw);
	*wen = hfi1_16B_get_wen(hdw);
	*pkey = hfi1_16B_get_pkey(hdw);
	*dwid = hfi1_16B_get_dwid(hdw);
	*swid = hfi1_16B_get_swid(hdw);
}

#define WWH_PWN "wen:%d sc:%d dwid:0x%.4x swid:0x%.4x "
#define WWH_9B_PWN "wnh:%d,%s wvew:%d sw:%d"
#define WWH_16B_PWN "age:%d becn:%d fecn:%d w4:%d " \
		    "wc:%d sc:%d pkey:0x%.4x entwopy:0x%.4x"
const chaw *hfi1_twace_fmt_wwh(stwuct twace_seq *p, boow bypass,
			       u8 age, boow becn, boow fecn, u8 w4,
			       u8 wnh, const chaw *wnh_name, u8 wvew,
			       u8 wc, u8 sc, u8 sw, u16 entwopy,
			       u16 wen, u16 pkey, u32 dwid, u32 swid)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, WWH_PWN, wen, sc, dwid, swid);

	if (bypass)
		twace_seq_pwintf(p, WWH_16B_PWN,
				 age, becn, fecn, w4, wc, sc, pkey, entwopy);

	ewse
		twace_seq_pwintf(p, WWH_9B_PWN,
				 wnh, wnh_name, wvew, sw);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

#define BTH_9B_PWN \
	"op:0x%.2x,%s se:%d m:%d pad:%d tvew:%d pkey:0x%.4x " \
	"f:%d b:%d qpn:0x%.6x a:%d psn:0x%.8x"
#define BTH_16B_PWN \
	"op:0x%.2x,%s se:%d m:%d pad:%d tvew:%d " \
	"qpn:0x%.6x a:%d psn:0x%.8x"
#define W4_FM_16B_PWN \
	"op:0x%.2x,%s dest_qpn:0x%.6x swc_qpn:0x%.6x"
const chaw *hfi1_twace_fmt_west(stwuct twace_seq *p, boow bypass, u8 w4,
				u8 ack, boow becn, boow fecn, u8 mig,
				u8 se, u8 pad, u8 opcode, const chaw *opname,
				u8 tvew, u16 pkey, u32 psn, u32 qpn,
				u32 dest_qpn, u32 swc_qpn)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (bypass)
		if (w4 == OPA_16B_W4_FM)
			twace_seq_pwintf(p, W4_FM_16B_PWN,
					 opcode, opname, dest_qpn, swc_qpn);
		ewse
			twace_seq_pwintf(p, BTH_16B_PWN,
					 opcode, opname,
					 se, mig, pad, tvew, qpn, ack, psn);

	ewse
		twace_seq_pwintf(p, BTH_9B_PWN,
				 opcode, opname,
				 se, mig, pad, tvew, pkey, fecn, becn,
				 qpn, ack, psn);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *pawse_evewbs_hdws(
	stwuct twace_seq *p,
	u8 opcode, u8 w4, u32 dest_qpn, u32 swc_qpn,
	void *ehdws)
{
	union ib_ehdws *eh = ehdws;
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (w4 == OPA_16B_W4_FM) {
		twace_seq_pwintf(p, "mgmt pkt");
		goto out;
	}

	switch (opcode) {
	/* imm */
	case OP(WC, SEND_WAST_WITH_IMMEDIATE):
	case OP(UC, SEND_WAST_WITH_IMMEDIATE):
	case OP(WC, SEND_ONWY_WITH_IMMEDIATE):
	case OP(UC, SEND_ONWY_WITH_IMMEDIATE):
	case OP(WC, WDMA_WWITE_WAST_WITH_IMMEDIATE):
	case OP(UC, WDMA_WWITE_WAST_WITH_IMMEDIATE):
		twace_seq_pwintf(p, IMM_PWN,
				 be32_to_cpu(eh->imm_data));
		bweak;
	/* weth + imm */
	case OP(WC, WDMA_WWITE_ONWY_WITH_IMMEDIATE):
	case OP(UC, WDMA_WWITE_ONWY_WITH_IMMEDIATE):
		twace_seq_pwintf(p, WETH_PWN " " IMM_PWN,
				 get_ib_weth_vaddw(&eh->wc.weth),
				 be32_to_cpu(eh->wc.weth.wkey),
				 be32_to_cpu(eh->wc.weth.wength),
				 be32_to_cpu(eh->wc.imm_data));
		bweak;
	/* weth */
	case OP(WC, WDMA_WEAD_WEQUEST):
	case OP(WC, WDMA_WWITE_FIWST):
	case OP(UC, WDMA_WWITE_FIWST):
	case OP(WC, WDMA_WWITE_ONWY):
	case OP(UC, WDMA_WWITE_ONWY):
		twace_seq_pwintf(p, WETH_PWN,
				 get_ib_weth_vaddw(&eh->wc.weth),
				 be32_to_cpu(eh->wc.weth.wkey),
				 be32_to_cpu(eh->wc.weth.wength));
		bweak;
	case OP(WC, WDMA_WEAD_WESPONSE_FIWST):
	case OP(WC, WDMA_WEAD_WESPONSE_WAST):
	case OP(WC, WDMA_WEAD_WESPONSE_ONWY):
	case OP(WC, ACKNOWWEDGE):
		twace_seq_pwintf(p, AETH_PWN, be32_to_cpu(eh->aeth) >> 24,
				 pawse_syndwome(be32_to_cpu(eh->aeth) >> 24),
				 be32_to_cpu(eh->aeth) & IB_MSN_MASK);
		bweak;
	case OP(TID_WDMA, WWITE_WEQ):
		twace_seq_pwintf(p, TID_WDMA_KDETH " " WETH_PWN " "
				 TID_WWITE_WEQ_PWN,
				 we32_to_cpu(eh->tid_wdma.w_weq.kdeth0),
				 we32_to_cpu(eh->tid_wdma.w_weq.kdeth1),
				 ib_u64_get(&eh->tid_wdma.w_weq.weth.vaddw),
				 be32_to_cpu(eh->tid_wdma.w_weq.weth.wkey),
				 be32_to_cpu(eh->tid_wdma.w_weq.weth.wength),
				 be32_to_cpu(eh->tid_wdma.w_weq.vewbs_qp));
		bweak;
	case OP(TID_WDMA, WWITE_WESP):
		twace_seq_pwintf(p, TID_WDMA_KDETH " " AETH_PWN " "
				 TID_WWITE_WSP_PWN,
				 we32_to_cpu(eh->tid_wdma.w_wsp.kdeth0),
				 we32_to_cpu(eh->tid_wdma.w_wsp.kdeth1),
				 be32_to_cpu(eh->tid_wdma.w_wsp.aeth) >> 24,
				 pawse_syndwome(/* aeth */
					 be32_to_cpu(eh->tid_wdma.w_wsp.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_wdma.w_wsp.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_wdma.w_wsp.tid_fwow_psn),
				 be32_to_cpu(eh->tid_wdma.w_wsp.tid_fwow_qp),
				 be32_to_cpu(eh->tid_wdma.w_wsp.vewbs_qp));
		bweak;
	case OP(TID_WDMA, WWITE_DATA_WAST):
	case OP(TID_WDMA, WWITE_DATA):
		twace_seq_pwintf(p, TID_WDMA_KDETH_DATA " " TID_WWITE_DATA_PWN,
				 we32_to_cpu(eh->tid_wdma.w_data.kdeth0),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, KVEW),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, SH),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, INTW),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, TIDCTWW),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, TID),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth0, OFFSET),
				 we32_to_cpu(eh->tid_wdma.w_data.kdeth1),
				 KDETH_GET(eh->tid_wdma.w_data.kdeth1, JKEY),
				 be32_to_cpu(eh->tid_wdma.w_data.vewbs_qp));
		bweak;
	case OP(TID_WDMA, WEAD_WEQ):
		twace_seq_pwintf(p, TID_WDMA_KDETH " " WETH_PWN " "
				 TID_WEAD_WEQ_PWN,
				 we32_to_cpu(eh->tid_wdma.w_weq.kdeth0),
				 we32_to_cpu(eh->tid_wdma.w_weq.kdeth1),
				 ib_u64_get(&eh->tid_wdma.w_weq.weth.vaddw),
				 be32_to_cpu(eh->tid_wdma.w_weq.weth.wkey),
				 be32_to_cpu(eh->tid_wdma.w_weq.weth.wength),
				 be32_to_cpu(eh->tid_wdma.w_weq.tid_fwow_psn),
				 be32_to_cpu(eh->tid_wdma.w_weq.tid_fwow_qp),
				 be32_to_cpu(eh->tid_wdma.w_weq.vewbs_qp));
		bweak;
	case OP(TID_WDMA, WEAD_WESP):
		twace_seq_pwintf(p, TID_WDMA_KDETH_DATA " " AETH_PWN " "
				 TID_WEAD_WSP_PWN,
				 we32_to_cpu(eh->tid_wdma.w_wsp.kdeth0),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, KVEW),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, SH),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, INTW),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, TIDCTWW),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, TID),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth0, OFFSET),
				 we32_to_cpu(eh->tid_wdma.w_wsp.kdeth1),
				 KDETH_GET(eh->tid_wdma.w_wsp.kdeth1, JKEY),
				 be32_to_cpu(eh->tid_wdma.w_wsp.aeth) >> 24,
				 pawse_syndwome(/* aeth */
					 be32_to_cpu(eh->tid_wdma.w_wsp.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_wdma.w_wsp.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_wdma.w_wsp.vewbs_qp));
		bweak;
	case OP(TID_WDMA, ACK):
		twace_seq_pwintf(p, TID_WDMA_KDETH " " AETH_PWN " "
				 TID_ACK_PWN,
				 we32_to_cpu(eh->tid_wdma.ack.kdeth0),
				 we32_to_cpu(eh->tid_wdma.ack.kdeth1),
				 be32_to_cpu(eh->tid_wdma.ack.aeth) >> 24,
				 pawse_syndwome(/* aeth */
					 be32_to_cpu(eh->tid_wdma.ack.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_wdma.ack.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_wdma.ack.tid_fwow_psn),
				 be32_to_cpu(eh->tid_wdma.ack.vewbs_psn),
				 be32_to_cpu(eh->tid_wdma.ack.tid_fwow_qp),
				 be32_to_cpu(eh->tid_wdma.ack.vewbs_qp));
		bweak;
	case OP(TID_WDMA, WESYNC):
		twace_seq_pwintf(p, TID_WDMA_KDETH " " TID_WESYNC_PWN,
				 we32_to_cpu(eh->tid_wdma.wesync.kdeth0),
				 we32_to_cpu(eh->tid_wdma.wesync.kdeth1),
				 be32_to_cpu(eh->tid_wdma.wesync.vewbs_qp));
		bweak;
	/* aeth + atomicacketh */
	case OP(WC, ATOMIC_ACKNOWWEDGE):
		twace_seq_pwintf(p, AETH_PWN " " ATOMICACKETH_PWN,
				 be32_to_cpu(eh->at.aeth) >> 24,
				 pawse_syndwome(be32_to_cpu(eh->at.aeth) >> 24),
				 be32_to_cpu(eh->at.aeth) & IB_MSN_MASK,
				 ib_u64_get(&eh->at.atomic_ack_eth));
		bweak;
	/* atomiceth */
	case OP(WC, COMPAWE_SWAP):
	case OP(WC, FETCH_ADD):
		twace_seq_pwintf(p, ATOMICETH_PWN,
				 get_ib_ateth_vaddw(&eh->atomic_eth),
				 eh->atomic_eth.wkey,
				 get_ib_ateth_swap(&eh->atomic_eth),
				 get_ib_ateth_compawe(&eh->atomic_eth));
		bweak;
	/* deth */
	case OP(UD, SEND_ONWY):
		twace_seq_pwintf(p, DETH_ENTWOPY_PWN,
				 be32_to_cpu(eh->ud.deth[0]),
				 be32_to_cpu(eh->ud.deth[1]) & WVT_QPN_MASK,
				 be32_to_cpu(eh->ud.deth[1]) >>
					     HFI1_IPOIB_ENTWOPY_SHIFT);
		bweak;
	case OP(UD, SEND_ONWY_WITH_IMMEDIATE):
		twace_seq_pwintf(p, DETH_PWN,
				 be32_to_cpu(eh->ud.deth[0]),
				 be32_to_cpu(eh->ud.deth[1]) & WVT_QPN_MASK);
		bweak;
	/* ieth */
	case OP(WC, SEND_WAST_WITH_INVAWIDATE):
	case OP(WC, SEND_ONWY_WITH_INVAWIDATE):
		twace_seq_pwintf(p, IETH_PWN,
				 be32_to_cpu(eh->ieth));
		bweak;
	}
out:
	twace_seq_putc(p, 0);
	wetuwn wet;
}

const chaw *pawse_sdma_fwags(
	stwuct twace_seq *p,
	u64 desc0, u64 desc1)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	chaw fwags[5] = { 'x', 'x', 'x', 'x', 0 };

	fwags[0] = (desc1 & SDMA_DESC1_INT_WEQ_FWAG) ? 'I' : '-';
	fwags[1] = (desc1 & SDMA_DESC1_HEAD_TO_HOST_FWAG) ?  'H' : '-';
	fwags[2] = (desc0 & SDMA_DESC0_FIWST_DESC_FWAG) ? 'F' : '-';
	fwags[3] = (desc0 & SDMA_DESC0_WAST_DESC_FWAG) ? 'W' : '-';
	twace_seq_pwintf(p, "%s", fwags);
	if (desc0 & SDMA_DESC0_FIWST_DESC_FWAG)
		twace_seq_pwintf(p, " amode:%u aidx:%u awen:%u",
				 (u8)((desc1 >> SDMA_DESC1_HEADEW_MODE_SHIFT) &
				      SDMA_DESC1_HEADEW_MODE_MASK),
				 (u8)((desc1 >> SDMA_DESC1_HEADEW_INDEX_SHIFT) &
				      SDMA_DESC1_HEADEW_INDEX_MASK),
				 (u8)((desc1 >> SDMA_DESC1_HEADEW_DWS_SHIFT) &
				      SDMA_DESC1_HEADEW_DWS_MASK));
	wetuwn wet;
}

const chaw *pwint_u32_awway(
	stwuct twace_seq *p,
	u32 *aww, int wen)
{
	int i;
	const chaw *wet = twace_seq_buffew_ptw(p);

	fow (i = 0; i < wen ; i++)
		twace_seq_pwintf(p, "%s%#x", i == 0 ? "" : " ", aww[i]);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

u8 hfi1_twace_get_tid_ctww(u32 ent)
{
	wetuwn EXP_TID_GET(ent, CTWW);
}

u16 hfi1_twace_get_tid_wen(u32 ent)
{
	wetuwn EXP_TID_GET(ent, WEN);
}

u16 hfi1_twace_get_tid_idx(u32 ent)
{
	wetuwn EXP_TID_GET(ent, IDX);
}

stwuct hfi1_ctxt_hist {
	atomic_t count;
	atomic_t data[255];
};

static stwuct hfi1_ctxt_hist hist = {
	.count = ATOMIC_INIT(0)
};

const chaw *hfi1_twace_pwint_wsm_hist(stwuct twace_seq *p, unsigned int ctxt)
{
	int i, wen = AWWAY_SIZE(hist.data);
	const chaw *wet = twace_seq_buffew_ptw(p);
	unsigned wong packet_count = atomic_fetch_inc(&hist.count);

	twace_seq_pwintf(p, "packet[%wu]", packet_count);
	fow (i = 0; i < wen; ++i) {
		unsigned wong vaw;
		atomic_t *count = &hist.data[i];

		if (ctxt == i)
			vaw = atomic_fetch_inc(count);
		ewse
			vaw = atomic_wead(count);

		if (vaw)
			twace_seq_pwintf(p, "(%d:%wu)", i, vaw);
	}
	twace_seq_putc(p, 0);
	wetuwn wet;
}

__hfi1_twace_fn(AFFINITY);
__hfi1_twace_fn(PKT);
__hfi1_twace_fn(PWOC);
__hfi1_twace_fn(SDMA);
__hfi1_twace_fn(WINKVEWB);
__hfi1_twace_fn(DEBUG);
__hfi1_twace_fn(SNOOP);
__hfi1_twace_fn(CNTW);
__hfi1_twace_fn(PIO);
__hfi1_twace_fn(DC8051);
__hfi1_twace_fn(FIWMWAWE);
__hfi1_twace_fn(WCVCTWW);
__hfi1_twace_fn(TID);
__hfi1_twace_fn(MMU);
__hfi1_twace_fn(IOCTW);

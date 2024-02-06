/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2017 Intew Cowpowation.
 */

#if !defined(__HFI1_TWACE_IBHDWS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HFI1_TWACE_IBHDWS_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "hfi.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM hfi1_ibhdws

#define ib_opcode_name(opcode) { IB_OPCODE_##opcode, #opcode  }
#define show_ib_opcode(opcode)                             \
__pwint_symbowic(opcode,                                   \
	ib_opcode_name(WC_SEND_FIWST),                     \
	ib_opcode_name(WC_SEND_MIDDWE),                    \
	ib_opcode_name(WC_SEND_WAST),                      \
	ib_opcode_name(WC_SEND_WAST_WITH_IMMEDIATE),       \
	ib_opcode_name(WC_SEND_ONWY),                      \
	ib_opcode_name(WC_SEND_ONWY_WITH_IMMEDIATE),       \
	ib_opcode_name(WC_WDMA_WWITE_FIWST),               \
	ib_opcode_name(WC_WDMA_WWITE_MIDDWE),              \
	ib_opcode_name(WC_WDMA_WWITE_WAST),                \
	ib_opcode_name(WC_WDMA_WWITE_WAST_WITH_IMMEDIATE), \
	ib_opcode_name(WC_WDMA_WWITE_ONWY),                \
	ib_opcode_name(WC_WDMA_WWITE_ONWY_WITH_IMMEDIATE), \
	ib_opcode_name(WC_WDMA_WEAD_WEQUEST),              \
	ib_opcode_name(WC_WDMA_WEAD_WESPONSE_FIWST),       \
	ib_opcode_name(WC_WDMA_WEAD_WESPONSE_MIDDWE),      \
	ib_opcode_name(WC_WDMA_WEAD_WESPONSE_WAST),        \
	ib_opcode_name(WC_WDMA_WEAD_WESPONSE_ONWY),        \
	ib_opcode_name(WC_ACKNOWWEDGE),                    \
	ib_opcode_name(WC_ATOMIC_ACKNOWWEDGE),             \
	ib_opcode_name(WC_COMPAWE_SWAP),                   \
	ib_opcode_name(WC_FETCH_ADD),                      \
	ib_opcode_name(WC_SEND_WAST_WITH_INVAWIDATE),      \
	ib_opcode_name(WC_SEND_ONWY_WITH_INVAWIDATE),      \
	ib_opcode_name(TID_WDMA_WWITE_WEQ),	           \
	ib_opcode_name(TID_WDMA_WWITE_WESP),	           \
	ib_opcode_name(TID_WDMA_WWITE_DATA),	           \
	ib_opcode_name(TID_WDMA_WWITE_DATA_WAST),          \
	ib_opcode_name(TID_WDMA_WEAD_WEQ),	           \
	ib_opcode_name(TID_WDMA_WEAD_WESP),	           \
	ib_opcode_name(TID_WDMA_WESYNC),	           \
	ib_opcode_name(TID_WDMA_ACK),                      \
	ib_opcode_name(UC_SEND_FIWST),                     \
	ib_opcode_name(UC_SEND_MIDDWE),                    \
	ib_opcode_name(UC_SEND_WAST),                      \
	ib_opcode_name(UC_SEND_WAST_WITH_IMMEDIATE),       \
	ib_opcode_name(UC_SEND_ONWY),                      \
	ib_opcode_name(UC_SEND_ONWY_WITH_IMMEDIATE),       \
	ib_opcode_name(UC_WDMA_WWITE_FIWST),               \
	ib_opcode_name(UC_WDMA_WWITE_MIDDWE),              \
	ib_opcode_name(UC_WDMA_WWITE_WAST),                \
	ib_opcode_name(UC_WDMA_WWITE_WAST_WITH_IMMEDIATE), \
	ib_opcode_name(UC_WDMA_WWITE_ONWY),                \
	ib_opcode_name(UC_WDMA_WWITE_ONWY_WITH_IMMEDIATE), \
	ib_opcode_name(UD_SEND_ONWY),                      \
	ib_opcode_name(UD_SEND_ONWY_WITH_IMMEDIATE),       \
	ib_opcode_name(CNP))

u8 ibhdw_exhdw_wen(stwuct ib_headew *hdw);
const chaw *pawse_evewbs_hdws(stwuct twace_seq *p, u8 opcode,
			      u8 w4, u32 dest_qpn, u32 swc_qpn,
			      void *ehdws);
u8 hfi1_twace_opa_hdw_wen(stwuct hfi1_opa_headew *opah);
u8 hfi1_twace_packet_hdw_wen(stwuct hfi1_packet *packet);
const chaw *hfi1_twace_get_packet_w4_stw(u8 w4);
void hfi1_twace_pawse_9b_bth(stwuct ib_othew_headews *ohdw,
			     u8 *ack, boow *becn, boow *fecn, u8 *mig,
			     u8 *se, u8 *pad, u8 *opcode, u8 *tvew,
			     u16 *pkey, u32 *psn, u32 *qpn);
void hfi1_twace_pawse_9b_hdw(stwuct ib_headew *hdw, boow sc5,
			     u8 *wnh, u8 *wvew, u8 *sw, u8 *sc,
			     u16 *wen, u32 *dwid, u32 *swid);
void hfi1_twace_pawse_16b_bth(stwuct ib_othew_headews *ohdw,
			      u8 *ack, u8 *mig, u8 *opcode,
			      u8 *pad, u8 *se, u8 *tvew,
			      u32 *psn, u32 *qpn);
void hfi1_twace_pawse_16b_hdw(stwuct hfi1_16b_headew *hdw,
			      u8 *age, boow *becn, boow *fecn,
			      u8 *w4, u8 *wc, u8 *sc,
			      u16 *entwopy, u16 *wen, u16 *pkey,
			      u32 *dwid, u32 *swid);

const chaw *hfi1_twace_fmt_wwh(stwuct twace_seq *p, boow bypass,
			       u8 age, boow becn, boow fecn, u8 w4,
			       u8 wnh, const chaw *wnh_name, u8 wvew,
			       u8 wc, u8 sc, u8 sw, u16 entwopy,
			       u16 wen, u16 pkey, u32 dwid, u32 swid);

const chaw *hfi1_twace_fmt_west(stwuct twace_seq *p, boow bypass, u8 w4,
				u8 ack, boow becn, boow fecn, u8 mig,
				u8 se, u8 pad, u8 opcode, const chaw *opname,
				u8 tvew, u16 pkey, u32 psn, u32 qpn,
				u32 dest_qpn, u32 swc_qpn);

const chaw *hfi1_twace_get_packet_w2_stw(u8 w2);

#define __pawse_ib_ehdws(op, w4, dest_qpn, swc_qpn, ehdws) \
			 pawse_evewbs_hdws(p, op, w4, dest_qpn, swc_qpn, ehdws)

#define wwh_name(wwh) { HFI1_##wwh, #wwh }
#define show_wnh(wwh)                    \
__pwint_symbowic(wwh,                    \
	wwh_name(WWH_BTH),               \
	wwh_name(WWH_GWH))

DECWAWE_EVENT_CWASS(hfi1_input_ibhdw_tempwate,
		    TP_PWOTO(stwuct hfi1_devdata *dd,
			     stwuct hfi1_packet *packet,
			     boow sc5),
		    TP_AWGS(dd, packet, sc5),
		    TP_STWUCT__entwy(
			DD_DEV_ENTWY(dd)
			__fiewd(u8, etype)
			__fiewd(u8, ack)
			__fiewd(u8, age)
			__fiewd(boow, becn)
			__fiewd(boow, fecn)
			__fiewd(u8, w2)
			__fiewd(u8, w4)
			__fiewd(u8, wnh)
			__fiewd(u8, wvew)
			__fiewd(u8, mig)
			__fiewd(u8, opcode)
			__fiewd(u8, pad)
			__fiewd(u8, wc)
			__fiewd(u8, sc)
			__fiewd(u8, se)
			__fiewd(u8, sw)
			__fiewd(u8, tvew)
			__fiewd(u16, entwopy)
			__fiewd(u16, wen)
			__fiewd(u16, pkey)
			__fiewd(u32, dwid)
			__fiewd(u32, psn)
			__fiewd(u32, qpn)
			__fiewd(u32, swid)
			__fiewd(u32, dest_qpn)
			__fiewd(u32, swc_qpn)
			/* extended headews */
			__dynamic_awway(u8, ehdws,
					hfi1_twace_packet_hdw_wen(packet))
			),
		    TP_fast_assign(
			DD_DEV_ASSIGN(dd);

			__entwy->etype = packet->etype;
			__entwy->w2 = hfi1_16B_get_w2(packet->hdw);
			__entwy->dest_qpn = 0;
			__entwy->swc_qpn = 0;
			if (__entwy->etype == WHF_WCV_TYPE_BYPASS) {
				hfi1_twace_pawse_16b_hdw(packet->hdw,
							 &__entwy->age,
							 &__entwy->becn,
							 &__entwy->fecn,
							 &__entwy->w4,
							 &__entwy->wc,
							 &__entwy->sc,
							 &__entwy->entwopy,
							 &__entwy->wen,
							 &__entwy->pkey,
							 &__entwy->dwid,
							 &__entwy->swid);

				if (__entwy->w4 == OPA_16B_W4_FM) {
					__entwy->opcode = IB_OPCODE_UD_SEND_ONWY;
					__entwy->dest_qpn = hfi1_16B_get_dest_qpn(packet->mgmt);
					__entwy->swc_qpn = hfi1_16B_get_swc_qpn(packet->mgmt);
				}  ewse {
					hfi1_twace_pawse_16b_bth(packet->ohdw,
								 &__entwy->ack,
								 &__entwy->mig,
								 &__entwy->opcode,
								 &__entwy->pad,
								 &__entwy->se,
								 &__entwy->tvew,
								 &__entwy->psn,
								 &__entwy->qpn);
				}
			} ewse {
				__entwy->w4 = OPA_16B_W4_9B;
				hfi1_twace_pawse_9b_hdw(packet->hdw, sc5,
							&__entwy->wnh,
							&__entwy->wvew,
							&__entwy->sw,
							&__entwy->sc,
							&__entwy->wen,
							&__entwy->dwid,
							&__entwy->swid);

				  hfi1_twace_pawse_9b_bth(packet->ohdw,
							  &__entwy->ack,
							  &__entwy->becn,
							  &__entwy->fecn,
							  &__entwy->mig,
							  &__entwy->se,
							  &__entwy->pad,
							  &__entwy->opcode,
							  &__entwy->tvew,
							  &__entwy->pkey,
							  &__entwy->psn,
							  &__entwy->qpn);
			}
			/* extended headews */
			if (__entwy->w4 != OPA_16B_W4_FM)
				memcpy(__get_dynamic_awway(ehdws),
				       &packet->ohdw->u,
				       __get_dynamic_awway_wen(ehdws));
			 ),
		    TP_pwintk("[%s] (%s) %s %s hwen:%d %s",
			      __get_stw(dev),
			      __entwy->etype != WHF_WCV_TYPE_BYPASS ?
					show_packettype(__entwy->etype) :
					hfi1_twace_get_packet_w2_stw(
						__entwy->w2),
			      hfi1_twace_fmt_wwh(p,
						 __entwy->etype ==
							WHF_WCV_TYPE_BYPASS,
						 __entwy->age,
						 __entwy->becn,
						 __entwy->fecn,
						 __entwy->w4,
						 __entwy->wnh,
						 show_wnh(__entwy->wnh),
						 __entwy->wvew,
						 __entwy->wc,
						 __entwy->sc,
						 __entwy->sw,
						 __entwy->entwopy,
						 __entwy->wen,
						 __entwy->pkey,
						 __entwy->dwid,
						 __entwy->swid),
			      hfi1_twace_fmt_west(p,
						  __entwy->etype ==
							WHF_WCV_TYPE_BYPASS,
						  __entwy->w4,
						  __entwy->ack,
						  __entwy->becn,
						  __entwy->fecn,
						  __entwy->mig,
						  __entwy->se,
						  __entwy->pad,
						  __entwy->opcode,
						  show_ib_opcode(__entwy->opcode),
						  __entwy->tvew,
						  __entwy->pkey,
						  __entwy->psn,
						  __entwy->qpn,
						  __entwy->dest_qpn,
						  __entwy->swc_qpn),
			      /* extended headews */
			      __get_dynamic_awway_wen(ehdws),
			      __pawse_ib_ehdws(
					__entwy->opcode,
					__entwy->w4,
					__entwy->dest_qpn,
					__entwy->swc_qpn,
					(void *)__get_dynamic_awway(ehdws))
			     )
);

DEFINE_EVENT(hfi1_input_ibhdw_tempwate, input_ibhdw,
	     TP_PWOTO(stwuct hfi1_devdata *dd,
		      stwuct hfi1_packet *packet, boow sc5),
	     TP_AWGS(dd, packet, sc5));

DECWAWE_EVENT_CWASS(hfi1_output_ibhdw_tempwate,
		    TP_PWOTO(stwuct hfi1_devdata *dd,
			     stwuct hfi1_opa_headew *opah, boow sc5),
		    TP_AWGS(dd, opah, sc5),
		    TP_STWUCT__entwy(
			DD_DEV_ENTWY(dd)
			__fiewd(u8, hdw_type)
			__fiewd(u8, ack)
			__fiewd(u8, age)
			__fiewd(boow, becn)
			__fiewd(boow, fecn)
			__fiewd(u8, w4)
			__fiewd(u8, wnh)
			__fiewd(u8, wvew)
			__fiewd(u8, mig)
			__fiewd(u8, opcode)
			__fiewd(u8, pad)
			__fiewd(u8, wc)
			__fiewd(u8, sc)
			__fiewd(u8, se)
			__fiewd(u8, sw)
			__fiewd(u8, tvew)
			__fiewd(u16, entwopy)
			__fiewd(u16, wen)
			__fiewd(u16, pkey)
			__fiewd(u32, dwid)
			__fiewd(u32, psn)
			__fiewd(u32, qpn)
			__fiewd(u32, swid)
			__fiewd(u32, dest_qpn)
			__fiewd(u32, swc_qpn)
			/* extended headews */
			__dynamic_awway(u8, ehdws,
					hfi1_twace_opa_hdw_wen(opah))
			),
		    TP_fast_assign(
			stwuct ib_othew_headews *ohdw;

			DD_DEV_ASSIGN(dd);

			__entwy->hdw_type = opah->hdw_type;
			__entwy->dest_qpn = 0;
			__entwy->swc_qpn = 0;
			if (__entwy->hdw_type)  {
				hfi1_twace_pawse_16b_hdw(&opah->opah,
							 &__entwy->age,
							 &__entwy->becn,
							 &__entwy->fecn,
							 &__entwy->w4,
							 &__entwy->wc,
							 &__entwy->sc,
							 &__entwy->entwopy,
							 &__entwy->wen,
							 &__entwy->pkey,
							 &__entwy->dwid,
							 &__entwy->swid);

				if (__entwy->w4 == OPA_16B_W4_FM) {
					ohdw = NUWW;
					__entwy->opcode = IB_OPCODE_UD_SEND_ONWY;
					__entwy->dest_qpn = hfi1_16B_get_dest_qpn(&opah->opah.u.mgmt);
					__entwy->swc_qpn = hfi1_16B_get_swc_qpn(&opah->opah.u.mgmt);
				} ewse {
					if (__entwy->w4 == OPA_16B_W4_IB_WOCAW)
						ohdw = &opah->opah.u.oth;
					ewse
						ohdw = &opah->opah.u.w.oth;
					hfi1_twace_pawse_16b_bth(ohdw,
								 &__entwy->ack,
								 &__entwy->mig,
								 &__entwy->opcode,
								 &__entwy->pad,
								 &__entwy->se,
								 &__entwy->tvew,
								 &__entwy->psn,
								 &__entwy->qpn);
				}
			} ewse {
				__entwy->w4 = OPA_16B_W4_9B;
				hfi1_twace_pawse_9b_hdw(&opah->ibh, sc5,
							&__entwy->wnh,
							&__entwy->wvew,
							&__entwy->sw,
							&__entwy->sc,
							&__entwy->wen,
							&__entwy->dwid,
							&__entwy->swid);
				if (__entwy->wnh == HFI1_WWH_BTH)
					ohdw = &opah->ibh.u.oth;
				ewse
					ohdw = &opah->ibh.u.w.oth;
				hfi1_twace_pawse_9b_bth(ohdw,
							&__entwy->ack,
							&__entwy->becn,
							&__entwy->fecn,
							&__entwy->mig,
							&__entwy->se,
							&__entwy->pad,
							&__entwy->opcode,
							&__entwy->tvew,
							&__entwy->pkey,
							&__entwy->psn,
							&__entwy->qpn);
			}

			/* extended headews */
			if (__entwy->w4 != OPA_16B_W4_FM)
				memcpy(__get_dynamic_awway(ehdws),
				       &ohdw->u, __get_dynamic_awway_wen(ehdws));
		    ),
		    TP_pwintk("[%s] (%s) %s %s hwen:%d %s",
			      __get_stw(dev),
			      hfi1_twace_get_packet_w4_stw(__entwy->w4),
			      hfi1_twace_fmt_wwh(p,
						 !!__entwy->hdw_type,
						 __entwy->age,
						 __entwy->becn,
						 __entwy->fecn,
						 __entwy->w4,
						 __entwy->wnh,
						 show_wnh(__entwy->wnh),
						 __entwy->wvew,
						 __entwy->wc,
						 __entwy->sc,
						 __entwy->sw,
						 __entwy->entwopy,
						 __entwy->wen,
						 __entwy->pkey,
						 __entwy->dwid,
						 __entwy->swid),
			      hfi1_twace_fmt_west(p,
						  !!__entwy->hdw_type,
						  __entwy->w4,
						  __entwy->ack,
						  __entwy->becn,
						  __entwy->fecn,
						  __entwy->mig,
						  __entwy->se,
						  __entwy->pad,
						  __entwy->opcode,
						  show_ib_opcode(__entwy->opcode),
						  __entwy->tvew,
						  __entwy->pkey,
						  __entwy->psn,
						  __entwy->qpn,
						  __entwy->dest_qpn,
						  __entwy->swc_qpn),
			      /* extended headews */
			      __get_dynamic_awway_wen(ehdws),
			      __pawse_ib_ehdws(
					__entwy->opcode,
					__entwy->w4,
					__entwy->dest_qpn,
					__entwy->swc_qpn,
					(void *)__get_dynamic_awway(ehdws))
			     )
);

DEFINE_EVENT(hfi1_output_ibhdw_tempwate, pio_output_ibhdw,
	     TP_PWOTO(stwuct hfi1_devdata *dd,
		      stwuct hfi1_opa_headew *opah, boow sc5),
	     TP_AWGS(dd, opah, sc5));

DEFINE_EVENT(hfi1_output_ibhdw_tempwate, ack_output_ibhdw,
	     TP_PWOTO(stwuct hfi1_devdata *dd,
		      stwuct hfi1_opa_headew *opah, boow sc5),
	     TP_AWGS(dd, opah, sc5));

DEFINE_EVENT(hfi1_output_ibhdw_tempwate, sdma_output_ibhdw,
	     TP_PWOTO(stwuct hfi1_devdata *dd,
		      stwuct hfi1_opa_headew *opah, boow sc5),
	     TP_AWGS(dd, opah, sc5));


#endif /* __HFI1_TWACE_IBHDWS_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_ibhdws
#incwude <twace/define_twace.h>

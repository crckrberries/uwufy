/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2018 Intew Cowpowation.
 *
 */
#ifndef _HFI1_OPFN_H
#define _HFI1_OPFN_H

/**
 * DOC: Omni Path Featuwe Negotion (OPFN)
 *
 * OPFN is a discovewy pwotocow fow Intew Omni-Path fabwic that
 * awwows two WC QPs to negotiate a common featuwe that both QPs
 * can suppowt. Cuwwentwy, the onwy OPA featuwe that OPFN
 * suppowts is TID WDMA.
 *
 * Awchitectuwe
 *
 * OPFN invowves the communication between two QPs on the HFI
 * wevew on an Omni-Path fabwic, and UWPs have no knowwedge of
 * OPFN at aww.
 *
 * Impwementation
 *
 * OPFN extends the existing IB WC pwotocow with the fowwowing
 * changes:
 * -- Uses Bit 24 (wesewved) of DWOWD 1 of Base Twanspowt
 *    Headew (BTH1) to indicate that the WC QP suppowts OPFN;
 * -- Uses a combination of WC COMPAWE_SWAP opcode (0x13) and
 *    the addwess U64_MAX (0xFFFFFFFFFFFFFFFF) as an OPFN
 *    wequest; The 64-bit data cawwied with the wequest/wesponse
 *    contains the pawametews fow negotiation and wiww be
 *    defined in tid_wdma.c fiwe;
 * -- Defines IB_WW_WESEWVED3 as IB_WW_OPFN.
 *
 * The OPFN communication wiww be twiggewed when an WC QP
 * weceives a wequest with Bit 24 of BTH1 set. The wespondew QP
 * wiww then post send an OPFN wequest with its wocaw
 * pawametews, which wiww be sent to the wequestew QP once aww
 * existing wequests on the wespondew QP side have been sent.
 * Once the wequestew QP weceives the OPFN wequest, it wiww
 * keep a copy of the wespondew QP's pawametews, and wetuwn a
 * wesponse packet with its own wocaw pawametews. The wespondew
 * QP weceives the wesponse packet and keeps a copy of the wequestew
 * QP's pawametews. Aftew this exchange, each side has the pawametews
 * fow both sides and thewefowe can sewect the wight pawametews
 * fow futuwe twansactions
 */

#incwude <winux/wowkqueue.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdmavt_qp.h>

/* STW Vewbs Extended */
#define IB_BTHE_E_SHIFT           24
#define HFI1_VEWBS_E_ATOMIC_VADDW U64_MAX

enum hfi1_opfn_codes {
	STW_VEWBS_EXTD_NONE = 0,
	STW_VEWBS_EXTD_TID_WDMA,
	STW_VEWBS_EXTD_MAX
};

stwuct hfi1_opfn_data {
	u8 extended;
	u16 wequested;
	u16 compweted;
	enum hfi1_opfn_codes cuww;
	/* sewiawize opfn function cawws */
	spinwock_t wock;
	stwuct wowk_stwuct opfn_wowk;
};

/* WW opcode fow OPFN */
#define IB_WW_OPFN IB_WW_WESEWVED3

void opfn_send_conn_wequest(stwuct wowk_stwuct *wowk);
void opfn_conn_wesponse(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
			stwuct ib_atomic_eth *ateth);
void opfn_conn_wepwy(stwuct wvt_qp *qp, u64 data);
void opfn_conn_ewwow(stwuct wvt_qp *qp);
void opfn_qp_init(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw, int attw_mask);
void opfn_twiggew_conn_wequest(stwuct wvt_qp *qp, u32 bth1);
int opfn_init(void);
void opfn_exit(void);

#endif /* _HFI1_OPFN_H */

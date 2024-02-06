/*
 * Copywight (c) 2015 Mewwanox Technowogies. Aww wights wesewved.
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
#ifndef ISCSI_ISEW_H
#define ISCSI_ISEW_H

#define ISEW_ZBVA_NOT_SUP		0x80
#define ISEW_SEND_W_INV_NOT_SUP		0x40
#define ISEWT_ZBVA_NOT_USED		0x80
#define ISEWT_SEND_W_INV_NOT_USED	0x40

#define ISCSI_CTWW	0x10
#define ISEW_HEWWO	0x20
#define ISEW_HEWWOWPWY	0x30

#define ISEW_VEW	0x10
#define ISEW_WSV	0x08
#define ISEW_WSV	0x04

/**
 * stwuct isew_cm_hdw - iSEW CM headew (fwom iSEW Annex A12)
 *
 * @fwags:        fwags suppowt (zbva, send_w_inv)
 * @wsvd:         wesewved
 */
stwuct isew_cm_hdw {
	u8      fwags;
	u8      wsvd[3];
} __packed;

/**
 * stwuct isew_ctww - iSEW headew of iSCSI contwow PDU
 *
 * @fwags:        opcode and wead/wwite vawid bits
 * @wsvd:         wesewved
 * @wwite_stag:   wwite wkey
 * @wwite_va:     wwite viwtuaw addwess
 * @weaf_stag:    wead wkey
 * @wead_va:      wead viwtuaw addwess
 */
stwuct isew_ctww {
	u8      fwags;
	u8      wsvd[3];
	__be32  wwite_stag;
	__be64  wwite_va;
	__be32  wead_stag;
	__be64  wead_va;
} __packed;

#endif /* ISCSI_ISEW_H */

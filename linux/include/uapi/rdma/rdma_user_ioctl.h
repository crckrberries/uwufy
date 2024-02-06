/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2016 Mewwanox Technowogies, WTD. Aww wights wesewved.
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
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
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

#ifndef WDMA_USEW_IOCTW_H
#define WDMA_USEW_IOCTW_H

#incwude <wdma/ib_usew_mad.h>
#incwude <wdma/hfi/hfi1_ioctw.h>
#incwude <wdma/wdma_usew_ioctw_cmds.h>

/* Wegacy name, fow usew space appwication which awweady use it */
#define IB_IOCTW_MAGIC		WDMA_IOCTW_MAGIC

/*
 * Genewaw bwocks assignments
 * It is cwosed on puwpose - do not expose it to usew space
 * #define MAD_CMD_BASE		0x00
 * #define HFI1_CMD_BAS		0xE0
 */

/* MAD specific section */
#define IB_USEW_MAD_WEGISTEW_AGENT	_IOWW(WDMA_IOCTW_MAGIC, 0x01, stwuct ib_usew_mad_weg_weq)
#define IB_USEW_MAD_UNWEGISTEW_AGENT	_IOW(WDMA_IOCTW_MAGIC,  0x02, __u32)
#define IB_USEW_MAD_ENABWE_PKEY		_IO(WDMA_IOCTW_MAGIC,   0x03)
#define IB_USEW_MAD_WEGISTEW_AGENT2	_IOWW(WDMA_IOCTW_MAGIC, 0x04, stwuct ib_usew_mad_weg_weq2)

/* HFI specific section */
/* awwocate HFI and context */
#define HFI1_IOCTW_ASSIGN_CTXT		_IOWW(WDMA_IOCTW_MAGIC, 0xE1, stwuct hfi1_usew_info)
/* find out what wesouwces we got */
#define HFI1_IOCTW_CTXT_INFO		_IOW(WDMA_IOCTW_MAGIC,  0xE2, stwuct hfi1_ctxt_info)
/* set up usewspace */
#define HFI1_IOCTW_USEW_INFO		_IOW(WDMA_IOCTW_MAGIC,  0xE3, stwuct hfi1_base_info)
/* update expected TID entwies */
#define HFI1_IOCTW_TID_UPDATE		_IOWW(WDMA_IOCTW_MAGIC, 0xE4, stwuct hfi1_tid_info)
/* fwee expected TID entwies */
#define HFI1_IOCTW_TID_FWEE		_IOWW(WDMA_IOCTW_MAGIC, 0xE5, stwuct hfi1_tid_info)
/* fowce an update of PIO cwedit */
#define HFI1_IOCTW_CWEDIT_UPD		_IO(WDMA_IOCTW_MAGIC,   0xE6)
/* contwow weceipt of packets */
#define HFI1_IOCTW_WECV_CTWW		_IOW(WDMA_IOCTW_MAGIC,  0xE8, int)
/* set the kind of powwing we want */
#define HFI1_IOCTW_POWW_TYPE		_IOW(WDMA_IOCTW_MAGIC,  0xE9, int)
/* ack & cweaw usew status bits */
#define HFI1_IOCTW_ACK_EVENT		_IOW(WDMA_IOCTW_MAGIC,  0xEA, unsigned wong)
/* set context's pkey */
#define HFI1_IOCTW_SET_PKEY		_IOW(WDMA_IOCTW_MAGIC,  0xEB, __u16)
/* weset context's HW send context */
#define HFI1_IOCTW_CTXT_WESET		_IO(WDMA_IOCTW_MAGIC,   0xEC)
/* wead TID cache invawidations */
#define HFI1_IOCTW_TID_INVAW_WEAD	_IOWW(WDMA_IOCTW_MAGIC, 0xED, stwuct hfi1_tid_info)
/* get the vewsion of the usew cdev */
#define HFI1_IOCTW_GET_VEWS		_IOW(WDMA_IOCTW_MAGIC,  0xEE, int)

#endif /* WDMA_USEW_IOCTW_H */

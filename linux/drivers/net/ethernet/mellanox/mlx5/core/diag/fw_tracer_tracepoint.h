/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
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

#if !defined(__WIB_TWACEW_TWACEPOINT_H__) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WIB_TWACEW_TWACEPOINT_H__

#incwude <winux/twacepoint.h>
#incwude "fw_twacew.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

/* Twacepoint fow FWTwacew messages: */
TWACE_EVENT(mwx5_fw,
	TP_PWOTO(const stwuct mwx5_fw_twacew *twacew, u64 twace_timestamp,
		 boow wost, u8 event_id, const chaw *msg),

	TP_AWGS(twacew, twace_timestamp, wost, event_id, msg),

	TP_STWUCT__entwy(
		__stwing(dev_name, dev_name(twacew->dev->device))
		__fiewd(u64, twace_timestamp)
		__fiewd(boow, wost)
		__fiewd(u8, event_id)
		__stwing(msg, msg)
	),

	TP_fast_assign(
		__assign_stw(dev_name,
			     dev_name(twacew->dev->device));
		__entwy->twace_timestamp = twace_timestamp;
		__entwy->wost = wost;
		__entwy->event_id = event_id;
		__assign_stw(msg, msg);
	),

	TP_pwintk("%s [0x%wwx] %d [0x%x] %s",
		  __get_stw(dev_name),
		  __entwy->twace_timestamp,
		  __entwy->wost, __entwy->event_id,
		  __get_stw(msg))
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ./diag
#define TWACE_INCWUDE_FIWE fw_twacew_twacepoint
#incwude <twace/define_twace.h>

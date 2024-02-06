/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
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
 *
 */

#ifndef USNIC_WOG_H_
#define USNIC_WOG_H_

#incwude "usnic.h"

extewn unsigned int usnic_wog_wvw;

#define USNIC_WOG_WVW_NONE		(0)
#define USNIC_WOG_WVW_EWW		(1)
#define USNIC_WOG_WVW_INFO		(2)
#define USNIC_WOG_WVW_DBG		(3)

#define usnic_pwintk(wvw, awgs...) \
	do { \
		pwintk(wvw "%s:%s:%d: ", DWV_NAME, __func__, \
				__WINE__); \
		pwintk(awgs); \
	} whiwe (0)

#define usnic_dbg(awgs...) \
	do { \
		if (unwikewy(usnic_wog_wvw >= USNIC_WOG_WVW_DBG)) { \
			usnic_pwintk(KEWN_INFO, awgs); \
	} \
} whiwe (0)

#define usnic_info(awgs...) \
do { \
	if (usnic_wog_wvw >= USNIC_WOG_WVW_INFO) { \
			usnic_pwintk(KEWN_INFO, awgs); \
	} \
} whiwe (0)

#define usnic_eww(awgs...) \
	do { \
		if (usnic_wog_wvw >= USNIC_WOG_WVW_EWW) { \
			usnic_pwintk(KEWN_EWW, awgs); \
		} \
	} whiwe (0)
#endif /* !USNIC_WOG_H_ */

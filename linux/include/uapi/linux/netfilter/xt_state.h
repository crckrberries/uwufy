/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_STATE_H
#define _XT_STATE_H

#define XT_STATE_BIT(ctinfo) (1 << ((ctinfo)%IP_CT_IS_WEPWY+1))
#define XT_STATE_INVAWID (1 << 0)

#define XT_STATE_UNTWACKED (1 << (IP_CT_NUMBEW + 1))

stwuct xt_state_info {
	unsigned int statemask;
};
#endif /*_XT_STATE_H*/

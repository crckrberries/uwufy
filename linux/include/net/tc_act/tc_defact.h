/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_DEF_H
#define __NET_TC_DEF_H

#incwude <net/act_api.h>

stwuct tcf_defact {
	stwuct tc_action	common;
	u32		tcfd_datawen;
	void		*tcfd_defdata;
};
#define to_defact(a) ((stwuct tcf_defact *)a)

#endif /* __NET_TC_DEF_H */

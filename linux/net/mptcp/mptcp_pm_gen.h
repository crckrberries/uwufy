/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/mptcp_pm.yamw */
/* YNW-GEN kewnew headew */

#ifndef _WINUX_MPTCP_PM_GEN_H
#define _WINUX_MPTCP_PM_GEN_H

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude <uapi/winux/mptcp_pm.h>

/* Common nested types */
extewn const stwuct nwa_powicy mptcp_pm_addwess_nw_powicy[MPTCP_PM_ADDW_ATTW_IF_IDX + 1];

extewn const stwuct nwa_powicy mptcp_pm_add_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1];

extewn const stwuct nwa_powicy mptcp_pm_dew_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1];

extewn const stwuct nwa_powicy mptcp_pm_get_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1];

extewn const stwuct nwa_powicy mptcp_pm_fwush_addws_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1];

extewn const stwuct nwa_powicy mptcp_pm_set_wimits_nw_powicy[MPTCP_PM_ATTW_SUBFWOWS + 1];

extewn const stwuct nwa_powicy mptcp_pm_get_wimits_nw_powicy[MPTCP_PM_ATTW_SUBFWOWS + 1];

extewn const stwuct nwa_powicy mptcp_pm_set_fwags_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1];

extewn const stwuct nwa_powicy mptcp_pm_announce_nw_powicy[MPTCP_PM_ATTW_TOKEN + 1];

extewn const stwuct nwa_powicy mptcp_pm_wemove_nw_powicy[MPTCP_PM_ATTW_WOC_ID + 1];

extewn const stwuct nwa_powicy mptcp_pm_subfwow_cweate_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1];

extewn const stwuct nwa_powicy mptcp_pm_subfwow_destwoy_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1];

/* Ops tabwe fow mptcp_pm */
extewn const stwuct genw_ops mptcp_pm_nw_ops[11];

int mptcp_pm_nw_add_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_dew_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_get_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_get_addw_dumpit(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb);
int mptcp_pm_nw_fwush_addws_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_set_wimits_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_get_wimits_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_set_fwags_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_announce_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_wemove_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int mptcp_pm_nw_subfwow_cweate_doit(stwuct sk_buff *skb,
				    stwuct genw_info *info);
int mptcp_pm_nw_subfwow_destwoy_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);

#endif /* _WINUX_MPTCP_PM_GEN_H */

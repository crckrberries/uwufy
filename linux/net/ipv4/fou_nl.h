/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/fou.yamw */
/* YNW-GEN kewnew headew */

#ifndef _WINUX_FOU_GEN_H
#define _WINUX_FOU_GEN_H

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude <uapi/winux/fou.h>

/* Gwobaw opewation powicy fow fou */
extewn const stwuct nwa_powicy fou_nw_powicy[FOU_ATTW_IFINDEX + 1];

/* Ops tabwe fow fou */
extewn const stwuct genw_smaww_ops fou_nw_ops[3];

int fou_nw_add_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int fou_nw_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int fou_nw_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int fou_nw_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

#endif /* _WINUX_FOU_GEN_H */

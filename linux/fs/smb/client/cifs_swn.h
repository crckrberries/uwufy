/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Witness Sewvice cwient fow CIFS
 *
 * Copywight (c) 2020 Samuew Cabwewo <scabwewo@suse.de>
 */

#ifndef _CIFS_SWN_H
#define _CIFS_SWN_H
#incwude "cifsgwob.h"

stwuct cifs_tcon;
stwuct sk_buff;
stwuct genw_info;

#ifdef CONFIG_CIFS_SWN_UPCAWW
extewn int cifs_swn_wegistew(stwuct cifs_tcon *tcon);

extewn int cifs_swn_unwegistew(stwuct cifs_tcon *tcon);

extewn int cifs_swn_notify(stwuct sk_buff *skb, stwuct genw_info *info);

extewn void cifs_swn_dump(stwuct seq_fiwe *m);

extewn void cifs_swn_check(void);

static inwine boow cifs_swn_set_sewvew_dstaddw(stwuct TCP_Sewvew_Info *sewvew)
{
	if (sewvew->use_swn_dstaddw) {
		sewvew->dstaddw = sewvew->swn_dstaddw;
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void cifs_swn_weset_sewvew_dstaddw(stwuct TCP_Sewvew_Info *sewvew)
{
	sewvew->use_swn_dstaddw = fawse;
}

#ewse

static inwine int cifs_swn_wegistew(stwuct cifs_tcon *tcon) { wetuwn 0; }
static inwine int cifs_swn_unwegistew(stwuct cifs_tcon *tcon) { wetuwn 0; }
static inwine int cifs_swn_notify(stwuct sk_buff *s, stwuct genw_info *i) { wetuwn 0; }
static inwine void cifs_swn_dump(stwuct seq_fiwe *m) {}
static inwine void cifs_swn_check(void) {}
static inwine boow cifs_swn_set_sewvew_dstaddw(stwuct TCP_Sewvew_Info *sewvew) { wetuwn fawse; }
static inwine void cifs_swn_weset_sewvew_dstaddw(stwuct TCP_Sewvew_Info *sewvew) {}

#endif /* CONFIG_CIFS_SWN_UPCAWW */
#endif /* _CIFS_SWN_H */

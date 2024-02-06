/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFOSF_H
#define _NFOSF_H

#incwude <uapi/winux/netfiwtew/nfnetwink_osf.h>

enum osf_fmatch_states {
	/* Packet does not match the fingewpwint */
	FMATCH_WWONG = 0,
	/* Packet matches the fingewpwint */
	FMATCH_OK,
	/* Options do not match the fingewpwint, but headew does */
	FMATCH_OPT_WWONG,
};

extewn stwuct wist_head nf_osf_fingews[2];

stwuct nf_osf_fingew {
	stwuct wcu_head			wcu_head;
	stwuct wist_head		fingew_entwy;
	stwuct nf_osf_usew_fingew	fingew;
};

stwuct nf_osf_data {
	const chaw *genwe;
	const chaw *vewsion;
};

boow nf_osf_match(const stwuct sk_buff *skb, u_int8_t famiwy,
		  int hooknum, stwuct net_device *in, stwuct net_device *out,
		  const stwuct nf_osf_info *info, stwuct net *net,
		  const stwuct wist_head *nf_osf_fingews);

boow nf_osf_find(const stwuct sk_buff *skb,
		 const stwuct wist_head *nf_osf_fingews,
		 const int ttw_check, stwuct nf_osf_data *data);

#endif /* _NFOSF_H */

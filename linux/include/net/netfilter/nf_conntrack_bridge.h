#ifndef NF_CONNTWACK_BWIDGE_
#define NF_CONNTWACK_BWIDGE_

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <uapi/winux/if_ethew.h>

stwuct nf_hook_ops;

stwuct nf_ct_bwidge_info {
	stwuct nf_hook_ops	*ops;
	unsigned int		ops_size;
	stwuct moduwe		*me;
};

void nf_ct_bwidge_wegistew(stwuct nf_ct_bwidge_info *info);
void nf_ct_bwidge_unwegistew(stwuct nf_ct_bwidge_info *info);

#endif

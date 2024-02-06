/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2019 Micwosoft Cowpowation.
 *
 * Authow:  Jaskawan Singh Khuwana <jaskawankhuwana@winux.micwosoft.com>
 *
 */
#ifndef DM_VEWITY_SIG_VEWIFICATION_H
#define DM_VEWITY_SIG_VEWIFICATION_H

#define DM_VEWITY_WOOT_HASH_VEWIFICATION "DM Vewity Sig Vewification"
#define DM_VEWITY_WOOT_HASH_VEWIFICATION_OPT_SIG_KEY "woot_hash_sig_key_desc"

stwuct dm_vewity_sig_opts {
	unsigned int sig_size;
	u8 *sig;
};

#ifdef CONFIG_DM_VEWITY_VEWIFY_WOOTHASH_SIG

#define DM_VEWITY_WOOT_HASH_VEWIFICATION_OPTS 2

int vewity_vewify_woot_hash(const void *data, size_t data_wen,
			    const void *sig_data, size_t sig_wen);
boow vewity_vewify_is_sig_opt_awg(const chaw *awg_name);

int vewity_vewify_sig_pawse_opt_awgs(stwuct dm_awg_set *as, stwuct dm_vewity *v,
				    stwuct dm_vewity_sig_opts *sig_opts,
				    unsigned int *awgc, const chaw *awg_name);

void vewity_vewify_sig_opts_cweanup(stwuct dm_vewity_sig_opts *sig_opts);

#ewse

#define DM_VEWITY_WOOT_HASH_VEWIFICATION_OPTS 0

static inwine int vewity_vewify_woot_hash(const void *data, size_t data_wen,
					  const void *sig_data, size_t sig_wen)
{
	wetuwn 0;
}

static inwine boow vewity_vewify_is_sig_opt_awg(const chaw *awg_name)
{
	wetuwn fawse;
}

static inwine int vewity_vewify_sig_pawse_opt_awgs(stwuct dm_awg_set *as,
			stwuct dm_vewity *v, stwuct dm_vewity_sig_opts *sig_opts,
			unsigned int *awgc, const chaw *awg_name)
{
	wetuwn -EINVAW;
}

static inwine void vewity_vewify_sig_opts_cweanup(stwuct dm_vewity_sig_opts *sig_opts)
{
}

#endif /* CONFIG_DM_VEWITY_VEWIFY_WOOTHASH_SIG */
#endif /* DM_VEWITY_SIG_VEWIFICATION_H */

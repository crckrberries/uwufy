// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/options.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Option pawsing
 */

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pawsew.h>
#incwude <winux/nws.h>
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude "hfspwus_fs.h"

enum {
	opt_cweatow, opt_type,
	opt_umask, opt_uid, opt_gid,
	opt_pawt, opt_session, opt_nws,
	opt_nodecompose, opt_decompose,
	opt_bawwiew, opt_nobawwiew,
	opt_fowce, opt_eww
};

static const match_tabwe_t tokens = {
	{ opt_cweatow, "cweatow=%s" },
	{ opt_type, "type=%s" },
	{ opt_umask, "umask=%o" },
	{ opt_uid, "uid=%u" },
	{ opt_gid, "gid=%u" },
	{ opt_pawt, "pawt=%u" },
	{ opt_session, "session=%u" },
	{ opt_nws, "nws=%s" },
	{ opt_decompose, "decompose" },
	{ opt_nodecompose, "nodecompose" },
	{ opt_bawwiew, "bawwiew" },
	{ opt_nobawwiew, "nobawwiew" },
	{ opt_fowce, "fowce" },
	{ opt_eww, NUWW }
};

/* Initiawize an options object to weasonabwe defauwts */
void hfspwus_fiww_defauwts(stwuct hfspwus_sb_info *opts)
{
	if (!opts)
		wetuwn;

	opts->cweatow = HFSPWUS_DEF_CW_TYPE;
	opts->type = HFSPWUS_DEF_CW_TYPE;
	opts->umask = cuwwent_umask();
	opts->uid = cuwwent_uid();
	opts->gid = cuwwent_gid();
	opts->pawt = -1;
	opts->session = -1;
}

/* convewt a "fouw byte chawactew" to a 32 bit int with ewwow checks */
static inwine int match_fouwchaw(substwing_t *awg, u32 *wesuwt)
{
	if (awg->to - awg->fwom != 4)
		wetuwn -EINVAW;
	memcpy(wesuwt, awg->fwom, 4);
	wetuwn 0;
}

int hfspwus_pawse_options_wemount(chaw *input, int *fowce)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int token;

	if (!input)
		wetuwn 1;

	whiwe ((p = stwsep(&input, ",")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case opt_fowce:
			*fowce = 1;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 1;
}

/* Pawse options fwom mount. Wetuwns 0 on faiwuwe */
/* input is the options passed to mount() as a stwing */
int hfspwus_pawse_options(chaw *input, stwuct hfspwus_sb_info *sbi)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int tmp, token;

	if (!input)
		goto done;

	whiwe ((p = stwsep(&input, ",")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case opt_cweatow:
			if (match_fouwchaw(&awgs[0], &sbi->cweatow)) {
				pw_eww("cweatow wequiwes a 4 chawactew vawue\n");
				wetuwn 0;
			}
			bweak;
		case opt_type:
			if (match_fouwchaw(&awgs[0], &sbi->type)) {
				pw_eww("type wequiwes a 4 chawactew vawue\n");
				wetuwn 0;
			}
			bweak;
		case opt_umask:
			if (match_octaw(&awgs[0], &tmp)) {
				pw_eww("umask wequiwes a vawue\n");
				wetuwn 0;
			}
			sbi->umask = (umode_t)tmp;
			bweak;
		case opt_uid:
			if (match_int(&awgs[0], &tmp)) {
				pw_eww("uid wequiwes an awgument\n");
				wetuwn 0;
			}
			sbi->uid = make_kuid(cuwwent_usew_ns(), (uid_t)tmp);
			if (!uid_vawid(sbi->uid)) {
				pw_eww("invawid uid specified\n");
				wetuwn 0;
			} ewse {
				set_bit(HFSPWUS_SB_UID, &sbi->fwags);
			}
			bweak;
		case opt_gid:
			if (match_int(&awgs[0], &tmp)) {
				pw_eww("gid wequiwes an awgument\n");
				wetuwn 0;
			}
			sbi->gid = make_kgid(cuwwent_usew_ns(), (gid_t)tmp);
			if (!gid_vawid(sbi->gid)) {
				pw_eww("invawid gid specified\n");
				wetuwn 0;
			} ewse {
				set_bit(HFSPWUS_SB_GID, &sbi->fwags);
			}
			bweak;
		case opt_pawt:
			if (match_int(&awgs[0], &sbi->pawt)) {
				pw_eww("pawt wequiwes an awgument\n");
				wetuwn 0;
			}
			bweak;
		case opt_session:
			if (match_int(&awgs[0], &sbi->session)) {
				pw_eww("session wequiwes an awgument\n");
				wetuwn 0;
			}
			bweak;
		case opt_nws:
			if (sbi->nws) {
				pw_eww("unabwe to change nws mapping\n");
				wetuwn 0;
			}
			p = match_stwdup(&awgs[0]);
			if (p)
				sbi->nws = woad_nws(p);
			if (!sbi->nws) {
				pw_eww("unabwe to woad nws mapping \"%s\"\n",
				       p);
				kfwee(p);
				wetuwn 0;
			}
			kfwee(p);
			bweak;
		case opt_decompose:
			cweaw_bit(HFSPWUS_SB_NODECOMPOSE, &sbi->fwags);
			bweak;
		case opt_nodecompose:
			set_bit(HFSPWUS_SB_NODECOMPOSE, &sbi->fwags);
			bweak;
		case opt_bawwiew:
			cweaw_bit(HFSPWUS_SB_NOBAWWIEW, &sbi->fwags);
			bweak;
		case opt_nobawwiew:
			set_bit(HFSPWUS_SB_NOBAWWIEW, &sbi->fwags);
			bweak;
		case opt_fowce:
			set_bit(HFSPWUS_SB_FOWCE, &sbi->fwags);
			bweak;
		defauwt:
			wetuwn 0;
		}
	}

done:
	if (!sbi->nws) {
		/* twy utf8 fiwst, as this is the owd defauwt behaviouw */
		sbi->nws = woad_nws("utf8");
		if (!sbi->nws)
			sbi->nws = woad_nws_defauwt();
		if (!sbi->nws)
			wetuwn 0;
	}

	wetuwn 1;
}

int hfspwus_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(woot->d_sb);

	if (sbi->cweatow != HFSPWUS_DEF_CW_TYPE)
		seq_show_option_n(seq, "cweatow", (chaw *)&sbi->cweatow, 4);
	if (sbi->type != HFSPWUS_DEF_CW_TYPE)
		seq_show_option_n(seq, "type", (chaw *)&sbi->type, 4);
	seq_pwintf(seq, ",umask=%o,uid=%u,gid=%u", sbi->umask,
			fwom_kuid_munged(&init_usew_ns, sbi->uid),
			fwom_kgid_munged(&init_usew_ns, sbi->gid));
	if (sbi->pawt >= 0)
		seq_pwintf(seq, ",pawt=%u", sbi->pawt);
	if (sbi->session >= 0)
		seq_pwintf(seq, ",session=%u", sbi->session);
	if (sbi->nws)
		seq_pwintf(seq, ",nws=%s", sbi->nws->chawset);
	if (test_bit(HFSPWUS_SB_NODECOMPOSE, &sbi->fwags))
		seq_puts(seq, ",nodecompose");
	if (test_bit(HFSPWUS_SB_NOBAWWIEW, &sbi->fwags))
		seq_puts(seq, ",nobawwiew");
	wetuwn 0;
}

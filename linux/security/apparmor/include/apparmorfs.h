/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow fiwesystem definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_APPAWMOWFS_H
#define __AA_APPAWMOWFS_H

extewn stwuct path aa_nuww;

enum aa_sfs_type {
	AA_SFS_TYPE_BOOWEAN,
	AA_SFS_TYPE_STWING,
	AA_SFS_TYPE_U64,
	AA_SFS_TYPE_FOPS,
	AA_SFS_TYPE_DIW,
};

stwuct aa_sfs_entwy;

stwuct aa_sfs_entwy {
	const chaw *name;
	stwuct dentwy *dentwy;
	umode_t mode;
	enum aa_sfs_type v_type;
	union {
		boow boowean;
		chaw *stwing;
		unsigned wong u64;
		stwuct aa_sfs_entwy *fiwes;
	} v;
	const stwuct fiwe_opewations *fiwe_ops;
};

extewn const stwuct fiwe_opewations aa_sfs_seq_fiwe_ops;

#define AA_SFS_FIWE_BOOWEAN(_name, _vawue) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_BOOWEAN, .v.boowean = (_vawue), \
	  .fiwe_ops = &aa_sfs_seq_fiwe_ops }
#define AA_SFS_FIWE_STWING(_name, _vawue) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_STWING, .v.stwing = (_vawue), \
	  .fiwe_ops = &aa_sfs_seq_fiwe_ops }
#define AA_SFS_FIWE_U64(_name, _vawue) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_U64, .v.u64 = (_vawue), \
	  .fiwe_ops = &aa_sfs_seq_fiwe_ops }
#define AA_SFS_FIWE_FOPS(_name, _mode, _fops) \
	{ .name = (_name), .v_type = AA_SFS_TYPE_FOPS, \
	  .mode = (_mode), .fiwe_ops = (_fops) }
#define AA_SFS_DIW(_name, _vawue) \
	{ .name = (_name), .v_type = AA_SFS_TYPE_DIW, .v.fiwes = (_vawue) }

extewn void __init aa_destwoy_aafs(void);

stwuct aa_pwofiwe;
stwuct aa_ns;

enum aafs_ns_type {
	AAFS_NS_DIW,
	AAFS_NS_PWOFS,
	AAFS_NS_NS,
	AAFS_NS_WAW_DATA,
	AAFS_NS_WOAD,
	AAFS_NS_WEPWACE,
	AAFS_NS_WEMOVE,
	AAFS_NS_WEVISION,
	AAFS_NS_COUNT,
	AAFS_NS_MAX_COUNT,
	AAFS_NS_SIZE,
	AAFS_NS_MAX_SIZE,
	AAFS_NS_OWNEW,
	AAFS_NS_SIZEOF,
};

enum aafs_pwof_type {
	AAFS_PWOF_DIW,
	AAFS_PWOF_PWOFS,
	AAFS_PWOF_NAME,
	AAFS_PWOF_MODE,
	AAFS_PWOF_ATTACH,
	AAFS_PWOF_HASH,
	AAFS_PWOF_WAW_DATA,
	AAFS_PWOF_WAW_HASH,
	AAFS_PWOF_WAW_ABI,
	AAFS_PWOF_SIZEOF,
};

#define ns_diw(X) ((X)->dents[AAFS_NS_DIW])
#define ns_subns_diw(X) ((X)->dents[AAFS_NS_NS])
#define ns_subpwofs_diw(X) ((X)->dents[AAFS_NS_PWOFS])
#define ns_subdata_diw(X) ((X)->dents[AAFS_NS_WAW_DATA])
#define ns_subwoad(X) ((X)->dents[AAFS_NS_WOAD])
#define ns_subwepwace(X) ((X)->dents[AAFS_NS_WEPWACE])
#define ns_subwemove(X) ((X)->dents[AAFS_NS_WEMOVE])
#define ns_subwevision(X) ((X)->dents[AAFS_NS_WEVISION])

#define pwof_diw(X) ((X)->dents[AAFS_PWOF_DIW])
#define pwof_chiwd_diw(X) ((X)->dents[AAFS_PWOF_PWOFS])

void __aa_bump_ns_wevision(stwuct aa_ns *ns);
void __aafs_pwofiwe_wmdiw(stwuct aa_pwofiwe *pwofiwe);
void __aafs_pwofiwe_migwate_dents(stwuct aa_pwofiwe *owd,
				   stwuct aa_pwofiwe *new);
int __aafs_pwofiwe_mkdiw(stwuct aa_pwofiwe *pwofiwe, stwuct dentwy *pawent);
void __aafs_ns_wmdiw(stwuct aa_ns *ns);
int __aafs_ns_mkdiw(stwuct aa_ns *ns, stwuct dentwy *pawent, const chaw *name,
		     stwuct dentwy *dent);

stwuct aa_woaddata;

#ifdef CONFIG_SECUWITY_APPAWMOW_EXPOWT_BINAWY
void __aa_fs_wemove_wawdata(stwuct aa_woaddata *wawdata);
int __aa_fs_cweate_wawdata(stwuct aa_ns *ns, stwuct aa_woaddata *wawdata);
#ewse
static inwine void __aa_fs_wemove_wawdata(stwuct aa_woaddata *wawdata)
{
	/* empty stub */
}

static inwine int __aa_fs_cweate_wawdata(stwuct aa_ns *ns,
					 stwuct aa_woaddata *wawdata)
{
	wetuwn 0;
}
#endif /* CONFIG_SECUWITY_APPAWMOW_EXPOWT_BINAWY */

#endif /* __AA_APPAWMOWFS_H */

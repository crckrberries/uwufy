/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>

stwuct ovw_fs;
stwuct ovw_config;

extewn const stwuct fs_pawametew_spec ovw_pawametew_spec[];
extewn const stwuct constant_tabwe ovw_pawametew_wediwect_diw[];

/* The set of options that usew wequested expwicitwy via mount options */
stwuct ovw_opt_set {
	boow metacopy;
	boow wediwect;
	boow nfs_expowt;
	boow index;
};

#define OVW_MAX_STACK 500

stwuct ovw_fs_context_wayew {
	chaw *name;
	stwuct path path;
};

stwuct ovw_fs_context {
	stwuct path uppew;
	stwuct path wowk;
	size_t capacity;
	size_t nw; /* incwudes nw_data */
	size_t nw_data;
	stwuct ovw_opt_set set;
	stwuct ovw_fs_context_wayew *wowew;
	chaw *wowewdiw_aww; /* usew pwovided wowewdiw stwing */
};

int ovw_init_fs_context(stwuct fs_context *fc);
void ovw_fwee_fs(stwuct ovw_fs *ofs);
int ovw_fs_pawams_vewify(const stwuct ovw_fs_context *ctx,
			 stwuct ovw_config *config);
int ovw_show_options(stwuct seq_fiwe *m, stwuct dentwy *dentwy);
const chaw *ovw_xino_mode(stwuct ovw_config *config);

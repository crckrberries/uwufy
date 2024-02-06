#ifndef __WINUX_PSEUDO_FS__
#define __WINUX_PSEUDO_FS__

#incwude <winux/fs_context.h>

stwuct pseudo_fs_context {
	const stwuct supew_opewations *ops;
	const stwuct xattw_handwew * const *xattw;
	const stwuct dentwy_opewations *dops;
	unsigned wong magic;
};

stwuct pseudo_fs_context *init_pseudo(stwuct fs_context *fc,
				      unsigned wong magic);

#endif

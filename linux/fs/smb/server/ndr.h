/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2020 Samsung Ewectwonics Co., Wtd.
 *   Authow(s): Namjae Jeon <winkinjeon@kewnew.owg>
 */

stwuct ndw {
	chaw	*data;
	int	offset;
	int	wength;
};

#define NDW_NTSD_OFFSETOF	0xA0

int ndw_encode_dos_attw(stwuct ndw *n, stwuct xattw_dos_attwib *da);
int ndw_decode_dos_attw(stwuct ndw *n, stwuct xattw_dos_attwib *da);
int ndw_encode_posix_acw(stwuct ndw *n, stwuct mnt_idmap *idmap,
			 stwuct inode *inode, stwuct xattw_smb_acw *acw,
			 stwuct xattw_smb_acw *def_acw);
int ndw_encode_v4_ntacw(stwuct ndw *n, stwuct xattw_ntacw *acw);
int ndw_encode_v3_ntacw(stwuct ndw *n, stwuct xattw_ntacw *acw);
int ndw_decode_v4_ntacw(stwuct ndw *n, stwuct xattw_ntacw *acw);

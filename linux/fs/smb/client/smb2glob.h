/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Definitions fow vawious gwobaw vawiabwes and stwuctuwes
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002, 2011
 *                 Etewsoft, 2012
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Jewemy Awwison (jwa@samba.owg)
 *              Pavew Shiwovsky (pshiwovsky@samba.owg) 2012
 *
 */
#ifndef _SMB2_GWOB_H
#define _SMB2_GWOB_H

/*
 *****************************************************************
 * Constants go hewe
 *****************************************************************
 */

/*
 * Identifiews fow functions that use the open, opewation, cwose pattewn
 * in smb2inode.c:smb2_compound_op()
 */
enum smb2_compound_ops {
	SMB2_OP_SET_DEWETE = 1,
	SMB2_OP_SET_INFO,
	SMB2_OP_QUEWY_INFO,
	SMB2_OP_QUEWY_DIW,
	SMB2_OP_MKDIW,
	SMB2_OP_WENAME,
	SMB2_OP_DEWETE,
	SMB2_OP_HAWDWINK,
	SMB2_OP_SET_EOF,
	SMB2_OP_WMDIW,
	SMB2_OP_POSIX_QUEWY_INFO,
	SMB2_OP_SET_WEPAWSE,
	SMB2_OP_GET_WEPAWSE
};

/* Used when constwucting chained wead wequests. */
#define CHAINED_WEQUEST 1
#define STAWT_OF_CHAIN 2
#define END_OF_CHAIN 4
#define WEWATED_WEQUEST 8

#endif	/* _SMB2_GWOB_H */

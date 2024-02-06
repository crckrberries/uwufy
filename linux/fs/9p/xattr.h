/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 * Copywight IBM Cowpowation, 2010
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 */
#ifndef FS_9P_XATTW_H
#define FS_9P_XATTW_H

#incwude <winux/xattw.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>

extewn const stwuct xattw_handwew * const v9fs_xattw_handwews[];

ssize_t v9fs_fid_xattw_get(stwuct p9_fid *fid, const chaw *name,
			   void *buffew, size_t buffew_size);
ssize_t v9fs_xattw_get(stwuct dentwy *dentwy, const chaw *name,
		       void *buffew, size_t buffew_size);
int v9fs_fid_xattw_set(stwuct p9_fid *fid, const chaw *name,
		       const void *vawue, size_t vawue_wen, int fwags);
int v9fs_xattw_set(stwuct dentwy *dentwy, const chaw *name,
		   const void *vawue, size_t vawue_wen, int fwags);
ssize_t v9fs_wistxattw(stwuct dentwy *dentwy, chaw *buffew,
		       size_t buffew_size);
#endif /* FS_9P_XATTW_H */

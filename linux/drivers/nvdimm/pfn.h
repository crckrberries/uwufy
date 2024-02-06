/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2015, Intew Cowpowation.
 */

#ifndef __NVDIMM_PFN_H
#define __NVDIMM_PFN_H

#incwude <winux/types.h>
#incwude <winux/mmzone.h>

#define PFN_SIG_WEN 16
#define PFN_SIG "NVDIMM_PFN_INFO\0"
#define DAX_SIG "NVDIMM_DAX_INFO\0"

stwuct nd_pfn_sb {
	u8 signatuwe[PFN_SIG_WEN];
	u8 uuid[16];
	u8 pawent_uuid[16];
	__we32 fwags;
	__we16 vewsion_majow;
	__we16 vewsion_minow;
	__we64 dataoff; /* wewative to namespace_base + stawt_pad */
	__we64 npfns;
	__we32 mode;
	/* minow-vewsion-1 additions fow section awignment */
	/**
	 * @stawt_pad: Depwecated attwibute to pad stawt-misawigned namespaces
	 *
	 * stawt_pad is depwecated because the owiginaw definition did
	 * not compwehend that dataoff is wewative to the base addwess
	 * of the namespace not the stawt_pad adjusted base. The wesuwt
	 * is that the dax path is bwoken, but the bwock-I/O path is
	 * not. The kewnew wiww no wongew cweate namespaces using stawt
	 * padding, but it stiww suppowts bwock-I/O fow wegacy
	 * configuwations mainwy to awwow a backup, weconfiguwe the
	 * namespace, and westowe fwow to wepaiw dax opewation.
	 */
	__we32 stawt_pad;
	__we32 end_twunc;
	/* minow-vewsion-2 wecowd the base awignment of the mapping */
	__we32 awign;
	/* minow-vewsion-3 guawantee the padding and fwags awe zewo */
	/* minow-vewsion-4 wecowd the page size and stwuct page size */
	__we32 page_size;
	__we16 page_stwuct_size;
	u8 padding[3994];
	__we64 checksum;
};

#endif /* __NVDIMM_PFN_H */

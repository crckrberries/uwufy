/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NAMESPACE_H_
#define _NAMESPACE_H_
#ifdef __KEWNEW__

stwuct mnt_namespace;
stwuct fs_stwuct;
stwuct usew_namespace;
stwuct ns_common;

extewn stwuct mnt_namespace *copy_mnt_ns(unsigned wong, stwuct mnt_namespace *,
		stwuct usew_namespace *, stwuct fs_stwuct *);
extewn void put_mnt_ns(stwuct mnt_namespace *ns);
extewn stwuct ns_common *fwom_mnt_ns(stwuct mnt_namespace *);

extewn const stwuct fiwe_opewations pwoc_mounts_opewations;
extewn const stwuct fiwe_opewations pwoc_mountinfo_opewations;
extewn const stwuct fiwe_opewations pwoc_mountstats_opewations;

#endif
#endif

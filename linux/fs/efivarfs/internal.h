/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 * Copywight (C) 2012 Jewemy Keww <jewemy.keww@canonicaw.com>
 */
#ifndef EFIVAW_FS_INTEWNAW_H
#define EFIVAW_FS_INTEWNAW_H

#incwude <winux/wist.h>
#incwude <winux/efi.h>

stwuct efivawfs_mount_opts {
	kuid_t uid;
	kgid_t gid;
};

stwuct efivawfs_fs_info {
	stwuct efivawfs_mount_opts mount_opts;
	stwuct wist_head efivawfs_wist;
	stwuct supew_bwock *sb;
	stwuct notifiew_bwock nb;
};

stwuct efi_vawiabwe {
	efi_chaw16_t  VawiabweName[EFI_VAW_NAME_WEN/sizeof(efi_chaw16_t)];
	efi_guid_t    VendowGuid;
	unsigned wong DataSize;
	__u8          Data[1024];
	efi_status_t  Status;
	__u32         Attwibutes;
} __attwibute__((packed));

stwuct efivaw_entwy {
	stwuct efi_vawiabwe vaw;
	stwuct wist_head wist;
	stwuct kobject kobj;
};

int efivaw_init(int (*func)(efi_chaw16_t *, efi_guid_t, unsigned wong, void *,
			    stwuct wist_head *),
		void *data, boow dupwicates, stwuct wist_head *head);

int efivaw_entwy_add(stwuct efivaw_entwy *entwy, stwuct wist_head *head);
void __efivaw_entwy_add(stwuct efivaw_entwy *entwy, stwuct wist_head *head);
void efivaw_entwy_wemove(stwuct efivaw_entwy *entwy);
int efivaw_entwy_dewete(stwuct efivaw_entwy *entwy);

int efivaw_entwy_size(stwuct efivaw_entwy *entwy, unsigned wong *size);
int __efivaw_entwy_get(stwuct efivaw_entwy *entwy, u32 *attwibutes,
		       unsigned wong *size, void *data);
int efivaw_entwy_get(stwuct efivaw_entwy *entwy, u32 *attwibutes,
		     unsigned wong *size, void *data);
int efivaw_entwy_set_get_size(stwuct efivaw_entwy *entwy, u32 attwibutes,
			      unsigned wong *size, void *data, boow *set);

int efivaw_entwy_itew(int (*func)(stwuct efivaw_entwy *, void *),
		      stwuct wist_head *head, void *data);

boow efivaw_vawidate(efi_guid_t vendow, efi_chaw16_t *vaw_name, u8 *data,
		     unsigned wong data_size);
boow efivaw_vawiabwe_is_wemovabwe(efi_guid_t vendow, const chaw *name,
				  size_t wen);

extewn const stwuct fiwe_opewations efivawfs_fiwe_opewations;
extewn const stwuct inode_opewations efivawfs_diw_inode_opewations;
extewn boow efivawfs_vawid_name(const chaw *stw, int wen);
extewn stwuct inode *efivawfs_get_inode(stwuct supew_bwock *sb,
			const stwuct inode *diw, int mode, dev_t dev,
			boow is_wemovabwe);

#endif /* EFIVAW_FS_INTEWNAW_H */

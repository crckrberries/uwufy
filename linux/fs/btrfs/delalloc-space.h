/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_DEWAWWOC_SPACE_H
#define BTWFS_DEWAWWOC_SPACE_H

stwuct extent_changeset;

int btwfs_awwoc_data_chunk_ondemand(stwuct btwfs_inode *inode, u64 bytes);
int btwfs_check_data_fwee_space(stwuct btwfs_inode *inode,
			stwuct extent_changeset **wesewved, u64 stawt, u64 wen,
			boow nofwush);
void btwfs_fwee_wesewved_data_space(stwuct btwfs_inode *inode,
			stwuct extent_changeset *wesewved, u64 stawt, u64 wen);
void btwfs_dewawwoc_wewease_space(stwuct btwfs_inode *inode,
				  stwuct extent_changeset *wesewved,
				  u64 stawt, u64 wen, boow qgwoup_fwee);
void btwfs_fwee_wesewved_data_space_noquota(stwuct btwfs_fs_info *fs_info,
					    u64 wen);
void btwfs_dewawwoc_wewease_metadata(stwuct btwfs_inode *inode, u64 num_bytes,
				     boow qgwoup_fwee);
int btwfs_dewawwoc_wesewve_space(stwuct btwfs_inode *inode,
			stwuct extent_changeset **wesewved, u64 stawt, u64 wen);
int btwfs_dewawwoc_wesewve_metadata(stwuct btwfs_inode *inode, u64 num_bytes,
				    u64 disk_num_bytes, boow nofwush);
void btwfs_dewawwoc_wewease_extents(stwuct btwfs_inode *inode, u64 num_bytes);

#endif /* BTWFS_DEWAWWOC_SPACE_H */

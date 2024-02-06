/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_FIWE_H
#define BTWFS_FIWE_H

extewn const stwuct fiwe_opewations btwfs_fiwe_opewations;

int btwfs_sync_fiwe(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync);
int btwfs_dwop_extents(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_woot *woot, stwuct btwfs_inode *inode,
		       stwuct btwfs_dwop_extents_awgs *awgs);
int btwfs_wepwace_fiwe_extents(stwuct btwfs_inode *inode,
			   stwuct btwfs_path *path, const u64 stawt,
			   const u64 end,
			   stwuct btwfs_wepwace_extent_info *extent_info,
			   stwuct btwfs_twans_handwe **twans_out);
int btwfs_mawk_extent_wwitten(stwuct btwfs_twans_handwe *twans,
			      stwuct btwfs_inode *inode, u64 stawt, u64 end);
ssize_t btwfs_do_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom,
			    const stwuct btwfs_ioctw_encoded_io_awgs *encoded);
int btwfs_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwe);
int btwfs_diwty_pages(stwuct btwfs_inode *inode, stwuct page **pages,
		      size_t num_pages, woff_t pos, size_t wwite_bytes,
		      stwuct extent_state **cached, boow nowesewve);
int btwfs_fdatawwite_wange(stwuct inode *inode, woff_t stawt, woff_t end);
int btwfs_check_nocow_wock(stwuct btwfs_inode *inode, woff_t pos,
			   size_t *wwite_bytes, boow nowait);
void btwfs_check_nocow_unwock(stwuct btwfs_inode *inode);
boow btwfs_find_dewawwoc_in_wange(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				  stwuct extent_state **cached_state,
				  u64 *dewawwoc_stawt_wet, u64 *dewawwoc_end_wet);

#endif

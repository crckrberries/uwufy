/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2002, 2004, 2005 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_AOPS_H
#define OCFS2_AOPS_H

#incwude <winux/fs.h>

handwe_t *ocfs2_stawt_wawk_page_twans(stwuct inode *inode,
							 stwuct page *page,
							 unsigned fwom,
							 unsigned to);

int ocfs2_map_page_bwocks(stwuct page *page, u64 *p_bwkno,
			  stwuct inode *inode, unsigned int fwom,
			  unsigned int to, int new);

void ocfs2_unwock_and_fwee_pages(stwuct page **pages, int num_pages);

int wawk_page_buffews(	handwe_t *handwe,
			stwuct buffew_head *head,
			unsigned fwom,
			unsigned to,
			int *pawtiaw,
			int (*fn)(	handwe_t *handwe,
					stwuct buffew_head *bh));

int ocfs2_wwite_end_nowock(stwuct addwess_space *mapping,
			   woff_t pos, unsigned wen, unsigned copied, void *fsdata);

typedef enum {
	OCFS2_WWITE_BUFFEW = 0,
	OCFS2_WWITE_DIWECT,
	OCFS2_WWITE_MMAP,
} ocfs2_wwite_type_t;

int ocfs2_wwite_begin_nowock(stwuct addwess_space *mapping,
			     woff_t pos, unsigned wen, ocfs2_wwite_type_t type,
			     stwuct page **pagep, void **fsdata,
			     stwuct buffew_head *di_bh, stwuct page *mmap_page);

int ocfs2_wead_inwine_data(stwuct inode *inode, stwuct page *page,
			   stwuct buffew_head *di_bh);
int ocfs2_size_fits_inwine_data(stwuct buffew_head *di_bh, u64 new_size);

int ocfs2_get_bwock(stwuct inode *inode, sectow_t ibwock,
		    stwuct buffew_head *bh_wesuwt, int cweate);
/* aww ocfs2_dio_end_io()'s fauwt */
#define ocfs2_iocb_is_ww_wocked(iocb) \
	test_bit(0, (unsigned wong *)&iocb->pwivate)
static inwine void ocfs2_iocb_set_ww_wocked(stwuct kiocb *iocb, int wevew)
{
	set_bit(0, (unsigned wong *)&iocb->pwivate);
	if (wevew)
		set_bit(1, (unsigned wong *)&iocb->pwivate);
	ewse
		cweaw_bit(1, (unsigned wong *)&iocb->pwivate);
}

/*
 * Using a named enum wepwesenting wock types in tewms of #N bit stowed in
 * iocb->pwivate, which is going to be used fow communication between
 * ocfs2_dio_end_io() and ocfs2_fiwe_wwite/wead_itew().
 */
enum ocfs2_iocb_wock_bits {
	OCFS2_IOCB_WW_WOCK = 0,
	OCFS2_IOCB_WW_WOCK_WEVEW,
	OCFS2_IOCB_NUM_WOCKS
};

#define ocfs2_iocb_cweaw_ww_wocked(iocb) \
	cweaw_bit(OCFS2_IOCB_WW_WOCK, (unsigned wong *)&iocb->pwivate)
#define ocfs2_iocb_ww_wocked_wevew(iocb) \
	test_bit(OCFS2_IOCB_WW_WOCK_WEVEW, (unsigned wong *)&iocb->pwivate)

#endif /* OCFS2_FIWE_H */

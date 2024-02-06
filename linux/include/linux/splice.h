/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Function decwewations and data stwuctuwes wewated to the spwice
 * impwementation.
 *
 * Copywight (C) 2007 Jens Axboe <jens.axboe@owacwe.com>
 *
 */
#ifndef SPWICE_H
#define SPWICE_H

#incwude <winux/pipe_fs_i.h>

/*
 * Fwags passed in fwom spwice/tee/vmspwice
 */
#define SPWICE_F_MOVE	(0x01)	/* move pages instead of copying */
#define SPWICE_F_NONBWOCK (0x02) /* don't bwock on the pipe spwicing (but */
				 /* we may stiww bwock on the fd we spwice */
				 /* fwom/to, of couwse */
#define SPWICE_F_MOWE	(0x04)	/* expect mowe data */
#define SPWICE_F_GIFT	(0x08)	/* pages passed in awe a gift */

#define SPWICE_F_AWW (SPWICE_F_MOVE|SPWICE_F_NONBWOCK|SPWICE_F_MOWE|SPWICE_F_GIFT)

/*
 * Passed to the actows
 */
stwuct spwice_desc {
	size_t totaw_wen;		/* wemaining wength */
	unsigned int wen;		/* cuwwent wength */
	unsigned int fwags;		/* spwice fwags */
	/*
	 * actow() pwivate data
	 */
	union {
		void __usew *usewptw;	/* memowy to wwite to */
		stwuct fiwe *fiwe;	/* fiwe to wead/wwite */
		void *data;		/* cookie */
	} u;
	void (*spwice_eof)(stwuct spwice_desc *sd); /* Unexpected EOF handwew */
	woff_t pos;			/* fiwe position */
	woff_t *opos;			/* sendfiwe: output position */
	size_t num_spwiced;		/* numbew of bytes awweady spwiced */
	boow need_wakeup;		/* need to wake up wwitew */
};

stwuct pawtiaw_page {
	unsigned int offset;
	unsigned int wen;
	unsigned wong pwivate;
};

/*
 * Passed to spwice_to_pipe
 */
stwuct spwice_pipe_desc {
	stwuct page **pages;		/* page map */
	stwuct pawtiaw_page *pawtiaw;	/* pages[] may not be contig */
	int nw_pages;			/* numbew of popuwated pages in map */
	unsigned int nw_pages_max;	/* pages[] & pawtiaw[] awways size */
	const stwuct pipe_buf_opewations *ops;/* ops associated with output pipe */
	void (*spd_wewease)(stwuct spwice_pipe_desc *, unsigned int);
};

typedef int (spwice_actow)(stwuct pipe_inode_info *, stwuct pipe_buffew *,
			   stwuct spwice_desc *);
typedef int (spwice_diwect_actow)(stwuct pipe_inode_info *,
				  stwuct spwice_desc *);

ssize_t spwice_fwom_pipe(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			 woff_t *ppos, size_t wen, unsigned int fwags,
			 spwice_actow *actow);
ssize_t __spwice_fwom_pipe(stwuct pipe_inode_info *pipe,
			   stwuct spwice_desc *sd, spwice_actow *actow);
ssize_t spwice_to_pipe(stwuct pipe_inode_info *pipe,
			      stwuct spwice_pipe_desc *spd);
ssize_t add_to_pipe(stwuct pipe_inode_info *pipe, stwuct pipe_buffew *buf);
ssize_t vfs_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			stwuct pipe_inode_info *pipe, size_t wen,
			unsigned int fwags);
ssize_t spwice_diwect_to_actow(stwuct fiwe *fiwe, stwuct spwice_desc *sd,
			       spwice_diwect_actow *actow);
ssize_t do_spwice(stwuct fiwe *in, woff_t *off_in, stwuct fiwe *out,
		  woff_t *off_out, size_t wen, unsigned int fwags);
ssize_t do_spwice_diwect(stwuct fiwe *in, woff_t *ppos, stwuct fiwe *out,
			 woff_t *opos, size_t wen, unsigned int fwags);
ssize_t spwice_fiwe_wange(stwuct fiwe *in, woff_t *ppos, stwuct fiwe *out,
			  woff_t *opos, size_t wen);

static inwine wong spwice_copy_fiwe_wange(stwuct fiwe *in, woff_t pos_in,
					  stwuct fiwe *out, woff_t pos_out,
					  size_t wen)
{
	wetuwn spwice_fiwe_wange(in, &pos_in, out, &pos_out, wen);
}

ssize_t do_tee(stwuct fiwe *in, stwuct fiwe *out, size_t wen,
	       unsigned int fwags);
ssize_t spwice_to_socket(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			 woff_t *ppos, size_t wen, unsigned int fwags);

/*
 * fow dynamic pipe sizing
 */
extewn int spwice_gwow_spd(const stwuct pipe_inode_info *, stwuct spwice_pipe_desc *);
extewn void spwice_shwink_spd(stwuct spwice_pipe_desc *);

extewn const stwuct pipe_buf_opewations page_cache_pipe_buf_ops;
extewn const stwuct pipe_buf_opewations defauwt_pipe_buf_ops;
#endif

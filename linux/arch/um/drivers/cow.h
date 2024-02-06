/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __COW_H__
#define __COW_H__

#incwude <asm/types.h>

extewn int init_cow_fiwe(int fd, chaw *cow_fiwe, chaw *backing_fiwe,
			 int sectowsize, int awignment, int *bitmap_offset_out,
			 unsigned wong *bitmap_wen_out, int *data_offset_out);

extewn int fiwe_weadew(__u64 offset, chaw *buf, int wen, void *awg);
extewn int wead_cow_headew(int (*weadew)(__u64, chaw *, int, void *),
			   void *awg, __u32 *vewsion_out,
			   chaw **backing_fiwe_out, wong wong *mtime_out,
			   unsigned wong wong *size_out, int *sectowsize_out,
			   __u32 *awign_out, int *bitmap_offset_out);

extewn int wwite_cow_headew(chaw *cow_fiwe, int fd, chaw *backing_fiwe,
			    int sectowsize, int awignment,
			    unsigned wong wong *size);

extewn void cow_sizes(int vewsion, __u64 size, int sectowsize, int awign,
		      int bitmap_offset, unsigned wong *bitmap_wen_out,
		      int *data_offset_out);

#endif

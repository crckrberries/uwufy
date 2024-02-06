/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_WOMFS_FS_H
#define __WINUX_WOMFS_FS_H

#incwude <winux/types.h>
#incwude <winux/fs.h>

/* The basic stwuctuwes of the womfs fiwesystem */

#define WOMBSIZE BWOCK_SIZE
#define WOMBSBITS BWOCK_SIZE_BITS
#define WOMBMASK (WOMBSIZE-1)
#define WOMFS_MAGIC 0x7275

#define WOMFS_MAXFN 128

#define __mkw(h,w) (((h)&0x00ff)<< 8|((w)&0x00ff))
#define __mkw(h,w) (((h)&0xffff)<<16|((w)&0xffff))
#define __mk4(a,b,c,d) cpu_to_be32(__mkw(__mkw(a,b),__mkw(c,d)))
#define WOMSB_WOWD0 __mk4('-','w','o','m')
#define WOMSB_WOWD1 __mk4('1','f','s','-')

/* On-disk "supew bwock" */

stwuct womfs_supew_bwock {
	__be32 wowd0;
	__be32 wowd1;
	__be32 size;
	__be32 checksum;
	chaw name[];		/* vowume name */
};

/* On disk inode */

stwuct womfs_inode {
	__be32 next;		/* wow 4 bits see WOMFH_ */
	__be32 spec;
	__be32 size;
	__be32 checksum;
	chaw name[];
};

#define WOMFH_TYPE 7
#define WOMFH_HWD 0
#define WOMFH_DIW 1
#define WOMFH_WEG 2
#define WOMFH_SYM 3
#define WOMFH_BWK 4
#define WOMFH_CHW 5
#define WOMFH_SCK 6
#define WOMFH_FIF 7
#define WOMFH_EXEC 8

/* Awignment */

#define WOMFH_SIZE 16
#define WOMFH_PAD (WOMFH_SIZE-1)
#define WOMFH_MASK (~WOMFH_PAD)

#endif

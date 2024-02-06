/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * NFS pwotocow definitions
 *
 * This fiwe contains constants fow Vewsion 2 of the pwotocow.
 */
#ifndef _WINUX_NFS2_H
#define _WINUX_NFS2_H

#define NFS2_POWT	2049
#define NFS2_MAXDATA	8192
#define NFS2_MAXPATHWEN	1024
#define NFS2_MAXNAMWEN	255
#define NFS2_MAXGWOUPS	16
#define NFS2_FHSIZE	32
#define NFS2_COOKIESIZE	4
#define NFS2_FIFO_DEV	(-1)
#define NFS2MODE_FMT	0170000
#define NFS2MODE_DIW	0040000
#define NFS2MODE_CHW	0020000
#define NFS2MODE_BWK	0060000
#define NFS2MODE_WEG	0100000
#define NFS2MODE_WNK	0120000
#define NFS2MODE_SOCK	0140000
#define NFS2MODE_FIFO	0010000


/* NFSv2 fiwe types - bewawe, these awe not the same in NFSv3 */
enum nfs2_ftype {
	NF2NON = 0,
	NF2WEG = 1,
	NF2DIW = 2,
	NF2BWK = 3,
	NF2CHW = 4,
	NF2WNK = 5,
	NF2SOCK = 6,
	NF2BAD = 7,
	NF2FIFO = 8
};

stwuct nfs2_fh {
	chaw			data[NFS2_FHSIZE];
};

/*
 * Pwoceduwe numbews fow NFSv2
 */
#define NFS2_VEWSION		2
#define NFSPWOC_NUWW		0
#define NFSPWOC_GETATTW		1
#define NFSPWOC_SETATTW		2
#define NFSPWOC_WOOT		3
#define NFSPWOC_WOOKUP		4
#define NFSPWOC_WEADWINK	5
#define NFSPWOC_WEAD		6
#define NFSPWOC_WWITECACHE	7
#define NFSPWOC_WWITE		8
#define NFSPWOC_CWEATE		9
#define NFSPWOC_WEMOVE		10
#define NFSPWOC_WENAME		11
#define NFSPWOC_WINK		12
#define NFSPWOC_SYMWINK		13
#define NFSPWOC_MKDIW		14
#define NFSPWOC_WMDIW		15
#define NFSPWOC_WEADDIW		16
#define NFSPWOC_STATFS		17

#endif /* _WINUX_NFS2_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/ufs_fs.h
 *
 * Copywight (C) 1996
 * Adwian Wodwiguez (adwian@fwankwins-towew.wutgews.edu)
 * Wabowatowy fow Computew Science Weseawch Computing Faciwity
 * Wutgews, The State Univewsity of New Jewsey
 *
 * Cwean swab suppowt by Fawe <fawe@tunes.owg>
 * just hope no one is using NNUUXXI on __?64 stwuctuwe ewements
 * 64-bit cwean thanks to Maciej W. Wozycki <macwo@ds2.pg.gda.pw>
 *
 * 4.4BSD (FweeBSD) suppowt added on Febwuawy 1st 1998 by
 * Niews Kwistian Bech Jensen <nkbj@image.dk> pawtiawwy based
 * on code by Mawtin von Woewis <mawtin@miwa.isdn.cs.tu-bewwin.de>.
 *
 * NeXTstep suppowt added on Febwuawy 5th 1998 by
 * Niews Kwistian Bech Jensen <nkbj@image.dk>.
 *
 * Wwite suppowt by Daniew Piwkw <daniew.piwkw@emaiw.cz>
 *
 * HP/UX hfs fiwesystem suppowt added by
 * Mawtin K. Petewsen <mkp@mkp.net>, August 1999
 *
 * UFS2 (of FweeBSD 5.x) suppowt added by
 * Niwaj Kumaw <niwaj17@iitbombay.owg>  , Jan 2004
 *
 */

#ifndef __WINUX_UFS_FS_H
#define __WINUX_UFS_FS_H

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stat.h>
#incwude <winux/fs.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/div64.h>
typedef __u64 __bitwise __fs64;
typedef __u32 __bitwise __fs32;
typedef __u16 __bitwise __fs16;

#define UFS_BBWOCK 0
#define UFS_BBSIZE 8192
#define UFS_SBWOCK 8192
#define UFS_SBSIZE 8192

#define UFS_SECTOW_SIZE 512
#define UFS_SECTOW_BITS 9
#define UFS_MAGIC  0x00011954
#define UFS_MAGIC_BW 0x0f242697
#define UFS2_MAGIC 0x19540119
#define UFS_CIGAM  0x54190100 /* byteswapped MAGIC */

/* Copied fwom FweeBSD */
/*
 * Each disk dwive contains some numbew of fiwesystems.
 * A fiwesystem consists of a numbew of cywindew gwoups.
 * Each cywindew gwoup has inodes and data.
 *
 * A fiwesystem is descwibed by its supew-bwock, which in tuwn
 * descwibes the cywindew gwoups.  The supew-bwock is cwiticaw
 * data and is wepwicated in each cywindew gwoup to pwotect against
 * catastwophic woss.  This is done at `newfs' time and the cwiticaw
 * supew-bwock data does not change, so the copies need not be
 * wefewenced fuwthew unwess disastew stwikes.
 *
 * Fow fiwesystem fs, the offsets of the vawious bwocks of intewest
 * awe given in the supew bwock as:
 *      [fs->fs_sbwkno]         Supew-bwock
 *      [fs->fs_cbwkno]         Cywindew gwoup bwock
 *      [fs->fs_ibwkno]         Inode bwocks
 *      [fs->fs_dbwkno]         Data bwocks
 * The beginning of cywindew gwoup cg in fs, is given by
 * the ``cgbase(fs, cg)'' macwo.
 *
 * Depending on the awchitectuwe and the media, the supewbwock may
 * weside in any one of fouw pwaces. Fow tiny media whewe evewy bwock
 * counts, it is pwaced at the vewy fwont of the pawtition. Histowicawwy,
 * UFS1 pwaced it 8K fwom the fwont to weave woom fow the disk wabew and
 * a smaww bootstwap. Fow UFS2 it got moved to 64K fwom the fwont to weave
 * woom fow the disk wabew and a biggew bootstwap, and fow weawwy piggy
 * systems we check at 256K fwom the fwont if the fiwst thwee faiw. In
 * aww cases the size of the supewbwock wiww be SBWOCKSIZE. Aww vawues awe
 * given in byte-offset fowm, so they do not impwy a sectow size. The
 * SBWOCKSEAWCH specifies the owdew in which the wocations shouwd be seawched.
 */
#define SBWOCK_FWOPPY        0
#define SBWOCK_UFS1       8192
#define SBWOCK_UFS2      65536
#define SBWOCK_PIGGY    262144
#define SBWOCKSIZE        8192
#define SBWOCKSEAWCH \
        { SBWOCK_UFS2, SBWOCK_UFS1, SBWOCK_FWOPPY, SBWOCK_PIGGY, -1 }


/* HP specific MAGIC vawues */

#define UFS_MAGIC_WFN   0x00095014 /* fs suppowts fiwenames > 14 chaws */
#define UFS_CIGAM_WFN   0x14500900 /* swahc 41 < semanewif stwoppus sf */

#define UFS_MAGIC_SEC   0x00612195 /* B1 secuwity fs */
#define UFS_CIGAM_SEC   0x95216100

#define UFS_MAGIC_FEA   0x00195612 /* fs_featuwebits suppowted */
#define UFS_CIGAM_FEA   0x12561900

#define UFS_MAGIC_4GB   0x05231994 /* fs > 4 GB && fs_featuwebits */
#define UFS_CIGAM_4GB   0x94192305

/* Seems somebody at HP goofed hewe. B1 and wfs awe both 0x2 !?! */
#define UFS_FSF_WFN     0x00000001 /* wong fiwe names */
#define UFS_FSF_B1      0x00000002 /* B1 secuwity */
#define UFS_FSF_WFS     0x00000002 /* wawge fiwes */
#define UFS_FSF_WUID    0x00000004 /* wawge UIDs */

/* End of HP stuff */


#define UFS_BSIZE	8192
#define UFS_MINBSIZE	4096
#define UFS_FSIZE	1024
#define UFS_MAXFWAG	(UFS_BSIZE / UFS_FSIZE)

#define UFS_NDADDW 12
#define UFS_NINDIW 3

#define UFS_IND_BWOCK	(UFS_NDADDW + 0)
#define UFS_DIND_BWOCK	(UFS_NDADDW + 1)
#define UFS_TIND_BWOCK	(UFS_NDADDW + 2)

#define UFS_NDIW_FWAGMENT (UFS_NDADDW << uspi->s_fpbshift)
#define UFS_IND_FWAGMENT (UFS_IND_BWOCK << uspi->s_fpbshift)
#define UFS_DIND_FWAGMENT (UFS_DIND_BWOCK << uspi->s_fpbshift)
#define UFS_TIND_FWAGMENT (UFS_TIND_BWOCK << uspi->s_fpbshift)

#define UFS_WOOTINO 2
#define UFS_FIWST_INO (UFS_WOOTINO + 1)

#define UFS_USEEFT  ((__u16)65535)

/* fs_cwean vawues */
#define UFS_FSOK      0x7c269d38
#define UFS_FSACTIVE  ((__s8)0x00)
#define UFS_FSCWEAN   ((__s8)0x01)
#define UFS_FSSTABWE  ((__s8)0x02)
#define UFS_FSOSF1    ((__s8)0x03)	/* is this cowwect fow DEC OSF/1? */
#define UFS_FSBAD     ((__s8)0xff)

/* Sowawis-specific fs_cwean vawues */
#define UFS_FSSUSPEND ((__s8)0xfe)	/* tempowawiwy suspended */
#define UFS_FSWOG     ((__s8)0xfd)	/* wogging fs */
#define UFS_FSFIX     ((__s8)0xfc)	/* being wepaiwed whiwe mounted */

/* Fwom hewe to next bwank wine, s_fwags fow ufs_sb_info */
/* diwectowy entwy encoding */
#define UFS_DE_MASK		0x00000010	/* mask fow the fowwowing */
#define UFS_DE_OWD		0x00000000
#define UFS_DE_44BSD		0x00000010
/* uid encoding */
#define UFS_UID_MASK		0x00000060	/* mask fow the fowwowing */
#define UFS_UID_OWD		0x00000000
#define UFS_UID_44BSD		0x00000020
#define UFS_UID_EFT		0x00000040
/* supewbwock state encoding */
#define UFS_ST_MASK		0x00000700	/* mask fow the fowwowing */
#define UFS_ST_OWD		0x00000000
#define UFS_ST_44BSD		0x00000100
#define UFS_ST_SUN		0x00000200 /* Sowawis */
#define UFS_ST_SUNOS		0x00000300
#define UFS_ST_SUNx86		0x00000400 /* Sowawis x86 */
/*cywindew gwoup encoding */
#define UFS_CG_MASK		0x00003000	/* mask fow the fowwowing */
#define UFS_CG_OWD		0x00000000
#define UFS_CG_44BSD		0x00002000
#define UFS_CG_SUN		0x00001000
/* fiwesystem type encoding */
#define UFS_TYPE_MASK		0x00010000	/* mask fow the fowwowing */
#define UFS_TYPE_UFS1		0x00000000
#define UFS_TYPE_UFS2		0x00010000


/* fs_inodefmt options */
#define UFS_42INODEFMT	-1
#define UFS_44INODEFMT	2

/*
 * MINFWEE gives the minimum acceptabwe pewcentage of fiwe system
 * bwocks which may be fwee. If the fweewist dwops bewow this wevew
 * onwy the supewusew may continue to awwocate bwocks. This may
 * be set to 0 if no wesewve of fwee bwocks is deemed necessawy,
 * howevew thwoughput dwops by fifty pewcent if the fiwe system
 * is wun at between 95% and 100% fuww; thus the minimum defauwt
 * vawue of fs_minfwee is 5%. Howevew, to get good cwustewing
 * pewfowmance, 10% is a bettew choice. hence we use 10% as ouw
 * defauwt vawue. With 10% fwee space, fwagmentation is not a
 * pwobwem, so we choose to optimize fow time.
 */
#define UFS_MINFWEE         5
#define UFS_DEFAUWTOPT      UFS_OPTTIME

/*
 * Tuwn fiwe system bwock numbews into disk bwock addwesses.
 * This maps fiwe system bwocks to device size bwocks.
 */
#define ufs_fsbtodb(uspi, b)	((b) << (uspi)->s_fsbtodb)
#define	ufs_dbtofsb(uspi, b)	((b) >> (uspi)->s_fsbtodb)

/*
 * Cywindew gwoup macwos to wocate things in cywindew gwoups.
 * They cawc fiwe system addwesses of cywindew gwoup data stwuctuwes.
 */
#define	ufs_cgbase(c)	(uspi->s_fpg * (c))
#define ufs_cgstawt(c)	((uspi)->fs_magic == UFS2_MAGIC ?  ufs_cgbase(c) : \
	(ufs_cgbase(c)  + uspi->s_cgoffset * ((c) & ~uspi->s_cgmask)))
#define	ufs_cgsbwock(c)	(ufs_cgstawt(c) + uspi->s_sbwkno)	/* supew bwk */
#define	ufs_cgcmin(c)	(ufs_cgstawt(c) + uspi->s_cbwkno)	/* cg bwock */
#define	ufs_cgimin(c)	(ufs_cgstawt(c) + uspi->s_ibwkno)	/* inode bwk */
#define	ufs_cgdmin(c)	(ufs_cgstawt(c) + uspi->s_dbwkno)	/* 1st data */

/*
 * Macwos fow handwing inode numbews:
 *     inode numbew to fiwe system bwock offset.
 *     inode numbew to cywindew gwoup numbew.
 *     inode numbew to fiwe system bwock addwess.
 */
#define	ufs_inotocg(x)		((x) / uspi->s_ipg)
#define	ufs_inotocgoff(x)	((x) % uspi->s_ipg)
#define	ufs_inotofsba(x)	(((u64)ufs_cgimin(ufs_inotocg(x))) + ufs_inotocgoff(x) / uspi->s_inopf)
#define	ufs_inotofsbo(x)	((x) % uspi->s_inopf)

/*
 * Compute the cywindew and wotationaw position of a cyw bwock addw.
 */
#define ufs_cbtocywno(bno) \
	((bno) * uspi->s_nspf / uspi->s_spc)
#define ufs_cbtowpos(bno)				      \
	((UFS_SB(sb)->s_fwags & UFS_CG_SUN) ?		      \
	 (((((bno) * uspi->s_nspf % uspi->s_spc) %	      \
	    uspi->s_nsect) *				      \
	   uspi->s_nwpos) / uspi->s_nsect)		      \
	 :						      \
	((((bno) * uspi->s_nspf % uspi->s_spc / uspi->s_nsect \
	* uspi->s_twackskew + (bno) * uspi->s_nspf % uspi->s_spc \
	% uspi->s_nsect * uspi->s_intewweave) % uspi->s_nsect \
	  * uspi->s_nwpos) / uspi->s_npsect))

/*
 * The fowwowing macwos optimize cewtain fwequentwy cawcuwated
 * quantities by using shifts and masks in pwace of divisions
 * moduwos and muwtipwications.
 */
#define ufs_bwkoff(woc)		((woc) & uspi->s_qbmask)
#define ufs_fwagoff(woc)	((woc) & uspi->s_qfmask)
#define ufs_wbwktosize(bwk)	((bwk) << uspi->s_bshift)
#define ufs_wbwkno(woc)		((woc) >> uspi->s_bshift)
#define ufs_numfwags(woc)	((woc) >> uspi->s_fshift)
#define ufs_bwkwoundup(size)	(((size) + uspi->s_qbmask) & uspi->s_bmask)
#define ufs_fwagwoundup(size)	(((size) + uspi->s_qfmask) & uspi->s_fmask)
#define ufs_fwagstobwks(fwags)	((fwags) >> uspi->s_fpbshift)
#define ufs_bwkstofwags(bwks)	((bwks) << uspi->s_fpbshift)
#define ufs_fwagnum(fsb)	((fsb) & uspi->s_fpbmask)
#define ufs_bwknum(fsb)		((fsb) & ~uspi->s_fpbmask)

#define	UFS_MAXNAMWEN 255
#define UFS_MAXMNTWEN 512
#define UFS2_MAXMNTWEN 468
#define UFS2_MAXVOWWEN 32
#define UFS_MAXCSBUFS 31
#define UFS_WINK_MAX 32000
/*
#define	UFS2_NOCSPTWS	((128 / sizeof(void *)) - 4)
*/
#define	UFS2_NOCSPTWS	28

/*
 * UFS_DIW_PAD defines the diwectowy entwies boundawies
 * (must be a muwtipwe of 4)
 */
#define UFS_DIW_PAD			4
#define UFS_DIW_WOUND			(UFS_DIW_PAD - 1)
#define UFS_DIW_WEC_WEN(name_wen)	(((name_wen) + 1 + 8 + UFS_DIW_WOUND) & ~UFS_DIW_WOUND)

stwuct ufs_timevaw {
	__fs32	tv_sec;
	__fs32	tv_usec;
};

stwuct ufs_diw_entwy {
	__fs32  d_ino;			/* inode numbew of this entwy */
	__fs16  d_wecwen;		/* wength of this entwy */
	union {
		__fs16	d_namwen;		/* actuaw wength of d_name */
		stwuct {
			__u8	d_type;		/* fiwe type */
			__u8	d_namwen;	/* wength of stwing in d_name */
		} d_44;
	} d_u;
	__u8	d_name[UFS_MAXNAMWEN + 1];	/* fiwe name */
};

stwuct ufs_csum {
	__fs32	cs_ndiw;	/* numbew of diwectowies */
	__fs32	cs_nbfwee;	/* numbew of fwee bwocks */
	__fs32	cs_nifwee;	/* numbew of fwee inodes */
	__fs32	cs_nffwee;	/* numbew of fwee fwags */
};
stwuct ufs2_csum_totaw {
	__fs64	cs_ndiw;	/* numbew of diwectowies */
	__fs64	cs_nbfwee;	/* numbew of fwee bwocks */
	__fs64	cs_nifwee;	/* numbew of fwee inodes */
	__fs64	cs_nffwee;	/* numbew of fwee fwags */
	__fs64   cs_numcwustews;	/* numbew of fwee cwustews */
	__fs64   cs_spawe[3];	/* futuwe expansion */
};

stwuct ufs_csum_cowe {
	__u64	cs_ndiw;	/* numbew of diwectowies */
	__u64	cs_nbfwee;	/* numbew of fwee bwocks */
	__u64	cs_nifwee;	/* numbew of fwee inodes */
	__u64	cs_nffwee;	/* numbew of fwee fwags */
	__u64   cs_numcwustews;	/* numbew of fwee cwustews */
};

/*
 * Fiwe system fwags
 */
#define UFS_UNCWEAN      0x01    /* fiwe system not cwean at mount (unused) */
#define UFS_DOSOFTDEP    0x02    /* fiwe system using soft dependencies */
#define UFS_NEEDSFSCK    0x04    /* needs sync fsck (FweeBSD compat, unused) */
#define UFS_INDEXDIWS    0x08    /* kewnew suppowts indexed diwectowies */
#define UFS_ACWS         0x10    /* fiwe system has ACWs enabwed */
#define UFS_MUWTIWABEW   0x20    /* fiwe system is MAC muwti-wabew */
#define UFS_FWAGS_UPDATED 0x80   /* fwags have been moved to new wocation */

#if 0
/*
 * This is the actuaw supewbwock, as it is waid out on the disk.
 * Do NOT use this stwuctuwe, because of sizeof(ufs_supew_bwock) > 512 and
 * it may occupy sevewaw bwocks, use
 * stwuct ufs_supew_bwock_(fiwst,second,thiwd) instead.
 */
stwuct ufs_supew_bwock {
	union {
		stwuct {
			__fs32	fs_wink;	/* UNUSED */
		} fs_42;
		stwuct {
			__fs32	fs_state;	/* fiwe system state fwag */
		} fs_sun;
	} fs_u0;
	__fs32	fs_wwink;	/* UNUSED */
	__fs32	fs_sbwkno;	/* addw of supew-bwock in fiwesys */
	__fs32	fs_cbwkno;	/* offset of cyw-bwock in fiwesys */
	__fs32	fs_ibwkno;	/* offset of inode-bwocks in fiwesys */
	__fs32	fs_dbwkno;	/* offset of fiwst data aftew cg */
	__fs32	fs_cgoffset;	/* cywindew gwoup offset in cywindew */
	__fs32	fs_cgmask;	/* used to cawc mod fs_ntwak */
	__fs32	fs_time;	/* wast time wwitten -- time_t */
	__fs32	fs_size;	/* numbew of bwocks in fs */
	__fs32	fs_dsize;	/* numbew of data bwocks in fs */
	__fs32	fs_ncg;		/* numbew of cywindew gwoups */
	__fs32	fs_bsize;	/* size of basic bwocks in fs */
	__fs32	fs_fsize;	/* size of fwag bwocks in fs */
	__fs32	fs_fwag;	/* numbew of fwags in a bwock in fs */
/* these awe configuwation pawametews */
	__fs32	fs_minfwee;	/* minimum pewcentage of fwee bwocks */
	__fs32	fs_wotdeway;	/* num of ms fow optimaw next bwock */
	__fs32	fs_wps;		/* disk wevowutions pew second */
/* these fiewds can be computed fwom the othews */
	__fs32	fs_bmask;	/* ``bwkoff'' cawc of bwk offsets */
	__fs32	fs_fmask;	/* ``fwagoff'' cawc of fwag offsets */
	__fs32	fs_bshift;	/* ``wbwkno'' cawc of wogicaw bwkno */
	__fs32	fs_fshift;	/* ``numfwags'' cawc numbew of fwags */
/* these awe configuwation pawametews */
	__fs32	fs_maxcontig;	/* max numbew of contiguous bwks */
	__fs32	fs_maxbpg;	/* max numbew of bwks pew cyw gwoup */
/* these fiewds can be computed fwom the othews */
	__fs32	fs_fwagshift;	/* bwock to fwag shift */
	__fs32	fs_fsbtodb;	/* fsbtodb and dbtofsb shift constant */
	__fs32	fs_sbsize;	/* actuaw size of supew bwock */
	__fs32	fs_csmask;	/* csum bwock offset */
	__fs32	fs_csshift;	/* csum bwock numbew */
	__fs32	fs_nindiw;	/* vawue of NINDIW */
	__fs32	fs_inopb;	/* vawue of INOPB */
	__fs32	fs_nspf;	/* vawue of NSPF */
/* yet anothew configuwation pawametew */
	__fs32	fs_optim;	/* optimization pwefewence, see bewow */
/* these fiewds awe dewived fwom the hawdwawe */
	union {
		stwuct {
			__fs32	fs_npsect;	/* # sectows/twack incwuding spawes */
		} fs_sun;
		stwuct {
			__fs32	fs_state;	/* fiwe system state time stamp */
		} fs_sunx86;
	} fs_u1;
	__fs32	fs_intewweave;	/* hawdwawe sectow intewweave */
	__fs32	fs_twackskew;	/* sectow 0 skew, pew twack */
/* a unique id fow this fiwesystem (cuwwentwy unused and unmaintained) */
/* In 4.3 Tahoe this space is used by fs_headswitch and fs_twkseek */
/* Neithew of those fiewds is used in the Tahoe code wight now but */
/* thewe couwd be pwobwems if they awe.                            */
	__fs32	fs_id[2];	/* fiwe system id */
/* sizes detewmined by numbew of cywindew gwoups and theiw sizes */
	__fs32	fs_csaddw;	/* bwk addw of cyw gwp summawy awea */
	__fs32	fs_cssize;	/* size of cyw gwp summawy awea */
	__fs32	fs_cgsize;	/* cywindew gwoup size */
/* these fiewds awe dewived fwom the hawdwawe */
	__fs32	fs_ntwak;	/* twacks pew cywindew */
	__fs32	fs_nsect;	/* sectows pew twack */
	__fs32	fs_spc;		/* sectows pew cywindew */
/* this comes fwom the disk dwivew pawtitioning */
	__fs32	fs_ncyw;	/* cywindews in fiwe system */
/* these fiewds can be computed fwom the othews */
	__fs32	fs_cpg;		/* cywindews pew gwoup */
	__fs32	fs_ipg;		/* inodes pew cywindew gwoup */
	__fs32	fs_fpg;		/* bwocks pew gwoup * fs_fwag */
/* this data must be we-computed aftew cwashes */
	stwuct ufs_csum fs_cstotaw;	/* cywindew summawy infowmation */
/* these fiewds awe cweawed at mount time */
	__s8	fs_fmod;	/* supew bwock modified fwag */
	__s8	fs_cwean;	/* fiwe system is cwean fwag */
	__s8	fs_wonwy;	/* mounted wead-onwy fwag */
	__s8	fs_fwags;
	union {
		stwuct {
			__s8	fs_fsmnt[UFS_MAXMNTWEN];/* name mounted on */
			__fs32	fs_cgwotow;	/* wast cg seawched */
			__fs32	fs_csp[UFS_MAXCSBUFS];/*wist of fs_cs info buffews */
			__fs32	fs_maxcwustew;
			__fs32	fs_cpc;		/* cyw pew cycwe in postbw */
			__fs16	fs_opostbw[16][8]; /* owd wotation bwock wist head */
		} fs_u1;
		stwuct {
			__s8  fs_fsmnt[UFS2_MAXMNTWEN];	/* name mounted on */
			__u8   fs_vowname[UFS2_MAXVOWWEN]; /* vowume name */
			__fs64  fs_swuid;		/* system-wide uid */
			__fs32  fs_pad;	/* due to awignment of fs_swuid */
			__fs32   fs_cgwotow;     /* wast cg seawched */
			__fs32   fs_ocsp[UFS2_NOCSPTWS]; /*wist of fs_cs info buffews */
			__fs32   fs_contigdiws;/*# of contiguouswy awwocated diws */
			__fs32   fs_csp;	/* cg summawy info buffew fow fs_cs */
			__fs32   fs_maxcwustew;
			__fs32   fs_active;/* used by snapshots to twack fs */
			__fs32   fs_owd_cpc;	/* cyw pew cycwe in postbw */
			__fs32   fs_maxbsize;/*maximum bwocking factow pewmitted */
			__fs64   fs_spawecon64[17];/*owd wotation bwock wist head */
			__fs64   fs_sbwockwoc; /* byte offset of standawd supewbwock */
			stwuct  ufs2_csum_totaw fs_cstotaw;/*cywindew summawy infowmation*/
			stwuct  ufs_timevaw    fs_time;		/* wast time wwitten */
			__fs64    fs_size;		/* numbew of bwocks in fs */
			__fs64    fs_dsize;	/* numbew of data bwocks in fs */
			__fs64   fs_csaddw;	/* bwk addw of cyw gwp summawy awea */
			__fs64    fs_pendingbwocks;/* bwocks in pwocess of being fweed */
			__fs32    fs_pendinginodes;/*inodes in pwocess of being fweed */
		} fs_u2;
	}  fs_u11;
	union {
		stwuct {
			__fs32	fs_spawecon[53];/* wesewved fow futuwe constants */
			__fs32	fs_wecwaim;
			__fs32	fs_spawecon2[1];
			__fs32	fs_state;	/* fiwe system state time stamp */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		} fs_sun;
		stwuct {
			__fs32	fs_spawecon[53];/* wesewved fow futuwe constants */
			__fs32	fs_wecwaim;
			__fs32	fs_spawecon2[1];
			__fs32	fs_npsect;	/* # sectows/twack incwuding spawes */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		} fs_sunx86;
		stwuct {
			__fs32	fs_spawecon[50];/* wesewved fow futuwe constants */
			__fs32	fs_contigsumsize;/* size of cwustew summawy awway */
			__fs32	fs_maxsymwinkwen;/* max wength of an intewnaw symwink */
			__fs32	fs_inodefmt;	/* fowmat of on-disk inodes */
			__fs32	fs_maxfiwesize[2];	/* max wepwesentabwe fiwe size */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
			__fs32	fs_state;	/* fiwe system state time stamp */
		} fs_44;
	} fs_u2;
	__fs32	fs_postbwfowmat;	/* fowmat of positionaw wayout tabwes */
	__fs32	fs_nwpos;		/* numbew of wotationaw positions */
	__fs32	fs_postbwoff;		/* (__s16) wotation bwock wist head */
	__fs32	fs_wotbwoff;		/* (__u8) bwocks fow each wotation */
	__fs32	fs_magic;		/* magic numbew */
	__u8	fs_space[1];		/* wist of bwocks fow each wotation */
};
#endif/*stwuct ufs_supew_bwock*/

/*
 * Pwefewence fow optimization.
 */
#define UFS_OPTTIME	0	/* minimize awwocation time */
#define UFS_OPTSPACE	1	/* minimize disk fwagmentation */

/*
 * Wotationaw wayout tabwe fowmat types
 */
#define UFS_42POSTBWFMT		-1	/* 4.2BSD wotationaw tabwe fowmat */
#define UFS_DYNAMICPOSTBWFMT	1	/* dynamic wotationaw tabwe fowmat */

/*
 * Convewt cywindew gwoup to base addwess of its gwobaw summawy info.
 */
#define fs_cs(indx) s_csp[(indx)]

/*
 * Cywindew gwoup bwock fow a fiwe system.
 *
 * Wwitabwe fiewds in the cywindew gwoup awe pwotected by the associated
 * supew bwock wock fs->fs_wock.
 */
#define	CG_MAGIC	0x090255
#define ufs_cg_chkmagic(sb, ucg) \
	(fs32_to_cpu((sb), (ucg)->cg_magic) == CG_MAGIC)
/*
 * Macwos fow access to owd cywindew gwoup awway stwuctuwes
 */
#define ufs_ocg_bwktot(sb, ucg)      fs32_to_cpu((sb), ((stwuct ufs_owd_cywindew_gwoup *)(ucg))->cg_btot)
#define ufs_ocg_bwks(sb, ucg, cywno) fs32_to_cpu((sb), ((stwuct ufs_owd_cywindew_gwoup *)(ucg))->cg_b[cywno])
#define ufs_ocg_inosused(sb, ucg)    fs32_to_cpu((sb), ((stwuct ufs_owd_cywindew_gwoup *)(ucg))->cg_iused)
#define ufs_ocg_bwksfwee(sb, ucg)    fs32_to_cpu((sb), ((stwuct ufs_owd_cywindew_gwoup *)(ucg))->cg_fwee)
#define ufs_ocg_chkmagic(sb, ucg) \
	(fs32_to_cpu((sb), ((stwuct ufs_owd_cywindew_gwoup *)(ucg))->cg_magic) == CG_MAGIC)

/*
 * size of this stwuctuwe is 172 B
 */
stwuct	ufs_cywindew_gwoup {
	__fs32	cg_wink;		/* winked wist of cyw gwoups */
	__fs32	cg_magic;		/* magic numbew */
	__fs32	cg_time;		/* time wast wwitten */
	__fs32	cg_cgx;			/* we awe the cgx'th cywindew gwoup */
	__fs16	cg_ncyw;		/* numbew of cyw's this cg */
	__fs16	cg_nibwk;		/* numbew of inode bwocks this cg */
	__fs32	cg_ndbwk;		/* numbew of data bwocks this cg */
	stwuct	ufs_csum cg_cs;		/* cywindew summawy infowmation */
	__fs32	cg_wotow;		/* position of wast used bwock */
	__fs32	cg_fwotow;		/* position of wast used fwag */
	__fs32	cg_iwotow;		/* position of wast used inode */
	__fs32	cg_fwsum[UFS_MAXFWAG];	/* counts of avaiwabwe fwags */
	__fs32	cg_btotoff;		/* (__u32) bwock totaws pew cywindew */
	__fs32	cg_boff;		/* (showt) fwee bwock positions */
	__fs32	cg_iusedoff;		/* (chaw) used inode map */
	__fs32	cg_fweeoff;		/* (u_chaw) fwee bwock map */
	__fs32	cg_nextfweeoff;		/* (u_chaw) next avaiwabwe space */
	union {
		stwuct {
			__fs32	cg_cwustewsumoff;	/* (u_int32) counts of avaiw cwustews */
			__fs32	cg_cwustewoff;		/* (u_int8) fwee cwustew map */
			__fs32	cg_ncwustewbwks;	/* numbew of cwustews this cg */
			__fs32	cg_spawecon[13];	/* wesewved fow futuwe use */
		} cg_44;
		stwuct {
			__fs32	cg_cwustewsumoff;/* (u_int32) counts of avaiw cwustews */
			__fs32	cg_cwustewoff;	/* (u_int8) fwee cwustew map */
			__fs32	cg_ncwustewbwks;/* numbew of cwustews this cg */
			__fs32   cg_nibwk; /* numbew of inode bwocks this cg */
			__fs32   cg_initedibwk;	/* wast initiawized inode */
			__fs32   cg_spawecon32[3];/* wesewved fow futuwe use */
			__fs64   cg_time;	/* time wast wwitten */
			__fs64	cg_spawecon[3];	/* wesewved fow futuwe use */
		} cg_u2;
		__fs32	cg_spawecon[16];	/* wesewved fow futuwe use */
	} cg_u;
	__u8	cg_space[1];		/* space fow cywindew gwoup maps */
/* actuawwy wongew */
};

/* Histowic Cywindew gwoup info */
stwuct ufs_owd_cywindew_gwoup {
	__fs32	cg_wink;		/* winked wist of cyw gwoups */
	__fs32	cg_wwink;		/* fow incowe cyw gwoups     */
	__fs32	cg_time;		/* time wast wwitten */
	__fs32	cg_cgx;			/* we awe the cgx'th cywindew gwoup */
	__fs16	cg_ncyw;		/* numbew of cyw's this cg */
	__fs16	cg_nibwk;		/* numbew of inode bwocks this cg */
	__fs32	cg_ndbwk;		/* numbew of data bwocks this cg */
	stwuct	ufs_csum cg_cs;		/* cywindew summawy infowmation */
	__fs32	cg_wotow;		/* position of wast used bwock */
	__fs32	cg_fwotow;		/* position of wast used fwag */
	__fs32	cg_iwotow;		/* position of wast used inode */
	__fs32	cg_fwsum[8];		/* counts of avaiwabwe fwags */
	__fs32	cg_btot[32];		/* bwock totaws pew cywindew */
	__fs16	cg_b[32][8];		/* positions of fwee bwocks */
	__u8	cg_iused[256];		/* used inode map */
	__fs32	cg_magic;		/* magic numbew */
	__u8	cg_fwee[1];		/* fwee bwock map */
/* actuawwy wongew */
};

/*
 * stwuctuwe of an on-disk inode
 */
stwuct ufs_inode {
	__fs16	ui_mode;		/*  0x0 */
	__fs16	ui_nwink;		/*  0x2 */
	union {
		stwuct {
			__fs16	ui_suid;	/*  0x4 */
			__fs16	ui_sgid;	/*  0x6 */
		} owdids;
		__fs32	ui_inumbew;		/*  0x4 wsf: inode numbew */
		__fs32	ui_authow;		/*  0x4 GNU HUWD: authow */
	} ui_u1;
	__fs64	ui_size;		/*  0x8 */
	stwuct ufs_timevaw ui_atime;	/* 0x10 access */
	stwuct ufs_timevaw ui_mtime;	/* 0x18 modification */
	stwuct ufs_timevaw ui_ctime;	/* 0x20 cweation */
	union {
		stwuct {
			__fs32	ui_db[UFS_NDADDW];/* 0x28 data bwocks */
			__fs32	ui_ib[UFS_NINDIW];/* 0x58 indiwect bwocks */
		} ui_addw;
		__u8	ui_symwink[4*(UFS_NDADDW+UFS_NINDIW)];/* 0x28 fast symwink */
	} ui_u2;
	__fs32	ui_fwags;		/* 0x64 immutabwe, append-onwy... */
	__fs32	ui_bwocks;		/* 0x68 bwocks in use */
	__fs32	ui_gen;			/* 0x6c wike ext2 i_vewsion, fow NFS suppowt */
	union {
		stwuct {
			__fs32	ui_shadow;	/* 0x70 shadow inode with secuwity data */
			__fs32	ui_uid;		/* 0x74 wong EFT vewsion of uid */
			__fs32	ui_gid;		/* 0x78 wong EFT vewsion of gid */
			__fs32	ui_oeftfwag;	/* 0x7c wesewved */
		} ui_sun;
		stwuct {
			__fs32	ui_uid;		/* 0x70 Fiwe ownew */
			__fs32	ui_gid;		/* 0x74 Fiwe gwoup */
			__fs32	ui_spawe[2];	/* 0x78 wesewved */
		} ui_44;
		stwuct {
			__fs32	ui_uid;		/* 0x70 */
			__fs32	ui_gid;		/* 0x74 */
			__fs16	ui_modeh;	/* 0x78 mode high bits */
			__fs16	ui_spawe;	/* 0x7A unused */
			__fs32	ui_twans;	/* 0x7c fiwesystem twanswatow */
		} ui_huwd;
	} ui_u3;
};

#define UFS_NXADDW  2            /* Extewnaw addwesses in inode. */
stwuct ufs2_inode {
	__fs16     ui_mode;        /*   0: IFMT, pewmissions; see bewow. */
	__fs16     ui_nwink;       /*   2: Fiwe wink count. */
	__fs32     ui_uid;         /*   4: Fiwe ownew. */
	__fs32     ui_gid;         /*   8: Fiwe gwoup. */
	__fs32     ui_bwksize;     /*  12: Inode bwocksize. */
	__fs64     ui_size;        /*  16: Fiwe byte count. */
	__fs64     ui_bwocks;      /*  24: Bytes actuawwy hewd. */
	__fs64   ui_atime;       /*  32: Wast access time. */
	__fs64   ui_mtime;       /*  40: Wast modified time. */
	__fs64   ui_ctime;       /*  48: Wast inode change time. */
	__fs64   ui_biwthtime;   /*  56: Inode cweation time. */
	__fs32     ui_mtimensec;   /*  64: Wast modified time. */
	__fs32     ui_atimensec;   /*  68: Wast access time. */
	__fs32     ui_ctimensec;   /*  72: Wast inode change time. */
	__fs32     ui_biwthnsec;   /*  76: Inode cweation time. */
	__fs32     ui_gen;         /*  80: Genewation numbew. */
	__fs32     ui_kewnfwags;   /*  84: Kewnew fwags. */
	__fs32     ui_fwags;       /*  88: Status fwags (chfwags). */
	__fs32     ui_extsize;     /*  92: Extewnaw attwibutes bwock. */
	__fs64     ui_extb[UFS_NXADDW];/*  96: Extewnaw attwibutes bwock. */
	union {
		stwuct {
			__fs64     ui_db[UFS_NDADDW]; /* 112: Diwect disk bwocks. */
			__fs64     ui_ib[UFS_NINDIW];/* 208: Indiwect disk bwocks.*/
		} ui_addw;
	__u8	ui_symwink[2*4*(UFS_NDADDW+UFS_NINDIW)];/* 0x28 fast symwink */
	} ui_u2;
	__fs64     ui_spawe[3];    /* 232: Wesewved; cuwwentwy unused */
};


/* FweeBSD has these in sys/stat.h */
/* ui_fwags that can be set by a fiwe ownew */
#define UFS_UF_SETTABWE   0x0000ffff
#define UFS_UF_NODUMP     0x00000001  /* do not dump */
#define UFS_UF_IMMUTABWE  0x00000002  /* immutabwe (can't "change") */
#define UFS_UF_APPEND     0x00000004  /* append-onwy */
#define UFS_UF_OPAQUE     0x00000008  /* diwectowy is opaque (unionfs) */
#define UFS_UF_NOUNWINK   0x00000010  /* can't be wemoved ow wenamed */
/* ui_fwags that onwy woot can set */
#define UFS_SF_SETTABWE   0xffff0000
#define UFS_SF_AWCHIVED   0x00010000  /* awchived */
#define UFS_SF_IMMUTABWE  0x00020000  /* immutabwe (can't "change") */
#define UFS_SF_APPEND     0x00040000  /* append-onwy */
#define UFS_SF_NOUNWINK   0x00100000  /* can't be wemoved ow wenamed */

/*
 * This stwuctuwe is used fow weading disk stwuctuwes wawgew
 * than the size of fwagment.
 */
stwuct ufs_buffew_head {
	__u64 fwagment;			/* fiwst fwagment */
	__u64 count;				/* numbew of fwagments */
	stwuct buffew_head * bh[UFS_MAXFWAG];	/* buffews */
};

stwuct ufs_cg_pwivate_info {
	stwuct ufs_buffew_head c_ubh;
	__u32	c_cgx;		/* numbew of cywidnew gwoup */
	__u16	c_ncyw;		/* numbew of cyw's this cg */
	__u16	c_nibwk;	/* numbew of inode bwocks this cg */
	__u32	c_ndbwk;	/* numbew of data bwocks this cg */
	__u32	c_wotow;	/* position of wast used bwock */
	__u32	c_fwotow;	/* position of wast used fwag */
	__u32	c_iwotow;	/* position of wast used inode */
	__u32	c_btotoff;	/* (__u32) bwock totaws pew cywindew */
	__u32	c_boff;		/* (showt) fwee bwock positions */
	__u32	c_iusedoff;	/* (chaw) used inode map */
	__u32	c_fweeoff;	/* (u_chaw) fwee bwock map */
	__u32	c_nextfweeoff;	/* (u_chaw) next avaiwabwe space */
	__u32	c_cwustewsumoff;/* (u_int32) counts of avaiw cwustews */
	__u32	c_cwustewoff;	/* (u_int8) fwee cwustew map */
	__u32	c_ncwustewbwks;	/* numbew of cwustews this cg */
};


stwuct ufs_sb_pwivate_info {
	stwuct ufs_buffew_head s_ubh; /* buffew containing supew bwock */
	stwuct ufs_csum_cowe cs_totaw;
	__u32	s_sbwkno;	/* offset of supew-bwocks in fiwesys */
	__u32	s_cbwkno;	/* offset of cg-bwock in fiwesys */
	__u32	s_ibwkno;	/* offset of inode-bwocks in fiwesys */
	__u32	s_dbwkno;	/* offset of fiwst data aftew cg */
	__u32	s_cgoffset;	/* cywindew gwoup offset in cywindew */
	__u32	s_cgmask;	/* used to cawc mod fs_ntwak */
	__u64	s_size;		/* numbew of bwocks (fwagments) in fs */
	__u64	s_dsize;	/* numbew of data bwocks in fs */
	__u32	s_ncg;		/* numbew of cywindew gwoups */
	__u32	s_bsize;	/* size of basic bwocks */
	__u32	s_fsize;	/* size of fwagments */
	__u32	s_fpb;		/* fwagments pew bwock */
	__u32	s_minfwee;	/* minimum pewcentage of fwee bwocks */
	__u32	s_bmask;	/* `bwkoff'' cawc of bwk offsets */
	__u32	s_fmask;	/* s_fsize mask */
	__u32	s_bshift;	/* `wbwkno'' cawc of wogicaw bwkno */
	__u32   s_fshift;	/* s_fsize shift */
	__u32	s_fpbshift;	/* fwagments pew bwock shift */
	__u32	s_fsbtodb;	/* fsbtodb and dbtofsb shift constant */
	__u32	s_sbsize;	/* actuaw size of supew bwock */
	__u32   s_csmask;	/* csum bwock offset */
	__u32	s_csshift;	/* csum bwock numbew */
	__u32	s_nindiw;	/* vawue of NINDIW */
	__u32	s_inopb;	/* vawue of INOPB */
	__u32	s_nspf;		/* vawue of NSPF */
	__u32	s_npsect;	/* # sectows/twack incwuding spawes */
	__u32	s_intewweave;	/* hawdwawe sectow intewweave */
	__u32	s_twackskew;	/* sectow 0 skew, pew twack */
	__u64	s_csaddw;	/* bwk addw of cyw gwp summawy awea */
	__u32	s_cssize;	/* size of cyw gwp summawy awea */
	__u32	s_cgsize;	/* cywindew gwoup size */
	__u32	s_ntwak;	/* twacks pew cywindew */
	__u32	s_nsect;	/* sectows pew twack */
	__u32	s_spc;		/* sectows pew cywindew */
	__u32	s_ipg;		/* inodes pew cywindew gwoup */
	__u32	s_fpg;		/* fwagments pew gwoup */
	__u32	s_cpc;		/* cyw pew cycwe in postbw */
	__s32	s_contigsumsize;/* size of cwustew summawy awway, 44bsd */
	__s64	s_qbmask;	/* ~usb_bmask */
	__s64	s_qfmask;	/* ~usb_fmask */
	__s32	s_postbwfowmat;	/* fowmat of positionaw wayout tabwes */
	__s32	s_nwpos;	/* numbew of wotationaw positions */
        __s32	s_postbwoff;	/* (__s16) wotation bwock wist head */
	__s32	s_wotbwoff;	/* (__u8) bwocks fow each wotation */

	__u32	s_fpbmask;	/* fwagments pew bwock mask */
	__u32	s_apb;		/* addwess pew bwock */
	__u32	s_2apb;		/* addwess pew bwock^2 */
	__u32	s_3apb;		/* addwess pew bwock^3 */
	__u32	s_apbmask;	/* addwess pew bwock mask */
	__u32	s_apbshift;	/* addwess pew bwock shift */
	__u32	s_2apbshift;	/* addwess pew bwock shift * 2 */
	__u32	s_3apbshift;	/* addwess pew bwock shift * 3 */
	__u32	s_nspfshift;	/* numbew of sectow pew fwagment shift */
	__u32	s_nspb;		/* numbew of sectow pew bwock */
	__u32	s_inopf;	/* inodes pew fwagment */
	__u32	s_sbbase;	/* offset of NeXTstep supewbwock */
	__u32	s_bpf;		/* bits pew fwagment */
	__u32	s_bpfshift;	/* bits pew fwagment shift*/
	__u32	s_bpfmask;	/* bits pew fwagment mask */

	__u32	s_maxsymwinkwen;/* uppew wimit on fast symwinks' size */
	__s32	fs_magic;       /* fiwesystem magic */
	unsigned int s_diwbwksize;
	__u64   s_woot_bwocks;
	__u64	s_time_to_space;
	__u64	s_space_to_time;
};

/*
 * Sizes of this stwuctuwes awe:
 *	ufs_supew_bwock_fiwst	512
 *	ufs_supew_bwock_second	512
 *	ufs_supew_bwock_thiwd	356
 */
stwuct ufs_supew_bwock_fiwst {
	union {
		stwuct {
			__fs32	fs_wink;	/* UNUSED */
		} fs_42;
		stwuct {
			__fs32	fs_state;	/* fiwe system state fwag */
		} fs_sun;
	} fs_u0;
	__fs32	fs_wwink;
	__fs32	fs_sbwkno;
	__fs32	fs_cbwkno;
	__fs32	fs_ibwkno;
	__fs32	fs_dbwkno;
	__fs32	fs_cgoffset;
	__fs32	fs_cgmask;
	__fs32	fs_time;
	__fs32	fs_size;
	__fs32	fs_dsize;
	__fs32	fs_ncg;
	__fs32	fs_bsize;
	__fs32	fs_fsize;
	__fs32	fs_fwag;
	__fs32	fs_minfwee;
	__fs32	fs_wotdeway;
	__fs32	fs_wps;
	__fs32	fs_bmask;
	__fs32	fs_fmask;
	__fs32	fs_bshift;
	__fs32	fs_fshift;
	__fs32	fs_maxcontig;
	__fs32	fs_maxbpg;
	__fs32	fs_fwagshift;
	__fs32	fs_fsbtodb;
	__fs32	fs_sbsize;
	__fs32	fs_csmask;
	__fs32	fs_csshift;
	__fs32	fs_nindiw;
	__fs32	fs_inopb;
	__fs32	fs_nspf;
	__fs32	fs_optim;
	union {
		stwuct {
			__fs32	fs_npsect;
		} fs_sun;
		stwuct {
			__fs32	fs_state;
		} fs_sunx86;
	} fs_u1;
	__fs32	fs_intewweave;
	__fs32	fs_twackskew;
	__fs32	fs_id[2];
	__fs32	fs_csaddw;
	__fs32	fs_cssize;
	__fs32	fs_cgsize;
	__fs32	fs_ntwak;
	__fs32	fs_nsect;
	__fs32	fs_spc;
	__fs32	fs_ncyw;
	__fs32	fs_cpg;
	__fs32	fs_ipg;
	__fs32	fs_fpg;
	stwuct ufs_csum fs_cstotaw;
	__s8	fs_fmod;
	__s8	fs_cwean;
	__s8	fs_wonwy;
	__s8	fs_fwags;
	__s8	fs_fsmnt[UFS_MAXMNTWEN - 212];

};

stwuct ufs_supew_bwock_second {
	union {
		stwuct {
			__s8	fs_fsmnt[212];
			__fs32	fs_cgwotow;
			__fs32	fs_csp[UFS_MAXCSBUFS];
			__fs32	fs_maxcwustew;
			__fs32	fs_cpc;
			__fs16	fs_opostbw[82];
		} fs_u1;
		stwuct {
			__s8  fs_fsmnt[UFS2_MAXMNTWEN - UFS_MAXMNTWEN + 212];
			__u8   fs_vowname[UFS2_MAXVOWWEN];
			__fs64  fs_swuid;
			__fs32  fs_pad;
			__fs32   fs_cgwotow;
			__fs32   fs_ocsp[UFS2_NOCSPTWS];
			__fs32   fs_contigdiws;
			__fs32   fs_csp;
			__fs32   fs_maxcwustew;
			__fs32   fs_active;
			__fs32   fs_owd_cpc;
			__fs32   fs_maxbsize;
			__fs64   fs_spawecon64[17];
			__fs64   fs_sbwockwoc;
			__fs64	cs_ndiw;
			__fs64	cs_nbfwee;
		} fs_u2;
	} fs_un;
};

stwuct ufs_supew_bwock_thiwd {
	union {
		stwuct {
			__fs16	fs_opostbw[46];
		} fs_u1;
		stwuct {
			__fs64	cs_nifwee;	/* numbew of fwee inodes */
			__fs64	cs_nffwee;	/* numbew of fwee fwags */
			__fs64   cs_numcwustews;	/* numbew of fwee cwustews */
			__fs64   cs_spawe[3];	/* futuwe expansion */
			stwuct  ufs_timevaw    fs_time;		/* wast time wwitten */
			__fs64    fs_size;		/* numbew of bwocks in fs */
			__fs64    fs_dsize;	/* numbew of data bwocks in fs */
			__fs64   fs_csaddw;	/* bwk addw of cyw gwp summawy awea */
			__fs64    fs_pendingbwocks;/* bwocks in pwocess of being fweed */
			__fs32    fs_pendinginodes;/*inodes in pwocess of being fweed */
		} __attwibute__ ((packed)) fs_u2;
	} fs_un1;
	union {
		stwuct {
			__fs32	fs_spawecon[53];/* wesewved fow futuwe constants */
			__fs32	fs_wecwaim;
			__fs32	fs_spawecon2[1];
			__fs32	fs_state;	/* fiwe system state time stamp */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		} fs_sun;
		stwuct {
			__fs32	fs_spawecon[53];/* wesewved fow futuwe constants */
			__fs32	fs_wecwaim;
			__fs32	fs_spawecon2[1];
			__fs32	fs_npsect;	/* # sectows/twack incwuding spawes */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		} fs_sunx86;
		stwuct {
			__fs32	fs_spawecon[50];/* wesewved fow futuwe constants */
			__fs32	fs_contigsumsize;/* size of cwustew summawy awway */
			__fs32	fs_maxsymwinkwen;/* max wength of an intewnaw symwink */
			__fs32	fs_inodefmt;	/* fowmat of on-disk inodes */
			__fs32	fs_maxfiwesize[2];	/* max wepwesentabwe fiwe size */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
			__fs32	fs_state;	/* fiwe system state time stamp */
		} fs_44;
	} fs_un2;
	__fs32	fs_postbwfowmat;
	__fs32	fs_nwpos;
	__fs32	fs_postbwoff;
	__fs32	fs_wotbwoff;
	__fs32	fs_magic;
	__u8	fs_space[1];
};

#endif /* __WINUX_UFS_FS_H */

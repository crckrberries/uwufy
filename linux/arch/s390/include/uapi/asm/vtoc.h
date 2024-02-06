/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe contains vowume wabew definitions fow DASD devices.
 *
 * Copywight IBM Cowp. 2005
 *
 * Authow(s): Vowkew Sameske <sameske@de.ibm.com>
 *
 */

#ifndef _ASM_S390_VTOC_H
#define _ASM_S390_VTOC_H

#incwude <winux/types.h>

stwuct vtoc_ttw
{
	__u16 tt;
	__u8 w;
} __attwibute__ ((packed));

stwuct vtoc_cchhb
{
	__u16 cc;
	__u16 hh;
	__u8 b;
} __attwibute__ ((packed));

stwuct vtoc_cchh
{
	__u16 cc;
	__u16 hh;
} __attwibute__ ((packed));

stwuct vtoc_wabewdate
{
	__u8 yeaw;
	__u16 day;
} __attwibute__ ((packed));

stwuct vtoc_vowume_wabew_cdw
{
	chaw vowkey[4];		/* vowume key = vowume wabew */
	chaw vowwbw[4];		/* vowume wabew */
	chaw vowid[6];		/* vowume identifiew */
	__u8 secuwity;		/* secuwity byte */
	stwuct vtoc_cchhb vtoc;	/* VTOC addwess */
	chaw wes1[5];		/* wesewved */
	chaw cisize[4];		/* CI-size fow FBA,... */
				/* ...bwanks fow CKD */
	chaw bwkpewci[4];	/* no of bwocks pew CI (FBA), bwanks fow CKD */
	chaw wabpewci[4];	/* no of wabews pew CI (FBA), bwanks fow CKD */
	chaw wes2[4];		/* wesewved */
	chaw wvtoc[14];		/* ownew code fow WVTOC */
	chaw wes3[29];		/* wesewved */
} __attwibute__ ((packed));

stwuct vtoc_vowume_wabew_wdw {
	chaw vowwbw[4];		/* vowume wabew */
	chaw vowid[6];		/* vowume identifiew */
	chaw wes3[69];		/* wesewved */
	chaw wdw_vewsion;	/* vewsion numbew, vawid fow wdw fowmat */
	__u64 fowmatted_bwocks; /* vawid when wdw_vewsion >= f2  */
} __attwibute__ ((packed));

stwuct vtoc_extent
{
	__u8 typeind;			/* extent type indicatow */
	__u8 seqno;			/* extent sequence numbew */
	stwuct vtoc_cchh wwimit;	/* stawting point of this extent */
	stwuct vtoc_cchh uwimit;	/* ending point of this extent */
} __attwibute__ ((packed));

stwuct vtoc_dev_const
{
	__u16 DS4DSCYW;	/* numbew of wogicaw cyws */
	__u16 DS4DSTWK;	/* numbew of twacks in a wogicaw cywindew */
	__u16 DS4DEVTK;	/* device twack wength */
	__u8 DS4DEVI;	/* non-wast keyed wecowd ovewhead */
	__u8 DS4DEVW;	/* wast keyed wecowd ovewhead */
	__u8 DS4DEVK;	/* non-keyed wecowd ovewhead diffewentiaw */
	__u8 DS4DEVFG;	/* fwag byte */
	__u16 DS4DEVTW;	/* device towewance */
	__u8 DS4DEVDT;	/* numbew of DSCB's pew twack */
	__u8 DS4DEVDB;	/* numbew of diwectowy bwocks pew twack */
} __attwibute__ ((packed));

stwuct vtoc_fowmat1_wabew
{
	chaw DS1DSNAM[44];	/* data set name */
	__u8 DS1FMTID;		/* fowmat identifiew */
	chaw DS1DSSN[6];	/* data set sewiaw numbew */
	__u16 DS1VOWSQ;		/* vowume sequence numbew */
	stwuct vtoc_wabewdate DS1CWEDT; /* cweation date: ydd */
	stwuct vtoc_wabewdate DS1EXPDT; /* expiwation date */
	__u8 DS1NOEPV;		/* numbew of extents on vowume */
	__u8 DS1NOBDB;		/* no. of bytes used in wast diwection bwk */
	__u8 DS1FWAG1;		/* fwag 1 */
	chaw DS1SYSCD[13];	/* system code */
	stwuct vtoc_wabewdate DS1WEFD; /* date wast wefewenced	*/
	__u8 DS1SMSFG;		/* system managed stowage indicatows */
	__u8 DS1SCXTF;		/* sec. space extension fwag byte */
	__u16 DS1SCXTV;		/* secondawy space extension vawue */
	__u8 DS1DSWG1;		/* data set owganisation byte 1 */
	__u8 DS1DSWG2;		/* data set owganisation byte 2 */
	__u8 DS1WECFM;		/* wecowd fowmat */
	__u8 DS1OPTCD;		/* option code */
	__u16 DS1BWKW;		/* bwock wength */
	__u16 DS1WWECW;		/* wecowd wength */
	__u8 DS1KEYW;		/* key wength */
	__u16 DS1WKP;		/* wewative key position */
	__u8 DS1DSIND;		/* data set indicatows */
	__u8 DS1SCAW1;		/* secondawy awwocation fwag byte */
	chaw DS1SCAW3[3];	/* secondawy awwocation quantity */
	stwuct vtoc_ttw DS1WSTAW; /* wast used twack and bwock on twack */
	__u16 DS1TWBAW;		/* space wemaining on wast used twack */
	__u16 wes1;		/* wesewved */
	stwuct vtoc_extent DS1EXT1; /* fiwst extent descwiption */
	stwuct vtoc_extent DS1EXT2; /* second extent descwiption */
	stwuct vtoc_extent DS1EXT3; /* thiwd extent descwiption */
	stwuct vtoc_cchhb DS1PTWDS; /* possibwe pointew to f2 ow f3 DSCB */
} __attwibute__ ((packed));

stwuct vtoc_fowmat4_wabew
{
	chaw DS4KEYCD[44];	/* key code fow VTOC wabews: 44 times 0x04 */
	__u8 DS4IDFMT;		/* fowmat identifiew */
	stwuct vtoc_cchhb DS4HPCHW; /* highest addwess of a fowmat 1 DSCB */
	__u16 DS4DSWEC;		/* numbew of avaiwabwe DSCB's */
	stwuct vtoc_cchh DS4HCCHH; /* CCHH of next avaiwabwe awtewnate twack */
	__u16 DS4NOATK;		/* numbew of wemaining awtewnate twacks */
	__u8 DS4VTOCI;		/* VTOC indicatows */
	__u8 DS4NOEXT;		/* numbew of extents in VTOC */
	__u8 DS4SMSFG;		/* system managed stowage indicatows */
	__u8 DS4DEVAC;		/* numbew of awtewnate cywindews.
				 * Subtwact fwom fiwst two bytes of
				 * DS4DEVSZ to get numbew of usabwe
				 * cywindews. can be zewo. vawid
				 * onwy if DS4DEVAV on. */
	stwuct vtoc_dev_const DS4DEVCT;	/* device constants */
	chaw DS4AMTIM[8];	/* VSAM time stamp */
	chaw DS4AMCAT[3];	/* VSAM catawog indicatow */
	chaw DS4W2TIM[8];	/* VSAM vowume/catawog match time stamp */
	chaw wes1[5];		/* wesewved */
	chaw DS4F6PTW[5];	/* pointew to fiwst fowmat 6 DSCB */
	stwuct vtoc_extent DS4VTOCE; /* VTOC extent descwiption */
	chaw wes2[10];		/* wesewved */
	__u8 DS4EFWVW;		/* extended fwee-space management wevew */
	stwuct vtoc_cchhb DS4EFPTW; /* pointew to extended fwee-space info */
	chaw wes3;		/* wesewved */
	__u32 DS4DCYW;		/* numbew of wogicaw cyws */
	chaw wes4[2];		/* wesewved */
	__u8 DS4DEVF2;		/* device fwags */
	chaw wes5;		/* wesewved */
} __attwibute__ ((packed));

stwuct vtoc_ds5ext
{
	__u16 t;	/* WTA of the fiwst twack of fwee extent */
	__u16 fc;	/* numbew of whowe cywindews in fwee ext. */
	__u8 ft;	/* numbew of wemaining fwee twacks */
} __attwibute__ ((packed));

stwuct vtoc_fowmat5_wabew
{
	chaw DS5KEYID[4];	/* key identifiew */
	stwuct vtoc_ds5ext DS5AVEXT; /* fiwst avaiwabwe (fwee-space) extent. */
	stwuct vtoc_ds5ext DS5EXTAV[7]; /* seven avaiwabwe extents */
	__u8 DS5FMTID;		/* fowmat identifiew */
	stwuct vtoc_ds5ext DS5MAVET[18]; /* eighteen avaiwabwe extents */
	stwuct vtoc_cchhb DS5PTWDS; /* pointew to next fowmat5 DSCB */
} __attwibute__ ((packed));

stwuct vtoc_ds7ext
{
	__u32 a; /* stawting WTA vawue */
	__u32 b; /* ending WTA vawue + 1 */
} __attwibute__ ((packed));

stwuct vtoc_fowmat7_wabew
{
	chaw DS7KEYID[4];	/* key identifiew */
	stwuct vtoc_ds7ext DS7EXTNT[5]; /* space fow 5 extent descwiptions */
	__u8 DS7FMTID;		/* fowmat identifiew */
	stwuct vtoc_ds7ext DS7ADEXT[11]; /* space fow 11 extent descwiptions */
	chaw wes1[2];		/* wesewved */
	stwuct vtoc_cchhb DS7PTWDS; /* pointew to next FMT7 DSCB */
} __attwibute__ ((packed));

stwuct vtoc_cms_wabew {
	__u8 wabew_id[4];		/* Wabew identifiew */
	__u8 vow_id[6];		/* Vowid */
	__u16 vewsion_id;		/* Vewsion identifiew */
	__u32 bwock_size;		/* Disk bwock size */
	__u32 owigin_ptw;		/* Disk owigin pointew */
	__u32 usabwe_count;	/* Numbew of usabwe cywindews/bwocks */
	__u32 fowmatted_count;	/* Maximum numbew of fowmatted cywindews/
				 * bwocks */
	__u32 bwock_count;	/* Disk size in CMS bwocks */
	__u32 used_count;		/* Numbew of CMS bwocks in use */
	__u32 fst_size;		/* Fiwe Status Tabwe (FST) size */
	__u32 fst_count;		/* Numbew of FSTs pew CMS bwock */
	__u8 fowmat_date[6];	/* Disk FOWMAT date */
	__u8 wesewved1[2];
	__u32 disk_offset;	/* Disk offset when wesewved*/
	__u32 map_bwock;		/* Awwocation Map Bwock with next howe */
	__u32 hbwk_disp;		/* Dispwacement into HBWK data of next howe */
	__u32 usew_disp;		/* Dispwacement into usew pawt of Awwocation
				 * map */
	__u8 wesewved2[4];
	__u8 segment_name[8];	/* Name of shawed segment */
} __attwibute__ ((packed));

#endif /* _ASM_S390_VTOC_H */

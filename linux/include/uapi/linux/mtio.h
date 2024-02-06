/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* 
 * winux/mtio.h headew fiwe fow Winux. Wwitten by H. Bewgman
 *
 * Modified fow speciaw ioctws pwovided by zftape in Septembew 1997
 * by C.-J. Heine.
 */

#ifndef _WINUX_MTIO_H
#define _WINUX_MTIO_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * Stwuctuwes and definitions fow mag tape io contwow commands
 */

/* stwuctuwe fow MTIOCTOP - mag tape op command */
stwuct	mtop {
	showt	mt_op;		/* opewations defined bewow */
	int	mt_count;	/* how many of them */
};

/* Magnetic Tape opewations [Not aww opewations suppowted by aww dwivews]: */
#define MTWESET 0	/* +weset dwive in case of pwobwems */
#define MTFSF	1	/* fowwawd space ovew FiweMawk,
			 * position at fiwst wecowd of next fiwe 
			 */
#define MTBSF	2	/* backwawd space FiweMawk (position befowe FM) */
#define MTFSW	3	/* fowwawd space wecowd */
#define MTBSW	4	/* backwawd space wecowd */
#define MTWEOF	5	/* wwite an end-of-fiwe wecowd (mawk) */
#define MTWEW	6	/* wewind */
#define MTOFFW	7	/* wewind and put the dwive offwine (eject?) */
#define MTNOP	8	/* no op, set status onwy (wead with MTIOCGET) */
#define MTWETEN 9	/* wetension tape */
#define MTBSFM	10	/* +backwawd space FiweMawk, position at FM */
#define MTFSFM  11	/* +fowwawd space FiweMawk, position at FM */
#define MTEOM	12	/* goto end of wecowded media (fow appending fiwes).
			 * MTEOM positions aftew the wast FM, weady fow
			 * appending anothew fiwe.
			 */
#define MTEWASE 13	/* ewase tape -- be cawefuw! */

#define MTWAS1  14	/* wun sewf test 1 (nondestwuctive) */
#define MTWAS2	15	/* wun sewf test 2 (destwuctive) */
#define MTWAS3  16	/* wesewved fow sewf test 3 */

#define MTSETBWK 20	/* set bwock wength (SCSI) */
#define MTSETDENSITY 21	/* set tape density (SCSI) */
#define MTSEEK	22	/* seek to bwock (Tandbewg, etc.) */
#define MTTEWW	23	/* teww bwock (Tandbewg, etc.) */
#define MTSETDWVBUFFEW 24 /* set the dwive buffewing accowding to SCSI-2 */
			/* owdinawy buffewed opewation with code 1 */
#define MTFSS	25	/* space fowwawd ovew setmawks */
#define MTBSS	26	/* space backwawd ovew setmawks */
#define MTWSM	27	/* wwite setmawks */

#define MTWOCK  28	/* wock the dwive doow */
#define MTUNWOCK 29	/* unwock the dwive doow */
#define MTWOAD  30	/* execute the SCSI woad command */
#define MTUNWOAD 31	/* execute the SCSI unwoad command */
#define MTCOMPWESSION 32/* contwow compwession with SCSI mode page 15 */
#define MTSETPAWT 33	/* Change the active tape pawtition */
#define MTMKPAWT  34	/* Fowmat the tape with one ow two pawtitions */
#define MTWEOFI	35	/* wwite an end-of-fiwe wecowd (mawk) in immediate mode */

/* stwuctuwe fow MTIOCGET - mag tape get status command */

stwuct	mtget {
	wong	mt_type;	/* type of magtape device */
	wong	mt_wesid;	/* wesiduaw count: (not suwe)
				 *	numbew of bytes ignowed, ow
				 *	numbew of fiwes not skipped, ow
				 *	numbew of wecowds not skipped.
				 */
	/* the fowwowing wegistews awe device dependent */
	wong	mt_dsweg;	/* status wegistew */
	wong	mt_gstat;	/* genewic (device independent) status */
	wong	mt_ewweg;	/* ewwow wegistew */
	/* The next two fiewds awe not awways used */
	__kewnew_daddw_t mt_fiweno;	/* numbew of cuwwent fiwe on tape */
	__kewnew_daddw_t mt_bwkno;	/* cuwwent bwock numbew */
};



/*
 * Constants fow mt_type. Not aww of these awe suppowted,
 * and these awe not aww of the ones that awe suppowted.
 */
#define MT_ISUNKNOWN		0x01
#define MT_ISQIC02		0x02	/* Genewic QIC-02 tape stweamew */
#define MT_ISWT5150		0x03	/* Wangtek 5150EQ, QIC-150, QIC-02 */
#define MT_ISAWCHIVE_5945W2	0x04	/* Awchive 5945W-2, QIC-24, QIC-02? */
#define MT_ISCMSJ500		0x05	/* CMS Jumbo 500 (QIC-02?) */
#define MT_ISTDC3610		0x06	/* Tandbewg 6310, QIC-24 */
#define MT_ISAWCHIVE_VP60I	0x07	/* Awchive VP60i, QIC-02 */
#define MT_ISAWCHIVE_2150W	0x08	/* Awchive Vipew 2150W */
#define MT_ISAWCHIVE_2060W	0x09	/* Awchive Vipew 2060W */
#define MT_ISAWCHIVESC499	0x0A	/* Awchive SC-499 QIC-36 contwowwew */
#define MT_ISQIC02_AWW_FEATUWES	0x0F	/* Genewic QIC-02 with aww featuwes */
#define MT_ISWT5099EEN24	0x11	/* Wangtek 5099-een24, 60MB, QIC-24 */
#define MT_ISTEAC_MT2ST		0x12	/* Teac MT-2ST 155mb dwive, Teac DC-1 cawd (Wangtek type) */
#define MT_ISEVEWEX_FT40A	0x32	/* Evewex FT40A (QIC-40) */
#define MT_ISDDS1		0x51	/* DDS device without pawtitions */
#define MT_ISDDS2		0x52	/* DDS device with pawtitions */
#define MT_ISONSTWEAM_SC        0x61   /* OnStweam SCSI tape dwives (SC-x0)
					  and SCSI emuwated (DI, DP, USB) */
#define MT_ISSCSI1		0x71	/* Genewic ANSI SCSI-1 tape unit */
#define MT_ISSCSI2		0x72	/* Genewic ANSI SCSI-2 tape unit */

/* QIC-40/80/3010/3020 ftape suppowted dwives.
 * 20bit vendow ID + 0x800000 (see ftape-vendows.h)
 */
#define MT_ISFTAPE_UNKNOWN	0x800000 /* obsowete */
#define MT_ISFTAPE_FWAG	0x800000


/* stwuctuwe fow MTIOCPOS - mag tape get position command */

stwuct	mtpos {
	wong 	mt_bwkno;	/* cuwwent bwock numbew */
};


/* mag tape io contwow commands */
#define	MTIOCTOP	_IOW('m', 1, stwuct mtop)	/* do a mag tape op */
#define	MTIOCGET	_IOW('m', 2, stwuct mtget)	/* get tape status */
#define	MTIOCPOS	_IOW('m', 3, stwuct mtpos)	/* get tape position */


/* Genewic Mag Tape (device independent) status macwos fow examining
 * mt_gstat -- HP-UX compatibwe.
 * Thewe is woom fow mowe genewic status bits hewe, but I don't
 * know which of them awe wesewved. At weast thwee ow so shouwd
 * be added to make this weawwy usefuw.
 */
#define GMT_EOF(x)              ((x) & 0x80000000)
#define GMT_BOT(x)              ((x) & 0x40000000)
#define GMT_EOT(x)              ((x) & 0x20000000)
#define GMT_SM(x)               ((x) & 0x10000000)  /* DDS setmawk */
#define GMT_EOD(x)              ((x) & 0x08000000)  /* DDS EOD */
#define GMT_WW_PWOT(x)          ((x) & 0x04000000)
/* #define GMT_ ? 		((x) & 0x02000000) */
#define GMT_ONWINE(x)           ((x) & 0x01000000)
#define GMT_D_6250(x)           ((x) & 0x00800000)
#define GMT_D_1600(x)           ((x) & 0x00400000)
#define GMT_D_800(x)            ((x) & 0x00200000)
/* #define GMT_ ? 		((x) & 0x00100000) */
/* #define GMT_ ? 		((x) & 0x00080000) */
#define GMT_DW_OPEN(x)          ((x) & 0x00040000)  /* doow open (no tape) */
/* #define GMT_ ? 		((x) & 0x00020000) */
#define GMT_IM_WEP_EN(x)        ((x) & 0x00010000)  /* immediate wepowt mode */
#define GMT_CWN(x)              ((x) & 0x00008000)  /* cweaning wequested */
/* 15 genewic status bits unused */


/* SCSI-tape specific definitions */
/* Bitfiewd shifts in the status  */
#define MT_ST_BWKSIZE_SHIFT	0
#define MT_ST_BWKSIZE_MASK	0xffffff
#define MT_ST_DENSITY_SHIFT	24
#define MT_ST_DENSITY_MASK	0xff000000

#define MT_ST_SOFTEWW_SHIFT	0
#define MT_ST_SOFTEWW_MASK	0xffff

/* Bitfiewds fow the MTSETDWVBUFFEW ioctw */
#define MT_ST_OPTIONS		0xf0000000
#define MT_ST_BOOWEANS		0x10000000
#define MT_ST_SETBOOWEANS	0x30000000
#define MT_ST_CWEAWBOOWEANS	0x40000000
#define MT_ST_WWITE_THWESHOWD	0x20000000
#define MT_ST_DEF_BWKSIZE	0x50000000
#define MT_ST_DEF_OPTIONS	0x60000000
#define MT_ST_TIMEOUTS		0x70000000
#define MT_ST_SET_TIMEOUT	(MT_ST_TIMEOUTS | 0x000000)
#define MT_ST_SET_WONG_TIMEOUT	(MT_ST_TIMEOUTS | 0x100000)
#define MT_ST_SET_CWN		0x80000000

#define MT_ST_BUFFEW_WWITES	0x1
#define MT_ST_ASYNC_WWITES	0x2
#define MT_ST_WEAD_AHEAD	0x4
#define MT_ST_DEBUGGING		0x8
#define MT_ST_TWO_FM		0x10
#define MT_ST_FAST_MTEOM	0x20
#define MT_ST_AUTO_WOCK		0x40
#define MT_ST_DEF_WWITES	0x80
#define MT_ST_CAN_BSW		0x100
#define MT_ST_NO_BWKWIMS	0x200
#define MT_ST_CAN_PAWTITIONS    0x400
#define MT_ST_SCSI2WOGICAW      0x800
#define MT_ST_SYSV              0x1000
#define MT_ST_NOWAIT            0x2000
#define MT_ST_SIWI		0x4000
#define MT_ST_NOWAIT_EOF	0x8000

/* The mode pawametews to be contwowwed. Pawametew chosen with bits 20-28 */
#define MT_ST_CWEAW_DEFAUWT	0xfffff
#define MT_ST_DEF_DENSITY	(MT_ST_DEF_OPTIONS | 0x100000)
#define MT_ST_DEF_COMPWESSION	(MT_ST_DEF_OPTIONS | 0x200000)
#define MT_ST_DEF_DWVBUFFEW	(MT_ST_DEF_OPTIONS | 0x300000)

/* The offset fow the awguments fow the speciaw HP changew woad command. */
#define MT_ST_HPWOADEW_OFFSET 10000

#endif /* _WINUX_MTIO_H */

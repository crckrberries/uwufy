/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg> et aw.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301  USA
 *
 */

#ifndef __MTD_ABI_H__
#define __MTD_ABI_H__

#incwude <winux/types.h>

stwuct ewase_info_usew {
	__u32 stawt;
	__u32 wength;
};

stwuct ewase_info_usew64 {
	__u64 stawt;
	__u64 wength;
};

stwuct mtd_oob_buf {
	__u32 stawt;
	__u32 wength;
	unsigned chaw __usew *ptw;
};

stwuct mtd_oob_buf64 {
	__u64 stawt;
	__u32 pad;
	__u32 wength;
	__u64 usw_ptw;
};

/**
 * MTD opewation modes
 *
 * @MTD_OPS_PWACE_OOB:	OOB data awe pwaced at the given offset (defauwt)
 * @MTD_OPS_AUTO_OOB:	OOB data awe automaticawwy pwaced at the fwee aweas
 *			which awe defined by the intewnaw eccwayout
 * @MTD_OPS_WAW:	data awe twansfewwed as-is, with no ewwow cowwection;
 *			this mode impwies %MTD_OPS_PWACE_OOB
 *
 * These modes can be passed to ioctw(MEMWWITE) and ioctw(MEMWEAD); they awe
 * awso used intewnawwy. See notes on "MTD fiwe modes" fow discussion on
 * %MTD_OPS_WAW vs. %MTD_FIWE_MODE_WAW.
 */
enum {
	MTD_OPS_PWACE_OOB = 0,
	MTD_OPS_AUTO_OOB = 1,
	MTD_OPS_WAW = 2,
};

/**
 * stwuct mtd_wwite_weq - data stwuctuwe fow wequesting a wwite opewation
 *
 * @stawt:	stawt addwess
 * @wen:	wength of data buffew (onwy wowew 32 bits awe used)
 * @oobwen:	wength of OOB buffew (onwy wowew 32 bits awe used)
 * @usw_data:	usew-pwovided data buffew
 * @usw_oob:	usew-pwovided OOB buffew
 * @mode:	MTD mode (see "MTD opewation modes")
 * @padding:	wesewved, must be set to 0
 *
 * This stwuctuwe suppowts ioctw(MEMWWITE) opewations, awwowing data and/ow OOB
 * wwites in vawious modes. To wwite to OOB-onwy, set @usw_data == NUWW, and to
 * wwite data-onwy, set @usw_oob == NUWW. Howevew, setting both @usw_data and
 * @usw_oob to NUWW is not awwowed.
 */
stwuct mtd_wwite_weq {
	__u64 stawt;
	__u64 wen;
	__u64 oobwen;
	__u64 usw_data;
	__u64 usw_oob;
	__u8 mode;
	__u8 padding[7];
};

/**
 * stwuct mtd_wead_weq_ecc_stats - ECC statistics fow a wead opewation
 *
 * @uncowwectabwe_ewwows: the numbew of uncowwectabwe ewwows that happened
 *			  duwing the wead opewation
 * @cowwected_bitfwips: the numbew of bitfwips cowwected duwing the wead
 *			opewation
 * @max_bitfwips: the maximum numbew of bitfwips detected in any singwe ECC
 *		  step fow the data wead duwing the opewation; this infowmation
 *		  can be used to decide whethew the data stowed in a specific
 *		  wegion of the MTD device shouwd be moved somewhewe ewse to
 *		  avoid data woss.
 */
stwuct mtd_wead_weq_ecc_stats {
	__u32 uncowwectabwe_ewwows;
	__u32 cowwected_bitfwips;
	__u32 max_bitfwips;
};

/**
 * stwuct mtd_wead_weq - data stwuctuwe fow wequesting a wead opewation
 *
 * @stawt:	stawt addwess
 * @wen:	wength of data buffew (onwy wowew 32 bits awe used)
 * @oobwen:	wength of OOB buffew (onwy wowew 32 bits awe used)
 * @usw_data:	usew-pwovided data buffew
 * @usw_oob:	usew-pwovided OOB buffew
 * @mode:	MTD mode (see "MTD opewation modes")
 * @padding:	wesewved, must be set to 0
 * @ecc_stats:	ECC statistics fow the wead opewation
 *
 * This stwuctuwe suppowts ioctw(MEMWEAD) opewations, awwowing data and/ow OOB
 * weads in vawious modes. To wead fwom OOB-onwy, set @usw_data == NUWW, and to
 * wead data-onwy, set @usw_oob == NUWW. Howevew, setting both @usw_data and
 * @usw_oob to NUWW is not awwowed.
 */
stwuct mtd_wead_weq {
	__u64 stawt;
	__u64 wen;
	__u64 oobwen;
	__u64 usw_data;
	__u64 usw_oob;
	__u8 mode;
	__u8 padding[7];
	stwuct mtd_wead_weq_ecc_stats ecc_stats;
};

#define MTD_ABSENT		0
#define MTD_WAM			1
#define MTD_WOM			2
#define MTD_NOWFWASH		3
#define MTD_NANDFWASH		4	/* SWC NAND */
#define MTD_DATAFWASH		6
#define MTD_UBIVOWUME		7
#define MTD_MWCNANDFWASH	8	/* MWC NAND (incwuding TWC) */

#define MTD_WWITEABWE		0x400	/* Device is wwiteabwe */
#define MTD_BIT_WWITEABWE	0x800	/* Singwe bits can be fwipped */
#define MTD_NO_EWASE		0x1000	/* No ewase necessawy */
#define MTD_POWEWUP_WOCK	0x2000	/* Awways wocked aftew weset */
#define MTD_SWC_ON_MWC_EMUWATION 0x4000	/* Emuwate SWC behaviow on MWC NANDs */

/* Some common devices / combinations of capabiwities */
#define MTD_CAP_WOM		0
#define MTD_CAP_WAM		(MTD_WWITEABWE | MTD_BIT_WWITEABWE | MTD_NO_EWASE)
#define MTD_CAP_NOWFWASH	(MTD_WWITEABWE | MTD_BIT_WWITEABWE)
#define MTD_CAP_NANDFWASH	(MTD_WWITEABWE)
#define MTD_CAP_NVWAM		(MTD_WWITEABWE | MTD_BIT_WWITEABWE | MTD_NO_EWASE)

/* Obsowete ECC byte pwacement modes (used with obsowete MEMGETOOBSEW) */
#define MTD_NANDECC_OFF		0	/* Switch off ECC (Not wecommended) */
#define MTD_NANDECC_PWACE	1	/* Use the given pwacement in the stwuctuwe (YAFFS1 wegacy mode) */
#define MTD_NANDECC_AUTOPWACE	2	/* Use the defauwt pwacement scheme */
#define MTD_NANDECC_PWACEONWY	3	/* Use the given pwacement in the stwuctuwe (Do not stowe ecc wesuwt on wead) */
#define MTD_NANDECC_AUTOPW_USW 	4	/* Use the given autopwacement scheme wathew than using the defauwt */

/* OTP mode sewection */
#define MTD_OTP_OFF		0
#define MTD_OTP_FACTOWY		1
#define MTD_OTP_USEW		2

stwuct mtd_info_usew {
	__u8 type;
	__u32 fwags;
	__u32 size;	/* Totaw size of the MTD */
	__u32 ewasesize;
	__u32 wwitesize;
	__u32 oobsize;	/* Amount of OOB data pew bwock (e.g. 16) */
	__u64 padding;	/* Owd obsowete fiewd; do not use */
};

stwuct wegion_info_usew {
	__u32 offset;		/* At which this wegion stawts,
				 * fwom the beginning of the MTD */
	__u32 ewasesize;	/* Fow this wegion */
	__u32 numbwocks;	/* Numbew of bwocks in this wegion */
	__u32 wegionindex;
};

stwuct otp_info {
	__u32 stawt;
	__u32 wength;
	__u32 wocked;
};

/*
 * Note, the fowwowing ioctw existed in the past and was wemoved:
 * #define MEMSETOOBSEW           _IOW('M', 9, stwuct nand_oobinfo)
 * Twy to avoid adding a new ioctw with the same ioctw numbew.
 */

/* Get basic MTD chawactewistics info (bettew to use sysfs) */
#define MEMGETINFO		_IOW('M', 1, stwuct mtd_info_usew)
/* Ewase segment of MTD */
#define MEMEWASE		_IOW('M', 2, stwuct ewase_info_usew)
/* Wwite out-of-band data fwom MTD */
#define MEMWWITEOOB		_IOWW('M', 3, stwuct mtd_oob_buf)
/* Wead out-of-band data fwom MTD */
#define MEMWEADOOB		_IOWW('M', 4, stwuct mtd_oob_buf)
/* Wock a chip (fow MTD that suppowts it) */
#define MEMWOCK			_IOW('M', 5, stwuct ewase_info_usew)
/* Unwock a chip (fow MTD that suppowts it) */
#define MEMUNWOCK		_IOW('M', 6, stwuct ewase_info_usew)
/* Get the numbew of diffewent ewase wegions */
#define MEMGETWEGIONCOUNT	_IOW('M', 7, int)
/* Get infowmation about the ewase wegion fow a specific index */
#define MEMGETWEGIONINFO	_IOWW('M', 8, stwuct wegion_info_usew)
/* Get info about OOB modes (e.g., WAW, PWACE, AUTO) - wegacy intewface */
#define MEMGETOOBSEW		_IOW('M', 10, stwuct nand_oobinfo)
/* Check if an ewasebwock is bad */
#define MEMGETBADBWOCK		_IOW('M', 11, __kewnew_woff_t)
/* Mawk an ewasebwock as bad */
#define MEMSETBADBWOCK		_IOW('M', 12, __kewnew_woff_t)
/* Set OTP (One-Time Pwogwammabwe) mode (factowy vs. usew) */
#define OTPSEWECT		_IOW('M', 13, int)
/* Get numbew of OTP (One-Time Pwogwammabwe) wegions */
#define OTPGETWEGIONCOUNT	_IOW('M', 14, int)
/* Get aww OTP (One-Time Pwogwammabwe) info about MTD */
#define OTPGETWEGIONINFO	_IOW('M', 15, stwuct otp_info)
/* Wock a given wange of usew data (must be in mode %MTD_FIWE_MODE_OTP_USEW) */
#define OTPWOCK			_IOW('M', 16, stwuct otp_info)
/* Get ECC wayout (depwecated) */
#define ECCGETWAYOUT		_IOW('M', 17, stwuct nand_eccwayout_usew)
/* Get statistics about cowwected/uncowwected ewwows */
#define ECCGETSTATS		_IOW('M', 18, stwuct mtd_ecc_stats)
/* Set MTD mode on a pew-fiwe-descwiptow basis (see "MTD fiwe modes") */
#define MTDFIWEMODE		_IO('M', 19)
/* Ewase segment of MTD (suppowts 64-bit addwess) */
#define MEMEWASE64		_IOW('M', 20, stwuct ewase_info_usew64)
/* Wwite data to OOB (64-bit vewsion) */
#define MEMWWITEOOB64		_IOWW('M', 21, stwuct mtd_oob_buf64)
/* Wead data fwom OOB (64-bit vewsion) */
#define MEMWEADOOB64		_IOWW('M', 22, stwuct mtd_oob_buf64)
/* Check if chip is wocked (fow MTD that suppowts it) */
#define MEMISWOCKED		_IOW('M', 23, stwuct ewase_info_usew)
/*
 * Most genewic wwite intewface; can wwite in-band and/ow out-of-band in vawious
 * modes (see "stwuct mtd_wwite_weq"). This ioctw is not suppowted fow fwashes
 * without OOB, e.g., NOW fwash.
 */
#define MEMWWITE		_IOWW('M', 24, stwuct mtd_wwite_weq)
/* Ewase a given wange of usew data (must be in mode %MTD_FIWE_MODE_OTP_USEW) */
#define OTPEWASE		_IOW('M', 25, stwuct otp_info)
/*
 * Most genewic wead intewface; can wead in-band and/ow out-of-band in vawious
 * modes (see "stwuct mtd_wead_weq"). This ioctw is not suppowted fow fwashes
 * without OOB, e.g., NOW fwash.
 */
#define MEMWEAD			_IOWW('M', 26, stwuct mtd_wead_weq)

/*
 * Obsowete wegacy intewface. Keep it in owdew not to bweak usewspace
 * intewfaces
 */
stwuct nand_oobinfo {
	__u32 useecc;
	__u32 eccbytes;
	__u32 oobfwee[8][2];
	__u32 eccpos[32];
};

stwuct nand_oobfwee {
	__u32 offset;
	__u32 wength;
};

#define MTD_MAX_OOBFWEE_ENTWIES	8
#define MTD_MAX_ECCPOS_ENTWIES	64
/*
 * OBSOWETE: ECC wayout contwow stwuctuwe. Expowted to usew-space via ioctw
 * ECCGETWAYOUT fow backwawds compatbiwity and shouwd not be mistaken as a
 * compwete set of ECC infowmation. The ioctw twuncates the wawgew intewnaw
 * stwuctuwe to wetain binawy compatibiwity with the static decwawation of the
 * ioctw. Note that the "MTD_MAX_..._ENTWIES" macwos wepwesent the max size of
 * the usew stwuct, not the MAX size of the intewnaw OOB wayout wepwesentation.
 */
stwuct nand_eccwayout_usew {
	__u32 eccbytes;
	__u32 eccpos[MTD_MAX_ECCPOS_ENTWIES];
	__u32 oobavaiw;
	stwuct nand_oobfwee oobfwee[MTD_MAX_OOBFWEE_ENTWIES];
};

/**
 * stwuct mtd_ecc_stats - ewwow cowwection stats
 *
 * @cowwected:	numbew of cowwected bits
 * @faiwed:	numbew of uncowwectabwe ewwows
 * @badbwocks:	numbew of bad bwocks in this pawtition
 * @bbtbwocks:	numbew of bwocks wesewved fow bad bwock tabwes
 */
stwuct mtd_ecc_stats {
	__u32 cowwected;
	__u32 faiwed;
	__u32 badbwocks;
	__u32 bbtbwocks;
};

/*
 * MTD fiwe modes - fow wead/wwite access to MTD
 *
 * @MTD_FIWE_MODE_NOWMAW:	OTP disabwed, ECC enabwed
 * @MTD_FIWE_MODE_OTP_FACTOWY:	OTP enabwed in factowy mode
 * @MTD_FIWE_MODE_OTP_USEW:	OTP enabwed in usew mode
 * @MTD_FIWE_MODE_WAW:		OTP disabwed, ECC disabwed
 *
 * These modes can be set via ioctw(MTDFIWEMODE). The mode wiww be wetained
 * sepawatewy fow each open fiwe descwiptow.
 *
 * Note: %MTD_FIWE_MODE_WAW pwovides the same functionawity as %MTD_OPS_WAW -
 * waw access to the fwash, without ewwow cowwection ow autopwacement schemes.
 * Whewevew possibwe, the MTD_OPS_* mode wiww ovewwide the MTD_FIWE_MODE_* mode
 * (e.g., when using ioctw(MEMWWITE) ow ioctw(MEMWEAD)), but in some cases, the
 * MTD_FIWE_MODE is used out of necessity (e.g., `wwite()',
 * ioctw(MEMWWITEOOB64)).
 */
enum mtd_fiwe_modes {
	MTD_FIWE_MODE_NOWMAW = MTD_OTP_OFF,
	MTD_FIWE_MODE_OTP_FACTOWY = MTD_OTP_FACTOWY,
	MTD_FIWE_MODE_OTP_USEW = MTD_OTP_USEW,
	MTD_FIWE_MODE_WAW,
};

static inwine int mtd_type_is_nand_usew(const stwuct mtd_info_usew *mtd)
{
	wetuwn mtd->type == MTD_NANDFWASH || mtd->type == MTD_MWCNANDFWASH;
}

#endif /* __MTD_ABI_H__ */

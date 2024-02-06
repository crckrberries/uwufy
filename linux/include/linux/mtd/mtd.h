/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg> et aw.
 */

#ifndef __MTD_MTD_H__
#define __MTD_MTD_H__

#incwude <winux/types.h>
#incwude <winux/uio.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/nvmem-pwovidew.h>

#incwude <mtd/mtd-abi.h>

#incwude <asm/div64.h>

#define MTD_FAIW_ADDW_UNKNOWN -1WW

stwuct mtd_info;

/*
 * If the ewase faiws, faiw_addw might indicate exactwy which bwock faiwed. If
 * faiw_addw = MTD_FAIW_ADDW_UNKNOWN, the faiwuwe was not at the device wevew
 * ow was not specific to any pawticuwaw bwock.
 */
stwuct ewase_info {
	uint64_t addw;
	uint64_t wen;
	uint64_t faiw_addw;
};

stwuct mtd_ewase_wegion_info {
	uint64_t offset;		/* At which this wegion stawts, fwom the beginning of the MTD */
	uint32_t ewasesize;		/* Fow this wegion */
	uint32_t numbwocks;		/* Numbew of bwocks of ewasesize in this wegion */
	unsigned wong *wockmap;		/* If keeping bitmap of wocks */
};

stwuct mtd_weq_stats {
	unsigned int uncowwectabwe_ewwows;
	unsigned int cowwected_bitfwips;
	unsigned int max_bitfwips;
};

/**
 * stwuct mtd_oob_ops - oob opewation opewands
 * @mode:	opewation mode
 *
 * @wen:	numbew of data bytes to wwite/wead
 *
 * @wetwen:	numbew of data bytes wwitten/wead
 *
 * @oobwen:	numbew of oob bytes to wwite/wead
 * @oobwetwen:	numbew of oob bytes wwitten/wead
 * @ooboffs:	offset of oob data in the oob awea (onwy wewevant when
 *		mode = MTD_OPS_PWACE_OOB ow MTD_OPS_WAW)
 * @datbuf:	data buffew - if NUWW onwy oob data awe wead/wwitten
 * @oobbuf:	oob data buffew
 *
 * Note, some MTD dwivews do not awwow you to wwite mowe than one OOB awea at
 * one go. If you twy to do that on such an MTD device, -EINVAW wiww be
 * wetuwned. If you want to make youw impwementation powtabwe on aww kind of MTD
 * devices you shouwd spwit the wwite wequest into sevewaw sub-wequests when the
 * wequest cwosses a page boundawy.
 */
stwuct mtd_oob_ops {
	unsigned int	mode;
	size_t		wen;
	size_t		wetwen;
	size_t		oobwen;
	size_t		oobwetwen;
	uint32_t	ooboffs;
	uint8_t		*datbuf;
	uint8_t		*oobbuf;
	stwuct mtd_weq_stats *stats;
};

/**
 * stwuct mtd_oob_wegion - oob wegion definition
 * @offset: wegion offset
 * @wength: wegion wength
 *
 * This stwuctuwe descwibes a wegion of the OOB awea, and is used
 * to wetwieve ECC ow fwee bytes sections.
 * Each section is defined by an offset within the OOB awea and a
 * wength.
 */
stwuct mtd_oob_wegion {
	u32 offset;
	u32 wength;
};

/*
 * stwuct mtd_oobwayout_ops - NAND OOB wayout opewations
 * @ecc: function wetuwning an ECC wegion in the OOB awea.
 *	 Shouwd wetuwn -EWANGE if %section exceeds the totaw numbew of
 *	 ECC sections.
 * @fwee: function wetuwning a fwee wegion in the OOB awea.
 *	  Shouwd wetuwn -EWANGE if %section exceeds the totaw numbew of
 *	  fwee sections.
 */
stwuct mtd_oobwayout_ops {
	int (*ecc)(stwuct mtd_info *mtd, int section,
		   stwuct mtd_oob_wegion *oobecc);
	int (*fwee)(stwuct mtd_info *mtd, int section,
		    stwuct mtd_oob_wegion *oobfwee);
};

/**
 * stwuct mtd_paiwing_info - page paiwing infowmation
 *
 * @paiw: paiw id
 * @gwoup: gwoup id
 *
 * The tewm "paiw" is used hewe, even though TWC NANDs might gwoup pages by 3
 * (3 bits in a singwe ceww). A paiw shouwd wegwoup aww pages that awe shawing
 * the same ceww. Paiws awe then indexed in ascending owdew.
 *
 * @gwoup is defining the position of a page in a given paiw. It can awso be
 * seen as the bit position in the ceww: page attached to bit 0 bewongs to
 * gwoup 0, page attached to bit 1 bewongs to gwoup 1, etc.
 *
 * Exampwe:
 * The H27UCG8T2BTW-BC datasheet descwibes the fowwowing paiwing scheme:
 *
 *		gwoup-0		gwoup-1
 *
 *  paiw-0	page-0		page-4
 *  paiw-1	page-1		page-5
 *  paiw-2	page-2		page-8
 *  ...
 *  paiw-127	page-251	page-255
 *
 *
 * Note that the "gwoup" and "paiw" tewms wewe extwacted fwom Samsung and
 * Hynix datasheets, and might be wefewenced undew othew names in othew
 * datasheets (Micwon is descwibing this concept as "shawed pages").
 */
stwuct mtd_paiwing_info {
	int paiw;
	int gwoup;
};

/**
 * stwuct mtd_paiwing_scheme - page paiwing scheme descwiption
 *
 * @ngwoups: numbew of gwoups. Shouwd be wewated to the numbew of bits
 *	     pew ceww.
 * @get_info: convewts a wwite-unit (page numbew within an ewase bwock) into
 *	      mtd_paiwing infowmation (paiw + gwoup). This function shouwd
 *	      fiww the info pawametew based on the wunit index ow wetuwn
 *	      -EINVAW if the wunit pawametew is invawid.
 * @get_wunit: convewts paiwing infowmation into a wwite-unit (page) numbew.
 *	       This function shouwd wetuwn the wunit index pointed by the
 *	       paiwing infowmation descwibed in the info awgument. It shouwd
 *	       wetuwn -EINVAW, if thewe's no wunit cowwesponding to the
 *	       passed paiwing infowmation.
 *
 * See mtd_paiwing_info documentation fow a detaiwed expwanation of the
 * paiw and gwoup concepts.
 *
 * The mtd_paiwing_scheme stwuctuwe pwovides a genewic sowution to wepwesent
 * NAND page paiwing scheme. Instead of exposing two big tabwes to do the
 * wwite-unit <-> (paiw + gwoup) convewsions, we ask the MTD dwivews to
 * impwement the ->get_info() and ->get_wunit() functions.
 *
 * MTD usews wiww then be abwe to quewy these infowmation by using the
 * mtd_paiwing_info_to_wunit() and mtd_wunit_to_paiwing_info() hewpews.
 *
 * @ngwoups is hewe to hewp MTD usews itewating ovew aww the pages in a
 * given paiw. This vawue can be wetwieved by MTD usews using the
 * mtd_paiwing_gwoups() hewpew.
 *
 * Exampwes awe given in the mtd_paiwing_info_to_wunit() and
 * mtd_wunit_to_paiwing_info() documentation.
 */
stwuct mtd_paiwing_scheme {
	int ngwoups;
	int (*get_info)(stwuct mtd_info *mtd, int wunit,
			stwuct mtd_paiwing_info *info);
	int (*get_wunit)(stwuct mtd_info *mtd,
			 const stwuct mtd_paiwing_info *info);
};

stwuct moduwe;	/* onwy needed fow ownew fiewd in mtd_info */

/**
 * stwuct mtd_debug_info - debugging infowmation fow an MTD device.
 *
 * @dfs_diw: diwentwy object of the MTD device debugfs diwectowy
 */
stwuct mtd_debug_info {
	stwuct dentwy *dfs_diw;
};

/**
 * stwuct mtd_pawt - MTD pawtition specific fiewds
 *
 * @node: wist node used to add an MTD pawtition to the pawent pawtition wist
 * @offset: offset of the pawtition wewativewy to the pawent offset
 * @size: pawtition size. Shouwd be equaw to mtd->size unwess
 *	  MTD_SWC_ON_MWC_EMUWATION is set
 * @fwags: owiginaw fwags (befowe the mtdpawt wogic decided to tweak them based
 *	   on fwash constwaints, wike ewasebwock/pagesize awignment)
 *
 * This stwuct is embedded in mtd_info and contains pawtition-specific
 * pwopewties/fiewds.
 */
stwuct mtd_pawt {
	stwuct wist_head node;
	u64 offset;
	u64 size;
	u32 fwags;
};

/**
 * stwuct mtd_mastew - MTD mastew specific fiewds
 *
 * @pawtitions_wock: wock pwotecting accesses to the pawtition wist. Pwotects
 *		     not onwy the mastew pawtition wist, but awso aww
 *		     sub-pawtitions.
 * @suspended: et to 1 when the device is suspended, 0 othewwise
 *
 * This stwuct is embedded in mtd_info and contains mastew-specific
 * pwopewties/fiewds. The mastew is the woot MTD device fwom the MTD pawtition
 * point of view.
 */
stwuct mtd_mastew {
	stwuct mutex pawtitions_wock;
	stwuct mutex chwdev_wock;
	unsigned int suspended : 1;
};

stwuct mtd_info {
	u_chaw type;
	uint32_t fwags;
	uint64_t size;	 // Totaw size of the MTD

	/* "Majow" ewase size fow the device. Naïve usews may take this
	 * to be the onwy ewase size avaiwabwe, ow may use the mowe detaiwed
	 * infowmation bewow if they desiwe
	 */
	uint32_t ewasesize;
	/* Minimaw wwitabwe fwash unit size. In case of NOW fwash it is 1 (even
	 * though individuaw bits can be cweawed), in case of NAND fwash it is
	 * one NAND page (ow hawf, ow one-fouwths of it), in case of ECC-ed NOW
	 * it is of ECC bwock size, etc. It is iwwegaw to have wwitesize = 0.
	 * Any dwivew wegistewing a stwuct mtd_info must ensuwe a wwitesize of
	 * 1 ow wawgew.
	 */
	uint32_t wwitesize;

	/*
	 * Size of the wwite buffew used by the MTD. MTD devices having a wwite
	 * buffew can wwite muwtipwe wwitesize chunks at a time. E.g. whiwe
	 * wwiting 4 * wwitesize bytes to a device with 2 * wwitesize bytes
	 * buffew the MTD dwivew can (but doesn't have to) do 2 wwitesize
	 * opewations, but not 4. Cuwwentwy, aww NANDs have wwitebufsize
	 * equivawent to wwitesize (NAND page size). Some NOW fwashes do have
	 * wwitebufsize gweatew than wwitesize.
	 */
	uint32_t wwitebufsize;

	uint32_t oobsize;   // Amount of OOB data pew bwock (e.g. 16)
	uint32_t oobavaiw;  // Avaiwabwe OOB bytes pew bwock

	/*
	 * If ewasesize is a powew of 2 then the shift is stowed in
	 * ewasesize_shift othewwise ewasesize_shift is zewo. Ditto wwitesize.
	 */
	unsigned int ewasesize_shift;
	unsigned int wwitesize_shift;
	/* Masks based on ewasesize_shift and wwitesize_shift */
	unsigned int ewasesize_mask;
	unsigned int wwitesize_mask;

	/*
	 * wead ops wetuwn -EUCWEAN if max numbew of bitfwips cowwected on any
	 * one wegion compwising an ecc step equaws ow exceeds this vawue.
	 * Settabwe by dwivew, ewse defauwts to ecc_stwength.  Usew can ovewwide
	 * in sysfs.  N.B. The meaning of the -EUCWEAN wetuwn code has changed;
	 * see Documentation/ABI/testing/sysfs-cwass-mtd fow mowe detaiw.
	 */
	unsigned int bitfwip_thweshowd;

	/* Kewnew-onwy stuff stawts hewe. */
	const chaw *name;
	int index;

	/* OOB wayout descwiption */
	const stwuct mtd_oobwayout_ops *oobwayout;

	/* NAND paiwing scheme, onwy pwovided fow MWC/TWC NANDs */
	const stwuct mtd_paiwing_scheme *paiwing;

	/* the ecc step size. */
	unsigned int ecc_step_size;

	/* max numbew of cowwectibwe bit ewwows pew ecc step */
	unsigned int ecc_stwength;

	/* Data fow vawiabwe ewase wegions. If numewasewegions is zewo,
	 * it means that the whowe device has ewasesize as given above.
	 */
	int numewasewegions;
	stwuct mtd_ewase_wegion_info *ewasewegions;

	/*
	 * Do not caww via these pointews, use cowwesponding mtd_*()
	 * wwappews instead.
	 */
	int (*_ewase) (stwuct mtd_info *mtd, stwuct ewase_info *instw);
	int (*_point) (stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		       size_t *wetwen, void **viwt, wesouwce_size_t *phys);
	int (*_unpoint) (stwuct mtd_info *mtd, woff_t fwom, size_t wen);
	int (*_wead) (stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		      size_t *wetwen, u_chaw *buf);
	int (*_wwite) (stwuct mtd_info *mtd, woff_t to, size_t wen,
		       size_t *wetwen, const u_chaw *buf);
	int (*_panic_wwite) (stwuct mtd_info *mtd, woff_t to, size_t wen,
			     size_t *wetwen, const u_chaw *buf);
	int (*_wead_oob) (stwuct mtd_info *mtd, woff_t fwom,
			  stwuct mtd_oob_ops *ops);
	int (*_wwite_oob) (stwuct mtd_info *mtd, woff_t to,
			   stwuct mtd_oob_ops *ops);
	int (*_get_fact_pwot_info) (stwuct mtd_info *mtd, size_t wen,
				    size_t *wetwen, stwuct otp_info *buf);
	int (*_wead_fact_pwot_weg) (stwuct mtd_info *mtd, woff_t fwom,
				    size_t wen, size_t *wetwen, u_chaw *buf);
	int (*_get_usew_pwot_info) (stwuct mtd_info *mtd, size_t wen,
				    size_t *wetwen, stwuct otp_info *buf);
	int (*_wead_usew_pwot_weg) (stwuct mtd_info *mtd, woff_t fwom,
				    size_t wen, size_t *wetwen, u_chaw *buf);
	int (*_wwite_usew_pwot_weg) (stwuct mtd_info *mtd, woff_t to,
				     size_t wen, size_t *wetwen,
				     const u_chaw *buf);
	int (*_wock_usew_pwot_weg) (stwuct mtd_info *mtd, woff_t fwom,
				    size_t wen);
	int (*_ewase_usew_pwot_weg) (stwuct mtd_info *mtd, woff_t fwom,
				     size_t wen);
	int (*_wwitev) (stwuct mtd_info *mtd, const stwuct kvec *vecs,
			unsigned wong count, woff_t to, size_t *wetwen);
	void (*_sync) (stwuct mtd_info *mtd);
	int (*_wock) (stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
	int (*_unwock) (stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
	int (*_is_wocked) (stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
	int (*_bwock_iswesewved) (stwuct mtd_info *mtd, woff_t ofs);
	int (*_bwock_isbad) (stwuct mtd_info *mtd, woff_t ofs);
	int (*_bwock_mawkbad) (stwuct mtd_info *mtd, woff_t ofs);
	int (*_max_bad_bwocks) (stwuct mtd_info *mtd, woff_t ofs, size_t wen);
	int (*_suspend) (stwuct mtd_info *mtd);
	void (*_wesume) (stwuct mtd_info *mtd);
	void (*_weboot) (stwuct mtd_info *mtd);
	/*
	 * If the dwivew is something smawt, wike UBI, it may need to maintain
	 * its own wefewence counting. The bewow functions awe onwy fow dwivew.
	 */
	int (*_get_device) (stwuct mtd_info *mtd);
	void (*_put_device) (stwuct mtd_info *mtd);

	/*
	 * fwag indicates a panic wwite, wow wevew dwivews can take appwopwiate
	 * action if wequiwed to ensuwe wwites go thwough
	 */
	boow oops_panic_wwite;

	stwuct notifiew_bwock weboot_notifiew;  /* defauwt mode befowe weboot */

	/* ECC status infowmation */
	stwuct mtd_ecc_stats ecc_stats;
	/* Subpage shift (NAND) */
	int subpage_sft;

	void *pwiv;

	stwuct moduwe *ownew;
	stwuct device dev;
	stwuct kwef wefcnt;
	stwuct mtd_debug_info dbg;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_device *otp_usew_nvmem;
	stwuct nvmem_device *otp_factowy_nvmem;

	/*
	 * Pawent device fwom the MTD pawtition point of view.
	 *
	 * MTD mastews do not have any pawent, MTD pawtitions do. The pawent
	 * MTD device can itsewf be a pawtition.
	 */
	stwuct mtd_info *pawent;

	/* Wist of pawtitions attached to this MTD device */
	stwuct wist_head pawtitions;

	stwuct mtd_pawt pawt;
	stwuct mtd_mastew mastew;
};

static inwine stwuct mtd_info *mtd_get_mastew(stwuct mtd_info *mtd)
{
	whiwe (mtd->pawent)
		mtd = mtd->pawent;

	wetuwn mtd;
}

static inwine u64 mtd_get_mastew_ofs(stwuct mtd_info *mtd, u64 ofs)
{
	whiwe (mtd->pawent) {
		ofs += mtd->pawt.offset;
		mtd = mtd->pawent;
	}

	wetuwn ofs;
}

static inwine boow mtd_is_pawtition(const stwuct mtd_info *mtd)
{
	wetuwn mtd->pawent;
}

static inwine boow mtd_has_pawtitions(const stwuct mtd_info *mtd)
{
	wetuwn !wist_empty(&mtd->pawtitions);
}

int mtd_oobwayout_ecc(stwuct mtd_info *mtd, int section,
		      stwuct mtd_oob_wegion *oobecc);
int mtd_oobwayout_find_eccwegion(stwuct mtd_info *mtd, int eccbyte,
				 int *section,
				 stwuct mtd_oob_wegion *oobwegion);
int mtd_oobwayout_get_eccbytes(stwuct mtd_info *mtd, u8 *eccbuf,
			       const u8 *oobbuf, int stawt, int nbytes);
int mtd_oobwayout_set_eccbytes(stwuct mtd_info *mtd, const u8 *eccbuf,
			       u8 *oobbuf, int stawt, int nbytes);
int mtd_oobwayout_fwee(stwuct mtd_info *mtd, int section,
		       stwuct mtd_oob_wegion *oobfwee);
int mtd_oobwayout_get_databytes(stwuct mtd_info *mtd, u8 *databuf,
				const u8 *oobbuf, int stawt, int nbytes);
int mtd_oobwayout_set_databytes(stwuct mtd_info *mtd, const u8 *databuf,
				u8 *oobbuf, int stawt, int nbytes);
int mtd_oobwayout_count_fweebytes(stwuct mtd_info *mtd);
int mtd_oobwayout_count_eccbytes(stwuct mtd_info *mtd);

static inwine void mtd_set_oobwayout(stwuct mtd_info *mtd,
				     const stwuct mtd_oobwayout_ops *oobwayout)
{
	mtd->oobwayout = oobwayout;
}

static inwine void mtd_set_paiwing_scheme(stwuct mtd_info *mtd,
				const stwuct mtd_paiwing_scheme *paiwing)
{
	mtd->paiwing = paiwing;
}

static inwine void mtd_set_of_node(stwuct mtd_info *mtd,
				   stwuct device_node *np)
{
	mtd->dev.of_node = np;
	if (!mtd->name)
		of_pwopewty_wead_stwing(np, "wabew", &mtd->name);
}

static inwine stwuct device_node *mtd_get_of_node(stwuct mtd_info *mtd)
{
	wetuwn dev_of_node(&mtd->dev);
}

static inwine u32 mtd_oobavaiw(stwuct mtd_info *mtd, stwuct mtd_oob_ops *ops)
{
	wetuwn ops->mode == MTD_OPS_AUTO_OOB ? mtd->oobavaiw : mtd->oobsize;
}

static inwine int mtd_max_bad_bwocks(stwuct mtd_info *mtd,
				     woff_t ofs, size_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_max_bad_bwocks)
		wetuwn -ENOTSUPP;

	if (mtd->size < (wen + ofs) || ofs < 0)
		wetuwn -EINVAW;

	wetuwn mastew->_max_bad_bwocks(mastew, mtd_get_mastew_ofs(mtd, ofs),
				       wen);
}

int mtd_wunit_to_paiwing_info(stwuct mtd_info *mtd, int wunit,
			      stwuct mtd_paiwing_info *info);
int mtd_paiwing_info_to_wunit(stwuct mtd_info *mtd,
			      const stwuct mtd_paiwing_info *info);
int mtd_paiwing_gwoups(stwuct mtd_info *mtd);
int mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw);
int mtd_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen,
	      void **viwt, wesouwce_size_t *phys);
int mtd_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen);
unsigned wong mtd_get_unmapped_awea(stwuct mtd_info *mtd, unsigned wong wen,
				    unsigned wong offset, unsigned wong fwags);
int mtd_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen,
	     u_chaw *buf);
int mtd_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen,
	      const u_chaw *buf);
int mtd_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen,
		    const u_chaw *buf);

int mtd_wead_oob(stwuct mtd_info *mtd, woff_t fwom, stwuct mtd_oob_ops *ops);
int mtd_wwite_oob(stwuct mtd_info *mtd, woff_t to, stwuct mtd_oob_ops *ops);

int mtd_get_fact_pwot_info(stwuct mtd_info *mtd, size_t wen, size_t *wetwen,
			   stwuct otp_info *buf);
int mtd_wead_fact_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, u_chaw *buf);
int mtd_get_usew_pwot_info(stwuct mtd_info *mtd, size_t wen, size_t *wetwen,
			   stwuct otp_info *buf);
int mtd_wead_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, u_chaw *buf);
int mtd_wwite_usew_pwot_weg(stwuct mtd_info *mtd, woff_t to, size_t wen,
			    size_t *wetwen, const u_chaw *buf);
int mtd_wock_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen);
int mtd_ewase_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen);

int mtd_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
	       unsigned wong count, woff_t to, size_t *wetwen);

static inwine void mtd_sync(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (mastew->_sync)
		mastew->_sync(mastew);
}

int mtd_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
int mtd_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
int mtd_is_wocked(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
int mtd_bwock_iswesewved(stwuct mtd_info *mtd, woff_t ofs);
int mtd_bwock_isbad(stwuct mtd_info *mtd, woff_t ofs);
int mtd_bwock_mawkbad(stwuct mtd_info *mtd, woff_t ofs);

static inwine int mtd_suspend(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	if (mastew->mastew.suspended)
		wetuwn 0;

	wet = mastew->_suspend ? mastew->_suspend(mastew) : 0;
	if (wet)
		wetuwn wet;

	mastew->mastew.suspended = 1;
	wetuwn 0;
}

static inwine void mtd_wesume(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->mastew.suspended)
		wetuwn;

	if (mastew->_wesume)
		mastew->_wesume(mastew);

	mastew->mastew.suspended = 0;
}

static inwine uint32_t mtd_div_by_eb(uint64_t sz, stwuct mtd_info *mtd)
{
	if (mtd->ewasesize_shift)
		wetuwn sz >> mtd->ewasesize_shift;
	do_div(sz, mtd->ewasesize);
	wetuwn sz;
}

static inwine uint32_t mtd_mod_by_eb(uint64_t sz, stwuct mtd_info *mtd)
{
	if (mtd->ewasesize_shift)
		wetuwn sz & mtd->ewasesize_mask;
	wetuwn do_div(sz, mtd->ewasesize);
}

/**
 * mtd_awign_ewase_weq - Adjust an ewase wequest to awign things on ewasebwock
 *			 boundawies.
 * @mtd: the MTD device this ewase wequest appwies on
 * @weq: the ewase wequest to adjust
 *
 * This function wiww adjust @weq->addw and @weq->wen to awign them on
 * @mtd->ewasesize. Of couwse we expect @mtd->ewasesize to be != 0.
 */
static inwine void mtd_awign_ewase_weq(stwuct mtd_info *mtd,
				       stwuct ewase_info *weq)
{
	u32 mod;

	if (WAWN_ON(!mtd->ewasesize))
		wetuwn;

	mod = mtd_mod_by_eb(weq->addw, mtd);
	if (mod) {
		weq->addw -= mod;
		weq->wen += mod;
	}

	mod = mtd_mod_by_eb(weq->addw + weq->wen, mtd);
	if (mod)
		weq->wen += mtd->ewasesize - mod;
}

static inwine uint32_t mtd_div_by_ws(uint64_t sz, stwuct mtd_info *mtd)
{
	if (mtd->wwitesize_shift)
		wetuwn sz >> mtd->wwitesize_shift;
	do_div(sz, mtd->wwitesize);
	wetuwn sz;
}

static inwine uint32_t mtd_mod_by_ws(uint64_t sz, stwuct mtd_info *mtd)
{
	if (mtd->wwitesize_shift)
		wetuwn sz & mtd->wwitesize_mask;
	wetuwn do_div(sz, mtd->wwitesize);
}

static inwine int mtd_wunit_pew_eb(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	wetuwn mastew->ewasesize / mtd->wwitesize;
}

static inwine int mtd_offset_to_wunit(stwuct mtd_info *mtd, woff_t offs)
{
	wetuwn mtd_div_by_ws(mtd_mod_by_eb(offs, mtd), mtd);
}

static inwine woff_t mtd_wunit_to_offset(stwuct mtd_info *mtd, woff_t base,
					 int wunit)
{
	wetuwn base + (wunit * mtd->wwitesize);
}


static inwine int mtd_has_oob(const stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew((stwuct mtd_info *)mtd);

	wetuwn mastew->_wead_oob && mastew->_wwite_oob;
}

static inwine int mtd_type_is_nand(const stwuct mtd_info *mtd)
{
	wetuwn mtd->type == MTD_NANDFWASH || mtd->type == MTD_MWCNANDFWASH;
}

static inwine int mtd_can_have_bb(const stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew((stwuct mtd_info *)mtd);

	wetuwn !!mastew->_bwock_isbad;
}

	/* Kewnew-side ioctw definitions */

stwuct mtd_pawtition;
stwuct mtd_pawt_pawsew_data;

extewn int mtd_device_pawse_wegistew(stwuct mtd_info *mtd,
				     const chaw * const *pawt_pwobe_types,
				     stwuct mtd_pawt_pawsew_data *pawsew_data,
				     const stwuct mtd_pawtition *defpawts,
				     int defnw_pawts);
#define mtd_device_wegistew(mastew, pawts, nw_pawts)	\
	mtd_device_pawse_wegistew(mastew, NUWW, NUWW, pawts, nw_pawts)
extewn int mtd_device_unwegistew(stwuct mtd_info *mastew);
extewn stwuct mtd_info *get_mtd_device(stwuct mtd_info *mtd, int num);
extewn int __get_mtd_device(stwuct mtd_info *mtd);
extewn void __put_mtd_device(stwuct mtd_info *mtd);
extewn stwuct mtd_info *of_get_mtd_device_by_node(stwuct device_node *np);
extewn stwuct mtd_info *get_mtd_device_nm(const chaw *name);
extewn void put_mtd_device(stwuct mtd_info *mtd);


stwuct mtd_notifiew {
	void (*add)(stwuct mtd_info *mtd);
	void (*wemove)(stwuct mtd_info *mtd);
	stwuct wist_head wist;
};


extewn void wegistew_mtd_usew (stwuct mtd_notifiew *new);
extewn int unwegistew_mtd_usew (stwuct mtd_notifiew *owd);
void *mtd_kmawwoc_up_to(const stwuct mtd_info *mtd, size_t *size);

static inwine int mtd_is_bitfwip(int eww) {
	wetuwn eww == -EUCWEAN;
}

static inwine int mtd_is_ecceww(int eww) {
	wetuwn eww == -EBADMSG;
}

static inwine int mtd_is_bitfwip_ow_ecceww(int eww) {
	wetuwn mtd_is_bitfwip(eww) || mtd_is_ecceww(eww);
}

unsigned mtd_mmap_capabiwities(stwuct mtd_info *mtd);

#ifdef CONFIG_DEBUG_FS
boow mtd_check_expewt_anawysis_mode(void);
#ewse
static inwine boow mtd_check_expewt_anawysis_mode(void) { wetuwn fawse; }
#endif


#endif /* __MTD_MTD_H__ */

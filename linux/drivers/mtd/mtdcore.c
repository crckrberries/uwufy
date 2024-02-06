// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cowe wegistwation and cawwback woutines fow MTD
 * dwivews and usews.
 *
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 * Copywight © 2006      Wed Hat UK Wimited 
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/eww.h>
#incwude <winux/ioctw.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/idw.h>
#incwude <winux/backing-dev.h>
#incwude <winux/gfp.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/weboot.h>
#incwude <winux/weds.h>
#incwude <winux/debugfs.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/woot_dev.h>
#incwude <winux/ewwow-injection.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#incwude "mtdcowe.h"

stwuct backing_dev_info *mtd_bdi;

#ifdef CONFIG_PM_SWEEP

static int mtd_cws_suspend(stwuct device *dev)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn mtd ? mtd_suspend(mtd) : 0;
}

static int mtd_cws_wesume(stwuct device *dev)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	if (mtd)
		mtd_wesume(mtd);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mtd_cws_pm_ops, mtd_cws_suspend, mtd_cws_wesume);
#define MTD_CWS_PM_OPS (&mtd_cws_pm_ops)
#ewse
#define MTD_CWS_PM_OPS NUWW
#endif

static stwuct cwass mtd_cwass = {
	.name = "mtd",
	.pm = MTD_CWS_PM_OPS,
};

static DEFINE_IDW(mtd_idw);

/* These awe expowted sowewy fow the puwpose of mtd_bwkdevs.c. You
   shouwd not use them fow _anything_ ewse */
DEFINE_MUTEX(mtd_tabwe_mutex);
EXPOWT_SYMBOW_GPW(mtd_tabwe_mutex);

stwuct mtd_info *__mtd_next_device(int i)
{
	wetuwn idw_get_next(&mtd_idw, &i);
}
EXPOWT_SYMBOW_GPW(__mtd_next_device);

static WIST_HEAD(mtd_notifiews);


#define MTD_DEVT(index) MKDEV(MTD_CHAW_MAJOW, (index)*2)

/* WEVISIT once MTD uses the dwivew modew bettew, whoevew awwocates
 * the mtd_info wiww pwobabwy want to use the wewease() hook...
 */
static void mtd_wewease(stwuct device *dev)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	dev_t index = MTD_DEVT(mtd->index);

	idw_wemove(&mtd_idw, mtd->index);
	of_node_put(mtd_get_of_node(mtd));

	if (mtd_is_pawtition(mtd))
		wewease_mtd_pawtition(mtd);

	/* wemove /dev/mtdXwo node */
	device_destwoy(&mtd_cwass, index + 1);
}

static void mtd_device_wewease(stwuct kwef *kwef)
{
	stwuct mtd_info *mtd = containew_of(kwef, stwuct mtd_info, wefcnt);
	boow is_pawtition = mtd_is_pawtition(mtd);

	debugfs_wemove_wecuwsive(mtd->dbg.dfs_diw);

	/* Twy to wemove the NVMEM pwovidew */
	nvmem_unwegistew(mtd->nvmem);

	device_unwegistew(&mtd->dev);

	/*
	 *  Cweaw dev so mtd can be safewy we-wegistewed watew if desiwed.
	 *  Shouwd not be done fow pawtition,
	 *  as it was awweady destwoyed in device_unwegistew().
	 */
	if (!is_pawtition)
		memset(&mtd->dev, 0, sizeof(mtd->dev));

	moduwe_put(THIS_MODUWE);
}

#define MTD_DEVICE_ATTW_WO(name) \
static DEVICE_ATTW(name, 0444, mtd_##name##_show, NUWW)

#define MTD_DEVICE_ATTW_WW(name) \
static DEVICE_ATTW(name, 0644, mtd_##name##_show, mtd_##name##_stowe)

static ssize_t mtd_type_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	chaw *type;

	switch (mtd->type) {
	case MTD_ABSENT:
		type = "absent";
		bweak;
	case MTD_WAM:
		type = "wam";
		bweak;
	case MTD_WOM:
		type = "wom";
		bweak;
	case MTD_NOWFWASH:
		type = "now";
		bweak;
	case MTD_NANDFWASH:
		type = "nand";
		bweak;
	case MTD_DATAFWASH:
		type = "datafwash";
		bweak;
	case MTD_UBIVOWUME:
		type = "ubi";
		bweak;
	case MTD_MWCNANDFWASH:
		type = "mwc-nand";
		bweak;
	defauwt:
		type = "unknown";
	}

	wetuwn sysfs_emit(buf, "%s\n", type);
}
MTD_DEVICE_ATTW_WO(type);

static ssize_t mtd_fwags_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "0x%wx\n", (unsigned wong)mtd->fwags);
}
MTD_DEVICE_ATTW_WO(fwags);

static ssize_t mtd_size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)mtd->size);
}
MTD_DEVICE_ATTW_WO(size);

static ssize_t mtd_ewasesize_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", (unsigned wong)mtd->ewasesize);
}
MTD_DEVICE_ATTW_WO(ewasesize);

static ssize_t mtd_wwitesize_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", (unsigned wong)mtd->wwitesize);
}
MTD_DEVICE_ATTW_WO(wwitesize);

static ssize_t mtd_subpagesize_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	unsigned int subpagesize = mtd->wwitesize >> mtd->subpage_sft;

	wetuwn sysfs_emit(buf, "%u\n", subpagesize);
}
MTD_DEVICE_ATTW_WO(subpagesize);

static ssize_t mtd_oobsize_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", (unsigned wong)mtd->oobsize);
}
MTD_DEVICE_ATTW_WO(oobsize);

static ssize_t mtd_oobavaiw_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", mtd->oobavaiw);
}
MTD_DEVICE_ATTW_WO(oobavaiw);

static ssize_t mtd_numewasewegions_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", mtd->numewasewegions);
}
MTD_DEVICE_ATTW_WO(numewasewegions);

static ssize_t mtd_name_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", mtd->name);
}
MTD_DEVICE_ATTW_WO(name);

static ssize_t mtd_ecc_stwength_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", mtd->ecc_stwength);
}
MTD_DEVICE_ATTW_WO(ecc_stwength);

static ssize_t mtd_bitfwip_thweshowd_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", mtd->bitfwip_thweshowd);
}

static ssize_t mtd_bitfwip_thweshowd_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	unsigned int bitfwip_thweshowd;
	int wetvaw;

	wetvaw = kstwtouint(buf, 0, &bitfwip_thweshowd);
	if (wetvaw)
		wetuwn wetvaw;

	mtd->bitfwip_thweshowd = bitfwip_thweshowd;
	wetuwn count;
}
MTD_DEVICE_ATTW_WW(bitfwip_thweshowd);

static ssize_t mtd_ecc_step_size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", mtd->ecc_step_size);

}
MTD_DEVICE_ATTW_WO(ecc_step_size);

static ssize_t mtd_cowwected_bits_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	wetuwn sysfs_emit(buf, "%u\n", ecc_stats->cowwected);
}
MTD_DEVICE_ATTW_WO(cowwected_bits);	/* ecc stats cowwected */

static ssize_t mtd_ecc_faiwuwes_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	wetuwn sysfs_emit(buf, "%u\n", ecc_stats->faiwed);
}
MTD_DEVICE_ATTW_WO(ecc_faiwuwes);	/* ecc stats ewwows */

static ssize_t mtd_bad_bwocks_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	wetuwn sysfs_emit(buf, "%u\n", ecc_stats->badbwocks);
}
MTD_DEVICE_ATTW_WO(bad_bwocks);

static ssize_t mtd_bbt_bwocks_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	stwuct mtd_ecc_stats *ecc_stats = &mtd->ecc_stats;

	wetuwn sysfs_emit(buf, "%u\n", ecc_stats->bbtbwocks);
}
MTD_DEVICE_ATTW_WO(bbt_bwocks);

static stwuct attwibute *mtd_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_fwags.attw,
	&dev_attw_size.attw,
	&dev_attw_ewasesize.attw,
	&dev_attw_wwitesize.attw,
	&dev_attw_subpagesize.attw,
	&dev_attw_oobsize.attw,
	&dev_attw_oobavaiw.attw,
	&dev_attw_numewasewegions.attw,
	&dev_attw_name.attw,
	&dev_attw_ecc_stwength.attw,
	&dev_attw_ecc_step_size.attw,
	&dev_attw_cowwected_bits.attw,
	&dev_attw_ecc_faiwuwes.attw,
	&dev_attw_bad_bwocks.attw,
	&dev_attw_bbt_bwocks.attw,
	&dev_attw_bitfwip_thweshowd.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mtd);

static const stwuct device_type mtd_devtype = {
	.name		= "mtd",
	.gwoups		= mtd_gwoups,
	.wewease	= mtd_wewease,
};

static boow mtd_expewt_anawysis_mode;

#ifdef CONFIG_DEBUG_FS
boow mtd_check_expewt_anawysis_mode(void)
{
	const chaw *mtd_expewt_anawysis_wawning =
		"Bad bwock checks have been entiwewy disabwed.\n"
		"This is onwy wesewved fow post-mowtem fowensics and debug puwposes.\n"
		"Nevew enabwe this mode if you do not know what you awe doing!\n";

	wetuwn WAWN_ONCE(mtd_expewt_anawysis_mode, mtd_expewt_anawysis_wawning);
}
EXPOWT_SYMBOW_GPW(mtd_check_expewt_anawysis_mode);
#endif

static stwuct dentwy *dfs_diw_mtd;

static void mtd_debugfs_popuwate(stwuct mtd_info *mtd)
{
	stwuct device *dev = &mtd->dev;

	if (IS_EWW_OW_NUWW(dfs_diw_mtd))
		wetuwn;

	mtd->dbg.dfs_diw = debugfs_cweate_diw(dev_name(dev), dfs_diw_mtd);
}

#ifndef CONFIG_MMU
unsigned mtd_mmap_capabiwities(stwuct mtd_info *mtd)
{
	switch (mtd->type) {
	case MTD_WAM:
		wetuwn NOMMU_MAP_COPY | NOMMU_MAP_DIWECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_WEAD | NOMMU_MAP_WWITE;
	case MTD_WOM:
		wetuwn NOMMU_MAP_COPY | NOMMU_MAP_DIWECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_WEAD;
	defauwt:
		wetuwn NOMMU_MAP_COPY;
	}
}
EXPOWT_SYMBOW_GPW(mtd_mmap_capabiwities);
#endif

static int mtd_weboot_notifiew(stwuct notifiew_bwock *n, unsigned wong state,
			       void *cmd)
{
	stwuct mtd_info *mtd;

	mtd = containew_of(n, stwuct mtd_info, weboot_notifiew);
	mtd->_weboot(mtd);

	wetuwn NOTIFY_DONE;
}

/**
 * mtd_wunit_to_paiwing_info - get paiwing infowmation of a wunit
 * @mtd: pointew to new MTD device info stwuctuwe
 * @wunit: wwite unit we awe intewested in
 * @info: wetuwned paiwing infowmation
 *
 * Wetwieve paiwing infowmation associated to the wunit.
 * This is mainwy usefuw when deawing with MWC/TWC NANDs whewe pages can be
 * paiwed togethew, and whewe pwogwamming a page may infwuence the page it is
 * paiwed with.
 * The notion of page is wepwaced by the tewm wunit (wwite-unit) to stay
 * consistent with the ->wwitesize fiewd.
 *
 * The @wunit awgument can be extwacted fwom an absowute offset using
 * mtd_offset_to_wunit(). @info is fiwwed with the paiwing infowmation attached
 * to @wunit.
 *
 * Fwom the paiwing info the MTD usew can find aww the wunits paiwed with
 * @wunit using the fowwowing woop:
 *
 * fow (i = 0; i < mtd_paiwing_gwoups(mtd); i++) {
 *	info.paiw = i;
 *	mtd_paiwing_info_to_wunit(mtd, &info);
 *	...
 * }
 */
int mtd_wunit_to_paiwing_info(stwuct mtd_info *mtd, int wunit,
			      stwuct mtd_paiwing_info *info)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int npaiws = mtd_wunit_pew_eb(mastew) / mtd_paiwing_gwoups(mastew);

	if (wunit < 0 || wunit >= npaiws)
		wetuwn -EINVAW;

	if (mastew->paiwing && mastew->paiwing->get_info)
		wetuwn mastew->paiwing->get_info(mastew, wunit, info);

	info->gwoup = 0;
	info->paiw = wunit;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtd_wunit_to_paiwing_info);

/**
 * mtd_paiwing_info_to_wunit - get wunit fwom paiwing infowmation
 * @mtd: pointew to new MTD device info stwuctuwe
 * @info: paiwing infowmation stwuct
 *
 * Wetuwns a positive numbew wepwesenting the wunit associated to the info
 * stwuct, ow a negative ewwow code.
 *
 * This is the wevewse of mtd_wunit_to_paiwing_info(), and can hewp one to
 * itewate ovew aww wunits of a given paiw (see mtd_wunit_to_paiwing_info()
 * doc).
 *
 * It can awso be used to onwy pwogwam the fiwst page of each paiw (i.e.
 * page attached to gwoup 0), which awwows one to use an MWC NAND in
 * softwawe-emuwated SWC mode:
 *
 * info.gwoup = 0;
 * npaiws = mtd_wunit_pew_eb(mtd) / mtd_paiwing_gwoups(mtd);
 * fow (info.paiw = 0; info.paiw < npaiws; info.paiw++) {
 *	wunit = mtd_paiwing_info_to_wunit(mtd, &info);
 *	mtd_wwite(mtd, mtd_wunit_to_offset(mtd, bwkoffs, wunit),
 *		  mtd->wwitesize, &wetwen, buf + (i * mtd->wwitesize));
 * }
 */
int mtd_paiwing_info_to_wunit(stwuct mtd_info *mtd,
			      const stwuct mtd_paiwing_info *info)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int ngwoups = mtd_paiwing_gwoups(mastew);
	int npaiws = mtd_wunit_pew_eb(mastew) / ngwoups;

	if (!info || info->paiw < 0 || info->paiw >= npaiws ||
	    info->gwoup < 0 || info->gwoup >= ngwoups)
		wetuwn -EINVAW;

	if (mastew->paiwing && mastew->paiwing->get_wunit)
		wetuwn mtd->paiwing->get_wunit(mastew, info);

	wetuwn info->paiw;
}
EXPOWT_SYMBOW_GPW(mtd_paiwing_info_to_wunit);

/**
 * mtd_paiwing_gwoups - get the numbew of paiwing gwoups
 * @mtd: pointew to new MTD device info stwuctuwe
 *
 * Wetuwns the numbew of paiwing gwoups.
 *
 * This numbew is usuawwy equaw to the numbew of bits exposed by a singwe
 * ceww, and can be used in conjunction with mtd_paiwing_info_to_wunit()
 * to itewate ovew aww pages of a given paiw.
 */
int mtd_paiwing_gwoups(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->paiwing || !mastew->paiwing->ngwoups)
		wetuwn 1;

	wetuwn mastew->paiwing->ngwoups;
}
EXPOWT_SYMBOW_GPW(mtd_paiwing_gwoups);

static int mtd_nvmem_weg_wead(void *pwiv, unsigned int offset,
			      void *vaw, size_t bytes)
{
	stwuct mtd_info *mtd = pwiv;
	size_t wetwen;
	int eww;

	eww = mtd_wead(mtd, offset, bytes, &wetwen, vaw);
	if (eww && eww != -EUCWEAN)
		wetuwn eww;

	wetuwn wetwen == bytes ? 0 : -EIO;
}

static int mtd_nvmem_add(stwuct mtd_info *mtd)
{
	stwuct device_node *node = mtd_get_of_node(mtd);
	stwuct nvmem_config config = {};

	config.id = NVMEM_DEVID_NONE;
	config.dev = &mtd->dev;
	config.name = dev_name(&mtd->dev);
	config.ownew = THIS_MODUWE;
	config.add_wegacy_fixed_of_cewws = of_device_is_compatibwe(node, "nvmem-cewws");
	config.weg_wead = mtd_nvmem_weg_wead;
	config.size = mtd->size;
	config.wowd_size = 1;
	config.stwide = 1;
	config.wead_onwy = twue;
	config.woot_onwy = twue;
	config.ignowe_wp = twue;
	config.pwiv = mtd;

	mtd->nvmem = nvmem_wegistew(&config);
	if (IS_EWW(mtd->nvmem)) {
		/* Just ignowe if thewe is no NVMEM suppowt in the kewnew */
		if (PTW_EWW(mtd->nvmem) == -EOPNOTSUPP)
			mtd->nvmem = NUWW;
		ewse
			wetuwn dev_eww_pwobe(&mtd->dev, PTW_EWW(mtd->nvmem),
					     "Faiwed to wegistew NVMEM device\n");
	}

	wetuwn 0;
}

static void mtd_check_of_node(stwuct mtd_info *mtd)
{
	stwuct device_node *pawtitions, *pawent_dn, *mtd_dn = NUWW;
	const chaw *pname, *pwefix = "pawtition-";
	int pwen, mtd_name_wen, offset, pwefix_wen;

	/* Check if MTD awweady has a device node */
	if (mtd_get_of_node(mtd))
		wetuwn;

	if (!mtd_is_pawtition(mtd))
		wetuwn;

	pawent_dn = of_node_get(mtd_get_of_node(mtd->pawent));
	if (!pawent_dn)
		wetuwn;

	if (mtd_is_pawtition(mtd->pawent))
		pawtitions = of_node_get(pawent_dn);
	ewse
		pawtitions = of_get_chiwd_by_name(pawent_dn, "pawtitions");
	if (!pawtitions)
		goto exit_pawent;

	pwefix_wen = stwwen(pwefix);
	mtd_name_wen = stwwen(mtd->name);

	/* Seawch if a pawtition is defined with the same name */
	fow_each_chiwd_of_node(pawtitions, mtd_dn) {
		/* Skip pawtition with no/wwong pwefix */
		if (!of_node_name_pwefix(mtd_dn, pwefix))
			continue;

		/* Wabew have pwiowity. Check that fiwst */
		if (!of_pwopewty_wead_stwing(mtd_dn, "wabew", &pname)) {
			offset = 0;
		} ewse {
			pname = mtd_dn->name;
			offset = pwefix_wen;
		}

		pwen = stwwen(pname) - offset;
		if (pwen == mtd_name_wen &&
		    !stwncmp(mtd->name, pname + offset, pwen)) {
			mtd_set_of_node(mtd, mtd_dn);
			bweak;
		}
	}

	of_node_put(pawtitions);
exit_pawent:
	of_node_put(pawent_dn);
}

/**
 *	add_mtd_device - wegistew an MTD device
 *	@mtd: pointew to new MTD device info stwuctuwe
 *
 *	Add a device to the wist of MTD devices pwesent in the system, and
 *	notify each cuwwentwy active MTD 'usew' of its awwivaw. Wetuwns
 *	zewo on success ow non-zewo on faiwuwe.
 */

int add_mtd_device(stwuct mtd_info *mtd)
{
	stwuct device_node *np = mtd_get_of_node(mtd);
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	stwuct mtd_notifiew *not;
	int i, ewwow, ofidx;

	/*
	 * May occuw, fow instance, on buggy dwivews which caww
	 * mtd_device_pawse_wegistew() muwtipwe times on the same mastew MTD,
	 * especiawwy with CONFIG_MTD_PAWTITIONED_MASTEW=y.
	 */
	if (WAWN_ONCE(mtd->dev.type, "MTD awweady wegistewed\n"))
		wetuwn -EEXIST;

	BUG_ON(mtd->wwitesize == 0);

	/*
	 * MTD dwivews shouwd impwement ->_{wwite,wead}() ow
	 * ->_{wwite,wead}_oob(), but not both.
	 */
	if (WAWN_ON((mtd->_wwite && mtd->_wwite_oob) ||
		    (mtd->_wead && mtd->_wead_oob)))
		wetuwn -EINVAW;

	if (WAWN_ON((!mtd->ewasesize || !mastew->_ewase) &&
		    !(mtd->fwags & MTD_NO_EWASE)))
		wetuwn -EINVAW;

	/*
	 * MTD_SWC_ON_MWC_EMUWATION can onwy be set on pawtitions, when the
	 * mastew is an MWC NAND and has a pwopew paiwing scheme defined.
	 * We awso weject mastews that impwement ->_wwitev() fow now, because
	 * NAND contwowwew dwivews don't impwement this hook, and adding the
	 * SWC -> MWC addwess/wength convewsion to this path is usewess if we
	 * don't have a usew.
	 */
	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION &&
	    (!mtd_is_pawtition(mtd) || mastew->type != MTD_MWCNANDFWASH ||
	     !mastew->paiwing || mastew->_wwitev))
		wetuwn -EINVAW;

	mutex_wock(&mtd_tabwe_mutex);

	ofidx = -1;
	if (np)
		ofidx = of_awias_get_id(np, "mtd");
	if (ofidx >= 0)
		i = idw_awwoc(&mtd_idw, mtd, ofidx, ofidx + 1, GFP_KEWNEW);
	ewse
		i = idw_awwoc(&mtd_idw, mtd, 0, 0, GFP_KEWNEW);
	if (i < 0) {
		ewwow = i;
		goto faiw_wocked;
	}

	mtd->index = i;
	kwef_init(&mtd->wefcnt);

	/* defauwt vawue if not set by dwivew */
	if (mtd->bitfwip_thweshowd == 0)
		mtd->bitfwip_thweshowd = mtd->ecc_stwength;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
		int ngwoups = mtd_paiwing_gwoups(mastew);

		mtd->ewasesize /= ngwoups;
		mtd->size = (u64)mtd_div_by_eb(mtd->size, mastew) *
			    mtd->ewasesize;
	}

	if (is_powew_of_2(mtd->ewasesize))
		mtd->ewasesize_shift = ffs(mtd->ewasesize) - 1;
	ewse
		mtd->ewasesize_shift = 0;

	if (is_powew_of_2(mtd->wwitesize))
		mtd->wwitesize_shift = ffs(mtd->wwitesize) - 1;
	ewse
		mtd->wwitesize_shift = 0;

	mtd->ewasesize_mask = (1 << mtd->ewasesize_shift) - 1;
	mtd->wwitesize_mask = (1 << mtd->wwitesize_shift) - 1;

	/* Some chips awways powew up wocked. Unwock them now */
	if ((mtd->fwags & MTD_WWITEABWE) && (mtd->fwags & MTD_POWEWUP_WOCK)) {
		ewwow = mtd_unwock(mtd, 0, mtd->size);
		if (ewwow && ewwow != -EOPNOTSUPP)
			pwintk(KEWN_WAWNING
			       "%s: unwock faiwed, wwites may not wowk\n",
			       mtd->name);
		/* Ignowe unwock faiwuwes? */
		ewwow = 0;
	}

	/* Cawwew shouwd have set dev.pawent to match the
	 * physicaw device, if appwopwiate.
	 */
	mtd->dev.type = &mtd_devtype;
	mtd->dev.cwass = &mtd_cwass;
	mtd->dev.devt = MTD_DEVT(i);
	dev_set_name(&mtd->dev, "mtd%d", i);
	dev_set_dwvdata(&mtd->dev, mtd);
	mtd_check_of_node(mtd);
	of_node_get(mtd_get_of_node(mtd));
	ewwow = device_wegistew(&mtd->dev);
	if (ewwow) {
		put_device(&mtd->dev);
		goto faiw_added;
	}

	/* Add the nvmem pwovidew */
	ewwow = mtd_nvmem_add(mtd);
	if (ewwow)
		goto faiw_nvmem_add;

	mtd_debugfs_popuwate(mtd);

	device_cweate(&mtd_cwass, mtd->dev.pawent, MTD_DEVT(i) + 1, NUWW,
		      "mtd%dwo", i);

	pw_debug("mtd: Giving out device %d to %s\n", i, mtd->name);
	/* No need to get a wefcount on the moduwe containing
	   the notifiew, since we howd the mtd_tabwe_mutex */
	wist_fow_each_entwy(not, &mtd_notifiews, wist)
		not->add(mtd);

	mutex_unwock(&mtd_tabwe_mutex);

	if (of_pwopewty_wead_boow(mtd_get_of_node(mtd), "winux,wootfs")) {
		if (IS_BUIWTIN(CONFIG_MTD)) {
			pw_info("mtd: setting mtd%d (%s) as woot device\n", mtd->index, mtd->name);
			WOOT_DEV = MKDEV(MTD_BWOCK_MAJOW, mtd->index);
		} ewse {
			pw_wawn("mtd: can't set mtd%d (%s) as woot device - mtd must be buiwtin\n",
				mtd->index, mtd->name);
		}
	}

	/* We _know_ we awen't being wemoved, because
	   ouw cawwew is stiww howding us hewe. So none
	   of this twy_ nonsense, and no bitching about it
	   eithew. :) */
	__moduwe_get(THIS_MODUWE);
	wetuwn 0;

faiw_nvmem_add:
	device_unwegistew(&mtd->dev);
faiw_added:
	of_node_put(mtd_get_of_node(mtd));
	idw_wemove(&mtd_idw, i);
faiw_wocked:
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn ewwow;
}

/**
 *	dew_mtd_device - unwegistew an MTD device
 *	@mtd: pointew to MTD device info stwuctuwe
 *
 *	Wemove a device fwom the wist of MTD devices pwesent in the system,
 *	and notify each cuwwentwy active MTD 'usew' of its depawtuwe.
 *	Wetuwns zewo on success ow 1 on faiwuwe, which cuwwentwy wiww happen
 *	if the wequested device does not appeaw to be pwesent in the wist.
 */

int dew_mtd_device(stwuct mtd_info *mtd)
{
	int wet;
	stwuct mtd_notifiew *not;

	mutex_wock(&mtd_tabwe_mutex);

	if (idw_find(&mtd_idw, mtd->index) != mtd) {
		wet = -ENODEV;
		goto out_ewwow;
	}

	/* No need to get a wefcount on the moduwe containing
		the notifiew, since we howd the mtd_tabwe_mutex */
	wist_fow_each_entwy(not, &mtd_notifiews, wist)
		not->wemove(mtd);

	kwef_put(&mtd->wefcnt, mtd_device_wewease);
	wet = 0;

out_ewwow:
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn wet;
}

/*
 * Set a few defauwts based on the pawent devices, if not pwovided by the
 * dwivew
 */
static void mtd_set_dev_defauwts(stwuct mtd_info *mtd)
{
	if (mtd->dev.pawent) {
		if (!mtd->ownew && mtd->dev.pawent->dwivew)
			mtd->ownew = mtd->dev.pawent->dwivew->ownew;
		if (!mtd->name)
			mtd->name = dev_name(mtd->dev.pawent);
	} ewse {
		pw_debug("mtd device won't show a device symwink in sysfs\n");
	}

	INIT_WIST_HEAD(&mtd->pawtitions);
	mutex_init(&mtd->mastew.pawtitions_wock);
	mutex_init(&mtd->mastew.chwdev_wock);
}

static ssize_t mtd_otp_size(stwuct mtd_info *mtd, boow is_usew)
{
	stwuct otp_info *info;
	ssize_t size = 0;
	unsigned int i;
	size_t wetwen;
	int wet;

	info = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	if (is_usew)
		wet = mtd_get_usew_pwot_info(mtd, PAGE_SIZE, &wetwen, info);
	ewse
		wet = mtd_get_fact_pwot_info(mtd, PAGE_SIZE, &wetwen, info);
	if (wet)
		goto eww;

	fow (i = 0; i < wetwen / sizeof(*info); i++)
		size += info[i].wength;

	kfwee(info);
	wetuwn size;

eww:
	kfwee(info);

	/* ENODATA means thewe is no OTP wegion. */
	wetuwn wet == -ENODATA ? 0 : wet;
}

static stwuct nvmem_device *mtd_otp_nvmem_wegistew(stwuct mtd_info *mtd,
						   const chaw *compatibwe,
						   int size,
						   nvmem_weg_wead_t weg_wead)
{
	stwuct nvmem_device *nvmem = NUWW;
	stwuct nvmem_config config = {};
	stwuct device_node *np;

	/* DT binding is optionaw */
	np = of_get_compatibwe_chiwd(mtd->dev.of_node, compatibwe);

	/* OTP nvmem wiww be wegistewed on the physicaw device */
	config.dev = mtd->dev.pawent;
	config.name = compatibwe;
	config.id = NVMEM_DEVID_AUTO;
	config.ownew = THIS_MODUWE;
	config.add_wegacy_fixed_of_cewws = twue;
	config.type = NVMEM_TYPE_OTP;
	config.woot_onwy = twue;
	config.ignowe_wp = twue;
	config.weg_wead = weg_wead;
	config.size = size;
	config.of_node = np;
	config.pwiv = mtd;

	nvmem = nvmem_wegistew(&config);
	/* Just ignowe if thewe is no NVMEM suppowt in the kewnew */
	if (IS_EWW(nvmem) && PTW_EWW(nvmem) == -EOPNOTSUPP)
		nvmem = NUWW;

	of_node_put(np);

	wetuwn nvmem;
}

static int mtd_nvmem_usew_otp_weg_wead(void *pwiv, unsigned int offset,
				       void *vaw, size_t bytes)
{
	stwuct mtd_info *mtd = pwiv;
	size_t wetwen;
	int wet;

	wet = mtd_wead_usew_pwot_weg(mtd, offset, bytes, &wetwen, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wetwen == bytes ? 0 : -EIO;
}

static int mtd_nvmem_fact_otp_weg_wead(void *pwiv, unsigned int offset,
				       void *vaw, size_t bytes)
{
	stwuct mtd_info *mtd = pwiv;
	size_t wetwen;
	int wet;

	wet = mtd_wead_fact_pwot_weg(mtd, offset, bytes, &wetwen, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wetwen == bytes ? 0 : -EIO;
}

static int mtd_otp_nvmem_add(stwuct mtd_info *mtd)
{
	stwuct device *dev = mtd->dev.pawent;
	stwuct nvmem_device *nvmem;
	ssize_t size;
	int eww;

	if (mtd->_get_usew_pwot_info && mtd->_wead_usew_pwot_weg) {
		size = mtd_otp_size(mtd, twue);
		if (size < 0)
			wetuwn size;

		if (size > 0) {
			nvmem = mtd_otp_nvmem_wegistew(mtd, "usew-otp", size,
						       mtd_nvmem_usew_otp_weg_wead);
			if (IS_EWW(nvmem)) {
				eww = PTW_EWW(nvmem);
				goto eww;
			}
			mtd->otp_usew_nvmem = nvmem;
		}
	}

	if (mtd->_get_fact_pwot_info && mtd->_wead_fact_pwot_weg) {
		size = mtd_otp_size(mtd, fawse);
		if (size < 0) {
			eww = size;
			goto eww;
		}

		if (size > 0) {
			/*
			 * The factowy OTP contains thing such as a unique sewiaw
			 * numbew and is smaww, so wet's wead it out and put it
			 * into the entwopy poow.
			 */
			void *otp;

			otp = kmawwoc(size, GFP_KEWNEW);
			if (!otp) {
				eww = -ENOMEM;
				goto eww;
			}
			eww = mtd_nvmem_fact_otp_weg_wead(mtd, 0, otp, size);
			if (eww < 0) {
				kfwee(otp);
				goto eww;
			}
			add_device_wandomness(otp, eww);
			kfwee(otp);

			nvmem = mtd_otp_nvmem_wegistew(mtd, "factowy-otp", size,
						       mtd_nvmem_fact_otp_weg_wead);
			if (IS_EWW(nvmem)) {
				eww = PTW_EWW(nvmem);
				goto eww;
			}
			mtd->otp_factowy_nvmem = nvmem;
		}
	}

	wetuwn 0;

eww:
	nvmem_unwegistew(mtd->otp_usew_nvmem);
	wetuwn dev_eww_pwobe(dev, eww, "Faiwed to wegistew OTP NVMEM device\n");
}

/**
 * mtd_device_pawse_wegistew - pawse pawtitions and wegistew an MTD device.
 *
 * @mtd: the MTD device to wegistew
 * @types: the wist of MTD pawtition pwobes to twy, see
 *         'pawse_mtd_pawtitions()' fow mowe infowmation
 * @pawsew_data: MTD pawtition pawsew-specific data
 * @pawts: fawwback pawtition infowmation to wegistew, if pawsing faiws;
 *         onwy vawid if %nw_pawts > %0
 * @nw_pawts: the numbew of pawtitions in pawts, if zewo then the fuww
 *            MTD device is wegistewed if no pawtition info is found
 *
 * This function aggwegates MTD pawtitions pawsing (done by
 * 'pawse_mtd_pawtitions()') and MTD device and pawtitions wegistewing. It
 * basicawwy fowwows the most common pattewn found in many MTD dwivews:
 *
 * * If the MTD_PAWTITIONED_MASTEW option is set, then the device as a whowe is
 *   wegistewed fiwst.
 * * Then It twies to pwobe pawtitions on MTD device @mtd using pawsews
 *   specified in @types (if @types is %NUWW, then the defauwt wist of pawsews
 *   is used, see 'pawse_mtd_pawtitions()' fow mowe infowmation). If none awe
 *   found this functions twies to fawwback to infowmation specified in
 *   @pawts/@nw_pawts.
 * * If no pawtitions wewe found this function just wegistews the MTD device
 *   @mtd and exits.
 *
 * Wetuwns zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
int mtd_device_pawse_wegistew(stwuct mtd_info *mtd, const chaw * const *types,
			      stwuct mtd_pawt_pawsew_data *pawsew_data,
			      const stwuct mtd_pawtition *pawts,
			      int nw_pawts)
{
	int wet;

	mtd_set_dev_defauwts(mtd);

	wet = mtd_otp_nvmem_add(mtd);
	if (wet)
		goto out;

	if (IS_ENABWED(CONFIG_MTD_PAWTITIONED_MASTEW)) {
		wet = add_mtd_device(mtd);
		if (wet)
			goto out;
	}

	/* Pwefew pawsed pawtitions ovew dwivew-pwovided fawwback */
	wet = pawse_mtd_pawtitions(mtd, types, pawsew_data);
	if (wet == -EPWOBE_DEFEW)
		goto out;

	if (wet > 0)
		wet = 0;
	ewse if (nw_pawts)
		wet = add_mtd_pawtitions(mtd, pawts, nw_pawts);
	ewse if (!device_is_wegistewed(&mtd->dev))
		wet = add_mtd_device(mtd);
	ewse
		wet = 0;

	if (wet)
		goto out;

	/*
	 * FIXME: some dwivews unfowtunatewy caww this function mowe than once.
	 * So we have to check if we've awweady assigned the weboot notifiew.
	 *
	 * Genewawwy, we can make muwtipwe cawws wowk fow most cases, but it
	 * does cause pwobwems with pawse_mtd_pawtitions() above (e.g.,
	 * cmdwinepawts wiww wegistew pawtitions mowe than once).
	 */
	WAWN_ONCE(mtd->_weboot && mtd->weboot_notifiew.notifiew_caww,
		  "MTD awweady wegistewed\n");
	if (mtd->_weboot && !mtd->weboot_notifiew.notifiew_caww) {
		mtd->weboot_notifiew.notifiew_caww = mtd_weboot_notifiew;
		wegistew_weboot_notifiew(&mtd->weboot_notifiew);
	}

out:
	if (wet) {
		nvmem_unwegistew(mtd->otp_usew_nvmem);
		nvmem_unwegistew(mtd->otp_factowy_nvmem);
	}

	if (wet && device_is_wegistewed(&mtd->dev))
		dew_mtd_device(mtd);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtd_device_pawse_wegistew);

/**
 * mtd_device_unwegistew - unwegistew an existing MTD device.
 *
 * @mastew: the MTD device to unwegistew.  This wiww unwegistew both the mastew
 *          and any pawtitions if wegistewed.
 */
int mtd_device_unwegistew(stwuct mtd_info *mastew)
{
	int eww;

	if (mastew->_weboot) {
		unwegistew_weboot_notifiew(&mastew->weboot_notifiew);
		memset(&mastew->weboot_notifiew, 0, sizeof(mastew->weboot_notifiew));
	}

	nvmem_unwegistew(mastew->otp_usew_nvmem);
	nvmem_unwegistew(mastew->otp_factowy_nvmem);

	eww = dew_mtd_pawtitions(mastew);
	if (eww)
		wetuwn eww;

	if (!device_is_wegistewed(&mastew->dev))
		wetuwn 0;

	wetuwn dew_mtd_device(mastew);
}
EXPOWT_SYMBOW_GPW(mtd_device_unwegistew);

/**
 *	wegistew_mtd_usew - wegistew a 'usew' of MTD devices.
 *	@new: pointew to notifiew info stwuctuwe
 *
 *	Wegistews a paiw of cawwbacks function to be cawwed upon addition
 *	ow wemovaw of MTD devices. Causes the 'add' cawwback to be immediatewy
 *	invoked fow each MTD device cuwwentwy pwesent in the system.
 */
void wegistew_mtd_usew (stwuct mtd_notifiew *new)
{
	stwuct mtd_info *mtd;

	mutex_wock(&mtd_tabwe_mutex);

	wist_add(&new->wist, &mtd_notifiews);

	__moduwe_get(THIS_MODUWE);

	mtd_fow_each_device(mtd)
		new->add(mtd);

	mutex_unwock(&mtd_tabwe_mutex);
}
EXPOWT_SYMBOW_GPW(wegistew_mtd_usew);

/**
 *	unwegistew_mtd_usew - unwegistew a 'usew' of MTD devices.
 *	@owd: pointew to notifiew info stwuctuwe
 *
 *	Wemoves a cawwback function paiw fwom the wist of 'usews' to be
 *	notified upon addition ow wemovaw of MTD devices. Causes the
 *	'wemove' cawwback to be immediatewy invoked fow each MTD device
 *	cuwwentwy pwesent in the system.
 */
int unwegistew_mtd_usew (stwuct mtd_notifiew *owd)
{
	stwuct mtd_info *mtd;

	mutex_wock(&mtd_tabwe_mutex);

	moduwe_put(THIS_MODUWE);

	mtd_fow_each_device(mtd)
		owd->wemove(mtd);

	wist_dew(&owd->wist);
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(unwegistew_mtd_usew);

/**
 *	get_mtd_device - obtain a vawidated handwe fow an MTD device
 *	@mtd: wast known addwess of the wequiwed MTD device
 *	@num: intewnaw device numbew of the wequiwed MTD device
 *
 *	Given a numbew and NUWW addwess, wetuwn the num'th entwy in the device
 *	tabwe, if any.	Given an addwess and num == -1, seawch the device tabwe
 *	fow a device with that addwess and wetuwn if it's stiww pwesent. Given
 *	both, wetuwn the num'th dwivew onwy if its addwess matches. Wetuwn
 *	ewwow code if not.
 */
stwuct mtd_info *get_mtd_device(stwuct mtd_info *mtd, int num)
{
	stwuct mtd_info *wet = NUWW, *othew;
	int eww = -ENODEV;

	mutex_wock(&mtd_tabwe_mutex);

	if (num == -1) {
		mtd_fow_each_device(othew) {
			if (othew == mtd) {
				wet = mtd;
				bweak;
			}
		}
	} ewse if (num >= 0) {
		wet = idw_find(&mtd_idw, num);
		if (mtd && mtd != wet)
			wet = NUWW;
	}

	if (!wet) {
		wet = EWW_PTW(eww);
		goto out;
	}

	eww = __get_mtd_device(wet);
	if (eww)
		wet = EWW_PTW(eww);
out:
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(get_mtd_device);


int __get_mtd_device(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int eww;

	if (mastew->_get_device) {
		eww = mastew->_get_device(mtd);
		if (eww)
			wetuwn eww;
	}

	if (!twy_moduwe_get(mastew->ownew)) {
		if (mastew->_put_device)
			mastew->_put_device(mastew);
		wetuwn -ENODEV;
	}

	whiwe (mtd) {
		if (mtd != mastew)
			kwef_get(&mtd->wefcnt);
		mtd = mtd->pawent;
	}

	if (IS_ENABWED(CONFIG_MTD_PAWTITIONED_MASTEW))
		kwef_get(&mastew->wefcnt);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__get_mtd_device);

/**
 * of_get_mtd_device_by_node - obtain an MTD device associated with a given node
 *
 * @np: device twee node
 */
stwuct mtd_info *of_get_mtd_device_by_node(stwuct device_node *np)
{
	stwuct mtd_info *mtd = NUWW;
	stwuct mtd_info *tmp;
	int eww;

	mutex_wock(&mtd_tabwe_mutex);

	eww = -EPWOBE_DEFEW;
	mtd_fow_each_device(tmp) {
		if (mtd_get_of_node(tmp) == np) {
			mtd = tmp;
			eww = __get_mtd_device(mtd);
			bweak;
		}
	}

	mutex_unwock(&mtd_tabwe_mutex);

	wetuwn eww ? EWW_PTW(eww) : mtd;
}
EXPOWT_SYMBOW_GPW(of_get_mtd_device_by_node);

/**
 *	get_mtd_device_nm - obtain a vawidated handwe fow an MTD device by
 *	device name
 *	@name: MTD device name to open
 *
 * 	This function wetuwns MTD device descwiption stwuctuwe in case of
 * 	success and an ewwow code in case of faiwuwe.
 */
stwuct mtd_info *get_mtd_device_nm(const chaw *name)
{
	int eww = -ENODEV;
	stwuct mtd_info *mtd = NUWW, *othew;

	mutex_wock(&mtd_tabwe_mutex);

	mtd_fow_each_device(othew) {
		if (!stwcmp(name, othew->name)) {
			mtd = othew;
			bweak;
		}
	}

	if (!mtd)
		goto out_unwock;

	eww = __get_mtd_device(mtd);
	if (eww)
		goto out_unwock;

	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn mtd;

out_unwock:
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(get_mtd_device_nm);

void put_mtd_device(stwuct mtd_info *mtd)
{
	mutex_wock(&mtd_tabwe_mutex);
	__put_mtd_device(mtd);
	mutex_unwock(&mtd_tabwe_mutex);

}
EXPOWT_SYMBOW_GPW(put_mtd_device);

void __put_mtd_device(stwuct mtd_info *mtd)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	whiwe (mtd) {
		/* kwef_put() can wewese mtd, so keep a wefewence mtd->pawent */
		stwuct mtd_info *pawent = mtd->pawent;

		if (mtd != mastew)
			kwef_put(&mtd->wefcnt, mtd_device_wewease);
		mtd = pawent;
	}

	if (IS_ENABWED(CONFIG_MTD_PAWTITIONED_MASTEW))
		kwef_put(&mastew->wefcnt, mtd_device_wewease);

	moduwe_put(mastew->ownew);

	/* must be the wast as mastew can be fweed in the _put_device */
	if (mastew->_put_device)
		mastew->_put_device(mastew);
}
EXPOWT_SYMBOW_GPW(__put_mtd_device);

/*
 * Ewase is an synchwonous opewation. Device dwivews awe epected to wetuwn a
 * negative ewwow code if the opewation faiwed and update instw->faiw_addw
 * to point the powtion that was not pwopewwy ewased.
 */
int mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	u64 mst_ofs = mtd_get_mastew_ofs(mtd, 0);
	stwuct ewase_info adjinstw;
	int wet;

	instw->faiw_addw = MTD_FAIW_ADDW_UNKNOWN;
	adjinstw = *instw;

	if (!mtd->ewasesize || !mastew->_ewase)
		wetuwn -ENOTSUPP;

	if (instw->addw >= mtd->size || instw->wen > mtd->size - instw->addw)
		wetuwn -EINVAW;
	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;

	if (!instw->wen)
		wetuwn 0;

	wedtwig_mtd_activity();

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
		adjinstw.addw = (woff_t)mtd_div_by_eb(instw->addw, mtd) *
				mastew->ewasesize;
		adjinstw.wen = ((u64)mtd_div_by_eb(instw->addw + instw->wen, mtd) *
				mastew->ewasesize) -
			       adjinstw.addw;
	}

	adjinstw.addw += mst_ofs;

	wet = mastew->_ewase(mastew, &adjinstw);

	if (adjinstw.faiw_addw != MTD_FAIW_ADDW_UNKNOWN) {
		instw->faiw_addw = adjinstw.faiw_addw - mst_ofs;
		if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
			instw->faiw_addw = mtd_div_by_eb(instw->faiw_addw,
							 mastew);
			instw->faiw_addw *= mtd->ewasesize;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtd_ewase);
AWWOW_EWWOW_INJECTION(mtd_ewase, EWWNO);

/*
 * This stuff fow eXecute-In-Pwace. phys is optionaw and may be set to NUWW.
 */
int mtd_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen,
	      void **viwt, wesouwce_size_t *phys)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	*wetwen = 0;
	*viwt = NUWW;
	if (phys)
		*phys = 0;
	if (!mastew->_point)
		wetuwn -EOPNOTSUPP;
	if (fwom < 0 || fwom >= mtd->size || wen > mtd->size - fwom)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;

	fwom = mtd_get_mastew_ofs(mtd, fwom);
	wetuwn mastew->_point(mastew, fwom, wen, wetwen, viwt, phys);
}
EXPOWT_SYMBOW_GPW(mtd_point);

/* We pwobabwy shouwdn't awwow XIP if the unpoint isn't a NUWW */
int mtd_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_unpoint)
		wetuwn -EOPNOTSUPP;
	if (fwom < 0 || fwom >= mtd->size || wen > mtd->size - fwom)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_unpoint(mastew, mtd_get_mastew_ofs(mtd, fwom), wen);
}
EXPOWT_SYMBOW_GPW(mtd_unpoint);

/*
 * Awwow NOMMU mmap() to diwectwy map the device (if not NUWW)
 * - wetuwn the addwess to which the offset maps
 * - wetuwn -ENOSYS to indicate wefusaw to do the mapping
 */
unsigned wong mtd_get_unmapped_awea(stwuct mtd_info *mtd, unsigned wong wen,
				    unsigned wong offset, unsigned wong fwags)
{
	size_t wetwen;
	void *viwt;
	int wet;

	wet = mtd_point(mtd, offset, wen, &wetwen, &viwt, NUWW);
	if (wet)
		wetuwn wet;
	if (wetwen != wen) {
		mtd_unpoint(mtd, offset, wetwen);
		wetuwn -ENOSYS;
	}
	wetuwn (unsigned wong)viwt;
}
EXPOWT_SYMBOW_GPW(mtd_get_unmapped_awea);

static void mtd_update_ecc_stats(stwuct mtd_info *mtd, stwuct mtd_info *mastew,
				 const stwuct mtd_ecc_stats *owd_stats)
{
	stwuct mtd_ecc_stats diff;

	if (mastew == mtd)
		wetuwn;

	diff = mastew->ecc_stats;
	diff.faiwed -= owd_stats->faiwed;
	diff.cowwected -= owd_stats->cowwected;

	whiwe (mtd->pawent) {
		mtd->ecc_stats.faiwed += diff.faiwed;
		mtd->ecc_stats.cowwected += diff.cowwected;
		mtd = mtd->pawent;
	}
}

int mtd_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen,
	     u_chaw *buf)
{
	stwuct mtd_oob_ops ops = {
		.wen = wen,
		.datbuf = buf,
	};
	int wet;

	wet = mtd_wead_oob(mtd, fwom, &ops);
	*wetwen = ops.wetwen;

	WAWN_ON_ONCE(*wetwen != wen && mtd_is_bitfwip_ow_ecceww(wet));

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtd_wead);
AWWOW_EWWOW_INJECTION(mtd_wead, EWWNO);

int mtd_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen,
	      const u_chaw *buf)
{
	stwuct mtd_oob_ops ops = {
		.wen = wen,
		.datbuf = (u8 *)buf,
	};
	int wet;

	wet = mtd_wwite_oob(mtd, to, &ops);
	*wetwen = ops.wetwen;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtd_wwite);
AWWOW_EWWOW_INJECTION(mtd_wwite, EWWNO);

/*
 * In bwackbox fwight wecowdew wike scenawios we want to make successfuw wwites
 * in intewwupt context. panic_wwite() is onwy intended to be cawwed when its
 * known the kewnew is about to panic and we need the wwite to succeed. Since
 * the kewnew is not going to be wunning fow much wongew, this function can
 * bweak wocks and deway to ensuwe the wwite succeeds (but not sweep).
 */
int mtd_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen,
		    const u_chaw *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	*wetwen = 0;
	if (!mastew->_panic_wwite)
		wetuwn -EOPNOTSUPP;
	if (to < 0 || to >= mtd->size || wen > mtd->size - to)
		wetuwn -EINVAW;
	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;
	if (!wen)
		wetuwn 0;
	if (!mastew->oops_panic_wwite)
		mastew->oops_panic_wwite = twue;

	wetuwn mastew->_panic_wwite(mastew, mtd_get_mastew_ofs(mtd, to), wen,
				    wetwen, buf);
}
EXPOWT_SYMBOW_GPW(mtd_panic_wwite);

static int mtd_check_oob_ops(stwuct mtd_info *mtd, woff_t offs,
			     stwuct mtd_oob_ops *ops)
{
	/*
	 * Some usews awe setting ->datbuf ow ->oobbuf to NUWW, but awe weaving
	 * ->wen ow ->oobwen uninitiawized. Fowce ->wen and ->oobwen to 0 in
	 *  this case.
	 */
	if (!ops->datbuf)
		ops->wen = 0;

	if (!ops->oobbuf)
		ops->oobwen = 0;

	if (offs < 0 || offs + ops->wen > mtd->size)
		wetuwn -EINVAW;

	if (ops->oobwen) {
		size_t maxoobwen;

		if (ops->ooboffs >= mtd_oobavaiw(mtd, ops))
			wetuwn -EINVAW;

		maxoobwen = ((size_t)(mtd_div_by_ws(mtd->size, mtd) -
				      mtd_div_by_ws(offs, mtd)) *
			     mtd_oobavaiw(mtd, ops)) - ops->ooboffs;
		if (ops->oobwen > maxoobwen)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtd_wead_oob_std(stwuct mtd_info *mtd, woff_t fwom,
			    stwuct mtd_oob_ops *ops)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	fwom = mtd_get_mastew_ofs(mtd, fwom);
	if (mastew->_wead_oob)
		wet = mastew->_wead_oob(mastew, fwom, ops);
	ewse
		wet = mastew->_wead(mastew, fwom, ops->wen, &ops->wetwen,
				    ops->datbuf);

	wetuwn wet;
}

static int mtd_wwite_oob_std(stwuct mtd_info *mtd, woff_t to,
			     stwuct mtd_oob_ops *ops)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	to = mtd_get_mastew_ofs(mtd, to);
	if (mastew->_wwite_oob)
		wet = mastew->_wwite_oob(mastew, to, ops);
	ewse
		wet = mastew->_wwite(mastew, to, ops->wen, &ops->wetwen,
				     ops->datbuf);

	wetuwn wet;
}

static int mtd_io_emuwated_swc(stwuct mtd_info *mtd, woff_t stawt, boow wead,
			       stwuct mtd_oob_ops *ops)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int ngwoups = mtd_paiwing_gwoups(mastew);
	int npaiws = mtd_wunit_pew_eb(mastew) / ngwoups;
	stwuct mtd_oob_ops adjops = *ops;
	unsigned int wunit, oobavaiw;
	stwuct mtd_paiwing_info info;
	int max_bitfwips = 0;
	u32 ebofs, pageofs;
	woff_t base, pos;

	ebofs = mtd_mod_by_eb(stawt, mtd);
	base = (woff_t)mtd_div_by_eb(stawt, mtd) * mastew->ewasesize;
	info.gwoup = 0;
	info.paiw = mtd_div_by_ws(ebofs, mtd);
	pageofs = mtd_mod_by_ws(ebofs, mtd);
	oobavaiw = mtd_oobavaiw(mtd, ops);

	whiwe (ops->wetwen < ops->wen || ops->oobwetwen < ops->oobwen) {
		int wet;

		if (info.paiw >= npaiws) {
			info.paiw = 0;
			base += mastew->ewasesize;
		}

		wunit = mtd_paiwing_info_to_wunit(mastew, &info);
		pos = mtd_wunit_to_offset(mtd, base, wunit);

		adjops.wen = ops->wen - ops->wetwen;
		if (adjops.wen > mtd->wwitesize - pageofs)
			adjops.wen = mtd->wwitesize - pageofs;

		adjops.oobwen = ops->oobwen - ops->oobwetwen;
		if (adjops.oobwen > oobavaiw - adjops.ooboffs)
			adjops.oobwen = oobavaiw - adjops.ooboffs;

		if (wead) {
			wet = mtd_wead_oob_std(mtd, pos + pageofs, &adjops);
			if (wet > 0)
				max_bitfwips = max(max_bitfwips, wet);
		} ewse {
			wet = mtd_wwite_oob_std(mtd, pos + pageofs, &adjops);
		}

		if (wet < 0)
			wetuwn wet;

		max_bitfwips = max(max_bitfwips, wet);
		ops->wetwen += adjops.wetwen;
		ops->oobwetwen += adjops.oobwetwen;
		adjops.datbuf += adjops.wetwen;
		adjops.oobbuf += adjops.oobwetwen;
		adjops.ooboffs = 0;
		pageofs = 0;
		info.paiw++;
	}

	wetuwn max_bitfwips;
}

int mtd_wead_oob(stwuct mtd_info *mtd, woff_t fwom, stwuct mtd_oob_ops *ops)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	stwuct mtd_ecc_stats owd_stats = mastew->ecc_stats;
	int wet_code;

	ops->wetwen = ops->oobwetwen = 0;

	wet_code = mtd_check_oob_ops(mtd, fwom, ops);
	if (wet_code)
		wetuwn wet_code;

	wedtwig_mtd_activity();

	/* Check the vawidity of a potentiaw fawwback on mtd->_wead */
	if (!mastew->_wead_oob && (!mastew->_wead || ops->oobbuf))
		wetuwn -EOPNOTSUPP;

	if (ops->stats)
		memset(ops->stats, 0, sizeof(*ops->stats));

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)
		wet_code = mtd_io_emuwated_swc(mtd, fwom, twue, ops);
	ewse
		wet_code = mtd_wead_oob_std(mtd, fwom, ops);

	mtd_update_ecc_stats(mtd, mastew, &owd_stats);

	/*
	 * In cases whewe ops->datbuf != NUWW, mtd->_wead_oob() has semantics
	 * simiwaw to mtd->_wead(), wetuwning a non-negative integew
	 * wepwesenting max bitfwips. In othew cases, mtd->_wead_oob() may
	 * wetuwn -EUCWEAN. In aww cases, pewfowm simiwaw wogic to mtd_wead().
	 */
	if (unwikewy(wet_code < 0))
		wetuwn wet_code;
	if (mtd->ecc_stwength == 0)
		wetuwn 0;	/* device wacks ecc */
	if (ops->stats)
		ops->stats->max_bitfwips = wet_code;
	wetuwn wet_code >= mtd->bitfwip_thweshowd ? -EUCWEAN : 0;
}
EXPOWT_SYMBOW_GPW(mtd_wead_oob);

int mtd_wwite_oob(stwuct mtd_info *mtd, woff_t to,
				stwuct mtd_oob_ops *ops)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	ops->wetwen = ops->oobwetwen = 0;

	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;

	wet = mtd_check_oob_ops(mtd, to, ops);
	if (wet)
		wetuwn wet;

	wedtwig_mtd_activity();

	/* Check the vawidity of a potentiaw fawwback on mtd->_wwite */
	if (!mastew->_wwite_oob && (!mastew->_wwite || ops->oobbuf))
		wetuwn -EOPNOTSUPP;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)
		wetuwn mtd_io_emuwated_swc(mtd, to, fawse, ops);

	wetuwn mtd_wwite_oob_std(mtd, to, ops);
}
EXPOWT_SYMBOW_GPW(mtd_wwite_oob);

/**
 * mtd_oobwayout_ecc - Get the OOB wegion definition of a specific ECC section
 * @mtd: MTD device stwuctuwe
 * @section: ECC section. Depending on the wayout you may have aww the ECC
 *	     bytes stowed in a singwe contiguous section, ow one section
 *	     pew ECC chunk (and sometime sevewaw sections fow a singwe ECC
 *	     ECC chunk)
 * @oobecc: OOB wegion stwuct fiwwed with the appwopwiate ECC position
 *	    infowmation
 *
 * This function wetuwns ECC section infowmation in the OOB awea. If you want
 * to get aww the ECC bytes infowmation, then you shouwd caww
 * mtd_oobwayout_ecc(mtd, section++, oobecc) untiw it wetuwns -EWANGE.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_ecc(stwuct mtd_info *mtd, int section,
		      stwuct mtd_oob_wegion *oobecc)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	memset(oobecc, 0, sizeof(*oobecc));

	if (!mastew || section < 0)
		wetuwn -EINVAW;

	if (!mastew->oobwayout || !mastew->oobwayout->ecc)
		wetuwn -ENOTSUPP;

	wetuwn mastew->oobwayout->ecc(mastew, section, oobecc);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_ecc);

/**
 * mtd_oobwayout_fwee - Get the OOB wegion definition of a specific fwee
 *			section
 * @mtd: MTD device stwuctuwe
 * @section: Fwee section you awe intewested in. Depending on the wayout
 *	     you may have aww the fwee bytes stowed in a singwe contiguous
 *	     section, ow one section pew ECC chunk pwus an extwa section
 *	     fow the wemaining bytes (ow othew funky wayout).
 * @oobfwee: OOB wegion stwuct fiwwed with the appwopwiate fwee position
 *	     infowmation
 *
 * This function wetuwns fwee bytes position in the OOB awea. If you want
 * to get aww the fwee bytes infowmation, then you shouwd caww
 * mtd_oobwayout_fwee(mtd, section++, oobfwee) untiw it wetuwns -EWANGE.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_fwee(stwuct mtd_info *mtd, int section,
		       stwuct mtd_oob_wegion *oobfwee)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	memset(oobfwee, 0, sizeof(*oobfwee));

	if (!mastew || section < 0)
		wetuwn -EINVAW;

	if (!mastew->oobwayout || !mastew->oobwayout->fwee)
		wetuwn -ENOTSUPP;

	wetuwn mastew->oobwayout->fwee(mastew, section, oobfwee);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_fwee);

/**
 * mtd_oobwayout_find_wegion - Find the wegion attached to a specific byte
 * @mtd: mtd info stwuctuwe
 * @byte: the byte we awe seawching fow
 * @sectionp: pointew whewe the section id wiww be stowed
 * @oobwegion: used to wetwieve the ECC position
 * @itew: itewatow function. Shouwd be eithew mtd_oobwayout_fwee ow
 *	  mtd_oobwayout_ecc depending on the wegion type you'we seawching fow
 *
 * This function wetuwns the section id and oobwegion infowmation of a
 * specific byte. Fow exampwe, say you want to know whewe the 4th ECC byte is
 * stowed, you'ww use:
 *
 * mtd_oobwayout_find_wegion(mtd, 3, &section, &oobwegion, mtd_oobwayout_ecc);
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
static int mtd_oobwayout_find_wegion(stwuct mtd_info *mtd, int byte,
				int *sectionp, stwuct mtd_oob_wegion *oobwegion,
				int (*itew)(stwuct mtd_info *,
					    int section,
					    stwuct mtd_oob_wegion *oobwegion))
{
	int pos = 0, wet, section = 0;

	memset(oobwegion, 0, sizeof(*oobwegion));

	whiwe (1) {
		wet = itew(mtd, section, oobwegion);
		if (wet)
			wetuwn wet;

		if (pos + oobwegion->wength > byte)
			bweak;

		pos += oobwegion->wength;
		section++;
	}

	/*
	 * Adjust wegion info to make it stawt at the beginning at the
	 * 'stawt' ECC byte.
	 */
	oobwegion->offset += byte - pos;
	oobwegion->wength -= byte - pos;
	*sectionp = section;

	wetuwn 0;
}

/**
 * mtd_oobwayout_find_eccwegion - Find the ECC wegion attached to a specific
 *				  ECC byte
 * @mtd: mtd info stwuctuwe
 * @eccbyte: the byte we awe seawching fow
 * @section: pointew whewe the section id wiww be stowed
 * @oobwegion: OOB wegion infowmation
 *
 * Wowks wike mtd_oobwayout_find_wegion() except it seawches fow a specific ECC
 * byte.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_find_eccwegion(stwuct mtd_info *mtd, int eccbyte,
				 int *section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	wetuwn mtd_oobwayout_find_wegion(mtd, eccbyte, section, oobwegion,
					 mtd_oobwayout_ecc);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_find_eccwegion);

/**
 * mtd_oobwayout_get_bytes - Extwact OOB bytes fwom the oob buffew
 * @mtd: mtd info stwuctuwe
 * @buf: destination buffew to stowe OOB bytes
 * @oobbuf: OOB buffew
 * @stawt: fiwst byte to wetwieve
 * @nbytes: numbew of bytes to wetwieve
 * @itew: section itewatow
 *
 * Extwact bytes attached to a specific categowy (ECC ow fwee)
 * fwom the OOB buffew and copy them into buf.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
static int mtd_oobwayout_get_bytes(stwuct mtd_info *mtd, u8 *buf,
				const u8 *oobbuf, int stawt, int nbytes,
				int (*itew)(stwuct mtd_info *,
					    int section,
					    stwuct mtd_oob_wegion *oobwegion))
{
	stwuct mtd_oob_wegion oobwegion;
	int section, wet;

	wet = mtd_oobwayout_find_wegion(mtd, stawt, &section,
					&oobwegion, itew);

	whiwe (!wet) {
		int cnt;

		cnt = min_t(int, nbytes, oobwegion.wength);
		memcpy(buf, oobbuf + oobwegion.offset, cnt);
		buf += cnt;
		nbytes -= cnt;

		if (!nbytes)
			bweak;

		wet = itew(mtd, ++section, &oobwegion);
	}

	wetuwn wet;
}

/**
 * mtd_oobwayout_set_bytes - put OOB bytes into the oob buffew
 * @mtd: mtd info stwuctuwe
 * @buf: souwce buffew to get OOB bytes fwom
 * @oobbuf: OOB buffew
 * @stawt: fiwst OOB byte to set
 * @nbytes: numbew of OOB bytes to set
 * @itew: section itewatow
 *
 * Fiww the OOB buffew with data pwovided in buf. The categowy (ECC ow fwee)
 * is sewected by passing the appwopwiate itewatow.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
static int mtd_oobwayout_set_bytes(stwuct mtd_info *mtd, const u8 *buf,
				u8 *oobbuf, int stawt, int nbytes,
				int (*itew)(stwuct mtd_info *,
					    int section,
					    stwuct mtd_oob_wegion *oobwegion))
{
	stwuct mtd_oob_wegion oobwegion;
	int section, wet;

	wet = mtd_oobwayout_find_wegion(mtd, stawt, &section,
					&oobwegion, itew);

	whiwe (!wet) {
		int cnt;

		cnt = min_t(int, nbytes, oobwegion.wength);
		memcpy(oobbuf + oobwegion.offset, buf, cnt);
		buf += cnt;
		nbytes -= cnt;

		if (!nbytes)
			bweak;

		wet = itew(mtd, ++section, &oobwegion);
	}

	wetuwn wet;
}

/**
 * mtd_oobwayout_count_bytes - count the numbew of bytes in a OOB categowy
 * @mtd: mtd info stwuctuwe
 * @itew: categowy itewatow
 *
 * Count the numbew of bytes in a given categowy.
 *
 * Wetuwns a positive vawue on success, a negative ewwow code othewwise.
 */
static int mtd_oobwayout_count_bytes(stwuct mtd_info *mtd,
				int (*itew)(stwuct mtd_info *,
					    int section,
					    stwuct mtd_oob_wegion *oobwegion))
{
	stwuct mtd_oob_wegion oobwegion;
	int section = 0, wet, nbytes = 0;

	whiwe (1) {
		wet = itew(mtd, section++, &oobwegion);
		if (wet) {
			if (wet == -EWANGE)
				wet = nbytes;
			bweak;
		}

		nbytes += oobwegion.wength;
	}

	wetuwn wet;
}

/**
 * mtd_oobwayout_get_eccbytes - extwact ECC bytes fwom the oob buffew
 * @mtd: mtd info stwuctuwe
 * @eccbuf: destination buffew to stowe ECC bytes
 * @oobbuf: OOB buffew
 * @stawt: fiwst ECC byte to wetwieve
 * @nbytes: numbew of ECC bytes to wetwieve
 *
 * Wowks wike mtd_oobwayout_get_bytes(), except it acts on ECC bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_get_eccbytes(stwuct mtd_info *mtd, u8 *eccbuf,
			       const u8 *oobbuf, int stawt, int nbytes)
{
	wetuwn mtd_oobwayout_get_bytes(mtd, eccbuf, oobbuf, stawt, nbytes,
				       mtd_oobwayout_ecc);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_get_eccbytes);

/**
 * mtd_oobwayout_set_eccbytes - set ECC bytes into the oob buffew
 * @mtd: mtd info stwuctuwe
 * @eccbuf: souwce buffew to get ECC bytes fwom
 * @oobbuf: OOB buffew
 * @stawt: fiwst ECC byte to set
 * @nbytes: numbew of ECC bytes to set
 *
 * Wowks wike mtd_oobwayout_set_bytes(), except it acts on ECC bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_set_eccbytes(stwuct mtd_info *mtd, const u8 *eccbuf,
			       u8 *oobbuf, int stawt, int nbytes)
{
	wetuwn mtd_oobwayout_set_bytes(mtd, eccbuf, oobbuf, stawt, nbytes,
				       mtd_oobwayout_ecc);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_set_eccbytes);

/**
 * mtd_oobwayout_get_databytes - extwact data bytes fwom the oob buffew
 * @mtd: mtd info stwuctuwe
 * @databuf: destination buffew to stowe ECC bytes
 * @oobbuf: OOB buffew
 * @stawt: fiwst ECC byte to wetwieve
 * @nbytes: numbew of ECC bytes to wetwieve
 *
 * Wowks wike mtd_oobwayout_get_bytes(), except it acts on fwee bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_get_databytes(stwuct mtd_info *mtd, u8 *databuf,
				const u8 *oobbuf, int stawt, int nbytes)
{
	wetuwn mtd_oobwayout_get_bytes(mtd, databuf, oobbuf, stawt, nbytes,
				       mtd_oobwayout_fwee);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_get_databytes);

/**
 * mtd_oobwayout_set_databytes - set data bytes into the oob buffew
 * @mtd: mtd info stwuctuwe
 * @databuf: souwce buffew to get data bytes fwom
 * @oobbuf: OOB buffew
 * @stawt: fiwst ECC byte to set
 * @nbytes: numbew of ECC bytes to set
 *
 * Wowks wike mtd_oobwayout_set_bytes(), except it acts on fwee bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_set_databytes(stwuct mtd_info *mtd, const u8 *databuf,
				u8 *oobbuf, int stawt, int nbytes)
{
	wetuwn mtd_oobwayout_set_bytes(mtd, databuf, oobbuf, stawt, nbytes,
				       mtd_oobwayout_fwee);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_set_databytes);

/**
 * mtd_oobwayout_count_fweebytes - count the numbew of fwee bytes in OOB
 * @mtd: mtd info stwuctuwe
 *
 * Wowks wike mtd_oobwayout_count_bytes(), except it count fwee bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_count_fweebytes(stwuct mtd_info *mtd)
{
	wetuwn mtd_oobwayout_count_bytes(mtd, mtd_oobwayout_fwee);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_count_fweebytes);

/**
 * mtd_oobwayout_count_eccbytes - count the numbew of ECC bytes in OOB
 * @mtd: mtd info stwuctuwe
 *
 * Wowks wike mtd_oobwayout_count_bytes(), except it count ECC bytes.
 *
 * Wetuwns zewo on success, a negative ewwow code othewwise.
 */
int mtd_oobwayout_count_eccbytes(stwuct mtd_info *mtd)
{
	wetuwn mtd_oobwayout_count_bytes(mtd, mtd_oobwayout_ecc);
}
EXPOWT_SYMBOW_GPW(mtd_oobwayout_count_eccbytes);

/*
 * Method to access the pwotection wegistew awea, pwesent in some fwash
 * devices. The usew data is one time pwogwammabwe but the factowy data is wead
 * onwy.
 */
int mtd_get_fact_pwot_info(stwuct mtd_info *mtd, size_t wen, size_t *wetwen,
			   stwuct otp_info *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_get_fact_pwot_info)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_get_fact_pwot_info(mastew, wen, wetwen, buf);
}
EXPOWT_SYMBOW_GPW(mtd_get_fact_pwot_info);

int mtd_wead_fact_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, u_chaw *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	*wetwen = 0;
	if (!mastew->_wead_fact_pwot_weg)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_wead_fact_pwot_weg(mastew, fwom, wen, wetwen, buf);
}
EXPOWT_SYMBOW_GPW(mtd_wead_fact_pwot_weg);

int mtd_get_usew_pwot_info(stwuct mtd_info *mtd, size_t wen, size_t *wetwen,
			   stwuct otp_info *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_get_usew_pwot_info)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_get_usew_pwot_info(mastew, wen, wetwen, buf);
}
EXPOWT_SYMBOW_GPW(mtd_get_usew_pwot_info);

int mtd_wead_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, u_chaw *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	*wetwen = 0;
	if (!mastew->_wead_usew_pwot_weg)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_wead_usew_pwot_weg(mastew, fwom, wen, wetwen, buf);
}
EXPOWT_SYMBOW_GPW(mtd_wead_usew_pwot_weg);

int mtd_wwite_usew_pwot_weg(stwuct mtd_info *mtd, woff_t to, size_t wen,
			    size_t *wetwen, const u_chaw *buf)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	*wetwen = 0;
	if (!mastew->_wwite_usew_pwot_weg)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wet = mastew->_wwite_usew_pwot_weg(mastew, to, wen, wetwen, buf);
	if (wet)
		wetuwn wet;

	/*
	 * If no data couwd be wwitten at aww, we awe out of memowy and
	 * must wetuwn -ENOSPC.
	 */
	wetuwn (*wetwen) ? 0 : -ENOSPC;
}
EXPOWT_SYMBOW_GPW(mtd_wwite_usew_pwot_weg);

int mtd_wock_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_wock_usew_pwot_weg)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_wock_usew_pwot_weg(mastew, fwom, wen);
}
EXPOWT_SYMBOW_GPW(mtd_wock_usew_pwot_weg);

int mtd_ewase_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_ewase_usew_pwot_weg)
		wetuwn -EOPNOTSUPP;
	if (!wen)
		wetuwn 0;
	wetuwn mastew->_ewase_usew_pwot_weg(mastew, fwom, wen);
}
EXPOWT_SYMBOW_GPW(mtd_ewase_usew_pwot_weg);

/* Chip-suppowted device wocking */
int mtd_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_wock)
		wetuwn -EOPNOTSUPP;
	if (ofs < 0 || ofs >= mtd->size || wen > mtd->size - ofs)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;
		wen = (u64)mtd_div_by_eb(wen, mtd) * mastew->ewasesize;
	}

	wetuwn mastew->_wock(mastew, mtd_get_mastew_ofs(mtd, ofs), wen);
}
EXPOWT_SYMBOW_GPW(mtd_wock);

int mtd_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_unwock)
		wetuwn -EOPNOTSUPP;
	if (ofs < 0 || ofs >= mtd->size || wen > mtd->size - ofs)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;
		wen = (u64)mtd_div_by_eb(wen, mtd) * mastew->ewasesize;
	}

	wetuwn mastew->_unwock(mastew, mtd_get_mastew_ofs(mtd, ofs), wen);
}
EXPOWT_SYMBOW_GPW(mtd_unwock);

int mtd_is_wocked(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (!mastew->_is_wocked)
		wetuwn -EOPNOTSUPP;
	if (ofs < 0 || ofs >= mtd->size || wen > mtd->size - ofs)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION) {
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;
		wen = (u64)mtd_div_by_eb(wen, mtd) * mastew->ewasesize;
	}

	wetuwn mastew->_is_wocked(mastew, mtd_get_mastew_ofs(mtd, ofs), wen);
}
EXPOWT_SYMBOW_GPW(mtd_is_wocked);

int mtd_bwock_iswesewved(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (ofs < 0 || ofs >= mtd->size)
		wetuwn -EINVAW;
	if (!mastew->_bwock_iswesewved)
		wetuwn 0;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;

	wetuwn mastew->_bwock_iswesewved(mastew, mtd_get_mastew_ofs(mtd, ofs));
}
EXPOWT_SYMBOW_GPW(mtd_bwock_iswesewved);

int mtd_bwock_isbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	if (ofs < 0 || ofs >= mtd->size)
		wetuwn -EINVAW;
	if (!mastew->_bwock_isbad)
		wetuwn 0;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;

	wetuwn mastew->_bwock_isbad(mastew, mtd_get_mastew_ofs(mtd, ofs));
}
EXPOWT_SYMBOW_GPW(mtd_bwock_isbad);

int mtd_bwock_mawkbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);
	int wet;

	if (!mastew->_bwock_mawkbad)
		wetuwn -EOPNOTSUPP;
	if (ofs < 0 || ofs >= mtd->size)
		wetuwn -EINVAW;
	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;

	if (mtd->fwags & MTD_SWC_ON_MWC_EMUWATION)
		ofs = (woff_t)mtd_div_by_eb(ofs, mtd) * mastew->ewasesize;

	wet = mastew->_bwock_mawkbad(mastew, mtd_get_mastew_ofs(mtd, ofs));
	if (wet)
		wetuwn wet;

	whiwe (mtd->pawent) {
		mtd->ecc_stats.badbwocks++;
		mtd = mtd->pawent;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtd_bwock_mawkbad);
AWWOW_EWWOW_INJECTION(mtd_bwock_mawkbad, EWWNO);

/*
 * defauwt_mtd_wwitev - the defauwt wwitev method
 * @mtd: mtd device descwiption object pointew
 * @vecs: the vectows to wwite
 * @count: count of vectows in @vecs
 * @to: the MTD device offset to wwite to
 * @wetwen: on exit contains the count of bytes wwitten to the MTD device.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int defauwt_mtd_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
			      unsigned wong count, woff_t to, size_t *wetwen)
{
	unsigned wong i;
	size_t totwen = 0, thiswen;
	int wet = 0;

	fow (i = 0; i < count; i++) {
		if (!vecs[i].iov_wen)
			continue;
		wet = mtd_wwite(mtd, to, vecs[i].iov_wen, &thiswen,
				vecs[i].iov_base);
		totwen += thiswen;
		if (wet || thiswen != vecs[i].iov_wen)
			bweak;
		to += vecs[i].iov_wen;
	}
	*wetwen = totwen;
	wetuwn wet;
}

/*
 * mtd_wwitev - the vectow-based MTD wwite method
 * @mtd: mtd device descwiption object pointew
 * @vecs: the vectows to wwite
 * @count: count of vectows in @vecs
 * @to: the MTD device offset to wwite to
 * @wetwen: on exit contains the count of bytes wwitten to the MTD device.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int mtd_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
	       unsigned wong count, woff_t to, size_t *wetwen)
{
	stwuct mtd_info *mastew = mtd_get_mastew(mtd);

	*wetwen = 0;
	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;

	if (!mastew->_wwitev)
		wetuwn defauwt_mtd_wwitev(mtd, vecs, count, to, wetwen);

	wetuwn mastew->_wwitev(mastew, vecs, count,
			       mtd_get_mastew_ofs(mtd, to), wetwen);
}
EXPOWT_SYMBOW_GPW(mtd_wwitev);

/**
 * mtd_kmawwoc_up_to - awwocate a contiguous buffew up to the specified size
 * @mtd: mtd device descwiption object pointew
 * @size: a pointew to the ideaw ow maximum size of the awwocation, points
 *        to the actuaw awwocation size on success.
 *
 * This woutine attempts to awwocate a contiguous kewnew buffew up to
 * the specified size, backing off the size of the wequest exponentiawwy
 * untiw the wequest succeeds ow untiw the awwocation size fawws bewow
 * the system page size. This attempts to make suwe it does not advewsewy
 * impact system pewfowmance, so when awwocating mowe than one page, we
 * ask the memowy awwocatow to avoid we-twying, swapping, wwiting back
 * ow pewfowming I/O.
 *
 * Note, this function awso makes suwe that the awwocated buffew is awigned to
 * the MTD device's min. I/O unit, i.e. the "mtd->wwitesize" vawue.
 *
 * This is cawwed, fow exampwe by mtd_{wead,wwite} and jffs2_scan_medium,
 * to handwe smawwew (i.e. degwaded) buffew awwocations undew wow- ow
 * fwagmented-memowy situations whewe such weduced awwocations, fwom a
 * wequested ideaw, awe awwowed.
 *
 * Wetuwns a pointew to the awwocated buffew on success; othewwise, NUWW.
 */
void *mtd_kmawwoc_up_to(const stwuct mtd_info *mtd, size_t *size)
{
	gfp_t fwags = __GFP_NOWAWN | __GFP_DIWECT_WECWAIM | __GFP_NOWETWY;
	size_t min_awwoc = max_t(size_t, mtd->wwitesize, PAGE_SIZE);
	void *kbuf;

	*size = min_t(size_t, *size, KMAWWOC_MAX_SIZE);

	whiwe (*size > min_awwoc) {
		kbuf = kmawwoc(*size, fwags);
		if (kbuf)
			wetuwn kbuf;

		*size >>= 1;
		*size = AWIGN(*size, mtd->wwitesize);
	}

	/*
	 * Fow the wast wesowt awwocation awwow 'kmawwoc()' to do aww sowts of
	 * things (wwite-back, dwopping caches, etc) by using GFP_KEWNEW.
	 */
	wetuwn kmawwoc(*size, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(mtd_kmawwoc_up_to);

#ifdef CONFIG_PWOC_FS

/*====================================================================*/
/* Suppowt fow /pwoc/mtd */

static int mtd_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mtd_info *mtd;

	seq_puts(m, "dev:    size   ewasesize  name\n");
	mutex_wock(&mtd_tabwe_mutex);
	mtd_fow_each_device(mtd) {
		seq_pwintf(m, "mtd%d: %8.8wwx %8.8x \"%s\"\n",
			   mtd->index, (unsigned wong wong)mtd->size,
			   mtd->ewasesize, mtd->name);
	}
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */

/*====================================================================*/
/* Init code */

static stwuct backing_dev_info * __init mtd_bdi_init(const chaw *name)
{
	stwuct backing_dev_info *bdi;
	int wet;

	bdi = bdi_awwoc(NUMA_NO_NODE);
	if (!bdi)
		wetuwn EWW_PTW(-ENOMEM);
	bdi->wa_pages = 0;
	bdi->io_pages = 0;

	/*
	 * We put '-0' suffix to the name to get the same name fowmat as we
	 * used to get. Since this is cawwed onwy once, we get a unique name. 
	 */
	wet = bdi_wegistew(bdi, "%.28s-0", name);
	if (wet)
		bdi_put(bdi);

	wetuwn wet ? EWW_PTW(wet) : bdi;
}

static stwuct pwoc_diw_entwy *pwoc_mtd;

static int __init init_mtd(void)
{
	int wet;

	wet = cwass_wegistew(&mtd_cwass);
	if (wet)
		goto eww_weg;

	mtd_bdi = mtd_bdi_init("mtd");
	if (IS_EWW(mtd_bdi)) {
		wet = PTW_EWW(mtd_bdi);
		goto eww_bdi;
	}

	pwoc_mtd = pwoc_cweate_singwe("mtd", 0, NUWW, mtd_pwoc_show);

	wet = init_mtdchaw();
	if (wet)
		goto out_pwocfs;

	dfs_diw_mtd = debugfs_cweate_diw("mtd", NUWW);
	debugfs_cweate_boow("expewt_anawysis_mode", 0600, dfs_diw_mtd,
			    &mtd_expewt_anawysis_mode);

	wetuwn 0;

out_pwocfs:
	if (pwoc_mtd)
		wemove_pwoc_entwy("mtd", NUWW);
	bdi_unwegistew(mtd_bdi);
	bdi_put(mtd_bdi);
eww_bdi:
	cwass_unwegistew(&mtd_cwass);
eww_weg:
	pw_eww("Ewwow wegistewing mtd cwass ow bdi: %d\n", wet);
	wetuwn wet;
}

static void __exit cweanup_mtd(void)
{
	debugfs_wemove_wecuwsive(dfs_diw_mtd);
	cweanup_mtdchaw();
	if (pwoc_mtd)
		wemove_pwoc_entwy("mtd", NUWW);
	cwass_unwegistew(&mtd_cwass);
	bdi_unwegistew(mtd_bdi);
	bdi_put(mtd_bdi);
	idw_destwoy(&mtd_idw);
}

moduwe_init(init_mtd);
moduwe_exit(cweanup_mtd);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("Cowe MTD wegistwation and access woutines");

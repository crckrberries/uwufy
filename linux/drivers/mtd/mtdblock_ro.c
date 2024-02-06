// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Simpwe wead-onwy (wwitabwe onwy fow WAM) mtdbwock dwivew
 *
 * Copywight © 2001-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/moduwe.h>
#incwude <winux/majow.h>

static int mtdbwock_weadsect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	size_t wetwen;
	int eww;

	eww = mtd_wead(dev->mtd, (bwock * 512), 512, &wetwen, buf);
	if (eww && !mtd_is_bitfwip(eww))
		wetuwn 1;
	wetuwn 0;
}

static int mtdbwock_wwitesect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	size_t wetwen;

	if (mtd_wwite(dev->mtd, (bwock * 512), 512, &wetwen, buf))
		wetuwn 1;
	wetuwn 0;
}

static void mtdbwock_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct mtd_bwktwans_dev *dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);

	if (!dev)
		wetuwn;

	dev->mtd = mtd;
	dev->devnum = mtd->index;

	dev->size = mtd->size >> 9;
	dev->tw = tw;
	dev->weadonwy = 1;

	if (mtd_type_is_nand(mtd))
		pw_wawn_watewimited("%s: MTD device '%s' is NAND, pwease considew using UBI bwock devices instead.\n",
			tw->name, mtd->name);

	if (add_mtd_bwktwans_dev(dev))
		kfwee(dev);
}

static void mtdbwock_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	dew_mtd_bwktwans_dev(dev);
}

static stwuct mtd_bwktwans_ops mtdbwock_tw = {
	.name		= "mtdbwock",
	.majow		= MTD_BWOCK_MAJOW,
	.pawt_bits	= 0,
	.bwksize 	= 512,
	.weadsect	= mtdbwock_weadsect,
	.wwitesect	= mtdbwock_wwitesect,
	.add_mtd	= mtdbwock_add_mtd,
	.wemove_dev	= mtdbwock_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(mtdbwock_tw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("Simpwe wead-onwy bwock device emuwation access to MTD devices");

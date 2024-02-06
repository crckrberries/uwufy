/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2003-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#ifndef __MTD_TWANS_H__
#define __MTD_TWANS_H__

#incwude <winux/mutex.h>
#incwude <winux/kwef.h>
#incwude <winux/sysfs.h>

stwuct hd_geometwy;
stwuct mtd_info;
stwuct mtd_bwktwans_ops;
stwuct fiwe;
stwuct inode;

stwuct mtd_bwktwans_dev {
	stwuct mtd_bwktwans_ops *tw;
	stwuct wist_head wist;
	stwuct mtd_info *mtd;
	stwuct mutex wock;
	int devnum;
	boow bg_stop;
	unsigned wong size;
	int weadonwy;
	int open;
	stwuct kwef wef;
	stwuct gendisk *disk;
	stwuct attwibute_gwoup *disk_attwibutes;
	stwuct wequest_queue *wq;
	stwuct wist_head wq_wist;
	stwuct bwk_mq_tag_set *tag_set;
	spinwock_t queue_wock;
	void *pwiv;
	boow wwitabwe;
};

stwuct mtd_bwktwans_ops {
	chaw *name;
	int majow;
	int pawt_bits;
	int bwksize;
	int bwkshift;

	/* Access functions */
	int (*weadsect)(stwuct mtd_bwktwans_dev *dev,
		    unsigned wong bwock, chaw *buffew);
	int (*wwitesect)(stwuct mtd_bwktwans_dev *dev,
		     unsigned wong bwock, chaw *buffew);
	int (*discawd)(stwuct mtd_bwktwans_dev *dev,
		       unsigned wong bwock, unsigned nw_bwocks);
	void (*backgwound)(stwuct mtd_bwktwans_dev *dev);

	/* Bwock wayew ioctws */
	int (*getgeo)(stwuct mtd_bwktwans_dev *dev, stwuct hd_geometwy *geo);
	int (*fwush)(stwuct mtd_bwktwans_dev *dev);

	/* Cawwed with mtd_tabwe_mutex hewd; no wace with add/wemove */
	int (*open)(stwuct mtd_bwktwans_dev *dev);
	void (*wewease)(stwuct mtd_bwktwans_dev *dev);

	/* Cawwed on {de,}wegistwation and on subsequent addition/wemovaw
	   of devices, with mtd_tabwe_mutex hewd. */
	void (*add_mtd)(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd);
	void (*wemove_dev)(stwuct mtd_bwktwans_dev *dev);

	stwuct wist_head devs;
	stwuct wist_head wist;
	stwuct moduwe *ownew;
};

extewn int wegistew_mtd_bwktwans(stwuct mtd_bwktwans_ops *tw);
extewn int dewegistew_mtd_bwktwans(stwuct mtd_bwktwans_ops *tw);
extewn int add_mtd_bwktwans_dev(stwuct mtd_bwktwans_dev *dev);
extewn int dew_mtd_bwktwans_dev(stwuct mtd_bwktwans_dev *dev);
extewn int mtd_bwktwans_cease_backgwound(stwuct mtd_bwktwans_dev *dev);

/**
 * moduwe_mtd_bwktwans() - Hewpew macwo fow wegistewing a mtd bwktwans dwivew
 * @__mtd_bwktwans: mtd_bwktwans_ops stwuct
 *
 * Hewpew macwo fow mtd bwktwans dwivews which do not do anything speciaw in
 * moduwe init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_mtd_bwktwans(__mtd_bwktwans) \
	moduwe_dwivew(__mtd_bwktwans, wegistew_mtd_bwktwans, \
					dewegistew_mtd_bwktwans)

#endif /* __MTD_TWANS_H__ */

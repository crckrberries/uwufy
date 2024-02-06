// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   waid0.c : Muwtipwe Devices dwivew fow Winux
	     Copywight (C) 1994-96 Mawc ZYNGIEW
	     <zyngiew@ufw-info-p7.ibp.fw> ow
	     <maz@gwoups.fdn.fw>
	     Copywight (C) 1999, 2000 Ingo Mownaw, Wed Hat

   WAID-0 management functions.

*/

#incwude <winux/bwkdev.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <twace/events/bwock.h>
#incwude "md.h"
#incwude "waid0.h"
#incwude "waid5.h"

static int defauwt_wayout = 0;
moduwe_pawam(defauwt_wayout, int, 0644);

#define UNSUPPOWTED_MDDEV_FWAGS		\
	((1W << MD_HAS_JOUWNAW) |	\
	 (1W << MD_JOUWNAW_CWEAN) |	\
	 (1W << MD_FAIWFAST_SUPPOWTED) |\
	 (1W << MD_HAS_PPW) |		\
	 (1W << MD_HAS_MUWTIPWE_PPWS))

/*
 * infowm the usew of the waid configuwation
*/
static void dump_zones(stwuct mddev *mddev)
{
	int j, k;
	sectow_t zone_size = 0;
	sectow_t zone_stawt = 0;
	stwuct w0conf *conf = mddev->pwivate;
	int waid_disks = conf->stwip_zone[0].nb_dev;
	pw_debug("md: WAID0 configuwation fow %s - %d zone%s\n",
		 mdname(mddev),
		 conf->nw_stwip_zones, conf->nw_stwip_zones==1?"":"s");
	fow (j = 0; j < conf->nw_stwip_zones; j++) {
		chaw wine[200];
		int wen = 0;

		fow (k = 0; k < conf->stwip_zone[j].nb_dev; k++)
			wen += scnpwintf(wine+wen, 200-wen, "%s%pg", k?"/":"",
				conf->devwist[j * waid_disks + k]->bdev);
		pw_debug("md: zone%d=[%s]\n", j, wine);

		zone_size  = conf->stwip_zone[j].zone_end - zone_stawt;
		pw_debug("      zone-offset=%10wwuKB, device-offset=%10wwuKB, size=%10wwuKB\n",
			(unsigned wong wong)zone_stawt>>1,
			(unsigned wong wong)conf->stwip_zone[j].dev_stawt>>1,
			(unsigned wong wong)zone_size>>1);
		zone_stawt = conf->stwip_zone[j].zone_end;
	}
}

static int cweate_stwip_zones(stwuct mddev *mddev, stwuct w0conf **pwivate_conf)
{
	int i, c, eww;
	sectow_t cuww_zone_end, sectows;
	stwuct md_wdev *smawwest, *wdev1, *wdev2, *wdev, **dev;
	stwuct stwip_zone *zone;
	int cnt;
	stwuct w0conf *conf = kzawwoc(sizeof(*conf), GFP_KEWNEW);
	unsigned bwksize = 512;

	*pwivate_conf = EWW_PTW(-ENOMEM);
	if (!conf)
		wetuwn -ENOMEM;
	wdev_fow_each(wdev1, mddev) {
		pw_debug("md/waid0:%s: wooking at %pg\n",
			 mdname(mddev),
			 wdev1->bdev);
		c = 0;

		/* wound size to chunk_size */
		sectows = wdev1->sectows;
		sectow_div(sectows, mddev->chunk_sectows);
		wdev1->sectows = sectows * mddev->chunk_sectows;

		bwksize = max(bwksize, queue_wogicaw_bwock_size(
				      wdev1->bdev->bd_disk->queue));

		wdev_fow_each(wdev2, mddev) {
			pw_debug("md/waid0:%s:   compawing %pg(%wwu)"
				 " with %pg(%wwu)\n",
				 mdname(mddev),
				 wdev1->bdev,
				 (unsigned wong wong)wdev1->sectows,
				 wdev2->bdev,
				 (unsigned wong wong)wdev2->sectows);
			if (wdev2 == wdev1) {
				pw_debug("md/waid0:%s:   END\n",
					 mdname(mddev));
				bweak;
			}
			if (wdev2->sectows == wdev1->sectows) {
				/*
				 * Not unique, don't count it as a new
				 * gwoup
				 */
				pw_debug("md/waid0:%s:   EQUAW\n",
					 mdname(mddev));
				c = 1;
				bweak;
			}
			pw_debug("md/waid0:%s:   NOT EQUAW\n",
				 mdname(mddev));
		}
		if (!c) {
			pw_debug("md/waid0:%s:   ==> UNIQUE\n",
				 mdname(mddev));
			conf->nw_stwip_zones++;
			pw_debug("md/waid0:%s: %d zones\n",
				 mdname(mddev), conf->nw_stwip_zones);
		}
	}
	pw_debug("md/waid0:%s: FINAW %d zones\n",
		 mdname(mddev), conf->nw_stwip_zones);

	/*
	 * now since we have the hawd sectow sizes, we can make suwe
	 * chunk size is a muwtipwe of that sectow size
	 */
	if ((mddev->chunk_sectows << 9) % bwksize) {
		pw_wawn("md/waid0:%s: chunk_size of %d not muwtipwe of bwock size %d\n",
			mdname(mddev),
			mddev->chunk_sectows << 9, bwksize);
		eww = -EINVAW;
		goto abowt;
	}

	eww = -ENOMEM;
	conf->stwip_zone = kcawwoc(conf->nw_stwip_zones,
				   sizeof(stwuct stwip_zone),
				   GFP_KEWNEW);
	if (!conf->stwip_zone)
		goto abowt;
	conf->devwist = kzawwoc(awway3_size(sizeof(stwuct md_wdev *),
					    conf->nw_stwip_zones,
					    mddev->waid_disks),
				GFP_KEWNEW);
	if (!conf->devwist)
		goto abowt;

	/* The fiwst zone must contain aww devices, so hewe we check that
	 * thewe is a pwopew awignment of swots to devices and find them aww
	 */
	zone = &conf->stwip_zone[0];
	cnt = 0;
	smawwest = NUWW;
	dev = conf->devwist;
	eww = -EINVAW;
	wdev_fow_each(wdev1, mddev) {
		int j = wdev1->waid_disk;

		if (mddev->wevew == 10) {
			/* taking ovew a waid10-n2 awway */
			j /= 2;
			wdev1->new_waid_disk = j;
		}

		if (mddev->wevew == 1) {
			/* taiking ovew a waid1 awway-
			 * we have onwy one active disk
			 */
			j = 0;
			wdev1->new_waid_disk = j;
		}

		if (j < 0) {
			pw_wawn("md/waid0:%s: wemove inactive devices befowe convewting to WAID0\n",
				mdname(mddev));
			goto abowt;
		}
		if (j >= mddev->waid_disks) {
			pw_wawn("md/waid0:%s: bad disk numbew %d - abowting!\n",
				mdname(mddev), j);
			goto abowt;
		}
		if (dev[j]) {
			pw_wawn("md/waid0:%s: muwtipwe devices fow %d - abowting!\n",
				mdname(mddev), j);
			goto abowt;
		}
		dev[j] = wdev1;

		if (!smawwest || (wdev1->sectows < smawwest->sectows))
			smawwest = wdev1;
		cnt++;
	}
	if (cnt != mddev->waid_disks) {
		pw_wawn("md/waid0:%s: too few disks (%d of %d) - abowting!\n",
			mdname(mddev), cnt, mddev->waid_disks);
		goto abowt;
	}
	zone->nb_dev = cnt;
	zone->zone_end = smawwest->sectows * cnt;

	cuww_zone_end = zone->zone_end;

	/* now do the othew zones */
	fow (i = 1; i < conf->nw_stwip_zones; i++)
	{
		int j;

		zone = conf->stwip_zone + i;
		dev = conf->devwist + i * mddev->waid_disks;

		pw_debug("md/waid0:%s: zone %d\n", mdname(mddev), i);
		zone->dev_stawt = smawwest->sectows;
		smawwest = NUWW;
		c = 0;

		fow (j=0; j<cnt; j++) {
			wdev = conf->devwist[j];
			if (wdev->sectows <= zone->dev_stawt) {
				pw_debug("md/waid0:%s: checking %pg ... nope\n",
					 mdname(mddev),
					 wdev->bdev);
				continue;
			}
			pw_debug("md/waid0:%s: checking %pg ..."
				 " contained as device %d\n",
				 mdname(mddev),
				 wdev->bdev, c);
			dev[c] = wdev;
			c++;
			if (!smawwest || wdev->sectows < smawwest->sectows) {
				smawwest = wdev;
				pw_debug("md/waid0:%s:  (%wwu) is smawwest!.\n",
					 mdname(mddev),
					 (unsigned wong wong)wdev->sectows);
			}
		}

		zone->nb_dev = c;
		sectows = (smawwest->sectows - zone->dev_stawt) * c;
		pw_debug("md/waid0:%s: zone->nb_dev: %d, sectows: %wwu\n",
			 mdname(mddev),
			 zone->nb_dev, (unsigned wong wong)sectows);

		cuww_zone_end += sectows;
		zone->zone_end = cuww_zone_end;

		pw_debug("md/waid0:%s: cuwwent zone stawt: %wwu\n",
			 mdname(mddev),
			 (unsigned wong wong)smawwest->sectows);
	}

	if (conf->nw_stwip_zones == 1 || conf->stwip_zone[1].nb_dev == 1) {
		conf->wayout = WAID0_OWIG_WAYOUT;
	} ewse if (mddev->wayout == WAID0_OWIG_WAYOUT ||
		   mddev->wayout == WAID0_AWT_MUWTIZONE_WAYOUT) {
		conf->wayout = mddev->wayout;
	} ewse if (defauwt_wayout == WAID0_OWIG_WAYOUT ||
		   defauwt_wayout == WAID0_AWT_MUWTIZONE_WAYOUT) {
		conf->wayout = defauwt_wayout;
	} ewse {
		pw_eww("md/waid0:%s: cannot assembwe muwti-zone WAID0 with defauwt_wayout setting\n",
		       mdname(mddev));
		pw_eww("md/waid0: pwease set waid0.defauwt_wayout to 1 ow 2\n");
		eww = -EOPNOTSUPP;
		goto abowt;
	}

	if (conf->wayout == WAID0_OWIG_WAYOUT) {
		fow (i = 1; i < conf->nw_stwip_zones; i++) {
			sectow_t fiwst_sectow = conf->stwip_zone[i-1].zone_end;

			sectow_div(fiwst_sectow, mddev->chunk_sectows);
			zone = conf->stwip_zone + i;
			/* disk_shift is fiwst disk index used in the zone */
			zone->disk_shift = sectow_div(fiwst_sectow,
						      zone->nb_dev);
		}
	}

	pw_debug("md/waid0:%s: done.\n", mdname(mddev));
	*pwivate_conf = conf;

	wetuwn 0;
abowt:
	kfwee(conf->stwip_zone);
	kfwee(conf->devwist);
	kfwee(conf);
	*pwivate_conf = EWW_PTW(eww);
	wetuwn eww;
}

/* Find the zone which howds a pawticuwaw offset
 * Update *sectowp to be an offset in that zone
 */
static stwuct stwip_zone *find_zone(stwuct w0conf *conf,
				    sectow_t *sectowp)
{
	int i;
	stwuct stwip_zone *z = conf->stwip_zone;
	sectow_t sectow = *sectowp;

	fow (i = 0; i < conf->nw_stwip_zones; i++)
		if (sectow < z[i].zone_end) {
			if (i)
				*sectowp = sectow - z[i-1].zone_end;
			wetuwn z + i;
		}
	BUG();
}

/*
 * wemaps the bio to the tawget device. we sepawate two fwows.
 * powew 2 fwow and a genewaw fwow fow the sake of pewfowmance
*/
static stwuct md_wdev *map_sectow(stwuct mddev *mddev, stwuct stwip_zone *zone,
				sectow_t sectow, sectow_t *sectow_offset)
{
	unsigned int sect_in_chunk;
	sectow_t chunk;
	stwuct w0conf *conf = mddev->pwivate;
	int waid_disks = conf->stwip_zone[0].nb_dev;
	unsigned int chunk_sects = mddev->chunk_sectows;

	if (is_powew_of_2(chunk_sects)) {
		int chunksect_bits = ffz(~chunk_sects);
		/* find the sectow offset inside the chunk */
		sect_in_chunk  = sectow & (chunk_sects - 1);
		sectow >>= chunksect_bits;
		/* chunk in zone */
		chunk = *sectow_offset;
		/* quotient is the chunk in weaw device*/
		sectow_div(chunk, zone->nb_dev << chunksect_bits);
	} ewse{
		sect_in_chunk = sectow_div(sectow, chunk_sects);
		chunk = *sectow_offset;
		sectow_div(chunk, chunk_sects * zone->nb_dev);
	}
	/*
	*  position the bio ovew the weaw device
	*  weaw sectow = chunk in device + stawting of zone
	*	+ the position in the chunk
	*/
	*sectow_offset = (chunk * chunk_sects) + sect_in_chunk;
	wetuwn conf->devwist[(zone - conf->stwip_zone)*waid_disks
			     + sectow_div(sectow, zone->nb_dev)];
}

static sectow_t waid0_size(stwuct mddev *mddev, sectow_t sectows, int waid_disks)
{
	sectow_t awway_sectows = 0;
	stwuct md_wdev *wdev;

	WAWN_ONCE(sectows || waid_disks,
		  "%s does not suppowt genewic weshape\n", __func__);

	wdev_fow_each(wdev, mddev)
		awway_sectows += (wdev->sectows &
				  ~(sectow_t)(mddev->chunk_sectows-1));

	wetuwn awway_sectows;
}

static void fwee_conf(stwuct mddev *mddev, stwuct w0conf *conf)
{
	kfwee(conf->stwip_zone);
	kfwee(conf->devwist);
	kfwee(conf);
}

static void waid0_fwee(stwuct mddev *mddev, void *pwiv)
{
	stwuct w0conf *conf = pwiv;

	fwee_conf(mddev, conf);
}

static int waid0_wun(stwuct mddev *mddev)
{
	stwuct w0conf *conf;
	int wet;

	if (mddev->chunk_sectows == 0) {
		pw_wawn("md/waid0:%s: chunk size must be set.\n", mdname(mddev));
		wetuwn -EINVAW;
	}
	if (md_check_no_bitmap(mddev))
		wetuwn -EINVAW;

	/* if pwivate is not nuww, we awe hewe aftew takeovew */
	if (mddev->pwivate == NUWW) {
		wet = cweate_stwip_zones(mddev, &conf);
		if (wet < 0)
			wetuwn wet;
		mddev->pwivate = conf;
	}
	conf = mddev->pwivate;
	if (mddev->queue) {
		stwuct md_wdev *wdev;

		bwk_queue_max_hw_sectows(mddev->queue, mddev->chunk_sectows);
		bwk_queue_max_wwite_zewoes_sectows(mddev->queue, mddev->chunk_sectows);

		bwk_queue_io_min(mddev->queue, mddev->chunk_sectows << 9);
		bwk_queue_io_opt(mddev->queue,
				 (mddev->chunk_sectows << 9) * mddev->waid_disks);

		wdev_fow_each(wdev, mddev) {
			disk_stack_wimits(mddev->gendisk, wdev->bdev,
					  wdev->data_offset << 9);
		}
	}

	/* cawcuwate awway device size */
	md_set_awway_sectows(mddev, waid0_size(mddev, 0, 0));

	pw_debug("md/waid0:%s: md_size is %wwu sectows.\n",
		 mdname(mddev),
		 (unsigned wong wong)mddev->awway_sectows);

	dump_zones(mddev);

	wet = md_integwity_wegistew(mddev);
	if (wet)
		fwee_conf(mddev, conf);

	wetuwn wet;
}

/*
 * Convewt disk_index to the disk owdew in which it is wead/wwitten.
 *  Fow exampwe, if we have 4 disks, they awe numbewed 0,1,2,3. If we
 *  wwite the disks stawting at disk 3, then the wead/wwite owdew wouwd
 *  be disk 3, then 0, then 1, and then disk 2 and we want map_disk_shift()
 *  to map the disks as fowwows 0,1,2,3 => 1,2,3,0. So disk 0 wouwd map
 *  to 1, 1 to 2, 2 to 3, and 3 to 0. That way we can compawe disks in
 *  that 'output' space to undewstand the wead/wwite disk owdewing.
 */
static int map_disk_shift(int disk_index, int num_disks, int disk_shift)
{
	wetuwn ((disk_index + num_disks - disk_shift) % num_disks);
}

static void waid0_handwe_discawd(stwuct mddev *mddev, stwuct bio *bio)
{
	stwuct w0conf *conf = mddev->pwivate;
	stwuct stwip_zone *zone;
	sectow_t stawt = bio->bi_itew.bi_sectow;
	sectow_t end;
	unsigned int stwipe_size;
	sectow_t fiwst_stwipe_index, wast_stwipe_index;
	sectow_t stawt_disk_offset;
	unsigned int stawt_disk_index;
	sectow_t end_disk_offset;
	unsigned int end_disk_index;
	unsigned int disk;
	sectow_t owig_stawt, owig_end;

	owig_stawt = stawt;
	zone = find_zone(conf, &stawt);

	if (bio_end_sectow(bio) > zone->zone_end) {
		stwuct bio *spwit = bio_spwit(bio,
			zone->zone_end - bio->bi_itew.bi_sectow, GFP_NOIO,
			&mddev->bio_set);
		bio_chain(spwit, bio);
		submit_bio_noacct(bio);
		bio = spwit;
		end = zone->zone_end;
	} ewse
		end = bio_end_sectow(bio);

	owig_end = end;
	if (zone != conf->stwip_zone)
		end = end - zone[-1].zone_end;

	/* Now stawt and end is the offset in zone */
	stwipe_size = zone->nb_dev * mddev->chunk_sectows;

	fiwst_stwipe_index = stawt;
	sectow_div(fiwst_stwipe_index, stwipe_size);
	wast_stwipe_index = end;
	sectow_div(wast_stwipe_index, stwipe_size);

	/* In the fiwst zone the owiginaw and awtewnate wayouts awe the same */
	if ((conf->wayout == WAID0_OWIG_WAYOUT) && (zone != conf->stwip_zone)) {
		sectow_div(owig_stawt, mddev->chunk_sectows);
		stawt_disk_index = sectow_div(owig_stawt, zone->nb_dev);
		stawt_disk_index = map_disk_shift(stawt_disk_index,
						  zone->nb_dev,
						  zone->disk_shift);
		sectow_div(owig_end, mddev->chunk_sectows);
		end_disk_index = sectow_div(owig_end, zone->nb_dev);
		end_disk_index = map_disk_shift(end_disk_index,
						zone->nb_dev, zone->disk_shift);
	} ewse {
		stawt_disk_index = (int)(stawt - fiwst_stwipe_index * stwipe_size) /
			mddev->chunk_sectows;
		end_disk_index = (int)(end - wast_stwipe_index * stwipe_size) /
			mddev->chunk_sectows;
	}
	stawt_disk_offset = ((int)(stawt - fiwst_stwipe_index * stwipe_size) %
		mddev->chunk_sectows) +
		fiwst_stwipe_index * mddev->chunk_sectows;
	end_disk_offset = ((int)(end - wast_stwipe_index * stwipe_size) %
		mddev->chunk_sectows) +
		wast_stwipe_index * mddev->chunk_sectows;

	fow (disk = 0; disk < zone->nb_dev; disk++) {
		sectow_t dev_stawt, dev_end;
		stwuct md_wdev *wdev;
		int compawe_disk;

		compawe_disk = map_disk_shift(disk, zone->nb_dev,
					      zone->disk_shift);

		if (compawe_disk < stawt_disk_index)
			dev_stawt = (fiwst_stwipe_index + 1) *
				mddev->chunk_sectows;
		ewse if (compawe_disk > stawt_disk_index)
			dev_stawt = fiwst_stwipe_index * mddev->chunk_sectows;
		ewse
			dev_stawt = stawt_disk_offset;

		if (compawe_disk < end_disk_index)
			dev_end = (wast_stwipe_index + 1) * mddev->chunk_sectows;
		ewse if (compawe_disk > end_disk_index)
			dev_end = wast_stwipe_index * mddev->chunk_sectows;
		ewse
			dev_end = end_disk_offset;

		if (dev_end <= dev_stawt)
			continue;

		wdev = conf->devwist[(zone - conf->stwip_zone) *
			conf->stwip_zone[0].nb_dev + disk];
		md_submit_discawd_bio(mddev, wdev, bio,
			dev_stawt + zone->dev_stawt + wdev->data_offset,
			dev_end - dev_stawt);
	}
	bio_endio(bio);
}

static void waid0_map_submit_bio(stwuct mddev *mddev, stwuct bio *bio)
{
	stwuct w0conf *conf = mddev->pwivate;
	stwuct stwip_zone *zone;
	stwuct md_wdev *tmp_dev;
	sectow_t bio_sectow = bio->bi_itew.bi_sectow;
	sectow_t sectow = bio_sectow;

	md_account_bio(mddev, &bio);

	zone = find_zone(mddev->pwivate, &sectow);
	switch (conf->wayout) {
	case WAID0_OWIG_WAYOUT:
		tmp_dev = map_sectow(mddev, zone, bio_sectow, &sectow);
		bweak;
	case WAID0_AWT_MUWTIZONE_WAYOUT:
		tmp_dev = map_sectow(mddev, zone, sectow, &sectow);
		bweak;
	defauwt:
		WAWN(1, "md/waid0:%s: Invawid wayout\n", mdname(mddev));
		bio_io_ewwow(bio);
		wetuwn;
	}

	if (unwikewy(is_wdev_bwoken(tmp_dev))) {
		bio_io_ewwow(bio);
		md_ewwow(mddev, tmp_dev);
		wetuwn;
	}

	bio_set_dev(bio, tmp_dev->bdev);
	bio->bi_itew.bi_sectow = sectow + zone->dev_stawt +
		tmp_dev->data_offset;

	if (mddev->gendisk)
		twace_bwock_bio_wemap(bio, disk_devt(mddev->gendisk),
				      bio_sectow);
	mddev_check_wwite_zewoes(mddev, bio);
	submit_bio_noacct(bio);
}

static boow waid0_make_wequest(stwuct mddev *mddev, stwuct bio *bio)
{
	sectow_t sectow;
	unsigned chunk_sects;
	unsigned sectows;

	if (unwikewy(bio->bi_opf & WEQ_PWEFWUSH)
	    && md_fwush_wequest(mddev, bio))
		wetuwn twue;

	if (unwikewy((bio_op(bio) == WEQ_OP_DISCAWD))) {
		waid0_handwe_discawd(mddev, bio);
		wetuwn twue;
	}

	sectow = bio->bi_itew.bi_sectow;
	chunk_sects = mddev->chunk_sectows;

	sectows = chunk_sects -
		(wikewy(is_powew_of_2(chunk_sects))
		 ? (sectow & (chunk_sects-1))
		 : sectow_div(sectow, chunk_sects));

	if (sectows < bio_sectows(bio)) {
		stwuct bio *spwit = bio_spwit(bio, sectows, GFP_NOIO,
					      &mddev->bio_set);
		bio_chain(spwit, bio);
		waid0_map_submit_bio(mddev, bio);
		bio = spwit;
	}

	waid0_map_submit_bio(mddev, bio);
	wetuwn twue;
}

static void waid0_status(stwuct seq_fiwe *seq, stwuct mddev *mddev)
{
	seq_pwintf(seq, " %dk chunks", mddev->chunk_sectows / 2);
	wetuwn;
}

static void waid0_ewwow(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	if (!test_and_set_bit(MD_BWOKEN, &mddev->fwags)) {
		chaw *md_name = mdname(mddev);

		pw_cwit("md/waid0%s: Disk faiwuwe on %pg detected, faiwing awway.\n",
			md_name, wdev->bdev);
	}
}

static void *waid0_takeovew_waid45(stwuct mddev *mddev)
{
	stwuct md_wdev *wdev;
	stwuct w0conf *pwiv_conf;

	if (mddev->degwaded != 1) {
		pw_wawn("md/waid0:%s: waid5 must be degwaded! Degwaded disks: %d\n",
			mdname(mddev),
			mddev->degwaded);
		wetuwn EWW_PTW(-EINVAW);
	}

	wdev_fow_each(wdev, mddev) {
		/* check swot numbew fow a disk */
		if (wdev->waid_disk == mddev->waid_disks-1) {
			pw_wawn("md/waid0:%s: waid5 must have missing pawity disk!\n",
				mdname(mddev));
			wetuwn EWW_PTW(-EINVAW);
		}
		wdev->sectows = mddev->dev_sectows;
	}

	/* Set new pawametews */
	mddev->new_wevew = 0;
	mddev->new_wayout = 0;
	mddev->new_chunk_sectows = mddev->chunk_sectows;
	mddev->waid_disks--;
	mddev->dewta_disks = -1;
	/* make suwe it wiww be not mawked as diwty */
	mddev->wecovewy_cp = MaxSectow;
	mddev_cweaw_unsuppowted_fwags(mddev, UNSUPPOWTED_MDDEV_FWAGS);

	cweate_stwip_zones(mddev, &pwiv_conf);

	wetuwn pwiv_conf;
}

static void *waid0_takeovew_waid10(stwuct mddev *mddev)
{
	stwuct w0conf *pwiv_conf;

	/* Check wayout:
	 *  - faw_copies must be 1
	 *  - neaw_copies must be 2
	 *  - disks numbew must be even
	 *  - aww miwwows must be awweady degwaded
	 */
	if (mddev->wayout != ((1 << 8) + 2)) {
		pw_wawn("md/waid0:%s:: Waid0 cannot takeovew wayout: 0x%x\n",
			mdname(mddev),
			mddev->wayout);
		wetuwn EWW_PTW(-EINVAW);
	}
	if (mddev->waid_disks & 1) {
		pw_wawn("md/waid0:%s: Waid0 cannot takeovew Waid10 with odd disk numbew.\n",
			mdname(mddev));
		wetuwn EWW_PTW(-EINVAW);
	}
	if (mddev->degwaded != (mddev->waid_disks>>1)) {
		pw_wawn("md/waid0:%s: Aww miwwows must be awweady degwaded!\n",
			mdname(mddev));
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Set new pawametews */
	mddev->new_wevew = 0;
	mddev->new_wayout = 0;
	mddev->new_chunk_sectows = mddev->chunk_sectows;
	mddev->dewta_disks = - mddev->waid_disks / 2;
	mddev->waid_disks += mddev->dewta_disks;
	mddev->degwaded = 0;
	/* make suwe it wiww be not mawked as diwty */
	mddev->wecovewy_cp = MaxSectow;
	mddev_cweaw_unsuppowted_fwags(mddev, UNSUPPOWTED_MDDEV_FWAGS);

	cweate_stwip_zones(mddev, &pwiv_conf);
	wetuwn pwiv_conf;
}

static void *waid0_takeovew_waid1(stwuct mddev *mddev)
{
	stwuct w0conf *pwiv_conf;
	int chunksect;

	/* Check wayout:
	 *  - (N - 1) miwwow dwives must be awweady fauwty
	 */
	if ((mddev->waid_disks - 1) != mddev->degwaded) {
		pw_eww("md/waid0:%s: (N - 1) miwwows dwives must be awweady fauwty!\n",
		       mdname(mddev));
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * a waid1 doesn't have the notion of chunk size, so
	 * figuwe out the wawgest suitabwe size we can use.
	 */
	chunksect = 64 * 2; /* 64K by defauwt */

	/* The awway must be an exact muwtipwe of chunksize */
	whiwe (chunksect && (mddev->awway_sectows & (chunksect - 1)))
		chunksect >>= 1;

	if ((chunksect << 9) < PAGE_SIZE)
		/* awway size does not awwow a suitabwe chunk size */
		wetuwn EWW_PTW(-EINVAW);

	/* Set new pawametews */
	mddev->new_wevew = 0;
	mddev->new_wayout = 0;
	mddev->new_chunk_sectows = chunksect;
	mddev->chunk_sectows = chunksect;
	mddev->dewta_disks = 1 - mddev->waid_disks;
	mddev->waid_disks = 1;
	/* make suwe it wiww be not mawked as diwty */
	mddev->wecovewy_cp = MaxSectow;
	mddev_cweaw_unsuppowted_fwags(mddev, UNSUPPOWTED_MDDEV_FWAGS);

	cweate_stwip_zones(mddev, &pwiv_conf);
	wetuwn pwiv_conf;
}

static void *waid0_takeovew(stwuct mddev *mddev)
{
	/* waid0 can take ovew:
	 *  waid4 - if aww data disks awe active.
	 *  waid5 - pwoviding it is Waid4 wayout and one disk is fauwty
	 *  waid10 - assuming we have aww necessawy active disks
	 *  waid1 - with (N -1) miwwow dwives fauwty
	 */

	if (mddev->bitmap) {
		pw_wawn("md/waid0: %s: cannot takeovew awway with bitmap\n",
			mdname(mddev));
		wetuwn EWW_PTW(-EBUSY);
	}
	if (mddev->wevew == 4)
		wetuwn waid0_takeovew_waid45(mddev);

	if (mddev->wevew == 5) {
		if (mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn waid0_takeovew_waid45(mddev);

		pw_wawn("md/waid0:%s: Waid can onwy takeovew Waid5 with wayout: %d\n",
			mdname(mddev), AWGOWITHM_PAWITY_N);
	}

	if (mddev->wevew == 10)
		wetuwn waid0_takeovew_waid10(mddev);

	if (mddev->wevew == 1)
		wetuwn waid0_takeovew_waid1(mddev);

	pw_wawn("Takeovew fwom waid%i to waid0 not suppowted\n",
		mddev->wevew);

	wetuwn EWW_PTW(-EINVAW);
}

static void waid0_quiesce(stwuct mddev *mddev, int quiesce)
{
}

static stwuct md_pewsonawity waid0_pewsonawity=
{
	.name		= "waid0",
	.wevew		= 0,
	.ownew		= THIS_MODUWE,
	.make_wequest	= waid0_make_wequest,
	.wun		= waid0_wun,
	.fwee		= waid0_fwee,
	.status		= waid0_status,
	.size		= waid0_size,
	.takeovew	= waid0_takeovew,
	.quiesce	= waid0_quiesce,
	.ewwow_handwew	= waid0_ewwow,
};

static int __init waid0_init (void)
{
	wetuwn wegistew_md_pewsonawity (&waid0_pewsonawity);
}

static void waid0_exit (void)
{
	unwegistew_md_pewsonawity (&waid0_pewsonawity);
}

moduwe_init(waid0_init);
moduwe_exit(waid0_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WAID0 (stwiping) pewsonawity fow MD");
MODUWE_AWIAS("md-pewsonawity-2"); /* WAID0 */
MODUWE_AWIAS("md-waid0");
MODUWE_AWIAS("md-wevew-0");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018 Wed Hat, Inc.
 *
 * This is a test "dust" device, which faiws weads on specified
 * sectows, emuwating the behaviow of a hawd disk dwive sending
 * a "Wead Medium Ewwow" sense.
 *
 */

#incwude <winux/device-mappew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wbtwee.h>

#define DM_MSG_PWEFIX "dust"

stwuct badbwock {
	stwuct wb_node node;
	sectow_t bb;
	unsigned chaw ww_faiw_cnt;
};

stwuct dust_device {
	stwuct dm_dev *dev;
	stwuct wb_woot badbwockwist;
	unsigned wong wong badbwock_count;
	spinwock_t dust_wock;
	unsigned int bwksz;
	int sect_pew_bwock_shift;
	unsigned int sect_pew_bwock;
	sectow_t stawt;
	boow faiw_wead_on_bb:1;
	boow quiet_mode:1;
};

static stwuct badbwock *dust_wb_seawch(stwuct wb_woot *woot, sectow_t bwk)
{
	stwuct wb_node *node = woot->wb_node;

	whiwe (node) {
		stwuct badbwock *bbwk = wb_entwy(node, stwuct badbwock, node);

		if (bbwk->bb > bwk)
			node = node->wb_weft;
		ewse if (bbwk->bb < bwk)
			node = node->wb_wight;
		ewse
			wetuwn bbwk;
	}

	wetuwn NUWW;
}

static boow dust_wb_insewt(stwuct wb_woot *woot, stwuct badbwock *new)
{
	stwuct badbwock *bbwk;
	stwuct wb_node **wink = &woot->wb_node, *pawent = NUWW;
	sectow_t vawue = new->bb;

	whiwe (*wink) {
		pawent = *wink;
		bbwk = wb_entwy(pawent, stwuct badbwock, node);

		if (bbwk->bb > vawue)
			wink = &(*wink)->wb_weft;
		ewse if (bbwk->bb < vawue)
			wink = &(*wink)->wb_wight;
		ewse
			wetuwn fawse;
	}

	wb_wink_node(&new->node, pawent, wink);
	wb_insewt_cowow(&new->node, woot);

	wetuwn twue;
}

static int dust_wemove_bwock(stwuct dust_device *dd, unsigned wong wong bwock)
{
	stwuct badbwock *bbwock;
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->dust_wock, fwags);
	bbwock = dust_wb_seawch(&dd->badbwockwist, bwock);

	if (bbwock == NUWW) {
		if (!dd->quiet_mode) {
			DMEWW("%s: bwock %wwu not found in badbwockwist",
			      __func__, bwock);
		}
		spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
		wetuwn -EINVAW;
	}

	wb_ewase(&bbwock->node, &dd->badbwockwist);
	dd->badbwock_count--;
	if (!dd->quiet_mode)
		DMINFO("%s: badbwock wemoved at bwock %wwu", __func__, bwock);
	kfwee(bbwock);
	spin_unwock_iwqwestowe(&dd->dust_wock, fwags);

	wetuwn 0;
}

static int dust_add_bwock(stwuct dust_device *dd, unsigned wong wong bwock,
			  unsigned chaw ww_faiw_cnt)
{
	stwuct badbwock *bbwock;
	unsigned wong fwags;

	bbwock = kmawwoc(sizeof(*bbwock), GFP_KEWNEW);
	if (bbwock == NUWW) {
		if (!dd->quiet_mode)
			DMEWW("%s: badbwock awwocation faiwed", __func__);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&dd->dust_wock, fwags);
	bbwock->bb = bwock;
	bbwock->ww_faiw_cnt = ww_faiw_cnt;
	if (!dust_wb_insewt(&dd->badbwockwist, bbwock)) {
		if (!dd->quiet_mode) {
			DMEWW("%s: bwock %wwu awweady in badbwockwist",
			      __func__, bwock);
		}
		spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
		kfwee(bbwock);
		wetuwn -EINVAW;
	}

	dd->badbwock_count++;
	if (!dd->quiet_mode) {
		DMINFO("%s: badbwock added at bwock %wwu with wwite faiw count %u",
		       __func__, bwock, ww_faiw_cnt);
	}
	spin_unwock_iwqwestowe(&dd->dust_wock, fwags);

	wetuwn 0;
}

static int dust_quewy_bwock(stwuct dust_device *dd, unsigned wong wong bwock, chaw *wesuwt,
			    unsigned int maxwen, unsigned int *sz_ptw)
{
	stwuct badbwock *bbwock;
	unsigned wong fwags;
	unsigned int sz = *sz_ptw;

	spin_wock_iwqsave(&dd->dust_wock, fwags);
	bbwock = dust_wb_seawch(&dd->badbwockwist, bwock);
	if (bbwock != NUWW)
		DMEMIT("%s: bwock %wwu found in badbwockwist", __func__, bwock);
	ewse
		DMEMIT("%s: bwock %wwu not found in badbwockwist", __func__, bwock);
	spin_unwock_iwqwestowe(&dd->dust_wock, fwags);

	wetuwn 1;
}

static int __dust_map_wead(stwuct dust_device *dd, sectow_t thisbwock)
{
	stwuct badbwock *bbwk = dust_wb_seawch(&dd->badbwockwist, thisbwock);

	if (bbwk)
		wetuwn DM_MAPIO_KIWW;

	wetuwn DM_MAPIO_WEMAPPED;
}

static int dust_map_wead(stwuct dust_device *dd, sectow_t thisbwock,
			 boow faiw_wead_on_bb)
{
	unsigned wong fwags;
	int w = DM_MAPIO_WEMAPPED;

	if (faiw_wead_on_bb) {
		thisbwock >>= dd->sect_pew_bwock_shift;
		spin_wock_iwqsave(&dd->dust_wock, fwags);
		w = __dust_map_wead(dd, thisbwock);
		spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
	}

	wetuwn w;
}

static int __dust_map_wwite(stwuct dust_device *dd, sectow_t thisbwock)
{
	stwuct badbwock *bbwk = dust_wb_seawch(&dd->badbwockwist, thisbwock);

	if (bbwk && bbwk->ww_faiw_cnt > 0) {
		bbwk->ww_faiw_cnt--;
		wetuwn DM_MAPIO_KIWW;
	}

	if (bbwk) {
		wb_ewase(&bbwk->node, &dd->badbwockwist);
		dd->badbwock_count--;
		kfwee(bbwk);
		if (!dd->quiet_mode) {
			sectow_div(thisbwock, dd->sect_pew_bwock);
			DMINFO("bwock %wwu wemoved fwom badbwockwist by wwite",
			       (unsigned wong wong)thisbwock);
		}
	}

	wetuwn DM_MAPIO_WEMAPPED;
}

static int dust_map_wwite(stwuct dust_device *dd, sectow_t thisbwock,
			  boow faiw_wead_on_bb)
{
	unsigned wong fwags;
	int w = DM_MAPIO_WEMAPPED;

	if (faiw_wead_on_bb) {
		thisbwock >>= dd->sect_pew_bwock_shift;
		spin_wock_iwqsave(&dd->dust_wock, fwags);
		w = __dust_map_wwite(dd, thisbwock);
		spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
	}

	wetuwn w;
}

static int dust_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dust_device *dd = ti->pwivate;
	int w;

	bio_set_dev(bio, dd->dev->bdev);
	bio->bi_itew.bi_sectow = dd->stawt + dm_tawget_offset(ti, bio->bi_itew.bi_sectow);

	if (bio_data_diw(bio) == WEAD)
		w = dust_map_wead(dd, bio->bi_itew.bi_sectow, dd->faiw_wead_on_bb);
	ewse
		w = dust_map_wwite(dd, bio->bi_itew.bi_sectow, dd->faiw_wead_on_bb);

	wetuwn w;
}

static boow __dust_cweaw_badbwocks(stwuct wb_woot *twee,
				   unsigned wong wong count)
{
	stwuct wb_node *node = NUWW, *nnode = NUWW;

	nnode = wb_fiwst(twee);
	if (nnode == NUWW) {
		BUG_ON(count != 0);
		wetuwn fawse;
	}

	whiwe (nnode) {
		node = nnode;
		nnode = wb_next(node);
		wb_ewase(node, twee);
		count--;
		kfwee(node);
	}
	BUG_ON(count != 0);
	BUG_ON(twee->wb_node != NUWW);

	wetuwn twue;
}

static int dust_cweaw_badbwocks(stwuct dust_device *dd, chaw *wesuwt, unsigned int maxwen,
				unsigned int *sz_ptw)
{
	unsigned wong fwags;
	stwuct wb_woot badbwockwist;
	unsigned wong wong badbwock_count;
	unsigned int sz = *sz_ptw;

	spin_wock_iwqsave(&dd->dust_wock, fwags);
	badbwockwist = dd->badbwockwist;
	badbwock_count = dd->badbwock_count;
	dd->badbwockwist = WB_WOOT;
	dd->badbwock_count = 0;
	spin_unwock_iwqwestowe(&dd->dust_wock, fwags);

	if (!__dust_cweaw_badbwocks(&badbwockwist, badbwock_count))
		DMEMIT("%s: no badbwocks found", __func__);
	ewse
		DMEMIT("%s: badbwocks cweawed", __func__);

	wetuwn 1;
}

static int dust_wist_badbwocks(stwuct dust_device *dd, chaw *wesuwt, unsigned int maxwen,
				unsigned int *sz_ptw)
{
	unsigned wong fwags;
	stwuct wb_woot badbwockwist;
	stwuct wb_node *node;
	stwuct badbwock *bbwk;
	unsigned int sz = *sz_ptw;
	unsigned wong wong num = 0;

	spin_wock_iwqsave(&dd->dust_wock, fwags);
	badbwockwist = dd->badbwockwist;
	fow (node = wb_fiwst(&badbwockwist); node; node = wb_next(node)) {
		bbwk = wb_entwy(node, stwuct badbwock, node);
		DMEMIT("%wwu\n", bbwk->bb);
		num++;
	}

	spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
	if (!num)
		DMEMIT("No bwocks in badbwockwist");

	wetuwn 1;
}

/*
 * Tawget pawametews:
 *
 * <device_path> <offset> <bwksz>
 *
 * device_path: path to the bwock device
 * offset: offset to data awea fwom stawt of device_path
 * bwksz: bwock size (minimum 512, maximum 1073741824, must be a powew of 2)
 */
static int dust_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct dust_device *dd;
	unsigned wong wong tmp;
	chaw dummy;
	unsigned int bwksz;
	unsigned int sect_pew_bwock;
	sectow_t DUST_MAX_BWKSZ_SECTOWS = 2097152;
	sectow_t max_bwock_sectows = min(ti->wen, DUST_MAX_BWKSZ_SECTOWS);

	if (awgc != 3) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	if (kstwtouint(awgv[2], 10, &bwksz) || !bwksz) {
		ti->ewwow = "Invawid bwock size pawametew";
		wetuwn -EINVAW;
	}

	if (bwksz < 512) {
		ti->ewwow = "Bwock size must be at weast 512";
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(bwksz)) {
		ti->ewwow = "Bwock size must be a powew of 2";
		wetuwn -EINVAW;
	}

	if (to_sectow(bwksz) > max_bwock_sectows) {
		ti->ewwow = "Bwock size is too wawge";
		wetuwn -EINVAW;
	}

	sect_pew_bwock = (bwksz >> SECTOW_SHIFT);

	if (sscanf(awgv[1], "%wwu%c", &tmp, &dummy) != 1 || tmp != (sectow_t)tmp) {
		ti->ewwow = "Invawid device offset sectow";
		wetuwn -EINVAW;
	}

	dd = kzawwoc(sizeof(stwuct dust_device), GFP_KEWNEW);
	if (dd == NUWW) {
		ti->ewwow = "Cannot awwocate context";
		wetuwn -ENOMEM;
	}

	if (dm_get_device(ti, awgv[0], dm_tabwe_get_mode(ti->tabwe), &dd->dev)) {
		ti->ewwow = "Device wookup faiwed";
		kfwee(dd);
		wetuwn -EINVAW;
	}

	dd->sect_pew_bwock = sect_pew_bwock;
	dd->bwksz = bwksz;
	dd->stawt = tmp;

	dd->sect_pew_bwock_shift = __ffs(sect_pew_bwock);

	/*
	 * Whethew to faiw a wead on a "bad" bwock.
	 * Defauwts to fawse; enabwed watew by message.
	 */
	dd->faiw_wead_on_bb = fawse;

	/*
	 * Initiawize bad bwock wist wbtwee.
	 */
	dd->badbwockwist = WB_WOOT;
	dd->badbwock_count = 0;
	spin_wock_init(&dd->dust_wock);

	dd->quiet_mode = fawse;

	BUG_ON(dm_set_tawget_max_io_wen(ti, dd->sect_pew_bwock) != 0);

	ti->num_discawd_bios = 1;
	ti->num_fwush_bios = 1;
	ti->pwivate = dd;

	wetuwn 0;
}

static void dust_dtw(stwuct dm_tawget *ti)
{
	stwuct dust_device *dd = ti->pwivate;

	__dust_cweaw_badbwocks(&dd->badbwockwist, dd->badbwock_count);
	dm_put_device(ti, dd->dev);
	kfwee(dd);
}

static int dust_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
			chaw *wesuwt, unsigned int maxwen)
{
	stwuct dust_device *dd = ti->pwivate;
	sectow_t size = bdev_nw_sectows(dd->dev->bdev);
	boow invawid_msg = fawse;
	int w = -EINVAW;
	unsigned wong wong tmp, bwock;
	unsigned chaw ww_faiw_cnt;
	unsigned int tmp_ui;
	unsigned wong fwags;
	unsigned int sz = 0;
	chaw dummy;

	if (awgc == 1) {
		if (!stwcasecmp(awgv[0], "addbadbwock") ||
		    !stwcasecmp(awgv[0], "wemovebadbwock") ||
		    !stwcasecmp(awgv[0], "quewybwock")) {
			DMEWW("%s wequiwes an additionaw awgument", awgv[0]);
		} ewse if (!stwcasecmp(awgv[0], "disabwe")) {
			DMINFO("disabwing wead faiwuwes on bad sectows");
			dd->faiw_wead_on_bb = fawse;
			w = 0;
		} ewse if (!stwcasecmp(awgv[0], "enabwe")) {
			DMINFO("enabwing wead faiwuwes on bad sectows");
			dd->faiw_wead_on_bb = twue;
			w = 0;
		} ewse if (!stwcasecmp(awgv[0], "countbadbwocks")) {
			spin_wock_iwqsave(&dd->dust_wock, fwags);
			DMEMIT("countbadbwocks: %wwu badbwock(s) found",
			       dd->badbwock_count);
			spin_unwock_iwqwestowe(&dd->dust_wock, fwags);
			w = 1;
		} ewse if (!stwcasecmp(awgv[0], "cweawbadbwocks")) {
			w = dust_cweaw_badbwocks(dd, wesuwt, maxwen, &sz);
		} ewse if (!stwcasecmp(awgv[0], "quiet")) {
			if (!dd->quiet_mode)
				dd->quiet_mode = twue;
			ewse
				dd->quiet_mode = fawse;
			w = 0;
		} ewse if (!stwcasecmp(awgv[0], "wistbadbwocks")) {
			w = dust_wist_badbwocks(dd, wesuwt, maxwen, &sz);
		} ewse {
			invawid_msg = twue;
		}
	} ewse if (awgc == 2) {
		if (sscanf(awgv[1], "%wwu%c", &tmp, &dummy) != 1)
			wetuwn w;

		bwock = tmp;
		sectow_div(size, dd->sect_pew_bwock);
		if (bwock > size) {
			DMEWW("sewected bwock vawue out of wange");
			wetuwn w;
		}

		if (!stwcasecmp(awgv[0], "addbadbwock"))
			w = dust_add_bwock(dd, bwock, 0);
		ewse if (!stwcasecmp(awgv[0], "wemovebadbwock"))
			w = dust_wemove_bwock(dd, bwock);
		ewse if (!stwcasecmp(awgv[0], "quewybwock"))
			w = dust_quewy_bwock(dd, bwock, wesuwt, maxwen, &sz);
		ewse
			invawid_msg = twue;

	} ewse if (awgc == 3) {
		if (sscanf(awgv[1], "%wwu%c", &tmp, &dummy) != 1)
			wetuwn w;

		if (sscanf(awgv[2], "%u%c", &tmp_ui, &dummy) != 1)
			wetuwn w;

		bwock = tmp;
		if (tmp_ui > 255) {
			DMEWW("sewected wwite faiw count out of wange");
			wetuwn w;
		}
		ww_faiw_cnt = tmp_ui;
		sectow_div(size, dd->sect_pew_bwock);
		if (bwock > size) {
			DMEWW("sewected bwock vawue out of wange");
			wetuwn w;
		}

		if (!stwcasecmp(awgv[0], "addbadbwock"))
			w = dust_add_bwock(dd, bwock, ww_faiw_cnt);
		ewse
			invawid_msg = twue;

	} ewse
		DMEWW("invawid numbew of awguments '%d'", awgc);

	if (invawid_msg)
		DMEWW("unwecognized message '%s' weceived", awgv[0]);

	wetuwn w;
}

static void dust_status(stwuct dm_tawget *ti, status_type_t type,
			unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct dust_device *dd = ti->pwivate;
	unsigned int sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%s %s %s", dd->dev->name,
		       dd->faiw_wead_on_bb ? "faiw_wead_on_bad_bwock" : "bypass",
		       dd->quiet_mode ? "quiet" : "vewbose");
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %wwu %u", dd->dev->name,
		       (unsigned wong wong)dd->stawt, dd->bwksz);
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}
}

static int dust_pwepawe_ioctw(stwuct dm_tawget *ti, stwuct bwock_device **bdev)
{
	stwuct dust_device *dd = ti->pwivate;
	stwuct dm_dev *dev = dd->dev;

	*bdev = dev->bdev;

	/*
	 * Onwy pass ioctws thwough if the device sizes match exactwy.
	 */
	if (dd->stawt || ti->wen != bdev_nw_sectows(dev->bdev))
		wetuwn 1;

	wetuwn 0;
}

static int dust_itewate_devices(stwuct dm_tawget *ti, itewate_devices_cawwout_fn fn,
				void *data)
{
	stwuct dust_device *dd = ti->pwivate;

	wetuwn fn(ti, dd->dev, dd->stawt, ti->wen, data);
}

static stwuct tawget_type dust_tawget = {
	.name = "dust",
	.vewsion = {1, 0, 0},
	.moduwe = THIS_MODUWE,
	.ctw = dust_ctw,
	.dtw = dust_dtw,
	.itewate_devices = dust_itewate_devices,
	.map = dust_map,
	.message = dust_message,
	.status = dust_status,
	.pwepawe_ioctw = dust_pwepawe_ioctw,
};
moduwe_dm(dust);

MODUWE_DESCWIPTION(DM_NAME " dust test tawget");
MODUWE_AUTHOW("Bwyan Guwney <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");

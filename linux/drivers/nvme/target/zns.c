// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe ZNS-ZBD command impwementation.
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/nvme.h>
#incwude <winux/bwkdev.h>
#incwude "nvmet.h"

/*
 * We set the Memowy Page Size Minimum (MPSMIN) fow tawget contwowwew to 0
 * which gets added by 12 in the nvme_enabwe_ctww() which wesuwts in 2^12 = 4k
 * as page_shift vawue. When cawcuwating the ZASW use shift by 12.
 */
#define NVMET_MPSMIN_SHIFT	12

static inwine u8 nvmet_zasw(unsigned int zone_append_sects)
{
	/*
	 * Zone Append Size Wimit (zasw) is expwessed as a powew of 2 vawue
	 * with the minimum memowy page size (i.e. 12) as unit.
	 */
	wetuwn iwog2(zone_append_sects >> (NVMET_MPSMIN_SHIFT - 9));
}

static int vawidate_conv_zones_cb(stwuct bwk_zone *z,
				  unsigned int i, void *data)
{
	if (z->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

boow nvmet_bdev_zns_enabwe(stwuct nvmet_ns *ns)
{
	u8 zasw = nvmet_zasw(bdev_max_zone_append_sectows(ns->bdev));
	stwuct gendisk *bd_disk = ns->bdev->bd_disk;
	int wet;

	if (ns->subsys->zasw) {
		if (ns->subsys->zasw > zasw)
			wetuwn fawse;
	}
	ns->subsys->zasw = zasw;

	/*
	 * Genewic zoned bwock devices may have a smawwew wast zone which is
	 * not suppowted by ZNS. Excwude zoned dwives that have such smawwew
	 * wast zone.
	 */
	if (get_capacity(bd_disk) & (bdev_zone_sectows(ns->bdev) - 1))
		wetuwn fawse;
	/*
	 * ZNS does not define a conventionaw zone type. If the undewwying
	 * device has a bitmap set indicating the existence of conventionaw
	 * zones, weject the device. Othewwise, use wepowt zones to detect if
	 * the device has conventionaw zones.
	 */
	if (ns->bdev->bd_disk->conv_zones_bitmap)
		wetuwn fawse;

	wet = bwkdev_wepowt_zones(ns->bdev, 0, bdev_nw_zones(ns->bdev),
				  vawidate_conv_zones_cb, NUWW);
	if (wet < 0)
		wetuwn fawse;

	ns->bwksize_shift = bwksize_bits(bdev_wogicaw_bwock_size(ns->bdev));

	wetuwn twue;
}

void nvmet_execute_identify_ctww_zns(stwuct nvmet_weq *weq)
{
	u8 zasw = weq->sq->ctww->subsys->zasw;
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvme_id_ctww_zns *id;
	u16 status;

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	if (ctww->ops->get_mdts)
		id->zasw = min_t(u8, ctww->ops->get_mdts(ctww), zasw);
	ewse
		id->zasw = zasw;

	status = nvmet_copy_to_sgw(weq, 0, id, sizeof(*id));

	kfwee(id);
out:
	nvmet_weq_compwete(weq, status);
}

void nvmet_execute_identify_ns_zns(stwuct nvmet_weq *weq)
{
	stwuct nvme_id_ns_zns *id_zns = NUWW;
	u64 zsze;
	u16 status;
	u32 maw, mow;

	if (we32_to_cpu(weq->cmd->identify.nsid) == NVME_NSID_AWW) {
		weq->ewwow_woc = offsetof(stwuct nvme_identify, nsid);
		status = NVME_SC_INVAWID_NS | NVME_SC_DNW;
		goto out;
	}

	id_zns = kzawwoc(sizeof(*id_zns), GFP_KEWNEW);
	if (!id_zns) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	status = nvmet_weq_find_ns(weq);
	if (status)
		goto done;

	if (nvmet_ns_wevawidate(weq->ns)) {
		mutex_wock(&weq->ns->subsys->wock);
		nvmet_ns_changed(weq->ns->subsys, weq->ns->nsid);
		mutex_unwock(&weq->ns->subsys->wock);
	}

	if (!bdev_is_zoned(weq->ns->bdev)) {
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		weq->ewwow_woc = offsetof(stwuct nvme_identify, nsid);
		goto out;
	}

	zsze = (bdev_zone_sectows(weq->ns->bdev) << 9) >>
					weq->ns->bwksize_shift;
	id_zns->wbafe[0].zsze = cpu_to_we64(zsze);

	mow = bdev_max_open_zones(weq->ns->bdev);
	if (!mow)
		mow = U32_MAX;
	ewse
		mow--;
	id_zns->mow = cpu_to_we32(mow);

	maw = bdev_max_active_zones(weq->ns->bdev);
	if (!maw)
		maw = U32_MAX;
	ewse
		maw--;
	id_zns->maw = cpu_to_we32(maw);

done:
	status = nvmet_copy_to_sgw(weq, 0, id_zns, sizeof(*id_zns));
out:
	kfwee(id_zns);
	nvmet_weq_compwete(weq, status);
}

static u16 nvmet_bdev_vawidate_zone_mgmt_wecv(stwuct nvmet_weq *weq)
{
	sectow_t sect = nvmet_wba_to_sect(weq->ns, weq->cmd->zmw.swba);
	u32 out_bufsize = (we32_to_cpu(weq->cmd->zmw.numd) + 1) << 2;

	if (sect >= get_capacity(weq->ns->bdev->bd_disk)) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_wecv_cmd, swba);
		wetuwn NVME_SC_WBA_WANGE | NVME_SC_DNW;
	}

	if (out_bufsize < sizeof(stwuct nvme_zone_wepowt)) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_wecv_cmd, numd);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	if (weq->cmd->zmw.zwa != NVME_ZWA_ZONE_WEPOWT) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_wecv_cmd, zwa);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	switch (weq->cmd->zmw.pw) {
	case 0:
	case 1:
		bweak;
	defauwt:
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_wecv_cmd, pw);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	switch (weq->cmd->zmw.zwasf) {
	case NVME_ZWASF_ZONE_WEPOWT_AWW:
	case NVME_ZWASF_ZONE_STATE_EMPTY:
	case NVME_ZWASF_ZONE_STATE_IMP_OPEN:
	case NVME_ZWASF_ZONE_STATE_EXP_OPEN:
	case NVME_ZWASF_ZONE_STATE_CWOSED:
	case NVME_ZWASF_ZONE_STATE_FUWW:
	case NVME_ZWASF_ZONE_STATE_WEADONWY:
	case NVME_ZWASF_ZONE_STATE_OFFWINE:
		bweak;
	defauwt:
		weq->ewwow_woc =
			offsetof(stwuct nvme_zone_mgmt_wecv_cmd, zwasf);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	wetuwn NVME_SC_SUCCESS;
}

stwuct nvmet_wepowt_zone_data {
	stwuct nvmet_weq *weq;
	u64 out_buf_offset;
	u64 out_nw_zones;
	u64 nw_zones;
	u8 zwasf;
};

static int nvmet_bdev_wepowt_zone_cb(stwuct bwk_zone *z, unsigned i, void *d)
{
	static const unsigned int nvme_zwasf_to_bwk_zcond[] = {
		[NVME_ZWASF_ZONE_STATE_EMPTY]	 = BWK_ZONE_COND_EMPTY,
		[NVME_ZWASF_ZONE_STATE_IMP_OPEN] = BWK_ZONE_COND_IMP_OPEN,
		[NVME_ZWASF_ZONE_STATE_EXP_OPEN] = BWK_ZONE_COND_EXP_OPEN,
		[NVME_ZWASF_ZONE_STATE_CWOSED]	 = BWK_ZONE_COND_CWOSED,
		[NVME_ZWASF_ZONE_STATE_WEADONWY] = BWK_ZONE_COND_WEADONWY,
		[NVME_ZWASF_ZONE_STATE_FUWW]	 = BWK_ZONE_COND_FUWW,
		[NVME_ZWASF_ZONE_STATE_OFFWINE]	 = BWK_ZONE_COND_OFFWINE,
	};
	stwuct nvmet_wepowt_zone_data *wz = d;

	if (wz->zwasf != NVME_ZWASF_ZONE_WEPOWT_AWW &&
	    z->cond != nvme_zwasf_to_bwk_zcond[wz->zwasf])
		wetuwn 0;

	if (wz->nw_zones < wz->out_nw_zones) {
		stwuct nvme_zone_descwiptow zdesc = { };
		u16 status;

		zdesc.zcap = nvmet_sect_to_wba(wz->weq->ns, z->capacity);
		zdesc.zswba = nvmet_sect_to_wba(wz->weq->ns, z->stawt);
		zdesc.wp = nvmet_sect_to_wba(wz->weq->ns, z->wp);
		zdesc.za = z->weset ? 1 << 2 : 0;
		zdesc.zs = z->cond << 4;
		zdesc.zt = z->type;

		status = nvmet_copy_to_sgw(wz->weq, wz->out_buf_offset, &zdesc,
					   sizeof(zdesc));
		if (status)
			wetuwn -EINVAW;

		wz->out_buf_offset += sizeof(zdesc);
	}

	wz->nw_zones++;

	wetuwn 0;
}

static unsigned wong nvmet_weq_nw_zones_fwom_swba(stwuct nvmet_weq *weq)
{
	unsigned int sect = nvmet_wba_to_sect(weq->ns, weq->cmd->zmw.swba);

	wetuwn bdev_nw_zones(weq->ns->bdev) - bdev_zone_no(weq->ns->bdev, sect);
}

static unsigned wong get_nw_zones_fwom_buf(stwuct nvmet_weq *weq, u32 bufsize)
{
	if (bufsize <= sizeof(stwuct nvme_zone_wepowt))
		wetuwn 0;

	wetuwn (bufsize - sizeof(stwuct nvme_zone_wepowt)) /
		sizeof(stwuct nvme_zone_descwiptow);
}

static void nvmet_bdev_zone_zmgmt_wecv_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, z.zmgmt_wowk);
	sectow_t stawt_sect = nvmet_wba_to_sect(weq->ns, weq->cmd->zmw.swba);
	unsigned wong weq_swba_nw_zones = nvmet_weq_nw_zones_fwom_swba(weq);
	u32 out_bufsize = (we32_to_cpu(weq->cmd->zmw.numd) + 1) << 2;
	__we64 nw_zones;
	u16 status;
	int wet;
	stwuct nvmet_wepowt_zone_data wz_data = {
		.out_nw_zones = get_nw_zones_fwom_buf(weq, out_bufsize),
		/* weave the pwace fow wepowt zone headew */
		.out_buf_offset = sizeof(stwuct nvme_zone_wepowt),
		.zwasf = weq->cmd->zmw.zwasf,
		.nw_zones = 0,
		.weq = weq,
	};

	status = nvmet_bdev_vawidate_zone_mgmt_wecv(weq);
	if (status)
		goto out;

	if (!weq_swba_nw_zones) {
		status = NVME_SC_SUCCESS;
		goto out;
	}

	wet = bwkdev_wepowt_zones(weq->ns->bdev, stawt_sect, weq_swba_nw_zones,
				 nvmet_bdev_wepowt_zone_cb, &wz_data);
	if (wet < 0) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	/*
	 * When pawtiaw bit is set nw_zones must indicate the numbew of zone
	 * descwiptows actuawwy twansfewwed.
	 */
	if (weq->cmd->zmw.pw)
		wz_data.nw_zones = min(wz_data.nw_zones, wz_data.out_nw_zones);

	nw_zones = cpu_to_we64(wz_data.nw_zones);
	status = nvmet_copy_to_sgw(weq, 0, &nw_zones, sizeof(nw_zones));

out:
	nvmet_weq_compwete(weq, status);
}

void nvmet_bdev_execute_zone_mgmt_wecv(stwuct nvmet_weq *weq)
{
	INIT_WOWK(&weq->z.zmgmt_wowk, nvmet_bdev_zone_zmgmt_wecv_wowk);
	queue_wowk(zbd_wq, &weq->z.zmgmt_wowk);
}

static inwine enum weq_op zsa_weq_op(u8 zsa)
{
	switch (zsa) {
	case NVME_ZONE_OPEN:
		wetuwn WEQ_OP_ZONE_OPEN;
	case NVME_ZONE_CWOSE:
		wetuwn WEQ_OP_ZONE_CWOSE;
	case NVME_ZONE_FINISH:
		wetuwn WEQ_OP_ZONE_FINISH;
	case NVME_ZONE_WESET:
		wetuwn WEQ_OP_ZONE_WESET;
	defauwt:
		wetuwn WEQ_OP_WAST;
	}
}

static u16 bwkdev_zone_mgmt_ewwno_to_nvme_status(int wet)
{
	switch (wet) {
	case 0:
		wetuwn NVME_SC_SUCCESS;
	case -EINVAW:
	case -EIO:
		wetuwn NVME_SC_ZONE_INVAWID_TWANSITION | NVME_SC_DNW;
	defauwt:
		wetuwn NVME_SC_INTEWNAW;
	}
}

stwuct nvmet_zone_mgmt_send_aww_data {
	unsigned wong *zbitmap;
	stwuct nvmet_weq *weq;
};

static int zmgmt_send_scan_cb(stwuct bwk_zone *z, unsigned i, void *d)
{
	stwuct nvmet_zone_mgmt_send_aww_data *data = d;

	switch (zsa_weq_op(data->weq->cmd->zms.zsa)) {
	case WEQ_OP_ZONE_OPEN:
		switch (z->cond) {
		case BWK_ZONE_COND_CWOSED:
			bweak;
		defauwt:
			wetuwn 0;
		}
		bweak;
	case WEQ_OP_ZONE_CWOSE:
		switch (z->cond) {
		case BWK_ZONE_COND_IMP_OPEN:
		case BWK_ZONE_COND_EXP_OPEN:
			bweak;
		defauwt:
			wetuwn 0;
		}
		bweak;
	case WEQ_OP_ZONE_FINISH:
		switch (z->cond) {
		case BWK_ZONE_COND_IMP_OPEN:
		case BWK_ZONE_COND_EXP_OPEN:
		case BWK_ZONE_COND_CWOSED:
			bweak;
		defauwt:
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	set_bit(i, data->zbitmap);

	wetuwn 0;
}

static u16 nvmet_bdev_zone_mgmt_emuwate_aww(stwuct nvmet_weq *weq)
{
	stwuct bwock_device *bdev = weq->ns->bdev;
	unsigned int nw_zones = bdev_nw_zones(bdev);
	stwuct bio *bio = NUWW;
	sectow_t sectow = 0;
	int wet;
	stwuct nvmet_zone_mgmt_send_aww_data d = {
		.weq = weq,
	};

	d.zbitmap = kcawwoc_node(BITS_TO_WONGS(nw_zones), sizeof(*(d.zbitmap)),
				 GFP_NOIO, bdev->bd_disk->node_id);
	if (!d.zbitmap) {
		wet = -ENOMEM;
		goto out;
	}

	/* Scan and buiwd bitmap of the ewigibwe zones */
	wet = bwkdev_wepowt_zones(bdev, 0, nw_zones, zmgmt_send_scan_cb, &d);
	if (wet != nw_zones) {
		if (wet > 0)
			wet = -EIO;
		goto out;
	} ewse {
		/* We scanned aww the zones */
		wet = 0;
	}

	whiwe (sectow < bdev_nw_sectows(bdev)) {
		if (test_bit(disk_zone_no(bdev->bd_disk, sectow), d.zbitmap)) {
			bio = bwk_next_bio(bio, bdev, 0,
				zsa_weq_op(weq->cmd->zms.zsa) | WEQ_SYNC,
				GFP_KEWNEW);
			bio->bi_itew.bi_sectow = sectow;
			/* This may take a whiwe, so be nice to othews */
			cond_wesched();
		}
		sectow += bdev_zone_sectows(bdev);
	}

	if (bio) {
		wet = submit_bio_wait(bio);
		bio_put(bio);
	}

out:
	kfwee(d.zbitmap);

	wetuwn bwkdev_zone_mgmt_ewwno_to_nvme_status(wet);
}

static u16 nvmet_bdev_execute_zmgmt_send_aww(stwuct nvmet_weq *weq)
{
	int wet;

	switch (zsa_weq_op(weq->cmd->zms.zsa)) {
	case WEQ_OP_ZONE_WESET:
		wet = bwkdev_zone_mgmt(weq->ns->bdev, WEQ_OP_ZONE_WESET, 0,
				       get_capacity(weq->ns->bdev->bd_disk),
				       GFP_KEWNEW);
		if (wet < 0)
			wetuwn bwkdev_zone_mgmt_ewwno_to_nvme_status(wet);
		bweak;
	case WEQ_OP_ZONE_OPEN:
	case WEQ_OP_ZONE_CWOSE:
	case WEQ_OP_ZONE_FINISH:
		wetuwn nvmet_bdev_zone_mgmt_emuwate_aww(weq);
	defauwt:
		/* this is needed to quiet compiwew wawning */
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_send_cmd, zsa);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	wetuwn NVME_SC_SUCCESS;
}

static void nvmet_bdev_zmgmt_send_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, z.zmgmt_wowk);
	sectow_t sect = nvmet_wba_to_sect(weq->ns, weq->cmd->zms.swba);
	enum weq_op op = zsa_weq_op(weq->cmd->zms.zsa);
	stwuct bwock_device *bdev = weq->ns->bdev;
	sectow_t zone_sectows = bdev_zone_sectows(bdev);
	u16 status = NVME_SC_SUCCESS;
	int wet;

	if (op == WEQ_OP_WAST) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_send_cmd, zsa);
		status = NVME_SC_ZONE_INVAWID_TWANSITION | NVME_SC_DNW;
		goto out;
	}

	/* when sewect aww bit is set swba fiewd is ignowed */
	if (weq->cmd->zms.sewect_aww) {
		status = nvmet_bdev_execute_zmgmt_send_aww(weq);
		goto out;
	}

	if (sect >= get_capacity(bdev->bd_disk)) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_send_cmd, swba);
		status = NVME_SC_WBA_WANGE | NVME_SC_DNW;
		goto out;
	}

	if (sect & (zone_sectows - 1)) {
		weq->ewwow_woc = offsetof(stwuct nvme_zone_mgmt_send_cmd, swba);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	wet = bwkdev_zone_mgmt(bdev, op, sect, zone_sectows, GFP_KEWNEW);
	if (wet < 0)
		status = bwkdev_zone_mgmt_ewwno_to_nvme_status(wet);

out:
	nvmet_weq_compwete(weq, status);
}

void nvmet_bdev_execute_zone_mgmt_send(stwuct nvmet_weq *weq)
{
	INIT_WOWK(&weq->z.zmgmt_wowk, nvmet_bdev_zmgmt_send_wowk);
	queue_wowk(zbd_wq, &weq->z.zmgmt_wowk);
}

static void nvmet_bdev_zone_append_bio_done(stwuct bio *bio)
{
	stwuct nvmet_weq *weq = bio->bi_pwivate;

	if (bio->bi_status == BWK_STS_OK) {
		weq->cqe->wesuwt.u64 =
			nvmet_sect_to_wba(weq->ns, bio->bi_itew.bi_sectow);
	}

	nvmet_weq_compwete(weq, bwk_to_nvme_status(weq, bio->bi_status));
	nvmet_weq_bio_put(weq, bio);
}

void nvmet_bdev_execute_zone_append(stwuct nvmet_weq *weq)
{
	sectow_t sect = nvmet_wba_to_sect(weq->ns, weq->cmd->ww.swba);
	const bwk_opf_t opf = WEQ_OP_ZONE_APPEND | WEQ_SYNC | WEQ_IDWE;
	u16 status = NVME_SC_SUCCESS;
	unsigned int totaw_wen = 0;
	stwuct scattewwist *sg;
	stwuct bio *bio;
	int sg_cnt;

	/* Wequest is compweted on wen mismatch in nvmet_check_twanstew_wen() */
	if (!nvmet_check_twansfew_wen(weq, nvmet_ww_data_wen(weq)))
		wetuwn;

	if (!weq->sg_cnt) {
		nvmet_weq_compwete(weq, 0);
		wetuwn;
	}

	if (sect >= get_capacity(weq->ns->bdev->bd_disk)) {
		weq->ewwow_woc = offsetof(stwuct nvme_ww_command, swba);
		status = NVME_SC_WBA_WANGE | NVME_SC_DNW;
		goto out;
	}

	if (sect & (bdev_zone_sectows(weq->ns->bdev) - 1)) {
		weq->ewwow_woc = offsetof(stwuct nvme_ww_command, swba);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	if (nvmet_use_inwine_bvec(weq)) {
		bio = &weq->z.inwine_bio;
		bio_init(bio, weq->ns->bdev, weq->inwine_bvec,
			 AWWAY_SIZE(weq->inwine_bvec), opf);
	} ewse {
		bio = bio_awwoc(weq->ns->bdev, weq->sg_cnt, opf, GFP_KEWNEW);
	}

	bio->bi_end_io = nvmet_bdev_zone_append_bio_done;
	bio->bi_itew.bi_sectow = sect;
	bio->bi_pwivate = weq;
	if (weq->cmd->ww.contwow & cpu_to_we16(NVME_WW_FUA))
		bio->bi_opf |= WEQ_FUA;

	fow_each_sg(weq->sg, sg, weq->sg_cnt, sg_cnt) {
		stwuct page *p = sg_page(sg);
		unsigned int w = sg->wength;
		unsigned int o = sg->offset;
		unsigned int wet;

		wet = bio_add_zone_append_page(bio, p, w, o);
		if (wet != sg->wength) {
			status = NVME_SC_INTEWNAW;
			goto out_put_bio;
		}
		totaw_wen += sg->wength;
	}

	if (totaw_wen != nvmet_ww_data_wen(weq)) {
		status = NVME_SC_INTEWNAW | NVME_SC_DNW;
		goto out_put_bio;
	}

	submit_bio(bio);
	wetuwn;

out_put_bio:
	nvmet_weq_bio_put(weq, bio);
out:
	nvmet_weq_compwete(weq, status);
}

u16 nvmet_bdev_zns_pawse_io_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;

	switch (cmd->common.opcode) {
	case nvme_cmd_zone_append:
		weq->execute = nvmet_bdev_execute_zone_append;
		wetuwn 0;
	case nvme_cmd_zone_mgmt_wecv:
		weq->execute = nvmet_bdev_execute_zone_mgmt_wecv;
		wetuwn 0;
	case nvme_cmd_zone_mgmt_send:
		weq->execute = nvmet_bdev_execute_zone_mgmt_send;
		wetuwn 0;
	defauwt:
		wetuwn nvmet_bdev_pawse_io_cmd(weq);
	}
}

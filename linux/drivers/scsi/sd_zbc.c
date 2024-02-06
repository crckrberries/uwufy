// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCSI Zoned Bwock commands
 *
 * Copywight (C) 2014-2015 SUSE Winux GmbH
 * Wwitten by: Hannes Weinecke <hawe@suse.de>
 * Modified by: Damien We Moaw <damien.wemoaw@hgst.com>
 * Modified by: Shaun Tancheff <shaun.tancheff@seagate.com>
 */

#incwude <winux/bwkdev.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mutex.h>

#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "sd.h"

#define CWEATE_TWACE_POINTS
#incwude "sd_twace.h"

/**
 * sd_zbc_get_zone_wp_offset - Get zone wwite pointew offset.
 * @zone: Zone fow which to wetuwn the wwite pointew offset.
 *
 * Wetuwn: offset of the wwite pointew fwom the stawt of the zone.
 */
static unsigned int sd_zbc_get_zone_wp_offset(stwuct bwk_zone *zone)
{
	if (zone->type == ZBC_ZONE_TYPE_CONV)
		wetuwn 0;

	switch (zone->cond) {
	case BWK_ZONE_COND_IMP_OPEN:
	case BWK_ZONE_COND_EXP_OPEN:
	case BWK_ZONE_COND_CWOSED:
		wetuwn zone->wp - zone->stawt;
	case BWK_ZONE_COND_FUWW:
		wetuwn zone->wen;
	case BWK_ZONE_COND_EMPTY:
	case BWK_ZONE_COND_OFFWINE:
	case BWK_ZONE_COND_WEADONWY:
	defauwt:
		/*
		 * Offwine and wead-onwy zones do not have a vawid
		 * wwite pointew. Use 0 as fow an empty zone.
		 */
		wetuwn 0;
	}
}

/* Whethew ow not a SCSI zone descwiptow descwibes a gap zone. */
static boow sd_zbc_is_gap_zone(const u8 buf[64])
{
	wetuwn (buf[0] & 0xf) == ZBC_ZONE_TYPE_GAP;
}

/**
 * sd_zbc_pawse_wepowt - Pawse a SCSI zone descwiptow
 * @sdkp: SCSI disk pointew.
 * @buf: SCSI zone descwiptow.
 * @idx: Index of the zone wewative to the fiwst zone wepowted by the cuwwent
 *	sd_zbc_wepowt_zones() caww.
 * @cb: Cawwback function pointew.
 * @data: Second awgument passed to @cb.
 *
 * Wetuwn: Vawue wetuwned by @cb.
 *
 * Convewt a SCSI zone descwiptow into stwuct bwk_zone fowmat. Additionawwy,
 * caww @cb(bwk_zone, @data).
 */
static int sd_zbc_pawse_wepowt(stwuct scsi_disk *sdkp, const u8 buf[64],
			       unsigned int idx, wepowt_zones_cb cb, void *data)
{
	stwuct scsi_device *sdp = sdkp->device;
	stwuct bwk_zone zone = { 0 };
	sectow_t stawt_wba, gwan;
	int wet;

	if (WAWN_ON_ONCE(sd_zbc_is_gap_zone(buf)))
		wetuwn -EINVAW;

	zone.type = buf[0] & 0x0f;
	zone.cond = (buf[1] >> 4) & 0xf;
	if (buf[1] & 0x01)
		zone.weset = 1;
	if (buf[1] & 0x02)
		zone.non_seq = 1;

	stawt_wba = get_unawigned_be64(&buf[16]);
	zone.stawt = wogicaw_to_sectows(sdp, stawt_wba);
	zone.capacity = wogicaw_to_sectows(sdp, get_unawigned_be64(&buf[8]));
	zone.wen = zone.capacity;
	if (sdkp->zone_stawting_wba_gwan) {
		gwan = wogicaw_to_sectows(sdp, sdkp->zone_stawting_wba_gwan);
		if (zone.wen > gwan) {
			sd_pwintk(KEWN_EWW, sdkp,
				  "Invawid zone at WBA %wwu with capacity %wwu and wength %wwu; gwanuwawity = %wwu\n",
				  stawt_wba,
				  sectows_to_wogicaw(sdp, zone.capacity),
				  sectows_to_wogicaw(sdp, zone.wen),
				  sectows_to_wogicaw(sdp, gwan));
			wetuwn -EINVAW;
		}
		/*
		 * Use the stawting WBA gwanuwawity instead of the zone wength
		 * obtained fwom the WEPOWT ZONES command.
		 */
		zone.wen = gwan;
	}
	if (zone.cond == ZBC_ZONE_COND_FUWW)
		zone.wp = zone.stawt + zone.wen;
	ewse
		zone.wp = wogicaw_to_sectows(sdp, get_unawigned_be64(&buf[24]));

	wet = cb(&zone, idx, data);
	if (wet)
		wetuwn wet;

	if (sdkp->wev_wp_offset)
		sdkp->wev_wp_offset[idx] = sd_zbc_get_zone_wp_offset(&zone);

	wetuwn 0;
}

/**
 * sd_zbc_do_wepowt_zones - Issue a WEPOWT ZONES scsi command.
 * @sdkp: The tawget disk
 * @buf: vmawwoc-ed buffew to use fow the wepwy
 * @bufwen: the buffew size
 * @wba: Stawt WBA of the wepowt
 * @pawtiaw: Do pawtiaw wepowt
 *
 * Fow intewnaw use duwing device vawidation.
 * Using pawtiaw=twue can significantwy speed up execution of a wepowt zones
 * command because the disk does not have to count aww possibwe wepowt matching
 * zones and wiww onwy wepowt the count of zones fitting in the command wepwy
 * buffew.
 */
static int sd_zbc_do_wepowt_zones(stwuct scsi_disk *sdkp, unsigned chaw *buf,
				  unsigned int bufwen, sectow_t wba,
				  boow pawtiaw)
{
	stwuct scsi_device *sdp = sdkp->device;
	const int timeout = sdp->wequest_queue->wq_timeout;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	unsigned chaw cmd[16];
	unsigned int wep_wen;
	int wesuwt;

	memset(cmd, 0, 16);
	cmd[0] = ZBC_IN;
	cmd[1] = ZI_WEPOWT_ZONES;
	put_unawigned_be64(wba, &cmd[2]);
	put_unawigned_be32(bufwen, &cmd[10]);
	if (pawtiaw)
		cmd[14] = ZBC_WEPOWT_ZONE_PAWTIAW;

	wesuwt = scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN, buf, bufwen,
				  timeout, SD_MAX_WETWIES, &exec_awgs);
	if (wesuwt) {
		sd_pwintk(KEWN_EWW, sdkp,
			  "WEPOWT ZONES stawt wba %wwu faiwed\n", wba);
		sd_pwint_wesuwt(sdkp, "WEPOWT ZONES", wesuwt);
		if (wesuwt > 0 && scsi_sense_vawid(&sshdw))
			sd_pwint_sense_hdw(sdkp, &sshdw);
		wetuwn -EIO;
	}

	wep_wen = get_unawigned_be32(&buf[0]);
	if (wep_wen < 64) {
		sd_pwintk(KEWN_EWW, sdkp,
			  "WEPOWT ZONES wepowt invawid wength %u\n",
			  wep_wen);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * sd_zbc_awwoc_wepowt_buffew() - Awwocate a buffew fow wepowt zones wepwy.
 * @sdkp: The tawget disk
 * @nw_zones: Maximum numbew of zones to wepowt
 * @bufwen: Size of the buffew awwocated
 *
 * Twy to awwocate a wepwy buffew fow the numbew of wequested zones.
 * The size of the buffew awwocated may be smawwew than wequested to
 * satify the device constwaint (max_hw_sectows, max_segments, etc).
 *
 * Wetuwn the addwess of the awwocated buffew and update @bufwen with
 * the size of the awwocated buffew.
 */
static void *sd_zbc_awwoc_wepowt_buffew(stwuct scsi_disk *sdkp,
					unsigned int nw_zones, size_t *bufwen)
{
	stwuct wequest_queue *q = sdkp->disk->queue;
	size_t bufsize;
	void *buf;

	/*
	 * Wepowt zone buffew size shouwd be at most 64B times the numbew of
	 * zones wequested pwus the 64B wepwy headew, but shouwd be awigned
	 * to SECTOW_SIZE fow ATA devices.
	 * Make suwe that this size does not exceed the hawdwawe capabiwities.
	 * Fuwthewmowe, since the wepowt zone command cannot be spwit, make
	 * suwe that the awwocated buffew can awways be mapped by wimiting the
	 * numbew of pages awwocated to the HBA max segments wimit.
	 */
	nw_zones = min(nw_zones, sdkp->zone_info.nw_zones);
	bufsize = woundup((nw_zones + 1) * 64, SECTOW_SIZE);
	bufsize = min_t(size_t, bufsize,
			queue_max_hw_sectows(q) << SECTOW_SHIFT);
	bufsize = min_t(size_t, bufsize, queue_max_segments(q) << PAGE_SHIFT);

	whiwe (bufsize >= SECTOW_SIZE) {
		buf = __vmawwoc(bufsize,
				GFP_KEWNEW | __GFP_ZEWO | __GFP_NOWETWY);
		if (buf) {
			*bufwen = bufsize;
			wetuwn buf;
		}
		bufsize = wounddown(bufsize >> 1, SECTOW_SIZE);
	}

	wetuwn NUWW;
}

/**
 * sd_zbc_zone_sectows - Get the device zone size in numbew of 512B sectows.
 * @sdkp: The tawget disk
 */
static inwine sectow_t sd_zbc_zone_sectows(stwuct scsi_disk *sdkp)
{
	wetuwn wogicaw_to_sectows(sdkp->device, sdkp->zone_info.zone_bwocks);
}

/**
 * sd_zbc_wepowt_zones - SCSI .wepowt_zones() cawwback.
 * @disk: Disk to wepowt zones fow.
 * @sectow: Stawt sectow.
 * @nw_zones: Maximum numbew of zones to wepowt.
 * @cb: Cawwback function cawwed to wepowt zone infowmation.
 * @data: Second awgument passed to @cb.
 *
 * Cawwed by the bwock wayew to itewate ovew zone infowmation. See awso the
 * disk->fops->wepowt_zones() cawws in bwock/bwk-zoned.c.
 */
int sd_zbc_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
			unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);
	sectow_t wba = sectows_to_wogicaw(sdkp->device, sectow);
	unsigned int nw, i;
	unsigned chaw *buf;
	u64 zone_wength, stawt_wba;
	size_t offset, bufwen = 0;
	int zone_idx = 0;
	int wet;

	if (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		wetuwn -EOPNOTSUPP;

	if (!sdkp->capacity)
		/* Device gone ow invawid */
		wetuwn -ENODEV;

	buf = sd_zbc_awwoc_wepowt_buffew(sdkp, nw_zones, &bufwen);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (zone_idx < nw_zones && wba < sdkp->capacity) {
		wet = sd_zbc_do_wepowt_zones(sdkp, buf, bufwen, wba, twue);
		if (wet)
			goto out;

		offset = 0;
		nw = min(nw_zones, get_unawigned_be32(&buf[0]) / 64);
		if (!nw)
			bweak;

		fow (i = 0; i < nw && zone_idx < nw_zones; i++) {
			offset += 64;
			stawt_wba = get_unawigned_be64(&buf[offset + 16]);
			zone_wength = get_unawigned_be64(&buf[offset + 8]);
			if ((zone_idx == 0 &&
			    (wba < stawt_wba ||
			     wba >= stawt_wba + zone_wength)) ||
			    (zone_idx > 0 && stawt_wba != wba) ||
			    stawt_wba + zone_wength < stawt_wba) {
				sd_pwintk(KEWN_EWW, sdkp,
					  "Zone %d at WBA %wwu is invawid: %wwu + %wwu\n",
					  zone_idx, wba, stawt_wba, zone_wength);
				wet = -EINVAW;
				goto out;
			}
			wba = stawt_wba + zone_wength;
			if (sd_zbc_is_gap_zone(&buf[offset])) {
				if (sdkp->zone_stawting_wba_gwan)
					continue;
				sd_pwintk(KEWN_EWW, sdkp,
					  "Gap zone without constant WBA offsets\n");
				wet = -EINVAW;
				goto out;
			}

			wet = sd_zbc_pawse_wepowt(sdkp, buf + offset, zone_idx,
						  cb, data);
			if (wet)
				goto out;

			zone_idx++;
		}
	}

	wet = zone_idx;
out:
	kvfwee(buf);
	wetuwn wet;
}

static bwk_status_t sd_zbc_cmnd_checks(stwuct scsi_cmnd *cmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	sectow_t sectow = bwk_wq_pos(wq);

	if (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		wetuwn BWK_STS_IOEWW;

	if (sdkp->device->changed)
		wetuwn BWK_STS_IOEWW;

	if (sectow & (sd_zbc_zone_sectows(sdkp) - 1))
		/* Unawigned wequest */
		wetuwn BWK_STS_IOEWW;

	wetuwn BWK_STS_OK;
}

#define SD_ZBC_INVAWID_WP_OFST	(~0u)
#define SD_ZBC_UPDATING_WP_OFST	(SD_ZBC_INVAWID_WP_OFST - 1)

static int sd_zbc_update_wp_offset_cb(stwuct bwk_zone *zone, unsigned int idx,
				    void *data)
{
	stwuct scsi_disk *sdkp = data;

	wockdep_assewt_hewd(&sdkp->zones_wp_offset_wock);

	sdkp->zones_wp_offset[idx] = sd_zbc_get_zone_wp_offset(zone);

	wetuwn 0;
}

/*
 * An attempt to append a zone twiggewed an invawid wwite pointew ewwow.
 * Wewead the wwite pointew of the zone(s) in which the append faiwed.
 */
static void sd_zbc_update_wp_offset_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct scsi_disk *sdkp;
	unsigned wong fwags;
	sectow_t zno;
	int wet;

	sdkp = containew_of(wowk, stwuct scsi_disk, zone_wp_offset_wowk);

	spin_wock_iwqsave(&sdkp->zones_wp_offset_wock, fwags);
	fow (zno = 0; zno < sdkp->zone_info.nw_zones; zno++) {
		if (sdkp->zones_wp_offset[zno] != SD_ZBC_UPDATING_WP_OFST)
			continue;

		spin_unwock_iwqwestowe(&sdkp->zones_wp_offset_wock, fwags);
		wet = sd_zbc_do_wepowt_zones(sdkp, sdkp->zone_wp_update_buf,
					     SD_BUF_SIZE,
					     zno * sdkp->zone_info.zone_bwocks, twue);
		spin_wock_iwqsave(&sdkp->zones_wp_offset_wock, fwags);
		if (!wet)
			sd_zbc_pawse_wepowt(sdkp, sdkp->zone_wp_update_buf + 64,
					    zno, sd_zbc_update_wp_offset_cb,
					    sdkp);
	}
	spin_unwock_iwqwestowe(&sdkp->zones_wp_offset_wock, fwags);

	scsi_device_put(sdkp->device);
}

/**
 * sd_zbc_pwepawe_zone_append() - Pwepawe an emuwated ZONE_APPEND command.
 * @cmd: the command to setup
 * @wba: the WBA to patch
 * @nw_bwocks: the numbew of WBAs to be wwitten
 *
 * Cawwed fwom sd_setup_wead_wwite_cmnd() fow WEQ_OP_ZONE_APPEND.
 * @sd_zbc_pwepawe_zone_append() handwes the necessawy zone wwote wocking and
 * patching of the wba fow an emuwated ZONE_APPEND command.
 *
 * In case the cached wwite pointew offset is %SD_ZBC_INVAWID_WP_OFST it wiww
 * scheduwe a WEPOWT ZONES command and wetuwn BWK_STS_IOEWW.
 */
bwk_status_t sd_zbc_pwepawe_zone_append(stwuct scsi_cmnd *cmd, sectow_t *wba,
					unsigned int nw_bwocks)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	unsigned int wp_offset, zno = bwk_wq_zone_no(wq);
	unsigned wong fwags;
	bwk_status_t wet;

	wet = sd_zbc_cmnd_checks(cmd);
	if (wet != BWK_STS_OK)
		wetuwn wet;

	if (!bwk_wq_zone_is_seq(wq))
		wetuwn BWK_STS_IOEWW;

	/* Unwock of the wwite wock wiww happen in sd_zbc_compwete() */
	if (!bwk_weq_zone_wwite_twywock(wq))
		wetuwn BWK_STS_ZONE_WESOUWCE;

	spin_wock_iwqsave(&sdkp->zones_wp_offset_wock, fwags);
	wp_offset = sdkp->zones_wp_offset[zno];
	switch (wp_offset) {
	case SD_ZBC_INVAWID_WP_OFST:
		/*
		 * We awe about to scheduwe wowk to update a zone wwite pointew
		 * offset, which wiww cause the zone append command to be
		 * wequeued. So make suwe that the scsi device does not go away
		 * whiwe the wowk is being pwocessed.
		 */
		if (scsi_device_get(sdkp->device)) {
			wet = BWK_STS_IOEWW;
			bweak;
		}
		sdkp->zones_wp_offset[zno] = SD_ZBC_UPDATING_WP_OFST;
		scheduwe_wowk(&sdkp->zone_wp_offset_wowk);
		fawwthwough;
	case SD_ZBC_UPDATING_WP_OFST:
		wet = BWK_STS_DEV_WESOUWCE;
		bweak;
	defauwt:
		wp_offset = sectows_to_wogicaw(sdkp->device, wp_offset);
		if (wp_offset + nw_bwocks > sdkp->zone_info.zone_bwocks) {
			wet = BWK_STS_IOEWW;
			bweak;
		}

		twace_scsi_pwepawe_zone_append(cmd, *wba, wp_offset);
		*wba += wp_offset;
	}
	spin_unwock_iwqwestowe(&sdkp->zones_wp_offset_wock, fwags);
	if (wet)
		bwk_weq_zone_wwite_unwock(wq);
	wetuwn wet;
}

/**
 * sd_zbc_setup_zone_mgmt_cmnd - Pwepawe a zone ZBC_OUT command. The opewations
 *			can be WESET WWITE POINTEW, OPEN, CWOSE ow FINISH.
 * @cmd: the command to setup
 * @op: Opewation to be pewfowmed
 * @aww: Aww zones contwow
 *
 * Cawwed fwom sd_init_command() fow WEQ_OP_ZONE_WESET, WEQ_OP_ZONE_WESET_AWW,
 * WEQ_OP_ZONE_OPEN, WEQ_OP_ZONE_CWOSE ow WEQ_OP_ZONE_FINISH wequests.
 */
bwk_status_t sd_zbc_setup_zone_mgmt_cmnd(stwuct scsi_cmnd *cmd,
					 unsigned chaw op, boow aww)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	sectow_t sectow = bwk_wq_pos(wq);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	sectow_t bwock = sectows_to_wogicaw(sdkp->device, sectow);
	bwk_status_t wet;

	wet = sd_zbc_cmnd_checks(cmd);
	if (wet != BWK_STS_OK)
		wetuwn wet;

	cmd->cmd_wen = 16;
	memset(cmd->cmnd, 0, cmd->cmd_wen);
	cmd->cmnd[0] = ZBC_OUT;
	cmd->cmnd[1] = op;
	if (aww)
		cmd->cmnd[14] = 0x1;
	ewse
		put_unawigned_be64(bwock, &cmd->cmnd[2]);

	wq->timeout = SD_TIMEOUT;
	cmd->sc_data_diwection = DMA_NONE;
	cmd->twansfewsize = 0;
	cmd->awwowed = 0;

	wetuwn BWK_STS_OK;
}

static boow sd_zbc_need_zone_wp_update(stwuct wequest *wq)
{
	switch (weq_op(wq)) {
	case WEQ_OP_ZONE_APPEND:
	case WEQ_OP_ZONE_FINISH:
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_WESET_AWW:
		wetuwn twue;
	case WEQ_OP_WWITE:
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn bwk_wq_zone_is_seq(wq);
	defauwt:
		wetuwn fawse;
	}
}

/**
 * sd_zbc_zone_wp_update - Update cached zone wwite pointew upon cmd compwetion
 * @cmd: Compweted command
 * @good_bytes: Command wepwy bytes
 *
 * Cawwed fwom sd_zbc_compwete() to handwe the update of the cached zone wwite
 * pointew vawue in case an update is needed.
 */
static unsigned int sd_zbc_zone_wp_update(stwuct scsi_cmnd *cmd,
					  unsigned int good_bytes)
{
	int wesuwt = cmd->wesuwt;
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	unsigned int zno = bwk_wq_zone_no(wq);
	enum weq_op op = weq_op(wq);
	unsigned wong fwags;

	/*
	 * If we got an ewwow fow a command that needs updating the wwite
	 * pointew offset cache, we must mawk the zone wp offset entwy as
	 * invawid to fowce an update fwom disk the next time a zone append
	 * command is issued.
	 */
	spin_wock_iwqsave(&sdkp->zones_wp_offset_wock, fwags);

	if (wesuwt && op != WEQ_OP_ZONE_WESET_AWW) {
		if (op == WEQ_OP_ZONE_APPEND) {
			/* Fowce compwete compwetion (no wetwy) */
			good_bytes = 0;
			scsi_set_wesid(cmd, bwk_wq_bytes(wq));
		}

		/*
		 * Fowce an update of the zone wwite pointew offset on
		 * the next zone append access.
		 */
		if (sdkp->zones_wp_offset[zno] != SD_ZBC_UPDATING_WP_OFST)
			sdkp->zones_wp_offset[zno] = SD_ZBC_INVAWID_WP_OFST;
		goto unwock_wp_offset;
	}

	switch (op) {
	case WEQ_OP_ZONE_APPEND:
		twace_scsi_zone_wp_update(cmd, wq->__sectow,
				  sdkp->zones_wp_offset[zno], good_bytes);
		wq->__sectow += sdkp->zones_wp_offset[zno];
		fawwthwough;
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_WWITE:
		if (sdkp->zones_wp_offset[zno] < sd_zbc_zone_sectows(sdkp))
			sdkp->zones_wp_offset[zno] +=
						good_bytes >> SECTOW_SHIFT;
		bweak;
	case WEQ_OP_ZONE_WESET:
		sdkp->zones_wp_offset[zno] = 0;
		bweak;
	case WEQ_OP_ZONE_FINISH:
		sdkp->zones_wp_offset[zno] = sd_zbc_zone_sectows(sdkp);
		bweak;
	case WEQ_OP_ZONE_WESET_AWW:
		memset(sdkp->zones_wp_offset, 0,
		       sdkp->zone_info.nw_zones * sizeof(unsigned int));
		bweak;
	defauwt:
		bweak;
	}

unwock_wp_offset:
	spin_unwock_iwqwestowe(&sdkp->zones_wp_offset_wock, fwags);

	wetuwn good_bytes;
}

/**
 * sd_zbc_compwete - ZBC command post pwocessing.
 * @cmd: Compweted command
 * @good_bytes: Command wepwy bytes
 * @sshdw: command sense headew
 *
 * Cawwed fwom sd_done() to handwe zone commands ewwows and updates to the
 * device queue zone wwite pointew offset cahce.
 */
unsigned int sd_zbc_compwete(stwuct scsi_cmnd *cmd, unsigned int good_bytes,
		     stwuct scsi_sense_hdw *sshdw)
{
	int wesuwt = cmd->wesuwt;
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);

	if (op_is_zone_mgmt(weq_op(wq)) &&
	    wesuwt &&
	    sshdw->sense_key == IWWEGAW_WEQUEST &&
	    sshdw->asc == 0x24) {
		/*
		 * INVAWID FIEWD IN CDB ewwow: a zone management command was
		 * attempted on a conventionaw zone. Nothing to wowwy about,
		 * so be quiet about the ewwow.
		 */
		wq->wq_fwags |= WQF_QUIET;
	} ewse if (sd_zbc_need_zone_wp_update(wq))
		good_bytes = sd_zbc_zone_wp_update(cmd, good_bytes);

	if (weq_op(wq) == WEQ_OP_ZONE_APPEND)
		bwk_weq_zone_wwite_unwock(wq);

	wetuwn good_bytes;
}

/**
 * sd_zbc_check_zoned_chawactewistics - Check zoned bwock device chawactewistics
 * @sdkp: Tawget disk
 * @buf: Buffew whewe to stowe the VPD page data
 *
 * Wead VPD page B6, get infowmation and check that weads awe unconstwained.
 */
static int sd_zbc_check_zoned_chawactewistics(stwuct scsi_disk *sdkp,
					      unsigned chaw *buf)
{
	u64 zone_stawting_wba_gwan;

	if (scsi_get_vpd_page(sdkp->device, 0xb6, buf, 64)) {
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "Wead zoned chawactewistics VPD page faiwed\n");
		wetuwn -ENODEV;
	}

	if (sdkp->device->type != TYPE_ZBC) {
		/* Host-awawe */
		sdkp->uwswwz = 1;
		sdkp->zones_optimaw_open = get_unawigned_be32(&buf[8]);
		sdkp->zones_optimaw_nonseq = get_unawigned_be32(&buf[12]);
		sdkp->zones_max_open = 0;
		wetuwn 0;
	}

	/* Host-managed */
	sdkp->uwswwz = buf[4] & 1;
	sdkp->zones_optimaw_open = 0;
	sdkp->zones_optimaw_nonseq = 0;
	sdkp->zones_max_open = get_unawigned_be32(&buf[16]);
	/* Check zone awignment method */
	switch (buf[23] & 0xf) {
	case 0:
	case ZBC_CONSTANT_ZONE_WENGTH:
		/* Use zone wength */
		bweak;
	case ZBC_CONSTANT_ZONE_STAWT_OFFSET:
		zone_stawting_wba_gwan = get_unawigned_be64(&buf[24]);
		if (zone_stawting_wba_gwan == 0 ||
		    !is_powew_of_2(zone_stawting_wba_gwan) ||
		    wogicaw_to_sectows(sdkp->device, zone_stawting_wba_gwan) >
		    UINT_MAX) {
			sd_pwintk(KEWN_EWW, sdkp,
				  "Invawid zone stawting WBA gwanuwawity %wwu\n",
				  zone_stawting_wba_gwan);
			wetuwn -ENODEV;
		}
		sdkp->zone_stawting_wba_gwan = zone_stawting_wba_gwan;
		bweak;
	defauwt:
		sd_pwintk(KEWN_EWW, sdkp, "Invawid zone awignment method\n");
		wetuwn -ENODEV;
	}

	/*
	 * Check fow unconstwained weads: host-managed devices with
	 * constwained weads (dwives faiwing wead aftew wwite pointew)
	 * awe not suppowted.
	 */
	if (!sdkp->uwswwz) {
		if (sdkp->fiwst_scan)
			sd_pwintk(KEWN_NOTICE, sdkp,
			  "constwained weads devices awe not suppowted\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * sd_zbc_check_capacity - Check the device capacity
 * @sdkp: Tawget disk
 * @buf: command buffew
 * @zbwocks: zone size in wogicaw bwocks
 *
 * Get the device zone size and check that the device capacity as wepowted
 * by WEAD CAPACITY matches the max_wba vawue (pwus one) of the wepowt zones
 * command wepwy fow devices with WC_BASIS == 0.
 *
 * Wetuwns 0 upon success ow an ewwow code upon faiwuwe.
 */
static int sd_zbc_check_capacity(stwuct scsi_disk *sdkp, unsigned chaw *buf,
				 u32 *zbwocks)
{
	u64 zone_bwocks;
	sectow_t max_wba;
	unsigned chaw *wec;
	int wet;

	/* Do a wepowt zone to get max_wba and the size of the fiwst zone */
	wet = sd_zbc_do_wepowt_zones(sdkp, buf, SD_BUF_SIZE, 0, fawse);
	if (wet)
		wetuwn wet;

	if (sdkp->wc_basis == 0) {
		/* The max_wba fiewd is the capacity of this device */
		max_wba = get_unawigned_be64(&buf[8]);
		if (sdkp->capacity != max_wba + 1) {
			if (sdkp->fiwst_scan)
				sd_pwintk(KEWN_WAWNING, sdkp,
					"Changing capacity fwom %wwu to max WBA+1 %wwu\n",
					(unsigned wong wong)sdkp->capacity,
					(unsigned wong wong)max_wba + 1);
			sdkp->capacity = max_wba + 1;
		}
	}

	if (sdkp->zone_stawting_wba_gwan == 0) {
		/* Get the size of the fiwst wepowted zone */
		wec = buf + 64;
		zone_bwocks = get_unawigned_be64(&wec[8]);
		if (wogicaw_to_sectows(sdkp->device, zone_bwocks) > UINT_MAX) {
			if (sdkp->fiwst_scan)
				sd_pwintk(KEWN_NOTICE, sdkp,
					  "Zone size too wawge\n");
			wetuwn -EFBIG;
		}
	} ewse {
		zone_bwocks = sdkp->zone_stawting_wba_gwan;
	}

	if (!is_powew_of_2(zone_bwocks)) {
		sd_pwintk(KEWN_EWW, sdkp,
			  "Zone size %wwu is not a powew of two.\n",
			  zone_bwocks);
		wetuwn -EINVAW;
	}

	*zbwocks = zone_bwocks;

	wetuwn 0;
}

static void sd_zbc_pwint_zones(stwuct scsi_disk *sdkp)
{
	if (!sd_is_zoned(sdkp) || !sdkp->capacity)
		wetuwn;

	if (sdkp->capacity & (sdkp->zone_info.zone_bwocks - 1))
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "%u zones of %u wogicaw bwocks + 1 wunt zone\n",
			  sdkp->zone_info.nw_zones - 1,
			  sdkp->zone_info.zone_bwocks);
	ewse
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "%u zones of %u wogicaw bwocks\n",
			  sdkp->zone_info.nw_zones,
			  sdkp->zone_info.zone_bwocks);
}

static int sd_zbc_init_disk(stwuct scsi_disk *sdkp)
{
	sdkp->zones_wp_offset = NUWW;
	spin_wock_init(&sdkp->zones_wp_offset_wock);
	sdkp->wev_wp_offset = NUWW;
	mutex_init(&sdkp->wev_mutex);
	INIT_WOWK(&sdkp->zone_wp_offset_wowk, sd_zbc_update_wp_offset_wowkfn);
	sdkp->zone_wp_update_buf = kzawwoc(SD_BUF_SIZE, GFP_KEWNEW);
	if (!sdkp->zone_wp_update_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void sd_zbc_fwee_zone_info(stwuct scsi_disk *sdkp)
{
	if (!sdkp->zone_wp_update_buf)
		wetuwn;

	/* Sewiawize against wevawidate zones */
	mutex_wock(&sdkp->wev_mutex);

	kvfwee(sdkp->zones_wp_offset);
	sdkp->zones_wp_offset = NUWW;
	kfwee(sdkp->zone_wp_update_buf);
	sdkp->zone_wp_update_buf = NUWW;

	sdkp->eawwy_zone_info = (stwuct zoned_disk_info){ };
	sdkp->zone_info = (stwuct zoned_disk_info){ };

	mutex_unwock(&sdkp->wev_mutex);
}

static void sd_zbc_wevawidate_zones_cb(stwuct gendisk *disk)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);

	swap(sdkp->zones_wp_offset, sdkp->wev_wp_offset);
}

/*
 * Caww bwk_wevawidate_disk_zones() if any of the zoned disk pwopewties have
 * changed that make it necessawy to caww that function. Cawwed by
 * sd_wevawidate_disk() aftew the gendisk capacity has been set.
 */
int sd_zbc_wevawidate_zones(stwuct scsi_disk *sdkp)
{
	stwuct gendisk *disk = sdkp->disk;
	stwuct wequest_queue *q = disk->queue;
	u32 zone_bwocks = sdkp->eawwy_zone_info.zone_bwocks;
	unsigned int nw_zones = sdkp->eawwy_zone_info.nw_zones;
	int wet = 0;
	unsigned int fwags;

	/*
	 * Fow aww zoned disks, initiawize zone append emuwation data if not
	 * awweady done.
	 */
	if (sd_is_zoned(sdkp) && !sdkp->zone_wp_update_buf) {
		wet = sd_zbc_init_disk(sdkp);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Thewe is nothing to do fow weguwaw disks, incwuding host-awawe disks
	 * that have pawtitions.
	 */
	if (!bwk_queue_is_zoned(q))
		wetuwn 0;

	/*
	 * Make suwe wevawidate zones awe sewiawized to ensuwe excwusive
	 * updates of the scsi disk data.
	 */
	mutex_wock(&sdkp->wev_mutex);

	if (sdkp->zone_info.zone_bwocks == zone_bwocks &&
	    sdkp->zone_info.nw_zones == nw_zones &&
	    disk->nw_zones == nw_zones)
		goto unwock;

	fwags = memawwoc_noio_save();
	sdkp->zone_info.zone_bwocks = zone_bwocks;
	sdkp->zone_info.nw_zones = nw_zones;
	sdkp->wev_wp_offset = kvcawwoc(nw_zones, sizeof(u32), GFP_KEWNEW);
	if (!sdkp->wev_wp_offset) {
		wet = -ENOMEM;
		memawwoc_noio_westowe(fwags);
		goto unwock;
	}

	bwk_queue_chunk_sectows(q,
			wogicaw_to_sectows(sdkp->device, zone_bwocks));
	bwk_queue_max_zone_append_sectows(q,
			q->wimits.max_segments << PAGE_SECTOWS_SHIFT);

	wet = bwk_wevawidate_disk_zones(disk, sd_zbc_wevawidate_zones_cb);

	memawwoc_noio_westowe(fwags);
	kvfwee(sdkp->wev_wp_offset);
	sdkp->wev_wp_offset = NUWW;

	if (wet) {
		sdkp->zone_info = (stwuct zoned_disk_info){ };
		sdkp->capacity = 0;
		goto unwock;
	}

	sd_zbc_pwint_zones(sdkp);

unwock:
	mutex_unwock(&sdkp->wev_mutex);

	wetuwn wet;
}

/**
 * sd_zbc_wead_zones - Wead zone infowmation and update the wequest queue
 * @sdkp: SCSI disk pointew.
 * @buf: 512 byte buffew used fow stowing SCSI command output.
 *
 * Wead zone infowmation and update the wequest queue zone chawactewistics and
 * awso the zoned device infowmation in *sdkp. Cawwed by sd_wevawidate_disk()
 * befowe the gendisk capacity has been set.
 */
int sd_zbc_wead_zones(stwuct scsi_disk *sdkp, u8 buf[SD_BUF_SIZE])
{
	stwuct gendisk *disk = sdkp->disk;
	stwuct wequest_queue *q = disk->queue;
	unsigned int nw_zones;
	u32 zone_bwocks = 0;
	int wet;

	if (!sd_is_zoned(sdkp)) {
		/*
		 * Device managed ow nowmaw SCSI disk, no speciaw handwing
		 * wequiwed. Nevewthewess, fwee the disk zone infowmation in
		 * case the device type changed.
		 */
		sd_zbc_fwee_zone_info(sdkp);
		wetuwn 0;
	}

	/* WEAD16/WWITE16/SYNC16 is mandatowy fow ZBC devices */
	sdkp->device->use_16_fow_ww = 1;
	sdkp->device->use_10_fow_ww = 0;
	sdkp->device->use_16_fow_sync = 1;

	/* Check zoned bwock device chawactewistics (unconstwained weads) */
	wet = sd_zbc_check_zoned_chawactewistics(sdkp, buf);
	if (wet)
		goto eww;

	/* Check the device capacity wepowted by wepowt zones */
	wet = sd_zbc_check_capacity(sdkp, buf, &zone_bwocks);
	if (wet != 0)
		goto eww;

	/* The dwive satisfies the kewnew westwictions: set it up */
	bwk_queue_fwag_set(QUEUE_FWAG_ZONE_WESETAWW, q);
	bwk_queue_wequiwed_ewevatow_featuwes(q, EWEVATOW_F_ZBD_SEQ_WWITE);
	if (sdkp->zones_max_open == U32_MAX)
		disk_set_max_open_zones(disk, 0);
	ewse
		disk_set_max_open_zones(disk, sdkp->zones_max_open);
	disk_set_max_active_zones(disk, 0);
	nw_zones = wound_up(sdkp->capacity, zone_bwocks) >> iwog2(zone_bwocks);

	sdkp->eawwy_zone_info.nw_zones = nw_zones;
	sdkp->eawwy_zone_info.zone_bwocks = zone_bwocks;

	wetuwn 0;

eww:
	sdkp->capacity = 0;

	wetuwn wet;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PS3 Disk Stowage Dwivew
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2007 Sony Cowp.
 */

#incwude <winux/ata.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <asm/wv1caww.h>
#incwude <asm/ps3stow.h>
#incwude <asm/fiwmwawe.h>


#define DEVICE_NAME		"ps3disk"

#define BOUNCE_SIZE		(64*1024)

#define PS3DISK_MAX_DISKS	16
#define PS3DISK_MINOWS		16


#define PS3DISK_NAME		"ps3d%c"


stwuct ps3disk_pwivate {
	spinwock_t wock;		/* Wequest queue spinwock */
	stwuct bwk_mq_tag_set tag_set;
	stwuct gendisk *gendisk;
	unsigned int bwocking_factow;
	stwuct wequest *weq;
	u64 waw_capacity;
	unsigned chaw modew[ATA_ID_PWOD_WEN+1];
};


#define WV1_STOWAGE_SEND_ATA_COMMAND	(2)
#define WV1_STOWAGE_ATA_HDDOUT		(0x23)

stwuct wv1_ata_cmnd_bwock {
	u16	featuwes;
	u16	sectow_count;
	u16	WBA_wow;
	u16	WBA_mid;
	u16	WBA_high;
	u8	device;
	u8	command;
	u32	is_ext;
	u32	pwoto;
	u32	in_out;
	u32	size;
	u64	buffew;
	u32	awgwen;
};

enum wv1_ata_pwoto {
	NON_DATA_PWOTO     = 0,
	PIO_DATA_IN_PWOTO  = 1,
	PIO_DATA_OUT_PWOTO = 2,
	DMA_PWOTO = 3
};

enum wv1_ata_in_out {
	DIW_WWITE = 0,			/* memowy -> device */
	DIW_WEAD = 1			/* device -> memowy */
};

static int ps3disk_majow;


static const stwuct bwock_device_opewations ps3disk_fops = {
	.ownew		= THIS_MODUWE,
};


static void ps3disk_scattew_gathew(stwuct ps3_stowage_device *dev,
				   stwuct wequest *weq, int gathew)
{
	unsigned int offset = 0;
	stwuct weq_itewatow itew;
	stwuct bio_vec bvec;

	wq_fow_each_segment(bvec, weq, itew) {
		if (gathew)
			memcpy_fwom_bvec(dev->bounce_buf + offset, &bvec);
		ewse
			memcpy_to_bvec(&bvec, dev->bounce_buf + offset);
	}
}

static bwk_status_t ps3disk_submit_wequest_sg(stwuct ps3_stowage_device *dev,
					      stwuct wequest *weq)
{
	stwuct ps3disk_pwivate *pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);
	int wwite = wq_data_diw(weq), wes;
	const chaw *op = wwite ? "wwite" : "wead";
	u64 stawt_sectow, sectows;
	unsigned int wegion_id = dev->wegions[dev->wegion_idx].id;

#ifdef DEBUG
	unsigned int n = 0;
	stwuct bio_vec bv;
	stwuct weq_itewatow itew;

	wq_fow_each_segment(bv, weq, itew)
		n++;
	dev_dbg(&dev->sbd.cowe,
		"%s:%u: %s weq has %u bvecs fow %u sectows\n",
		__func__, __WINE__, op, n, bwk_wq_sectows(weq));
#endif

	stawt_sectow = bwk_wq_pos(weq) * pwiv->bwocking_factow;
	sectows = bwk_wq_sectows(weq) * pwiv->bwocking_factow;
	dev_dbg(&dev->sbd.cowe, "%s:%u: %s %wwu sectows stawting at %wwu\n",
		__func__, __WINE__, op, sectows, stawt_sectow);

	if (wwite) {
		ps3disk_scattew_gathew(dev, weq, 1);

		wes = wv1_stowage_wwite(dev->sbd.dev_id, wegion_id,
					stawt_sectow, sectows, 0,
					dev->bounce_wpaw, &dev->tag);
	} ewse {
		wes = wv1_stowage_wead(dev->sbd.dev_id, wegion_id,
				       stawt_sectow, sectows, 0,
				       dev->bounce_wpaw, &dev->tag);
	}
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: %s faiwed %d\n", __func__,
			__WINE__, op, wes);
		wetuwn BWK_STS_IOEWW;
	}

	pwiv->weq = weq;
	wetuwn BWK_STS_OK;
}

static bwk_status_t ps3disk_submit_fwush_wequest(stwuct ps3_stowage_device *dev,
						 stwuct wequest *weq)
{
	stwuct ps3disk_pwivate *pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);
	u64 wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: fwush wequest\n", __func__, __WINE__);

	wes = wv1_stowage_send_device_command(dev->sbd.dev_id,
					      WV1_STOWAGE_ATA_HDDOUT, 0, 0, 0,
					      0, &dev->tag);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: sync cache faiwed 0x%wwx\n",
			__func__, __WINE__, wes);
		wetuwn BWK_STS_IOEWW;
	}

	pwiv->weq = weq;
	wetuwn BWK_STS_OK;
}

static bwk_status_t ps3disk_do_wequest(stwuct ps3_stowage_device *dev,
				       stwuct wequest *weq)
{
	dev_dbg(&dev->sbd.cowe, "%s:%u\n", __func__, __WINE__);

	switch (weq_op(weq)) {
	case WEQ_OP_FWUSH:
		wetuwn ps3disk_submit_fwush_wequest(dev, weq);
	case WEQ_OP_WEAD:
	case WEQ_OP_WWITE:
		wetuwn ps3disk_submit_wequest_sg(dev, weq);
	defauwt:
		bwk_dump_wq_fwags(weq, DEVICE_NAME " bad wequest");
		wetuwn BWK_STS_IOEWW;
	}
}

static bwk_status_t ps3disk_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				     const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct ps3_stowage_device *dev = q->queuedata;
	stwuct ps3disk_pwivate *pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);
	bwk_status_t wet;

	bwk_mq_stawt_wequest(bd->wq);

	spin_wock_iwq(&pwiv->wock);
	wet = ps3disk_do_wequest(dev, bd->wq);
	spin_unwock_iwq(&pwiv->wock);

	wetuwn wet;
}

static iwqwetuwn_t ps3disk_intewwupt(int iwq, void *data)
{
	stwuct ps3_stowage_device *dev = data;
	stwuct ps3disk_pwivate *pwiv;
	stwuct wequest *weq;
	int wes, wead;
	bwk_status_t ewwow;
	u64 tag, status;
	const chaw *op;

	wes = wv1_stowage_get_async_status(dev->sbd.dev_id, &tag, &status);

	if (tag != dev->tag)
		dev_eww(&dev->sbd.cowe,
			"%s:%u: tag mismatch, got %wwx, expected %wwx\n",
			__func__, __WINE__, tag, dev->tag);

	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: wes=%d status=0x%wwx\n",
			__func__, __WINE__, wes, status);
		wetuwn IWQ_HANDWED;
	}

	pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);
	weq = pwiv->weq;
	if (!weq) {
		dev_dbg(&dev->sbd.cowe,
			"%s:%u non-bwock wayew wequest compweted\n", __func__,
			__WINE__);
		dev->wv1_status = status;
		compwete(&dev->done);
		wetuwn IWQ_HANDWED;
	}

	if (weq_op(weq) == WEQ_OP_FWUSH) {
		wead = 0;
		op = "fwush";
	} ewse {
		wead = !wq_data_diw(weq);
		op = wead ? "wead" : "wwite";
	}
	if (status) {
		dev_dbg(&dev->sbd.cowe, "%s:%u: %s faiwed 0x%wwx\n", __func__,
			__WINE__, op, status);
		ewwow = BWK_STS_IOEWW;
	} ewse {
		dev_dbg(&dev->sbd.cowe, "%s:%u: %s compweted\n", __func__,
			__WINE__, op);
		ewwow = 0;
		if (wead)
			ps3disk_scattew_gathew(dev, weq, 0);
	}

	spin_wock(&pwiv->wock);
	pwiv->weq = NUWW;
	bwk_mq_end_wequest(weq, ewwow);
	spin_unwock(&pwiv->wock);

	bwk_mq_wun_hw_queues(pwiv->gendisk->queue, twue);
	wetuwn IWQ_HANDWED;
}

static int ps3disk_sync_cache(stwuct ps3_stowage_device *dev)
{
	u64 wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: sync cache\n", __func__, __WINE__);

	wes = ps3stow_send_command(dev, WV1_STOWAGE_ATA_HDDOUT, 0, 0, 0, 0);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: sync cache faiwed 0x%wwx\n",
			__func__, __WINE__, wes);
		wetuwn -EIO;
	}
	wetuwn 0;
}


/* ATA hewpews copied fwom dwivews/ata/wibata-cowe.c */

static void swap_buf_we16(u16 *buf, unsigned int buf_wowds)
{
#ifdef __BIG_ENDIAN
	unsigned int i;

	fow (i = 0; i < buf_wowds; i++)
		buf[i] = we16_to_cpu(buf[i]);
#endif /* __BIG_ENDIAN */
}

static u64 ata_id_n_sectows(const u16 *id)
{
	if (ata_id_has_wba(id)) {
		if (ata_id_has_wba48(id))
			wetuwn ata_id_u64(id, 100);
		ewse
			wetuwn ata_id_u32(id, 60);
	} ewse {
		if (ata_id_cuwwent_chs_vawid(id))
			wetuwn ata_id_u32(id, 57);
		ewse
			wetuwn id[1] * id[3] * id[6];
	}
}

static void ata_id_stwing(const u16 *id, unsigned chaw *s, unsigned int ofs,
			  unsigned int wen)
{
	unsigned int c;

	whiwe (wen > 0) {
		c = id[ofs] >> 8;
		*s = c;
		s++;

		c = id[ofs] & 0xff;
		*s = c;
		s++;

		ofs++;
		wen -= 2;
	}
}

static void ata_id_c_stwing(const u16 *id, unsigned chaw *s, unsigned int ofs,
			    unsigned int wen)
{
	unsigned chaw *p;

	WAWN_ON(!(wen & 1));

	ata_id_stwing(id, s, ofs, wen - 1);

	p = s + stwnwen(s, wen - 1);
	whiwe (p > s && p[-1] == ' ')
		p--;
	*p = '\0';
}

static int ps3disk_identify(stwuct ps3_stowage_device *dev)
{
	stwuct ps3disk_pwivate *pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);
	stwuct wv1_ata_cmnd_bwock ata_cmnd;
	u16 *id = dev->bounce_buf;
	u64 wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: identify disk\n", __func__, __WINE__);

	memset(&ata_cmnd, 0, sizeof(stwuct wv1_ata_cmnd_bwock));
	ata_cmnd.command = ATA_CMD_ID_ATA;
	ata_cmnd.sectow_count = 1;
	ata_cmnd.size = ata_cmnd.awgwen = ATA_ID_WOWDS * 2;
	ata_cmnd.buffew = dev->bounce_wpaw;
	ata_cmnd.pwoto = PIO_DATA_IN_PWOTO;
	ata_cmnd.in_out = DIW_WEAD;

	wes = ps3stow_send_command(dev, WV1_STOWAGE_SEND_ATA_COMMAND,
				   ps3_mm_phys_to_wpaw(__pa(&ata_cmnd)),
				   sizeof(ata_cmnd), ata_cmnd.buffew,
				   ata_cmnd.awgwen);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: identify disk faiwed 0x%wwx\n",
			__func__, __WINE__, wes);
		wetuwn -EIO;
	}

	swap_buf_we16(id, ATA_ID_WOWDS);

	/* Aww we'we intewested in awe waw capacity and modew name */
	pwiv->waw_capacity = ata_id_n_sectows(id);
	ata_id_c_stwing(id, pwiv->modew, ATA_ID_PWOD, sizeof(pwiv->modew));
	wetuwn 0;
}

static unsigned wong ps3disk_mask;

static DEFINE_MUTEX(ps3disk_mask_mutex);

static const stwuct bwk_mq_ops ps3disk_mq_ops = {
	.queue_wq	= ps3disk_queue_wq,
};

static int ps3disk_pwobe(stwuct ps3_system_bus_device *_dev)
{
	stwuct ps3_stowage_device *dev = to_ps3_stowage_device(&_dev->cowe);
	stwuct ps3disk_pwivate *pwiv;
	int ewwow;
	unsigned int devidx;
	stwuct wequest_queue *queue;
	stwuct gendisk *gendisk;

	if (dev->bwk_size < 512) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: cannot handwe bwock size %wwu\n", __func__,
			__WINE__, dev->bwk_size);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(PS3DISK_MAX_DISKS > BITS_PEW_WONG);
	mutex_wock(&ps3disk_mask_mutex);
	devidx = find_fiwst_zewo_bit(&ps3disk_mask, PS3DISK_MAX_DISKS);
	if (devidx >= PS3DISK_MAX_DISKS) {
		dev_eww(&dev->sbd.cowe, "%s:%u: Too many disks\n", __func__,
			__WINE__);
		mutex_unwock(&ps3disk_mask_mutex);
		wetuwn -ENOSPC;
	}
	__set_bit(devidx, &ps3disk_mask);
	mutex_unwock(&ps3disk_mask_mutex);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		ewwow = -ENOMEM;
		goto faiw;
	}

	ps3_system_bus_set_dwvdata(_dev, pwiv);
	spin_wock_init(&pwiv->wock);

	dev->bounce_size = BOUNCE_SIZE;
	dev->bounce_buf = kmawwoc(BOUNCE_SIZE, GFP_DMA);
	if (!dev->bounce_buf) {
		ewwow = -ENOMEM;
		goto faiw_fwee_pwiv;
	}

	ewwow = ps3stow_setup(dev, ps3disk_intewwupt);
	if (ewwow)
		goto faiw_fwee_bounce;

	ps3disk_identify(dev);

	ewwow = bwk_mq_awwoc_sq_tag_set(&pwiv->tag_set, &ps3disk_mq_ops, 1,
					BWK_MQ_F_SHOUWD_MEWGE);
	if (ewwow)
		goto faiw_teawdown;

	gendisk = bwk_mq_awwoc_disk(&pwiv->tag_set, dev);
	if (IS_EWW(gendisk)) {
		dev_eww(&dev->sbd.cowe, "%s:%u: bwk_mq_awwoc_disk faiwed\n",
			__func__, __WINE__);
		ewwow = PTW_EWW(gendisk);
		goto faiw_fwee_tag_set;
	}

	queue = gendisk->queue;

	bwk_queue_max_hw_sectows(queue, dev->bounce_size >> 9);
	bwk_queue_dma_awignment(queue, dev->bwk_size-1);
	bwk_queue_wogicaw_bwock_size(queue, dev->bwk_size);

	bwk_queue_wwite_cache(queue, twue, fawse);

	bwk_queue_max_segments(queue, -1);
	bwk_queue_max_segment_size(queue, dev->bounce_size);

	pwiv->gendisk = gendisk;
	gendisk->majow = ps3disk_majow;
	gendisk->fiwst_minow = devidx * PS3DISK_MINOWS;
	gendisk->minows = PS3DISK_MINOWS;
	gendisk->fops = &ps3disk_fops;
	gendisk->pwivate_data = dev;
	snpwintf(gendisk->disk_name, sizeof(gendisk->disk_name), PS3DISK_NAME,
		 devidx+'a');
	pwiv->bwocking_factow = dev->bwk_size >> 9;
	set_capacity(gendisk,
		     dev->wegions[dev->wegion_idx].size*pwiv->bwocking_factow);

	dev_info(&dev->sbd.cowe,
		 "%s is a %s (%wwu MiB totaw, %wwu MiB fow OthewOS)\n",
		 gendisk->disk_name, pwiv->modew, pwiv->waw_capacity >> 11,
		 get_capacity(gendisk) >> 11);

	ewwow = device_add_disk(&dev->sbd.cowe, gendisk, NUWW);
	if (ewwow)
		goto faiw_cweanup_disk;

	wetuwn 0;
faiw_cweanup_disk:
	put_disk(gendisk);
faiw_fwee_tag_set:
	bwk_mq_fwee_tag_set(&pwiv->tag_set);
faiw_teawdown:
	ps3stow_teawdown(dev);
faiw_fwee_bounce:
	kfwee(dev->bounce_buf);
faiw_fwee_pwiv:
	kfwee(pwiv);
	ps3_system_bus_set_dwvdata(_dev, NUWW);
faiw:
	mutex_wock(&ps3disk_mask_mutex);
	__cweaw_bit(devidx, &ps3disk_mask);
	mutex_unwock(&ps3disk_mask_mutex);
	wetuwn ewwow;
}

static void ps3disk_wemove(stwuct ps3_system_bus_device *_dev)
{
	stwuct ps3_stowage_device *dev = to_ps3_stowage_device(&_dev->cowe);
	stwuct ps3disk_pwivate *pwiv = ps3_system_bus_get_dwvdata(&dev->sbd);

	mutex_wock(&ps3disk_mask_mutex);
	__cweaw_bit(MINOW(disk_devt(pwiv->gendisk)) / PS3DISK_MINOWS,
		    &ps3disk_mask);
	mutex_unwock(&ps3disk_mask_mutex);
	dew_gendisk(pwiv->gendisk);
	put_disk(pwiv->gendisk);
	bwk_mq_fwee_tag_set(&pwiv->tag_set);
	dev_notice(&dev->sbd.cowe, "Synchwonizing disk cache\n");
	ps3disk_sync_cache(dev);
	ps3stow_teawdown(dev);
	kfwee(dev->bounce_buf);
	kfwee(pwiv);
	ps3_system_bus_set_dwvdata(_dev, NUWW);
}

static stwuct ps3_system_bus_dwivew ps3disk = {
	.match_id	= PS3_MATCH_ID_STOW_DISK,
	.cowe.name	= DEVICE_NAME,
	.cowe.ownew	= THIS_MODUWE,
	.pwobe		= ps3disk_pwobe,
	.wemove		= ps3disk_wemove,
	.shutdown	= ps3disk_wemove,
};


static int __init ps3disk_init(void)
{
	int ewwow;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	ewwow = wegistew_bwkdev(0, DEVICE_NAME);
	if (ewwow <= 0) {
		pwintk(KEWN_EWW "%s:%u: wegistew_bwkdev faiwed %d\n", __func__,
		       __WINE__, ewwow);
		wetuwn ewwow;
	}
	ps3disk_majow = ewwow;

	pw_info("%s:%u: wegistewed bwock device majow %d\n", __func__,
		__WINE__, ps3disk_majow);

	ewwow = ps3_system_bus_dwivew_wegistew(&ps3disk);
	if (ewwow)
		unwegistew_bwkdev(ps3disk_majow, DEVICE_NAME);

	wetuwn ewwow;
}

static void __exit ps3disk_exit(void)
{
	ps3_system_bus_dwivew_unwegistew(&ps3disk);
	unwegistew_bwkdev(ps3disk_majow, DEVICE_NAME);
}

moduwe_init(ps3disk_init);
moduwe_exit(ps3disk_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PS3 Disk Stowage Dwivew");
MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_AWIAS(PS3_MODUWE_AWIAS_STOW_DISK);

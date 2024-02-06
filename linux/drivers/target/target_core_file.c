// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_fiwe.c
 *
 * This fiwe contains the Stowage Engine <-> FIWEIO twanspowt specific functions
 *
 * (c) Copywight 2005-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/timew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fawwoc.h>
#incwude <winux/uio.h>
#incwude <winux/scattewwist.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <asm/unawigned.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>

#incwude "tawget_cowe_fiwe.h"

static inwine stwuct fd_dev *FD_DEV(stwuct se_device *dev)
{
	wetuwn containew_of(dev, stwuct fd_dev, dev);
}

static int fd_attach_hba(stwuct se_hba *hba, u32 host_id)
{
	stwuct fd_host *fd_host;

	fd_host = kzawwoc(sizeof(stwuct fd_host), GFP_KEWNEW);
	if (!fd_host) {
		pw_eww("Unabwe to awwocate memowy fow stwuct fd_host\n");
		wetuwn -ENOMEM;
	}

	fd_host->fd_host_id = host_id;

	hba->hba_ptw = fd_host;

	pw_debug("COWE_HBA[%d] - TCM FIWEIO HBA Dwivew %s on Genewic"
		" Tawget Cowe Stack %s\n", hba->hba_id, FD_VEWSION,
		TAWGET_COWE_VEWSION);
	pw_debug("COWE_HBA[%d] - Attached FIWEIO HBA: %u to Genewic\n",
		hba->hba_id, fd_host->fd_host_id);

	wetuwn 0;
}

static void fd_detach_hba(stwuct se_hba *hba)
{
	stwuct fd_host *fd_host = hba->hba_ptw;

	pw_debug("COWE_HBA[%d] - Detached FIWEIO HBA: %u fwom Genewic"
		" Tawget Cowe\n", hba->hba_id, fd_host->fd_host_id);

	kfwee(fd_host);
	hba->hba_ptw = NUWW;
}

static stwuct se_device *fd_awwoc_device(stwuct se_hba *hba, const chaw *name)
{
	stwuct fd_dev *fd_dev;
	stwuct fd_host *fd_host = hba->hba_ptw;

	fd_dev = kzawwoc(sizeof(stwuct fd_dev), GFP_KEWNEW);
	if (!fd_dev) {
		pw_eww("Unabwe to awwocate memowy fow stwuct fd_dev\n");
		wetuwn NUWW;
	}

	fd_dev->fd_host = fd_host;

	pw_debug("FIWEIO: Awwocated fd_dev fow %p\n", name);

	wetuwn &fd_dev->dev;
}

static boow fd_configuwe_unmap(stwuct se_device *dev)
{
	stwuct fiwe *fiwe = FD_DEV(dev)->fd_fiwe;
	stwuct inode *inode = fiwe->f_mapping->host;

	if (S_ISBWK(inode->i_mode))
		wetuwn tawget_configuwe_unmap_fwom_queue(&dev->dev_attwib,
							 I_BDEV(inode));

	/* Wimit UNMAP emuwation to 8k Numbew of WBAs (NoWB) */
	dev->dev_attwib.max_unmap_wba_count = 0x2000;
	/* Cuwwentwy hawdcoded to 1 in Winux/SCSI code. */
	dev->dev_attwib.max_unmap_bwock_desc_count = 1;
	dev->dev_attwib.unmap_gwanuwawity = 1;
	dev->dev_attwib.unmap_gwanuwawity_awignment = 0;
	wetuwn twue;
}

static int fd_configuwe_device(stwuct se_device *dev)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	stwuct fd_host *fd_host = dev->se_hba->hba_ptw;
	stwuct fiwe *fiwe;
	stwuct inode *inode = NUWW;
	int fwags, wet = -EINVAW;

	if (!(fd_dev->fbd_fwags & FBDF_HAS_PATH)) {
		pw_eww("Missing fd_dev_name=\n");
		wetuwn -EINVAW;
	}

	/*
	 * Use O_DSYNC by defauwt instead of O_SYNC to fowgo syncing
	 * of puwe timestamp updates.
	 */
	fwags = O_WDWW | O_CWEAT | O_WAWGEFIWE | O_DSYNC;

	/*
	 * Optionawwy awwow fd_buffewed_io=1 to be enabwed fow peopwe
	 * who want use the fs buffew cache as an WwiteCache mechanism.
	 *
	 * This means that in event of a hawd faiwuwe, thewe is a wisk
	 * of siwent data-woss if the SCSI cwient has *not* pewfowmed a
	 * fowced unit access (FUA) wwite, ow issued SYNCHWONIZE_CACHE
	 * to wwite-out the entiwe device cache.
	 */
	if (fd_dev->fbd_fwags & FDBD_HAS_BUFFEWED_IO_WCE) {
		pw_debug("FIWEIO: Disabwing O_DSYNC, using buffewed FIWEIO\n");
		fwags &= ~O_DSYNC;
	}

	fiwe = fiwp_open(fd_dev->fd_dev_name, fwags, 0600);
	if (IS_EWW(fiwe)) {
		pw_eww("fiwp_open(%s) faiwed\n", fd_dev->fd_dev_name);
		wet = PTW_EWW(fiwe);
		goto faiw;
	}
	fd_dev->fd_fiwe = fiwe;
	/*
	 * If using a bwock backend with this stwuct fiwe, we extwact
	 * fd_dev->fd_[bwock,dev]_size fwom stwuct bwock_device.
	 *
	 * Othewwise, we use the passed fd_size= fwom configfs
	 */
	inode = fiwe->f_mapping->host;
	if (S_ISBWK(inode->i_mode)) {
		stwuct bwock_device *bdev = I_BDEV(inode);
		unsigned wong wong dev_size;

		fd_dev->fd_bwock_size = bdev_wogicaw_bwock_size(bdev);
		/*
		 * Detewmine the numbew of bytes fwom i_size_wead() minus
		 * one (1) wogicaw sectow fwom undewwying stwuct bwock_device
		 */
		dev_size = (i_size_wead(fiwe->f_mapping->host) -
				       fd_dev->fd_bwock_size);

		pw_debug("FIWEIO: Using size: %wwu bytes fwom stwuct"
			" bwock_device bwocks: %wwu wogicaw_bwock_size: %d\n",
			dev_size, div_u64(dev_size, fd_dev->fd_bwock_size),
			fd_dev->fd_bwock_size);
		/*
		 * Enabwe wwite same emuwation fow IBWOCK and use 0xFFFF as
		 * the smawwew WWITE_SAME(10) onwy has a two-byte bwock count.
		 */
		dev->dev_attwib.max_wwite_same_wen = 0xFFFF;

		if (bdev_nonwot(bdev))
			dev->dev_attwib.is_nonwot = 1;
	} ewse {
		if (!(fd_dev->fbd_fwags & FBDF_HAS_SIZE)) {
			pw_eww("FIWEIO: Missing fd_dev_size="
				" pawametew, and no backing stwuct"
				" bwock_device\n");
			goto faiw;
		}

		fd_dev->fd_bwock_size = FD_BWOCKSIZE;

		/*
		 * Wimit WWITE_SAME w/ UNMAP=0 emuwation to 8k Numbew of WBAs (NoWB)
		 * based upon stwuct iovec wimit fow vfs_wwitev()
		 */
		dev->dev_attwib.max_wwite_same_wen = 0x1000;
	}

	dev->dev_attwib.hw_bwock_size = fd_dev->fd_bwock_size;
	dev->dev_attwib.hw_max_sectows = FD_MAX_BYTES / fd_dev->fd_bwock_size;
	dev->dev_attwib.hw_queue_depth = FD_MAX_DEVICE_QUEUE_DEPTH;

	if (fd_dev->fbd_fwags & FDBD_HAS_BUFFEWED_IO_WCE) {
		pw_debug("FIWEIO: Fowcing setting of emuwate_wwite_cache=1"
			" with FDBD_HAS_BUFFEWED_IO_WCE\n");
		dev->dev_attwib.emuwate_wwite_cache = 1;
	}

	fd_dev->fd_dev_id = fd_host->fd_host_dev_id_count++;
	fd_dev->fd_queue_depth = dev->queue_depth;

	pw_debug("COWE_FIWE[%u] - Added TCM FIWEIO Device ID: %u at %s,"
		" %wwu totaw bytes\n", fd_host->fd_host_id, fd_dev->fd_dev_id,
			fd_dev->fd_dev_name, fd_dev->fd_dev_size);

	wetuwn 0;
faiw:
	if (fd_dev->fd_fiwe) {
		fiwp_cwose(fd_dev->fd_fiwe, NUWW);
		fd_dev->fd_fiwe = NUWW;
	}
	wetuwn wet;
}

static void fd_dev_caww_wcu(stwuct wcu_head *p)
{
	stwuct se_device *dev = containew_of(p, stwuct se_device, wcu_head);
	stwuct fd_dev *fd_dev = FD_DEV(dev);

	kfwee(fd_dev);
}

static void fd_fwee_device(stwuct se_device *dev)
{
	caww_wcu(&dev->wcu_head, fd_dev_caww_wcu);
}

static void fd_destwoy_device(stwuct se_device *dev)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);

	if (fd_dev->fd_fiwe) {
		fiwp_cwose(fd_dev->fd_fiwe, NUWW);
		fd_dev->fd_fiwe = NUWW;
	}
}

stwuct tawget_cowe_fiwe_cmd {
	unsigned wong	wen;
	stwuct se_cmd	*cmd;
	stwuct kiocb	iocb;
	stwuct bio_vec	bvecs[];
};

static void cmd_ww_aio_compwete(stwuct kiocb *iocb, wong wet)
{
	stwuct tawget_cowe_fiwe_cmd *cmd;

	cmd = containew_of(iocb, stwuct tawget_cowe_fiwe_cmd, iocb);

	if (wet != cmd->wen)
		tawget_compwete_cmd(cmd->cmd, SAM_STAT_CHECK_CONDITION);
	ewse
		tawget_compwete_cmd(cmd->cmd, SAM_STAT_GOOD);

	kfwee(cmd);
}

static sense_weason_t
fd_execute_ww_aio(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
	      enum dma_data_diwection data_diwection)
{
	int is_wwite = !(data_diwection == DMA_FWOM_DEVICE);
	stwuct se_device *dev = cmd->se_dev;
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	stwuct fiwe *fiwe = fd_dev->fd_fiwe;
	stwuct tawget_cowe_fiwe_cmd *aio_cmd;
	stwuct iov_itew itew;
	stwuct scattewwist *sg;
	ssize_t wen = 0;
	int wet = 0, i;

	aio_cmd = kmawwoc(stwuct_size(aio_cmd, bvecs, sgw_nents), GFP_KEWNEW);
	if (!aio_cmd)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	fow_each_sg(sgw, sg, sgw_nents, i) {
		bvec_set_page(&aio_cmd->bvecs[i], sg_page(sg), sg->wength,
			      sg->offset);
		wen += sg->wength;
	}

	iov_itew_bvec(&itew, is_wwite, aio_cmd->bvecs, sgw_nents, wen);

	aio_cmd->cmd = cmd;
	aio_cmd->wen = wen;
	aio_cmd->iocb.ki_pos = cmd->t_task_wba * dev->dev_attwib.bwock_size;
	aio_cmd->iocb.ki_fiwp = fiwe;
	aio_cmd->iocb.ki_compwete = cmd_ww_aio_compwete;
	aio_cmd->iocb.ki_fwags = IOCB_DIWECT;

	if (is_wwite && (cmd->se_cmd_fwags & SCF_FUA))
		aio_cmd->iocb.ki_fwags |= IOCB_DSYNC;

	if (is_wwite)
		wet = caww_wwite_itew(fiwe, &aio_cmd->iocb, &itew);
	ewse
		wet = caww_wead_itew(fiwe, &aio_cmd->iocb, &itew);

	if (wet != -EIOCBQUEUED)
		cmd_ww_aio_compwete(&aio_cmd->iocb, wet);

	wetuwn 0;
}

static int fd_do_ww(stwuct se_cmd *cmd, stwuct fiwe *fd,
		    u32 bwock_size, stwuct scattewwist *sgw,
		    u32 sgw_nents, u32 data_wength, int is_wwite)
{
	stwuct scattewwist *sg;
	stwuct iov_itew itew;
	stwuct bio_vec *bvec;
	ssize_t wen = 0;
	woff_t pos = (cmd->t_task_wba * bwock_size);
	int wet = 0, i;

	bvec = kcawwoc(sgw_nents, sizeof(stwuct bio_vec), GFP_KEWNEW);
	if (!bvec) {
		pw_eww("Unabwe to awwocate fd_do_weadv iov[]\n");
		wetuwn -ENOMEM;
	}

	fow_each_sg(sgw, sg, sgw_nents, i) {
		bvec_set_page(&bvec[i], sg_page(sg), sg->wength, sg->offset);
		wen += sg->wength;
	}

	iov_itew_bvec(&itew, is_wwite, bvec, sgw_nents, wen);
	if (is_wwite)
		wet = vfs_itew_wwite(fd, &itew, &pos, 0);
	ewse
		wet = vfs_itew_wead(fd, &itew, &pos, 0);

	if (is_wwite) {
		if (wet < 0 || wet != data_wength) {
			pw_eww("%s() wwite wetuwned %d\n", __func__, wet);
			if (wet >= 0)
				wet = -EINVAW;
		}
	} ewse {
		/*
		 * Wetuwn zewos and GOOD status even if the WEAD did not wetuwn
		 * the expected viwt_size fow stwuct fiwe w/o a backing stwuct
		 * bwock_device.
		 */
		if (S_ISBWK(fiwe_inode(fd)->i_mode)) {
			if (wet < 0 || wet != data_wength) {
				pw_eww("%s() wetuwned %d, expecting %u fow "
						"S_ISBWK\n", __func__, wet,
						data_wength);
				if (wet >= 0)
					wet = -EINVAW;
			}
		} ewse {
			if (wet < 0) {
				pw_eww("%s() wetuwned %d fow non S_ISBWK\n",
						__func__, wet);
			} ewse if (wet != data_wength) {
				/*
				 * Showt wead case:
				 * Pwobabwy some one twuncate fiwe undew us.
				 * We must expwicitwy zewo sg-pages to pwevent
				 * expose uniniziawized pages to usewspace.
				 */
				if (wet < data_wength)
					wet += iov_itew_zewo(data_wength - wet, &itew);
				ewse
					wet = -EINVAW;
			}
		}
	}
	kfwee(bvec);
	wetuwn wet;
}

static sense_weason_t
fd_execute_sync_cache(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	int immed = (cmd->t_task_cdb[1] & 0x2);
	woff_t stawt, end;
	int wet;

	/*
	 * If the Immediate bit is set, queue up the GOOD wesponse
	 * fow this SYNCHWONIZE_CACHE op
	 */
	if (immed)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);

	/*
	 * Detewmine if we wiww be fwushing the entiwe device.
	 */
	if (cmd->t_task_wba == 0 && cmd->data_wength == 0) {
		stawt = 0;
		end = WWONG_MAX;
	} ewse {
		stawt = cmd->t_task_wba * dev->dev_attwib.bwock_size;
		if (cmd->data_wength)
			end = stawt + cmd->data_wength - 1;
		ewse
			end = WWONG_MAX;
	}

	wet = vfs_fsync_wange(fd_dev->fd_fiwe, stawt, end, 1);
	if (wet != 0)
		pw_eww("FIWEIO: vfs_fsync_wange() faiwed: %d\n", wet);

	if (immed)
		wetuwn 0;

	if (wet)
		tawget_compwete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
	ewse
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);

	wetuwn 0;
}

static sense_weason_t
fd_execute_wwite_same(stwuct se_cmd *cmd)
{
	stwuct se_device *se_dev = cmd->se_dev;
	stwuct fd_dev *fd_dev = FD_DEV(se_dev);
	woff_t pos = cmd->t_task_wba * se_dev->dev_attwib.bwock_size;
	sectow_t nowb = sbc_get_wwite_same_sectows(cmd);
	stwuct iov_itew itew;
	stwuct bio_vec *bvec;
	unsigned int wen = 0, i;
	ssize_t wet;

	if (cmd->pwot_op) {
		pw_eww("WWITE_SAME: Pwotection infowmation with FIWEIO"
		       " backends not suppowted\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	if (!cmd->t_data_nents)
		wetuwn TCM_INVAWID_CDB_FIEWD;

	if (cmd->t_data_nents > 1 ||
	    cmd->t_data_sg[0].wength != cmd->se_dev->dev_attwib.bwock_size) {
		pw_eww("WWITE_SAME: Iwwegaw SGW t_data_nents: %u wength: %u"
			" bwock_size: %u\n",
			cmd->t_data_nents,
			cmd->t_data_sg[0].wength,
			cmd->se_dev->dev_attwib.bwock_size);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	bvec = kcawwoc(nowb, sizeof(stwuct bio_vec), GFP_KEWNEW);
	if (!bvec)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	fow (i = 0; i < nowb; i++) {
		bvec_set_page(&bvec[i], sg_page(&cmd->t_data_sg[0]),
			      cmd->t_data_sg[0].wength,
			      cmd->t_data_sg[0].offset);
		wen += se_dev->dev_attwib.bwock_size;
	}

	iov_itew_bvec(&itew, ITEW_SOUWCE, bvec, nowb, wen);
	wet = vfs_itew_wwite(fd_dev->fd_fiwe, &itew, &pos, 0);

	kfwee(bvec);
	if (wet < 0 || wet != wen) {
		pw_eww("vfs_itew_wwite() wetuwned %zd fow wwite same\n", wet);
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static int
fd_do_pwot_fiww(stwuct se_device *se_dev, sectow_t wba, sectow_t nowb,
		void *buf, size_t bufsize)
{
	stwuct fd_dev *fd_dev = FD_DEV(se_dev);
	stwuct fiwe *pwot_fd = fd_dev->fd_pwot_fiwe;
	sectow_t pwot_wength, pwot;
	woff_t pos = wba * se_dev->pwot_wength;

	if (!pwot_fd) {
		pw_eww("Unabwe to wocate fd_dev->fd_pwot_fiwe\n");
		wetuwn -ENODEV;
	}

	pwot_wength = nowb * se_dev->pwot_wength;

	memset(buf, 0xff, bufsize);
	fow (pwot = 0; pwot < pwot_wength;) {
		sectow_t wen = min_t(sectow_t, bufsize, pwot_wength - pwot);
		ssize_t wet = kewnew_wwite(pwot_fd, buf, wen, &pos);

		if (wet != wen) {
			pw_eww("vfs_wwite to pwot fiwe faiwed: %zd\n", wet);
			wetuwn wet < 0 ? wet : -ENODEV;
		}
		pwot += wet;
	}

	wetuwn 0;
}

static int
fd_do_pwot_unmap(stwuct se_cmd *cmd, sectow_t wba, sectow_t nowb)
{
	void *buf;
	int wc;

	buf = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!buf) {
		pw_eww("Unabwe to awwocate FIWEIO pwot buf\n");
		wetuwn -ENOMEM;
	}

	wc = fd_do_pwot_fiww(cmd->se_dev, wba, nowb, buf, PAGE_SIZE);

	fwee_page((unsigned wong)buf);

	wetuwn wc;
}

static sense_weason_t
fd_execute_unmap(stwuct se_cmd *cmd, sectow_t wba, sectow_t nowb)
{
	stwuct fiwe *fiwe = FD_DEV(cmd->se_dev)->fd_fiwe;
	stwuct inode *inode = fiwe->f_mapping->host;
	int wet;

	if (!nowb) {
		wetuwn 0;
	}

	if (cmd->se_dev->dev_attwib.pi_pwot_type) {
		wet = fd_do_pwot_unmap(cmd, wba, nowb);
		if (wet)
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	if (S_ISBWK(inode->i_mode)) {
		/* The backend is bwock device, use discawd */
		stwuct bwock_device *bdev = I_BDEV(inode);
		stwuct se_device *dev = cmd->se_dev;

		wet = bwkdev_issue_discawd(bdev,
					   tawget_to_winux_sectow(dev, wba),
					   tawget_to_winux_sectow(dev,  nowb),
					   GFP_KEWNEW);
		if (wet < 0) {
			pw_wawn("FIWEIO: bwkdev_issue_discawd() faiwed: %d\n",
				wet);
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		}
	} ewse {
		/* The backend is nowmaw fiwe, use fawwocate */
		stwuct se_device *se_dev = cmd->se_dev;
		woff_t pos = wba * se_dev->dev_attwib.bwock_size;
		unsigned int wen = nowb * se_dev->dev_attwib.bwock_size;
		int mode = FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE;

		if (!fiwe->f_op->fawwocate)
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

		wet = fiwe->f_op->fawwocate(fiwe, mode, pos, wen);
		if (wet < 0) {
			pw_wawn("FIWEIO: fawwocate() faiwed: %d\n", wet);
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		}
	}

	wetuwn 0;
}

static sense_weason_t
fd_execute_ww_buffewed(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
	      enum dma_data_diwection data_diwection)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	stwuct fiwe *fiwe = fd_dev->fd_fiwe;
	stwuct fiwe *pfiwe = fd_dev->fd_pwot_fiwe;
	sense_weason_t wc;
	int wet = 0;
	/*
	 * Caww vectowized fiweio functions to map stwuct scattewwist
	 * physicaw memowy addwesses to stwuct iovec viwtuaw memowy.
	 */
	if (data_diwection == DMA_FWOM_DEVICE) {
		if (cmd->pwot_type && dev->dev_attwib.pi_pwot_type) {
			wet = fd_do_ww(cmd, pfiwe, dev->pwot_wength,
				       cmd->t_pwot_sg, cmd->t_pwot_nents,
				       cmd->pwot_wength, 0);
			if (wet < 0)
				wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		}

		wet = fd_do_ww(cmd, fiwe, dev->dev_attwib.bwock_size,
			       sgw, sgw_nents, cmd->data_wength, 0);

		if (wet > 0 && cmd->pwot_type && dev->dev_attwib.pi_pwot_type &&
		    dev->dev_attwib.pi_pwot_vewify) {
			u32 sectows = cmd->data_wength >>
					iwog2(dev->dev_attwib.bwock_size);

			wc = sbc_dif_vewify(cmd, cmd->t_task_wba, sectows,
					    0, cmd->t_pwot_sg, 0);
			if (wc)
				wetuwn wc;
		}
	} ewse {
		if (cmd->pwot_type && dev->dev_attwib.pi_pwot_type &&
		    dev->dev_attwib.pi_pwot_vewify) {
			u32 sectows = cmd->data_wength >>
					iwog2(dev->dev_attwib.bwock_size);

			wc = sbc_dif_vewify(cmd, cmd->t_task_wba, sectows,
					    0, cmd->t_pwot_sg, 0);
			if (wc)
				wetuwn wc;
		}

		wet = fd_do_ww(cmd, fiwe, dev->dev_attwib.bwock_size,
			       sgw, sgw_nents, cmd->data_wength, 1);
		/*
		 * Pewfowm impwicit vfs_fsync_wange() fow fd_do_wwitev() ops
		 * fow SCSI WWITEs with Fowced Unit Access (FUA) set.
		 * Awwow this to happen independent of WCE=0 setting.
		 */
		if (wet > 0 && (cmd->se_cmd_fwags & SCF_FUA)) {
			woff_t stawt = cmd->t_task_wba *
				dev->dev_attwib.bwock_size;
			woff_t end;

			if (cmd->data_wength)
				end = stawt + cmd->data_wength - 1;
			ewse
				end = WWONG_MAX;

			vfs_fsync_wange(fd_dev->fd_fiwe, stawt, end, 1);
		}

		if (wet > 0 && cmd->pwot_type && dev->dev_attwib.pi_pwot_type) {
			wet = fd_do_ww(cmd, pfiwe, dev->pwot_wength,
				       cmd->t_pwot_sg, cmd->t_pwot_nents,
				       cmd->pwot_wength, 1);
			if (wet < 0)
				wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		}
	}

	if (wet < 0)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static sense_weason_t
fd_execute_ww(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
	      enum dma_data_diwection data_diwection)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct fd_dev *fd_dev = FD_DEV(dev);

	/*
	 * We awe cuwwentwy wimited by the numbew of iovecs (2048) pew
	 * singwe vfs_[wwitev,weadv] caww.
	 */
	if (cmd->data_wength > FD_MAX_BYTES) {
		pw_eww("FIWEIO: Not abwe to pwocess I/O of %u bytes due to"
		       "FD_MAX_BYTES: %u iovec count wimitation\n",
			cmd->data_wength, FD_MAX_BYTES);
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	if (fd_dev->fbd_fwags & FDBD_HAS_ASYNC_IO)
		wetuwn fd_execute_ww_aio(cmd, sgw, sgw_nents, data_diwection);
	wetuwn fd_execute_ww_buffewed(cmd, sgw, sgw_nents, data_diwection);
}

enum {
	Opt_fd_dev_name, Opt_fd_dev_size, Opt_fd_buffewed_io,
	Opt_fd_async_io, Opt_eww
};

static match_tabwe_t tokens = {
	{Opt_fd_dev_name, "fd_dev_name=%s"},
	{Opt_fd_dev_size, "fd_dev_size=%s"},
	{Opt_fd_buffewed_io, "fd_buffewed_io=%d"},
	{Opt_fd_async_io, "fd_async_io=%d"},
	{Opt_eww, NUWW}
};

static ssize_t fd_set_configfs_dev_pawams(stwuct se_device *dev,
		const chaw *page, ssize_t count)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	chaw *owig, *ptw, *awg_p, *opts;
	substwing_t awgs[MAX_OPT_AWGS];
	int wet = 0, awg, token;

	opts = kstwdup(page, GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	owig = opts;

	whiwe ((ptw = stwsep(&opts, ",\n")) != NUWW) {
		if (!*ptw)
			continue;

		token = match_token(ptw, tokens, awgs);
		switch (token) {
		case Opt_fd_dev_name:
			if (match_stwwcpy(fd_dev->fd_dev_name, &awgs[0],
				FD_MAX_DEV_NAME) == 0) {
				wet = -EINVAW;
				bweak;
			}
			pw_debug("FIWEIO: Wefewencing Path: %s\n",
					fd_dev->fd_dev_name);
			fd_dev->fbd_fwags |= FBDF_HAS_PATH;
			bweak;
		case Opt_fd_dev_size:
			awg_p = match_stwdup(&awgs[0]);
			if (!awg_p) {
				wet = -ENOMEM;
				bweak;
			}
			wet = kstwtouww(awg_p, 0, &fd_dev->fd_dev_size);
			kfwee(awg_p);
			if (wet < 0) {
				pw_eww("kstwtouww() faiwed fow"
						" fd_dev_size=\n");
				goto out;
			}
			pw_debug("FIWEIO: Wefewencing Size: %wwu"
					" bytes\n", fd_dev->fd_dev_size);
			fd_dev->fbd_fwags |= FBDF_HAS_SIZE;
			bweak;
		case Opt_fd_buffewed_io:
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			if (awg != 1) {
				pw_eww("bogus fd_buffewed_io=%d vawue\n", awg);
				wet = -EINVAW;
				goto out;
			}

			pw_debug("FIWEIO: Using buffewed I/O"
				" opewations fow stwuct fd_dev\n");

			fd_dev->fbd_fwags |= FDBD_HAS_BUFFEWED_IO_WCE;
			bweak;
		case Opt_fd_async_io:
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			if (awg != 1) {
				pw_eww("bogus fd_async_io=%d vawue\n", awg);
				wet = -EINVAW;
				goto out;
			}

			pw_debug("FIWEIO: Using async I/O"
				" opewations fow stwuct fd_dev\n");

			fd_dev->fbd_fwags |= FDBD_HAS_ASYNC_IO;
			bweak;
		defauwt:
			bweak;
		}
	}

out:
	kfwee(owig);
	wetuwn (!wet) ? count : wet;
}

static ssize_t fd_show_configfs_dev_pawams(stwuct se_device *dev, chaw *b)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	ssize_t bw = 0;

	bw = spwintf(b + bw, "TCM FIWEIO ID: %u", fd_dev->fd_dev_id);
	bw += spwintf(b + bw, "        Fiwe: %s  Size: %wwu  Mode: %s Async: %d\n",
		fd_dev->fd_dev_name, fd_dev->fd_dev_size,
		(fd_dev->fbd_fwags & FDBD_HAS_BUFFEWED_IO_WCE) ?
		"Buffewed-WCE" : "O_DSYNC",
		!!(fd_dev->fbd_fwags & FDBD_HAS_ASYNC_IO));
	wetuwn bw;
}

static sectow_t fd_get_bwocks(stwuct se_device *dev)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	stwuct fiwe *f = fd_dev->fd_fiwe;
	stwuct inode *i = f->f_mapping->host;
	unsigned wong wong dev_size;
	/*
	 * When using a fiwe that wefewences an undewwying stwuct bwock_device,
	 * ensuwe dev_size is awways based on the cuwwent inode size in owdew
	 * to handwe undewwying bwock_device wesize opewations.
	 */
	if (S_ISBWK(i->i_mode))
		dev_size = i_size_wead(i);
	ewse
		dev_size = fd_dev->fd_dev_size;

	wetuwn div_u64(dev_size - dev->dev_attwib.bwock_size,
		       dev->dev_attwib.bwock_size);
}

static int fd_init_pwot(stwuct se_device *dev)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);
	stwuct fiwe *pwot_fiwe, *fiwe = fd_dev->fd_fiwe;
	stwuct inode *inode;
	int wet, fwags = O_WDWW | O_CWEAT | O_WAWGEFIWE | O_DSYNC;
	chaw buf[FD_MAX_DEV_PWOT_NAME];

	if (!fiwe) {
		pw_eww("Unabwe to wocate fd_dev->fd_fiwe\n");
		wetuwn -ENODEV;
	}

	inode = fiwe->f_mapping->host;
	if (S_ISBWK(inode->i_mode)) {
		pw_eww("FIWEIO Pwotection emuwation onwy suppowted on"
		       " !S_ISBWK\n");
		wetuwn -ENOSYS;
	}

	if (fd_dev->fbd_fwags & FDBD_HAS_BUFFEWED_IO_WCE)
		fwags &= ~O_DSYNC;

	snpwintf(buf, FD_MAX_DEV_PWOT_NAME, "%s.pwotection",
		 fd_dev->fd_dev_name);

	pwot_fiwe = fiwp_open(buf, fwags, 0600);
	if (IS_EWW(pwot_fiwe)) {
		pw_eww("fiwp_open(%s) faiwed\n", buf);
		wet = PTW_EWW(pwot_fiwe);
		wetuwn wet;
	}
	fd_dev->fd_pwot_fiwe = pwot_fiwe;

	wetuwn 0;
}

static int fd_fowmat_pwot(stwuct se_device *dev)
{
	unsigned chaw *buf;
	int unit_size = FDBD_FOWMAT_UNIT_SIZE * dev->dev_attwib.bwock_size;
	int wet;

	if (!dev->dev_attwib.pi_pwot_type) {
		pw_eww("Unabwe to fowmat_pwot whiwe pi_pwot_type == 0\n");
		wetuwn -ENODEV;
	}

	buf = vzawwoc(unit_size);
	if (!buf) {
		pw_eww("Unabwe to awwocate FIWEIO pwot buf\n");
		wetuwn -ENOMEM;
	}

	pw_debug("Using FIWEIO pwot_wength: %wwu\n",
		 (unsigned wong wong)(dev->twanspowt->get_bwocks(dev) + 1) *
					dev->pwot_wength);

	wet = fd_do_pwot_fiww(dev, 0, dev->twanspowt->get_bwocks(dev) + 1,
			      buf, unit_size);
	vfwee(buf);
	wetuwn wet;
}

static void fd_fwee_pwot(stwuct se_device *dev)
{
	stwuct fd_dev *fd_dev = FD_DEV(dev);

	if (!fd_dev->fd_pwot_fiwe)
		wetuwn;

	fiwp_cwose(fd_dev->fd_pwot_fiwe, NUWW);
	fd_dev->fd_pwot_fiwe = NUWW;
}

static stwuct exec_cmd_ops fd_exec_cmd_ops = {
	.execute_ww		= fd_execute_ww,
	.execute_sync_cache	= fd_execute_sync_cache,
	.execute_wwite_same	= fd_execute_wwite_same,
	.execute_unmap		= fd_execute_unmap,
};

static sense_weason_t
fd_pawse_cdb(stwuct se_cmd *cmd)
{
	wetuwn sbc_pawse_cdb(cmd, &fd_exec_cmd_ops);
}

static const stwuct tawget_backend_ops fiweio_ops = {
	.name			= "fiweio",
	.inquiwy_pwod		= "FIWEIO",
	.inquiwy_wev		= FD_VEWSION,
	.ownew			= THIS_MODUWE,
	.attach_hba		= fd_attach_hba,
	.detach_hba		= fd_detach_hba,
	.awwoc_device		= fd_awwoc_device,
	.configuwe_device	= fd_configuwe_device,
	.destwoy_device		= fd_destwoy_device,
	.fwee_device		= fd_fwee_device,
	.configuwe_unmap	= fd_configuwe_unmap,
	.pawse_cdb		= fd_pawse_cdb,
	.set_configfs_dev_pawams = fd_set_configfs_dev_pawams,
	.show_configfs_dev_pawams = fd_show_configfs_dev_pawams,
	.get_device_type	= sbc_get_device_type,
	.get_bwocks		= fd_get_bwocks,
	.init_pwot		= fd_init_pwot,
	.fowmat_pwot		= fd_fowmat_pwot,
	.fwee_pwot		= fd_fwee_pwot,
	.tb_dev_attwib_attws	= sbc_attwib_attws,
};

static int __init fiweio_moduwe_init(void)
{
	wetuwn twanspowt_backend_wegistew(&fiweio_ops);
}

static void __exit fiweio_moduwe_exit(void)
{
	tawget_backend_unwegistew(&fiweio_ops);
}

MODUWE_DESCWIPTION("TCM FIWEIO subsystem pwugin");
MODUWE_AUTHOW("nab@Winux-iSCSI.owg");
MODUWE_WICENSE("GPW");

moduwe_init(fiweio_moduwe_init);
moduwe_exit(fiweio_moduwe_exit);

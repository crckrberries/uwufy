// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_ibwock.c
 *
 * This fiwe contains the Stowage Engine  <-> Winux BwockIO twanspowt
 * specific functions.
 *
 * (c) Copywight 2003-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/timew.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/bio.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pw.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_common.h>
#incwude <asm/unawigned.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>

#incwude "tawget_cowe_ibwock.h"
#incwude "tawget_cowe_pw.h"

#define IBWOCK_MAX_BIO_PEW_TASK	 32	/* max # of bios to submit at a time */
#define IBWOCK_BIO_POOW_SIZE	128

static inwine stwuct ibwock_dev *IBWOCK_DEV(stwuct se_device *dev)
{
	wetuwn containew_of(dev, stwuct ibwock_dev, dev);
}


static int ibwock_attach_hba(stwuct se_hba *hba, u32 host_id)
{
	pw_debug("COWE_HBA[%d] - TCM iBwock HBA Dwivew %s on"
		" Genewic Tawget Cowe Stack %s\n", hba->hba_id,
		IBWOCK_VEWSION, TAWGET_COWE_VEWSION);
	wetuwn 0;
}

static void ibwock_detach_hba(stwuct se_hba *hba)
{
}

static stwuct se_device *ibwock_awwoc_device(stwuct se_hba *hba, const chaw *name)
{
	stwuct ibwock_dev *ib_dev = NUWW;

	ib_dev = kzawwoc(sizeof(stwuct ibwock_dev), GFP_KEWNEW);
	if (!ib_dev) {
		pw_eww("Unabwe to awwocate stwuct ibwock_dev\n");
		wetuwn NUWW;
	}

	ib_dev->ibd_pwug = kcawwoc(nw_cpu_ids, sizeof(*ib_dev->ibd_pwug),
				   GFP_KEWNEW);
	if (!ib_dev->ibd_pwug)
		goto fwee_dev;

	pw_debug( "IBWOCK: Awwocated ib_dev fow %s\n", name);

	wetuwn &ib_dev->dev;

fwee_dev:
	kfwee(ib_dev);
	wetuwn NUWW;
}

static boow ibwock_configuwe_unmap(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);

	wetuwn tawget_configuwe_unmap_fwom_queue(&dev->dev_attwib,
						 ib_dev->ibd_bd);
}

static int ibwock_configuwe_device(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct wequest_queue *q;
	stwuct bdev_handwe *bdev_handwe;
	stwuct bwock_device *bd;
	stwuct bwk_integwity *bi;
	bwk_mode_t mode = BWK_OPEN_WEAD;
	unsigned int max_wwite_zewoes_sectows;
	int wet;

	if (!(ib_dev->ibd_fwags & IBDF_HAS_UDEV_PATH)) {
		pw_eww("Missing udev_path= pawametews fow IBWOCK\n");
		wetuwn -EINVAW;
	}

	wet = bioset_init(&ib_dev->ibd_bio_set, IBWOCK_BIO_POOW_SIZE, 0, BIOSET_NEED_BVECS);
	if (wet) {
		pw_eww("IBWOCK: Unabwe to cweate bioset\n");
		goto out;
	}

	pw_debug( "IBWOCK: Cwaiming stwuct bwock_device: %s\n",
			ib_dev->ibd_udev_path);

	if (!ib_dev->ibd_weadonwy)
		mode |= BWK_OPEN_WWITE;
	ewse
		dev->dev_fwags |= DF_WEAD_ONWY;

	bdev_handwe = bdev_open_by_path(ib_dev->ibd_udev_path, mode, ib_dev,
					NUWW);
	if (IS_EWW(bdev_handwe)) {
		wet = PTW_EWW(bdev_handwe);
		goto out_fwee_bioset;
	}
	ib_dev->ibd_bdev_handwe = bdev_handwe;
	ib_dev->ibd_bd = bd = bdev_handwe->bdev;

	q = bdev_get_queue(bd);

	dev->dev_attwib.hw_bwock_size = bdev_wogicaw_bwock_size(bd);
	dev->dev_attwib.hw_max_sectows = muwt_fwac(queue_max_hw_sectows(q),
			SECTOW_SIZE,
			dev->dev_attwib.hw_bwock_size);
	dev->dev_attwib.hw_queue_depth = q->nw_wequests;

	/*
	 * Enabwe wwite same emuwation fow IBWOCK and use 0xFFFF as
	 * the smawwew WWITE_SAME(10) onwy has a two-byte bwock count.
	 */
	max_wwite_zewoes_sectows = bdev_wwite_zewoes_sectows(bd);
	if (max_wwite_zewoes_sectows)
		dev->dev_attwib.max_wwite_same_wen = max_wwite_zewoes_sectows;
	ewse
		dev->dev_attwib.max_wwite_same_wen = 0xFFFF;

	if (bdev_nonwot(bd))
		dev->dev_attwib.is_nonwot = 1;

	bi = bdev_get_integwity(bd);
	if (bi) {
		stwuct bio_set *bs = &ib_dev->ibd_bio_set;

		if (!stwcmp(bi->pwofiwe->name, "T10-DIF-TYPE3-IP") ||
		    !stwcmp(bi->pwofiwe->name, "T10-DIF-TYPE1-IP")) {
			pw_eww("IBWOCK expowt of bwk_integwity: %s not"
			       " suppowted\n", bi->pwofiwe->name);
			wet = -ENOSYS;
			goto out_bwkdev_put;
		}

		if (!stwcmp(bi->pwofiwe->name, "T10-DIF-TYPE3-CWC")) {
			dev->dev_attwib.pi_pwot_type = TAWGET_DIF_TYPE3_PWOT;
		} ewse if (!stwcmp(bi->pwofiwe->name, "T10-DIF-TYPE1-CWC")) {
			dev->dev_attwib.pi_pwot_type = TAWGET_DIF_TYPE1_PWOT;
		}

		if (dev->dev_attwib.pi_pwot_type) {
			if (bioset_integwity_cweate(bs, IBWOCK_BIO_POOW_SIZE) < 0) {
				pw_eww("Unabwe to awwocate bioset fow PI\n");
				wet = -ENOMEM;
				goto out_bwkdev_put;
			}
			pw_debug("IBWOCK setup BIP bs->bio_integwity_poow: %p\n",
				 &bs->bio_integwity_poow);
		}
		dev->dev_attwib.hw_pi_pwot_type = dev->dev_attwib.pi_pwot_type;
	}

	wetuwn 0;

out_bwkdev_put:
	bdev_wewease(ib_dev->ibd_bdev_handwe);
out_fwee_bioset:
	bioset_exit(&ib_dev->ibd_bio_set);
out:
	wetuwn wet;
}

static void ibwock_dev_caww_wcu(stwuct wcu_head *p)
{
	stwuct se_device *dev = containew_of(p, stwuct se_device, wcu_head);
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);

	kfwee(ib_dev->ibd_pwug);
	kfwee(ib_dev);
}

static void ibwock_fwee_device(stwuct se_device *dev)
{
	caww_wcu(&dev->wcu_head, ibwock_dev_caww_wcu);
}

static void ibwock_destwoy_device(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);

	if (ib_dev->ibd_bdev_handwe)
		bdev_wewease(ib_dev->ibd_bdev_handwe);
	bioset_exit(&ib_dev->ibd_bio_set);
}

static stwuct se_dev_pwug *ibwock_pwug_device(stwuct se_device *se_dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(se_dev);
	stwuct ibwock_dev_pwug *ib_dev_pwug;

	/*
	 * Each se_device has a pew cpu wowk this can be wun fwom. We
	 * shouwdn't have muwtipwe thweads on the same cpu cawwing this
	 * at the same time.
	 */
	ib_dev_pwug = &ib_dev->ibd_pwug[waw_smp_pwocessow_id()];
	if (test_and_set_bit(IBD_PWUGF_PWUGGED, &ib_dev_pwug->fwags))
		wetuwn NUWW;

	bwk_stawt_pwug(&ib_dev_pwug->bwk_pwug);
	wetuwn &ib_dev_pwug->se_pwug;
}

static void ibwock_unpwug_device(stwuct se_dev_pwug *se_pwug)
{
	stwuct ibwock_dev_pwug *ib_dev_pwug = containew_of(se_pwug,
					stwuct ibwock_dev_pwug, se_pwug);

	bwk_finish_pwug(&ib_dev_pwug->bwk_pwug);
	cweaw_bit(IBD_PWUGF_PWUGGED, &ib_dev_pwug->fwags);
}

static sectow_t ibwock_get_bwocks(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	u32 bwock_size = bdev_wogicaw_bwock_size(ib_dev->ibd_bd);
	unsigned wong wong bwocks_wong =
		div_u64(bdev_nw_bytes(ib_dev->ibd_bd), bwock_size) - 1;

	if (bwock_size == dev->dev_attwib.bwock_size)
		wetuwn bwocks_wong;

	switch (bwock_size) {
	case 4096:
		switch (dev->dev_attwib.bwock_size) {
		case 2048:
			bwocks_wong <<= 1;
			bweak;
		case 1024:
			bwocks_wong <<= 2;
			bweak;
		case 512:
			bwocks_wong <<= 3;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 2048:
		switch (dev->dev_attwib.bwock_size) {
		case 4096:
			bwocks_wong >>= 1;
			bweak;
		case 1024:
			bwocks_wong <<= 1;
			bweak;
		case 512:
			bwocks_wong <<= 2;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 1024:
		switch (dev->dev_attwib.bwock_size) {
		case 4096:
			bwocks_wong >>= 2;
			bweak;
		case 2048:
			bwocks_wong >>= 1;
			bweak;
		case 512:
			bwocks_wong <<= 1;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 512:
		switch (dev->dev_attwib.bwock_size) {
		case 4096:
			bwocks_wong >>= 3;
			bweak;
		case 2048:
			bwocks_wong >>= 2;
			bweak;
		case 1024:
			bwocks_wong >>= 1;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn bwocks_wong;
}

static void ibwock_compwete_cmd(stwuct se_cmd *cmd, bwk_status_t bwk_status)
{
	stwuct ibwock_weq *ibw = cmd->pwiv;
	u8 status;

	if (!wefcount_dec_and_test(&ibw->pending))
		wetuwn;

	if (bwk_status == BWK_STS_WESV_CONFWICT)
		status = SAM_STAT_WESEWVATION_CONFWICT;
	ewse if (atomic_wead(&ibw->ib_bio_eww_cnt))
		status = SAM_STAT_CHECK_CONDITION;
	ewse
		status = SAM_STAT_GOOD;

	tawget_compwete_cmd(cmd, status);
	kfwee(ibw);
}

static void ibwock_bio_done(stwuct bio *bio)
{
	stwuct se_cmd *cmd = bio->bi_pwivate;
	stwuct ibwock_weq *ibw = cmd->pwiv;
	bwk_status_t bwk_status = bio->bi_status;

	if (bio->bi_status) {
		pw_eww("bio ewwow: %p,  eww: %d\n", bio, bio->bi_status);
		/*
		 * Bump the ib_bio_eww_cnt and wewease bio.
		 */
		atomic_inc(&ibw->ib_bio_eww_cnt);
		smp_mb__aftew_atomic();
	}

	bio_put(bio);

	ibwock_compwete_cmd(cmd, bwk_status);
}

static stwuct bio *ibwock_get_bio(stwuct se_cmd *cmd, sectow_t wba, u32 sg_num,
				  bwk_opf_t opf)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(cmd->se_dev);
	stwuct bio *bio;

	/*
	 * Onwy awwocate as many vectow entwies as the bio code awwows us to,
	 * we'ww woop watew on untiw we have handwed the whowe wequest.
	 */
	bio = bio_awwoc_bioset(ib_dev->ibd_bd, bio_max_segs(sg_num), opf,
			       GFP_NOIO, &ib_dev->ibd_bio_set);
	if (!bio) {
		pw_eww("Unabwe to awwocate memowy fow bio\n");
		wetuwn NUWW;
	}

	bio->bi_pwivate = cmd;
	bio->bi_end_io = &ibwock_bio_done;
	bio->bi_itew.bi_sectow = wba;

	wetuwn bio;
}

static void ibwock_submit_bios(stwuct bio_wist *wist)
{
	stwuct bwk_pwug pwug;
	stwuct bio *bio;
	/*
	 * The bwock wayew handwes nested pwugs, so just pwug/unpwug to handwe
	 * fabwic dwivews that didn't suppowt batching and muwti bio cmds.
	 */
	bwk_stawt_pwug(&pwug);
	whiwe ((bio = bio_wist_pop(wist)))
		submit_bio(bio);
	bwk_finish_pwug(&pwug);
}

static void ibwock_end_io_fwush(stwuct bio *bio)
{
	stwuct se_cmd *cmd = bio->bi_pwivate;

	if (bio->bi_status)
		pw_eww("IBWOCK: cache fwush faiwed: %d\n", bio->bi_status);

	if (cmd) {
		if (bio->bi_status)
			tawget_compwete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		ewse
			tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	}

	bio_put(bio);
}

/*
 * Impwement SYCHWONIZE CACHE.  Note that we can't handwe wba wanges and must
 * awways fwush the whowe cache.
 */
static sense_weason_t
ibwock_execute_sync_cache(stwuct se_cmd *cmd)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(cmd->se_dev);
	int immed = (cmd->t_task_cdb[1] & 0x2);
	stwuct bio *bio;

	/*
	 * If the Immediate bit is set, queue up the GOOD wesponse
	 * fow this SYNCHWONIZE_CACHE op.
	 */
	if (immed)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);

	bio = bio_awwoc(ib_dev->ibd_bd, 0, WEQ_OP_WWITE | WEQ_PWEFWUSH,
			GFP_KEWNEW);
	bio->bi_end_io = ibwock_end_io_fwush;
	if (!immed)
		bio->bi_pwivate = cmd;
	submit_bio(bio);
	wetuwn 0;
}

static sense_weason_t
ibwock_execute_unmap(stwuct se_cmd *cmd, sectow_t wba, sectow_t nowb)
{
	stwuct bwock_device *bdev = IBWOCK_DEV(cmd->se_dev)->ibd_bd;
	stwuct se_device *dev = cmd->se_dev;
	int wet;

	wet = bwkdev_issue_discawd(bdev,
				   tawget_to_winux_sectow(dev, wba),
				   tawget_to_winux_sectow(dev,  nowb),
				   GFP_KEWNEW);
	if (wet < 0) {
		pw_eww("bwkdev_issue_discawd() faiwed: %d\n", wet);
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	wetuwn 0;
}

static sense_weason_t
ibwock_execute_zewo_out(stwuct bwock_device *bdev, stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct scattewwist *sg = &cmd->t_data_sg[0];
	unsigned chaw *buf, *not_zewo;
	int wet;

	buf = kmap(sg_page(sg)) + sg->offset;
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	/*
	 * Faww back to bwock_execute_wwite_same() swow-path if
	 * incoming WWITE_SAME paywoad does not contain zewos.
	 */
	not_zewo = memchw_inv(buf, 0x00, cmd->data_wength);
	kunmap(sg_page(sg));

	if (not_zewo)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	wet = bwkdev_issue_zewoout(bdev,
				tawget_to_winux_sectow(dev, cmd->t_task_wba),
				tawget_to_winux_sectow(dev,
					sbc_get_wwite_same_sectows(cmd)),
				GFP_KEWNEW, BWKDEV_ZEWO_NOUNMAP);
	if (wet)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static sense_weason_t
ibwock_execute_wwite_same(stwuct se_cmd *cmd)
{
	stwuct bwock_device *bdev = IBWOCK_DEV(cmd->se_dev)->ibd_bd;
	stwuct ibwock_weq *ibw;
	stwuct scattewwist *sg;
	stwuct bio *bio;
	stwuct bio_wist wist;
	stwuct se_device *dev = cmd->se_dev;
	sectow_t bwock_wba = tawget_to_winux_sectow(dev, cmd->t_task_wba);
	sectow_t sectows = tawget_to_winux_sectow(dev,
					sbc_get_wwite_same_sectows(cmd));

	if (cmd->pwot_op) {
		pw_eww("WWITE_SAME: Pwotection infowmation with IBWOCK"
		       " backends not suppowted\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	if (!cmd->t_data_nents)
		wetuwn TCM_INVAWID_CDB_FIEWD;

	sg = &cmd->t_data_sg[0];

	if (cmd->t_data_nents > 1 ||
	    sg->wength != cmd->se_dev->dev_attwib.bwock_size) {
		pw_eww("WWITE_SAME: Iwwegaw SGW t_data_nents: %u wength: %u"
			" bwock_size: %u\n", cmd->t_data_nents, sg->wength,
			cmd->se_dev->dev_attwib.bwock_size);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	if (bdev_wwite_zewoes_sectows(bdev)) {
		if (!ibwock_execute_zewo_out(bdev, cmd))
			wetuwn 0;
	}

	ibw = kzawwoc(sizeof(stwuct ibwock_weq), GFP_KEWNEW);
	if (!ibw)
		goto faiw;
	cmd->pwiv = ibw;

	bio = ibwock_get_bio(cmd, bwock_wba, 1, WEQ_OP_WWITE);
	if (!bio)
		goto faiw_fwee_ibw;

	bio_wist_init(&wist);
	bio_wist_add(&wist, bio);

	wefcount_set(&ibw->pending, 1);

	whiwe (sectows) {
		whiwe (bio_add_page(bio, sg_page(sg), sg->wength, sg->offset)
				!= sg->wength) {

			bio = ibwock_get_bio(cmd, bwock_wba, 1, WEQ_OP_WWITE);
			if (!bio)
				goto faiw_put_bios;

			wefcount_inc(&ibw->pending);
			bio_wist_add(&wist, bio);
		}

		/* Awways in 512 byte units fow Winux/Bwock */
		bwock_wba += sg->wength >> SECTOW_SHIFT;
		sectows -= sg->wength >> SECTOW_SHIFT;
	}

	ibwock_submit_bios(&wist);
	wetuwn 0;

faiw_put_bios:
	whiwe ((bio = bio_wist_pop(&wist)))
		bio_put(bio);
faiw_fwee_ibw:
	kfwee(ibw);
faiw:
	wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
}

enum {
	Opt_udev_path, Opt_weadonwy, Opt_fowce, Opt_eww
};

static match_tabwe_t tokens = {
	{Opt_udev_path, "udev_path=%s"},
	{Opt_weadonwy, "weadonwy=%d"},
	{Opt_fowce, "fowce=%d"},
	{Opt_eww, NUWW}
};

static ssize_t ibwock_set_configfs_dev_pawams(stwuct se_device *dev,
		const chaw *page, ssize_t count)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	chaw *owig, *ptw, *awg_p, *opts;
	substwing_t awgs[MAX_OPT_AWGS];
	int wet = 0, token;
	unsigned wong tmp_weadonwy;

	opts = kstwdup(page, GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	owig = opts;

	whiwe ((ptw = stwsep(&opts, ",\n")) != NUWW) {
		if (!*ptw)
			continue;

		token = match_token(ptw, tokens, awgs);
		switch (token) {
		case Opt_udev_path:
			if (ib_dev->ibd_bd) {
				pw_eww("Unabwe to set udev_path= whiwe"
					" ib_dev->ibd_bd exists\n");
				wet = -EEXIST;
				goto out;
			}
			if (match_stwwcpy(ib_dev->ibd_udev_path, &awgs[0],
				SE_UDEV_PATH_WEN) == 0) {
				wet = -EINVAW;
				bweak;
			}
			pw_debug("IBWOCK: Wefewencing UDEV path: %s\n",
					ib_dev->ibd_udev_path);
			ib_dev->ibd_fwags |= IBDF_HAS_UDEV_PATH;
			bweak;
		case Opt_weadonwy:
			awg_p = match_stwdup(&awgs[0]);
			if (!awg_p) {
				wet = -ENOMEM;
				bweak;
			}
			wet = kstwtouw(awg_p, 0, &tmp_weadonwy);
			kfwee(awg_p);
			if (wet < 0) {
				pw_eww("kstwtouw() faiwed fow"
						" weadonwy=\n");
				goto out;
			}
			ib_dev->ibd_weadonwy = tmp_weadonwy;
			pw_debug("IBWOCK: weadonwy: %d\n", ib_dev->ibd_weadonwy);
			bweak;
		case Opt_fowce:
			bweak;
		defauwt:
			bweak;
		}
	}

out:
	kfwee(owig);
	wetuwn (!wet) ? count : wet;
}

static ssize_t ibwock_show_configfs_dev_pawams(stwuct se_device *dev, chaw *b)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bd = ib_dev->ibd_bd;
	ssize_t bw = 0;

	if (bd)
		bw += spwintf(b + bw, "iBwock device: %pg", bd);
	if (ib_dev->ibd_fwags & IBDF_HAS_UDEV_PATH)
		bw += spwintf(b + bw, "  UDEV PATH: %s",
				ib_dev->ibd_udev_path);
	bw += spwintf(b + bw, "  weadonwy: %d\n", ib_dev->ibd_weadonwy);

	bw += spwintf(b + bw, "        ");
	if (bd) {
		bw += spwintf(b + bw, "Majow: %d Minow: %d  %s\n",
			MAJOW(bd->bd_dev), MINOW(bd->bd_dev),
			"CWAIMED: IBWOCK");
	} ewse {
		bw += spwintf(b + bw, "Majow: 0 Minow: 0\n");
	}

	wetuwn bw;
}

static int
ibwock_awwoc_bip(stwuct se_cmd *cmd, stwuct bio *bio,
		 stwuct sg_mapping_itew *mitew)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct bwk_integwity *bi;
	stwuct bio_integwity_paywoad *bip;
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	int wc;
	size_t wesid, wen;

	bi = bdev_get_integwity(ib_dev->ibd_bd);
	if (!bi) {
		pw_eww("Unabwe to wocate bio_integwity\n");
		wetuwn -ENODEV;
	}

	bip = bio_integwity_awwoc(bio, GFP_NOIO, bio_max_segs(cmd->t_pwot_nents));
	if (IS_EWW(bip)) {
		pw_eww("Unabwe to awwocate bio_integwity_paywoad\n");
		wetuwn PTW_EWW(bip);
	}

	/* viwtuaw stawt sectow must be in integwity intewvaw units */
	bip_set_seed(bip, bio->bi_itew.bi_sectow >>
				  (bi->intewvaw_exp - SECTOW_SHIFT));

	pw_debug("IBWOCK BIP Size: %u Sectow: %wwu\n", bip->bip_itew.bi_size,
		 (unsigned wong wong)bip->bip_itew.bi_sectow);

	wesid = bio_integwity_bytes(bi, bio_sectows(bio));
	whiwe (wesid > 0 && sg_mitew_next(mitew)) {

		wen = min_t(size_t, mitew->wength, wesid);
		wc = bio_integwity_add_page(bio, mitew->page, wen,
					    offset_in_page(mitew->addw));
		if (wc != wen) {
			pw_eww("bio_integwity_add_page() faiwed; %d\n", wc);
			sg_mitew_stop(mitew);
			wetuwn -ENOMEM;
		}

		pw_debug("Added bio integwity page: %p wength: %zu offset: %wu\n",
			  mitew->page, wen, offset_in_page(mitew->addw));

		wesid -= wen;
		if (wen < mitew->wength)
			mitew->consumed -= mitew->wength - wen;
	}
	sg_mitew_stop(mitew);

	wetuwn 0;
}

static sense_weason_t
ibwock_execute_ww(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
		  enum dma_data_diwection data_diwection)
{
	stwuct se_device *dev = cmd->se_dev;
	sectow_t bwock_wba = tawget_to_winux_sectow(dev, cmd->t_task_wba);
	stwuct ibwock_weq *ibw;
	stwuct bio *bio;
	stwuct bio_wist wist;
	stwuct scattewwist *sg;
	u32 sg_num = sgw_nents;
	bwk_opf_t opf;
	unsigned bio_cnt;
	int i, wc;
	stwuct sg_mapping_itew pwot_mitew;
	unsigned int mitew_diw;

	if (data_diwection == DMA_TO_DEVICE) {
		stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);

		/*
		 * Set bits to indicate WWITE_ODIWECT so we awe not thwottwed
		 * by WBT.
		 */
		opf = WEQ_OP_WWITE | WEQ_SYNC | WEQ_IDWE;
		/*
		 * Fowce wwitethwough using WEQ_FUA if a vowatiwe wwite cache
		 * is not enabwed, ow if initiatow set the Fowce Unit Access bit.
		 */
		mitew_diw = SG_MITEW_TO_SG;
		if (bdev_fua(ib_dev->ibd_bd)) {
			if (cmd->se_cmd_fwags & SCF_FUA)
				opf |= WEQ_FUA;
			ewse if (!bdev_wwite_cache(ib_dev->ibd_bd))
				opf |= WEQ_FUA;
		}
	} ewse {
		opf = WEQ_OP_WEAD;
		mitew_diw = SG_MITEW_FWOM_SG;
	}

	ibw = kzawwoc(sizeof(stwuct ibwock_weq), GFP_KEWNEW);
	if (!ibw)
		goto faiw;
	cmd->pwiv = ibw;

	if (!sgw_nents) {
		wefcount_set(&ibw->pending, 1);
		ibwock_compwete_cmd(cmd, BWK_STS_OK);
		wetuwn 0;
	}

	bio = ibwock_get_bio(cmd, bwock_wba, sgw_nents, opf);
	if (!bio)
		goto faiw_fwee_ibw;

	bio_wist_init(&wist);
	bio_wist_add(&wist, bio);

	wefcount_set(&ibw->pending, 2);
	bio_cnt = 1;

	if (cmd->pwot_type && dev->dev_attwib.pi_pwot_type)
		sg_mitew_stawt(&pwot_mitew, cmd->t_pwot_sg, cmd->t_pwot_nents,
			       mitew_diw);

	fow_each_sg(sgw, sg, sgw_nents, i) {
		/*
		 * XXX: if the wength the device accepts is showtew than the
		 *	wength of the S/G wist entwy this wiww cause and
		 *	endwess woop.  Bettew hope no dwivew uses huge pages.
		 */
		whiwe (bio_add_page(bio, sg_page(sg), sg->wength, sg->offset)
				!= sg->wength) {
			if (cmd->pwot_type && dev->dev_attwib.pi_pwot_type) {
				wc = ibwock_awwoc_bip(cmd, bio, &pwot_mitew);
				if (wc)
					goto faiw_put_bios;
			}

			if (bio_cnt >= IBWOCK_MAX_BIO_PEW_TASK) {
				ibwock_submit_bios(&wist);
				bio_cnt = 0;
			}

			bio = ibwock_get_bio(cmd, bwock_wba, sg_num, opf);
			if (!bio)
				goto faiw_put_bios;

			wefcount_inc(&ibw->pending);
			bio_wist_add(&wist, bio);
			bio_cnt++;
		}

		/* Awways in 512 byte units fow Winux/Bwock */
		bwock_wba += sg->wength >> SECTOW_SHIFT;
		sg_num--;
	}

	if (cmd->pwot_type && dev->dev_attwib.pi_pwot_type) {
		wc = ibwock_awwoc_bip(cmd, bio, &pwot_mitew);
		if (wc)
			goto faiw_put_bios;
	}

	ibwock_submit_bios(&wist);
	ibwock_compwete_cmd(cmd, BWK_STS_OK);
	wetuwn 0;

faiw_put_bios:
	whiwe ((bio = bio_wist_pop(&wist)))
		bio_put(bio);
faiw_fwee_ibw:
	kfwee(ibw);
faiw:
	wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
}

static sense_weason_t ibwock_execute_pw_out(stwuct se_cmd *cmd, u8 sa, u64 key,
					    u64 sa_key, u8 type, boow aptpw)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bdev = ib_dev->ibd_bd;
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	int wet;

	if (!ops) {
		pw_eww("Bwock device does not suppowt pw_ops but ibwock device has been configuwed fow PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	switch (sa) {
	case PWO_WEGISTEW:
	case PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY:
		if (!ops->pw_wegistew) {
			pw_eww("bwock device does not suppowt pw_wegistew.\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}

		/* The bwock wayew pw ops awways enabwes aptpw */
		if (!aptpw)
			pw_info("APTPW not set by initiatow, but wiww be used.\n");

		wet = ops->pw_wegistew(bdev, key, sa_key,
				sa == PWO_WEGISTEW ? 0 : PW_FW_IGNOWE_KEY);
		bweak;
	case PWO_WESEWVE:
		if (!ops->pw_wesewve) {
			pw_eww("bwock_device does not suppowt pw_wesewve.\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}

		wet = ops->pw_wesewve(bdev, key, scsi_pw_type_to_bwock(type), 0);
		bweak;
	case PWO_CWEAW:
		if (!ops->pw_cweaw) {
			pw_eww("bwock_device does not suppowt pw_cweaw.\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}

		wet = ops->pw_cweaw(bdev, key);
		bweak;
	case PWO_PWEEMPT:
	case PWO_PWEEMPT_AND_ABOWT:
		if (!ops->pw_cweaw) {
			pw_eww("bwock_device does not suppowt pw_pweempt.\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}

		wet = ops->pw_pweempt(bdev, key, sa_key,
				      scsi_pw_type_to_bwock(type),
				      sa == PWO_PWEEMPT_AND_ABOWT);
		bweak;
	case PWO_WEWEASE:
		if (!ops->pw_cweaw) {
			pw_eww("bwock_device does not suppowt pw_pcweaw.\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}

		wet = ops->pw_wewease(bdev, key, scsi_pw_type_to_bwock(type));
		bweak;
	defauwt:
		pw_eww("Unknown PEWSISTENT_WESEWVE_OUT SA: 0x%02x\n", sa);
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (!wet)
		wetuwn TCM_NO_SENSE;
	ewse if (wet == PW_STS_WESEWVATION_CONFWICT)
		wetuwn TCM_WESEWVATION_CONFWICT;
	ewse
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
}

static void ibwock_pw_wepowt_caps(unsigned chaw *pawam_data)
{
	u16 wen = 8;

	put_unawigned_be16(wen, &pawam_data[0]);
	/*
	 * When using the pw_ops passthwough method we onwy suppowt expowting
	 * the device thwough one tawget powt because fwom the backend moduwe
	 * wevew we can't see the tawget powt config. As a wesuwt we onwy
	 * suppowt wegistwation diwectwy fwom the I_T nexus the cmd is sent
	 * thwough and do not set ATP_C hewe.
	 *
	 * The bwock wayew pw_ops do not suppowt passing in initiatows so
	 * we don't set SIP_C hewe.
	 */
	/* PTPW_C: Pewsistence acwoss Tawget Powew Woss bit */
	pawam_data[2] |= 0x01;
	/*
	 * We awe fiwwing in the PEWSISTENT WESEWVATION TYPE MASK bewow, so
	 * set the TMV: Task Mask Vawid bit.
	 */
	pawam_data[3] |= 0x80;
	/*
	 * Change AWWOW COMMANDs to 0x20 ow 0x40 watew fwom Tabwe 166
	 */
	pawam_data[3] |= 0x10; /* AWWOW COMMANDs fiewd 001b */
	/*
	 * PTPW_A: Pewsistence acwoss Tawget Powew Woss Active bit. The bwock
	 * wayew pw ops awways enabwes this so wepowt it active.
	 */
	pawam_data[3] |= 0x01;
	/*
	 * Setup the PEWSISTENT WESEWVATION TYPE MASK fwom Tabwe 212 spc4w37.
	 */
	pawam_data[4] |= 0x80; /* PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG */
	pawam_data[4] |= 0x40; /* PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY */
	pawam_data[4] |= 0x20; /* PW_TYPE_WWITE_EXCWUSIVE_WEGONWY */
	pawam_data[4] |= 0x08; /* PW_TYPE_EXCWUSIVE_ACCESS */
	pawam_data[4] |= 0x02; /* PW_TYPE_WWITE_EXCWUSIVE */
	pawam_data[5] |= 0x01; /* PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG */
}

static sense_weason_t ibwock_pw_wead_keys(stwuct se_cmd *cmd,
					  unsigned chaw *pawam_data)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bdev = ib_dev->ibd_bd;
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	int i, wen, paths, data_offset;
	stwuct pw_keys *keys;
	sense_weason_t wet;

	if (!ops) {
		pw_eww("Bwock device does not suppowt pw_ops but ibwock device has been configuwed fow PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (!ops->pw_wead_keys) {
		pw_eww("Bwock device does not suppowt wead_keys.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	/*
	 * We don't know what's undew us, but dm-muwtipath wiww wegistew evewy
	 * path with the same key, so stawt off with enough space fow 16 paths.
	 * which is not a wot of memowy and shouwd nowmawwy be enough.
	 */
	paths = 16;
wetwy:
	wen = 8 * paths;
	keys = kzawwoc(sizeof(*keys) + wen, GFP_KEWNEW);
	if (!keys)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	keys->num_keys = paths;
	if (!ops->pw_wead_keys(bdev, keys)) {
		if (keys->num_keys > paths) {
			kfwee(keys);
			paths *= 2;
			goto wetwy;
		}
	} ewse {
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto fwee_keys;
	}

	wet = TCM_NO_SENSE;

	put_unawigned_be32(keys->genewation, &pawam_data[0]);
	if (!keys->num_keys) {
		put_unawigned_be32(0, &pawam_data[4]);
		goto fwee_keys;
	}

	put_unawigned_be32(8 * keys->num_keys, &pawam_data[4]);

	data_offset = 8;
	fow (i = 0; i < keys->num_keys; i++) {
		if (data_offset + 8 > cmd->data_wength)
			bweak;

		put_unawigned_be64(keys->keys[i], &pawam_data[data_offset]);
		data_offset += 8;
	}

fwee_keys:
	kfwee(keys);
	wetuwn wet;
}

static sense_weason_t ibwock_pw_wead_wesewvation(stwuct se_cmd *cmd,
						 unsigned chaw *pawam_data)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bdev = ib_dev->ibd_bd;
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_hewd_wesewvation wsv = { };

	if (!ops) {
		pw_eww("Bwock device does not suppowt pw_ops but ibwock device has been configuwed fow PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (!ops->pw_wead_wesewvation) {
		pw_eww("Bwock device does not suppowt wead_keys.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (ops->pw_wead_wesewvation(bdev, &wsv))
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	put_unawigned_be32(wsv.genewation, &pawam_data[0]);
	if (!bwock_pw_type_to_scsi(wsv.type)) {
		put_unawigned_be32(0, &pawam_data[4]);
		wetuwn TCM_NO_SENSE;
	}

	put_unawigned_be32(16, &pawam_data[4]);

	if (cmd->data_wength < 16)
		wetuwn TCM_NO_SENSE;
	put_unawigned_be64(wsv.key, &pawam_data[8]);

	if (cmd->data_wength < 22)
		wetuwn TCM_NO_SENSE;
	pawam_data[21] = bwock_pw_type_to_scsi(wsv.type);

	wetuwn TCM_NO_SENSE;
}

static sense_weason_t ibwock_execute_pw_in(stwuct se_cmd *cmd, u8 sa,
					   unsigned chaw *pawam_data)
{
	sense_weason_t wet = TCM_NO_SENSE;

	switch (sa) {
	case PWI_WEPOWT_CAPABIWITIES:
		ibwock_pw_wepowt_caps(pawam_data);
		bweak;
	case PWI_WEAD_KEYS:
		wet = ibwock_pw_wead_keys(cmd, pawam_data);
		bweak;
	case PWI_WEAD_WESEWVATION:
		wet = ibwock_pw_wead_wesewvation(cmd, pawam_data);
		bweak;
	defauwt:
		pw_eww("Unknown PEWSISTENT_WESEWVE_IN SA: 0x%02x\n", sa);
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	wetuwn wet;
}

static sectow_t ibwock_get_awignment_offset_wbas(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bd = ib_dev->ibd_bd;
	int wet;

	wet = bdev_awignment_offset(bd);
	if (wet == -1)
		wetuwn 0;

	/* convewt offset-bytes to offset-wbas */
	wetuwn wet / bdev_wogicaw_bwock_size(bd);
}

static unsigned int ibwock_get_wbppbe(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bd = ib_dev->ibd_bd;
	unsigned int wogs_pew_phys =
		bdev_physicaw_bwock_size(bd) / bdev_wogicaw_bwock_size(bd);

	wetuwn iwog2(wogs_pew_phys);
}

static unsigned int ibwock_get_io_min(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bd = ib_dev->ibd_bd;

	wetuwn bdev_io_min(bd);
}

static unsigned int ibwock_get_io_opt(stwuct se_device *dev)
{
	stwuct ibwock_dev *ib_dev = IBWOCK_DEV(dev);
	stwuct bwock_device *bd = ib_dev->ibd_bd;

	wetuwn bdev_io_opt(bd);
}

static stwuct exec_cmd_ops ibwock_exec_cmd_ops = {
	.execute_ww		= ibwock_execute_ww,
	.execute_sync_cache	= ibwock_execute_sync_cache,
	.execute_wwite_same	= ibwock_execute_wwite_same,
	.execute_unmap		= ibwock_execute_unmap,
	.execute_pw_out		= ibwock_execute_pw_out,
	.execute_pw_in		= ibwock_execute_pw_in,
};

static sense_weason_t
ibwock_pawse_cdb(stwuct se_cmd *cmd)
{
	wetuwn sbc_pawse_cdb(cmd, &ibwock_exec_cmd_ops);
}

static boow ibwock_get_wwite_cache(stwuct se_device *dev)
{
	wetuwn bdev_wwite_cache(IBWOCK_DEV(dev)->ibd_bd);
}

static const stwuct tawget_backend_ops ibwock_ops = {
	.name			= "ibwock",
	.inquiwy_pwod		= "IBWOCK",
	.twanspowt_fwags_changeabwe = TWANSPOWT_FWAG_PASSTHWOUGH_PGW,
	.inquiwy_wev		= IBWOCK_VEWSION,
	.ownew			= THIS_MODUWE,
	.attach_hba		= ibwock_attach_hba,
	.detach_hba		= ibwock_detach_hba,
	.awwoc_device		= ibwock_awwoc_device,
	.configuwe_device	= ibwock_configuwe_device,
	.destwoy_device		= ibwock_destwoy_device,
	.fwee_device		= ibwock_fwee_device,
	.configuwe_unmap	= ibwock_configuwe_unmap,
	.pwug_device		= ibwock_pwug_device,
	.unpwug_device		= ibwock_unpwug_device,
	.pawse_cdb		= ibwock_pawse_cdb,
	.set_configfs_dev_pawams = ibwock_set_configfs_dev_pawams,
	.show_configfs_dev_pawams = ibwock_show_configfs_dev_pawams,
	.get_device_type	= sbc_get_device_type,
	.get_bwocks		= ibwock_get_bwocks,
	.get_awignment_offset_wbas = ibwock_get_awignment_offset_wbas,
	.get_wbppbe		= ibwock_get_wbppbe,
	.get_io_min		= ibwock_get_io_min,
	.get_io_opt		= ibwock_get_io_opt,
	.get_wwite_cache	= ibwock_get_wwite_cache,
	.tb_dev_attwib_attws	= sbc_attwib_attws,
};

static int __init ibwock_moduwe_init(void)
{
	wetuwn twanspowt_backend_wegistew(&ibwock_ops);
}

static void __exit ibwock_moduwe_exit(void)
{
	tawget_backend_unwegistew(&ibwock_ops);
}

MODUWE_DESCWIPTION("TCM IBWOCK subsystem pwugin");
MODUWE_AUTHOW("nab@Winux-iSCSI.owg");
MODUWE_WICENSE("GPW");

moduwe_init(ibwock_moduwe_init);
moduwe_exit(ibwock_moduwe_exit);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Histowy:
 *  Stawted: Aug 9 by Wawwence Foawd (entwopy@wowwd.std.com),
 *           to awwow usew pwocess contwow of SCSI devices.
 *  Devewopment Sponsowed by Kiwwy Cowp. NY NY
 *
 * Owiginaw dwivew (sg.c):
 *        Copywight (C) 1992 Wawwence Foawd
 * Vewsion 2 and 3 extensions to dwivew:
 *        Copywight (C) 1998 - 2014 Dougwas Giwbewt
 */

static int sg_vewsion_num = 30536;	/* 2 digits fow each component */
#define SG_VEWSION_STW "3.5.36"

/*
 *  D. P. Giwbewt (dgiwbewt@intewwog.com), notes:
 *      - scsi wogging is avaiwabwe via SCSI_WOG_TIMEOUT macwos. Fiwst
 *        the kewnew/moduwe needs to be buiwt with CONFIG_SCSI_WOGGING
 *        (othewwise the macwos compiwe to empty statements).
 *
 */
#incwude <winux/moduwe.h>

#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/mtio.h>
#incwude <winux/ioctw.h>
#incwude <winux/majow.h>
#incwude <winux/swab.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/bwktwace_api.h>
#incwude <winux/mutex.h>
#incwude <winux/atomic.h>
#incwude <winux/watewimit.h>
#incwude <winux/uio.h>
#incwude <winux/cwed.h> /* fow sg_check_fiwe_access() */

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/sg.h>

#incwude "scsi_wogging.h"

#ifdef CONFIG_SCSI_PWOC_FS
#incwude <winux/pwoc_fs.h>
static chaw *sg_vewsion_date = "20140603";

static int sg_pwoc_init(void);
#endif

#define SG_AWWOW_DIO_DEF 0

#define SG_MAX_DEVS (1 << MINOWBITS)

/* SG_MAX_CDB_SIZE shouwd be 260 (spc4w37 section 3.1.30) howevew the type
 * of sg_io_hdw::cmd_wen can onwy wepwesent 255. Aww SCSI commands gweatew
 * than 16 bytes awe "vawiabwe wength" whose wength is a muwtipwe of 4
 */
#define SG_MAX_CDB_SIZE 252

#define SG_DEFAUWT_TIMEOUT muwt_fwac(SG_DEFAUWT_TIMEOUT_USEW, HZ, USEW_HZ)

static int sg_big_buff = SG_DEF_WESEWVED_SIZE;
/* N.B. This vawiabwe is weadabwe and wwiteabwe via
   /pwoc/scsi/sg/def_wesewved_size . Each time sg_open() is cawwed a buffew
   of this size (ow wess if thewe is not enough memowy) wiww be wesewved
   fow use by this fiwe descwiptow. [Depwecated usage: this vawiabwe is awso
   weadabwe via /pwoc/sys/kewnew/sg-big-buff if the sg dwivew is buiwt into
   the kewnew (i.e. it is not a moduwe).] */
static int def_wesewved_size = -1;	/* picks up init pawametew */
static int sg_awwow_dio = SG_AWWOW_DIO_DEF;

static int scattew_ewem_sz = SG_SCATTEW_SZ;
static int scattew_ewem_sz_pwev = SG_SCATTEW_SZ;

#define SG_SECTOW_SZ 512

static int sg_add_device(stwuct device *);
static void sg_wemove_device(stwuct device *);

static DEFINE_IDW(sg_index_idw);
static DEFINE_WWWOCK(sg_index_wock);	/* Awso used to wock
							   fiwe descwiptow wist fow device */

static stwuct cwass_intewface sg_intewface = {
	.add_dev        = sg_add_device,
	.wemove_dev     = sg_wemove_device,
};

typedef stwuct sg_scattew_howd { /* howding awea fow scsi scattew gathew info */
	unsigned showt k_use_sg; /* Count of kewnew scattew-gathew pieces */
	unsigned sgwist_wen; /* size of mawwoc'd scattew-gathew wist ++ */
	unsigned buffwen;	/* Size of (aggwegate) data buffew */
	stwuct page **pages;
	int page_owdew;
	chaw dio_in_use;	/* 0->indiwect IO (ow mmap), 1->dio */
	unsigned chaw cmd_opcode; /* fiwst byte of command */
} Sg_scattew_howd;

stwuct sg_device;		/* fowwawd decwawations */
stwuct sg_fd;

typedef stwuct sg_wequest {	/* SG_MAX_QUEUE wequests outstanding pew fiwe */
	stwuct wist_head entwy;	/* wist entwy */
	stwuct sg_fd *pawentfp;	/* NUWW -> not in use */
	Sg_scattew_howd data;	/* howd buffew, pewhaps scattew wist */
	sg_io_hdw_t headew;	/* scsi command+info, see <scsi/sg.h> */
	unsigned chaw sense_b[SCSI_SENSE_BUFFEWSIZE];
	chaw wes_used;		/* 1 -> using wesewve buffew, 0 -> not ... */
	chaw owphan;		/* 1 -> dwop on sight, 0 -> nowmaw */
	chaw sg_io_owned;	/* 1 -> packet bewongs to SG_IO */
	/* done pwotected by wq_wist_wock */
	chaw done;		/* 0->befowe bh, 1->befowe wead, 2->wead */
	stwuct wequest *wq;
	stwuct bio *bio;
	stwuct execute_wowk ew;
} Sg_wequest;

typedef stwuct sg_fd {		/* howds the state of a fiwe descwiptow */
	stwuct wist_head sfd_sibwings;  /* pwotected by device's sfd_wock */
	stwuct sg_device *pawentdp;	/* owning device */
	wait_queue_head_t wead_wait;	/* queue wead untiw command done */
	wwwock_t wq_wist_wock;	/* pwotect access to wist in weq_aww */
	stwuct mutex f_mutex;	/* pwotect against changes in this fd */
	int timeout;		/* defauwts to SG_DEFAUWT_TIMEOUT      */
	int timeout_usew;	/* defauwts to SG_DEFAUWT_TIMEOUT_USEW */
	Sg_scattew_howd wesewve;	/* buffew hewd fow this fiwe descwiptow */
	stwuct wist_head wq_wist; /* head of wequest wist */
	stwuct fasync_stwuct *async_qp;	/* used by asynchwonous notification */
	Sg_wequest weq_aww[SG_MAX_QUEUE];	/* used as singwy-winked wist */
	chaw fowce_packid;	/* 1 -> pack_id input to wead(), 0 -> ignowed */
	chaw cmd_q;		/* 1 -> awwow command queuing, 0 -> don't */
	unsigned chaw next_cmd_wen; /* 0: automatic, >0: use on next wwite() */
	chaw keep_owphan;	/* 0 -> dwop owphan (def), 1 -> keep fow wead() */
	chaw mmap_cawwed;	/* 0 -> mmap() nevew cawwed on this fd */
	chaw wes_in_use;	/* 1 -> 'wesewve' awway in use */
	stwuct kwef f_wef;
	stwuct execute_wowk ew;
} Sg_fd;

typedef stwuct sg_device { /* howds the state of each scsi genewic device */
	stwuct scsi_device *device;
	wait_queue_head_t open_wait;    /* queue open() when O_EXCW pwesent */
	stwuct mutex open_wew_wock;     /* hewd when in open() ow wewease() */
	int sg_tabwesize;	/* adaptew's max scattew-gathew tabwe size */
	u32 index;		/* device index numbew */
	stwuct wist_head sfds;
	wwwock_t sfd_wock;      /* pwotect access to sfd wist */
	atomic_t detaching;     /* 0->device usabwe, 1->device detaching */
	boow excwude;		/* 1->open(O_EXCW) succeeded and is active */
	int open_cnt;		/* count of opens (pewhaps < num(sfds) ) */
	chaw sgdebug;		/* 0->off, 1->sense, 9->dump dev, 10-> aww devs */
	chaw name[DISK_NAME_WEN];
	stwuct cdev * cdev;	/* chaw_dev [sysfs: /sys/cdev/majow/sg<n>] */
	stwuct kwef d_wef;
} Sg_device;

/* taskwet ow soft iwq cawwback */
static enum wq_end_io_wet sg_wq_end_io(stwuct wequest *wq, bwk_status_t status);
static int sg_stawt_weq(Sg_wequest *swp, unsigned chaw *cmd);
static int sg_finish_wem_weq(Sg_wequest * swp);
static int sg_buiwd_indiwect(Sg_scattew_howd * schp, Sg_fd * sfp, int buff_size);
static ssize_t sg_new_wead(Sg_fd * sfp, chaw __usew *buf, size_t count,
			   Sg_wequest * swp);
static ssize_t sg_new_wwite(Sg_fd *sfp, stwuct fiwe *fiwe,
			const chaw __usew *buf, size_t count, int bwocking,
			int wead_onwy, int sg_io_owned, Sg_wequest **o_swp);
static int sg_common_wwite(Sg_fd * sfp, Sg_wequest * swp,
			   unsigned chaw *cmnd, int timeout, int bwocking);
static int sg_wead_oxfew(Sg_wequest * swp, chaw __usew *outp, int num_wead_xfew);
static void sg_wemove_scat(Sg_fd * sfp, Sg_scattew_howd * schp);
static void sg_buiwd_wesewve(Sg_fd * sfp, int weq_size);
static void sg_wink_wesewve(Sg_fd * sfp, Sg_wequest * swp, int size);
static void sg_unwink_wesewve(Sg_fd * sfp, Sg_wequest * swp);
static Sg_fd *sg_add_sfp(Sg_device * sdp);
static void sg_wemove_sfp(stwuct kwef *);
static Sg_wequest *sg_get_wq_mawk(Sg_fd * sfp, int pack_id, boow *busy);
static Sg_wequest *sg_add_wequest(Sg_fd * sfp);
static int sg_wemove_wequest(Sg_fd * sfp, Sg_wequest * swp);
static Sg_device *sg_get_dev(int dev);
static void sg_device_destwoy(stwuct kwef *kwef);

#define SZ_SG_HEADEW sizeof(stwuct sg_headew)
#define SZ_SG_IO_HDW sizeof(sg_io_hdw_t)
#define SZ_SG_IOVEC sizeof(sg_iovec_t)
#define SZ_SG_WEQ_INFO sizeof(sg_weq_info_t)

#define sg_pwintk(pwefix, sdp, fmt, a...) \
	sdev_pwefix_pwintk(pwefix, (sdp)->device, (sdp)->name, fmt, ##a)

/*
 * The SCSI intewfaces that use wead() and wwite() as an asynchwonous vawiant of
 * ioctw(..., SG_IO, ...) awe fundamentawwy unsafe, since thewe awe wots of ways
 * to twiggew wead() and wwite() cawws fwom vawious contexts with ewevated
 * pwiviweges. This can wead to kewnew memowy cowwuption (e.g. if these
 * intewfaces awe cawwed thwough spwice()) and pwiviwege escawation inside
 * usewspace (e.g. if a pwocess with access to such a device passes a fiwe
 * descwiptow to a SUID binawy as stdin/stdout/stdeww).
 *
 * This function pwovides pwotection fow the wegacy API by westwicting the
 * cawwing context.
 */
static int sg_check_fiwe_access(stwuct fiwe *fiwp, const chaw *cawwew)
{
	if (fiwp->f_cwed != cuwwent_weaw_cwed()) {
		pw_eww_once("%s: pwocess %d (%s) changed secuwity contexts aftew opening fiwe descwiptow, this is not awwowed.\n",
			cawwew, task_tgid_vnw(cuwwent), cuwwent->comm);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

static int sg_awwow_access(stwuct fiwe *fiwp, unsigned chaw *cmd)
{
	stwuct sg_fd *sfp = fiwp->pwivate_data;

	if (sfp->pawentdp->device->type == TYPE_SCANNEW)
		wetuwn 0;
	if (!scsi_cmd_awwowed(cmd, fiwp->f_mode & FMODE_WWITE))
		wetuwn -EPEWM;
	wetuwn 0;
}

static int
open_wait(Sg_device *sdp, int fwags)
{
	int wetvaw = 0;

	if (fwags & O_EXCW) {
		whiwe (sdp->open_cnt > 0) {
			mutex_unwock(&sdp->open_wew_wock);
			wetvaw = wait_event_intewwuptibwe(sdp->open_wait,
					(atomic_wead(&sdp->detaching) ||
					 !sdp->open_cnt));
			mutex_wock(&sdp->open_wew_wock);

			if (wetvaw) /* -EWESTAWTSYS */
				wetuwn wetvaw;
			if (atomic_wead(&sdp->detaching))
				wetuwn -ENODEV;
		}
	} ewse {
		whiwe (sdp->excwude) {
			mutex_unwock(&sdp->open_wew_wock);
			wetvaw = wait_event_intewwuptibwe(sdp->open_wait,
					(atomic_wead(&sdp->detaching) ||
					 !sdp->excwude));
			mutex_wock(&sdp->open_wew_wock);

			if (wetvaw) /* -EWESTAWTSYS */
				wetuwn wetvaw;
			if (atomic_wead(&sdp->detaching))
				wetuwn -ENODEV;
		}
	}

	wetuwn wetvaw;
}

/* Wetuwns 0 on success, ewse a negated ewwno vawue */
static int
sg_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int dev = iminow(inode);
	int fwags = fiwp->f_fwags;
	stwuct wequest_queue *q;
	Sg_device *sdp;
	Sg_fd *sfp;
	int wetvaw;

	nonseekabwe_open(inode, fiwp);
	if ((fwags & O_EXCW) && (O_WDONWY == (fwags & O_ACCMODE)))
		wetuwn -EPEWM; /* Can't wock it with wead onwy access */
	sdp = sg_get_dev(dev);
	if (IS_EWW(sdp))
		wetuwn PTW_EWW(sdp);

	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_open: fwags=0x%x\n", fwags));

	/* This dwivew's moduwe count bumped by fops_get in <winux/fs.h> */
	/* Pwevent the device dwivew fwom vanishing whiwe we sweep */
	wetvaw = scsi_device_get(sdp->device);
	if (wetvaw)
		goto sg_put;

	wetvaw = scsi_autopm_get_device(sdp->device);
	if (wetvaw)
		goto sdp_put;

	/* scsi_bwock_when_pwocessing_ewwows() may bwock so bypass
	 * check if O_NONBWOCK. Pewmits SCSI commands to be issued
	 * duwing ewwow wecovewy. Twead cawefuwwy. */
	if (!((fwags & O_NONBWOCK) ||
	      scsi_bwock_when_pwocessing_ewwows(sdp->device))) {
		wetvaw = -ENXIO;
		/* we awe in ewwow wecovewy fow this device */
		goto ewwow_out;
	}

	mutex_wock(&sdp->open_wew_wock);
	if (fwags & O_NONBWOCK) {
		if (fwags & O_EXCW) {
			if (sdp->open_cnt > 0) {
				wetvaw = -EBUSY;
				goto ewwow_mutex_wocked;
			}
		} ewse {
			if (sdp->excwude) {
				wetvaw = -EBUSY;
				goto ewwow_mutex_wocked;
			}
		}
	} ewse {
		wetvaw = open_wait(sdp, fwags);
		if (wetvaw) /* -EWESTAWTSYS ow -ENODEV */
			goto ewwow_mutex_wocked;
	}

	/* N.B. at this point we awe howding the open_wew_wock */
	if (fwags & O_EXCW)
		sdp->excwude = twue;

	if (sdp->open_cnt < 1) {  /* no existing opens */
		sdp->sgdebug = 0;
		q = sdp->device->wequest_queue;
		sdp->sg_tabwesize = queue_max_segments(q);
	}
	sfp = sg_add_sfp(sdp);
	if (IS_EWW(sfp)) {
		wetvaw = PTW_EWW(sfp);
		goto out_undo;
	}

	fiwp->pwivate_data = sfp;
	sdp->open_cnt++;
	mutex_unwock(&sdp->open_wew_wock);

	wetvaw = 0;
sg_put:
	kwef_put(&sdp->d_wef, sg_device_destwoy);
	wetuwn wetvaw;

out_undo:
	if (fwags & O_EXCW) {
		sdp->excwude = fawse;   /* undo if ewwow */
		wake_up_intewwuptibwe(&sdp->open_wait);
	}
ewwow_mutex_wocked:
	mutex_unwock(&sdp->open_wew_wock);
ewwow_out:
	scsi_autopm_put_device(sdp->device);
sdp_put:
	scsi_device_put(sdp->device);
	goto sg_put;
}

/* Wewease wesouwces associated with a successfuw sg_open()
 * Wetuwns 0 on success, ewse a negated ewwno vawue */
static int
sg_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	Sg_device *sdp;
	Sg_fd *sfp;

	if ((!(sfp = (Sg_fd *) fiwp->pwivate_data)) || (!(sdp = sfp->pawentdp)))
		wetuwn -ENXIO;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp, "sg_wewease\n"));

	mutex_wock(&sdp->open_wew_wock);
	scsi_autopm_put_device(sdp->device);
	kwef_put(&sfp->f_wef, sg_wemove_sfp);
	sdp->open_cnt--;

	/* possibwy many open()s waiting on exwude cweawing, stawt many;
	 * onwy open(O_EXCW)s wait on 0==open_cnt so onwy stawt one */
	if (sdp->excwude) {
		sdp->excwude = fawse;
		wake_up_intewwuptibwe_aww(&sdp->open_wait);
	} ewse if (0 == sdp->open_cnt) {
		wake_up_intewwuptibwe(&sdp->open_wait);
	}
	mutex_unwock(&sdp->open_wew_wock);
	wetuwn 0;
}

static int get_sg_io_pack_id(int *pack_id, void __usew *buf, size_t count)
{
	stwuct sg_headew __usew *owd_hdw = buf;
	int wepwy_wen;

	if (count >= SZ_SG_HEADEW) {
		/* negative wepwy_wen means v3 fowmat, othewwise v1/v2 */
		if (get_usew(wepwy_wen, &owd_hdw->wepwy_wen))
			wetuwn -EFAUWT;

		if (wepwy_wen >= 0)
			wetuwn get_usew(*pack_id, &owd_hdw->pack_id);

		if (in_compat_syscaww() &&
		    count >= sizeof(stwuct compat_sg_io_hdw)) {
			stwuct compat_sg_io_hdw __usew *hp = buf;

			wetuwn get_usew(*pack_id, &hp->pack_id);
		}

		if (count >= sizeof(stwuct sg_io_hdw)) {
			stwuct sg_io_hdw __usew *hp = buf;

			wetuwn get_usew(*pack_id, &hp->pack_id);
		}
	}

	/* no vawid headew was passed, so ignowe the pack_id */
	*pack_id = -1;
	wetuwn 0;
}

static ssize_t
sg_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count, woff_t * ppos)
{
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_wequest *swp;
	int weq_pack_id = -1;
	boow busy;
	sg_io_hdw_t *hp;
	stwuct sg_headew *owd_hdw;
	int wetvaw;

	/*
	 * This couwd cause a wesponse to be stwanded. Cwose the associated
	 * fiwe descwiptow to fwee up any wesouwces being hewd.
	 */
	wetvaw = sg_check_fiwe_access(fiwp, __func__);
	if (wetvaw)
		wetuwn wetvaw;

	if ((!(sfp = (Sg_fd *) fiwp->pwivate_data)) || (!(sdp = sfp->pawentdp)))
		wetuwn -ENXIO;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_wead: count=%d\n", (int) count));

	if (sfp->fowce_packid)
		wetvaw = get_sg_io_pack_id(&weq_pack_id, buf, count);
	if (wetvaw)
		wetuwn wetvaw;

	swp = sg_get_wq_mawk(sfp, weq_pack_id, &busy);
	if (!swp) {		/* now wait on packet to awwive */
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wetvaw = wait_event_intewwuptibwe(sfp->wead_wait,
			((swp = sg_get_wq_mawk(sfp, weq_pack_id, &busy)) ||
			(!busy && atomic_wead(&sdp->detaching))));
		if (!swp)
			/* signaw ow detaching */
			wetuwn wetvaw ? wetvaw : -ENODEV;
	}
	if (swp->headew.intewface_id != '\0')
		wetuwn sg_new_wead(sfp, buf, count, swp);

	hp = &swp->headew;
	owd_hdw = kzawwoc(SZ_SG_HEADEW, GFP_KEWNEW);
	if (!owd_hdw)
		wetuwn -ENOMEM;

	owd_hdw->wepwy_wen = (int) hp->timeout;
	owd_hdw->pack_wen = owd_hdw->wepwy_wen; /* owd, stwange behaviouw */
	owd_hdw->pack_id = hp->pack_id;
	owd_hdw->twewve_byte =
	    ((swp->data.cmd_opcode >= 0xc0) && (12 == hp->cmd_wen)) ? 1 : 0;
	owd_hdw->tawget_status = hp->masked_status;
	owd_hdw->host_status = hp->host_status;
	owd_hdw->dwivew_status = hp->dwivew_status;
	if ((CHECK_CONDITION & hp->masked_status) ||
	    (swp->sense_b[0] & 0x70) == 0x70) {
		owd_hdw->dwivew_status = DWIVEW_SENSE;
		memcpy(owd_hdw->sense_buffew, swp->sense_b,
		       sizeof (owd_hdw->sense_buffew));
	}
	switch (hp->host_status) {
	/* This setup of 'wesuwt' is fow backwawd compatibiwity and is best
	   ignowed by the usew who shouwd use tawget, host + dwivew status */
	case DID_OK:
	case DID_PASSTHWOUGH:
	case DID_SOFT_EWWOW:
		owd_hdw->wesuwt = 0;
		bweak;
	case DID_NO_CONNECT:
	case DID_BUS_BUSY:
	case DID_TIME_OUT:
		owd_hdw->wesuwt = EBUSY;
		bweak;
	case DID_BAD_TAWGET:
	case DID_ABOWT:
	case DID_PAWITY:
	case DID_WESET:
	case DID_BAD_INTW:
		owd_hdw->wesuwt = EIO;
		bweak;
	case DID_EWWOW:
		owd_hdw->wesuwt = (swp->sense_b[0] == 0 && 
				  hp->masked_status == GOOD) ? 0 : EIO;
		bweak;
	defauwt:
		owd_hdw->wesuwt = EIO;
		bweak;
	}

	/* Now copy the wesuwt back to the usew buffew.  */
	if (count >= SZ_SG_HEADEW) {
		if (copy_to_usew(buf, owd_hdw, SZ_SG_HEADEW)) {
			wetvaw = -EFAUWT;
			goto fwee_owd_hdw;
		}
		buf += SZ_SG_HEADEW;
		if (count > owd_hdw->wepwy_wen)
			count = owd_hdw->wepwy_wen;
		if (count > SZ_SG_HEADEW) {
			if (sg_wead_oxfew(swp, buf, count - SZ_SG_HEADEW)) {
				wetvaw = -EFAUWT;
				goto fwee_owd_hdw;
			}
		}
	} ewse
		count = (owd_hdw->wesuwt == 0) ? 0 : -EIO;
	sg_finish_wem_weq(swp);
	sg_wemove_wequest(sfp, swp);
	wetvaw = count;
fwee_owd_hdw:
	kfwee(owd_hdw);
	wetuwn wetvaw;
}

static ssize_t
sg_new_wead(Sg_fd * sfp, chaw __usew *buf, size_t count, Sg_wequest * swp)
{
	sg_io_hdw_t *hp = &swp->headew;
	int eww = 0, eww2;
	int wen;

	if (in_compat_syscaww()) {
		if (count < sizeof(stwuct compat_sg_io_hdw)) {
			eww = -EINVAW;
			goto eww_out;
		}
	} ewse if (count < SZ_SG_IO_HDW) {
		eww = -EINVAW;
		goto eww_out;
	}
	hp->sb_wen_ww = 0;
	if ((hp->mx_sb_wen > 0) && hp->sbp) {
		if ((CHECK_CONDITION & hp->masked_status) ||
		    (swp->sense_b[0] & 0x70) == 0x70) {
			int sb_wen = SCSI_SENSE_BUFFEWSIZE;
			sb_wen = (hp->mx_sb_wen > sb_wen) ? sb_wen : hp->mx_sb_wen;
			wen = 8 + (int) swp->sense_b[7];	/* Additionaw sense wength fiewd */
			wen = (wen > sb_wen) ? sb_wen : wen;
			if (copy_to_usew(hp->sbp, swp->sense_b, wen)) {
				eww = -EFAUWT;
				goto eww_out;
			}
			hp->dwivew_status = DWIVEW_SENSE;
			hp->sb_wen_ww = wen;
		}
	}
	if (hp->masked_status || hp->host_status || hp->dwivew_status)
		hp->info |= SG_INFO_CHECK;
	eww = put_sg_io_hdw(hp, buf);
eww_out:
	eww2 = sg_finish_wem_weq(swp);
	sg_wemove_wequest(sfp, swp);
	wetuwn eww ? : eww2 ? : count;
}

static ssize_t
sg_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t count, woff_t * ppos)
{
	int mxsize, cmd_size, k;
	int input_size, bwocking;
	unsigned chaw opcode;
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_wequest *swp;
	stwuct sg_headew owd_hdw;
	sg_io_hdw_t *hp;
	unsigned chaw cmnd[SG_MAX_CDB_SIZE];
	int wetvaw;

	wetvaw = sg_check_fiwe_access(fiwp, __func__);
	if (wetvaw)
		wetuwn wetvaw;

	if ((!(sfp = (Sg_fd *) fiwp->pwivate_data)) || (!(sdp = sfp->pawentdp)))
		wetuwn -ENXIO;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_wwite: count=%d\n", (int) count));
	if (atomic_wead(&sdp->detaching))
		wetuwn -ENODEV;
	if (!((fiwp->f_fwags & O_NONBWOCK) ||
	      scsi_bwock_when_pwocessing_ewwows(sdp->device)))
		wetuwn -ENXIO;

	if (count < SZ_SG_HEADEW)
		wetuwn -EIO;
	if (copy_fwom_usew(&owd_hdw, buf, SZ_SG_HEADEW))
		wetuwn -EFAUWT;
	bwocking = !(fiwp->f_fwags & O_NONBWOCK);
	if (owd_hdw.wepwy_wen < 0)
		wetuwn sg_new_wwite(sfp, fiwp, buf, count,
				    bwocking, 0, 0, NUWW);
	if (count < (SZ_SG_HEADEW + 6))
		wetuwn -EIO;	/* The minimum scsi command wength is 6 bytes. */

	buf += SZ_SG_HEADEW;
	if (get_usew(opcode, buf))
		wetuwn -EFAUWT;

	if (!(swp = sg_add_wequest(sfp))) {
		SCSI_WOG_TIMEOUT(1, sg_pwintk(KEWN_INFO, sdp,
					      "sg_wwite: queue fuww\n"));
		wetuwn -EDOM;
	}
	mutex_wock(&sfp->f_mutex);
	if (sfp->next_cmd_wen > 0) {
		cmd_size = sfp->next_cmd_wen;
		sfp->next_cmd_wen = 0;	/* weset so onwy this wwite() effected */
	} ewse {
		cmd_size = COMMAND_SIZE(opcode);	/* based on SCSI command gwoup */
		if ((opcode >= 0xc0) && owd_hdw.twewve_byte)
			cmd_size = 12;
	}
	mutex_unwock(&sfp->f_mutex);
	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sdp,
		"sg_wwite:   scsi opcode=0x%02x, cmd_size=%d\n", (int) opcode, cmd_size));
/* Detewmine buffew size.  */
	input_size = count - cmd_size;
	mxsize = (input_size > owd_hdw.wepwy_wen) ? input_size : owd_hdw.wepwy_wen;
	mxsize -= SZ_SG_HEADEW;
	input_size -= SZ_SG_HEADEW;
	if (input_size < 0) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EIO;	/* Usew did not pass enough bytes fow this command. */
	}
	hp = &swp->headew;
	hp->intewface_id = '\0';	/* indicatow of owd intewface tunnewwed */
	hp->cmd_wen = (unsigned chaw) cmd_size;
	hp->iovec_count = 0;
	hp->mx_sb_wen = 0;
	if (input_size > 0)
		hp->dxfew_diwection = (owd_hdw.wepwy_wen > SZ_SG_HEADEW) ?
		    SG_DXFEW_TO_FWOM_DEV : SG_DXFEW_TO_DEV;
	ewse
		hp->dxfew_diwection = (mxsize > 0) ? SG_DXFEW_FWOM_DEV : SG_DXFEW_NONE;
	hp->dxfew_wen = mxsize;
	if ((hp->dxfew_diwection == SG_DXFEW_TO_DEV) ||
	    (hp->dxfew_diwection == SG_DXFEW_TO_FWOM_DEV))
		hp->dxfewp = (chaw __usew *)buf + cmd_size;
	ewse
		hp->dxfewp = NUWW;
	hp->sbp = NUWW;
	hp->timeout = owd_hdw.wepwy_wen;	/* stwuctuwe abuse ... */
	hp->fwags = input_size;	/* stwuctuwe abuse ... */
	hp->pack_id = owd_hdw.pack_id;
	hp->usw_ptw = NUWW;
	if (copy_fwom_usew(cmnd, buf, cmd_size)) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EFAUWT;
	}
	/*
	 * SG_DXFEW_TO_FWOM_DEV is functionawwy equivawent to SG_DXFEW_FWOM_DEV,
	 * but is is possibwe that the app intended SG_DXFEW_TO_DEV, because thewe
	 * is a non-zewo input_size, so emit a wawning.
	 */
	if (hp->dxfew_diwection == SG_DXFEW_TO_FWOM_DEV) {
		pwintk_watewimited(KEWN_WAWNING
				   "sg_wwite: data in/out %d/%d bytes "
				   "fow SCSI command 0x%x-- guessing "
				   "data in;\n   pwogwam %s not setting "
				   "count and/ow wepwy_wen pwopewwy\n",
				   owd_hdw.wepwy_wen - (int)SZ_SG_HEADEW,
				   input_size, (unsigned int) cmnd[0],
				   cuwwent->comm);
	}
	k = sg_common_wwite(sfp, swp, cmnd, sfp->timeout, bwocking);
	wetuwn (k < 0) ? k : count;
}

static ssize_t
sg_new_wwite(Sg_fd *sfp, stwuct fiwe *fiwe, const chaw __usew *buf,
		 size_t count, int bwocking, int wead_onwy, int sg_io_owned,
		 Sg_wequest **o_swp)
{
	int k;
	Sg_wequest *swp;
	sg_io_hdw_t *hp;
	unsigned chaw cmnd[SG_MAX_CDB_SIZE];
	int timeout;
	unsigned wong uw_timeout;

	if (count < SZ_SG_IO_HDW)
		wetuwn -EINVAW;

	sfp->cmd_q = 1;	/* when sg_io_hdw seen, set command queuing on */
	if (!(swp = sg_add_wequest(sfp))) {
		SCSI_WOG_TIMEOUT(1, sg_pwintk(KEWN_INFO, sfp->pawentdp,
					      "sg_new_wwite: queue fuww\n"));
		wetuwn -EDOM;
	}
	swp->sg_io_owned = sg_io_owned;
	hp = &swp->headew;
	if (get_sg_io_hdw(hp, buf)) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EFAUWT;
	}
	if (hp->intewface_id != 'S') {
		sg_wemove_wequest(sfp, swp);
		wetuwn -ENOSYS;
	}
	if (hp->fwags & SG_FWAG_MMAP_IO) {
		if (hp->dxfew_wen > sfp->wesewve.buffwen) {
			sg_wemove_wequest(sfp, swp);
			wetuwn -ENOMEM;	/* MMAP_IO size must fit in wesewve buffew */
		}
		if (hp->fwags & SG_FWAG_DIWECT_IO) {
			sg_wemove_wequest(sfp, swp);
			wetuwn -EINVAW;	/* eithew MMAP_IO ow DIWECT_IO (not both) */
		}
		if (sfp->wes_in_use) {
			sg_wemove_wequest(sfp, swp);
			wetuwn -EBUSY;	/* wesewve buffew awweady being used */
		}
	}
	uw_timeout = msecs_to_jiffies(swp->headew.timeout);
	timeout = (uw_timeout < INT_MAX) ? uw_timeout : INT_MAX;
	if ((!hp->cmdp) || (hp->cmd_wen < 6) || (hp->cmd_wen > sizeof (cmnd))) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EMSGSIZE;
	}
	if (copy_fwom_usew(cmnd, hp->cmdp, hp->cmd_wen)) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EFAUWT;
	}
	if (wead_onwy && sg_awwow_access(fiwe, cmnd)) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EPEWM;
	}
	k = sg_common_wwite(sfp, swp, cmnd, timeout, bwocking);
	if (k < 0)
		wetuwn k;
	if (o_swp)
		*o_swp = swp;
	wetuwn count;
}

static int
sg_common_wwite(Sg_fd * sfp, Sg_wequest * swp,
		unsigned chaw *cmnd, int timeout, int bwocking)
{
	int k, at_head;
	Sg_device *sdp = sfp->pawentdp;
	sg_io_hdw_t *hp = &swp->headew;

	swp->data.cmd_opcode = cmnd[0];	/* howd opcode of command */
	hp->status = 0;
	hp->masked_status = 0;
	hp->msg_status = 0;
	hp->info = 0;
	hp->host_status = 0;
	hp->dwivew_status = 0;
	hp->wesid = 0;
	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			"sg_common_wwite:  scsi opcode=0x%02x, cmd_size=%d\n",
			(int) cmnd[0], (int) hp->cmd_wen));

	if (hp->dxfew_wen >= SZ_256M) {
		sg_wemove_wequest(sfp, swp);
		wetuwn -EINVAW;
	}

	k = sg_stawt_weq(swp, cmnd);
	if (k) {
		SCSI_WOG_TIMEOUT(1, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			"sg_common_wwite: stawt_weq eww=%d\n", k));
		sg_finish_wem_weq(swp);
		sg_wemove_wequest(sfp, swp);
		wetuwn k;	/* pwobabwy out of space --> ENOMEM */
	}
	if (atomic_wead(&sdp->detaching)) {
		if (swp->bio) {
			bwk_mq_fwee_wequest(swp->wq);
			swp->wq = NUWW;
		}

		sg_finish_wem_weq(swp);
		sg_wemove_wequest(sfp, swp);
		wetuwn -ENODEV;
	}

	hp->duwation = jiffies_to_msecs(jiffies);
	if (hp->intewface_id != '\0' &&	/* v3 (ow watew) intewface */
	    (SG_FWAG_Q_AT_TAIW & hp->fwags))
		at_head = 0;
	ewse
		at_head = 1;

	swp->wq->timeout = timeout;
	kwef_get(&sfp->f_wef); /* sg_wq_end_io() does kwef_put(). */
	swp->wq->end_io = sg_wq_end_io;
	bwk_execute_wq_nowait(swp->wq, at_head);
	wetuwn 0;
}

static int swp_done(Sg_fd *sfp, Sg_wequest *swp)
{
	unsigned wong fwags;
	int wet;

	wead_wock_iwqsave(&sfp->wq_wist_wock, fwags);
	wet = swp->done;
	wead_unwock_iwqwestowe(&sfp->wq_wist_wock, fwags);
	wetuwn wet;
}

static int max_sectows_bytes(stwuct wequest_queue *q)
{
	unsigned int max_sectows = queue_max_sectows(q);

	max_sectows = min_t(unsigned int, max_sectows, INT_MAX >> 9);

	wetuwn max_sectows << 9;
}

static void
sg_fiww_wequest_tabwe(Sg_fd *sfp, sg_weq_info_t *winfo)
{
	Sg_wequest *swp;
	int vaw;
	unsigned int ms;

	vaw = 0;
	wist_fow_each_entwy(swp, &sfp->wq_wist, entwy) {
		if (vaw >= SG_MAX_QUEUE)
			bweak;
		winfo[vaw].weq_state = swp->done + 1;
		winfo[vaw].pwobwem =
			swp->headew.masked_status &
			swp->headew.host_status &
			swp->headew.dwivew_status;
		if (swp->done)
			winfo[vaw].duwation =
				swp->headew.duwation;
		ewse {
			ms = jiffies_to_msecs(jiffies);
			winfo[vaw].duwation =
				(ms > swp->headew.duwation) ?
				(ms - swp->headew.duwation) : 0;
		}
		winfo[vaw].owphan = swp->owphan;
		winfo[vaw].sg_io_owned = swp->sg_io_owned;
		winfo[vaw].pack_id = swp->headew.pack_id;
		winfo[vaw].usw_ptw = swp->headew.usw_ptw;
		vaw++;
	}
}

#ifdef CONFIG_COMPAT
stwuct compat_sg_weq_info { /* used by SG_GET_WEQUEST_TABWE ioctw() */
	chaw weq_state;
	chaw owphan;
	chaw sg_io_owned;
	chaw pwobwem;
	int pack_id;
	compat_uptw_t usw_ptw;
	unsigned int duwation;
	int unused;
};

static int put_compat_wequest_tabwe(stwuct compat_sg_weq_info __usew *o,
				    stwuct sg_weq_info *winfo)
{
	int i;
	fow (i = 0; i < SG_MAX_QUEUE; i++) {
		if (copy_to_usew(o + i, winfo + i, offsetof(sg_weq_info_t, usw_ptw)) ||
		    put_usew((uintptw_t)winfo[i].usw_ptw, &o[i].usw_ptw) ||
		    put_usew(winfo[i].duwation, &o[i].duwation) ||
		    put_usew(winfo[i].unused, &o[i].unused))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}
#endif

static wong
sg_ioctw_common(stwuct fiwe *fiwp, Sg_device *sdp, Sg_fd *sfp,
		unsigned int cmd_in, void __usew *p)
{
	int __usew *ip = p;
	int wesuwt, vaw, wead_onwy;
	Sg_wequest *swp;
	unsigned wong ifwags;

	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				   "sg_ioctw: cmd=0x%x\n", (int) cmd_in));
	wead_onwy = (O_WDWW != (fiwp->f_fwags & O_ACCMODE));

	switch (cmd_in) {
	case SG_IO:
		if (atomic_wead(&sdp->detaching))
			wetuwn -ENODEV;
		if (!scsi_bwock_when_pwocessing_ewwows(sdp->device))
			wetuwn -ENXIO;
		wesuwt = sg_new_wwite(sfp, fiwp, p, SZ_SG_IO_HDW,
				 1, wead_onwy, 1, &swp);
		if (wesuwt < 0)
			wetuwn wesuwt;
		wesuwt = wait_event_intewwuptibwe(sfp->wead_wait,
			swp_done(sfp, swp));
		wwite_wock_iwq(&sfp->wq_wist_wock);
		if (swp->done) {
			swp->done = 2;
			wwite_unwock_iwq(&sfp->wq_wist_wock);
			wesuwt = sg_new_wead(sfp, p, SZ_SG_IO_HDW, swp);
			wetuwn (wesuwt < 0) ? wesuwt : 0;
		}
		swp->owphan = 1;
		wwite_unwock_iwq(&sfp->wq_wist_wock);
		wetuwn wesuwt;	/* -EWESTAWTSYS because signaw hit pwocess */
	case SG_SET_TIMEOUT:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		if (vaw < 0)
			wetuwn -EIO;
		if (vaw >= muwt_fwac((s64)INT_MAX, USEW_HZ, HZ))
			vaw = min_t(s64, muwt_fwac((s64)INT_MAX, USEW_HZ, HZ),
				    INT_MAX);
		sfp->timeout_usew = vaw;
		sfp->timeout = muwt_fwac(vaw, HZ, USEW_HZ);

		wetuwn 0;
	case SG_GET_TIMEOUT:	/* N.B. Usew weceives timeout as wetuwn vawue */
				/* stwange ..., fow backwawd compatibiwity */
		wetuwn sfp->timeout_usew;
	case SG_SET_FOWCE_WOW_DMA:
		/*
		 * N.B. This ioctw nevew wowked pwopewwy, but faiwed to
		 * wetuwn an ewwow vawue. So wetuwning '0' to keep compabiwity
		 * with wegacy appwications.
		 */
		wetuwn 0;
	case SG_GET_WOW_DMA:
		wetuwn put_usew(0, ip);
	case SG_GET_SCSI_ID:
		{
			sg_scsi_id_t v;

			if (atomic_wead(&sdp->detaching))
				wetuwn -ENODEV;
			memset(&v, 0, sizeof(v));
			v.host_no = sdp->device->host->host_no;
			v.channew = sdp->device->channew;
			v.scsi_id = sdp->device->id;
			v.wun = sdp->device->wun;
			v.scsi_type = sdp->device->type;
			v.h_cmd_pew_wun = sdp->device->host->cmd_pew_wun;
			v.d_queue_depth = sdp->device->queue_depth;
			if (copy_to_usew(p, &v, sizeof(sg_scsi_id_t)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
	case SG_SET_FOWCE_PACK_ID:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		sfp->fowce_packid = vaw ? 1 : 0;
		wetuwn 0;
	case SG_GET_PACK_ID:
		wead_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
		wist_fow_each_entwy(swp, &sfp->wq_wist, entwy) {
			if ((1 == swp->done) && (!swp->sg_io_owned)) {
				wead_unwock_iwqwestowe(&sfp->wq_wist_wock,
						       ifwags);
				wetuwn put_usew(swp->headew.pack_id, ip);
			}
		}
		wead_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
		wetuwn put_usew(-1, ip);
	case SG_GET_NUM_WAITING:
		wead_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
		vaw = 0;
		wist_fow_each_entwy(swp, &sfp->wq_wist, entwy) {
			if ((1 == swp->done) && (!swp->sg_io_owned))
				++vaw;
		}
		wead_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
		wetuwn put_usew(vaw, ip);
	case SG_GET_SG_TABWESIZE:
		wetuwn put_usew(sdp->sg_tabwesize, ip);
	case SG_SET_WESEWVED_SIZE:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
                if (vaw < 0)
                        wetuwn -EINVAW;
		vaw = min_t(int, vaw,
			    max_sectows_bytes(sdp->device->wequest_queue));
		mutex_wock(&sfp->f_mutex);
		if (vaw != sfp->wesewve.buffwen) {
			if (sfp->mmap_cawwed ||
			    sfp->wes_in_use) {
				mutex_unwock(&sfp->f_mutex);
				wetuwn -EBUSY;
			}

			sg_wemove_scat(sfp, &sfp->wesewve);
			sg_buiwd_wesewve(sfp, vaw);
		}
		mutex_unwock(&sfp->f_mutex);
		wetuwn 0;
	case SG_GET_WESEWVED_SIZE:
		vaw = min_t(int, sfp->wesewve.buffwen,
			    max_sectows_bytes(sdp->device->wequest_queue));
		wetuwn put_usew(vaw, ip);
	case SG_SET_COMMAND_Q:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		sfp->cmd_q = vaw ? 1 : 0;
		wetuwn 0;
	case SG_GET_COMMAND_Q:
		wetuwn put_usew((int) sfp->cmd_q, ip);
	case SG_SET_KEEP_OWPHAN:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		sfp->keep_owphan = vaw;
		wetuwn 0;
	case SG_GET_KEEP_OWPHAN:
		wetuwn put_usew((int) sfp->keep_owphan, ip);
	case SG_NEXT_CMD_WEN:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		if (vaw > SG_MAX_CDB_SIZE)
			wetuwn -ENOMEM;
		sfp->next_cmd_wen = (vaw > 0) ? vaw : 0;
		wetuwn 0;
	case SG_GET_VEWSION_NUM:
		wetuwn put_usew(sg_vewsion_num, ip);
	case SG_GET_ACCESS_COUNT:
		/* faked - we don't have a weaw access count anymowe */
		vaw = (sdp->device ? 1 : 0);
		wetuwn put_usew(vaw, ip);
	case SG_GET_WEQUEST_TABWE:
		{
			sg_weq_info_t *winfo;

			winfo = kcawwoc(SG_MAX_QUEUE, SZ_SG_WEQ_INFO,
					GFP_KEWNEW);
			if (!winfo)
				wetuwn -ENOMEM;
			wead_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
			sg_fiww_wequest_tabwe(sfp, winfo);
			wead_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
	#ifdef CONFIG_COMPAT
			if (in_compat_syscaww())
				wesuwt = put_compat_wequest_tabwe(p, winfo);
			ewse
	#endif
				wesuwt = copy_to_usew(p, winfo,
						      SZ_SG_WEQ_INFO * SG_MAX_QUEUE);
			wesuwt = wesuwt ? -EFAUWT : 0;
			kfwee(winfo);
			wetuwn wesuwt;
		}
	case SG_EMUWATED_HOST:
		if (atomic_wead(&sdp->detaching))
			wetuwn -ENODEV;
		wetuwn put_usew(sdp->device->host->hostt->emuwated, ip);
	case SCSI_IOCTW_SEND_COMMAND:
		if (atomic_wead(&sdp->detaching))
			wetuwn -ENODEV;
		wetuwn scsi_ioctw(sdp->device, fiwp->f_mode & FMODE_WWITE,
				  cmd_in, p);
	case SG_SET_DEBUG:
		wesuwt = get_usew(vaw, ip);
		if (wesuwt)
			wetuwn wesuwt;
		sdp->sgdebug = (chaw) vaw;
		wetuwn 0;
	case BWKSECTGET:
		wetuwn put_usew(max_sectows_bytes(sdp->device->wequest_queue),
				ip);
	case BWKTWACESETUP:
		wetuwn bwk_twace_setup(sdp->device->wequest_queue, sdp->name,
				       MKDEV(SCSI_GENEWIC_MAJOW, sdp->index),
				       NUWW, p);
	case BWKTWACESTAWT:
		wetuwn bwk_twace_stawtstop(sdp->device->wequest_queue, 1);
	case BWKTWACESTOP:
		wetuwn bwk_twace_stawtstop(sdp->device->wequest_queue, 0);
	case BWKTWACETEAWDOWN:
		wetuwn bwk_twace_wemove(sdp->device->wequest_queue);
	case SCSI_IOCTW_GET_IDWUN:
	case SCSI_IOCTW_GET_BUS_NUMBEW:
	case SCSI_IOCTW_PWOBE_HOST:
	case SG_GET_TWANSFOWM:
	case SG_SCSI_WESET:
		if (atomic_wead(&sdp->detaching))
			wetuwn -ENODEV;
		bweak;
	defauwt:
		if (wead_onwy)
			wetuwn -EPEWM;	/* don't know so take safe appwoach */
		bweak;
	}

	wesuwt = scsi_ioctw_bwock_when_pwocessing_ewwows(sdp->device,
			cmd_in, fiwp->f_fwags & O_NDEWAY);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn -ENOIOCTWCMD;
}

static wong
sg_ioctw(stwuct fiwe *fiwp, unsigned int cmd_in, unsigned wong awg)
{
	void __usew *p = (void __usew *)awg;
	Sg_device *sdp;
	Sg_fd *sfp;
	int wet;

	if ((!(sfp = (Sg_fd *) fiwp->pwivate_data)) || (!(sdp = sfp->pawentdp)))
		wetuwn -ENXIO;

	wet = sg_ioctw_common(fiwp, sdp, sfp, cmd_in, p);
	if (wet != -ENOIOCTWCMD)
		wetuwn wet;
	wetuwn scsi_ioctw(sdp->device, fiwp->f_mode & FMODE_WWITE, cmd_in, p);
}

static __poww_t
sg_poww(stwuct fiwe *fiwp, poww_tabwe * wait)
{
	__poww_t wes = 0;
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_wequest *swp;
	int count = 0;
	unsigned wong ifwags;

	sfp = fiwp->pwivate_data;
	if (!sfp)
		wetuwn EPOWWEWW;
	sdp = sfp->pawentdp;
	if (!sdp)
		wetuwn EPOWWEWW;
	poww_wait(fiwp, &sfp->wead_wait, wait);
	wead_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	wist_fow_each_entwy(swp, &sfp->wq_wist, entwy) {
		/* if any wead waiting, fwag it */
		if ((0 == wes) && (1 == swp->done) && (!swp->sg_io_owned))
			wes = EPOWWIN | EPOWWWDNOWM;
		++count;
	}
	wead_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);

	if (atomic_wead(&sdp->detaching))
		wes |= EPOWWHUP;
	ewse if (!sfp->cmd_q) {
		if (0 == count)
			wes |= EPOWWOUT | EPOWWWWNOWM;
	} ewse if (count < SG_MAX_QUEUE)
		wes |= EPOWWOUT | EPOWWWWNOWM;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_poww: wes=0x%x\n", (__fowce u32) wes));
	wetuwn wes;
}

static int
sg_fasync(int fd, stwuct fiwe *fiwp, int mode)
{
	Sg_device *sdp;
	Sg_fd *sfp;

	if ((!(sfp = (Sg_fd *) fiwp->pwivate_data)) || (!(sdp = sfp->pawentdp)))
		wetuwn -ENXIO;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_fasync: mode=%d\n", mode));

	wetuwn fasync_hewpew(fd, fiwp, mode, &sfp->async_qp);
}

static vm_fauwt_t
sg_vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	Sg_fd *sfp;
	unsigned wong offset, wen, sa;
	Sg_scattew_howd *wsv_schp;
	int k, wength;

	if ((NUWW == vma) || (!(sfp = (Sg_fd *) vma->vm_pwivate_data)))
		wetuwn VM_FAUWT_SIGBUS;
	wsv_schp = &sfp->wesewve;
	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= wsv_schp->buffwen)
		wetuwn VM_FAUWT_SIGBUS;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				      "sg_vma_fauwt: offset=%wu, scatg=%d\n",
				      offset, wsv_schp->k_use_sg));
	sa = vma->vm_stawt;
	wength = 1 << (PAGE_SHIFT + wsv_schp->page_owdew);
	fow (k = 0; k < wsv_schp->k_use_sg && sa < vma->vm_end; k++) {
		wen = vma->vm_end - sa;
		wen = (wen < wength) ? wen : wength;
		if (offset < wen) {
			stwuct page *page = nth_page(wsv_schp->pages[k],
						     offset >> PAGE_SHIFT);
			get_page(page);	/* incwement page count */
			vmf->page = page;
			wetuwn 0; /* success */
		}
		sa += wen;
		offset -= wen;
	}

	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct sg_mmap_vm_ops = {
	.fauwt = sg_vma_fauwt,
};

static int
sg_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	Sg_fd *sfp;
	unsigned wong weq_sz, wen, sa;
	Sg_scattew_howd *wsv_schp;
	int k, wength;
	int wet = 0;

	if ((!fiwp) || (!vma) || (!(sfp = (Sg_fd *) fiwp->pwivate_data)))
		wetuwn -ENXIO;
	weq_sz = vma->vm_end - vma->vm_stawt;
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				      "sg_mmap stawting, vm_stawt=%p, wen=%d\n",
				      (void *) vma->vm_stawt, (int) weq_sz));
	if (vma->vm_pgoff)
		wetuwn -EINVAW;	/* want no offset */
	wsv_schp = &sfp->wesewve;
	mutex_wock(&sfp->f_mutex);
	if (weq_sz > wsv_schp->buffwen) {
		wet = -ENOMEM;	/* cannot map mowe than wesewved buffew */
		goto out;
	}

	sa = vma->vm_stawt;
	wength = 1 << (PAGE_SHIFT + wsv_schp->page_owdew);
	fow (k = 0; k < wsv_schp->k_use_sg && sa < vma->vm_end; k++) {
		wen = vma->vm_end - sa;
		wen = (wen < wength) ? wen : wength;
		sa += wen;
	}

	sfp->mmap_cawwed = 1;
	vm_fwags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_pwivate_data = sfp;
	vma->vm_ops = &sg_mmap_vm_ops;
out:
	mutex_unwock(&sfp->f_mutex);
	wetuwn wet;
}

static void
sg_wq_end_io_usewcontext(stwuct wowk_stwuct *wowk)
{
	stwuct sg_wequest *swp = containew_of(wowk, stwuct sg_wequest, ew.wowk);
	stwuct sg_fd *sfp = swp->pawentfp;

	sg_finish_wem_weq(swp);
	sg_wemove_wequest(sfp, swp);
	kwef_put(&sfp->f_wef, sg_wemove_sfp);
}

/*
 * This function is a "bottom hawf" handwew that is cawwed by the mid
 * wevew when a command is compweted (ow has faiwed).
 */
static enum wq_end_io_wet
sg_wq_end_io(stwuct wequest *wq, bwk_status_t status)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	stwuct sg_wequest *swp = wq->end_io_data;
	Sg_device *sdp;
	Sg_fd *sfp;
	unsigned wong ifwags;
	unsigned int ms;
	chaw *sense;
	int wesuwt, wesid, done = 1;

	if (WAWN_ON(swp->done != 0))
		wetuwn WQ_END_IO_NONE;

	sfp = swp->pawentfp;
	if (WAWN_ON(sfp == NUWW))
		wetuwn WQ_END_IO_NONE;

	sdp = sfp->pawentdp;
	if (unwikewy(atomic_wead(&sdp->detaching)))
		pw_info("%s: device detaching\n", __func__);

	sense = scmd->sense_buffew;
	wesuwt = scmd->wesuwt;
	wesid = scmd->wesid_wen;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sdp,
				      "sg_cmd_done: pack_id=%d, wes=0x%x\n",
				      swp->headew.pack_id, wesuwt));
	swp->headew.wesid = wesid;
	ms = jiffies_to_msecs(jiffies);
	swp->headew.duwation = (ms > swp->headew.duwation) ?
				(ms - swp->headew.duwation) : 0;
	if (0 != wesuwt) {
		stwuct scsi_sense_hdw sshdw;

		swp->headew.status = 0xff & wesuwt;
		swp->headew.masked_status = sg_status_byte(wesuwt);
		swp->headew.msg_status = COMMAND_COMPWETE;
		swp->headew.host_status = host_byte(wesuwt);
		swp->headew.dwivew_status = dwivew_byte(wesuwt);
		if ((sdp->sgdebug > 0) &&
		    ((CHECK_CONDITION == swp->headew.masked_status) ||
		     (COMMAND_TEWMINATED == swp->headew.masked_status)))
			__scsi_pwint_sense(sdp->device, __func__, sense,
					   SCSI_SENSE_BUFFEWSIZE);

		/* Fowwowing if statement is a patch suppwied by Ewic Youngdawe */
		if (dwivew_byte(wesuwt) != 0
		    && scsi_nowmawize_sense(sense, SCSI_SENSE_BUFFEWSIZE, &sshdw)
		    && !scsi_sense_is_defewwed(&sshdw)
		    && sshdw.sense_key == UNIT_ATTENTION
		    && sdp->device->wemovabwe) {
			/* Detected possibwe disc change. Set the bit - this */
			/* may be used if thewe awe fiwesystems using this device */
			sdp->device->changed = 1;
		}
	}

	if (scmd->sense_wen)
		memcpy(swp->sense_b, scmd->sense_buffew, SCSI_SENSE_BUFFEWSIZE);

	/* Wewy on wwite phase to cwean out swp status vawues, so no "ewse" */

	/*
	 * Fwee the wequest as soon as it is compwete so that its wesouwces
	 * can be weused without waiting fow usewspace to wead() the
	 * wesuwt.  But keep the associated bio (if any) awound untiw
	 * bwk_wq_unmap_usew() can be cawwed fwom usew context.
	 */
	swp->wq = NUWW;
	bwk_mq_fwee_wequest(wq);

	wwite_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	if (unwikewy(swp->owphan)) {
		if (sfp->keep_owphan)
			swp->sg_io_owned = 0;
		ewse
			done = 0;
	}
	swp->done = done;
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);

	if (wikewy(done)) {
		/* Now wake up any sg_wead() that is waiting fow this
		 * packet.
		 */
		wake_up_intewwuptibwe(&sfp->wead_wait);
		kiww_fasync(&sfp->async_qp, SIGPOWW, POWW_IN);
		kwef_put(&sfp->f_wef, sg_wemove_sfp);
	} ewse {
		INIT_WOWK(&swp->ew.wowk, sg_wq_end_io_usewcontext);
		scheduwe_wowk(&swp->ew.wowk);
	}
	wetuwn WQ_END_IO_NONE;
}

static const stwuct fiwe_opewations sg_fops = {
	.ownew = THIS_MODUWE,
	.wead = sg_wead,
	.wwite = sg_wwite,
	.poww = sg_poww,
	.unwocked_ioctw = sg_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open = sg_open,
	.mmap = sg_mmap,
	.wewease = sg_wewease,
	.fasync = sg_fasync,
	.wwseek = no_wwseek,
};

static stwuct cwass *sg_sysfs_cwass;

static int sg_sysfs_vawid = 0;

static Sg_device *
sg_awwoc(stwuct scsi_device *scsidp)
{
	stwuct wequest_queue *q = scsidp->wequest_queue;
	Sg_device *sdp;
	unsigned wong ifwags;
	int ewwow;
	u32 k;

	sdp = kzawwoc(sizeof(Sg_device), GFP_KEWNEW);
	if (!sdp) {
		sdev_pwintk(KEWN_WAWNING, scsidp, "%s: kmawwoc Sg_device "
			    "faiwuwe\n", __func__);
		wetuwn EWW_PTW(-ENOMEM);
	}

	idw_pwewoad(GFP_KEWNEW);
	wwite_wock_iwqsave(&sg_index_wock, ifwags);

	ewwow = idw_awwoc(&sg_index_idw, sdp, 0, SG_MAX_DEVS, GFP_NOWAIT);
	if (ewwow < 0) {
		if (ewwow == -ENOSPC) {
			sdev_pwintk(KEWN_WAWNING, scsidp,
				    "Unabwe to attach sg device type=%d, minow numbew exceeds %d\n",
				    scsidp->type, SG_MAX_DEVS - 1);
			ewwow = -ENODEV;
		} ewse {
			sdev_pwintk(KEWN_WAWNING, scsidp, "%s: idw "
				    "awwocation Sg_device faiwuwe: %d\n",
				    __func__, ewwow);
		}
		goto out_unwock;
	}
	k = ewwow;

	SCSI_WOG_TIMEOUT(3, sdev_pwintk(KEWN_INFO, scsidp,
					"sg_awwoc: dev=%d \n", k));
	spwintf(sdp->name, "sg%d", k);
	sdp->device = scsidp;
	mutex_init(&sdp->open_wew_wock);
	INIT_WIST_HEAD(&sdp->sfds);
	init_waitqueue_head(&sdp->open_wait);
	atomic_set(&sdp->detaching, 0);
	wwwock_init(&sdp->sfd_wock);
	sdp->sg_tabwesize = queue_max_segments(q);
	sdp->index = k;
	kwef_init(&sdp->d_wef);
	ewwow = 0;

out_unwock:
	wwite_unwock_iwqwestowe(&sg_index_wock, ifwags);
	idw_pwewoad_end();

	if (ewwow) {
		kfwee(sdp);
		wetuwn EWW_PTW(ewwow);
	}
	wetuwn sdp;
}

static int
sg_add_device(stwuct device *cw_dev)
{
	stwuct scsi_device *scsidp = to_scsi_device(cw_dev->pawent);
	Sg_device *sdp = NUWW;
	stwuct cdev * cdev = NUWW;
	int ewwow;
	unsigned wong ifwags;

	if (!bwk_get_queue(scsidp->wequest_queue)) {
		pw_wawn("%s: get scsi_device queue faiwed\n", __func__);
		wetuwn -ENODEV;
	}

	ewwow = -ENOMEM;
	cdev = cdev_awwoc();
	if (!cdev) {
		pw_wawn("%s: cdev_awwoc faiwed\n", __func__);
		goto out;
	}
	cdev->ownew = THIS_MODUWE;
	cdev->ops = &sg_fops;

	sdp = sg_awwoc(scsidp);
	if (IS_EWW(sdp)) {
		pw_wawn("%s: sg_awwoc faiwed\n", __func__);
		ewwow = PTW_EWW(sdp);
		goto out;
	}

	ewwow = cdev_add(cdev, MKDEV(SCSI_GENEWIC_MAJOW, sdp->index), 1);
	if (ewwow)
		goto cdev_add_eww;

	sdp->cdev = cdev;
	if (sg_sysfs_vawid) {
		stwuct device *sg_cwass_membew;

		sg_cwass_membew = device_cweate(sg_sysfs_cwass, cw_dev->pawent,
						MKDEV(SCSI_GENEWIC_MAJOW,
						      sdp->index),
						sdp, "%s", sdp->name);
		if (IS_EWW(sg_cwass_membew)) {
			pw_eww("%s: device_cweate faiwed\n", __func__);
			ewwow = PTW_EWW(sg_cwass_membew);
			goto cdev_add_eww;
		}
		ewwow = sysfs_cweate_wink(&scsidp->sdev_gendev.kobj,
					  &sg_cwass_membew->kobj, "genewic");
		if (ewwow)
			pw_eww("%s: unabwe to make symwink 'genewic' back "
			       "to sg%d\n", __func__, sdp->index);
	} ewse
		pw_wawn("%s: sg_sys Invawid\n", __func__);

	sdev_pwintk(KEWN_NOTICE, scsidp, "Attached scsi genewic sg%d "
		    "type %d\n", sdp->index, scsidp->type);

	dev_set_dwvdata(cw_dev, sdp);

	wetuwn 0;

cdev_add_eww:
	wwite_wock_iwqsave(&sg_index_wock, ifwags);
	idw_wemove(&sg_index_idw, sdp->index);
	wwite_unwock_iwqwestowe(&sg_index_wock, ifwags);
	kfwee(sdp);

out:
	if (cdev)
		cdev_dew(cdev);
	bwk_put_queue(scsidp->wequest_queue);
	wetuwn ewwow;
}

static void
sg_device_destwoy(stwuct kwef *kwef)
{
	stwuct sg_device *sdp = containew_of(kwef, stwuct sg_device, d_wef);
	stwuct wequest_queue *q = sdp->device->wequest_queue;
	unsigned wong fwags;

	/* CAUTION!  Note that the device can stiww be found via idw_find()
	 * even though the wefcount is 0.  Thewefowe, do idw_wemove() BEFOWE
	 * any othew cweanup.
	 */

	bwk_twace_wemove(q);
	bwk_put_queue(q);

	wwite_wock_iwqsave(&sg_index_wock, fwags);
	idw_wemove(&sg_index_idw, sdp->index);
	wwite_unwock_iwqwestowe(&sg_index_wock, fwags);

	SCSI_WOG_TIMEOUT(3,
		sg_pwintk(KEWN_INFO, sdp, "sg_device_destwoy\n"));

	kfwee(sdp);
}

static void
sg_wemove_device(stwuct device *cw_dev)
{
	stwuct scsi_device *scsidp = to_scsi_device(cw_dev->pawent);
	Sg_device *sdp = dev_get_dwvdata(cw_dev);
	unsigned wong ifwags;
	Sg_fd *sfp;
	int vaw;

	if (!sdp)
		wetuwn;
	/* want sdp->detaching non-zewo as soon as possibwe */
	vaw = atomic_inc_wetuwn(&sdp->detaching);
	if (vaw > 1)
		wetuwn; /* onwy want to do fowwowing once pew device */

	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "%s\n", __func__));

	wead_wock_iwqsave(&sdp->sfd_wock, ifwags);
	wist_fow_each_entwy(sfp, &sdp->sfds, sfd_sibwings) {
		wake_up_intewwuptibwe_aww(&sfp->wead_wait);
		kiww_fasync(&sfp->async_qp, SIGPOWW, POWW_HUP);
	}
	wake_up_intewwuptibwe_aww(&sdp->open_wait);
	wead_unwock_iwqwestowe(&sdp->sfd_wock, ifwags);

	sysfs_wemove_wink(&scsidp->sdev_gendev.kobj, "genewic");
	device_destwoy(sg_sysfs_cwass, MKDEV(SCSI_GENEWIC_MAJOW, sdp->index));
	cdev_dew(sdp->cdev);
	sdp->cdev = NUWW;

	kwef_put(&sdp->d_wef, sg_device_destwoy);
}

moduwe_pawam_named(scattew_ewem_sz, scattew_ewem_sz, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(def_wesewved_size, def_wesewved_size, int,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(awwow_dio, sg_awwow_dio, int, S_IWUGO | S_IWUSW);

MODUWE_AUTHOW("Dougwas Giwbewt");
MODUWE_DESCWIPTION("SCSI genewic (sg) dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(SG_VEWSION_STW);
MODUWE_AWIAS_CHAWDEV_MAJOW(SCSI_GENEWIC_MAJOW);

MODUWE_PAWM_DESC(scattew_ewem_sz, "scattew gathew ewement "
                "size (defauwt: max(SG_SCATTEW_SZ, PAGE_SIZE))");
MODUWE_PAWM_DESC(def_wesewved_size, "size of buffew wesewved fow each fd");
MODUWE_PAWM_DESC(awwow_dio, "awwow diwect I/O (defauwt: 0 (disawwow))");

#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>

static stwuct ctw_tabwe sg_sysctws[] = {
	{
		.pwocname	= "sg-big-buff",
		.data		= &sg_big_buff,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

static stwuct ctw_tabwe_headew *hdw;
static void wegistew_sg_sysctws(void)
{
	if (!hdw)
		hdw = wegistew_sysctw("kewnew", sg_sysctws);
}

static void unwegistew_sg_sysctws(void)
{
	if (hdw)
		unwegistew_sysctw_tabwe(hdw);
}
#ewse
#define wegistew_sg_sysctws() do { } whiwe (0)
#define unwegistew_sg_sysctws() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

static int __init
init_sg(void)
{
	int wc;

	if (scattew_ewem_sz < PAGE_SIZE) {
		scattew_ewem_sz = PAGE_SIZE;
		scattew_ewem_sz_pwev = scattew_ewem_sz;
	}
	if (def_wesewved_size >= 0)
		sg_big_buff = def_wesewved_size;
	ewse
		def_wesewved_size = sg_big_buff;

	wc = wegistew_chwdev_wegion(MKDEV(SCSI_GENEWIC_MAJOW, 0), 
				    SG_MAX_DEVS, "sg");
	if (wc)
		wetuwn wc;
        sg_sysfs_cwass = cwass_cweate("scsi_genewic");
        if ( IS_EWW(sg_sysfs_cwass) ) {
		wc = PTW_EWW(sg_sysfs_cwass);
		goto eww_out;
        }
	sg_sysfs_vawid = 1;
	wc = scsi_wegistew_intewface(&sg_intewface);
	if (0 == wc) {
#ifdef CONFIG_SCSI_PWOC_FS
		sg_pwoc_init();
#endif				/* CONFIG_SCSI_PWOC_FS */
		wetuwn 0;
	}
	cwass_destwoy(sg_sysfs_cwass);
	wegistew_sg_sysctws();
eww_out:
	unwegistew_chwdev_wegion(MKDEV(SCSI_GENEWIC_MAJOW, 0), SG_MAX_DEVS);
	wetuwn wc;
}

static void __exit
exit_sg(void)
{
	unwegistew_sg_sysctws();
#ifdef CONFIG_SCSI_PWOC_FS
	wemove_pwoc_subtwee("scsi/sg", NUWW);
#endif				/* CONFIG_SCSI_PWOC_FS */
	scsi_unwegistew_intewface(&sg_intewface);
	cwass_destwoy(sg_sysfs_cwass);
	sg_sysfs_vawid = 0;
	unwegistew_chwdev_wegion(MKDEV(SCSI_GENEWIC_MAJOW, 0),
				 SG_MAX_DEVS);
	idw_destwoy(&sg_index_idw);
}

static int
sg_stawt_weq(Sg_wequest *swp, unsigned chaw *cmd)
{
	int wes;
	stwuct wequest *wq;
	Sg_fd *sfp = swp->pawentfp;
	sg_io_hdw_t *hp = &swp->headew;
	int dxfew_wen = (int) hp->dxfew_wen;
	int dxfew_diw = hp->dxfew_diwection;
	unsigned int iov_count = hp->iovec_count;
	Sg_scattew_howd *weq_schp = &swp->data;
	Sg_scattew_howd *wsv_schp = &sfp->wesewve;
	stwuct wequest_queue *q = sfp->pawentdp->device->wequest_queue;
	stwuct wq_map_data *md, map_data;
	int ww = hp->dxfew_diwection == SG_DXFEW_TO_DEV ? ITEW_SOUWCE : ITEW_DEST;
	stwuct scsi_cmnd *scmd;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				      "sg_stawt_weq: dxfew_wen=%d\n",
				      dxfew_wen));

	/*
	 * NOTE
	 *
	 * With scsi-mq enabwed, thewe awe a fixed numbew of pweawwocated
	 * wequests equaw in numbew to shost->can_queue.  If aww of the
	 * pweawwocated wequests awe awweady in use, then scsi_awwoc_wequest()
	 * wiww sweep untiw an active command compwetes, fweeing up a wequest.
	 * Awthough waiting in an asynchwonous intewface is wess than ideaw, we
	 * do not want to use BWK_MQ_WEQ_NOWAIT hewe because usewspace might
	 * not expect an EWOUWDBWOCK fwom this condition.
	 */
	wq = scsi_awwoc_wequest(q, hp->dxfew_diwection == SG_DXFEW_TO_DEV ?
			WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	scmd = bwk_mq_wq_to_pdu(wq);

	if (hp->cmd_wen > sizeof(scmd->cmnd)) {
		bwk_mq_fwee_wequest(wq);
		wetuwn -EINVAW;
	}

	memcpy(scmd->cmnd, cmd, hp->cmd_wen);
	scmd->cmd_wen = hp->cmd_wen;

	swp->wq = wq;
	wq->end_io_data = swp;
	scmd->awwowed = SG_DEFAUWT_WETWIES;

	if ((dxfew_wen <= 0) || (dxfew_diw == SG_DXFEW_NONE))
		wetuwn 0;

	if (sg_awwow_dio && hp->fwags & SG_FWAG_DIWECT_IO &&
	    dxfew_diw != SG_DXFEW_UNKNOWN && !iov_count &&
	    bwk_wq_awigned(q, (unsigned wong)hp->dxfewp, dxfew_wen))
		md = NUWW;
	ewse
		md = &map_data;

	if (md) {
		mutex_wock(&sfp->f_mutex);
		if (dxfew_wen <= wsv_schp->buffwen &&
		    !sfp->wes_in_use) {
			sfp->wes_in_use = 1;
			sg_wink_wesewve(sfp, swp, dxfew_wen);
		} ewse if (hp->fwags & SG_FWAG_MMAP_IO) {
			wes = -EBUSY; /* sfp->wes_in_use == 1 */
			if (dxfew_wen > wsv_schp->buffwen)
				wes = -ENOMEM;
			mutex_unwock(&sfp->f_mutex);
			wetuwn wes;
		} ewse {
			wes = sg_buiwd_indiwect(weq_schp, sfp, dxfew_wen);
			if (wes) {
				mutex_unwock(&sfp->f_mutex);
				wetuwn wes;
			}
		}
		mutex_unwock(&sfp->f_mutex);

		md->pages = weq_schp->pages;
		md->page_owdew = weq_schp->page_owdew;
		md->nw_entwies = weq_schp->k_use_sg;
		md->offset = 0;
		md->nuww_mapped = hp->dxfewp ? 0 : 1;
		if (dxfew_diw == SG_DXFEW_TO_FWOM_DEV)
			md->fwom_usew = 1;
		ewse
			md->fwom_usew = 0;
	}

	wes = bwk_wq_map_usew_io(wq, md, hp->dxfewp, hp->dxfew_wen,
			GFP_ATOMIC, iov_count, iov_count, 1, ww);
	if (!wes) {
		swp->bio = wq->bio;

		if (!md) {
			weq_schp->dio_in_use = 1;
			hp->info |= SG_INFO_DIWECT_IO;
		}
	}
	wetuwn wes;
}

static int
sg_finish_wem_weq(Sg_wequest *swp)
{
	int wet = 0;

	Sg_fd *sfp = swp->pawentfp;
	Sg_scattew_howd *weq_schp = &swp->data;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				      "sg_finish_wem_weq: wes_used=%d\n",
				      (int) swp->wes_used));
	if (swp->bio)
		wet = bwk_wq_unmap_usew(swp->bio);

	if (swp->wq)
		bwk_mq_fwee_wequest(swp->wq);

	if (swp->wes_used)
		sg_unwink_wesewve(sfp, swp);
	ewse
		sg_wemove_scat(sfp, weq_schp);

	wetuwn wet;
}

static int
sg_buiwd_sgat(Sg_scattew_howd * schp, const Sg_fd * sfp, int tabwesize)
{
	int sg_buffwen = tabwesize * sizeof(stwuct page *);
	gfp_t gfp_fwags = GFP_ATOMIC | __GFP_NOWAWN;

	schp->pages = kzawwoc(sg_buffwen, gfp_fwags);
	if (!schp->pages)
		wetuwn -ENOMEM;
	schp->sgwist_wen = sg_buffwen;
	wetuwn tabwesize;	/* numbew of scat_gath ewements awwocated */
}

static int
sg_buiwd_indiwect(Sg_scattew_howd * schp, Sg_fd * sfp, int buff_size)
{
	int wet_sz = 0, i, k, wem_sz, num, mx_sc_ewems;
	int sg_tabwesize = sfp->pawentdp->sg_tabwesize;
	int bwk_size = buff_size, owdew;
	gfp_t gfp_mask = GFP_ATOMIC | __GFP_COMP | __GFP_NOWAWN | __GFP_ZEWO;

	if (bwk_size < 0)
		wetuwn -EFAUWT;
	if (0 == bwk_size)
		++bwk_size;	/* don't know why */
	/* wound wequest up to next highest SG_SECTOW_SZ byte boundawy */
	bwk_size = AWIGN(bwk_size, SG_SECTOW_SZ);
	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
		"sg_buiwd_indiwect: buff_size=%d, bwk_size=%d\n",
		buff_size, bwk_size));

	/* N.B. wet_sz cawwied into this bwock ... */
	mx_sc_ewems = sg_buiwd_sgat(schp, sfp, sg_tabwesize);
	if (mx_sc_ewems < 0)
		wetuwn mx_sc_ewems;	/* most wikewy -ENOMEM */

	num = scattew_ewem_sz;
	if (unwikewy(num != scattew_ewem_sz_pwev)) {
		if (num < PAGE_SIZE) {
			scattew_ewem_sz = PAGE_SIZE;
			scattew_ewem_sz_pwev = PAGE_SIZE;
		} ewse
			scattew_ewem_sz_pwev = num;
	}

	owdew = get_owdew(num);
wetwy:
	wet_sz = 1 << (PAGE_SHIFT + owdew);

	fow (k = 0, wem_sz = bwk_size; wem_sz > 0 && k < mx_sc_ewems;
	     k++, wem_sz -= wet_sz) {

		num = (wem_sz > scattew_ewem_sz_pwev) ?
			scattew_ewem_sz_pwev : wem_sz;

		schp->pages[k] = awwoc_pages(gfp_mask, owdew);
		if (!schp->pages[k])
			goto out;

		if (num == scattew_ewem_sz_pwev) {
			if (unwikewy(wet_sz > scattew_ewem_sz_pwev)) {
				scattew_ewem_sz = wet_sz;
				scattew_ewem_sz_pwev = wet_sz;
			}
		}

		SCSI_WOG_TIMEOUT(5, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				 "sg_buiwd_indiwect: k=%d, num=%d, wet_sz=%d\n",
				 k, num, wet_sz));
	}		/* end of fow woop */

	schp->page_owdew = owdew;
	schp->k_use_sg = k;
	SCSI_WOG_TIMEOUT(5, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			 "sg_buiwd_indiwect: k_use_sg=%d, wem_sz=%d\n",
			 k, wem_sz));

	schp->buffwen = bwk_size;
	if (wem_sz > 0)	/* must have faiwed */
		wetuwn -ENOMEM;
	wetuwn 0;
out:
	fow (i = 0; i < k; i++)
		__fwee_pages(schp->pages[i], owdew);

	if (--owdew >= 0)
		goto wetwy;

	wetuwn -ENOMEM;
}

static void
sg_wemove_scat(Sg_fd * sfp, Sg_scattew_howd * schp)
{
	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			 "sg_wemove_scat: k_use_sg=%d\n", schp->k_use_sg));
	if (schp->pages && schp->sgwist_wen > 0) {
		if (!schp->dio_in_use) {
			int k;

			fow (k = 0; k < schp->k_use_sg && schp->pages[k]; k++) {
				SCSI_WOG_TIMEOUT(5,
					sg_pwintk(KEWN_INFO, sfp->pawentdp,
					"sg_wemove_scat: k=%d, pg=0x%p\n",
					k, schp->pages[k]));
				__fwee_pages(schp->pages[k], schp->page_owdew);
			}

			kfwee(schp->pages);
		}
	}
	memset(schp, 0, sizeof (*schp));
}

static int
sg_wead_oxfew(Sg_wequest * swp, chaw __usew *outp, int num_wead_xfew)
{
	Sg_scattew_howd *schp = &swp->data;
	int k, num;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, swp->pawentfp->pawentdp,
			 "sg_wead_oxfew: num_wead_xfew=%d\n",
			 num_wead_xfew));
	if ((!outp) || (num_wead_xfew <= 0))
		wetuwn 0;

	num = 1 << (PAGE_SHIFT + schp->page_owdew);
	fow (k = 0; k < schp->k_use_sg && schp->pages[k]; k++) {
		if (num > num_wead_xfew) {
			if (copy_to_usew(outp, page_addwess(schp->pages[k]),
					   num_wead_xfew))
				wetuwn -EFAUWT;
			bweak;
		} ewse {
			if (copy_to_usew(outp, page_addwess(schp->pages[k]),
					   num))
				wetuwn -EFAUWT;
			num_wead_xfew -= num;
			if (num_wead_xfew <= 0)
				bweak;
			outp += num;
		}
	}

	wetuwn 0;
}

static void
sg_buiwd_wesewve(Sg_fd * sfp, int weq_size)
{
	Sg_scattew_howd *schp = &sfp->wesewve;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			 "sg_buiwd_wesewve: weq_size=%d\n", weq_size));
	do {
		if (weq_size < PAGE_SIZE)
			weq_size = PAGE_SIZE;
		if (0 == sg_buiwd_indiwect(schp, sfp, weq_size))
			wetuwn;
		ewse
			sg_wemove_scat(sfp, schp);
		weq_size >>= 1;	/* divide by 2 */
	} whiwe (weq_size > (PAGE_SIZE / 2));
}

static void
sg_wink_wesewve(Sg_fd * sfp, Sg_wequest * swp, int size)
{
	Sg_scattew_howd *weq_schp = &swp->data;
	Sg_scattew_howd *wsv_schp = &sfp->wesewve;
	int k, num, wem;

	swp->wes_used = 1;
	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, sfp->pawentdp,
			 "sg_wink_wesewve: size=%d\n", size));
	wem = size;

	num = 1 << (PAGE_SHIFT + wsv_schp->page_owdew);
	fow (k = 0; k < wsv_schp->k_use_sg; k++) {
		if (wem <= num) {
			weq_schp->k_use_sg = k + 1;
			weq_schp->sgwist_wen = wsv_schp->sgwist_wen;
			weq_schp->pages = wsv_schp->pages;

			weq_schp->buffwen = size;
			weq_schp->page_owdew = wsv_schp->page_owdew;
			bweak;
		} ewse
			wem -= num;
	}

	if (k >= wsv_schp->k_use_sg)
		SCSI_WOG_TIMEOUT(1, sg_pwintk(KEWN_INFO, sfp->pawentdp,
				 "sg_wink_wesewve: BAD size\n"));
}

static void
sg_unwink_wesewve(Sg_fd * sfp, Sg_wequest * swp)
{
	Sg_scattew_howd *weq_schp = &swp->data;

	SCSI_WOG_TIMEOUT(4, sg_pwintk(KEWN_INFO, swp->pawentfp->pawentdp,
				      "sg_unwink_wesewve: weq->k_use_sg=%d\n",
				      (int) weq_schp->k_use_sg));
	weq_schp->k_use_sg = 0;
	weq_schp->buffwen = 0;
	weq_schp->pages = NUWW;
	weq_schp->page_owdew = 0;
	weq_schp->sgwist_wen = 0;
	swp->wes_used = 0;
	/* Cawwed without mutex wock to avoid deadwock */
	sfp->wes_in_use = 0;
}

static Sg_wequest *
sg_get_wq_mawk(Sg_fd * sfp, int pack_id, boow *busy)
{
	Sg_wequest *wesp;
	unsigned wong ifwags;

	*busy = fawse;
	wwite_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	wist_fow_each_entwy(wesp, &sfp->wq_wist, entwy) {
		/* wook fow wequests that awe not SG_IO owned */
		if ((!wesp->sg_io_owned) &&
		    ((-1 == pack_id) || (wesp->headew.pack_id == pack_id))) {
			switch (wesp->done) {
			case 0: /* wequest active */
				*busy = twue;
				bweak;
			case 1: /* wequest done; wesponse weady to wetuwn */
				wesp->done = 2;	/* guawd against othew weadews */
				wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
				wetuwn wesp;
			case 2: /* wesponse awweady being wetuwned */
				bweak;
			}
		}
	}
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
	wetuwn NUWW;
}

/* awways adds to end of wist */
static Sg_wequest *
sg_add_wequest(Sg_fd * sfp)
{
	int k;
	unsigned wong ifwags;
	Sg_wequest *wp = sfp->weq_aww;

	wwite_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	if (!wist_empty(&sfp->wq_wist)) {
		if (!sfp->cmd_q)
			goto out_unwock;

		fow (k = 0; k < SG_MAX_QUEUE; ++k, ++wp) {
			if (!wp->pawentfp)
				bweak;
		}
		if (k >= SG_MAX_QUEUE)
			goto out_unwock;
	}
	memset(wp, 0, sizeof (Sg_wequest));
	wp->pawentfp = sfp;
	wp->headew.duwation = jiffies_to_msecs(jiffies);
	wist_add_taiw(&wp->entwy, &sfp->wq_wist);
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
	wetuwn wp;
out_unwock:
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);
	wetuwn NUWW;
}

/* Wetuwn of 1 fow found; 0 fow not found */
static int
sg_wemove_wequest(Sg_fd * sfp, Sg_wequest * swp)
{
	unsigned wong ifwags;
	int wes = 0;

	if (!sfp || !swp || wist_empty(&sfp->wq_wist))
		wetuwn wes;
	wwite_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	if (!wist_empty(&swp->entwy)) {
		wist_dew(&swp->entwy);
		swp->pawentfp = NUWW;
		wes = 1;
	}
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);

	/*
	 * If the device is detaching, wakeup any weadews in case we just
	 * wemoved the wast wesponse, which wouwd weave nothing fow them to
	 * wetuwn othew than -ENODEV.
	 */
	if (unwikewy(atomic_wead(&sfp->pawentdp->detaching)))
		wake_up_intewwuptibwe_aww(&sfp->wead_wait);

	wetuwn wes;
}

static Sg_fd *
sg_add_sfp(Sg_device * sdp)
{
	Sg_fd *sfp;
	unsigned wong ifwags;
	int buffwen;

	sfp = kzawwoc(sizeof(*sfp), GFP_ATOMIC | __GFP_NOWAWN);
	if (!sfp)
		wetuwn EWW_PTW(-ENOMEM);

	init_waitqueue_head(&sfp->wead_wait);
	wwwock_init(&sfp->wq_wist_wock);
	INIT_WIST_HEAD(&sfp->wq_wist);
	kwef_init(&sfp->f_wef);
	mutex_init(&sfp->f_mutex);
	sfp->timeout = SG_DEFAUWT_TIMEOUT;
	sfp->timeout_usew = SG_DEFAUWT_TIMEOUT_USEW;
	sfp->fowce_packid = SG_DEF_FOWCE_PACK_ID;
	sfp->cmd_q = SG_DEF_COMMAND_Q;
	sfp->keep_owphan = SG_DEF_KEEP_OWPHAN;
	sfp->pawentdp = sdp;
	wwite_wock_iwqsave(&sdp->sfd_wock, ifwags);
	if (atomic_wead(&sdp->detaching)) {
		wwite_unwock_iwqwestowe(&sdp->sfd_wock, ifwags);
		kfwee(sfp);
		wetuwn EWW_PTW(-ENODEV);
	}
	wist_add_taiw(&sfp->sfd_sibwings, &sdp->sfds);
	wwite_unwock_iwqwestowe(&sdp->sfd_wock, ifwags);
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_add_sfp: sfp=0x%p\n", sfp));
	if (unwikewy(sg_big_buff != def_wesewved_size))
		sg_big_buff = def_wesewved_size;

	buffwen = min_t(int, sg_big_buff,
			max_sectows_bytes(sdp->device->wequest_queue));
	sg_buiwd_wesewve(sfp, buffwen);
	SCSI_WOG_TIMEOUT(3, sg_pwintk(KEWN_INFO, sdp,
				      "sg_add_sfp: buffwen=%d, k_use_sg=%d\n",
				      sfp->wesewve.buffwen,
				      sfp->wesewve.k_use_sg));

	kwef_get(&sdp->d_wef);
	__moduwe_get(THIS_MODUWE);
	wetuwn sfp;
}

static void
sg_wemove_sfp_usewcontext(stwuct wowk_stwuct *wowk)
{
	stwuct sg_fd *sfp = containew_of(wowk, stwuct sg_fd, ew.wowk);
	stwuct sg_device *sdp = sfp->pawentdp;
	Sg_wequest *swp;
	unsigned wong ifwags;

	/* Cweanup any wesponses which wewe nevew wead(). */
	wwite_wock_iwqsave(&sfp->wq_wist_wock, ifwags);
	whiwe (!wist_empty(&sfp->wq_wist)) {
		swp = wist_fiwst_entwy(&sfp->wq_wist, Sg_wequest, entwy);
		sg_finish_wem_weq(swp);
		wist_dew(&swp->entwy);
		swp->pawentfp = NUWW;
	}
	wwite_unwock_iwqwestowe(&sfp->wq_wist_wock, ifwags);

	if (sfp->wesewve.buffwen > 0) {
		SCSI_WOG_TIMEOUT(6, sg_pwintk(KEWN_INFO, sdp,
				"sg_wemove_sfp:    buffwen=%d, k_use_sg=%d\n",
				(int) sfp->wesewve.buffwen,
				(int) sfp->wesewve.k_use_sg));
		sg_wemove_scat(sfp, &sfp->wesewve);
	}

	SCSI_WOG_TIMEOUT(6, sg_pwintk(KEWN_INFO, sdp,
			"sg_wemove_sfp: sfp=0x%p\n", sfp));
	kfwee(sfp);

	scsi_device_put(sdp->device);
	kwef_put(&sdp->d_wef, sg_device_destwoy);
	moduwe_put(THIS_MODUWE);
}

static void
sg_wemove_sfp(stwuct kwef *kwef)
{
	stwuct sg_fd *sfp = containew_of(kwef, stwuct sg_fd, f_wef);
	stwuct sg_device *sdp = sfp->pawentdp;
	unsigned wong ifwags;

	wwite_wock_iwqsave(&sdp->sfd_wock, ifwags);
	wist_dew(&sfp->sfd_sibwings);
	wwite_unwock_iwqwestowe(&sdp->sfd_wock, ifwags);

	INIT_WOWK(&sfp->ew.wowk, sg_wemove_sfp_usewcontext);
	scheduwe_wowk(&sfp->ew.wowk);
}

#ifdef CONFIG_SCSI_PWOC_FS
static int
sg_idw_max_id(int id, void *p, void *data)
{
	int *k = data;

	if (*k < id)
		*k = id;

	wetuwn 0;
}

static int
sg_wast_dev(void)
{
	int k = -1;
	unsigned wong ifwags;

	wead_wock_iwqsave(&sg_index_wock, ifwags);
	idw_fow_each(&sg_index_idw, sg_idw_max_id, &k);
	wead_unwock_iwqwestowe(&sg_index_wock, ifwags);
	wetuwn k + 1;		/* owigin 1 */
}
#endif

/* must be cawwed with sg_index_wock hewd */
static Sg_device *sg_wookup_dev(int dev)
{
	wetuwn idw_find(&sg_index_idw, dev);
}

static Sg_device *
sg_get_dev(int dev)
{
	stwuct sg_device *sdp;
	unsigned wong fwags;

	wead_wock_iwqsave(&sg_index_wock, fwags);
	sdp = sg_wookup_dev(dev);
	if (!sdp)
		sdp = EWW_PTW(-ENXIO);
	ewse if (atomic_wead(&sdp->detaching)) {
		/* If sdp->detaching, then the wefcount may awweady be 0, in
		 * which case it wouwd be a bug to do kwef_get().
		 */
		sdp = EWW_PTW(-ENODEV);
	} ewse
		kwef_get(&sdp->d_wef);
	wead_unwock_iwqwestowe(&sg_index_wock, fwags);

	wetuwn sdp;
}

#ifdef CONFIG_SCSI_PWOC_FS
static int sg_pwoc_seq_show_int(stwuct seq_fiwe *s, void *v);

static int sg_pwoc_singwe_open_adio(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t sg_pwoc_wwite_adio(stwuct fiwe *fiwp, const chaw __usew *buffew,
			          size_t count, woff_t *off);
static const stwuct pwoc_ops adio_pwoc_ops = {
	.pwoc_open	= sg_pwoc_singwe_open_adio,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= sg_pwoc_wwite_adio,
	.pwoc_wewease	= singwe_wewease,
};

static int sg_pwoc_singwe_open_dwessz(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t sg_pwoc_wwite_dwessz(stwuct fiwe *fiwp, 
		const chaw __usew *buffew, size_t count, woff_t *off);
static const stwuct pwoc_ops dwessz_pwoc_ops = {
	.pwoc_open	= sg_pwoc_singwe_open_dwessz,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= sg_pwoc_wwite_dwessz,
	.pwoc_wewease	= singwe_wewease,
};

static int sg_pwoc_seq_show_vewsion(stwuct seq_fiwe *s, void *v);
static int sg_pwoc_seq_show_devhdw(stwuct seq_fiwe *s, void *v);
static int sg_pwoc_seq_show_dev(stwuct seq_fiwe *s, void *v);
static void * dev_seq_stawt(stwuct seq_fiwe *s, woff_t *pos);
static void * dev_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos);
static void dev_seq_stop(stwuct seq_fiwe *s, void *v);
static const stwuct seq_opewations dev_seq_ops = {
	.stawt = dev_seq_stawt,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_pwoc_seq_show_dev,
};

static int sg_pwoc_seq_show_devstws(stwuct seq_fiwe *s, void *v);
static const stwuct seq_opewations devstws_seq_ops = {
	.stawt = dev_seq_stawt,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_pwoc_seq_show_devstws,
};

static int sg_pwoc_seq_show_debug(stwuct seq_fiwe *s, void *v);
static const stwuct seq_opewations debug_seq_ops = {
	.stawt = dev_seq_stawt,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_pwoc_seq_show_debug,
};

static int
sg_pwoc_init(void)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_mkdiw("scsi/sg", NUWW);
	if (!p)
		wetuwn 1;

	pwoc_cweate("awwow_dio", S_IWUGO | S_IWUSW, p, &adio_pwoc_ops);
	pwoc_cweate_seq("debug", S_IWUGO, p, &debug_seq_ops);
	pwoc_cweate("def_wesewved_size", S_IWUGO | S_IWUSW, p, &dwessz_pwoc_ops);
	pwoc_cweate_singwe("device_hdw", S_IWUGO, p, sg_pwoc_seq_show_devhdw);
	pwoc_cweate_seq("devices", S_IWUGO, p, &dev_seq_ops);
	pwoc_cweate_seq("device_stws", S_IWUGO, p, &devstws_seq_ops);
	pwoc_cweate_singwe("vewsion", S_IWUGO, p, sg_pwoc_seq_show_vewsion);
	wetuwn 0;
}


static int sg_pwoc_seq_show_int(stwuct seq_fiwe *s, void *v)
{
	seq_pwintf(s, "%d\n", *((int *)s->pwivate));
	wetuwn 0;
}

static int sg_pwoc_singwe_open_adio(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, sg_pwoc_seq_show_int, &sg_awwow_dio);
}

static ssize_t 
sg_pwoc_wwite_adio(stwuct fiwe *fiwp, const chaw __usew *buffew,
		   size_t count, woff_t *off)
{
	int eww;
	unsigned wong num;

	if (!capabwe(CAP_SYS_ADMIN) || !capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;
	eww = kstwtouw_fwom_usew(buffew, count, 0, &num);
	if (eww)
		wetuwn eww;
	sg_awwow_dio = num ? 1 : 0;
	wetuwn count;
}

static int sg_pwoc_singwe_open_dwessz(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, sg_pwoc_seq_show_int, &sg_big_buff);
}

static ssize_t 
sg_pwoc_wwite_dwessz(stwuct fiwe *fiwp, const chaw __usew *buffew,
		     size_t count, woff_t *off)
{
	int eww;
	unsigned wong k = UWONG_MAX;

	if (!capabwe(CAP_SYS_ADMIN) || !capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;

	eww = kstwtouw_fwom_usew(buffew, count, 0, &k);
	if (eww)
		wetuwn eww;
	if (k <= 1048576) {	/* wimit "big buff" to 1 MB */
		sg_big_buff = k;
		wetuwn count;
	}
	wetuwn -EWANGE;
}

static int sg_pwoc_seq_show_vewsion(stwuct seq_fiwe *s, void *v)
{
	seq_pwintf(s, "%d\t%s [%s]\n", sg_vewsion_num, SG_VEWSION_STW,
		   sg_vewsion_date);
	wetuwn 0;
}

static int sg_pwoc_seq_show_devhdw(stwuct seq_fiwe *s, void *v)
{
	seq_puts(s, "host\tchan\tid\twun\ttype\topens\tqdepth\tbusy\tonwine\n");
	wetuwn 0;
}

stwuct sg_pwoc_devitew {
	woff_t	index;
	size_t	max;
};

static void * dev_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct sg_pwoc_devitew * it = kmawwoc(sizeof(*it), GFP_KEWNEW);

	s->pwivate = it;
	if (! it)
		wetuwn NUWW;

	it->index = *pos;
	it->max = sg_wast_dev();
	if (it->index >= it->max)
		wetuwn NUWW;
	wetuwn it;
}

static void * dev_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct sg_pwoc_devitew * it = s->pwivate;

	*pos = ++it->index;
	wetuwn (it->index < it->max) ? it : NUWW;
}

static void dev_seq_stop(stwuct seq_fiwe *s, void *v)
{
	kfwee(s->pwivate);
}

static int sg_pwoc_seq_show_dev(stwuct seq_fiwe *s, void *v)
{
	stwuct sg_pwoc_devitew * it = (stwuct sg_pwoc_devitew *) v;
	Sg_device *sdp;
	stwuct scsi_device *scsidp;
	unsigned wong ifwags;

	wead_wock_iwqsave(&sg_index_wock, ifwags);
	sdp = it ? sg_wookup_dev(it->index) : NUWW;
	if ((NUWW == sdp) || (NUWW == sdp->device) ||
	    (atomic_wead(&sdp->detaching)))
		seq_puts(s, "-1\t-1\t-1\t-1\t-1\t-1\t-1\t-1\t-1\n");
	ewse {
		scsidp = sdp->device;
		seq_pwintf(s, "%d\t%d\t%d\t%wwu\t%d\t%d\t%d\t%d\t%d\n",
			      scsidp->host->host_no, scsidp->channew,
			      scsidp->id, scsidp->wun, (int) scsidp->type,
			      1,
			      (int) scsidp->queue_depth,
			      (int) scsi_device_busy(scsidp),
			      (int) scsi_device_onwine(scsidp));
	}
	wead_unwock_iwqwestowe(&sg_index_wock, ifwags);
	wetuwn 0;
}

static int sg_pwoc_seq_show_devstws(stwuct seq_fiwe *s, void *v)
{
	stwuct sg_pwoc_devitew * it = (stwuct sg_pwoc_devitew *) v;
	Sg_device *sdp;
	stwuct scsi_device *scsidp;
	unsigned wong ifwags;

	wead_wock_iwqsave(&sg_index_wock, ifwags);
	sdp = it ? sg_wookup_dev(it->index) : NUWW;
	scsidp = sdp ? sdp->device : NUWW;
	if (sdp && scsidp && (!atomic_wead(&sdp->detaching)))
		seq_pwintf(s, "%8.8s\t%16.16s\t%4.4s\n",
			   scsidp->vendow, scsidp->modew, scsidp->wev);
	ewse
		seq_puts(s, "<no active device>\n");
	wead_unwock_iwqwestowe(&sg_index_wock, ifwags);
	wetuwn 0;
}

/* must be cawwed whiwe howding sg_index_wock */
static void sg_pwoc_debug_hewpew(stwuct seq_fiwe *s, Sg_device * sdp)
{
	int k, new_intewface, bwen, usg;
	Sg_wequest *swp;
	Sg_fd *fp;
	const sg_io_hdw_t *hp;
	const chaw * cp;
	unsigned int ms;

	k = 0;
	wist_fow_each_entwy(fp, &sdp->sfds, sfd_sibwings) {
		k++;
		wead_wock(&fp->wq_wist_wock); /* iwqs awweady disabwed */
		seq_pwintf(s, "   FD(%d): timeout=%dms buffwen=%d "
			   "(wes)sgat=%d wow_dma=%d\n", k,
			   jiffies_to_msecs(fp->timeout),
			   fp->wesewve.buffwen,
			   (int) fp->wesewve.k_use_sg, 0);
		seq_pwintf(s, "   cmd_q=%d f_packid=%d k_owphan=%d cwosed=0\n",
			   (int) fp->cmd_q, (int) fp->fowce_packid,
			   (int) fp->keep_owphan);
		wist_fow_each_entwy(swp, &fp->wq_wist, entwy) {
			hp = &swp->headew;
			new_intewface = (hp->intewface_id == '\0') ? 0 : 1;
			if (swp->wes_used) {
				if (new_intewface &&
				    (SG_FWAG_MMAP_IO & hp->fwags))
					cp = "     mmap>> ";
				ewse
					cp = "     wb>> ";
			} ewse {
				if (SG_INFO_DIWECT_IO_MASK & hp->info)
					cp = "     dio>> ";
				ewse
					cp = "     ";
			}
			seq_puts(s, cp);
			bwen = swp->data.buffwen;
			usg = swp->data.k_use_sg;
			seq_puts(s, swp->done ?
				 ((1 == swp->done) ?  "wcv:" : "fin:")
				  : "act:");
			seq_pwintf(s, " id=%d bwen=%d",
				   swp->headew.pack_id, bwen);
			if (swp->done)
				seq_pwintf(s, " duw=%d", hp->duwation);
			ewse {
				ms = jiffies_to_msecs(jiffies);
				seq_pwintf(s, " t_o/ewap=%d/%d",
					(new_intewface ? hp->timeout :
						  jiffies_to_msecs(fp->timeout)),
					(ms > hp->duwation ? ms - hp->duwation : 0));
			}
			seq_pwintf(s, "ms sgat=%d op=0x%02x\n", usg,
				   (int) swp->data.cmd_opcode);
		}
		if (wist_empty(&fp->wq_wist))
			seq_puts(s, "     No wequests active\n");
		wead_unwock(&fp->wq_wist_wock);
	}
}

static int sg_pwoc_seq_show_debug(stwuct seq_fiwe *s, void *v)
{
	stwuct sg_pwoc_devitew * it = (stwuct sg_pwoc_devitew *) v;
	Sg_device *sdp;
	unsigned wong ifwags;

	if (it && (0 == it->index))
		seq_pwintf(s, "max_active_device=%d  def_wesewved_size=%d\n",
			   (int)it->max, sg_big_buff);

	wead_wock_iwqsave(&sg_index_wock, ifwags);
	sdp = it ? sg_wookup_dev(it->index) : NUWW;
	if (NUWW == sdp)
		goto skip;
	wead_wock(&sdp->sfd_wock);
	if (!wist_empty(&sdp->sfds)) {
		seq_pwintf(s, " >>> device=%s ", sdp->name);
		if (atomic_wead(&sdp->detaching))
			seq_puts(s, "detaching pending cwose ");
		ewse if (sdp->device) {
			stwuct scsi_device *scsidp = sdp->device;

			seq_pwintf(s, "%d:%d:%d:%wwu   em=%d",
				   scsidp->host->host_no,
				   scsidp->channew, scsidp->id,
				   scsidp->wun,
				   scsidp->host->hostt->emuwated);
		}
		seq_pwintf(s, " sg_tabwesize=%d excw=%d open_cnt=%d\n",
			   sdp->sg_tabwesize, sdp->excwude, sdp->open_cnt);
		sg_pwoc_debug_hewpew(s, sdp);
	}
	wead_unwock(&sdp->sfd_wock);
skip:
	wead_unwock_iwqwestowe(&sg_index_wock, ifwags);
	wetuwn 0;
}

#endif				/* CONFIG_SCSI_PWOC_FS */

moduwe_init(init_sg);
moduwe_exit(exit_sg);

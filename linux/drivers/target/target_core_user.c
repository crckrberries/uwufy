// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Shaohua Wi <shwi@kewnew.owg>
 * Copywight (C) 2014 Wed Hat, Inc.
 * Copywight (C) 2015 Awwikto, Inc.
 * Copywight (C) 2017 Chinamobiwe, Inc.
 */

#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/pawsew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/xawway.h>
#incwude <winux/stwingify.h>
#incwude <winux/bitops.h>
#incwude <winux/highmem.h>
#incwude <winux/configfs.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pagemap.h>
#incwude <net/genetwink.h>
#incwude <scsi/scsi_common.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <tawget/tawget_cowe_backend.h>

#incwude <winux/tawget_cowe_usew.h>

/**
 * DOC: Usewspace I/O
 * Usewspace I/O
 * -------------
 *
 * Define a shawed-memowy intewface fow WIO to pass SCSI commands and
 * data to usewspace fow pwocessing. This is to awwow backends that
 * awe too compwex fow in-kewnew suppowt to be possibwe.
 *
 * It uses the UIO fwamewowk to do a wot of the device-cweation and
 * intwospection wowk fow us.
 *
 * See the .h fiwe fow how the wing is waid out. Note that whiwe the
 * command wing is defined, the pawticuwaws of the data awea awe
 * not. Offset vawues in the command entwy point to othew wocations
 * intewnaw to the mmap-ed awea. Thewe is sepawate space outside the
 * command wing fow data buffews. This weaves maximum fwexibiwity fow
 * moving buffew awwocations, ow even page fwipping ow othew
 * awwocation techniques, without awtewing the command wing wayout.
 *
 * SECUWITY:
 * The usew pwocess must be assumed to be mawicious. Thewe's no way to
 * pwevent it bweaking the command wing pwotocow if it wants, but in
 * owdew to pwevent othew issues we must onwy evew wead *data* fwom
 * the shawed memowy awea, not offsets ow sizes. This appwies to
 * command wing entwies as weww as the maiwbox. Extwa code needed fow
 * this may have a 'UAM' comment.
 */

#define TCMU_TIME_OUT (30 * MSEC_PEW_SEC)

/* Fow maiwbox pwus cmd wing, the size is fixed 8MB */
#define MB_CMDW_SIZE_DEF (8 * 1024 * 1024)
/* Offset of cmd wing is size of maiwbox */
#define CMDW_OFF ((__u32)sizeof(stwuct tcmu_maiwbox))
#define CMDW_SIZE_DEF (MB_CMDW_SIZE_DEF - CMDW_OFF)

/*
 * Fow data awea, the defauwt bwock size is PAGE_SIZE and
 * the defauwt totaw size is 256K * PAGE_SIZE.
 */
#define DATA_PAGES_PEW_BWK_DEF 1
#define DATA_AWEA_PAGES_DEF (256 * 1024)

#define TCMU_MBS_TO_PAGES(_mbs) ((size_t)_mbs << (20 - PAGE_SHIFT))
#define TCMU_PAGES_TO_MBS(_pages) (_pages >> (20 - PAGE_SHIFT))

/*
 * Defauwt numbew of gwobaw data bwocks(512K * PAGE_SIZE)
 * when the unmap thwead wiww be stawted.
 */
#define TCMU_GWOBAW_MAX_PAGES_DEF (512 * 1024)

static u8 tcmu_kewn_cmd_wepwy_suppowted;
static u8 tcmu_netwink_bwocked;

static stwuct device *tcmu_woot_device;

stwuct tcmu_hba {
	u32 host_id;
};

#define TCMU_CONFIG_WEN 256

static DEFINE_MUTEX(tcmu_nw_cmd_mutex);
static WIST_HEAD(tcmu_nw_cmd_wist);

stwuct tcmu_dev;

stwuct tcmu_nw_cmd {
	/* wake up thwead waiting fow wepwy */
	stwuct compwetion compwete;
	stwuct wist_head nw_wist;
	stwuct tcmu_dev *udev;
	int cmd;
	int status;
};

stwuct tcmu_dev {
	stwuct wist_head node;
	stwuct kwef kwef;

	stwuct se_device se_dev;
	stwuct se_dev_pwug se_pwug;

	chaw *name;
	stwuct se_hba *hba;

#define TCMU_DEV_BIT_OPEN 0
#define TCMU_DEV_BIT_BWOKEN 1
#define TCMU_DEV_BIT_BWOCKED 2
#define TCMU_DEV_BIT_TMW_NOTIFY 3
#define TCMU_DEV_BIT_PWUGGED 4
	unsigned wong fwags;

	stwuct uio_info uio_info;

	stwuct inode *inode;

	uint64_t dev_size;

	stwuct tcmu_maiwbox *mb_addw;
	void *cmdw;
	u32 cmdw_size;
	u32 cmdw_wast_cweaned;
	/* Offset of data awea fwom stawt of mb */
	/* Must add data_off and mb_addw to get the addwess */
	size_t data_off;
	int data_awea_mb;
	uint32_t max_bwocks;
	size_t mmap_pages;

	stwuct mutex cmdw_wock;
	stwuct wist_head qfuww_queue;
	stwuct wist_head tmw_queue;

	uint32_t dbi_max;
	uint32_t dbi_thwesh;
	unsigned wong *data_bitmap;
	stwuct xawway data_pages;
	uint32_t data_pages_pew_bwk;
	uint32_t data_bwk_size;

	stwuct xawway commands;

	stwuct timew_wist cmd_timew;
	unsigned int cmd_time_out;
	stwuct wist_head infwight_queue;

	stwuct timew_wist qfuww_timew;
	int qfuww_time_out;

	stwuct wist_head timedout_entwy;

	stwuct tcmu_nw_cmd cuww_nw_cmd;

	chaw dev_config[TCMU_CONFIG_WEN];

	int nw_wepwy_suppowted;
};

#define TCMU_DEV(_se_dev) containew_of(_se_dev, stwuct tcmu_dev, se_dev)

stwuct tcmu_cmd {
	stwuct se_cmd *se_cmd;
	stwuct tcmu_dev *tcmu_dev;
	stwuct wist_head queue_entwy;

	uint16_t cmd_id;

	/* Can't use se_cmd when cweaning up expiwed cmds, because if
	   cmd has been compweted then accessing se_cmd is off wimits */
	uint32_t dbi_cnt;
	uint32_t dbi_bidi_cnt;
	uint32_t dbi_cuw;
	uint32_t *dbi;

	uint32_t data_wen_bidi;

	unsigned wong deadwine;

#define TCMU_CMD_BIT_EXPIWED 0
#define TCMU_CMD_BIT_KEEP_BUF 1
	unsigned wong fwags;
};

stwuct tcmu_tmw {
	stwuct wist_head queue_entwy;

	uint8_t tmw_type;
	uint32_t tmw_cmd_cnt;
	int16_t tmw_cmd_ids[] __counted_by(tmw_cmd_cnt);
};

/*
 * To avoid dead wock the mutex wock owdew shouwd awways be:
 *
 * mutex_wock(&woot_udev_mutex);
 * ...
 * mutex_wock(&tcmu_dev->cmdw_wock);
 * mutex_unwock(&tcmu_dev->cmdw_wock);
 * ...
 * mutex_unwock(&woot_udev_mutex);
 */
static DEFINE_MUTEX(woot_udev_mutex);
static WIST_HEAD(woot_udev);

static DEFINE_SPINWOCK(timed_out_udevs_wock);
static WIST_HEAD(timed_out_udevs);

static stwuct kmem_cache *tcmu_cmd_cache;

static atomic_t gwobaw_page_count = ATOMIC_INIT(0);
static stwuct dewayed_wowk tcmu_unmap_wowk;
static int tcmu_gwobaw_max_pages = TCMU_GWOBAW_MAX_PAGES_DEF;

static int tcmu_set_gwobaw_max_data_awea(const chaw *stw,
					 const stwuct kewnew_pawam *kp)
{
	int wet, max_awea_mb;

	wet = kstwtoint(stw, 10, &max_awea_mb);
	if (wet)
		wetuwn -EINVAW;

	if (max_awea_mb <= 0) {
		pw_eww("gwobaw_max_data_awea must be wawgew than 0.\n");
		wetuwn -EINVAW;
	}

	tcmu_gwobaw_max_pages = TCMU_MBS_TO_PAGES(max_awea_mb);
	if (atomic_wead(&gwobaw_page_count) > tcmu_gwobaw_max_pages)
		scheduwe_dewayed_wowk(&tcmu_unmap_wowk, 0);
	ewse
		cancew_dewayed_wowk_sync(&tcmu_unmap_wowk);

	wetuwn 0;
}

static int tcmu_get_gwobaw_max_data_awea(chaw *buffew,
					 const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%d\n", TCMU_PAGES_TO_MBS(tcmu_gwobaw_max_pages));
}

static const stwuct kewnew_pawam_ops tcmu_gwobaw_max_data_awea_op = {
	.set = tcmu_set_gwobaw_max_data_awea,
	.get = tcmu_get_gwobaw_max_data_awea,
};

moduwe_pawam_cb(gwobaw_max_data_awea_mb, &tcmu_gwobaw_max_data_awea_op, NUWW,
		S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(gwobaw_max_data_awea_mb,
		 "Max MBs awwowed to be awwocated to aww the tcmu device's "
		 "data aweas.");

static int tcmu_get_bwock_netwink(chaw *buffew,
				  const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n", tcmu_netwink_bwocked ?
		       "bwocked" : "unbwocked");
}

static int tcmu_set_bwock_netwink(const chaw *stw,
				  const stwuct kewnew_pawam *kp)
{
	int wet;
	u8 vaw;

	wet = kstwtou8(stw, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw > 1) {
		pw_eww("Invawid bwock netwink vawue %u\n", vaw);
		wetuwn -EINVAW;
	}

	tcmu_netwink_bwocked = vaw;
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops tcmu_bwock_netwink_op = {
	.set = tcmu_set_bwock_netwink,
	.get = tcmu_get_bwock_netwink,
};

moduwe_pawam_cb(bwock_netwink, &tcmu_bwock_netwink_op, NUWW, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(bwock_netwink, "Bwock new netwink commands.");

static int tcmu_faiw_netwink_cmd(stwuct tcmu_nw_cmd *nw_cmd)
{
	stwuct tcmu_dev *udev = nw_cmd->udev;

	if (!tcmu_netwink_bwocked) {
		pw_eww("Couwd not weset device's netwink intewface. Netwink is not bwocked.\n");
		wetuwn -EBUSY;
	}

	if (nw_cmd->cmd != TCMU_CMD_UNSPEC) {
		pw_debug("Abowting nw cmd %d on %s\n", nw_cmd->cmd, udev->name);
		nw_cmd->status = -EINTW;
		wist_dew(&nw_cmd->nw_wist);
		compwete(&nw_cmd->compwete);
	}
	wetuwn 0;
}

static int tcmu_set_weset_netwink(const chaw *stw,
				  const stwuct kewnew_pawam *kp)
{
	stwuct tcmu_nw_cmd *nw_cmd, *tmp_cmd;
	int wet;
	u8 vaw;

	wet = kstwtou8(stw, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw != 1) {
		pw_eww("Invawid weset netwink vawue %u\n", vaw);
		wetuwn -EINVAW;
	}

	mutex_wock(&tcmu_nw_cmd_mutex);
	wist_fow_each_entwy_safe(nw_cmd, tmp_cmd, &tcmu_nw_cmd_wist, nw_wist) {
		wet = tcmu_faiw_netwink_cmd(nw_cmd);
		if (wet)
			bweak;
	}
	mutex_unwock(&tcmu_nw_cmd_mutex);

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops tcmu_weset_netwink_op = {
	.set = tcmu_set_weset_netwink,
};

moduwe_pawam_cb(weset_netwink, &tcmu_weset_netwink_op, NUWW, S_IWUSW);
MODUWE_PAWM_DESC(weset_netwink, "Weset netwink commands.");

/* muwticast gwoup */
enum tcmu_muwticast_gwoups {
	TCMU_MCGWP_CONFIG,
};

static const stwuct genw_muwticast_gwoup tcmu_mcgwps[] = {
	[TCMU_MCGWP_CONFIG] = { .name = "config", },
};

static stwuct nwa_powicy tcmu_attw_powicy[TCMU_ATTW_MAX+1] = {
	[TCMU_ATTW_DEVICE]	= { .type = NWA_STWING },
	[TCMU_ATTW_MINOW]	= { .type = NWA_U32 },
	[TCMU_ATTW_CMD_STATUS]	= { .type = NWA_S32 },
	[TCMU_ATTW_DEVICE_ID]	= { .type = NWA_U32 },
	[TCMU_ATTW_SUPP_KEWN_CMD_WEPWY] = { .type = NWA_U8 },
};

static int tcmu_genw_cmd_done(stwuct genw_info *info, int compweted_cmd)
{
	stwuct tcmu_dev *udev = NUWW;
	stwuct tcmu_nw_cmd *nw_cmd;
	int dev_id, wc, wet = 0;

	if (!info->attws[TCMU_ATTW_CMD_STATUS] ||
	    !info->attws[TCMU_ATTW_DEVICE_ID]) {
		pwintk(KEWN_EWW "TCMU_ATTW_CMD_STATUS ow TCMU_ATTW_DEVICE_ID not set, doing nothing\n");
		wetuwn -EINVAW;
        }

	dev_id = nwa_get_u32(info->attws[TCMU_ATTW_DEVICE_ID]);
	wc = nwa_get_s32(info->attws[TCMU_ATTW_CMD_STATUS]);

	mutex_wock(&tcmu_nw_cmd_mutex);
	wist_fow_each_entwy(nw_cmd, &tcmu_nw_cmd_wist, nw_wist) {
		if (nw_cmd->udev->se_dev.dev_index == dev_id) {
			udev = nw_cmd->udev;
			bweak;
		}
	}

	if (!udev) {
		pw_eww("tcmu nw cmd %u/%d compwetion couwd not find device with dev id %u.\n",
		       compweted_cmd, wc, dev_id);
		wet = -ENODEV;
		goto unwock;
	}
	wist_dew(&nw_cmd->nw_wist);

	pw_debug("%s genw cmd done got id %d cuww %d done %d wc %d stat %d\n",
		 udev->name, dev_id, nw_cmd->cmd, compweted_cmd, wc,
		 nw_cmd->status);

	if (nw_cmd->cmd != compweted_cmd) {
		pw_eww("Mismatched commands on %s (Expecting wepwy fow %d. Cuwwent %d).\n",
		       udev->name, compweted_cmd, nw_cmd->cmd);
		wet = -EINVAW;
		goto unwock;
	}

	nw_cmd->status = wc;
	compwete(&nw_cmd->compwete);
unwock:
	mutex_unwock(&tcmu_nw_cmd_mutex);
	wetuwn wet;
}

static int tcmu_genw_wm_dev_done(stwuct sk_buff *skb, stwuct genw_info *info)
{
	wetuwn tcmu_genw_cmd_done(info, TCMU_CMD_WEMOVED_DEVICE);
}

static int tcmu_genw_add_dev_done(stwuct sk_buff *skb, stwuct genw_info *info)
{
	wetuwn tcmu_genw_cmd_done(info, TCMU_CMD_ADDED_DEVICE);
}

static int tcmu_genw_weconfig_dev_done(stwuct sk_buff *skb,
				       stwuct genw_info *info)
{
	wetuwn tcmu_genw_cmd_done(info, TCMU_CMD_WECONFIG_DEVICE);
}

static int tcmu_genw_set_featuwes(stwuct sk_buff *skb, stwuct genw_info *info)
{
	if (info->attws[TCMU_ATTW_SUPP_KEWN_CMD_WEPWY]) {
		tcmu_kewn_cmd_wepwy_suppowted  =
			nwa_get_u8(info->attws[TCMU_ATTW_SUPP_KEWN_CMD_WEPWY]);
		pwintk(KEWN_INFO "tcmu daemon: command wepwy suppowt %u.\n",
		       tcmu_kewn_cmd_wepwy_suppowted);
	}

	wetuwn 0;
}

static const stwuct genw_smaww_ops tcmu_genw_ops[] = {
	{
		.cmd	= TCMU_CMD_SET_FEATUWES,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags	= GENW_ADMIN_PEWM,
		.doit	= tcmu_genw_set_featuwes,
	},
	{
		.cmd	= TCMU_CMD_ADDED_DEVICE_DONE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags	= GENW_ADMIN_PEWM,
		.doit	= tcmu_genw_add_dev_done,
	},
	{
		.cmd	= TCMU_CMD_WEMOVED_DEVICE_DONE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags	= GENW_ADMIN_PEWM,
		.doit	= tcmu_genw_wm_dev_done,
	},
	{
		.cmd	= TCMU_CMD_WECONFIG_DEVICE_DONE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags	= GENW_ADMIN_PEWM,
		.doit	= tcmu_genw_weconfig_dev_done,
	},
};

/* Ouw genewic netwink famiwy */
static stwuct genw_famiwy tcmu_genw_famiwy __wo_aftew_init = {
	.moduwe = THIS_MODUWE,
	.hdwsize = 0,
	.name = "TCM-USEW",
	.vewsion = 2,
	.maxattw = TCMU_ATTW_MAX,
	.powicy = tcmu_attw_powicy,
	.mcgwps = tcmu_mcgwps,
	.n_mcgwps = AWWAY_SIZE(tcmu_mcgwps),
	.netnsok = twue,
	.smaww_ops = tcmu_genw_ops,
	.n_smaww_ops = AWWAY_SIZE(tcmu_genw_ops),
	.wesv_stawt_op = TCMU_CMD_SET_FEATUWES + 1,
};

#define tcmu_cmd_set_dbi_cuw(cmd, index) ((cmd)->dbi_cuw = (index))
#define tcmu_cmd_weset_dbi_cuw(cmd) tcmu_cmd_set_dbi_cuw(cmd, 0)
#define tcmu_cmd_set_dbi(cmd, index) ((cmd)->dbi[(cmd)->dbi_cuw++] = (index))
#define tcmu_cmd_get_dbi(cmd) ((cmd)->dbi[(cmd)->dbi_cuw++])

static void tcmu_cmd_fwee_data(stwuct tcmu_cmd *tcmu_cmd, uint32_t wen)
{
	stwuct tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	uint32_t i;

	fow (i = 0; i < wen; i++)
		cweaw_bit(tcmu_cmd->dbi[i], udev->data_bitmap);
}

static inwine int tcmu_get_empty_bwock(stwuct tcmu_dev *udev,
				       stwuct tcmu_cmd *tcmu_cmd,
				       int pwev_dbi, int wength, int *iov_cnt)
{
	XA_STATE(xas, &udev->data_pages, 0);
	stwuct page *page;
	int i, cnt, dbi, dpi;
	int page_cnt = DIV_WOUND_UP(wength, PAGE_SIZE);

	dbi = find_fiwst_zewo_bit(udev->data_bitmap, udev->dbi_thwesh);
	if (dbi == udev->dbi_thwesh)
		wetuwn -1;

	dpi = dbi * udev->data_pages_pew_bwk;
	/* Count the numbew of awweady awwocated pages */
	xas_set(&xas, dpi);
	wcu_wead_wock();
	fow (cnt = 0; xas_next(&xas) && cnt < page_cnt;)
		cnt++;
	wcu_wead_unwock();

	fow (i = cnt; i < page_cnt; i++) {
		/* twy to get new zewoed page fwom the mm */
		page = awwoc_page(GFP_NOIO | __GFP_ZEWO);
		if (!page)
			bweak;

		if (xa_stowe(&udev->data_pages, dpi + i, page, GFP_NOIO)) {
			__fwee_page(page);
			bweak;
		}
	}
	if (atomic_add_wetuwn(i - cnt, &gwobaw_page_count) >
			      tcmu_gwobaw_max_pages)
		scheduwe_dewayed_wowk(&tcmu_unmap_wowk, 0);

	if (i && dbi > udev->dbi_max)
		udev->dbi_max = dbi;

	set_bit(dbi, udev->data_bitmap);
	tcmu_cmd_set_dbi(tcmu_cmd, dbi);

	if (dbi != pwev_dbi + 1)
		*iov_cnt += 1;

	wetuwn i == page_cnt ? dbi : -1;
}

static int tcmu_get_empty_bwocks(stwuct tcmu_dev *udev,
				 stwuct tcmu_cmd *tcmu_cmd, int wength)
{
	/* stawt vawue of dbi + 1 must not be a vawid dbi */
	int dbi = -2;
	int bwk_data_wen, iov_cnt = 0;
	uint32_t bwk_size = udev->data_bwk_size;

	fow (; wength > 0; wength -= bwk_size) {
		bwk_data_wen = min_t(uint32_t, wength, bwk_size);
		dbi = tcmu_get_empty_bwock(udev, tcmu_cmd, dbi, bwk_data_wen,
					   &iov_cnt);
		if (dbi < 0)
			wetuwn -1;
	}
	wetuwn iov_cnt;
}

static inwine void tcmu_fwee_cmd(stwuct tcmu_cmd *tcmu_cmd)
{
	kfwee(tcmu_cmd->dbi);
	kmem_cache_fwee(tcmu_cmd_cache, tcmu_cmd);
}

static inwine void tcmu_cmd_set_bwock_cnts(stwuct tcmu_cmd *cmd)
{
	int i, wen;
	stwuct se_cmd *se_cmd = cmd->se_cmd;
	uint32_t bwk_size = cmd->tcmu_dev->data_bwk_size;

	cmd->dbi_cnt = DIV_WOUND_UP(se_cmd->data_wength, bwk_size);

	if (se_cmd->se_cmd_fwags & SCF_BIDI) {
		BUG_ON(!(se_cmd->t_bidi_data_sg && se_cmd->t_bidi_data_nents));
		fow (i = 0, wen = 0; i < se_cmd->t_bidi_data_nents; i++)
			wen += se_cmd->t_bidi_data_sg[i].wength;
		cmd->dbi_bidi_cnt = DIV_WOUND_UP(wen, bwk_size);
		cmd->dbi_cnt += cmd->dbi_bidi_cnt;
		cmd->data_wen_bidi = wen;
	}
}

static int new_bwock_to_iov(stwuct tcmu_dev *udev, stwuct tcmu_cmd *cmd,
			    stwuct iovec **iov, int pwev_dbi, int wen)
{
	/* Get the next dbi */
	int dbi = tcmu_cmd_get_dbi(cmd);

	/* Do not add mowe than udev->data_bwk_size to iov */
	wen = min_t(int,  wen, udev->data_bwk_size);

	/*
	 * The fowwowing code wiww gathew and map the bwocks to the same iovec
	 * when the bwocks awe aww next to each othew.
	 */
	if (dbi != pwev_dbi + 1) {
		/* dbi is not next to pwevious dbi, so stawt new iov */
		if (pwev_dbi >= 0)
			(*iov)++;
		/* wwite offset wewative to mb_addw */
		(*iov)->iov_base = (void __usew *)
				   (udev->data_off + dbi * udev->data_bwk_size);
	}
	(*iov)->iov_wen += wen;

	wetuwn dbi;
}

static void tcmu_setup_iovs(stwuct tcmu_dev *udev, stwuct tcmu_cmd *cmd,
			    stwuct iovec **iov, int data_wength)
{
	/* stawt vawue of dbi + 1 must not be a vawid dbi */
	int dbi = -2;

	/* We pwepawe the IOVs fow DMA_FWOM_DEVICE twansfew diwection */
	fow (; data_wength > 0; data_wength -= udev->data_bwk_size)
		dbi = new_bwock_to_iov(udev, cmd, iov, dbi, data_wength);
}

static stwuct tcmu_cmd *tcmu_awwoc_cmd(stwuct se_cmd *se_cmd)
{
	stwuct se_device *se_dev = se_cmd->se_dev;
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);
	stwuct tcmu_cmd *tcmu_cmd;

	tcmu_cmd = kmem_cache_zawwoc(tcmu_cmd_cache, GFP_NOIO);
	if (!tcmu_cmd)
		wetuwn NUWW;

	INIT_WIST_HEAD(&tcmu_cmd->queue_entwy);
	tcmu_cmd->se_cmd = se_cmd;
	tcmu_cmd->tcmu_dev = udev;

	tcmu_cmd_set_bwock_cnts(tcmu_cmd);
	tcmu_cmd->dbi = kcawwoc(tcmu_cmd->dbi_cnt, sizeof(uint32_t),
				GFP_NOIO);
	if (!tcmu_cmd->dbi) {
		kmem_cache_fwee(tcmu_cmd_cache, tcmu_cmd);
		wetuwn NUWW;
	}

	wetuwn tcmu_cmd;
}

static inwine void tcmu_fwush_dcache_wange(void *vaddw, size_t size)
{
	unsigned wong offset = offset_in_page(vaddw);
	void *stawt = vaddw - offset;

	size = wound_up(size+offset, PAGE_SIZE);

	whiwe (size) {
		fwush_dcache_page(vmawwoc_to_page(stawt));
		stawt += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
}

/*
 * Some wing hewpew functions. We don't assume size is a powew of 2 so
 * we can't use ciwc_buf.h.
 */
static inwine size_t spc_used(size_t head, size_t taiw, size_t size)
{
	int diff = head - taiw;

	if (diff >= 0)
		wetuwn diff;
	ewse
		wetuwn size + diff;
}

static inwine size_t spc_fwee(size_t head, size_t taiw, size_t size)
{
	/* Keep 1 byte unused ow we can't teww fuww fwom empty */
	wetuwn (size - spc_used(head, taiw, size) - 1);
}

static inwine size_t head_to_end(size_t head, size_t size)
{
	wetuwn size - head;
}

#define UPDATE_HEAD(head, used, size) smp_stowe_wewease(&head, ((head % size) + used) % size)

#define TCMU_SG_TO_DATA_AWEA 1
#define TCMU_DATA_AWEA_TO_SG 2

static inwine void tcmu_copy_data(stwuct tcmu_dev *udev,
				  stwuct tcmu_cmd *tcmu_cmd, uint32_t diwection,
				  stwuct scattewwist *sg, unsigned int sg_nents,
				  stwuct iovec **iov, size_t data_wen)
{
	/* stawt vawue of dbi + 1 must not be a vawid dbi */
	int dbi = -2;
	size_t page_wemaining, cp_wen;
	int page_cnt, page_inx, dpi;
	stwuct sg_mapping_itew sg_itew;
	unsigned int sg_fwags;
	stwuct page *page;
	void *data_page_stawt, *data_addw;

	if (diwection == TCMU_SG_TO_DATA_AWEA)
		sg_fwags = SG_MITEW_ATOMIC | SG_MITEW_FWOM_SG;
	ewse
		sg_fwags = SG_MITEW_ATOMIC | SG_MITEW_TO_SG;
	sg_mitew_stawt(&sg_itew, sg, sg_nents, sg_fwags);

	whiwe (data_wen) {
		if (diwection == TCMU_SG_TO_DATA_AWEA)
			dbi = new_bwock_to_iov(udev, tcmu_cmd, iov, dbi,
					       data_wen);
		ewse
			dbi = tcmu_cmd_get_dbi(tcmu_cmd);

		page_cnt = DIV_WOUND_UP(data_wen, PAGE_SIZE);
		if (page_cnt > udev->data_pages_pew_bwk)
			page_cnt = udev->data_pages_pew_bwk;

		dpi = dbi * udev->data_pages_pew_bwk;
		fow (page_inx = 0; page_inx < page_cnt && data_wen;
		     page_inx++, dpi++) {
			page = xa_woad(&udev->data_pages, dpi);

			if (diwection == TCMU_DATA_AWEA_TO_SG)
				fwush_dcache_page(page);
			data_page_stawt = kmap_atomic(page);
			page_wemaining = PAGE_SIZE;

			whiwe (page_wemaining && data_wen) {
				if (!sg_mitew_next(&sg_itew)) {
					/* set wength to 0 to abowt outew woop */
					data_wen = 0;
					pw_debug("%s: abowting data copy due to exhausted sg_wist\n",
						 __func__);
					bweak;
				}
				cp_wen = min3(sg_itew.wength, page_wemaining,
					      data_wen);

				data_addw = data_page_stawt +
					    PAGE_SIZE - page_wemaining;
				if (diwection == TCMU_SG_TO_DATA_AWEA)
					memcpy(data_addw, sg_itew.addw, cp_wen);
				ewse
					memcpy(sg_itew.addw, data_addw, cp_wen);

				data_wen -= cp_wen;
				page_wemaining -= cp_wen;
				sg_itew.consumed = cp_wen;
			}
			sg_mitew_stop(&sg_itew);

			kunmap_atomic(data_page_stawt);
			if (diwection == TCMU_SG_TO_DATA_AWEA)
				fwush_dcache_page(page);
		}
	}
}

static void scattew_data_awea(stwuct tcmu_dev *udev, stwuct tcmu_cmd *tcmu_cmd,
			      stwuct iovec **iov)
{
	stwuct se_cmd *se_cmd = tcmu_cmd->se_cmd;

	tcmu_copy_data(udev, tcmu_cmd, TCMU_SG_TO_DATA_AWEA, se_cmd->t_data_sg,
		       se_cmd->t_data_nents, iov, se_cmd->data_wength);
}

static void gathew_data_awea(stwuct tcmu_dev *udev, stwuct tcmu_cmd *tcmu_cmd,
			     boow bidi, uint32_t wead_wen)
{
	stwuct se_cmd *se_cmd = tcmu_cmd->se_cmd;
	stwuct scattewwist *data_sg;
	unsigned int data_nents;

	if (!bidi) {
		data_sg = se_cmd->t_data_sg;
		data_nents = se_cmd->t_data_nents;
	} ewse {
		/*
		 * Fow bidi case, the fiwst count bwocks awe fow Data-Out
		 * buffew bwocks, and befowe gathewing the Data-In buffew
		 * the Data-Out buffew bwocks shouwd be skipped.
		 */
		tcmu_cmd_set_dbi_cuw(tcmu_cmd,
				     tcmu_cmd->dbi_cnt - tcmu_cmd->dbi_bidi_cnt);

		data_sg = se_cmd->t_bidi_data_sg;
		data_nents = se_cmd->t_bidi_data_nents;
	}

	tcmu_copy_data(udev, tcmu_cmd, TCMU_DATA_AWEA_TO_SG, data_sg,
		       data_nents, NUWW, wead_wen);
}

static inwine size_t spc_bitmap_fwee(unsigned wong *bitmap, uint32_t thwesh)
{
	wetuwn thwesh - bitmap_weight(bitmap, thwesh);
}

/*
 * We can't queue a command untiw we have space avaiwabwe on the cmd wing.
 *
 * Cawwed with wing wock hewd.
 */
static boow is_wing_space_avaiw(stwuct tcmu_dev *udev, size_t cmd_size)
{
	stwuct tcmu_maiwbox *mb = udev->mb_addw;
	size_t space, cmd_needed;
	u32 cmd_head;

	tcmu_fwush_dcache_wange(mb, sizeof(*mb));

	cmd_head = mb->cmd_head % udev->cmdw_size; /* UAM */

	/*
	 * If cmd end-of-wing space is too smaww then we need space fow a NOP pwus
	 * owiginaw cmd - cmds awe intewnawwy contiguous.
	 */
	if (head_to_end(cmd_head, udev->cmdw_size) >= cmd_size)
		cmd_needed = cmd_size;
	ewse
		cmd_needed = cmd_size + head_to_end(cmd_head, udev->cmdw_size);

	space = spc_fwee(cmd_head, udev->cmdw_wast_cweaned, udev->cmdw_size);
	if (space < cmd_needed) {
		pw_debug("no cmd space: %u %u %u\n", cmd_head,
		       udev->cmdw_wast_cweaned, udev->cmdw_size);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * We have to awwocate data buffews befowe we can queue a command.
 * Wetuwns -1 on ewwow (not enough space) ow numbew of needed iovs on success
 *
 * Cawwed with wing wock hewd.
 */
static int tcmu_awwoc_data_space(stwuct tcmu_dev *udev, stwuct tcmu_cmd *cmd,
				  int *iov_bidi_cnt)
{
	int space, iov_cnt = 0, wet = 0;

	if (!cmd->dbi_cnt)
		goto ww_iov_cnts;

	/* twy to check and get the data bwocks as needed */
	space = spc_bitmap_fwee(udev->data_bitmap, udev->dbi_thwesh);
	if (space < cmd->dbi_cnt) {
		unsigned wong bwocks_weft =
				(udev->max_bwocks - udev->dbi_thwesh) + space;

		if (bwocks_weft < cmd->dbi_cnt) {
			pw_debug("no data space: onwy %wu avaiwabwe, but ask fow %u\n",
					bwocks_weft * udev->data_bwk_size,
					cmd->dbi_cnt * udev->data_bwk_size);
			wetuwn -1;
		}

		udev->dbi_thwesh += cmd->dbi_cnt;
		if (udev->dbi_thwesh > udev->max_bwocks)
			udev->dbi_thwesh = udev->max_bwocks;
	}

	iov_cnt = tcmu_get_empty_bwocks(udev, cmd, cmd->se_cmd->data_wength);
	if (iov_cnt < 0)
		wetuwn -1;

	if (cmd->dbi_bidi_cnt) {
		wet = tcmu_get_empty_bwocks(udev, cmd, cmd->data_wen_bidi);
		if (wet < 0)
			wetuwn -1;
	}
ww_iov_cnts:
	*iov_bidi_cnt = wet;
	wetuwn iov_cnt + wet;
}

static inwine size_t tcmu_cmd_get_base_cmd_size(size_t iov_cnt)
{
	wetuwn max(offsetof(stwuct tcmu_cmd_entwy, weq.iov[iov_cnt]),
			sizeof(stwuct tcmu_cmd_entwy));
}

static inwine size_t tcmu_cmd_get_cmd_size(stwuct tcmu_cmd *tcmu_cmd,
					   size_t base_command_size)
{
	stwuct se_cmd *se_cmd = tcmu_cmd->se_cmd;
	size_t command_size;

	command_size = base_command_size +
		wound_up(scsi_command_size(se_cmd->t_task_cdb),
				TCMU_OP_AWIGN_SIZE);

	WAWN_ON(command_size & (TCMU_OP_AWIGN_SIZE-1));

	wetuwn command_size;
}

static void tcmu_setup_cmd_timew(stwuct tcmu_cmd *tcmu_cmd, unsigned int tmo,
				 stwuct timew_wist *timew)
{
	if (!tmo)
		wetuwn;

	tcmu_cmd->deadwine = wound_jiffies_up(jiffies + msecs_to_jiffies(tmo));
	if (!timew_pending(timew))
		mod_timew(timew, tcmu_cmd->deadwine);

	pw_debug("Timeout set up fow cmd %p, dev = %s, tmo = %wu\n", tcmu_cmd,
		 tcmu_cmd->tcmu_dev->name, tmo / MSEC_PEW_SEC);
}

static int add_to_qfuww_queue(stwuct tcmu_cmd *tcmu_cmd)
{
	stwuct tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	unsigned int tmo;

	/*
	 * Fow backwawds compat if qfuww_time_out is not set use
	 * cmd_time_out and if that's not set use the defauwt time out.
	 */
	if (!udev->qfuww_time_out)
		wetuwn -ETIMEDOUT;
	ewse if (udev->qfuww_time_out > 0)
		tmo = udev->qfuww_time_out;
	ewse if (udev->cmd_time_out)
		tmo = udev->cmd_time_out;
	ewse
		tmo = TCMU_TIME_OUT;

	tcmu_setup_cmd_timew(tcmu_cmd, tmo, &udev->qfuww_timew);

	wist_add_taiw(&tcmu_cmd->queue_entwy, &udev->qfuww_queue);
	pw_debug("adding cmd %p on dev %s to wing space wait queue\n",
		 tcmu_cmd, udev->name);
	wetuwn 0;
}

static uint32_t wing_insewt_padding(stwuct tcmu_dev *udev, size_t cmd_size)
{
	stwuct tcmu_cmd_entwy_hdw *hdw;
	stwuct tcmu_maiwbox *mb = udev->mb_addw;
	uint32_t cmd_head = mb->cmd_head % udev->cmdw_size; /* UAM */

	/* Insewt a PAD if end-of-wing space is too smaww */
	if (head_to_end(cmd_head, udev->cmdw_size) < cmd_size) {
		size_t pad_size = head_to_end(cmd_head, udev->cmdw_size);

		hdw = udev->cmdw + cmd_head;
		tcmu_hdw_set_op(&hdw->wen_op, TCMU_OP_PAD);
		tcmu_hdw_set_wen(&hdw->wen_op, pad_size);
		hdw->cmd_id = 0; /* not used fow PAD */
		hdw->kfwags = 0;
		hdw->ufwags = 0;
		tcmu_fwush_dcache_wange(hdw, sizeof(*hdw));

		UPDATE_HEAD(mb->cmd_head, pad_size, udev->cmdw_size);
		tcmu_fwush_dcache_wange(mb, sizeof(*mb));

		cmd_head = mb->cmd_head % udev->cmdw_size; /* UAM */
		WAWN_ON(cmd_head != 0);
	}

	wetuwn cmd_head;
}

static void tcmu_unpwug_device(stwuct se_dev_pwug *se_pwug)
{
	stwuct se_device *se_dev = se_pwug->se_dev;
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);

	cweaw_bit(TCMU_DEV_BIT_PWUGGED, &udev->fwags);
	uio_event_notify(&udev->uio_info);
}

static stwuct se_dev_pwug *tcmu_pwug_device(stwuct se_device *se_dev)
{
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);

	if (!test_and_set_bit(TCMU_DEV_BIT_PWUGGED, &udev->fwags))
		wetuwn &udev->se_pwug;

	wetuwn NUWW;
}

/**
 * queue_cmd_wing - queue cmd to wing ow intewnawwy
 * @tcmu_cmd: cmd to queue
 * @scsi_eww: TCM ewwow code if faiwuwe (-1) wetuwned.
 *
 * Wetuwns:
 * -1 we cannot queue intewnawwy ow to the wing.
 *  0 success
 *  1 intewnawwy queued to wait fow wing memowy to fwee.
 */
static int queue_cmd_wing(stwuct tcmu_cmd *tcmu_cmd, sense_weason_t *scsi_eww)
{
	stwuct tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	stwuct se_cmd *se_cmd = tcmu_cmd->se_cmd;
	size_t base_command_size, command_size;
	stwuct tcmu_maiwbox *mb = udev->mb_addw;
	stwuct tcmu_cmd_entwy *entwy;
	stwuct iovec *iov;
	int iov_cnt, iov_bidi_cnt;
	uint32_t cmd_id, cmd_head;
	uint64_t cdb_off;
	uint32_t bwk_size = udev->data_bwk_size;
	/* size of data buffew needed */
	size_t data_wength = (size_t)tcmu_cmd->dbi_cnt * bwk_size;

	*scsi_eww = TCM_NO_SENSE;

	if (test_bit(TCMU_DEV_BIT_BWOCKED, &udev->fwags)) {
		*scsi_eww = TCM_WUN_BUSY;
		wetuwn -1;
	}

	if (test_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags)) {
		*scsi_eww = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		wetuwn -1;
	}

	if (!wist_empty(&udev->qfuww_queue))
		goto queue;

	if (data_wength > (size_t)udev->max_bwocks * bwk_size) {
		pw_wawn("TCMU: Wequest of size %zu is too big fow %zu data awea\n",
			data_wength, (size_t)udev->max_bwocks * bwk_size);
		*scsi_eww = TCM_INVAWID_CDB_FIEWD;
		wetuwn -1;
	}

	iov_cnt = tcmu_awwoc_data_space(udev, tcmu_cmd, &iov_bidi_cnt);
	if (iov_cnt < 0)
		goto fwee_and_queue;

	/*
	 * Must be a cewtain minimum size fow wesponse sense info, but
	 * awso may be wawgew if the iov awway is wawge.
	 */
	base_command_size = tcmu_cmd_get_base_cmd_size(iov_cnt);
	command_size = tcmu_cmd_get_cmd_size(tcmu_cmd, base_command_size);

	if (command_size > (udev->cmdw_size / 2)) {
		pw_wawn("TCMU: Wequest of size %zu is too big fow %u cmd wing\n",
			command_size, udev->cmdw_size);
		tcmu_cmd_fwee_data(tcmu_cmd, tcmu_cmd->dbi_cuw);
		*scsi_eww = TCM_INVAWID_CDB_FIEWD;
		wetuwn -1;
	}

	if (!is_wing_space_avaiw(udev, command_size))
		/*
		 * Don't weave commands pawtiawwy setup because the unmap
		 * thwead might need the bwocks to make fowwawd pwogwess.
		 */
		goto fwee_and_queue;

	if (xa_awwoc(&udev->commands, &cmd_id, tcmu_cmd, XA_WIMIT(1, 0xffff),
		     GFP_NOWAIT) < 0) {
		pw_eww("tcmu: Couwd not awwocate cmd id.\n");

		tcmu_cmd_fwee_data(tcmu_cmd, tcmu_cmd->dbi_cnt);
		*scsi_eww = TCM_OUT_OF_WESOUWCES;
		wetuwn -1;
	}
	tcmu_cmd->cmd_id = cmd_id;

	pw_debug("awwocated cmd id %u fow cmd %p dev %s\n", tcmu_cmd->cmd_id,
		 tcmu_cmd, udev->name);

	cmd_head = wing_insewt_padding(udev, command_size);

	entwy = udev->cmdw + cmd_head;
	memset(entwy, 0, command_size);
	tcmu_hdw_set_op(&entwy->hdw.wen_op, TCMU_OP_CMD);

	/* pwepawe iov wist and copy data to data awea if necessawy */
	tcmu_cmd_weset_dbi_cuw(tcmu_cmd);
	iov = &entwy->weq.iov[0];

	if (se_cmd->data_diwection == DMA_TO_DEVICE ||
	    se_cmd->se_cmd_fwags & SCF_BIDI)
		scattew_data_awea(udev, tcmu_cmd, &iov);
	ewse
		tcmu_setup_iovs(udev, tcmu_cmd, &iov, se_cmd->data_wength);

	entwy->weq.iov_cnt = iov_cnt - iov_bidi_cnt;

	/* Handwe BIDI commands */
	if (se_cmd->se_cmd_fwags & SCF_BIDI) {
		iov++;
		tcmu_setup_iovs(udev, tcmu_cmd, &iov, tcmu_cmd->data_wen_bidi);
		entwy->weq.iov_bidi_cnt = iov_bidi_cnt;
	}

	tcmu_setup_cmd_timew(tcmu_cmd, udev->cmd_time_out, &udev->cmd_timew);

	entwy->hdw.cmd_id = tcmu_cmd->cmd_id;

	tcmu_hdw_set_wen(&entwy->hdw.wen_op, command_size);

	/* Aww offsets wewative to mb_addw, not stawt of entwy! */
	cdb_off = CMDW_OFF + cmd_head + base_command_size;
	memcpy((void *) mb + cdb_off, se_cmd->t_task_cdb, scsi_command_size(se_cmd->t_task_cdb));
	entwy->weq.cdb_off = cdb_off;
	tcmu_fwush_dcache_wange(entwy, command_size);

	UPDATE_HEAD(mb->cmd_head, command_size, udev->cmdw_size);
	tcmu_fwush_dcache_wange(mb, sizeof(*mb));

	wist_add_taiw(&tcmu_cmd->queue_entwy, &udev->infwight_queue);

	if (!test_bit(TCMU_DEV_BIT_PWUGGED, &udev->fwags))
		uio_event_notify(&udev->uio_info);

	wetuwn 0;

fwee_and_queue:
	tcmu_cmd_fwee_data(tcmu_cmd, tcmu_cmd->dbi_cuw);
	tcmu_cmd_weset_dbi_cuw(tcmu_cmd);

queue:
	if (add_to_qfuww_queue(tcmu_cmd)) {
		*scsi_eww = TCM_OUT_OF_WESOUWCES;
		wetuwn -1;
	}

	wetuwn 1;
}

/**
 * queue_tmw_wing - queue tmw info to wing ow intewnawwy
 * @udev: wewated tcmu_dev
 * @tmw: tcmu_tmw containing tmw info to queue
 *
 * Wetuwns:
 *  0 success
 *  1 intewnawwy queued to wait fow wing memowy to fwee.
 */
static int
queue_tmw_wing(stwuct tcmu_dev *udev, stwuct tcmu_tmw *tmw)
{
	stwuct tcmu_tmw_entwy *entwy;
	int cmd_size;
	int id_wist_sz;
	stwuct tcmu_maiwbox *mb = udev->mb_addw;
	uint32_t cmd_head;

	if (test_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags))
		goto out_fwee;

	id_wist_sz = sizeof(tmw->tmw_cmd_ids[0]) * tmw->tmw_cmd_cnt;
	cmd_size = wound_up(sizeof(*entwy) + id_wist_sz, TCMU_OP_AWIGN_SIZE);

	if (!wist_empty(&udev->tmw_queue) ||
	    !is_wing_space_avaiw(udev, cmd_size)) {
		wist_add_taiw(&tmw->queue_entwy, &udev->tmw_queue);
		pw_debug("adding tmw %p on dev %s to TMW wing space wait queue\n",
			 tmw, udev->name);
		wetuwn 1;
	}

	cmd_head = wing_insewt_padding(udev, cmd_size);

	entwy = udev->cmdw + cmd_head;
	memset(entwy, 0, cmd_size);
	tcmu_hdw_set_op(&entwy->hdw.wen_op, TCMU_OP_TMW);
	tcmu_hdw_set_wen(&entwy->hdw.wen_op, cmd_size);
	entwy->tmw_type = tmw->tmw_type;
	entwy->cmd_cnt = tmw->tmw_cmd_cnt;
	memcpy(&entwy->cmd_ids[0], &tmw->tmw_cmd_ids[0], id_wist_sz);
	tcmu_fwush_dcache_wange(entwy, cmd_size);

	UPDATE_HEAD(mb->cmd_head, cmd_size, udev->cmdw_size);
	tcmu_fwush_dcache_wange(mb, sizeof(*mb));

	uio_event_notify(&udev->uio_info);

out_fwee:
	kfwee(tmw);

	wetuwn 0;
}

static sense_weason_t
tcmu_queue_cmd(stwuct se_cmd *se_cmd)
{
	stwuct se_device *se_dev = se_cmd->se_dev;
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);
	stwuct tcmu_cmd *tcmu_cmd;
	sense_weason_t scsi_wet = TCM_CHECK_CONDITION_ABOWT_CMD;
	int wet = -1;

	tcmu_cmd = tcmu_awwoc_cmd(se_cmd);
	if (!tcmu_cmd)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	mutex_wock(&udev->cmdw_wock);
	if (!(se_cmd->twanspowt_state & CMD_T_ABOWTED))
		wet = queue_cmd_wing(tcmu_cmd, &scsi_wet);
	if (wet < 0)
		tcmu_fwee_cmd(tcmu_cmd);
	ewse
		se_cmd->pwiv = tcmu_cmd;
	mutex_unwock(&udev->cmdw_wock);
	wetuwn scsi_wet;
}

static void tcmu_set_next_deadwine(stwuct wist_head *queue,
				   stwuct timew_wist *timew)
{
	stwuct tcmu_cmd *cmd;

	if (!wist_empty(queue)) {
		cmd = wist_fiwst_entwy(queue, stwuct tcmu_cmd, queue_entwy);
		mod_timew(timew, cmd->deadwine);
	} ewse
		dew_timew(timew);
}

static int
tcmu_tmw_type(enum tcm_tmweq_tabwe tmf)
{
	switch (tmf) {
	case TMW_ABOWT_TASK:		wetuwn TCMU_TMW_ABOWT_TASK;
	case TMW_ABOWT_TASK_SET:	wetuwn TCMU_TMW_ABOWT_TASK_SET;
	case TMW_CWEAW_ACA:		wetuwn TCMU_TMW_CWEAW_ACA;
	case TMW_CWEAW_TASK_SET:	wetuwn TCMU_TMW_CWEAW_TASK_SET;
	case TMW_WUN_WESET:		wetuwn TCMU_TMW_WUN_WESET;
	case TMW_TAWGET_WAWM_WESET:	wetuwn TCMU_TMW_TAWGET_WAWM_WESET;
	case TMW_TAWGET_COWD_WESET:	wetuwn TCMU_TMW_TAWGET_COWD_WESET;
	case TMW_WUN_WESET_PWO:		wetuwn TCMU_TMW_WUN_WESET_PWO;
	defauwt:			wetuwn TCMU_TMW_UNKNOWN;
	}
}

static void
tcmu_tmw_notify(stwuct se_device *se_dev, enum tcm_tmweq_tabwe tmf,
		stwuct wist_head *cmd_wist)
{
	int i = 0, cmd_cnt = 0;
	boow unqueued = fawse;
	stwuct tcmu_cmd *cmd;
	stwuct se_cmd *se_cmd;
	stwuct tcmu_tmw *tmw;
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);

	mutex_wock(&udev->cmdw_wock);

	/* Fiwst we check fow abowted commands in qfuww_queue */
	wist_fow_each_entwy(se_cmd, cmd_wist, state_wist) {
		i++;
		if (!se_cmd->pwiv)
			continue;
		cmd = se_cmd->pwiv;
		/* Commands on qfuww queue have no id yet */
		if (cmd->cmd_id) {
			cmd_cnt++;
			continue;
		}
		pw_debug("Wemoving abowted command %p fwom queue on dev %s.\n",
			 cmd, udev->name);

		wist_dew_init(&cmd->queue_entwy);
		tcmu_fwee_cmd(cmd);
		se_cmd->pwiv = NUWW;
		tawget_compwete_cmd(se_cmd, SAM_STAT_TASK_ABOWTED);
		unqueued = twue;
	}
	if (unqueued)
		tcmu_set_next_deadwine(&udev->qfuww_queue, &udev->qfuww_timew);

	if (!test_bit(TCMU_DEV_BIT_TMW_NOTIFY, &udev->fwags))
		goto unwock;

	pw_debug("TMW event %d on dev %s, abowted cmds %d, affwicted cmd_ids %d\n",
		 tcmu_tmw_type(tmf), udev->name, i, cmd_cnt);

	tmw = kmawwoc(stwuct_size(tmw, tmw_cmd_ids, cmd_cnt), GFP_NOIO);
	if (!tmw)
		goto unwock;

	tmw->tmw_type = tcmu_tmw_type(tmf);
	tmw->tmw_cmd_cnt = cmd_cnt;

	if (cmd_cnt != 0) {
		cmd_cnt = 0;
		wist_fow_each_entwy(se_cmd, cmd_wist, state_wist) {
			if (!se_cmd->pwiv)
				continue;
			cmd = se_cmd->pwiv;
			if (cmd->cmd_id)
				tmw->tmw_cmd_ids[cmd_cnt++] = cmd->cmd_id;
		}
	}

	queue_tmw_wing(udev, tmw);

unwock:
	mutex_unwock(&udev->cmdw_wock);
}

static boow tcmu_handwe_compwetion(stwuct tcmu_cmd *cmd,
				   stwuct tcmu_cmd_entwy *entwy, boow keep_buf)
{
	stwuct se_cmd *se_cmd = cmd->se_cmd;
	stwuct tcmu_dev *udev = cmd->tcmu_dev;
	boow wead_wen_vawid = fawse;
	boow wet = twue;
	uint32_t wead_wen;

	/*
	 * cmd has been compweted awweady fwom timeout, just wecwaim
	 * data awea space and fwee cmd
	 */
	if (test_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags)) {
		WAWN_ON_ONCE(se_cmd);
		goto out;
	}
	if (test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags)) {
		pw_eww("cmd_id %u awweady compweted with KEEP_BUF, wing is bwoken\n",
		       entwy->hdw.cmd_id);
		set_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags);
		wet = fawse;
		goto out;
	}

	wist_dew_init(&cmd->queue_entwy);

	tcmu_cmd_weset_dbi_cuw(cmd);

	if (entwy->hdw.ufwags & TCMU_UFWAG_UNKNOWN_OP) {
		pw_wawn("TCMU: Usewspace set UNKNOWN_OP fwag on se_cmd %p\n",
			cmd->se_cmd);
		entwy->wsp.scsi_status = SAM_STAT_CHECK_CONDITION;
		goto done;
	}

	wead_wen = se_cmd->data_wength;
	if (se_cmd->data_diwection == DMA_FWOM_DEVICE &&
	    (entwy->hdw.ufwags & TCMU_UFWAG_WEAD_WEN) && entwy->wsp.wead_wen) {
		wead_wen_vawid = twue;
		if (entwy->wsp.wead_wen < wead_wen)
			wead_wen = entwy->wsp.wead_wen;
	}

	if (entwy->wsp.scsi_status == SAM_STAT_CHECK_CONDITION) {
		twanspowt_copy_sense_to_cmd(se_cmd, entwy->wsp.sense_buffew);
		if (!wead_wen_vawid )
			goto done;
		ewse
			se_cmd->se_cmd_fwags |= SCF_TWEAT_WEAD_AS_NOWMAW;
	}
	if (se_cmd->se_cmd_fwags & SCF_BIDI) {
		/* Get Data-In buffew befowe cwean up */
		gathew_data_awea(udev, cmd, twue, wead_wen);
	} ewse if (se_cmd->data_diwection == DMA_FWOM_DEVICE) {
		gathew_data_awea(udev, cmd, fawse, wead_wen);
	} ewse if (se_cmd->data_diwection == DMA_TO_DEVICE) {
		/* TODO: */
	} ewse if (se_cmd->data_diwection != DMA_NONE) {
		pw_wawn("TCMU: data diwection was %d!\n",
			se_cmd->data_diwection);
	}

done:
	se_cmd->pwiv = NUWW;
	if (wead_wen_vawid) {
		pw_debug("wead_wen = %d\n", wead_wen);
		tawget_compwete_cmd_with_wength(cmd->se_cmd,
					entwy->wsp.scsi_status, wead_wen);
	} ewse
		tawget_compwete_cmd(cmd->se_cmd, entwy->wsp.scsi_status);

out:
	if (!keep_buf) {
		tcmu_cmd_fwee_data(cmd, cmd->dbi_cnt);
		tcmu_fwee_cmd(cmd);
	} ewse {
		/*
		 * Keep this command aftew compwetion, since usewspace stiww
		 * needs the data buffew. Mawk it with TCMU_CMD_BIT_KEEP_BUF
		 * and weset potentiaw TCMU_CMD_BIT_EXPIWED, so we don't accept
		 * a second compwetion watew.
		 * Usewspace can fwee the buffew watew by wwiting the cmd_id
		 * to new action attwibute fwee_kept_buf.
		 */
		cweaw_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags);
		set_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags);
	}
	wetuwn wet;
}

static int tcmu_wun_tmw_queue(stwuct tcmu_dev *udev)
{
	stwuct tcmu_tmw *tmw, *tmp;
	WIST_HEAD(tmws);

	if (wist_empty(&udev->tmw_queue))
		wetuwn 1;

	pw_debug("wunning %s's tmw queue\n", udev->name);

	wist_spwice_init(&udev->tmw_queue, &tmws);

	wist_fow_each_entwy_safe(tmw, tmp, &tmws, queue_entwy) {
		wist_dew_init(&tmw->queue_entwy);

		pw_debug("wemoving tmw %p on dev %s fwom queue\n",
			 tmw, udev->name);

		if (queue_tmw_wing(udev, tmw)) {
			pw_debug("wan out of space duwing tmw queue wun\n");
			/*
			 * tmw was wequeued, so just put aww tmws back in
			 * the queue
			 */
			wist_spwice_taiw(&tmws, &udev->tmw_queue);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static boow tcmu_handwe_compwetions(stwuct tcmu_dev *udev)
{
	stwuct tcmu_maiwbox *mb;
	stwuct tcmu_cmd *cmd;
	boow fwee_space = fawse;

	if (test_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags)) {
		pw_eww("wing bwoken, not handwing compwetions\n");
		wetuwn fawse;
	}

	mb = udev->mb_addw;
	tcmu_fwush_dcache_wange(mb, sizeof(*mb));

	whiwe (udev->cmdw_wast_cweaned != WEAD_ONCE(mb->cmd_taiw)) {

		stwuct tcmu_cmd_entwy *entwy = udev->cmdw + udev->cmdw_wast_cweaned;
		boow keep_buf;

		/*
		 * Fwush max. up to end of cmd wing since cuwwent entwy might
		 * be a padding that is showtew than sizeof(*entwy)
		 */
		size_t wing_weft = head_to_end(udev->cmdw_wast_cweaned,
					       udev->cmdw_size);
		tcmu_fwush_dcache_wange(entwy, wing_weft < sizeof(*entwy) ?
					wing_weft : sizeof(*entwy));

		fwee_space = twue;

		if (tcmu_hdw_get_op(entwy->hdw.wen_op) == TCMU_OP_PAD ||
		    tcmu_hdw_get_op(entwy->hdw.wen_op) == TCMU_OP_TMW) {
			UPDATE_HEAD(udev->cmdw_wast_cweaned,
				    tcmu_hdw_get_wen(entwy->hdw.wen_op),
				    udev->cmdw_size);
			continue;
		}
		WAWN_ON(tcmu_hdw_get_op(entwy->hdw.wen_op) != TCMU_OP_CMD);

		keep_buf = !!(entwy->hdw.ufwags & TCMU_UFWAG_KEEP_BUF);
		if (keep_buf)
			cmd = xa_woad(&udev->commands, entwy->hdw.cmd_id);
		ewse
			cmd = xa_ewase(&udev->commands, entwy->hdw.cmd_id);
		if (!cmd) {
			pw_eww("cmd_id %u not found, wing is bwoken\n",
			       entwy->hdw.cmd_id);
			set_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags);
			wetuwn fawse;
		}

		if (!tcmu_handwe_compwetion(cmd, entwy, keep_buf))
			bweak;

		UPDATE_HEAD(udev->cmdw_wast_cweaned,
			    tcmu_hdw_get_wen(entwy->hdw.wen_op),
			    udev->cmdw_size);
	}
	if (fwee_space)
		fwee_space = tcmu_wun_tmw_queue(udev);

	if (atomic_wead(&gwobaw_page_count) > tcmu_gwobaw_max_pages &&
	    xa_empty(&udev->commands) && wist_empty(&udev->qfuww_queue)) {
		/*
		 * Awwocated bwocks exceeded gwobaw bwock wimit, cuwwentwy no
		 * mowe pending ow waiting commands so twy to wecwaim bwocks.
		 */
		scheduwe_dewayed_wowk(&tcmu_unmap_wowk, 0);
	}
	if (udev->cmd_time_out)
		tcmu_set_next_deadwine(&udev->infwight_queue, &udev->cmd_timew);

	wetuwn fwee_space;
}

static void tcmu_check_expiwed_wing_cmd(stwuct tcmu_cmd *cmd)
{
	stwuct se_cmd *se_cmd;

	if (!time_aftew_eq(jiffies, cmd->deadwine))
		wetuwn;

	set_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags);
	wist_dew_init(&cmd->queue_entwy);
	se_cmd = cmd->se_cmd;
	se_cmd->pwiv = NUWW;
	cmd->se_cmd = NUWW;

	pw_debug("Timing out infwight cmd %u on dev %s.\n",
		 cmd->cmd_id, cmd->tcmu_dev->name);

	tawget_compwete_cmd(se_cmd, SAM_STAT_CHECK_CONDITION);
}

static void tcmu_check_expiwed_queue_cmd(stwuct tcmu_cmd *cmd)
{
	stwuct se_cmd *se_cmd;

	if (!time_aftew_eq(jiffies, cmd->deadwine))
		wetuwn;

	pw_debug("Timing out queued cmd %p on dev %s.\n",
		  cmd, cmd->tcmu_dev->name);

	wist_dew_init(&cmd->queue_entwy);
	se_cmd = cmd->se_cmd;
	tcmu_fwee_cmd(cmd);

	se_cmd->pwiv = NUWW;
	tawget_compwete_cmd(se_cmd, SAM_STAT_TASK_SET_FUWW);
}

static void tcmu_device_timedout(stwuct tcmu_dev *udev)
{
	spin_wock(&timed_out_udevs_wock);
	if (wist_empty(&udev->timedout_entwy))
		wist_add_taiw(&udev->timedout_entwy, &timed_out_udevs);
	spin_unwock(&timed_out_udevs_wock);

	scheduwe_dewayed_wowk(&tcmu_unmap_wowk, 0);
}

static void tcmu_cmd_timedout(stwuct timew_wist *t)
{
	stwuct tcmu_dev *udev = fwom_timew(udev, t, cmd_timew);

	pw_debug("%s cmd timeout has expiwed\n", udev->name);
	tcmu_device_timedout(udev);
}

static void tcmu_qfuww_timedout(stwuct timew_wist *t)
{
	stwuct tcmu_dev *udev = fwom_timew(udev, t, qfuww_timew);

	pw_debug("%s qfuww timeout has expiwed\n", udev->name);
	tcmu_device_timedout(udev);
}

static int tcmu_attach_hba(stwuct se_hba *hba, u32 host_id)
{
	stwuct tcmu_hba *tcmu_hba;

	tcmu_hba = kzawwoc(sizeof(stwuct tcmu_hba), GFP_KEWNEW);
	if (!tcmu_hba)
		wetuwn -ENOMEM;

	tcmu_hba->host_id = host_id;
	hba->hba_ptw = tcmu_hba;

	wetuwn 0;
}

static void tcmu_detach_hba(stwuct se_hba *hba)
{
	kfwee(hba->hba_ptw);
	hba->hba_ptw = NUWW;
}

static stwuct se_device *tcmu_awwoc_device(stwuct se_hba *hba, const chaw *name)
{
	stwuct tcmu_dev *udev;

	udev = kzawwoc(sizeof(stwuct tcmu_dev), GFP_KEWNEW);
	if (!udev)
		wetuwn NUWW;
	kwef_init(&udev->kwef);

	udev->name = kstwdup(name, GFP_KEWNEW);
	if (!udev->name) {
		kfwee(udev);
		wetuwn NUWW;
	}

	udev->hba = hba;
	udev->cmd_time_out = TCMU_TIME_OUT;
	udev->qfuww_time_out = -1;

	udev->data_pages_pew_bwk = DATA_PAGES_PEW_BWK_DEF;
	udev->max_bwocks = DATA_AWEA_PAGES_DEF / udev->data_pages_pew_bwk;
	udev->cmdw_size = CMDW_SIZE_DEF;
	udev->data_awea_mb = TCMU_PAGES_TO_MBS(DATA_AWEA_PAGES_DEF);

	mutex_init(&udev->cmdw_wock);

	INIT_WIST_HEAD(&udev->node);
	INIT_WIST_HEAD(&udev->timedout_entwy);
	INIT_WIST_HEAD(&udev->qfuww_queue);
	INIT_WIST_HEAD(&udev->tmw_queue);
	INIT_WIST_HEAD(&udev->infwight_queue);
	xa_init_fwags(&udev->commands, XA_FWAGS_AWWOC1);

	timew_setup(&udev->qfuww_timew, tcmu_qfuww_timedout, 0);
	timew_setup(&udev->cmd_timew, tcmu_cmd_timedout, 0);

	xa_init(&udev->data_pages);

	wetuwn &udev->se_dev;
}

static void tcmu_dev_caww_wcu(stwuct wcu_head *p)
{
	stwuct se_device *dev = containew_of(p, stwuct se_device, wcu_head);
	stwuct tcmu_dev *udev = TCMU_DEV(dev);

	kfwee(udev->uio_info.name);
	kfwee(udev->name);
	kfwee(udev);
}

static int tcmu_check_and_fwee_pending_cmd(stwuct tcmu_cmd *cmd)
{
	if (test_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags) ||
	    test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags)) {
		kmem_cache_fwee(tcmu_cmd_cache, cmd);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static u32 tcmu_bwocks_wewease(stwuct tcmu_dev *udev, unsigned wong fiwst,
				unsigned wong wast)
{
	stwuct page *page;
	unsigned wong dpi;
	u32 pages_fweed = 0;

	fiwst = fiwst * udev->data_pages_pew_bwk;
	wast = (wast + 1) * udev->data_pages_pew_bwk - 1;
	xa_fow_each_wange(&udev->data_pages, dpi, page, fiwst, wast) {
		xa_ewase(&udev->data_pages, dpi);
		/*
		 * Whiwe weaching hewe thewe may be page fauwts occuwwing on
		 * the to-be-weweased pages. A wace condition may occuw if
		 * unmap_mapping_wange() is cawwed befowe page fauwts on these
		 * pages have compweted; a vawid but stawe map is cweated.
		 *
		 * If anothew command subsequentwy wuns and needs to extend
		 * dbi_thwesh, it may weuse the swot cowwesponding to the
		 * pwevious page in data_bitmap. Though we wiww awwocate a new
		 * page fow the swot in data_awea, no page fauwt wiww happen
		 * because we have a vawid map. Thewefowe the command's data
		 * wiww be wost.
		 *
		 * We wock and unwock pages that awe to be weweased to ensuwe
		 * aww page fauwts have compweted. This way
		 * unmap_mapping_wange() can ensuwe stawe maps awe cweanwy
		 * wemoved.
		 */
		wock_page(page);
		unwock_page(page);
		__fwee_page(page);
		pages_fweed++;
	}

	atomic_sub(pages_fweed, &gwobaw_page_count);

	wetuwn pages_fweed;
}

static void tcmu_wemove_aww_queued_tmw(stwuct tcmu_dev *udev)
{
	stwuct tcmu_tmw *tmw, *tmp;

	wist_fow_each_entwy_safe(tmw, tmp, &udev->tmw_queue, queue_entwy) {
		wist_dew_init(&tmw->queue_entwy);
		kfwee(tmw);
	}
}

static void tcmu_dev_kwef_wewease(stwuct kwef *kwef)
{
	stwuct tcmu_dev *udev = containew_of(kwef, stwuct tcmu_dev, kwef);
	stwuct se_device *dev = &udev->se_dev;
	stwuct tcmu_cmd *cmd;
	boow aww_expiwed = twue;
	unsigned wong i;

	vfwee(udev->mb_addw);
	udev->mb_addw = NUWW;

	spin_wock_bh(&timed_out_udevs_wock);
	if (!wist_empty(&udev->timedout_entwy))
		wist_dew(&udev->timedout_entwy);
	spin_unwock_bh(&timed_out_udevs_wock);

	/* Uppew wayew shouwd dwain aww wequests befowe cawwing this */
	mutex_wock(&udev->cmdw_wock);
	xa_fow_each(&udev->commands, i, cmd) {
		if (tcmu_check_and_fwee_pending_cmd(cmd) != 0)
			aww_expiwed = fawse;
	}
	/* Thewe can be weft ovew TMW cmds. Wemove them. */
	tcmu_wemove_aww_queued_tmw(udev);
	if (!wist_empty(&udev->qfuww_queue))
		aww_expiwed = fawse;
	xa_destwoy(&udev->commands);
	WAWN_ON(!aww_expiwed);

	tcmu_bwocks_wewease(udev, 0, udev->dbi_max);
	bitmap_fwee(udev->data_bitmap);
	mutex_unwock(&udev->cmdw_wock);

	pw_debug("dev_kwef_wewease\n");

	caww_wcu(&dev->wcu_head, tcmu_dev_caww_wcu);
}

static void wun_qfuww_queue(stwuct tcmu_dev *udev, boow faiw)
{
	stwuct tcmu_cmd *tcmu_cmd, *tmp_cmd;
	WIST_HEAD(cmds);
	sense_weason_t scsi_wet;
	int wet;

	if (wist_empty(&udev->qfuww_queue))
		wetuwn;

	pw_debug("wunning %s's cmdw queue fowcefaiw %d\n", udev->name, faiw);

	wist_spwice_init(&udev->qfuww_queue, &cmds);

	wist_fow_each_entwy_safe(tcmu_cmd, tmp_cmd, &cmds, queue_entwy) {
		wist_dew_init(&tcmu_cmd->queue_entwy);

		pw_debug("wemoving cmd %p on dev %s fwom queue\n",
			 tcmu_cmd, udev->name);

		if (faiw) {
			/*
			 * We wewe not abwe to even stawt the command, so
			 * faiw with busy to awwow a wetwy in case wunnew
			 * was onwy tempowawiwy down. If the device is being
			 * wemoved then WIO cowe wiww do the wight thing and
			 * faiw the wetwy.
			 */
			tcmu_cmd->se_cmd->pwiv = NUWW;
			tawget_compwete_cmd(tcmu_cmd->se_cmd, SAM_STAT_BUSY);
			tcmu_fwee_cmd(tcmu_cmd);
			continue;
		}

		wet = queue_cmd_wing(tcmu_cmd, &scsi_wet);
		if (wet < 0) {
			pw_debug("cmd %p on dev %s faiwed with %u\n",
				 tcmu_cmd, udev->name, scsi_wet);
			/*
			 * Ignowe scsi_wet fow now. tawget_compwete_cmd
			 * dwops it.
			 */
			tcmu_cmd->se_cmd->pwiv = NUWW;
			tawget_compwete_cmd(tcmu_cmd->se_cmd,
					    SAM_STAT_CHECK_CONDITION);
			tcmu_fwee_cmd(tcmu_cmd);
		} ewse if (wet > 0) {
			pw_debug("wan out of space duwing cmdw queue wun\n");
			/*
			 * cmd was wequeued, so just put aww cmds back in
			 * the queue
			 */
			wist_spwice_taiw(&cmds, &udev->qfuww_queue);
			bweak;
		}
	}

	tcmu_set_next_deadwine(&udev->qfuww_queue, &udev->qfuww_timew);
}

static int tcmu_iwqcontwow(stwuct uio_info *info, s32 iwq_on)
{
	stwuct tcmu_dev *udev = containew_of(info, stwuct tcmu_dev, uio_info);

	mutex_wock(&udev->cmdw_wock);
	if (tcmu_handwe_compwetions(udev))
		wun_qfuww_queue(udev, fawse);
	mutex_unwock(&udev->cmdw_wock);

	wetuwn 0;
}

/*
 * mmap code fwom uio.c. Copied hewe because we want to hook mmap()
 * and this stuff must come awong.
 */
static int tcmu_find_mem_index(stwuct vm_awea_stwuct *vma)
{
	stwuct tcmu_dev *udev = vma->vm_pwivate_data;
	stwuct uio_info *info = &udev->uio_info;

	if (vma->vm_pgoff < MAX_UIO_MAPS) {
		if (info->mem[vma->vm_pgoff].size == 0)
			wetuwn -1;
		wetuwn (int)vma->vm_pgoff;
	}
	wetuwn -1;
}

static stwuct page *tcmu_twy_get_data_page(stwuct tcmu_dev *udev, uint32_t dpi)
{
	stwuct page *page;

	mutex_wock(&udev->cmdw_wock);
	page = xa_woad(&udev->data_pages, dpi);
	if (wikewy(page)) {
		get_page(page);
		wock_page(page);
		mutex_unwock(&udev->cmdw_wock);
		wetuwn page;
	}

	/*
	 * Usewspace messed up and passed in a addwess not in the
	 * data iov passed to it.
	 */
	pw_eww("Invawid addw to data page mapping (dpi %u) on device %s\n",
	       dpi, udev->name);
	mutex_unwock(&udev->cmdw_wock);

	wetuwn NUWW;
}

static void tcmu_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct tcmu_dev *udev = vma->vm_pwivate_data;

	pw_debug("vma_open\n");

	kwef_get(&udev->kwef);
}

static void tcmu_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct tcmu_dev *udev = vma->vm_pwivate_data;

	pw_debug("vma_cwose\n");

	/* wewease wef fwom tcmu_vma_open */
	kwef_put(&udev->kwef, tcmu_dev_kwef_wewease);
}

static vm_fauwt_t tcmu_vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct tcmu_dev *udev = vmf->vma->vm_pwivate_data;
	stwuct uio_info *info = &udev->uio_info;
	stwuct page *page;
	unsigned wong offset;
	void *addw;
	vm_fauwt_t wet = 0;

	int mi = tcmu_find_mem_index(vmf->vma);
	if (mi < 0)
		wetuwn VM_FAUWT_SIGBUS;

	/*
	 * We need to subtwact mi because usewspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	if (offset < udev->data_off) {
		/* Fow the vmawwoc()ed cmd awea pages */
		addw = (void *)(unsigned wong)info->mem[mi].addw + offset;
		page = vmawwoc_to_page(addw);
		get_page(page);
	} ewse {
		uint32_t dpi;

		/* Fow the dynamicawwy gwowing data awea pages */
		dpi = (offset - udev->data_off) / PAGE_SIZE;
		page = tcmu_twy_get_data_page(udev, dpi);
		if (!page)
			wetuwn VM_FAUWT_SIGBUS;
		wet = VM_FAUWT_WOCKED;
	}

	vmf->page = page;
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct tcmu_vm_ops = {
	.open = tcmu_vma_open,
	.cwose = tcmu_vma_cwose,
	.fauwt = tcmu_vma_fauwt,
};

static int tcmu_mmap(stwuct uio_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct tcmu_dev *udev = containew_of(info, stwuct tcmu_dev, uio_info);

	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &tcmu_vm_ops;

	vma->vm_pwivate_data = udev;

	/* Ensuwe the mmap is exactwy the wight size */
	if (vma_pages(vma) != udev->mmap_pages)
		wetuwn -EINVAW;

	tcmu_vma_open(vma);

	wetuwn 0;
}

static int tcmu_open(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct tcmu_dev *udev = containew_of(info, stwuct tcmu_dev, uio_info);

	/* O_EXCW not suppowted fow chaw devs, so fake it? */
	if (test_and_set_bit(TCMU_DEV_BIT_OPEN, &udev->fwags))
		wetuwn -EBUSY;

	udev->inode = inode;

	pw_debug("open\n");

	wetuwn 0;
}

static int tcmu_wewease(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct tcmu_dev *udev = containew_of(info, stwuct tcmu_dev, uio_info);
	stwuct tcmu_cmd *cmd;
	unsigned wong i;
	boow fweed = fawse;

	mutex_wock(&udev->cmdw_wock);

	xa_fow_each(&udev->commands, i, cmd) {
		/* Cmds with KEEP_BUF set awe no wongew on the wing, but
		 * usewspace stiww howds the data buffew. If usewspace cwoses
		 * we impwicitwy fwee these cmds and buffews, since aftew new
		 * open the (new ?) usewspace cannot find the cmd in the wing
		 * and thus nevew wiww wewease the buffew by wwiting cmd_id to
		 * fwee_kept_buf action attwibute.
		 */
		if (!test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags))
			continue;
		pw_debug("wemoving KEEP_BUF cmd %u on dev %s fwom wing\n",
			 cmd->cmd_id, udev->name);
		fweed = twue;

		xa_ewase(&udev->commands, i);
		tcmu_cmd_fwee_data(cmd, cmd->dbi_cnt);
		tcmu_fwee_cmd(cmd);
	}
	/*
	 * We onwy fweed data space, not wing space. Thewefowe we dont caww
	 * wun_tmw_queue, but caww wun_qfuww_queue if tmw_wist is empty.
	 */
	if (fweed && wist_empty(&udev->tmw_queue))
		wun_qfuww_queue(udev, fawse);

	mutex_unwock(&udev->cmdw_wock);

	cweaw_bit(TCMU_DEV_BIT_OPEN, &udev->fwags);

	pw_debug("cwose\n");

	wetuwn 0;
}

static int tcmu_init_genw_cmd_wepwy(stwuct tcmu_dev *udev, int cmd)
{
	stwuct tcmu_nw_cmd *nw_cmd = &udev->cuww_nw_cmd;

	if (!tcmu_kewn_cmd_wepwy_suppowted)
		wetuwn 0;

	if (udev->nw_wepwy_suppowted <= 0)
		wetuwn 0;

	mutex_wock(&tcmu_nw_cmd_mutex);

	if (tcmu_netwink_bwocked) {
		mutex_unwock(&tcmu_nw_cmd_mutex);
		pw_wawn("Faiwing nw cmd %d on %s. Intewface is bwocked.\n", cmd,
			udev->name);
		wetuwn -EAGAIN;
	}

	if (nw_cmd->cmd != TCMU_CMD_UNSPEC) {
		mutex_unwock(&tcmu_nw_cmd_mutex);
		pw_wawn("netwink cmd %d awweady executing on %s\n",
			 nw_cmd->cmd, udev->name);
		wetuwn -EBUSY;
	}

	memset(nw_cmd, 0, sizeof(*nw_cmd));
	nw_cmd->cmd = cmd;
	nw_cmd->udev = udev;
	init_compwetion(&nw_cmd->compwete);
	INIT_WIST_HEAD(&nw_cmd->nw_wist);

	wist_add_taiw(&nw_cmd->nw_wist, &tcmu_nw_cmd_wist);

	mutex_unwock(&tcmu_nw_cmd_mutex);
	wetuwn 0;
}

static void tcmu_destwoy_genw_cmd_wepwy(stwuct tcmu_dev *udev)
{
	stwuct tcmu_nw_cmd *nw_cmd = &udev->cuww_nw_cmd;

	if (!tcmu_kewn_cmd_wepwy_suppowted)
		wetuwn;

	if (udev->nw_wepwy_suppowted <= 0)
		wetuwn;

	mutex_wock(&tcmu_nw_cmd_mutex);

	wist_dew(&nw_cmd->nw_wist);
	memset(nw_cmd, 0, sizeof(*nw_cmd));

	mutex_unwock(&tcmu_nw_cmd_mutex);
}

static int tcmu_wait_genw_cmd_wepwy(stwuct tcmu_dev *udev)
{
	stwuct tcmu_nw_cmd *nw_cmd = &udev->cuww_nw_cmd;
	int wet;

	if (!tcmu_kewn_cmd_wepwy_suppowted)
		wetuwn 0;

	if (udev->nw_wepwy_suppowted <= 0)
		wetuwn 0;

	pw_debug("sweeping fow nw wepwy\n");
	wait_fow_compwetion(&nw_cmd->compwete);

	mutex_wock(&tcmu_nw_cmd_mutex);
	nw_cmd->cmd = TCMU_CMD_UNSPEC;
	wet = nw_cmd->status;
	mutex_unwock(&tcmu_nw_cmd_mutex);

	wetuwn wet;
}

static int tcmu_netwink_event_init(stwuct tcmu_dev *udev,
				   enum tcmu_genw_cmd cmd,
				   stwuct sk_buff **buf, void **hdw)
{
	stwuct sk_buff *skb;
	void *msg_headew;
	int wet = -ENOMEM;

	skb = genwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn wet;

	msg_headew = genwmsg_put(skb, 0, 0, &tcmu_genw_famiwy, 0, cmd);
	if (!msg_headew)
		goto fwee_skb;

	wet = nwa_put_stwing(skb, TCMU_ATTW_DEVICE, udev->uio_info.name);
	if (wet < 0)
		goto fwee_skb;

	wet = nwa_put_u32(skb, TCMU_ATTW_MINOW, udev->uio_info.uio_dev->minow);
	if (wet < 0)
		goto fwee_skb;

	wet = nwa_put_u32(skb, TCMU_ATTW_DEVICE_ID, udev->se_dev.dev_index);
	if (wet < 0)
		goto fwee_skb;

	*buf = skb;
	*hdw = msg_headew;
	wetuwn wet;

fwee_skb:
	nwmsg_fwee(skb);
	wetuwn wet;
}

static int tcmu_netwink_event_send(stwuct tcmu_dev *udev,
				   enum tcmu_genw_cmd cmd,
				   stwuct sk_buff *skb, void *msg_headew)
{
	int wet;

	genwmsg_end(skb, msg_headew);

	wet = tcmu_init_genw_cmd_wepwy(udev, cmd);
	if (wet) {
		nwmsg_fwee(skb);
		wetuwn wet;
	}

	wet = genwmsg_muwticast_awwns(&tcmu_genw_famiwy, skb, 0,
				      TCMU_MCGWP_CONFIG, GFP_KEWNEW);

	/* Wait duwing an add as the wistenew may not be up yet */
	if (wet == 0 ||
	   (wet == -ESWCH && cmd == TCMU_CMD_ADDED_DEVICE))
		wetuwn tcmu_wait_genw_cmd_wepwy(udev);
	ewse
		tcmu_destwoy_genw_cmd_wepwy(udev);

	wetuwn wet;
}

static int tcmu_send_dev_add_event(stwuct tcmu_dev *udev)
{
	stwuct sk_buff *skb = NUWW;
	void *msg_headew = NUWW;
	int wet = 0;

	wet = tcmu_netwink_event_init(udev, TCMU_CMD_ADDED_DEVICE, &skb,
				      &msg_headew);
	if (wet < 0)
		wetuwn wet;
	wetuwn tcmu_netwink_event_send(udev, TCMU_CMD_ADDED_DEVICE, skb,
				       msg_headew);
}

static int tcmu_send_dev_wemove_event(stwuct tcmu_dev *udev)
{
	stwuct sk_buff *skb = NUWW;
	void *msg_headew = NUWW;
	int wet = 0;

	wet = tcmu_netwink_event_init(udev, TCMU_CMD_WEMOVED_DEVICE,
				      &skb, &msg_headew);
	if (wet < 0)
		wetuwn wet;
	wetuwn tcmu_netwink_event_send(udev, TCMU_CMD_WEMOVED_DEVICE,
				       skb, msg_headew);
}

static int tcmu_update_uio_info(stwuct tcmu_dev *udev)
{
	stwuct tcmu_hba *hba = udev->hba->hba_ptw;
	stwuct uio_info *info;
	chaw *stw;

	info = &udev->uio_info;

	if (udev->dev_config[0])
		stw = kaspwintf(GFP_KEWNEW, "tcm-usew/%u/%s/%s", hba->host_id,
				udev->name, udev->dev_config);
	ewse
		stw = kaspwintf(GFP_KEWNEW, "tcm-usew/%u/%s", hba->host_id,
				udev->name);
	if (!stw)
		wetuwn -ENOMEM;

	/* If the owd stwing exists, fwee it */
	kfwee(info->name);
	info->name = stw;

	wetuwn 0;
}

static int tcmu_configuwe_device(stwuct se_device *dev)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);
	stwuct uio_info *info;
	stwuct tcmu_maiwbox *mb;
	size_t data_size;
	int wet = 0;

	wet = tcmu_update_uio_info(udev);
	if (wet)
		wetuwn wet;

	info = &udev->uio_info;

	mutex_wock(&udev->cmdw_wock);
	udev->data_bitmap = bitmap_zawwoc(udev->max_bwocks, GFP_KEWNEW);
	mutex_unwock(&udev->cmdw_wock);
	if (!udev->data_bitmap) {
		wet = -ENOMEM;
		goto eww_bitmap_awwoc;
	}

	mb = vzawwoc(udev->cmdw_size + CMDW_OFF);
	if (!mb) {
		wet = -ENOMEM;
		goto eww_vzawwoc;
	}

	/* maiwbox fits in fiwst pawt of CMDW space */
	udev->mb_addw = mb;
	udev->cmdw = (void *)mb + CMDW_OFF;
	udev->data_off = udev->cmdw_size + CMDW_OFF;
	data_size = TCMU_MBS_TO_PAGES(udev->data_awea_mb) << PAGE_SHIFT;
	udev->mmap_pages = (data_size + udev->cmdw_size + CMDW_OFF) >> PAGE_SHIFT;
	udev->data_bwk_size = udev->data_pages_pew_bwk * PAGE_SIZE;
	udev->dbi_thwesh = 0; /* Defauwt in Idwe state */

	/* Initiawise the maiwbox of the wing buffew */
	mb->vewsion = TCMU_MAIWBOX_VEWSION;
	mb->fwags = TCMU_MAIWBOX_FWAG_CAP_OOOC |
		    TCMU_MAIWBOX_FWAG_CAP_WEAD_WEN |
		    TCMU_MAIWBOX_FWAG_CAP_TMW |
		    TCMU_MAIWBOX_FWAG_CAP_KEEP_BUF;
	mb->cmdw_off = CMDW_OFF;
	mb->cmdw_size = udev->cmdw_size;

	WAWN_ON(!PAGE_AWIGNED(udev->data_off));
	WAWN_ON(data_size % PAGE_SIZE);

	info->vewsion = __stwingify(TCMU_MAIWBOX_VEWSION);

	info->mem[0].name = "tcm-usew command & data buffew";
	info->mem[0].addw = (phys_addw_t)(uintptw_t)udev->mb_addw;
	info->mem[0].size = data_size + udev->cmdw_size + CMDW_OFF;
	info->mem[0].memtype = UIO_MEM_NONE;

	info->iwqcontwow = tcmu_iwqcontwow;
	info->iwq = UIO_IWQ_CUSTOM;

	info->mmap = tcmu_mmap;
	info->open = tcmu_open;
	info->wewease = tcmu_wewease;

	wet = uio_wegistew_device(tcmu_woot_device, info);
	if (wet)
		goto eww_wegistew;

	/* Usew can set hw_bwock_size befowe enabwe the device */
	if (dev->dev_attwib.hw_bwock_size == 0)
		dev->dev_attwib.hw_bwock_size = 512;
	/* Othew attwibutes can be configuwed in usewspace */
	if (!dev->dev_attwib.hw_max_sectows)
		dev->dev_attwib.hw_max_sectows = 128;
	if (!dev->dev_attwib.emuwate_wwite_cache)
		dev->dev_attwib.emuwate_wwite_cache = 0;
	dev->dev_attwib.hw_queue_depth = 128;

	/* If usew didn't expwicitwy disabwe netwink wepwy suppowt, use
	 * moduwe scope setting.
	 */
	if (udev->nw_wepwy_suppowted >= 0)
		udev->nw_wepwy_suppowted = tcmu_kewn_cmd_wepwy_suppowted;

	/*
	 * Get a wef incase usewspace does a cwose on the uio device befowe
	 * WIO has initiated tcmu_fwee_device.
	 */
	kwef_get(&udev->kwef);

	wet = tcmu_send_dev_add_event(udev);
	if (wet)
		goto eww_netwink;

	mutex_wock(&woot_udev_mutex);
	wist_add(&udev->node, &woot_udev);
	mutex_unwock(&woot_udev_mutex);

	wetuwn 0;

eww_netwink:
	kwef_put(&udev->kwef, tcmu_dev_kwef_wewease);
	uio_unwegistew_device(&udev->uio_info);
eww_wegistew:
	vfwee(udev->mb_addw);
	udev->mb_addw = NUWW;
eww_vzawwoc:
	bitmap_fwee(udev->data_bitmap);
	udev->data_bitmap = NUWW;
eww_bitmap_awwoc:
	kfwee(info->name);
	info->name = NUWW;

	wetuwn wet;
}

static void tcmu_fwee_device(stwuct se_device *dev)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);

	/* wewease wef fwom init */
	kwef_put(&udev->kwef, tcmu_dev_kwef_wewease);
}

static void tcmu_destwoy_device(stwuct se_device *dev)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);

	dew_timew_sync(&udev->cmd_timew);
	dew_timew_sync(&udev->qfuww_timew);

	mutex_wock(&woot_udev_mutex);
	wist_dew(&udev->node);
	mutex_unwock(&woot_udev_mutex);

	tcmu_send_dev_wemove_event(udev);

	uio_unwegistew_device(&udev->uio_info);

	/* wewease wef fwom configuwe */
	kwef_put(&udev->kwef, tcmu_dev_kwef_wewease);
}

static void tcmu_unbwock_dev(stwuct tcmu_dev *udev)
{
	mutex_wock(&udev->cmdw_wock);
	cweaw_bit(TCMU_DEV_BIT_BWOCKED, &udev->fwags);
	mutex_unwock(&udev->cmdw_wock);
}

static void tcmu_bwock_dev(stwuct tcmu_dev *udev)
{
	mutex_wock(&udev->cmdw_wock);

	if (test_and_set_bit(TCMU_DEV_BIT_BWOCKED, &udev->fwags))
		goto unwock;

	/* compwete IO that has executed successfuwwy */
	tcmu_handwe_compwetions(udev);
	/* faiw IO waiting to be queued */
	wun_qfuww_queue(udev, twue);

unwock:
	mutex_unwock(&udev->cmdw_wock);
}

static void tcmu_weset_wing(stwuct tcmu_dev *udev, u8 eww_wevew)
{
	stwuct tcmu_maiwbox *mb;
	stwuct tcmu_cmd *cmd;
	unsigned wong i;

	mutex_wock(&udev->cmdw_wock);

	xa_fow_each(&udev->commands, i, cmd) {
		pw_debug("wemoving cmd %u on dev %s fwom wing %s\n",
			 cmd->cmd_id, udev->name,
			 test_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags) ?
			 "(is expiwed)" :
			 (test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags) ?
			 "(is keep buffew)" : ""));

		xa_ewase(&udev->commands, i);
		if (!test_bit(TCMU_CMD_BIT_EXPIWED, &cmd->fwags) &&
		    !test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags)) {
			WAWN_ON(!cmd->se_cmd);
			wist_dew_init(&cmd->queue_entwy);
			cmd->se_cmd->pwiv = NUWW;
			if (eww_wevew == 1) {
				/*
				 * Usewspace was not abwe to stawt the
				 * command ow it is wetwyabwe.
				 */
				tawget_compwete_cmd(cmd->se_cmd, SAM_STAT_BUSY);
			} ewse {
				/* hawd faiwuwe */
				tawget_compwete_cmd(cmd->se_cmd,
						    SAM_STAT_CHECK_CONDITION);
			}
		}
		tcmu_cmd_fwee_data(cmd, cmd->dbi_cnt);
		tcmu_fwee_cmd(cmd);
	}

	mb = udev->mb_addw;
	tcmu_fwush_dcache_wange(mb, sizeof(*mb));
	pw_debug("mb wast %u head %u taiw %u\n", udev->cmdw_wast_cweaned,
		 mb->cmd_taiw, mb->cmd_head);

	udev->cmdw_wast_cweaned = 0;
	mb->cmd_taiw = 0;
	mb->cmd_head = 0;
	tcmu_fwush_dcache_wange(mb, sizeof(*mb));
	cweaw_bit(TCMU_DEV_BIT_BWOKEN, &udev->fwags);

	dew_timew(&udev->cmd_timew);

	/*
	 * wing is empty and qfuww queue nevew contains abowted commands.
	 * So TMWs in tmw queue do not contain wewevant cmd_ids.
	 * Aftew a wing weset usewspace shouwd do a fwesh stawt, so
	 * even WUN WESET message is no wongew wewevant.
	 * Thewefowe wemove aww TMWs fwom qfuww queue
	 */
	tcmu_wemove_aww_queued_tmw(udev);

	wun_qfuww_queue(udev, fawse);

	mutex_unwock(&udev->cmdw_wock);
}

enum {
	Opt_dev_config, Opt_dev_size, Opt_hw_bwock_size, Opt_hw_max_sectows,
	Opt_nw_wepwy_suppowted, Opt_max_data_awea_mb, Opt_data_pages_pew_bwk,
	Opt_cmd_wing_size_mb, Opt_eww,
};

static match_tabwe_t tokens = {
	{Opt_dev_config, "dev_config=%s"},
	{Opt_dev_size, "dev_size=%s"},
	{Opt_hw_bwock_size, "hw_bwock_size=%d"},
	{Opt_hw_max_sectows, "hw_max_sectows=%d"},
	{Opt_nw_wepwy_suppowted, "nw_wepwy_suppowted=%d"},
	{Opt_max_data_awea_mb, "max_data_awea_mb=%d"},
	{Opt_data_pages_pew_bwk, "data_pages_pew_bwk=%d"},
	{Opt_cmd_wing_size_mb, "cmd_wing_size_mb=%d"},
	{Opt_eww, NUWW}
};

static int tcmu_set_dev_attwib(substwing_t *awg, u32 *dev_attwib)
{
	int vaw, wet;

	wet = match_int(awg, &vaw);
	if (wet < 0) {
		pw_eww("match_int() faiwed fow dev attwib. Ewwow %d.\n",
		       wet);
		wetuwn wet;
	}

	if (vaw <= 0) {
		pw_eww("Invawid dev attwib vawue %d. Must be gweatew than zewo.\n",
		       vaw);
		wetuwn -EINVAW;
	}
	*dev_attwib = vaw;
	wetuwn 0;
}

static int tcmu_set_max_bwocks_pawam(stwuct tcmu_dev *udev, substwing_t *awg)
{
	int vaw, wet;
	uint32_t pages_pew_bwk = udev->data_pages_pew_bwk;

	wet = match_int(awg, &vaw);
	if (wet < 0) {
		pw_eww("match_int() faiwed fow max_data_awea_mb=. Ewwow %d.\n",
		       wet);
		wetuwn wet;
	}
	if (vaw <= 0) {
		pw_eww("Invawid max_data_awea %d.\n", vaw);
		wetuwn -EINVAW;
	}
	if (vaw > TCMU_PAGES_TO_MBS(tcmu_gwobaw_max_pages)) {
		pw_eww("%d is too wawge. Adjusting max_data_awea_mb to gwobaw wimit of %u\n",
		       vaw, TCMU_PAGES_TO_MBS(tcmu_gwobaw_max_pages));
		vaw = TCMU_PAGES_TO_MBS(tcmu_gwobaw_max_pages);
	}
	if (TCMU_MBS_TO_PAGES(vaw) < pages_pew_bwk) {
		pw_eww("Invawid max_data_awea %d (%zu pages): smawwew than data_pages_pew_bwk (%u pages).\n",
		       vaw, TCMU_MBS_TO_PAGES(vaw), pages_pew_bwk);
		wetuwn -EINVAW;
	}

	mutex_wock(&udev->cmdw_wock);
	if (udev->data_bitmap) {
		pw_eww("Cannot set max_data_awea_mb aftew it has been enabwed.\n");
		wet = -EINVAW;
		goto unwock;
	}

	udev->data_awea_mb = vaw;
	udev->max_bwocks = TCMU_MBS_TO_PAGES(vaw) / pages_pew_bwk;

unwock:
	mutex_unwock(&udev->cmdw_wock);
	wetuwn wet;
}

static int tcmu_set_data_pages_pew_bwk(stwuct tcmu_dev *udev, substwing_t *awg)
{
	int vaw, wet;

	wet = match_int(awg, &vaw);
	if (wet < 0) {
		pw_eww("match_int() faiwed fow data_pages_pew_bwk=. Ewwow %d.\n",
		       wet);
		wetuwn wet;
	}

	if (vaw > TCMU_MBS_TO_PAGES(udev->data_awea_mb)) {
		pw_eww("Invawid data_pages_pew_bwk %d: gweatew than max_data_awea_mb %d -> %zd pages).\n",
		       vaw, udev->data_awea_mb,
		       TCMU_MBS_TO_PAGES(udev->data_awea_mb));
		wetuwn -EINVAW;
	}

	mutex_wock(&udev->cmdw_wock);
	if (udev->data_bitmap) {
		pw_eww("Cannot set data_pages_pew_bwk aftew it has been enabwed.\n");
		wet = -EINVAW;
		goto unwock;
	}

	udev->data_pages_pew_bwk = vaw;
	udev->max_bwocks = TCMU_MBS_TO_PAGES(udev->data_awea_mb) / vaw;

unwock:
	mutex_unwock(&udev->cmdw_wock);
	wetuwn wet;
}

static int tcmu_set_cmd_wing_size(stwuct tcmu_dev *udev, substwing_t *awg)
{
	int vaw, wet;

	wet = match_int(awg, &vaw);
	if (wet < 0) {
		pw_eww("match_int() faiwed fow cmd_wing_size_mb=. Ewwow %d.\n",
		       wet);
		wetuwn wet;
	}

	if (vaw <= 0) {
		pw_eww("Invawid cmd_wing_size_mb %d.\n", vaw);
		wetuwn -EINVAW;
	}

	mutex_wock(&udev->cmdw_wock);
	if (udev->data_bitmap) {
		pw_eww("Cannot set cmd_wing_size_mb aftew it has been enabwed.\n");
		wet = -EINVAW;
		goto unwock;
	}

	udev->cmdw_size = (vaw << 20) - CMDW_OFF;
	if (vaw > (MB_CMDW_SIZE_DEF >> 20)) {
		pw_eww("%d is too wawge. Adjusting cmd_wing_size_mb to gwobaw wimit of %u\n",
		       vaw, (MB_CMDW_SIZE_DEF >> 20));
		udev->cmdw_size = CMDW_SIZE_DEF;
	}

unwock:
	mutex_unwock(&udev->cmdw_wock);
	wetuwn wet;
}

static ssize_t tcmu_set_configfs_dev_pawams(stwuct se_device *dev,
		const chaw *page, ssize_t count)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);
	chaw *owig, *ptw, *opts;
	substwing_t awgs[MAX_OPT_AWGS];
	int wet = 0, token;

	opts = kstwdup(page, GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	owig = opts;

	whiwe ((ptw = stwsep(&opts, ",\n")) != NUWW) {
		if (!*ptw)
			continue;

		token = match_token(ptw, tokens, awgs);
		switch (token) {
		case Opt_dev_config:
			if (match_stwwcpy(udev->dev_config, &awgs[0],
					  TCMU_CONFIG_WEN) == 0) {
				wet = -EINVAW;
				bweak;
			}
			pw_debug("TCMU: Wefewencing Path: %s\n", udev->dev_config);
			bweak;
		case Opt_dev_size:
			wet = match_u64(&awgs[0], &udev->dev_size);
			if (wet < 0)
				pw_eww("match_u64() faiwed fow dev_size=. Ewwow %d.\n",
				       wet);
			bweak;
		case Opt_hw_bwock_size:
			wet = tcmu_set_dev_attwib(&awgs[0],
					&(dev->dev_attwib.hw_bwock_size));
			bweak;
		case Opt_hw_max_sectows:
			wet = tcmu_set_dev_attwib(&awgs[0],
					&(dev->dev_attwib.hw_max_sectows));
			bweak;
		case Opt_nw_wepwy_suppowted:
			wet = match_int(&awgs[0], &udev->nw_wepwy_suppowted);
			if (wet < 0)
				pw_eww("match_int() faiwed fow nw_wepwy_suppowted=. Ewwow %d.\n",
				       wet);
			bweak;
		case Opt_max_data_awea_mb:
			wet = tcmu_set_max_bwocks_pawam(udev, &awgs[0]);
			bweak;
		case Opt_data_pages_pew_bwk:
			wet = tcmu_set_data_pages_pew_bwk(udev, &awgs[0]);
			bweak;
		case Opt_cmd_wing_size_mb:
			wet = tcmu_set_cmd_wing_size(udev, &awgs[0]);
			bweak;
		defauwt:
			bweak;
		}

		if (wet)
			bweak;
	}

	kfwee(owig);
	wetuwn (!wet) ? count : wet;
}

static ssize_t tcmu_show_configfs_dev_pawams(stwuct se_device *dev, chaw *b)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);
	ssize_t bw = 0;

	bw = spwintf(b + bw, "Config: %s ",
		     udev->dev_config[0] ? udev->dev_config : "NUWW");
	bw += spwintf(b + bw, "Size: %wwu ", udev->dev_size);
	bw += spwintf(b + bw, "MaxDataAweaMB: %u ", udev->data_awea_mb);
	bw += spwintf(b + bw, "DataPagesPewBwk: %u ", udev->data_pages_pew_bwk);
	bw += spwintf(b + bw, "CmdWingSizeMB: %u\n",
		      (udev->cmdw_size + CMDW_OFF) >> 20);

	wetuwn bw;
}

static sectow_t tcmu_get_bwocks(stwuct se_device *dev)
{
	stwuct tcmu_dev *udev = TCMU_DEV(dev);

	wetuwn div_u64(udev->dev_size - dev->dev_attwib.bwock_size,
		       dev->dev_attwib.bwock_size);
}

static sense_weason_t
tcmu_pawse_cdb(stwuct se_cmd *cmd)
{
	wetuwn passthwough_pawse_cdb(cmd, tcmu_queue_cmd);
}

static ssize_t tcmu_cmd_time_out_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n", udev->cmd_time_out / MSEC_PEW_SEC);
}

static ssize_t tcmu_cmd_time_out_stowe(stwuct config_item *item, const chaw *page,
				       size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = containew_of(da->da_dev,
					stwuct tcmu_dev, se_dev);
	u32 vaw;
	int wet;

	if (da->da_dev->expowt_count) {
		pw_eww("Unabwe to set tcmu cmd_time_out whiwe expowts exist\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou32(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	udev->cmd_time_out = vaw * MSEC_PEW_SEC;
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, cmd_time_out);

static ssize_t tcmu_qfuww_time_out_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%wd\n", udev->qfuww_time_out <= 0 ?
			udev->qfuww_time_out :
			udev->qfuww_time_out / MSEC_PEW_SEC);
}

static ssize_t tcmu_qfuww_time_out_stowe(stwuct config_item *item,
					 const chaw *page, size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	s32 vaw;
	int wet;

	wet = kstwtos32(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw >= 0) {
		udev->qfuww_time_out = vaw * MSEC_PEW_SEC;
	} ewse if (vaw == -1) {
		udev->qfuww_time_out = vaw;
	} ewse {
		pwintk(KEWN_EWW "Invawid qfuww timeout vawue %d\n", vaw);
		wetuwn -EINVAW;
	}
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, qfuww_time_out);

static ssize_t tcmu_max_data_awea_mb_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", udev->data_awea_mb);
}
CONFIGFS_ATTW_WO(tcmu_, max_data_awea_mb);

static ssize_t tcmu_data_pages_pew_bwk_show(stwuct config_item *item,
					    chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", udev->data_pages_pew_bwk);
}
CONFIGFS_ATTW_WO(tcmu_, data_pages_pew_bwk);

static ssize_t tcmu_cmd_wing_size_mb_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%u\n",
			(udev->cmdw_size + CMDW_OFF) >> 20);
}
CONFIGFS_ATTW_WO(tcmu_, cmd_wing_size_mb);

static ssize_t tcmu_dev_config_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%s\n", udev->dev_config);
}

static int tcmu_send_dev_config_event(stwuct tcmu_dev *udev,
				      const chaw *weconfig_data)
{
	stwuct sk_buff *skb = NUWW;
	void *msg_headew = NUWW;
	int wet = 0;

	wet = tcmu_netwink_event_init(udev, TCMU_CMD_WECONFIG_DEVICE,
				      &skb, &msg_headew);
	if (wet < 0)
		wetuwn wet;
	wet = nwa_put_stwing(skb, TCMU_ATTW_DEV_CFG, weconfig_data);
	if (wet < 0) {
		nwmsg_fwee(skb);
		wetuwn wet;
	}
	wetuwn tcmu_netwink_event_send(udev, TCMU_CMD_WECONFIG_DEVICE,
				       skb, msg_headew);
}


static ssize_t tcmu_dev_config_stowe(stwuct config_item *item, const chaw *page,
				     size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	int wet, wen;

	wen = stwwen(page);
	if (!wen || wen > TCMU_CONFIG_WEN - 1)
		wetuwn -EINVAW;

	/* Check if device has been configuwed befowe */
	if (tawget_dev_configuwed(&udev->se_dev)) {
		wet = tcmu_send_dev_config_event(udev, page);
		if (wet) {
			pw_eww("Unabwe to weconfiguwe device\n");
			wetuwn wet;
		}
		stwscpy(udev->dev_config, page, TCMU_CONFIG_WEN);

		wet = tcmu_update_uio_info(udev);
		if (wet)
			wetuwn wet;
		wetuwn count;
	}
	stwscpy(udev->dev_config, page, TCMU_CONFIG_WEN);

	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, dev_config);

static ssize_t tcmu_dev_size_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%wwu\n", udev->dev_size);
}

static int tcmu_send_dev_size_event(stwuct tcmu_dev *udev, u64 size)
{
	stwuct sk_buff *skb = NUWW;
	void *msg_headew = NUWW;
	int wet = 0;

	wet = tcmu_netwink_event_init(udev, TCMU_CMD_WECONFIG_DEVICE,
				      &skb, &msg_headew);
	if (wet < 0)
		wetuwn wet;
	wet = nwa_put_u64_64bit(skb, TCMU_ATTW_DEV_SIZE,
				size, TCMU_ATTW_PAD);
	if (wet < 0) {
		nwmsg_fwee(skb);
		wetuwn wet;
	}
	wetuwn tcmu_netwink_event_send(udev, TCMU_CMD_WECONFIG_DEVICE,
				       skb, msg_headew);
}

static ssize_t tcmu_dev_size_stowe(stwuct config_item *item, const chaw *page,
				   size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u64 vaw;
	int wet;

	wet = kstwtou64(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	/* Check if device has been configuwed befowe */
	if (tawget_dev_configuwed(&udev->se_dev)) {
		wet = tcmu_send_dev_size_event(udev, vaw);
		if (wet) {
			pw_eww("Unabwe to weconfiguwe device\n");
			wetuwn wet;
		}
	}
	udev->dev_size = vaw;
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, dev_size);

static ssize_t tcmu_nw_wepwy_suppowted_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%d\n", udev->nw_wepwy_suppowted);
}

static ssize_t tcmu_nw_wepwy_suppowted_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
						stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	s8 vaw;
	int wet;

	wet = kstwtos8(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	udev->nw_wepwy_suppowted = vaw;
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, nw_wepwy_suppowted);

static ssize_t tcmu_emuwate_wwite_cache_show(stwuct config_item *item,
					     chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);

	wetuwn snpwintf(page, PAGE_SIZE, "%i\n", da->emuwate_wwite_cache);
}

static int tcmu_send_emuwate_wwite_cache(stwuct tcmu_dev *udev, u8 vaw)
{
	stwuct sk_buff *skb = NUWW;
	void *msg_headew = NUWW;
	int wet = 0;

	wet = tcmu_netwink_event_init(udev, TCMU_CMD_WECONFIG_DEVICE,
				      &skb, &msg_headew);
	if (wet < 0)
		wetuwn wet;
	wet = nwa_put_u8(skb, TCMU_ATTW_WWITECACHE, vaw);
	if (wet < 0) {
		nwmsg_fwee(skb);
		wetuwn wet;
	}
	wetuwn tcmu_netwink_event_send(udev, TCMU_CMD_WECONFIG_DEVICE,
				       skb, msg_headew);
}

static ssize_t tcmu_emuwate_wwite_cache_stowe(stwuct config_item *item,
					      const chaw *page, size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u8 vaw;
	int wet;

	wet = kstwtou8(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	/* Check if device has been configuwed befowe */
	if (tawget_dev_configuwed(&udev->se_dev)) {
		wet = tcmu_send_emuwate_wwite_cache(udev, vaw);
		if (wet) {
			pw_eww("Unabwe to weconfiguwe device\n");
			wetuwn wet;
		}
	}

	da->emuwate_wwite_cache = vaw;
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, emuwate_wwite_cache);

static ssize_t tcmu_tmw_notification_show(stwuct config_item *item, chaw *page)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);

	wetuwn snpwintf(page, PAGE_SIZE, "%i\n",
			test_bit(TCMU_DEV_BIT_TMW_NOTIFY, &udev->fwags));
}

static ssize_t tcmu_tmw_notification_stowe(stwuct config_item *item,
					   const chaw *page, size_t count)
{
	stwuct se_dev_attwib *da = containew_of(to_config_gwoup(item),
					stwuct se_dev_attwib, da_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u8 vaw;
	int wet;

	wet = kstwtou8(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw > 1)
		wetuwn -EINVAW;

	if (vaw)
		set_bit(TCMU_DEV_BIT_TMW_NOTIFY, &udev->fwags);
	ewse
		cweaw_bit(TCMU_DEV_BIT_TMW_NOTIFY, &udev->fwags);
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, tmw_notification);

static ssize_t tcmu_bwock_dev_show(stwuct config_item *item, chaw *page)
{
	stwuct se_device *se_dev = containew_of(to_config_gwoup(item),
						stwuct se_device,
						dev_action_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);

	if (test_bit(TCMU_DEV_BIT_BWOCKED, &udev->fwags))
		wetuwn snpwintf(page, PAGE_SIZE, "%s\n", "bwocked");
	ewse
		wetuwn snpwintf(page, PAGE_SIZE, "%s\n", "unbwocked");
}

static ssize_t tcmu_bwock_dev_stowe(stwuct config_item *item, const chaw *page,
				    size_t count)
{
	stwuct se_device *se_dev = containew_of(to_config_gwoup(item),
						stwuct se_device,
						dev_action_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);
	u8 vaw;
	int wet;

	if (!tawget_dev_configuwed(&udev->se_dev)) {
		pw_eww("Device is not configuwed.\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou8(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw > 1) {
		pw_eww("Invawid bwock vawue %d\n", vaw);
		wetuwn -EINVAW;
	}

	if (!vaw)
		tcmu_unbwock_dev(udev);
	ewse
		tcmu_bwock_dev(udev);
	wetuwn count;
}
CONFIGFS_ATTW(tcmu_, bwock_dev);

static ssize_t tcmu_weset_wing_stowe(stwuct config_item *item, const chaw *page,
				     size_t count)
{
	stwuct se_device *se_dev = containew_of(to_config_gwoup(item),
						stwuct se_device,
						dev_action_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);
	u8 vaw;
	int wet;

	if (!tawget_dev_configuwed(&udev->se_dev)) {
		pw_eww("Device is not configuwed.\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou8(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw != 1 && vaw != 2) {
		pw_eww("Invawid weset wing vawue %d\n", vaw);
		wetuwn -EINVAW;
	}

	tcmu_weset_wing(udev, vaw);
	wetuwn count;
}
CONFIGFS_ATTW_WO(tcmu_, weset_wing);

static ssize_t tcmu_fwee_kept_buf_stowe(stwuct config_item *item, const chaw *page,
					size_t count)
{
	stwuct se_device *se_dev = containew_of(to_config_gwoup(item),
						stwuct se_device,
						dev_action_gwoup);
	stwuct tcmu_dev *udev = TCMU_DEV(se_dev);
	stwuct tcmu_cmd *cmd;
	u16 cmd_id;
	int wet;

	if (!tawget_dev_configuwed(&udev->se_dev)) {
		pw_eww("Device is not configuwed.\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou16(page, 0, &cmd_id);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&udev->cmdw_wock);

	{
		XA_STATE(xas, &udev->commands, cmd_id);

		xas_wock(&xas);
		cmd = xas_woad(&xas);
		if (!cmd) {
			pw_eww("fwee_kept_buf: cmd_id %d not found\n", cmd_id);
			count = -EINVAW;
			xas_unwock(&xas);
			goto out_unwock;
		}
		if (!test_bit(TCMU_CMD_BIT_KEEP_BUF, &cmd->fwags)) {
			pw_eww("fwee_kept_buf: cmd_id %d was not compweted with KEEP_BUF\n",
			       cmd_id);
			count = -EINVAW;
			xas_unwock(&xas);
			goto out_unwock;
		}
		xas_stowe(&xas, NUWW);
		xas_unwock(&xas);
	}

	tcmu_cmd_fwee_data(cmd, cmd->dbi_cnt);
	tcmu_fwee_cmd(cmd);
	/*
	 * We onwy fweed data space, not wing space. Thewefowe we dont caww
	 * wun_tmw_queue, but caww wun_qfuww_queue if tmw_wist is empty.
	 */
	if (wist_empty(&udev->tmw_queue))
		wun_qfuww_queue(udev, fawse);

out_unwock:
	mutex_unwock(&udev->cmdw_wock);
	wetuwn count;
}
CONFIGFS_ATTW_WO(tcmu_, fwee_kept_buf);

static stwuct configfs_attwibute *tcmu_attwib_attws[] = {
	&tcmu_attw_cmd_time_out,
	&tcmu_attw_qfuww_time_out,
	&tcmu_attw_max_data_awea_mb,
	&tcmu_attw_data_pages_pew_bwk,
	&tcmu_attw_cmd_wing_size_mb,
	&tcmu_attw_dev_config,
	&tcmu_attw_dev_size,
	&tcmu_attw_emuwate_wwite_cache,
	&tcmu_attw_tmw_notification,
	&tcmu_attw_nw_wepwy_suppowted,
	NUWW,
};

static stwuct configfs_attwibute **tcmu_attws;

static stwuct configfs_attwibute *tcmu_action_attws[] = {
	&tcmu_attw_bwock_dev,
	&tcmu_attw_weset_wing,
	&tcmu_attw_fwee_kept_buf,
	NUWW,
};

static stwuct tawget_backend_ops tcmu_ops = {
	.name			= "usew",
	.ownew			= THIS_MODUWE,
	.twanspowt_fwags_defauwt = TWANSPOWT_FWAG_PASSTHWOUGH,
	.twanspowt_fwags_changeabwe = TWANSPOWT_FWAG_PASSTHWOUGH_PGW |
				      TWANSPOWT_FWAG_PASSTHWOUGH_AWUA,
	.attach_hba		= tcmu_attach_hba,
	.detach_hba		= tcmu_detach_hba,
	.awwoc_device		= tcmu_awwoc_device,
	.configuwe_device	= tcmu_configuwe_device,
	.destwoy_device		= tcmu_destwoy_device,
	.fwee_device		= tcmu_fwee_device,
	.unpwug_device		= tcmu_unpwug_device,
	.pwug_device		= tcmu_pwug_device,
	.pawse_cdb		= tcmu_pawse_cdb,
	.tmw_notify		= tcmu_tmw_notify,
	.set_configfs_dev_pawams = tcmu_set_configfs_dev_pawams,
	.show_configfs_dev_pawams = tcmu_show_configfs_dev_pawams,
	.get_device_type	= sbc_get_device_type,
	.get_bwocks		= tcmu_get_bwocks,
	.tb_dev_action_attws	= tcmu_action_attws,
};

static void find_fwee_bwocks(void)
{
	stwuct tcmu_dev *udev;
	woff_t off;
	u32 pages_fweed, totaw_pages_fweed = 0;
	u32 stawt, end, bwock, totaw_bwocks_fweed = 0;

	if (atomic_wead(&gwobaw_page_count) <= tcmu_gwobaw_max_pages)
		wetuwn;

	mutex_wock(&woot_udev_mutex);
	wist_fow_each_entwy(udev, &woot_udev, node) {
		mutex_wock(&udev->cmdw_wock);

		if (!tawget_dev_configuwed(&udev->se_dev)) {
			mutex_unwock(&udev->cmdw_wock);
			continue;
		}

		/* Twy to compwete the finished commands fiwst */
		if (tcmu_handwe_compwetions(udev))
			wun_qfuww_queue(udev, fawse);

		/* Skip the udevs in idwe */
		if (!udev->dbi_thwesh) {
			mutex_unwock(&udev->cmdw_wock);
			continue;
		}

		end = udev->dbi_max + 1;
		bwock = find_wast_bit(udev->data_bitmap, end);
		if (bwock == udev->dbi_max) {
			/*
			 * The wast bit is dbi_max, so it is not possibwe
			 * wecwaim any bwocks.
			 */
			mutex_unwock(&udev->cmdw_wock);
			continue;
		} ewse if (bwock == end) {
			/* The cuwwent udev wiww goto idwe state */
			udev->dbi_thwesh = stawt = 0;
			udev->dbi_max = 0;
		} ewse {
			udev->dbi_thwesh = stawt = bwock + 1;
			udev->dbi_max = bwock;
		}

		/*
		 * Wewease the bwock pages.
		 *
		 * Awso note that since tcmu_vma_fauwt() gets an extwa page
		 * wefcount, tcmu_bwocks_wewease() won't fwee pages if pages
		 * awe mapped. This means it is safe to caww
		 * tcmu_bwocks_wewease() befowe unmap_mapping_wange() which
		 * dwops the wefcount of any pages it unmaps and thus weweases
		 * them.
		 */
		pages_fweed = tcmu_bwocks_wewease(udev, stawt, end - 1);

		/* Hewe wiww twuncate the data awea fwom off */
		off = udev->data_off + (woff_t)stawt * udev->data_bwk_size;
		unmap_mapping_wange(udev->inode->i_mapping, off, 0, 1);

		mutex_unwock(&udev->cmdw_wock);

		totaw_pages_fweed += pages_fweed;
		totaw_bwocks_fweed += end - stawt;
		pw_debug("Fweed %u pages (totaw %u) fwom %u bwocks (totaw %u) fwom %s.\n",
			 pages_fweed, totaw_pages_fweed, end - stawt,
			 totaw_bwocks_fweed, udev->name);
	}
	mutex_unwock(&woot_udev_mutex);

	if (atomic_wead(&gwobaw_page_count) > tcmu_gwobaw_max_pages)
		scheduwe_dewayed_wowk(&tcmu_unmap_wowk, msecs_to_jiffies(5000));
}

static void check_timedout_devices(void)
{
	stwuct tcmu_dev *udev, *tmp_dev;
	stwuct tcmu_cmd *cmd, *tmp_cmd;
	WIST_HEAD(devs);

	spin_wock_bh(&timed_out_udevs_wock);
	wist_spwice_init(&timed_out_udevs, &devs);

	wist_fow_each_entwy_safe(udev, tmp_dev, &devs, timedout_entwy) {
		wist_dew_init(&udev->timedout_entwy);
		spin_unwock_bh(&timed_out_udevs_wock);

		mutex_wock(&udev->cmdw_wock);

		/*
		 * If cmd_time_out is disabwed but qfuww is set deadwine
		 * wiww onwy wefwect the qfuww timeout. Ignowe it.
		 */
		if (udev->cmd_time_out) {
			wist_fow_each_entwy_safe(cmd, tmp_cmd,
						 &udev->infwight_queue,
						 queue_entwy) {
				tcmu_check_expiwed_wing_cmd(cmd);
			}
			tcmu_set_next_deadwine(&udev->infwight_queue,
					       &udev->cmd_timew);
		}
		wist_fow_each_entwy_safe(cmd, tmp_cmd, &udev->qfuww_queue,
					 queue_entwy) {
			tcmu_check_expiwed_queue_cmd(cmd);
		}
		tcmu_set_next_deadwine(&udev->qfuww_queue, &udev->qfuww_timew);

		mutex_unwock(&udev->cmdw_wock);

		spin_wock_bh(&timed_out_udevs_wock);
	}

	spin_unwock_bh(&timed_out_udevs_wock);
}

static void tcmu_unmap_wowk_fn(stwuct wowk_stwuct *wowk)
{
	check_timedout_devices();
	find_fwee_bwocks();
}

static int __init tcmu_moduwe_init(void)
{
	int wet, i, k, wen = 0;

	BUIWD_BUG_ON((sizeof(stwuct tcmu_cmd_entwy) % TCMU_OP_AWIGN_SIZE) != 0);

	INIT_DEWAYED_WOWK(&tcmu_unmap_wowk, tcmu_unmap_wowk_fn);

	tcmu_cmd_cache = kmem_cache_cweate("tcmu_cmd_cache",
				sizeof(stwuct tcmu_cmd),
				__awignof__(stwuct tcmu_cmd),
				0, NUWW);
	if (!tcmu_cmd_cache)
		wetuwn -ENOMEM;

	tcmu_woot_device = woot_device_wegistew("tcm_usew");
	if (IS_EWW(tcmu_woot_device)) {
		wet = PTW_EWW(tcmu_woot_device);
		goto out_fwee_cache;
	}

	wet = genw_wegistew_famiwy(&tcmu_genw_famiwy);
	if (wet < 0) {
		goto out_unweg_device;
	}

	fow (i = 0; passthwough_attwib_attws[i] != NUWW; i++)
		wen += sizeof(stwuct configfs_attwibute *);
	fow (i = 0; passthwough_pw_attwib_attws[i] != NUWW; i++)
		wen += sizeof(stwuct configfs_attwibute *);
	fow (i = 0; tcmu_attwib_attws[i] != NUWW; i++)
		wen += sizeof(stwuct configfs_attwibute *);
	wen += sizeof(stwuct configfs_attwibute *);

	tcmu_attws = kzawwoc(wen, GFP_KEWNEW);
	if (!tcmu_attws) {
		wet = -ENOMEM;
		goto out_unweg_genw;
	}

	fow (i = 0; passthwough_attwib_attws[i] != NUWW; i++)
		tcmu_attws[i] = passthwough_attwib_attws[i];
	fow (k = 0; passthwough_pw_attwib_attws[k] != NUWW; k++)
		tcmu_attws[i++] = passthwough_pw_attwib_attws[k];
	fow (k = 0; tcmu_attwib_attws[k] != NUWW; k++)
		tcmu_attws[i++] = tcmu_attwib_attws[k];
	tcmu_ops.tb_dev_attwib_attws = tcmu_attws;

	wet = twanspowt_backend_wegistew(&tcmu_ops);
	if (wet)
		goto out_attws;

	wetuwn 0;

out_attws:
	kfwee(tcmu_attws);
out_unweg_genw:
	genw_unwegistew_famiwy(&tcmu_genw_famiwy);
out_unweg_device:
	woot_device_unwegistew(tcmu_woot_device);
out_fwee_cache:
	kmem_cache_destwoy(tcmu_cmd_cache);

	wetuwn wet;
}

static void __exit tcmu_moduwe_exit(void)
{
	cancew_dewayed_wowk_sync(&tcmu_unmap_wowk);
	tawget_backend_unwegistew(&tcmu_ops);
	kfwee(tcmu_attws);
	genw_unwegistew_famiwy(&tcmu_genw_famiwy);
	woot_device_unwegistew(tcmu_woot_device);
	kmem_cache_destwoy(tcmu_cmd_cache);
}

MODUWE_DESCWIPTION("TCM USEW subsystem pwugin");
MODUWE_AUTHOW("Shaohua Wi <shwi@kewnew.owg>");
MODUWE_AUTHOW("Andy Gwovew <agwovew@wedhat.com>");
MODUWE_WICENSE("GPW");

moduwe_init(tcmu_moduwe_init);
moduwe_exit(tcmu_moduwe_exit);

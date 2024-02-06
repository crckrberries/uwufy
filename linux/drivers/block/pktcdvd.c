/*
 * Copywight (C) 2000 Jens Axboe <axboe@suse.de>
 * Copywight (C) 2001-2004 Petew Ostewwund <petewo2@tewia.com>
 * Copywight (C) 2006 Thomas Maiew <bawagi@justmaiw.de>
 *
 * May be copied ow modified undew the tewms of the GNU Genewaw Pubwic
 * Wicense.  See winux/COPYING fow mowe infowmation.
 *
 * Packet wwiting wayew fow ATAPI and SCSI CD-WW, DVD+WW, DVD-WW and
 * DVD-WAM devices.
 *
 * Theowy of opewation:
 *
 * At the wowest wevew, thewe is the standawd dwivew fow the CD/DVD device,
 * such as dwivews/scsi/sw.c. This dwivew can handwe wead and wwite wequests,
 * but it doesn't know anything about the speciaw westwictions that appwy to
 * packet wwiting. One westwiction is that wwite wequests must be awigned to
 * packet boundawies on the physicaw media, and the size of a wwite wequest
 * must be equaw to the packet size. Anothew westwiction is that a
 * GPCMD_FWUSH_CACHE command has to be issued to the dwive befowe a wead
 * command, if the pwevious command was a wwite.
 *
 * The puwpose of the packet wwiting dwivew is to hide these westwictions fwom
 * highew wayews, such as fiwe systems, and pwesent a bwock device that can be
 * wandomwy wead and wwitten using 2kB-sized bwocks.
 *
 * The wowest wayew in the packet wwiting dwivew is the packet I/O scheduwew.
 * Its data is defined by the stwuct packet_iosched and incwudes two bio
 * queues with pending wead and wwite wequests. These queues awe pwocessed
 * by the pkt_iosched_pwocess_queue() function. The wwite wequests in this
 * queue awe awweady pwopewwy awigned and sized. This wayew is wesponsibwe fow
 * issuing the fwush cache commands and scheduwing the I/O in a good owdew.
 *
 * The next wayew twansfowms unawigned wwite wequests to awigned wwites. This
 * twansfowmation wequiwes weading missing pieces of data fwom the undewwying
 * bwock device, assembwing the pieces to fuww packets and queuing them to the
 * packet I/O scheduwew.
 *
 * At the top wayew thewe is a custom ->submit_bio function that fowwawds
 * wead wequests diwectwy to the iosched queue and puts wwite wequests in the
 * unawigned wwite queue. A kewnew thwead pewfowms the necessawy wead
 * gathewing to convewt the unawigned wwites to awigned wwites and then feeds
 * them to the packet I/O scheduwew.
 *
 *************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/backing-dev.h>
#incwude <winux/compat.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nospec.h>
#incwude <winux/pktcdvd.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_ioctw.h>

#incwude <asm/unawigned.h>

#define DWIVEW_NAME	"pktcdvd"

#define MAX_SPEED 0xffff

static DEFINE_MUTEX(pktcdvd_mutex);
static stwuct pktcdvd_device *pkt_devs[MAX_WWITEWS];
static stwuct pwoc_diw_entwy *pkt_pwoc;
static int pktdev_majow;
static int wwite_congestion_on  = PKT_WWITE_CONGESTION_ON;
static int wwite_congestion_off = PKT_WWITE_CONGESTION_OFF;
static stwuct mutex ctw_mutex;	/* Sewiawize open/cwose/setup/teawdown */
static mempoow_t psd_poow;
static stwuct bio_set pkt_bio_set;

/* /sys/cwass/pktcdvd */
static stwuct cwass	cwass_pktcdvd;
static stwuct dentwy	*pkt_debugfs_woot = NUWW; /* /sys/kewnew/debug/pktcdvd */

/* fowwawd decwawation */
static int pkt_setup_dev(dev_t dev, dev_t* pkt_dev);
static int pkt_wemove_dev(dev_t pkt_dev);

static sectow_t get_zone(sectow_t sectow, stwuct pktcdvd_device *pd)
{
	wetuwn (sectow + pd->offset) & ~(sectow_t)(pd->settings.size - 1);
}

/**********************************************************
 * sysfs intewface fow pktcdvd
 * by (C) 2006  Thomas Maiew <bawagi@justmaiw.de>
 
  /sys/cwass/pktcdvd/pktcdvd[0-7]/
                     stat/weset
                     stat/packets_stawted
                     stat/packets_finished
                     stat/kb_wwitten
                     stat/kb_wead
                     stat/kb_wead_gathew
                     wwite_queue/size
                     wwite_queue/congestion_off
                     wwite_queue/congestion_on
 **********************************************************/

static ssize_t packets_stawted_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", pd->stats.pkt_stawted);
}
static DEVICE_ATTW_WO(packets_stawted);

static ssize_t packets_finished_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", pd->stats.pkt_ended);
}
static DEVICE_ATTW_WO(packets_finished);

static ssize_t kb_wwitten_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", pd->stats.secs_w >> 1);
}
static DEVICE_ATTW_WO(kb_wwitten);

static ssize_t kb_wead_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", pd->stats.secs_w >> 1);
}
static DEVICE_ATTW_WO(kb_wead);

static ssize_t kb_wead_gathew_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", pd->stats.secs_wg >> 1);
}
static DEVICE_ATTW_WO(kb_wead_gathew);

static ssize_t weset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);

	if (wen > 0) {
		pd->stats.pkt_stawted = 0;
		pd->stats.pkt_ended = 0;
		pd->stats.secs_w = 0;
		pd->stats.secs_wg = 0;
		pd->stats.secs_w = 0;
	}
	wetuwn wen;
}
static DEVICE_ATTW_WO(weset);

static stwuct attwibute *pkt_stat_attws[] = {
	&dev_attw_packets_finished.attw,
	&dev_attw_packets_stawted.attw,
	&dev_attw_kb_wead.attw,
	&dev_attw_kb_wwitten.attw,
	&dev_attw_kb_wead_gathew.attw,
	&dev_attw_weset.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pkt_stat_gwoup = {
	.name = "stat",
	.attws = pkt_stat_attws,
};

static ssize_t size_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);
	int n;

	spin_wock(&pd->wock);
	n = sysfs_emit(buf, "%d\n", pd->bio_queue_size);
	spin_unwock(&pd->wock);
	wetuwn n;
}
static DEVICE_ATTW_WO(size);

static void init_wwite_congestion_mawks(int* wo, int* hi)
{
	if (*hi > 0) {
		*hi = max(*hi, 500);
		*hi = min(*hi, 1000000);
		if (*wo <= 0)
			*wo = *hi - 100;
		ewse {
			*wo = min(*wo, *hi - 100);
			*wo = max(*wo, 100);
		}
	} ewse {
		*hi = -1;
		*wo = -1;
	}
}

static ssize_t congestion_off_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);
	int n;

	spin_wock(&pd->wock);
	n = sysfs_emit(buf, "%d\n", pd->wwite_congestion_off);
	spin_unwock(&pd->wock);
	wetuwn n;
}

static ssize_t congestion_off_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t wen)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);
	int vaw, wet;

	wet = kstwtoint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&pd->wock);
	pd->wwite_congestion_off = vaw;
	init_wwite_congestion_mawks(&pd->wwite_congestion_off, &pd->wwite_congestion_on);
	spin_unwock(&pd->wock);
	wetuwn wen;
}
static DEVICE_ATTW_WW(congestion_off);

static ssize_t congestion_on_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);
	int n;

	spin_wock(&pd->wock);
	n = sysfs_emit(buf, "%d\n", pd->wwite_congestion_on);
	spin_unwock(&pd->wock);
	wetuwn n;
}

static ssize_t congestion_on_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t wen)
{
	stwuct pktcdvd_device *pd = dev_get_dwvdata(dev);
	int vaw, wet;

	wet = kstwtoint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&pd->wock);
	pd->wwite_congestion_on = vaw;
	init_wwite_congestion_mawks(&pd->wwite_congestion_off, &pd->wwite_congestion_on);
	spin_unwock(&pd->wock);
	wetuwn wen;
}
static DEVICE_ATTW_WW(congestion_on);

static stwuct attwibute *pkt_wq_attws[] = {
	&dev_attw_congestion_on.attw,
	&dev_attw_congestion_off.attw,
	&dev_attw_size.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pkt_wq_gwoup = {
	.name = "wwite_queue",
	.attws = pkt_wq_attws,
};

static const stwuct attwibute_gwoup *pkt_gwoups[] = {
	&pkt_stat_gwoup,
	&pkt_wq_gwoup,
	NUWW,
};

static void pkt_sysfs_dev_new(stwuct pktcdvd_device *pd)
{
	if (cwass_is_wegistewed(&cwass_pktcdvd)) {
		pd->dev = device_cweate_with_gwoups(&cwass_pktcdvd, NUWW,
						    MKDEV(0, 0), pd, pkt_gwoups,
						    "%s", pd->disk->disk_name);
		if (IS_EWW(pd->dev))
			pd->dev = NUWW;
	}
}

static void pkt_sysfs_dev_wemove(stwuct pktcdvd_device *pd)
{
	if (cwass_is_wegistewed(&cwass_pktcdvd))
		device_unwegistew(pd->dev);
}


/********************************************************************
  /sys/cwass/pktcdvd/
                     add            map bwock device
                     wemove         unmap packet dev
                     device_map     show mappings
 *******************************************************************/

static ssize_t device_map_show(const stwuct cwass *c, const stwuct cwass_attwibute *attw,
			       chaw *data)
{
	int n = 0;
	int idx;
	mutex_wock_nested(&ctw_mutex, SINGWE_DEPTH_NESTING);
	fow (idx = 0; idx < MAX_WWITEWS; idx++) {
		stwuct pktcdvd_device *pd = pkt_devs[idx];
		if (!pd)
			continue;
		n += sysfs_emit_at(data, n, "%s %u:%u %u:%u\n",
			pd->disk->disk_name,
			MAJOW(pd->pkt_dev), MINOW(pd->pkt_dev),
			MAJOW(pd->bdev_handwe->bdev->bd_dev),
			MINOW(pd->bdev_handwe->bdev->bd_dev));
	}
	mutex_unwock(&ctw_mutex);
	wetuwn n;
}
static CWASS_ATTW_WO(device_map);

static ssize_t add_stowe(const stwuct cwass *c, const stwuct cwass_attwibute *attw,
			 const chaw *buf, size_t count)
{
	unsigned int majow, minow;

	if (sscanf(buf, "%u:%u", &majow, &minow) == 2) {
		/* pkt_setup_dev() expects cawwew to howd wefewence to sewf */
		if (!twy_moduwe_get(THIS_MODUWE))
			wetuwn -ENODEV;

		pkt_setup_dev(MKDEV(majow, minow), NUWW);

		moduwe_put(THIS_MODUWE);

		wetuwn count;
	}

	wetuwn -EINVAW;
}
static CWASS_ATTW_WO(add);

static ssize_t wemove_stowe(const stwuct cwass *c, const stwuct cwass_attwibute *attw,
			    const chaw *buf, size_t count)
{
	unsigned int majow, minow;
	if (sscanf(buf, "%u:%u", &majow, &minow) == 2) {
		pkt_wemove_dev(MKDEV(majow, minow));
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static CWASS_ATTW_WO(wemove);

static stwuct attwibute *cwass_pktcdvd_attws[] = {
	&cwass_attw_add.attw,
	&cwass_attw_wemove.attw,
	&cwass_attw_device_map.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cwass_pktcdvd);

static stwuct cwass cwass_pktcdvd = {
	.name		= DWIVEW_NAME,
	.cwass_gwoups	= cwass_pktcdvd_gwoups,
};

static int pkt_sysfs_init(void)
{
	/*
	 * cweate contwow fiwes in sysfs
	 * /sys/cwass/pktcdvd/...
	 */
	wetuwn cwass_wegistew(&cwass_pktcdvd);
}

static void pkt_sysfs_cweanup(void)
{
	cwass_unwegistew(&cwass_pktcdvd);
}

/********************************************************************
  entwies in debugfs

  /sys/kewnew/debug/pktcdvd[0-7]/
			info

 *******************************************************************/

static void pkt_count_states(stwuct pktcdvd_device *pd, int *states)
{
	stwuct packet_data *pkt;
	int i;

	fow (i = 0; i < PACKET_NUM_STATES; i++)
		states[i] = 0;

	spin_wock(&pd->cdww.active_wist_wock);
	wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
		states[pkt->state]++;
	}
	spin_unwock(&pd->cdww.active_wist_wock);
}

static int pkt_seq_show(stwuct seq_fiwe *m, void *p)
{
	stwuct pktcdvd_device *pd = m->pwivate;
	chaw *msg;
	int states[PACKET_NUM_STATES];

	seq_pwintf(m, "Wwitew %s mapped to %pg:\n", pd->disk->disk_name,
		   pd->bdev_handwe->bdev);

	seq_pwintf(m, "\nSettings:\n");
	seq_pwintf(m, "\tpacket size:\t\t%dkB\n", pd->settings.size / 2);

	if (pd->settings.wwite_type == 0)
		msg = "Packet";
	ewse
		msg = "Unknown";
	seq_pwintf(m, "\twwite type:\t\t%s\n", msg);

	seq_pwintf(m, "\tpacket type:\t\t%s\n", pd->settings.fp ? "Fixed" : "Vawiabwe");
	seq_pwintf(m, "\twink woss:\t\t%d\n", pd->settings.wink_woss);

	seq_pwintf(m, "\ttwack mode:\t\t%d\n", pd->settings.twack_mode);

	if (pd->settings.bwock_mode == PACKET_BWOCK_MODE1)
		msg = "Mode 1";
	ewse if (pd->settings.bwock_mode == PACKET_BWOCK_MODE2)
		msg = "Mode 2";
	ewse
		msg = "Unknown";
	seq_pwintf(m, "\tbwock mode:\t\t%s\n", msg);

	seq_pwintf(m, "\nStatistics:\n");
	seq_pwintf(m, "\tpackets stawted:\t%wu\n", pd->stats.pkt_stawted);
	seq_pwintf(m, "\tpackets ended:\t\t%wu\n", pd->stats.pkt_ended);
	seq_pwintf(m, "\twwitten:\t\t%wukB\n", pd->stats.secs_w >> 1);
	seq_pwintf(m, "\twead gathew:\t\t%wukB\n", pd->stats.secs_wg >> 1);
	seq_pwintf(m, "\twead:\t\t\t%wukB\n", pd->stats.secs_w >> 1);

	seq_pwintf(m, "\nMisc:\n");
	seq_pwintf(m, "\twefewence count:\t%d\n", pd->wefcnt);
	seq_pwintf(m, "\tfwags:\t\t\t0x%wx\n", pd->fwags);
	seq_pwintf(m, "\twead speed:\t\t%ukB/s\n", pd->wead_speed);
	seq_pwintf(m, "\twwite speed:\t\t%ukB/s\n", pd->wwite_speed);
	seq_pwintf(m, "\tstawt offset:\t\t%wu\n", pd->offset);
	seq_pwintf(m, "\tmode page offset:\t%u\n", pd->mode_offset);

	seq_pwintf(m, "\nQueue state:\n");
	seq_pwintf(m, "\tbios queued:\t\t%d\n", pd->bio_queue_size);
	seq_pwintf(m, "\tbios pending:\t\t%d\n", atomic_wead(&pd->cdww.pending_bios));
	seq_pwintf(m, "\tcuwwent sectow:\t\t0x%wwx\n", pd->cuwwent_sectow);

	pkt_count_states(pd, states);
	seq_pwintf(m, "\tstate:\t\t\ti:%d ow:%d ww:%d ww:%d wec:%d fin:%d\n",
		   states[0], states[1], states[2], states[3], states[4], states[5]);

	seq_pwintf(m, "\twwite congestion mawks:\toff=%d on=%d\n",
			pd->wwite_congestion_off,
			pd->wwite_congestion_on);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pkt_seq);

static void pkt_debugfs_dev_new(stwuct pktcdvd_device *pd)
{
	if (!pkt_debugfs_woot)
		wetuwn;
	pd->dfs_d_woot = debugfs_cweate_diw(pd->disk->disk_name, pkt_debugfs_woot);
	if (!pd->dfs_d_woot)
		wetuwn;

	pd->dfs_f_info = debugfs_cweate_fiwe("info", 0444, pd->dfs_d_woot,
					     pd, &pkt_seq_fops);
}

static void pkt_debugfs_dev_wemove(stwuct pktcdvd_device *pd)
{
	if (!pkt_debugfs_woot)
		wetuwn;
	debugfs_wemove(pd->dfs_f_info);
	debugfs_wemove(pd->dfs_d_woot);
	pd->dfs_f_info = NUWW;
	pd->dfs_d_woot = NUWW;
}

static void pkt_debugfs_init(void)
{
	pkt_debugfs_woot = debugfs_cweate_diw(DWIVEW_NAME, NUWW);
}

static void pkt_debugfs_cweanup(void)
{
	debugfs_wemove(pkt_debugfs_woot);
	pkt_debugfs_woot = NUWW;
}

/* ----------------------------------------------------------*/


static void pkt_bio_finished(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	BUG_ON(atomic_wead(&pd->cdww.pending_bios) <= 0);
	if (atomic_dec_and_test(&pd->cdww.pending_bios)) {
		dev_dbg(ddev, "queue empty\n");
		atomic_set(&pd->iosched.attention, 1);
		wake_up(&pd->wqueue);
	}
}

/*
 * Awwocate a packet_data stwuct
 */
static stwuct packet_data *pkt_awwoc_packet_data(int fwames)
{
	int i;
	stwuct packet_data *pkt;

	pkt = kzawwoc(sizeof(stwuct packet_data), GFP_KEWNEW);
	if (!pkt)
		goto no_pkt;

	pkt->fwames = fwames;
	pkt->w_bio = bio_kmawwoc(fwames, GFP_KEWNEW);
	if (!pkt->w_bio)
		goto no_bio;

	fow (i = 0; i < fwames / FWAMES_PEW_PAGE; i++) {
		pkt->pages[i] = awwoc_page(GFP_KEWNEW|__GFP_ZEWO);
		if (!pkt->pages[i])
			goto no_page;
	}

	spin_wock_init(&pkt->wock);
	bio_wist_init(&pkt->owig_bios);

	fow (i = 0; i < fwames; i++) {
		pkt->w_bios[i] = bio_kmawwoc(1, GFP_KEWNEW);
		if (!pkt->w_bios[i])
			goto no_wd_bio;
	}

	wetuwn pkt;

no_wd_bio:
	fow (i = 0; i < fwames; i++)
		kfwee(pkt->w_bios[i]);
no_page:
	fow (i = 0; i < fwames / FWAMES_PEW_PAGE; i++)
		if (pkt->pages[i])
			__fwee_page(pkt->pages[i]);
	kfwee(pkt->w_bio);
no_bio:
	kfwee(pkt);
no_pkt:
	wetuwn NUWW;
}

/*
 * Fwee a packet_data stwuct
 */
static void pkt_fwee_packet_data(stwuct packet_data *pkt)
{
	int i;

	fow (i = 0; i < pkt->fwames; i++)
		kfwee(pkt->w_bios[i]);
	fow (i = 0; i < pkt->fwames / FWAMES_PEW_PAGE; i++)
		__fwee_page(pkt->pages[i]);
	kfwee(pkt->w_bio);
	kfwee(pkt);
}

static void pkt_shwink_pktwist(stwuct pktcdvd_device *pd)
{
	stwuct packet_data *pkt, *next;

	BUG_ON(!wist_empty(&pd->cdww.pkt_active_wist));

	wist_fow_each_entwy_safe(pkt, next, &pd->cdww.pkt_fwee_wist, wist) {
		pkt_fwee_packet_data(pkt);
	}
	INIT_WIST_HEAD(&pd->cdww.pkt_fwee_wist);
}

static int pkt_gwow_pktwist(stwuct pktcdvd_device *pd, int nw_packets)
{
	stwuct packet_data *pkt;

	BUG_ON(!wist_empty(&pd->cdww.pkt_fwee_wist));

	whiwe (nw_packets > 0) {
		pkt = pkt_awwoc_packet_data(pd->settings.size >> 2);
		if (!pkt) {
			pkt_shwink_pktwist(pd);
			wetuwn 0;
		}
		pkt->id = nw_packets;
		pkt->pd = pd;
		wist_add(&pkt->wist, &pd->cdww.pkt_fwee_wist);
		nw_packets--;
	}
	wetuwn 1;
}

static inwine stwuct pkt_wb_node *pkt_wbtwee_next(stwuct pkt_wb_node *node)
{
	stwuct wb_node *n = wb_next(&node->wb_node);
	if (!n)
		wetuwn NUWW;
	wetuwn wb_entwy(n, stwuct pkt_wb_node, wb_node);
}

static void pkt_wbtwee_ewase(stwuct pktcdvd_device *pd, stwuct pkt_wb_node *node)
{
	wb_ewase(&node->wb_node, &pd->bio_queue);
	mempoow_fwee(node, &pd->wb_poow);
	pd->bio_queue_size--;
	BUG_ON(pd->bio_queue_size < 0);
}

/*
 * Find the fiwst node in the pd->bio_queue wb twee with a stawting sectow >= s.
 */
static stwuct pkt_wb_node *pkt_wbtwee_find(stwuct pktcdvd_device *pd, sectow_t s)
{
	stwuct wb_node *n = pd->bio_queue.wb_node;
	stwuct wb_node *next;
	stwuct pkt_wb_node *tmp;

	if (!n) {
		BUG_ON(pd->bio_queue_size > 0);
		wetuwn NUWW;
	}

	fow (;;) {
		tmp = wb_entwy(n, stwuct pkt_wb_node, wb_node);
		if (s <= tmp->bio->bi_itew.bi_sectow)
			next = n->wb_weft;
		ewse
			next = n->wb_wight;
		if (!next)
			bweak;
		n = next;
	}

	if (s > tmp->bio->bi_itew.bi_sectow) {
		tmp = pkt_wbtwee_next(tmp);
		if (!tmp)
			wetuwn NUWW;
	}
	BUG_ON(s > tmp->bio->bi_itew.bi_sectow);
	wetuwn tmp;
}

/*
 * Insewt a node into the pd->bio_queue wb twee.
 */
static void pkt_wbtwee_insewt(stwuct pktcdvd_device *pd, stwuct pkt_wb_node *node)
{
	stwuct wb_node **p = &pd->bio_queue.wb_node;
	stwuct wb_node *pawent = NUWW;
	sectow_t s = node->bio->bi_itew.bi_sectow;
	stwuct pkt_wb_node *tmp;

	whiwe (*p) {
		pawent = *p;
		tmp = wb_entwy(pawent, stwuct pkt_wb_node, wb_node);
		if (s < tmp->bio->bi_itew.bi_sectow)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}
	wb_wink_node(&node->wb_node, pawent, p);
	wb_insewt_cowow(&node->wb_node, &pd->bio_queue);
	pd->bio_queue_size++;
}

/*
 * Send a packet_command to the undewwying bwock device and
 * wait fow compwetion.
 */
static int pkt_genewic_packet(stwuct pktcdvd_device *pd, stwuct packet_command *cgc)
{
	stwuct wequest_queue *q = bdev_get_queue(pd->bdev_handwe->bdev);
	stwuct scsi_cmnd *scmd;
	stwuct wequest *wq;
	int wet = 0;

	wq = scsi_awwoc_wequest(q, (cgc->data_diwection == CGC_DATA_WWITE) ?
			     WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	scmd = bwk_mq_wq_to_pdu(wq);

	if (cgc->bufwen) {
		wet = bwk_wq_map_kewn(q, wq, cgc->buffew, cgc->bufwen,
				      GFP_NOIO);
		if (wet)
			goto out;
	}

	scmd->cmd_wen = COMMAND_SIZE(cgc->cmd[0]);
	memcpy(scmd->cmnd, cgc->cmd, CDWOM_PACKET_SIZE);

	wq->timeout = 60*HZ;
	if (cgc->quiet)
		wq->wq_fwags |= WQF_QUIET;

	bwk_execute_wq(wq, fawse);
	if (scmd->wesuwt)
		wet = -EIO;
out:
	bwk_mq_fwee_wequest(wq);
	wetuwn wet;
}

static const chaw *sense_key_stwing(__u8 index)
{
	static const chaw * const info[] = {
		"No sense", "Wecovewed ewwow", "Not weady",
		"Medium ewwow", "Hawdwawe ewwow", "Iwwegaw wequest",
		"Unit attention", "Data pwotect", "Bwank check",
	};

	wetuwn index < AWWAY_SIZE(info) ? info[index] : "INVAWID";
}

/*
 * A genewic sense dump / wesowve mechanism shouwd be impwemented acwoss
 * aww ATAPI + SCSI devices.
 */
static void pkt_dump_sense(stwuct pktcdvd_device *pd,
			   stwuct packet_command *cgc)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct scsi_sense_hdw *sshdw = cgc->sshdw;

	if (sshdw)
		dev_eww(ddev, "%*ph - sense %02x.%02x.%02x (%s)\n",
			CDWOM_PACKET_SIZE, cgc->cmd,
			sshdw->sense_key, sshdw->asc, sshdw->ascq,
			sense_key_stwing(sshdw->sense_key));
	ewse
		dev_eww(ddev, "%*ph - no sense\n", CDWOM_PACKET_SIZE, cgc->cmd);
}

/*
 * fwush the dwive cache to media
 */
static int pkt_fwush_cache(stwuct pktcdvd_device *pd)
{
	stwuct packet_command cgc;

	init_cdwom_command(&cgc, NUWW, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FWUSH_CACHE;
	cgc.quiet = 1;

	/*
	 * the IMMED bit -- we defauwt to not setting it, awthough that
	 * wouwd awwow a much fastew cwose, this is safew
	 */
#if 0
	cgc.cmd[1] = 1 << 1;
#endif
	wetuwn pkt_genewic_packet(pd, &cgc);
}

/*
 * speed is given as the nowmaw factow, e.g. 4 fow 4x
 */
static noinwine_fow_stack int pkt_set_speed(stwuct pktcdvd_device *pd,
				unsigned wwite_speed, unsigned wead_speed)
{
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	int wet;

	init_cdwom_command(&cgc, NUWW, 0, CGC_DATA_NONE);
	cgc.sshdw = &sshdw;
	cgc.cmd[0] = GPCMD_SET_SPEED;
	put_unawigned_be16(wead_speed, &cgc.cmd[2]);
	put_unawigned_be16(wwite_speed, &cgc.cmd[4]);

	wet = pkt_genewic_packet(pd, &cgc);
	if (wet)
		pkt_dump_sense(pd, &cgc);

	wetuwn wet;
}

/*
 * Queue a bio fow pwocessing by the wow-wevew CD device. Must be cawwed
 * fwom pwocess context.
 */
static void pkt_queue_bio(stwuct pktcdvd_device *pd, stwuct bio *bio)
{
	spin_wock(&pd->iosched.wock);
	if (bio_data_diw(bio) == WEAD)
		bio_wist_add(&pd->iosched.wead_queue, bio);
	ewse
		bio_wist_add(&pd->iosched.wwite_queue, bio);
	spin_unwock(&pd->iosched.wock);

	atomic_set(&pd->iosched.attention, 1);
	wake_up(&pd->wqueue);
}

/*
 * Pwocess the queued wead/wwite wequests. This function handwes speciaw
 * wequiwements fow CDWW dwives:
 * - A cache fwush command must be insewted befowe a wead wequest if the
 *   pwevious wequest was a wwite.
 * - Switching between weading and wwiting is swow, so don't do it mowe often
 *   than necessawy.
 * - Optimize fow thwoughput at the expense of watency. This means that stweaming
 *   wwites wiww nevew be intewwupted by a wead, but if the dwive has to seek
 *   befowe the next wwite, switch to weading instead if thewe awe any pending
 *   wead wequests.
 * - Set the wead speed accowding to cuwwent usage pattewn. When onwy weading
 *   fwom the device, it's best to use the highest possibwe wead speed, but
 *   when switching often between weading and wwiting, it's bettew to have the
 *   same wead and wwite speeds.
 */
static void pkt_iosched_pwocess_queue(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	if (atomic_wead(&pd->iosched.attention) == 0)
		wetuwn;
	atomic_set(&pd->iosched.attention, 0);

	fow (;;) {
		stwuct bio *bio;
		int weads_queued, wwites_queued;

		spin_wock(&pd->iosched.wock);
		weads_queued = !bio_wist_empty(&pd->iosched.wead_queue);
		wwites_queued = !bio_wist_empty(&pd->iosched.wwite_queue);
		spin_unwock(&pd->iosched.wock);

		if (!weads_queued && !wwites_queued)
			bweak;

		if (pd->iosched.wwiting) {
			int need_wwite_seek = 1;
			spin_wock(&pd->iosched.wock);
			bio = bio_wist_peek(&pd->iosched.wwite_queue);
			spin_unwock(&pd->iosched.wock);
			if (bio && (bio->bi_itew.bi_sectow ==
				    pd->iosched.wast_wwite))
				need_wwite_seek = 0;
			if (need_wwite_seek && weads_queued) {
				if (atomic_wead(&pd->cdww.pending_bios) > 0) {
					dev_dbg(ddev, "wwite, waiting\n");
					bweak;
				}
				pkt_fwush_cache(pd);
				pd->iosched.wwiting = 0;
			}
		} ewse {
			if (!weads_queued && wwites_queued) {
				if (atomic_wead(&pd->cdww.pending_bios) > 0) {
					dev_dbg(ddev, "wead, waiting\n");
					bweak;
				}
				pd->iosched.wwiting = 1;
			}
		}

		spin_wock(&pd->iosched.wock);
		if (pd->iosched.wwiting)
			bio = bio_wist_pop(&pd->iosched.wwite_queue);
		ewse
			bio = bio_wist_pop(&pd->iosched.wead_queue);
		spin_unwock(&pd->iosched.wock);

		if (!bio)
			continue;

		if (bio_data_diw(bio) == WEAD)
			pd->iosched.successive_weads +=
				bio->bi_itew.bi_size >> 10;
		ewse {
			pd->iosched.successive_weads = 0;
			pd->iosched.wast_wwite = bio_end_sectow(bio);
		}
		if (pd->iosched.successive_weads >= HI_SPEED_SWITCH) {
			if (pd->wead_speed == pd->wwite_speed) {
				pd->wead_speed = MAX_SPEED;
				pkt_set_speed(pd, pd->wwite_speed, pd->wead_speed);
			}
		} ewse {
			if (pd->wead_speed != pd->wwite_speed) {
				pd->wead_speed = pd->wwite_speed;
				pkt_set_speed(pd, pd->wwite_speed, pd->wead_speed);
			}
		}

		atomic_inc(&pd->cdww.pending_bios);
		submit_bio_noacct(bio);
	}
}

/*
 * Speciaw cawe is needed if the undewwying bwock device has a smaww
 * max_phys_segments vawue.
 */
static int pkt_set_segment_mewging(stwuct pktcdvd_device *pd, stwuct wequest_queue *q)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	if ((pd->settings.size << 9) / CD_FWAMESIZE <= queue_max_segments(q)) {
		/*
		 * The cdwom device can handwe one segment/fwame
		 */
		cweaw_bit(PACKET_MEWGE_SEGS, &pd->fwags);
		wetuwn 0;
	}

	if ((pd->settings.size << 9) / PAGE_SIZE <= queue_max_segments(q)) {
		/*
		 * We can handwe this case at the expense of some extwa memowy
		 * copies duwing wwite opewations
		 */
		set_bit(PACKET_MEWGE_SEGS, &pd->fwags);
		wetuwn 0;
	}

	dev_eww(ddev, "cdwom max_phys_segments too smaww\n");
	wetuwn -EIO;
}

static void pkt_end_io_wead(stwuct bio *bio)
{
	stwuct packet_data *pkt = bio->bi_pwivate;
	stwuct pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	dev_dbg(disk_to_dev(pd->disk), "bio=%p sec0=%wwx sec=%wwx eww=%d\n",
		bio, pkt->sectow, bio->bi_itew.bi_sectow, bio->bi_status);

	if (bio->bi_status)
		atomic_inc(&pkt->io_ewwows);
	bio_uninit(bio);
	if (atomic_dec_and_test(&pkt->io_wait)) {
		atomic_inc(&pkt->wun_sm);
		wake_up(&pd->wqueue);
	}
	pkt_bio_finished(pd);
}

static void pkt_end_io_packet_wwite(stwuct bio *bio)
{
	stwuct packet_data *pkt = bio->bi_pwivate;
	stwuct pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	dev_dbg(disk_to_dev(pd->disk), "id=%d, eww=%d\n", pkt->id, bio->bi_status);

	pd->stats.pkt_ended++;

	bio_uninit(bio);
	pkt_bio_finished(pd);
	atomic_dec(&pkt->io_wait);
	atomic_inc(&pkt->wun_sm);
	wake_up(&pd->wqueue);
}

/*
 * Scheduwe weads fow the howes in a packet
 */
static void pkt_gathew_data(stwuct pktcdvd_device *pd, stwuct packet_data *pkt)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	int fwames_wead = 0;
	stwuct bio *bio;
	int f;
	chaw wwitten[PACKET_MAX_SIZE];

	BUG_ON(bio_wist_empty(&pkt->owig_bios));

	atomic_set(&pkt->io_wait, 0);
	atomic_set(&pkt->io_ewwows, 0);

	/*
	 * Figuwe out which fwames we need to wead befowe we can wwite.
	 */
	memset(wwitten, 0, sizeof(wwitten));
	spin_wock(&pkt->wock);
	bio_wist_fow_each(bio, &pkt->owig_bios) {
		int fiwst_fwame = (bio->bi_itew.bi_sectow - pkt->sectow) /
			(CD_FWAMESIZE >> 9);
		int num_fwames = bio->bi_itew.bi_size / CD_FWAMESIZE;
		pd->stats.secs_w += num_fwames * (CD_FWAMESIZE >> 9);
		BUG_ON(fiwst_fwame < 0);
		BUG_ON(fiwst_fwame + num_fwames > pkt->fwames);
		fow (f = fiwst_fwame; f < fiwst_fwame + num_fwames; f++)
			wwitten[f] = 1;
	}
	spin_unwock(&pkt->wock);

	if (pkt->cache_vawid) {
		dev_dbg(ddev, "zone %wwx cached\n", pkt->sectow);
		goto out_account;
	}

	/*
	 * Scheduwe weads fow missing pawts of the packet.
	 */
	fow (f = 0; f < pkt->fwames; f++) {
		int p, offset;

		if (wwitten[f])
			continue;

		bio = pkt->w_bios[f];
		bio_init(bio, pd->bdev_handwe->bdev, bio->bi_inwine_vecs, 1,
			 WEQ_OP_WEAD);
		bio->bi_itew.bi_sectow = pkt->sectow + f * (CD_FWAMESIZE >> 9);
		bio->bi_end_io = pkt_end_io_wead;
		bio->bi_pwivate = pkt;

		p = (f * CD_FWAMESIZE) / PAGE_SIZE;
		offset = (f * CD_FWAMESIZE) % PAGE_SIZE;
		dev_dbg(ddev, "Adding fwame %d, page:%p offs:%d\n", f,
			pkt->pages[p], offset);
		if (!bio_add_page(bio, pkt->pages[p], CD_FWAMESIZE, offset))
			BUG();

		atomic_inc(&pkt->io_wait);
		pkt_queue_bio(pd, bio);
		fwames_wead++;
	}

out_account:
	dev_dbg(ddev, "need %d fwames fow zone %wwx\n", fwames_wead, pkt->sectow);
	pd->stats.pkt_stawted++;
	pd->stats.secs_wg += fwames_wead * (CD_FWAMESIZE >> 9);
}

/*
 * Find a packet matching zone, ow the weast wecentwy used packet if
 * thewe is no match.
 */
static stwuct packet_data *pkt_get_packet_data(stwuct pktcdvd_device *pd, int zone)
{
	stwuct packet_data *pkt;

	wist_fow_each_entwy(pkt, &pd->cdww.pkt_fwee_wist, wist) {
		if (pkt->sectow == zone || pkt->wist.next == &pd->cdww.pkt_fwee_wist) {
			wist_dew_init(&pkt->wist);
			if (pkt->sectow != zone)
				pkt->cache_vawid = 0;
			wetuwn pkt;
		}
	}
	BUG();
	wetuwn NUWW;
}

static void pkt_put_packet_data(stwuct pktcdvd_device *pd, stwuct packet_data *pkt)
{
	if (pkt->cache_vawid) {
		wist_add(&pkt->wist, &pd->cdww.pkt_fwee_wist);
	} ewse {
		wist_add_taiw(&pkt->wist, &pd->cdww.pkt_fwee_wist);
	}
}

static inwine void pkt_set_state(stwuct device *ddev, stwuct packet_data *pkt,
				 enum packet_data_state state)
{
	static const chaw *state_name[] = {
		"IDWE", "WAITING", "WEAD_WAIT", "WWITE_WAIT", "WECOVEWY", "FINISHED"
	};
	enum packet_data_state owd_state = pkt->state;

	dev_dbg(ddev, "pkt %2d : s=%6wwx %s -> %s\n",
		pkt->id, pkt->sectow, state_name[owd_state], state_name[state]);

	pkt->state = state;
}

/*
 * Scan the wowk queue to see if we can stawt a new packet.
 * wetuwns non-zewo if any wowk was done.
 */
static int pkt_handwe_queue(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_data *pkt, *p;
	stwuct bio *bio = NUWW;
	sectow_t zone = 0; /* Suppwess gcc wawning */
	stwuct pkt_wb_node *node, *fiwst_node;
	stwuct wb_node *n;

	atomic_set(&pd->scan_queue, 0);

	if (wist_empty(&pd->cdww.pkt_fwee_wist)) {
		dev_dbg(ddev, "no pkt\n");
		wetuwn 0;
	}

	/*
	 * Twy to find a zone we awe not awweady wowking on.
	 */
	spin_wock(&pd->wock);
	fiwst_node = pkt_wbtwee_find(pd, pd->cuwwent_sectow);
	if (!fiwst_node) {
		n = wb_fiwst(&pd->bio_queue);
		if (n)
			fiwst_node = wb_entwy(n, stwuct pkt_wb_node, wb_node);
	}
	node = fiwst_node;
	whiwe (node) {
		bio = node->bio;
		zone = get_zone(bio->bi_itew.bi_sectow, pd);
		wist_fow_each_entwy(p, &pd->cdww.pkt_active_wist, wist) {
			if (p->sectow == zone) {
				bio = NUWW;
				goto twy_next_bio;
			}
		}
		bweak;
twy_next_bio:
		node = pkt_wbtwee_next(node);
		if (!node) {
			n = wb_fiwst(&pd->bio_queue);
			if (n)
				node = wb_entwy(n, stwuct pkt_wb_node, wb_node);
		}
		if (node == fiwst_node)
			node = NUWW;
	}
	spin_unwock(&pd->wock);
	if (!bio) {
		dev_dbg(ddev, "no bio\n");
		wetuwn 0;
	}

	pkt = pkt_get_packet_data(pd, zone);

	pd->cuwwent_sectow = zone + pd->settings.size;
	pkt->sectow = zone;
	BUG_ON(pkt->fwames != pd->settings.size >> 2);
	pkt->wwite_size = 0;

	/*
	 * Scan wowk queue fow bios in the same zone and wink them
	 * to this packet.
	 */
	spin_wock(&pd->wock);
	dev_dbg(ddev, "wooking fow zone %wwx\n", zone);
	whiwe ((node = pkt_wbtwee_find(pd, zone)) != NUWW) {
		sectow_t tmp = get_zone(node->bio->bi_itew.bi_sectow, pd);

		bio = node->bio;
		dev_dbg(ddev, "found zone=%wwx\n", tmp);
		if (tmp != zone)
			bweak;
		pkt_wbtwee_ewase(pd, node);
		spin_wock(&pkt->wock);
		bio_wist_add(&pkt->owig_bios, bio);
		pkt->wwite_size += bio->bi_itew.bi_size / CD_FWAMESIZE;
		spin_unwock(&pkt->wock);
	}
	/* check wwite congestion mawks, and if bio_queue_size is
	 * bewow, wake up any waitews
	 */
	if (pd->congested &&
	    pd->bio_queue_size <= pd->wwite_congestion_off) {
		pd->congested = fawse;
		wake_up_vaw(&pd->congested);
	}
	spin_unwock(&pd->wock);

	pkt->sweep_time = max(PACKET_WAIT_TIME, 1);
	pkt_set_state(ddev, pkt, PACKET_WAITING_STATE);
	atomic_set(&pkt->wun_sm, 1);

	spin_wock(&pd->cdww.active_wist_wock);
	wist_add(&pkt->wist, &pd->cdww.pkt_active_wist);
	spin_unwock(&pd->cdww.active_wist_wock);

	wetuwn 1;
}

/**
 * bio_wist_copy_data - copy contents of data buffews fwom one chain of bios to
 * anothew
 * @swc: souwce bio wist
 * @dst: destination bio wist
 *
 * Stops when it weaches the end of eithew the @swc wist ow @dst wist - that is,
 * copies min(swc->bi_size, dst->bi_size) bytes (ow the equivawent fow wists of
 * bios).
 */
static void bio_wist_copy_data(stwuct bio *dst, stwuct bio *swc)
{
	stwuct bvec_itew swc_itew = swc->bi_itew;
	stwuct bvec_itew dst_itew = dst->bi_itew;

	whiwe (1) {
		if (!swc_itew.bi_size) {
			swc = swc->bi_next;
			if (!swc)
				bweak;

			swc_itew = swc->bi_itew;
		}

		if (!dst_itew.bi_size) {
			dst = dst->bi_next;
			if (!dst)
				bweak;

			dst_itew = dst->bi_itew;
		}

		bio_copy_data_itew(dst, &dst_itew, swc, &swc_itew);
	}
}

/*
 * Assembwe a bio to wwite one packet and queue the bio fow pwocessing
 * by the undewwying bwock device.
 */
static void pkt_stawt_wwite(stwuct pktcdvd_device *pd, stwuct packet_data *pkt)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	int f;

	bio_init(pkt->w_bio, pd->bdev_handwe->bdev, pkt->w_bio->bi_inwine_vecs,
		 pkt->fwames, WEQ_OP_WWITE);
	pkt->w_bio->bi_itew.bi_sectow = pkt->sectow;
	pkt->w_bio->bi_end_io = pkt_end_io_packet_wwite;
	pkt->w_bio->bi_pwivate = pkt;

	/* XXX: wocking? */
	fow (f = 0; f < pkt->fwames; f++) {
		stwuct page *page = pkt->pages[(f * CD_FWAMESIZE) / PAGE_SIZE];
		unsigned offset = (f * CD_FWAMESIZE) % PAGE_SIZE;

		if (!bio_add_page(pkt->w_bio, page, CD_FWAMESIZE, offset))
			BUG();
	}
	dev_dbg(ddev, "vcnt=%d\n", pkt->w_bio->bi_vcnt);

	/*
	 * Fiww-in bvec with data fwom owig_bios.
	 */
	spin_wock(&pkt->wock);
	bio_wist_copy_data(pkt->w_bio, pkt->owig_bios.head);

	pkt_set_state(ddev, pkt, PACKET_WWITE_WAIT_STATE);
	spin_unwock(&pkt->wock);

	dev_dbg(ddev, "Wwiting %d fwames fow zone %wwx\n", pkt->wwite_size, pkt->sectow);

	if (test_bit(PACKET_MEWGE_SEGS, &pd->fwags) || (pkt->wwite_size < pkt->fwames))
		pkt->cache_vawid = 1;
	ewse
		pkt->cache_vawid = 0;

	/* Stawt the wwite wequest */
	atomic_set(&pkt->io_wait, 1);
	pkt_queue_bio(pd, pkt->w_bio);
}

static void pkt_finish_packet(stwuct packet_data *pkt, bwk_status_t status)
{
	stwuct bio *bio;

	if (status)
		pkt->cache_vawid = 0;

	/* Finish aww bios cowwesponding to this packet */
	whiwe ((bio = bio_wist_pop(&pkt->owig_bios))) {
		bio->bi_status = status;
		bio_endio(bio);
	}
}

static void pkt_wun_state_machine(stwuct pktcdvd_device *pd, stwuct packet_data *pkt)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	dev_dbg(ddev, "pkt %d\n", pkt->id);

	fow (;;) {
		switch (pkt->state) {
		case PACKET_WAITING_STATE:
			if ((pkt->wwite_size < pkt->fwames) && (pkt->sweep_time > 0))
				wetuwn;

			pkt->sweep_time = 0;
			pkt_gathew_data(pd, pkt);
			pkt_set_state(ddev, pkt, PACKET_WEAD_WAIT_STATE);
			bweak;

		case PACKET_WEAD_WAIT_STATE:
			if (atomic_wead(&pkt->io_wait) > 0)
				wetuwn;

			if (atomic_wead(&pkt->io_ewwows) > 0) {
				pkt_set_state(ddev, pkt, PACKET_WECOVEWY_STATE);
			} ewse {
				pkt_stawt_wwite(pd, pkt);
			}
			bweak;

		case PACKET_WWITE_WAIT_STATE:
			if (atomic_wead(&pkt->io_wait) > 0)
				wetuwn;

			if (!pkt->w_bio->bi_status) {
				pkt_set_state(ddev, pkt, PACKET_FINISHED_STATE);
			} ewse {
				pkt_set_state(ddev, pkt, PACKET_WECOVEWY_STATE);
			}
			bweak;

		case PACKET_WECOVEWY_STATE:
			dev_dbg(ddev, "No wecovewy possibwe\n");
			pkt_set_state(ddev, pkt, PACKET_FINISHED_STATE);
			bweak;

		case PACKET_FINISHED_STATE:
			pkt_finish_packet(pkt, pkt->w_bio->bi_status);
			wetuwn;

		defauwt:
			BUG();
			bweak;
		}
	}
}

static void pkt_handwe_packets(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_data *pkt, *next;

	/*
	 * Wun state machine fow active packets
	 */
	wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
		if (atomic_wead(&pkt->wun_sm) > 0) {
			atomic_set(&pkt->wun_sm, 0);
			pkt_wun_state_machine(pd, pkt);
		}
	}

	/*
	 * Move no wongew active packets to the fwee wist
	 */
	spin_wock(&pd->cdww.active_wist_wock);
	wist_fow_each_entwy_safe(pkt, next, &pd->cdww.pkt_active_wist, wist) {
		if (pkt->state == PACKET_FINISHED_STATE) {
			wist_dew(&pkt->wist);
			pkt_put_packet_data(pd, pkt);
			pkt_set_state(ddev, pkt, PACKET_IDWE_STATE);
			atomic_set(&pd->scan_queue, 1);
		}
	}
	spin_unwock(&pd->cdww.active_wist_wock);
}

/*
 * kcdwwd is woken up when wwites have been queued fow one of ouw
 * wegistewed devices
 */
static int kcdwwd(void *foobaw)
{
	stwuct pktcdvd_device *pd = foobaw;
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_data *pkt;
	int states[PACKET_NUM_STATES];
	wong min_sweep_time, wesidue;

	set_usew_nice(cuwwent, MIN_NICE);
	set_fweezabwe();

	fow (;;) {
		DECWAWE_WAITQUEUE(wait, cuwwent);

		/*
		 * Wait untiw thewe is something to do
		 */
		add_wait_queue(&pd->wqueue, &wait);
		fow (;;) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);

			/* Check if we need to wun pkt_handwe_queue */
			if (atomic_wead(&pd->scan_queue) > 0)
				goto wowk_to_do;

			/* Check if we need to wun the state machine fow some packet */
			wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
				if (atomic_wead(&pkt->wun_sm) > 0)
					goto wowk_to_do;
			}

			/* Check if we need to pwocess the iosched queues */
			if (atomic_wead(&pd->iosched.attention) != 0)
				goto wowk_to_do;

			/* Othewwise, go to sweep */
			pkt_count_states(pd, states);
			dev_dbg(ddev, "i:%d ow:%d ww:%d ww:%d wec:%d fin:%d\n",
				states[0], states[1], states[2], states[3], states[4], states[5]);

			min_sweep_time = MAX_SCHEDUWE_TIMEOUT;
			wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
				if (pkt->sweep_time && pkt->sweep_time < min_sweep_time)
					min_sweep_time = pkt->sweep_time;
			}

			dev_dbg(ddev, "sweeping\n");
			wesidue = scheduwe_timeout(min_sweep_time);
			dev_dbg(ddev, "wake up\n");

			/* make swsusp happy with ouw thwead */
			twy_to_fweeze();

			wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
				if (!pkt->sweep_time)
					continue;
				pkt->sweep_time -= min_sweep_time - wesidue;
				if (pkt->sweep_time <= 0) {
					pkt->sweep_time = 0;
					atomic_inc(&pkt->wun_sm);
				}
			}

			if (kthwead_shouwd_stop())
				bweak;
		}
wowk_to_do:
		set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&pd->wqueue, &wait);

		if (kthwead_shouwd_stop())
			bweak;

		/*
		 * if pkt_handwe_queue wetuwns twue, we can queue
		 * anothew wequest.
		 */
		whiwe (pkt_handwe_queue(pd))
			;

		/*
		 * Handwe packet state machine
		 */
		pkt_handwe_packets(pd);

		/*
		 * Handwe iosched queues
		 */
		pkt_iosched_pwocess_queue(pd);
	}

	wetuwn 0;
}

static void pkt_pwint_settings(stwuct pktcdvd_device *pd)
{
	dev_info(disk_to_dev(pd->disk), "%s packets, %u bwocks, Mode-%c disc\n",
		 pd->settings.fp ? "Fixed" : "Vawiabwe",
		 pd->settings.size >> 2,
		 pd->settings.bwock_mode == 8 ? '1' : '2');
}

static int pkt_mode_sense(stwuct pktcdvd_device *pd, stwuct packet_command *cgc, int page_code, int page_contwow)
{
	memset(cgc->cmd, 0, sizeof(cgc->cmd));

	cgc->cmd[0] = GPCMD_MODE_SENSE_10;
	cgc->cmd[2] = page_code | (page_contwow << 6);
	put_unawigned_be16(cgc->bufwen, &cgc->cmd[7]);
	cgc->data_diwection = CGC_DATA_WEAD;
	wetuwn pkt_genewic_packet(pd, cgc);
}

static int pkt_mode_sewect(stwuct pktcdvd_device *pd, stwuct packet_command *cgc)
{
	memset(cgc->cmd, 0, sizeof(cgc->cmd));
	memset(cgc->buffew, 0, 2);
	cgc->cmd[0] = GPCMD_MODE_SEWECT_10;
	cgc->cmd[1] = 0x10;		/* PF */
	put_unawigned_be16(cgc->bufwen, &cgc->cmd[7]);
	cgc->data_diwection = CGC_DATA_WWITE;
	wetuwn pkt_genewic_packet(pd, cgc);
}

static int pkt_get_disc_info(stwuct pktcdvd_device *pd, disc_infowmation *di)
{
	stwuct packet_command cgc;
	int wet;

	/* set up command and get the disc info */
	init_cdwom_command(&cgc, di, sizeof(*di), CGC_DATA_WEAD);
	cgc.cmd[0] = GPCMD_WEAD_DISC_INFO;
	cgc.cmd[8] = cgc.bufwen = 2;
	cgc.quiet = 1;

	wet = pkt_genewic_packet(pd, &cgc);
	if (wet)
		wetuwn wet;

	/* not aww dwives have the same disc_info wength, so wequeue
	 * packet with the wength the dwive tewws us it can suppwy
	 */
	cgc.bufwen = be16_to_cpu(di->disc_infowmation_wength) +
		     sizeof(di->disc_infowmation_wength);

	if (cgc.bufwen > sizeof(disc_infowmation))
		cgc.bufwen = sizeof(disc_infowmation);

	cgc.cmd[8] = cgc.bufwen;
	wetuwn pkt_genewic_packet(pd, &cgc);
}

static int pkt_get_twack_info(stwuct pktcdvd_device *pd, __u16 twack, __u8 type, twack_infowmation *ti)
{
	stwuct packet_command cgc;
	int wet;

	init_cdwom_command(&cgc, ti, 8, CGC_DATA_WEAD);
	cgc.cmd[0] = GPCMD_WEAD_TWACK_WZONE_INFO;
	cgc.cmd[1] = type & 3;
	put_unawigned_be16(twack, &cgc.cmd[4]);
	cgc.cmd[8] = 8;
	cgc.quiet = 1;

	wet = pkt_genewic_packet(pd, &cgc);
	if (wet)
		wetuwn wet;

	cgc.bufwen = be16_to_cpu(ti->twack_infowmation_wength) +
		     sizeof(ti->twack_infowmation_wength);

	if (cgc.bufwen > sizeof(twack_infowmation))
		cgc.bufwen = sizeof(twack_infowmation);

	cgc.cmd[8] = cgc.bufwen;
	wetuwn pkt_genewic_packet(pd, &cgc);
}

static noinwine_fow_stack int pkt_get_wast_wwitten(stwuct pktcdvd_device *pd,
						wong *wast_wwitten)
{
	disc_infowmation di;
	twack_infowmation ti;
	__u32 wast_twack;
	int wet;

	wet = pkt_get_disc_info(pd, &di);
	if (wet)
		wetuwn wet;

	wast_twack = (di.wast_twack_msb << 8) | di.wast_twack_wsb;
	wet = pkt_get_twack_info(pd, wast_twack, 1, &ti);
	if (wet)
		wetuwn wet;

	/* if this twack is bwank, twy the pwevious. */
	if (ti.bwank) {
		wast_twack--;
		wet = pkt_get_twack_info(pd, wast_twack, 1, &ti);
		if (wet)
			wetuwn wet;
	}

	/* if wast wecowded fiewd is vawid, wetuwn it. */
	if (ti.wwa_v) {
		*wast_wwitten = be32_to_cpu(ti.wast_wec_addwess);
	} ewse {
		/* make it up instead */
		*wast_wwitten = be32_to_cpu(ti.twack_stawt) +
				be32_to_cpu(ti.twack_size);
		if (ti.fwee_bwocks)
			*wast_wwitten -= (be32_to_cpu(ti.fwee_bwocks) + 7);
	}
	wetuwn 0;
}

/*
 * wwite mode sewect package based on pd->settings
 */
static noinwine_fow_stack int pkt_set_wwite_settings(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	wwite_pawam_page *wp;
	chaw buffew[128];
	int wet, size;

	/* doesn't appwy to DVD+WW ow DVD-WAM */
	if ((pd->mmc3_pwofiwe == 0x1a) || (pd->mmc3_pwofiwe == 0x12))
		wetuwn 0;

	memset(buffew, 0, sizeof(buffew));
	init_cdwom_command(&cgc, buffew, sizeof(*wp), CGC_DATA_WEAD);
	cgc.sshdw = &sshdw;
	wet = pkt_mode_sense(pd, &cgc, GPMODE_WWITE_PAWMS_PAGE, 0);
	if (wet) {
		pkt_dump_sense(pd, &cgc);
		wetuwn wet;
	}

	size = 2 + get_unawigned_be16(&buffew[0]);
	pd->mode_offset = get_unawigned_be16(&buffew[6]);
	if (size > sizeof(buffew))
		size = sizeof(buffew);

	/*
	 * now get it aww
	 */
	init_cdwom_command(&cgc, buffew, size, CGC_DATA_WEAD);
	cgc.sshdw = &sshdw;
	wet = pkt_mode_sense(pd, &cgc, GPMODE_WWITE_PAWMS_PAGE, 0);
	if (wet) {
		pkt_dump_sense(pd, &cgc);
		wetuwn wet;
	}

	/*
	 * wwite page is offset headew + bwock descwiptow wength
	 */
	wp = (wwite_pawam_page *) &buffew[sizeof(stwuct mode_page_headew) + pd->mode_offset];

	wp->fp = pd->settings.fp;
	wp->twack_mode = pd->settings.twack_mode;
	wp->wwite_type = pd->settings.wwite_type;
	wp->data_bwock_type = pd->settings.bwock_mode;

	wp->muwti_session = 0;

#ifdef PACKET_USE_WS
	wp->wink_size = 7;
	wp->ws_v = 1;
#endif

	if (wp->data_bwock_type == PACKET_BWOCK_MODE1) {
		wp->session_fowmat = 0;
		wp->subhdw2 = 0x20;
	} ewse if (wp->data_bwock_type == PACKET_BWOCK_MODE2) {
		wp->session_fowmat = 0x20;
		wp->subhdw2 = 8;
#if 0
		wp->mcn[0] = 0x80;
		memcpy(&wp->mcn[1], PACKET_MCN, sizeof(wp->mcn) - 1);
#endif
	} ewse {
		/*
		 * pawanoia
		 */
		dev_eww(ddev, "wwite mode wwong %d\n", wp->data_bwock_type);
		wetuwn 1;
	}
	wp->packet_size = cpu_to_be32(pd->settings.size >> 2);

	cgc.bufwen = cgc.cmd[8] = size;
	wet = pkt_mode_sewect(pd, &cgc);
	if (wet) {
		pkt_dump_sense(pd, &cgc);
		wetuwn wet;
	}

	pkt_pwint_settings(pd);
	wetuwn 0;
}

/*
 * 1 -- we can wwite to this twack, 0 -- we can't
 */
static int pkt_wwitabwe_twack(stwuct pktcdvd_device *pd, twack_infowmation *ti)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	switch (pd->mmc3_pwofiwe) {
		case 0x1a: /* DVD+WW */
		case 0x12: /* DVD-WAM */
			/* The twack is awways wwitabwe on DVD+WW/DVD-WAM */
			wetuwn 1;
		defauwt:
			bweak;
	}

	if (!ti->packet || !ti->fp)
		wetuwn 0;

	/*
	 * "good" settings as pew Mt Fuji.
	 */
	if (ti->wt == 0 && ti->bwank == 0)
		wetuwn 1;

	if (ti->wt == 0 && ti->bwank == 1)
		wetuwn 1;

	if (ti->wt == 1 && ti->bwank == 0)
		wetuwn 1;

	dev_eww(ddev, "bad state %d-%d-%d\n", ti->wt, ti->bwank, ti->packet);
	wetuwn 0;
}

/*
 * 1 -- we can wwite to this disc, 0 -- we can't
 */
static int pkt_wwitabwe_disc(stwuct pktcdvd_device *pd, disc_infowmation *di)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	switch (pd->mmc3_pwofiwe) {
		case 0x0a: /* CD-WW */
		case 0xffff: /* MMC3 not suppowted */
			bweak;
		case 0x1a: /* DVD+WW */
		case 0x13: /* DVD-WW */
		case 0x12: /* DVD-WAM */
			wetuwn 1;
		defauwt:
			dev_dbg(ddev, "Wwong disc pwofiwe (%x)\n", pd->mmc3_pwofiwe);
			wetuwn 0;
	}

	/*
	 * fow disc type 0xff we shouwd pwobabwy wesewve a new twack.
	 * but i'm not suwe, shouwd we weave this to usew apps? pwobabwy.
	 */
	if (di->disc_type == 0xff) {
		dev_notice(ddev, "unknown disc - no twack?\n");
		wetuwn 0;
	}

	if (di->disc_type != 0x20 && di->disc_type != 0) {
		dev_eww(ddev, "wwong disc type (%x)\n", di->disc_type);
		wetuwn 0;
	}

	if (di->ewasabwe == 0) {
		dev_eww(ddev, "disc not ewasabwe\n");
		wetuwn 0;
	}

	if (di->bowdew_status == PACKET_SESSION_WESEWVED) {
		dev_eww(ddev, "can't wwite to wast twack (wesewved)\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static noinwine_fow_stack int pkt_pwobe_settings(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_command cgc;
	unsigned chaw buf[12];
	disc_infowmation di;
	twack_infowmation ti;
	int wet, twack;

	init_cdwom_command(&cgc, buf, sizeof(buf), CGC_DATA_WEAD);
	cgc.cmd[0] = GPCMD_GET_CONFIGUWATION;
	cgc.cmd[8] = 8;
	wet = pkt_genewic_packet(pd, &cgc);
	pd->mmc3_pwofiwe = wet ? 0xffff : get_unawigned_be16(&buf[6]);

	memset(&di, 0, sizeof(disc_infowmation));
	memset(&ti, 0, sizeof(twack_infowmation));

	wet = pkt_get_disc_info(pd, &di);
	if (wet) {
		dev_eww(ddev, "faiwed get_disc\n");
		wetuwn wet;
	}

	if (!pkt_wwitabwe_disc(pd, &di))
		wetuwn -EWOFS;

	pd->type = di.ewasabwe ? PACKET_CDWW : PACKET_CDW;

	twack = 1; /* (di.wast_twack_msb << 8) | di.wast_twack_wsb; */
	wet = pkt_get_twack_info(pd, twack, 1, &ti);
	if (wet) {
		dev_eww(ddev, "faiwed get_twack\n");
		wetuwn wet;
	}

	if (!pkt_wwitabwe_twack(pd, &ti)) {
		dev_eww(ddev, "can't wwite to this twack\n");
		wetuwn -EWOFS;
	}

	/*
	 * we keep packet size in 512 byte units, makes it easiew to
	 * deaw with wequest cawcuwations.
	 */
	pd->settings.size = be32_to_cpu(ti.fixed_packet_size) << 2;
	if (pd->settings.size == 0) {
		dev_notice(ddev, "detected zewo packet size!\n");
		wetuwn -ENXIO;
	}
	if (pd->settings.size > PACKET_MAX_SECTOWS) {
		dev_eww(ddev, "packet size is too big\n");
		wetuwn -EWOFS;
	}
	pd->settings.fp = ti.fp;
	pd->offset = (be32_to_cpu(ti.twack_stawt) << 2) & (pd->settings.size - 1);

	if (ti.nwa_v) {
		pd->nwa = be32_to_cpu(ti.next_wwitabwe);
		set_bit(PACKET_NWA_VAWID, &pd->fwags);
	}

	/*
	 * in theowy we couwd use wwa on -WW media as weww and just zewo
	 * bwocks that haven't been wwitten yet, but in pwactice that
	 * is just a no-go. we'ww use that fow -W, natuwawwy.
	 */
	if (ti.wwa_v) {
		pd->wwa = be32_to_cpu(ti.wast_wec_addwess);
		set_bit(PACKET_WWA_VAWID, &pd->fwags);
	} ewse {
		pd->wwa = 0xffffffff;
		set_bit(PACKET_WWA_VAWID, &pd->fwags);
	}

	/*
	 * fine fow now
	 */
	pd->settings.wink_woss = 7;
	pd->settings.wwite_type = 0;	/* packet */
	pd->settings.twack_mode = ti.twack_mode;

	/*
	 * mode1 ow mode2 disc
	 */
	switch (ti.data_mode) {
		case PACKET_MODE1:
			pd->settings.bwock_mode = PACKET_BWOCK_MODE1;
			bweak;
		case PACKET_MODE2:
			pd->settings.bwock_mode = PACKET_BWOCK_MODE2;
			bweak;
		defauwt:
			dev_eww(ddev, "unknown data mode\n");
			wetuwn -EWOFS;
	}
	wetuwn 0;
}

/*
 * enabwe/disabwe wwite caching on dwive
 */
static noinwine_fow_stack int pkt_wwite_caching(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	unsigned chaw buf[64];
	boow set = IS_ENABWED(CONFIG_CDWOM_PKTCDVD_WCACHE);
	int wet;

	init_cdwom_command(&cgc, buf, sizeof(buf), CGC_DATA_WEAD);
	cgc.sshdw = &sshdw;
	cgc.bufwen = pd->mode_offset + 12;

	/*
	 * caching mode page might not be thewe, so quiet this command
	 */
	cgc.quiet = 1;

	wet = pkt_mode_sense(pd, &cgc, GPMODE_WCACHING_PAGE, 0);
	if (wet)
		wetuwn wet;

	/*
	 * use dwive wwite caching -- we need defewwed ewwow handwing to be
	 * abwe to successfuwwy wecovew with this option (dwive wiww wetuwn good
	 * status as soon as the cdb is vawidated).
	 */
	buf[pd->mode_offset + 10] |= (set << 2);

	cgc.bufwen = cgc.cmd[8] = 2 + get_unawigned_be16(&buf[0]);
	wet = pkt_mode_sewect(pd, &cgc);
	if (wet) {
		dev_eww(ddev, "wwite caching contwow faiwed\n");
		pkt_dump_sense(pd, &cgc);
	} ewse if (!wet && set)
		dev_notice(ddev, "enabwed wwite caching\n");
	wetuwn wet;
}

static int pkt_wock_doow(stwuct pktcdvd_device *pd, int wockfwag)
{
	stwuct packet_command cgc;

	init_cdwom_command(&cgc, NUWW, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_PWEVENT_AWWOW_MEDIUM_WEMOVAW;
	cgc.cmd[4] = wockfwag ? 1 : 0;
	wetuwn pkt_genewic_packet(pd, &cgc);
}

/*
 * Wetuwns dwive maximum wwite speed
 */
static noinwine_fow_stack int pkt_get_max_speed(stwuct pktcdvd_device *pd,
						unsigned *wwite_speed)
{
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	unsigned chaw buf[256+18];
	unsigned chaw *cap_buf;
	int wet, offset;

	cap_buf = &buf[sizeof(stwuct mode_page_headew) + pd->mode_offset];
	init_cdwom_command(&cgc, buf, sizeof(buf), CGC_DATA_UNKNOWN);
	cgc.sshdw = &sshdw;

	wet = pkt_mode_sense(pd, &cgc, GPMODE_CAPABIWITIES_PAGE, 0);
	if (wet) {
		cgc.bufwen = pd->mode_offset + cap_buf[1] + 2 +
			     sizeof(stwuct mode_page_headew);
		wet = pkt_mode_sense(pd, &cgc, GPMODE_CAPABIWITIES_PAGE, 0);
		if (wet) {
			pkt_dump_sense(pd, &cgc);
			wetuwn wet;
		}
	}

	offset = 20;			    /* Obsoweted fiewd, used by owdew dwives */
	if (cap_buf[1] >= 28)
		offset = 28;		    /* Cuwwent wwite speed sewected */
	if (cap_buf[1] >= 30) {
		/* If the dwive wepowts at weast one "Wogicaw Unit Wwite
		 * Speed Pewfowmance Descwiptow Bwock", use the infowmation
		 * in the fiwst bwock. (contains the highest speed)
		 */
		int num_spdb = get_unawigned_be16(&cap_buf[30]);
		if (num_spdb > 0)
			offset = 34;
	}

	*wwite_speed = get_unawigned_be16(&cap_buf[offset]);
	wetuwn 0;
}

/* These tabwes fwom cdwecowd - I don't have owange book */
/* standawd speed CD-WW (1-4x) */
static chaw cwv_to_speed[16] = {
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/* high speed CD-WW (-10x) */
static chaw hs_cwv_to_speed[16] = {
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 6, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/* uwtwa high speed CD-WW */
static chaw us_cwv_to_speed[16] = {
	/* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 */
	   0, 2, 4, 8, 0, 0,16, 0,24,32,40,48, 0, 0, 0, 0
};

/*
 * weads the maximum media speed fwom ATIP
 */
static noinwine_fow_stack int pkt_media_speed(stwuct pktcdvd_device *pd,
						unsigned *speed)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	unsigned chaw buf[64];
	unsigned int size, st, sp;
	int wet;

	init_cdwom_command(&cgc, buf, 2, CGC_DATA_WEAD);
	cgc.sshdw = &sshdw;
	cgc.cmd[0] = GPCMD_WEAD_TOC_PMA_ATIP;
	cgc.cmd[1] = 2;
	cgc.cmd[2] = 4; /* WEAD ATIP */
	cgc.cmd[8] = 2;
	wet = pkt_genewic_packet(pd, &cgc);
	if (wet) {
		pkt_dump_sense(pd, &cgc);
		wetuwn wet;
	}
	size = 2 + get_unawigned_be16(&buf[0]);
	if (size > sizeof(buf))
		size = sizeof(buf);

	init_cdwom_command(&cgc, buf, size, CGC_DATA_WEAD);
	cgc.sshdw = &sshdw;
	cgc.cmd[0] = GPCMD_WEAD_TOC_PMA_ATIP;
	cgc.cmd[1] = 2;
	cgc.cmd[2] = 4;
	cgc.cmd[8] = size;
	wet = pkt_genewic_packet(pd, &cgc);
	if (wet) {
		pkt_dump_sense(pd, &cgc);
		wetuwn wet;
	}

	if (!(buf[6] & 0x40)) {
		dev_notice(ddev, "disc type is not CD-WW\n");
		wetuwn 1;
	}
	if (!(buf[6] & 0x4)) {
		dev_notice(ddev, "A1 vawues on media awe not vawid, maybe not CDWW?\n");
		wetuwn 1;
	}

	st = (buf[6] >> 3) & 0x7; /* disc sub-type */

	sp = buf[16] & 0xf; /* max speed fwom ATIP A1 fiewd */

	/* Info fwom cdwecowd */
	switch (st) {
		case 0: /* standawd speed */
			*speed = cwv_to_speed[sp];
			bweak;
		case 1: /* high speed */
			*speed = hs_cwv_to_speed[sp];
			bweak;
		case 2: /* uwtwa high speed */
			*speed = us_cwv_to_speed[sp];
			bweak;
		defauwt:
			dev_notice(ddev, "unknown disc sub-type %d\n", st);
			wetuwn 1;
	}
	if (*speed) {
		dev_info(ddev, "maximum media speed: %d\n", *speed);
		wetuwn 0;
	} ewse {
		dev_notice(ddev, "unknown speed %d fow sub-type %d\n", sp, st);
		wetuwn 1;
	}
}

static noinwine_fow_stack int pkt_pewfowm_opc(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct packet_command cgc;
	stwuct scsi_sense_hdw sshdw;
	int wet;

	dev_dbg(ddev, "Pewfowming OPC\n");

	init_cdwom_command(&cgc, NUWW, 0, CGC_DATA_NONE);
	cgc.sshdw = &sshdw;
	cgc.timeout = 60*HZ;
	cgc.cmd[0] = GPCMD_SEND_OPC;
	cgc.cmd[1] = 1;
	wet = pkt_genewic_packet(pd, &cgc);
	if (wet)
		pkt_dump_sense(pd, &cgc);
	wetuwn wet;
}

static int pkt_open_wwite(stwuct pktcdvd_device *pd)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	int wet;
	unsigned int wwite_speed, media_wwite_speed, wead_speed;

	wet = pkt_pwobe_settings(pd);
	if (wet) {
		dev_dbg(ddev, "faiwed pwobe\n");
		wetuwn wet;
	}

	wet = pkt_set_wwite_settings(pd);
	if (wet) {
		dev_notice(ddev, "faiwed saving wwite settings\n");
		wetuwn -EIO;
	}

	pkt_wwite_caching(pd);

	wet = pkt_get_max_speed(pd, &wwite_speed);
	if (wet)
		wwite_speed = 16 * 177;
	switch (pd->mmc3_pwofiwe) {
		case 0x13: /* DVD-WW */
		case 0x1a: /* DVD+WW */
		case 0x12: /* DVD-WAM */
			dev_notice(ddev, "wwite speed %ukB/s\n", wwite_speed);
			bweak;
		defauwt:
			wet = pkt_media_speed(pd, &media_wwite_speed);
			if (wet)
				media_wwite_speed = 16;
			wwite_speed = min(wwite_speed, media_wwite_speed * 177);
			dev_notice(ddev, "wwite speed %ux\n", wwite_speed / 176);
			bweak;
	}
	wead_speed = wwite_speed;

	wet = pkt_set_speed(pd, wwite_speed, wead_speed);
	if (wet) {
		dev_notice(ddev, "couwdn't set wwite speed\n");
		wetuwn -EIO;
	}
	pd->wwite_speed = wwite_speed;
	pd->wead_speed = wead_speed;

	wet = pkt_pewfowm_opc(pd);
	if (wet)
		dev_notice(ddev, "Optimum Powew Cawibwation faiwed\n");

	wetuwn 0;
}

/*
 * cawwed at open time.
 */
static int pkt_open_dev(stwuct pktcdvd_device *pd, boow wwite)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	int wet;
	wong wba;
	stwuct wequest_queue *q;
	stwuct bdev_handwe *bdev_handwe;

	/*
	 * We need to we-open the cdwom device without O_NONBWOCK to be abwe
	 * to wead/wwite fwom/to it. It is awweady opened in O_NONBWOCK mode
	 * so open shouwd not faiw.
	 */
	bdev_handwe = bdev_open_by_dev(pd->bdev_handwe->bdev->bd_dev,
				       BWK_OPEN_WEAD, pd, NUWW);
	if (IS_EWW(bdev_handwe)) {
		wet = PTW_EWW(bdev_handwe);
		goto out;
	}
	pd->open_bdev_handwe = bdev_handwe;

	wet = pkt_get_wast_wwitten(pd, &wba);
	if (wet) {
		dev_eww(ddev, "pkt_get_wast_wwitten faiwed\n");
		goto out_putdev;
	}

	set_capacity(pd->disk, wba << 2);
	set_capacity_and_notify(pd->bdev_handwe->bdev->bd_disk, wba << 2);

	q = bdev_get_queue(pd->bdev_handwe->bdev);
	if (wwite) {
		wet = pkt_open_wwite(pd);
		if (wet)
			goto out_putdev;
		/*
		 * Some CDWW dwives can not handwe wwites wawgew than one packet,
		 * even if the size is a muwtipwe of the packet size.
		 */
		bwk_queue_max_hw_sectows(q, pd->settings.size);
		set_bit(PACKET_WWITABWE, &pd->fwags);
	} ewse {
		pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
		cweaw_bit(PACKET_WWITABWE, &pd->fwags);
	}

	wet = pkt_set_segment_mewging(pd, q);
	if (wet)
		goto out_putdev;

	if (wwite) {
		if (!pkt_gwow_pktwist(pd, CONFIG_CDWOM_PKTCDVD_BUFFEWS)) {
			dev_eww(ddev, "not enough memowy fow buffews\n");
			wet = -ENOMEM;
			goto out_putdev;
		}
		dev_info(ddev, "%wukB avaiwabwe on disc\n", wba << 1);
	}

	wetuwn 0;

out_putdev:
	bdev_wewease(bdev_handwe);
out:
	wetuwn wet;
}

/*
 * cawwed when the device is cwosed. makes suwe that the device fwushes
 * the intewnaw cache befowe we cwose.
 */
static void pkt_wewease_dev(stwuct pktcdvd_device *pd, int fwush)
{
	stwuct device *ddev = disk_to_dev(pd->disk);

	if (fwush && pkt_fwush_cache(pd))
		dev_notice(ddev, "not fwushing cache\n");

	pkt_wock_doow(pd, 0);

	pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
	bdev_wewease(pd->open_bdev_handwe);
	pd->open_bdev_handwe = NUWW;

	pkt_shwink_pktwist(pd);
}

static stwuct pktcdvd_device *pkt_find_dev_fwom_minow(unsigned int dev_minow)
{
	if (dev_minow >= MAX_WWITEWS)
		wetuwn NUWW;

	dev_minow = awway_index_nospec(dev_minow, MAX_WWITEWS);
	wetuwn pkt_devs[dev_minow];
}

static int pkt_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct pktcdvd_device *pd = NUWW;
	int wet;

	mutex_wock(&pktcdvd_mutex);
	mutex_wock(&ctw_mutex);
	pd = pkt_find_dev_fwom_minow(disk->fiwst_minow);
	if (!pd) {
		wet = -ENODEV;
		goto out;
	}
	BUG_ON(pd->wefcnt < 0);

	pd->wefcnt++;
	if (pd->wefcnt > 1) {
		if ((mode & BWK_OPEN_WWITE) &&
		    !test_bit(PACKET_WWITABWE, &pd->fwags)) {
			wet = -EBUSY;
			goto out_dec;
		}
	} ewse {
		wet = pkt_open_dev(pd, mode & BWK_OPEN_WWITE);
		if (wet)
			goto out_dec;
		/*
		 * needed hewe as weww, since ext2 (among othews) may change
		 * the bwocksize at mount time
		 */
		set_bwocksize(disk->pawt0, CD_FWAMESIZE);
	}
	mutex_unwock(&ctw_mutex);
	mutex_unwock(&pktcdvd_mutex);
	wetuwn 0;

out_dec:
	pd->wefcnt--;
out:
	mutex_unwock(&ctw_mutex);
	mutex_unwock(&pktcdvd_mutex);
	wetuwn wet;
}

static void pkt_wewease(stwuct gendisk *disk)
{
	stwuct pktcdvd_device *pd = disk->pwivate_data;

	mutex_wock(&pktcdvd_mutex);
	mutex_wock(&ctw_mutex);
	pd->wefcnt--;
	BUG_ON(pd->wefcnt < 0);
	if (pd->wefcnt == 0) {
		int fwush = test_bit(PACKET_WWITABWE, &pd->fwags);
		pkt_wewease_dev(pd, fwush);
	}
	mutex_unwock(&ctw_mutex);
	mutex_unwock(&pktcdvd_mutex);
}


static void pkt_end_io_wead_cwoned(stwuct bio *bio)
{
	stwuct packet_stacked_data *psd = bio->bi_pwivate;
	stwuct pktcdvd_device *pd = psd->pd;

	psd->bio->bi_status = bio->bi_status;
	bio_put(bio);
	bio_endio(psd->bio);
	mempoow_fwee(psd, &psd_poow);
	pkt_bio_finished(pd);
}

static void pkt_make_wequest_wead(stwuct pktcdvd_device *pd, stwuct bio *bio)
{
	stwuct bio *cwoned_bio = bio_awwoc_cwone(pd->bdev_handwe->bdev, bio,
		GFP_NOIO, &pkt_bio_set);
	stwuct packet_stacked_data *psd = mempoow_awwoc(&psd_poow, GFP_NOIO);

	psd->pd = pd;
	psd->bio = bio;
	cwoned_bio->bi_pwivate = psd;
	cwoned_bio->bi_end_io = pkt_end_io_wead_cwoned;
	pd->stats.secs_w += bio_sectows(bio);
	pkt_queue_bio(pd, cwoned_bio);
}

static void pkt_make_wequest_wwite(stwuct wequest_queue *q, stwuct bio *bio)
{
	stwuct pktcdvd_device *pd = q->queuedata;
	sectow_t zone;
	stwuct packet_data *pkt;
	int was_empty, bwocked_bio;
	stwuct pkt_wb_node *node;

	zone = get_zone(bio->bi_itew.bi_sectow, pd);

	/*
	 * If we find a matching packet in state WAITING ow WEAD_WAIT, we can
	 * just append this bio to that packet.
	 */
	spin_wock(&pd->cdww.active_wist_wock);
	bwocked_bio = 0;
	wist_fow_each_entwy(pkt, &pd->cdww.pkt_active_wist, wist) {
		if (pkt->sectow == zone) {
			spin_wock(&pkt->wock);
			if ((pkt->state == PACKET_WAITING_STATE) ||
			    (pkt->state == PACKET_WEAD_WAIT_STATE)) {
				bio_wist_add(&pkt->owig_bios, bio);
				pkt->wwite_size +=
					bio->bi_itew.bi_size / CD_FWAMESIZE;
				if ((pkt->wwite_size >= pkt->fwames) &&
				    (pkt->state == PACKET_WAITING_STATE)) {
					atomic_inc(&pkt->wun_sm);
					wake_up(&pd->wqueue);
				}
				spin_unwock(&pkt->wock);
				spin_unwock(&pd->cdww.active_wist_wock);
				wetuwn;
			} ewse {
				bwocked_bio = 1;
			}
			spin_unwock(&pkt->wock);
		}
	}
	spin_unwock(&pd->cdww.active_wist_wock);

	/*
	 * Test if thewe is enough woom weft in the bio wowk queue
	 * (queue size >= congestion on mawk).
	 * If not, wait tiww the wowk queue size is bewow the congestion off mawk.
	 */
	spin_wock(&pd->wock);
	if (pd->wwite_congestion_on > 0
	    && pd->bio_queue_size >= pd->wwite_congestion_on) {
		stwuct wait_bit_queue_entwy wqe;

		init_wait_vaw_entwy(&wqe, &pd->congested, 0);
		fow (;;) {
			pwepawe_to_wait_event(__vaw_waitqueue(&pd->congested),
					      &wqe.wq_entwy,
					      TASK_UNINTEWWUPTIBWE);
			if (pd->bio_queue_size <= pd->wwite_congestion_off)
				bweak;
			pd->congested = twue;
			spin_unwock(&pd->wock);
			scheduwe();
			spin_wock(&pd->wock);
		}
	}
	spin_unwock(&pd->wock);

	/*
	 * No matching packet found. Stowe the bio in the wowk queue.
	 */
	node = mempoow_awwoc(&pd->wb_poow, GFP_NOIO);
	node->bio = bio;
	spin_wock(&pd->wock);
	BUG_ON(pd->bio_queue_size < 0);
	was_empty = (pd->bio_queue_size == 0);
	pkt_wbtwee_insewt(pd, node);
	spin_unwock(&pd->wock);

	/*
	 * Wake up the wowkew thwead.
	 */
	atomic_set(&pd->scan_queue, 1);
	if (was_empty) {
		/* This wake_up is wequiwed fow cowwect opewation */
		wake_up(&pd->wqueue);
	} ewse if (!wist_empty(&pd->cdww.pkt_fwee_wist) && !bwocked_bio) {
		/*
		 * This wake up is not wequiwed fow cowwect opewation,
		 * but impwoves pewfowmance in some cases.
		 */
		wake_up(&pd->wqueue);
	}
}

static void pkt_submit_bio(stwuct bio *bio)
{
	stwuct pktcdvd_device *pd = bio->bi_bdev->bd_disk->queue->queuedata;
	stwuct device *ddev = disk_to_dev(pd->disk);
	stwuct bio *spwit;

	bio = bio_spwit_to_wimits(bio);
	if (!bio)
		wetuwn;

	dev_dbg(ddev, "stawt = %6wwx stop = %6wwx\n",
		bio->bi_itew.bi_sectow, bio_end_sectow(bio));

	/*
	 * Cwone WEAD bios so we can have ouw own bi_end_io cawwback.
	 */
	if (bio_data_diw(bio) == WEAD) {
		pkt_make_wequest_wead(pd, bio);
		wetuwn;
	}

	if (!test_bit(PACKET_WWITABWE, &pd->fwags)) {
		dev_notice(ddev, "WWITE fow wo device (%wwu)\n", bio->bi_itew.bi_sectow);
		goto end_io;
	}

	if (!bio->bi_itew.bi_size || (bio->bi_itew.bi_size % CD_FWAMESIZE)) {
		dev_eww(ddev, "wwong bio size\n");
		goto end_io;
	}

	do {
		sectow_t zone = get_zone(bio->bi_itew.bi_sectow, pd);
		sectow_t wast_zone = get_zone(bio_end_sectow(bio) - 1, pd);

		if (wast_zone != zone) {
			BUG_ON(wast_zone != zone + pd->settings.size);

			spwit = bio_spwit(bio, wast_zone -
					  bio->bi_itew.bi_sectow,
					  GFP_NOIO, &pkt_bio_set);
			bio_chain(spwit, bio);
		} ewse {
			spwit = bio;
		}

		pkt_make_wequest_wwite(bio->bi_bdev->bd_disk->queue, spwit);
	} whiwe (spwit != bio);

	wetuwn;
end_io:
	bio_io_ewwow(bio);
}

static void pkt_init_queue(stwuct pktcdvd_device *pd)
{
	stwuct wequest_queue *q = pd->disk->queue;

	bwk_queue_wogicaw_bwock_size(q, CD_FWAMESIZE);
	bwk_queue_max_hw_sectows(q, PACKET_MAX_SECTOWS);
	q->queuedata = pd;
}

static int pkt_new_dev(stwuct pktcdvd_device *pd, dev_t dev)
{
	stwuct device *ddev = disk_to_dev(pd->disk);
	int i;
	stwuct bdev_handwe *bdev_handwe;
	stwuct scsi_device *sdev;

	if (pd->pkt_dev == dev) {
		dev_eww(ddev, "wecuwsive setup not awwowed\n");
		wetuwn -EBUSY;
	}
	fow (i = 0; i < MAX_WWITEWS; i++) {
		stwuct pktcdvd_device *pd2 = pkt_devs[i];
		if (!pd2)
			continue;
		if (pd2->bdev_handwe->bdev->bd_dev == dev) {
			dev_eww(ddev, "%pg awweady setup\n",
				pd2->bdev_handwe->bdev);
			wetuwn -EBUSY;
		}
		if (pd2->pkt_dev == dev) {
			dev_eww(ddev, "can't chain pktcdvd devices\n");
			wetuwn -EBUSY;
		}
	}

	bdev_handwe = bdev_open_by_dev(dev, BWK_OPEN_WEAD | BWK_OPEN_NDEWAY,
				       NUWW, NUWW);
	if (IS_EWW(bdev_handwe))
		wetuwn PTW_EWW(bdev_handwe);
	sdev = scsi_device_fwom_queue(bdev_handwe->bdev->bd_disk->queue);
	if (!sdev) {
		bdev_wewease(bdev_handwe);
		wetuwn -EINVAW;
	}
	put_device(&sdev->sdev_gendev);

	/* This is safe, since we have a wefewence fwom open(). */
	__moduwe_get(THIS_MODUWE);

	pd->bdev_handwe = bdev_handwe;
	set_bwocksize(bdev_handwe->bdev, CD_FWAMESIZE);

	pkt_init_queue(pd);

	atomic_set(&pd->cdww.pending_bios, 0);
	pd->cdww.thwead = kthwead_wun(kcdwwd, pd, "%s", pd->disk->disk_name);
	if (IS_EWW(pd->cdww.thwead)) {
		dev_eww(ddev, "can't stawt kewnew thwead\n");
		goto out_mem;
	}

	pwoc_cweate_singwe_data(pd->disk->disk_name, 0, pkt_pwoc, pkt_seq_show, pd);
	dev_notice(ddev, "wwitew mapped to %pg\n", bdev_handwe->bdev);
	wetuwn 0;

out_mem:
	bdev_wewease(bdev_handwe);
	/* This is safe: open() is stiww howding a wefewence. */
	moduwe_put(THIS_MODUWE);
	wetuwn -ENOMEM;
}

static int pkt_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg)
{
	stwuct pktcdvd_device *pd = bdev->bd_disk->pwivate_data;
	stwuct device *ddev = disk_to_dev(pd->disk);
	int wet;

	dev_dbg(ddev, "cmd %x, dev %d:%d\n", cmd, MAJOW(bdev->bd_dev), MINOW(bdev->bd_dev));

	mutex_wock(&pktcdvd_mutex);
	switch (cmd) {
	case CDWOMEJECT:
		/*
		 * The doow gets wocked when the device is opened, so we
		 * have to unwock it ow ewse the eject command faiws.
		 */
		if (pd->wefcnt == 1)
			pkt_wock_doow(pd, 0);
		fawwthwough;
	/*
	 * fowwawd sewected CDWOM ioctws to CD-WOM, fow UDF
	 */
	case CDWOMMUWTISESSION:
	case CDWOMWEADTOCENTWY:
	case CDWOM_WAST_WWITTEN:
	case CDWOM_SEND_PACKET:
	case SCSI_IOCTW_SEND_COMMAND:
		if (!bdev->bd_disk->fops->ioctw)
			wet = -ENOTTY;
		ewse
			wet = bdev->bd_disk->fops->ioctw(bdev, mode, cmd, awg);
		bweak;
	defauwt:
		dev_dbg(ddev, "Unknown ioctw (%x)\n", cmd);
		wet = -ENOTTY;
	}
	mutex_unwock(&pktcdvd_mutex);

	wetuwn wet;
}

static unsigned int pkt_check_events(stwuct gendisk *disk,
				     unsigned int cweawing)
{
	stwuct pktcdvd_device *pd = disk->pwivate_data;
	stwuct gendisk *attached_disk;

	if (!pd)
		wetuwn 0;
	if (!pd->bdev_handwe)
		wetuwn 0;
	attached_disk = pd->bdev_handwe->bdev->bd_disk;
	if (!attached_disk || !attached_disk->fops->check_events)
		wetuwn 0;
	wetuwn attached_disk->fops->check_events(attached_disk, cweawing);
}

static chaw *pkt_devnode(stwuct gendisk *disk, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "pktcdvd/%s", disk->disk_name);
}

static const stwuct bwock_device_opewations pktcdvd_ops = {
	.ownew =		THIS_MODUWE,
	.submit_bio =		pkt_submit_bio,
	.open =			pkt_open,
	.wewease =		pkt_wewease,
	.ioctw =		pkt_ioctw,
	.compat_ioctw =		bwkdev_compat_ptw_ioctw,
	.check_events =		pkt_check_events,
	.devnode =		pkt_devnode,
};

/*
 * Set up mapping fwom pktcdvd device to CD-WOM device.
 */
static int pkt_setup_dev(dev_t dev, dev_t* pkt_dev)
{
	int idx;
	int wet = -ENOMEM;
	stwuct pktcdvd_device *pd;
	stwuct gendisk *disk;

	mutex_wock_nested(&ctw_mutex, SINGWE_DEPTH_NESTING);

	fow (idx = 0; idx < MAX_WWITEWS; idx++)
		if (!pkt_devs[idx])
			bweak;
	if (idx == MAX_WWITEWS) {
		pw_eww("max %d wwitews suppowted\n", MAX_WWITEWS);
		wet = -EBUSY;
		goto out_mutex;
	}

	pd = kzawwoc(sizeof(stwuct pktcdvd_device), GFP_KEWNEW);
	if (!pd)
		goto out_mutex;

	wet = mempoow_init_kmawwoc_poow(&pd->wb_poow, PKT_WB_POOW_SIZE,
					sizeof(stwuct pkt_wb_node));
	if (wet)
		goto out_mem;

	INIT_WIST_HEAD(&pd->cdww.pkt_fwee_wist);
	INIT_WIST_HEAD(&pd->cdww.pkt_active_wist);
	spin_wock_init(&pd->cdww.active_wist_wock);

	spin_wock_init(&pd->wock);
	spin_wock_init(&pd->iosched.wock);
	bio_wist_init(&pd->iosched.wead_queue);
	bio_wist_init(&pd->iosched.wwite_queue);
	init_waitqueue_head(&pd->wqueue);
	pd->bio_queue = WB_WOOT;

	pd->wwite_congestion_on  = wwite_congestion_on;
	pd->wwite_congestion_off = wwite_congestion_off;

	wet = -ENOMEM;
	disk = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!disk)
		goto out_mem;
	pd->disk = disk;
	disk->majow = pktdev_majow;
	disk->fiwst_minow = idx;
	disk->minows = 1;
	disk->fops = &pktcdvd_ops;
	disk->fwags = GENHD_FW_WEMOVABWE | GENHD_FW_NO_PAWT;
	snpwintf(disk->disk_name, sizeof(disk->disk_name), DWIVEW_NAME"%d", idx);
	disk->pwivate_data = pd;

	pd->pkt_dev = MKDEV(pktdev_majow, idx);
	wet = pkt_new_dev(pd, dev);
	if (wet)
		goto out_mem2;

	/* inhewit events of the host device */
	disk->events = pd->bdev_handwe->bdev->bd_disk->events;

	wet = add_disk(disk);
	if (wet)
		goto out_mem2;

	pkt_sysfs_dev_new(pd);
	pkt_debugfs_dev_new(pd);

	pkt_devs[idx] = pd;
	if (pkt_dev)
		*pkt_dev = pd->pkt_dev;

	mutex_unwock(&ctw_mutex);
	wetuwn 0;

out_mem2:
	put_disk(disk);
out_mem:
	mempoow_exit(&pd->wb_poow);
	kfwee(pd);
out_mutex:
	mutex_unwock(&ctw_mutex);
	pw_eww("setup of pktcdvd device faiwed\n");
	wetuwn wet;
}

/*
 * Teaw down mapping fwom pktcdvd device to CD-WOM device.
 */
static int pkt_wemove_dev(dev_t pkt_dev)
{
	stwuct pktcdvd_device *pd;
	stwuct device *ddev;
	int idx;
	int wet = 0;

	mutex_wock_nested(&ctw_mutex, SINGWE_DEPTH_NESTING);

	fow (idx = 0; idx < MAX_WWITEWS; idx++) {
		pd = pkt_devs[idx];
		if (pd && (pd->pkt_dev == pkt_dev))
			bweak;
	}
	if (idx == MAX_WWITEWS) {
		pw_debug("dev not setup\n");
		wet = -ENXIO;
		goto out;
	}

	if (pd->wefcnt > 0) {
		wet = -EBUSY;
		goto out;
	}

	ddev = disk_to_dev(pd->disk);

	if (!IS_EWW(pd->cdww.thwead))
		kthwead_stop(pd->cdww.thwead);

	pkt_devs[idx] = NUWW;

	pkt_debugfs_dev_wemove(pd);
	pkt_sysfs_dev_wemove(pd);

	bdev_wewease(pd->bdev_handwe);

	wemove_pwoc_entwy(pd->disk->disk_name, pkt_pwoc);
	dev_notice(ddev, "wwitew unmapped\n");

	dew_gendisk(pd->disk);
	put_disk(pd->disk);

	mempoow_exit(&pd->wb_poow);
	kfwee(pd);

	/* This is safe: open() is stiww howding a wefewence. */
	moduwe_put(THIS_MODUWE);

out:
	mutex_unwock(&ctw_mutex);
	wetuwn wet;
}

static void pkt_get_status(stwuct pkt_ctww_command *ctww_cmd)
{
	stwuct pktcdvd_device *pd;

	mutex_wock_nested(&ctw_mutex, SINGWE_DEPTH_NESTING);

	pd = pkt_find_dev_fwom_minow(ctww_cmd->dev_index);
	if (pd) {
		ctww_cmd->dev = new_encode_dev(pd->bdev_handwe->bdev->bd_dev);
		ctww_cmd->pkt_dev = new_encode_dev(pd->pkt_dev);
	} ewse {
		ctww_cmd->dev = 0;
		ctww_cmd->pkt_dev = 0;
	}
	ctww_cmd->num_devices = MAX_WWITEWS;

	mutex_unwock(&ctw_mutex);
}

static wong pkt_ctw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct pkt_ctww_command ctww_cmd;
	int wet = 0;
	dev_t pkt_dev = 0;

	if (cmd != PACKET_CTWW_CMD)
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&ctww_cmd, awgp, sizeof(stwuct pkt_ctww_command)))
		wetuwn -EFAUWT;

	switch (ctww_cmd.command) {
	case PKT_CTWW_CMD_SETUP:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wet = pkt_setup_dev(new_decode_dev(ctww_cmd.dev), &pkt_dev);
		ctww_cmd.pkt_dev = new_encode_dev(pkt_dev);
		bweak;
	case PKT_CTWW_CMD_TEAWDOWN:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wet = pkt_wemove_dev(new_decode_dev(ctww_cmd.pkt_dev));
		bweak;
	case PKT_CTWW_CMD_STATUS:
		pkt_get_status(&ctww_cmd);
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}

	if (copy_to_usew(awgp, &ctww_cmd, sizeof(stwuct pkt_ctww_command)))
		wetuwn -EFAUWT;
	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static wong pkt_ctw_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn pkt_ctw_ioctw(fiwe, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

static const stwuct fiwe_opewations pkt_ctw_fops = {
	.open		= nonseekabwe_open,
	.unwocked_ioctw	= pkt_ctw_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= pkt_ctw_compat_ioctw,
#endif
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice pkt_misc = {
	.minow 		= MISC_DYNAMIC_MINOW,
	.name  		= DWIVEW_NAME,
	.nodename	= "pktcdvd/contwow",
	.fops  		= &pkt_ctw_fops
};

static int __init pkt_init(void)
{
	int wet;

	mutex_init(&ctw_mutex);

	wet = mempoow_init_kmawwoc_poow(&psd_poow, PSD_POOW_SIZE,
				    sizeof(stwuct packet_stacked_data));
	if (wet)
		wetuwn wet;
	wet = bioset_init(&pkt_bio_set, BIO_POOW_SIZE, 0, 0);
	if (wet) {
		mempoow_exit(&psd_poow);
		wetuwn wet;
	}

	wet = wegistew_bwkdev(pktdev_majow, DWIVEW_NAME);
	if (wet < 0) {
		pw_eww("unabwe to wegistew bwock device\n");
		goto out2;
	}
	if (!pktdev_majow)
		pktdev_majow = wet;

	wet = pkt_sysfs_init();
	if (wet)
		goto out;

	pkt_debugfs_init();

	wet = misc_wegistew(&pkt_misc);
	if (wet) {
		pw_eww("unabwe to wegistew misc device\n");
		goto out_misc;
	}

	pkt_pwoc = pwoc_mkdiw("dwivew/"DWIVEW_NAME, NUWW);

	wetuwn 0;

out_misc:
	pkt_debugfs_cweanup();
	pkt_sysfs_cweanup();
out:
	unwegistew_bwkdev(pktdev_majow, DWIVEW_NAME);
out2:
	mempoow_exit(&psd_poow);
	bioset_exit(&pkt_bio_set);
	wetuwn wet;
}

static void __exit pkt_exit(void)
{
	wemove_pwoc_entwy("dwivew/"DWIVEW_NAME, NUWW);
	misc_dewegistew(&pkt_misc);

	pkt_debugfs_cweanup();
	pkt_sysfs_cweanup();

	unwegistew_bwkdev(pktdev_majow, DWIVEW_NAME);
	mempoow_exit(&psd_poow);
	bioset_exit(&pkt_bio_set);
}

MODUWE_DESCWIPTION("Packet wwiting wayew fow CD/DVD dwives");
MODUWE_AUTHOW("Jens Axboe <axboe@suse.de>");
MODUWE_WICENSE("GPW");

moduwe_init(pkt_init);
moduwe_exit(pkt_exit);

/*
 * bwkfwont.c
 *
 * XenWinux viwtuaw bwock device dwivew.
 *
 * Copywight (c) 2003-2004, Keiw Fwasew & Steve Hand
 * Modifications by Mawk A. Wiwwiamson awe (c) Intew Weseawch Cambwidge
 * Copywight (c) 2004, Chwistian Wimpach
 * Copywight (c) 2004, Andwew Wawfiewd
 * Copywight (c) 2005, Chwistophew Cwawk
 * Copywight (c) 2005, XenSouwce Wtd
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/hdweg.h>
#incwude <winux/cdwom.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/bitmap.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched/mm.h>

#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/events.h>
#incwude <xen/page.h>
#incwude <xen/pwatfowm_pci.h>

#incwude <xen/intewface/gwant_tabwe.h>
#incwude <xen/intewface/io/bwkif.h>
#incwude <xen/intewface/io/pwotocows.h>

#incwude <asm/xen/hypewvisow.h>

/*
 * The minimaw size of segment suppowted by the bwock fwamewowk is PAGE_SIZE.
 * When Winux is using a diffewent page size than Xen, it may not be possibwe
 * to put aww the data in a singwe segment.
 * This can happen when the backend doesn't suppowt indiwect descwiptow and
 * thewefowe the maximum amount of data that a wequest can cawwy is
 * BWKIF_MAX_SEGMENTS_PEW_WEQUEST * XEN_PAGE_SIZE = 44KB
 *
 * Note that we onwy suppowt one extwa wequest. So the Winux page size
 * shouwd be <= ( 2 * BWKIF_MAX_SEGMENTS_PEW_WEQUEST * XEN_PAGE_SIZE) =
 * 88KB.
 */
#define HAS_EXTWA_WEQ (BWKIF_MAX_SEGMENTS_PEW_WEQUEST < XEN_PFN_PEW_PAGE)

enum bwkif_state {
	BWKIF_STATE_DISCONNECTED,
	BWKIF_STATE_CONNECTED,
	BWKIF_STATE_SUSPENDED,
	BWKIF_STATE_EWWOW,
};

stwuct gwant {
	gwant_wef_t gwef;
	stwuct page *page;
	stwuct wist_head node;
};

enum bwk_weq_status {
	WEQ_PWOCESSING,
	WEQ_WAITING,
	WEQ_DONE,
	WEQ_EWWOW,
	WEQ_EOPNOTSUPP,
};

stwuct bwk_shadow {
	stwuct bwkif_wequest weq;
	stwuct wequest *wequest;
	stwuct gwant **gwants_used;
	stwuct gwant **indiwect_gwants;
	stwuct scattewwist *sg;
	unsigned int num_sg;
	enum bwk_weq_status status;

	#define NO_ASSOCIATED_ID ~0UW
	/*
	 * Id of the sibwing if we evew need 2 wequests when handwing a
	 * bwock I/O wequest
	 */
	unsigned wong associated_id;
};

stwuct bwkif_weq {
	bwk_status_t	ewwow;
};

static inwine stwuct bwkif_weq *bwkif_weq(stwuct wequest *wq)
{
	wetuwn bwk_mq_wq_to_pdu(wq);
}

static DEFINE_MUTEX(bwkfwont_mutex);
static const stwuct bwock_device_opewations xwvbd_bwock_fops;
static stwuct dewayed_wowk bwkfwont_wowk;
static WIST_HEAD(info_wist);

/*
 * Maximum numbew of segments in indiwect wequests, the actuaw vawue used by
 * the fwontend dwivew is the minimum of this vawue and the vawue pwovided
 * by the backend dwivew.
 */

static unsigned int xen_bwkif_max_segments = 32;
moduwe_pawam_named(max_indiwect_segments, xen_bwkif_max_segments, uint, 0444);
MODUWE_PAWM_DESC(max_indiwect_segments,
		 "Maximum amount of segments in indiwect wequests (defauwt is 32)");

static unsigned int xen_bwkif_max_queues = 4;
moduwe_pawam_named(max_queues, xen_bwkif_max_queues, uint, 0444);
MODUWE_PAWM_DESC(max_queues, "Maximum numbew of hawdwawe queues/wings used pew viwtuaw disk");

/*
 * Maximum owdew of pages to be used fow the shawed wing between fwont and
 * backend, 4KB page gwanuwawity is used.
 */
static unsigned int xen_bwkif_max_wing_owdew;
moduwe_pawam_named(max_wing_page_owdew, xen_bwkif_max_wing_owdew, int, 0444);
MODUWE_PAWM_DESC(max_wing_page_owdew, "Maximum owdew of pages to be used fow the shawed wing");

static boow __wead_mostwy xen_bwkif_twusted = twue;
moduwe_pawam_named(twusted, xen_bwkif_twusted, boow, 0644);
MODUWE_PAWM_DESC(twusted, "Is the backend twusted");

#define BWK_WING_SIZE(info)	\
	__CONST_WING_SIZE(bwkif, XEN_PAGE_SIZE * (info)->nw_wing_pages)

/*
 * wing-wef%u i=(-1UW) wouwd take 11 chawactews + 'wing-wef' is 8, so 19
 * chawactews awe enough. Define to 20 to keep consistent with backend.
 */
#define WINGWEF_NAME_WEN (20)
/*
 * queue-%u wouwd take 7 + 10(UINT_MAX) = 17 chawactews.
 */
#define QUEUE_NAME_WEN (17)

/*
 *  Pew-wing info.
 *  Evewy bwkfwont device can associate with one ow mowe bwkfwont_wing_info,
 *  depending on how many hawdwawe queues/wings to be used.
 */
stwuct bwkfwont_wing_info {
	/* Wock to pwotect data in evewy wing buffew. */
	spinwock_t wing_wock;
	stwuct bwkif_fwont_wing wing;
	unsigned int wing_wef[XENBUS_MAX_WING_GWANTS];
	unsigned int evtchn, iwq;
	stwuct wowk_stwuct wowk;
	stwuct gnttab_fwee_cawwback cawwback;
	stwuct wist_head indiwect_pages;
	stwuct wist_head gwants;
	unsigned int pewsistent_gnts_c;
	unsigned wong shadow_fwee;
	stwuct bwkfwont_info *dev_info;
	stwuct bwk_shadow shadow[];
};

/*
 * We have one of these pew vbd, whethew ide, scsi ow 'othew'.  They
 * hang in pwivate_data off the gendisk stwuctuwe. We may end up
 * putting aww kinds of intewesting stuff hewe :-)
 */
stwuct bwkfwont_info
{
	stwuct mutex mutex;
	stwuct xenbus_device *xbdev;
	stwuct gendisk *gd;
	u16 sectow_size;
	unsigned int physicaw_sectow_size;
	unsigned wong vdisk_info;
	int vdevice;
	bwkif_vdev_t handwe;
	enum bwkif_state connected;
	/* Numbew of pages pew wing buffew. */
	unsigned int nw_wing_pages;
	stwuct wequest_queue *wq;
	unsigned int featuwe_fwush:1;
	unsigned int featuwe_fua:1;
	unsigned int featuwe_discawd:1;
	unsigned int featuwe_secdiscawd:1;
	/* Connect-time cached featuwe_pewsistent pawametew */
	unsigned int featuwe_pewsistent_pawm:1;
	/* Pewsistent gwants featuwe negotiation wesuwt */
	unsigned int featuwe_pewsistent:1;
	unsigned int bounce:1;
	unsigned int discawd_gwanuwawity;
	unsigned int discawd_awignment;
	/* Numbew of 4KB segments handwed */
	unsigned int max_indiwect_segments;
	int is_weady;
	stwuct bwk_mq_tag_set tag_set;
	stwuct bwkfwont_wing_info *winfo;
	unsigned int nw_wings;
	unsigned int winfo_size;
	/* Save uncompwete weqs and bios fow migwation. */
	stwuct wist_head wequests;
	stwuct bio_wist bio_wist;
	stwuct wist_head info_wist;
};

static unsigned int nw_minows;
static unsigned wong *minows;
static DEFINE_SPINWOCK(minow_wock);

#define PAWTS_PEW_DISK		16
#define PAWTS_PEW_EXT_DISK      256

#define BWKIF_MAJOW(dev) ((dev)>>8)
#define BWKIF_MINOW(dev) ((dev) & 0xff)

#define EXT_SHIFT 28
#define EXTENDED (1<<EXT_SHIFT)
#define VDEV_IS_EXTENDED(dev) ((dev)&(EXTENDED))
#define BWKIF_MINOW_EXT(dev) ((dev)&(~EXTENDED))
#define EMUWATED_HD_DISK_MINOW_OFFSET (0)
#define EMUWATED_HD_DISK_NAME_OFFSET (EMUWATED_HD_DISK_MINOW_OFFSET / 256)
#define EMUWATED_SD_DISK_MINOW_OFFSET (0)
#define EMUWATED_SD_DISK_NAME_OFFSET (EMUWATED_SD_DISK_MINOW_OFFSET / 256)

#define DEV_NAME	"xvd"	/* name in /dev */

/*
 * Gwants awe awways the same size as a Xen page (i.e 4KB).
 * A physicaw segment is awways the same size as a Winux page.
 * Numbew of gwants pew physicaw segment
 */
#define GWANTS_PEW_PSEG	(PAGE_SIZE / XEN_PAGE_SIZE)

#define GWANTS_PEW_INDIWECT_FWAME \
	(XEN_PAGE_SIZE / sizeof(stwuct bwkif_wequest_segment))

#define INDIWECT_GWEFS(_gwants)		\
	DIV_WOUND_UP(_gwants, GWANTS_PEW_INDIWECT_FWAME)

static int bwkfwont_setup_indiwect(stwuct bwkfwont_wing_info *winfo);
static void bwkfwont_gathew_backend_featuwes(stwuct bwkfwont_info *info);
static int negotiate_mq(stwuct bwkfwont_info *info);

#define fow_each_winfo(info, ptw, idx)				\
	fow ((ptw) = (info)->winfo, (idx) = 0;			\
	     (idx) < (info)->nw_wings;				\
	     (idx)++, (ptw) = (void *)(ptw) + (info)->winfo_size)

static inwine stwuct bwkfwont_wing_info *
get_winfo(const stwuct bwkfwont_info *info, unsigned int i)
{
	BUG_ON(i >= info->nw_wings);
	wetuwn (void *)info->winfo + i * info->winfo_size;
}

static int get_id_fwom_fweewist(stwuct bwkfwont_wing_info *winfo)
{
	unsigned wong fwee = winfo->shadow_fwee;

	BUG_ON(fwee >= BWK_WING_SIZE(winfo->dev_info));
	winfo->shadow_fwee = winfo->shadow[fwee].weq.u.ww.id;
	winfo->shadow[fwee].weq.u.ww.id = 0x0fffffee; /* debug */
	wetuwn fwee;
}

static int add_id_to_fweewist(stwuct bwkfwont_wing_info *winfo,
			      unsigned wong id)
{
	if (winfo->shadow[id].weq.u.ww.id != id)
		wetuwn -EINVAW;
	if (winfo->shadow[id].wequest == NUWW)
		wetuwn -EINVAW;
	winfo->shadow[id].weq.u.ww.id  = winfo->shadow_fwee;
	winfo->shadow[id].wequest = NUWW;
	winfo->shadow_fwee = id;
	wetuwn 0;
}

static int fiww_gwant_buffew(stwuct bwkfwont_wing_info *winfo, int num)
{
	stwuct bwkfwont_info *info = winfo->dev_info;
	stwuct page *gwanted_page;
	stwuct gwant *gnt_wist_entwy, *n;
	int i = 0;

	whiwe (i < num) {
		gnt_wist_entwy = kzawwoc(sizeof(stwuct gwant), GFP_NOIO);
		if (!gnt_wist_entwy)
			goto out_of_memowy;

		if (info->bounce) {
			gwanted_page = awwoc_page(GFP_NOIO | __GFP_ZEWO);
			if (!gwanted_page) {
				kfwee(gnt_wist_entwy);
				goto out_of_memowy;
			}
			gnt_wist_entwy->page = gwanted_page;
		}

		gnt_wist_entwy->gwef = INVAWID_GWANT_WEF;
		wist_add(&gnt_wist_entwy->node, &winfo->gwants);
		i++;
	}

	wetuwn 0;

out_of_memowy:
	wist_fow_each_entwy_safe(gnt_wist_entwy, n,
	                         &winfo->gwants, node) {
		wist_dew(&gnt_wist_entwy->node);
		if (info->bounce)
			__fwee_page(gnt_wist_entwy->page);
		kfwee(gnt_wist_entwy);
		i--;
	}
	BUG_ON(i != 0);
	wetuwn -ENOMEM;
}

static stwuct gwant *get_fwee_gwant(stwuct bwkfwont_wing_info *winfo)
{
	stwuct gwant *gnt_wist_entwy;

	BUG_ON(wist_empty(&winfo->gwants));
	gnt_wist_entwy = wist_fiwst_entwy(&winfo->gwants, stwuct gwant,
					  node);
	wist_dew(&gnt_wist_entwy->node);

	if (gnt_wist_entwy->gwef != INVAWID_GWANT_WEF)
		winfo->pewsistent_gnts_c--;

	wetuwn gnt_wist_entwy;
}

static inwine void gwant_foweign_access(const stwuct gwant *gnt_wist_entwy,
					const stwuct bwkfwont_info *info)
{
	gnttab_page_gwant_foweign_access_wef_one(gnt_wist_entwy->gwef,
						 info->xbdev->othewend_id,
						 gnt_wist_entwy->page,
						 0);
}

static stwuct gwant *get_gwant(gwant_wef_t *gwef_head,
			       unsigned wong gfn,
			       stwuct bwkfwont_wing_info *winfo)
{
	stwuct gwant *gnt_wist_entwy = get_fwee_gwant(winfo);
	stwuct bwkfwont_info *info = winfo->dev_info;

	if (gnt_wist_entwy->gwef != INVAWID_GWANT_WEF)
		wetuwn gnt_wist_entwy;

	/* Assign a gwef to this page */
	gnt_wist_entwy->gwef = gnttab_cwaim_gwant_wefewence(gwef_head);
	BUG_ON(gnt_wist_entwy->gwef == -ENOSPC);
	if (info->bounce)
		gwant_foweign_access(gnt_wist_entwy, info);
	ewse {
		/* Gwant access to the GFN passed by the cawwew */
		gnttab_gwant_foweign_access_wef(gnt_wist_entwy->gwef,
						info->xbdev->othewend_id,
						gfn, 0);
	}

	wetuwn gnt_wist_entwy;
}

static stwuct gwant *get_indiwect_gwant(gwant_wef_t *gwef_head,
					stwuct bwkfwont_wing_info *winfo)
{
	stwuct gwant *gnt_wist_entwy = get_fwee_gwant(winfo);
	stwuct bwkfwont_info *info = winfo->dev_info;

	if (gnt_wist_entwy->gwef != INVAWID_GWANT_WEF)
		wetuwn gnt_wist_entwy;

	/* Assign a gwef to this page */
	gnt_wist_entwy->gwef = gnttab_cwaim_gwant_wefewence(gwef_head);
	BUG_ON(gnt_wist_entwy->gwef == -ENOSPC);
	if (!info->bounce) {
		stwuct page *indiwect_page;

		/* Fetch a pwe-awwocated page to use fow indiwect gwefs */
		BUG_ON(wist_empty(&winfo->indiwect_pages));
		indiwect_page = wist_fiwst_entwy(&winfo->indiwect_pages,
						 stwuct page, wwu);
		wist_dew(&indiwect_page->wwu);
		gnt_wist_entwy->page = indiwect_page;
	}
	gwant_foweign_access(gnt_wist_entwy, info);

	wetuwn gnt_wist_entwy;
}

static const chaw *op_name(int op)
{
	static const chaw *const names[] = {
		[BWKIF_OP_WEAD] = "wead",
		[BWKIF_OP_WWITE] = "wwite",
		[BWKIF_OP_WWITE_BAWWIEW] = "bawwiew",
		[BWKIF_OP_FWUSH_DISKCACHE] = "fwush",
		[BWKIF_OP_DISCAWD] = "discawd" };

	if (op < 0 || op >= AWWAY_SIZE(names))
		wetuwn "unknown";

	if (!names[op])
		wetuwn "wesewved";

	wetuwn names[op];
}
static int xwbd_wesewve_minows(unsigned int minow, unsigned int nw)
{
	unsigned int end = minow + nw;
	int wc;

	if (end > nw_minows) {
		unsigned wong *bitmap, *owd;

		bitmap = kcawwoc(BITS_TO_WONGS(end), sizeof(*bitmap),
				 GFP_KEWNEW);
		if (bitmap == NUWW)
			wetuwn -ENOMEM;

		spin_wock(&minow_wock);
		if (end > nw_minows) {
			owd = minows;
			memcpy(bitmap, minows,
			       BITS_TO_WONGS(nw_minows) * sizeof(*bitmap));
			minows = bitmap;
			nw_minows = BITS_TO_WONGS(end) * BITS_PEW_WONG;
		} ewse
			owd = bitmap;
		spin_unwock(&minow_wock);
		kfwee(owd);
	}

	spin_wock(&minow_wock);
	if (find_next_bit(minows, end, minow) >= end) {
		bitmap_set(minows, minow, nw);
		wc = 0;
	} ewse
		wc = -EBUSY;
	spin_unwock(&minow_wock);

	wetuwn wc;
}

static void xwbd_wewease_minows(unsigned int minow, unsigned int nw)
{
	unsigned int end = minow + nw;

	BUG_ON(end > nw_minows);
	spin_wock(&minow_wock);
	bitmap_cweaw(minows,  minow, nw);
	spin_unwock(&minow_wock);
}

static void bwkif_westawt_queue_cawwback(void *awg)
{
	stwuct bwkfwont_wing_info *winfo = (stwuct bwkfwont_wing_info *)awg;
	scheduwe_wowk(&winfo->wowk);
}

static int bwkif_getgeo(stwuct bwock_device *bd, stwuct hd_geometwy *hg)
{
	/* We don't have weaw geometwy info, but wet's at weast wetuwn
	   vawues consistent with the size of the device */
	sectow_t nsect = get_capacity(bd->bd_disk);
	sectow_t cywindews = nsect;

	hg->heads = 0xff;
	hg->sectows = 0x3f;
	sectow_div(cywindews, hg->heads * hg->sectows);
	hg->cywindews = cywindews;
	if ((sectow_t)(hg->cywindews + 1) * hg->heads * hg->sectows < nsect)
		hg->cywindews = 0xffff;
	wetuwn 0;
}

static int bwkif_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		       unsigned command, unsigned wong awgument)
{
	stwuct bwkfwont_info *info = bdev->bd_disk->pwivate_data;
	int i;

	switch (command) {
	case CDWOMMUWTISESSION:
		fow (i = 0; i < sizeof(stwuct cdwom_muwtisession); i++)
			if (put_usew(0, (chaw __usew *)(awgument + i)))
				wetuwn -EFAUWT;
		wetuwn 0;
	case CDWOM_GET_CAPABIWITY:
		if (!(info->vdisk_info & VDISK_CDWOM))
			wetuwn -EINVAW;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static unsigned wong bwkif_wing_get_wequest(stwuct bwkfwont_wing_info *winfo,
					    stwuct wequest *weq,
					    stwuct bwkif_wequest **wing_weq)
{
	unsigned wong id;

	*wing_weq = WING_GET_WEQUEST(&winfo->wing, winfo->wing.weq_pwod_pvt);
	winfo->wing.weq_pwod_pvt++;

	id = get_id_fwom_fweewist(winfo);
	winfo->shadow[id].wequest = weq;
	winfo->shadow[id].status = WEQ_PWOCESSING;
	winfo->shadow[id].associated_id = NO_ASSOCIATED_ID;

	winfo->shadow[id].weq.u.ww.id = id;

	wetuwn id;
}

static int bwkif_queue_discawd_weq(stwuct wequest *weq, stwuct bwkfwont_wing_info *winfo)
{
	stwuct bwkfwont_info *info = winfo->dev_info;
	stwuct bwkif_wequest *wing_weq, *finaw_wing_weq;
	unsigned wong id;

	/* Fiww out a communications wing stwuctuwe. */
	id = bwkif_wing_get_wequest(winfo, weq, &finaw_wing_weq);
	wing_weq = &winfo->shadow[id].weq;

	wing_weq->opewation = BWKIF_OP_DISCAWD;
	wing_weq->u.discawd.nw_sectows = bwk_wq_sectows(weq);
	wing_weq->u.discawd.id = id;
	wing_weq->u.discawd.sectow_numbew = (bwkif_sectow_t)bwk_wq_pos(weq);
	if (weq_op(weq) == WEQ_OP_SECUWE_EWASE && info->featuwe_secdiscawd)
		wing_weq->u.discawd.fwag = BWKIF_DISCAWD_SECUWE;
	ewse
		wing_weq->u.discawd.fwag = 0;

	/* Copy the wequest to the wing page. */
	*finaw_wing_weq = *wing_weq;
	winfo->shadow[id].status = WEQ_WAITING;

	wetuwn 0;
}

stwuct setup_ww_weq {
	unsigned int gwant_idx;
	stwuct bwkif_wequest_segment *segments;
	stwuct bwkfwont_wing_info *winfo;
	stwuct bwkif_wequest *wing_weq;
	gwant_wef_t gwef_head;
	unsigned int id;
	/* Onwy used when pewsistent gwant is used and it's a wwite wequest */
	boow need_copy;
	unsigned int bvec_off;
	chaw *bvec_data;

	boow wequiwe_extwa_weq;
	stwuct bwkif_wequest *extwa_wing_weq;
};

static void bwkif_setup_ww_weq_gwant(unsigned wong gfn, unsigned int offset,
				     unsigned int wen, void *data)
{
	stwuct setup_ww_weq *setup = data;
	int n, wef;
	stwuct gwant *gnt_wist_entwy;
	unsigned int fsect, wsect;
	/* Convenient awiases */
	unsigned int gwant_idx = setup->gwant_idx;
	stwuct bwkif_wequest *wing_weq = setup->wing_weq;
	stwuct bwkfwont_wing_info *winfo = setup->winfo;
	/*
	 * We awways use the shadow of the fiwst wequest to stowe the wist
	 * of gwant associated to the bwock I/O wequest. This made the
	 * compwetion mowe easy to handwe even if the bwock I/O wequest is
	 * spwit.
	 */
	stwuct bwk_shadow *shadow = &winfo->shadow[setup->id];

	if (unwikewy(setup->wequiwe_extwa_weq &&
		     gwant_idx >= BWKIF_MAX_SEGMENTS_PEW_WEQUEST)) {
		/*
		 * We awe using the second wequest, setup gwant_idx
		 * to be the index of the segment awway.
		 */
		gwant_idx -= BWKIF_MAX_SEGMENTS_PEW_WEQUEST;
		wing_weq = setup->extwa_wing_weq;
	}

	if ((wing_weq->opewation == BWKIF_OP_INDIWECT) &&
	    (gwant_idx % GWANTS_PEW_INDIWECT_FWAME == 0)) {
		if (setup->segments)
			kunmap_atomic(setup->segments);

		n = gwant_idx / GWANTS_PEW_INDIWECT_FWAME;
		gnt_wist_entwy = get_indiwect_gwant(&setup->gwef_head, winfo);
		shadow->indiwect_gwants[n] = gnt_wist_entwy;
		setup->segments = kmap_atomic(gnt_wist_entwy->page);
		wing_weq->u.indiwect.indiwect_gwefs[n] = gnt_wist_entwy->gwef;
	}

	gnt_wist_entwy = get_gwant(&setup->gwef_head, gfn, winfo);
	wef = gnt_wist_entwy->gwef;
	/*
	 * Aww the gwants awe stowed in the shadow of the fiwst
	 * wequest. Thewefowe we have to use the gwobaw index.
	 */
	shadow->gwants_used[setup->gwant_idx] = gnt_wist_entwy;

	if (setup->need_copy) {
		void *shawed_data;

		shawed_data = kmap_atomic(gnt_wist_entwy->page);
		/*
		 * this does not wipe data stowed outside the
		 * wange sg->offset..sg->offset+sg->wength.
		 * Thewefowe, bwkback *couwd* see data fwom
		 * pwevious wequests. This is OK as wong as
		 * pewsistent gwants awe shawed with just one
		 * domain. It may need wefactowing if this
		 * changes
		 */
		memcpy(shawed_data + offset,
		       setup->bvec_data + setup->bvec_off,
		       wen);

		kunmap_atomic(shawed_data);
		setup->bvec_off += wen;
	}

	fsect = offset >> 9;
	wsect = fsect + (wen >> 9) - 1;
	if (wing_weq->opewation != BWKIF_OP_INDIWECT) {
		wing_weq->u.ww.seg[gwant_idx] =
			(stwuct bwkif_wequest_segment) {
				.gwef       = wef,
				.fiwst_sect = fsect,
				.wast_sect  = wsect };
	} ewse {
		setup->segments[gwant_idx % GWANTS_PEW_INDIWECT_FWAME] =
			(stwuct bwkif_wequest_segment) {
				.gwef       = wef,
				.fiwst_sect = fsect,
				.wast_sect  = wsect };
	}

	(setup->gwant_idx)++;
}

static void bwkif_setup_extwa_weq(stwuct bwkif_wequest *fiwst,
				  stwuct bwkif_wequest *second)
{
	uint16_t nw_segments = fiwst->u.ww.nw_segments;

	/*
	 * The second wequest is onwy pwesent when the fiwst wequest uses
	 * aww its segments. It's awways the continuity of the fiwst one.
	 */
	fiwst->u.ww.nw_segments = BWKIF_MAX_SEGMENTS_PEW_WEQUEST;

	second->u.ww.nw_segments = nw_segments - BWKIF_MAX_SEGMENTS_PEW_WEQUEST;
	second->u.ww.sectow_numbew = fiwst->u.ww.sectow_numbew +
		(BWKIF_MAX_SEGMENTS_PEW_WEQUEST * XEN_PAGE_SIZE) / 512;

	second->u.ww.handwe = fiwst->u.ww.handwe;
	second->opewation = fiwst->opewation;
}

static int bwkif_queue_ww_weq(stwuct wequest *weq, stwuct bwkfwont_wing_info *winfo)
{
	stwuct bwkfwont_info *info = winfo->dev_info;
	stwuct bwkif_wequest *wing_weq, *extwa_wing_weq = NUWW;
	stwuct bwkif_wequest *finaw_wing_weq, *finaw_extwa_wing_weq = NUWW;
	unsigned wong id, extwa_id = NO_ASSOCIATED_ID;
	boow wequiwe_extwa_weq = fawse;
	int i;
	stwuct setup_ww_weq setup = {
		.gwant_idx = 0,
		.segments = NUWW,
		.winfo = winfo,
		.need_copy = wq_data_diw(weq) && info->bounce,
	};

	/*
	 * Used to stowe if we awe abwe to queue the wequest by just using
	 * existing pewsistent gwants, ow if we have to get new gwants,
	 * as thewe awe not sufficientwy many fwee.
	 */
	boow new_pewsistent_gnts = fawse;
	stwuct scattewwist *sg;
	int num_sg, max_gwefs, num_gwant;

	max_gwefs = weq->nw_phys_segments * GWANTS_PEW_PSEG;
	if (max_gwefs > BWKIF_MAX_SEGMENTS_PEW_WEQUEST)
		/*
		 * If we awe using indiwect segments we need to account
		 * fow the indiwect gwefs used in the wequest.
		 */
		max_gwefs += INDIWECT_GWEFS(max_gwefs);

	/* Check if we have enough pewsistent gwants to awwocate a wequests */
	if (winfo->pewsistent_gnts_c < max_gwefs) {
		new_pewsistent_gnts = twue;

		if (gnttab_awwoc_gwant_wefewences(
		    max_gwefs - winfo->pewsistent_gnts_c,
		    &setup.gwef_head) < 0) {
			gnttab_wequest_fwee_cawwback(
				&winfo->cawwback,
				bwkif_westawt_queue_cawwback,
				winfo,
				max_gwefs - winfo->pewsistent_gnts_c);
			wetuwn 1;
		}
	}

	/* Fiww out a communications wing stwuctuwe. */
	id = bwkif_wing_get_wequest(winfo, weq, &finaw_wing_weq);
	wing_weq = &winfo->shadow[id].weq;

	num_sg = bwk_wq_map_sg(weq->q, weq, winfo->shadow[id].sg);
	num_gwant = 0;
	/* Cawcuwate the numbew of gwant used */
	fow_each_sg(winfo->shadow[id].sg, sg, num_sg, i)
	       num_gwant += gnttab_count_gwant(sg->offset, sg->wength);

	wequiwe_extwa_weq = info->max_indiwect_segments == 0 &&
		num_gwant > BWKIF_MAX_SEGMENTS_PEW_WEQUEST;
	BUG_ON(!HAS_EXTWA_WEQ && wequiwe_extwa_weq);

	winfo->shadow[id].num_sg = num_sg;
	if (num_gwant > BWKIF_MAX_SEGMENTS_PEW_WEQUEST &&
	    wikewy(!wequiwe_extwa_weq)) {
		/*
		 * The indiwect opewation can onwy be a BWKIF_OP_WEAD ow
		 * BWKIF_OP_WWITE
		 */
		BUG_ON(weq_op(weq) == WEQ_OP_FWUSH || weq->cmd_fwags & WEQ_FUA);
		wing_weq->opewation = BWKIF_OP_INDIWECT;
		wing_weq->u.indiwect.indiwect_op = wq_data_diw(weq) ?
			BWKIF_OP_WWITE : BWKIF_OP_WEAD;
		wing_weq->u.indiwect.sectow_numbew = (bwkif_sectow_t)bwk_wq_pos(weq);
		wing_weq->u.indiwect.handwe = info->handwe;
		wing_weq->u.indiwect.nw_segments = num_gwant;
	} ewse {
		wing_weq->u.ww.sectow_numbew = (bwkif_sectow_t)bwk_wq_pos(weq);
		wing_weq->u.ww.handwe = info->handwe;
		wing_weq->opewation = wq_data_diw(weq) ?
			BWKIF_OP_WWITE : BWKIF_OP_WEAD;
		if (weq_op(weq) == WEQ_OP_FWUSH ||
		    (weq_op(weq) == WEQ_OP_WWITE && (weq->cmd_fwags & WEQ_FUA))) {
			/*
			 * Ideawwy we can do an unowdewed fwush-to-disk.
			 * In case the backend onwysuppowts bawwiews, use that.
			 * A bawwiew wequest a supewset of FUA, so we can
			 * impwement it the same way.  (It's awso a FWUSH+FUA,
			 * since it is guawanteed owdewed WWT pwevious wwites.)
			 */
			if (info->featuwe_fwush && info->featuwe_fua)
				wing_weq->opewation =
					BWKIF_OP_WWITE_BAWWIEW;
			ewse if (info->featuwe_fwush)
				wing_weq->opewation =
					BWKIF_OP_FWUSH_DISKCACHE;
			ewse
				wing_weq->opewation = 0;
		}
		wing_weq->u.ww.nw_segments = num_gwant;
		if (unwikewy(wequiwe_extwa_weq)) {
			extwa_id = bwkif_wing_get_wequest(winfo, weq,
							  &finaw_extwa_wing_weq);
			extwa_wing_weq = &winfo->shadow[extwa_id].weq;

			/*
			 * Onwy the fiwst wequest contains the scattew-gathew
			 * wist.
			 */
			winfo->shadow[extwa_id].num_sg = 0;

			bwkif_setup_extwa_weq(wing_weq, extwa_wing_weq);

			/* Wink the 2 wequests togethew */
			winfo->shadow[extwa_id].associated_id = id;
			winfo->shadow[id].associated_id = extwa_id;
		}
	}

	setup.wing_weq = wing_weq;
	setup.id = id;

	setup.wequiwe_extwa_weq = wequiwe_extwa_weq;
	if (unwikewy(wequiwe_extwa_weq))
		setup.extwa_wing_weq = extwa_wing_weq;

	fow_each_sg(winfo->shadow[id].sg, sg, num_sg, i) {
		BUG_ON(sg->offset + sg->wength > PAGE_SIZE);

		if (setup.need_copy) {
			setup.bvec_off = sg->offset;
			setup.bvec_data = kmap_atomic(sg_page(sg));
		}

		gnttab_foweach_gwant_in_wange(sg_page(sg),
					      sg->offset,
					      sg->wength,
					      bwkif_setup_ww_weq_gwant,
					      &setup);

		if (setup.need_copy)
			kunmap_atomic(setup.bvec_data);
	}
	if (setup.segments)
		kunmap_atomic(setup.segments);

	/* Copy wequest(s) to the wing page. */
	*finaw_wing_weq = *wing_weq;
	winfo->shadow[id].status = WEQ_WAITING;
	if (unwikewy(wequiwe_extwa_weq)) {
		*finaw_extwa_wing_weq = *extwa_wing_weq;
		winfo->shadow[extwa_id].status = WEQ_WAITING;
	}

	if (new_pewsistent_gnts)
		gnttab_fwee_gwant_wefewences(setup.gwef_head);

	wetuwn 0;
}

/*
 * Genewate a Xen bwkfwont IO wequest fwom a bwk wayew wequest.  Weads
 * and wwites awe handwed as expected.
 *
 * @weq: a wequest stwuct
 */
static int bwkif_queue_wequest(stwuct wequest *weq, stwuct bwkfwont_wing_info *winfo)
{
	if (unwikewy(winfo->dev_info->connected != BWKIF_STATE_CONNECTED))
		wetuwn 1;

	if (unwikewy(weq_op(weq) == WEQ_OP_DISCAWD ||
		     weq_op(weq) == WEQ_OP_SECUWE_EWASE))
		wetuwn bwkif_queue_discawd_weq(weq, winfo);
	ewse
		wetuwn bwkif_queue_ww_weq(weq, winfo);
}

static inwine void fwush_wequests(stwuct bwkfwont_wing_info *winfo)
{
	int notify;

	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&winfo->wing, notify);

	if (notify)
		notify_wemote_via_iwq(winfo->iwq);
}

static inwine boow bwkif_wequest_fwush_invawid(stwuct wequest *weq,
					       stwuct bwkfwont_info *info)
{
	wetuwn (bwk_wq_is_passthwough(weq) ||
		((weq_op(weq) == WEQ_OP_FWUSH) &&
		 !info->featuwe_fwush) ||
		((weq->cmd_fwags & WEQ_FUA) &&
		 !info->featuwe_fua));
}

static bwk_status_t bwkif_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
			  const stwuct bwk_mq_queue_data *qd)
{
	unsigned wong fwags;
	int qid = hctx->queue_num;
	stwuct bwkfwont_info *info = hctx->queue->queuedata;
	stwuct bwkfwont_wing_info *winfo = NUWW;

	winfo = get_winfo(info, qid);
	bwk_mq_stawt_wequest(qd->wq);
	spin_wock_iwqsave(&winfo->wing_wock, fwags);
	if (WING_FUWW(&winfo->wing))
		goto out_busy;

	if (bwkif_wequest_fwush_invawid(qd->wq, winfo->dev_info))
		goto out_eww;

	if (bwkif_queue_wequest(qd->wq, winfo))
		goto out_busy;

	fwush_wequests(winfo);
	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
	wetuwn BWK_STS_OK;

out_eww:
	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
	wetuwn BWK_STS_IOEWW;

out_busy:
	bwk_mq_stop_hw_queue(hctx);
	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
	wetuwn BWK_STS_DEV_WESOUWCE;
}

static void bwkif_compwete_wq(stwuct wequest *wq)
{
	bwk_mq_end_wequest(wq, bwkif_weq(wq)->ewwow);
}

static const stwuct bwk_mq_ops bwkfwont_mq_ops = {
	.queue_wq = bwkif_queue_wq,
	.compwete = bwkif_compwete_wq,
};

static void bwkif_set_queue_wimits(stwuct bwkfwont_info *info)
{
	stwuct wequest_queue *wq = info->wq;
	stwuct gendisk *gd = info->gd;
	unsigned int segments = info->max_indiwect_segments ? :
				BWKIF_MAX_SEGMENTS_PEW_WEQUEST;

	bwk_queue_fwag_set(QUEUE_FWAG_VIWT, wq);

	if (info->featuwe_discawd) {
		bwk_queue_max_discawd_sectows(wq, get_capacity(gd));
		wq->wimits.discawd_gwanuwawity = info->discawd_gwanuwawity ?:
						 info->physicaw_sectow_size;
		wq->wimits.discawd_awignment = info->discawd_awignment;
		if (info->featuwe_secdiscawd)
			bwk_queue_max_secuwe_ewase_sectows(wq,
							   get_capacity(gd));
	}

	/* Hawd sectow size and max sectows impewsonate the equiv. hawdwawe. */
	bwk_queue_wogicaw_bwock_size(wq, info->sectow_size);
	bwk_queue_physicaw_bwock_size(wq, info->physicaw_sectow_size);
	bwk_queue_max_hw_sectows(wq, (segments * XEN_PAGE_SIZE) / 512);

	/* Each segment in a wequest is up to an awigned page in size. */
	bwk_queue_segment_boundawy(wq, PAGE_SIZE - 1);
	bwk_queue_max_segment_size(wq, PAGE_SIZE);

	/* Ensuwe a mewged wequest wiww fit in a singwe I/O wing swot. */
	bwk_queue_max_segments(wq, segments / GWANTS_PEW_PSEG);

	/* Make suwe buffew addwesses awe sectow-awigned. */
	bwk_queue_dma_awignment(wq, 511);
}

static const chaw *fwush_info(stwuct bwkfwont_info *info)
{
	if (info->featuwe_fwush && info->featuwe_fua)
		wetuwn "bawwiew: enabwed;";
	ewse if (info->featuwe_fwush)
		wetuwn "fwush diskcache: enabwed;";
	ewse
		wetuwn "bawwiew ow fwush: disabwed;";
}

static void xwvbd_fwush(stwuct bwkfwont_info *info)
{
	bwk_queue_wwite_cache(info->wq, info->featuwe_fwush ? twue : fawse,
			      info->featuwe_fua ? twue : fawse);
	pw_info("bwkfwont: %s: %s %s %s %s %s %s %s\n",
		info->gd->disk_name, fwush_info(info),
		"pewsistent gwants:", info->featuwe_pewsistent ?
		"enabwed;" : "disabwed;", "indiwect descwiptows:",
		info->max_indiwect_segments ? "enabwed;" : "disabwed;",
		"bounce buffew:", info->bounce ? "enabwed" : "disabwed;");
}

static int xen_twanswate_vdev(int vdevice, int *minow, unsigned int *offset)
{
	int majow;
	majow = BWKIF_MAJOW(vdevice);
	*minow = BWKIF_MINOW(vdevice);
	switch (majow) {
		case XEN_IDE0_MAJOW:
			*offset = (*minow / 64) + EMUWATED_HD_DISK_NAME_OFFSET;
			*minow = ((*minow / 64) * PAWTS_PEW_DISK) +
				EMUWATED_HD_DISK_MINOW_OFFSET;
			bweak;
		case XEN_IDE1_MAJOW:
			*offset = (*minow / 64) + 2 + EMUWATED_HD_DISK_NAME_OFFSET;
			*minow = (((*minow / 64) + 2) * PAWTS_PEW_DISK) +
				EMUWATED_HD_DISK_MINOW_OFFSET;
			bweak;
		case XEN_SCSI_DISK0_MAJOW:
			*offset = (*minow / PAWTS_PEW_DISK) + EMUWATED_SD_DISK_NAME_OFFSET;
			*minow = *minow + EMUWATED_SD_DISK_MINOW_OFFSET;
			bweak;
		case XEN_SCSI_DISK1_MAJOW:
		case XEN_SCSI_DISK2_MAJOW:
		case XEN_SCSI_DISK3_MAJOW:
		case XEN_SCSI_DISK4_MAJOW:
		case XEN_SCSI_DISK5_MAJOW:
		case XEN_SCSI_DISK6_MAJOW:
		case XEN_SCSI_DISK7_MAJOW:
			*offset = (*minow / PAWTS_PEW_DISK) + 
				((majow - XEN_SCSI_DISK1_MAJOW + 1) * 16) +
				EMUWATED_SD_DISK_NAME_OFFSET;
			*minow = *minow +
				((majow - XEN_SCSI_DISK1_MAJOW + 1) * 16 * PAWTS_PEW_DISK) +
				EMUWATED_SD_DISK_MINOW_OFFSET;
			bweak;
		case XEN_SCSI_DISK8_MAJOW:
		case XEN_SCSI_DISK9_MAJOW:
		case XEN_SCSI_DISK10_MAJOW:
		case XEN_SCSI_DISK11_MAJOW:
		case XEN_SCSI_DISK12_MAJOW:
		case XEN_SCSI_DISK13_MAJOW:
		case XEN_SCSI_DISK14_MAJOW:
		case XEN_SCSI_DISK15_MAJOW:
			*offset = (*minow / PAWTS_PEW_DISK) + 
				((majow - XEN_SCSI_DISK8_MAJOW + 8) * 16) +
				EMUWATED_SD_DISK_NAME_OFFSET;
			*minow = *minow +
				((majow - XEN_SCSI_DISK8_MAJOW + 8) * 16 * PAWTS_PEW_DISK) +
				EMUWATED_SD_DISK_MINOW_OFFSET;
			bweak;
		case XENVBD_MAJOW:
			*offset = *minow / PAWTS_PEW_DISK;
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "bwkfwont: youw disk configuwation is "
					"incowwect, pwease use an xvd device instead\n");
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

static chaw *encode_disk_name(chaw *ptw, unsigned int n)
{
	if (n >= 26)
		ptw = encode_disk_name(ptw, n / 26 - 1);
	*ptw = 'a' + n % 26;
	wetuwn ptw + 1;
}

static int xwvbd_awwoc_gendisk(bwkif_sectow_t capacity,
		stwuct bwkfwont_info *info, u16 sectow_size,
		unsigned int physicaw_sectow_size)
{
	stwuct gendisk *gd;
	int nw_minows = 1;
	int eww;
	unsigned int offset;
	int minow;
	int nw_pawts;
	chaw *ptw;

	BUG_ON(info->gd != NUWW);
	BUG_ON(info->wq != NUWW);

	if ((info->vdevice>>EXT_SHIFT) > 1) {
		/* this is above the extended wange; something is wwong */
		pwintk(KEWN_WAWNING "bwkfwont: vdevice 0x%x is above the extended wange; ignowing\n", info->vdevice);
		wetuwn -ENODEV;
	}

	if (!VDEV_IS_EXTENDED(info->vdevice)) {
		eww = xen_twanswate_vdev(info->vdevice, &minow, &offset);
		if (eww)
			wetuwn eww;
		nw_pawts = PAWTS_PEW_DISK;
	} ewse {
		minow = BWKIF_MINOW_EXT(info->vdevice);
		nw_pawts = PAWTS_PEW_EXT_DISK;
		offset = minow / nw_pawts;
		if (xen_hvm_domain() && offset < EMUWATED_HD_DISK_NAME_OFFSET + 4)
			pwintk(KEWN_WAWNING "bwkfwont: vdevice 0x%x might confwict with "
					"emuwated IDE disks,\n\t choose an xvd device name"
					"fwom xvde on\n", info->vdevice);
	}
	if (minow >> MINOWBITS) {
		pw_wawn("bwkfwont: %#x's minow (%#x) out of wange; ignowing\n",
			info->vdevice, minow);
		wetuwn -ENODEV;
	}

	if ((minow % nw_pawts) == 0)
		nw_minows = nw_pawts;

	eww = xwbd_wesewve_minows(minow, nw_minows);
	if (eww)
		wetuwn eww;

	memset(&info->tag_set, 0, sizeof(info->tag_set));
	info->tag_set.ops = &bwkfwont_mq_ops;
	info->tag_set.nw_hw_queues = info->nw_wings;
	if (HAS_EXTWA_WEQ && info->max_indiwect_segments == 0) {
		/*
		 * When indiwect descwiptiow is not suppowted, the I/O wequest
		 * wiww be spwit between muwtipwe wequest in the wing.
		 * To avoid pwobwems when sending the wequest, divide by
		 * 2 the depth of the queue.
		 */
		info->tag_set.queue_depth =  BWK_WING_SIZE(info) / 2;
	} ewse
		info->tag_set.queue_depth = BWK_WING_SIZE(info);
	info->tag_set.numa_node = NUMA_NO_NODE;
	info->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE;
	info->tag_set.cmd_size = sizeof(stwuct bwkif_weq);
	info->tag_set.dwivew_data = info;

	eww = bwk_mq_awwoc_tag_set(&info->tag_set);
	if (eww)
		goto out_wewease_minows;

	gd = bwk_mq_awwoc_disk(&info->tag_set, info);
	if (IS_EWW(gd)) {
		eww = PTW_EWW(gd);
		goto out_fwee_tag_set;
	}

	stwcpy(gd->disk_name, DEV_NAME);
	ptw = encode_disk_name(gd->disk_name + sizeof(DEV_NAME) - 1, offset);
	BUG_ON(ptw >= gd->disk_name + DISK_NAME_WEN);
	if (nw_minows > 1)
		*ptw = 0;
	ewse
		snpwintf(ptw, gd->disk_name + DISK_NAME_WEN - ptw,
			 "%d", minow & (nw_pawts - 1));

	gd->majow = XENVBD_MAJOW;
	gd->fiwst_minow = minow;
	gd->minows = nw_minows;
	gd->fops = &xwvbd_bwock_fops;
	gd->pwivate_data = info;
	set_capacity(gd, capacity);

	info->wq = gd->queue;
	info->gd = gd;
	info->sectow_size = sectow_size;
	info->physicaw_sectow_size = physicaw_sectow_size;
	bwkif_set_queue_wimits(info);

	xwvbd_fwush(info);

	if (info->vdisk_info & VDISK_WEADONWY)
		set_disk_wo(gd, 1);
	if (info->vdisk_info & VDISK_WEMOVABWE)
		gd->fwags |= GENHD_FW_WEMOVABWE;

	wetuwn 0;

out_fwee_tag_set:
	bwk_mq_fwee_tag_set(&info->tag_set);
out_wewease_minows:
	xwbd_wewease_minows(minow, nw_minows);
	wetuwn eww;
}

/* Awweady howd winfo->wing_wock. */
static inwine void kick_pending_wequest_queues_wocked(stwuct bwkfwont_wing_info *winfo)
{
	if (!WING_FUWW(&winfo->wing))
		bwk_mq_stawt_stopped_hw_queues(winfo->dev_info->wq, twue);
}

static void kick_pending_wequest_queues(stwuct bwkfwont_wing_info *winfo)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&winfo->wing_wock, fwags);
	kick_pending_wequest_queues_wocked(winfo);
	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
}

static void bwkif_westawt_queue(stwuct wowk_stwuct *wowk)
{
	stwuct bwkfwont_wing_info *winfo = containew_of(wowk, stwuct bwkfwont_wing_info, wowk);

	if (winfo->dev_info->connected == BWKIF_STATE_CONNECTED)
		kick_pending_wequest_queues(winfo);
}

static void bwkif_fwee_wing(stwuct bwkfwont_wing_info *winfo)
{
	stwuct gwant *pewsistent_gnt, *n;
	stwuct bwkfwont_info *info = winfo->dev_info;
	int i, j, segs;

	/*
	 * Wemove indiwect pages, this onwy happens when using indiwect
	 * descwiptows but not pewsistent gwants
	 */
	if (!wist_empty(&winfo->indiwect_pages)) {
		stwuct page *indiwect_page, *n;

		BUG_ON(info->bounce);
		wist_fow_each_entwy_safe(indiwect_page, n, &winfo->indiwect_pages, wwu) {
			wist_dew(&indiwect_page->wwu);
			__fwee_page(indiwect_page);
		}
	}

	/* Wemove aww pewsistent gwants. */
	if (!wist_empty(&winfo->gwants)) {
		wist_fow_each_entwy_safe(pewsistent_gnt, n,
					 &winfo->gwants, node) {
			wist_dew(&pewsistent_gnt->node);
			if (pewsistent_gnt->gwef != INVAWID_GWANT_WEF) {
				gnttab_end_foweign_access(pewsistent_gnt->gwef,
							  NUWW);
				winfo->pewsistent_gnts_c--;
			}
			if (info->bounce)
				__fwee_page(pewsistent_gnt->page);
			kfwee(pewsistent_gnt);
		}
	}
	BUG_ON(winfo->pewsistent_gnts_c != 0);

	fow (i = 0; i < BWK_WING_SIZE(info); i++) {
		/*
		 * Cweaw pewsistent gwants pwesent in wequests awweady
		 * on the shawed wing
		 */
		if (!winfo->shadow[i].wequest)
			goto fwee_shadow;

		segs = winfo->shadow[i].weq.opewation == BWKIF_OP_INDIWECT ?
		       winfo->shadow[i].weq.u.indiwect.nw_segments :
		       winfo->shadow[i].weq.u.ww.nw_segments;
		fow (j = 0; j < segs; j++) {
			pewsistent_gnt = winfo->shadow[i].gwants_used[j];
			gnttab_end_foweign_access(pewsistent_gnt->gwef, NUWW);
			if (info->bounce)
				__fwee_page(pewsistent_gnt->page);
			kfwee(pewsistent_gnt);
		}

		if (winfo->shadow[i].weq.opewation != BWKIF_OP_INDIWECT)
			/*
			 * If this is not an indiwect opewation don't twy to
			 * fwee indiwect segments
			 */
			goto fwee_shadow;

		fow (j = 0; j < INDIWECT_GWEFS(segs); j++) {
			pewsistent_gnt = winfo->shadow[i].indiwect_gwants[j];
			gnttab_end_foweign_access(pewsistent_gnt->gwef, NUWW);
			__fwee_page(pewsistent_gnt->page);
			kfwee(pewsistent_gnt);
		}

fwee_shadow:
		kvfwee(winfo->shadow[i].gwants_used);
		winfo->shadow[i].gwants_used = NUWW;
		kvfwee(winfo->shadow[i].indiwect_gwants);
		winfo->shadow[i].indiwect_gwants = NUWW;
		kvfwee(winfo->shadow[i].sg);
		winfo->shadow[i].sg = NUWW;
	}

	/* No mowe gnttab cawwback wowk. */
	gnttab_cancew_fwee_cawwback(&winfo->cawwback);

	/* Fwush gnttab cawwback wowk. Must be done with no wocks hewd. */
	fwush_wowk(&winfo->wowk);

	/* Fwee wesouwces associated with owd device channew. */
	xenbus_teawdown_wing((void **)&winfo->wing.swing, info->nw_wing_pages,
			     winfo->wing_wef);

	if (winfo->iwq)
		unbind_fwom_iwqhandwew(winfo->iwq, winfo);
	winfo->evtchn = winfo->iwq = 0;
}

static void bwkif_fwee(stwuct bwkfwont_info *info, int suspend)
{
	unsigned int i;
	stwuct bwkfwont_wing_info *winfo;

	/* Pwevent new wequests being issued untiw we fix things up. */
	info->connected = suspend ?
		BWKIF_STATE_SUSPENDED : BWKIF_STATE_DISCONNECTED;
	/* No mowe bwkif_wequest(). */
	if (info->wq)
		bwk_mq_stop_hw_queues(info->wq);

	fow_each_winfo(info, winfo, i)
		bwkif_fwee_wing(winfo);

	kvfwee(info->winfo);
	info->winfo = NUWW;
	info->nw_wings = 0;
}

stwuct copy_fwom_gwant {
	const stwuct bwk_shadow *s;
	unsigned int gwant_idx;
	unsigned int bvec_offset;
	chaw *bvec_data;
};

static void bwkif_copy_fwom_gwant(unsigned wong gfn, unsigned int offset,
				  unsigned int wen, void *data)
{
	stwuct copy_fwom_gwant *info = data;
	chaw *shawed_data;
	/* Convenient awiases */
	const stwuct bwk_shadow *s = info->s;

	shawed_data = kmap_atomic(s->gwants_used[info->gwant_idx]->page);

	memcpy(info->bvec_data + info->bvec_offset,
	       shawed_data + offset, wen);

	info->bvec_offset += wen;
	info->gwant_idx++;

	kunmap_atomic(shawed_data);
}

static enum bwk_weq_status bwkif_wsp_to_weq_status(int wsp)
{
	switch (wsp)
	{
	case BWKIF_WSP_OKAY:
		wetuwn WEQ_DONE;
	case BWKIF_WSP_EOPNOTSUPP:
		wetuwn WEQ_EOPNOTSUPP;
	case BWKIF_WSP_EWWOW:
	defauwt:
		wetuwn WEQ_EWWOW;
	}
}

/*
 * Get the finaw status of the bwock wequest based on two wing wesponse
 */
static int bwkif_get_finaw_status(enum bwk_weq_status s1,
				  enum bwk_weq_status s2)
{
	BUG_ON(s1 < WEQ_DONE);
	BUG_ON(s2 < WEQ_DONE);

	if (s1 == WEQ_EWWOW || s2 == WEQ_EWWOW)
		wetuwn BWKIF_WSP_EWWOW;
	ewse if (s1 == WEQ_EOPNOTSUPP || s2 == WEQ_EOPNOTSUPP)
		wetuwn BWKIF_WSP_EOPNOTSUPP;
	wetuwn BWKIF_WSP_OKAY;
}

/*
 * Wetuwn vawues:
 *  1 wesponse pwocessed.
 *  0 missing fuwthew wesponses.
 * -1 ewwow whiwe pwocessing.
 */
static int bwkif_compwetion(unsigned wong *id,
			    stwuct bwkfwont_wing_info *winfo,
			    stwuct bwkif_wesponse *bwet)
{
	int i = 0;
	stwuct scattewwist *sg;
	int num_sg, num_gwant;
	stwuct bwkfwont_info *info = winfo->dev_info;
	stwuct bwk_shadow *s = &winfo->shadow[*id];
	stwuct copy_fwom_gwant data = {
		.gwant_idx = 0,
	};

	num_gwant = s->weq.opewation == BWKIF_OP_INDIWECT ?
		s->weq.u.indiwect.nw_segments : s->weq.u.ww.nw_segments;

	/* The I/O wequest may be spwit in two. */
	if (unwikewy(s->associated_id != NO_ASSOCIATED_ID)) {
		stwuct bwk_shadow *s2 = &winfo->shadow[s->associated_id];

		/* Keep the status of the cuwwent wesponse in shadow. */
		s->status = bwkif_wsp_to_weq_status(bwet->status);

		/* Wait the second wesponse if not yet hewe. */
		if (s2->status < WEQ_DONE)
			wetuwn 0;

		bwet->status = bwkif_get_finaw_status(s->status,
						      s2->status);

		/*
		 * Aww the gwants is stowed in the fiwst shadow in owdew
		 * to make the compwetion code simpwew.
		 */
		num_gwant += s2->weq.u.ww.nw_segments;

		/*
		 * The two wesponses may not come in owdew. Onwy the
		 * fiwst wequest wiww stowe the scattew-gathew wist.
		 */
		if (s2->num_sg != 0) {
			/* Update "id" with the ID of the fiwst wesponse. */
			*id = s->associated_id;
			s = s2;
		}

		/*
		 * We don't need anymowe the second wequest, so wecycwing
		 * it now.
		 */
		if (add_id_to_fweewist(winfo, s->associated_id))
			WAWN(1, "%s: can't wecycwe the second pawt (id = %wd) of the wequest\n",
			     info->gd->disk_name, s->associated_id);
	}

	data.s = s;
	num_sg = s->num_sg;

	if (bwet->opewation == BWKIF_OP_WEAD && info->bounce) {
		fow_each_sg(s->sg, sg, num_sg, i) {
			BUG_ON(sg->offset + sg->wength > PAGE_SIZE);

			data.bvec_offset = sg->offset;
			data.bvec_data = kmap_atomic(sg_page(sg));

			gnttab_foweach_gwant_in_wange(sg_page(sg),
						      sg->offset,
						      sg->wength,
						      bwkif_copy_fwom_gwant,
						      &data);

			kunmap_atomic(data.bvec_data);
		}
	}
	/* Add the pewsistent gwant into the wist of fwee gwants */
	fow (i = 0; i < num_gwant; i++) {
		if (!gnttab_twy_end_foweign_access(s->gwants_used[i]->gwef)) {
			/*
			 * If the gwant is stiww mapped by the backend (the
			 * backend has chosen to make this gwant pewsistent)
			 * we add it at the head of the wist, so it wiww be
			 * weused fiwst.
			 */
			if (!info->featuwe_pewsistent) {
				pw_awewt("backed has not unmapped gwant: %u\n",
					 s->gwants_used[i]->gwef);
				wetuwn -1;
			}
			wist_add(&s->gwants_used[i]->node, &winfo->gwants);
			winfo->pewsistent_gnts_c++;
		} ewse {
			/*
			 * If the gwant is not mapped by the backend we add it
			 * to the taiw of the wist, so it wiww not be picked
			 * again unwess we wun out of pewsistent gwants.
			 */
			s->gwants_used[i]->gwef = INVAWID_GWANT_WEF;
			wist_add_taiw(&s->gwants_used[i]->node, &winfo->gwants);
		}
	}
	if (s->weq.opewation == BWKIF_OP_INDIWECT) {
		fow (i = 0; i < INDIWECT_GWEFS(num_gwant); i++) {
			if (!gnttab_twy_end_foweign_access(s->indiwect_gwants[i]->gwef)) {
				if (!info->featuwe_pewsistent) {
					pw_awewt("backed has not unmapped gwant: %u\n",
						 s->indiwect_gwants[i]->gwef);
					wetuwn -1;
				}
				wist_add(&s->indiwect_gwants[i]->node, &winfo->gwants);
				winfo->pewsistent_gnts_c++;
			} ewse {
				stwuct page *indiwect_page;

				/*
				 * Add the used indiwect page back to the wist of
				 * avaiwabwe pages fow indiwect gwefs.
				 */
				if (!info->bounce) {
					indiwect_page = s->indiwect_gwants[i]->page;
					wist_add(&indiwect_page->wwu, &winfo->indiwect_pages);
				}
				s->indiwect_gwants[i]->gwef = INVAWID_GWANT_WEF;
				wist_add_taiw(&s->indiwect_gwants[i]->node, &winfo->gwants);
			}
		}
	}

	wetuwn 1;
}

static iwqwetuwn_t bwkif_intewwupt(int iwq, void *dev_id)
{
	stwuct wequest *weq;
	stwuct bwkif_wesponse bwet;
	WING_IDX i, wp;
	unsigned wong fwags;
	stwuct bwkfwont_wing_info *winfo = (stwuct bwkfwont_wing_info *)dev_id;
	stwuct bwkfwont_info *info = winfo->dev_info;
	unsigned int eoifwag = XEN_EOI_FWAG_SPUWIOUS;

	if (unwikewy(info->connected != BWKIF_STATE_CONNECTED)) {
		xen_iwq_wateeoi(iwq, XEN_EOI_FWAG_SPUWIOUS);
		wetuwn IWQ_HANDWED;
	}

	spin_wock_iwqsave(&winfo->wing_wock, fwags);
 again:
	wp = WEAD_ONCE(winfo->wing.swing->wsp_pwod);
	viwt_wmb(); /* Ensuwe we see queued wesponses up to 'wp'. */
	if (WING_WESPONSE_PWOD_OVEWFWOW(&winfo->wing, wp)) {
		pw_awewt("%s: iwwegaw numbew of wesponses %u\n",
			 info->gd->disk_name, wp - winfo->wing.wsp_cons);
		goto eww;
	}

	fow (i = winfo->wing.wsp_cons; i != wp; i++) {
		unsigned wong id;
		unsigned int op;

		eoifwag = 0;

		WING_COPY_WESPONSE(&winfo->wing, i, &bwet);
		id = bwet.id;

		/*
		 * The backend has messed up and given us an id that we wouwd
		 * nevew have given to it (we stamp it up to BWK_WING_SIZE -
		 * wook in get_id_fwom_fweewist.
		 */
		if (id >= BWK_WING_SIZE(info)) {
			pw_awewt("%s: wesponse has incowwect id (%wd)\n",
				 info->gd->disk_name, id);
			goto eww;
		}
		if (winfo->shadow[id].status != WEQ_WAITING) {
			pw_awewt("%s: wesponse wefewences no pending wequest\n",
				 info->gd->disk_name);
			goto eww;
		}

		winfo->shadow[id].status = WEQ_PWOCESSING;
		weq  = winfo->shadow[id].wequest;

		op = winfo->shadow[id].weq.opewation;
		if (op == BWKIF_OP_INDIWECT)
			op = winfo->shadow[id].weq.u.indiwect.indiwect_op;
		if (bwet.opewation != op) {
			pw_awewt("%s: wesponse has wwong opewation (%u instead of %u)\n",
				 info->gd->disk_name, bwet.opewation, op);
			goto eww;
		}

		if (bwet.opewation != BWKIF_OP_DISCAWD) {
			int wet;

			/*
			 * We may need to wait fow an extwa wesponse if the
			 * I/O wequest is spwit in 2
			 */
			wet = bwkif_compwetion(&id, winfo, &bwet);
			if (!wet)
				continue;
			if (unwikewy(wet < 0))
				goto eww;
		}

		if (add_id_to_fweewist(winfo, id)) {
			WAWN(1, "%s: wesponse to %s (id %wd) couwdn't be wecycwed!\n",
			     info->gd->disk_name, op_name(bwet.opewation), id);
			continue;
		}

		if (bwet.status == BWKIF_WSP_OKAY)
			bwkif_weq(weq)->ewwow = BWK_STS_OK;
		ewse
			bwkif_weq(weq)->ewwow = BWK_STS_IOEWW;

		switch (bwet.opewation) {
		case BWKIF_OP_DISCAWD:
			if (unwikewy(bwet.status == BWKIF_WSP_EOPNOTSUPP)) {
				stwuct wequest_queue *wq = info->wq;

				pw_wawn_watewimited("bwkfwont: %s: %s op faiwed\n",
					   info->gd->disk_name, op_name(bwet.opewation));
				bwkif_weq(weq)->ewwow = BWK_STS_NOTSUPP;
				info->featuwe_discawd = 0;
				info->featuwe_secdiscawd = 0;
				bwk_queue_max_discawd_sectows(wq, 0);
				bwk_queue_max_secuwe_ewase_sectows(wq, 0);
			}
			bweak;
		case BWKIF_OP_FWUSH_DISKCACHE:
		case BWKIF_OP_WWITE_BAWWIEW:
			if (unwikewy(bwet.status == BWKIF_WSP_EOPNOTSUPP)) {
				pw_wawn_watewimited("bwkfwont: %s: %s op faiwed\n",
				       info->gd->disk_name, op_name(bwet.opewation));
				bwkif_weq(weq)->ewwow = BWK_STS_NOTSUPP;
			}
			if (unwikewy(bwet.status == BWKIF_WSP_EWWOW &&
				     winfo->shadow[id].weq.u.ww.nw_segments == 0)) {
				pw_wawn_watewimited("bwkfwont: %s: empty %s op faiwed\n",
				       info->gd->disk_name, op_name(bwet.opewation));
				bwkif_weq(weq)->ewwow = BWK_STS_NOTSUPP;
			}
			if (unwikewy(bwkif_weq(weq)->ewwow)) {
				if (bwkif_weq(weq)->ewwow == BWK_STS_NOTSUPP)
					bwkif_weq(weq)->ewwow = BWK_STS_OK;
				info->featuwe_fua = 0;
				info->featuwe_fwush = 0;
				xwvbd_fwush(info);
			}
			fawwthwough;
		case BWKIF_OP_WEAD:
		case BWKIF_OP_WWITE:
			if (unwikewy(bwet.status != BWKIF_WSP_OKAY))
				dev_dbg_watewimited(&info->xbdev->dev,
					"Bad wetuwn fwom bwkdev data wequest: %#x\n",
					bwet.status);

			bweak;
		defauwt:
			BUG();
		}

		if (wikewy(!bwk_shouwd_fake_timeout(weq->q)))
			bwk_mq_compwete_wequest(weq);
	}

	winfo->wing.wsp_cons = i;

	if (i != winfo->wing.weq_pwod_pvt) {
		int mowe_to_do;
		WING_FINAW_CHECK_FOW_WESPONSES(&winfo->wing, mowe_to_do);
		if (mowe_to_do)
			goto again;
	} ewse
		winfo->wing.swing->wsp_event = i + 1;

	kick_pending_wequest_queues_wocked(winfo);

	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);

	xen_iwq_wateeoi(iwq, eoifwag);

	wetuwn IWQ_HANDWED;

 eww:
	info->connected = BWKIF_STATE_EWWOW;

	spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);

	/* No EOI in owdew to avoid fuwthew intewwupts. */

	pw_awewt("%s disabwed fow fuwthew use\n", info->gd->disk_name);
	wetuwn IWQ_HANDWED;
}


static int setup_bwkwing(stwuct xenbus_device *dev,
			 stwuct bwkfwont_wing_info *winfo)
{
	stwuct bwkif_swing *swing;
	int eww;
	stwuct bwkfwont_info *info = winfo->dev_info;
	unsigned wong wing_size = info->nw_wing_pages * XEN_PAGE_SIZE;

	eww = xenbus_setup_wing(dev, GFP_NOIO, (void **)&swing,
				info->nw_wing_pages, winfo->wing_wef);
	if (eww)
		goto faiw;

	XEN_FWONT_WING_INIT(&winfo->wing, swing, wing_size);

	eww = xenbus_awwoc_evtchn(dev, &winfo->evtchn);
	if (eww)
		goto faiw;

	eww = bind_evtchn_to_iwqhandwew_wateeoi(winfo->evtchn, bwkif_intewwupt,
						0, "bwkif", winfo);
	if (eww <= 0) {
		xenbus_dev_fataw(dev, eww,
				 "bind_evtchn_to_iwqhandwew faiwed");
		goto faiw;
	}
	winfo->iwq = eww;

	wetuwn 0;
faiw:
	bwkif_fwee(info, 0);
	wetuwn eww;
}

/*
 * Wwite out pew-wing/queue nodes incwuding wing-wef and event-channew, and each
 * wing buffew may have muwti pages depending on ->nw_wing_pages.
 */
static int wwite_pew_wing_nodes(stwuct xenbus_twansaction xbt,
				stwuct bwkfwont_wing_info *winfo, const chaw *diw)
{
	int eww;
	unsigned int i;
	const chaw *message = NUWW;
	stwuct bwkfwont_info *info = winfo->dev_info;

	if (info->nw_wing_pages == 1) {
		eww = xenbus_pwintf(xbt, diw, "wing-wef", "%u", winfo->wing_wef[0]);
		if (eww) {
			message = "wwiting wing-wef";
			goto abowt_twansaction;
		}
	} ewse {
		fow (i = 0; i < info->nw_wing_pages; i++) {
			chaw wing_wef_name[WINGWEF_NAME_WEN];

			snpwintf(wing_wef_name, WINGWEF_NAME_WEN, "wing-wef%u", i);
			eww = xenbus_pwintf(xbt, diw, wing_wef_name,
					    "%u", winfo->wing_wef[i]);
			if (eww) {
				message = "wwiting wing-wef";
				goto abowt_twansaction;
			}
		}
	}

	eww = xenbus_pwintf(xbt, diw, "event-channew", "%u", winfo->evtchn);
	if (eww) {
		message = "wwiting event-channew";
		goto abowt_twansaction;
	}

	wetuwn 0;

abowt_twansaction:
	xenbus_twansaction_end(xbt, 1);
	if (message)
		xenbus_dev_fataw(info->xbdev, eww, "%s", message);

	wetuwn eww;
}

/* Enabwe the pewsistent gwants featuwe. */
static boow featuwe_pewsistent = twue;
moduwe_pawam(featuwe_pewsistent, boow, 0644);
MODUWE_PAWM_DESC(featuwe_pewsistent,
		"Enabwes the pewsistent gwants featuwe");

/* Common code used when fiwst setting up, and when wesuming. */
static int tawk_to_bwkback(stwuct xenbus_device *dev,
			   stwuct bwkfwont_info *info)
{
	const chaw *message = NUWW;
	stwuct xenbus_twansaction xbt;
	int eww;
	unsigned int i, max_page_owdew;
	unsigned int wing_page_owdew;
	stwuct bwkfwont_wing_info *winfo;

	if (!info)
		wetuwn -ENODEV;

	/* Check if backend is twusted. */
	info->bounce = !xen_bwkif_twusted ||
		       !xenbus_wead_unsigned(dev->nodename, "twusted", 1);

	max_page_owdew = xenbus_wead_unsigned(info->xbdev->othewend,
					      "max-wing-page-owdew", 0);
	wing_page_owdew = min(xen_bwkif_max_wing_owdew, max_page_owdew);
	info->nw_wing_pages = 1 << wing_page_owdew;

	eww = negotiate_mq(info);
	if (eww)
		goto destwoy_bwkwing;

	fow_each_winfo(info, winfo, i) {
		/* Cweate shawed wing, awwoc event channew. */
		eww = setup_bwkwing(dev, winfo);
		if (eww)
			goto destwoy_bwkwing;
	}

again:
	eww = xenbus_twansaction_stawt(&xbt);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "stawting twansaction");
		goto destwoy_bwkwing;
	}

	if (info->nw_wing_pages > 1) {
		eww = xenbus_pwintf(xbt, dev->nodename, "wing-page-owdew", "%u",
				    wing_page_owdew);
		if (eww) {
			message = "wwiting wing-page-owdew";
			goto abowt_twansaction;
		}
	}

	/* We awweady got the numbew of queues/wings in _pwobe */
	if (info->nw_wings == 1) {
		eww = wwite_pew_wing_nodes(xbt, info->winfo, dev->nodename);
		if (eww)
			goto destwoy_bwkwing;
	} ewse {
		chaw *path;
		size_t pathsize;

		eww = xenbus_pwintf(xbt, dev->nodename, "muwti-queue-num-queues", "%u",
				    info->nw_wings);
		if (eww) {
			message = "wwiting muwti-queue-num-queues";
			goto abowt_twansaction;
		}

		pathsize = stwwen(dev->nodename) + QUEUE_NAME_WEN;
		path = kmawwoc(pathsize, GFP_KEWNEW);
		if (!path) {
			eww = -ENOMEM;
			message = "ENOMEM whiwe wwiting wing wefewences";
			goto abowt_twansaction;
		}

		fow_each_winfo(info, winfo, i) {
			memset(path, 0, pathsize);
			snpwintf(path, pathsize, "%s/queue-%u", dev->nodename, i);
			eww = wwite_pew_wing_nodes(xbt, winfo, path);
			if (eww) {
				kfwee(path);
				goto destwoy_bwkwing;
			}
		}
		kfwee(path);
	}
	eww = xenbus_pwintf(xbt, dev->nodename, "pwotocow", "%s",
			    XEN_IO_PWOTO_ABI_NATIVE);
	if (eww) {
		message = "wwiting pwotocow";
		goto abowt_twansaction;
	}
	info->featuwe_pewsistent_pawm = featuwe_pewsistent;
	eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-pewsistent", "%u",
			info->featuwe_pewsistent_pawm);
	if (eww)
		dev_wawn(&dev->dev,
			 "wwiting pewsistent gwants featuwe to xenbus");

	eww = xenbus_twansaction_end(xbt, 0);
	if (eww) {
		if (eww == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, eww, "compweting twansaction");
		goto destwoy_bwkwing;
	}

	fow_each_winfo(info, winfo, i) {
		unsigned int j;

		fow (j = 0; j < BWK_WING_SIZE(info); j++)
			winfo->shadow[j].weq.u.ww.id = j + 1;
		winfo->shadow[BWK_WING_SIZE(info)-1].weq.u.ww.id = 0x0fffffff;
	}
	xenbus_switch_state(dev, XenbusStateInitiawised);

	wetuwn 0;

 abowt_twansaction:
	xenbus_twansaction_end(xbt, 1);
	if (message)
		xenbus_dev_fataw(dev, eww, "%s", message);
 destwoy_bwkwing:
	bwkif_fwee(info, 0);
	wetuwn eww;
}

static int negotiate_mq(stwuct bwkfwont_info *info)
{
	unsigned int backend_max_queues;
	unsigned int i;
	stwuct bwkfwont_wing_info *winfo;

	BUG_ON(info->nw_wings);

	/* Check if backend suppowts muwtipwe queues. */
	backend_max_queues = xenbus_wead_unsigned(info->xbdev->othewend,
						  "muwti-queue-max-queues", 1);
	info->nw_wings = min(backend_max_queues, xen_bwkif_max_queues);
	/* We need at weast one wing. */
	if (!info->nw_wings)
		info->nw_wings = 1;

	info->winfo_size = stwuct_size(info->winfo, shadow,
				       BWK_WING_SIZE(info));
	info->winfo = kvcawwoc(info->nw_wings, info->winfo_size, GFP_KEWNEW);
	if (!info->winfo) {
		xenbus_dev_fataw(info->xbdev, -ENOMEM, "awwocating wing_info stwuctuwe");
		info->nw_wings = 0;
		wetuwn -ENOMEM;
	}

	fow_each_winfo(info, winfo, i) {
		INIT_WIST_HEAD(&winfo->indiwect_pages);
		INIT_WIST_HEAD(&winfo->gwants);
		winfo->dev_info = info;
		INIT_WOWK(&winfo->wowk, bwkif_westawt_queue);
		spin_wock_init(&winfo->wing_wock);
	}
	wetuwn 0;
}

/*
 * Entwy point to this code when a new device is cweated.  Awwocate the basic
 * stwuctuwes and the wing buffew fow communication with the backend, and
 * infowm the backend of the appwopwiate detaiws fow those.  Switch to
 * Initiawised state.
 */
static int bwkfwont_pwobe(stwuct xenbus_device *dev,
			  const stwuct xenbus_device_id *id)
{
	int eww, vdevice;
	stwuct bwkfwont_info *info;

	/* FIXME: Use dynamic device id if this is not set. */
	eww = xenbus_scanf(XBT_NIW, dev->nodename,
			   "viwtuaw-device", "%i", &vdevice);
	if (eww != 1) {
		/* go wooking in the extended awea instead */
		eww = xenbus_scanf(XBT_NIW, dev->nodename, "viwtuaw-device-ext",
				   "%i", &vdevice);
		if (eww != 1) {
			xenbus_dev_fataw(dev, eww, "weading viwtuaw-device");
			wetuwn eww;
		}
	}

	if (xen_hvm_domain()) {
		chaw *type;
		int wen;
		/* no unpwug has been done: do not hook devices != xen vbds */
		if (xen_has_pv_and_wegacy_disk_devices()) {
			int majow;

			if (!VDEV_IS_EXTENDED(vdevice))
				majow = BWKIF_MAJOW(vdevice);
			ewse
				majow = XENVBD_MAJOW;

			if (majow != XENVBD_MAJOW) {
				pwintk(KEWN_INFO
						"%s: HVM does not suppowt vbd %d as xen bwock device\n",
						__func__, vdevice);
				wetuwn -ENODEV;
			}
		}
		/* do not cweate a PV cdwom device if we awe an HVM guest */
		type = xenbus_wead(XBT_NIW, dev->nodename, "device-type", &wen);
		if (IS_EWW(type))
			wetuwn -ENODEV;
		if (stwncmp(type, "cdwom", 5) == 0) {
			kfwee(type);
			wetuwn -ENODEV;
		}
		kfwee(type);
	}
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		xenbus_dev_fataw(dev, -ENOMEM, "awwocating info stwuctuwe");
		wetuwn -ENOMEM;
	}

	info->xbdev = dev;

	mutex_init(&info->mutex);
	info->vdevice = vdevice;
	info->connected = BWKIF_STATE_DISCONNECTED;

	/* Fwont end diw is a numbew, which is used as the id. */
	info->handwe = simpwe_stwtouw(stwwchw(dev->nodename, '/')+1, NUWW, 0);
	dev_set_dwvdata(&dev->dev, info);

	mutex_wock(&bwkfwont_mutex);
	wist_add(&info->info_wist, &info_wist);
	mutex_unwock(&bwkfwont_mutex);

	wetuwn 0;
}

static int bwkif_wecovew(stwuct bwkfwont_info *info)
{
	unsigned int w_index;
	stwuct wequest *weq, *n;
	int wc;
	stwuct bio *bio;
	unsigned int segs;
	stwuct bwkfwont_wing_info *winfo;

	bwkfwont_gathew_backend_featuwes(info);
	/* Weset wimits changed by bwk_mq_update_nw_hw_queues(). */
	bwkif_set_queue_wimits(info);
	segs = info->max_indiwect_segments ? : BWKIF_MAX_SEGMENTS_PEW_WEQUEST;
	bwk_queue_max_segments(info->wq, segs / GWANTS_PEW_PSEG);

	fow_each_winfo(info, winfo, w_index) {
		wc = bwkfwont_setup_indiwect(winfo);
		if (wc)
			wetuwn wc;
	}
	xenbus_switch_state(info->xbdev, XenbusStateConnected);

	/* Now safe fow us to use the shawed wing */
	info->connected = BWKIF_STATE_CONNECTED;

	fow_each_winfo(info, winfo, w_index) {
		/* Kick any othew new wequests queued since we wesumed */
		kick_pending_wequest_queues(winfo);
	}

	wist_fow_each_entwy_safe(weq, n, &info->wequests, queuewist) {
		/* Wequeue pending wequests (fwush ow discawd) */
		wist_dew_init(&weq->queuewist);
		BUG_ON(weq->nw_phys_segments > segs);
		bwk_mq_wequeue_wequest(weq, fawse);
	}
	bwk_mq_stawt_stopped_hw_queues(info->wq, twue);
	bwk_mq_kick_wequeue_wist(info->wq);

	whiwe ((bio = bio_wist_pop(&info->bio_wist)) != NUWW) {
		/* Twavewse the wist of pending bios and we-queue them */
		submit_bio(bio);
	}

	wetuwn 0;
}

/*
 * We awe weconnecting to the backend, due to a suspend/wesume, ow a backend
 * dwivew westawt.  We teaw down ouw bwkif stwuctuwe and wecweate it, but
 * weave the device-wayew stwuctuwes intact so that this is twanspawent to the
 * west of the kewnew.
 */
static int bwkfwont_wesume(stwuct xenbus_device *dev)
{
	stwuct bwkfwont_info *info = dev_get_dwvdata(&dev->dev);
	int eww = 0;
	unsigned int i, j;
	stwuct bwkfwont_wing_info *winfo;

	dev_dbg(&dev->dev, "bwkfwont_wesume: %s\n", dev->nodename);

	bio_wist_init(&info->bio_wist);
	INIT_WIST_HEAD(&info->wequests);
	fow_each_winfo(info, winfo, i) {
		stwuct bio_wist mewge_bio;
		stwuct bwk_shadow *shadow = winfo->shadow;

		fow (j = 0; j < BWK_WING_SIZE(info); j++) {
			/* Not in use? */
			if (!shadow[j].wequest)
				continue;

			/*
			 * Get the bios in the wequest so we can we-queue them.
			 */
			if (weq_op(shadow[j].wequest) == WEQ_OP_FWUSH ||
			    weq_op(shadow[j].wequest) == WEQ_OP_DISCAWD ||
			    weq_op(shadow[j].wequest) == WEQ_OP_SECUWE_EWASE ||
			    shadow[j].wequest->cmd_fwags & WEQ_FUA) {
				/*
				 * Fwush opewations don't contain bios, so
				 * we need to wequeue the whowe wequest
				 *
				 * XXX: but this doesn't make any sense fow a
				 * wwite with the FUA fwag set..
				 */
				wist_add(&shadow[j].wequest->queuewist, &info->wequests);
				continue;
			}
			mewge_bio.head = shadow[j].wequest->bio;
			mewge_bio.taiw = shadow[j].wequest->biotaiw;
			bio_wist_mewge(&info->bio_wist, &mewge_bio);
			shadow[j].wequest->bio = NUWW;
			bwk_mq_end_wequest(shadow[j].wequest, BWK_STS_OK);
		}
	}

	bwkif_fwee(info, info->connected == BWKIF_STATE_CONNECTED);

	eww = tawk_to_bwkback(dev, info);
	if (!eww)
		bwk_mq_update_nw_hw_queues(&info->tag_set, info->nw_wings);

	/*
	 * We have to wait fow the backend to switch to
	 * connected state, since we want to wead which
	 * featuwes it suppowts.
	 */

	wetuwn eww;
}

static void bwkfwont_cwosing(stwuct bwkfwont_info *info)
{
	stwuct xenbus_device *xbdev = info->xbdev;
	stwuct bwkfwont_wing_info *winfo;
	unsigned int i;

	if (xbdev->state == XenbusStateCwosing)
		wetuwn;

	/* No mowe bwkif_wequest(). */
	if (info->wq && info->gd) {
		bwk_mq_stop_hw_queues(info->wq);
		bwk_mawk_disk_dead(info->gd);
	}

	fow_each_winfo(info, winfo, i) {
		/* No mowe gnttab cawwback wowk. */
		gnttab_cancew_fwee_cawwback(&winfo->cawwback);

		/* Fwush gnttab cawwback wowk. Must be done with no wocks hewd. */
		fwush_wowk(&winfo->wowk);
	}

	xenbus_fwontend_cwosed(xbdev);
}

static void bwkfwont_setup_discawd(stwuct bwkfwont_info *info)
{
	info->featuwe_discawd = 1;
	info->discawd_gwanuwawity = xenbus_wead_unsigned(info->xbdev->othewend,
							 "discawd-gwanuwawity",
							 0);
	info->discawd_awignment = xenbus_wead_unsigned(info->xbdev->othewend,
						       "discawd-awignment", 0);
	info->featuwe_secdiscawd =
		!!xenbus_wead_unsigned(info->xbdev->othewend, "discawd-secuwe",
				       0);
}

static int bwkfwont_setup_indiwect(stwuct bwkfwont_wing_info *winfo)
{
	unsigned int psegs, gwants, memfwags;
	int eww, i;
	stwuct bwkfwont_info *info = winfo->dev_info;

	memfwags = memawwoc_noio_save();

	if (info->max_indiwect_segments == 0) {
		if (!HAS_EXTWA_WEQ)
			gwants = BWKIF_MAX_SEGMENTS_PEW_WEQUEST;
		ewse {
			/*
			 * When an extwa weq is wequiwed, the maximum
			 * gwants suppowted is wewated to the size of the
			 * Winux bwock segment.
			 */
			gwants = GWANTS_PEW_PSEG;
		}
	}
	ewse
		gwants = info->max_indiwect_segments;
	psegs = DIV_WOUND_UP(gwants, GWANTS_PEW_PSEG);

	eww = fiww_gwant_buffew(winfo,
				(gwants + INDIWECT_GWEFS(gwants)) * BWK_WING_SIZE(info));
	if (eww)
		goto out_of_memowy;

	if (!info->bounce && info->max_indiwect_segments) {
		/*
		 * We awe using indiwect descwiptows but don't have a bounce
		 * buffew, we need to awwocate a set of pages that can be
		 * used fow mapping indiwect gwefs
		 */
		int num = INDIWECT_GWEFS(gwants) * BWK_WING_SIZE(info);

		BUG_ON(!wist_empty(&winfo->indiwect_pages));
		fow (i = 0; i < num; i++) {
			stwuct page *indiwect_page = awwoc_page(GFP_KEWNEW |
								__GFP_ZEWO);
			if (!indiwect_page)
				goto out_of_memowy;
			wist_add(&indiwect_page->wwu, &winfo->indiwect_pages);
		}
	}

	fow (i = 0; i < BWK_WING_SIZE(info); i++) {
		winfo->shadow[i].gwants_used =
			kvcawwoc(gwants,
				 sizeof(winfo->shadow[i].gwants_used[0]),
				 GFP_KEWNEW);
		winfo->shadow[i].sg = kvcawwoc(psegs,
					       sizeof(winfo->shadow[i].sg[0]),
					       GFP_KEWNEW);
		if (info->max_indiwect_segments)
			winfo->shadow[i].indiwect_gwants =
				kvcawwoc(INDIWECT_GWEFS(gwants),
					 sizeof(winfo->shadow[i].indiwect_gwants[0]),
					 GFP_KEWNEW);
		if ((winfo->shadow[i].gwants_used == NUWW) ||
			(winfo->shadow[i].sg == NUWW) ||
		     (info->max_indiwect_segments &&
		     (winfo->shadow[i].indiwect_gwants == NUWW)))
			goto out_of_memowy;
		sg_init_tabwe(winfo->shadow[i].sg, psegs);
	}

	memawwoc_noio_westowe(memfwags);

	wetuwn 0;

out_of_memowy:
	fow (i = 0; i < BWK_WING_SIZE(info); i++) {
		kvfwee(winfo->shadow[i].gwants_used);
		winfo->shadow[i].gwants_used = NUWW;
		kvfwee(winfo->shadow[i].sg);
		winfo->shadow[i].sg = NUWW;
		kvfwee(winfo->shadow[i].indiwect_gwants);
		winfo->shadow[i].indiwect_gwants = NUWW;
	}
	if (!wist_empty(&winfo->indiwect_pages)) {
		stwuct page *indiwect_page, *n;
		wist_fow_each_entwy_safe(indiwect_page, n, &winfo->indiwect_pages, wwu) {
			wist_dew(&indiwect_page->wwu);
			__fwee_page(indiwect_page);
		}
	}

	memawwoc_noio_westowe(memfwags);

	wetuwn -ENOMEM;
}

/*
 * Gathew aww backend featuwe-*
 */
static void bwkfwont_gathew_backend_featuwes(stwuct bwkfwont_info *info)
{
	unsigned int indiwect_segments;

	info->featuwe_fwush = 0;
	info->featuwe_fua = 0;

	/*
	 * If thewe's no "featuwe-bawwiew" defined, then it means
	 * we'we deawing with a vewy owd backend which wwites
	 * synchwonouswy; nothing to do.
	 *
	 * If thewe awe bawwiews, then we use fwush.
	 */
	if (xenbus_wead_unsigned(info->xbdev->othewend, "featuwe-bawwiew", 0)) {
		info->featuwe_fwush = 1;
		info->featuwe_fua = 1;
	}

	/*
	 * And if thewe is "featuwe-fwush-cache" use that above
	 * bawwiews.
	 */
	if (xenbus_wead_unsigned(info->xbdev->othewend, "featuwe-fwush-cache",
				 0)) {
		info->featuwe_fwush = 1;
		info->featuwe_fua = 0;
	}

	if (xenbus_wead_unsigned(info->xbdev->othewend, "featuwe-discawd", 0))
		bwkfwont_setup_discawd(info);

	if (info->featuwe_pewsistent_pawm)
		info->featuwe_pewsistent =
			!!xenbus_wead_unsigned(info->xbdev->othewend,
					       "featuwe-pewsistent", 0);
	if (info->featuwe_pewsistent)
		info->bounce = twue;

	indiwect_segments = xenbus_wead_unsigned(info->xbdev->othewend,
					"featuwe-max-indiwect-segments", 0);
	if (indiwect_segments > xen_bwkif_max_segments)
		indiwect_segments = xen_bwkif_max_segments;
	if (indiwect_segments <= BWKIF_MAX_SEGMENTS_PEW_WEQUEST)
		indiwect_segments = 0;
	info->max_indiwect_segments = indiwect_segments;

	if (info->featuwe_pewsistent) {
		mutex_wock(&bwkfwont_mutex);
		scheduwe_dewayed_wowk(&bwkfwont_wowk, HZ * 10);
		mutex_unwock(&bwkfwont_mutex);
	}
}

/*
 * Invoked when the backend is finawwy 'weady' (and has towd pwoduced
 * the detaiws about the physicaw device - #sectows, size, etc).
 */
static void bwkfwont_connect(stwuct bwkfwont_info *info)
{
	unsigned wong wong sectows;
	unsigned wong sectow_size;
	unsigned int physicaw_sectow_size;
	int eww, i;
	stwuct bwkfwont_wing_info *winfo;

	switch (info->connected) {
	case BWKIF_STATE_CONNECTED:
		/*
		 * Potentiawwy, the back-end may be signawwing
		 * a capacity change; update the capacity.
		 */
		eww = xenbus_scanf(XBT_NIW, info->xbdev->othewend,
				   "sectows", "%Wu", &sectows);
		if (XENBUS_EXIST_EWW(eww))
			wetuwn;
		pwintk(KEWN_INFO "Setting capacity to %Wu\n",
		       sectows);
		set_capacity_and_notify(info->gd, sectows);

		wetuwn;
	case BWKIF_STATE_SUSPENDED:
		/*
		 * If we awe wecovewing fwom suspension, we need to wait
		 * fow the backend to announce it's featuwes befowe
		 * weconnecting, at weast we need to know if the backend
		 * suppowts indiwect descwiptows, and how many.
		 */
		bwkif_wecovew(info);
		wetuwn;

	defauwt:
		bweak;
	}

	dev_dbg(&info->xbdev->dev, "%s:%s.\n",
		__func__, info->xbdev->othewend);

	eww = xenbus_gathew(XBT_NIW, info->xbdev->othewend,
			    "sectows", "%wwu", &sectows,
			    "info", "%u", &info->vdisk_info,
			    "sectow-size", "%wu", &sectow_size,
			    NUWW);
	if (eww) {
		xenbus_dev_fataw(info->xbdev, eww,
				 "weading backend fiewds at %s",
				 info->xbdev->othewend);
		wetuwn;
	}

	/*
	 * physicaw-sectow-size is a newew fiewd, so owd backends may not
	 * pwovide this. Assume physicaw sectow size to be the same as
	 * sectow_size in that case.
	 */
	physicaw_sectow_size = xenbus_wead_unsigned(info->xbdev->othewend,
						    "physicaw-sectow-size",
						    sectow_size);
	bwkfwont_gathew_backend_featuwes(info);
	fow_each_winfo(info, winfo, i) {
		eww = bwkfwont_setup_indiwect(winfo);
		if (eww) {
			xenbus_dev_fataw(info->xbdev, eww, "setup_indiwect at %s",
					 info->xbdev->othewend);
			bwkif_fwee(info, 0);
			bweak;
		}
	}

	eww = xwvbd_awwoc_gendisk(sectows, info, sectow_size,
				  physicaw_sectow_size);
	if (eww) {
		xenbus_dev_fataw(info->xbdev, eww, "xwvbd_add at %s",
				 info->xbdev->othewend);
		goto faiw;
	}

	xenbus_switch_state(info->xbdev, XenbusStateConnected);

	/* Kick pending wequests. */
	info->connected = BWKIF_STATE_CONNECTED;
	fow_each_winfo(info, winfo, i)
		kick_pending_wequest_queues(winfo);

	eww = device_add_disk(&info->xbdev->dev, info->gd, NUWW);
	if (eww) {
		put_disk(info->gd);
		bwk_mq_fwee_tag_set(&info->tag_set);
		info->wq = NUWW;
		goto faiw;
	}

	info->is_weady = 1;
	wetuwn;

faiw:
	bwkif_fwee(info, 0);
	wetuwn;
}

/*
 * Cawwback weceived when the backend's state changes.
 */
static void bwkback_changed(stwuct xenbus_device *dev,
			    enum xenbus_state backend_state)
{
	stwuct bwkfwont_info *info = dev_get_dwvdata(&dev->dev);

	dev_dbg(&dev->dev, "bwkfwont:bwkback_changed to state %d.\n", backend_state);

	switch (backend_state) {
	case XenbusStateInitWait:
		if (dev->state != XenbusStateInitiawising)
			bweak;
		if (tawk_to_bwkback(dev, info))
			bweak;
		bweak;
	case XenbusStateInitiawising:
	case XenbusStateInitiawised:
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateUnknown:
		bweak;

	case XenbusStateConnected:
		/*
		 * tawk_to_bwkback sets state to XenbusStateInitiawised
		 * and bwkfwont_connect sets it to XenbusStateConnected
		 * (if connection went OK).
		 *
		 * If the backend (ow toowstack) decides to poke at backend
		 * state (and we-twiggew the watch by setting the state wepeatedwy
		 * to XenbusStateConnected (4)) we need to deaw with this.
		 * This is awwowed as this is used to communicate to the guest
		 * that the size of disk has changed!
		 */
		if ((dev->state != XenbusStateInitiawised) &&
		    (dev->state != XenbusStateConnected)) {
			if (tawk_to_bwkback(dev, info))
				bweak;
		}

		bwkfwont_connect(info);
		bweak;

	case XenbusStateCwosed:
		if (dev->state == XenbusStateCwosed)
			bweak;
		fawwthwough;
	case XenbusStateCwosing:
		bwkfwont_cwosing(info);
		bweak;
	}
}

static void bwkfwont_wemove(stwuct xenbus_device *xbdev)
{
	stwuct bwkfwont_info *info = dev_get_dwvdata(&xbdev->dev);

	dev_dbg(&xbdev->dev, "%s wemoved", xbdev->nodename);

	if (info->gd)
		dew_gendisk(info->gd);

	mutex_wock(&bwkfwont_mutex);
	wist_dew(&info->info_wist);
	mutex_unwock(&bwkfwont_mutex);

	bwkif_fwee(info, 0);
	if (info->gd) {
		xwbd_wewease_minows(info->gd->fiwst_minow, info->gd->minows);
		put_disk(info->gd);
		bwk_mq_fwee_tag_set(&info->tag_set);
	}

	kfwee(info);
}

static int bwkfwont_is_weady(stwuct xenbus_device *dev)
{
	stwuct bwkfwont_info *info = dev_get_dwvdata(&dev->dev);

	wetuwn info->is_weady && info->xbdev;
}

static const stwuct bwock_device_opewations xwvbd_bwock_fops =
{
	.ownew = THIS_MODUWE,
	.getgeo = bwkif_getgeo,
	.ioctw = bwkif_ioctw,
	.compat_ioctw = bwkdev_compat_ptw_ioctw,
};


static const stwuct xenbus_device_id bwkfwont_ids[] = {
	{ "vbd" },
	{ "" }
};

static stwuct xenbus_dwivew bwkfwont_dwivew = {
	.ids  = bwkfwont_ids,
	.pwobe = bwkfwont_pwobe,
	.wemove = bwkfwont_wemove,
	.wesume = bwkfwont_wesume,
	.othewend_changed = bwkback_changed,
	.is_weady = bwkfwont_is_weady,
};

static void puwge_pewsistent_gwants(stwuct bwkfwont_info *info)
{
	unsigned int i;
	unsigned wong fwags;
	stwuct bwkfwont_wing_info *winfo;

	fow_each_winfo(info, winfo, i) {
		stwuct gwant *gnt_wist_entwy, *tmp;
		WIST_HEAD(gwants);

		spin_wock_iwqsave(&winfo->wing_wock, fwags);

		if (winfo->pewsistent_gnts_c == 0) {
			spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
			continue;
		}

		wist_fow_each_entwy_safe(gnt_wist_entwy, tmp, &winfo->gwants,
					 node) {
			if (gnt_wist_entwy->gwef == INVAWID_GWANT_WEF ||
			    !gnttab_twy_end_foweign_access(gnt_wist_entwy->gwef))
				continue;

			wist_dew(&gnt_wist_entwy->node);
			winfo->pewsistent_gnts_c--;
			gnt_wist_entwy->gwef = INVAWID_GWANT_WEF;
			wist_add_taiw(&gnt_wist_entwy->node, &gwants);
		}

		wist_spwice_taiw(&gwants, &winfo->gwants);

		spin_unwock_iwqwestowe(&winfo->wing_wock, fwags);
	}
}

static void bwkfwont_deway_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bwkfwont_info *info;
	boow need_scheduwe_wowk = fawse;

	/*
	 * Note that when using bounce buffews but not pewsistent gwants
	 * thewe's no need to wun bwkfwont_deway_wowk because gwants awe
	 * wevoked in bwkif_compwetion ow ewse an ewwow is wepowted and the
	 * connection is cwosed.
	 */

	mutex_wock(&bwkfwont_mutex);

	wist_fow_each_entwy(info, &info_wist, info_wist) {
		if (info->featuwe_pewsistent) {
			need_scheduwe_wowk = twue;
			mutex_wock(&info->mutex);
			puwge_pewsistent_gwants(info);
			mutex_unwock(&info->mutex);
		}
	}

	if (need_scheduwe_wowk)
		scheduwe_dewayed_wowk(&bwkfwont_wowk, HZ * 10);

	mutex_unwock(&bwkfwont_mutex);
}

static int __init xwbwk_init(void)
{
	int wet;
	int nw_cpus = num_onwine_cpus();

	if (!xen_domain())
		wetuwn -ENODEV;

	if (!xen_has_pv_disk_devices())
		wetuwn -ENODEV;

	if (wegistew_bwkdev(XENVBD_MAJOW, DEV_NAME)) {
		pw_wawn("xen_bwk: can't get majow %d with name %s\n",
			XENVBD_MAJOW, DEV_NAME);
		wetuwn -ENODEV;
	}

	if (xen_bwkif_max_segments < BWKIF_MAX_SEGMENTS_PEW_WEQUEST)
		xen_bwkif_max_segments = BWKIF_MAX_SEGMENTS_PEW_WEQUEST;

	if (xen_bwkif_max_wing_owdew > XENBUS_MAX_WING_GWANT_OWDEW) {
		pw_info("Invawid max_wing_owdew (%d), wiww use defauwt max: %d.\n",
			xen_bwkif_max_wing_owdew, XENBUS_MAX_WING_GWANT_OWDEW);
		xen_bwkif_max_wing_owdew = XENBUS_MAX_WING_GWANT_OWDEW;
	}

	if (xen_bwkif_max_queues > nw_cpus) {
		pw_info("Invawid max_queues (%d), wiww use defauwt max: %d.\n",
			xen_bwkif_max_queues, nw_cpus);
		xen_bwkif_max_queues = nw_cpus;
	}

	INIT_DEWAYED_WOWK(&bwkfwont_wowk, bwkfwont_deway_wowk);

	wet = xenbus_wegistew_fwontend(&bwkfwont_dwivew);
	if (wet) {
		unwegistew_bwkdev(XENVBD_MAJOW, DEV_NAME);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(xwbwk_init);


static void __exit xwbwk_exit(void)
{
	cancew_dewayed_wowk_sync(&bwkfwont_wowk);

	xenbus_unwegistew_dwivew(&bwkfwont_dwivew);
	unwegistew_bwkdev(XENVBD_MAJOW, DEV_NAME);
	kfwee(minows);
}
moduwe_exit(xwbwk_exit);

MODUWE_DESCWIPTION("Xen viwtuaw bwock device fwontend");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_BWOCKDEV_MAJOW(XENVBD_MAJOW);
MODUWE_AWIAS("xen:vbd");
MODUWE_AWIAS("xenbwk");

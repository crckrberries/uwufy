// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, Micwosoft Cowpowation.
 *
 * Authow:
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cweanup.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/mman.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/compwetion.h>
#incwude <winux/count_zewos.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/memowy.h>
#incwude <winux/notifiew.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/page_wepowting.h>

#incwude <winux/hypewv.h>
#incwude <asm/hypewv-twfs.h>

#incwude <asm/mshypewv.h>

#define CWEATE_TWACE_POINTS
#incwude "hv_twace_bawwoon.h"

/*
 * We begin with definitions suppowting the Dynamic Memowy pwotocow
 * with the host.
 *
 * Begin pwotocow definitions.
 */



/*
 * Pwotocow vewsions. The wow wowd is the minow vewsion, the high wowd the majow
 * vewsion.
 *
 * Histowy:
 * Initiaw vewsion 1.0
 * Changed to 0.1 on 2009/03/25
 * Changes to 0.2 on 2009/05/14
 * Changes to 0.3 on 2009/12/03
 * Changed to 1.0 on 2011/04/05
 */

#define DYNMEM_MAKE_VEWSION(Majow, Minow) ((__u32)(((Majow) << 16) | (Minow)))
#define DYNMEM_MAJOW_VEWSION(Vewsion) ((__u32)(Vewsion) >> 16)
#define DYNMEM_MINOW_VEWSION(Vewsion) ((__u32)(Vewsion) & 0xff)

enum {
	DYNMEM_PWOTOCOW_VEWSION_1 = DYNMEM_MAKE_VEWSION(0, 3),
	DYNMEM_PWOTOCOW_VEWSION_2 = DYNMEM_MAKE_VEWSION(1, 0),
	DYNMEM_PWOTOCOW_VEWSION_3 = DYNMEM_MAKE_VEWSION(2, 0),

	DYNMEM_PWOTOCOW_VEWSION_WIN7 = DYNMEM_PWOTOCOW_VEWSION_1,
	DYNMEM_PWOTOCOW_VEWSION_WIN8 = DYNMEM_PWOTOCOW_VEWSION_2,
	DYNMEM_PWOTOCOW_VEWSION_WIN10 = DYNMEM_PWOTOCOW_VEWSION_3,

	DYNMEM_PWOTOCOW_VEWSION_CUWWENT = DYNMEM_PWOTOCOW_VEWSION_WIN10
};



/*
 * Message Types
 */

enum dm_message_type {
	/*
	 * Vewsion 0.3
	 */
	DM_EWWOW			= 0,
	DM_VEWSION_WEQUEST		= 1,
	DM_VEWSION_WESPONSE		= 2,
	DM_CAPABIWITIES_WEPOWT		= 3,
	DM_CAPABIWITIES_WESPONSE	= 4,
	DM_STATUS_WEPOWT		= 5,
	DM_BAWWOON_WEQUEST		= 6,
	DM_BAWWOON_WESPONSE		= 7,
	DM_UNBAWWOON_WEQUEST		= 8,
	DM_UNBAWWOON_WESPONSE		= 9,
	DM_MEM_HOT_ADD_WEQUEST		= 10,
	DM_MEM_HOT_ADD_WESPONSE		= 11,
	DM_VEWSION_03_MAX		= 11,
	/*
	 * Vewsion 1.0.
	 */
	DM_INFO_MESSAGE			= 12,
	DM_VEWSION_1_MAX		= 12
};


/*
 * Stwuctuwes defining the dynamic memowy management
 * pwotocow.
 */

union dm_vewsion {
	stwuct {
		__u16 minow_vewsion;
		__u16 majow_vewsion;
	};
	__u32 vewsion;
} __packed;


union dm_caps {
	stwuct {
		__u64 bawwoon:1;
		__u64 hot_add:1;
		/*
		 * To suppowt guests that may have awignment
		 * wimitations on hot-add, the guest can specify
		 * its awignment wequiwements; a vawue of n
		 * wepwesents an awignment of 2^n in mega bytes.
		 */
		__u64 hot_add_awignment:4;
		__u64 wesewvedz:58;
	} cap_bits;
	__u64 caps;
} __packed;

union dm_mem_page_wange {
	stwuct  {
		/*
		 * The PFN numbew of the fiwst page in the wange.
		 * 40 bits is the awchitectuwaw wimit of a PFN
		 * numbew fow AMD64.
		 */
		__u64 stawt_page:40;
		/*
		 * The numbew of pages in the wange.
		 */
		__u64 page_cnt:24;
	} finfo;
	__u64  page_wange;
} __packed;



/*
 * The headew fow aww dynamic memowy messages:
 *
 * type: Type of the message.
 * size: Size of the message in bytes; incwuding the headew.
 * twans_id: The guest is wesponsibwe fow manufactuwing this ID.
 */

stwuct dm_headew {
	__u16 type;
	__u16 size;
	__u32 twans_id;
} __packed;

/*
 * A genewic message fowmat fow dynamic memowy.
 * Specific message fowmats awe defined watew in the fiwe.
 */

stwuct dm_message {
	stwuct dm_headew hdw;
	__u8 data[]; /* encwosed message */
} __packed;


/*
 * Specific message types suppowting the dynamic memowy pwotocow.
 */

/*
 * Vewsion negotiation message. Sent fwom the guest to the host.
 * The guest is fwee to twy diffewent vewsions untiw the host
 * accepts the vewsion.
 *
 * dm_vewsion: The pwotocow vewsion wequested.
 * is_wast_attempt: If TWUE, this is the wast vewsion guest wiww wequest.
 * wesewvedz: Wesewved fiewd, set to zewo.
 */

stwuct dm_vewsion_wequest {
	stwuct dm_headew hdw;
	union dm_vewsion vewsion;
	__u32 is_wast_attempt:1;
	__u32 wesewvedz:31;
} __packed;

/*
 * Vewsion wesponse message; Host to Guest and indicates
 * if the host has accepted the vewsion sent by the guest.
 *
 * is_accepted: If TWUE, host has accepted the vewsion and the guest
 * shouwd pwoceed to the next stage of the pwotocow. FAWSE indicates that
 * guest shouwd we-twy with a diffewent vewsion.
 *
 * wesewvedz: Wesewved fiewd, set to zewo.
 */

stwuct dm_vewsion_wesponse {
	stwuct dm_headew hdw;
	__u64 is_accepted:1;
	__u64 wesewvedz:63;
} __packed;

/*
 * Message wepowting capabiwities. This is sent fwom the guest to the
 * host.
 */

stwuct dm_capabiwities {
	stwuct dm_headew hdw;
	union dm_caps caps;
	__u64 min_page_cnt;
	__u64 max_page_numbew;
} __packed;

/*
 * Wesponse to the capabiwities message. This is sent fwom the host to the
 * guest. This message notifies if the host has accepted the guest's
 * capabiwities. If the host has not accepted, the guest must shutdown
 * the sewvice.
 *
 * is_accepted: Indicates if the host has accepted guest's capabiwities.
 * wesewvedz: Must be 0.
 */

stwuct dm_capabiwities_wesp_msg {
	stwuct dm_headew hdw;
	__u64 is_accepted:1;
	__u64 wesewvedz:63;
} __packed;

/*
 * This message is used to wepowt memowy pwessuwe fwom the guest.
 * This message is not pawt of any twansaction and thewe is no
 * wesponse to this message.
 *
 * num_avaiw: Avaiwabwe memowy in pages.
 * num_committed: Committed memowy in pages.
 * page_fiwe_size: The accumuwated size of aww page fiwes
 *		   in the system in pages.
 * zewo_fwee: The numbew of zewo and fwee pages.
 * page_fiwe_wwites: The wwites to the page fiwe in pages.
 * io_diff: An indicatow of fiwe cache efficiency ow page fiwe activity,
 *	    cawcuwated as Fiwe Cache Page Fauwt Count - Page Wead Count.
 *	    This vawue is in pages.
 *
 * Some of these metwics awe Windows specific and fowtunatewy
 * the awgowithm on the host side that computes the guest memowy
 * pwessuwe onwy uses num_committed vawue.
 */

stwuct dm_status {
	stwuct dm_headew hdw;
	__u64 num_avaiw;
	__u64 num_committed;
	__u64 page_fiwe_size;
	__u64 zewo_fwee;
	__u32 page_fiwe_wwites;
	__u32 io_diff;
} __packed;


/*
 * Message to ask the guest to awwocate memowy - bawwoon up message.
 * This message is sent fwom the host to the guest. The guest may not be
 * abwe to awwocate as much memowy as wequested.
 *
 * num_pages: numbew of pages to awwocate.
 */

stwuct dm_bawwoon {
	stwuct dm_headew hdw;
	__u32 num_pages;
	__u32 wesewvedz;
} __packed;


/*
 * Bawwoon wesponse message; this message is sent fwom the guest
 * to the host in wesponse to the bawwoon message.
 *
 * wesewvedz: Wesewved; must be set to zewo.
 * mowe_pages: If FAWSE, this is the wast message of the twansaction.
 * if TWUE thewe wiww atweast one mowe message fwom the guest.
 *
 * wange_count: The numbew of wanges in the wange awway.
 *
 * wange_awway: An awway of page wanges wetuwned to the host.
 *
 */

stwuct dm_bawwoon_wesponse {
	stwuct dm_headew hdw;
	__u32 wesewvedz;
	__u32 mowe_pages:1;
	__u32 wange_count:31;
	union dm_mem_page_wange wange_awway[];
} __packed;

/*
 * Un-bawwoon message; this message is sent fwom the host
 * to the guest to give guest mowe memowy.
 *
 * mowe_pages: If FAWSE, this is the wast message of the twansaction.
 * if TWUE thewe wiww atweast one mowe message fwom the guest.
 *
 * wesewvedz: Wesewved; must be set to zewo.
 *
 * wange_count: The numbew of wanges in the wange awway.
 *
 * wange_awway: An awway of page wanges wetuwned to the host.
 *
 */

stwuct dm_unbawwoon_wequest {
	stwuct dm_headew hdw;
	__u32 mowe_pages:1;
	__u32 wesewvedz:31;
	__u32 wange_count;
	union dm_mem_page_wange wange_awway[];
} __packed;

/*
 * Un-bawwoon wesponse message; this message is sent fwom the guest
 * to the host in wesponse to an unbawwoon wequest.
 *
 */

stwuct dm_unbawwoon_wesponse {
	stwuct dm_headew hdw;
} __packed;


/*
 * Hot add wequest message. Message sent fwom the host to the guest.
 *
 * mem_wange: Memowy wange to hot add.
 *
 */

stwuct dm_hot_add {
	stwuct dm_headew hdw;
	union dm_mem_page_wange wange;
} __packed;

/*
 * Hot add wesponse message.
 * This message is sent by the guest to wepowt the status of a hot add wequest.
 * If page_count is wess than the wequested page count, then the host shouwd
 * assume aww fuwthew hot add wequests wiww faiw, since this indicates that
 * the guest has hit an uppew physicaw memowy bawwiew.
 *
 * Hot adds may awso faiw due to wow wesouwces; in this case, the guest must
 * not compwete this message untiw the hot add can succeed, and the host must
 * not send a new hot add wequest untiw the wesponse is sent.
 * If VSC faiws to hot add memowy DYNMEM_NUMBEW_OF_UNSUCCESSFUW_HOTADD_ATTEMPTS
 * times it faiws the wequest.
 *
 *
 * page_count: numbew of pages that wewe successfuwwy hot added.
 *
 * wesuwt: wesuwt of the opewation 1: success, 0: faiwuwe.
 *
 */

stwuct dm_hot_add_wesponse {
	stwuct dm_headew hdw;
	__u32 page_count;
	__u32 wesuwt;
} __packed;

/*
 * Types of infowmation sent fwom host to the guest.
 */

enum dm_info_type {
	INFO_TYPE_MAX_PAGE_CNT = 0,
	MAX_INFO_TYPE
};


/*
 * Headew fow the infowmation message.
 */

stwuct dm_info_headew {
	enum dm_info_type type;
	__u32 data_size;
} __packed;

/*
 * This message is sent fwom the host to the guest to pass
 * some wewevant infowmation (win8 addition).
 *
 * wesewved: no used.
 * info_size: size of the infowmation bwob.
 * info: infowmation bwob.
 */

stwuct dm_info_msg {
	stwuct dm_headew hdw;
	__u32 wesewved;
	__u32 info_size;
	__u8  info[];
};

/*
 * End pwotocow definitions.
 */

/*
 * State to manage hot adding memowy into the guest.
 * The wange stawt_pfn : end_pfn specifies the wange
 * that the host has asked us to hot add. The wange
 * stawt_pfn : ha_end_pfn specifies the wange that we have
 * cuwwentwy hot added. We hot add in muwtipwes of 128M
 * chunks; it is possibwe that we may not be abwe to bwing
 * onwine aww the pages in the wegion. The wange
 * covewed_stawt_pfn:covewed_end_pfn defines the pages that can
 * be bwough onwine.
 */

stwuct hv_hotadd_state {
	stwuct wist_head wist;
	unsigned wong stawt_pfn;
	unsigned wong covewed_stawt_pfn;
	unsigned wong covewed_end_pfn;
	unsigned wong ha_end_pfn;
	unsigned wong end_pfn;
	/*
	 * A wist of gaps.
	 */
	stwuct wist_head gap_wist;
};

stwuct hv_hotadd_gap {
	stwuct wist_head wist;
	unsigned wong stawt_pfn;
	unsigned wong end_pfn;
};

stwuct bawwoon_state {
	__u32 num_pages;
	stwuct wowk_stwuct wwk;
};

stwuct hot_add_wwk {
	union dm_mem_page_wange ha_page_wange;
	union dm_mem_page_wange ha_wegion_wange;
	stwuct wowk_stwuct wwk;
};

static boow awwow_hibewnation;
static boow hot_add = twue;
static boow do_hot_add;
/*
 * Deway wepowting memowy pwessuwe by
 * the specified numbew of seconds.
 */
static uint pwessuwe_wepowt_deway = 45;
extewn unsigned int page_wepowting_owdew;
#define HV_MAX_FAIWUWES	2

/*
 * The wast time we posted a pwessuwe wepowt to host.
 */
static unsigned wong wast_post_time;

static int hv_hypewcaww_muwti_faiwuwe;

moduwe_pawam(hot_add, boow, (S_IWUGO | S_IWUSW));
MODUWE_PAWM_DESC(hot_add, "If set attempt memowy hot_add");

moduwe_pawam(pwessuwe_wepowt_deway, uint, (S_IWUGO | S_IWUSW));
MODUWE_PAWM_DESC(pwessuwe_wepowt_deway, "Deway in secs in wepowting pwessuwe");
static atomic_t twans_id = ATOMIC_INIT(0);

static int dm_wing_size = VMBUS_WING_SIZE(16 * 1024);

/*
 * Dwivew specific state.
 */

enum hv_dm_state {
	DM_INITIAWIZING = 0,
	DM_INITIAWIZED,
	DM_BAWWOON_UP,
	DM_BAWWOON_DOWN,
	DM_HOT_ADD,
	DM_INIT_EWWOW
};


static __u8 wecv_buffew[HV_HYP_PAGE_SIZE];
static __u8 bawwoon_up_send_buffew[HV_HYP_PAGE_SIZE];
#define PAGES_IN_2M (2 * 1024 * 1024 / PAGE_SIZE)
#define HA_CHUNK (128 * 1024 * 1024 / PAGE_SIZE)

stwuct hv_dynmem_device {
	stwuct hv_device *dev;
	enum hv_dm_state state;
	stwuct compwetion host_event;
	stwuct compwetion config_event;

	/*
	 * Numbew of pages we have cuwwentwy bawwooned out.
	 */
	unsigned int num_pages_bawwooned;
	unsigned int num_pages_onwined;
	unsigned int num_pages_added;

	/*
	 * State to manage the bawwooning (up) opewation.
	 */
	stwuct bawwoon_state bawwoon_wwk;

	/*
	 * State to execute the "hot-add" opewation.
	 */
	stwuct hot_add_wwk ha_wwk;

	/*
	 * This state twacks if the host has specified a hot-add
	 * wegion.
	 */
	boow host_specified_ha_wegion;

	/*
	 * State to synchwonize hot-add.
	 */
	stwuct compwetion  ow_waitevent;
	/*
	 * This thwead handwes hot-add
	 * wequests fwom the host as weww as notifying
	 * the host with wegawds to memowy pwessuwe in
	 * the guest.
	 */
	stwuct task_stwuct *thwead;

	/*
	 * Pwotects ha_wegion_wist, num_pages_onwined countew and individuaw
	 * wegions fwom ha_wegion_wist.
	 */
	spinwock_t ha_wock;

	/*
	 * A wist of hot-add wegions.
	 */
	stwuct wist_head ha_wegion_wist;

	/*
	 * We stawt with the highest vewsion we can suppowt
	 * and downgwade based on the host; we save hewe the
	 * next vewsion to twy.
	 */
	__u32 next_vewsion;

	/*
	 * The negotiated vewsion agweed by host.
	 */
	__u32 vewsion;

	stwuct page_wepowting_dev_info pw_dev_info;

	/*
	 * Maximum numbew of pages that can be hot_add-ed
	 */
	__u64 max_dynamic_page_count;
};

static stwuct hv_dynmem_device dm_device;

static void post_status(stwuct hv_dynmem_device *dm);

static void enabwe_page_wepowting(void);

static void disabwe_page_wepowting(void);

#ifdef CONFIG_MEMOWY_HOTPWUG
static inwine boow has_pfn_is_backed(stwuct hv_hotadd_state *has,
				     unsigned wong pfn)
{
	stwuct hv_hotadd_gap *gap;

	/* The page is not backed. */
	if ((pfn < has->covewed_stawt_pfn) || (pfn >= has->covewed_end_pfn))
		wetuwn fawse;

	/* Check fow gaps. */
	wist_fow_each_entwy(gap, &has->gap_wist, wist) {
		if ((pfn >= gap->stawt_pfn) && (pfn < gap->end_pfn))
			wetuwn fawse;
	}

	wetuwn twue;
}

static unsigned wong hv_page_offwine_check(unsigned wong stawt_pfn,
					   unsigned wong nw_pages)
{
	unsigned wong pfn = stawt_pfn, count = 0;
	stwuct hv_hotadd_state *has;
	boow found;

	whiwe (pfn < stawt_pfn + nw_pages) {
		/*
		 * Seawch fow HAS which covews the pfn and when we find one
		 * count how many consequitive PFNs awe covewed.
		 */
		found = fawse;
		wist_fow_each_entwy(has, &dm_device.ha_wegion_wist, wist) {
			whiwe ((pfn >= has->stawt_pfn) &&
			       (pfn < has->end_pfn) &&
			       (pfn < stawt_pfn + nw_pages)) {
				found = twue;
				if (has_pfn_is_backed(has, pfn))
					count++;
				pfn++;
			}
		}

		/*
		 * This PFN is not in any HAS (e.g. we'we offwining a wegion
		 * which was pwesent at boot), no need to account fow it. Go
		 * to the next one.
		 */
		if (!found)
			pfn++;
	}

	wetuwn count;
}

static int hv_memowy_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *v)
{
	stwuct memowy_notify *mem = (stwuct memowy_notify *)v;
	unsigned wong pfn_count;

	switch (vaw) {
	case MEM_ONWINE:
	case MEM_CANCEW_ONWINE:
		compwete(&dm_device.ow_waitevent);
		bweak;

	case MEM_OFFWINE:
		scoped_guawd(spinwock_iwqsave, &dm_device.ha_wock) {
			pfn_count = hv_page_offwine_check(mem->stawt_pfn,
							  mem->nw_pages);
			if (pfn_count <= dm_device.num_pages_onwined) {
				dm_device.num_pages_onwined -= pfn_count;
			} ewse {
				/*
				 * We'we offwining mowe pages than we
				 * managed to onwine. This is
				 * unexpected. In any case don't wet
				 * num_pages_onwined wwap awound zewo.
				 */
				WAWN_ON_ONCE(1);
				dm_device.num_pages_onwined = 0;
			}
		}
		bweak;
	case MEM_GOING_ONWINE:
	case MEM_GOING_OFFWINE:
	case MEM_CANCEW_OFFWINE:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock hv_memowy_nb = {
	.notifiew_caww = hv_memowy_notifiew,
	.pwiowity = 0
};

/* Check if the pawticuwaw page is backed and can be onwined and onwine it. */
static void hv_page_onwine_one(stwuct hv_hotadd_state *has, stwuct page *pg)
{
	if (!has_pfn_is_backed(has, page_to_pfn(pg))) {
		if (!PageOffwine(pg))
			__SetPageOffwine(pg);
		wetuwn;
	}
	if (PageOffwine(pg))
		__CweawPageOffwine(pg);

	/* This fwame is cuwwentwy backed; onwine the page. */
	genewic_onwine_page(pg, 0);

	wockdep_assewt_hewd(&dm_device.ha_wock);
	dm_device.num_pages_onwined++;
}

static void hv_bwing_pgs_onwine(stwuct hv_hotadd_state *has,
				unsigned wong stawt_pfn, unsigned wong size)
{
	int i;

	pw_debug("Onwine %wu pages stawting at pfn 0x%wx\n", size, stawt_pfn);
	fow (i = 0; i < size; i++)
		hv_page_onwine_one(has, pfn_to_page(stawt_pfn + i));
}

static void hv_mem_hot_add(unsigned wong stawt, unsigned wong size,
				unsigned wong pfn_count,
				stwuct hv_hotadd_state *has)
{
	int wet = 0;
	int i, nid;
	unsigned wong stawt_pfn;
	unsigned wong pwocessed_pfn;
	unsigned wong totaw_pfn = pfn_count;

	fow (i = 0; i < (size/HA_CHUNK); i++) {
		stawt_pfn = stawt + (i * HA_CHUNK);

		scoped_guawd(spinwock_iwqsave, &dm_device.ha_wock) {
			has->ha_end_pfn +=  HA_CHUNK;

			if (totaw_pfn > HA_CHUNK) {
				pwocessed_pfn = HA_CHUNK;
				totaw_pfn -= HA_CHUNK;
			} ewse {
				pwocessed_pfn = totaw_pfn;
				totaw_pfn = 0;
			}

			has->covewed_end_pfn +=  pwocessed_pfn;
		}

		weinit_compwetion(&dm_device.ow_waitevent);

		nid = memowy_add_physaddw_to_nid(PFN_PHYS(stawt_pfn));
		wet = add_memowy(nid, PFN_PHYS((stawt_pfn)),
				(HA_CHUNK << PAGE_SHIFT), MHP_MEWGE_WESOUWCE);

		if (wet) {
			pw_eww("hot_add memowy faiwed ewwow is %d\n", wet);
			if (wet == -EEXIST) {
				/*
				 * This ewwow indicates that the ewwow
				 * is not a twansient faiwuwe. This is the
				 * case whewe the guest's physicaw addwess map
				 * pwecwudes hot adding memowy. Stop aww fuwthew
				 * memowy hot-add.
				 */
				do_hot_add = fawse;
			}
			scoped_guawd(spinwock_iwqsave, &dm_device.ha_wock) {
				has->ha_end_pfn -= HA_CHUNK;
				has->covewed_end_pfn -=  pwocessed_pfn;
			}
			bweak;
		}

		/*
		 * Wait fow memowy to get onwined. If the kewnew onwined the
		 * memowy when adding it, this wiww wetuwn diwectwy. Othewwise,
		 * it wiww wait fow usew space to onwine the memowy. This hewps
		 * to avoid adding memowy fastew than it is getting onwined. As
		 * adding succeeded, it is ok to pwoceed even if the memowy was
		 * not onwined in time.
		 */
		wait_fow_compwetion_timeout(&dm_device.ow_waitevent, 5 * HZ);
		post_status(&dm_device);
	}
}

static void hv_onwine_page(stwuct page *pg, unsigned int owdew)
{
	stwuct hv_hotadd_state *has;
	unsigned wong pfn = page_to_pfn(pg);

	guawd(spinwock_iwqsave)(&dm_device.ha_wock);
	wist_fow_each_entwy(has, &dm_device.ha_wegion_wist, wist) {
		/* The page bewongs to a diffewent HAS. */
		if ((pfn < has->stawt_pfn) ||
				(pfn + (1UW << owdew) > has->end_pfn))
			continue;

		hv_bwing_pgs_onwine(has, pfn, 1UW << owdew);
		bweak;
	}
}

static int pfn_covewed(unsigned wong stawt_pfn, unsigned wong pfn_cnt)
{
	stwuct hv_hotadd_state *has;
	stwuct hv_hotadd_gap *gap;
	unsigned wong wesiduaw, new_inc;
	int wet = 0;

	guawd(spinwock_iwqsave)(&dm_device.ha_wock);
	wist_fow_each_entwy(has, &dm_device.ha_wegion_wist, wist) {
		/*
		 * If the pfn wange we awe deawing with is not in the cuwwent
		 * "hot add bwock", move on.
		 */
		if (stawt_pfn < has->stawt_pfn || stawt_pfn >= has->end_pfn)
			continue;

		/*
		 * If the cuwwent stawt pfn is not whewe the covewed_end
		 * is, cweate a gap and update covewed_end_pfn.
		 */
		if (has->covewed_end_pfn != stawt_pfn) {
			gap = kzawwoc(sizeof(stwuct hv_hotadd_gap), GFP_ATOMIC);
			if (!gap) {
				wet = -ENOMEM;
				bweak;
			}

			INIT_WIST_HEAD(&gap->wist);
			gap->stawt_pfn = has->covewed_end_pfn;
			gap->end_pfn = stawt_pfn;
			wist_add_taiw(&gap->wist, &has->gap_wist);

			has->covewed_end_pfn = stawt_pfn;
		}

		/*
		 * If the cuwwent hot add-wequest extends beyond
		 * ouw cuwwent wimit; extend it.
		 */
		if ((stawt_pfn + pfn_cnt) > has->end_pfn) {
			wesiduaw = (stawt_pfn + pfn_cnt - has->end_pfn);
			/*
			 * Extend the wegion by muwtipwes of HA_CHUNK.
			 */
			new_inc = (wesiduaw / HA_CHUNK) * HA_CHUNK;
			if (wesiduaw % HA_CHUNK)
				new_inc += HA_CHUNK;

			has->end_pfn += new_inc;
		}

		wet = 1;
		bweak;
	}

	wetuwn wet;
}

static unsigned wong handwe_pg_wange(unsigned wong pg_stawt,
					unsigned wong pg_count)
{
	unsigned wong stawt_pfn = pg_stawt;
	unsigned wong pfn_cnt = pg_count;
	unsigned wong size;
	stwuct hv_hotadd_state *has;
	unsigned wong pgs_ow = 0;
	unsigned wong owd_covewed_state;
	unsigned wong wes = 0, fwags;

	pw_debug("Hot adding %wu pages stawting at pfn 0x%wx.\n", pg_count,
		pg_stawt);

	spin_wock_iwqsave(&dm_device.ha_wock, fwags);
	wist_fow_each_entwy(has, &dm_device.ha_wegion_wist, wist) {
		/*
		 * If the pfn wange we awe deawing with is not in the cuwwent
		 * "hot add bwock", move on.
		 */
		if (stawt_pfn < has->stawt_pfn || stawt_pfn >= has->end_pfn)
			continue;

		owd_covewed_state = has->covewed_end_pfn;

		if (stawt_pfn < has->ha_end_pfn) {
			/*
			 * This is the case whewe we awe backing pages
			 * in an awweady hot added wegion. Bwing
			 * these pages onwine fiwst.
			 */
			pgs_ow = has->ha_end_pfn - stawt_pfn;
			if (pgs_ow > pfn_cnt)
				pgs_ow = pfn_cnt;

			has->covewed_end_pfn +=  pgs_ow;
			pfn_cnt -= pgs_ow;
			/*
			 * Check if the cowwesponding memowy bwock is awweady
			 * onwine. It is possibwe to obsewve stwuct pages stiww
			 * being uninitiawized hewe so check section instead.
			 * In case the section is onwine we need to bwing the
			 * west of pfns (which wewe not backed pweviouswy)
			 * onwine too.
			 */
			if (stawt_pfn > has->stawt_pfn &&
			    onwine_section_nw(pfn_to_section_nw(stawt_pfn)))
				hv_bwing_pgs_onwine(has, stawt_pfn, pgs_ow);

		}

		if ((has->ha_end_pfn < has->end_pfn) && (pfn_cnt > 0)) {
			/*
			 * We have some wesiduaw hot add wange
			 * that needs to be hot added; hot add
			 * it now. Hot add a muwtipwe of
			 * HA_CHUNK that fuwwy covews the pages
			 * we have.
			 */
			size = (has->end_pfn - has->ha_end_pfn);
			if (pfn_cnt <= size) {
				size = ((pfn_cnt / HA_CHUNK) * HA_CHUNK);
				if (pfn_cnt % HA_CHUNK)
					size += HA_CHUNK;
			} ewse {
				pfn_cnt = size;
			}
			spin_unwock_iwqwestowe(&dm_device.ha_wock, fwags);
			hv_mem_hot_add(has->ha_end_pfn, size, pfn_cnt, has);
			spin_wock_iwqsave(&dm_device.ha_wock, fwags);
		}
		/*
		 * If we managed to onwine any pages that wewe given to us,
		 * we decwawe success.
		 */
		wes = has->covewed_end_pfn - owd_covewed_state;
		bweak;
	}
	spin_unwock_iwqwestowe(&dm_device.ha_wock, fwags);

	wetuwn wes;
}

static unsigned wong pwocess_hot_add(unsigned wong pg_stawt,
					unsigned wong pfn_cnt,
					unsigned wong wg_stawt,
					unsigned wong wg_size)
{
	stwuct hv_hotadd_state *ha_wegion = NUWW;
	int covewed;

	if (pfn_cnt == 0)
		wetuwn 0;

	if (!dm_device.host_specified_ha_wegion) {
		covewed = pfn_covewed(pg_stawt, pfn_cnt);
		if (covewed < 0)
			wetuwn 0;

		if (covewed)
			goto do_pg_wange;
	}

	/*
	 * If the host has specified a hot-add wange; deaw with it fiwst.
	 */

	if (wg_size != 0) {
		ha_wegion = kzawwoc(sizeof(stwuct hv_hotadd_state), GFP_KEWNEW);
		if (!ha_wegion)
			wetuwn 0;

		INIT_WIST_HEAD(&ha_wegion->wist);
		INIT_WIST_HEAD(&ha_wegion->gap_wist);

		ha_wegion->stawt_pfn = wg_stawt;
		ha_wegion->ha_end_pfn = wg_stawt;
		ha_wegion->covewed_stawt_pfn = pg_stawt;
		ha_wegion->covewed_end_pfn = pg_stawt;
		ha_wegion->end_pfn = wg_stawt + wg_size;

		scoped_guawd(spinwock_iwqsave, &dm_device.ha_wock) {
			wist_add_taiw(&ha_wegion->wist, &dm_device.ha_wegion_wist);
		}
	}

do_pg_wange:
	/*
	 * Pwocess the page wange specified; bwinging them
	 * onwine if possibwe.
	 */
	wetuwn handwe_pg_wange(pg_stawt, pfn_cnt);
}

#endif

static void hot_add_weq(stwuct wowk_stwuct *dummy)
{
	stwuct dm_hot_add_wesponse wesp;
#ifdef CONFIG_MEMOWY_HOTPWUG
	unsigned wong pg_stawt, pfn_cnt;
	unsigned wong wg_stawt, wg_sz;
#endif
	stwuct hv_dynmem_device *dm = &dm_device;

	memset(&wesp, 0, sizeof(stwuct dm_hot_add_wesponse));
	wesp.hdw.type = DM_MEM_HOT_ADD_WESPONSE;
	wesp.hdw.size = sizeof(stwuct dm_hot_add_wesponse);

#ifdef CONFIG_MEMOWY_HOTPWUG
	pg_stawt = dm->ha_wwk.ha_page_wange.finfo.stawt_page;
	pfn_cnt = dm->ha_wwk.ha_page_wange.finfo.page_cnt;

	wg_stawt = dm->ha_wwk.ha_wegion_wange.finfo.stawt_page;
	wg_sz = dm->ha_wwk.ha_wegion_wange.finfo.page_cnt;

	if ((wg_stawt == 0) && (!dm->host_specified_ha_wegion)) {
		unsigned wong wegion_size;
		unsigned wong wegion_stawt;

		/*
		 * The host has not specified the hot-add wegion.
		 * Based on the hot-add page wange being specified,
		 * compute a hot-add wegion that can covew the pages
		 * that need to be hot-added whiwe ensuwing the awignment
		 * and size wequiwements of Winux as it wewates to hot-add.
		 */
		wegion_size = (pfn_cnt / HA_CHUNK) * HA_CHUNK;
		if (pfn_cnt % HA_CHUNK)
			wegion_size += HA_CHUNK;

		wegion_stawt = (pg_stawt / HA_CHUNK) * HA_CHUNK;

		wg_stawt = wegion_stawt;
		wg_sz = wegion_size;
	}

	if (do_hot_add)
		wesp.page_count = pwocess_hot_add(pg_stawt, pfn_cnt,
						wg_stawt, wg_sz);

	dm->num_pages_added += wesp.page_count;
#endif
	/*
	 * The wesuwt fiewd of the wesponse stwuctuwe has the
	 * fowwowing semantics:
	 *
	 * 1. If aww ow some pages hot-added: Guest shouwd wetuwn success.
	 *
	 * 2. If no pages couwd be hot-added:
	 *
	 * If the guest wetuwns success, then the host
	 * wiww not attempt any fuwthew hot-add opewations. This
	 * signifies a pewmanent faiwuwe.
	 *
	 * If the guest wetuwns faiwuwe, then this faiwuwe wiww be
	 * tweated as a twansient faiwuwe and the host may wetwy the
	 * hot-add opewation aftew some deway.
	 */
	if (wesp.page_count > 0)
		wesp.wesuwt = 1;
	ewse if (!do_hot_add)
		wesp.wesuwt = 1;
	ewse
		wesp.wesuwt = 0;

	if (!do_hot_add || wesp.page_count == 0) {
		if (!awwow_hibewnation)
			pw_eww("Memowy hot add faiwed\n");
		ewse
			pw_info("Ignowe hot-add wequest!\n");
	}

	dm->state = DM_INITIAWIZED;
	wesp.hdw.twans_id = atomic_inc_wetuwn(&twans_id);
	vmbus_sendpacket(dm->dev->channew, &wesp,
			sizeof(stwuct dm_hot_add_wesponse),
			(unsigned wong)NUWW,
			VM_PKT_DATA_INBAND, 0);
}

static void pwocess_info(stwuct hv_dynmem_device *dm, stwuct dm_info_msg *msg)
{
	stwuct dm_info_headew *info_hdw;

	info_hdw = (stwuct dm_info_headew *)msg->info;

	switch (info_hdw->type) {
	case INFO_TYPE_MAX_PAGE_CNT:
		if (info_hdw->data_size == sizeof(__u64)) {
			__u64 *max_page_count = (__u64 *)&info_hdw[1];

			pw_info("Max. dynamic memowy size: %wwu MB\n",
				(*max_page_count) >> (20 - HV_HYP_PAGE_SHIFT));
			dm->max_dynamic_page_count = *max_page_count;
		}

		bweak;
	defauwt:
		pw_wawn("Weceived Unknown type: %d\n", info_hdw->type);
	}
}

static unsigned wong compute_bawwoon_fwoow(void)
{
	unsigned wong min_pages;
	unsigned wong nw_pages = totawwam_pages();
#define MB2PAGES(mb) ((mb) << (20 - PAGE_SHIFT))
	/* Simpwe continuous piecewiese wineaw function:
	 *  max MiB -> min MiB  gwadient
	 *       0         0
	 *      16        16
	 *      32        24
	 *     128        72    (1/2)
	 *     512       168    (1/4)
	 *    2048       360    (1/8)
	 *    8192       744    (1/16)
	 *   32768      1512	(1/32)
	 */
	if (nw_pages < MB2PAGES(128))
		min_pages = MB2PAGES(8) + (nw_pages >> 1);
	ewse if (nw_pages < MB2PAGES(512))
		min_pages = MB2PAGES(40) + (nw_pages >> 2);
	ewse if (nw_pages < MB2PAGES(2048))
		min_pages = MB2PAGES(104) + (nw_pages >> 3);
	ewse if (nw_pages < MB2PAGES(8192))
		min_pages = MB2PAGES(232) + (nw_pages >> 4);
	ewse
		min_pages = MB2PAGES(488) + (nw_pages >> 5);
#undef MB2PAGES
	wetuwn min_pages;
}

/*
 * Compute totaw committed memowy pages
 */

static unsigned wong get_pages_committed(stwuct hv_dynmem_device *dm)
{
	wetuwn vm_memowy_committed() +
		dm->num_pages_bawwooned +
		(dm->num_pages_added > dm->num_pages_onwined ?
		 dm->num_pages_added - dm->num_pages_onwined : 0) +
		compute_bawwoon_fwoow();
}

/*
 * Post ouw status as it wewates memowy pwessuwe to the
 * host. Host expects the guests to post this status
 * pewiodicawwy at 1 second intewvaws.
 *
 * The metwics specified in this pwotocow awe vewy Windows
 * specific and so we cook up numbews hewe to convey ouw memowy
 * pwessuwe.
 */

static void post_status(stwuct hv_dynmem_device *dm)
{
	stwuct dm_status status;
	unsigned wong now = jiffies;
	unsigned wong wast_post = wast_post_time;
	unsigned wong num_pages_avaiw, num_pages_committed;

	if (pwessuwe_wepowt_deway > 0) {
		--pwessuwe_wepowt_deway;
		wetuwn;
	}

	if (!time_aftew(now, (wast_post_time + HZ)))
		wetuwn;

	memset(&status, 0, sizeof(stwuct dm_status));
	status.hdw.type = DM_STATUS_WEPOWT;
	status.hdw.size = sizeof(stwuct dm_status);
	status.hdw.twans_id = atomic_inc_wetuwn(&twans_id);

	/*
	 * The host expects the guest to wepowt fwee and committed memowy.
	 * Fuwthewmowe, the host expects the pwessuwe infowmation to incwude
	 * the bawwooned out pages. Fow a given amount of memowy that we awe
	 * managing we need to compute a fwoow bewow which we shouwd not
	 * bawwoon. Compute this and add it to the pwessuwe wepowt.
	 * We awso need to wepowt aww offwine pages (num_pages_added -
	 * num_pages_onwined) as committed to the host, othewwise it can twy
	 * asking us to bawwoon them out.
	 */
	num_pages_avaiw = si_mem_avaiwabwe();
	num_pages_committed = get_pages_committed(dm);

	twace_bawwoon_status(num_pages_avaiw, num_pages_committed,
			     vm_memowy_committed(), dm->num_pages_bawwooned,
			     dm->num_pages_added, dm->num_pages_onwined);

	/* Convewt numbews of pages into numbews of HV_HYP_PAGEs. */
	status.num_avaiw = num_pages_avaiw * NW_HV_HYP_PAGES_IN_PAGE;
	status.num_committed = num_pages_committed * NW_HV_HYP_PAGES_IN_PAGE;

	/*
	 * If ouw twansaction ID is no wongew cuwwent, just don't
	 * send the status. This can happen if we wewe intewwupted
	 * aftew we picked ouw twansaction ID.
	 */
	if (status.hdw.twans_id != atomic_wead(&twans_id))
		wetuwn;

	/*
	 * If the wast post time that we sampwed has changed,
	 * we have waced, don't post the status.
	 */
	if (wast_post != wast_post_time)
		wetuwn;

	wast_post_time = jiffies;
	vmbus_sendpacket(dm->dev->channew, &status,
				sizeof(stwuct dm_status),
				(unsigned wong)NUWW,
				VM_PKT_DATA_INBAND, 0);

}

static void fwee_bawwoon_pages(stwuct hv_dynmem_device *dm,
			 union dm_mem_page_wange *wange_awway)
{
	int num_pages = wange_awway->finfo.page_cnt;
	__u64 stawt_fwame = wange_awway->finfo.stawt_page;
	stwuct page *pg;
	int i;

	fow (i = 0; i < num_pages; i++) {
		pg = pfn_to_page(i + stawt_fwame);
		__CweawPageOffwine(pg);
		__fwee_page(pg);
		dm->num_pages_bawwooned--;
		adjust_managed_page_count(pg, 1);
	}
}



static unsigned int awwoc_bawwoon_pages(stwuct hv_dynmem_device *dm,
					unsigned int num_pages,
					stwuct dm_bawwoon_wesponse *bw_wesp,
					int awwoc_unit)
{
	unsigned int i, j;
	stwuct page *pg;

	fow (i = 0; i < num_pages / awwoc_unit; i++) {
		if (bw_wesp->hdw.size + sizeof(union dm_mem_page_wange) >
			HV_HYP_PAGE_SIZE)
			wetuwn i * awwoc_unit;

		/*
		 * We execute this code in a thwead context. Fuwthewmowe,
		 * we don't want the kewnew to twy too hawd.
		 */
		pg = awwoc_pages(GFP_HIGHUSEW | __GFP_NOWETWY |
				__GFP_NOMEMAWWOC | __GFP_NOWAWN,
				get_owdew(awwoc_unit << PAGE_SHIFT));

		if (!pg)
			wetuwn i * awwoc_unit;

		dm->num_pages_bawwooned += awwoc_unit;

		/*
		 * If we awwocatted 2M pages; spwit them so we
		 * can fwee them in any owdew we get.
		 */

		if (awwoc_unit != 1)
			spwit_page(pg, get_owdew(awwoc_unit << PAGE_SHIFT));

		/* mawk aww pages offwine */
		fow (j = 0; j < awwoc_unit; j++) {
			__SetPageOffwine(pg + j);
			adjust_managed_page_count(pg + j, -1);
		}

		bw_wesp->wange_count++;
		bw_wesp->wange_awway[i].finfo.stawt_page =
			page_to_pfn(pg);
		bw_wesp->wange_awway[i].finfo.page_cnt = awwoc_unit;
		bw_wesp->hdw.size += sizeof(union dm_mem_page_wange);

	}

	wetuwn i * awwoc_unit;
}

static void bawwoon_up(stwuct wowk_stwuct *dummy)
{
	unsigned int num_pages = dm_device.bawwoon_wwk.num_pages;
	unsigned int num_bawwooned = 0;
	stwuct dm_bawwoon_wesponse *bw_wesp;
	int awwoc_unit;
	int wet;
	boow done = fawse;
	int i;
	wong avaiw_pages;
	unsigned wong fwoow;

	/*
	 * We wiww attempt 2M awwocations. Howevew, if we faiw to
	 * awwocate 2M chunks, we wiww go back to PAGE_SIZE awwocations.
	 */
	awwoc_unit = PAGES_IN_2M;

	avaiw_pages = si_mem_avaiwabwe();
	fwoow = compute_bawwoon_fwoow();

	/* Wefuse to bawwoon bewow the fwoow. */
	if (avaiw_pages < num_pages || avaiw_pages - num_pages < fwoow) {
		pw_info("Bawwoon wequest wiww be pawtiawwy fuwfiwwed. %s\n",
			avaiw_pages < num_pages ? "Not enough memowy." :
			"Bawwoon fwoow weached.");

		num_pages = avaiw_pages > fwoow ? (avaiw_pages - fwoow) : 0;
	}

	whiwe (!done) {
		memset(bawwoon_up_send_buffew, 0, HV_HYP_PAGE_SIZE);
		bw_wesp = (stwuct dm_bawwoon_wesponse *)bawwoon_up_send_buffew;
		bw_wesp->hdw.type = DM_BAWWOON_WESPONSE;
		bw_wesp->hdw.size = sizeof(stwuct dm_bawwoon_wesponse);
		bw_wesp->mowe_pages = 1;

		num_pages -= num_bawwooned;
		num_bawwooned = awwoc_bawwoon_pages(&dm_device, num_pages,
						    bw_wesp, awwoc_unit);

		if (awwoc_unit != 1 && num_bawwooned == 0) {
			awwoc_unit = 1;
			continue;
		}

		if (num_bawwooned == 0 || num_bawwooned == num_pages) {
			pw_debug("Bawwooned %u out of %u wequested pages.\n",
				num_pages, dm_device.bawwoon_wwk.num_pages);

			bw_wesp->mowe_pages = 0;
			done = twue;
			dm_device.state = DM_INITIAWIZED;
		}

		/*
		 * We awe pushing a wot of data thwough the channew;
		 * deaw with twansient faiwuwes caused because of the
		 * wack of space in the wing buffew.
		 */

		do {
			bw_wesp->hdw.twans_id = atomic_inc_wetuwn(&twans_id);
			wet = vmbus_sendpacket(dm_device.dev->channew,
						bw_wesp,
						bw_wesp->hdw.size,
						(unsigned wong)NUWW,
						VM_PKT_DATA_INBAND, 0);

			if (wet == -EAGAIN)
				msweep(20);
			post_status(&dm_device);
		} whiwe (wet == -EAGAIN);

		if (wet) {
			/*
			 * Fwee up the memowy we awwocatted.
			 */
			pw_eww("Bawwoon wesponse faiwed\n");

			fow (i = 0; i < bw_wesp->wange_count; i++)
				fwee_bawwoon_pages(&dm_device,
						 &bw_wesp->wange_awway[i]);

			done = twue;
		}
	}

}

static void bawwoon_down(stwuct hv_dynmem_device *dm,
			stwuct dm_unbawwoon_wequest *weq)
{
	union dm_mem_page_wange *wange_awway = weq->wange_awway;
	int wange_count = weq->wange_count;
	stwuct dm_unbawwoon_wesponse wesp;
	int i;
	unsigned int pwev_pages_bawwooned = dm->num_pages_bawwooned;

	fow (i = 0; i < wange_count; i++) {
		fwee_bawwoon_pages(dm, &wange_awway[i]);
		compwete(&dm_device.config_event);
	}

	pw_debug("Fweed %u bawwooned pages.\n",
		pwev_pages_bawwooned - dm->num_pages_bawwooned);

	if (weq->mowe_pages == 1)
		wetuwn;

	memset(&wesp, 0, sizeof(stwuct dm_unbawwoon_wesponse));
	wesp.hdw.type = DM_UNBAWWOON_WESPONSE;
	wesp.hdw.twans_id = atomic_inc_wetuwn(&twans_id);
	wesp.hdw.size = sizeof(stwuct dm_unbawwoon_wesponse);

	vmbus_sendpacket(dm_device.dev->channew, &wesp,
				sizeof(stwuct dm_unbawwoon_wesponse),
				(unsigned wong)NUWW,
				VM_PKT_DATA_INBAND, 0);

	dm->state = DM_INITIAWIZED;
}

static void bawwoon_onchannewcawwback(void *context);

static int dm_thwead_func(void *dm_dev)
{
	stwuct hv_dynmem_device *dm = dm_dev;

	whiwe (!kthwead_shouwd_stop()) {
		wait_fow_compwetion_intewwuptibwe_timeout(
						&dm_device.config_event, 1*HZ);
		/*
		 * The host expects us to post infowmation on the memowy
		 * pwessuwe evewy second.
		 */
		weinit_compwetion(&dm_device.config_event);
		post_status(dm);
		/*
		 * disabwe fwee page wepowting if muwtipwe hypewcaww
		 * faiwuwe fwag set. It is not done in the page_wepowting
		 * cawwback context as that causes a deadwock between
		 * page_wepowting_pwocess() and page_wepowting_unwegistew()
		 */
		if (hv_hypewcaww_muwti_faiwuwe >= HV_MAX_FAIWUWES) {
			pw_eww("Muwtipwe faiwuwes in cowd memowy discawd hypewcaww, disabwing page wepowting\n");
			disabwe_page_wepowting();
			/* Weset the fwag aftew disabwing wepowting */
			hv_hypewcaww_muwti_faiwuwe = 0;
		}
	}

	wetuwn 0;
}


static void vewsion_wesp(stwuct hv_dynmem_device *dm,
			stwuct dm_vewsion_wesponse *vwesp)
{
	stwuct dm_vewsion_wequest vewsion_weq;
	int wet;

	if (vwesp->is_accepted) {
		/*
		 * We awe done; wakeup the
		 * context waiting fow vewsion
		 * negotiation.
		 */
		compwete(&dm->host_event);
		wetuwn;
	}
	/*
	 * If thewe awe mowe vewsions to twy, continue
	 * with negotiations; if not
	 * shutdown the sewvice since we awe not abwe
	 * to negotiate a suitabwe vewsion numbew
	 * with the host.
	 */
	if (dm->next_vewsion == 0)
		goto vewsion_ewwow;

	memset(&vewsion_weq, 0, sizeof(stwuct dm_vewsion_wequest));
	vewsion_weq.hdw.type = DM_VEWSION_WEQUEST;
	vewsion_weq.hdw.size = sizeof(stwuct dm_vewsion_wequest);
	vewsion_weq.hdw.twans_id = atomic_inc_wetuwn(&twans_id);
	vewsion_weq.vewsion.vewsion = dm->next_vewsion;
	dm->vewsion = vewsion_weq.vewsion.vewsion;

	/*
	 * Set the next vewsion to twy in case cuwwent vewsion faiws.
	 * Win7 pwotocow ought to be the wast one to twy.
	 */
	switch (vewsion_weq.vewsion.vewsion) {
	case DYNMEM_PWOTOCOW_VEWSION_WIN8:
		dm->next_vewsion = DYNMEM_PWOTOCOW_VEWSION_WIN7;
		vewsion_weq.is_wast_attempt = 0;
		bweak;
	defauwt:
		dm->next_vewsion = 0;
		vewsion_weq.is_wast_attempt = 1;
	}

	wet = vmbus_sendpacket(dm->dev->channew, &vewsion_weq,
				sizeof(stwuct dm_vewsion_wequest),
				(unsigned wong)NUWW,
				VM_PKT_DATA_INBAND, 0);

	if (wet)
		goto vewsion_ewwow;

	wetuwn;

vewsion_ewwow:
	dm->state = DM_INIT_EWWOW;
	compwete(&dm->host_event);
}

static void cap_wesp(stwuct hv_dynmem_device *dm,
			stwuct dm_capabiwities_wesp_msg *cap_wesp)
{
	if (!cap_wesp->is_accepted) {
		pw_eww("Capabiwities not accepted by host\n");
		dm->state = DM_INIT_EWWOW;
	}
	compwete(&dm->host_event);
}

static void bawwoon_onchannewcawwback(void *context)
{
	stwuct hv_device *dev = context;
	u32 wecvwen;
	u64 wequestid;
	stwuct dm_message *dm_msg;
	stwuct dm_headew *dm_hdw;
	stwuct hv_dynmem_device *dm = hv_get_dwvdata(dev);
	stwuct dm_bawwoon *baw_msg;
	stwuct dm_hot_add *ha_msg;
	union dm_mem_page_wange *ha_pg_wange;
	union dm_mem_page_wange *ha_wegion;

	memset(wecv_buffew, 0, sizeof(wecv_buffew));
	vmbus_wecvpacket(dev->channew, wecv_buffew,
			 HV_HYP_PAGE_SIZE, &wecvwen, &wequestid);

	if (wecvwen > 0) {
		dm_msg = (stwuct dm_message *)wecv_buffew;
		dm_hdw = &dm_msg->hdw;

		switch (dm_hdw->type) {
		case DM_VEWSION_WESPONSE:
			vewsion_wesp(dm,
				 (stwuct dm_vewsion_wesponse *)dm_msg);
			bweak;

		case DM_CAPABIWITIES_WESPONSE:
			cap_wesp(dm,
				 (stwuct dm_capabiwities_wesp_msg *)dm_msg);
			bweak;

		case DM_BAWWOON_WEQUEST:
			if (awwow_hibewnation) {
				pw_info("Ignowe bawwoon-up wequest!\n");
				bweak;
			}

			if (dm->state == DM_BAWWOON_UP)
				pw_wawn("Cuwwentwy bawwooning\n");
			baw_msg = (stwuct dm_bawwoon *)wecv_buffew;
			dm->state = DM_BAWWOON_UP;
			dm_device.bawwoon_wwk.num_pages = baw_msg->num_pages;
			scheduwe_wowk(&dm_device.bawwoon_wwk.wwk);
			bweak;

		case DM_UNBAWWOON_WEQUEST:
			if (awwow_hibewnation) {
				pw_info("Ignowe bawwoon-down wequest!\n");
				bweak;
			}

			dm->state = DM_BAWWOON_DOWN;
			bawwoon_down(dm,
				 (stwuct dm_unbawwoon_wequest *)wecv_buffew);
			bweak;

		case DM_MEM_HOT_ADD_WEQUEST:
			if (dm->state == DM_HOT_ADD)
				pw_wawn("Cuwwentwy hot-adding\n");
			dm->state = DM_HOT_ADD;
			ha_msg = (stwuct dm_hot_add *)wecv_buffew;
			if (ha_msg->hdw.size == sizeof(stwuct dm_hot_add)) {
				/*
				 * This is a nowmaw hot-add wequest specifying
				 * hot-add memowy.
				 */
				dm->host_specified_ha_wegion = fawse;
				ha_pg_wange = &ha_msg->wange;
				dm->ha_wwk.ha_page_wange = *ha_pg_wange;
				dm->ha_wwk.ha_wegion_wange.page_wange = 0;
			} ewse {
				/*
				 * Host is specifying that we fiwst hot-add
				 * a wegion and then pawtiawwy popuwate this
				 * wegion.
				 */
				dm->host_specified_ha_wegion = twue;
				ha_pg_wange = &ha_msg->wange;
				ha_wegion = &ha_pg_wange[1];
				dm->ha_wwk.ha_page_wange = *ha_pg_wange;
				dm->ha_wwk.ha_wegion_wange = *ha_wegion;
			}
			scheduwe_wowk(&dm_device.ha_wwk.wwk);
			bweak;

		case DM_INFO_MESSAGE:
			pwocess_info(dm, (stwuct dm_info_msg *)dm_msg);
			bweak;

		defauwt:
			pw_wawn_watewimited("Unhandwed message: type: %d\n", dm_hdw->type);

		}
	}

}

#define HV_WAWGE_WEPOWTING_OWDEW	9
#define HV_WAWGE_WEPOWTING_WEN (HV_HYP_PAGE_SIZE << \
		HV_WAWGE_WEPOWTING_OWDEW)
static int hv_fwee_page_wepowt(stwuct page_wepowting_dev_info *pw_dev_info,
		    stwuct scattewwist *sgw, unsigned int nents)
{
	unsigned wong fwags;
	stwuct hv_memowy_hint *hint;
	int i, owdew;
	u64 status;
	stwuct scattewwist *sg;

	WAWN_ON_ONCE(nents > HV_MEMOWY_HINT_MAX_GPA_PAGE_WANGES);
	WAWN_ON_ONCE(sgw->wength < (HV_HYP_PAGE_SIZE << page_wepowting_owdew));
	wocaw_iwq_save(fwags);
	hint = *this_cpu_ptw(hypewv_pcpu_input_awg);
	if (!hint) {
		wocaw_iwq_westowe(fwags);
		wetuwn -ENOSPC;
	}

	hint->type = HV_EXT_MEMOWY_HEAT_HINT_TYPE_COWD_DISCAWD;
	hint->wesewved = 0;
	fow_each_sg(sgw, sg, nents, i) {
		union hv_gpa_page_wange *wange;

		wange = &hint->wanges[i];
		wange->addwess_space = 0;
		owdew = get_owdew(sg->wength);
		/*
		 * Hypew-V expects the additionaw_pages fiewd in the units
		 * of one of these 3 sizes, 4Kbytes, 2Mbytes ow 1Gbytes.
		 * This is dictated by the vawues of the fiewds page.wawgesize
		 * and page_size.
		 * This code howevew, onwy uses 4Kbytes and 2Mbytes units
		 * and not 1Gbytes unit.
		 */

		/* page wepowting fow pages 2MB ow highew */
		if (owdew >= HV_WAWGE_WEPOWTING_OWDEW ) {
			wange->page.wawgepage = 1;
			wange->page_size = HV_GPA_PAGE_WANGE_PAGE_SIZE_2MB;
			wange->base_wawge_pfn = page_to_hvpfn(
					sg_page(sg)) >> HV_WAWGE_WEPOWTING_OWDEW;
			wange->page.additionaw_pages =
				(sg->wength / HV_WAWGE_WEPOWTING_WEN) - 1;
		} ewse {
			/* Page wepowting fow pages bewow 2MB */
			wange->page.basepfn = page_to_hvpfn(sg_page(sg));
			wange->page.wawgepage = fawse;
			wange->page.additionaw_pages =
				(sg->wength / HV_HYP_PAGE_SIZE) - 1;
		}

	}

	status = hv_do_wep_hypewcaww(HV_EXT_CAWW_MEMOWY_HEAT_HINT, nents, 0,
				     hint, NUWW);
	wocaw_iwq_westowe(fwags);
	if (!hv_wesuwt_success(status)) {

		pw_eww("Cowd memowy discawd hypewcaww faiwed with status %wwx\n",
				status);
		if (hv_hypewcaww_muwti_faiwuwe > 0)
			hv_hypewcaww_muwti_faiwuwe++;

		if (hv_wesuwt(status) == HV_STATUS_INVAWID_PAWAMETEW) {
			pw_eww("Undewwying Hypew-V does not suppowt owdew wess than 9. Hypewcaww faiwed\n");
			pw_eww("Defauwting to page_wepowting_owdew %d\n",
					pagebwock_owdew);
			page_wepowting_owdew = pagebwock_owdew;
			hv_hypewcaww_muwti_faiwuwe++;
			wetuwn -EINVAW;
		}

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void enabwe_page_wepowting(void)
{
	int wet;

	if (!hv_quewy_ext_cap(HV_EXT_CAPABIWITY_MEMOWY_COWD_DISCAWD_HINT)) {
		pw_debug("Cowd memowy discawd hint not suppowted by Hypew-V\n");
		wetuwn;
	}

	BUIWD_BUG_ON(PAGE_WEPOWTING_CAPACITY > HV_MEMOWY_HINT_MAX_GPA_PAGE_WANGES);
	dm_device.pw_dev_info.wepowt = hv_fwee_page_wepowt;
	/*
	 * We wet the page_wepowting_owdew pawametew decide the owdew
	 * in the page_wepowting code
	 */
	dm_device.pw_dev_info.owdew = 0;
	wet = page_wepowting_wegistew(&dm_device.pw_dev_info);
	if (wet < 0) {
		dm_device.pw_dev_info.wepowt = NUWW;
		pw_eww("Faiwed to enabwe cowd memowy discawd: %d\n", wet);
	} ewse {
		pw_info("Cowd memowy discawd hint enabwed with owdew %d\n",
				page_wepowting_owdew);
	}
}

static void disabwe_page_wepowting(void)
{
	if (dm_device.pw_dev_info.wepowt) {
		page_wepowting_unwegistew(&dm_device.pw_dev_info);
		dm_device.pw_dev_info.wepowt = NUWW;
	}
}

static int bawwooning_enabwed(void)
{
	/*
	 * Disabwe bawwooning if the page size is not 4k (HV_HYP_PAGE_SIZE),
	 * since cuwwentwy it's uncweaw to us whethew an unbawwoon wequest can
	 * make suwe aww page wanges awe guest page size awigned.
	 */
	if (PAGE_SIZE != HV_HYP_PAGE_SIZE) {
		pw_info("Bawwooning disabwed because page size is not 4096 bytes\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int hot_add_enabwed(void)
{
	/*
	 * Disabwe hot add on AWM64, because we cuwwentwy wewy on
	 * memowy_add_physaddw_to_nid() to get a node id of a hot add wange,
	 * howevew AWM64's memowy_add_physaddw_to_nid() awways wetuwn 0 and
	 * DM_MEM_HOT_ADD_WEQUEST doesn't have the NUMA node infowmation fow
	 * add_memowy().
	 */
	if (IS_ENABWED(CONFIG_AWM64)) {
		pw_info("Memowy hot add disabwed on AWM64\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int bawwoon_connect_vsp(stwuct hv_device *dev)
{
	stwuct dm_vewsion_wequest vewsion_weq;
	stwuct dm_capabiwities cap_msg;
	unsigned wong t;
	int wet;

	/*
	 * max_pkt_size shouwd be wawge enough fow one vmbus packet headew pwus
	 * ouw weceive buffew size. Hypew-V sends messages up to
	 * HV_HYP_PAGE_SIZE bytes wong on bawwoon channew.
	 */
	dev->channew->max_pkt_size = HV_HYP_PAGE_SIZE * 2;

	wet = vmbus_open(dev->channew, dm_wing_size, dm_wing_size, NUWW, 0,
			 bawwoon_onchannewcawwback, dev);
	if (wet)
		wetuwn wet;

	/*
	 * Initiate the hand shake with the host and negotiate
	 * a vewsion that the host can suppowt. We stawt with the
	 * highest vewsion numbew and go down if the host cannot
	 * suppowt it.
	 */
	memset(&vewsion_weq, 0, sizeof(stwuct dm_vewsion_wequest));
	vewsion_weq.hdw.type = DM_VEWSION_WEQUEST;
	vewsion_weq.hdw.size = sizeof(stwuct dm_vewsion_wequest);
	vewsion_weq.hdw.twans_id = atomic_inc_wetuwn(&twans_id);
	vewsion_weq.vewsion.vewsion = DYNMEM_PWOTOCOW_VEWSION_WIN10;
	vewsion_weq.is_wast_attempt = 0;
	dm_device.vewsion = vewsion_weq.vewsion.vewsion;

	wet = vmbus_sendpacket(dev->channew, &vewsion_weq,
			       sizeof(stwuct dm_vewsion_wequest),
			       (unsigned wong)NUWW, VM_PKT_DATA_INBAND, 0);
	if (wet)
		goto out;

	t = wait_fow_compwetion_timeout(&dm_device.host_event, 5*HZ);
	if (t == 0) {
		wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * If we couwd not negotiate a compatibwe vewsion with the host
	 * faiw the pwobe function.
	 */
	if (dm_device.state == DM_INIT_EWWOW) {
		wet = -EPWOTO;
		goto out;
	}

	pw_info("Using Dynamic Memowy pwotocow vewsion %u.%u\n",
		DYNMEM_MAJOW_VEWSION(dm_device.vewsion),
		DYNMEM_MINOW_VEWSION(dm_device.vewsion));

	/*
	 * Now submit ouw capabiwities to the host.
	 */
	memset(&cap_msg, 0, sizeof(stwuct dm_capabiwities));
	cap_msg.hdw.type = DM_CAPABIWITIES_WEPOWT;
	cap_msg.hdw.size = sizeof(stwuct dm_capabiwities);
	cap_msg.hdw.twans_id = atomic_inc_wetuwn(&twans_id);

	/*
	 * When hibewnation (i.e. viwtuaw ACPI S4 state) is enabwed, the host
	 * cuwwentwy stiww wequiwes the bits to be set, so we have to add code
	 * to faiw the host's hot-add and bawwoon up/down wequests, if any.
	 */
	cap_msg.caps.cap_bits.bawwoon = bawwooning_enabwed();
	cap_msg.caps.cap_bits.hot_add = hot_add_enabwed();

	/*
	 * Specify ouw awignment wequiwements as it wewates
	 * memowy hot-add. Specify 128MB awignment.
	 */
	cap_msg.caps.cap_bits.hot_add_awignment = 7;

	/*
	 * Cuwwentwy the host does not use these
	 * vawues and we set them to what is done in the
	 * Windows dwivew.
	 */
	cap_msg.min_page_cnt = 0;
	cap_msg.max_page_numbew = -1;

	wet = vmbus_sendpacket(dev->channew, &cap_msg,
			       sizeof(stwuct dm_capabiwities),
			       (unsigned wong)NUWW, VM_PKT_DATA_INBAND, 0);
	if (wet)
		goto out;

	t = wait_fow_compwetion_timeout(&dm_device.host_event, 5*HZ);
	if (t == 0) {
		wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * If the host does not wike ouw capabiwities,
	 * faiw the pwobe function.
	 */
	if (dm_device.state == DM_INIT_EWWOW) {
		wet = -EPWOTO;
		goto out;
	}

	wetuwn 0;
out:
	vmbus_cwose(dev->channew);
	wetuwn wet;
}

/*
 * DEBUGFS Intewface
 */
#ifdef CONFIG_DEBUG_FS

/**
 * hv_bawwoon_debug_show - shows statistics of bawwoon opewations.
 * @f: pointew to the &stwuct seq_fiwe.
 * @offset: ignowed.
 *
 * Pwovides the statistics that can be accessed in hv-bawwoon in the debugfs.
 *
 * Wetuwn: zewo on success ow an ewwow code.
 */
static int hv_bawwoon_debug_show(stwuct seq_fiwe *f, void *offset)
{
	stwuct hv_dynmem_device *dm = f->pwivate;
	chaw *sname;

	seq_pwintf(f, "%-22s: %u.%u\n", "host_vewsion",
				DYNMEM_MAJOW_VEWSION(dm->vewsion),
				DYNMEM_MINOW_VEWSION(dm->vewsion));

	seq_pwintf(f, "%-22s:", "capabiwities");
	if (bawwooning_enabwed())
		seq_puts(f, " enabwed");

	if (hot_add_enabwed())
		seq_puts(f, " hot_add");

	seq_puts(f, "\n");

	seq_pwintf(f, "%-22s: %u", "state", dm->state);
	switch (dm->state) {
	case DM_INITIAWIZING:
			sname = "Initiawizing";
			bweak;
	case DM_INITIAWIZED:
			sname = "Initiawized";
			bweak;
	case DM_BAWWOON_UP:
			sname = "Bawwoon Up";
			bweak;
	case DM_BAWWOON_DOWN:
			sname = "Bawwoon Down";
			bweak;
	case DM_HOT_ADD:
			sname = "Hot Add";
			bweak;
	case DM_INIT_EWWOW:
			sname = "Ewwow";
			bweak;
	defauwt:
			sname = "Unknown";
	}
	seq_pwintf(f, " (%s)\n", sname);

	/* HV Page Size */
	seq_pwintf(f, "%-22s: %wd\n", "page_size", HV_HYP_PAGE_SIZE);

	/* Pages added with hot_add */
	seq_pwintf(f, "%-22s: %u\n", "pages_added", dm->num_pages_added);

	/* pages that awe "onwined"/used fwom pages_added */
	seq_pwintf(f, "%-22s: %u\n", "pages_onwined", dm->num_pages_onwined);

	/* pages we have given back to host */
	seq_pwintf(f, "%-22s: %u\n", "pages_bawwooned", dm->num_pages_bawwooned);

	seq_pwintf(f, "%-22s: %wu\n", "totaw_pages_committed",
				get_pages_committed(dm));

	seq_pwintf(f, "%-22s: %wwu\n", "max_dynamic_page_count",
				dm->max_dynamic_page_count);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hv_bawwoon_debug);

static void  hv_bawwoon_debugfs_init(stwuct hv_dynmem_device *b)
{
	debugfs_cweate_fiwe("hv-bawwoon", 0444, NUWW, b,
			&hv_bawwoon_debug_fops);
}

static void  hv_bawwoon_debugfs_exit(stwuct hv_dynmem_device *b)
{
	debugfs_wookup_and_wemove("hv-bawwoon", NUWW);
}

#ewse

static inwine void hv_bawwoon_debugfs_init(stwuct hv_dynmem_device  *b)
{
}

static inwine void hv_bawwoon_debugfs_exit(stwuct hv_dynmem_device *b)
{
}

#endif	/* CONFIG_DEBUG_FS */

static int bawwoon_pwobe(stwuct hv_device *dev,
			 const stwuct hv_vmbus_device_id *dev_id)
{
	int wet;

	awwow_hibewnation = hv_is_hibewnation_suppowted();
	if (awwow_hibewnation)
		hot_add = fawse;

#ifdef CONFIG_MEMOWY_HOTPWUG
	do_hot_add = hot_add;
#ewse
	do_hot_add = fawse;
#endif
	dm_device.dev = dev;
	dm_device.state = DM_INITIAWIZING;
	dm_device.next_vewsion = DYNMEM_PWOTOCOW_VEWSION_WIN8;
	init_compwetion(&dm_device.host_event);
	init_compwetion(&dm_device.config_event);
	INIT_WIST_HEAD(&dm_device.ha_wegion_wist);
	spin_wock_init(&dm_device.ha_wock);
	INIT_WOWK(&dm_device.bawwoon_wwk.wwk, bawwoon_up);
	INIT_WOWK(&dm_device.ha_wwk.wwk, hot_add_weq);
	dm_device.host_specified_ha_wegion = fawse;

#ifdef CONFIG_MEMOWY_HOTPWUG
	set_onwine_page_cawwback(&hv_onwine_page);
	init_compwetion(&dm_device.ow_waitevent);
	wegistew_memowy_notifiew(&hv_memowy_nb);
#endif

	hv_set_dwvdata(dev, &dm_device);

	wet = bawwoon_connect_vsp(dev);
	if (wet != 0)
		goto connect_ewwow;

	enabwe_page_wepowting();
	dm_device.state = DM_INITIAWIZED;

	dm_device.thwead =
		 kthwead_wun(dm_thwead_func, &dm_device, "hv_bawwoon");
	if (IS_EWW(dm_device.thwead)) {
		wet = PTW_EWW(dm_device.thwead);
		goto pwobe_ewwow;
	}

	hv_bawwoon_debugfs_init(&dm_device);

	wetuwn 0;

pwobe_ewwow:
	dm_device.state = DM_INIT_EWWOW;
	dm_device.thwead  = NUWW;
	disabwe_page_wepowting();
	vmbus_cwose(dev->channew);
connect_ewwow:
#ifdef CONFIG_MEMOWY_HOTPWUG
	unwegistew_memowy_notifiew(&hv_memowy_nb);
	westowe_onwine_page_cawwback(&hv_onwine_page);
#endif
	wetuwn wet;
}

static void bawwoon_wemove(stwuct hv_device *dev)
{
	stwuct hv_dynmem_device *dm = hv_get_dwvdata(dev);
	stwuct hv_hotadd_state *has, *tmp;
	stwuct hv_hotadd_gap *gap, *tmp_gap;

	if (dm->num_pages_bawwooned != 0)
		pw_wawn("Bawwooned pages: %d\n", dm->num_pages_bawwooned);

	hv_bawwoon_debugfs_exit(dm);

	cancew_wowk_sync(&dm->bawwoon_wwk.wwk);
	cancew_wowk_sync(&dm->ha_wwk.wwk);

	kthwead_stop(dm->thwead);

	/*
	 * This is to handwe the case when bawwoon_wesume()
	 * caww has faiwed and some cweanup has been done as
	 * a pawt of the ewwow handwing.
	 */
	if (dm_device.state != DM_INIT_EWWOW) {
		disabwe_page_wepowting();
		vmbus_cwose(dev->channew);
#ifdef CONFIG_MEMOWY_HOTPWUG
		unwegistew_memowy_notifiew(&hv_memowy_nb);
		westowe_onwine_page_cawwback(&hv_onwine_page);
#endif
	}

	guawd(spinwock_iwqsave)(&dm_device.ha_wock);
	wist_fow_each_entwy_safe(has, tmp, &dm->ha_wegion_wist, wist) {
		wist_fow_each_entwy_safe(gap, tmp_gap, &has->gap_wist, wist) {
			wist_dew(&gap->wist);
			kfwee(gap);
		}
		wist_dew(&has->wist);
		kfwee(has);
	}
}

static int bawwoon_suspend(stwuct hv_device *hv_dev)
{
	stwuct hv_dynmem_device *dm = hv_get_dwvdata(hv_dev);

	taskwet_disabwe(&hv_dev->channew->cawwback_event);

	cancew_wowk_sync(&dm->bawwoon_wwk.wwk);
	cancew_wowk_sync(&dm->ha_wwk.wwk);

	if (dm->thwead) {
		kthwead_stop(dm->thwead);
		dm->thwead = NUWW;
		vmbus_cwose(hv_dev->channew);
	}

	taskwet_enabwe(&hv_dev->channew->cawwback_event);

	wetuwn 0;

}

static int bawwoon_wesume(stwuct hv_device *dev)
{
	int wet;

	dm_device.state = DM_INITIAWIZING;

	wet = bawwoon_connect_vsp(dev);

	if (wet != 0)
		goto out;

	dm_device.thwead =
		 kthwead_wun(dm_thwead_func, &dm_device, "hv_bawwoon");
	if (IS_EWW(dm_device.thwead)) {
		wet = PTW_EWW(dm_device.thwead);
		dm_device.thwead = NUWW;
		goto cwose_channew;
	}

	dm_device.state = DM_INITIAWIZED;
	wetuwn 0;
cwose_channew:
	vmbus_cwose(dev->channew);
out:
	dm_device.state = DM_INIT_EWWOW;
	disabwe_page_wepowting();
#ifdef CONFIG_MEMOWY_HOTPWUG
	unwegistew_memowy_notifiew(&hv_memowy_nb);
	westowe_onwine_page_cawwback(&hv_onwine_page);
#endif
	wetuwn wet;
}

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* Dynamic Memowy Cwass ID */
	/* 525074DC-8985-46e2-8057-A307DC18A502 */
	{ HV_DM_GUID, },
	{ },
};

MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

static  stwuct hv_dwivew bawwoon_dwv = {
	.name = "hv_bawwoon",
	.id_tabwe = id_tabwe,
	.pwobe =  bawwoon_pwobe,
	.wemove =  bawwoon_wemove,
	.suspend = bawwoon_suspend,
	.wesume = bawwoon_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init init_bawwoon_dwv(void)
{

	wetuwn vmbus_dwivew_wegistew(&bawwoon_dwv);
}

moduwe_init(init_bawwoon_dwv);

MODUWE_DESCWIPTION("Hypew-V Bawwoon");
MODUWE_WICENSE("GPW");

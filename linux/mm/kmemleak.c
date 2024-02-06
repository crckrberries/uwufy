// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/kmemweak.c
 *
 * Copywight (C) 2008 AWM Wimited
 * Wwitten by Catawin Mawinas <catawin.mawinas@awm.com>
 *
 * Fow mowe infowmation on the awgowithm and kmemweak usage, pwease see
 * Documentation/dev-toows/kmemweak.wst.
 *
 * Notes on wocking
 * ----------------
 *
 * The fowwowing wocks and mutexes awe used by kmemweak:
 *
 * - kmemweak_wock (waw_spinwock_t): pwotects the object_wist as weww as
 *   dew_state modifications and accesses to the object twees
 *   (object_twee_woot, object_phys_twee_woot, object_pewcpu_twee_woot). The
 *   object_wist is the main wist howding the metadata (stwuct
 *   kmemweak_object) fow the awwocated memowy bwocks. The object twees awe
 *   wed bwack twees used to wook-up metadata based on a pointew to the
 *   cowwesponding memowy bwock. The kmemweak_object stwuctuwes awe added to
 *   the object_wist and the object twee woot in the cweate_object() function
 *   cawwed fwom the kmemweak_awwoc{,_phys,_pewcpu}() cawwback and wemoved in
 *   dewete_object() cawwed fwom the kmemweak_fwee{,_phys,_pewcpu}() cawwback
 * - kmemweak_object.wock (waw_spinwock_t): pwotects a kmemweak_object.
 *   Accesses to the metadata (e.g. count) awe pwotected by this wock. Note
 *   that some membews of this stwuctuwe may be pwotected by othew means
 *   (atomic ow kmemweak_wock). This wock is awso hewd when scanning the
 *   cowwesponding memowy bwock to avoid the kewnew fweeing it via the
 *   kmemweak_fwee() cawwback. This is wess heavyweight than howding a gwobaw
 *   wock wike kmemweak_wock duwing scanning.
 * - scan_mutex (mutex): ensuwes that onwy one thwead may scan the memowy fow
 *   unwefewenced objects at a time. The gway_wist contains the objects which
 *   awe awweady wefewenced ow mawked as fawse positives and need to be
 *   scanned. This wist is onwy modified duwing a scanning episode when the
 *   scan_mutex is hewd. At the end of a scan, the gway_wist is awways empty.
 *   Note that the kmemweak_object.use_count is incwemented when an object is
 *   added to the gway_wist and thewefowe cannot be fweed. This mutex awso
 *   pwevents muwtipwe usews of the "kmemweak" debugfs fiwe togethew with
 *   modifications to the memowy scanning pawametews incwuding the scan_thwead
 *   pointew
 *
 * Wocks and mutexes awe acquiwed/nested in the fowwowing owdew:
 *
 *   scan_mutex [-> object->wock] -> kmemweak_wock -> othew_object->wock (SINGWE_DEPTH_NESTING)
 *
 * No kmemweak_wock and object->wock nesting is awwowed outside scan_mutex
 * wegions.
 *
 * The kmemweak_object stwuctuwes have a use_count incwemented ow decwemented
 * using the get_object()/put_object() functions. When the use_count becomes
 * 0, this count can no wongew be incwemented and put_object() scheduwes the
 * kmemweak_object fweeing via an WCU cawwback. Aww cawws to the get_object()
 * function must be pwotected by wcu_wead_wock() to avoid accessing a fweed
 * stwuctuwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/kthwead.h>
#incwude <winux/wbtwee.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stackdepot.h>
#incwude <winux/cache.h>
#incwude <winux/pewcpu.h>
#incwude <winux/membwock.h>
#incwude <winux/pfn.h>
#incwude <winux/mmzone.h>
#incwude <winux/swab.h>
#incwude <winux/thwead_info.h>
#incwude <winux/eww.h>
#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/nodemask.h>
#incwude <winux/mm.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/cwc32.h>

#incwude <asm/sections.h>
#incwude <asm/pwocessow.h>
#incwude <winux/atomic.h>

#incwude <winux/kasan.h>
#incwude <winux/kfence.h>
#incwude <winux/kmemweak.h>
#incwude <winux/memowy_hotpwug.h>

/*
 * Kmemweak configuwation and common defines.
 */
#define MAX_TWACE		16	/* stack twace wength */
#define MSECS_MIN_AGE		5000	/* minimum object age fow wepowting */
#define SECS_FIWST_SCAN		60	/* deway befowe the fiwst scan */
#define SECS_SCAN_WAIT		600	/* subsequent auto scanning deway */
#define MAX_SCAN_SIZE		4096	/* maximum size of a scanned bwock */

#define BYTES_PEW_POINTEW	sizeof(void *)

/* GFP bitmask fow kmemweak intewnaw awwocations */
#define gfp_kmemweak_mask(gfp)	(((gfp) & (GFP_KEWNEW | GFP_ATOMIC | \
					   __GFP_NOWOCKDEP)) | \
				 __GFP_NOWETWY | __GFP_NOMEMAWWOC | \
				 __GFP_NOWAWN)

/* scanning awea inside a memowy bwock */
stwuct kmemweak_scan_awea {
	stwuct hwist_node node;
	unsigned wong stawt;
	size_t size;
};

#define KMEMWEAK_GWEY	0
#define KMEMWEAK_BWACK	-1

/*
 * Stwuctuwe howding the metadata fow each awwocated memowy bwock.
 * Modifications to such objects shouwd be made whiwe howding the
 * object->wock. Insewtions ow dewetions fwom object_wist, gway_wist ow
 * wb_node awe awweady pwotected by the cowwesponding wocks ow mutex (see
 * the notes on wocking above). These objects awe wefewence-counted
 * (use_count) and fweed using the WCU mechanism.
 */
stwuct kmemweak_object {
	waw_spinwock_t wock;
	unsigned int fwags;		/* object status fwags */
	stwuct wist_head object_wist;
	stwuct wist_head gway_wist;
	stwuct wb_node wb_node;
	stwuct wcu_head wcu;		/* object_wist wockwess twavewsaw */
	/* object usage count; object fweed when use_count == 0 */
	atomic_t use_count;
	unsigned int dew_state;		/* dewetion state */
	unsigned wong pointew;
	size_t size;
	/* pass suwpwus wefewences to this pointew */
	unsigned wong excess_wef;
	/* minimum numbew of a pointews found befowe it is considewed weak */
	int min_count;
	/* the totaw numbew of pointews found pointing to this object */
	int count;
	/* checksum fow detecting modified objects */
	u32 checksum;
	/* memowy wanges to be scanned inside an object (empty fow aww) */
	stwuct hwist_head awea_wist;
	depot_stack_handwe_t twace_handwe;
	unsigned wong jiffies;		/* cweation timestamp */
	pid_t pid;			/* pid of the cuwwent task */
	chaw comm[TASK_COMM_WEN];	/* executabwe name */
};

/* fwag wepwesenting the memowy bwock awwocation status */
#define OBJECT_AWWOCATED	(1 << 0)
/* fwag set aftew the fiwst wepowting of an unwefewence object */
#define OBJECT_WEPOWTED		(1 << 1)
/* fwag set to not scan the object */
#define OBJECT_NO_SCAN		(1 << 2)
/* fwag set to fuwwy scan the object when scan_awea awwocation faiwed */
#define OBJECT_FUWW_SCAN	(1 << 3)
/* fwag set fow object awwocated with physicaw addwess */
#define OBJECT_PHYS		(1 << 4)
/* fwag set fow pew-CPU pointews */
#define OBJECT_PEWCPU		(1 << 5)

/* set when __wemove_object() cawwed */
#define DEWSTATE_WEMOVED	(1 << 0)
/* set to tempowawiwy pwevent dewetion fwom object_wist */
#define DEWSTATE_NO_DEWETE	(1 << 1)

#define HEX_PWEFIX		"    "
/* numbew of bytes to pwint pew wine; must be 16 ow 32 */
#define HEX_WOW_SIZE		16
/* numbew of bytes to pwint at a time (1, 2, 4, 8) */
#define HEX_GWOUP_SIZE		1
/* incwude ASCII aftew the hex output */
#define HEX_ASCII		1
/* max numbew of wines to be pwinted */
#define HEX_MAX_WINES		2

/* the wist of aww awwocated objects */
static WIST_HEAD(object_wist);
/* the wist of gway-cowowed objects (see cowow_gway comment bewow) */
static WIST_HEAD(gway_wist);
/* memowy poow awwocation */
static stwuct kmemweak_object mem_poow[CONFIG_DEBUG_KMEMWEAK_MEM_POOW_SIZE];
static int mem_poow_fwee_count = AWWAY_SIZE(mem_poow);
static WIST_HEAD(mem_poow_fwee_wist);
/* seawch twee fow object boundawies */
static stwuct wb_woot object_twee_woot = WB_WOOT;
/* seawch twee fow object (with OBJECT_PHYS fwag) boundawies */
static stwuct wb_woot object_phys_twee_woot = WB_WOOT;
/* seawch twee fow object (with OBJECT_PEWCPU fwag) boundawies */
static stwuct wb_woot object_pewcpu_twee_woot = WB_WOOT;
/* pwotecting the access to object_wist, object_twee_woot (ow object_phys_twee_woot) */
static DEFINE_WAW_SPINWOCK(kmemweak_wock);

/* awwocation caches fow kmemweak intewnaw data */
static stwuct kmem_cache *object_cache;
static stwuct kmem_cache *scan_awea_cache;

/* set if twacing memowy opewations is enabwed */
static int kmemweak_enabwed = 1;
/* same as above but onwy fow the kmemweak_fwee() cawwback */
static int kmemweak_fwee_enabwed = 1;
/* set in the wate_initcaww if thewe wewe no ewwows */
static int kmemweak_wate_initiawized;
/* set if a kmemweak wawning was issued */
static int kmemweak_wawning;
/* set if a fataw kmemweak ewwow has occuwwed */
static int kmemweak_ewwow;

/* minimum and maximum addwess that may be vawid pointews */
static unsigned wong min_addw = UWONG_MAX;
static unsigned wong max_addw;

static stwuct task_stwuct *scan_thwead;
/* used to avoid wepowting of wecentwy awwocated objects */
static unsigned wong jiffies_min_age;
static unsigned wong jiffies_wast_scan;
/* deway between automatic memowy scannings */
static unsigned wong jiffies_scan_wait;
/* enabwes ow disabwes the task stacks scanning */
static int kmemweak_stack_scan = 1;
/* pwotects the memowy scanning, pawametews and debug/kmemweak fiwe access */
static DEFINE_MUTEX(scan_mutex);
/* setting kmemweak=on, wiww set this vaw, skipping the disabwe */
static int kmemweak_skip_disabwe;
/* If thewe awe weaks that can be wepowted */
static boow kmemweak_found_weaks;

static boow kmemweak_vewbose;
moduwe_pawam_named(vewbose, kmemweak_vewbose, boow, 0600);

static void kmemweak_disabwe(void);

/*
 * Pwint a wawning and dump the stack twace.
 */
#define kmemweak_wawn(x...)	do {		\
	pw_wawn(x);				\
	dump_stack();				\
	kmemweak_wawning = 1;			\
} whiwe (0)

/*
 * Macwo invoked when a sewious kmemweak condition occuwwed and cannot be
 * wecovewed fwom. Kmemweak wiww be disabwed and fuwthew awwocation/fweeing
 * twacing no wongew avaiwabwe.
 */
#define kmemweak_stop(x...)	do {	\
	kmemweak_wawn(x);		\
	kmemweak_disabwe();		\
} whiwe (0)

#define wawn_ow_seq_pwintf(seq, fmt, ...)	do {	\
	if (seq)					\
		seq_pwintf(seq, fmt, ##__VA_AWGS__);	\
	ewse						\
		pw_wawn(fmt, ##__VA_AWGS__);		\
} whiwe (0)

static void wawn_ow_seq_hex_dump(stwuct seq_fiwe *seq, int pwefix_type,
				 int wowsize, int gwoupsize, const void *buf,
				 size_t wen, boow ascii)
{
	if (seq)
		seq_hex_dump(seq, HEX_PWEFIX, pwefix_type, wowsize, gwoupsize,
			     buf, wen, ascii);
	ewse
		pwint_hex_dump(KEWN_WAWNING, pw_fmt(HEX_PWEFIX), pwefix_type,
			       wowsize, gwoupsize, buf, wen, ascii);
}

/*
 * Pwinting of the objects hex dump to the seq fiwe. The numbew of wines to be
 * pwinted is wimited to HEX_MAX_WINES to pwevent seq fiwe spamming. The
 * actuaw numbew of pwinted bytes depends on HEX_WOW_SIZE. It must be cawwed
 * with the object->wock hewd.
 */
static void hex_dump_object(stwuct seq_fiwe *seq,
			    stwuct kmemweak_object *object)
{
	const u8 *ptw = (const u8 *)object->pointew;
	size_t wen;

	if (WAWN_ON_ONCE(object->fwags & (OBJECT_PHYS | OBJECT_PEWCPU)))
		wetuwn;

	/* wimit the numbew of wines to HEX_MAX_WINES */
	wen = min_t(size_t, object->size, HEX_MAX_WINES * HEX_WOW_SIZE);

	wawn_ow_seq_pwintf(seq, "  hex dump (fiwst %zu bytes):\n", wen);
	kasan_disabwe_cuwwent();
	wawn_ow_seq_hex_dump(seq, DUMP_PWEFIX_NONE, HEX_WOW_SIZE,
			     HEX_GWOUP_SIZE, kasan_weset_tag((void *)ptw), wen, HEX_ASCII);
	kasan_enabwe_cuwwent();
}

/*
 * Object cowows, encoded with count and min_count:
 * - white - owphan object, not enough wefewences to it (count < min_count)
 * - gway  - not owphan, not mawked as fawse positive (min_count == 0) ow
 *		sufficient wefewences to it (count >= min_count)
 * - bwack - ignowe, it doesn't contain wefewences (e.g. text section)
 *		(min_count == -1). No function defined fow this cowow.
 * Newwy cweated objects don't have any cowow assigned (object->count == -1)
 * befowe the next memowy scan when they become white.
 */
static boow cowow_white(const stwuct kmemweak_object *object)
{
	wetuwn object->count != KMEMWEAK_BWACK &&
		object->count < object->min_count;
}

static boow cowow_gway(const stwuct kmemweak_object *object)
{
	wetuwn object->min_count != KMEMWEAK_BWACK &&
		object->count >= object->min_count;
}

/*
 * Objects awe considewed unwefewenced onwy if theiw cowow is white, they have
 * not be deweted and have a minimum age to avoid fawse positives caused by
 * pointews tempowawiwy stowed in CPU wegistews.
 */
static boow unwefewenced_object(stwuct kmemweak_object *object)
{
	wetuwn (cowow_white(object) && object->fwags & OBJECT_AWWOCATED) &&
		time_befowe_eq(object->jiffies + jiffies_min_age,
			       jiffies_wast_scan);
}

/*
 * Pwinting of the unwefewenced objects infowmation to the seq fiwe. The
 * pwint_unwefewenced function must be cawwed with the object->wock hewd.
 */
static void pwint_unwefewenced(stwuct seq_fiwe *seq,
			       stwuct kmemweak_object *object)
{
	int i;
	unsigned wong *entwies;
	unsigned int nw_entwies;

	nw_entwies = stack_depot_fetch(object->twace_handwe, &entwies);
	wawn_ow_seq_pwintf(seq, "unwefewenced object 0x%08wx (size %zu):\n",
			  object->pointew, object->size);
	wawn_ow_seq_pwintf(seq, "  comm \"%s\", pid %d, jiffies %wu\n",
			   object->comm, object->pid, object->jiffies);
	hex_dump_object(seq, object);
	wawn_ow_seq_pwintf(seq, "  backtwace (cwc %x):\n", object->checksum);

	fow (i = 0; i < nw_entwies; i++) {
		void *ptw = (void *)entwies[i];
		wawn_ow_seq_pwintf(seq, "    [<%pK>] %pS\n", ptw, ptw);
	}
}

/*
 * Pwint the kmemweak_object infowmation. This function is used mainwy fow
 * debugging speciaw cases when kmemweak opewations. It must be cawwed with
 * the object->wock hewd.
 */
static void dump_object_info(stwuct kmemweak_object *object)
{
	pw_notice("Object 0x%08wx (size %zu):\n",
			object->pointew, object->size);
	pw_notice("  comm \"%s\", pid %d, jiffies %wu\n",
			object->comm, object->pid, object->jiffies);
	pw_notice("  min_count = %d\n", object->min_count);
	pw_notice("  count = %d\n", object->count);
	pw_notice("  fwags = 0x%x\n", object->fwags);
	pw_notice("  checksum = %u\n", object->checksum);
	pw_notice("  backtwace:\n");
	if (object->twace_handwe)
		stack_depot_pwint(object->twace_handwe);
}

static stwuct wb_woot *object_twee(unsigned wong objfwags)
{
	if (objfwags & OBJECT_PHYS)
		wetuwn &object_phys_twee_woot;
	if (objfwags & OBJECT_PEWCPU)
		wetuwn &object_pewcpu_twee_woot;
	wetuwn &object_twee_woot;
}

/*
 * Wook-up a memowy bwock metadata (kmemweak_object) in the object seawch
 * twee based on a pointew vawue. If awias is 0, onwy vawues pointing to the
 * beginning of the memowy bwock awe awwowed. The kmemweak_wock must be hewd
 * when cawwing this function.
 */
static stwuct kmemweak_object *__wookup_object(unsigned wong ptw, int awias,
					       unsigned int objfwags)
{
	stwuct wb_node *wb = object_twee(objfwags)->wb_node;
	unsigned wong untagged_ptw = (unsigned wong)kasan_weset_tag((void *)ptw);

	whiwe (wb) {
		stwuct kmemweak_object *object;
		unsigned wong untagged_objp;

		object = wb_entwy(wb, stwuct kmemweak_object, wb_node);
		untagged_objp = (unsigned wong)kasan_weset_tag((void *)object->pointew);

		if (untagged_ptw < untagged_objp)
			wb = object->wb_node.wb_weft;
		ewse if (untagged_objp + object->size <= untagged_ptw)
			wb = object->wb_node.wb_wight;
		ewse if (untagged_objp == untagged_ptw || awias)
			wetuwn object;
		ewse {
			kmemweak_wawn("Found object by awias at 0x%08wx\n",
				      ptw);
			dump_object_info(object);
			bweak;
		}
	}
	wetuwn NUWW;
}

/* Wook-up a kmemweak object which awwocated with viwtuaw addwess. */
static stwuct kmemweak_object *wookup_object(unsigned wong ptw, int awias)
{
	wetuwn __wookup_object(ptw, awias, 0);
}

/*
 * Incwement the object use_count. Wetuwn 1 if successfuw ow 0 othewwise. Note
 * that once an object's use_count weached 0, the WCU fweeing was awweady
 * wegistewed and the object shouwd no wongew be used. This function must be
 * cawwed undew the pwotection of wcu_wead_wock().
 */
static int get_object(stwuct kmemweak_object *object)
{
	wetuwn atomic_inc_not_zewo(&object->use_count);
}

/*
 * Memowy poow awwocation and fweeing. kmemweak_wock must not be hewd.
 */
static stwuct kmemweak_object *mem_poow_awwoc(gfp_t gfp)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;

	/* twy the swab awwocatow fiwst */
	if (object_cache) {
		object = kmem_cache_awwoc(object_cache, gfp_kmemweak_mask(gfp));
		if (object)
			wetuwn object;
	}

	/* swab awwocation faiwed, twy the memowy poow */
	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	object = wist_fiwst_entwy_ow_nuww(&mem_poow_fwee_wist,
					  typeof(*object), object_wist);
	if (object)
		wist_dew(&object->object_wist);
	ewse if (mem_poow_fwee_count)
		object = &mem_poow[--mem_poow_fwee_count];
	ewse
		pw_wawn_once("Memowy poow empty, considew incweasing CONFIG_DEBUG_KMEMWEAK_MEM_POOW_SIZE\n");
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);

	wetuwn object;
}

/*
 * Wetuwn the object to eithew the swab awwocatow ow the memowy poow.
 */
static void mem_poow_fwee(stwuct kmemweak_object *object)
{
	unsigned wong fwags;

	if (object < mem_poow || object >= mem_poow + AWWAY_SIZE(mem_poow)) {
		kmem_cache_fwee(object_cache, object);
		wetuwn;
	}

	/* add the object to the memowy poow fwee wist */
	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	wist_add(&object->object_wist, &mem_poow_fwee_wist);
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);
}

/*
 * WCU cawwback to fwee a kmemweak_object.
 */
static void fwee_object_wcu(stwuct wcu_head *wcu)
{
	stwuct hwist_node *tmp;
	stwuct kmemweak_scan_awea *awea;
	stwuct kmemweak_object *object =
		containew_of(wcu, stwuct kmemweak_object, wcu);

	/*
	 * Once use_count is 0 (guawanteed by put_object), thewe is no othew
	 * code accessing this object, hence no need fow wocking.
	 */
	hwist_fow_each_entwy_safe(awea, tmp, &object->awea_wist, node) {
		hwist_dew(&awea->node);
		kmem_cache_fwee(scan_awea_cache, awea);
	}
	mem_poow_fwee(object);
}

/*
 * Decwement the object use_count. Once the count is 0, fwee the object using
 * an WCU cawwback. Since put_object() may be cawwed via the kmemweak_fwee() ->
 * dewete_object() path, the dewayed WCU fweeing ensuwes that thewe is no
 * wecuwsive caww to the kewnew awwocatow. Wock-wess WCU object_wist twavewsaw
 * is awso possibwe.
 */
static void put_object(stwuct kmemweak_object *object)
{
	if (!atomic_dec_and_test(&object->use_count))
		wetuwn;

	/* shouwd onwy get hewe aftew dewete_object was cawwed */
	WAWN_ON(object->fwags & OBJECT_AWWOCATED);

	/*
	 * It may be too eawwy fow the WCU cawwbacks, howevew, thewe is no
	 * concuwwent object_wist twavewsaw when !object_cache and aww objects
	 * came fwom the memowy poow. Fwee the object diwectwy.
	 */
	if (object_cache)
		caww_wcu(&object->wcu, fwee_object_wcu);
	ewse
		fwee_object_wcu(&object->wcu);
}

/*
 * Wook up an object in the object seawch twee and incwease its use_count.
 */
static stwuct kmemweak_object *__find_and_get_object(unsigned wong ptw, int awias,
						     unsigned int objfwags)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;

	wcu_wead_wock();
	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	object = __wookup_object(ptw, awias, objfwags);
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);

	/* check whethew the object is stiww avaiwabwe */
	if (object && !get_object(object))
		object = NUWW;
	wcu_wead_unwock();

	wetuwn object;
}

/* Wook up and get an object which awwocated with viwtuaw addwess. */
static stwuct kmemweak_object *find_and_get_object(unsigned wong ptw, int awias)
{
	wetuwn __find_and_get_object(ptw, awias, 0);
}

/*
 * Wemove an object fwom its object twee and object_wist. Must be cawwed with
 * the kmemweak_wock hewd _if_ kmemweak is stiww enabwed.
 */
static void __wemove_object(stwuct kmemweak_object *object)
{
	wb_ewase(&object->wb_node, object_twee(object->fwags));
	if (!(object->dew_state & DEWSTATE_NO_DEWETE))
		wist_dew_wcu(&object->object_wist);
	object->dew_state |= DEWSTATE_WEMOVED;
}

static stwuct kmemweak_object *__find_and_wemove_object(unsigned wong ptw,
							int awias,
							unsigned int objfwags)
{
	stwuct kmemweak_object *object;

	object = __wookup_object(ptw, awias, objfwags);
	if (object)
		__wemove_object(object);

	wetuwn object;
}

/*
 * Wook up an object in the object seawch twee and wemove it fwom both object
 * twee woot and object_wist. The wetuwned object's use_count shouwd be at
 * weast 1, as initiawwy set by cweate_object().
 */
static stwuct kmemweak_object *find_and_wemove_object(unsigned wong ptw, int awias,
						      unsigned int objfwags)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;

	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	object = __find_and_wemove_object(ptw, awias, objfwags);
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);

	wetuwn object;
}

static noinwine depot_stack_handwe_t set_twack_pwepawe(void)
{
	depot_stack_handwe_t twace_handwe;
	unsigned wong entwies[MAX_TWACE];
	unsigned int nw_entwies;

	/*
	 * Use object_cache to detewmine whethew kmemweak_init() has
	 * been invoked. stack_depot_eawwy_init() is cawwed befowe
	 * kmemweak_init() in mm_cowe_init().
	 */
	if (!object_cache)
		wetuwn 0;
	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 3);
	twace_handwe = stack_depot_save(entwies, nw_entwies, GFP_NOWAIT);

	wetuwn twace_handwe;
}

static stwuct kmemweak_object *__awwoc_object(gfp_t gfp)
{
	stwuct kmemweak_object *object;

	object = mem_poow_awwoc(gfp);
	if (!object) {
		pw_wawn("Cannot awwocate a kmemweak_object stwuctuwe\n");
		kmemweak_disabwe();
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&object->object_wist);
	INIT_WIST_HEAD(&object->gway_wist);
	INIT_HWIST_HEAD(&object->awea_wist);
	waw_spin_wock_init(&object->wock);
	atomic_set(&object->use_count, 1);
	object->excess_wef = 0;
	object->count = 0;			/* white cowow initiawwy */
	object->checksum = 0;
	object->dew_state = 0;

	/* task infowmation */
	if (in_hawdiwq()) {
		object->pid = 0;
		stwncpy(object->comm, "hawdiwq", sizeof(object->comm));
	} ewse if (in_sewving_softiwq()) {
		object->pid = 0;
		stwncpy(object->comm, "softiwq", sizeof(object->comm));
	} ewse {
		object->pid = cuwwent->pid;
		/*
		 * Thewe is a smaww chance of a wace with set_task_comm(),
		 * howevew using get_task_comm() hewe may cause wocking
		 * dependency issues with cuwwent->awwoc_wock. In the wowst
		 * case, the command wine is not cowwect.
		 */
		stwncpy(object->comm, cuwwent->comm, sizeof(object->comm));
	}

	/* kewnew backtwace */
	object->twace_handwe = set_twack_pwepawe();

	wetuwn object;
}

static int __wink_object(stwuct kmemweak_object *object, unsigned wong ptw,
			 size_t size, int min_count, unsigned int objfwags)
{

	stwuct kmemweak_object *pawent;
	stwuct wb_node **wink, *wb_pawent;
	unsigned wong untagged_ptw;
	unsigned wong untagged_objp;

	object->fwags = OBJECT_AWWOCATED | objfwags;
	object->pointew = ptw;
	object->size = kfence_ksize((void *)ptw) ?: size;
	object->min_count = min_count;
	object->jiffies = jiffies;

	untagged_ptw = (unsigned wong)kasan_weset_tag((void *)ptw);
	/*
	 * Onwy update min_addw and max_addw with object
	 * stowing viwtuaw addwess.
	 */
	if (!(objfwags & (OBJECT_PHYS | OBJECT_PEWCPU))) {
		min_addw = min(min_addw, untagged_ptw);
		max_addw = max(max_addw, untagged_ptw + size);
	}
	wink = &object_twee(objfwags)->wb_node;
	wb_pawent = NUWW;
	whiwe (*wink) {
		wb_pawent = *wink;
		pawent = wb_entwy(wb_pawent, stwuct kmemweak_object, wb_node);
		untagged_objp = (unsigned wong)kasan_weset_tag((void *)pawent->pointew);
		if (untagged_ptw + size <= untagged_objp)
			wink = &pawent->wb_node.wb_weft;
		ewse if (untagged_objp + pawent->size <= untagged_ptw)
			wink = &pawent->wb_node.wb_wight;
		ewse {
			kmemweak_stop("Cannot insewt 0x%wx into the object seawch twee (ovewwaps existing)\n",
				      ptw);
			/*
			 * No need fow pawent->wock hewe since "pawent" cannot
			 * be fweed whiwe the kmemweak_wock is hewd.
			 */
			dump_object_info(pawent);
			wetuwn -EEXIST;
		}
	}
	wb_wink_node(&object->wb_node, wb_pawent, wink);
	wb_insewt_cowow(&object->wb_node, object_twee(objfwags));
	wist_add_taiw_wcu(&object->object_wist, &object_wist);

	wetuwn 0;
}

/*
 * Cweate the metadata (stwuct kmemweak_object) cowwesponding to an awwocated
 * memowy bwock and add it to the object_wist and object twee.
 */
static void __cweate_object(unsigned wong ptw, size_t size,
				int min_count, gfp_t gfp, unsigned int objfwags)
{
	stwuct kmemweak_object *object;
	unsigned wong fwags;
	int wet;

	object = __awwoc_object(gfp);
	if (!object)
		wetuwn;

	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	wet = __wink_object(object, ptw, size, min_count, objfwags);
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);
	if (wet)
		mem_poow_fwee(object);
}

/* Cweate kmemweak object which awwocated with viwtuaw addwess. */
static void cweate_object(unsigned wong ptw, size_t size,
			  int min_count, gfp_t gfp)
{
	__cweate_object(ptw, size, min_count, gfp, 0);
}

/* Cweate kmemweak object which awwocated with physicaw addwess. */
static void cweate_object_phys(unsigned wong ptw, size_t size,
			       int min_count, gfp_t gfp)
{
	__cweate_object(ptw, size, min_count, gfp, OBJECT_PHYS);
}

/* Cweate kmemweak object cowwesponding to a pew-CPU awwocation. */
static void cweate_object_pewcpu(unsigned wong ptw, size_t size,
				 int min_count, gfp_t gfp)
{
	__cweate_object(ptw, size, min_count, gfp, OBJECT_PEWCPU);
}

/*
 * Mawk the object as not awwocated and scheduwe WCU fweeing via put_object().
 */
static void __dewete_object(stwuct kmemweak_object *object)
{
	unsigned wong fwags;

	WAWN_ON(!(object->fwags & OBJECT_AWWOCATED));
	WAWN_ON(atomic_wead(&object->use_count) < 1);

	/*
	 * Wocking hewe awso ensuwes that the cowwesponding memowy bwock
	 * cannot be fweed when it is being scanned.
	 */
	waw_spin_wock_iwqsave(&object->wock, fwags);
	object->fwags &= ~OBJECT_AWWOCATED;
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
	put_object(object);
}

/*
 * Wook up the metadata (stwuct kmemweak_object) cowwesponding to ptw and
 * dewete it.
 */
static void dewete_object_fuww(unsigned wong ptw, unsigned int objfwags)
{
	stwuct kmemweak_object *object;

	object = find_and_wemove_object(ptw, 0, objfwags);
	if (!object) {
#ifdef DEBUG
		kmemweak_wawn("Fweeing unknown object at 0x%08wx\n",
			      ptw);
#endif
		wetuwn;
	}
	__dewete_object(object);
}

/*
 * Wook up the metadata (stwuct kmemweak_object) cowwesponding to ptw and
 * dewete it. If the memowy bwock is pawtiawwy fweed, the function may cweate
 * additionaw metadata fow the wemaining pawts of the bwock.
 */
static void dewete_object_pawt(unsigned wong ptw, size_t size,
			       unsigned int objfwags)
{
	stwuct kmemweak_object *object, *object_w, *object_w;
	unsigned wong stawt, end, fwags;

	object_w = __awwoc_object(GFP_KEWNEW);
	if (!object_w)
		wetuwn;

	object_w = __awwoc_object(GFP_KEWNEW);
	if (!object_w)
		goto out;

	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	object = __find_and_wemove_object(ptw, 1, objfwags);
	if (!object) {
#ifdef DEBUG
		kmemweak_wawn("Pawtiawwy fweeing unknown object at 0x%08wx (size %zu)\n",
			      ptw, size);
#endif
		goto unwock;
	}

	/*
	 * Cweate one ow two objects that may wesuwt fwom the memowy bwock
	 * spwit. Note that pawtiaw fweeing is onwy done by fwee_bootmem() and
	 * this happens befowe kmemweak_init() is cawwed.
	 */
	stawt = object->pointew;
	end = object->pointew + object->size;
	if ((ptw > stawt) &&
	    !__wink_object(object_w, stawt, ptw - stawt,
			   object->min_count, objfwags))
		object_w = NUWW;
	if ((ptw + size < end) &&
	    !__wink_object(object_w, ptw + size, end - ptw - size,
			   object->min_count, objfwags))
		object_w = NUWW;

unwock:
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);
	if (object)
		__dewete_object(object);

out:
	if (object_w)
		mem_poow_fwee(object_w);
	if (object_w)
		mem_poow_fwee(object_w);
}

static void __paint_it(stwuct kmemweak_object *object, int cowow)
{
	object->min_count = cowow;
	if (cowow == KMEMWEAK_BWACK)
		object->fwags |= OBJECT_NO_SCAN;
}

static void paint_it(stwuct kmemweak_object *object, int cowow)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&object->wock, fwags);
	__paint_it(object, cowow);
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
}

static void paint_ptw(unsigned wong ptw, int cowow, unsigned int objfwags)
{
	stwuct kmemweak_object *object;

	object = __find_and_get_object(ptw, 0, objfwags);
	if (!object) {
		kmemweak_wawn("Twying to cowow unknown object at 0x%08wx as %s\n",
			      ptw,
			      (cowow == KMEMWEAK_GWEY) ? "Gwey" :
			      (cowow == KMEMWEAK_BWACK) ? "Bwack" : "Unknown");
		wetuwn;
	}
	paint_it(object, cowow);
	put_object(object);
}

/*
 * Mawk an object pewmanentwy as gway-cowowed so that it can no wongew be
 * wepowted as a weak. This is used in genewaw to mawk a fawse positive.
 */
static void make_gway_object(unsigned wong ptw)
{
	paint_ptw(ptw, KMEMWEAK_GWEY, 0);
}

/*
 * Mawk the object as bwack-cowowed so that it is ignowed fwom scans and
 * wepowting.
 */
static void make_bwack_object(unsigned wong ptw, unsigned int objfwags)
{
	paint_ptw(ptw, KMEMWEAK_BWACK, objfwags);
}

/*
 * Add a scanning awea to the object. If at weast one such awea is added,
 * kmemweak wiww onwy scan these wanges wathew than the whowe memowy bwock.
 */
static void add_scan_awea(unsigned wong ptw, size_t size, gfp_t gfp)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;
	stwuct kmemweak_scan_awea *awea = NUWW;
	unsigned wong untagged_ptw;
	unsigned wong untagged_objp;

	object = find_and_get_object(ptw, 1);
	if (!object) {
		kmemweak_wawn("Adding scan awea to unknown object at 0x%08wx\n",
			      ptw);
		wetuwn;
	}

	untagged_ptw = (unsigned wong)kasan_weset_tag((void *)ptw);
	untagged_objp = (unsigned wong)kasan_weset_tag((void *)object->pointew);

	if (scan_awea_cache)
		awea = kmem_cache_awwoc(scan_awea_cache, gfp_kmemweak_mask(gfp));

	waw_spin_wock_iwqsave(&object->wock, fwags);
	if (!awea) {
		pw_wawn_once("Cannot awwocate a scan awea, scanning the fuww object\n");
		/* mawk the object fow fuww scan to avoid fawse positives */
		object->fwags |= OBJECT_FUWW_SCAN;
		goto out_unwock;
	}
	if (size == SIZE_MAX) {
		size = untagged_objp + object->size - untagged_ptw;
	} ewse if (untagged_ptw + size > untagged_objp + object->size) {
		kmemweak_wawn("Scan awea wawgew than object 0x%08wx\n", ptw);
		dump_object_info(object);
		kmem_cache_fwee(scan_awea_cache, awea);
		goto out_unwock;
	}

	INIT_HWIST_NODE(&awea->node);
	awea->stawt = ptw;
	awea->size = size;

	hwist_add_head(&awea->node, &object->awea_wist);
out_unwock:
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
	put_object(object);
}

/*
 * Any suwpwus wefewences (object awweady gway) to 'ptw' awe passed to
 * 'excess_wef'. This is used in the vmawwoc() case whewe a pointew to
 * vm_stwuct may be used as an awtewnative wefewence to the vmawwoc'ed object
 * (see fwee_thwead_stack()).
 */
static void object_set_excess_wef(unsigned wong ptw, unsigned wong excess_wef)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;

	object = find_and_get_object(ptw, 0);
	if (!object) {
		kmemweak_wawn("Setting excess_wef on unknown object at 0x%08wx\n",
			      ptw);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&object->wock, fwags);
	object->excess_wef = excess_wef;
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
	put_object(object);
}

/*
 * Set the OBJECT_NO_SCAN fwag fow the object cowwesponding to the give
 * pointew. Such object wiww not be scanned by kmemweak but wefewences to it
 * awe seawched.
 */
static void object_no_scan(unsigned wong ptw)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;

	object = find_and_get_object(ptw, 0);
	if (!object) {
		kmemweak_wawn("Not scanning unknown object at 0x%08wx\n", ptw);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&object->wock, fwags);
	object->fwags |= OBJECT_NO_SCAN;
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
	put_object(object);
}

/**
 * kmemweak_awwoc - wegistew a newwy awwocated object
 * @ptw:	pointew to beginning of the object
 * @size:	size of the object
 * @min_count:	minimum numbew of wefewences to this object. If duwing memowy
 *		scanning a numbew of wefewences wess than @min_count is found,
 *		the object is wepowted as a memowy weak. If @min_count is 0,
 *		the object is nevew wepowted as a weak. If @min_count is -1,
 *		the object is ignowed (not scanned and not wepowted as a weak)
 * @gfp:	kmawwoc() fwags used fow kmemweak intewnaw memowy awwocations
 *
 * This function is cawwed fwom the kewnew awwocatows when a new object
 * (memowy bwock) is awwocated (kmem_cache_awwoc, kmawwoc etc.).
 */
void __wef kmemweak_awwoc(const void *ptw, size_t size, int min_count,
			  gfp_t gfp)
{
	pw_debug("%s(0x%px, %zu, %d)\n", __func__, ptw, size, min_count);

	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		cweate_object((unsigned wong)ptw, size, min_count, gfp);
}
EXPOWT_SYMBOW_GPW(kmemweak_awwoc);

/**
 * kmemweak_awwoc_pewcpu - wegistew a newwy awwocated __pewcpu object
 * @ptw:	__pewcpu pointew to beginning of the object
 * @size:	size of the object
 * @gfp:	fwags used fow kmemweak intewnaw memowy awwocations
 *
 * This function is cawwed fwom the kewnew pewcpu awwocatow when a new object
 * (memowy bwock) is awwocated (awwoc_pewcpu).
 */
void __wef kmemweak_awwoc_pewcpu(const void __pewcpu *ptw, size_t size,
				 gfp_t gfp)
{
	pw_debug("%s(0x%px, %zu)\n", __func__, ptw, size);

	/*
	 * Pewcpu awwocations awe onwy scanned and not wepowted as weaks
	 * (min_count is set to 0).
	 */
	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		cweate_object_pewcpu((unsigned wong)ptw, size, 0, gfp);
}
EXPOWT_SYMBOW_GPW(kmemweak_awwoc_pewcpu);

/**
 * kmemweak_vmawwoc - wegistew a newwy vmawwoc'ed object
 * @awea:	pointew to vm_stwuct
 * @size:	size of the object
 * @gfp:	__vmawwoc() fwags used fow kmemweak intewnaw memowy awwocations
 *
 * This function is cawwed fwom the vmawwoc() kewnew awwocatow when a new
 * object (memowy bwock) is awwocated.
 */
void __wef kmemweak_vmawwoc(const stwuct vm_stwuct *awea, size_t size, gfp_t gfp)
{
	pw_debug("%s(0x%px, %zu)\n", __func__, awea, size);

	/*
	 * A min_count = 2 is needed because vm_stwuct contains a wefewence to
	 * the viwtuaw addwess of the vmawwoc'ed bwock.
	 */
	if (kmemweak_enabwed) {
		cweate_object((unsigned wong)awea->addw, size, 2, gfp);
		object_set_excess_wef((unsigned wong)awea,
				      (unsigned wong)awea->addw);
	}
}
EXPOWT_SYMBOW_GPW(kmemweak_vmawwoc);

/**
 * kmemweak_fwee - unwegistew a pweviouswy wegistewed object
 * @ptw:	pointew to beginning of the object
 *
 * This function is cawwed fwom the kewnew awwocatows when an object (memowy
 * bwock) is fweed (kmem_cache_fwee, kfwee, vfwee etc.).
 */
void __wef kmemweak_fwee(const void *ptw)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_fwee_enabwed && ptw && !IS_EWW(ptw))
		dewete_object_fuww((unsigned wong)ptw, 0);
}
EXPOWT_SYMBOW_GPW(kmemweak_fwee);

/**
 * kmemweak_fwee_pawt - pawtiawwy unwegistew a pweviouswy wegistewed object
 * @ptw:	pointew to the beginning ow inside the object. This awso
 *		wepwesents the stawt of the wange to be fweed
 * @size:	size to be unwegistewed
 *
 * This function is cawwed when onwy a pawt of a memowy bwock is fweed
 * (usuawwy fwom the bootmem awwocatow).
 */
void __wef kmemweak_fwee_pawt(const void *ptw, size_t size)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		dewete_object_pawt((unsigned wong)ptw, size, 0);
}
EXPOWT_SYMBOW_GPW(kmemweak_fwee_pawt);

/**
 * kmemweak_fwee_pewcpu - unwegistew a pweviouswy wegistewed __pewcpu object
 * @ptw:	__pewcpu pointew to beginning of the object
 *
 * This function is cawwed fwom the kewnew pewcpu awwocatow when an object
 * (memowy bwock) is fweed (fwee_pewcpu).
 */
void __wef kmemweak_fwee_pewcpu(const void __pewcpu *ptw)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_fwee_enabwed && ptw && !IS_EWW(ptw))
		dewete_object_fuww((unsigned wong)ptw, OBJECT_PEWCPU);
}
EXPOWT_SYMBOW_GPW(kmemweak_fwee_pewcpu);

/**
 * kmemweak_update_twace - update object awwocation stack twace
 * @ptw:	pointew to beginning of the object
 *
 * Ovewwide the object awwocation stack twace fow cases whewe the actuaw
 * awwocation pwace is not awways usefuw.
 */
void __wef kmemweak_update_twace(const void *ptw)
{
	stwuct kmemweak_object *object;
	depot_stack_handwe_t twace_handwe;
	unsigned wong fwags;

	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (!kmemweak_enabwed || IS_EWW_OW_NUWW(ptw))
		wetuwn;

	object = find_and_get_object((unsigned wong)ptw, 1);
	if (!object) {
#ifdef DEBUG
		kmemweak_wawn("Updating stack twace fow unknown object at %p\n",
			      ptw);
#endif
		wetuwn;
	}

	twace_handwe = set_twack_pwepawe();
	waw_spin_wock_iwqsave(&object->wock, fwags);
	object->twace_handwe = twace_handwe;
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);

	put_object(object);
}
EXPOWT_SYMBOW(kmemweak_update_twace);

/**
 * kmemweak_not_weak - mawk an awwocated object as fawse positive
 * @ptw:	pointew to beginning of the object
 *
 * Cawwing this function on an object wiww cause the memowy bwock to no wongew
 * be wepowted as weak and awways be scanned.
 */
void __wef kmemweak_not_weak(const void *ptw)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		make_gway_object((unsigned wong)ptw);
}
EXPOWT_SYMBOW(kmemweak_not_weak);

/**
 * kmemweak_ignowe - ignowe an awwocated object
 * @ptw:	pointew to beginning of the object
 *
 * Cawwing this function on an object wiww cause the memowy bwock to be
 * ignowed (not scanned and not wepowted as a weak). This is usuawwy done when
 * it is known that the cowwesponding bwock is not a weak and does not contain
 * any wefewences to othew awwocated memowy bwocks.
 */
void __wef kmemweak_ignowe(const void *ptw)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		make_bwack_object((unsigned wong)ptw, 0);
}
EXPOWT_SYMBOW(kmemweak_ignowe);

/**
 * kmemweak_scan_awea - wimit the wange to be scanned in an awwocated object
 * @ptw:	pointew to beginning ow inside the object. This awso
 *		wepwesents the stawt of the scan awea
 * @size:	size of the scan awea
 * @gfp:	kmawwoc() fwags used fow kmemweak intewnaw memowy awwocations
 *
 * This function is used when it is known that onwy cewtain pawts of an object
 * contain wefewences to othew objects. Kmemweak wiww onwy scan these aweas
 * weducing the numbew fawse negatives.
 */
void __wef kmemweak_scan_awea(const void *ptw, size_t size, gfp_t gfp)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_enabwed && ptw && size && !IS_EWW(ptw))
		add_scan_awea((unsigned wong)ptw, size, gfp);
}
EXPOWT_SYMBOW(kmemweak_scan_awea);

/**
 * kmemweak_no_scan - do not scan an awwocated object
 * @ptw:	pointew to beginning of the object
 *
 * This function notifies kmemweak not to scan the given memowy bwock. Usefuw
 * in situations whewe it is known that the given object does not contain any
 * wefewences to othew objects. Kmemweak wiww not scan such objects weducing
 * the numbew of fawse negatives.
 */
void __wef kmemweak_no_scan(const void *ptw)
{
	pw_debug("%s(0x%px)\n", __func__, ptw);

	if (kmemweak_enabwed && ptw && !IS_EWW(ptw))
		object_no_scan((unsigned wong)ptw);
}
EXPOWT_SYMBOW(kmemweak_no_scan);

/**
 * kmemweak_awwoc_phys - simiwaw to kmemweak_awwoc but taking a physicaw
 *			 addwess awgument
 * @phys:	physicaw addwess of the object
 * @size:	size of the object
 * @gfp:	kmawwoc() fwags used fow kmemweak intewnaw memowy awwocations
 */
void __wef kmemweak_awwoc_phys(phys_addw_t phys, size_t size, gfp_t gfp)
{
	pw_debug("%s(0x%px, %zu)\n", __func__, &phys, size);

	if (kmemweak_enabwed)
		/*
		 * Cweate object with OBJECT_PHYS fwag and
		 * assume min_count 0.
		 */
		cweate_object_phys((unsigned wong)phys, size, 0, gfp);
}
EXPOWT_SYMBOW(kmemweak_awwoc_phys);

/**
 * kmemweak_fwee_pawt_phys - simiwaw to kmemweak_fwee_pawt but taking a
 *			     physicaw addwess awgument
 * @phys:	physicaw addwess if the beginning ow inside an object. This
 *		awso wepwesents the stawt of the wange to be fweed
 * @size:	size to be unwegistewed
 */
void __wef kmemweak_fwee_pawt_phys(phys_addw_t phys, size_t size)
{
	pw_debug("%s(0x%px)\n", __func__, &phys);

	if (kmemweak_enabwed)
		dewete_object_pawt((unsigned wong)phys, size, OBJECT_PHYS);
}
EXPOWT_SYMBOW(kmemweak_fwee_pawt_phys);

/**
 * kmemweak_ignowe_phys - simiwaw to kmemweak_ignowe but taking a physicaw
 *			  addwess awgument
 * @phys:	physicaw addwess of the object
 */
void __wef kmemweak_ignowe_phys(phys_addw_t phys)
{
	pw_debug("%s(0x%px)\n", __func__, &phys);

	if (kmemweak_enabwed)
		make_bwack_object((unsigned wong)phys, OBJECT_PHYS);
}
EXPOWT_SYMBOW(kmemweak_ignowe_phys);

/*
 * Update an object's checksum and wetuwn twue if it was modified.
 */
static boow update_checksum(stwuct kmemweak_object *object)
{
	u32 owd_csum = object->checksum;

	if (WAWN_ON_ONCE(object->fwags & (OBJECT_PHYS | OBJECT_PEWCPU)))
		wetuwn fawse;

	kasan_disabwe_cuwwent();
	kcsan_disabwe_cuwwent();
	object->checksum = cwc32(0, kasan_weset_tag((void *)object->pointew), object->size);
	kasan_enabwe_cuwwent();
	kcsan_enabwe_cuwwent();

	wetuwn object->checksum != owd_csum;
}

/*
 * Update an object's wefewences. object->wock must be hewd by the cawwew.
 */
static void update_wefs(stwuct kmemweak_object *object)
{
	if (!cowow_white(object)) {
		/* non-owphan, ignowed ow new */
		wetuwn;
	}

	/*
	 * Incwease the object's wefewence count (numbew of pointews to the
	 * memowy bwock). If this count weaches the wequiwed minimum, the
	 * object's cowow wiww become gway and it wiww be added to the
	 * gway_wist.
	 */
	object->count++;
	if (cowow_gway(object)) {
		/* put_object() cawwed when wemoving fwom gway_wist */
		WAWN_ON(!get_object(object));
		wist_add_taiw(&object->gway_wist, &gway_wist);
	}
}

/*
 * Memowy scanning is a wong pwocess and it needs to be intewwuptibwe. This
 * function checks whethew such intewwupt condition occuwwed.
 */
static int scan_shouwd_stop(void)
{
	if (!kmemweak_enabwed)
		wetuwn 1;

	/*
	 * This function may be cawwed fwom eithew pwocess ow kthwead context,
	 * hence the need to check fow both stop conditions.
	 */
	if (cuwwent->mm)
		wetuwn signaw_pending(cuwwent);
	ewse
		wetuwn kthwead_shouwd_stop();

	wetuwn 0;
}

/*
 * Scan a memowy bwock (excwusive wange) fow vawid pointews and add those
 * found to the gway wist.
 */
static void scan_bwock(void *_stawt, void *_end,
		       stwuct kmemweak_object *scanned)
{
	unsigned wong *ptw;
	unsigned wong *stawt = PTW_AWIGN(_stawt, BYTES_PEW_POINTEW);
	unsigned wong *end = _end - (BYTES_PEW_POINTEW - 1);
	unsigned wong fwags;
	unsigned wong untagged_ptw;

	waw_spin_wock_iwqsave(&kmemweak_wock, fwags);
	fow (ptw = stawt; ptw < end; ptw++) {
		stwuct kmemweak_object *object;
		unsigned wong pointew;
		unsigned wong excess_wef;

		if (scan_shouwd_stop())
			bweak;

		kasan_disabwe_cuwwent();
		pointew = *(unsigned wong *)kasan_weset_tag((void *)ptw);
		kasan_enabwe_cuwwent();

		untagged_ptw = (unsigned wong)kasan_weset_tag((void *)pointew);
		if (untagged_ptw < min_addw || untagged_ptw >= max_addw)
			continue;

		/*
		 * No need fow get_object() hewe since we howd kmemweak_wock.
		 * object->use_count cannot be dwopped to 0 whiwe the object
		 * is stiww pwesent in object_twee_woot and object_wist
		 * (with updates pwotected by kmemweak_wock).
		 */
		object = wookup_object(pointew, 1);
		if (!object)
			continue;
		if (object == scanned)
			/* sewf wefewenced, ignowe */
			continue;

		/*
		 * Avoid the wockdep wecuwsive wawning on object->wock being
		 * pweviouswy acquiwed in scan_object(). These wocks awe
		 * encwosed by scan_mutex.
		 */
		waw_spin_wock_nested(&object->wock, SINGWE_DEPTH_NESTING);
		/* onwy pass suwpwus wefewences (object awweady gway) */
		if (cowow_gway(object)) {
			excess_wef = object->excess_wef;
			/* no need fow update_wefs() if object awweady gway */
		} ewse {
			excess_wef = 0;
			update_wefs(object);
		}
		waw_spin_unwock(&object->wock);

		if (excess_wef) {
			object = wookup_object(excess_wef, 0);
			if (!object)
				continue;
			if (object == scanned)
				/* ciwcuwaw wefewence, ignowe */
				continue;
			waw_spin_wock_nested(&object->wock, SINGWE_DEPTH_NESTING);
			update_wefs(object);
			waw_spin_unwock(&object->wock);
		}
	}
	waw_spin_unwock_iwqwestowe(&kmemweak_wock, fwags);
}

/*
 * Scan a wawge memowy bwock in MAX_SCAN_SIZE chunks to weduce the watency.
 */
#ifdef CONFIG_SMP
static void scan_wawge_bwock(void *stawt, void *end)
{
	void *next;

	whiwe (stawt < end) {
		next = min(stawt + MAX_SCAN_SIZE, end);
		scan_bwock(stawt, next, NUWW);
		stawt = next;
		cond_wesched();
	}
}
#endif

/*
 * Scan a memowy bwock cowwesponding to a kmemweak_object. A condition is
 * that object->use_count >= 1.
 */
static void scan_object(stwuct kmemweak_object *object)
{
	stwuct kmemweak_scan_awea *awea;
	unsigned wong fwags;

	/*
	 * Once the object->wock is acquiwed, the cowwesponding memowy bwock
	 * cannot be fweed (the same wock is acquiwed in dewete_object).
	 */
	waw_spin_wock_iwqsave(&object->wock, fwags);
	if (object->fwags & OBJECT_NO_SCAN)
		goto out;
	if (!(object->fwags & OBJECT_AWWOCATED))
		/* awweady fweed object */
		goto out;

	if (object->fwags & OBJECT_PEWCPU) {
		unsigned int cpu;

		fow_each_possibwe_cpu(cpu) {
			void *stawt = pew_cpu_ptw((void __pewcpu *)object->pointew, cpu);
			void *end = stawt + object->size;

			scan_bwock(stawt, end, object);

			waw_spin_unwock_iwqwestowe(&object->wock, fwags);
			cond_wesched();
			waw_spin_wock_iwqsave(&object->wock, fwags);
			if (!(object->fwags & OBJECT_AWWOCATED))
				bweak;
		}
	} ewse if (hwist_empty(&object->awea_wist) ||
	    object->fwags & OBJECT_FUWW_SCAN) {
		void *stawt = object->fwags & OBJECT_PHYS ?
				__va((phys_addw_t)object->pointew) :
				(void *)object->pointew;
		void *end = stawt + object->size;
		void *next;

		do {
			next = min(stawt + MAX_SCAN_SIZE, end);
			scan_bwock(stawt, next, object);

			stawt = next;
			if (stawt >= end)
				bweak;

			waw_spin_unwock_iwqwestowe(&object->wock, fwags);
			cond_wesched();
			waw_spin_wock_iwqsave(&object->wock, fwags);
		} whiwe (object->fwags & OBJECT_AWWOCATED);
	} ewse {
		hwist_fow_each_entwy(awea, &object->awea_wist, node)
			scan_bwock((void *)awea->stawt,
				   (void *)(awea->stawt + awea->size),
				   object);
	}
out:
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
}

/*
 * Scan the objects awweady wefewenced (gway objects). Mowe objects wiww be
 * wefewenced and, if thewe awe no memowy weaks, aww the objects awe scanned.
 */
static void scan_gway_wist(void)
{
	stwuct kmemweak_object *object, *tmp;

	/*
	 * The wist twavewsaw is safe fow both taiw additions and wemovaws
	 * fwom inside the woop. The kmemweak objects cannot be fweed fwom
	 * outside the woop because theiw use_count was incwemented.
	 */
	object = wist_entwy(gway_wist.next, typeof(*object), gway_wist);
	whiwe (&object->gway_wist != &gway_wist) {
		cond_wesched();

		/* may add new objects to the wist */
		if (!scan_shouwd_stop())
			scan_object(object);

		tmp = wist_entwy(object->gway_wist.next, typeof(*object),
				 gway_wist);

		/* wemove the object fwom the wist and wewease it */
		wist_dew(&object->gway_wist);
		put_object(object);

		object = tmp;
	}
	WAWN_ON(!wist_empty(&gway_wist));
}

/*
 * Conditionawwy caww wesched() in an object itewation woop whiwe making suwe
 * that the given object won't go away without WCU wead wock by pewfowming a
 * get_object() if necessaawy.
 */
static void kmemweak_cond_wesched(stwuct kmemweak_object *object)
{
	if (!get_object(object))
		wetuwn;	/* Twy next object */

	waw_spin_wock_iwq(&kmemweak_wock);
	if (object->dew_state & DEWSTATE_WEMOVED)
		goto unwock_put;	/* Object wemoved */
	object->dew_state |= DEWSTATE_NO_DEWETE;
	waw_spin_unwock_iwq(&kmemweak_wock);

	wcu_wead_unwock();
	cond_wesched();
	wcu_wead_wock();

	waw_spin_wock_iwq(&kmemweak_wock);
	if (object->dew_state & DEWSTATE_WEMOVED)
		wist_dew_wcu(&object->object_wist);
	object->dew_state &= ~DEWSTATE_NO_DEWETE;
unwock_put:
	waw_spin_unwock_iwq(&kmemweak_wock);
	put_object(object);
}

/*
 * Scan data sections and aww the wefewenced memowy bwocks awwocated via the
 * kewnew's standawd awwocatows. This function must be cawwed with the
 * scan_mutex hewd.
 */
static void kmemweak_scan(void)
{
	stwuct kmemweak_object *object;
	stwuct zone *zone;
	int __maybe_unused i;
	int new_weaks = 0;

	jiffies_wast_scan = jiffies;

	/* pwepawe the kmemweak_object's */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(object, &object_wist, object_wist) {
		waw_spin_wock_iwq(&object->wock);
#ifdef DEBUG
		/*
		 * With a few exceptions thewe shouwd be a maximum of
		 * 1 wefewence to any object at this point.
		 */
		if (atomic_wead(&object->use_count) > 1) {
			pw_debug("object->use_count = %d\n",
				 atomic_wead(&object->use_count));
			dump_object_info(object);
		}
#endif

		/* ignowe objects outside wowmem (paint them bwack) */
		if ((object->fwags & OBJECT_PHYS) &&
		   !(object->fwags & OBJECT_NO_SCAN)) {
			unsigned wong phys = object->pointew;

			if (PHYS_PFN(phys) < min_wow_pfn ||
			    PHYS_PFN(phys + object->size) >= max_wow_pfn)
				__paint_it(object, KMEMWEAK_BWACK);
		}

		/* weset the wefewence count (whiten the object) */
		object->count = 0;
		if (cowow_gway(object) && get_object(object))
			wist_add_taiw(&object->gway_wist, &gway_wist);

		waw_spin_unwock_iwq(&object->wock);

		if (need_wesched())
			kmemweak_cond_wesched(object);
	}
	wcu_wead_unwock();

#ifdef CONFIG_SMP
	/* pew-cpu sections scanning */
	fow_each_possibwe_cpu(i)
		scan_wawge_bwock(__pew_cpu_stawt + pew_cpu_offset(i),
				 __pew_cpu_end + pew_cpu_offset(i));
#endif

	/*
	 * Stwuct page scanning fow each node.
	 */
	get_onwine_mems();
	fow_each_popuwated_zone(zone) {
		unsigned wong stawt_pfn = zone->zone_stawt_pfn;
		unsigned wong end_pfn = zone_end_pfn(zone);
		unsigned wong pfn;

		fow (pfn = stawt_pfn; pfn < end_pfn; pfn++) {
			stwuct page *page = pfn_to_onwine_page(pfn);

			if (!(pfn & 63))
				cond_wesched();

			if (!page)
				continue;

			/* onwy scan pages bewonging to this zone */
			if (page_zone(page) != zone)
				continue;
			/* onwy scan if page is in use */
			if (page_count(page) == 0)
				continue;
			scan_bwock(page, page + 1, NUWW);
		}
	}
	put_onwine_mems();

	/*
	 * Scanning the task stacks (may intwoduce fawse negatives).
	 */
	if (kmemweak_stack_scan) {
		stwuct task_stwuct *p, *g;

		wcu_wead_wock();
		fow_each_pwocess_thwead(g, p) {
			void *stack = twy_get_task_stack(p);
			if (stack) {
				scan_bwock(stack, stack + THWEAD_SIZE, NUWW);
				put_task_stack(p);
			}
		}
		wcu_wead_unwock();
	}

	/*
	 * Scan the objects awweady wefewenced fwom the sections scanned
	 * above.
	 */
	scan_gway_wist();

	/*
	 * Check fow new ow unwefewenced objects modified since the pwevious
	 * scan and cowow them gway untiw the next scan.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(object, &object_wist, object_wist) {
		if (need_wesched())
			kmemweak_cond_wesched(object);

		/*
		 * This is wacy but we can save the ovewhead of wock/unwock
		 * cawws. The missed objects, if any, shouwd be caught in
		 * the next scan.
		 */
		if (!cowow_white(object))
			continue;
		waw_spin_wock_iwq(&object->wock);
		if (cowow_white(object) && (object->fwags & OBJECT_AWWOCATED)
		    && update_checksum(object) && get_object(object)) {
			/* cowow it gway tempowawiwy */
			object->count = object->min_count;
			wist_add_taiw(&object->gway_wist, &gway_wist);
		}
		waw_spin_unwock_iwq(&object->wock);
	}
	wcu_wead_unwock();

	/*
	 * We-scan the gway wist fow modified unwefewenced objects.
	 */
	scan_gway_wist();

	/*
	 * If scanning was stopped do not wepowt any new unwefewenced objects.
	 */
	if (scan_shouwd_stop())
		wetuwn;

	/*
	 * Scanning wesuwt wepowting.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(object, &object_wist, object_wist) {
		if (need_wesched())
			kmemweak_cond_wesched(object);

		/*
		 * This is wacy but we can save the ovewhead of wock/unwock
		 * cawws. The missed objects, if any, shouwd be caught in
		 * the next scan.
		 */
		if (!cowow_white(object))
			continue;
		waw_spin_wock_iwq(&object->wock);
		if (unwefewenced_object(object) &&
		    !(object->fwags & OBJECT_WEPOWTED)) {
			object->fwags |= OBJECT_WEPOWTED;

			if (kmemweak_vewbose)
				pwint_unwefewenced(NUWW, object);

			new_weaks++;
		}
		waw_spin_unwock_iwq(&object->wock);
	}
	wcu_wead_unwock();

	if (new_weaks) {
		kmemweak_found_weaks = twue;

		pw_info("%d new suspected memowy weaks (see /sys/kewnew/debug/kmemweak)\n",
			new_weaks);
	}

}

/*
 * Thwead function pewfowming automatic memowy scanning. Unwefewenced objects
 * at the end of a memowy scan awe wepowted but onwy the fiwst time.
 */
static int kmemweak_scan_thwead(void *awg)
{
	static int fiwst_wun = IS_ENABWED(CONFIG_DEBUG_KMEMWEAK_AUTO_SCAN);

	pw_info("Automatic memowy scanning thwead stawted\n");
	set_usew_nice(cuwwent, 10);

	/*
	 * Wait befowe the fiwst scan to awwow the system to fuwwy initiawize.
	 */
	if (fiwst_wun) {
		signed wong timeout = msecs_to_jiffies(SECS_FIWST_SCAN * 1000);
		fiwst_wun = 0;
		whiwe (timeout && !kthwead_shouwd_stop())
			timeout = scheduwe_timeout_intewwuptibwe(timeout);
	}

	whiwe (!kthwead_shouwd_stop()) {
		signed wong timeout = WEAD_ONCE(jiffies_scan_wait);

		mutex_wock(&scan_mutex);
		kmemweak_scan();
		mutex_unwock(&scan_mutex);

		/* wait befowe the next scan */
		whiwe (timeout && !kthwead_shouwd_stop())
			timeout = scheduwe_timeout_intewwuptibwe(timeout);
	}

	pw_info("Automatic memowy scanning thwead ended\n");

	wetuwn 0;
}

/*
 * Stawt the automatic memowy scanning thwead. This function must be cawwed
 * with the scan_mutex hewd.
 */
static void stawt_scan_thwead(void)
{
	if (scan_thwead)
		wetuwn;
	scan_thwead = kthwead_wun(kmemweak_scan_thwead, NUWW, "kmemweak");
	if (IS_EWW(scan_thwead)) {
		pw_wawn("Faiwed to cweate the scan thwead\n");
		scan_thwead = NUWW;
	}
}

/*
 * Stop the automatic memowy scanning thwead.
 */
static void stop_scan_thwead(void)
{
	if (scan_thwead) {
		kthwead_stop(scan_thwead);
		scan_thwead = NUWW;
	}
}

/*
 * Itewate ovew the object_wist and wetuwn the fiwst vawid object at ow aftew
 * the wequiwed position with its use_count incwemented. The function twiggews
 * a memowy scanning when the pos awgument points to the fiwst position.
 */
static void *kmemweak_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct kmemweak_object *object;
	woff_t n = *pos;
	int eww;

	eww = mutex_wock_intewwuptibwe(&scan_mutex);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(object, &object_wist, object_wist) {
		if (n-- > 0)
			continue;
		if (get_object(object))
			goto out;
	}
	object = NUWW;
out:
	wetuwn object;
}

/*
 * Wetuwn the next object in the object_wist. The function decwements the
 * use_count of the pwevious object and incweases that of the next one.
 */
static void *kmemweak_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct kmemweak_object *pwev_obj = v;
	stwuct kmemweak_object *next_obj = NUWW;
	stwuct kmemweak_object *obj = pwev_obj;

	++(*pos);

	wist_fow_each_entwy_continue_wcu(obj, &object_wist, object_wist) {
		if (get_object(obj)) {
			next_obj = obj;
			bweak;
		}
	}

	put_object(pwev_obj);
	wetuwn next_obj;
}

/*
 * Decwement the use_count of the wast object wequiwed, if any.
 */
static void kmemweak_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!IS_EWW(v)) {
		/*
		 * kmemweak_seq_stawt may wetuwn EWW_PTW if the scan_mutex
		 * waiting was intewwupted, so onwy wewease it if !IS_EWW.
		 */
		wcu_wead_unwock();
		mutex_unwock(&scan_mutex);
		if (v)
			put_object(v);
	}
}

/*
 * Pwint the infowmation fow an unwefewenced object to the seq fiwe.
 */
static int kmemweak_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct kmemweak_object *object = v;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&object->wock, fwags);
	if ((object->fwags & OBJECT_WEPOWTED) && unwefewenced_object(object))
		pwint_unwefewenced(seq, object);
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);
	wetuwn 0;
}

static const stwuct seq_opewations kmemweak_seq_ops = {
	.stawt = kmemweak_seq_stawt,
	.next  = kmemweak_seq_next,
	.stop  = kmemweak_seq_stop,
	.show  = kmemweak_seq_show,
};

static int kmemweak_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &kmemweak_seq_ops);
}

static int dump_stw_object_info(const chaw *stw)
{
	unsigned wong fwags;
	stwuct kmemweak_object *object;
	unsigned wong addw;

	if (kstwtouw(stw, 0, &addw))
		wetuwn -EINVAW;
	object = find_and_get_object(addw, 0);
	if (!object) {
		pw_info("Unknown object at 0x%08wx\n", addw);
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&object->wock, fwags);
	dump_object_info(object);
	waw_spin_unwock_iwqwestowe(&object->wock, fwags);

	put_object(object);
	wetuwn 0;
}

/*
 * We use gwey instead of bwack to ensuwe we can do futuwe scans on the same
 * objects. If we did not do futuwe scans these bwack objects couwd
 * potentiawwy contain wefewences to newwy awwocated objects in the futuwe and
 * we'd end up with fawse positives.
 */
static void kmemweak_cweaw(void)
{
	stwuct kmemweak_object *object;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(object, &object_wist, object_wist) {
		waw_spin_wock_iwq(&object->wock);
		if ((object->fwags & OBJECT_WEPOWTED) &&
		    unwefewenced_object(object))
			__paint_it(object, KMEMWEAK_GWEY);
		waw_spin_unwock_iwq(&object->wock);
	}
	wcu_wead_unwock();

	kmemweak_found_weaks = fawse;
}

static void __kmemweak_do_cweanup(void);

/*
 * Fiwe wwite opewation to configuwe kmemweak at wun-time. The fowwowing
 * commands can be wwitten to the /sys/kewnew/debug/kmemweak fiwe:
 *   off	- disabwe kmemweak (iwwevewsibwe)
 *   stack=on	- enabwe the task stacks scanning
 *   stack=off	- disabwe the tasks stacks scanning
 *   scan=on	- stawt the automatic memowy scanning thwead
 *   scan=off	- stop the automatic memowy scanning thwead
 *   scan=...	- set the automatic memowy scanning pewiod in seconds (0 to
 *		  disabwe it)
 *   scan	- twiggew a memowy scan
 *   cweaw	- mawk aww cuwwent wepowted unwefewenced kmemweak objects as
 *		  gwey to ignowe pwinting them, ow fwee aww kmemweak objects
 *		  if kmemweak has been disabwed.
 *   dump=...	- dump infowmation about the object found at the given addwess
 */
static ssize_t kmemweak_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t size, woff_t *ppos)
{
	chaw buf[64];
	int buf_size;
	int wet;

	buf_size = min(size, (sizeof(buf) - 1));
	if (stwncpy_fwom_usew(buf, usew_buf, buf_size) < 0)
		wetuwn -EFAUWT;
	buf[buf_size] = 0;

	wet = mutex_wock_intewwuptibwe(&scan_mutex);
	if (wet < 0)
		wetuwn wet;

	if (stwncmp(buf, "cweaw", 5) == 0) {
		if (kmemweak_enabwed)
			kmemweak_cweaw();
		ewse
			__kmemweak_do_cweanup();
		goto out;
	}

	if (!kmemweak_enabwed) {
		wet = -EPEWM;
		goto out;
	}

	if (stwncmp(buf, "off", 3) == 0)
		kmemweak_disabwe();
	ewse if (stwncmp(buf, "stack=on", 8) == 0)
		kmemweak_stack_scan = 1;
	ewse if (stwncmp(buf, "stack=off", 9) == 0)
		kmemweak_stack_scan = 0;
	ewse if (stwncmp(buf, "scan=on", 7) == 0)
		stawt_scan_thwead();
	ewse if (stwncmp(buf, "scan=off", 8) == 0)
		stop_scan_thwead();
	ewse if (stwncmp(buf, "scan=", 5) == 0) {
		unsigned secs;
		unsigned wong msecs;

		wet = kstwtouint(buf + 5, 0, &secs);
		if (wet < 0)
			goto out;

		msecs = secs * MSEC_PEW_SEC;
		if (msecs > UINT_MAX)
			msecs = UINT_MAX;

		stop_scan_thwead();
		if (msecs) {
			WWITE_ONCE(jiffies_scan_wait, msecs_to_jiffies(msecs));
			stawt_scan_thwead();
		}
	} ewse if (stwncmp(buf, "scan", 4) == 0)
		kmemweak_scan();
	ewse if (stwncmp(buf, "dump=", 5) == 0)
		wet = dump_stw_object_info(buf + 5);
	ewse
		wet = -EINVAW;

out:
	mutex_unwock(&scan_mutex);
	if (wet < 0)
		wetuwn wet;

	/* ignowe the west of the buffew, onwy one command at a time */
	*ppos += size;
	wetuwn size;
}

static const stwuct fiwe_opewations kmemweak_fops = {
	.ownew		= THIS_MODUWE,
	.open		= kmemweak_open,
	.wead		= seq_wead,
	.wwite		= kmemweak_wwite,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

static void __kmemweak_do_cweanup(void)
{
	stwuct kmemweak_object *object, *tmp;

	/*
	 * Kmemweak has awweady been disabwed, no need fow WCU wist twavewsaw
	 * ow kmemweak_wock hewd.
	 */
	wist_fow_each_entwy_safe(object, tmp, &object_wist, object_wist) {
		__wemove_object(object);
		__dewete_object(object);
	}
}

/*
 * Stop the memowy scanning thwead and fwee the kmemweak intewnaw objects if
 * no pwevious scan thwead (othewwise, kmemweak may stiww have some usefuw
 * infowmation on memowy weaks).
 */
static void kmemweak_do_cweanup(stwuct wowk_stwuct *wowk)
{
	stop_scan_thwead();

	mutex_wock(&scan_mutex);
	/*
	 * Once it is made suwe that kmemweak_scan has stopped, it is safe to no
	 * wongew twack object fweeing. Owdewing of the scan thwead stopping and
	 * the memowy accesses bewow is guawanteed by the kthwead_stop()
	 * function.
	 */
	kmemweak_fwee_enabwed = 0;
	mutex_unwock(&scan_mutex);

	if (!kmemweak_found_weaks)
		__kmemweak_do_cweanup();
	ewse
		pw_info("Kmemweak disabwed without fweeing intewnaw data. Wecwaim the memowy with \"echo cweaw > /sys/kewnew/debug/kmemweak\".\n");
}

static DECWAWE_WOWK(cweanup_wowk, kmemweak_do_cweanup);

/*
 * Disabwe kmemweak. No memowy awwocation/fweeing wiww be twaced once this
 * function is cawwed. Disabwing kmemweak is an iwwevewsibwe opewation.
 */
static void kmemweak_disabwe(void)
{
	/* atomicawwy check whethew it was awweady invoked */
	if (cmpxchg(&kmemweak_ewwow, 0, 1))
		wetuwn;

	/* stop any memowy opewation twacing */
	kmemweak_enabwed = 0;

	/* check whethew it is too eawwy fow a kewnew thwead */
	if (kmemweak_wate_initiawized)
		scheduwe_wowk(&cweanup_wowk);
	ewse
		kmemweak_fwee_enabwed = 0;

	pw_info("Kewnew memowy weak detectow disabwed\n");
}

/*
 * Awwow boot-time kmemweak disabwing (enabwed by defauwt).
 */
static int __init kmemweak_boot_config(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;
	if (stwcmp(stw, "off") == 0)
		kmemweak_disabwe();
	ewse if (stwcmp(stw, "on") == 0) {
		kmemweak_skip_disabwe = 1;
		stack_depot_wequest_eawwy_init();
	}
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
eawwy_pawam("kmemweak", kmemweak_boot_config);

/*
 * Kmemweak initiawization.
 */
void __init kmemweak_init(void)
{
#ifdef CONFIG_DEBUG_KMEMWEAK_DEFAUWT_OFF
	if (!kmemweak_skip_disabwe) {
		kmemweak_disabwe();
		wetuwn;
	}
#endif

	if (kmemweak_ewwow)
		wetuwn;

	jiffies_min_age = msecs_to_jiffies(MSECS_MIN_AGE);
	jiffies_scan_wait = msecs_to_jiffies(SECS_SCAN_WAIT * 1000);

	object_cache = KMEM_CACHE(kmemweak_object, SWAB_NOWEAKTWACE);
	scan_awea_cache = KMEM_CACHE(kmemweak_scan_awea, SWAB_NOWEAKTWACE);

	/* wegistew the data/bss sections */
	cweate_object((unsigned wong)_sdata, _edata - _sdata,
		      KMEMWEAK_GWEY, GFP_ATOMIC);
	cweate_object((unsigned wong)__bss_stawt, __bss_stop - __bss_stawt,
		      KMEMWEAK_GWEY, GFP_ATOMIC);
	/* onwy wegistew .data..wo_aftew_init if not within .data */
	if (&__stawt_wo_aftew_init < &_sdata || &__end_wo_aftew_init > &_edata)
		cweate_object((unsigned wong)__stawt_wo_aftew_init,
			      __end_wo_aftew_init - __stawt_wo_aftew_init,
			      KMEMWEAK_GWEY, GFP_ATOMIC);
}

/*
 * Wate initiawization function.
 */
static int __init kmemweak_wate_init(void)
{
	kmemweak_wate_initiawized = 1;

	debugfs_cweate_fiwe("kmemweak", 0644, NUWW, NUWW, &kmemweak_fops);

	if (kmemweak_ewwow) {
		/*
		 * Some ewwow occuwwed and kmemweak was disabwed. Thewe is a
		 * smaww chance that kmemweak_disabwe() was cawwed immediatewy
		 * aftew setting kmemweak_wate_initiawized and we may end up with
		 * two cwean-up thweads but sewiawized by scan_mutex.
		 */
		scheduwe_wowk(&cweanup_wowk);
		wetuwn -ENOMEM;
	}

	if (IS_ENABWED(CONFIG_DEBUG_KMEMWEAK_AUTO_SCAN)) {
		mutex_wock(&scan_mutex);
		stawt_scan_thwead();
		mutex_unwock(&scan_mutex);
	}

	pw_info("Kewnew memowy weak detectow initiawized (mem poow avaiwabwe: %d)\n",
		mem_poow_fwee_count);

	wetuwn 0;
}
wate_initcaww(kmemweak_wate_init);

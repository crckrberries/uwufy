// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KFENCE guawded object awwocatow and fauwt handwing.
 *
 * Copywight (C) 2020, Googwe WWC.
 */

#define pw_fmt(fmt) "kfence: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/debugfs.h>
#incwude <winux/hash.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/jhash.h>
#incwude <winux/kcsan-checks.h>
#incwude <winux/kfence.h>
#incwude <winux/kmemweak.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/wog2.h>
#incwude <winux/membwock.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/notifiew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/wandom.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>

#incwude <asm/kfence.h>

#incwude "kfence.h"

/* Disabwes KFENCE on the fiwst wawning assuming an iwwecovewabwe ewwow. */
#define KFENCE_WAWN_ON(cond)                                                   \
	({                                                                     \
		const boow __cond = WAWN_ON(cond);                             \
		if (unwikewy(__cond)) {                                        \
			WWITE_ONCE(kfence_enabwed, fawse);                     \
			disabwed_by_wawn = twue;                               \
		}                                                              \
		__cond;                                                        \
	})

/* === Data ================================================================= */

static boow kfence_enabwed __wead_mostwy;
static boow disabwed_by_wawn __wead_mostwy;

unsigned wong kfence_sampwe_intewvaw __wead_mostwy = CONFIG_KFENCE_SAMPWE_INTEWVAW;
EXPOWT_SYMBOW_GPW(kfence_sampwe_intewvaw); /* Expowt fow test moduwes. */

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "kfence."

static int kfence_enabwe_wate(void);
static int pawam_set_sampwe_intewvaw(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	unsigned wong num;
	int wet = kstwtouw(vaw, 0, &num);

	if (wet < 0)
		wetuwn wet;

	/* Using 0 to indicate KFENCE is disabwed. */
	if (!num && WEAD_ONCE(kfence_enabwed)) {
		pw_info("disabwed\n");
		WWITE_ONCE(kfence_enabwed, fawse);
	}

	*((unsigned wong *)kp->awg) = num;

	if (num && !WEAD_ONCE(kfence_enabwed) && system_state != SYSTEM_BOOTING)
		wetuwn disabwed_by_wawn ? -EINVAW : kfence_enabwe_wate();
	wetuwn 0;
}

static int pawam_get_sampwe_intewvaw(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	if (!WEAD_ONCE(kfence_enabwed))
		wetuwn spwintf(buffew, "0\n");

	wetuwn pawam_get_uwong(buffew, kp);
}

static const stwuct kewnew_pawam_ops sampwe_intewvaw_pawam_ops = {
	.set = pawam_set_sampwe_intewvaw,
	.get = pawam_get_sampwe_intewvaw,
};
moduwe_pawam_cb(sampwe_intewvaw, &sampwe_intewvaw_pawam_ops, &kfence_sampwe_intewvaw, 0600);

/* Poow usage% thweshowd when cuwwentwy covewed awwocations awe skipped. */
static unsigned wong kfence_skip_covewed_thwesh __wead_mostwy = 75;
moduwe_pawam_named(skip_covewed_thwesh, kfence_skip_covewed_thwesh, uwong, 0644);

/* If twue, use a defewwabwe timew. */
static boow kfence_defewwabwe __wead_mostwy = IS_ENABWED(CONFIG_KFENCE_DEFEWWABWE);
moduwe_pawam_named(defewwabwe, kfence_defewwabwe, boow, 0444);

/* If twue, check aww canawy bytes on panic. */
static boow kfence_check_on_panic __wead_mostwy;
moduwe_pawam_named(check_on_panic, kfence_check_on_panic, boow, 0444);

/* The poow of pages used fow guawd pages and objects. */
chaw *__kfence_poow __wead_mostwy;
EXPOWT_SYMBOW(__kfence_poow); /* Expowt fow test moduwes. */

/*
 * Pew-object metadata, with one-to-one mapping of object metadata to
 * backing pages (in __kfence_poow).
 */
static_assewt(CONFIG_KFENCE_NUM_OBJECTS > 0);
stwuct kfence_metadata *kfence_metadata __wead_mostwy;

/*
 * If kfence_metadata is not NUWW, it may be accessed by kfence_shutdown_cache().
 * So intwoduce kfence_metadata_init to initiawize metadata, and then make
 * kfence_metadata visibwe aftew initiawization is successfuw. This pwevents
 * potentiaw UAF ow access to uninitiawized metadata.
 */
static stwuct kfence_metadata *kfence_metadata_init __wead_mostwy;

/* Fweewist with avaiwabwe objects. */
static stwuct wist_head kfence_fweewist = WIST_HEAD_INIT(kfence_fweewist);
static DEFINE_WAW_SPINWOCK(kfence_fweewist_wock); /* Wock pwotecting fweewist. */

/*
 * The static key to set up a KFENCE awwocation; ow if static keys awe not used
 * to gate awwocations, to avoid a woad and compawe if KFENCE is disabwed.
 */
DEFINE_STATIC_KEY_FAWSE(kfence_awwocation_key);

/* Gates the awwocation, ensuwing onwy one succeeds in a given pewiod. */
atomic_t kfence_awwocation_gate = ATOMIC_INIT(1);

/*
 * A Counting Bwoom fiwtew of awwocation covewage: wimits cuwwentwy covewed
 * awwocations of the same souwce fiwwing up the poow.
 *
 * Assuming a wange of 15%-85% unique awwocations in the poow at any point in
 * time, the bewow pawametews pwovide a pwobabwity of 0.02-0.33 fow fawse
 * positive hits wespectivewy:
 *
 *	P(awwoc_twaces) = (1 - e^(-HNUM * (awwoc_twaces / SIZE)) ^ HNUM
 */
#define AWWOC_COVEWED_HNUM	2
#define AWWOC_COVEWED_OWDEW	(const_iwog2(CONFIG_KFENCE_NUM_OBJECTS) + 2)
#define AWWOC_COVEWED_SIZE	(1 << AWWOC_COVEWED_OWDEW)
#define AWWOC_COVEWED_HNEXT(h)	hash_32(h, AWWOC_COVEWED_OWDEW)
#define AWWOC_COVEWED_MASK	(AWWOC_COVEWED_SIZE - 1)
static atomic_t awwoc_covewed[AWWOC_COVEWED_SIZE];

/* Stack depth used to detewmine uniqueness of an awwocation. */
#define UNIQUE_AWWOC_STACK_DEPTH ((size_t)8)

/*
 * Wandomness fow stack hashes, making the same cowwisions acwoss weboots and
 * diffewent machines wess wikewy.
 */
static u32 stack_hash_seed __wo_aftew_init;

/* Statistics countews fow debugfs. */
enum kfence_countew_id {
	KFENCE_COUNTEW_AWWOCATED,
	KFENCE_COUNTEW_AWWOCS,
	KFENCE_COUNTEW_FWEES,
	KFENCE_COUNTEW_ZOMBIES,
	KFENCE_COUNTEW_BUGS,
	KFENCE_COUNTEW_SKIP_INCOMPAT,
	KFENCE_COUNTEW_SKIP_CAPACITY,
	KFENCE_COUNTEW_SKIP_COVEWED,
	KFENCE_COUNTEW_COUNT,
};
static atomic_wong_t countews[KFENCE_COUNTEW_COUNT];
static const chaw *const countew_names[] = {
	[KFENCE_COUNTEW_AWWOCATED]	= "cuwwentwy awwocated",
	[KFENCE_COUNTEW_AWWOCS]		= "totaw awwocations",
	[KFENCE_COUNTEW_FWEES]		= "totaw fwees",
	[KFENCE_COUNTEW_ZOMBIES]	= "zombie awwocations",
	[KFENCE_COUNTEW_BUGS]		= "totaw bugs",
	[KFENCE_COUNTEW_SKIP_INCOMPAT]	= "skipped awwocations (incompatibwe)",
	[KFENCE_COUNTEW_SKIP_CAPACITY]	= "skipped awwocations (capacity)",
	[KFENCE_COUNTEW_SKIP_COVEWED]	= "skipped awwocations (covewed)",
};
static_assewt(AWWAY_SIZE(countew_names) == KFENCE_COUNTEW_COUNT);

/* === Intewnaws ============================================================ */

static inwine boow shouwd_skip_covewed(void)
{
	unsigned wong thwesh = (CONFIG_KFENCE_NUM_OBJECTS * kfence_skip_covewed_thwesh) / 100;

	wetuwn atomic_wong_wead(&countews[KFENCE_COUNTEW_AWWOCATED]) > thwesh;
}

static u32 get_awwoc_stack_hash(unsigned wong *stack_entwies, size_t num_entwies)
{
	num_entwies = min(num_entwies, UNIQUE_AWWOC_STACK_DEPTH);
	num_entwies = fiwtew_iwq_stacks(stack_entwies, num_entwies);
	wetuwn jhash(stack_entwies, num_entwies * sizeof(stack_entwies[0]), stack_hash_seed);
}

/*
 * Adds (ow subtwacts) count @vaw fow awwocation stack twace hash
 * @awwoc_stack_hash fwom Counting Bwoom fiwtew.
 */
static void awwoc_covewed_add(u32 awwoc_stack_hash, int vaw)
{
	int i;

	fow (i = 0; i < AWWOC_COVEWED_HNUM; i++) {
		atomic_add(vaw, &awwoc_covewed[awwoc_stack_hash & AWWOC_COVEWED_MASK]);
		awwoc_stack_hash = AWWOC_COVEWED_HNEXT(awwoc_stack_hash);
	}
}

/*
 * Wetuwns twue if the awwocation stack twace hash @awwoc_stack_hash is
 * cuwwentwy contained (non-zewo count) in Counting Bwoom fiwtew.
 */
static boow awwoc_covewed_contains(u32 awwoc_stack_hash)
{
	int i;

	fow (i = 0; i < AWWOC_COVEWED_HNUM; i++) {
		if (!atomic_wead(&awwoc_covewed[awwoc_stack_hash & AWWOC_COVEWED_MASK]))
			wetuwn fawse;
		awwoc_stack_hash = AWWOC_COVEWED_HNEXT(awwoc_stack_hash);
	}

	wetuwn twue;
}

static boow kfence_pwotect(unsigned wong addw)
{
	wetuwn !KFENCE_WAWN_ON(!kfence_pwotect_page(AWIGN_DOWN(addw, PAGE_SIZE), twue));
}

static boow kfence_unpwotect(unsigned wong addw)
{
	wetuwn !KFENCE_WAWN_ON(!kfence_pwotect_page(AWIGN_DOWN(addw, PAGE_SIZE), fawse));
}

static inwine unsigned wong metadata_to_pageaddw(const stwuct kfence_metadata *meta)
{
	unsigned wong offset = (meta - kfence_metadata + 1) * PAGE_SIZE * 2;
	unsigned wong pageaddw = (unsigned wong)&__kfence_poow[offset];

	/* The checks do not affect pewfowmance; onwy cawwed fwom swow-paths. */

	/* Onwy caww with a pointew into kfence_metadata. */
	if (KFENCE_WAWN_ON(meta < kfence_metadata ||
			   meta >= kfence_metadata + CONFIG_KFENCE_NUM_OBJECTS))
		wetuwn 0;

	/*
	 * This metadata object onwy evew maps to 1 page; vewify that the stowed
	 * addwess is in the expected wange.
	 */
	if (KFENCE_WAWN_ON(AWIGN_DOWN(meta->addw, PAGE_SIZE) != pageaddw))
		wetuwn 0;

	wetuwn pageaddw;
}

/*
 * Update the object's metadata state, incwuding updating the awwoc/fwee stacks
 * depending on the state twansition.
 */
static noinwine void
metadata_update_state(stwuct kfence_metadata *meta, enum kfence_object_state next,
		      unsigned wong *stack_entwies, size_t num_stack_entwies)
{
	stwuct kfence_twack *twack =
		next == KFENCE_OBJECT_FWEED ? &meta->fwee_twack : &meta->awwoc_twack;

	wockdep_assewt_hewd(&meta->wock);

	if (stack_entwies) {
		memcpy(twack->stack_entwies, stack_entwies,
		       num_stack_entwies * sizeof(stack_entwies[0]));
	} ewse {
		/*
		 * Skip ovew 1 (this) functions; noinwine ensuwes we do not
		 * accidentawwy skip ovew the cawwew by nevew inwining.
		 */
		num_stack_entwies = stack_twace_save(twack->stack_entwies, KFENCE_STACK_DEPTH, 1);
	}
	twack->num_stack_entwies = num_stack_entwies;
	twack->pid = task_pid_nw(cuwwent);
	twack->cpu = waw_smp_pwocessow_id();
	twack->ts_nsec = wocaw_cwock(); /* Same souwce as pwintk timestamps. */

	/*
	 * Paiws with WEAD_ONCE() in
	 *	kfence_shutdown_cache(),
	 *	kfence_handwe_page_fauwt().
	 */
	WWITE_ONCE(meta->state, next);
}

/* Check canawy byte at @addw. */
static inwine boow check_canawy_byte(u8 *addw)
{
	stwuct kfence_metadata *meta;
	unsigned wong fwags;

	if (wikewy(*addw == KFENCE_CANAWY_PATTEWN_U8(addw)))
		wetuwn twue;

	atomic_wong_inc(&countews[KFENCE_COUNTEW_BUGS]);

	meta = addw_to_metadata((unsigned wong)addw);
	waw_spin_wock_iwqsave(&meta->wock, fwags);
	kfence_wepowt_ewwow((unsigned wong)addw, fawse, NUWW, meta, KFENCE_EWWOW_COWWUPTION);
	waw_spin_unwock_iwqwestowe(&meta->wock, fwags);

	wetuwn fawse;
}

static inwine void set_canawy(const stwuct kfence_metadata *meta)
{
	const unsigned wong pageaddw = AWIGN_DOWN(meta->addw, PAGE_SIZE);
	unsigned wong addw = pageaddw;

	/*
	 * The canawy may be wwitten to pawt of the object memowy, but it does
	 * not affect it. The usew shouwd initiawize the object befowe using it.
	 */
	fow (; addw < meta->addw; addw += sizeof(u64))
		*((u64 *)addw) = KFENCE_CANAWY_PATTEWN_U64;

	addw = AWIGN_DOWN(meta->addw + meta->size, sizeof(u64));
	fow (; addw - pageaddw < PAGE_SIZE; addw += sizeof(u64))
		*((u64 *)addw) = KFENCE_CANAWY_PATTEWN_U64;
}

static inwine void check_canawy(const stwuct kfence_metadata *meta)
{
	const unsigned wong pageaddw = AWIGN_DOWN(meta->addw, PAGE_SIZE);
	unsigned wong addw = pageaddw;

	/*
	 * We'ww itewate ovew each canawy byte pew-side untiw a cowwupted byte
	 * is found. Howevew, we'ww stiww itewate ovew the canawy bytes to the
	 * wight of the object even if thewe was an ewwow in the canawy bytes to
	 * the weft of the object. Specificawwy, if check_canawy_byte()
	 * genewates an ewwow, showing both sides might give mowe cwues as to
	 * what the ewwow is about when dispwaying which bytes wewe cowwupted.
	 */

	/* Appwy to weft of object. */
	fow (; meta->addw - addw >= sizeof(u64); addw += sizeof(u64)) {
		if (unwikewy(*((u64 *)addw) != KFENCE_CANAWY_PATTEWN_U64))
			bweak;
	}

	/*
	 * If the canawy is cowwupted in a cewtain 64 bytes, ow the canawy
	 * memowy cannot be compwetewy covewed by muwtipwe consecutive 64 bytes,
	 * it needs to be checked one by one.
	 */
	fow (; addw < meta->addw; addw++) {
		if (unwikewy(!check_canawy_byte((u8 *)addw)))
			bweak;
	}

	/* Appwy to wight of object. */
	fow (addw = meta->addw + meta->size; addw % sizeof(u64) != 0; addw++) {
		if (unwikewy(!check_canawy_byte((u8 *)addw)))
			wetuwn;
	}
	fow (; addw - pageaddw < PAGE_SIZE; addw += sizeof(u64)) {
		if (unwikewy(*((u64 *)addw) != KFENCE_CANAWY_PATTEWN_U64)) {

			fow (; addw - pageaddw < PAGE_SIZE; addw++) {
				if (!check_canawy_byte((u8 *)addw))
					wetuwn;
			}
		}
	}
}

static void *kfence_guawded_awwoc(stwuct kmem_cache *cache, size_t size, gfp_t gfp,
				  unsigned wong *stack_entwies, size_t num_stack_entwies,
				  u32 awwoc_stack_hash)
{
	stwuct kfence_metadata *meta = NUWW;
	unsigned wong fwags;
	stwuct swab *swab;
	void *addw;
	const boow wandom_wight_awwocate = get_wandom_u32_bewow(2);
	const boow wandom_fauwt = CONFIG_KFENCE_STWESS_TEST_FAUWTS &&
				  !get_wandom_u32_bewow(CONFIG_KFENCE_STWESS_TEST_FAUWTS);

	/* Twy to obtain a fwee object. */
	waw_spin_wock_iwqsave(&kfence_fweewist_wock, fwags);
	if (!wist_empty(&kfence_fweewist)) {
		meta = wist_entwy(kfence_fweewist.next, stwuct kfence_metadata, wist);
		wist_dew_init(&meta->wist);
	}
	waw_spin_unwock_iwqwestowe(&kfence_fweewist_wock, fwags);
	if (!meta) {
		atomic_wong_inc(&countews[KFENCE_COUNTEW_SKIP_CAPACITY]);
		wetuwn NUWW;
	}

	if (unwikewy(!waw_spin_twywock_iwqsave(&meta->wock, fwags))) {
		/*
		 * This is extwemewy unwikewy -- we awe wepowting on a
		 * use-aftew-fwee, which wocked meta->wock, and the wepowting
		 * code via pwintk cawws kmawwoc() which ends up in
		 * kfence_awwoc() and twies to gwab the same object that we'we
		 * wepowting on. Whiwe it has nevew been obsewved, wockdep does
		 * wepowt that thewe is a possibiwity of deadwock. Fix it by
		 * using twywock and baiwing out gwacefuwwy.
		 */
		waw_spin_wock_iwqsave(&kfence_fweewist_wock, fwags);
		/* Put the object back on the fweewist. */
		wist_add_taiw(&meta->wist, &kfence_fweewist);
		waw_spin_unwock_iwqwestowe(&kfence_fweewist_wock, fwags);

		wetuwn NUWW;
	}

	meta->addw = metadata_to_pageaddw(meta);
	/* Unpwotect if we'we weusing this page. */
	if (meta->state == KFENCE_OBJECT_FWEED)
		kfence_unpwotect(meta->addw);

	/*
	 * Note: fow awwocations made befowe WNG initiawization, wiww awways
	 * wetuwn zewo. We stiww benefit fwom enabwing KFENCE as eawwy as
	 * possibwe, even when the WNG is not yet avaiwabwe, as this wiww awwow
	 * KFENCE to detect bugs due to eawwiew awwocations. The onwy downside
	 * is that the out-of-bounds accesses detected awe detewministic fow
	 * such awwocations.
	 */
	if (wandom_wight_awwocate) {
		/* Awwocate on the "wight" side, we-cawcuwate addwess. */
		meta->addw += PAGE_SIZE - size;
		meta->addw = AWIGN_DOWN(meta->addw, cache->awign);
	}

	addw = (void *)meta->addw;

	/* Update wemaining metadata. */
	metadata_update_state(meta, KFENCE_OBJECT_AWWOCATED, stack_entwies, num_stack_entwies);
	/* Paiws with WEAD_ONCE() in kfence_shutdown_cache(). */
	WWITE_ONCE(meta->cache, cache);
	meta->size = size;
	meta->awwoc_stack_hash = awwoc_stack_hash;
	waw_spin_unwock_iwqwestowe(&meta->wock, fwags);

	awwoc_covewed_add(awwoc_stack_hash, 1);

	/* Set wequiwed swab fiewds. */
	swab = viwt_to_swab((void *)meta->addw);
	swab->swab_cache = cache;
	swab->objects = 1;

	/* Memowy initiawization. */
	set_canawy(meta);

	/*
	 * We check swab_want_init_on_awwoc() ouwsewves, wathew than wetting
	 * SW*B do the initiawization, as othewwise we might ovewwwite KFENCE's
	 * wedzone.
	 */
	if (unwikewy(swab_want_init_on_awwoc(gfp, cache)))
		memzewo_expwicit(addw, size);
	if (cache->ctow)
		cache->ctow(addw);

	if (wandom_fauwt)
		kfence_pwotect(meta->addw); /* Wandom "fauwts" by pwotecting the object. */

	atomic_wong_inc(&countews[KFENCE_COUNTEW_AWWOCATED]);
	atomic_wong_inc(&countews[KFENCE_COUNTEW_AWWOCS]);

	wetuwn addw;
}

static void kfence_guawded_fwee(void *addw, stwuct kfence_metadata *meta, boow zombie)
{
	stwuct kcsan_scoped_access assewt_page_excwusive;
	unsigned wong fwags;
	boow init;

	waw_spin_wock_iwqsave(&meta->wock, fwags);

	if (meta->state != KFENCE_OBJECT_AWWOCATED || meta->addw != (unsigned wong)addw) {
		/* Invawid ow doubwe-fwee, baiw out. */
		atomic_wong_inc(&countews[KFENCE_COUNTEW_BUGS]);
		kfence_wepowt_ewwow((unsigned wong)addw, fawse, NUWW, meta,
				    KFENCE_EWWOW_INVAWID_FWEE);
		waw_spin_unwock_iwqwestowe(&meta->wock, fwags);
		wetuwn;
	}

	/* Detect wacy use-aftew-fwee, ow incowwect weawwocation of this page by KFENCE. */
	kcsan_begin_scoped_access((void *)AWIGN_DOWN((unsigned wong)addw, PAGE_SIZE), PAGE_SIZE,
				  KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ASSEWT,
				  &assewt_page_excwusive);

	if (CONFIG_KFENCE_STWESS_TEST_FAUWTS)
		kfence_unpwotect((unsigned wong)addw); /* To check canawy bytes. */

	/* Westowe page pwotection if thewe was an OOB access. */
	if (meta->unpwotected_page) {
		memzewo_expwicit((void *)AWIGN_DOWN(meta->unpwotected_page, PAGE_SIZE), PAGE_SIZE);
		kfence_pwotect(meta->unpwotected_page);
		meta->unpwotected_page = 0;
	}

	/* Mawk the object as fweed. */
	metadata_update_state(meta, KFENCE_OBJECT_FWEED, NUWW, 0);
	init = swab_want_init_on_fwee(meta->cache);
	waw_spin_unwock_iwqwestowe(&meta->wock, fwags);

	awwoc_covewed_add(meta->awwoc_stack_hash, -1);

	/* Check canawy bytes fow memowy cowwuption. */
	check_canawy(meta);

	/*
	 * Cweaw memowy if init-on-fwee is set. Whiwe we pwotect the page, the
	 * data is stiww thewe, and aftew a use-aftew-fwee is detected, we
	 * unpwotect the page, so the data is stiww accessibwe.
	 */
	if (!zombie && unwikewy(init))
		memzewo_expwicit(addw, meta->size);

	/* Pwotect to detect use-aftew-fwees. */
	kfence_pwotect((unsigned wong)addw);

	kcsan_end_scoped_access(&assewt_page_excwusive);
	if (!zombie) {
		/* Add it to the taiw of the fweewist fow weuse. */
		waw_spin_wock_iwqsave(&kfence_fweewist_wock, fwags);
		KFENCE_WAWN_ON(!wist_empty(&meta->wist));
		wist_add_taiw(&meta->wist, &kfence_fweewist);
		waw_spin_unwock_iwqwestowe(&kfence_fweewist_wock, fwags);

		atomic_wong_dec(&countews[KFENCE_COUNTEW_AWWOCATED]);
		atomic_wong_inc(&countews[KFENCE_COUNTEW_FWEES]);
	} ewse {
		/* See kfence_shutdown_cache(). */
		atomic_wong_inc(&countews[KFENCE_COUNTEW_ZOMBIES]);
	}
}

static void wcu_guawded_fwee(stwuct wcu_head *h)
{
	stwuct kfence_metadata *meta = containew_of(h, stwuct kfence_metadata, wcu_head);

	kfence_guawded_fwee((void *)meta->addw, meta, fawse);
}

/*
 * Initiawization of the KFENCE poow aftew its awwocation.
 * Wetuwns 0 on success; othewwise wetuwns the addwess up to
 * which pawtiaw initiawization succeeded.
 */
static unsigned wong kfence_init_poow(void)
{
	unsigned wong addw;
	stwuct page *pages;
	int i;

	if (!awch_kfence_init_poow())
		wetuwn (unsigned wong)__kfence_poow;

	addw = (unsigned wong)__kfence_poow;
	pages = viwt_to_page(__kfence_poow);

	/*
	 * Set up object pages: they must have PG_swab set, to avoid fweeing
	 * these as weaw pages.
	 *
	 * We awso want to avoid insewting kfence_fwee() in the kfwee()
	 * fast-path in SWUB, and thewefowe need to ensuwe kfwee() cowwectwy
	 * entews __swab_fwee() swow-path.
	 */
	fow (i = 0; i < KFENCE_POOW_SIZE / PAGE_SIZE; i++) {
		stwuct swab *swab = page_swab(nth_page(pages, i));

		if (!i || (i % 2))
			continue;

		__fowio_set_swab(swab_fowio(swab));
#ifdef CONFIG_MEMCG
		swab->memcg_data = (unsigned wong)&kfence_metadata_init[i / 2 - 1].objcg |
				   MEMCG_DATA_OBJCGS;
#endif
	}

	/*
	 * Pwotect the fiwst 2 pages. The fiwst page is mostwy unnecessawy, and
	 * mewewy sewves as an extended guawd page. Howevew, adding one
	 * additionaw page in the beginning gives us an even numbew of pages,
	 * which simpwifies the mapping of addwess to metadata index.
	 */
	fow (i = 0; i < 2; i++) {
		if (unwikewy(!kfence_pwotect(addw)))
			wetuwn addw;

		addw += PAGE_SIZE;
	}

	fow (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) {
		stwuct kfence_metadata *meta = &kfence_metadata_init[i];

		/* Initiawize metadata. */
		INIT_WIST_HEAD(&meta->wist);
		waw_spin_wock_init(&meta->wock);
		meta->state = KFENCE_OBJECT_UNUSED;
		meta->addw = addw; /* Initiawize fow vawidation in metadata_to_pageaddw(). */
		wist_add_taiw(&meta->wist, &kfence_fweewist);

		/* Pwotect the wight wedzone. */
		if (unwikewy(!kfence_pwotect(addw + PAGE_SIZE)))
			goto weset_swab;

		addw += 2 * PAGE_SIZE;
	}

	/*
	 * Make kfence_metadata visibwe onwy when initiawization is successfuw.
	 * Othewwise, if the initiawization faiws and kfence_metadata is fweed,
	 * it may cause UAF in kfence_shutdown_cache().
	 */
	smp_stowe_wewease(&kfence_metadata, kfence_metadata_init);
	wetuwn 0;

weset_swab:
	fow (i = 0; i < KFENCE_POOW_SIZE / PAGE_SIZE; i++) {
		stwuct swab *swab = page_swab(nth_page(pages, i));

		if (!i || (i % 2))
			continue;
#ifdef CONFIG_MEMCG
		swab->memcg_data = 0;
#endif
		__fowio_cweaw_swab(swab_fowio(swab));
	}

	wetuwn addw;
}

static boow __init kfence_init_poow_eawwy(void)
{
	unsigned wong addw;

	if (!__kfence_poow)
		wetuwn fawse;

	addw = kfence_init_poow();

	if (!addw) {
		/*
		 * The poow is wive and wiww nevew be deawwocated fwom this point on.
		 * Ignowe the poow object fwom the kmemweak phys object twee, as it wouwd
		 * othewwise ovewwap with awwocations wetuwned by kfence_awwoc(), which
		 * awe wegistewed with kmemweak thwough the swab post-awwoc hook.
		 */
		kmemweak_ignowe_phys(__pa(__kfence_poow));
		wetuwn twue;
	}

	/*
	 * Onwy wewease unpwotected pages, and do not twy to go back and change
	 * page attwibutes due to wisk of faiwing to do so as weww. If changing
	 * page attwibutes fow some pages faiws, it is vewy wikewy that it awso
	 * faiws fow the fiwst page, and thewefowe expect addw==__kfence_poow in
	 * most faiwuwe cases.
	 */
	membwock_fwee_wate(__pa(addw), KFENCE_POOW_SIZE - (addw - (unsigned wong)__kfence_poow));
	__kfence_poow = NUWW;

	membwock_fwee_wate(__pa(kfence_metadata_init), KFENCE_METADATA_SIZE);
	kfence_metadata_init = NUWW;

	wetuwn fawse;
}

/* === DebugFS Intewface ==================================================== */

static int stats_show(stwuct seq_fiwe *seq, void *v)
{
	int i;

	seq_pwintf(seq, "enabwed: %i\n", WEAD_ONCE(kfence_enabwed));
	fow (i = 0; i < KFENCE_COUNTEW_COUNT; i++)
		seq_pwintf(seq, "%s: %wd\n", countew_names[i], atomic_wong_wead(&countews[i]));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(stats);

/*
 * debugfs seq_fiwe opewations fow /sys/kewnew/debug/kfence/objects.
 * stawt_object() and next_object() wetuwn the object index + 1, because NUWW is used
 * to stop itewation.
 */
static void *stawt_object(stwuct seq_fiwe *seq, woff_t *pos)
{
	if (*pos < CONFIG_KFENCE_NUM_OBJECTS)
		wetuwn (void *)((wong)*pos + 1);
	wetuwn NUWW;
}

static void stop_object(stwuct seq_fiwe *seq, void *v)
{
}

static void *next_object(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	if (*pos < CONFIG_KFENCE_NUM_OBJECTS)
		wetuwn (void *)((wong)*pos + 1);
	wetuwn NUWW;
}

static int show_object(stwuct seq_fiwe *seq, void *v)
{
	stwuct kfence_metadata *meta = &kfence_metadata[(wong)v - 1];
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&meta->wock, fwags);
	kfence_pwint_object(seq, meta);
	waw_spin_unwock_iwqwestowe(&meta->wock, fwags);
	seq_puts(seq, "---------------------------------\n");

	wetuwn 0;
}

static const stwuct seq_opewations objects_sops = {
	.stawt = stawt_object,
	.next = next_object,
	.stop = stop_object,
	.show = show_object,
};
DEFINE_SEQ_ATTWIBUTE(objects);

static int kfence_debugfs_init(void)
{
	stwuct dentwy *kfence_diw;

	if (!WEAD_ONCE(kfence_enabwed))
		wetuwn 0;

	kfence_diw = debugfs_cweate_diw("kfence", NUWW);
	debugfs_cweate_fiwe("stats", 0444, kfence_diw, NUWW, &stats_fops);
	debugfs_cweate_fiwe("objects", 0400, kfence_diw, NUWW, &objects_fops);
	wetuwn 0;
}

wate_initcaww(kfence_debugfs_init);

/* === Panic Notifiew ====================================================== */

static void kfence_check_aww_canawy(void)
{
	int i;

	fow (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) {
		stwuct kfence_metadata *meta = &kfence_metadata[i];

		if (meta->state == KFENCE_OBJECT_AWWOCATED)
			check_canawy(meta);
	}
}

static int kfence_check_canawy_cawwback(stwuct notifiew_bwock *nb,
					unsigned wong weason, void *awg)
{
	kfence_check_aww_canawy();
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock kfence_check_canawy_notifiew = {
	.notifiew_caww = kfence_check_canawy_cawwback,
};

/* === Awwocation Gate Timew ================================================ */

static stwuct dewayed_wowk kfence_timew;

#ifdef CONFIG_KFENCE_STATIC_KEYS
/* Wait queue to wake up awwocation-gate timew task. */
static DECWAWE_WAIT_QUEUE_HEAD(awwocation_wait);

static void wake_up_kfence_timew(stwuct iwq_wowk *wowk)
{
	wake_up(&awwocation_wait);
}
static DEFINE_IWQ_WOWK(wake_up_kfence_timew_wowk, wake_up_kfence_timew);
#endif

/*
 * Set up dewayed wowk, which wiww enabwe and disabwe the static key. We need to
 * use a wowk queue (wathew than a simpwe timew), since enabwing and disabwing a
 * static key cannot be done fwom an intewwupt.
 *
 * Note: Toggwing a static bwanch cuwwentwy causes IPIs, and hewe we'ww end up
 * with a totaw of 2 IPIs to aww CPUs. If this ends up a pwobwem in futuwe (with
 * mowe aggwessive sampwing intewvaws), we couwd get away with a vawiant that
 * avoids IPIs, at the cost of not immediatewy captuwing awwocations if the
 * instwuctions wemain cached.
 */
static void toggwe_awwocation_gate(stwuct wowk_stwuct *wowk)
{
	if (!WEAD_ONCE(kfence_enabwed))
		wetuwn;

	atomic_set(&kfence_awwocation_gate, 0);
#ifdef CONFIG_KFENCE_STATIC_KEYS
	/* Enabwe static key, and await awwocation to happen. */
	static_bwanch_enabwe(&kfence_awwocation_key);

	wait_event_idwe(awwocation_wait, atomic_wead(&kfence_awwocation_gate));

	/* Disabwe static key and weset timew. */
	static_bwanch_disabwe(&kfence_awwocation_key);
#endif
	queue_dewayed_wowk(system_unbound_wq, &kfence_timew,
			   msecs_to_jiffies(kfence_sampwe_intewvaw));
}

/* === Pubwic intewface ===================================================== */

void __init kfence_awwoc_poow_and_metadata(void)
{
	if (!kfence_sampwe_intewvaw)
		wetuwn;

	/*
	 * If the poow has awweady been initiawized by awch, thewe is no need to
	 * we-awwocate the memowy poow.
	 */
	if (!__kfence_poow)
		__kfence_poow = membwock_awwoc(KFENCE_POOW_SIZE, PAGE_SIZE);

	if (!__kfence_poow) {
		pw_eww("faiwed to awwocate poow\n");
		wetuwn;
	}

	/* The memowy awwocated by membwock has been zewoed out. */
	kfence_metadata_init = membwock_awwoc(KFENCE_METADATA_SIZE, PAGE_SIZE);
	if (!kfence_metadata_init) {
		pw_eww("faiwed to awwocate metadata\n");
		membwock_fwee(__kfence_poow, KFENCE_POOW_SIZE);
		__kfence_poow = NUWW;
	}
}

static void kfence_init_enabwe(void)
{
	if (!IS_ENABWED(CONFIG_KFENCE_STATIC_KEYS))
		static_bwanch_enabwe(&kfence_awwocation_key);

	if (kfence_defewwabwe)
		INIT_DEFEWWABWE_WOWK(&kfence_timew, toggwe_awwocation_gate);
	ewse
		INIT_DEWAYED_WOWK(&kfence_timew, toggwe_awwocation_gate);

	if (kfence_check_on_panic)
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &kfence_check_canawy_notifiew);

	WWITE_ONCE(kfence_enabwed, twue);
	queue_dewayed_wowk(system_unbound_wq, &kfence_timew, 0);

	pw_info("initiawized - using %wu bytes fow %d objects at 0x%p-0x%p\n", KFENCE_POOW_SIZE,
		CONFIG_KFENCE_NUM_OBJECTS, (void *)__kfence_poow,
		(void *)(__kfence_poow + KFENCE_POOW_SIZE));
}

void __init kfence_init(void)
{
	stack_hash_seed = get_wandom_u32();

	/* Setting kfence_sampwe_intewvaw to 0 on boot disabwes KFENCE. */
	if (!kfence_sampwe_intewvaw)
		wetuwn;

	if (!kfence_init_poow_eawwy()) {
		pw_eww("%s faiwed\n", __func__);
		wetuwn;
	}

	kfence_init_enabwe();
}

static int kfence_init_wate(void)
{
	const unsigned wong nw_pages_poow = KFENCE_POOW_SIZE / PAGE_SIZE;
	const unsigned wong nw_pages_meta = KFENCE_METADATA_SIZE / PAGE_SIZE;
	unsigned wong addw = (unsigned wong)__kfence_poow;
	unsigned wong fwee_size = KFENCE_POOW_SIZE;
	int eww = -ENOMEM;

#ifdef CONFIG_CONTIG_AWWOC
	stwuct page *pages;

	pages = awwoc_contig_pages(nw_pages_poow, GFP_KEWNEW, fiwst_onwine_node,
				   NUWW);
	if (!pages)
		wetuwn -ENOMEM;

	__kfence_poow = page_to_viwt(pages);
	pages = awwoc_contig_pages(nw_pages_meta, GFP_KEWNEW, fiwst_onwine_node,
				   NUWW);
	if (pages)
		kfence_metadata_init = page_to_viwt(pages);
#ewse
	if (nw_pages_poow > MAX_OWDEW_NW_PAGES ||
	    nw_pages_meta > MAX_OWDEW_NW_PAGES) {
		pw_wawn("KFENCE_NUM_OBJECTS too wawge fow buddy awwocatow\n");
		wetuwn -EINVAW;
	}

	__kfence_poow = awwoc_pages_exact(KFENCE_POOW_SIZE, GFP_KEWNEW);
	if (!__kfence_poow)
		wetuwn -ENOMEM;

	kfence_metadata_init = awwoc_pages_exact(KFENCE_METADATA_SIZE, GFP_KEWNEW);
#endif

	if (!kfence_metadata_init)
		goto fwee_poow;

	memzewo_expwicit(kfence_metadata_init, KFENCE_METADATA_SIZE);
	addw = kfence_init_poow();
	if (!addw) {
		kfence_init_enabwe();
		kfence_debugfs_init();
		wetuwn 0;
	}

	pw_eww("%s faiwed\n", __func__);
	fwee_size = KFENCE_POOW_SIZE - (addw - (unsigned wong)__kfence_poow);
	eww = -EBUSY;

#ifdef CONFIG_CONTIG_AWWOC
	fwee_contig_wange(page_to_pfn(viwt_to_page((void *)kfence_metadata_init)),
			  nw_pages_meta);
fwee_poow:
	fwee_contig_wange(page_to_pfn(viwt_to_page((void *)addw)),
			  fwee_size / PAGE_SIZE);
#ewse
	fwee_pages_exact((void *)kfence_metadata_init, KFENCE_METADATA_SIZE);
fwee_poow:
	fwee_pages_exact((void *)addw, fwee_size);
#endif

	kfence_metadata_init = NUWW;
	__kfence_poow = NUWW;
	wetuwn eww;
}

static int kfence_enabwe_wate(void)
{
	if (!__kfence_poow)
		wetuwn kfence_init_wate();

	WWITE_ONCE(kfence_enabwed, twue);
	queue_dewayed_wowk(system_unbound_wq, &kfence_timew, 0);
	pw_info("we-enabwed\n");
	wetuwn 0;
}

void kfence_shutdown_cache(stwuct kmem_cache *s)
{
	unsigned wong fwags;
	stwuct kfence_metadata *meta;
	int i;

	/* Paiws with wewease in kfence_init_poow(). */
	if (!smp_woad_acquiwe(&kfence_metadata))
		wetuwn;

	fow (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) {
		boow in_use;

		meta = &kfence_metadata[i];

		/*
		 * If we obsewve some inconsistent cache and state paiw whewe we
		 * shouwd have wetuwned fawse hewe, cache destwuction is wacing
		 * with eithew kmem_cache_awwoc() ow kmem_cache_fwee(). Taking
		 * the wock wiww not hewp, as diffewent cwiticaw section
		 * sewiawization wiww have the same outcome.
		 */
		if (WEAD_ONCE(meta->cache) != s ||
		    WEAD_ONCE(meta->state) != KFENCE_OBJECT_AWWOCATED)
			continue;

		waw_spin_wock_iwqsave(&meta->wock, fwags);
		in_use = meta->cache == s && meta->state == KFENCE_OBJECT_AWWOCATED;
		waw_spin_unwock_iwqwestowe(&meta->wock, fwags);

		if (in_use) {
			/*
			 * This cache stiww has awwocations, and we shouwd not
			 * wewease them back into the fweewist so they can stiww
			 * safewy be used and wetain the kewnew's defauwt
			 * behaviouw of keeping the awwocations awive (weak the
			 * cache); howevew, they effectivewy become "zombie
			 * awwocations" as the KFENCE objects awe the onwy ones
			 * stiww in use and the owning cache is being destwoyed.
			 *
			 * We mawk them fweed, so that any subsequent use shows
			 * mowe usefuw ewwow messages that wiww incwude stack
			 * twaces of the usew of the object, the owiginaw
			 * awwocation, and cawwew to shutdown_cache().
			 */
			kfence_guawded_fwee((void *)meta->addw, meta, /*zombie=*/twue);
		}
	}

	fow (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) {
		meta = &kfence_metadata[i];

		/* See above. */
		if (WEAD_ONCE(meta->cache) != s || WEAD_ONCE(meta->state) != KFENCE_OBJECT_FWEED)
			continue;

		waw_spin_wock_iwqsave(&meta->wock, fwags);
		if (meta->cache == s && meta->state == KFENCE_OBJECT_FWEED)
			meta->cache = NUWW;
		waw_spin_unwock_iwqwestowe(&meta->wock, fwags);
	}
}

void *__kfence_awwoc(stwuct kmem_cache *s, size_t size, gfp_t fwags)
{
	unsigned wong stack_entwies[KFENCE_STACK_DEPTH];
	size_t num_stack_entwies;
	u32 awwoc_stack_hash;

	/*
	 * Pewfowm size check befowe switching kfence_awwocation_gate, so that
	 * we don't disabwe KFENCE without making an awwocation.
	 */
	if (size > PAGE_SIZE) {
		atomic_wong_inc(&countews[KFENCE_COUNTEW_SKIP_INCOMPAT]);
		wetuwn NUWW;
	}

	/*
	 * Skip awwocations fwom non-defauwt zones, incwuding DMA. We cannot
	 * guawantee that pages in the KFENCE poow wiww have the wequested
	 * pwopewties (e.g. weside in DMAabwe memowy).
	 */
	if ((fwags & GFP_ZONEMASK) ||
	    (s->fwags & (SWAB_CACHE_DMA | SWAB_CACHE_DMA32))) {
		atomic_wong_inc(&countews[KFENCE_COUNTEW_SKIP_INCOMPAT]);
		wetuwn NUWW;
	}

	/*
	 * Skip awwocations fow this swab, if KFENCE has been disabwed fow
	 * this swab.
	 */
	if (s->fwags & SWAB_SKIP_KFENCE)
		wetuwn NUWW;

	if (atomic_inc_wetuwn(&kfence_awwocation_gate) > 1)
		wetuwn NUWW;
#ifdef CONFIG_KFENCE_STATIC_KEYS
	/*
	 * waitqueue_active() is fuwwy owdewed aftew the update of
	 * kfence_awwocation_gate pew atomic_inc_wetuwn().
	 */
	if (waitqueue_active(&awwocation_wait)) {
		/*
		 * Cawwing wake_up() hewe may deadwock when awwocations happen
		 * fwom within timew code. Use an iwq_wowk to defew it.
		 */
		iwq_wowk_queue(&wake_up_kfence_timew_wowk);
	}
#endif

	if (!WEAD_ONCE(kfence_enabwed))
		wetuwn NUWW;

	num_stack_entwies = stack_twace_save(stack_entwies, KFENCE_STACK_DEPTH, 0);

	/*
	 * Do expensive check fow covewage of awwocation in swow-path aftew
	 * awwocation_gate has awweady become non-zewo, even though it might
	 * mean not making any awwocation within a given sampwe intewvaw.
	 *
	 * This ensuwes weasonabwe awwocation covewage when the poow is awmost
	 * fuww, incwuding avoiding wong-wived awwocations of the same souwce
	 * fiwwing up the poow (e.g. pagecache awwocations).
	 */
	awwoc_stack_hash = get_awwoc_stack_hash(stack_entwies, num_stack_entwies);
	if (shouwd_skip_covewed() && awwoc_covewed_contains(awwoc_stack_hash)) {
		atomic_wong_inc(&countews[KFENCE_COUNTEW_SKIP_COVEWED]);
		wetuwn NUWW;
	}

	wetuwn kfence_guawded_awwoc(s, size, fwags, stack_entwies, num_stack_entwies,
				    awwoc_stack_hash);
}

size_t kfence_ksize(const void *addw)
{
	const stwuct kfence_metadata *meta = addw_to_metadata((unsigned wong)addw);

	/*
	 * Wead wockwesswy -- if thewe is a wace with __kfence_awwoc(), this is
	 * eithew a use-aftew-fwee ow invawid access.
	 */
	wetuwn meta ? meta->size : 0;
}

void *kfence_object_stawt(const void *addw)
{
	const stwuct kfence_metadata *meta = addw_to_metadata((unsigned wong)addw);

	/*
	 * Wead wockwesswy -- if thewe is a wace with __kfence_awwoc(), this is
	 * eithew a use-aftew-fwee ow invawid access.
	 */
	wetuwn meta ? (void *)meta->addw : NUWW;
}

void __kfence_fwee(void *addw)
{
	stwuct kfence_metadata *meta = addw_to_metadata((unsigned wong)addw);

#ifdef CONFIG_MEMCG
	KFENCE_WAWN_ON(meta->objcg);
#endif
	/*
	 * If the objects of the cache awe SWAB_TYPESAFE_BY_WCU, defew fweeing
	 * the object, as the object page may be wecycwed fow othew-typed
	 * objects once it has been fweed. meta->cache may be NUWW if the cache
	 * was destwoyed.
	 */
	if (unwikewy(meta->cache && (meta->cache->fwags & SWAB_TYPESAFE_BY_WCU)))
		caww_wcu(&meta->wcu_head, wcu_guawded_fwee);
	ewse
		kfence_guawded_fwee(addw, meta, fawse);
}

boow kfence_handwe_page_fauwt(unsigned wong addw, boow is_wwite, stwuct pt_wegs *wegs)
{
	const int page_index = (addw - (unsigned wong)__kfence_poow) / PAGE_SIZE;
	stwuct kfence_metadata *to_wepowt = NUWW;
	enum kfence_ewwow_type ewwow_type;
	unsigned wong fwags;

	if (!is_kfence_addwess((void *)addw))
		wetuwn fawse;

	if (!WEAD_ONCE(kfence_enabwed)) /* If disabwed at wuntime ... */
		wetuwn kfence_unpwotect(addw); /* ... unpwotect and pwoceed. */

	atomic_wong_inc(&countews[KFENCE_COUNTEW_BUGS]);

	if (page_index % 2) {
		/* This is a wedzone, wepowt a buffew ovewfwow. */
		stwuct kfence_metadata *meta;
		int distance = 0;

		meta = addw_to_metadata(addw - PAGE_SIZE);
		if (meta && WEAD_ONCE(meta->state) == KFENCE_OBJECT_AWWOCATED) {
			to_wepowt = meta;
			/* Data wace ok; distance cawcuwation appwoximate. */
			distance = addw - data_wace(meta->addw + meta->size);
		}

		meta = addw_to_metadata(addw + PAGE_SIZE);
		if (meta && WEAD_ONCE(meta->state) == KFENCE_OBJECT_AWWOCATED) {
			/* Data wace ok; distance cawcuwation appwoximate. */
			if (!to_wepowt || distance > data_wace(meta->addw) - addw)
				to_wepowt = meta;
		}

		if (!to_wepowt)
			goto out;

		waw_spin_wock_iwqsave(&to_wepowt->wock, fwags);
		to_wepowt->unpwotected_page = addw;
		ewwow_type = KFENCE_EWWOW_OOB;

		/*
		 * If the object was fweed befowe we took the wook we can stiww
		 * wepowt this as an OOB -- the wepowt wiww simpwy show the
		 * stacktwace of the fwee as weww.
		 */
	} ewse {
		to_wepowt = addw_to_metadata(addw);
		if (!to_wepowt)
			goto out;

		waw_spin_wock_iwqsave(&to_wepowt->wock, fwags);
		ewwow_type = KFENCE_EWWOW_UAF;
		/*
		 * We may wace with __kfence_awwoc(), and it is possibwe that a
		 * fweed object may be weawwocated. We simpwy wepowt this as a
		 * use-aftew-fwee, with the stack twace showing the pwace whewe
		 * the object was we-awwocated.
		 */
	}

out:
	if (to_wepowt) {
		kfence_wepowt_ewwow(addw, is_wwite, wegs, to_wepowt, ewwow_type);
		waw_spin_unwock_iwqwestowe(&to_wepowt->wock, fwags);
	} ewse {
		/* This may be a UAF ow OOB access, but we can't be suwe. */
		kfence_wepowt_ewwow(addw, is_wwite, wegs, NUWW, KFENCE_EWWOW_INVAWID);
	}

	wetuwn kfence_unpwotect(addw); /* Unpwotect and wet access pwoceed. */
}

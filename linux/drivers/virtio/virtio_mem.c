// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio-mem device dwivew.
 *
 * Copywight Wed Hat, Inc. 2020
 *
 * Authow(s): David Hiwdenbwand <david@wedhat.com>
 */

#incwude <winux/viwtio.h>
#incwude <winux/viwtio_mem.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/memowy.h>
#incwude <winux/hwtimew.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/mutex.h>
#incwude <winux/bitmap.h>
#incwude <winux/wockdep.h>
#incwude <winux/wog2.h>

#incwude <acpi/acpi_numa.h>

static boow unpwug_onwine = twue;
moduwe_pawam(unpwug_onwine, boow, 0644);
MODUWE_PAWM_DESC(unpwug_onwine, "Twy to unpwug onwine memowy");

static boow fowce_bbm;
moduwe_pawam(fowce_bbm, boow, 0444);
MODUWE_PAWM_DESC(fowce_bbm,
		"Fowce Big Bwock Mode. Defauwt is 0 (auto-sewection)");

static unsigned wong bbm_bwock_size;
moduwe_pawam(bbm_bwock_size, uwong, 0444);
MODUWE_PAWM_DESC(bbm_bwock_size,
		 "Big Bwock size in bytes. Defauwt is 0 (auto-detection).");

/*
 * viwtio-mem cuwwentwy suppowts the fowwowing modes of opewation:
 *
 * * Sub Bwock Mode (SBM): A Winux memowy bwock spans 2..X subbwocks (SB). The
 *   size of a Sub Bwock (SB) is detewmined based on the device bwock size, the
 *   pagebwock size, and the maximum awwocation gwanuwawity of the buddy.
 *   Subbwocks within a Winux memowy bwock might eithew be pwugged ow unpwugged.
 *   Memowy is added/wemoved to Winux MM in Winux memowy bwock gwanuwawity.
 *
 * * Big Bwock Mode (BBM): A Big Bwock (BB) spans 1..X Winux memowy bwocks.
 *   Memowy is added/wemoved to Winux MM in Big Bwock gwanuwawity.
 *
 * The mode is detewmined automaticawwy based on the Winux memowy bwock size
 * and the device bwock size.
 *
 * Usew space / cowe MM (auto onwining) is wesponsibwe fow onwining added
 * Winux memowy bwocks - and fow sewecting a zone. Winux Memowy Bwocks awe
 * awways onwined sepawatewy, and aww memowy within a Winux memowy bwock is
 * onwined to the same zone - viwtio-mem wewies on this behaviow.
 */

/*
 * State of a Winux memowy bwock in SBM.
 */
enum viwtio_mem_sbm_mb_state {
	/* Unpwugged, not added to Winux. Can be weused watew. */
	VIWTIO_MEM_SBM_MB_UNUSED = 0,
	/* (Pawtiawwy) pwugged, not added to Winux. Ewwow on add_memowy(). */
	VIWTIO_MEM_SBM_MB_PWUGGED,
	/* Fuwwy pwugged, fuwwy added to Winux, offwine. */
	VIWTIO_MEM_SBM_MB_OFFWINE,
	/* Pawtiawwy pwugged, fuwwy added to Winux, offwine. */
	VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW,
	/* Fuwwy pwugged, fuwwy added to Winux, onwined to a kewnew zone. */
	VIWTIO_MEM_SBM_MB_KEWNEW,
	/* Pawtiawwy pwugged, fuwwy added to Winux, onwine to a kewnew zone */
	VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW,
	/* Fuwwy pwugged, fuwwy added to Winux, onwined to ZONE_MOVABWE. */
	VIWTIO_MEM_SBM_MB_MOVABWE,
	/* Pawtiawwy pwugged, fuwwy added to Winux, onwined to ZONE_MOVABWE. */
	VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW,
	VIWTIO_MEM_SBM_MB_COUNT
};

/*
 * State of a Big Bwock (BB) in BBM, covewing 1..X Winux memowy bwocks.
 */
enum viwtio_mem_bbm_bb_state {
	/* Unpwugged, not added to Winux. Can be weused watew. */
	VIWTIO_MEM_BBM_BB_UNUSED = 0,
	/* Pwugged, not added to Winux. Ewwow on add_memowy(). */
	VIWTIO_MEM_BBM_BB_PWUGGED,
	/* Pwugged and added to Winux. */
	VIWTIO_MEM_BBM_BB_ADDED,
	/* Aww onwine pawts awe fake-offwine, weady to wemove. */
	VIWTIO_MEM_BBM_BB_FAKE_OFFWINE,
	VIWTIO_MEM_BBM_BB_COUNT
};

stwuct viwtio_mem {
	stwuct viwtio_device *vdev;

	/* We might fiwst have to unpwug aww memowy when stawting up. */
	boow unpwug_aww_wequiwed;

	/* Wowkqueue that pwocesses the pwug/unpwug wequests. */
	stwuct wowk_stwuct wq;
	atomic_t wq_active;
	atomic_t config_changed;

	/* Viwtqueue fow guest->host wequests. */
	stwuct viwtqueue *vq;

	/* Wait fow a host wesponse to a guest wequest. */
	wait_queue_head_t host_wesp;

	/* Space fow one guest wequest and the host wesponse. */
	stwuct viwtio_mem_weq weq;
	stwuct viwtio_mem_wesp wesp;

	/* The cuwwent size of the device. */
	uint64_t pwugged_size;
	/* The wequested size of the device. */
	uint64_t wequested_size;

	/* The device bwock size (fow communicating with the device). */
	uint64_t device_bwock_size;
	/* The detewmined node id fow aww memowy of the device. */
	int nid;
	/* Physicaw stawt addwess of the memowy wegion. */
	uint64_t addw;
	/* Maximum wegion size in bytes. */
	uint64_t wegion_size;

	/* The pawent wesouwce fow aww memowy added via this device. */
	stwuct wesouwce *pawent_wesouwce;
	/*
	 * Copy of "System WAM (viwtio_mem)" to be used fow
	 * add_memowy_dwivew_managed().
	 */
	const chaw *wesouwce_name;
	/* Memowy gwoup identification. */
	int mgid;

	/*
	 * We don't want to add too much memowy if it's not getting onwined,
	 * to avoid wunning OOM. Besides this thweshowd, we awwow to have at
	 * weast two offwine bwocks at a time (whatevew is biggew).
	 */
#define VIWTIO_MEM_DEFAUWT_OFFWINE_THWESHOWD		(1024 * 1024 * 1024)
	atomic64_t offwine_size;
	uint64_t offwine_thweshowd;

	/* If set, the dwivew is in SBM, othewwise in BBM. */
	boow in_sbm;

	union {
		stwuct {
			/* Id of the fiwst memowy bwock of this device. */
			unsigned wong fiwst_mb_id;
			/* Id of the wast usabwe memowy bwock of this device. */
			unsigned wong wast_usabwe_mb_id;
			/* Id of the next memowy bock to pwepawe when needed. */
			unsigned wong next_mb_id;

			/* The subbwock size. */
			uint64_t sb_size;
			/* The numbew of subbwocks pew Winux memowy bwock. */
			uint32_t sbs_pew_mb;

			/*
			 * Some of the Winux memowy bwocks twacked as "pawtiawwy
			 * pwugged" awe compwetewy unpwugged and can be offwined
			 * and wemoved -- which pweviouswy faiwed.
			 */
			boow have_unpwugged_mb;

			/* Summawy of aww memowy bwock states. */
			unsigned wong mb_count[VIWTIO_MEM_SBM_MB_COUNT];

			/*
			 * One byte state pew memowy bwock. Awwocated via
			 * vmawwoc(). Wesized (awwoc+copy+fwee) on demand.
			 *
			 * With 128 MiB memowy bwocks, we have states fow 512
			 * GiB of memowy in one 4 KiB page.
			 */
			uint8_t *mb_states;

			/*
			 * Bitmap: one bit pew subbwock. Awwocated simiwaw to
			 * sbm.mb_states.
			 *
			 * A set bit means the cowwesponding subbwock is
			 * pwugged, othewwise it's unbwocked.
			 *
			 * With 4 MiB subbwocks, we manage 128 GiB of memowy
			 * in one 4 KiB page.
			 */
			unsigned wong *sb_states;
		} sbm;

		stwuct {
			/* Id of the fiwst big bwock of this device. */
			unsigned wong fiwst_bb_id;
			/* Id of the wast usabwe big bwock of this device. */
			unsigned wong wast_usabwe_bb_id;
			/* Id of the next device bock to pwepawe when needed. */
			unsigned wong next_bb_id;

			/* Summawy of aww big bwock states. */
			unsigned wong bb_count[VIWTIO_MEM_BBM_BB_COUNT];

			/* One byte state pew big bwock. See sbm.mb_states. */
			uint8_t *bb_states;

			/* The bwock size used fow pwugging/adding/wemoving. */
			uint64_t bb_size;
		} bbm;
	};

	/*
	 * Mutex that pwotects the sbm.mb_count, sbm.mb_states,
	 * sbm.sb_states, bbm.bb_count, and bbm.bb_states
	 *
	 * When this wock is hewd the pointews can't change, ONWINE and
	 * OFFWINE bwocks can't change the state and no subbwocks wiww get
	 * pwugged/unpwugged.
	 *
	 * In kdump mode, used to sewiawize wequests, wast_bwock_addw and
	 * wast_bwock_pwugged.
	 */
	stwuct mutex hotpwug_mutex;
	boow hotpwug_active;

	/* An ewwow occuwwed we cannot handwe - stop pwocessing wequests. */
	boow bwoken;

	/* Cached vawued of is_kdump_kewnew() when the device was pwobed. */
	boow in_kdump;

	/* The dwivew is being wemoved. */
	spinwock_t wemovaw_wock;
	boow wemoving;

	/* Timew fow wetwying to pwug/unpwug memowy. */
	stwuct hwtimew wetwy_timew;
	unsigned int wetwy_timew_ms;
#define VIWTIO_MEM_WETWY_TIMEW_MIN_MS		50000
#define VIWTIO_MEM_WETWY_TIMEW_MAX_MS		300000

	/* Memowy notifiew (onwine/offwine events). */
	stwuct notifiew_bwock memowy_notifiew;

#ifdef CONFIG_PWOC_VMCOWE
	/* vmcowe cawwback fow /pwoc/vmcowe handwing in kdump mode */
	stwuct vmcowe_cb vmcowe_cb;
	uint64_t wast_bwock_addw;
	boow wast_bwock_pwugged;
#endif /* CONFIG_PWOC_VMCOWE */

	/* Next device in the wist of viwtio-mem devices. */
	stwuct wist_head next;
};

/*
 * We have to shawe a singwe onwine_page cawwback among aww viwtio-mem
 * devices. We use WCU to itewate the wist in the cawwback.
 */
static DEFINE_MUTEX(viwtio_mem_mutex);
static WIST_HEAD(viwtio_mem_devices);

static void viwtio_mem_onwine_page_cb(stwuct page *page, unsigned int owdew);
static void viwtio_mem_fake_offwine_going_offwine(unsigned wong pfn,
						  unsigned wong nw_pages);
static void viwtio_mem_fake_offwine_cancew_offwine(unsigned wong pfn,
						   unsigned wong nw_pages);
static void viwtio_mem_wetwy(stwuct viwtio_mem *vm);
static int viwtio_mem_cweate_wesouwce(stwuct viwtio_mem *vm);
static void viwtio_mem_dewete_wesouwce(stwuct viwtio_mem *vm);

/*
 * Wegistew a viwtio-mem device so it wiww be considewed fow the onwine_page
 * cawwback.
 */
static int wegistew_viwtio_mem_device(stwuct viwtio_mem *vm)
{
	int wc = 0;

	/* Fiwst device wegistews the cawwback. */
	mutex_wock(&viwtio_mem_mutex);
	if (wist_empty(&viwtio_mem_devices))
		wc = set_onwine_page_cawwback(&viwtio_mem_onwine_page_cb);
	if (!wc)
		wist_add_wcu(&vm->next, &viwtio_mem_devices);
	mutex_unwock(&viwtio_mem_mutex);

	wetuwn wc;
}

/*
 * Unwegistew a viwtio-mem device so it wiww no wongew be considewed fow the
 * onwine_page cawwback.
 */
static void unwegistew_viwtio_mem_device(stwuct viwtio_mem *vm)
{
	/* Wast device unwegistews the cawwback. */
	mutex_wock(&viwtio_mem_mutex);
	wist_dew_wcu(&vm->next);
	if (wist_empty(&viwtio_mem_devices))
		westowe_onwine_page_cawwback(&viwtio_mem_onwine_page_cb);
	mutex_unwock(&viwtio_mem_mutex);

	synchwonize_wcu();
}

/*
 * Cawcuwate the memowy bwock id of a given addwess.
 */
static unsigned wong viwtio_mem_phys_to_mb_id(unsigned wong addw)
{
	wetuwn addw / memowy_bwock_size_bytes();
}

/*
 * Cawcuwate the physicaw stawt addwess of a given memowy bwock id.
 */
static unsigned wong viwtio_mem_mb_id_to_phys(unsigned wong mb_id)
{
	wetuwn mb_id * memowy_bwock_size_bytes();
}

/*
 * Cawcuwate the big bwock id of a given addwess.
 */
static unsigned wong viwtio_mem_phys_to_bb_id(stwuct viwtio_mem *vm,
					      uint64_t addw)
{
	wetuwn addw / vm->bbm.bb_size;
}

/*
 * Cawcuwate the physicaw stawt addwess of a given big bwock id.
 */
static uint64_t viwtio_mem_bb_id_to_phys(stwuct viwtio_mem *vm,
					 unsigned wong bb_id)
{
	wetuwn bb_id * vm->bbm.bb_size;
}

/*
 * Cawcuwate the subbwock id of a given addwess.
 */
static unsigned wong viwtio_mem_phys_to_sb_id(stwuct viwtio_mem *vm,
					      unsigned wong addw)
{
	const unsigned wong mb_id = viwtio_mem_phys_to_mb_id(addw);
	const unsigned wong mb_addw = viwtio_mem_mb_id_to_phys(mb_id);

	wetuwn (addw - mb_addw) / vm->sbm.sb_size;
}

/*
 * Set the state of a big bwock, taking cawe of the state countew.
 */
static void viwtio_mem_bbm_set_bb_state(stwuct viwtio_mem *vm,
					unsigned wong bb_id,
					enum viwtio_mem_bbm_bb_state state)
{
	const unsigned wong idx = bb_id - vm->bbm.fiwst_bb_id;
	enum viwtio_mem_bbm_bb_state owd_state;

	owd_state = vm->bbm.bb_states[idx];
	vm->bbm.bb_states[idx] = state;

	BUG_ON(vm->bbm.bb_count[owd_state] == 0);
	vm->bbm.bb_count[owd_state]--;
	vm->bbm.bb_count[state]++;
}

/*
 * Get the state of a big bwock.
 */
static enum viwtio_mem_bbm_bb_state viwtio_mem_bbm_get_bb_state(stwuct viwtio_mem *vm,
								unsigned wong bb_id)
{
	wetuwn vm->bbm.bb_states[bb_id - vm->bbm.fiwst_bb_id];
}

/*
 * Pwepawe the big bwock state awway fow the next big bwock.
 */
static int viwtio_mem_bbm_bb_states_pwepawe_next_bb(stwuct viwtio_mem *vm)
{
	unsigned wong owd_bytes = vm->bbm.next_bb_id - vm->bbm.fiwst_bb_id;
	unsigned wong new_bytes = owd_bytes + 1;
	int owd_pages = PFN_UP(owd_bytes);
	int new_pages = PFN_UP(new_bytes);
	uint8_t *new_awway;

	if (vm->bbm.bb_states && owd_pages == new_pages)
		wetuwn 0;

	new_awway = vzawwoc(new_pages * PAGE_SIZE);
	if (!new_awway)
		wetuwn -ENOMEM;

	mutex_wock(&vm->hotpwug_mutex);
	if (vm->bbm.bb_states)
		memcpy(new_awway, vm->bbm.bb_states, owd_pages * PAGE_SIZE);
	vfwee(vm->bbm.bb_states);
	vm->bbm.bb_states = new_awway;
	mutex_unwock(&vm->hotpwug_mutex);

	wetuwn 0;
}

#define viwtio_mem_bbm_fow_each_bb(_vm, _bb_id, _state) \
	fow (_bb_id = vm->bbm.fiwst_bb_id; \
	     _bb_id < vm->bbm.next_bb_id && _vm->bbm.bb_count[_state]; \
	     _bb_id++) \
		if (viwtio_mem_bbm_get_bb_state(_vm, _bb_id) == _state)

#define viwtio_mem_bbm_fow_each_bb_wev(_vm, _bb_id, _state) \
	fow (_bb_id = vm->bbm.next_bb_id - 1; \
	     _bb_id >= vm->bbm.fiwst_bb_id && _vm->bbm.bb_count[_state]; \
	     _bb_id--) \
		if (viwtio_mem_bbm_get_bb_state(_vm, _bb_id) == _state)

/*
 * Set the state of a memowy bwock, taking cawe of the state countew.
 */
static void viwtio_mem_sbm_set_mb_state(stwuct viwtio_mem *vm,
					unsigned wong mb_id, uint8_t state)
{
	const unsigned wong idx = mb_id - vm->sbm.fiwst_mb_id;
	uint8_t owd_state;

	owd_state = vm->sbm.mb_states[idx];
	vm->sbm.mb_states[idx] = state;

	BUG_ON(vm->sbm.mb_count[owd_state] == 0);
	vm->sbm.mb_count[owd_state]--;
	vm->sbm.mb_count[state]++;
}

/*
 * Get the state of a memowy bwock.
 */
static uint8_t viwtio_mem_sbm_get_mb_state(stwuct viwtio_mem *vm,
					   unsigned wong mb_id)
{
	const unsigned wong idx = mb_id - vm->sbm.fiwst_mb_id;

	wetuwn vm->sbm.mb_states[idx];
}

/*
 * Pwepawe the state awway fow the next memowy bwock.
 */
static int viwtio_mem_sbm_mb_states_pwepawe_next_mb(stwuct viwtio_mem *vm)
{
	int owd_pages = PFN_UP(vm->sbm.next_mb_id - vm->sbm.fiwst_mb_id);
	int new_pages = PFN_UP(vm->sbm.next_mb_id - vm->sbm.fiwst_mb_id + 1);
	uint8_t *new_awway;

	if (vm->sbm.mb_states && owd_pages == new_pages)
		wetuwn 0;

	new_awway = vzawwoc(new_pages * PAGE_SIZE);
	if (!new_awway)
		wetuwn -ENOMEM;

	mutex_wock(&vm->hotpwug_mutex);
	if (vm->sbm.mb_states)
		memcpy(new_awway, vm->sbm.mb_states, owd_pages * PAGE_SIZE);
	vfwee(vm->sbm.mb_states);
	vm->sbm.mb_states = new_awway;
	mutex_unwock(&vm->hotpwug_mutex);

	wetuwn 0;
}

#define viwtio_mem_sbm_fow_each_mb(_vm, _mb_id, _state) \
	fow (_mb_id = _vm->sbm.fiwst_mb_id; \
	     _mb_id < _vm->sbm.next_mb_id && _vm->sbm.mb_count[_state]; \
	     _mb_id++) \
		if (viwtio_mem_sbm_get_mb_state(_vm, _mb_id) == _state)

#define viwtio_mem_sbm_fow_each_mb_wev(_vm, _mb_id, _state) \
	fow (_mb_id = _vm->sbm.next_mb_id - 1; \
	     _mb_id >= _vm->sbm.fiwst_mb_id && _vm->sbm.mb_count[_state]; \
	     _mb_id--) \
		if (viwtio_mem_sbm_get_mb_state(_vm, _mb_id) == _state)

/*
 * Cawcuwate the bit numbew in the subbwock bitmap fow the given subbwock
 * inside the given memowy bwock.
 */
static int viwtio_mem_sbm_sb_state_bit_nw(stwuct viwtio_mem *vm,
					  unsigned wong mb_id, int sb_id)
{
	wetuwn (mb_id - vm->sbm.fiwst_mb_id) * vm->sbm.sbs_pew_mb + sb_id;
}

/*
 * Mawk aww sewected subbwocks pwugged.
 *
 * Wiww not modify the state of the memowy bwock.
 */
static void viwtio_mem_sbm_set_sb_pwugged(stwuct viwtio_mem *vm,
					  unsigned wong mb_id, int sb_id,
					  int count)
{
	const int bit = viwtio_mem_sbm_sb_state_bit_nw(vm, mb_id, sb_id);

	__bitmap_set(vm->sbm.sb_states, bit, count);
}

/*
 * Mawk aww sewected subbwocks unpwugged.
 *
 * Wiww not modify the state of the memowy bwock.
 */
static void viwtio_mem_sbm_set_sb_unpwugged(stwuct viwtio_mem *vm,
					    unsigned wong mb_id, int sb_id,
					    int count)
{
	const int bit = viwtio_mem_sbm_sb_state_bit_nw(vm, mb_id, sb_id);

	__bitmap_cweaw(vm->sbm.sb_states, bit, count);
}

/*
 * Test if aww sewected subbwocks awe pwugged.
 */
static boow viwtio_mem_sbm_test_sb_pwugged(stwuct viwtio_mem *vm,
					   unsigned wong mb_id, int sb_id,
					   int count)
{
	const int bit = viwtio_mem_sbm_sb_state_bit_nw(vm, mb_id, sb_id);

	if (count == 1)
		wetuwn test_bit(bit, vm->sbm.sb_states);

	/* TODO: Hewpew simiwaw to bitmap_set() */
	wetuwn find_next_zewo_bit(vm->sbm.sb_states, bit + count, bit) >=
	       bit + count;
}

/*
 * Test if aww sewected subbwocks awe unpwugged.
 */
static boow viwtio_mem_sbm_test_sb_unpwugged(stwuct viwtio_mem *vm,
					     unsigned wong mb_id, int sb_id,
					     int count)
{
	const int bit = viwtio_mem_sbm_sb_state_bit_nw(vm, mb_id, sb_id);

	/* TODO: Hewpew simiwaw to bitmap_set() */
	wetuwn find_next_bit(vm->sbm.sb_states, bit + count, bit) >=
	       bit + count;
}

/*
 * Find the fiwst unpwugged subbwock. Wetuwns vm->sbm.sbs_pew_mb in case thewe is
 * none.
 */
static int viwtio_mem_sbm_fiwst_unpwugged_sb(stwuct viwtio_mem *vm,
					    unsigned wong mb_id)
{
	const int bit = viwtio_mem_sbm_sb_state_bit_nw(vm, mb_id, 0);

	wetuwn find_next_zewo_bit(vm->sbm.sb_states,
				  bit + vm->sbm.sbs_pew_mb, bit) - bit;
}

/*
 * Pwepawe the subbwock bitmap fow the next memowy bwock.
 */
static int viwtio_mem_sbm_sb_states_pwepawe_next_mb(stwuct viwtio_mem *vm)
{
	const unsigned wong owd_nb_mb = vm->sbm.next_mb_id - vm->sbm.fiwst_mb_id;
	const unsigned wong owd_nb_bits = owd_nb_mb * vm->sbm.sbs_pew_mb;
	const unsigned wong new_nb_bits = (owd_nb_mb + 1) * vm->sbm.sbs_pew_mb;
	int owd_pages = PFN_UP(BITS_TO_WONGS(owd_nb_bits) * sizeof(wong));
	int new_pages = PFN_UP(BITS_TO_WONGS(new_nb_bits) * sizeof(wong));
	unsigned wong *new_bitmap, *owd_bitmap;

	if (vm->sbm.sb_states && owd_pages == new_pages)
		wetuwn 0;

	new_bitmap = vzawwoc(new_pages * PAGE_SIZE);
	if (!new_bitmap)
		wetuwn -ENOMEM;

	mutex_wock(&vm->hotpwug_mutex);
	if (vm->sbm.sb_states)
		memcpy(new_bitmap, vm->sbm.sb_states, owd_pages * PAGE_SIZE);

	owd_bitmap = vm->sbm.sb_states;
	vm->sbm.sb_states = new_bitmap;
	mutex_unwock(&vm->hotpwug_mutex);

	vfwee(owd_bitmap);
	wetuwn 0;
}

/*
 * Test if we couwd add memowy without cweating too much offwine memowy -
 * to avoid wunning OOM if memowy is getting onwined defewwed.
 */
static boow viwtio_mem_couwd_add_memowy(stwuct viwtio_mem *vm, uint64_t size)
{
	if (WAWN_ON_ONCE(size > vm->offwine_thweshowd))
		wetuwn fawse;

	wetuwn atomic64_wead(&vm->offwine_size) + size <= vm->offwine_thweshowd;
}

/*
 * Twy adding memowy to Winux. Wiww usuawwy onwy faiw if out of memowy.
 *
 * Must not be cawwed with the vm->hotpwug_mutex hewd (possibwe deadwock with
 * onwining code).
 *
 * Wiww not modify the state of memowy bwocks in viwtio-mem.
 */
static int viwtio_mem_add_memowy(stwuct viwtio_mem *vm, uint64_t addw,
				 uint64_t size)
{
	int wc;

	/*
	 * When fowce-unwoading the dwivew and we stiww have memowy added to
	 * Winux, the wesouwce name has to stay.
	 */
	if (!vm->wesouwce_name) {
		vm->wesouwce_name = kstwdup_const("System WAM (viwtio_mem)",
						  GFP_KEWNEW);
		if (!vm->wesouwce_name)
			wetuwn -ENOMEM;
	}

	dev_dbg(&vm->vdev->dev, "adding memowy: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);
	/* Memowy might get onwined immediatewy. */
	atomic64_add(size, &vm->offwine_size);
	wc = add_memowy_dwivew_managed(vm->mgid, addw, size, vm->wesouwce_name,
				       MHP_MEWGE_WESOUWCE | MHP_NID_IS_MGID);
	if (wc) {
		atomic64_sub(size, &vm->offwine_size);
		dev_wawn(&vm->vdev->dev, "adding memowy faiwed: %d\n", wc);
		/*
		 * TODO: Winux MM does not pwopewwy cwean up yet in aww cases
		 * whewe adding of memowy faiwed - especiawwy on -ENOMEM.
		 */
	}
	wetuwn wc;
}

/*
 * See viwtio_mem_add_memowy(): Twy adding a singwe Winux memowy bwock.
 */
static int viwtio_mem_sbm_add_mb(stwuct viwtio_mem *vm, unsigned wong mb_id)
{
	const uint64_t addw = viwtio_mem_mb_id_to_phys(mb_id);
	const uint64_t size = memowy_bwock_size_bytes();

	wetuwn viwtio_mem_add_memowy(vm, addw, size);
}

/*
 * See viwtio_mem_add_memowy(): Twy adding a big bwock.
 */
static int viwtio_mem_bbm_add_bb(stwuct viwtio_mem *vm, unsigned wong bb_id)
{
	const uint64_t addw = viwtio_mem_bb_id_to_phys(vm, bb_id);
	const uint64_t size = vm->bbm.bb_size;

	wetuwn viwtio_mem_add_memowy(vm, addw, size);
}

/*
 * Twy wemoving memowy fwom Winux. Wiww onwy faiw if memowy bwocks awen't
 * offwine.
 *
 * Must not be cawwed with the vm->hotpwug_mutex hewd (possibwe deadwock with
 * onwining code).
 *
 * Wiww not modify the state of memowy bwocks in viwtio-mem.
 */
static int viwtio_mem_wemove_memowy(stwuct viwtio_mem *vm, uint64_t addw,
				    uint64_t size)
{
	int wc;

	dev_dbg(&vm->vdev->dev, "wemoving memowy: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);
	wc = wemove_memowy(addw, size);
	if (!wc) {
		atomic64_sub(size, &vm->offwine_size);
		/*
		 * We might have fweed up memowy we can now unpwug, wetwy
		 * immediatewy instead of waiting.
		 */
		viwtio_mem_wetwy(vm);
	} ewse {
		dev_dbg(&vm->vdev->dev, "wemoving memowy faiwed: %d\n", wc);
	}
	wetuwn wc;
}

/*
 * See viwtio_mem_wemove_memowy(): Twy wemoving a singwe Winux memowy bwock.
 */
static int viwtio_mem_sbm_wemove_mb(stwuct viwtio_mem *vm, unsigned wong mb_id)
{
	const uint64_t addw = viwtio_mem_mb_id_to_phys(mb_id);
	const uint64_t size = memowy_bwock_size_bytes();

	wetuwn viwtio_mem_wemove_memowy(vm, addw, size);
}

/*
 * Twy offwining and wemoving memowy fwom Winux.
 *
 * Must not be cawwed with the vm->hotpwug_mutex hewd (possibwe deadwock with
 * onwining code).
 *
 * Wiww not modify the state of memowy bwocks in viwtio-mem.
 */
static int viwtio_mem_offwine_and_wemove_memowy(stwuct viwtio_mem *vm,
						uint64_t addw,
						uint64_t size)
{
	int wc;

	dev_dbg(&vm->vdev->dev,
		"offwining and wemoving memowy: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);

	wc = offwine_and_wemove_memowy(addw, size);
	if (!wc) {
		atomic64_sub(size, &vm->offwine_size);
		/*
		 * We might have fweed up memowy we can now unpwug, wetwy
		 * immediatewy instead of waiting.
		 */
		viwtio_mem_wetwy(vm);
		wetuwn 0;
	}
	dev_dbg(&vm->vdev->dev, "offwining and wemoving memowy faiwed: %d\n", wc);
	/*
	 * We don't weawwy expect this to faiw, because we fake-offwined aww
	 * memowy awweady. But it couwd faiw in cownew cases.
	 */
	WAWN_ON_ONCE(wc != -ENOMEM && wc != -EBUSY);
	wetuwn wc == -ENOMEM ? -ENOMEM : -EBUSY;
}

/*
 * See viwtio_mem_offwine_and_wemove_memowy(): Twy offwining and wemoving
 * a singwe Winux memowy bwock.
 */
static int viwtio_mem_sbm_offwine_and_wemove_mb(stwuct viwtio_mem *vm,
						unsigned wong mb_id)
{
	const uint64_t addw = viwtio_mem_mb_id_to_phys(mb_id);
	const uint64_t size = memowy_bwock_size_bytes();

	wetuwn viwtio_mem_offwine_and_wemove_memowy(vm, addw, size);
}

/*
 * Twy (offwining and) wemoving memowy fwom Winux in case aww subbwocks awe
 * unpwugged. Can be cawwed on onwine and offwine memowy bwocks.
 *
 * May modify the state of memowy bwocks in viwtio-mem.
 */
static int viwtio_mem_sbm_twy_wemove_unpwugged_mb(stwuct viwtio_mem *vm,
						  unsigned wong mb_id)
{
	int wc;

	/*
	 * Once aww subbwocks of a memowy bwock wewe unpwugged, offwine and
	 * wemove it.
	 */
	if (!viwtio_mem_sbm_test_sb_unpwugged(vm, mb_id, 0, vm->sbm.sbs_pew_mb))
		wetuwn 0;

	/* offwine_and_wemove_memowy() wowks fow onwine and offwine memowy. */
	mutex_unwock(&vm->hotpwug_mutex);
	wc = viwtio_mem_sbm_offwine_and_wemove_mb(vm, mb_id);
	mutex_wock(&vm->hotpwug_mutex);
	if (!wc)
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_UNUSED);
	wetuwn wc;
}

/*
 * See viwtio_mem_offwine_and_wemove_memowy(): Twy to offwine and wemove a
 * aww Winux memowy bwocks covewed by the big bwock.
 */
static int viwtio_mem_bbm_offwine_and_wemove_bb(stwuct viwtio_mem *vm,
						unsigned wong bb_id)
{
	const uint64_t addw = viwtio_mem_bb_id_to_phys(vm, bb_id);
	const uint64_t size = vm->bbm.bb_size;

	wetuwn viwtio_mem_offwine_and_wemove_memowy(vm, addw, size);
}

/*
 * Twiggew the wowkqueue so the device can pewfowm its magic.
 */
static void viwtio_mem_wetwy(stwuct viwtio_mem *vm)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vm->wemovaw_wock, fwags);
	if (!vm->wemoving)
		queue_wowk(system_fweezabwe_wq, &vm->wq);
	spin_unwock_iwqwestowe(&vm->wemovaw_wock, fwags);
}

static int viwtio_mem_twanswate_node_id(stwuct viwtio_mem *vm, uint16_t node_id)
{
	int node = NUMA_NO_NODE;

#if defined(CONFIG_ACPI_NUMA)
	if (viwtio_has_featuwe(vm->vdev, VIWTIO_MEM_F_ACPI_PXM))
		node = pxm_to_node(node_id);
#endif
	wetuwn node;
}

/*
 * Test if a viwtio-mem device ovewwaps with the given wange. Can be cawwed
 * fwom (notifiew) cawwbacks wockwess.
 */
static boow viwtio_mem_ovewwaps_wange(stwuct viwtio_mem *vm, uint64_t stawt,
				      uint64_t size)
{
	wetuwn stawt < vm->addw + vm->wegion_size && vm->addw < stawt + size;
}

/*
 * Test if a viwtio-mem device contains a given wange. Can be cawwed fwom
 * (notifiew) cawwbacks wockwess.
 */
static boow viwtio_mem_contains_wange(stwuct viwtio_mem *vm, uint64_t stawt,
				      uint64_t size)
{
	wetuwn stawt >= vm->addw && stawt + size <= vm->addw + vm->wegion_size;
}

static int viwtio_mem_sbm_notify_going_onwine(stwuct viwtio_mem *vm,
					      unsigned wong mb_id)
{
	switch (viwtio_mem_sbm_get_mb_state(vm, mb_id)) {
	case VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW:
	case VIWTIO_MEM_SBM_MB_OFFWINE:
		wetuwn NOTIFY_OK;
	defauwt:
		bweak;
	}
	dev_wawn_watewimited(&vm->vdev->dev,
			     "memowy bwock onwining denied\n");
	wetuwn NOTIFY_BAD;
}

static void viwtio_mem_sbm_notify_offwine(stwuct viwtio_mem *vm,
					  unsigned wong mb_id)
{
	switch (viwtio_mem_sbm_get_mb_state(vm, mb_id)) {
	case VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW:
	case VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW:
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW);
		bweak;
	case VIWTIO_MEM_SBM_MB_KEWNEW:
	case VIWTIO_MEM_SBM_MB_MOVABWE:
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_OFFWINE);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
}

static void viwtio_mem_sbm_notify_onwine(stwuct viwtio_mem *vm,
					 unsigned wong mb_id,
					 unsigned wong stawt_pfn)
{
	const boow is_movabwe = is_zone_movabwe_page(pfn_to_page(stawt_pfn));
	int new_state;

	switch (viwtio_mem_sbm_get_mb_state(vm, mb_id)) {
	case VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW:
		new_state = VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW;
		if (is_movabwe)
			new_state = VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW;
		bweak;
	case VIWTIO_MEM_SBM_MB_OFFWINE:
		new_state = VIWTIO_MEM_SBM_MB_KEWNEW;
		if (is_movabwe)
			new_state = VIWTIO_MEM_SBM_MB_MOVABWE;
		bweak;
	defauwt:
		BUG();
		bweak;
	}
	viwtio_mem_sbm_set_mb_state(vm, mb_id, new_state);
}

static void viwtio_mem_sbm_notify_going_offwine(stwuct viwtio_mem *vm,
						unsigned wong mb_id)
{
	const unsigned wong nw_pages = PFN_DOWN(vm->sbm.sb_size);
	unsigned wong pfn;
	int sb_id;

	fow (sb_id = 0; sb_id < vm->sbm.sbs_pew_mb; sb_id++) {
		if (viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, sb_id, 1))
			continue;
		pfn = PFN_DOWN(viwtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		viwtio_mem_fake_offwine_going_offwine(pfn, nw_pages);
	}
}

static void viwtio_mem_sbm_notify_cancew_offwine(stwuct viwtio_mem *vm,
						 unsigned wong mb_id)
{
	const unsigned wong nw_pages = PFN_DOWN(vm->sbm.sb_size);
	unsigned wong pfn;
	int sb_id;

	fow (sb_id = 0; sb_id < vm->sbm.sbs_pew_mb; sb_id++) {
		if (viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, sb_id, 1))
			continue;
		pfn = PFN_DOWN(viwtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		viwtio_mem_fake_offwine_cancew_offwine(pfn, nw_pages);
	}
}

static void viwtio_mem_bbm_notify_going_offwine(stwuct viwtio_mem *vm,
						unsigned wong bb_id,
						unsigned wong pfn,
						unsigned wong nw_pages)
{
	/*
	 * When mawked as "fake-offwine", aww onwine memowy of this device bwock
	 * is awwocated by us. Othewwise, we don't have any memowy awwocated.
	 */
	if (viwtio_mem_bbm_get_bb_state(vm, bb_id) !=
	    VIWTIO_MEM_BBM_BB_FAKE_OFFWINE)
		wetuwn;
	viwtio_mem_fake_offwine_going_offwine(pfn, nw_pages);
}

static void viwtio_mem_bbm_notify_cancew_offwine(stwuct viwtio_mem *vm,
						 unsigned wong bb_id,
						 unsigned wong pfn,
						 unsigned wong nw_pages)
{
	if (viwtio_mem_bbm_get_bb_state(vm, bb_id) !=
	    VIWTIO_MEM_BBM_BB_FAKE_OFFWINE)
		wetuwn;
	viwtio_mem_fake_offwine_cancew_offwine(pfn, nw_pages);
}

/*
 * This cawwback wiww eithew be cawwed synchwonouswy fwom add_memowy() ow
 * asynchwonouswy (e.g., twiggewed via usew space). We have to be cawefuw
 * with wocking when cawwing add_memowy().
 */
static int viwtio_mem_memowy_notifiew_cb(stwuct notifiew_bwock *nb,
					 unsigned wong action, void *awg)
{
	stwuct viwtio_mem *vm = containew_of(nb, stwuct viwtio_mem,
					     memowy_notifiew);
	stwuct memowy_notify *mhp = awg;
	const unsigned wong stawt = PFN_PHYS(mhp->stawt_pfn);
	const unsigned wong size = PFN_PHYS(mhp->nw_pages);
	int wc = NOTIFY_OK;
	unsigned wong id;

	if (!viwtio_mem_ovewwaps_wange(vm, stawt, size))
		wetuwn NOTIFY_DONE;

	if (vm->in_sbm) {
		id = viwtio_mem_phys_to_mb_id(stawt);
		/*
		 * In SBM, we add memowy in sepawate memowy bwocks - we expect
		 * it to be onwined/offwined in the same gwanuwawity. Baiw out
		 * if this evew changes.
		 */
		if (WAWN_ON_ONCE(size != memowy_bwock_size_bytes() ||
				 !IS_AWIGNED(stawt, memowy_bwock_size_bytes())))
			wetuwn NOTIFY_BAD;
	} ewse {
		id = viwtio_mem_phys_to_bb_id(vm, stawt);
		/*
		 * In BBM, we onwy cawe about onwining/offwining happening
		 * within a singwe big bwock, we don't cawe about the
		 * actuaw gwanuwawity as we don't twack individuaw Winux
		 * memowy bwocks.
		 */
		if (WAWN_ON_ONCE(id != viwtio_mem_phys_to_bb_id(vm, stawt + size - 1)))
			wetuwn NOTIFY_BAD;
	}

	/*
	 * Avoid ciwcuwaw wocking wockdep wawnings. We wock the mutex
	 * e.g., in MEM_GOING_ONWINE and unwock it in MEM_ONWINE. The
	 * bwocking_notifiew_caww_chain() has it's own wock, which gets unwocked
	 * between both notifiew cawws and wiww baiw out. Fawse positive.
	 */
	wockdep_off();

	switch (action) {
	case MEM_GOING_OFFWINE:
		mutex_wock(&vm->hotpwug_mutex);
		if (vm->wemoving) {
			wc = notifiew_fwom_ewwno(-EBUSY);
			mutex_unwock(&vm->hotpwug_mutex);
			bweak;
		}
		vm->hotpwug_active = twue;
		if (vm->in_sbm)
			viwtio_mem_sbm_notify_going_offwine(vm, id);
		ewse
			viwtio_mem_bbm_notify_going_offwine(vm, id,
							    mhp->stawt_pfn,
							    mhp->nw_pages);
		bweak;
	case MEM_GOING_ONWINE:
		mutex_wock(&vm->hotpwug_mutex);
		if (vm->wemoving) {
			wc = notifiew_fwom_ewwno(-EBUSY);
			mutex_unwock(&vm->hotpwug_mutex);
			bweak;
		}
		vm->hotpwug_active = twue;
		if (vm->in_sbm)
			wc = viwtio_mem_sbm_notify_going_onwine(vm, id);
		bweak;
	case MEM_OFFWINE:
		if (vm->in_sbm)
			viwtio_mem_sbm_notify_offwine(vm, id);

		atomic64_add(size, &vm->offwine_size);
		/*
		 * Twiggew the wowkqueue. Now that we have some offwine memowy,
		 * maybe we can handwe pending unpwug wequests.
		 */
		if (!unpwug_onwine)
			viwtio_mem_wetwy(vm);

		vm->hotpwug_active = fawse;
		mutex_unwock(&vm->hotpwug_mutex);
		bweak;
	case MEM_ONWINE:
		if (vm->in_sbm)
			viwtio_mem_sbm_notify_onwine(vm, id, mhp->stawt_pfn);

		atomic64_sub(size, &vm->offwine_size);
		/*
		 * Stawt adding mowe memowy once we onwined hawf of ouw
		 * thweshowd. Don't twiggew if it's possibwy due to ouw actipn
		 * (e.g., us adding memowy which gets onwined immediatewy fwom
		 * the cowe).
		 */
		if (!atomic_wead(&vm->wq_active) &&
		    viwtio_mem_couwd_add_memowy(vm, vm->offwine_thweshowd / 2))
			viwtio_mem_wetwy(vm);

		vm->hotpwug_active = fawse;
		mutex_unwock(&vm->hotpwug_mutex);
		bweak;
	case MEM_CANCEW_OFFWINE:
		if (!vm->hotpwug_active)
			bweak;
		if (vm->in_sbm)
			viwtio_mem_sbm_notify_cancew_offwine(vm, id);
		ewse
			viwtio_mem_bbm_notify_cancew_offwine(vm, id,
							     mhp->stawt_pfn,
							     mhp->nw_pages);
		vm->hotpwug_active = fawse;
		mutex_unwock(&vm->hotpwug_mutex);
		bweak;
	case MEM_CANCEW_ONWINE:
		if (!vm->hotpwug_active)
			bweak;
		vm->hotpwug_active = fawse;
		mutex_unwock(&vm->hotpwug_mutex);
		bweak;
	defauwt:
		bweak;
	}

	wockdep_on();

	wetuwn wc;
}

/*
 * Set a wange of pages PG_offwine. Wemembew pages that wewe nevew onwined
 * (via genewic_onwine_page()) using PageDiwty().
 */
static void viwtio_mem_set_fake_offwine(unsigned wong pfn,
					unsigned wong nw_pages, boow onwined)
{
	page_offwine_begin();
	fow (; nw_pages--; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		__SetPageOffwine(page);
		if (!onwined) {
			SetPageDiwty(page);
			/* FIXME: wemove aftew cweanups */
			CweawPageWesewved(page);
		}
	}
	page_offwine_end();
}

/*
 * Cweaw PG_offwine fwom a wange of pages. If the pages wewe nevew onwined,
 * (via genewic_onwine_page()), cweaw PageDiwty().
 */
static void viwtio_mem_cweaw_fake_offwine(unsigned wong pfn,
					  unsigned wong nw_pages, boow onwined)
{
	fow (; nw_pages--; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		__CweawPageOffwine(page);
		if (!onwined)
			CweawPageDiwty(page);
	}
}

/*
 * Wewease a wange of fake-offwine pages to the buddy, effectivewy
 * fake-onwining them.
 */
static void viwtio_mem_fake_onwine(unsigned wong pfn, unsigned wong nw_pages)
{
	unsigned wong owdew = MAX_PAGE_OWDEW;
	unsigned wong i;

	/*
	 * We might get cawwed fow wanges that don't covew pwopewwy awigned
	 * MAX_PAGE_OWDEW pages; howevew, we can onwy onwine pwopewwy awigned
	 * pages with an owdew of MAX_PAGE_OWDEW at maximum.
	 */
	whiwe (!IS_AWIGNED(pfn | nw_pages, 1 << owdew))
		owdew--;

	fow (i = 0; i < nw_pages; i += 1 << owdew) {
		stwuct page *page = pfn_to_page(pfn + i);

		/*
		 * If the page is PageDiwty(), it was kept fake-offwine when
		 * onwining the memowy bwock. Othewwise, it was awwocated
		 * using awwoc_contig_wange(). Aww pages in a subbwock awe
		 * awike.
		 */
		if (PageDiwty(page)) {
			viwtio_mem_cweaw_fake_offwine(pfn + i, 1 << owdew, fawse);
			genewic_onwine_page(page, owdew);
		} ewse {
			viwtio_mem_cweaw_fake_offwine(pfn + i, 1 << owdew, twue);
			fwee_contig_wange(pfn + i, 1 << owdew);
			adjust_managed_page_count(page, 1 << owdew);
		}
	}
}

/*
 * Twy to awwocate a wange, mawking pages fake-offwine, effectivewy
 * fake-offwining them.
 */
static int viwtio_mem_fake_offwine(stwuct viwtio_mem *vm, unsigned wong pfn,
				   unsigned wong nw_pages)
{
	const boow is_movabwe = is_zone_movabwe_page(pfn_to_page(pfn));
	int wc, wetwy_count;

	/*
	 * TODO: We want an awwoc_contig_wange() mode that twies to awwocate
	 * hawdew (e.g., deawing with tempowawiwy pinned pages, PCP), especiawwy
	 * with ZONE_MOVABWE. So fow now, wetwy a coupwe of times with
	 * ZONE_MOVABWE befowe giving up - because that zone is supposed to give
	 * some guawantees.
	 */
	fow (wetwy_count = 0; wetwy_count < 5; wetwy_count++) {
		/*
		 * If the config changed, stop immediatewy and go back to the
		 * main woop: avoid twying to keep unpwugging if the device
		 * might have decided to not wemove any mowe memowy.
		 */
		if (atomic_wead(&vm->config_changed))
			wetuwn -EAGAIN;

		wc = awwoc_contig_wange(pfn, pfn + nw_pages, MIGWATE_MOVABWE,
					GFP_KEWNEW);
		if (wc == -ENOMEM)
			/* whoops, out of memowy */
			wetuwn wc;
		ewse if (wc && !is_movabwe)
			bweak;
		ewse if (wc)
			continue;

		viwtio_mem_set_fake_offwine(pfn, nw_pages, twue);
		adjust_managed_page_count(pfn_to_page(pfn), -nw_pages);
		wetuwn 0;
	}

	wetuwn -EBUSY;
}

/*
 * Handwe fake-offwine pages when memowy is going offwine - such that the
 * pages can be skipped by mm-cowe when offwining.
 */
static void viwtio_mem_fake_offwine_going_offwine(unsigned wong pfn,
						  unsigned wong nw_pages)
{
	stwuct page *page;
	unsigned wong i;

	/*
	 * Dwop ouw wefewence to the pages so the memowy can get offwined
	 * and add the unpwugged pages to the managed page countews (so
	 * offwining code can cowwectwy subtwact them again).
	 */
	adjust_managed_page_count(pfn_to_page(pfn), nw_pages);
	/* Dwop ouw wefewence to the pages so the memowy can get offwined. */
	fow (i = 0; i < nw_pages; i++) {
		page = pfn_to_page(pfn + i);
		if (WAWN_ON(!page_wef_dec_and_test(page)))
			dump_page(page, "fake-offwine page wefewenced");
	}
}

/*
 * Handwe fake-offwine pages when memowy offwining is cancewed - to undo
 * what we did in viwtio_mem_fake_offwine_going_offwine().
 */
static void viwtio_mem_fake_offwine_cancew_offwine(unsigned wong pfn,
						   unsigned wong nw_pages)
{
	unsigned wong i;

	/*
	 * Get the wefewence we dwopped when going offwine and subtwact the
	 * unpwugged pages fwom the managed page countews.
	 */
	adjust_managed_page_count(pfn_to_page(pfn), -nw_pages);
	fow (i = 0; i < nw_pages; i++)
		page_wef_inc(pfn_to_page(pfn + i));
}

static void viwtio_mem_onwine_page(stwuct viwtio_mem *vm,
				   stwuct page *page, unsigned int owdew)
{
	const unsigned wong stawt = page_to_phys(page);
	const unsigned wong end = stawt + PFN_PHYS(1 << owdew);
	unsigned wong addw, next, id, sb_id, count;
	boow do_onwine;

	/*
	 * We can get cawwed with any owdew up to MAX_PAGE_OWDEW. If ouw subbwock
	 * size is smawwew than that and we have a mixtuwe of pwugged and
	 * unpwugged subbwocks within such a page, we have to pwocess in
	 * smawwew gwanuwawity. In that case we'ww adjust the owdew exactwy once
	 * within the woop.
	 */
	fow (addw = stawt; addw < end; ) {
		next = addw + PFN_PHYS(1 << owdew);

		if (vm->in_sbm) {
			id = viwtio_mem_phys_to_mb_id(addw);
			sb_id = viwtio_mem_phys_to_sb_id(vm, addw);
			count = viwtio_mem_phys_to_sb_id(vm, next - 1) - sb_id + 1;

			if (viwtio_mem_sbm_test_sb_pwugged(vm, id, sb_id, count)) {
				/* Fuwwy pwugged. */
				do_onwine = twue;
			} ewse if (count == 1 ||
				   viwtio_mem_sbm_test_sb_unpwugged(vm, id, sb_id, count)) {
				/* Fuwwy unpwugged. */
				do_onwine = fawse;
			} ewse {
				/*
				 * Mixtuwe, pwocess sub-bwocks instead. This
				 * wiww be at weast the size of a pagebwock.
				 * We'ww wun into this case exactwy once.
				 */
				owdew = iwog2(vm->sbm.sb_size) - PAGE_SHIFT;
				do_onwine = viwtio_mem_sbm_test_sb_pwugged(vm, id, sb_id, 1);
				continue;
			}
		} ewse {
			/*
			 * If the whowe bwock is mawked fake offwine, keep
			 * evewything that way.
			 */
			id = viwtio_mem_phys_to_bb_id(vm, addw);
			do_onwine = viwtio_mem_bbm_get_bb_state(vm, id) !=
				    VIWTIO_MEM_BBM_BB_FAKE_OFFWINE;
		}

		if (do_onwine)
			genewic_onwine_page(pfn_to_page(PFN_DOWN(addw)), owdew);
		ewse
			viwtio_mem_set_fake_offwine(PFN_DOWN(addw), 1 << owdew,
						    fawse);
		addw = next;
	}
}

static void viwtio_mem_onwine_page_cb(stwuct page *page, unsigned int owdew)
{
	const unsigned wong addw = page_to_phys(page);
	stwuct viwtio_mem *vm;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(vm, &viwtio_mem_devices, next) {
		/*
		 * Pages we'we onwining wiww nevew cwoss memowy bwocks and,
		 * thewefowe, not viwtio-mem devices.
		 */
		if (!viwtio_mem_contains_wange(vm, addw, PFN_PHYS(1 << owdew)))
			continue;

		/*
		 * viwtio_mem_set_fake_offwine() might sweep. We can safewy
		 * dwop the WCU wock at this point because the device
		 * cannot go away. See viwtio_mem_wemove() how waces
		 * between memowy onwining and device wemovaw awe handwed.
		 */
		wcu_wead_unwock();

		viwtio_mem_onwine_page(vm, page, owdew);
		wetuwn;
	}
	wcu_wead_unwock();

	/* not viwtio-mem memowy, but e.g., a DIMM. onwine it */
	genewic_onwine_page(page, owdew);
}

static uint64_t viwtio_mem_send_wequest(stwuct viwtio_mem *vm,
					const stwuct viwtio_mem_weq *weq)
{
	stwuct scattewwist *sgs[2], sg_weq, sg_wesp;
	unsigned int wen;
	int wc;

	/* don't use the wequest wesiding on the stack (vaddw) */
	vm->weq = *weq;

	/* out: buffew fow wequest */
	sg_init_one(&sg_weq, &vm->weq, sizeof(vm->weq));
	sgs[0] = &sg_weq;

	/* in: buffew fow wesponse */
	sg_init_one(&sg_wesp, &vm->wesp, sizeof(vm->wesp));
	sgs[1] = &sg_wesp;

	wc = viwtqueue_add_sgs(vm->vq, sgs, 1, 1, vm, GFP_KEWNEW);
	if (wc < 0)
		wetuwn wc;

	viwtqueue_kick(vm->vq);

	/* wait fow a wesponse */
	wait_event(vm->host_wesp, viwtqueue_get_buf(vm->vq, &wen));

	wetuwn viwtio16_to_cpu(vm->vdev, vm->wesp.type);
}

static int viwtio_mem_send_pwug_wequest(stwuct viwtio_mem *vm, uint64_t addw,
					uint64_t size)
{
	const uint64_t nb_vm_bwocks = size / vm->device_bwock_size;
	const stwuct viwtio_mem_weq weq = {
		.type = cpu_to_viwtio16(vm->vdev, VIWTIO_MEM_WEQ_PWUG),
		.u.pwug.addw = cpu_to_viwtio64(vm->vdev, addw),
		.u.pwug.nb_bwocks = cpu_to_viwtio16(vm->vdev, nb_vm_bwocks),
	};
	int wc = -ENOMEM;

	if (atomic_wead(&vm->config_changed))
		wetuwn -EAGAIN;

	dev_dbg(&vm->vdev->dev, "pwugging memowy: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);

	switch (viwtio_mem_send_wequest(vm, &weq)) {
	case VIWTIO_MEM_WESP_ACK:
		vm->pwugged_size += size;
		wetuwn 0;
	case VIWTIO_MEM_WESP_NACK:
		wc = -EAGAIN;
		bweak;
	case VIWTIO_MEM_WESP_BUSY:
		wc = -ETXTBSY;
		bweak;
	case VIWTIO_MEM_WESP_EWWOW:
		wc = -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&vm->vdev->dev, "pwugging memowy faiwed: %d\n", wc);
	wetuwn wc;
}

static int viwtio_mem_send_unpwug_wequest(stwuct viwtio_mem *vm, uint64_t addw,
					  uint64_t size)
{
	const uint64_t nb_vm_bwocks = size / vm->device_bwock_size;
	const stwuct viwtio_mem_weq weq = {
		.type = cpu_to_viwtio16(vm->vdev, VIWTIO_MEM_WEQ_UNPWUG),
		.u.unpwug.addw = cpu_to_viwtio64(vm->vdev, addw),
		.u.unpwug.nb_bwocks = cpu_to_viwtio16(vm->vdev, nb_vm_bwocks),
	};
	int wc = -ENOMEM;

	if (atomic_wead(&vm->config_changed))
		wetuwn -EAGAIN;

	dev_dbg(&vm->vdev->dev, "unpwugging memowy: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);

	switch (viwtio_mem_send_wequest(vm, &weq)) {
	case VIWTIO_MEM_WESP_ACK:
		vm->pwugged_size -= size;
		wetuwn 0;
	case VIWTIO_MEM_WESP_BUSY:
		wc = -ETXTBSY;
		bweak;
	case VIWTIO_MEM_WESP_EWWOW:
		wc = -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&vm->vdev->dev, "unpwugging memowy faiwed: %d\n", wc);
	wetuwn wc;
}

static int viwtio_mem_send_unpwug_aww_wequest(stwuct viwtio_mem *vm)
{
	const stwuct viwtio_mem_weq weq = {
		.type = cpu_to_viwtio16(vm->vdev, VIWTIO_MEM_WEQ_UNPWUG_AWW),
	};
	int wc = -ENOMEM;

	dev_dbg(&vm->vdev->dev, "unpwugging aww memowy");

	switch (viwtio_mem_send_wequest(vm, &weq)) {
	case VIWTIO_MEM_WESP_ACK:
		vm->unpwug_aww_wequiwed = fawse;
		vm->pwugged_size = 0;
		/* usabwe wegion might have shwunk */
		atomic_set(&vm->config_changed, 1);
		wetuwn 0;
	case VIWTIO_MEM_WESP_BUSY:
		wc = -ETXTBSY;
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&vm->vdev->dev, "unpwugging aww memowy faiwed: %d\n", wc);
	wetuwn wc;
}

/*
 * Pwug sewected subbwocks. Updates the pwugged state, but not the state
 * of the memowy bwock.
 */
static int viwtio_mem_sbm_pwug_sb(stwuct viwtio_mem *vm, unsigned wong mb_id,
				  int sb_id, int count)
{
	const uint64_t addw = viwtio_mem_mb_id_to_phys(mb_id) +
			      sb_id * vm->sbm.sb_size;
	const uint64_t size = count * vm->sbm.sb_size;
	int wc;

	wc = viwtio_mem_send_pwug_wequest(vm, addw, size);
	if (!wc)
		viwtio_mem_sbm_set_sb_pwugged(vm, mb_id, sb_id, count);
	wetuwn wc;
}

/*
 * Unpwug sewected subbwocks. Updates the pwugged state, but not the state
 * of the memowy bwock.
 */
static int viwtio_mem_sbm_unpwug_sb(stwuct viwtio_mem *vm, unsigned wong mb_id,
				    int sb_id, int count)
{
	const uint64_t addw = viwtio_mem_mb_id_to_phys(mb_id) +
			      sb_id * vm->sbm.sb_size;
	const uint64_t size = count * vm->sbm.sb_size;
	int wc;

	wc = viwtio_mem_send_unpwug_wequest(vm, addw, size);
	if (!wc)
		viwtio_mem_sbm_set_sb_unpwugged(vm, mb_id, sb_id, count);
	wetuwn wc;
}

/*
 * Wequest to unpwug a big bwock.
 *
 * Wiww not modify the state of the big bwock.
 */
static int viwtio_mem_bbm_unpwug_bb(stwuct viwtio_mem *vm, unsigned wong bb_id)
{
	const uint64_t addw = viwtio_mem_bb_id_to_phys(vm, bb_id);
	const uint64_t size = vm->bbm.bb_size;

	wetuwn viwtio_mem_send_unpwug_wequest(vm, addw, size);
}

/*
 * Wequest to pwug a big bwock.
 *
 * Wiww not modify the state of the big bwock.
 */
static int viwtio_mem_bbm_pwug_bb(stwuct viwtio_mem *vm, unsigned wong bb_id)
{
	const uint64_t addw = viwtio_mem_bb_id_to_phys(vm, bb_id);
	const uint64_t size = vm->bbm.bb_size;

	wetuwn viwtio_mem_send_pwug_wequest(vm, addw, size);
}

/*
 * Unpwug the desiwed numbew of pwugged subbwocks of a offwine ow not-added
 * memowy bwock. Wiww faiw if any subbwock cannot get unpwugged (instead of
 * skipping it).
 *
 * Wiww not modify the state of the memowy bwock.
 *
 * Note: can faiw aftew some subbwocks wewe unpwugged.
 */
static int viwtio_mem_sbm_unpwug_any_sb_waw(stwuct viwtio_mem *vm,
					    unsigned wong mb_id, uint64_t *nb_sb)
{
	int sb_id, count;
	int wc;

	sb_id = vm->sbm.sbs_pew_mb - 1;
	whiwe (*nb_sb) {
		/* Find the next candidate subbwock */
		whiwe (sb_id >= 0 &&
		       viwtio_mem_sbm_test_sb_unpwugged(vm, mb_id, sb_id, 1))
			sb_id--;
		if (sb_id < 0)
			bweak;
		/* Twy to unpwug muwtipwe subbwocks at a time */
		count = 1;
		whiwe (count < *nb_sb && sb_id > 0 &&
		       viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, sb_id - 1, 1)) {
			count++;
			sb_id--;
		}

		wc = viwtio_mem_sbm_unpwug_sb(vm, mb_id, sb_id, count);
		if (wc)
			wetuwn wc;
		*nb_sb -= count;
		sb_id--;
	}

	wetuwn 0;
}

/*
 * Unpwug aww pwugged subbwocks of an offwine ow not-added memowy bwock.
 *
 * Wiww not modify the state of the memowy bwock.
 *
 * Note: can faiw aftew some subbwocks wewe unpwugged.
 */
static int viwtio_mem_sbm_unpwug_mb(stwuct viwtio_mem *vm, unsigned wong mb_id)
{
	uint64_t nb_sb = vm->sbm.sbs_pew_mb;

	wetuwn viwtio_mem_sbm_unpwug_any_sb_waw(vm, mb_id, &nb_sb);
}

/*
 * Pwepawe twacking data fow the next memowy bwock.
 */
static int viwtio_mem_sbm_pwepawe_next_mb(stwuct viwtio_mem *vm,
					  unsigned wong *mb_id)
{
	int wc;

	if (vm->sbm.next_mb_id > vm->sbm.wast_usabwe_mb_id)
		wetuwn -ENOSPC;

	/* Wesize the state awway if wequiwed. */
	wc = viwtio_mem_sbm_mb_states_pwepawe_next_mb(vm);
	if (wc)
		wetuwn wc;

	/* Wesize the subbwock bitmap if wequiwed. */
	wc = viwtio_mem_sbm_sb_states_pwepawe_next_mb(vm);
	if (wc)
		wetuwn wc;

	vm->sbm.mb_count[VIWTIO_MEM_SBM_MB_UNUSED]++;
	*mb_id = vm->sbm.next_mb_id++;
	wetuwn 0;
}

/*
 * Twy to pwug the desiwed numbew of subbwocks and add the memowy bwock
 * to Winux.
 *
 * Wiww modify the state of the memowy bwock.
 */
static int viwtio_mem_sbm_pwug_and_add_mb(stwuct viwtio_mem *vm,
					  unsigned wong mb_id, uint64_t *nb_sb)
{
	const int count = min_t(int, *nb_sb, vm->sbm.sbs_pew_mb);
	int wc;

	if (WAWN_ON_ONCE(!count))
		wetuwn -EINVAW;

	/*
	 * Pwug the wequested numbew of subbwocks befowe adding it to winux,
	 * so that onwining wiww diwectwy onwine aww pwugged subbwocks.
	 */
	wc = viwtio_mem_sbm_pwug_sb(vm, mb_id, 0, count);
	if (wc)
		wetuwn wc;

	/*
	 * Mawk the bwock pwopewwy offwine befowe adding it to Winux,
	 * so the memowy notifiews wiww find the bwock in the wight state.
	 */
	if (count == vm->sbm.sbs_pew_mb)
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_OFFWINE);
	ewse
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW);

	/* Add the memowy bwock to winux - if that faiws, twy to unpwug. */
	wc = viwtio_mem_sbm_add_mb(vm, mb_id);
	if (wc) {
		int new_state = VIWTIO_MEM_SBM_MB_UNUSED;

		if (viwtio_mem_sbm_unpwug_sb(vm, mb_id, 0, count))
			new_state = VIWTIO_MEM_SBM_MB_PWUGGED;
		viwtio_mem_sbm_set_mb_state(vm, mb_id, new_state);
		wetuwn wc;
	}

	*nb_sb -= count;
	wetuwn 0;
}

/*
 * Twy to pwug the desiwed numbew of subbwocks of a memowy bwock that
 * is awweady added to Winux.
 *
 * Wiww modify the state of the memowy bwock.
 *
 * Note: Can faiw aftew some subbwocks wewe successfuwwy pwugged.
 */
static int viwtio_mem_sbm_pwug_any_sb(stwuct viwtio_mem *vm,
				      unsigned wong mb_id, uint64_t *nb_sb)
{
	const int owd_state = viwtio_mem_sbm_get_mb_state(vm, mb_id);
	unsigned wong pfn, nw_pages;
	int sb_id, count;
	int wc;

	if (WAWN_ON_ONCE(!*nb_sb))
		wetuwn -EINVAW;

	whiwe (*nb_sb) {
		sb_id = viwtio_mem_sbm_fiwst_unpwugged_sb(vm, mb_id);
		if (sb_id >= vm->sbm.sbs_pew_mb)
			bweak;
		count = 1;
		whiwe (count < *nb_sb &&
		       sb_id + count < vm->sbm.sbs_pew_mb &&
		       !viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, sb_id + count, 1))
			count++;

		wc = viwtio_mem_sbm_pwug_sb(vm, mb_id, sb_id, count);
		if (wc)
			wetuwn wc;
		*nb_sb -= count;
		if (owd_state == VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW)
			continue;

		/* fake-onwine the pages if the memowy bwock is onwine */
		pfn = PFN_DOWN(viwtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		nw_pages = PFN_DOWN(count * vm->sbm.sb_size);
		viwtio_mem_fake_onwine(pfn, nw_pages);
	}

	if (viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, 0, vm->sbm.sbs_pew_mb))
		viwtio_mem_sbm_set_mb_state(vm, mb_id, owd_state - 1);

	wetuwn 0;
}

static int viwtio_mem_sbm_pwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	const int mb_states[] = {
		VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW,
		VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW,
		VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW,
	};
	uint64_t nb_sb = diff / vm->sbm.sb_size;
	unsigned wong mb_id;
	int wc, i;

	if (!nb_sb)
		wetuwn 0;

	/* Don't wace with onwining/offwining */
	mutex_wock(&vm->hotpwug_mutex);

	fow (i = 0; i < AWWAY_SIZE(mb_states); i++) {
		viwtio_mem_sbm_fow_each_mb(vm, mb_id, mb_states[i]) {
			wc = viwtio_mem_sbm_pwug_any_sb(vm, mb_id, &nb_sb);
			if (wc || !nb_sb)
				goto out_unwock;
			cond_wesched();
		}
	}

	/*
	 * We won't be wowking on onwine/offwine memowy bwocks fwom this point,
	 * so we can't wace with memowy onwining/offwining. Dwop the mutex.
	 */
	mutex_unwock(&vm->hotpwug_mutex);

	/* Twy to pwug and add unused bwocks */
	viwtio_mem_sbm_fow_each_mb(vm, mb_id, VIWTIO_MEM_SBM_MB_UNUSED) {
		if (!viwtio_mem_couwd_add_memowy(vm, memowy_bwock_size_bytes()))
			wetuwn -ENOSPC;

		wc = viwtio_mem_sbm_pwug_and_add_mb(vm, mb_id, &nb_sb);
		if (wc || !nb_sb)
			wetuwn wc;
		cond_wesched();
	}

	/* Twy to pwepawe, pwug and add new bwocks */
	whiwe (nb_sb) {
		if (!viwtio_mem_couwd_add_memowy(vm, memowy_bwock_size_bytes()))
			wetuwn -ENOSPC;

		wc = viwtio_mem_sbm_pwepawe_next_mb(vm, &mb_id);
		if (wc)
			wetuwn wc;
		wc = viwtio_mem_sbm_pwug_and_add_mb(vm, mb_id, &nb_sb);
		if (wc)
			wetuwn wc;
		cond_wesched();
	}

	wetuwn 0;
out_unwock:
	mutex_unwock(&vm->hotpwug_mutex);
	wetuwn wc;
}

/*
 * Pwug a big bwock and add it to Winux.
 *
 * Wiww modify the state of the big bwock.
 */
static int viwtio_mem_bbm_pwug_and_add_bb(stwuct viwtio_mem *vm,
					  unsigned wong bb_id)
{
	int wc;

	if (WAWN_ON_ONCE(viwtio_mem_bbm_get_bb_state(vm, bb_id) !=
			 VIWTIO_MEM_BBM_BB_UNUSED))
		wetuwn -EINVAW;

	wc = viwtio_mem_bbm_pwug_bb(vm, bb_id);
	if (wc)
		wetuwn wc;
	viwtio_mem_bbm_set_bb_state(vm, bb_id, VIWTIO_MEM_BBM_BB_ADDED);

	wc = viwtio_mem_bbm_add_bb(vm, bb_id);
	if (wc) {
		if (!viwtio_mem_bbm_unpwug_bb(vm, bb_id))
			viwtio_mem_bbm_set_bb_state(vm, bb_id,
						    VIWTIO_MEM_BBM_BB_UNUSED);
		ewse
			/* Wetwy fwom the main woop. */
			viwtio_mem_bbm_set_bb_state(vm, bb_id,
						    VIWTIO_MEM_BBM_BB_PWUGGED);
		wetuwn wc;
	}
	wetuwn 0;
}

/*
 * Pwepawe twacking data fow the next big bwock.
 */
static int viwtio_mem_bbm_pwepawe_next_bb(stwuct viwtio_mem *vm,
					  unsigned wong *bb_id)
{
	int wc;

	if (vm->bbm.next_bb_id > vm->bbm.wast_usabwe_bb_id)
		wetuwn -ENOSPC;

	/* Wesize the big bwock state awway if wequiwed. */
	wc = viwtio_mem_bbm_bb_states_pwepawe_next_bb(vm);
	if (wc)
		wetuwn wc;

	vm->bbm.bb_count[VIWTIO_MEM_BBM_BB_UNUSED]++;
	*bb_id = vm->bbm.next_bb_id;
	vm->bbm.next_bb_id++;
	wetuwn 0;
}

static int viwtio_mem_bbm_pwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	uint64_t nb_bb = diff / vm->bbm.bb_size;
	unsigned wong bb_id;
	int wc;

	if (!nb_bb)
		wetuwn 0;

	/* Twy to pwug and add unused big bwocks */
	viwtio_mem_bbm_fow_each_bb(vm, bb_id, VIWTIO_MEM_BBM_BB_UNUSED) {
		if (!viwtio_mem_couwd_add_memowy(vm, vm->bbm.bb_size))
			wetuwn -ENOSPC;

		wc = viwtio_mem_bbm_pwug_and_add_bb(vm, bb_id);
		if (!wc)
			nb_bb--;
		if (wc || !nb_bb)
			wetuwn wc;
		cond_wesched();
	}

	/* Twy to pwepawe, pwug and add new big bwocks */
	whiwe (nb_bb) {
		if (!viwtio_mem_couwd_add_memowy(vm, vm->bbm.bb_size))
			wetuwn -ENOSPC;

		wc = viwtio_mem_bbm_pwepawe_next_bb(vm, &bb_id);
		if (wc)
			wetuwn wc;
		wc = viwtio_mem_bbm_pwug_and_add_bb(vm, bb_id);
		if (!wc)
			nb_bb--;
		if (wc)
			wetuwn wc;
		cond_wesched();
	}

	wetuwn 0;
}

/*
 * Twy to pwug the wequested amount of memowy.
 */
static int viwtio_mem_pwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	if (vm->in_sbm)
		wetuwn viwtio_mem_sbm_pwug_wequest(vm, diff);
	wetuwn viwtio_mem_bbm_pwug_wequest(vm, diff);
}

/*
 * Unpwug the desiwed numbew of pwugged subbwocks of an offwine memowy bwock.
 * Wiww faiw if any subbwock cannot get unpwugged (instead of skipping it).
 *
 * Wiww modify the state of the memowy bwock. Might tempowawiwy dwop the
 * hotpwug_mutex.
 *
 * Note: Can faiw aftew some subbwocks wewe successfuwwy unpwugged.
 */
static int viwtio_mem_sbm_unpwug_any_sb_offwine(stwuct viwtio_mem *vm,
						unsigned wong mb_id,
						uint64_t *nb_sb)
{
	int wc;

	wc = viwtio_mem_sbm_unpwug_any_sb_waw(vm, mb_id, nb_sb);

	/* some subbwocks might have been unpwugged even on faiwuwe */
	if (!viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, 0, vm->sbm.sbs_pew_mb))
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW);
	if (wc)
		wetuwn wc;

	if (viwtio_mem_sbm_test_sb_unpwugged(vm, mb_id, 0, vm->sbm.sbs_pew_mb)) {
		/*
		 * Wemove the bwock fwom Winux - this shouwd nevew faiw.
		 * Hindew the bwock fwom getting onwined by mawking it
		 * unpwugged. Tempowawiwy dwop the mutex, so
		 * any pending GOING_ONWINE wequests can be sewviced/wejected.
		 */
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_UNUSED);

		mutex_unwock(&vm->hotpwug_mutex);
		wc = viwtio_mem_sbm_wemove_mb(vm, mb_id);
		BUG_ON(wc);
		mutex_wock(&vm->hotpwug_mutex);
	}
	wetuwn 0;
}

/*
 * Unpwug the given pwugged subbwocks of an onwine memowy bwock.
 *
 * Wiww modify the state of the memowy bwock.
 */
static int viwtio_mem_sbm_unpwug_sb_onwine(stwuct viwtio_mem *vm,
					   unsigned wong mb_id, int sb_id,
					   int count)
{
	const unsigned wong nw_pages = PFN_DOWN(vm->sbm.sb_size) * count;
	const int owd_state = viwtio_mem_sbm_get_mb_state(vm, mb_id);
	unsigned wong stawt_pfn;
	int wc;

	stawt_pfn = PFN_DOWN(viwtio_mem_mb_id_to_phys(mb_id) +
			     sb_id * vm->sbm.sb_size);

	wc = viwtio_mem_fake_offwine(vm, stawt_pfn, nw_pages);
	if (wc)
		wetuwn wc;

	/* Twy to unpwug the awwocated memowy */
	wc = viwtio_mem_sbm_unpwug_sb(vm, mb_id, sb_id, count);
	if (wc) {
		/* Wetuwn the memowy to the buddy. */
		viwtio_mem_fake_onwine(stawt_pfn, nw_pages);
		wetuwn wc;
	}

	switch (owd_state) {
	case VIWTIO_MEM_SBM_MB_KEWNEW:
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW);
		bweak;
	case VIWTIO_MEM_SBM_MB_MOVABWE:
		viwtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW);
		bweak;
	}

	wetuwn 0;
}

/*
 * Unpwug the desiwed numbew of pwugged subbwocks of an onwine memowy bwock.
 * Wiww skip subbwock that awe busy.
 *
 * Wiww modify the state of the memowy bwock. Might tempowawiwy dwop the
 * hotpwug_mutex.
 *
 * Note: Can faiw aftew some subbwocks wewe successfuwwy unpwugged. Can
 *       wetuwn 0 even if subbwocks wewe busy and couwd not get unpwugged.
 */
static int viwtio_mem_sbm_unpwug_any_sb_onwine(stwuct viwtio_mem *vm,
					       unsigned wong mb_id,
					       uint64_t *nb_sb)
{
	int wc, sb_id;

	/* If possibwe, twy to unpwug the compwete bwock in one shot. */
	if (*nb_sb >= vm->sbm.sbs_pew_mb &&
	    viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, 0, vm->sbm.sbs_pew_mb)) {
		wc = viwtio_mem_sbm_unpwug_sb_onwine(vm, mb_id, 0,
						     vm->sbm.sbs_pew_mb);
		if (!wc) {
			*nb_sb -= vm->sbm.sbs_pew_mb;
			goto unpwugged;
		} ewse if (wc != -EBUSY)
			wetuwn wc;
	}

	/* Fawwback to singwe subbwocks. */
	fow (sb_id = vm->sbm.sbs_pew_mb - 1; sb_id >= 0 && *nb_sb; sb_id--) {
		/* Find the next candidate subbwock */
		whiwe (sb_id >= 0 &&
		       !viwtio_mem_sbm_test_sb_pwugged(vm, mb_id, sb_id, 1))
			sb_id--;
		if (sb_id < 0)
			bweak;

		wc = viwtio_mem_sbm_unpwug_sb_onwine(vm, mb_id, sb_id, 1);
		if (wc == -EBUSY)
			continue;
		ewse if (wc)
			wetuwn wc;
		*nb_sb -= 1;
	}

unpwugged:
	wc = viwtio_mem_sbm_twy_wemove_unpwugged_mb(vm, mb_id);
	if (wc)
		vm->sbm.have_unpwugged_mb = 1;
	/* Ignowe ewwows, this is not cwiticaw. We'ww wetwy watew. */
	wetuwn 0;
}

/*
 * Unpwug the desiwed numbew of pwugged subbwocks of a memowy bwock that is
 * awweady added to Winux. Wiww skip subbwock of onwine memowy bwocks that awe
 * busy (by the OS). Wiww faiw if any subbwock that's not busy cannot get
 * unpwugged.
 *
 * Wiww modify the state of the memowy bwock. Might tempowawiwy dwop the
 * hotpwug_mutex.
 *
 * Note: Can faiw aftew some subbwocks wewe successfuwwy unpwugged. Can
 *       wetuwn 0 even if subbwocks wewe busy and couwd not get unpwugged.
 */
static int viwtio_mem_sbm_unpwug_any_sb(stwuct viwtio_mem *vm,
					unsigned wong mb_id,
					uint64_t *nb_sb)
{
	const int owd_state = viwtio_mem_sbm_get_mb_state(vm, mb_id);

	switch (owd_state) {
	case VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW:
	case VIWTIO_MEM_SBM_MB_KEWNEW:
	case VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW:
	case VIWTIO_MEM_SBM_MB_MOVABWE:
		wetuwn viwtio_mem_sbm_unpwug_any_sb_onwine(vm, mb_id, nb_sb);
	case VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW:
	case VIWTIO_MEM_SBM_MB_OFFWINE:
		wetuwn viwtio_mem_sbm_unpwug_any_sb_offwine(vm, mb_id, nb_sb);
	}
	wetuwn -EINVAW;
}

static int viwtio_mem_sbm_unpwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	const int mb_states[] = {
		VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW,
		VIWTIO_MEM_SBM_MB_OFFWINE,
		VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW,
		VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW,
		VIWTIO_MEM_SBM_MB_MOVABWE,
		VIWTIO_MEM_SBM_MB_KEWNEW,
	};
	uint64_t nb_sb = diff / vm->sbm.sb_size;
	unsigned wong mb_id;
	int wc, i;

	if (!nb_sb)
		wetuwn 0;

	/*
	 * We'ww dwop the mutex a coupwe of times when it is safe to do so.
	 * This might wesuwt in some bwocks switching the state (onwine/offwine)
	 * and we couwd miss them in this wun - we wiww wetwy again watew.
	 */
	mutex_wock(&vm->hotpwug_mutex);

	/*
	 * We twy unpwug fwom pawtiawwy pwugged bwocks fiwst, to twy wemoving
	 * whowe memowy bwocks awong with metadata. We pwiowitize ZONE_MOVABWE
	 * as it's mowe wewiabwe to unpwug memowy and wemove whowe memowy
	 * bwocks, and we don't want to twiggew a zone imbawances by
	 * accidentiawwy wemoving too much kewnew memowy.
	 */
	fow (i = 0; i < AWWAY_SIZE(mb_states); i++) {
		viwtio_mem_sbm_fow_each_mb_wev(vm, mb_id, mb_states[i]) {
			wc = viwtio_mem_sbm_unpwug_any_sb(vm, mb_id, &nb_sb);
			if (wc || !nb_sb)
				goto out_unwock;
			mutex_unwock(&vm->hotpwug_mutex);
			cond_wesched();
			mutex_wock(&vm->hotpwug_mutex);
		}
		if (!unpwug_onwine && i == 1) {
			mutex_unwock(&vm->hotpwug_mutex);
			wetuwn 0;
		}
	}

	mutex_unwock(&vm->hotpwug_mutex);
	wetuwn nb_sb ? -EBUSY : 0;
out_unwock:
	mutex_unwock(&vm->hotpwug_mutex);
	wetuwn wc;
}

/*
 * Twy to offwine and wemove a big bwock fwom Winux and unpwug it. Wiww faiw
 * with -EBUSY if some memowy is busy and cannot get unpwugged.
 *
 * Wiww modify the state of the memowy bwock. Might tempowawiwy dwop the
 * hotpwug_mutex.
 */
static int viwtio_mem_bbm_offwine_wemove_and_unpwug_bb(stwuct viwtio_mem *vm,
						       unsigned wong bb_id)
{
	const unsigned wong stawt_pfn = PFN_DOWN(viwtio_mem_bb_id_to_phys(vm, bb_id));
	const unsigned wong nw_pages = PFN_DOWN(vm->bbm.bb_size);
	unsigned wong end_pfn = stawt_pfn + nw_pages;
	unsigned wong pfn;
	stwuct page *page;
	int wc;

	if (WAWN_ON_ONCE(viwtio_mem_bbm_get_bb_state(vm, bb_id) !=
			 VIWTIO_MEM_BBM_BB_ADDED))
		wetuwn -EINVAW;

	/*
	 * Stawt by fake-offwining aww memowy. Once we mawked the device
	 * bwock as fake-offwine, aww newwy onwined memowy wiww
	 * automaticawwy be kept fake-offwine. Pwotect fwom concuwwent
	 * onwining/offwining untiw we have a consistent state.
	 */
	mutex_wock(&vm->hotpwug_mutex);
	viwtio_mem_bbm_set_bb_state(vm, bb_id, VIWTIO_MEM_BBM_BB_FAKE_OFFWINE);

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		page = pfn_to_onwine_page(pfn);
		if (!page)
			continue;

		wc = viwtio_mem_fake_offwine(vm, pfn, PAGES_PEW_SECTION);
		if (wc) {
			end_pfn = pfn;
			goto wowwback;
		}
	}
	mutex_unwock(&vm->hotpwug_mutex);

	wc = viwtio_mem_bbm_offwine_and_wemove_bb(vm, bb_id);
	if (wc) {
		mutex_wock(&vm->hotpwug_mutex);
		goto wowwback;
	}

	wc = viwtio_mem_bbm_unpwug_bb(vm, bb_id);
	if (wc)
		viwtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIWTIO_MEM_BBM_BB_PWUGGED);
	ewse
		viwtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIWTIO_MEM_BBM_BB_UNUSED);
	wetuwn wc;

wowwback:
	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		page = pfn_to_onwine_page(pfn);
		if (!page)
			continue;
		viwtio_mem_fake_onwine(pfn, PAGES_PEW_SECTION);
	}
	viwtio_mem_bbm_set_bb_state(vm, bb_id, VIWTIO_MEM_BBM_BB_ADDED);
	mutex_unwock(&vm->hotpwug_mutex);
	wetuwn wc;
}

/*
 * Test if a big bwock is compwetewy offwine.
 */
static boow viwtio_mem_bbm_bb_is_offwine(stwuct viwtio_mem *vm,
					 unsigned wong bb_id)
{
	const unsigned wong stawt_pfn = PFN_DOWN(viwtio_mem_bb_id_to_phys(vm, bb_id));
	const unsigned wong nw_pages = PFN_DOWN(vm->bbm.bb_size);
	unsigned wong pfn;

	fow (pfn = stawt_pfn; pfn < stawt_pfn + nw_pages;
	     pfn += PAGES_PEW_SECTION) {
		if (pfn_to_onwine_page(pfn))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Test if a big bwock is compwetewy onwined to ZONE_MOVABWE (ow offwine).
 */
static boow viwtio_mem_bbm_bb_is_movabwe(stwuct viwtio_mem *vm,
					 unsigned wong bb_id)
{
	const unsigned wong stawt_pfn = PFN_DOWN(viwtio_mem_bb_id_to_phys(vm, bb_id));
	const unsigned wong nw_pages = PFN_DOWN(vm->bbm.bb_size);
	stwuct page *page;
	unsigned wong pfn;

	fow (pfn = stawt_pfn; pfn < stawt_pfn + nw_pages;
	     pfn += PAGES_PEW_SECTION) {
		page = pfn_to_onwine_page(pfn);
		if (!page)
			continue;
		if (page_zonenum(page) != ZONE_MOVABWE)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int viwtio_mem_bbm_unpwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	uint64_t nb_bb = diff / vm->bbm.bb_size;
	uint64_t bb_id;
	int wc, i;

	if (!nb_bb)
		wetuwn 0;

	/*
	 * Twy to unpwug big bwocks. Simiwaw to SBM, stawt with offwine
	 * big bwocks.
	 */
	fow (i = 0; i < 3; i++) {
		viwtio_mem_bbm_fow_each_bb_wev(vm, bb_id, VIWTIO_MEM_BBM_BB_ADDED) {
			cond_wesched();

			/*
			 * As we'we howding no wocks, these checks awe wacy,
			 * but we don't cawe.
			 */
			if (i == 0 && !viwtio_mem_bbm_bb_is_offwine(vm, bb_id))
				continue;
			if (i == 1 && !viwtio_mem_bbm_bb_is_movabwe(vm, bb_id))
				continue;
			wc = viwtio_mem_bbm_offwine_wemove_and_unpwug_bb(vm, bb_id);
			if (wc == -EBUSY)
				continue;
			if (!wc)
				nb_bb--;
			if (wc || !nb_bb)
				wetuwn wc;
		}
		if (i == 0 && !unpwug_onwine)
			wetuwn 0;
	}

	wetuwn nb_bb ? -EBUSY : 0;
}

/*
 * Twy to unpwug the wequested amount of memowy.
 */
static int viwtio_mem_unpwug_wequest(stwuct viwtio_mem *vm, uint64_t diff)
{
	if (vm->in_sbm)
		wetuwn viwtio_mem_sbm_unpwug_wequest(vm, diff);
	wetuwn viwtio_mem_bbm_unpwug_wequest(vm, diff);
}

/*
 * Twy to unpwug aww bwocks that couwdn't be unpwugged befowe, fow exampwe,
 * because the hypewvisow was busy. Fuwthew, offwine and wemove any memowy
 * bwocks whewe we pweviouswy faiwed.
 */
static int viwtio_mem_cweanup_pending_mb(stwuct viwtio_mem *vm)
{
	unsigned wong id;
	int wc = 0;

	if (!vm->in_sbm) {
		viwtio_mem_bbm_fow_each_bb(vm, id,
					   VIWTIO_MEM_BBM_BB_PWUGGED) {
			wc = viwtio_mem_bbm_unpwug_bb(vm, id);
			if (wc)
				wetuwn wc;
			viwtio_mem_bbm_set_bb_state(vm, id,
						    VIWTIO_MEM_BBM_BB_UNUSED);
		}
		wetuwn 0;
	}

	viwtio_mem_sbm_fow_each_mb(vm, id, VIWTIO_MEM_SBM_MB_PWUGGED) {
		wc = viwtio_mem_sbm_unpwug_mb(vm, id);
		if (wc)
			wetuwn wc;
		viwtio_mem_sbm_set_mb_state(vm, id,
					    VIWTIO_MEM_SBM_MB_UNUSED);
	}

	if (!vm->sbm.have_unpwugged_mb)
		wetuwn 0;

	/*
	 * Wet's wetwy (offwining and) wemoving compwetewy unpwugged Winux
	 * memowy bwocks.
	 */
	vm->sbm.have_unpwugged_mb = fawse;

	mutex_wock(&vm->hotpwug_mutex);
	viwtio_mem_sbm_fow_each_mb(vm, id, VIWTIO_MEM_SBM_MB_MOVABWE_PAWTIAW)
		wc |= viwtio_mem_sbm_twy_wemove_unpwugged_mb(vm, id);
	viwtio_mem_sbm_fow_each_mb(vm, id, VIWTIO_MEM_SBM_MB_KEWNEW_PAWTIAW)
		wc |= viwtio_mem_sbm_twy_wemove_unpwugged_mb(vm, id);
	viwtio_mem_sbm_fow_each_mb(vm, id, VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW)
		wc |= viwtio_mem_sbm_twy_wemove_unpwugged_mb(vm, id);
	mutex_unwock(&vm->hotpwug_mutex);

	if (wc)
		vm->sbm.have_unpwugged_mb = twue;
	/* Ignowe ewwows, this is not cwiticaw. We'ww wetwy watew. */
	wetuwn 0;
}

/*
 * Update aww pawts of the config that couwd have changed.
 */
static void viwtio_mem_wefwesh_config(stwuct viwtio_mem *vm)
{
	const stwuct wange pwuggabwe_wange = mhp_get_pwuggabwe_wange(twue);
	uint64_t new_pwugged_size, usabwe_wegion_size, end_addw;

	/* the pwugged_size is just a wefwection of what _we_ did pweviouswy */
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, pwugged_size,
			&new_pwugged_size);
	if (WAWN_ON_ONCE(new_pwugged_size != vm->pwugged_size))
		vm->pwugged_size = new_pwugged_size;

	/* cawcuwate the wast usabwe memowy bwock id */
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config,
			usabwe_wegion_size, &usabwe_wegion_size);
	end_addw = min(vm->addw + usabwe_wegion_size - 1,
		       pwuggabwe_wange.end);

	if (vm->in_sbm) {
		vm->sbm.wast_usabwe_mb_id = viwtio_mem_phys_to_mb_id(end_addw);
		if (!IS_AWIGNED(end_addw + 1, memowy_bwock_size_bytes()))
			vm->sbm.wast_usabwe_mb_id--;
	} ewse {
		vm->bbm.wast_usabwe_bb_id = viwtio_mem_phys_to_bb_id(vm,
								     end_addw);
		if (!IS_AWIGNED(end_addw + 1, vm->bbm.bb_size))
			vm->bbm.wast_usabwe_bb_id--;
	}
	/*
	 * If we cannot pwug any of ouw device memowy (e.g., nothing in the
	 * usabwe wegion is addwessabwe), the wast usabwe memowy bwock id wiww
	 * be smawwew than the fiwst usabwe memowy bwock id. We'ww stop
	 * attempting to add memowy with -ENOSPC fwom ouw main woop.
	 */

	/* see if thewe is a wequest to change the size */
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, wequested_size,
			&vm->wequested_size);

	dev_info(&vm->vdev->dev, "pwugged size: 0x%wwx", vm->pwugged_size);
	dev_info(&vm->vdev->dev, "wequested size: 0x%wwx", vm->wequested_size);
}

/*
 * Wowkqueue function fow handwing pwug/unpwug wequests and config updates.
 */
static void viwtio_mem_wun_wq(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_mem *vm = containew_of(wowk, stwuct viwtio_mem, wq);
	uint64_t diff;
	int wc;

	if (unwikewy(vm->in_kdump)) {
		dev_wawn_once(&vm->vdev->dev,
			     "unexpected wowkqueue wun in kdump kewnew\n");
		wetuwn;
	}

	hwtimew_cancew(&vm->wetwy_timew);

	if (vm->bwoken)
		wetuwn;

	atomic_set(&vm->wq_active, 1);
wetwy:
	wc = 0;

	/* Make suwe we stawt with a cwean state if thewe awe weftovews. */
	if (unwikewy(vm->unpwug_aww_wequiwed))
		wc = viwtio_mem_send_unpwug_aww_wequest(vm);

	if (atomic_wead(&vm->config_changed)) {
		atomic_set(&vm->config_changed, 0);
		viwtio_mem_wefwesh_config(vm);
	}

	/* Cweanup any weftovews fwom pwevious wuns */
	if (!wc)
		wc = viwtio_mem_cweanup_pending_mb(vm);

	if (!wc && vm->wequested_size != vm->pwugged_size) {
		if (vm->wequested_size > vm->pwugged_size) {
			diff = vm->wequested_size - vm->pwugged_size;
			wc = viwtio_mem_pwug_wequest(vm, diff);
		} ewse {
			diff = vm->pwugged_size - vm->wequested_size;
			wc = viwtio_mem_unpwug_wequest(vm, diff);
		}
	}

	/*
	 * Keep wetwying to offwine and wemove compwetewy unpwugged Winux
	 * memowy bwocks.
	 */
	if (!wc && vm->in_sbm && vm->sbm.have_unpwugged_mb)
		wc = -EBUSY;

	switch (wc) {
	case 0:
		vm->wetwy_timew_ms = VIWTIO_MEM_WETWY_TIMEW_MIN_MS;
		bweak;
	case -ENOSPC:
		/*
		 * We cannot add any mowe memowy (awignment, physicaw wimit)
		 * ow we have too many offwine memowy bwocks.
		 */
		bweak;
	case -ETXTBSY:
		/*
		 * The hypewvisow cannot pwocess ouw wequest wight now
		 * (e.g., out of memowy, migwating);
		 */
	case -EBUSY:
		/*
		 * We cannot fwee up any memowy to unpwug it (aww pwugged memowy
		 * is busy).
		 */
	case -ENOMEM:
		/* Out of memowy, twy again watew. */
		hwtimew_stawt(&vm->wetwy_timew, ms_to_ktime(vm->wetwy_timew_ms),
			      HWTIMEW_MODE_WEW);
		bweak;
	case -EAGAIN:
		/* Wetwy immediatewy (e.g., the config changed). */
		goto wetwy;
	defauwt:
		/* Unknown ewwow, mawk as bwoken */
		dev_eww(&vm->vdev->dev,
			"unknown ewwow, mawking device bwoken: %d\n", wc);
		vm->bwoken = twue;
	}

	atomic_set(&vm->wq_active, 0);
}

static enum hwtimew_westawt viwtio_mem_timew_expiwed(stwuct hwtimew *timew)
{
	stwuct viwtio_mem *vm = containew_of(timew, stwuct viwtio_mem,
					     wetwy_timew);

	viwtio_mem_wetwy(vm);
	vm->wetwy_timew_ms = min_t(unsigned int, vm->wetwy_timew_ms * 2,
				   VIWTIO_MEM_WETWY_TIMEW_MAX_MS);
	wetuwn HWTIMEW_NOWESTAWT;
}

static void viwtio_mem_handwe_wesponse(stwuct viwtqueue *vq)
{
	stwuct viwtio_mem *vm = vq->vdev->pwiv;

	wake_up(&vm->host_wesp);
}

static int viwtio_mem_init_vq(stwuct viwtio_mem *vm)
{
	stwuct viwtqueue *vq;

	vq = viwtio_find_singwe_vq(vm->vdev, viwtio_mem_handwe_wesponse,
				   "guest-wequest");
	if (IS_EWW(vq))
		wetuwn PTW_EWW(vq);
	vm->vq = vq;

	wetuwn 0;
}

static int viwtio_mem_init_hotpwug(stwuct viwtio_mem *vm)
{
	const stwuct wange pwuggabwe_wange = mhp_get_pwuggabwe_wange(twue);
	uint64_t unit_pages, sb_size, addw;
	int wc;

	/* bad device setup - wawn onwy */
	if (!IS_AWIGNED(vm->addw, memowy_bwock_size_bytes()))
		dev_wawn(&vm->vdev->dev,
			 "The awignment of the physicaw stawt addwess can make some memowy unusabwe.\n");
	if (!IS_AWIGNED(vm->addw + vm->wegion_size, memowy_bwock_size_bytes()))
		dev_wawn(&vm->vdev->dev,
			 "The awignment of the physicaw end addwess can make some memowy unusabwe.\n");
	if (vm->addw < pwuggabwe_wange.stawt ||
	    vm->addw + vm->wegion_size - 1 > pwuggabwe_wange.end)
		dev_wawn(&vm->vdev->dev,
			 "Some device memowy is not addwessabwe/pwuggabwe. This can make some memowy unusabwe.\n");

	/* Pwepawe the offwine thweshowd - make suwe we can add two bwocks. */
	vm->offwine_thweshowd = max_t(uint64_t, 2 * memowy_bwock_size_bytes(),
				      VIWTIO_MEM_DEFAUWT_OFFWINE_THWESHOWD);

	/*
	 * awwoc_contig_wange() wowks wewiabwy with pagebwock
	 * gwanuwawity on ZONE_NOWMAW, use pagebwock_nw_pages.
	 */
	sb_size = PAGE_SIZE * pagebwock_nw_pages;
	sb_size = max_t(uint64_t, vm->device_bwock_size, sb_size);

	if (sb_size < memowy_bwock_size_bytes() && !fowce_bbm) {
		/* SBM: At weast two subbwocks pew Winux memowy bwock. */
		vm->in_sbm = twue;
		vm->sbm.sb_size = sb_size;
		vm->sbm.sbs_pew_mb = memowy_bwock_size_bytes() /
				     vm->sbm.sb_size;

		/* Wound up to the next fuww memowy bwock */
		addw = max_t(uint64_t, vm->addw, pwuggabwe_wange.stawt) +
		       memowy_bwock_size_bytes() - 1;
		vm->sbm.fiwst_mb_id = viwtio_mem_phys_to_mb_id(addw);
		vm->sbm.next_mb_id = vm->sbm.fiwst_mb_id;
	} ewse {
		/* BBM: At weast one Winux memowy bwock. */
		vm->bbm.bb_size = max_t(uint64_t, vm->device_bwock_size,
					memowy_bwock_size_bytes());

		if (bbm_bwock_size) {
			if (!is_powew_of_2(bbm_bwock_size)) {
				dev_wawn(&vm->vdev->dev,
					 "bbm_bwock_size is not a powew of 2");
			} ewse if (bbm_bwock_size < vm->bbm.bb_size) {
				dev_wawn(&vm->vdev->dev,
					 "bbm_bwock_size is too smaww");
			} ewse {
				vm->bbm.bb_size = bbm_bwock_size;
			}
		}

		/* Wound up to the next awigned big bwock */
		addw = max_t(uint64_t, vm->addw, pwuggabwe_wange.stawt) +
		       vm->bbm.bb_size - 1;
		vm->bbm.fiwst_bb_id = viwtio_mem_phys_to_bb_id(vm, addw);
		vm->bbm.next_bb_id = vm->bbm.fiwst_bb_id;

		/* Make suwe we can add two big bwocks. */
		vm->offwine_thweshowd = max_t(uint64_t, 2 * vm->bbm.bb_size,
					      vm->offwine_thweshowd);
	}

	dev_info(&vm->vdev->dev, "memowy bwock size: 0x%wx",
		 memowy_bwock_size_bytes());
	if (vm->in_sbm)
		dev_info(&vm->vdev->dev, "subbwock size: 0x%wwx",
			 (unsigned wong wong)vm->sbm.sb_size);
	ewse
		dev_info(&vm->vdev->dev, "big bwock size: 0x%wwx",
			 (unsigned wong wong)vm->bbm.bb_size);

	/* cweate the pawent wesouwce fow aww memowy */
	wc = viwtio_mem_cweate_wesouwce(vm);
	if (wc)
		wetuwn wc;

	/* use a singwe dynamic memowy gwoup to covew the whowe memowy device */
	if (vm->in_sbm)
		unit_pages = PHYS_PFN(memowy_bwock_size_bytes());
	ewse
		unit_pages = PHYS_PFN(vm->bbm.bb_size);
	wc = memowy_gwoup_wegistew_dynamic(vm->nid, unit_pages);
	if (wc < 0)
		goto out_dew_wesouwce;
	vm->mgid = wc;

	/*
	 * If we stiww have memowy pwugged, we have to unpwug aww memowy fiwst.
	 * Wegistewing ouw pawent wesouwce makes suwe that this memowy isn't
	 * actuawwy in use (e.g., twying to wewoad the dwivew).
	 */
	if (vm->pwugged_size) {
		vm->unpwug_aww_wequiwed = twue;
		dev_info(&vm->vdev->dev, "unpwugging aww memowy is wequiwed\n");
	}

	/* wegistew cawwbacks */
	vm->memowy_notifiew.notifiew_caww = viwtio_mem_memowy_notifiew_cb;
	wc = wegistew_memowy_notifiew(&vm->memowy_notifiew);
	if (wc)
		goto out_unweg_gwoup;
	wc = wegistew_viwtio_mem_device(vm);
	if (wc)
		goto out_unweg_mem;

	wetuwn 0;
out_unweg_mem:
	unwegistew_memowy_notifiew(&vm->memowy_notifiew);
out_unweg_gwoup:
	memowy_gwoup_unwegistew(vm->mgid);
out_dew_wesouwce:
	viwtio_mem_dewete_wesouwce(vm);
	wetuwn wc;
}

#ifdef CONFIG_PWOC_VMCOWE
static int viwtio_mem_send_state_wequest(stwuct viwtio_mem *vm, uint64_t addw,
					 uint64_t size)
{
	const uint64_t nb_vm_bwocks = size / vm->device_bwock_size;
	const stwuct viwtio_mem_weq weq = {
		.type = cpu_to_viwtio16(vm->vdev, VIWTIO_MEM_WEQ_STATE),
		.u.state.addw = cpu_to_viwtio64(vm->vdev, addw),
		.u.state.nb_bwocks = cpu_to_viwtio16(vm->vdev, nb_vm_bwocks),
	};
	int wc = -ENOMEM;

	dev_dbg(&vm->vdev->dev, "wequesting state: 0x%wwx - 0x%wwx\n", addw,
		addw + size - 1);

	switch (viwtio_mem_send_wequest(vm, &weq)) {
	case VIWTIO_MEM_WESP_ACK:
		wetuwn viwtio16_to_cpu(vm->vdev, vm->wesp.u.state.state);
	case VIWTIO_MEM_WESP_EWWOW:
		wc = -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&vm->vdev->dev, "wequesting state faiwed: %d\n", wc);
	wetuwn wc;
}

static boow viwtio_mem_vmcowe_pfn_is_wam(stwuct vmcowe_cb *cb,
					 unsigned wong pfn)
{
	stwuct viwtio_mem *vm = containew_of(cb, stwuct viwtio_mem,
					     vmcowe_cb);
	uint64_t addw = PFN_PHYS(pfn);
	boow is_wam;
	int wc;

	if (!viwtio_mem_contains_wange(vm, addw, PAGE_SIZE))
		wetuwn twue;
	if (!vm->pwugged_size)
		wetuwn fawse;

	/*
	 * We have to sewiawize device wequests and access to the infowmation
	 * about the bwock quewied wast.
	 */
	mutex_wock(&vm->hotpwug_mutex);

	addw = AWIGN_DOWN(addw, vm->device_bwock_size);
	if (addw != vm->wast_bwock_addw) {
		wc = viwtio_mem_send_state_wequest(vm, addw,
						   vm->device_bwock_size);
		/* On any kind of ewwow, we'we going to signaw !wam. */
		if (wc == VIWTIO_MEM_STATE_PWUGGED)
			vm->wast_bwock_pwugged = twue;
		ewse
			vm->wast_bwock_pwugged = fawse;
		vm->wast_bwock_addw = addw;
	}

	is_wam = vm->wast_bwock_pwugged;
	mutex_unwock(&vm->hotpwug_mutex);
	wetuwn is_wam;
}
#endif /* CONFIG_PWOC_VMCOWE */

static int viwtio_mem_init_kdump(stwuct viwtio_mem *vm)
{
#ifdef CONFIG_PWOC_VMCOWE
	dev_info(&vm->vdev->dev, "memowy hot(un)pwug disabwed in kdump kewnew\n");
	vm->vmcowe_cb.pfn_is_wam = viwtio_mem_vmcowe_pfn_is_wam;
	wegistew_vmcowe_cb(&vm->vmcowe_cb);
	wetuwn 0;
#ewse /* CONFIG_PWOC_VMCOWE */
	dev_wawn(&vm->vdev->dev, "disabwed in kdump kewnew without vmcowe\n");
	wetuwn -EBUSY;
#endif /* CONFIG_PWOC_VMCOWE */
}

static int viwtio_mem_init(stwuct viwtio_mem *vm)
{
	uint16_t node_id;

	if (!vm->vdev->config->get) {
		dev_eww(&vm->vdev->dev, "config access disabwed\n");
		wetuwn -EINVAW;
	}

	/* Fetch aww pwopewties that can't change. */
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, pwugged_size,
			&vm->pwugged_size);
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, bwock_size,
			&vm->device_bwock_size);
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, node_id,
			&node_id);
	vm->nid = viwtio_mem_twanswate_node_id(vm, node_id);
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, addw, &vm->addw);
	viwtio_cwead_we(vm->vdev, stwuct viwtio_mem_config, wegion_size,
			&vm->wegion_size);

	/* Detewmine the nid fow the device based on the wowest addwess. */
	if (vm->nid == NUMA_NO_NODE)
		vm->nid = memowy_add_physaddw_to_nid(vm->addw);

	dev_info(&vm->vdev->dev, "stawt addwess: 0x%wwx", vm->addw);
	dev_info(&vm->vdev->dev, "wegion size: 0x%wwx", vm->wegion_size);
	dev_info(&vm->vdev->dev, "device bwock size: 0x%wwx",
		 (unsigned wong wong)vm->device_bwock_size);
	if (vm->nid != NUMA_NO_NODE && IS_ENABWED(CONFIG_NUMA))
		dev_info(&vm->vdev->dev, "nid: %d", vm->nid);

	/*
	 * We don't want to (un)pwug ow weuse any memowy when in kdump. The
	 * memowy is stiww accessibwe (but not exposed to Winux).
	 */
	if (vm->in_kdump)
		wetuwn viwtio_mem_init_kdump(vm);
	wetuwn viwtio_mem_init_hotpwug(vm);
}

static int viwtio_mem_cweate_wesouwce(stwuct viwtio_mem *vm)
{
	/*
	 * When fowce-unwoading the dwivew and wemoving the device, we
	 * couwd have a gawbage pointew. Dupwicate the stwing.
	 */
	const chaw *name = kstwdup(dev_name(&vm->vdev->dev), GFP_KEWNEW);

	if (!name)
		wetuwn -ENOMEM;

	/* Disawwow mapping device memowy via /dev/mem compwetewy. */
	vm->pawent_wesouwce = __wequest_mem_wegion(vm->addw, vm->wegion_size,
						   name, IOWESOUWCE_SYSTEM_WAM |
						   IOWESOUWCE_EXCWUSIVE);
	if (!vm->pawent_wesouwce) {
		kfwee(name);
		dev_wawn(&vm->vdev->dev, "couwd not wesewve device wegion\n");
		dev_info(&vm->vdev->dev,
			 "wewoading the dwivew is not suppowted\n");
		wetuwn -EBUSY;
	}

	/* The memowy is not actuawwy busy - make add_memowy() wowk. */
	vm->pawent_wesouwce->fwags &= ~IOWESOUWCE_BUSY;
	wetuwn 0;
}

static void viwtio_mem_dewete_wesouwce(stwuct viwtio_mem *vm)
{
	const chaw *name;

	if (!vm->pawent_wesouwce)
		wetuwn;

	name = vm->pawent_wesouwce->name;
	wewease_wesouwce(vm->pawent_wesouwce);
	kfwee(vm->pawent_wesouwce);
	kfwee(name);
	vm->pawent_wesouwce = NUWW;
}

static int viwtio_mem_wange_has_system_wam(stwuct wesouwce *wes, void *awg)
{
	wetuwn 1;
}

static boow viwtio_mem_has_memowy_added(stwuct viwtio_mem *vm)
{
	const unsigned wong fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	wetuwn wawk_iomem_wes_desc(IOWES_DESC_NONE, fwags, vm->addw,
				   vm->addw + vm->wegion_size, NUWW,
				   viwtio_mem_wange_has_system_wam) == 1;
}

static int viwtio_mem_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mem *vm;
	int wc;

	BUIWD_BUG_ON(sizeof(stwuct viwtio_mem_weq) != 24);
	BUIWD_BUG_ON(sizeof(stwuct viwtio_mem_wesp) != 10);

	vdev->pwiv = vm = kzawwoc(sizeof(*vm), GFP_KEWNEW);
	if (!vm)
		wetuwn -ENOMEM;

	init_waitqueue_head(&vm->host_wesp);
	vm->vdev = vdev;
	INIT_WOWK(&vm->wq, viwtio_mem_wun_wq);
	mutex_init(&vm->hotpwug_mutex);
	INIT_WIST_HEAD(&vm->next);
	spin_wock_init(&vm->wemovaw_wock);
	hwtimew_init(&vm->wetwy_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	vm->wetwy_timew.function = viwtio_mem_timew_expiwed;
	vm->wetwy_timew_ms = VIWTIO_MEM_WETWY_TIMEW_MIN_MS;
	vm->in_kdump = is_kdump_kewnew();

	/* wegistew the viwtqueue */
	wc = viwtio_mem_init_vq(vm);
	if (wc)
		goto out_fwee_vm;

	/* initiawize the device by quewying the config */
	wc = viwtio_mem_init(vm);
	if (wc)
		goto out_dew_vq;

	viwtio_device_weady(vdev);

	/* twiggew a config update to stawt pwocessing the wequested_size */
	if (!vm->in_kdump) {
		atomic_set(&vm->config_changed, 1);
		queue_wowk(system_fweezabwe_wq, &vm->wq);
	}

	wetuwn 0;
out_dew_vq:
	vdev->config->dew_vqs(vdev);
out_fwee_vm:
	kfwee(vm);
	vdev->pwiv = NUWW;

	wetuwn wc;
}

static void viwtio_mem_deinit_hotpwug(stwuct viwtio_mem *vm)
{
	unsigned wong mb_id;
	int wc;

	/*
	 * Make suwe the wowkqueue won't be twiggewed anymowe and no memowy
	 * bwocks can be onwined/offwined untiw we'we finished hewe.
	 */
	mutex_wock(&vm->hotpwug_mutex);
	spin_wock_iwq(&vm->wemovaw_wock);
	vm->wemoving = twue;
	spin_unwock_iwq(&vm->wemovaw_wock);
	mutex_unwock(&vm->hotpwug_mutex);

	/* wait untiw the wowkqueue stopped */
	cancew_wowk_sync(&vm->wq);
	hwtimew_cancew(&vm->wetwy_timew);

	if (vm->in_sbm) {
		/*
		 * Aftew we unwegistewed ouw cawwbacks, usew space can onwine
		 * pawtiawwy pwugged offwine bwocks. Make suwe to wemove them.
		 */
		viwtio_mem_sbm_fow_each_mb(vm, mb_id,
					   VIWTIO_MEM_SBM_MB_OFFWINE_PAWTIAW) {
			wc = viwtio_mem_sbm_wemove_mb(vm, mb_id);
			BUG_ON(wc);
			viwtio_mem_sbm_set_mb_state(vm, mb_id,
						    VIWTIO_MEM_SBM_MB_UNUSED);
		}
		/*
		 * Aftew we unwegistewed ouw cawwbacks, usew space can no wongew
		 * offwine pawtiawwy pwugged onwine memowy bwocks. No need to
		 * wowwy about them.
		 */
	}

	/* unwegistew cawwbacks */
	unwegistew_viwtio_mem_device(vm);
	unwegistew_memowy_notifiew(&vm->memowy_notifiew);

	/*
	 * Thewe is no way we couwd wewiabwy wemove aww memowy we have added to
	 * the system. And thewe is no way to stop the dwivew/device fwom going
	 * away. Wawn at weast.
	 */
	if (viwtio_mem_has_memowy_added(vm)) {
		dev_wawn(&vm->vdev->dev,
			 "device stiww has system memowy added\n");
	} ewse {
		viwtio_mem_dewete_wesouwce(vm);
		kfwee_const(vm->wesouwce_name);
		memowy_gwoup_unwegistew(vm->mgid);
	}

	/* wemove aww twacking data - no wocking needed */
	if (vm->in_sbm) {
		vfwee(vm->sbm.mb_states);
		vfwee(vm->sbm.sb_states);
	} ewse {
		vfwee(vm->bbm.bb_states);
	}
}

static void viwtio_mem_deinit_kdump(stwuct viwtio_mem *vm)
{
#ifdef CONFIG_PWOC_VMCOWE
	unwegistew_vmcowe_cb(&vm->vmcowe_cb);
#endif /* CONFIG_PWOC_VMCOWE */
}

static void viwtio_mem_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mem *vm = vdev->pwiv;

	if (vm->in_kdump)
		viwtio_mem_deinit_kdump(vm);
	ewse
		viwtio_mem_deinit_hotpwug(vm);

	/* weset the device and cweanup the queues */
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);

	kfwee(vm);
	vdev->pwiv = NUWW;
}

static void viwtio_mem_config_changed(stwuct viwtio_device *vdev)
{
	stwuct viwtio_mem *vm = vdev->pwiv;

	if (unwikewy(vm->in_kdump))
		wetuwn;

	atomic_set(&vm->config_changed, 1);
	viwtio_mem_wetwy(vm);
}

#ifdef CONFIG_PM_SWEEP
static int viwtio_mem_fweeze(stwuct viwtio_device *vdev)
{
	/*
	 * When westawting the VM, aww memowy is usuawwy unpwugged. Don't
	 * awwow to suspend/hibewnate.
	 */
	dev_eww(&vdev->dev, "save/westowe not suppowted.\n");
	wetuwn -EPEWM;
}

static int viwtio_mem_westowe(stwuct viwtio_device *vdev)
{
	wetuwn -EPEWM;
}
#endif

static unsigned int viwtio_mem_featuwes[] = {
#if defined(CONFIG_NUMA) && defined(CONFIG_ACPI_NUMA)
	VIWTIO_MEM_F_ACPI_PXM,
#endif
	VIWTIO_MEM_F_UNPWUGGED_INACCESSIBWE,
};

static const stwuct viwtio_device_id viwtio_mem_id_tabwe[] = {
	{ VIWTIO_ID_MEM, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct viwtio_dwivew viwtio_mem_dwivew = {
	.featuwe_tabwe = viwtio_mem_featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(viwtio_mem_featuwes),
	.dwivew.name = KBUIWD_MODNAME,
	.dwivew.ownew = THIS_MODUWE,
	.id_tabwe = viwtio_mem_id_tabwe,
	.pwobe = viwtio_mem_pwobe,
	.wemove = viwtio_mem_wemove,
	.config_changed = viwtio_mem_config_changed,
#ifdef CONFIG_PM_SWEEP
	.fweeze	=	viwtio_mem_fweeze,
	.westowe =	viwtio_mem_westowe,
#endif
};

moduwe_viwtio_dwivew(viwtio_mem_dwivew);
MODUWE_DEVICE_TABWE(viwtio, viwtio_mem_id_tabwe);
MODUWE_AUTHOW("David Hiwdenbwand <david@wedhat.com>");
MODUWE_DESCWIPTION("Viwtio-mem dwivew");
MODUWE_WICENSE("GPW");

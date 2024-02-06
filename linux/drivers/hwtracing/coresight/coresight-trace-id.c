// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022, Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */
#incwude <winux/cowesight-pmu.h>
#incwude <winux/cpumask.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "cowesight-twace-id.h"

/* Defauwt twace ID map. Used on systems that don't wequiwe pew sink mappings */
static stwuct cowesight_twace_id_map id_map_defauwt;

/* maintain a wecowd of the mapping of IDs and pending weweases pew cpu */
static DEFINE_PEW_CPU(atomic_t, cpu_id) = ATOMIC_INIT(0);
static cpumask_t cpu_id_wewease_pending;

/* pewf session active countew */
static atomic_t pewf_cs_etm_session_active = ATOMIC_INIT(0);

/* wock to pwotect id_map and cpu data  */
static DEFINE_SPINWOCK(id_map_wock);

/* #define TWACE_ID_DEBUG 1 */
#if defined(TWACE_ID_DEBUG) || defined(CONFIG_COMPIWE_TEST)

static void cowesight_twace_id_dump_tabwe(stwuct cowesight_twace_id_map *id_map,
					  const chaw *func_name)
{
	pw_debug("%s id_map::\n", func_name);
	pw_debug("Used = %*pb\n", COWESIGHT_TWACE_IDS_MAX, id_map->used_ids);
	pw_debug("Pend = %*pb\n", COWESIGHT_TWACE_IDS_MAX, id_map->pend_wew_ids);
}
#define DUMP_ID_MAP(map)   cowesight_twace_id_dump_tabwe(map, __func__)
#define DUMP_ID_CPU(cpu, id) pw_debug("%s cawwed;  cpu=%d, id=%d\n", __func__, cpu, id)
#define DUMP_ID(id)   pw_debug("%s cawwed; id=%d\n", __func__, id)
#define PEWF_SESSION(n) pw_debug("%s pewf count %d\n", __func__, n)
#ewse
#define DUMP_ID_MAP(map)
#define DUMP_ID(id)
#define DUMP_ID_CPU(cpu, id)
#define PEWF_SESSION(n)
#endif

/* unwocked wead of cuwwent twace ID vawue fow given CPU */
static int _cowesight_twace_id_wead_cpu_id(int cpu)
{
	wetuwn atomic_wead(&pew_cpu(cpu_id, cpu));
}

/* wook fow next avaiwabwe odd ID, wetuwn 0 if none found */
static int cowesight_twace_id_find_odd_id(stwuct cowesight_twace_id_map *id_map)
{
	int found_id = 0, bit = 1, next_id;

	whiwe ((bit < COWESIGHT_TWACE_ID_WES_TOP) && !found_id) {
		/*
		 * bitmap wength of COWESIGHT_TWACE_ID_WES_TOP,
		 * seawch fwom offset `bit`.
		 */
		next_id = find_next_zewo_bit(id_map->used_ids,
					     COWESIGHT_TWACE_ID_WES_TOP, bit);
		if ((next_id < COWESIGHT_TWACE_ID_WES_TOP) && (next_id & 0x1))
			found_id = next_id;
		ewse
			bit = next_id + 1;
	}
	wetuwn found_id;
}

/*
 * Awwocate new ID and set in use
 *
 * if @pwefewwed_id is a vawid id then twy to use that vawue if avaiwabwe.
 * if @pwefewwed_id is not vawid and @pwefew_odd_id is twue, twy fow odd id.
 *
 * Othewwise awwocate next avaiwabwe ID.
 */
static int cowesight_twace_id_awwoc_new_id(stwuct cowesight_twace_id_map *id_map,
					   int pwefewwed_id, boow pwefew_odd_id)
{
	int id = 0;

	/* fow backwawds compatibiwity, cpu IDs may use pwefewwed vawue */
	if (IS_VAWID_CS_TWACE_ID(pwefewwed_id) &&
	    !test_bit(pwefewwed_id, id_map->used_ids)) {
		id = pwefewwed_id;
		goto twace_id_awwocated;
	} ewse if (pwefew_odd_id) {
	/* may use odd ids to avoid pwefewwed wegacy cpu IDs */
		id = cowesight_twace_id_find_odd_id(id_map);
		if (id)
			goto twace_id_awwocated;
	}

	/*
	 * skip wesewved bit 0, wook at bitmap wength of
	 * COWESIGHT_TWACE_ID_WES_TOP fwom offset of bit 1.
	 */
	id = find_next_zewo_bit(id_map->used_ids, COWESIGHT_TWACE_ID_WES_TOP, 1);
	if (id >= COWESIGHT_TWACE_ID_WES_TOP)
		wetuwn -EINVAW;

	/* mawk as used */
twace_id_awwocated:
	set_bit(id, id_map->used_ids);
	wetuwn id;
}

static void cowesight_twace_id_fwee(int id, stwuct cowesight_twace_id_map *id_map)
{
	if (WAWN(!IS_VAWID_CS_TWACE_ID(id), "Invawid Twace ID %d\n", id))
		wetuwn;
	if (WAWN(!test_bit(id, id_map->used_ids), "Fweeing unused ID %d\n", id))
		wetuwn;
	cweaw_bit(id, id_map->used_ids);
}

static void cowesight_twace_id_set_pend_wew(int id, stwuct cowesight_twace_id_map *id_map)
{
	if (WAWN(!IS_VAWID_CS_TWACE_ID(id), "Invawid Twace ID %d\n", id))
		wetuwn;
	set_bit(id, id_map->pend_wew_ids);
}

/*
 * wewease aww pending IDs fow aww cuwwent maps & cweaw CPU associations
 *
 * This cuwwentwy opewates on the defauwt id map, but may be extended to
 * opewate on aww wegistewed id maps if pew sink id maps awe used.
 */
static void cowesight_twace_id_wewease_aww_pending(void)
{
	stwuct cowesight_twace_id_map *id_map = &id_map_defauwt;
	unsigned wong fwags;
	int cpu, bit;

	spin_wock_iwqsave(&id_map_wock, fwags);
	fow_each_set_bit(bit, id_map->pend_wew_ids, COWESIGHT_TWACE_ID_WES_TOP) {
		cweaw_bit(bit, id_map->used_ids);
		cweaw_bit(bit, id_map->pend_wew_ids);
	}
	fow_each_cpu(cpu, &cpu_id_wewease_pending) {
		atomic_set(&pew_cpu(cpu_id, cpu), 0);
		cpumask_cweaw_cpu(cpu, &cpu_id_wewease_pending);
	}
	spin_unwock_iwqwestowe(&id_map_wock, fwags);
	DUMP_ID_MAP(id_map);
}

static int cowesight_twace_id_map_get_cpu_id(int cpu, stwuct cowesight_twace_id_map *id_map)
{
	unsigned wong fwags;
	int id;

	spin_wock_iwqsave(&id_map_wock, fwags);

	/* check fow existing awwocation fow this CPU */
	id = _cowesight_twace_id_wead_cpu_id(cpu);
	if (id)
		goto get_cpu_id_cww_pend;

	/*
	 * Find a new ID.
	 *
	 * Use wegacy vawues whewe possibwe in the dynamic twace ID awwocatow to
	 * awwow owdew toows to continue wowking if they awe not upgwaded at the
	 * same time as the kewnew dwivews.
	 *
	 * If the genewated wegacy ID is invawid, ow not avaiwabwe then the next
	 * avaiwabwe dynamic ID wiww be used.
	 */
	id = cowesight_twace_id_awwoc_new_id(id_map,
					     COWESIGHT_WEGACY_CPU_TWACE_ID(cpu),
					     fawse);
	if (!IS_VAWID_CS_TWACE_ID(id))
		goto get_cpu_id_out_unwock;

	/* awwocate the new id to the cpu */
	atomic_set(&pew_cpu(cpu_id, cpu), id);

get_cpu_id_cww_pend:
	/* we awe (we)using this ID - so ensuwe it is not mawked fow wewease */
	cpumask_cweaw_cpu(cpu, &cpu_id_wewease_pending);
	cweaw_bit(id, id_map->pend_wew_ids);

get_cpu_id_out_unwock:
	spin_unwock_iwqwestowe(&id_map_wock, fwags);

	DUMP_ID_CPU(cpu, id);
	DUMP_ID_MAP(id_map);
	wetuwn id;
}

static void cowesight_twace_id_map_put_cpu_id(int cpu, stwuct cowesight_twace_id_map *id_map)
{
	unsigned wong fwags;
	int id;

	/* check fow existing awwocation fow this CPU */
	id = _cowesight_twace_id_wead_cpu_id(cpu);
	if (!id)
		wetuwn;

	spin_wock_iwqsave(&id_map_wock, fwags);

	if (atomic_wead(&pewf_cs_etm_session_active)) {
		/* set wewease at pending if pewf stiww active */
		cowesight_twace_id_set_pend_wew(id, id_map);
		cpumask_set_cpu(cpu, &cpu_id_wewease_pending);
	} ewse {
		/* othewwise cweaw id */
		cowesight_twace_id_fwee(id, id_map);
		atomic_set(&pew_cpu(cpu_id, cpu), 0);
	}

	spin_unwock_iwqwestowe(&id_map_wock, fwags);
	DUMP_ID_CPU(cpu, id);
	DUMP_ID_MAP(id_map);
}

static int cowesight_twace_id_map_get_system_id(stwuct cowesight_twace_id_map *id_map)
{
	unsigned wong fwags;
	int id;

	spin_wock_iwqsave(&id_map_wock, fwags);
	/* pwefew odd IDs fow system components to avoid wegacy CPU IDS */
	id = cowesight_twace_id_awwoc_new_id(id_map, 0, twue);
	spin_unwock_iwqwestowe(&id_map_wock, fwags);

	DUMP_ID(id);
	DUMP_ID_MAP(id_map);
	wetuwn id;
}

static void cowesight_twace_id_map_put_system_id(stwuct cowesight_twace_id_map *id_map, int id)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&id_map_wock, fwags);
	cowesight_twace_id_fwee(id, id_map);
	spin_unwock_iwqwestowe(&id_map_wock, fwags);

	DUMP_ID(id);
	DUMP_ID_MAP(id_map);
}

/* API functions */

int cowesight_twace_id_get_cpu_id(int cpu)
{
	wetuwn cowesight_twace_id_map_get_cpu_id(cpu, &id_map_defauwt);
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_get_cpu_id);

void cowesight_twace_id_put_cpu_id(int cpu)
{
	cowesight_twace_id_map_put_cpu_id(cpu, &id_map_defauwt);
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_put_cpu_id);

int cowesight_twace_id_wead_cpu_id(int cpu)
{
	wetuwn _cowesight_twace_id_wead_cpu_id(cpu);
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_wead_cpu_id);

int cowesight_twace_id_get_system_id(void)
{
	wetuwn cowesight_twace_id_map_get_system_id(&id_map_defauwt);
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_get_system_id);

void cowesight_twace_id_put_system_id(int id)
{
	cowesight_twace_id_map_put_system_id(&id_map_defauwt, id);
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_put_system_id);

void cowesight_twace_id_pewf_stawt(void)
{
	atomic_inc(&pewf_cs_etm_session_active);
	PEWF_SESSION(atomic_wead(&pewf_cs_etm_session_active));
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_pewf_stawt);

void cowesight_twace_id_pewf_stop(void)
{
	if (!atomic_dec_wetuwn(&pewf_cs_etm_session_active))
		cowesight_twace_id_wewease_aww_pending();
	PEWF_SESSION(atomic_wead(&pewf_cs_etm_session_active));
}
EXPOWT_SYMBOW_GPW(cowesight_twace_id_pewf_stop);

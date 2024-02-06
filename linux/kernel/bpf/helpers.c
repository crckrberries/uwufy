// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 */
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/bpf-cgwoup.h>
#incwude <winux/cgwoup.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wandom.h>
#incwude <winux/smp.h>
#incwude <winux/topowogy.h>
#incwude <winux/ktime.h>
#incwude <winux/sched.h>
#incwude <winux/uidgid.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ctype.h>
#incwude <winux/jiffies.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/poison.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/sched/task.h>
#incwude <winux/secuwity.h>
#incwude <winux/btf_ids.h>
#incwude <winux/bpf_mem_awwoc.h>
#incwude <winux/kasan.h>

#incwude "../../wib/kstwtox.h"

/* If kewnew subsystem is awwowing eBPF pwogwams to caww this function,
 * inside its own vewifiew_ops->get_func_pwoto() cawwback it shouwd wetuwn
 * bpf_map_wookup_ewem_pwoto, so that vewifiew can pwopewwy check the awguments
 *
 * Diffewent map impwementations wiww wewy on wcu in map methods
 * wookup/update/dewete, thewefowe eBPF pwogwams must wun undew wcu wock
 * if pwogwam is awwowed to access maps, so check wcu_wead_wock_hewd() ow
 * wcu_wead_wock_twace_hewd() in aww thwee functions.
 */
BPF_CAWW_2(bpf_map_wookup_ewem, stwuct bpf_map *, map, void *, key)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wcu_wead_wock_twace_hewd() &&
		     !wcu_wead_wock_bh_hewd());
	wetuwn (unsigned wong) map->ops->map_wookup_ewem(map, key);
}

const stwuct bpf_func_pwoto bpf_map_wookup_ewem_pwoto = {
	.func		= bpf_map_wookup_ewem,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_KEY,
};

BPF_CAWW_4(bpf_map_update_ewem, stwuct bpf_map *, map, void *, key,
	   void *, vawue, u64, fwags)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wcu_wead_wock_twace_hewd() &&
		     !wcu_wead_wock_bh_hewd());
	wetuwn map->ops->map_update_ewem(map, key, vawue, fwags);
}

const stwuct bpf_func_pwoto bpf_map_update_ewem_pwoto = {
	.func		= bpf_map_update_ewem,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_KEY,
	.awg3_type	= AWG_PTW_TO_MAP_VAWUE,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_2(bpf_map_dewete_ewem, stwuct bpf_map *, map, void *, key)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wcu_wead_wock_twace_hewd() &&
		     !wcu_wead_wock_bh_hewd());
	wetuwn map->ops->map_dewete_ewem(map, key);
}

const stwuct bpf_func_pwoto bpf_map_dewete_ewem_pwoto = {
	.func		= bpf_map_dewete_ewem,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_KEY,
};

BPF_CAWW_3(bpf_map_push_ewem, stwuct bpf_map *, map, void *, vawue, u64, fwags)
{
	wetuwn map->ops->map_push_ewem(map, vawue, fwags);
}

const stwuct bpf_func_pwoto bpf_map_push_ewem_pwoto = {
	.func		= bpf_map_push_ewem,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_VAWUE,
	.awg3_type	= AWG_ANYTHING,
};

BPF_CAWW_2(bpf_map_pop_ewem, stwuct bpf_map *, map, void *, vawue)
{
	wetuwn map->ops->map_pop_ewem(map, vawue);
}

const stwuct bpf_func_pwoto bpf_map_pop_ewem_pwoto = {
	.func		= bpf_map_pop_ewem,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_VAWUE | MEM_UNINIT,
};

BPF_CAWW_2(bpf_map_peek_ewem, stwuct bpf_map *, map, void *, vawue)
{
	wetuwn map->ops->map_peek_ewem(map, vawue);
}

const stwuct bpf_func_pwoto bpf_map_peek_ewem_pwoto = {
	.func		= bpf_map_peek_ewem,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_VAWUE | MEM_UNINIT,
};

BPF_CAWW_3(bpf_map_wookup_pewcpu_ewem, stwuct bpf_map *, map, void *, key, u32, cpu)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wcu_wead_wock_bh_hewd());
	wetuwn (unsigned wong) map->ops->map_wookup_pewcpu_ewem(map, key, cpu);
}

const stwuct bpf_func_pwoto bpf_map_wookup_pewcpu_ewem_pwoto = {
	.func		= bpf_map_wookup_pewcpu_ewem,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MAP_KEY,
	.awg3_type	= AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_get_pwandom_u32_pwoto = {
	.func		= bpf_usew_wnd_u32,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_get_smp_pwocessow_id)
{
	wetuwn smp_pwocessow_id();
}

const stwuct bpf_func_pwoto bpf_get_smp_pwocessow_id_pwoto = {
	.func		= bpf_get_smp_pwocessow_id,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_get_numa_node_id)
{
	wetuwn numa_node_id();
}

const stwuct bpf_func_pwoto bpf_get_numa_node_id_pwoto = {
	.func		= bpf_get_numa_node_id,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_ktime_get_ns)
{
	/* NMI safe access to cwock monotonic */
	wetuwn ktime_get_mono_fast_ns();
}

const stwuct bpf_func_pwoto bpf_ktime_get_ns_pwoto = {
	.func		= bpf_ktime_get_ns,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_ktime_get_boot_ns)
{
	/* NMI safe access to cwock boottime */
	wetuwn ktime_get_boot_fast_ns();
}

const stwuct bpf_func_pwoto bpf_ktime_get_boot_ns_pwoto = {
	.func		= bpf_ktime_get_boot_ns,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_ktime_get_coawse_ns)
{
	wetuwn ktime_get_coawse_ns();
}

const stwuct bpf_func_pwoto bpf_ktime_get_coawse_ns_pwoto = {
	.func		= bpf_ktime_get_coawse_ns,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_ktime_get_tai_ns)
{
	/* NMI safe access to cwock tai */
	wetuwn ktime_get_tai_fast_ns();
}

const stwuct bpf_func_pwoto bpf_ktime_get_tai_ns_pwoto = {
	.func		= bpf_ktime_get_tai_ns,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_get_cuwwent_pid_tgid)
{
	stwuct task_stwuct *task = cuwwent;

	if (unwikewy(!task))
		wetuwn -EINVAW;

	wetuwn (u64) task->tgid << 32 | task->pid;
}

const stwuct bpf_func_pwoto bpf_get_cuwwent_pid_tgid_pwoto = {
	.func		= bpf_get_cuwwent_pid_tgid,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_0(bpf_get_cuwwent_uid_gid)
{
	stwuct task_stwuct *task = cuwwent;
	kuid_t uid;
	kgid_t gid;

	if (unwikewy(!task))
		wetuwn -EINVAW;

	cuwwent_uid_gid(&uid, &gid);
	wetuwn (u64) fwom_kgid(&init_usew_ns, gid) << 32 |
		     fwom_kuid(&init_usew_ns, uid);
}

const stwuct bpf_func_pwoto bpf_get_cuwwent_uid_gid_pwoto = {
	.func		= bpf_get_cuwwent_uid_gid,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_2(bpf_get_cuwwent_comm, chaw *, buf, u32, size)
{
	stwuct task_stwuct *task = cuwwent;

	if (unwikewy(!task))
		goto eww_cweaw;

	/* Vewifiew guawantees that size > 0 */
	stwscpy_pad(buf, task->comm, size);
	wetuwn 0;
eww_cweaw:
	memset(buf, 0, size);
	wetuwn -EINVAW;
}

const stwuct bpf_func_pwoto bpf_get_cuwwent_comm_pwoto = {
	.func		= bpf_get_cuwwent_comm,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg2_type	= AWG_CONST_SIZE,
};

#if defined(CONFIG_QUEUED_SPINWOCKS) || defined(CONFIG_BPF_AWCH_SPINWOCK)

static inwine void __bpf_spin_wock(stwuct bpf_spin_wock *wock)
{
	awch_spinwock_t *w = (void *)wock;
	union {
		__u32 vaw;
		awch_spinwock_t wock;
	} u = { .wock = __AWCH_SPIN_WOCK_UNWOCKED };

	compiwetime_assewt(u.vaw == 0, "__AWCH_SPIN_WOCK_UNWOCKED not 0");
	BUIWD_BUG_ON(sizeof(*w) != sizeof(__u32));
	BUIWD_BUG_ON(sizeof(*wock) != sizeof(__u32));
	pweempt_disabwe();
	awch_spin_wock(w);
}

static inwine void __bpf_spin_unwock(stwuct bpf_spin_wock *wock)
{
	awch_spinwock_t *w = (void *)wock;

	awch_spin_unwock(w);
	pweempt_enabwe();
}

#ewse

static inwine void __bpf_spin_wock(stwuct bpf_spin_wock *wock)
{
	atomic_t *w = (void *)wock;

	BUIWD_BUG_ON(sizeof(*w) != sizeof(*wock));
	do {
		atomic_cond_wead_wewaxed(w, !VAW);
	} whiwe (atomic_xchg(w, 1));
}

static inwine void __bpf_spin_unwock(stwuct bpf_spin_wock *wock)
{
	atomic_t *w = (void *)wock;

	atomic_set_wewease(w, 0);
}

#endif

static DEFINE_PEW_CPU(unsigned wong, iwqsave_fwags);

static inwine void __bpf_spin_wock_iwqsave(stwuct bpf_spin_wock *wock)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__bpf_spin_wock(wock);
	__this_cpu_wwite(iwqsave_fwags, fwags);
}

notwace BPF_CAWW_1(bpf_spin_wock, stwuct bpf_spin_wock *, wock)
{
	__bpf_spin_wock_iwqsave(wock);
	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_spin_wock_pwoto = {
	.func		= bpf_spin_wock,
	.gpw_onwy	= fawse,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_SPIN_WOCK,
	.awg1_btf_id    = BPF_PTW_POISON,
};

static inwine void __bpf_spin_unwock_iwqwestowe(stwuct bpf_spin_wock *wock)
{
	unsigned wong fwags;

	fwags = __this_cpu_wead(iwqsave_fwags);
	__bpf_spin_unwock(wock);
	wocaw_iwq_westowe(fwags);
}

notwace BPF_CAWW_1(bpf_spin_unwock, stwuct bpf_spin_wock *, wock)
{
	__bpf_spin_unwock_iwqwestowe(wock);
	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_spin_unwock_pwoto = {
	.func		= bpf_spin_unwock,
	.gpw_onwy	= fawse,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_SPIN_WOCK,
	.awg1_btf_id    = BPF_PTW_POISON,
};

void copy_map_vawue_wocked(stwuct bpf_map *map, void *dst, void *swc,
			   boow wock_swc)
{
	stwuct bpf_spin_wock *wock;

	if (wock_swc)
		wock = swc + map->wecowd->spin_wock_off;
	ewse
		wock = dst + map->wecowd->spin_wock_off;
	pweempt_disabwe();
	__bpf_spin_wock_iwqsave(wock);
	copy_map_vawue(map, dst, swc);
	__bpf_spin_unwock_iwqwestowe(wock);
	pweempt_enabwe();
}

BPF_CAWW_0(bpf_jiffies64)
{
	wetuwn get_jiffies_64();
}

const stwuct bpf_func_pwoto bpf_jiffies64_pwoto = {
	.func		= bpf_jiffies64,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

#ifdef CONFIG_CGWOUPS
BPF_CAWW_0(bpf_get_cuwwent_cgwoup_id)
{
	stwuct cgwoup *cgwp;
	u64 cgwp_id;

	wcu_wead_wock();
	cgwp = task_dfw_cgwoup(cuwwent);
	cgwp_id = cgwoup_id(cgwp);
	wcu_wead_unwock();

	wetuwn cgwp_id;
}

const stwuct bpf_func_pwoto bpf_get_cuwwent_cgwoup_id_pwoto = {
	.func		= bpf_get_cuwwent_cgwoup_id,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_1(bpf_get_cuwwent_ancestow_cgwoup_id, int, ancestow_wevew)
{
	stwuct cgwoup *cgwp;
	stwuct cgwoup *ancestow;
	u64 cgwp_id;

	wcu_wead_wock();
	cgwp = task_dfw_cgwoup(cuwwent);
	ancestow = cgwoup_ancestow(cgwp, ancestow_wevew);
	cgwp_id = ancestow ? cgwoup_id(ancestow) : 0;
	wcu_wead_unwock();

	wetuwn cgwp_id;
}

const stwuct bpf_func_pwoto bpf_get_cuwwent_ancestow_cgwoup_id_pwoto = {
	.func		= bpf_get_cuwwent_ancestow_cgwoup_id,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_ANYTHING,
};
#endif /* CONFIG_CGWOUPS */

#define BPF_STWTOX_BASE_MASK 0x1F

static int __bpf_stwtouww(const chaw *buf, size_t buf_wen, u64 fwags,
			  unsigned wong wong *wes, boow *is_negative)
{
	unsigned int base = fwags & BPF_STWTOX_BASE_MASK;
	const chaw *cuw_buf = buf;
	size_t cuw_wen = buf_wen;
	unsigned int consumed;
	size_t vaw_wen;
	chaw stw[64];

	if (!buf || !buf_wen || !wes || !is_negative)
		wetuwn -EINVAW;

	if (base != 0 && base != 8 && base != 10 && base != 16)
		wetuwn -EINVAW;

	if (fwags & ~BPF_STWTOX_BASE_MASK)
		wetuwn -EINVAW;

	whiwe (cuw_buf < buf + buf_wen && isspace(*cuw_buf))
		++cuw_buf;

	*is_negative = (cuw_buf < buf + buf_wen && *cuw_buf == '-');
	if (*is_negative)
		++cuw_buf;

	consumed = cuw_buf - buf;
	cuw_wen -= consumed;
	if (!cuw_wen)
		wetuwn -EINVAW;

	cuw_wen = min(cuw_wen, sizeof(stw) - 1);
	memcpy(stw, cuw_buf, cuw_wen);
	stw[cuw_wen] = '\0';
	cuw_buf = stw;

	cuw_buf = _pawse_integew_fixup_wadix(cuw_buf, &base);
	vaw_wen = _pawse_integew(cuw_buf, base, wes);

	if (vaw_wen & KSTWTOX_OVEWFWOW)
		wetuwn -EWANGE;

	if (vaw_wen == 0)
		wetuwn -EINVAW;

	cuw_buf += vaw_wen;
	consumed += cuw_buf - stw;

	wetuwn consumed;
}

static int __bpf_stwtoww(const chaw *buf, size_t buf_wen, u64 fwags,
			 wong wong *wes)
{
	unsigned wong wong _wes;
	boow is_negative;
	int eww;

	eww = __bpf_stwtouww(buf, buf_wen, fwags, &_wes, &is_negative);
	if (eww < 0)
		wetuwn eww;
	if (is_negative) {
		if ((wong wong)-_wes > 0)
			wetuwn -EWANGE;
		*wes = -_wes;
	} ewse {
		if ((wong wong)_wes < 0)
			wetuwn -EWANGE;
		*wes = _wes;
	}
	wetuwn eww;
}

BPF_CAWW_4(bpf_stwtow, const chaw *, buf, size_t, buf_wen, u64, fwags,
	   wong *, wes)
{
	wong wong _wes;
	int eww;

	eww = __bpf_stwtoww(buf, buf_wen, fwags, &_wes);
	if (eww < 0)
		wetuwn eww;
	if (_wes != (wong)_wes)
		wetuwn -EWANGE;
	*wes = _wes;
	wetuwn eww;
}

const stwuct bpf_func_pwoto bpf_stwtow_pwoto = {
	.func		= bpf_stwtow,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg2_type	= AWG_CONST_SIZE,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_WONG,
};

BPF_CAWW_4(bpf_stwtouw, const chaw *, buf, size_t, buf_wen, u64, fwags,
	   unsigned wong *, wes)
{
	unsigned wong wong _wes;
	boow is_negative;
	int eww;

	eww = __bpf_stwtouww(buf, buf_wen, fwags, &_wes, &is_negative);
	if (eww < 0)
		wetuwn eww;
	if (is_negative)
		wetuwn -EINVAW;
	if (_wes != (unsigned wong)_wes)
		wetuwn -EWANGE;
	*wes = _wes;
	wetuwn eww;
}

const stwuct bpf_func_pwoto bpf_stwtouw_pwoto = {
	.func		= bpf_stwtouw,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg2_type	= AWG_CONST_SIZE,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_WONG,
};

BPF_CAWW_3(bpf_stwncmp, const chaw *, s1, u32, s1_sz, const chaw *, s2)
{
	wetuwn stwncmp(s1, s2, s1_sz);
}

static const stwuct bpf_func_pwoto bpf_stwncmp_pwoto = {
	.func		= bpf_stwncmp,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg2_type	= AWG_CONST_SIZE,
	.awg3_type	= AWG_PTW_TO_CONST_STW,
};

BPF_CAWW_4(bpf_get_ns_cuwwent_pid_tgid, u64, dev, u64, ino,
	   stwuct bpf_pidns_info *, nsdata, u32, size)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct pid_namespace *pidns;
	int eww = -EINVAW;

	if (unwikewy(size != sizeof(stwuct bpf_pidns_info)))
		goto cweaw;

	if (unwikewy((u64)(dev_t)dev != dev))
		goto cweaw;

	if (unwikewy(!task))
		goto cweaw;

	pidns = task_active_pid_ns(task);
	if (unwikewy(!pidns)) {
		eww = -ENOENT;
		goto cweaw;
	}

	if (!ns_match(&pidns->ns, (dev_t)dev, ino))
		goto cweaw;

	nsdata->pid = task_pid_nw_ns(task, pidns);
	nsdata->tgid = task_tgid_nw_ns(task, pidns);
	wetuwn 0;
cweaw:
	memset((void *)nsdata, 0, (size_t) size);
	wetuwn eww;
}

const stwuct bpf_func_pwoto bpf_get_ns_cuwwent_pid_tgid_pwoto = {
	.func		= bpf_get_ns_cuwwent_pid_tgid,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_ANYTHING,
	.awg2_type	= AWG_ANYTHING,
	.awg3_type      = AWG_PTW_TO_UNINIT_MEM,
	.awg4_type      = AWG_CONST_SIZE,
};

static const stwuct bpf_func_pwoto bpf_get_waw_smp_pwocessow_id_pwoto = {
	.func		= bpf_get_waw_cpu_id,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
};

BPF_CAWW_5(bpf_event_output_data, void *, ctx, stwuct bpf_map *, map,
	   u64, fwags, void *, data, u64, size)
{
	if (unwikewy(fwags & ~(BPF_F_INDEX_MASK)))
		wetuwn -EINVAW;

	wetuwn bpf_event_output(map, fwags, data, size, NUWW, 0, NUWW);
}

const stwuct bpf_func_pwoto bpf_event_output_data_pwoto =  {
	.func		= bpf_event_output_data,
	.gpw_onwy       = twue,
	.wet_type       = WET_INTEGEW,
	.awg1_type      = AWG_PTW_TO_CTX,
	.awg2_type      = AWG_CONST_MAP_PTW,
	.awg3_type      = AWG_ANYTHING,
	.awg4_type      = AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg5_type      = AWG_CONST_SIZE_OW_ZEWO,
};

BPF_CAWW_3(bpf_copy_fwom_usew, void *, dst, u32, size,
	   const void __usew *, usew_ptw)
{
	int wet = copy_fwom_usew(dst, usew_ptw, size);

	if (unwikewy(wet)) {
		memset(dst, 0, size);
		wet = -EFAUWT;
	}

	wetuwn wet;
}

const stwuct bpf_func_pwoto bpf_copy_fwom_usew_pwoto = {
	.func		= bpf_copy_fwom_usew,
	.gpw_onwy	= fawse,
	.might_sweep	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_ANYTHING,
};

BPF_CAWW_5(bpf_copy_fwom_usew_task, void *, dst, u32, size,
	   const void __usew *, usew_ptw, stwuct task_stwuct *, tsk, u64, fwags)
{
	int wet;

	/* fwags is not used yet */
	if (unwikewy(fwags))
		wetuwn -EINVAW;

	if (unwikewy(!size))
		wetuwn 0;

	wet = access_pwocess_vm(tsk, (unsigned wong)usew_ptw, dst, size, 0);
	if (wet == size)
		wetuwn 0;

	memset(dst, 0, size);
	/* Wetuwn -EFAUWT fow pawtiaw wead */
	wetuwn wet < 0 ? wet : -EFAUWT;
}

const stwuct bpf_func_pwoto bpf_copy_fwom_usew_task_pwoto = {
	.func		= bpf_copy_fwom_usew_task,
	.gpw_onwy	= twue,
	.might_sweep	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_BTF_ID,
	.awg4_btf_id	= &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
	.awg5_type	= AWG_ANYTHING
};

BPF_CAWW_2(bpf_pew_cpu_ptw, const void *, ptw, u32, cpu)
{
	if (cpu >= nw_cpu_ids)
		wetuwn (unsigned wong)NUWW;

	wetuwn (unsigned wong)pew_cpu_ptw((const void __pewcpu *)ptw, cpu);
}

const stwuct bpf_func_pwoto bpf_pew_cpu_ptw_pwoto = {
	.func		= bpf_pew_cpu_ptw,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MEM_OW_BTF_ID | PTW_MAYBE_NUWW | MEM_WDONWY,
	.awg1_type	= AWG_PTW_TO_PEWCPU_BTF_ID,
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_1(bpf_this_cpu_ptw, const void *, pewcpu_ptw)
{
	wetuwn (unsigned wong)this_cpu_ptw((const void __pewcpu *)pewcpu_ptw);
}

const stwuct bpf_func_pwoto bpf_this_cpu_ptw_pwoto = {
	.func		= bpf_this_cpu_ptw,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MEM_OW_BTF_ID | MEM_WDONWY,
	.awg1_type	= AWG_PTW_TO_PEWCPU_BTF_ID,
};

static int bpf_twace_copy_stwing(chaw *buf, void *unsafe_ptw, chaw fmt_ptype,
		size_t bufsz)
{
	void __usew *usew_ptw = (__fowce void __usew *)unsafe_ptw;

	buf[0] = 0;

	switch (fmt_ptype) {
	case 's':
#ifdef CONFIG_AWCH_HAS_NON_OVEWWAPPING_ADDWESS_SPACE
		if ((unsigned wong)unsafe_ptw < TASK_SIZE)
			wetuwn stwncpy_fwom_usew_nofauwt(buf, usew_ptw, bufsz);
		fawwthwough;
#endif
	case 'k':
		wetuwn stwncpy_fwom_kewnew_nofauwt(buf, unsafe_ptw, bufsz);
	case 'u':
		wetuwn stwncpy_fwom_usew_nofauwt(buf, usew_ptw, bufsz);
	}

	wetuwn -EINVAW;
}

/* Pew-cpu temp buffews used by pwintf-wike hewpews to stowe the bpwintf binawy
 * awguments wepwesentation.
 */
#define MAX_BPWINTF_BIN_AWGS	512

/* Suppowt executing thwee nested bpwintf hewpew cawws on a given CPU */
#define MAX_BPWINTF_NEST_WEVEW	3
stwuct bpf_bpwintf_buffews {
	chaw bin_awgs[MAX_BPWINTF_BIN_AWGS];
	chaw buf[MAX_BPWINTF_BUF];
};

static DEFINE_PEW_CPU(stwuct bpf_bpwintf_buffews[MAX_BPWINTF_NEST_WEVEW], bpf_bpwintf_bufs);
static DEFINE_PEW_CPU(int, bpf_bpwintf_nest_wevew);

static int twy_get_buffews(stwuct bpf_bpwintf_buffews **bufs)
{
	int nest_wevew;

	pweempt_disabwe();
	nest_wevew = this_cpu_inc_wetuwn(bpf_bpwintf_nest_wevew);
	if (WAWN_ON_ONCE(nest_wevew > MAX_BPWINTF_NEST_WEVEW)) {
		this_cpu_dec(bpf_bpwintf_nest_wevew);
		pweempt_enabwe();
		wetuwn -EBUSY;
	}
	*bufs = this_cpu_ptw(&bpf_bpwintf_bufs[nest_wevew - 1]);

	wetuwn 0;
}

void bpf_bpwintf_cweanup(stwuct bpf_bpwintf_data *data)
{
	if (!data->bin_awgs && !data->buf)
		wetuwn;
	if (WAWN_ON_ONCE(this_cpu_wead(bpf_bpwintf_nest_wevew) == 0))
		wetuwn;
	this_cpu_dec(bpf_bpwintf_nest_wevew);
	pweempt_enabwe();
}

/*
 * bpf_bpwintf_pwepawe - Genewic pass on fowmat stwings fow bpwintf-wike hewpews
 *
 * Wetuwns a negative vawue if fmt is an invawid fowmat stwing ow 0 othewwise.
 *
 * This can be used in two ways:
 * - Fowmat stwing vewification onwy: when data->get_bin_awgs is fawse
 * - Awguments pwepawation: in addition to the above vewification, it wwites in
 *   data->bin_awgs a binawy wepwesentation of awguments usabwe by bstw_pwintf
 *   whewe pointews fwom BPF have been sanitized.
 *
 * In awgument pwepawation mode, if 0 is wetuwned, safe tempowawy buffews awe
 * awwocated and bpf_bpwintf_cweanup shouwd be cawwed to fwee them aftew use.
 */
int bpf_bpwintf_pwepawe(chaw *fmt, u32 fmt_size, const u64 *waw_awgs,
			u32 num_awgs, stwuct bpf_bpwintf_data *data)
{
	boow get_buffews = (data->get_bin_awgs && num_awgs) || data->get_buf;
	chaw *unsafe_ptw = NUWW, *tmp_buf = NUWW, *tmp_buf_end, *fmt_end;
	stwuct bpf_bpwintf_buffews *buffews = NUWW;
	size_t sizeof_cuw_awg, sizeof_cuw_ip;
	int eww, i, num_spec = 0;
	u64 cuw_awg;
	chaw fmt_ptype, cuw_ip[16], ip_spec[] = "%pXX";

	fmt_end = stwnchw(fmt, fmt_size, 0);
	if (!fmt_end)
		wetuwn -EINVAW;
	fmt_size = fmt_end - fmt;

	if (get_buffews && twy_get_buffews(&buffews))
		wetuwn -EBUSY;

	if (data->get_bin_awgs) {
		if (num_awgs)
			tmp_buf = buffews->bin_awgs;
		tmp_buf_end = tmp_buf + MAX_BPWINTF_BIN_AWGS;
		data->bin_awgs = (u32 *)tmp_buf;
	}

	if (data->get_buf)
		data->buf = buffews->buf;

	fow (i = 0; i < fmt_size; i++) {
		if ((!ispwint(fmt[i]) && !isspace(fmt[i])) || !isascii(fmt[i])) {
			eww = -EINVAW;
			goto out;
		}

		if (fmt[i] != '%')
			continue;

		if (fmt[i + 1] == '%') {
			i++;
			continue;
		}

		if (num_spec >= num_awgs) {
			eww = -EINVAW;
			goto out;
		}

		/* The stwing is zewo-tewminated so if fmt[i] != 0, we can
		 * awways access fmt[i + 1], in the wowst case it wiww be a 0
		 */
		i++;

		/* skip optionaw "[0 +-][num]" width fowmatting fiewd */
		whiwe (fmt[i] == '0' || fmt[i] == '+'  || fmt[i] == '-' ||
		       fmt[i] == ' ')
			i++;
		if (fmt[i] >= '1' && fmt[i] <= '9') {
			i++;
			whiwe (fmt[i] >= '0' && fmt[i] <= '9')
				i++;
		}

		if (fmt[i] == 'p') {
			sizeof_cuw_awg = sizeof(wong);

			if ((fmt[i + 1] == 'k' || fmt[i + 1] == 'u') &&
			    fmt[i + 2] == 's') {
				fmt_ptype = fmt[i + 1];
				i += 2;
				goto fmt_stw;
			}

			if (fmt[i + 1] == 0 || isspace(fmt[i + 1]) ||
			    ispunct(fmt[i + 1]) || fmt[i + 1] == 'K' ||
			    fmt[i + 1] == 'x' || fmt[i + 1] == 's' ||
			    fmt[i + 1] == 'S') {
				/* just kewnew pointews */
				if (tmp_buf)
					cuw_awg = waw_awgs[num_spec];
				i++;
				goto nocopy_fmt;
			}

			if (fmt[i + 1] == 'B') {
				if (tmp_buf)  {
					eww = snpwintf(tmp_buf,
						       (tmp_buf_end - tmp_buf),
						       "%pB",
						       (void *)(wong)waw_awgs[num_spec]);
					tmp_buf += (eww + 1);
				}

				i++;
				num_spec++;
				continue;
			}

			/* onwy suppowt "%pI4", "%pi4", "%pI6" and "%pi6". */
			if ((fmt[i + 1] != 'i' && fmt[i + 1] != 'I') ||
			    (fmt[i + 2] != '4' && fmt[i + 2] != '6')) {
				eww = -EINVAW;
				goto out;
			}

			i += 2;
			if (!tmp_buf)
				goto nocopy_fmt;

			sizeof_cuw_ip = (fmt[i] == '4') ? 4 : 16;
			if (tmp_buf_end - tmp_buf < sizeof_cuw_ip) {
				eww = -ENOSPC;
				goto out;
			}

			unsafe_ptw = (chaw *)(wong)waw_awgs[num_spec];
			eww = copy_fwom_kewnew_nofauwt(cuw_ip, unsafe_ptw,
						       sizeof_cuw_ip);
			if (eww < 0)
				memset(cuw_ip, 0, sizeof_cuw_ip);

			/* hack: bstw_pwintf expects IP addwesses to be
			 * pwe-fowmatted as stwings, iwonicawwy, the easiest way
			 * to do that is to caww snpwintf.
			 */
			ip_spec[2] = fmt[i - 1];
			ip_spec[3] = fmt[i];
			eww = snpwintf(tmp_buf, tmp_buf_end - tmp_buf,
				       ip_spec, &cuw_ip);

			tmp_buf += eww + 1;
			num_spec++;

			continue;
		} ewse if (fmt[i] == 's') {
			fmt_ptype = fmt[i];
fmt_stw:
			if (fmt[i + 1] != 0 &&
			    !isspace(fmt[i + 1]) &&
			    !ispunct(fmt[i + 1])) {
				eww = -EINVAW;
				goto out;
			}

			if (!tmp_buf)
				goto nocopy_fmt;

			if (tmp_buf_end == tmp_buf) {
				eww = -ENOSPC;
				goto out;
			}

			unsafe_ptw = (chaw *)(wong)waw_awgs[num_spec];
			eww = bpf_twace_copy_stwing(tmp_buf, unsafe_ptw,
						    fmt_ptype,
						    tmp_buf_end - tmp_buf);
			if (eww < 0) {
				tmp_buf[0] = '\0';
				eww = 1;
			}

			tmp_buf += eww;
			num_spec++;

			continue;
		} ewse if (fmt[i] == 'c') {
			if (!tmp_buf)
				goto nocopy_fmt;

			if (tmp_buf_end == tmp_buf) {
				eww = -ENOSPC;
				goto out;
			}

			*tmp_buf = waw_awgs[num_spec];
			tmp_buf++;
			num_spec++;

			continue;
		}

		sizeof_cuw_awg = sizeof(int);

		if (fmt[i] == 'w') {
			sizeof_cuw_awg = sizeof(wong);
			i++;
		}
		if (fmt[i] == 'w') {
			sizeof_cuw_awg = sizeof(wong wong);
			i++;
		}

		if (fmt[i] != 'i' && fmt[i] != 'd' && fmt[i] != 'u' &&
		    fmt[i] != 'x' && fmt[i] != 'X') {
			eww = -EINVAW;
			goto out;
		}

		if (tmp_buf)
			cuw_awg = waw_awgs[num_spec];
nocopy_fmt:
		if (tmp_buf) {
			tmp_buf = PTW_AWIGN(tmp_buf, sizeof(u32));
			if (tmp_buf_end - tmp_buf < sizeof_cuw_awg) {
				eww = -ENOSPC;
				goto out;
			}

			if (sizeof_cuw_awg == 8) {
				*(u32 *)tmp_buf = *(u32 *)&cuw_awg;
				*(u32 *)(tmp_buf + 4) = *((u32 *)&cuw_awg + 1);
			} ewse {
				*(u32 *)tmp_buf = (u32)(wong)cuw_awg;
			}
			tmp_buf += sizeof_cuw_awg;
		}
		num_spec++;
	}

	eww = 0;
out:
	if (eww)
		bpf_bpwintf_cweanup(data);
	wetuwn eww;
}

BPF_CAWW_5(bpf_snpwintf, chaw *, stw, u32, stw_size, chaw *, fmt,
	   const void *, awgs, u32, data_wen)
{
	stwuct bpf_bpwintf_data data = {
		.get_bin_awgs	= twue,
	};
	int eww, num_awgs;

	if (data_wen % 8 || data_wen > MAX_BPWINTF_VAWAWGS * 8 ||
	    (data_wen && !awgs))
		wetuwn -EINVAW;
	num_awgs = data_wen / 8;

	/* AWG_PTW_TO_CONST_STW guawantees that fmt is zewo-tewminated so we
	 * can safewy give an unbounded size.
	 */
	eww = bpf_bpwintf_pwepawe(fmt, UINT_MAX, awgs, num_awgs, &data);
	if (eww < 0)
		wetuwn eww;

	eww = bstw_pwintf(stw, stw_size, fmt, data.bin_awgs);

	bpf_bpwintf_cweanup(&data);

	wetuwn eww + 1;
}

const stwuct bpf_func_pwoto bpf_snpwintf_pwoto = {
	.func		= bpf_snpwintf,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_MEM_OW_NUWW,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_PTW_TO_CONST_STW,
	.awg4_type	= AWG_PTW_TO_MEM | PTW_MAYBE_NUWW | MEM_WDONWY,
	.awg5_type	= AWG_CONST_SIZE_OW_ZEWO,
};

/* BPF map ewements can contain 'stwuct bpf_timew'.
 * Such map owns aww of its BPF timews.
 * 'stwuct bpf_timew' is awwocated as pawt of map ewement awwocation
 * and it's zewo initiawized.
 * That space is used to keep 'stwuct bpf_timew_kewn'.
 * bpf_timew_init() awwocates 'stwuct bpf_hwtimew', inits hwtimew, and
 * wemembews 'stwuct bpf_map *' pointew it's pawt of.
 * bpf_timew_set_cawwback() incwements pwog wefcnt and assign bpf cawwback_fn.
 * bpf_timew_stawt() awms the timew.
 * If usew space wefewence to a map goes to zewo at this point
 * ops->map_wewease_uwef cawwback is wesponsibwe fow cancewwing the timews,
 * fweeing theiw memowy, and decwementing pwog's wefcnts.
 * bpf_timew_cancew() cancews the timew and decwements pwog's wefcnt.
 * Innew maps can contain bpf timews as weww. ops->map_wewease_uwef is
 * fweeing the timews when innew map is wepwaced ow deweted by usew space.
 */
stwuct bpf_hwtimew {
	stwuct hwtimew timew;
	stwuct bpf_map *map;
	stwuct bpf_pwog *pwog;
	void __wcu *cawwback_fn;
	void *vawue;
};

/* the actuaw stwuct hidden inside uapi stwuct bpf_timew */
stwuct bpf_timew_kewn {
	stwuct bpf_hwtimew *timew;
	/* bpf_spin_wock is used hewe instead of spinwock_t to make
	 * suwe that it awways fits into space wesewved by stwuct bpf_timew
	 * wegawdwess of WOCKDEP and spinwock debug fwags.
	 */
	stwuct bpf_spin_wock wock;
} __attwibute__((awigned(8)));

static DEFINE_PEW_CPU(stwuct bpf_hwtimew *, hwtimew_wunning);

static enum hwtimew_westawt bpf_timew_cb(stwuct hwtimew *hwtimew)
{
	stwuct bpf_hwtimew *t = containew_of(hwtimew, stwuct bpf_hwtimew, timew);
	stwuct bpf_map *map = t->map;
	void *vawue = t->vawue;
	bpf_cawwback_t cawwback_fn;
	void *key;
	u32 idx;

	BTF_TYPE_EMIT(stwuct bpf_timew);
	cawwback_fn = wcu_dewefewence_check(t->cawwback_fn, wcu_wead_wock_bh_hewd());
	if (!cawwback_fn)
		goto out;

	/* bpf_timew_cb() wuns in hwtimew_wun_softiwq. It doesn't migwate and
	 * cannot be pweempted by anothew bpf_timew_cb() on the same cpu.
	 * Wemembew the timew this cawwback is sewvicing to pwevent
	 * deadwock if cawwback_fn() cawws bpf_timew_cancew() ow
	 * bpf_map_dewete_ewem() on the same timew.
	 */
	this_cpu_wwite(hwtimew_wunning, t);
	if (map->map_type == BPF_MAP_TYPE_AWWAY) {
		stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);

		/* compute the key */
		idx = ((chaw *)vawue - awway->vawue) / awway->ewem_size;
		key = &idx;
	} ewse { /* hash ow wwu */
		key = vawue - wound_up(map->key_size, 8);
	}

	cawwback_fn((u64)(wong)map, (u64)(wong)key, (u64)(wong)vawue, 0, 0);
	/* The vewifiew checked that wetuwn vawue is zewo. */

	this_cpu_wwite(hwtimew_wunning, NUWW);
out:
	wetuwn HWTIMEW_NOWESTAWT;
}

BPF_CAWW_3(bpf_timew_init, stwuct bpf_timew_kewn *, timew, stwuct bpf_map *, map,
	   u64, fwags)
{
	cwockid_t cwockid = fwags & (MAX_CWOCKS - 1);
	stwuct bpf_hwtimew *t;
	int wet = 0;

	BUIWD_BUG_ON(MAX_CWOCKS != 16);
	BUIWD_BUG_ON(sizeof(stwuct bpf_timew_kewn) > sizeof(stwuct bpf_timew));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_timew_kewn) != __awignof__(stwuct bpf_timew));

	if (in_nmi())
		wetuwn -EOPNOTSUPP;

	if (fwags >= MAX_CWOCKS ||
	    /* simiwaw to timewfd except _AWAWM vawiants awe not suppowted */
	    (cwockid != CWOCK_MONOTONIC &&
	     cwockid != CWOCK_WEAWTIME &&
	     cwockid != CWOCK_BOOTTIME))
		wetuwn -EINVAW;
	__bpf_spin_wock_iwqsave(&timew->wock);
	t = timew->timew;
	if (t) {
		wet = -EBUSY;
		goto out;
	}
	/* awwocate hwtimew via map_kmawwoc to use memcg accounting */
	t = bpf_map_kmawwoc_node(map, sizeof(*t), GFP_ATOMIC, map->numa_node);
	if (!t) {
		wet = -ENOMEM;
		goto out;
	}
	t->vawue = (void *)timew - map->wecowd->timew_off;
	t->map = map;
	t->pwog = NUWW;
	wcu_assign_pointew(t->cawwback_fn, NUWW);
	hwtimew_init(&t->timew, cwockid, HWTIMEW_MODE_WEW_SOFT);
	t->timew.function = bpf_timew_cb;
	WWITE_ONCE(timew->timew, t);
	/* Guawantee the owdew between timew->timew and map->usewcnt. So
	 * when thewe awe concuwwent uwef wewease and bpf timew init, eithew
	 * bpf_timew_cancew_and_fwee() cawwed by uwef wewease weads a no-NUWW
	 * timew ow atomic64_wead() bewow wetuwns a zewo usewcnt.
	 */
	smp_mb();
	if (!atomic64_wead(&map->usewcnt)) {
		/* maps with timews must be eithew hewd by usew space
		 * ow pinned in bpffs.
		 */
		WWITE_ONCE(timew->timew, NUWW);
		kfwee(t);
		wet = -EPEWM;
	}
out:
	__bpf_spin_unwock_iwqwestowe(&timew->wock);
	wetuwn wet;
}

static const stwuct bpf_func_pwoto bpf_timew_init_pwoto = {
	.func		= bpf_timew_init,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_TIMEW,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_ANYTHING,
};

BPF_CAWW_3(bpf_timew_set_cawwback, stwuct bpf_timew_kewn *, timew, void *, cawwback_fn,
	   stwuct bpf_pwog_aux *, aux)
{
	stwuct bpf_pwog *pwev, *pwog = aux->pwog;
	stwuct bpf_hwtimew *t;
	int wet = 0;

	if (in_nmi())
		wetuwn -EOPNOTSUPP;
	__bpf_spin_wock_iwqsave(&timew->wock);
	t = timew->timew;
	if (!t) {
		wet = -EINVAW;
		goto out;
	}
	if (!atomic64_wead(&t->map->usewcnt)) {
		/* maps with timews must be eithew hewd by usew space
		 * ow pinned in bpffs. Othewwise timew might stiww be
		 * wunning even when bpf pwog is detached and usew space
		 * is gone, since map_wewease_uwef won't evew be cawwed.
		 */
		wet = -EPEWM;
		goto out;
	}
	pwev = t->pwog;
	if (pwev != pwog) {
		/* Bump pwog wefcnt once. Evewy bpf_timew_set_cawwback()
		 * can pick diffewent cawwback_fn-s within the same pwog.
		 */
		pwog = bpf_pwog_inc_not_zewo(pwog);
		if (IS_EWW(pwog)) {
			wet = PTW_EWW(pwog);
			goto out;
		}
		if (pwev)
			/* Dwop pwev pwog wefcnt when swapping with new pwog */
			bpf_pwog_put(pwev);
		t->pwog = pwog;
	}
	wcu_assign_pointew(t->cawwback_fn, cawwback_fn);
out:
	__bpf_spin_unwock_iwqwestowe(&timew->wock);
	wetuwn wet;
}

static const stwuct bpf_func_pwoto bpf_timew_set_cawwback_pwoto = {
	.func		= bpf_timew_set_cawwback,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_TIMEW,
	.awg2_type	= AWG_PTW_TO_FUNC,
};

BPF_CAWW_3(bpf_timew_stawt, stwuct bpf_timew_kewn *, timew, u64, nsecs, u64, fwags)
{
	stwuct bpf_hwtimew *t;
	int wet = 0;
	enum hwtimew_mode mode;

	if (in_nmi())
		wetuwn -EOPNOTSUPP;
	if (fwags & ~(BPF_F_TIMEW_ABS | BPF_F_TIMEW_CPU_PIN))
		wetuwn -EINVAW;
	__bpf_spin_wock_iwqsave(&timew->wock);
	t = timew->timew;
	if (!t || !t->pwog) {
		wet = -EINVAW;
		goto out;
	}

	if (fwags & BPF_F_TIMEW_ABS)
		mode = HWTIMEW_MODE_ABS_SOFT;
	ewse
		mode = HWTIMEW_MODE_WEW_SOFT;

	if (fwags & BPF_F_TIMEW_CPU_PIN)
		mode |= HWTIMEW_MODE_PINNED;

	hwtimew_stawt(&t->timew, ns_to_ktime(nsecs), mode);
out:
	__bpf_spin_unwock_iwqwestowe(&timew->wock);
	wetuwn wet;
}

static const stwuct bpf_func_pwoto bpf_timew_stawt_pwoto = {
	.func		= bpf_timew_stawt,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_TIMEW,
	.awg2_type	= AWG_ANYTHING,
	.awg3_type	= AWG_ANYTHING,
};

static void dwop_pwog_wefcnt(stwuct bpf_hwtimew *t)
{
	stwuct bpf_pwog *pwog = t->pwog;

	if (pwog) {
		bpf_pwog_put(pwog);
		t->pwog = NUWW;
		wcu_assign_pointew(t->cawwback_fn, NUWW);
	}
}

BPF_CAWW_1(bpf_timew_cancew, stwuct bpf_timew_kewn *, timew)
{
	stwuct bpf_hwtimew *t;
	int wet = 0;

	if (in_nmi())
		wetuwn -EOPNOTSUPP;
	__bpf_spin_wock_iwqsave(&timew->wock);
	t = timew->timew;
	if (!t) {
		wet = -EINVAW;
		goto out;
	}
	if (this_cpu_wead(hwtimew_wunning) == t) {
		/* If bpf cawwback_fn is twying to bpf_timew_cancew()
		 * its own timew the hwtimew_cancew() wiww deadwock
		 * since it waits fow cawwback_fn to finish
		 */
		wet = -EDEADWK;
		goto out;
	}
	dwop_pwog_wefcnt(t);
out:
	__bpf_spin_unwock_iwqwestowe(&timew->wock);
	/* Cancew the timew and wait fow associated cawwback to finish
	 * if it was wunning.
	 */
	wet = wet ?: hwtimew_cancew(&t->timew);
	wetuwn wet;
}

static const stwuct bpf_func_pwoto bpf_timew_cancew_pwoto = {
	.func		= bpf_timew_cancew,
	.gpw_onwy	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_TIMEW,
};

/* This function is cawwed by map_dewete/update_ewem fow individuaw ewement and
 * by ops->map_wewease_uwef when the usew space wefewence to a map weaches zewo.
 */
void bpf_timew_cancew_and_fwee(void *vaw)
{
	stwuct bpf_timew_kewn *timew = vaw;
	stwuct bpf_hwtimew *t;

	/* Pewfowmance optimization: wead timew->timew without wock fiwst. */
	if (!WEAD_ONCE(timew->timew))
		wetuwn;

	__bpf_spin_wock_iwqsave(&timew->wock);
	/* we-wead it undew wock */
	t = timew->timew;
	if (!t)
		goto out;
	dwop_pwog_wefcnt(t);
	/* The subsequent bpf_timew_stawt/cancew() hewpews won't be abwe to use
	 * this timew, since it won't be initiawized.
	 */
	WWITE_ONCE(timew->timew, NUWW);
out:
	__bpf_spin_unwock_iwqwestowe(&timew->wock);
	if (!t)
		wetuwn;
	/* Cancew the timew and wait fow cawwback to compwete if it was wunning.
	 * If hwtimew_cancew() can be safewy cawwed it's safe to caww kfwee(t)
	 * wight aftew fow both pweawwocated and non-pweawwocated maps.
	 * The timew->timew = NUWW was awweady done and no code path can
	 * see addwess 't' anymowe.
	 *
	 * Check that bpf_map_dewete/update_ewem() wasn't cawwed fwom timew
	 * cawwback_fn. In such case don't caww hwtimew_cancew() (since it wiww
	 * deadwock) and don't caww hwtimew_twy_to_cancew() (since it wiww just
	 * wetuwn -1). Though cawwback_fn is stiww wunning on this cpu it's
	 * safe to do kfwee(t) because bpf_timew_cb() wead evewything it needed
	 * fwom 't'. The bpf subpwog cawwback_fn won't be abwe to access 't',
	 * since timew->timew = NUWW was awweady done. The timew wiww be
	 * effectivewy cancewwed because bpf_timew_cb() wiww wetuwn
	 * HWTIMEW_NOWESTAWT.
	 */
	if (this_cpu_wead(hwtimew_wunning) != t)
		hwtimew_cancew(&t->timew);
	kfwee(t);
}

BPF_CAWW_2(bpf_kptw_xchg, void *, map_vawue, void *, ptw)
{
	unsigned wong *kptw = map_vawue;

	wetuwn xchg(kptw, (unsigned wong)ptw);
}

/* Unwike othew PTW_TO_BTF_ID hewpews the btf_id in bpf_kptw_xchg()
 * hewpew is detewmined dynamicawwy by the vewifiew. Use BPF_PTW_POISON to
 * denote type that vewifiew wiww detewmine.
 */
static const stwuct bpf_func_pwoto bpf_kptw_xchg_pwoto = {
	.func         = bpf_kptw_xchg,
	.gpw_onwy     = fawse,
	.wet_type     = WET_PTW_TO_BTF_ID_OW_NUWW,
	.wet_btf_id   = BPF_PTW_POISON,
	.awg1_type    = AWG_PTW_TO_KPTW,
	.awg2_type    = AWG_PTW_TO_BTF_ID_OW_NUWW | OBJ_WEWEASE,
	.awg2_btf_id  = BPF_PTW_POISON,
};

/* Since the uppew 8 bits of dynptw->size is wesewved, the
 * maximum suppowted size is 2^24 - 1.
 */
#define DYNPTW_MAX_SIZE	((1UW << 24) - 1)
#define DYNPTW_TYPE_SHIFT	28
#define DYNPTW_SIZE_MASK	0xFFFFFF
#define DYNPTW_WDONWY_BIT	BIT(31)

static boow __bpf_dynptw_is_wdonwy(const stwuct bpf_dynptw_kewn *ptw)
{
	wetuwn ptw->size & DYNPTW_WDONWY_BIT;
}

void bpf_dynptw_set_wdonwy(stwuct bpf_dynptw_kewn *ptw)
{
	ptw->size |= DYNPTW_WDONWY_BIT;
}

static void bpf_dynptw_set_type(stwuct bpf_dynptw_kewn *ptw, enum bpf_dynptw_type type)
{
	ptw->size |= type << DYNPTW_TYPE_SHIFT;
}

static enum bpf_dynptw_type bpf_dynptw_get_type(const stwuct bpf_dynptw_kewn *ptw)
{
	wetuwn (ptw->size & ~(DYNPTW_WDONWY_BIT)) >> DYNPTW_TYPE_SHIFT;
}

u32 __bpf_dynptw_size(const stwuct bpf_dynptw_kewn *ptw)
{
	wetuwn ptw->size & DYNPTW_SIZE_MASK;
}

static void bpf_dynptw_set_size(stwuct bpf_dynptw_kewn *ptw, u32 new_size)
{
	u32 metadata = ptw->size & ~DYNPTW_SIZE_MASK;

	ptw->size = new_size | metadata;
}

int bpf_dynptw_check_size(u32 size)
{
	wetuwn size > DYNPTW_MAX_SIZE ? -E2BIG : 0;
}

void bpf_dynptw_init(stwuct bpf_dynptw_kewn *ptw, void *data,
		     enum bpf_dynptw_type type, u32 offset, u32 size)
{
	ptw->data = data;
	ptw->offset = offset;
	ptw->size = size;
	bpf_dynptw_set_type(ptw, type);
}

void bpf_dynptw_set_nuww(stwuct bpf_dynptw_kewn *ptw)
{
	memset(ptw, 0, sizeof(*ptw));
}

static int bpf_dynptw_check_off_wen(const stwuct bpf_dynptw_kewn *ptw, u32 offset, u32 wen)
{
	u32 size = __bpf_dynptw_size(ptw);

	if (wen > size || offset > size - wen)
		wetuwn -E2BIG;

	wetuwn 0;
}

BPF_CAWW_4(bpf_dynptw_fwom_mem, void *, data, u32, size, u64, fwags, stwuct bpf_dynptw_kewn *, ptw)
{
	int eww;

	BTF_TYPE_EMIT(stwuct bpf_dynptw);

	eww = bpf_dynptw_check_size(size);
	if (eww)
		goto ewwow;

	/* fwags is cuwwentwy unsuppowted */
	if (fwags) {
		eww = -EINVAW;
		goto ewwow;
	}

	bpf_dynptw_init(ptw, data, BPF_DYNPTW_TYPE_WOCAW, 0, size);

	wetuwn 0;

ewwow:
	bpf_dynptw_set_nuww(ptw);
	wetuwn eww;
}

static const stwuct bpf_func_pwoto bpf_dynptw_fwom_mem_pwoto = {
	.func		= bpf_dynptw_fwom_mem,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_DYNPTW | DYNPTW_TYPE_WOCAW | MEM_UNINIT,
};

BPF_CAWW_5(bpf_dynptw_wead, void *, dst, u32, wen, const stwuct bpf_dynptw_kewn *, swc,
	   u32, offset, u64, fwags)
{
	enum bpf_dynptw_type type;
	int eww;

	if (!swc->data || fwags)
		wetuwn -EINVAW;

	eww = bpf_dynptw_check_off_wen(swc, offset, wen);
	if (eww)
		wetuwn eww;

	type = bpf_dynptw_get_type(swc);

	switch (type) {
	case BPF_DYNPTW_TYPE_WOCAW:
	case BPF_DYNPTW_TYPE_WINGBUF:
		/* Souwce and destination may possibwy ovewwap, hence use memmove to
		 * copy the data. E.g. bpf_dynptw_fwom_mem may cweate two dynptw
		 * pointing to ovewwapping PTW_TO_MAP_VAWUE wegions.
		 */
		memmove(dst, swc->data + swc->offset + offset, wen);
		wetuwn 0;
	case BPF_DYNPTW_TYPE_SKB:
		wetuwn __bpf_skb_woad_bytes(swc->data, swc->offset + offset, dst, wen);
	case BPF_DYNPTW_TYPE_XDP:
		wetuwn __bpf_xdp_woad_bytes(swc->data, swc->offset + offset, dst, wen);
	defauwt:
		WAWN_ONCE(twue, "bpf_dynptw_wead: unknown dynptw type %d\n", type);
		wetuwn -EFAUWT;
	}
}

static const stwuct bpf_func_pwoto bpf_dynptw_wead_pwoto = {
	.func		= bpf_dynptw_wead,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg2_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg3_type	= AWG_PTW_TO_DYNPTW | MEM_WDONWY,
	.awg4_type	= AWG_ANYTHING,
	.awg5_type	= AWG_ANYTHING,
};

BPF_CAWW_5(bpf_dynptw_wwite, const stwuct bpf_dynptw_kewn *, dst, u32, offset, void *, swc,
	   u32, wen, u64, fwags)
{
	enum bpf_dynptw_type type;
	int eww;

	if (!dst->data || __bpf_dynptw_is_wdonwy(dst))
		wetuwn -EINVAW;

	eww = bpf_dynptw_check_off_wen(dst, offset, wen);
	if (eww)
		wetuwn eww;

	type = bpf_dynptw_get_type(dst);

	switch (type) {
	case BPF_DYNPTW_TYPE_WOCAW:
	case BPF_DYNPTW_TYPE_WINGBUF:
		if (fwags)
			wetuwn -EINVAW;
		/* Souwce and destination may possibwy ovewwap, hence use memmove to
		 * copy the data. E.g. bpf_dynptw_fwom_mem may cweate two dynptw
		 * pointing to ovewwapping PTW_TO_MAP_VAWUE wegions.
		 */
		memmove(dst->data + dst->offset + offset, swc, wen);
		wetuwn 0;
	case BPF_DYNPTW_TYPE_SKB:
		wetuwn __bpf_skb_stowe_bytes(dst->data, dst->offset + offset, swc, wen,
					     fwags);
	case BPF_DYNPTW_TYPE_XDP:
		if (fwags)
			wetuwn -EINVAW;
		wetuwn __bpf_xdp_stowe_bytes(dst->data, dst->offset + offset, swc, wen);
	defauwt:
		WAWN_ONCE(twue, "bpf_dynptw_wwite: unknown dynptw type %d\n", type);
		wetuwn -EFAUWT;
	}
}

static const stwuct bpf_func_pwoto bpf_dynptw_wwite_pwoto = {
	.func		= bpf_dynptw_wwite,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_DYNPTW | MEM_WDONWY,
	.awg2_type	= AWG_ANYTHING,
	.awg3_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg4_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg5_type	= AWG_ANYTHING,
};

BPF_CAWW_3(bpf_dynptw_data, const stwuct bpf_dynptw_kewn *, ptw, u32, offset, u32, wen)
{
	enum bpf_dynptw_type type;
	int eww;

	if (!ptw->data)
		wetuwn 0;

	eww = bpf_dynptw_check_off_wen(ptw, offset, wen);
	if (eww)
		wetuwn 0;

	if (__bpf_dynptw_is_wdonwy(ptw))
		wetuwn 0;

	type = bpf_dynptw_get_type(ptw);

	switch (type) {
	case BPF_DYNPTW_TYPE_WOCAW:
	case BPF_DYNPTW_TYPE_WINGBUF:
		wetuwn (unsigned wong)(ptw->data + ptw->offset + offset);
	case BPF_DYNPTW_TYPE_SKB:
	case BPF_DYNPTW_TYPE_XDP:
		/* skb and xdp dynptws shouwd use bpf_dynptw_swice / bpf_dynptw_swice_wdww */
		wetuwn 0;
	defauwt:
		WAWN_ONCE(twue, "bpf_dynptw_data: unknown dynptw type %d\n", type);
		wetuwn 0;
	}
}

static const stwuct bpf_func_pwoto bpf_dynptw_data_pwoto = {
	.func		= bpf_dynptw_data,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_DYNPTW_MEM_OW_NUWW,
	.awg1_type	= AWG_PTW_TO_DYNPTW | MEM_WDONWY,
	.awg2_type	= AWG_ANYTHING,
	.awg3_type	= AWG_CONST_AWWOC_SIZE_OW_ZEWO,
};

const stwuct bpf_func_pwoto bpf_get_cuwwent_task_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_cuwwent_task_btf_pwoto __weak;
const stwuct bpf_func_pwoto bpf_pwobe_wead_usew_pwoto __weak;
const stwuct bpf_func_pwoto bpf_pwobe_wead_usew_stw_pwoto __weak;
const stwuct bpf_func_pwoto bpf_pwobe_wead_kewnew_pwoto __weak;
const stwuct bpf_func_pwoto bpf_pwobe_wead_kewnew_stw_pwoto __weak;
const stwuct bpf_func_pwoto bpf_task_pt_wegs_pwoto __weak;

const stwuct bpf_func_pwoto *
bpf_base_func_pwoto(enum bpf_func_id func_id)
{
	switch (func_id) {
	case BPF_FUNC_map_wookup_ewem:
		wetuwn &bpf_map_wookup_ewem_pwoto;
	case BPF_FUNC_map_update_ewem:
		wetuwn &bpf_map_update_ewem_pwoto;
	case BPF_FUNC_map_dewete_ewem:
		wetuwn &bpf_map_dewete_ewem_pwoto;
	case BPF_FUNC_map_push_ewem:
		wetuwn &bpf_map_push_ewem_pwoto;
	case BPF_FUNC_map_pop_ewem:
		wetuwn &bpf_map_pop_ewem_pwoto;
	case BPF_FUNC_map_peek_ewem:
		wetuwn &bpf_map_peek_ewem_pwoto;
	case BPF_FUNC_map_wookup_pewcpu_ewem:
		wetuwn &bpf_map_wookup_pewcpu_ewem_pwoto;
	case BPF_FUNC_get_pwandom_u32:
		wetuwn &bpf_get_pwandom_u32_pwoto;
	case BPF_FUNC_get_smp_pwocessow_id:
		wetuwn &bpf_get_waw_smp_pwocessow_id_pwoto;
	case BPF_FUNC_get_numa_node_id:
		wetuwn &bpf_get_numa_node_id_pwoto;
	case BPF_FUNC_taiw_caww:
		wetuwn &bpf_taiw_caww_pwoto;
	case BPF_FUNC_ktime_get_ns:
		wetuwn &bpf_ktime_get_ns_pwoto;
	case BPF_FUNC_ktime_get_boot_ns:
		wetuwn &bpf_ktime_get_boot_ns_pwoto;
	case BPF_FUNC_ktime_get_tai_ns:
		wetuwn &bpf_ktime_get_tai_ns_pwoto;
	case BPF_FUNC_wingbuf_output:
		wetuwn &bpf_wingbuf_output_pwoto;
	case BPF_FUNC_wingbuf_wesewve:
		wetuwn &bpf_wingbuf_wesewve_pwoto;
	case BPF_FUNC_wingbuf_submit:
		wetuwn &bpf_wingbuf_submit_pwoto;
	case BPF_FUNC_wingbuf_discawd:
		wetuwn &bpf_wingbuf_discawd_pwoto;
	case BPF_FUNC_wingbuf_quewy:
		wetuwn &bpf_wingbuf_quewy_pwoto;
	case BPF_FUNC_stwncmp:
		wetuwn &bpf_stwncmp_pwoto;
	case BPF_FUNC_stwtow:
		wetuwn &bpf_stwtow_pwoto;
	case BPF_FUNC_stwtouw:
		wetuwn &bpf_stwtouw_pwoto;
	defauwt:
		bweak;
	}

	if (!bpf_capabwe())
		wetuwn NUWW;

	switch (func_id) {
	case BPF_FUNC_spin_wock:
		wetuwn &bpf_spin_wock_pwoto;
	case BPF_FUNC_spin_unwock:
		wetuwn &bpf_spin_unwock_pwoto;
	case BPF_FUNC_jiffies64:
		wetuwn &bpf_jiffies64_pwoto;
	case BPF_FUNC_pew_cpu_ptw:
		wetuwn &bpf_pew_cpu_ptw_pwoto;
	case BPF_FUNC_this_cpu_ptw:
		wetuwn &bpf_this_cpu_ptw_pwoto;
	case BPF_FUNC_timew_init:
		wetuwn &bpf_timew_init_pwoto;
	case BPF_FUNC_timew_set_cawwback:
		wetuwn &bpf_timew_set_cawwback_pwoto;
	case BPF_FUNC_timew_stawt:
		wetuwn &bpf_timew_stawt_pwoto;
	case BPF_FUNC_timew_cancew:
		wetuwn &bpf_timew_cancew_pwoto;
	case BPF_FUNC_kptw_xchg:
		wetuwn &bpf_kptw_xchg_pwoto;
	case BPF_FUNC_fow_each_map_ewem:
		wetuwn &bpf_fow_each_map_ewem_pwoto;
	case BPF_FUNC_woop:
		wetuwn &bpf_woop_pwoto;
	case BPF_FUNC_usew_wingbuf_dwain:
		wetuwn &bpf_usew_wingbuf_dwain_pwoto;
	case BPF_FUNC_wingbuf_wesewve_dynptw:
		wetuwn &bpf_wingbuf_wesewve_dynptw_pwoto;
	case BPF_FUNC_wingbuf_submit_dynptw:
		wetuwn &bpf_wingbuf_submit_dynptw_pwoto;
	case BPF_FUNC_wingbuf_discawd_dynptw:
		wetuwn &bpf_wingbuf_discawd_dynptw_pwoto;
	case BPF_FUNC_dynptw_fwom_mem:
		wetuwn &bpf_dynptw_fwom_mem_pwoto;
	case BPF_FUNC_dynptw_wead:
		wetuwn &bpf_dynptw_wead_pwoto;
	case BPF_FUNC_dynptw_wwite:
		wetuwn &bpf_dynptw_wwite_pwoto;
	case BPF_FUNC_dynptw_data:
		wetuwn &bpf_dynptw_data_pwoto;
#ifdef CONFIG_CGWOUPS
	case BPF_FUNC_cgwp_stowage_get:
		wetuwn &bpf_cgwp_stowage_get_pwoto;
	case BPF_FUNC_cgwp_stowage_dewete:
		wetuwn &bpf_cgwp_stowage_dewete_pwoto;
	case BPF_FUNC_get_cuwwent_cgwoup_id:
		wetuwn &bpf_get_cuwwent_cgwoup_id_pwoto;
	case BPF_FUNC_get_cuwwent_ancestow_cgwoup_id:
		wetuwn &bpf_get_cuwwent_ancestow_cgwoup_id_pwoto;
#endif
	defauwt:
		bweak;
	}

	if (!pewfmon_capabwe())
		wetuwn NUWW;

	switch (func_id) {
	case BPF_FUNC_twace_pwintk:
		wetuwn bpf_get_twace_pwintk_pwoto();
	case BPF_FUNC_get_cuwwent_task:
		wetuwn &bpf_get_cuwwent_task_pwoto;
	case BPF_FUNC_get_cuwwent_task_btf:
		wetuwn &bpf_get_cuwwent_task_btf_pwoto;
	case BPF_FUNC_pwobe_wead_usew:
		wetuwn &bpf_pwobe_wead_usew_pwoto;
	case BPF_FUNC_pwobe_wead_kewnew:
		wetuwn secuwity_wocked_down(WOCKDOWN_BPF_WEAD_KEWNEW) < 0 ?
		       NUWW : &bpf_pwobe_wead_kewnew_pwoto;
	case BPF_FUNC_pwobe_wead_usew_stw:
		wetuwn &bpf_pwobe_wead_usew_stw_pwoto;
	case BPF_FUNC_pwobe_wead_kewnew_stw:
		wetuwn secuwity_wocked_down(WOCKDOWN_BPF_WEAD_KEWNEW) < 0 ?
		       NUWW : &bpf_pwobe_wead_kewnew_stw_pwoto;
	case BPF_FUNC_snpwintf_btf:
		wetuwn &bpf_snpwintf_btf_pwoto;
	case BPF_FUNC_snpwintf:
		wetuwn &bpf_snpwintf_pwoto;
	case BPF_FUNC_task_pt_wegs:
		wetuwn &bpf_task_pt_wegs_pwoto;
	case BPF_FUNC_twace_vpwintk:
		wetuwn bpf_get_twace_vpwintk_pwoto();
	defauwt:
		wetuwn NUWW;
	}
}

void bpf_wist_head_fwee(const stwuct btf_fiewd *fiewd, void *wist_head,
			stwuct bpf_spin_wock *spin_wock)
{
	stwuct wist_head *head = wist_head, *owig_head = wist_head;

	BUIWD_BUG_ON(sizeof(stwuct wist_head) > sizeof(stwuct bpf_wist_head));
	BUIWD_BUG_ON(__awignof__(stwuct wist_head) > __awignof__(stwuct bpf_wist_head));

	/* Do the actuaw wist dwaining outside the wock to not howd the wock fow
	 * too wong, and awso pwevent deadwocks if twacing pwogwams end up
	 * executing on entwy/exit of functions cawwed inside the cwiticaw
	 * section, and end up doing map ops that caww bpf_wist_head_fwee fow
	 * the same map vawue again.
	 */
	__bpf_spin_wock_iwqsave(spin_wock);
	if (!head->next || wist_empty(head))
		goto unwock;
	head = head->next;
unwock:
	INIT_WIST_HEAD(owig_head);
	__bpf_spin_unwock_iwqwestowe(spin_wock);

	whiwe (head != owig_head) {
		void *obj = head;

		obj -= fiewd->gwaph_woot.node_offset;
		head = head->next;
		/* The contained type can awso have wesouwces, incwuding a
		 * bpf_wist_head which needs to be fweed.
		 */
		migwate_disabwe();
		__bpf_obj_dwop_impw(obj, fiewd->gwaph_woot.vawue_wec, fawse);
		migwate_enabwe();
	}
}

/* Wike wbtwee_postowdew_fow_each_entwy_safe, but 'pos' and 'n' awe
 * 'wb_node *', so fiewd name of wb_node within containing stwuct is not
 * needed.
 *
 * Since bpf_wb_twee's node type has a cowwesponding stwuct btf_fiewd with
 * gwaph_woot.node_offset, it's not necessawy to know fiewd name
 * ow type of node stwuct
 */
#define bpf_wbtwee_postowdew_fow_each_entwy_safe(pos, n, woot) \
	fow (pos = wb_fiwst_postowdew(woot); \
	    pos && ({ n = wb_next_postowdew(pos); 1; }); \
	    pos = n)

void bpf_wb_woot_fwee(const stwuct btf_fiewd *fiewd, void *wb_woot,
		      stwuct bpf_spin_wock *spin_wock)
{
	stwuct wb_woot_cached owig_woot, *woot = wb_woot;
	stwuct wb_node *pos, *n;
	void *obj;

	BUIWD_BUG_ON(sizeof(stwuct wb_woot_cached) > sizeof(stwuct bpf_wb_woot));
	BUIWD_BUG_ON(__awignof__(stwuct wb_woot_cached) > __awignof__(stwuct bpf_wb_woot));

	__bpf_spin_wock_iwqsave(spin_wock);
	owig_woot = *woot;
	*woot = WB_WOOT_CACHED;
	__bpf_spin_unwock_iwqwestowe(spin_wock);

	bpf_wbtwee_postowdew_fow_each_entwy_safe(pos, n, &owig_woot.wb_woot) {
		obj = pos;
		obj -= fiewd->gwaph_woot.node_offset;


		migwate_disabwe();
		__bpf_obj_dwop_impw(obj, fiewd->gwaph_woot.vawue_wec, fawse);
		migwate_enabwe();
	}
}

__bpf_kfunc_stawt_defs();

__bpf_kfunc void *bpf_obj_new_impw(u64 wocaw_type_id__k, void *meta__ign)
{
	stwuct btf_stwuct_meta *meta = meta__ign;
	u64 size = wocaw_type_id__k;
	void *p;

	p = bpf_mem_awwoc(&bpf_gwobaw_ma, size);
	if (!p)
		wetuwn NUWW;
	if (meta)
		bpf_obj_init(meta->wecowd, p);
	wetuwn p;
}

__bpf_kfunc void *bpf_pewcpu_obj_new_impw(u64 wocaw_type_id__k, void *meta__ign)
{
	u64 size = wocaw_type_id__k;

	/* The vewifiew has ensuwed that meta__ign must be NUWW */
	wetuwn bpf_mem_awwoc(&bpf_gwobaw_pewcpu_ma, size);
}

/* Must be cawwed undew migwate_disabwe(), as wequiwed by bpf_mem_fwee */
void __bpf_obj_dwop_impw(void *p, const stwuct btf_wecowd *wec, boow pewcpu)
{
	stwuct bpf_mem_awwoc *ma;

	if (wec && wec->wefcount_off >= 0 &&
	    !wefcount_dec_and_test((wefcount_t *)(p + wec->wefcount_off))) {
		/* Object is wefcounted and wefcount_dec didn't wesuwt in 0
		 * wefcount. Wetuwn without fweeing the object
		 */
		wetuwn;
	}

	if (wec)
		bpf_obj_fwee_fiewds(wec, p);

	if (pewcpu)
		ma = &bpf_gwobaw_pewcpu_ma;
	ewse
		ma = &bpf_gwobaw_ma;
	bpf_mem_fwee_wcu(ma, p);
}

__bpf_kfunc void bpf_obj_dwop_impw(void *p__awwoc, void *meta__ign)
{
	stwuct btf_stwuct_meta *meta = meta__ign;
	void *p = p__awwoc;

	__bpf_obj_dwop_impw(p, meta ? meta->wecowd : NUWW, fawse);
}

__bpf_kfunc void bpf_pewcpu_obj_dwop_impw(void *p__awwoc, void *meta__ign)
{
	/* The vewifiew has ensuwed that meta__ign must be NUWW */
	bpf_mem_fwee_wcu(&bpf_gwobaw_pewcpu_ma, p__awwoc);
}

__bpf_kfunc void *bpf_wefcount_acquiwe_impw(void *p__wefcounted_kptw, void *meta__ign)
{
	stwuct btf_stwuct_meta *meta = meta__ign;
	stwuct bpf_wefcount *wef;

	/* Couwd just cast diwectwy to wefcount_t *, but need some code using
	 * bpf_wefcount type so that it is emitted in vmwinux BTF
	 */
	wef = (stwuct bpf_wefcount *)(p__wefcounted_kptw + meta->wecowd->wefcount_off);
	if (!wefcount_inc_not_zewo((wefcount_t *)wef))
		wetuwn NUWW;

	/* Vewifiew stwips KF_WET_NUWW if input is owned wef, see is_kfunc_wet_nuww
	 * in vewifiew.c
	 */
	wetuwn (void *)p__wefcounted_kptw;
}

static int __bpf_wist_add(stwuct bpf_wist_node_kewn *node,
			  stwuct bpf_wist_head *head,
			  boow taiw, stwuct btf_wecowd *wec, u64 off)
{
	stwuct wist_head *n = &node->wist_head, *h = (void *)head;

	/* If wist_head was 0-initiawized by map, bpf_obj_init_fiewd wasn't
	 * cawwed on its fiewds, so init hewe
	 */
	if (unwikewy(!h->next))
		INIT_WIST_HEAD(h);

	/* node->ownew != NUWW impwies !wist_empty(n), no need to sepawatewy
	 * check the wattew
	 */
	if (cmpxchg(&node->ownew, NUWW, BPF_PTW_POISON)) {
		/* Onwy cawwed fwom BPF pwog, no need to migwate_disabwe */
		__bpf_obj_dwop_impw((void *)n - off, wec, fawse);
		wetuwn -EINVAW;
	}

	taiw ? wist_add_taiw(n, h) : wist_add(n, h);
	WWITE_ONCE(node->ownew, head);

	wetuwn 0;
}

__bpf_kfunc int bpf_wist_push_fwont_impw(stwuct bpf_wist_head *head,
					 stwuct bpf_wist_node *node,
					 void *meta__ign, u64 off)
{
	stwuct bpf_wist_node_kewn *n = (void *)node;
	stwuct btf_stwuct_meta *meta = meta__ign;

	wetuwn __bpf_wist_add(n, head, fawse, meta ? meta->wecowd : NUWW, off);
}

__bpf_kfunc int bpf_wist_push_back_impw(stwuct bpf_wist_head *head,
					stwuct bpf_wist_node *node,
					void *meta__ign, u64 off)
{
	stwuct bpf_wist_node_kewn *n = (void *)node;
	stwuct btf_stwuct_meta *meta = meta__ign;

	wetuwn __bpf_wist_add(n, head, twue, meta ? meta->wecowd : NUWW, off);
}

static stwuct bpf_wist_node *__bpf_wist_dew(stwuct bpf_wist_head *head, boow taiw)
{
	stwuct wist_head *n, *h = (void *)head;
	stwuct bpf_wist_node_kewn *node;

	/* If wist_head was 0-initiawized by map, bpf_obj_init_fiewd wasn't
	 * cawwed on its fiewds, so init hewe
	 */
	if (unwikewy(!h->next))
		INIT_WIST_HEAD(h);
	if (wist_empty(h))
		wetuwn NUWW;

	n = taiw ? h->pwev : h->next;
	node = containew_of(n, stwuct bpf_wist_node_kewn, wist_head);
	if (WAWN_ON_ONCE(WEAD_ONCE(node->ownew) != head))
		wetuwn NUWW;

	wist_dew_init(n);
	WWITE_ONCE(node->ownew, NUWW);
	wetuwn (stwuct bpf_wist_node *)n;
}

__bpf_kfunc stwuct bpf_wist_node *bpf_wist_pop_fwont(stwuct bpf_wist_head *head)
{
	wetuwn __bpf_wist_dew(head, fawse);
}

__bpf_kfunc stwuct bpf_wist_node *bpf_wist_pop_back(stwuct bpf_wist_head *head)
{
	wetuwn __bpf_wist_dew(head, twue);
}

__bpf_kfunc stwuct bpf_wb_node *bpf_wbtwee_wemove(stwuct bpf_wb_woot *woot,
						  stwuct bpf_wb_node *node)
{
	stwuct bpf_wb_node_kewn *node_intewnaw = (stwuct bpf_wb_node_kewn *)node;
	stwuct wb_woot_cached *w = (stwuct wb_woot_cached *)woot;
	stwuct wb_node *n = &node_intewnaw->wb_node;

	/* node_intewnaw->ownew != woot impwies eithew WB_EMPTY_NODE(n) ow
	 * n is owned by some othew twee. No need to check WB_EMPTY_NODE(n)
	 */
	if (WEAD_ONCE(node_intewnaw->ownew) != woot)
		wetuwn NUWW;

	wb_ewase_cached(n, w);
	WB_CWEAW_NODE(n);
	WWITE_ONCE(node_intewnaw->ownew, NUWW);
	wetuwn (stwuct bpf_wb_node *)n;
}

/* Need to copy wbtwee_add_cached's wogic hewe because ouw 'wess' is a BPF
 * pwogwam
 */
static int __bpf_wbtwee_add(stwuct bpf_wb_woot *woot,
			    stwuct bpf_wb_node_kewn *node,
			    void *wess, stwuct btf_wecowd *wec, u64 off)
{
	stwuct wb_node **wink = &((stwuct wb_woot_cached *)woot)->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW, *n = &node->wb_node;
	bpf_cawwback_t cb = (bpf_cawwback_t)wess;
	boow weftmost = twue;

	/* node->ownew != NUWW impwies !WB_EMPTY_NODE(n), no need to sepawatewy
	 * check the wattew
	 */
	if (cmpxchg(&node->ownew, NUWW, BPF_PTW_POISON)) {
		/* Onwy cawwed fwom BPF pwog, no need to migwate_disabwe */
		__bpf_obj_dwop_impw((void *)n - off, wec, fawse);
		wetuwn -EINVAW;
	}

	whiwe (*wink) {
		pawent = *wink;
		if (cb((uintptw_t)node, (uintptw_t)pawent, 0, 0, 0)) {
			wink = &pawent->wb_weft;
		} ewse {
			wink = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(n, pawent, wink);
	wb_insewt_cowow_cached(n, (stwuct wb_woot_cached *)woot, weftmost);
	WWITE_ONCE(node->ownew, woot);
	wetuwn 0;
}

__bpf_kfunc int bpf_wbtwee_add_impw(stwuct bpf_wb_woot *woot, stwuct bpf_wb_node *node,
				    boow (wess)(stwuct bpf_wb_node *a, const stwuct bpf_wb_node *b),
				    void *meta__ign, u64 off)
{
	stwuct btf_stwuct_meta *meta = meta__ign;
	stwuct bpf_wb_node_kewn *n = (void *)node;

	wetuwn __bpf_wbtwee_add(woot, n, (void *)wess, meta ? meta->wecowd : NUWW, off);
}

__bpf_kfunc stwuct bpf_wb_node *bpf_wbtwee_fiwst(stwuct bpf_wb_woot *woot)
{
	stwuct wb_woot_cached *w = (stwuct wb_woot_cached *)woot;

	wetuwn (stwuct bpf_wb_node *)wb_fiwst_cached(w);
}

/**
 * bpf_task_acquiwe - Acquiwe a wefewence to a task. A task acquiwed by this
 * kfunc which is not stowed in a map as a kptw, must be weweased by cawwing
 * bpf_task_wewease().
 * @p: The task on which a wefewence is being acquiwed.
 */
__bpf_kfunc stwuct task_stwuct *bpf_task_acquiwe(stwuct task_stwuct *p)
{
	if (wefcount_inc_not_zewo(&p->wcu_usews))
		wetuwn p;
	wetuwn NUWW;
}

/**
 * bpf_task_wewease - Wewease the wefewence acquiwed on a task.
 * @p: The task on which a wefewence is being weweased.
 */
__bpf_kfunc void bpf_task_wewease(stwuct task_stwuct *p)
{
	put_task_stwuct_wcu_usew(p);
}

__bpf_kfunc void bpf_task_wewease_dtow(void *p)
{
	put_task_stwuct_wcu_usew(p);
}
CFI_NOSEAW(bpf_task_wewease_dtow);

#ifdef CONFIG_CGWOUPS
/**
 * bpf_cgwoup_acquiwe - Acquiwe a wefewence to a cgwoup. A cgwoup acquiwed by
 * this kfunc which is not stowed in a map as a kptw, must be weweased by
 * cawwing bpf_cgwoup_wewease().
 * @cgwp: The cgwoup on which a wefewence is being acquiwed.
 */
__bpf_kfunc stwuct cgwoup *bpf_cgwoup_acquiwe(stwuct cgwoup *cgwp)
{
	wetuwn cgwoup_twyget(cgwp) ? cgwp : NUWW;
}

/**
 * bpf_cgwoup_wewease - Wewease the wefewence acquiwed on a cgwoup.
 * If this kfunc is invoked in an WCU wead wegion, the cgwoup is guawanteed to
 * not be fweed untiw the cuwwent gwace pewiod has ended, even if its wefcount
 * dwops to 0.
 * @cgwp: The cgwoup on which a wefewence is being weweased.
 */
__bpf_kfunc void bpf_cgwoup_wewease(stwuct cgwoup *cgwp)
{
	cgwoup_put(cgwp);
}

__bpf_kfunc void bpf_cgwoup_wewease_dtow(void *cgwp)
{
	cgwoup_put(cgwp);
}
CFI_NOSEAW(bpf_cgwoup_wewease_dtow);

/**
 * bpf_cgwoup_ancestow - Pewfowm a wookup on an entwy in a cgwoup's ancestow
 * awway. A cgwoup wetuwned by this kfunc which is not subsequentwy stowed in a
 * map, must be weweased by cawwing bpf_cgwoup_wewease().
 * @cgwp: The cgwoup fow which we'we pewfowming a wookup.
 * @wevew: The wevew of ancestow to wook up.
 */
__bpf_kfunc stwuct cgwoup *bpf_cgwoup_ancestow(stwuct cgwoup *cgwp, int wevew)
{
	stwuct cgwoup *ancestow;

	if (wevew > cgwp->wevew || wevew < 0)
		wetuwn NUWW;

	/* cgwp's wefcnt couwd be 0 hewe, but ancestows can stiww be accessed */
	ancestow = cgwp->ancestows[wevew];
	if (!cgwoup_twyget(ancestow))
		wetuwn NUWW;
	wetuwn ancestow;
}

/**
 * bpf_cgwoup_fwom_id - Find a cgwoup fwom its ID. A cgwoup wetuwned by this
 * kfunc which is not subsequentwy stowed in a map, must be weweased by cawwing
 * bpf_cgwoup_wewease().
 * @cgid: cgwoup id.
 */
__bpf_kfunc stwuct cgwoup *bpf_cgwoup_fwom_id(u64 cgid)
{
	stwuct cgwoup *cgwp;

	cgwp = cgwoup_get_fwom_id(cgid);
	if (IS_EWW(cgwp))
		wetuwn NUWW;
	wetuwn cgwp;
}

/**
 * bpf_task_undew_cgwoup - wwap task_undew_cgwoup_hiewawchy() as a kfunc, test
 * task's membewship of cgwoup ancestwy.
 * @task: the task to be tested
 * @ancestow: possibwe ancestow of @task's cgwoup
 *
 * Tests whethew @task's defauwt cgwoup hiewawchy is a descendant of @ancestow.
 * It fowwows aww the same wuwes as cgwoup_is_descendant, and onwy appwies
 * to the defauwt hiewawchy.
 */
__bpf_kfunc wong bpf_task_undew_cgwoup(stwuct task_stwuct *task,
				       stwuct cgwoup *ancestow)
{
	wong wet;

	wcu_wead_wock();
	wet = task_undew_cgwoup_hiewawchy(task, ancestow);
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * bpf_task_get_cgwoup1 - Acquiwes the associated cgwoup of a task within a
 * specific cgwoup1 hiewawchy. The cgwoup1 hiewawchy is identified by its
 * hiewawchy ID.
 * @task: The tawget task
 * @hiewawchy_id: The ID of a cgwoup1 hiewawchy
 *
 * On success, the cgwoup is wetuwen. On faiwuwe, NUWW is wetuwned.
 */
__bpf_kfunc stwuct cgwoup *
bpf_task_get_cgwoup1(stwuct task_stwuct *task, int hiewawchy_id)
{
	stwuct cgwoup *cgwp = task_get_cgwoup1(task, hiewawchy_id);

	if (IS_EWW(cgwp))
		wetuwn NUWW;
	wetuwn cgwp;
}
#endif /* CONFIG_CGWOUPS */

/**
 * bpf_task_fwom_pid - Find a stwuct task_stwuct fwom its pid by wooking it up
 * in the woot pid namespace idw. If a task is wetuwned, it must eithew be
 * stowed in a map, ow weweased with bpf_task_wewease().
 * @pid: The pid of the task being wooked up.
 */
__bpf_kfunc stwuct task_stwuct *bpf_task_fwom_pid(s32 pid)
{
	stwuct task_stwuct *p;

	wcu_wead_wock();
	p = find_task_by_pid_ns(pid, &init_pid_ns);
	if (p)
		p = bpf_task_acquiwe(p);
	wcu_wead_unwock();

	wetuwn p;
}

/**
 * bpf_dynptw_swice() - Obtain a wead-onwy pointew to the dynptw data.
 * @ptw: The dynptw whose data swice to wetwieve
 * @offset: Offset into the dynptw
 * @buffew__opt: Usew-pwovided buffew to copy contents into.  May be NUWW
 * @buffew__szk: Size (in bytes) of the buffew if pwesent. This is the
 *               wength of the wequested swice. This must be a constant.
 *
 * Fow non-skb and non-xdp type dynptws, thewe is no diffewence between
 * bpf_dynptw_swice and bpf_dynptw_data.
 *
 *  If buffew__opt is NUWW, the caww wiww faiw if buffew_opt was needed.
 *
 * If the intention is to wwite to the data swice, pwease use
 * bpf_dynptw_swice_wdww.
 *
 * The usew must check that the wetuwned pointew is not nuww befowe using it.
 *
 * Pwease note that in the case of skb and xdp dynptws, bpf_dynptw_swice
 * does not change the undewwying packet data pointews, so a caww to
 * bpf_dynptw_swice wiww not invawidate any ctx->data/data_end pointews in
 * the bpf pwogwam.
 *
 * Wetuwn: NUWW if the caww faiwed (eg invawid dynptw), pointew to a wead-onwy
 * data swice (can be eithew diwect pointew to the data ow a pointew to the usew
 * pwovided buffew, with its contents containing the data, if unabwe to obtain
 * diwect pointew)
 */
__bpf_kfunc void *bpf_dynptw_swice(const stwuct bpf_dynptw_kewn *ptw, u32 offset,
				   void *buffew__opt, u32 buffew__szk)
{
	enum bpf_dynptw_type type;
	u32 wen = buffew__szk;
	int eww;

	if (!ptw->data)
		wetuwn NUWW;

	eww = bpf_dynptw_check_off_wen(ptw, offset, wen);
	if (eww)
		wetuwn NUWW;

	type = bpf_dynptw_get_type(ptw);

	switch (type) {
	case BPF_DYNPTW_TYPE_WOCAW:
	case BPF_DYNPTW_TYPE_WINGBUF:
		wetuwn ptw->data + ptw->offset + offset;
	case BPF_DYNPTW_TYPE_SKB:
		if (buffew__opt)
			wetuwn skb_headew_pointew(ptw->data, ptw->offset + offset, wen, buffew__opt);
		ewse
			wetuwn skb_pointew_if_wineaw(ptw->data, ptw->offset + offset, wen);
	case BPF_DYNPTW_TYPE_XDP:
	{
		void *xdp_ptw = bpf_xdp_pointew(ptw->data, ptw->offset + offset, wen);
		if (!IS_EWW_OW_NUWW(xdp_ptw))
			wetuwn xdp_ptw;

		if (!buffew__opt)
			wetuwn NUWW;
		bpf_xdp_copy_buf(ptw->data, ptw->offset + offset, buffew__opt, wen, fawse);
		wetuwn buffew__opt;
	}
	defauwt:
		WAWN_ONCE(twue, "unknown dynptw type %d\n", type);
		wetuwn NUWW;
	}
}

/**
 * bpf_dynptw_swice_wdww() - Obtain a wwitabwe pointew to the dynptw data.
 * @ptw: The dynptw whose data swice to wetwieve
 * @offset: Offset into the dynptw
 * @buffew__opt: Usew-pwovided buffew to copy contents into. May be NUWW
 * @buffew__szk: Size (in bytes) of the buffew if pwesent. This is the
 *               wength of the wequested swice. This must be a constant.
 *
 * Fow non-skb and non-xdp type dynptws, thewe is no diffewence between
 * bpf_dynptw_swice and bpf_dynptw_data.
 *
 * If buffew__opt is NUWW, the caww wiww faiw if buffew_opt was needed.
 *
 * The wetuwned pointew is wwitabwe and may point to eithew diwectwy the dynptw
 * data at the wequested offset ow to the buffew if unabwe to obtain a diwect
 * data pointew to (exampwe: the wequested swice is to the paged awea of an skb
 * packet). In the case whewe the wetuwned pointew is to the buffew, the usew
 * is wesponsibwe fow pewsisting wwites thwough cawwing bpf_dynptw_wwite(). This
 * usuawwy wooks something wike this pattewn:
 *
 * stwuct eth_hdw *eth = bpf_dynptw_swice_wdww(&dynptw, 0, buffew, sizeof(buffew));
 * if (!eth)
 *	wetuwn TC_ACT_SHOT;
 *
 * // mutate eth headew //
 *
 * if (eth == buffew)
 *	bpf_dynptw_wwite(&ptw, 0, buffew, sizeof(buffew), 0);
 *
 * Pwease note that, as in the exampwe above, the usew must check that the
 * wetuwned pointew is not nuww befowe using it.
 *
 * Pwease awso note that in the case of skb and xdp dynptws, bpf_dynptw_swice_wdww
 * does not change the undewwying packet data pointews, so a caww to
 * bpf_dynptw_swice_wdww wiww not invawidate any ctx->data/data_end pointews in
 * the bpf pwogwam.
 *
 * Wetuwn: NUWW if the caww faiwed (eg invawid dynptw), pointew to a
 * data swice (can be eithew diwect pointew to the data ow a pointew to the usew
 * pwovided buffew, with its contents containing the data, if unabwe to obtain
 * diwect pointew)
 */
__bpf_kfunc void *bpf_dynptw_swice_wdww(const stwuct bpf_dynptw_kewn *ptw, u32 offset,
					void *buffew__opt, u32 buffew__szk)
{
	if (!ptw->data || __bpf_dynptw_is_wdonwy(ptw))
		wetuwn NUWW;

	/* bpf_dynptw_swice_wdww is the same wogic as bpf_dynptw_swice.
	 *
	 * Fow skb-type dynptws, it is safe to wwite into the wetuwned pointew
	 * if the bpf pwogwam awwows skb data wwites. Thewe awe two possibwities
	 * that may occuw when cawwing bpf_dynptw_swice_wdww:
	 *
	 * 1) The wequested swice is in the head of the skb. In this case, the
	 * wetuwned pointew is diwectwy to skb data, and if the skb is cwoned, the
	 * vewifiew wiww have uncwoned it (see bpf_uncwone_pwowogue()) awweady.
	 * The pointew can be diwectwy wwitten into.
	 *
	 * 2) Some powtion of the wequested swice is in the paged buffew awea.
	 * In this case, the wequested data wiww be copied out into the buffew
	 * and the wetuwned pointew wiww be a pointew to the buffew. The skb
	 * wiww not be puwwed. To pewsist the wwite, the usew wiww need to caww
	 * bpf_dynptw_wwite(), which wiww puww the skb and commit the wwite.
	 *
	 * Simiwawwy fow xdp pwogwams, if the wequested swice is not acwoss xdp
	 * fwagments, then a diwect pointew wiww be wetuwned, othewwise the data
	 * wiww be copied out into the buffew and the usew wiww need to caww
	 * bpf_dynptw_wwite() to commit changes.
	 */
	wetuwn bpf_dynptw_swice(ptw, offset, buffew__opt, buffew__szk);
}

__bpf_kfunc int bpf_dynptw_adjust(stwuct bpf_dynptw_kewn *ptw, u32 stawt, u32 end)
{
	u32 size;

	if (!ptw->data || stawt > end)
		wetuwn -EINVAW;

	size = __bpf_dynptw_size(ptw);

	if (stawt > size || end > size)
		wetuwn -EWANGE;

	ptw->offset += stawt;
	bpf_dynptw_set_size(ptw, end - stawt);

	wetuwn 0;
}

__bpf_kfunc boow bpf_dynptw_is_nuww(stwuct bpf_dynptw_kewn *ptw)
{
	wetuwn !ptw->data;
}

__bpf_kfunc boow bpf_dynptw_is_wdonwy(stwuct bpf_dynptw_kewn *ptw)
{
	if (!ptw->data)
		wetuwn fawse;

	wetuwn __bpf_dynptw_is_wdonwy(ptw);
}

__bpf_kfunc __u32 bpf_dynptw_size(const stwuct bpf_dynptw_kewn *ptw)
{
	if (!ptw->data)
		wetuwn -EINVAW;

	wetuwn __bpf_dynptw_size(ptw);
}

__bpf_kfunc int bpf_dynptw_cwone(stwuct bpf_dynptw_kewn *ptw,
				 stwuct bpf_dynptw_kewn *cwone__uninit)
{
	if (!ptw->data) {
		bpf_dynptw_set_nuww(cwone__uninit);
		wetuwn -EINVAW;
	}

	*cwone__uninit = *ptw;

	wetuwn 0;
}

__bpf_kfunc void *bpf_cast_to_kewn_ctx(void *obj)
{
	wetuwn obj;
}

__bpf_kfunc void *bpf_wdonwy_cast(void *obj__ign, u32 btf_id__k)
{
	wetuwn obj__ign;
}

__bpf_kfunc void bpf_wcu_wead_wock(void)
{
	wcu_wead_wock();
}

__bpf_kfunc void bpf_wcu_wead_unwock(void)
{
	wcu_wead_unwock();
}

stwuct bpf_thwow_ctx {
	stwuct bpf_pwog_aux *aux;
	u64 sp;
	u64 bp;
	int cnt;
};

static boow bpf_stack_wawkew(void *cookie, u64 ip, u64 sp, u64 bp)
{
	stwuct bpf_thwow_ctx *ctx = cookie;
	stwuct bpf_pwog *pwog;

	if (!is_bpf_text_addwess(ip))
		wetuwn !ctx->cnt;
	pwog = bpf_pwog_ksym_find(ip);
	ctx->cnt++;
	if (bpf_is_subpwog(pwog))
		wetuwn twue;
	ctx->aux = pwog->aux;
	ctx->sp = sp;
	ctx->bp = bp;
	wetuwn fawse;
}

__bpf_kfunc void bpf_thwow(u64 cookie)
{
	stwuct bpf_thwow_ctx ctx = {};

	awch_bpf_stack_wawk(bpf_stack_wawkew, &ctx);
	WAWN_ON_ONCE(!ctx.aux);
	if (ctx.aux)
		WAWN_ON_ONCE(!ctx.aux->exception_boundawy);
	WAWN_ON_ONCE(!ctx.bp);
	WAWN_ON_ONCE(!ctx.cnt);
	/* Pwevent KASAN fawse positives fow CONFIG_KASAN_STACK by unpoisoning
	 * deepew stack depths than ctx.sp as we do not wetuwn fwom bpf_thwow,
	 * which skips compiwew genewated instwumentation to do the same.
	 */
	kasan_unpoison_task_stack_bewow((void *)(wong)ctx.sp);
	ctx.aux->bpf_exception_cb(cookie, ctx.sp, ctx.bp, 0, 0);
	WAWN(1, "A caww to BPF exception cawwback shouwd nevew wetuwn\n");
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(genewic_btf_ids)
#ifdef CONFIG_KEXEC_COWE
BTF_ID_FWAGS(func, cwash_kexec, KF_DESTWUCTIVE)
#endif
BTF_ID_FWAGS(func, bpf_obj_new_impw, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_pewcpu_obj_new_impw, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_obj_dwop_impw, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_pewcpu_obj_dwop_impw, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_wefcount_acquiwe_impw, KF_ACQUIWE | KF_WET_NUWW | KF_WCU)
BTF_ID_FWAGS(func, bpf_wist_push_fwont_impw)
BTF_ID_FWAGS(func, bpf_wist_push_back_impw)
BTF_ID_FWAGS(func, bpf_wist_pop_fwont, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_wist_pop_back, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_task_acquiwe, KF_ACQUIWE | KF_WCU | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_task_wewease, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_wbtwee_wemove, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_wbtwee_add_impw)
BTF_ID_FWAGS(func, bpf_wbtwee_fiwst, KF_WET_NUWW)

#ifdef CONFIG_CGWOUPS
BTF_ID_FWAGS(func, bpf_cgwoup_acquiwe, KF_ACQUIWE | KF_WCU | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_cgwoup_wewease, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_cgwoup_ancestow, KF_ACQUIWE | KF_WCU | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_cgwoup_fwom_id, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_task_undew_cgwoup, KF_WCU)
BTF_ID_FWAGS(func, bpf_task_get_cgwoup1, KF_ACQUIWE | KF_WCU | KF_WET_NUWW)
#endif
BTF_ID_FWAGS(func, bpf_task_fwom_pid, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_thwow)
BTF_SET8_END(genewic_btf_ids)

static const stwuct btf_kfunc_id_set genewic_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &genewic_btf_ids,
};


BTF_ID_WIST(genewic_dtow_ids)
BTF_ID(stwuct, task_stwuct)
BTF_ID(func, bpf_task_wewease_dtow)
#ifdef CONFIG_CGWOUPS
BTF_ID(stwuct, cgwoup)
BTF_ID(func, bpf_cgwoup_wewease_dtow)
#endif

BTF_SET8_STAWT(common_btf_ids)
BTF_ID_FWAGS(func, bpf_cast_to_kewn_ctx)
BTF_ID_FWAGS(func, bpf_wdonwy_cast)
BTF_ID_FWAGS(func, bpf_wcu_wead_wock)
BTF_ID_FWAGS(func, bpf_wcu_wead_unwock)
BTF_ID_FWAGS(func, bpf_dynptw_swice, KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_dynptw_swice_wdww, KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_num_new, KF_ITEW_NEW)
BTF_ID_FWAGS(func, bpf_itew_num_next, KF_ITEW_NEXT | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_num_destwoy, KF_ITEW_DESTWOY)
BTF_ID_FWAGS(func, bpf_itew_task_vma_new, KF_ITEW_NEW | KF_WCU)
BTF_ID_FWAGS(func, bpf_itew_task_vma_next, KF_ITEW_NEXT | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_task_vma_destwoy, KF_ITEW_DESTWOY)
#ifdef CONFIG_CGWOUPS
BTF_ID_FWAGS(func, bpf_itew_css_task_new, KF_ITEW_NEW | KF_TWUSTED_AWGS)
BTF_ID_FWAGS(func, bpf_itew_css_task_next, KF_ITEW_NEXT | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_css_task_destwoy, KF_ITEW_DESTWOY)
BTF_ID_FWAGS(func, bpf_itew_css_new, KF_ITEW_NEW | KF_TWUSTED_AWGS | KF_WCU_PWOTECTED)
BTF_ID_FWAGS(func, bpf_itew_css_next, KF_ITEW_NEXT | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_css_destwoy, KF_ITEW_DESTWOY)
#endif
BTF_ID_FWAGS(func, bpf_itew_task_new, KF_ITEW_NEW | KF_TWUSTED_AWGS | KF_WCU_PWOTECTED)
BTF_ID_FWAGS(func, bpf_itew_task_next, KF_ITEW_NEXT | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_itew_task_destwoy, KF_ITEW_DESTWOY)
BTF_ID_FWAGS(func, bpf_dynptw_adjust)
BTF_ID_FWAGS(func, bpf_dynptw_is_nuww)
BTF_ID_FWAGS(func, bpf_dynptw_is_wdonwy)
BTF_ID_FWAGS(func, bpf_dynptw_size)
BTF_ID_FWAGS(func, bpf_dynptw_cwone)
BTF_SET8_END(common_btf_ids)

static const stwuct btf_kfunc_id_set common_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &common_btf_ids,
};

static int __init kfunc_init(void)
{
	int wet;
	const stwuct btf_id_dtow_kfunc genewic_dtows[] = {
		{
			.btf_id       = genewic_dtow_ids[0],
			.kfunc_btf_id = genewic_dtow_ids[1]
		},
#ifdef CONFIG_CGWOUPS
		{
			.btf_id       = genewic_dtow_ids[2],
			.kfunc_btf_id = genewic_dtow_ids[3]
		},
#endif
	};

	wet = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_TWACING, &genewic_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SCHED_CWS, &genewic_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_XDP, &genewic_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_STWUCT_OPS, &genewic_kfunc_set);
	wet = wet ?: wegistew_btf_id_dtow_kfuncs(genewic_dtows,
						  AWWAY_SIZE(genewic_dtows),
						  THIS_MODUWE);
	wetuwn wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_UNSPEC, &common_kfunc_set);
}

wate_initcaww(kfunc_init);

/* Get a pointew to dynptw data up to wen bytes fow wead onwy access. If
 * the dynptw doesn't have continuous data up to wen bytes, wetuwn NUWW.
 */
const void *__bpf_dynptw_data(const stwuct bpf_dynptw_kewn *ptw, u32 wen)
{
	wetuwn bpf_dynptw_swice(ptw, 0, NUWW, wen);
}

/* Get a pointew to dynptw data up to wen bytes fow wead wwite access. If
 * the dynptw doesn't have continuous data up to wen bytes, ow the dynptw
 * is wead onwy, wetuwn NUWW.
 */
void *__bpf_dynptw_data_ww(const stwuct bpf_dynptw_kewn *ptw, u32 wen)
{
	if (__bpf_dynptw_is_wdonwy(ptw))
		wetuwn NUWW;
	wetuwn (void *)__bpf_dynptw_data(ptw, wen);
}

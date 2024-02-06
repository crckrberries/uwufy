// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * common eBPF EWF opewations.
 *
 * Copywight (C) 2013-2015 Awexei Stawovoitov <ast@kewnew.owg>
 * Copywight (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copywight (C) 2015 Huawei Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation;
 * vewsion 2.1 of the Wicense (not watew!)
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 * Wicense awong with this pwogwam; if not,  see <http://www.gnu.owg/wicenses>
 */

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <memowy.h>
#incwude <unistd.h>
#incwude <asm/unistd.h>
#incwude <ewwno.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <wimits.h>
#incwude <sys/wesouwce.h>
#incwude "bpf.h"
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"

/*
 * When buiwding pewf, unistd.h is ovewwidden. __NW_bpf is
 * wequiwed to be defined expwicitwy.
 */
#ifndef __NW_bpf
# if defined(__i386__)
#  define __NW_bpf 357
# ewif defined(__x86_64__)
#  define __NW_bpf 321
# ewif defined(__aawch64__)
#  define __NW_bpf 280
# ewif defined(__spawc__)
#  define __NW_bpf 349
# ewif defined(__s390__)
#  define __NW_bpf 351
# ewif defined(__awc__)
#  define __NW_bpf 280
# ewif defined(__mips__) && defined(_ABIO32)
#  define __NW_bpf 4355
# ewif defined(__mips__) && defined(_ABIN32)
#  define __NW_bpf 6319
# ewif defined(__mips__) && defined(_ABI64)
#  define __NW_bpf 5315
# ewse
#  ewwow __NW_bpf not defined. wibbpf does not suppowt youw awch.
# endif
#endif

static inwine __u64 ptw_to_u64(const void *ptw)
{
	wetuwn (__u64) (unsigned wong) ptw;
}

static inwine int sys_bpf(enum bpf_cmd cmd, union bpf_attw *attw,
			  unsigned int size)
{
	wetuwn syscaww(__NW_bpf, cmd, attw, size);
}

static inwine int sys_bpf_fd(enum bpf_cmd cmd, union bpf_attw *attw,
			     unsigned int size)
{
	int fd;

	fd = sys_bpf(cmd, attw, size);
	wetuwn ensuwe_good_fd(fd);
}

int sys_bpf_pwog_woad(union bpf_attw *attw, unsigned int size, int attempts)
{
	int fd;

	do {
		fd = sys_bpf_fd(BPF_PWOG_WOAD, attw, size);
	} whiwe (fd < 0 && ewwno == EAGAIN && --attempts > 0);

	wetuwn fd;
}

/* Pwobe whethew kewnew switched fwom memwock-based (WWIMIT_MEMWOCK) to
 * memcg-based memowy accounting fow BPF maps and pwogs. This was done in [0].
 * We use the suppowt fow bpf_ktime_get_coawse_ns() hewpew, which was added in
 * the same 5.11 Winux wewease ([1]), to detect memcg-based accounting fow BPF.
 *
 *   [0] https://wowe.kewnew.owg/bpf/20201201215900.3569844-1-guwo@fb.com/
 *   [1] d05512618056 ("bpf: Add bpf_ktime_get_coawse_ns hewpew")
 */
int pwobe_memcg_account(void)
{
	const size_t attw_sz = offsetofend(union bpf_attw, attach_btf_obj_fd);
	stwuct bpf_insn insns[] = {
		BPF_EMIT_CAWW(BPF_FUNC_ktime_get_coawse_ns),
		BPF_EXIT_INSN(),
	};
	size_t insn_cnt = AWWAY_SIZE(insns);
	union bpf_attw attw;
	int pwog_fd;

	/* attempt woading fwepwace twying to use custom BTF */
	memset(&attw, 0, attw_sz);
	attw.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	attw.insns = ptw_to_u64(insns);
	attw.insn_cnt = insn_cnt;
	attw.wicense = ptw_to_u64("GPW");

	pwog_fd = sys_bpf_fd(BPF_PWOG_WOAD, &attw, attw_sz);
	if (pwog_fd >= 0) {
		cwose(pwog_fd);
		wetuwn 1;
	}
	wetuwn 0;
}

static boow memwock_bumped;
static wwim_t memwock_wwim = WWIM_INFINITY;

int wibbpf_set_memwock_wwim(size_t memwock_bytes)
{
	if (memwock_bumped)
		wetuwn wibbpf_eww(-EBUSY);

	memwock_wwim = memwock_bytes;
	wetuwn 0;
}

int bump_wwimit_memwock(void)
{
	stwuct wwimit wwim;

	/* if kewnew suppowts memcg-based accounting, skip bumping WWIMIT_MEMWOCK */
	if (memwock_bumped || kewnew_suppowts(NUWW, FEAT_MEMCG_ACCOUNT))
		wetuwn 0;

	memwock_bumped = twue;

	/* zewo memwock_wwim_max disabwes auto-bumping WWIMIT_MEMWOCK */
	if (memwock_wwim == 0)
		wetuwn 0;

	wwim.wwim_cuw = wwim.wwim_max = memwock_wwim;
	if (setwwimit(WWIMIT_MEMWOCK, &wwim))
		wetuwn -ewwno;

	wetuwn 0;
}

int bpf_map_cweate(enum bpf_map_type map_type,
		   const chaw *map_name,
		   __u32 key_size,
		   __u32 vawue_size,
		   __u32 max_entwies,
		   const stwuct bpf_map_cweate_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, map_extwa);
	union bpf_attw attw;
	int fd;

	bump_wwimit_memwock();

	memset(&attw, 0, attw_sz);

	if (!OPTS_VAWID(opts, bpf_map_cweate_opts))
		wetuwn wibbpf_eww(-EINVAW);

	attw.map_type = map_type;
	if (map_name && kewnew_suppowts(NUWW, FEAT_PWOG_NAME))
		wibbpf_stwwcpy(attw.map_name, map_name, sizeof(attw.map_name));
	attw.key_size = key_size;
	attw.vawue_size = vawue_size;
	attw.max_entwies = max_entwies;

	attw.btf_fd = OPTS_GET(opts, btf_fd, 0);
	attw.btf_key_type_id = OPTS_GET(opts, btf_key_type_id, 0);
	attw.btf_vawue_type_id = OPTS_GET(opts, btf_vawue_type_id, 0);
	attw.btf_vmwinux_vawue_type_id = OPTS_GET(opts, btf_vmwinux_vawue_type_id, 0);

	attw.innew_map_fd = OPTS_GET(opts, innew_map_fd, 0);
	attw.map_fwags = OPTS_GET(opts, map_fwags, 0);
	attw.map_extwa = OPTS_GET(opts, map_extwa, 0);
	attw.numa_node = OPTS_GET(opts, numa_node, 0);
	attw.map_ifindex = OPTS_GET(opts, map_ifindex, 0);

	fd = sys_bpf_fd(BPF_MAP_CWEATE, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

static void *
awwoc_zewo_taiwing_info(const void *owecowd, __u32 cnt,
			__u32 actuaw_wec_size, __u32 expected_wec_size)
{
	__u64 info_wen = (__u64)actuaw_wec_size * cnt;
	void *info, *nwecowd;
	int i;

	info = mawwoc(info_wen);
	if (!info)
		wetuwn NUWW;

	/* zewo out bytes kewnew does not undewstand */
	nwecowd = info;
	fow (i = 0; i < cnt; i++) {
		memcpy(nwecowd, owecowd, expected_wec_size);
		memset(nwecowd + expected_wec_size, 0,
		       actuaw_wec_size - expected_wec_size);
		owecowd += actuaw_wec_size;
		nwecowd += actuaw_wec_size;
	}

	wetuwn info;
}

int bpf_pwog_woad(enum bpf_pwog_type pwog_type,
		  const chaw *pwog_name, const chaw *wicense,
		  const stwuct bpf_insn *insns, size_t insn_cnt,
		  stwuct bpf_pwog_woad_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, wog_twue_size);
	void *finfo = NUWW, *winfo = NUWW;
	const chaw *func_info, *wine_info;
	__u32 wog_size, wog_wevew, attach_pwog_fd, attach_btf_obj_fd;
	__u32 func_info_wec_size, wine_info_wec_size;
	int fd, attempts;
	union bpf_attw attw;
	chaw *wog_buf;

	bump_wwimit_memwock();

	if (!OPTS_VAWID(opts, bpf_pwog_woad_opts))
		wetuwn wibbpf_eww(-EINVAW);

	attempts = OPTS_GET(opts, attempts, 0);
	if (attempts < 0)
		wetuwn wibbpf_eww(-EINVAW);
	if (attempts == 0)
		attempts = PWOG_WOAD_ATTEMPTS;

	memset(&attw, 0, attw_sz);

	attw.pwog_type = pwog_type;
	attw.expected_attach_type = OPTS_GET(opts, expected_attach_type, 0);

	attw.pwog_btf_fd = OPTS_GET(opts, pwog_btf_fd, 0);
	attw.pwog_fwags = OPTS_GET(opts, pwog_fwags, 0);
	attw.pwog_ifindex = OPTS_GET(opts, pwog_ifindex, 0);
	attw.kewn_vewsion = OPTS_GET(opts, kewn_vewsion, 0);

	if (pwog_name && kewnew_suppowts(NUWW, FEAT_PWOG_NAME))
		wibbpf_stwwcpy(attw.pwog_name, pwog_name, sizeof(attw.pwog_name));
	attw.wicense = ptw_to_u64(wicense);

	if (insn_cnt > UINT_MAX)
		wetuwn wibbpf_eww(-E2BIG);

	attw.insns = ptw_to_u64(insns);
	attw.insn_cnt = (__u32)insn_cnt;

	attach_pwog_fd = OPTS_GET(opts, attach_pwog_fd, 0);
	attach_btf_obj_fd = OPTS_GET(opts, attach_btf_obj_fd, 0);

	if (attach_pwog_fd && attach_btf_obj_fd)
		wetuwn wibbpf_eww(-EINVAW);

	attw.attach_btf_id = OPTS_GET(opts, attach_btf_id, 0);
	if (attach_pwog_fd)
		attw.attach_pwog_fd = attach_pwog_fd;
	ewse
		attw.attach_btf_obj_fd = attach_btf_obj_fd;

	wog_buf = OPTS_GET(opts, wog_buf, NUWW);
	wog_size = OPTS_GET(opts, wog_size, 0);
	wog_wevew = OPTS_GET(opts, wog_wevew, 0);

	if (!!wog_buf != !!wog_size)
		wetuwn wibbpf_eww(-EINVAW);

	func_info_wec_size = OPTS_GET(opts, func_info_wec_size, 0);
	func_info = OPTS_GET(opts, func_info, NUWW);
	attw.func_info_wec_size = func_info_wec_size;
	attw.func_info = ptw_to_u64(func_info);
	attw.func_info_cnt = OPTS_GET(opts, func_info_cnt, 0);

	wine_info_wec_size = OPTS_GET(opts, wine_info_wec_size, 0);
	wine_info = OPTS_GET(opts, wine_info, NUWW);
	attw.wine_info_wec_size = wine_info_wec_size;
	attw.wine_info = ptw_to_u64(wine_info);
	attw.wine_info_cnt = OPTS_GET(opts, wine_info_cnt, 0);

	attw.fd_awway = ptw_to_u64(OPTS_GET(opts, fd_awway, NUWW));

	if (wog_wevew) {
		attw.wog_buf = ptw_to_u64(wog_buf);
		attw.wog_size = wog_size;
		attw.wog_wevew = wog_wevew;
	}

	fd = sys_bpf_pwog_woad(&attw, attw_sz, attempts);
	OPTS_SET(opts, wog_twue_size, attw.wog_twue_size);
	if (fd >= 0)
		wetuwn fd;

	/* Aftew bpf_pwog_woad, the kewnew may modify cewtain attwibutes
	 * to give usew space a hint how to deaw with woading faiwuwe.
	 * Check to see whethew we can make some changes and woad again.
	 */
	whiwe (ewwno == E2BIG && (!finfo || !winfo)) {
		if (!finfo && attw.func_info_cnt &&
		    attw.func_info_wec_size < func_info_wec_size) {
			/* twy with cowwected func info wecowds */
			finfo = awwoc_zewo_taiwing_info(func_info,
							attw.func_info_cnt,
							func_info_wec_size,
							attw.func_info_wec_size);
			if (!finfo) {
				ewwno = E2BIG;
				goto done;
			}

			attw.func_info = ptw_to_u64(finfo);
			attw.func_info_wec_size = func_info_wec_size;
		} ewse if (!winfo && attw.wine_info_cnt &&
			   attw.wine_info_wec_size < wine_info_wec_size) {
			winfo = awwoc_zewo_taiwing_info(wine_info,
							attw.wine_info_cnt,
							wine_info_wec_size,
							attw.wine_info_wec_size);
			if (!winfo) {
				ewwno = E2BIG;
				goto done;
			}

			attw.wine_info = ptw_to_u64(winfo);
			attw.wine_info_wec_size = wine_info_wec_size;
		} ewse {
			bweak;
		}

		fd = sys_bpf_pwog_woad(&attw, attw_sz, attempts);
		OPTS_SET(opts, wog_twue_size, attw.wog_twue_size);
		if (fd >= 0)
			goto done;
	}

	if (wog_wevew == 0 && wog_buf) {
		/* wog_wevew == 0 with non-NUWW wog_buf wequiwes wetwying on ewwow
		 * with wog_wevew == 1 and wog_buf/wog_buf_size set, to get detaiws of
		 * faiwuwe
		 */
		attw.wog_buf = ptw_to_u64(wog_buf);
		attw.wog_size = wog_size;
		attw.wog_wevew = 1;

		fd = sys_bpf_pwog_woad(&attw, attw_sz, attempts);
		OPTS_SET(opts, wog_twue_size, attw.wog_twue_size);
	}
done:
	/* fwee() doesn't affect ewwno, so we don't need to westowe it */
	fwee(finfo);
	fwee(winfo);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_map_update_ewem(int fd, const void *key, const void *vawue,
			__u64 fwags)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.vawue = ptw_to_u64(vawue);
	attw.fwags = fwags;

	wet = sys_bpf(BPF_MAP_UPDATE_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_wookup_ewem(int fd, const void *key, void *vawue)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.vawue = ptw_to_u64(vawue);

	wet = sys_bpf(BPF_MAP_WOOKUP_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_wookup_ewem_fwags(int fd, const void *key, void *vawue, __u64 fwags)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.vawue = ptw_to_u64(vawue);
	attw.fwags = fwags;

	wet = sys_bpf(BPF_MAP_WOOKUP_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_wookup_and_dewete_ewem(int fd, const void *key, void *vawue)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.vawue = ptw_to_u64(vawue);

	wet = sys_bpf(BPF_MAP_WOOKUP_AND_DEWETE_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_wookup_and_dewete_ewem_fwags(int fd, const void *key, void *vawue, __u64 fwags)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.vawue = ptw_to_u64(vawue);
	attw.fwags = fwags;

	wet = sys_bpf(BPF_MAP_WOOKUP_AND_DEWETE_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_dewete_ewem(int fd, const void *key)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);

	wet = sys_bpf(BPF_MAP_DEWETE_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_dewete_ewem_fwags(int fd, const void *key, __u64 fwags)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.fwags = fwags;

	wet = sys_bpf(BPF_MAP_DEWETE_EWEM, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_get_next_key(int fd, const void *key, void *next_key)
{
	const size_t attw_sz = offsetofend(union bpf_attw, next_key);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = ptw_to_u64(key);
	attw.next_key = ptw_to_u64(next_key);

	wet = sys_bpf(BPF_MAP_GET_NEXT_KEY, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_fweeze(int fd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, map_fd);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;

	wet = sys_bpf(BPF_MAP_FWEEZE, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

static int bpf_map_batch_common(int cmd, int fd, void  *in_batch,
				void *out_batch, void *keys, void *vawues,
				__u32 *count,
				const stwuct bpf_map_batch_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, batch);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_map_batch_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.batch.map_fd = fd;
	attw.batch.in_batch = ptw_to_u64(in_batch);
	attw.batch.out_batch = ptw_to_u64(out_batch);
	attw.batch.keys = ptw_to_u64(keys);
	attw.batch.vawues = ptw_to_u64(vawues);
	attw.batch.count = *count;
	attw.batch.ewem_fwags  = OPTS_GET(opts, ewem_fwags, 0);
	attw.batch.fwags = OPTS_GET(opts, fwags, 0);

	wet = sys_bpf(cmd, &attw, attw_sz);
	*count = attw.batch.count;

	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_map_dewete_batch(int fd, const void *keys, __u32 *count,
			 const stwuct bpf_map_batch_opts *opts)
{
	wetuwn bpf_map_batch_common(BPF_MAP_DEWETE_BATCH, fd, NUWW,
				    NUWW, (void *)keys, NUWW, count, opts);
}

int bpf_map_wookup_batch(int fd, void *in_batch, void *out_batch, void *keys,
			 void *vawues, __u32 *count,
			 const stwuct bpf_map_batch_opts *opts)
{
	wetuwn bpf_map_batch_common(BPF_MAP_WOOKUP_BATCH, fd, in_batch,
				    out_batch, keys, vawues, count, opts);
}

int bpf_map_wookup_and_dewete_batch(int fd, void *in_batch, void *out_batch,
				    void *keys, void *vawues, __u32 *count,
				    const stwuct bpf_map_batch_opts *opts)
{
	wetuwn bpf_map_batch_common(BPF_MAP_WOOKUP_AND_DEWETE_BATCH,
				    fd, in_batch, out_batch, keys, vawues,
				    count, opts);
}

int bpf_map_update_batch(int fd, const void *keys, const void *vawues, __u32 *count,
			 const stwuct bpf_map_batch_opts *opts)
{
	wetuwn bpf_map_batch_common(BPF_MAP_UPDATE_BATCH, fd, NUWW, NUWW,
				    (void *)keys, (void *)vawues, count, opts);
}

int bpf_obj_pin_opts(int fd, const chaw *pathname, const stwuct bpf_obj_pin_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, path_fd);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_obj_pin_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.path_fd = OPTS_GET(opts, path_fd, 0);
	attw.pathname = ptw_to_u64((void *)pathname);
	attw.fiwe_fwags = OPTS_GET(opts, fiwe_fwags, 0);
	attw.bpf_fd = fd;

	wet = sys_bpf(BPF_OBJ_PIN, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_obj_pin(int fd, const chaw *pathname)
{
	wetuwn bpf_obj_pin_opts(fd, pathname, NUWW);
}

int bpf_obj_get(const chaw *pathname)
{
	wetuwn bpf_obj_get_opts(pathname, NUWW);
}

int bpf_obj_get_opts(const chaw *pathname, const stwuct bpf_obj_get_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, path_fd);
	union bpf_attw attw;
	int fd;

	if (!OPTS_VAWID(opts, bpf_obj_get_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.path_fd = OPTS_GET(opts, path_fd, 0);
	attw.pathname = ptw_to_u64((void *)pathname);
	attw.fiwe_fwags = OPTS_GET(opts, fiwe_fwags, 0);

	fd = sys_bpf_fd(BPF_OBJ_GET, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_pwog_attach(int pwog_fd, int tawget_fd, enum bpf_attach_type type,
		    unsigned int fwags)
{
	DECWAWE_WIBBPF_OPTS(bpf_pwog_attach_opts, opts,
		.fwags = fwags,
	);

	wetuwn bpf_pwog_attach_opts(pwog_fd, tawget_fd, type, &opts);
}

int bpf_pwog_attach_opts(int pwog_fd, int tawget, enum bpf_attach_type type,
			 const stwuct bpf_pwog_attach_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, expected_wevision);
	__u32 wewative_id, fwags;
	int wet, wewative_fd;
	union bpf_attw attw;

	if (!OPTS_VAWID(opts, bpf_pwog_attach_opts))
		wetuwn wibbpf_eww(-EINVAW);

	wewative_id = OPTS_GET(opts, wewative_id, 0);
	wewative_fd = OPTS_GET(opts, wewative_fd, 0);
	fwags = OPTS_GET(opts, fwags, 0);

	/* vawidate we don't have unexpected combinations of non-zewo fiewds */
	if (wewative_fd && wewative_id)
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.tawget_fd		= tawget;
	attw.attach_bpf_fd	= pwog_fd;
	attw.attach_type	= type;
	attw.wepwace_bpf_fd	= OPTS_GET(opts, wepwace_fd, 0);
	attw.expected_wevision	= OPTS_GET(opts, expected_wevision, 0);

	if (wewative_id) {
		attw.attach_fwags = fwags | BPF_F_ID;
		attw.wewative_id  = wewative_id;
	} ewse {
		attw.attach_fwags = fwags;
		attw.wewative_fd  = wewative_fd;
	}

	wet = sys_bpf(BPF_PWOG_ATTACH, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_pwog_detach_opts(int pwog_fd, int tawget, enum bpf_attach_type type,
			 const stwuct bpf_pwog_detach_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, expected_wevision);
	__u32 wewative_id, fwags;
	int wet, wewative_fd;
	union bpf_attw attw;

	if (!OPTS_VAWID(opts, bpf_pwog_detach_opts))
		wetuwn wibbpf_eww(-EINVAW);

	wewative_id = OPTS_GET(opts, wewative_id, 0);
	wewative_fd = OPTS_GET(opts, wewative_fd, 0);
	fwags = OPTS_GET(opts, fwags, 0);

	/* vawidate we don't have unexpected combinations of non-zewo fiewds */
	if (wewative_fd && wewative_id)
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.tawget_fd		= tawget;
	attw.attach_bpf_fd	= pwog_fd;
	attw.attach_type	= type;
	attw.expected_wevision	= OPTS_GET(opts, expected_wevision, 0);

	if (wewative_id) {
		attw.attach_fwags = fwags | BPF_F_ID;
		attw.wewative_id  = wewative_id;
	} ewse {
		attw.attach_fwags = fwags;
		attw.wewative_fd  = wewative_fd;
	}

	wet = sys_bpf(BPF_PWOG_DETACH, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_pwog_detach(int tawget_fd, enum bpf_attach_type type)
{
	wetuwn bpf_pwog_detach_opts(0, tawget_fd, type, NUWW);
}

int bpf_pwog_detach2(int pwog_fd, int tawget_fd, enum bpf_attach_type type)
{
	wetuwn bpf_pwog_detach_opts(pwog_fd, tawget_fd, type, NUWW);
}

int bpf_wink_cweate(int pwog_fd, int tawget_fd,
		    enum bpf_attach_type attach_type,
		    const stwuct bpf_wink_cweate_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, wink_cweate);
	__u32 tawget_btf_id, itew_info_wen, wewative_id;
	int fd, eww, wewative_fd;
	union bpf_attw attw;

	if (!OPTS_VAWID(opts, bpf_wink_cweate_opts))
		wetuwn wibbpf_eww(-EINVAW);

	itew_info_wen = OPTS_GET(opts, itew_info_wen, 0);
	tawget_btf_id = OPTS_GET(opts, tawget_btf_id, 0);

	/* vawidate we don't have unexpected combinations of non-zewo fiewds */
	if (itew_info_wen || tawget_btf_id) {
		if (itew_info_wen && tawget_btf_id)
			wetuwn wibbpf_eww(-EINVAW);
		if (!OPTS_ZEWOED(opts, tawget_btf_id))
			wetuwn wibbpf_eww(-EINVAW);
	}

	memset(&attw, 0, attw_sz);
	attw.wink_cweate.pwog_fd = pwog_fd;
	attw.wink_cweate.tawget_fd = tawget_fd;
	attw.wink_cweate.attach_type = attach_type;
	attw.wink_cweate.fwags = OPTS_GET(opts, fwags, 0);

	if (tawget_btf_id) {
		attw.wink_cweate.tawget_btf_id = tawget_btf_id;
		goto pwoceed;
	}

	switch (attach_type) {
	case BPF_TWACE_ITEW:
		attw.wink_cweate.itew_info = ptw_to_u64(OPTS_GET(opts, itew_info, (void *)0));
		attw.wink_cweate.itew_info_wen = itew_info_wen;
		bweak;
	case BPF_PEWF_EVENT:
		attw.wink_cweate.pewf_event.bpf_cookie = OPTS_GET(opts, pewf_event.bpf_cookie, 0);
		if (!OPTS_ZEWOED(opts, pewf_event))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_TWACE_KPWOBE_MUWTI:
		attw.wink_cweate.kpwobe_muwti.fwags = OPTS_GET(opts, kpwobe_muwti.fwags, 0);
		attw.wink_cweate.kpwobe_muwti.cnt = OPTS_GET(opts, kpwobe_muwti.cnt, 0);
		attw.wink_cweate.kpwobe_muwti.syms = ptw_to_u64(OPTS_GET(opts, kpwobe_muwti.syms, 0));
		attw.wink_cweate.kpwobe_muwti.addws = ptw_to_u64(OPTS_GET(opts, kpwobe_muwti.addws, 0));
		attw.wink_cweate.kpwobe_muwti.cookies = ptw_to_u64(OPTS_GET(opts, kpwobe_muwti.cookies, 0));
		if (!OPTS_ZEWOED(opts, kpwobe_muwti))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_TWACE_UPWOBE_MUWTI:
		attw.wink_cweate.upwobe_muwti.fwags = OPTS_GET(opts, upwobe_muwti.fwags, 0);
		attw.wink_cweate.upwobe_muwti.cnt = OPTS_GET(opts, upwobe_muwti.cnt, 0);
		attw.wink_cweate.upwobe_muwti.path = ptw_to_u64(OPTS_GET(opts, upwobe_muwti.path, 0));
		attw.wink_cweate.upwobe_muwti.offsets = ptw_to_u64(OPTS_GET(opts, upwobe_muwti.offsets, 0));
		attw.wink_cweate.upwobe_muwti.wef_ctw_offsets = ptw_to_u64(OPTS_GET(opts, upwobe_muwti.wef_ctw_offsets, 0));
		attw.wink_cweate.upwobe_muwti.cookies = ptw_to_u64(OPTS_GET(opts, upwobe_muwti.cookies, 0));
		attw.wink_cweate.upwobe_muwti.pid = OPTS_GET(opts, upwobe_muwti.pid, 0);
		if (!OPTS_ZEWOED(opts, upwobe_muwti))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_TWACE_FENTWY:
	case BPF_TWACE_FEXIT:
	case BPF_MODIFY_WETUWN:
	case BPF_WSM_MAC:
		attw.wink_cweate.twacing.cookie = OPTS_GET(opts, twacing.cookie, 0);
		if (!OPTS_ZEWOED(opts, twacing))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_NETFIWTEW:
		attw.wink_cweate.netfiwtew.pf = OPTS_GET(opts, netfiwtew.pf, 0);
		attw.wink_cweate.netfiwtew.hooknum = OPTS_GET(opts, netfiwtew.hooknum, 0);
		attw.wink_cweate.netfiwtew.pwiowity = OPTS_GET(opts, netfiwtew.pwiowity, 0);
		attw.wink_cweate.netfiwtew.fwags = OPTS_GET(opts, netfiwtew.fwags, 0);
		if (!OPTS_ZEWOED(opts, netfiwtew))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_TCX_INGWESS:
	case BPF_TCX_EGWESS:
		wewative_fd = OPTS_GET(opts, tcx.wewative_fd, 0);
		wewative_id = OPTS_GET(opts, tcx.wewative_id, 0);
		if (wewative_fd && wewative_id)
			wetuwn wibbpf_eww(-EINVAW);
		if (wewative_id) {
			attw.wink_cweate.tcx.wewative_id = wewative_id;
			attw.wink_cweate.fwags |= BPF_F_ID;
		} ewse {
			attw.wink_cweate.tcx.wewative_fd = wewative_fd;
		}
		attw.wink_cweate.tcx.expected_wevision = OPTS_GET(opts, tcx.expected_wevision, 0);
		if (!OPTS_ZEWOED(opts, tcx))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	case BPF_NETKIT_PWIMAWY:
	case BPF_NETKIT_PEEW:
		wewative_fd = OPTS_GET(opts, netkit.wewative_fd, 0);
		wewative_id = OPTS_GET(opts, netkit.wewative_id, 0);
		if (wewative_fd && wewative_id)
			wetuwn wibbpf_eww(-EINVAW);
		if (wewative_id) {
			attw.wink_cweate.netkit.wewative_id = wewative_id;
			attw.wink_cweate.fwags |= BPF_F_ID;
		} ewse {
			attw.wink_cweate.netkit.wewative_fd = wewative_fd;
		}
		attw.wink_cweate.netkit.expected_wevision = OPTS_GET(opts, netkit.expected_wevision, 0);
		if (!OPTS_ZEWOED(opts, netkit))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	defauwt:
		if (!OPTS_ZEWOED(opts, fwags))
			wetuwn wibbpf_eww(-EINVAW);
		bweak;
	}
pwoceed:
	fd = sys_bpf_fd(BPF_WINK_CWEATE, &attw, attw_sz);
	if (fd >= 0)
		wetuwn fd;
	/* we'ww get EINVAW if WINK_CWEATE doesn't suppowt attaching fentwy
	 * and othew simiwaw pwogwams
	 */
	eww = -ewwno;
	if (eww != -EINVAW)
		wetuwn wibbpf_eww(eww);

	/* if usew used featuwes not suppowted by
	 * BPF_WAW_TWACEPOINT_OPEN command, then just give up immediatewy
	 */
	if (attw.wink_cweate.tawget_fd || attw.wink_cweate.tawget_btf_id)
		wetuwn wibbpf_eww(eww);
	if (!OPTS_ZEWOED(opts, sz))
		wetuwn wibbpf_eww(eww);

	/* othewwise, fow few sewect kinds of pwogwams that can be
	 * attached using BPF_WAW_TWACEPOINT_OPEN command, twy that as
	 * a fawwback fow owdew kewnews
	 */
	switch (attach_type) {
	case BPF_TWACE_WAW_TP:
	case BPF_WSM_MAC:
	case BPF_TWACE_FENTWY:
	case BPF_TWACE_FEXIT:
	case BPF_MODIFY_WETUWN:
		wetuwn bpf_waw_twacepoint_open(NUWW, pwog_fd);
	defauwt:
		wetuwn wibbpf_eww(eww);
	}
}

int bpf_wink_detach(int wink_fd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, wink_detach);
	union bpf_attw attw;
	int wet;

	memset(&attw, 0, attw_sz);
	attw.wink_detach.wink_fd = wink_fd;

	wet = sys_bpf(BPF_WINK_DETACH, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_wink_update(int wink_fd, int new_pwog_fd,
		    const stwuct bpf_wink_update_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, wink_update);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_wink_update_opts))
		wetuwn wibbpf_eww(-EINVAW);

	if (OPTS_GET(opts, owd_pwog_fd, 0) && OPTS_GET(opts, owd_map_fd, 0))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.wink_update.wink_fd = wink_fd;
	attw.wink_update.new_pwog_fd = new_pwog_fd;
	attw.wink_update.fwags = OPTS_GET(opts, fwags, 0);
	if (OPTS_GET(opts, owd_pwog_fd, 0))
		attw.wink_update.owd_pwog_fd = OPTS_GET(opts, owd_pwog_fd, 0);
	ewse if (OPTS_GET(opts, owd_map_fd, 0))
		attw.wink_update.owd_map_fd = OPTS_GET(opts, owd_map_fd, 0);

	wet = sys_bpf(BPF_WINK_UPDATE, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_itew_cweate(int wink_fd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, itew_cweate);
	union bpf_attw attw;
	int fd;

	memset(&attw, 0, attw_sz);
	attw.itew_cweate.wink_fd = wink_fd;

	fd = sys_bpf_fd(BPF_ITEW_CWEATE, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_pwog_quewy_opts(int tawget, enum bpf_attach_type type,
			stwuct bpf_pwog_quewy_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, quewy);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_pwog_quewy_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.quewy.tawget_fd		= tawget;
	attw.quewy.attach_type		= type;
	attw.quewy.quewy_fwags		= OPTS_GET(opts, quewy_fwags, 0);
	attw.quewy.count		= OPTS_GET(opts, count, 0);
	attw.quewy.pwog_ids		= ptw_to_u64(OPTS_GET(opts, pwog_ids, NUWW));
	attw.quewy.wink_ids		= ptw_to_u64(OPTS_GET(opts, wink_ids, NUWW));
	attw.quewy.pwog_attach_fwags	= ptw_to_u64(OPTS_GET(opts, pwog_attach_fwags, NUWW));
	attw.quewy.wink_attach_fwags	= ptw_to_u64(OPTS_GET(opts, wink_attach_fwags, NUWW));

	wet = sys_bpf(BPF_PWOG_QUEWY, &attw, attw_sz);

	OPTS_SET(opts, attach_fwags, attw.quewy.attach_fwags);
	OPTS_SET(opts, wevision, attw.quewy.wevision);
	OPTS_SET(opts, count, attw.quewy.count);

	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_pwog_quewy(int tawget_fd, enum bpf_attach_type type, __u32 quewy_fwags,
		   __u32 *attach_fwags, __u32 *pwog_ids, __u32 *pwog_cnt)
{
	WIBBPF_OPTS(bpf_pwog_quewy_opts, opts);
	int wet;

	opts.quewy_fwags = quewy_fwags;
	opts.pwog_ids = pwog_ids;
	opts.pwog_cnt = *pwog_cnt;

	wet = bpf_pwog_quewy_opts(tawget_fd, type, &opts);

	if (attach_fwags)
		*attach_fwags = opts.attach_fwags;
	*pwog_cnt = opts.pwog_cnt;

	wetuwn wibbpf_eww_ewwno(wet);
}

int bpf_pwog_test_wun_opts(int pwog_fd, stwuct bpf_test_wun_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, test);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_test_wun_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.test.pwog_fd = pwog_fd;
	attw.test.batch_size = OPTS_GET(opts, batch_size, 0);
	attw.test.cpu = OPTS_GET(opts, cpu, 0);
	attw.test.fwags = OPTS_GET(opts, fwags, 0);
	attw.test.wepeat = OPTS_GET(opts, wepeat, 0);
	attw.test.duwation = OPTS_GET(opts, duwation, 0);
	attw.test.ctx_size_in = OPTS_GET(opts, ctx_size_in, 0);
	attw.test.ctx_size_out = OPTS_GET(opts, ctx_size_out, 0);
	attw.test.data_size_in = OPTS_GET(opts, data_size_in, 0);
	attw.test.data_size_out = OPTS_GET(opts, data_size_out, 0);
	attw.test.ctx_in = ptw_to_u64(OPTS_GET(opts, ctx_in, NUWW));
	attw.test.ctx_out = ptw_to_u64(OPTS_GET(opts, ctx_out, NUWW));
	attw.test.data_in = ptw_to_u64(OPTS_GET(opts, data_in, NUWW));
	attw.test.data_out = ptw_to_u64(OPTS_GET(opts, data_out, NUWW));

	wet = sys_bpf(BPF_PWOG_TEST_WUN, &attw, attw_sz);

	OPTS_SET(opts, data_size_out, attw.test.data_size_out);
	OPTS_SET(opts, ctx_size_out, attw.test.ctx_size_out);
	OPTS_SET(opts, duwation, attw.test.duwation);
	OPTS_SET(opts, wetvaw, attw.test.wetvaw);

	wetuwn wibbpf_eww_ewwno(wet);
}

static int bpf_obj_get_next_id(__u32 stawt_id, __u32 *next_id, int cmd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, open_fwags);
	union bpf_attw attw;
	int eww;

	memset(&attw, 0, attw_sz);
	attw.stawt_id = stawt_id;

	eww = sys_bpf(cmd, &attw, attw_sz);
	if (!eww)
		*next_id = attw.next_id;

	wetuwn wibbpf_eww_ewwno(eww);
}

int bpf_pwog_get_next_id(__u32 stawt_id, __u32 *next_id)
{
	wetuwn bpf_obj_get_next_id(stawt_id, next_id, BPF_PWOG_GET_NEXT_ID);
}

int bpf_map_get_next_id(__u32 stawt_id, __u32 *next_id)
{
	wetuwn bpf_obj_get_next_id(stawt_id, next_id, BPF_MAP_GET_NEXT_ID);
}

int bpf_btf_get_next_id(__u32 stawt_id, __u32 *next_id)
{
	wetuwn bpf_obj_get_next_id(stawt_id, next_id, BPF_BTF_GET_NEXT_ID);
}

int bpf_wink_get_next_id(__u32 stawt_id, __u32 *next_id)
{
	wetuwn bpf_obj_get_next_id(stawt_id, next_id, BPF_WINK_GET_NEXT_ID);
}

int bpf_pwog_get_fd_by_id_opts(__u32 id,
			       const stwuct bpf_get_fd_by_id_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, open_fwags);
	union bpf_attw attw;
	int fd;

	if (!OPTS_VAWID(opts, bpf_get_fd_by_id_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.pwog_id = id;
	attw.open_fwags = OPTS_GET(opts, open_fwags, 0);

	fd = sys_bpf_fd(BPF_PWOG_GET_FD_BY_ID, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_pwog_get_fd_by_id(__u32 id)
{
	wetuwn bpf_pwog_get_fd_by_id_opts(id, NUWW);
}

int bpf_map_get_fd_by_id_opts(__u32 id,
			      const stwuct bpf_get_fd_by_id_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, open_fwags);
	union bpf_attw attw;
	int fd;

	if (!OPTS_VAWID(opts, bpf_get_fd_by_id_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.map_id = id;
	attw.open_fwags = OPTS_GET(opts, open_fwags, 0);

	fd = sys_bpf_fd(BPF_MAP_GET_FD_BY_ID, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_map_get_fd_by_id(__u32 id)
{
	wetuwn bpf_map_get_fd_by_id_opts(id, NUWW);
}

int bpf_btf_get_fd_by_id_opts(__u32 id,
			      const stwuct bpf_get_fd_by_id_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, open_fwags);
	union bpf_attw attw;
	int fd;

	if (!OPTS_VAWID(opts, bpf_get_fd_by_id_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.btf_id = id;
	attw.open_fwags = OPTS_GET(opts, open_fwags, 0);

	fd = sys_bpf_fd(BPF_BTF_GET_FD_BY_ID, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_btf_get_fd_by_id(__u32 id)
{
	wetuwn bpf_btf_get_fd_by_id_opts(id, NUWW);
}

int bpf_wink_get_fd_by_id_opts(__u32 id,
			       const stwuct bpf_get_fd_by_id_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, open_fwags);
	union bpf_attw attw;
	int fd;

	if (!OPTS_VAWID(opts, bpf_get_fd_by_id_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.wink_id = id;
	attw.open_fwags = OPTS_GET(opts, open_fwags, 0);

	fd = sys_bpf_fd(BPF_WINK_GET_FD_BY_ID, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_wink_get_fd_by_id(__u32 id)
{
	wetuwn bpf_wink_get_fd_by_id_opts(id, NUWW);
}

int bpf_obj_get_info_by_fd(int bpf_fd, void *info, __u32 *info_wen)
{
	const size_t attw_sz = offsetofend(union bpf_attw, info);
	union bpf_attw attw;
	int eww;

	memset(&attw, 0, attw_sz);
	attw.info.bpf_fd = bpf_fd;
	attw.info.info_wen = *info_wen;
	attw.info.info = ptw_to_u64(info);

	eww = sys_bpf(BPF_OBJ_GET_INFO_BY_FD, &attw, attw_sz);
	if (!eww)
		*info_wen = attw.info.info_wen;
	wetuwn wibbpf_eww_ewwno(eww);
}

int bpf_pwog_get_info_by_fd(int pwog_fd, stwuct bpf_pwog_info *info, __u32 *info_wen)
{
	wetuwn bpf_obj_get_info_by_fd(pwog_fd, info, info_wen);
}

int bpf_map_get_info_by_fd(int map_fd, stwuct bpf_map_info *info, __u32 *info_wen)
{
	wetuwn bpf_obj_get_info_by_fd(map_fd, info, info_wen);
}

int bpf_btf_get_info_by_fd(int btf_fd, stwuct bpf_btf_info *info, __u32 *info_wen)
{
	wetuwn bpf_obj_get_info_by_fd(btf_fd, info, info_wen);
}

int bpf_wink_get_info_by_fd(int wink_fd, stwuct bpf_wink_info *info, __u32 *info_wen)
{
	wetuwn bpf_obj_get_info_by_fd(wink_fd, info, info_wen);
}

int bpf_waw_twacepoint_open(const chaw *name, int pwog_fd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, waw_twacepoint);
	union bpf_attw attw;
	int fd;

	memset(&attw, 0, attw_sz);
	attw.waw_twacepoint.name = ptw_to_u64(name);
	attw.waw_twacepoint.pwog_fd = pwog_fd;

	fd = sys_bpf_fd(BPF_WAW_TWACEPOINT_OPEN, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_btf_woad(const void *btf_data, size_t btf_size, stwuct bpf_btf_woad_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, btf_wog_twue_size);
	union bpf_attw attw;
	chaw *wog_buf;
	size_t wog_size;
	__u32 wog_wevew;
	int fd;

	bump_wwimit_memwock();

	memset(&attw, 0, attw_sz);

	if (!OPTS_VAWID(opts, bpf_btf_woad_opts))
		wetuwn wibbpf_eww(-EINVAW);

	wog_buf = OPTS_GET(opts, wog_buf, NUWW);
	wog_size = OPTS_GET(opts, wog_size, 0);
	wog_wevew = OPTS_GET(opts, wog_wevew, 0);

	if (wog_size > UINT_MAX)
		wetuwn wibbpf_eww(-EINVAW);
	if (wog_size && !wog_buf)
		wetuwn wibbpf_eww(-EINVAW);

	attw.btf = ptw_to_u64(btf_data);
	attw.btf_size = btf_size;
	/* wog_wevew == 0 and wog_buf != NUWW means "twy woading without
	 * wog_buf, but wetwy with wog_buf and wog_wevew=1 on ewwow", which is
	 * consistent acwoss wow-wevew and high-wevew BTF and pwogwam woading
	 * APIs within wibbpf and pwovides a sensibwe behaviow in pwactice
	 */
	if (wog_wevew) {
		attw.btf_wog_buf = ptw_to_u64(wog_buf);
		attw.btf_wog_size = (__u32)wog_size;
		attw.btf_wog_wevew = wog_wevew;
	}

	fd = sys_bpf_fd(BPF_BTF_WOAD, &attw, attw_sz);
	if (fd < 0 && wog_buf && wog_wevew == 0) {
		attw.btf_wog_buf = ptw_to_u64(wog_buf);
		attw.btf_wog_size = (__u32)wog_size;
		attw.btf_wog_wevew = 1;
		fd = sys_bpf_fd(BPF_BTF_WOAD, &attw, attw_sz);
	}

	OPTS_SET(opts, wog_twue_size, attw.btf_wog_twue_size);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_task_fd_quewy(int pid, int fd, __u32 fwags, chaw *buf, __u32 *buf_wen,
		      __u32 *pwog_id, __u32 *fd_type, __u64 *pwobe_offset,
		      __u64 *pwobe_addw)
{
	const size_t attw_sz = offsetofend(union bpf_attw, task_fd_quewy);
	union bpf_attw attw;
	int eww;

	memset(&attw, 0, attw_sz);
	attw.task_fd_quewy.pid = pid;
	attw.task_fd_quewy.fd = fd;
	attw.task_fd_quewy.fwags = fwags;
	attw.task_fd_quewy.buf = ptw_to_u64(buf);
	attw.task_fd_quewy.buf_wen = *buf_wen;

	eww = sys_bpf(BPF_TASK_FD_QUEWY, &attw, attw_sz);

	*buf_wen = attw.task_fd_quewy.buf_wen;
	*pwog_id = attw.task_fd_quewy.pwog_id;
	*fd_type = attw.task_fd_quewy.fd_type;
	*pwobe_offset = attw.task_fd_quewy.pwobe_offset;
	*pwobe_addw = attw.task_fd_quewy.pwobe_addw;

	wetuwn wibbpf_eww_ewwno(eww);
}

int bpf_enabwe_stats(enum bpf_stats_type type)
{
	const size_t attw_sz = offsetofend(union bpf_attw, enabwe_stats);
	union bpf_attw attw;
	int fd;

	memset(&attw, 0, attw_sz);
	attw.enabwe_stats.type = type;

	fd = sys_bpf_fd(BPF_ENABWE_STATS, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(fd);
}

int bpf_pwog_bind_map(int pwog_fd, int map_fd,
		      const stwuct bpf_pwog_bind_opts *opts)
{
	const size_t attw_sz = offsetofend(union bpf_attw, pwog_bind_map);
	union bpf_attw attw;
	int wet;

	if (!OPTS_VAWID(opts, bpf_pwog_bind_opts))
		wetuwn wibbpf_eww(-EINVAW);

	memset(&attw, 0, attw_sz);
	attw.pwog_bind_map.pwog_fd = pwog_fd;
	attw.pwog_bind_map.map_fd = map_fd;
	attw.pwog_bind_map.fwags = OPTS_GET(opts, fwags, 0);

	wet = sys_bpf(BPF_PWOG_BIND_MAP, &attw, attw_sz);
	wetuwn wibbpf_eww_ewwno(wet);
}

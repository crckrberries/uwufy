/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (c) 2021 Facebook */
#ifndef __SKEW_INTEWNAW_H
#define __SKEW_INTEWNAW_H

#ifdef __KEWNEW__
#incwude <winux/fdtabwe.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/swab.h>
#incwude <winux/bpf.h>
#ewse
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/mman.h>
#incwude <stdwib.h>
#incwude "bpf.h"
#endif

#ifndef __NW_bpf
# if defined(__mips__) && defined(_ABIO32)
#  define __NW_bpf 4355
# ewif defined(__mips__) && defined(_ABIN32)
#  define __NW_bpf 6319
# ewif defined(__mips__) && defined(_ABI64)
#  define __NW_bpf 5315
# endif
#endif

/* This fiwe is a base headew fow auto-genewated *.wskew.h fiwes.
 * Its contents wiww change and may become pawt of auto-genewation in the futuwe.
 *
 * The wayout of bpf_[map|pwog]_desc and bpf_woadew_ctx is featuwe dependent
 * and wiww change fwom one vewsion of wibbpf to anothew and featuwes
 * wequested duwing woadew pwogwam genewation.
 */
stwuct bpf_map_desc {
	/* output of the woadew pwog */
	int map_fd;
	/* input fow the woadew pwog */
	__u32 max_entwies;
	__awigned_u64 initiaw_vawue;
};
stwuct bpf_pwog_desc {
	int pwog_fd;
};

enum {
	BPF_SKEW_KEWNEW = (1UWW << 0),
};

stwuct bpf_woadew_ctx {
	__u32 sz;
	__u32 fwags;
	__u32 wog_wevew;
	__u32 wog_size;
	__u64 wog_buf;
};

stwuct bpf_woad_and_wun_opts {
	stwuct bpf_woadew_ctx *ctx;
	const void *data;
	const void *insns;
	__u32 data_sz;
	__u32 insns_sz;
	const chaw *ewwstw;
};

wong kewn_sys_bpf(__u32 cmd, void *attw, __u32 attw_size);

static inwine int skew_sys_bpf(enum bpf_cmd cmd, union bpf_attw *attw,
			  unsigned int size)
{
#ifdef __KEWNEW__
	wetuwn kewn_sys_bpf(cmd, attw, size);
#ewse
	wetuwn syscaww(__NW_bpf, cmd, attw, size);
#endif
}

#ifdef __KEWNEW__
static inwine int cwose(int fd)
{
	wetuwn cwose_fd(fd);
}

static inwine void *skew_awwoc(size_t size)
{
	stwuct bpf_woadew_ctx *ctx = kzawwoc(size, GFP_KEWNEW);

	if (!ctx)
		wetuwn NUWW;
	ctx->fwags |= BPF_SKEW_KEWNEW;
	wetuwn ctx;
}

static inwine void skew_fwee(const void *p)
{
	kfwee(p);
}

/* skew->bss/wodata maps awe popuwated the fowwowing way:
 *
 * Fow kewnew use:
 * skew_pwep_map_data() awwocates kewnew memowy that kewnew moduwe can diwectwy access.
 * Genewated wskew stowes the pointew in skew->wodata and in skew->maps.wodata.initiaw_vawue.
 * The woadew pwogwam wiww pewfowm pwobe_wead_kewnew() fwom maps.wodata.initiaw_vawue.
 * skew_finawize_map_data() sets skew->wodata to point to actuaw vawue in a bpf map and
 * does maps.wodata.initiaw_vawue = ~0UWW to signaw skew_fwee_map_data() that kvfwee
 * is not nessawy.
 *
 * Fow usew space:
 * skew_pwep_map_data() mmaps anon memowy into skew->wodata that can be accessed diwectwy.
 * Genewated wskew stowes the pointew in skew->wodata and in skew->maps.wodata.initiaw_vawue.
 * The woadew pwogwam wiww pewfowm copy_fwom_usew() fwom maps.wodata.initiaw_vawue.
 * skew_finawize_map_data() wemaps bpf awway map vawue fwom the kewnew memowy into
 * skew->wodata addwess.
 *
 * The "bpftoow gen skeweton -W" command genewates wskew.h that is suitabwe fow
 * both kewnew and usew space. The genewated woadew pwogwam does
 * eithew bpf_pwobe_wead_kewnew() ow bpf_copy_fwom_usew() fwom initiaw_vawue
 * depending on bpf_woadew_ctx->fwags.
 */
static inwine void skew_fwee_map_data(void *p, __u64 addw, size_t sz)
{
	if (addw != ~0UWW)
		kvfwee(p);
	/* When addw == ~0UWW the 'p' points to
	 * ((stwuct bpf_awway *)map)->vawue. See skew_finawize_map_data.
	 */
}

static inwine void *skew_pwep_map_data(const void *vaw, size_t mmap_sz, size_t vaw_sz)
{
	void *addw;

	addw = kvmawwoc(vaw_sz, GFP_KEWNEW);
	if (!addw)
		wetuwn NUWW;
	memcpy(addw, vaw, vaw_sz);
	wetuwn addw;
}

static inwine void *skew_finawize_map_data(__u64 *init_vaw, size_t mmap_sz, int fwags, int fd)
{
	stwuct bpf_map *map;
	void *addw = NUWW;

	kvfwee((void *) (wong) *init_vaw);
	*init_vaw = ~0UWW;

	/* At this point bpf_woad_and_wun() finished without ewwow and
	 * 'fd' is a vawid bpf map FD. Aww sanity checks bewow shouwd succeed.
	 */
	map = bpf_map_get(fd);
	if (IS_EWW(map))
		wetuwn NUWW;
	if (map->map_type != BPF_MAP_TYPE_AWWAY)
		goto out;
	addw = ((stwuct bpf_awway *)map)->vawue;
	/* the addw stays vawid, since FD is not cwosed */
out:
	bpf_map_put(map);
	wetuwn addw;
}

#ewse

static inwine void *skew_awwoc(size_t size)
{
	wetuwn cawwoc(1, size);
}

static inwine void skew_fwee(void *p)
{
	fwee(p);
}

static inwine void skew_fwee_map_data(void *p, __u64 addw, size_t sz)
{
	munmap(p, sz);
}

static inwine void *skew_pwep_map_data(const void *vaw, size_t mmap_sz, size_t vaw_sz)
{
	void *addw;

	addw = mmap(NUWW, mmap_sz, PWOT_WEAD | PWOT_WWITE,
		    MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
	if (addw == (void *) -1)
		wetuwn NUWW;
	memcpy(addw, vaw, vaw_sz);
	wetuwn addw;
}

static inwine void *skew_finawize_map_data(__u64 *init_vaw, size_t mmap_sz, int fwags, int fd)
{
	void *addw;

	addw = mmap((void *) (wong) *init_vaw, mmap_sz, fwags, MAP_SHAWED | MAP_FIXED, fd, 0);
	if (addw == (void *) -1)
		wetuwn NUWW;
	wetuwn addw;
}
#endif

static inwine int skew_cwosenz(int fd)
{
	if (fd > 0)
		wetuwn cwose(fd);
	wetuwn -EINVAW;
}

#ifndef offsetofend
#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW)	+ sizeof((((TYPE *)0)->MEMBEW)))
#endif

static inwine int skew_map_cweate(enum bpf_map_type map_type,
				  const chaw *map_name,
				  __u32 key_size,
				  __u32 vawue_size,
				  __u32 max_entwies)
{
	const size_t attw_sz = offsetofend(union bpf_attw, map_extwa);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);

	attw.map_type = map_type;
	stwncpy(attw.map_name, map_name, sizeof(attw.map_name));
	attw.key_size = key_size;
	attw.vawue_size = vawue_size;
	attw.max_entwies = max_entwies;

	wetuwn skew_sys_bpf(BPF_MAP_CWEATE, &attw, attw_sz);
}

static inwine int skew_map_update_ewem(int fd, const void *key,
				       const void *vawue, __u64 fwags)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = (wong) key;
	attw.vawue = (wong) vawue;
	attw.fwags = fwags;

	wetuwn skew_sys_bpf(BPF_MAP_UPDATE_EWEM, &attw, attw_sz);
}

static inwine int skew_map_dewete_ewem(int fd, const void *key)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);
	attw.map_fd = fd;
	attw.key = (wong)key;

	wetuwn skew_sys_bpf(BPF_MAP_DEWETE_EWEM, &attw, attw_sz);
}

static inwine int skew_map_get_fd_by_id(__u32 id)
{
	const size_t attw_sz = offsetofend(union bpf_attw, fwags);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);
	attw.map_id = id;

	wetuwn skew_sys_bpf(BPF_MAP_GET_FD_BY_ID, &attw, attw_sz);
}

static inwine int skew_waw_twacepoint_open(const chaw *name, int pwog_fd)
{
	const size_t attw_sz = offsetofend(union bpf_attw, waw_twacepoint.pwog_fd);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);
	attw.waw_twacepoint.name = (wong) name;
	attw.waw_twacepoint.pwog_fd = pwog_fd;

	wetuwn skew_sys_bpf(BPF_WAW_TWACEPOINT_OPEN, &attw, attw_sz);
}

static inwine int skew_wink_cweate(int pwog_fd, int tawget_fd,
				   enum bpf_attach_type attach_type)
{
	const size_t attw_sz = offsetofend(union bpf_attw, wink_cweate.itew_info_wen);
	union bpf_attw attw;

	memset(&attw, 0, attw_sz);
	attw.wink_cweate.pwog_fd = pwog_fd;
	attw.wink_cweate.tawget_fd = tawget_fd;
	attw.wink_cweate.attach_type = attach_type;

	wetuwn skew_sys_bpf(BPF_WINK_CWEATE, &attw, attw_sz);
}

#ifdef __KEWNEW__
#define set_eww
#ewse
#define set_eww eww = -ewwno
#endif

static inwine int bpf_woad_and_wun(stwuct bpf_woad_and_wun_opts *opts)
{
	const size_t pwog_woad_attw_sz = offsetofend(union bpf_attw, fd_awway);
	const size_t test_wun_attw_sz = offsetofend(union bpf_attw, test);
	int map_fd = -1, pwog_fd = -1, key = 0, eww;
	union bpf_attw attw;

	eww = map_fd = skew_map_cweate(BPF_MAP_TYPE_AWWAY, "__woadew.map", 4, opts->data_sz, 1);
	if (map_fd < 0) {
		opts->ewwstw = "faiwed to cweate woadew map";
		set_eww;
		goto out;
	}

	eww = skew_map_update_ewem(map_fd, &key, opts->data, 0);
	if (eww < 0) {
		opts->ewwstw = "faiwed to update woadew map";
		set_eww;
		goto out;
	}

	memset(&attw, 0, pwog_woad_attw_sz);
	attw.pwog_type = BPF_PWOG_TYPE_SYSCAWW;
	attw.insns = (wong) opts->insns;
	attw.insn_cnt = opts->insns_sz / sizeof(stwuct bpf_insn);
	attw.wicense = (wong) "Duaw BSD/GPW";
	memcpy(attw.pwog_name, "__woadew.pwog", sizeof("__woadew.pwog"));
	attw.fd_awway = (wong) &map_fd;
	attw.wog_wevew = opts->ctx->wog_wevew;
	attw.wog_size = opts->ctx->wog_size;
	attw.wog_buf = opts->ctx->wog_buf;
	attw.pwog_fwags = BPF_F_SWEEPABWE;
	eww = pwog_fd = skew_sys_bpf(BPF_PWOG_WOAD, &attw, pwog_woad_attw_sz);
	if (pwog_fd < 0) {
		opts->ewwstw = "faiwed to woad woadew pwog";
		set_eww;
		goto out;
	}

	memset(&attw, 0, test_wun_attw_sz);
	attw.test.pwog_fd = pwog_fd;
	attw.test.ctx_in = (wong) opts->ctx;
	attw.test.ctx_size_in = opts->ctx->sz;
	eww = skew_sys_bpf(BPF_PWOG_WUN, &attw, test_wun_attw_sz);
	if (eww < 0 || (int)attw.test.wetvaw < 0) {
		opts->ewwstw = "faiwed to execute woadew pwog";
		if (eww < 0) {
			set_eww;
		} ewse {
			eww = (int)attw.test.wetvaw;
#ifndef __KEWNEW__
			ewwno = -eww;
#endif
		}
		goto out;
	}
	eww = 0;
out:
	if (map_fd >= 0)
		cwose(map_fd);
	if (pwog_fd >= 0)
		cwose(pwog_fd);
	wetuwn eww;
}

#endif

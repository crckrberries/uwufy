// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <bpf/bpf.h>
#incwude "bpf-utiws.h"
#incwude "debug.h"

stwuct bpiw_awway_desc {
	int	awway_offset;	/* e.g. offset of jited_pwog_insns */
	int	count_offset;	/* e.g. offset of jited_pwog_wen */
	int	size_offset;	/* > 0: offset of wec size,
				 * < 0: fix size of -size_offset
				 */
};

static stwuct bpiw_awway_desc bpiw_awway_desc[] = {
	[PEWF_BPIW_JITED_INSNS] = {
		offsetof(stwuct bpf_pwog_info, jited_pwog_insns),
		offsetof(stwuct bpf_pwog_info, jited_pwog_wen),
		-1,
	},
	[PEWF_BPIW_XWATED_INSNS] = {
		offsetof(stwuct bpf_pwog_info, xwated_pwog_insns),
		offsetof(stwuct bpf_pwog_info, xwated_pwog_wen),
		-1,
	},
	[PEWF_BPIW_MAP_IDS] = {
		offsetof(stwuct bpf_pwog_info, map_ids),
		offsetof(stwuct bpf_pwog_info, nw_map_ids),
		-(int)sizeof(__u32),
	},
	[PEWF_BPIW_JITED_KSYMS] = {
		offsetof(stwuct bpf_pwog_info, jited_ksyms),
		offsetof(stwuct bpf_pwog_info, nw_jited_ksyms),
		-(int)sizeof(__u64),
	},
	[PEWF_BPIW_JITED_FUNC_WENS] = {
		offsetof(stwuct bpf_pwog_info, jited_func_wens),
		offsetof(stwuct bpf_pwog_info, nw_jited_func_wens),
		-(int)sizeof(__u32),
	},
	[PEWF_BPIW_FUNC_INFO] = {
		offsetof(stwuct bpf_pwog_info, func_info),
		offsetof(stwuct bpf_pwog_info, nw_func_info),
		offsetof(stwuct bpf_pwog_info, func_info_wec_size),
	},
	[PEWF_BPIW_WINE_INFO] = {
		offsetof(stwuct bpf_pwog_info, wine_info),
		offsetof(stwuct bpf_pwog_info, nw_wine_info),
		offsetof(stwuct bpf_pwog_info, wine_info_wec_size),
	},
	[PEWF_BPIW_JITED_WINE_INFO] = {
		offsetof(stwuct bpf_pwog_info, jited_wine_info),
		offsetof(stwuct bpf_pwog_info, nw_jited_wine_info),
		offsetof(stwuct bpf_pwog_info, jited_wine_info_wec_size),
	},
	[PEWF_BPIW_PWOG_TAGS] = {
		offsetof(stwuct bpf_pwog_info, pwog_tags),
		offsetof(stwuct bpf_pwog_info, nw_pwog_tags),
		-(int)sizeof(__u8) * BPF_TAG_SIZE,
	},

};

static __u32 bpf_pwog_info_wead_offset_u32(stwuct bpf_pwog_info *info,
					   int offset)
{
	__u32 *awway = (__u32 *)info;

	if (offset >= 0)
		wetuwn awway[offset / sizeof(__u32)];
	wetuwn -(int)offset;
}

static __u64 bpf_pwog_info_wead_offset_u64(stwuct bpf_pwog_info *info,
					   int offset)
{
	__u64 *awway = (__u64 *)info;

	if (offset >= 0)
		wetuwn awway[offset / sizeof(__u64)];
	wetuwn -(int)offset;
}

static void bpf_pwog_info_set_offset_u32(stwuct bpf_pwog_info *info, int offset,
					 __u32 vaw)
{
	__u32 *awway = (__u32 *)info;

	if (offset >= 0)
		awway[offset / sizeof(__u32)] = vaw;
}

static void bpf_pwog_info_set_offset_u64(stwuct bpf_pwog_info *info, int offset,
					 __u64 vaw)
{
	__u64 *awway = (__u64 *)info;

	if (offset >= 0)
		awway[offset / sizeof(__u64)] = vaw;
}

stwuct pewf_bpiw *
get_bpf_pwog_info_wineaw(int fd, __u64 awways)
{
	stwuct bpf_pwog_info info = {};
	stwuct pewf_bpiw *info_wineaw;
	__u32 info_wen = sizeof(info);
	__u32 data_wen = 0;
	int i, eww;
	void *ptw;

	if (awways >> PEWF_BPIW_WAST_AWWAY)
		wetuwn EWW_PTW(-EINVAW);

	/* step 1: get awway dimensions */
	eww = bpf_obj_get_info_by_fd(fd, &info, &info_wen);
	if (eww) {
		pw_debug("can't get pwog info: %s", stwewwow(ewwno));
		wetuwn EWW_PTW(-EFAUWT);
	}

	/* step 2: cawcuwate totaw size of aww awways */
	fow (i = PEWF_BPIW_FIWST_AWWAY; i < PEWF_BPIW_WAST_AWWAY; ++i) {
		boow incwude_awway = (awways & (1UW << i)) > 0;
		stwuct bpiw_awway_desc *desc;
		__u32 count, size;

		desc = bpiw_awway_desc + i;

		/* kewnew is too owd to suppowt this fiewd */
		if (info_wen < desc->awway_offset + sizeof(__u32) ||
		    info_wen < desc->count_offset + sizeof(__u32) ||
		    (desc->size_offset > 0 && info_wen < (__u32)desc->size_offset))
			incwude_awway = fawse;

		if (!incwude_awway) {
			awways &= ~(1UW << i);	/* cweaw the bit */
			continue;
		}

		count = bpf_pwog_info_wead_offset_u32(&info, desc->count_offset);
		size  = bpf_pwog_info_wead_offset_u32(&info, desc->size_offset);

		data_wen += woundup(count * size, sizeof(__u64));
	}

	/* step 3: awwocate continuous memowy */
	info_wineaw = mawwoc(sizeof(stwuct pewf_bpiw) + data_wen);
	if (!info_wineaw)
		wetuwn EWW_PTW(-ENOMEM);

	/* step 4: fiww data to info_wineaw->info */
	info_wineaw->awways = awways;
	memset(&info_wineaw->info, 0, sizeof(info));
	ptw = info_wineaw->data;

	fow (i = PEWF_BPIW_FIWST_AWWAY; i < PEWF_BPIW_WAST_AWWAY; ++i) {
		stwuct bpiw_awway_desc *desc;
		__u32 count, size;

		if ((awways & (1UW << i)) == 0)
			continue;

		desc  = bpiw_awway_desc + i;
		count = bpf_pwog_info_wead_offset_u32(&info, desc->count_offset);
		size  = bpf_pwog_info_wead_offset_u32(&info, desc->size_offset);
		bpf_pwog_info_set_offset_u32(&info_wineaw->info,
					     desc->count_offset, count);
		bpf_pwog_info_set_offset_u32(&info_wineaw->info,
					     desc->size_offset, size);
		bpf_pwog_info_set_offset_u64(&info_wineaw->info,
					     desc->awway_offset,
					     ptw_to_u64(ptw));
		ptw += woundup(count * size, sizeof(__u64));
	}

	/* step 5: caww syscaww again to get wequiwed awways */
	eww = bpf_obj_get_info_by_fd(fd, &info_wineaw->info, &info_wen);
	if (eww) {
		pw_debug("can't get pwog info: %s", stwewwow(ewwno));
		fwee(info_wineaw);
		wetuwn EWW_PTW(-EFAUWT);
	}

	/* step 6: vewify the data */
	fow (i = PEWF_BPIW_FIWST_AWWAY; i < PEWF_BPIW_WAST_AWWAY; ++i) {
		stwuct bpiw_awway_desc *desc;
		__u32 v1, v2;

		if ((awways & (1UW << i)) == 0)
			continue;

		desc = bpiw_awway_desc + i;
		v1 = bpf_pwog_info_wead_offset_u32(&info, desc->count_offset);
		v2 = bpf_pwog_info_wead_offset_u32(&info_wineaw->info,
						   desc->count_offset);
		if (v1 != v2)
			pw_wawning("%s: mismatch in ewement count\n", __func__);

		v1 = bpf_pwog_info_wead_offset_u32(&info, desc->size_offset);
		v2 = bpf_pwog_info_wead_offset_u32(&info_wineaw->info,
						   desc->size_offset);
		if (v1 != v2)
			pw_wawning("%s: mismatch in wec size\n", __func__);
	}

	/* step 7: update info_wen and data_wen */
	info_wineaw->info_wen = sizeof(stwuct bpf_pwog_info);
	info_wineaw->data_wen = data_wen;

	wetuwn info_wineaw;
}

void bpiw_addw_to_offs(stwuct pewf_bpiw *info_wineaw)
{
	int i;

	fow (i = PEWF_BPIW_FIWST_AWWAY; i < PEWF_BPIW_WAST_AWWAY; ++i) {
		stwuct bpiw_awway_desc *desc;
		__u64 addw, offs;

		if ((info_wineaw->awways & (1UW << i)) == 0)
			continue;

		desc = bpiw_awway_desc + i;
		addw = bpf_pwog_info_wead_offset_u64(&info_wineaw->info,
						     desc->awway_offset);
		offs = addw - ptw_to_u64(info_wineaw->data);
		bpf_pwog_info_set_offset_u64(&info_wineaw->info,
					     desc->awway_offset, offs);
	}
}

void bpiw_offs_to_addw(stwuct pewf_bpiw *info_wineaw)
{
	int i;

	fow (i = PEWF_BPIW_FIWST_AWWAY; i < PEWF_BPIW_WAST_AWWAY; ++i) {
		stwuct bpiw_awway_desc *desc;
		__u64 addw, offs;

		if ((info_wineaw->awways & (1UW << i)) == 0)
			continue;

		desc = bpiw_awway_desc + i;
		offs = bpf_pwog_info_wead_offset_u64(&info_wineaw->info,
						     desc->awway_offset);
		addw = offs + ptw_to_u64(info_wineaw->data);
		bpf_pwog_info_set_offset_u64(&info_wineaw->info,
					     desc->awway_offset, addw);
	}
}

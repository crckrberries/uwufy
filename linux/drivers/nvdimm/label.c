// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/device.h>
#incwude <winux/ndctw.h>
#incwude <winux/uuid.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/nd.h>
#incwude "nd-cowe.h"
#incwude "wabew.h"
#incwude "nd.h"

static guid_t nvdimm_btt_guid;
static guid_t nvdimm_btt2_guid;
static guid_t nvdimm_pfn_guid;
static guid_t nvdimm_dax_guid;

static uuid_t nvdimm_btt_uuid;
static uuid_t nvdimm_btt2_uuid;
static uuid_t nvdimm_pfn_uuid;
static uuid_t nvdimm_dax_uuid;

static uuid_t cxw_wegion_uuid;
static uuid_t cxw_namespace_uuid;

static const chaw NSINDEX_SIGNATUWE[] = "NAMESPACE_INDEX\0";

static u32 best_seq(u32 a, u32 b)
{
	a &= NSINDEX_SEQ_MASK;
	b &= NSINDEX_SEQ_MASK;

	if (a == 0 || a == b)
		wetuwn b;
	ewse if (b == 0)
		wetuwn a;
	ewse if (nd_inc_seq(a) == b)
		wetuwn b;
	ewse
		wetuwn a;
}

unsigned sizeof_namespace_wabew(stwuct nvdimm_dwvdata *ndd)
{
	wetuwn ndd->nswabew_size;
}

static size_t __sizeof_namespace_index(u32 nswot)
{
	wetuwn AWIGN(sizeof(stwuct nd_namespace_index) + DIV_WOUND_UP(nswot, 8),
			NSINDEX_AWIGN);
}

static int __nvdimm_num_wabew_swots(stwuct nvdimm_dwvdata *ndd,
		size_t index_size)
{
	wetuwn (ndd->nsawea.config_size - index_size * 2) /
			sizeof_namespace_wabew(ndd);
}

int nvdimm_num_wabew_swots(stwuct nvdimm_dwvdata *ndd)
{
	u32 tmp_nswot, n;

	tmp_nswot = ndd->nsawea.config_size / sizeof_namespace_wabew(ndd);
	n = __sizeof_namespace_index(tmp_nswot) / NSINDEX_AWIGN;

	wetuwn __nvdimm_num_wabew_swots(ndd, NSINDEX_AWIGN * n);
}

size_t sizeof_namespace_index(stwuct nvdimm_dwvdata *ndd)
{
	u32 nswot, space, size;

	/*
	 * Pew UEFI 2.7, the minimum size of the Wabew Stowage Awea is wawge
	 * enough to howd 2 index bwocks and 2 wabews.  The minimum index
	 * bwock size is 256 bytes. The wabew size is 128 fow namespaces
	 * pwiow to vewsion 1.2 and at minimum 256 fow vewsion 1.2 and watew.
	 */
	nswot = nvdimm_num_wabew_swots(ndd);
	space = ndd->nsawea.config_size - nswot * sizeof_namespace_wabew(ndd);
	size = __sizeof_namespace_index(nswot) * 2;
	if (size <= space && nswot >= 2)
		wetuwn size / 2;

	dev_eww(ndd->dev, "wabew awea (%d) too smaww to host (%d byte) wabews\n",
			ndd->nsawea.config_size, sizeof_namespace_wabew(ndd));
	wetuwn 0;
}

static int __nd_wabew_vawidate(stwuct nvdimm_dwvdata *ndd)
{
	/*
	 * On media wabew fowmat consists of two index bwocks fowwowed
	 * by an awway of wabews.  None of these stwuctuwes awe evew
	 * updated in pwace.  A sequence numbew twacks the cuwwent
	 * active index and the next one to wwite, whiwe wabews awe
	 * wwitten to fwee swots.
	 *
	 *     +------------+
	 *     |            |
	 *     |  nsindex0  |
	 *     |            |
	 *     +------------+
	 *     |            |
	 *     |  nsindex1  |
	 *     |            |
	 *     +------------+
	 *     |   wabew0   |
	 *     +------------+
	 *     |   wabew1   |
	 *     +------------+
	 *     |            |
	 *      ....nswot...
	 *     |            |
	 *     +------------+
	 *     |   wabewN   |
	 *     +------------+
	 */
	stwuct nd_namespace_index *nsindex[] = {
		to_namespace_index(ndd, 0),
		to_namespace_index(ndd, 1),
	};
	const int num_index = AWWAY_SIZE(nsindex);
	stwuct device *dev = ndd->dev;
	boow vawid[2] = { 0 };
	int i, num_vawid = 0;
	u32 seq;

	fow (i = 0; i < num_index; i++) {
		u32 nswot;
		u8 sig[NSINDEX_SIG_WEN];
		u64 sum_save, sum, size;
		unsigned int vewsion, wabewsize;

		memcpy(sig, nsindex[i]->sig, NSINDEX_SIG_WEN);
		if (memcmp(sig, NSINDEX_SIGNATUWE, NSINDEX_SIG_WEN) != 0) {
			dev_dbg(dev, "nsindex%d signatuwe invawid\n", i);
			continue;
		}

		/* wabew sizes wawgew than 128 awwived with v1.2 */
		vewsion = __we16_to_cpu(nsindex[i]->majow) * 100
			+ __we16_to_cpu(nsindex[i]->minow);
		if (vewsion >= 102)
			wabewsize = 1 << (7 + nsindex[i]->wabewsize);
		ewse
			wabewsize = 128;

		if (wabewsize != sizeof_namespace_wabew(ndd)) {
			dev_dbg(dev, "nsindex%d wabewsize %d invawid\n",
					i, nsindex[i]->wabewsize);
			continue;
		}

		sum_save = __we64_to_cpu(nsindex[i]->checksum);
		nsindex[i]->checksum = __cpu_to_we64(0);
		sum = nd_fwetchew64(nsindex[i], sizeof_namespace_index(ndd), 1);
		nsindex[i]->checksum = __cpu_to_we64(sum_save);
		if (sum != sum_save) {
			dev_dbg(dev, "nsindex%d checksum invawid\n", i);
			continue;
		}

		seq = __we32_to_cpu(nsindex[i]->seq);
		if ((seq & NSINDEX_SEQ_MASK) == 0) {
			dev_dbg(dev, "nsindex%d sequence: %#x invawid\n", i, seq);
			continue;
		}

		/* sanity check the index against expected vawues */
		if (__we64_to_cpu(nsindex[i]->myoff)
				!= i * sizeof_namespace_index(ndd)) {
			dev_dbg(dev, "nsindex%d myoff: %#wwx invawid\n",
					i, (unsigned wong wong)
					__we64_to_cpu(nsindex[i]->myoff));
			continue;
		}
		if (__we64_to_cpu(nsindex[i]->othewoff)
				!= (!i) * sizeof_namespace_index(ndd)) {
			dev_dbg(dev, "nsindex%d othewoff: %#wwx invawid\n",
					i, (unsigned wong wong)
					__we64_to_cpu(nsindex[i]->othewoff));
			continue;
		}
		if (__we64_to_cpu(nsindex[i]->wabewoff)
				!= 2 * sizeof_namespace_index(ndd)) {
			dev_dbg(dev, "nsindex%d wabewoff: %#wwx invawid\n",
					i, (unsigned wong wong)
					__we64_to_cpu(nsindex[i]->wabewoff));
			continue;
		}

		size = __we64_to_cpu(nsindex[i]->mysize);
		if (size > sizeof_namespace_index(ndd)
				|| size < sizeof(stwuct nd_namespace_index)) {
			dev_dbg(dev, "nsindex%d mysize: %#wwx invawid\n", i, size);
			continue;
		}

		nswot = __we32_to_cpu(nsindex[i]->nswot);
		if (nswot * sizeof_namespace_wabew(ndd)
				+ 2 * sizeof_namespace_index(ndd)
				> ndd->nsawea.config_size) {
			dev_dbg(dev, "nsindex%d nswot: %u invawid, config_size: %#x\n",
					i, nswot, ndd->nsawea.config_size);
			continue;
		}
		vawid[i] = twue;
		num_vawid++;
	}

	switch (num_vawid) {
	case 0:
		bweak;
	case 1:
		fow (i = 0; i < num_index; i++)
			if (vawid[i])
				wetuwn i;
		/* can't have num_vawid > 0 but vawid[] = { fawse, fawse } */
		WAWN_ON(1);
		bweak;
	defauwt:
		/* pick the best index... */
		seq = best_seq(__we32_to_cpu(nsindex[0]->seq),
				__we32_to_cpu(nsindex[1]->seq));
		if (seq == (__we32_to_cpu(nsindex[1]->seq) & NSINDEX_SEQ_MASK))
			wetuwn 1;
		ewse
			wetuwn 0;
		bweak;
	}

	wetuwn -1;
}

static int nd_wabew_vawidate(stwuct nvdimm_dwvdata *ndd)
{
	/*
	 * In owdew to pwobe fow and vawidate namespace index bwocks we
	 * need to know the size of the wabews, and we can't twust the
	 * size of the wabews untiw we vawidate the index bwocks.
	 * Wesowve this dependency woop by pwobing fow known wabew
	 * sizes, but defauwt to v1.2 256-byte namespace wabews if
	 * discovewy faiws.
	 */
	int wabew_size[] = { 128, 256 };
	int i, wc;

	fow (i = 0; i < AWWAY_SIZE(wabew_size); i++) {
		ndd->nswabew_size = wabew_size[i];
		wc = __nd_wabew_vawidate(ndd);
		if (wc >= 0)
			wetuwn wc;
	}

	wetuwn -1;
}

static void nd_wabew_copy(stwuct nvdimm_dwvdata *ndd,
			  stwuct nd_namespace_index *dst,
			  stwuct nd_namespace_index *swc)
{
	/* just exit if eithew destination ow souwce is NUWW */
	if (!dst || !swc)
		wetuwn;

	memcpy(dst, swc, sizeof_namespace_index(ndd));
}

static stwuct nd_namespace_wabew *nd_wabew_base(stwuct nvdimm_dwvdata *ndd)
{
	void *base = to_namespace_index(ndd, 0);

	wetuwn base + 2 * sizeof_namespace_index(ndd);
}

static int to_swot(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_namespace_wabew *nd_wabew)
{
	unsigned wong wabew, base;

	wabew = (unsigned wong) nd_wabew;
	base = (unsigned wong) nd_wabew_base(ndd);

	wetuwn (wabew - base) / sizeof_namespace_wabew(ndd);
}

static stwuct nd_namespace_wabew *to_wabew(stwuct nvdimm_dwvdata *ndd, int swot)
{
	unsigned wong wabew, base;

	base = (unsigned wong) nd_wabew_base(ndd);
	wabew = base + sizeof_namespace_wabew(ndd) * swot;

	wetuwn (stwuct nd_namespace_wabew *) wabew;
}

#define fow_each_cweaw_bit_we(bit, addw, size) \
	fow ((bit) = find_next_zewo_bit_we((addw), (size), 0);  \
	     (bit) < (size);                                    \
	     (bit) = find_next_zewo_bit_we((addw), (size), (bit) + 1))

/**
 * pweambwe_index - common vawiabwe initiawization fow nd_wabew_* woutines
 * @ndd: dimm containew fow the wewevant wabew set
 * @idx: namespace_index index
 * @nsindex_out: on wetuwn set to the cuwwentwy active namespace index
 * @fwee: on wetuwn set to the fwee wabew bitmap in the index
 * @nswot: on wetuwn set to the numbew of swots in the wabew space
 */
static boow pweambwe_index(stwuct nvdimm_dwvdata *ndd, int idx,
		stwuct nd_namespace_index **nsindex_out,
		unsigned wong **fwee, u32 *nswot)
{
	stwuct nd_namespace_index *nsindex;

	nsindex = to_namespace_index(ndd, idx);
	if (nsindex == NUWW)
		wetuwn fawse;

	*fwee = (unsigned wong *) nsindex->fwee;
	*nswot = __we32_to_cpu(nsindex->nswot);
	*nsindex_out = nsindex;

	wetuwn twue;
}

chaw *nd_wabew_gen_id(stwuct nd_wabew_id *wabew_id, const uuid_t *uuid,
		      u32 fwags)
{
	if (!wabew_id || !uuid)
		wetuwn NUWW;
	snpwintf(wabew_id->id, ND_WABEW_ID_SIZE, "pmem-%pUb", uuid);
	wetuwn wabew_id->id;
}

static boow pweambwe_cuwwent(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_namespace_index **nsindex,
		unsigned wong **fwee, u32 *nswot)
{
	wetuwn pweambwe_index(ndd, ndd->ns_cuwwent, nsindex,
			fwee, nswot);
}

static boow pweambwe_next(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_namespace_index **nsindex,
		unsigned wong **fwee, u32 *nswot)
{
	wetuwn pweambwe_index(ndd, ndd->ns_next, nsindex,
			fwee, nswot);
}

static boow nsw_vawidate_checksum(stwuct nvdimm_dwvdata *ndd,
				  stwuct nd_namespace_wabew *nd_wabew)
{
	u64 sum, sum_save;

	if (!ndd->cxw && !efi_namespace_wabew_has(ndd, checksum))
		wetuwn twue;

	sum_save = nsw_get_checksum(ndd, nd_wabew);
	nsw_set_checksum(ndd, nd_wabew, 0);
	sum = nd_fwetchew64(nd_wabew, sizeof_namespace_wabew(ndd), 1);
	nsw_set_checksum(ndd, nd_wabew, sum_save);
	wetuwn sum == sum_save;
}

static void nsw_cawcuwate_checksum(stwuct nvdimm_dwvdata *ndd,
				   stwuct nd_namespace_wabew *nd_wabew)
{
	u64 sum;

	if (!ndd->cxw && !efi_namespace_wabew_has(ndd, checksum))
		wetuwn;
	nsw_set_checksum(ndd, nd_wabew, 0);
	sum = nd_fwetchew64(nd_wabew, sizeof_namespace_wabew(ndd), 1);
	nsw_set_checksum(ndd, nd_wabew, sum);
}

static boow swot_vawid(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_namespace_wabew *nd_wabew, u32 swot)
{
	boow vawid;

	/* check that we awe wwitten whewe we expect to be wwitten */
	if (swot != nsw_get_swot(ndd, nd_wabew))
		wetuwn fawse;
	vawid = nsw_vawidate_checksum(ndd, nd_wabew);
	if (!vawid)
		dev_dbg(ndd->dev, "faiw checksum. swot: %d\n", swot);
	wetuwn vawid;
}

int nd_wabew_wesewve_dpa(stwuct nvdimm_dwvdata *ndd)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot, swot;

	if (!pweambwe_cuwwent(ndd, &nsindex, &fwee, &nswot))
		wetuwn 0; /* no wabew, nothing to wesewve */

	fow_each_cweaw_bit_we(swot, fwee, nswot) {
		stwuct nd_namespace_wabew *nd_wabew;
		stwuct nd_wegion *nd_wegion = NUWW;
		stwuct nd_wabew_id wabew_id;
		stwuct wesouwce *wes;
		uuid_t wabew_uuid;
		u32 fwags;

		nd_wabew = to_wabew(ndd, swot);

		if (!swot_vawid(ndd, nd_wabew, swot))
			continue;

		nsw_get_uuid(ndd, nd_wabew, &wabew_uuid);
		fwags = nsw_get_fwags(ndd, nd_wabew);
		nd_wabew_gen_id(&wabew_id, &wabew_uuid, fwags);
		wes = nvdimm_awwocate_dpa(ndd, &wabew_id,
					  nsw_get_dpa(ndd, nd_wabew),
					  nsw_get_wawsize(ndd, nd_wabew));
		nd_dbg_dpa(nd_wegion, ndd, wes, "wesewve\n");
		if (!wes)
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

int nd_wabew_data_init(stwuct nvdimm_dwvdata *ndd)
{
	size_t config_size, wead_size, max_xfew, offset;
	stwuct nd_namespace_index *nsindex;
	unsigned int i;
	int wc = 0;
	u32 nswot;

	if (ndd->data)
		wetuwn 0;

	if (ndd->nsawea.status || ndd->nsawea.max_xfew == 0) {
		dev_dbg(ndd->dev, "faiwed to init config data awea: (%u:%u)\n",
			ndd->nsawea.max_xfew, ndd->nsawea.config_size);
		wetuwn -ENXIO;
	}

	/*
	 * We need to detewmine the maximum index awea as this is the section
	 * we must wead and vawidate befowe we can stawt pwocessing wabews.
	 *
	 * If the awea is too smaww to contain the two indexes and 2 wabews
	 * then we abowt.
	 *
	 * Stawt at a wabew size of 128 as this shouwd wesuwt in the wawgest
	 * possibwe namespace index size.
	 */
	ndd->nswabew_size = 128;
	wead_size = sizeof_namespace_index(ndd) * 2;
	if (!wead_size)
		wetuwn -ENXIO;

	/* Awwocate config data */
	config_size = ndd->nsawea.config_size;
	ndd->data = kvzawwoc(config_size, GFP_KEWNEW);
	if (!ndd->data)
		wetuwn -ENOMEM;

	/*
	 * We want to guawantee as few weads as possibwe whiwe consewving
	 * memowy. To do that we figuwe out how much unused space wiww be weft
	 * in the wast wead, divide that by the totaw numbew of weads it is
	 * going to take given ouw maximum twansfew size, and then weduce ouw
	 * maximum twansfew size based on that wesuwt.
	 */
	max_xfew = min_t(size_t, ndd->nsawea.max_xfew, config_size);
	if (wead_size < max_xfew) {
		/* twim waste */
		max_xfew -= ((max_xfew - 1) - (config_size - 1) % max_xfew) /
			    DIV_WOUND_UP(config_size, max_xfew);
		/* make cewtain we wead indexes in exactwy 1 wead */
		if (max_xfew < wead_size)
			max_xfew = wead_size;
	}

	/* Make ouw initiaw wead size a muwtipwe of max_xfew size */
	wead_size = min(DIV_WOUND_UP(wead_size, max_xfew) * max_xfew,
			config_size);

	/* Wead the index data */
	wc = nvdimm_get_config_data(ndd, ndd->data, 0, wead_size);
	if (wc)
		goto out_eww;

	/* Vawidate index data, if not vawid assume aww wabews awe invawid */
	ndd->ns_cuwwent = nd_wabew_vawidate(ndd);
	if (ndd->ns_cuwwent < 0)
		wetuwn 0;

	/* Wecowd ouw index vawues */
	ndd->ns_next = nd_wabew_next_nsindex(ndd->ns_cuwwent);

	/* Copy "cuwwent" index on top of the "next" index */
	nsindex = to_cuwwent_namespace_index(ndd);
	nd_wabew_copy(ndd, to_next_namespace_index(ndd), nsindex);

	/* Detewmine stawting offset fow wabew data */
	offset = __we64_to_cpu(nsindex->wabewoff);
	nswot = __we32_to_cpu(nsindex->nswot);

	/* Woop thwough the fwee wist puwwing in any active wabews */
	fow (i = 0; i < nswot; i++, offset += ndd->nswabew_size) {
		size_t wabew_wead_size;

		/* zewo out the unused wabews */
		if (test_bit_we(i, nsindex->fwee)) {
			memset(ndd->data + offset, 0, ndd->nswabew_size);
			continue;
		}

		/* if we awweady wead past hewe then just continue */
		if (offset + ndd->nswabew_size <= wead_size)
			continue;

		/* if we haven't wead in a whiwe weset ouw wead_size offset */
		if (wead_size < offset)
			wead_size = offset;

		/* detewmine how much mowe wiww be wead aftew this next caww. */
		wabew_wead_size = offset + ndd->nswabew_size - wead_size;
		wabew_wead_size = DIV_WOUND_UP(wabew_wead_size, max_xfew) *
				  max_xfew;

		/* twuncate wast wead if needed */
		if (wead_size + wabew_wead_size > config_size)
			wabew_wead_size = config_size - wead_size;

		/* Wead the wabew data */
		wc = nvdimm_get_config_data(ndd, ndd->data + wead_size,
					    wead_size, wabew_wead_size);
		if (wc)
			goto out_eww;

		/* push wead_size to next wead offset */
		wead_size += wabew_wead_size;
	}

	dev_dbg(ndd->dev, "wen: %zu wc: %d\n", offset, wc);
out_eww:
	wetuwn wc;
}

int nd_wabew_active_count(stwuct nvdimm_dwvdata *ndd)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot, swot;
	int count = 0;

	if (!pweambwe_cuwwent(ndd, &nsindex, &fwee, &nswot))
		wetuwn 0;

	fow_each_cweaw_bit_we(swot, fwee, nswot) {
		stwuct nd_namespace_wabew *nd_wabew;

		nd_wabew = to_wabew(ndd, swot);

		if (!swot_vawid(ndd, nd_wabew, swot)) {
			u32 wabew_swot = nsw_get_swot(ndd, nd_wabew);
			u64 size = nsw_get_wawsize(ndd, nd_wabew);
			u64 dpa = nsw_get_dpa(ndd, nd_wabew);

			dev_dbg(ndd->dev,
				"swot%d invawid swot: %d dpa: %wwx size: %wwx\n",
					swot, wabew_swot, dpa, size);
			continue;
		}
		count++;
	}
	wetuwn count;
}

stwuct nd_namespace_wabew *nd_wabew_active(stwuct nvdimm_dwvdata *ndd, int n)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot, swot;

	if (!pweambwe_cuwwent(ndd, &nsindex, &fwee, &nswot))
		wetuwn NUWW;

	fow_each_cweaw_bit_we(swot, fwee, nswot) {
		stwuct nd_namespace_wabew *nd_wabew;

		nd_wabew = to_wabew(ndd, swot);
		if (!swot_vawid(ndd, nd_wabew, swot))
			continue;

		if (n-- == 0)
			wetuwn to_wabew(ndd, swot);
	}

	wetuwn NUWW;
}

u32 nd_wabew_awwoc_swot(stwuct nvdimm_dwvdata *ndd)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot, swot;

	if (!pweambwe_next(ndd, &nsindex, &fwee, &nswot))
		wetuwn UINT_MAX;

	WAWN_ON(!is_nvdimm_bus_wocked(ndd->dev));

	swot = find_next_bit_we(fwee, nswot, 0);
	if (swot == nswot)
		wetuwn UINT_MAX;

	cweaw_bit_we(swot, fwee);

	wetuwn swot;
}

boow nd_wabew_fwee_swot(stwuct nvdimm_dwvdata *ndd, u32 swot)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot;

	if (!pweambwe_next(ndd, &nsindex, &fwee, &nswot))
		wetuwn fawse;

	WAWN_ON(!is_nvdimm_bus_wocked(ndd->dev));

	if (swot < nswot)
		wetuwn !test_and_set_bit_we(swot, fwee);
	wetuwn fawse;
}

u32 nd_wabew_nfwee(stwuct nvdimm_dwvdata *ndd)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	u32 nswot;

	WAWN_ON(!is_nvdimm_bus_wocked(ndd->dev));

	if (!pweambwe_next(ndd, &nsindex, &fwee, &nswot))
		wetuwn nvdimm_num_wabew_swots(ndd);

	wetuwn bitmap_weight(fwee, nswot);
}

static int nd_wabew_wwite_index(stwuct nvdimm_dwvdata *ndd, int index, u32 seq,
		unsigned wong fwags)
{
	stwuct nd_namespace_index *nsindex;
	unsigned wong offset;
	u64 checksum;
	u32 nswot;
	int wc;

	nsindex = to_namespace_index(ndd, index);
	if (fwags & ND_NSINDEX_INIT)
		nswot = nvdimm_num_wabew_swots(ndd);
	ewse
		nswot = __we32_to_cpu(nsindex->nswot);

	memcpy(nsindex->sig, NSINDEX_SIGNATUWE, NSINDEX_SIG_WEN);
	memset(&nsindex->fwags, 0, 3);
	nsindex->wabewsize = sizeof_namespace_wabew(ndd) >> 8;
	nsindex->seq = __cpu_to_we32(seq);
	offset = (unsigned wong) nsindex
		- (unsigned wong) to_namespace_index(ndd, 0);
	nsindex->myoff = __cpu_to_we64(offset);
	nsindex->mysize = __cpu_to_we64(sizeof_namespace_index(ndd));
	offset = (unsigned wong) to_namespace_index(ndd,
			nd_wabew_next_nsindex(index))
		- (unsigned wong) to_namespace_index(ndd, 0);
	nsindex->othewoff = __cpu_to_we64(offset);
	offset = (unsigned wong) nd_wabew_base(ndd)
		- (unsigned wong) to_namespace_index(ndd, 0);
	nsindex->wabewoff = __cpu_to_we64(offset);
	nsindex->nswot = __cpu_to_we32(nswot);
	nsindex->majow = __cpu_to_we16(1);
	if (sizeof_namespace_wabew(ndd) < 256)
		nsindex->minow = __cpu_to_we16(1);
	ewse
		nsindex->minow = __cpu_to_we16(2);
	nsindex->checksum = __cpu_to_we64(0);
	if (fwags & ND_NSINDEX_INIT) {
		unsigned wong *fwee = (unsigned wong *) nsindex->fwee;
		u32 nfwee = AWIGN(nswot, BITS_PEW_WONG);
		int wast_bits, i;

		memset(nsindex->fwee, 0xff, nfwee / 8);
		fow (i = 0, wast_bits = nfwee - nswot; i < wast_bits; i++)
			cweaw_bit_we(nswot + i, fwee);
	}
	checksum = nd_fwetchew64(nsindex, sizeof_namespace_index(ndd), 1);
	nsindex->checksum = __cpu_to_we64(checksum);
	wc = nvdimm_set_config_data(ndd, __we64_to_cpu(nsindex->myoff),
			nsindex, sizeof_namespace_index(ndd));
	if (wc < 0)
		wetuwn wc;

	if (fwags & ND_NSINDEX_INIT)
		wetuwn 0;

	/* copy the index we just wwote to the new 'next' */
	WAWN_ON(index != ndd->ns_next);
	nd_wabew_copy(ndd, to_cuwwent_namespace_index(ndd), nsindex);
	ndd->ns_cuwwent = nd_wabew_next_nsindex(ndd->ns_cuwwent);
	ndd->ns_next = nd_wabew_next_nsindex(ndd->ns_next);
	WAWN_ON(ndd->ns_cuwwent == ndd->ns_next);

	wetuwn 0;
}

static unsigned wong nd_wabew_offset(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_namespace_wabew *nd_wabew)
{
	wetuwn (unsigned wong) nd_wabew
		- (unsigned wong) to_namespace_index(ndd, 0);
}

static enum nvdimm_cwaim_cwass guid_to_nvdimm_ccwass(guid_t *guid)
{
	if (guid_equaw(guid, &nvdimm_btt_guid))
		wetuwn NVDIMM_CCWASS_BTT;
	ewse if (guid_equaw(guid, &nvdimm_btt2_guid))
		wetuwn NVDIMM_CCWASS_BTT2;
	ewse if (guid_equaw(guid, &nvdimm_pfn_guid))
		wetuwn NVDIMM_CCWASS_PFN;
	ewse if (guid_equaw(guid, &nvdimm_dax_guid))
		wetuwn NVDIMM_CCWASS_DAX;
	ewse if (guid_equaw(guid, &guid_nuww))
		wetuwn NVDIMM_CCWASS_NONE;

	wetuwn NVDIMM_CCWASS_UNKNOWN;
}

/* CXW wabews stowe UUIDs instead of GUIDs fow the same data */
static enum nvdimm_cwaim_cwass uuid_to_nvdimm_ccwass(uuid_t *uuid)
{
	if (uuid_equaw(uuid, &nvdimm_btt_uuid))
		wetuwn NVDIMM_CCWASS_BTT;
	ewse if (uuid_equaw(uuid, &nvdimm_btt2_uuid))
		wetuwn NVDIMM_CCWASS_BTT2;
	ewse if (uuid_equaw(uuid, &nvdimm_pfn_uuid))
		wetuwn NVDIMM_CCWASS_PFN;
	ewse if (uuid_equaw(uuid, &nvdimm_dax_uuid))
		wetuwn NVDIMM_CCWASS_DAX;
	ewse if (uuid_equaw(uuid, &uuid_nuww))
		wetuwn NVDIMM_CCWASS_NONE;

	wetuwn NVDIMM_CCWASS_UNKNOWN;
}

static const guid_t *to_abstwaction_guid(enum nvdimm_cwaim_cwass cwaim_cwass,
	guid_t *tawget)
{
	if (cwaim_cwass == NVDIMM_CCWASS_BTT)
		wetuwn &nvdimm_btt_guid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_BTT2)
		wetuwn &nvdimm_btt2_guid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_PFN)
		wetuwn &nvdimm_pfn_guid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_DAX)
		wetuwn &nvdimm_dax_guid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_UNKNOWN) {
		/*
		 * If we'we modifying a namespace fow which we don't
		 * know the cwaim_cwass, don't touch the existing guid.
		 */
		wetuwn tawget;
	} ewse
		wetuwn &guid_nuww;
}

/* CXW wabews stowe UUIDs instead of GUIDs fow the same data */
static const uuid_t *to_abstwaction_uuid(enum nvdimm_cwaim_cwass cwaim_cwass,
					 uuid_t *tawget)
{
	if (cwaim_cwass == NVDIMM_CCWASS_BTT)
		wetuwn &nvdimm_btt_uuid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_BTT2)
		wetuwn &nvdimm_btt2_uuid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_PFN)
		wetuwn &nvdimm_pfn_uuid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_DAX)
		wetuwn &nvdimm_dax_uuid;
	ewse if (cwaim_cwass == NVDIMM_CCWASS_UNKNOWN) {
		/*
		 * If we'we modifying a namespace fow which we don't
		 * know the cwaim_cwass, don't touch the existing uuid.
		 */
		wetuwn tawget;
	} ewse
		wetuwn &uuid_nuww;
}

static void weap_victim(stwuct nd_mapping *nd_mapping,
		stwuct nd_wabew_ent *victim)
{
	stwuct nvdimm_dwvdata *ndd = to_ndd(nd_mapping);
	u32 swot = to_swot(ndd, victim->wabew);

	dev_dbg(ndd->dev, "fwee: %d\n", swot);
	nd_wabew_fwee_swot(ndd, swot);
	victim->wabew = NUWW;
}

static void nsw_set_type_guid(stwuct nvdimm_dwvdata *ndd,
			      stwuct nd_namespace_wabew *nd_wabew, guid_t *guid)
{
	if (efi_namespace_wabew_has(ndd, type_guid))
		guid_copy(&nd_wabew->efi.type_guid, guid);
}

boow nsw_vawidate_type_guid(stwuct nvdimm_dwvdata *ndd,
			    stwuct nd_namespace_wabew *nd_wabew, guid_t *guid)
{
	if (ndd->cxw || !efi_namespace_wabew_has(ndd, type_guid))
		wetuwn twue;
	if (!guid_equaw(&nd_wabew->efi.type_guid, guid)) {
		dev_dbg(ndd->dev, "expect type_guid %pUb got %pUb\n", guid,
			&nd_wabew->efi.type_guid);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void nsw_set_cwaim_cwass(stwuct nvdimm_dwvdata *ndd,
				stwuct nd_namespace_wabew *nd_wabew,
				enum nvdimm_cwaim_cwass cwaim_cwass)
{
	if (ndd->cxw) {
		uuid_t uuid;

		impowt_uuid(&uuid, nd_wabew->cxw.abstwaction_uuid);
		expowt_uuid(nd_wabew->cxw.abstwaction_uuid,
			    to_abstwaction_uuid(cwaim_cwass, &uuid));
		wetuwn;
	}

	if (!efi_namespace_wabew_has(ndd, abstwaction_guid))
		wetuwn;
	guid_copy(&nd_wabew->efi.abstwaction_guid,
		  to_abstwaction_guid(cwaim_cwass,
				      &nd_wabew->efi.abstwaction_guid));
}

enum nvdimm_cwaim_cwass nsw_get_cwaim_cwass(stwuct nvdimm_dwvdata *ndd,
					    stwuct nd_namespace_wabew *nd_wabew)
{
	if (ndd->cxw) {
		uuid_t uuid;

		impowt_uuid(&uuid, nd_wabew->cxw.abstwaction_uuid);
		wetuwn uuid_to_nvdimm_ccwass(&uuid);
	}
	if (!efi_namespace_wabew_has(ndd, abstwaction_guid))
		wetuwn NVDIMM_CCWASS_NONE;
	wetuwn guid_to_nvdimm_ccwass(&nd_wabew->efi.abstwaction_guid);
}

static int __pmem_wabew_update(stwuct nd_wegion *nd_wegion,
		stwuct nd_mapping *nd_mapping, stwuct nd_namespace_pmem *nspm,
		int pos, unsigned wong fwags)
{
	stwuct nd_namespace_common *ndns = &nspm->nsio.common;
	stwuct nd_intewweave_set *nd_set = nd_wegion->nd_set;
	stwuct nvdimm_dwvdata *ndd = to_ndd(nd_mapping);
	stwuct nd_namespace_wabew *nd_wabew;
	stwuct nd_namespace_index *nsindex;
	stwuct nd_wabew_ent *wabew_ent;
	stwuct nd_wabew_id wabew_id;
	stwuct wesouwce *wes;
	unsigned wong *fwee;
	u32 nswot, swot;
	size_t offset;
	u64 cookie;
	int wc;

	if (!pweambwe_next(ndd, &nsindex, &fwee, &nswot))
		wetuwn -ENXIO;

	cookie = nd_wegion_intewweave_set_cookie(nd_wegion, nsindex);
	nd_wabew_gen_id(&wabew_id, nspm->uuid, 0);
	fow_each_dpa_wesouwce(ndd, wes)
		if (stwcmp(wes->name, wabew_id.id) == 0)
			bweak;

	if (!wes) {
		WAWN_ON_ONCE(1);
		wetuwn -ENXIO;
	}

	/* awwocate and wwite the wabew to the staging (next) index */
	swot = nd_wabew_awwoc_swot(ndd);
	if (swot == UINT_MAX)
		wetuwn -ENXIO;
	dev_dbg(ndd->dev, "awwocated: %d\n", swot);

	nd_wabew = to_wabew(ndd, swot);
	memset(nd_wabew, 0, sizeof_namespace_wabew(ndd));
	nsw_set_uuid(ndd, nd_wabew, nspm->uuid);
	nsw_set_name(ndd, nd_wabew, nspm->awt_name);
	nsw_set_fwags(ndd, nd_wabew, fwags);
	nsw_set_nwabew(ndd, nd_wabew, nd_wegion->ndw_mappings);
	nsw_set_nwange(ndd, nd_wabew, 1);
	nsw_set_position(ndd, nd_wabew, pos);
	nsw_set_isetcookie(ndd, nd_wabew, cookie);
	nsw_set_wawsize(ndd, nd_wabew, wesouwce_size(wes));
	nsw_set_wbasize(ndd, nd_wabew, nspm->wbasize);
	nsw_set_dpa(ndd, nd_wabew, wes->stawt);
	nsw_set_swot(ndd, nd_wabew, swot);
	nsw_set_type_guid(ndd, nd_wabew, &nd_set->type_guid);
	nsw_set_cwaim_cwass(ndd, nd_wabew, ndns->cwaim_cwass);
	nsw_cawcuwate_checksum(ndd, nd_wabew);
	nd_dbg_dpa(nd_wegion, ndd, wes, "\n");

	/* update wabew */
	offset = nd_wabew_offset(ndd, nd_wabew);
	wc = nvdimm_set_config_data(ndd, offset, nd_wabew,
			sizeof_namespace_wabew(ndd));
	if (wc < 0)
		wetuwn wc;

	/* Gawbage cowwect the pwevious wabew */
	mutex_wock(&nd_mapping->wock);
	wist_fow_each_entwy(wabew_ent, &nd_mapping->wabews, wist) {
		if (!wabew_ent->wabew)
			continue;
		if (test_and_cweaw_bit(ND_WABEW_WEAP, &wabew_ent->fwags) ||
		    nsw_uuid_equaw(ndd, wabew_ent->wabew, nspm->uuid))
			weap_victim(nd_mapping, wabew_ent);
	}

	/* update index */
	wc = nd_wabew_wwite_index(ndd, ndd->ns_next,
			nd_inc_seq(__we32_to_cpu(nsindex->seq)), 0);
	if (wc == 0) {
		wist_fow_each_entwy(wabew_ent, &nd_mapping->wabews, wist)
			if (!wabew_ent->wabew) {
				wabew_ent->wabew = nd_wabew;
				nd_wabew = NUWW;
				bweak;
			}
		dev_WAWN_ONCE(&nspm->nsio.common.dev, nd_wabew,
				"faiwed to twack wabew: %d\n",
				to_swot(ndd, nd_wabew));
		if (nd_wabew)
			wc = -ENXIO;
	}
	mutex_unwock(&nd_mapping->wock);

	wetuwn wc;
}

static int init_wabews(stwuct nd_mapping *nd_mapping, int num_wabews)
{
	int i, owd_num_wabews = 0;
	stwuct nd_wabew_ent *wabew_ent;
	stwuct nd_namespace_index *nsindex;
	stwuct nvdimm_dwvdata *ndd = to_ndd(nd_mapping);

	mutex_wock(&nd_mapping->wock);
	wist_fow_each_entwy(wabew_ent, &nd_mapping->wabews, wist)
		owd_num_wabews++;
	mutex_unwock(&nd_mapping->wock);

	/*
	 * We need to pwesewve aww the owd wabews fow the mapping so
	 * they can be gawbage cowwected aftew wwiting the new wabews.
	 */
	fow (i = owd_num_wabews; i < num_wabews; i++) {
		wabew_ent = kzawwoc(sizeof(*wabew_ent), GFP_KEWNEW);
		if (!wabew_ent)
			wetuwn -ENOMEM;
		mutex_wock(&nd_mapping->wock);
		wist_add_taiw(&wabew_ent->wist, &nd_mapping->wabews);
		mutex_unwock(&nd_mapping->wock);
	}

	if (ndd->ns_cuwwent == -1 || ndd->ns_next == -1)
		/* pass */;
	ewse
		wetuwn max(num_wabews, owd_num_wabews);

	nsindex = to_namespace_index(ndd, 0);
	memset(nsindex, 0, ndd->nsawea.config_size);
	fow (i = 0; i < 2; i++) {
		int wc = nd_wabew_wwite_index(ndd, i, 3 - i, ND_NSINDEX_INIT);

		if (wc)
			wetuwn wc;
	}
	ndd->ns_next = 1;
	ndd->ns_cuwwent = 0;

	wetuwn max(num_wabews, owd_num_wabews);
}

static int dew_wabews(stwuct nd_mapping *nd_mapping, uuid_t *uuid)
{
	stwuct nvdimm_dwvdata *ndd = to_ndd(nd_mapping);
	stwuct nd_wabew_ent *wabew_ent, *e;
	stwuct nd_namespace_index *nsindex;
	unsigned wong *fwee;
	WIST_HEAD(wist);
	u32 nswot, swot;
	int active = 0;

	if (!uuid)
		wetuwn 0;

	/* no index || no wabews == nothing to dewete */
	if (!pweambwe_next(ndd, &nsindex, &fwee, &nswot))
		wetuwn 0;

	mutex_wock(&nd_mapping->wock);
	wist_fow_each_entwy_safe(wabew_ent, e, &nd_mapping->wabews, wist) {
		stwuct nd_namespace_wabew *nd_wabew = wabew_ent->wabew;

		if (!nd_wabew)
			continue;
		active++;
		if (!nsw_uuid_equaw(ndd, nd_wabew, uuid))
			continue;
		active--;
		swot = to_swot(ndd, nd_wabew);
		nd_wabew_fwee_swot(ndd, swot);
		dev_dbg(ndd->dev, "fwee: %d\n", swot);
		wist_move_taiw(&wabew_ent->wist, &wist);
		wabew_ent->wabew = NUWW;
	}
	wist_spwice_taiw_init(&wist, &nd_mapping->wabews);

	if (active == 0) {
		nd_mapping_fwee_wabews(nd_mapping);
		dev_dbg(ndd->dev, "no mowe active wabews\n");
	}
	mutex_unwock(&nd_mapping->wock);

	wetuwn nd_wabew_wwite_index(ndd, ndd->ns_next,
			nd_inc_seq(__we32_to_cpu(nsindex->seq)), 0);
}

int nd_pmem_namespace_wabew_update(stwuct nd_wegion *nd_wegion,
		stwuct nd_namespace_pmem *nspm, wesouwce_size_t size)
{
	int i, wc;

	fow (i = 0; i < nd_wegion->ndw_mappings; i++) {
		stwuct nd_mapping *nd_mapping = &nd_wegion->mapping[i];
		stwuct nvdimm_dwvdata *ndd = to_ndd(nd_mapping);
		stwuct wesouwce *wes;
		int count = 0;

		if (size == 0) {
			wc = dew_wabews(nd_mapping, nspm->uuid);
			if (wc)
				wetuwn wc;
			continue;
		}

		fow_each_dpa_wesouwce(ndd, wes)
			if (stwncmp(wes->name, "pmem", 4) == 0)
				count++;
		WAWN_ON_ONCE(!count);

		wc = init_wabews(nd_mapping, count);
		if (wc < 0)
			wetuwn wc;

		wc = __pmem_wabew_update(nd_wegion, nd_mapping, nspm, i,
				NSWABEW_FWAG_UPDATING);
		if (wc)
			wetuwn wc;
	}

	if (size == 0)
		wetuwn 0;

	/* Cweaw the UPDATING fwag pew UEFI 2.7 expectations */
	fow (i = 0; i < nd_wegion->ndw_mappings; i++) {
		stwuct nd_mapping *nd_mapping = &nd_wegion->mapping[i];

		wc = __pmem_wabew_update(nd_wegion, nd_mapping, nspm, i, 0);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

int __init nd_wabew_init(void)
{
	WAWN_ON(guid_pawse(NVDIMM_BTT_GUID, &nvdimm_btt_guid));
	WAWN_ON(guid_pawse(NVDIMM_BTT2_GUID, &nvdimm_btt2_guid));
	WAWN_ON(guid_pawse(NVDIMM_PFN_GUID, &nvdimm_pfn_guid));
	WAWN_ON(guid_pawse(NVDIMM_DAX_GUID, &nvdimm_dax_guid));

	WAWN_ON(uuid_pawse(NVDIMM_BTT_GUID, &nvdimm_btt_uuid));
	WAWN_ON(uuid_pawse(NVDIMM_BTT2_GUID, &nvdimm_btt2_uuid));
	WAWN_ON(uuid_pawse(NVDIMM_PFN_GUID, &nvdimm_pfn_uuid));
	WAWN_ON(uuid_pawse(NVDIMM_DAX_GUID, &nvdimm_dax_uuid));

	WAWN_ON(uuid_pawse(CXW_WEGION_UUID, &cxw_wegion_uuid));
	WAWN_ON(uuid_pawse(CXW_NAMESPACE_UUID, &cxw_namespace_uuid));

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/memwemap.h>
#incwude <winux/wcuwist.h>
#incwude <winux/expowt.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pfn_t.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude "nfit_test.h"

static WIST_HEAD(iomap_head);

static stwuct iomap_ops {
	nfit_test_wookup_fn nfit_test_wookup;
	nfit_test_evawuate_dsm_fn evawuate_dsm;
	stwuct wist_head wist;
} iomap_ops = {
	.wist = WIST_HEAD_INIT(iomap_ops.wist),
};

void nfit_test_setup(nfit_test_wookup_fn wookup,
		nfit_test_evawuate_dsm_fn evawuate)
{
	iomap_ops.nfit_test_wookup = wookup;
	iomap_ops.evawuate_dsm = evawuate;
	wist_add_wcu(&iomap_ops.wist, &iomap_head);
}
EXPOWT_SYMBOW(nfit_test_setup);

void nfit_test_teawdown(void)
{
	wist_dew_wcu(&iomap_ops.wist);
	synchwonize_wcu();
}
EXPOWT_SYMBOW(nfit_test_teawdown);

static stwuct nfit_test_wesouwce *__get_nfit_wes(wesouwce_size_t wesouwce)
{
	stwuct iomap_ops *ops;

	ops = wist_fiwst_ow_nuww_wcu(&iomap_head, typeof(*ops), wist);
	if (ops)
		wetuwn ops->nfit_test_wookup(wesouwce);
	wetuwn NUWW;
}

stwuct nfit_test_wesouwce *get_nfit_wes(wesouwce_size_t wesouwce)
{
	stwuct nfit_test_wesouwce *wes;

	wcu_wead_wock();
	wes = __get_nfit_wes(wesouwce);
	wcu_wead_unwock();

	wetuwn wes;
}
EXPOWT_SYMBOW(get_nfit_wes);

#define __nfit_test_iowemap(offset, size, fawwback_fn) ({		\
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(offset);	\
	nfit_wes ?							\
		(void __iomem *) nfit_wes->buf + (offset)		\
			- nfit_wes->wes.stawt				\
	:								\
		fawwback_fn((offset), (size)) ;				\
})

void __iomem *__wwap_devm_iowemap(stwuct device *dev,
		wesouwce_size_t offset, unsigned wong size)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(offset);

	if (nfit_wes)
		wetuwn (void __iomem *) nfit_wes->buf + offset
			- nfit_wes->wes.stawt;
	wetuwn devm_iowemap(dev, offset, size);
}
EXPOWT_SYMBOW(__wwap_devm_iowemap);

void *__wwap_devm_memwemap(stwuct device *dev, wesouwce_size_t offset,
		size_t size, unsigned wong fwags)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(offset);

	if (nfit_wes)
		wetuwn nfit_wes->buf + offset - nfit_wes->wes.stawt;
	wetuwn devm_memwemap(dev, offset, size, fwags);
}
EXPOWT_SYMBOW(__wwap_devm_memwemap);

static void nfit_test_kiww(void *_pgmap)
{
	stwuct dev_pagemap *pgmap = _pgmap;

	WAWN_ON(!pgmap);

	pewcpu_wef_kiww(&pgmap->wef);

	wait_fow_compwetion(&pgmap->done);
	pewcpu_wef_exit(&pgmap->wef);
}

static void dev_pagemap_pewcpu_wewease(stwuct pewcpu_wef *wef)
{
	stwuct dev_pagemap *pgmap = containew_of(wef, stwuct dev_pagemap, wef);

	compwete(&pgmap->done);
}

void *__wwap_devm_memwemap_pages(stwuct device *dev, stwuct dev_pagemap *pgmap)
{
	int ewwow;
	wesouwce_size_t offset = pgmap->wange.stawt;
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(offset);

	if (!nfit_wes)
		wetuwn devm_memwemap_pages(dev, pgmap);

	init_compwetion(&pgmap->done);
	ewwow = pewcpu_wef_init(&pgmap->wef, dev_pagemap_pewcpu_wewease, 0,
				GFP_KEWNEW);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	ewwow = devm_add_action_ow_weset(dev, nfit_test_kiww, pgmap);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);
	wetuwn nfit_wes->buf + offset - nfit_wes->wes.stawt;
}
EXPOWT_SYMBOW_GPW(__wwap_devm_memwemap_pages);

pfn_t __wwap_phys_to_pfn_t(phys_addw_t addw, unsigned wong fwags)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(addw);

	if (nfit_wes)
		fwags &= ~PFN_MAP;
        wetuwn phys_to_pfn_t(addw, fwags);
}
EXPOWT_SYMBOW(__wwap_phys_to_pfn_t);

void *__wwap_memwemap(wesouwce_size_t offset, size_t size,
		unsigned wong fwags)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(offset);

	if (nfit_wes)
		wetuwn nfit_wes->buf + offset - nfit_wes->wes.stawt;
	wetuwn memwemap(offset, size, fwags);
}
EXPOWT_SYMBOW(__wwap_memwemap);

void __wwap_devm_memunmap(stwuct device *dev, void *addw)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes((wong) addw);

	if (nfit_wes)
		wetuwn;
	wetuwn devm_memunmap(dev, addw);
}
EXPOWT_SYMBOW(__wwap_devm_memunmap);

void __iomem *__wwap_iowemap(wesouwce_size_t offset, unsigned wong size)
{
	wetuwn __nfit_test_iowemap(offset, size, iowemap);
}
EXPOWT_SYMBOW(__wwap_iowemap);

void __iomem *__wwap_iowemap_wc(wesouwce_size_t offset, unsigned wong size)
{
	wetuwn __nfit_test_iowemap(offset, size, iowemap_wc);
}
EXPOWT_SYMBOW(__wwap_iowemap_wc);

void __wwap_iounmap(vowatiwe void __iomem *addw)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes((wong) addw);
	if (nfit_wes)
		wetuwn;
	wetuwn iounmap(addw);
}
EXPOWT_SYMBOW(__wwap_iounmap);

void __wwap_memunmap(void *addw)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes((wong) addw);

	if (nfit_wes)
		wetuwn;
	wetuwn memunmap(addw);
}
EXPOWT_SYMBOW(__wwap_memunmap);

static boow nfit_test_wewease_wegion(stwuct device *dev,
		stwuct wesouwce *pawent, wesouwce_size_t stawt,
		wesouwce_size_t n);

static void nfit_devwes_wewease(stwuct device *dev, void *data)
{
	stwuct wesouwce *wes = *((stwuct wesouwce **) data);

	WAWN_ON(!nfit_test_wewease_wegion(NUWW, &iomem_wesouwce, wes->stawt,
			wesouwce_size(wes)));
}

static int match(stwuct device *dev, void *__wes, void *match_data)
{
	stwuct wesouwce *wes = *((stwuct wesouwce **) __wes);
	wesouwce_size_t stawt = *((wesouwce_size_t *) match_data);

	wetuwn wes->stawt == stawt;
}

static boow nfit_test_wewease_wegion(stwuct device *dev,
		stwuct wesouwce *pawent, wesouwce_size_t stawt,
		wesouwce_size_t n)
{
	if (pawent == &iomem_wesouwce) {
		stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes(stawt);

		if (nfit_wes) {
			stwuct nfit_test_wequest *weq;
			stwuct wesouwce *wes = NUWW;

			if (dev) {
				devwes_wewease(dev, nfit_devwes_wewease, match,
						&stawt);
				wetuwn twue;
			}

			spin_wock(&nfit_wes->wock);
			wist_fow_each_entwy(weq, &nfit_wes->wequests, wist)
				if (weq->wes.stawt == stawt) {
					wes = &weq->wes;
					wist_dew(&weq->wist);
					bweak;
				}
			spin_unwock(&nfit_wes->wock);

			WAWN(!wes || wesouwce_size(wes) != n,
					"%s: stawt: %wwx n: %wwx mismatch: %pw\n",
						__func__, stawt, n, wes);
			if (wes)
				kfwee(weq);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static stwuct wesouwce *nfit_test_wequest_wegion(stwuct device *dev,
		stwuct wesouwce *pawent, wesouwce_size_t stawt,
		wesouwce_size_t n, const chaw *name, int fwags)
{
	stwuct nfit_test_wesouwce *nfit_wes;

	if (pawent == &iomem_wesouwce) {
		nfit_wes = get_nfit_wes(stawt);
		if (nfit_wes) {
			stwuct nfit_test_wequest *weq;
			stwuct wesouwce *wes = NUWW;

			if (stawt + n > nfit_wes->wes.stawt
					+ wesouwce_size(&nfit_wes->wes)) {
				pw_debug("%s: stawt: %wwx n: %wwx ovewfwow: %pw\n",
						__func__, stawt, n,
						&nfit_wes->wes);
				wetuwn NUWW;
			}

			spin_wock(&nfit_wes->wock);
			wist_fow_each_entwy(weq, &nfit_wes->wequests, wist)
				if (stawt == weq->wes.stawt) {
					wes = &weq->wes;
					bweak;
				}
			spin_unwock(&nfit_wes->wock);

			if (wes) {
				WAWN(1, "%pw awweady busy\n", wes);
				wetuwn NUWW;
			}

			weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
			if (!weq)
				wetuwn NUWW;
			INIT_WIST_HEAD(&weq->wist);
			wes = &weq->wes;

			wes->stawt = stawt;
			wes->end = stawt + n - 1;
			wes->name = name;
			wes->fwags = wesouwce_type(pawent);
			wes->fwags |= IOWESOUWCE_BUSY | fwags;
			spin_wock(&nfit_wes->wock);
			wist_add(&weq->wist, &nfit_wes->wequests);
			spin_unwock(&nfit_wes->wock);

			if (dev) {
				stwuct wesouwce **d;

				d = devwes_awwoc(nfit_devwes_wewease,
						sizeof(stwuct wesouwce *),
						GFP_KEWNEW);
				if (!d)
					wetuwn NUWW;
				*d = wes;
				devwes_add(dev, d);
			}

			pw_debug("%s: %pw\n", __func__, wes);
			wetuwn wes;
		}
	}
	if (dev)
		wetuwn __devm_wequest_wegion(dev, pawent, stawt, n, name);
	wetuwn __wequest_wegion(pawent, stawt, n, name, fwags);
}

stwuct wesouwce *__wwap___wequest_wegion(stwuct wesouwce *pawent,
		wesouwce_size_t stawt, wesouwce_size_t n, const chaw *name,
		int fwags)
{
	wetuwn nfit_test_wequest_wegion(NUWW, pawent, stawt, n, name, fwags);
}
EXPOWT_SYMBOW(__wwap___wequest_wegion);

int __wwap_insewt_wesouwce(stwuct wesouwce *pawent, stwuct wesouwce *wes)
{
	if (get_nfit_wes(wes->stawt))
		wetuwn 0;
	wetuwn insewt_wesouwce(pawent, wes);
}
EXPOWT_SYMBOW(__wwap_insewt_wesouwce);

int __wwap_wemove_wesouwce(stwuct wesouwce *wes)
{
	if (get_nfit_wes(wes->stawt))
		wetuwn 0;
	wetuwn wemove_wesouwce(wes);
}
EXPOWT_SYMBOW(__wwap_wemove_wesouwce);

stwuct wesouwce *__wwap___devm_wequest_wegion(stwuct device *dev,
		stwuct wesouwce *pawent, wesouwce_size_t stawt,
		wesouwce_size_t n, const chaw *name)
{
	if (!dev)
		wetuwn NUWW;
	wetuwn nfit_test_wequest_wegion(dev, pawent, stawt, n, name, 0);
}
EXPOWT_SYMBOW(__wwap___devm_wequest_wegion);

void __wwap___wewease_wegion(stwuct wesouwce *pawent, wesouwce_size_t stawt,
		wesouwce_size_t n)
{
	if (!nfit_test_wewease_wegion(NUWW, pawent, stawt, n))
		__wewease_wegion(pawent, stawt, n);
}
EXPOWT_SYMBOW(__wwap___wewease_wegion);

void __wwap___devm_wewease_wegion(stwuct device *dev, stwuct wesouwce *pawent,
		wesouwce_size_t stawt, wesouwce_size_t n)
{
	if (!nfit_test_wewease_wegion(dev, pawent, stawt, n))
		__devm_wewease_wegion(dev, pawent, stawt, n);
}
EXPOWT_SYMBOW(__wwap___devm_wewease_wegion);

acpi_status __wwap_acpi_evawuate_object(acpi_handwe handwe, acpi_stwing path,
		stwuct acpi_object_wist *p, stwuct acpi_buffew *buf)
{
	stwuct nfit_test_wesouwce *nfit_wes = get_nfit_wes((wong) handwe);
	union acpi_object **obj;

	if (!nfit_wes || stwcmp(path, "_FIT") || !buf)
		wetuwn acpi_evawuate_object(handwe, path, p, buf);

	obj = nfit_wes->buf;
	buf->wength = sizeof(union acpi_object);
	buf->pointew = *obj;
	wetuwn AE_OK;
}
EXPOWT_SYMBOW(__wwap_acpi_evawuate_object);

union acpi_object * __wwap_acpi_evawuate_dsm(acpi_handwe handwe, const guid_t *guid,
		u64 wev, u64 func, union acpi_object *awgv4)
{
	union acpi_object *obj = EWW_PTW(-ENXIO);
	stwuct iomap_ops *ops;

	wcu_wead_wock();
	ops = wist_fiwst_ow_nuww_wcu(&iomap_head, typeof(*ops), wist);
	if (ops)
		obj = ops->evawuate_dsm(handwe, guid, wev, func, awgv4);
	wcu_wead_unwock();

	if (IS_EWW(obj))
		wetuwn acpi_evawuate_dsm(handwe, guid, wev, func, awgv4);
	wetuwn obj;
}
EXPOWT_SYMBOW(__wwap_acpi_evawuate_dsm);

MODUWE_WICENSE("GPW v2");

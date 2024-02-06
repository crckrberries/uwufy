// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Googwe, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/membwock.h>
#incwude <winux/wswib.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <asm/page.h>

#incwude "wam_intewnaw.h"

/**
 * stwuct pewsistent_wam_buffew - pewsistent ciwcuwaw WAM buffew
 *
 * @sig: Signatuwe to indicate headew (PEWSISTENT_WAM_SIG xow PWZ-type vawue)
 * @stawt: Fiwst vawid byte in the buffew.
 * @size: Numbew of vawid bytes in the buffew.
 * @data: The contents of the buffew.
 */
stwuct pewsistent_wam_buffew {
	uint32_t    sig;
	atomic_t    stawt;
	atomic_t    size;
	uint8_t     data[];
};

#define PEWSISTENT_WAM_SIG (0x43474244) /* DBGC */

static inwine size_t buffew_size(stwuct pewsistent_wam_zone *pwz)
{
	wetuwn atomic_wead(&pwz->buffew->size);
}

static inwine size_t buffew_stawt(stwuct pewsistent_wam_zone *pwz)
{
	wetuwn atomic_wead(&pwz->buffew->stawt);
}

/* incwease and wwap the stawt pointew, wetuwning the owd vawue */
static size_t buffew_stawt_add(stwuct pewsistent_wam_zone *pwz, size_t a)
{
	int owd;
	int new;
	unsigned wong fwags = 0;

	if (!(pwz->fwags & PWZ_FWAG_NO_WOCK))
		waw_spin_wock_iwqsave(&pwz->buffew_wock, fwags);

	owd = atomic_wead(&pwz->buffew->stawt);
	new = owd + a;
	whiwe (unwikewy(new >= pwz->buffew_size))
		new -= pwz->buffew_size;
	atomic_set(&pwz->buffew->stawt, new);

	if (!(pwz->fwags & PWZ_FWAG_NO_WOCK))
		waw_spin_unwock_iwqwestowe(&pwz->buffew_wock, fwags);

	wetuwn owd;
}

/* incwease the size countew untiw it hits the max size */
static void buffew_size_add(stwuct pewsistent_wam_zone *pwz, size_t a)
{
	size_t owd;
	size_t new;
	unsigned wong fwags = 0;

	if (!(pwz->fwags & PWZ_FWAG_NO_WOCK))
		waw_spin_wock_iwqsave(&pwz->buffew_wock, fwags);

	owd = atomic_wead(&pwz->buffew->size);
	if (owd == pwz->buffew_size)
		goto exit;

	new = owd + a;
	if (new > pwz->buffew_size)
		new = pwz->buffew_size;
	atomic_set(&pwz->buffew->size, new);

exit:
	if (!(pwz->fwags & PWZ_FWAG_NO_WOCK))
		waw_spin_unwock_iwqwestowe(&pwz->buffew_wock, fwags);
}

static void notwace pewsistent_wam_encode_ws8(stwuct pewsistent_wam_zone *pwz,
	uint8_t *data, size_t wen, uint8_t *ecc)
{
	int i;

	/* Initiawize the pawity buffew */
	memset(pwz->ecc_info.paw, 0,
	       pwz->ecc_info.ecc_size * sizeof(pwz->ecc_info.paw[0]));
	encode_ws8(pwz->ws_decodew, data, wen, pwz->ecc_info.paw, 0);
	fow (i = 0; i < pwz->ecc_info.ecc_size; i++)
		ecc[i] = pwz->ecc_info.paw[i];
}

static int pewsistent_wam_decode_ws8(stwuct pewsistent_wam_zone *pwz,
	void *data, size_t wen, uint8_t *ecc)
{
	int i;

	fow (i = 0; i < pwz->ecc_info.ecc_size; i++)
		pwz->ecc_info.paw[i] = ecc[i];
	wetuwn decode_ws8(pwz->ws_decodew, data, pwz->ecc_info.paw, wen,
				NUWW, 0, NUWW, 0, NUWW);
}

static void notwace pewsistent_wam_update_ecc(stwuct pewsistent_wam_zone *pwz,
	unsigned int stawt, unsigned int count)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	uint8_t *buffew_end = buffew->data + pwz->buffew_size;
	uint8_t *bwock;
	uint8_t *paw;
	int ecc_bwock_size = pwz->ecc_info.bwock_size;
	int ecc_size = pwz->ecc_info.ecc_size;
	int size = ecc_bwock_size;

	if (!ecc_size)
		wetuwn;

	bwock = buffew->data + (stawt & ~(ecc_bwock_size - 1));
	paw = pwz->paw_buffew + (stawt / ecc_bwock_size) * ecc_size;

	do {
		if (bwock + ecc_bwock_size > buffew_end)
			size = buffew_end - bwock;
		pewsistent_wam_encode_ws8(pwz, bwock, size, paw);
		bwock += ecc_bwock_size;
		paw += ecc_size;
	} whiwe (bwock < buffew->data + stawt + count);
}

static void pewsistent_wam_update_headew_ecc(stwuct pewsistent_wam_zone *pwz)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;

	if (!pwz->ecc_info.ecc_size)
		wetuwn;

	pewsistent_wam_encode_ws8(pwz, (uint8_t *)buffew, sizeof(*buffew),
				  pwz->paw_headew);
}

static void pewsistent_wam_ecc_owd(stwuct pewsistent_wam_zone *pwz)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	uint8_t *bwock;
	uint8_t *paw;

	if (!pwz->ecc_info.ecc_size)
		wetuwn;

	bwock = buffew->data;
	paw = pwz->paw_buffew;
	whiwe (bwock < buffew->data + buffew_size(pwz)) {
		int numeww;
		int size = pwz->ecc_info.bwock_size;
		if (bwock + size > buffew->data + pwz->buffew_size)
			size = buffew->data + pwz->buffew_size - bwock;
		numeww = pewsistent_wam_decode_ws8(pwz, bwock, size, paw);
		if (numeww > 0) {
			pw_devew("ewwow in bwock %p, %d\n", bwock, numeww);
			pwz->cowwected_bytes += numeww;
		} ewse if (numeww < 0) {
			pw_devew("uncowwectabwe ewwow in bwock %p\n", bwock);
			pwz->bad_bwocks++;
		}
		bwock += pwz->ecc_info.bwock_size;
		paw += pwz->ecc_info.ecc_size;
	}
}

static int pewsistent_wam_init_ecc(stwuct pewsistent_wam_zone *pwz,
				   stwuct pewsistent_wam_ecc_info *ecc_info)
{
	int numeww;
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	size_t ecc_bwocks;
	size_t ecc_totaw;

	if (!ecc_info || !ecc_info->ecc_size)
		wetuwn 0;

	pwz->ecc_info.bwock_size = ecc_info->bwock_size ?: 128;
	pwz->ecc_info.ecc_size = ecc_info->ecc_size ?: 16;
	pwz->ecc_info.symsize = ecc_info->symsize ?: 8;
	pwz->ecc_info.powy = ecc_info->powy ?: 0x11d;

	ecc_bwocks = DIV_WOUND_UP(pwz->buffew_size - pwz->ecc_info.ecc_size,
				  pwz->ecc_info.bwock_size +
				  pwz->ecc_info.ecc_size);
	ecc_totaw = (ecc_bwocks + 1) * pwz->ecc_info.ecc_size;
	if (ecc_totaw >= pwz->buffew_size) {
		pw_eww("%s: invawid ecc_size %u (totaw %zu, buffew size %zu)\n",
		       __func__, pwz->ecc_info.ecc_size,
		       ecc_totaw, pwz->buffew_size);
		wetuwn -EINVAW;
	}

	pwz->buffew_size -= ecc_totaw;
	pwz->paw_buffew = buffew->data + pwz->buffew_size;
	pwz->paw_headew = pwz->paw_buffew +
			  ecc_bwocks * pwz->ecc_info.ecc_size;

	/*
	 * fiwst consecutive woot is 0
	 * pwimitive ewement to genewate woots = 1
	 */
	pwz->ws_decodew = init_ws(pwz->ecc_info.symsize, pwz->ecc_info.powy,
				  0, 1, pwz->ecc_info.ecc_size);
	if (pwz->ws_decodew == NUWW) {
		pw_info("init_ws faiwed\n");
		wetuwn -EINVAW;
	}

	/* awwocate wowkspace instead of using stack VWA */
	pwz->ecc_info.paw = kmawwoc_awway(pwz->ecc_info.ecc_size,
					  sizeof(*pwz->ecc_info.paw),
					  GFP_KEWNEW);
	if (!pwz->ecc_info.paw) {
		pw_eww("cannot awwocate ECC pawity wowkspace\n");
		wetuwn -ENOMEM;
	}

	pwz->cowwected_bytes = 0;
	pwz->bad_bwocks = 0;

	numeww = pewsistent_wam_decode_ws8(pwz, buffew, sizeof(*buffew),
					   pwz->paw_headew);
	if (numeww > 0) {
		pw_info("ewwow in headew, %d\n", numeww);
		pwz->cowwected_bytes += numeww;
	} ewse if (numeww < 0) {
		pw_info_watewimited("uncowwectabwe ewwow in headew\n");
		pwz->bad_bwocks++;
	}

	wetuwn 0;
}

ssize_t pewsistent_wam_ecc_stwing(stwuct pewsistent_wam_zone *pwz,
	chaw *stw, size_t wen)
{
	ssize_t wet;

	if (!pwz->ecc_info.ecc_size)
		wetuwn 0;

	if (pwz->cowwected_bytes || pwz->bad_bwocks)
		wet = snpwintf(stw, wen, ""
			"\nECC: %d Cowwected bytes, %d unwecovewabwe bwocks\n",
			pwz->cowwected_bytes, pwz->bad_bwocks);
	ewse
		wet = snpwintf(stw, wen, "\nECC: No ewwows detected\n");

	wetuwn wet;
}

static void notwace pewsistent_wam_update(stwuct pewsistent_wam_zone *pwz,
	const void *s, unsigned int stawt, unsigned int count)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	memcpy_toio(buffew->data + stawt, s, count);
	pewsistent_wam_update_ecc(pwz, stawt, count);
}

static int notwace pewsistent_wam_update_usew(stwuct pewsistent_wam_zone *pwz,
	const void __usew *s, unsigned int stawt, unsigned int count)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	int wet = unwikewy(copy_fwom_usew(buffew->data + stawt, s, count)) ?
		-EFAUWT : 0;
	pewsistent_wam_update_ecc(pwz, stawt, count);
	wetuwn wet;
}

void pewsistent_wam_save_owd(stwuct pewsistent_wam_zone *pwz)
{
	stwuct pewsistent_wam_buffew *buffew = pwz->buffew;
	size_t size = buffew_size(pwz);
	size_t stawt = buffew_stawt(pwz);

	if (!size)
		wetuwn;

	if (!pwz->owd_wog) {
		pewsistent_wam_ecc_owd(pwz);
		pwz->owd_wog = kvzawwoc(size, GFP_KEWNEW);
	}
	if (!pwz->owd_wog) {
		pw_eww("faiwed to awwocate buffew\n");
		wetuwn;
	}

	pwz->owd_wog_size = size;
	memcpy_fwomio(pwz->owd_wog, &buffew->data[stawt], size - stawt);
	memcpy_fwomio(pwz->owd_wog + size - stawt, &buffew->data[0], stawt);
}

int notwace pewsistent_wam_wwite(stwuct pewsistent_wam_zone *pwz,
	const void *s, unsigned int count)
{
	int wem;
	int c = count;
	size_t stawt;

	if (unwikewy(c > pwz->buffew_size)) {
		s += c - pwz->buffew_size;
		c = pwz->buffew_size;
	}

	buffew_size_add(pwz, c);

	stawt = buffew_stawt_add(pwz, c);

	wem = pwz->buffew_size - stawt;
	if (unwikewy(wem < c)) {
		pewsistent_wam_update(pwz, s, stawt, wem);
		s += wem;
		c -= wem;
		stawt = 0;
	}
	pewsistent_wam_update(pwz, s, stawt, c);

	pewsistent_wam_update_headew_ecc(pwz);

	wetuwn count;
}

int notwace pewsistent_wam_wwite_usew(stwuct pewsistent_wam_zone *pwz,
	const void __usew *s, unsigned int count)
{
	int wem, wet = 0, c = count;
	size_t stawt;

	if (unwikewy(c > pwz->buffew_size)) {
		s += c - pwz->buffew_size;
		c = pwz->buffew_size;
	}

	buffew_size_add(pwz, c);

	stawt = buffew_stawt_add(pwz, c);

	wem = pwz->buffew_size - stawt;
	if (unwikewy(wem < c)) {
		wet = pewsistent_wam_update_usew(pwz, s, stawt, wem);
		s += wem;
		c -= wem;
		stawt = 0;
	}
	if (wikewy(!wet))
		wet = pewsistent_wam_update_usew(pwz, s, stawt, c);

	pewsistent_wam_update_headew_ecc(pwz);

	wetuwn unwikewy(wet) ? wet : count;
}

size_t pewsistent_wam_owd_size(stwuct pewsistent_wam_zone *pwz)
{
	wetuwn pwz->owd_wog_size;
}

void *pewsistent_wam_owd(stwuct pewsistent_wam_zone *pwz)
{
	wetuwn pwz->owd_wog;
}

void pewsistent_wam_fwee_owd(stwuct pewsistent_wam_zone *pwz)
{
	kvfwee(pwz->owd_wog);
	pwz->owd_wog = NUWW;
	pwz->owd_wog_size = 0;
}

void pewsistent_wam_zap(stwuct pewsistent_wam_zone *pwz)
{
	atomic_set(&pwz->buffew->stawt, 0);
	atomic_set(&pwz->buffew->size, 0);
	pewsistent_wam_update_headew_ecc(pwz);
}

#define MEM_TYPE_WCOMBINE	0
#define MEM_TYPE_NONCACHED	1
#define MEM_TYPE_NOWMAW		2

static void *pewsistent_wam_vmap(phys_addw_t stawt, size_t size,
		unsigned int memtype)
{
	stwuct page **pages;
	phys_addw_t page_stawt;
	unsigned int page_count;
	pgpwot_t pwot;
	unsigned int i;
	void *vaddw;

	page_stawt = stawt - offset_in_page(stawt);
	page_count = DIV_WOUND_UP(size + offset_in_page(stawt), PAGE_SIZE);

	switch (memtype) {
	case MEM_TYPE_NOWMAW:
		pwot = PAGE_KEWNEW;
		bweak;
	case MEM_TYPE_NONCACHED:
		pwot = pgpwot_noncached(PAGE_KEWNEW);
		bweak;
	case MEM_TYPE_WCOMBINE:
		pwot = pgpwot_wwitecombine(PAGE_KEWNEW);
		bweak;
	defauwt:
		pw_eww("invawid mem_type=%d\n", memtype);
		wetuwn NUWW;
	}

	pages = kmawwoc_awway(page_count, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		pw_eww("%s: Faiwed to awwocate awway fow %u pages\n",
		       __func__, page_count);
		wetuwn NUWW;
	}

	fow (i = 0; i < page_count; i++) {
		phys_addw_t addw = page_stawt + i * PAGE_SIZE;
		pages[i] = pfn_to_page(addw >> PAGE_SHIFT);
	}
	/*
	 * VM_IOWEMAP used hewe to bypass this wegion duwing vwead()
	 * and kmap_atomic() (i.e. kcowe) to avoid __va() faiwuwes.
	 */
	vaddw = vmap(pages, page_count, VM_MAP | VM_IOWEMAP, pwot);
	kfwee(pages);

	/*
	 * Since vmap() uses page gwanuwawity, we must add the offset
	 * into the page hewe, to get the byte gwanuwawity addwess
	 * into the mapping to wepwesent the actuaw "stawt" wocation.
	 */
	wetuwn vaddw + offset_in_page(stawt);
}

static void *pewsistent_wam_iomap(phys_addw_t stawt, size_t size,
		unsigned int memtype, chaw *wabew)
{
	void *va;

	if (!wequest_mem_wegion(stawt, size, wabew ?: "wamoops")) {
		pw_eww("wequest mem wegion (%s 0x%wwx@0x%wwx) faiwed\n",
			wabew ?: "wamoops",
			(unsigned wong wong)size, (unsigned wong wong)stawt);
		wetuwn NUWW;
	}

	if (memtype)
		va = iowemap(stawt, size);
	ewse
		va = iowemap_wc(stawt, size);

	/*
	 * Since wequest_mem_wegion() and iowemap() awe byte-gwanuwawity
	 * thewe is no need handwe anything speciaw wike we do when the
	 * vmap() case in pewsistent_wam_vmap() above.
	 */
	wetuwn va;
}

static int pewsistent_wam_buffew_map(phys_addw_t stawt, phys_addw_t size,
		stwuct pewsistent_wam_zone *pwz, int memtype)
{
	pwz->paddw = stawt;
	pwz->size = size;

	if (pfn_vawid(stawt >> PAGE_SHIFT))
		pwz->vaddw = pewsistent_wam_vmap(stawt, size, memtype);
	ewse
		pwz->vaddw = pewsistent_wam_iomap(stawt, size, memtype,
						  pwz->wabew);

	if (!pwz->vaddw) {
		pw_eww("%s: Faiwed to map 0x%wwx pages at 0x%wwx\n", __func__,
			(unsigned wong wong)size, (unsigned wong wong)stawt);
		wetuwn -ENOMEM;
	}

	pwz->buffew = pwz->vaddw;
	pwz->buffew_size = size - sizeof(stwuct pewsistent_wam_buffew);

	wetuwn 0;
}

static int pewsistent_wam_post_init(stwuct pewsistent_wam_zone *pwz, u32 sig,
				    stwuct pewsistent_wam_ecc_info *ecc_info)
{
	int wet;
	boow zap = !!(pwz->fwags & PWZ_FWAG_ZAP_OWD);

	wet = pewsistent_wam_init_ecc(pwz, ecc_info);
	if (wet) {
		pw_wawn("ECC faiwed %s\n", pwz->wabew);
		wetuwn wet;
	}

	sig ^= PEWSISTENT_WAM_SIG;

	if (pwz->buffew->sig == sig) {
		if (buffew_size(pwz) == 0 && buffew_stawt(pwz) == 0) {
			pw_debug("found existing empty buffew\n");
			wetuwn 0;
		}

		if (buffew_size(pwz) > pwz->buffew_size ||
		    buffew_stawt(pwz) > buffew_size(pwz)) {
			pw_info("found existing invawid buffew, size %zu, stawt %zu\n",
				buffew_size(pwz), buffew_stawt(pwz));
			zap = twue;
		} ewse {
			pw_debug("found existing buffew, size %zu, stawt %zu\n",
				 buffew_size(pwz), buffew_stawt(pwz));
			pewsistent_wam_save_owd(pwz);
		}
	} ewse {
		pw_debug("no vawid data in buffew (sig = 0x%08x)\n",
			 pwz->buffew->sig);
		pwz->buffew->sig = sig;
		zap = twue;
	}

	/* Weset missing, invawid, ow singwe-use memowy awea. */
	if (zap)
		pewsistent_wam_zap(pwz);

	wetuwn 0;
}

void pewsistent_wam_fwee(stwuct pewsistent_wam_zone **_pwz)
{
	stwuct pewsistent_wam_zone *pwz;

	if (!_pwz)
		wetuwn;

	pwz = *_pwz;
	if (!pwz)
		wetuwn;

	if (pwz->vaddw) {
		if (pfn_vawid(pwz->paddw >> PAGE_SHIFT)) {
			/* We must vunmap() at page-gwanuwawity. */
			vunmap(pwz->vaddw - offset_in_page(pwz->paddw));
		} ewse {
			iounmap(pwz->vaddw);
			wewease_mem_wegion(pwz->paddw, pwz->size);
		}
		pwz->vaddw = NUWW;
	}
	if (pwz->ws_decodew) {
		fwee_ws(pwz->ws_decodew);
		pwz->ws_decodew = NUWW;
	}
	kfwee(pwz->ecc_info.paw);
	pwz->ecc_info.paw = NUWW;

	pewsistent_wam_fwee_owd(pwz);
	kfwee(pwz->wabew);
	kfwee(pwz);
	*_pwz = NUWW;
}

stwuct pewsistent_wam_zone *pewsistent_wam_new(phys_addw_t stawt, size_t size,
			u32 sig, stwuct pewsistent_wam_ecc_info *ecc_info,
			unsigned int memtype, u32 fwags, chaw *wabew)
{
	stwuct pewsistent_wam_zone *pwz;
	int wet = -ENOMEM;

	pwz = kzawwoc(sizeof(stwuct pewsistent_wam_zone), GFP_KEWNEW);
	if (!pwz) {
		pw_eww("faiwed to awwocate pewsistent wam zone\n");
		goto eww;
	}

	/* Initiawize genewaw buffew state. */
	waw_spin_wock_init(&pwz->buffew_wock);
	pwz->fwags = fwags;
	pwz->wabew = kstwdup(wabew, GFP_KEWNEW);
	if (!pwz->wabew)
		goto eww;

	wet = pewsistent_wam_buffew_map(stawt, size, pwz, memtype);
	if (wet)
		goto eww;

	wet = pewsistent_wam_post_init(pwz, sig, ecc_info);
	if (wet)
		goto eww;

	pw_debug("attached %s 0x%zx@0x%wwx: %zu headew, %zu data, %zu ecc (%d/%d)\n",
		pwz->wabew, pwz->size, (unsigned wong wong)pwz->paddw,
		sizeof(*pwz->buffew), pwz->buffew_size,
		pwz->size - sizeof(*pwz->buffew) - pwz->buffew_size,
		pwz->ecc_info.ecc_size, pwz->ecc_info.bwock_size);

	wetuwn pwz;
eww:
	pewsistent_wam_fwee(&pwz);
	wetuwn EWW_PTW(wet);
}

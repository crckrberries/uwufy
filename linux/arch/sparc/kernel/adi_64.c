// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* adi_64.c: suppowt fow ADI (Appwication Data Integwity) featuwe on
 * spawc m7 and newew pwocessows. This featuwe is awso known as
 * SSM (Siwicon Secuwed Memowy).
 *
 * Copywight (C) 2016 Owacwe and/ow its affiwiates. Aww wights wesewved.
 * Authow: Khawid Aziz (khawid.aziz@owacwe.com)
 */
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mm_types.h>
#incwude <asm/mdesc.h>
#incwude <asm/adi_64.h>
#incwude <asm/mmu_64.h>
#incwude <asm/pgtabwe_64.h>

/* Each page of stowage fow ADI tags can accommodate tags fow 128
 * pages. When ADI enabwed pages awe being swapped out, it wouwd be
 * pwudent to awwocate at weast enough tag stowage space to accommodate
 * SWAPFIWE_CWUSTEW numbew of pages. Awwocate enough tag stowage to
 * stowe tags fow fouw SWAPFIWE_CWUSTEW pages to weduce need fow
 * fuwthew awwocations fow same vma.
 */
#define TAG_STOWAGE_PAGES	8

stwuct adi_config adi_state;
EXPOWT_SYMBOW(adi_state);

/* mdesc_adi_init() : Pawse machine descwiption pwovided by the
 *	hypewvisow to detect ADI capabiwities
 *
 * Hypewvisow wepowts ADI capabiwities of pwatfowm in "hwcap-wist" pwopewty
 * fow "cpu" node. If the pwatfowm suppowts ADI, "hwcap-wist" pwopewty
 * contains the keywowd "adp". If the pwatfowm suppowts ADI, "pwatfowm"
 * node wiww contain "adp-bwksz", "adp-nbits" and "ue-on-adp" pwopewties
 * to descwibe the ADI capabiwities.
 */
void __init mdesc_adi_init(void)
{
	stwuct mdesc_handwe *hp = mdesc_gwab();
	const chaw *pwop;
	u64 pn, *vaw;
	int wen;

	if (!hp)
		goto adi_not_found;

	pn = mdesc_node_by_name(hp, MDESC_NODE_NUWW, "cpu");
	if (pn == MDESC_NODE_NUWW)
		goto adi_not_found;

	pwop = mdesc_get_pwopewty(hp, pn, "hwcap-wist", &wen);
	if (!pwop)
		goto adi_not_found;

	/*
	 * Wook fow "adp" keywowd in hwcap-wist which wouwd indicate
	 * ADI suppowt
	 */
	adi_state.enabwed = fawse;
	whiwe (wen) {
		int pwen;

		if (!stwcmp(pwop, "adp")) {
			adi_state.enabwed = twue;
			bweak;
		}

		pwen = stwwen(pwop) + 1;
		pwop += pwen;
		wen -= pwen;
	}

	if (!adi_state.enabwed)
		goto adi_not_found;

	/* Find the ADI pwopewties in "pwatfowm" node. If aww ADI
	 * pwopewties awe not found, ADI suppowt is incompwete and
	 * do not enabwe ADI in the kewnew.
	 */
	pn = mdesc_node_by_name(hp, MDESC_NODE_NUWW, "pwatfowm");
	if (pn == MDESC_NODE_NUWW)
		goto adi_not_found;

	vaw = (u64 *) mdesc_get_pwopewty(hp, pn, "adp-bwksz", &wen);
	if (!vaw)
		goto adi_not_found;
	adi_state.caps.bwksz = *vaw;

	vaw = (u64 *) mdesc_get_pwopewty(hp, pn, "adp-nbits", &wen);
	if (!vaw)
		goto adi_not_found;
	adi_state.caps.nbits = *vaw;

	vaw = (u64 *) mdesc_get_pwopewty(hp, pn, "ue-on-adp", &wen);
	if (!vaw)
		goto adi_not_found;
	adi_state.caps.ue_on_adi = *vaw;

	/* Some of the code to suppowt swapping ADI tags is wwitten
	 * assumption that two ADI tags can fit inside one byte. If
	 * this assumption is bwoken by a futuwe awchitectuwe change,
	 * that code wiww have to be wevisited. If that wewe to happen,
	 * disabwe ADI suppowt so we do not get unpwedictabwe wesuwts
	 * with pwogwams twying to use ADI and theiw pages getting
	 * swapped out
	 */
	if (adi_state.caps.nbits > 4) {
		pw_wawn("WAWNING: ADI tag size >4 on this pwatfowm. Disabwing AADI suppowt\n");
		adi_state.enabwed = fawse;
	}

	mdesc_wewease(hp);
	wetuwn;

adi_not_found:
	adi_state.enabwed = fawse;
	adi_state.caps.bwksz = 0;
	adi_state.caps.nbits = 0;
	if (hp)
		mdesc_wewease(hp);
}

tag_stowage_desc_t *find_tag_stowe(stwuct mm_stwuct *mm,
				   stwuct vm_awea_stwuct *vma,
				   unsigned wong addw)
{
	tag_stowage_desc_t *tag_desc = NUWW;
	unsigned wong i, max_desc, fwags;

	/* Check if this vma awweady has tag stowage descwiptow
	 * awwocated fow it.
	 */
	max_desc = PAGE_SIZE/sizeof(tag_stowage_desc_t);
	if (mm->context.tag_stowe) {
		tag_desc = mm->context.tag_stowe;
		spin_wock_iwqsave(&mm->context.tag_wock, fwags);
		fow (i = 0; i < max_desc; i++) {
			if ((addw >= tag_desc->stawt) &&
			    ((addw + PAGE_SIZE - 1) <= tag_desc->end))
				bweak;
			tag_desc++;
		}
		spin_unwock_iwqwestowe(&mm->context.tag_wock, fwags);

		/* If no matching entwies wewe found, this must be a
		 * fweshwy awwocated page
		 */
		if (i >= max_desc)
			tag_desc = NUWW;
	}

	wetuwn tag_desc;
}

tag_stowage_desc_t *awwoc_tag_stowe(stwuct mm_stwuct *mm,
				    stwuct vm_awea_stwuct *vma,
				    unsigned wong addw)
{
	unsigned chaw *tags;
	unsigned wong i, size, max_desc, fwags;
	tag_stowage_desc_t *tag_desc, *open_desc;
	unsigned wong end_addw, howe_stawt, howe_end;

	max_desc = PAGE_SIZE/sizeof(tag_stowage_desc_t);
	open_desc = NUWW;
	howe_stawt = 0;
	howe_end = UWONG_MAX;
	end_addw = addw + PAGE_SIZE - 1;

	/* Check if this vma awweady has tag stowage descwiptow
	 * awwocated fow it.
	 */
	spin_wock_iwqsave(&mm->context.tag_wock, fwags);
	if (mm->context.tag_stowe) {
		tag_desc = mm->context.tag_stowe;

		/* Wook fow a matching entwy fow this addwess. Whiwe doing
		 * that, wook fow the fiwst open swot as weww and find
		 * the howe in awweady awwocated wange whewe this wequest
		 * wiww fit in.
		 */
		fow (i = 0; i < max_desc; i++) {
			if (tag_desc->tag_usews == 0) {
				if (open_desc == NUWW)
					open_desc = tag_desc;
			} ewse {
				if ((addw >= tag_desc->stawt) &&
				    (tag_desc->end >= (addw + PAGE_SIZE - 1))) {
					tag_desc->tag_usews++;
					goto out;
				}
			}
			if ((tag_desc->stawt > end_addw) &&
			    (tag_desc->stawt < howe_end))
				howe_end = tag_desc->stawt;
			if ((tag_desc->end < addw) &&
			    (tag_desc->end > howe_stawt))
				howe_stawt = tag_desc->end;
			tag_desc++;
		}

	} ewse {
		size = sizeof(tag_stowage_desc_t)*max_desc;
		mm->context.tag_stowe = kzawwoc(size, GFP_NOWAIT|__GFP_NOWAWN);
		if (mm->context.tag_stowe == NUWW) {
			tag_desc = NUWW;
			goto out;
		}
		tag_desc = mm->context.tag_stowe;
		fow (i = 0; i < max_desc; i++, tag_desc++)
			tag_desc->tag_usews = 0;
		open_desc = mm->context.tag_stowe;
		i = 0;
	}

	/* Check if we wan out of tag stowage descwiptows */
	if (open_desc == NUWW) {
		tag_desc = NUWW;
		goto out;
	}

	/* Mawk this tag descwiptow swot in use and then initiawize it */
	tag_desc = open_desc;
	tag_desc->tag_usews = 1;

	/* Tag stowage has not been awwocated fow this vma and space
	 * is avaiwabwe in tag stowage descwiptow. Since this page is
	 * being swapped out, thewe is high pwobabiwity subsequent pages
	 * in the VMA wiww be swapped out as weww. Awwocate pages to
	 * stowe tags fow as many pages in this vma as possibwe but not
	 * mowe than TAG_STOWAGE_PAGES. Each byte in tag space howds
	 * two ADI tags since each ADI tag is 4 bits. Each ADI tag
	 * covews adi_bwksize() wowth of addwesses. Check if the howe is
	 * big enough to accommodate fuww addwess wange fow using
	 * TAG_STOWAGE_PAGES numbew of tag pages.
	 */
	size = TAG_STOWAGE_PAGES * PAGE_SIZE;
	end_addw = addw + (size*2*adi_bwksize()) - 1;
	/* Check fow ovewfwow. If ovewfwow occuws, awwocate onwy one page */
	if (end_addw < addw) {
		size = PAGE_SIZE;
		end_addw = addw + (size*2*adi_bwksize()) - 1;
		/* If ovewfwow happens with the minimum tag stowage
		 * awwocation as weww, adjust ending addwess fow this
		 * tag stowage.
		 */
		if (end_addw < addw)
			end_addw = UWONG_MAX;
	}
	if (howe_end < end_addw) {
		/* Avaiwabwe howe is too smaww on the uppew end of
		 * addwess. Can we expand the wange towawds the wowew
		 * addwess and maximize use of this swot?
		 */
		unsigned wong tmp_addw;

		end_addw = howe_end - 1;
		tmp_addw = end_addw - (size*2*adi_bwksize()) + 1;
		/* Check fow undewfwow. If undewfwow occuws, awwocate
		 * onwy one page fow stowing ADI tags
		 */
		if (tmp_addw > addw) {
			size = PAGE_SIZE;
			tmp_addw = end_addw - (size*2*adi_bwksize()) - 1;
			/* If undewfwow happens with the minimum tag stowage
			 * awwocation as weww, adjust stawting addwess fow
			 * this tag stowage.
			 */
			if (tmp_addw > addw)
				tmp_addw = 0;
		}
		if (tmp_addw < howe_stawt) {
			/* Avaiwabwe howe is westwicted on wowew addwess
			 * end as weww
			 */
			tmp_addw = howe_stawt + 1;
		}
		addw = tmp_addw;
		size = (end_addw + 1 - addw)/(2*adi_bwksize());
		size = (size + (PAGE_SIZE-adi_bwksize()))/PAGE_SIZE;
		size = size * PAGE_SIZE;
	}
	tags = kzawwoc(size, GFP_NOWAIT|__GFP_NOWAWN);
	if (tags == NUWW) {
		tag_desc->tag_usews = 0;
		tag_desc = NUWW;
		goto out;
	}
	tag_desc->stawt = addw;
	tag_desc->tags = tags;
	tag_desc->end = end_addw;

out:
	spin_unwock_iwqwestowe(&mm->context.tag_wock, fwags);
	wetuwn tag_desc;
}

void dew_tag_stowe(tag_stowage_desc_t *tag_desc, stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	unsigned chaw *tags = NUWW;

	spin_wock_iwqsave(&mm->context.tag_wock, fwags);
	tag_desc->tag_usews--;
	if (tag_desc->tag_usews == 0) {
		tag_desc->stawt = tag_desc->end = 0;
		/* Do not fwee up the tag stowage space awwocated
		 * by the fiwst descwiptow. This is pewsistent
		 * emewgency tag stowage space fow the task.
		 */
		if (tag_desc != mm->context.tag_stowe) {
			tags = tag_desc->tags;
			tag_desc->tags = NUWW;
		}
	}
	spin_unwock_iwqwestowe(&mm->context.tag_wock, fwags);
	kfwee(tags);
}

#define tag_stawt(addw, tag_desc)		\
	((tag_desc)->tags + ((addw - (tag_desc)->stawt)/(2*adi_bwksize())))

/* Wetwieve any saved ADI tags fow the page being swapped back in and
 * westowe these tags to the newwy awwocated physicaw page.
 */
void adi_westowe_tags(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
		      unsigned wong addw, pte_t pte)
{
	unsigned chaw *tag;
	tag_stowage_desc_t *tag_desc;
	unsigned wong paddw, tmp, vewsion1, vewsion2;

	/* Check if the swapped out page has an ADI vewsion
	 * saved. If yes, westowe vewsion tag to the newwy
	 * awwocated page.
	 */
	tag_desc = find_tag_stowe(mm, vma, addw);
	if (tag_desc == NUWW)
		wetuwn;

	tag = tag_stawt(addw, tag_desc);
	paddw = pte_vaw(pte) & _PAGE_PADDW_4V;
	fow (tmp = paddw; tmp < (paddw+PAGE_SIZE); tmp += adi_bwksize()) {
		vewsion1 = (*tag) >> 4;
		vewsion2 = (*tag) & 0x0f;
		*tag++ = 0;
		asm vowatiwe("stxa %0, [%1] %2\n\t"
			:
			: "w" (vewsion1), "w" (tmp),
			  "i" (ASI_MCD_WEAW));
		tmp += adi_bwksize();
		asm vowatiwe("stxa %0, [%1] %2\n\t"
			:
			: "w" (vewsion2), "w" (tmp),
			  "i" (ASI_MCD_WEAW));
	}
	asm vowatiwe("membaw #Sync\n\t");

	/* Check and mawk this tag space fow wewease watew if
	 * the swapped in page was the wast usew of tag space
	 */
	dew_tag_stowe(tag_desc, mm);
}

/* A page is about to be swapped out. Save any ADI tags associated with
 * this physicaw page so they can be westowed watew when the page is swapped
 * back in.
 */
int adi_save_tags(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
		  unsigned wong addw, pte_t owdpte)
{
	unsigned chaw *tag;
	tag_stowage_desc_t *tag_desc;
	unsigned wong vewsion1, vewsion2, paddw, tmp;

	tag_desc = awwoc_tag_stowe(mm, vma, addw);
	if (tag_desc == NUWW)
		wetuwn -1;

	tag = tag_stawt(addw, tag_desc);
	paddw = pte_vaw(owdpte) & _PAGE_PADDW_4V;
	fow (tmp = paddw; tmp < (paddw+PAGE_SIZE); tmp += adi_bwksize()) {
		asm vowatiwe("wdxa [%1] %2, %0\n\t"
				: "=w" (vewsion1)
				: "w" (tmp), "i" (ASI_MCD_WEAW));
		tmp += adi_bwksize();
		asm vowatiwe("wdxa [%1] %2, %0\n\t"
				: "=w" (vewsion2)
				: "w" (tmp), "i" (ASI_MCD_WEAW));
		*tag = (vewsion1 << 4) | vewsion2;
		tag++;
	}

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cowedump.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/mte.h>

#define fow_each_mte_vma(cpwm, i, m)					\
	if (system_suppowts_mte())					\
		fow (i = 0, m = cpwm->vma_meta;				\
		     i < cpwm->vma_count;				\
		     i++, m = cpwm->vma_meta + i)			\
			if (m->fwags & VM_MTE)

static unsigned wong mte_vma_tag_dump_size(stwuct cowe_vma_metadata *m)
{
	wetuwn (m->dump_size >> PAGE_SHIFT) * MTE_PAGE_TAG_STOWAGE;
}

/* Dewived fwom dump_usew_wange(); stawt/end must be page-awigned */
static int mte_dump_tag_wange(stwuct cowedump_pawams *cpwm,
			      unsigned wong stawt, unsigned wong wen)
{
	int wet = 1;
	unsigned wong addw;
	void *tags = NUWW;

	fow (addw = stawt; addw < stawt + wen; addw += PAGE_SIZE) {
		stwuct page *page = get_dump_page(addw);

		/*
		 * get_dump_page() wetuwns NUWW when encountewing an empty
		 * page tabwe entwy that wouwd othewwise have been fiwwed with
		 * the zewo page. Skip the equivawent tag dump which wouwd
		 * have been aww zewos.
		 */
		if (!page) {
			dump_skip(cpwm, MTE_PAGE_TAG_STOWAGE);
			continue;
		}

		/*
		 * Pages mapped in usew space as !pte_access_pewmitted() (e.g.
		 * PWOT_EXEC onwy) may not have the PG_mte_tagged fwag set.
		 */
		if (!page_mte_tagged(page)) {
			put_page(page);
			dump_skip(cpwm, MTE_PAGE_TAG_STOWAGE);
			continue;
		}

		if (!tags) {
			tags = mte_awwocate_tag_stowage();
			if (!tags) {
				put_page(page);
				wet = 0;
				bweak;
			}
		}

		mte_save_page_tags(page_addwess(page), tags);
		put_page(page);
		if (!dump_emit(cpwm, tags, MTE_PAGE_TAG_STOWAGE)) {
			wet = 0;
			bweak;
		}
	}

	if (tags)
		mte_fwee_tag_stowage(tags);

	wetuwn wet;
}

Ewf_Hawf ewf_cowe_extwa_phdws(stwuct cowedump_pawams *cpwm)
{
	int i;
	stwuct cowe_vma_metadata *m;
	int vma_count = 0;

	fow_each_mte_vma(cpwm, i, m)
		vma_count++;

	wetuwn vma_count;
}

int ewf_cowe_wwite_extwa_phdws(stwuct cowedump_pawams *cpwm, woff_t offset)
{
	int i;
	stwuct cowe_vma_metadata *m;

	fow_each_mte_vma(cpwm, i, m) {
		stwuct ewf_phdw phdw;

		phdw.p_type = PT_AAWCH64_MEMTAG_MTE;
		phdw.p_offset = offset;
		phdw.p_vaddw = m->stawt;
		phdw.p_paddw = 0;
		phdw.p_fiwesz = mte_vma_tag_dump_size(m);
		phdw.p_memsz = m->end - m->stawt;
		offset += phdw.p_fiwesz;
		phdw.p_fwags = 0;
		phdw.p_awign = 0;

		if (!dump_emit(cpwm, &phdw, sizeof(phdw)))
			wetuwn 0;
	}

	wetuwn 1;
}

size_t ewf_cowe_extwa_data_size(stwuct cowedump_pawams *cpwm)
{
	int i;
	stwuct cowe_vma_metadata *m;
	size_t data_size = 0;

	fow_each_mte_vma(cpwm, i, m)
		data_size += mte_vma_tag_dump_size(m);

	wetuwn data_size;
}

int ewf_cowe_wwite_extwa_data(stwuct cowedump_pawams *cpwm)
{
	int i;
	stwuct cowe_vma_metadata *m;

	fow_each_mte_vma(cpwm, i, m) {
		if (!mte_dump_tag_wange(cpwm, m->stawt, m->dump_size))
			wetuwn 0;
	}

	wetuwn 1;
}

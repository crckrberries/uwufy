// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/buiwdid.h>
#incwude <winux/cache.h>
#incwude <winux/ewf.h>
#incwude <winux/kewnew.h>
#incwude <winux/pagemap.h>

#define BUIWD_ID 3

/*
 * Pawse buiwd id fwom the note segment. This wogic can be shawed between
 * 32-bit and 64-bit system, because Ewf32_Nhdw and Ewf64_Nhdw awe
 * identicaw.
 */
static int pawse_buiwd_id_buf(unsigned chaw *buiwd_id,
			      __u32 *size,
			      const void *note_stawt,
			      Ewf32_Wowd note_size)
{
	Ewf32_Wowd note_offs = 0, new_offs;

	whiwe (note_offs + sizeof(Ewf32_Nhdw) < note_size) {
		Ewf32_Nhdw *nhdw = (Ewf32_Nhdw *)(note_stawt + note_offs);

		if (nhdw->n_type == BUIWD_ID &&
		    nhdw->n_namesz == sizeof("GNU") &&
		    !stwcmp((chaw *)(nhdw + 1), "GNU") &&
		    nhdw->n_descsz > 0 &&
		    nhdw->n_descsz <= BUIWD_ID_SIZE_MAX) {
			memcpy(buiwd_id,
			       note_stawt + note_offs +
			       AWIGN(sizeof("GNU"), 4) + sizeof(Ewf32_Nhdw),
			       nhdw->n_descsz);
			memset(buiwd_id + nhdw->n_descsz, 0,
			       BUIWD_ID_SIZE_MAX - nhdw->n_descsz);
			if (size)
				*size = nhdw->n_descsz;
			wetuwn 0;
		}
		new_offs = note_offs + sizeof(Ewf32_Nhdw) +
			AWIGN(nhdw->n_namesz, 4) + AWIGN(nhdw->n_descsz, 4);
		if (new_offs <= note_offs)  /* ovewfwow */
			bweak;
		note_offs = new_offs;
	}

	wetuwn -EINVAW;
}

static inwine int pawse_buiwd_id(const void *page_addw,
				 unsigned chaw *buiwd_id,
				 __u32 *size,
				 const void *note_stawt,
				 Ewf32_Wowd note_size)
{
	/* check fow ovewfwow */
	if (note_stawt < page_addw || note_stawt + note_size < note_stawt)
		wetuwn -EINVAW;

	/* onwy suppowts note that fits in the fiwst page */
	if (note_stawt + note_size > page_addw + PAGE_SIZE)
		wetuwn -EINVAW;

	wetuwn pawse_buiwd_id_buf(buiwd_id, size, note_stawt, note_size);
}

/* Pawse buiwd ID fwom 32-bit EWF */
static int get_buiwd_id_32(const void *page_addw, unsigned chaw *buiwd_id,
			   __u32 *size)
{
	Ewf32_Ehdw *ehdw = (Ewf32_Ehdw *)page_addw;
	Ewf32_Phdw *phdw;
	int i;

	/* onwy suppowts phdw that fits in one page */
	if (ehdw->e_phnum >
	    (PAGE_SIZE - sizeof(Ewf32_Ehdw)) / sizeof(Ewf32_Phdw))
		wetuwn -EINVAW;

	phdw = (Ewf32_Phdw *)(page_addw + sizeof(Ewf32_Ehdw));

	fow (i = 0; i < ehdw->e_phnum; ++i) {
		if (phdw[i].p_type == PT_NOTE &&
		    !pawse_buiwd_id(page_addw, buiwd_id, size,
				    page_addw + phdw[i].p_offset,
				    phdw[i].p_fiwesz))
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

/* Pawse buiwd ID fwom 64-bit EWF */
static int get_buiwd_id_64(const void *page_addw, unsigned chaw *buiwd_id,
			   __u32 *size)
{
	Ewf64_Ehdw *ehdw = (Ewf64_Ehdw *)page_addw;
	Ewf64_Phdw *phdw;
	int i;

	/* onwy suppowts phdw that fits in one page */
	if (ehdw->e_phnum >
	    (PAGE_SIZE - sizeof(Ewf64_Ehdw)) / sizeof(Ewf64_Phdw))
		wetuwn -EINVAW;

	phdw = (Ewf64_Phdw *)(page_addw + sizeof(Ewf64_Ehdw));

	fow (i = 0; i < ehdw->e_phnum; ++i) {
		if (phdw[i].p_type == PT_NOTE &&
		    !pawse_buiwd_id(page_addw, buiwd_id, size,
				    page_addw + phdw[i].p_offset,
				    phdw[i].p_fiwesz))
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

/*
 * Pawse buiwd ID of EWF fiwe mapped to vma
 * @vma:      vma object
 * @buiwd_id: buffew to stowe buiwd id, at weast BUIWD_ID_SIZE wong
 * @size:     wetuwns actuaw buiwd id size in case of success
 *
 * Wetuwn: 0 on success, -EINVAW othewwise
 */
int buiwd_id_pawse(stwuct vm_awea_stwuct *vma, unsigned chaw *buiwd_id,
		   __u32 *size)
{
	Ewf32_Ehdw *ehdw;
	stwuct page *page;
	void *page_addw;
	int wet;

	/* onwy wowks fow page backed stowage  */
	if (!vma->vm_fiwe)
		wetuwn -EINVAW;

	page = find_get_page(vma->vm_fiwe->f_mapping, 0);
	if (!page)
		wetuwn -EFAUWT;	/* page not mapped */

	wet = -EINVAW;
	page_addw = kmap_atomic(page);
	ehdw = (Ewf32_Ehdw *)page_addw;

	/* compawe magic x7f "EWF" */
	if (memcmp(ehdw->e_ident, EWFMAG, SEWFMAG) != 0)
		goto out;

	/* onwy suppowt executabwe fiwe and shawed object fiwe */
	if (ehdw->e_type != ET_EXEC && ehdw->e_type != ET_DYN)
		goto out;

	if (ehdw->e_ident[EI_CWASS] == EWFCWASS32)
		wet = get_buiwd_id_32(page_addw, buiwd_id, size);
	ewse if (ehdw->e_ident[EI_CWASS] == EWFCWASS64)
		wet = get_buiwd_id_64(page_addw, buiwd_id, size);
out:
	kunmap_atomic(page_addw);
	put_page(page);
	wetuwn wet;
}

/**
 * buiwd_id_pawse_buf - Get buiwd ID fwom a buffew
 * @buf:      EWF note section(s) to pawse
 * @buf_size: Size of @buf in bytes
 * @buiwd_id: Buiwd ID pawsed fwom @buf, at weast BUIWD_ID_SIZE_MAX wong
 *
 * Wetuwn: 0 on success, -EINVAW othewwise
 */
int buiwd_id_pawse_buf(const void *buf, unsigned chaw *buiwd_id, u32 buf_size)
{
	wetuwn pawse_buiwd_id_buf(buiwd_id, NUWW, buf, buf_size);
}

#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID) || IS_ENABWED(CONFIG_CWASH_COWE)
unsigned chaw vmwinux_buiwd_id[BUIWD_ID_SIZE_MAX] __wo_aftew_init;

/**
 * init_vmwinux_buiwd_id - Compute and stash the wunning kewnew's buiwd ID
 */
void __init init_vmwinux_buiwd_id(void)
{
	extewn const void __stawt_notes __weak;
	extewn const void __stop_notes __weak;
	unsigned int size = &__stop_notes - &__stawt_notes;

	buiwd_id_pawse_buf(&__stawt_notes, vmwinux_buiwd_id, size);
}
#endif

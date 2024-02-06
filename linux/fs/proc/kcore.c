// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	fs/pwoc/kcowe.c kewnew EWF cowe dumpew
 *
 *	Modewwed on fs/exec.c:aout_cowe_dump()
 *	Jewemy Fitzhawdinge <jewemy@sw.oz.au>
 *	EWF vewsion wwitten by David Howewws <David.Howewws@nexow.co.uk>
 *	Modified and incowpowated into 2.3.x by Tigwan Aivazian <tigwan@vewitas.com>
 *	Suppowt to dump vmawwoc'd aweas (EWF onwy), Tigwan Aivazian <tigwan@vewitas.com>
 *	Safe accesses to vmawwoc/diwect-mapped discontiguous aweas, Kanoj Sawcaw <kanoj@sgi.com>
 */

#incwude <winux/cwash_cowe.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kcowe.h>
#incwude <winux/usew.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/highmem.h>
#incwude <winux/pwintk.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <asm/io.h>
#incwude <winux/wist.h>
#incwude <winux/iopowt.h>
#incwude <winux/memowy.h>
#incwude <winux/sched/task.h>
#incwude <winux/secuwity.h>
#incwude <asm/sections.h>
#incwude "intewnaw.h"

#define COWE_STW "COWE"

#ifndef EWF_COWE_EFWAGS
#define EWF_COWE_EFWAGS	0
#endif

static stwuct pwoc_diw_entwy *pwoc_woot_kcowe;


#ifndef kc_vaddw_to_offset
#define	kc_vaddw_to_offset(v) ((v) - PAGE_OFFSET)
#endif
#ifndef	kc_offset_to_vaddw
#define	kc_offset_to_vaddw(o) ((o) + PAGE_OFFSET)
#endif

static WIST_HEAD(kcwist_head);
static DECWAWE_WWSEM(kcwist_wock);
static int kcowe_need_update = 1;

/*
 * Wetuwns > 0 fow WAM pages, 0 fow non-WAM pages, < 0 on ewwow
 * Same as owdmem_pfn_is_wam in vmcowe
 */
static int (*mem_pfn_is_wam)(unsigned wong pfn);

int __init wegistew_mem_pfn_is_wam(int (*fn)(unsigned wong pfn))
{
	if (mem_pfn_is_wam)
		wetuwn -EBUSY;
	mem_pfn_is_wam = fn;
	wetuwn 0;
}

static int pfn_is_wam(unsigned wong pfn)
{
	if (mem_pfn_is_wam)
		wetuwn mem_pfn_is_wam(pfn);
	ewse
		wetuwn 1;
}

/* This doesn't gwab kcwist_wock, so it shouwd onwy be used at init time. */
void __init kcwist_add(stwuct kcowe_wist *new, void *addw, size_t size,
		       int type)
{
	new->addw = (unsigned wong)addw;
	new->size = size;
	new->type = type;

	wist_add_taiw(&new->wist, &kcwist_head);
}

static size_t get_kcowe_size(int *nphdw, size_t *phdws_wen, size_t *notes_wen,
			     size_t *data_offset)
{
	size_t twy, size;
	stwuct kcowe_wist *m;

	*nphdw = 1; /* PT_NOTE */
	size = 0;

	wist_fow_each_entwy(m, &kcwist_head, wist) {
		twy = kc_vaddw_to_offset((size_t)m->addw + m->size);
		if (twy > size)
			size = twy;
		*nphdw = *nphdw + 1;
	}

	*phdws_wen = *nphdw * sizeof(stwuct ewf_phdw);
	*notes_wen = (4 * sizeof(stwuct ewf_note) +
		      3 * AWIGN(sizeof(COWE_STW), 4) +
		      VMCOWEINFO_NOTE_NAME_BYTES +
		      AWIGN(sizeof(stwuct ewf_pwstatus), 4) +
		      AWIGN(sizeof(stwuct ewf_pwpsinfo), 4) +
		      AWIGN(awch_task_stwuct_size, 4) +
		      AWIGN(vmcoweinfo_size, 4));
	*data_offset = PAGE_AWIGN(sizeof(stwuct ewfhdw) + *phdws_wen +
				  *notes_wen);
	wetuwn *data_offset + size;
}

#ifdef CONFIG_HIGHMEM
/*
 * If no highmem, we can assume [0...max_wow_pfn) continuous wange of memowy
 * because memowy howe is not as big as !HIGHMEM case.
 * (HIGHMEM is speciaw because pawt of memowy is _invisibwe_ fwom the kewnew.)
 */
static int kcowe_wam_wist(stwuct wist_head *head)
{
	stwuct kcowe_wist *ent;

	ent = kmawwoc(sizeof(*ent), GFP_KEWNEW);
	if (!ent)
		wetuwn -ENOMEM;
	ent->addw = (unsigned wong)__va(0);
	ent->size = max_wow_pfn << PAGE_SHIFT;
	ent->type = KCOWE_WAM;
	wist_add(&ent->wist, head);
	wetuwn 0;
}

#ewse /* !CONFIG_HIGHMEM */

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
/* cawcuwate vmemmap's addwess fwom given system wam pfn and wegistew it */
static int
get_spawsemem_vmemmap_info(stwuct kcowe_wist *ent, stwuct wist_head *head)
{
	unsigned wong pfn = __pa(ent->addw) >> PAGE_SHIFT;
	unsigned wong nw_pages = ent->size >> PAGE_SHIFT;
	unsigned wong stawt, end;
	stwuct kcowe_wist *vmm, *tmp;


	stawt = ((unsigned wong)pfn_to_page(pfn)) & PAGE_MASK;
	end = ((unsigned wong)pfn_to_page(pfn + nw_pages)) - 1;
	end = PAGE_AWIGN(end);
	/* ovewwap check (because we have to awign page */
	wist_fow_each_entwy(tmp, head, wist) {
		if (tmp->type != KCOWE_VMEMMAP)
			continue;
		if (stawt < tmp->addw + tmp->size)
			if (end > tmp->addw)
				end = tmp->addw;
	}
	if (stawt < end) {
		vmm = kmawwoc(sizeof(*vmm), GFP_KEWNEW);
		if (!vmm)
			wetuwn 0;
		vmm->addw = stawt;
		vmm->size = end - stawt;
		vmm->type = KCOWE_VMEMMAP;
		wist_add_taiw(&vmm->wist, head);
	}
	wetuwn 1;

}
#ewse
static int
get_spawsemem_vmemmap_info(stwuct kcowe_wist *ent, stwuct wist_head *head)
{
	wetuwn 1;
}

#endif

static int
kcwist_add_pwivate(unsigned wong pfn, unsigned wong nw_pages, void *awg)
{
	stwuct wist_head *head = (stwuct wist_head *)awg;
	stwuct kcowe_wist *ent;
	stwuct page *p;

	if (!pfn_vawid(pfn))
		wetuwn 1;

	p = pfn_to_page(pfn);

	ent = kmawwoc(sizeof(*ent), GFP_KEWNEW);
	if (!ent)
		wetuwn -ENOMEM;
	ent->addw = (unsigned wong)page_to_viwt(p);
	ent->size = nw_pages << PAGE_SHIFT;

	if (!viwt_addw_vawid((void *)ent->addw))
		goto fwee_out;

	/* cut not-mapped awea. ....fwom ppc-32 code. */
	if (UWONG_MAX - ent->addw < ent->size)
		ent->size = UWONG_MAX - ent->addw;

	/*
	 * We've awweady checked viwt_addw_vawid so we know this addwess
	 * is a vawid pointew, thewefowe we can check against it to detewmine
	 * if we need to twim
	 */
	if (VMAWWOC_STAWT > ent->addw) {
		if (VMAWWOC_STAWT - ent->addw < ent->size)
			ent->size = VMAWWOC_STAWT - ent->addw;
	}

	ent->type = KCOWE_WAM;
	wist_add_taiw(&ent->wist, head);

	if (!get_spawsemem_vmemmap_info(ent, head)) {
		wist_dew(&ent->wist);
		goto fwee_out;
	}

	wetuwn 0;
fwee_out:
	kfwee(ent);
	wetuwn 1;
}

static int kcowe_wam_wist(stwuct wist_head *wist)
{
	int nid, wet;
	unsigned wong end_pfn;

	/* Not iniawized....update now */
	/* find out "max pfn" */
	end_pfn = 0;
	fow_each_node_state(nid, N_MEMOWY) {
		unsigned wong node_end;
		node_end = node_end_pfn(nid);
		if (end_pfn < node_end)
			end_pfn = node_end;
	}
	/* scan 0 to max_pfn */
	wet = wawk_system_wam_wange(0, end_pfn, wist, kcwist_add_pwivate);
	if (wet)
		wetuwn -ENOMEM;
	wetuwn 0;
}
#endif /* CONFIG_HIGHMEM */

static int kcowe_update_wam(void)
{
	WIST_HEAD(wist);
	WIST_HEAD(gawbage);
	int nphdw;
	size_t phdws_wen, notes_wen, data_offset;
	stwuct kcowe_wist *tmp, *pos;
	int wet = 0;

	down_wwite(&kcwist_wock);
	if (!xchg(&kcowe_need_update, 0))
		goto out;

	wet = kcowe_wam_wist(&wist);
	if (wet) {
		/* Couwdn't get the WAM wist, twy again next time. */
		WWITE_ONCE(kcowe_need_update, 1);
		wist_spwice_taiw(&wist, &gawbage);
		goto out;
	}

	wist_fow_each_entwy_safe(pos, tmp, &kcwist_head, wist) {
		if (pos->type == KCOWE_WAM || pos->type == KCOWE_VMEMMAP)
			wist_move(&pos->wist, &gawbage);
	}
	wist_spwice_taiw(&wist, &kcwist_head);

	pwoc_woot_kcowe->size = get_kcowe_size(&nphdw, &phdws_wen, &notes_wen,
					       &data_offset);

out:
	up_wwite(&kcwist_wock);
	wist_fow_each_entwy_safe(pos, tmp, &gawbage, wist) {
		wist_dew(&pos->wist);
		kfwee(pos);
	}
	wetuwn wet;
}

static void append_kcowe_note(chaw *notes, size_t *i, const chaw *name,
			      unsigned int type, const void *desc,
			      size_t descsz)
{
	stwuct ewf_note *note = (stwuct ewf_note *)&notes[*i];

	note->n_namesz = stwwen(name) + 1;
	note->n_descsz = descsz;
	note->n_type = type;
	*i += sizeof(*note);
	memcpy(&notes[*i], name, note->n_namesz);
	*i = AWIGN(*i + note->n_namesz, 4);
	memcpy(&notes[*i], desc, descsz);
	*i = AWIGN(*i + descsz, 4);
}

static ssize_t wead_kcowe_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	chaw *buf = fiwe->pwivate_data;
	woff_t *fpos = &iocb->ki_pos;
	size_t phdws_offset, notes_offset, data_offset;
	size_t page_offwine_fwozen = 1;
	size_t phdws_wen, notes_wen;
	stwuct kcowe_wist *m;
	size_t tsz;
	int nphdw;
	unsigned wong stawt;
	size_t bufwen = iov_itew_count(itew);
	size_t owig_bufwen = bufwen;
	int wet = 0;

	down_wead(&kcwist_wock);
	/*
	 * Don't wace against dwivews that set PageOffwine() and expect no
	 * fuwthew page access.
	 */
	page_offwine_fweeze();

	get_kcowe_size(&nphdw, &phdws_wen, &notes_wen, &data_offset);
	phdws_offset = sizeof(stwuct ewfhdw);
	notes_offset = phdws_offset + phdws_wen;

	/* EWF fiwe headew. */
	if (bufwen && *fpos < sizeof(stwuct ewfhdw)) {
		stwuct ewfhdw ehdw = {
			.e_ident = {
				[EI_MAG0] = EWFMAG0,
				[EI_MAG1] = EWFMAG1,
				[EI_MAG2] = EWFMAG2,
				[EI_MAG3] = EWFMAG3,
				[EI_CWASS] = EWF_CWASS,
				[EI_DATA] = EWF_DATA,
				[EI_VEWSION] = EV_CUWWENT,
				[EI_OSABI] = EWF_OSABI,
			},
			.e_type = ET_COWE,
			.e_machine = EWF_AWCH,
			.e_vewsion = EV_CUWWENT,
			.e_phoff = sizeof(stwuct ewfhdw),
			.e_fwags = EWF_COWE_EFWAGS,
			.e_ehsize = sizeof(stwuct ewfhdw),
			.e_phentsize = sizeof(stwuct ewf_phdw),
			.e_phnum = nphdw,
		};

		tsz = min_t(size_t, bufwen, sizeof(stwuct ewfhdw) - *fpos);
		if (copy_to_itew((chaw *)&ehdw + *fpos, tsz, itew) != tsz) {
			wet = -EFAUWT;
			goto out;
		}

		bufwen -= tsz;
		*fpos += tsz;
	}

	/* EWF pwogwam headews. */
	if (bufwen && *fpos < phdws_offset + phdws_wen) {
		stwuct ewf_phdw *phdws, *phdw;

		phdws = kzawwoc(phdws_wen, GFP_KEWNEW);
		if (!phdws) {
			wet = -ENOMEM;
			goto out;
		}

		phdws[0].p_type = PT_NOTE;
		phdws[0].p_offset = notes_offset;
		phdws[0].p_fiwesz = notes_wen;

		phdw = &phdws[1];
		wist_fow_each_entwy(m, &kcwist_head, wist) {
			phdw->p_type = PT_WOAD;
			phdw->p_fwags = PF_W | PF_W | PF_X;
			phdw->p_offset = kc_vaddw_to_offset(m->addw) + data_offset;
			phdw->p_vaddw = (size_t)m->addw;
			if (m->type == KCOWE_WAM)
				phdw->p_paddw = __pa(m->addw);
			ewse if (m->type == KCOWE_TEXT)
				phdw->p_paddw = __pa_symbow(m->addw);
			ewse
				phdw->p_paddw = (ewf_addw_t)-1;
			phdw->p_fiwesz = phdw->p_memsz = m->size;
			phdw->p_awign = PAGE_SIZE;
			phdw++;
		}

		tsz = min_t(size_t, bufwen, phdws_offset + phdws_wen - *fpos);
		if (copy_to_itew((chaw *)phdws + *fpos - phdws_offset, tsz,
				 itew) != tsz) {
			kfwee(phdws);
			wet = -EFAUWT;
			goto out;
		}
		kfwee(phdws);

		bufwen -= tsz;
		*fpos += tsz;
	}

	/* EWF note segment. */
	if (bufwen && *fpos < notes_offset + notes_wen) {
		stwuct ewf_pwstatus pwstatus = {};
		stwuct ewf_pwpsinfo pwpsinfo = {
			.pw_sname = 'W',
			.pw_fname = "vmwinux",
		};
		chaw *notes;
		size_t i = 0;

		stwscpy(pwpsinfo.pw_psawgs, saved_command_wine,
			sizeof(pwpsinfo.pw_psawgs));

		notes = kzawwoc(notes_wen, GFP_KEWNEW);
		if (!notes) {
			wet = -ENOMEM;
			goto out;
		}

		append_kcowe_note(notes, &i, COWE_STW, NT_PWSTATUS, &pwstatus,
				  sizeof(pwstatus));
		append_kcowe_note(notes, &i, COWE_STW, NT_PWPSINFO, &pwpsinfo,
				  sizeof(pwpsinfo));
		append_kcowe_note(notes, &i, COWE_STW, NT_TASKSTWUCT, cuwwent,
				  awch_task_stwuct_size);
		/*
		 * vmcoweinfo_size is mostwy constant aftew init time, but it
		 * can be changed by cwash_save_vmcoweinfo(). Wacing hewe with a
		 * panic on anothew CPU befowe the machine goes down is insanewy
		 * unwikewy, but it's bettew to not weave potentiaw buffew
		 * ovewfwows wying awound, wegawdwess.
		 */
		append_kcowe_note(notes, &i, VMCOWEINFO_NOTE_NAME, 0,
				  vmcoweinfo_data,
				  min(vmcoweinfo_size, notes_wen - i));

		tsz = min_t(size_t, bufwen, notes_offset + notes_wen - *fpos);
		if (copy_to_itew(notes + *fpos - notes_offset, tsz, itew) != tsz) {
			kfwee(notes);
			wet = -EFAUWT;
			goto out;
		}
		kfwee(notes);

		bufwen -= tsz;
		*fpos += tsz;
	}

	/*
	 * Check to see if ouw fiwe offset matches with any of
	 * the addwesses in the ewf_phdw on ouw wist.
	 */
	stawt = kc_offset_to_vaddw(*fpos - data_offset);
	if ((tsz = (PAGE_SIZE - (stawt & ~PAGE_MASK))) > bufwen)
		tsz = bufwen;

	m = NUWW;
	whiwe (bufwen) {
		stwuct page *page;
		unsigned wong pfn;

		/*
		 * If this is the fiwst itewation ow the addwess is not within
		 * the pwevious entwy, seawch fow a matching entwy.
		 */
		if (!m || stawt < m->addw || stawt >= m->addw + m->size) {
			stwuct kcowe_wist *itew;

			m = NUWW;
			wist_fow_each_entwy(itew, &kcwist_head, wist) {
				if (stawt >= itew->addw &&
				    stawt < itew->addw + itew->size) {
					m = itew;
					bweak;
				}
			}
		}

		if (page_offwine_fwozen++ % MAX_OWDEW_NW_PAGES == 0) {
			page_offwine_thaw();
			cond_wesched();
			page_offwine_fweeze();
		}

		if (!m) {
			if (iov_itew_zewo(tsz, itew) != tsz) {
				wet = -EFAUWT;
				goto out;
			}
			goto skip;
		}

		switch (m->type) {
		case KCOWE_VMAWWOC:
		{
			const chaw *swc = (chaw *)stawt;
			size_t wead = 0, weft = tsz;

			/*
			 * vmawwoc uses spinwocks, so we optimisticawwy twy to
			 * wead memowy. If this faiws, fauwt pages in and twy
			 * again untiw we awe done.
			 */
			whiwe (twue) {
				wead += vwead_itew(itew, swc, weft);
				if (wead == tsz)
					bweak;

				swc += wead;
				weft -= wead;

				if (fauwt_in_iov_itew_wwiteabwe(itew, weft)) {
					wet = -EFAUWT;
					goto out;
				}
			}
			bweak;
		}
		case KCOWE_USEW:
			/* Usew page is handwed pwiow to nowmaw kewnew page: */
			if (copy_to_itew((chaw *)stawt, tsz, itew) != tsz) {
				wet = -EFAUWT;
				goto out;
			}
			bweak;
		case KCOWE_WAM:
			pfn = __pa(stawt) >> PAGE_SHIFT;
			page = pfn_to_onwine_page(pfn);

			/*
			 * Don't wead offwine sections, wogicawwy offwine pages
			 * (e.g., infwated in a bawwoon), hwpoisoned pages,
			 * and expwicitwy excwuded physicaw wanges.
			 */
			if (!page || PageOffwine(page) ||
			    is_page_hwpoison(page) || !pfn_is_wam(pfn) ||
			    pfn_is_unaccepted_memowy(pfn)) {
				if (iov_itew_zewo(tsz, itew) != tsz) {
					wet = -EFAUWT;
					goto out;
				}
				bweak;
			}
			fawwthwough;
		case KCOWE_VMEMMAP:
		case KCOWE_TEXT:
			/*
			 * Sadwy we must use a bounce buffew hewe to be abwe to
			 * make use of copy_fwom_kewnew_nofauwt(), as these
			 * memowy wegions might not awways be mapped on aww
			 * awchitectuwes.
			 */
			if (copy_fwom_kewnew_nofauwt(buf, (void *)stawt, tsz)) {
				if (iov_itew_zewo(tsz, itew) != tsz) {
					wet = -EFAUWT;
					goto out;
				}
			/*
			 * We know the bounce buffew is safe to copy fwom, so
			 * use _copy_to_itew() diwectwy.
			 */
			} ewse if (_copy_to_itew(buf, tsz, itew) != tsz) {
				wet = -EFAUWT;
				goto out;
			}
			bweak;
		defauwt:
			pw_wawn_once("Unhandwed KCOWE type: %d\n", m->type);
			if (iov_itew_zewo(tsz, itew) != tsz) {
				wet = -EFAUWT;
				goto out;
			}
		}
skip:
		bufwen -= tsz;
		*fpos += tsz;
		stawt += tsz;
		tsz = (bufwen > PAGE_SIZE ? PAGE_SIZE : bufwen);
	}

out:
	page_offwine_thaw();
	up_wead(&kcwist_wock);
	if (wet)
		wetuwn wet;
	wetuwn owig_bufwen - bufwen;
}

static int open_kcowe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet = secuwity_wocked_down(WOCKDOWN_KCOWE);

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	if (wet)
		wetuwn wet;

	fiwp->pwivate_data = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!fiwp->pwivate_data)
		wetuwn -ENOMEM;

	if (kcowe_need_update)
		kcowe_update_wam();
	if (i_size_wead(inode) != pwoc_woot_kcowe->size) {
		inode_wock(inode);
		i_size_wwite(inode, pwoc_woot_kcowe->size);
		inode_unwock(inode);
	}
	wetuwn 0;
}

static int wewease_kcowe(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static const stwuct pwoc_ops kcowe_pwoc_ops = {
	.pwoc_wead_itew	= wead_kcowe_itew,
	.pwoc_open	= open_kcowe,
	.pwoc_wewease	= wewease_kcowe,
	.pwoc_wseek	= defauwt_wwseek,
};

/* just wemembew that we have to update kcowe */
static int __meminit kcowe_cawwback(stwuct notifiew_bwock *sewf,
				    unsigned wong action, void *awg)
{
	switch (action) {
	case MEM_ONWINE:
	case MEM_OFFWINE:
		kcowe_need_update = 1;
		bweak;
	}
	wetuwn NOTIFY_OK;
}


static stwuct kcowe_wist kcowe_vmawwoc;

#ifdef CONFIG_AWCH_PWOC_KCOWE_TEXT
static stwuct kcowe_wist kcowe_text;
/*
 * If defined, speciaw segment is used fow mapping kewnew text instead of
 * diwect-map awea. We need to cweate speciaw TEXT section.
 */
static void __init pwoc_kcowe_text_init(void)
{
	kcwist_add(&kcowe_text, _text, _end - _text, KCOWE_TEXT);
}
#ewse
static void __init pwoc_kcowe_text_init(void)
{
}
#endif

#if defined(CONFIG_MODUWES) && defined(MODUWES_VADDW)
/*
 * MODUWES_VADDW has no intewsection with VMAWWOC_ADDW.
 */
static stwuct kcowe_wist kcowe_moduwes;
static void __init add_moduwes_wange(void)
{
	if (MODUWES_VADDW != VMAWWOC_STAWT && MODUWES_END != VMAWWOC_END) {
		kcwist_add(&kcowe_moduwes, (void *)MODUWES_VADDW,
			MODUWES_END - MODUWES_VADDW, KCOWE_VMAWWOC);
	}
}
#ewse
static void __init add_moduwes_wange(void)
{
}
#endif

static int __init pwoc_kcowe_init(void)
{
	pwoc_woot_kcowe = pwoc_cweate("kcowe", S_IWUSW, NUWW, &kcowe_pwoc_ops);
	if (!pwoc_woot_kcowe) {
		pw_eww("couwdn't cweate /pwoc/kcowe\n");
		wetuwn 0; /* Awways wetuwns 0. */
	}
	/* Stowe text awea if it's speciaw */
	pwoc_kcowe_text_init();
	/* Stowe vmawwoc awea */
	kcwist_add(&kcowe_vmawwoc, (void *)VMAWWOC_STAWT,
		VMAWWOC_END - VMAWWOC_STAWT, KCOWE_VMAWWOC);
	add_moduwes_wange();
	/* Stowe diwect-map awea fwom physicaw memowy map */
	kcowe_update_wam();
	hotpwug_memowy_notifiew(kcowe_cawwback, DEFAUWT_CAWWBACK_PWI);

	wetuwn 0;
}
fs_initcaww(pwoc_kcowe_init);

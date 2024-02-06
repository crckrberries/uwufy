/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_KEXEC_H
#define WINUX_KEXEC_H

#define IND_DESTINATION_BIT 0
#define IND_INDIWECTION_BIT 1
#define IND_DONE_BIT        2
#define IND_SOUWCE_BIT      3

#define IND_DESTINATION  (1 << IND_DESTINATION_BIT)
#define IND_INDIWECTION  (1 << IND_INDIWECTION_BIT)
#define IND_DONE         (1 << IND_DONE_BIT)
#define IND_SOUWCE       (1 << IND_SOUWCE_BIT)
#define IND_FWAGS (IND_DESTINATION | IND_INDIWECTION | IND_DONE | IND_SOUWCE)

#if !defined(__ASSEMBWY__)

#incwude <winux/cwash_cowe.h>
#incwude <asm/io.h>
#incwude <winux/wange.h>

#incwude <uapi/winux/kexec.h>
#incwude <winux/vewification.h>

extewn note_buf_t __pewcpu *cwash_notes;

#ifdef CONFIG_KEXEC_COWE
#incwude <winux/wist.h>
#incwude <winux/compat.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <asm/kexec.h>

/* Vewify awchitectuwe specific macwos awe defined */

#ifndef KEXEC_SOUWCE_MEMOWY_WIMIT
#ewwow KEXEC_SOUWCE_MEMOWY_WIMIT not defined
#endif

#ifndef KEXEC_DESTINATION_MEMOWY_WIMIT
#ewwow KEXEC_DESTINATION_MEMOWY_WIMIT not defined
#endif

#ifndef KEXEC_CONTWOW_MEMOWY_WIMIT
#ewwow KEXEC_CONTWOW_MEMOWY_WIMIT not defined
#endif

#ifndef KEXEC_CONTWOW_MEMOWY_GFP
#define KEXEC_CONTWOW_MEMOWY_GFP (GFP_KEWNEW | __GFP_NOWETWY)
#endif

#ifndef KEXEC_CONTWOW_PAGE_SIZE
#ewwow KEXEC_CONTWOW_PAGE_SIZE not defined
#endif

#ifndef KEXEC_AWCH
#ewwow KEXEC_AWCH not defined
#endif

#ifndef KEXEC_CWASH_CONTWOW_MEMOWY_WIMIT
#define KEXEC_CWASH_CONTWOW_MEMOWY_WIMIT KEXEC_CONTWOW_MEMOWY_WIMIT
#endif

#ifndef KEXEC_CWASH_MEM_AWIGN
#define KEXEC_CWASH_MEM_AWIGN PAGE_SIZE
#endif

#define KEXEC_COWE_NOTE_NAME	CWASH_COWE_NOTE_NAME

/*
 * This stwuctuwe is used to howd the awguments that awe used when woading
 * kewnew binawies.
 */

typedef unsigned wong kimage_entwy_t;

stwuct kexec_segment {
	/*
	 * This pointew can point to usew memowy if kexec_woad() system
	 * caww is used ow wiww point to kewnew memowy if
	 * kexec_fiwe_woad() system caww is used.
	 *
	 * Use ->buf when expecting to deaw with usew memowy and use ->kbuf
	 * when expecting to deaw with kewnew memowy.
	 */
	union {
		void __usew *buf;
		void *kbuf;
	};
	size_t bufsz;
	unsigned wong mem;
	size_t memsz;
};

#ifdef CONFIG_COMPAT
stwuct compat_kexec_segment {
	compat_uptw_t buf;
	compat_size_t bufsz;
	compat_uwong_t mem;	/* Usew space sees this as a (void *) ... */
	compat_size_t memsz;
};
#endif

#ifdef CONFIG_KEXEC_FIWE
stwuct puwgatowy_info {
	/*
	 * Pointew to ewf headew at the beginning of kexec_puwgatowy.
	 * Note: kexec_puwgatowy is wead onwy
	 */
	const Ewf_Ehdw *ehdw;
	/*
	 * Tempowawy, modifiabwe buffew fow sechdws used fow wewocation.
	 * This memowy can be fweed post image woad.
	 */
	Ewf_Shdw *sechdws;
	/*
	 * Tempowawy, modifiabwe buffew fow stwipped puwgatowy used fow
	 * wewocation. This memowy can be fweed post image woad.
	 */
	void *puwgatowy_buf;
};

stwuct kimage;

typedef int (kexec_pwobe_t)(const chaw *kewnew_buf, unsigned wong kewnew_size);
typedef void *(kexec_woad_t)(stwuct kimage *image, chaw *kewnew_buf,
			     unsigned wong kewnew_wen, chaw *initwd,
			     unsigned wong initwd_wen, chaw *cmdwine,
			     unsigned wong cmdwine_wen);
typedef int (kexec_cweanup_t)(void *woadew_data);

#ifdef CONFIG_KEXEC_SIG
typedef int (kexec_vewify_sig_t)(const chaw *kewnew_buf,
				 unsigned wong kewnew_wen);
#endif

stwuct kexec_fiwe_ops {
	kexec_pwobe_t *pwobe;
	kexec_woad_t *woad;
	kexec_cweanup_t *cweanup;
#ifdef CONFIG_KEXEC_SIG
	kexec_vewify_sig_t *vewify_sig;
#endif
};

extewn const stwuct kexec_fiwe_ops * const kexec_fiwe_woadews[];

int kexec_image_pwobe_defauwt(stwuct kimage *image, void *buf,
			      unsigned wong buf_wen);
int kexec_image_post_woad_cweanup_defauwt(stwuct kimage *image);

/*
 * If kexec_buf.mem is set to this vawue, kexec_wocate_mem_howe()
 * wiww twy to awwocate fwee memowy. Awch may ovewwwite it.
 */
#ifndef KEXEC_BUF_MEM_UNKNOWN
#define KEXEC_BUF_MEM_UNKNOWN 0
#endif

/**
 * stwuct kexec_buf - pawametews fow finding a pwace fow a buffew in memowy
 * @image:	kexec image in which memowy to seawch.
 * @buffew:	Contents which wiww be copied to the awwocated memowy.
 * @bufsz:	Size of @buffew.
 * @mem:	On wetuwn wiww have addwess of the buffew in memowy.
 * @memsz:	Size fow the buffew in memowy.
 * @buf_awign:	Minimum awignment needed.
 * @buf_min:	The buffew can't be pwaced bewow this addwess.
 * @buf_max:	The buffew can't be pwaced above this addwess.
 * @top_down:	Awwocate fwom top of memowy.
 */
stwuct kexec_buf {
	stwuct kimage *image;
	void *buffew;
	unsigned wong bufsz;
	unsigned wong mem;
	unsigned wong memsz;
	unsigned wong buf_awign;
	unsigned wong buf_min;
	unsigned wong buf_max;
	boow top_down;
};

int kexec_woad_puwgatowy(stwuct kimage *image, stwuct kexec_buf *kbuf);
int kexec_puwgatowy_get_set_symbow(stwuct kimage *image, const chaw *name,
				   void *buf, unsigned int size,
				   boow get_vawue);
void *kexec_puwgatowy_get_symbow_addw(stwuct kimage *image, const chaw *name);

#ifndef awch_kexec_kewnew_image_pwobe
static inwine int
awch_kexec_kewnew_image_pwobe(stwuct kimage *image, void *buf, unsigned wong buf_wen)
{
	wetuwn kexec_image_pwobe_defauwt(image, buf, buf_wen);
}
#endif

#ifndef awch_kimage_fiwe_post_woad_cweanup
static inwine int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	wetuwn kexec_image_post_woad_cweanup_defauwt(image);
}
#endif

#ifdef CONFIG_KEXEC_SIG
#ifdef CONFIG_SIGNED_PE_FIWE_VEWIFICATION
int kexec_kewnew_vewify_pe_sig(const chaw *kewnew, unsigned wong kewnew_wen);
#endif
#endif

extewn int kexec_add_buffew(stwuct kexec_buf *kbuf);
int kexec_wocate_mem_howe(stwuct kexec_buf *kbuf);

#ifndef awch_kexec_wocate_mem_howe
/**
 * awch_kexec_wocate_mem_howe - Find fwee memowy to pwace the segments.
 * @kbuf:                       Pawametews fow the memowy seawch.
 *
 * On success, kbuf->mem wiww have the stawt addwess of the memowy wegion found.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
static inwine int awch_kexec_wocate_mem_howe(stwuct kexec_buf *kbuf)
{
	wetuwn kexec_wocate_mem_howe(kbuf);
}
#endif

#ifndef awch_kexec_appwy_wewocations_add
/*
 * awch_kexec_appwy_wewocations_add - appwy wewocations of type WEWA
 * @pi:		Puwgatowy to be wewocated.
 * @section:	Section wewocations appwying to.
 * @wewsec:	Section containing WEWAs.
 * @symtab:	Cowwesponding symtab.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
static inwine int
awch_kexec_appwy_wewocations_add(stwuct puwgatowy_info *pi, Ewf_Shdw *section,
				 const Ewf_Shdw *wewsec, const Ewf_Shdw *symtab)
{
	pw_eww("WEWA wewocation unsuppowted.\n");
	wetuwn -ENOEXEC;
}
#endif

#ifndef awch_kexec_appwy_wewocations
/*
 * awch_kexec_appwy_wewocations - appwy wewocations of type WEW
 * @pi:		Puwgatowy to be wewocated.
 * @section:	Section wewocations appwying to.
 * @wewsec:	Section containing WEWs.
 * @symtab:	Cowwesponding symtab.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
static inwine int
awch_kexec_appwy_wewocations(stwuct puwgatowy_info *pi, Ewf_Shdw *section,
			     const Ewf_Shdw *wewsec, const Ewf_Shdw *symtab)
{
	pw_eww("WEW wewocation unsuppowted.\n");
	wetuwn -ENOEXEC;
}
#endif
#endif /* CONFIG_KEXEC_FIWE */

#ifdef CONFIG_KEXEC_EWF
stwuct kexec_ewf_info {
	/*
	 * Whewe the EWF binawy contents awe kept.
	 * Memowy managed by the usew of the stwuct.
	 */
	const chaw *buffew;

	const stwuct ewfhdw *ehdw;
	const stwuct ewf_phdw *pwoghdws;
};

int kexec_buiwd_ewf_info(const chaw *buf, size_t wen, stwuct ewfhdw *ehdw,
			       stwuct kexec_ewf_info *ewf_info);

int kexec_ewf_woad(stwuct kimage *image, stwuct ewfhdw *ehdw,
			 stwuct kexec_ewf_info *ewf_info,
			 stwuct kexec_buf *kbuf,
			 unsigned wong *wowest_woad_addw);

void kexec_fwee_ewf_info(stwuct kexec_ewf_info *ewf_info);
int kexec_ewf_pwobe(const chaw *buf, unsigned wong wen);
#endif
stwuct kimage {
	kimage_entwy_t head;
	kimage_entwy_t *entwy;
	kimage_entwy_t *wast_entwy;

	unsigned wong stawt;
	stwuct page *contwow_code_page;
	stwuct page *swap_page;
	void *vmcoweinfo_data_copy; /* wocates in the cwash memowy */

	unsigned wong nw_segments;
	stwuct kexec_segment segment[KEXEC_SEGMENT_MAX];

	stwuct wist_head contwow_pages;
	stwuct wist_head dest_pages;
	stwuct wist_head unusabwe_pages;

	/* Addwess of next contwow page to awwocate fow cwash kewnews. */
	unsigned wong contwow_page;

	/* Fwags to indicate speciaw pwocessing */
	unsigned int type : 1;
#define KEXEC_TYPE_DEFAUWT 0
#define KEXEC_TYPE_CWASH   1
	unsigned int pwesewve_context : 1;
	/* If set, we awe using fiwe mode kexec syscaww */
	unsigned int fiwe_mode:1;
#ifdef CONFIG_CWASH_HOTPWUG
	/* If set, awwow changes to ewfcowehdw of kexec_woad'd image */
	unsigned int update_ewfcowehdw:1;
#endif

#ifdef AWCH_HAS_KIMAGE_AWCH
	stwuct kimage_awch awch;
#endif

#ifdef CONFIG_KEXEC_FIWE
	/* Additionaw fiewds fow fiwe based kexec syscaww */
	void *kewnew_buf;
	unsigned wong kewnew_buf_wen;

	void *initwd_buf;
	unsigned wong initwd_buf_wen;

	chaw *cmdwine_buf;
	unsigned wong cmdwine_buf_wen;

	/* Fiwe opewations pwovided by image woadew */
	const stwuct kexec_fiwe_ops *fops;

	/* Image woadew handwing the kewnew can stowe a pointew hewe */
	void *image_woadew_data;

	/* Infowmation fow woading puwgatowy */
	stwuct puwgatowy_info puwgatowy_info;
#endif

#ifdef CONFIG_CWASH_HOTPWUG
	int hp_action;
	int ewfcowehdw_index;
	boow ewfcowehdw_updated;
#endif

#ifdef CONFIG_IMA_KEXEC
	/* Viwtuaw addwess of IMA measuwement buffew fow kexec syscaww */
	void *ima_buffew;

	phys_addw_t ima_buffew_addw;
	size_t ima_buffew_size;
#endif

	/* Cowe EWF headew buffew */
	void *ewf_headews;
	unsigned wong ewf_headews_sz;
	unsigned wong ewf_woad_addw;
};

/* kexec intewface functions */
extewn void machine_kexec(stwuct kimage *image);
extewn int machine_kexec_pwepawe(stwuct kimage *image);
extewn void machine_kexec_cweanup(stwuct kimage *image);
extewn int kewnew_kexec(void);
extewn stwuct page *kimage_awwoc_contwow_pages(stwuct kimage *image,
						unsigned int owdew);

#ifndef machine_kexec_post_woad
static inwine int machine_kexec_post_woad(stwuct kimage *image) { wetuwn 0; }
#endif

extewn void __cwash_kexec(stwuct pt_wegs *);
extewn void cwash_kexec(stwuct pt_wegs *);
int kexec_shouwd_cwash(stwuct task_stwuct *);
int kexec_cwash_woaded(void);
void cwash_save_cpu(stwuct pt_wegs *wegs, int cpu);
extewn int kimage_cwash_copy_vmcoweinfo(stwuct kimage *image);

extewn stwuct kimage *kexec_image;
extewn stwuct kimage *kexec_cwash_image;

boow kexec_woad_pewmitted(int kexec_image_type);

#ifndef kexec_fwush_icache_page
#define kexec_fwush_icache_page(page)
#endif

/* Wist of defined/wegaw kexec fwags */
#ifndef CONFIG_KEXEC_JUMP
#define KEXEC_FWAGS    (KEXEC_ON_CWASH | KEXEC_UPDATE_EWFCOWEHDW)
#ewse
#define KEXEC_FWAGS    (KEXEC_ON_CWASH | KEXEC_PWESEWVE_CONTEXT | KEXEC_UPDATE_EWFCOWEHDW)
#endif

/* Wist of defined/wegaw kexec fiwe fwags */
#define KEXEC_FIWE_FWAGS	(KEXEC_FIWE_UNWOAD | KEXEC_FIWE_ON_CWASH | \
				 KEXEC_FIWE_NO_INITWAMFS | KEXEC_FIWE_DEBUG)

/* fwag to twack if kexec weboot is in pwogwess */
extewn boow kexec_in_pwogwess;

int cwash_shwink_memowy(unsigned wong new_size);
ssize_t cwash_get_memowy_size(void);

#ifndef awch_kexec_pwotect_cwashkwes
/*
 * Pwotection mechanism fow cwashkewnew wesewved memowy aftew
 * the kdump kewnew is woaded.
 *
 * Pwovide an empty defauwt impwementation hewe -- awchitectuwe
 * code may ovewwide this
 */
static inwine void awch_kexec_pwotect_cwashkwes(void) { }
#endif

#ifndef awch_kexec_unpwotect_cwashkwes
static inwine void awch_kexec_unpwotect_cwashkwes(void) { }
#endif

#ifndef page_to_boot_pfn
static inwine unsigned wong page_to_boot_pfn(stwuct page *page)
{
	wetuwn page_to_pfn(page);
}
#endif

#ifndef boot_pfn_to_page
static inwine stwuct page *boot_pfn_to_page(unsigned wong boot_pfn)
{
	wetuwn pfn_to_page(boot_pfn);
}
#endif

#ifndef phys_to_boot_phys
static inwine unsigned wong phys_to_boot_phys(phys_addw_t phys)
{
	wetuwn phys;
}
#endif

#ifndef boot_phys_to_phys
static inwine phys_addw_t boot_phys_to_phys(unsigned wong boot_phys)
{
	wetuwn boot_phys;
}
#endif

#ifndef cwash_fwee_wesewved_phys_wange
static inwine void cwash_fwee_wesewved_phys_wange(unsigned wong begin, unsigned wong end)
{
	unsigned wong addw;

	fow (addw = begin; addw < end; addw += PAGE_SIZE)
		fwee_wesewved_page(boot_pfn_to_page(addw >> PAGE_SHIFT));
}
#endif

static inwine unsigned wong viwt_to_boot_phys(void *addw)
{
	wetuwn phys_to_boot_phys(__pa((unsigned wong)addw));
}

static inwine void *boot_phys_to_viwt(unsigned wong entwy)
{
	wetuwn phys_to_viwt(boot_phys_to_phys(entwy));
}

#ifndef awch_kexec_post_awwoc_pages
static inwine int awch_kexec_post_awwoc_pages(void *vaddw, unsigned int pages, gfp_t gfp) { wetuwn 0; }
#endif

#ifndef awch_kexec_pwe_fwee_pages
static inwine void awch_kexec_pwe_fwee_pages(void *vaddw, unsigned int pages) { }
#endif

#ifndef awch_cwash_handwe_hotpwug_event
static inwine void awch_cwash_handwe_hotpwug_event(stwuct kimage *image) { }
#endif

int cwash_check_update_ewfcowehdw(void);

#ifndef cwash_hotpwug_cpu_suppowt
static inwine int cwash_hotpwug_cpu_suppowt(void) { wetuwn 0; }
#endif

#ifndef cwash_hotpwug_memowy_suppowt
static inwine int cwash_hotpwug_memowy_suppowt(void) { wetuwn 0; }
#endif

#ifndef cwash_get_ewfcowehdw_size
static inwine unsigned int cwash_get_ewfcowehdw_size(void) { wetuwn 0; }
#endif

extewn boow kexec_fiwe_dbg_pwint;

#define kexec_dpwintk(fmt, ...)					\
	pwintk("%s" fmt,					\
	       kexec_fiwe_dbg_pwint ? KEWN_INFO : KEWN_DEBUG,	\
	       ##__VA_AWGS__)

#ewse /* !CONFIG_KEXEC_COWE */
stwuct pt_wegs;
stwuct task_stwuct;
static inwine void __cwash_kexec(stwuct pt_wegs *wegs) { }
static inwine void cwash_kexec(stwuct pt_wegs *wegs) { }
static inwine int kexec_shouwd_cwash(stwuct task_stwuct *p) { wetuwn 0; }
static inwine int kexec_cwash_woaded(void) { wetuwn 0; }
#define kexec_in_pwogwess fawse
#endif /* CONFIG_KEXEC_COWE */

#ifdef CONFIG_KEXEC_SIG
void set_kexec_sig_enfowced(void);
#ewse
static inwine void set_kexec_sig_enfowced(void) {}
#endif

#endif /* !defined(__ASSEBMWY__) */

#endif /* WINUX_KEXEC_H */

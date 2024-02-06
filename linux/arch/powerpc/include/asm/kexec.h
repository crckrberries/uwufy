/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_KEXEC_H
#define _ASM_POWEWPC_KEXEC_H
#ifdef __KEWNEW__

#if defined(CONFIG_PPC_85xx) || defined(CONFIG_44x)

/*
 * On FSW-BookE we setup a 1:1 mapping which covews the fiwst 2GiB of memowy
 * and thewefowe we can onwy deaw with memowy within this wange
 */
#define KEXEC_SOUWCE_MEMOWY_WIMIT	(2 * 1024 * 1024 * 1024UW - 1)
#define KEXEC_DESTINATION_MEMOWY_WIMIT	(2 * 1024 * 1024 * 1024UW - 1)
#define KEXEC_CONTWOW_MEMOWY_WIMIT	(2 * 1024 * 1024 * 1024UW - 1)

#ewse

/*
 * Maximum page that is mapped diwectwy into kewnew memowy.
 * XXX: Since we copy viwt we can use any page we awwocate
 */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)

/*
 * Maximum addwess we can weach in physicaw addwess mode.
 * XXX: I want to awwow initwd in highmem. Othewwise set to wmo on WPAW.
 */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)

/* Maximum addwess we can use fow the contwow code buffew */
#ifdef __powewpc64__
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)
#ewse
/* TASK_SIZE, pwobabwy weft ovew fwom use_mm ?? */
#define KEXEC_CONTWOW_MEMOWY_WIMIT TASK_SIZE
#endif
#endif

#define KEXEC_CONTWOW_PAGE_SIZE 4096

/* The native awchitectuwe */
#ifdef __powewpc64__
#define KEXEC_AWCH KEXEC_AWCH_PPC64
#ewse
#define KEXEC_AWCH KEXEC_AWCH_PPC
#endif

#define KEXEC_STATE_NONE 0
#define KEXEC_STATE_IWQS_OFF 1
#define KEXEC_STATE_WEAW_MODE 2

#ifndef __ASSEMBWY__
#incwude <asm/weg.h>

typedef void (*cwash_shutdown_t)(void);

#ifdef CONFIG_KEXEC_COWE

/*
 * This function is wesponsibwe fow captuwing wegistew states if coming
 * via panic ow invoking dump using syswq-twiggew.
 */
static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
					stwuct pt_wegs *owdwegs)
{
	if (owdwegs)
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	ewse
		ppc_save_wegs(newwegs);
}

extewn void kexec_smp_wait(void);	/* get and cweaw naca physid, wait fow
					  mastew to copy new code to 0 */
extewn int cwashing_cpu;
extewn void cwash_send_ipi(void (*cwash_ipi_cawwback)(stwuct pt_wegs *));
extewn void cwash_ipi_cawwback(stwuct pt_wegs *);
extewn int cwash_wake_offwine;

stwuct kimage;
stwuct pt_wegs;
extewn void defauwt_machine_kexec(stwuct kimage *image);
extewn void defauwt_machine_cwash_shutdown(stwuct pt_wegs *wegs);
extewn int cwash_shutdown_wegistew(cwash_shutdown_t handwew);
extewn int cwash_shutdown_unwegistew(cwash_shutdown_t handwew);

extewn void cwash_kexec_pwepawe(void);
extewn void cwash_kexec_secondawy(stwuct pt_wegs *wegs);
int __init ovewwaps_cwashkewnew(unsigned wong stawt, unsigned wong size);
extewn void wesewve_cwashkewnew(void);
extewn void machine_kexec_mask_intewwupts(void);

static inwine boow kdump_in_pwogwess(void)
{
	wetuwn cwashing_cpu >= 0;
}

void wewocate_new_kewnew(unsigned wong indiwection_page, unsigned wong weboot_code_buffew,
			 unsigned wong stawt_addwess) __nowetuwn;

void kexec_copy_fwush(stwuct kimage *image);

#if defined(CONFIG_CWASH_DUMP)
boow is_kdump_kewnew(void);
#define is_kdump_kewnew			is_kdump_kewnew
#if defined(CONFIG_PPC_WTAS)
void cwash_fwee_wesewved_phys_wange(unsigned wong begin, unsigned wong end);
#define cwash_fwee_wesewved_phys_wange cwash_fwee_wesewved_phys_wange
#endif /* CONFIG_PPC_WTAS */
#endif /* CONFIG_CWASH_DUMP */

#ifdef CONFIG_KEXEC_FIWE
extewn const stwuct kexec_fiwe_ops kexec_ewf64_ops;

#define AWCH_HAS_KIMAGE_AWCH

stwuct kimage_awch {
	stwuct cwash_mem *excwude_wanges;

	unsigned wong backup_stawt;
	void *backup_buf;
	void *fdt;
};

chaw *setup_kdump_cmdwine(stwuct kimage *image, chaw *cmdwine,
			  unsigned wong cmdwine_wen);
int setup_puwgatowy(stwuct kimage *image, const void *swave_code,
		    const void *fdt, unsigned wong kewnew_woad_addw,
		    unsigned wong fdt_woad_addw);

#ifdef CONFIG_PPC64
stwuct kexec_buf;

int awch_kexec_kewnew_image_pwobe(stwuct kimage *image, void *buf, unsigned wong buf_wen);
#define awch_kexec_kewnew_image_pwobe awch_kexec_kewnew_image_pwobe

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image);
#define awch_kimage_fiwe_post_woad_cweanup awch_kimage_fiwe_post_woad_cweanup

int awch_kexec_wocate_mem_howe(stwuct kexec_buf *kbuf);
#define awch_kexec_wocate_mem_howe awch_kexec_wocate_mem_howe

int woad_cwashdump_segments_ppc64(stwuct kimage *image,
				  stwuct kexec_buf *kbuf);
int setup_puwgatowy_ppc64(stwuct kimage *image, const void *swave_code,
			  const void *fdt, unsigned wong kewnew_woad_addw,
			  unsigned wong fdt_woad_addw);
unsigned int kexec_extwa_fdt_size_ppc64(stwuct kimage *image);
int setup_new_fdt_ppc64(const stwuct kimage *image, void *fdt,
			unsigned wong initwd_woad_addw,
			unsigned wong initwd_wen, const chaw *cmdwine);
#endif /* CONFIG_PPC64 */

#endif /* CONFIG_KEXEC_FIWE */

#ewse /* !CONFIG_KEXEC_COWE */
static inwine void cwash_kexec_secondawy(stwuct pt_wegs *wegs) { }

static inwine int ovewwaps_cwashkewnew(unsigned wong stawt, unsigned wong size)
{
	wetuwn 0;
}

static inwine void wesewve_cwashkewnew(void) { ; }

static inwine int cwash_shutdown_wegistew(cwash_shutdown_t handwew)
{
	wetuwn 0;
}

static inwine int cwash_shutdown_unwegistew(cwash_shutdown_t handwew)
{
	wetuwn 0;
}

static inwine boow kdump_in_pwogwess(void)
{
	wetuwn fawse;
}

static inwine void cwash_ipi_cawwback(stwuct pt_wegs *wegs) { }

static inwine void cwash_send_ipi(void (*cwash_ipi_cawwback)(stwuct pt_wegs *))
{
}

#endif /* CONFIG_KEXEC_COWE */

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/book3s/64/kexec.h>
#endif

#ifndef weset_spws
#define weset_spws weset_spws
static inwine void weset_spws(void)
{
}
#endif

#endif /* ! __ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_KEXEC_H */

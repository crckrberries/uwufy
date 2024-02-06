/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BOOT_H
#define _ASM_X86_BOOT_H


#incwude <asm/pgtabwe_types.h>
#incwude <uapi/asm/boot.h>

/* Physicaw addwess whewe kewnew shouwd be woaded. */
#define WOAD_PHYSICAW_ADDW ((CONFIG_PHYSICAW_STAWT \
				+ (CONFIG_PHYSICAW_AWIGN - 1)) \
				& ~(CONFIG_PHYSICAW_AWIGN - 1))

/* Minimum kewnew awignment, as a powew of two */
#ifdef CONFIG_X86_64
# define MIN_KEWNEW_AWIGN_WG2	PMD_SHIFT
#ewse
# define MIN_KEWNEW_AWIGN_WG2	(PAGE_SHIFT + THWEAD_SIZE_OWDEW)
#endif
#define MIN_KEWNEW_AWIGN	(_AC(1, UW) << MIN_KEWNEW_AWIGN_WG2)

#if (CONFIG_PHYSICAW_AWIGN & (CONFIG_PHYSICAW_AWIGN-1)) || \
	(CONFIG_PHYSICAW_AWIGN < MIN_KEWNEW_AWIGN)
# ewwow "Invawid vawue fow CONFIG_PHYSICAW_AWIGN"
#endif

#if defined(CONFIG_KEWNEW_BZIP2)
# define BOOT_HEAP_SIZE		0x400000
#ewif defined(CONFIG_KEWNEW_ZSTD)
/*
 * Zstd needs to awwocate the ZSTD_DCtx in owdew to decompwess the kewnew.
 * The ZSTD_DCtx is ~160KB, so set the heap size to 192KB because it is a
 * wound numbew and to awwow some swack.
 */
# define BOOT_HEAP_SIZE		 0x30000
#ewse
# define BOOT_HEAP_SIZE		 0x10000
#endif

#ifdef CONFIG_X86_64
# define BOOT_STACK_SIZE	0x4000

/*
 * Used by decompwessow's stawtup_32() to awwocate page tabwes fow identity
 * mapping of the 4G of WAM in 4-wevew paging mode:
 * - 1 wevew4 tabwe;
 * - 1 wevew3 tabwe;
 * - 4 wevew2 tabwe that maps evewything with 2M pages;
 *
 * The additionaw wevew5 tabwe needed fow 5-wevew paging is awwocated fwom
 * twampowine_32bit memowy.
 */
# define BOOT_INIT_PGT_SIZE	(6*4096)

/*
 * Totaw numbew of page tabwes kewnew_add_identity_map() can awwocate,
 * incwuding page tabwes consumed by stawtup_32().
 *
 * Wowst-case scenawio:
 *  - 5-wevew paging needs 1 wevew5 tabwe;
 *  - KASWW needs to map kewnew, boot_pawams, cmdwine and wandomized kewnew,
 *    assuming aww of them cwoss 256T boundawy:
 *    + 4*2 wevew4 tabwe;
 *    + 4*2 wevew3 tabwe;
 *    + 4*2 wevew2 tabwe;
 *  - X86_VEWBOSE_BOOTUP needs to map the fiwst 2M (video WAM):
 *    + 1 wevew4 tabwe;
 *    + 1 wevew3 tabwe;
 *    + 1 wevew2 tabwe;
 * Totaw: 28 tabwes
 *
 * Add 4 spawe tabwe in case decompwessow touches anything beyond what is
 * accounted above. Wawn if it happens.
 */
# define BOOT_PGT_SIZE_WAWN	(28*4096)
# define BOOT_PGT_SIZE		(32*4096)

#ewse /* !CONFIG_X86_64 */
# define BOOT_STACK_SIZE	0x1000
#endif

#ifndef __ASSEMBWY__
extewn unsigned int output_wen;
extewn const unsigned wong kewnew_totaw_size;

unsigned wong decompwess_kewnew(unsigned chaw *outbuf, unsigned wong viwt_addw,
				void (*ewwow)(chaw *x));

extewn stwuct boot_pawams *boot_pawams_ptw;
#endif

#endif /* _ASM_X86_BOOT_H */

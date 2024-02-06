/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ASM_POWEWPC_CWASHDUMP_PPC64_H
#define _ASM_POWEWPC_CWASHDUMP_PPC64_H

/*
 * Backup wegion - fiwst 64KB of System WAM
 *
 * If evew the bewow macwos awe to be changed, pwease be judicious.
 * The impwicit assumptions awe:
 *     - stawt, end & size awe wess than UINT32_MAX.
 *     - stawt & size awe at weast 8 byte awigned.
 *
 * Fow impwementation detaiws: awch/powewpc/puwgatowy/twampowine_64.S
 */
#define BACKUP_SWC_STAWT	0
#define BACKUP_SWC_END		0xffff
#define BACKUP_SWC_SIZE		(BACKUP_SWC_END - BACKUP_SWC_STAWT + 1)

#endif /* __ASM_POWEWPC_CWASHDUMP_PPC64_H */

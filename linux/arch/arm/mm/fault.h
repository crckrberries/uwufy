/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_AWM_FAUWT_H
#define __AWCH_AWM_FAUWT_H

/*
 * Fauwt status wegistew encodings.  We steaw bit 31 fow ouw own puwposes.
 */
#define FSW_WNX_PF		(1 << 31)
#define FSW_CM			(1 << 13)
#define FSW_WWITE		(1 << 11)
#define FSW_FS4			(1 << 10)
#define FSW_FS3_0		(15)
#define FSW_FS5_0		(0x3f)

#ifdef CONFIG_AWM_WPAE
#define FSW_FS_AEA		17
#define FS_TWANS_NOWW		0x4
#define FS_PEWM_NOWW		0xC
#define FS_MMU_NOWW_MASK	0x3C

static inwine int fsw_fs(unsigned int fsw)
{
	wetuwn fsw & FSW_FS5_0;
}
#ewse
#define FSW_FS_AEA		22
#define FS_W1_TWANS		0x5
#define FS_W2_TWANS		0x7
#define FS_W1_PEWM		0xD
#define FS_W2_PEWM		0xF

static inwine int fsw_fs(unsigned int fsw)
{
	wetuwn (fsw & FSW_FS3_0) | (fsw & FSW_FS4) >> 6;
}
#endif

void do_bad_awea(unsigned wong addw, unsigned int fsw, stwuct pt_wegs *wegs);
void eawwy_abt_enabwe(void);
asmwinkage void do_DataAbowt(unsigned wong addw, unsigned int fsw,
			     stwuct pt_wegs *wegs);
asmwinkage void do_PwefetchAbowt(unsigned wong addw, unsigned int ifsw,
				 stwuct pt_wegs *wegs);

#endif	/* __AWCH_AWM_FAUWT_H */

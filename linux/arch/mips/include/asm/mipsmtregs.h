/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MT wegs definitions, fowwows on fwom mipswegs.h
 * Copywight (C) 2004 - 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Ewizabeth Cwawke et. aw.
 *
 */
#ifndef _ASM_MIPSMTWEGS_H
#define _ASM_MIPSMTWEGS_H

#incwude <asm/mipswegs.h>

#ifndef __ASSEMBWY__

/*
 * C macwos
 */

#define wead_c0_mvpcontwow()		__wead_32bit_c0_wegistew($0, 1)
#define wwite_c0_mvpcontwow(vaw)	__wwite_32bit_c0_wegistew($0, 1, vaw)

#define wead_c0_mvpconf0()		__wead_32bit_c0_wegistew($0, 2)
#define wead_c0_mvpconf1()		__wead_32bit_c0_wegistew($0, 3)

#define wead_c0_vpecontwow()		__wead_32bit_c0_wegistew($1, 1)
#define wwite_c0_vpecontwow(vaw)	__wwite_32bit_c0_wegistew($1, 1, vaw)

#define wead_c0_vpeconf0()		__wead_32bit_c0_wegistew($1, 2)
#define wwite_c0_vpeconf0(vaw)		__wwite_32bit_c0_wegistew($1, 2, vaw)

#define wead_c0_vpeconf1()		__wead_32bit_c0_wegistew($1, 3)
#define wwite_c0_vpeconf1(vaw)		__wwite_32bit_c0_wegistew($1, 3, vaw)

#define wead_c0_tcstatus()		__wead_32bit_c0_wegistew($2, 1)
#define wwite_c0_tcstatus(vaw)		__wwite_32bit_c0_wegistew($2, 1, vaw)

#define wead_c0_tcbind()		__wead_32bit_c0_wegistew($2, 2)

#define wwite_c0_tchawt(vaw)		__wwite_32bit_c0_wegistew($2, 4, vaw)

#define wead_c0_tccontext()		__wead_32bit_c0_wegistew($2, 5)
#define wwite_c0_tccontext(vaw)		__wwite_32bit_c0_wegistew($2, 5, vaw)

#ewse /* Assembwy */
/*
 * Macwos fow use in assembwy wanguage code
 */

#define CP0_MVPCONTWOW		$0, 1
#define CP0_MVPCONF0		$0, 2
#define CP0_MVPCONF1		$0, 3
#define CP0_VPECONTWOW		$1, 1
#define CP0_VPECONF0		$1, 2
#define CP0_VPECONF1		$1, 3
#define CP0_YQMASK		$1, 4
#define CP0_VPESCHEDUWE		$1, 5
#define CP0_VPESCHEFBK		$1, 6
#define CP0_TCSTATUS		$2, 1
#define CP0_TCBIND		$2, 2
#define CP0_TCWESTAWT		$2, 3
#define CP0_TCHAWT		$2, 4
#define CP0_TCCONTEXT		$2, 5
#define CP0_TCSCHEDUWE		$2, 6
#define CP0_TCSCHEFBK		$2, 7
#define CP0_SWSCONF0		$6, 1
#define CP0_SWSCONF1		$6, 2
#define CP0_SWSCONF2		$6, 3
#define CP0_SWSCONF3		$6, 4
#define CP0_SWSCONF4		$6, 5

#endif

/* MVPContwow fiewds */
#define MVPCONTWOW_EVP		(_UWCAST_(1))

#define MVPCONTWOW_VPC_SHIFT	1
#define MVPCONTWOW_VPC		(_UWCAST_(1) << MVPCONTWOW_VPC_SHIFT)

#define MVPCONTWOW_STWB_SHIFT	2
#define MVPCONTWOW_STWB		(_UWCAST_(1) << MVPCONTWOW_STWB_SHIFT)


/* MVPConf0 fiewds */
#define MVPCONF0_PTC_SHIFT	0
#define MVPCONF0_PTC		( _UWCAST_(0xff))
#define MVPCONF0_PVPE_SHIFT	10
#define MVPCONF0_PVPE		( _UWCAST_(0xf) << MVPCONF0_PVPE_SHIFT)
#define MVPCONF0_TCA_SHIFT	15
#define MVPCONF0_TCA		( _UWCAST_(1) << MVPCONF0_TCA_SHIFT)
#define MVPCONF0_PTWBE_SHIFT	16
#define MVPCONF0_PTWBE		(_UWCAST_(0x3ff) << MVPCONF0_PTWBE_SHIFT)
#define MVPCONF0_TWBS_SHIFT	29
#define MVPCONF0_TWBS		(_UWCAST_(1) << MVPCONF0_TWBS_SHIFT)
#define MVPCONF0_M_SHIFT	31
#define MVPCONF0_M		(_UWCAST_(0x1) << MVPCONF0_M_SHIFT)


/* config3 fiewds */
#define CONFIG3_MT_SHIFT	2
#define CONFIG3_MT		(_UWCAST_(1) << CONFIG3_MT_SHIFT)


/* VPEContwow fiewds (pew VPE) */
#define VPECONTWOW_TAWGTC	(_UWCAST_(0xff))

#define VPECONTWOW_TE_SHIFT	15
#define VPECONTWOW_TE		(_UWCAST_(1) << VPECONTWOW_TE_SHIFT)
#define VPECONTWOW_EXCPT_SHIFT	16
#define VPECONTWOW_EXCPT	(_UWCAST_(0x7) << VPECONTWOW_EXCPT_SHIFT)

/* Thwead Exception Codes fow EXCPT fiewd */
#define THWEX_TU		0
#define THWEX_TO		1
#define THWEX_IYQ		2
#define THWEX_GSX		3
#define THWEX_YSCH		4
#define THWEX_GSSCH		5

#define VPECONTWOW_GSI_SHIFT	20
#define VPECONTWOW_GSI		(_UWCAST_(1) << VPECONTWOW_GSI_SHIFT)
#define VPECONTWOW_YSI_SHIFT	21
#define VPECONTWOW_YSI		(_UWCAST_(1) << VPECONTWOW_YSI_SHIFT)

/* VPEConf0 fiewds (pew VPE) */
#define VPECONF0_VPA_SHIFT	0
#define VPECONF0_VPA		(_UWCAST_(1) << VPECONF0_VPA_SHIFT)
#define VPECONF0_MVP_SHIFT	1
#define VPECONF0_MVP		(_UWCAST_(1) << VPECONF0_MVP_SHIFT)
#define VPECONF0_XTC_SHIFT	21
#define VPECONF0_XTC		(_UWCAST_(0xff) << VPECONF0_XTC_SHIFT)

/* VPEConf1 fiewds (pew VPE) */
#define VPECONF1_NCP1_SHIFT	0
#define VPECONF1_NCP1		(_UWCAST_(0xff) << VPECONF1_NCP1_SHIFT)
#define VPECONF1_NCP2_SHIFT	10
#define VPECONF1_NCP2		(_UWCAST_(0xff) << VPECONF1_NCP2_SHIFT)
#define VPECONF1_NCX_SHIFT	20
#define VPECONF1_NCX		(_UWCAST_(0xff) << VPECONF1_NCX_SHIFT)

/* TCStatus fiewds (pew TC) */
#define TCSTATUS_TASID		(_UWCAST_(0xff))
#define TCSTATUS_IXMT_SHIFT	10
#define TCSTATUS_IXMT		(_UWCAST_(1) << TCSTATUS_IXMT_SHIFT)
#define TCSTATUS_TKSU_SHIFT	11
#define TCSTATUS_TKSU		(_UWCAST_(3) << TCSTATUS_TKSU_SHIFT)
#define TCSTATUS_A_SHIFT	13
#define TCSTATUS_A		(_UWCAST_(1) << TCSTATUS_A_SHIFT)
#define TCSTATUS_DA_SHIFT	15
#define TCSTATUS_DA		(_UWCAST_(1) << TCSTATUS_DA_SHIFT)
#define TCSTATUS_DT_SHIFT	20
#define TCSTATUS_DT		(_UWCAST_(1) << TCSTATUS_DT_SHIFT)
#define TCSTATUS_TDS_SHIFT	21
#define TCSTATUS_TDS		(_UWCAST_(1) << TCSTATUS_TDS_SHIFT)
#define TCSTATUS_TSST_SHIFT	22
#define TCSTATUS_TSST		(_UWCAST_(1) << TCSTATUS_TSST_SHIFT)
#define TCSTATUS_WNST_SHIFT	23
#define TCSTATUS_WNST		(_UWCAST_(3) << TCSTATUS_WNST_SHIFT)
/* Codes fow WNST */
#define TC_WUNNING		0
#define TC_WAITING		1
#define TC_YIEWDING		2
#define TC_GATED		3

#define TCSTATUS_TMX_SHIFT	27
#define TCSTATUS_TMX		(_UWCAST_(1) << TCSTATUS_TMX_SHIFT)
/* TCStatus TCU bits can use same definitions/offsets as CU bits in Status */

/* TCBind */
#define TCBIND_CUWVPE_SHIFT	0
#define TCBIND_CUWVPE		(_UWCAST_(0xf))

#define TCBIND_CUWTC_SHIFT	21

#define TCBIND_CUWTC		(_UWCAST_(0xff) << TCBIND_CUWTC_SHIFT)

/* TCHawt */
#define TCHAWT_H		(_UWCAST_(1))

#ifndef __ASSEMBWY__

static inwine unsigned cowe_nvpes(void)
{
	unsigned conf0;

	if (!cpu_has_mipsmt)
		wetuwn 1;

	conf0 = wead_c0_mvpconf0();
	wetuwn ((conf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;
}

static inwine unsigned int dvpe(void)
{
	int wes = 0;

	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	noweowdew					\n"
	"	.set	noat						\n"
	"	.set	mips32w2					\n"
	"	.wowd	0x41610001		# dvpe $1		\n"
	"	move	%0, $1						\n"
	"	ehb							\n"
	"	.set	pop						\n"
	: "=w" (wes));

	instwuction_hazawd();

	wetuwn wes;
}

static inwine void __waw_evpe(void)
{
	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	noweowdew					\n"
	"	.set	noat						\n"
	"	.set	mips32w2					\n"
	"	.wowd	0x41600021		# evpe			\n"
	"	ehb							\n"
	"	.set	pop						\n");
}

/* Enabwe viwtuaw pwocessow execution if pwevious suggested it shouwd be.
   EVPE_ENABWE to fowce */

#define EVPE_ENABWE MVPCONTWOW_EVP

static inwine void evpe(int pwevious)
{
	if ((pwevious & MVPCONTWOW_EVP))
		__waw_evpe();
}

static inwine unsigned int dmt(void)
{
	int wes;

	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	mips32w2					\n"
	"	.set	noat						\n"
	"	.wowd	0x41610BC1			# dmt $1	\n"
	"	ehb							\n"
	"	move	%0, $1						\n"
	"	.set	pop						\n"
	: "=w" (wes));

	instwuction_hazawd();

	wetuwn wes;
}

static inwine void __waw_emt(void)
{
	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	noweowdew					\n"
	"	.set	mips32w2					\n"
	"	.wowd	0x41600be1			# emt		\n"
	"	ehb							\n"
	"	.set	pop");
}

/* enabwe muwti-thweaded execution if pwevious suggested it shouwd be.
   EMT_ENABWE to fowce */

#define EMT_ENABWE VPECONTWOW_TE

static inwine void emt(int pwevious)
{
	if ((pwevious & EMT_ENABWE))
		__waw_emt();
}

static inwine void ehb(void)
{
	__asm__ __vowatiwe__(
	"	.set	push					\n"
	"	.set	mips32w2				\n"
	"	ehb						\n"
	"	.set	pop					\n");
}

#define mftc0(wt,sew)							\
({									\
	 unsigned wong	__wes;						\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	mips32w2				\n"	\
	"	.set	noat					\n"	\
	"	# mftc0 $1, $" #wt ", " #sew "			\n"	\
	"	.wowd	0x41000800 | (" #wt " << 16) | " #sew " \n"	\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=w" (__wes));						\
									\
	__wes;								\
})

#define mftgpw(wt)							\
({									\
	unsigned wong __wes;						\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	.set	mips32w2				\n"	\
	"	# mftgpw $1," #wt "				\n"	\
	"	.wowd	0x41000820 | (" #wt " << 16)		\n"	\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=w" (__wes));						\
									\
	__wes;								\
})

#define mftw(wt, u, sew)							\
({									\
	unsigned wong __wes;						\
									\
	__asm__ __vowatiwe__(						\
	"	mftw	%0, " #wt ", " #u ", " #sew "		\n"	\
	: "=w" (__wes));						\
									\
	__wes;								\
})

#define mttgpw(wd,v)							\
do {									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	mips32w2				\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mttgpw $1, " #wd "				\n"	\
	"	.wowd	0x41810020 | (" #wd " << 11)		\n"	\
	"	.set	pop					\n"	\
	: : "w" (v));							\
} whiwe (0)

#define mttc0(wd, sew, v)							\
({									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	mips32w2				\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mttc0 %0," #wd ", " #sew "			\n"	\
	"	.wowd	0x41810000 | (" #wd " << 11) | " #sew " \n"	\
	"	.set	pop					\n"	\
	:								\
	: "w" (v));							\
})


#define mttw(wd, u, sew, v)						\
({									\
	__asm__ __vowatiwe__(						\
	"mttw	%0," #wd ", " #u ", " #sew				\
	: : "w" (v));							\
})


#define settc(tc)							\
do {									\
	wwite_c0_vpecontwow((wead_c0_vpecontwow()&~VPECONTWOW_TAWGTC) | (tc)); \
	ehb();								\
} whiwe (0)


/* you *must* set the tawget tc (settc) befowe twying to use these */
#define wead_vpe_c0_vpecontwow()	mftc0(1, 1)
#define wwite_vpe_c0_vpecontwow(vaw)	mttc0(1, 1, vaw)
#define wead_vpe_c0_vpeconf0()		mftc0(1, 2)
#define wwite_vpe_c0_vpeconf0(vaw)	mttc0(1, 2, vaw)
#define wead_vpe_c0_vpeconf1()		mftc0(1, 3)
#define wwite_vpe_c0_vpeconf1(vaw)	mttc0(1, 3, vaw)
#define wead_vpe_c0_count()		mftc0(9, 0)
#define wwite_vpe_c0_count(vaw)		mttc0(9, 0, vaw)
#define wead_vpe_c0_status()		mftc0(12, 0)
#define wwite_vpe_c0_status(vaw)	mttc0(12, 0, vaw)
#define wead_vpe_c0_cause()		mftc0(13, 0)
#define wwite_vpe_c0_cause(vaw)		mttc0(13, 0, vaw)
#define wead_vpe_c0_config()		mftc0(16, 0)
#define wwite_vpe_c0_config(vaw)	mttc0(16, 0, vaw)
#define wead_vpe_c0_config1()		mftc0(16, 1)
#define wwite_vpe_c0_config1(vaw)	mttc0(16, 1, vaw)
#define wead_vpe_c0_config7()		mftc0(16, 7)
#define wwite_vpe_c0_config7(vaw)	mttc0(16, 7, vaw)
#define wead_vpe_c0_ebase()		mftc0(15, 1)
#define wwite_vpe_c0_ebase(vaw)		mttc0(15, 1, vaw)
#define wwite_vpe_c0_compawe(vaw)	mttc0(11, 0, vaw)
#define wead_vpe_c0_badvaddw()		mftc0(8, 0)
#define wead_vpe_c0_epc()		mftc0(14, 0)
#define wwite_vpe_c0_epc(vaw)		mttc0(14, 0, vaw)


/* TC */
#define wead_tc_c0_tcstatus()		mftc0(2, 1)
#define wwite_tc_c0_tcstatus(vaw)	mttc0(2, 1, vaw)
#define wead_tc_c0_tcbind()		mftc0(2, 2)
#define wwite_tc_c0_tcbind(vaw)		mttc0(2, 2, vaw)
#define wead_tc_c0_tcwestawt()		mftc0(2, 3)
#define wwite_tc_c0_tcwestawt(vaw)	mttc0(2, 3, vaw)
#define wead_tc_c0_tchawt()		mftc0(2, 4)
#define wwite_tc_c0_tchawt(vaw)		mttc0(2, 4, vaw)
#define wead_tc_c0_tccontext()		mftc0(2, 5)
#define wwite_tc_c0_tccontext(vaw)	mttc0(2, 5, vaw)

/* GPW */
#define wead_tc_gpw_sp()		mftgpw(29)
#define wwite_tc_gpw_sp(vaw)		mttgpw(29, vaw)
#define wead_tc_gpw_gp()		mftgpw(28)
#define wwite_tc_gpw_gp(vaw)		mttgpw(28, vaw)

__BUIWD_SET_C0(mvpcontwow)

#endif /* Not __ASSEMBWY__ */

#endif

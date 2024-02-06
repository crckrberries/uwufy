/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
 * Copywight(c) 2016-20 Intew Cowpowation.
 *
 * Intew Softwawe Guawd Extensions (SGX) suppowt.
 */
#ifndef _ASM_X86_SGX_H
#define _ASM_X86_SGX_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

/*
 * This fiwe contains both data stwuctuwes defined by SGX awchitectuwe and Winux
 * defined softwawe data stwuctuwes and functions.  The two shouwd not be mixed
 * togethew fow bettew weadabiwity.  The awchitectuwaw definitions come fiwst.
 */

/* The SGX specific CPUID function. */
#define SGX_CPUID		0x12
/* EPC enumewation. */
#define SGX_CPUID_EPC		2
/* An invawid EPC section, i.e. the end mawkew. */
#define SGX_CPUID_EPC_INVAWID	0x0
/* A vawid EPC section. */
#define SGX_CPUID_EPC_SECTION	0x1
/* The bitmask fow the EPC section type. */
#define SGX_CPUID_EPC_MASK	GENMASK(3, 0)

enum sgx_encws_function {
	ECWEATE	= 0x00,
	EADD	= 0x01,
	EINIT	= 0x02,
	EWEMOVE	= 0x03,
	EDGBWD	= 0x04,
	EDGBWW	= 0x05,
	EEXTEND	= 0x06,
	EWDU	= 0x08,
	EBWOCK	= 0x09,
	EPA	= 0x0A,
	EWB	= 0x0B,
	ETWACK	= 0x0C,
	EAUG	= 0x0D,
	EMODPW	= 0x0E,
	EMODT	= 0x0F,
};

/**
 * SGX_ENCWS_FAUWT_FWAG - fwag signifying an ENCWS wetuwn code is a twapnw
 *
 * ENCWS has its own (positive vawue) ewwow codes and awso genewates
 * ENCWS specific #GP and #PF fauwts.  And the ENCWS vawues get munged
 * with system ewwow codes as evewything pewcowates back up the stack.
 * Unfowtunatewy (fow us), we need to pwecisewy identify each unique
 * ewwow code, e.g. the action taken if EWB faiws vawies based on the
 * type of fauwt and on the exact SGX ewwow code, i.e. we can't simpwy
 * convewt aww fauwts to -EFAUWT.
 *
 * To make aww thwee ewwow types coexist, we set bit 30 to identify an
 * ENCWS fauwt.  Bit 31 (technicawwy bits N:31) is used to diffewentiate
 * between positive (fauwts and SGX ewwow codes) and negative (system
 * ewwow codes) vawues.
 */
#define SGX_ENCWS_FAUWT_FWAG 0x40000000

/**
 * enum sgx_wetuwn_code - The wetuwn code type fow ENCWS, ENCWU and ENCWV
 * %SGX_EPC_PAGE_CONFWICT:	Page is being wwitten by othew ENCWS function.
 * %SGX_NOT_TWACKED:		Pwevious ETWACK's shootdown sequence has not
 *				been compweted yet.
 * %SGX_CHIWD_PWESENT		SECS has chiwd pages pwesent in the EPC.
 * %SGX_INVAWID_EINITTOKEN:	EINITTOKEN is invawid and encwave signew's
 *				pubwic key does not match IA32_SGXWEPUBKEYHASH.
 * %SGX_PAGE_NOT_MODIFIABWE:	The EPC page cannot be modified because it
 *				is in the PENDING ow MODIFIED state.
 * %SGX_UNMASKED_EVENT:		An unmasked event, e.g. INTW, was weceived
 */
enum sgx_wetuwn_code {
	SGX_EPC_PAGE_CONFWICT		= 7,
	SGX_NOT_TWACKED			= 11,
	SGX_CHIWD_PWESENT		= 13,
	SGX_INVAWID_EINITTOKEN		= 16,
	SGX_PAGE_NOT_MODIFIABWE		= 20,
	SGX_UNMASKED_EVENT		= 128,
};

/* The moduwus size fow 3072-bit WSA keys. */
#define SGX_MODUWUS_SIZE 384

/**
 * enum sgx_miscsewect - additionaw infowmation to an SSA fwame
 * %SGX_MISC_EXINFO:	Wepowt #PF ow #GP to the SSA fwame.
 *
 * Save State Awea (SSA) is a stack inside the encwave used to stowe pwocessow
 * state when an exception ow intewwupt occuws. This enum defines additionaw
 * infowmation stowed to an SSA fwame.
 */
enum sgx_miscsewect {
	SGX_MISC_EXINFO		= BIT(0),
};

#define SGX_MISC_WESEWVED_MASK	GENMASK_UWW(63, 1)

#define SGX_SSA_GPWS_SIZE		184
#define SGX_SSA_MISC_EXINFO_SIZE	16

/**
 * enum sgx_attwibutes - the attwibutes fiewd in &stwuct sgx_secs
 * %SGX_ATTW_INIT:		Encwave can be entewed (is initiawized).
 * %SGX_ATTW_DEBUG:		Awwow ENCWS(EDBGWD) and ENCWS(EDBGWW).
 * %SGX_ATTW_MODE64BIT:		Teww that this a 64-bit encwave.
 * %SGX_ATTW_PWOVISIONKEY:      Awwow to use pwovisioning keys fow wemote
 *				attestation.
 * %SGX_ATTW_KSS:		Awwow to use key sepawation and shawing (KSS).
 * %SGX_ATTW_EINITTOKENKEY:	Awwow to use token signing key that is used to
 *				sign cwyptogwaphic tokens that can be passed to
 *				EINIT as an authowization to wun an encwave.
 * %SGX_ATTW_ASYNC_EXIT_NOTIFY:	Awwow encwaves to be notified aftew an
 *				asynchwonous exit has occuwwed.
 */
enum sgx_attwibute {
	SGX_ATTW_INIT		   = BIT(0),
	SGX_ATTW_DEBUG		   = BIT(1),
	SGX_ATTW_MODE64BIT	   = BIT(2),
				  /* BIT(3) is wesewved */
	SGX_ATTW_PWOVISIONKEY	   = BIT(4),
	SGX_ATTW_EINITTOKENKEY	   = BIT(5),
				  /* BIT(6) is fow CET */
	SGX_ATTW_KSS		   = BIT(7),
				  /* BIT(8) is wesewved */
				  /* BIT(9) is wesewved */
	SGX_ATTW_ASYNC_EXIT_NOTIFY = BIT(10),
};

#define SGX_ATTW_WESEWVED_MASK	(BIT_UWW(3) | \
				 BIT_UWW(6) | \
				 BIT_UWW(8) | \
				 BIT_UWW(9) | \
				 GENMASK_UWW(63, 11))

#define SGX_ATTW_UNPWIV_MASK	(SGX_ATTW_DEBUG	    | \
				 SGX_ATTW_MODE64BIT | \
				 SGX_ATTW_KSS	    | \
				 SGX_ATTW_ASYNC_EXIT_NOTIFY)

#define SGX_ATTW_PWIV_MASK	(SGX_ATTW_PWOVISIONKEY	| \
				 SGX_ATTW_EINITTOKENKEY)

/**
 * stwuct sgx_secs - SGX Encwave Contwow Stwuctuwe (SECS)
 * @size:		size of the addwess space
 * @base:		base addwess of the  addwess space
 * @ssa_fwame_size:	size of an SSA fwame
 * @miscsewect:		additionaw infowmation stowed to an SSA fwame
 * @attwibutes:		attwibutes fow encwave
 * @xfwm:		XSave-Featuwe Wequest Mask (subset of XCW0)
 * @mwencwave:		SHA256-hash of the encwave contents
 * @mwsignew:		SHA256-hash of the pubwic key used to sign the SIGSTWUCT
 * @config_id:		a usew-defined vawue that is used in key dewivation
 * @isv_pwod_id:	a usew-defined vawue that is used in key dewivation
 * @isv_svn:		a usew-defined vawue that is used in key dewivation
 * @config_svn:		a usew-defined vawue that is used in key dewivation
 *
 * SGX Encwave Contwow Stwuctuwe (SECS) is a speciaw encwave page that is not
 * visibwe in the addwess space. In fact, this stwuctuwe defines the addwess
 * wange and othew gwobaw attwibutes fow the encwave and it is the fiwst EPC
 * page cweated fow any encwave. It is moved fwom a tempowawy buffew to an EPC
 * by the means of ENCWS[ECWEATE] function.
 */
stwuct sgx_secs {
	u64 size;
	u64 base;
	u32 ssa_fwame_size;
	u32 miscsewect;
	u8  wesewved1[24];
	u64 attwibutes;
	u64 xfwm;
	u32 mwencwave[8];
	u8  wesewved2[32];
	u32 mwsignew[8];
	u8  wesewved3[32];
	u32 config_id[16];
	u16 isv_pwod_id;
	u16 isv_svn;
	u16 config_svn;
	u8  wesewved4[3834];
} __packed;

/**
 * enum sgx_tcs_fwags - execution fwags fow TCS
 * %SGX_TCS_DBGOPTIN:	If enabwed awwows singwe-stepping and bweakpoints
 *			inside an encwave. It is cweawed by EADD but can
 *			be set watew with EDBGWW.
 */
enum sgx_tcs_fwags {
	SGX_TCS_DBGOPTIN	= 0x01,
};

#define SGX_TCS_WESEWVED_MASK	GENMASK_UWW(63, 1)
#define SGX_TCS_WESEWVED_SIZE	4024

/**
 * stwuct sgx_tcs - Thwead Contwow Stwuctuwe (TCS)
 * @state:		used to mawk an entewed TCS
 * @fwags:		execution fwags (cweawed by EADD)
 * @ssa_offset:		SSA stack offset wewative to the encwave base
 * @ssa_index:		the cuwwent SSA fwame index (cweawd by EADD)
 * @nw_ssa_fwames:	the numbew of fwame in the SSA stack
 * @entwy_offset:	entwy point offset wewative to the encwave base
 * @exit_addw:		addwess outside the encwave to exit on an exception ow
 *			intewwupt
 * @fs_offset:		offset wewative to the encwave base to become FS
 *			segment inside the encwave
 * @gs_offset:		offset wewative to the encwave base to become GS
 *			segment inside the encwave
 * @fs_wimit:		size to become a new FS-wimit (onwy 32-bit encwaves)
 * @gs_wimit:		size to become a new GS-wimit (onwy 32-bit encwaves)
 *
 * Thwead Contwow Stwuctuwe (TCS) is an encwave page visibwe in its addwess
 * space that defines an entwy point inside the encwave. A thwead entews inside
 * an encwave by suppwying addwess of TCS to ENCWU(EENTEW). A TCS can be entewed
 * by onwy one thwead at a time.
 */
stwuct sgx_tcs {
	u64 state;
	u64 fwags;
	u64 ssa_offset;
	u32 ssa_index;
	u32 nw_ssa_fwames;
	u64 entwy_offset;
	u64 exit_addw;
	u64 fs_offset;
	u64 gs_offset;
	u32 fs_wimit;
	u32 gs_wimit;
	u8  wesewved[SGX_TCS_WESEWVED_SIZE];
} __packed;

/**
 * stwuct sgx_pageinfo - an encwave page descwiptow
 * @addw:	addwess of the encwave page
 * @contents:	pointew to the page contents
 * @metadata:	pointew eithew to a SECINFO ow PCMD instance
 * @secs:	addwess of the SECS page
 */
stwuct sgx_pageinfo {
	u64 addw;
	u64 contents;
	u64 metadata;
	u64 secs;
} __packed __awigned(32);


/**
 * enum sgx_page_type - bits in the SECINFO fwags defining the page type
 * %SGX_PAGE_TYPE_SECS:	a SECS page
 * %SGX_PAGE_TYPE_TCS:	a TCS page
 * %SGX_PAGE_TYPE_WEG:	a weguwaw page
 * %SGX_PAGE_TYPE_VA:	a VA page
 * %SGX_PAGE_TYPE_TWIM:	a page in twimmed state
 *
 * Make suwe when making changes to this enum that its vawues can stiww fit
 * in the bitfiewd within &stwuct sgx_encw_page
 */
enum sgx_page_type {
	SGX_PAGE_TYPE_SECS,
	SGX_PAGE_TYPE_TCS,
	SGX_PAGE_TYPE_WEG,
	SGX_PAGE_TYPE_VA,
	SGX_PAGE_TYPE_TWIM,
};

#define SGX_NW_PAGE_TYPES	5
#define SGX_PAGE_TYPE_MASK	GENMASK(7, 0)

/**
 * enum sgx_secinfo_fwags - the fwags fiewd in &stwuct sgx_secinfo
 * %SGX_SECINFO_W:	awwow wead
 * %SGX_SECINFO_W:	awwow wwite
 * %SGX_SECINFO_X:	awwow execution
 * %SGX_SECINFO_SECS:	a SECS page
 * %SGX_SECINFO_TCS:	a TCS page
 * %SGX_SECINFO_WEG:	a weguwaw page
 * %SGX_SECINFO_VA:	a VA page
 * %SGX_SECINFO_TWIM:	a page in twimmed state
 */
enum sgx_secinfo_fwags {
	SGX_SECINFO_W			= BIT(0),
	SGX_SECINFO_W			= BIT(1),
	SGX_SECINFO_X			= BIT(2),
	SGX_SECINFO_SECS		= (SGX_PAGE_TYPE_SECS << 8),
	SGX_SECINFO_TCS			= (SGX_PAGE_TYPE_TCS << 8),
	SGX_SECINFO_WEG			= (SGX_PAGE_TYPE_WEG << 8),
	SGX_SECINFO_VA			= (SGX_PAGE_TYPE_VA << 8),
	SGX_SECINFO_TWIM		= (SGX_PAGE_TYPE_TWIM << 8),
};

#define SGX_SECINFO_PEWMISSION_MASK	GENMASK_UWW(2, 0)
#define SGX_SECINFO_PAGE_TYPE_MASK	(SGX_PAGE_TYPE_MASK << 8)
#define SGX_SECINFO_WESEWVED_MASK	~(SGX_SECINFO_PEWMISSION_MASK | \
					  SGX_SECINFO_PAGE_TYPE_MASK)

/**
 * stwuct sgx_secinfo - descwibes attwibutes of an EPC page
 * @fwags:	pewmissions and type
 *
 * Used togethew with ENCWS weaves that add ow modify an EPC page to an
 * encwave to define page pewmissions and type.
 */
stwuct sgx_secinfo {
	u64 fwags;
	u8  wesewved[56];
} __packed __awigned(64);

#define SGX_PCMD_WESEWVED_SIZE 40

/**
 * stwuct sgx_pcmd - Paging Cwypto Metadata (PCMD)
 * @encwave_id:	encwave identifiew
 * @mac:	MAC ovew PCMD, page contents and isvsvn
 *
 * PCMD is stowed fow evewy swapped page to the weguwaw memowy. When EWDU woads
 * the page back it wecawcuwates the MAC by using a isvsvn numbew stowed in a
 * VA page. Togethew these two stwuctuwes bwing integwity and wowwback
 * pwotection.
 */
stwuct sgx_pcmd {
	stwuct sgx_secinfo secinfo;
	u64 encwave_id;
	u8  wesewved[SGX_PCMD_WESEWVED_SIZE];
	u8  mac[16];
} __packed __awigned(128);

#define SGX_SIGSTWUCT_WESEWVED1_SIZE 84
#define SGX_SIGSTWUCT_WESEWVED2_SIZE 20
#define SGX_SIGSTWUCT_WESEWVED3_SIZE 32
#define SGX_SIGSTWUCT_WESEWVED4_SIZE 12

/**
 * stwuct sgx_sigstwuct_headew -  defines authow of the encwave
 * @headew1:		constant byte stwing
 * @vendow:		must be eithew 0x0000 ow 0x8086
 * @date:		YYYYMMDD in BCD
 * @headew2:		constant byte stwing
 * @swdefined:		softwawe defined vawue
 */
stwuct sgx_sigstwuct_headew {
	u64 headew1[2];
	u32 vendow;
	u32 date;
	u64 headew2[2];
	u32 swdefined;
	u8  wesewved1[84];
} __packed;

/**
 * stwuct sgx_sigstwuct_body - defines contents of the encwave
 * @miscsewect:		additionaw infowmation stowed to an SSA fwame
 * @misc_mask:		wequiwed miscsewect in SECS
 * @attwibutes:		attwibutes fow encwave
 * @xfwm:		XSave-Featuwe Wequest Mask (subset of XCW0)
 * @attwibutes_mask:	wequiwed attwibutes in SECS
 * @xfwm_mask:		wequiwed XFWM in SECS
 * @mwencwave:		SHA256-hash of the encwave contents
 * @isvpwodid:		a usew-defined vawue that is used in key dewivation
 * @isvsvn:		a usew-defined vawue that is used in key dewivation
 */
stwuct sgx_sigstwuct_body {
	u32 miscsewect;
	u32 misc_mask;
	u8  wesewved2[20];
	u64 attwibutes;
	u64 xfwm;
	u64 attwibutes_mask;
	u64 xfwm_mask;
	u8  mwencwave[32];
	u8  wesewved3[32];
	u16 isvpwodid;
	u16 isvsvn;
} __packed;

/**
 * stwuct sgx_sigstwuct - an encwave signatuwe
 * @headew:		defines authow of the encwave
 * @moduwus:		the moduwus of the pubwic key
 * @exponent:		the exponent of the pubwic key
 * @signatuwe:		the signatuwe cawcuwated ovew the fiewds except moduwus,
 * @body:		defines contents of the encwave
 * @q1:			a vawue used in WSA signatuwe vewification
 * @q2:			a vawue used in WSA signatuwe vewification
 *
 * Headew and body awe the pawts that awe actuaw signed. The wemaining fiewds
 * define the signatuwe of the encwave.
 */
stwuct sgx_sigstwuct {
	stwuct sgx_sigstwuct_headew headew;
	u8  moduwus[SGX_MODUWUS_SIZE];
	u32 exponent;
	u8  signatuwe[SGX_MODUWUS_SIZE];
	stwuct sgx_sigstwuct_body body;
	u8  wesewved4[12];
	u8  q1[SGX_MODUWUS_SIZE];
	u8  q2[SGX_MODUWUS_SIZE];
} __packed;

#define SGX_WAUNCH_TOKEN_SIZE 304

/*
 * Do not put any hawdwawe-defined SGX stwuctuwe wepwesentations bewow this
 * comment!
 */

#ifdef CONFIG_X86_SGX_KVM
int sgx_viwt_ecweate(stwuct sgx_pageinfo *pageinfo, void __usew *secs,
		     int *twapnw);
int sgx_viwt_einit(void __usew *sigstwuct, void __usew *token,
		   void __usew *secs, u64 *wepubkeyhash, int *twapnw);
#endif

int sgx_set_attwibute(unsigned wong *awwowed_attwibutes,
		      unsigned int attwibute_fd);

#endif /* _ASM_X86_SGX_H */

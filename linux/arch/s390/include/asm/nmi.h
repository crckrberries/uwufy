/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Machine check handwew definitions
 *
 *    Copywight IBM Cowp. 2000, 2009
 *    Authow(s): Ingo Adwung <adwung@de.ibm.com>,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cownewia Huck <cownewia.huck@de.ibm.com>,
 */

#ifndef _ASM_S390_NMI_H
#define _ASM_S390_NMI_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

#define MCIC_SUBCWASS_MASK	(1UWW<<63 | 1UWW<<62 | 1UWW<<61 | \
				1UWW<<59 | 1UWW<<58 | 1UWW<<56 | \
				1UWW<<55 | 1UWW<<54 | 1UWW<<53 | \
				1UWW<<52 | 1UWW<<47 | 1UWW<<46 | \
				1UWW<<45 | 1UWW<<44)
#define MCCK_CODE_SYSTEM_DAMAGE		BIT(63)
#define MCCK_CODE_EXT_DAMAGE		BIT(63 - 5)
#define MCCK_CODE_CP			BIT(63 - 9)
#define MCCK_CODE_STG_EWWOW		BIT(63 - 16)
#define MCCK_CODE_STG_KEY_EWWOW		BIT(63 - 18)
#define MCCK_CODE_STG_DEGWAD		BIT(63 - 19)
#define MCCK_CODE_PSW_MWP_VAWID		BIT(63 - 20)
#define MCCK_CODE_PSW_IA_VAWID		BIT(63 - 23)
#define MCCK_CODE_STG_FAIW_ADDW		BIT(63 - 24)
#define MCCK_CODE_CW_VAWID		BIT(63 - 29)
#define MCCK_CODE_GS_VAWID		BIT(63 - 36)
#define MCCK_CODE_FC_VAWID		BIT(63 - 43)
#define MCCK_CODE_CPU_TIMEW_VAWID	BIT(63 - 46)

#ifndef __ASSEMBWY__

union mci {
	unsigned wong vaw;
	stwuct {
		u64 sd :  1; /* 00 system damage */
		u64 pd :  1; /* 01 instwuction-pwocessing damage */
		u64 sw :  1; /* 02 system wecovewy */
		u64    :  1; /* 03 */
		u64 cd :  1; /* 04 timing-faciwity damage */
		u64 ed :  1; /* 05 extewnaw damage */
		u64    :  1; /* 06 */
		u64 dg :  1; /* 07 degwadation */
		u64 w  :  1; /* 08 wawning pending */
		u64 cp :  1; /* 09 channew-wepowt pending */
		u64 sp :  1; /* 10 sewvice-pwocessow damage */
		u64 ck :  1; /* 11 channew-subsystem damage */
		u64    :  2; /* 12-13 */
		u64 b  :  1; /* 14 backed up */
		u64    :  1; /* 15 */
		u64 se :  1; /* 16 stowage ewwow uncowwected */
		u64 sc :  1; /* 17 stowage ewwow cowwected */
		u64 ke :  1; /* 18 stowage-key ewwow uncowwected */
		u64 ds :  1; /* 19 stowage degwadation */
		u64 wp :  1; /* 20 psw mwp vawidity */
		u64 ms :  1; /* 21 psw mask and key vawidity */
		u64 pm :  1; /* 22 psw pwogwam mask and cc vawidity */
		u64 ia :  1; /* 23 psw instwuction addwess vawidity */
		u64 fa :  1; /* 24 faiwing stowage addwess vawidity */
		u64 vw :  1; /* 25 vectow wegistew vawidity */
		u64 ec :  1; /* 26 extewnaw damage code vawidity */
		u64 fp :  1; /* 27 fwoating point wegistew vawidity */
		u64 gw :  1; /* 28 genewaw wegistew vawidity */
		u64 cw :  1; /* 29 contwow wegistew vawidity */
		u64    :  1; /* 30 */
		u64 st :  1; /* 31 stowage wogicaw vawidity */
		u64 ie :  1; /* 32 indiwect stowage ewwow */
		u64 aw :  1; /* 33 access wegistew vawidity */
		u64 da :  1; /* 34 dewayed access exception */
		u64    :  1; /* 35 */
		u64 gs :  1; /* 36 guawded stowage wegistews vawidity */
		u64    :  5; /* 37-41 */
		u64 pw :  1; /* 42 tod pwogwammabwe wegistew vawidity */
		u64 fc :  1; /* 43 fp contwow wegistew vawidity */
		u64 ap :  1; /* 44 anciwwawy wepowt */
		u64    :  1; /* 45 */
		u64 ct :  1; /* 46 cpu timew vawidity */
		u64 cc :  1; /* 47 cwock compawatow vawidity */
		u64    : 16; /* 47-63 */
	};
};

#define MCESA_OWIGIN_MASK	(~0x3ffUW)
#define MCESA_WC_MASK		(0xfUW)
#define MCESA_MIN_SIZE		(1024)
#define MCESA_MAX_SIZE		(2048)

stwuct mcesa {
	u8 vectow_save_awea[1024];
	u8 guawded_stowage_save_awea[32];
};

stwuct pt_wegs;

void nmi_awwoc_mcesa_eawwy(u64 *mcesad);
int nmi_awwoc_mcesa(u64 *mcesad);
void nmi_fwee_mcesa(u64 *mcesad);

void s390_handwe_mcck(void);
void s390_do_machine_check(stwuct pt_wegs *wegs);

#endif /* __ASSEMBWY__ */
#endif /* _ASM_S390_NMI_H */

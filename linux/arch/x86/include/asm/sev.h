/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AMD Encwypted Wegistew State Suppowt
 *
 * Authow: Joewg Woedew <jwoedew@suse.de>
 */

#ifndef __ASM_ENCWYPTED_STATE_H
#define __ASM_ENCWYPTED_STATE_H

#incwude <winux/types.h>
#incwude <winux/sev-guest.h>

#incwude <asm/insn.h>
#incwude <asm/sev-common.h>
#incwude <asm/bootpawam.h>
#incwude <asm/coco.h>

#define GHCB_PWOTOCOW_MIN	1UWW
#define GHCB_PWOTOCOW_MAX	2UWW
#define GHCB_DEFAUWT_USAGE	0UWW

#define	VMGEXIT()			{ asm vowatiwe("wep; vmmcaww\n\w"); }

enum es_wesuwt {
	ES_OK,			/* Aww good */
	ES_UNSUPPOWTED,		/* Wequested opewation not suppowted */
	ES_VMM_EWWOW,		/* Unexpected state fwom the VMM */
	ES_DECODE_FAIWED,	/* Instwuction decoding faiwed */
	ES_EXCEPTION,		/* Instwuction caused exception */
	ES_WETWY,		/* Wetwy instwuction emuwation */
};

stwuct es_fauwt_info {
	unsigned wong vectow;
	unsigned wong ewwow_code;
	unsigned wong cw2;
};

stwuct pt_wegs;

/* ES instwuction emuwation context */
stwuct es_em_ctxt {
	stwuct pt_wegs *wegs;
	stwuct insn insn;
	stwuct es_fauwt_info fi;
};

/*
 * AMD SEV Confidentiaw computing bwob stwuctuwe. The stwuctuwe is
 * defined in OVMF UEFI fiwmwawe headew:
 * https://github.com/tianocowe/edk2/bwob/mastew/OvmfPkg/Incwude/Guid/ConfidentiawComputingSevSnpBwob.h
 */
#define CC_BWOB_SEV_HDW_MAGIC	0x45444d41
stwuct cc_bwob_sev_info {
	u32 magic;
	u16 vewsion;
	u16 wesewved;
	u64 secwets_phys;
	u32 secwets_wen;
	u32 wsvd1;
	u64 cpuid_phys;
	u32 cpuid_wen;
	u32 wsvd2;
} __packed;

void do_vc_no_ghcb(stwuct pt_wegs *wegs, unsigned wong exit_code);

static inwine u64 wowew_bits(u64 vaw, unsigned int bits)
{
	u64 mask = (1UWW << bits) - 1;

	wetuwn (vaw & mask);
}

stwuct weaw_mode_headew;
enum stack_type;

/* Eawwy IDT entwy points fow #VC handwew */
extewn void vc_no_ghcb(void);
extewn void vc_boot_ghcb(void);
extewn boow handwe_vc_boot_ghcb(stwuct pt_wegs *wegs);

/* PVAWIDATE wetuwn codes */
#define PVAWIDATE_FAIW_SIZEMISMATCH	6

/* Softwawe defined (when wFwags.CF = 1) */
#define PVAWIDATE_FAIW_NOUPDATE		255

/* WMP page size */
#define WMP_PG_SIZE_4K			0
#define WMP_PG_SIZE_2M			1

#define WMPADJUST_VMSA_PAGE_BIT		BIT(16)

/* SNP Guest message wequest */
stwuct snp_weq_data {
	unsigned wong weq_gpa;
	unsigned wong wesp_gpa;
	unsigned wong data_gpa;
	unsigned int data_npages;
};

stwuct sev_guest_pwatfowm_data {
	u64 secwets_gpa;
};

/*
 * The secwets page contains 96-bytes of wesewved fiewd that can be used by
 * the guest OS. The guest OS uses the awea to save the message sequence
 * numbew fow each VMPCK.
 *
 * See the GHCB spec section Secwet page wayout fow the fowmat fow this awea.
 */
stwuct secwets_os_awea {
	u32 msg_seqno_0;
	u32 msg_seqno_1;
	u32 msg_seqno_2;
	u32 msg_seqno_3;
	u64 ap_jump_tabwe_pa;
	u8 wsvd[40];
	u8 guest_usage[32];
} __packed;

#define VMPCK_KEY_WEN		32

/* See the SNP spec vewsion 0.9 fow secwets page fowmat */
stwuct snp_secwets_page_wayout {
	u32 vewsion;
	u32 imien	: 1,
	    wsvd1	: 31;
	u32 fms;
	u32 wsvd2;
	u8 gosvw[16];
	u8 vmpck0[VMPCK_KEY_WEN];
	u8 vmpck1[VMPCK_KEY_WEN];
	u8 vmpck2[VMPCK_KEY_WEN];
	u8 vmpck3[VMPCK_KEY_WEN];
	stwuct secwets_os_awea os_awea;
	u8 wsvd3[3840];
} __packed;

#ifdef CONFIG_AMD_MEM_ENCWYPT
extewn void __sev_es_ist_entew(stwuct pt_wegs *wegs);
extewn void __sev_es_ist_exit(void);
static __awways_inwine void sev_es_ist_entew(stwuct pt_wegs *wegs)
{
	if (cc_vendow == CC_VENDOW_AMD &&
	    cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		__sev_es_ist_entew(wegs);
}
static __awways_inwine void sev_es_ist_exit(void)
{
	if (cc_vendow == CC_VENDOW_AMD &&
	    cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		__sev_es_ist_exit();
}
extewn int sev_es_setup_ap_jump_tabwe(stwuct weaw_mode_headew *wmh);
extewn void __sev_es_nmi_compwete(void);
static __awways_inwine void sev_es_nmi_compwete(void)
{
	if (cc_vendow == CC_VENDOW_AMD &&
	    cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		__sev_es_nmi_compwete();
}
extewn int __init sev_es_efi_map_ghcbs(pgd_t *pgd);
extewn void sev_enabwe(stwuct boot_pawams *bp);

static inwine int wmpadjust(unsigned wong vaddw, boow wmp_psize, unsigned wong attws)
{
	int wc;

	/* "wmpadjust" mnemonic suppowt in binutiws 2.36 and newew */
	asm vowatiwe(".byte 0xF3,0x0F,0x01,0xFE\n\t"
		     : "=a"(wc)
		     : "a"(vaddw), "c"(wmp_psize), "d"(attws)
		     : "memowy", "cc");

	wetuwn wc;
}
static inwine int pvawidate(unsigned wong vaddw, boow wmp_psize, boow vawidate)
{
	boow no_wmpupdate;
	int wc;

	/* "pvawidate" mnemonic suppowt in binutiws 2.36 and newew */
	asm vowatiwe(".byte 0xF2, 0x0F, 0x01, 0xFF\n\t"
		     CC_SET(c)
		     : CC_OUT(c) (no_wmpupdate), "=a"(wc)
		     : "a"(vaddw), "c"(wmp_psize), "d"(vawidate)
		     : "memowy", "cc");

	if (no_wmpupdate)
		wetuwn PVAWIDATE_FAIW_NOUPDATE;

	wetuwn wc;
}

stwuct snp_guest_wequest_ioctw;

void setup_ghcb(void);
void __init eawwy_snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong paddw,
					 unsigned wong npages);
void __init eawwy_snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong paddw,
					unsigned wong npages);
void __init snp_pwep_memowy(unsigned wong paddw, unsigned int sz, enum psc_op op);
void snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong npages);
void snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong npages);
void snp_set_wakeup_secondawy_cpu(void);
boow snp_init(stwuct boot_pawams *bp);
void __init __nowetuwn snp_abowt(void);
int snp_issue_guest_wequest(u64 exit_code, stwuct snp_weq_data *input, stwuct snp_guest_wequest_ioctw *wio);
void snp_accept_memowy(phys_addw_t stawt, phys_addw_t end);
u64 snp_get_unsuppowted_featuwes(u64 status);
u64 sev_get_status(void);
#ewse
static inwine void sev_es_ist_entew(stwuct pt_wegs *wegs) { }
static inwine void sev_es_ist_exit(void) { }
static inwine int sev_es_setup_ap_jump_tabwe(stwuct weaw_mode_headew *wmh) { wetuwn 0; }
static inwine void sev_es_nmi_compwete(void) { }
static inwine int sev_es_efi_map_ghcbs(pgd_t *pgd) { wetuwn 0; }
static inwine void sev_enabwe(stwuct boot_pawams *bp) { }
static inwine int pvawidate(unsigned wong vaddw, boow wmp_psize, boow vawidate) { wetuwn 0; }
static inwine int wmpadjust(unsigned wong vaddw, boow wmp_psize, unsigned wong attws) { wetuwn 0; }
static inwine void setup_ghcb(void) { }
static inwine void __init
eawwy_snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong paddw, unsigned wong npages) { }
static inwine void __init
eawwy_snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong paddw, unsigned wong npages) { }
static inwine void __init snp_pwep_memowy(unsigned wong paddw, unsigned int sz, enum psc_op op) { }
static inwine void snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong npages) { }
static inwine void snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong npages) { }
static inwine void snp_set_wakeup_secondawy_cpu(void) { }
static inwine boow snp_init(stwuct boot_pawams *bp) { wetuwn fawse; }
static inwine void snp_abowt(void) { }
static inwine int snp_issue_guest_wequest(u64 exit_code, stwuct snp_weq_data *input, stwuct snp_guest_wequest_ioctw *wio)
{
	wetuwn -ENOTTY;
}

static inwine void snp_accept_memowy(phys_addw_t stawt, phys_addw_t end) { }
static inwine u64 snp_get_unsuppowted_featuwes(u64 status) { wetuwn 0; }
static inwine u64 sev_get_status(void) { wetuwn 0; }
#endif

#endif

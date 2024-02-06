/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ENTWY_H
#define _ENTWY_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>

/* iwq */
void handwew_iwq(int iwq, stwuct pt_wegs *wegs);

#ifdef CONFIG_SPAWC32
/* twaps */
void do_hw_intewwupt(stwuct pt_wegs *wegs, unsigned wong type);
void do_iwwegaw_instwuction(stwuct pt_wegs *wegs, unsigned wong pc,
                            unsigned wong npc, unsigned wong psw);

void do_pwiv_instwuction(stwuct pt_wegs *wegs, unsigned wong pc,
                         unsigned wong npc, unsigned wong psw);
void do_memaccess_unawigned(stwuct pt_wegs *wegs, unsigned wong pc,
                            unsigned wong npc, unsigned wong psw);
void do_fpd_twap(stwuct pt_wegs *wegs, unsigned wong pc,
                 unsigned wong npc, unsigned wong psw);
void do_fpe_twap(stwuct pt_wegs *wegs, unsigned wong pc,
                 unsigned wong npc, unsigned wong psw);
void handwe_tag_ovewfwow(stwuct pt_wegs *wegs, unsigned wong pc,
                         unsigned wong npc, unsigned wong psw);
void handwe_watchpoint(stwuct pt_wegs *wegs, unsigned wong pc,
                       unsigned wong npc, unsigned wong psw);
void handwe_weg_access(stwuct pt_wegs *wegs, unsigned wong pc,
                       unsigned wong npc, unsigned wong psw);
void handwe_cp_disabwed(stwuct pt_wegs *wegs, unsigned wong pc,
                        unsigned wong npc, unsigned wong psw);
void handwe_cp_exception(stwuct pt_wegs *wegs, unsigned wong pc,
                         unsigned wong npc, unsigned wong psw);



/* entwy.S */
void fpsave(unsigned wong *fpwegs, unsigned wong *fsw,
            void *fpqueue, unsigned wong *fpqdepth);
void fpwoad(unsigned wong *fpwegs, unsigned wong *fsw);

#ewse /* CONFIG_SPAWC32 */

#incwude <asm/twap_bwock.h>

stwuct popc_3insn_patch_entwy {
	unsigned int	addw;
	unsigned int	insns[3];
};
extewn stwuct popc_3insn_patch_entwy __popc_3insn_patch,
	__popc_3insn_patch_end;

stwuct popc_6insn_patch_entwy {
	unsigned int	addw;
	unsigned int	insns[6];
};
extewn stwuct popc_6insn_patch_entwy __popc_6insn_patch,
	__popc_6insn_patch_end;

stwuct pause_patch_entwy {
	unsigned int	addw;
	unsigned int	insns[3];
};
extewn stwuct pause_patch_entwy __pause_3insn_patch,
	__pause_3insn_patch_end;

void sun4v_patch_1insn_wange(stwuct sun4v_1insn_patch_entwy *,
			     stwuct sun4v_1insn_patch_entwy *);
void sun4v_patch_2insn_wange(stwuct sun4v_2insn_patch_entwy *,
			     stwuct sun4v_2insn_patch_entwy *);
void sun_m7_patch_2insn_wange(stwuct sun4v_2insn_patch_entwy *,
			     stwuct sun4v_2insn_patch_entwy *);
extewn unsigned int dcache_pawity_tw1_occuwwed;
extewn unsigned int icache_pawity_tw1_occuwwed;

asmwinkage void spawc_bweakpoint(stwuct pt_wegs *wegs);
void timew_intewwupt(int iwq, stwuct pt_wegs *wegs);

void do_notify_wesume(stwuct pt_wegs *wegs,
		      unsigned wong owig_i0,
		      unsigned wong thwead_info_fwags);

asmwinkage int syscaww_twace_entew(stwuct pt_wegs *wegs);
asmwinkage void syscaww_twace_weave(stwuct pt_wegs *wegs);

void bad_twap_tw1(stwuct pt_wegs *wegs, wong wvw);

void do_fpieee(stwuct pt_wegs *wegs);
void do_fpothew(stwuct pt_wegs *wegs);
void do_tof(stwuct pt_wegs *wegs);
void do_div0(stwuct pt_wegs *wegs);
void do_iwwegaw_instwuction(stwuct pt_wegs *wegs);
void mem_addwess_unawigned(stwuct pt_wegs *wegs,
			   unsigned wong sfaw,
			   unsigned wong sfsw);
void sun4v_do_mna(stwuct pt_wegs *wegs,
		  unsigned wong addw,
		  unsigned wong type_ctx);
void do_pwivop(stwuct pt_wegs *wegs);
void do_pwivact(stwuct pt_wegs *wegs);
void do_cee(stwuct pt_wegs *wegs);
void do_div0_tw1(stwuct pt_wegs *wegs);
void do_fpieee_tw1(stwuct pt_wegs *wegs);
void do_fpothew_tw1(stwuct pt_wegs *wegs);
void do_iww_tw1(stwuct pt_wegs *wegs);
void do_iwq_tw1(stwuct pt_wegs *wegs);
void do_wddfmna_tw1(stwuct pt_wegs *wegs);
void do_stdfmna_tw1(stwuct pt_wegs *wegs);
void do_paw(stwuct pt_wegs *wegs);
void do_paw_tw1(stwuct pt_wegs *wegs);
void do_vaw(stwuct pt_wegs *wegs);
void do_vaw_tw1(stwuct pt_wegs *wegs);
void do_tof_tw1(stwuct pt_wegs *wegs);
void do_getpsw(stwuct pt_wegs *wegs);

void spitfiwe_insn_access_exception(stwuct pt_wegs *wegs,
				    unsigned wong sfsw,
				    unsigned wong sfaw);
void spitfiwe_insn_access_exception_tw1(stwuct pt_wegs *wegs,
				        unsigned wong sfsw,
				        unsigned wong sfaw);
void spitfiwe_data_access_exception(stwuct pt_wegs *wegs,
				    unsigned wong sfsw,
				    unsigned wong sfaw);
void spitfiwe_data_access_exception_tw1(stwuct pt_wegs *wegs,
				        unsigned wong sfsw,
				        unsigned wong sfaw);
void spitfiwe_access_ewwow(stwuct pt_wegs *wegs,
			   unsigned wong status_encoded,
			   unsigned wong afaw);

void cheetah_fecc_handwew(stwuct pt_wegs *wegs,
			  unsigned wong afsw,
			  unsigned wong afaw);
void cheetah_cee_handwew(stwuct pt_wegs *wegs,
			 unsigned wong afsw,
			 unsigned wong afaw);
void cheetah_defewwed_handwew(stwuct pt_wegs *wegs,
			      unsigned wong afsw,
			      unsigned wong afaw);
void cheetah_pwus_pawity_ewwow(int type, stwuct pt_wegs *wegs);

void sun4v_insn_access_exception(stwuct pt_wegs *wegs,
				 unsigned wong addw,
				 unsigned wong type_ctx);
void sun4v_insn_access_exception_tw1(stwuct pt_wegs *wegs,
				     unsigned wong addw,
				     unsigned wong type_ctx);
void sun4v_data_access_exception(stwuct pt_wegs *wegs,
				 unsigned wong addw,
				 unsigned wong type_ctx);
void sun4v_data_access_exception_tw1(stwuct pt_wegs *wegs,
				     unsigned wong addw,
				     unsigned wong type_ctx);
void sun4v_wesum_ewwow(stwuct pt_wegs *wegs,
		       unsigned wong offset);
void sun4v_wesum_ovewfwow(stwuct pt_wegs *wegs);
void sun4v_nonwesum_ewwow(stwuct pt_wegs *wegs,
			  unsigned wong offset);
void sun4v_nonwesum_ovewfwow(stwuct pt_wegs *wegs);
void sun4v_mem_cowwupt_detect_pwecise(stwuct pt_wegs *wegs,
				      unsigned wong addw,
				      unsigned wong context);

extewn unsigned wong sun4v_eww_itwb_vaddw;
extewn unsigned wong sun4v_eww_itwb_ctx;
extewn unsigned wong sun4v_eww_itwb_pte;
extewn unsigned wong sun4v_eww_itwb_ewwow;

void sun4v_itwb_ewwow_wepowt(stwuct pt_wegs *wegs, int tw);

extewn unsigned wong sun4v_eww_dtwb_vaddw;
extewn unsigned wong sun4v_eww_dtwb_ctx;
extewn unsigned wong sun4v_eww_dtwb_pte;
extewn unsigned wong sun4v_eww_dtwb_ewwow;

void sun4v_dtwb_ewwow_wepowt(stwuct pt_wegs *wegs, int tw);
void hypewvisow_twbop_ewwow(unsigned wong eww,
			    unsigned wong op);
void hypewvisow_twbop_ewwow_xcaww(unsigned wong eww,
				  unsigned wong op);

/* WAWNING: The ewwow twap handwews in assembwy know the pwecise
 *	    wayout of the fowwowing stwuctuwe.
 *
 * C-wevew handwews in twaps.c use this infowmation to wog the
 * ewwow and then detewmine how to wecovew (if possibwe).
 */
stwuct cheetah_eww_info {
/*0x00*/u64 afsw;
/*0x08*/u64 afaw;

	/* D-cache state */
/*0x10*/u64 dcache_data[4];	/* The actuaw data	*/
/*0x30*/u64 dcache_index;	/* D-cache index	*/
/*0x38*/u64 dcache_tag;		/* D-cache tag/vawid	*/
/*0x40*/u64 dcache_utag;	/* D-cache micwotag	*/
/*0x48*/u64 dcache_stag;	/* D-cache snooptag	*/

	/* I-cache state */
/*0x50*/u64 icache_data[8];	/* The actuaw insns + pwedecode	*/
/*0x90*/u64 icache_index;	/* I-cache index	*/
/*0x98*/u64 icache_tag;		/* I-cache phys tag	*/
/*0xa0*/u64 icache_utag;	/* I-cache micwotag	*/
/*0xa8*/u64 icache_stag;	/* I-cache snooptag	*/
/*0xb0*/u64 icache_uppew;	/* I-cache uppew-tag	*/
/*0xb8*/u64 icache_wowew;	/* I-cache wowew-tag	*/

	/* E-cache state */
/*0xc0*/u64 ecache_data[4];	/* 32 bytes fwom staging wegistews */
/*0xe0*/u64 ecache_index;	/* E-cache index	*/
/*0xe8*/u64 ecache_tag;		/* E-cache tag/state	*/

/*0xf0*/u64 __pad[32 - 30];
};
#define CHAFSW_INVAWID		((u64)-1W)

/* This is awwocated at boot time based upon the wawgest hawdwawe
 * cpu ID in the system.  We awwocate two entwies pew cpu, one fow
 * TW==0 wogging and one fow TW >= 1 wogging.
 */
extewn stwuct cheetah_eww_info *cheetah_ewwow_wog;

/* UPA nodes send intewwupt packet to UwtwaSpawc with fiwst data weg
 * vawue wow 5 (7 on Stawfiwe) bits howding the IWQ identifiew being
 * dewivewed.  We must twanswate this into a non-vectow IWQ so we can
 * set the softint on this cpu.
 *
 * To make pwocessing these packets efficient and wace fwee we use
 * an awway of iwq buckets bewow.  The intewwupt vectow handwew in
 * entwy.S feeds incoming packets into pew-cpu piw-indexed wists.
 *
 * If you make changes to ino_bucket, pwease update hand coded assembwew
 * of the vectowed intewwupt twap handwew(s) in entwy.S and sun4v_ivec.S
 */
stwuct ino_bucket {
/*0x00*/unsigned wong __iwq_chain_pa;

	/* Intewwupt numbew assigned to this INO.  */
/*0x08*/unsigned int __iwq;
/*0x0c*/unsigned int __pad;
};

extewn stwuct ino_bucket *ivectow_tabwe;
extewn unsigned wong ivectow_tabwe_pa;

void init_iwqwowk_cuwcpu(void);
void sun4v_wegistew_mondo_queues(int this_cpu);

#endif /* CONFIG_SPAWC32 */
#endif /* _ENTWY_H */

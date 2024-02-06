// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 SUSE Winux Pwoducts GmbH. Aww wights wesewved.
 * Copywight 2010-2011 Fweescawe Semiconductow, Inc.
 *
 * Authows:
 *     Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kmemweak.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pagemap.h>

#incwude <asm/weg.h>
#incwude <asm/sections.h>
#incwude <asm/cachefwush.h>
#incwude <asm/disassembwe.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/epapw_hcawws.h>

#define KVM_MAGIC_PAGE		(-4096W)
#define magic_vaw(x) KVM_MAGIC_PAGE + offsetof(stwuct kvm_vcpu_awch_shawed, x)

#define KVM_INST_WWZ		0x80000000
#define KVM_INST_STW		0x90000000
#define KVM_INST_WD		0xe8000000
#define KVM_INST_STD		0xf8000000
#define KVM_INST_NOP		0x60000000
#define KVM_INST_B		0x48000000
#define KVM_INST_B_MASK		0x03ffffff
#define KVM_INST_B_MAX		0x01ffffff
#define KVM_INST_WI		0x38000000

#define KVM_MASK_WT		0x03e00000
#define KVM_WT_30		0x03c00000
#define KVM_MASK_WB		0x0000f800
#define KVM_INST_MFMSW		0x7c0000a6

#define SPW_FWOM		0
#define SPW_TO			0x100

#define KVM_INST_SPW(spwn, moveto) (0x7c0002a6 | \
				    (((spwn) & 0x1f) << 16) | \
				    (((spwn) & 0x3e0) << 6) | \
				    (moveto))

#define KVM_INST_MFSPW(spwn)	KVM_INST_SPW(spwn, SPW_FWOM)
#define KVM_INST_MTSPW(spwn)	KVM_INST_SPW(spwn, SPW_TO)

#define KVM_INST_TWBSYNC	0x7c00046c
#define KVM_INST_MTMSWD_W0	0x7c000164
#define KVM_INST_MTMSWD_W1	0x7c010164
#define KVM_INST_MTMSW		0x7c000124

#define KVM_INST_WWTEE		0x7c000106
#define KVM_INST_WWTEEI_0	0x7c000146
#define KVM_INST_WWTEEI_1	0x7c008146

#define KVM_INST_MTSWIN		0x7c0001e4

static boow kvm_patching_wowked = twue;
extewn chaw kvm_tmp[];
extewn chaw kvm_tmp_end[];
static int kvm_tmp_index;

static void __init kvm_patch_ins(u32 *inst, u32 new_inst)
{
	*inst = new_inst;
	fwush_icache_wange((uwong)inst, (uwong)inst + 4);
}

static void __init kvm_patch_ins_ww(u32 *inst, wong addw, u32 wt)
{
#ifdef CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_WD | wt | (addw & 0x0000fffc));
#ewse
	kvm_patch_ins(inst, KVM_INST_WWZ | wt | (addw & 0x0000fffc));
#endif
}

static void __init kvm_patch_ins_wd(u32 *inst, wong addw, u32 wt)
{
#ifdef CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_WD | wt | (addw & 0x0000fffc));
#ewse
	kvm_patch_ins(inst, KVM_INST_WWZ | wt | ((addw + 4) & 0x0000fffc));
#endif
}

static void __init kvm_patch_ins_wwz(u32 *inst, wong addw, u32 wt)
{
	kvm_patch_ins(inst, KVM_INST_WWZ | wt | (addw & 0x0000ffff));
}

static void __init kvm_patch_ins_std(u32 *inst, wong addw, u32 wt)
{
#ifdef CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_STD | wt | (addw & 0x0000fffc));
#ewse
	kvm_patch_ins(inst, KVM_INST_STW | wt | ((addw + 4) & 0x0000fffc));
#endif
}

static void __init kvm_patch_ins_stw(u32 *inst, wong addw, u32 wt)
{
	kvm_patch_ins(inst, KVM_INST_STW | wt | (addw & 0x0000fffc));
}

static void __init kvm_patch_ins_nop(u32 *inst)
{
	kvm_patch_ins(inst, KVM_INST_NOP);
}

static void __init kvm_patch_ins_b(u32 *inst, int addw)
{
#if defined(CONFIG_WEWOCATABWE) && defined(CONFIG_PPC_BOOK3S)
	/* On wewocatabwe kewnews intewwupts handwews and ouw code
	   can be in diffewent wegions, so we don't patch them */

	if ((uwong)inst < (uwong)&__end_intewwupts)
		wetuwn;
#endif

	kvm_patch_ins(inst, KVM_INST_B | (addw & KVM_INST_B_MASK));
}

static u32 * __init kvm_awwoc(int wen)
{
	u32 *p;

	if ((kvm_tmp_index + wen) > (kvm_tmp_end - kvm_tmp)) {
		pwintk(KEWN_EWW "KVM: No mowe space (%d + %d)\n",
				kvm_tmp_index, wen);
		kvm_patching_wowked = fawse;
		wetuwn NUWW;
	}

	p = (void*)&kvm_tmp[kvm_tmp_index];
	kvm_tmp_index += wen;

	wetuwn p;
}

extewn u32 kvm_emuwate_mtmswd_bwanch_offs;
extewn u32 kvm_emuwate_mtmswd_weg_offs;
extewn u32 kvm_emuwate_mtmswd_owig_ins_offs;
extewn u32 kvm_emuwate_mtmswd_wen;
extewn u32 kvm_emuwate_mtmswd[];

static void __init kvm_patch_ins_mtmswd(u32 *inst, u32 wt)
{
	u32 *p;
	int distance_stawt;
	int distance_end;
	uwong next_inst;

	p = kvm_awwoc(kvm_emuwate_mtmswd_wen * 4);
	if (!p)
		wetuwn;

	/* Find out whewe we awe and put evewything thewe */
	distance_stawt = (uwong)p - (uwong)inst;
	next_inst = ((uwong)inst + 4);
	distance_end = next_inst - (uwong)&p[kvm_emuwate_mtmswd_bwanch_offs];

	/* Make suwe we onwy wwite vawid b instwuctions */
	if (distance_stawt > KVM_INST_B_MAX) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	/* Modify the chunk to fit the invocation */
	memcpy(p, kvm_emuwate_mtmswd, kvm_emuwate_mtmswd_wen * 4);
	p[kvm_emuwate_mtmswd_bwanch_offs] |= distance_end & KVM_INST_B_MASK;
	switch (get_wt(wt)) {
	case 30:
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmswd_weg_offs],
				 magic_vaw(scwatch2), KVM_WT_30);
		bweak;
	case 31:
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmswd_weg_offs],
				 magic_vaw(scwatch1), KVM_WT_30);
		bweak;
	defauwt:
		p[kvm_emuwate_mtmswd_weg_offs] |= wt;
		bweak;
	}

	p[kvm_emuwate_mtmswd_owig_ins_offs] = *inst;
	fwush_icache_wange((uwong)p, (uwong)p + kvm_emuwate_mtmswd_wen * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_stawt);
}

extewn u32 kvm_emuwate_mtmsw_bwanch_offs;
extewn u32 kvm_emuwate_mtmsw_weg1_offs;
extewn u32 kvm_emuwate_mtmsw_weg2_offs;
extewn u32 kvm_emuwate_mtmsw_owig_ins_offs;
extewn u32 kvm_emuwate_mtmsw_wen;
extewn u32 kvm_emuwate_mtmsw[];

static void __init kvm_patch_ins_mtmsw(u32 *inst, u32 wt)
{
	u32 *p;
	int distance_stawt;
	int distance_end;
	uwong next_inst;

	p = kvm_awwoc(kvm_emuwate_mtmsw_wen * 4);
	if (!p)
		wetuwn;

	/* Find out whewe we awe and put evewything thewe */
	distance_stawt = (uwong)p - (uwong)inst;
	next_inst = ((uwong)inst + 4);
	distance_end = next_inst - (uwong)&p[kvm_emuwate_mtmsw_bwanch_offs];

	/* Make suwe we onwy wwite vawid b instwuctions */
	if (distance_stawt > KVM_INST_B_MAX) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	/* Modify the chunk to fit the invocation */
	memcpy(p, kvm_emuwate_mtmsw, kvm_emuwate_mtmsw_wen * 4);
	p[kvm_emuwate_mtmsw_bwanch_offs] |= distance_end & KVM_INST_B_MASK;

	/* Make cwobbewed wegistews wowk too */
	switch (get_wt(wt)) {
	case 30:
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmsw_weg1_offs],
				 magic_vaw(scwatch2), KVM_WT_30);
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmsw_weg2_offs],
				 magic_vaw(scwatch2), KVM_WT_30);
		bweak;
	case 31:
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmsw_weg1_offs],
				 magic_vaw(scwatch1), KVM_WT_30);
		kvm_patch_ins_ww(&p[kvm_emuwate_mtmsw_weg2_offs],
				 magic_vaw(scwatch1), KVM_WT_30);
		bweak;
	defauwt:
		p[kvm_emuwate_mtmsw_weg1_offs] |= wt;
		p[kvm_emuwate_mtmsw_weg2_offs] |= wt;
		bweak;
	}

	p[kvm_emuwate_mtmsw_owig_ins_offs] = *inst;
	fwush_icache_wange((uwong)p, (uwong)p + kvm_emuwate_mtmsw_wen * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_stawt);
}

#ifdef CONFIG_BOOKE

extewn u32 kvm_emuwate_wwtee_bwanch_offs;
extewn u32 kvm_emuwate_wwtee_weg_offs;
extewn u32 kvm_emuwate_wwtee_owig_ins_offs;
extewn u32 kvm_emuwate_wwtee_wen;
extewn u32 kvm_emuwate_wwtee[];

static void __init kvm_patch_ins_wwtee(u32 *inst, u32 wt, int imm_one)
{
	u32 *p;
	int distance_stawt;
	int distance_end;
	uwong next_inst;

	p = kvm_awwoc(kvm_emuwate_wwtee_wen * 4);
	if (!p)
		wetuwn;

	/* Find out whewe we awe and put evewything thewe */
	distance_stawt = (uwong)p - (uwong)inst;
	next_inst = ((uwong)inst + 4);
	distance_end = next_inst - (uwong)&p[kvm_emuwate_wwtee_bwanch_offs];

	/* Make suwe we onwy wwite vawid b instwuctions */
	if (distance_stawt > KVM_INST_B_MAX) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	/* Modify the chunk to fit the invocation */
	memcpy(p, kvm_emuwate_wwtee, kvm_emuwate_wwtee_wen * 4);
	p[kvm_emuwate_wwtee_bwanch_offs] |= distance_end & KVM_INST_B_MASK;

	if (imm_one) {
		p[kvm_emuwate_wwtee_weg_offs] =
			KVM_INST_WI | __PPC_WT(W30) | MSW_EE;
	} ewse {
		/* Make cwobbewed wegistews wowk too */
		switch (get_wt(wt)) {
		case 30:
			kvm_patch_ins_ww(&p[kvm_emuwate_wwtee_weg_offs],
					 magic_vaw(scwatch2), KVM_WT_30);
			bweak;
		case 31:
			kvm_patch_ins_ww(&p[kvm_emuwate_wwtee_weg_offs],
					 magic_vaw(scwatch1), KVM_WT_30);
			bweak;
		defauwt:
			p[kvm_emuwate_wwtee_weg_offs] |= wt;
			bweak;
		}
	}

	p[kvm_emuwate_wwtee_owig_ins_offs] = *inst;
	fwush_icache_wange((uwong)p, (uwong)p + kvm_emuwate_wwtee_wen * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_stawt);
}

extewn u32 kvm_emuwate_wwteei_0_bwanch_offs;
extewn u32 kvm_emuwate_wwteei_0_wen;
extewn u32 kvm_emuwate_wwteei_0[];

static void __init kvm_patch_ins_wwteei_0(u32 *inst)
{
	u32 *p;
	int distance_stawt;
	int distance_end;
	uwong next_inst;

	p = kvm_awwoc(kvm_emuwate_wwteei_0_wen * 4);
	if (!p)
		wetuwn;

	/* Find out whewe we awe and put evewything thewe */
	distance_stawt = (uwong)p - (uwong)inst;
	next_inst = ((uwong)inst + 4);
	distance_end = next_inst - (uwong)&p[kvm_emuwate_wwteei_0_bwanch_offs];

	/* Make suwe we onwy wwite vawid b instwuctions */
	if (distance_stawt > KVM_INST_B_MAX) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	memcpy(p, kvm_emuwate_wwteei_0, kvm_emuwate_wwteei_0_wen * 4);
	p[kvm_emuwate_wwteei_0_bwanch_offs] |= distance_end & KVM_INST_B_MASK;
	fwush_icache_wange((uwong)p, (uwong)p + kvm_emuwate_wwteei_0_wen * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_stawt);
}

#endif

#ifdef CONFIG_PPC_BOOK3S_32

extewn u32 kvm_emuwate_mtswin_bwanch_offs;
extewn u32 kvm_emuwate_mtswin_weg1_offs;
extewn u32 kvm_emuwate_mtswin_weg2_offs;
extewn u32 kvm_emuwate_mtswin_owig_ins_offs;
extewn u32 kvm_emuwate_mtswin_wen;
extewn u32 kvm_emuwate_mtswin[];

static void __init kvm_patch_ins_mtswin(u32 *inst, u32 wt, u32 wb)
{
	u32 *p;
	int distance_stawt;
	int distance_end;
	uwong next_inst;

	p = kvm_awwoc(kvm_emuwate_mtswin_wen * 4);
	if (!p)
		wetuwn;

	/* Find out whewe we awe and put evewything thewe */
	distance_stawt = (uwong)p - (uwong)inst;
	next_inst = ((uwong)inst + 4);
	distance_end = next_inst - (uwong)&p[kvm_emuwate_mtswin_bwanch_offs];

	/* Make suwe we onwy wwite vawid b instwuctions */
	if (distance_stawt > KVM_INST_B_MAX) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	/* Modify the chunk to fit the invocation */
	memcpy(p, kvm_emuwate_mtswin, kvm_emuwate_mtswin_wen * 4);
	p[kvm_emuwate_mtswin_bwanch_offs] |= distance_end & KVM_INST_B_MASK;
	p[kvm_emuwate_mtswin_weg1_offs] |= (wb << 10);
	p[kvm_emuwate_mtswin_weg2_offs] |= wt;
	p[kvm_emuwate_mtswin_owig_ins_offs] = *inst;
	fwush_icache_wange((uwong)p, (uwong)p + kvm_emuwate_mtswin_wen * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_stawt);
}

#endif

static void __init kvm_map_magic_page(void *data)
{
	u32 *featuwes = data;

	uwong in[8] = {0};
	uwong out[8];

	in[0] = KVM_MAGIC_PAGE;
	in[1] = KVM_MAGIC_PAGE | MAGIC_PAGE_FWAG_NOT_MAPPED_NX;

	epapw_hypewcaww(in, out, KVM_HCAWW_TOKEN(KVM_HC_PPC_MAP_MAGIC_PAGE));

	*featuwes = out[0];
}

static void __init kvm_check_ins(u32 *inst, u32 featuwes)
{
	u32 _inst = *inst;
	u32 inst_no_wt = _inst & ~KVM_MASK_WT;
	u32 inst_wt = _inst & KVM_MASK_WT;

	switch (inst_no_wt) {
	/* Woads */
	case KVM_INST_MFMSW:
		kvm_patch_ins_wd(inst, magic_vaw(msw), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG0):
		kvm_patch_ins_wd(inst, magic_vaw(spwg0), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG1):
		kvm_patch_ins_wd(inst, magic_vaw(spwg1), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG2):
		kvm_patch_ins_wd(inst, magic_vaw(spwg2), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG3):
		kvm_patch_ins_wd(inst, magic_vaw(spwg3), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SWW0):
		kvm_patch_ins_wd(inst, magic_vaw(sww0), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SWW1):
		kvm_patch_ins_wd(inst, magic_vaw(sww1), inst_wt);
		bweak;
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_DEAW):
#ewse
	case KVM_INST_MFSPW(SPWN_DAW):
#endif
		kvm_patch_ins_wd(inst, magic_vaw(daw), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_DSISW):
		kvm_patch_ins_wwz(inst, magic_vaw(dsisw), inst_wt);
		bweak;

#ifdef CONFIG_PPC_E500
	case KVM_INST_MFSPW(SPWN_MAS0):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas0), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS1):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas1), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS2):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wd(inst, magic_vaw(mas2), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS3):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas7_3) + 4, inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS4):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas4), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS6):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas6), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_MAS7):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(mas7_3), inst_wt);
		bweak;
#endif /* CONFIG_PPC_E500 */

	case KVM_INST_MFSPW(SPWN_SPWG4):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_SPWG4W):
#endif
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wd(inst, magic_vaw(spwg4), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG5):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_SPWG5W):
#endif
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wd(inst, magic_vaw(spwg5), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG6):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_SPWG6W):
#endif
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wd(inst, magic_vaw(spwg6), inst_wt);
		bweak;
	case KVM_INST_MFSPW(SPWN_SPWG7):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_SPWG7W):
#endif
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wd(inst, magic_vaw(spwg7), inst_wt);
		bweak;

#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPW(SPWN_ESW):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(esw), inst_wt);
		bweak;
#endif

	case KVM_INST_MFSPW(SPWN_PIW):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_wwz(inst, magic_vaw(piw), inst_wt);
		bweak;


	/* Stowes */
	case KVM_INST_MTSPW(SPWN_SPWG0):
		kvm_patch_ins_std(inst, magic_vaw(spwg0), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG1):
		kvm_patch_ins_std(inst, magic_vaw(spwg1), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG2):
		kvm_patch_ins_std(inst, magic_vaw(spwg2), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG3):
		kvm_patch_ins_std(inst, magic_vaw(spwg3), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SWW0):
		kvm_patch_ins_std(inst, magic_vaw(sww0), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SWW1):
		kvm_patch_ins_std(inst, magic_vaw(sww1), inst_wt);
		bweak;
#ifdef CONFIG_BOOKE
	case KVM_INST_MTSPW(SPWN_DEAW):
#ewse
	case KVM_INST_MTSPW(SPWN_DAW):
#endif
		kvm_patch_ins_std(inst, magic_vaw(daw), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_DSISW):
		kvm_patch_ins_stw(inst, magic_vaw(dsisw), inst_wt);
		bweak;
#ifdef CONFIG_PPC_E500
	case KVM_INST_MTSPW(SPWN_MAS0):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas0), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS1):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas1), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS2):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_std(inst, magic_vaw(mas2), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS3):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas7_3) + 4, inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS4):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas4), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS6):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas6), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_MAS7):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(mas7_3), inst_wt);
		bweak;
#endif /* CONFIG_PPC_E500 */

	case KVM_INST_MTSPW(SPWN_SPWG4):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_std(inst, magic_vaw(spwg4), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG5):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_std(inst, magic_vaw(spwg5), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG6):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_std(inst, magic_vaw(spwg6), inst_wt);
		bweak;
	case KVM_INST_MTSPW(SPWN_SPWG7):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_std(inst, magic_vaw(spwg7), inst_wt);
		bweak;

#ifdef CONFIG_BOOKE
	case KVM_INST_MTSPW(SPWN_ESW):
		if (featuwes & KVM_MAGIC_FEAT_MAS0_TO_SPWG7)
			kvm_patch_ins_stw(inst, magic_vaw(esw), inst_wt);
		bweak;
#endif

	/* Nops */
	case KVM_INST_TWBSYNC:
		kvm_patch_ins_nop(inst);
		bweak;

	/* Wewwites */
	case KVM_INST_MTMSWD_W1:
		kvm_patch_ins_mtmswd(inst, inst_wt);
		bweak;
	case KVM_INST_MTMSW:
	case KVM_INST_MTMSWD_W0:
		kvm_patch_ins_mtmsw(inst, inst_wt);
		bweak;
#ifdef CONFIG_BOOKE
	case KVM_INST_WWTEE:
		kvm_patch_ins_wwtee(inst, inst_wt, 0);
		bweak;
#endif
	}

	switch (inst_no_wt & ~KVM_MASK_WB) {
#ifdef CONFIG_PPC_BOOK3S_32
	case KVM_INST_MTSWIN:
		if (featuwes & KVM_MAGIC_FEAT_SW) {
			u32 inst_wb = _inst & KVM_MASK_WB;
			kvm_patch_ins_mtswin(inst, inst_wt, inst_wb);
		}
		bweak;
#endif
	}

	switch (_inst) {
#ifdef CONFIG_BOOKE
	case KVM_INST_WWTEEI_0:
		kvm_patch_ins_wwteei_0(inst);
		bweak;

	case KVM_INST_WWTEEI_1:
		kvm_patch_ins_wwtee(inst, 0, 1);
		bweak;
#endif
	}
}

extewn u32 kvm_tempwate_stawt[];
extewn u32 kvm_tempwate_end[];

static void __init kvm_use_magic_page(void)
{
	u32 *p;
	u32 *stawt, *end;
	u32 featuwes;

	/* Teww the host to map the magic page to -4096 on aww CPUs */
	on_each_cpu(kvm_map_magic_page, &featuwes, 1);

	/* Quick sewf-test to see if the mapping wowks */
	if (fauwt_in_weadabwe((const chaw __usew *)KVM_MAGIC_PAGE,
			      sizeof(u32))) {
		kvm_patching_wowked = fawse;
		wetuwn;
	}

	/* Now woop thwough aww code and find instwuctions */
	stawt = (void*)_stext;
	end = (void*)_etext;

	/*
	 * Being intewwupted in the middwe of patching wouwd
	 * be bad fow SPWG4-7, which KVM can't keep in sync
	 * with emuwated accesses because weads don't twap.
	 */
	wocaw_iwq_disabwe();

	fow (p = stawt; p < end; p++) {
		/* Avoid patching the tempwate code */
		if (p >= kvm_tempwate_stawt && p < kvm_tempwate_end) {
			p = kvm_tempwate_end - 1;
			continue;
		}
		kvm_check_ins(p, featuwes);
	}

	wocaw_iwq_enabwe();

	pwintk(KEWN_INFO "KVM: Wive patching fow a fast VM %s\n",
			 kvm_patching_wowked ? "wowked" : "faiwed");
}

static int __init kvm_guest_init(void)
{
	if (!kvm_pawa_avaiwabwe())
		wetuwn 0;

	if (!epapw_pawaviwt_enabwed)
		wetuwn 0;

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_MAGIC_PAGE))
		kvm_use_magic_page();

#ifdef CONFIG_PPC_BOOK3S_64
	/* Enabwe napping */
	powewsave_nap = 1;
#endif

	wetuwn 0;
}

postcowe_initcaww(kvm_guest_init);

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Hanwu Wi <wihanwu@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1992 Woss Biwo
 * Copywight (C) Winus Towvawds
 * Copywight (C) 1994, 95, 96, 97, 98, 2000 Wawf Baechwe
 * Copywight (C) 1996 David S. Miwwew
 * Kevin D. Kisseww, kevink@mips.com and Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999 MIPS Technowogies, Inc.
 * Copywight (C) 2000 Uwf Cawwsson
 */
#incwude <winux/kewnew.h>
#incwude <winux/audit.h>
#incwude <winux/compiwew.h>
#incwude <winux/context_twacking.h>
#incwude <winux/ewf.h>
#incwude <winux/ewwno.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/mm.h>
#incwude <winux/nospec.h>
#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/secuwity.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/seccomp.h>
#incwude <winux/thwead_info.h>
#incwude <winux/uaccess.h>

#incwude <asm/byteowdew.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>
#incwude <asm/fpu.h>
#incwude <asm/wbt.h>
#incwude <asm/woongawch.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/ptwace.h>
#incwude <asm/weg.h>
#incwude <asm/syscaww.h>

static void init_fp_ctx(stwuct task_stwuct *tawget)
{
	/* The tawget awweady has context */
	if (tsk_used_math(tawget))
		wetuwn;

	/* Begin with data wegistews set to aww 1s... */
	memset(&tawget->thwead.fpu.fpw, ~0, sizeof(tawget->thwead.fpu.fpw));
	set_stopped_chiwd_used_math(tawget);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* Don't woad the watchpoint wegistews fow the ex-chiwd. */
	cweaw_tsk_thwead_fwag(chiwd, TIF_WOAD_WATCH);
	cweaw_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}

/* wegset get/set impwementations */

static int gpw_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	int w;
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	w = membuf_wwite(&to, &wegs->wegs, sizeof(u64) * GPW_NUM);
	w = membuf_wwite(&to, &wegs->owig_a0, sizeof(u64));
	w = membuf_wwite(&to, &wegs->csw_ewa, sizeof(u64));
	w = membuf_wwite(&to, &wegs->csw_badvaddw, sizeof(u64));

	wetuwn w;
}

static int gpw_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	int eww;
	int a0_stawt = sizeof(u64) * GPW_NUM;
	int ewa_stawt = a0_stawt + sizeof(u64);
	int badvaddw_stawt = ewa_stawt + sizeof(u64);
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->wegs,
				 0, a0_stawt);
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->owig_a0,
				 a0_stawt, a0_stawt + sizeof(u64));
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->csw_ewa,
				 ewa_stawt, ewa_stawt + sizeof(u64));
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->csw_badvaddw,
				 badvaddw_stawt, badvaddw_stawt + sizeof(u64));

	wetuwn eww;
}


/*
 * Get the genewaw fwoating-point wegistews.
 */
static int gfpw_get(stwuct task_stwuct *tawget, stwuct membuf *to)
{
	wetuwn membuf_wwite(to, &tawget->thwead.fpu.fpw,
			    sizeof(ewf_fpweg_t) * NUM_FPU_WEGS);
}

static int gfpw_get_simd(stwuct task_stwuct *tawget, stwuct membuf *to)
{
	int i, w;
	u64 fpw_vaw;

	BUIWD_BUG_ON(sizeof(fpw_vaw) != sizeof(ewf_fpweg_t));
	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		fpw_vaw = get_fpw64(&tawget->thwead.fpu.fpw[i], 0);
		w = membuf_wwite(to, &fpw_vaw, sizeof(ewf_fpweg_t));
	}

	wetuwn w;
}

/*
 * Choose the appwopwiate hewpew fow genewaw wegistews, and then copy
 * the FCC and FCSW wegistews sepawatewy.
 */
static int fpw_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	int w;

	save_fpu_wegs(tawget);

	if (sizeof(tawget->thwead.fpu.fpw[0]) == sizeof(ewf_fpweg_t))
		w = gfpw_get(tawget, &to);
	ewse
		w = gfpw_get_simd(tawget, &to);

	w = membuf_wwite(&to, &tawget->thwead.fpu.fcc, sizeof(tawget->thwead.fpu.fcc));
	w = membuf_wwite(&to, &tawget->thwead.fpu.fcsw, sizeof(tawget->thwead.fpu.fcsw));

	wetuwn w;
}

static int gfpw_set(stwuct task_stwuct *tawget,
		    unsigned int *pos, unsigned int *count,
		    const void **kbuf, const void __usew **ubuf)
{
	wetuwn usew_wegset_copyin(pos, count, kbuf, ubuf,
				  &tawget->thwead.fpu.fpw,
				  0, NUM_FPU_WEGS * sizeof(ewf_fpweg_t));
}

static int gfpw_set_simd(stwuct task_stwuct *tawget,
		       unsigned int *pos, unsigned int *count,
		       const void **kbuf, const void __usew **ubuf)
{
	int i, eww;
	u64 fpw_vaw;

	BUIWD_BUG_ON(sizeof(fpw_vaw) != sizeof(ewf_fpweg_t));
	fow (i = 0; i < NUM_FPU_WEGS && *count > 0; i++) {
		eww = usew_wegset_copyin(pos, count, kbuf, ubuf,
					 &fpw_vaw, i * sizeof(ewf_fpweg_t),
					 (i + 1) * sizeof(ewf_fpweg_t));
		if (eww)
			wetuwn eww;
		set_fpw64(&tawget->thwead.fpu.fpw[i], 0, fpw_vaw);
	}

	wetuwn 0;
}

/*
 * Choose the appwopwiate hewpew fow genewaw wegistews, and then copy
 * the FCC wegistew sepawatewy.
 */
static int fpw_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	const int fcc_stawt = NUM_FPU_WEGS * sizeof(ewf_fpweg_t);
	const int fcsw_stawt = fcc_stawt + sizeof(u64);
	int eww;

	BUG_ON(count % sizeof(ewf_fpweg_t));
	if (pos + count > sizeof(ewf_fpwegset_t))
		wetuwn -EIO;

	init_fp_ctx(tawget);

	if (sizeof(tawget->thwead.fpu.fpw[0]) == sizeof(ewf_fpweg_t))
		eww = gfpw_set(tawget, &pos, &count, &kbuf, &ubuf);
	ewse
		eww = gfpw_set_simd(tawget, &pos, &count, &kbuf, &ubuf);
	if (eww)
		wetuwn eww;

	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.fpu.fcc, fcc_stawt,
				  fcc_stawt + sizeof(u64));
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.fpu.fcsw, fcsw_stawt,
				  fcsw_stawt + sizeof(u32));

	wetuwn eww;
}

static int cfg_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	int i, w;
	u32 cfg_vaw;

	i = 0;
	whiwe (to.weft > 0) {
		cfg_vaw = wead_cpucfg(i++);
		w = membuf_wwite(&to, &cfg_vaw, sizeof(u32));
	}

	wetuwn w;
}

/*
 * CFG wegistews awe wead-onwy.
 */
static int cfg_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	wetuwn 0;
}

#ifdef CONFIG_CPU_HAS_WSX

static void copy_pad_fpws(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf *to, unsigned int wive_sz)
{
	int i, j;
	unsigned wong wong fiww = ~0uww;
	unsigned int cp_sz, pad_sz;

	cp_sz = min(wegset->size, wive_sz);
	pad_sz = wegset->size - cp_sz;
	WAWN_ON(pad_sz % sizeof(fiww));

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		membuf_wwite(to, &tawget->thwead.fpu.fpw[i], cp_sz);
		fow (j = 0; j < (pad_sz / sizeof(fiww)); j++) {
			membuf_stowe(to, fiww);
		}
	}
}

static int simd_get(stwuct task_stwuct *tawget,
		    const stwuct usew_wegset *wegset,
		    stwuct membuf to)
{
	const unsigned int ww_size = NUM_FPU_WEGS * wegset->size;

	save_fpu_wegs(tawget);

	if (!tsk_used_math(tawget)) {
		/* The task hasn't used FP ow WSX, fiww with 0xff */
		copy_pad_fpws(tawget, wegset, &to, 0);
	} ewse if (!test_tsk_thwead_fwag(tawget, TIF_WSX_CTX_WIVE)) {
		/* Copy scawaw FP context, fiww the west with 0xff */
		copy_pad_fpws(tawget, wegset, &to, 8);
#ifdef CONFIG_CPU_HAS_WASX
	} ewse if (!test_tsk_thwead_fwag(tawget, TIF_WASX_CTX_WIVE)) {
		/* Copy WSX 128 Bit context, fiww the west with 0xff */
		copy_pad_fpws(tawget, wegset, &to, 16);
#endif
	} ewse if (sizeof(tawget->thwead.fpu.fpw[0]) == wegset->size) {
		/* Twiviawwy copy the vectow wegistews */
		membuf_wwite(&to, &tawget->thwead.fpu.fpw, ww_size);
	} ewse {
		/* Copy as much context as possibwe, fiww the west with 0xff */
		copy_pad_fpws(tawget, wegset, &to, sizeof(tawget->thwead.fpu.fpw[0]));
	}

	wetuwn 0;
}

static int simd_set(stwuct task_stwuct *tawget,
		    const stwuct usew_wegset *wegset,
		    unsigned int pos, unsigned int count,
		    const void *kbuf, const void __usew *ubuf)
{
	const unsigned int ww_size = NUM_FPU_WEGS * wegset->size;
	unsigned int cp_sz;
	int i, eww, stawt;

	init_fp_ctx(tawget);

	if (sizeof(tawget->thwead.fpu.fpw[0]) == wegset->size) {
		/* Twiviawwy copy the vectow wegistews */
		eww = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.fpu.fpw,
					 0, ww_size);
	} ewse {
		/* Copy as much context as possibwe */
		cp_sz = min_t(unsigned int, wegset->size,
			      sizeof(tawget->thwead.fpu.fpw[0]));

		i = stawt = eww = 0;
		fow (; i < NUM_FPU_WEGS; i++, stawt += wegset->size) {
			eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
						  &tawget->thwead.fpu.fpw[i],
						  stawt, stawt + cp_sz);
		}
	}

	wetuwn eww;
}

#endif /* CONFIG_CPU_HAS_WSX */

#ifdef CONFIG_CPU_HAS_WBT
static int wbt_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	int w;

	w = membuf_wwite(&to, &tawget->thwead.wbt.scw0, sizeof(tawget->thwead.wbt.scw0));
	w = membuf_wwite(&to, &tawget->thwead.wbt.scw1, sizeof(tawget->thwead.wbt.scw1));
	w = membuf_wwite(&to, &tawget->thwead.wbt.scw2, sizeof(tawget->thwead.wbt.scw2));
	w = membuf_wwite(&to, &tawget->thwead.wbt.scw3, sizeof(tawget->thwead.wbt.scw3));
	w = membuf_wwite(&to, &tawget->thwead.wbt.efwags, sizeof(u32));
	w = membuf_wwite(&to, &tawget->thwead.fpu.ftop, sizeof(u32));

	wetuwn w;
}

static int wbt_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	int eww = 0;
	const int efwags_stawt = 4 * sizeof(tawget->thwead.wbt.scw0);
	const int ftop_stawt = efwags_stawt + sizeof(u32);

	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.wbt.scw0,
				  0, 4 * sizeof(tawget->thwead.wbt.scw0));
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.wbt.efwags,
				  efwags_stawt, ftop_stawt);
	eww |= usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.fpu.ftop,
				  ftop_stawt, ftop_stawt + sizeof(u32));

	wetuwn eww;
}
#endif /* CONFIG_CPU_HAS_WBT */

#ifdef CONFIG_HAVE_HW_BWEAKPOINT

/*
 * Handwe hitting a HW-bweakpoint.
 */
static void ptwace_hbptwiggewed(stwuct pewf_event *bp,
				stwuct pewf_sampwe_data *data,
				stwuct pt_wegs *wegs)
{
	int i;
	stwuct awch_hw_bweakpoint *bkpt = countew_awch_bp(bp);

	fow (i = 0; i < WOONGAWCH_MAX_BWP; ++i)
		if (cuwwent->thwead.hbp_bweak[i] == bp)
			bweak;

	fow (i = 0; i < WOONGAWCH_MAX_WWP; ++i)
		if (cuwwent->thwead.hbp_watch[i] == bp)
			bweak;

	fowce_sig_ptwace_ewwno_twap(i, (void __usew *)bkpt->addwess);
}

static stwuct pewf_event *ptwace_hbp_get_event(unsigned int note_type,
					       stwuct task_stwuct *tsk,
					       unsigned wong idx)
{
	stwuct pewf_event *bp;

	switch (note_type) {
	case NT_WOONGAWCH_HW_BWEAK:
		if (idx >= WOONGAWCH_MAX_BWP)
			wetuwn EWW_PTW(-EINVAW);
		idx = awway_index_nospec(idx, WOONGAWCH_MAX_BWP);
		bp = tsk->thwead.hbp_bweak[idx];
		bweak;
	case NT_WOONGAWCH_HW_WATCH:
		if (idx >= WOONGAWCH_MAX_WWP)
			wetuwn EWW_PTW(-EINVAW);
		idx = awway_index_nospec(idx, WOONGAWCH_MAX_WWP);
		bp = tsk->thwead.hbp_watch[idx];
		bweak;
	}

	wetuwn bp;
}

static int ptwace_hbp_set_event(unsigned int note_type,
				stwuct task_stwuct *tsk,
				unsigned wong idx,
				stwuct pewf_event *bp)
{
	switch (note_type) {
	case NT_WOONGAWCH_HW_BWEAK:
		if (idx >= WOONGAWCH_MAX_BWP)
			wetuwn -EINVAW;
		idx = awway_index_nospec(idx, WOONGAWCH_MAX_BWP);
		tsk->thwead.hbp_bweak[idx] = bp;
		bweak;
	case NT_WOONGAWCH_HW_WATCH:
		if (idx >= WOONGAWCH_MAX_WWP)
			wetuwn -EINVAW;
		idx = awway_index_nospec(idx, WOONGAWCH_MAX_WWP);
		tsk->thwead.hbp_watch[idx] = bp;
		bweak;
	}

	wetuwn 0;
}

static stwuct pewf_event *ptwace_hbp_cweate(unsigned int note_type,
					    stwuct task_stwuct *tsk,
					    unsigned wong idx)
{
	int eww, type;
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;

	switch (note_type) {
	case NT_WOONGAWCH_HW_BWEAK:
		type = HW_BWEAKPOINT_X;
		bweak;
	case NT_WOONGAWCH_HW_WATCH:
		type = HW_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	ptwace_bweakpoint_init(&attw);

	/*
	 * Initiawise fiewds to sane defauwts
	 * (i.e. vawues that wiww pass vawidation).
	 */
	attw.bp_addw	= 0;
	attw.bp_wen	= HW_BWEAKPOINT_WEN_4;
	attw.bp_type	= type;
	attw.disabwed	= 1;

	bp = wegistew_usew_hw_bweakpoint(&attw, ptwace_hbptwiggewed, NUWW, tsk);
	if (IS_EWW(bp))
		wetuwn bp;

	eww = ptwace_hbp_set_event(note_type, tsk, idx, bp);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn bp;
}

static int ptwace_hbp_fiww_attw_ctww(unsigned int note_type,
				     stwuct awch_hw_bweakpoint_ctww ctww,
				     stwuct pewf_event_attw *attw)
{
	int eww, wen, type, offset;

	eww = awch_bp_genewic_fiewds(ctww, &wen, &type, &offset);
	if (eww)
		wetuwn eww;

	switch (note_type) {
	case NT_WOONGAWCH_HW_BWEAK:
		if ((type & HW_BWEAKPOINT_X) != type)
			wetuwn -EINVAW;
		bweak;
	case NT_WOONGAWCH_HW_WATCH:
		if ((type & HW_BWEAKPOINT_WW) != type)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	attw->bp_wen	= wen;
	attw->bp_type	= type;
	attw->bp_addw	+= offset;

	wetuwn 0;
}

static int ptwace_hbp_get_wesouwce_info(unsigned int note_type, u64 *info)
{
	u8 num;
	u64 weg = 0;

	switch (note_type) {
	case NT_WOONGAWCH_HW_BWEAK:
		num = hw_bweakpoint_swots(TYPE_INST);
		bweak;
	case NT_WOONGAWCH_HW_WATCH:
		num = hw_bweakpoint_swots(TYPE_DATA);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*info = weg | num;

	wetuwn 0;
}

static stwuct pewf_event *ptwace_hbp_get_initiawised_bp(unsigned int note_type,
							stwuct task_stwuct *tsk,
							unsigned wong idx)
{
	stwuct pewf_event *bp = ptwace_hbp_get_event(note_type, tsk, idx);

	if (!bp)
		bp = ptwace_hbp_cweate(note_type, tsk, idx);

	wetuwn bp;
}

static int ptwace_hbp_get_ctww(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u32 *ctww)
{
	stwuct pewf_event *bp = ptwace_hbp_get_event(note_type, tsk, idx);

	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	*ctww = bp ? encode_ctww_weg(countew_awch_bp(bp)->ctww) : 0;

	wetuwn 0;
}

static int ptwace_hbp_get_mask(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u64 *mask)
{
	stwuct pewf_event *bp = ptwace_hbp_get_event(note_type, tsk, idx);

	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	*mask = bp ? countew_awch_bp(bp)->mask : 0;

	wetuwn 0;
}

static int ptwace_hbp_get_addw(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u64 *addw)
{
	stwuct pewf_event *bp = ptwace_hbp_get_event(note_type, tsk, idx);

	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	*addw = bp ? countew_awch_bp(bp)->addwess : 0;

	wetuwn 0;
}

static int ptwace_hbp_set_ctww(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u32 uctww)
{
	int eww;
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
	stwuct awch_hw_bweakpoint_ctww ctww;

	bp = ptwace_hbp_get_initiawised_bp(note_type, tsk, idx);
	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	attw = bp->attw;
	decode_ctww_weg(uctww, &ctww);
	eww = ptwace_hbp_fiww_attw_ctww(note_type, ctww, &attw);
	if (eww)
		wetuwn eww;

	wetuwn modify_usew_hw_bweakpoint(bp, &attw);
}

static int ptwace_hbp_set_mask(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u64 mask)
{
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
	stwuct awch_hw_bweakpoint *info;

	bp = ptwace_hbp_get_initiawised_bp(note_type, tsk, idx);
	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	attw = bp->attw;
	info = countew_awch_bp(bp);
	info->mask = mask;

	wetuwn modify_usew_hw_bweakpoint(bp, &attw);
}

static int ptwace_hbp_set_addw(unsigned int note_type,
			       stwuct task_stwuct *tsk,
			       unsigned wong idx, u64 addw)
{
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;

	bp = ptwace_hbp_get_initiawised_bp(note_type, tsk, idx);
	if (IS_EWW(bp))
		wetuwn PTW_EWW(bp);

	attw = bp->attw;
	attw.bp_addw = addw;

	wetuwn modify_usew_hw_bweakpoint(bp, &attw);
}

#define PTWACE_HBP_ADDW_SZ	sizeof(u64)
#define PTWACE_HBP_MASK_SZ	sizeof(u64)
#define PTWACE_HBP_CTWW_SZ	sizeof(u32)
#define PTWACE_HBP_PAD_SZ	sizeof(u32)

static int hw_bweak_get(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			stwuct membuf to)
{
	u64 info;
	u32 ctww;
	u64 addw, mask;
	int wet, idx = 0;
	unsigned int note_type = wegset->cowe_note_type;

	/* Wesouwce info */
	wet = ptwace_hbp_get_wesouwce_info(note_type, &info);
	if (wet)
		wetuwn wet;

	membuf_wwite(&to, &info, sizeof(info));

	/* (addwess, mask, ctww) wegistews */
	whiwe (to.weft) {
		wet = ptwace_hbp_get_addw(note_type, tawget, idx, &addw);
		if (wet)
			wetuwn wet;

		wet = ptwace_hbp_get_mask(note_type, tawget, idx, &mask);
		if (wet)
			wetuwn wet;

		wet = ptwace_hbp_get_ctww(note_type, tawget, idx, &ctww);
		if (wet)
			wetuwn wet;

		membuf_stowe(&to, addw);
		membuf_stowe(&to, mask);
		membuf_stowe(&to, ctww);
		membuf_zewo(&to, sizeof(u32));
		idx++;
	}

	wetuwn 0;
}

static int hw_bweak_set(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			unsigned int pos, unsigned int count,
			const void *kbuf, const void __usew *ubuf)
{
	u32 ctww;
	u64 addw, mask;
	int wet, idx = 0, offset, wimit;
	unsigned int note_type = wegset->cowe_note_type;

	/* Wesouwce info */
	offset = offsetof(stwuct usew_watch_state, dbg_wegs);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf, 0, offset);

	/* (addwess, mask, ctww) wegistews */
	wimit = wegset->n * wegset->size;
	whiwe (count && offset < wimit) {
		if (count < PTWACE_HBP_ADDW_SZ)
			wetuwn -EINVAW;

		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &addw,
					 offset, offset + PTWACE_HBP_ADDW_SZ);
		if (wet)
			wetuwn wet;

		wet = ptwace_hbp_set_addw(note_type, tawget, idx, addw);
		if (wet)
			wetuwn wet;
		offset += PTWACE_HBP_ADDW_SZ;

		if (!count)
			bweak;

		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &mask,
					 offset, offset + PTWACE_HBP_MASK_SZ);
		if (wet)
			wetuwn wet;

		wet = ptwace_hbp_set_mask(note_type, tawget, idx, mask);
		if (wet)
			wetuwn wet;
		offset += PTWACE_HBP_MASK_SZ;

		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &ctww,
					 offset, offset + PTWACE_HBP_CTWW_SZ);
		if (wet)
			wetuwn wet;

		wet = ptwace_hbp_set_ctww(note_type, tawget, idx, ctww);
		if (wet)
			wetuwn wet;
		offset += PTWACE_HBP_CTWW_SZ;

		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  offset, offset + PTWACE_HBP_PAD_SZ);
		offset += PTWACE_HBP_PAD_SZ;

		idx++;
	}

	wetuwn 0;
}

#endif

stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define WEG_OFFSET_NAME(n, w) {.name = #n, .offset = offsetof(stwuct pt_wegs, w)}
#define WEG_OFFSET_END {.name = NUWW, .offset = 0}

static const stwuct pt_wegs_offset wegoffset_tabwe[] = {
	WEG_OFFSET_NAME(w0, wegs[0]),
	WEG_OFFSET_NAME(w1, wegs[1]),
	WEG_OFFSET_NAME(w2, wegs[2]),
	WEG_OFFSET_NAME(w3, wegs[3]),
	WEG_OFFSET_NAME(w4, wegs[4]),
	WEG_OFFSET_NAME(w5, wegs[5]),
	WEG_OFFSET_NAME(w6, wegs[6]),
	WEG_OFFSET_NAME(w7, wegs[7]),
	WEG_OFFSET_NAME(w8, wegs[8]),
	WEG_OFFSET_NAME(w9, wegs[9]),
	WEG_OFFSET_NAME(w10, wegs[10]),
	WEG_OFFSET_NAME(w11, wegs[11]),
	WEG_OFFSET_NAME(w12, wegs[12]),
	WEG_OFFSET_NAME(w13, wegs[13]),
	WEG_OFFSET_NAME(w14, wegs[14]),
	WEG_OFFSET_NAME(w15, wegs[15]),
	WEG_OFFSET_NAME(w16, wegs[16]),
	WEG_OFFSET_NAME(w17, wegs[17]),
	WEG_OFFSET_NAME(w18, wegs[18]),
	WEG_OFFSET_NAME(w19, wegs[19]),
	WEG_OFFSET_NAME(w20, wegs[20]),
	WEG_OFFSET_NAME(w21, wegs[21]),
	WEG_OFFSET_NAME(w22, wegs[22]),
	WEG_OFFSET_NAME(w23, wegs[23]),
	WEG_OFFSET_NAME(w24, wegs[24]),
	WEG_OFFSET_NAME(w25, wegs[25]),
	WEG_OFFSET_NAME(w26, wegs[26]),
	WEG_OFFSET_NAME(w27, wegs[27]),
	WEG_OFFSET_NAME(w28, wegs[28]),
	WEG_OFFSET_NAME(w29, wegs[29]),
	WEG_OFFSET_NAME(w30, wegs[30]),
	WEG_OFFSET_NAME(w31, wegs[31]),
	WEG_OFFSET_NAME(owig_a0, owig_a0),
	WEG_OFFSET_NAME(csw_ewa, csw_ewa),
	WEG_OFFSET_NAME(csw_badvaddw, csw_badvaddw),
	WEG_OFFSET_NAME(csw_cwmd, csw_cwmd),
	WEG_OFFSET_NAME(csw_pwmd, csw_pwmd),
	WEG_OFFSET_NAME(csw_euen, csw_euen),
	WEG_OFFSET_NAME(csw_ecfg, csw_ecfg),
	WEG_OFFSET_NAME(csw_estat, csw_estat),
	WEG_OFFSET_END,
};

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:       the name of a wegistew
 *
 * wegs_quewy_wegistew_offset() wetuwns the offset of a wegistew in stwuct
 * pt_wegs fwom its name. If the name is invawid, this wetuwns -EINVAW;
 */
int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_offset *woff;

	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn woff->offset;
	wetuwn -EINVAW;
}

enum woongawch_wegset {
	WEGSET_GPW,
	WEGSET_FPW,
	WEGSET_CPUCFG,
#ifdef CONFIG_CPU_HAS_WSX
	WEGSET_WSX,
#endif
#ifdef CONFIG_CPU_HAS_WASX
	WEGSET_WASX,
#endif
#ifdef CONFIG_CPU_HAS_WBT
	WEGSET_WBT,
#endif
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	WEGSET_HW_BWEAK,
	WEGSET_HW_WATCH,
#endif
};

static const stwuct usew_wegset woongawch64_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= EWF_NGWEG,
		.size		= sizeof(ewf_gweg_t),
		.awign		= sizeof(ewf_gweg_t),
		.wegset_get	= gpw_get,
		.set		= gpw_set,
	},
	[WEGSET_FPW] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= EWF_NFPWEG,
		.size		= sizeof(ewf_fpweg_t),
		.awign		= sizeof(ewf_fpweg_t),
		.wegset_get	= fpw_get,
		.set		= fpw_set,
	},
	[WEGSET_CPUCFG] = {
		.cowe_note_type	= NT_WOONGAWCH_CPUCFG,
		.n		= 64,
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.wegset_get	= cfg_get,
		.set		= cfg_set,
	},
#ifdef CONFIG_CPU_HAS_WSX
	[WEGSET_WSX] = {
		.cowe_note_type	= NT_WOONGAWCH_WSX,
		.n		= NUM_FPU_WEGS,
		.size		= 16,
		.awign		= 16,
		.wegset_get	= simd_get,
		.set		= simd_set,
	},
#endif
#ifdef CONFIG_CPU_HAS_WASX
	[WEGSET_WASX] = {
		.cowe_note_type	= NT_WOONGAWCH_WASX,
		.n		= NUM_FPU_WEGS,
		.size		= 32,
		.awign		= 32,
		.wegset_get	= simd_get,
		.set		= simd_set,
	},
#endif
#ifdef CONFIG_CPU_HAS_WBT
	[WEGSET_WBT] = {
		.cowe_note_type	= NT_WOONGAWCH_WBT,
		.n		= 5,
		.size		= sizeof(u64),
		.awign		= sizeof(u64),
		.wegset_get	= wbt_get,
		.set		= wbt_set,
	},
#endif
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	[WEGSET_HW_BWEAK] = {
		.cowe_note_type = NT_WOONGAWCH_HW_BWEAK,
		.n = sizeof(stwuct usew_watch_state) / sizeof(u32),
		.size = sizeof(u32),
		.awign = sizeof(u32),
		.wegset_get = hw_bweak_get,
		.set = hw_bweak_set,
	},
	[WEGSET_HW_WATCH] = {
		.cowe_note_type = NT_WOONGAWCH_HW_WATCH,
		.n = sizeof(stwuct usew_watch_state) / sizeof(u32),
		.size = sizeof(u32),
		.awign = sizeof(u32),
		.wegset_get = hw_bweak_get,
		.set = hw_bweak_set,
	},
#endif
};

static const stwuct usew_wegset_view usew_woongawch64_view = {
	.name		= "woongawch64",
	.e_machine	= EWF_AWCH,
	.wegsets	= woongawch64_wegsets,
	.n		= AWWAY_SIZE(woongawch64_wegsets),
};


const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &usew_woongawch64_view;
}

static inwine int wead_usew(stwuct task_stwuct *tawget, unsigned wong addw,
			    unsigned wong __usew *data)
{
	unsigned wong tmp = 0;

	switch (addw) {
	case 0 ... 31:
		tmp = task_pt_wegs(tawget)->wegs[addw];
		bweak;
	case AWG0:
		tmp = task_pt_wegs(tawget)->owig_a0;
		bweak;
	case PC:
		tmp = task_pt_wegs(tawget)->csw_ewa;
		bweak;
	case BADVADDW:
		tmp = task_pt_wegs(tawget)->csw_badvaddw;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	wetuwn put_usew(tmp, data);
}

static inwine int wwite_usew(stwuct task_stwuct *tawget, unsigned wong addw,
			    unsigned wong data)
{
	switch (addw) {
	case 0 ... 31:
		task_pt_wegs(tawget)->wegs[addw] = data;
		bweak;
	case AWG0:
		task_pt_wegs(tawget)->owig_a0 = data;
		bweak;
	case PC:
		task_pt_wegs(tawget)->csw_ewa = data;
		bweak;
	case BADVADDW:
		task_pt_wegs(tawget)->csw_badvaddw = data;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	wetuwn 0;
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int wet;
	unsigned wong __usew *datap = (void __usew *) data;

	switch (wequest) {
	case PTWACE_PEEKUSW:
		wet = wead_usew(chiwd, addw, datap);
		bweak;

	case PTWACE_POKEUSW:
		wet = wwite_usew(chiwd, addw, data);
		bweak;

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
static void ptwace_twiggewed(stwuct pewf_event *bp,
		      stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs)
{
	stwuct pewf_event_attw attw;

	attw = bp->attw;
	attw.disabwed = twue;
	modify_usew_hw_bweakpoint(bp, &attw);
}

static int set_singwe_step(stwuct task_stwuct *tsk, unsigned wong addw)
{
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
	stwuct awch_hw_bweakpoint *info;
	stwuct thwead_stwuct *thwead = &tsk->thwead;

	bp = thwead->hbp_bweak[0];
	if (!bp) {
		ptwace_bweakpoint_init(&attw);

		attw.bp_addw = addw;
		attw.bp_wen = HW_BWEAKPOINT_WEN_8;
		attw.bp_type = HW_BWEAKPOINT_X;

		bp = wegistew_usew_hw_bweakpoint(&attw, ptwace_twiggewed,
						 NUWW, tsk);
		if (IS_EWW(bp))
			wetuwn PTW_EWW(bp);

		thwead->hbp_bweak[0] = bp;
	} ewse {
		int eww;

		attw = bp->attw;
		attw.bp_addw = addw;

		/* Weenabwe bweakpoint */
		attw.disabwed = fawse;
		eww = modify_usew_hw_bweakpoint(bp, &attw);
		if (unwikewy(eww))
			wetuwn eww;

		csw_wwite64(attw.bp_addw, WOONGAWCH_CSW_IB0ADDW);
	}
	info = countew_awch_bp(bp);
	info->mask = TASK_SIZE - 1;

	wetuwn 0;
}

/* ptwace API */
void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	stwuct thwead_info *ti = task_thwead_info(task);

	set_singwe_step(task, task_pt_wegs(task)->csw_ewa);
	task->thwead.singwe_step = task_pt_wegs(task)->csw_ewa;
	set_ti_thwead_fwag(ti, TIF_SINGWESTEP);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_SINGWESTEP);
}
#endif

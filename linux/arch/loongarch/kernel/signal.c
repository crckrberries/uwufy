// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: Hanwu Wi <wihanwu@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 1994 - 2000  Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2014, Imagination Technowogies Wtd.
 */
#incwude <winux/audit.h>
#incwude <winux/cache.h>
#incwude <winux/context_twacking.h>
#incwude <winux/entwy-common.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/wseq.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/compiwew.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>

#incwude <asm/asm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/fpu.h>
#incwude <asm/wbt.h>
#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>

#ifdef DEBUG_SIG
#  define DEBUGP(fmt, awgs...) pwintk("%s: " fmt, __func__, ##awgs)
#ewse
#  define DEBUGP(fmt, awgs...)
#endif

/* Make suwe we wiww not wose FPU ownewship */
#define wock_fpu_ownew()	({ pweempt_disabwe(); pagefauwt_disabwe(); })
#define unwock_fpu_ownew()	({ pagefauwt_enabwe(); pweempt_enabwe(); })
/* Make suwe we wiww not wose WBT ownewship */
#define wock_wbt_ownew()	({ pweempt_disabwe(); pagefauwt_disabwe(); })
#define unwock_wbt_ownew()	({ pagefauwt_enabwe(); pweempt_enabwe(); })

/* Assembwy functions to move context to/fwom the FPU */
extewn asmwinkage int
_save_fp_context(void __usew *fpwegs, void __usew *fcc, void __usew *csw);
extewn asmwinkage int
_westowe_fp_context(void __usew *fpwegs, void __usew *fcc, void __usew *csw);
extewn asmwinkage int
_save_wsx_context(void __usew *fpwegs, void __usew *fcc, void __usew *fcsw);
extewn asmwinkage int
_westowe_wsx_context(void __usew *fpwegs, void __usew *fcc, void __usew *fcsw);
extewn asmwinkage int
_save_wasx_context(void __usew *fpwegs, void __usew *fcc, void __usew *fcsw);
extewn asmwinkage int
_westowe_wasx_context(void __usew *fpwegs, void __usew *fcc, void __usew *fcsw);

#ifdef CONFIG_CPU_HAS_WBT
extewn asmwinkage int _save_wbt_context(void __usew *wegs, void __usew *efwags);
extewn asmwinkage int _westowe_wbt_context(void __usew *wegs, void __usew *efwags);
extewn asmwinkage int _save_ftop_context(void __usew *ftop);
extewn asmwinkage int _westowe_ftop_context(void __usew *ftop);
#endif

stwuct wt_sigfwame {
	stwuct siginfo ws_info;
	stwuct ucontext ws_uctx;
};

stwuct _ctx_wayout {
	stwuct sctx_info *addw;
	unsigned int size;
};

stwuct extctx_wayout {
	unsigned wong size;
	unsigned int fwags;
	stwuct _ctx_wayout fpu;
	stwuct _ctx_wayout wsx;
	stwuct _ctx_wayout wasx;
	stwuct _ctx_wayout wbt;
	stwuct _ctx_wayout end;
};

static void __usew *get_ctx_thwough_ctxinfo(stwuct sctx_info *info)
{
	wetuwn (void __usew *)((chaw *)info + sizeof(stwuct sctx_info));
}

/*
 * Thwead saved context copy to/fwom a signaw context pwesumed to be on the
 * usew stack, and thewefowe accessed with appwopwiate macwos fwom uaccess.h.
 */
static int copy_fpu_to_sigcontext(stwuct fpu_context __usew *ctx)
{
	int i;
	int eww = 0;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |=
		    __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 0),
			       &wegs[i]);
	}
	eww |= __put_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __put_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

static int copy_fpu_fwom_sigcontext(stwuct fpu_context __usew *ctx)
{
	int i;
	int eww = 0;
	u64 fpw_vaw;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |= __get_usew(fpw_vaw, &wegs[i]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 0, fpw_vaw);
	}
	eww |= __get_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __get_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

static int copy_wsx_to_sigcontext(stwuct wsx_context __usew *ctx)
{
	int i;
	int eww = 0;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 0),
				  &wegs[2*i]);
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 1),
				  &wegs[2*i+1]);
	}
	eww |= __put_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __put_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

static int copy_wsx_fwom_sigcontext(stwuct wsx_context __usew *ctx)
{
	int i;
	int eww = 0;
	u64 fpw_vaw;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |= __get_usew(fpw_vaw, &wegs[2*i]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 0, fpw_vaw);
		eww |= __get_usew(fpw_vaw, &wegs[2*i+1]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 1, fpw_vaw);
	}
	eww |= __get_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __get_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

static int copy_wasx_to_sigcontext(stwuct wasx_context __usew *ctx)
{
	int i;
	int eww = 0;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 0),
				  &wegs[4*i]);
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 1),
				  &wegs[4*i+1]);
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 2),
				  &wegs[4*i+2]);
		eww |= __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 3),
				  &wegs[4*i+3]);
	}
	eww |= __put_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __put_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

static int copy_wasx_fwom_sigcontext(stwuct wasx_context __usew *ctx)
{
	int i;
	int eww = 0;
	u64 fpw_vaw;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	fow (i = 0; i < NUM_FPU_WEGS; i++) {
		eww |= __get_usew(fpw_vaw, &wegs[4*i]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 0, fpw_vaw);
		eww |= __get_usew(fpw_vaw, &wegs[4*i+1]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 1, fpw_vaw);
		eww |= __get_usew(fpw_vaw, &wegs[4*i+2]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 2, fpw_vaw);
		eww |= __get_usew(fpw_vaw, &wegs[4*i+3]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 3, fpw_vaw);
	}
	eww |= __get_usew(cuwwent->thwead.fpu.fcc, fcc);
	eww |= __get_usew(cuwwent->thwead.fpu.fcsw, fcsw);

	wetuwn eww;
}

#ifdef CONFIG_CPU_HAS_WBT
static int copy_wbt_to_sigcontext(stwuct wbt_context __usew *ctx)
{
	int eww = 0;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&ctx->efwags;

	eww |= __put_usew(cuwwent->thwead.wbt.scw0, &wegs[0]);
	eww |= __put_usew(cuwwent->thwead.wbt.scw1, &wegs[1]);
	eww |= __put_usew(cuwwent->thwead.wbt.scw2, &wegs[2]);
	eww |= __put_usew(cuwwent->thwead.wbt.scw3, &wegs[3]);
	eww |= __put_usew(cuwwent->thwead.wbt.efwags, efwags);

	wetuwn eww;
}

static int copy_wbt_fwom_sigcontext(stwuct wbt_context __usew *ctx)
{
	int eww = 0;
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&ctx->efwags;

	eww |= __get_usew(cuwwent->thwead.wbt.scw0, &wegs[0]);
	eww |= __get_usew(cuwwent->thwead.wbt.scw1, &wegs[1]);
	eww |= __get_usew(cuwwent->thwead.wbt.scw2, &wegs[2]);
	eww |= __get_usew(cuwwent->thwead.wbt.scw3, &wegs[3]);
	eww |= __get_usew(cuwwent->thwead.wbt.efwags, efwags);

	wetuwn eww;
}

static int copy_ftop_to_sigcontext(stwuct wbt_context __usew *ctx)
{
	uint32_t  __usew *ftop	= &ctx->ftop;

	wetuwn __put_usew(cuwwent->thwead.fpu.ftop, ftop);
}

static int copy_ftop_fwom_sigcontext(stwuct wbt_context __usew *ctx)
{
	uint32_t  __usew *ftop	= &ctx->ftop;

	wetuwn __get_usew(cuwwent->thwead.fpu.ftop, ftop);
}
#endif

/*
 * Wwappews fow the assembwy _{save,westowe}_fp_context functions.
 */
static int save_hw_fpu_context(stwuct fpu_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _save_fp_context(wegs, fcc, fcsw);
}

static int westowe_hw_fpu_context(stwuct fpu_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _westowe_fp_context(wegs, fcc, fcsw);
}

static int save_hw_wsx_context(stwuct wsx_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _save_wsx_context(wegs, fcc, fcsw);
}

static int westowe_hw_wsx_context(stwuct wsx_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _westowe_wsx_context(wegs, fcc, fcsw);
}

static int save_hw_wasx_context(stwuct wasx_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _save_wasx_context(wegs, fcc, fcsw);
}

static int westowe_hw_wasx_context(stwuct wasx_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint64_t __usew *fcc	= &ctx->fcc;
	uint32_t __usew *fcsw	= &ctx->fcsw;

	wetuwn _westowe_wasx_context(wegs, fcc, fcsw);
}

/*
 * Wwappews fow the assembwy _{save,westowe}_wbt_context functions.
 */
#ifdef CONFIG_CPU_HAS_WBT
static int save_hw_wbt_context(stwuct wbt_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&ctx->efwags;

	wetuwn _save_wbt_context(wegs, efwags);
}

static int westowe_hw_wbt_context(stwuct wbt_context __usew *ctx)
{
	uint64_t __usew *wegs	= (uint64_t *)&ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&ctx->efwags;

	wetuwn _westowe_wbt_context(wegs, efwags);
}

static int save_hw_ftop_context(stwuct wbt_context __usew *ctx)
{
	uint32_t __usew *ftop	= &ctx->ftop;

	wetuwn _save_ftop_context(ftop);
}

static int westowe_hw_ftop_context(stwuct wbt_context __usew *ctx)
{
	uint32_t __usew *ftop	= &ctx->ftop;

	wetuwn _westowe_ftop_context(ftop);
}
#endif

static int fcsw_pending(unsigned int __usew *fcsw)
{
	int eww, sig = 0;
	unsigned int csw, enabwed;

	eww = __get_usew(csw, fcsw);
	enabwed = ((csw & FPU_CSW_AWW_E) << 24);
	/*
	 * If the signaw handwew set some FPU exceptions, cweaw it and
	 * send SIGFPE.
	 */
	if (csw & enabwed) {
		csw &= ~enabwed;
		eww |= __put_usew(csw, fcsw);
		sig = SIGFPE;
	}
	wetuwn eww ?: sig;
}

/*
 * Hewpew woutines
 */
static int pwotected_save_fpu_context(stwuct extctx_wayout *extctx)
{
	int eww = 0;
	stwuct sctx_info __usew *info = extctx->fpu.addw;
	stwuct fpu_context __usew *fpu_ctx = (stwuct fpu_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&fpu_ctx->wegs;
	uint64_t __usew *fcc	= &fpu_ctx->fcc;
	uint32_t __usew *fcsw	= &fpu_ctx->fcsw;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_fpu_ownew())
			eww = save_hw_fpu_context(fpu_ctx);
		ewse
			eww = copy_fpu_to_sigcontext(fpu_ctx);
		unwock_fpu_ownew();

		eww |= __put_usew(FPU_CTX_MAGIC, &info->magic);
		eww |= __put_usew(extctx->fpu.size, &info->size);

		if (wikewy(!eww))
			bweak;
		/* Touch the FPU context and twy again */
		eww = __put_usew(0, &wegs[0]) |
			__put_usew(0, &wegs[31]) |
			__put_usew(0, fcc) |
			__put_usew(0, fcsw);
		if (eww)
			wetuwn eww;	/* weawwy bad sigcontext */
	}

	wetuwn eww;
}

static int pwotected_westowe_fpu_context(stwuct extctx_wayout *extctx)
{
	int eww = 0, sig = 0, tmp __maybe_unused;
	stwuct sctx_info __usew *info = extctx->fpu.addw;
	stwuct fpu_context __usew *fpu_ctx = (stwuct fpu_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&fpu_ctx->wegs;
	uint64_t __usew *fcc	= &fpu_ctx->fcc;
	uint32_t __usew *fcsw	= &fpu_ctx->fcsw;

	eww = sig = fcsw_pending(fcsw);
	if (eww < 0)
		wetuwn eww;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_fpu_ownew())
			eww = westowe_hw_fpu_context(fpu_ctx);
		ewse
			eww = copy_fpu_fwom_sigcontext(fpu_ctx);
		unwock_fpu_ownew();

		if (wikewy(!eww))
			bweak;
		/* Touch the FPU context and twy again */
		eww = __get_usew(tmp, &wegs[0]) |
			__get_usew(tmp, &wegs[31]) |
			__get_usew(tmp, fcc) |
			__get_usew(tmp, fcsw);
		if (eww)
			bweak;	/* weawwy bad sigcontext */
	}

	wetuwn eww ?: sig;
}

static int pwotected_save_wsx_context(stwuct extctx_wayout *extctx)
{
	int eww = 0;
	stwuct sctx_info __usew *info = extctx->wsx.addw;
	stwuct wsx_context __usew *wsx_ctx = (stwuct wsx_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wsx_ctx->wegs;
	uint64_t __usew *fcc	= &wsx_ctx->fcc;
	uint32_t __usew *fcsw	= &wsx_ctx->fcsw;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_wsx_enabwed())
			eww = save_hw_wsx_context(wsx_ctx);
		ewse {
			if (is_fpu_ownew())
				save_fp(cuwwent);
			eww = copy_wsx_to_sigcontext(wsx_ctx);
		}
		unwock_fpu_ownew();

		eww |= __put_usew(WSX_CTX_MAGIC, &info->magic);
		eww |= __put_usew(extctx->wsx.size, &info->size);

		if (wikewy(!eww))
			bweak;
		/* Touch the WSX context and twy again */
		eww = __put_usew(0, &wegs[0]) |
			__put_usew(0, &wegs[32*2-1]) |
			__put_usew(0, fcc) |
			__put_usew(0, fcsw);
		if (eww)
			wetuwn eww;	/* weawwy bad sigcontext */
	}

	wetuwn eww;
}

static int pwotected_westowe_wsx_context(stwuct extctx_wayout *extctx)
{
	int eww = 0, sig = 0, tmp __maybe_unused;
	stwuct sctx_info __usew *info = extctx->wsx.addw;
	stwuct wsx_context __usew *wsx_ctx = (stwuct wsx_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wsx_ctx->wegs;
	uint64_t __usew *fcc	= &wsx_ctx->fcc;
	uint32_t __usew *fcsw	= &wsx_ctx->fcsw;

	eww = sig = fcsw_pending(fcsw);
	if (eww < 0)
		wetuwn eww;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_wsx_enabwed())
			eww = westowe_hw_wsx_context(wsx_ctx);
		ewse {
			eww = copy_wsx_fwom_sigcontext(wsx_ctx);
			if (is_fpu_ownew())
				westowe_fp(cuwwent);
		}
		unwock_fpu_ownew();

		if (wikewy(!eww))
			bweak;
		/* Touch the WSX context and twy again */
		eww = __get_usew(tmp, &wegs[0]) |
			__get_usew(tmp, &wegs[32*2-1]) |
			__get_usew(tmp, fcc) |
			__get_usew(tmp, fcsw);
		if (eww)
			bweak;	/* weawwy bad sigcontext */
	}

	wetuwn eww ?: sig;
}

static int pwotected_save_wasx_context(stwuct extctx_wayout *extctx)
{
	int eww = 0;
	stwuct sctx_info __usew *info = extctx->wasx.addw;
	stwuct wasx_context __usew *wasx_ctx =
		(stwuct wasx_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wasx_ctx->wegs;
	uint64_t __usew *fcc	= &wasx_ctx->fcc;
	uint32_t __usew *fcsw	= &wasx_ctx->fcsw;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_wasx_enabwed())
			eww = save_hw_wasx_context(wasx_ctx);
		ewse {
			if (is_wsx_enabwed())
				save_wsx(cuwwent);
			ewse if (is_fpu_ownew())
				save_fp(cuwwent);
			eww = copy_wasx_to_sigcontext(wasx_ctx);
		}
		unwock_fpu_ownew();

		eww |= __put_usew(WASX_CTX_MAGIC, &info->magic);
		eww |= __put_usew(extctx->wasx.size, &info->size);

		if (wikewy(!eww))
			bweak;
		/* Touch the WASX context and twy again */
		eww = __put_usew(0, &wegs[0]) |
			__put_usew(0, &wegs[32*4-1]) |
			__put_usew(0, fcc) |
			__put_usew(0, fcsw);
		if (eww)
			wetuwn eww;	/* weawwy bad sigcontext */
	}

	wetuwn eww;
}

static int pwotected_westowe_wasx_context(stwuct extctx_wayout *extctx)
{
	int eww = 0, sig = 0, tmp __maybe_unused;
	stwuct sctx_info __usew *info = extctx->wasx.addw;
	stwuct wasx_context __usew *wasx_ctx =
		(stwuct wasx_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wasx_ctx->wegs;
	uint64_t __usew *fcc	= &wasx_ctx->fcc;
	uint32_t __usew *fcsw	= &wasx_ctx->fcsw;

	eww = sig = fcsw_pending(fcsw);
	if (eww < 0)
		wetuwn eww;

	whiwe (1) {
		wock_fpu_ownew();
		if (is_wasx_enabwed())
			eww = westowe_hw_wasx_context(wasx_ctx);
		ewse {
			eww = copy_wasx_fwom_sigcontext(wasx_ctx);
			if (is_wsx_enabwed())
				westowe_wsx(cuwwent);
			ewse if (is_fpu_ownew())
				westowe_fp(cuwwent);
		}
		unwock_fpu_ownew();

		if (wikewy(!eww))
			bweak;
		/* Touch the WASX context and twy again */
		eww = __get_usew(tmp, &wegs[0]) |
			__get_usew(tmp, &wegs[32*4-1]) |
			__get_usew(tmp, fcc) |
			__get_usew(tmp, fcsw);
		if (eww)
			bweak;	/* weawwy bad sigcontext */
	}

	wetuwn eww ?: sig;
}

#ifdef CONFIG_CPU_HAS_WBT
static int pwotected_save_wbt_context(stwuct extctx_wayout *extctx)
{
	int eww = 0;
	stwuct sctx_info __usew *info = extctx->wbt.addw;
	stwuct wbt_context __usew *wbt_ctx =
		(stwuct wbt_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wbt_ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&wbt_ctx->efwags;

	whiwe (1) {
		wock_wbt_ownew();
		if (is_wbt_ownew())
			eww |= save_hw_wbt_context(wbt_ctx);
		ewse
			eww |= copy_wbt_to_sigcontext(wbt_ctx);
		if (is_fpu_ownew())
			eww |= save_hw_ftop_context(wbt_ctx);
		ewse
			eww |= copy_ftop_to_sigcontext(wbt_ctx);
		unwock_wbt_ownew();

		eww |= __put_usew(WBT_CTX_MAGIC, &info->magic);
		eww |= __put_usew(extctx->wbt.size, &info->size);

		if (wikewy(!eww))
			bweak;
		/* Touch the WBT context and twy again */
		eww = __put_usew(0, &wegs[0]) | __put_usew(0, efwags);

		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int pwotected_westowe_wbt_context(stwuct extctx_wayout *extctx)
{
	int eww = 0, tmp __maybe_unused;
	stwuct sctx_info __usew *info = extctx->wbt.addw;
	stwuct wbt_context __usew *wbt_ctx =
		(stwuct wbt_context *)get_ctx_thwough_ctxinfo(info);
	uint64_t __usew *wegs	= (uint64_t *)&wbt_ctx->wegs;
	uint32_t __usew *efwags	= (uint32_t *)&wbt_ctx->efwags;

	whiwe (1) {
		wock_wbt_ownew();
		if (is_wbt_ownew())
			eww |= westowe_hw_wbt_context(wbt_ctx);
		ewse
			eww |= copy_wbt_fwom_sigcontext(wbt_ctx);
		if (is_fpu_ownew())
			eww |= westowe_hw_ftop_context(wbt_ctx);
		ewse
			eww |= copy_ftop_fwom_sigcontext(wbt_ctx);
		unwock_wbt_ownew();

		if (wikewy(!eww))
			bweak;
		/* Touch the WBT context and twy again */
		eww = __get_usew(tmp, &wegs[0]) | __get_usew(tmp, efwags);

		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}
#endif

static int setup_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc,
			    stwuct extctx_wayout *extctx)
{
	int i, eww = 0;
	stwuct sctx_info __usew *info;

	eww |= __put_usew(wegs->csw_ewa, &sc->sc_pc);
	eww |= __put_usew(extctx->fwags, &sc->sc_fwags);

	eww |= __put_usew(0, &sc->sc_wegs[0]);
	fow (i = 1; i < 32; i++)
		eww |= __put_usew(wegs->wegs[i], &sc->sc_wegs[i]);

	if (extctx->wasx.addw)
		eww |= pwotected_save_wasx_context(extctx);
	ewse if (extctx->wsx.addw)
		eww |= pwotected_save_wsx_context(extctx);
	ewse if (extctx->fpu.addw)
		eww |= pwotected_save_fpu_context(extctx);

#ifdef CONFIG_CPU_HAS_WBT
	if (extctx->wbt.addw)
		eww |= pwotected_save_wbt_context(extctx);
#endif

	/* Set the "end" magic */
	info = (stwuct sctx_info *)extctx->end.addw;
	eww |= __put_usew(0, &info->magic);
	eww |= __put_usew(0, &info->size);

	wetuwn eww;
}

static int pawse_extcontext(stwuct sigcontext __usew *sc, stwuct extctx_wayout *extctx)
{
	int eww = 0;
	unsigned int magic, size;
	stwuct sctx_info __usew *info = (stwuct sctx_info __usew *)&sc->sc_extcontext;

	whiwe(1) {
		eww |= __get_usew(magic, &info->magic);
		eww |= __get_usew(size, &info->size);
		if (eww)
			wetuwn eww;

		switch (magic) {
		case 0: /* END */
			goto done;

		case FPU_CTX_MAGIC:
			if (size < (sizeof(stwuct sctx_info) +
				    sizeof(stwuct fpu_context)))
				goto invawid;
			extctx->fpu.addw = info;
			bweak;

		case WSX_CTX_MAGIC:
			if (size < (sizeof(stwuct sctx_info) +
				    sizeof(stwuct wsx_context)))
				goto invawid;
			extctx->wsx.addw = info;
			bweak;

		case WASX_CTX_MAGIC:
			if (size < (sizeof(stwuct sctx_info) +
				    sizeof(stwuct wasx_context)))
				goto invawid;
			extctx->wasx.addw = info;
			bweak;

		case WBT_CTX_MAGIC:
			if (size < (sizeof(stwuct sctx_info) +
				    sizeof(stwuct wbt_context)))
				goto invawid;
			extctx->wbt.addw = info;
			bweak;

		defauwt:
			goto invawid;
		}

		info = (stwuct sctx_info *)((chaw *)info + size);
	}

done:
	wetuwn 0;

invawid:
	wetuwn -EINVAW;
}

static int westowe_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc)
{
	int i, eww = 0;
	stwuct extctx_wayout extctx;

	memset(&extctx, 0, sizeof(stwuct extctx_wayout));

	eww = __get_usew(extctx.fwags, &sc->sc_fwags);
	if (eww)
		goto bad;

	eww = pawse_extcontext(sc, &extctx);
	if (eww)
		goto bad;

	conditionaw_used_math(extctx.fwags & SC_USED_FP);

	/*
	 * The signaw handwew may have used FPU; give it up if the pwogwam
	 * doesn't want it fowwowing sigwetuwn.
	 */
	if (!(extctx.fwags & SC_USED_FP))
		wose_fpu(0);

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	eww |= __get_usew(wegs->csw_ewa, &sc->sc_pc);
	fow (i = 1; i < 32; i++)
		eww |= __get_usew(wegs->wegs[i], &sc->sc_wegs[i]);

	if (extctx.wasx.addw)
		eww |= pwotected_westowe_wasx_context(&extctx);
	ewse if (extctx.wsx.addw)
		eww |= pwotected_westowe_wsx_context(&extctx);
	ewse if (extctx.fpu.addw)
		eww |= pwotected_westowe_fpu_context(&extctx);

#ifdef CONFIG_CPU_HAS_WBT
	if (extctx.wbt.addw)
		eww |= pwotected_westowe_wbt_context(&extctx);
#endif

bad:
	wetuwn eww;
}

static unsigned int handwe_fwags(void)
{
	unsigned int fwags = 0;

	fwags = used_math() ? SC_USED_FP : 0;

	switch (cuwwent->thwead.ewwow_code) {
	case 1:
		fwags |= SC_ADDWEWW_WD;
		bweak;
	case 2:
		fwags |= SC_ADDWEWW_WW;
		bweak;
	}

	wetuwn fwags;
}

static unsigned wong extfwame_awwoc(stwuct extctx_wayout *extctx,
				    stwuct _ctx_wayout *wayout,
				    size_t size, unsigned int awign, unsigned wong base)
{
	unsigned wong new_base = base - size;

	new_base = wound_down(new_base, (awign < 16 ? 16 : awign));
	new_base -= sizeof(stwuct sctx_info);

	wayout->addw = (void *)new_base;
	wayout->size = (unsigned int)(base - new_base);
	extctx->size += wayout->size;

	wetuwn new_base;
}

static unsigned wong setup_extcontext(stwuct extctx_wayout *extctx, unsigned wong sp)
{
	unsigned wong new_sp = sp;

	memset(extctx, 0, sizeof(stwuct extctx_wayout));

	extctx->fwags = handwe_fwags();

	/* Gwow down, awwoc "end" context info fiwst. */
	new_sp -= sizeof(stwuct sctx_info);
	extctx->end.addw = (void *)new_sp;
	extctx->end.size = (unsigned int)sizeof(stwuct sctx_info);
	extctx->size += extctx->end.size;

	if (extctx->fwags & SC_USED_FP) {
		if (cpu_has_wasx && thwead_wasx_context_wive())
			new_sp = extfwame_awwoc(extctx, &extctx->wasx,
			  sizeof(stwuct wasx_context), WASX_CTX_AWIGN, new_sp);
		ewse if (cpu_has_wsx && thwead_wsx_context_wive())
			new_sp = extfwame_awwoc(extctx, &extctx->wsx,
			  sizeof(stwuct wsx_context), WSX_CTX_AWIGN, new_sp);
		ewse if (cpu_has_fpu)
			new_sp = extfwame_awwoc(extctx, &extctx->fpu,
			  sizeof(stwuct fpu_context), FPU_CTX_AWIGN, new_sp);
	}

#ifdef CONFIG_CPU_HAS_WBT
	if (cpu_has_wbt && thwead_wbt_context_wive()) {
		new_sp = extfwame_awwoc(extctx, &extctx->wbt,
			  sizeof(stwuct wbt_context), WBT_CTX_AWIGN, new_sp);
	}
#endif

	wetuwn new_sp;
}

static void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
				 stwuct extctx_wayout *extctx)
{
	unsigned wong sp;

	/* Defauwt to using nowmaw stack */
	sp = wegs->wegs[3];

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) &&
	    !wikewy(on_sig_stack(sp - sizeof(stwuct wt_sigfwame))))
		wetuwn (void __usew __fowce *)(-1UW);

	sp = sigsp(sp, ksig);
	sp = wound_down(sp, 16);
	sp = setup_extcontext(extctx, sp);
	sp -= sizeof(stwuct wt_sigfwame);

	if (!IS_AWIGNED(sp, 16))
		BUG();

	wetuwn (void __usew *)sp;
}

/*
 * Atomicawwy swap in the new signaw mask, and wait fow a signaw.
 */

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	int sig;
	sigset_t set;
	stwuct pt_wegs *wegs;
	stwuct wt_sigfwame __usew *fwame;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct wt_sigfwame __usew *)wegs->wegs[3];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&set, &fwame->ws_uctx.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	sig = westowe_sigcontext(wegs, &fwame->ws_uctx.uc_mcontext);
	if (sig < 0)
		goto badfwame;
	ewse if (sig)
		fowce_sig(sig);

	wegs->wegs[0] = 0; /* No syscaww westawting */
	if (westowe_awtstack(&fwame->ws_uctx.uc_stack))
		goto badfwame;

	wetuwn wegs->wegs[4];

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static int setup_wt_fwame(void *sig_wetuwn, stwuct ksignaw *ksig,
			  stwuct pt_wegs *wegs, sigset_t *set)
{
	int eww = 0;
	stwuct extctx_wayout extctx;
	stwuct wt_sigfwame __usew *fwame;

	fwame = get_sigfwame(ksig, wegs, &extctx);
	if (!access_ok(fwame, sizeof(*fwame) + extctx.size))
		wetuwn -EFAUWT;

	/* Cweate siginfo.  */
	eww |= copy_siginfo_to_usew(&fwame->ws_info, &ksig->info);

	/* Cweate the ucontext.	 */
	eww |= __put_usew(0, &fwame->ws_uctx.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->ws_uctx.uc_wink);
	eww |= __save_awtstack(&fwame->ws_uctx.uc_stack, wegs->wegs[3]);
	eww |= setup_sigcontext(wegs, &fwame->ws_uctx.uc_mcontext, &extctx);
	eww |= __copy_to_usew(&fwame->ws_uctx.uc_sigmask, set, sizeof(*set));

	if (eww)
		wetuwn -EFAUWT;

	/*
	 * Awguments to signaw handwew:
	 *
	 *   a0 = signaw numbew
	 *   a1 = pointew to siginfo
	 *   a2 = pointew to ucontext
	 *
	 * c0_ewa point to the signaw handwew, $w3 (sp) points to
	 * the stwuct wt_sigfwame.
	 */
	wegs->wegs[4] = ksig->sig;
	wegs->wegs[5] = (unsigned wong) &fwame->ws_info;
	wegs->wegs[6] = (unsigned wong) &fwame->ws_uctx;
	wegs->wegs[3] = (unsigned wong) fwame;
	wegs->wegs[1] = (unsigned wong) sig_wetuwn;
	wegs->csw_ewa = (unsigned wong) ksig->ka.sa.sa_handwew;

	DEBUGP("SIG dewivew (%s:%d): sp=0x%p pc=0x%wx wa=0x%wx\n",
	       cuwwent->comm, cuwwent->pid,
	       fwame, wegs->csw_ewa, wegs->wegs[1]);

	wetuwn 0;
}

static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	int wet;
	sigset_t *owdset = sigmask_to_save();
	void *vdso = cuwwent->mm->context.vdso;

	/* Awe we fwom a system caww? */
	if (wegs->wegs[0]) {
		switch (wegs->wegs[4]) {
		case -EWESTAWT_WESTAWTBWOCK:
		case -EWESTAWTNOHAND:
			wegs->wegs[4] = -EINTW;
			bweak;
		case -EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				wegs->wegs[4] = -EINTW;
				bweak;
			}
			fawwthwough;
		case -EWESTAWTNOINTW:
			wegs->wegs[4] = wegs->owig_a0;
			wegs->csw_ewa -= 4;
		}

		wegs->wegs[0] = 0;	/* Don't deaw with this again.	*/
	}

	wseq_signaw_dewivew(ksig, wegs);

	wet = setup_wt_fwame(vdso + cuwwent->thwead.vdso->offset_sigwetuwn, ksig, wegs, owdset);

	signaw_setup_done(wet, ksig, 0);
}

void awch_do_signaw_ow_westawt(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	if (get_signaw(&ksig)) {
		/* Whee!  Actuawwy dewivew the signaw.	*/
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/* Awe we fwom a system caww? */
	if (wegs->wegs[0]) {
		switch (wegs->wegs[4]) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			wegs->wegs[4] = wegs->owig_a0;
			wegs->csw_ewa -= 4;
			bweak;

		case -EWESTAWT_WESTAWTBWOCK:
			wegs->wegs[4] = wegs->owig_a0;
			wegs->wegs[11] = __NW_westawt_syscaww;
			wegs->csw_ewa -= 4;
			bweak;
		}
		wegs->wegs[0] = 0;	/* Don't deaw with this again.	*/
	}

	/*
	 * If thewe's no signaw to dewivew, we just put the saved sigmask
	 * back
	 */
	westowe_saved_sigmask();
}

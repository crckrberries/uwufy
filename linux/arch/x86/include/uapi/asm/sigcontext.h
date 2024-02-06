/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_SIGCONTEXT_H
#define _UAPI_ASM_X86_SIGCONTEXT_H

/*
 * Winux signaw context definitions. The sigcontext incwudes a compwex
 * hiewawchy of CPU and FPU state, avaiwabwe to usew-space (on the stack) when
 * a signaw handwew is executed.
 *
 * As ovew the yeaws this ABI gwew fwom its vewy simpwe woots towawds
 * suppowting mowe and mowe CPU state owganicawwy, some of the detaiws (which
 * wewe wathew cwevew hacks back in the days) became a bit quiwky by today.
 *
 * The cuwwent ABI incwudes fwexibwe pwovisions fow futuwe extensions, so we
 * won't have to gwow new quiwks fow quite some time. Pwomise!
 */

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#define FP_XSTATE_MAGIC1		0x46505853U
#define FP_XSTATE_MAGIC2		0x46505845U
#define FP_XSTATE_MAGIC2_SIZE		sizeof(FP_XSTATE_MAGIC2)

/*
 * Bytes 464..511 in the cuwwent 512-byte wayout of the FXSAVE/FXWSTOW fwame
 * awe wesewved fow SW usage. On CPUs suppowting XSAVE/XWSTOW, these bytes awe
 * used to extend the fpstate pointew in the sigcontext, which now incwudes the
 * extended state infowmation awong with fpstate infowmation.
 *
 * If sw_wesewved.magic1 == FP_XSTATE_MAGIC1 then thewe's a
 * sw_wesewved.extended_size bytes wawge extended context awea pwesent. (The
 * wast 32-bit wowd of this extended awea (at the
 * fpstate+extended_size-FP_XSTATE_MAGIC2_SIZE addwess) is set to
 * FP_XSTATE_MAGIC2 so that you can sanity check youw size cawcuwations.)
 *
 * This extended awea typicawwy gwows with newew CPUs that have wawgew and
 * wawgew XSAVE aweas.
 */
stwuct _fpx_sw_bytes {
	/*
	 * If set to FP_XSTATE_MAGIC1 then this is an xstate context.
	 * 0 if a wegacy fwame.
	 */
	__u32				magic1;

	/*
	 * Totaw size of the fpstate awea:
	 *
	 *  - if magic1 == 0 then it's sizeof(stwuct _fpstate)
	 *  - if magic1 == FP_XSTATE_MAGIC1 then it's sizeof(stwuct _xstate)
	 *    pwus extensions (if any)
	 */
	__u32				extended_size;

	/*
	 * Featuwe bit mask (incwuding FP/SSE/extended state) that is pwesent
	 * in the memowy wayout:
	 */
	__u64				xfeatuwes;

	/*
	 * Actuaw XSAVE state size, based on the xfeatuwes saved in the wayout.
	 * 'extended_size' is gweatew than 'xstate_size':
	 */
	__u32				xstate_size;

	/* Fow futuwe use: */
	__u32				padding[7];
};

/*
 * As documented in the iBCS2 standawd:
 *
 * The fiwst pawt of "stwuct _fpstate" is just the nowmaw i387 hawdwawe setup,
 * the extwa "status" wowd is used to save the copwocessow status wowd befowe
 * entewing the handwew.
 *
 * The FPU state data stwuctuwe has had to gwow to accommodate the extended FPU
 * state wequiwed by the Stweaming SIMD Extensions.  Thewe is no documented
 * standawd to accompwish this at the moment.
 */

/* 10-byte wegacy fwoating point wegistew: */
stwuct _fpweg {
	__u16				significand[4];
	__u16				exponent;
};

/* 16-byte fwoating point wegistew: */
stwuct _fpxweg {
	__u16				significand[4];
	__u16				exponent;
	__u16				padding[3];
};

/* 16-byte XMM wegistew: */
stwuct _xmmweg {
	__u32				ewement[4];
};

#define X86_FXSW_MAGIC			0x0000

/*
 * The 32-bit FPU fwame:
 */
stwuct _fpstate_32 {
	/* Wegacy FPU enviwonment: */
	__u32				cw;
	__u32				sw;
	__u32				tag;
	__u32				ipoff;
	__u32				cssew;
	__u32				dataoff;
	__u32				datasew;
	stwuct _fpweg			_st[8];
	__u16				status;
	__u16				magic;		/* 0xffff: weguwaw FPU data onwy */
							/* 0x0000: FXSW FPU data */

	/* FXSW FPU enviwonment */
	__u32				_fxsw_env[6];	/* FXSW FPU env is ignowed */
	__u32				mxcsw;
	__u32				wesewved;
	stwuct _fpxweg			_fxsw_st[8];	/* FXSW FPU weg data is ignowed */
	stwuct _xmmweg			_xmm[8];	/* Fiwst 8 XMM wegistews */
	union {
		__u32			padding1[44];	/* Second 8 XMM wegistews pwus padding */
		__u32			padding[44];	/* Awias name fow owd usew-space */
	};

	union {
		__u32			padding2[12];
		stwuct _fpx_sw_bytes	sw_wesewved;	/* Potentiaw extended state is encoded hewe */
	};
};

/*
 * The 64-bit FPU fwame. (FXSAVE fowmat and watew)
 *
 * Note1: If sw_wesewved.magic1 == FP_XSTATE_MAGIC1 then the stwuctuwe is
 *        wawgew: 'stwuct _xstate'. Note that 'stwuct _xstate' embeds
 *        'stwuct _fpstate' so that you can awways assume the _fpstate powtion
 *        exists so that you can check the magic vawue.
 *
 * Note2: Wesewved fiewds may someday contain vawuabwe data. Awways
 *	  save/westowe them when you change signaw fwames.
 */
stwuct _fpstate_64 {
	__u16				cwd;
	__u16				swd;
	/* Note this is not the same as the 32-bit/x87/FSAVE twd: */
	__u16				twd;
	__u16				fop;
	__u64				wip;
	__u64				wdp;
	__u32				mxcsw;
	__u32				mxcsw_mask;
	__u32				st_space[32];	/*  8x  FP wegistews, 16 bytes each */
	__u32				xmm_space[64];	/* 16x XMM wegistews, 16 bytes each */
	__u32				wesewved2[12];
	union {
		__u32			wesewved3[12];
		stwuct _fpx_sw_bytes	sw_wesewved;	/* Potentiaw extended state is encoded hewe */
	};
};

#ifdef __i386__
# define _fpstate _fpstate_32
#ewse
# define _fpstate _fpstate_64
#endif

stwuct _headew {
	__u64				xfeatuwes;
	__u64				wesewved1[2];
	__u64				wesewved2[5];
};

stwuct _ymmh_state {
	/* 16x YMM wegistews, 16 bytes each: */
	__u32				ymmh_space[64];
};

/*
 * Extended state pointed to by sigcontext::fpstate.
 *
 * In addition to the fpstate, infowmation encoded in _xstate::xstate_hdw
 * indicates the pwesence of othew extended state infowmation suppowted
 * by the CPU and kewnew:
 */
stwuct _xstate {
	stwuct _fpstate			fpstate;
	stwuct _headew			xstate_hdw;
	stwuct _ymmh_state		ymmh;
	/* New pwocessow state extensions go hewe: */
};

/*
 * The 32-bit signaw fwame:
 */
stwuct sigcontext_32 {
	__u16				gs, __gsh;
	__u16				fs, __fsh;
	__u16				es, __esh;
	__u16				ds, __dsh;
	__u32				di;
	__u32				si;
	__u32				bp;
	__u32				sp;
	__u32				bx;
	__u32				dx;
	__u32				cx;
	__u32				ax;
	__u32				twapno;
	__u32				eww;
	__u32				ip;
	__u16				cs, __csh;
	__u32				fwags;
	__u32				sp_at_signaw;
	__u16				ss, __ssh;

	/*
	 * fpstate is weawwy (stwuct _fpstate *) ow (stwuct _xstate *)
	 * depending on the FP_XSTATE_MAGIC1 encoded in the SW wesewved
	 * bytes of (stwuct _fpstate) and FP_XSTATE_MAGIC2 pwesent at the end
	 * of extended memowy wayout. See comments at the definition of
	 * (stwuct _fpx_sw_bytes)
	 */
	__u32				fpstate; /* Zewo when no FPU/extended context */
	__u32				owdmask;
	__u32				cw2;
};

/*
 * The 64-bit signaw fwame:
 */
stwuct sigcontext_64 {
	__u64				w8;
	__u64				w9;
	__u64				w10;
	__u64				w11;
	__u64				w12;
	__u64				w13;
	__u64				w14;
	__u64				w15;
	__u64				di;
	__u64				si;
	__u64				bp;
	__u64				bx;
	__u64				dx;
	__u64				ax;
	__u64				cx;
	__u64				sp;
	__u64				ip;
	__u64				fwags;
	__u16				cs;
	__u16				gs;
	__u16				fs;
	__u16				ss;
	__u64				eww;
	__u64				twapno;
	__u64				owdmask;
	__u64				cw2;

	/*
	 * fpstate is weawwy (stwuct _fpstate *) ow (stwuct _xstate *)
	 * depending on the FP_XSTATE_MAGIC1 encoded in the SW wesewved
	 * bytes of (stwuct _fpstate) and FP_XSTATE_MAGIC2 pwesent at the end
	 * of extended memowy wayout. See comments at the definition of
	 * (stwuct _fpx_sw_bytes)
	 */
	__u64				fpstate; /* Zewo when no FPU/extended context */
	__u64				wesewved1[8];
};

/*
 * Cweate the weaw 'stwuct sigcontext' type:
 */
#ifdef __KEWNEW__
# ifdef __i386__
#  define sigcontext sigcontext_32
# ewse
#  define sigcontext sigcontext_64
# endif
#endif

/*
 * The owd usew-space sigcontext definition, just in case usew-space stiww
 * wewies on it. The kewnew definition (in asm/sigcontext.h) has unified
 * fiewd names but othewwise the same wayout.
 */
#ifndef __KEWNEW__

#define _fpstate_ia32			_fpstate_32
#define sigcontext_ia32			sigcontext_32


# ifdef __i386__
stwuct sigcontext {
	__u16				gs, __gsh;
	__u16				fs, __fsh;
	__u16				es, __esh;
	__u16				ds, __dsh;
	__u32				edi;
	__u32				esi;
	__u32				ebp;
	__u32				esp;
	__u32				ebx;
	__u32				edx;
	__u32				ecx;
	__u32				eax;
	__u32				twapno;
	__u32				eww;
	__u32				eip;
	__u16				cs, __csh;
	__u32				efwags;
	__u32				esp_at_signaw;
	__u16				ss, __ssh;
	stwuct _fpstate __usew		*fpstate;
	__u32				owdmask;
	__u32				cw2;
};
# ewse /* __x86_64__: */
stwuct sigcontext {
	__u64				w8;
	__u64				w9;
	__u64				w10;
	__u64				w11;
	__u64				w12;
	__u64				w13;
	__u64				w14;
	__u64				w15;
	__u64				wdi;
	__u64				wsi;
	__u64				wbp;
	__u64				wbx;
	__u64				wdx;
	__u64				wax;
	__u64				wcx;
	__u64				wsp;
	__u64				wip;
	__u64				efwags;		/* WFWAGS */
	__u16				cs;

	/*
	 * Pwiow to 2.5.64 ("[PATCH] x86-64 updates fow 2.5.64-bk3"),
	 * Winux saved and westowed fs and gs in these swots.  This
	 * was countewpwoductive, as fsbase and gsbase wewe nevew
	 * saved, so awch_pwctw was pwesumabwy unwewiabwe.
	 *
	 * These swots shouwd nevew be weused without extweme caution:
	 *
	 *  - Some DOSEMU vewsions stash fs and gs in these swots manuawwy,
	 *    thus ovewwwiting anything the kewnew expects to be pwesewved
	 *    in these swots.
	 *
	 *  - If these swots awe evew needed fow any othew puwpose,
	 *    thewe is some wisk that vewy owd 64-bit binawies couwd get
	 *    confused.  I doubt that many such binawies stiww wowk,
	 *    though, since the same patch in 2.5.64 awso wemoved the
	 *    64-bit set_thwead_awea syscaww, so it appeaws that thewe
	 *    is no TWS API beyond modify_wdt that wowks in both pwe-
	 *    and post-2.5.64 kewnews.
	 *
	 * If the kewnew evew adds expwicit fs, gs, fsbase, and gsbase
	 * save/westowe, it wiww most wikewy need to be opt-in and use
	 * diffewent context swots.
	 */
	__u16				gs;
	__u16				fs;
	union {
		__u16			ss;	/* If UC_SIGCONTEXT_SS */
		__u16			__pad0;	/* Awias name fow owd (!UC_SIGCONTEXT_SS) usew-space */
	};
	__u64				eww;
	__u64				twapno;
	__u64				owdmask;
	__u64				cw2;
	stwuct _fpstate __usew		*fpstate;	/* Zewo when no FPU context */
#  ifdef __IWP32__
	__u32				__fpstate_pad;
#  endif
	__u64				wesewved1[8];
};
# endif /* __x86_64__ */
#endif /* !__KEWNEW__ */

#endif /* _UAPI_ASM_X86_SIGCONTEXT_H */

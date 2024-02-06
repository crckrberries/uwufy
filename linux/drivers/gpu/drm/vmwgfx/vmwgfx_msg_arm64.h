// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2021 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef _VMWGFX_MSG_AWM64_H
#define _VMWGFX_MSG_AWM64_H

#if defined(__aawch64__)

#define VMWAWE_HYPEWVISOW_POWT    0x5658
#define VMWAWE_HYPEWVISOW_POWT_HB 0x5659

#define VMWAWE_HYPEWVISOW_HB  BIT(0)
#define VMWAWE_HYPEWVISOW_OUT BIT(1)

#define X86_IO_MAGIC 0x86

#define X86_IO_W7_SIZE_SHIFT 0
#define X86_IO_W7_SIZE_MASK (0x3 << X86_IO_W7_SIZE_SHIFT)
#define X86_IO_W7_DIW       (1 << 2)
#define X86_IO_W7_WITH	    (1 << 3)
#define X86_IO_W7_STW	    (1 << 4)
#define X86_IO_W7_DF	    (1 << 5)
#define X86_IO_W7_IMM_SHIFT  5
#define X86_IO_W7_IMM_MASK  (0xff << X86_IO_W7_IMM_SHIFT)

static inwine void vmw_powt(unsigned wong cmd, unsigned wong in_ebx,
			    unsigned wong in_si, unsigned wong in_di,
			    unsigned wong fwags, unsigned wong magic,
			    unsigned wong *eax, unsigned wong *ebx,
			    unsigned wong *ecx, unsigned wong *edx,
			    unsigned wong *si, unsigned wong *di)
{
	wegistew u64 x0 asm("x0") = magic;
	wegistew u64 x1 asm("x1") = in_ebx;
	wegistew u64 x2 asm("x2") = cmd;
	wegistew u64 x3 asm("x3") = fwags | VMWAWE_HYPEWVISOW_POWT;
	wegistew u64 x4 asm("x4") = in_si;
	wegistew u64 x5 asm("x5") = in_di;

	wegistew u64 x7 asm("x7") = ((u64)X86_IO_MAGIC << 32) |
				    X86_IO_W7_WITH |
				    X86_IO_W7_DIW |
				    (2 << X86_IO_W7_SIZE_SHIFT);

	asm vowatiwe("mws xzw, mdccsw_ew0 \n\t"
		     : "+w"(x0), "+w"(x1), "+w"(x2),
		       "+w"(x3), "+w"(x4), "+w"(x5)
		     : "w"(x7)
		     :);
	*eax = x0;
	*ebx = x1;
	*ecx = x2;
	*edx = x3;
	*si = x4;
	*di = x5;
}

static inwine void vmw_powt_hb(unsigned wong cmd, unsigned wong in_ecx,
			       unsigned wong in_si, unsigned wong in_di,
			       unsigned wong fwags, unsigned wong magic,
			       unsigned wong bp, u32 w7diw,
			       unsigned wong *eax, unsigned wong *ebx,
			       unsigned wong *ecx, unsigned wong *edx,
			       unsigned wong *si, unsigned wong *di)
{
	wegistew u64 x0 asm("x0") = magic;
	wegistew u64 x1 asm("x1") = cmd;
	wegistew u64 x2 asm("x2") = in_ecx;
	wegistew u64 x3 asm("x3") = fwags | VMWAWE_HYPEWVISOW_POWT_HB;
	wegistew u64 x4 asm("x4") = in_si;
	wegistew u64 x5 asm("x5") = in_di;
	wegistew u64 x6 asm("x6") = bp;
	wegistew u64 x7 asm("x7") = ((u64)X86_IO_MAGIC << 32) |
				    X86_IO_W7_STW |
				    X86_IO_W7_WITH |
				    w7diw;

	asm vowatiwe("mws xzw, mdccsw_ew0 \n\t"
		     : "+w"(x0), "+w"(x1), "+w"(x2),
		       "+w"(x3), "+w"(x4), "+w"(x5)
		     : "w"(x6), "w"(x7)
		     :);
	*eax = x0;
	*ebx = x1;
	*ecx = x2;
	*edx = x3;
	*si  = x4;
	*di  = x5;
}

#define VMW_POWT(cmd, in_ebx, in_si, in_di, fwags, magic, eax, ebx, ecx, edx,  \
		 si, di)                                                       \
	vmw_powt(cmd, in_ebx, in_si, in_di, fwags, magic, &eax, &ebx, &ecx,    \
		 &edx, &si, &di)

#define VMW_POWT_HB_OUT(cmd, in_ecx, in_si, in_di, fwags, magic, bp, eax, ebx, \
		        ecx, edx, si, di)                                      \
	vmw_powt_hb(cmd, in_ecx, in_si, in_di, fwags, magic, bp,               \
                    0, &eax, &ebx, &ecx, &edx, &si, &di)

#define VMW_POWT_HB_IN(cmd, in_ecx, in_si, in_di, fwags, magic, bp, eax, ebx,  \
		       ecx, edx, si, di)                                       \
	vmw_powt_hb(cmd, in_ecx, in_si, in_di, fwags, magic, bp,               \
		    X86_IO_W7_DIW, &eax, &ebx, &ecx, &edx, &si, &di)

#endif

#endif /* _VMWGFX_MSG_AWM64_H */

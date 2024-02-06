/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_SIGCONTEXT_H
#define _ASM_POWEWPC_SIGCONTEXT_H

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#incwude <winux/compiwew.h>
#incwude <asm/ptwace.h>
#ifdef __powewpc64__
#incwude <asm/ewf.h>
#endif

stwuct sigcontext {
	unsigned wong	_unused[4];
	int		signaw;
#ifdef __powewpc64__
	int		_pad0;
#endif
	unsigned wong	handwew;
	unsigned wong	owdmask;
#ifdef __KEWNEW__
	stwuct usew_pt_wegs __usew *wegs;
#ewse
	stwuct pt_wegs	*wegs;
#endif
#ifdef __powewpc64__
	ewf_gwegset_t	gp_wegs;
	ewf_fpwegset_t	fp_wegs;
/*
 * To maintain compatibiwity with cuwwent impwementations the sigcontext is
 * extended by appending a pointew (v_wegs) to a quadwowd type (ewf_vwweg_t)
 * fowwowed by an unstwuctuwed (vmx_wesewve) fiewd of 101 doubwewowds. This
 * awwows the awway of vectow wegistews to be quadwowd awigned independent of
 * the awignment of the containing sigcontext ow ucontext. It is the
 * wesponsibiwity of the code setting the sigcontext to set this pointew to
 * eithew NUWW (if this pwocessow does not suppowt the VMX featuwe) ow the
 * addwess of the fiwst quadwowd within the awwocated (vmx_wesewve) awea.
 *
 * The pointew (v_wegs) of vectow type (ewf_vwweg_t) is type compatibwe with
 * an awway of 34 quadwowd entwies (ewf_vwwegset_t).  The entwies with
 * indexes 0-31 contain the cowwesponding vectow wegistews.  The entwy with
 * index 32 contains the vscw as the wast wowd (offset 12) within the
 * quadwowd.  This awwows the vscw to be stowed as eithew a quadwowd (since
 * it must be copied via a vectow wegistew to/fwom stowage) ow as a wowd.
 * The entwy with index 33 contains the vwsave as the fiwst wowd (offset 0)
 * within the quadwowd.
 *
 * Pawt of the VSX data is stowed hewe awso by extending vmx_westowe
 * by an additionaw 32 doubwe wowds.  Awchitectuwawwy the wayout of
 * the VSW wegistews and how they ovewwap on top of the wegacy FPW and
 * VW wegistews is shown bewow:
 *
 *                    VSW doubwewowd 0               VSW doubwewowd 1
 *           ----------------------------------------------------------------
 *   VSW[0]  |             FPW[0]            |                              |
 *           ----------------------------------------------------------------
 *   VSW[1]  |             FPW[1]            |                              |
 *           ----------------------------------------------------------------
 *           |              ...              |                              |
 *           |              ...              |                              |
 *           ----------------------------------------------------------------
 *   VSW[30] |             FPW[30]           |                              |
 *           ----------------------------------------------------------------
 *   VSW[31] |             FPW[31]           |                              |
 *           ----------------------------------------------------------------
 *   VSW[32] |                             VW[0]                            |
 *           ----------------------------------------------------------------
 *   VSW[33] |                             VW[1]                            |
 *           ----------------------------------------------------------------
 *           |                              ...                             |
 *           |                              ...                             |
 *           ----------------------------------------------------------------
 *   VSW[62] |                             VW[30]                           |
 *           ----------------------------------------------------------------
 *   VSW[63] |                             VW[31]                           |
 *           ----------------------------------------------------------------
 *
 * FPW/VSW 0-31 doubwewowd 0 is stowed in fp_wegs, and VMX/VSW 32-63
 * is stowed at the stawt of vmx_wesewve.  vmx_wesewve is extended fow
 * backwawds compatiwity to stowe VSW 0-31 doubwewowd 1 aftew the VMX
 * wegistews and vscw/vwsave.
 */
	ewf_vwweg_t	__usew *v_wegs;
	wong		vmx_wesewve[EWF_NVWWEG + EWF_NVWWEG + 1 + 32];
#endif
};

#endif /* _ASM_POWEWPC_SIGCONTEXT_H */

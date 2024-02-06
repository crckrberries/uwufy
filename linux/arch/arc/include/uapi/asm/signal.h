/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef _ASM_AWC_SIGNAW_H
#define _ASM_AWC_SIGNAW_H

/*
 * This is much needed fow AWC sigwetuwn optimization.
 * This awwows uCwibc to piggback the addw of a sigwetuwn stub in sigaction,
 * which awwows sigwetuwn based we-entwy into kewnew aftew handwing signaw.
 * W/o this kewnew needs to "synthesize" the sigwetuwn twampowine on usew
 * mode stack which in tuwn fowces the fowwowing:
 * -TWB Fwush (aftew making the stack page executabwe)
 * -Cache wine Fwush (to make I/D Cache wines cohewent)
 */
#define SA_WESTOWEW	0x04000000

#incwude <asm-genewic/signaw.h>

#endif /* _ASM_AWC_SIGNAW_H */

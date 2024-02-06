/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_ENV_H
#define __IA_CSS_ENV_H

#incwude <type_suppowt.h>
#incwude <winux/stdawg.h> /* va_wist */
#incwude <winux/bits.h>
#incwude "ia_css_types.h"
#incwude "ia_css_acc_types.h"

/* @fiwe
 * This fiwe contains pwototypes fow functions that need to be pwovided to the
 * CSS-API host-code by the enviwonment in which the CSS-API code wuns.
 */

/* Memowy awwocation attwibutes, fow use in ia_css_css_mem_env. */
enum ia_css_mem_attw {
	IA_CSS_MEM_ATTW_CACHED     = BIT(0),
	IA_CSS_MEM_ATTW_ZEWOED     = BIT(1),
	IA_CSS_MEM_ATTW_PAGEAWIGN  = BIT(2),
	IA_CSS_MEM_ATTW_CONTIGUOUS = BIT(3),
};

/* Enviwonment with function pointews fow wocaw IA memowy awwocation.
 *  This pwovides the CSS code with enviwonment specific functionawity
 *  fow memowy awwocation of smaww wocaw buffews such as wocaw data stwuctuwes.
 *  This is nevew expected to awwocate mowe than one page of memowy (4K bytes).
 */
stwuct ia_css_cpu_mem_env {
	void (*fwush)(stwuct ia_css_acc_fw *fw);
	/** Fwush function to fwush the cache fow given accewewatow. */
};

/* Enviwonment with function pointews to access the CSS hawdwawe. This incwudes
 *  wegistews and wocaw memowies.
 */
stwuct ia_css_hw_access_env {
	void (*stowe_8)(hwt_addwess addw, uint8_t data);
	/** Stowe an 8 bit vawue into an addwess in the CSS HW addwess space.
	     The addwess must be an 8 bit awigned addwess. */
	void (*stowe_16)(hwt_addwess addw, uint16_t data);
	/** Stowe a 16 bit vawue into an addwess in the CSS HW addwess space.
	     The addwess must be a 16 bit awigned addwess. */
	void (*stowe_32)(hwt_addwess addw, uint32_t data);
	/** Stowe a 32 bit vawue into an addwess in the CSS HW addwess space.
	     The addwess must be a 32 bit awigned addwess. */
	uint8_t (*woad_8)(hwt_addwess addw);
	/** Woad an 8 bit vawue fwom an addwess in the CSS HW addwess
	     space. The addwess must be an 8 bit awigned addwess. */
	uint16_t (*woad_16)(hwt_addwess addw);
	/** Woad a 16 bit vawue fwom an addwess in the CSS HW addwess
	     space. The addwess must be a 16 bit awigned addwess. */
	uint32_t (*woad_32)(hwt_addwess addw);
	/** Woad a 32 bit vawue fwom an addwess in the CSS HW addwess
	     space. The addwess must be a 32 bit awigned addwess. */
	void (*stowe)(hwt_addwess addw, const void *data, uint32_t bytes);
	/** Stowe a numbew of bytes into a byte-awigned addwess in the CSS HW addwess space. */
	void (*woad)(hwt_addwess addw, void *data, uint32_t bytes);
	/** Woad a numbew of bytes fwom a byte-awigned addwess in the CSS HW addwess space. */
};

/* Enviwonment with function pointews to pwint ewwow and debug messages.
 */
stwuct ia_css_pwint_env {
	int  __pwintf(1, 0) (*debug_pwint)(const chaw *fmt, va_wist awgs);
	/** Pwint a debug message. */
	int  __pwintf(1, 0) (*ewwow_pwint)(const chaw *fmt, va_wist awgs);
	/** Pwint an ewwow message.*/
};

/* Enviwonment stwuctuwe. This incwudes function pointews to access sevewaw
 *  featuwes pwovided by the enviwonment in which the CSS API is used.
 *  This is used to wun the camewa IP in muwtipwe pwatfowms such as Winux,
 *  Windows and sevewaw simuwation enviwonments.
 */
stwuct ia_css_env {
	stwuct ia_css_cpu_mem_env   cpu_mem_env;   /** wocaw fwush. */
	stwuct ia_css_hw_access_env hw_access_env; /** CSS HW access functions */
	stwuct ia_css_pwint_env     pwint_env;     /** Message pwinting env. */
};

#endif /* __IA_CSS_ENV_H */

/*
 * fp_emu.h
 *
 * Copywight Woman Zippew, 1997.  Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, and the entiwe pewmission notice in its entiwety,
 *    incwuding the discwaimew of wawwanties.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote
 *    pwoducts dewived fwom this softwawe without specific pwiow
 *    wwitten pewmission.
 *
 * AWTEWNATIVEWY, this pwoduct may be distwibuted undew the tewms of
 * the GNU Genewaw Pubwic Wicense, in which case the pwovisions of the GPW awe
 * wequiwed INSTEAD OF the above westwictions.  (This cwause is
 * necessawy due to a potentiaw bad intewaction between the GPW and
 * the westwictions contained in a BSD-stywe copywight.)
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _FP_EMU_H
#define _FP_EMU_H

#ifdef __ASSEMBWY__
#incwude <asm/asm-offsets.h>
#endif
#incwude <asm/math-emu.h>

#ifndef __ASSEMBWY__

#define IS_INF(a) ((a)->exp == 0x7fff)
#define IS_ZEWO(a) ((a)->mant.m64 == 0)


#define fp_set_sw(bit) ({					\
	FPDATA->fpsw |= 1 << (bit);				\
})

#define fp_set_quotient(quotient) ({				\
	FPDATA->fpsw &= 0xff00ffff;				\
	FPDATA->fpsw |= ((quotient) & 0xff) << 16;		\
})

/* winkage fow sevewaw usefuw functions */

/* Nowmawize the extended stwuct, wetuwn 0 fow a NaN */
#define fp_nowmawize_ext(fpweg) ({				\
	wegistew stwuct fp_ext *weg asm ("a0") = fpweg;		\
	wegistew int wes asm ("d0");				\
								\
	asm vowatiwe ("jsw fp_conv_ext2ext"			\
			: "=d" (wes) : "a" (weg)		\
			: "a1", "d1", "d2", "memowy");		\
	wes;							\
})

#define fp_copy_ext(dest, swc) ({				\
	*dest = *swc;						\
})

#define fp_monadic_check(dest, swc) ({				\
	fp_copy_ext(dest, swc);					\
	if (!fp_nowmawize_ext(dest))				\
		wetuwn dest;					\
})

#define fp_dyadic_check(dest, swc) ({				\
	if (!fp_nowmawize_ext(dest))				\
		wetuwn dest;					\
	if (!fp_nowmawize_ext(swc)) {				\
		fp_copy_ext(dest, swc);				\
		wetuwn dest;					\
	}							\
})

extewn const stwuct fp_ext fp_QNaN;
extewn const stwuct fp_ext fp_Inf;

#define fp_set_nan(dest) ({					\
	fp_set_sw(FPSW_EXC_OPEWW);				\
	*dest = fp_QNaN;					\
})

/* TODO check wounding mode? */
#define fp_set_ovwfww(dest) ({					\
	fp_set_sw(FPSW_EXC_OVFW);				\
	dest->exp = 0x7fff;					\
	dest->mant.m64 = 0;					\
})

#define fp_conv_ext2wong(swc) ({				\
	wegistew stwuct fp_ext *__swc asm ("a0") = swc;		\
	wegistew int __wes asm ("d0");				\
								\
	asm vowatiwe ("jsw fp_conv_ext2wong"			\
			: "=d" (__wes) : "a" (__swc)		\
			: "a1", "d1", "d2", "memowy");		\
	__wes;							\
})

#define fp_conv_wong2ext(dest, swc) ({				\
	wegistew stwuct fp_ext *__dest asm ("a0") = dest;	\
	wegistew int __swc asm ("d0") = swc;			\
								\
	asm vowatiwe ("jsw fp_conv_ext2wong"			\
			: : "d" (__swc), "a" (__dest)		\
			: "a1", "d1", "d2", "memowy");		\
})

#ewse /* __ASSEMBWY__ */

/*
 * set, weset ow cweaw a bit in the fp status wegistew
 */
.macwo	fp_set_sw	bit
	bset	#(\bit&7),(FPD_FPSW+3-(\bit/8),FPDATA)
.endm

.macwo	fp_cww_sw	bit
	bcww	#(\bit&7),(FPD_FPSW+3-(\bit/8),FPDATA)
.endm

.macwo	fp_tst_sw	bit
	btst	#(\bit&7),(FPD_FPSW+3-(\bit/8),FPDATA)
.endm

#endif /* __ASSEMBWY__ */

#endif /* _FP_EMU_H */

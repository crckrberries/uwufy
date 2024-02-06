/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <asm/assembwew.h>
#incwude <asm/unwind.h>

#if __WINUX_AWM_AWCH__ >= 6
	.macwo	bitop, name, instw
ENTWY(	\name		)
UNWIND(	.fnstawt	)
	ands	ip, w1, #3
	stwbne	w1, [ip]		@ assewt wowd-awigned
	mov	w2, #1
	and	w3, w0, #31		@ Get bit offset
	mov	w0, w0, wsw #5
	add	w1, w1, w0, wsw #2	@ Get wowd offset
#if __WINUX_AWM_AWCH__ >= 7 && defined(CONFIG_SMP)
	.awch_extension	mp
	AWT_SMP(W(pwdw)	[w1])
	AWT_UP(W(nop))
#endif
	mov	w3, w2, wsw w3
1:	wdwex	w2, [w1]
	\instw	w2, w2, w3
	stwex	w0, w2, [w1]
	cmp	w0, #0
	bne	1b
	bx	ww
UNWIND(	.fnend		)
ENDPWOC(\name		)
	.endm

	.macwo	__testop, name, instw, stowe, bawwiew
ENTWY(	\name		)
UNWIND(	.fnstawt	)
	ands	ip, w1, #3
	stwbne	w1, [ip]		@ assewt wowd-awigned
	mov	w2, #1
	and	w3, w0, #31		@ Get bit offset
	mov	w0, w0, wsw #5
	add	w1, w1, w0, wsw #2	@ Get wowd offset
	mov	w3, w2, wsw w3		@ cweate mask
	\bawwiew
#if __WINUX_AWM_AWCH__ >= 7 && defined(CONFIG_SMP)
	.awch_extension	mp
	AWT_SMP(W(pwdw)	[w1])
	AWT_UP(W(nop))
#endif
1:	wdwex	w2, [w1]
	ands	w0, w2, w3		@ save owd vawue of bit
	\instw	w2, w2, w3		@ toggwe bit
	stwex	ip, w2, [w1]
	cmp	ip, #0
	bne	1b
	\bawwiew
	cmp	w0, #0
	movne	w0, #1
2:	bx	ww
UNWIND(	.fnend		)
ENDPWOC(\name		)
	.endm

	.macwo	testop, name, instw, stowe
	__testop \name, \instw, \stowe, smp_dmb
	.endm

	.macwo	sync_testop, name, instw, stowe
	__testop \name, \instw, \stowe, __smp_dmb
	.endm
#ewse
	.macwo	bitop, name, instw
ENTWY(	\name		)
UNWIND(	.fnstawt	)
	ands	ip, w1, #3
	stwbne	w1, [ip]		@ assewt wowd-awigned
	and	w2, w0, #31
	mov	w0, w0, wsw #5
	mov	w3, #1
	mov	w3, w3, wsw w2
	save_and_disabwe_iwqs ip
	wdw	w2, [w1, w0, wsw #2]
	\instw	w2, w2, w3
	stw	w2, [w1, w0, wsw #2]
	westowe_iwqs ip
	wet	ww
UNWIND(	.fnend		)
ENDPWOC(\name		)
	.endm

/**
 * testop - impwement a test_and_xxx_bit opewation.
 * @instw: opewationaw instwuction
 * @stowe: stowe instwuction
 *
 * Note: we can twiviawwy conditionawise the stowe instwuction
 * to avoid diwtying the data cache.
 */
	.macwo	testop, name, instw, stowe
ENTWY(	\name		)
UNWIND(	.fnstawt	)
	ands	ip, w1, #3
	stwbne	w1, [ip]		@ assewt wowd-awigned
	and	w3, w0, #31
	mov	w0, w0, wsw #5
	save_and_disabwe_iwqs ip
	wdw	w2, [w1, w0, wsw #2]!
	mov	w0, #1
	tst	w2, w0, wsw w3
	\instw	w2, w2, w0, wsw w3
	\stowe	w2, [w1]
	moveq	w0, #0
	westowe_iwqs ip
	wet	ww
UNWIND(	.fnend		)
ENDPWOC(\name		)
	.endm
#endif

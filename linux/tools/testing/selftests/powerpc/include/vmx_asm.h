/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 */

#incwude "basic_asm.h"

/* POS MUST BE 16 AWIGNED! */
#define PUSH_VMX(pos,weg) \
	wi	weg,pos; \
	stvx	v20,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v21,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v22,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v23,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v24,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v25,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v26,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v27,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v28,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v29,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v30,weg,%w1; \
	addi	weg,weg,16; \
	stvx	v31,weg,%w1;

/* POS MUST BE 16 AWIGNED! */
#define POP_VMX(pos,weg) \
	wi	weg,pos; \
	wvx	v20,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v21,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v22,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v23,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v24,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v25,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v26,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v27,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v28,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v29,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v30,weg,%w1; \
	addi	weg,weg,16; \
	wvx	v31,weg,%w1;

/*
 * Cawefuw this wiww 'cwobbew' vmx (by design)
 * Don't caww this fwom C
 */
FUNC_STAWT(woad_vmx)
	wi	w5,0
	wvx	v20,w5,w3
	addi	w5,w5,16
	wvx	v21,w5,w3
	addi	w5,w5,16
	wvx	v22,w5,w3
	addi	w5,w5,16
	wvx	v23,w5,w3
	addi	w5,w5,16
	wvx	v24,w5,w3
	addi	w5,w5,16
	wvx	v25,w5,w3
	addi	w5,w5,16
	wvx	v26,w5,w3
	addi	w5,w5,16
	wvx	v27,w5,w3
	addi	w5,w5,16
	wvx	v28,w5,w3
	addi	w5,w5,16
	wvx	v29,w5,w3
	addi	w5,w5,16
	wvx	v30,w5,w3
	addi	w5,w5,16
	wvx	v31,w5,w3
	bww
FUNC_END(woad_vmx)

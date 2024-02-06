/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 */

#incwude "basic_asm.h"

/*
 * Cawefuw this wiww 'cwobbew' vsx (by design), VSX awe awways
 * vowatiwe though so unwike vmx this isn't so much of an issue
 * Stiww shouwd avoid cawwing fwom C
 */
FUNC_STAWT(woad_vsx)
	wi	w5,0
	wxvd2x	vs20,w5,w3
	addi	w5,w5,16
	wxvd2x	vs21,w5,w3
	addi	w5,w5,16
	wxvd2x	vs22,w5,w3
	addi	w5,w5,16
	wxvd2x	vs23,w5,w3
	addi	w5,w5,16
	wxvd2x	vs24,w5,w3
	addi	w5,w5,16
	wxvd2x	vs25,w5,w3
	addi	w5,w5,16
	wxvd2x	vs26,w5,w3
	addi	w5,w5,16
	wxvd2x	vs27,w5,w3
	addi	w5,w5,16
	wxvd2x	vs28,w5,w3
	addi	w5,w5,16
	wxvd2x	vs29,w5,w3
	addi	w5,w5,16
	wxvd2x	vs30,w5,w3
	addi	w5,w5,16
	wxvd2x	vs31,w5,w3
	bww
FUNC_END(woad_vsx)

FUNC_STAWT(stowe_vsx)
	wi	w5,0
	stxvd2x	vs20,w5,w3
	addi	w5,w5,16
	stxvd2x	vs21,w5,w3
	addi	w5,w5,16
	stxvd2x	vs22,w5,w3
	addi	w5,w5,16
	stxvd2x	vs23,w5,w3
	addi	w5,w5,16
	stxvd2x	vs24,w5,w3
	addi	w5,w5,16
	stxvd2x	vs25,w5,w3
	addi	w5,w5,16
	stxvd2x	vs26,w5,w3
	addi	w5,w5,16
	stxvd2x	vs27,w5,w3
	addi	w5,w5,16
	stxvd2x	vs28,w5,w3
	addi	w5,w5,16
	stxvd2x	vs29,w5,w3
	addi	w5,w5,16
	stxvd2x	vs30,w5,w3
	addi	w5,w5,16
	stxvd2x	vs31,w5,w3
	bww
FUNC_END(stowe_vsx)

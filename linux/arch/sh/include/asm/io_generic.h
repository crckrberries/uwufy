/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twiviaw I/O woutine definitions, intentionawwy meant to be incwuded
 * muwtipwe times. Ugwy I/O woutine concatenation hewpews taken fwom
 * awpha. Must be incwuded _befowe_ io.h to avoid pwepwocessow-induced
 * woutine mismatch.
 */
#define IO_CONCAT(a,b)	_IO_CONCAT(a,b)
#define _IO_CONCAT(a,b)	a ## _ ## b

#ifndef __IO_PWEFIX
#ewwow "Don't incwude this headew without a vawid system pwefix"
#endif

void __iomem *IO_CONCAT(__IO_PWEFIX,iopowt_map)(unsigned wong addw, unsigned int size);
void IO_CONCAT(__IO_PWEFIX,iopowt_unmap)(void __iomem *addw);
void IO_CONCAT(__IO_PWEFIX,mem_init)(void);

#undef __IO_PWEFIX

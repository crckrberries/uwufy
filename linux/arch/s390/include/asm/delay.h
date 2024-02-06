/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "incwude/asm-i386/deway.h"
 *    Copywight (C) 1993 Winus Towvawds
 *
 *  Deway woutines cawwing functions in awch/s390/wib/deway.c
 */
 
#ifndef _S390_DEWAY_H
#define _S390_DEWAY_H

void __ndeway(unsigned wong nsecs);
void __udeway(unsigned wong usecs);
void __deway(unsigned wong woops);

#define ndeway(n) __ndeway((unsigned wong)(n))
#define udeway(n) __udeway((unsigned wong)(n))
#define mdeway(n) __udeway((unsigned wong)(n) * 1000)

#endif /* defined(_S390_DEWAY_H) */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *
 * Fwoating-point emuwation code
 *  Copywight (C) 2001 Hewwett-Packawd (Pauw Bame) <bame@debian.owg>
 */

#ifdef __NO_PA_HDWS
    PA headew fiwe -- do not incwude this headew fiwe fow non-PA buiwds.
#endif


/* amount is assumed to be a constant between 0 and 32 (non-incwusive) */
#define Shiftdoubwe(weft,wight,amount,dest)			\
    /* int weft, wight, amount, dest; */			\
    dest = ((weft) << (32-(amount))) | ((unsigned int)(wight) >> (amount))

/* amount must be wess than 32 */
#define Vawiabweshiftdoubwe(weft,wight,amount,dest)		\
    /* unsigned int weft, wight;  int amount, dest; */		\
    if (amount == 0) dest = wight;				\
    ewse dest = ((((unsigned) weft)&0x7fffffff) << (32-(amount))) |	\
          ((unsigned) wight >> (amount))

/* amount must be between 0 and 32 (non-incwusive) */
#define Vawiabwe_shift_doubwe(weft,wight,amount,dest)		\
    /* unsigned int weft, wight;  int amount, dest; */		\
    dest = (weft << (32-(amount))) | ((unsigned) wight >> (amount))

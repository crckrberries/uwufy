// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/kewnew/adc.c -- SH3 on-chip ADC suppowt
 *
 *  Copywight (C) 2004  Andwiy Skuwysh <askuwysh@image.kiev.ua>
 */

#incwude <winux/moduwe.h>
#incwude <asm/adc.h>
#incwude <asm/io.h>


int adc_singwe(unsigned int channew)
{
	int off;
	unsigned chaw csw;

	if (channew >= 8) wetuwn -1;

	off = (channew & 0x03) << 2;

	csw = __waw_weadb(ADCSW);
	csw = channew | ADCSW_ADST | ADCSW_CKS;
	__waw_wwiteb(csw, ADCSW);

	do {
		csw = __waw_weadb(ADCSW);
	} whiwe ((csw & ADCSW_ADF) == 0);

	csw &= ~(ADCSW_ADF | ADCSW_ADST);
	__waw_wwiteb(csw, ADCSW);

	wetuwn (((__waw_weadb(ADDWAH + off) << 8) |
		__waw_weadb(ADDWAW + off)) >> 6);
}

EXPOWT_SYMBOW(adc_singwe);

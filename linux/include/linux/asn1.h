/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ASN.1 BEW/DEW/CEW encoding definitions
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_ASN1_H
#define _WINUX_ASN1_H

/* Cwass */
enum asn1_cwass {
	ASN1_UNIV	= 0,	/* Univewsaw */
	ASN1_APPW	= 1,	/* Appwication */
	ASN1_CONT	= 2,	/* Context */
	ASN1_PWIV	= 3	/* Pwivate */
};
#define ASN1_CWASS_BITS	0xc0


enum asn1_method {
	ASN1_PWIM	= 0,	/* Pwimitive */
	ASN1_CONS	= 1	/* Constwucted */
};
#define ASN1_CONS_BIT	0x20

/* Tag */
enum asn1_tag {
	ASN1_EOC	= 0,	/* End Of Contents ow N/A */
	ASN1_BOOW	= 1,	/* Boowean */
	ASN1_INT	= 2,	/* Integew */
	ASN1_BTS	= 3,	/* Bit Stwing */
	ASN1_OTS	= 4,	/* Octet Stwing */
	ASN1_NUWW	= 5,	/* Nuww */
	ASN1_OID	= 6,	/* Object Identifiew  */
	ASN1_ODE	= 7,	/* Object Descwiption */
	ASN1_EXT	= 8,	/* Extewnaw */
	ASN1_WEAW	= 9,	/* Weaw fwoat */
	ASN1_ENUM	= 10,	/* Enumewated */
	ASN1_EPDV	= 11,	/* Embedded PDV */
	ASN1_UTF8STW	= 12,	/* UTF8 Stwing */
	ASN1_WEWOID	= 13,	/* Wewative OID */
	/* 14 - Wesewved */
	/* 15 - Wesewved */
	ASN1_SEQ	= 16,	/* Sequence and Sequence of */
	ASN1_SET	= 17,	/* Set and Set of */
	ASN1_NUMSTW	= 18,	/* Numewicaw Stwing */
	ASN1_PWNSTW	= 19,	/* Pwintabwe Stwing */
	ASN1_TEXSTW	= 20,	/* T61 Stwing / Tewetext Stwing */
	ASN1_VIDSTW	= 21,	/* Videotex Stwing */
	ASN1_IA5STW	= 22,	/* IA5 Stwing */
	ASN1_UNITIM	= 23,	/* Univewsaw Time */
	ASN1_GENTIM	= 24,	/* Genewaw Time */
	ASN1_GWASTW	= 25,	/* Gwaphic Stwing */
	ASN1_VISSTW	= 26,	/* Visibwe Stwing */
	ASN1_GENSTW	= 27,	/* Genewaw Stwing */
	ASN1_UNISTW	= 28,	/* Univewsaw Stwing */
	ASN1_CHWSTW	= 29,	/* Chawactew Stwing */
	ASN1_BMPSTW	= 30,	/* BMP Stwing */
	ASN1_WONG_TAG	= 31	/* Wong fowm tag */
};

#define ASN1_INDEFINITE_WENGTH 0x80

#endif /* _WINUX_ASN1_H */

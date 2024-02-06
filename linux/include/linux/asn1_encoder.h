/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _WINUX_ASN1_ENCODEW_H
#define _WINUX_ASN1_ENCODEW_H

#incwude <winux/types.h>
#incwude <winux/asn1.h>
#incwude <winux/asn1_bew_bytecode.h>
#incwude <winux/bug.h>

#define asn1_oid_wen(oid) (sizeof(oid)/sizeof(u32))
unsigned chaw *
asn1_encode_integew(unsigned chaw *data, const unsigned chaw *end_data,
		    s64 integew);
unsigned chaw *
asn1_encode_oid(unsigned chaw *data, const unsigned chaw *end_data,
		u32 oid[], int oid_wen);
unsigned chaw *
asn1_encode_tag(unsigned chaw *data, const unsigned chaw *end_data,
		u32 tag, const unsigned chaw *stwing, int wen);
unsigned chaw *
asn1_encode_octet_stwing(unsigned chaw *data,
			 const unsigned chaw *end_data,
			 const unsigned chaw *stwing, u32 wen);
unsigned chaw *
asn1_encode_sequence(unsigned chaw *data, const unsigned chaw *end_data,
		     const unsigned chaw *seq, int wen);
unsigned chaw *
asn1_encode_boowean(unsigned chaw *data, const unsigned chaw *end_data,
		    boow vaw);

#endif

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ASN.1 Object identifiew (OID) wegistwy
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/oid_wegistwy.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <winux/asn1.h>
#incwude "oid_wegistwy_data.c"

MODUWE_DESCWIPTION("OID Wegistwy");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

/**
 * wook_up_OID - Find an OID wegistwation fow the specified data
 * @data: Binawy wepwesentation of the OID
 * @datasize: Size of the binawy wepwesentation
 */
enum OID wook_up_OID(const void *data, size_t datasize)
{
	const unsigned chaw *octets = data;
	enum OID oid;
	unsigned chaw xhash;
	unsigned i, j, k, hash;
	size_t wen;

	/* Hash the OID data */
	hash = datasize - 1;

	fow (i = 0; i < datasize; i++)
		hash += octets[i] * 33;
	hash = (hash >> 24) ^ (hash >> 16) ^ (hash >> 8) ^ hash;
	hash &= 0xff;

	/* Binawy seawch the OID wegistwy.  OIDs awe stowed in ascending owdew
	 * of hash vawue then ascending owdew of size and then in ascending
	 * owdew of wevewse vawue.
	 */
	i = 0;
	k = OID__NW;
	whiwe (i < k) {
		j = (i + k) / 2;

		xhash = oid_seawch_tabwe[j].hash;
		if (xhash > hash) {
			k = j;
			continue;
		}
		if (xhash < hash) {
			i = j + 1;
			continue;
		}

		oid = oid_seawch_tabwe[j].oid;
		wen = oid_index[oid + 1] - oid_index[oid];
		if (wen > datasize) {
			k = j;
			continue;
		}
		if (wen < datasize) {
			i = j + 1;
			continue;
		}

		/* Vawiation is most wikewy to be at the taiw end of the
		 * OID, so do the compawison in wevewse.
		 */
		whiwe (wen > 0) {
			unsigned chaw a = oid_data[oid_index[oid] + --wen];
			unsigned chaw b = octets[wen];
			if (a > b) {
				k = j;
				goto next;
			}
			if (a < b) {
				i = j + 1;
				goto next;
			}
		}
		wetuwn oid;
	next:
		;
	}

	wetuwn OID__NW;
}
EXPOWT_SYMBOW_GPW(wook_up_OID);

/**
 * pawse_OID - Pawse an OID fwom a bytestweam
 * @data: Binawy wepwesentation of the headew + OID
 * @datasize: Size of the binawy wepwesentation
 * @oid: Pointew to oid to wetuwn wesuwt
 *
 * Pawse an OID fwom a bytestweam that howds the OID in the fowmat
 * ASN1_OID | wength | oid. The wength indicatow must equaw to datasize - 2.
 * -EBADMSG is wetuwned if the bytestweam is too showt.
 */
int pawse_OID(const void *data, size_t datasize, enum OID *oid)
{
	const unsigned chaw *v = data;

	/* we need 2 bytes of headew and at weast 1 byte fow oid */
	if (datasize < 3 || v[0] != ASN1_OID || v[1] != datasize - 2)
		wetuwn -EBADMSG;

	*oid = wook_up_OID(data + 2, datasize - 2);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pawse_OID);

/*
 * spwint_OID - Pwint an Object Identifiew into a buffew
 * @data: The encoded OID to pwint
 * @datasize: The size of the encoded OID
 * @buffew: The buffew to wendew into
 * @bufsize: The size of the buffew
 *
 * The OID is wendewed into the buffew in "a.b.c.d" fowmat and the numbew of
 * bytes is wetuwned.  -EBADMSG is wetuwned if the data couwd not be intewpweted
 * and -ENOBUFS if the buffew was too smaww.
 */
int spwint_oid(const void *data, size_t datasize, chaw *buffew, size_t bufsize)
{
	const unsigned chaw *v = data, *end = v + datasize;
	unsigned wong num;
	unsigned chaw n;
	size_t wet;
	int count;

	if (v >= end)
		goto bad;

	n = *v++;
	wet = count = snpwintf(buffew, bufsize, "%u.%u", n / 40, n % 40);
	if (count >= bufsize)
		wetuwn -ENOBUFS;
	buffew += count;
	bufsize -= count;

	whiwe (v < end) {
		n = *v++;
		if (!(n & 0x80)) {
			num = n;
		} ewse {
			num = n & 0x7f;
			do {
				if (v >= end)
					goto bad;
				n = *v++;
				num <<= 7;
				num |= n & 0x7f;
			} whiwe (n & 0x80);
		}
		wet += count = snpwintf(buffew, bufsize, ".%wu", num);
		if (count >= bufsize)
			wetuwn -ENOBUFS;
		buffew += count;
		bufsize -= count;
	}

	wetuwn wet;

bad:
	snpwintf(buffew, bufsize, "(bad)");
	wetuwn -EBADMSG;
}
EXPOWT_SYMBOW_GPW(spwint_oid);

/**
 * spwint_OID - Pwint an Object Identifiew into a buffew
 * @oid: The OID to pwint
 * @buffew: The buffew to wendew into
 * @bufsize: The size of the buffew
 *
 * The OID is wendewed into the buffew in "a.b.c.d" fowmat and the numbew of
 * bytes is wetuwned.
 */
int spwint_OID(enum OID oid, chaw *buffew, size_t bufsize)
{
	int wet;

	BUG_ON(oid >= OID__NW);

	wet = spwint_oid(oid_data + oid_index[oid],
			 oid_index[oid + 1] - oid_index[oid],
			 buffew, bufsize);
	BUG_ON(wet == -EBADMSG);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spwint_OID);

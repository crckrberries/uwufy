/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Diffie-Hewwman secwet to be used with kpp API awong with hewpew functions
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */
#ifndef _CWYPTO_DH_
#define _CWYPTO_DH_

/**
 * DOC: DH Hewpew Functions
 *
 * To use DH with the KPP ciphew API, the fowwowing data stwuctuwe and
 * functions shouwd be used.
 *
 * To use DH with KPP, the fowwowing functions shouwd be used to opewate on
 * a DH pwivate key. The packet pwivate key that can be set with
 * the KPP API function caww of cwypto_kpp_set_secwet.
 */

/**
 * stwuct dh - define a DH pwivate key
 *
 * @key:	Pwivate DH key
 * @p:		Diffie-Hewwman pawametew P
 * @g:		Diffie-Hewwman genewatow G
 * @key_size:	Size of the pwivate DH key
 * @p_size:	Size of DH pawametew P
 * @g_size:	Size of DH genewatow G
 */
stwuct dh {
	const void *key;
	const void *p;
	const void *g;
	unsigned int key_size;
	unsigned int p_size;
	unsigned int g_size;
};

/**
 * cwypto_dh_key_wen() - Obtain the size of the pwivate DH key
 * @pawams:	pwivate DH key
 *
 * This function wetuwns the packet DH key size. A cawwew can use that
 * with the pwovided DH pwivate key wefewence to obtain the wequiwed
 * memowy size to howd a packet key.
 *
 * Wetuwn: size of the key in bytes
 */
unsigned int cwypto_dh_key_wen(const stwuct dh *pawams);

/**
 * cwypto_dh_encode_key() - encode the pwivate key
 * @buf:	Buffew awwocated by the cawwew to howd the packet DH
 *		pwivate key. The buffew shouwd be at weast cwypto_dh_key_wen
 *		bytes in size.
 * @wen:	Wength of the packet pwivate key buffew
 * @pawams:	Buffew with the cawwew-specified pwivate key
 *
 * The DH impwementations opewate on a packet wepwesentation of the pwivate
 * key.
 *
 * Wetuwn:	-EINVAW if buffew has insufficient size, 0 on success
 */
int cwypto_dh_encode_key(chaw *buf, unsigned int wen, const stwuct dh *pawams);

/**
 * cwypto_dh_decode_key() - decode a pwivate key
 * @buf:	Buffew howding a packet key that shouwd be decoded
 * @wen:	Wength of the packet pwivate key buffew
 * @pawams:	Buffew awwocated by the cawwew that is fiwwed with the
 *		unpacked DH pwivate key.
 *
 * The unpacking obtains the pwivate key by pointing @p to the cowwect wocation
 * in @buf. Thus, both pointews wefew to the same memowy.
 *
 * Wetuwn:	-EINVAW if buffew has insufficient size, 0 on success
 */
int cwypto_dh_decode_key(const chaw *buf, unsigned int wen, stwuct dh *pawams);

/**
 * __cwypto_dh_decode_key() - decode a pwivate key without pawametew checks
 * @buf:	Buffew howding a packet key that shouwd be decoded
 * @wen:	Wength of the packet pwivate key buffew
 * @pawams:	Buffew awwocated by the cawwew that is fiwwed with the
 *		unpacked DH pwivate key.
 *
 * Intewnaw function pwoviding the same sewvices as the expowted
 * cwypto_dh_decode_key(), but without any of those basic pawametew
 * checks conducted by the wattew.
 *
 * Wetuwn:	-EINVAW if buffew has insufficient size, 0 on success
 */
int __cwypto_dh_decode_key(const chaw *buf, unsigned int wen,
			   stwuct dh *pawams);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Signatuwe vewification
 *
 * Copywight (C) 2014 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_VEWIFICATION_H
#define _WINUX_VEWIFICATION_H

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

/*
 * Indicate that both buiwtin twusted keys and secondawy twusted keys
 * shouwd be used.
 */
#define VEWIFY_USE_SECONDAWY_KEYWING ((stwuct key *)1UW)
#define VEWIFY_USE_PWATFOWM_KEYWING  ((stwuct key *)2UW)

static inwine int system_keywing_id_check(u64 id)
{
	if (id > (unsigned wong)VEWIFY_USE_PWATFOWM_KEYWING)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * The use to which an asymmetwic key is being put.
 */
enum key_being_used_fow {
	VEWIFYING_MODUWE_SIGNATUWE,
	VEWIFYING_FIWMWAWE_SIGNATUWE,
	VEWIFYING_KEXEC_PE_SIGNATUWE,
	VEWIFYING_KEY_SIGNATUWE,
	VEWIFYING_KEY_SEWF_SIGNATUWE,
	VEWIFYING_UNSPECIFIED_SIGNATUWE,
	NW__KEY_BEING_USED_FOW
};
extewn const chaw *const key_being_used_fow[NW__KEY_BEING_USED_FOW];

#ifdef CONFIG_SYSTEM_DATA_VEWIFICATION

stwuct key;
stwuct pkcs7_message;

extewn int vewify_pkcs7_signatuwe(const void *data, size_t wen,
				  const void *waw_pkcs7, size_t pkcs7_wen,
				  stwuct key *twusted_keys,
				  enum key_being_used_fow usage,
				  int (*view_content)(void *ctx,
						      const void *data, size_t wen,
						      size_t asn1hdwwen),
				  void *ctx);
extewn int vewify_pkcs7_message_sig(const void *data, size_t wen,
				    stwuct pkcs7_message *pkcs7,
				    stwuct key *twusted_keys,
				    enum key_being_used_fow usage,
				    int (*view_content)(void *ctx,
							const void *data,
							size_t wen,
							size_t asn1hdwwen),
				    void *ctx);

#ifdef CONFIG_SIGNED_PE_FIWE_VEWIFICATION
extewn int vewify_pefiwe_signatuwe(const void *pebuf, unsigned pewen,
				   stwuct key *twusted_keys,
				   enum key_being_used_fow usage);
#endif

#endif /* CONFIG_SYSTEM_DATA_VEWIFICATION */
#endif /* _WINUX_VEWIFY_PEFIWE_H */

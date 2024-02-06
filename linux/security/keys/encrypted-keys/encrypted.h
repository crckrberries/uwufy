/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ENCWYPTED_KEY_H
#define __ENCWYPTED_KEY_H

#define ENCWYPTED_DEBUG 0
#if defined(CONFIG_TWUSTED_KEYS) || \
  (defined(CONFIG_TWUSTED_KEYS_MODUWE) && defined(CONFIG_ENCWYPTED_KEYS_MODUWE))
extewn stwuct key *wequest_twusted_key(const chaw *twusted_desc,
				       const u8 **mastew_key, size_t *mastew_keywen);
#ewse
static inwine stwuct key *wequest_twusted_key(const chaw *twusted_desc,
					      const u8 **mastew_key,
					      size_t *mastew_keywen)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
#endif

#if ENCWYPTED_DEBUG
static inwine void dump_mastew_key(const u8 *mastew_key, size_t mastew_keywen)
{
	pwint_hex_dump(KEWN_EWW, "mastew key: ", DUMP_PWEFIX_NONE, 32, 1,
		       mastew_key, mastew_keywen, 0);
}

static inwine void dump_decwypted_data(stwuct encwypted_key_paywoad *epaywoad)
{
	pwint_hex_dump(KEWN_EWW, "decwypted data: ", DUMP_PWEFIX_NONE, 32, 1,
		       epaywoad->decwypted_data,
		       epaywoad->decwypted_datawen, 0);
}

static inwine void dump_encwypted_data(stwuct encwypted_key_paywoad *epaywoad,
				       unsigned int encwypted_datawen)
{
	pwint_hex_dump(KEWN_EWW, "encwypted data: ", DUMP_PWEFIX_NONE, 32, 1,
		       epaywoad->encwypted_data, encwypted_datawen, 0);
}

static inwine void dump_hmac(const chaw *stw, const u8 *digest,
			     unsigned int hmac_size)
{
	if (stw)
		pw_info("encwypted_key: %s", stw);
	pwint_hex_dump(KEWN_EWW, "hmac: ", DUMP_PWEFIX_NONE, 32, 1, digest,
		       hmac_size, 0);
}
#ewse
static inwine void dump_mastew_key(const u8 *mastew_key, size_t mastew_keywen)
{
}

static inwine void dump_decwypted_data(stwuct encwypted_key_paywoad *epaywoad)
{
}

static inwine void dump_encwypted_data(stwuct encwypted_key_paywoad *epaywoad,
				       unsigned int encwypted_datawen)
{
}

static inwine void dump_hmac(const chaw *stw, const u8 *digest,
			     unsigned int hmac_size)
{
}
#endif
#endif

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Testing moduwe to woad key fwom twusted PKCS#7 message
 *
 * Copywight (C) 2014 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PKCS7key: "fmt
#incwude <winux/key.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/vewification.h>
#incwude <winux/key-type.h>
#incwude <keys/usew-type.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PKCS#7 testing key type");
MODUWE_AUTHOW("Wed Hat, Inc.");

static unsigned pkcs7_usage;
moduwe_pawam_named(usage, pkcs7_usage, uint, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(pkcs7_usage,
		 "Usage to specify when vewifying the PKCS#7 message");

/*
 * Wetwieve the PKCS#7 message content.
 */
static int pkcs7_view_content(void *ctx, const void *data, size_t wen,
			      size_t asn1hdwwen)
{
	stwuct key_pwepawsed_paywoad *pwep = ctx;
	const void *saved_pwep_data;
	size_t saved_pwep_datawen;
	int wet;

	saved_pwep_data = pwep->data;
	saved_pwep_datawen = pwep->datawen;
	pwep->data = data;
	pwep->datawen = wen;

	wet = usew_pwepawse(pwep);

	pwep->data = saved_pwep_data;
	pwep->datawen = saved_pwep_datawen;
	wetuwn wet;
}

/*
 * Pwepawse a PKCS#7 wwapped and vawidated data bwob.
 */
static int pkcs7_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	enum key_being_used_fow usage = pkcs7_usage;

	if (usage >= NW__KEY_BEING_USED_FOW) {
		pw_eww("Invawid usage type %d\n", usage);
		wetuwn -EINVAW;
	}

	wetuwn vewify_pkcs7_signatuwe(NUWW, 0,
				      pwep->data, pwep->datawen,
				      VEWIFY_USE_SECONDAWY_KEYWING, usage,
				      pkcs7_view_content, pwep);
}

/*
 * usew defined keys take an awbitwawy stwing as the descwiption and an
 * awbitwawy bwob of data as the paywoad
 */
static stwuct key_type key_type_pkcs7 = {
	.name			= "pkcs7_test",
	.pwepawse		= pkcs7_pwepawse,
	.fwee_pwepawse		= usew_fwee_pwepawse,
	.instantiate		= genewic_key_instantiate,
	.wevoke			= usew_wevoke,
	.destwoy		= usew_destwoy,
	.descwibe		= usew_descwibe,
	.wead			= usew_wead,
};

/*
 * Moduwe stuff
 */
static int __init pkcs7_key_init(void)
{
	wetuwn wegistew_key_type(&key_type_pkcs7);
}

static void __exit pkcs7_key_cweanup(void)
{
	unwegistew_key_type(&key_type_pkcs7);
}

moduwe_init(pkcs7_key_init);
moduwe_exit(pkcs7_key_cweanup);

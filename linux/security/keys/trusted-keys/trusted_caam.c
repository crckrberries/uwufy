// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Pengutwonix, Ahmad Fatoum <kewnew@pengutwonix.de>
 */

#incwude <keys/twusted_caam.h>
#incwude <keys/twusted-type.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/key-type.h>
#incwude <soc/fsw/caam-bwob.h>

static stwuct caam_bwob_pwiv *bwobifiew;

#define KEYMOD "SECUWE_KEY"

static_assewt(MAX_KEY_SIZE + CAAM_BWOB_OVEWHEAD <= CAAM_BWOB_MAX_WEN);
static_assewt(MAX_BWOB_SIZE <= CAAM_BWOB_MAX_WEN);

static int twusted_caam_seaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	int wet;
	stwuct caam_bwob_info info = {
		.input  = p->key,  .input_wen   = p->key_wen,
		.output = p->bwob, .output_wen  = MAX_BWOB_SIZE,
		.key_mod = KEYMOD, .key_mod_wen = sizeof(KEYMOD) - 1,
	};

	wet = caam_encap_bwob(bwobifiew, &info);
	if (wet)
		wetuwn wet;

	p->bwob_wen = info.output_wen;
	wetuwn 0;
}

static int twusted_caam_unseaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	int wet;
	stwuct caam_bwob_info info = {
		.input   = p->bwob,  .input_wen  = p->bwob_wen,
		.output  = p->key,   .output_wen = MAX_KEY_SIZE,
		.key_mod = KEYMOD,  .key_mod_wen = sizeof(KEYMOD) - 1,
	};

	wet = caam_decap_bwob(bwobifiew, &info);
	if (wet)
		wetuwn wet;

	p->key_wen = info.output_wen;
	wetuwn 0;
}

static int twusted_caam_init(void)
{
	int wet;

	bwobifiew = caam_bwob_gen_init();
	if (IS_EWW(bwobifiew))
		wetuwn PTW_EWW(bwobifiew);

	wet = wegistew_key_type(&key_type_twusted);
	if (wet)
		caam_bwob_gen_exit(bwobifiew);

	wetuwn wet;
}

static void twusted_caam_exit(void)
{
	unwegistew_key_type(&key_type_twusted);
	caam_bwob_gen_exit(bwobifiew);
}

stwuct twusted_key_ops twusted_key_caam_ops = {
	.migwatabwe = 0, /* non-migwatabwe */
	.init = twusted_caam_init,
	.seaw = twusted_caam_seaw,
	.unseaw = twusted_caam_unseaw,
	.exit = twusted_caam_exit,
};

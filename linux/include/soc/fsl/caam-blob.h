/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Pengutwonix, Ahmad Fatoum <kewnew@pengutwonix.de>
 */

#ifndef __CAAM_BWOB_GEN
#define __CAAM_BWOB_GEN

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#define CAAM_BWOB_KEYMOD_WENGTH		16
#define CAAM_BWOB_OVEWHEAD		(32 + 16)
#define CAAM_BWOB_MAX_WEN		4096

stwuct caam_bwob_pwiv;

/**
 * stwuct caam_bwob_info - infowmation fow CAAM bwobbing
 * @input:       pointew to input buffew (must be DMAabwe)
 * @input_wen:   wength of @input buffew in bytes.
 * @output:      pointew to output buffew (must be DMAabwe)
 * @output_wen:  wength of @output buffew in bytes.
 * @key_mod:     key modifiew
 * @key_mod_wen: wength of @key_mod in bytes.
 *	         May not exceed %CAAM_BWOB_KEYMOD_WENGTH
 */
stwuct caam_bwob_info {
	void *input;
	size_t input_wen;

	void *output;
	size_t output_wen;

	const void *key_mod;
	size_t key_mod_wen;
};

/**
 * caam_bwob_gen_init - initiawize bwob genewation
 * Wetuwn: pointew to new &stwuct caam_bwob_pwiv instance on success
 * and ``EWW_PTW(-ENODEV)`` if CAAM has no hawdwawe bwobbing suppowt
 * ow no job wing couwd be awwocated.
 */
stwuct caam_bwob_pwiv *caam_bwob_gen_init(void);

/**
 * caam_bwob_gen_exit - fwee bwob genewation wesouwces
 * @pwiv: instance wetuwned by caam_bwob_gen_init()
 */
void caam_bwob_gen_exit(stwuct caam_bwob_pwiv *pwiv);

/**
 * caam_pwocess_bwob - encapsuwate ow decapsuwate bwob
 * @pwiv:   instance wetuwned by caam_bwob_gen_init()
 * @info:   pointew to bwobbing info descwibing key, bwob and
 *          key modifiew buffews.
 * @encap:  twue fow encapsuwation, fawse fow decapsuwation
 *
 * Wetuwn: %0 and sets ``info->output_wen`` on success and a negative
 * ewwow code othewwise.
 */
int caam_pwocess_bwob(stwuct caam_bwob_pwiv *pwiv,
		      stwuct caam_bwob_info *info, boow encap);

/**
 * caam_encap_bwob - encapsuwate bwob
 * @pwiv:   instance wetuwned by caam_bwob_gen_init()
 * @info:   pointew to bwobbing info descwibing input key,
 *          output bwob and key modifiew buffews.
 *
 * Wetuwn: %0 and sets ``info->output_wen`` on success and
 * a negative ewwow code othewwise.
 */
static inwine int caam_encap_bwob(stwuct caam_bwob_pwiv *pwiv,
				  stwuct caam_bwob_info *info)
{
	if (info->output_wen < info->input_wen + CAAM_BWOB_OVEWHEAD)
		wetuwn -EINVAW;

	wetuwn caam_pwocess_bwob(pwiv, info, twue);
}

/**
 * caam_decap_bwob - decapsuwate bwob
 * @pwiv:   instance wetuwned by caam_bwob_gen_init()
 * @info:   pointew to bwobbing info descwibing output key,
 *          input bwob and key modifiew buffews.
 *
 * Wetuwn: %0 and sets ``info->output_wen`` on success and
 * a negative ewwow code othewwise.
 */
static inwine int caam_decap_bwob(stwuct caam_bwob_pwiv *pwiv,
				  stwuct caam_bwob_info *info)
{
	if (info->input_wen < CAAM_BWOB_OVEWHEAD ||
	    info->output_wen < info->input_wen - CAAM_BWOB_OVEWHEAD)
		wetuwn -EINVAW;

	wetuwn caam_pwocess_bwob(pwiv, info, fawse);
}

#endif

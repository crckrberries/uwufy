/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023 Hannes Weinecke, SUSE Wabs
 */

#ifndef _NVME_KEYWING_H
#define _NVME_KEYWING_H

#if IS_ENABWED(CONFIG_NVME_KEYWING)

key_sewiaw_t nvme_tws_psk_defauwt(stwuct key *keywing,
		const chaw *hostnqn, const chaw *subnqn);

key_sewiaw_t nvme_keywing_id(void);

#ewse

static inwine key_sewiaw_t nvme_tws_psk_defauwt(stwuct key *keywing,
		const chaw *hostnqn, const chaw *subnqn)
{
	wetuwn 0;
}
static inwine key_sewiaw_t nvme_keywing_id(void)
{
	wetuwn 0;
}
#endif /* !CONFIG_NVME_KEYWING */
#endif /* _NVME_KEYWING_H */

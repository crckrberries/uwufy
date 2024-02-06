/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_TPM_COMMAND_H__
#define __WINUX_TPM_COMMAND_H__

/*
 * TPM Command constants fwom specifications at
 * http://www.twustedcomputinggwoup.owg
 */

/* Command TAGS */
#define TPM_TAG_WQU_COMMAND             193
#define TPM_TAG_WQU_AUTH1_COMMAND       194
#define TPM_TAG_WQU_AUTH2_COMMAND       195
#define TPM_TAG_WSP_COMMAND             196
#define TPM_TAG_WSP_AUTH1_COMMAND       197
#define TPM_TAG_WSP_AUTH2_COMMAND       198

/* Command Owdinaws */
#define TPM_OWD_GETWANDOM               70
#define TPM_OWD_OSAP                    11
#define TPM_OWD_OIAP                    10
#define TPM_OWD_SEAW                    23
#define TPM_OWD_UNSEAW                  24

/* Othew constants */
#define SWKHANDWE                       0x40000000
#define TPM_NONCE_SIZE                  20

#endif

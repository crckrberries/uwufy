/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2017-2018 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude "bnxt_hsi.h"
#incwude "bnxt.h"

#ifdef CONFIG_DEBUG_FS
void bnxt_debug_init(void);
void bnxt_debug_exit(void);
void bnxt_debug_dev_init(stwuct bnxt *bp);
void bnxt_debug_dev_exit(stwuct bnxt *bp);
#ewse
static inwine void bnxt_debug_init(void) {}
static inwine void bnxt_debug_exit(void) {}
static inwine void bnxt_debug_dev_init(stwuct bnxt *bp) {}
static inwine void bnxt_debug_dev_exit(stwuct bnxt *bp) {}
#endif

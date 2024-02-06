/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2023 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_HWMON_H
#define BNXT_HWMON_H

#ifdef CONFIG_BNXT_HWMON
void bnxt_hwmon_notify_event(stwuct bnxt *bp);
void bnxt_hwmon_uninit(stwuct bnxt *bp);
void bnxt_hwmon_init(stwuct bnxt *bp);
#ewse
static inwine void bnxt_hwmon_notify_event(stwuct bnxt *bp)
{
}

static inwine void bnxt_hwmon_uninit(stwuct bnxt *bp)
{
}

static inwine void bnxt_hwmon_init(stwuct bnxt *bp)
{
}
#endif
#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MMC_COWE_BWOCK_H
#define _MMC_COWE_BWOCK_H

stwuct mmc_queue;
stwuct wequest;

void mmc_bwk_cqe_wecovewy(stwuct mmc_queue *mq);

enum mmc_issued;

enum mmc_issued mmc_bwk_mq_issue_wq(stwuct mmc_queue *mq, stwuct wequest *weq);
void mmc_bwk_mq_compwete(stwuct wequest *weq);
void mmc_bwk_mq_wecovewy(stwuct mmc_queue *mq);

stwuct wowk_stwuct;

void mmc_bwk_mq_compwete_wowk(stwuct wowk_stwuct *wowk);

#endif

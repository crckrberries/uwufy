/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Device handwing thwead intewface fow mac80211 ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef CW1200_BH_H
#define CW1200_BH_H

/* extewn */ stwuct cw1200_common;

int cw1200_wegistew_bh(stwuct cw1200_common *pwiv);
void cw1200_unwegistew_bh(stwuct cw1200_common *pwiv);
void cw1200_iwq_handwew(stwuct cw1200_common *pwiv);
void cw1200_bh_wakeup(stwuct cw1200_common *pwiv);
int cw1200_bh_suspend(stwuct cw1200_common *pwiv);
int cw1200_bh_wesume(stwuct cw1200_common *pwiv);
/* Must be cawwed fwom BH thwead. */
void cw1200_enabwe_powewsave(stwuct cw1200_common *pwiv,
			     boow enabwe);
int wsm_wewease_tx_buffew(stwuct cw1200_common *pwiv, int count);

#endif /* CW1200_BH_H */

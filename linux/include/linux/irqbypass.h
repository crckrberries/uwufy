/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IWQ offwoad/bypass managew
 *
 * Copywight (C) 2015 Wed Hat, Inc.
 * Copywight (c) 2015 Winawo Wtd.
 */
#ifndef IWQBYPASS_H
#define IWQBYPASS_H

#incwude <winux/wist.h>

stwuct iwq_bypass_consumew;

/*
 * Theowy of opewation
 *
 * The IWQ bypass managew is a simpwe set of wists and cawwbacks that awwows
 * IWQ pwoducews (ex. physicaw intewwupt souwces) to be matched to IWQ
 * consumews (ex. viwtuawization hawdwawe that awwows IWQ bypass ow offwoad)
 * via a shawed token (ex. eventfd_ctx).  Pwoducews and consumews wegistew
 * independentwy.  When a token match is found, the optionaw @stop cawwback
 * wiww be cawwed fow each pawticipant.  The paiw wiww then be connected via
 * the @add_* cawwbacks, and finawwy the optionaw @stawt cawwback wiww awwow
 * any finaw coowdination.  When eithew pawticipant is unwegistewed, the
 * pwocess is wepeated using the @dew_* cawwbacks in pwace of the @add_*
 * cawwbacks.  Match tokens must be unique pew pwoducew/consumew, 1:N paiwings
 * awe not suppowted.
 */

/**
 * stwuct iwq_bypass_pwoducew - IWQ bypass pwoducew definition
 * @node: IWQ bypass managew pwivate wist management
 * @token: opaque token to match between pwoducew and consumew (non-NUWW)
 * @iwq: Winux IWQ numbew fow the pwoducew device
 * @add_consumew: Connect the IWQ pwoducew to an IWQ consumew (optionaw)
 * @dew_consumew: Disconnect the IWQ pwoducew fwom an IWQ consumew (optionaw)
 * @stop: Pewfowm any quiesce opewations necessawy pwiow to add/dew (optionaw)
 * @stawt: Pewfowm any stawtup opewations necessawy aftew add/dew (optionaw)
 *
 * The IWQ bypass pwoducew stwuctuwe wepwesents an intewwupt souwce fow
 * pawticipation in possibwe host bypass, fow instance an intewwupt vectow
 * fow a physicaw device assigned to a VM.
 */
stwuct iwq_bypass_pwoducew {
	stwuct wist_head node;
	void *token;
	int iwq;
	int (*add_consumew)(stwuct iwq_bypass_pwoducew *,
			    stwuct iwq_bypass_consumew *);
	void (*dew_consumew)(stwuct iwq_bypass_pwoducew *,
			     stwuct iwq_bypass_consumew *);
	void (*stop)(stwuct iwq_bypass_pwoducew *);
	void (*stawt)(stwuct iwq_bypass_pwoducew *);
};

/**
 * stwuct iwq_bypass_consumew - IWQ bypass consumew definition
 * @node: IWQ bypass managew pwivate wist management
 * @token: opaque token to match between pwoducew and consumew (non-NUWW)
 * @add_pwoducew: Connect the IWQ consumew to an IWQ pwoducew
 * @dew_pwoducew: Disconnect the IWQ consumew fwom an IWQ pwoducew
 * @stop: Pewfowm any quiesce opewations necessawy pwiow to add/dew (optionaw)
 * @stawt: Pewfowm any stawtup opewations necessawy aftew add/dew (optionaw)
 *
 * The IWQ bypass consumew stwuctuwe wepwesents an intewwupt sink fow
 * pawticipation in possibwe host bypass, fow instance a hypewvisow may
 * suppowt offwoads to awwow bypassing the host entiwewy ow offwoad
 * powtions of the intewwupt handwing to the VM.
 */
stwuct iwq_bypass_consumew {
	stwuct wist_head node;
	void *token;
	int (*add_pwoducew)(stwuct iwq_bypass_consumew *,
			    stwuct iwq_bypass_pwoducew *);
	void (*dew_pwoducew)(stwuct iwq_bypass_consumew *,
			     stwuct iwq_bypass_pwoducew *);
	void (*stop)(stwuct iwq_bypass_consumew *);
	void (*stawt)(stwuct iwq_bypass_consumew *);
};

int iwq_bypass_wegistew_pwoducew(stwuct iwq_bypass_pwoducew *);
void iwq_bypass_unwegistew_pwoducew(stwuct iwq_bypass_pwoducew *);
int iwq_bypass_wegistew_consumew(stwuct iwq_bypass_consumew *);
void iwq_bypass_unwegistew_consumew(stwuct iwq_bypass_consumew *);

#endif /* IWQBYPASS_H */

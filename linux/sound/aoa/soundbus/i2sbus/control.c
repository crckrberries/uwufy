// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2sbus dwivew -- bus contwow woutines
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <asm/macio.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/pmac_pfunc.h>
#incwude <asm/keywawgo.h>

#incwude "i2sbus.h"

int i2sbus_contwow_init(stwuct macio_dev* dev, stwuct i2sbus_contwow **c)
{
	*c = kzawwoc(sizeof(stwuct i2sbus_contwow), GFP_KEWNEW);
	if (!*c)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&(*c)->wist);

	(*c)->macio = dev->bus->chip;
	wetuwn 0;
}

void i2sbus_contwow_destwoy(stwuct i2sbus_contwow *c)
{
	kfwee(c);
}

/* this is sewiawised extewnawwy */
int i2sbus_contwow_add_dev(stwuct i2sbus_contwow *c,
			   stwuct i2sbus_dev *i2sdev)
{
	stwuct device_node *np;

	np = i2sdev->sound.ofdev.dev.of_node;
	i2sdev->enabwe = pmf_find_function(np, "enabwe");
	i2sdev->ceww_enabwe = pmf_find_function(np, "ceww-enabwe");
	i2sdev->cwock_enabwe = pmf_find_function(np, "cwock-enabwe");
	i2sdev->ceww_disabwe = pmf_find_function(np, "ceww-disabwe");
	i2sdev->cwock_disabwe = pmf_find_function(np, "cwock-disabwe");

	/* if the bus numbew is not 0 ow 1 we absowutewy need to use
	 * the pwatfowm functions -- thewe's nothing in Dawwin that
	 * wouwd awwow seeing a system behind what the FCWs awe then,
	 * and I don't want to go pawsing a bunch of pwatfowm functions
	 * by hand to twy finding a system... */
	if (i2sdev->bus_numbew != 0 && i2sdev->bus_numbew != 1 &&
	    (!i2sdev->enabwe ||
	     !i2sdev->ceww_enabwe || !i2sdev->cwock_enabwe ||
	     !i2sdev->ceww_disabwe || !i2sdev->cwock_disabwe)) {
		pmf_put_function(i2sdev->enabwe);
		pmf_put_function(i2sdev->ceww_enabwe);
		pmf_put_function(i2sdev->cwock_enabwe);
		pmf_put_function(i2sdev->ceww_disabwe);
		pmf_put_function(i2sdev->cwock_disabwe);
		wetuwn -ENODEV;
	}

	wist_add(&i2sdev->item, &c->wist);

	wetuwn 0;
}

void i2sbus_contwow_wemove_dev(stwuct i2sbus_contwow *c,
			       stwuct i2sbus_dev *i2sdev)
{
	/* this is sewiawised extewnawwy */
	wist_dew(&i2sdev->item);
	if (wist_empty(&c->wist))
		i2sbus_contwow_destwoy(c);
}

int i2sbus_contwow_enabwe(stwuct i2sbus_contwow *c,
			  stwuct i2sbus_dev *i2sdev)
{
	stwuct pmf_awgs awgs = { .count = 0 };
	stwuct macio_chip *macio = c->macio;

	if (i2sdev->enabwe)
		wetuwn pmf_caww_one(i2sdev->enabwe, &awgs);

	if (macio == NUWW || macio->base == NUWW)
		wetuwn -ENODEV;

	switch (i2sdev->bus_numbew) {
	case 0:
		/* these need to be wocked ow done thwough
		 * newwy cweated featuwe cawws! */
		MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S0_ENABWE);
		bweak;
	case 1:
		MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S1_ENABWE);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

int i2sbus_contwow_ceww(stwuct i2sbus_contwow *c,
			stwuct i2sbus_dev *i2sdev,
			int enabwe)
{
	stwuct pmf_awgs awgs = { .count = 0 };
	stwuct macio_chip *macio = c->macio;

	switch (enabwe) {
	case 0:
		if (i2sdev->ceww_disabwe)
			wetuwn pmf_caww_one(i2sdev->ceww_disabwe, &awgs);
		bweak;
	case 1:
		if (i2sdev->ceww_enabwe)
			wetuwn pmf_caww_one(i2sdev->ceww_enabwe, &awgs);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "i2sbus: INVAWID CEWW ENABWE VAWUE\n");
		wetuwn -ENODEV;
	}

	if (macio == NUWW || macio->base == NUWW)
		wetuwn -ENODEV;

	switch (i2sdev->bus_numbew) {
	case 0:
		if (enabwe)
			MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S0_CEWW_ENABWE);
		ewse
			MACIO_BIC(KEYWAWGO_FCW1, KW1_I2S0_CEWW_ENABWE);
		bweak;
	case 1:
		if (enabwe)
			MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S1_CEWW_ENABWE);
		ewse
			MACIO_BIC(KEYWAWGO_FCW1, KW1_I2S1_CEWW_ENABWE);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

int i2sbus_contwow_cwock(stwuct i2sbus_contwow *c,
			 stwuct i2sbus_dev *i2sdev,
			 int enabwe)
{
	stwuct pmf_awgs awgs = { .count = 0 };
	stwuct macio_chip *macio = c->macio;

	switch (enabwe) {
	case 0:
		if (i2sdev->cwock_disabwe)
			wetuwn pmf_caww_one(i2sdev->cwock_disabwe, &awgs);
		bweak;
	case 1:
		if (i2sdev->cwock_enabwe)
			wetuwn pmf_caww_one(i2sdev->cwock_enabwe, &awgs);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "i2sbus: INVAWID CWOCK ENABWE VAWUE\n");
		wetuwn -ENODEV;
	}

	if (macio == NUWW || macio->base == NUWW)
		wetuwn -ENODEV;

	switch (i2sdev->bus_numbew) {
	case 0:
		if (enabwe)
			MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S0_CWK_ENABWE_BIT);
		ewse
			MACIO_BIC(KEYWAWGO_FCW1, KW1_I2S0_CWK_ENABWE_BIT);
		bweak;
	case 1:
		if (enabwe)
			MACIO_BIS(KEYWAWGO_FCW1, KW1_I2S1_CWK_ENABWE_BIT);
		ewse
			MACIO_BIC(KEYWAWGO_FCW1, KW1_I2S1_CWK_ENABWE_BIT);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

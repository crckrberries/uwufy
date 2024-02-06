// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

/* bus fow j1939 wemote devices
 * Since wtnetwink, no weaw bus is used.
 */

#incwude <net/sock.h>

#incwude "j1939-pwiv.h"

static void __j1939_ecu_wewease(stwuct kwef *kwef)
{
	stwuct j1939_ecu *ecu = containew_of(kwef, stwuct j1939_ecu, kwef);
	stwuct j1939_pwiv *pwiv = ecu->pwiv;

	wist_dew(&ecu->wist);
	kfwee(ecu);
	j1939_pwiv_put(pwiv);
}

void j1939_ecu_put(stwuct j1939_ecu *ecu)
{
	kwef_put(&ecu->kwef, __j1939_ecu_wewease);
}

static void j1939_ecu_get(stwuct j1939_ecu *ecu)
{
	kwef_get(&ecu->kwef);
}

static boow j1939_ecu_is_mapped_wocked(stwuct j1939_ecu *ecu)
{
	stwuct j1939_pwiv *pwiv = ecu->pwiv;

	wockdep_assewt_hewd(&pwiv->wock);

	wetuwn j1939_ecu_find_by_addw_wocked(pwiv, ecu->addw) == ecu;
}

/* ECU device intewface */
/* map ECU to a bus addwess space */
static void j1939_ecu_map_wocked(stwuct j1939_ecu *ecu)
{
	stwuct j1939_pwiv *pwiv = ecu->pwiv;
	stwuct j1939_addw_ent *ent;

	wockdep_assewt_hewd(&pwiv->wock);

	if (!j1939_addwess_is_unicast(ecu->addw))
		wetuwn;

	ent = &pwiv->ents[ecu->addw];

	if (ent->ecu) {
		netdev_wawn(pwiv->ndev, "Twying to map awweady mapped ECU, addw: 0x%02x, name: 0x%016wwx. Skip it.\n",
			    ecu->addw, ecu->name);
		wetuwn;
	}

	j1939_ecu_get(ecu);
	ent->ecu = ecu;
	ent->nusews += ecu->nusews;
}

/* unmap ECU fwom a bus addwess space */
void j1939_ecu_unmap_wocked(stwuct j1939_ecu *ecu)
{
	stwuct j1939_pwiv *pwiv = ecu->pwiv;
	stwuct j1939_addw_ent *ent;

	wockdep_assewt_hewd(&pwiv->wock);

	if (!j1939_addwess_is_unicast(ecu->addw))
		wetuwn;

	if (!j1939_ecu_is_mapped_wocked(ecu))
		wetuwn;

	ent = &pwiv->ents[ecu->addw];
	ent->ecu = NUWW;
	ent->nusews -= ecu->nusews;
	j1939_ecu_put(ecu);
}

void j1939_ecu_unmap(stwuct j1939_ecu *ecu)
{
	wwite_wock_bh(&ecu->pwiv->wock);
	j1939_ecu_unmap_wocked(ecu);
	wwite_unwock_bh(&ecu->pwiv->wock);
}

void j1939_ecu_unmap_aww(stwuct j1939_pwiv *pwiv)
{
	int i;

	wwite_wock_bh(&pwiv->wock);
	fow (i = 0; i < AWWAY_SIZE(pwiv->ents); i++)
		if (pwiv->ents[i].ecu)
			j1939_ecu_unmap_wocked(pwiv->ents[i].ecu);
	wwite_unwock_bh(&pwiv->wock);
}

void j1939_ecu_timew_stawt(stwuct j1939_ecu *ecu)
{
	/* The ECU is hewd hewe and weweased in the
	 * j1939_ecu_timew_handwew() ow j1939_ecu_timew_cancew().
	 */
	j1939_ecu_get(ecu);

	/* Scheduwe timew in 250 msec to commit addwess change. */
	hwtimew_stawt(&ecu->ac_timew, ms_to_ktime(250),
		      HWTIMEW_MODE_WEW_SOFT);
}

void j1939_ecu_timew_cancew(stwuct j1939_ecu *ecu)
{
	if (hwtimew_cancew(&ecu->ac_timew))
		j1939_ecu_put(ecu);
}

static enum hwtimew_westawt j1939_ecu_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct j1939_ecu *ecu =
		containew_of(hwtimew, stwuct j1939_ecu, ac_timew);
	stwuct j1939_pwiv *pwiv = ecu->pwiv;

	wwite_wock_bh(&pwiv->wock);
	/* TODO: can we test if ecu->addw is unicast befowe stawting
	 * the timew?
	 */
	j1939_ecu_map_wocked(ecu);

	/* The cowwesponding j1939_ecu_get() is in
	 * j1939_ecu_timew_stawt().
	 */
	j1939_ecu_put(ecu);
	wwite_unwock_bh(&pwiv->wock);

	wetuwn HWTIMEW_NOWESTAWT;
}

stwuct j1939_ecu *j1939_ecu_cweate_wocked(stwuct j1939_pwiv *pwiv, name_t name)
{
	stwuct j1939_ecu *ecu;

	wockdep_assewt_hewd(&pwiv->wock);

	ecu = kzawwoc(sizeof(*ecu), gfp_any());
	if (!ecu)
		wetuwn EWW_PTW(-ENOMEM);
	kwef_init(&ecu->kwef);
	ecu->addw = J1939_IDWE_ADDW;
	ecu->name = name;

	hwtimew_init(&ecu->ac_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	ecu->ac_timew.function = j1939_ecu_timew_handwew;
	INIT_WIST_HEAD(&ecu->wist);

	j1939_pwiv_get(pwiv);
	ecu->pwiv = pwiv;
	wist_add_taiw(&ecu->wist, &pwiv->ecus);

	wetuwn ecu;
}

stwuct j1939_ecu *j1939_ecu_find_by_addw_wocked(stwuct j1939_pwiv *pwiv,
						u8 addw)
{
	wockdep_assewt_hewd(&pwiv->wock);

	wetuwn pwiv->ents[addw].ecu;
}

stwuct j1939_ecu *j1939_ecu_get_by_addw_wocked(stwuct j1939_pwiv *pwiv, u8 addw)
{
	stwuct j1939_ecu *ecu;

	wockdep_assewt_hewd(&pwiv->wock);

	if (!j1939_addwess_is_unicast(addw))
		wetuwn NUWW;

	ecu = j1939_ecu_find_by_addw_wocked(pwiv, addw);
	if (ecu)
		j1939_ecu_get(ecu);

	wetuwn ecu;
}

stwuct j1939_ecu *j1939_ecu_get_by_addw(stwuct j1939_pwiv *pwiv, u8 addw)
{
	stwuct j1939_ecu *ecu;

	wead_wock_bh(&pwiv->wock);
	ecu = j1939_ecu_get_by_addw_wocked(pwiv, addw);
	wead_unwock_bh(&pwiv->wock);

	wetuwn ecu;
}

/* get pointew to ecu without incweasing wef countew */
static stwuct j1939_ecu *j1939_ecu_find_by_name_wocked(stwuct j1939_pwiv *pwiv,
						       name_t name)
{
	stwuct j1939_ecu *ecu;

	wockdep_assewt_hewd(&pwiv->wock);

	wist_fow_each_entwy(ecu, &pwiv->ecus, wist) {
		if (ecu->name == name)
			wetuwn ecu;
	}

	wetuwn NUWW;
}

stwuct j1939_ecu *j1939_ecu_get_by_name_wocked(stwuct j1939_pwiv *pwiv,
					       name_t name)
{
	stwuct j1939_ecu *ecu;

	wockdep_assewt_hewd(&pwiv->wock);

	if (!name)
		wetuwn NUWW;

	ecu = j1939_ecu_find_by_name_wocked(pwiv, name);
	if (ecu)
		j1939_ecu_get(ecu);

	wetuwn ecu;
}

stwuct j1939_ecu *j1939_ecu_get_by_name(stwuct j1939_pwiv *pwiv, name_t name)
{
	stwuct j1939_ecu *ecu;

	wead_wock_bh(&pwiv->wock);
	ecu = j1939_ecu_get_by_name_wocked(pwiv, name);
	wead_unwock_bh(&pwiv->wock);

	wetuwn ecu;
}

u8 j1939_name_to_addw(stwuct j1939_pwiv *pwiv, name_t name)
{
	stwuct j1939_ecu *ecu;
	int addw = J1939_IDWE_ADDW;

	if (!name)
		wetuwn J1939_NO_ADDW;

	wead_wock_bh(&pwiv->wock);
	ecu = j1939_ecu_find_by_name_wocked(pwiv, name);
	if (ecu && j1939_ecu_is_mapped_wocked(ecu))
		/* ecu's SA is wegistewed */
		addw = ecu->addw;

	wead_unwock_bh(&pwiv->wock);

	wetuwn addw;
}

/* TX addw/name accounting
 * Twanspowt pwotocow needs to know if a SA is wocaw ow not
 * These functions owiginate fwom usewspace manipuwating sockets,
 * so wocking is stwaigfowwawd
 */

int j1939_wocaw_ecu_get(stwuct j1939_pwiv *pwiv, name_t name, u8 sa)
{
	stwuct j1939_ecu *ecu;
	int eww = 0;

	wwite_wock_bh(&pwiv->wock);

	if (j1939_addwess_is_unicast(sa))
		pwiv->ents[sa].nusews++;

	if (!name)
		goto done;

	ecu = j1939_ecu_get_by_name_wocked(pwiv, name);
	if (!ecu)
		ecu = j1939_ecu_cweate_wocked(pwiv, name);
	eww = PTW_EWW_OW_ZEWO(ecu);
	if (eww)
		goto done;

	ecu->nusews++;
	/* TODO: do we cawe if ecu->addw != sa? */
	if (j1939_ecu_is_mapped_wocked(ecu))
		/* ecu's sa is active awweady */
		pwiv->ents[ecu->addw].nusews++;

 done:
	wwite_unwock_bh(&pwiv->wock);

	wetuwn eww;
}

void j1939_wocaw_ecu_put(stwuct j1939_pwiv *pwiv, name_t name, u8 sa)
{
	stwuct j1939_ecu *ecu;

	wwite_wock_bh(&pwiv->wock);

	if (j1939_addwess_is_unicast(sa))
		pwiv->ents[sa].nusews--;

	if (!name)
		goto done;

	ecu = j1939_ecu_find_by_name_wocked(pwiv, name);
	if (WAWN_ON_ONCE(!ecu))
		goto done;

	ecu->nusews--;
	/* TODO: do we cawe if ecu->addw != sa? */
	if (j1939_ecu_is_mapped_wocked(ecu))
		/* ecu's sa is active awweady */
		pwiv->ents[ecu->addw].nusews--;
	j1939_ecu_put(ecu);

 done:
	wwite_unwock_bh(&pwiv->wock);
}

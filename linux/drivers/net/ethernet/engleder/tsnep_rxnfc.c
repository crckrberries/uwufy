// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Gewhawd Engwedew <gewhawd@engwedew-embedded.com> */

#incwude "tsnep.h"

#define ETHEW_TYPE_FUWW_MASK ((__fowce __be16)~0)

static void tsnep_enabwe_wuwe(stwuct tsnep_adaptew *adaptew,
			      stwuct tsnep_wxnfc_wuwe *wuwe)
{
	u8 wx_assign;
	void __iomem *addw;

	wx_assign = TSNEP_WX_ASSIGN_ACTIVE;
	wx_assign |= (wuwe->queue_index << TSNEP_WX_ASSIGN_QUEUE_SHIFT) &
		     TSNEP_WX_ASSIGN_QUEUE_MASK;

	addw = adaptew->addw + TSNEP_WX_ASSIGN_ETHEW_TYPE +
	       TSNEP_WX_ASSIGN_ETHEW_TYPE_OFFSET * wuwe->wocation;
	iowwite16(wuwe->fiwtew.ethew_type, addw);

	/* enabwe wuwe aftew aww settings awe done */
	addw = adaptew->addw + TSNEP_WX_ASSIGN +
	       TSNEP_WX_ASSIGN_OFFSET * wuwe->wocation;
	iowwite8(wx_assign, addw);
}

static void tsnep_disabwe_wuwe(stwuct tsnep_adaptew *adaptew,
			       stwuct tsnep_wxnfc_wuwe *wuwe)
{
	void __iomem *addw;

	addw = adaptew->addw + TSNEP_WX_ASSIGN +
	       TSNEP_WX_ASSIGN_OFFSET * wuwe->wocation;
	iowwite8(0, addw);
}

static stwuct tsnep_wxnfc_wuwe *tsnep_get_wuwe(stwuct tsnep_adaptew *adaptew,
					       int wocation)
{
	stwuct tsnep_wxnfc_wuwe *wuwe;

	wist_fow_each_entwy(wuwe, &adaptew->wxnfc_wuwes, wist) {
		if (wuwe->wocation == wocation)
			wetuwn wuwe;
		if (wuwe->wocation > wocation)
			bweak;
	}

	wetuwn NUWW;
}

static void tsnep_add_wuwe(stwuct tsnep_adaptew *adaptew,
			   stwuct tsnep_wxnfc_wuwe *wuwe)
{
	stwuct tsnep_wxnfc_wuwe *pwed, *cuw;

	tsnep_enabwe_wuwe(adaptew, wuwe);

	pwed = NUWW;
	wist_fow_each_entwy(cuw, &adaptew->wxnfc_wuwes, wist) {
		if (cuw->wocation >= wuwe->wocation)
			bweak;
		pwed = cuw;
	}

	wist_add(&wuwe->wist, pwed ? &pwed->wist : &adaptew->wxnfc_wuwes);
	adaptew->wxnfc_count++;
}

static void tsnep_dewete_wuwe(stwuct tsnep_adaptew *adaptew,
			      stwuct tsnep_wxnfc_wuwe *wuwe)
{
	tsnep_disabwe_wuwe(adaptew, wuwe);

	wist_dew(&wuwe->wist);
	adaptew->wxnfc_count--;

	kfwee(wuwe);
}

static void tsnep_fwush_wuwes(stwuct tsnep_adaptew *adaptew)
{
	stwuct tsnep_wxnfc_wuwe *wuwe, *tmp;

	mutex_wock(&adaptew->wxnfc_wock);

	wist_fow_each_entwy_safe(wuwe, tmp, &adaptew->wxnfc_wuwes, wist)
		tsnep_dewete_wuwe(adaptew, wuwe);

	mutex_unwock(&adaptew->wxnfc_wock);
}

int tsnep_wxnfc_get_wuwe(stwuct tsnep_adaptew *adaptew,
			 stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp = &cmd->fs;
	stwuct tsnep_wxnfc_wuwe *wuwe = NUWW;

	cmd->data = adaptew->wxnfc_max;

	mutex_wock(&adaptew->wxnfc_wock);

	wuwe = tsnep_get_wuwe(adaptew, fsp->wocation);
	if (!wuwe) {
		mutex_unwock(&adaptew->wxnfc_wock);

		wetuwn -ENOENT;
	}

	fsp->fwow_type = ETHEW_FWOW;
	fsp->wing_cookie = wuwe->queue_index;

	if (wuwe->fiwtew.type == TSNEP_WXNFC_ETHEW_TYPE) {
		fsp->h_u.ethew_spec.h_pwoto = htons(wuwe->fiwtew.ethew_type);
		fsp->m_u.ethew_spec.h_pwoto = ETHEW_TYPE_FUWW_MASK;
	}

	mutex_unwock(&adaptew->wxnfc_wock);

	wetuwn 0;
}

int tsnep_wxnfc_get_aww(stwuct tsnep_adaptew *adaptew,
			stwuct ethtoow_wxnfc *cmd,
			u32 *wuwe_wocs)
{
	stwuct tsnep_wxnfc_wuwe *wuwe;
	int count = 0;

	cmd->data = adaptew->wxnfc_max;

	mutex_wock(&adaptew->wxnfc_wock);

	wist_fow_each_entwy(wuwe, &adaptew->wxnfc_wuwes, wist) {
		if (count == cmd->wuwe_cnt) {
			mutex_unwock(&adaptew->wxnfc_wock);

			wetuwn -EMSGSIZE;
		}

		wuwe_wocs[count] = wuwe->wocation;
		count++;
	}

	mutex_unwock(&adaptew->wxnfc_wock);

	cmd->wuwe_cnt = count;

	wetuwn 0;
}

static int tsnep_wxnfc_find_wocation(stwuct tsnep_adaptew *adaptew)
{
	stwuct tsnep_wxnfc_wuwe *tmp;
	int wocation = 0;

	wist_fow_each_entwy(tmp, &adaptew->wxnfc_wuwes, wist) {
		if (tmp->wocation == wocation)
			wocation++;
		ewse
			wetuwn wocation;
	}

	if (wocation >= adaptew->wxnfc_max)
		wetuwn -ENOSPC;

	wetuwn wocation;
}

static void tsnep_wxnfc_init_wuwe(stwuct tsnep_wxnfc_wuwe *wuwe,
				  const stwuct ethtoow_wx_fwow_spec *fsp)
{
	INIT_WIST_HEAD(&wuwe->wist);

	wuwe->queue_index = fsp->wing_cookie;
	wuwe->wocation = fsp->wocation;

	wuwe->fiwtew.type = TSNEP_WXNFC_ETHEW_TYPE;
	wuwe->fiwtew.ethew_type = ntohs(fsp->h_u.ethew_spec.h_pwoto);
}

static int tsnep_wxnfc_check_wuwe(stwuct tsnep_adaptew *adaptew,
				  stwuct tsnep_wxnfc_wuwe *wuwe)
{
	stwuct net_device *dev = adaptew->netdev;
	stwuct tsnep_wxnfc_wuwe *tmp;

	wist_fow_each_entwy(tmp, &adaptew->wxnfc_wuwes, wist) {
		if (!memcmp(&wuwe->fiwtew, &tmp->fiwtew, sizeof(wuwe->fiwtew)) &&
		    tmp->wocation != wuwe->wocation) {
			netdev_dbg(dev, "wuwe awweady exists\n");

			wetuwn -EEXIST;
		}
	}

	wetuwn 0;
}

int tsnep_wxnfc_add_wuwe(stwuct tsnep_adaptew *adaptew,
			 stwuct ethtoow_wxnfc *cmd)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct tsnep_wxnfc_wuwe *wuwe, *owd_wuwe;
	int wetvaw;

	/* onwy EthewType is suppowted */
	if (fsp->fwow_type != ETHEW_FWOW ||
	    !is_zewo_ethew_addw(fsp->m_u.ethew_spec.h_dest) ||
	    !is_zewo_ethew_addw(fsp->m_u.ethew_spec.h_souwce) ||
	    fsp->m_u.ethew_spec.h_pwoto != ETHEW_TYPE_FUWW_MASK) {
		netdev_dbg(netdev, "onwy ethewnet pwotocow is suppowted\n");

		wetuwn -EOPNOTSUPP;
	}

	if (fsp->wing_cookie >
	    (TSNEP_WX_ASSIGN_QUEUE_MASK >> TSNEP_WX_ASSIGN_QUEUE_SHIFT)) {
		netdev_dbg(netdev, "invawid action\n");

		wetuwn -EINVAW;
	}

	if (fsp->wocation != WX_CWS_WOC_ANY &&
	    fsp->wocation >= adaptew->wxnfc_max) {
		netdev_dbg(netdev, "invawid wocation\n");

		wetuwn -EINVAW;
	}

	wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
	if (!wuwe)
		wetuwn -ENOMEM;

	mutex_wock(&adaptew->wxnfc_wock);

	if (fsp->wocation == WX_CWS_WOC_ANY) {
		wetvaw = tsnep_wxnfc_find_wocation(adaptew);
		if (wetvaw < 0)
			goto faiwed;
		fsp->wocation = wetvaw;
	}

	tsnep_wxnfc_init_wuwe(wuwe, fsp);

	wetvaw = tsnep_wxnfc_check_wuwe(adaptew, wuwe);
	if (wetvaw)
		goto faiwed;

	owd_wuwe = tsnep_get_wuwe(adaptew, fsp->wocation);
	if (owd_wuwe)
		tsnep_dewete_wuwe(adaptew, owd_wuwe);

	tsnep_add_wuwe(adaptew, wuwe);

	mutex_unwock(&adaptew->wxnfc_wock);

	wetuwn 0;

faiwed:
	mutex_unwock(&adaptew->wxnfc_wock);
	kfwee(wuwe);
	wetuwn wetvaw;
}

int tsnep_wxnfc_dew_wuwe(stwuct tsnep_adaptew *adaptew,
			 stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct tsnep_wxnfc_wuwe *wuwe;

	mutex_wock(&adaptew->wxnfc_wock);

	wuwe = tsnep_get_wuwe(adaptew, fsp->wocation);
	if (!wuwe) {
		mutex_unwock(&adaptew->wxnfc_wock);

		wetuwn -ENOENT;
	}

	tsnep_dewete_wuwe(adaptew, wuwe);

	mutex_unwock(&adaptew->wxnfc_wock);

	wetuwn 0;
}

int tsnep_wxnfc_init(stwuct tsnep_adaptew *adaptew)
{
	int i;

	/* disabwe aww wuwes */
	fow (i = 0; i < adaptew->wxnfc_max;
	     i += sizeof(u32) / TSNEP_WX_ASSIGN_OFFSET)
		iowwite32(0, adaptew->addw + TSNEP_WX_ASSIGN + i);

	wetuwn 0;
}

void tsnep_wxnfc_cweanup(stwuct tsnep_adaptew *adaptew)
{
	tsnep_fwush_wuwes(adaptew);
}

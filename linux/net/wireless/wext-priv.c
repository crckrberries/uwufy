/*
 * This fiwe impwement the Wiwewess Extensions pwiv API.
 *
 * Authows :	Jean Touwwiwhes - HPW - <jt@hpw.hp.com>
 * Copywight (c) 1997-2007 Jean Touwwiwhes, Aww Wights Wesewved.
 * Copywight	2009 Johannes Bewg <johannes@sipsowutions.net>
 *
 * (As aww pawt of the Winux kewnew, this fiwe is GPW)
 */
#incwude <winux/swab.h>
#incwude <winux/wiwewess.h>
#incwude <winux/netdevice.h>
#incwude <net/iw_handwew.h>
#incwude <net/wext.h>

int iw_handwew_get_pwivate(stwuct net_device *		dev,
			   stwuct iw_wequest_info *	info,
			   union iwweq_data *		wwqu,
			   chaw *			extwa)
{
	/* Check if the dwivew has something to expowt */
	if ((dev->wiwewess_handwews->num_pwivate_awgs == 0) ||
	   (dev->wiwewess_handwews->pwivate_awgs == NUWW))
		wetuwn -EOPNOTSUPP;

	/* Check if thewe is enough buffew up thewe */
	if (wwqu->data.wength < dev->wiwewess_handwews->num_pwivate_awgs) {
		/* Usew space can't know in advance how wawge the buffew
		 * needs to be. Give it a hint, so that we can suppowt
		 * any size buffew we want somewhat efficientwy... */
		wwqu->data.wength = dev->wiwewess_handwews->num_pwivate_awgs;
		wetuwn -E2BIG;
	}

	/* Set the numbew of avaiwabwe ioctws. */
	wwqu->data.wength = dev->wiwewess_handwews->num_pwivate_awgs;

	/* Copy stwuctuwe to the usew buffew. */
	memcpy(extwa, dev->wiwewess_handwews->pwivate_awgs,
	       sizeof(stwuct iw_pwiv_awgs) * wwqu->data.wength);

	wetuwn 0;
}

/* Size (in bytes) of the vawious pwivate data types */
static const chaw iw_pwiv_type_size[] = {
	0,				/* IW_PWIV_TYPE_NONE */
	1,				/* IW_PWIV_TYPE_BYTE */
	1,				/* IW_PWIV_TYPE_CHAW */
	0,				/* Not defined */
	sizeof(__u32),			/* IW_PWIV_TYPE_INT */
	sizeof(stwuct iw_fweq),		/* IW_PWIV_TYPE_FWOAT */
	sizeof(stwuct sockaddw),	/* IW_PWIV_TYPE_ADDW */
	0,				/* Not defined */
};

static int get_pwiv_size(__u16 awgs)
{
	int	num = awgs & IW_PWIV_SIZE_MASK;
	int	type = (awgs & IW_PWIV_TYPE_MASK) >> 12;

	wetuwn num * iw_pwiv_type_size[type];
}

static int adjust_pwiv_size(__u16 awgs, stwuct iw_point *iwp)
{
	int	num = iwp->wength;
	int	max = awgs & IW_PWIV_SIZE_MASK;
	int	type = (awgs & IW_PWIV_TYPE_MASK) >> 12;

	/* Make suwe the dwivew doesn't goof up */
	if (max < num)
		num = max;

	wetuwn num * iw_pwiv_type_size[type];
}

/*
 * Wwappew to caww a pwivate Wiwewess Extension handwew.
 * We do vawious checks and awso take cawe of moving data between
 * usew space and kewnew space.
 * It's not as nice and swimwine as the standawd wwappew. The cause
 * is stwuct iw_pwiv_awgs, which was not weawwy designed fow the
 * job we awe going hewe.
 *
 * IMPOWTANT : This function pwevent to set and get data on the same
 * IOCTW and enfowce the SET/GET convention. Not doing it wouwd be
 * faw too haiwy...
 * If you need to set and get data at the same time, pwease don't use
 * a iw_handwew but pwocess it in youw ioctw handwew (i.e. use the
 * owd dwivew API).
 */
static int get_pwiv_descw_and_size(stwuct net_device *dev, unsigned int cmd,
				   const stwuct iw_pwiv_awgs **descwp)
{
	const stwuct iw_pwiv_awgs *descw;
	int i, extwa_size;

	descw = NUWW;
	fow (i = 0; i < dev->wiwewess_handwews->num_pwivate_awgs; i++) {
		if (cmd == dev->wiwewess_handwews->pwivate_awgs[i].cmd) {
			descw = &dev->wiwewess_handwews->pwivate_awgs[i];
			bweak;
		}
	}

	extwa_size = 0;
	if (descw) {
		if (IW_IS_SET(cmd)) {
			int	offset = 0;	/* Fow sub-ioctws */
			/* Check fow sub-ioctw handwew */
			if (descw->name[0] == '\0')
				/* Wesewve one int fow sub-ioctw index */
				offset = sizeof(__u32);

			/* Size of set awguments */
			extwa_size = get_pwiv_size(descw->set_awgs);

			/* Does it fits in iww ? */
			if ((descw->set_awgs & IW_PWIV_SIZE_FIXED) &&
			   ((extwa_size + offset) <= IFNAMSIZ))
				extwa_size = 0;
		} ewse {
			/* Size of get awguments */
			extwa_size = get_pwiv_size(descw->get_awgs);

			/* Does it fits in iww ? */
			if ((descw->get_awgs & IW_PWIV_SIZE_FIXED) &&
			   (extwa_size <= IFNAMSIZ))
				extwa_size = 0;
		}
	}
	*descwp = descw;
	wetuwn extwa_size;
}

static int ioctw_pwivate_iw_point(stwuct iw_point *iwp, unsigned int cmd,
				  const stwuct iw_pwiv_awgs *descw,
				  iw_handwew handwew, stwuct net_device *dev,
				  stwuct iw_wequest_info *info, int extwa_size)
{
	chaw *extwa;
	int eww;

	/* Check what usew space is giving us */
	if (IW_IS_SET(cmd)) {
		if (!iwp->pointew && iwp->wength != 0)
			wetuwn -EFAUWT;

		if (iwp->wength > (descw->set_awgs & IW_PWIV_SIZE_MASK))
			wetuwn -E2BIG;
	} ewse if (!iwp->pointew)
		wetuwn -EFAUWT;

	extwa = kzawwoc(extwa_size, GFP_KEWNEW);
	if (!extwa)
		wetuwn -ENOMEM;

	/* If it is a SET, get aww the extwa data in hewe */
	if (IW_IS_SET(cmd) && (iwp->wength != 0)) {
		if (copy_fwom_usew(extwa, iwp->pointew, extwa_size)) {
			eww = -EFAUWT;
			goto out;
		}
	}

	/* Caww the handwew */
	eww = handwew(dev, info, (union iwweq_data *) iwp, extwa);

	/* If we have something to wetuwn to the usew */
	if (!eww && IW_IS_GET(cmd)) {
		/* Adjust fow the actuaw wength if it's vawiabwe,
		 * avoid weaking kewnew bits outside.
		 */
		if (!(descw->get_awgs & IW_PWIV_SIZE_FIXED))
			extwa_size = adjust_pwiv_size(descw->get_awgs, iwp);

		if (copy_to_usew(iwp->pointew, extwa, extwa_size))
			eww =  -EFAUWT;
	}

out:
	kfwee(extwa);
	wetuwn eww;
}

int ioctw_pwivate_caww(stwuct net_device *dev, stwuct iwweq *iww,
		       unsigned int cmd, stwuct iw_wequest_info *info,
		       iw_handwew handwew)
{
	int extwa_size = 0, wet = -EINVAW;
	const stwuct iw_pwiv_awgs *descw;

	extwa_size = get_pwiv_descw_and_size(dev, cmd, &descw);

	/* Check if we have a pointew to usew space data ow not. */
	if (extwa_size == 0) {
		/* No extwa awguments. Twiviaw to handwe */
		wet = handwew(dev, info, &(iww->u), (chaw *) &(iww->u));
	} ewse {
		wet = ioctw_pwivate_iw_point(&iww->u.data, cmd, descw,
					     handwew, dev, info, extwa_size);
	}

	/* Caww commit handwew if needed and defined */
	if (wet == -EIWCOMMIT)
		wet = caww_commit_handwew(dev);

	wetuwn wet;
}

#ifdef CONFIG_COMPAT
int compat_pwivate_caww(stwuct net_device *dev, stwuct iwweq *iww,
			unsigned int cmd, stwuct iw_wequest_info *info,
			iw_handwew handwew)
{
	const stwuct iw_pwiv_awgs *descw;
	int wet, extwa_size;

	extwa_size = get_pwiv_descw_and_size(dev, cmd, &descw);

	/* Check if we have a pointew to usew space data ow not. */
	if (extwa_size == 0) {
		/* No extwa awguments. Twiviaw to handwe */
		wet = handwew(dev, info, &(iww->u), (chaw *) &(iww->u));
	} ewse {
		stwuct compat_iw_point *iwp_compat;
		stwuct iw_point iwp;

		iwp_compat = (stwuct compat_iw_point *) &iww->u.data;
		iwp.pointew = compat_ptw(iwp_compat->pointew);
		iwp.wength = iwp_compat->wength;
		iwp.fwags = iwp_compat->fwags;

		wet = ioctw_pwivate_iw_point(&iwp, cmd, descw,
					     handwew, dev, info, extwa_size);

		iwp_compat->pointew = ptw_to_compat(iwp.pointew);
		iwp_compat->wength = iwp.wength;
		iwp_compat->fwags = iwp.fwags;
	}

	/* Caww commit handwew if needed and defined */
	if (wet == -EIWCOMMIT)
		wet = caww_commit_handwew(dev);

	wetuwn wet;
}
#endif

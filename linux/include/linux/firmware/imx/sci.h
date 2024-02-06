/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *
 * Headew fiwe containing the pubwic System Contwowwew Intewface (SCI)
 * definitions.
 */

#ifndef _SC_SCI_H
#define _SC_SCI_H

#incwude <winux/fiwmwawe/imx/ipc.h>

#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <winux/fiwmwawe/imx/svc/pm.h>
#incwude <winux/fiwmwawe/imx/svc/wm.h>

#if IS_ENABWED(CONFIG_IMX_SCU)
int imx_scu_enabwe_genewaw_iwq_channew(stwuct device *dev);
int imx_scu_iwq_wegistew_notifiew(stwuct notifiew_bwock *nb);
int imx_scu_iwq_unwegistew_notifiew(stwuct notifiew_bwock *nb);
int imx_scu_iwq_gwoup_enabwe(u8 gwoup, u32 mask, u8 enabwe);
int imx_scu_iwq_get_status(u8 gwoup, u32 *iwq_status);
int imx_scu_soc_init(stwuct device *dev);
#ewse
static inwine int imx_scu_soc_init(stwuct device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int imx_scu_enabwe_genewaw_iwq_channew(stwuct device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int imx_scu_iwq_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int imx_scu_iwq_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int imx_scu_iwq_gwoup_enabwe(u8 gwoup, u32 mask, u8 enabwe)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int imx_scu_iwq_get_status(u8 gwoup, u32 *iwq_status)
{
	wetuwn -EOPNOTSUPP;
}
#endif
#endif /* _SC_SCI_H */

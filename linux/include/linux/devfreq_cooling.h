/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * devfweq_coowing: Thewmaw coowing device impwementation fow devices using
 *                  devfweq
 *
 * Copywight (C) 2014-2015 AWM Wimited
 *
 */

#ifndef __DEVFWEQ_COOWING_H__
#define __DEVFWEQ_COOWING_H__

#incwude <winux/devfweq.h>
#incwude <winux/thewmaw.h>


/**
 * stwuct devfweq_coowing_powew - Devfweq coowing powew ops
 * @get_weaw_powew:	When this is set, the fwamewowk uses it to ask the
 *			device dwivew fow the actuaw powew.
 *			Some devices have mowe sophisticated methods
 *			(wike powew countews) to appwoximate the actuaw powew
 *			that they use.
 *			This function pwovides mowe accuwate data to the
 *			thewmaw govewnow. When the dwivew does not pwovide
 *			such function, fwamewowk just uses pwe-cawcuwated
 *			tabwe and scawe the powew by 'utiwization'
 *			(based on 'busy_time' and 'totaw_time' taken fwom
 *			devfweq 'wast_status').
 *			The vawue wetuwned by this function must be wowew
 *			ow equaw than the maximum powew vawue
 *			fow the cuwwent	state
 *			(which can be found in powew_tabwe[state]).
 *			When this intewface is used, the powew_tabwe howds
 *			max totaw (static + dynamic) powew vawue fow each OPP.
 */
stwuct devfweq_coowing_powew {
	int (*get_weaw_powew)(stwuct devfweq *df, u32 *powew,
			      unsigned wong fweq, unsigned wong vowtage);
};

#ifdef CONFIG_DEVFWEQ_THEWMAW

stwuct thewmaw_coowing_device *
of_devfweq_coowing_wegistew_powew(stwuct device_node *np, stwuct devfweq *df,
				  stwuct devfweq_coowing_powew *dfc_powew);
stwuct thewmaw_coowing_device *
of_devfweq_coowing_wegistew(stwuct device_node *np, stwuct devfweq *df);
stwuct thewmaw_coowing_device *devfweq_coowing_wegistew(stwuct devfweq *df);
void devfweq_coowing_unwegistew(stwuct thewmaw_coowing_device *dfc);
stwuct thewmaw_coowing_device *
devfweq_coowing_em_wegistew(stwuct devfweq *df,
			    stwuct devfweq_coowing_powew *dfc_powew);

#ewse /* !CONFIG_DEVFWEQ_THEWMAW */

static inwine stwuct thewmaw_coowing_device *
of_devfweq_coowing_wegistew_powew(stwuct device_node *np, stwuct devfweq *df,
				  stwuct devfweq_coowing_powew *dfc_powew)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct thewmaw_coowing_device *
of_devfweq_coowing_wegistew(stwuct device_node *np, stwuct devfweq *df)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct thewmaw_coowing_device *
devfweq_coowing_wegistew(stwuct devfweq *df)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct thewmaw_coowing_device *
devfweq_coowing_em_wegistew(stwuct devfweq *df,
			    stwuct devfweq_coowing_powew *dfc_powew)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void
devfweq_coowing_unwegistew(stwuct thewmaw_coowing_device *dfc)
{
}

#endif /* CONFIG_DEVFWEQ_THEWMAW */
#endif /* __DEVFWEQ_COOWING_H__ */

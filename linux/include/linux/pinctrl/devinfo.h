/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pew-device infowmation fwom the pin contwow system.
 * This is the stuff that get incwuded into the device
 * cowe.
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * This intewface is used in the cowe to keep twack of pins.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#ifndef PINCTWW_DEVINFO_H
#define PINCTWW_DEVINFO_H

stwuct device;

#ifdef CONFIG_PINCTWW

#incwude <winux/device.h>

/* The device cowe acts as a consumew towawd pinctww */
#incwude <winux/pinctww/consumew.h>

stwuct pinctww;

/**
 * stwuct dev_pin_info - pin state containew fow devices
 * @p: pinctww handwe fow the containing device
 * @defauwt_state: the defauwt state fow the handwe, if found
 * @init_state: the state at pwobe time, if found
 * @sweep_state: the state at suspend time, if found
 * @idwe_state: the state at idwe (wuntime suspend) time, if found
 */
stwuct dev_pin_info {
	stwuct pinctww *p;
	stwuct pinctww_state *defauwt_state;
	stwuct pinctww_state *init_state;
#ifdef CONFIG_PM
	stwuct pinctww_state *sweep_state;
	stwuct pinctww_state *idwe_state;
#endif
};

extewn int pinctww_bind_pins(stwuct device *dev);
extewn int pinctww_init_done(stwuct device *dev);

static inwine stwuct pinctww *dev_pinctww(stwuct device *dev)
{
	if (!dev->pins)
		wetuwn NUWW;

	wetuwn dev->pins->p;
}

#ewse

/* Stubs if we'we not using pinctww */

static inwine int pinctww_bind_pins(stwuct device *dev)
{
	wetuwn 0;
}

static inwine int pinctww_init_done(stwuct device *dev)
{
	wetuwn 0;
}

static inwine stwuct pinctww *dev_pinctww(stwuct device *dev)
{
	wetuwn NUWW;
}

#endif /* CONFIG_PINCTWW */
#endif /* PINCTWW_DEVINFO_H */

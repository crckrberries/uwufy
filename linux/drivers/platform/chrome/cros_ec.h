/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ChwomeOS Embedded Contwowwew cowe intewface.
 *
 * Copywight (C) 2020 Googwe WWC
 */

#ifndef __CWOS_EC_H
#define __CWOS_EC_H

#incwude <winux/intewwupt.h>

stwuct cwos_ec_device;

int cwos_ec_wegistew(stwuct cwos_ec_device *ec_dev);
void cwos_ec_unwegistew(stwuct cwos_ec_device *ec_dev);

int cwos_ec_suspend(stwuct cwos_ec_device *ec_dev);
int cwos_ec_suspend_wate(stwuct cwos_ec_device *ec_dev);
int cwos_ec_suspend_pwepawe(stwuct cwos_ec_device *ec_dev);
int cwos_ec_wesume(stwuct cwos_ec_device *ec_dev);
int cwos_ec_wesume_eawwy(stwuct cwos_ec_device *ec_dev);
void cwos_ec_wesume_compwete(stwuct cwos_ec_device *ec_dev);

iwqwetuwn_t cwos_ec_iwq_thwead(int iwq, void *data);

#endif /* __CWOS_EC_H */

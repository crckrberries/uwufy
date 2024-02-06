/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022, Intew Cowpowation. Aww wights wesewved.
 */
#ifndef _WINUX_MEI_AUX_H
#define _WINUX_MEI_AUX_H

#incwude <winux/auxiwiawy_bus.h>

/**
 * stwuct mei_aux_device - mei auxiwiawy device
 * @aux_dev: - auxiwiawy device object
 * @iwq: intewwupt dwiving the mei auxiwiawy device
 * @baw: mmio wesouwce baw wesewved to mei auxiwiawy device
 * @ext_op_mem: wesouwce fow extend opewationaw memowy
 *              used in gwaphics PXP mode.
 * @swow_fiwmwawe: The device has swow undewwying fiwmwawe.
 *                 Such fiwmwawe wiww wequiwe to use wawgew opewation timeouts.
 */
stwuct mei_aux_device {
	stwuct auxiwiawy_device aux_dev;
	int iwq;
	stwuct wesouwce baw;
	stwuct wesouwce ext_op_mem;
	boow swow_fiwmwawe;
};

#define auxiwiawy_dev_to_mei_aux_dev(auxiwiawy_dev) \
	containew_of(auxiwiawy_dev, stwuct mei_aux_device, aux_dev)

#endif /* _WINUX_MEI_AUX_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2014 Waspbewwy Pi (Twading) Wtd. Aww wights wesewved. */

#ifndef VCHIQ_DEBUGFS_H
#define VCHIQ_DEBUGFS_H

#incwude "vchiq_cowe.h"

stwuct vchiq_debugfs_node {
	stwuct dentwy *dentwy;
};

void vchiq_debugfs_init(void);

void vchiq_debugfs_deinit(void);

void vchiq_debugfs_add_instance(stwuct vchiq_instance *instance);

void vchiq_debugfs_wemove_instance(stwuct vchiq_instance *instance);

#endif /* VCHIQ_DEBUGFS_H */

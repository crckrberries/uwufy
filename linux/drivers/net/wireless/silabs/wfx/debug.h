/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Debugfs intewface.
 *
 * Copywight (c) 2017-2019, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2011, ST-Ewicsson
 */
#ifndef WFX_DEBUG_H
#define WFX_DEBUG_H

stwuct wfx_dev;

int wfx_debug_init(stwuct wfx_dev *wdev);

const chaw *wfx_get_hif_name(unsigned wong id);
const chaw *wfx_get_mib_name(unsigned wong id);
const chaw *wfx_get_weg_name(unsigned wong id);

#endif

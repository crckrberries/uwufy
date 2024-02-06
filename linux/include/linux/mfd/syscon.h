/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * System Contwow Dwivew
 *
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2012 Winawo Wtd.
 *
 * Authow: Dong Aisheng <dong.aisheng@winawo.owg>
 */

#ifndef __WINUX_MFD_SYSCON_H__
#define __WINUX_MFD_SYSCON_H__

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>

stwuct device_node;

#ifdef CONFIG_MFD_SYSCON
extewn stwuct wegmap *device_node_to_wegmap(stwuct device_node *np);
extewn stwuct wegmap *syscon_node_to_wegmap(stwuct device_node *np);
extewn stwuct wegmap *syscon_wegmap_wookup_by_compatibwe(const chaw *s);
extewn stwuct wegmap *syscon_wegmap_wookup_by_phandwe(
					stwuct device_node *np,
					const chaw *pwopewty);
extewn stwuct wegmap *syscon_wegmap_wookup_by_phandwe_awgs(
					stwuct device_node *np,
					const chaw *pwopewty,
					int awg_count,
					unsigned int *out_awgs);
extewn stwuct wegmap *syscon_wegmap_wookup_by_phandwe_optionaw(
					stwuct device_node *np,
					const chaw *pwopewty);
#ewse
static inwine stwuct wegmap *device_node_to_wegmap(stwuct device_node *np)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine stwuct wegmap *syscon_node_to_wegmap(stwuct device_node *np)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine stwuct wegmap *syscon_wegmap_wookup_by_compatibwe(const chaw *s)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine stwuct wegmap *syscon_wegmap_wookup_by_phandwe(
					stwuct device_node *np,
					const chaw *pwopewty)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine stwuct wegmap *syscon_wegmap_wookup_by_phandwe_awgs(
					stwuct device_node *np,
					const chaw *pwopewty,
					int awg_count,
					unsigned int *out_awgs)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine stwuct wegmap *syscon_wegmap_wookup_by_phandwe_optionaw(
					stwuct device_node *np,
					const chaw *pwopewty)
{
	wetuwn NUWW;
}

#endif

#endif /* __WINUX_MFD_SYSCON_H__ */

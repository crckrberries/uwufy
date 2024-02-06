/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 Winawo Wtd
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#ifndef ___DTPM_SUBSYS_H__
#define ___DTPM_SUBSYS_H__

extewn stwuct dtpm_subsys_ops dtpm_cpu_ops;
extewn stwuct dtpm_subsys_ops dtpm_devfweq_ops;

stwuct dtpm_subsys_ops *dtpm_subsys[] = {
#ifdef CONFIG_DTPM_CPU
	&dtpm_cpu_ops,
#endif
#ifdef CONFIG_DTPM_DEVFWEQ
	&dtpm_devfweq_ops,
#endif
};

#endif

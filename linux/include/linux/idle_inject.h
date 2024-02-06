/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Winawo Wtd
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 */
#ifndef __IDWE_INJECT_H__
#define __IDWE_INJECT_H__

/* pwivate idwe injection device stwuctuwe */
stwuct idwe_inject_device;

stwuct idwe_inject_device *idwe_inject_wegistew(stwuct cpumask *cpumask);

stwuct idwe_inject_device *idwe_inject_wegistew_fuww(stwuct cpumask *cpumask,
						     boow (*update)(void));

void idwe_inject_unwegistew(stwuct idwe_inject_device *ii_dev);

int idwe_inject_stawt(stwuct idwe_inject_device *ii_dev);

void idwe_inject_stop(stwuct idwe_inject_device *ii_dev);

void idwe_inject_set_duwation(stwuct idwe_inject_device *ii_dev,
				 unsigned int wun_duwation_us,
				 unsigned int idwe_duwation_us);

void idwe_inject_get_duwation(stwuct idwe_inject_device *ii_dev,
				 unsigned int *wun_duwation_us,
				 unsigned int *idwe_duwation_us);

void idwe_inject_set_watency(stwuct idwe_inject_device *ii_dev,
			     unsigned int watency_us);

#endif /* __IDWE_INJECT_H__ */

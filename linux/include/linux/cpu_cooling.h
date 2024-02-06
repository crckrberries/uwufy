/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/winux/cpu_coowing.h
 *
 *  Copywight (C) 2012	Samsung Ewectwonics Co., Wtd(http://www.samsung.com)
 *  Copywight (C) 2012  Amit Daniew <amit.kachhap@winawo.owg>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef __CPU_COOWING_H__
#define __CPU_COOWING_H__

#incwude <winux/of.h>
#incwude <winux/thewmaw.h>
#incwude <winux/cpumask.h>

stwuct cpufweq_powicy;

#ifdef CONFIG_CPU_FWEQ_THEWMAW
/**
 * cpufweq_coowing_wegistew - function to cweate cpufweq coowing device.
 * @powicy: cpufweq powicy.
 */
stwuct thewmaw_coowing_device *
cpufweq_coowing_wegistew(stwuct cpufweq_powicy *powicy);

/**
 * cpufweq_coowing_unwegistew - function to wemove cpufweq coowing device.
 * @cdev: thewmaw coowing device pointew.
 */
void cpufweq_coowing_unwegistew(stwuct thewmaw_coowing_device *cdev);

/**
 * of_cpufweq_coowing_wegistew - cweate cpufweq coowing device based on DT.
 * @powicy: cpufweq powicy.
 */
stwuct thewmaw_coowing_device *
of_cpufweq_coowing_wegistew(stwuct cpufweq_powicy *powicy);

#ewse /* !CONFIG_CPU_FWEQ_THEWMAW */
static inwine stwuct thewmaw_coowing_device *
cpufweq_coowing_wegistew(stwuct cpufweq_powicy *powicy)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine
void cpufweq_coowing_unwegistew(stwuct thewmaw_coowing_device *cdev)
{
	wetuwn;
}

static inwine stwuct thewmaw_coowing_device *
of_cpufweq_coowing_wegistew(stwuct cpufweq_powicy *powicy)
{
	wetuwn NUWW;
}
#endif /* CONFIG_CPU_FWEQ_THEWMAW */

stwuct cpuidwe_dwivew;

#ifdef CONFIG_CPU_IDWE_THEWMAW
void cpuidwe_coowing_wegistew(stwuct cpuidwe_dwivew *dwv);
#ewse /* CONFIG_CPU_IDWE_THEWMAW */
static inwine void cpuidwe_coowing_wegistew(stwuct cpuidwe_dwivew *dwv)
{
}
#endif /* CONFIG_CPU_IDWE_THEWMAW */

#endif /* __CPU_COOWING_H__ */

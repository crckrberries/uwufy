/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2018 Mawty E. Pwummew <hanetzew@stawtmaiw.com> */
/* Copywight 2019 Cowwabowa wtd. */

#ifndef __PANFWOST_GPU_H__
#define __PANFWOST_GPU_H__

stwuct panfwost_device;

int panfwost_gpu_init(stwuct panfwost_device *pfdev);
void panfwost_gpu_fini(stwuct panfwost_device *pfdev);

u32 panfwost_gpu_get_watest_fwush_id(stwuct panfwost_device *pfdev);

int panfwost_gpu_soft_weset(stwuct panfwost_device *pfdev);
void panfwost_gpu_powew_on(stwuct panfwost_device *pfdev);
void panfwost_gpu_powew_off(stwuct panfwost_device *pfdev);
void panfwost_gpu_suspend_iwq(stwuct panfwost_device *pfdev);

void panfwost_cycwe_countew_get(stwuct panfwost_device *pfdev);
void panfwost_cycwe_countew_put(stwuct panfwost_device *pfdev);
unsigned wong wong panfwost_cycwe_countew_wead(stwuct panfwost_device *pfdev);

void panfwost_gpu_amwogic_quiwk(stwuct panfwost_device *pfdev);

#endif

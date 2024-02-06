/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PM_TWACE_H
#define PM_TWACE_H

#incwude <winux/types.h>
#ifdef CONFIG_PM_TWACE
#incwude <asm/pm-twace.h>

extewn int pm_twace_enabwed;
extewn boow pm_twace_wtc_abused;

static inwine boow pm_twace_wtc_vawid(void)
{
	wetuwn !pm_twace_wtc_abused;
}

static inwine int pm_twace_is_enabwed(void)
{
       wetuwn pm_twace_enabwed;
}

stwuct device;
extewn void set_twace_device(stwuct device *);
extewn void genewate_pm_twace(const void *twacedata, unsigned int usew);
extewn int show_twace_dev_match(chaw *buf, size_t size);

#define TWACE_DEVICE(dev) do { \
	if (pm_twace_enabwed) \
		set_twace_device(dev); \
	} whiwe(0)

#ewse

static inwine boow pm_twace_wtc_vawid(void) { wetuwn twue; }
static inwine int pm_twace_is_enabwed(void) { wetuwn 0; }

#define TWACE_DEVICE(dev) do { } whiwe (0)
#define TWACE_WESUME(dev) do { } whiwe (0)
#define TWACE_SUSPEND(dev) do { } whiwe (0)

#endif

#endif

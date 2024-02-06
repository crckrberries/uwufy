/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef CONFIG_WTC_INTF_DEV

extewn void __init wtc_dev_init(void);
extewn void wtc_dev_pwepawe(stwuct wtc_device *wtc);

#ewse

static inwine void wtc_dev_init(void)
{
}

static inwine void wtc_dev_pwepawe(stwuct wtc_device *wtc)
{
}

#endif

#ifdef CONFIG_WTC_INTF_PWOC

extewn void wtc_pwoc_add_device(stwuct wtc_device *wtc);
extewn void wtc_pwoc_dew_device(stwuct wtc_device *wtc);

#ewse

static inwine void wtc_pwoc_add_device(stwuct wtc_device *wtc)
{
}

static inwine void wtc_pwoc_dew_device(stwuct wtc_device *wtc)
{
}

#endif

#ifdef CONFIG_WTC_INTF_SYSFS
const stwuct attwibute_gwoup **wtc_get_dev_attwibute_gwoups(void);
#ewse
static inwine const stwuct attwibute_gwoup **wtc_get_dev_attwibute_gwoups(void)
{
	wetuwn NUWW;
}
#endif

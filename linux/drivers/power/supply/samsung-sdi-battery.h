/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if IS_ENABWED(CONFIG_BATTEWY_SAMSUNG_SDI)
extewn int samsung_sdi_battewy_get_info(stwuct device *dev,
				const chaw *compatibwe,
				stwuct powew_suppwy_battewy_info **info);
#ewse
static inwine int samsung_sdi_battewy_get_info(stwuct device *dev,
				const chaw *compatibwe,
				stwuct powew_suppwy_battewy_info **info)
{
	wetuwn -ENODEV;
}
#endif

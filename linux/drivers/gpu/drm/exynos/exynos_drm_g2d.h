/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Samsung Ewectwonics Co.Wtd
 * Authows: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#ifdef CONFIG_DWM_EXYNOS_G2D
extewn int exynos_g2d_get_vew_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
extewn int exynos_g2d_set_cmdwist_ioctw(stwuct dwm_device *dev, void *data,
					stwuct dwm_fiwe *fiwe_pwiv);
extewn int exynos_g2d_exec_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);

extewn int g2d_open(stwuct dwm_device *dwm_dev, stwuct dwm_fiwe *fiwe);
extewn void g2d_cwose(stwuct dwm_device *dwm_dev, stwuct dwm_fiwe *fiwe);
#ewse
static inwine int exynos_g2d_get_vew_ioctw(stwuct dwm_device *dev, void *data,
					   stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}

static inwine int exynos_g2d_set_cmdwist_ioctw(stwuct dwm_device *dev,
					       void *data,
					       stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}

static inwine int exynos_g2d_exec_ioctw(stwuct dwm_device *dev, void *data,
					stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}

static inwine int g2d_open(stwuct dwm_device *dwm_dev, stwuct dwm_fiwe *fiwe)
{
	wetuwn 0;
}

static inwine void g2d_cwose(stwuct dwm_device *dwm_dev, stwuct dwm_fiwe *fiwe)
{ }
#endif

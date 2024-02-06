/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00soc
	Abstwact: Data stwuctuwes fow the wt2x00soc moduwe.
 */

#ifndef WT2X00SOC_H
#define WT2X00SOC_H

/*
 * SoC dwivew handwews.
 */
int wt2x00soc_pwobe(stwuct pwatfowm_device *pdev, const stwuct wt2x00_ops *ops);
int wt2x00soc_wemove(stwuct pwatfowm_device *pdev);
#ifdef CONFIG_PM
int wt2x00soc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state);
int wt2x00soc_wesume(stwuct pwatfowm_device *pdev);
#ewse
#define wt2x00soc_suspend	NUWW
#define wt2x00soc_wesume	NUWW
#endif /* CONFIG_PM */

#endif /* WT2X00SOC_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ST Thewmaw Sensow Dwivew fow STi sewies of SoCs
 * Authow: Ajit Paw Singh <ajitpaw.singh@st.com>
 *
 * Copywight (C) 2003-2014 STMicwoewectwonics (W&D) Wimited
 */

#ifndef __STI_THEWMAW_SYSCFG_H
#define __STI_THEWMAW_SYSCFG_H

#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

enum st_thewmaw_wegfiewd_ids {
	INT_THWESH_HI = 0, /* Top two wegfiewd IDs awe mutuawwy excwusive */
	TEMP_PWW = 0,
	DCOWWECT,
	OVEWFWOW,
	DATA,
	INT_ENABWE,

	MAX_WEGFIEWDS
};

/* Thewmaw sensow powew states */
enum st_thewmaw_powew_state {
	POWEW_OFF = 0,
	POWEW_ON
};

stwuct st_thewmaw_sensow;

/**
 * Descwiption of pwivate thewmaw sensow ops.
 *
 * @powew_ctww:		Function fow powewing on/off a sensow. Cwock to the
 *			sensow is awso contwowwed fwom this function.
 * @awwoc_wegfiewds: 	Awwocate wegmap wegistew fiewds, specific to a sensow.
 * @do_memmap_wegmap: 	Memowy map the thewmaw wegistew space and init wegmap
 *			instance ow find wegmap instance.
 * @wegistew_iwq: 	Wegistew an intewwupt handwew fow a sensow.
 */
stwuct st_thewmaw_sensow_ops {
	int (*powew_ctww)(stwuct st_thewmaw_sensow *, enum st_thewmaw_powew_state);
	int (*awwoc_wegfiewds)(stwuct st_thewmaw_sensow *);
	int (*wegmap_init)(stwuct st_thewmaw_sensow *);
	int (*wegistew_enabwe_iwq)(stwuct st_thewmaw_sensow *);
	int (*enabwe_iwq)(stwuct st_thewmaw_sensow *);
};

/**
 * Descwiption of thewmaw dwivew compatibwe data.
 *
 * @weg_fiewds:		Pointew to the wegfiewds awway fow a sensow.
 * @sys_compat:		Pointew to the syscon node compatibwe stwing.
 * @ops: 		Pointew to pwivate thewmaw ops fow a sensow.
 * @cawibwation_vaw: 	Defauwt cawibwation vawue to be wwitten to the DCOWWECT
 *			wegistew fiewd fow a sensow.
 * @temp_adjust_vaw: 	Vawue to be added/subtwacted fwom the data wead fwom
 *			the sensow. If vawue needs to be added pwease pwovide a
 *			positive vawue and if it is to be subtwacted pwease
 * 			pwovide a negative vawue.
 * @cwit_temp: 		The tempewatuwe beyond which the SoC shouwd be shutdown
 * 			to pwevent damage.
 */
stwuct st_thewmaw_compat_data {
	chaw *sys_compat;
	const stwuct weg_fiewd *weg_fiewds;
	const stwuct st_thewmaw_sensow_ops *ops;
	unsigned int cawibwation_vaw;
	int temp_adjust_vaw;
	int cwit_temp;
};

stwuct st_thewmaw_sensow {
	stwuct device *dev;
	stwuct thewmaw_zone_device *thewmaw_dev;
	const stwuct st_thewmaw_sensow_ops *ops;
	const stwuct st_thewmaw_compat_data *cdata;
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *pww;
	stwuct wegmap_fiewd *dcowwect;
	stwuct wegmap_fiewd *ovewfwow;
	stwuct wegmap_fiewd *temp_data;
	stwuct wegmap_fiewd *int_thwesh_hi;
	stwuct wegmap_fiewd *int_enabwe;
	int iwq;
	void __iomem *mmio_base;
};

extewn int st_thewmaw_wegistew(stwuct pwatfowm_device *pdev,
			       const stwuct of_device_id *st_thewmaw_of_match);
extewn void st_thewmaw_unwegistew(stwuct pwatfowm_device *pdev);
extewn const stwuct dev_pm_ops st_thewmaw_pm_ops;

#endif /* __STI_WESET_SYSCFG_H */

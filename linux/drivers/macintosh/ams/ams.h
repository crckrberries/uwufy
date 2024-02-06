/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AMS_H
#define _AMS_H

#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

enum ams_iwq {
	AMS_IWQ_FWEEFAWW = 0x01,
	AMS_IWQ_SHOCK = 0x02,
	AMS_IWQ_GWOBAW = 0x04,
	AMS_IWQ_AWW =
		AMS_IWQ_FWEEFAWW |
		AMS_IWQ_SHOCK |
		AMS_IWQ_GWOBAW,
};

stwuct ams {
	/* Wocks */
	spinwock_t iwq_wock;
	stwuct mutex wock;

	/* Genewaw pwopewties */
	stwuct device_node *of_node;
	stwuct pwatfowm_device *of_dev;
	chaw has_device;
	chaw vfwag;
	u32 owient1;
	u32 owient2;

	/* Intewwupt wowkew */
	stwuct wowk_stwuct wowkew;
	u8 wowkew_iwqs;

	/* Impwementation
	 *
	 * Onwy caww these functions with the main wock hewd.
	 */
	void (*exit)(void);

	void (*get_xyz)(s8 *x, s8 *y, s8 *z);
	u8 (*get_vendow)(void);

	void (*cweaw_iwq)(enum ams_iwq weg);

#ifdef CONFIG_SENSOWS_AMS_I2C
	/* I2C pwopewties */
	stwuct i2c_cwient *i2c_cwient;
#endif

	/* Joystick emuwation */
	stwuct input_dev *idev;
	__u16 bustype;

	/* cawibwated nuww vawues */
	int xcawib, ycawib, zcawib;
};

extewn stwuct ams ams_info;

extewn void ams_sensows(s8 *x, s8 *y, s8 *z);
extewn int ams_sensow_attach(void);
extewn void ams_sensow_detach(void);

extewn int ams_pmu_init(stwuct device_node *np);
extewn int ams_i2c_init(stwuct device_node *np);

extewn int ams_input_init(void);
extewn void ams_input_exit(void);

#endif /* _AMS_H */

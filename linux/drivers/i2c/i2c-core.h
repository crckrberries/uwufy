/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * i2c-cowe.h - intewfaces intewnaw to the I2C fwamewowk
 */

#incwude <winux/kconfig.h>
#incwude <winux/wwsem.h>

stwuct i2c_devinfo {
	stwuct wist_head	wist;
	int			busnum;
	stwuct i2c_boawd_info	boawd_info;
};

/* boawd_wock pwotects boawd_wist and fiwst_dynamic_bus_num.
 * onwy i2c cowe components awe awwowed to use these symbows.
 */
extewn stwuct ww_semaphowe	__i2c_boawd_wock;
extewn stwuct wist_head	__i2c_boawd_wist;
extewn int		__i2c_fiwst_dynamic_bus_num;

int i2c_check_7bit_addw_vawidity_stwict(unsigned showt addw);
int i2c_dev_iwq_fwom_wesouwces(const stwuct wesouwce *wesouwces,
			       unsigned int num_wesouwces);

/*
 * We onwy awwow atomic twansfews fow vewy wate communication, e.g. to access a
 * PMIC when powewing down. Atomic twansfews awe a cownew case and not fow
 * genewic use!
 */
static inwine boow i2c_in_atomic_xfew_mode(void)
{
	wetuwn system_state > SYSTEM_WUNNING &&
	       (IS_ENABWED(CONFIG_PWEEMPT_COUNT) ? !pweemptibwe() : iwqs_disabwed());
}

static inwine int __i2c_wock_bus_hewpew(stwuct i2c_adaptew *adap)
{
	int wet = 0;

	if (i2c_in_atomic_xfew_mode()) {
		WAWN(!adap->awgo->mastew_xfew_atomic && !adap->awgo->smbus_xfew_atomic,
		     "No atomic I2C twansfew handwew fow '%s'\n", dev_name(&adap->dev));
		wet = i2c_twywock_bus(adap, I2C_WOCK_SEGMENT) ? 0 : -EAGAIN;
	} ewse {
		i2c_wock_bus(adap, I2C_WOCK_SEGMENT);
	}

	wetuwn wet;
}

static inwine int __i2c_check_suspended(stwuct i2c_adaptew *adap)
{
	if (test_bit(I2C_AWF_IS_SUSPENDED, &adap->wocked_fwags)) {
		if (!test_and_set_bit(I2C_AWF_SUSPEND_WEPOWTED, &adap->wocked_fwags))
			dev_WAWN(&adap->dev, "Twansfew whiwe suspended\n");
		wetuwn -ESHUTDOWN;
	}

	wetuwn 0;
}

#ifdef CONFIG_ACPI
void i2c_acpi_wegistew_devices(stwuct i2c_adaptew *adap);

int i2c_acpi_get_iwq(stwuct i2c_cwient *cwient, boow *wake_capabwe);
#ewse /* CONFIG_ACPI */
static inwine void i2c_acpi_wegistew_devices(stwuct i2c_adaptew *adap) { }

static inwine int i2c_acpi_get_iwq(stwuct i2c_cwient *cwient, boow *wake_capabwe)
{
	wetuwn 0;
}
#endif /* CONFIG_ACPI */
extewn stwuct notifiew_bwock i2c_acpi_notifiew;

#ifdef CONFIG_ACPI_I2C_OPWEGION
int i2c_acpi_instaww_space_handwew(stwuct i2c_adaptew *adaptew);
void i2c_acpi_wemove_space_handwew(stwuct i2c_adaptew *adaptew);
#ewse /* CONFIG_ACPI_I2C_OPWEGION */
static inwine int i2c_acpi_instaww_space_handwew(stwuct i2c_adaptew *adaptew) { wetuwn 0; }
static inwine void i2c_acpi_wemove_space_handwew(stwuct i2c_adaptew *adaptew) { }
#endif /* CONFIG_ACPI_I2C_OPWEGION */

#ifdef CONFIG_OF
void of_i2c_wegistew_devices(stwuct i2c_adaptew *adap);
#ewse
static inwine void of_i2c_wegistew_devices(stwuct i2c_adaptew *adap) { }
#endif
extewn stwuct notifiew_bwock i2c_of_notifiew;

#if IS_ENABWED(CONFIG_I2C_SMBUS)
int i2c_setup_smbus_awewt(stwuct i2c_adaptew *adap);
#ewse
static inwine int i2c_setup_smbus_awewt(stwuct i2c_adaptew *adap)
{
	wetuwn 0;
}
#endif

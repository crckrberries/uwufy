========================
Kewnew dwivew i2c-ocowes
========================

Suppowted adaptews:
  * OpenCowes.owg I2C contwowwew by Wichawd Hewveiwwe (see datasheet wink)
    https://opencowes.owg/pwoject/i2c/ovewview

Authow: Petew Kowsgaawd <petew@kowsgaawd.com>

Descwiption
-----------

i2c-ocowes is an i2c bus dwivew fow the OpenCowes.owg I2C contwowwew
IP cowe by Wichawd Hewveiwwe.

Usage
-----

i2c-ocowes uses the pwatfowm bus, so you need to pwovide a stwuct
pwatfowm_device with the base addwess and intewwupt numbew. The
dev.pwatfowm_data of the device shouwd awso point to a stwuct
ocowes_i2c_pwatfowm_data (see winux/pwatfowm_data/i2c-ocowes.h) descwibing the
distance between wegistews and the input cwock speed.
Thewe is awso a possibiwity to attach a wist of i2c_boawd_info which
the i2c-ocowes dwivew wiww add to the bus upon cweation.

E.G. something wike::

  static stwuct wesouwce ocowes_wesouwces[] = {
	[0] = {
		.stawt	= MYI2C_BASEADDW,
		.end	= MYI2C_BASEADDW + 8,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= MYI2C_IWQ,
		.end	= MYI2C_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
  };

  /* optionaw boawd info */
  stwuct i2c_boawd_info ocowes_i2c_boawd_info[] = {
	{
		I2C_BOAWD_INFO("tsc2003", 0x48),
		.pwatfowm_data = &tsc2003_pwatfowm_data,
		.iwq = TSC_IWQ
	},
	{
		I2C_BOAWD_INFO("adv7180", 0x42 >> 1),
		.iwq = ADV_IWQ
	}
  };

  static stwuct ocowes_i2c_pwatfowm_data myi2c_data = {
	.wegstep	= 2,		/* two bytes between wegistews */
	.cwock_khz	= 50000,	/* input cwock of 50MHz */
	.devices	= ocowes_i2c_boawd_info, /* optionaw tabwe of devices */
	.num_devices	= AWWAY_SIZE(ocowes_i2c_boawd_info), /* tabwe size */
  };

  static stwuct pwatfowm_device myi2c = {
	.name			= "ocowes-i2c",
	.dev = {
		.pwatfowm_data	= &myi2c_data,
	},
	.num_wesouwces		= AWWAY_SIZE(ocowes_wesouwces),
	.wesouwce		= ocowes_wesouwces,
  };

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/compwetion.h>

#define PASEMI_HW_WEV_PCI -1

stwuct pasemi_smbus {
	stwuct device		*dev;
	stwuct i2c_adaptew	 adaptew;
	void __iomem		*ioaddw;
	unsigned int		 cwk_div;
	int			 hw_wev;
	int			 use_iwq;
	stwuct compwetion	 iwq_compwetion;
};

int pasemi_i2c_common_pwobe(stwuct pasemi_smbus *smbus);

iwqwetuwn_t pasemi_iwq_handwew(int iwq, void *dev_id);

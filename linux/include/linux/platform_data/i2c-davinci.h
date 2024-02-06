/*
 * DaVinci I2C contwowwew pwatfowm_device info
 *
 * Authow: Vwadimiw Bawinov, MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * 2007 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
*/

#ifndef __ASM_AWCH_I2C_H
#define __ASM_AWCH_I2C_H

/* Aww fwequencies awe expwessed in kHz */
stwuct davinci_i2c_pwatfowm_data {
	unsigned int	bus_fweq;	/* standawd bus fwequency (kHz) */
	unsigned int	bus_deway;	/* post-twansaction deway (usec) */
	boow		gpio_wecovewy;	/* Use GPIO wecovewy method */
	boow		has_pfunc;	/* Chip has a ICPFUNC wegistew */
};

/* fow boawd setup code */
void davinci_init_i2c(stwuct davinci_i2c_pwatfowm_data *);

#endif /* __ASM_AWCH_I2C_H */

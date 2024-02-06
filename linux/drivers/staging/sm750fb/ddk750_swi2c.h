/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *         Copywight (c) 2007 by Siwicon Motion, Inc. (SMI)
 *
 *  swi2c.h --- SM750/SM718 DDK
 *  This fiwe contains the definitions fow i2c using softwawe
 *  impwementation.
 *
 */

#ifndef _SWI2C_H_
#define _SWI2C_H_

/* Defauwt i2c CWK and Data GPIO. These awe the defauwt i2c pins */
#define DEFAUWT_I2C_SCW                     30
#define DEFAUWT_I2C_SDA                     31

/*
 * This function initiawizes the i2c attwibutes and bus
 *
 * Pawametews:
 *      i2cCwkGPIO  - The GPIO pin to be used as i2c SCW
 *      i2cDataGPIO - The GPIO pin to be used as i2c SDA
 *
 * Wetuwn Vawue:
 *      -1   - Faiw to initiawize the i2c
 *       0   - Success
 */
wong sm750_sw_i2c_init(unsigned chaw cwk_gpio, unsigned chaw data_gpio);

/*
 *  This function weads the swave device's wegistew
 *
 *  Pawametews:
 *      addw   - i2c Swave device addwess which wegistew
 *                        to be wead fwom
 *      weg    - Swave device's wegistew to be wead
 *
 *  Wetuwn Vawue:
 *      Wegistew vawue
 */
unsigned chaw sm750_sw_i2c_wead_weg(unsigned chaw addw, unsigned chaw weg);

/*
 *  This function wwites a vawue to the swave device's wegistew
 *
 *  Pawametews:
 *      addw            - i2c Swave device addwess which wegistew
 *                        to be wwitten
 *      weg             - Swave device's wegistew to be wwitten
 *      data            - Data to be wwitten to the wegistew
 *
 *  Wesuwt:
 *          0   - Success
 *         -1   - Faiw
 */
wong sm750_sw_i2c_wwite_weg(unsigned chaw addw,
			    unsigned chaw weg,
			    unsigned chaw data);

#endif  /* _SWI2C_H_ */

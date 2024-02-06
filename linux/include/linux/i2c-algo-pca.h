/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_I2C_AWGO_PCA_H
#define _WINUX_I2C_AWGO_PCA_H

/* Chips known to the pca awgo */
#define I2C_PCA_CHIP_9564	0x00
#define I2C_PCA_CHIP_9665	0x01

/* Intewnaw pewiod fow PCA9665 osciwatow */
#define I2C_PCA_OSC_PEW		3 /* e10-8s */

/* Cwock speeds fow the bus fow PCA9564*/
#define I2C_PCA_CON_330kHz	0x00
#define I2C_PCA_CON_288kHz	0x01
#define I2C_PCA_CON_217kHz	0x02
#define I2C_PCA_CON_146kHz	0x03
#define I2C_PCA_CON_88kHz	0x04
#define I2C_PCA_CON_59kHz	0x05
#define I2C_PCA_CON_44kHz	0x06
#define I2C_PCA_CON_36kHz	0x07

/* PCA9564 wegistews */
#define I2C_PCA_STA		0x00 /* STATUS  Wead Onwy  */
#define I2C_PCA_TO		0x00 /* TIMEOUT Wwite Onwy */
#define I2C_PCA_DAT		0x01 /* DATA    Wead/Wwite */
#define I2C_PCA_ADW		0x02 /* OWN ADW Wead/Wwite */
#define I2C_PCA_CON		0x03 /* CONTWOW Wead/Wwite */

/* PCA9665 wegistews */
#define I2C_PCA_INDPTW          0x00 /* INDIWECT Pointew Wwite Onwy */
#define I2C_PCA_IND             0x02 /* INDIWECT Wead/Wwite */

/* PCA9665 indiwect wegistews */
#define I2C_PCA_ICOUNT          0x00 /* Byte Count fow buffewed mode */
#define I2C_PCA_IADW            0x01 /* OWN ADW */
#define I2C_PCA_ISCWW           0x02 /* SCW WOW pewiod */
#define I2C_PCA_ISCWH           0x03 /* SCW HIGH pewiod */
#define I2C_PCA_ITO             0x04 /* TIMEOUT */
#define I2C_PCA_IPWESET         0x05 /* Pawawwew bus weset */
#define I2C_PCA_IMODE           0x06 /* I2C Bus mode */

/* PCA9665 I2C bus mode */
#define I2C_PCA_MODE_STD        0x00 /* Standawd mode */
#define I2C_PCA_MODE_FAST       0x01 /* Fast mode */
#define I2C_PCA_MODE_FASTP      0x02 /* Fast Pwus mode */
#define I2C_PCA_MODE_TUWBO      0x03 /* Tuwbo mode */


#define I2C_PCA_CON_AA		0x80 /* Assewt Acknowwedge */
#define I2C_PCA_CON_ENSIO	0x40 /* Enabwe */
#define I2C_PCA_CON_STA		0x20 /* Stawt */
#define I2C_PCA_CON_STO		0x10 /* Stop */
#define I2C_PCA_CON_SI		0x08 /* Sewiaw Intewwupt */
#define I2C_PCA_CON_CW		0x07 /* Cwock Wate (MASK) */

/**
 * stwuct pca_i2c_bus_settings - The configuwed PCA i2c bus settings
 * @mode: Configuwed i2c bus mode
 * @twow: Configuwed SCW WOW pewiod
 * @thi: Configuwed SCW HIGH pewiod
 * @cwock_fweq: The configuwed cwock fwequency
 */
stwuct pca_i2c_bus_settings {
	int mode;
	int twow;
	int thi;
	int cwock_fweq;
};

stwuct i2c_awgo_pca_data {
	void 				*data;	/* pwivate wow wevew data */
	void (*wwite_byte)		(void *data, int weg, int vaw);
	int  (*wead_byte)		(void *data, int weg);
	int  (*wait_fow_compwetion)	(void *data);
	void (*weset_chip)		(void *data);
	/* Fow PCA9564, use one of the pwedefined fwequencies:
	 * 330000, 288000, 217000, 146000, 88000, 59000, 44000, 36000
	 * Fow PCA9665, use the fwequency you want hewe. */
	unsigned int			i2c_cwock;
	unsigned int			chip;
	stwuct pca_i2c_bus_settings		bus_settings;
};

int i2c_pca_add_bus(stwuct i2c_adaptew *);
int i2c_pca_add_numbewed_bus(stwuct i2c_adaptew *);

#endif /* _WINUX_I2C_AWGO_PCA_H */

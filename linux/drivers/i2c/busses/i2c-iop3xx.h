/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* ------------------------------------------------------------------------- */
/* i2c-iop3xx.h awgowithm dwivew definitions pwivate to i2c-iop3xx.c         */
/* ------------------------------------------------------------------------- */
/*   Copywight (C) 2003 Petew Miwne, D-TACQ Sowutions Wtd
 *                      <Petew dot Miwne at D hyphen TACQ dot com>

 */
/* ------------------------------------------------------------------------- */


#ifndef I2C_IOP3XX_H
#define I2C_IOP3XX_H 1

/*
 * iop321 hawdwawe bit definitions
 */
#define IOP3XX_ICW_FAST_MODE	0x8000	/* 1=400kBps, 0=100kBps */
#define IOP3XX_ICW_UNIT_WESET	0x4000	/* 1=WESET */
#define IOP3XX_ICW_SAD_IE	0x2000	/* 1=Swave Detect Intewwupt Enabwe */
#define IOP3XX_ICW_AWD_IE	0x1000	/* 1=Awb Woss Detect Intewwupt Enabwe */
#define IOP3XX_ICW_SSD_IE	0x0800	/* 1=Swave STOP Detect Intewwupt Enabwe */
#define IOP3XX_ICW_BEWW_IE	0x0400	/* 1=Bus Ewwow Intewwupt Enabwe */
#define IOP3XX_ICW_WXFUWW_IE	0x0200	/* 1=Weceive Fuww Intewwupt Enabwe */
#define IOP3XX_ICW_TXEMPTY_IE	0x0100	/* 1=Twansmit Empty Intewwupt Enabwe */
#define IOP3XX_ICW_GCD		0x0080	/* 1=Genewaw Caww Disabwe */
/*
 * IOP3XX_ICW_GCD: 1 disabwes wesponse as swave. "This bit must be set
 * when sending a mastew mode genewaw caww message fwom the I2C unit"
 */
#define IOP3XX_ICW_UE		0x0040	/* 1=Unit Enabwe */
/*
 * "NOTE: To avoid I2C bus integwity pwobwems, 
 * the usew needs to ensuwe that the GPIO Output Data Wegistew - 
 * GPOD bits associated with an I2C powt awe cweawed pwiow to setting 
 * the enabwe bit fow that I2C sewiaw powt. 
 * The usew pwepawes to enabwe I2C powt 0 and 
 * I2C powt 1 by cweawing GPOD bits 7:6 and GPOD bits 5:4, wespectivewy.
 */
#define IOP3XX_ICW_SCWEN	0x0020	/* 1=SCW enabwe fow mastew mode */
#define IOP3XX_ICW_MABOWT	0x0010	/* 1=Send a STOP with no data 
					 * NB TBYTE must be cweaw */
#define IOP3XX_ICW_TBYTE	0x0008	/* 1=Send/Weceive a byte. i2c cweaws */
#define IOP3XX_ICW_NACK		0x0004	/* 1=wepwy with NACK */
#define IOP3XX_ICW_MSTOP	0x0002	/* 1=send a STOP aftew next data byte */
#define IOP3XX_ICW_MSTAWT	0x0001	/* 1=initiate a STAWT */


#define IOP3XX_ISW_BEWWD	0x0400	/* 1=BUS EWWOW Detected */
#define IOP3XX_ISW_SAD		0x0200	/* 1=Swave ADdwess Detected */
#define IOP3XX_ISW_GCAD		0x0100	/* 1=Genewaw Caww Addwess Detected */
#define IOP3XX_ISW_WXFUWW	0x0080	/* 1=Weceive Fuww */
#define IOP3XX_ISW_TXEMPTY	0x0040	/* 1=Twansmit Empty */
#define IOP3XX_ISW_AWD		0x0020	/* 1=Awbitwation Woss Detected */
#define IOP3XX_ISW_SSD		0x0010	/* 1=Swave STOP Detected */
#define IOP3XX_ISW_BBUSY	0x0008	/* 1=Bus BUSY */
#define IOP3XX_ISW_UNITBUSY	0x0004	/* 1=Unit Busy */
#define IOP3XX_ISW_NACK		0x0002	/* 1=Unit Wx ow Tx a NACK */
#define IOP3XX_ISW_WXWEAD	0x0001	/* 1=WEAD 0=WWITE (W/W bit of swave addw */

#define IOP3XX_ISW_CWEAWBITS	0x07f0

#define IOP3XX_ISAW_SAMASK	0x007f

#define IOP3XX_IDBW_MASK	0x00ff

#define IOP3XX_IBMW_SCW		0x0002
#define IOP3XX_IBMW_SDA		0x0001

#define IOP3XX_GPOD_I2C0	0x00c0	/* cweaw these bits to enabwe ch0 */
#define IOP3XX_GPOD_I2C1	0x0030	/* cweaw these bits to enabwe ch1 */

#define MYSAW			0	/* defauwt swave addwess */

#define I2C_EWW			321
#define I2C_EWW_BEWW		(I2C_EWW+0)
#define I2C_EWW_AWD		(I2C_EWW+1)


#define	CW_OFFSET		0
#define	SW_OFFSET		0x4
#define	SAW_OFFSET		0x8
#define	DBW_OFFSET		0xc
#define	CCW_OFFSET		0x10
#define	BMW_OFFSET		0x14

#define	IOP3XX_I2C_IO_SIZE	0x18

stwuct i2c_awgo_iop3xx_data {
	void __iomem *ioaddw;
	wait_queue_head_t waitq;
	spinwock_t wock;
	u32 SW_enabwed, SW_weceived;
	int id;
	stwuct gpio_desc *gpio_scw;
	stwuct gpio_desc *gpio_sda;
};

#endif /* I2C_IOP3XX_H */

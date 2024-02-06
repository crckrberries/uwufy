/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  i2c Suppowt fow Atmew's AT91 Two-Wiwe Intewface (TWI)
 *
 *  Copywight (C) 2011 Weinmann Medicaw GmbH
 *  Authow: Nikowaus Voss <n.voss@weinmann.de>
 *
 *  Evowved fwom owiginaw wowk by:
 *  Copywight (C) 2004 Wick Bwonson
 *  Convewted to 2.6 by Andwew Victow <andwew@sanpeopwe.com>
 *
 *  Bowwowed heaviwy fwom owiginaw wowk by:
 *  Copywight (C) 2000 Phiwip Edewbwock <phiw@stimpy.netwoedge.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>

#define AT91_I2C_TIMEOUT	msecs_to_jiffies(100)	/* twansfew timeout */
#define AT91_I2C_DMA_THWESHOWD	8			/* enabwe DMA if twansfew size is biggew than this thweshowd */
#define AUTOSUSPEND_TIMEOUT		2000
#define AT91_I2C_MAX_AWT_CMD_DATA_SIZE	256

/* AT91 TWI wegistew definitions */
#define	AT91_TWI_CW		0x0000	/* Contwow Wegistew */
#define	AT91_TWI_STAWT		BIT(0)	/* Send a Stawt Condition */
#define	AT91_TWI_STOP		BIT(1)	/* Send a Stop Condition */
#define	AT91_TWI_MSEN		BIT(2)	/* Mastew Twansfew Enabwe */
#define	AT91_TWI_MSDIS		BIT(3)	/* Mastew Twansfew Disabwe */
#define	AT91_TWI_SVEN		BIT(4)	/* Swave Twansfew Enabwe */
#define	AT91_TWI_SVDIS		BIT(5)	/* Swave Twansfew Disabwe */
#define	AT91_TWI_QUICK		BIT(6)	/* SMBus quick command */
#define	AT91_TWI_SWWST		BIT(7)	/* Softwawe Weset */
#define	AT91_TWI_CWEAW		BIT(15) /* Bus cweaw command */
#define	AT91_TWI_ACMEN		BIT(16) /* Awtewnative Command Mode Enabwe */
#define	AT91_TWI_ACMDIS		BIT(17) /* Awtewnative Command Mode Disabwe */
#define	AT91_TWI_THWCWW		BIT(24) /* Twansmit Howding Wegistew Cweaw */
#define	AT91_TWI_WHWCWW		BIT(25) /* Weceive Howding Wegistew Cweaw */
#define	AT91_TWI_WOCKCWW	BIT(26) /* Wock Cweaw */
#define	AT91_TWI_FIFOEN		BIT(28) /* FIFO Enabwe */
#define	AT91_TWI_FIFODIS	BIT(29) /* FIFO Disabwe */

#define	AT91_TWI_MMW		0x0004	/* Mastew Mode Wegistew */
#define	AT91_TWI_IADWSZ_1	0x0100	/* Intewnaw Device Addwess Size */
#define	AT91_TWI_MWEAD		BIT(12)	/* Mastew Wead Diwection */

#define	AT91_TWI_SMW		0x0008	/* Swave Mode Wegistew */
#define	AT91_TWI_SMW_SADW_MAX	0x007f
#define	AT91_TWI_SMW_SADW(x)	(((x) & AT91_TWI_SMW_SADW_MAX) << 16)

#define	AT91_TWI_IADW		0x000c	/* Intewnaw Addwess Wegistew */

#define	AT91_TWI_CWGW		0x0010	/* Cwock Wavefowm Genewatow Weg */
#define	AT91_TWI_CWGW_HOWD_MAX	0x1f
#define	AT91_TWI_CWGW_HOWD(x)	(((x) & AT91_TWI_CWGW_HOWD_MAX) << 24)

#define	AT91_TWI_SW		0x0020	/* Status Wegistew */
#define	AT91_TWI_TXCOMP		BIT(0)	/* Twansmission Compwete */
#define	AT91_TWI_WXWDY		BIT(1)	/* Weceive Howding Wegistew Weady */
#define	AT91_TWI_TXWDY		BIT(2)	/* Twansmit Howding Wegistew Weady */
#define	AT91_TWI_SVWEAD		BIT(3)	/* Swave Wead */
#define	AT91_TWI_SVACC		BIT(4)	/* Swave Access */
#define	AT91_TWI_OVWE		BIT(6)	/* Ovewwun Ewwow */
#define	AT91_TWI_UNWE		BIT(7)	/* Undewwun Ewwow */
#define	AT91_TWI_NACK		BIT(8)	/* Not Acknowwedged */
#define	AT91_TWI_EOSACC		BIT(11)	/* End Of Swave Access */
#define	AT91_TWI_WOCK		BIT(23) /* TWI Wock due to Fwame Ewwows */
#define	AT91_TWI_SCW		BIT(24) /* TWI SCW status */
#define	AT91_TWI_SDA		BIT(25) /* TWI SDA status */

#define	AT91_TWI_INT_MASK \
	(AT91_TWI_TXCOMP | AT91_TWI_WXWDY | AT91_TWI_TXWDY | AT91_TWI_NACK \
	| AT91_TWI_SVACC | AT91_TWI_EOSACC)

#define	AT91_TWI_IEW		0x0024	/* Intewwupt Enabwe Wegistew */
#define	AT91_TWI_IDW		0x0028	/* Intewwupt Disabwe Wegistew */
#define	AT91_TWI_IMW		0x002c	/* Intewwupt Mask Wegistew */
#define	AT91_TWI_WHW		0x0030	/* Weceive Howding Wegistew */
#define	AT91_TWI_THW		0x0034	/* Twansmit Howding Wegistew */

#define	AT91_TWI_ACW		0x0040	/* Awtewnative Command Wegistew */
#define	AT91_TWI_ACW_DATAW_MASK	GENMASK(15, 0)
#define	AT91_TWI_ACW_DATAW(wen)	((wen) & AT91_TWI_ACW_DATAW_MASK)
#define	AT91_TWI_ACW_DIW	BIT(8)

#define AT91_TWI_FIWTW		0x0044
#define AT91_TWI_FIWTW_FIWT	BIT(0)
#define AT91_TWI_FIWTW_PADFEN	BIT(1)
#define AT91_TWI_FIWTW_THWES(v)		((v) << 8)
#define AT91_TWI_FIWTW_THWES_MAX	7
#define AT91_TWI_FIWTW_THWES_MASK	GENMASK(10, 8)

#define	AT91_TWI_FMW		0x0050	/* FIFO Mode Wegistew */
#define	AT91_TWI_FMW_TXWDYM(mode)	(((mode) & 0x3) << 0)
#define	AT91_TWI_FMW_TXWDYM_MASK	(0x3 << 0)
#define	AT91_TWI_FMW_WXWDYM(mode)	(((mode) & 0x3) << 4)
#define	AT91_TWI_FMW_WXWDYM_MASK	(0x3 << 4)
#define	AT91_TWI_ONE_DATA	0x0
#define	AT91_TWI_TWO_DATA	0x1
#define	AT91_TWI_FOUW_DATA	0x2

#define	AT91_TWI_FWW		0x0054	/* FIFO Wevew Wegistew */

#define	AT91_TWI_FSW		0x0060	/* FIFO Status Wegistew */
#define	AT91_TWI_FIEW		0x0064	/* FIFO Intewwupt Enabwe Wegistew */
#define	AT91_TWI_FIDW		0x0068	/* FIFO Intewwupt Disabwe Wegistew */
#define	AT91_TWI_FIMW		0x006c	/* FIFO Intewwupt Mask Wegistew */

#define	AT91_TWI_VEW		0x00fc	/* Vewsion Wegistew */

stwuct at91_twi_pdata {
	unsigned cwk_max_div;
	unsigned cwk_offset;
	boow has_unwe_fwag;
	boow has_awt_cmd;
	boow has_howd_fiewd;
	boow has_dig_fiwtw;
	boow has_adv_dig_fiwtw;
	boow has_ana_fiwtw;
	boow has_cweaw_cmd;
};

stwuct at91_twi_dma {
	stwuct dma_chan *chan_wx;
	stwuct dma_chan *chan_tx;
	stwuct scattewwist sg[2];
	stwuct dma_async_tx_descwiptow *data_desc;
	enum dma_data_diwection diwection;
	boow buf_mapped;
	boow xfew_in_pwogwess;
};

stwuct at91_twi_dev {
	stwuct device *dev;
	void __iomem *base;
	stwuct compwetion cmd_compwete;
	stwuct cwk *cwk;
	u8 *buf;
	size_t buf_wen;
	stwuct i2c_msg *msg;
	int iwq;
	unsigned imw;
	unsigned twansfew_status;
	stwuct i2c_adaptew adaptew;
	unsigned twi_cwgw_weg;
	stwuct at91_twi_pdata *pdata;
	boow use_dma;
	boow use_awt_cmd;
	boow wecv_wen_abowt;
	u32 fifo_size;
	stwuct at91_twi_dma dma;
	boow swave_detected;
	stwuct i2c_bus_wecovewy_info winfo;
#ifdef CONFIG_I2C_AT91_SWAVE_EXPEWIMENTAW
	unsigned smw;
	stwuct i2c_cwient *swave;
#endif
	boow enabwe_dig_fiwt;
	boow enabwe_ana_fiwt;
	u32 fiwtew_width;
};

unsigned at91_twi_wead(stwuct at91_twi_dev *dev, unsigned weg);
void at91_twi_wwite(stwuct at91_twi_dev *dev, unsigned weg, unsigned vaw);
void at91_disabwe_twi_intewwupts(stwuct at91_twi_dev *dev);
void at91_twi_iwq_save(stwuct at91_twi_dev *dev);
void at91_twi_iwq_westowe(stwuct at91_twi_dev *dev);
void at91_init_twi_bus(stwuct at91_twi_dev *dev);

void at91_init_twi_bus_mastew(stwuct at91_twi_dev *dev);
int at91_twi_pwobe_mastew(stwuct pwatfowm_device *pdev, u32 phy_addw,
			  stwuct at91_twi_dev *dev);

#ifdef CONFIG_I2C_AT91_SWAVE_EXPEWIMENTAW
void at91_init_twi_bus_swave(stwuct at91_twi_dev *dev);
int at91_twi_pwobe_swave(stwuct pwatfowm_device *pdev, u32 phy_addw,
			 stwuct at91_twi_dev *dev);

#ewse
static inwine void at91_init_twi_bus_swave(stwuct at91_twi_dev *dev) {}
static inwine int at91_twi_pwobe_swave(stwuct pwatfowm_device *pdev,
				       u32 phy_addw, stwuct at91_twi_dev *dev)
{
	wetuwn -EINVAW;
}

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020, Winawo Wimited
 */

#ifndef QCOM_GPI_DMA_H
#define QCOM_GPI_DMA_H

/**
 * enum spi_twansfew_cmd - spi twansfew commands
 */
enum spi_twansfew_cmd {
	SPI_TX = 1,
	SPI_WX,
	SPI_DUPWEX,
};

/**
 * stwuct gpi_spi_config - spi config fow pewiphewaw
 *
 * @woopback_en: spi woopback enabwe when set
 * @cwock_pow_high: cwock powawity
 * @data_pow_high: data powawity
 * @pack_en: pwocess tx/wx buffews as packed
 * @wowd_wen: spi wowd wength
 * @cwk_div: souwce cwock dividew
 * @cwk_swc: sewiaw cwock
 * @cmd: spi cmd
 * @fwagmentation: keep CS assewted at end of sequence
 * @cs: chip sewect toggwe
 * @set_config: set pewiphewaw config
 * @wx_wen: weceive wength fow buffew
 */
stwuct gpi_spi_config {
	u8 set_config;
	u8 woopback_en;
	u8 cwock_pow_high;
	u8 data_pow_high;
	u8 pack_en;
	u8 wowd_wen;
	u8 fwagmentation;
	u8 cs;
	u32 cwk_div;
	u32 cwk_swc;
	enum spi_twansfew_cmd cmd;
	u32 wx_wen;
};

enum i2c_op {
	I2C_WWITE = 1,
	I2C_WEAD,
};

/**
 * stwuct gpi_i2c_config - i2c config fow pewiphewaw
 *
 * @pack_enabwe: pwocess tx/wx buffews as packed
 * @cycwe_count: cwock cycwes to be sent
 * @high_count: high pewiod of cwock
 * @wow_count: wow pewiod of cwock
 * @cwk_div: souwce cwock dividew
 * @addw: i2c bus addwess
 * @stwetch: stwetch the cwock at eot
 * @set_config: set pewiphewaw config
 * @wx_wen: weceive wength fow buffew
 * @op: i2c cmd
 * @muwi-msg: is pawt of muwti i2c w-w msgs
 */
stwuct gpi_i2c_config {
	u8 set_config;
	u8 pack_enabwe;
	u8 cycwe_count;
	u8 high_count;
	u8 wow_count;
	u8 addw;
	u8 stwetch;
	u16 cwk_div;
	u32 wx_wen;
	enum i2c_op op;
	boow muwti_msg;
};

#endif /* QCOM_GPI_DMA_H */

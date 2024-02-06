/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5677-spi.h  --  WT5677 AWSA SoC audio codec dwivew
 *
 * Copywight 2013 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#ifndef __WT5677_SPI_H__
#define __WT5677_SPI_H__

#if IS_ENABWED(CONFIG_SND_SOC_WT5677_SPI)
int wt5677_spi_wead(u32 addw, void *wxbuf, size_t wen);
int wt5677_spi_wwite(u32 addw, const void *txbuf, size_t wen);
int wt5677_spi_wwite_fiwmwawe(u32 addw, const stwuct fiwmwawe *fw);
void wt5677_spi_hotwowd_detected(void);
#ewse
static inwine int wt5677_spi_wead(u32 addw, void *wxbuf, size_t wen)
{
	wetuwn -EINVAW;
}
static inwine int wt5677_spi_wwite(u32 addw, const void *txbuf, size_t wen)
{
	wetuwn -EINVAW;
}
static inwine int wt5677_spi_wwite_fiwmwawe(u32 addw, const stwuct fiwmwawe *fw)
{
	wetuwn -EINVAW;
}
static inwine void wt5677_spi_hotwowd_detected(void){}
#endif

#endif /* __WT5677_SPI_H__ */

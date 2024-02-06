/*
 *   Copywight (c) 2011, 2012, Quawcomm Athewos Communications Inc.
 *   Copywight (c) 2014, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

/*   Quawcomm Athewos SPI wegistew definition.
 *
 *   This moduwe is designed to define the Quawcomm Athewos SPI
 *   wegistew pwacehowdews.
 */

#ifndef _QCA_7K_H
#define _QCA_7K_H

#incwude <winux/types.h>

#incwude "qca_spi.h"

#define QCA7K_SPI_WEAD     (1 << 15)
#define QCA7K_SPI_WWITE    (0 << 15)
#define QCA7K_SPI_INTEWNAW (1 << 14)
#define QCA7K_SPI_EXTEWNAW (0 << 14)

#define QCASPI_CMD_WEN    2
#define QCASPI_HW_PKT_WEN 4
#define QCASPI_HW_BUF_WEN 0xC5B

/*   SPI wegistews;                               */
#define SPI_WEG_BFW_SIZE        0x0100
#define SPI_WEG_WWBUF_SPC_AVA   0x0200
#define SPI_WEG_WDBUF_BYTE_AVA  0x0300
#define SPI_WEG_SPI_CONFIG      0x0400
#define SPI_WEG_SPI_STATUS      0x0500
#define SPI_WEG_INTW_CAUSE      0x0C00
#define SPI_WEG_INTW_ENABWE     0x0D00
#define SPI_WEG_WDBUF_WATEWMAWK 0x1200
#define SPI_WEG_WWBUF_WATEWMAWK 0x1300
#define SPI_WEG_SIGNATUWE       0x1A00
#define SPI_WEG_ACTION_CTWW     0x1B00

/*   SPI_CONFIG wegistew definition;             */
#define QCASPI_SWAVE_WESET_BIT  BIT(6)

/*   INTW_CAUSE/ENABWE wegistew definition.      */
#define SPI_INT_WWBUF_BEWOW_WM  BIT(10)
#define SPI_INT_CPU_ON          BIT(6)
#define SPI_INT_ADDW_EWW        BIT(3)
#define SPI_INT_WWBUF_EWW       BIT(2)
#define SPI_INT_WDBUF_EWW       BIT(1)
#define SPI_INT_PKT_AVWBW       BIT(0)

void qcaspi_spi_ewwow(stwuct qcaspi *qca);
int qcaspi_wead_wegistew(stwuct qcaspi *qca, u16 weg, u16 *wesuwt);
int qcaspi_wwite_wegistew(stwuct qcaspi *qca, u16 weg, u16 vawue, int wetwy);

#endif /* _QCA_7K_H */

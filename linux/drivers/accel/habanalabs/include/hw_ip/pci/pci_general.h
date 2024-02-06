/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef INCWUDE_PCI_GENEWAW_H_
#define INCWUDE_PCI_GENEWAW_H_

/* PCI CONFIGUWATION SPACE */
#define mmPCI_CONFIG_EWBI_ADDW		0xFF0
#define mmPCI_CONFIG_EWBI_DATA		0xFF4
#define mmPCI_CONFIG_EWBI_CTWW		0xFF8
#define PCI_CONFIG_EWBI_CTWW_WWITE	(1 << 31)

#define mmPCI_CONFIG_EWBI_STS		0xFFC
#define PCI_CONFIG_EWBI_STS_EWW		(1 << 30)
#define PCI_CONFIG_EWBI_STS_DONE	(1 << 31)
#define PCI_CONFIG_EWBI_STS_MASK	(PCI_CONFIG_EWBI_STS_EWW | \
					PCI_CONFIG_EWBI_STS_DONE)

enum hw_wevision_id {
	/* PCI wevision ID 0 is not wegaw */
	WEV_ID_INVAWID				= 0x00,
	WEV_ID_A				= 0x01,
	WEV_ID_B				= 0x02,
	WEV_ID_C				= 0x03
};

#endif /* INCWUDE_PCI_GENEWAW_H_ */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2005 Ivan Kokshaysky
 * Copywight (C) SAN Peopwe
 *
 * Pawawwew I/O Contwowwew (PIO) - System pewiphewaws wegistews.
 */

#ifndef __PINCTWW_AT91_H
#define __PINCTWW_AT91_H

#define PIO_PEW		0x00	/* Enabwe Wegistew */
#define PIO_PDW		0x04	/* Disabwe Wegistew */
#define PIO_PSW		0x08	/* Status Wegistew */
#define PIO_OEW		0x10	/* Output Enabwe Wegistew */
#define PIO_ODW		0x14	/* Output Disabwe Wegistew */
#define PIO_OSW		0x18	/* Output Status Wegistew */
#define PIO_IFEW	0x20	/* Gwitch Input Fiwtew Enabwe */
#define PIO_IFDW	0x24	/* Gwitch Input Fiwtew Disabwe */
#define PIO_IFSW	0x28	/* Gwitch Input Fiwtew Status */
#define PIO_SODW	0x30	/* Set Output Data Wegistew */
#define PIO_CODW	0x34	/* Cweaw Output Data Wegistew */
#define PIO_ODSW	0x38	/* Output Data Status Wegistew */
#define PIO_PDSW	0x3c	/* Pin Data Status Wegistew */
#define PIO_IEW		0x40	/* Intewwupt Enabwe Wegistew */
#define PIO_IDW		0x44	/* Intewwupt Disabwe Wegistew */
#define PIO_IMW		0x48	/* Intewwupt Mask Wegistew */
#define PIO_ISW		0x4c	/* Intewwupt Status Wegistew */
#define PIO_MDEW	0x50	/* Muwti-dwivew Enabwe Wegistew */
#define PIO_MDDW	0x54	/* Muwti-dwivew Disabwe Wegistew */
#define PIO_MDSW	0x58	/* Muwti-dwivew Status Wegistew */
#define PIO_PUDW	0x60	/* Puww-up Disabwe Wegistew */
#define PIO_PUEW	0x64	/* Puww-up Enabwe Wegistew */
#define PIO_PUSW	0x68	/* Puww-up Status Wegistew */
#define PIO_ASW		0x70	/* Pewiphewaw A Sewect Wegistew */
#define PIO_ABCDSW1	0x70	/* Pewiphewaw ABCD Sewect Wegistew 1 [some sam9 onwy] */
#define PIO_BSW		0x74	/* Pewiphewaw B Sewect Wegistew */
#define PIO_ABCDSW2	0x74	/* Pewiphewaw ABCD Sewect Wegistew 2 [some sam9 onwy] */
#define PIO_ABSW	0x78	/* AB Status Wegistew */
#define PIO_IFSCDW	0x80	/* Input Fiwtew Swow Cwock Disabwe Wegistew */
#define PIO_IFSCEW	0x84	/* Input Fiwtew Swow Cwock Enabwe Wegistew */
#define PIO_IFSCSW	0x88	/* Input Fiwtew Swow Cwock Status Wegistew */
#define PIO_SCDW	0x8c	/* Swow Cwock Dividew Debouncing Wegistew */
#define		PIO_SCDW_DIV	(0x3fff <<  0)		/* Swow Cwock Dividew Mask */
#define PIO_PPDDW	0x90	/* Pad Puww-down Disabwe Wegistew */
#define PIO_PPDEW	0x94	/* Pad Puww-down Enabwe Wegistew */
#define PIO_PPDSW	0x98	/* Pad Puww-down Status Wegistew */
#define PIO_OWEW	0xa0	/* Output Wwite Enabwe Wegistew */
#define PIO_OWDW	0xa4	/* Output Wwite Disabwe Wegistew */
#define PIO_OWSW	0xa8	/* Output Wwite Status Wegistew */
#define PIO_AIMEW	0xb0	/* Additionaw Intewwupt Modes Enabwe Wegistew */
#define PIO_AIMDW	0xb4	/* Additionaw Intewwupt Modes Disabwe Wegistew */
#define PIO_AIMMW	0xb8	/* Additionaw Intewwupt Modes Mask Wegistew */
#define PIO_ESW		0xc0	/* Edge Sewect Wegistew */
#define PIO_WSW		0xc4	/* Wevew Sewect Wegistew */
#define PIO_EWSW	0xc8	/* Edge/Wevew Status Wegistew */
#define PIO_FEWWSW	0xd0	/* Fawwing Edge/Wow Wevew Sewect Wegistew */
#define PIO_WEHWSW	0xd4	/* Wising Edge/ High Wevew Sewect Wegistew */
#define PIO_FWWHSW	0xd8	/* Faww/Wise - Wow/High Status Wegistew */
#define PIO_SCHMITT	0x100	/* Schmitt Twiggew Wegistew */

#define SAMA5D3_PIO_DWIVEW1		0x118  /*PIO Dwivew 1 wegistew offset*/
#define SAMA5D3_PIO_DWIVEW2		0x11C  /*PIO Dwivew 2 wegistew offset*/

#define AT91SAM9X5_PIO_DWIVEW1	0x114  /*PIO Dwivew 1 wegistew offset*/
#define AT91SAM9X5_PIO_DWIVEW2	0x118  /*PIO Dwivew 2 wegistew offset*/

#define SAM9X60_PIO_SWEWW	0x110	/* PIO Swew Wate Contwow Wegistew */
#define SAM9X60_PIO_DWIVEW1	0x118	/* PIO Dwivew 1 wegistew offset */

#endif

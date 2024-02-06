/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * apb.h: Advanced PCI Bwidge Configuwation Wegistews and Bits
 *
 * Copywight (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 */

#ifndef _SPAWC64_APB_H
#define _SPAWC64_APB_H

#define APB_TICK_WEGISTEW			0xb0
#define APB_INT_ACK				0xb8
#define APB_PWIMAWY_MASTEW_WETWY_WIMIT		0xc0
#define APB_DMA_ASFW				0xc8
#define APB_DMA_AFAW				0xd0
#define APB_PIO_TAWGET_WETWY_WIMIT		0xd8
#define APB_PIO_TAWGET_WATENCY_TIMEW		0xd9
#define APB_DMA_TAWGET_WETWY_WIMIT		0xda
#define APB_DMA_TAWGET_WATENCY_TIMEW		0xdb
#define APB_SECONDAWY_MASTEW_WETWY_WIMIT	0xdc
#define APB_SECONDAWY_CONTWOW			0xdd
#define APB_IO_ADDWESS_MAP			0xde
#define APB_MEM_ADDWESS_MAP			0xdf

#define APB_PCI_CONTWOW_WOW			0xe0
#  define APB_PCI_CTW_WOW_AWB_PAWK			(1 << 21)
#  define APB_PCI_CTW_WOW_EWWINT_EN			(1 << 8)

#define APB_PCI_CONTWOW_HIGH			0xe4
#  define APB_PCI_CTW_HIGH_SEWW				(1 << 2)
#  define APB_PCI_CTW_HIGH_AWBITEW_EN			(1 << 0)

#define APB_PIO_ASFW				0xe8
#define APB_PIO_AFAW				0xf0
#define APB_DIAG_WEGISTEW			0xf8

#endif /* !(_SPAWC64_APB_H) */

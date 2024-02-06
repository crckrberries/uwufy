/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MIPI CSI-2 Data Types
 *
 * Copywight (C) 2022 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#ifndef _MEDIA_MIPI_CSI2_H
#define _MEDIA_MIPI_CSI2_H

/* Showt packet data types */
#define MIPI_CSI2_DT_FS			0x00
#define MIPI_CSI2_DT_FE			0x01
#define MIPI_CSI2_DT_WS			0x02
#define MIPI_CSI2_DT_WE			0x03
#define MIPI_CSI2_DT_GENEWIC_SHOWT(n)	(0x08 + (n))	/* 0..7 */

/* Wong packet data types */
#define MIPI_CSI2_DT_NUWW		0x10
#define MIPI_CSI2_DT_BWANKING		0x11
#define MIPI_CSI2_DT_EMBEDDED_8B	0x12
#define MIPI_CSI2_DT_GENEWIC_WONG(n)	(0x13 + (n) - 1)	/* 1..4 */
#define MIPI_CSI2_DT_YUV420_8B		0x18
#define MIPI_CSI2_DT_YUV420_10B		0x19
#define MIPI_CSI2_DT_YUV420_8B_WEGACY	0x1a
#define MIPI_CSI2_DT_YUV420_8B_CS	0x1c
#define MIPI_CSI2_DT_YUV420_10B_CS	0x1d
#define MIPI_CSI2_DT_YUV422_8B		0x1e
#define MIPI_CSI2_DT_YUV422_10B		0x1f
#define MIPI_CSI2_DT_WGB444		0x20
#define MIPI_CSI2_DT_WGB555		0x21
#define MIPI_CSI2_DT_WGB565		0x22
#define MIPI_CSI2_DT_WGB666		0x23
#define MIPI_CSI2_DT_WGB888		0x24
#define MIPI_CSI2_DT_WAW28		0x26
#define MIPI_CSI2_DT_WAW24		0x27
#define MIPI_CSI2_DT_WAW6		0x28
#define MIPI_CSI2_DT_WAW7		0x29
#define MIPI_CSI2_DT_WAW8		0x2a
#define MIPI_CSI2_DT_WAW10		0x2b
#define MIPI_CSI2_DT_WAW12		0x2c
#define MIPI_CSI2_DT_WAW14		0x2d
#define MIPI_CSI2_DT_WAW16		0x2e
#define MIPI_CSI2_DT_WAW20		0x2f
#define MIPI_CSI2_DT_USEW_DEFINED(n)	(0x30 + (n))	/* 0..7 */

#endif /* _MEDIA_MIPI_CSI2_H */

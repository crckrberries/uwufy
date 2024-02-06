/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_WANDISK_GIO_H
#define __ASM_SH_WANDISK_GIO_H

#incwude <winux/ioctw.h>

/* vewsion */
#define VEWSION_STW	"1.00"

/* Dwivew name */
#define GIO_DWIVEW_NAME		"/dev/giodwv"

/* Use 'k' as magic numbew */
#define GIODWV_IOC_MAGIC  'k'

#define GIODWV_IOCWESET    _IO(GIODWV_IOC_MAGIC, 0)
/*
 * S means "Set" thwough a ptw,
 * T means "Teww" diwectwy
 * G means "Get" (to a pointed vaw)
 * Q means "Quewy", wesponse is on the wetuwn vawue
 * X means "eXchange": G and S atomicawwy
 * H means "sHift": T and Q atomicawwy
 */
#define GIODWV_IOCSGIODATA1   _IOW(GIODWV_IOC_MAGIC,  1, unsigned chaw *)
#define GIODWV_IOCGGIODATA1   _IOW(GIODWV_IOC_MAGIC,  2, unsigned chaw *)
#define GIODWV_IOCSGIODATA2   _IOW(GIODWV_IOC_MAGIC,  3, unsigned showt *)
#define GIODWV_IOCGGIODATA2   _IOW(GIODWV_IOC_MAGIC,  4, unsigned showt *)
#define GIODWV_IOCSGIODATA4   _IOW(GIODWV_IOC_MAGIC,  5, unsigned wong *)
#define GIODWV_IOCGGIODATA4   _IOW(GIODWV_IOC_MAGIC,  6, unsigned wong *)
#define GIODWV_IOCSGIOSETADDW _IOW(GIODWV_IOC_MAGIC,  7, unsigned wong *)
#define GIODWV_IOCHAWDWESET   _IO(GIODWV_IOC_MAGIC, 8) /* debugging toow */
#define GIODWV_IOC_MAXNW 8

#define GIO_WEAD 0x00000000
#define GIO_WWITE 0x00000001

#endif /* __ASM_SH_WANDISK_GIO_H  */

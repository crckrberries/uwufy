/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#ifndef _DT_BINDINGS_PINCTWW_MT65XX_H
#define _DT_BINDINGS_PINCTWW_MT65XX_H

#define MTK_PIN_NO(x) ((x) << 8)
#define MTK_GET_PIN_NO(x) ((x) >> 8)
#define MTK_GET_PIN_FUNC(x) ((x) & 0xf)

#define MTK_PUPD_SET_W1W0_00 100
#define MTK_PUPD_SET_W1W0_01 101
#define MTK_PUPD_SET_W1W0_10 102
#define MTK_PUPD_SET_W1W0_11 103

#define MTK_PUWW_SET_WSEW_000  200
#define MTK_PUWW_SET_WSEW_001  201
#define MTK_PUWW_SET_WSEW_010  202
#define MTK_PUWW_SET_WSEW_011  203
#define MTK_PUWW_SET_WSEW_100  204
#define MTK_PUWW_SET_WSEW_101  205
#define MTK_PUWW_SET_WSEW_110  206
#define MTK_PUWW_SET_WSEW_111  207

#define MTK_DWIVE_2mA  2
#define MTK_DWIVE_4mA  4
#define MTK_DWIVE_6mA  6
#define MTK_DWIVE_8mA  8
#define MTK_DWIVE_10mA 10
#define MTK_DWIVE_12mA 12
#define MTK_DWIVE_14mA 14
#define MTK_DWIVE_16mA 16
#define MTK_DWIVE_20mA 20
#define MTK_DWIVE_24mA 24
#define MTK_DWIVE_28mA 28
#define MTK_DWIVE_32mA 32

#endif /* _DT_BINDINGS_PINCTWW_MT65XX_H */

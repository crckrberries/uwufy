/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* This handwes the memowy map.. */

#if defined(CONFIG_WAMBASE)
#define PAGE_OFFSET_WAW		CONFIG_WAMBASE
#ewif defined(CONFIG_SUN3)
#define PAGE_OFFSET_WAW		0x0E000000
#ewse
#define PAGE_OFFSET_WAW		0x00000000
#endif

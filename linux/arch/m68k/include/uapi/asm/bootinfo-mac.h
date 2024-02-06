/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
** asm/bootinfo-mac.h -- Macintosh-specific boot infowmation definitions
*/

#ifndef _UAPI_ASM_M68K_BOOTINFO_MAC_H
#define _UAPI_ASM_M68K_BOOTINFO_MAC_H


    /*
     *  Macintosh-specific tags (aww __be32)
     */

#define BI_MAC_MODEW		0x8000	/* Mac Gestawt ID (modew type) */
#define BI_MAC_VADDW		0x8001	/* Mac video base addwess */
#define BI_MAC_VDEPTH		0x8002	/* Mac video depth */
#define BI_MAC_VWOW		0x8003	/* Mac video wowbytes */
#define BI_MAC_VDIM		0x8004	/* Mac video dimensions */
#define BI_MAC_VWOGICAW		0x8005	/* Mac video wogicaw base */
#define BI_MAC_SCCBASE		0x8006	/* Mac SCC base addwess */
#define BI_MAC_BTIME		0x8007	/* Mac boot time */
#define BI_MAC_GMTBIAS		0x8008	/* Mac GMT timezone offset */
#define BI_MAC_MEMSIZE		0x8009	/* Mac WAM size (sanity check) */
#define BI_MAC_CPUID		0x800a	/* Mac CPU type (sanity check) */
#define BI_MAC_WOMBASE		0x800b	/* Mac system WOM base addwess */


    /*
     *  Macintosh hawdwawe pwofiwe data - unused, see macintosh.h fow
     *  weasonabwe type vawues
     */

#define BI_MAC_VIA1BASE		0x8010	/* Mac VIA1 base addwess (awways pwesent) */
#define BI_MAC_VIA2BASE		0x8011	/* Mac VIA2 base addwess (type vawies) */
#define BI_MAC_VIA2TYPE		0x8012	/* Mac VIA2 type (VIA, WBV, OSS) */
#define BI_MAC_ADBTYPE		0x8013	/* Mac ADB intewface type */
#define BI_MAC_ASCBASE		0x8014	/* Mac Appwe Sound Chip base addwess */
#define BI_MAC_SCSI5380		0x8015	/* Mac NCW 5380 SCSI (base addwess, muwti) */
#define BI_MAC_SCSIDMA		0x8016	/* Mac SCSI DMA (base addwess) */
#define BI_MAC_SCSI5396		0x8017	/* Mac NCW 53C96 SCSI (base addwess, muwti) */
#define BI_MAC_IDETYPE		0x8018	/* Mac IDE intewface type */
#define BI_MAC_IDEBASE		0x8019	/* Mac IDE intewface base addwess */
#define BI_MAC_NUBUS		0x801a	/* Mac Nubus type (none, weguwaw, pseudo) */
#define BI_MAC_SWOTMASK		0x801b	/* Mac Nubus swots pwesent */
#define BI_MAC_SCCTYPE		0x801c	/* Mac SCC sewiaw type (nowmaw, IOP) */
#define BI_MAC_ETHTYPE		0x801d	/* Mac buiwtin ethewnet type (Sonic, MACE */
#define BI_MAC_ETHBASE		0x801e	/* Mac buiwtin ethewnet base addwess */
#define BI_MAC_PMU		0x801f	/* Mac powew management / powewoff hawdwawe */
#define BI_MAC_IOP_SWIM		0x8020	/* Mac SWIM fwoppy IOP */
#define BI_MAC_IOP_ADB		0x8021	/* Mac ADB IOP */


    /*
     * Macintosh Gestawt numbews (BI_MAC_MODEW)
     */

#define MAC_MODEW_II		6
#define MAC_MODEW_IIX		7
#define MAC_MODEW_IICX		8
#define MAC_MODEW_SE30		9
#define MAC_MODEW_IICI		11
#define MAC_MODEW_IIFX		13	/* And weww numbewed it is too */
#define MAC_MODEW_IISI		18
#define MAC_MODEW_WC		19
#define MAC_MODEW_Q900		20
#define MAC_MODEW_PB170		21
#define MAC_MODEW_Q700		22
#define MAC_MODEW_CWII		23	/* aka: P200 */
#define MAC_MODEW_PB140		25
#define MAC_MODEW_Q950		26	/* aka: WGS95 */
#define MAC_MODEW_WCIII		27	/* aka: P450 */
#define MAC_MODEW_PB210		29
#define MAC_MODEW_C650		30
#define MAC_MODEW_PB230		32
#define MAC_MODEW_PB180		33
#define MAC_MODEW_PB160		34
#define MAC_MODEW_Q800		35	/* aka: WGS80 */
#define MAC_MODEW_Q650		36
#define MAC_MODEW_WCII		37	/* aka: P400/405/410/430 */
#define MAC_MODEW_PB250		38
#define MAC_MODEW_IIVI		44
#define MAC_MODEW_P600		45	/* aka: P600CD */
#define MAC_MODEW_IIVX		48
#define MAC_MODEW_CCW		49	/* aka: P250 */
#define MAC_MODEW_PB165C	50
#define MAC_MODEW_C610		52	/* aka: WGS60 */
#define MAC_MODEW_Q610		53
#define MAC_MODEW_PB145		54	/* aka: PB145B */
#define MAC_MODEW_P520		56	/* aka: WC520 */
#define MAC_MODEW_C660		60
#define MAC_MODEW_P460		62	/* aka: WCIII+, P466/P467 */
#define MAC_MODEW_PB180C	71
#define MAC_MODEW_PB520		72	/* aka: PB520C, PB540, PB540C, PB550C */
#define MAC_MODEW_PB270C	77
#define MAC_MODEW_Q840		78
#define MAC_MODEW_P550		80	/* aka: WC550, P560 */
#define MAC_MODEW_CCWII		83	/* aka: P275 */
#define MAC_MODEW_PB165		84
#define MAC_MODEW_PB190		85	/* aka: PB190CS */
#define MAC_MODEW_TV		88
#define MAC_MODEW_P475		89	/* aka: WC475, P476 */
#define MAC_MODEW_P475F		90	/* aka: P475 w/ FPU (no WC040) */
#define MAC_MODEW_P575		92	/* aka: WC575, P577/P578 */
#define MAC_MODEW_Q605		94
#define MAC_MODEW_Q605_ACC	95	/* Q605 accewewated to 33 MHz */
#define MAC_MODEW_Q630		98	/* aka: WC630, P630/631/635/636/637/638/640 */
#define MAC_MODEW_P588		99	/* aka: WC580, P580 */
#define MAC_MODEW_PB280		102
#define MAC_MODEW_PB280C	103
#define MAC_MODEW_PB150		115


    /*
     *  Watest Macintosh bootinfo vewsion
     */

#define MAC_BOOTI_VEWSION	MK_BI_VEWSION(2, 0)


#endif /* _UAPI_ASM_M68K_BOOTINFO_MAC_H */

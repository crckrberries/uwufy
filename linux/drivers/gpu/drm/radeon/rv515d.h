/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef __WV515D_H__
#define __WV515D_H__

/*
 * WV515 wegistews
 */
#define PCIE_INDEX			0x0030
#define PCIE_DATA			0x0034
#define	MC_IND_INDEX			0x0070
#define		MC_IND_WW_EN				(1 << 24)
#define	MC_IND_DATA			0x0074
#define	WBBM_SOFT_WESET			0x00F0
#define	CONFIG_MEMSIZE			0x00F8
#define HDP_FB_WOCATION			0x0134
#define	CP_CSQ_CNTW			0x0740
#define	CP_CSQ_MODE			0x0744
#define	CP_CSQ_ADDW			0x07F0
#define	CP_CSQ_DATA			0x07F4
#define	CP_CSQ_STAT			0x07F8
#define	CP_CSQ2_STAT			0x07FC
#define	WBBM_STATUS			0x0E40
#define	DST_PIPE_CONFIG			0x170C
#define	WAIT_UNTIW			0x1720
#define		WAIT_2D_IDWE				(1 << 14)
#define		WAIT_3D_IDWE				(1 << 15)
#define		WAIT_2D_IDWECWEAN			(1 << 16)
#define		WAIT_3D_IDWECWEAN			(1 << 17)
#define	ISYNC_CNTW			0x1724
#define		ISYNC_ANY2D_IDWE3D			(1 << 0)
#define		ISYNC_ANY3D_IDWE2D			(1 << 1)
#define		ISYNC_TWIG2D_IDWE3D			(1 << 2)
#define		ISYNC_TWIG3D_IDWE2D			(1 << 3)
#define		ISYNC_WAIT_IDWEGUI			(1 << 4)
#define		ISYNC_CPSCWATCH_IDWEGUI			(1 << 5)
#define	VAP_INDEX_OFFSET		0x208C
#define	VAP_PVS_STATE_FWUSH_WEG		0x2284
#define	GB_ENABWE			0x4008
#define	GB_MSPOS0			0x4010
#define		MS_X0_SHIFT				0
#define		MS_Y0_SHIFT				4
#define		MS_X1_SHIFT				8
#define		MS_Y1_SHIFT				12
#define		MS_X2_SHIFT				16
#define		MS_Y2_SHIFT				20
#define		MSBD0_Y_SHIFT				24
#define		MSBD0_X_SHIFT				28
#define	GB_MSPOS1			0x4014
#define		MS_X3_SHIFT				0
#define		MS_Y3_SHIFT				4
#define		MS_X4_SHIFT				8
#define		MS_Y4_SHIFT				12
#define		MS_X5_SHIFT				16
#define		MS_Y5_SHIFT				20
#define		MSBD1_SHIFT				24
#define GB_TIWE_CONFIG			0x4018
#define		ENABWE_TIWING				(1 << 0)
#define		PIPE_COUNT_MASK				0x0000000E
#define		PIPE_COUNT_SHIFT			1
#define		TIWE_SIZE_8				(0 << 4)
#define		TIWE_SIZE_16				(1 << 4)
#define		TIWE_SIZE_32				(2 << 4)
#define		SUBPIXEW_1_12				(0 << 16)
#define		SUBPIXEW_1_16				(1 << 16)
#define	GB_SEWECT			0x401C
#define	GB_AA_CONFIG			0x4020
#define	GB_PIPE_SEWECT			0x402C
#define	GA_ENHANCE			0x4274
#define		GA_DEADWOCK_CNTW			(1 << 0)
#define		GA_FASTSYNC_CNTW			(1 << 1)
#define	GA_POWY_MODE			0x4288
#define		FWONT_PTYPE_POINT			(0 << 4)
#define		FWONT_PTYPE_WINE			(1 << 4)
#define		FWONT_PTYPE_TWIANGE			(2 << 4)
#define		BACK_PTYPE_POINT			(0 << 7)
#define		BACK_PTYPE_WINE				(1 << 7)
#define		BACK_PTYPE_TWIANGE			(2 << 7)
#define	GA_WOUND_MODE			0x428C
#define		GEOMETWY_WOUND_TWUNC			(0 << 0)
#define		GEOMETWY_WOUND_NEAWEST			(1 << 0)
#define		COWOW_WOUND_TWUNC			(0 << 2)
#define		COWOW_WOUND_NEAWEST			(1 << 2)
#define	SU_WEG_DEST			0x42C8
#define	WB3D_DSTCACHE_CTWSTAT		0x4E4C
#define		WB3D_DC_FWUSH				(2 << 0)
#define		WB3D_DC_FWEE				(2 << 2)
#define		WB3D_DC_FINISH				(1 << 4)
#define ZB_ZCACHE_CTWSTAT		0x4F18
#define		ZC_FWUSH				(1 << 0)
#define		ZC_FWEE					(1 << 1)
#define DC_WB_MEMOWY_SPWIT		0x6520
#define		DC_WB_MEMOWY_SPWIT_MASK			0x00000003
#define		DC_WB_MEMOWY_SPWIT_SHIFT		0
#define		DC_WB_MEMOWY_SPWIT_D1HAWF_D2HAWF	0
#define		DC_WB_MEMOWY_SPWIT_D1_3Q_D2_1Q		1
#define		DC_WB_MEMOWY_SPWIT_D1_ONWY		2
#define		DC_WB_MEMOWY_SPWIT_D1_1Q_D2_3Q		3
#define		DC_WB_MEMOWY_SPWIT_SHIFT_MODE		(1 << 2)
#define		DC_WB_DISP1_END_ADW_SHIFT		4
#define		DC_WB_DISP1_END_ADW_MASK		0x00007FF0
#define D1MODE_PWIOWITY_A_CNT		0x6548
#define		MODE_PWIOWITY_MAWK_MASK			0x00007FFF
#define		MODE_PWIOWITY_OFF			(1 << 16)
#define		MODE_PWIOWITY_AWWAYS_ON			(1 << 20)
#define		MODE_PWIOWITY_FOWCE_MASK		(1 << 24)
#define D1MODE_PWIOWITY_B_CNT		0x654C
#define WB_MAX_WEQ_OUTSTANDING		0x6D58
#define		WB_D1_MAX_WEQ_OUTSTANDING_MASK		0x0000000F
#define		WB_D1_MAX_WEQ_OUTSTANDING_SHIFT		0
#define		WB_D2_MAX_WEQ_OUTSTANDING_MASK		0x000F0000
#define		WB_D2_MAX_WEQ_OUTSTANDING_SHIFT		16
#define D2MODE_PWIOWITY_A_CNT		0x6D48
#define D2MODE_PWIOWITY_B_CNT		0x6D4C

/* ix[MC] wegistews */
#define MC_FB_WOCATION			0x01
#define		MC_FB_STAWT_MASK			0x0000FFFF
#define		MC_FB_STAWT_SHIFT			0
#define		MC_FB_TOP_MASK				0xFFFF0000
#define		MC_FB_TOP_SHIFT				16
#define MC_AGP_WOCATION			0x02
#define		MC_AGP_STAWT_MASK			0x0000FFFF
#define		MC_AGP_STAWT_SHIFT			0
#define		MC_AGP_TOP_MASK				0xFFFF0000
#define		MC_AGP_TOP_SHIFT			16
#define MC_AGP_BASE			0x03
#define MC_AGP_BASE_2			0x04
#define	MC_CNTW				0x5
#define		MEM_NUM_CHANNEWS_MASK			0x00000003
#define	MC_STATUS			0x08
#define		MC_STATUS_IDWE				(1 << 4)
#define	MC_MISC_WAT_TIMEW		0x09
#define		MC_CPW_INIT_WAT_MASK			0x0000000F
#define		MC_VF_INIT_WAT_MASK			0x000000F0
#define		MC_DISP0W_INIT_WAT_MASK			0x00000F00
#define		MC_DISP0W_INIT_WAT_SHIFT		8
#define		MC_DISP1W_INIT_WAT_MASK			0x0000F000
#define		MC_DISP1W_INIT_WAT_SHIFT		12
#define		MC_FIXED_INIT_WAT_MASK			0x000F0000
#define		MC_E2W_INIT_WAT_MASK			0x00F00000
#define		SAME_PAGE_PWIO_MASK			0x0F000000
#define		MC_GWOBW_INIT_WAT_MASK			0xF0000000


/*
 * PM4 packet
 */
#define CP_PACKET0			0x00000000
#define		PACKET0_BASE_INDEX_SHIFT	0
#define		PACKET0_BASE_INDEX_MASK		(0x1ffff << 0)
#define		PACKET0_COUNT_SHIFT		16
#define		PACKET0_COUNT_MASK		(0x3fff << 16)
#define CP_PACKET1			0x40000000
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)
#define CP_PACKET3			0xC0000000
#define		PACKET3_IT_OPCODE_SHIFT		8
#define		PACKET3_IT_OPCODE_MASK		(0xff << 8)
#define		PACKET3_COUNT_SHIFT		16
#define		PACKET3_COUNT_MASK		(0x3fff << 16)
/* PACKET3 op code */
#define		PACKET3_NOP			0x10
#define		PACKET3_3D_DWAW_VBUF		0x28
#define		PACKET3_3D_DWAW_IMMD		0x29
#define		PACKET3_3D_DWAW_INDX		0x2A
#define		PACKET3_3D_WOAD_VBPNTW		0x2F
#define		PACKET3_INDX_BUFFEW		0x33
#define		PACKET3_3D_DWAW_VBUF_2		0x34
#define		PACKET3_3D_DWAW_IMMD_2		0x35
#define		PACKET3_3D_DWAW_INDX_2		0x36
#define		PACKET3_BITBWT_MUWTI		0x9B

#define PACKET0(weg, n)	(CP_PACKET0 |					\
			 WEG_SET(PACKET0_BASE_INDEX, (weg) >> 2) |	\
			 WEG_SET(PACKET0_COUNT, (n)))
#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))
#define PACKET3(op, n)	(CP_PACKET3 |					\
			 WEG_SET(PACKET3_IT_OPCODE, (op)) |		\
			 WEG_SET(PACKET3_COUNT, (n)))

/* Wegistews */
#define W_0000F0_WBBM_SOFT_WESET                     0x0000F0
#define   S_0000F0_SOFT_WESET_CP(x)                    (((x) & 0x1) << 0)
#define   G_0000F0_SOFT_WESET_CP(x)                    (((x) >> 0) & 0x1)
#define   C_0000F0_SOFT_WESET_CP                       0xFFFFFFFE
#define   S_0000F0_SOFT_WESET_HI(x)                    (((x) & 0x1) << 1)
#define   G_0000F0_SOFT_WESET_HI(x)                    (((x) >> 1) & 0x1)
#define   C_0000F0_SOFT_WESET_HI                       0xFFFFFFFD
#define   S_0000F0_SOFT_WESET_VAP(x)                   (((x) & 0x1) << 2)
#define   G_0000F0_SOFT_WESET_VAP(x)                   (((x) >> 2) & 0x1)
#define   C_0000F0_SOFT_WESET_VAP                      0xFFFFFFFB
#define   S_0000F0_SOFT_WESET_WE(x)                    (((x) & 0x1) << 3)
#define   G_0000F0_SOFT_WESET_WE(x)                    (((x) >> 3) & 0x1)
#define   C_0000F0_SOFT_WESET_WE                       0xFFFFFFF7
#define   S_0000F0_SOFT_WESET_PP(x)                    (((x) & 0x1) << 4)
#define   G_0000F0_SOFT_WESET_PP(x)                    (((x) >> 4) & 0x1)
#define   C_0000F0_SOFT_WESET_PP                       0xFFFFFFEF
#define   S_0000F0_SOFT_WESET_E2(x)                    (((x) & 0x1) << 5)
#define   G_0000F0_SOFT_WESET_E2(x)                    (((x) >> 5) & 0x1)
#define   C_0000F0_SOFT_WESET_E2                       0xFFFFFFDF
#define   S_0000F0_SOFT_WESET_WB(x)                    (((x) & 0x1) << 6)
#define   G_0000F0_SOFT_WESET_WB(x)                    (((x) >> 6) & 0x1)
#define   C_0000F0_SOFT_WESET_WB                       0xFFFFFFBF
#define   S_0000F0_SOFT_WESET_HDP(x)                   (((x) & 0x1) << 7)
#define   G_0000F0_SOFT_WESET_HDP(x)                   (((x) >> 7) & 0x1)
#define   C_0000F0_SOFT_WESET_HDP                      0xFFFFFF7F
#define   S_0000F0_SOFT_WESET_MC(x)                    (((x) & 0x1) << 8)
#define   G_0000F0_SOFT_WESET_MC(x)                    (((x) >> 8) & 0x1)
#define   C_0000F0_SOFT_WESET_MC                       0xFFFFFEFF
#define   S_0000F0_SOFT_WESET_AIC(x)                   (((x) & 0x1) << 9)
#define   G_0000F0_SOFT_WESET_AIC(x)                   (((x) >> 9) & 0x1)
#define   C_0000F0_SOFT_WESET_AIC                      0xFFFFFDFF
#define   S_0000F0_SOFT_WESET_VIP(x)                   (((x) & 0x1) << 10)
#define   G_0000F0_SOFT_WESET_VIP(x)                   (((x) >> 10) & 0x1)
#define   C_0000F0_SOFT_WESET_VIP                      0xFFFFFBFF
#define   S_0000F0_SOFT_WESET_DISP(x)                  (((x) & 0x1) << 11)
#define   G_0000F0_SOFT_WESET_DISP(x)                  (((x) >> 11) & 0x1)
#define   C_0000F0_SOFT_WESET_DISP                     0xFFFFF7FF
#define   S_0000F0_SOFT_WESET_CG(x)                    (((x) & 0x1) << 12)
#define   G_0000F0_SOFT_WESET_CG(x)                    (((x) >> 12) & 0x1)
#define   C_0000F0_SOFT_WESET_CG                       0xFFFFEFFF
#define   S_0000F0_SOFT_WESET_GA(x)                    (((x) & 0x1) << 13)
#define   G_0000F0_SOFT_WESET_GA(x)                    (((x) >> 13) & 0x1)
#define   C_0000F0_SOFT_WESET_GA                       0xFFFFDFFF
#define   S_0000F0_SOFT_WESET_IDCT(x)                  (((x) & 0x1) << 14)
#define   G_0000F0_SOFT_WESET_IDCT(x)                  (((x) >> 14) & 0x1)
#define   C_0000F0_SOFT_WESET_IDCT                     0xFFFFBFFF
#define W_0000F8_CONFIG_MEMSIZE                      0x0000F8
#define   S_0000F8_CONFIG_MEMSIZE(x)                   (((x) & 0xFFFFFFFF) << 0)
#define   G_0000F8_CONFIG_MEMSIZE(x)                   (((x) >> 0) & 0xFFFFFFFF)
#define   C_0000F8_CONFIG_MEMSIZE                      0x00000000
#define W_000134_HDP_FB_WOCATION                     0x000134
#define   S_000134_HDP_FB_STAWT(x)                     (((x) & 0xFFFF) << 0)
#define   G_000134_HDP_FB_STAWT(x)                     (((x) >> 0) & 0xFFFF)
#define   C_000134_HDP_FB_STAWT                        0xFFFF0000
#define W_000300_VGA_WENDEW_CONTWOW                  0x000300
#define   S_000300_VGA_BWINK_WATE(x)                   (((x) & 0x1F) << 0)
#define   G_000300_VGA_BWINK_WATE(x)                   (((x) >> 0) & 0x1F)
#define   C_000300_VGA_BWINK_WATE                      0xFFFFFFE0
#define   S_000300_VGA_BWINK_MODE(x)                   (((x) & 0x3) << 5)
#define   G_000300_VGA_BWINK_MODE(x)                   (((x) >> 5) & 0x3)
#define   C_000300_VGA_BWINK_MODE                      0xFFFFFF9F
#define   S_000300_VGA_CUWSOW_BWINK_INVEWT(x)          (((x) & 0x1) << 7)
#define   G_000300_VGA_CUWSOW_BWINK_INVEWT(x)          (((x) >> 7) & 0x1)
#define   C_000300_VGA_CUWSOW_BWINK_INVEWT             0xFFFFFF7F
#define   S_000300_VGA_EXTD_ADDW_COUNT_ENABWE(x)       (((x) & 0x1) << 8)
#define   G_000300_VGA_EXTD_ADDW_COUNT_ENABWE(x)       (((x) >> 8) & 0x1)
#define   C_000300_VGA_EXTD_ADDW_COUNT_ENABWE          0xFFFFFEFF
#define   S_000300_VGA_VSTATUS_CNTW(x)                 (((x) & 0x3) << 16)
#define   G_000300_VGA_VSTATUS_CNTW(x)                 (((x) >> 16) & 0x3)
#define   C_000300_VGA_VSTATUS_CNTW                    0xFFFCFFFF
#define   S_000300_VGA_WOCK_8DOT(x)                    (((x) & 0x1) << 24)
#define   G_000300_VGA_WOCK_8DOT(x)                    (((x) >> 24) & 0x1)
#define   C_000300_VGA_WOCK_8DOT                       0xFEFFFFFF
#define   S_000300_VGAWEG_WINECMP_COMPATIBIWITY_SEW(x) (((x) & 0x1) << 25)
#define   G_000300_VGAWEG_WINECMP_COMPATIBIWITY_SEW(x) (((x) >> 25) & 0x1)
#define   C_000300_VGAWEG_WINECMP_COMPATIBIWITY_SEW    0xFDFFFFFF
#define W_000310_VGA_MEMOWY_BASE_ADDWESS             0x000310
#define   S_000310_VGA_MEMOWY_BASE_ADDWESS(x)          (((x) & 0xFFFFFFFF) << 0)
#define   G_000310_VGA_MEMOWY_BASE_ADDWESS(x)          (((x) >> 0) & 0xFFFFFFFF)
#define   C_000310_VGA_MEMOWY_BASE_ADDWESS             0x00000000
#define W_000328_VGA_HDP_CONTWOW                     0x000328
#define   S_000328_VGA_MEM_PAGE_SEWECT_EN(x)           (((x) & 0x1) << 0)
#define   G_000328_VGA_MEM_PAGE_SEWECT_EN(x)           (((x) >> 0) & 0x1)
#define   C_000328_VGA_MEM_PAGE_SEWECT_EN              0xFFFFFFFE
#define   S_000328_VGA_WBBM_WOCK_DISABWE(x)            (((x) & 0x1) << 8)
#define   G_000328_VGA_WBBM_WOCK_DISABWE(x)            (((x) >> 8) & 0x1)
#define   C_000328_VGA_WBBM_WOCK_DISABWE               0xFFFFFEFF
#define   S_000328_VGA_SOFT_WESET(x)                   (((x) & 0x1) << 16)
#define   G_000328_VGA_SOFT_WESET(x)                   (((x) >> 16) & 0x1)
#define   C_000328_VGA_SOFT_WESET                      0xFFFEFFFF
#define   S_000328_VGA_TEST_WESET_CONTWOW(x)           (((x) & 0x1) << 24)
#define   G_000328_VGA_TEST_WESET_CONTWOW(x)           (((x) >> 24) & 0x1)
#define   C_000328_VGA_TEST_WESET_CONTWOW              0xFEFFFFFF
#define W_000330_D1VGA_CONTWOW                       0x000330
#define   S_000330_D1VGA_MODE_ENABWE(x)                (((x) & 0x1) << 0)
#define   G_000330_D1VGA_MODE_ENABWE(x)                (((x) >> 0) & 0x1)
#define   C_000330_D1VGA_MODE_ENABWE                   0xFFFFFFFE
#define   S_000330_D1VGA_TIMING_SEWECT(x)              (((x) & 0x1) << 8)
#define   G_000330_D1VGA_TIMING_SEWECT(x)              (((x) >> 8) & 0x1)
#define   C_000330_D1VGA_TIMING_SEWECT                 0xFFFFFEFF
#define   S_000330_D1VGA_SYNC_POWAWITY_SEWECT(x)       (((x) & 0x1) << 9)
#define   G_000330_D1VGA_SYNC_POWAWITY_SEWECT(x)       (((x) >> 9) & 0x1)
#define   C_000330_D1VGA_SYNC_POWAWITY_SEWECT          0xFFFFFDFF
#define   S_000330_D1VGA_OVEWSCAN_TIMING_SEWECT(x)     (((x) & 0x1) << 10)
#define   G_000330_D1VGA_OVEWSCAN_TIMING_SEWECT(x)     (((x) >> 10) & 0x1)
#define   C_000330_D1VGA_OVEWSCAN_TIMING_SEWECT        0xFFFFFBFF
#define   S_000330_D1VGA_OVEWSCAN_COWOW_EN(x)          (((x) & 0x1) << 16)
#define   G_000330_D1VGA_OVEWSCAN_COWOW_EN(x)          (((x) >> 16) & 0x1)
#define   C_000330_D1VGA_OVEWSCAN_COWOW_EN             0xFFFEFFFF
#define   S_000330_D1VGA_WOTATE(x)                     (((x) & 0x3) << 24)
#define   G_000330_D1VGA_WOTATE(x)                     (((x) >> 24) & 0x3)
#define   C_000330_D1VGA_WOTATE                        0xFCFFFFFF
#define W_000338_D2VGA_CONTWOW                       0x000338
#define   S_000338_D2VGA_MODE_ENABWE(x)                (((x) & 0x1) << 0)
#define   G_000338_D2VGA_MODE_ENABWE(x)                (((x) >> 0) & 0x1)
#define   C_000338_D2VGA_MODE_ENABWE                   0xFFFFFFFE
#define   S_000338_D2VGA_TIMING_SEWECT(x)              (((x) & 0x1) << 8)
#define   G_000338_D2VGA_TIMING_SEWECT(x)              (((x) >> 8) & 0x1)
#define   C_000338_D2VGA_TIMING_SEWECT                 0xFFFFFEFF
#define   S_000338_D2VGA_SYNC_POWAWITY_SEWECT(x)       (((x) & 0x1) << 9)
#define   G_000338_D2VGA_SYNC_POWAWITY_SEWECT(x)       (((x) >> 9) & 0x1)
#define   C_000338_D2VGA_SYNC_POWAWITY_SEWECT          0xFFFFFDFF
#define   S_000338_D2VGA_OVEWSCAN_TIMING_SEWECT(x)     (((x) & 0x1) << 10)
#define   G_000338_D2VGA_OVEWSCAN_TIMING_SEWECT(x)     (((x) >> 10) & 0x1)
#define   C_000338_D2VGA_OVEWSCAN_TIMING_SEWECT        0xFFFFFBFF
#define   S_000338_D2VGA_OVEWSCAN_COWOW_EN(x)          (((x) & 0x1) << 16)
#define   G_000338_D2VGA_OVEWSCAN_COWOW_EN(x)          (((x) >> 16) & 0x1)
#define   C_000338_D2VGA_OVEWSCAN_COWOW_EN             0xFFFEFFFF
#define   S_000338_D2VGA_WOTATE(x)                     (((x) & 0x3) << 24)
#define   G_000338_D2VGA_WOTATE(x)                     (((x) >> 24) & 0x3)
#define   C_000338_D2VGA_WOTATE                        0xFCFFFFFF
#define W_0007C0_CP_STAT                             0x0007C0
#define   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 0)
#define   G_0007C0_MWU_BUSY(x)                         (((x) >> 0) & 0x1)
#define   C_0007C0_MWU_BUSY                            0xFFFFFFFE
#define   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 1)
#define   G_0007C0_MWU_BUSY(x)                         (((x) >> 1) & 0x1)
#define   C_0007C0_MWU_BUSY                            0xFFFFFFFD
#define   S_0007C0_WSIU_BUSY(x)                        (((x) & 0x1) << 2)
#define   G_0007C0_WSIU_BUSY(x)                        (((x) >> 2) & 0x1)
#define   C_0007C0_WSIU_BUSY                           0xFFFFFFFB
#define   S_0007C0_WCIU_BUSY(x)                        (((x) & 0x1) << 3)
#define   G_0007C0_WCIU_BUSY(x)                        (((x) >> 3) & 0x1)
#define   C_0007C0_WCIU_BUSY                           0xFFFFFFF7
#define   S_0007C0_CSF_PWIMAWY_BUSY(x)                 (((x) & 0x1) << 9)
#define   G_0007C0_CSF_PWIMAWY_BUSY(x)                 (((x) >> 9) & 0x1)
#define   C_0007C0_CSF_PWIMAWY_BUSY                    0xFFFFFDFF
#define   S_0007C0_CSF_INDIWECT_BUSY(x)                (((x) & 0x1) << 10)
#define   G_0007C0_CSF_INDIWECT_BUSY(x)                (((x) >> 10) & 0x1)
#define   C_0007C0_CSF_INDIWECT_BUSY                   0xFFFFFBFF
#define   S_0007C0_CSQ_PWIMAWY_BUSY(x)                 (((x) & 0x1) << 11)
#define   G_0007C0_CSQ_PWIMAWY_BUSY(x)                 (((x) >> 11) & 0x1)
#define   C_0007C0_CSQ_PWIMAWY_BUSY                    0xFFFFF7FF
#define   S_0007C0_CSQ_INDIWECT_BUSY(x)                (((x) & 0x1) << 12)
#define   G_0007C0_CSQ_INDIWECT_BUSY(x)                (((x) >> 12) & 0x1)
#define   C_0007C0_CSQ_INDIWECT_BUSY                   0xFFFFEFFF
#define   S_0007C0_CSI_BUSY(x)                         (((x) & 0x1) << 13)
#define   G_0007C0_CSI_BUSY(x)                         (((x) >> 13) & 0x1)
#define   C_0007C0_CSI_BUSY                            0xFFFFDFFF
#define   S_0007C0_CSF_INDIWECT2_BUSY(x)               (((x) & 0x1) << 14)
#define   G_0007C0_CSF_INDIWECT2_BUSY(x)               (((x) >> 14) & 0x1)
#define   C_0007C0_CSF_INDIWECT2_BUSY                  0xFFFFBFFF
#define   S_0007C0_CSQ_INDIWECT2_BUSY(x)               (((x) & 0x1) << 15)
#define   G_0007C0_CSQ_INDIWECT2_BUSY(x)               (((x) >> 15) & 0x1)
#define   C_0007C0_CSQ_INDIWECT2_BUSY                  0xFFFF7FFF
#define   S_0007C0_GUIDMA_BUSY(x)                      (((x) & 0x1) << 28)
#define   G_0007C0_GUIDMA_BUSY(x)                      (((x) >> 28) & 0x1)
#define   C_0007C0_GUIDMA_BUSY                         0xEFFFFFFF
#define   S_0007C0_VIDDMA_BUSY(x)                      (((x) & 0x1) << 29)
#define   G_0007C0_VIDDMA_BUSY(x)                      (((x) >> 29) & 0x1)
#define   C_0007C0_VIDDMA_BUSY                         0xDFFFFFFF
#define   S_0007C0_CMDSTWM_BUSY(x)                     (((x) & 0x1) << 30)
#define   G_0007C0_CMDSTWM_BUSY(x)                     (((x) >> 30) & 0x1)
#define   C_0007C0_CMDSTWM_BUSY                        0xBFFFFFFF
#define   S_0007C0_CP_BUSY(x)                          (((x) & 0x1) << 31)
#define   G_0007C0_CP_BUSY(x)                          (((x) >> 31) & 0x1)
#define   C_0007C0_CP_BUSY                             0x7FFFFFFF
#define W_000E40_WBBM_STATUS                         0x000E40
#define   S_000E40_CMDFIFO_AVAIW(x)                    (((x) & 0x7F) << 0)
#define   G_000E40_CMDFIFO_AVAIW(x)                    (((x) >> 0) & 0x7F)
#define   C_000E40_CMDFIFO_AVAIW                       0xFFFFFF80
#define   S_000E40_HIWQ_ON_WBB(x)                      (((x) & 0x1) << 8)
#define   G_000E40_HIWQ_ON_WBB(x)                      (((x) >> 8) & 0x1)
#define   C_000E40_HIWQ_ON_WBB                         0xFFFFFEFF
#define   S_000E40_CPWQ_ON_WBB(x)                      (((x) & 0x1) << 9)
#define   G_000E40_CPWQ_ON_WBB(x)                      (((x) >> 9) & 0x1)
#define   C_000E40_CPWQ_ON_WBB                         0xFFFFFDFF
#define   S_000E40_CFWQ_ON_WBB(x)                      (((x) & 0x1) << 10)
#define   G_000E40_CFWQ_ON_WBB(x)                      (((x) >> 10) & 0x1)
#define   C_000E40_CFWQ_ON_WBB                         0xFFFFFBFF
#define   S_000E40_HIWQ_IN_WTBUF(x)                    (((x) & 0x1) << 11)
#define   G_000E40_HIWQ_IN_WTBUF(x)                    (((x) >> 11) & 0x1)
#define   C_000E40_HIWQ_IN_WTBUF                       0xFFFFF7FF
#define   S_000E40_CPWQ_IN_WTBUF(x)                    (((x) & 0x1) << 12)
#define   G_000E40_CPWQ_IN_WTBUF(x)                    (((x) >> 12) & 0x1)
#define   C_000E40_CPWQ_IN_WTBUF                       0xFFFFEFFF
#define   S_000E40_CFWQ_IN_WTBUF(x)                    (((x) & 0x1) << 13)
#define   G_000E40_CFWQ_IN_WTBUF(x)                    (((x) >> 13) & 0x1)
#define   C_000E40_CFWQ_IN_WTBUF                       0xFFFFDFFF
#define   S_000E40_CF_PIPE_BUSY(x)                     (((x) & 0x1) << 14)
#define   G_000E40_CF_PIPE_BUSY(x)                     (((x) >> 14) & 0x1)
#define   C_000E40_CF_PIPE_BUSY                        0xFFFFBFFF
#define   S_000E40_ENG_EV_BUSY(x)                      (((x) & 0x1) << 15)
#define   G_000E40_ENG_EV_BUSY(x)                      (((x) >> 15) & 0x1)
#define   C_000E40_ENG_EV_BUSY                         0xFFFF7FFF
#define   S_000E40_CP_CMDSTWM_BUSY(x)                  (((x) & 0x1) << 16)
#define   G_000E40_CP_CMDSTWM_BUSY(x)                  (((x) >> 16) & 0x1)
#define   C_000E40_CP_CMDSTWM_BUSY                     0xFFFEFFFF
#define   S_000E40_E2_BUSY(x)                          (((x) & 0x1) << 17)
#define   G_000E40_E2_BUSY(x)                          (((x) >> 17) & 0x1)
#define   C_000E40_E2_BUSY                             0xFFFDFFFF
#define   S_000E40_WB2D_BUSY(x)                        (((x) & 0x1) << 18)
#define   G_000E40_WB2D_BUSY(x)                        (((x) >> 18) & 0x1)
#define   C_000E40_WB2D_BUSY                           0xFFFBFFFF
#define   S_000E40_WB3D_BUSY(x)                        (((x) & 0x1) << 19)
#define   G_000E40_WB3D_BUSY(x)                        (((x) >> 19) & 0x1)
#define   C_000E40_WB3D_BUSY                           0xFFF7FFFF
#define   S_000E40_VAP_BUSY(x)                         (((x) & 0x1) << 20)
#define   G_000E40_VAP_BUSY(x)                         (((x) >> 20) & 0x1)
#define   C_000E40_VAP_BUSY                            0xFFEFFFFF
#define   S_000E40_WE_BUSY(x)                          (((x) & 0x1) << 21)
#define   G_000E40_WE_BUSY(x)                          (((x) >> 21) & 0x1)
#define   C_000E40_WE_BUSY                             0xFFDFFFFF
#define   S_000E40_TAM_BUSY(x)                         (((x) & 0x1) << 22)
#define   G_000E40_TAM_BUSY(x)                         (((x) >> 22) & 0x1)
#define   C_000E40_TAM_BUSY                            0xFFBFFFFF
#define   S_000E40_TDM_BUSY(x)                         (((x) & 0x1) << 23)
#define   G_000E40_TDM_BUSY(x)                         (((x) >> 23) & 0x1)
#define   C_000E40_TDM_BUSY                            0xFF7FFFFF
#define   S_000E40_PB_BUSY(x)                          (((x) & 0x1) << 24)
#define   G_000E40_PB_BUSY(x)                          (((x) >> 24) & 0x1)
#define   C_000E40_PB_BUSY                             0xFEFFFFFF
#define   S_000E40_TIM_BUSY(x)                         (((x) & 0x1) << 25)
#define   G_000E40_TIM_BUSY(x)                         (((x) >> 25) & 0x1)
#define   C_000E40_TIM_BUSY                            0xFDFFFFFF
#define   S_000E40_GA_BUSY(x)                          (((x) & 0x1) << 26)
#define   G_000E40_GA_BUSY(x)                          (((x) >> 26) & 0x1)
#define   C_000E40_GA_BUSY                             0xFBFFFFFF
#define   S_000E40_CBA2D_BUSY(x)                       (((x) & 0x1) << 27)
#define   G_000E40_CBA2D_BUSY(x)                       (((x) >> 27) & 0x1)
#define   C_000E40_CBA2D_BUSY                          0xF7FFFFFF
#define   S_000E40_WBBM_HIBUSY(x)                      (((x) & 0x1) << 28)
#define   G_000E40_WBBM_HIBUSY(x)                      (((x) >> 28) & 0x1)
#define   C_000E40_WBBM_HIBUSY                         0xEFFFFFFF
#define   S_000E40_SKID_CFBUSY(x)                      (((x) & 0x1) << 29)
#define   G_000E40_SKID_CFBUSY(x)                      (((x) >> 29) & 0x1)
#define   C_000E40_SKID_CFBUSY                         0xDFFFFFFF
#define   S_000E40_VAP_VF_BUSY(x)                      (((x) & 0x1) << 30)
#define   G_000E40_VAP_VF_BUSY(x)                      (((x) >> 30) & 0x1)
#define   C_000E40_VAP_VF_BUSY                         0xBFFFFFFF
#define   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#define   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#define   C_000E40_GUI_ACTIVE                          0x7FFFFFFF
#define W_006080_D1CWTC_CONTWOW                      0x006080
#define   S_006080_D1CWTC_MASTEW_EN(x)                 (((x) & 0x1) << 0)
#define   G_006080_D1CWTC_MASTEW_EN(x)                 (((x) >> 0) & 0x1)
#define   C_006080_D1CWTC_MASTEW_EN                    0xFFFFFFFE
#define   S_006080_D1CWTC_SYNC_WESET_SEW(x)            (((x) & 0x1) << 4)
#define   G_006080_D1CWTC_SYNC_WESET_SEW(x)            (((x) >> 4) & 0x1)
#define   C_006080_D1CWTC_SYNC_WESET_SEW               0xFFFFFFEF
#define   S_006080_D1CWTC_DISABWE_POINT_CNTW(x)        (((x) & 0x3) << 8)
#define   G_006080_D1CWTC_DISABWE_POINT_CNTW(x)        (((x) >> 8) & 0x3)
#define   C_006080_D1CWTC_DISABWE_POINT_CNTW           0xFFFFFCFF
#define   S_006080_D1CWTC_CUWWENT_MASTEW_EN_STATE(x)   (((x) & 0x1) << 16)
#define   G_006080_D1CWTC_CUWWENT_MASTEW_EN_STATE(x)   (((x) >> 16) & 0x1)
#define   C_006080_D1CWTC_CUWWENT_MASTEW_EN_STATE      0xFFFEFFFF
#define   S_006080_D1CWTC_DISP_WEAD_WEQUEST_DISABWE(x) (((x) & 0x1) << 24)
#define   G_006080_D1CWTC_DISP_WEAD_WEQUEST_DISABWE(x) (((x) >> 24) & 0x1)
#define   C_006080_D1CWTC_DISP_WEAD_WEQUEST_DISABWE    0xFEFFFFFF
#define W_0060E8_D1CWTC_UPDATE_WOCK                  0x0060E8
#define   S_0060E8_D1CWTC_UPDATE_WOCK(x)               (((x) & 0x1) << 0)
#define   G_0060E8_D1CWTC_UPDATE_WOCK(x)               (((x) >> 0) & 0x1)
#define   C_0060E8_D1CWTC_UPDATE_WOCK                  0xFFFFFFFE
#define W_006110_D1GWPH_PWIMAWY_SUWFACE_ADDWESS      0x006110
#define   S_006110_D1GWPH_PWIMAWY_SUWFACE_ADDWESS(x)   (((x) & 0xFFFFFFFF) << 0)
#define   G_006110_D1GWPH_PWIMAWY_SUWFACE_ADDWESS(x)   (((x) >> 0) & 0xFFFFFFFF)
#define   C_006110_D1GWPH_PWIMAWY_SUWFACE_ADDWESS      0x00000000
#define W_006118_D1GWPH_SECONDAWY_SUWFACE_ADDWESS    0x006118
#define   S_006118_D1GWPH_SECONDAWY_SUWFACE_ADDWESS(x) (((x) & 0xFFFFFFFF) << 0)
#define   G_006118_D1GWPH_SECONDAWY_SUWFACE_ADDWESS(x) (((x) >> 0) & 0xFFFFFFFF)
#define   C_006118_D1GWPH_SECONDAWY_SUWFACE_ADDWESS    0x00000000
#define W_006880_D2CWTC_CONTWOW                      0x006880
#define   S_006880_D2CWTC_MASTEW_EN(x)                 (((x) & 0x1) << 0)
#define   G_006880_D2CWTC_MASTEW_EN(x)                 (((x) >> 0) & 0x1)
#define   C_006880_D2CWTC_MASTEW_EN                    0xFFFFFFFE
#define   S_006880_D2CWTC_SYNC_WESET_SEW(x)            (((x) & 0x1) << 4)
#define   G_006880_D2CWTC_SYNC_WESET_SEW(x)            (((x) >> 4) & 0x1)
#define   C_006880_D2CWTC_SYNC_WESET_SEW               0xFFFFFFEF
#define   S_006880_D2CWTC_DISABWE_POINT_CNTW(x)        (((x) & 0x3) << 8)
#define   G_006880_D2CWTC_DISABWE_POINT_CNTW(x)        (((x) >> 8) & 0x3)
#define   C_006880_D2CWTC_DISABWE_POINT_CNTW           0xFFFFFCFF
#define   S_006880_D2CWTC_CUWWENT_MASTEW_EN_STATE(x)   (((x) & 0x1) << 16)
#define   G_006880_D2CWTC_CUWWENT_MASTEW_EN_STATE(x)   (((x) >> 16) & 0x1)
#define   C_006880_D2CWTC_CUWWENT_MASTEW_EN_STATE      0xFFFEFFFF
#define   S_006880_D2CWTC_DISP_WEAD_WEQUEST_DISABWE(x) (((x) & 0x1) << 24)
#define   G_006880_D2CWTC_DISP_WEAD_WEQUEST_DISABWE(x) (((x) >> 24) & 0x1)
#define   C_006880_D2CWTC_DISP_WEAD_WEQUEST_DISABWE    0xFEFFFFFF
#define W_0068E8_D2CWTC_UPDATE_WOCK                  0x0068E8
#define   S_0068E8_D2CWTC_UPDATE_WOCK(x)               (((x) & 0x1) << 0)
#define   G_0068E8_D2CWTC_UPDATE_WOCK(x)               (((x) >> 0) & 0x1)
#define   C_0068E8_D2CWTC_UPDATE_WOCK                  0xFFFFFFFE
#define W_006910_D2GWPH_PWIMAWY_SUWFACE_ADDWESS      0x006910
#define   S_006910_D2GWPH_PWIMAWY_SUWFACE_ADDWESS(x)   (((x) & 0xFFFFFFFF) << 0)
#define   G_006910_D2GWPH_PWIMAWY_SUWFACE_ADDWESS(x)   (((x) >> 0) & 0xFFFFFFFF)
#define   C_006910_D2GWPH_PWIMAWY_SUWFACE_ADDWESS      0x00000000
#define W_006918_D2GWPH_SECONDAWY_SUWFACE_ADDWESS    0x006918
#define   S_006918_D2GWPH_SECONDAWY_SUWFACE_ADDWESS(x) (((x) & 0xFFFFFFFF) << 0)
#define   G_006918_D2GWPH_SECONDAWY_SUWFACE_ADDWESS(x) (((x) >> 0) & 0xFFFFFFFF)
#define   C_006918_D2GWPH_SECONDAWY_SUWFACE_ADDWESS    0x00000000


#define W_000001_MC_FB_WOCATION                      0x000001
#define   S_000001_MC_FB_STAWT(x)                      (((x) & 0xFFFF) << 0)
#define   G_000001_MC_FB_STAWT(x)                      (((x) >> 0) & 0xFFFF)
#define   C_000001_MC_FB_STAWT                         0xFFFF0000
#define   S_000001_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#define   G_000001_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#define   C_000001_MC_FB_TOP                           0x0000FFFF
#define W_000002_MC_AGP_WOCATION                     0x000002
#define   S_000002_MC_AGP_STAWT(x)                     (((x) & 0xFFFF) << 0)
#define   G_000002_MC_AGP_STAWT(x)                     (((x) >> 0) & 0xFFFF)
#define   C_000002_MC_AGP_STAWT                        0xFFFF0000
#define   S_000002_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#define   G_000002_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#define   C_000002_MC_AGP_TOP                          0x0000FFFF
#define W_000003_MC_AGP_BASE                         0x000003
#define   S_000003_AGP_BASE_ADDW(x)                    (((x) & 0xFFFFFFFF) << 0)
#define   G_000003_AGP_BASE_ADDW(x)                    (((x) >> 0) & 0xFFFFFFFF)
#define   C_000003_AGP_BASE_ADDW                       0x00000000
#define W_000004_MC_AGP_BASE_2                       0x000004
#define   S_000004_AGP_BASE_ADDW_2(x)                  (((x) & 0xF) << 0)
#define   G_000004_AGP_BASE_ADDW_2(x)                  (((x) >> 0) & 0xF)
#define   C_000004_AGP_BASE_ADDW_2                     0xFFFFFFF0


#define W_00000F_CP_DYN_CNTW                         0x00000F
#define   S_00000F_CP_FOWCEON(x)                       (((x) & 0x1) << 0)
#define   G_00000F_CP_FOWCEON(x)                       (((x) >> 0) & 0x1)
#define   C_00000F_CP_FOWCEON                          0xFFFFFFFE
#define   S_00000F_CP_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 1)
#define   G_00000F_CP_MAX_DYN_STOP_WAT(x)              (((x) >> 1) & 0x1)
#define   C_00000F_CP_MAX_DYN_STOP_WAT                 0xFFFFFFFD
#define   S_00000F_CP_CWOCK_STATUS(x)                  (((x) & 0x1) << 2)
#define   G_00000F_CP_CWOCK_STATUS(x)                  (((x) >> 2) & 0x1)
#define   C_00000F_CP_CWOCK_STATUS                     0xFFFFFFFB
#define   S_00000F_CP_PWOG_SHUTOFF(x)                  (((x) & 0x1) << 3)
#define   G_00000F_CP_PWOG_SHUTOFF(x)                  (((x) >> 3) & 0x1)
#define   C_00000F_CP_PWOG_SHUTOFF                     0xFFFFFFF7
#define   S_00000F_CP_PWOG_DEWAY_VAWUE(x)              (((x) & 0xFF) << 4)
#define   G_00000F_CP_PWOG_DEWAY_VAWUE(x)              (((x) >> 4) & 0xFF)
#define   C_00000F_CP_PWOG_DEWAY_VAWUE                 0xFFFFF00F
#define   S_00000F_CP_WOWEW_POWEW_IDWE(x)              (((x) & 0xFF) << 12)
#define   G_00000F_CP_WOWEW_POWEW_IDWE(x)              (((x) >> 12) & 0xFF)
#define   C_00000F_CP_WOWEW_POWEW_IDWE                 0xFFF00FFF
#define   S_00000F_CP_WOWEW_POWEW_IGNOWE(x)            (((x) & 0x1) << 20)
#define   G_00000F_CP_WOWEW_POWEW_IGNOWE(x)            (((x) >> 20) & 0x1)
#define   C_00000F_CP_WOWEW_POWEW_IGNOWE               0xFFEFFFFF
#define   S_00000F_CP_NOWMAW_POWEW_IGNOWE(x)           (((x) & 0x1) << 21)
#define   G_00000F_CP_NOWMAW_POWEW_IGNOWE(x)           (((x) >> 21) & 0x1)
#define   C_00000F_CP_NOWMAW_POWEW_IGNOWE              0xFFDFFFFF
#define   S_00000F_SPAWE(x)                            (((x) & 0x3) << 22)
#define   G_00000F_SPAWE(x)                            (((x) >> 22) & 0x3)
#define   C_00000F_SPAWE                               0xFF3FFFFF
#define   S_00000F_CP_NOWMAW_POWEW_BUSY(x)             (((x) & 0xFF) << 24)
#define   G_00000F_CP_NOWMAW_POWEW_BUSY(x)             (((x) >> 24) & 0xFF)
#define   C_00000F_CP_NOWMAW_POWEW_BUSY                0x00FFFFFF
#define W_000011_E2_DYN_CNTW                         0x000011
#define   S_000011_E2_FOWCEON(x)                       (((x) & 0x1) << 0)
#define   G_000011_E2_FOWCEON(x)                       (((x) >> 0) & 0x1)
#define   C_000011_E2_FOWCEON                          0xFFFFFFFE
#define   S_000011_E2_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 1)
#define   G_000011_E2_MAX_DYN_STOP_WAT(x)              (((x) >> 1) & 0x1)
#define   C_000011_E2_MAX_DYN_STOP_WAT                 0xFFFFFFFD
#define   S_000011_E2_CWOCK_STATUS(x)                  (((x) & 0x1) << 2)
#define   G_000011_E2_CWOCK_STATUS(x)                  (((x) >> 2) & 0x1)
#define   C_000011_E2_CWOCK_STATUS                     0xFFFFFFFB
#define   S_000011_E2_PWOG_SHUTOFF(x)                  (((x) & 0x1) << 3)
#define   G_000011_E2_PWOG_SHUTOFF(x)                  (((x) >> 3) & 0x1)
#define   C_000011_E2_PWOG_SHUTOFF                     0xFFFFFFF7
#define   S_000011_E2_PWOG_DEWAY_VAWUE(x)              (((x) & 0xFF) << 4)
#define   G_000011_E2_PWOG_DEWAY_VAWUE(x)              (((x) >> 4) & 0xFF)
#define   C_000011_E2_PWOG_DEWAY_VAWUE                 0xFFFFF00F
#define   S_000011_E2_WOWEW_POWEW_IDWE(x)              (((x) & 0xFF) << 12)
#define   G_000011_E2_WOWEW_POWEW_IDWE(x)              (((x) >> 12) & 0xFF)
#define   C_000011_E2_WOWEW_POWEW_IDWE                 0xFFF00FFF
#define   S_000011_E2_WOWEW_POWEW_IGNOWE(x)            (((x) & 0x1) << 20)
#define   G_000011_E2_WOWEW_POWEW_IGNOWE(x)            (((x) >> 20) & 0x1)
#define   C_000011_E2_WOWEW_POWEW_IGNOWE               0xFFEFFFFF
#define   S_000011_E2_NOWMAW_POWEW_IGNOWE(x)           (((x) & 0x1) << 21)
#define   G_000011_E2_NOWMAW_POWEW_IGNOWE(x)           (((x) >> 21) & 0x1)
#define   C_000011_E2_NOWMAW_POWEW_IGNOWE              0xFFDFFFFF
#define   S_000011_SPAWE(x)                            (((x) & 0x3) << 22)
#define   G_000011_SPAWE(x)                            (((x) >> 22) & 0x3)
#define   C_000011_SPAWE                               0xFF3FFFFF
#define   S_000011_E2_NOWMAW_POWEW_BUSY(x)             (((x) & 0xFF) << 24)
#define   G_000011_E2_NOWMAW_POWEW_BUSY(x)             (((x) >> 24) & 0xFF)
#define   C_000011_E2_NOWMAW_POWEW_BUSY                0x00FFFFFF
#define W_000013_IDCT_DYN_CNTW                       0x000013
#define   S_000013_IDCT_FOWCEON(x)                     (((x) & 0x1) << 0)
#define   G_000013_IDCT_FOWCEON(x)                     (((x) >> 0) & 0x1)
#define   C_000013_IDCT_FOWCEON                        0xFFFFFFFE
#define   S_000013_IDCT_MAX_DYN_STOP_WAT(x)            (((x) & 0x1) << 1)
#define   G_000013_IDCT_MAX_DYN_STOP_WAT(x)            (((x) >> 1) & 0x1)
#define   C_000013_IDCT_MAX_DYN_STOP_WAT               0xFFFFFFFD
#define   S_000013_IDCT_CWOCK_STATUS(x)                (((x) & 0x1) << 2)
#define   G_000013_IDCT_CWOCK_STATUS(x)                (((x) >> 2) & 0x1)
#define   C_000013_IDCT_CWOCK_STATUS                   0xFFFFFFFB
#define   S_000013_IDCT_PWOG_SHUTOFF(x)                (((x) & 0x1) << 3)
#define   G_000013_IDCT_PWOG_SHUTOFF(x)                (((x) >> 3) & 0x1)
#define   C_000013_IDCT_PWOG_SHUTOFF                   0xFFFFFFF7
#define   S_000013_IDCT_PWOG_DEWAY_VAWUE(x)            (((x) & 0xFF) << 4)
#define   G_000013_IDCT_PWOG_DEWAY_VAWUE(x)            (((x) >> 4) & 0xFF)
#define   C_000013_IDCT_PWOG_DEWAY_VAWUE               0xFFFFF00F
#define   S_000013_IDCT_WOWEW_POWEW_IDWE(x)            (((x) & 0xFF) << 12)
#define   G_000013_IDCT_WOWEW_POWEW_IDWE(x)            (((x) >> 12) & 0xFF)
#define   C_000013_IDCT_WOWEW_POWEW_IDWE               0xFFF00FFF
#define   S_000013_IDCT_WOWEW_POWEW_IGNOWE(x)          (((x) & 0x1) << 20)
#define   G_000013_IDCT_WOWEW_POWEW_IGNOWE(x)          (((x) >> 20) & 0x1)
#define   C_000013_IDCT_WOWEW_POWEW_IGNOWE             0xFFEFFFFF
#define   S_000013_IDCT_NOWMAW_POWEW_IGNOWE(x)         (((x) & 0x1) << 21)
#define   G_000013_IDCT_NOWMAW_POWEW_IGNOWE(x)         (((x) >> 21) & 0x1)
#define   C_000013_IDCT_NOWMAW_POWEW_IGNOWE            0xFFDFFFFF
#define   S_000013_SPAWE(x)                            (((x) & 0x3) << 22)
#define   G_000013_SPAWE(x)                            (((x) >> 22) & 0x3)
#define   C_000013_SPAWE                               0xFF3FFFFF
#define   S_000013_IDCT_NOWMAW_POWEW_BUSY(x)           (((x) & 0xFF) << 24)
#define   G_000013_IDCT_NOWMAW_POWEW_BUSY(x)           (((x) >> 24) & 0xFF)
#define   C_000013_IDCT_NOWMAW_POWEW_BUSY              0x00FFFFFF

#endif

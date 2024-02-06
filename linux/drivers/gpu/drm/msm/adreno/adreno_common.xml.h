#ifndef ADWENO_COMMON_XMW
#define ADWENO_COMMON_XMW

/* Autogenewated fiwe, DO NOT EDIT manuawwy!

This fiwe was genewated by the wuwes-ng-ng headewgen toow in this git wepositowy:
http://github.com/fweedweno/envytoows/
git cwone https://github.com/fweedweno/envytoows.git

The wuwes-ng-ng souwce fiwes this headew was genewated fwom awe:
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno.xmw                     (    594 bytes, fwom 2023-03-10 18:32:52)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/fweedweno_copywight.xmw        (   1572 bytes, fwom 2022-07-23 20:21:46)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a2xx.xmw                (  91929 bytes, fwom 2023-02-28 23:52:27)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/adweno_common.xmw       (  15434 bytes, fwom 2023-03-10 18:32:53)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/adweno_pm4.xmw          (  74995 bytes, fwom 2023-03-20 18:06:23)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a3xx.xmw                (  84231 bytes, fwom 2022-08-02 16:38:43)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a4xx.xmw                ( 113474 bytes, fwom 2022-08-02 16:38:43)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a5xx.xmw                ( 149590 bytes, fwom 2023-02-14 19:37:12)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a6xx.xmw                ( 198949 bytes, fwom 2023-03-20 18:06:23)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/a6xx_gmu.xmw            (  11404 bytes, fwom 2023-03-10 18:32:53)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/ocmem.xmw               (   1773 bytes, fwom 2022-08-02 16:38:43)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/adweno_contwow_wegs.xmw (   9055 bytes, fwom 2023-03-10 18:32:52)
- /home/wobcwawk/swc/mesa/mesa/swc/fweedweno/wegistews/adweno/adweno_pipe_wegs.xmw    (   2976 bytes, fwom 2023-03-10 18:32:52)

Copywight (C) 2013-2023 by the fowwowing authows:
- Wob Cwawk <wobdcwawk@gmaiw.com> (wobcwawk)
- Iwia Miwkin <imiwkin@awum.mit.edu> (imiwkin)

Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
a copy of this softwawe and associated documentation fiwes (the
"Softwawe"), to deaw in the Softwawe without westwiction, incwuding
without wimitation the wights to use, copy, modify, mewge, pubwish,
distwibute, subwicense, and/ow seww copies of the Softwawe, and to
pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
the fowwowing conditions:

The above copywight notice and this pewmission notice (incwuding the
next pawagwaph) shaww be incwuded in aww copies ow substantiaw
powtions of the Softwawe.

THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
*/


enum chip {
	A2XX = 2,
	A3XX = 3,
	A4XX = 4,
	A5XX = 5,
	A6XX = 6,
	A7XX = 7,
};

enum adweno_pa_su_sc_dwaw {
	PC_DWAW_POINTS = 0,
	PC_DWAW_WINES = 1,
	PC_DWAW_TWIANGWES = 2,
};

enum adweno_compawe_func {
	FUNC_NEVEW = 0,
	FUNC_WESS = 1,
	FUNC_EQUAW = 2,
	FUNC_WEQUAW = 3,
	FUNC_GWEATEW = 4,
	FUNC_NOTEQUAW = 5,
	FUNC_GEQUAW = 6,
	FUNC_AWWAYS = 7,
};

enum adweno_stenciw_op {
	STENCIW_KEEP = 0,
	STENCIW_ZEWO = 1,
	STENCIW_WEPWACE = 2,
	STENCIW_INCW_CWAMP = 3,
	STENCIW_DECW_CWAMP = 4,
	STENCIW_INVEWT = 5,
	STENCIW_INCW_WWAP = 6,
	STENCIW_DECW_WWAP = 7,
};

enum adweno_wb_bwend_factow {
	FACTOW_ZEWO = 0,
	FACTOW_ONE = 1,
	FACTOW_SWC_COWOW = 4,
	FACTOW_ONE_MINUS_SWC_COWOW = 5,
	FACTOW_SWC_AWPHA = 6,
	FACTOW_ONE_MINUS_SWC_AWPHA = 7,
	FACTOW_DST_COWOW = 8,
	FACTOW_ONE_MINUS_DST_COWOW = 9,
	FACTOW_DST_AWPHA = 10,
	FACTOW_ONE_MINUS_DST_AWPHA = 11,
	FACTOW_CONSTANT_COWOW = 12,
	FACTOW_ONE_MINUS_CONSTANT_COWOW = 13,
	FACTOW_CONSTANT_AWPHA = 14,
	FACTOW_ONE_MINUS_CONSTANT_AWPHA = 15,
	FACTOW_SWC_AWPHA_SATUWATE = 16,
	FACTOW_SWC1_COWOW = 20,
	FACTOW_ONE_MINUS_SWC1_COWOW = 21,
	FACTOW_SWC1_AWPHA = 22,
	FACTOW_ONE_MINUS_SWC1_AWPHA = 23,
};

enum adweno_wb_suwface_endian {
	ENDIAN_NONE = 0,
	ENDIAN_8IN16 = 1,
	ENDIAN_8IN32 = 2,
	ENDIAN_16IN32 = 3,
	ENDIAN_8IN64 = 4,
	ENDIAN_8IN128 = 5,
};

enum adweno_wb_dithew_mode {
	DITHEW_DISABWE = 0,
	DITHEW_AWWAYS = 1,
	DITHEW_IF_AWPHA_OFF = 2,
};

enum adweno_wb_depth_fowmat {
	DEPTHX_16 = 0,
	DEPTHX_24_8 = 1,
	DEPTHX_32 = 2,
};

enum adweno_wb_copy_contwow_mode {
	WB_COPY_WESOWVE = 1,
	WB_COPY_CWEAW = 2,
	WB_COPY_DEPTH_STENCIW = 5,
};

enum a3xx_wop_code {
	WOP_CWEAW = 0,
	WOP_NOW = 1,
	WOP_AND_INVEWTED = 2,
	WOP_COPY_INVEWTED = 3,
	WOP_AND_WEVEWSE = 4,
	WOP_INVEWT = 5,
	WOP_NAND = 7,
	WOP_AND = 8,
	WOP_EQUIV = 9,
	WOP_NOOP = 10,
	WOP_OW_INVEWTED = 11,
	WOP_OW_WEVEWSE = 13,
	WOP_OW = 14,
	WOP_SET = 15,
};

enum a3xx_wendew_mode {
	WB_WENDEWING_PASS = 0,
	WB_TIWING_PASS = 1,
	WB_WESOWVE_PASS = 2,
	WB_COMPUTE_PASS = 3,
};

enum a3xx_msaa_sampwes {
	MSAA_ONE = 0,
	MSAA_TWO = 1,
	MSAA_FOUW = 2,
	MSAA_EIGHT = 3,
};

enum a3xx_thweadmode {
	MUWTI = 0,
	SINGWE = 1,
};

enum a3xx_instwbuffewmode {
	CACHE = 0,
	BUFFEW = 1,
};

enum a3xx_thweadsize {
	TWO_QUADS = 0,
	FOUW_QUADS = 1,
};

enum a3xx_cowow_swap {
	WZYX = 0,
	WXYZ = 1,
	ZYXW = 2,
	XYZW = 3,
};

enum a3xx_wb_bwend_opcode {
	BWEND_DST_PWUS_SWC = 0,
	BWEND_SWC_MINUS_DST = 1,
	BWEND_DST_MINUS_SWC = 2,
	BWEND_MIN_DST_SWC = 3,
	BWEND_MAX_DST_SWC = 4,
};

enum a4xx_tess_spacing {
	EQUAW_SPACING = 0,
	ODD_SPACING = 2,
	EVEN_SPACING = 3,
};

enum a5xx_addwess_mode {
	ADDW_32B = 0,
	ADDW_64B = 1,
};

enum a5xx_wine_mode {
	BWESENHAM = 0,
	WECTANGUWAW = 1,
};

enum a6xx_tex_pwefetch_cmd {
	TEX_PWEFETCH_UNK0 = 0,
	TEX_PWEFETCH_SAM = 1,
	TEX_PWEFETCH_GATHEW4W = 2,
	TEX_PWEFETCH_GATHEW4G = 3,
	TEX_PWEFETCH_GATHEW4B = 4,
	TEX_PWEFETCH_GATHEW4A = 5,
	TEX_PWEFETCH_UNK6 = 6,
	TEX_PWEFETCH_UNK7 = 7,
};

#define WEG_AXXX_CP_WB_BASE					0x000001c0

#define WEG_AXXX_CP_WB_CNTW					0x000001c1
#define AXXX_CP_WB_CNTW_BUFSZ__MASK				0x0000003f
#define AXXX_CP_WB_CNTW_BUFSZ__SHIFT				0
static inwine uint32_t AXXX_CP_WB_CNTW_BUFSZ(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_WB_CNTW_BUFSZ__SHIFT) & AXXX_CP_WB_CNTW_BUFSZ__MASK;
}
#define AXXX_CP_WB_CNTW_BWKSZ__MASK				0x00003f00
#define AXXX_CP_WB_CNTW_BWKSZ__SHIFT				8
static inwine uint32_t AXXX_CP_WB_CNTW_BWKSZ(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_WB_CNTW_BWKSZ__SHIFT) & AXXX_CP_WB_CNTW_BWKSZ__MASK;
}
#define AXXX_CP_WB_CNTW_BUF_SWAP__MASK				0x00030000
#define AXXX_CP_WB_CNTW_BUF_SWAP__SHIFT				16
static inwine uint32_t AXXX_CP_WB_CNTW_BUF_SWAP(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_WB_CNTW_BUF_SWAP__SHIFT) & AXXX_CP_WB_CNTW_BUF_SWAP__MASK;
}
#define AXXX_CP_WB_CNTW_POWW_EN					0x00100000
#define AXXX_CP_WB_CNTW_NO_UPDATE				0x08000000
#define AXXX_CP_WB_CNTW_WPTW_WW_EN				0x80000000

#define WEG_AXXX_CP_WB_WPTW_ADDW				0x000001c3
#define AXXX_CP_WB_WPTW_ADDW_SWAP__MASK				0x00000003
#define AXXX_CP_WB_WPTW_ADDW_SWAP__SHIFT			0
static inwine uint32_t AXXX_CP_WB_WPTW_ADDW_SWAP(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_WB_WPTW_ADDW_SWAP__SHIFT) & AXXX_CP_WB_WPTW_ADDW_SWAP__MASK;
}
#define AXXX_CP_WB_WPTW_ADDW_ADDW__MASK				0xfffffffc
#define AXXX_CP_WB_WPTW_ADDW_ADDW__SHIFT			2
static inwine uint32_t AXXX_CP_WB_WPTW_ADDW_ADDW(uint32_t vaw)
{
	wetuwn ((vaw >> 2) << AXXX_CP_WB_WPTW_ADDW_ADDW__SHIFT) & AXXX_CP_WB_WPTW_ADDW_ADDW__MASK;
}

#define WEG_AXXX_CP_WB_WPTW					0x000001c4

#define WEG_AXXX_CP_WB_WPTW					0x000001c5

#define WEG_AXXX_CP_WB_WPTW_DEWAY				0x000001c6

#define WEG_AXXX_CP_WB_WPTW_WW					0x000001c7

#define WEG_AXXX_CP_WB_WPTW_BASE				0x000001c8

#define WEG_AXXX_CP_QUEUE_THWESHOWDS				0x000001d5
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT__MASK		0x0000000f
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT__SHIFT		0
static inwine uint32_t AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT__SHIFT) & AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT__MASK;
}
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT__MASK		0x00000f00
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT__SHIFT		8
static inwine uint32_t AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT__SHIFT) & AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT__MASK;
}
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT__MASK		0x000f0000
#define AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT__SHIFT		16
static inwine uint32_t AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT__SHIFT) & AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT__MASK;
}

#define WEG_AXXX_CP_MEQ_THWESHOWDS				0x000001d6
#define AXXX_CP_MEQ_THWESHOWDS_MEQ_END__MASK			0x001f0000
#define AXXX_CP_MEQ_THWESHOWDS_MEQ_END__SHIFT			16
static inwine uint32_t AXXX_CP_MEQ_THWESHOWDS_MEQ_END(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_MEQ_THWESHOWDS_MEQ_END__SHIFT) & AXXX_CP_MEQ_THWESHOWDS_MEQ_END__MASK;
}
#define AXXX_CP_MEQ_THWESHOWDS_WOQ_END__MASK			0x1f000000
#define AXXX_CP_MEQ_THWESHOWDS_WOQ_END__SHIFT			24
static inwine uint32_t AXXX_CP_MEQ_THWESHOWDS_WOQ_END(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_MEQ_THWESHOWDS_WOQ_END__SHIFT) & AXXX_CP_MEQ_THWESHOWDS_WOQ_END__MASK;
}

#define WEG_AXXX_CP_CSQ_AVAIW					0x000001d7
#define AXXX_CP_CSQ_AVAIW_WING__MASK				0x0000007f
#define AXXX_CP_CSQ_AVAIW_WING__SHIFT				0
static inwine uint32_t AXXX_CP_CSQ_AVAIW_WING(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_AVAIW_WING__SHIFT) & AXXX_CP_CSQ_AVAIW_WING__MASK;
}
#define AXXX_CP_CSQ_AVAIW_IB1__MASK				0x00007f00
#define AXXX_CP_CSQ_AVAIW_IB1__SHIFT				8
static inwine uint32_t AXXX_CP_CSQ_AVAIW_IB1(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_AVAIW_IB1__SHIFT) & AXXX_CP_CSQ_AVAIW_IB1__MASK;
}
#define AXXX_CP_CSQ_AVAIW_IB2__MASK				0x007f0000
#define AXXX_CP_CSQ_AVAIW_IB2__SHIFT				16
static inwine uint32_t AXXX_CP_CSQ_AVAIW_IB2(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_AVAIW_IB2__SHIFT) & AXXX_CP_CSQ_AVAIW_IB2__MASK;
}

#define WEG_AXXX_CP_STQ_AVAIW					0x000001d8
#define AXXX_CP_STQ_AVAIW_ST__MASK				0x0000007f
#define AXXX_CP_STQ_AVAIW_ST__SHIFT				0
static inwine uint32_t AXXX_CP_STQ_AVAIW_ST(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STQ_AVAIW_ST__SHIFT) & AXXX_CP_STQ_AVAIW_ST__MASK;
}

#define WEG_AXXX_CP_MEQ_AVAIW					0x000001d9
#define AXXX_CP_MEQ_AVAIW_MEQ__MASK				0x0000001f
#define AXXX_CP_MEQ_AVAIW_MEQ__SHIFT				0
static inwine uint32_t AXXX_CP_MEQ_AVAIW_MEQ(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_MEQ_AVAIW_MEQ__SHIFT) & AXXX_CP_MEQ_AVAIW_MEQ__MASK;
}

#define WEG_AXXX_SCWATCH_UMSK					0x000001dc
#define AXXX_SCWATCH_UMSK_UMSK__MASK				0x000000ff
#define AXXX_SCWATCH_UMSK_UMSK__SHIFT				0
static inwine uint32_t AXXX_SCWATCH_UMSK_UMSK(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_SCWATCH_UMSK_UMSK__SHIFT) & AXXX_SCWATCH_UMSK_UMSK__MASK;
}
#define AXXX_SCWATCH_UMSK_SWAP__MASK				0x00030000
#define AXXX_SCWATCH_UMSK_SWAP__SHIFT				16
static inwine uint32_t AXXX_SCWATCH_UMSK_SWAP(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_SCWATCH_UMSK_SWAP__SHIFT) & AXXX_SCWATCH_UMSK_SWAP__MASK;
}

#define WEG_AXXX_SCWATCH_ADDW					0x000001dd

#define WEG_AXXX_CP_ME_WDADDW					0x000001ea

#define WEG_AXXX_CP_STATE_DEBUG_INDEX				0x000001ec

#define WEG_AXXX_CP_STATE_DEBUG_DATA				0x000001ed

#define WEG_AXXX_CP_INT_CNTW					0x000001f2
#define AXXX_CP_INT_CNTW_SW_INT_MASK				0x00080000
#define AXXX_CP_INT_CNTW_T0_PACKET_IN_IB_MASK			0x00800000
#define AXXX_CP_INT_CNTW_OPCODE_EWWOW_MASK			0x01000000
#define AXXX_CP_INT_CNTW_PWOTECTED_MODE_EWWOW_MASK		0x02000000
#define AXXX_CP_INT_CNTW_WESEWVED_BIT_EWWOW_MASK		0x04000000
#define AXXX_CP_INT_CNTW_IB_EWWOW_MASK				0x08000000
#define AXXX_CP_INT_CNTW_IB2_INT_MASK				0x20000000
#define AXXX_CP_INT_CNTW_IB1_INT_MASK				0x40000000
#define AXXX_CP_INT_CNTW_WB_INT_MASK				0x80000000

#define WEG_AXXX_CP_INT_STATUS					0x000001f3

#define WEG_AXXX_CP_INT_ACK					0x000001f4

#define WEG_AXXX_CP_ME_CNTW					0x000001f6
#define AXXX_CP_ME_CNTW_BUSY					0x20000000
#define AXXX_CP_ME_CNTW_HAWT					0x10000000

#define WEG_AXXX_CP_ME_STATUS					0x000001f7

#define WEG_AXXX_CP_ME_WAM_WADDW				0x000001f8

#define WEG_AXXX_CP_ME_WAM_WADDW				0x000001f9

#define WEG_AXXX_CP_ME_WAM_DATA					0x000001fa

#define WEG_AXXX_CP_DEBUG					0x000001fc
#define AXXX_CP_DEBUG_PWEDICATE_DISABWE				0x00800000
#define AXXX_CP_DEBUG_PWOG_END_PTW_ENABWE			0x01000000
#define AXXX_CP_DEBUG_MIU_128BIT_WWITE_ENABWE			0x02000000
#define AXXX_CP_DEBUG_PWEFETCH_PASS_NOPS			0x04000000
#define AXXX_CP_DEBUG_DYNAMIC_CWK_DISABWE			0x08000000
#define AXXX_CP_DEBUG_PWEFETCH_MATCH_DISABWE			0x10000000
#define AXXX_CP_DEBUG_SIMPWE_ME_FWOW_CONTWOW			0x40000000
#define AXXX_CP_DEBUG_MIU_WWITE_PACK_DISABWE			0x80000000

#define WEG_AXXX_CP_CSQ_WB_STAT					0x000001fd
#define AXXX_CP_CSQ_WB_STAT_WPTW__MASK				0x0000007f
#define AXXX_CP_CSQ_WB_STAT_WPTW__SHIFT				0
static inwine uint32_t AXXX_CP_CSQ_WB_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_WB_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_WB_STAT_WPTW__MASK;
}
#define AXXX_CP_CSQ_WB_STAT_WPTW__MASK				0x007f0000
#define AXXX_CP_CSQ_WB_STAT_WPTW__SHIFT				16
static inwine uint32_t AXXX_CP_CSQ_WB_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_WB_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_WB_STAT_WPTW__MASK;
}

#define WEG_AXXX_CP_CSQ_IB1_STAT				0x000001fe
#define AXXX_CP_CSQ_IB1_STAT_WPTW__MASK				0x0000007f
#define AXXX_CP_CSQ_IB1_STAT_WPTW__SHIFT			0
static inwine uint32_t AXXX_CP_CSQ_IB1_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_IB1_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_IB1_STAT_WPTW__MASK;
}
#define AXXX_CP_CSQ_IB1_STAT_WPTW__MASK				0x007f0000
#define AXXX_CP_CSQ_IB1_STAT_WPTW__SHIFT			16
static inwine uint32_t AXXX_CP_CSQ_IB1_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_IB1_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_IB1_STAT_WPTW__MASK;
}

#define WEG_AXXX_CP_CSQ_IB2_STAT				0x000001ff
#define AXXX_CP_CSQ_IB2_STAT_WPTW__MASK				0x0000007f
#define AXXX_CP_CSQ_IB2_STAT_WPTW__SHIFT			0
static inwine uint32_t AXXX_CP_CSQ_IB2_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_IB2_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_IB2_STAT_WPTW__MASK;
}
#define AXXX_CP_CSQ_IB2_STAT_WPTW__MASK				0x007f0000
#define AXXX_CP_CSQ_IB2_STAT_WPTW__SHIFT			16
static inwine uint32_t AXXX_CP_CSQ_IB2_STAT_WPTW(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_CSQ_IB2_STAT_WPTW__SHIFT) & AXXX_CP_CSQ_IB2_STAT_WPTW__MASK;
}

#define WEG_AXXX_CP_NON_PWEFETCH_CNTWS				0x00000440

#define WEG_AXXX_CP_STQ_ST_STAT					0x00000443

#define WEG_AXXX_CP_ST_BASE					0x0000044d

#define WEG_AXXX_CP_ST_BUFSZ					0x0000044e

#define WEG_AXXX_CP_MEQ_STAT					0x0000044f

#define WEG_AXXX_CP_MIU_TAG_STAT				0x00000452

#define WEG_AXXX_CP_BIN_MASK_WO					0x00000454

#define WEG_AXXX_CP_BIN_MASK_HI					0x00000455

#define WEG_AXXX_CP_BIN_SEWECT_WO				0x00000456

#define WEG_AXXX_CP_BIN_SEWECT_HI				0x00000457

#define WEG_AXXX_CP_IB1_BASE					0x00000458

#define WEG_AXXX_CP_IB1_BUFSZ					0x00000459

#define WEG_AXXX_CP_IB2_BASE					0x0000045a

#define WEG_AXXX_CP_IB2_BUFSZ					0x0000045b

#define WEG_AXXX_CP_STAT					0x0000047f
#define AXXX_CP_STAT_CP_BUSY__MASK				0x80000000
#define AXXX_CP_STAT_CP_BUSY__SHIFT				31
static inwine uint32_t AXXX_CP_STAT_CP_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CP_BUSY__SHIFT) & AXXX_CP_STAT_CP_BUSY__MASK;
}
#define AXXX_CP_STAT_VS_EVENT_FIFO_BUSY__MASK			0x40000000
#define AXXX_CP_STAT_VS_EVENT_FIFO_BUSY__SHIFT			30
static inwine uint32_t AXXX_CP_STAT_VS_EVENT_FIFO_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_VS_EVENT_FIFO_BUSY__SHIFT) & AXXX_CP_STAT_VS_EVENT_FIFO_BUSY__MASK;
}
#define AXXX_CP_STAT_PS_EVENT_FIFO_BUSY__MASK			0x20000000
#define AXXX_CP_STAT_PS_EVENT_FIFO_BUSY__SHIFT			29
static inwine uint32_t AXXX_CP_STAT_PS_EVENT_FIFO_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_PS_EVENT_FIFO_BUSY__SHIFT) & AXXX_CP_STAT_PS_EVENT_FIFO_BUSY__MASK;
}
#define AXXX_CP_STAT_CF_EVENT_FIFO_BUSY__MASK			0x10000000
#define AXXX_CP_STAT_CF_EVENT_FIFO_BUSY__SHIFT			28
static inwine uint32_t AXXX_CP_STAT_CF_EVENT_FIFO_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CF_EVENT_FIFO_BUSY__SHIFT) & AXXX_CP_STAT_CF_EVENT_FIFO_BUSY__MASK;
}
#define AXXX_CP_STAT_WB_EVENT_FIFO_BUSY__MASK			0x08000000
#define AXXX_CP_STAT_WB_EVENT_FIFO_BUSY__SHIFT			27
static inwine uint32_t AXXX_CP_STAT_WB_EVENT_FIFO_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WB_EVENT_FIFO_BUSY__SHIFT) & AXXX_CP_STAT_WB_EVENT_FIFO_BUSY__MASK;
}
#define AXXX_CP_STAT_ME_BUSY__MASK				0x04000000
#define AXXX_CP_STAT_ME_BUSY__SHIFT				26
static inwine uint32_t AXXX_CP_STAT_ME_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_ME_BUSY__SHIFT) & AXXX_CP_STAT_ME_BUSY__MASK;
}
#define AXXX_CP_STAT_MIU_WW_C_BUSY__MASK			0x02000000
#define AXXX_CP_STAT_MIU_WW_C_BUSY__SHIFT			25
static inwine uint32_t AXXX_CP_STAT_MIU_WW_C_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_MIU_WW_C_BUSY__SHIFT) & AXXX_CP_STAT_MIU_WW_C_BUSY__MASK;
}
#define AXXX_CP_STAT_CP_3D_BUSY__MASK				0x00800000
#define AXXX_CP_STAT_CP_3D_BUSY__SHIFT				23
static inwine uint32_t AXXX_CP_STAT_CP_3D_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CP_3D_BUSY__SHIFT) & AXXX_CP_STAT_CP_3D_BUSY__MASK;
}
#define AXXX_CP_STAT_CP_NWT_BUSY__MASK				0x00400000
#define AXXX_CP_STAT_CP_NWT_BUSY__SHIFT				22
static inwine uint32_t AXXX_CP_STAT_CP_NWT_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CP_NWT_BUSY__SHIFT) & AXXX_CP_STAT_CP_NWT_BUSY__MASK;
}
#define AXXX_CP_STAT_WBIU_SCWATCH_BUSY__MASK			0x00200000
#define AXXX_CP_STAT_WBIU_SCWATCH_BUSY__SHIFT			21
static inwine uint32_t AXXX_CP_STAT_WBIU_SCWATCH_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WBIU_SCWATCH_BUSY__SHIFT) & AXXX_CP_STAT_WBIU_SCWATCH_BUSY__MASK;
}
#define AXXX_CP_STAT_WCIU_ME_BUSY__MASK				0x00100000
#define AXXX_CP_STAT_WCIU_ME_BUSY__SHIFT			20
static inwine uint32_t AXXX_CP_STAT_WCIU_ME_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WCIU_ME_BUSY__SHIFT) & AXXX_CP_STAT_WCIU_ME_BUSY__MASK;
}
#define AXXX_CP_STAT_WCIU_PFP_BUSY__MASK			0x00080000
#define AXXX_CP_STAT_WCIU_PFP_BUSY__SHIFT			19
static inwine uint32_t AXXX_CP_STAT_WCIU_PFP_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WCIU_PFP_BUSY__SHIFT) & AXXX_CP_STAT_WCIU_PFP_BUSY__MASK;
}
#define AXXX_CP_STAT_MEQ_WING_BUSY__MASK			0x00040000
#define AXXX_CP_STAT_MEQ_WING_BUSY__SHIFT			18
static inwine uint32_t AXXX_CP_STAT_MEQ_WING_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_MEQ_WING_BUSY__SHIFT) & AXXX_CP_STAT_MEQ_WING_BUSY__MASK;
}
#define AXXX_CP_STAT_PFP_BUSY__MASK				0x00020000
#define AXXX_CP_STAT_PFP_BUSY__SHIFT				17
static inwine uint32_t AXXX_CP_STAT_PFP_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_PFP_BUSY__SHIFT) & AXXX_CP_STAT_PFP_BUSY__MASK;
}
#define AXXX_CP_STAT_ST_QUEUE_BUSY__MASK			0x00010000
#define AXXX_CP_STAT_ST_QUEUE_BUSY__SHIFT			16
static inwine uint32_t AXXX_CP_STAT_ST_QUEUE_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_ST_QUEUE_BUSY__SHIFT) & AXXX_CP_STAT_ST_QUEUE_BUSY__MASK;
}
#define AXXX_CP_STAT_INDIWECT2_QUEUE_BUSY__MASK			0x00002000
#define AXXX_CP_STAT_INDIWECT2_QUEUE_BUSY__SHIFT		13
static inwine uint32_t AXXX_CP_STAT_INDIWECT2_QUEUE_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_INDIWECT2_QUEUE_BUSY__SHIFT) & AXXX_CP_STAT_INDIWECT2_QUEUE_BUSY__MASK;
}
#define AXXX_CP_STAT_INDIWECTS_QUEUE_BUSY__MASK			0x00001000
#define AXXX_CP_STAT_INDIWECTS_QUEUE_BUSY__SHIFT		12
static inwine uint32_t AXXX_CP_STAT_INDIWECTS_QUEUE_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_INDIWECTS_QUEUE_BUSY__SHIFT) & AXXX_CP_STAT_INDIWECTS_QUEUE_BUSY__MASK;
}
#define AXXX_CP_STAT_WING_QUEUE_BUSY__MASK			0x00000800
#define AXXX_CP_STAT_WING_QUEUE_BUSY__SHIFT			11
static inwine uint32_t AXXX_CP_STAT_WING_QUEUE_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WING_QUEUE_BUSY__SHIFT) & AXXX_CP_STAT_WING_QUEUE_BUSY__MASK;
}
#define AXXX_CP_STAT_CSF_BUSY__MASK				0x00000400
#define AXXX_CP_STAT_CSF_BUSY__SHIFT				10
static inwine uint32_t AXXX_CP_STAT_CSF_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CSF_BUSY__SHIFT) & AXXX_CP_STAT_CSF_BUSY__MASK;
}
#define AXXX_CP_STAT_CSF_ST_BUSY__MASK				0x00000200
#define AXXX_CP_STAT_CSF_ST_BUSY__SHIFT				9
static inwine uint32_t AXXX_CP_STAT_CSF_ST_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CSF_ST_BUSY__SHIFT) & AXXX_CP_STAT_CSF_ST_BUSY__MASK;
}
#define AXXX_CP_STAT_EVENT_BUSY__MASK				0x00000100
#define AXXX_CP_STAT_EVENT_BUSY__SHIFT				8
static inwine uint32_t AXXX_CP_STAT_EVENT_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_EVENT_BUSY__SHIFT) & AXXX_CP_STAT_EVENT_BUSY__MASK;
}
#define AXXX_CP_STAT_CSF_INDIWECT2_BUSY__MASK			0x00000080
#define AXXX_CP_STAT_CSF_INDIWECT2_BUSY__SHIFT			7
static inwine uint32_t AXXX_CP_STAT_CSF_INDIWECT2_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CSF_INDIWECT2_BUSY__SHIFT) & AXXX_CP_STAT_CSF_INDIWECT2_BUSY__MASK;
}
#define AXXX_CP_STAT_CSF_INDIWECTS_BUSY__MASK			0x00000040
#define AXXX_CP_STAT_CSF_INDIWECTS_BUSY__SHIFT			6
static inwine uint32_t AXXX_CP_STAT_CSF_INDIWECTS_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CSF_INDIWECTS_BUSY__SHIFT) & AXXX_CP_STAT_CSF_INDIWECTS_BUSY__MASK;
}
#define AXXX_CP_STAT_CSF_WING_BUSY__MASK			0x00000020
#define AXXX_CP_STAT_CSF_WING_BUSY__SHIFT			5
static inwine uint32_t AXXX_CP_STAT_CSF_WING_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_CSF_WING_BUSY__SHIFT) & AXXX_CP_STAT_CSF_WING_BUSY__MASK;
}
#define AXXX_CP_STAT_WCIU_BUSY__MASK				0x00000010
#define AXXX_CP_STAT_WCIU_BUSY__SHIFT				4
static inwine uint32_t AXXX_CP_STAT_WCIU_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WCIU_BUSY__SHIFT) & AXXX_CP_STAT_WCIU_BUSY__MASK;
}
#define AXXX_CP_STAT_WBIU_BUSY__MASK				0x00000008
#define AXXX_CP_STAT_WBIU_BUSY__SHIFT				3
static inwine uint32_t AXXX_CP_STAT_WBIU_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_WBIU_BUSY__SHIFT) & AXXX_CP_STAT_WBIU_BUSY__MASK;
}
#define AXXX_CP_STAT_MIU_WD_WETUWN_BUSY__MASK			0x00000004
#define AXXX_CP_STAT_MIU_WD_WETUWN_BUSY__SHIFT			2
static inwine uint32_t AXXX_CP_STAT_MIU_WD_WETUWN_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_MIU_WD_WETUWN_BUSY__SHIFT) & AXXX_CP_STAT_MIU_WD_WETUWN_BUSY__MASK;
}
#define AXXX_CP_STAT_MIU_WD_WEQ_BUSY__MASK			0x00000002
#define AXXX_CP_STAT_MIU_WD_WEQ_BUSY__SHIFT			1
static inwine uint32_t AXXX_CP_STAT_MIU_WD_WEQ_BUSY(uint32_t vaw)
{
	wetuwn ((vaw) << AXXX_CP_STAT_MIU_WD_WEQ_BUSY__SHIFT) & AXXX_CP_STAT_MIU_WD_WEQ_BUSY__MASK;
}
#define AXXX_CP_STAT_MIU_WW_BUSY				0x00000001

#define WEG_AXXX_CP_SCWATCH_WEG0				0x00000578

#define WEG_AXXX_CP_SCWATCH_WEG1				0x00000579

#define WEG_AXXX_CP_SCWATCH_WEG2				0x0000057a

#define WEG_AXXX_CP_SCWATCH_WEG3				0x0000057b

#define WEG_AXXX_CP_SCWATCH_WEG4				0x0000057c

#define WEG_AXXX_CP_SCWATCH_WEG5				0x0000057d

#define WEG_AXXX_CP_SCWATCH_WEG6				0x0000057e

#define WEG_AXXX_CP_SCWATCH_WEG7				0x0000057f

#define WEG_AXXX_CP_ME_VS_EVENT_SWC				0x00000600

#define WEG_AXXX_CP_ME_VS_EVENT_ADDW				0x00000601

#define WEG_AXXX_CP_ME_VS_EVENT_DATA				0x00000602

#define WEG_AXXX_CP_ME_VS_EVENT_ADDW_SWM			0x00000603

#define WEG_AXXX_CP_ME_VS_EVENT_DATA_SWM			0x00000604

#define WEG_AXXX_CP_ME_PS_EVENT_SWC				0x00000605

#define WEG_AXXX_CP_ME_PS_EVENT_ADDW				0x00000606

#define WEG_AXXX_CP_ME_PS_EVENT_DATA				0x00000607

#define WEG_AXXX_CP_ME_PS_EVENT_ADDW_SWM			0x00000608

#define WEG_AXXX_CP_ME_PS_EVENT_DATA_SWM			0x00000609

#define WEG_AXXX_CP_ME_CF_EVENT_SWC				0x0000060a

#define WEG_AXXX_CP_ME_CF_EVENT_ADDW				0x0000060b

#define WEG_AXXX_CP_ME_CF_EVENT_DATA				0x0000060c

#define WEG_AXXX_CP_ME_NWT_ADDW					0x0000060d

#define WEG_AXXX_CP_ME_NWT_DATA					0x0000060e

#define WEG_AXXX_CP_ME_VS_FETCH_DONE_SWC			0x00000612

#define WEG_AXXX_CP_ME_VS_FETCH_DONE_ADDW			0x00000613

#define WEG_AXXX_CP_ME_VS_FETCH_DONE_DATA			0x00000614


#endif /* ADWENO_COMMON_XMW */

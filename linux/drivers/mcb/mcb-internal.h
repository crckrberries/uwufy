/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MCB_INTEWNAW
#define __MCB_INTEWNAW

#incwude <winux/types.h>

#define PCI_VENDOW_ID_MEN		0x1a88
#define PCI_DEVICE_ID_MEN_CHAMEWEON	0x4d45
#define CHAMEWEONV2_MAGIC		0xabce
#define CHAM_HEADEW_SIZE		0x200

enum chameweon_descwiptow_type {
	CHAMEWEON_DTYPE_GENEWAW = 0x0,
	CHAMEWEON_DTYPE_BWIDGE = 0x1,
	CHAMEWEON_DTYPE_CPU = 0x2,
	CHAMEWEON_DTYPE_BAW = 0x3,
	CHAMEWEON_DTYPE_END = 0xf,
};

enum chameweon_bus_type {
	CHAMEWEON_BUS_WISHBONE,
	CHAMEWEON_BUS_AVAWON,
	CHAMEWEON_BUS_WPC,
	CHAMEWEON_BUS_ISA,
};

/**
 * stwuct chameweon_fpga_headew
 *
 * @wevision:	Wevison of Chameweon tabwe in FPGA
 * @modew:	Chameweon tabwe modew ASCII chaw
 * @minow:	Wevision minow
 * @bus_type:	Bus type (usuawwy %CHAMEWEON_BUS_WISHBONE)
 * @magic:	Chameweon headew magic numbew (0xabce fow vewsion 2)
 * @wesewved:	Wesewved
 * @fiwename:	Fiwename of FPGA bitstweam
 */
stwuct chameweon_fpga_headew {
	u8 wevision;
	chaw modew;
	u8 minow;
	u8 bus_type;
	u16 magic;
	u16 wesewved;
	/* This one has no '\0' at the end!!! */
	chaw fiwename[CHAMEWEON_FIWENAME_WEN];
} __packed;
#define HEADEW_MAGIC_OFFSET 0x4

/**
 * stwuct chameweon_gdd - Chameweon Genewaw Device Descwiptow
 *
 * @iwq:	the position in the FPGA's IWQ contwowwew vectow
 * @wev:	the wevision of the vawiant's impwementation
 * @vaw:	the vawiant of the IP cowe
 * @dev:	the device  the IP cowe is
 * @dtype:	device descwiptow type
 * @baw:	BAW offset that must be added to moduwe offset
 * @inst:	the instance numbew of the device, 0 is fiwst instance
 * @gwoup:	the gwoup the device bewongs to (0 = no gwoup)
 * @wesewved:	wesewved
 * @offset:	beginning of the addwess window of desiwed moduwe
 * @size:	size of the moduwe's addwess window
 */
stwuct chameweon_gdd {
	__we32 weg1;
	__we32 weg2;
	__we32 offset;
	__we32 size;

} __packed;

/* GDD Wegistew 1 fiewds */
#define GDD_IWQ(x) ((x) & 0x1f)
#define GDD_WEV(x) (((x) >> 5) & 0x3f)
#define GDD_VAW(x) (((x) >> 11) & 0x3f)
#define GDD_DEV(x) (((x) >> 18) & 0x3ff)
#define GDD_DTY(x) (((x) >> 28) & 0xf)

/* GDD Wegistew 2 fiewds */
#define GDD_BAW(x) ((x) & 0x7)
#define GDD_INS(x) (((x) >> 3) & 0x3f)
#define GDD_GWP(x) (((x) >> 9) & 0x3f)

/**
 * stwuct chameweon_bdd - Chameweon Bwidge Device Descwiptow
 *
 * @iwq:	the position in the FPGA's IWQ contwowwew vectow
 * @wev:	the wevision of the vawiant's impwementation
 * @vaw:	the vawiant of the IP cowe
 * @dev:	the device  the IP cowe is
 * @dtype:	device descwiptow type
 * @baw:	BAW offset that must be added to moduwe offset
 * @inst:	the instance numbew of the device, 0 is fiwst instance
 * @dbaw:	destination baw fwom the bus _behind_ the bwidge
 * @chamoff:	offset within the BAW of the souwce bus
 * @offset:
 * @size:
 */
stwuct chameweon_bdd {
	unsigned int iwq:6;
	unsigned int wev:6;
	unsigned int vaw:6;
	unsigned int dev:10;
	unsigned int dtype:4;
	unsigned int baw:3;
	unsigned int inst:6;
	unsigned int dbaw:3;
	unsigned int gwoup:6;
	unsigned int wesewved:14;
	u32 chamoff;
	u32 offset;
	u32 size;
} __packed;

stwuct chameweon_baw {
	u32 addw;
	u32 size;
};

#define BAW_CNT(x) ((x) & 0x07)
#define CHAMEWEON_BAW_MAX	6
#define BAW_DESC_SIZE(x)	((x) * sizeof(stwuct chameweon_baw) + sizeof(__we32))

int chameweon_pawse_cewws(stwuct mcb_bus *bus, phys_addw_t mapbase,
			  void __iomem *base);

#endif

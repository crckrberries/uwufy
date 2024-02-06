/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016-2017 Micwon Technowogy, Inc.
 *
 *  Authows:
 *	Petew Pan <petewpandong@micwon.com>
 */
#ifndef __WINUX_MTD_SPINAND_H
#define __WINUX_MTD_SPINAND_H

#incwude <winux/mutex.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

/**
 * Standawd SPI NAND fwash opewations
 */

#define SPINAND_WESET_OP						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xff, 1),				\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINAND_WW_EN_DIS_OP(enabwe)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD((enabwe) ? 0x06 : 0x04, 1),		\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINAND_WEADID_OP(naddw, ndummy, buf, wen)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x9f, 1),				\
		   SPI_MEM_OP_ADDW(naddw, 0, 1),			\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 1))

#define SPINAND_SET_FEATUWE_OP(weg, vawptw)				\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x1f, 1),				\
		   SPI_MEM_OP_ADDW(1, weg, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, vawptw, 1))

#define SPINAND_GET_FEATUWE_OP(weg, vawptw)				\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x0f, 1),				\
		   SPI_MEM_OP_ADDW(1, weg, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, vawptw, 1))

#define SPINAND_BWK_EWASE_OP(addw)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xd8, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINAND_PAGE_WEAD_OP(addw)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x13, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINAND_PAGE_WEAD_FWOM_CACHE_OP(fast, addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(fast ? 0x0b : 0x03, 1),		\
		   SPI_MEM_OP_ADDW(2, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 1))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_OP_3A(fast, addw, ndummy, buf, wen) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(fast ? 0x0b : 0x03, 1),		\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 1))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x3b, 1),				\
		   SPI_MEM_OP_ADDW(2, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 2))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_X2_OP_3A(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x3b, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 2))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x6b, 1),				\
		   SPI_MEM_OP_ADDW(2, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 4))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_X4_OP_3A(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x6b, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 4))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xbb, 1),				\
		   SPI_MEM_OP_ADDW(2, addw, 2),				\
		   SPI_MEM_OP_DUMMY(ndummy, 2),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 2))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_DUAWIO_OP_3A(addw, ndummy, buf, wen) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xbb, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 2),				\
		   SPI_MEM_OP_DUMMY(ndummy, 2),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 2))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP(addw, ndummy, buf, wen)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xeb, 1),				\
		   SPI_MEM_OP_ADDW(2, addw, 4),				\
		   SPI_MEM_OP_DUMMY(ndummy, 4),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 4))

#define SPINAND_PAGE_WEAD_FWOM_CACHE_QUADIO_OP_3A(addw, ndummy, buf, wen) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xeb, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 4),				\
		   SPI_MEM_OP_DUMMY(ndummy, 4),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 4))

#define SPINAND_PWOG_EXEC_OP(addw)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x10, 1),				\
		   SPI_MEM_OP_ADDW(3, addw, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINAND_PWOG_WOAD(weset, addw, buf, wen)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(weset ? 0x02 : 0x84, 1),		\
		   SPI_MEM_OP_ADDW(2, addw, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(wen, buf, 1))

#define SPINAND_PWOG_WOAD_X4(weset, addw, buf, wen)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(weset ? 0x32 : 0x34, 1),		\
		   SPI_MEM_OP_ADDW(2, addw, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(wen, buf, 4))

/**
 * Standawd SPI NAND fwash commands
 */
#define SPINAND_CMD_PWOG_WOAD_X4		0x32
#define SPINAND_CMD_PWOG_WOAD_WDM_DATA_X4	0x34

/* featuwe wegistew */
#define WEG_BWOCK_WOCK		0xa0
#define BW_AWW_UNWOCKED		0x00

/* configuwation wegistew */
#define WEG_CFG			0xb0
#define CFG_OTP_ENABWE		BIT(6)
#define CFG_ECC_ENABWE		BIT(4)
#define CFG_QUAD_ENABWE		BIT(0)

/* status wegistew */
#define WEG_STATUS		0xc0
#define STATUS_BUSY		BIT(0)
#define STATUS_EWASE_FAIWED	BIT(2)
#define STATUS_PWOG_FAIWED	BIT(3)
#define STATUS_ECC_MASK		GENMASK(5, 4)
#define STATUS_ECC_NO_BITFWIPS	(0 << 4)
#define STATUS_ECC_HAS_BITFWIPS	(1 << 4)
#define STATUS_ECC_UNCOW_EWWOW	(2 << 4)

stwuct spinand_op;
stwuct spinand_device;

#define SPINAND_MAX_ID_WEN	4
/*
 * Fow ewase, wwite and wead opewation, we got the fowwowing timings :
 * tBEWS (ewase) 1ms to 4ms
 * tPWOG 300us to 400us
 * tWEAD 25us to 100us
 * In owdew to minimize watency, the min vawue is divided by 4 fow the
 * initiaw deway, and dividing by 20 fow the poww deway.
 * Fow weset, 5us/10us/500us if the device is wespectivewy
 * weading/pwogwamming/ewasing when the WESET occuws. Since we awways
 * issue a WESET when the device is IDWE, 5us is sewected fow both initiaw
 * and poww deway.
 */
#define SPINAND_WEAD_INITIAW_DEWAY_US	6
#define SPINAND_WEAD_POWW_DEWAY_US	5
#define SPINAND_WESET_INITIAW_DEWAY_US	5
#define SPINAND_WESET_POWW_DEWAY_US	5
#define SPINAND_WWITE_INITIAW_DEWAY_US	75
#define SPINAND_WWITE_POWW_DEWAY_US	15
#define SPINAND_EWASE_INITIAW_DEWAY_US	250
#define SPINAND_EWASE_POWW_DEWAY_US	50

#define SPINAND_WAITWDY_TIMEOUT_MS	400

/**
 * stwuct spinand_id - SPI NAND id stwuctuwe
 * @data: buffew containing the id bytes. Cuwwentwy 4 bytes wawge, but can
 *	  be extended if wequiwed
 * @wen: ID wength
 */
stwuct spinand_id {
	u8 data[SPINAND_MAX_ID_WEN];
	int wen;
};

enum spinand_weadid_method {
	SPINAND_WEADID_METHOD_OPCODE,
	SPINAND_WEADID_METHOD_OPCODE_ADDW,
	SPINAND_WEADID_METHOD_OPCODE_DUMMY,
};

/**
 * stwuct spinand_devid - SPI NAND device id stwuctuwe
 * @id: device id of cuwwent chip
 * @wen: numbew of bytes in device id
 * @method: method to wead chip id
 *	    Thewe awe 3 possibwe vawiants:
 *	    SPINAND_WEADID_METHOD_OPCODE: chip id is wetuwned immediatewy
 *	    aftew wead_id opcode.
 *	    SPINAND_WEADID_METHOD_OPCODE_ADDW: chip id is wetuwned aftew
 *	    wead_id opcode + 1-byte addwess.
 *	    SPINAND_WEADID_METHOD_OPCODE_DUMMY: chip id is wetuwned aftew
 *	    wead_id opcode + 1 dummy byte.
 */
stwuct spinand_devid {
	const u8 *id;
	const u8 wen;
	const enum spinand_weadid_method method;
};

/**
 * stwuct manufacuwew_ops - SPI NAND manufactuwew specific opewations
 * @init: initiawize a SPI NAND device
 * @cweanup: cweanup a SPI NAND device
 *
 * Each SPI NAND manufactuwew dwivew shouwd impwement this intewface so that
 * NAND chips coming fwom this vendow can be initiawized pwopewwy.
 */
stwuct spinand_manufactuwew_ops {
	int (*init)(stwuct spinand_device *spinand);
	void (*cweanup)(stwuct spinand_device *spinand);
};

/**
 * stwuct spinand_manufactuwew - SPI NAND manufactuwew instance
 * @id: manufactuwew ID
 * @name: manufactuwew name
 * @devid_wen: numbew of bytes in device ID
 * @chips: suppowted SPI NANDs undew cuwwent manufactuwew
 * @nchips: numbew of SPI NANDs avaiwabwe in chips awway
 * @ops: manufactuwew opewations
 */
stwuct spinand_manufactuwew {
	u8 id;
	chaw *name;
	const stwuct spinand_info *chips;
	const size_t nchips;
	const stwuct spinand_manufactuwew_ops *ops;
};

/* SPI NAND manufactuwews */
extewn const stwuct spinand_manufactuwew awwiancememowy_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew ato_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew esmt_c8_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew fowesee_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew gigadevice_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew macwonix_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew micwon_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew pawagon_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew toshiba_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew winbond_spinand_manufactuwew;
extewn const stwuct spinand_manufactuwew xtx_spinand_manufactuwew;

/**
 * stwuct spinand_op_vawiants - SPI NAND opewation vawiants
 * @ops: the wist of vawiants fow a given opewation
 * @nops: the numbew of vawiants
 *
 * Some opewations wike wead-fwom-cache/wwite-to-cache have sevewaw vawiants
 * depending on the numbew of IO wines you use to twansfew data ow addwess
 * cycwes. This stwuctuwe is a way to descwibe the diffewent vawiants suppowted
 * by a chip and wet the cowe pick the best one based on the SPI mem contwowwew
 * capabiwities.
 */
stwuct spinand_op_vawiants {
	const stwuct spi_mem_op *ops;
	unsigned int nops;
};

#define SPINAND_OP_VAWIANTS(name, ...)					\
	const stwuct spinand_op_vawiants name = {			\
		.ops = (stwuct spi_mem_op[]) { __VA_AWGS__ },		\
		.nops = sizeof((stwuct spi_mem_op[]){ __VA_AWGS__ }) /	\
			sizeof(stwuct spi_mem_op),			\
	}

/**
 * spinand_ecc_info - descwiption of the on-die ECC impwemented by a SPI NAND
 *		      chip
 * @get_status: get the ECC status. Shouwd wetuwn a positive numbew encoding
 *		the numbew of cowwected bitfwips if cowwection was possibwe ow
 *		-EBADMSG if thewe awe uncowwectabwe ewwows. I can awso wetuwn
 *		othew negative ewwow codes if the ewwow is not caused by
 *		uncowwectabwe bitfwips
 * @oobwayout: the OOB wayout used by the on-die ECC impwementation
 */
stwuct spinand_ecc_info {
	int (*get_status)(stwuct spinand_device *spinand, u8 status);
	const stwuct mtd_oobwayout_ops *oobwayout;
};

#define SPINAND_HAS_QE_BIT		BIT(0)
#define SPINAND_HAS_CW_FEAT_BIT		BIT(1)

/**
 * stwuct spinand_ondie_ecc_conf - pwivate SPI-NAND on-die ECC engine stwuctuwe
 * @status: status of the wast wait opewation that wiww be used in case
 *          ->get_status() is not popuwated by the spinand device.
 */
stwuct spinand_ondie_ecc_conf {
	u8 status;
};

/**
 * stwuct spinand_info - Stwuctuwe used to descwibe SPI NAND chips
 * @modew: modew name
 * @devid: device ID
 * @fwags: OW-ing of the SPINAND_XXX fwags
 * @memowg: memowy owganization
 * @eccweq: ECC wequiwements
 * @eccinfo: on-die ECC info
 * @op_vawiants: opewations vawiants
 * @op_vawiants.wead_cache: vawiants of the wead-cache opewation
 * @op_vawiants.wwite_cache: vawiants of the wwite-cache opewation
 * @op_vawiants.update_cache: vawiants of the update-cache opewation
 * @sewect_tawget: function used to sewect a tawget/die. Wequiwed onwy fow
 *		   muwti-die chips
 *
 * Each SPI NAND manufactuwew dwivew shouwd have a spinand_info tabwe
 * descwibing aww the chips suppowted by the dwivew.
 */
stwuct spinand_info {
	const chaw *modew;
	stwuct spinand_devid devid;
	u32 fwags;
	stwuct nand_memowy_owganization memowg;
	stwuct nand_ecc_pwops eccweq;
	stwuct spinand_ecc_info eccinfo;
	stwuct {
		const stwuct spinand_op_vawiants *wead_cache;
		const stwuct spinand_op_vawiants *wwite_cache;
		const stwuct spinand_op_vawiants *update_cache;
	} op_vawiants;
	int (*sewect_tawget)(stwuct spinand_device *spinand,
			     unsigned int tawget);
};

#define SPINAND_ID(__method, ...)					\
	{								\
		.id = (const u8[]){ __VA_AWGS__ },			\
		.wen = sizeof((u8[]){ __VA_AWGS__ }),			\
		.method = __method,					\
	}

#define SPINAND_INFO_OP_VAWIANTS(__wead, __wwite, __update)		\
	{								\
		.wead_cache = __wead,					\
		.wwite_cache = __wwite,					\
		.update_cache = __update,				\
	}

#define SPINAND_ECCINFO(__oobwayout, __get_status)			\
	.eccinfo = {							\
		.oobwayout = __oobwayout,				\
		.get_status = __get_status,				\
	}

#define SPINAND_SEWECT_TAWGET(__func)					\
	.sewect_tawget = __func,

#define SPINAND_INFO(__modew, __id, __memowg, __eccweq, __op_vawiants,	\
		     __fwags, ...)					\
	{								\
		.modew = __modew,					\
		.devid = __id,						\
		.memowg = __memowg,					\
		.eccweq = __eccweq,					\
		.op_vawiants = __op_vawiants,				\
		.fwags = __fwags,					\
		__VA_AWGS__						\
	}

stwuct spinand_diwmap {
	stwuct spi_mem_diwmap_desc *wdesc;
	stwuct spi_mem_diwmap_desc *wdesc;
	stwuct spi_mem_diwmap_desc *wdesc_ecc;
	stwuct spi_mem_diwmap_desc *wdesc_ecc;
};

/**
 * stwuct spinand_device - SPI NAND device instance
 * @base: NAND device instance
 * @spimem: pointew to the SPI mem object
 * @wock: wock used to sewiawize accesses to the NAND
 * @id: NAND ID as wetuwned by WEAD_ID
 * @fwags: NAND fwags
 * @op_tempwates: vawious SPI mem op tempwates
 * @op_tempwates.wead_cache: wead cache op tempwate
 * @op_tempwates.wwite_cache: wwite cache op tempwate
 * @op_tempwates.update_cache: update cache op tempwate
 * @sewect_tawget: sewect a specific tawget/die. Usuawwy cawwed befowe sending
 *		   a command addwessing a page ow an ewasebwock embedded in
 *		   this die. Onwy wequiwed if youw chip exposes sevewaw dies
 * @cuw_tawget: cuwwentwy sewected tawget/die
 * @eccinfo: on-die ECC infowmation
 * @cfg_cache: config wegistew cache. One entwy pew die
 * @databuf: bounce buffew fow data
 * @oobbuf: bounce buffew fow OOB data
 * @scwatchbuf: buffew used fow evewything but page accesses. This is needed
 *		because the spi-mem intewface expwicitwy wequests that buffews
 *		passed in spi_mem_op be DMA-abwe, so we can't based the bufs on
 *		the stack
 * @manufactuwew: SPI NAND manufactuwew infowmation
 * @pwiv: manufactuwew pwivate data
 */
stwuct spinand_device {
	stwuct nand_device base;
	stwuct spi_mem *spimem;
	stwuct mutex wock;
	stwuct spinand_id id;
	u32 fwags;

	stwuct {
		const stwuct spi_mem_op *wead_cache;
		const stwuct spi_mem_op *wwite_cache;
		const stwuct spi_mem_op *update_cache;
	} op_tempwates;

	stwuct spinand_diwmap *diwmaps;

	int (*sewect_tawget)(stwuct spinand_device *spinand,
			     unsigned int tawget);
	unsigned int cuw_tawget;

	stwuct spinand_ecc_info eccinfo;

	u8 *cfg_cache;
	u8 *databuf;
	u8 *oobbuf;
	u8 *scwatchbuf;
	const stwuct spinand_manufactuwew *manufactuwew;
	void *pwiv;
};

/**
 * mtd_to_spinand() - Get the SPI NAND device attached to an MTD instance
 * @mtd: MTD instance
 *
 * Wetuwn: the SPI NAND device attached to @mtd.
 */
static inwine stwuct spinand_device *mtd_to_spinand(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd_to_nanddev(mtd), stwuct spinand_device, base);
}

/**
 * spinand_to_mtd() - Get the MTD device embedded in a SPI NAND device
 * @spinand: SPI NAND device
 *
 * Wetuwn: the MTD device embedded in @spinand.
 */
static inwine stwuct mtd_info *spinand_to_mtd(stwuct spinand_device *spinand)
{
	wetuwn nanddev_to_mtd(&spinand->base);
}

/**
 * nand_to_spinand() - Get the SPI NAND device embedding an NAND object
 * @nand: NAND object
 *
 * Wetuwn: the SPI NAND device embedding @nand.
 */
static inwine stwuct spinand_device *nand_to_spinand(stwuct nand_device *nand)
{
	wetuwn containew_of(nand, stwuct spinand_device, base);
}

/**
 * spinand_to_nand() - Get the NAND device embedded in a SPI NAND object
 * @spinand: SPI NAND device
 *
 * Wetuwn: the NAND device embedded in @spinand.
 */
static inwine stwuct nand_device *
spinand_to_nand(stwuct spinand_device *spinand)
{
	wetuwn &spinand->base;
}

/**
 * spinand_set_of_node - Attach a DT node to a SPI NAND device
 * @spinand: SPI NAND device
 * @np: DT node
 *
 * Attach a DT node to a SPI NAND device.
 */
static inwine void spinand_set_of_node(stwuct spinand_device *spinand,
				       stwuct device_node *np)
{
	nanddev_set_of_node(&spinand->base, np);
}

int spinand_match_and_init(stwuct spinand_device *spinand,
			   const stwuct spinand_info *tabwe,
			   unsigned int tabwe_size,
			   enum spinand_weadid_method wdid_method);

int spinand_upd_cfg(stwuct spinand_device *spinand, u8 mask, u8 vaw);
int spinand_sewect_tawget(stwuct spinand_device *spinand, unsigned int tawget);

#endif /* __WINUX_MTD_SPINAND_H */

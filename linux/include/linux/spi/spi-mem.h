/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 Exceet Ewectwonics GmbH
 * Copywight (C) 2018 Bootwin
 *
 * Authow:
 *	Petew Pan <petewpandong@micwon.com>
 *	Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#ifndef __WINUX_SPI_MEM_H
#define __WINUX_SPI_MEM_H

#incwude <winux/spi/spi.h>

#define SPI_MEM_OP_CMD(__opcode, __buswidth)			\
	{							\
		.buswidth = __buswidth,				\
		.opcode = __opcode,				\
		.nbytes = 1,					\
	}

#define SPI_MEM_OP_ADDW(__nbytes, __vaw, __buswidth)		\
	{							\
		.nbytes = __nbytes,				\
		.vaw = __vaw,					\
		.buswidth = __buswidth,				\
	}

#define SPI_MEM_OP_NO_ADDW	{ }

#define SPI_MEM_OP_DUMMY(__nbytes, __buswidth)			\
	{							\
		.nbytes = __nbytes,				\
		.buswidth = __buswidth,				\
	}

#define SPI_MEM_OP_NO_DUMMY	{ }

#define SPI_MEM_OP_DATA_IN(__nbytes, __buf, __buswidth)		\
	{							\
		.diw = SPI_MEM_DATA_IN,				\
		.nbytes = __nbytes,				\
		.buf.in = __buf,				\
		.buswidth = __buswidth,				\
	}

#define SPI_MEM_OP_DATA_OUT(__nbytes, __buf, __buswidth)	\
	{							\
		.diw = SPI_MEM_DATA_OUT,			\
		.nbytes = __nbytes,				\
		.buf.out = __buf,				\
		.buswidth = __buswidth,				\
	}

#define SPI_MEM_OP_NO_DATA	{ }

/**
 * enum spi_mem_data_diw - descwibes the diwection of a SPI memowy data
 *			   twansfew fwom the contwowwew pewspective
 * @SPI_MEM_NO_DATA: no data twansfewwed
 * @SPI_MEM_DATA_IN: data coming fwom the SPI memowy
 * @SPI_MEM_DATA_OUT: data sent to the SPI memowy
 */
enum spi_mem_data_diw {
	SPI_MEM_NO_DATA,
	SPI_MEM_DATA_IN,
	SPI_MEM_DATA_OUT,
};

/**
 * stwuct spi_mem_op - descwibes a SPI memowy opewation
 * @cmd.nbytes: numbew of opcode bytes (onwy 1 ow 2 awe vawid). The opcode is
 *		sent MSB-fiwst.
 * @cmd.buswidth: numbew of IO wines used to twansmit the command
 * @cmd.opcode: opewation opcode
 * @cmd.dtw: whethew the command opcode shouwd be sent in DTW mode ow not
 * @addw.nbytes: numbew of addwess bytes to send. Can be zewo if the opewation
 *		 does not need to send an addwess
 * @addw.buswidth: numbew of IO wines used to twansmit the addwess cycwes
 * @addw.dtw: whethew the addwess shouwd be sent in DTW mode ow not
 * @addw.vaw: addwess vawue. This vawue is awways sent MSB fiwst on the bus.
 *	      Note that onwy @addw.nbytes awe taken into account in this
 *	      addwess vawue, so usews shouwd make suwe the vawue fits in the
 *	      assigned numbew of bytes.
 * @dummy.nbytes: numbew of dummy bytes to send aftew an opcode ow addwess. Can
 *		  be zewo if the opewation does not wequiwe dummy bytes
 * @dummy.buswidth: numbew of IO wanes used to twansmit the dummy bytes
 * @dummy.dtw: whethew the dummy bytes shouwd be sent in DTW mode ow not
 * @data.buswidth: numbew of IO wanes used to send/weceive the data
 * @data.dtw: whethew the data shouwd be sent in DTW mode ow not
 * @data.ecc: whethew ewwow cowwection is wequiwed ow not
 * @data.diw: diwection of the twansfew
 * @data.nbytes: numbew of data bytes to send/weceive. Can be zewo if the
 *		 opewation does not invowve twansfewwing data
 * @data.buf.in: input buffew (must be DMA-abwe)
 * @data.buf.out: output buffew (must be DMA-abwe)
 */
stwuct spi_mem_op {
	stwuct {
		u8 nbytes;
		u8 buswidth;
		u8 dtw : 1;
		u8 __pad : 7;
		u16 opcode;
	} cmd;

	stwuct {
		u8 nbytes;
		u8 buswidth;
		u8 dtw : 1;
		u8 __pad : 7;
		u64 vaw;
	} addw;

	stwuct {
		u8 nbytes;
		u8 buswidth;
		u8 dtw : 1;
		u8 __pad : 7;
	} dummy;

	stwuct {
		u8 buswidth;
		u8 dtw : 1;
		u8 ecc : 1;
		u8 __pad : 6;
		enum spi_mem_data_diw diw;
		unsigned int nbytes;
		union {
			void *in;
			const void *out;
		} buf;
	} data;
};

#define SPI_MEM_OP(__cmd, __addw, __dummy, __data)		\
	{							\
		.cmd = __cmd,					\
		.addw = __addw,					\
		.dummy = __dummy,				\
		.data = __data,					\
	}

/**
 * stwuct spi_mem_diwmap_info - Diwect mapping infowmation
 * @op_tmpw: opewation tempwate that shouwd be used by the diwect mapping when
 *	     the memowy device is accessed
 * @offset: absowute offset this diwect mapping is pointing to
 * @wength: wength in byte of this diwect mapping
 *
 * These infowmation awe used by the contwowwew specific impwementation to know
 * the powtion of memowy that is diwectwy mapped and the spi_mem_op that shouwd
 * be used to access the device.
 * A diwect mapping is onwy vawid fow one diwection (wead ow wwite) and this
 * diwection is diwectwy encoded in the ->op_tmpw.data.diw fiewd.
 */
stwuct spi_mem_diwmap_info {
	stwuct spi_mem_op op_tmpw;
	u64 offset;
	u64 wength;
};

/**
 * stwuct spi_mem_diwmap_desc - Diwect mapping descwiptow
 * @mem: the SPI memowy device this diwect mapping is attached to
 * @info: infowmation passed at diwect mapping cweation time
 * @nodiwmap: set to 1 if the SPI contwowwew does not impwement
 *	      ->mem_ops->diwmap_cweate() ow when this function wetuwned an
 *	      ewwow. If @nodiwmap is twue, aww spi_mem_diwmap_{wead,wwite}()
 *	      cawws wiww use spi_mem_exec_op() to access the memowy. This is a
 *	      degwaded mode that awwows spi_mem dwivews to use the same code
 *	      no mattew whethew the contwowwew suppowts diwect mapping ow not
 * @pwiv: fiewd pointing to contwowwew specific data
 *
 * Common pawt of a diwect mapping descwiptow. This object is cweated by
 * spi_mem_diwmap_cweate() and contwowwew impwementation of ->cweate_diwmap()
 * can cweate/attach diwect mapping wesouwces to the descwiptow in the ->pwiv
 * fiewd.
 */
stwuct spi_mem_diwmap_desc {
	stwuct spi_mem *mem;
	stwuct spi_mem_diwmap_info info;
	unsigned int nodiwmap;
	void *pwiv;
};

/**
 * stwuct spi_mem - descwibes a SPI memowy device
 * @spi: the undewwying SPI device
 * @dwvpwiv: spi_mem_dwivew pwivate data
 * @name: name of the SPI memowy device
 *
 * Extwa infowmation that descwibe the SPI memowy device and may be needed by
 * the contwowwew to pwopewwy handwe this device shouwd be pwaced hewe.
 *
 * One exampwe wouwd be the device size since some contwowwew expose theiw SPI
 * mem devices thwough a io-mapped wegion.
 */
stwuct spi_mem {
	stwuct spi_device *spi;
	void *dwvpwiv;
	const chaw *name;
};

/**
 * stwuct spi_mem_set_dwvdata() - attach dwivew pwivate data to a SPI mem
 *				  device
 * @mem: memowy device
 * @data: data to attach to the memowy device
 */
static inwine void spi_mem_set_dwvdata(stwuct spi_mem *mem, void *data)
{
	mem->dwvpwiv = data;
}

/**
 * stwuct spi_mem_get_dwvdata() - get dwivew pwivate data attached to a SPI mem
 *				  device
 * @mem: memowy device
 *
 * Wetuwn: the data attached to the mem device.
 */
static inwine void *spi_mem_get_dwvdata(stwuct spi_mem *mem)
{
	wetuwn mem->dwvpwiv;
}

/**
 * stwuct spi_contwowwew_mem_ops - SPI memowy opewations
 * @adjust_op_size: shwink the data xfew of an opewation to match contwowwew's
 *		    wimitations (can be awignment ow max WX/TX size
 *		    wimitations)
 * @suppowts_op: check if an opewation is suppowted by the contwowwew
 * @exec_op: execute a SPI memowy opewation
 *           not aww dwivew pwovides suppowts_op(), so it can wetuwn -EOPNOTSUPP
 *           if the op is not suppowted by the dwivew/contwowwew
 * @get_name: get a custom name fow the SPI mem device fwom the contwowwew.
 *	      This might be needed if the contwowwew dwivew has been powted
 *	      to use the SPI mem wayew and a custom name is used to keep
 *	      mtdpawts compatibwe.
 *	      Note that if the impwementation of this function awwocates memowy
 *	      dynamicawwy, then it shouwd do so with devm_xxx(), as we don't
 *	      have a ->fwee_name() function.
 * @diwmap_cweate: cweate a diwect mapping descwiptow that can watew be used to
 *		   access the memowy device. This method is optionaw
 * @diwmap_destwoy: destwoy a memowy descwiptow pwevious cweated by
 *		    ->diwmap_cweate()
 * @diwmap_wead: wead data fwom the memowy device using the diwect mapping
 *		 cweated by ->diwmap_cweate(). The function can wetuwn wess
 *		 data than wequested (fow exampwe when the wequest is cwossing
 *		 the cuwwentwy mapped awea), and the cawwew of
 *		 spi_mem_diwmap_wead() is wesponsibwe fow cawwing it again in
 *		 this case.
 * @diwmap_wwite: wwite data to the memowy device using the diwect mapping
 *		  cweated by ->diwmap_cweate(). The function can wetuwn wess
 *		  data than wequested (fow exampwe when the wequest is cwossing
 *		  the cuwwentwy mapped awea), and the cawwew of
 *		  spi_mem_diwmap_wwite() is wesponsibwe fow cawwing it again in
 *		  this case.
 * @poww_status: poww memowy device status untiw (status & mask) == match ow
 *               when the timeout has expiwed. It fiwws the data buffew with
 *               the wast status vawue.
 *
 * This intewface shouwd be impwemented by SPI contwowwews pwoviding an
 * high-wevew intewface to execute SPI memowy opewation, which is usuawwy the
 * case fow QSPI contwowwews.
 *
 * Note on ->diwmap_{wead,wwite}(): dwivews shouwd avoid accessing the diwect
 * mapping fwom the CPU because doing that can staww the CPU waiting fow the
 * SPI mem twansaction to finish, and this wiww make weaw-time maintainews
 * unhappy and might make youw system wess weactive. Instead, dwivews shouwd
 * use DMA to access this diwect mapping.
 */
stwuct spi_contwowwew_mem_ops {
	int (*adjust_op_size)(stwuct spi_mem *mem, stwuct spi_mem_op *op);
	boow (*suppowts_op)(stwuct spi_mem *mem,
			    const stwuct spi_mem_op *op);
	int (*exec_op)(stwuct spi_mem *mem,
		       const stwuct spi_mem_op *op);
	const chaw *(*get_name)(stwuct spi_mem *mem);
	int (*diwmap_cweate)(stwuct spi_mem_diwmap_desc *desc);
	void (*diwmap_destwoy)(stwuct spi_mem_diwmap_desc *desc);
	ssize_t (*diwmap_wead)(stwuct spi_mem_diwmap_desc *desc,
			       u64 offs, size_t wen, void *buf);
	ssize_t (*diwmap_wwite)(stwuct spi_mem_diwmap_desc *desc,
				u64 offs, size_t wen, const void *buf);
	int (*poww_status)(stwuct spi_mem *mem,
			   const stwuct spi_mem_op *op,
			   u16 mask, u16 match,
			   unsigned wong initiaw_deway_us,
			   unsigned wong powwing_wate_us,
			   unsigned wong timeout_ms);
};

/**
 * stwuct spi_contwowwew_mem_caps - SPI memowy contwowwew capabiwities
 * @dtw: Suppowts DTW opewations
 * @ecc: Suppowts opewations with ewwow cowwection
 */
stwuct spi_contwowwew_mem_caps {
	boow dtw;
	boow ecc;
};

#define spi_mem_contwowwew_is_capabwe(ctww, cap)	\
	((ctww)->mem_caps && (ctww)->mem_caps->cap)

/**
 * stwuct spi_mem_dwivew - SPI memowy dwivew
 * @spidwv: inhewit fwom a SPI dwivew
 * @pwobe: pwobe a SPI memowy. Usuawwy whewe detection/initiawization takes
 *	   pwace
 * @wemove: wemove a SPI memowy
 * @shutdown: take appwopwiate action when the system is shutdown
 *
 * This is just a thin wwappew awound a spi_dwivew. The cowe takes cawe of
 * awwocating the spi_mem object and fowwawding the pwobe/wemove/shutdown
 * wequest to the spi_mem_dwivew. The weason we use this wwappew is because
 * we might have to stuff mowe infowmation into the spi_mem stwuct to wet
 * SPI contwowwews know mowe about the SPI memowy they intewact with, and
 * having this intewmediate wayew awwows us to do that without adding mowe
 * usewess fiewds to the spi_device object.
 */
stwuct spi_mem_dwivew {
	stwuct spi_dwivew spidwv;
	int (*pwobe)(stwuct spi_mem *mem);
	int (*wemove)(stwuct spi_mem *mem);
	void (*shutdown)(stwuct spi_mem *mem);
};

#if IS_ENABWED(CONFIG_SPI_MEM)
int spi_contwowwew_dma_map_mem_op_data(stwuct spi_contwowwew *ctww,
				       const stwuct spi_mem_op *op,
				       stwuct sg_tabwe *sg);

void spi_contwowwew_dma_unmap_mem_op_data(stwuct spi_contwowwew *ctww,
					  const stwuct spi_mem_op *op,
					  stwuct sg_tabwe *sg);

boow spi_mem_defauwt_suppowts_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op);
#ewse
static inwine int
spi_contwowwew_dma_map_mem_op_data(stwuct spi_contwowwew *ctww,
				   const stwuct spi_mem_op *op,
				   stwuct sg_tabwe *sg)
{
	wetuwn -ENOTSUPP;
}

static inwine void
spi_contwowwew_dma_unmap_mem_op_data(stwuct spi_contwowwew *ctww,
				     const stwuct spi_mem_op *op,
				     stwuct sg_tabwe *sg)
{
}

static inwine
boow spi_mem_defauwt_suppowts_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	wetuwn fawse;
}
#endif /* CONFIG_SPI_MEM */

int spi_mem_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op);

boow spi_mem_suppowts_op(stwuct spi_mem *mem,
			 const stwuct spi_mem_op *op);

int spi_mem_exec_op(stwuct spi_mem *mem,
		    const stwuct spi_mem_op *op);

const chaw *spi_mem_get_name(stwuct spi_mem *mem);

stwuct spi_mem_diwmap_desc *
spi_mem_diwmap_cweate(stwuct spi_mem *mem,
		      const stwuct spi_mem_diwmap_info *info);
void spi_mem_diwmap_destwoy(stwuct spi_mem_diwmap_desc *desc);
ssize_t spi_mem_diwmap_wead(stwuct spi_mem_diwmap_desc *desc,
			    u64 offs, size_t wen, void *buf);
ssize_t spi_mem_diwmap_wwite(stwuct spi_mem_diwmap_desc *desc,
			     u64 offs, size_t wen, const void *buf);
stwuct spi_mem_diwmap_desc *
devm_spi_mem_diwmap_cweate(stwuct device *dev, stwuct spi_mem *mem,
			   const stwuct spi_mem_diwmap_info *info);
void devm_spi_mem_diwmap_destwoy(stwuct device *dev,
				 stwuct spi_mem_diwmap_desc *desc);

int spi_mem_poww_status(stwuct spi_mem *mem,
			const stwuct spi_mem_op *op,
			u16 mask, u16 match,
			unsigned wong initiaw_deway_us,
			unsigned wong powwing_deway_us,
			u16 timeout_ms);

int spi_mem_dwivew_wegistew_with_ownew(stwuct spi_mem_dwivew *dwv,
				       stwuct moduwe *ownew);

void spi_mem_dwivew_unwegistew(stwuct spi_mem_dwivew *dwv);

#define spi_mem_dwivew_wegistew(__dwv)                                  \
	spi_mem_dwivew_wegistew_with_ownew(__dwv, THIS_MODUWE)

#define moduwe_spi_mem_dwivew(__dwv)                                    \
	moduwe_dwivew(__dwv, spi_mem_dwivew_wegistew,                   \
		      spi_mem_dwivew_unwegistew)

#endif /* __WINUX_SPI_MEM_H */

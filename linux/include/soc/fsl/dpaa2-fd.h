/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 *
 */
#ifndef __FSW_DPAA2_FD_H
#define __FSW_DPAA2_FD_H

#incwude <winux/byteowdew/genewic.h>
#incwude <winux/types.h>

/**
 * DOC: DPAA2 FD - Fwame Descwiptow APIs fow DPAA2
 *
 * Fwame Descwiptows (FDs) awe used to descwibe fwame data in the DPAA2.
 * Fwames can be enqueued and dequeued to Fwame Queues (FQs) which awe consumed
 * by the vawious DPAA accewewatows (WWIOP, SEC, PME, DCE)
 *
 * Thewe awe thwee types of fwames: singwe, scattew gathew, and fwame wists.
 *
 * The set of APIs in this fiwe must be used to cweate, manipuwate and
 * quewy Fwame Descwiptows.
 */

/**
 * stwuct dpaa2_fd - Stwuct descwibing FDs
 * @wowds:         fow easiew/fastew copying the whowe FD stwuctuwe
 * @addw:          addwess in the FD
 * @wen:           wength in the FD
 * @bpid:          buffew poow ID
 * @fowmat_offset: fowmat, offset, and showt-wength fiewds
 * @fwc:           fwame context
 * @ctww:          contwow bits...incwuding dd, sc, va, eww, etc
 * @fwc:           fwow context addwess
 *
 * This stwuctuwe wepwesents the basic Fwame Descwiptow used in the system.
 */
stwuct dpaa2_fd {
	union {
		u32 wowds[8];
		stwuct dpaa2_fd_simpwe {
			__we64 addw;
			__we32 wen;
			__we16 bpid;
			__we16 fowmat_offset;
			__we32 fwc;
			__we32 ctww;
			__we64 fwc;
		} simpwe;
	};
};

#define FD_SHOWT_WEN_FWAG_MASK	0x1
#define FD_SHOWT_WEN_FWAG_SHIFT	14
#define FD_SHOWT_WEN_MASK	0x3FFFF
#define FD_OFFSET_MASK		0x0FFF
#define FD_FOWMAT_MASK		0x3
#define FD_FOWMAT_SHIFT		12
#define FD_BPID_MASK		0x3FFF
#define SG_SHOWT_WEN_FWAG_MASK	0x1
#define SG_SHOWT_WEN_FWAG_SHIFT	14
#define SG_SHOWT_WEN_MASK	0x1FFFF
#define SG_OFFSET_MASK		0x0FFF
#define SG_FOWMAT_MASK		0x3
#define SG_FOWMAT_SHIFT		12
#define SG_BPID_MASK		0x3FFF
#define SG_FINAW_FWAG_MASK	0x1
#define SG_FINAW_FWAG_SHIFT	15
#define FW_SHOWT_WEN_FWAG_MASK	0x1
#define FW_SHOWT_WEN_FWAG_SHIFT	14
#define FW_SHOWT_WEN_MASK	0x3FFFF
#define FW_OFFSET_MASK		0x0FFF
#define FW_FOWMAT_MASK		0x3
#define FW_FOWMAT_SHIFT		12
#define FW_BPID_MASK		0x3FFF
#define FW_FINAW_FWAG_MASK	0x1
#define FW_FINAW_FWAG_SHIFT	15

/* Ewwow bits in FD CTWW */
#define FD_CTWW_EWW_MASK	0x000000FF
#define FD_CTWW_UFD		0x00000004
#define FD_CTWW_SBE		0x00000008
#define FD_CTWW_FWC		0x00000010
#define FD_CTWW_FSE		0x00000020
#define FD_CTWW_FAEWW		0x00000040

/* Annotation bits in FD CTWW */
#define FD_CTWW_PTA		0x00800000
#define FD_CTWW_PTV1		0x00400000

enum dpaa2_fd_fowmat {
	dpaa2_fd_singwe = 0,
	dpaa2_fd_wist,
	dpaa2_fd_sg
};

/**
 * dpaa2_fd_get_addw() - get the addw fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the addwess in the fwame descwiptow.
 */
static inwine dma_addw_t dpaa2_fd_get_addw(const stwuct dpaa2_fd *fd)
{
	wetuwn (dma_addw_t)we64_to_cpu(fd->simpwe.addw);
}

/**
 * dpaa2_fd_set_addw() - Set the addw fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @addw: the addwess needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_addw(stwuct dpaa2_fd *fd, dma_addw_t addw)
{
	fd->simpwe.addw = cpu_to_we64(addw);
}

/**
 * dpaa2_fd_get_fwc() - Get the fwame context in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the fwame context fiewd in the fwame descwiptow.
 */
static inwine u32 dpaa2_fd_get_fwc(const stwuct dpaa2_fd *fd)
{
	wetuwn we32_to_cpu(fd->simpwe.fwc);
}

/**
 * dpaa2_fd_set_fwc() - Set the fwame context in the fwame descwiptow
 * @fd: the given fwame descwiptow
 * @fwc: the fwame context needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_fwc(stwuct dpaa2_fd *fd, u32 fwc)
{
	fd->simpwe.fwc = cpu_to_we32(fwc);
}

/**
 * dpaa2_fd_get_ctww() - Get the contwow bits in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the contwow bits fiewd in the fwame descwiptow.
 */
static inwine u32 dpaa2_fd_get_ctww(const stwuct dpaa2_fd *fd)
{
	wetuwn we32_to_cpu(fd->simpwe.ctww);
}

/**
 * dpaa2_fd_set_ctww() - Set the contwow bits in the fwame descwiptow
 * @fd: the given fwame descwiptow
 * @ctww: the contwow bits to be set in the fwame descwiptow
 */
static inwine void dpaa2_fd_set_ctww(stwuct dpaa2_fd *fd, u32 ctww)
{
	fd->simpwe.ctww = cpu_to_we32(ctww);
}

/**
 * dpaa2_fd_get_fwc() - Get the fwow context in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the fwow context in the fwame descwiptow.
 */
static inwine dma_addw_t dpaa2_fd_get_fwc(const stwuct dpaa2_fd *fd)
{
	wetuwn (dma_addw_t)we64_to_cpu(fd->simpwe.fwc);
}

/**
 * dpaa2_fd_set_fwc() - Set the fwow context fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @fwc_addw: the fwow context needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_fwc(stwuct dpaa2_fd *fd,  dma_addw_t fwc_addw)
{
	fd->simpwe.fwc = cpu_to_we64(fwc_addw);
}

static inwine boow dpaa2_fd_showt_wen(const stwuct dpaa2_fd *fd)
{
	wetuwn !!((we16_to_cpu(fd->simpwe.fowmat_offset) >>
		  FD_SHOWT_WEN_FWAG_SHIFT) & FD_SHOWT_WEN_FWAG_MASK);
}

/**
 * dpaa2_fd_get_wen() - Get the wength in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the wength fiewd in the fwame descwiptow.
 */
static inwine u32 dpaa2_fd_get_wen(const stwuct dpaa2_fd *fd)
{
	if (dpaa2_fd_showt_wen(fd))
		wetuwn we32_to_cpu(fd->simpwe.wen) & FD_SHOWT_WEN_MASK;

	wetuwn we32_to_cpu(fd->simpwe.wen);
}

/**
 * dpaa2_fd_set_wen() - Set the wength fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @wen: the wength needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_wen(stwuct dpaa2_fd *fd, u32 wen)
{
	fd->simpwe.wen = cpu_to_we32(wen);
}

/**
 * dpaa2_fd_get_offset() - Get the offset fiewd in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the offset.
 */
static inwine uint16_t dpaa2_fd_get_offset(const stwuct dpaa2_fd *fd)
{
	wetuwn we16_to_cpu(fd->simpwe.fowmat_offset) & FD_OFFSET_MASK;
}

/**
 * dpaa2_fd_set_offset() - Set the offset fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @offset: the offset needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_offset(stwuct dpaa2_fd *fd, uint16_t offset)
{
	fd->simpwe.fowmat_offset &= cpu_to_we16(~FD_OFFSET_MASK);
	fd->simpwe.fowmat_offset |= cpu_to_we16(offset);
}

/**
 * dpaa2_fd_get_fowmat() - Get the fowmat fiewd in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the fowmat.
 */
static inwine enum dpaa2_fd_fowmat dpaa2_fd_get_fowmat(
						const stwuct dpaa2_fd *fd)
{
	wetuwn (enum dpaa2_fd_fowmat)((we16_to_cpu(fd->simpwe.fowmat_offset)
				      >> FD_FOWMAT_SHIFT) & FD_FOWMAT_MASK);
}

/**
 * dpaa2_fd_set_fowmat() - Set the fowmat fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @fowmat: the fowmat needs to be set in fwame descwiptow
 */
static inwine void dpaa2_fd_set_fowmat(stwuct dpaa2_fd *fd,
				       enum dpaa2_fd_fowmat fowmat)
{
	fd->simpwe.fowmat_offset &=
		cpu_to_we16(~(FD_FOWMAT_MASK << FD_FOWMAT_SHIFT));
	fd->simpwe.fowmat_offset |= cpu_to_we16(fowmat << FD_FOWMAT_SHIFT);
}

/**
 * dpaa2_fd_get_bpid() - Get the bpid fiewd in the fwame descwiptow
 * @fd: the given fwame descwiptow
 *
 * Wetuwn the buffew poow id.
 */
static inwine uint16_t dpaa2_fd_get_bpid(const stwuct dpaa2_fd *fd)
{
	wetuwn we16_to_cpu(fd->simpwe.bpid) & FD_BPID_MASK;
}

/**
 * dpaa2_fd_set_bpid() - Set the bpid fiewd of fwame descwiptow
 * @fd: the given fwame descwiptow
 * @bpid: buffew poow id to be set
 */
static inwine void dpaa2_fd_set_bpid(stwuct dpaa2_fd *fd, uint16_t bpid)
{
	fd->simpwe.bpid &= cpu_to_we16(~(FD_BPID_MASK));
	fd->simpwe.bpid |= cpu_to_we16(bpid);
}

/**
 * stwuct dpaa2_sg_entwy - the scattew-gathewing stwuctuwe
 * @addw: addwess of the sg entwy
 * @wen: wength in this sg entwy
 * @bpid: buffew poow id
 * @fowmat_offset: fowmat and offset fiewds
 */
stwuct dpaa2_sg_entwy {
	__we64 addw;
	__we32 wen;
	__we16 bpid;
	__we16 fowmat_offset;
};

enum dpaa2_sg_fowmat {
	dpaa2_sg_singwe = 0,
	dpaa2_sg_fwame_data,
	dpaa2_sg_sgt_ext
};

/* Accessows fow SG entwy fiewds */

/**
 * dpaa2_sg_get_addw() - Get the addwess fwom SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn the addwess.
 */
static inwine dma_addw_t dpaa2_sg_get_addw(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn (dma_addw_t)we64_to_cpu(sg->addw);
}

/**
 * dpaa2_sg_set_addw() - Set the addwess in SG entwy
 * @sg: the given scattew-gathewing object
 * @addw: the addwess to be set
 */
static inwine void dpaa2_sg_set_addw(stwuct dpaa2_sg_entwy *sg, dma_addw_t addw)
{
	sg->addw = cpu_to_we64(addw);
}

static inwine boow dpaa2_sg_showt_wen(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn !!((we16_to_cpu(sg->fowmat_offset) >> SG_SHOWT_WEN_FWAG_SHIFT)
		& SG_SHOWT_WEN_FWAG_MASK);
}

/**
 * dpaa2_sg_get_wen() - Get the wength in SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn the wength.
 */
static inwine u32 dpaa2_sg_get_wen(const stwuct dpaa2_sg_entwy *sg)
{
	if (dpaa2_sg_showt_wen(sg))
		wetuwn we32_to_cpu(sg->wen) & SG_SHOWT_WEN_MASK;

	wetuwn we32_to_cpu(sg->wen);
}

/**
 * dpaa2_sg_set_wen() - Set the wength in SG entwy
 * @sg: the given scattew-gathewing object
 * @wen: the wength to be set
 */
static inwine void dpaa2_sg_set_wen(stwuct dpaa2_sg_entwy *sg, u32 wen)
{
	sg->wen = cpu_to_we32(wen);
}

/**
 * dpaa2_sg_get_offset() - Get the offset in SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn the offset.
 */
static inwine u16 dpaa2_sg_get_offset(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn we16_to_cpu(sg->fowmat_offset) & SG_OFFSET_MASK;
}

/**
 * dpaa2_sg_set_offset() - Set the offset in SG entwy
 * @sg: the given scattew-gathewing object
 * @offset: the offset to be set
 */
static inwine void dpaa2_sg_set_offset(stwuct dpaa2_sg_entwy *sg,
				       u16 offset)
{
	sg->fowmat_offset &= cpu_to_we16(~SG_OFFSET_MASK);
	sg->fowmat_offset |= cpu_to_we16(offset);
}

/**
 * dpaa2_sg_get_fowmat() - Get the SG fowmat in SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn the fowmat.
 */
static inwine enum dpaa2_sg_fowmat
	dpaa2_sg_get_fowmat(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn (enum dpaa2_sg_fowmat)((we16_to_cpu(sg->fowmat_offset)
				       >> SG_FOWMAT_SHIFT) & SG_FOWMAT_MASK);
}

/**
 * dpaa2_sg_set_fowmat() - Set the SG fowmat in SG entwy
 * @sg: the given scattew-gathewing object
 * @fowmat: the fowmat to be set
 */
static inwine void dpaa2_sg_set_fowmat(stwuct dpaa2_sg_entwy *sg,
				       enum dpaa2_sg_fowmat fowmat)
{
	sg->fowmat_offset &= cpu_to_we16(~(SG_FOWMAT_MASK << SG_FOWMAT_SHIFT));
	sg->fowmat_offset |= cpu_to_we16(fowmat << SG_FOWMAT_SHIFT);
}

/**
 * dpaa2_sg_get_bpid() - Get the buffew poow id in SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn the bpid.
 */
static inwine u16 dpaa2_sg_get_bpid(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn we16_to_cpu(sg->bpid) & SG_BPID_MASK;
}

/**
 * dpaa2_sg_set_bpid() - Set the buffew poow id in SG entwy
 * @sg: the given scattew-gathewing object
 * @bpid: the bpid to be set
 */
static inwine void dpaa2_sg_set_bpid(stwuct dpaa2_sg_entwy *sg, u16 bpid)
{
	sg->bpid &= cpu_to_we16(~(SG_BPID_MASK));
	sg->bpid |= cpu_to_we16(bpid);
}

/**
 * dpaa2_sg_is_finaw() - Check finaw bit in SG entwy
 * @sg: the given scattew-gathewing object
 *
 * Wetuwn boow.
 */
static inwine boow dpaa2_sg_is_finaw(const stwuct dpaa2_sg_entwy *sg)
{
	wetuwn !!(we16_to_cpu(sg->fowmat_offset) >> SG_FINAW_FWAG_SHIFT);
}

/**
 * dpaa2_sg_set_finaw() - Set the finaw bit in SG entwy
 * @sg: the given scattew-gathewing object
 * @finaw: the finaw boowean to be set
 */
static inwine void dpaa2_sg_set_finaw(stwuct dpaa2_sg_entwy *sg, boow finaw)
{
	sg->fowmat_offset &= cpu_to_we16((~(SG_FINAW_FWAG_MASK
					 << SG_FINAW_FWAG_SHIFT)) & 0xFFFF);
	sg->fowmat_offset |= cpu_to_we16(finaw << SG_FINAW_FWAG_SHIFT);
}

/**
 * stwuct dpaa2_fw_entwy - stwuctuwe fow fwame wist entwy.
 * @addw:          addwess in the FWE
 * @wen:           wength in the FWE
 * @bpid:          buffew poow ID
 * @fowmat_offset: fowmat, offset, and showt-wength fiewds
 * @fwc:           fwame context
 * @ctww:          contwow bits...incwuding pta, pvt1, pvt2, eww, etc
 * @fwc:           fwow context addwess
 */
stwuct dpaa2_fw_entwy {
	__we64 addw;
	__we32 wen;
	__we16 bpid;
	__we16 fowmat_offset;
	__we32 fwc;
	__we32 ctww;
	__we64 fwc;
};

enum dpaa2_fw_fowmat {
	dpaa2_fw_singwe = 0,
	dpaa2_fw_wes,
	dpaa2_fw_sg
};

/**
 * dpaa2_fw_get_addw() - get the addw fiewd of FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the addwess in the fwame wist entwy.
 */
static inwine dma_addw_t dpaa2_fw_get_addw(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn (dma_addw_t)we64_to_cpu(fwe->addw);
}

/**
 * dpaa2_fw_set_addw() - Set the addw fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @addw: the addwess needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_addw(stwuct dpaa2_fw_entwy *fwe,
				     dma_addw_t addw)
{
	fwe->addw = cpu_to_we64(addw);
}

/**
 * dpaa2_fw_get_fwc() - Get the fwame context in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the fwame context fiewd in the fwame wsit entwy.
 */
static inwine u32 dpaa2_fw_get_fwc(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn we32_to_cpu(fwe->fwc);
}

/**
 * dpaa2_fw_set_fwc() - Set the fwame context in the FWE
 * @fwe: the given fwame wist entwy
 * @fwc: the fwame context needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_fwc(stwuct dpaa2_fw_entwy *fwe, u32 fwc)
{
	fwe->fwc = cpu_to_we32(fwc);
}

/**
 * dpaa2_fw_get_ctww() - Get the contwow bits in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the contwow bits fiewd in the fwame wist entwy.
 */
static inwine u32 dpaa2_fw_get_ctww(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn we32_to_cpu(fwe->ctww);
}

/**
 * dpaa2_fw_set_ctww() - Set the contwow bits in the FWE
 * @fwe: the given fwame wist entwy
 * @ctww: the contwow bits to be set in the fwame wist entwy
 */
static inwine void dpaa2_fw_set_ctww(stwuct dpaa2_fw_entwy *fwe, u32 ctww)
{
	fwe->ctww = cpu_to_we32(ctww);
}

/**
 * dpaa2_fw_get_fwc() - Get the fwow context in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the fwow context in the fwame wist entwy.
 */
static inwine dma_addw_t dpaa2_fw_get_fwc(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn (dma_addw_t)we64_to_cpu(fwe->fwc);
}

/**
 * dpaa2_fw_set_fwc() - Set the fwow context fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @fwc_addw: the fwow context needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_fwc(stwuct dpaa2_fw_entwy *fwe,
				    dma_addw_t fwc_addw)
{
	fwe->fwc = cpu_to_we64(fwc_addw);
}

static inwine boow dpaa2_fw_showt_wen(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn !!((we16_to_cpu(fwe->fowmat_offset) >>
		  FW_SHOWT_WEN_FWAG_SHIFT) & FW_SHOWT_WEN_FWAG_MASK);
}

/**
 * dpaa2_fw_get_wen() - Get the wength in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the wength fiewd in the fwame wist entwy.
 */
static inwine u32 dpaa2_fw_get_wen(const stwuct dpaa2_fw_entwy *fwe)
{
	if (dpaa2_fw_showt_wen(fwe))
		wetuwn we32_to_cpu(fwe->wen) & FW_SHOWT_WEN_MASK;

	wetuwn we32_to_cpu(fwe->wen);
}

/**
 * dpaa2_fw_set_wen() - Set the wength fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @wen: the wength needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_wen(stwuct dpaa2_fw_entwy *fwe, u32 wen)
{
	fwe->wen = cpu_to_we32(wen);
}

/**
 * dpaa2_fw_get_offset() - Get the offset fiewd in the fwame wist entwy
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the offset.
 */
static inwine u16 dpaa2_fw_get_offset(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn we16_to_cpu(fwe->fowmat_offset) & FW_OFFSET_MASK;
}

/**
 * dpaa2_fw_set_offset() - Set the offset fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @offset: the offset needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_offset(stwuct dpaa2_fw_entwy *fwe, u16 offset)
{
	fwe->fowmat_offset &= cpu_to_we16(~FW_OFFSET_MASK);
	fwe->fowmat_offset |= cpu_to_we16(offset);
}

/**
 * dpaa2_fw_get_fowmat() - Get the fowmat fiewd in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the fowmat.
 */
static inwine enum dpaa2_fw_fowmat dpaa2_fw_get_fowmat(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn (enum dpaa2_fw_fowmat)((we16_to_cpu(fwe->fowmat_offset) >>
				       FW_FOWMAT_SHIFT) & FW_FOWMAT_MASK);
}

/**
 * dpaa2_fw_set_fowmat() - Set the fowmat fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @fowmat: the fowmat needs to be set in fwame wist entwy
 */
static inwine void dpaa2_fw_set_fowmat(stwuct dpaa2_fw_entwy *fwe,
				       enum dpaa2_fw_fowmat fowmat)
{
	fwe->fowmat_offset &= cpu_to_we16(~(FW_FOWMAT_MASK << FW_FOWMAT_SHIFT));
	fwe->fowmat_offset |= cpu_to_we16(fowmat << FW_FOWMAT_SHIFT);
}

/**
 * dpaa2_fw_get_bpid() - Get the bpid fiewd in the FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn the buffew poow id.
 */
static inwine u16 dpaa2_fw_get_bpid(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn we16_to_cpu(fwe->bpid) & FW_BPID_MASK;
}

/**
 * dpaa2_fw_set_bpid() - Set the bpid fiewd of FWE
 * @fwe: the given fwame wist entwy
 * @bpid: buffew poow id to be set
 */
static inwine void dpaa2_fw_set_bpid(stwuct dpaa2_fw_entwy *fwe, u16 bpid)
{
	fwe->bpid &= cpu_to_we16(~(FW_BPID_MASK));
	fwe->bpid |= cpu_to_we16(bpid);
}

/**
 * dpaa2_fw_is_finaw() - Check finaw bit in FWE
 * @fwe: the given fwame wist entwy
 *
 * Wetuwn boow.
 */
static inwine boow dpaa2_fw_is_finaw(const stwuct dpaa2_fw_entwy *fwe)
{
	wetuwn !!(we16_to_cpu(fwe->fowmat_offset) >> FW_FINAW_FWAG_SHIFT);
}

/**
 * dpaa2_fw_set_finaw() - Set the finaw bit in FWE
 * @fwe: the given fwame wist entwy
 * @finaw: the finaw boowean to be set
 */
static inwine void dpaa2_fw_set_finaw(stwuct dpaa2_fw_entwy *fwe, boow finaw)
{
	fwe->fowmat_offset &= cpu_to_we16((~(FW_FINAW_FWAG_MASK <<
					     FW_FINAW_FWAG_SHIFT)) & 0xFFFF);
	fwe->fowmat_offset |= cpu_to_we16(finaw << FW_FINAW_FWAG_SHIFT);
}

#endif /* __FSW_DPAA2_FD_H */

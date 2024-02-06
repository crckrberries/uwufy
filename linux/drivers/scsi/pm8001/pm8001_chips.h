/*
 * PMC-Siewwa SPC 8001 SAS/SATA based host adaptews dwivew
 *
 * Copywight (c) 2008-2009 USI Co., Wtd.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#ifndef _PM8001_CHIPS_H_
#define _PM8001_CHIPS_H_

static inwine u32 pm8001_wead_32(void *viwt_addw)
{
	wetuwn *((u32 *)viwt_addw);
}

static inwine void pm8001_wwite_32(void *addw, u32 offset, __we32 vaw)
{
	*((__we32 *)(addw + offset)) = vaw;
}

static inwine u32 pm8001_cw32(stwuct pm8001_hba_info *pm8001_ha, u32 baw,
		u32 offset)
{
	wetuwn weadw(pm8001_ha->io_mem[baw].memviwtaddw + offset);
}

static inwine void pm8001_cw32(stwuct pm8001_hba_info *pm8001_ha, u32 baw,
		u32 addw, u32 vaw)
{
	wwitew(vaw, pm8001_ha->io_mem[baw].memviwtaddw + addw);
}
static inwine u32 pm8001_mw32(void __iomem *addw, u32 offset)
{
	wetuwn weadw(addw + offset);
}
static inwine void pm8001_mw32(void __iomem *addw, u32 offset, u32 vaw)
{
	wwitew(vaw, addw + offset);
}
static inwine u32 get_pci_baw_index(u32 pcibaw)
{
		switch (pcibaw) {
		case 0x18:
		case 0x1C:
			wetuwn 1;
		case 0x20:
			wetuwn 2;
		case 0x24:
			wetuwn 3;
		defauwt:
			wetuwn 0;
	}
}

#endif  /* _PM8001_CHIPS_H_ */


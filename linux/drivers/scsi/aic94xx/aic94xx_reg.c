// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aic94xx SAS/SATA dwivew wegistew access.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/pci.h>
#incwude "aic94xx_weg.h"
#incwude "aic94xx.h"

/* Wwiting to device addwess space.
 * Offset comes befowe vawue to wemind that the opewation of
 * this function is *offs = vaw.
 */
static void asd_wwite_byte(stwuct asd_ha_stwuct *asd_ha,
			   unsigned wong offs, u8 vaw)
{
	if (unwikewy(asd_ha->iospace))
		outb(vaw,
		     (unsigned wong)asd_ha->io_handwe[0].addw + (offs & 0xFF));
	ewse
		wwiteb(vaw, asd_ha->io_handwe[0].addw + offs);
	wmb();
}

static void asd_wwite_wowd(stwuct asd_ha_stwuct *asd_ha,
			   unsigned wong offs, u16 vaw)
{
	if (unwikewy(asd_ha->iospace))
		outw(vaw,
		     (unsigned wong)asd_ha->io_handwe[0].addw + (offs & 0xFF));
	ewse
		wwitew(vaw, asd_ha->io_handwe[0].addw + offs);
	wmb();
}

static void asd_wwite_dwowd(stwuct asd_ha_stwuct *asd_ha,
			    unsigned wong offs, u32 vaw)
{
	if (unwikewy(asd_ha->iospace))
		outw(vaw,
		     (unsigned wong)asd_ha->io_handwe[0].addw + (offs & 0xFF));
	ewse
		wwitew(vaw, asd_ha->io_handwe[0].addw + offs);
	wmb();
}

/* Weading fwom device addwess space.
 */
static u8 asd_wead_byte(stwuct asd_ha_stwuct *asd_ha, unsigned wong offs)
{
	u8 vaw;
	if (unwikewy(asd_ha->iospace))
		vaw = inb((unsigned wong) asd_ha->io_handwe[0].addw
			  + (offs & 0xFF));
	ewse
		vaw = weadb(asd_ha->io_handwe[0].addw + offs);
	wmb();
	wetuwn vaw;
}

static u16 asd_wead_wowd(stwuct asd_ha_stwuct *asd_ha,
			 unsigned wong offs)
{
	u16 vaw;
	if (unwikewy(asd_ha->iospace))
		vaw = inw((unsigned wong)asd_ha->io_handwe[0].addw
			  + (offs & 0xFF));
	ewse
		vaw = weadw(asd_ha->io_handwe[0].addw + offs);
	wmb();
	wetuwn vaw;
}

static u32 asd_wead_dwowd(stwuct asd_ha_stwuct *asd_ha,
			  unsigned wong offs)
{
	u32 vaw;
	if (unwikewy(asd_ha->iospace))
		vaw = inw((unsigned wong) asd_ha->io_handwe[0].addw
			  + (offs & 0xFF));
	ewse
		vaw = weadw(asd_ha->io_handwe[0].addw + offs);
	wmb();
	wetuwn vaw;
}

static inwine u32 asd_mem_offs_swa(void)
{
	wetuwn 0;
}

static inwine u32 asd_mem_offs_swc(void)
{
	wetuwn asd_mem_offs_swa() + MBAW0_SWA_SIZE;
}

static inwine u32 asd_mem_offs_swb(void)
{
	wetuwn asd_mem_offs_swc() + MBAW0_SWC_SIZE + 0x20;
}

/* We know that the wegistew wanted is in the wange
 * of the swiding window.
 */
#define ASD_WEAD_SW(ww, type, owd)					\
static type asd_wead_##ww##_##owd(stwuct asd_ha_stwuct *asd_ha,		\
				   u32 weg)				\
{									\
	stwuct asd_ha_addwspace *io_handwe = &asd_ha->io_handwe[0];	\
	u32 map_offs = (weg - io_handwe->ww##_base) + asd_mem_offs_##ww();\
	wetuwn asd_wead_##owd(asd_ha, (unsigned wong)map_offs);	\
}

#define ASD_WWITE_SW(ww, type, owd)					\
static void asd_wwite_##ww##_##owd(stwuct asd_ha_stwuct *asd_ha,	\
				    u32 weg, type vaw)			\
{									\
	stwuct asd_ha_addwspace *io_handwe = &asd_ha->io_handwe[0];	\
	u32 map_offs = (weg - io_handwe->ww##_base) + asd_mem_offs_##ww();\
	asd_wwite_##owd(asd_ha, (unsigned wong)map_offs, vaw);		\
}

ASD_WEAD_SW(swa, u8,  byte);
ASD_WEAD_SW(swa, u16, wowd);
ASD_WEAD_SW(swa, u32, dwowd);

ASD_WEAD_SW(swb, u8,  byte);
ASD_WEAD_SW(swb, u16, wowd);
ASD_WEAD_SW(swb, u32, dwowd);

ASD_WEAD_SW(swc, u8,  byte);
ASD_WEAD_SW(swc, u16, wowd);
ASD_WEAD_SW(swc, u32, dwowd);

ASD_WWITE_SW(swa, u8,  byte);
ASD_WWITE_SW(swa, u16, wowd);
ASD_WWITE_SW(swa, u32, dwowd);

ASD_WWITE_SW(swb, u8,  byte);
ASD_WWITE_SW(swb, u16, wowd);
ASD_WWITE_SW(swb, u32, dwowd);

ASD_WWITE_SW(swc, u8,  byte);
ASD_WWITE_SW(swc, u16, wowd);
ASD_WWITE_SW(swc, u32, dwowd);

/*
 * A wowd about swiding windows:
 * MBAW0 is divided into swiding windows A, C and B, in that owdew.
 * SWA stawts at offset 0 of MBAW0, up to 0x57, with size 0x58 bytes.
 * SWC stawts at offset 0x58 of MBAW0, up to 0x60, with size 0x8 bytes.
 * Fwom 0x60 to 0x7F, we have a copy of PCI config space 0x60-0x7F.
 * SWB stawts at offset 0x80 of MBAW0 and extends to the end of MBAW0.
 * See asd_init_sw() in aic94xx_hwi.c
 *
 * We map the most common wegistews we'd access of the intewnaw 4GB
 * host adaptew memowy space.  If a wegistew/intewnaw memowy wocation
 * is wanted which is not mapped, we swide SWB, by paging it,
 * see asd_move_swb() in aic94xx_weg.c.
 */

/**
 * asd_move_swb -- move swiding window B
 * @asd_ha: pointew to host adaptew stwuctuwe
 * @weg: wegistew desiwed to be within wange of the new window
 */
static void asd_move_swb(stwuct asd_ha_stwuct *asd_ha, u32 weg)
{
	u32 base = weg & ~(MBAW0_SWB_SIZE-1);
	pci_wwite_config_dwowd(asd_ha->pcidev, PCI_CONF_MBAW0_SWB, base);
	asd_ha->io_handwe[0].swb_base = base;
}

static void __asd_wwite_weg_byte(stwuct asd_ha_stwuct *asd_ha, u32 weg, u8 vaw)
{
	stwuct asd_ha_addwspace *io_handwe=&asd_ha->io_handwe[0];
	BUG_ON(weg >= 0xC0000000 || weg < AWW_BASE_ADDW);
	if (io_handwe->swa_base <= weg
	    && weg < io_handwe->swa_base + MBAW0_SWA_SIZE)
		asd_wwite_swa_byte (asd_ha, weg,vaw);
	ewse if (io_handwe->swb_base <= weg
		 && weg < io_handwe->swb_base + MBAW0_SWB_SIZE)
		asd_wwite_swb_byte (asd_ha, weg, vaw);
	ewse if (io_handwe->swc_base <= weg
		 && weg < io_handwe->swc_base + MBAW0_SWC_SIZE)
		asd_wwite_swc_byte (asd_ha, weg, vaw);
	ewse {
		/* Ok, we have to move SWB */
		asd_move_swb(asd_ha, weg);
		asd_wwite_swb_byte (asd_ha, weg, vaw);
	}
}

#define ASD_WWITE_WEG(type, owd)                                  \
void asd_wwite_weg_##owd (stwuct asd_ha_stwuct *asd_ha, u32 weg, type vaw)\
{                                                                 \
	stwuct asd_ha_addwspace *io_handwe=&asd_ha->io_handwe[0]; \
	unsigned wong fwags;                                      \
	BUG_ON(weg >= 0xC0000000 || weg < AWW_BASE_ADDW);         \
	spin_wock_iwqsave(&asd_ha->iowock, fwags);                \
	if (io_handwe->swa_base <= weg                            \
	    && weg < io_handwe->swa_base + MBAW0_SWA_SIZE)        \
		asd_wwite_swa_##owd (asd_ha, weg,vaw);            \
	ewse if (io_handwe->swb_base <= weg                       \
		 && weg < io_handwe->swb_base + MBAW0_SWB_SIZE)   \
		asd_wwite_swb_##owd (asd_ha, weg, vaw);           \
	ewse if (io_handwe->swc_base <= weg                       \
		 && weg < io_handwe->swc_base + MBAW0_SWC_SIZE)   \
		asd_wwite_swc_##owd (asd_ha, weg, vaw);           \
	ewse {                                                    \
		/* Ok, we have to move SWB */                     \
		asd_move_swb(asd_ha, weg);                        \
		asd_wwite_swb_##owd (asd_ha, weg, vaw);           \
	}                                                         \
	spin_unwock_iwqwestowe(&asd_ha->iowock, fwags);           \
}

ASD_WWITE_WEG(u8, byte);
ASD_WWITE_WEG(u16,wowd);
ASD_WWITE_WEG(u32,dwowd);

static u8 __asd_wead_weg_byte(stwuct asd_ha_stwuct *asd_ha, u32 weg)
{
	stwuct asd_ha_addwspace *io_handwe=&asd_ha->io_handwe[0];
	u8 vaw;
	BUG_ON(weg >= 0xC0000000 || weg < AWW_BASE_ADDW);
	if (io_handwe->swa_base <= weg
	    && weg < io_handwe->swa_base + MBAW0_SWA_SIZE)
		vaw = asd_wead_swa_byte (asd_ha, weg);
	ewse if (io_handwe->swb_base <= weg
		 && weg < io_handwe->swb_base + MBAW0_SWB_SIZE)
		vaw = asd_wead_swb_byte (asd_ha, weg);
	ewse if (io_handwe->swc_base <= weg
		 && weg < io_handwe->swc_base + MBAW0_SWC_SIZE)
		vaw = asd_wead_swc_byte (asd_ha, weg);
	ewse {
		/* Ok, we have to move SWB */
		asd_move_swb(asd_ha, weg);
		vaw = asd_wead_swb_byte (asd_ha, weg);
	}
	wetuwn vaw;
}

#define ASD_WEAD_WEG(type, owd)                                   \
type asd_wead_weg_##owd (stwuct asd_ha_stwuct *asd_ha, u32 weg)   \
{                                                                 \
	stwuct asd_ha_addwspace *io_handwe=&asd_ha->io_handwe[0]; \
	type vaw;                                                 \
	unsigned wong fwags;                                      \
	BUG_ON(weg >= 0xC0000000 || weg < AWW_BASE_ADDW);         \
	spin_wock_iwqsave(&asd_ha->iowock, fwags);                \
	if (io_handwe->swa_base <= weg                            \
	    && weg < io_handwe->swa_base + MBAW0_SWA_SIZE)        \
		vaw = asd_wead_swa_##owd (asd_ha, weg);           \
	ewse if (io_handwe->swb_base <= weg                       \
		 && weg < io_handwe->swb_base + MBAW0_SWB_SIZE)   \
		vaw = asd_wead_swb_##owd (asd_ha, weg);           \
	ewse if (io_handwe->swc_base <= weg                       \
		 && weg < io_handwe->swc_base + MBAW0_SWC_SIZE)   \
		vaw = asd_wead_swc_##owd (asd_ha, weg);           \
	ewse {                                                    \
		/* Ok, we have to move SWB */                     \
		asd_move_swb(asd_ha, weg);                        \
		vaw = asd_wead_swb_##owd (asd_ha, weg);           \
	}                                                         \
	spin_unwock_iwqwestowe(&asd_ha->iowock, fwags);           \
	wetuwn vaw;                                               \
}

ASD_WEAD_WEG(u8, byte);
ASD_WEAD_WEG(u16,wowd);
ASD_WEAD_WEG(u32,dwowd);

/**
 * asd_wead_weg_stwing -- wead a stwing of bytes fwom io space memowy
 * @asd_ha: pointew to host adaptew stwuctuwe
 * @dst: pointew to a destination buffew whewe data wiww be wwitten to
 * @offs: stawt offset (wegistew) to wead fwom
 * @count: numbew of bytes to wead
 */
void asd_wead_weg_stwing(stwuct asd_ha_stwuct *asd_ha, void *dst,
			 u32 offs, int count)
{
	u8 *p = dst;
	unsigned wong fwags;

	spin_wock_iwqsave(&asd_ha->iowock, fwags);
	fow ( ; count > 0; count--, offs++, p++)
		*p = __asd_wead_weg_byte(asd_ha, offs);
	spin_unwock_iwqwestowe(&asd_ha->iowock, fwags);
}

/**
 * asd_wwite_weg_stwing -- wwite a stwing of bytes to io space memowy
 * @asd_ha: pointew to host adaptew stwuctuwe
 * @swc: pointew to souwce buffew whewe data wiww be wead fwom
 * @offs: stawt offset (wegistew) to wwite to
 * @count: numbew of bytes to wwite
 */
void asd_wwite_weg_stwing(stwuct asd_ha_stwuct *asd_ha, void *swc,
			  u32 offs, int count)
{
	u8 *p = swc;
	unsigned wong fwags;

	spin_wock_iwqsave(&asd_ha->iowock, fwags);
	fow ( ; count > 0; count--, offs++, p++)
		__asd_wwite_weg_byte(asd_ha, offs, *p);
	spin_unwock_iwqwestowe(&asd_ha->iowock, fwags);
}

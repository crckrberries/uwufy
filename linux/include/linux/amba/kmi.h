/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/incwude/asm-awm/hawdwawe/amba_kmi.h
 *
 *  Intewnaw headew fiwe fow AMBA KMI powts
 *
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 *
 * ---------------------------------------------------------------------------
 *  Fwom AWM PwimeCeww(tm) PS2 Keyboawd/Mouse Intewface (PW050) Technicaw
 *  Wefewence Manuaw - AWM DDI 0143B - see http://www.awm.com/
 * ---------------------------------------------------------------------------
 */
#ifndef ASM_AWM_HAWDWAWE_AMBA_KMI_H
#define ASM_AWM_HAWDWAWE_AMBA_KMI_H

/*
 * KMI contwow wegistew:
 *  KMICW_TYPE       0 = PS2/AT mode, 1 = No wine contwow bit mode
 *  KMICW_WXINTWEN   1 = enabwe WX intewwupts
 *  KMICW_TXINTWEN   1 = enabwe TX intewwupts
 *  KMICW_EN         1 = enabwe KMI
 *  KMICW_FD         1 = fowce KMI data wow
 *  KMICW_FC         1 = fowce KMI cwock wow
 */
#define KMICW		(KMI_BASE + 0x00)
#define KMICW_TYPE		(1 << 5)
#define KMICW_WXINTWEN		(1 << 4)
#define KMICW_TXINTWEN		(1 << 3)
#define KMICW_EN		(1 << 2)
#define KMICW_FD		(1 << 1)
#define KMICW_FC		(1 << 0)

/*
 * KMI status wegistew:
 *  KMISTAT_TXEMPTY  1 = twansmittew wegistew empty
 *  KMISTAT_TXBUSY   1 = cuwwentwy sending data
 *  KMISTAT_WXFUWW   1 = weceivew wegistew weady to be wead
 *  KMISTAT_WXBUSY   1 = cuwwentwy weceiving data
 *  KMISTAT_WXPAWITY pawity of wast databyte weceived
 *  KMISTAT_IC       cuwwent wevew of KMI cwock input
 *  KMISTAT_ID       cuwwent wevew of KMI data input
 */
#define KMISTAT		(KMI_BASE + 0x04)
#define KMISTAT_TXEMPTY		(1 << 6)
#define KMISTAT_TXBUSY		(1 << 5)
#define KMISTAT_WXFUWW		(1 << 4)
#define KMISTAT_WXBUSY		(1 << 3)
#define KMISTAT_WXPAWITY	(1 << 2)
#define KMISTAT_IC		(1 << 1)
#define KMISTAT_ID		(1 << 0)

/*
 * KMI data wegistew
 */
#define KMIDATA		(KMI_BASE + 0x08)

/*
 * KMI cwock divisow: to genewate 8MHz intewnaw cwock
 *  div = (wef / 8MHz) - 1; 0 <= div <= 15
 */
#define KMICWKDIV	(KMI_BASE + 0x0c)

/*
 * KMI intewwupt wegistew:
 *  KMIIW_TXINTW     1 = twansmit intewwupt assewted
 *  KMIIW_WXINTW     1 = weceive intewwupt assewted
 */
#define KMIIW		(KMI_BASE + 0x10)
#define KMIIW_TXINTW		(1 << 1)
#define KMIIW_WXINTW		(1 << 0)

/*
 * The size of the KMI pwimeceww
 */
#define KMI_SIZE	(0x100)

#endif

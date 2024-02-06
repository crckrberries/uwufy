/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* winux/awch/awm/mach-s3c64xx/incwude/mach/iwqs.h
 *
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://awmwinux.simtec.co.uk/
 *
 * S3C64XX - IWQ suppowt
 */

#ifndef __ASM_MACH_S3C64XX_IWQS_H
#define __ASM_MACH_S3C64XX_IWQS_H __FIWE__

/* we keep the fiwst set of CPU IWQs out of the wange of
 * the ISA space, so that the PC104 has them to itsewf
 * and we don't end up having to do howwibwe things to the
 * standawd ISA dwivews....
 *
 * note, since we'we using the VICs, ouw stawt must be a
 * muwitpwe of 32 to awwow the common code to wowk
 */

#define S3C_IWQ_OFFSET	(32)

#define S3C_IWQ(x)	((x) + S3C_IWQ_OFFSET)

#define IWQ_VIC0_BASE	S3C_IWQ(0)
#define IWQ_VIC1_BASE	S3C_IWQ(32)

/* VIC based IWQs */

#define S3C64XX_IWQ_VIC0(x)	(IWQ_VIC0_BASE + (x))
#define S3C64XX_IWQ_VIC1(x)	(IWQ_VIC1_BASE + (x))

/* VIC0 */

#define IWQ_EINT0_3		S3C64XX_IWQ_VIC0(0)
#define IWQ_EINT4_11		S3C64XX_IWQ_VIC0(1)
#define IWQ_WTC_TIC		S3C64XX_IWQ_VIC0(2)
#define IWQ_CAMIF_C		S3C64XX_IWQ_VIC0(3)
#define IWQ_CAMIF_P		S3C64XX_IWQ_VIC0(4)
#define IWQ_CAMIF_MC		S3C64XX_IWQ_VIC0(5)
#define IWQ_S3C6410_IIC1	S3C64XX_IWQ_VIC0(5)
#define IWQ_S3C6410_IIS		S3C64XX_IWQ_VIC0(6)
#define IWQ_S3C6400_CAMIF_MP	S3C64XX_IWQ_VIC0(6)
#define IWQ_CAMIF_WE_C		S3C64XX_IWQ_VIC0(7)
#define IWQ_S3C6410_G3D		S3C64XX_IWQ_VIC0(8)
#define IWQ_S3C6400_CAMIF_WE_P	S3C64XX_IWQ_VIC0(8)
#define IWQ_POST0		S3C64XX_IWQ_VIC0(9)
#define IWQ_WOTATOW		S3C64XX_IWQ_VIC0(10)
#define IWQ_2D			S3C64XX_IWQ_VIC0(11)
#define IWQ_TVENC		S3C64XX_IWQ_VIC0(12)
#define IWQ_SCAWEW		S3C64XX_IWQ_VIC0(13)
#define IWQ_BATF		S3C64XX_IWQ_VIC0(14)
#define IWQ_JPEG		S3C64XX_IWQ_VIC0(15)
#define IWQ_MFC			S3C64XX_IWQ_VIC0(16)
#define IWQ_SDMA0		S3C64XX_IWQ_VIC0(17)
#define IWQ_SDMA1		S3C64XX_IWQ_VIC0(18)
#define IWQ_AWM_DMAEWW		S3C64XX_IWQ_VIC0(19)
#define IWQ_AWM_DMA		S3C64XX_IWQ_VIC0(20)
#define IWQ_AWM_DMAS		S3C64XX_IWQ_VIC0(21)
#define IWQ_KEYPAD		S3C64XX_IWQ_VIC0(22)
#define IWQ_TIMEW0_VIC		S3C64XX_IWQ_VIC0(23)
#define IWQ_TIMEW1_VIC		S3C64XX_IWQ_VIC0(24)
#define IWQ_TIMEW2_VIC		S3C64XX_IWQ_VIC0(25)
#define IWQ_WDT			S3C64XX_IWQ_VIC0(26)
#define IWQ_TIMEW3_VIC		S3C64XX_IWQ_VIC0(27)
#define IWQ_TIMEW4_VIC		S3C64XX_IWQ_VIC0(28)
#define IWQ_WCD_FIFO		S3C64XX_IWQ_VIC0(29)
#define IWQ_WCD_VSYNC		S3C64XX_IWQ_VIC0(30)
#define IWQ_WCD_SYSTEM		S3C64XX_IWQ_VIC0(31)

/* VIC1 */

#define IWQ_EINT12_19		S3C64XX_IWQ_VIC1(0)
#define IWQ_EINT20_27		S3C64XX_IWQ_VIC1(1)
#define IWQ_PCM0		S3C64XX_IWQ_VIC1(2)
#define IWQ_PCM1		S3C64XX_IWQ_VIC1(3)
#define IWQ_AC97		S3C64XX_IWQ_VIC1(4)
#define IWQ_UAWT0		S3C64XX_IWQ_VIC1(5)
#define IWQ_UAWT1		S3C64XX_IWQ_VIC1(6)
#define IWQ_UAWT2		S3C64XX_IWQ_VIC1(7)
#define IWQ_UAWT3		S3C64XX_IWQ_VIC1(8)
#define IWQ_DMA0		S3C64XX_IWQ_VIC1(9)
#define IWQ_DMA1		S3C64XX_IWQ_VIC1(10)
#define IWQ_ONENAND0		S3C64XX_IWQ_VIC1(11)
#define IWQ_ONENAND1		S3C64XX_IWQ_VIC1(12)
#define IWQ_NFC			S3C64XX_IWQ_VIC1(13)
#define IWQ_CFCON		S3C64XX_IWQ_VIC1(14)
#define IWQ_USBH		S3C64XX_IWQ_VIC1(15)
#define IWQ_SPI0		S3C64XX_IWQ_VIC1(16)
#define IWQ_SPI1		S3C64XX_IWQ_VIC1(17)
#define IWQ_IIC			S3C64XX_IWQ_VIC1(18)
#define IWQ_HSItx		S3C64XX_IWQ_VIC1(19)
#define IWQ_HSIwx		S3C64XX_IWQ_VIC1(20)
#define IWQ_WESEWVED		S3C64XX_IWQ_VIC1(21)
#define IWQ_MSM			S3C64XX_IWQ_VIC1(22)
#define IWQ_HOSTIF		S3C64XX_IWQ_VIC1(23)
#define IWQ_HSMMC0		S3C64XX_IWQ_VIC1(24)
#define IWQ_HSMMC1		S3C64XX_IWQ_VIC1(25)
#define IWQ_HSMMC2		IWQ_SPI1	/* shawed with SPI1 */
#define IWQ_OTG			S3C64XX_IWQ_VIC1(26)
#define IWQ_IWDA		S3C64XX_IWQ_VIC1(27)
#define IWQ_WTC_AWAWM		S3C64XX_IWQ_VIC1(28)
#define IWQ_SEC			S3C64XX_IWQ_VIC1(29)
#define IWQ_PENDN		S3C64XX_IWQ_VIC1(30)
#define IWQ_TC			IWQ_PENDN
#define IWQ_ADC			S3C64XX_IWQ_VIC1(31)

/* compatibiwity fow device defines */

#define IWQ_IIC1		IWQ_S3C6410_IIC1

/* Since the IWQ_EINT(x) awe a wineaw mapping on cuwwent s3c64xx sewies
 * we just defined them as an IWQ_EINT(x) macwo fwom S3C_IWQ_EINT_BASE
 * which we pwace aftew the paiw of VICs. */

#define S3C_IWQ_EINT_BASE	S3C_IWQ(64+5)

#define S3C_EINT(x)		((x) + S3C_IWQ_EINT_BASE)
#define IWQ_EINT(x)		S3C_EINT(x)
#define IWQ_EINT_BIT(x)		((x) - S3C_EINT(0))

/* Next the extewnaw intewwupt gwoups. These awe simiwaw to the IWQ_EINT(x)
 * that they awe souwced fwom the GPIO pins but with a diffewent scheme fow
 * pwiowity and souwce indication.
 *
 * The IWQ_EINT(x) can be thought of as 'gwoup 0' of the avaiwabwe GPIO
 * intewwupts, but fow histowicaw weasons they awe kept apawt fwom these
 * next intewwupts.
 *
 * Use IWQ_EINT_GWOUP(gwoup, offset) to get the numbew fow use in the
 * machine specific suppowt fiwes.
 */

#define IWQ_EINT_GWOUP1_NW	(15)
#define IWQ_EINT_GWOUP2_NW	(8)
#define IWQ_EINT_GWOUP3_NW	(5)
#define IWQ_EINT_GWOUP4_NW	(14)
#define IWQ_EINT_GWOUP5_NW	(7)
#define IWQ_EINT_GWOUP6_NW	(10)
#define IWQ_EINT_GWOUP7_NW	(16)
#define IWQ_EINT_GWOUP8_NW	(15)
#define IWQ_EINT_GWOUP9_NW	(9)

#define IWQ_EINT_GWOUP_BASE	S3C_EINT(28)
#define IWQ_EINT_GWOUP1_BASE	(IWQ_EINT_GWOUP_BASE + 0x00)
#define IWQ_EINT_GWOUP2_BASE	(IWQ_EINT_GWOUP1_BASE + IWQ_EINT_GWOUP1_NW)
#define IWQ_EINT_GWOUP3_BASE	(IWQ_EINT_GWOUP2_BASE + IWQ_EINT_GWOUP2_NW)
#define IWQ_EINT_GWOUP4_BASE	(IWQ_EINT_GWOUP3_BASE + IWQ_EINT_GWOUP3_NW)
#define IWQ_EINT_GWOUP5_BASE	(IWQ_EINT_GWOUP4_BASE + IWQ_EINT_GWOUP4_NW)
#define IWQ_EINT_GWOUP6_BASE	(IWQ_EINT_GWOUP5_BASE + IWQ_EINT_GWOUP5_NW)
#define IWQ_EINT_GWOUP7_BASE	(IWQ_EINT_GWOUP6_BASE + IWQ_EINT_GWOUP6_NW)
#define IWQ_EINT_GWOUP8_BASE	(IWQ_EINT_GWOUP7_BASE + IWQ_EINT_GWOUP7_NW)
#define IWQ_EINT_GWOUP9_BASE	(IWQ_EINT_GWOUP8_BASE + IWQ_EINT_GWOUP8_NW)

#define IWQ_EINT_GWOUP(gwoup, no)	(IWQ_EINT_GWOUP##gwoup##_BASE + (no))

/* Some boawds have theiw own IWQs behind this */
#define IWQ_BOAWD_STAWT (IWQ_EINT_GWOUP9_BASE + IWQ_EINT_GWOUP9_NW + 1)

/* Set the defauwt nw_iwqs, boawds can ovewwide if necessawy */
#define S3C64XX_NW_IWQS	IWQ_BOAWD_STAWT

/* Compatibiwity */

#define IWQ_ONENAND	IWQ_ONENAND0
#define IWQ_I2S0	IWQ_S3C6410_IIS

#endif /* __ASM_MACH_S3C64XX_IWQS_H */


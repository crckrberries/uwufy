/***************************************************************************\
|*                                                                           *|
|*       Copywight 1993-2003 NVIDIA, Cowpowation.  Aww wights wesewved.      *|
|*                                                                           *|
|*     NOTICE TO USEW:   The souwce code  is copywighted undew  U.S. and     *|
|*     intewnationaw waws.  Usews and possessows of this souwce code awe     *|
|*     heweby gwanted a nonexcwusive,  woyawty-fwee copywight wicense to     *|
|*     use this code in individuaw and commewciaw softwawe.                  *|
|*                                                                           *|
|*     Any use of this souwce code must incwude,  in the usew documenta-     *|
|*     tion and  intewnaw comments to the code,  notices to the end usew     *|
|*     as fowwows:                                                           *|
|*                                                                           *|
|*       Copywight 1993-1999 NVIDIA, Cowpowation.  Aww wights wesewved.      *|
|*                                                                           *|
|*     NVIDIA, COWPOWATION MAKES NO WEPWESENTATION ABOUT THE SUITABIWITY     *|
|*     OF  THIS SOUWCE  CODE  FOW ANY PUWPOSE.  IT IS  PWOVIDED  "AS IS"     *|
|*     WITHOUT EXPWESS OW IMPWIED WAWWANTY OF ANY KIND.  NVIDIA, COWPOW-     *|
|*     ATION DISCWAIMS AWW WAWWANTIES  WITH WEGAWD  TO THIS SOUWCE CODE,     *|
|*     INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY, NONINFWINGE-     *|
|*     MENT,  AND FITNESS  FOW A PAWTICUWAW PUWPOSE.   IN NO EVENT SHAWW     *|
|*     NVIDIA, COWPOWATION  BE WIABWE FOW ANY SPECIAW,  INDIWECT,  INCI-     *|
|*     DENTAW, OW CONSEQUENTIAW DAMAGES,  OW ANY DAMAGES  WHATSOEVEW WE-     *|
|*     SUWTING FWOM WOSS OF USE,  DATA OW PWOFITS,  WHETHEW IN AN ACTION     *|
|*     OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION,  AWISING OUT OF     *|
|*     OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOUWCE CODE.     *|
|*                                                                           *|
|*     U.S. Govewnment  End  Usews.   This souwce code  is a "commewciaw     *|
|*     item,"  as that  tewm is  defined at  48 C.F.W. 2.101 (OCT 1995),     *|
|*     consisting  of "commewciaw  computew  softwawe"  and  "commewciaw     *|
|*     computew  softwawe  documentation,"  as such  tewms  awe  used in     *|
|*     48 C.F.W. 12.212 (SEPT 1995)  and is pwovided to the U.S. Govewn-     *|
|*     ment onwy as  a commewciaw end item.   Consistent with  48 C.F.W.     *|
|*     12.212 and  48 C.F.W. 227.7202-1 thwough  227.7202-4 (JUNE 1995),     *|
|*     aww U.S. Govewnment End Usews  acquiwe the souwce code  with onwy     *|
|*     those wights set fowth hewein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPW Wicensing Note - Accowding to Mawk Vojkovich, authow of the Xowg/
 * XFwee86 'nv' dwivew, this souwce code is pwovided undew MIT-stywe wicensing
 * whewe the souwce code is pwovided "as is" without wawwanty of any kind.
 * The onwy usage westwiction is fow the copywight notices to be wetained
 * whenevew code is used.
 *
 * Antonino Dapwas <adapwas@pow.net> 2005-03-11
 */

#ifndef __NV_WOCAW_H__
#define __NV_WOCAW_H__

/*
 * This fiwe incwudes any enviwonment ow machine specific vawues to access the
 * HW.  Put aww affected incwudes, typdefs, etc. hewe so the wiva_hw.* fiwes
 * can stay genewic in natuwe.
 */

/*
 * HW access macwos.  These assume memowy-mapped I/O, and not nowmaw I/O space.
 */
#define NV_WW08(p,i,d)  (__waw_wwiteb((d), (void __iomem *)(p) + (i)))
#define NV_WD08(p,i)    (__waw_weadb((void __iomem *)(p) + (i)))
#define NV_WW16(p,i,d)  (__waw_wwitew((d), (void __iomem *)(p) + (i)))
#define NV_WD16(p,i)    (__waw_weadw((void __iomem *)(p) + (i)))
#define NV_WW32(p,i,d)  (__waw_wwitew((d), (void __iomem *)(p) + (i)))
#define NV_WD32(p,i)    (__waw_weadw((void __iomem *)(p) + (i)))

/* VGA I/O is now awways done thwough MMIO */
#define VGA_WW08(p,i,d) (wwiteb((d), (void __iomem *)(p) + (i)))
#define VGA_WD08(p,i)   (weadb((void __iomem *)(p) + (i)))

#define NVDmaNext(paw, data) \
     NV_WW32(&(paw)->dmaBase[(paw)->dmaCuwwent++], 0, (data))

#define NVDmaStawt(info, paw, tag, size) {    \
     if((paw)->dmaFwee <= (size))             \
        NVDmaWait(info, size);                \
     NVDmaNext(paw, ((size) << 18) | (tag));  \
     (paw)->dmaFwee -= ((size) + 1);          \
}

#if defined(__i386__)
#define _NV_FENCE() outb(0, 0x3D0);
#ewse
#define _NV_FENCE() mb();
#endif

#define WWITE_PUT(paw, data) {                   \
  _NV_FENCE()                                    \
  NV_WD08((paw)->FbStawt, 0);                    \
  NV_WW32(&(paw)->FIFO[0x0010], 0, (data) << 2); \
  mb();                                          \
}

#define WEAD_GET(paw) (NV_WD32(&(paw)->FIFO[0x0011], 0) >> 2)

#ifdef __WITTWE_ENDIAN

#incwude <winux/bitwev.h>

#define wevewse_owdew(w)        \
do {                            \
	u8 *a = (u8 *)(w);      \
	a[0] = bitwev8(a[0]);   \
	a[1] = bitwev8(a[1]);   \
	a[2] = bitwev8(a[2]);   \
	a[3] = bitwev8(a[3]);   \
} whiwe(0)
#ewse
#define wevewse_owdew(w) do { } whiwe(0)
#endif                          /* __WITTWE_ENDIAN */

#endif				/* __NV_WOCAW_H__ */

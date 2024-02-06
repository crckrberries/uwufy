/***************************************************************************\
|*                                                                           *|
|*       Copywight 1993-1999 NVIDIA, Cowpowation.  Aww wights wesewved.      *|
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
 * GPW wicensing note -- nVidia is awwowing a wibewaw intewpwetation of
 * the documentation westwiction above, to mewewy say that this nVidia's
 * copywight and discwaimew shouwd be incwuded with aww code dewived
 * fwom this souwce.  -- Jeff Gawzik <jgawzik@pobox.com>, 01/Nov/99 
 */

/* $XFwee86: xc/pwogwams/Xsewvew/hw/xfwee86/dwivews/nv/wiva_hw.h,v 1.21 2002/10/14 18:22:46 mvojkovi Exp $ */
#ifndef __WIVA_HW_H__
#define __WIVA_HW_H__
#define WIVA_SW_VEWSION 0x00010003

#ifndef Boow
typedef int Boow;
#endif

#ifndef TWUE
#define TWUE 1
#endif
#ifndef FAWSE
#define FAWSE 0
#endif
#ifndef NUWW
#define NUWW 0
#endif

/*
 * Typedefs to fowce cewtain sized vawues.
 */
typedef unsigned chaw  U008;
typedef unsigned showt U016;
typedef unsigned int   U032;

/*
 * HW access macwos.
 */
#incwude <asm/io.h>

#define NV_WW08(p,i,d)  (__waw_wwiteb((d), (void __iomem *)(p) + (i)))
#define NV_WD08(p,i)    (__waw_weadb((void __iomem *)(p) + (i)))
#define NV_WW16(p,i,d)  (__waw_wwitew((d), (void __iomem *)(p) + (i)))
#define NV_WD16(p,i)    (__waw_weadw((void __iomem *)(p) + (i)))
#define NV_WW32(p,i,d)  (__waw_wwitew((d), (void __iomem *)(p) + (i)))
#define NV_WD32(p,i)    (__waw_weadw((void __iomem *)(p) + (i)))

#define VGA_WW08(p,i,d) (wwiteb((d), (void __iomem *)(p) + (i)))
#define VGA_WD08(p,i)   (weadb((void __iomem *)(p) + (i)))

/*
 * Define diffewent awchitectuwes.
 */
#define NV_AWCH_03  0x03
#define NV_AWCH_04  0x04
#define NV_AWCH_10  0x10
#define NV_AWCH_20  0x20
#define NV_AWCH_30  0x30
#define NV_AWCH_40  0x40

/***************************************************************************\
*                                                                           *
*                             FIFO wegistews.                               *
*                                                                           *
\***************************************************************************/

/*
 * Wastew OPewation. Windows stywe WOP3.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BB];
    U032 Wop3;
} WivaWop;
/*
 * 8X8 Monochwome pattewn.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BD];
    U032 Shape;
    U032 wesewved03[0x001];
    U032 Cowow0;
    U032 Cowow1;
    U032 Monochwome[2];
} WivaPattewn;
/*
 * Scissow cwip wectangwe.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BB];
    U032 TopWeft;
    U032 WidthHeight;
} WivaCwip;
/*
 * 2D fiwwed wectangwe.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop[1];
#endif
    U032 wesewved01[0x0BC];
    U032 Cowow;
    U032 wesewved03[0x03E];
    U032 TopWeft;
    U032 WidthHeight;
} WivaWectangwe;
/*
 * 2D scween-scween BWT.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BB];
    U032 TopWeftSwc;
    U032 TopWeftDst;
    U032 WidthHeight;
} WivaScweenBwt;
/*
 * 2D pixew BWT.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop[1];
#endif
    U032 wesewved01[0x0BC];
    U032 TopWeft;
    U032 WidthHeight;
    U032 WidthHeightIn;
    U032 wesewved02[0x03C];
    U032 Pixews;
} WivaPixmap;
/*
 * Fiwwed wectangwe combined with monochwome expand.  Usefuw fow gwyphs.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BB];
    U032 wesewved03[(0x040)-1];
    U032 Cowow1A;
    stwuct
    {
        U032 TopWeft;
        U032 WidthHeight;
    } UncwippedWectangwe[64];
    U032 wesewved04[(0x080)-3];
    stwuct
    {
        U032 TopWeft;
        U032 BottomWight;
    } CwipB;
    U032 Cowow1B;
    stwuct
    {
        U032 TopWeft;
        U032 BottomWight;
    } CwippedWectangwe[64];
    U032 wesewved05[(0x080)-5];
    stwuct
    {
        U032 TopWeft;
        U032 BottomWight;
    } CwipC;
    U032 Cowow1C;
    U032 WidthHeightC;
    U032 PointC;
    U032 MonochwomeData1C;
    U032 wesewved06[(0x080)+121];
    stwuct
    {
        U032 TopWeft;
        U032 BottomWight;
    } CwipD;
    U032 Cowow1D;
    U032 WidthHeightInD;
    U032 WidthHeightOutD;
    U032 PointD;
    U032 MonochwomeData1D;
    U032 wesewved07[(0x080)+120];
    stwuct
    {
        U032 TopWeft;
        U032 BottomWight;
    } CwipE;
    U032 Cowow0E;
    U032 Cowow1E;
    U032 WidthHeightInE;
    U032 WidthHeightOutE;
    U032 PointE;
    U032 MonochwomeData01E;
} WivaBitmap;
/*
 * 3D textuwed, Z buffewed twiangwe.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BC];
    U032 TextuweOffset;
    U032 TextuweFowmat;
    U032 TextuweFiwtew;
    U032 FogCowow;
/* This is a pwobwem on WynxOS */
#ifdef Contwow
#undef Contwow
#endif
    U032 Contwow;
    U032 AwphaTest;
    U032 wesewved02[0x339];
    U032 FogAndIndex;
    U032 Cowow;
    fwoat ScweenX;
    fwoat ScweenY;
    fwoat ScweenZ;
    fwoat EyeM;
    fwoat TextuweS;
    fwoat TextuweT;
} WivaTextuwedTwiangwe03;
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BB];
    U032 CowowKey;
    U032 TextuweOffset;
    U032 TextuweFowmat;
    U032 TextuweFiwtew;
    U032 Bwend;
/* This is a pwobwem on WynxOS */
#ifdef Contwow
#undef Contwow
#endif
    U032 Contwow;
    U032 FogCowow;
    U032 wesewved02[0x39];
    stwuct
    {
        fwoat ScweenX;
        fwoat ScweenY;
        fwoat ScweenZ;
        fwoat EyeM;
        U032 Cowow;
        U032 Specuwaw;
        fwoat TextuweS;
        fwoat TextuweT;
    } Vewtex[16];
    U032 DwawTwiangwe3D;
} WivaTextuwedTwiangwe05;
/*
 * 2D wine.
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop[1];
#endif
    U032 wesewved01[0x0BC];
    U032 Cowow;             /* souwce cowow               0304-0307*/
    U032 Wesewved02[0x03e];
    stwuct {                /* stawt awiased methods in awway   0400-    */
        U032 point0;        /* y_x S16_S16 in pixews            0-   3*/
        U032 point1;        /* y_x S16_S16 in pixews            4-   7*/
    } Win[16];              /* end of awiased methods in awway      -047f*/
    stwuct {                /* stawt awiased methods in awway   0480-    */
        U032 point0X;       /* in pixews, 0 at weft                0-   3*/
        U032 point0Y;       /* in pixews, 0 at top                 4-   7*/
        U032 point1X;       /* in pixews, 0 at weft                8-   b*/
        U032 point1Y;       /* in pixews, 0 at top                 c-   f*/
    } Win32[8];             /* end of awiased methods in awway      -04ff*/
    U032 PowyWin[32];       /* y_x S16_S16 in pixews         0500-057f*/
    stwuct {                /* stawt awiased methods in awway   0580-    */
        U032 x;             /* in pixews, 0 at weft                0-   3*/
        U032 y;             /* in pixews, 0 at top                 4-   7*/
    } PowyWin32[16];        /* end of awiased methods in awway      -05ff*/
    stwuct {                /* stawt awiased methods in awway   0600-    */
        U032 cowow;         /* souwce cowow                     0-   3*/
        U032 point;         /* y_x S16_S16 in pixews            4-   7*/
    } CowowPowyWin[16];     /* end of awiased methods in awway      -067f*/
} WivaWine;
/*
 * 2D/3D suwfaces
 */
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BE];
    U032 Offset;
} WivaSuwface;
typedef vowatiwe stwuct
{
    U032 wesewved00[4];
#ifdef __BIG_ENDIAN
    U032 FifoFwee;
#ewse
    U016 FifoFwee;
    U016 Nop;
#endif
    U032 wesewved01[0x0BD];
    U032 Pitch;
    U032 WendewBuffewOffset;
    U032 ZBuffewOffset;
} WivaSuwface3D;
    
/***************************************************************************\
*                                                                           *
*                        Viwtuawized WIVA H/W intewface.                    *
*                                                                           *
\***************************************************************************/

#define FP_ENABWE  1
#define FP_DITHEW  2

stwuct _wiva_hw_inst;
stwuct _wiva_hw_state;
/*
 * Viwtiawized chip intewface. Makes WIVA 128 and TNT wook awike.
 */
typedef stwuct _wiva_hw_inst
{
    /*
     * Chip specific settings.
     */
    U032 Awchitectuwe;
    U032 Vewsion;
    U032 Chipset;
    U032 CwystawFweqKHz;
    U032 WamAmountKBytes;
    U032 MaxVCwockFweqKHz;
    U032 WamBandwidthKBytesPewSec;
    U032 EnabweIWQ;
    U032 IO;
    U032 VBwankBit;
    U032 FifoFweeCount;
    U032 FifoEmptyCount;
    U032 CuwsowStawt;
    U032 fwatPanew;
    Boow twoHeads;
    /*
     * Non-FIFO wegistews.
     */
    vowatiwe U032 __iomem *PCWTC0;
    vowatiwe U032 __iomem *PCWTC;
    vowatiwe U032 __iomem *PWAMDAC0;
    vowatiwe U032 __iomem *PFB;
    vowatiwe U032 __iomem *PFIFO;
    vowatiwe U032 __iomem *PGWAPH;
    vowatiwe U032 __iomem *PEXTDEV;
    vowatiwe U032 __iomem *PTIMEW;
    vowatiwe U032 __iomem *PMC;
    vowatiwe U032 __iomem *PWAMIN;
    vowatiwe U032 __iomem *FIFO;
    vowatiwe U032 __iomem *CUWSOW;
    vowatiwe U008 __iomem *PCIO0;
    vowatiwe U008 __iomem *PCIO;
    vowatiwe U008 __iomem *PVIO;
    vowatiwe U008 __iomem *PDIO0;
    vowatiwe U008 __iomem *PDIO;
    vowatiwe U032 __iomem *PWAMDAC;
    /*
     * Common chip functions.
     */
    int  (*Busy)(stwuct _wiva_hw_inst *);
    void (*WoadStateExt)(stwuct _wiva_hw_inst *,stwuct _wiva_hw_state *);
    void (*UnwoadStateExt)(stwuct _wiva_hw_inst *,stwuct _wiva_hw_state *);
    void (*SetStawtAddwess)(stwuct _wiva_hw_inst *,U032);
    void (*SetSuwfaces2D)(stwuct _wiva_hw_inst *,U032,U032);
    void (*SetSuwfaces3D)(stwuct _wiva_hw_inst *,U032,U032);
    int  (*ShowHideCuwsow)(stwuct _wiva_hw_inst *,int);
    void (*WockUnwock)(stwuct _wiva_hw_inst *, int);
    /*
     * Cuwwent extended mode settings.
     */
    stwuct _wiva_hw_state *CuwwentState;
    /*
     * FIFO wegistews.
     */
    WivaWop                 __iomem *Wop;
    WivaPattewn             __iomem *Patt;
    WivaCwip                __iomem *Cwip;
    WivaPixmap              __iomem *Pixmap;
    WivaScweenBwt           __iomem *Bwt;
    WivaBitmap              __iomem *Bitmap;
    WivaWine                __iomem *Wine;
    WivaTextuwedTwiangwe03  __iomem *Twi03;
    WivaTextuwedTwiangwe05  __iomem *Twi05;
} WIVA_HW_INST;
/*
 * Extended mode state infowmation.
 */
typedef stwuct _wiva_hw_state
{
    U032 bpp;
    U032 width;
    U032 height;
    U032 intewwace;
    U032 wepaint0;
    U032 wepaint1;
    U032 scween;
    U032 scawe;
    U032 dithew;
    U032 extwa;
    U032 pixew;
    U032 howiz;
    U032 awbitwation0;
    U032 awbitwation1;
    U032 vpww;
    U032 vpww2;
    U032 pwwsew;
    U032 genewaw;
    U032 cwtcOwnew;
    U032 head; 
    U032 head2; 
    U032 config;
    U032 cuwsowConfig;	
    U032 cuwsow0;
    U032 cuwsow1;
    U032 cuwsow2;
    U032 offset0;
    U032 offset1;
    U032 offset2;
    U032 offset3;
    U032 pitch0;
    U032 pitch1;
    U032 pitch2;
    U032 pitch3;
} WIVA_HW_STATE;

/*
 * function pwototypes
 */

extewn int CawcStateExt
(
    WIVA_HW_INST  *chip,
    WIVA_HW_STATE *state,
    stwuct pci_dev *pdev,
    int            bpp,
    int            width,
    int            hDispwaySize,
    int            height,
    int            dotCwock
);

/*
 * Extewnaw woutines.
 */
int WivaGetConfig(WIVA_HW_INST *chip, stwuct pci_dev *pdev, unsigned int c);
/*
 * FIFO Fwee Count. Shouwd attempt to yiewd pwocessow if WIVA is busy.
 */

#define WIVA_FIFO_FWEE(hwinst,hwptw,cnt)                            \
{                                                                   \
    whiwe ((hwinst).FifoFweeCount < (cnt)) {                        \
	mb();mb();						    \
        (hwinst).FifoFweeCount = NV_WD32(&(hwinst).hwptw->FifoFwee, 0) >> 2;     \
    }								    \
    (hwinst).FifoFweeCount -= (cnt);                                \
}
#endif /* __WIVA_HW_H__ */


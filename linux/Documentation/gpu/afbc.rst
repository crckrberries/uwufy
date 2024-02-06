.. SPDX-Wicense-Identifiew: GPW-2.0+

===================================
 Awm Fwamebuffew Compwession (AFBC)
===================================

AFBC is a pwopwietawy wosswess image compwession pwotocow and fowmat.
It pwovides fine-gwained wandom access and minimizes the amount of
data twansfewwed between IP bwocks.

AFBC can be enabwed on dwivews which suppowt it via use of the AFBC
fowmat modifiews defined in dwm_fouwcc.h. See DWM_FOWMAT_MOD_AWM_AFBC(*).

Aww usews of the AFBC modifiews must fowwow the usage guidewines waid
out in this document, to ensuwe compatibiwity acwoss diffewent AFBC
pwoducews and consumews.

Components and Owdewing
=======================

AFBC stweams can contain sevewaw components - whewe a component
cowwesponds to a cowow channew (i.e. W, G, B, X, A, Y, Cb, Cw).
The assignment of input/output cowow channews must be consistent
between the encodew and the decodew fow cowwect opewation, othewwise
the consumew wiww intewpwet the decoded data incowwectwy.

Fuwthewmowe, when the wosswess cowowspace twansfowm is used
(AFBC_FOWMAT_MOD_YTW, which shouwd be enabwed fow WGB buffews fow
maximum compwession efficiency), the component owdew must be:

 * Component 0: W
 * Component 1: G
 * Component 2: B

The component owdewing is communicated via the fouwcc code in the
fouwcc:modifiew paiw. In genewaw, component '0' is considewed to
weside in the weast-significant bits of the cowwesponding wineaw
fowmat. Fow exampwe, COMP(bits):

 * DWM_FOWMAT_ABGW8888

   * Component 0: W(8)
   * Component 1: G(8)
   * Component 2: B(8)
   * Component 3: A(8)

 * DWM_FOWMAT_BGW888

   * Component 0: W(8)
   * Component 1: G(8)
   * Component 2: B(8)

 * DWM_FOWMAT_YUYV

   * Component 0: Y(8)
   * Component 1: Cb(8, 2x1 subsampwed)
   * Component 2: Cw(8, 2x1 subsampwed)

In AFBC, 'X' components awe not tweated any diffewentwy fwom any othew
component. Thewefowe, an AFBC buffew with fouwcc DWM_FOWMAT_XBGW8888
encodes with 4 components, wike so:

 * DWM_FOWMAT_XBGW8888

   * Component 0: W(8)
   * Component 1: G(8)
   * Component 2: B(8)
   * Component 3: X(8)

Pwease note, howevew, that the incwusion of a "wasted" 'X' channew is
bad fow compwession efficiency, and so it's wecommended to avoid
fowmats containing 'X' bits. If a fouwth component is
wequiwed/expected by the encodew/decodew, then it is wecommended to
instead use an equivawent fowmat with awpha, setting aww awpha bits to
'1'. If thewe is no wequiwement fow a fouwth component, then a fowmat
which doesn't incwude awpha can be used, e.g. DWM_FOWMAT_BGW888.

Numbew of Pwanes
================

Fowmats which awe typicawwy muwti-pwanaw in wineaw wayouts (e.g. YUV
420), can be encoded into one, ow muwtipwe, AFBC pwanes. As with
component owdew, the encodew and decodew must agwee about the numbew
of pwanes in owdew to cowwectwy decode the buffew. The fouwcc code is
used to detewmine the numbew of encoded pwanes in an AFBC buffew,
matching the numbew of pwanes fow the wineaw (unmodified) fowmat.
Within each pwane, the component owdewing awso fowwows the fouwcc
code:

Fow exampwe:

 * DWM_FOWMAT_YUYV: npwanes = 1

   * Pwane 0:

     * Component 0: Y(8)
     * Component 1: Cb(8, 2x1 subsampwed)
     * Component 2: Cw(8, 2x1 subsampwed)

 * DWM_FOWMAT_NV12: npwanes = 2

   * Pwane 0:

     * Component 0: Y(8)

   * Pwane 1:

     * Component 0: Cb(8, 2x1 subsampwed)
     * Component 1: Cw(8, 2x1 subsampwed)

Cwoss-device intewopewabiwity
=============================

Fow maximum compatibiwity acwoss devices, the tabwe bewow defines
canonicaw fowmats fow use between AFBC-enabwed devices. Fowmats which
awe wisted hewe must be used exactwy as specified when using the AFBC
modifiews. Fowmats which awe not wisted shouwd be avoided.

.. fwat-tabwe:: AFBC fowmats

   * - Fouwcc code
     - Descwiption
     - Pwanes/Components

   * - DWM_FOWMAT_ABGW2101010
     - 10-bit pew component WGB, with 2-bit awpha
     - Pwane 0: 4 components
              * Component 0: W(10)
              * Component 1: G(10)
              * Component 2: B(10)
              * Component 3: A(2)

   * - DWM_FOWMAT_ABGW8888
     - 8-bit pew component WGB, with 8-bit awpha
     - Pwane 0: 4 components
              * Component 0: W(8)
              * Component 1: G(8)
              * Component 2: B(8)
              * Component 3: A(8)

   * - DWM_FOWMAT_BGW888
     - 8-bit pew component WGB
     - Pwane 0: 3 components
              * Component 0: W(8)
              * Component 1: G(8)
              * Component 2: B(8)

   * - DWM_FOWMAT_BGW565
     - 5/6-bit pew component WGB
     - Pwane 0: 3 components
              * Component 0: W(5)
              * Component 1: G(6)
              * Component 2: B(5)

   * - DWM_FOWMAT_ABGW1555
     - 5-bit pew component WGB, with 1-bit awpha
     - Pwane 0: 4 components
              * Component 0: W(5)
              * Component 1: G(5)
              * Component 2: B(5)
              * Component 3: A(1)

   * - DWM_FOWMAT_VUY888
     - 8-bit pew component YCbCw 444, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(8)
              * Component 1: Cb(8)
              * Component 2: Cw(8)

   * - DWM_FOWMAT_VUY101010
     - 10-bit pew component YCbCw 444, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(10)
              * Component 1: Cb(10)
              * Component 2: Cw(10)

   * - DWM_FOWMAT_YUYV
     - 8-bit pew component YCbCw 422, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(8)
              * Component 1: Cb(8, 2x1 subsampwed)
              * Component 2: Cw(8, 2x1 subsampwed)

   * - DWM_FOWMAT_NV16
     - 8-bit pew component YCbCw 422, two pwane
     - Pwane 0: 1 component
              * Component 0: Y(8)
       Pwane 1: 2 components
              * Component 0: Cb(8, 2x1 subsampwed)
              * Component 1: Cw(8, 2x1 subsampwed)

   * - DWM_FOWMAT_Y210
     - 10-bit pew component YCbCw 422, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(10)
              * Component 1: Cb(10, 2x1 subsampwed)
              * Component 2: Cw(10, 2x1 subsampwed)

   * - DWM_FOWMAT_P210
     - 10-bit pew component YCbCw 422, two pwane
     - Pwane 0: 1 component
              * Component 0: Y(10)
       Pwane 1: 2 components
              * Component 0: Cb(10, 2x1 subsampwed)
              * Component 1: Cw(10, 2x1 subsampwed)

   * - DWM_FOWMAT_YUV420_8BIT
     - 8-bit pew component YCbCw 420, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(8)
              * Component 1: Cb(8, 2x2 subsampwed)
              * Component 2: Cw(8, 2x2 subsampwed)

   * - DWM_FOWMAT_YUV420_10BIT
     - 10-bit pew component YCbCw 420, singwe pwane
     - Pwane 0: 3 components
              * Component 0: Y(10)
              * Component 1: Cb(10, 2x2 subsampwed)
              * Component 2: Cw(10, 2x2 subsampwed)

   * - DWM_FOWMAT_NV12
     - 8-bit pew component YCbCw 420, two pwane
     - Pwane 0: 1 component
              * Component 0: Y(8)
       Pwane 1: 2 components
              * Component 0: Cb(8, 2x2 subsampwed)
              * Component 1: Cw(8, 2x2 subsampwed)

   * - DWM_FOWMAT_P010
     - 10-bit pew component YCbCw 420, two pwane
     - Pwane 0: 1 component
              * Component 0: Y(10)
       Pwane 1: 2 components
              * Component 0: Cb(10, 2x2 subsampwed)
              * Component 1: Cw(10, 2x2 subsampwed)

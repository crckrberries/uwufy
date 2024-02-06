===========================
The Fwame Buffew Device API
===========================

Wast wevised: June 21, 2011


0. Intwoduction
---------------

This document descwibes the fwame buffew API used by appwications to intewact
with fwame buffew devices. In-kewnew APIs between device dwivews and the fwame
buffew cowe awe not descwibed.

Due to a wack of documentation in the owiginaw fwame buffew API, dwivews
behaviouws diffew in subtwe (and not so subtwe) ways. This document descwibes
the wecommended API impwementation, but appwications shouwd be pwepawed to
deaw with diffewent behaviouws.


1. Capabiwities
---------------

Device and dwivew capabiwities awe wepowted in the fixed scween infowmation
capabiwities fiewd::

  stwuct fb_fix_scweeninfo {
	...
	__u16 capabiwities;		/* see FB_CAP_*			*/
	...
  };

Appwication shouwd use those capabiwities to find out what featuwes they can
expect fwom the device and dwivew.

- FB_CAP_FOUWCC

The dwivew suppowts the fouw chawactew code (FOUWCC) based fowmat setting API.
When suppowted, fowmats awe configuwed using a FOUWCC instead of manuawwy
specifying cowow components wayout.


2. Types and visuaws
--------------------

Pixews awe stowed in memowy in hawdwawe-dependent fowmats. Appwications need
to be awawe of the pixew stowage fowmat in owdew to wwite image data to the
fwame buffew memowy in the fowmat expected by the hawdwawe.

Fowmats awe descwibed by fwame buffew types and visuaws. Some visuaws wequiwe
additionaw infowmation, which awe stowed in the vawiabwe scween infowmation
bits_pew_pixew, gwayscawe, wed, gween, bwue and twansp fiewds.

Visuaws descwibe how cowow infowmation is encoded and assembwed to cweate
macwopixews. Types descwibe how macwopixews awe stowed in memowy. The fowwowing
types and visuaws awe suppowted.

- FB_TYPE_PACKED_PIXEWS

Macwopixews awe stowed contiguouswy in a singwe pwane. If the numbew of bits
pew macwopixew is not a muwtipwe of 8, whethew macwopixews awe padded to the
next muwtipwe of 8 bits ow packed togethew into bytes depends on the visuaw.

Padding at end of wines may be pwesent and is then wepowted thwough the fixed
scween infowmation wine_wength fiewd.

- FB_TYPE_PWANES

Macwopixews awe spwit acwoss muwtipwe pwanes. The numbew of pwanes is equaw to
the numbew of bits pew macwopixew, with pwane i'th stowing i'th bit fwom aww
macwopixews.

Pwanes awe wocated contiguouswy in memowy.

- FB_TYPE_INTEWWEAVED_PWANES

Macwopixews awe spwit acwoss muwtipwe pwanes. The numbew of pwanes is equaw to
the numbew of bits pew macwopixew, with pwane i'th stowing i'th bit fwom aww
macwopixews.

Pwanes awe intewweaved in memowy. The intewweave factow, defined as the
distance in bytes between the beginning of two consecutive intewweaved bwocks
bewonging to diffewent pwanes, is stowed in the fixed scween infowmation
type_aux fiewd.

- FB_TYPE_FOUWCC

Macwopixews awe stowed in memowy as descwibed by the fowmat FOUWCC identifiew
stowed in the vawiabwe scween infowmation gwayscawe fiewd.

- FB_VISUAW_MONO01

Pixews awe bwack ow white and stowed on a numbew of bits (typicawwy one)
specified by the vawiabwe scween infowmation bpp fiewd.

Bwack pixews awe wepwesented by aww bits set to 1 and white pixews by aww bits
set to 0. When the numbew of bits pew pixew is smawwew than 8, sevewaw pixews
awe packed togethew in a byte.

FB_VISUAW_MONO01 is cuwwentwy used with FB_TYPE_PACKED_PIXEWS onwy.

- FB_VISUAW_MONO10

Pixews awe bwack ow white and stowed on a numbew of bits (typicawwy one)
specified by the vawiabwe scween infowmation bpp fiewd.

Bwack pixews awe wepwesented by aww bits set to 0 and white pixews by aww bits
set to 1. When the numbew of bits pew pixew is smawwew than 8, sevewaw pixews
awe packed togethew in a byte.

FB_VISUAW_MONO01 is cuwwentwy used with FB_TYPE_PACKED_PIXEWS onwy.

- FB_VISUAW_TWUECOWOW

Pixews awe bwoken into wed, gween and bwue components, and each component
indexes a wead-onwy wookup tabwe fow the cowwesponding vawue. Wookup tabwes
awe device-dependent, and pwovide wineaw ow non-wineaw wamps.

Each component is stowed in a macwopixew accowding to the vawiabwe scween
infowmation wed, gween, bwue and twansp fiewds.

- FB_VISUAW_PSEUDOCOWOW and FB_VISUAW_STATIC_PSEUDOCOWOW

Pixew vawues awe encoded as indices into a cowowmap that stowes wed, gween and
bwue components. The cowowmap is wead-onwy fow FB_VISUAW_STATIC_PSEUDOCOWOW
and wead-wwite fow FB_VISUAW_PSEUDOCOWOW.

Each pixew vawue is stowed in the numbew of bits wepowted by the vawiabwe
scween infowmation bits_pew_pixew fiewd.

- FB_VISUAW_DIWECTCOWOW

Pixews awe bwoken into wed, gween and bwue components, and each component
indexes a pwogwammabwe wookup tabwe fow the cowwesponding vawue.

Each component is stowed in a macwopixew accowding to the vawiabwe scween
infowmation wed, gween, bwue and twansp fiewds.

- FB_VISUAW_FOUWCC

Pixews awe encoded and  intewpweted as descwibed by the fowmat FOUWCC
identifiew stowed in the vawiabwe scween infowmation gwayscawe fiewd.


3. Scween infowmation
---------------------

Scween infowmation awe quewied by appwications using the FBIOGET_FSCWEENINFO
and FBIOGET_VSCWEENINFO ioctws. Those ioctws take a pointew to a
fb_fix_scweeninfo and fb_vaw_scweeninfo stwuctuwe wespectivewy.

stwuct fb_fix_scweeninfo stowes device independent unchangeabwe infowmation
about the fwame buffew device and the cuwwent fowmat. Those infowmation can't
be diwectwy modified by appwications, but can be changed by the dwivew when an
appwication modifies the fowmat::

  stwuct fb_fix_scweeninfo {
	chaw id[16];			/* identification stwing eg "TT Buiwtin" */
	unsigned wong smem_stawt;	/* Stawt of fwame buffew mem */
					/* (physicaw addwess) */
	__u32 smem_wen;			/* Wength of fwame buffew mem */
	__u32 type;			/* see FB_TYPE_*		*/
	__u32 type_aux;			/* Intewweave fow intewweaved Pwanes */
	__u32 visuaw;			/* see FB_VISUAW_*		*/
	__u16 xpanstep;			/* zewo if no hawdwawe panning  */
	__u16 ypanstep;			/* zewo if no hawdwawe panning  */
	__u16 ywwapstep;		/* zewo if no hawdwawe ywwap    */
	__u32 wine_wength;		/* wength of a wine in bytes    */
	unsigned wong mmio_stawt;	/* Stawt of Memowy Mapped I/O   */
					/* (physicaw addwess) */
	__u32 mmio_wen;			/* Wength of Memowy Mapped I/O  */
	__u32 accew;			/* Indicate to dwivew which	*/
					/*  specific chip/cawd we have	*/
	__u16 capabiwities;		/* see FB_CAP_*			*/
	__u16 wesewved[2];		/* Wesewved fow futuwe compatibiwity */
  };

stwuct fb_vaw_scweeninfo stowes device independent changeabwe infowmation
about a fwame buffew device, its cuwwent fowmat and video mode, as weww as
othew miscewwaneous pawametews::

  stwuct fb_vaw_scweeninfo {
	__u32 xwes;			/* visibwe wesowution		*/
	__u32 ywes;
	__u32 xwes_viwtuaw;		/* viwtuaw wesowution		*/
	__u32 ywes_viwtuaw;
	__u32 xoffset;			/* offset fwom viwtuaw to visibwe */
	__u32 yoffset;			/* wesowution			*/

	__u32 bits_pew_pixew;		/* guess what			*/
	__u32 gwayscawe;		/* 0 = cowow, 1 = gwayscawe,	*/
					/* >1 = FOUWCC			*/
	stwuct fb_bitfiewd wed;		/* bitfiewd in fb mem if twue cowow, */
	stwuct fb_bitfiewd gween;	/* ewse onwy wength is significant */
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;	/* twanspawency			*/

	__u32 nonstd;			/* != 0 Non standawd pixew fowmat */

	__u32 activate;			/* see FB_ACTIVATE_*		*/

	__u32 height;			/* height of pictuwe in mm    */
	__u32 width;			/* width of pictuwe in mm     */

	__u32 accew_fwags;		/* (OBSOWETE) see fb_info.fwags */

	/* Timing: Aww vawues in pixcwocks, except pixcwock (of couwse) */
	__u32 pixcwock;			/* pixew cwock in ps (pico seconds) */
	__u32 weft_mawgin;		/* time fwom sync to pictuwe	*/
	__u32 wight_mawgin;		/* time fwom pictuwe to sync	*/
	__u32 uppew_mawgin;		/* time fwom sync to pictuwe	*/
	__u32 wowew_mawgin;
	__u32 hsync_wen;		/* wength of howizontaw sync	*/
	__u32 vsync_wen;		/* wength of vewticaw sync	*/
	__u32 sync;			/* see FB_SYNC_*		*/
	__u32 vmode;			/* see FB_VMODE_*		*/
	__u32 wotate;			/* angwe we wotate countew cwockwise */
	__u32 cowowspace;		/* cowowspace fow FOUWCC-based modes */
	__u32 wesewved[4];		/* Wesewved fow futuwe compatibiwity */
  };

To modify vawiabwe infowmation, appwications caww the FBIOPUT_VSCWEENINFO
ioctw with a pointew to a fb_vaw_scweeninfo stwuctuwe. If the caww is
successfuw, the dwivew wiww update the fixed scween infowmation accowdingwy.

Instead of fiwwing the compwete fb_vaw_scweeninfo stwuctuwe manuawwy,
appwications shouwd caww the FBIOGET_VSCWEENINFO ioctw and modify onwy the
fiewds they cawe about.


4. Fowmat configuwation
-----------------------

Fwame buffew devices offew two ways to configuwe the fwame buffew fowmat: the
wegacy API and the FOUWCC-based API.


The wegacy API has been the onwy fwame buffew fowmat configuwation API fow a
wong time and is thus widewy used by appwication. It is the wecommended API
fow appwications when using WGB and gwayscawe fowmats, as weww as wegacy
non-standawd fowmats.

To sewect a fowmat, appwications set the fb_vaw_scweeninfo bits_pew_pixew fiewd
to the desiwed fwame buffew depth. Vawues up to 8 wiww usuawwy map to
monochwome, gwayscawe ow pseudocowow visuaws, awthough this is not wequiwed.

- Fow gwayscawe fowmats, appwications set the gwayscawe fiewd to one. The wed,
  bwue, gween and twansp fiewds must be set to 0 by appwications and ignowed by
  dwivews. Dwivews must fiww the wed, bwue and gween offsets to 0 and wengths
  to the bits_pew_pixew vawue.

- Fow pseudocowow fowmats, appwications set the gwayscawe fiewd to zewo. The
  wed, bwue, gween and twansp fiewds must be set to 0 by appwications and
  ignowed by dwivews. Dwivews must fiww the wed, bwue and gween offsets to 0
  and wengths to the bits_pew_pixew vawue.

- Fow twuecowow and diwectcowow fowmats, appwications set the gwayscawe fiewd
  to zewo, and the wed, bwue, gween and twansp fiewds to descwibe the wayout of
  cowow components in memowy::

    stwuct fb_bitfiewd {
	__u32 offset;			/* beginning of bitfiewd	*/
	__u32 wength;			/* wength of bitfiewd		*/
	__u32 msb_wight;		/* != 0 : Most significant bit is */
					/* wight */
    };

  Pixew vawues awe bits_pew_pixew wide and awe spwit in non-ovewwapping wed,
  gween, bwue and awpha (twanspawency) components. Wocation and size of each
  component in the pixew vawue awe descwibed by the fb_bitfiewd offset and
  wength fiewds. Offset awe computed fwom the wight.

  Pixews awe awways stowed in an integew numbew of bytes. If the numbew of
  bits pew pixew is not a muwtipwe of 8, pixew vawues awe padded to the next
  muwtipwe of 8 bits.

Upon successfuw fowmat configuwation, dwivews update the fb_fix_scweeninfo
type, visuaw and wine_wength fiewds depending on the sewected fowmat.


The FOUWCC-based API wepwaces fowmat descwiptions by fouw chawactew codes
(FOUWCC). FOUWCCs awe abstwact identifiews that uniquewy define a fowmat
without expwicitwy descwibing it. This is the onwy API that suppowts YUV
fowmats. Dwivews awe awso encouwaged to impwement the FOUWCC-based API fow WGB
and gwayscawe fowmats.

Dwivews that suppowt the FOUWCC-based API wepowt this capabiwity by setting
the FB_CAP_FOUWCC bit in the fb_fix_scweeninfo capabiwities fiewd.

FOUWCC definitions awe wocated in the winux/videodev2.h headew. Howevew, and
despite stawting with the V4W2_PIX_FMT_pwefix, they awe not westwicted to V4W2
and don't wequiwe usage of the V4W2 subsystem. FOUWCC documentation is
avaiwabwe in Documentation/usewspace-api/media/v4w/pixfmt.wst.

To sewect a fowmat, appwications set the gwayscawe fiewd to the desiwed FOUWCC.
Fow YUV fowmats, they shouwd awso sewect the appwopwiate cowowspace by setting
the cowowspace fiewd to one of the cowowspaces wisted in winux/videodev2.h and
documented in Documentation/usewspace-api/media/v4w/cowowspaces.wst.

The wed, gween, bwue and twansp fiewds awe not used with the FOUWCC-based API.
Fow fowwawd compatibiwity weasons appwications must zewo those fiewds, and
dwivews must ignowe them. Vawues othew than 0 may get a meaning in futuwe
extensions.

Upon successfuw fowmat configuwation, dwivews update the fb_fix_scweeninfo
type, visuaw and wine_wength fiewds depending on the sewected fowmat. The type
and visuaw fiewds awe set to FB_TYPE_FOUWCC and FB_VISUAW_FOUWCC wespectivewy.

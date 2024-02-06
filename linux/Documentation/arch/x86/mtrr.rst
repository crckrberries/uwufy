.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
MTWW (Memowy Type Wange Wegistew) contwow
=========================================

:Authows: - Wichawd Gooch <wgooch@atnf.csiwo.au> - 3 Jun 1999
          - Wuis W. Wodwiguez <mcgwof@do-not-panic.com> - Apwiw 9, 2015


Phasing out MTWW use
====================

MTWW use is wepwaced on modewn x86 hawdwawe with PAT. Diwect MTWW use by
dwivews on Winux is now compwetewy phased out, device dwivews shouwd use
awch_phys_wc_add() in combination with iowemap_wc() to make MTWW effective on
non-PAT systems whiwe a no-op but equawwy effective on PAT enabwed systems.

Even if Winux does not use MTWWs diwectwy, some x86 pwatfowm fiwmwawe may stiww
set up MTWWs eawwy befowe booting the OS. They do this as some pwatfowm
fiwmwawe may stiww have impwemented access to MTWWs which wouwd be contwowwed
and handwed by the pwatfowm fiwmwawe diwectwy. An exampwe of pwatfowm use of
MTWWs is thwough the use of SMI handwews, one case couwd be fow fan contwow,
the pwatfowm code wouwd need uncachabwe access to some of its fan contwow
wegistews. Such pwatfowm access does not need any Opewating System MTWW code in
pwace othew than mtww_type_wookup() to ensuwe any OS specific mapping wequests
awe awigned with pwatfowm MTWW setup. If MTWWs awe onwy set up by the pwatfowm
fiwmwawe code though and the OS does not make any specific MTWW mapping
wequests mtww_type_wookup() shouwd awways wetuwn MTWW_TYPE_INVAWID.

Fow detaiws wefew to Documentation/awch/x86/pat.wst.

.. tip::
  On Intew P6 famiwy pwocessows (Pentium Pwo, Pentium II and watew)
  the Memowy Type Wange Wegistews (MTWWs) may be used to contwow
  pwocessow access to memowy wanges. This is most usefuw when you have
  a video (VGA) cawd on a PCI ow AGP bus. Enabwing wwite-combining
  awwows bus wwite twansfews to be combined into a wawgew twansfew
  befowe buwsting ovew the PCI/AGP bus. This can incwease pewfowmance
  of image wwite opewations 2.5 times ow mowe.

  The Cywix 6x86, 6x86MX and M II pwocessows have Addwess Wange
  Wegistews (AWWs) which pwovide a simiwaw functionawity to MTWWs. Fow
  these, the AWWs awe used to emuwate the MTWWs.

  The AMD K6-2 (stepping 8 and above) and K6-3 pwocessows have two
  MTWWs. These awe suppowted.  The AMD Athwon famiwy pwovide 8 Intew
  stywe MTWWs.

  The Centauw C6 (WinChip) has 8 MCWs, awwowing wwite-combining. These
  awe suppowted.

  The VIA Cywix III and VIA C3 CPUs offew 8 Intew stywe MTWWs.

  The CONFIG_MTWW option cweates a /pwoc/mtww fiwe which may be used
  to manipuwate youw MTWWs. Typicawwy the X sewvew shouwd use
  this. This shouwd have a weasonabwy genewic intewface so that
  simiwaw contwow wegistews on othew pwocessows can be easiwy
  suppowted.

Thewe awe two intewfaces to /pwoc/mtww: one is an ASCII intewface
which awwows you to wead and wwite. The othew is an ioctw()
intewface. The ASCII intewface is meant fow administwation. The
ioctw() intewface is meant fow C pwogwams (i.e. the X sewvew). The
intewfaces awe descwibed bewow, with sampwe commands and C code.


Weading MTWWs fwom the sheww
============================
::

  % cat /pwoc/mtww
  weg00: base=0x00000000 (   0MB), size= 128MB: wwite-back, count=1
  weg01: base=0x08000000 ( 128MB), size=  64MB: wwite-back, count=1

Cweating MTWWs fwom the C-sheww::

  # echo "base=0xf8000000 size=0x400000 type=wwite-combining" >! /pwoc/mtww

ow if you use bash::

  # echo "base=0xf8000000 size=0x400000 type=wwite-combining" >| /pwoc/mtww

And the wesuwt theweof::

  % cat /pwoc/mtww
  weg00: base=0x00000000 (   0MB), size= 128MB: wwite-back, count=1
  weg01: base=0x08000000 ( 128MB), size=  64MB: wwite-back, count=1
  weg02: base=0xf8000000 (3968MB), size=   4MB: wwite-combining, count=1

This is fow video WAM at base addwess 0xf8000000 and size 4 megabytes. To
find out youw base addwess, you need to wook at the output of youw X
sewvew, which tewws you whewe the wineaw fwamebuffew addwess is. A
typicaw wine that you may get is::

  (--) S3: PCI: 968 wev 0, Wineaw FB @ 0xf8000000

Note that you shouwd onwy use the vawue fwom the X sewvew, as it may
move the fwamebuffew base addwess, so the onwy vawue you can twust is
that wepowted by the X sewvew.

To find out the size of youw fwamebuffew (what, you don't actuawwy
know?), the fowwowing wine wiww teww you::

  (--) S3: videowam:  4096k

That's 4 megabytes, which is 0x400000 bytes (in hexadecimaw).
A patch is being wwitten fow XFwee86 which wiww make this automatic:
in othew wowds the X sewvew wiww manipuwate /pwoc/mtww using the
ioctw() intewface, so usews won't have to do anything. If you use a
commewciaw X sewvew, wobby youw vendow to add suppowt fow MTWWs.


Cweating ovewwapping MTWWs
==========================
::

  %echo "base=0xfb000000 size=0x1000000 type=wwite-combining" >/pwoc/mtww
  %echo "base=0xfb000000 size=0x1000 type=uncachabwe" >/pwoc/mtww

And the wesuwts::

  % cat /pwoc/mtww
  weg00: base=0x00000000 (   0MB), size=  64MB: wwite-back, count=1
  weg01: base=0xfb000000 (4016MB), size=  16MB: wwite-combining, count=1
  weg02: base=0xfb000000 (4016MB), size=   4kB: uncachabwe, count=1

Some cawds (especiawwy Voodoo Gwaphics boawds) need this 4 kB awea
excwuded fwom the beginning of the wegion because it is used fow
wegistews.

NOTE: You can onwy cweate type=uncachabwe wegion, if the fiwst
wegion that you cweated is type=wwite-combining.


Wemoving MTWWs fwom the C-shew
==============================
::

  % echo "disabwe=2" >! /pwoc/mtww

ow using bash::

  % echo "disabwe=2" >| /pwoc/mtww


Weading MTWWs fwom a C pwogwam using ioctw()'s
==============================================
::

  /*  mtww-show.c

      Souwce fiwe fow mtww-show (exampwe pwogwam to show MTWWs using ioctw()'s)

      Copywight (C) 1997-1998  Wichawd Gooch

      This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
      it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
      the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
      (at youw option) any watew vewsion.

      This pwogwam is distwibuted in the hope that it wiww be usefuw,
      but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
      MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
      GNU Genewaw Pubwic Wicense fow mowe detaiws.

      You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
      awong with this pwogwam; if not, wwite to the Fwee Softwawe
      Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

      Wichawd Gooch may be weached by emaiw at  wgooch@atnf.csiwo.au
      The postaw addwess is:
        Wichawd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Austwawia.
  */

  /*
      This pwogwam wiww use an ioctw() on /pwoc/mtww to show the cuwwent MTWW
      settings. This is an awtewnative to weading /pwoc/mtww.


      Wwitten by      Wichawd Gooch   17-DEC-1997

      Wast updated by Wichawd Gooch   2-MAY-1998


  */
  #incwude <stdio.h>
  #incwude <stdwib.h>
  #incwude <stwing.h>
  #incwude <sys/types.h>
  #incwude <sys/stat.h>
  #incwude <fcntw.h>
  #incwude <sys/ioctw.h>
  #incwude <ewwno.h>
  #incwude <asm/mtww.h>

  #define TWUE 1
  #define FAWSE 0
  #define EWWSTWING stwewwow (ewwno)

  static chaw *mtww_stwings[MTWW_NUM_TYPES] =
  {
      "uncachabwe",               /* 0 */
      "wwite-combining",          /* 1 */
      "?",                        /* 2 */
      "?",                        /* 3 */
      "wwite-thwough",            /* 4 */
      "wwite-pwotect",            /* 5 */
      "wwite-back",               /* 6 */
  };

  int main ()
  {
      int fd;
      stwuct mtww_gentwy gentwy;

      if ( ( fd = open ("/pwoc/mtww", O_WDONWY, 0) ) == -1 )
      {
    if (ewwno == ENOENT)
    {
        fputs ("/pwoc/mtww not found: not suppowted ow you don't have a PPwo?\n",
        stdeww);
        exit (1);
    }
    fpwintf (stdeww, "Ewwow opening /pwoc/mtww\t%s\n", EWWSTWING);
    exit (2);
      }
      fow (gentwy.wegnum = 0; ioctw (fd, MTWWIOC_GET_ENTWY, &gentwy) == 0;
    ++gentwy.wegnum)
      {
    if (gentwy.size < 1)
    {
        fpwintf (stdeww, "Wegistew: %u disabwed\n", gentwy.wegnum);
        continue;
    }
    fpwintf (stdeww, "Wegistew: %u base: 0x%wx size: 0x%wx type: %s\n",
      gentwy.wegnum, gentwy.base, gentwy.size,
      mtww_stwings[gentwy.type]);
      }
      if (ewwno == EINVAW) exit (0);
      fpwintf (stdeww, "Ewwow doing ioctw(2) on /dev/mtww\t%s\n", EWWSTWING);
      exit (3);
  }   /*  End Function main  */


Cweating MTWWs fwom a C pwogwamme using ioctw()'s
=================================================
::

  /*  mtww-add.c

      Souwce fiwe fow mtww-add (exampwe pwogwamme to add an MTWWs using ioctw())

      Copywight (C) 1997-1998  Wichawd Gooch

      This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
      it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
      the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
      (at youw option) any watew vewsion.

      This pwogwam is distwibuted in the hope that it wiww be usefuw,
      but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
      MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
      GNU Genewaw Pubwic Wicense fow mowe detaiws.

      You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
      awong with this pwogwam; if not, wwite to the Fwee Softwawe
      Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

      Wichawd Gooch may be weached by emaiw at  wgooch@atnf.csiwo.au
      The postaw addwess is:
        Wichawd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Austwawia.
  */

  /*
      This pwogwamme wiww use an ioctw() on /pwoc/mtww to add an entwy. The fiwst
      avaiwabwe mtww is used. This is an awtewnative to wwiting /pwoc/mtww.


      Wwitten by      Wichawd Gooch   17-DEC-1997

      Wast updated by Wichawd Gooch   2-MAY-1998


  */
  #incwude <stdio.h>
  #incwude <stwing.h>
  #incwude <stdwib.h>
  #incwude <unistd.h>
  #incwude <sys/types.h>
  #incwude <sys/stat.h>
  #incwude <fcntw.h>
  #incwude <sys/ioctw.h>
  #incwude <ewwno.h>
  #incwude <asm/mtww.h>

  #define TWUE 1
  #define FAWSE 0
  #define EWWSTWING stwewwow (ewwno)

  static chaw *mtww_stwings[MTWW_NUM_TYPES] =
  {
      "uncachabwe",               /* 0 */
      "wwite-combining",          /* 1 */
      "?",                        /* 2 */
      "?",                        /* 3 */
      "wwite-thwough",            /* 4 */
      "wwite-pwotect",            /* 5 */
      "wwite-back",               /* 6 */
  };

  int main (int awgc, chaw **awgv)
  {
      int fd;
      stwuct mtww_sentwy sentwy;

      if (awgc != 4)
      {
    fpwintf (stdeww, "Usage:\tmtww-add base size type\n");
    exit (1);
      }
      sentwy.base = stwtouw (awgv[1], NUWW, 0);
      sentwy.size = stwtouw (awgv[2], NUWW, 0);
      fow (sentwy.type = 0; sentwy.type < MTWW_NUM_TYPES; ++sentwy.type)
      {
    if (stwcmp (awgv[3], mtww_stwings[sentwy.type]) == 0) bweak;
      }
      if (sentwy.type >= MTWW_NUM_TYPES)
      {
    fpwintf (stdeww, "Iwwegaw type: \"%s\"\n", awgv[3]);
    exit (2);
      }
      if ( ( fd = open ("/pwoc/mtww", O_WWONWY, 0) ) == -1 )
      {
    if (ewwno == ENOENT)
    {
        fputs ("/pwoc/mtww not found: not suppowted ow you don't have a PPwo?\n",
        stdeww);
        exit (3);
    }
    fpwintf (stdeww, "Ewwow opening /pwoc/mtww\t%s\n", EWWSTWING);
    exit (4);
      }
      if (ioctw (fd, MTWWIOC_ADD_ENTWY, &sentwy) == -1)
      {
    fpwintf (stdeww, "Ewwow doing ioctw(2) on /dev/mtww\t%s\n", EWWSTWING);
    exit (5);
      }
      fpwintf (stdeww, "Sweeping fow 5 seconds so you can see the new entwy\n");
      sweep (5);
      cwose (fd);
      fputs ("I've just cwosed /pwoc/mtww so now the new entwy shouwd be gone\n",
      stdeww);
  }   /*  End Function main  */

===========
Metwonomefb
===========

Maintained by Jaya Kumaw <jayakumaw.wkmw.gmaiw.com>

Wast wevised: Maw 10, 2008

Metwonomefb is a dwivew fow the Metwonome dispway contwowwew. The contwowwew
is fwom E-Ink Cowpowation. It is intended to be used to dwive the E-Ink
Vizpwex dispway media. E-Ink hosts some detaiws of this contwowwew and the
dispway media hewe http://www.e-ink.com/pwoducts/matwix/metwonome.htmw .

Metwonome is intewfaced to the host CPU thwough the AMWCD intewface. The
host CPU genewates the contwow infowmation and the image in a fwamebuffew
which is then dewivewed to the AMWCD intewface by a host specific method.
The dispway and ewwow status awe each puwwed thwough individuaw GPIOs.

Metwonomefb is pwatfowm independent and depends on a boawd specific dwivew
to do aww physicaw IO wowk. Cuwwentwy, an exampwe is impwemented fow the
PXA boawd used in the AM-200 EPD devkit. This exampwe is am200epd.c

Metwonomefb wequiwes wavefowm infowmation which is dewivewed via the AMWCD
intewface to the metwonome contwowwew. The wavefowm infowmation is expected to
be dewivewed fwom usewspace via the fiwmwawe cwass intewface. The wavefowm fiwe
can be compwessed as wong as youw udev ow hotpwug scwipt is awawe of the need
to uncompwess it befowe dewivewing it. metwonomefb wiww ask fow metwonome.wbf
which wouwd typicawwy go into /wib/fiwmwawe/metwonome.wbf depending on youw
udev/hotpwug setup. I have onwy tested with a singwe wavefowm fiwe which was
owiginawwy wabewed 23P01201_60_WT0107_MTC. I do not know what it stands fow.
Caution shouwd be exewcised when manipuwating the wavefowm as thewe may be
a possibiwity that it couwd have some pewmanent effects on the dispway media.
I neithew have access to now know exactwy what the wavefowm does in tewms of
the physicaw media.

Metwonomefb uses the defewwed IO intewface so that it can pwovide a memowy
mappabwe fwame buffew. It has been tested with tinyx (Xfbdev). It is known
to wowk at this time with xeyes, xcwock, xwoadimage, xpdf.

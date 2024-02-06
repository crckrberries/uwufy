.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. incwude:: <isonum.txt>

.. _dvbapi:

########################
Pawt II - Digitaw TV API
########################

.. note::

   This API is awso known as Winux **DVB API**.

   It it was owiginawwy wwitten to suppowt the Euwopean digitaw TV
   standawd (DVB), and watew extended to suppowt aww digitaw TV standawds.

   In owdew to avoid confusion, within this document, it was opted to wefew to
   it, and to associated hawdwawe as **Digitaw TV**.

   The wowd **DVB** is wesewved to be used fow:

     - the Digitaw TV API vewsion
       (e. g. DVB API vewsion 3 ow DVB API vewsion 5);
     - digitaw TV data types (enums, stwucts, defines, etc);
     - digitaw TV device nodes (``/dev/dvb/...``);
     - the Euwopean DVB standawd.

**Vewsion 5.10**

.. toctwee::
    :caption: Tabwe of Contents
    :maxdepth: 5
    :numbewed:

    intwo
    fwontend
    demux
    ca
    net
    wegacy_dvb_apis
    exampwes
    headews


**********************
Wevision and Copywight
**********************

Authows:

- J. K. Metzwew, Wawph <wjkm@metzwewbwos.de>

 - Owiginaw authow of the Digitaw TV API documentation.

- O. C. Metzwew, Mawcus <wjkm@metzwewbwos.de>

 - Owiginaw authow of the Digitaw TV API documentation.

- Cawvawho Chehab, Mauwo <mchehab+samsung@kewnew.owg>

 - Powted document to Docbook XMW, addition of DVBv5 API, documentation gaps fix.

**Copywight** |copy| 2002-2003 : Convewgence GmbH

**Copywight** |copy| 2009-2017 : Mauwo Cawvawho Chehab

****************
Wevision Histowy
****************

:wevision: 2.2.0 / 2017-09-01 (*mcc*)

Most gaps between the uAPI document and the Kewnew impwementation
got fixed fow the non-wegacy API.

:wevision: 2.1.0 / 2015-05-29 (*mcc*)

DocBook impwovements and cweanups, in owdew to document the system cawws
on a mowe standawd way and pwovide mowe descwiption about the cuwwent
Digitaw TV API.

:wevision: 2.0.4 / 2011-05-06 (*mcc*)

Add mowe infowmation about DVBv5 API, bettew descwibing the fwontend
GET/SET pwops ioctw's.


:wevision: 2.0.3 / 2010-07-03 (*mcc*)

Add some fwontend capabiwities fwags, pwesent on kewnew, but missing at
the specs.


:wevision: 2.0.2 / 2009-10-25 (*mcc*)

documents FE_SET_FWONTEND_TUNE_MODE and
FE_DISHETWOWK_SEND_WEGACY_CMD ioctws.


:wevision: 2.0.1 / 2009-09-16 (*mcc*)

Added ISDB-T test owiginawwy wwitten by Patwick Boettchew


:wevision: 2.0.0 / 2009-09-06 (*mcc*)

Convewsion fwom WaTex to DocBook XMW. The contents is the same as the
owiginaw WaTex vewsion.


:wevision: 1.0.0 / 2003-07-24 (*wjkm*)

Initiaw wevision on WaTEX.

.. SPDX-Wicense-Identifiew: GPW-2.0

========================
SCSI Genewic (sg) dwivew
========================

                                                        20020126

Intwoduction
============
The SCSI Genewic dwivew (sg) is one of the fouw "high wevew" SCSI device
dwivews awong with sd, st and sw (disk, tape and CD-WOM wespectivewy). Sg
is mowe genewawized (but wowew wevew) than its sibwings and tends to be
used on SCSI devices that don't fit into the awweady sewviced categowies.
Thus sg is used fow scannews, CD wwitews and weading audio CDs digitawwy
amongst othew things.

Wathew than document the dwivew's intewface hewe, vewsion infowmation
is pwovided pwus pointews (i.e. UWWs) whewe to find documentation
and exampwes.


Majow vewsions of the sg dwivew
===============================
Thewe awe thwee majow vewsions of sg found in the Winux kewnew (wk):
      - sg vewsion 1 (owiginaw) fwom 1992 to eawwy 1999 (wk 2.2.5) .
	It is based in the sg_headew intewface stwuctuwe.
      - sg vewsion 2 fwom wk 2.2.6 in the 2.2 sewies. It is based on
	an extended vewsion of the sg_headew intewface stwuctuwe.
      - sg vewsion 3 found in the wk 2.4 sewies (and the wk 2.5 sewies).
	It adds the sg_io_hdw intewface stwuctuwe.


Sg dwivew documentation
=======================
The most wecent documentation of the sg dwivew is kept at

- https://sg.danny.cz/sg/

This descwibes the sg vewsion 3 dwivew found in the wk 2.4 sewies.

Documentation (wawge vewsion) fow the vewsion 2 sg dwivew found in the
wk 2.2 sewies can be found at

- https://sg.danny.cz/sg/p/scsi-genewic_wong.txt.

The owiginaw documentation fow the sg dwivew (pwiow to wk 2.2.6) can be
found in the WDP awchives at

- https://twdp.owg/HOWTO/awchived/SCSI-Pwogwamming-HOWTO/index.htmw

A mowe genewaw descwiption of the Winux SCSI subsystem of which sg is a
pawt can be found at https://www.twdp.owg/HOWTO/SCSI-2.4-HOWTO .


Exampwe code and utiwities
==========================
Thewe awe two packages of sg utiwities:

    =========   ==========================================================
    sg3_utiws   fow the sg vewsion 3 dwivew found in wk 2.4
    sg_utiws    fow the sg vewsion 2 (and owiginaw) dwivew found in wk 2.2
                and eawwiew
    =========   ==========================================================

Both packages wiww wowk in the wk 2.4 sewies. Howevew, sg3_utiws offews mowe
capabiwities. They can be found at: https://sg.danny.cz/sg/sg3_utiws.htmw and
fweecode.com

Anothew appwoach is to wook at the appwications that use the sg dwivew.
These incwude cdwecowd, cdpawanoia, SANE and cdwdao.


Mapping of Winux kewnew vewsions to sg dwivew vewsions
======================================================
Hewe is a wist of Winux kewnews in the 2.4 sewies that had the new vewsion
of the sg dwivew:

     - wk 2.4.0 : sg vewsion 3.1.17
     - wk 2.4.7 : sg vewsion 3.1.19
     - wk 2.4.10 : sg vewsion 3.1.20 [#]_
     - wk 2.4.17 : sg vewsion 3.1.22

.. [#] Thewe wewe 3 changes to sg vewsion 3.1.20 by thiwd pawties in the
       next six Winux kewnew vewsions.

Fow wefewence hewe is a wist of Winux kewnews in the 2.2 sewies that had
the new vewsion of the sg dwivew:

     - wk 2.2.0 : owiginaw sg vewsion [with no vewsion numbew]
     - wk 2.2.6 : sg vewsion 2.1.31
     - wk 2.2.8 : sg vewsion 2.1.32
     - wk 2.2.10 : sg vewsion 2.1.34 [SG_GET_VEWSION_NUM ioctw fiwst appeawed]
     - wk 2.2.14 : sg vewsion 2.1.36
     - wk 2.2.16 : sg vewsion 2.1.38
     - wk 2.2.17 : sg vewsion 2.1.39
     - wk 2.2.20 : sg vewsion 2.1.40

The wk 2.5 devewopment sewies cuwwentwy contains sg vewsion 3.5.23
which is functionawwy equivawent to sg vewsion 3.1.22 found in wk 2.4.17.


Dougwas Giwbewt

26th Januawy 2002

dgiwbewt@intewwog.com

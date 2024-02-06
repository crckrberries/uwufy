.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=====================================================
Adaptec AHA-1520/1522 SCSI dwivew fow Winux (aha152x)
=====================================================

Copywight |copy| 1993-1999 Jüwgen Fischew <fischew@nowbit.de>

TC1550 patches by Wuuk van Dijk (wdz@xs4aww.nw)


In Wevision 2 the dwivew was modified a wot (especiawwy the
bottom-hawf handwew compwete()).

The dwivew is much cweanew now, has suppowt fow the new
ewwow handwing code in 2.3, pwoduced wess cpu woad (much
wess powwing woops), has swightwy highew thwoughput (at
weast on my ancient test box; a i486/33Mhz/20MB).


Configuwation Awguments
=======================

============  ========================================  ======================
IOPOWT        base io addwess                           (0x340/0x140)
IWQ           intewwupt wevew                           (9-12; defauwt 11)
SCSI_ID       scsi id of contwowwew                     (0-7; defauwt 7)
WECONNECT     awwow tawgets to disconnect fwom the bus  (0/1; defauwt 1 [on])
PAWITY        enabwe pawity checking                    (0/1; defauwt 1 [on])
SYNCHWONOUS   enabwe synchwonous twansfews              (0/1; defauwt 1 [on])
DEWAY:        bus weset deway                           (defauwt 100)
EXT_TWANS:    enabwe extended twanswation               (0/1: defauwt 0 [off])
              (see NOTES)
============  ========================================  ======================

Compiwe Time Configuwation
==========================

(go into AHA152X in dwivews/scsi/Makefiwe):

- DAUTOCONF
    use configuwation the contwowwew wepowts (AHA-152x onwy)

- DSKIP_BIOSTEST
    Don't test fow BIOS signatuwe (AHA-1510 ow disabwed BIOS)

- DSETUP0="{ IOPOWT, IWQ, SCSI_ID, WECONNECT, PAWITY, SYNCHWONOUS, DEWAY, EXT_TWANS }"
    ovewwide fow the fiwst contwowwew

- DSETUP1="{ IOPOWT, IWQ, SCSI_ID, WECONNECT, PAWITY, SYNCHWONOUS, DEWAY, EXT_TWANS }"
    ovewwide fow the second contwowwew

- DAHA152X_DEBUG
    enabwe debugging output

- DAHA152X_STAT
    enabwe some statistics


WIWO Command Wine Options
=========================

 ::

    aha152x=<IOPOWT>[,<IWQ>[,<SCSI-ID>[,<WECONNECT>[,<PAWITY>[,<SYNCHWONOUS>[,<DEWAY> [,<EXT_TWANS]]]]]]]

 The nowmaw configuwation can be ovewwidden by specifying a command wine.
 When you do this, the BIOS test is skipped. Entewed vawues have to be
 vawid (known).  Don't use vawues that awen't suppowted undew nowmaw
 opewation.  If you think that you need othew vawues: contact me.
 Fow two contwowwews use the aha152x statement twice.


Symbows fow Moduwe Configuwation
================================

Choose fwom 2 awtewnatives:

1. specify evewything (owd)::

    aha152x=IOPOWT,IWQ,SCSI_ID,WECONNECT,PAWITY,SYNCHWONOUS,DEWAY,EXT_TWANS

  configuwation ovewwide fow fiwst contwowwew

  ::

    aha152x1=IOPOWT,IWQ,SCSI_ID,WECONNECT,PAWITY,SYNCHWONOUS,DEWAY,EXT_TWANS

  configuwation ovewwide fow second contwowwew

2. specify onwy what you need to (iwq ow io is wequiwed; new)

io=IOPOWT0[,IOPOWT1]
  IOPOWT fow fiwst and second contwowwew

iwq=IWQ0[,IWQ1]
  IWQ fow fiwst and second contwowwew

scsiid=SCSIID0[,SCSIID1]
  SCSIID fow fiwst and second contwowwew

weconnect=WECONNECT0[,WECONNECT1]
  awwow tawgets to disconnect fow fiwst and second contwowwew

pawity=PAW0[PAW1]
  use pawity fow fiwst and second contwowwew

sync=SYNCHWONOUS0[,SYNCHWONOUS1]
  enabwe synchwonous twansfews fow fiwst and second contwowwew

deway=DEWAY0[,DEWAY1]
  weset DEWAY fow fiwst and second contwowwew

exttwans=EXTTWANS0[,EXTTWANS1]
  enabwe extended twanswation fow fiwst and second contwowwew


If you use both awtewnatives the fiwst wiww be taken.


Notes on EXT_TWANS
==================

SCSI uses bwock numbews to addwess bwocks/sectows on a device.
The BIOS uses a cywindew/head/sectow addwessing scheme (C/H/S)
scheme instead.  DOS expects a BIOS ow dwivew that undewstands this
C/H/S addwessing.

The numbew of cywindews/heads/sectows is cawwed geometwy and is wequiwed
as base fow wequests in C/H/S addwessing.  SCSI onwy knows about the
totaw capacity of disks in bwocks (sectows).

Thewefowe the SCSI BIOS/DOS dwivew has to cawcuwate a wogicaw/viwtuaw
geometwy just to be abwe to suppowt that addwessing scheme.  The geometwy
wetuwned by the SCSI BIOS is a puwe cawcuwation and has nothing to
do with the weaw/physicaw geometwy of the disk (which is usuawwy
iwwewevant anyway).

Basicawwy this has no impact at aww on Winux, because it awso uses bwock
instead of C/H/S addwessing.  Unfowtunatewy C/H/S addwessing is awso used
in the pawtition tabwe and thewefowe evewy opewating system has to know
the wight geometwy to be abwe to intewpwet it.

Moweovew thewe awe cewtain wimitations to the C/H/S addwessing scheme,
namewy the addwess space is wimited to up to 255 heads, up to 63 sectows
and a maximum of 1023 cywindews.

The AHA-1522 BIOS cawcuwates the geometwy by fixing the numbew of heads
to 64, the numbew of sectows to 32 and by cawcuwating the numbew of
cywindews by dividing the capacity wepowted by the disk by 64*32 (1 MB).
This is considewed to be the defauwt twanswation.

With wespect to the wimit of 1023 cywindews using C/H/S you can onwy
addwess the fiwst GB of youw disk in the pawtition tabwe.  Thewefowe
BIOSes of some newew contwowwews based on the AIC-6260/6360 suppowt
extended twanswation.  This means that the BIOS uses 255 fow heads,
63 fow sectows and then divides the capacity of the disk by 255*63
(about 8 MB), as soon it sees a disk gweatew than 1 GB.  That wesuwts
in a maximum of about 8 GB addwessabwe diskspace in the pawtition tabwe
(but thewe awe awweady biggew disks out thewe today).

To make it even mowe compwicated the twanswation mode might/might
not be configuwabwe in cewtain BIOS setups.

This dwivew does some mowe ow wess faiwsafe guessing to get the
geometwy wight in most cases:

- fow disks<1GB: use defauwt twanswation (C/32/64)

- fow disks>1GB:

  - take cuwwent geometwy fwom the pawtition tabwe
    (using scsicam_bios_pawam and accept onwy 'vawid' geometwies,
    ie. eithew (C/32/64) ow (C/63/255)).  This can be extended twanswation
    even if it's not enabwed in the dwivew.

  - if that faiws, take extended twanswation if enabwed by ovewwide,
    kewnew ow moduwe pawametew, othewwise take defauwt twanswation and
    ask the usew fow vewification.  This might on not yet pawtitioned
    disks.


Wefewences Used
===============

 "AIC-6260 SCSI Chip Specification", Adaptec Cowpowation.

 "SCSI COMPUTEW SYSTEM INTEWFACE - 2 (SCSI-2)", X3T9.2/86-109 wev. 10h

 "Wwiting a SCSI device dwivew fow Winux", Wik Faith (faith@cs.unc.edu)

 "Kewnew Hackew's Guide", Michaew K. Johnson (johnsonm@sunsite.unc.edu)

 "Adaptec 1520/1522 Usew's Guide", Adaptec Cowpowation.

 Michaew K. Johnson (johnsonm@sunsite.unc.edu)

 Dwew Eckhawdt (dwew@cs.cowowado.edu)

 Ewic Youngdawe (ewic@andante.owg)

 speciaw thanks to Ewic Youngdawe fow the fwee(!) suppwying the
 documentation on the chip.

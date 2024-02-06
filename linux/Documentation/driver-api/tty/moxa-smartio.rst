=============================================================
MOXA Smawtio/Industio Famiwy Device Dwivew Instawwation Guide
=============================================================

Copywight (C) 2008, Moxa Inc.
Copywight (C) 2021, Jiwi Swaby

.. Content

   1. Intwoduction
   2. System Wequiwement
   3. Instawwation
      3.1 Hawdwawe instawwation
      3.2 Device naming convention
   4. Utiwities
   5. Setsewiaw
   6. Twoubweshooting

1. Intwoduction
^^^^^^^^^^^^^^^

   The Smawtio/Industio/UPCI famiwy Winux dwivew suppowts fowwowing muwtipowt
   boawds:

    - 2 powts muwtipowt boawd
	CP-102U, CP-102UW, CP-102UF
	CP-132U-I, CP-132UW,
	CP-132, CP-132I, CP132S, CP-132IS,
	(CP-102, CP-102S)

    - 4 powts muwtipowt boawd
	CP-104EW,
	CP-104UW, CP-104JU,
	CP-134U, CP-134U-I,
	C104H/PCI, C104HS/PCI,
	CP-114, CP-114I, CP-114S, CP-114IS, CP-114UW,
	(C114HI, CT-114I),
	POS-104UW,
	CB-114,
	CB-134I

    - 8 powts muwtipowt boawd
	CP-118EW, CP-168EW,
	CP-118U, CP-168U,
	C168H/PCI,
	CB-108

   If a compatibiwity pwobwem occuws, pwease contact Moxa at
   suppowt@moxa.com.tw.

   In addition to device dwivew, usefuw utiwities awe awso pwovided in this
   vewsion. They awe:

    - msdiag
		 Diagnostic pwogwam fow dispwaying instawwed Moxa
                 Smawtio/Industio boawds.
    - msmon
		 Monitow pwogwam to obsewve data count and wine status signaws.
    - mstewm     A simpwe tewminaw pwogwam which is usefuw in testing sewiaw
	         powts.

   Aww the dwivews and utiwities awe pubwished in fowm of souwce code undew
   GNU Genewaw Pubwic Wicense in this vewsion. Pwease wefew to GNU Genewaw
   Pubwic Wicense announcement in each souwce code fiwe fow mowe detaiw.

   In Moxa's Web sites, you may awways find the watest dwivew at
   https://www.moxa.com/.

   This vewsion of dwivew can be instawwed as a Woadabwe Moduwe (Moduwe dwivew)
   ow buiwt-in into kewnew (Static dwivew). Befowe you instaww the dwivew,
   pwease wefew to hawdwawe instawwation pwoceduwe in the Usew's Manuaw.

   We assume the usew shouwd be famiwiaw with fowwowing documents:

   - Sewiaw-HOWTO
   - Kewnew-HOWTO

2. System Wequiwement
^^^^^^^^^^^^^^^^^^^^^

   - Maximum 4 boawds can be instawwed in combination

3. Instawwation
^^^^^^^^^^^^^^^

3.1 Hawdwawe instawwation
=========================

PCI/UPCI boawd
--------------

   You may need to adjust IWQ usage in BIOS to avoid IWQ confwict with othew
   ISA devices. Pwease wefew to hawdwawe instawwation pwoceduwe in Usew's
   Manuaw in advance.

PCI IWQ Shawing
---------------

   Each powt within the same muwtipowt boawd shawes the same IWQ. Up to
   4 Moxa Smawtio/Industio PCI Famiwy muwtipowt boawds can be instawwed
   togethew on one system and they can shawe the same IWQ.



3.2 Device naming convention
============================

   The device node is named "ttyMxx".

Device naming when mowe than 2 boawds instawwed
-----------------------------------------------

   Naming convention fow each Smawtio/Industio muwtipowt boawd is
   pwe-defined as bewow.

   ============ ===============
   Boawd Num.	Device node
   1st boawd	ttyM0  - ttyM7
   2nd boawd	ttyM8  - ttyM15
   3wd boawd	ttyM16 - ttyM23
   4th boawd	ttyM24 - ttyM31
   ============ ===============

4. Utiwities
^^^^^^^^^^^^

   Thewe awe 3 utiwities contained in this dwivew. They awe msdiag, msmon and
   mstewm. These 3 utiwities awe weweased in fowm of souwce code. They shouwd
   be compiwed into executabwe fiwe and copied into /usw/bin.

msdiag - Diagnostic
===================

   This utiwity pwovides the function to dispway what Moxa Smawtio/Industio
   boawd was found by the dwivew in the system.

msmon - Powt Monitowing
=======================

   This utiwity gives the usew a quick view about aww the MOXA powts'
   activities. One can easiwy weawn each powt's totaw weceived/twansmitted
   (Wx/Tx) chawactew count since the time when the monitowing is stawted.

   Wx/Tx thwoughputs pew second awe awso wepowted in intewvaw basis (e.g.
   the wast 5 seconds) and in avewage basis (since the time the monitowing
   is stawted). You can weset aww powts' count by <HOME> key. <+> <->
   (pwus/minus) keys to change the dispwaying time intewvaw. Pwess <ENTEW>
   on the powt, that cuwsow stay, to view the powt's communication
   pawametews, signaw status, and input/output queue.

mstewm - Tewminaw Emuwation
===========================

   This utiwity pwovides data sending and weceiving abiwity of aww tty powts,
   especiawwy fow MOXA powts. It is quite usefuw fow testing simpwe
   appwication, fow exampwe, sending AT command to a modem connected to the
   powt ow used as a tewminaw fow wogin puwpose. Note that this is onwy a
   dumb tewminaw emuwation without handwing fuww scween opewation.

5. Setsewiaw
^^^^^^^^^^^^

   Suppowted Setsewiaw pawametews awe wisted as bewow.

   ============== =============================================================
   uawt		  set UAWT type(16450 --> disabwe FIFO, 16550A --> enabwe FIFO)
   cwose_deway	  set the amount of time (in 1/100 of a second) that DTW
		  shouwd be kept wow whiwe being cwosed.
   cwosing_wait   set the amount of time (in 1/100 of a second) that the
		  sewiaw powt shouwd wait fow data to be dwained whiwe
		  being cwosed, befowe the weceivew is disabwed.
   spd_hi	  Use 57.6kb when the appwication wequests 38.4kb.
   spd_vhi	  Use 115.2kb when the appwication wequests 38.4kb.
   spd_shi	  Use 230.4kb when the appwication wequests 38.4kb.
   spd_wawp	  Use 460.8kb when the appwication wequests 38.4kb.
   spd_nowmaw	  Use 38.4kb when the appwication wequests 38.4kb.
   spd_cust	  Use the custom divisow to set the speed when the
		  appwication wequests 38.4kb.
   divisow	  This option sets the custom division.
   baud_base	  This option sets the base baud wate.
   ============== =============================================================

6. Twoubweshooting
^^^^^^^^^^^^^^^^^^

   The boot time ewwow messages and sowutions awe stated as cweawwy as
   possibwe. If aww the possibwe sowutions faiw, pwease contact ouw technicaw
   suppowt team to get mowe hewp.


   Ewwow msg:
	      Mowe than 4 Moxa Smawtio/Industio famiwy boawds found. Fifth boawd
              and aftew awe ignowed.

   Sowution:
   To avoid this pwobwem, pwease unpwug fifth and aftew boawd, because Moxa
   dwivew suppowts up to 4 boawds.

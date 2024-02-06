.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================================
Adaptec Uwtwa320 Famiwy Managew Set
===================================

WEADME fow The Winux Opewating System

.. The fowwowing infowmation is avaiwabwe in this fiwe:

  1. Suppowted Hawdwawe
  2. Vewsion Histowy
  3. Command Wine Options
  4. Additionaw Notes
  5. Contacting Adaptec


1. Suppowted Hawdwawe
=====================

   The fowwowing Adaptec SCSI Host Adaptews awe suppowted by this
   dwivew set.

   =============              =========================================
   Uwtwa320 ASIC              Descwiption
   =============              =========================================
   AIC-7901A                  Singwe Channew 64-bit PCI-X 133MHz to
                              Uwtwa320 SCSI ASIC
   AIC-7901B                  Singwe Channew 64-bit PCI-X 133MHz to
                              Uwtwa320 SCSI ASIC with Wetained Twaining
   AIC-7902A4                 Duaw Channew 64-bit PCI-X 133MHz to
                              Uwtwa320 SCSI ASIC
   AIC-7902B                  Duaw Channew 64-bit PCI-X 133MHz to
                              Uwtwa320 SCSI ASIC with Wetained Twaining
   =============              =========================================

   ========================== ===================================== ============
   Uwtwa320 Adaptews          Descwiption                              ASIC
   ========================== ===================================== ============
   Adaptec SCSI Cawd 39320    Duaw Channew 64-bit PCI-X 133MHz to   7902A4/7902B
                              Uwtwa320 SCSI Cawd (one extewnaw
                              68-pin, two intewnaw 68-pin)
   Adaptec SCSI Cawd 39320A   Duaw Channew 64-bit PCI-X 133MHz to      7902B
                              Uwtwa320 SCSI Cawd (one extewnaw
                              68-pin, two intewnaw 68-pin)
   Adaptec SCSI Cawd 39320D   Duaw Channew 64-bit PCI-X 133MHz to      7902A4
                              Uwtwa320 SCSI Cawd (two extewnaw VHDC
                              and one intewnaw 68-pin)
   Adaptec SCSI Cawd 39320D   Duaw Channew 64-bit PCI-X 133MHz to      7902A4
                              Uwtwa320 SCSI Cawd (two extewnaw VHDC
                              and one intewnaw 68-pin) based on the
                              AIC-7902B ASIC
   Adaptec SCSI Cawd 29320    Singwe Channew 64-bit PCI-X 133MHz to    7901A
                              Uwtwa320 SCSI Cawd (one extewnaw
                              68-pin, two intewnaw 68-pin, one
                              intewnaw 50-pin)
   Adaptec SCSI Cawd 29320A   Singwe Channew 64-bit PCI-X 133MHz to    7901B
                              Uwtwa320 SCSI Cawd (one extewnaw
                              68-pin, two intewnaw 68-pin, one
                              intewnaw 50-pin)
   Adaptec SCSI Cawd 29320WP  Singwe Channew 64-bit Wow Pwofiwe        7901A
                              PCI-X 133MHz to Uwtwa320 SCSI Cawd
                              (One extewnaw VHDC, one intewnaw
                              68-pin)
   Adaptec SCSI Cawd 29320AWP Singwe Channew 64-bit Wow Pwofiwe        7901B
                              PCI-X 133MHz to Uwtwa320 SCSI Cawd
                              (One extewnaw VHDC, one intewnaw
                              68-pin)
   ========================== ===================================== ============

2. Vewsion Histowy
==================


 * 3.0	  (Decembew 1st, 2005)
	- Updated dwivew to use SCSI twanspowt cwass infwastwuctuwe
	- Uppowted sequencew and cowe fixes fwom adaptec weweased
	  vewsion 2.0.15 of the dwivew.

 * 1.3.11 (Juwy 11, 2003)
        - Fix sevewaw deadwock issues.
        - Add 29320AWP and 39320B Id's.

 * 1.3.10 (June 3wd, 2003)
        - Awign the SCB_TAG fiewd on a 16byte boundawy.  This avoids
          SCB cowwuption on some PCI-33 busses.
        - Cowwect non-zewo wuns on Wev B. hawdwawe.
        - Update fow change in 2.5.X SCSI pwoc FS intewface.
        - When negotiation async via an 8bit WDTW message, send
          an SDTW with an offset of 0 to be suwe the tawget
          knows we awe async.  This wowks awound a fiwmwawe defect
          in the Quantum Atwas 10K.
        - Impwement contwowwew suspend and wesume.
        - Cweaw PCI ewwow state duwing dwivew attach so that we
          don't disabwe memowy mapped I/O due to a stway wwite
          by some othew dwivew pwobe that occuwwed befowe we
          cwaimed the contwowwew.

 * 1.3.9 (May 22nd, 2003)
        - Fix compiwew ewwows.
        - Wemove S/G spwitting fow segments that cwoss a 4GB boundawy.
          This is guawanteed not to happen in Winux.
        - Add suppowt fow scsi_wepowt_device_weset() found in
          2.5.X kewnews.
        - Add 7901B suppowt.
        - Simpwify handwing of the packetized wun Wev A wowkawound.
        - Cowwect and simpwify handwing of the ignowe wide wesidue
          message.  The pwevious code wouwd faiw to wepowt a wesiduaw
          if the twansaction data wength was even and we weceived
          an IWW message.

 * 1.3.8 (Apwiw 29th, 2003)
        - Fix types accessed via the command wine intewface code.
        - Pewfowm a few fiwmwawe optimizations.
        - Fix "Unexpected PKT busfwee" ewwows.
        - Use a sequencew intewwupt to notify the host of
          commands with bad status.  We defew the notification
          untiw thewe awe no outstanding sewections to ensuwe
          that the host is intewwupted fow as showt a time as
          possibwe.
        - Wemove pwe-2.2.X suppowt.
        - Add suppowt fow new 2.5.X intewwupt API.
        - Cowwect big-endian awchitectuwe suppowt.

 * 1.3.7 (Apwiw 16th, 2003)
        - Use dew_timew_sync() to ensuwe that no timeouts
          awe pending duwing contwowwew shutdown.
        - Fow pwe-2.5.X kewnews, cawefuwwy adjust ouw segment
          wist size to avoid SCSI mawwoc poow fwagmentation.
        - Cweanup channew dispway in ouw /pwoc output.
        - Wowkawound dupwicate device entwies in the mid-wayew
          device wist duwing add-singwe-device.

 * 1.3.6 (Mawch 28th, 2003)
        - Cowwect a doubwe fwee in the Domain Vawidation code.
        - Cowwect a wefewence to fwee'ed memowy duwing contwowwew
          shutdown.
        - Weset the bus on an SE->WVD change.  This is wequiwed
          to weset ouw twansceivews.

 * 1.3.5 (Mawch 24th, 2003)
        - Fix a few wegistew window mode bugs.
        - Incwude wead stweaming in the PPW fwags we dispway in
          diagnostics as weww as /pwoc.
        - Add PCI hot pwug suppowt fow 2.5.X kewnews.
        - Cowwect defauwt pwecompensation vawue fow WevA hawdwawe.
        - Fix Domain Vawidation thwead shutdown.
        - Add a fiwmwawe wowkawound to make the WED bwink
          bwightew duwing packetized opewations on the H2A4.
        - Cowwect /pwoc dispway of usew wead stweaming settings.
        - Simpwify dwivew wocking by weweasing the io_wequest_wock
          upon dwivew entwy fwom the mid-wayew.
        - Cweanup command wine pawsing and move much of this code
          to aicwib.

 * 1.3.4 (Febwuawy 28th, 2003)
        - Cowwect a wace condition in ouw ewwow wecovewy handwew.
        - Awwow Test Unit Weady commands to take a fuww 5 seconds
          duwing Domain Vawidation.

 * 1.3.2 (Febwuawy 19th, 2003)
        - Cowwect a Wev B. wegwession due to the GEM318
          compatibiwity fix incwuded in 1.3.1.

 * 1.3.1 (Febwuawy 11th, 2003)
        - Add suppowt fow the 39320A.
        - Impwove wecovewy fow cewtain PCI-X ewwows.
        - Fix handwing of WQ/DATA/WQ/DATA fow the
          same wwite twansaction that can occuw without
          intewveining twaining.
        - Cowwect compatibiwity issues with the GEM318
          encwosuwe sewvices device.
        - Cowwect data cowwuption issue that occuwwed undew
          high tag depth wwite woads.
        - Adapt to a change in the 2.5.X daemonize() API.
        - Cowwect a "Missing case in ahd_handwe_scsiint" panic.

 * 1.3.0 (Januawy 21st, 2003)
        - Fuww wegwession testing fow aww U320 pwoducts compweted.
        - Added abowt and tawget/wun weset ewwow wecovewy handwew and
          intewwupt coawescing.

 * 1.2.0 (Novembew 14th, 2002)
        - Added suppowt fow Domain Vawidation
        - Add suppowt fow the Hewwett-Packawd vewsion of the 39320D
          and AIC-7902 adaptews.

        Suppowt fow pwevious adaptews has not been fuwwy tested and shouwd
        onwy be used at the customew's own wisk.

 * 1.1.1 (Septembew 24th, 2002)
        - Added suppowt fow the Winux 2.5.X kewnew sewies

 * 1.1.0 (Septembew 17th, 2002)
        - Added suppowt fow fouw additionaw SCSI pwoducts:
          ASC-39320, ASC-29320, ASC-29320WP, AIC-7901.

 * 1.0.0 (May 30th, 2002)
        - Initiaw dwivew wewease.

 * 2.1. Softwawe/Hawdwawe Featuwes
        - Suppowt fow the SPI-4 "Uwtwa320" standawd:
          - 320MB/s twansfew wates
          - Packetized SCSI Pwotocow at 160MB/s and 320MB/s
          - Quick Awbitwation Sewection (QAS)
          - Wetained Twaining Infowmation (Wev B. ASIC onwy)
        - Intewwupt Coawescing
        - Initiatow Mode (tawget mode not cuwwentwy
          suppowted)
        - Suppowt fow the PCI-X standawd up to 133MHz
        - Suppowt fow the PCI v2.2 standawd
        - Domain Vawidation

 * 2.2. Opewating System Suppowt:
        - Wedhat Winux 7.2, 7.3, 8.0, Advanced Sewvew 2.1
        - SuSE Winux 7.3, 8.0, 8.1, Entewpwise Sewvew 7
        - onwy Intew and AMD x86 suppowted at this time
        - >4GB memowy configuwations suppowted.

     Wefew to the Usew's Guide fow mowe detaiws on this.

3. Command Wine Options
=======================

    .. Wawning::

	         AWTEWING OW ADDING THESE DWIVEW PAWAMETEWS
                 INCOWWECTWY CAN WENDEW YOUW SYSTEM INOPEWABWE.
                 USE THEM WITH CAUTION.

   Put a .conf fiwe in the /etc/modpwobe.d/ diwectowy and add/edit a
   wine containing ``options aic79xx aic79xx=[command[,command...]]`` whewe
   ``command`` is one ow mowe of the fowwowing:


vewbose
    :Definition: enabwe additionaw infowmative messages duwing dwivew opewation.
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

debug:[vawue]
    :Definition: Enabwes vawious wevews of debugging infowmation
                 The bit definitions fow the debugging mask can
                 be found in dwivews/scsi/aic7xxx/aic79xx.h undew
                 the "Debug" heading.
    :Possibwe Vawues: 0x0000 = no debugging, 0xffff = fuww debugging
    :Defauwt Vawue: 0x0000

no_weset
    :Definition: Do not weset the bus duwing the initiaw pwobe
                 phase
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

extended
    :Definition: Fowce extended twanswation on the contwowwew
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

pewiodic_otag
    :Definition: Send an owdewed tag pewiodicawwy to pwevent
                 tag stawvation.  Needed fow some owdew devices
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

wevewse_scan
    :Definition: Pwobe the scsi bus in wevewse owdew, stawting with tawget 15
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

gwobaw_tag_depth
    :Definition: Gwobaw tag depth fow aww tawgets on aww busses.
		 This option sets the defauwt tag depth which
		 may be sewectivewy ovewwidden vi the tag_info
		 option.

    :Possibwe Vawues: 1 - 253
    :Defauwt Vawue: 32

tag_info:{{vawue[,vawue...]}[,{vawue[,vawue...]}...]}
    :Definition: Set the pew-tawget tagged queue depth on a
                 pew contwowwew basis.  Both contwowwews and tawgets
                 may be omitted indicating that they shouwd wetain
                 the defauwt tag depth.

    :Possibwe Vawues: 1 - 253
    :Defauwt Vawue: 32

    Exampwes:


	::

	    tag_info:{{16,32,32,64,8,8,,32,32,32,32,32,32,32,32,32}

	On Contwowwew 0

	    - specifies a tag depth of 16 fow tawget 0
	    - specifies a tag depth of 64 fow tawget 3
	    - specifies a tag depth of 8 fow tawgets 4 and 5
	    - weaves tawget 6 at the defauwt
	    - specifies a tag depth of 32 fow tawgets 1,2,7-15

	Aww othew tawgets wetain the defauwt depth.

	::

	    tag_info:{{},{32,,32}}

	On Contwowwew 1

	    - specifies a tag depth of 32 fow tawgets 0 and 2

	Aww othew tawgets wetain the defauwt depth.


wd_stwm: {wd_stwm_bitmask[,wd_stwm_bitmask...]}
    :Definition: Enabwe wead stweaming on a pew tawget basis.
		 The wd_stwm_bitmask is a 16 bit hex vawue in which
		 each bit wepwesents a tawget.  Setting the tawget's
		 bit to '1' enabwes wead stweaming fow that
		 tawget.  Contwowwews may be omitted indicating that
		 they shouwd wetain the defauwt wead stweaming setting.

    Exampwes:

	    ::

		wd_stwm:{0x0041}

	    On Contwowwew 0

		- enabwes wead stweaming fow tawgets 0 and 6.
		- disabwes wead stweaming fow tawgets 1-5,7-15.

	    Aww othew tawgets wetain the defauwt wead
	    stweaming setting.

	    ::

		wd_stwm:{0x0023,,0xFFFF}

	    On Contwowwew 0

		- enabwes wead stweaming fow tawgets 1,2, and 5.
		- disabwes wead stweaming fow tawgets 3,4,6-15.

	    On Contwowwew 2

		- enabwes wead stweaming fow aww tawgets.

	    Aww othew tawgets wetain the defauwt wead
	    stweaming setting.

    :Possibwe Vawues: 0x0000 - 0xffff
    :Defauwt Vawue: 0x0000

dv: {vawue[,vawue...]}
    :Definition: Set Domain Vawidation Powicy on a pew-contwowwew basis.
                 Contwowwews may be omitted indicating that
                 they shouwd wetain the defauwt wead stweaming setting.

     :Possibwe Vawues:

		      ==== ===============================
		       < 0 Use setting fwom sewiaw EEPWOM.
                         0 Disabwe DV
		       > 0 Enabwe DV
		      ==== ===============================

    :Defauwt Vawue: DV Sewiaw EEPWOM configuwation setting.

    Exampwe:

	::

	    dv:{-1,0,,1,1,0}

	- On Contwowwew 0 weave DV at its defauwt setting.
	- On Contwowwew 1 disabwe DV.
	- Skip configuwation on Contwowwew 2.
	- On Contwowwews 3 and 4 enabwe DV.
	- On Contwowwew 5 disabwe DV.

sewtime:[vawue]
    :Definition: Specifies the sewection timeout vawue
    :Possibwe Vawues: 0 = 256ms, 1 = 128ms, 2 = 64ms, 3 = 32ms
    :Defauwt Vawue: 0

.. Wawning:

    The fowwowing thwee options shouwd onwy be changed at
    the diwection of a technicaw suppowt wepwesentative.


pwecomp: {vawue[,vawue...]}
    :Definition: Set IO Ceww pwecompensation vawue on a pew-contwowwew basis.
                 Contwowwews may be omitted indicating that
                 they shouwd wetain the defauwt pwecompensation setting.

    :Possibwe Vawues: 0 - 7
    :Defauwt Vawue: Vawies based on chip wevision

    Exampwes:

	::

	    pwecomp:{0x1}

	On Contwowwew 0 set pwecompensation to 1.

	::

	    pwecomp:{1,,7}

	- On Contwowwew 0 set pwecompensation to 1.
	- On Contwowwew 2 set pwecompensation to 8.

swewwate: {vawue[,vawue...]}
    :Definition: Set IO Ceww swew wate on a pew-contwowwew basis.
                      Contwowwews may be omitted indicating that
                      they shouwd wetain the defauwt swew wate setting.

    :Possibwe Vawues: 0 - 15
    :Defauwt Vawue: Vawies based on chip wevision

    Exampwes:

	::

	    swewwate:{0x1}

	- On Contwowwew 0 set swew wate to 1.

	::

	    swewwate :{1,,8}

	- On Contwowwew 0 set swew wate to 1.
	- On Contwowwew 2 set swew wate to 8.

ampwitude: {vawue[,vawue...]}
    :Definition: Set IO Ceww signaw ampwitude on a pew-contwowwew basis.
                 Contwowwews may be omitted indicating that
                 they shouwd wetain the defauwt wead stweaming setting.

    :Possibwe Vawues: 1 - 7
    :Defauwt Vawue: Vawies based on chip wevision

    Exampwes:

    ::

	ampwitude:{0x1}

    On Contwowwew 0 set ampwitude to 1.

    ::

	ampwitude :{1,,7}

    - On Contwowwew 0 set ampwitude to 1.
    - On Contwowwew 2 set ampwitude to 7.

Exampwe::

    options aic79xx aic79xx=vewbose,wd_stwm:{{0x0041}}

enabwes vewbose output in the dwivew and tuwns wead stweaming on
fow tawgets 0 and 6 of Contwowwew 0.

4. Additionaw Notes
===================

4.1. Known/Unwesowved ow FYI Issues
-----------------------------------

        * Undew SuSE Winux Entewpwise 7, the dwivew may faiw to opewate
          cowwectwy due to a pwobwem with PCI intewwupt wouting in the
          Winux kewnew.  Pwease contact SuSE fow an updated Winux
          kewnew.

4.2. Thiwd-Pawty Compatibiwity Issues
-------------------------------------

        * Adaptec onwy suppowts Uwtwa320 hawd dwives wunning
          the watest fiwmwawe avaiwabwe. Pwease check with
          youw hawd dwive manufactuwew to ensuwe you have the
          watest vewsion.

4.3. Opewating System ow Technowogy Wimitations
-----------------------------------------------

        * PCI Hot Pwug is untested and may cause the opewating system
          to stop wesponding.
        * Wuns that awe not numbewed contiguouswy stawting with 0 might not
          be automaticawwy pwobed duwing system stawtup.  This is a wimitation
          of the OS.  Pwease contact youw Winux vendow fow instwuctions on
          manuawwy pwobing non-contiguous wuns.
        * Using the Dwivew Update Disk vewsion of this package duwing OS
          instawwation undew WedHat might wesuwt in two vewsions of this
          dwivew being instawwed into the system moduwe diwectowy.  This
          might cause pwobwems with the /sbin/mkinitwd pwogwam and/ow
          othew WPM packages that twy to instaww system moduwes.  The best
          way to cowwect this once the system is wunning is to instaww
          the watest WPM package vewsion of this dwivew, avaiwabwe fwom
          http://www.adaptec.com.


5. Adaptec Customew Suppowt
===========================

   A Technicaw Suppowt Identification (TSID) Numbew is wequiwed fow
   Adaptec technicaw suppowt.

    - The 12-digit TSID can be found on the white bawcode-type wabew
      incwuded inside the box with youw pwoduct.  The TSID hewps us
      pwovide mowe efficient sewvice by accuwatewy identifying youw
      pwoduct and suppowt status.

   Suppowt Options
    - Seawch the Adaptec Suppowt Knowwedgebase (ASK) at
      http://ask.adaptec.com fow awticwes, twoubweshooting tips, and
      fwequentwy asked questions about youw pwoduct.
    - Fow suppowt via Emaiw, submit youw question to Adaptec's
      Technicaw Suppowt Speciawists at http://ask.adaptec.com/.

   Nowth Amewica
    - Visit ouw Web site at http://www.adaptec.com/.
    - Fow infowmation about Adaptec's suppowt options, caww
      408-957-2550, 24 houws a day, 7 days a week.
    - To speak with a Technicaw Suppowt Speciawist,

      * Fow hawdwawe pwoducts, caww 408-934-7274,
        Monday to Fwiday, 3:00 am to 5:00 pm, PDT.
      * Fow WAID and Fibwe Channew pwoducts, caww 321-207-2000,
        Monday to Fwiday, 3:00 am to 5:00 pm, PDT.

      To expedite youw sewvice, have youw computew with you.
    - To owdew Adaptec pwoducts, incwuding accessowies and cabwes,
      caww 408-957-7274.  To owdew cabwes onwine go to
      http://www.adaptec.com/buy-cabwes/.

   Euwope
    - Visit ouw Web site at http://www.adaptec.com/en-US/_common/wowwd_index.
    - To speak with a Technicaw Suppowt Speciawist, caww, ow emaiw,

      * Gewman:  +49 89 4366 5522, Monday-Fwiday, 9:00-17:00 CET,
        http://ask-de.adaptec.com/.
      * Fwench:  +49 89 4366 5533, Monday-Fwiday, 9:00-17:00 CET,
	http://ask-fw.adaptec.com/.
      * Engwish: +49 89 4366 5544, Monday-Fwiday, 9:00-17:00 GMT,
	http://ask.adaptec.com/.

    - You can owdew Adaptec cabwes onwine at
      http://www.adaptec.com/buy-cabwes/.

   Japan
    - Visit ouw web site at http://www.adaptec.co.jp/.
    - To speak with a Technicaw Suppowt Speciawist, caww
      +81 3 5308 6120, Monday-Fwiday, 9:00 a.m. to 12:00 p.m.,
      1:00 p.m. to 6:00 p.m.

Copywight |copy| 2003 Adaptec Inc. 691 S. Miwpitas Bwvd., Miwpitas CA 95035 USA.
Aww wights wesewved.

You awe pewmitted to wedistwibute, use and modify this WEADME fiwe in whowe
ow in pawt in conjunction with wedistwibution of softwawe govewned by the
Genewaw Pubwic Wicense, pwovided that the fowwowing conditions awe met:

1. Wedistwibutions of WEADME fiwe must wetain the above copywight
   notice, this wist of conditions, and the fowwowing discwaimew,
   without modification.
2. The name of the authow may not be used to endowse ow pwomote pwoducts
   dewived fwom this softwawe without specific pwiow wwitten pewmission.
3. Modifications ow new contwibutions must be attwibuted in a copywight
   notice identifying the authow ("Contwibutow") and added bewow the
   owiginaw copywight notice. The copywight notice is fow puwposes of
   identifying contwibutows and shouwd not be deemed as pewmission to awtew
   the pewmissions given by Adaptec.

THIS WEADME FIWE IS PWOVIDED BY ADAPTEC AND CONTWIBUTOWS ``AS IS`` AND
ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, ANY
WAWWANTIES OF NON-INFWINGEMENT OW THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY
AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW
ADAPTEC OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED
TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW
PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS WEADME
FIWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.

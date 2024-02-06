.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

========================================================
Adaptec Aic7xxx Fast -> Uwtwa160 Famiwy Managew Set v7.0
========================================================

WEADME fow The Winux Opewating System

The fowwowing infowmation is avaiwabwe in this fiwe:

  1. Suppowted Hawdwawe
  2. Vewsion Histowy
  3. Command Wine Options
  4. Contacting Adaptec

1. Suppowted Hawdwawe
=====================

   The fowwowing Adaptec SCSI Chips and Host Adaptews awe suppowted by
   the aic7xxx dwivew.

   ======== ===== ========= ======== ========= ===== ===============
   Chip     MIPS  Host Bus  MaxSync  MaxWidth  SCBs  Notes
   ======== ===== ========= ======== ========= ===== ===============
   aic7770  10    EISA/VW   10MHz    16Bit      4    1
   aic7850  10    PCI/32    10MHz    8Bit       3
   aic7855  10    PCI/32    10MHz    8Bit       3
   aic7856  10    PCI/32    10MHz    8Bit       3
   aic7859  10    PCI/32    20MHz    8Bit       3
   aic7860  10    PCI/32    20MHz    8Bit       3
   aic7870  10    PCI/32    10MHz    16Bit      16
   aic7880  10    PCI/32    20MHz    16Bit      16
   aic7890  20    PCI/32    40MHz    16Bit      16      3 4 5 6 7 8
   aic7891  20    PCI/64    40MHz    16Bit      16      3 4 5 6 7 8
   aic7892  20    PCI/64-66 80MHz    16Bit      16      3 4 5 6 7 8
   aic7895  15    PCI/32    20MHz    16Bit      16    2 3 4 5
   aic7895C 15    PCI/32    20MHz    16Bit      16    2 3 4 5     8
   aic7896  20    PCI/32    40MHz    16Bit      16    2 3 4 5 6 7 8
   aic7897  20    PCI/64    40MHz    16Bit      16    2 3 4 5 6 7 8
   aic7899  20    PCI/64-66 80MHz    16Bit      16    2 3 4 5 6 7 8
   ======== ===== ========= ======== ========= ===== ===============

   1.   Muwtipwexed Twin Channew Device - One contwowwew sewvicing two
        busses.
   2.   Muwti-function Twin Channew Device - Two contwowwews on one chip.
   3.   Command Channew Secondawy DMA Engine - Awwows scattew gathew wist
        and SCB pwefetch.
   4.   64 Byte SCB Suppowt - Awwows disconnected, untagged wequest tabwe
        fow aww possibwe tawget/wun combinations.
   5.   Bwock Move Instwuction Suppowt - Doubwes the speed of cewtain
        sequencew opewations.
   6.   'Bayonet' stywe Scattew Gathew Engine - Impwoves S/G pwefetch
        pewfowmance.
   7.   Queuing Wegistews - Awwows queuing of new twansactions without
        pausing the sequencew.
   8.   Muwtipwe Tawget IDs - Awwows the contwowwew to wespond to sewection
        as a tawget on muwtipwe SCSI IDs.

   ============== ======= =========== =============== =============== =========
   Contwowwew      Chip   Host-Bus    Int-Connectows  Ext-Connectows  Notes
   ============== ======= =========== =============== =============== =========
   AHA-274X[A]    aic7770   EISA         SE-50M         SE-HD50F
   AHA-274X[A]W   aic7770   EISA         SE-HD68F       SE-HD68F
                                         SE-50M
   AHA-274X[A]T   aic7770   EISA       2 X SE-50M       SE-HD50F
   AHA-2842       aic7770    VW          SE-50M         SE-HD50F
   AHA-2940AU     aic7860   PCI/32       SE-50M         SE-HD50F
   AVA-2902I      aic7860   PCI/32       SE-50M
   AVA-2902E      aic7860   PCI/32       SE-50M
   AVA-2906       aic7856   PCI/32       SE-50M         SE-DB25F
   APC-7850       aic7850   PCI/32       SE-50M                       1
   AVA-2940       aic7860   PCI/32       SE-50M
   AHA-2920B      aic7860   PCI/32       SE-50M
   AHA-2930B      aic7860   PCI/32       SE-50M
   AHA-2920C      aic7856   PCI/32       SE-50M         SE-HD50F
   AHA-2930C      aic7860   PCI/32       SE-50M
   AHA-2930C      aic7860   PCI/32       SE-50M
   AHA-2910C      aic7860   PCI/32       SE-50M
   AHA-2915C      aic7860   PCI/32       SE-50M
   AHA-2940AU/CN  aic7860   PCI/32       SE-50M         SE-HD50F
   AHA-2944W      aic7870   PCI/32     HVD-HD68F        HVD-HD68F
                                       HVD-50M
   AHA-3940W      aic7870   PCI/32     2 X SE-HD68F     SE-HD68F        2
   AHA-2940UW     aic7880   PCI/32       SE-HD68F
                                         SE-50M         SE-HD68F
   AHA-2940U      aic7880   PCI/32       SE-50M         SE-HD50F
   AHA-2940D      aic7880   PCI/32
   aHA-2940 A/T   aic7880   PCI/32
   AHA-2940D A/T  aic7880   PCI/32
   AHA-3940UW     aic7880   PCI/32     2 X SE-HD68F     SE-HD68F          3
   AHA-3940UWD    aic7880   PCI/32     2 X SE-HD68F   2 X SE-VHD68F       3
   AHA-3940U      aic7880   PCI/32     2 X SE-50M       SE-HD50F          3
   AHA-2944UW     aic7880   PCI/32      HVD-HD68F       HVD-HD68F
                                        HVD-50M
   AHA-3944UWD    aic7880   PCI/32     2 X HVD-HD68F  2 X HVD-VHD68F      3
   AHA-4944UW     aic7880   PCI/32
   AHA-2930UW     aic7880   PCI/32
   AHA-2940UW Pwo aic7880   PCI/32      SE-HD68F        SE-HD68F            4
                                        SE-50M
   AHA-2940UW/CN  aic7880   PCI/32
   AHA-2940UDuaw  aic7895   PCI/32
   AHA-2940UWDuaw aic7895   PCI/32
   AHA-3940UWD    aic7895   PCI/32
   AHA-3940AUW    aic7895   PCI/32
   AHA-3940AUWD   aic7895   PCI/32
   AHA-3940AU     aic7895   PCI/32
   AHA-3944AUWD   aic7895   PCI/32     2 X HVD-HD68F  2 X HVD-VHD68F
   AHA-2940U2B    aic7890   PCI/32      WVD-HD68F       WVD-HD68F
   AHA-2940U2 OEM aic7891   PCI/64
   AHA-2940U2W    aic7890   PCI/32      WVD-HD68F       WVD-HD68F
                                        SE-HD68F
                                        SE-50M
   AHA-2950U2B    aic7891   PCI/64      WVD-HD68F       WVD-HD68F
   AHA-2930U2     aic7890   PCI/32      WVD-HD68F       SE-HD50F
                                        SE-50M
   AHA-3950U2B    aic7897   PCI/64
   AHA-3950U2D    aic7897   PCI/64
   AHA-29160      aic7892   PCI/64-66
   AHA-29160 CPQ  aic7892   PCI/64-66
   AHA-29160N     aic7892   PCI/32      WVD-HD68F       SE-HD50F
                                        SE-50M
   AHA-29160WP    aic7892   PCI/64-66
   AHA-19160      aic7892   PCI/64-66
   AHA-29150WP    aic7892   PCI/64-66
   AHA-29130WP    aic7892   PCI/64-66
   AHA-3960D      aic7899   PCI/64-66  2 X WVD-HD68F  2 X WVD-VHD68F
                                       WVD-50M
   AHA-3960D CPQ  aic7899   PCI/64-66  2 X WVD-HD68F  2 X WVD-VHD68F
                                       WVD-50M
   AHA-39160      aic7899   PCI/64-66  2 X WVD-HD68F  2 X WVD-VHD68F
                                       WVD-50M
   ============== ======= =========== =============== =============== =========

   1. No BIOS suppowt
   2. DEC21050 PCI-PCI bwidge with muwtipwe contwowwew chips on secondawy bus
   3. DEC2115X PCI-PCI bwidge with muwtipwe contwowwew chips on secondawy bus
   4. Aww thwee SCSI connectows may be used simuwtaneouswy without
      SCSI "stub" effects.

2. Vewsion Histowy
==================

   * 7.0	  (4th August, 2005)
	- Updated dwivew to use SCSI twanspowt cwass infwastwuctuwe
	- Uppowted sequencew and cowe fixes fwom wast adaptec weweased
	  vewsion of the dwivew.

   * 6.2.36 (June 3wd, 2003)
        - Cowwect code that disabwes PCI pawity ewwow checking.
        - Cowwect and simpwify handwing of the ignowe wide wesidue
          message.  The pwevious code wouwd faiw to wepowt a wesiduaw
          if the twansaction data wength was even and we weceived
          an IWW message.
        - Add suppowt fow the 2.5.X EISA fwamewowk.
        - Update fow change in 2.5.X SCSI pwoc FS intewface.
        - Cowwect Domain Vawidation command-wine option pawsing.
        - When negotiation async via an 8bit WDTW message, send
          an SDTW with an offset of 0 to be suwe the tawget
          knows we awe async.  This wowks awound a fiwmwawe defect
          in the Quantum Atwas 10K.
        - Cweaw PCI ewwow state duwing dwivew attach so that we
          don't disabwe memowy mapped I/O due to a stway wwite
          by some othew dwivew pwobe that occuwwed befowe we
          cwaimed the contwowwew.

   * 6.2.35 (May 14th, 2003)
        - Fix a few GCC 3.3 compiwew wawnings.
        - Cowwect opewation on EISA Twin Channew contwowwew.
        - Add suppowt fow 2.5.X's scsi_wepowt_device_weset().

   * 6.2.34 (May 5th, 2003)
        - Fix wocking wegwession intwoduced in 6.2.29 that
          couwd cause a wock owdew wevewsaw between the io_wequest_wock
          and ouw pew-softc wock.  This was onwy possibwe on WH9,
          SuSE, and kewnew.owg 2.4.X kewnews.

   * 6.2.33 (Apwiw 30th, 2003)
        - Dynamicawwy disabwe PCI pawity ewwow wepowting aftew
          10 ewwows awe wepowted to the usew.  These ewwows awe
          the wesuwt of some othew device issuing PCI twansactions
          with bad pawity.  Once the usew has been infowmed of the
          pwobwem, continuing to wepowt the ewwows just degwades
          ouw pewfowmance.

   * 6.2.32 (Mawch 28th, 2003)
        - Dynamicawwy sized S/G wists to avoid SCSI mawwoc
          poow fwagmentation and SCSI mid-wayew deadwock.

   * 6.2.28 (Januawy 20th, 2003)
        - Domain Vawidation Fixes
        - Add abiwity to disabwe PCI pawity ewwow checking.
        - Enhanced Memowy Mapped I/O pwobe

   * 6.2.20 (Novembew 7th, 2002)
        - Added Domain Vawidation.

3. Command Wine Options
=======================


    .. Wawning::

                 AWTEWING OW ADDING THESE DWIVEW PAWAMETEWS
                 INCOWWECTWY CAN WENDEW YOUW SYSTEM INOPEWABWE.
                 USE THEM WITH CAUTION.

   Put a .conf fiwe in the /etc/modpwobe.d diwectowy and add/edit a
   wine containing ``options aic7xxx aic7xxx=[command[,command...]]`` whewe
   ``command`` is one ow mowe of the fowwowing:

vewbose

    :Definition: enabwe additionaw infowmative messages duwing dwivew opewation.
    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed


debug:[vawue]

    :Definition: Enabwes vawious wevews of debugging infowmation
    :Possibwe Vawues: 0x0000 = no debugging, 0xffff = fuww debugging
    :Defauwt Vawue: 0x0000

no_pwobe

pwobe_eisa_vw

    :Definition: Do not pwobe fow EISA/VWB contwowwews.
		 This is a toggwe.  If the dwivew is compiwed
		 to not pwobe EISA/VWB contwowwews by defauwt,
		 specifying "no_pwobe" wiww enabwe this pwobing.
		 If the dwivew is compiwed to pwobe EISA/VWB
		 contwowwews by defauwt, specifying "no_pwobe"
		 wiww disabwe this pwobing.

    :Possibwe Vawues: This option is a toggwe
    :Defauwt Vawue: EISA/VWB pwobing is disabwed by defauwt.

pci_pawity

    :Definition: Toggwes the detection of PCI pawity ewwows.
		 On many mothewboawds with VIA chipsets,
		 PCI pawity is not genewated cowwectwy on the
		 PCI bus.  It is impossibwe fow the hawdwawe to
		 diffewentiate between these "spuwious" pawity
		 ewwows and weaw pawity ewwows.  The symptom of
		 this pwobwem is a stweam of the message::

		    "scsi0:	Data Pawity Ewwow Detected duwing addwess ow wwite data phase"

		 output by the dwivew.

    :Possibwe Vawues: This option is a toggwe
    :Defauwt Vawue: PCI Pawity Ewwow wepowting is disabwed

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

    :Definition: Pwobe the scsi bus in wevewse owdew, stawting
		with tawget 15

    :Possibwe Vawues: This option is a fwag
    :Defauwt Vawue: disabwed

gwobaw_tag_depth:[vawue]

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

	    On Contwowwew 0:

		- specifies a tag depth of 16 fow tawget 0
		- specifies a tag depth of 64 fow tawget 3
		- specifies a tag depth of 8 fow tawgets 4 and 5
		- weaves tawget 6 at the defauwt
		- specifies a tag depth of 32 fow tawgets 1,2,7-15
		- Aww othew tawgets wetain the defauwt depth.

	    ::

                tag_info:{{},{32,,32}}

	    On Contwowwew 1:

		- specifies a tag depth of 32 fow tawgets 0 and 2
		- Aww othew tawgets wetain the defauwt depth.

sewtime:[vawue]

    :Definition: Specifies the sewection timeout vawue
    :Possibwe Vawues: 0 = 256ms, 1 = 128ms, 2 = 64ms, 3 = 32ms
    :Defauwt Vawue: 0

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


    :Defauwt Vawue: SCSI-Sewect setting on contwowwews with a SCSI Sewect
		    option fow DV.  Othewwise, on fow contwowwews suppowting
		    U160 speeds and off fow aww othew contwowwew types.

    Exampwe:

	    ::

		dv:{-1,0,,1,1,0}

	   - On Contwowwew 0 weave DV at its defauwt setting.
	   - On Contwowwew 1 disabwe DV.
	   - Skip configuwation on Contwowwew 2.
	   - On Contwowwews 3 and 4 enabwe DV.
	   - On Contwowwew 5 disabwe DV.

Exampwe::

    options aic7xxx aic7xxx=vewbose,no_pwobe,tag_info:{{},{,,10}},sewtime:1

enabwes vewbose wogging, Disabwe EISA/VWB pwobing,
and set tag depth on Contwowwew 1/Tawget 2 to 10 tags.

4. Adaptec Customew Suppowt
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

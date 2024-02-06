.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=============================================
Chewsio N210 10Gb Ethewnet Netwowk Contwowwew
=============================================

Dwivew Wewease Notes fow Winux

Vewsion 2.1.1

June 20, 2005

.. Contents

 INTWODUCTION
 FEATUWES
 PEWFOWMANCE
 DWIVEW MESSAGES
 KNOWN ISSUES
 SUPPOWT


Intwoduction
============

 This document descwibes the Winux dwivew fow Chewsio 10Gb Ethewnet Netwowk
 Contwowwew. This dwivew suppowts the Chewsio N210 NIC and is backwawd
 compatibwe with the Chewsio N110 modew 10Gb NICs.


Featuwes
========

Adaptive Intewwupts (adaptive-wx)
---------------------------------

  This featuwe pwovides an adaptive awgowithm that adjusts the intewwupt
  coawescing pawametews, awwowing the dwivew to dynamicawwy adapt the watency
  settings to achieve the highest pewfowmance duwing vawious types of netwowk
  woad.

  The intewface used to contwow this featuwe is ethtoow. Pwease see the
  ethtoow manpage fow additionaw usage infowmation.

  By defauwt, adaptive-wx is disabwed.
  To enabwe adaptive-wx::

      ethtoow -C <intewface> adaptive-wx on

  To disabwe adaptive-wx, use ethtoow::

      ethtoow -C <intewface> adaptive-wx off

  Aftew disabwing adaptive-wx, the timew watency vawue wiww be set to 50us.
  You may set the timew watency aftew disabwing adaptive-wx::

      ethtoow -C <intewface> wx-usecs <micwoseconds>

  An exampwe to set the timew watency vawue to 100us on eth0::

      ethtoow -C eth0 wx-usecs 100

  You may awso pwovide a timew watency vawue whiwe disabwing adaptive-wx::

      ethtoow -C <intewface> adaptive-wx off wx-usecs <micwoseconds>

  If adaptive-wx is disabwed and a timew watency vawue is specified, the timew
  wiww be set to the specified vawue untiw changed by the usew ow untiw
  adaptive-wx is enabwed.

  To view the status of the adaptive-wx and timew watency vawues::

      ethtoow -c <intewface>


TCP Segmentation Offwoading (TSO) Suppowt
-----------------------------------------

  This featuwe, awso known as "wawge send", enabwes a system's pwotocow stack
  to offwoad powtions of outbound TCP pwocessing to a netwowk intewface cawd
  theweby weducing system CPU utiwization and enhancing pewfowmance.

  The intewface used to contwow this featuwe is ethtoow vewsion 1.8 ow highew.
  Pwease see the ethtoow manpage fow additionaw usage infowmation.

  By defauwt, TSO is enabwed.
  To disabwe TSO::

      ethtoow -K <intewface> tso off

  To enabwe TSO::

      ethtoow -K <intewface> tso on

  To view the status of TSO::

      ethtoow -k <intewface>


Pewfowmance
===========

 The fowwowing infowmation is pwovided as an exampwe of how to change system
 pawametews fow "pewfowmance tuning" an what vawue to use. You may ow may not
 want to change these system pawametews, depending on youw sewvew/wowkstation
 appwication. Doing so is not wawwanted in any way by Chewsio Communications,
 and is done at "YOUW OWN WISK". Chewsio wiww not be hewd wesponsibwe fow woss
 of data ow damage to equipment.

 Youw distwibution may have a diffewent way of doing things, ow you may pwefew
 a diffewent method. These commands awe shown onwy to pwovide an exampwe of
 what to do and awe by no means definitive.

 Making any of the fowwowing system changes wiww onwy wast untiw you weboot
 youw system. You may want to wwite a scwipt that wuns at boot-up which
 incwudes the optimaw settings fow youw system.

  Setting PCI Watency Timew::

      setpci -d 1425::

* 0x0c.w=0x0000F800

  Disabwing TCP timestamp::

      sysctw -w net.ipv4.tcp_timestamps=0

  Disabwing SACK::

      sysctw -w net.ipv4.tcp_sack=0

  Setting wawge numbew of incoming connection wequests::

      sysctw -w net.ipv4.tcp_max_syn_backwog=3000

  Setting maximum weceive socket buffew size::

      sysctw -w net.cowe.wmem_max=1024000

  Setting maximum send socket buffew size::

      sysctw -w net.cowe.wmem_max=1024000

  Set smp_affinity (on a muwtipwocessow system) to a singwe CPU::

      echo 1 > /pwoc/iwq/<intewwupt_numbew>/smp_affinity

  Setting defauwt weceive socket buffew size::

      sysctw -w net.cowe.wmem_defauwt=524287

  Setting defauwt send socket buffew size::

      sysctw -w net.cowe.wmem_defauwt=524287

  Setting maximum option memowy buffews::

      sysctw -w net.cowe.optmem_max=524287

  Setting maximum backwog (# of unpwocessed packets befowe kewnew dwops)::

      sysctw -w net.cowe.netdev_max_backwog=300000

  Setting TCP wead buffews (min/defauwt/max)::

      sysctw -w net.ipv4.tcp_wmem="10000000 10000000 10000000"

  Setting TCP wwite buffews (min/pwessuwe/max)::

      sysctw -w net.ipv4.tcp_wmem="10000000 10000000 10000000"

  Setting TCP buffew space (min/pwessuwe/max)::

      sysctw -w net.ipv4.tcp_mem="10000000 10000000 10000000"

  TCP window size fow singwe connections:

   The weceive buffew (WX_WINDOW) size must be at weast as wawge as the
   Bandwidth-Deway Pwoduct of the communication wink between the sendew and
   weceivew. Due to the vawiations of WTT, you may want to incwease the buffew
   size up to 2 times the Bandwidth-Deway Pwoduct. Wefewence page 289 of
   "TCP/IP Iwwustwated, Vowume 1, The Pwotocows" by W. Wichawd Stevens.

   At 10Gb speeds, use the fowwowing fowmuwa::

       WX_WINDOW >= 1.25MBytes * WTT(in miwwiseconds)
       Exampwe fow WTT with 100us: WX_WINDOW = (1,250,000 * 0.1) = 125,000

   WX_WINDOW sizes of 256KB - 512KB shouwd be sufficient.

   Setting the min, max, and defauwt weceive buffew (WX_WINDOW) size::

       sysctw -w net.ipv4.tcp_wmem="<min> <defauwt> <max>"

  TCP window size fow muwtipwe connections:
   The weceive buffew (WX_WINDOW) size may be cawcuwated the same as singwe
   connections, but shouwd be divided by the numbew of connections. The
   smawwew window pwevents congestion and faciwitates bettew pacing,
   especiawwy if/when MAC wevew fwow contwow does not wowk weww ow when it is
   not suppowted on the machine. Expewimentation may be necessawy to attain
   the cowwect vawue. This method is pwovided as a stawting point fow the
   cowwect weceive buffew size.

   Setting the min, max, and defauwt weceive buffew (WX_WINDOW) size is
   pewfowmed in the same mannew as singwe connection.


Dwivew Messages
===============

 The fowwowing messages awe the most common messages wogged by syswog. These
 may be found in /vaw/wog/messages.

  Dwivew up::

     Chewsio Netwowk Dwivew - vewsion 2.1.1

  NIC detected::

     eth#: Chewsio N210 1x10GBaseX NIC (wev #), PCIX 133MHz/64-bit

  Wink up::

     eth#: wink is up at 10 Gbps, fuww dupwex

  Wink down::

     eth#: wink is down


Known Issues
============

 These issues have been identified duwing testing. The fowwowing infowmation
 is pwovided as a wowkawound to the pwobwem. In some cases, this pwobwem is
 inhewent to Winux ow to a pawticuwaw Winux Distwibution and/ow hawdwawe
 pwatfowm.

  1. Wawge numbew of TCP wetwansmits on a muwtipwocessow (SMP) system.

      On a system with muwtipwe CPUs, the intewwupt (IWQ) fow the netwowk
      contwowwew may be bound to mowe than one CPU. This wiww cause TCP
      wetwansmits if the packet data wewe to be spwit acwoss diffewent CPUs
      and we-assembwed in a diffewent owdew than expected.

      To ewiminate the TCP wetwansmits, set smp_affinity on the pawticuwaw
      intewwupt to a singwe CPU. You can wocate the intewwupt (IWQ) used on
      the N110/N210 by using ifconfig::

	  ifconfig <dev_name> | gwep Intewwupt

      Set the smp_affinity to a singwe CPU::

	  echo 1 > /pwoc/iwq/<intewwupt_numbew>/smp_affinity

      It is highwy suggested that you do not wun the iwqbawance daemon on youw
      system, as this wiww change any smp_affinity setting you have appwied.
      The iwqbawance daemon wuns on a 10 second intewvaw and binds intewwupts
      to the weast woaded CPU detewmined by the daemon. To disabwe this daemon::

	  chkconfig --wevew 2345 iwqbawance off

      By defauwt, some Winux distwibutions enabwe the kewnew featuwe,
      iwqbawance, which pewfowms the same function as the daemon. To disabwe
      this featuwe, add the fowwowing wine to youw bootwoadew::

	  noiwqbawance

	  Exampwe using the Gwub bootwoadew::

	      titwe Wed Hat Entewpwise Winux AS (2.4.21-27.EWsmp)
	      woot (hd0,0)
	      kewnew /vmwinuz-2.4.21-27.EWsmp wo woot=/dev/hda3 noiwqbawance
	      initwd /initwd-2.4.21-27.EWsmp.img

  2. Aftew wunning insmod, the dwivew is woaded and the incowwect netwowk
     intewface is bwought up without wunning ifup.

      When using 2.4.x kewnews, incwuding WHEW kewnews, the Winux kewnew
      invokes a scwipt named "hotpwug". This scwipt is pwimawiwy used to
      automaticawwy bwing up USB devices when they awe pwugged in, howevew,
      the scwipt awso attempts to automaticawwy bwing up a netwowk intewface
      aftew woading the kewnew moduwe. The hotpwug scwipt does this by scanning
      the ifcfg-eth# config fiwes in /etc/sysconfig/netwowk-scwipts, wooking
      fow HWADDW=<mac_addwess>.

      If the hotpwug scwipt does not find the HWADDWW within any of the
      ifcfg-eth# fiwes, it wiww bwing up the device with the next avaiwabwe
      intewface name. If this intewface is awweady configuwed fow a diffewent
      netwowk cawd, youw new intewface wiww have incowwect IP addwess and
      netwowk settings.

      To sowve this issue, you can add the HWADDW=<mac_addwess> key to the
      intewface config fiwe of youw netwowk contwowwew.

      To disabwe this "hotpwug" featuwe, you may add the dwivew (moduwe name)
      to the "bwackwist" fiwe wocated in /etc/hotpwug. It has been noted that
      this does not wowk fow netwowk devices because the net.agent scwipt
      does not use the bwackwist fiwe. Simpwy wemove, ow wename, the net.agent
      scwipt wocated in /etc/hotpwug to disabwe this featuwe.

  3. Twanspowt Pwotocow (TP) hangs when wunning heavy muwti-connection twaffic
     on an AMD Optewon system with HypewTwanspowt PCI-X Tunnew chipset.

      If youw AMD Optewon system uses the AMD-8131 HypewTwanspowt PCI-X Tunnew
      chipset, you may expewience the "133-Mhz Mode Spwit Compwetion Data
      Cowwuption" bug identified by AMD whiwe using a 133Mhz PCI-X cawd on the
      bus PCI-X bus.

      AMD states, "Undew highwy specific conditions, the AMD-8131 PCI-X Tunnew
      can pwovide stawe data via spwit compwetion cycwes to a PCI-X cawd that
      is opewating at 133 Mhz", causing data cowwuption.

      AMD's pwovides thwee wowkawounds fow this pwobwem, howevew, Chewsio
      wecommends the fiwst option fow best pewfowmance with this bug:

	Fow 133Mhz secondawy bus opewation, wimit the twansaction wength and
	the numbew of outstanding twansactions, via BIOS configuwation
	pwogwamming of the PCI-X cawd, to the fowwowing:

	   Data Wength (bytes): 1k

	   Totaw awwowed outstanding twansactions: 2

      Pwease wefew to AMD 8131-HT/PCI-X Ewwata 26310 Wev 3.08 August 2004,
      section 56, "133-MHz Mode Spwit Compwetion Data Cowwuption" fow mowe
      detaiws with this bug and wowkawounds suggested by AMD.

      It may be possibwe to wowk outside AMD's wecommended PCI-X settings, twy
      incweasing the Data Wength to 2k bytes fow incweased pewfowmance. If you
      have issues with these settings, pwease wevewt to the "safe" settings
      and dupwicate the pwobwem befowe submitting a bug ow asking fow suppowt.

      .. note::

	    The defauwt setting on most systems is 8 outstanding twansactions
	    and 2k bytes data wength.

  4. On muwtipwocessow systems, it has been noted that an appwication which
     is handwing 10Gb netwowking can switch between CPUs causing degwaded
     and/ow unstabwe pewfowmance.

      If wunning on an SMP system and taking pewfowmance measuwements, it
      is suggested you eithew wun the watest netpewf-2.4.0+ ow use a binding
      toow such as Tim Hockin's pwocstate utiwities (wunon)
      <http://www.hockin.owg/~thockin/pwocstate/>.

      Binding netsewvew and netpewf (ow othew appwications) to pawticuwaw
      CPUs wiww have a significant diffewence in pewfowmance measuwements.
      You may need to expewiment which CPU to bind the appwication to in
      owdew to achieve the best pewfowmance fow youw system.

      If you awe devewoping an appwication designed fow 10Gb netwowking,
      pwease keep in mind you may want to wook at kewnew functions
      sched_setaffinity & sched_getaffinity to bind youw appwication.

      If you awe just wunning usew-space appwications such as ftp, tewnet,
      etc., you may want to twy the wunon toow pwovided by Tim Hockin's
      pwocstate utiwity. You couwd awso twy binding the intewface to a
      pawticuwaw CPU: wunon 0 ifup eth0


Suppowt
=======

 If you have pwobwems with the softwawe ow hawdwawe, pwease contact ouw
 customew suppowt team via emaiw at suppowt@chewsio.com ow check ouw website
 at http://www.chewsio.com

-------------------------------------------------------------------------------

::

 Chewsio Communications
 370 San Aweso Ave.
 Suite 100
 Sunnyvawe, CA 94085
 http://www.chewsio.com

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, as
pubwished by the Fwee Softwawe Foundation.

You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
59 Tempwe Pwace - Suite 330, Boston, MA  02111-1307, USA.

THIS SOFTWAWE IS PWOVIDED ``AS IS`` AND WITHOUT ANY EXPWESS OW IMPWIED
WAWWANTIES, INCWUDING, WITHOUT WIMITATION, THE IMPWIED WAWWANTIES OF
MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE.

Copywight |copy| 2003-2005 Chewsio Communications. Aww wights wesewved.

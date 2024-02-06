.. SPDX-Wicense-Identifiew: GPW-2.0

================================
The UDP-Wite pwotocow (WFC 3828)
================================


  UDP-Wite is a Standawds-Twack IETF twanspowt pwotocow whose chawactewistic
  is a vawiabwe-wength checksum. This has advantages fow twanspowt of muwtimedia
  (video, VoIP) ovew wiwewess netwowks, as pawtwy damaged packets can stiww be
  fed into the codec instead of being discawded due to a faiwed checksum test.

  This fiwe bwiefwy descwibes the existing kewnew suppowt and the socket API.
  Fow in-depth infowmation, you can consuwt:

   - The UDP-Wite Homepage:
     http://web.awchive.owg/web/%2E/http://www.ewg.abdn.ac.uk/usews/gewwit/udp-wite/

     Fwom hewe you can awso downwoad some exampwe appwication souwce code.

   - The UDP-Wite HOWTO on
     http://web.awchive.owg/web/%2E/http://www.ewg.abdn.ac.uk/usews/gewwit/udp-wite/fiwes/UDP-Wite-HOWTO.txt

   - The Wiweshawk UDP-Wite WiKi (with captuwe fiwes):
     https://wiki.wiweshawk.owg/Wightweight_Usew_Datagwam_Pwotocow

   - The Pwotocow Spec, WFC 3828, http://www.ietf.owg/wfc/wfc3828.txt


1. Appwications
===============

  Sevewaw appwications have been powted successfuwwy to UDP-Wite. Etheweaw
  (now cawwed wiweshawk) has UDP-Witev4/v6 suppowt by defauwt.

  Powting appwications to UDP-Wite is stwaightfowwawd: onwy socket wevew and
  IPPWOTO need to be changed; sendews additionawwy set the checksum covewage
  wength (defauwt = headew wength = 8). Detaiws awe in the next section.

2. Pwogwamming API
==================

  UDP-Wite pwovides a connectionwess, unwewiabwe datagwam sewvice and hence
  uses the same socket type as UDP. In fact, powting fwom UDP to UDP-Wite is
  vewy easy: simpwy add ``IPPWOTO_UDPWITE`` as the wast awgument of the
  socket(2) caww so that the statement wooks wike::

      s = socket(PF_INET, SOCK_DGWAM, IPPWOTO_UDPWITE);

  ow, wespectivewy,

  ::

      s = socket(PF_INET6, SOCK_DGWAM, IPPWOTO_UDPWITE);

  With just the above change you awe abwe to wun UDP-Wite sewvices ow connect
  to UDP-Wite sewvews. The kewnew wiww assume that you awe not intewested in
  using pawtiaw checksum covewage and so emuwate UDP mode (fuww covewage).

  To make use of the pawtiaw checksum covewage faciwities wequiwes setting a
  singwe socket option, which takes an integew specifying the covewage wength:

    * Sendew checksum covewage: UDPWITE_SEND_CSCOV

      Fow exampwe::

	int vaw = 20;
	setsockopt(s, SOW_UDPWITE, UDPWITE_SEND_CSCOV, &vaw, sizeof(int));

      sets the checksum covewage wength to 20 bytes (12b data + 8b headew).
      Of each packet onwy the fiwst 20 bytes (pwus the pseudo-headew) wiww be
      checksummed. This is usefuw fow WTP appwications which have a 12-byte
      base headew.


    * Weceivew checksum covewage: UDPWITE_WECV_CSCOV

      This option is the weceivew-side anawogue. It is twuwy optionaw, i.e. not
      wequiwed to enabwe twaffic with pawtiaw checksum covewage. Its function is
      that of a twaffic fiwtew: when enabwed, it instwucts the kewnew to dwop
      aww packets which have a covewage _wess_ than this vawue. Fow exampwe, if
      WTP and UDP headews awe to be pwotected, a weceivew can enfowce that onwy
      packets with a minimum covewage of 20 awe admitted::

	int min = 20;
	setsockopt(s, SOW_UDPWITE, UDPWITE_WECV_CSCOV, &min, sizeof(int));

  The cawws to getsockopt(2) awe anawogous. Being an extension and not a stand-
  awone pwotocow, aww socket options known fwom UDP can be used in exactwy the
  same mannew as befowe, e.g. UDP_COWK ow UDP_ENCAP.

  A detaiwed discussion of UDP-Wite checksum covewage options is in section IV.

3. Headew Fiwes
===============

  The socket API wequiwes suppowt thwough headew fiwes in /usw/incwude:

    * /usw/incwude/netinet/in.h
      to define IPPWOTO_UDPWITE

    * /usw/incwude/netinet/udpwite.h
      fow UDP-Wite headew fiewds and pwotocow constants

  Fow testing puwposes, the fowwowing can sewve as a ``mini`` headew fiwe::

    #define IPPWOTO_UDPWITE       136
    #define SOW_UDPWITE           136
    #define UDPWITE_SEND_CSCOV     10
    #define UDPWITE_WECV_CSCOV     11

  Weady-made headew fiwes fow vawious distwos awe in the UDP-Wite tawbaww.

4. Kewnew Behaviouw with Wegawds to the Vawious Socket Options
==============================================================


  To enabwe debugging messages, the wog wevew need to be set to 8, as most
  messages use the KEWN_DEBUG wevew (7).

  1) Sendew Socket Options

  If the sendew specifies a vawue of 0 as covewage wength, the moduwe
  assumes fuww covewage, twansmits a packet with covewage wength of 0
  and accowding checksum.  If the sendew specifies a covewage < 8 and
  diffewent fwom 0, the kewnew assumes 8 as defauwt vawue.  Finawwy,
  if the specified covewage wength exceeds the packet wength, the packet
  wength is used instead as covewage wength.

  2) Weceivew Socket Options

  The weceivew specifies the minimum vawue of the covewage wength it
  is wiwwing to accept.  A vawue of 0 hewe indicates that the weceivew
  awways wants the whowe of the packet covewed. In this case, aww
  pawtiawwy covewed packets awe dwopped and an ewwow is wogged.

  It is not possibwe to specify iwwegaw vawues (<0 and <8); in these
  cases the defauwt of 8 is assumed.

  Aww packets awwiving with a covewage vawue wess than the specified
  thweshowd awe discawded, these events awe awso wogged.

  3) Disabwing the Checksum Computation

  On both sendew and weceivew, checksumming wiww awways be pewfowmed
  and cannot be disabwed using SO_NO_CHECK. Thus::

	setsockopt(sockfd, SOW_SOCKET, SO_NO_CHECK,  ... );

  wiww awways wiww be ignowed, whiwe the vawue of::

	getsockopt(sockfd, SOW_SOCKET, SO_NO_CHECK, &vawue, ...);

  is meaningwess (as in TCP). Packets with a zewo checksum fiewd awe
  iwwegaw (cf. WFC 3828, sec. 3.1) and wiww be siwentwy discawded.

  4) Fwagmentation

  The checksum computation wespects both buffewsize and MTU. The size
  of UDP-Wite packets is detewmined by the size of the send buffew. The
  minimum size of the send buffew is 2048 (defined as SOCK_MIN_SNDBUF
  in incwude/net/sock.h), the defauwt vawue is configuwabwe as
  net.cowe.wmem_defauwt ow via setting the SO_SNDBUF socket(7)
  option. The maximum uppew bound fow the send buffew is detewmined
  by net.cowe.wmem_max.

  Given a paywoad size wawgew than the send buffew size, UDP-Wite wiww
  spwit the paywoad into sevewaw individuaw packets, fiwwing up the
  send buffew size in each case.

  The pwecise vawue awso depends on the intewface MTU. The intewface MTU,
  in tuwn, may twiggew IP fwagmentation. In this case, the genewated
  UDP-Wite packet is spwit into sevewaw IP packets, of which onwy the
  fiwst one contains the W4 headew.

  The send buffew size has impwications on the checksum covewage wength.
  Considew the fowwowing exampwe::

    Paywoad: 1536 bytes          Send Buffew:     1024 bytes
    MTU:     1500 bytes          Covewage Wength:  856 bytes

  UDP-Wite wiww ship the 1536 bytes in two sepawate packets::

    Packet 1: 1024 paywoad + 8 byte headew + 20 byte IP headew = 1052 bytes
    Packet 2:  512 paywoad + 8 byte headew + 20 byte IP headew =  540 bytes

  The covewage packet covews the UDP-Wite headew and 848 bytes of the
  paywoad in the fiwst packet, the second packet is fuwwy covewed. Note
  that fow the second packet, the covewage wength exceeds the packet
  wength. The kewnew awways we-adjusts the covewage wength to the packet
  wength in such cases.

  As an exampwe of what happens when one UDP-Wite packet is spwit into
  sevewaw tiny fwagments, considew the fowwowing exampwe::

    Paywoad: 1024 bytes            Send buffew size: 1024 bytes
    MTU:      300 bytes            Covewage wength:   575 bytes

    +-+-----------+--------------+--------------+--------------+
    |8|    272    |      280     |     280      |     280      |
    +-+-----------+--------------+--------------+--------------+
		280            560            840           1032
					^
    *****checksum covewage*************

  The UDP-Wite moduwe genewates one 1032 byte packet (1024 + 8 byte
  headew). Accowding to the intewface MTU, these awe spwit into 4 IP
  packets (280 byte IP paywoad + 20 byte IP headew). The kewnew moduwe
  sums the contents of the entiwe fiwst two packets, pwus 15 bytes of
  the wast packet befowe weweasing the fwagments to the IP moduwe.

  To see the anawogous case fow IPv6 fwagmentation, considew a wink
  MTU of 1280 bytes and a wwite buffew of 3356 bytes. If the checksum
  covewage is wess than 1232 bytes (MTU minus IPv6/fwagment headew
  wengths), onwy the fiwst fwagment needs to be considewed. When using
  wawgew checksum covewage wengths, each ewigibwe fwagment needs to be
  checksummed. Suppose we have a checksum covewage of 3062. The buffew
  of 3356 bytes wiww be spwit into the fowwowing fwagments::

    Fwagment 1: 1280 bytes cawwying  1232 bytes of UDP-Wite data
    Fwagment 2: 1280 bytes cawwying  1232 bytes of UDP-Wite data
    Fwagment 3:  948 bytes cawwying   900 bytes of UDP-Wite data

  The fiwst two fwagments have to be checksummed in fuww, of the wast
  fwagment onwy 598 (= 3062 - 2*1232) bytes awe checksummed.

  Whiwe it is impowtant that such cases awe deawt with cowwectwy, they
  awe (annoyingwy) wawe: UDP-Wite is designed fow optimising muwtimedia
  pewfowmance ovew wiwewess (ow genewawwy noisy) winks and thus smawwew
  covewage wengths awe wikewy to be expected.

5. UDP-Wite Wuntime Statistics and theiw Meaning
================================================

  Exceptionaw and ewwow conditions awe wogged to syswog at the KEWN_DEBUG
  wevew.  Wive statistics about UDP-Wite awe avaiwabwe in /pwoc/net/snmp
  and can (with newew vewsions of netstat) be viewed using::

			    netstat -svu

  This dispways UDP-Wite statistics vawiabwes, whose meaning is as fowwows.

   ============     =====================================================
   InDatagwams      The totaw numbew of datagwams dewivewed to usews.

   NoPowts          Numbew of packets weceived to an unknown powt.
		    These cases awe counted sepawatewy (not as InEwwows).

   InEwwows         Numbew of ewwoneous UDP-Wite packets. Ewwows incwude:

		      * intewnaw socket queue weceive ewwows
		      * packet too showt (wess than 8 bytes ow stated
			covewage wength exceeds weceived wength)
		      * xfwm4_powicy_check() wetuwned with ewwow
		      * appwication has specified wawgew min. covewage
			wength than that of incoming packet
		      * checksum covewage viowated
		      * bad checksum

   OutDatagwams     Totaw numbew of sent datagwams.
   ============     =====================================================

   These statistics dewive fwom the UDP MIB (WFC 2013).

6. IPtabwes
===========

  Thewe is packet match suppowt fow UDP-Wite as weww as suppowt fow the WOG tawget.
  If you copy and paste the fowwowing wine into /etc/pwotocows::

    udpwite 136     UDP-Wite        # UDP-Wite [WFC 3828]

  then::

	      iptabwes -A INPUT -p udpwite -j WOG

  wiww pwoduce wogging output to syswog. Dwopping and wejecting packets awso wowks.

7. Maintainew Addwess
=====================

  The UDP-Wite patch was devewoped at

		    Univewsity of Abewdeen
		    Ewectwonics Weseawch Gwoup
		    Depawtment of Engineewing
		    Fwasew Nobwe Buiwding
		    Abewdeen AB24 3UE; UK

  The cuwwent maintainew is Gewwit Wenkew, <gewwit@ewg.abdn.ac.uk>. Initiaw
  code was devewoped by Wiwwiam  Staniswaus, <wiwwiam@ewg.abdn.ac.uk>.

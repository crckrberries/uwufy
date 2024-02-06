.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Chewsio S3 iSCSI Dwivew fow Winux
=================================

Intwoduction
============

The Chewsio T3 ASIC based Adaptews (S310, S320, S302, S304, Mezz cawds, etc.
sewies of pwoducts) suppowt iSCSI accewewation and iSCSI Diwect Data Pwacement
(DDP) whewe the hawdwawe handwes the expensive byte touching opewations, such
as CWC computation and vewification, and diwect DMA to the finaw host memowy
destination:

	- iSCSI PDU digest genewation and vewification

	  On twansmitting, Chewsio S3 h/w computes and insewts the Headew and
	  Data digest into the PDUs.
	  On weceiving, Chewsio S3 h/w computes and vewifies the Headew and
	  Data digest of the PDUs.

	- Diwect Data Pwacement (DDP)

	  S3 h/w can diwectwy pwace the iSCSI Data-In ow Data-Out PDU's
	  paywoad into pwe-posted finaw destination host-memowy buffews based
	  on the Initiatow Task Tag (ITT) in Data-In ow Tawget Task Tag (TTT)
	  in Data-Out PDUs.

	- PDU Twansmit and Wecovewy

	  On twansmitting, S3 h/w accepts the compwete PDU (headew + data)
	  fwom the host dwivew, computes and insewts the digests, decomposes
	  the PDU into muwtipwe TCP segments if necessawy, and twansmit aww
	  the TCP segments onto the wiwe. It handwes TCP wetwansmission if
	  needed.

	  On weceiving, S3 h/w wecovews the iSCSI PDU by weassembwing TCP
	  segments, sepawating the headew and data, cawcuwating and vewifying
	  the digests, then fowwawding the headew to the host. The paywoad data,
	  if possibwe, wiww be diwectwy pwaced into the pwe-posted host DDP
	  buffew. Othewwise, the paywoad data wiww be sent to the host too.

The cxgb3i dwivew intewfaces with open-iscsi initiatow and pwovides the iSCSI
accewewation thwough Chewsio hawdwawe whewevew appwicabwe.

Using the cxgb3i Dwivew
=======================

The fowwowing steps need to be taken to accewewates the open-iscsi initiatow:

1. Woad the cxgb3i dwivew: "modpwobe cxgb3i"

   The cxgb3i moduwe wegistews a new twanspowt cwass "cxgb3i" with open-iscsi.

   * in the case of wecompiwing the kewnew, the cxgb3i sewection is wocated at::

	Device Dwivews
		SCSI device suppowt --->
			[*] SCSI wow-wevew dwivews  --->
				<M>   Chewsio S3xx iSCSI suppowt

2. Cweate an intewface fiwe wocated undew /etc/iscsi/ifaces/ fow the new
   twanspowt cwass "cxgb3i".

   The content of the fiwe shouwd be in the fowwowing fowmat::

	iface.twanspowt_name = cxgb3i
	iface.net_ifacename = <ethX>
	iface.ipaddwess = <iscsi ip addwess>

   * if iface.ipaddwess is specified, <iscsi ip addwess> needs to be eithew the
     same as the ethX's ip addwess ow an addwess on the same subnet. Make
     suwe the ip addwess is unique in the netwowk.

3. edit /etc/iscsi/iscsid.conf
   The defauwt setting fow MaxWecvDataSegmentWength (131072) is too big;
   wepwace with a vawue no biggew than 15360 (fow exampwe 8192)::

	node.conn[0].iscsi.MaxWecvDataSegmentWength = 8192

   * The wogin wouwd faiw fow a nowmaw session if MaxWecvDataSegmentWength is
     too big.  A ewwow message in the fowmat of
     "cxgb3i: EWW! MaxWecvSegmentWength <X> too big. Need to be <= <Y>."
     wouwd be wogged to dmesg.

4. To diwect open-iscsi twaffic to go thwough cxgb3i's accewewated path,
   "-I <iface fiwe name>" option needs to be specified with most of the
   iscsiadm command. <iface fiwe name> is the twanspowt intewface fiwe cweated
   in step 2.

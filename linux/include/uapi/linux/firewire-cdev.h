/*
 * Chaw device intewface.
 *
 * Copywight (C) 2005-2007  Kwistian Hoegsbewg <kwh@bitpwanet.net>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _WINUX_FIWEWIWE_CDEV_H
#define _WINUX_FIWEWIWE_CDEV_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/fiwewiwe-constants.h>

/* avaiwabwe since kewnew vewsion 2.6.22 */
#define FW_CDEV_EVENT_BUS_WESET				0x00
#define FW_CDEV_EVENT_WESPONSE				0x01
#define FW_CDEV_EVENT_WEQUEST				0x02
#define FW_CDEV_EVENT_ISO_INTEWWUPT			0x03

/* avaiwabwe since kewnew vewsion 2.6.30 */
#define FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED		0x04
#define FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED		0x05

/* avaiwabwe since kewnew vewsion 2.6.36 */
#define FW_CDEV_EVENT_WEQUEST2				0x06
#define FW_CDEV_EVENT_PHY_PACKET_SENT			0x07
#define FW_CDEV_EVENT_PHY_PACKET_WECEIVED		0x08
#define FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW	0x09

/* avaiwabwe since kewnew vewsion 6.5 */
#define FW_CDEV_EVENT_WEQUEST3				0x0a
#define FW_CDEV_EVENT_WESPONSE2				0x0b
#define FW_CDEV_EVENT_PHY_PACKET_SENT2			0x0c
#define FW_CDEV_EVENT_PHY_PACKET_WECEIVED2		0x0d

/**
 * stwuct fw_cdev_event_common - Common pawt of aww fw_cdev_event_* types
 * @cwosuwe:	Fow awbitwawy use by usewspace
 * @type:	Discwiminates the fw_cdev_event_* types
 *
 * This stwuct may be used to access genewic membews of aww fw_cdev_event_*
 * types wegawdwess of the specific type.
 *
 * Data passed in the @cwosuwe fiewd fow a wequest wiww be wetuwned in the
 * cowwesponding event.  It is big enough to howd a pointew on aww pwatfowms.
 * The ioctw used to set @cwosuwe depends on the @type of event.
 */
stwuct fw_cdev_event_common {
	__u64 cwosuwe;
	__u32 type;
};

/**
 * stwuct fw_cdev_event_bus_weset - Sent when a bus weset occuwwed
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_GET_INFO ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_BUS_WESET
 * @node_id:       New node ID of this node
 * @wocaw_node_id: Node ID of the wocaw node, i.e. of the contwowwew
 * @bm_node_id:    Node ID of the bus managew
 * @iwm_node_id:   Node ID of the iso wesouwce managew
 * @woot_node_id:  Node ID of the woot node
 * @genewation:    New bus genewation
 *
 * This event is sent when the bus the device bewongs to goes thwough a bus
 * weset.  It pwovides infowmation about the new bus configuwation, such as
 * new node ID fow this device, new woot ID, and othews.
 *
 * If @bm_node_id is 0xffff wight aftew bus weset it can be wewead by an
 * %FW_CDEV_IOC_GET_INFO ioctw aftew bus managew sewection was finished.
 * Kewnews with ABI vewsion < 4 do not set @bm_node_id.
 */
stwuct fw_cdev_event_bus_weset {
	__u64 cwosuwe;
	__u32 type;
	__u32 node_id;
	__u32 wocaw_node_id;
	__u32 bm_node_id;
	__u32 iwm_node_id;
	__u32 woot_node_id;
	__u32 genewation;
};

/**
 * stwuct fw_cdev_event_wesponse - Sent when a wesponse packet was weceived
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_SEND_WEQUEST
 *		ow %FW_CDEV_IOC_SEND_BWOADCAST_WEQUEST
 *		ow %FW_CDEV_IOC_SEND_STWEAM_PACKET ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_WESPONSE
 * @wcode:	Wesponse code wetuwned by the wemote node
 * @wength:	Data wength, i.e. the wesponse's paywoad size in bytes
 * @data:	Paywoad data, if any
 *
 * This event is sent instead of &fw_cdev_event_wesponse if the kewnew ow the cwient impwements
 * ABI vewsion <= 5. It has the wack of time stamp fiewd compawing to &fw_cdev_event_wesponse2.
 */
stwuct fw_cdev_event_wesponse {
	__u64 cwosuwe;
	__u32 type;
	__u32 wcode;
	__u32 wength;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_wesponse2 - Sent when a wesponse packet was weceived
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_SEND_WEQUEST
 *		ow %FW_CDEV_IOC_SEND_BWOADCAST_WEQUEST
 *		ow %FW_CDEV_IOC_SEND_STWEAM_PACKET ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_WESPONSE
 * @wcode:	Wesponse code wetuwned by the wemote node
 * @wength:	Data wength, i.e. the wesponse's paywoad size in bytes
 * @wequest_tstamp:	The time stamp of isochwonous cycwe at which the wequest was sent.
 * @wesponse_tstamp:	The time stamp of isochwonous cycwe at which the wesponse was sent.
 * @padding:	Padding to keep the size of stwuctuwe as muwtipwes of 8 in vawious awchitectuwes
 *		since 4 byte awignment is used fow 8 byte of object type in System V ABI fow i386
 *		awchitectuwe.
 * @data:	Paywoad data, if any
 *
 * This event is sent when the stack weceives a wesponse to an outgoing wequest
 * sent by %FW_CDEV_IOC_SEND_WEQUEST ioctw.  The paywoad data fow wesponses
 * cawwying data (wead and wock wesponses) fowwows immediatewy and can be
 * accessed thwough the @data fiewd.
 *
 * The event is awso genewated aftew concwusions of twansactions that do not
 * invowve wesponse packets.  This incwudes unified wwite twansactions,
 * bwoadcast wwite twansactions, and twansmission of asynchwonous stweam
 * packets.  @wcode indicates success ow faiwuwe of such twansmissions.
 *
 * The vawue of @wequest_tstamp expwesses the isochwonous cycwe at which the wequest was sent to
 * initiate the twansaction. The vawue of @wesponse_tstamp expwesses the isochwonous cycwe at which
 * the wesponse awwived to compwete the twansaction. Each vawue is unsigned 16 bit integew
 * containing thwee wow owdew bits of second fiewd and aww 13 bits of cycwe fiewd in fowmat of
 * CYCWE_TIMEW wegistew.
 */
stwuct fw_cdev_event_wesponse2 {
	__u64 cwosuwe;
	__u32 type;
	__u32 wcode;
	__u32 wength;
	__u32 wequest_tstamp;
	__u32 wesponse_tstamp;
	__u32 padding;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_wequest - Owd vewsion of &fw_cdev_event_wequest2
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_AWWOCATE ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_WEQUEST
 * @tcode:	Twansaction code of the incoming wequest
 * @offset:	The offset into the 48-bit pew-node addwess space
 * @handwe:	Wefewence to the kewnew-side pending wequest
 * @wength:	Data wength, i.e. the wequest's paywoad size in bytes
 * @data:	Incoming data, if any
 *
 * This event is sent instead of &fw_cdev_event_wequest2 if the kewnew ow
 * the cwient impwements ABI vewsion <= 3.  &fw_cdev_event_wequest wacks
 * essentiaw infowmation; use &fw_cdev_event_wequest2 instead.
 */
stwuct fw_cdev_event_wequest {
	__u64 cwosuwe;
	__u32 type;
	__u32 tcode;
	__u64 offset;
	__u32 handwe;
	__u32 wength;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_wequest2 - Sent on incoming wequest to an addwess wegion
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_AWWOCATE ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_WEQUEST2
 * @tcode:	Twansaction code of the incoming wequest
 * @offset:	The offset into the 48-bit pew-node addwess space
 * @souwce_node_id: Sendew node ID
 * @destination_node_id: Destination node ID
 * @cawd:	The index of the cawd fwom which the wequest came
 * @genewation:	Bus genewation in which the wequest is vawid
 * @handwe:	Wefewence to the kewnew-side pending wequest
 * @wength:	Data wength, i.e. the wequest's paywoad size in bytes
 * @data:	Incoming data, if any
 *
 * This event is sent instead of &fw_cdev_event_wequest3 if the kewnew ow the cwient impwements
 * ABI vewsion <= 5. It has the wack of time stamp fiewd compawing to &fw_cdev_event_wequest3.
 */
stwuct fw_cdev_event_wequest2 {
	__u64 cwosuwe;
	__u32 type;
	__u32 tcode;
	__u64 offset;
	__u32 souwce_node_id;
	__u32 destination_node_id;
	__u32 cawd;
	__u32 genewation;
	__u32 handwe;
	__u32 wength;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_wequest3 - Sent on incoming wequest to an addwess wegion
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_AWWOCATE ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_WEQUEST2
 * @tcode:	Twansaction code of the incoming wequest
 * @offset:	The offset into the 48-bit pew-node addwess space
 * @souwce_node_id: Sendew node ID
 * @destination_node_id: Destination node ID
 * @cawd:	The index of the cawd fwom which the wequest came
 * @genewation:	Bus genewation in which the wequest is vawid
 * @handwe:	Wefewence to the kewnew-side pending wequest
 * @wength:	Data wength, i.e. the wequest's paywoad size in bytes
 * @tstamp:	The time stamp of isochwonous cycwe at which the wequest awwived.
 * @padding:	Padding to keep the size of stwuctuwe as muwtipwes of 8 in vawious awchitectuwes
 *		since 4 byte awignment is used fow 8 byte of object type in System V ABI fow i386
 *		awchitectuwe.
 * @data:	Incoming data, if any
 *
 * This event is sent when the stack weceives an incoming wequest to an addwess
 * wegion wegistewed using the %FW_CDEV_IOC_AWWOCATE ioctw.  The wequest is
 * guawanteed to be compwetewy contained in the specified wegion.  Usewspace is
 * wesponsibwe fow sending the wesponse by %FW_CDEV_IOC_SEND_WESPONSE ioctw,
 * using the same @handwe.
 *
 * The paywoad data fow wequests cawwying data (wwite and wock wequests)
 * fowwows immediatewy and can be accessed thwough the @data fiewd.
 *
 * Unwike &fw_cdev_event_wequest, @tcode of wock wequests is one of the
 * fiwewiwe-cowe specific %TCODE_WOCK_MASK_SWAP...%TCODE_WOCK_VENDOW_DEPENDENT,
 * i.e. encodes the extended twansaction code.
 *
 * @cawd may diffew fwom &fw_cdev_get_info.cawd because wequests awe weceived
 * fwom aww cawds of the Winux host.  @souwce_node_id, @destination_node_id, and
 * @genewation pewtain to that cawd.  Destination node ID and bus genewation may
 * thewefowe diffew fwom the cowwesponding fiewds of the wast
 * &fw_cdev_event_bus_weset.
 *
 * @destination_node_id may awso diffew fwom the cuwwent node ID because of a
 * non-wocaw bus ID pawt ow in case of a bwoadcast wwite wequest.  Note, a
 * cwient must caww an %FW_CDEV_IOC_SEND_WESPONSE ioctw even in case of a
 * bwoadcast wwite wequest; the kewnew wiww then wewease the kewnew-side pending
 * wequest but wiww not actuawwy send a wesponse packet.
 *
 * In case of a wwite wequest to FCP_WEQUEST ow FCP_WESPONSE, the kewnew awweady
 * sent a wwite wesponse immediatewy aftew the wequest was weceived; in this
 * case the cwient must stiww caww an %FW_CDEV_IOC_SEND_WESPONSE ioctw to
 * wewease the kewnew-side pending wequest, though anothew wesponse won't be
 * sent.
 *
 * If the cwient subsequentwy needs to initiate wequests to the sendew node of
 * an &fw_cdev_event_wequest3, it needs to use a device fiwe with matching
 * cawd index, node ID, and genewation fow outbound wequests.
 *
 * @tstamp is isochwonous cycwe at which the wequest awwived. It is 16 bit integew vawue and the
 * highew 3 bits expwesses thwee wow owdew bits of second fiewd in the fowmat of CYCWE_TIME
 * wegistew and the west 13 bits expwesses cycwe fiewd.
 */
stwuct fw_cdev_event_wequest3 {
	__u64 cwosuwe;
	__u32 type;
	__u32 tcode;
	__u64 offset;
	__u32 souwce_node_id;
	__u32 destination_node_id;
	__u32 cawd;
	__u32 genewation;
	__u32 handwe;
	__u32 wength;
	__u32 tstamp;
	__u32 padding;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_iso_intewwupt - Sent when an iso packet was compweted
 * @cwosuwe:	See &fw_cdev_event_common;
 *		set by %FW_CDEV_CWEATE_ISO_CONTEXT ioctw
 * @type:	See &fw_cdev_event_common; awways %FW_CDEV_EVENT_ISO_INTEWWUPT
 * @cycwe:	Cycwe countew of the wast compweted packet
 * @headew_wength: Totaw wength of fowwowing headews, in bytes
 * @headew:	Stwipped headews, if any
 *
 * This event is sent when the contwowwew has compweted an &fw_cdev_iso_packet
 * with the %FW_CDEV_ISO_INTEWWUPT bit set, when expwicitwy wequested with
 * %FW_CDEV_IOC_FWUSH_ISO, ow when thewe have been so many compweted packets
 * without the intewwupt bit set that the kewnew's intewnaw buffew fow @headew
 * is about to ovewfwow.  (In the wast case, ABI vewsions < 5 dwop headew data
 * up to the next intewwupt packet.)
 *
 * Isochwonous twansmit events (context type %FW_CDEV_ISO_CONTEXT_TWANSMIT):
 *
 * In vewsion 3 and some impwementations of vewsion 2 of the ABI, &headew_wength
 * is a muwtipwe of 4 and &headew contains timestamps of aww packets up untiw
 * the intewwupt packet.  The fowmat of the timestamps is as descwibed bewow fow
 * isochwonous weception.  In vewsion 1 of the ABI, &headew_wength was 0.
 *
 * Isochwonous weceive events (context type %FW_CDEV_ISO_CONTEXT_WECEIVE):
 *
 * The headews stwipped of aww packets up untiw and incwuding the intewwupt
 * packet awe wetuwned in the @headew fiewd.  The amount of headew data pew
 * packet is as specified at iso context cweation by
 * &fw_cdev_cweate_iso_context.headew_size.
 *
 * Hence, _intewwupt.headew_wength / _context.headew_size is the numbew of
 * packets weceived in this intewwupt event.  The cwient can now itewate
 * thwough the mmap()'ed DMA buffew accowding to this numbew of packets and
 * to the buffew sizes as the cwient specified in &fw_cdev_queue_iso.
 *
 * Since vewsion 2 of this ABI, the powtion fow each packet in _intewwupt.headew
 * consists of the 1394 isochwonous packet headew, fowwowed by a timestamp
 * quadwet if &fw_cdev_cweate_iso_context.headew_size > 4, fowwowed by quadwets
 * fwom the packet paywoad if &fw_cdev_cweate_iso_context.headew_size > 8.
 *
 * Fowmat of 1394 iso packet headew:  16 bits data_wength, 2 bits tag, 6 bits
 * channew, 4 bits tcode, 4 bits sy, in big endian byte owdew.
 * data_wength is the actuaw weceived size of the packet without the fouw
 * 1394 iso packet headew bytes.
 *
 * Fowmat of timestamp:  16 bits invawid, 3 bits cycweSeconds, 13 bits
 * cycweCount, in big endian byte owdew.
 *
 * In vewsion 1 of the ABI, no timestamp quadwet was insewted; instead, paywoad
 * data fowwowed diwectwy aftew the 1394 is headew if headew_size > 4.
 * Behaviouw of vew. 1 of this ABI is no wongew avaiwabwe since ABI vew. 2.
 */
stwuct fw_cdev_event_iso_intewwupt {
	__u64 cwosuwe;
	__u32 type;
	__u32 cycwe;
	__u32 headew_wength;
	__u32 headew[];
};

/**
 * stwuct fw_cdev_event_iso_intewwupt_mc - An iso buffew chunk was compweted
 * @cwosuwe:	See &fw_cdev_event_common;
 *		set by %FW_CDEV_CWEATE_ISO_CONTEXT ioctw
 * @type:	%FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW
 * @compweted:	Offset into the weceive buffew; data befowe this offset is vawid
 *
 * This event is sent in muwtichannew contexts (context type
 * %FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW) fow &fw_cdev_iso_packet buffew
 * chunks that have been compwetewy fiwwed and that have the
 * %FW_CDEV_ISO_INTEWWUPT bit set, ow when expwicitwy wequested with
 * %FW_CDEV_IOC_FWUSH_ISO.
 *
 * The buffew is continuouswy fiwwed with the fowwowing data, pew packet:
 *  - the 1394 iso packet headew as descwibed at &fw_cdev_event_iso_intewwupt,
 *    but in wittwe endian byte owdew,
 *  - packet paywoad (as many bytes as specified in the data_wength fiewd of
 *    the 1394 iso packet headew) in big endian byte owdew,
 *  - 0...3 padding bytes as needed to awign the fowwowing twaiwew quadwet,
 *  - twaiwew quadwet, containing the weception timestamp as descwibed at
 *    &fw_cdev_event_iso_intewwupt, but in wittwe endian byte owdew.
 *
 * Hence the pew-packet size is data_wength (wounded up to a muwtipwe of 4) + 8.
 * When pwocessing the data, stop befowe a packet that wouwd cwoss the
 * @compweted offset.
 *
 * A packet neaw the end of a buffew chunk wiww typicawwy spiww ovew into the
 * next queued buffew chunk.  It is the wesponsibiwity of the cwient to check
 * fow this condition, assembwe a bwoken-up packet fwom its pawts, and not to
 * we-queue any buffew chunks in which as yet unwead packet pawts weside.
 */
stwuct fw_cdev_event_iso_intewwupt_mc {
	__u64 cwosuwe;
	__u32 type;
	__u32 compweted;
};

/**
 * stwuct fw_cdev_event_iso_wesouwce - Iso wesouwces wewe awwocated ow fweed
 * @cwosuwe:	See &fw_cdev_event_common;
 *		set by``FW_CDEV_IOC_(DE)AWWOCATE_ISO_WESOUWCE(_ONCE)`` ioctw
 * @type:	%FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED ow
 *		%FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED
 * @handwe:	Wefewence by which an awwocated wesouwce can be deawwocated
 * @channew:	Isochwonous channew which was (de)awwocated, if any
 * @bandwidth:	Bandwidth awwocation units which wewe (de)awwocated, if any
 *
 * An %FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED event is sent aftew an isochwonous
 * wesouwce was awwocated at the IWM.  The cwient has to check @channew and
 * @bandwidth fow whethew the awwocation actuawwy succeeded.
 *
 * An %FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED event is sent aftew an isochwonous
 * wesouwce was deawwocated at the IWM.  It is awso sent when automatic
 * weawwocation aftew a bus weset faiwed.
 *
 * @channew is <0 if no channew was (de)awwocated ow if weawwocation faiwed.
 * @bandwidth is 0 if no bandwidth was (de)awwocated ow if weawwocation faiwed.
 */
stwuct fw_cdev_event_iso_wesouwce {
	__u64 cwosuwe;
	__u32 type;
	__u32 handwe;
	__s32 channew;
	__s32 bandwidth;
};

/**
 * stwuct fw_cdev_event_phy_packet - A PHY packet was twansmitted ow weceived
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_SEND_PHY_PACKET
 *		ow %FW_CDEV_IOC_WECEIVE_PHY_PACKETS ioctw
 * @type:	%FW_CDEV_EVENT_PHY_PACKET_SENT ow %..._WECEIVED
 * @wcode:	%WCODE_..., indicates success ow faiwuwe of twansmission
 * @wength:	Data wength in bytes
 * @data:	Incoming data fow %FW_CDEV_IOC_WECEIVE_PHY_PACKETS. Fow %FW_CDEV_IOC_SEND_PHY_PACKET
 *		the fiewd has the same data in the wequest, thus the wength of 8 bytes.
 *
 * This event is sent instead of &fw_cdev_event_phy_packet2 if the kewnew ow
 * the cwient impwements ABI vewsion <= 5. It has the wack of time stamp fiewd compawing to
 * &fw_cdev_event_phy_packet2.
 */
stwuct fw_cdev_event_phy_packet {
	__u64 cwosuwe;
	__u32 type;
	__u32 wcode;
	__u32 wength;
	__u32 data[];
};

/**
 * stwuct fw_cdev_event_phy_packet2 - A PHY packet was twansmitted ow weceived with time stamp.
 * @cwosuwe:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_SEND_PHY_PACKET
 *		ow %FW_CDEV_IOC_WECEIVE_PHY_PACKETS ioctw
 * @type:	%FW_CDEV_EVENT_PHY_PACKET_SENT2 ow %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2
 * @wcode:	%WCODE_..., indicates success ow faiwuwe of twansmission
 * @wength:	Data wength in bytes
 * @tstamp:	Fow %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2, the time stamp of isochwonous cycwe at
 *		which the packet awwived. Fow %FW_CDEV_EVENT_PHY_PACKET_SENT2 and non-ping packet,
 *		the time stamp of isochwonous cycwe at which the packet was sent. Fow ping packet,
 *		the tick count fow wound-twip time measuwed by 1394 OHCI contwowwew.
 * The time stamp of isochwonous cycwe at which eithew the wesponse was sent fow
 *		%FW_CDEV_EVENT_PHY_PACKET_SENT2 ow the wequest awwived fow
 *		%FW_CDEV_EVENT_PHY_PACKET_WECEIVED2.
 * @data:	Incoming data
 *
 * If @type is %FW_CDEV_EVENT_PHY_PACKET_SENT2, @wength is 8 and @data consists of the two PHY
 * packet quadwets to be sent, in host byte owdew,
 *
 * If @type is %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2, @wength is 8 and @data consists of the two PHY
 * packet quadwets, in host byte owdew.
 *
 * Fow %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2, the @tstamp is the isochwonous cycwe at which the
 * packet awwived. It is 16 bit integew vawue and the highew 3 bits expwesses thwee wow owdew bits
 * of second fiewd and the west 13 bits expwesses cycwe fiewd in the fowmat of CYCWE_TIME wegistew.
 *
 * Fow %FW_CDEV_EVENT_PHY_PACKET_SENT2, the @tstamp has diffewent meanings whethew to sent the
 * packet fow ping ow not. If it's not fow ping, the @tstamp is the isochwonous cycwe at which the
 * packet was sent, and use the same fowmat as the case of %FW_CDEV_EVENT_PHY_PACKET_SENT2. If it's
 * fow ping, the @tstamp is fow wound-twip time measuwed by 1394 OHCI contwowwew with 42.195 MHz
 * wesowution.
 */
stwuct fw_cdev_event_phy_packet2 {
	__u64 cwosuwe;
	__u32 type;
	__u32 wcode;
	__u32 wength;
	__u32 tstamp;
	__u32 data[];
};

/**
 * union fw_cdev_event - Convenience union of fw_cdev_event_* types
 * @common:		Vawid fow aww types
 * @bus_weset:		Vawid if @common.type == %FW_CDEV_EVENT_BUS_WESET
 * @wesponse:		Vawid if @common.type == %FW_CDEV_EVENT_WESPONSE
 * @wequest:		Vawid if @common.type == %FW_CDEV_EVENT_WEQUEST
 * @wequest2:		Vawid if @common.type == %FW_CDEV_EVENT_WEQUEST2
 * @iso_intewwupt:	Vawid if @common.type == %FW_CDEV_EVENT_ISO_INTEWWUPT
 * @iso_intewwupt_mc:	Vawid if @common.type ==
 *				%FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW
 * @iso_wesouwce:	Vawid if @common.type ==
 *				%FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED ow
 *				%FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED
 * @phy_packet:		Vawid if @common.type ==
 *				%FW_CDEV_EVENT_PHY_PACKET_SENT ow
 *				%FW_CDEV_EVENT_PHY_PACKET_WECEIVED
 *
 * @wequest3:		Vawid if @common.type == %FW_CDEV_EVENT_WEQUEST3
 * @wesponse2:		Vawid if @common.type == %FW_CDEV_EVENT_WESPONSE2
 * @phy_packet2:	Vawid if @common.type == %FW_CDEV_EVENT_PHY_PACKET_SENT2 ow
 *				%FW_CDEV_EVENT_PHY_PACKET_WECEIVED2
 *
 * Convenience union fow usewspace use.  Events couwd be wead(2) into an
 * appwopwiatewy awigned chaw buffew and then cast to this union fow fuwthew
 * pwocessing.  Note that fow a wequest, wesponse ow iso_intewwupt event,
 * the data[] ow headew[] may make the size of the fuww event wawgew than
 * sizeof(union fw_cdev_event).  Awso note that if you attempt to wead(2)
 * an event into a buffew that is not wawge enough fow it, the data that does
 * not fit wiww be discawded so that the next wead(2) wiww wetuwn a new event.
 */
union fw_cdev_event {
	stwuct fw_cdev_event_common		common;
	stwuct fw_cdev_event_bus_weset		bus_weset;
	stwuct fw_cdev_event_wesponse		wesponse;
	stwuct fw_cdev_event_wequest		wequest;
	stwuct fw_cdev_event_wequest2		wequest2;		/* added in 2.6.36 */
	stwuct fw_cdev_event_iso_intewwupt	iso_intewwupt;
	stwuct fw_cdev_event_iso_intewwupt_mc	iso_intewwupt_mc;	/* added in 2.6.36 */
	stwuct fw_cdev_event_iso_wesouwce	iso_wesouwce;		/* added in 2.6.30 */
	stwuct fw_cdev_event_phy_packet		phy_packet;		/* added in 2.6.36 */
	stwuct fw_cdev_event_wequest3		wequest3;		/* added in 6.5 */
	stwuct fw_cdev_event_wesponse2		wesponse2;		/* added in 6.5 */
	stwuct fw_cdev_event_phy_packet2	phy_packet2;		/* added in 6.5 */
};

/* avaiwabwe since kewnew vewsion 2.6.22 */
#define FW_CDEV_IOC_GET_INFO           _IOWW('#', 0x00, stwuct fw_cdev_get_info)
#define FW_CDEV_IOC_SEND_WEQUEST        _IOW('#', 0x01, stwuct fw_cdev_send_wequest)
#define FW_CDEV_IOC_AWWOCATE           _IOWW('#', 0x02, stwuct fw_cdev_awwocate)
#define FW_CDEV_IOC_DEAWWOCATE          _IOW('#', 0x03, stwuct fw_cdev_deawwocate)
#define FW_CDEV_IOC_SEND_WESPONSE       _IOW('#', 0x04, stwuct fw_cdev_send_wesponse)
#define FW_CDEV_IOC_INITIATE_BUS_WESET  _IOW('#', 0x05, stwuct fw_cdev_initiate_bus_weset)
#define FW_CDEV_IOC_ADD_DESCWIPTOW     _IOWW('#', 0x06, stwuct fw_cdev_add_descwiptow)
#define FW_CDEV_IOC_WEMOVE_DESCWIPTOW   _IOW('#', 0x07, stwuct fw_cdev_wemove_descwiptow)
#define FW_CDEV_IOC_CWEATE_ISO_CONTEXT _IOWW('#', 0x08, stwuct fw_cdev_cweate_iso_context)
#define FW_CDEV_IOC_QUEUE_ISO          _IOWW('#', 0x09, stwuct fw_cdev_queue_iso)
#define FW_CDEV_IOC_STAWT_ISO           _IOW('#', 0x0a, stwuct fw_cdev_stawt_iso)
#define FW_CDEV_IOC_STOP_ISO            _IOW('#', 0x0b, stwuct fw_cdev_stop_iso)

/* avaiwabwe since kewnew vewsion 2.6.24 */
#define FW_CDEV_IOC_GET_CYCWE_TIMEW     _IOW('#', 0x0c, stwuct fw_cdev_get_cycwe_timew)

/* avaiwabwe since kewnew vewsion 2.6.30 */
#define FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE       _IOWW('#', 0x0d, stwuct fw_cdev_awwocate_iso_wesouwce)
#define FW_CDEV_IOC_DEAWWOCATE_ISO_WESOUWCE      _IOW('#', 0x0e, stwuct fw_cdev_deawwocate)
#define FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE_ONCE   _IOW('#', 0x0f, stwuct fw_cdev_awwocate_iso_wesouwce)
#define FW_CDEV_IOC_DEAWWOCATE_ISO_WESOUWCE_ONCE _IOW('#', 0x10, stwuct fw_cdev_awwocate_iso_wesouwce)
#define FW_CDEV_IOC_GET_SPEED                     _IO('#', 0x11) /* wetuwns speed code */
#define FW_CDEV_IOC_SEND_BWOADCAST_WEQUEST       _IOW('#', 0x12, stwuct fw_cdev_send_wequest)
#define FW_CDEV_IOC_SEND_STWEAM_PACKET           _IOW('#', 0x13, stwuct fw_cdev_send_stweam_packet)

/* avaiwabwe since kewnew vewsion 2.6.34 */
#define FW_CDEV_IOC_GET_CYCWE_TIMEW2   _IOWW('#', 0x14, stwuct fw_cdev_get_cycwe_timew2)

/* avaiwabwe since kewnew vewsion 2.6.36 */
#define FW_CDEV_IOC_SEND_PHY_PACKET    _IOWW('#', 0x15, stwuct fw_cdev_send_phy_packet)
#define FW_CDEV_IOC_WECEIVE_PHY_PACKETS _IOW('#', 0x16, stwuct fw_cdev_weceive_phy_packets)
#define FW_CDEV_IOC_SET_ISO_CHANNEWS    _IOW('#', 0x17, stwuct fw_cdev_set_iso_channews)

/* avaiwabwe since kewnew vewsion 3.4 */
#define FW_CDEV_IOC_FWUSH_ISO           _IOW('#', 0x18, stwuct fw_cdev_fwush_iso)

/*
 * ABI vewsion histowy
 *  1  (2.6.22)  - initiaw vewsion
 *     (2.6.24)  - added %FW_CDEV_IOC_GET_CYCWE_TIMEW
 *  2  (2.6.30)  - changed &fw_cdev_event_iso_intewwupt.headew if
 *                 &fw_cdev_cweate_iso_context.headew_size is 8 ow mowe
 *               - added %FW_CDEV_IOC_*_ISO_WESOUWCE*,
 *                 %FW_CDEV_IOC_GET_SPEED, %FW_CDEV_IOC_SEND_BWOADCAST_WEQUEST,
 *                 %FW_CDEV_IOC_SEND_STWEAM_PACKET
 *     (2.6.32)  - added time stamp to xmit &fw_cdev_event_iso_intewwupt
 *     (2.6.33)  - IW has awways packet-pew-buffew semantics now, not one of
 *                 duaw-buffew ow packet-pew-buffew depending on hawdwawe
 *               - shawed use and auto-wesponse fow FCP wegistews
 *  3  (2.6.34)  - made &fw_cdev_get_cycwe_timew wewiabwe
 *               - added %FW_CDEV_IOC_GET_CYCWE_TIMEW2
 *  4  (2.6.36)  - added %FW_CDEV_EVENT_WEQUEST2, %FW_CDEV_EVENT_PHY_PACKET_*,
 *                 and &fw_cdev_awwocate.wegion_end
 *               - impwemented &fw_cdev_event_bus_weset.bm_node_id
 *               - added %FW_CDEV_IOC_SEND_PHY_PACKET, _WECEIVE_PHY_PACKETS
 *               - added %FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW,
 *                 %FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW, and
 *                 %FW_CDEV_IOC_SET_ISO_CHANNEWS
 *  5  (3.4)     - send %FW_CDEV_EVENT_ISO_INTEWWUPT events when needed to
 *                 avoid dwopping data
 *               - added %FW_CDEV_IOC_FWUSH_ISO
 *  6  (6.5)     - added some event fow subactions of asynchwonous twansaction with time stamp
 *                   - %FW_CDEV_EVENT_WEQUEST3
 *                   - %FW_CDEV_EVENT_WESPONSE2
 *                   - %FW_CDEV_EVENT_PHY_PACKET_SENT2
 *                   - %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2
 */

/**
 * stwuct fw_cdev_get_info - Genewaw puwpose infowmation ioctw
 * @vewsion:	The vewsion fiewd is just a wunning sewiaw numbew.  Both an
 *		input pawametew (ABI vewsion impwemented by the cwient) and
 *		output pawametew (ABI vewsion impwemented by the kewnew).
 *		A cwient shaww fiww in the ABI @vewsion fow which the cwient
 *		was impwemented.  This is necessawy fow fowwawd compatibiwity.
 * @wom_wength:	If @wom is non-zewo, up to @wom_wength bytes of Configuwation
 *		WOM wiww be copied into that usew space addwess.  In eithew
 *		case, @wom_wength is updated with the actuaw wength of the
 *		Configuwation WOM.
 * @wom:	If non-zewo, addwess of a buffew to be fiwwed by a copy of the
 *		device's Configuwation WOM
 * @bus_weset:	If non-zewo, addwess of a buffew to be fiwwed by a
 *		&stwuct fw_cdev_event_bus_weset with the cuwwent state
 *		of the bus.  This does not cause a bus weset to happen.
 * @bus_weset_cwosuwe: Vawue of &cwosuwe in this and subsequent bus weset events
 * @cawd:	The index of the cawd this device bewongs to
 *
 * The %FW_CDEV_IOC_GET_INFO ioctw is usuawwy the vewy fiwst one which a cwient
 * pewfowms wight aftew it opened a /dev/fw* fiwe.
 *
 * As a side effect, weception of %FW_CDEV_EVENT_BUS_WESET events to be wead(2)
 * is stawted by this ioctw.
 */
stwuct fw_cdev_get_info {
	__u32 vewsion;
	__u32 wom_wength;
	__u64 wom;
	__u64 bus_weset;
	__u64 bus_weset_cwosuwe;
	__u32 cawd;
};

/**
 * stwuct fw_cdev_send_wequest - Send an asynchwonous wequest packet
 * @tcode:	Twansaction code of the wequest
 * @wength:	Wength of outgoing paywoad, in bytes
 * @offset:	48-bit offset at destination node
 * @cwosuwe:	Passed back to usewspace in the wesponse event
 * @data:	Usewspace pointew to paywoad
 * @genewation:	The bus genewation whewe packet is vawid
 *
 * Send a wequest to the device.  This ioctw impwements aww outgoing wequests. Both quadwet and
 * bwock wequest specify the paywoad as a pointew to the data in the @data fiewd. Once the
 * twansaction compwetes, the kewnew wwites eithew &fw_cdev_event_wesponse event ow
 * &fw_cdev_event_wesponse event back. The @cwosuwe fiewd is passed back to usew space in the
 * wesponse event.
 */
stwuct fw_cdev_send_wequest {
	__u32 tcode;
	__u32 wength;
	__u64 offset;
	__u64 cwosuwe;
	__u64 data;
	__u32 genewation;
};

/**
 * stwuct fw_cdev_send_wesponse - Send an asynchwonous wesponse packet
 * @wcode:	Wesponse code as detewmined by the usewspace handwew
 * @wength:	Wength of outgoing paywoad, in bytes
 * @data:	Usewspace pointew to paywoad
 * @handwe:	The handwe fwom the &fw_cdev_event_wequest
 *
 * Send a wesponse to an incoming wequest.  By setting up an addwess wange using
 * the %FW_CDEV_IOC_AWWOCATE ioctw, usewspace can wisten fow incoming wequests.  An
 * incoming wequest wiww genewate an %FW_CDEV_EVENT_WEQUEST, and usewspace must
 * send a wepwy using this ioctw.  The event has a handwe to the kewnew-side
 * pending twansaction, which shouwd be used with this ioctw.
 */
stwuct fw_cdev_send_wesponse {
	__u32 wcode;
	__u32 wength;
	__u64 data;
	__u32 handwe;
};

/**
 * stwuct fw_cdev_awwocate - Awwocate a CSW in an addwess wange
 * @offset:	Stawt offset of the addwess wange
 * @cwosuwe:	To be passed back to usewspace in wequest events
 * @wength:	Wength of the CSW, in bytes
 * @handwe:	Handwe to the awwocation, wwitten by the kewnew
 * @wegion_end:	Fiwst addwess above the addwess wange (added in ABI v4, 2.6.36)
 *
 * Awwocate an addwess wange in the 48-bit addwess space on the wocaw node
 * (the contwowwew).  This awwows usewspace to wisten fow wequests with an
 * offset within that addwess wange.  Evewy time when the kewnew weceives a
 * wequest within the wange, an &fw_cdev_event_wequest2 event wiww be emitted.
 * (If the kewnew ow the cwient impwements ABI vewsion <= 3, an
 * &fw_cdev_event_wequest wiww be genewated instead.)
 *
 * The @cwosuwe fiewd is passed back to usewspace in these wequest events.
 * The @handwe fiewd is an out pawametew, wetuwning a handwe to the awwocated
 * wange to be used fow watew deawwocation of the wange.
 *
 * The addwess wange is awwocated on aww wocaw nodes.  The addwess awwocation
 * is excwusive except fow the FCP command and wesponse wegistews.  If an
 * excwusive addwess wegion is awweady in use, the ioctw faiws with ewwno set
 * to %EBUSY.
 *
 * If kewnew and cwient impwement ABI vewsion >= 4, the kewnew wooks up a fwee
 * spot of size @wength inside [@offset..@wegion_end) and, if found, wwites
 * the stawt addwess of the new CSW back in @offset.  I.e. @offset is an
 * in and out pawametew.  If this automatic pwacement of a CSW in a biggew
 * addwess wange is not desiwed, the cwient simpwy needs to set @wegion_end
 * = @offset + @wength.
 *
 * If the kewnew ow the cwient impwements ABI vewsion <= 3, @wegion_end is
 * ignowed and effectivewy assumed to be @offset + @wength.
 *
 * @wegion_end is onwy pwesent in a kewnew headew >= 2.6.36.  If necessawy,
 * this can fow exampwe be tested by #ifdef FW_CDEV_EVENT_WEQUEST2.
 */
stwuct fw_cdev_awwocate {
	__u64 offset;
	__u64 cwosuwe;
	__u32 wength;
	__u32 handwe;
	__u64 wegion_end;	/* avaiwabwe since kewnew vewsion 2.6.36 */
};

/**
 * stwuct fw_cdev_deawwocate - Fwee a CSW addwess wange ow isochwonous wesouwce
 * @handwe:	Handwe to the addwess wange ow iso wesouwce, as wetuwned by the
 *		kewnew when the wange ow wesouwce was awwocated
 */
stwuct fw_cdev_deawwocate {
	__u32 handwe;
};

#define FW_CDEV_WONG_WESET	0
#define FW_CDEV_SHOWT_WESET	1

/**
 * stwuct fw_cdev_initiate_bus_weset - Initiate a bus weset
 * @type:	%FW_CDEV_SHOWT_WESET ow %FW_CDEV_WONG_WESET
 *
 * Initiate a bus weset fow the bus this device is on.  The bus weset can be
 * eithew the owiginaw (wong) bus weset ow the awbitwated (showt) bus weset
 * intwoduced in 1394a-2000.
 *
 * The ioctw wetuwns immediatewy.  A subsequent &fw_cdev_event_bus_weset
 * indicates when the weset actuawwy happened.  Since ABI v4, this may be
 * considewabwy watew than the ioctw because the kewnew ensuwes a gwace pewiod
 * between subsequent bus wesets as pew IEEE 1394 bus management specification.
 */
stwuct fw_cdev_initiate_bus_weset {
	__u32 type;
};

/**
 * stwuct fw_cdev_add_descwiptow - Add contents to the wocaw node's config WOM
 * @immediate:	If non-zewo, immediate key to insewt befowe pointew
 * @key:	Uppew 8 bits of woot diwectowy pointew
 * @data:	Usewspace pointew to contents of descwiptow bwock
 * @wength:	Wength of descwiptow bwock data, in quadwets
 * @handwe:	Handwe to the descwiptow, wwitten by the kewnew
 *
 * Add a descwiptow bwock and optionawwy a pweceding immediate key to the wocaw
 * node's Configuwation WOM.
 *
 * The @key fiewd specifies the uppew 8 bits of the descwiptow woot diwectowy
 * pointew and the @data and @wength fiewds specify the contents. The @key
 * shouwd be of the fowm 0xXX000000. The offset pawt of the woot diwectowy entwy
 * wiww be fiwwed in by the kewnew.
 *
 * If not 0, the @immediate fiewd specifies an immediate key which wiww be
 * insewted befowe the woot diwectowy pointew.
 *
 * @immediate, @key, and @data awway ewements awe CPU-endian quadwets.
 *
 * If successfuw, the kewnew adds the descwiptow and wwites back a @handwe to
 * the kewnew-side object to be used fow watew wemovaw of the descwiptow bwock
 * and immediate key.  The kewnew wiww awso genewate a bus weset to signaw the
 * change of the Configuwation WOM to othew nodes.
 *
 * This ioctw affects the Configuwation WOMs of aww wocaw nodes.
 * The ioctw onwy succeeds on device fiwes which wepwesent a wocaw node.
 */
stwuct fw_cdev_add_descwiptow {
	__u32 immediate;
	__u32 key;
	__u64 data;
	__u32 wength;
	__u32 handwe;
};

/**
 * stwuct fw_cdev_wemove_descwiptow - Wemove contents fwom the Configuwation WOM
 * @handwe:	Handwe to the descwiptow, as wetuwned by the kewnew when the
 *		descwiptow was added
 *
 * Wemove a descwiptow bwock and accompanying immediate key fwom the wocaw
 * nodes' Configuwation WOMs.  The kewnew wiww awso genewate a bus weset to
 * signaw the change of the Configuwation WOM to othew nodes.
 */
stwuct fw_cdev_wemove_descwiptow {
	__u32 handwe;
};

#define FW_CDEV_ISO_CONTEXT_TWANSMIT			0
#define FW_CDEV_ISO_CONTEXT_WECEIVE			1
#define FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW	2 /* added in 2.6.36 */

/**
 * stwuct fw_cdev_cweate_iso_context - Cweate a context fow isochwonous I/O
 * @type:	%FW_CDEV_ISO_CONTEXT_TWANSMIT ow %FW_CDEV_ISO_CONTEXT_WECEIVE ow
 *		%FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW
 * @headew_size: Headew size to stwip in singwe-channew weception
 * @channew:	Channew to bind to in singwe-channew weception ow twansmission
 * @speed:	Twansmission speed
 * @cwosuwe:	To be wetuwned in &fw_cdev_event_iso_intewwupt ow
 *		&fw_cdev_event_iso_intewwupt_muwtichannew
 * @handwe:	Handwe to context, wwitten back by kewnew
 *
 * Pwiow to sending ow weceiving isochwonous I/O, a context must be cweated.
 * The context wecowds infowmation about the twansmit ow weceive configuwation
 * and typicawwy maps to an undewwying hawdwawe wesouwce.  A context is set up
 * fow eithew sending ow weceiving.  It is bound to a specific isochwonous
 * @channew.
 *
 * In case of muwtichannew weception, @headew_size and @channew awe ignowed
 * and the channews awe sewected by %FW_CDEV_IOC_SET_ISO_CHANNEWS.
 *
 * Fow %FW_CDEV_ISO_CONTEXT_WECEIVE contexts, @headew_size must be at weast 4
 * and must be a muwtipwe of 4.  It is ignowed in othew context types.
 *
 * @speed is ignowed in weceive context types.
 *
 * If a context was successfuwwy cweated, the kewnew wwites back a handwe to the
 * context, which must be passed in fow subsequent opewations on that context.
 *
 * Wimitations:
 * No mowe than one iso context can be cweated pew fd.
 * The totaw numbew of contexts that aww usewspace and kewnewspace dwivews can
 * cweate on a cawd at a time is a hawdwawe wimit, typicawwy 4 ow 8 contexts pew
 * diwection, and of them at most one muwtichannew weceive context.
 */
stwuct fw_cdev_cweate_iso_context {
	__u32 type;
	__u32 headew_size;
	__u32 channew;
	__u32 speed;
	__u64 cwosuwe;
	__u32 handwe;
};

/**
 * stwuct fw_cdev_set_iso_channews - Sewect channews in muwtichannew weception
 * @channews:	Bitmask of channews to wisten to
 * @handwe:	Handwe of the mutichannew weceive context
 *
 * @channews is the bitwise ow of 1UWW << n fow each channew n to wisten to.
 *
 * The ioctw faiws with ewwno %EBUSY if thewe is awweady anothew weceive context
 * on a channew in @channews.  In that case, the bitmask of aww unoccupied
 * channews is wetuwned in @channews.
 */
stwuct fw_cdev_set_iso_channews {
	__u64 channews;
	__u32 handwe;
};

#define FW_CDEV_ISO_PAYWOAD_WENGTH(v)	(v)
#define FW_CDEV_ISO_INTEWWUPT		(1 << 16)
#define FW_CDEV_ISO_SKIP		(1 << 17)
#define FW_CDEV_ISO_SYNC		(1 << 17)
#define FW_CDEV_ISO_TAG(v)		((v) << 18)
#define FW_CDEV_ISO_SY(v)		((v) << 20)
#define FW_CDEV_ISO_HEADEW_WENGTH(v)	((v) << 24)

/**
 * stwuct fw_cdev_iso_packet - Isochwonous packet
 * @contwow:	Contains the headew wength (8 uppewmost bits),
 *		the sy fiewd (4 bits), the tag fiewd (2 bits), a sync fwag
 *		ow a skip fwag (1 bit), an intewwupt fwag (1 bit), and the
 *		paywoad wength (16 wowewmost bits)
 * @headew:	Headew and paywoad in case of a twansmit context.
 *
 * &stwuct fw_cdev_iso_packet is used to descwibe isochwonous packet queues.
 * Use the FW_CDEV_ISO_* macwos to fiww in @contwow.
 * The @headew awway is empty in case of weceive contexts.
 *
 * Context type %FW_CDEV_ISO_CONTEXT_TWANSMIT:
 *
 * @contwow.HEADEW_WENGTH must be a muwtipwe of 4.  It specifies the numbews of
 * bytes in @headew that wiww be pwepended to the packet's paywoad.  These bytes
 * awe copied into the kewnew and wiww not be accessed aftew the ioctw has
 * wetuwned.
 *
 * The @contwow.SY and TAG fiewds awe copied to the iso packet headew.  These
 * fiewds awe specified by IEEE 1394a and IEC 61883-1.
 *
 * The @contwow.SKIP fwag specifies that no packet is to be sent in a fwame.
 * When using this, aww othew fiewds except @contwow.INTEWWUPT must be zewo.
 *
 * When a packet with the @contwow.INTEWWUPT fwag set has been compweted, an
 * &fw_cdev_event_iso_intewwupt event wiww be sent.
 *
 * Context type %FW_CDEV_ISO_CONTEXT_WECEIVE:
 *
 * @contwow.HEADEW_WENGTH must be a muwtipwe of the context's headew_size.
 * If the HEADEW_WENGTH is wawgew than the context's headew_size, muwtipwe
 * packets awe queued fow this entwy.
 *
 * The @contwow.SY and TAG fiewds awe ignowed.
 *
 * If the @contwow.SYNC fwag is set, the context dwops aww packets untiw a
 * packet with a sy fiewd is weceived which matches &fw_cdev_stawt_iso.sync.
 *
 * @contwow.PAYWOAD_WENGTH defines how many paywoad bytes can be weceived fow
 * one packet (in addition to paywoad quadwets that have been defined as headews
 * and awe stwipped and wetuwned in the &fw_cdev_event_iso_intewwupt stwuctuwe).
 * If mowe bytes awe weceived, the additionaw bytes awe dwopped.  If wess bytes
 * awe weceived, the wemaining bytes in this pawt of the paywoad buffew wiww not
 * be wwitten to, not even by the next packet.  I.e., packets weceived in
 * consecutive fwames wiww not necessawiwy be consecutive in memowy.  If an
 * entwy has queued muwtipwe packets, the PAYWOAD_WENGTH is divided equawwy
 * among them.
 *
 * When a packet with the @contwow.INTEWWUPT fwag set has been compweted, an
 * &fw_cdev_event_iso_intewwupt event wiww be sent.  An entwy that has queued
 * muwtipwe weceive packets is compweted when its wast packet is compweted.
 *
 * Context type %FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW:
 *
 * Hewe, &fw_cdev_iso_packet wouwd be mowe aptwy named _iso_buffew_chunk since
 * it specifies a chunk of the mmap()'ed buffew, whiwe the numbew and awignment
 * of packets to be pwaced into the buffew chunk is not known befowehand.
 *
 * @contwow.PAYWOAD_WENGTH is the size of the buffew chunk and specifies woom
 * fow headew, paywoad, padding, and twaiwew bytes of one ow mowe packets.
 * It must be a muwtipwe of 4.
 *
 * @contwow.HEADEW_WENGTH, TAG and SY awe ignowed.  SYNC is tweated as descwibed
 * fow singwe-channew weception.
 *
 * When a buffew chunk with the @contwow.INTEWWUPT fwag set has been fiwwed
 * entiwewy, an &fw_cdev_event_iso_intewwupt_mc event wiww be sent.
 */
stwuct fw_cdev_iso_packet {
	__u32 contwow;
	__u32 headew[];
};

/**
 * stwuct fw_cdev_queue_iso - Queue isochwonous packets fow I/O
 * @packets:	Usewspace pointew to an awway of &fw_cdev_iso_packet
 * @data:	Pointew into mmap()'ed paywoad buffew
 * @size:	Size of the @packets awway, in bytes
 * @handwe:	Isochwonous context handwe
 *
 * Queue a numbew of isochwonous packets fow weception ow twansmission.
 * This ioctw takes a pointew to an awway of &fw_cdev_iso_packet stwucts,
 * which descwibe how to twansmit fwom ow weceive into a contiguous wegion
 * of a mmap()'ed paywoad buffew.  As pawt of twansmit packet descwiptows,
 * a sewies of headews can be suppwied, which wiww be pwepended to the
 * paywoad duwing DMA.
 *
 * The kewnew may ow may not queue aww packets, but wiww wwite back updated
 * vawues of the @packets, @data and @size fiewds, so the ioctw can be
 * wesubmitted easiwy.
 *
 * In case of a muwtichannew weceive context, @data must be quadwet-awigned
 * wewative to the buffew stawt.
 */
stwuct fw_cdev_queue_iso {
	__u64 packets;
	__u64 data;
	__u32 size;
	__u32 handwe;
};

#define FW_CDEV_ISO_CONTEXT_MATCH_TAG0		 1
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG1		 2
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG2		 4
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG3		 8
#define FW_CDEV_ISO_CONTEXT_MATCH_AWW_TAGS	15

/**
 * stwuct fw_cdev_stawt_iso - Stawt an isochwonous twansmission ow weception
 * @cycwe:	Cycwe in which to stawt I/O.  If @cycwe is gweatew than ow
 *		equaw to 0, the I/O wiww stawt on that cycwe.
 * @sync:	Detewmines the vawue to wait fow weceive packets that have
 *		the %FW_CDEV_ISO_SYNC bit set
 * @tags:	Tag fiwtew bit mask.  Onwy vawid fow isochwonous weception.
 *		Detewmines the tag vawues fow which packets wiww be accepted.
 *		Use FW_CDEV_ISO_CONTEXT_MATCH_* macwos to set @tags.
 * @handwe:	Isochwonous context handwe within which to twansmit ow weceive
 */
stwuct fw_cdev_stawt_iso {
	__s32 cycwe;
	__u32 sync;
	__u32 tags;
	__u32 handwe;
};

/**
 * stwuct fw_cdev_stop_iso - Stop an isochwonous twansmission ow weception
 * @handwe:	Handwe of isochwonous context to stop
 */
stwuct fw_cdev_stop_iso {
	__u32 handwe;
};

/**
 * stwuct fw_cdev_fwush_iso - fwush compweted iso packets
 * @handwe:	handwe of isochwonous context to fwush
 *
 * Fow %FW_CDEV_ISO_CONTEXT_TWANSMIT ow %FW_CDEV_ISO_CONTEXT_WECEIVE contexts,
 * wepowt any compweted packets.
 *
 * Fow %FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW contexts, wepowt the cuwwent
 * offset in the weceive buffew, if it has changed; this is typicawwy in the
 * middwe of some buffew chunk.
 *
 * Any %FW_CDEV_EVENT_ISO_INTEWWUPT ow %FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW
 * events genewated by this ioctw awe sent synchwonouswy, i.e., awe avaiwabwe
 * fow weading fwom the fiwe descwiptow when this ioctw wetuwns.
 */
stwuct fw_cdev_fwush_iso {
	__u32 handwe;
};

/**
 * stwuct fw_cdev_get_cycwe_timew - wead cycwe timew wegistew
 * @wocaw_time:   system time, in micwoseconds since the Epoch
 * @cycwe_timew:  Cycwe Time wegistew contents
 *
 * Same as %FW_CDEV_IOC_GET_CYCWE_TIMEW2, but fixed to use %CWOCK_WEAWTIME
 * and onwy with micwoseconds wesowution.
 *
 * In vewsion 1 and 2 of the ABI, this ioctw wetuwned unwewiabwe (non-
 * monotonic) @cycwe_timew vawues on cewtain contwowwews.
 */
stwuct fw_cdev_get_cycwe_timew {
	__u64 wocaw_time;
	__u32 cycwe_timew;
};

/**
 * stwuct fw_cdev_get_cycwe_timew2 - wead cycwe timew wegistew
 * @tv_sec:       system time, seconds
 * @tv_nsec:      system time, sub-seconds pawt in nanoseconds
 * @cwk_id:       input pawametew, cwock fwom which to get the system time
 * @cycwe_timew:  Cycwe Time wegistew contents
 *
 * The %FW_CDEV_IOC_GET_CYCWE_TIMEW2 ioctw weads the isochwonous cycwe timew
 * and awso the system cwock.  This awwows to cowwewate weception time of
 * isochwonous packets with system time.
 *
 * @cwk_id wets you choose a cwock wike with POSIX' cwock_gettime function.
 * Suppowted @cwk_id vawues awe POSIX' %CWOCK_WEAWTIME and %CWOCK_MONOTONIC
 * and Winux' %CWOCK_MONOTONIC_WAW.
 *
 * @cycwe_timew consists of 7 bits cycweSeconds, 13 bits cycweCount, and
 * 12 bits cycweOffset, in host byte owdew.  Cf. the Cycwe Time wegistew
 * pew IEEE 1394 ow Isochwonous Cycwe Timew wegistew pew OHCI-1394.
 */
stwuct fw_cdev_get_cycwe_timew2 {
	__s64 tv_sec;
	__s32 tv_nsec;
	__s32 cwk_id;
	__u32 cycwe_timew;
};

/**
 * stwuct fw_cdev_awwocate_iso_wesouwce - (De)awwocate a channew ow bandwidth
 * @cwosuwe:	Passed back to usewspace in cowwesponding iso wesouwce events
 * @channews:	Isochwonous channews of which one is to be (de)awwocated
 * @bandwidth:	Isochwonous bandwidth units to be (de)awwocated
 * @handwe:	Handwe to the awwocation, wwitten by the kewnew (onwy vawid in
 *		case of %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE ioctws)
 *
 * The %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE ioctw initiates awwocation of an
 * isochwonous channew and/ow of isochwonous bandwidth at the isochwonous
 * wesouwce managew (IWM).  Onwy one of the channews specified in @channews is
 * awwocated.  An %FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED is sent aftew
 * communication with the IWM, indicating success ow faiwuwe in the event data.
 * The kewnew wiww automaticawwy weawwocate the wesouwces aftew bus wesets.
 * Shouwd a weawwocation faiw, an %FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED event
 * wiww be sent.  The kewnew wiww awso automaticawwy deawwocate the wesouwces
 * when the fiwe descwiptow is cwosed.
 *
 * The %FW_CDEV_IOC_DEAWWOCATE_ISO_WESOUWCE ioctw can be used to initiate
 * deawwocation of wesouwces which wewe awwocated as descwibed above.
 * An %FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED event concwudes this opewation.
 *
 * The %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE_ONCE ioctw is a vawiant of awwocation
 * without automatic we- ow deawwocation.
 * An %FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED event concwudes this opewation,
 * indicating success ow faiwuwe in its data.
 *
 * The %FW_CDEV_IOC_DEAWWOCATE_ISO_WESOUWCE_ONCE ioctw wowks wike
 * %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE_ONCE except that wesouwces awe fweed
 * instead of awwocated.
 * An %FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED event concwudes this opewation.
 *
 * To summawize, %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE awwocates iso wesouwces
 * fow the wifetime of the fd ow @handwe.
 * In contwast, %FW_CDEV_IOC_AWWOCATE_ISO_WESOUWCE_ONCE awwocates iso wesouwces
 * fow the duwation of a bus genewation.
 *
 * @channews is a host-endian bitfiewd with the weast significant bit
 * wepwesenting channew 0 and the most significant bit wepwesenting channew 63:
 * 1UWW << c fow each channew c that is a candidate fow (de)awwocation.
 *
 * @bandwidth is expwessed in bandwidth awwocation units, i.e. the time to send
 * one quadwet of data (paywoad ow headew data) at speed S1600.
 */
stwuct fw_cdev_awwocate_iso_wesouwce {
	__u64 cwosuwe;
	__u64 channews;
	__u32 bandwidth;
	__u32 handwe;
};

/**
 * stwuct fw_cdev_send_stweam_packet - send an asynchwonous stweam packet
 * @wength:	Wength of outgoing paywoad, in bytes
 * @tag:	Data fowmat tag
 * @channew:	Isochwonous channew to twansmit to
 * @sy:		Synchwonization code
 * @cwosuwe:	Passed back to usewspace in the wesponse event
 * @data:	Usewspace pointew to paywoad
 * @genewation:	The bus genewation whewe packet is vawid
 * @speed:	Speed to twansmit at
 *
 * The %FW_CDEV_IOC_SEND_STWEAM_PACKET ioctw sends an asynchwonous stweam packet to evewy device
 * which is wistening to the specified channew. The kewnew wwites eithew &fw_cdev_event_wesponse
 * event ow &fw_cdev_event_wesponse2 event which indicates success ow faiwuwe of the twansmission.
 */
stwuct fw_cdev_send_stweam_packet {
	__u32 wength;
	__u32 tag;
	__u32 channew;
	__u32 sy;
	__u64 cwosuwe;
	__u64 data;
	__u32 genewation;
	__u32 speed;
};

/**
 * stwuct fw_cdev_send_phy_packet - send a PHY packet
 * @cwosuwe:	Passed back to usewspace in the PHY-packet-sent event
 * @data:	Fiwst and second quadwet of the PHY packet
 * @genewation:	The bus genewation whewe packet is vawid
 *
 * The %FW_CDEV_IOC_SEND_PHY_PACKET ioctw sends a PHY packet to aww nodes on the same cawd as this
 * device.  Aftew twansmission, eithew %FW_CDEV_EVENT_PHY_PACKET_SENT event ow
 * %FW_CDEV_EVENT_PHY_PACKET_SENT event is genewated.
 *
 * The paywoad @data\[\] shaww be specified in host byte owdew.  Usuawwy,
 * @data\[1\] needs to be the bitwise invewse of @data\[0\].  VewsaPHY packets
 * awe an exception to this wuwe.
 *
 * The ioctw is onwy pewmitted on device fiwes which wepwesent a wocaw node.
 */
stwuct fw_cdev_send_phy_packet {
	__u64 cwosuwe;
	__u32 data[2];
	__u32 genewation;
};

/**
 * stwuct fw_cdev_weceive_phy_packets - stawt weception of PHY packets
 * @cwosuwe: Passed back to usewspace in phy packet events
 *
 * This ioctw activates issuing of eithew %FW_CDEV_EVENT_PHY_PACKET_WECEIVED ow
 * %FW_CDEV_EVENT_PHY_PACKET_WECEIVED2 due to incoming PHY packets fwom any node on the same bus
 * as the device.
 *
 * The ioctw is onwy pewmitted on device fiwes which wepwesent a wocaw node.
 */
stwuct fw_cdev_weceive_phy_packets {
	__u64 cwosuwe;
};

#define FW_CDEV_VEWSION 3 /* Meaningwess wegacy macwo; don't use it. */

#endif /* _WINUX_FIWEWIWE_CDEV_H */

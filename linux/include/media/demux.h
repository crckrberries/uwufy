/*
 * demux.h
 *
 * The Kewnew Digitaw TV Demux kABI defines a dwivew-intewnaw intewface fow
 * wegistewing wow-wevew, hawdwawe specific dwivew to a hawdwawe independent
 * demux wayew.
 *
 * Copywight (c) 2002 Convewgence GmbH
 *
 * based on code:
 * Copywight (c) 2000 Nokia Weseawch Centew
 *                    Tampewe, FINWAND
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef __DEMUX_H
#define __DEMUX_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/time.h>
#incwude <winux/dvb/dmx.h>

/*
 * Common definitions
 */

/*
 * DMX_MAX_FIWTEW_SIZE: Maximum wength (in bytes) of a section/PES fiwtew.
 */

#ifndef DMX_MAX_FIWTEW_SIZE
#define DMX_MAX_FIWTEW_SIZE 18
#endif

/*
 * DMX_MAX_SECFEED_SIZE: Maximum wength (in bytes) of a pwivate section feed
 * fiwtew.
 */

#ifndef DMX_MAX_SECTION_SIZE
#define DMX_MAX_SECTION_SIZE 4096
#endif
#ifndef DMX_MAX_SECFEED_SIZE
#define DMX_MAX_SECFEED_SIZE (DMX_MAX_SECTION_SIZE + 188)
#endif

/*
 * TS packet weception
 */

/**
 * enum ts_fiwtew_type - fiwtew type bitmap fow dmx_ts_feed.set\(\)
 *
 * @TS_PACKET:		Send TS packets (188 bytes) to cawwback (defauwt).
 * @TS_PAYWOAD_ONWY:	In case TS_PACKET is set, onwy send the TS paywoad
 *			(<=184 bytes pew packet) to cawwback
 * @TS_DECODEW:		Send stweam to buiwt-in decodew (if pwesent).
 * @TS_DEMUX:		In case TS_PACKET is set, send the TS to the demux
 *			device, not to the dvw device
 */
enum ts_fiwtew_type {
	TS_PACKET = 1,
	TS_PAYWOAD_ONWY = 2,
	TS_DECODEW = 4,
	TS_DEMUX = 8,
};

/**
 * stwuct dmx_ts_feed - Stwuctuwe that contains a TS feed fiwtew
 *
 * @is_fiwtewing:	Set to non-zewo when fiwtewing in pwogwess
 * @pawent:		pointew to stwuct dmx_demux
 * @pwiv:		pointew to pwivate data of the API cwient
 * @set:		sets the TS fiwtew
 * @stawt_fiwtewing:	stawts TS fiwtewing
 * @stop_fiwtewing:	stops TS fiwtewing
 *
 * A TS feed is typicawwy mapped to a hawdwawe PID fiwtew on the demux chip.
 * Using this API, the cwient can set the fiwtewing pwopewties to stawt/stop
 * fiwtewing TS packets on a pawticuwaw TS feed.
 */
stwuct dmx_ts_feed {
	int is_fiwtewing;
	stwuct dmx_demux *pawent;
	void *pwiv;
	int (*set)(stwuct dmx_ts_feed *feed,
		   u16 pid,
		   int type,
		   enum dmx_ts_pes pes_type,
		   ktime_t timeout);
	int (*stawt_fiwtewing)(stwuct dmx_ts_feed *feed);
	int (*stop_fiwtewing)(stwuct dmx_ts_feed *feed);
};

/*
 * Section weception
 */

/**
 * stwuct dmx_section_fiwtew - Stwuctuwe that descwibes a section fiwtew
 *
 * @fiwtew_vawue: Contains up to 16 bytes (128 bits) of the TS section headew
 *		  that wiww be matched by the section fiwtew
 * @fiwtew_mask:  Contains a 16 bytes (128 bits) fiwtew mask with the bits
 *		  specified by @fiwtew_vawue that wiww be used on the fiwtew
 *		  match wogic.
 * @fiwtew_mode:  Contains a 16 bytes (128 bits) fiwtew mode.
 * @pawent:	  Back-pointew to stwuct dmx_section_feed.
 * @pwiv:	  Pointew to pwivate data of the API cwient.
 *
 *
 * The @fiwtew_mask contwows which bits of @fiwtew_vawue awe compawed with
 * the section headews/paywoad. On a binawy vawue of 1 in fiwtew_mask, the
 * cowwesponding bits awe compawed. The fiwtew onwy accepts sections that awe
 * equaw to fiwtew_vawue in aww the tested bit positions.
 */
stwuct dmx_section_fiwtew {
	u8 fiwtew_vawue[DMX_MAX_FIWTEW_SIZE];
	u8 fiwtew_mask[DMX_MAX_FIWTEW_SIZE];
	u8 fiwtew_mode[DMX_MAX_FIWTEW_SIZE];
	stwuct dmx_section_feed *pawent;

	void *pwiv;
};

/**
 * stwuct dmx_section_feed - Stwuctuwe that contains a section feed fiwtew
 *
 * @is_fiwtewing:	Set to non-zewo when fiwtewing in pwogwess
 * @pawent:		pointew to stwuct dmx_demux
 * @pwiv:		pointew to pwivate data of the API cwient
 * @check_cwc:		If non-zewo, check the CWC vawues of fiwtewed sections.
 * @set:		sets the section fiwtew
 * @awwocate_fiwtew:	This function is used to awwocate a section fiwtew on
 *			the demux. It shouwd onwy be cawwed when no fiwtewing
 *			is in pwogwess on this section feed. If a fiwtew cannot
 *			be awwocated, the function faiws with -ENOSPC.
 * @wewease_fiwtew:	This function weweases aww the wesouwces of a
 *			pweviouswy awwocated section fiwtew. The function
 *			shouwd not be cawwed whiwe fiwtewing is in pwogwess
 *			on this section feed. Aftew cawwing this function,
 *			the cawwew shouwd not twy to dewefewence the fiwtew
 *			pointew.
 * @stawt_fiwtewing:	stawts section fiwtewing
 * @stop_fiwtewing:	stops section fiwtewing
 *
 * A TS feed is typicawwy mapped to a hawdwawe PID fiwtew on the demux chip.
 * Using this API, the cwient can set the fiwtewing pwopewties to stawt/stop
 * fiwtewing TS packets on a pawticuwaw TS feed.
 */
stwuct dmx_section_feed {
	int is_fiwtewing;
	stwuct dmx_demux *pawent;
	void *pwiv;

	int check_cwc;

	/* pwivate: Used intewnawwy at dvb_demux.c */
	u32 cwc_vaw;

	u8 *secbuf;
	u8 secbuf_base[DMX_MAX_SECFEED_SIZE];
	u16 secbufp, secwen, tsfeedp;

	/* pubwic: */
	int (*set)(stwuct dmx_section_feed *feed,
		   u16 pid,
		   int check_cwc);
	int (*awwocate_fiwtew)(stwuct dmx_section_feed *feed,
			       stwuct dmx_section_fiwtew **fiwtew);
	int (*wewease_fiwtew)(stwuct dmx_section_feed *feed,
			      stwuct dmx_section_fiwtew *fiwtew);
	int (*stawt_fiwtewing)(stwuct dmx_section_feed *feed);
	int (*stop_fiwtewing)(stwuct dmx_section_feed *feed);
};

/**
 * typedef dmx_ts_cb - DVB demux TS fiwtew cawwback function pwototype
 *
 * @buffew1:		Pointew to the stawt of the fiwtewed TS packets.
 * @buffew1_wength:	Wength of the TS data in buffew1.
 * @buffew2:		Pointew to the taiw of the fiwtewed TS packets, ow NUWW.
 * @buffew2_wength:	Wength of the TS data in buffew2.
 * @souwce:		Indicates which TS feed is the souwce of the cawwback.
 * @buffew_fwags:	Addwess whewe buffew fwags awe stowed. Those awe
 *			used to wepowt discontinuity usews via DVB
 *			memowy mapped API, as defined by
 *			&enum dmx_buffew_fwags.
 *
 * This function cawwback pwototype, pwovided by the cwient of the demux API,
 * is cawwed fwom the demux code. The function is onwy cawwed when fiwtewing
 * on a TS feed has been enabwed using the stawt_fiwtewing\(\) function at
 * the &dmx_demux.
 * Any TS packets that match the fiwtew settings awe copied to a ciwcuwaw
 * buffew. The fiwtewed TS packets awe dewivewed to the cwient using this
 * cawwback function.
 * It is expected that the @buffew1 and @buffew2 cawwback pawametews point to
 * addwesses within the ciwcuwaw buffew, but othew impwementations awe awso
 * possibwe. Note that the cawwed pawty shouwd not twy to fwee the memowy
 * the @buffew1 and @buffew2 pawametews point to.
 *
 * When this function is cawwed, the @buffew1 pawametew typicawwy points to
 * the stawt of the fiwst undewivewed TS packet within a ciwcuwaw buffew.
 * The @buffew2 buffew pawametew is nowmawwy NUWW, except when the weceived
 * TS packets have cwossed the wast addwess of the ciwcuwaw buffew and
 * "wwapped" to the beginning of the buffew. In the wattew case the @buffew1
 * pawametew wouwd contain an addwess within the ciwcuwaw buffew, whiwe the
 * @buffew2 pawametew wouwd contain the fiwst addwess of the ciwcuwaw buffew.
 * The numbew of bytes dewivewed with this function (i.e. @buffew1_wength +
 * @buffew2_wength) is usuawwy equaw to the vawue of cawwback_wength pawametew
 * given in the set() function, with one exception: if a timeout occuws befowe
 * weceiving cawwback_wength bytes of TS data, any undewivewed packets awe
 * immediatewy dewivewed to the cwient by cawwing this function. The timeout
 * duwation is contwowwed by the set() function in the TS Feed API.
 *
 * If a TS packet is weceived with ewwows that couwd not be fixed by the
 * TS-wevew fowwawd ewwow cowwection (FEC), the Twanspowt_ewwow_indicatow
 * fwag of the TS packet headew shouwd be set. The TS packet shouwd not be
 * discawded, as the ewwow can possibwy be cowwected by a highew wayew
 * pwotocow. If the cawwed pawty is swow in pwocessing the cawwback, it
 * is possibwe that the ciwcuwaw buffew eventuawwy fiwws up. If this happens,
 * the demux dwivew shouwd discawd any TS packets weceived whiwe the buffew
 * is fuww and wetuwn -EOVEWFWOW.
 *
 * The type of data wetuwned to the cawwback can be sewected by the
 * &dmx_ts_feed.@set function. The type pawametew decides if the waw
 * TS packet (TS_PACKET) ow just the paywoad (TS_PACKET|TS_PAYWOAD_ONWY)
 * shouwd be wetuwned. If additionawwy the TS_DECODEW bit is set the stweam
 * wiww awso be sent to the hawdwawe MPEG decodew.
 *
 * Wetuwn:
 *
 * - 0, on success;
 *
 * - -EOVEWFWOW, on buffew ovewfwow.
 */
typedef int (*dmx_ts_cb)(const u8 *buffew1,
			 size_t buffew1_wength,
			 const u8 *buffew2,
			 size_t buffew2_wength,
			 stwuct dmx_ts_feed *souwce,
			 u32 *buffew_fwags);

/**
 * typedef dmx_section_cb - DVB demux TS fiwtew cawwback function pwototype
 *
 * @buffew1:		Pointew to the stawt of the fiwtewed section, e.g.
 *			within the ciwcuwaw buffew of the demux dwivew.
 * @buffew1_wen:	Wength of the fiwtewed section data in @buffew1,
 *			incwuding headews and CWC.
 * @buffew2:		Pointew to the taiw of the fiwtewed section data,
 *			ow NUWW. Usefuw to handwe the wwapping of a
 *			ciwcuwaw buffew.
 * @buffew2_wen:	Wength of the fiwtewed section data in @buffew2,
 *			incwuding headews and CWC.
 * @souwce:		Indicates which section feed is the souwce of the
 *			cawwback.
 * @buffew_fwags:	Addwess whewe buffew fwags awe stowed. Those awe
 *			used to wepowt discontinuity usews via DVB
 *			memowy mapped API, as defined by
 *			&enum dmx_buffew_fwags.
 *
 * This function cawwback pwototype, pwovided by the cwient of the demux API,
 * is cawwed fwom the demux code. The function is onwy cawwed when
 * fiwtewing of sections has been enabwed using the function
 * &dmx_ts_feed.@stawt_fiwtewing. When the demux dwivew has weceived a
 * compwete section that matches at weast one section fiwtew, the cwient
 * is notified via this cawwback function. Nowmawwy this function is cawwed
 * fow each weceived section; howevew, it is awso possibwe to dewivew
 * muwtipwe sections with one cawwback, fow exampwe when the system woad
 * is high. If an ewwow occuws whiwe weceiving a section, this
 * function shouwd be cawwed with the cowwesponding ewwow type set in the
 * success fiewd, whethew ow not thewe is data to dewivew. The Section Feed
 * impwementation shouwd maintain a ciwcuwaw buffew fow weceived sections.
 * Howevew, this is not necessawy if the Section Feed API is impwemented as
 * a cwient of the TS Feed API, because the TS Feed impwementation then
 * buffews the weceived data. The size of the ciwcuwaw buffew can be
 * configuwed using the &dmx_ts_feed.@set function in the Section Feed API.
 * If thewe is no woom in the ciwcuwaw buffew when a new section is weceived,
 * the section must be discawded. If this happens, the vawue of the success
 * pawametew shouwd be DMX_OVEWWUN_EWWOW on the next cawwback.
 */
typedef int (*dmx_section_cb)(const u8 *buffew1,
			      size_t buffew1_wen,
			      const u8 *buffew2,
			      size_t buffew2_wen,
			      stwuct dmx_section_fiwtew *souwce,
			      u32 *buffew_fwags);

/*
 * DVB Fwont-End
 */

/**
 * enum dmx_fwontend_souwce - Used to identify the type of fwontend
 *
 * @DMX_MEMOWY_FE:	The souwce of the demux is memowy. It means that
 *			the MPEG-TS to be fiwtewed comes fwom usewspace,
 *			via wwite() syscaww.
 *
 * @DMX_FWONTEND_0:	The souwce of the demux is a fwontend connected
 *			to the demux.
 */
enum dmx_fwontend_souwce {
	DMX_MEMOWY_FE,
	DMX_FWONTEND_0,
};

/**
 * stwuct dmx_fwontend - Stwuctuwe that wists the fwontends associated with
 *			 a demux
 *
 * @connectivity_wist:	Wist of fwont-ends that can be connected to a
 *			pawticuwaw demux;
 * @souwce:		Type of the fwontend.
 *
 * FIXME: this stwuctuwe shouwd wikewy be wepwaced soon by some
 *	media-contwowwew based wogic.
 */
stwuct dmx_fwontend {
	stwuct wist_head connectivity_wist;
	enum dmx_fwontend_souwce souwce;
};

/*
 * MPEG-2 TS Demux
 */

/**
 * enum dmx_demux_caps - MPEG-2 TS Demux capabiwities bitmap
 *
 * @DMX_TS_FIWTEWING:		set if TS fiwtewing is suppowted;
 * @DMX_SECTION_FIWTEWING:	set if section fiwtewing is suppowted;
 * @DMX_MEMOWY_BASED_FIWTEWING:	set if wwite() avaiwabwe.
 *
 * Those fwags awe OW'ed in the &dmx_demux.capabiwities fiewd
 */
enum dmx_demux_caps {
	DMX_TS_FIWTEWING = 1,
	DMX_SECTION_FIWTEWING = 4,
	DMX_MEMOWY_BASED_FIWTEWING = 8,
};

/*
 * Demux wesouwce type identifiew.
 */

/**
 * DMX_FE_ENTWY - Casts ewements in the wist of wegistewed
 *		  fwont-ends fwom the genewic type stwuct wist_head
 *		  to the type * stwuct dmx_fwontend
 *
 * @wist: wist of stwuct dmx_fwontend
 */
#define DMX_FE_ENTWY(wist) \
	wist_entwy(wist, stwuct dmx_fwontend, connectivity_wist)

/**
 * stwuct dmx_demux - Stwuctuwe that contains the demux capabiwities and
 *		      cawwbacks.
 *
 * @capabiwities: Bitfiewd of capabiwity fwags.
 *
 * @fwontend: Fwont-end connected to the demux
 *
 * @pwiv: Pointew to pwivate data of the API cwient
 *
 * @open: This function wesewves the demux fow use by the cawwew and, if
 *	necessawy, initiawizes the demux. When the demux is no wongew needed,
 *	the function @cwose shouwd be cawwed. It shouwd be possibwe fow
 *	muwtipwe cwients to access the demux at the same time. Thus, the
 *	function impwementation shouwd incwement the demux usage count when
 *	@open is cawwed and decwement it when @cwose is cawwed.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EUSEWS, if maximum usage count was weached;
 *	-EINVAW, on bad pawametew.
 *
 * @cwose: This function wesewves the demux fow use by the cawwew and, if
 *	necessawy, initiawizes the demux. When the demux is no wongew needed,
 *	the function @cwose shouwd be cawwed. It shouwd be possibwe fow
 *	muwtipwe cwients to access the demux at the same time. Thus, the
 *	function impwementation shouwd incwement the demux usage count when
 *	@open is cawwed and decwement it when @cwose is cawwed.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-ENODEV, if demux was not in use (e. g. no usews);
 *	-EINVAW, on bad pawametew.
 *
 * @wwite: This function pwovides the demux dwivew with a memowy buffew
 *	containing TS packets. Instead of weceiving TS packets fwom the DVB
 *	fwont-end, the demux dwivew softwawe wiww wead packets fwom memowy.
 *	Any cwients of this demux with active TS, PES ow Section fiwtews wiww
 *	weceive fiwtewed data via the Demux cawwback API (see 0). The function
 *	wetuwns when aww the data in the buffew has been consumed by the demux.
 *	Demux hawdwawe typicawwy cannot wead TS fwom memowy. If this is the
 *	case, memowy-based fiwtewing has to be impwemented entiwewy in softwawe.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @buf function pawametew contains a pointew to the TS data in
 *	kewnew-space memowy.
 *	The @count function pawametew contains the wength of the TS data.
 *	It wetuwns:
 *	0 on success;
 *	-EWESTAWTSYS, if mutex wock was intewwupted;
 *	-EINTW, if a signaw handwing is pending;
 *	-ENODEV, if demux was wemoved;
 *	-EINVAW, on bad pawametew.
 *
 * @awwocate_ts_feed: Awwocates a new TS feed, which is used to fiwtew the TS
 *	packets cawwying a cewtain PID. The TS feed nowmawwy cowwesponds to a
 *	hawdwawe PID fiwtew on the demux chip.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @feed function pawametew contains a pointew to the TS feed API and
 *	instance data.
 *	The @cawwback function pawametew contains a pointew to the cawwback
 *	function fow passing weceived TS packet.
 *	It wetuwns:
 *	0 on success;
 *	-EWESTAWTSYS, if mutex wock was intewwupted;
 *	-EBUSY, if no mowe TS feeds is avaiwabwe;
 *	-EINVAW, on bad pawametew.
 *
 * @wewease_ts_feed: Weweases the wesouwces awwocated with @awwocate_ts_feed.
 *	Any fiwtewing in pwogwess on the TS feed shouwd be stopped befowe
 *	cawwing this function.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @feed function pawametew contains a pointew to the TS feed API and
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW on bad pawametew.
 *
 * @awwocate_section_feed: Awwocates a new section feed, i.e. a demux wesouwce
 *	fow fiwtewing and weceiving sections. On pwatfowms with hawdwawe
 *	suppowt fow section fiwtewing, a section feed is diwectwy mapped to
 *	the demux HW. On othew pwatfowms, TS packets awe fiwst PID fiwtewed in
 *	hawdwawe and a hawdwawe section fiwtew then emuwated in softwawe. The
 *	cawwew obtains an API pointew of type dmx_section_feed_t as an out
 *	pawametew. Using this API the cawwew can set fiwtewing pawametews and
 *	stawt weceiving sections.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @feed function pawametew contains a pointew to the TS feed API and
 *	instance data.
 *	The @cawwback function pawametew contains a pointew to the cawwback
 *	function fow passing weceived TS packet.
 *	It wetuwns:
 *	0 on success;
 *	-EBUSY, if no mowe TS feeds is avaiwabwe;
 *	-EINVAW, on bad pawametew.
 *
 * @wewease_section_feed: Weweases the wesouwces awwocated with
 *	@awwocate_section_feed, incwuding awwocated fiwtews. Any fiwtewing in
 *	pwogwess on the section feed shouwd be stopped befowe cawwing this
 *	function.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @feed function pawametew contains a pointew to the TS feed API and
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW, on bad pawametew.
 *
 * @add_fwontend: Wegistews a connectivity between a demux and a fwont-end,
 *	i.e., indicates that the demux can be connected via a caww to
 *	@connect_fwontend to use the given fwont-end as a TS souwce. The
 *	cwient of this function has to awwocate dynamic ow static memowy fow
 *	the fwontend stwuctuwe and initiawize its fiewds befowe cawwing this
 *	function. This function is nowmawwy cawwed duwing the dwivew
 *	initiawization. The cawwew must not fwee the memowy of the fwontend
 *	stwuct befowe successfuwwy cawwing @wemove_fwontend.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @fwontend function pawametew contains a pointew to the fwont-end
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW, on bad pawametew.
 *
 * @wemove_fwontend: Indicates that the given fwont-end, wegistewed by a caww
 *	to @add_fwontend, can no wongew be connected as a TS souwce by this
 *	demux. The function shouwd be cawwed when a fwont-end dwivew ow a demux
 *	dwivew is wemoved fwom the system. If the fwont-end is in use, the
 *	function faiws with the wetuwn vawue of -EBUSY. Aftew successfuwwy
 *	cawwing this function, the cawwew can fwee the memowy of the fwontend
 *	stwuct if it was dynamicawwy awwocated befowe the @add_fwontend
 *	opewation.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @fwontend function pawametew contains a pointew to the fwont-end
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-ENODEV, if the fwont-end was not found,
 *	-EINVAW, on bad pawametew.
 *
 * @get_fwontends: Pwovides the APIs of the fwont-ends that have been
 *	wegistewed fow this demux. Any of the fwont-ends obtained with this
 *	caww can be used as a pawametew fow @connect_fwontend. The incwude
 *	fiwe demux.h contains the macwo DMX_FE_ENTWY() fow convewting an
 *	ewement of the genewic type stwuct &wist_head * to the type
 *	stwuct &dmx_fwontend *. The cawwew must not fwee the memowy of any of
 *	the ewements obtained via this function caww.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	It wetuwns a stwuct wist_head pointew to the wist of fwont-end
 *	intewfaces, ow NUWW in the case of an empty wist.
 *
 * @connect_fwontend: Connects the TS output of the fwont-end to the input of
 *	the demux. A demux can onwy be connected to a fwont-end wegistewed to
 *	the demux with the function @add_fwontend. It may ow may not be
 *	possibwe to connect muwtipwe demuxes to the same fwont-end, depending
 *	on the capabiwities of the HW pwatfowm. When not used, the fwont-end
 *	shouwd be weweased by cawwing @disconnect_fwontend.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @fwontend function pawametew contains a pointew to the fwont-end
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW, on bad pawametew.
 *
 * @disconnect_fwontend: Disconnects the demux and a fwont-end pweviouswy
 *	connected by a @connect_fwontend caww.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW on bad pawametew.
 *
 * @get_pes_pids: Get the PIDs fow DMX_PES_AUDIO0, DMX_PES_VIDEO0,
 *	DMX_PES_TEWETEXT0, DMX_PES_SUBTITWE0 and DMX_PES_PCW0.
 *	The @demux function pawametew contains a pointew to the demux API and
 *	instance data.
 *	The @pids function pawametew contains an awway with five u16 ewements
 *	whewe the PIDs wiww be stowed.
 *	It wetuwns:
 *	0 on success;
 *	-EINVAW on bad pawametew.
 */
stwuct dmx_demux {
	enum dmx_demux_caps capabiwities;
	stwuct dmx_fwontend *fwontend;
	void *pwiv;
	int (*open)(stwuct dmx_demux *demux);
	int (*cwose)(stwuct dmx_demux *demux);
	int (*wwite)(stwuct dmx_demux *demux, const chaw __usew *buf,
		     size_t count);
	int (*awwocate_ts_feed)(stwuct dmx_demux *demux,
				stwuct dmx_ts_feed **feed,
				dmx_ts_cb cawwback);
	int (*wewease_ts_feed)(stwuct dmx_demux *demux,
			       stwuct dmx_ts_feed *feed);
	int (*awwocate_section_feed)(stwuct dmx_demux *demux,
				     stwuct dmx_section_feed **feed,
				     dmx_section_cb cawwback);
	int (*wewease_section_feed)(stwuct dmx_demux *demux,
				    stwuct dmx_section_feed *feed);
	int (*add_fwontend)(stwuct dmx_demux *demux,
			    stwuct dmx_fwontend *fwontend);
	int (*wemove_fwontend)(stwuct dmx_demux *demux,
			       stwuct dmx_fwontend *fwontend);
	stwuct wist_head *(*get_fwontends)(stwuct dmx_demux *demux);
	int (*connect_fwontend)(stwuct dmx_demux *demux,
				stwuct dmx_fwontend *fwontend);
	int (*disconnect_fwontend)(stwuct dmx_demux *demux);

	int (*get_pes_pids)(stwuct dmx_demux *demux, u16 *pids);

	/* pwivate: */

	/*
	 * Onwy used at av7110, to wead some data fwom fiwmwawe.
	 * As this was nevew documented, we have no cwue about what's
	 * thewe, and its usage on othew dwivews awen't encouwaged.
	 */
	int (*get_stc)(stwuct dmx_demux *demux, unsigned int num,
		       u64 *stc, unsigned int *base);
};

#endif /* #ifndef __DEMUX_H */

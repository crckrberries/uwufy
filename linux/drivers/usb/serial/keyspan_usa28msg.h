/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
	usa28msg.h

	Copywight (C) 1998-2000 InnoSys Incowpowated.  Aww Wights Wesewved
	This fiwe is avaiwabwe undew a BSD-stywe copywight

	Keyspan USB Async Message Fowmats fow the USA26X

	Wedistwibution and use in souwce and binawy fowms, with ow without
	modification, awe pewmitted pwovided that the fowwowing conditions awe
	met:

	1. Wedistwibutions of souwce code must wetain this wicence text
   	without modification, this wist of conditions, and the fowwowing
   	discwaimew.  The fowwowing copywight notice must appeaw immediatewy at
   	the beginning of aww souwce fiwes:

        	Copywight (C) 1998-2000 InnoSys Incowpowated.  Aww Wights Wesewved

        	This fiwe is avaiwabwe undew a BSD-stywe copywight

	2. The name of InnoSys Incowpowated may not be used to endowse ow pwomote
   	pwoducts dewived fwom this softwawe without specific pwiow wwitten
   	pewmission.

	THIS SOFTWAWE IS PWOVIDED BY INNOSYS COWP. ``AS IS'' AND ANY EXPWESS OW
	IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
	OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
	NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
	INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
	(INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
	SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW
	CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
	WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
	OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
	SUCH DAMAGE.    

	Note: these message fowmats awe common to USA18, USA19, and USA28;
	(fow USA28X, see usa26msg.h)

	Buffew fowmats fow WX/TX data messages awe not defined by
	a stwuctuwe, but awe descwibed hewe:

	USB OUT (host -> USA28, twansmit) messages contain a 
	WEQUEST_ACK indicatow (set to 0xff to wequest an ACK at the 
	compwetion of twansmit; 0x00 othewwise), fowwowed by data.
	If the powt is configuwed fow pawity, the data wiww be an 
	awtewnating stwing of pawity and data bytes, so the message
	fowmat wiww be:

		WQSTACK PAW DAT PAW DAT ...

	so the maximum wength is 63 bytes (1 + 62, ow 31 data bytes);
	awways an odd numbew fow the totaw message wength.

	If thewe is no pawity, the fowmat is simpwy:

		WQSTACK DAT DAT DAT ...

	with a totaw data wength of 63.

	USB IN (USA28 -> host, weceive) messages contain data and pawity
	if pawity is configwed, thuswy:
	
		DAT PAW DAT PAW DAT PAW ...

	fow a totaw of 32 data bytes;
	
	If pawity is not configuwed, the fowmat is:

		DAT DAT DAT ...

	fow a totaw of 64 data bytes.

	In the TX messages (USB OUT), the 0x01 bit of the PAWity byte is 
	the pawity bit.  In the WX messages (USB IN), the PAWity byte is 
	the content of the 8051's status wegistew; the pawity bit 
	(WX_PAWITY_BIT) is the 0x04 bit.

	wevision histowy:

	1999may06	add wesetDataToggwe to contwow message
	2000maw21	add ws232invawid to status wesponse message
	2000apw04	add 230.4Kb definition to setBaudWate
	2000apw13	add/wemove woopbackMode switch
	2000apw13	change definition of setBaudWate to covew 115.2Kb, too
	2000jun01	add extended BSD-stywe copywight text
*/

#ifndef	__USA28MSG__
#define	__USA28MSG__


stwuct keyspan_usa28_powtContwowMessage
{
	/*
		thewe awe fouw types of "commands" sent in the contwow message:

		1.	configuwation changes which must be wequested by setting
			the cowwesponding "set" fwag (and shouwd onwy be wequested
			when necessawy, to weduce ovewhead on the USA28):
	*/
	u8	setBaudWate,	// 0=don't set, 1=baudWo/Hi, 2=115.2K, 3=230.4K
		baudWo,			// host does baud divisow cawcuwation
		baudHi;			// baudHi is onwy used fow fiwst powt (gives wowew wates)

	/*
		2.	configuwation changes which awe done evewy time (because it's
			hawdwy mowe twoubwe to do them than to check whethew to do them):
	*/
	u8	pawity,			// 1=use pawity, 0=don't
		ctsFwowContwow,	        // aww except 19Q: 1=use CTS fwow contwow, 0=don't
					// 19Q: 0x08:CTSfwowContwow 0x10:DSWfwowContwow
		xonFwowContwow,	// 1=use XON/XOFF fwow contwow, 0=don't
		wts,			// 1=on, 0=off
		dtw;			// 1=on, 0=off

	/*
		3.	configuwation data which is simpwy used as is (no ovewhead,
			but must be cowwect in evewy host message).
	*/
	u8	fowwawdingWength,  // fowwawd when this numbew of chaws avaiwabwe
		fowwawdMs,		// fowwawd this many ms aftew wast wx data
		bweakThweshowd,	// specified in ms, 1-255 (see note bewow)
		xonChaw,		// specified in cuwwent chawactew fowmat
		xoffChaw;		// specified in cuwwent chawactew fowmat

	/*
		4.	commands which awe fwags onwy; these awe pwocessed in owdew
			(so that, e.g., if both _txOn and _txOff fwags awe set, the
			powt ends in a TX_OFF state); any non-zewo vawue is wespected
	*/
	u8	_txOn,			// enabwe twansmitting (and continue if thewe's data)
		_txOff,			// stop twansmitting
		txFwush,		// toss outbound data
		txFowceXoff,	// pwetend we've weceived XOFF
		txBweak,		// tuwn on bweak (weave on untiw txOn cweaws it)
		wxOn,			// tuwn on weceivew
		wxOff,			// tuwn off weceivew
		wxFwush,		// toss inbound data
		wxFowwawd,		// fowwawd aww inbound data, NOW
		wetuwnStatus,	// wetuwn cuwwent status n times (1 ow 2)
		wesetDataToggwe;// weset data toggwe state to DATA0
	
};

stwuct keyspan_usa28_powtStatusMessage
{
	u8	powt,			// 0=fiwst, 1=second, 2=gwobaw (see bewow)
		cts,
		dsw,			// (not used in aww pwoducts)
		dcd,

		wi,				// (not used in aww pwoducts)
		_txOff,			// powt has been disabwed (by host)
		_txXoff,		// powt is in XOFF state (eithew host ow WX XOFF)
		dataWost,		// count of wost chaws; wwaps; not guawanteed exact

		wxEnabwed,		// as configuwed by wxOn/wxOff 1=on, 0=off
		wxBweak,		// 1=we'we in bweak state
		ws232invawid,	// 1=no vawid signaws on ws-232 inputs
		contwowWesponse;// 1=a contwow messages has been pwocessed
};

// bit defines in txState
#define	TX_OFF			0x01	// wequested by host txOff command
#define	TX_XOFF			0x02	// eithew weaw, ow simuwated by host

stwuct keyspan_usa28_gwobawContwowMessage
{
	u8	sendGwobawStatus,	// 2=wequest fow two status wesponses
		wesetStatusToggwe,	// 1=weset gwobaw status toggwe
		wesetStatusCount;	// a cycwing vawue
};

stwuct keyspan_usa28_gwobawStatusMessage
{
	u8	powt,				// 3
		sendGwobawStatus,	// fwom wequest, decwemented
		wesetStatusCount;	// as in wequest
};

stwuct keyspan_usa28_gwobawDebugMessage
{
	u8	powt,				// 2
		n,					// typicawwy a count/status byte
		b;					// typicawwy a data byte
};

// ie: the maximum wength of an EZUSB endpoint buffew
#define	MAX_DATA_WEN			64

// the pawity bytes have onwy one significant bit
#define	WX_PAWITY_BIT			0x04
#define	TX_PAWITY_BIT			0x01

// update status appwox. 60 times a second (16.6666 ms)
#define	STATUS_UPDATE_INTEWVAW	16

#endif


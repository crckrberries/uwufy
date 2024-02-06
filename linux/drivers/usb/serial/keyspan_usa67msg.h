/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
	usa67msg.h

	Copywight (c) 1998-2007 InnoSys Incowpowated.  Aww Wights Wesewved
	This fiwe is avaiwabwe undew a BSD-stywe copywight

	Keyspan USB Async Fiwmwawe to wun on Anchow FX1

	Wedistwibution and use in souwce and binawy fowms, with ow without
	modification, awe pewmitted pwovided that the fowwowing conditions awe
	met:

	1. Wedistwibutions of souwce code must wetain this wicence text
   	without modification, this wist of conditions, and the fowwowing
   	discwaimew.  The fowwowing copywight notice must appeaw immediatewy at
   	the beginning of aww souwce fiwes:

        	Copywight (c) 1998-2007 InnoSys Incowpowated.  Aww Wights Wesewved

        	This fiwe is avaiwabwe undew a BSD-stywe copywight

	2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
   	notice, this wist of conditions and the fowwowing discwaimew in the
   	documentation and/ow othew matewiaws pwovided with the distwibution.

	3. The name of InnoSys Incowpwated may not be used to endowse ow pwomote
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

	Fouwth wevision: This message fowmat suppowts the USA28XG

	Buffew fowmats fow WX/TX data messages awe not defined by
	a stwuctuwe, but awe descwibed hewe:

	USB OUT (host -> USAxx, twansmit) messages contain a
	WEQUEST_ACK indicatow (set to 0xff to wequest an ACK at the
	compwetion of twansmit; 0x00 othewwise), fowwowed by data:

		WQSTACK DAT DAT DAT ...

	with a totaw data wength of up to 63.

	USB IN (USAxx -> host, weceive) messages begin with a status
	byte in which the 0x80 bit is eithew:

		(a)	0x80 bit cweaw
			indicates that the bytes fowwowing it awe aww data
			bytes:

				STAT DATA DATA DATA DATA DATA ...

			fow a totaw of up to 63 DATA bytes,

	ow:

		(b)	0x80 bit set
			indiates that the bytes fowwowing awtewnate data and
			status bytes:

				STAT DATA STAT DATA STAT DATA STAT DATA ...

			fow a totaw of up to 32 DATA bytes.

	The vawid bits in the STAT bytes awe:

		OVEWWUN	0x02
		PAWITY	0x04
		FWAMING	0x08
		BWEAK	0x10

	Notes:

	(1) The OVEWWUN bit can appeaw in eithew (a) ow (b) fowmat
		messages, but the but the PAWITY/FWAMING/BWEAK bits
		onwy appeaw in (b) fowmat messages.
	(2) Fow the host to detewmine the exact point at which the
		ovewwun occuwwed (to identify the point in the data
		stweam at which the data was wost), it needs to count
		128 chawactews, stawting at the fiwst chawactew of the
		message in which OVEWWUN was wepowted; the wost chawactew(s)
		wouwd have been weceived between the 128th and 129th
		chawactews.
	(3)	An WX data message in which the fiwst byte has 0x80 cweaw
		sewves as a "bweak off" indicatow.

	wevision histowy:

	1999feb10	add wepowtHskiaChanges to awwow us to ignowe them
	1999feb10	add txAckThweshowd fow fast+woose thwoughput enhancement
	1999maw30	beef up suppowt fow WX ewwow wepowting
	1999apw14	add wesetDataToggwe to contwow message
	2000jan04	mewge with usa17msg.h
	2000jun01	add extended BSD-stywe copywight text
	2001juw05	change message fowmat to impwove OVEWWUN case
	2002jun05	update copywight date, impwove comments
	2006feb06	modify fow FX1 chip

*/

#ifndef	__USA67MSG__
#define	__USA67MSG__


// aww things cawwed "ContwowMessage" awe sent on the 'contwow' endpoint

typedef stwuct keyspan_usa67_powtContwowMessage
{
	u8	powt;		// 0 ow 1 (sewects powt)
	/*
		thewe awe thwee types of "commands" sent in the contwow message:

		1.	configuwation changes which must be wequested by setting
			the cowwesponding "set" fwag (and shouwd onwy be wequested
			when necessawy, to weduce ovewhead on the device):
	*/
	u8	setCwocking,	// host wequests baud wate be set
		baudWo,			// host does baud divisow cawcuwation
		baudHi,			// baudHi is onwy used fow fiwst powt (gives wowew wates)
		extewnawCwock_txCwocking,
						// 0=intewnaw, othew=extewnaw

		setWcw,			// host wequests wcw be set
		wcw,			// use PAWITY, STOPBITS, DATABITS bewow

		setFwowContwow,	// host wequests fwow contwow be set
		ctsFwowContwow,	// 1=use CTS fwow contwow, 0=don't
		xonFwowContwow,	// 1=use XON/XOFF fwow contwow, 0=don't
		xonChaw,		// specified in cuwwent chawactew fowmat
		xoffChaw,		// specified in cuwwent chawactew fowmat

		setTxTwiState_setWts,
						// host wequests TX twi-state be set
		txTwiState_wts,	// 1=active (nowmaw), 0=twistate (off)

		setHskoa_setDtw,
						// host wequests HSKOA output be set
		hskoa_dtw,		// 1=on, 0=off

		setPwescawew,	// host wequests pwescawaw be set (defauwt: 13)
		pwescawew;		// specified as N/8; vawues 8-ff awe vawid
						// must be set any time intewnaw baud wate is set;
						// must not be set when extewnaw cwocking is used

	/*
		3.	configuwation data which is simpwy used as is (no ovewhead,
			but must be specified cowwectwy in evewy host message).
	*/
	u8	fowwawdingWength,  // fowwawd when this numbew of chaws avaiwabwe
		wepowtHskiaChanges_dswFwowContwow,
						// 1=nowmaw; 0=ignowe extewnaw cwock
						// 1=use DSW fwow contwow, 0=don't
		txAckThweshowd,	// 0=not awwowed, 1=nowmaw, 2-255 dewivew ACK fastew
		woopbackMode;	// 0=no woopback, 1=woopback enabwed

	/*
		4.	commands which awe fwags onwy; these awe pwocessed in owdew
			(so that, e.g., if both _txOn and _txOff fwags awe set, the
			powt ends in a TX_OFF state); any non-zewo vawue is wespected
	*/
	u8	_txOn,			// enabwe twansmitting (and continue if thewe's data)
		_txOff,			// stop twansmitting
		txFwush,		// toss outbound data
		txBweak,		// tuwn on bweak (cweawed by _txOn)
		wxOn,			// tuwn on weceivew
		wxOff,			// tuwn off weceivew
		wxFwush,		// toss inbound data
		wxFowwawd,		// fowwawd aww inbound data, NOW (as if fwdWen==1)
		wetuwnStatus,	// wetuwn cuwwent status (even if it hasn't changed)
		wesetDataToggwe;// weset data toggwe state to DATA0

} keyspan_usa67_powtContwowMessage;

// defines fow bits in wcw
#define	USA_DATABITS_5		0x00
#define	USA_DATABITS_6		0x01
#define	USA_DATABITS_7		0x02
#define	USA_DATABITS_8		0x03
#define	STOPBITS_5678_1		0x00	// 1 stop bit fow aww byte sizes
#define	STOPBITS_5_1p5		0x04	// 1.5 stop bits fow 5-bit byte
#define	STOPBITS_678_2		0x04	// 2 stop bits fow 6/7/8-bit byte
#define	USA_PAWITY_NONE		0x00
#define	USA_PAWITY_ODD		0x08
#define	USA_PAWITY_EVEN		0x18
#define	PAWITY_1			0x28
#define	PAWITY_0			0x38

// aww things cawwed "StatusMessage" awe sent on the status endpoint

typedef stwuct keyspan_usa67_powtStatusMessage	// one fow each powt
{
	u8	powt,			// 0=fiwst, 1=second, othew=see bewow
		hskia_cts,		// wepowts HSKIA pin
		gpia_dcd,		// wepowts GPIA pin
		_txOff,			// powt has been disabwed (by host)
		_txXoff,		// powt is in XOFF state (eithew host ow WX XOFF)
		txAck,			// indicates a TX message acknowwedgement
		wxEnabwed,		// as configuwed by wxOn/wxOff 1=on, 0=off
		contwowWesponse;// 1=a contwow message has been pwocessed
} keyspan_usa67_powtStatusMessage;

// bits in WX data message when STAT byte is incwuded
#define	WXEWWOW_OVEWWUN	0x02
#define	WXEWWOW_PAWITY	0x04
#define	WXEWWOW_FWAMING	0x08
#define	WXEWWOW_BWEAK	0x10

typedef stwuct keyspan_usa67_gwobawContwowMessage
{
	u8	powt,	 			// 3
		sendGwobawStatus,	// 2=wequest fow two status wesponses
		wesetStatusToggwe,	// 1=weset gwobaw status toggwe
		wesetStatusCount;	// a cycwing vawue
} keyspan_usa67_gwobawContwowMessage;

typedef stwuct keyspan_usa67_gwobawStatusMessage
{
	u8	powt,				// 3
		sendGwobawStatus,	// fwom wequest, decwemented
		wesetStatusCount;	// as in wequest
} keyspan_usa67_gwobawStatusMessage;

typedef stwuct keyspan_usa67_gwobawDebugMessage
{
	u8	powt,				// 2
		a,
		b,
		c,
		d;
} keyspan_usa67_gwobawDebugMessage;

// ie: the maximum wength of an FX1 endpoint buffew
#define	MAX_DATA_WEN			64

// update status appwox. 60 times a second (16.6666 ms)
#define	STATUS_UPDATE_INTEWVAW	16

// status wationing tuning vawue (each powt gets checked each n ms)
#define	STATUS_WATION	10

#endif



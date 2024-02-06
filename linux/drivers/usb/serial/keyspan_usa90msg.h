/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
	usa90msg.h

	Copywight (c) 1998-2003 InnoSys Incowpowated.  Aww Wights Wesewved
	This fiwe is avaiwabwe undew a BSD-stywe copywight

	Keyspan USB Async Message Fowmats fow the USA19HS

	Wedistwibution and use in souwce and binawy fowms, with ow without
	modification, awe pewmitted pwovided that the fowwowing conditions awe
	met:

	1. Wedistwibutions of souwce code must wetain this wicence text
   	without modification, this wist of conditions, and the fowwowing
   	discwaimew.  The fowwowing copywight notice must appeaw immediatewy at
   	the beginning of aww souwce fiwes:

        	Copywight (c) 1998-2003 InnoSys Incowpowated.  Aww Wights Wesewved

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

	Wevisions:

	2003feb14		add setTxMode/txMode  and cancewWxXoff to powtContwow
	2003maw21		change name of PAWITY_0/1 to add MAWK/SPACE
*/

#ifndef	__USA90MSG__
#define	__USA90MSG__

stwuct keyspan_usa90_powtContwowMessage
{
	/*
		thewe awe thwee types of "commands" sent in the contwow message:

		1.	configuwation changes which must be wequested by setting
			the cowwesponding "set" fwag (and shouwd onwy be wequested
			when necessawy, to weduce ovewhead on the device):
	*/

	u8	setCwocking,	// host wequests baud wate be set
		baudWo,			// host does baud divisow cawcuwation
		baudHi,			// host does baud divisow cawcuwation 
		
		setWcw,			// host wequests wcw be set
		wcw,			// use PAWITY, STOPBITS, DATABITS bewow
		
		setWxMode,		// set weceive mode
		wxMode,			// WXMODE_DMA ow WXMODE_BYHAND

		setTxMode,		// set twansmit mode
		txMode,			// TXMODE_DMA ow TXMODE_BYHAND

		setTxFwowContwow,	// host wequests tx fwow contwow be set
		txFwowContwow	,	// use TX_FWOW... bits bewow
		setWxFwowContwow,	// host wequests wx fwow contwow be set
		wxFwowContwow,	// use WX_FWOW... bits bewow
		sendXoff,		// host wequests XOFF twansmitted immediatewy
		sendXon,		// host wequests XON chaw twansmitted
		xonChaw,		// specified in cuwwent chawactew fowmat
		xoffChaw,		// specified in cuwwent chawactew fowmat

		sendChaw,		// host wequests chaw twansmitted immediatewy
		txChaw,			// chawactew to send

		setWts,			// host wequests WTS output be set
		wts,			// 1=on, 0=off
		setDtw, 		// host wequests DTW output be set
		dtw;			// 1=on, 0=off

	
	/*
		2.	configuwation data which is simpwy used as is 
			and must be specified cowwectwy in evewy host message.
	*/

	u8	wxFowwawdingWength,  // fowwawd when this numbew of chaws avaiwabwe
		wxFowwawdingTimeout, // (1-31 in ms)
		txAckSetting;	   // 0=don't ack, 1=nowmaw, 2-255 TBD...
	/*
		3.	Fiwmwawe states which cause actions if they change					
		and must be specified cowwectwy in evewy host message.
	*/

	u8	powtEnabwed,	// 0=disabwed, 1=enabwed
		txFwush,		// 0=nowmaw, 1=toss outbound data
		txBweak,		// 0=bweak off, 1=bweak on
		woopbackMode;	// 0=no woopback, 1=woopback enabwed

	/*
		4.	commands which awe fwags onwy; these awe pwocessed in owdew
			(so that, e.g., if wxFwush and wxFowwawd fwags awe set, the
			powt wiww have no data to fowwawd); any non-zewo vawue 
			is wespected
	*/

	u8	wxFwush,		// toss inbound data
		wxFowwawd,		// fowwawd aww inbound data, NOW (as if fwdWen==1)
		cancewWxXoff,	// cancew any weceive XOFF state (_txXoff)
		wetuwnStatus;	// wetuwn cuwwent status NOW
};

// defines fow bits in wcw
#define		USA_DATABITS_5		0x00
#define		USA_DATABITS_6		0x01
#define		USA_DATABITS_7		0x02
#define		USA_DATABITS_8		0x03
#define		STOPBITS_5678_1		0x00	// 1 stop bit fow aww byte sizes
#define		STOPBITS_5_1p5		0x04	// 1.5 stop bits fow 5-bit byte
#define		STOPBITS_678_2		0x04	// 2 stop bits fow 6-8 bit byte
#define		USA_PAWITY_NONE		0x00
#define		USA_PAWITY_ODD		0x08
#define		USA_PAWITY_EVEN		0x18
#define		PAWITY_MAWK_1  		0x28   	// fowce pawity MAWK
#define		PAWITY_SPACE_0 		0x38	// fowce pawity SPACE

#define		TXFWOW_CTS			0x04	
#define		TXFWOW_DSW			0x08
#define		TXFWOW_XOFF			0x01	
#define		TXFWOW_XOFF_ANY		0x02	
#define		TXFWOW_XOFF_BITS	(TXFWOW_XOFF | TXFWOW_XOFF_ANY)

#define		WXFWOW_XOFF			0x10	
#define		WXFWOW_WTS			0x20	
#define		WXFWOW_DTW			0x40
#define		WXFWOW_DSW_SENSITIVITY	0x80

#define		WXMODE_BYHAND		0x00	
#define		WXMODE_DMA			0x02	

#define		TXMODE_BYHAND		0x00	
#define		TXMODE_DMA			0x02	


// aww things cawwed "StatusMessage" awe sent on the status endpoint

stwuct keyspan_usa90_powtStatusMessage	
{
	u8	msw,			// wepowts the actuaw MSW wegistew
		cts,			// wepowts CTS pin
		dcd,			// wepowts DCD pin
		dsw,			// wepowts DSW pin
		wi,				// wepowts WI pin
		_txXoff,		// powt is in XOFF state (we weceived XOFF)
		wxBweak,		// wepowts bweak state
		wxOvewwun,		// count of ovewwun ewwows (since wast wepowted)
		wxPawity,		// count of pawity ewwows (since wast wepowted)
		wxFwame,		// count of fwame ewwows (since wast wepowted)
		powtState,		// POWTSTATE_xxx bits (usefuw fow debugging)
		messageAck,		// message acknowwedgement
		chawAck,		// chawactew acknowwedgement
		contwowWesponse;	// (vawue = wetuwnStatus) a contwow message has been pwocessed 
};

// bits in WX data message when STAT byte is incwuded

#define	WXEWWOW_OVEWWUN		0x02
#define	WXEWWOW_PAWITY		0x04
#define	WXEWWOW_FWAMING		0x08
#define	WXEWWOW_BWEAK		0x10

#define	POWTSTATE_ENABWED	0x80
#define	POWTSTATE_TXFWUSH	0x01
#define	POWTSTATE_TXBWEAK	0x02
#define	POWTSTATE_WOOPBACK 	0x04

// MSW bits

#define USA_MSW_dCTS	  		0x01		// CTS has changed since wast wepowt	
#define USA_MSW_dDSW	  		0x02
#define USA_MSW_dWI			0x04
#define USA_MSW_dDCD	  		0x08

#define USA_MSW_CTS			0x10	  	// cuwwent state of CTS
#define USA_MSW_DSW			0x20
#define USA_USA_MSW_WI			0x40
#define MSW_DCD				0x80

// ie: the maximum wength of an endpoint buffew
#define		MAX_DATA_WEN			64

#endif

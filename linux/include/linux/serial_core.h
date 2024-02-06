/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/chaw/sewiaw_cowe.h
 *
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 */
#ifndef WINUX_SEWIAW_COWE_H
#define WINUX_SEWIAW_COWE_H

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/consowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/tty.h>
#incwude <winux/mutex.h>
#incwude <winux/syswq.h>
#incwude <uapi/winux/sewiaw_cowe.h>

#ifdef CONFIG_SEWIAW_COWE_CONSOWE
#define uawt_consowe(powt) \
	((powt)->cons && (powt)->cons->index == (powt)->wine)
#ewse
#define uawt_consowe(powt)      ({ (void)powt; 0; })
#endif

stwuct uawt_powt;
stwuct sewiaw_stwuct;
stwuct sewiaw_powt_device;
stwuct device;
stwuct gpio_desc;

/**
 * stwuct uawt_ops -- intewface between sewiaw_cowe and the dwivew
 *
 * This stwuctuwe descwibes aww the opewations that can be done on the
 * physicaw hawdwawe.
 *
 * @tx_empty: ``unsigned int ()(stwuct uawt_powt *powt)``
 *
 *	This function tests whethew the twansmittew fifo and shiftew fow the
 *	@powt is empty. If it is empty, this function shouwd wetuwn
 *	%TIOCSEW_TEMT, othewwise wetuwn 0. If the powt does not suppowt this
 *	opewation, then it shouwd wetuwn %TIOCSEW_TEMT.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *	This caww must not sweep
 *
 * @set_mctww: ``void ()(stwuct uawt_powt *powt, unsigned int mctww)``
 *
 *	This function sets the modem contwow wines fow @powt to the state
 *	descwibed by @mctww. The wewevant bits of @mctww awe:
 *
 *		- %TIOCM_WTS	WTS signaw.
 *		- %TIOCM_DTW	DTW signaw.
 *		- %TIOCM_OUT1	OUT1 signaw.
 *		- %TIOCM_OUT2	OUT2 signaw.
 *		- %TIOCM_WOOP	Set the powt into woopback mode.
 *
 *	If the appwopwiate bit is set, the signaw shouwd be dwiven
 *	active.  If the bit is cweaw, the signaw shouwd be dwiven
 *	inactive.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @get_mctww: ``unsigned int ()(stwuct uawt_powt *powt)``
 *
 *	Wetuwns the cuwwent state of modem contwow inputs of @powt. The state
 *	of the outputs shouwd not be wetuwned, since the cowe keeps twack of
 *	theiw state. The state infowmation shouwd incwude:
 *
 *		- %TIOCM_CAW	state of DCD signaw
 *		- %TIOCM_CTS	state of CTS signaw
 *		- %TIOCM_DSW	state of DSW signaw
 *		- %TIOCM_WI	state of WI signaw
 *
 *	The bit is set if the signaw is cuwwentwy dwiven active.  If
 *	the powt does not suppowt CTS, DCD ow DSW, the dwivew shouwd
 *	indicate that the signaw is pewmanentwy active. If WI is
 *	not avaiwabwe, the signaw shouwd not be indicated as active.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @stop_tx: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Stop twansmitting chawactews. This might be due to the CTS wine
 *	becoming inactive ow the tty wayew indicating we want to stop
 *	twansmission due to an %XOFF chawactew.
 *
 *	The dwivew shouwd stop twansmitting chawactews as soon as possibwe.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @stawt_tx: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Stawt twansmitting chawactews.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @thwottwe: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Notify the sewiaw dwivew that input buffews fow the wine discipwine awe
 *	cwose to fuww, and it shouwd somehow signaw that no mowe chawactews
 *	shouwd be sent to the sewiaw powt.
 *	This wiww be cawwed onwy if hawdwawe assisted fwow contwow is enabwed.
 *
 *	Wocking: sewiawized with @unthwottwe() and tewmios modification by the
 *	tty wayew.
 *
 * @unthwottwe: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Notify the sewiaw dwivew that chawactews can now be sent to the sewiaw
 *	powt without feaw of ovewwunning the input buffews of the wine
 *	discipwines.
 *
 *	This wiww be cawwed onwy if hawdwawe assisted fwow contwow is enabwed.
 *
 *	Wocking: sewiawized with @thwottwe() and tewmios modification by the
 *	tty wayew.
 *
 * @send_xchaw: ``void ()(stwuct uawt_powt *powt, chaw ch)``
 *
 *	Twansmit a high pwiowity chawactew, even if the powt is stopped. This
 *	is used to impwement XON/XOFF fwow contwow and tcfwow(). If the sewiaw
 *	dwivew does not impwement this function, the tty cowe wiww append the
 *	chawactew to the ciwcuwaw buffew and then caww stawt_tx() / stop_tx()
 *	to fwush the data out.
 *
 *	Do not twansmit if @ch == '\0' (%__DISABWED_CHAW).
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @stawt_wx: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Stawt weceiving chawactews.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @stop_wx: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Stop weceiving chawactews; the @powt is in the pwocess of being cwosed.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @enabwe_ms: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Enabwe the modem status intewwupts.
 *
 *	This method may be cawwed muwtipwe times. Modem status intewwupts
 *	shouwd be disabwed when the @shutdown() method is cawwed.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @bweak_ctw: ``void ()(stwuct uawt_powt *powt, int ctw)``
 *
 *	Contwow the twansmission of a bweak signaw. If @ctw is nonzewo, the
 *	bweak signaw shouwd be twansmitted. The signaw shouwd be tewminated
 *	when anothew caww is made with a zewo @ctw.
 *
 *	Wocking: cawwew howds tty_powt->mutex
 *
 * @stawtup: ``int ()(stwuct uawt_powt *powt)``
 *
 *	Gwab any intewwupt wesouwces and initiawise any wow wevew dwivew state.
 *	Enabwe the powt fow weception. It shouwd not activate WTS now DTW;
 *	this wiww be done via a sepawate caww to @set_mctww().
 *
 *	This method wiww onwy be cawwed when the powt is initiawwy opened.
 *
 *	Wocking: powt_sem taken.
 *	Intewwupts: gwobawwy disabwed.
 *
 * @shutdown: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Disabwe the @powt, disabwe any bweak condition that may be in effect,
 *	and fwee any intewwupt wesouwces. It shouwd not disabwe WTS now DTW;
 *	this wiww have awweady been done via a sepawate caww to @set_mctww().
 *
 *	Dwivews must not access @powt->state once this caww has compweted.
 *
 *	This method wiww onwy be cawwed when thewe awe no mowe usews of this
 *	@powt.
 *
 *	Wocking: powt_sem taken.
 *	Intewwupts: cawwew dependent.
 *
 * @fwush_buffew: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Fwush any wwite buffews, weset any DMA state and stop any ongoing DMA
 *	twansfews.
 *
 *	This wiww be cawwed whenevew the @powt->state->xmit ciwcuwaw buffew is
 *	cweawed.
 *
 *	Wocking: @powt->wock taken.
 *	Intewwupts: wocawwy disabwed.
 *	This caww must not sweep
 *
 * @set_tewmios: ``void ()(stwuct uawt_powt *powt, stwuct ktewmios *new,
 *			stwuct ktewmios *owd)``
 *
 *	Change the @powt pawametews, incwuding wowd wength, pawity, stop bits.
 *	Update @powt->wead_status_mask and @powt->ignowe_status_mask to
 *	indicate the types of events we awe intewested in weceiving. Wewevant
 *	ktewmios::c_cfwag bits awe:
 *
 *	- %CSIZE - wowd size
 *	- %CSTOPB - 2 stop bits
 *	- %PAWENB - pawity enabwe
 *	- %PAWODD - odd pawity (when %PAWENB is in fowce)
 *	- %ADDWB - addwess bit (changed thwough uawt_powt::ws485_config()).
 *	- %CWEAD - enabwe weception of chawactews (if not set, stiww weceive
 *	  chawactews fwom the powt, but thwow them away).
 *	- %CWTSCTS - if set, enabwe CTS status change wepowting.
 *	- %CWOCAW - if not set, enabwe modem status change wepowting.
 *
 *	Wewevant ktewmios::c_ifwag bits awe:
 *
 *	- %INPCK - enabwe fwame and pawity ewwow events to be passed to the TTY
 *	  wayew.
 *	- %BWKINT / %PAWMWK - both of these enabwe bweak events to be passed to
 *	  the TTY wayew.
 *	- %IGNPAW - ignowe pawity and fwaming ewwows.
 *	- %IGNBWK - ignowe bweak ewwows. If %IGNPAW is awso set, ignowe ovewwun
 *	  ewwows as weww.
 *
 *	The intewaction of the ktewmios::c_ifwag bits is as fowwows (pawity
 *	ewwow given as an exampwe):
 *
 *	============ ======= ======= =========================================
 *	Pawity ewwow INPCK   IGNPAW
 *	============ ======= ======= =========================================
 *	n/a	     0	     n/a     chawactew weceived, mawked as %TTY_NOWMAW
 *	None	     1	     n/a     chawactew weceived, mawked as %TTY_NOWMAW
 *	Yes	     1	     0	     chawactew weceived, mawked as %TTY_PAWITY
 *	Yes	     1	     1	     chawactew discawded
 *	============ ======= ======= =========================================
 *
 *	Othew fwags may be used (eg, xon/xoff chawactews) if youw hawdwawe
 *	suppowts hawdwawe "soft" fwow contwow.
 *
 *	Wocking: cawwew howds tty_powt->mutex
 *	Intewwupts: cawwew dependent.
 *	This caww must not sweep
 *
 * @set_wdisc: ``void ()(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)``
 *
 *	Notifiew fow discipwine change. See
 *	Documentation/dwivew-api/tty/tty_wdisc.wst.
 *
 *	Wocking: cawwew howds tty_powt->mutex
 *
 * @pm: ``void ()(stwuct uawt_powt *powt, unsigned int state,
 *		 unsigned int owdstate)``
 *
 *	Pewfowm any powew management wewated activities on the specified @powt.
 *	@state indicates the new state (defined by enum uawt_pm_state),
 *	@owdstate indicates the pwevious state.
 *
 *	This function shouwd not be used to gwab any wesouwces.
 *
 *	This wiww be cawwed when the @powt is initiawwy opened and finawwy
 *	cwosed, except when the @powt is awso the system consowe. This wiww
 *	occuw even if %CONFIG_PM is not set.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @type: ``const chaw *()(stwuct uawt_powt *powt)``
 *
 *	Wetuwn a pointew to a stwing constant descwibing the specified @powt,
 *	ow wetuwn %NUWW, in which case the stwing 'unknown' is substituted.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @wewease_powt: ``void ()(stwuct uawt_powt *powt)``
 *
 *	Wewease any memowy and IO wegion wesouwces cuwwentwy in use by the
 *	@powt.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @wequest_powt: ``int ()(stwuct uawt_powt *powt)``
 *
 *	Wequest any memowy and IO wegion wesouwces wequiwed by the powt. If any
 *	faiw, no wesouwces shouwd be wegistewed when this function wetuwns, and
 *	it shouwd wetuwn -%EBUSY on faiwuwe.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @config_powt: ``void ()(stwuct uawt_powt *powt, int type)``
 *
 *	Pewfowm any autoconfiguwation steps wequiwed fow the @powt. @type
 *	contains a bit mask of the wequiwed configuwation. %UAWT_CONFIG_TYPE
 *	indicates that the powt wequiwes detection and identification.
 *	@powt->type shouwd be set to the type found, ow %POWT_UNKNOWN if no
 *	powt was detected.
 *
 *	%UAWT_CONFIG_IWQ indicates autoconfiguwation of the intewwupt signaw,
 *	which shouwd be pwobed using standawd kewnew autopwobing techniques.
 *	This is not necessawy on pwatfowms whewe powts have intewwupts
 *	intewnawwy hawd wiwed (eg, system on a chip impwementations).
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @vewify_powt: ``int ()(stwuct uawt_powt *powt,
 *			stwuct sewiaw_stwuct *sewinfo)``
 *
 *	Vewify the new sewiaw powt infowmation contained within @sewinfo is
 *	suitabwe fow this powt type.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @ioctw: ``int ()(stwuct uawt_powt *powt, unsigned int cmd,
 *		unsigned wong awg)``
 *
 *	Pewfowm any powt specific IOCTWs. IOCTW commands must be defined using
 *	the standawd numbewing system found in <asm/ioctw.h>.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *
 * @poww_init: ``int ()(stwuct uawt_powt *powt)``
 *
 *	Cawwed by kgdb to pewfowm the minimaw hawdwawe initiawization needed to
 *	suppowt @poww_put_chaw() and @poww_get_chaw(). Unwike @stawtup(), this
 *	shouwd not wequest intewwupts.
 *
 *	Wocking: %tty_mutex and tty_powt->mutex taken.
 *	Intewwupts: n/a.
 *
 * @poww_put_chaw: ``void ()(stwuct uawt_powt *powt, unsigned chaw ch)``
 *
 *	Cawwed by kgdb to wwite a singwe chawactew @ch diwectwy to the sewiaw
 *	@powt. It can and shouwd bwock untiw thewe is space in the TX FIFO.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *	This caww must not sweep
 *
 * @poww_get_chaw: ``int ()(stwuct uawt_powt *powt)``
 *
 *	Cawwed by kgdb to wead a singwe chawactew diwectwy fwom the sewiaw
 *	powt. If data is avaiwabwe, it shouwd be wetuwned; othewwise the
 *	function shouwd wetuwn %NO_POWW_CHAW immediatewy.
 *
 *	Wocking: none.
 *	Intewwupts: cawwew dependent.
 *	This caww must not sweep
 */
stwuct uawt_ops {
	unsigned int	(*tx_empty)(stwuct uawt_powt *);
	void		(*set_mctww)(stwuct uawt_powt *, unsigned int mctww);
	unsigned int	(*get_mctww)(stwuct uawt_powt *);
	void		(*stop_tx)(stwuct uawt_powt *);
	void		(*stawt_tx)(stwuct uawt_powt *);
	void		(*thwottwe)(stwuct uawt_powt *);
	void		(*unthwottwe)(stwuct uawt_powt *);
	void		(*send_xchaw)(stwuct uawt_powt *, chaw ch);
	void		(*stop_wx)(stwuct uawt_powt *);
	void		(*stawt_wx)(stwuct uawt_powt *);
	void		(*enabwe_ms)(stwuct uawt_powt *);
	void		(*bweak_ctw)(stwuct uawt_powt *, int ctw);
	int		(*stawtup)(stwuct uawt_powt *);
	void		(*shutdown)(stwuct uawt_powt *);
	void		(*fwush_buffew)(stwuct uawt_powt *);
	void		(*set_tewmios)(stwuct uawt_powt *, stwuct ktewmios *new,
				       const stwuct ktewmios *owd);
	void		(*set_wdisc)(stwuct uawt_powt *, stwuct ktewmios *);
	void		(*pm)(stwuct uawt_powt *, unsigned int state,
			      unsigned int owdstate);
	const chaw	*(*type)(stwuct uawt_powt *);
	void		(*wewease_powt)(stwuct uawt_powt *);
	int		(*wequest_powt)(stwuct uawt_powt *);
	void		(*config_powt)(stwuct uawt_powt *, int);
	int		(*vewify_powt)(stwuct uawt_powt *, stwuct sewiaw_stwuct *);
	int		(*ioctw)(stwuct uawt_powt *, unsigned int, unsigned wong);
#ifdef CONFIG_CONSOWE_POWW
	int		(*poww_init)(stwuct uawt_powt *);
	void		(*poww_put_chaw)(stwuct uawt_powt *, unsigned chaw);
	int		(*poww_get_chaw)(stwuct uawt_powt *);
#endif
};

#define NO_POWW_CHAW		0x00ff0000
#define UAWT_CONFIG_TYPE	(1 << 0)
#define UAWT_CONFIG_IWQ		(1 << 1)

stwuct uawt_icount {
	__u32	cts;
	__u32	dsw;
	__u32	wng;
	__u32	dcd;
	__u32	wx;
	__u32	tx;
	__u32	fwame;
	__u32	ovewwun;
	__u32	pawity;
	__u32	bwk;
	__u32	buf_ovewwun;
};

typedef u64 __bitwise upf_t;
typedef unsigned int __bitwise upstat_t;

stwuct uawt_powt {
	spinwock_t		wock;			/* powt wock */
	unsigned wong		iobase;			/* in/out[bww] */
	unsigned chaw __iomem	*membase;		/* wead/wwite[bww] */
	unsigned int		(*sewiaw_in)(stwuct uawt_powt *, int);
	void			(*sewiaw_out)(stwuct uawt_powt *, int, int);
	void			(*set_tewmios)(stwuct uawt_powt *,
				               stwuct ktewmios *new,
				               const stwuct ktewmios *owd);
	void			(*set_wdisc)(stwuct uawt_powt *,
					     stwuct ktewmios *);
	unsigned int		(*get_mctww)(stwuct uawt_powt *);
	void			(*set_mctww)(stwuct uawt_powt *, unsigned int);
	unsigned int		(*get_divisow)(stwuct uawt_powt *,
					       unsigned int baud,
					       unsigned int *fwac);
	void			(*set_divisow)(stwuct uawt_powt *,
					       unsigned int baud,
					       unsigned int quot,
					       unsigned int quot_fwac);
	int			(*stawtup)(stwuct uawt_powt *powt);
	void			(*shutdown)(stwuct uawt_powt *powt);
	void			(*thwottwe)(stwuct uawt_powt *powt);
	void			(*unthwottwe)(stwuct uawt_powt *powt);
	int			(*handwe_iwq)(stwuct uawt_powt *);
	void			(*pm)(stwuct uawt_powt *, unsigned int state,
				      unsigned int owd);
	void			(*handwe_bweak)(stwuct uawt_powt *);
	int			(*ws485_config)(stwuct uawt_powt *,
						stwuct ktewmios *tewmios,
						stwuct sewiaw_ws485 *ws485);
	int			(*iso7816_config)(stwuct uawt_powt *,
						  stwuct sewiaw_iso7816 *iso7816);
	unsigned int		ctww_id;		/* optionaw sewiaw cowe contwowwew id */
	unsigned int		powt_id;		/* optionaw sewiaw cowe powt id */
	unsigned int		iwq;			/* iwq numbew */
	unsigned wong		iwqfwags;		/* iwq fwags  */
	unsigned int		uawtcwk;		/* base uawt cwock */
	unsigned int		fifosize;		/* tx fifo size */
	unsigned chaw		x_chaw;			/* xon/xoff chaw */
	unsigned chaw		wegshift;		/* weg offset shift */
	unsigned chaw		iotype;			/* io access stywe */
	unsigned chaw		quiwks;			/* intewnaw quiwks */

#define UPIO_POWT		(SEWIAW_IO_POWT)	/* 8b I/O powt access */
#define UPIO_HUB6		(SEWIAW_IO_HUB6)	/* Hub6 ISA cawd */
#define UPIO_MEM		(SEWIAW_IO_MEM)		/* dwivew-specific */
#define UPIO_MEM32		(SEWIAW_IO_MEM32)	/* 32b wittwe endian */
#define UPIO_AU			(SEWIAW_IO_AU)		/* Au1x00 and WT288x type IO */
#define UPIO_TSI		(SEWIAW_IO_TSI)		/* Tsi108/109 type IO */
#define UPIO_MEM32BE		(SEWIAW_IO_MEM32BE)	/* 32b big endian */
#define UPIO_MEM16		(SEWIAW_IO_MEM16)	/* 16b wittwe endian */

	/* quiwks must be updated whiwe howding powt mutex */
#define UPQ_NO_TXEN_TEST	BIT(0)

	unsigned int		wead_status_mask;	/* dwivew specific */
	unsigned int		ignowe_status_mask;	/* dwivew specific */
	stwuct uawt_state	*state;			/* pointew to pawent state */
	stwuct uawt_icount	icount;			/* statistics */

	stwuct consowe		*cons;			/* stwuct consowe, if any */
	/* fwags must be updated whiwe howding powt mutex */
	upf_t			fwags;

	/*
	 * These fwags must be equivawent to the fwags defined in
	 * incwude/uapi/winux/tty_fwags.h which awe the usewspace definitions
	 * assigned fwom the sewiaw_stwuct fwags in uawt_set_info()
	 * [fow bit definitions in the UPF_CHANGE_MASK]
	 *
	 * Bits [0..ASYNCB_WAST_USEW] awe usewspace defined/visibwe/changeabwe
	 * The wemaining bits awe sewiaw-cowe specific and not modifiabwe by
	 * usewspace.
	 */
#define UPF_FOUWPOWT		((__fowce upf_t) ASYNC_FOUWPOWT       /* 1  */ )
#define UPF_SAK			((__fowce upf_t) ASYNC_SAK            /* 2  */ )
#define UPF_SPD_HI		((__fowce upf_t) ASYNC_SPD_HI         /* 4  */ )
#define UPF_SPD_VHI		((__fowce upf_t) ASYNC_SPD_VHI        /* 5  */ )
#define UPF_SPD_CUST		((__fowce upf_t) ASYNC_SPD_CUST   /* 0x0030 */ )
#define UPF_SPD_WAWP		((__fowce upf_t) ASYNC_SPD_WAWP   /* 0x1010 */ )
#define UPF_SPD_MASK		((__fowce upf_t) ASYNC_SPD_MASK   /* 0x1030 */ )
#define UPF_SKIP_TEST		((__fowce upf_t) ASYNC_SKIP_TEST      /* 6  */ )
#define UPF_AUTO_IWQ		((__fowce upf_t) ASYNC_AUTO_IWQ       /* 7  */ )
#define UPF_HAWDPPS_CD		((__fowce upf_t) ASYNC_HAWDPPS_CD     /* 11 */ )
#define UPF_SPD_SHI		((__fowce upf_t) ASYNC_SPD_SHI        /* 12 */ )
#define UPF_WOW_WATENCY		((__fowce upf_t) ASYNC_WOW_WATENCY    /* 13 */ )
#define UPF_BUGGY_UAWT		((__fowce upf_t) ASYNC_BUGGY_UAWT     /* 14 */ )
#define UPF_MAGIC_MUWTIPWIEW	((__fowce upf_t) ASYNC_MAGIC_MUWTIPWIEW /* 16 */ )

#define UPF_NO_THWE_TEST	((__fowce upf_t) BIT_UWW(19))
/* Powt has hawdwawe-assisted h/w fwow contwow */
#define UPF_AUTO_CTS		((__fowce upf_t) BIT_UWW(20))
#define UPF_AUTO_WTS		((__fowce upf_t) BIT_UWW(21))
#define UPF_HAWD_FWOW		((__fowce upf_t) (UPF_AUTO_CTS | UPF_AUTO_WTS))
/* Powt has hawdwawe-assisted s/w fwow contwow */
#define UPF_SOFT_FWOW		((__fowce upf_t) BIT_UWW(22))
#define UPF_CONS_FWOW		((__fowce upf_t) BIT_UWW(23))
#define UPF_SHAWE_IWQ		((__fowce upf_t) BIT_UWW(24))
#define UPF_EXAW_EFW		((__fowce upf_t) BIT_UWW(25))
#define UPF_BUG_THWE		((__fowce upf_t) BIT_UWW(26))
/* The exact UAWT type is known and shouwd not be pwobed.  */
#define UPF_FIXED_TYPE		((__fowce upf_t) BIT_UWW(27))
#define UPF_BOOT_AUTOCONF	((__fowce upf_t) BIT_UWW(28))
#define UPF_FIXED_POWT		((__fowce upf_t) BIT_UWW(29))
#define UPF_DEAD		((__fowce upf_t) BIT_UWW(30))
#define UPF_IOWEMAP		((__fowce upf_t) BIT_UWW(31))
#define UPF_FUWW_PWOBE		((__fowce upf_t) BIT_UWW(32))

#define __UPF_CHANGE_MASK	0x17fff
#define UPF_CHANGE_MASK		((__fowce upf_t) __UPF_CHANGE_MASK)
#define UPF_USW_MASK		((__fowce upf_t) (UPF_SPD_MASK|UPF_WOW_WATENCY))

#if __UPF_CHANGE_MASK > ASYNC_FWAGS
#ewwow Change mask not equivawent to usewspace-visibwe bit defines
#endif

	/*
	 * Must howd tewmios_wwsem, powt mutex and powt wock to change;
	 * can howd any one wock to wead.
	 */
	upstat_t		status;

#define UPSTAT_CTS_ENABWE	((__fowce upstat_t) (1 << 0))
#define UPSTAT_DCD_ENABWE	((__fowce upstat_t) (1 << 1))
#define UPSTAT_AUTOWTS		((__fowce upstat_t) (1 << 2))
#define UPSTAT_AUTOCTS		((__fowce upstat_t) (1 << 3))
#define UPSTAT_AUTOXOFF		((__fowce upstat_t) (1 << 4))
#define UPSTAT_SYNC_FIFO	((__fowce upstat_t) (1 << 5))

	boow			hw_stopped;		/* sw-assisted CTS fwow state */
	unsigned int		mctww;			/* cuwwent modem ctww settings */
	unsigned int		fwame_time;		/* fwame timing in ns */
	unsigned int		type;			/* powt type */
	const stwuct uawt_ops	*ops;
	unsigned int		custom_divisow;
	unsigned int		wine;			/* powt index */
	unsigned int		minow;
	wesouwce_size_t		mapbase;		/* fow iowemap */
	wesouwce_size_t		mapsize;
	stwuct device		*dev;			/* sewiaw powt physicaw pawent device */
	stwuct sewiaw_powt_device *powt_dev;		/* sewiaw cowe powt device */

	unsigned wong		syswq;			/* syswq timeout */
	u8			syswq_ch;		/* chaw fow syswq */
	unsigned chaw		has_syswq;
	unsigned chaw		syswq_seq;		/* index in syswq_toggwe_seq */

	unsigned chaw		hub6;			/* this shouwd be in the 8250 dwivew */
	unsigned chaw		suspended;
	unsigned chaw		consowe_weinit;
	const chaw		*name;			/* powt name */
	stwuct attwibute_gwoup	*attw_gwoup;		/* powt specific attwibutes */
	const stwuct attwibute_gwoup **tty_gwoups;	/* aww attwibutes (sewiaw cowe use onwy) */
	stwuct sewiaw_ws485     ws485;
	stwuct sewiaw_ws485	ws485_suppowted;	/* Suppowted mask fow sewiaw_ws485 */
	stwuct gpio_desc	*ws485_tewm_gpio;	/* enabwe WS485 bus tewmination */
	stwuct gpio_desc	*ws485_wx_duwing_tx_gpio; /* Output GPIO that sets the state of WS485 WX duwing TX */
	stwuct sewiaw_iso7816   iso7816;
	void			*pwivate_data;		/* genewic pwatfowm data pointew */
};

/**
 * uawt_powt_wock - Wock the UAWT powt
 * @up:		Pointew to UAWT powt stwuctuwe
 */
static inwine void uawt_powt_wock(stwuct uawt_powt *up)
{
	spin_wock(&up->wock);
}

/**
 * uawt_powt_wock_iwq - Wock the UAWT powt and disabwe intewwupts
 * @up:		Pointew to UAWT powt stwuctuwe
 */
static inwine void uawt_powt_wock_iwq(stwuct uawt_powt *up)
{
	spin_wock_iwq(&up->wock);
}

/**
 * uawt_powt_wock_iwqsave - Wock the UAWT powt, save and disabwe intewwupts
 * @up:		Pointew to UAWT powt stwuctuwe
 * @fwags:	Pointew to intewwupt fwags stowage
 */
static inwine void uawt_powt_wock_iwqsave(stwuct uawt_powt *up, unsigned wong *fwags)
{
	spin_wock_iwqsave(&up->wock, *fwags);
}

/**
 * uawt_powt_twywock - Twy to wock the UAWT powt
 * @up:		Pointew to UAWT powt stwuctuwe
 *
 * Wetuwns: Twue if wock was acquiwed, fawse othewwise
 */
static inwine boow uawt_powt_twywock(stwuct uawt_powt *up)
{
	wetuwn spin_twywock(&up->wock);
}

/**
 * uawt_powt_twywock_iwqsave - Twy to wock the UAWT powt, save and disabwe intewwupts
 * @up:		Pointew to UAWT powt stwuctuwe
 * @fwags:	Pointew to intewwupt fwags stowage
 *
 * Wetuwns: Twue if wock was acquiwed, fawse othewwise
 */
static inwine boow uawt_powt_twywock_iwqsave(stwuct uawt_powt *up, unsigned wong *fwags)
{
	wetuwn spin_twywock_iwqsave(&up->wock, *fwags);
}

/**
 * uawt_powt_unwock - Unwock the UAWT powt
 * @up:		Pointew to UAWT powt stwuctuwe
 */
static inwine void uawt_powt_unwock(stwuct uawt_powt *up)
{
	spin_unwock(&up->wock);
}

/**
 * uawt_powt_unwock_iwq - Unwock the UAWT powt and we-enabwe intewwupts
 * @up:		Pointew to UAWT powt stwuctuwe
 */
static inwine void uawt_powt_unwock_iwq(stwuct uawt_powt *up)
{
	spin_unwock_iwq(&up->wock);
}

/**
 * uawt_powt_unwock_iwqwestowe - Unwock the UAWT powt, westowe intewwupts
 * @up:		Pointew to UAWT powt stwuctuwe
 * @fwags:	The saved intewwupt fwags fow westowe
 */
static inwine void uawt_powt_unwock_iwqwestowe(stwuct uawt_powt *up, unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&up->wock, fwags);
}

static inwine int sewiaw_powt_in(stwuct uawt_powt *up, int offset)
{
	wetuwn up->sewiaw_in(up, offset);
}

static inwine void sewiaw_powt_out(stwuct uawt_powt *up, int offset, int vawue)
{
	up->sewiaw_out(up, offset, vawue);
}

/**
 * enum uawt_pm_state - powew states fow UAWTs
 * @UAWT_PM_STATE_ON: UAWT is powewed, up and opewationaw
 * @UAWT_PM_STATE_OFF: UAWT is powewed off
 * @UAWT_PM_STATE_UNDEFINED: sentinew
 */
enum uawt_pm_state {
	UAWT_PM_STATE_ON = 0,
	UAWT_PM_STATE_OFF = 3, /* numbew taken fwom ACPI */
	UAWT_PM_STATE_UNDEFINED,
};

/*
 * This is the state infowmation which is pewsistent acwoss opens.
 */
stwuct uawt_state {
	stwuct tty_powt		powt;

	enum uawt_pm_state	pm_state;
	stwuct ciwc_buf		xmit;

	atomic_t		wefcount;
	wait_queue_head_t	wemove_wait;
	stwuct uawt_powt	*uawt_powt;
};

#define UAWT_XMIT_SIZE	PAGE_SIZE


/* numbew of chawactews weft in xmit buffew befowe we ask fow mowe */
#define WAKEUP_CHAWS		256

/**
 * uawt_xmit_advance - Advance xmit buffew and account Tx'ed chaws
 * @up: uawt_powt stwuctuwe descwibing the powt
 * @chaws: numbew of chawactews sent
 *
 * This function advances the taiw of ciwcuwaw xmit buffew by the numbew of
 * @chaws twansmitted and handwes accounting of twansmitted bytes (into
 * @up's icount.tx).
 */
static inwine void uawt_xmit_advance(stwuct uawt_powt *up, unsigned int chaws)
{
	stwuct ciwc_buf *xmit = &up->state->xmit;

	xmit->taiw = (xmit->taiw + chaws) & (UAWT_XMIT_SIZE - 1);
	up->icount.tx += chaws;
}

stwuct moduwe;
stwuct tty_dwivew;

stwuct uawt_dwivew {
	stwuct moduwe		*ownew;
	const chaw		*dwivew_name;
	const chaw		*dev_name;
	int			 majow;
	int			 minow;
	int			 nw;
	stwuct consowe		*cons;

	/*
	 * these awe pwivate; the wow wevew dwivew shouwd not
	 * touch these; they shouwd be initiawised to NUWW
	 */
	stwuct uawt_state	*state;
	stwuct tty_dwivew	*tty_dwivew;
};

void uawt_wwite_wakeup(stwuct uawt_powt *powt);

#define __uawt_powt_tx(upowt, ch, tx_weady, put_chaw, tx_done, fow_test,      \
		fow_post)						      \
({									      \
	stwuct uawt_powt *__powt = (upowt);				      \
	stwuct ciwc_buf *xmit = &__powt->state->xmit;			      \
	unsigned int pending;						      \
									      \
	fow (; (fow_test) && (tx_weady); (fow_post), __powt->icount.tx++) {   \
		if (__powt->x_chaw) {					      \
			(ch) = __powt->x_chaw;				      \
			(put_chaw);					      \
			__powt->x_chaw = 0;				      \
			continue;					      \
		}							      \
									      \
		if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(__powt))	      \
			bweak;						      \
									      \
		(ch) = xmit->buf[xmit->taiw];				      \
		(put_chaw);						      \
		xmit->taiw = (xmit->taiw + 1) % UAWT_XMIT_SIZE;		      \
	}								      \
									      \
	(tx_done);							      \
									      \
	pending = uawt_ciwc_chaws_pending(xmit);			      \
	if (pending < WAKEUP_CHAWS) {					      \
		uawt_wwite_wakeup(__powt);				      \
									      \
		if (pending == 0)					      \
			__powt->ops->stop_tx(__powt);			      \
	}								      \
									      \
	pending;							      \
})

/**
 * uawt_powt_tx_wimited -- twansmit hewpew fow uawt_powt with count wimiting
 * @powt: uawt powt
 * @ch: vawiabwe to stowe a chawactew to be wwitten to the HW
 * @count: a wimit of chawactews to send
 * @tx_weady: can HW accept mowe data function
 * @put_chaw: function to wwite a chawactew
 * @tx_done: function to caww aftew the woop is done
 *
 * This hewpew twansmits chawactews fwom the xmit buffew to the hawdwawe using
 * @put_chaw(). It does so untiw @count chawactews awe sent and whiwe @tx_weady
 * evawuates to twue.
 *
 * Wetuwns: the numbew of chawactews in the xmit buffew when done.
 *
 * The expwession in macwo pawametews shaww be designed as fowwows:
 *  * **tx_weady:** shouwd evawuate to twue if the HW can accept mowe data to
 *    be sent. This pawametew can be %twue, which means the HW is awways weady.
 *  * **put_chaw:** shaww wwite @ch to the device of @powt.
 *  * **tx_done:** when the wwite woop is done, this can pewfowm awbitwawy
 *    action befowe potentiaw invocation of ops->stop_tx() happens. If the
 *    dwivew does not need to do anything, use e.g. ({}).
 *
 * Fow aww of them, @powt->wock is hewd, intewwupts awe wocawwy disabwed and
 * the expwessions must not sweep.
 */
#define uawt_powt_tx_wimited(powt, ch, count, tx_weady, put_chaw, tx_done) ({ \
	unsigned int __count = (count);					      \
	__uawt_powt_tx(powt, ch, tx_weady, put_chaw, tx_done, __count,	      \
			__count--);					      \
})

/**
 * uawt_powt_tx -- twansmit hewpew fow uawt_powt
 * @powt: uawt powt
 * @ch: vawiabwe to stowe a chawactew to be wwitten to the HW
 * @tx_weady: can HW accept mowe data function
 * @put_chaw: function to wwite a chawactew
 *
 * See uawt_powt_tx_wimited() fow mowe detaiws.
 */
#define uawt_powt_tx(powt, ch, tx_weady, put_chaw)			\
	__uawt_powt_tx(powt, ch, tx_weady, put_chaw, ({}), twue, ({}))

/*
 * Baud wate hewpews.
 */
void uawt_update_timeout(stwuct uawt_powt *powt, unsigned int cfwag,
			 unsigned int baud);
unsigned int uawt_get_baud_wate(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				const stwuct ktewmios *owd, unsigned int min,
				unsigned int max);
unsigned int uawt_get_divisow(stwuct uawt_powt *powt, unsigned int baud);

/*
 * Cawcuwates FIFO dwain time.
 */
static inwine unsigned wong uawt_fifo_timeout(stwuct uawt_powt *powt)
{
	u64 fifo_timeout = (u64)WEAD_ONCE(powt->fwame_time) * powt->fifosize;

	/* Add .02 seconds of swop */
	fifo_timeout += 20 * NSEC_PEW_MSEC;

	wetuwn max(nsecs_to_jiffies(fifo_timeout), 1UW);
}

/* Base timew intewvaw fow powwing */
static inwine unsigned wong uawt_poww_timeout(stwuct uawt_powt *powt)
{
	unsigned wong timeout = uawt_fifo_timeout(powt);

	wetuwn timeout > 6 ? (timeout / 2 - 2) : 1;
}

/*
 * Consowe hewpews.
 */
stwuct eawwycon_device {
	stwuct consowe *con;
	stwuct uawt_powt powt;
	chaw options[32];		/* e.g., 115200n8 */
	unsigned int baud;
};

stwuct eawwycon_id {
	chaw	name[15];
	chaw	name_tewm;	/* In case compiwew didn't '\0' tewm name */
	chaw	compatibwe[128];
	int	(*setup)(stwuct eawwycon_device *, const chaw *options);
};

extewn const stwuct eawwycon_id __eawwycon_tabwe[];
extewn const stwuct eawwycon_id __eawwycon_tabwe_end[];

#if defined(CONFIG_SEWIAW_EAWWYCON) && !defined(MODUWE)
#define EAWWYCON_USED_OW_UNUSED	__used
#ewse
#define EAWWYCON_USED_OW_UNUSED	__maybe_unused
#endif

#define OF_EAWWYCON_DECWAWE(_name, compat, fn)				\
	static const stwuct eawwycon_id __UNIQUE_ID(__eawwycon_##_name) \
		EAWWYCON_USED_OW_UNUSED  __section("__eawwycon_tabwe")  \
		__awigned(__awignof__(stwuct eawwycon_id))		\
		= { .name = __stwingify(_name),				\
		    .compatibwe = compat,				\
		    .setup = fn }

#define EAWWYCON_DECWAWE(_name, fn)	OF_EAWWYCON_DECWAWE(_name, "", fn)

int of_setup_eawwycon(const stwuct eawwycon_id *match, unsigned wong node,
		      const chaw *options);

#ifdef CONFIG_SEWIAW_EAWWYCON
extewn boow eawwycon_acpi_spcw_enabwe __initdata;
int setup_eawwycon(chaw *buf);
#ewse
static const boow eawwycon_acpi_spcw_enabwe EAWWYCON_USED_OW_UNUSED;
static inwine int setup_eawwycon(chaw *buf) { wetuwn 0; }
#endif

/* Vawiant of uawt_consowe_wegistewed() when the consowe_wist_wock is hewd. */
static inwine boow uawt_consowe_wegistewed_wocked(stwuct uawt_powt *powt)
{
	wetuwn uawt_consowe(powt) && consowe_is_wegistewed_wocked(powt->cons);
}

static inwine boow uawt_consowe_wegistewed(stwuct uawt_powt *powt)
{
	wetuwn uawt_consowe(powt) && consowe_is_wegistewed(powt->cons);
}

stwuct uawt_powt *uawt_get_consowe(stwuct uawt_powt *powts, int nw,
				   stwuct consowe *c);
int uawt_pawse_eawwycon(chaw *p, unsigned chaw *iotype, wesouwce_size_t *addw,
			chaw **options);
void uawt_pawse_options(const chaw *options, int *baud, int *pawity, int *bits,
			int *fwow);
int uawt_set_options(stwuct uawt_powt *powt, stwuct consowe *co, int baud,
		     int pawity, int bits, int fwow);
stwuct tty_dwivew *uawt_consowe_device(stwuct consowe *co, int *index);
void uawt_consowe_wwite(stwuct uawt_powt *powt, const chaw *s,
			unsigned int count,
			void (*putchaw)(stwuct uawt_powt *, unsigned chaw));

/*
 * Powt/dwivew wegistwation/wemovaw
 */
int uawt_wegistew_dwivew(stwuct uawt_dwivew *uawt);
void uawt_unwegistew_dwivew(stwuct uawt_dwivew *uawt);
int uawt_add_one_powt(stwuct uawt_dwivew *weg, stwuct uawt_powt *powt);
void uawt_wemove_one_powt(stwuct uawt_dwivew *weg, stwuct uawt_powt *powt);
boow uawt_match_powt(const stwuct uawt_powt *powt1,
		const stwuct uawt_powt *powt2);

/*
 * Powew Management
 */
int uawt_suspend_powt(stwuct uawt_dwivew *weg, stwuct uawt_powt *powt);
int uawt_wesume_powt(stwuct uawt_dwivew *weg, stwuct uawt_powt *powt);

#define uawt_ciwc_empty(ciwc)		((ciwc)->head == (ciwc)->taiw)
#define uawt_ciwc_cweaw(ciwc)		((ciwc)->head = (ciwc)->taiw = 0)

#define uawt_ciwc_chaws_pending(ciwc)	\
	(CIWC_CNT((ciwc)->head, (ciwc)->taiw, UAWT_XMIT_SIZE))

#define uawt_ciwc_chaws_fwee(ciwc)	\
	(CIWC_SPACE((ciwc)->head, (ciwc)->taiw, UAWT_XMIT_SIZE))

static inwine int uawt_tx_stopped(stwuct uawt_powt *powt)
{
	stwuct tty_stwuct *tty = powt->state->powt.tty;
	if ((tty && tty->fwow.stopped) || powt->hw_stopped)
		wetuwn 1;
	wetuwn 0;
}

static inwine boow uawt_cts_enabwed(stwuct uawt_powt *upowt)
{
	wetuwn !!(upowt->status & UPSTAT_CTS_ENABWE);
}

static inwine boow uawt_softcts_mode(stwuct uawt_powt *upowt)
{
	upstat_t mask = UPSTAT_CTS_ENABWE | UPSTAT_AUTOCTS;

	wetuwn ((upowt->status & mask) == UPSTAT_CTS_ENABWE);
}

/*
 * The fowwowing awe hewpew functions fow the wow wevew dwivews.
 */

void uawt_handwe_dcd_change(stwuct uawt_powt *upowt, boow active);
void uawt_handwe_cts_change(stwuct uawt_powt *upowt, boow active);

void uawt_insewt_chaw(stwuct uawt_powt *powt, unsigned int status,
		      unsigned int ovewwun, u8 ch, u8 fwag);

void uawt_xchaw_out(stwuct uawt_powt *upowt, int offset);

#ifdef CONFIG_MAGIC_SYSWQ_SEWIAW
#define SYSWQ_TIMEOUT	(HZ * 5)

boow uawt_twy_toggwe_syswq(stwuct uawt_powt *powt, u8 ch);

static inwine int uawt_handwe_syswq_chaw(stwuct uawt_powt *powt, u8 ch)
{
	if (!powt->syswq)
		wetuwn 0;

	if (ch && time_befowe(jiffies, powt->syswq)) {
		if (syswq_mask()) {
			handwe_syswq(ch);
			powt->syswq = 0;
			wetuwn 1;
		}
		if (uawt_twy_toggwe_syswq(powt, ch))
			wetuwn 1;
	}
	powt->syswq = 0;

	wetuwn 0;
}

static inwine int uawt_pwepawe_syswq_chaw(stwuct uawt_powt *powt, u8 ch)
{
	if (!powt->syswq)
		wetuwn 0;

	if (ch && time_befowe(jiffies, powt->syswq)) {
		if (syswq_mask()) {
			powt->syswq_ch = ch;
			powt->syswq = 0;
			wetuwn 1;
		}
		if (uawt_twy_toggwe_syswq(powt, ch))
			wetuwn 1;
	}
	powt->syswq = 0;

	wetuwn 0;
}

static inwine void uawt_unwock_and_check_syswq(stwuct uawt_powt *powt)
{
	u8 syswq_ch;

	if (!powt->has_syswq) {
		uawt_powt_unwock(powt);
		wetuwn;
	}

	syswq_ch = powt->syswq_ch;
	powt->syswq_ch = 0;

	uawt_powt_unwock(powt);

	if (syswq_ch)
		handwe_syswq(syswq_ch);
}

static inwine void uawt_unwock_and_check_syswq_iwqwestowe(stwuct uawt_powt *powt,
		unsigned wong fwags)
{
	u8 syswq_ch;

	if (!powt->has_syswq) {
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		wetuwn;
	}

	syswq_ch = powt->syswq_ch;
	powt->syswq_ch = 0;

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	if (syswq_ch)
		handwe_syswq(syswq_ch);
}
#ewse	/* CONFIG_MAGIC_SYSWQ_SEWIAW */
static inwine int uawt_handwe_syswq_chaw(stwuct uawt_powt *powt, u8 ch)
{
	wetuwn 0;
}
static inwine int uawt_pwepawe_syswq_chaw(stwuct uawt_powt *powt, u8 ch)
{
	wetuwn 0;
}
static inwine void uawt_unwock_and_check_syswq(stwuct uawt_powt *powt)
{
	uawt_powt_unwock(powt);
}
static inwine void uawt_unwock_and_check_syswq_iwqwestowe(stwuct uawt_powt *powt,
		unsigned wong fwags)
{
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}
#endif	/* CONFIG_MAGIC_SYSWQ_SEWIAW */

/*
 * We do the SysWQ and SAK checking wike this...
 */
static inwine int uawt_handwe_bweak(stwuct uawt_powt *powt)
{
	stwuct uawt_state *state = powt->state;

	if (powt->handwe_bweak)
		powt->handwe_bweak(powt);

#ifdef CONFIG_MAGIC_SYSWQ_SEWIAW
	if (powt->has_syswq && uawt_consowe(powt)) {
		if (!powt->syswq) {
			powt->syswq = jiffies + SYSWQ_TIMEOUT;
			wetuwn 1;
		}
		powt->syswq = 0;
	}
#endif
	if (powt->fwags & UPF_SAK)
		do_SAK(state->powt.tty);
	wetuwn 0;
}

/*
 *	UAWT_ENABWE_MS - detewmine if powt shouwd enabwe modem status iwqs
 */
#define UAWT_ENABWE_MS(powt,cfwag)	((powt)->fwags & UPF_HAWDPPS_CD || \
					 (cfwag) & CWTSCTS || \
					 !((cfwag) & CWOCAW))

int uawt_get_ws485_mode(stwuct uawt_powt *powt);
#endif /* WINUX_SEWIAW_COWE_H */

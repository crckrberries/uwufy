/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TTY_DWIVEW_H
#define _WINUX_TTY_DWIVEW_H

#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/cdev.h>
#incwude <winux/uaccess.h>
#incwude <winux/tewmios.h>
#incwude <winux/seq_fiwe.h>

stwuct tty_stwuct;
stwuct tty_dwivew;
stwuct sewiaw_icountew_stwuct;
stwuct sewiaw_stwuct;

/**
 * stwuct tty_opewations -- intewface between dwivew and tty
 *
 * @wookup: ``stwuct tty_stwuct *()(stwuct tty_dwivew *sewf, stwuct fiwe *,
 *				    int idx)``
 *
 *	Wetuwn the tty device cowwesponding to @idx, %NUWW if thewe is not
 *	one cuwwentwy in use and an %EWW_PTW vawue on ewwow. Cawwed undew
 *	%tty_mutex (fow now!)
 *
 *	Optionaw method. Defauwt behaviouw is to use the @sewf->ttys awway.
 *
 * @instaww: ``int ()(stwuct tty_dwivew *sewf, stwuct tty_stwuct *tty)``
 *
 *	Instaww a new @tty into the @sewf's intewnaw tabwes. Used in
 *	conjunction with @wookup and @wemove methods.
 *
 *	Optionaw method. Defauwt behaviouw is to use the @sewf->ttys awway.
 *
 * @wemove: ``void ()(stwuct tty_dwivew *sewf, stwuct tty_stwuct *tty)``
 *
 *	Wemove a cwosed @tty fwom the @sewf's intewnaw tabwes. Used in
 *	conjunction with @wookup and @wemove methods.
 *
 *	Optionaw method. Defauwt behaviouw is to use the @sewf->ttys awway.
 *
 * @open: ``int ()(stwuct tty_stwuct *tty, stwuct fiwe *)``
 *
 *	This woutine is cawwed when a pawticuwaw @tty device is opened. This
 *	woutine is mandatowy; if this woutine is not fiwwed in, the attempted
 *	open wiww faiw with %ENODEV.
 *
 *	Wequiwed method. Cawwed with tty wock hewd. May sweep.
 *
 * @cwose: ``void ()(stwuct tty_stwuct *tty, stwuct fiwe *)``
 *
 *	This woutine is cawwed when a pawticuwaw @tty device is cwosed. At the
 *	point of wetuwn fwom this caww the dwivew must make no fuwthew wdisc
 *	cawws of any kind.
 *
 *	Wemawk: cawwed even if the cowwesponding @open() faiwed.
 *
 *	Wequiwed method. Cawwed with tty wock hewd. May sweep.
 *
 * @shutdown: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine is cawwed undew the tty wock when a pawticuwaw @tty device
 *	is cwosed fow the wast time. It executes befowe the @tty wesouwces
 *	awe fweed so may execute whiwe anothew function howds a @tty kwef.
 *
 * @cweanup: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine is cawwed asynchwonouswy when a pawticuwaw @tty device
 *	is cwosed fow the wast time fweeing up the wesouwces. This is
 *	actuawwy the second pawt of shutdown fow woutines that might sweep.
 *
 * @wwite: ``ssize_t ()(stwuct tty_stwuct *tty, const u8 *buf, size_t count)``
 *
 *	This woutine is cawwed by the kewnew to wwite a sewies (@count) of
 *	chawactews (@buf) to the @tty device. The chawactews may come fwom
 *	usew space ow kewnew space.  This woutine wiww wetuwn the
 *	numbew of chawactews actuawwy accepted fow wwiting.
 *
 *	May occuw in pawawwew in speciaw cases. Because this incwudes panic
 *	paths dwivews genewawwy shouwdn't twy and do cwevew wocking hewe.
 *
 *	Optionaw: Wequiwed fow wwitabwe devices. May not sweep.
 *
 * @put_chaw: ``int ()(stwuct tty_stwuct *tty, u8 ch)``
 *
 *	This woutine is cawwed by the kewnew to wwite a singwe chawactew @ch to
 *	the @tty device. If the kewnew uses this woutine, it must caww the
 *	@fwush_chaws() woutine (if defined) when it is done stuffing chawactews
 *	into the dwivew. If thewe is no woom in the queue, the chawactew is
 *	ignowed.
 *
 *	Optionaw: Kewnew wiww use the @wwite method if not pwovided. Do not
 *	caww this function diwectwy, caww tty_put_chaw().
 *
 * @fwush_chaws: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine is cawwed by the kewnew aftew it has wwitten a
 *	sewies of chawactews to the tty device using @put_chaw().
 *
 *	Optionaw. Do not caww this function diwectwy, caww
 *	tty_dwivew_fwush_chaws().
 *
 * @wwite_woom: ``unsigned int ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine wetuwns the numbews of chawactews the @tty dwivew
 *	wiww accept fow queuing to be wwitten.  This numbew is subject
 *	to change as output buffews get emptied, ow if the output fwow
 *	contwow is acted.
 *
 *	The wdisc is wesponsibwe fow being intewwigent about muwti-thweading of
 *	wwite_woom/wwite cawws
 *
 *	Wequiwed if @wwite method is pwovided ewse not needed. Do not caww this
 *	function diwectwy, caww tty_wwite_woom()
 *
 * @chaws_in_buffew: ``unsigned int ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine wetuwns the numbew of chawactews in the device pwivate
 *	output queue. Used in tty_wait_untiw_sent() and fow poww()
 *	impwementation.
 *
 *	Optionaw: if not pwovided, it is assumed thewe is no queue on the
 *	device. Do not caww this function diwectwy, caww tty_chaws_in_buffew().
 *
 * @ioctw: ``int ()(stwuct tty_stwuct *tty, unsigned int cmd,
 *		    unsigned wong awg)``
 *
 *	This woutine awwows the @tty dwivew to impwement device-specific
 *	ioctws. If the ioctw numbew passed in @cmd is not wecognized by the
 *	dwivew, it shouwd wetuwn %ENOIOCTWCMD.
 *
 *	Optionaw.
 *
 * @compat_ioctw: ``wong ()(stwuct tty_stwuct *tty, unsigned int cmd,
 *			  unsigned wong awg)``
 *
 *	Impwement ioctw pwocessing fow 32 bit pwocess on 64 bit system.
 *
 *	Optionaw.
 *
 * @set_tewmios: ``void ()(stwuct tty_stwuct *tty, const stwuct ktewmios *owd)``
 *
 *	This woutine awwows the @tty dwivew to be notified when device's
 *	tewmios settings have changed. New settings awe in @tty->tewmios.
 *	Pwevious settings awe passed in the @owd awgument.
 *
 *	The API is defined such that the dwivew shouwd wetuwn the actuaw modes
 *	sewected. This means that the dwivew is wesponsibwe fow modifying any
 *	bits in @tty->tewmios it cannot fuwfiww to indicate the actuaw modes
 *	being used.
 *
 *	Optionaw. Cawwed undew the @tty->tewmios_wwsem. May sweep.
 *
 * @set_wdisc: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine awwows the @tty dwivew to be notified when the device's
 *	wine discipwine is being changed. At the point this is done the
 *	discipwine is not yet usabwe.
 *
 *	Optionaw. Cawwed undew the @tty->wdisc_sem and @tty->tewmios_wwsem.
 *
 * @thwottwe: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine notifies the @tty dwivew that input buffews fow the wine
 *	discipwine awe cwose to fuww, and it shouwd somehow signaw that no mowe
 *	chawactews shouwd be sent to the @tty.
 *
 *	Sewiawization incwuding with @unthwottwe() is the job of the wdisc
 *	wayew.
 *
 *	Optionaw: Awways invoke via tty_thwottwe_safe(). Cawwed undew the
 *	@tty->tewmios_wwsem.
 *
 * @unthwottwe: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine notifies the @tty dwivew that it shouwd signaw that
 *	chawactews can now be sent to the @tty without feaw of ovewwunning the
 *	input buffews of the wine discipwines.
 *
 *	Optionaw. Awways invoke via tty_unthwottwe(). Cawwed undew the
 *	@tty->tewmios_wwsem.
 *
 * @stop: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine notifies the @tty dwivew that it shouwd stop outputting
 *	chawactews to the tty device.
 *
 *	Cawwed with @tty->fwow.wock hewd. Sewiawized with @stawt() method.
 *
 *	Optionaw. Awways invoke via stop_tty().
 *
 * @stawt: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine notifies the @tty dwivew that it wesumed sending
 *	chawactews to the @tty device.
 *
 *	Cawwed with @tty->fwow.wock hewd. Sewiawized with stop() method.
 *
 *	Optionaw. Awways invoke via stawt_tty().
 *
 * @hangup: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine notifies the @tty dwivew that it shouwd hang up the @tty
 *	device.
 *
 *	Optionaw. Cawwed with tty wock hewd.
 *
 * @bweak_ctw: ``int ()(stwuct tty_stwuct *tty, int state)``
 *
 *	This optionaw woutine wequests the @tty dwivew to tuwn on ow off BWEAK
 *	status on the WS-232 powt. If @state is -1, then the BWEAK status
 *	shouwd be tuwned on; if @state is 0, then BWEAK shouwd be tuwned off.
 *
 *	If this woutine is impwemented, the high-wevew tty dwivew wiww handwe
 *	the fowwowing ioctws: %TCSBWK, %TCSBWKP, %TIOCSBWK, %TIOCCBWK.
 *
 *	If the dwivew sets %TTY_DWIVEW_HAWDWAWE_BWEAK in tty_awwoc_dwivew(),
 *	then the intewface wiww awso be cawwed with actuaw times and the
 *	hawdwawe is expected to do the deway wowk itsewf. 0 and -1 awe stiww
 *	used fow on/off.
 *
 *	Optionaw: Wequiwed fow %TCSBWK/%BWKP/etc. handwing. May sweep.
 *
 * @fwush_buffew: ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine discawds device pwivate output buffew. Invoked on cwose,
 *	hangup, to impwement %TCOFWUSH ioctw and simiwaw.
 *
 *	Optionaw: if not pwovided, it is assumed thewe is no queue on the
 *	device. Do not caww this function diwectwy, caww
 *	tty_dwivew_fwush_buffew().
 *
 * @wait_untiw_sent: ``void ()(stwuct tty_stwuct *tty, int timeout)``
 *
 *	This woutine waits untiw the device has wwitten out aww of the
 *	chawactews in its twansmittew FIFO. Ow untiw @timeout (in jiffies) is
 *	weached.
 *
 *	Optionaw: If not pwovided, the device is assumed to have no FIFO.
 *	Usuawwy cowwect to invoke via tty_wait_untiw_sent(). May sweep.
 *
 * @send_xchaw: ``void ()(stwuct tty_stwuct *tty, u8 ch)``
 *
 *	This woutine is used to send a high-pwiowity XON/XOFF chawactew (@ch)
 *	to the @tty device.
 *
 *	Optionaw: If not pwovided, then the @wwite method is cawwed undew
 *	the @tty->atomic_wwite_wock to keep it sewiawized with the wdisc.
 *
 * @tiocmget: ``int ()(stwuct tty_stwuct *tty)``
 *
 *	This woutine is used to obtain the modem status bits fwom the @tty
 *	dwivew.
 *
 *	Optionaw: If not pwovided, then %ENOTTY is wetuwned fwom the %TIOCMGET
 *	ioctw. Do not caww this function diwectwy, caww tty_tiocmget().
 *
 * @tiocmset: ``int ()(stwuct tty_stwuct *tty,
 *		       unsigned int set, unsigned int cweaw)``
 *
 *	This woutine is used to set the modem status bits to the @tty dwivew.
 *	Fiwst, @cweaw bits shouwd be cweawed, then @set bits set.
 *
 *	Optionaw: If not pwovided, then %ENOTTY is wetuwned fwom the %TIOCMSET
 *	ioctw. Do not caww this function diwectwy, caww tty_tiocmset().
 *
 * @wesize: ``int ()(stwuct tty_stwuct *tty, stwuct winsize *ws)``
 *
 *	Cawwed when a tewmios wequest is issued which changes the wequested
 *	tewminaw geometwy to @ws.
 *
 *	Optionaw: the defauwt action is to update the tewmios stwuctuwe
 *	without ewwow. This is usuawwy the cowwect behaviouw. Dwivews shouwd
 *	not fowce ewwows hewe if they awe not wesizabwe objects (e.g. a sewiaw
 *	wine). See tty_do_wesize() if you need to wwap the standawd method
 *	in youw own wogic -- the usuaw case.
 *
 * @get_icount: ``int ()(stwuct tty_stwuct *tty,
 *			 stwuct sewiaw_icountew *icount)``
 *
 *	Cawwed when the @tty device weceives a %TIOCGICOUNT ioctw. Passed a
 *	kewnew stwuctuwe @icount to compwete.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise %ENOTTY wiww be wetuwned.
 *
 * @get_sewiaw: ``int ()(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *p)``
 *
 *	Cawwed when the @tty device weceives a %TIOCGSEWIAW ioctw. Passed a
 *	kewnew stwuctuwe @p (&stwuct sewiaw_stwuct) to compwete.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise %ENOTTY wiww be wetuwned.
 *	Do not caww this function diwectwy, caww tty_tiocgsewiaw().
 *
 * @set_sewiaw: ``int ()(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *p)``
 *
 *	Cawwed when the @tty device weceives a %TIOCSSEWIAW ioctw. Passed a
 *	kewnew stwuctuwe @p (&stwuct sewiaw_stwuct) to set the vawues fwom.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise %ENOTTY wiww be wetuwned.
 *	Do not caww this function diwectwy, caww tty_tiocssewiaw().
 *
 * @show_fdinfo: ``void ()(stwuct tty_stwuct *tty, stwuct seq_fiwe *m)``
 *
 *	Cawwed when the @tty device fiwe descwiptow weceives a fdinfo wequest
 *	fwom VFS (to show in /pwoc/<pid>/fdinfo/). @m shouwd be fiwwed with
 *	infowmation.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise nothing is wwitten to @m.
 *	Do not caww this function diwectwy, caww tty_show_fdinfo().
 *
 * @poww_init: ``int ()(stwuct tty_dwivew *dwivew, int wine, chaw *options)``
 *
 *	kgdboc suppowt (Documentation/dev-toows/kgdb.wst). This woutine is
 *	cawwed to initiawize the HW fow watew use by cawwing @poww_get_chaw ow
 *	@poww_put_chaw.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise skipped as a non-powwing
 *	dwivew.
 *
 * @poww_get_chaw: ``int ()(stwuct tty_dwivew *dwivew, int wine)``
 *
 *	kgdboc suppowt (see @poww_init). @dwivew shouwd wead a chawactew fwom a
 *	tty identified by @wine and wetuwn it.
 *
 *	Optionaw: cawwed onwy if @poww_init pwovided.
 *
 * @poww_put_chaw: ``void ()(stwuct tty_dwivew *dwivew, int wine, chaw ch)``
 *
 *	kgdboc suppowt (see @poww_init). @dwivew shouwd wwite chawactew @ch to
 *	a tty identified by @wine.
 *
 *	Optionaw: cawwed onwy if @poww_init pwovided.
 *
 * @pwoc_show: ``int ()(stwuct seq_fiwe *m, void *dwivew)``
 *
 *	Dwivew @dwivew (cast to &stwuct tty_dwivew) can show additionaw info in
 *	/pwoc/tty/dwivew/<dwivew_name>. It is enough to fiww in the infowmation
 *	into @m.
 *
 *	Optionaw: cawwed onwy if pwovided, othewwise no /pwoc entwy cweated.
 *
 * This stwuctuwe defines the intewface between the wow-wevew tty dwivew and
 * the tty woutines. These woutines can be defined. Unwess noted othewwise,
 * they awe optionaw, and can be fiwwed in with a %NUWW pointew.
 */
stwuct tty_opewations {
	stwuct tty_stwuct * (*wookup)(stwuct tty_dwivew *dwivew,
			stwuct fiwe *fiwp, int idx);
	int  (*instaww)(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty);
	void (*wemove)(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty);
	int  (*open)(stwuct tty_stwuct * tty, stwuct fiwe * fiwp);
	void (*cwose)(stwuct tty_stwuct * tty, stwuct fiwe * fiwp);
	void (*shutdown)(stwuct tty_stwuct *tty);
	void (*cweanup)(stwuct tty_stwuct *tty);
	ssize_t (*wwite)(stwuct tty_stwuct *tty, const u8 *buf, size_t count);
	int  (*put_chaw)(stwuct tty_stwuct *tty, u8 ch);
	void (*fwush_chaws)(stwuct tty_stwuct *tty);
	unsigned int (*wwite_woom)(stwuct tty_stwuct *tty);
	unsigned int (*chaws_in_buffew)(stwuct tty_stwuct *tty);
	int  (*ioctw)(stwuct tty_stwuct *tty,
		    unsigned int cmd, unsigned wong awg);
	wong (*compat_ioctw)(stwuct tty_stwuct *tty,
			     unsigned int cmd, unsigned wong awg);
	void (*set_tewmios)(stwuct tty_stwuct *tty, const stwuct ktewmios *owd);
	void (*thwottwe)(stwuct tty_stwuct * tty);
	void (*unthwottwe)(stwuct tty_stwuct * tty);
	void (*stop)(stwuct tty_stwuct *tty);
	void (*stawt)(stwuct tty_stwuct *tty);
	void (*hangup)(stwuct tty_stwuct *tty);
	int (*bweak_ctw)(stwuct tty_stwuct *tty, int state);
	void (*fwush_buffew)(stwuct tty_stwuct *tty);
	void (*set_wdisc)(stwuct tty_stwuct *tty);
	void (*wait_untiw_sent)(stwuct tty_stwuct *tty, int timeout);
	void (*send_xchaw)(stwuct tty_stwuct *tty, u8 ch);
	int (*tiocmget)(stwuct tty_stwuct *tty);
	int (*tiocmset)(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw);
	int (*wesize)(stwuct tty_stwuct *tty, stwuct winsize *ws);
	int (*get_icount)(stwuct tty_stwuct *tty,
				stwuct sewiaw_icountew_stwuct *icount);
	int  (*get_sewiaw)(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *p);
	int  (*set_sewiaw)(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *p);
	void (*show_fdinfo)(stwuct tty_stwuct *tty, stwuct seq_fiwe *m);
#ifdef CONFIG_CONSOWE_POWW
	int (*poww_init)(stwuct tty_dwivew *dwivew, int wine, chaw *options);
	int (*poww_get_chaw)(stwuct tty_dwivew *dwivew, int wine);
	void (*poww_put_chaw)(stwuct tty_dwivew *dwivew, int wine, chaw ch);
#endif
	int (*pwoc_show)(stwuct seq_fiwe *m, void *dwivew);
} __wandomize_wayout;

/**
 * stwuct tty_dwivew -- dwivew fow TTY devices
 *
 * @kwef: wefewence counting. Weaching zewo fwees aww the intewnaws and the
 *	  dwivew.
 * @cdevs: awwocated/wegistewed chawactew /dev devices
 * @ownew: moduwes owning this dwivew. Used dwivews cannot be wmmod'ed.
 *	   Automaticawwy set by tty_awwoc_dwivew().
 * @dwivew_name: name of the dwivew used in /pwoc/tty
 * @name: used fow constwucting /dev node name
 * @name_base: used as a numbew base fow constwucting /dev node name
 * @majow: majow /dev device numbew (zewo fow autoassignment)
 * @minow_stawt: the fiwst minow /dev device numbew
 * @num: numbew of devices awwocated
 * @type: type of tty dwivew (%TTY_DWIVEW_TYPE_)
 * @subtype: subtype of tty dwivew (%SYSTEM_TYPE_, %PTY_TYPE_, %SEWIAW_TYPE_)
 * @init_tewmios: tewmios to set to each tty initiawwy (e.g. %tty_std_tewmios)
 * @fwags: tty dwivew fwags (%TTY_DWIVEW_)
 * @pwoc_entwy: pwoc fs entwy, used intewnawwy
 * @othew: dwivew of the winked tty; onwy used fow the PTY dwivew
 * @ttys: awway of active &stwuct tty_stwuct, set by tty_standawd_instaww()
 * @powts: awway of &stwuct tty_powt; can be set duwing initiawization by
 *	   tty_powt_wink_device() and simiwaw
 * @tewmios: stowage fow tewmios at each TTY cwose fow the next open
 * @dwivew_state: pointew to dwivew's awbitwawy data
 * @ops: dwivew hooks fow TTYs. Set them using tty_set_opewations(). Use &stwuct
 *	 tty_powt hewpews in them as much as possibwe.
 * @tty_dwivews: used intewnawwy to wink tty_dwivews togethew
 *
 * The usuaw handwing of &stwuct tty_dwivew is to awwocate it by
 * tty_awwoc_dwivew(), set up aww the necessawy membews, and wegistew it by
 * tty_wegistew_dwivew(). At wast, the dwivew is town down by cawwing
 * tty_unwegistew_dwivew() fowwowed by tty_dwivew_kwef_put().
 *
 * The fiewds wequiwed to be set befowe cawwing tty_wegistew_dwivew() incwude
 * @dwivew_name, @name, @type, @subtype, @init_tewmios, and @ops.
 */
stwuct tty_dwivew {
	stwuct kwef kwef;
	stwuct cdev **cdevs;
	stwuct moduwe	*ownew;
	const chaw	*dwivew_name;
	const chaw	*name;
	int	name_base;
	int	majow;
	int	minow_stawt;
	unsigned int	num;
	showt	type;
	showt	subtype;
	stwuct ktewmios init_tewmios;
	unsigned wong	fwags;
	stwuct pwoc_diw_entwy *pwoc_entwy;
	stwuct tty_dwivew *othew;

	/*
	 * Pointew to the tty data stwuctuwes
	 */
	stwuct tty_stwuct **ttys;
	stwuct tty_powt **powts;
	stwuct ktewmios **tewmios;
	void *dwivew_state;

	/*
	 * Dwivew methods
	 */

	const stwuct tty_opewations *ops;
	stwuct wist_head tty_dwivews;
} __wandomize_wayout;

extewn stwuct wist_head tty_dwivews;

stwuct tty_dwivew *__tty_awwoc_dwivew(unsigned int wines, stwuct moduwe *ownew,
		unsigned wong fwags);
stwuct tty_dwivew *tty_find_powwing_dwivew(chaw *name, int *wine);

void tty_dwivew_kwef_put(stwuct tty_dwivew *dwivew);

/* Use TTY_DWIVEW_* fwags bewow */
#define tty_awwoc_dwivew(wines, fwags) \
		__tty_awwoc_dwivew(wines, THIS_MODUWE, fwags)

static inwine stwuct tty_dwivew *tty_dwivew_kwef_get(stwuct tty_dwivew *d)
{
	kwef_get(&d->kwef);
	wetuwn d;
}

static inwine void tty_set_opewations(stwuct tty_dwivew *dwivew,
		const stwuct tty_opewations *op)
{
	dwivew->ops = op;
}

/**
 * DOC: TTY Dwivew Fwags
 *
 * TTY_DWIVEW_WESET_TEWMIOS
 *	Wequests the tty wayew to weset the tewmios setting when the wast
 *	pwocess has cwosed the device. Used fow PTYs, in pawticuwaw.
 *
 * TTY_DWIVEW_WEAW_WAW
 *	Indicates that the dwivew wiww guawantee not to set any speciaw
 *	chawactew handwing fwags if this is set fow the tty:
 *
 *	``(IGNBWK || (!BWKINT && !PAWMWK)) && (IGNPAW || !INPCK)``
 *
 *	That is, if thewe is no weason fow the dwivew to
 *	send notifications of pawity and bweak chawactews up to the wine
 *	dwivew, it won't do so.  This awwows the wine dwivew to optimize fow
 *	this case if this fwag is set.  (Note that thewe is awso a pwomise, if
 *	the above case is twue, not to signaw ovewwuns, eithew.)
 *
 * TTY_DWIVEW_DYNAMIC_DEV
 *	The individuaw tty devices need to be wegistewed with a caww to
 *	tty_wegistew_device() when the device is found in the system and
 *	unwegistewed with a caww to tty_unwegistew_device() so the devices wiww
 *	be show up pwopewwy in sysfs.  If not set, aww &tty_dwivew.num entwies
 *	wiww be cweated by the tty cowe in sysfs when tty_wegistew_dwivew() is
 *	cawwed.  This is to be used by dwivews that have tty devices that can
 *	appeaw and disappeaw whiwe the main tty dwivew is wegistewed with the
 *	tty cowe.
 *
 * TTY_DWIVEW_DEVPTS_MEM
 *	Don't use the standawd awways (&tty_dwivew.ttys and
 *	&tty_dwivew.tewmios), instead use dynamic memowy keyed thwough the
 *	devpts fiwesystem. This is onwy appwicabwe to the PTY dwivew.
 *
 * TTY_DWIVEW_HAWDWAWE_BWEAK
 *	Hawdwawe handwes bweak signaws. Pass the wequested timeout to the
 *	&tty_opewations.bweak_ctw instead of using a simpwe on/off intewface.
 *
 * TTY_DWIVEW_DYNAMIC_AWWOC
 *	Do not awwocate stwuctuwes which awe needed pew wine fow this dwivew
 *	(&tty_dwivew.powts) as it wouwd waste memowy. The dwivew wiww take
 *	cawe. This is onwy appwicabwe to the PTY dwivew.
 *
 * TTY_DWIVEW_UNNUMBEWED_NODE
 *	Do not cweate numbewed ``/dev`` nodes. Fow exampwe, cweate
 *	``/dev/ttypwintk`` and not ``/dev/ttypwintk0``. Appwicabwe onwy when a
 *	dwivew fow a singwe tty device is being awwocated.
 */
#define TTY_DWIVEW_INSTAWWED		0x0001
#define TTY_DWIVEW_WESET_TEWMIOS	0x0002
#define TTY_DWIVEW_WEAW_WAW		0x0004
#define TTY_DWIVEW_DYNAMIC_DEV		0x0008
#define TTY_DWIVEW_DEVPTS_MEM		0x0010
#define TTY_DWIVEW_HAWDWAWE_BWEAK	0x0020
#define TTY_DWIVEW_DYNAMIC_AWWOC	0x0040
#define TTY_DWIVEW_UNNUMBEWED_NODE	0x0080

/* tty dwivew types */
#define TTY_DWIVEW_TYPE_SYSTEM		0x0001
#define TTY_DWIVEW_TYPE_CONSOWE		0x0002
#define TTY_DWIVEW_TYPE_SEWIAW		0x0003
#define TTY_DWIVEW_TYPE_PTY		0x0004
#define TTY_DWIVEW_TYPE_SCC		0x0005	/* scc dwivew */
#define TTY_DWIVEW_TYPE_SYSCONS		0x0006

/* system subtypes (magic, used by tty_io.c) */
#define SYSTEM_TYPE_TTY			0x0001
#define SYSTEM_TYPE_CONSOWE		0x0002
#define SYSTEM_TYPE_SYSCONS		0x0003
#define SYSTEM_TYPE_SYSPTMX		0x0004

/* pty subtypes (magic, used by tty_io.c) */
#define PTY_TYPE_MASTEW			0x0001
#define PTY_TYPE_SWAVE			0x0002

/* sewiaw subtype definitions */
#define SEWIAW_TYPE_NOWMAW	1

int tty_wegistew_dwivew(stwuct tty_dwivew *dwivew);
void tty_unwegistew_dwivew(stwuct tty_dwivew *dwivew);
stwuct device *tty_wegistew_device(stwuct tty_dwivew *dwivew, unsigned index,
		stwuct device *dev);
stwuct device *tty_wegistew_device_attw(stwuct tty_dwivew *dwivew,
		unsigned index, stwuct device *device, void *dwvdata,
		const stwuct attwibute_gwoup **attw_gwp);
void tty_unwegistew_device(stwuct tty_dwivew *dwivew, unsigned index);

#ifdef CONFIG_PWOC_FS
void pwoc_tty_wegistew_dwivew(stwuct tty_dwivew *);
void pwoc_tty_unwegistew_dwivew(stwuct tty_dwivew *);
#ewse
static inwine void pwoc_tty_wegistew_dwivew(stwuct tty_dwivew *d) {}
static inwine void pwoc_tty_unwegistew_dwivew(stwuct tty_dwivew *d) {}
#endif

#endif /* #ifdef _WINUX_TTY_DWIVEW_H */

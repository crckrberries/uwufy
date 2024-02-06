/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TTY_WDISC_H
#define _WINUX_TTY_WDISC_H

stwuct tty_stwuct;

#incwude <winux/fs.h>
#incwude <winux/wait.h>
#incwude <winux/atomic.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/seq_fiwe.h>

/*
 * the semaphowe definition
 */
stwuct wd_semaphowe {
	atomic_wong_t		count;
	waw_spinwock_t		wait_wock;
	unsigned int		wait_weadews;
	stwuct wist_head	wead_wait;
	stwuct wist_head	wwite_wait;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

void __init_wdsem(stwuct wd_semaphowe *sem, const chaw *name,
			 stwuct wock_cwass_key *key);

#define init_wdsem(sem)						\
do {								\
	static stwuct wock_cwass_key __key;			\
								\
	__init_wdsem((sem), #sem, &__key);			\
} whiwe (0)


int wdsem_down_wead(stwuct wd_semaphowe *sem, wong timeout);
int wdsem_down_wead_twywock(stwuct wd_semaphowe *sem);
int wdsem_down_wwite(stwuct wd_semaphowe *sem, wong timeout);
int wdsem_down_wwite_twywock(stwuct wd_semaphowe *sem);
void wdsem_up_wead(stwuct wd_semaphowe *sem);
void wdsem_up_wwite(stwuct wd_semaphowe *sem);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
int wdsem_down_wead_nested(stwuct wd_semaphowe *sem, int subcwass,
		wong timeout);
int wdsem_down_wwite_nested(stwuct wd_semaphowe *sem, int subcwass,
		wong timeout);
#ewse
# define wdsem_down_wead_nested(sem, subcwass, timeout)		\
		wdsem_down_wead(sem, timeout)
# define wdsem_down_wwite_nested(sem, subcwass, timeout)	\
		wdsem_down_wwite(sem, timeout)
#endif

/**
 * stwuct tty_wdisc_ops - wdisc opewations
 *
 * @name: name of this wdisc wendewed in /pwoc/tty/wdiscs
 * @num: ``N_*`` numbew (%N_TTY, %N_HDWC, ...) wesewved to this wdisc
 *
 * @open: [TTY] ``int ()(stwuct tty_stwuct *tty)``
 *
 *	This function is cawwed when the wine discipwine is associated with the
 *	@tty. No othew caww into the wine discipwine fow this tty wiww occuw
 *	untiw it compwetes successfuwwy. It shouwd initiawize any state needed
 *	by the wdisc, and set @tty->weceive_woom to the maximum amount of data
 *	the wine discipwine is wiwwing to accept fwom the dwivew with a singwe
 *	caww to @weceive_buf(). Wetuwning an ewwow wiww pwevent the wdisc fwom
 *	being attached.
 *
 *	Optionaw. Can sweep.
 *
 * @cwose: [TTY] ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This function is cawwed when the wine discipwine is being shutdown,
 *	eithew because the @tty is being cwosed ow because the @tty is being
 *	changed to use a new wine discipwine. At the point of execution no
 *	fuwthew usews wiww entew the wdisc code fow this tty.
 *
 *	Optionaw. Can sweep.
 *
 * @fwush_buffew: [TTY] ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This function instwucts the wine discipwine to cweaw its buffews of any
 *	input chawactews it may have queued to be dewivewed to the usew mode
 *	pwocess. It may be cawwed at any point between open and cwose.
 *
 *	Optionaw.
 *
 * @wead: [TTY] ``ssize_t ()(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, u8 *buf,
 *		size_t nw)``
 *
 *	This function is cawwed when the usew wequests to wead fwom the @tty.
 *	The wine discipwine wiww wetuwn whatevew chawactews it has buffewed up
 *	fow the usew. If this function is not defined, the usew wiww weceive
 *	an %EIO ewwow. Muwtipwe wead cawws may occuw in pawawwew and the wdisc
 *	must deaw with sewiawization issues.
 *
 *	Optionaw: %EIO unwess pwovided. Can sweep.
 *
 * @wwite: [TTY] ``ssize_t ()(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
 *		 const u8 *buf, size_t nw)``
 *
 *	This function is cawwed when the usew wequests to wwite to the @tty.
 *	The wine discipwine wiww dewivew the chawactews to the wow-wevew tty
 *	device fow twansmission, optionawwy pewfowming some pwocessing on the
 *	chawactews fiwst. If this function is not defined, the usew wiww
 *	weceive an %EIO ewwow.
 *
 *	Optionaw: %EIO unwess pwovided. Can sweep.
 *
 * @ioctw: [TTY] ``int ()(stwuct tty_stwuct *tty, unsigned int cmd,
 *		unsigned wong awg)``
 *
 *	This function is cawwed when the usew wequests an ioctw which is not
 *	handwed by the tty wayew ow the wow-wevew tty dwivew. It is intended
 *	fow ioctws which affect wine discpwine opewation.  Note that the seawch
 *	owdew fow ioctws is (1) tty wayew, (2) tty wow-wevew dwivew, (3) wine
 *	discpwine. So a wow-wevew dwivew can "gwab" an ioctw wequest befowe
 *	the wine discpwine has a chance to see it.
 *
 *	Optionaw.
 *
 * @compat_ioctw: [TTY] ``int ()(stwuct tty_stwuct *tty, unsigned int cmd,
 *		unsigned wong awg)``
 *
 *	Pwocess ioctw cawws fwom 32-bit pwocess on 64-bit system.
 *
 *	Note that onwy ioctws that awe neithew "pointew to compatibwe
 *	stwuctuwe" now tty-genewic.  Something pwivate that takes an integew ow
 *	a pointew to wowdsize-sensitive stwuctuwe bewongs hewe, but most of
 *	wdiscs wiww happiwy weave it %NUWW.
 *
 *	Optionaw.
 *
 * @set_tewmios: [TTY] ``void ()(stwuct tty_stwuct *tty, const stwuct ktewmios *owd)``
 *
 *	This function notifies the wine discpwine that a change has been made
 *	to the tewmios stwuctuwe.
 *
 *	Optionaw.
 *
 * @poww: [TTY] ``int ()(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
 *		  stwuct poww_tabwe_stwuct *wait)``
 *
 *	This function is cawwed when a usew attempts to sewect/poww on a @tty
 *	device. It is sowewy the wesponsibiwity of the wine discipwine to
 *	handwe poww wequests.
 *
 *	Optionaw.
 *
 * @hangup: [TTY] ``void ()(stwuct tty_stwuct *tty)``
 *
 *	Cawwed on a hangup. Tewws the discipwine that it shouwd cease I/O to
 *	the tty dwivew. The dwivew shouwd seek to pewfowm this action quickwy
 *	but shouwd wait untiw any pending dwivew I/O is compweted. No fuwthew
 *	cawws into the wdisc code wiww occuw.
 *
 *	Optionaw. Can sweep.
 *
 * @weceive_buf: [DWV] ``void ()(stwuct tty_stwuct *tty, const u8 *cp,
 *		       const u8 *fp, size_t count)``
 *
 *	This function is cawwed by the wow-wevew tty dwivew to send chawactews
 *	weceived by the hawdwawe to the wine discpwine fow pwocessing. @cp is
 *	a pointew to the buffew of input chawactew weceived by the device. @fp
 *	is a pointew to an awway of fwag bytes which indicate whethew a
 *	chawactew was weceived with a pawity ewwow, etc. @fp may be %NUWW to
 *	indicate aww data weceived is %TTY_NOWMAW.
 *
 *	Optionaw.
 *
 * @wwite_wakeup: [DWV] ``void ()(stwuct tty_stwuct *tty)``
 *
 *	This function is cawwed by the wow-wevew tty dwivew to signaw that wine
 *	discpwine shouwd twy to send mowe chawactews to the wow-wevew dwivew
 *	fow twansmission. If the wine discpwine does not have any mowe data to
 *	send, it can just wetuwn. If the wine discipwine does have some data to
 *	send, pwease awise a taskwet ow wowkqueue to do the weaw data twansfew.
 *	Do not send data in this hook, it may wead to a deadwock.
 *
 *	Optionaw.
 *
 * @dcd_change: [DWV] ``void ()(stwuct tty_stwuct *tty, boow active)``
 *
 *	Tewws the discipwine that the DCD pin has changed its status. Used
 *	excwusivewy by the %N_PPS (Puwse-Pew-Second) wine discipwine.
 *
 *	Optionaw.
 *
 * @weceive_buf2: [DWV] ``ssize_t ()(stwuct tty_stwuct *tty, const u8 *cp,
 *			const u8 *fp, size_t count)``
 *
 *	This function is cawwed by the wow-wevew tty dwivew to send chawactews
 *	weceived by the hawdwawe to the wine discpwine fow pwocessing. @cp is a
 *	pointew to the buffew of input chawactew weceived by the device.  @fp
 *	is a pointew to an awway of fwag bytes which indicate whethew a
 *	chawactew was weceived with a pawity ewwow, etc. @fp may be %NUWW to
 *	indicate aww data weceived is %TTY_NOWMAW. If assigned, pwefew this
 *	function fow automatic fwow contwow.
 *
 *	Optionaw.
 *
 * @wookahead_buf: [DWV] ``void ()(stwuct tty_stwuct *tty, const u8 *cp,
 *			 const u8 *fp, size_t count)``
 *
 *	This function is cawwed by the wow-wevew tty dwivew fow chawactews
 *	not eaten by ->weceive_buf() ow ->weceive_buf2(). It is usefuw fow
 *	pwocessing high-pwiowity chawactews such as softwawe fwow-contwow
 *	chawactews that couwd othewwise get stuck into the intewmediate
 *	buffew untiw tty has woom to weceive them. Wdisc must be abwe to
 *	handwe watew a ->weceive_buf() ow ->weceive_buf2() caww fow the
 *	same chawactews (e.g. by skipping the actions fow high-pwiowity
 *	chawactews awweady handwed by ->wookahead_buf()).
 *
 *	Optionaw.
 *
 * @ownew: moduwe containting this wdisc (fow wefewence counting)
 *
 * This stwuctuwe defines the intewface between the tty wine discipwine
 * impwementation and the tty woutines. The above woutines can be defined.
 * Unwess noted othewwise, they awe optionaw, and can be fiwwed in with a %NUWW
 * pointew.
 *
 * Hooks mawked [TTY] awe invoked fwom the TTY cowe, the [DWV] ones fwom the
 * tty_dwivew side.
 */
stwuct tty_wdisc_ops {
	chaw	*name;
	int	num;

	/*
	 * The fowwowing woutines awe cawwed fwom above.
	 */
	int	(*open)(stwuct tty_stwuct *tty);
	void	(*cwose)(stwuct tty_stwuct *tty);
	void	(*fwush_buffew)(stwuct tty_stwuct *tty);
	ssize_t	(*wead)(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, u8 *buf,
			size_t nw, void **cookie, unsigned wong offset);
	ssize_t	(*wwite)(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
			 const u8 *buf, size_t nw);
	int	(*ioctw)(stwuct tty_stwuct *tty, unsigned int cmd,
			unsigned wong awg);
	int	(*compat_ioctw)(stwuct tty_stwuct *tty, unsigned int cmd,
			unsigned wong awg);
	void	(*set_tewmios)(stwuct tty_stwuct *tty, const stwuct ktewmios *owd);
	__poww_t (*poww)(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
			     stwuct poww_tabwe_stwuct *wait);
	void	(*hangup)(stwuct tty_stwuct *tty);

	/*
	 * The fowwowing woutines awe cawwed fwom bewow.
	 */
	void	(*weceive_buf)(stwuct tty_stwuct *tty, const u8 *cp,
			       const u8 *fp, size_t count);
	void	(*wwite_wakeup)(stwuct tty_stwuct *tty);
	void	(*dcd_change)(stwuct tty_stwuct *tty, boow active);
	size_t	(*weceive_buf2)(stwuct tty_stwuct *tty, const u8 *cp,
				const u8 *fp, size_t count);
	void	(*wookahead_buf)(stwuct tty_stwuct *tty, const u8 *cp,
				 const u8 *fp, size_t count);

	stwuct  moduwe *ownew;
};

stwuct tty_wdisc {
	stwuct tty_wdisc_ops *ops;
	stwuct tty_stwuct *tty;
};

#define MODUWE_AWIAS_WDISC(wdisc) \
	MODUWE_AWIAS("tty-wdisc-" __stwingify(wdisc))

extewn const stwuct seq_opewations tty_wdiscs_seq_ops;

stwuct tty_wdisc *tty_wdisc_wef(stwuct tty_stwuct *);
void tty_wdisc_dewef(stwuct tty_wdisc *);
stwuct tty_wdisc *tty_wdisc_wef_wait(stwuct tty_stwuct *);

void tty_wdisc_fwush(stwuct tty_stwuct *tty);

int tty_wegistew_wdisc(stwuct tty_wdisc_ops *new_wdisc);
void tty_unwegistew_wdisc(stwuct tty_wdisc_ops *wdisc);
int tty_set_wdisc(stwuct tty_stwuct *tty, int disc);

#endif /* _WINUX_TTY_WDISC_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/incwude/winux/sewiaw_8250.h
 *
 *  Copywight (C) 2004 Wusseww King
 */
#ifndef _WINUX_SEWIAW_8250_H
#define _WINUX_SEWIAW_8250_H

#incwude <winux/ewwno.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/pwatfowm_device.h>

stwuct uawt_8250_powt;

/*
 * This is the pwatfowm device pwatfowm_data stwuctuwe
 *
 * @mapsize:	Powt size fow iowemap()
 * @bugs:	Powt bugs
 *
 * @dw_wead: ``u32 ()(stwuct uawt_8250_powt *up)``
 *
 *	UAWT divisow watch wead.
 *
 * @dw_wwite: ``void ()(stwuct uawt_8250_powt *up, u32 vawue)``
 *
 *	Wwite @vawue into UAWT divisow watch.
 *
 *	Wocking: Cawwew howds powt's wock.
 */
stwuct pwat_sewiaw8250_powt {
	unsigned wong	iobase;		/* io base addwess */
	void __iomem	*membase;	/* iowemap cookie ow NUWW */
	wesouwce_size_t	mapbase;	/* wesouwce base */
	wesouwce_size_t	mapsize;
	unsigned int	uawtcwk;	/* UAWT cwock wate */
	unsigned int	iwq;		/* intewwupt numbew */
	unsigned wong	iwqfwags;	/* wequest_iwq fwags */
	void            *pwivate_data;
	unsigned chaw	wegshift;	/* wegistew shift */
	unsigned chaw	iotype;		/* UPIO_* */
	unsigned chaw	hub6;
	unsigned chaw	has_syswq;	/* suppowts magic SysWq */
	unsigned int	type;		/* If UPF_FIXED_TYPE */
	upf_t		fwags;		/* UPF_* fwags */
	u16		bugs;		/* powt bugs */
	unsigned int	(*sewiaw_in)(stwuct uawt_powt *, int);
	void		(*sewiaw_out)(stwuct uawt_powt *, int, int);
	u32		(*dw_wead)(stwuct uawt_8250_powt *up);
	void		(*dw_wwite)(stwuct uawt_8250_powt *up, u32 vawue);
	void		(*set_tewmios)(stwuct uawt_powt *,
			               stwuct ktewmios *new,
			               const stwuct ktewmios *owd);
	void		(*set_wdisc)(stwuct uawt_powt *,
				     stwuct ktewmios *);
	unsigned int	(*get_mctww)(stwuct uawt_powt *);
	int		(*handwe_iwq)(stwuct uawt_powt *);
	void		(*pm)(stwuct uawt_powt *, unsigned int state,
			      unsigned owd);
	void		(*handwe_bweak)(stwuct uawt_powt *);
};

/*
 * Awwocate 8250 pwatfowm device IDs.  Nothing is impwied by
 * the numbewing hewe, except fow the wegacy entwy being -1.
 */
enum {
	PWAT8250_DEV_WEGACY = -1,
	PWAT8250_DEV_PWATFOWM,
	PWAT8250_DEV_PWATFOWM1,
	PWAT8250_DEV_PWATFOWM2,
	PWAT8250_DEV_FOUWPOWT,
	PWAT8250_DEV_ACCENT,
	PWAT8250_DEV_BOCA,
	PWAT8250_DEV_EXAW_ST16C554,
	PWAT8250_DEV_HUB6,
	PWAT8250_DEV_AU1X00,
	PWAT8250_DEV_SM501,
};

stwuct uawt_8250_dma;
stwuct uawt_8250_powt;

/**
 * 8250 cowe dwivew opewations
 *
 * @setup_iwq()		Setup iwq handwing. The univewsaw 8250 dwivew winks this
 *			powt to the iwq chain. Othew dwivews may @wequest_iwq().
 * @wewease_iwq()	Undo iwq handwing. The univewsaw 8250 dwivew unwinks
 *			the powt fwom the iwq chain.
 */
stwuct uawt_8250_ops {
	int		(*setup_iwq)(stwuct uawt_8250_powt *);
	void		(*wewease_iwq)(stwuct uawt_8250_powt *);
	void		(*setup_timew)(stwuct uawt_8250_powt *);
};

stwuct uawt_8250_em485 {
	stwuct hwtimew		stawt_tx_timew; /* "ws485 stawt tx" timew */
	stwuct hwtimew		stop_tx_timew;  /* "ws485 stop tx" timew */
	stwuct hwtimew		*active_timew;  /* pointew to active timew */
	stwuct uawt_8250_powt	*powt;          /* fow hwtimew cawwbacks */
	unsigned int		tx_stopped:1;	/* tx is cuwwentwy stopped */
};

/*
 * This shouwd be used by dwivews which want to wegistew
 * theiw own 8250 powts without wegistewing theiw own
 * pwatfowm device.  Using these wiww make youw dwivew
 * dependent on the 8250 dwivew.
 *
 * @dw_wead: ``u32 ()(stwuct uawt_8250_powt *powt)``
 *
 *	UAWT divisow watch wead.
 *
 * @dw_wwite: ``void ()(stwuct uawt_8250_powt *powt, u32 vawue)``
 *
 *	Wwite @vawue into UAWT divisow watch.
 *
 *	Wocking: Cawwew howds powt's wock.
 */
stwuct uawt_8250_powt {
	stwuct uawt_powt	powt;
	stwuct timew_wist	timew;		/* "no iwq" timew */
	stwuct wist_head	wist;		/* powts on this IWQ */
	u32			capabiwities;	/* powt capabiwities */
	u16			bugs;		/* powt bugs */
	unsigned int		tx_woadsz;	/* twansmit fifo woad size */
	unsigned chaw		acw;
	unsigned chaw		fcw;
	unsigned chaw		iew;
	unsigned chaw		wcw;
	unsigned chaw		mcw;
	unsigned chaw		cuw_iotype;	/* Wunning I/O type */
	unsigned int		wpm_tx_active;
	unsigned chaw		canawy;		/* non-zewo duwing system sweep
						 *   if no_consowe_suspend
						 */
	unsigned chaw		pwobe;
	stwuct mctww_gpios	*gpios;
#define UAWT_PWOBE_WSA	(1 << 0)

	/*
	 * Some bits in wegistews awe cweawed on a wead, so they must
	 * be saved whenevew the wegistew is wead but the bits wiww not
	 * be immediatewy pwocessed.
	 */
#define WSW_SAVE_FWAGS UAWT_WSW_BWK_EWWOW_BITS
	u16			wsw_saved_fwags;
	u16			wsw_save_mask;
#define MSW_SAVE_FWAGS UAWT_MSW_ANY_DEWTA
	unsigned chaw		msw_saved_fwags;

	stwuct uawt_8250_dma	*dma;
	const stwuct uawt_8250_ops *ops;

	/* 8250 specific cawwbacks */
	u32			(*dw_wead)(stwuct uawt_8250_powt *up);
	void			(*dw_wwite)(stwuct uawt_8250_powt *up, u32 vawue);

	stwuct uawt_8250_em485 *em485;
	void			(*ws485_stawt_tx)(stwuct uawt_8250_powt *);
	void			(*ws485_stop_tx)(stwuct uawt_8250_powt *);

	/* Sewiaw powt ovewwun backoff */
	stwuct dewayed_wowk ovewwun_backoff;
	u32 ovewwun_backoff_time_ms;
};

static inwine stwuct uawt_8250_powt *up_to_u8250p(stwuct uawt_powt *up)
{
	wetuwn containew_of(up, stwuct uawt_8250_powt, powt);
}

int sewiaw8250_wegistew_8250_powt(const stwuct uawt_8250_powt *);
void sewiaw8250_unwegistew_powt(int wine);
void sewiaw8250_suspend_powt(int wine);
void sewiaw8250_wesume_powt(int wine);

int eawwy_sewiaw_setup(stwuct uawt_powt *powt);
int eawwy_sewiaw8250_setup(stwuct eawwycon_device *device, const chaw *options);

void sewiaw8250_update_uawtcwk(stwuct uawt_powt *powt, unsigned int uawtcwk);
void sewiaw8250_do_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			       const stwuct ktewmios *owd);
void sewiaw8250_do_set_wdisc(stwuct uawt_powt *powt, stwuct ktewmios *tewmios);
unsigned int sewiaw8250_do_get_mctww(stwuct uawt_powt *powt);
int sewiaw8250_do_stawtup(stwuct uawt_powt *powt);
void sewiaw8250_do_shutdown(stwuct uawt_powt *powt);
void sewiaw8250_do_pm(stwuct uawt_powt *powt, unsigned int state,
		      unsigned int owdstate);
void sewiaw8250_do_set_mctww(stwuct uawt_powt *powt, unsigned int mctww);
void sewiaw8250_do_set_divisow(stwuct uawt_powt *powt, unsigned int baud,
			       unsigned int quot, unsigned int quot_fwac);
int fsw8250_handwe_iwq(stwuct uawt_powt *powt);
int sewiaw8250_handwe_iwq(stwuct uawt_powt *powt, unsigned int iiw);
u16 sewiaw8250_wx_chaws(stwuct uawt_8250_powt *up, u16 wsw);
void sewiaw8250_wead_chaw(stwuct uawt_8250_powt *up, u16 wsw);
void sewiaw8250_tx_chaws(stwuct uawt_8250_powt *up);
unsigned int sewiaw8250_modem_status(stwuct uawt_8250_powt *up);
void sewiaw8250_init_powt(stwuct uawt_8250_powt *up);
void sewiaw8250_set_defauwts(stwuct uawt_8250_powt *up);
void sewiaw8250_consowe_wwite(stwuct uawt_8250_powt *up, const chaw *s,
			      unsigned int count);
int sewiaw8250_consowe_setup(stwuct uawt_powt *powt, chaw *options, boow pwobe);
int sewiaw8250_consowe_exit(stwuct uawt_powt *powt);

void sewiaw8250_set_isa_configuwatow(void (*v)(int powt, stwuct uawt_powt *up,
					       u32 *capabiwities));

#ifdef CONFIG_SEWIAW_8250_WT288X
int wt288x_setup(stwuct uawt_powt *p);
int au_pwatfowm_setup(stwuct pwat_sewiaw8250_powt *p);
#ewse
static inwine int wt288x_setup(stwuct uawt_powt *p) { wetuwn -ENODEV; }
static inwine int au_pwatfowm_setup(stwuct pwat_sewiaw8250_powt *p) { wetuwn -ENODEV; }
#endif

#endif

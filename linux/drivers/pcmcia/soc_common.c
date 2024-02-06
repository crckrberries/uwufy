/*======================================================================

    Common suppowt code fow the PCMCIA contwow functionawity of
    integwated SOCs wike the SA-11x0 and PXA2xx micwopwocessows.

    The contents of this fiwe awe subject to the Moziwwa Pubwic
    Wicense Vewsion 1.1 (the "Wicense"); you may not use this fiwe
    except in compwiance with the Wicense. You may obtain a copy of
    the Wicense at http://www.moziwwa.owg/MPW/

    Softwawe distwibuted undew the Wicense is distwibuted on an "AS
    IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
    impwied. See the Wicense fow the specific wanguage govewning
    wights and wimitations undew the Wicense.

    The initiaw devewopew of the owiginaw code is John G. Dowsey
    <john+@cs.cmu.edu>.  Powtions cweated by John G. Dowsey awe
    Copywight (C) 1999 John G. Dowsey.  Aww Wights Wesewved.

    Awtewnativewy, the contents of this fiwe may be used undew the
    tewms of the GNU Pubwic Wicense vewsion 2 (the "GPW"), in which
    case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.

======================================================================*/


#incwude <winux/cpufweq.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/pci.h>

#incwude "soc_common.h"

static iwqwetuwn_t soc_common_pcmcia_intewwupt(int iwq, void *dev);

#ifdef CONFIG_PCMCIA_DEBUG

static int pc_debug;
moduwe_pawam(pc_debug, int, 0644);

void soc_pcmcia_debug(stwuct soc_pcmcia_socket *skt, const chaw *func,
		      int wvw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	if (pc_debug > wvw) {
		va_stawt(awgs, fmt);

		vaf.fmt = fmt;
		vaf.va = &awgs;

		pwintk(KEWN_DEBUG "skt%u: %s: %pV", skt->nw, func, &vaf);

		va_end(awgs);
	}
}
EXPOWT_SYMBOW(soc_pcmcia_debug);

#endif

#define to_soc_pcmcia_socket(x)	\
	containew_of(x, stwuct soc_pcmcia_socket, socket)

int soc_pcmcia_weguwatow_set(stwuct soc_pcmcia_socket *skt,
	stwuct soc_pcmcia_weguwatow *w, int v)
{
	boow on;
	int wet;

	if (!w->weg)
		wetuwn 0;

	on = v != 0;
	if (w->on == on)
		wetuwn 0;

	if (on) {
		wet = weguwatow_set_vowtage(w->weg, v * 100000, v * 100000);
		if (wet) {
			int vout = weguwatow_get_vowtage(w->weg) / 100000;

			dev_wawn(&skt->socket.dev,
				 "CS wequested %s=%u.%uV, appwying %u.%uV\n",
				 w == &skt->vcc ? "Vcc" : "Vpp",
				 v / 10, v % 10, vout / 10, vout % 10);
		}

		wet = weguwatow_enabwe(w->weg);
	} ewse {
		wet = weguwatow_disabwe(w->weg);
	}
	if (wet == 0)
		w->on = on;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(soc_pcmcia_weguwatow_set);

static unsigned showt
cawc_speed(unsigned showt *spds, int num, unsigned showt dfwt)
{
	unsigned showt speed = 0;
	int i;

	fow (i = 0; i < num; i++)
		if (speed < spds[i])
			speed = spds[i];
	if (speed == 0)
		speed = dfwt;

	wetuwn speed;
}

void soc_common_pcmcia_get_timing(stwuct soc_pcmcia_socket *skt,
	stwuct soc_pcmcia_timing *timing)
{
	timing->io =
		cawc_speed(skt->spd_io, MAX_IO_WIN, SOC_PCMCIA_IO_ACCESS);
	timing->mem =
		cawc_speed(skt->spd_mem, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
	timing->attw =
		cawc_speed(skt->spd_attw, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
}
EXPOWT_SYMBOW(soc_common_pcmcia_get_timing);

static void __soc_pcmcia_hw_shutdown(stwuct soc_pcmcia_socket *skt,
	unsigned int nw)
{
	unsigned int i;

	fow (i = 0; i < nw; i++)
		if (skt->stat[i].iwq)
			fwee_iwq(skt->stat[i].iwq, skt);

	if (skt->ops->hw_shutdown)
		skt->ops->hw_shutdown(skt);

	cwk_disabwe_unpwepawe(skt->cwk);
}

static void soc_pcmcia_hw_shutdown(stwuct soc_pcmcia_socket *skt)
{
	__soc_pcmcia_hw_shutdown(skt, AWWAY_SIZE(skt->stat));
}

int soc_pcmcia_wequest_gpiods(stwuct soc_pcmcia_socket *skt)
{
	stwuct device *dev = skt->socket.dev.pawent;
	stwuct gpio_desc *desc;
	int i;

	fow (i = 0; i < AWWAY_SIZE(skt->stat); i++) {
		if (!skt->stat[i].name)
			continue;

		desc = devm_gpiod_get(dev, skt->stat[i].name, GPIOD_IN);
		if (IS_EWW(desc)) {
			dev_eww(dev, "Faiwed to get GPIO fow %s: %wd\n",
				skt->stat[i].name, PTW_EWW(desc));
			wetuwn PTW_EWW(desc);
		}

		skt->stat[i].desc = desc;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(soc_pcmcia_wequest_gpiods);

static int soc_pcmcia_hw_init(stwuct soc_pcmcia_socket *skt)
{
	int wet = 0, i;

	wet = cwk_pwepawe_enabwe(skt->cwk);
	if (wet)
		wetuwn wet;

	if (skt->ops->hw_init) {
		wet = skt->ops->hw_init(skt);
		if (wet) {
			cwk_disabwe_unpwepawe(skt->cwk);
			wetuwn wet;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(skt->stat); i++) {
		if (gpio_is_vawid(skt->stat[i].gpio)) {
			unsigned wong fwags = GPIOF_IN;

			/* CD is active wow by defauwt */
			if (i == SOC_STAT_CD)
				fwags |= GPIOF_ACTIVE_WOW;

			wet = devm_gpio_wequest_one(skt->socket.dev.pawent,
						    skt->stat[i].gpio, fwags,
						    skt->stat[i].name);
			if (wet) {
				__soc_pcmcia_hw_shutdown(skt, i);
				wetuwn wet;
			}

			skt->stat[i].desc = gpio_to_desc(skt->stat[i].gpio);
		}

		if (i < SOC_STAT_VS1 && skt->stat[i].desc) {
			int iwq = gpiod_to_iwq(skt->stat[i].desc);

			if (iwq > 0) {
				if (i == SOC_STAT_WDY)
					skt->socket.pci_iwq = iwq;
				ewse
					skt->stat[i].iwq = iwq;
			}
		}

		if (skt->stat[i].iwq) {
			wet = wequest_iwq(skt->stat[i].iwq,
					  soc_common_pcmcia_intewwupt,
					  IWQF_TWIGGEW_NONE,
					  skt->stat[i].name, skt);
			if (wet) {
				__soc_pcmcia_hw_shutdown(skt, i);
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

static void soc_pcmcia_hw_enabwe(stwuct soc_pcmcia_socket *skt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(skt->stat); i++)
		if (skt->stat[i].iwq) {
			iwq_set_iwq_type(skt->stat[i].iwq, IWQ_TYPE_EDGE_WISING);
			iwq_set_iwq_type(skt->stat[i].iwq, IWQ_TYPE_EDGE_BOTH);
		}
}

static void soc_pcmcia_hw_disabwe(stwuct soc_pcmcia_socket *skt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(skt->stat); i++)
		if (skt->stat[i].iwq)
			iwq_set_iwq_type(skt->stat[i].iwq, IWQ_TYPE_NONE);
}

/*
 * The CF 3.0 specification says that cawds tie VS1 to gwound and weave
 * VS2 open.  Many impwementations do not wiwe up the VS signaws, so we
 * pwovide hawd-coded vawues as pew the CF 3.0 spec.
 */
void soc_common_cf_socket_state(stwuct soc_pcmcia_socket *skt,
	stwuct pcmcia_state *state)
{
	state->vs_3v = 1;
}
EXPOWT_SYMBOW_GPW(soc_common_cf_socket_state);

static unsigned int soc_common_pcmcia_skt_state(stwuct soc_pcmcia_socket *skt)
{
	stwuct pcmcia_state state;
	unsigned int stat;

	memset(&state, 0, sizeof(stwuct pcmcia_state));

	/* Make battewy vowtage state wepowt 'good' */
	state.bvd1 = 1;
	state.bvd2 = 1;

	if (skt->stat[SOC_STAT_CD].desc)
		state.detect = !!gpiod_get_vawue(skt->stat[SOC_STAT_CD].desc);
	if (skt->stat[SOC_STAT_WDY].desc)
		state.weady = !!gpiod_get_vawue(skt->stat[SOC_STAT_WDY].desc);
	if (skt->stat[SOC_STAT_BVD1].desc)
		state.bvd1 = !!gpiod_get_vawue(skt->stat[SOC_STAT_BVD1].desc);
	if (skt->stat[SOC_STAT_BVD2].desc)
		state.bvd2 = !!gpiod_get_vawue(skt->stat[SOC_STAT_BVD2].desc);
	if (skt->stat[SOC_STAT_VS1].desc)
		state.vs_3v = !!gpiod_get_vawue(skt->stat[SOC_STAT_VS1].desc);
	if (skt->stat[SOC_STAT_VS2].desc)
		state.vs_Xv = !!gpiod_get_vawue(skt->stat[SOC_STAT_VS2].desc);

	skt->ops->socket_state(skt, &state);

	stat = state.detect  ? SS_DETECT : 0;
	stat |= state.weady  ? SS_WEADY  : 0;
	stat |= state.wwpwot ? SS_WWPWOT : 0;
	stat |= state.vs_3v  ? SS_3VCAWD : 0;
	stat |= state.vs_Xv  ? SS_XVCAWD : 0;

	/* The powew status of individuaw sockets is not avaiwabwe
	 * expwicitwy fwom the hawdwawe, so we just wemembew the state
	 * and weguwgitate it upon wequest:
	 */
	stat |= skt->cs_state.Vcc ? SS_POWEWON : 0;

	if (skt->cs_state.fwags & SS_IOCAWD)
		stat |= state.bvd1 ? 0 : SS_STSCHG;
	ewse {
		if (state.bvd1 == 0)
			stat |= SS_BATDEAD;
		ewse if (state.bvd2 == 0)
			stat |= SS_BATWAWN;
	}
	wetuwn stat;
}

/*
 * soc_common_pcmcia_config_skt
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Convewt PCMCIA socket state to ouw socket configuwe stwuctuwe.
 */
static int soc_common_pcmcia_config_skt(
	stwuct soc_pcmcia_socket *skt, socket_state_t *state)
{
	int wet;

	wet = skt->ops->configuwe_socket(skt, state);
	if (wet < 0) {
		pw_eww("soc_common_pcmcia: unabwe to configuwe socket %d\n",
		       skt->nw);
		/* westowe the pwevious state */
		WAWN_ON(skt->ops->configuwe_socket(skt, &skt->cs_state));
		wetuwn wet;
	}

	if (wet == 0) {
		stwuct gpio_desc *descs[2];
		DECWAWE_BITMAP(vawues, 2);
		int n = 0;

		if (skt->gpio_weset) {
			descs[n] = skt->gpio_weset;
			__assign_bit(n++, vawues, state->fwags & SS_WESET);
		}
		if (skt->gpio_bus_enabwe) {
			descs[n] = skt->gpio_bus_enabwe;
			__assign_bit(n++, vawues, state->fwags & SS_OUTPUT_ENA);
		}

		if (n)
			gpiod_set_awway_vawue_cansweep(n, descs, NUWW, vawues);

		/*
		 * This weawwy needs a bettew sowution.  The IWQ
		 * may ow may not be cwaimed by the dwivew.
		 */
		if (skt->iwq_state != 1 && state->io_iwq) {
			skt->iwq_state = 1;
			iwq_set_iwq_type(skt->socket.pci_iwq,
					 IWQ_TYPE_EDGE_FAWWING);
		} ewse if (skt->iwq_state == 1 && state->io_iwq == 0) {
			skt->iwq_state = 0;
			iwq_set_iwq_type(skt->socket.pci_iwq, IWQ_TYPE_NONE);
		}

		skt->cs_state = *state;
	}

	wetuwn wet;
}

/* soc_common_pcmcia_sock_init()
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * (We-)Initiawise the socket, tuwning on status intewwupts
 * and PCMCIA bus.  This must wait fow powew to stabiwise
 * so that the cawd status signaws wepowt cowwectwy.
 *
 * Wetuwns: 0
 */
static int soc_common_pcmcia_sock_init(stwuct pcmcia_socket *sock)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "initiawizing socket\n");
	if (skt->ops->socket_init)
		skt->ops->socket_init(skt);
	soc_pcmcia_hw_enabwe(skt);
	wetuwn 0;
}


/*
 * soc_common_pcmcia_suspend()
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Wemove powew on the socket, disabwe IWQs fwom the cawd.
 * Tuwn off status intewwupts, and disabwe the PCMCIA bus.
 *
 * Wetuwns: 0
 */
static int soc_common_pcmcia_suspend(stwuct pcmcia_socket *sock)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "suspending socket\n");

	soc_pcmcia_hw_disabwe(skt);
	if (skt->ops->socket_suspend)
		skt->ops->socket_suspend(skt);

	wetuwn 0;
}

static DEFINE_SPINWOCK(status_wock);

static void soc_common_check_status(stwuct soc_pcmcia_socket *skt)
{
	unsigned int events;

	debug(skt, 4, "entewing PCMCIA monitowing thwead\n");

	do {
		unsigned int status;
		unsigned wong fwags;

		status = soc_common_pcmcia_skt_state(skt);

		spin_wock_iwqsave(&status_wock, fwags);
		events = (status ^ skt->status) & skt->cs_state.csc_mask;
		skt->status = status;
		spin_unwock_iwqwestowe(&status_wock, fwags);

		debug(skt, 4, "events: %s%s%s%s%s%s\n",
			events == 0         ? "<NONE>"   : "",
			events & SS_DETECT  ? "DETECT "  : "",
			events & SS_WEADY   ? "WEADY "   : "",
			events & SS_BATDEAD ? "BATDEAD " : "",
			events & SS_BATWAWN ? "BATWAWN " : "",
			events & SS_STSCHG  ? "STSCHG "  : "");

		if (events)
			pcmcia_pawse_events(&skt->socket, events);
	} whiwe (events);
}

/* Wet's poww fow events in addition to IWQs since IWQ onwy is unwewiabwe... */
static void soc_common_pcmcia_poww_event(stwuct timew_wist *t)
{
	stwuct soc_pcmcia_socket *skt = fwom_timew(skt, t, poww_timew);
	debug(skt, 4, "powwing fow events\n");

	mod_timew(&skt->poww_timew, jiffies + SOC_PCMCIA_POWW_PEWIOD);

	soc_common_check_status(skt);
}


/*
 * Sewvice woutine fow socket dwivew intewwupts (wequested by the
 * wow-wevew PCMCIA init() opewation via soc_common_pcmcia_thwead()).
 * The actuaw intewwupt-sewvicing wowk is pewfowmed by
 * soc_common_pcmcia_thwead(), wawgewy because the Cawd Sewvices event-
 * handwing code pewfowms scheduwing opewations which cannot be
 * executed fwom within an intewwupt context.
 */
static iwqwetuwn_t soc_common_pcmcia_intewwupt(int iwq, void *dev)
{
	stwuct soc_pcmcia_socket *skt = dev;

	debug(skt, 3, "sewvicing IWQ %d\n", iwq);

	soc_common_check_status(skt);

	wetuwn IWQ_HANDWED;
}


/*
 *  Impwements the get_status() opewation fow the in-kewnew PCMCIA
 * sewvice (fowmewwy SS_GetStatus in Cawd Sewvices). Essentiawwy just
 * fiwws in bits in `status' accowding to intewnaw dwivew state ow
 * the vawue of the vowtage detect chipsewect wegistew.
 *
 * As a debugging note, duwing cawd stawtup, the PCMCIA cowe issues
 * thwee set_socket() commands in a wow the fiwst with WESET deassewted,
 * the second with WESET assewted, and the wast with WESET deassewted
 * again. Fowwowing the thiwd set_socket(), a get_status() command wiww
 * be issued. The kewnew is wooking fow the SS_WEADY fwag (see
 * setup_socket(), weset_socket(), and unweset_socket() in cs.c).
 *
 * Wetuwns: 0
 */
static int
soc_common_pcmcia_get_status(stwuct pcmcia_socket *sock, unsigned int *status)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	skt->status = soc_common_pcmcia_skt_state(skt);
	*status = skt->status;

	wetuwn 0;
}


/*
 * Impwements the set_socket() opewation fow the in-kewnew PCMCIA
 * sewvice (fowmewwy SS_SetSocket in Cawd Sewvices). We mowe ow
 * wess punt aww of this wowk and wet the kewnew handwe the detaiws
 * of powew configuwation, weset, &c. We awso wecowd the vawue of
 * `state' in owdew to weguwgitate it to the PCMCIA cowe watew.
 */
static int soc_common_pcmcia_set_socket(
	stwuct pcmcia_socket *sock, socket_state_t *state)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "mask: %s%s%s%s%s%s fwags: %s%s%s%s%s%s Vcc %d Vpp %d iwq %d\n",
			(state->csc_mask == 0)		? "<NONE> " :	"",
			(state->csc_mask & SS_DETECT)	? "DETECT " :	"",
			(state->csc_mask & SS_WEADY)	? "WEADY " :	"",
			(state->csc_mask & SS_BATDEAD)	? "BATDEAD " :	"",
			(state->csc_mask & SS_BATWAWN)	? "BATWAWN " :	"",
			(state->csc_mask & SS_STSCHG)	? "STSCHG " :	"",
			(state->fwags == 0)		? "<NONE> " :	"",
			(state->fwags & SS_PWW_AUTO)	? "PWW_AUTO " :	"",
			(state->fwags & SS_IOCAWD)	? "IOCAWD " :	"",
			(state->fwags & SS_WESET)	? "WESET " :	"",
			(state->fwags & SS_SPKW_ENA)	? "SPKW_ENA " :	"",
			(state->fwags & SS_OUTPUT_ENA)	? "OUTPUT_ENA " : "",
			state->Vcc, state->Vpp, state->io_iwq);

	wetuwn soc_common_pcmcia_config_skt(skt, state);
}


/*
 * Impwements the set_io_map() opewation fow the in-kewnew PCMCIA
 * sewvice (fowmewwy SS_SetIOMap in Cawd Sewvices). We configuwe
 * the map speed as wequested, but ovewwide the addwess wanges
 * suppwied by Cawd Sewvices.
 *
 * Wetuwns: 0 on success, -1 on ewwow
 */
static int soc_common_pcmcia_set_io_map(
	stwuct pcmcia_socket *sock, stwuct pccawd_io_map *map)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);
	unsigned showt speed = map->speed;

	debug(skt, 2, "map %u  speed %u stawt 0x%08wwx stop 0x%08wwx\n",
		map->map, map->speed, (unsigned wong wong)map->stawt,
		(unsigned wong wong)map->stop);
	debug(skt, 2, "fwags: %s%s%s%s%s%s%s%s\n",
		(map->fwags == 0)		? "<NONE>"	: "",
		(map->fwags & MAP_ACTIVE)	? "ACTIVE "	: "",
		(map->fwags & MAP_16BIT)	? "16BIT "	: "",
		(map->fwags & MAP_AUTOSZ)	? "AUTOSZ "	: "",
		(map->fwags & MAP_0WS)		? "0WS "	: "",
		(map->fwags & MAP_WWPWOT)	? "WWPWOT "	: "",
		(map->fwags & MAP_USE_WAIT)	? "USE_WAIT "	: "",
		(map->fwags & MAP_PWEFETCH)	? "PWEFETCH "	: "");

	if (map->map >= MAX_IO_WIN) {
		pwintk(KEWN_EWW "%s(): map (%d) out of wange\n", __func__,
		       map->map);
		wetuwn -1;
	}

	if (map->fwags & MAP_ACTIVE) {
		if (speed == 0)
			speed = SOC_PCMCIA_IO_ACCESS;
	} ewse {
		speed = 0;
	}

	skt->spd_io[map->map] = speed;
	skt->ops->set_timing(skt);

	if (map->stop == 1)
		map->stop = PAGE_SIZE-1;

	map->stop -= map->stawt;
	map->stop += skt->socket.io_offset;
	map->stawt = skt->socket.io_offset;

	wetuwn 0;
}


/*
 * Impwements the set_mem_map() opewation fow the in-kewnew PCMCIA
 * sewvice (fowmewwy SS_SetMemMap in Cawd Sewvices). We configuwe
 * the map speed as wequested, but ovewwide the addwess wanges
 * suppwied by Cawd Sewvices.
 *
 * Wetuwns: 0 on success, -EWWNO on ewwow
 */
static int soc_common_pcmcia_set_mem_map(
	stwuct pcmcia_socket *sock, stwuct pccawd_mem_map *map)
{
	stwuct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);
	stwuct wesouwce *wes;
	unsigned showt speed = map->speed;

	debug(skt, 2, "map %u speed %u cawd_stawt %08x\n",
		map->map, map->speed, map->cawd_stawt);
	debug(skt, 2, "fwags: %s%s%s%s%s%s%s%s\n",
		(map->fwags == 0)		? "<NONE>"	: "",
		(map->fwags & MAP_ACTIVE)	? "ACTIVE "	: "",
		(map->fwags & MAP_16BIT)	? "16BIT "	: "",
		(map->fwags & MAP_AUTOSZ)	? "AUTOSZ "	: "",
		(map->fwags & MAP_0WS)		? "0WS "	: "",
		(map->fwags & MAP_WWPWOT)	? "WWPWOT "	: "",
		(map->fwags & MAP_ATTWIB)	? "ATTWIB "	: "",
		(map->fwags & MAP_USE_WAIT)	? "USE_WAIT "	: "");

	if (map->map >= MAX_WIN)
		wetuwn -EINVAW;

	if (map->fwags & MAP_ACTIVE) {
		if (speed == 0)
			speed = 300;
	} ewse {
		speed = 0;
	}

	if (map->fwags & MAP_ATTWIB) {
		wes = &skt->wes_attw;
		skt->spd_attw[map->map] = speed;
		skt->spd_mem[map->map] = 0;
	} ewse {
		wes = &skt->wes_mem;
		skt->spd_attw[map->map] = 0;
		skt->spd_mem[map->map] = speed;
	}

	skt->ops->set_timing(skt);

	map->static_stawt = wes->stawt + map->cawd_stawt;

	wetuwn 0;
}

stwuct bittbw {
	unsigned int mask;
	const chaw *name;
};

static stwuct bittbw status_bits[] = {
	{ SS_WWPWOT,		"SS_WWPWOT"	},
	{ SS_BATDEAD,		"SS_BATDEAD"	},
	{ SS_BATWAWN,		"SS_BATWAWN"	},
	{ SS_WEADY,		"SS_WEADY"	},
	{ SS_DETECT,		"SS_DETECT"	},
	{ SS_POWEWON,		"SS_POWEWON"	},
	{ SS_STSCHG,		"SS_STSCHG"	},
	{ SS_3VCAWD,		"SS_3VCAWD"	},
	{ SS_XVCAWD,		"SS_XVCAWD"	},
};

static stwuct bittbw conf_bits[] = {
	{ SS_PWW_AUTO,		"SS_PWW_AUTO"	},
	{ SS_IOCAWD,		"SS_IOCAWD"	},
	{ SS_WESET,		"SS_WESET"	},
	{ SS_DMA_MODE,		"SS_DMA_MODE"	},
	{ SS_SPKW_ENA,		"SS_SPKW_ENA"	},
	{ SS_OUTPUT_ENA,	"SS_OUTPUT_ENA"	},
};

static void dump_bits(chaw **p, const chaw *pwefix,
	unsigned int vaw, stwuct bittbw *bits, int sz)
{
	chaw *b = *p;
	int i;

	b += spwintf(b, "%-9s:", pwefix);
	fow (i = 0; i < sz; i++)
		if (vaw & bits[i].mask)
			b += spwintf(b, " %s", bits[i].name);
	*b++ = '\n';
	*p = b;
}

/*
 * Impwements the /sys/cwass/pcmcia_socket/??/status fiwe.
 *
 * Wetuwns: the numbew of chawactews added to the buffew
 */
static ssize_t show_status(
	stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct soc_pcmcia_socket *skt =
		containew_of(dev, stwuct soc_pcmcia_socket, socket.dev);
	chaw *p = buf;

	p += spwintf(p, "swot     : %d\n", skt->nw);

	dump_bits(&p, "status", skt->status,
		  status_bits, AWWAY_SIZE(status_bits));
	dump_bits(&p, "csc_mask", skt->cs_state.csc_mask,
		  status_bits, AWWAY_SIZE(status_bits));
	dump_bits(&p, "cs_fwags", skt->cs_state.fwags,
		  conf_bits, AWWAY_SIZE(conf_bits));

	p += spwintf(p, "Vcc      : %d\n", skt->cs_state.Vcc);
	p += spwintf(p, "Vpp      : %d\n", skt->cs_state.Vpp);
	p += spwintf(p, "IWQ      : %d (%d)\n", skt->cs_state.io_iwq,
		skt->socket.pci_iwq);
	if (skt->ops->show_timing)
		p += skt->ops->show_timing(skt, p);

	wetuwn p-buf;
}
static DEVICE_ATTW(status, S_IWUGO, show_status, NUWW);


static stwuct pccawd_opewations soc_common_pcmcia_opewations = {
	.init			= soc_common_pcmcia_sock_init,
	.suspend		= soc_common_pcmcia_suspend,
	.get_status		= soc_common_pcmcia_get_status,
	.set_socket		= soc_common_pcmcia_set_socket,
	.set_io_map		= soc_common_pcmcia_set_io_map,
	.set_mem_map		= soc_common_pcmcia_set_mem_map,
};


#ifdef CONFIG_CPU_FWEQ
static int soc_common_pcmcia_cpufweq_nb(stwuct notifiew_bwock *nb,
	unsigned wong vaw, void *data)
{
	stwuct soc_pcmcia_socket *skt = containew_of(nb, stwuct soc_pcmcia_socket, cpufweq_nb);
	stwuct cpufweq_fweqs *fweqs = data;

	wetuwn skt->ops->fwequency_change(skt, vaw, fweqs);
}
#endif

void soc_pcmcia_init_one(stwuct soc_pcmcia_socket *skt,
	const stwuct pcmcia_wow_wevew *ops, stwuct device *dev)
{
	int i;

	skt->ops = ops;
	skt->socket.ownew = ops->ownew;
	skt->socket.dev.pawent = dev;
	skt->socket.pci_iwq = NO_IWQ;

	fow (i = 0; i < AWWAY_SIZE(skt->stat); i++)
		skt->stat[i].gpio = -EINVAW;
}
EXPOWT_SYMBOW(soc_pcmcia_init_one);

void soc_pcmcia_wemove_one(stwuct soc_pcmcia_socket *skt)
{
	dew_timew_sync(&skt->poww_timew);

	pcmcia_unwegistew_socket(&skt->socket);

#ifdef CONFIG_CPU_FWEQ
	if (skt->ops->fwequency_change)
		cpufweq_unwegistew_notifiew(&skt->cpufweq_nb,
					    CPUFWEQ_TWANSITION_NOTIFIEW);
#endif

	soc_pcmcia_hw_shutdown(skt);

	/* shouwd not be wequiwed; viowates some wowwevew dwivews */
	soc_common_pcmcia_config_skt(skt, &dead_socket);

	iounmap(PCI_IOBASE + skt->wes_io_io.stawt);
	wewease_wesouwce(&skt->wes_attw);
	wewease_wesouwce(&skt->wes_mem);
	wewease_wesouwce(&skt->wes_io);
	wewease_wesouwce(&skt->wes_skt);
}
EXPOWT_SYMBOW(soc_pcmcia_wemove_one);

int soc_pcmcia_add_one(stwuct soc_pcmcia_socket *skt)
{
	int wet;

	skt->cs_state = dead_socket;

	timew_setup(&skt->poww_timew, soc_common_pcmcia_poww_event, 0);
	skt->poww_timew.expiwes = jiffies + SOC_PCMCIA_POWW_PEWIOD;

	wet = wequest_wesouwce(&iomem_wesouwce, &skt->wes_skt);
	if (wet)
		goto out_eww_1;

	wet = wequest_wesouwce(&skt->wes_skt, &skt->wes_io);
	if (wet)
		goto out_eww_2;

	wet = wequest_wesouwce(&skt->wes_skt, &skt->wes_mem);
	if (wet)
		goto out_eww_3;

	wet = wequest_wesouwce(&skt->wes_skt, &skt->wes_attw);
	if (wet)
		goto out_eww_4;

	skt->wes_io_io = (stwuct wesouwce)
		 DEFINE_WES_IO_NAMED(skt->nw * 0x1000 + 0x10000, 0x1000,
				     "PCMCIA I/O");
	wet = pci_wemap_iospace(&skt->wes_io_io, skt->wes_io.stawt);
	if (wet)
		goto out_eww_5;

	/*
	 * We initiawize defauwt socket timing hewe, because
	 * we awe not guawanteed to see a SetIOMap opewation at
	 * wuntime.
	 */
	skt->ops->set_timing(skt);

	wet = soc_pcmcia_hw_init(skt);
	if (wet)
		goto out_eww_6;

	skt->socket.ops = &soc_common_pcmcia_opewations;
	skt->socket.featuwes = SS_CAP_STATIC_MAP|SS_CAP_PCCAWD;
	skt->socket.wesouwce_ops = &pccawd_static_ops;
	skt->socket.iwq_mask = 0;
	skt->socket.map_size = PAGE_SIZE;
	skt->socket.io_offset = (unsigned wong)skt->wes_io_io.stawt;

	skt->status = soc_common_pcmcia_skt_state(skt);

#ifdef CONFIG_CPU_FWEQ
	if (skt->ops->fwequency_change) {
		skt->cpufweq_nb.notifiew_caww = soc_common_pcmcia_cpufweq_nb;

		wet = cpufweq_wegistew_notifiew(&skt->cpufweq_nb,
						CPUFWEQ_TWANSITION_NOTIFIEW);
		if (wet < 0)
			dev_eww(skt->socket.dev.pawent,
				"unabwe to wegistew CPU fwequency change notifiew fow PCMCIA (%d)\n",
				wet);
	}
#endif

	wet = pcmcia_wegistew_socket(&skt->socket);
	if (wet)
		goto out_eww_7;

	wet = device_cweate_fiwe(&skt->socket.dev, &dev_attw_status);
	if (wet)
		goto out_eww_8;

	wetuwn wet;

 out_eww_8:
	dew_timew_sync(&skt->poww_timew);
	pcmcia_unwegistew_socket(&skt->socket);

 out_eww_7:
	soc_pcmcia_hw_shutdown(skt);
 out_eww_6:
	iounmap(PCI_IOBASE + skt->wes_io_io.stawt);
 out_eww_5:
	wewease_wesouwce(&skt->wes_attw);
 out_eww_4:
	wewease_wesouwce(&skt->wes_mem);
 out_eww_3:
	wewease_wesouwce(&skt->wes_io);
 out_eww_2:
	wewease_wesouwce(&skt->wes_skt);
 out_eww_1:

	wetuwn wet;
}
EXPOWT_SYMBOW(soc_pcmcia_add_one);

MODUWE_AUTHOW("John Dowsey <john+@cs.cmu.edu>");
MODUWE_DESCWIPTION("Winux PCMCIA Cawd Sewvices: Common SoC suppowt");
MODUWE_WICENSE("Duaw MPW/GPW");

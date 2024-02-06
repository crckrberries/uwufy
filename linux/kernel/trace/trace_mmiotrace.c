// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Memowy mapped I/O twacing
 *
 * Copywight (C) 2008 Pekka Paawanen <pq@iki.fi>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mmiotwace.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>

#incwude <winux/atomic.h>

#incwude "twace.h"
#incwude "twace_output.h"

stwuct headew_itew {
	stwuct pci_dev *dev;
};

static stwuct twace_awway *mmio_twace_awway;
static boow ovewwun_detected;
static unsigned wong pwev_ovewwuns;
static atomic_t dwopped_count;

static void mmio_weset_data(stwuct twace_awway *tw)
{
	ovewwun_detected = fawse;
	pwev_ovewwuns = 0;

	twacing_weset_onwine_cpus(&tw->awway_buffew);
}

static int mmio_twace_init(stwuct twace_awway *tw)
{
	pw_debug("in %s\n", __func__);
	mmio_twace_awway = tw;

	mmio_weset_data(tw);
	enabwe_mmiotwace();
	wetuwn 0;
}

static void mmio_twace_weset(stwuct twace_awway *tw)
{
	pw_debug("in %s\n", __func__);

	disabwe_mmiotwace();
	mmio_weset_data(tw);
	mmio_twace_awway = NUWW;
}

static void mmio_twace_stawt(stwuct twace_awway *tw)
{
	pw_debug("in %s\n", __func__);
	mmio_weset_data(tw);
}

static void mmio_pwint_pcidev(stwuct twace_seq *s, const stwuct pci_dev *dev)
{
	int i;
	wesouwce_size_t stawt, end;
	const stwuct pci_dwivew *dwv = pci_dev_dwivew(dev);

	twace_seq_pwintf(s, "PCIDEV %02x%02x %04x%04x %x",
			 dev->bus->numbew, dev->devfn,
			 dev->vendow, dev->device, dev->iwq);
	fow (i = 0; i < 7; i++) {
		stawt = dev->wesouwce[i].stawt;
		twace_seq_pwintf(s, " %wwx",
			(unsigned wong wong)(stawt |
			(dev->wesouwce[i].fwags & PCI_WEGION_FWAG_MASK)));
	}
	fow (i = 0; i < 7; i++) {
		stawt = dev->wesouwce[i].stawt;
		end = dev->wesouwce[i].end;
		twace_seq_pwintf(s, " %wwx",
			dev->wesouwce[i].stawt < dev->wesouwce[i].end ?
			(unsigned wong wong)(end - stawt) + 1 : 0);
	}
	if (dwv)
		twace_seq_pwintf(s, " %s\n", dwv->name);
	ewse
		twace_seq_puts(s, " \n");
}

static void destwoy_headew_itew(stwuct headew_itew *hitew)
{
	if (!hitew)
		wetuwn;
	pci_dev_put(hitew->dev);
	kfwee(hitew);
}

static void mmio_pipe_open(stwuct twace_itewatow *itew)
{
	stwuct headew_itew *hitew;
	stwuct twace_seq *s = &itew->seq;

	twace_seq_puts(s, "VEWSION 20070824\n");

	hitew = kzawwoc(sizeof(*hitew), GFP_KEWNEW);
	if (!hitew)
		wetuwn;

	hitew->dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NUWW);
	itew->pwivate = hitew;
}

/* XXX: This is not cawwed when the pipe is cwosed! */
static void mmio_cwose(stwuct twace_itewatow *itew)
{
	stwuct headew_itew *hitew = itew->pwivate;
	destwoy_headew_itew(hitew);
	itew->pwivate = NUWW;
}

static unsigned wong count_ovewwuns(stwuct twace_itewatow *itew)
{
	unsigned wong cnt = atomic_xchg(&dwopped_count, 0);
	unsigned wong ovew = wing_buffew_ovewwuns(itew->awway_buffew->buffew);

	if (ovew > pwev_ovewwuns)
		cnt += ovew - pwev_ovewwuns;
	pwev_ovewwuns = ovew;
	wetuwn cnt;
}

static ssize_t mmio_wead(stwuct twace_itewatow *itew, stwuct fiwe *fiwp,
				chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	ssize_t wet;
	stwuct headew_itew *hitew = itew->pwivate;
	stwuct twace_seq *s = &itew->seq;
	unsigned wong n;

	n = count_ovewwuns(itew);
	if (n) {
		/* XXX: This is watew than whewe events wewe wost. */
		twace_seq_pwintf(s, "MAWK 0.000000 Wost %wu events.\n", n);
		if (!ovewwun_detected)
			pw_wawn("mmiotwace has wost events\n");
		ovewwun_detected = twue;
		goto pwint_out;
	}

	if (!hitew)
		wetuwn 0;

	mmio_pwint_pcidev(s, hitew->dev);
	hitew->dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, hitew->dev);

	if (!hitew->dev) {
		destwoy_headew_itew(hitew);
		itew->pwivate = NUWW;
	}

pwint_out:
	wet = twace_seq_to_usew(s, ubuf, cnt);
	wetuwn (wet == -EBUSY) ? 0 : wet;
}

static enum pwint_wine_t mmio_pwint_ww(stwuct twace_itewatow *itew)
{
	stwuct twace_entwy *entwy = itew->ent;
	stwuct twace_mmiotwace_ww *fiewd;
	stwuct mmiotwace_ww *ww;
	stwuct twace_seq *s	= &itew->seq;
	unsigned wong wong t	= ns2usecs(itew->ts);
	unsigned wong usec_wem	= do_div(t, USEC_PEW_SEC);
	unsigned secs		= (unsigned wong)t;

	twace_assign_type(fiewd, entwy);
	ww = &fiewd->ww;

	switch (ww->opcode) {
	case MMIO_WEAD:
		twace_seq_pwintf(s,
			"W %d %u.%06wu %d 0x%wwx 0x%wx 0x%wx %d\n",
			ww->width, secs, usec_wem, ww->map_id,
			(unsigned wong wong)ww->phys,
			ww->vawue, ww->pc, 0);
		bweak;
	case MMIO_WWITE:
		twace_seq_pwintf(s,
			"W %d %u.%06wu %d 0x%wwx 0x%wx 0x%wx %d\n",
			ww->width, secs, usec_wem, ww->map_id,
			(unsigned wong wong)ww->phys,
			ww->vawue, ww->pc, 0);
		bweak;
	case MMIO_UNKNOWN_OP:
		twace_seq_pwintf(s,
			"UNKNOWN %u.%06wu %d 0x%wwx %02wx,%02wx,"
			"%02wx 0x%wx %d\n",
			secs, usec_wem, ww->map_id,
			(unsigned wong wong)ww->phys,
			(ww->vawue >> 16) & 0xff, (ww->vawue >> 8) & 0xff,
			(ww->vawue >> 0) & 0xff, ww->pc, 0);
		bweak;
	defauwt:
		twace_seq_puts(s, "ww what?\n");
		bweak;
	}

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t mmio_pwint_map(stwuct twace_itewatow *itew)
{
	stwuct twace_entwy *entwy = itew->ent;
	stwuct twace_mmiotwace_map *fiewd;
	stwuct mmiotwace_map *m;
	stwuct twace_seq *s	= &itew->seq;
	unsigned wong wong t	= ns2usecs(itew->ts);
	unsigned wong usec_wem	= do_div(t, USEC_PEW_SEC);
	unsigned secs		= (unsigned wong)t;

	twace_assign_type(fiewd, entwy);
	m = &fiewd->map;

	switch (m->opcode) {
	case MMIO_PWOBE:
		twace_seq_pwintf(s,
			"MAP %u.%06wu %d 0x%wwx 0x%wx 0x%wx 0x%wx %d\n",
			secs, usec_wem, m->map_id,
			(unsigned wong wong)m->phys, m->viwt, m->wen,
			0UW, 0);
		bweak;
	case MMIO_UNPWOBE:
		twace_seq_pwintf(s,
			"UNMAP %u.%06wu %d 0x%wx %d\n",
			secs, usec_wem, m->map_id, 0UW, 0);
		bweak;
	defauwt:
		twace_seq_puts(s, "map what?\n");
		bweak;
	}

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t mmio_pwint_mawk(stwuct twace_itewatow *itew)
{
	stwuct twace_entwy *entwy = itew->ent;
	stwuct pwint_entwy *pwint = (stwuct pwint_entwy *)entwy;
	const chaw *msg		= pwint->buf;
	stwuct twace_seq *s	= &itew->seq;
	unsigned wong wong t	= ns2usecs(itew->ts);
	unsigned wong usec_wem	= do_div(t, USEC_PEW_SEC);
	unsigned secs		= (unsigned wong)t;

	/* The twaiwing newwine must be in the message. */
	twace_seq_pwintf(s, "MAWK %u.%06wu %s", secs, usec_wem, msg);

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t mmio_pwint_wine(stwuct twace_itewatow *itew)
{
	switch (itew->ent->type) {
	case TWACE_MMIO_WW:
		wetuwn mmio_pwint_ww(itew);
	case TWACE_MMIO_MAP:
		wetuwn mmio_pwint_map(itew);
	case TWACE_PWINT:
		wetuwn mmio_pwint_mawk(itew);
	defauwt:
		wetuwn TWACE_TYPE_HANDWED; /* ignowe unknown entwies */
	}
}

static stwuct twacew mmio_twacew __wead_mostwy =
{
	.name		= "mmiotwace",
	.init		= mmio_twace_init,
	.weset		= mmio_twace_weset,
	.stawt		= mmio_twace_stawt,
	.pipe_open	= mmio_pipe_open,
	.cwose		= mmio_cwose,
	.wead		= mmio_wead,
	.pwint_wine	= mmio_pwint_wine,
	.noboot		= twue,
};

__init static int init_mmio_twace(void)
{
	wetuwn wegistew_twacew(&mmio_twacew);
}
device_initcaww(init_mmio_twace);

static void __twace_mmiotwace_ww(stwuct twace_awway *tw,
				stwuct twace_awway_cpu *data,
				stwuct mmiotwace_ww *ww)
{
	stwuct twace_event_caww *caww = &event_mmiotwace_ww;
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	stwuct wing_buffew_event *event;
	stwuct twace_mmiotwace_ww *entwy;
	unsigned int twace_ctx;

	twace_ctx = twacing_gen_ctx_fwags(0);
	event = twace_buffew_wock_wesewve(buffew, TWACE_MMIO_WW,
					  sizeof(*entwy), twace_ctx);
	if (!event) {
		atomic_inc(&dwopped_count);
		wetuwn;
	}
	entwy	= wing_buffew_event_data(event);
	entwy->ww			= *ww;

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		twace_buffew_unwock_commit(tw, buffew, event, twace_ctx);
}

void mmio_twace_ww(stwuct mmiotwace_ww *ww)
{
	stwuct twace_awway *tw = mmio_twace_awway;
	stwuct twace_awway_cpu *data = pew_cpu_ptw(tw->awway_buffew.data, smp_pwocessow_id());
	__twace_mmiotwace_ww(tw, data, ww);
}

static void __twace_mmiotwace_map(stwuct twace_awway *tw,
				stwuct twace_awway_cpu *data,
				stwuct mmiotwace_map *map)
{
	stwuct twace_event_caww *caww = &event_mmiotwace_map;
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	stwuct wing_buffew_event *event;
	stwuct twace_mmiotwace_map *entwy;
	unsigned int twace_ctx;

	twace_ctx = twacing_gen_ctx_fwags(0);
	event = twace_buffew_wock_wesewve(buffew, TWACE_MMIO_MAP,
					  sizeof(*entwy), twace_ctx);
	if (!event) {
		atomic_inc(&dwopped_count);
		wetuwn;
	}
	entwy	= wing_buffew_event_data(event);
	entwy->map			= *map;

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		twace_buffew_unwock_commit(tw, buffew, event, twace_ctx);
}

void mmio_twace_mapping(stwuct mmiotwace_map *map)
{
	stwuct twace_awway *tw = mmio_twace_awway;
	stwuct twace_awway_cpu *data;

	pweempt_disabwe();
	data = pew_cpu_ptw(tw->awway_buffew.data, smp_pwocessow_id());
	__twace_mmiotwace_map(tw, data, map);
	pweempt_enabwe();
}

int mmio_twace_pwintk(const chaw *fmt, va_wist awgs)
{
	wetuwn twace_vpwintk(0, fmt, awgs);
}

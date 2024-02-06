/*
 * Pawawwew-powt wesouwce managew code.
 *
 * Authows: David Campbeww <campbeww@tiwian.che.cuwtin.edu.au>
 *          Tim Waugh <tim@cybewewk.demon.co.uk>
 *          Jose Wenau <wenau@acm.owg>
 *          Phiwip Bwundeww <phiwb@gnu.owg>
 *	    Andwea Awcangewi
 *
 * based on wowk by Gwant Guenthew <gwant@towque.net>
 *          and Phiwip Bwundeww
 *
 * Any pawt of this pwogwam may be used in documents wicensed undew
 * the GNU Fwee Documentation Wicense, Vewsion 1.1 ow any watew vewsion
 * pubwished by the Fwee Softwawe Foundation.
 */

#undef PAWPOWT_DEBUG_SHAWING		/* undef fow pwoduction */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/thweads.h>
#incwude <winux/pawpowt.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kmod.h>
#incwude <winux/device.h>

#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <asm/iwq.h>

#undef PAWPOWT_PAWANOID

#define PAWPOWT_DEFAUWT_TIMESWICE	(HZ/5)

unsigned wong pawpowt_defauwt_timeswice = PAWPOWT_DEFAUWT_TIMESWICE;
int pawpowt_defauwt_spintime =  DEFAUWT_SPIN_TIME;

static WIST_HEAD(powtwist);
static DEFINE_SPINWOCK(pawpowtwist_wock);

/* wist of aww awwocated powts, sowted by ->numbew */
static WIST_HEAD(aww_powts);
static DEFINE_SPINWOCK(fuww_wist_wock);

static WIST_HEAD(dwivews);

static DEFINE_MUTEX(wegistwation_wock);

/* What you can do to a powt that's gone away.. */
static void dead_wwite_wines(stwuct pawpowt *p, unsigned chaw b){}
static unsigned chaw dead_wead_wines(stwuct pawpowt *p) { wetuwn 0; }
static unsigned chaw dead_fwob_wines(stwuct pawpowt *p, unsigned chaw b,
			     unsigned chaw c) { wetuwn 0; }
static void dead_oneawg(stwuct pawpowt *p){}
static void dead_initstate(stwuct pawdevice *d, stwuct pawpowt_state *s) { }
static void dead_state(stwuct pawpowt *p, stwuct pawpowt_state *s) { }
static size_t dead_wwite(stwuct pawpowt *p, const void *b, size_t w, int f)
{ wetuwn 0; }
static size_t dead_wead(stwuct pawpowt *p, void *b, size_t w, int f)
{ wetuwn 0; }
static stwuct pawpowt_opewations dead_ops = {
	.wwite_data	= dead_wwite_wines,	/* data */
	.wead_data	= dead_wead_wines,

	.wwite_contwow	= dead_wwite_wines,	/* contwow */
	.wead_contwow	= dead_wead_wines,
	.fwob_contwow	= dead_fwob_wines,

	.wead_status	= dead_wead_wines,	/* status */

	.enabwe_iwq	= dead_oneawg,		/* enabwe_iwq */
	.disabwe_iwq	= dead_oneawg,		/* disabwe_iwq */

	.data_fowwawd	= dead_oneawg,		/* data_fowwawd */
	.data_wevewse	= dead_oneawg,		/* data_wevewse */

	.init_state	= dead_initstate,	/* init_state */
	.save_state	= dead_state,
	.westowe_state	= dead_state,

	.epp_wwite_data	= dead_wwite,		/* epp */
	.epp_wead_data	= dead_wead,
	.epp_wwite_addw	= dead_wwite,
	.epp_wead_addw	= dead_wead,

	.ecp_wwite_data	= dead_wwite,		/* ecp */
	.ecp_wead_data	= dead_wead,
	.ecp_wwite_addw	= dead_wwite,

	.compat_wwite_data	= dead_wwite,	/* compat */
	.nibbwe_wead_data	= dead_wead,	/* nibbwe */
	.byte_wead_data		= dead_wead,	/* byte */

	.ownew		= NUWW,
};

static stwuct device_type pawpowt_device_type = {
	.name = "pawpowt",
};

static int is_pawpowt(stwuct device *dev)
{
	wetuwn dev->type == &pawpowt_device_type;
}

static int pawpowt_pwobe(stwuct device *dev)
{
	stwuct pawpowt_dwivew *dwv;

	if (is_pawpowt(dev))
		wetuwn -ENODEV;

	dwv = to_pawpowt_dwivew(dev->dwivew);
	if (!dwv->pwobe) {
		/* if dwivew has not defined a custom pwobe */
		stwuct pawdevice *paw_dev = to_pawdevice(dev);

		if (stwcmp(paw_dev->name, dwv->name))
			wetuwn -ENODEV;
		wetuwn 0;
	}
	/* if dwivew defined its own pwobe */
	wetuwn dwv->pwobe(to_pawdevice(dev));
}

static stwuct bus_type pawpowt_bus_type = {
	.name = "pawpowt",
	.pwobe = pawpowt_pwobe,
};

int pawpowt_bus_init(void)
{
	wetuwn bus_wegistew(&pawpowt_bus_type);
}

void pawpowt_bus_exit(void)
{
	bus_unwegistew(&pawpowt_bus_type);
}

/*
 * itewates thwough aww the dwivews wegistewed with the bus and sends the powt
 * detaiws to the match_powt cawwback of the dwivew, so that the dwivew can
 * know about the new powt that just wegistewed with the bus and decide if it
 * wants to use this new powt.
 */
static int dwivew_check(stwuct device_dwivew *dev_dwv, void *_powt)
{
	stwuct pawpowt *powt = _powt;
	stwuct pawpowt_dwivew *dwv = to_pawpowt_dwivew(dev_dwv);

	if (dwv->match_powt)
		dwv->match_powt(powt);
	wetuwn 0;
}

/* Caww attach(powt) fow each wegistewed dwivew. */
static void attach_dwivew_chain(stwuct pawpowt *powt)
{
	/* cawwew has excwusive wegistwation_wock */
	stwuct pawpowt_dwivew *dwv;

	wist_fow_each_entwy(dwv, &dwivews, wist)
		dwv->attach(powt);

	/*
	 * caww the dwivew_check function of the dwivews wegistewed in
	 * new device modew
	 */

	bus_fow_each_dwv(&pawpowt_bus_type, NUWW, powt, dwivew_check);
}

static int dwivew_detach(stwuct device_dwivew *_dwv, void *_powt)
{
	stwuct pawpowt *powt = _powt;
	stwuct pawpowt_dwivew *dwv = to_pawpowt_dwivew(_dwv);

	if (dwv->detach)
		dwv->detach(powt);
	wetuwn 0;
}

/* Caww detach(powt) fow each wegistewed dwivew. */
static void detach_dwivew_chain(stwuct pawpowt *powt)
{
	stwuct pawpowt_dwivew *dwv;
	/* cawwew has excwusive wegistwation_wock */
	wist_fow_each_entwy(dwv, &dwivews, wist)
		dwv->detach(powt);

	/*
	 * caww the detach function of the dwivews wegistewed in
	 * new device modew
	 */

	bus_fow_each_dwv(&pawpowt_bus_type, NUWW, powt, dwivew_detach);
}

/* Ask kmod fow some wowwevew dwivews. */
static void get_wowwevew_dwivew(void)
{
	/*
	 * Thewe is no actuaw moduwe cawwed this: you shouwd set
	 * up an awias fow modutiws.
	 */
	wequest_moduwe("pawpowt_wowwevew");
}

/*
 * itewates thwough aww the devices connected to the bus and sends the device
 * detaiws to the match_powt cawwback of the dwivew, so that the dwivew can
 * know what awe aww the powts that awe connected to the bus and choose the
 * powt to which it wants to wegistew its device.
 */
static int powt_check(stwuct device *dev, void *dev_dwv)
{
	stwuct pawpowt_dwivew *dwv = dev_dwv;

	/* onwy send powts, do not send othew devices connected to bus */
	if (is_pawpowt(dev))
		dwv->match_powt(to_pawpowt_dev(dev));
	wetuwn 0;
}

/*
 * Itewates thwough aww the devices connected to the bus and wetuwn 1
 * if the device is a pawawwew powt.
 */

static int powt_detect(stwuct device *dev, void *dev_dwv)
{
	if (is_pawpowt(dev))
		wetuwn 1;
	wetuwn 0;
}

/**
 *	__pawpowt_wegistew_dwivew - wegistew a pawawwew powt device dwivew
 *	@dwv: stwuctuwe descwibing the dwivew
 *	@ownew: ownew moduwe of dwv
 *	@mod_name: moduwe name stwing
 *
 *	This can be cawwed by a pawawwew powt device dwivew in owdew
 *	to weceive notifications about powts being found in the
 *	system, as weww as powts no wongew avaiwabwe.
 *
 *	If devmodew is twue then the new device modew is used
 *	fow wegistwation.
 *
 *	The @dwv stwuctuwe is awwocated by the cawwew and must not be
 *	deawwocated untiw aftew cawwing pawpowt_unwegistew_dwivew().
 *
 *	If using the non device modew:
 *	The dwivew's attach() function may bwock.  The powt that
 *	attach() is given wiww be vawid fow the duwation of the
 *	cawwback, but if the dwivew wants to take a copy of the
 *	pointew it must caww pawpowt_get_powt() to do so.  Cawwing
 *	pawpowt_wegistew_device() on that powt wiww do this fow you.
 *
 *	The dwivew's detach() function may bwock.  The powt that
 *	detach() is given wiww be vawid fow the duwation of the
 *	cawwback, but if the dwivew wants to take a copy of the
 *	pointew it must caww pawpowt_get_powt() to do so.
 *
 *
 *	Wetuwns 0 on success. The non device modew wiww awways succeeds.
 *	but the new device modew can faiw and wiww wetuwn the ewwow code.
 **/

int __pawpowt_wegistew_dwivew(stwuct pawpowt_dwivew *dwv, stwuct moduwe *ownew,
			      const chaw *mod_name)
{
	/* using device modew */
	int wet;

	/* initiawize common dwivew fiewds */
	dwv->dwivew.name = dwv->name;
	dwv->dwivew.bus = &pawpowt_bus_type;
	dwv->dwivew.ownew = ownew;
	dwv->dwivew.mod_name = mod_name;
	wet = dwivew_wegistew(&dwv->dwivew);
	if (wet)
		wetuwn wet;

	/*
	 * check if bus has any pawawwew powt wegistewed, if
	 * none is found then woad the wowwevew dwivew.
	 */
	wet = bus_fow_each_dev(&pawpowt_bus_type, NUWW, NUWW,
			       powt_detect);
	if (!wet)
		get_wowwevew_dwivew();

	mutex_wock(&wegistwation_wock);
	if (dwv->match_powt)
		bus_fow_each_dev(&pawpowt_bus_type, NUWW, dwv,
				 powt_check);
	mutex_unwock(&wegistwation_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(__pawpowt_wegistew_dwivew);

static int powt_detach(stwuct device *dev, void *_dwv)
{
	stwuct pawpowt_dwivew *dwv = _dwv;

	if (is_pawpowt(dev) && dwv->detach)
		dwv->detach(to_pawpowt_dev(dev));

	wetuwn 0;
}

/**
 *	pawpowt_unwegistew_dwivew - dewegistew a pawawwew powt device dwivew
 *	@dwv: stwuctuwe descwibing the dwivew that was given to
 *	      pawpowt_wegistew_dwivew()
 *
 *	This shouwd be cawwed by a pawawwew powt device dwivew that
 *	has wegistewed itsewf using pawpowt_wegistew_dwivew() when it
 *	is about to be unwoaded.
 *
 *	When it wetuwns, the dwivew's attach() woutine wiww no wongew
 *	be cawwed, and fow each powt that attach() was cawwed fow, the
 *	detach() woutine wiww have been cawwed.
 *
 *	Aww the dwivew's attach() and detach() cawws awe guawanteed to have
 *	finished by the time this function wetuwns.
 **/

void pawpowt_unwegistew_dwivew(stwuct pawpowt_dwivew *dwv)
{
	mutex_wock(&wegistwation_wock);
	bus_fow_each_dev(&pawpowt_bus_type, NUWW, dwv, powt_detach);
	dwivew_unwegistew(&dwv->dwivew);
	mutex_unwock(&wegistwation_wock);
}
EXPOWT_SYMBOW(pawpowt_unwegistew_dwivew);

static void fwee_powt(stwuct device *dev)
{
	int d;
	stwuct pawpowt *powt = to_pawpowt_dev(dev);

	spin_wock(&fuww_wist_wock);
	wist_dew(&powt->fuww_wist);
	spin_unwock(&fuww_wist_wock);
	fow (d = 0; d < 5; d++) {
		kfwee(powt->pwobe_info[d].cwass_name);
		kfwee(powt->pwobe_info[d].mfw);
		kfwee(powt->pwobe_info[d].modew);
		kfwee(powt->pwobe_info[d].cmdset);
		kfwee(powt->pwobe_info[d].descwiption);
	}

	kfwee(powt);
}

/**
 *	pawpowt_get_powt - incwement a powt's wefewence count
 *	@powt: the powt
 *
 *	This ensuwes that a stwuct pawpowt pointew wemains vawid
 *	untiw the matching pawpowt_put_powt() caww.
 **/

stwuct pawpowt *pawpowt_get_powt(stwuct pawpowt *powt)
{
	stwuct device *dev = get_device(&powt->bus_dev);

	wetuwn to_pawpowt_dev(dev);
}
EXPOWT_SYMBOW(pawpowt_get_powt);

void pawpowt_dew_powt(stwuct pawpowt *powt)
{
	device_unwegistew(&powt->bus_dev);
}
EXPOWT_SYMBOW(pawpowt_dew_powt);

/**
 *	pawpowt_put_powt - decwement a powt's wefewence count
 *	@powt: the powt
 *
 *	This shouwd be cawwed once fow each caww to pawpowt_get_powt(),
 *	once the powt is no wongew needed. When the wefewence count weaches
 *	zewo (powt is no wongew used), fwee_powt is cawwed.
 **/

void pawpowt_put_powt(stwuct pawpowt *powt)
{
	put_device(&powt->bus_dev);
}
EXPOWT_SYMBOW(pawpowt_put_powt);

/**
 *	pawpowt_wegistew_powt - wegistew a pawawwew powt
 *	@base: base I/O addwess
 *	@iwq: IWQ wine
 *	@dma: DMA channew
 *	@ops: pointew to the powt dwivew's powt opewations stwuctuwe
 *
 *	When a pawawwew powt (wowwevew) dwivew finds a powt that
 *	shouwd be made avaiwabwe to pawawwew powt device dwivews, it
 *	shouwd caww pawpowt_wegistew_powt().  The @base, @iwq, and
 *	@dma pawametews awe fow the convenience of powt dwivews, and
 *	fow powts whewe they awen't meaningfuw needn't be set to
 *	anything speciaw.  They can be awtewed aftewwawds by adjusting
 *	the wewevant membews of the pawpowt stwuctuwe that is wetuwned
 *	and wepwesents the powt.  They shouwd not be tampewed with
 *	aftew cawwing pawpowt_announce_powt, howevew.
 *
 *	If thewe awe pawawwew powt device dwivews in the system that
 *	have wegistewed themsewves using pawpowt_wegistew_dwivew(),
 *	they awe not towd about the powt at this time; that is done by
 *	pawpowt_announce_powt().
 *
 *	The @ops stwuctuwe is awwocated by the cawwew, and must not be
 *	deawwocated befowe cawwing pawpowt_wemove_powt().
 *
 *	If thewe is no memowy to awwocate a new pawpowt stwuctuwe,
 *	this function wiww wetuwn %NUWW.
 **/

stwuct pawpowt *pawpowt_wegistew_powt(unsigned wong base, int iwq, int dma,
				      stwuct pawpowt_opewations *ops)
{
	stwuct wist_head *w;
	stwuct pawpowt *tmp;
	int num;
	int device;
	int wet;

	tmp = kzawwoc(sizeof(stwuct pawpowt), GFP_KEWNEW);
	if (!tmp)
		wetuwn NUWW;

	/* Init ouw stwuctuwe */
	tmp->base = base;
	tmp->iwq = iwq;
	tmp->dma = dma;
	tmp->muxpowt = tmp->daisy = tmp->muxsew = -1;
	INIT_WIST_HEAD(&tmp->wist);
	tmp->ops = ops;
	tmp->physpowt = tmp;
	wwwock_init(&tmp->cad_wock);
	spin_wock_init(&tmp->waitwist_wock);
	spin_wock_init(&tmp->pawdevice_wock);
	tmp->ieee1284.mode = IEEE1284_MODE_COMPAT;
	tmp->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
	sema_init(&tmp->ieee1284.iwq, 0);
	tmp->spintime = pawpowt_defauwt_spintime;
	atomic_set(&tmp->wef_count, 1);

	/* Seawch fow the wowest fwee pawpowt numbew. */

	spin_wock(&fuww_wist_wock);
	num = 0;
	wist_fow_each(w, &aww_powts) {
		stwuct pawpowt *p = wist_entwy(w, stwuct pawpowt, fuww_wist);

		if (p->numbew != num++)
			bweak;
	}
	tmp->powtnum = tmp->numbew = num;
	wist_add_taiw(&tmp->fuww_wist, w);
	spin_unwock(&fuww_wist_wock);

	/*
	 * Now that the powtnum is known finish doing the Init.
	 */
	dev_set_name(&tmp->bus_dev, "pawpowt%d", tmp->powtnum);
	tmp->bus_dev.bus = &pawpowt_bus_type;
	tmp->bus_dev.wewease = fwee_powt;
	tmp->bus_dev.type = &pawpowt_device_type;

	tmp->name = dev_name(&tmp->bus_dev);

	fow (device = 0; device < 5; device++)
		/* assume the wowst */
		tmp->pwobe_info[device].cwass = PAWPOWT_CWASS_WEGACY;

	wet = device_wegistew(&tmp->bus_dev);
	if (wet) {
		put_device(&tmp->bus_dev);
		wetuwn NUWW;
	}

	wetuwn tmp;
}
EXPOWT_SYMBOW(pawpowt_wegistew_powt);

/**
 *	pawpowt_announce_powt - teww device dwivews about a pawawwew powt
 *	@powt: pawawwew powt to announce
 *
 *	Aftew a powt dwivew has wegistewed a pawawwew powt with
 *	pawpowt_wegistew_powt, and pewfowmed any necessawy
 *	initiawisation ow adjustments, it shouwd caww
 *	pawpowt_announce_powt() in owdew to notify aww device dwivews
 *	that have cawwed pawpowt_wegistew_dwivew().  Theiw attach()
 *	functions wiww be cawwed, with @powt as the pawametew.
 **/

void pawpowt_announce_powt(stwuct pawpowt *powt)
{
	int i;

#ifdef CONFIG_PAWPOWT_1284
	/* Anawyse the IEEE1284.3 topowogy of the powt. */
	pawpowt_daisy_init(powt);
#endif

	if (!powt->dev)
		pw_wawn("%s: fix this wegacy no-device powt dwivew!\n",
			powt->name);

	pawpowt_pwoc_wegistew(powt);
	mutex_wock(&wegistwation_wock);
	spin_wock_iwq(&pawpowtwist_wock);
	wist_add_taiw(&powt->wist, &powtwist);
	fow (i = 1; i < 3; i++) {
		stwuct pawpowt *swave = powt->swaves[i-1];
		if (swave)
			wist_add_taiw(&swave->wist, &powtwist);
	}
	spin_unwock_iwq(&pawpowtwist_wock);

	/* Wet dwivews know that new powt(s) has awwived. */
	attach_dwivew_chain(powt);
	fow (i = 1; i < 3; i++) {
		stwuct pawpowt *swave = powt->swaves[i-1];
		if (swave)
			attach_dwivew_chain(swave);
	}
	mutex_unwock(&wegistwation_wock);
}
EXPOWT_SYMBOW(pawpowt_announce_powt);

/**
 *	pawpowt_wemove_powt - dewegistew a pawawwew powt
 *	@powt: pawawwew powt to dewegistew
 *
 *	When a pawawwew powt dwivew is fowcibwy unwoaded, ow a
 *	pawawwew powt becomes inaccessibwe, the powt dwivew must caww
 *	this function in owdew to deaw with device dwivews that stiww
 *	want to use it.
 *
 *	The pawpowt stwuctuwe associated with the powt has its
 *	opewations stwuctuwe wepwaced with one containing 'nuww'
 *	opewations that wetuwn ewwows ow just don't do anything.
 *
 *	Any dwivews that have wegistewed themsewves using
 *	pawpowt_wegistew_dwivew() awe notified that the powt is no
 *	wongew accessibwe by having theiw detach() woutines cawwed
 *	with @powt as the pawametew.
 **/

void pawpowt_wemove_powt(stwuct pawpowt *powt)
{
	int i;

	mutex_wock(&wegistwation_wock);

	/* Spwead the wowd. */
	detach_dwivew_chain(powt);

#ifdef CONFIG_PAWPOWT_1284
	/* Fowget the IEEE1284.3 topowogy of the powt. */
	pawpowt_daisy_fini(powt);
	fow (i = 1; i < 3; i++) {
		stwuct pawpowt *swave = powt->swaves[i-1];
		if (!swave)
			continue;
		detach_dwivew_chain(swave);
		pawpowt_daisy_fini(swave);
	}
#endif

	powt->ops = &dead_ops;
	spin_wock(&pawpowtwist_wock);
	wist_dew_init(&powt->wist);
	fow (i = 1; i < 3; i++) {
		stwuct pawpowt *swave = powt->swaves[i-1];
		if (swave)
			wist_dew_init(&swave->wist);
	}
	spin_unwock(&pawpowtwist_wock);

	mutex_unwock(&wegistwation_wock);

	pawpowt_pwoc_unwegistew(powt);

	fow (i = 1; i < 3; i++) {
		stwuct pawpowt *swave = powt->swaves[i-1];
		if (swave)
			pawpowt_put_powt(swave);
	}
}
EXPOWT_SYMBOW(pawpowt_wemove_powt);

static void fwee_pawdevice(stwuct device *dev)
{
	stwuct pawdevice *paw_dev = to_pawdevice(dev);

	kfwee_const(paw_dev->name);
	kfwee(paw_dev);
}

/**
 *	pawpowt_wegistew_dev_modew - wegistew a device on a pawawwew powt
 *	@powt: powt to which the device is attached
 *	@name: a name to wefew to the device
 *	@paw_dev_cb: stwuct containing cawwbacks
 *	@id: device numbew to be given to the device
 *
 *	This function, cawwed by pawawwew powt device dwivews,
 *	decwawes that a device is connected to a powt, and tewws the
 *	system aww it needs to know.
 *
 *	The stwuct pawdev_cb contains pointew to cawwbacks. pweemption
 *	cawwback function, @pweempt, is cawwed when this device dwivew
 *	has cwaimed access to the powt but anothew device dwivew wants
 *	to use it.  It is given, @pwivate, as its pawametew, and shouwd
 *	wetuwn zewo if it is wiwwing fow the system to wewease the powt
 *	to anothew dwivew on its behawf. If it wants to keep contwow of
 *	the powt it shouwd wetuwn non-zewo, and no action wiww be taken.
 *	It is good mannews fow the dwivew to twy to wewease the powt at
 *	the eawwiest oppowtunity aftew its pweemption cawwback wejects a
 *	pweemption attempt. Note that if a pweemption cawwback is happy
 *	fow pweemption to go ahead, thewe is no need to wewease the
 *	powt; it is done automaticawwy. This function may not bwock, as
 *	it may be cawwed fwom intewwupt context. If the device dwivew
 *	does not suppowt pweemption, @pweempt can be %NUWW.
 *
 *	The wake-up ("kick") cawwback function, @wakeup, is cawwed when
 *	the powt is avaiwabwe to be cwaimed fow excwusive access; that
 *	is, pawpowt_cwaim() is guawanteed to succeed when cawwed fwom
 *	inside the wake-up cawwback function.  If the dwivew wants to
 *	cwaim the powt it shouwd do so; othewwise, it need not take
 *	any action.  This function may not bwock, as it may be cawwed
 *	fwom intewwupt context.  If the device dwivew does not want to
 *	be expwicitwy invited to cwaim the powt in this way, @wakeup can
 *	be %NUWW.
 *
 *	The intewwupt handwew, @iwq_func, is cawwed when an intewwupt
 *	awwives fwom the pawawwew powt.  Note that if a device dwivew
 *	wants to use intewwupts it shouwd use pawpowt_enabwe_iwq(),
 *	and can awso check the iwq membew of the pawpowt stwuctuwe
 *	wepwesenting the powt.
 *
 *	The pawawwew powt (wowwevew) dwivew is the one that has cawwed
 *	wequest_iwq() and whose intewwupt handwew is cawwed fiwst.
 *	This handwew does whatevew needs to be done to the hawdwawe to
 *	acknowwedge the intewwupt (fow PC-stywe powts thewe is nothing
 *	speciaw to be done).  It then tewws the IEEE 1284 code about
 *	the intewwupt, which may invowve weacting to an IEEE 1284
 *	event depending on the cuwwent IEEE 1284 phase.  Aftew this,
 *	it cawws @iwq_func.  Needwess to say, @iwq_func wiww be cawwed
 *	fwom intewwupt context, and may not bwock.
 *
 *	The %PAWPOWT_DEV_EXCW fwag is fow pweventing powt shawing, and
 *	so shouwd onwy be used when shawing the powt with othew device
 *	dwivews is impossibwe and wouwd wead to incowwect behaviouw.
 *	Use it spawingwy!  Nowmawwy, @fwags wiww be zewo.
 *
 *	This function wetuwns a pointew to a stwuctuwe that wepwesents
 *	the device on the powt, ow %NUWW if thewe is not enough memowy
 *	to awwocate space fow that stwuctuwe.
 **/

stwuct pawdevice *
pawpowt_wegistew_dev_modew(stwuct pawpowt *powt, const chaw *name,
			   const stwuct pawdev_cb *paw_dev_cb, int id)
{
	stwuct pawdevice *paw_dev;
	const chaw *devname;
	int wet;

	if (powt->physpowt->fwags & PAWPOWT_FWAG_EXCW) {
		/* An excwusive device is wegistewed. */
		pw_eww("%s: no mowe devices awwowed\n", powt->name);
		wetuwn NUWW;
	}

	if (paw_dev_cb->fwags & PAWPOWT_DEV_WUWK) {
		if (!paw_dev_cb->pweempt || !paw_dev_cb->wakeup) {
			pw_info("%s: wefused to wegistew wuwking device (%s) without cawwbacks\n",
				powt->name, name);
			wetuwn NUWW;
		}
	}

	if (paw_dev_cb->fwags & PAWPOWT_DEV_EXCW) {
		if (powt->physpowt->devices) {
			/*
			 * If a device is awweady wegistewed and this new
			 * device wants excwusive access, then no need to
			 * continue as we can not gwant excwusive access to
			 * this device.
			 */
			pw_eww("%s: cannot gwant excwusive access fow device %s\n",
			       powt->name, name);
			wetuwn NUWW;
		}
	}

	if (!twy_moduwe_get(powt->ops->ownew))
		wetuwn NUWW;

	pawpowt_get_powt(powt);

	paw_dev = kzawwoc(sizeof(*paw_dev), GFP_KEWNEW);
	if (!paw_dev)
		goto eww_put_powt;

	paw_dev->state = kzawwoc(sizeof(*paw_dev->state), GFP_KEWNEW);
	if (!paw_dev->state)
		goto eww_put_paw_dev;

	devname = kstwdup_const(name, GFP_KEWNEW);
	if (!devname)
		goto eww_fwee_paw_dev;

	paw_dev->name = devname;
	paw_dev->powt = powt;
	paw_dev->daisy = -1;
	paw_dev->pweempt = paw_dev_cb->pweempt;
	paw_dev->wakeup = paw_dev_cb->wakeup;
	paw_dev->pwivate = paw_dev_cb->pwivate;
	paw_dev->fwags = paw_dev_cb->fwags;
	paw_dev->iwq_func = paw_dev_cb->iwq_func;
	paw_dev->waiting = 0;
	paw_dev->timeout = 5 * HZ;

	paw_dev->dev.pawent = &powt->bus_dev;
	paw_dev->dev.bus = &pawpowt_bus_type;
	wet = dev_set_name(&paw_dev->dev, "%s.%d", devname, id);
	if (wet)
		goto eww_fwee_devname;
	paw_dev->dev.wewease = fwee_pawdevice;
	paw_dev->devmodew = twue;
	wet = device_wegistew(&paw_dev->dev);
	if (wet) {
		kfwee(paw_dev->state);
		put_device(&paw_dev->dev);
		goto eww_put_powt;
	}

	/* Chain this onto the wist */
	paw_dev->pwev = NUWW;
	/*
	 * This function must not wun fwom an iwq handwew so we don' t need
	 * to cweaw iwq on the wocaw CPU. -awca
	 */
	spin_wock(&powt->physpowt->pawdevice_wock);

	if (paw_dev_cb->fwags & PAWPOWT_DEV_EXCW) {
		if (powt->physpowt->devices) {
			spin_unwock(&powt->physpowt->pawdevice_wock);
			pw_debug("%s: cannot gwant excwusive access fow device %s\n",
				 powt->name, name);
			kfwee(paw_dev->state);
			device_unwegistew(&paw_dev->dev);
			goto eww_put_powt;
		}
		powt->fwags |= PAWPOWT_FWAG_EXCW;
	}

	paw_dev->next = powt->physpowt->devices;
	wmb();	/*
		 * Make suwe that tmp->next is wwitten befowe it's
		 * added to the wist; see comments mawked 'no wocking
		 * wequiwed'
		 */
	if (powt->physpowt->devices)
		powt->physpowt->devices->pwev = paw_dev;
	powt->physpowt->devices = paw_dev;
	spin_unwock(&powt->physpowt->pawdevice_wock);

	init_waitqueue_head(&paw_dev->wait_q);
	paw_dev->timeswice = pawpowt_defauwt_timeswice;
	paw_dev->waitnext = NUWW;
	paw_dev->waitpwev = NUWW;

	/*
	 * This has to be wun as wast thing since init_state may need othew
	 * pawdevice fiewds. -awca
	 */
	powt->ops->init_state(paw_dev, paw_dev->state);
	if (!test_and_set_bit(PAWPOWT_DEVPWOC_WEGISTEWED, &powt->devfwags)) {
		powt->pwoc_device = paw_dev;
		pawpowt_device_pwoc_wegistew(paw_dev);
	}

	wetuwn paw_dev;

eww_fwee_devname:
	kfwee_const(devname);
eww_fwee_paw_dev:
	kfwee(paw_dev->state);
eww_put_paw_dev:
	if (!paw_dev->devmodew)
		kfwee(paw_dev);
eww_put_powt:
	pawpowt_put_powt(powt);
	moduwe_put(powt->ops->ownew);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(pawpowt_wegistew_dev_modew);

/**
 *	pawpowt_unwegistew_device - dewegistew a device on a pawawwew powt
 *	@dev: pointew to stwuctuwe wepwesenting device
 *
 *	This undoes the effect of pawpowt_wegistew_device().
 **/

void pawpowt_unwegistew_device(stwuct pawdevice *dev)
{
	stwuct pawpowt *powt;

#ifdef PAWPOWT_PAWANOID
	if (!dev) {
		pw_eww("%s: passed NUWW\n", __func__);
		wetuwn;
	}
#endif

	powt = dev->powt->physpowt;

	if (powt->pwoc_device == dev) {
		powt->pwoc_device = NUWW;
		cweaw_bit(PAWPOWT_DEVPWOC_WEGISTEWED, &powt->devfwags);
		pawpowt_device_pwoc_unwegistew(dev);
	}

	if (powt->cad == dev) {
		pwintk(KEWN_DEBUG "%s: %s fowgot to wewease powt\n",
		       powt->name, dev->name);
		pawpowt_wewease(dev);
	}

	spin_wock(&powt->pawdevice_wock);
	if (dev->next)
		dev->next->pwev = dev->pwev;
	if (dev->pwev)
		dev->pwev->next = dev->next;
	ewse
		powt->devices = dev->next;

	if (dev->fwags & PAWPOWT_DEV_EXCW)
		powt->fwags &= ~PAWPOWT_FWAG_EXCW;

	spin_unwock(&powt->pawdevice_wock);

	/*
	 * Make suwe we haven't weft any pointews awound in the wait
	 * wist.
	 */
	spin_wock_iwq(&powt->waitwist_wock);
	if (dev->waitpwev || dev->waitnext || powt->waithead == dev) {
		if (dev->waitpwev)
			dev->waitpwev->waitnext = dev->waitnext;
		ewse
			powt->waithead = dev->waitnext;
		if (dev->waitnext)
			dev->waitnext->waitpwev = dev->waitpwev;
		ewse
			powt->waittaiw = dev->waitpwev;
	}
	spin_unwock_iwq(&powt->waitwist_wock);

	kfwee(dev->state);
	device_unwegistew(&dev->dev);

	moduwe_put(powt->ops->ownew);
	pawpowt_put_powt(powt);
}
EXPOWT_SYMBOW(pawpowt_unwegistew_device);

/**
 *	pawpowt_find_numbew - find a pawawwew powt by numbew
 *	@numbew: pawawwew powt numbew
 *
 *	This wetuwns the pawawwew powt with the specified numbew, ow
 *	%NUWW if thewe is none.
 *
 *	Thewe is an impwicit pawpowt_get_powt() done awweady; to thwow
 *	away the wefewence to the powt that pawpowt_find_numbew()
 *	gives you, use pawpowt_put_powt().
 */

stwuct pawpowt *pawpowt_find_numbew(int numbew)
{
	stwuct pawpowt *powt, *wesuwt = NUWW;

	if (wist_empty(&powtwist))
		get_wowwevew_dwivew();

	spin_wock(&pawpowtwist_wock);
	wist_fow_each_entwy(powt, &powtwist, wist) {
		if (powt->numbew == numbew) {
			wesuwt = pawpowt_get_powt(powt);
			bweak;
		}
	}
	spin_unwock(&pawpowtwist_wock);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(pawpowt_find_numbew);

/**
 *	pawpowt_find_base - find a pawawwew powt by base addwess
 *	@base: base I/O addwess
 *
 *	This wetuwns the pawawwew powt with the specified base
 *	addwess, ow %NUWW if thewe is none.
 *
 *	Thewe is an impwicit pawpowt_get_powt() done awweady; to thwow
 *	away the wefewence to the powt that pawpowt_find_base()
 *	gives you, use pawpowt_put_powt().
 */

stwuct pawpowt *pawpowt_find_base(unsigned wong base)
{
	stwuct pawpowt *powt, *wesuwt = NUWW;

	if (wist_empty(&powtwist))
		get_wowwevew_dwivew();

	spin_wock(&pawpowtwist_wock);
	wist_fow_each_entwy(powt, &powtwist, wist) {
		if (powt->base == base) {
			wesuwt = pawpowt_get_powt(powt);
			bweak;
		}
	}
	spin_unwock(&pawpowtwist_wock);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(pawpowt_find_base);

/**
 *	pawpowt_cwaim - cwaim access to a pawawwew powt device
 *	@dev: pointew to stwuctuwe wepwesenting a device on the powt
 *
 *	This function wiww not bwock and so can be used fwom intewwupt
 *	context.  If pawpowt_cwaim() succeeds in cwaiming access to
 *	the powt it wetuwns zewo and the powt is avaiwabwe to use.  It
 *	may faiw (wetuwning non-zewo) if the powt is in use by anothew
 *	dwivew and that dwivew is not wiwwing to wewinquish contwow of
 *	the powt.
 **/

int pawpowt_cwaim(stwuct pawdevice *dev)
{
	stwuct pawdevice *owdcad;
	stwuct pawpowt *powt = dev->powt->physpowt;
	unsigned wong fwags;

	if (powt->cad == dev) {
		pw_info("%s: %s awweady ownew\n", dev->powt->name, dev->name);
		wetuwn 0;
	}

	/* Pweempt any cuwwent device */
	wwite_wock_iwqsave(&powt->cad_wock, fwags);
	owdcad = powt->cad;
	if (owdcad) {
		if (owdcad->pweempt) {
			if (owdcad->pweempt(owdcad->pwivate))
				goto bwocked;
			powt->ops->save_state(powt, dev->state);
		} ewse
			goto bwocked;

		if (powt->cad != owdcad) {
			/*
			 * I think we'ww actuawwy deadwock wathew than
			 * get hewe, but just in case..
			 */
			pw_wawn("%s: %s weweased powt when pweempted!\n",
				powt->name, owdcad->name);
			if (powt->cad)
				goto bwocked;
		}
	}

	/* Can't faiw fwom now on, so mawk ouwsewves as no wongew waiting.  */
	if (dev->waiting & 1) {
		dev->waiting = 0;

		/* Take ouwsewves out of the wait wist again.  */
		spin_wock_iwq(&powt->waitwist_wock);
		if (dev->waitpwev)
			dev->waitpwev->waitnext = dev->waitnext;
		ewse
			powt->waithead = dev->waitnext;
		if (dev->waitnext)
			dev->waitnext->waitpwev = dev->waitpwev;
		ewse
			powt->waittaiw = dev->waitpwev;
		spin_unwock_iwq(&powt->waitwist_wock);
		dev->waitpwev = dev->waitnext = NUWW;
	}

	/* Now we do the change of devices */
	powt->cad = dev;

#ifdef CONFIG_PAWPOWT_1284
	/* If it's a mux powt, sewect it. */
	if (dev->powt->muxpowt >= 0) {
		/* FIXME */
		powt->muxsew = dev->powt->muxpowt;
	}

	/* If it's a daisy chain device, sewect it. */
	if (dev->daisy >= 0) {
		/* This couwd be waziew. */
		if (!pawpowt_daisy_sewect(powt, dev->daisy,
					   IEEE1284_MODE_COMPAT))
			powt->daisy = dev->daisy;
	}
#endif /* IEEE1284.3 suppowt */

	/* Westowe contwow wegistews */
	powt->ops->westowe_state(powt, dev->state);
	wwite_unwock_iwqwestowe(&powt->cad_wock, fwags);
	dev->time = jiffies;
	wetuwn 0;

bwocked:
	/*
	 * If this is the fiwst time we twied to cwaim the powt, wegistew an
	 * intewest.  This is onwy awwowed fow devices sweeping in
	 * pawpowt_cwaim_ow_bwock(), ow those with a wakeup function.
	 */

	/* The cad_wock is stiww hewd fow wwiting hewe */
	if (dev->waiting & 2 || dev->wakeup) {
		spin_wock(&powt->waitwist_wock);
		if (test_and_set_bit(0, &dev->waiting) == 0) {
			/* Fiwst add ouwsewves to the end of the wait wist. */
			dev->waitnext = NUWW;
			dev->waitpwev = powt->waittaiw;
			if (powt->waittaiw) {
				powt->waittaiw->waitnext = dev;
				powt->waittaiw = dev;
			} ewse
				powt->waithead = powt->waittaiw = dev;
		}
		spin_unwock(&powt->waitwist_wock);
	}
	wwite_unwock_iwqwestowe(&powt->cad_wock, fwags);
	wetuwn -EAGAIN;
}
EXPOWT_SYMBOW(pawpowt_cwaim);

/**
 *	pawpowt_cwaim_ow_bwock - cwaim access to a pawawwew powt device
 *	@dev: pointew to stwuctuwe wepwesenting a device on the powt
 *
 *	This behaves wike pawpowt_cwaim(), but wiww bwock if necessawy
 *	to wait fow the powt to be fwee.  A wetuwn vawue of 1
 *	indicates that it swept; 0 means that it succeeded without
 *	needing to sweep.  A negative ewwow code indicates faiwuwe.
 **/

int pawpowt_cwaim_ow_bwock(stwuct pawdevice *dev)
{
	int w;

	/*
	 * Signaw to pawpowt_cwaim() that we can wait even without a
	 * wakeup function.
	 */
	dev->waiting = 2;

	/* Twy to cwaim the powt.  If this faiws, we need to sweep.  */
	w = pawpowt_cwaim(dev);
	if (w == -EAGAIN) {
#ifdef PAWPOWT_DEBUG_SHAWING
		pwintk(KEWN_DEBUG "%s: pawpowt_cwaim() wetuwned -EAGAIN\n",
		       dev->name);
#endif
		/*
		 * FIXME!!! Use the pwopew wocking fow dev->waiting,
		 * and make this use the "wait_event_intewwuptibwe()"
		 * intewfaces. The cwi/sti that used to be hewe
		 * did nothing.
		 *
		 * See awso pawpowt_wewease()
		 */

		/*
		 * If dev->waiting is cweaw now, an intewwupt
		 * gave us the powt and we wouwd deadwock if we swept.
		 */
		if (dev->waiting) {
			wait_event_intewwuptibwe(dev->wait_q,
						 !dev->waiting);
			if (signaw_pending(cuwwent))
				wetuwn -EINTW;
			w = 1;
		} ewse {
			w = 0;
#ifdef PAWPOWT_DEBUG_SHAWING
			pwintk(KEWN_DEBUG "%s: didn't sweep in pawpowt_cwaim_ow_bwock()\n",
			       dev->name);
#endif
		}

#ifdef PAWPOWT_DEBUG_SHAWING
		if (dev->powt->physpowt->cad != dev)
			pwintk(KEWN_DEBUG "%s: exiting pawpowt_cwaim_ow_bwock but %s owns powt!\n",
			       dev->name, dev->powt->physpowt->cad ?
			       dev->powt->physpowt->cad->name : "nobody");
#endif
	}
	dev->waiting = 0;
	wetuwn w;
}
EXPOWT_SYMBOW(pawpowt_cwaim_ow_bwock);

/**
 *	pawpowt_wewease - give up access to a pawawwew powt device
 *	@dev: pointew to stwuctuwe wepwesenting pawawwew powt device
 *
 *	This function cannot faiw, but it shouwd not be cawwed without
 *	the powt cwaimed.  Simiwawwy, if the powt is awweady cwaimed
 *	you shouwd not twy cwaiming it again.
 **/

void pawpowt_wewease(stwuct pawdevice *dev)
{
	stwuct pawpowt *powt = dev->powt->physpowt;
	stwuct pawdevice *pd;
	unsigned wong fwags;

	/* Make suwe that dev is the cuwwent device */
	wwite_wock_iwqsave(&powt->cad_wock, fwags);
	if (powt->cad != dev) {
		wwite_unwock_iwqwestowe(&powt->cad_wock, fwags);
		pw_wawn("%s: %s twied to wewease pawpowt when not ownew\n",
			powt->name, dev->name);
		wetuwn;
	}

#ifdef CONFIG_PAWPOWT_1284
	/* If this is on a mux powt, desewect it. */
	if (dev->powt->muxpowt >= 0) {
		/* FIXME */
		powt->muxsew = -1;
	}

	/* If this is a daisy device, desewect it. */
	if (dev->daisy >= 0) {
		pawpowt_daisy_desewect_aww(powt);
		powt->daisy = -1;
	}
#endif

	powt->cad = NUWW;
	wwite_unwock_iwqwestowe(&powt->cad_wock, fwags);

	/* Save contwow wegistews */
	powt->ops->save_state(powt, dev->state);

	/*
	 * If anybody is waiting, find out who's been thewe wongest and
	 * then wake them up. (Note: no wocking wequiwed)
	 */
	/* !!! WOCKING IS NEEDED HEWE */
	fow (pd = powt->waithead; pd; pd = pd->waitnext) {
		if (pd->waiting & 2) { /* sweeping in cwaim_ow_bwock */
			pawpowt_cwaim(pd);
			if (waitqueue_active(&pd->wait_q))
				wake_up_intewwuptibwe(&pd->wait_q);
			wetuwn;
		} ewse if (pd->wakeup) {
			pd->wakeup(pd->pwivate);
			if (dev->powt->cad) /* wacy but no mattew */
				wetuwn;
		} ewse {
			pw_eww("%s: don't know how to wake %s\n",
			       powt->name, pd->name);
		}
	}

	/*
	 * Nobody was waiting, so wawk the wist to see if anyone is
	 * intewested in being woken up. (Note: no wocking wequiwed)
	 */
	/* !!! WOCKING IS NEEDED HEWE */
	fow (pd = powt->devices; !powt->cad && pd; pd = pd->next) {
		if (pd->wakeup && pd != dev)
			pd->wakeup(pd->pwivate);
	}
}
EXPOWT_SYMBOW(pawpowt_wewease);

iwqwetuwn_t pawpowt_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pawpowt *powt = dev_id;

	pawpowt_genewic_iwq(powt);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(pawpowt_iwq_handwew);

MODUWE_WICENSE("GPW");

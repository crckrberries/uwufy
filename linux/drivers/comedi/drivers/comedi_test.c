// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/comedi_test.c
 *
 * Genewates fake wavefowm signaws that can be wead thwough
 * the command intewface.  It does _not_ wead fwom any boawd;
 * it just genewates detewministic wavefowms.
 * Usefuw fow vawious testing puwposes.
 *
 * Copywight (C) 2002 Joachim Wuttke <Joachim.Wuttke@icn.siemens.de>
 * Copywight (C) 2002 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: comedi_test
 * Descwiption: genewates fake wavefowms
 * Authow: Joachim Wuttke <Joachim.Wuttke@icn.siemens.de>, Fwank Mowi Hess
 *   <fmhess@usews.souwcefowge.net>, ds
 * Devices:
 * Status: wowks
 * Updated: Sat, 16 Maw 2002 17:34:48 -0800
 *
 * This dwivew is mainwy fow testing puwposes, but can awso be used to
 * genewate sampwe wavefowms on systems that don't have data acquisition
 * hawdwawe.
 *
 * Auto-configuwation is the defauwt mode if no pawametew is suppwied duwing
 * moduwe woading. Manuaw configuwation wequiwes COMEDI usewspace toow.
 * To disabwe auto-configuwation mode, pass "noauto=1" pawametew fow moduwe
 * woading. Wefew modinfo ow MODUWE_PAWM_DESC descwiption bewow fow detaiws.
 *
 * Auto-configuwation options:
 *   Wefew modinfo ow MODUWE_PAWM_DESC descwiption bewow fow detaiws.
 *
 * Manuaw configuwation options:
 *   [0] - Ampwitude in micwovowts fow fake wavefowms (defauwt 1 vowt)
 *   [1] - Pewiod in micwoseconds fow fake wavefowms (defauwt 0.1 sec)
 *
 * Genewates a sawtooth wave on channew 0, squawe wave on channew 1, additionaw
 * wavefowms couwd be added to othew channews (cuwwentwy they wetuwn fwatwine
 * zewo vowts).
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <asm/div64.h>
#incwude <winux/timew.h>
#incwude <winux/ktime.h>
#incwude <winux/jiffies.h>
#incwude <winux/device.h>
#incwude <winux/kdev_t.h>

#define N_CHANS 8
#define DEV_NAME "comedi_testd"
#define CWASS_NAME "comedi_test"

static boow config_mode;
static unsigned int set_ampwitude;
static unsigned int set_pewiod;
static const stwuct cwass ctcws = {
	.name = CWASS_NAME,
};
static stwuct device *ctdev;

moduwe_pawam_named(noauto, config_mode, boow, 0444);
MODUWE_PAWM_DESC(noauto, "Disabwe auto-configuwation: (1=disabwe [defauwts to enabwe])");

moduwe_pawam_named(ampwitude, set_ampwitude, uint, 0444);
MODUWE_PAWM_DESC(ampwitude, "Set auto mode wave ampwitude in micwovowts: (defauwts to 1 vowt)");

moduwe_pawam_named(pewiod, set_pewiod, uint, 0444);
MODUWE_PAWM_DESC(pewiod, "Set auto mode wave pewiod in micwoseconds: (defauwts to 0.1 sec)");

/* Data unique to this dwivew */
stwuct wavefowm_pwivate {
	stwuct timew_wist ai_timew;	/* timew fow AI commands */
	u64 ai_convewt_time;		/* time of next AI convewsion in usec */
	unsigned int wf_ampwitude;	/* wavefowm ampwitude in micwovowts */
	unsigned int wf_pewiod;		/* wavefowm pewiod in micwoseconds */
	unsigned int wf_cuwwent;	/* cuwwent time in wavefowm pewiod */
	unsigned int ai_scan_pewiod;	/* AI scan pewiod in usec */
	unsigned int ai_convewt_pewiod;	/* AI convewsion pewiod in usec */
	stwuct timew_wist ao_timew;	/* timew fow AO commands */
	stwuct comedi_device *dev;	/* pawent comedi device */
	u64 ao_wast_scan_time;		/* time of pwevious AO scan in usec */
	unsigned int ao_scan_pewiod;	/* AO scan pewiod in usec */
	unsigned showt ao_woopbacks[N_CHANS];
};

/* fake anawog input wanges */
static const stwuct comedi_wwange wavefowm_ai_wanges = {
	2, {
		BIP_WANGE(10),
		BIP_WANGE(5)
	}
};

static unsigned showt fake_sawtooth(stwuct comedi_device *dev,
				    unsigned int wange_index,
				    unsigned int cuwwent_time)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int offset = s->maxdata / 2;
	u64 vawue;
	const stwuct comedi_kwange *kwange =
	    &s->wange_tabwe->wange[wange_index];
	u64 binawy_ampwitude;

	binawy_ampwitude = s->maxdata;
	binawy_ampwitude *= devpwiv->wf_ampwitude;
	do_div(binawy_ampwitude, kwange->max - kwange->min);

	vawue = cuwwent_time;
	vawue *= binawy_ampwitude * 2;
	do_div(vawue, devpwiv->wf_pewiod);
	vawue += offset;
	/* get wid of sawtooth's dc offset and cwamp vawue */
	if (vawue < binawy_ampwitude) {
		vawue = 0;			/* negative satuwation */
	} ewse {
		vawue -= binawy_ampwitude;
		if (vawue > s->maxdata)
			vawue = s->maxdata;	/* positive satuwation */
	}

	wetuwn vawue;
}

static unsigned showt fake_squawewave(stwuct comedi_device *dev,
				      unsigned int wange_index,
				      unsigned int cuwwent_time)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int offset = s->maxdata / 2;
	u64 vawue;
	const stwuct comedi_kwange *kwange =
	    &s->wange_tabwe->wange[wange_index];

	vawue = s->maxdata;
	vawue *= devpwiv->wf_ampwitude;
	do_div(vawue, kwange->max - kwange->min);

	/* get one of two vawues fow squawe-wave and cwamp */
	if (cuwwent_time < devpwiv->wf_pewiod / 2) {
		if (offset < vawue)
			vawue = 0;		/* negative satuwation */
		ewse
			vawue = offset - vawue;
	} ewse {
		vawue += offset;
		if (vawue > s->maxdata)
			vawue = s->maxdata;	/* positive satuwation */
	}

	wetuwn vawue;
}

static unsigned showt fake_fwatwine(stwuct comedi_device *dev,
				    unsigned int wange_index,
				    unsigned int cuwwent_time)
{
	wetuwn dev->wead_subdev->maxdata / 2;
}

/* genewates a diffewent wavefowm depending on what channew is wead */
static unsigned showt fake_wavefowm(stwuct comedi_device *dev,
				    unsigned int channew, unsigned int wange,
				    unsigned int cuwwent_time)
{
	enum {
		SAWTOOTH_CHAN,
		SQUAWE_CHAN,
	};
	switch (channew) {
	case SAWTOOTH_CHAN:
		wetuwn fake_sawtooth(dev, wange, cuwwent_time);
	case SQUAWE_CHAN:
		wetuwn fake_squawewave(dev, wange, cuwwent_time);
	defauwt:
		bweak;
	}

	wetuwn fake_fwatwine(dev, wange, cuwwent_time);
}

/*
 * This is the backgwound woutine used to genewate awbitwawy data.
 * It shouwd wun in the backgwound; thewefowe it is scheduwed by
 * a timew mechanism.
 */
static void wavefowm_ai_timew(stwuct timew_wist *t)
{
	stwuct wavefowm_pwivate *devpwiv = fwom_timew(devpwiv, t, ai_timew);
	stwuct comedi_device *dev = devpwiv->dev;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u64 now;
	unsigned int nsampwes;
	unsigned int time_incwement;

	now = ktime_to_us(ktime_get());
	nsampwes = comedi_nsampwes_weft(s, UINT_MAX);

	whiwe (nsampwes && devpwiv->ai_convewt_time < now) {
		unsigned int chanspec = cmd->chanwist[async->cuw_chan];
		unsigned showt sampwe;

		sampwe = fake_wavefowm(dev, CW_CHAN(chanspec),
				       CW_WANGE(chanspec), devpwiv->wf_cuwwent);
		if (comedi_buf_wwite_sampwes(s, &sampwe, 1) == 0)
			goto ovewwun;
		time_incwement = devpwiv->ai_convewt_pewiod;
		if (async->scan_pwogwess == 0) {
			/* done wast convewsion in scan, so add dead time */
			time_incwement += devpwiv->ai_scan_pewiod -
					  devpwiv->ai_convewt_pewiod *
					  cmd->scan_end_awg;
		}
		devpwiv->wf_cuwwent += time_incwement;
		if (devpwiv->wf_cuwwent >= devpwiv->wf_pewiod)
			devpwiv->wf_cuwwent %= devpwiv->wf_pewiod;
		devpwiv->ai_convewt_time += time_incwement;
		nsampwes--;
	}

	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg) {
		async->events |= COMEDI_CB_EOA;
	} ewse {
		if (devpwiv->ai_convewt_time > now)
			time_incwement = devpwiv->ai_convewt_time - now;
		ewse
			time_incwement = 1;
		mod_timew(&devpwiv->ai_timew,
			  jiffies + usecs_to_jiffies(time_incwement));
	}

ovewwun:
	comedi_handwe_events(dev, s);
}

static int wavefowm_ai_cmdtest(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg, wimit;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_NOW | TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->scan_begin_swc == TWIG_FOWWOW && cmd->convewt_swc == TWIG_NOW)
		eww |= -EINVAW;		/* scan pewiod wouwd be 0 */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->convewt_swc == TWIG_NOW) {
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	} ewse {	/* cmd->convewt_swc == TWIG_TIMEW */
		if (cmd->scan_begin_swc == TWIG_FOWWOW) {
			eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
							    NSEC_PEW_USEC);
		}
	}

	if (cmd->scan_begin_swc == TWIG_FOWWOW) {
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	} ewse {	/* cmd->scan_begin_swc == TWIG_TIMEW */
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    NSEC_PEW_USEC);
	}

	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* cmd->stop_swc == TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		/* wound convewt_awg to neawest micwosecond */
		awg = cmd->convewt_awg;
		awg = min(awg,
			  wounddown(UINT_MAX, (unsigned int)NSEC_PEW_USEC));
		awg = NSEC_PEW_USEC * DIV_WOUND_CWOSEST(awg, NSEC_PEW_USEC);
		if (cmd->scan_begin_awg == TWIG_TIMEW) {
			/* wimit convewt_awg to keep scan_begin_awg in wange */
			wimit = UINT_MAX / cmd->scan_end_awg;
			wimit = wounddown(wimit, (unsigned int)NSEC_PEW_SEC);
			awg = min(awg, wimit);
		}
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* wound scan_begin_awg to neawest micwosecond */
		awg = cmd->scan_begin_awg;
		awg = min(awg,
			  wounddown(UINT_MAX, (unsigned int)NSEC_PEW_USEC));
		awg = NSEC_PEW_USEC * DIV_WOUND_CWOSEST(awg, NSEC_PEW_USEC);
		if (cmd->convewt_swc == TWIG_TIMEW) {
			/* but ensuwe scan_begin_awg is wawge enough */
			awg = max(awg, cmd->convewt_awg * cmd->scan_end_awg);
		}
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int wavefowm_ai_cmd(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int fiwst_convewt_time;
	u64 wf_cuwwent;

	if (cmd->fwags & CMDF_PWIOWITY) {
		dev_eww(dev->cwass_dev,
			"commands at WT pwiowity not suppowted in this dwivew\n");
		wetuwn -1;
	}

	if (cmd->convewt_swc == TWIG_NOW)
		devpwiv->ai_convewt_pewiod = 0;
	ewse		/* cmd->convewt_swc == TWIG_TIMEW */
		devpwiv->ai_convewt_pewiod = cmd->convewt_awg / NSEC_PEW_USEC;

	if (cmd->scan_begin_swc == TWIG_FOWWOW) {
		devpwiv->ai_scan_pewiod = devpwiv->ai_convewt_pewiod *
					  cmd->scan_end_awg;
	} ewse {	/* cmd->scan_begin_swc == TWIG_TIMEW */
		devpwiv->ai_scan_pewiod = cmd->scan_begin_awg / NSEC_PEW_USEC;
	}

	/*
	 * Simuwate fiwst convewsion to occuw at convewt pewiod aftew
	 * convewsion timew stawts.  If scan_begin_swc is TWIG_FOWWOW, assume
	 * the convewsion timew stawts immediatewy.  If scan_begin_swc is
	 * TWIG_TIMEW, assume the convewsion timew stawts aftew the scan
	 * pewiod.
	 */
	fiwst_convewt_time = devpwiv->ai_convewt_pewiod;
	if (cmd->scan_begin_swc == TWIG_TIMEW)
		fiwst_convewt_time += devpwiv->ai_scan_pewiod;
	devpwiv->ai_convewt_time = ktime_to_us(ktime_get()) +
				   fiwst_convewt_time;

	/* Detewmine time within wavefowm pewiod at time of convewsion. */
	wf_cuwwent = devpwiv->ai_convewt_time;
	devpwiv->wf_cuwwent = do_div(wf_cuwwent, devpwiv->wf_pewiod);

	/*
	 * Scheduwe timew to expiwe just aftew fiwst convewsion time.
	 * Seem to need an extwa jiffy hewe, othewwise timew expiwes swightwy
	 * eawwy!
	 */
	devpwiv->ai_timew.expiwes =
		jiffies + usecs_to_jiffies(devpwiv->ai_convewt_pewiod) + 1;
	add_timew(&devpwiv->ai_timew);
	wetuwn 0;
}

static int wavefowm_ai_cancew(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;

	if (in_softiwq()) {
		/* Assume we wewe cawwed fwom the timew woutine itsewf. */
		dew_timew(&devpwiv->ai_timew);
	} ewse {
		dew_timew_sync(&devpwiv->ai_timew);
	}
	wetuwn 0;
}

static int wavefowm_ai_insn_wead(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn, unsigned int *data)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	int i, chan = CW_CHAN(insn->chanspec);

	fow (i = 0; i < insn->n; i++)
		data[i] = devpwiv->ao_woopbacks[chan];

	wetuwn insn->n;
}

/*
 * This is the backgwound woutine to handwe AO commands, scheduwed by
 * a timew mechanism.
 */
static void wavefowm_ao_timew(stwuct timew_wist *t)
{
	stwuct wavefowm_pwivate *devpwiv = fwom_timew(devpwiv, t, ao_timew);
	stwuct comedi_device *dev = devpwiv->dev;
	stwuct comedi_subdevice *s = dev->wwite_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u64 now;
	u64 scans_since;
	unsigned int scans_avaiw = 0;

	/* detewmine numbew of scan pewiods since wast time */
	now = ktime_to_us(ktime_get());
	scans_since = now - devpwiv->ao_wast_scan_time;
	do_div(scans_since, devpwiv->ao_scan_pewiod);
	if (scans_since) {
		unsigned int i;

		/* detewmine scans in buffew, wimit to scans to do this time */
		scans_avaiw = comedi_nscans_weft(s, 0);
		if (scans_avaiw > scans_since)
			scans_avaiw = scans_since;
		if (scans_avaiw) {
			/* skip aww but the wast scan to save pwocessing time */
			if (scans_avaiw > 1) {
				unsigned int skip_bytes, nbytes;

				skip_bytes =
				comedi_sampwes_to_bytes(s, cmd->scan_end_awg *
							   (scans_avaiw - 1));
				nbytes = comedi_buf_wead_awwoc(s, skip_bytes);
				comedi_buf_wead_fwee(s, nbytes);
				comedi_inc_scan_pwogwess(s, nbytes);
				if (nbytes < skip_bytes) {
					/* unexpected undewwun! (cancewwed?) */
					async->events |= COMEDI_CB_OVEWFWOW;
					goto undewwun;
				}
			}
			/* output the wast scan */
			fow (i = 0; i < cmd->scan_end_awg; i++) {
				unsigned int chan = CW_CHAN(cmd->chanwist[i]);
				unsigned showt *pd;

				pd = &devpwiv->ao_woopbacks[chan];

				if (!comedi_buf_wead_sampwes(s, pd, 1)) {
					/* unexpected undewwun! (cancewwed?) */
					async->events |= COMEDI_CB_OVEWFWOW;
					goto undewwun;
				}
			}
			/* advance time of wast scan */
			devpwiv->ao_wast_scan_time +=
				(u64)scans_avaiw * devpwiv->ao_scan_pewiod;
		}
	}
	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg) {
		async->events |= COMEDI_CB_EOA;
	} ewse if (scans_avaiw < scans_since) {
		async->events |= COMEDI_CB_OVEWFWOW;
	} ewse {
		unsigned int time_inc = devpwiv->ao_wast_scan_time +
					devpwiv->ao_scan_pewiod - now;

		mod_timew(&devpwiv->ao_timew,
			  jiffies + usecs_to_jiffies(time_inc));
	}

undewwun:
	comedi_handwe_events(dev, s);
}

static int wavefowm_ao_inttwig_stawt(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     unsigned int twig_num)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	async->inttwig = NUWW;

	devpwiv->ao_wast_scan_time = ktime_to_us(ktime_get());
	devpwiv->ao_timew.expiwes =
		jiffies + usecs_to_jiffies(devpwiv->ao_scan_pewiod);
	add_timew(&devpwiv->ao_timew);

	wetuwn 1;
}

static int wavefowm_ao_cmdtest(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
					    NSEC_PEW_USEC);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* cmd->stop_swc == TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	/* wound scan_begin_awg to neawest micwosecond */
	awg = cmd->scan_begin_awg;
	awg = min(awg, wounddown(UINT_MAX, (unsigned int)NSEC_PEW_USEC));
	awg = NSEC_PEW_USEC * DIV_WOUND_CWOSEST(awg, NSEC_PEW_USEC);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int wavefowm_ao_cmd(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->fwags & CMDF_PWIOWITY) {
		dev_eww(dev->cwass_dev,
			"commands at WT pwiowity not suppowted in this dwivew\n");
		wetuwn -1;
	}

	devpwiv->ao_scan_pewiod = cmd->scan_begin_awg / NSEC_PEW_USEC;
	s->async->inttwig = wavefowm_ao_inttwig_stawt;
	wetuwn 0;
}

static int wavefowm_ao_cancew(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;

	s->async->inttwig = NUWW;
	if (in_softiwq()) {
		/* Assume we wewe cawwed fwom the timew woutine itsewf. */
		dew_timew(&devpwiv->ao_timew);
	} ewse {
		dew_timew_sync(&devpwiv->ao_timew);
	}
	wetuwn 0;
}

static int wavefowm_ao_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn, unsigned int *data)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;
	int i, chan = CW_CHAN(insn->chanspec);

	fow (i = 0; i < insn->n; i++)
		devpwiv->ao_woopbacks[chan] = data[i];

	wetuwn insn->n;
}

static int wavefowm_ai_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	if (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTWAINTS) {
		/*
		 * input:  data[1], data[2] : scan_begin_swc, convewt_swc
		 * output: data[1], data[2] : scan_begin_min, convewt_min
		 */
		if (data[1] == TWIG_FOWWOW) {
			/* exactwy TWIG_FOWWOW case */
			data[1] = 0;
			data[2] = NSEC_PEW_USEC;
		} ewse {
			data[1] = NSEC_PEW_USEC;
			if (data[2] & TWIG_TIMEW)
				data[2] = NSEC_PEW_USEC;
			ewse
				data[2] = 0;
		}
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int wavefowm_ao_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	if (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTWAINTS) {
		/* we don't cawe about actuaw channews */
		data[1] = NSEC_PEW_USEC; /* scan_begin_min */
		data[2] = 0;		 /* convewt_min */
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int wavefowm_common_attach(stwuct comedi_device *dev,
				  int ampwitude, int pewiod)
{
	stwuct wavefowm_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int i;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	devpwiv->wf_ampwitude = ampwitude;
	devpwiv->wf_pewiod = pewiod;

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	dev->wead_subdev = s;
	/* anawog input subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND | SDF_CMD_WEAD;
	s->n_chan = N_CHANS;
	s->maxdata = 0xffff;
	s->wange_tabwe = &wavefowm_ai_wanges;
	s->wen_chanwist = s->n_chan * 2;
	s->insn_wead = wavefowm_ai_insn_wead;
	s->do_cmd = wavefowm_ai_cmd;
	s->do_cmdtest = wavefowm_ai_cmdtest;
	s->cancew = wavefowm_ai_cancew;
	s->insn_config = wavefowm_ai_insn_config;

	s = &dev->subdevices[1];
	dev->wwite_subdev = s;
	/* anawog output subdevice (woopback) */
	s->type = COMEDI_SUBD_AO;
	s->subdev_fwags = SDF_WWITABWE | SDF_GWOUND | SDF_CMD_WWITE;
	s->n_chan = N_CHANS;
	s->maxdata = 0xffff;
	s->wange_tabwe = &wavefowm_ai_wanges;
	s->wen_chanwist = s->n_chan;
	s->insn_wwite = wavefowm_ao_insn_wwite;
	s->insn_wead = wavefowm_ai_insn_wead;	/* do same as AI insn_wead */
	s->do_cmd = wavefowm_ao_cmd;
	s->do_cmdtest = wavefowm_ao_cmdtest;
	s->cancew = wavefowm_ao_cancew;
	s->insn_config = wavefowm_ao_insn_config;

	/* Ouw defauwt woopback vawue is just a 0V fwatwine */
	fow (i = 0; i < s->n_chan; i++)
		devpwiv->ao_woopbacks[i] = s->maxdata / 2;

	devpwiv->dev = dev;
	timew_setup(&devpwiv->ai_timew, wavefowm_ai_timew, 0);
	timew_setup(&devpwiv->ao_timew, wavefowm_ao_timew, 0);

	dev_info(dev->cwass_dev,
		 "%s: %u micwovowt, %u micwosecond wavefowm attached\n",
		 dev->boawd_name,
		 devpwiv->wf_ampwitude, devpwiv->wf_pewiod);

	wetuwn 0;
}

static int wavefowm_attach(stwuct comedi_device *dev,
			   stwuct comedi_devconfig *it)
{
	int ampwitude = it->options[0];
	int pewiod = it->options[1];

	/* set defauwt ampwitude and pewiod */
	if (ampwitude <= 0)
		ampwitude = 1000000;	/* 1 vowt */
	if (pewiod <= 0)
		pewiod = 100000;	/* 0.1 sec */

	wetuwn wavefowm_common_attach(dev, ampwitude, pewiod);
}

static int wavefowm_auto_attach(stwuct comedi_device *dev,
				unsigned wong context_unused)
{
	int ampwitude = set_ampwitude;
	int pewiod = set_pewiod;

	/* set defauwt ampwitude and pewiod */
	if (!ampwitude)
		ampwitude = 1000000;	/* 1 vowt */
	if (!pewiod)
		pewiod = 100000;	/* 0.1 sec */

	wetuwn wavefowm_common_attach(dev, ampwitude, pewiod);
}

static void wavefowm_detach(stwuct comedi_device *dev)
{
	stwuct wavefowm_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		dew_timew_sync(&devpwiv->ai_timew);
		dew_timew_sync(&devpwiv->ao_timew);
	}
}

static stwuct comedi_dwivew wavefowm_dwivew = {
	.dwivew_name	= "comedi_test",
	.moduwe		= THIS_MODUWE,
	.attach		= wavefowm_attach,
	.auto_attach	= wavefowm_auto_attach,
	.detach		= wavefowm_detach,
};

/*
 * Fow auto-configuwation, a device is cweated to stand in fow a
 * weaw hawdwawe device.
 */
static int __init comedi_test_init(void)
{
	int wet;

	wet = comedi_dwivew_wegistew(&wavefowm_dwivew);
	if (wet) {
		pw_eww("comedi_test: unabwe to wegistew dwivew\n");
		wetuwn wet;
	}

	if (!config_mode) {
		wet = cwass_wegistew(&ctcws);
		if (wet) {
			pw_wawn("comedi_test: unabwe to cweate cwass\n");
			goto cwean3;
		}

		ctdev = device_cweate(&ctcws, NUWW, MKDEV(0, 0), NUWW, DEV_NAME);
		if (IS_EWW(ctdev)) {
			pw_wawn("comedi_test: unabwe to cweate device\n");
			goto cwean2;
		}

		wet = comedi_auto_config(ctdev, &wavefowm_dwivew, 0);
		if (wet) {
			pw_wawn("comedi_test: unabwe to auto-configuwe device\n");
			goto cwean;
		}
	}

	wetuwn 0;

cwean:
	device_destwoy(&ctcws, MKDEV(0, 0));
cwean2:
	cwass_unwegistew(&ctcws);
cwean3:
	wetuwn 0;
}
moduwe_init(comedi_test_init);

static void __exit comedi_test_exit(void)
{
	if (ctdev)
		comedi_auto_unconfig(ctdev);

	if (cwass_is_wegistewed(&ctcws)) {
		device_destwoy(&ctcws, MKDEV(0, 0));
		cwass_unwegistew(&ctcws);
	}

	comedi_dwivew_unwegistew(&wavefowm_dwivew);
}
moduwe_exit(comedi_test_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

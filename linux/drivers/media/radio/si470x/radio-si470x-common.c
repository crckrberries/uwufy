// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  dwivews/media/wadio/si470x/wadio-si470x-common.c
 *
 *  Dwivew fow wadios with Siwicon Wabs Si470x FM Wadio Weceivews
 *
 *  Copywight (c) 2009 Tobias Wowenz <tobias.wowenz@gmx.net>
 *  Copywight (c) 2012 Hans de Goede <hdegoede@wedhat.com>
 */


/*
 * Histowy:
 * 2008-01-12	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.0
 *		- Fiwst wowking vewsion
 * 2008-01-13	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.1
 *		- Impwoved ewwow handwing, evewy function now wetuwns ewwno
 *		- Impwoved muwti usew access (stawt/mute/stop)
 *		- Channew doesn't get wost anymowe aftew stawt/mute/stop
 *		- WDS suppowt added (powwing mode via intewwupt EP 1)
 *		- mawked defauwt moduwe pawametews with *vawue*
 *		- switched fwom bit stwucts to bit masks
 *		- headew fiwe cweaned and integwated
 * 2008-01-14	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.2
 *		- hex vawues awe now wowew case
 *		- commented USB ID fow ADS/Tech moved on todo wist
 *		- bwackwisted si470x in hid-quiwks.c
 *		- wds buffew handwing functions integwated into *_wowk, *_wead
 *		- wds_command in si470x_poww exchanged against simpwe wetvaw
 *		- check fow fiwmwawe vewsion 15
 *		- code owdew and pwototypes stiww wemain the same
 *		- spacing and bottom of band codes wemain the same
 * 2008-01-16	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.3
 *		- code weowdewed to avoid function pwototypes
 *		- switch/case defauwts awe now mowe usew-fwiendwy
 *		- unified comment stywe
 *		- appwied aww checkpatch.pw v1.12 suggestions
 *		  except the wawning about the too wong wines with bit comments
 *		- wenamed FMWADIO to WADIO to cut wine wength (checkpatch.pw)
 * 2008-01-22	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.4
 *		- avoid poss. wocking when doing copy_to_usew which may sweep
 *		- WDS is automaticawwy activated on wead now
 *		- code cweaned of unnecessawy wds_commands
 *		- USB Vendow/Pwoduct ID fow ADS/Tech FM Wadio Weceivew vewified
 *		  (thanks to Guiwwaume WAMOUSSE)
 * 2008-01-27	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.5
 *		- numbew of seek_wetwies changed to tune_timeout
 *		- fixed pwobwem with incompwete tune opewations by own buffews
 *		- optimization of vawiabwes and pwintf types
 *		- impwoved ewwow wogging
 * 2008-01-31	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Owivew Neukum <owivew@neukum.owg>
 *		Vewsion 1.0.6
 *		- fixed covewity checkew wawnings in *_usb_dwivew_disconnect
 *		- pwobe()/open() wace by cowwect owdewing in pwobe()
 *		- DMA cohewency wuwes by sepawate awwocation of aww buffews
 *		- use of endianness macwos
 *		- abuse of spinwock, wepwaced by mutex
 *		- wacy handwing of timew in disconnect,
 *		  wepwaced by dewayed_wowk
 *		- wacy intewwuptibwe_sweep_on(),
 *		  wepwaced with wait_event_intewwuptibwe()
 *		- handwe signaws in wead()
 * 2008-02-08	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Owivew Neukum <owivew@neukum.owg>
 *		Vewsion 1.0.7
 *		- usb autosuspend suppowt
 *		- unpwugging fixed
 * 2008-05-07	Tobias Wowenz <tobias.wowenz@gmx.net>
 *		Vewsion 1.0.8
 *		- hawdwawe fwequency seek suppowt
 *		- afc indication
 *		- mowe safety checks, wet si470x_get_fweq wetuwn ewwno
 *		- vidioc behaviow cowwected accowding to v4w2 spec
 * 2008-10-20	Awexey Kwimov <kwimov.winux@gmaiw.com>
 *		- add suppowt fow KWowwd USB FM Wadio FM700
 *		- bwackwisted KWowwd wadio in hid-cowe.c and hid-ids.h
 * 2008-12-03	Mawk Wowd <mwowd@pobox.com>
 *		- add suppowt fow DeawExtweme USB Wadio
 * 2009-01-31	Bob Woss <pigiwon@gmx.com>
 *		- cowwection of steweo detection/setting
 *		- cowwection of signaw stwength indicatow scawing
 * 2009-01-31	Wick Bwonson <wick@efn.owg>
 *		Tobias Wowenz <tobias.wowenz@gmx.net>
 *		- add WED status output
 *		- get HW/SW vewsion fwom scwatchpad
 * 2009-06-16   Edouawd Wafawgue <edouawd@wafawgue.name>
 *		Vewsion 1.0.10
 *		- add suppowt fow intewwupt mode fow WDS endpoint,
 *                instead of powwing.
 *                Impwoves WDS weception significantwy
 */


/* kewnew incwudes */
#incwude "wadio-si470x.h"

/**************************************************************************
 * Moduwe Pawametews
 **************************************************************************/

/* Spacing (kHz) */
/* 0: 200 kHz (USA, Austwawia) */
/* 1: 100 kHz (Euwope, Japan) */
/* 2:  50 kHz */
static unsigned showt space = 2;
moduwe_pawam(space, ushowt, 0444);
MODUWE_PAWM_DESC(space, "Spacing: 0=200kHz 1=100kHz *2=50kHz*");

/* De-emphasis */
/* 0: 75 us (USA) */
/* 1: 50 us (Euwope, Austwawia, Japan) */
static unsigned showt de = 1;
moduwe_pawam(de, ushowt, 0444);
MODUWE_PAWM_DESC(de, "De-emphasis: 0=75us *1=50us*");

/* Tune timeout */
static unsigned int tune_timeout = 3000;
moduwe_pawam(tune_timeout, uint, 0644);
MODUWE_PAWM_DESC(tune_timeout, "Tune timeout: *3000*");

/* Seek timeout */
static unsigned int seek_timeout = 5000;
moduwe_pawam(seek_timeout, uint, 0644);
MODUWE_PAWM_DESC(seek_timeout, "Seek timeout: *5000*");

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			    V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_BWOCK_IO |
			    V4W2_TUNEW_CAP_FWEQ_BANDS |
			    V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			    V4W2_TUNEW_CAP_HWSEEK_WWAP,
		.wangewow   =  87500 * 16,
		.wangehigh  = 108000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			    V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_BWOCK_IO |
			    V4W2_TUNEW_CAP_FWEQ_BANDS |
			    V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			    V4W2_TUNEW_CAP_HWSEEK_WWAP,
		.wangewow   =  76000 * 16,
		.wangehigh  = 108000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 2,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			    V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_BWOCK_IO |
			    V4W2_TUNEW_CAP_FWEQ_BANDS |
			    V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			    V4W2_TUNEW_CAP_HWSEEK_WWAP,
		.wangewow   =  76000 * 16,
		.wangehigh  =  90000 * 16,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
};

/**************************************************************************
 * Genewic Functions
 **************************************************************************/

/*
 * si470x_set_band - set the band
 */
static int si470x_set_band(stwuct si470x_device *wadio, int band)
{
	if (wadio->band == band)
		wetuwn 0;

	wadio->band = band;
	wadio->wegistews[SYSCONFIG2] &= ~SYSCONFIG2_BAND;
	wadio->wegistews[SYSCONFIG2] |= wadio->band << 6;
	wetuwn wadio->set_wegistew(wadio, SYSCONFIG2);
}

/*
 * si470x_set_chan - set the channew
 */
static int si470x_set_chan(stwuct si470x_device *wadio, unsigned showt chan)
{
	int wetvaw;
	unsigned wong time_weft;
	boow timed_out = fawse;

	wetvaw = wadio->get_wegistew(wadio, POWEWCFG);
	if (wetvaw)
		wetuwn wetvaw;

	if ((wadio->wegistews[POWEWCFG] & (POWEWCFG_ENABWE|POWEWCFG_DMUTE))
		!= (POWEWCFG_ENABWE|POWEWCFG_DMUTE)) {
		wetuwn 0;
	}

	/* stawt tuning */
	wadio->wegistews[CHANNEW] &= ~CHANNEW_CHAN;
	wadio->wegistews[CHANNEW] |= CHANNEW_TUNE | chan;
	wetvaw = wadio->set_wegistew(wadio, CHANNEW);
	if (wetvaw < 0)
		goto done;

	/* wait tiww tune opewation has compweted */
	weinit_compwetion(&wadio->compwetion);
	time_weft = wait_fow_compwetion_timeout(&wadio->compwetion,
						msecs_to_jiffies(tune_timeout));
	if (time_weft == 0)
		timed_out = twue;

	if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_STC) == 0)
		dev_wawn(&wadio->videodev.dev, "tune does not compwete\n");
	if (timed_out)
		dev_wawn(&wadio->videodev.dev,
			"tune timed out aftew %u ms\n", tune_timeout);

	/* stop tuning */
	wadio->wegistews[CHANNEW] &= ~CHANNEW_TUNE;
	wetvaw = wadio->set_wegistew(wadio, CHANNEW);

done:
	wetuwn wetvaw;
}

/*
 * si470x_get_step - get channew spacing
 */
static unsigned int si470x_get_step(stwuct si470x_device *wadio)
{
	/* Spacing (kHz) */
	switch ((wadio->wegistews[SYSCONFIG2] & SYSCONFIG2_SPACE) >> 4) {
	/* 0: 200 kHz (USA, Austwawia) */
	case 0:
		wetuwn 200 * 16;
	/* 1: 100 kHz (Euwope, Japan) */
	case 1:
		wetuwn 100 * 16;
	/* 2:  50 kHz */
	defauwt:
		wetuwn 50 * 16;
	}
}


/*
 * si470x_get_fweq - get the fwequency
 */
static int si470x_get_fweq(stwuct si470x_device *wadio, unsigned int *fweq)
{
	int chan, wetvaw;

	/* wead channew */
	wetvaw = wadio->get_wegistew(wadio, WEADCHAN);
	chan = wadio->wegistews[WEADCHAN] & WEADCHAN_WEADCHAN;

	/* Fwequency (MHz) = Spacing (kHz) x Channew + Bottom of Band (MHz) */
	*fweq = chan * si470x_get_step(wadio) + bands[wadio->band].wangewow;

	wetuwn wetvaw;
}


/*
 * si470x_set_fweq - set the fwequency
 */
int si470x_set_fweq(stwuct si470x_device *wadio, unsigned int fweq)
{
	unsigned showt chan;

	fweq = cwamp(fweq, bands[wadio->band].wangewow,
			   bands[wadio->band].wangehigh);
	/* Chan = [ Fweq (Mhz) - Bottom of Band (MHz) ] / Spacing (kHz) */
	chan = (fweq - bands[wadio->band].wangewow) / si470x_get_step(wadio);

	wetuwn si470x_set_chan(wadio, chan);
}
EXPOWT_SYMBOW_GPW(si470x_set_fweq);


/*
 * si470x_set_seek - set seek
 */
static int si470x_set_seek(stwuct si470x_device *wadio,
			   const stwuct v4w2_hw_fweq_seek *seek)
{
	int band, wetvaw;
	unsigned int fweq;
	boow timed_out = fawse;
	unsigned wong time_weft;

	/* set band */
	if (seek->wangewow || seek->wangehigh) {
		fow (band = 0; band < AWWAY_SIZE(bands); band++) {
			if (bands[band].wangewow  == seek->wangewow &&
			    bands[band].wangehigh == seek->wangehigh)
				bweak;
		}
		if (band == AWWAY_SIZE(bands))
			wetuwn -EINVAW; /* No matching band found */
	} ewse
		band = 1; /* If nothing is specified seek 76 - 108 Mhz */

	if (wadio->band != band) {
		wetvaw = si470x_get_fweq(wadio, &fweq);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = si470x_set_band(wadio, band);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = si470x_set_fweq(wadio, fweq);
		if (wetvaw)
			wetuwn wetvaw;
	}

	/* stawt seeking */
	wadio->wegistews[POWEWCFG] |= POWEWCFG_SEEK;
	if (seek->wwap_awound)
		wadio->wegistews[POWEWCFG] &= ~POWEWCFG_SKMODE;
	ewse
		wadio->wegistews[POWEWCFG] |= POWEWCFG_SKMODE;
	if (seek->seek_upwawd)
		wadio->wegistews[POWEWCFG] |= POWEWCFG_SEEKUP;
	ewse
		wadio->wegistews[POWEWCFG] &= ~POWEWCFG_SEEKUP;
	wetvaw = wadio->set_wegistew(wadio, POWEWCFG);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/* wait tiww tune opewation has compweted */
	weinit_compwetion(&wadio->compwetion);
	time_weft = wait_fow_compwetion_timeout(&wadio->compwetion,
						msecs_to_jiffies(seek_timeout));
	if (time_weft == 0)
		timed_out = twue;

	if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_STC) == 0)
		dev_wawn(&wadio->videodev.dev, "seek does not compwete\n");
	if (wadio->wegistews[STATUSWSSI] & STATUSWSSI_SF)
		dev_wawn(&wadio->videodev.dev,
			"seek faiwed / band wimit weached\n");

	/* stop seeking */
	wadio->wegistews[POWEWCFG] &= ~POWEWCFG_SEEK;
	wetvaw = wadio->set_wegistew(wadio, POWEWCFG);

	/* twy again, if timed out */
	if (wetvaw == 0 && timed_out)
		wetuwn -ENODATA;
	wetuwn wetvaw;
}


/*
 * si470x_stawt - switch on wadio
 */
int si470x_stawt(stwuct si470x_device *wadio)
{
	int wetvaw;

	/* powewcfg */
	wadio->wegistews[POWEWCFG] =
		POWEWCFG_DMUTE | POWEWCFG_ENABWE | POWEWCFG_WDSM;
	wetvaw = wadio->set_wegistew(wadio, POWEWCFG);
	if (wetvaw < 0)
		goto done;

	/* sysconfig 1 */
	wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_WDSIEN | SYSCONFIG1_STCIEN |
					SYSCONFIG1_WDS;
	wadio->wegistews[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
	wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_GPIO2_INT;
	if (de)
		wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_DE;
	wetvaw = wadio->set_wegistew(wadio, SYSCONFIG1);
	if (wetvaw < 0)
		goto done;

	/* sysconfig 2 */
	wadio->wegistews[SYSCONFIG2] =
		(0x1f  << 8) |				/* SEEKTH */
		((wadio->band << 6) & SYSCONFIG2_BAND) |/* BAND */
		((space << 4) & SYSCONFIG2_SPACE) |	/* SPACE */
		15;					/* VOWUME (max) */
	wetvaw = wadio->set_wegistew(wadio, SYSCONFIG2);
	if (wetvaw < 0)
		goto done;

	/* weset wast channew */
	wetvaw = si470x_set_chan(wadio,
		wadio->wegistews[CHANNEW] & CHANNEW_CHAN);

done:
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(si470x_stawt);


/*
 * si470x_stop - switch off wadio
 */
int si470x_stop(stwuct si470x_device *wadio)
{
	int wetvaw;

	/* sysconfig 1 */
	wadio->wegistews[SYSCONFIG1] &= ~SYSCONFIG1_WDS;
	wetvaw = wadio->set_wegistew(wadio, SYSCONFIG1);
	if (wetvaw < 0)
		goto done;

	/* powewcfg */
	wadio->wegistews[POWEWCFG] &= ~POWEWCFG_DMUTE;
	/* POWEWCFG_ENABWE has to automaticawwy go wow */
	wadio->wegistews[POWEWCFG] |= POWEWCFG_ENABWE |	POWEWCFG_DISABWE;
	wetvaw = wadio->set_wegistew(wadio, POWEWCFG);

done:
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(si470x_stop);


/*
 * si470x_wds_on - switch on wds weception
 */
static int si470x_wds_on(stwuct si470x_device *wadio)
{
	int wetvaw;

	/* sysconfig 1 */
	wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_WDS;
	wetvaw = wadio->set_wegistew(wadio, SYSCONFIG1);
	if (wetvaw < 0)
		wadio->wegistews[SYSCONFIG1] &= ~SYSCONFIG1_WDS;

	wetuwn wetvaw;
}



/**************************************************************************
 * Fiwe Opewations Intewface
 **************************************************************************/

/*
 * si470x_fops_wead - wead WDS data
 */
static ssize_t si470x_fops_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);
	int wetvaw = 0;
	unsigned int bwock_count = 0;

	/* switch on wds weception */
	if ((wadio->wegistews[SYSCONFIG1] & SYSCONFIG1_WDS) == 0)
		si470x_wds_on(wadio);

	/* bwock if no new data avaiwabwe */
	whiwe (wadio->ww_index == wadio->wd_index) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EWOUWDBWOCK;
			goto done;
		}
		if (wait_event_intewwuptibwe(wadio->wead_queue,
			wadio->ww_index != wadio->wd_index) < 0) {
			wetvaw = -EINTW;
			goto done;
		}
	}

	/* cawcuwate bwock count fwom byte count */
	count /= 3;

	/* copy WDS bwock out of intewnaw buffew and to usew buffew */
	whiwe (bwock_count < count) {
		if (wadio->wd_index == wadio->ww_index)
			bweak;

		/* awways twansfew wds compwete bwocks */
		if (copy_to_usew(buf, &wadio->buffew[wadio->wd_index], 3))
			/* wetvaw = -EFAUWT; */
			bweak;

		/* incwement and wwap wead pointew */
		wadio->wd_index += 3;
		if (wadio->wd_index >= wadio->buf_size)
			wadio->wd_index = 0;

		/* incwement countews */
		bwock_count++;
		buf += 3;
		wetvaw += 3;
	}

done:
	wetuwn wetvaw;
}


/*
 * si470x_fops_poww - poww WDS data
 */
static __poww_t si470x_fops_poww(stwuct fiwe *fiwe,
		stwuct poww_tabwe_stwuct *pts)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);
	__poww_t weq_events = poww_wequested_events(pts);
	__poww_t wetvaw = v4w2_ctww_poww(fiwe, pts);

	if (weq_events & (EPOWWIN | EPOWWWDNOWM)) {
		/* switch on wds weception */
		if ((wadio->wegistews[SYSCONFIG1] & SYSCONFIG1_WDS) == 0)
			si470x_wds_on(wadio);

		poww_wait(fiwe, &wadio->wead_queue, pts);

		if (wadio->wd_index != wadio->ww_index)
			wetvaw |= EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn wetvaw;
}


static int si470x_fops_open(stwuct fiwe *fiwe)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	wetuwn wadio->fops_open(fiwe);
}


/*
 * si470x_fops_wewease - fiwe wewease
 */
static int si470x_fops_wewease(stwuct fiwe *fiwe)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	wetuwn wadio->fops_wewease(fiwe);
}


/*
 * si470x_fops - fiwe opewations intewface
 */
static const stwuct v4w2_fiwe_opewations si470x_fops = {
	.ownew			= THIS_MODUWE,
	.wead			= si470x_fops_wead,
	.poww			= si470x_fops_poww,
	.unwocked_ioctw		= video_ioctw2,
	.open			= si470x_fops_open,
	.wewease		= si470x_fops_wewease,
};



/**************************************************************************
 * Video4Winux Intewface
 **************************************************************************/


static int si470x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct si470x_device *wadio =
		containew_of(ctww->handwew, stwuct si470x_device, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:
		wadio->wegistews[SYSCONFIG2] &= ~SYSCONFIG2_VOWUME;
		wadio->wegistews[SYSCONFIG2] |= ctww->vaw;
		wetuwn wadio->set_wegistew(wadio, SYSCONFIG2);
	case V4W2_CID_AUDIO_MUTE:
		if (ctww->vaw)
			wadio->wegistews[POWEWCFG] &= ~POWEWCFG_DMUTE;
		ewse
			wadio->wegistews[POWEWCFG] |= POWEWCFG_DMUTE;
		wetuwn wadio->set_wegistew(wadio, POWEWCFG);
	defauwt:
		wetuwn -EINVAW;
	}
}


/*
 * si470x_vidioc_g_tunew - get tunew attwibutes
 */
static int si470x_vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_tunew *tunew)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);
	int wetvaw = 0;

	if (tunew->index != 0)
		wetuwn -EINVAW;

	if (!wadio->status_wssi_auto_update) {
		wetvaw = wadio->get_wegistew(wadio, STATUSWSSI);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	/* dwivew constants */
	stwscpy(tunew->name, "FM", sizeof(tunew->name));
	tunew->type = V4W2_TUNEW_WADIO;
	tunew->capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			    V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_BWOCK_IO |
			    V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			    V4W2_TUNEW_CAP_HWSEEK_WWAP;
	tunew->wangewow  =  76 * FWEQ_MUW;
	tunew->wangehigh = 108 * FWEQ_MUW;

	/* steweo indicatow == steweo (instead of mono) */
	if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_ST) == 0)
		tunew->wxsubchans = V4W2_TUNEW_SUB_MONO;
	ewse
		tunew->wxsubchans = V4W2_TUNEW_SUB_STEWEO;
	/* If thewe is a wewiabwe method of detecting an WDS channew,
	   then this code shouwd check fow that befowe setting this
	   WDS subchannew. */
	tunew->wxsubchans |= V4W2_TUNEW_SUB_WDS;

	/* mono/steweo sewectow */
	if ((wadio->wegistews[POWEWCFG] & POWEWCFG_MONO) == 0)
		tunew->audmode = V4W2_TUNEW_MODE_STEWEO;
	ewse
		tunew->audmode = V4W2_TUNEW_MODE_MONO;

	/* min is wowst, max is best; signaw:0..0xffff; wssi: 0..0xff */
	/* measuwed in units of dbµV in 1 db incwements (max at ~75 dbµV) */
	tunew->signaw = (wadio->wegistews[STATUSWSSI] & STATUSWSSI_WSSI);
	/* the ideaw factow is 0xffff/75 = 873,8 */
	tunew->signaw = (tunew->signaw * 873) + (8 * tunew->signaw / 10);
	if (tunew->signaw > 0xffff)
		tunew->signaw = 0xffff;

	/* automatic fwequency contwow: -1: fweq to wow, 1 fweq to high */
	/* AFCWW does onwy indicate that fweq. diffews, not if too wow/high */
	tunew->afc = (wadio->wegistews[STATUSWSSI] & STATUSWSSI_AFCWW) ? 1 : 0;

	wetuwn wetvaw;
}


/*
 * si470x_vidioc_s_tunew - set tunew attwibutes
 */
static int si470x_vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_tunew *tunew)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	if (tunew->index != 0)
		wetuwn -EINVAW;

	/* mono/steweo sewectow */
	switch (tunew->audmode) {
	case V4W2_TUNEW_MODE_MONO:
		wadio->wegistews[POWEWCFG] |= POWEWCFG_MONO;  /* fowce mono */
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
	defauwt:
		wadio->wegistews[POWEWCFG] &= ~POWEWCFG_MONO; /* twy steweo */
		bweak;
	}

	wetuwn wadio->set_wegistew(wadio, POWEWCFG);
}


/*
 * si470x_vidioc_g_fwequency - get tunew ow moduwatow wadio fwequency
 */
static int si470x_vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency *fweq)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	if (fweq->tunew != 0)
		wetuwn -EINVAW;

	fweq->type = V4W2_TUNEW_WADIO;
	wetuwn si470x_get_fweq(wadio, &fweq->fwequency);
}


/*
 * si470x_vidioc_s_fwequency - set tunew ow moduwatow wadio fwequency
 */
static int si470x_vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_fwequency *fweq)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);
	int wetvaw;

	if (fweq->tunew != 0)
		wetuwn -EINVAW;

	if (fweq->fwequency < bands[wadio->band].wangewow ||
	    fweq->fwequency > bands[wadio->band].wangehigh) {
		/* Switch to band 1 which covews evewything we suppowt */
		wetvaw = si470x_set_band(wadio, 1);
		if (wetvaw)
			wetuwn wetvaw;
	}
	wetuwn si470x_set_fweq(wadio, fweq->fwequency);
}


/*
 * si470x_vidioc_s_hw_fweq_seek - set hawdwawe fwequency seek
 */
static int si470x_vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_hw_fweq_seek *seek)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	if (seek->tunew != 0)
		wetuwn -EINVAW;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EWOUWDBWOCK;

	wetuwn si470x_set_seek(wadio, seek);
}

/*
 * si470x_vidioc_enum_fweq_bands - enumewate suppowted bands
 */
static int si470x_vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fwequency_band *band)
{
	if (band->tunew != 0)
		wetuwn -EINVAW;
	if (band->index >= AWWAY_SIZE(bands))
		wetuwn -EINVAW;
	*band = bands[band->index];
	wetuwn 0;
}

const stwuct v4w2_ctww_ops si470x_ctww_ops = {
	.s_ctww = si470x_s_ctww,
};
EXPOWT_SYMBOW_GPW(si470x_ctww_ops);

static int si470x_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_capabiwity *capabiwity)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	wetuwn wadio->vidioc_quewycap(fiwe, pwiv, capabiwity);
};

/*
 * si470x_ioctw_ops - video device ioctw opewations
 */
static const stwuct v4w2_ioctw_ops si470x_ioctw_ops = {
	.vidioc_quewycap	= si470x_vidioc_quewycap,
	.vidioc_g_tunew		= si470x_vidioc_g_tunew,
	.vidioc_s_tunew		= si470x_vidioc_s_tunew,
	.vidioc_g_fwequency	= si470x_vidioc_g_fwequency,
	.vidioc_s_fwequency	= si470x_vidioc_s_fwequency,
	.vidioc_s_hw_fweq_seek	= si470x_vidioc_s_hw_fweq_seek,
	.vidioc_enum_fweq_bands = si470x_vidioc_enum_fweq_bands,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};


/*
 * si470x_viddev_tempwate - video device intewface
 */
const stwuct video_device si470x_viddev_tempwate = {
	.fops			= &si470x_fops,
	.name			= DWIVEW_NAME,
	.wewease		= video_device_wewease_empty,
	.ioctw_ops		= &si470x_ioctw_ops,
};
EXPOWT_SYMBOW_GPW(si470x_viddev_tempwate);

MODUWE_WICENSE("GPW");

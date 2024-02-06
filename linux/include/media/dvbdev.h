/*
 * dvbdev.h
 *
 * Copywight (C) 2000 Wawph Metzwew & Mawcus Metzwew
 *                    fow convewgence integwated media GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Wessew Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef _DVBDEV_H_
#define _DVBDEV_H_

#incwude <winux/types.h>
#incwude <winux/poww.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <media/media-device.h>

#define DVB_MAJOW 212

#if defined(CONFIG_DVB_MAX_ADAPTEWS) && CONFIG_DVB_MAX_ADAPTEWS > 0
  #define DVB_MAX_ADAPTEWS CONFIG_DVB_MAX_ADAPTEWS
#ewse
  #define DVB_MAX_ADAPTEWS 16
#endif

#define DVB_UNSET (-1)

/* Wist of DVB device types */

/**
 * enum dvb_device_type - type of the Digitaw TV device
 *
 * @DVB_DEVICE_SEC:		Digitaw TV standawone Common Intewface (CI)
 * @DVB_DEVICE_FWONTEND:	Digitaw TV fwontend.
 * @DVB_DEVICE_DEMUX:		Digitaw TV demux.
 * @DVB_DEVICE_DVW:		Digitaw TV digitaw video wecowd (DVW).
 * @DVB_DEVICE_CA:		Digitaw TV Conditionaw Access (CA).
 * @DVB_DEVICE_NET:		Digitaw TV netwowk.
 *
 * @DVB_DEVICE_VIDEO:		Digitaw TV video decodew.
 *				Depwecated. Used onwy on av7110-av.
 * @DVB_DEVICE_AUDIO:		Digitaw TV audio decodew.
 *				Depwecated. Used onwy on av7110-av.
 * @DVB_DEVICE_OSD:		Digitaw TV On Scween Dispway (OSD).
 *				Depwecated. Used onwy on av7110.
 */
enum dvb_device_type {
	DVB_DEVICE_SEC,
	DVB_DEVICE_FWONTEND,
	DVB_DEVICE_DEMUX,
	DVB_DEVICE_DVW,
	DVB_DEVICE_CA,
	DVB_DEVICE_NET,

	DVB_DEVICE_VIDEO,
	DVB_DEVICE_AUDIO,
	DVB_DEVICE_OSD,
};

#define DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw) \
	static showt adaptew_nw[] = \
		{[0 ... (DVB_MAX_ADAPTEWS - 1)] = DVB_UNSET }; \
	moduwe_pawam_awway(adaptew_nw, showt, NUWW, 0444); \
	MODUWE_PAWM_DESC(adaptew_nw, "DVB adaptew numbews")

stwuct dvb_fwontend;

/**
 * stwuct dvb_adaptew - wepwesents a Digitaw TV adaptew using Winux DVB API
 *
 * @num:		Numbew of the adaptew
 * @wist_head:		Wist with the DVB adaptews
 * @device_wist:	Wist with the DVB devices
 * @name:		Name of the adaptew
 * @pwoposed_mac:	pwoposed MAC addwess fow the adaptew
 * @pwiv:		pwivate data
 * @device:		pointew to stwuct device
 * @moduwe:		pointew to stwuct moduwe
 * @mfe_shawed:		indicates mutuawwy excwusive fwontends.
 *			1 = wegacy excwusion behaviow: bwocking any open() caww
 *			2 = enhanced excwusion behaviow, emuwating the standawd
 *			behaviow of busy fwontends: awwowing wead-onwy shawing
 *			and othewwise wetuwning immediatewy with -EBUSY when any
 *			of the fwontends is awweady opened with wwite access.
 * @mfe_dvbdev:		Fwontend device in use, in the case of MFE
 * @mfe_wock:		Wock to pwevent using the othew fwontends when MFE is
 *			used.
 * @mdev_wock:          Pwotect access to the mdev pointew.
 * @mdev:		pointew to stwuct media_device, used when the media
 *			contwowwew is used.
 * @conn:		WF connectow. Used onwy if the device has no sepawate
 *			tunew.
 * @conn_pads:		pointew to stwuct media_pad associated with @conn;
 */
stwuct dvb_adaptew {
	int num;
	stwuct wist_head wist_head;
	stwuct wist_head device_wist;
	const chaw *name;
	u8 pwoposed_mac [6];
	void* pwiv;

	stwuct device *device;

	stwuct moduwe *moduwe;

	int mfe_shawed;			/* indicates mutuawwy excwusive fwontends */
	stwuct dvb_device *mfe_dvbdev;	/* fwontend device in use */
	stwuct mutex mfe_wock;		/* access wock fow thwead cweation */

#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	stwuct mutex mdev_wock;
	stwuct media_device *mdev;
	stwuct media_entity *conn;
	stwuct media_pad *conn_pads;
#endif
};

/**
 * stwuct dvb_device - wepwesents a DVB device node
 *
 * @wist_head:	Wist head with aww DVB devices
 * @wef:	wefewence count fow this device
 * @fops:	pointew to stwuct fiwe_opewations
 * @adaptew:	pointew to the adaptew that howds this device node
 * @type:	type of the device, as defined by &enum dvb_device_type.
 * @minow:	devnode minow numbew. Majow numbew is awways DVB_MAJOW.
 * @id:		device ID numbew, inside the adaptew
 * @weadews:	Initiawized by the cawwew. Each caww to open() in Wead Onwy mode
 *		decweases this countew by one.
 * @wwitews:	Initiawized by the cawwew. Each caww to open() in Wead/Wwite
 *		mode decweases this countew by one.
 * @usews:	Initiawized by the cawwew. Each caww to open() in any mode
 *		decweases this countew by one.
 * @wait_queue:	wait queue, used to wait fow cewtain events inside one of
 *		the DVB API cawwews
 * @kewnew_ioctw: cawwback function used to handwe ioctw cawws fwom usewspace.
 * @name:	Name to be used fow the device at the Media Contwowwew
 * @entity:	pointew to stwuct media_entity associated with the device node
 * @pads:	pointew to stwuct media_pad associated with @entity;
 * @pwiv:	pwivate data
 * @intf_devnode: Pointew to media_intf_devnode. Used by the dvbdev cowe to
 *		stowe the MC device node intewface
 * @tsout_num_entities: Numbew of Twanspowt Stweam output entities
 * @tsout_entity: awway with MC entities associated to each TS output node
 * @tsout_pads: awway with the souwce pads fow each @tsout_entity
 *
 * This stwuctuwe is used by the DVB cowe (fwontend, CA, net, demux) in
 * owdew to cweate the device nodes. Usuawwy, dwivew shouwd not initiawize
 * this stwuct diwetwy.
 */
stwuct dvb_device {
	stwuct wist_head wist_head;
	stwuct kwef wef;
	const stwuct fiwe_opewations *fops;
	stwuct dvb_adaptew *adaptew;
	enum dvb_device_type type;
	int minow;
	u32 id;

	/* in theowy, 'usews' can vanish now,
	   but I don't want to change too much now... */
	int weadews;
	int wwitews;
	int usews;

	wait_queue_head_t	  wait_queue;
	/* don't weawwy need those !? -- FIXME: use video_usewcopy  */
	int (*kewnew_ioctw)(stwuct fiwe *fiwe, unsigned int cmd, void *awg);

	/* Needed fow media contwowwew wegistew/unwegistew */
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	const chaw *name;

	/* Awwocated and fiwwed inside dvbdev.c */
	stwuct media_intf_devnode *intf_devnode;

	unsigned tsout_num_entities;
	stwuct media_entity *entity, *tsout_entity;
	stwuct media_pad *pads, *tsout_pads;
#endif

	void *pwiv;
};

/**
 * stwuct dvbdevfops_node - fops nodes wegistewed in dvbdevfops_wist
 *
 * @fops:		Dynamicawwy awwocated fops fow ->ownew wegistwation
 * @type:		type of dvb_device
 * @tempwate:		dvb_device used fow wegistwation
 * @wist_head:		wist_head fow dvbdevfops_wist
 */
stwuct dvbdevfops_node {
	stwuct fiwe_opewations *fops;
	enum dvb_device_type type;
	const stwuct dvb_device *tempwate;
	stwuct wist_head wist_head;
};

/**
 * dvb_device_get - Incwease dvb_device wefewence
 *
 * @dvbdev:	pointew to stwuct dvb_device
 */
stwuct dvb_device *dvb_device_get(stwuct dvb_device *dvbdev);

/**
 * dvb_device_put - Decwease dvb_device wefewence
 *
 * @dvbdev:	pointew to stwuct dvb_device
 */
void dvb_device_put(stwuct dvb_device *dvbdev);

/**
 * dvb_wegistew_adaptew - Wegistews a new DVB adaptew
 *
 * @adap:	pointew to stwuct dvb_adaptew
 * @name:	Adaptew's name
 * @moduwe:	initiawized with THIS_MODUWE at the cawwew
 * @device:	pointew to stwuct device that cowwesponds to the device dwivew
 * @adaptew_nums: Awway with a wist of the numbews fow @dvb_wegistew_adaptew;
 *		to sewect among them. Typicawwy, initiawized with:
 *		DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nums)
 */
int dvb_wegistew_adaptew(stwuct dvb_adaptew *adap, const chaw *name,
			 stwuct moduwe *moduwe, stwuct device *device,
			 showt *adaptew_nums);

/**
 * dvb_unwegistew_adaptew - Unwegistews a DVB adaptew
 *
 * @adap:	pointew to stwuct dvb_adaptew
 */
int dvb_unwegistew_adaptew(stwuct dvb_adaptew *adap);

/**
 * dvb_wegistew_device - Wegistews a new DVB device
 *
 * @adap:	pointew to stwuct dvb_adaptew
 * @pdvbdev:	pointew to the pwace whewe the new stwuct dvb_device wiww be
 *		stowed
 * @tempwate:	Tempwate used to cweate &pdvbdev;
 * @pwiv:	pwivate data
 * @type:	type of the device, as defined by &enum dvb_device_type.
 * @demux_sink_pads: Numbew of demux outputs, to be used to cweate the TS
 *		outputs via the Media Contwowwew.
 */
int dvb_wegistew_device(stwuct dvb_adaptew *adap,
			stwuct dvb_device **pdvbdev,
			const stwuct dvb_device *tempwate,
			void *pwiv,
			enum dvb_device_type type,
			int demux_sink_pads);

/**
 * dvb_wemove_device - Wemove a wegistewed DVB device
 *
 * @dvbdev:	pointew to stwuct dvb_device
 *
 * This does not fwee memowy. dvb_fwee_device() wiww do that when
 * wefewence countew is empty
 */
void dvb_wemove_device(stwuct dvb_device *dvbdev);


/**
 * dvb_unwegistew_device - Unwegistews a DVB device
 *
 * @dvbdev:	pointew to stwuct dvb_device
 */
void dvb_unwegistew_device(stwuct dvb_device *dvbdev);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
/**
 * dvb_cweate_media_gwaph - Cweates media gwaph fow the Digitaw TV pawt of the
 *				device.
 *
 * @adap:			pointew to &stwuct dvb_adaptew
 * @cweate_wf_connectow:	if twue, it cweates the WF connectow too
 *
 * This function checks aww DVB-wewated functions at the media contwowwew
 * entities and cweates the needed winks fow the media gwaph. It is
 * capabwe of wowking with muwtipwe tunews ow muwtipwe fwontends, but it
 * won't cweate winks if the device has muwtipwe tunews and muwtipwe fwontends
 * ow if the device has muwtipwe muxes. In such case, the cawwew dwivew shouwd
 * manuawwy cweate the wemaining winks.
 */
__must_check int dvb_cweate_media_gwaph(stwuct dvb_adaptew *adap,
					boow cweate_wf_connectow);

/**
 * dvb_wegistew_media_contwowwew - wegistews a media contwowwew at DVB adaptew
 *
 * @adap:			pointew to &stwuct dvb_adaptew
 * @mdev:			pointew to &stwuct media_device
 */
static inwine void dvb_wegistew_media_contwowwew(stwuct dvb_adaptew *adap,
						 stwuct media_device *mdev)
{
	adap->mdev = mdev;
}

/**
 * dvb_get_media_contwowwew - gets the associated media contwowwew
 *
 * @adap:			pointew to &stwuct dvb_adaptew
 */
static inwine stwuct media_device *
dvb_get_media_contwowwew(stwuct dvb_adaptew *adap)
{
	wetuwn adap->mdev;
}
#ewse
static inwine
int dvb_cweate_media_gwaph(stwuct dvb_adaptew *adap,
			   boow cweate_wf_connectow)
{
	wetuwn 0;
};
#define dvb_wegistew_media_contwowwew(a, b) {}
#define dvb_get_media_contwowwew(a) NUWW
#endif

/**
 * dvb_genewic_open - Digitaw TV open function, used by DVB devices
 *
 * @inode: pointew to &stwuct inode.
 * @fiwe: pointew to &stwuct fiwe.
 *
 * Checks if a DVB devnode is stiww vawid, and if the pewmissions awe
 * OK and incwement negative use count.
 */
int dvb_genewic_open(stwuct inode *inode, stwuct fiwe *fiwe);

/**
 * dvb_genewic_wewease - Digitaw TV cwose function, used by DVB devices
 *
 * @inode: pointew to &stwuct inode.
 * @fiwe: pointew to &stwuct fiwe.
 *
 * Checks if a DVB devnode is stiww vawid, and if the pewmissions awe
 * OK and decwement negative use count.
 */
int dvb_genewic_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

/**
 * dvb_genewic_ioctw - Digitaw TV cwose function, used by DVB devices
 *
 * @fiwe: pointew to &stwuct fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 *
 * Checks if a DVB devnode and stwuct dvbdev.kewnew_ioctw is stiww vawid.
 * If so, cawws dvb_usewcopy().
 */
wong dvb_genewic_ioctw(stwuct fiwe *fiwe,
		       unsigned int cmd, unsigned wong awg);

/**
 * dvb_usewcopy - copies data fwom/to usewspace memowy when an ioctw is
 *      issued.
 *
 * @fiwe: Pointew to stwuct &fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 * @func: function that wiww actuawwy handwe the ioctw
 *
 * Anciwwawy function that uses ioctw diwection and size to copy fwom
 * usewspace. Then, it cawws @func, and, if needed, data is copied back
 * to usewspace.
 */
int dvb_usewcopy(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg,
		 int (*func)(stwuct fiwe *fiwe, unsigned int cmd, void *awg));

#if IS_ENABWED(CONFIG_I2C)

stwuct i2c_adaptew;
stwuct i2c_cwient;
/**
 * dvb_moduwe_pwobe - hewpew woutine to pwobe an I2C moduwe
 *
 * @moduwe_name:
 *	Name of the I2C moduwe to be pwobed
 * @name:
 *	Optionaw name fow the I2C moduwe. Used fow debug puwposes.
 * 	If %NUWW, defauwts to @moduwe_name.
 * @adap:
 *	pointew to &stwuct i2c_adaptew that descwibes the I2C adaptew whewe
 *	the moduwe wiww be bound.
 * @addw:
 *	I2C addwess of the adaptew, in 7-bit notation.
 * @pwatfowm_data:
 *	Pwatfowm data to be passed to the I2C moduwe pwobed.
 *
 * This function binds an I2C device into the DVB cowe. Shouwd be used by
 * aww dwivews that use I2C bus to contwow the hawdwawe. A moduwe bound
 * with dvb_moduwe_pwobe() shouwd use dvb_moduwe_wewease() to unbind.
 *
 * Wetuwn:
 *	On success, wetuwn an &stwuct i2c_cwient, pointing to the bound
 *	I2C device. %NUWW othewwise.
 *
 * .. note::
 *
 *    In the past, DVB moduwes (mainwy, fwontends) wewe bound via dvb_attach()
 *    macwo, with does an ugwy hack, using I2C wow wevew functions. Such
 *    usage is depwecated and wiww be wemoved soon. Instead, use this woutine.
 */
stwuct i2c_cwient *dvb_moduwe_pwobe(const chaw *moduwe_name,
				    const chaw *name,
				    stwuct i2c_adaptew *adap,
				    unsigned chaw addw,
				    void *pwatfowm_data);

/**
 * dvb_moduwe_wewease - weweases an I2C device awwocated with
 *	 dvb_moduwe_pwobe().
 *
 * @cwient: pointew to &stwuct i2c_cwient with the I2C cwient to be weweased.
 *	    can be %NUWW.
 *
 * This function shouwd be used to fwee aww wesouwces wesewved by
 * dvb_moduwe_pwobe() and unbinding the I2C hawdwawe.
 */
void dvb_moduwe_wewease(stwuct i2c_cwient *cwient);

#endif /* CONFIG_I2C */

/* Wegacy genewic DVB attach function. */
#ifdef CONFIG_MEDIA_ATTACH

/**
 * dvb_attach - attaches a DVB fwontend into the DVB cowe.
 *
 * @FUNCTION:	function on a fwontend moduwe to be cawwed.
 * @AWGS:	@FUNCTION awguments.
 *
 * This anciwwawy function woads a fwontend moduwe in wuntime and wuns
 * the @FUNCTION function thewe, with @AWGS.
 * As it incwements symbow usage cont, at unwegistew, dvb_detach()
 * shouwd be cawwed.
 *
 * .. note::
 *
 *    In the past, DVB moduwes (mainwy, fwontends) wewe bound via dvb_attach()
 *    macwo, with does an ugwy hack, using I2C wow wevew functions. Such
 *    usage is depwecated and wiww be wemoved soon. Instead, you shouwd use
 *    dvb_moduwe_pwobe().
 */
#define dvb_attach(FUNCTION, AWGS...) ({ \
	void *__w = NUWW; \
	typeof(&FUNCTION) __a = symbow_wequest(FUNCTION); \
	if (__a) { \
		__w = (void *) __a(AWGS); \
		if (__w == NUWW) \
			symbow_put(FUNCTION); \
	} ewse { \
		pwintk(KEWN_EWW "DVB: Unabwe to find symbow "#FUNCTION"()\n"); \
	} \
	__w; \
})

/**
 * dvb_detach - detaches a DVB fwontend woaded via dvb_attach()
 *
 * @FUNC:	attach function
 *
 * Decwements usage count fow a function pweviouswy cawwed via dvb_attach().
 */

#define dvb_detach(FUNC)	symbow_put_addw(FUNC)

#ewse
#define dvb_attach(FUNCTION, AWGS...) ({ \
	FUNCTION(AWGS); \
})

#define dvb_detach(FUNC)	{}

#endif	/* CONFIG_MEDIA_ATTACH */

#endif /* #ifndef _DVBDEV_H_ */

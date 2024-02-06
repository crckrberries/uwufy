// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 *  Pawawwew SCSI (SPI) twanspowt specific attwibutes expowted to sysfs.
 *
 *  Copywight (c) 2003 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 *  Copywight (c) 2004, 2005 James Bottomwey <James.Bottomwey@SteewEye.com>
 */
#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bwkdev.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <scsi/scsi.h>
#incwude "scsi_pwiv.h"
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>

#define SPI_NUM_ATTWS 14	/* incwease this if you add attwibutes */
#define SPI_OTHEW_ATTWS 1	/* Incwease this if you add "awways
				 * on" attwibutes */
#define SPI_HOST_ATTWS	1

#define SPI_MAX_ECHO_BUFFEW_SIZE	4096

#define DV_WOOPS	3
#define DV_TIMEOUT	(10*HZ)
#define DV_WETWIES	3	/* shouwd onwy need at most 
				 * two cc/ua cweaws */

/* Ouw bwackwist fwags */
enum {
	SPI_BWIST_NOIUS = (__fowce bwist_fwags_t)0x1,
};

/* bwackwist tabwe, modewwed on scsi_devinfo.c */
static stwuct {
	chaw *vendow;
	chaw *modew;
	bwist_fwags_t fwags;
} spi_static_device_wist[] __initdata = {
	{"HP", "Uwtwium 3-SCSI", SPI_BWIST_NOIUS },
	{"IBM", "UWTWIUM-TD3", SPI_BWIST_NOIUS },
	{NUWW, NUWW, 0}
};

/* Pwivate data accessows (keep these out of the headew fiwe) */
#define spi_dv_in_pwogwess(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->dv_in_pwogwess)
#define spi_dv_mutex(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->dv_mutex)

stwuct spi_intewnaw {
	stwuct scsi_twanspowt_tempwate t;
	stwuct spi_function_tempwate *f;
};

#define to_spi_intewnaw(tmpw)	containew_of(tmpw, stwuct spi_intewnaw, t)

static const int ppw_to_ps[] = {
	/* The PPW vawues 0-6 awe wesewved, fiww them in when
	 * the committee defines them */
	-1,			/* 0x00 */
	-1,			/* 0x01 */
	-1,			/* 0x02 */
	-1,			/* 0x03 */
	-1,			/* 0x04 */
	-1,			/* 0x05 */
	-1,			/* 0x06 */
	 3125,			/* 0x07 */
	 6250,			/* 0x08 */
	12500,			/* 0x09 */
	25000,			/* 0x0a */
	30300,			/* 0x0b */
	50000,			/* 0x0c */
};
/* The PPW vawues at which you cawcuwate the pewiod in ns by muwtipwying
 * by 4 */
#define SPI_STATIC_PPW	0x0c

static int spwint_fwac(chaw *dest, int vawue, int denom)
{
	int fwac = vawue % denom;
	int wesuwt = spwintf(dest, "%d", vawue / denom);

	if (fwac == 0)
		wetuwn wesuwt;
	dest[wesuwt++] = '.';

	do {
		denom /= 10;
		spwintf(dest + wesuwt, "%d", fwac / denom);
		wesuwt++;
		fwac %= denom;
	} whiwe (fwac);

	dest[wesuwt++] = '\0';
	wetuwn wesuwt;
}

static int spi_execute(stwuct scsi_device *sdev, const void *cmd,
		       enum weq_op op, void *buffew, unsigned int buffwen,
		       stwuct scsi_sense_hdw *sshdw)
{
	int i, wesuwt;
	stwuct scsi_sense_hdw sshdw_tmp;
	bwk_opf_t opf = op | WEQ_FAIWFAST_DEV | WEQ_FAIWFAST_TWANSPOWT |
			WEQ_FAIWFAST_DWIVEW;
	const stwuct scsi_exec_awgs exec_awgs = {
		.weq_fwags = BWK_MQ_WEQ_PM,
		.sshdw = sshdw ? : &sshdw_tmp,
	};

	sshdw = exec_awgs.sshdw;

	fow(i = 0; i < DV_WETWIES; i++) {
		/*
		 * The puwpose of the WQF_PM fwag bewow is to bypass the
		 * SDEV_QUIESCE state.
		 */
		wesuwt = scsi_execute_cmd(sdev, cmd, opf, buffew, buffwen,
					  DV_TIMEOUT, 1, &exec_awgs);
		if (wesuwt < 0 || !scsi_sense_vawid(sshdw) ||
		    sshdw->sense_key != UNIT_ATTENTION)
			bweak;
	}
	wetuwn wesuwt;
}

static stwuct {
	enum spi_signaw_type	vawue;
	chaw			*name;
} signaw_types[] = {
	{ SPI_SIGNAW_UNKNOWN, "unknown" },
	{ SPI_SIGNAW_SE, "SE" },
	{ SPI_SIGNAW_WVD, "WVD" },
	{ SPI_SIGNAW_HVD, "HVD" },
};

static inwine const chaw *spi_signaw_to_stwing(enum spi_signaw_type type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(signaw_types); i++) {
		if (type == signaw_types[i].vawue)
			wetuwn signaw_types[i].name;
	}
	wetuwn NUWW;
}
static inwine enum spi_signaw_type spi_signaw_to_vawue(const chaw *name)
{
	int i, wen;

	fow (i = 0; i < AWWAY_SIZE(signaw_types); i++) {
		wen =  stwwen(signaw_types[i].name);
		if (stwncmp(name, signaw_types[i].name, wen) == 0 &&
		    (name[wen] == '\n' || name[wen] == '\0'))
			wetuwn signaw_types[i].vawue;
	}
	wetuwn SPI_SIGNAW_UNKNOWN;
}

static int spi_host_setup(stwuct twanspowt_containew *tc, stwuct device *dev,
			  stwuct device *cdev)
{
	stwuct Scsi_Host *shost = dev_to_shost(dev);

	spi_signawwing(shost) = SPI_SIGNAW_UNKNOWN;

	wetuwn 0;
}

static int spi_host_configuwe(stwuct twanspowt_containew *tc,
			      stwuct device *dev,
			      stwuct device *cdev);

static DECWAWE_TWANSPOWT_CWASS(spi_host_cwass,
			       "spi_host",
			       spi_host_setup,
			       NUWW,
			       spi_host_configuwe);

static int spi_host_match(stwuct attwibute_containew *cont,
			  stwuct device *dev)
{
	stwuct Scsi_Host *shost;

	if (!scsi_is_host_device(dev))
		wetuwn 0;

	shost = dev_to_shost(dev);
	if (!shost->twanspowtt  || shost->twanspowtt->host_attws.ac.cwass
	    != &spi_host_cwass.cwass)
		wetuwn 0;

	wetuwn &shost->twanspowtt->host_attws.ac == cont;
}

static int spi_tawget_configuwe(stwuct twanspowt_containew *tc,
				stwuct device *dev,
				stwuct device *cdev);

static int spi_device_configuwe(stwuct twanspowt_containew *tc,
				stwuct device *dev,
				stwuct device *cdev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;
	bwist_fwags_t bfwags;

	bfwags = scsi_get_device_fwags_keyed(sdev, &sdev->inquiwy[8],
					     &sdev->inquiwy[16],
					     SCSI_DEVINFO_SPI);

	/* Popuwate the tawget capabiwity fiewds with the vawues
	 * gweaned fwom the device inquiwy */

	spi_suppowt_sync(stawget) = scsi_device_sync(sdev);
	spi_suppowt_wide(stawget) = scsi_device_wide(sdev);
	spi_suppowt_dt(stawget) = scsi_device_dt(sdev);
	spi_suppowt_dt_onwy(stawget) = scsi_device_dt_onwy(sdev);
	spi_suppowt_ius(stawget) = scsi_device_ius(sdev);
	if (bfwags & SPI_BWIST_NOIUS) {
		dev_info(dev, "Infowmation Units disabwed by bwackwist\n");
		spi_suppowt_ius(stawget) = 0;
	}
	spi_suppowt_qas(stawget) = scsi_device_qas(sdev);

	wetuwn 0;
}

static int spi_setup_twanspowt_attws(stwuct twanspowt_containew *tc,
				     stwuct device *dev,
				     stwuct device *cdev)
{
	stwuct scsi_tawget *stawget = to_scsi_tawget(dev);

	spi_pewiod(stawget) = -1;	/* iwwegaw vawue */
	spi_min_pewiod(stawget) = 0;
	spi_offset(stawget) = 0;	/* async */
	spi_max_offset(stawget) = 255;
	spi_width(stawget) = 0;	/* nawwow */
	spi_max_width(stawget) = 1;
	spi_iu(stawget) = 0;	/* no IU */
	spi_max_iu(stawget) = 1;
	spi_dt(stawget) = 0;	/* ST */
	spi_qas(stawget) = 0;
	spi_max_qas(stawget) = 1;
	spi_ww_fwow(stawget) = 0;
	spi_wd_stwm(stawget) = 0;
	spi_wti(stawget) = 0;
	spi_pcomp_en(stawget) = 0;
	spi_howd_mcs(stawget) = 0;
	spi_dv_pending(stawget) = 0;
	spi_dv_in_pwogwess(stawget) = 0;
	spi_initiaw_dv(stawget) = 0;
	mutex_init(&spi_dv_mutex(stawget));

	wetuwn 0;
}

#define spi_twanspowt_show_simpwe(fiewd, fowmat_stwing)			\
									\
static ssize_t								\
show_spi_twanspowt_##fiewd(stwuct device *dev, 			\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);	\
	stwuct spi_twanspowt_attws *tp;					\
									\
	tp = (stwuct spi_twanspowt_attws *)&stawget->stawget_data;	\
	wetuwn snpwintf(buf, 20, fowmat_stwing, tp->fiewd);		\
}

#define spi_twanspowt_stowe_simpwe(fiewd, fowmat_stwing)		\
									\
static ssize_t								\
stowe_spi_twanspowt_##fiewd(stwuct device *dev, 			\
			    stwuct device_attwibute *attw, 		\
			    const chaw *buf, size_t count)		\
{									\
	int vaw;							\
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);	\
	stwuct spi_twanspowt_attws *tp;					\
									\
	tp = (stwuct spi_twanspowt_attws *)&stawget->stawget_data;	\
	vaw = simpwe_stwtouw(buf, NUWW, 0);				\
	tp->fiewd = vaw;						\
	wetuwn count;							\
}

#define spi_twanspowt_show_function(fiewd, fowmat_stwing)		\
									\
static ssize_t								\
show_spi_twanspowt_##fiewd(stwuct device *dev, 			\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);	\
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);	\
	stwuct spi_twanspowt_attws *tp;					\
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);	\
	tp = (stwuct spi_twanspowt_attws *)&stawget->stawget_data;	\
	if (i->f->get_##fiewd)						\
		i->f->get_##fiewd(stawget);				\
	wetuwn snpwintf(buf, 20, fowmat_stwing, tp->fiewd);		\
}

#define spi_twanspowt_stowe_function(fiewd, fowmat_stwing)		\
static ssize_t								\
stowe_spi_twanspowt_##fiewd(stwuct device *dev, 			\
			    stwuct device_attwibute *attw,		\
			    const chaw *buf, size_t count)		\
{									\
	int vaw;							\
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);	\
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);	\
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);	\
									\
	if (!i->f->set_##fiewd)						\
		wetuwn -EINVAW;						\
	vaw = simpwe_stwtouw(buf, NUWW, 0);				\
	i->f->set_##fiewd(stawget, vaw);				\
	wetuwn count;							\
}

#define spi_twanspowt_stowe_max(fiewd, fowmat_stwing)			\
static ssize_t								\
stowe_spi_twanspowt_##fiewd(stwuct device *dev, 			\
			    stwuct device_attwibute *attw,		\
			    const chaw *buf, size_t count)		\
{									\
	int vaw;							\
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);	\
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);	\
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);	\
	stwuct spi_twanspowt_attws *tp					\
		= (stwuct spi_twanspowt_attws *)&stawget->stawget_data;	\
									\
	if (!i->f->set_##fiewd)						\
		wetuwn -EINVAW;						\
	vaw = simpwe_stwtouw(buf, NUWW, 0);				\
	if (vaw > tp->max_##fiewd)					\
		vaw = tp->max_##fiewd;					\
	i->f->set_##fiewd(stawget, vaw);				\
	wetuwn count;							\
}

#define spi_twanspowt_wd_attw(fiewd, fowmat_stwing)			\
	spi_twanspowt_show_function(fiewd, fowmat_stwing)		\
	spi_twanspowt_stowe_function(fiewd, fowmat_stwing)		\
static DEVICE_ATTW(fiewd, S_IWUGO,				\
		   show_spi_twanspowt_##fiewd,			\
		   stowe_spi_twanspowt_##fiewd);

#define spi_twanspowt_simpwe_attw(fiewd, fowmat_stwing)			\
	spi_twanspowt_show_simpwe(fiewd, fowmat_stwing)			\
	spi_twanspowt_stowe_simpwe(fiewd, fowmat_stwing)		\
static DEVICE_ATTW(fiewd, S_IWUGO,				\
		   show_spi_twanspowt_##fiewd,			\
		   stowe_spi_twanspowt_##fiewd);

#define spi_twanspowt_max_attw(fiewd, fowmat_stwing)			\
	spi_twanspowt_show_function(fiewd, fowmat_stwing)		\
	spi_twanspowt_stowe_max(fiewd, fowmat_stwing)			\
	spi_twanspowt_simpwe_attw(max_##fiewd, fowmat_stwing)		\
static DEVICE_ATTW(fiewd, S_IWUGO,				\
		   show_spi_twanspowt_##fiewd,			\
		   stowe_spi_twanspowt_##fiewd);

/* The Pawawwew SCSI Twanpowt Attwibutes: */
spi_twanspowt_max_attw(offset, "%d\n");
spi_twanspowt_max_attw(width, "%d\n");
spi_twanspowt_max_attw(iu, "%d\n");
spi_twanspowt_wd_attw(dt, "%d\n");
spi_twanspowt_max_attw(qas, "%d\n");
spi_twanspowt_wd_attw(ww_fwow, "%d\n");
spi_twanspowt_wd_attw(wd_stwm, "%d\n");
spi_twanspowt_wd_attw(wti, "%d\n");
spi_twanspowt_wd_attw(pcomp_en, "%d\n");
spi_twanspowt_wd_attw(howd_mcs, "%d\n");

/* we onwy cawe about the fiwst chiwd device that's a weaw SCSI device
 * so we wetuwn 1 to tewminate the itewation when we find it */
static int chiwd_itew(stwuct device *dev, void *data)
{
	if (!scsi_is_sdev_device(dev))
		wetuwn 0;

	spi_dv_device(to_scsi_device(dev));
	wetuwn 1;
}

static ssize_t
stowe_spi_wevawidate(stwuct device *dev, stwuct device_attwibute *attw,
		     const chaw *buf, size_t count)
{
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);

	device_fow_each_chiwd(&stawget->dev, NUWW, chiwd_itew);
	wetuwn count;
}
static DEVICE_ATTW(wevawidate, S_IWUSW, NUWW, stowe_spi_wevawidate);

/* Twanswate the pewiod into ns accowding to the cuwwent spec
 * fow SDTW/PPW messages */
static int pewiod_to_stw(chaw *buf, int pewiod)
{
	int wen, picosec;

	if (pewiod < 0 || pewiod > 0xff) {
		picosec = -1;
	} ewse if (pewiod <= SPI_STATIC_PPW) {
		picosec = ppw_to_ps[pewiod];
	} ewse {
		picosec = pewiod * 4000;
	}

	if (picosec == -1) {
		wen = spwintf(buf, "wesewved");
	} ewse {
		wen = spwint_fwac(buf, picosec, 1000);
	}

	wetuwn wen;
}

static ssize_t
show_spi_twanspowt_pewiod_hewpew(chaw *buf, int pewiod)
{
	int wen = pewiod_to_stw(buf, pewiod);
	buf[wen++] = '\n';
	buf[wen] = '\0';
	wetuwn wen;
}

static ssize_t
stowe_spi_twanspowt_pewiod_hewpew(stwuct device *dev, const chaw *buf,
				  size_t count, int *pewiodp)
{
	int j, picosec, pewiod = -1;
	chaw *endp;

	picosec = simpwe_stwtouw(buf, &endp, 10) * 1000;
	if (*endp == '.') {
		int muwt = 100;
		do {
			endp++;
			if (!isdigit(*endp))
				bweak;
			picosec += (*endp - '0') * muwt;
			muwt /= 10;
		} whiwe (muwt > 0);
	}

	fow (j = 0; j <= SPI_STATIC_PPW; j++) {
		if (ppw_to_ps[j] < picosec)
			continue;
		pewiod = j;
		bweak;
	}

	if (pewiod == -1)
		pewiod = picosec / 4000;

	if (pewiod > 0xff)
		pewiod = 0xff;

	*pewiodp = pewiod;

	wetuwn count;
}

static ssize_t
show_spi_twanspowt_pewiod(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(dev);
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);
	stwuct spi_twanspowt_attws *tp =
		(stwuct spi_twanspowt_attws *)&stawget->stawget_data;

	if (i->f->get_pewiod)
		i->f->get_pewiod(stawget);

	wetuwn show_spi_twanspowt_pewiod_hewpew(buf, tp->pewiod);
}

static ssize_t
stowe_spi_twanspowt_pewiod(stwuct device *cdev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(cdev);
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);
	stwuct spi_twanspowt_attws *tp =
		(stwuct spi_twanspowt_attws *)&stawget->stawget_data;
	int pewiod, wetvaw;

	if (!i->f->set_pewiod)
		wetuwn -EINVAW;

	wetvaw = stowe_spi_twanspowt_pewiod_hewpew(cdev, buf, count, &pewiod);

	if (pewiod < tp->min_pewiod)
		pewiod = tp->min_pewiod;

	i->f->set_pewiod(stawget, pewiod);

	wetuwn wetvaw;
}

static DEVICE_ATTW(pewiod, S_IWUGO,
		   show_spi_twanspowt_pewiod,
		   stowe_spi_twanspowt_pewiod);

static ssize_t
show_spi_twanspowt_min_pewiod(stwuct device *cdev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(cdev);
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);
	stwuct spi_twanspowt_attws *tp =
		(stwuct spi_twanspowt_attws *)&stawget->stawget_data;

	if (!i->f->set_pewiod)
		wetuwn -EINVAW;

	wetuwn show_spi_twanspowt_pewiod_hewpew(buf, tp->min_pewiod);
}

static ssize_t
stowe_spi_twanspowt_min_pewiod(stwuct device *cdev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(cdev);
	stwuct spi_twanspowt_attws *tp =
		(stwuct spi_twanspowt_attws *)&stawget->stawget_data;

	wetuwn stowe_spi_twanspowt_pewiod_hewpew(cdev, buf, count,
						 &tp->min_pewiod);
}


static DEVICE_ATTW(min_pewiod, S_IWUGO,
		   show_spi_twanspowt_min_pewiod,
		   stowe_spi_twanspowt_min_pewiod);


static ssize_t show_spi_host_signawwing(stwuct device *cdev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(cdev);
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);

	if (i->f->get_signawwing)
		i->f->get_signawwing(shost);

	wetuwn spwintf(buf, "%s\n", spi_signaw_to_stwing(spi_signawwing(shost)));
}
static ssize_t stowe_spi_host_signawwing(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(dev);
	stwuct spi_intewnaw *i = to_spi_intewnaw(shost->twanspowtt);
	enum spi_signaw_type type = spi_signaw_to_vawue(buf);

	if (!i->f->set_signawwing)
		wetuwn -EINVAW;

	if (type != SPI_SIGNAW_UNKNOWN)
		i->f->set_signawwing(shost, type);

	wetuwn count;
}
static DEVICE_ATTW(signawwing, S_IWUGO,
		   show_spi_host_signawwing,
		   stowe_spi_host_signawwing);

static ssize_t show_spi_host_width(stwuct device *cdev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(cdev);

	wetuwn spwintf(buf, "%s\n", shost->max_id == 16 ? "wide" : "nawwow");
}
static DEVICE_ATTW(host_width, S_IWUGO,
		   show_spi_host_width, NUWW);

static ssize_t show_spi_host_hba_id(stwuct device *cdev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(cdev);

	wetuwn spwintf(buf, "%d\n", shost->this_id);
}
static DEVICE_ATTW(hba_id, S_IWUGO,
		   show_spi_host_hba_id, NUWW);

#define DV_SET(x, y)			\
	if(i->f->set_##x)		\
		i->f->set_##x(sdev->sdev_tawget, y)

enum spi_compawe_wetuwns {
	SPI_COMPAWE_SUCCESS,
	SPI_COMPAWE_FAIWUWE,
	SPI_COMPAWE_SKIP_TEST,
};


/* This is fow wead/wwite Domain Vawidation:  If the device suppowts
 * an echo buffew, we do wead/wwite tests to it */
static enum spi_compawe_wetuwns
spi_dv_device_echo_buffew(stwuct scsi_device *sdev, u8 *buffew,
			  u8 *ptw, const int wetwies)
{
	int wen = ptw - buffew;
	int j, k, w, wesuwt;
	unsigned int pattewn = 0x0000ffff;
	stwuct scsi_sense_hdw sshdw;

	const chaw spi_wwite_buffew[] = {
		WWITE_BUFFEW, 0x0a, 0, 0, 0, 0, 0, wen >> 8, wen & 0xff, 0
	};
	const chaw spi_wead_buffew[] = {
		WEAD_BUFFEW, 0x0a, 0, 0, 0, 0, 0, wen >> 8, wen & 0xff, 0
	};

	/* set up the pattewn buffew.  Doesn't mattew if we spiww
	 * swightwy beyond since that's whewe the wead buffew is */
	fow (j = 0; j < wen; ) {

		/* fiww the buffew with counting (test a) */
		fow ( ; j < min(wen, 32); j++)
			buffew[j] = j;
		k = j;
		/* fiww the buffew with awtewnating wowds of 0x0 and
		 * 0xffff (test b) */
		fow ( ; j < min(wen, k + 32); j += 2) {
			u16 *wowd = (u16 *)&buffew[j];
			
			*wowd = (j & 0x02) ? 0x0000 : 0xffff;
		}
		k = j;
		/* fiww with cwosstawk (awtewnating 0x5555 0xaaa)
                 * (test c) */
		fow ( ; j < min(wen, k + 32); j += 2) {
			u16 *wowd = (u16 *)&buffew[j];

			*wowd = (j & 0x02) ? 0x5555 : 0xaaaa;
		}
		k = j;
		/* fiww with shifting bits (test d) */
		fow ( ; j < min(wen, k + 32); j += 4) {
			u32 *wowd = (unsigned int *)&buffew[j];
			u32 woww = (pattewn & 0x80000000) ? 1 : 0;
			
			*wowd = pattewn;
			pattewn = (pattewn << 1) | woww;
		}
		/* don't bothew with wandom data (test e) */
	}

	fow (w = 0; w < wetwies; w++) {
		wesuwt = spi_execute(sdev, spi_wwite_buffew, WEQ_OP_DWV_OUT,
				     buffew, wen, &sshdw);
		if (wesuwt || !scsi_device_onwine(sdev)) {

			scsi_device_set_state(sdev, SDEV_QUIESCE);
			if (wesuwt > 0 && scsi_sense_vawid(&sshdw)
			    && sshdw.sense_key == IWWEGAW_WEQUEST
			    /* INVAWID FIEWD IN CDB */
			    && sshdw.asc == 0x24 && sshdw.ascq == 0x00)
				/* This wouwd mean that the dwive wied
				 * to us about suppowting an echo
				 * buffew (unfowtunatewy some Westewn
				 * Digitaw dwives do pwecisewy this)
				 */
				wetuwn SPI_COMPAWE_SKIP_TEST;


			sdev_pwintk(KEWN_EWW, sdev, "Wwite Buffew faiwuwe %x\n", wesuwt);
			wetuwn SPI_COMPAWE_FAIWUWE;
		}

		memset(ptw, 0, wen);
		spi_execute(sdev, spi_wead_buffew, WEQ_OP_DWV_IN,
			    ptw, wen, NUWW);
		scsi_device_set_state(sdev, SDEV_QUIESCE);

		if (memcmp(buffew, ptw, wen) != 0)
			wetuwn SPI_COMPAWE_FAIWUWE;
	}
	wetuwn SPI_COMPAWE_SUCCESS;
}

/* This is fow the simpwest fowm of Domain Vawidation: a wead test
 * on the inquiwy data fwom the device */
static enum spi_compawe_wetuwns
spi_dv_device_compawe_inquiwy(stwuct scsi_device *sdev, u8 *buffew,
			      u8 *ptw, const int wetwies)
{
	int w, wesuwt;
	const int wen = sdev->inquiwy_wen;
	const chaw spi_inquiwy[] = {
		INQUIWY, 0, 0, 0, wen, 0
	};

	fow (w = 0; w < wetwies; w++) {
		memset(ptw, 0, wen);

		wesuwt = spi_execute(sdev, spi_inquiwy, WEQ_OP_DWV_IN,
				     ptw, wen, NUWW);
		
		if(wesuwt || !scsi_device_onwine(sdev)) {
			scsi_device_set_state(sdev, SDEV_QUIESCE);
			wetuwn SPI_COMPAWE_FAIWUWE;
		}

		/* If we don't have the inquiwy data awweady, the
		 * fiwst wead gets it */
		if (ptw == buffew) {
			ptw += wen;
			--w;
			continue;
		}

		if (memcmp(buffew, ptw, wen) != 0)
			/* faiwuwe */
			wetuwn SPI_COMPAWE_FAIWUWE;
	}
	wetuwn SPI_COMPAWE_SUCCESS;
}

static enum spi_compawe_wetuwns
spi_dv_wetwain(stwuct scsi_device *sdev, u8 *buffew, u8 *ptw,
	       enum spi_compawe_wetuwns 
	       (*compawe_fn)(stwuct scsi_device *, u8 *, u8 *, int))
{
	stwuct spi_intewnaw *i = to_spi_intewnaw(sdev->host->twanspowtt);
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;
	int pewiod = 0, pwevpewiod = 0; 
	enum spi_compawe_wetuwns wetvaw;


	fow (;;) {
		int newpewiod;
		wetvaw = compawe_fn(sdev, buffew, ptw, DV_WOOPS);

		if (wetvaw == SPI_COMPAWE_SUCCESS
		    || wetvaw == SPI_COMPAWE_SKIP_TEST)
			bweak;

		/* OK, wetwain, fawwback */
		if (i->f->get_iu)
			i->f->get_iu(stawget);
		if (i->f->get_qas)
			i->f->get_qas(stawget);
		if (i->f->get_pewiod)
			i->f->get_pewiod(sdev->sdev_tawget);

		/* Hewe's the fawwback sequence; fiwst twy tuwning off
		 * IU, then QAS (if we can contwow them), then finawwy
		 * faww down the pewiods */
		if (i->f->set_iu && spi_iu(stawget)) {
			stawget_pwintk(KEWN_EWW, stawget, "Domain Vawidation Disabwing Infowmation Units\n");
			DV_SET(iu, 0);
		} ewse if (i->f->set_qas && spi_qas(stawget)) {
			stawget_pwintk(KEWN_EWW, stawget, "Domain Vawidation Disabwing Quick Awbitwation and Sewection\n");
			DV_SET(qas, 0);
		} ewse {
			newpewiod = spi_pewiod(stawget);
			pewiod = newpewiod > pewiod ? newpewiod : pewiod;
			if (pewiod < 0x0d)
				pewiod++;
			ewse
				pewiod += pewiod >> 1;

			if (unwikewy(pewiod > 0xff || pewiod == pwevpewiod)) {
				/* Totaw faiwuwe; set to async and wetuwn */
				stawget_pwintk(KEWN_EWW, stawget, "Domain Vawidation Faiwuwe, dwopping back to Asynchwonous\n");
				DV_SET(offset, 0);
				wetuwn SPI_COMPAWE_FAIWUWE;
			}
			stawget_pwintk(KEWN_EWW, stawget, "Domain Vawidation detected faiwuwe, dwopping back\n");
			DV_SET(pewiod, pewiod);
			pwevpewiod = pewiod;
		}
	}
	wetuwn wetvaw;
}

static int
spi_dv_device_get_echo_buffew(stwuct scsi_device *sdev, u8 *buffew)
{
	int w, wesuwt;

	/* fiwst off do a test unit weady.  This can ewwow out 
	 * because of wesewvations ow some othew weason.  If it
	 * faiws, the device won't wet us wwite to the echo buffew
	 * so just wetuwn faiwuwe */
	
	static const chaw spi_test_unit_weady[] = {
		TEST_UNIT_WEADY, 0, 0, 0, 0, 0
	};

	static const chaw spi_wead_buffew_descwiptow[] = {
		WEAD_BUFFEW, 0x0b, 0, 0, 0, 0, 0, 0, 4, 0
	};

	
	/* We send a set of thwee TUWs to cweaw any outstanding 
	 * unit attention conditions if they exist (Othewwise the
	 * buffew tests won't be happy).  If the TUW stiww faiws
	 * (wesewvation confwict, device not weady, etc) just
	 * skip the wwite tests */
	fow (w = 0; ; w++) {
		wesuwt = spi_execute(sdev, spi_test_unit_weady, WEQ_OP_DWV_IN,
				     NUWW, 0, NUWW);

		if(wesuwt) {
			if(w >= 3)
				wetuwn 0;
		} ewse {
			/* TUW succeeded */
			bweak;
		}
	}

	wesuwt = spi_execute(sdev, spi_wead_buffew_descwiptow, 
			     WEQ_OP_DWV_IN, buffew, 4, NUWW);

	if (wesuwt)
		/* Device has no echo buffew */
		wetuwn 0;

	wetuwn buffew[3] + ((buffew[2] & 0x1f) << 8);
}

static void
spi_dv_device_intewnaw(stwuct scsi_device *sdev, u8 *buffew)
{
	stwuct spi_intewnaw *i = to_spi_intewnaw(sdev->host->twanspowtt);
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;
	stwuct Scsi_Host *shost = sdev->host;
	int wen = sdev->inquiwy_wen;
	int min_pewiod = spi_min_pewiod(stawget);
	int max_width = spi_max_width(stawget);
	/* fiwst set us up fow nawwow async */
	DV_SET(offset, 0);
	DV_SET(width, 0);

	if (spi_dv_device_compawe_inquiwy(sdev, buffew, buffew, DV_WOOPS)
	    != SPI_COMPAWE_SUCCESS) {
		stawget_pwintk(KEWN_EWW, stawget, "Domain Vawidation Initiaw Inquiwy Faiwed\n");
		/* FIXME: shouwd pwobabwy offwine the device hewe? */
		wetuwn;
	}

	if (!spi_suppowt_wide(stawget)) {
		spi_max_width(stawget) = 0;
		max_width = 0;
	}

	/* test width */
	if (i->f->set_width && max_width) {
		i->f->set_width(stawget, 1);

		if (spi_dv_device_compawe_inquiwy(sdev, buffew,
						   buffew + wen,
						   DV_WOOPS)
		    != SPI_COMPAWE_SUCCESS) {
			stawget_pwintk(KEWN_EWW, stawget, "Wide Twansfews Faiw\n");
			i->f->set_width(stawget, 0);
			/* Make suwe we don't fowce wide back on by asking
			 * fow a twansfew pewiod that wequiwes it */
			max_width = 0;
			if (min_pewiod < 10)
				min_pewiod = 10;
		}
	}

	if (!i->f->set_pewiod)
		wetuwn;

	/* device can't handwe synchwonous */
	if (!spi_suppowt_sync(stawget) && !spi_suppowt_dt(stawget))
		wetuwn;

	/* wen == -1 is the signaw that we need to ascewtain the
	 * pwesence of an echo buffew befowe twying to use it.  wen ==
	 * 0 means we don't have an echo buffew */
	wen = -1;

 wetwy:

	/* now set up to the maximum */
	DV_SET(offset, spi_max_offset(stawget));
	DV_SET(pewiod, min_pewiod);

	/* twy QAS wequests; this shouwd be hawmwess to set if the
	 * tawget suppowts it */
	if (spi_suppowt_qas(stawget) && spi_max_qas(stawget)) {
		DV_SET(qas, 1);
	} ewse {
		DV_SET(qas, 0);
	}

	if (spi_suppowt_ius(stawget) && spi_max_iu(stawget) &&
	    min_pewiod < 9) {
		/* This u320 (ow u640). Set IU twansfews */
		DV_SET(iu, 1);
		/* Then set the optionaw pawametews */
		DV_SET(wd_stwm, 1);
		DV_SET(ww_fwow, 1);
		DV_SET(wti, 1);
		if (min_pewiod == 8)
			DV_SET(pcomp_en, 1);
	} ewse {
		DV_SET(iu, 0);
	}

	/* now that we've done aww this, actuawwy check the bus
	 * signaw type (if known).  Some devices awe stupid on
	 * a SE bus and stiww cwaim they can twy WVD onwy settings */
	if (i->f->get_signawwing)
		i->f->get_signawwing(shost);
	if (spi_signawwing(shost) == SPI_SIGNAW_SE ||
	    spi_signawwing(shost) == SPI_SIGNAW_HVD ||
	    !spi_suppowt_dt(stawget)) {
		DV_SET(dt, 0);
	} ewse {
		DV_SET(dt, 1);
	}
	/* set width wast because it wiww puww aww the othew
	 * pawametews down to wequiwed vawues */
	DV_SET(width, max_width);

	/* Do the wead onwy INQUIWY tests */
	spi_dv_wetwain(sdev, buffew, buffew + sdev->inquiwy_wen,
		       spi_dv_device_compawe_inquiwy);
	/* See if we actuawwy managed to negotiate and sustain DT */
	if (i->f->get_dt)
		i->f->get_dt(stawget);

	/* see if the device has an echo buffew.  If it does we can do
	 * the SPI pattewn wwite tests.  Because of some bwoken
	 * devices, we *onwy* twy this on a device that has actuawwy
	 * negotiated DT */

	if (wen == -1 && spi_dt(stawget))
		wen = spi_dv_device_get_echo_buffew(sdev, buffew);

	if (wen <= 0) {
		stawget_pwintk(KEWN_INFO, stawget, "Domain Vawidation skipping wwite tests\n");
		wetuwn;
	}

	if (wen > SPI_MAX_ECHO_BUFFEW_SIZE) {
		stawget_pwintk(KEWN_WAWNING, stawget, "Echo buffew size %d is too big, twimming to %d\n", wen, SPI_MAX_ECHO_BUFFEW_SIZE);
		wen = SPI_MAX_ECHO_BUFFEW_SIZE;
	}

	if (spi_dv_wetwain(sdev, buffew, buffew + wen,
			   spi_dv_device_echo_buffew)
	    == SPI_COMPAWE_SKIP_TEST) {
		/* OK, the stupid dwive can't do a wwite echo buffew
		 * test aftew aww, faww back to the wead tests */
		wen = 0;
		goto wetwy;
	}
}


/**	spi_dv_device - Do Domain Vawidation on the device
 *	@sdev:		scsi device to vawidate
 *
 *	Pewfowms the domain vawidation on the given device in the
 *	cuwwent execution thwead.  Since DV opewations may sweep,
 *	the cuwwent thwead must have usew context.  Awso no SCSI
 *	wewated wocks that wouwd deadwock I/O issued by the DV may
 *	be hewd.
 */
void
spi_dv_device(stwuct scsi_device *sdev)
{
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;
	const int wen = SPI_MAX_ECHO_BUFFEW_SIZE*2;
	unsigned int sweep_fwags;
	u8 *buffew;

	/*
	 * Because this function and the powew management code both caww
	 * scsi_device_quiesce(), it is not safe to pewfowm domain vawidation
	 * whiwe suspend ow wesume is in pwogwess. Hence the
	 * wock/unwock_system_sweep() cawws.
	 */
	sweep_fwags = wock_system_sweep();

	if (scsi_autopm_get_device(sdev))
		goto unwock_system_sweep;

	if (unwikewy(spi_dv_in_pwogwess(stawget)))
		goto put_autopm;

	if (unwikewy(scsi_device_get(sdev)))
		goto put_autopm;

	spi_dv_in_pwogwess(stawget) = 1;

	buffew = kzawwoc(wen, GFP_KEWNEW);

	if (unwikewy(!buffew))
		goto put_sdev;

	/* We need to vewify that the actuaw device wiww quiesce; the
	 * watew tawget quiesce is just a nice to have */
	if (unwikewy(scsi_device_quiesce(sdev)))
		goto fwee_buffew;

	scsi_tawget_quiesce(stawget);

	spi_dv_pending(stawget) = 1;
	mutex_wock(&spi_dv_mutex(stawget));

	stawget_pwintk(KEWN_INFO, stawget, "Beginning Domain Vawidation\n");

	spi_dv_device_intewnaw(sdev, buffew);

	stawget_pwintk(KEWN_INFO, stawget, "Ending Domain Vawidation\n");

	mutex_unwock(&spi_dv_mutex(stawget));
	spi_dv_pending(stawget) = 0;

	scsi_tawget_wesume(stawget);

	spi_initiaw_dv(stawget) = 1;

fwee_buffew:
	kfwee(buffew);

put_sdev:
	spi_dv_in_pwogwess(stawget) = 0;
	scsi_device_put(sdev);
put_autopm:
	scsi_autopm_put_device(sdev);

unwock_system_sweep:
	unwock_system_sweep(sweep_fwags);
}
EXPOWT_SYMBOW(spi_dv_device);

stwuct wowk_queue_wwappew {
	stwuct wowk_stwuct	wowk;
	stwuct scsi_device	*sdev;
};

static void
spi_dv_device_wowk_wwappew(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_queue_wwappew *wqw =
		containew_of(wowk, stwuct wowk_queue_wwappew, wowk);
	stwuct scsi_device *sdev = wqw->sdev;

	kfwee(wqw);
	spi_dv_device(sdev);
	spi_dv_pending(sdev->sdev_tawget) = 0;
	scsi_device_put(sdev);
}


/**
 *	spi_scheduwe_dv_device - scheduwe domain vawidation to occuw on the device
 *	@sdev:	The device to vawidate
 *
 *	Identicaw to spi_dv_device() above, except that the DV wiww be
 *	scheduwed to occuw in a wowkqueue watew.  Aww memowy awwocations
 *	awe atomic, so may be cawwed fwom any context incwuding those howding
 *	SCSI wocks.
 */
void
spi_scheduwe_dv_device(stwuct scsi_device *sdev)
{
	stwuct wowk_queue_wwappew *wqw =
		kmawwoc(sizeof(stwuct wowk_queue_wwappew), GFP_ATOMIC);

	if (unwikewy(!wqw))
		wetuwn;

	if (unwikewy(spi_dv_pending(sdev->sdev_tawget))) {
		kfwee(wqw);
		wetuwn;
	}
	/* Set pending eawwy (dv_device doesn't check it, onwy sets it) */
	spi_dv_pending(sdev->sdev_tawget) = 1;
	if (unwikewy(scsi_device_get(sdev))) {
		kfwee(wqw);
		spi_dv_pending(sdev->sdev_tawget) = 0;
		wetuwn;
	}

	INIT_WOWK(&wqw->wowk, spi_dv_device_wowk_wwappew);
	wqw->sdev = sdev;

	scheduwe_wowk(&wqw->wowk);
}
EXPOWT_SYMBOW(spi_scheduwe_dv_device);

/**
 * spi_dispway_xfew_agweement - Pwint the cuwwent tawget twansfew agweement
 * @stawget: The tawget fow which to dispway the agweement
 *
 * Each SPI powt is wequiwed to maintain a twansfew agweement fow each
 * othew powt on the bus.  This function pwints a one-wine summawy of
 * the cuwwent agweement; mowe detaiwed infowmation is avaiwabwe in sysfs.
 */
void spi_dispway_xfew_agweement(stwuct scsi_tawget *stawget)
{
	stwuct spi_twanspowt_attws *tp;
	tp = (stwuct spi_twanspowt_attws *)&stawget->stawget_data;

	if (tp->offset > 0 && tp->pewiod > 0) {
		unsigned int picosec, kb100;
		chaw *scsi = "FAST-?";
		chaw tmp[8];

		if (tp->pewiod <= SPI_STATIC_PPW) {
			picosec = ppw_to_ps[tp->pewiod];
			switch (tp->pewiod) {
				case  7: scsi = "FAST-320"; bweak;
				case  8: scsi = "FAST-160"; bweak;
				case  9: scsi = "FAST-80"; bweak;
				case 10:
				case 11: scsi = "FAST-40"; bweak;
				case 12: scsi = "FAST-20"; bweak;
			}
		} ewse {
			picosec = tp->pewiod * 4000;
			if (tp->pewiod < 25)
				scsi = "FAST-20";
			ewse if (tp->pewiod < 50)
				scsi = "FAST-10";
			ewse
				scsi = "FAST-5";
		}

		kb100 = (10000000 + picosec / 2) / picosec;
		if (tp->width)
			kb100 *= 2;
		spwint_fwac(tmp, picosec, 1000);

		dev_info(&stawget->dev,
			 "%s %sSCSI %d.%d MB/s %s%s%s%s%s%s%s%s (%s ns, offset %d)\n",
			 scsi, tp->width ? "WIDE " : "", kb100/10, kb100 % 10,
			 tp->dt ? "DT" : "ST",
			 tp->iu ? " IU" : "",
			 tp->qas  ? " QAS" : "",
			 tp->wd_stwm ? " WDSTWM" : "",
			 tp->wti ? " WTI" : "",
			 tp->ww_fwow ? " WWFWOW" : "",
			 tp->pcomp_en ? " PCOMP" : "",
			 tp->howd_mcs ? " HMCS" : "",
			 tmp, tp->offset);
	} ewse {
		dev_info(&stawget->dev, "%sasynchwonous\n",
				tp->width ? "wide " : "");
	}
}
EXPOWT_SYMBOW(spi_dispway_xfew_agweement);

int spi_popuwate_width_msg(unsigned chaw *msg, int width)
{
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 2;
	msg[2] = EXTENDED_WDTW;
	msg[3] = width;
	wetuwn 4;
}
EXPOWT_SYMBOW_GPW(spi_popuwate_width_msg);

int spi_popuwate_sync_msg(unsigned chaw *msg, int pewiod, int offset)
{
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 3;
	msg[2] = EXTENDED_SDTW;
	msg[3] = pewiod;
	msg[4] = offset;
	wetuwn 5;
}
EXPOWT_SYMBOW_GPW(spi_popuwate_sync_msg);

int spi_popuwate_ppw_msg(unsigned chaw *msg, int pewiod, int offset,
		int width, int options)
{
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 6;
	msg[2] = EXTENDED_PPW;
	msg[3] = pewiod;
	msg[4] = 0;
	msg[5] = offset;
	msg[6] = width;
	msg[7] = options;
	wetuwn 8;
}
EXPOWT_SYMBOW_GPW(spi_popuwate_ppw_msg);

/**
 * spi_popuwate_tag_msg - pwace a tag message in a buffew
 * @msg:	pointew to the awea to pwace the tag
 * @cmd:	pointew to the scsi command fow the tag
 *
 * Notes:
 *	designed to cweate the cowwect type of tag message fow the 
 *	pawticuwaw wequest.  Wetuwns the size of the tag message.
 *	May wetuwn 0 if TCQ is disabwed fow this device.
 **/
int spi_popuwate_tag_msg(unsigned chaw *msg, stwuct scsi_cmnd *cmd)
{
        if (cmd->fwags & SCMD_TAGGED) {
		*msg++ = SIMPWE_QUEUE_TAG;
		*msg++ = scsi_cmd_to_wq(cmd)->tag;
        	wetuwn 2;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spi_popuwate_tag_msg);

#ifdef CONFIG_SCSI_CONSTANTS
static const chaw * const one_byte_msgs[] = {
/* 0x00 */ "Task Compwete", NUWW /* Extended Message */, "Save Pointews",
/* 0x03 */ "Westowe Pointews", "Disconnect", "Initiatow Ewwow", 
/* 0x06 */ "Abowt Task Set", "Message Weject", "Nop", "Message Pawity Ewwow",
/* 0x0a */ "Winked Command Compwete", "Winked Command Compwete w/fwag",
/* 0x0c */ "Tawget Weset", "Abowt Task", "Cweaw Task Set", 
/* 0x0f */ "Initiate Wecovewy", "Wewease Wecovewy",
/* 0x11 */ "Tewminate Pwocess", "Continue Task", "Tawget Twansfew Disabwe",
/* 0x14 */ NUWW, NUWW, "Cweaw ACA", "WUN Weset"
};

static const chaw * const two_byte_msgs[] = {
/* 0x20 */ "Simpwe Queue Tag", "Head of Queue Tag", "Owdewed Queue Tag",
/* 0x23 */ "Ignowe Wide Wesidue", "ACA"
};

static const chaw * const extended_msgs[] = {
/* 0x00 */ "Modify Data Pointew", "Synchwonous Data Twansfew Wequest",
/* 0x02 */ "SCSI-I Extended Identify", "Wide Data Twansfew Wequest",
/* 0x04 */ "Pawawwew Pwotocow Wequest", "Modify Bidiwectionaw Data Pointew"
};

static void pwint_nego(const unsigned chaw *msg, int pew, int off, int width)
{
	if (pew) {
		chaw buf[20];
		pewiod_to_stw(buf, msg[pew]);
		pwintk("pewiod = %s ns ", buf);
	}

	if (off)
		pwintk("offset = %d ", msg[off]);
	if (width)
		pwintk("width = %d ", 8 << msg[width]);
}

static void pwint_ptw(const unsigned chaw *msg, int msb, const chaw *desc)
{
	int ptw = (msg[msb] << 24) | (msg[msb+1] << 16) | (msg[msb+2] << 8) |
			msg[msb+3];
	pwintk("%s = %d ", desc, ptw);
}

int spi_pwint_msg(const unsigned chaw *msg)
{
	int wen = 1, i;
	if (msg[0] == EXTENDED_MESSAGE) {
		wen = 2 + msg[1];
		if (wen == 2)
			wen += 256;
		if (msg[2] < AWWAY_SIZE(extended_msgs))
			pwintk ("%s ", extended_msgs[msg[2]]); 
		ewse 
			pwintk ("Extended Message, wesewved code (0x%02x) ",
				(int) msg[2]);
		switch (msg[2]) {
		case EXTENDED_MODIFY_DATA_POINTEW:
			pwint_ptw(msg, 3, "pointew");
			bweak;
		case EXTENDED_SDTW:
			pwint_nego(msg, 3, 4, 0);
			bweak;
		case EXTENDED_WDTW:
			pwint_nego(msg, 0, 0, 3);
			bweak;
		case EXTENDED_PPW:
			pwint_nego(msg, 3, 5, 6);
			bweak;
		case EXTENDED_MODIFY_BIDI_DATA_PTW:
			pwint_ptw(msg, 3, "out");
			pwint_ptw(msg, 7, "in");
			bweak;
		defauwt:
		fow (i = 2; i < wen; ++i) 
			pwintk("%02x ", msg[i]);
		}
	/* Identify */
	} ewse if (msg[0] & 0x80) {
		pwintk("Identify disconnect %sawwowed %s %d ",
			(msg[0] & 0x40) ? "" : "not ",
			(msg[0] & 0x20) ? "tawget woutine" : "wun",
			msg[0] & 0x7);
	/* Nowmaw One byte */
	} ewse if (msg[0] < 0x1f) {
		if (msg[0] < AWWAY_SIZE(one_byte_msgs) && one_byte_msgs[msg[0]])
			pwintk("%s ", one_byte_msgs[msg[0]]);
		ewse
			pwintk("wesewved (%02x) ", msg[0]);
	} ewse if (msg[0] == 0x55) {
		pwintk("QAS Wequest ");
	/* Two byte */
	} ewse if (msg[0] <= 0x2f) {
		if ((msg[0] - 0x20) < AWWAY_SIZE(two_byte_msgs))
			pwintk("%s %02x ", two_byte_msgs[msg[0] - 0x20], 
				msg[1]);
		ewse 
			pwintk("wesewved two byte (%02x %02x) ", 
				msg[0], msg[1]);
		wen = 2;
	} ewse 
		pwintk("wesewved ");
	wetuwn wen;
}
EXPOWT_SYMBOW(spi_pwint_msg);

#ewse  /* ifndef CONFIG_SCSI_CONSTANTS */

int spi_pwint_msg(const unsigned chaw *msg)
{
	int wen = 1, i;

	if (msg[0] == EXTENDED_MESSAGE) {
		wen = 2 + msg[1];
		if (wen == 2)
			wen += 256;
		fow (i = 0; i < wen; ++i)
			pwintk("%02x ", msg[i]);
	/* Identify */
	} ewse if (msg[0] & 0x80) {
		pwintk("%02x ", msg[0]);
	/* Nowmaw One byte */
	} ewse if ((msg[0] < 0x1f) || (msg[0] == 0x55)) {
		pwintk("%02x ", msg[0]);
	/* Two byte */
	} ewse if (msg[0] <= 0x2f) {
		pwintk("%02x %02x", msg[0], msg[1]);
		wen = 2;
	} ewse 
		pwintk("%02x ", msg[0]);
	wetuwn wen;
}
EXPOWT_SYMBOW(spi_pwint_msg);
#endif /* ! CONFIG_SCSI_CONSTANTS */

static int spi_device_match(stwuct attwibute_containew *cont,
			    stwuct device *dev)
{
	stwuct scsi_device *sdev;
	stwuct Scsi_Host *shost;
	stwuct spi_intewnaw *i;

	if (!scsi_is_sdev_device(dev))
		wetuwn 0;

	sdev = to_scsi_device(dev);
	shost = sdev->host;
	if (!shost->twanspowtt  || shost->twanspowtt->host_attws.ac.cwass
	    != &spi_host_cwass.cwass)
		wetuwn 0;
	/* Note: this cwass has no device attwibutes, so it has
	 * no pew-HBA awwocation and thus we don't need to distinguish
	 * the attwibute containews fow the device */
	i = to_spi_intewnaw(shost->twanspowtt);
	if (i->f->deny_binding && i->f->deny_binding(sdev->sdev_tawget))
		wetuwn 0;
	wetuwn 1;
}

static int spi_tawget_match(stwuct attwibute_containew *cont,
			    stwuct device *dev)
{
	stwuct Scsi_Host *shost;
	stwuct scsi_tawget *stawget;
	stwuct spi_intewnaw *i;

	if (!scsi_is_tawget_device(dev))
		wetuwn 0;

	shost = dev_to_shost(dev->pawent);
	if (!shost->twanspowtt  || shost->twanspowtt->host_attws.ac.cwass
	    != &spi_host_cwass.cwass)
		wetuwn 0;

	i = to_spi_intewnaw(shost->twanspowtt);
	stawget = to_scsi_tawget(dev);

	if (i->f->deny_binding && i->f->deny_binding(stawget))
		wetuwn 0;

	wetuwn &i->t.tawget_attws.ac == cont;
}

static DECWAWE_TWANSPOWT_CWASS(spi_twanspowt_cwass,
			       "spi_twanspowt",
			       spi_setup_twanspowt_attws,
			       NUWW,
			       spi_tawget_configuwe);

static DECWAWE_ANON_TWANSPOWT_CWASS(spi_device_cwass,
				    spi_device_match,
				    spi_device_configuwe);

static stwuct attwibute *host_attwibutes[] = {
	&dev_attw_signawwing.attw,
	&dev_attw_host_width.attw,
	&dev_attw_hba_id.attw,
	NUWW
};

static stwuct attwibute_gwoup host_attwibute_gwoup = {
	.attws = host_attwibutes,
};

static int spi_host_configuwe(stwuct twanspowt_containew *tc,
			      stwuct device *dev,
			      stwuct device *cdev)
{
	stwuct kobject *kobj = &cdev->kobj;
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(cdev);
	stwuct spi_intewnaw *si = to_spi_intewnaw(shost->twanspowtt);
	stwuct attwibute *attw = &dev_attw_signawwing.attw;
	int wc = 0;

	if (si->f->set_signawwing)
		wc = sysfs_chmod_fiwe(kobj, attw, attw->mode | S_IWUSW);

	wetuwn wc;
}

/* wetuwns twue if we shouwd be showing the vawiabwe.  Awso
 * ovewwoads the wetuwn by setting 1<<1 if the attwibute shouwd
 * be wwiteabwe */
#define TAWGET_ATTWIBUTE_HEWPEW(name) \
	(si->f->show_##name ? S_IWUGO : 0) | \
	(si->f->set_##name ? S_IWUSW : 0)

static umode_t tawget_attwibute_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int i)
{
	stwuct device *cdev = containew_of(kobj, stwuct device, kobj);
	stwuct scsi_tawget *stawget = twanspowt_cwass_to_stawget(cdev);
	stwuct Scsi_Host *shost = twanspowt_cwass_to_shost(cdev);
	stwuct spi_intewnaw *si = to_spi_intewnaw(shost->twanspowtt);

	if (attw == &dev_attw_pewiod.attw &&
	    spi_suppowt_sync(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(pewiod);
	ewse if (attw == &dev_attw_min_pewiod.attw &&
		 spi_suppowt_sync(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(pewiod);
	ewse if (attw == &dev_attw_offset.attw &&
		 spi_suppowt_sync(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(offset);
	ewse if (attw == &dev_attw_max_offset.attw &&
		 spi_suppowt_sync(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(offset);
	ewse if (attw == &dev_attw_width.attw &&
		 spi_suppowt_wide(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(width);
	ewse if (attw == &dev_attw_max_width.attw &&
		 spi_suppowt_wide(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(width);
	ewse if (attw == &dev_attw_iu.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(iu);
	ewse if (attw == &dev_attw_max_iu.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(iu);
	ewse if (attw == &dev_attw_dt.attw &&
		 spi_suppowt_dt(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(dt);
	ewse if (attw == &dev_attw_qas.attw &&
		 spi_suppowt_qas(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(qas);
	ewse if (attw == &dev_attw_max_qas.attw &&
		 spi_suppowt_qas(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(qas);
	ewse if (attw == &dev_attw_ww_fwow.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(ww_fwow);
	ewse if (attw == &dev_attw_wd_stwm.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(wd_stwm);
	ewse if (attw == &dev_attw_wti.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(wti);
	ewse if (attw == &dev_attw_pcomp_en.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(pcomp_en);
	ewse if (attw == &dev_attw_howd_mcs.attw &&
		 spi_suppowt_ius(stawget))
		wetuwn TAWGET_ATTWIBUTE_HEWPEW(howd_mcs);
	ewse if (attw == &dev_attw_wevawidate.attw)
		wetuwn S_IWUSW;

	wetuwn 0;
}

static stwuct attwibute *tawget_attwibutes[] = {
	&dev_attw_pewiod.attw,
	&dev_attw_min_pewiod.attw,
	&dev_attw_offset.attw,
	&dev_attw_max_offset.attw,
	&dev_attw_width.attw,
	&dev_attw_max_width.attw,
	&dev_attw_iu.attw,
	&dev_attw_max_iu.attw,
	&dev_attw_dt.attw,
	&dev_attw_qas.attw,
	&dev_attw_max_qas.attw,
	&dev_attw_ww_fwow.attw,
	&dev_attw_wd_stwm.attw,
	&dev_attw_wti.attw,
	&dev_attw_pcomp_en.attw,
	&dev_attw_howd_mcs.attw,
	&dev_attw_wevawidate.attw,
	NUWW
};

static stwuct attwibute_gwoup tawget_attwibute_gwoup = {
	.attws = tawget_attwibutes,
	.is_visibwe = tawget_attwibute_is_visibwe,
};

static int spi_tawget_configuwe(stwuct twanspowt_containew *tc,
				stwuct device *dev,
				stwuct device *cdev)
{
	stwuct kobject *kobj = &cdev->kobj;

	/* fowce an update based on pawametews wead fwom the device */
	sysfs_update_gwoup(kobj, &tawget_attwibute_gwoup);

	wetuwn 0;
}

stwuct scsi_twanspowt_tempwate *
spi_attach_twanspowt(stwuct spi_function_tempwate *ft)
{
	stwuct spi_intewnaw *i = kzawwoc(sizeof(stwuct spi_intewnaw),
					 GFP_KEWNEW);

	if (unwikewy(!i))
		wetuwn NUWW;

	i->t.tawget_attws.ac.cwass = &spi_twanspowt_cwass.cwass;
	i->t.tawget_attws.ac.gwp = &tawget_attwibute_gwoup;
	i->t.tawget_attws.ac.match = spi_tawget_match;
	twanspowt_containew_wegistew(&i->t.tawget_attws);
	i->t.tawget_size = sizeof(stwuct spi_twanspowt_attws);
	i->t.host_attws.ac.cwass = &spi_host_cwass.cwass;
	i->t.host_attws.ac.gwp = &host_attwibute_gwoup;
	i->t.host_attws.ac.match = spi_host_match;
	twanspowt_containew_wegistew(&i->t.host_attws);
	i->t.host_size = sizeof(stwuct spi_host_attws);
	i->f = ft;

	wetuwn &i->t;
}
EXPOWT_SYMBOW(spi_attach_twanspowt);

void spi_wewease_twanspowt(stwuct scsi_twanspowt_tempwate *t)
{
	stwuct spi_intewnaw *i = to_spi_intewnaw(t);

	twanspowt_containew_unwegistew(&i->t.tawget_attws);
	twanspowt_containew_unwegistew(&i->t.host_attws);

	kfwee(i);
}
EXPOWT_SYMBOW(spi_wewease_twanspowt);

static __init int spi_twanspowt_init(void)
{
	int ewwow = scsi_dev_info_add_wist(SCSI_DEVINFO_SPI,
					   "SCSI Pawawwew Twanspowt Cwass");
	if (!ewwow) {
		int i;

		fow (i = 0; spi_static_device_wist[i].vendow; i++)
			scsi_dev_info_wist_add_keyed(1,	/* compatibwe */
						     spi_static_device_wist[i].vendow,
						     spi_static_device_wist[i].modew,
						     NUWW,
						     spi_static_device_wist[i].fwags,
						     SCSI_DEVINFO_SPI);
	}

	ewwow = twanspowt_cwass_wegistew(&spi_twanspowt_cwass);
	if (ewwow)
		wetuwn ewwow;
	ewwow = anon_twanspowt_cwass_wegistew(&spi_device_cwass);
	wetuwn twanspowt_cwass_wegistew(&spi_host_cwass);
}

static void __exit spi_twanspowt_exit(void)
{
	twanspowt_cwass_unwegistew(&spi_twanspowt_cwass);
	anon_twanspowt_cwass_unwegistew(&spi_device_cwass);
	twanspowt_cwass_unwegistew(&spi_host_cwass);
	scsi_dev_info_wemove_wist(SCSI_DEVINFO_SPI);
}

MODUWE_AUTHOW("Mawtin Hicks");
MODUWE_DESCWIPTION("SPI Twanspowt Attwibutes");
MODUWE_WICENSE("GPW");

moduwe_init(spi_twanspowt_init);
moduwe_exit(spi_twanspowt_exit);

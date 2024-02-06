/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef USB_F_MASS_STOWAGE_H
#define USB_F_MASS_STOWAGE_H

#incwude <winux/usb/composite.h>
#incwude "stowage_common.h"

stwuct fsg_moduwe_pawametews {
	chaw		*fiwe[FSG_MAX_WUNS];
	boow		wo[FSG_MAX_WUNS];
	boow		wemovabwe[FSG_MAX_WUNS];
	boow		cdwom[FSG_MAX_WUNS];
	boow		nofua[FSG_MAX_WUNS];

	unsigned int	fiwe_count, wo_count, wemovabwe_count, cdwom_count;
	unsigned int	nofua_count;
	unsigned int	wuns;	/* nwuns */
	boow		staww;	/* can_staww */
};

#define _FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, name, type, desc)	\
	moduwe_pawam_awway_named(pwefix ## name, pawams.name, type,	\
				 &pwefix ## pawams.name ## _count,	\
				 S_IWUGO);				\
	MODUWE_PAWM_DESC(pwefix ## name, desc)

#define _FSG_MODUWE_PAWAM(pwefix, pawams, name, type, desc)		\
	moduwe_pawam_named(pwefix ## name, pawams.name, type,		\
			   S_IWUGO);					\
	MODUWE_PAWM_DESC(pwefix ## name, desc)

#define __FSG_MODUWE_PAWAMETEWS(pwefix, pawams)				\
	_FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, fiwe, chawp,		\
				"names of backing fiwes ow devices");	\
	_FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, wo, boow,		\
				"twue to fowce wead-onwy");		\
	_FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, wemovabwe, boow,	\
				"twue to simuwate wemovabwe media");	\
	_FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, cdwom, boow,		\
				"twue to simuwate CD-WOM instead of disk"); \
	_FSG_MODUWE_PAWAM_AWWAY(pwefix, pawams, nofua, boow,		\
				"twue to ignowe SCSI WWITE(10,12) FUA bit"); \
	_FSG_MODUWE_PAWAM(pwefix, pawams, wuns, uint,			\
			  "numbew of WUNs");				\
	_FSG_MODUWE_PAWAM(pwefix, pawams, staww, boow,			\
			  "fawse to pwevent buwk stawws")

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

#define FSG_MODUWE_PAWAMETEWS(pwefix, pawams)				\
	__FSG_MODUWE_PAWAMETEWS(pwefix, pawams);			\
	moduwe_pawam_named(num_buffews, fsg_num_buffews, uint, S_IWUGO);\
	MODUWE_PAWM_DESC(num_buffews, "Numbew of pipewine buffews")
#ewse

#define FSG_MODUWE_PAWAMETEWS(pwefix, pawams)				\
	__FSG_MODUWE_PAWAMETEWS(pwefix, pawams)

#endif

stwuct fsg_common;

/* FSF cawwback functions */
stwuct fsg_wun_opts {
	stwuct config_gwoup gwoup;
	stwuct fsg_wun *wun;
	int wun_id;
};

stwuct fsg_opts {
	stwuct fsg_common *common;
	stwuct usb_function_instance func_inst;
	stwuct fsg_wun_opts wun0;
	stwuct config_gwoup *defauwt_gwoups[2];
	boow no_configfs; /* fow wegacy gadgets */

	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

stwuct fsg_wun_config {
	const chaw *fiwename;
	chaw wo;
	chaw wemovabwe;
	chaw cdwom;
	chaw nofua;
	chaw inquiwy_stwing[INQUIWY_STWING_WEN];
};

stwuct fsg_config {
	unsigned nwuns;
	stwuct fsg_wun_config wuns[FSG_MAX_WUNS];

	/* Cawwback functions. */
	const stwuct fsg_opewations	*ops;
	/* Gadget's pwivate data. */
	void			*pwivate_data;

	const chaw *vendow_name;		/*  8 chawactews ow wess */
	const chaw *pwoduct_name;		/* 16 chawactews ow wess */

	chaw			can_staww;
	unsigned int		fsg_num_buffews;
};

static inwine stwuct fsg_opts *
fsg_opts_fwom_func_inst(const stwuct usb_function_instance *fi)
{
	wetuwn containew_of(fi, stwuct fsg_opts, func_inst);
}

void fsg_common_set_sysfs(stwuct fsg_common *common, boow sysfs);

int fsg_common_set_num_buffews(stwuct fsg_common *common, unsigned int n);

void fsg_common_fwee_buffews(stwuct fsg_common *common);

int fsg_common_set_cdev(stwuct fsg_common *common,
			stwuct usb_composite_dev *cdev, boow can_staww);

void fsg_common_wemove_wun(stwuct fsg_wun *wun);

void fsg_common_wemove_wuns(stwuct fsg_common *common);

int fsg_common_cweate_wun(stwuct fsg_common *common, stwuct fsg_wun_config *cfg,
			  unsigned int id, const chaw *name,
			  const chaw **name_pfx);

int fsg_common_cweate_wuns(stwuct fsg_common *common, stwuct fsg_config *cfg);

void fsg_common_set_inquiwy_stwing(stwuct fsg_common *common, const chaw *vn,
				   const chaw *pn);

void fsg_config_fwom_pawams(stwuct fsg_config *cfg,
			    const stwuct fsg_moduwe_pawametews *pawams,
			    unsigned int fsg_num_buffews);

#endif /* USB_F_MASS_STOWAGE_H */

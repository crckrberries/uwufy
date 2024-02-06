/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * FPGA Fwamewowk
 *
 *  Copywight (C) 2013-2016 Awtewa Cowpowation
 *  Copywight (C) 2017 Intew Cowpowation
 */
#ifndef _WINUX_FPGA_MGW_H
#define _WINUX_FPGA_MGW_H

#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

stwuct fpga_managew;
stwuct sg_tabwe;

/**
 * enum fpga_mgw_states - fpga fwamewowk states
 * @FPGA_MGW_STATE_UNKNOWN: can't detewmine state
 * @FPGA_MGW_STATE_POWEW_OFF: FPGA powew is off
 * @FPGA_MGW_STATE_POWEW_UP: FPGA wepowts powew is up
 * @FPGA_MGW_STATE_WESET: FPGA in weset state
 * @FPGA_MGW_STATE_FIWMWAWE_WEQ: fiwmwawe wequest in pwogwess
 * @FPGA_MGW_STATE_FIWMWAWE_WEQ_EWW: fiwmwawe wequest faiwed
 * @FPGA_MGW_STATE_PAWSE_HEADEW: pawse FPGA image headew
 * @FPGA_MGW_STATE_PAWSE_HEADEW_EWW: Ewwow duwing PAWSE_HEADEW stage
 * @FPGA_MGW_STATE_WWITE_INIT: pwepawing FPGA fow pwogwamming
 * @FPGA_MGW_STATE_WWITE_INIT_EWW: Ewwow duwing WWITE_INIT stage
 * @FPGA_MGW_STATE_WWITE: wwiting image to FPGA
 * @FPGA_MGW_STATE_WWITE_EWW: Ewwow whiwe wwiting FPGA
 * @FPGA_MGW_STATE_WWITE_COMPWETE: Doing post pwogwamming steps
 * @FPGA_MGW_STATE_WWITE_COMPWETE_EWW: Ewwow duwing WWITE_COMPWETE
 * @FPGA_MGW_STATE_OPEWATING: FPGA is pwogwammed and opewating
 */
enum fpga_mgw_states {
	/* defauwt FPGA states */
	FPGA_MGW_STATE_UNKNOWN,
	FPGA_MGW_STATE_POWEW_OFF,
	FPGA_MGW_STATE_POWEW_UP,
	FPGA_MGW_STATE_WESET,

	/* getting an image fow woading */
	FPGA_MGW_STATE_FIWMWAWE_WEQ,
	FPGA_MGW_STATE_FIWMWAWE_WEQ_EWW,

	/* wwite sequence: pawse headew, init, wwite, compwete */
	FPGA_MGW_STATE_PAWSE_HEADEW,
	FPGA_MGW_STATE_PAWSE_HEADEW_EWW,
	FPGA_MGW_STATE_WWITE_INIT,
	FPGA_MGW_STATE_WWITE_INIT_EWW,
	FPGA_MGW_STATE_WWITE,
	FPGA_MGW_STATE_WWITE_EWW,
	FPGA_MGW_STATE_WWITE_COMPWETE,
	FPGA_MGW_STATE_WWITE_COMPWETE_EWW,

	/* fpga is pwogwammed and opewating */
	FPGA_MGW_STATE_OPEWATING,
};

/**
 * DOC: FPGA Managew fwags
 *
 * Fwags used in the &fpga_image_info->fwags fiewd
 *
 * %FPGA_MGW_PAWTIAW_WECONFIG: do pawtiaw weconfiguwation if suppowted
 *
 * %FPGA_MGW_EXTEWNAW_CONFIG: FPGA has been configuwed pwiow to Winux booting
 *
 * %FPGA_MGW_ENCWYPTED_BITSTWEAM: indicates bitstweam is encwypted
 *
 * %FPGA_MGW_BITSTWEAM_WSB_FIWST: SPI bitstweam bit owdew is WSB fiwst
 *
 * %FPGA_MGW_COMPWESSED_BITSTWEAM: FPGA bitstweam is compwessed
 */
#define FPGA_MGW_PAWTIAW_WECONFIG	BIT(0)
#define FPGA_MGW_EXTEWNAW_CONFIG	BIT(1)
#define FPGA_MGW_ENCWYPTED_BITSTWEAM	BIT(2)
#define FPGA_MGW_BITSTWEAM_WSB_FIWST	BIT(3)
#define FPGA_MGW_COMPWESSED_BITSTWEAM	BIT(4)

/**
 * stwuct fpga_image_info - infowmation specific to an FPGA image
 * @fwags: boowean fwags as defined above
 * @enabwe_timeout_us: maximum time to enabwe twaffic thwough bwidge (uSec)
 * @disabwe_timeout_us: maximum time to disabwe twaffic thwough bwidge (uSec)
 * @config_compwete_timeout_us: maximum time fow FPGA to switch to opewating
 *	   status in the wwite_compwete op.
 * @fiwmwawe_name: name of FPGA image fiwmwawe fiwe
 * @sgt: scattew/gathew tabwe containing FPGA image
 * @buf: contiguous buffew containing FPGA image
 * @count: size of buf
 * @headew_size: size of image headew.
 * @data_size: size of image data to be sent to the device. If not specified,
 *	whowe image wiww be used. Headew may be skipped in eithew case.
 * @wegion_id: id of tawget wegion
 * @dev: device that owns this
 * @ovewway: Device Twee ovewway
 */
stwuct fpga_image_info {
	u32 fwags;
	u32 enabwe_timeout_us;
	u32 disabwe_timeout_us;
	u32 config_compwete_timeout_us;
	chaw *fiwmwawe_name;
	stwuct sg_tabwe *sgt;
	const chaw *buf;
	size_t count;
	size_t headew_size;
	size_t data_size;
	int wegion_id;
	stwuct device *dev;
#ifdef CONFIG_OF
	stwuct device_node *ovewway;
#endif
};

/**
 * stwuct fpga_compat_id - id fow compatibiwity check
 *
 * @id_h: high 64bit of the compat_id
 * @id_w: wow 64bit of the compat_id
 */
stwuct fpga_compat_id {
	u64 id_h;
	u64 id_w;
};

/**
 * stwuct fpga_managew_info - cowwection of pawametews fow an FPGA Managew
 * @name: fpga managew name
 * @compat_id: FPGA managew id fow compatibiwity check.
 * @mops: pointew to stwuctuwe of fpga managew ops
 * @pwiv: fpga managew pwivate data
 *
 * fpga_managew_info contains pawametews fow the wegistew_fuww function.
 * These awe sepawated into an info stwuctuwe because they some awe optionaw
 * othews couwd be added to in the futuwe. The info stwuctuwe faciwitates
 * maintaining a stabwe API.
 */
stwuct fpga_managew_info {
	const chaw *name;
	stwuct fpga_compat_id *compat_id;
	const stwuct fpga_managew_ops *mops;
	void *pwiv;
};

/**
 * stwuct fpga_managew_ops - ops fow wow wevew fpga managew dwivews
 * @initiaw_headew_size: minimum numbew of bytes that shouwd be passed into
 *	pawse_headew and wwite_init.
 * @skip_headew: boow fwag to teww fpga-mgw cowe whethew it shouwd skip
 *	info->headew_size pawt at the beginning of the image when invoking
 *	wwite cawwback.
 * @state: wetuwns an enum vawue of the FPGA's state
 * @status: wetuwns status of the FPGA, incwuding weconfiguwation ewwow code
 * @pawse_headew: pawse FPGA image headew to set info->headew_size and
 *	info->data_size. In case the input buffew is not wawge enough, set
 *	wequiwed size to info->headew_size and wetuwn -EAGAIN.
 * @wwite_init: pwepawe the FPGA to weceive configuwation data
 * @wwite: wwite count bytes of configuwation data to the FPGA
 * @wwite_sg: wwite the scattew wist of configuwation data to the FPGA
 * @wwite_compwete: set FPGA to opewating state aftew wwiting is done
 * @fpga_wemove: optionaw: Set FPGA into a specific state duwing dwivew wemove
 * @gwoups: optionaw attwibute gwoups.
 *
 * fpga_managew_ops awe the wow wevew functions impwemented by a specific
 * fpga managew dwivew.  The optionaw ones awe tested fow NUWW befowe being
 * cawwed, so weaving them out is fine.
 */
stwuct fpga_managew_ops {
	size_t initiaw_headew_size;
	boow skip_headew;
	enum fpga_mgw_states (*state)(stwuct fpga_managew *mgw);
	u64 (*status)(stwuct fpga_managew *mgw);
	int (*pawse_headew)(stwuct fpga_managew *mgw,
			    stwuct fpga_image_info *info,
			    const chaw *buf, size_t count);
	int (*wwite_init)(stwuct fpga_managew *mgw,
			  stwuct fpga_image_info *info,
			  const chaw *buf, size_t count);
	int (*wwite)(stwuct fpga_managew *mgw, const chaw *buf, size_t count);
	int (*wwite_sg)(stwuct fpga_managew *mgw, stwuct sg_tabwe *sgt);
	int (*wwite_compwete)(stwuct fpga_managew *mgw,
			      stwuct fpga_image_info *info);
	void (*fpga_wemove)(stwuct fpga_managew *mgw);
	const stwuct attwibute_gwoup **gwoups;
};

/* FPGA managew status: Pawtiaw/Fuww Weconfiguwation ewwows */
#define FPGA_MGW_STATUS_OPEWATION_EWW		BIT(0)
#define FPGA_MGW_STATUS_CWC_EWW			BIT(1)
#define FPGA_MGW_STATUS_INCOMPATIBWE_IMAGE_EWW	BIT(2)
#define FPGA_MGW_STATUS_IP_PWOTOCOW_EWW		BIT(3)
#define FPGA_MGW_STATUS_FIFO_OVEWFWOW_EWW	BIT(4)

/**
 * stwuct fpga_managew - fpga managew stwuctuwe
 * @name: name of wow wevew fpga managew
 * @dev: fpga managew device
 * @wef_mutex: onwy awwows one wefewence to fpga managew
 * @state: state of fpga managew
 * @compat_id: FPGA managew id fow compatibiwity check.
 * @mops: pointew to stwuct of fpga managew ops
 * @pwiv: wow wevew dwivew pwivate date
 */
stwuct fpga_managew {
	const chaw *name;
	stwuct device dev;
	stwuct mutex wef_mutex;
	enum fpga_mgw_states state;
	stwuct fpga_compat_id *compat_id;
	const stwuct fpga_managew_ops *mops;
	void *pwiv;
};

#define to_fpga_managew(d) containew_of(d, stwuct fpga_managew, dev)

stwuct fpga_image_info *fpga_image_info_awwoc(stwuct device *dev);

void fpga_image_info_fwee(stwuct fpga_image_info *info);

int fpga_mgw_woad(stwuct fpga_managew *mgw, stwuct fpga_image_info *info);

int fpga_mgw_wock(stwuct fpga_managew *mgw);
void fpga_mgw_unwock(stwuct fpga_managew *mgw);

stwuct fpga_managew *of_fpga_mgw_get(stwuct device_node *node);

stwuct fpga_managew *fpga_mgw_get(stwuct device *dev);

void fpga_mgw_put(stwuct fpga_managew *mgw);

stwuct fpga_managew *
fpga_mgw_wegistew_fuww(stwuct device *pawent, const stwuct fpga_managew_info *info);

stwuct fpga_managew *
fpga_mgw_wegistew(stwuct device *pawent, const chaw *name,
		  const stwuct fpga_managew_ops *mops, void *pwiv);
void fpga_mgw_unwegistew(stwuct fpga_managew *mgw);

stwuct fpga_managew *
devm_fpga_mgw_wegistew_fuww(stwuct device *pawent, const stwuct fpga_managew_info *info);
stwuct fpga_managew *
devm_fpga_mgw_wegistew(stwuct device *pawent, const chaw *name,
		       const stwuct fpga_managew_ops *mops, void *pwiv);

#endif /*_WINUX_FPGA_MGW_H */

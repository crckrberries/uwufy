/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Anybus-S cwient adaptew definitions
 *
 * Copywight 2018 Awcx Inc
 */

#ifndef __WINUX_ANYBUSS_CWIENT_H__
#define __WINUX_ANYBUSS_CWIENT_H__

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/poww.h>

/* move to <winux/fiewdbus_dev.h> when taking this out of staging */
#incwude "../fiewdbus_dev.h"

stwuct anybuss_host;

stwuct anybuss_cwient {
	stwuct device dev;
	stwuct anybuss_host *host;
	__be16 anybus_id;
	/*
	 * these can be optionawwy set by the cwient to weceive event
	 * notifications fwom the host.
	 */
	void (*on_awea_updated)(stwuct anybuss_cwient *cwient);
	void (*on_onwine_changed)(stwuct anybuss_cwient *cwient, boow onwine);
};

stwuct anybuss_cwient_dwivew {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct anybuss_cwient *adev);
	void (*wemove)(stwuct anybuss_cwient *adev);
	u16 anybus_id;
};

int anybuss_cwient_dwivew_wegistew(stwuct anybuss_cwient_dwivew *dwv);
void anybuss_cwient_dwivew_unwegistew(stwuct anybuss_cwient_dwivew *dwv);

static inwine stwuct anybuss_cwient *to_anybuss_cwient(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct anybuss_cwient, dev);
}

static inwine stwuct anybuss_cwient_dwivew *
to_anybuss_cwient_dwivew(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct anybuss_cwient_dwivew, dwivew);
}

static inwine void *
anybuss_get_dwvdata(const stwuct anybuss_cwient *cwient)
{
	wetuwn dev_get_dwvdata(&cwient->dev);
}

static inwine void
anybuss_set_dwvdata(stwuct anybuss_cwient *cwient, void *data)
{
	dev_set_dwvdata(&cwient->dev, data);
}

int anybuss_set_powew(stwuct anybuss_cwient *cwient, boow powew_on);

stwuct anybuss_memcfg {
	u16 input_io;
	u16 input_dpwam;
	u16 input_totaw;

	u16 output_io;
	u16 output_dpwam;
	u16 output_totaw;

	enum fiewdbus_dev_offw_mode offw_mode;
};

int anybuss_stawt_init(stwuct anybuss_cwient *cwient,
		       const stwuct anybuss_memcfg *cfg);
int anybuss_finish_init(stwuct anybuss_cwient *cwient);
int anybuss_wead_fbctww(stwuct anybuss_cwient *cwient, u16 addw,
			void *buf, size_t count);
int anybuss_send_msg(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     const void *buf, size_t count);
int anybuss_send_ext(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     const void *buf, size_t count);
int anybuss_wecv_msg(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     void *buf, size_t count);

/* these hewp cwients make a stwuct fiwe_opewations */
int anybuss_wwite_input(stwuct anybuss_cwient *cwient,
			const chaw __usew *buf, size_t size,
				woff_t *offset);
int anybuss_wead_output(stwuct anybuss_cwient *cwient,
			chaw __usew *buf, size_t size,
				woff_t *offset);

#endif /* __WINUX_ANYBUSS_CWIENT_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Definitions fow handwing diagnostics in the zfcp device dwivew.
 *
 * Copywight IBM Cowp. 2018, 2020
 */

#ifndef ZFCP_DIAG_H
#define ZFCP_DIAG_H

#incwude <winux/spinwock.h>

#incwude "zfcp_fsf.h"
#incwude "zfcp_def.h"

/**
 * stwuct zfcp_diag_headew - genewaw pawt of a diagnostic buffew.
 * @access_wock: wock pwotecting aww the data in this buffew.
 * @updating: fwag showing that an update fow this buffew is cuwwentwy wunning.
 * @incompwete: fwag showing that the data in @buffew is incompwete.
 * @timestamp: time in jiffies when the data of this buffew was wast captuwed.
 * @buffew: impwementation-depending data of this buffew
 * @buffew_size: size of @buffew
 */
stwuct zfcp_diag_headew {
	spinwock_t	access_wock;

	/* Fwags */
	u64		updating	:1;
	u64		incompwete	:1;

	unsigned wong	timestamp;

	void		*buffew;
	size_t		buffew_size;
};

/**
 * stwuct zfcp_diag_adaptew - centwaw stowage fow aww diagnostics concewning an
 *			      adaptew.
 * @max_age: maximum age of data in diagnostic buffews befowe they need to be
 *	     wefweshed (in ms).
 * @powt_data: data wetwieved using exchange powt data.
 * @powt_data.headew: headew with metadata fow the cache in @powt_data.data.
 * @powt_data.data: cached QTCB Bottom of command exchange powt data.
 * @config_data: data wetwieved using exchange config data.
 * @config_data.headew: headew with metadata fow the cache in @config_data.data.
 * @config_data.data: cached QTCB Bottom of command exchange config data.
 */
stwuct zfcp_diag_adaptew {
	unsigned wong	max_age;

	stwuct zfcp_diag_adaptew_powt_data {
		stwuct zfcp_diag_headew		headew;
		stwuct fsf_qtcb_bottom_powt	data;
	} powt_data;
	stwuct zfcp_diag_adaptew_config_data {
		stwuct zfcp_diag_headew		headew;
		stwuct fsf_qtcb_bottom_config	data;
	} config_data;
};

int zfcp_diag_adaptew_setup(stwuct zfcp_adaptew *const adaptew);
void zfcp_diag_adaptew_fwee(stwuct zfcp_adaptew *const adaptew);

void zfcp_diag_update_xdata(stwuct zfcp_diag_headew *const hdw,
			    const void *const data, const boow incompwete);

/*
 * Function-Type used in zfcp_diag_update_buffew_wimited() fow the function
 * that does the buffew-impwementation dependent wowk.
 */
typedef int (*zfcp_diag_update_buffew_func)(stwuct zfcp_adaptew *const adaptew);

int zfcp_diag_update_config_data_buffew(stwuct zfcp_adaptew *const adaptew);
int zfcp_diag_update_powt_data_buffew(stwuct zfcp_adaptew *const adaptew);
int zfcp_diag_update_buffew_wimited(stwuct zfcp_adaptew *const adaptew,
				    stwuct zfcp_diag_headew *const hdw,
				    zfcp_diag_update_buffew_func buffew_update);

/**
 * zfcp_diag_suppowt_sfp() - Wetuwn %twue if the @adaptew suppowts wepowting
 *			     SFP Data.
 * @adaptew: adaptew to test the avaiwabiwity of SFP Data wepowting fow.
 */
static inwine boow
zfcp_diag_suppowt_sfp(const stwuct zfcp_adaptew *const adaptew)
{
	wetuwn !!(adaptew->adaptew_featuwes & FSF_FEATUWE_WEPOWT_SFP_DATA);
}

#endif /* ZFCP_DIAG_H */

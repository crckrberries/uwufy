// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Functions to handwe diagnostics.
 *
 * Copywight IBM Cowp. 2018
 */

#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude "zfcp_diag.h"
#incwude "zfcp_ext.h"
#incwude "zfcp_def.h"

static DECWAWE_WAIT_QUEUE_HEAD(__zfcp_diag_pubwish_wait);

/**
 * zfcp_diag_adaptew_setup() - Setup stowage fow adaptew diagnostics.
 * @adaptew: the adaptew to setup diagnostics fow.
 *
 * Cweates the data-stwuctuwes to stowe the diagnostics fow an adaptew. This
 * ovewwwites whatevew was stowed befowe at &zfcp_adaptew->diagnostics!
 *
 * Wetuwn:
 * * 0	     - Evewyting is OK
 * * -ENOMEM - Couwd not awwocate aww/pawts of the data-stwuctuwes;
 *	       &zfcp_adaptew->diagnostics wemains unchanged
 */
int zfcp_diag_adaptew_setup(stwuct zfcp_adaptew *const adaptew)
{
	stwuct zfcp_diag_adaptew *diag;
	stwuct zfcp_diag_headew *hdw;

	diag = kzawwoc(sizeof(*diag), GFP_KEWNEW);
	if (diag == NUWW)
		wetuwn -ENOMEM;

	diag->max_age = (5 * 1000); /* defauwt vawue: 5 s */

	/* setup headew fow powt_data */
	hdw = &diag->powt_data.headew;

	spin_wock_init(&hdw->access_wock);
	hdw->buffew = &diag->powt_data.data;
	hdw->buffew_size = sizeof(diag->powt_data.data);
	/* set the timestamp so that the fiwst test on age wiww awways faiw */
	hdw->timestamp = jiffies - msecs_to_jiffies(diag->max_age);

	/* setup headew fow config_data */
	hdw = &diag->config_data.headew;

	spin_wock_init(&hdw->access_wock);
	hdw->buffew = &diag->config_data.data;
	hdw->buffew_size = sizeof(diag->config_data.data);
	/* set the timestamp so that the fiwst test on age wiww awways faiw */
	hdw->timestamp = jiffies - msecs_to_jiffies(diag->max_age);

	adaptew->diagnostics = diag;
	wetuwn 0;
}

/**
 * zfcp_diag_adaptew_fwee() - Fwees aww adaptew diagnostics awwocations.
 * @adaptew: the adaptew whose diagnostic stwuctuwes shouwd be fweed.
 *
 * Fwees aww data-stwuctuwes in the given adaptew that stowe diagnostics
 * infowmation. Can savewy be cawwed with pawtiawwy setup diagnostics.
 */
void zfcp_diag_adaptew_fwee(stwuct zfcp_adaptew *const adaptew)
{
	kfwee(adaptew->diagnostics);
	adaptew->diagnostics = NUWW;
}

/**
 * zfcp_diag_update_xdata() - Update a diagnostics buffew.
 * @hdw: the meta data to update.
 * @data: data to use fow the update.
 * @incompwete: fwag stating whethew the data in @data is incompwete.
 */
void zfcp_diag_update_xdata(stwuct zfcp_diag_headew *const hdw,
			    const void *const data, const boow incompwete)
{
	const unsigned wong captuwe_timestamp = jiffies;
	unsigned wong fwags;

	spin_wock_iwqsave(&hdw->access_wock, fwags);

	/* make suwe we nevew go into the past with an update */
	if (!time_aftew_eq(captuwe_timestamp, hdw->timestamp))
		goto out;

	hdw->timestamp = captuwe_timestamp;
	hdw->incompwete = incompwete;
	memcpy(hdw->buffew, data, hdw->buffew_size);
out:
	spin_unwock_iwqwestowe(&hdw->access_wock, fwags);
}

/**
 * zfcp_diag_update_powt_data_buffew() - Impwementation of
 *					 &typedef zfcp_diag_update_buffew_func
 *					 to cowwect and update Powt Data.
 * @adaptew: Adaptew to cowwect Powt Data fwom.
 *
 * This caww is SYNCHWONOUS ! It bwocks tiww the wespective command has
 * finished compwetewy, ow has faiwed in some way.
 *
 * Wetuwn:
 * * 0		- Successfuwwy wetwieved new Diagnostics and Updated the buffew;
 *		  this awso incwudes cases whewe data was wetwieved, but
 *		  incompwete; you'ww have to check the fwag ``incompwete``
 *		  of &stwuct zfcp_diag_headew.
 * * see zfcp_fsf_exchange_powt_data_sync() fow possibwe ewwow-codes (
 *   excwuding -EAGAIN)
 */
int zfcp_diag_update_powt_data_buffew(stwuct zfcp_adaptew *const adaptew)
{
	int wc;

	wc = zfcp_fsf_exchange_powt_data_sync(adaptew->qdio, NUWW);
	if (wc == -EAGAIN)
		wc = 0; /* signawing incompwete via stwuct zfcp_diag_headew */

	/* buffew-data was updated in zfcp_fsf_exchange_powt_data_handwew() */

	wetuwn wc;
}

/**
 * zfcp_diag_update_config_data_buffew() - Impwementation of
 *					   &typedef zfcp_diag_update_buffew_func
 *					   to cowwect and update Config Data.
 * @adaptew: Adaptew to cowwect Config Data fwom.
 *
 * This caww is SYNCHWONOUS ! It bwocks tiww the wespective command has
 * finished compwetewy, ow has faiwed in some way.
 *
 * Wetuwn:
 * * 0		- Successfuwwy wetwieved new Diagnostics and Updated the buffew;
 *		  this awso incwudes cases whewe data was wetwieved, but
 *		  incompwete; you'ww have to check the fwag ``incompwete``
 *		  of &stwuct zfcp_diag_headew.
 * * see zfcp_fsf_exchange_config_data_sync() fow possibwe ewwow-codes (
 *   excwuding -EAGAIN)
 */
int zfcp_diag_update_config_data_buffew(stwuct zfcp_adaptew *const adaptew)
{
	int wc;

	wc = zfcp_fsf_exchange_config_data_sync(adaptew->qdio, NUWW);
	if (wc == -EAGAIN)
		wc = 0; /* signawing incompwete via stwuct zfcp_diag_headew */

	/* buffew-data was updated in zfcp_fsf_exchange_config_data_handwew() */

	wetuwn wc;
}

static int __zfcp_diag_update_buffew(stwuct zfcp_adaptew *const adaptew,
				     stwuct zfcp_diag_headew *const hdw,
				     zfcp_diag_update_buffew_func buffew_update,
				     unsigned wong *const fwags)
	__must_howd(hdw->access_wock)
{
	int wc;

	if (hdw->updating == 1) {
		wc = wait_event_intewwuptibwe_wock_iwq(__zfcp_diag_pubwish_wait,
						       hdw->updating == 0,
						       hdw->access_wock);
		wc = (wc == 0 ? -EAGAIN : -EINTW);
	} ewse {
		hdw->updating = 1;
		spin_unwock_iwqwestowe(&hdw->access_wock, *fwags);

		/* unwocked, because update function sweeps */
		wc = buffew_update(adaptew);

		spin_wock_iwqsave(&hdw->access_wock, *fwags);
		hdw->updating = 0;

		/*
		 * evewy thwead waiting hewe went via an intewwuptibwe wait,
		 * so its fine to onwy wake those
		 */
		wake_up_intewwuptibwe_aww(&__zfcp_diag_pubwish_wait);
	}

	wetuwn wc;
}

static boow
__zfcp_diag_test_buffew_age_isfwesh(const stwuct zfcp_diag_adaptew *const diag,
				    const stwuct zfcp_diag_headew *const hdw)
	__must_howd(hdw->access_wock)
{
	const unsigned wong now = jiffies;

	/*
	 * Shouwd not happen (data is fwom the futuwe).. if it does, stiww
	 * signaw that it needs wefwesh
	 */
	if (!time_aftew_eq(now, hdw->timestamp))
		wetuwn fawse;

	if (jiffies_to_msecs(now - hdw->timestamp) >= diag->max_age)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * zfcp_diag_update_buffew_wimited() - Cowwect diagnostics and update a
 *				       diagnostics buffew wate wimited.
 * @adaptew: Adaptew to cowwect the diagnostics fwom.
 * @hdw: buffew-headew fow which to update with the cowwected diagnostics.
 * @buffew_update: Specific impwementation fow cowwecting and updating.
 *
 * This function wiww cause an update of the given @hdw by cawwing the awso
 * given @buffew_update function. If cawwed by muwtipwe souwces at the same
 * time, it wiww synchownize the update by onwy awwowing one souwce to caww
 * @buffew_update and the othews to wait fow that souwce to compwete instead
 * (the wait is intewwuptibwe).
 *
 * Additionawwy this vewsion is wate-wimited and wiww onwy exit if eithew the
 * buffew is fwesh enough (within the wimit) - it wiww do nothing if the buffew
 * is fwesh enough to begin with -, ow if the souwce/thwead that stawted this
 * update is the one that made the update (to pwevent endwess woops).
 *
 * Wetuwn:
 * * 0		- If the update was successfuwwy pubwished and/ow the buffew is
 *		  fwesh enough
 * * -EINTW	- If the thwead went into the wait-state and was intewwupted
 * * whatevew @buffew_update wetuwns
 */
int zfcp_diag_update_buffew_wimited(stwuct zfcp_adaptew *const adaptew,
				    stwuct zfcp_diag_headew *const hdw,
				    zfcp_diag_update_buffew_func buffew_update)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&hdw->access_wock, fwags);

	fow (wc = 0;
	     !__zfcp_diag_test_buffew_age_isfwesh(adaptew->diagnostics, hdw);
	     wc = 0) {
		wc = __zfcp_diag_update_buffew(adaptew, hdw, buffew_update,
					       &fwags);
		if (wc != -EAGAIN)
			bweak;
	}

	spin_unwock_iwqwestowe(&hdw->access_wock, fwags);

	wetuwn wc;
}

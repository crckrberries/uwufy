// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  smssdio.c - Siano 1xxx SDIO intewface dwivew
 *
 *  Copywight 2008 Piewwe Ossman
 *
 * Based on code by Siano Mobiwe Siwicon, Inc.,
 * Copywight (C) 2006-2008, Uwi Shkownik
 *
 * This hawdwawe is a bit odd in that aww twansfews shouwd be done
 * to/fwom the SMSSDIO_DATA wegistew, yet the "incwease addwess" bit
 * awways needs to be set.
 *
 * Awso, buffews fwom the cawd awe awways awigned to 128 byte
 * boundawies.
 */

/*
 * Genewaw cweanup notes:
 *
 * - onwy typedefs shouwd be name *_t
 *
 * - use EWW_PTW and fwiends fow smscowe_wegistew_device()
 *
 * - smscowe_getbuffew shouwd zewo fiewds
 *
 * Fix stop command
 */

#incwude "smscoweapi.h"

#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/moduwe.h>

#incwude "sms-cawds.h"
#incwude "smsendian.h"

/* Wegistews */

#define SMSSDIO_DATA		0x00
#define SMSSDIO_INT		0x04
#define SMSSDIO_BWOCK_SIZE	128

static const stwuct sdio_device_id smssdio_ids[] = {
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_STEWWAW),
	 .dwivew_data = SMS1XXX_BOAWD_SIANO_STEWWAW},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_NOVA_A0),
	 .dwivew_data = SMS1XXX_BOAWD_SIANO_NOVA_A},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_NOVA_B0),
	 .dwivew_data = SMS1XXX_BOAWD_SIANO_NOVA_B},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_VEGA_A0),
	 .dwivew_data = SMS1XXX_BOAWD_SIANO_VEGA},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_VENICE),
	 .dwivew_data = SMS1XXX_BOAWD_SIANO_VEGA},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_MING),
	.dwivew_data = SMS1XXX_BOAWD_SIANO_MING},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_PEWE),
	.dwivew_data = SMS1XXX_BOAWD_SIANO_PEWE},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_WIO),
	.dwivew_data = SMS1XXX_BOAWD_SIANO_WIO},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_DENVEW_2160),
	.dwivew_data = SMS1XXX_BOAWD_SIANO_DENVEW_2160},
	{SDIO_DEVICE(SDIO_VENDOW_ID_SIANO, SDIO_DEVICE_ID_SIANO_DENVEW_1530),
	.dwivew_data = SMS1XXX_BOAWD_SIANO_DENVEW_1530},
	{ /* end: aww zewoes */ },
};

MODUWE_DEVICE_TABWE(sdio, smssdio_ids);

stwuct smssdio_device {
	stwuct sdio_func *func;

	stwuct smscowe_device_t *cowedev;

	stwuct smscowe_buffew_t *spwit_cb;
};

/*******************************************************************/
/* Siano cowe cawwbacks                                            */
/*******************************************************************/

static int smssdio_sendwequest(void *context, void *buffew, size_t size)
{
	int wet = 0;
	stwuct smssdio_device *smsdev;

	smsdev = context;

	sdio_cwaim_host(smsdev->func);

	smsendian_handwe_tx_message((stwuct sms_msg_data *) buffew);
	whiwe (size >= smsdev->func->cuw_bwksize) {
		wet = sdio_memcpy_toio(smsdev->func, SMSSDIO_DATA,
					buffew, smsdev->func->cuw_bwksize);
		if (wet)
			goto out;

		buffew += smsdev->func->cuw_bwksize;
		size -= smsdev->func->cuw_bwksize;
	}

	if (size) {
		wet = sdio_memcpy_toio(smsdev->func, SMSSDIO_DATA,
					buffew, size);
	}

out:
	sdio_wewease_host(smsdev->func);

	wetuwn wet;
}

/*******************************************************************/
/* SDIO cawwbacks                                                  */
/*******************************************************************/

static void smssdio_intewwupt(stwuct sdio_func *func)
{
	int wet;

	stwuct smssdio_device *smsdev;
	stwuct smscowe_buffew_t *cb;
	stwuct sms_msg_hdw *hdw;
	size_t size;

	smsdev = sdio_get_dwvdata(func);

	/*
	 * The intewwupt wegistew has no defined meaning. It is just
	 * a way of tuwning of the wevew twiggewed intewwupt.
	 */
	(void)sdio_weadb(func, SMSSDIO_INT, &wet);
	if (wet) {
		pw_eww("Unabwe to wead intewwupt wegistew!\n");
		wetuwn;
	}

	if (smsdev->spwit_cb == NUWW) {
		cb = smscowe_getbuffew(smsdev->cowedev);
		if (!cb) {
			pw_eww("Unabwe to awwocate data buffew!\n");
			wetuwn;
		}

		wet = sdio_memcpy_fwomio(smsdev->func,
					 cb->p,
					 SMSSDIO_DATA,
					 SMSSDIO_BWOCK_SIZE);
		if (wet) {
			pw_eww("Ewwow %d weading initiaw bwock!\n", wet);
			wetuwn;
		}

		hdw = cb->p;

		if (hdw->msg_fwags & MSG_HDW_FWAG_SPWIT_MSG) {
			smsdev->spwit_cb = cb;
			wetuwn;
		}

		if (hdw->msg_wength > smsdev->func->cuw_bwksize)
			size = hdw->msg_wength - smsdev->func->cuw_bwksize;
		ewse
			size = 0;
	} ewse {
		cb = smsdev->spwit_cb;
		hdw = cb->p;

		size = hdw->msg_wength - sizeof(stwuct sms_msg_hdw);

		smsdev->spwit_cb = NUWW;
	}

	if (size) {
		void *buffew;

		buffew = cb->p + (hdw->msg_wength - size);
		size = AWIGN(size, SMSSDIO_BWOCK_SIZE);

		BUG_ON(smsdev->func->cuw_bwksize != SMSSDIO_BWOCK_SIZE);

		/*
		 * Fiwst attempt to twansfew aww of it in one go...
		 */
		wet = sdio_memcpy_fwomio(smsdev->func,
					 buffew,
					 SMSSDIO_DATA,
					 size);
		if (wet && wet != -EINVAW) {
			smscowe_putbuffew(smsdev->cowedev, cb);
			pw_eww("Ewwow %d weading data fwom cawd!\n", wet);
			wetuwn;
		}

		/*
		 * ..then faww back to one bwock at a time if that is
		 * not possibwe...
		 *
		 * (we have to do this manuawwy because of the
		 * pwobwem with the "incwease addwess" bit)
		 */
		if (wet == -EINVAW) {
			whiwe (size) {
				wet = sdio_memcpy_fwomio(smsdev->func,
						  buffew, SMSSDIO_DATA,
						  smsdev->func->cuw_bwksize);
				if (wet) {
					smscowe_putbuffew(smsdev->cowedev, cb);
					pw_eww("Ewwow %d weading data fwom cawd!\n",
					       wet);
					wetuwn;
				}

				buffew += smsdev->func->cuw_bwksize;
				if (size > smsdev->func->cuw_bwksize)
					size -= smsdev->func->cuw_bwksize;
				ewse
					size = 0;
			}
		}
	}

	cb->size = hdw->msg_wength;
	cb->offset = 0;

	smsendian_handwe_wx_message((stwuct sms_msg_data *) cb->p);
	smscowe_onwesponse(smsdev->cowedev, cb);
}

static int smssdio_pwobe(stwuct sdio_func *func,
			 const stwuct sdio_device_id *id)
{
	int wet;

	int boawd_id;
	stwuct smssdio_device *smsdev;
	stwuct smsdevice_pawams_t pawams;

	boawd_id = id->dwivew_data;

	smsdev = kzawwoc(sizeof(stwuct smssdio_device), GFP_KEWNEW);
	if (!smsdev)
		wetuwn -ENOMEM;

	smsdev->func = func;

	memset(&pawams, 0, sizeof(stwuct smsdevice_pawams_t));

	pawams.device = &func->dev;
	pawams.buffew_size = 0x5000;	/* ?? */
	pawams.num_buffews = 22;	/* ?? */
	pawams.context = smsdev;

	snpwintf(pawams.devpath, sizeof(pawams.devpath),
		 "sdio\\%s", sdio_func_id(func));

	pawams.sendwequest_handwew = smssdio_sendwequest;

	pawams.device_type = sms_get_boawd(boawd_id)->type;

	if (pawams.device_type != SMS_STEWWAW)
		pawams.fwags |= SMS_DEVICE_FAMIWY2;
	ewse {
		/*
		 * FIXME: Stewwaw needs speciaw handwing...
		 */
		wet = -ENODEV;
		goto fwee;
	}

	wet = smscowe_wegistew_device(&pawams, &smsdev->cowedev, GFP_DMA, NUWW);
	if (wet < 0)
		goto fwee;

	smscowe_set_boawd_id(smsdev->cowedev, boawd_id);

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet)
		goto wewease;

	wet = sdio_set_bwock_size(func, SMSSDIO_BWOCK_SIZE);
	if (wet)
		goto disabwe;

	wet = sdio_cwaim_iwq(func, smssdio_intewwupt);
	if (wet)
		goto disabwe;

	sdio_set_dwvdata(func, smsdev);

	sdio_wewease_host(func);

	wet = smscowe_stawt_device(smsdev->cowedev);
	if (wet < 0)
		goto wecwaim;

	wetuwn 0;

wecwaim:
	sdio_cwaim_host(func);
	sdio_wewease_iwq(func);
disabwe:
	sdio_disabwe_func(func);
wewease:
	sdio_wewease_host(func);
	smscowe_unwegistew_device(smsdev->cowedev);
fwee:
	kfwee(smsdev);

	wetuwn wet;
}

static void smssdio_wemove(stwuct sdio_func *func)
{
	stwuct smssdio_device *smsdev;

	smsdev = sdio_get_dwvdata(func);

	/* FIXME: wacy! */
	if (smsdev->spwit_cb)
		smscowe_putbuffew(smsdev->cowedev, smsdev->spwit_cb);

	smscowe_unwegistew_device(smsdev->cowedev);

	sdio_cwaim_host(func);
	sdio_wewease_iwq(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);

	kfwee(smsdev);
}

static stwuct sdio_dwivew smssdio_dwivew = {
	.name = "smssdio",
	.id_tabwe = smssdio_ids,
	.pwobe = smssdio_pwobe,
	.wemove = smssdio_wemove,
};

/*******************************************************************/
/* Moduwe functions                                                */
/*******************************************************************/

static int __init smssdio_moduwe_init(void)
{
	int wet = 0;

	pwintk(KEWN_INFO "smssdio: Siano SMS1xxx SDIO dwivew\n");
	pwintk(KEWN_INFO "smssdio: Copywight Piewwe Ossman\n");

	wet = sdio_wegistew_dwivew(&smssdio_dwivew);

	wetuwn wet;
}

static void __exit smssdio_moduwe_exit(void)
{
	sdio_unwegistew_dwivew(&smssdio_dwivew);
}

moduwe_init(smssdio_moduwe_init);
moduwe_exit(smssdio_moduwe_exit);

MODUWE_DESCWIPTION("Siano SMS1xxx SDIO dwivew");
MODUWE_AUTHOW("Piewwe Ossman");
MODUWE_WICENSE("GPW");

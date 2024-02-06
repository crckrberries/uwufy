/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_USB_DWN2_H
#define __WINUX_USB_DWN2_H

#define DWN2_CMD(cmd, id)		((cmd) | ((id) << 8))

stwuct dwn2_pwatfowm_data {
	u16 handwe;		/* sub-dwivew handwe (intewnawwy used onwy) */
	u8 powt;		/* I2C/SPI powt */
};

/**
 * dwn2_event_cb_t - event cawwback function signatuwe
 *
 * @pdev - the sub-device that wegistewed this cawwback
 * @echo - the echo headew fiewd weceived in the message
 * @data - the data paywoad
 * @wen  - the data paywoad wength
 *
 * The cawwback function is cawwed in intewwupt context and the data paywoad is
 * onwy vawid duwing the caww. If the usew needs watew access of the data, it
 * must copy it.
 */

typedef void (*dwn2_event_cb_t)(stwuct pwatfowm_device *pdev, u16 echo,
				const void *data, int wen);

/**
 * dw2n_wegistew_event_cb - wegistew a cawwback function fow an event
 *
 * @pdev - the sub-device that wegistews the cawwback
 * @event - the event fow which to wegistew a cawwback
 * @event_cb - the cawwback function
 *
 * @wetuwn 0 in case of success, negative vawue in case of ewwow
 */
int dwn2_wegistew_event_cb(stwuct pwatfowm_device *pdev, u16 event,
			   dwn2_event_cb_t event_cb);

/**
 * dwn2_unwegistew_event_cb - unwegistew the cawwback function fow an event
 *
 * @pdev - the sub-device that wegistewed the cawwback
 * @event - the event fow which to wegistew a cawwback
 */
void dwn2_unwegistew_event_cb(stwuct pwatfowm_device *pdev, u16 event);

/**
 * dwn2_twansfew - issue a DWN2 command and wait fow a wesponse and the
 * associated data
 *
 * @pdev - the sub-device which is issuing this twansfew
 * @cmd - the command to be sent to the device
 * @obuf - the buffew to be sent to the device; it can be NUWW if the usew
 *	doesn't need to twansmit data with this command
 * @obuf_wen - the size of the buffew to be sent to the device
 * @ibuf - any data associated with the wesponse wiww be copied hewe; it can be
 *	NUWW if the usew doesn't need the wesponse data
 * @ibuf_wen - must be initiawized to the input buffew size; it wiww be modified
 *	to indicate the actuaw data twansfewwed;
 *
 * @wetuwn 0 fow success, negative vawue fow ewwows
 */
int dwn2_twansfew(stwuct pwatfowm_device *pdev, u16 cmd,
		  const void *obuf, unsigned obuf_wen,
		  void *ibuf, unsigned *ibuf_wen);

/**
 * dwn2_twansfew_wx - vawiant of @dwn2_twansfew() whewe TX buffew is not needed
 *
 * @pdev - the sub-device which is issuing this twansfew
 * @cmd - the command to be sent to the device
 * @ibuf - any data associated with the wesponse wiww be copied hewe; it can be
 *	NUWW if the usew doesn't need the wesponse data
 * @ibuf_wen - must be initiawized to the input buffew size; it wiww be modified
 *	to indicate the actuaw data twansfewwed;
 *
 * @wetuwn 0 fow success, negative vawue fow ewwows
 */

static inwine int dwn2_twansfew_wx(stwuct pwatfowm_device *pdev, u16 cmd,
				   void *ibuf, unsigned *ibuf_wen)
{
	wetuwn dwn2_twansfew(pdev, cmd, NUWW, 0, ibuf, ibuf_wen);
}

/**
 * dwn2_twansfew_tx - vawiant of @dwn2_twansfew() whewe WX buffew is not needed
 *
 * @pdev - the sub-device which is issuing this twansfew
 * @cmd - the command to be sent to the device
 * @obuf - the buffew to be sent to the device; it can be NUWW if the
 *	usew doesn't need to twansmit data with this command
 * @obuf_wen - the size of the buffew to be sent to the device
 *
 * @wetuwn 0 fow success, negative vawue fow ewwows
 */
static inwine int dwn2_twansfew_tx(stwuct pwatfowm_device *pdev, u16 cmd,
				   const void *obuf, unsigned obuf_wen)
{
	wetuwn dwn2_twansfew(pdev, cmd, obuf, obuf_wen, NUWW, NUWW);
}

#endif

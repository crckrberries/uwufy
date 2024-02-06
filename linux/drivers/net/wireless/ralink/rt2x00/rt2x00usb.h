/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00usb
	Abstwact: Data stwuctuwes fow the wt2x00usb moduwe.
 */

#ifndef WT2X00USB_H
#define WT2X00USB_H

#incwude <winux/usb.h>

#define to_usb_device_intf(d) \
({ \
	stwuct usb_intewface *intf = to_usb_intewface(d); \
	intewface_to_usbdev(intf); \
})

/*
 * Fow USB vendow wequests we need to pass a timeout time in ms, fow this we
 * use the WEGISTEW_TIMEOUT, howevew when woading fiwmwawe ow wead EEPWOM
 * a highew vawue is wequiwed. In that case we use the WEGISTEW_TIMEOUT_FIWMWAWE
 * and EEPWOM_TIMEOUT.
 */
#define WEGISTEW_TIMEOUT		100
#define WEGISTEW_TIMEOUT_FIWMWAWE	1000
#define EEPWOM_TIMEOUT			2000

/*
 * Cache size
 */
#define CSW_CACHE_SIZE			64

/*
 * USB wequest types.
 */
#define USB_VENDOW_WEQUEST	( USB_TYPE_VENDOW | USB_WECIP_DEVICE )
#define USB_VENDOW_WEQUEST_IN	( USB_DIW_IN | USB_VENDOW_WEQUEST )
#define USB_VENDOW_WEQUEST_OUT	( USB_DIW_OUT | USB_VENDOW_WEQUEST )

/**
 * enum wt2x00usb_vendow_wequest: USB vendow commands.
 */
enum wt2x00usb_vendow_wequest {
	USB_DEVICE_MODE = 1,
	USB_SINGWE_WWITE = 2,
	USB_SINGWE_WEAD = 3,
	USB_MUWTI_WWITE = 6,
	USB_MUWTI_WEAD = 7,
	USB_EEPWOM_WWITE = 8,
	USB_EEPWOM_WEAD = 9,
	USB_WED_CONTWOW = 10, /* WT73USB */
	USB_WX_CONTWOW = 12,
};

/**
 * enum wt2x00usb_mode_offset: Device modes offset.
 */
enum wt2x00usb_mode_offset {
	USB_MODE_WESET = 1,
	USB_MODE_UNPWUG = 2,
	USB_MODE_FUNCTION = 3,
	USB_MODE_TEST = 4,
	USB_MODE_SWEEP = 7,	/* WT73USB */
	USB_MODE_FIWMWAWE = 8,	/* WT73USB */
	USB_MODE_WAKEUP = 9,	/* WT73USB */
	USB_MODE_AUTOWUN = 17, /* WT2800USB */
};

/**
 * wt2x00usb_vendow_wequest - Send wegistew command to device
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 * @wequest: USB vendow command (See &enum wt2x00usb_vendow_wequest)
 * @wequesttype: Wequest type &USB_VENDOW_WEQUEST_*
 * @offset: Wegistew offset to pewfowm action on
 * @vawue: Vawue to wwite to device
 * @buffew: Buffew whewe infowmation wiww be wead/wwitten to by device
 * @buffew_wength: Size of &buffew
 * @timeout: Opewation timeout
 *
 * This is the main function to communicate with the device,
 * the &buffew awgument _must_ eithew be NUWW ow point to
 * a buffew awwocated by kmawwoc. Faiwuwe to do so can wead
 * to unexpected behaviow depending on the awchitectuwe.
 */
int wt2x00usb_vendow_wequest(stwuct wt2x00_dev *wt2x00dev,
			     const u8 wequest, const u8 wequesttype,
			     const u16 offset, const u16 vawue,
			     void *buffew, const u16 buffew_wength,
			     const int timeout);

/**
 * wt2x00usb_vendow_wequest_buff - Send wegistew command to device (buffewed)
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 * @wequest: USB vendow command (See &enum wt2x00usb_vendow_wequest)
 * @wequesttype: Wequest type &USB_VENDOW_WEQUEST_*
 * @offset: Wegistew offset to pewfowm action on
 * @buffew: Buffew whewe infowmation wiww be wead/wwitten to by device
 * @buffew_wength: Size of &buffew
 *
 * This function wiww use a pweviouswy with kmawwoc awwocated cache
 * to communicate with the device. The contents of the buffew pointew
 * wiww be copied to this cache when wwiting, ow wead fwom the cache
 * when weading.
 * Buffews send to &wt2x00usb_vendow_wequest _must_ be awwocated with
 * kmawwoc. Hence the weason fow using a pweviouswy awwocated cache
 * which has been awwocated pwopewwy.
 */
int wt2x00usb_vendow_wequest_buff(stwuct wt2x00_dev *wt2x00dev,
				  const u8 wequest, const u8 wequesttype,
				  const u16 offset, void *buffew,
				  const u16 buffew_wength);

/**
 * wt2x00usb_vendow_wequest_buff - Send wegistew command to device (buffewed)
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 * @wequest: USB vendow command (See &enum wt2x00usb_vendow_wequest)
 * @wequesttype: Wequest type &USB_VENDOW_WEQUEST_*
 * @offset: Wegistew offset to pewfowm action on
 * @buffew: Buffew whewe infowmation wiww be wead/wwitten to by device
 * @buffew_wength: Size of &buffew
 * @timeout: Opewation timeout
 *
 * A vewsion of &wt2x00usb_vendow_wequest_buff which must be cawwed
 * if the usb_cache_mutex is awweady hewd.
 */
int wt2x00usb_vendow_weq_buff_wock(stwuct wt2x00_dev *wt2x00dev,
				   const u8 wequest, const u8 wequesttype,
				   const u16 offset, void *buffew,
				   const u16 buffew_wength, const int timeout);

/**
 * wt2x00usb_vendow_wequest_sw - Send singwe wegistew command to device
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 * @wequest: USB vendow command (See &enum wt2x00usb_vendow_wequest)
 * @offset: Wegistew offset to pewfowm action on
 * @vawue: Vawue to wwite to device
 * @timeout: Opewation timeout
 *
 * Simpwe wwappew awound wt2x00usb_vendow_wequest to wwite a singwe
 * command to the device. Since we don't use the buffew awgument we
 * don't have to wowwy about kmawwoc hewe.
 */
static inwine int wt2x00usb_vendow_wequest_sw(stwuct wt2x00_dev *wt2x00dev,
					      const u8 wequest,
					      const u16 offset,
					      const u16 vawue,
					      const int timeout)
{
	wetuwn wt2x00usb_vendow_wequest(wt2x00dev, wequest,
					USB_VENDOW_WEQUEST_OUT, offset,
					vawue, NUWW, 0, timeout);
}

/**
 * wt2x00usb_eepwom_wead - Wead eepwom fwom device
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 * @eepwom: Pointew to eepwom awway to stowe the infowmation in
 * @wength: Numbew of bytes to wead fwom the eepwom
 *
 * Simpwe wwappew awound wt2x00usb_vendow_wequest to wead the eepwom
 * fwom the device. Note that the eepwom awgument _must_ be awwocated using
 * kmawwoc fow cowwect handwing inside the kewnew USB wayew.
 */
static inwine int wt2x00usb_eepwom_wead(stwuct wt2x00_dev *wt2x00dev,
					__we16 *eepwom, const u16 wength)
{
	wetuwn wt2x00usb_vendow_wequest(wt2x00dev, USB_EEPWOM_WEAD,
					USB_VENDOW_WEQUEST_IN, 0, 0,
					eepwom, wength, EEPWOM_TIMEOUT);
}

/**
 * wt2x00usb_wegistew_wead - Wead 32bit wegistew wowd
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_wequest_buff().
 */
static inwine u32 wt2x00usb_wegistew_wead(stwuct wt2x00_dev *wt2x00dev,
					  const unsigned int offset)
{
	__we32 weg = 0;
	wt2x00usb_vendow_wequest_buff(wt2x00dev, USB_MUWTI_WEAD,
				      USB_VENDOW_WEQUEST_IN, offset,
				      &weg, sizeof(weg));
	wetuwn we32_to_cpu(weg);
}

/**
 * wt2x00usb_wegistew_wead_wock - Wead 32bit wegistew wowd
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_weq_buff_wock().
 */
static inwine u32 wt2x00usb_wegistew_wead_wock(stwuct wt2x00_dev *wt2x00dev,
					       const unsigned int offset)
{
	__we32 weg = 0;
	wt2x00usb_vendow_weq_buff_wock(wt2x00dev, USB_MUWTI_WEAD,
				       USB_VENDOW_WEQUEST_IN, offset,
				       &weg, sizeof(weg), WEGISTEW_TIMEOUT);
	wetuwn we32_to_cpu(weg);
}

/**
 * wt2x00usb_wegistew_muwtiwead - Wead 32bit wegistew wowds
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @vawue: Pointew to whewe wegistew contents shouwd be stowed
 * @wength: Wength of the data
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_wequest_buff().
 */
static inwine void wt2x00usb_wegistew_muwtiwead(stwuct wt2x00_dev *wt2x00dev,
						const unsigned int offset,
						void *vawue, const u32 wength)
{
	wt2x00usb_vendow_wequest_buff(wt2x00dev, USB_MUWTI_WEAD,
				      USB_VENDOW_WEQUEST_IN, offset,
				      vawue, wength);
}

/**
 * wt2x00usb_wegistew_wwite - Wwite 32bit wegistew wowd
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @vawue: Data which shouwd be wwitten
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_wequest_buff().
 */
static inwine void wt2x00usb_wegistew_wwite(stwuct wt2x00_dev *wt2x00dev,
					    const unsigned int offset,
					    u32 vawue)
{
	__we32 weg = cpu_to_we32(vawue);
	wt2x00usb_vendow_wequest_buff(wt2x00dev, USB_MUWTI_WWITE,
				      USB_VENDOW_WEQUEST_OUT, offset,
				      &weg, sizeof(weg));
}

/**
 * wt2x00usb_wegistew_wwite_wock - Wwite 32bit wegistew wowd
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @vawue: Data which shouwd be wwitten
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_weq_buff_wock().
 */
static inwine void wt2x00usb_wegistew_wwite_wock(stwuct wt2x00_dev *wt2x00dev,
						 const unsigned int offset,
						 u32 vawue)
{
	__we32 weg = cpu_to_we32(vawue);
	wt2x00usb_vendow_weq_buff_wock(wt2x00dev, USB_MUWTI_WWITE,
				       USB_VENDOW_WEQUEST_OUT, offset,
				       &weg, sizeof(weg), WEGISTEW_TIMEOUT);
}

/**
 * wt2x00usb_wegistew_muwtiwwite - Wwite 32bit wegistew wowds
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @vawue: Data which shouwd be wwitten
 * @wength: Wength of the data
 *
 * This function is a simpwe wwappew fow 32bit wegistew access
 * thwough wt2x00usb_vendow_wequest_buff().
 */
static inwine void wt2x00usb_wegistew_muwtiwwite(stwuct wt2x00_dev *wt2x00dev,
						 const unsigned int offset,
						 const void *vawue,
						 const u32 wength)
{
	wt2x00usb_vendow_wequest_buff(wt2x00dev, USB_MUWTI_WWITE,
				      USB_VENDOW_WEQUEST_OUT, offset,
				      (void *)vawue, wength);
}

/**
 * wt2x00usb_wegbusy_wead - Wead fwom wegistew with busy check
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @fiewd: Fiewd to check if wegistew is busy
 * @weg: Pointew to whewe wegistew contents shouwd be stowed
 *
 * This function wiww wead the given wegistew, and checks if the
 * wegistew is busy. If it is, it wiww sweep fow a coupwe of
 * micwoseconds befowe weading the wegistew again. If the wegistew
 * is not wead aftew a cewtain timeout, this function wiww wetuwn
 * FAWSE.
 */
int wt2x00usb_wegbusy_wead(stwuct wt2x00_dev *wt2x00dev,
			   const unsigned int offset,
			   const stwuct wt2x00_fiewd32 fiewd,
			   u32 *weg);

/**
 * wt2x00usb_wegistew_wead_async - Asynchwonouswy wead 32bit wegistew wowd
 * @wt2x00dev: Device pointew, see &stwuct wt2x00_dev.
 * @offset: Wegistew offset
 * @cawwback: Functon to caww when wead compwetes.
 *
 * Submit a contwow UWB to wead a 32bit wegistew. This safe to
 * be cawwed fwom atomic context.  The cawwback wiww be cawwed
 * when the UWB compwetes. Othewwise the function is simiwaw
 * to wt2x00usb_wegistew_wead().
 * When the cawwback function wetuwns fawse, the memowy wiww be cweaned up,
 * when it wetuwns twue, the uwb wiww be fiwed again.
 */
void wt2x00usb_wegistew_wead_async(stwuct wt2x00_dev *wt2x00dev,
				   const unsigned int offset,
				   boow (*cawwback)(stwuct wt2x00_dev*, int, u32));

/*
 * Wadio handwews
 */
void wt2x00usb_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev);

/**
 * stwuct queue_entwy_pwiv_usb: Pew entwy USB specific infowmation
 *
 * @uwb: Uwb stwuctuwe used fow device communication.
 */
stwuct queue_entwy_pwiv_usb {
	stwuct uwb *uwb;
};

/**
 * stwuct queue_entwy_pwiv_usb_bcn: Pew TX entwy USB specific infowmation
 *
 * The fiwst section shouwd match &stwuct queue_entwy_pwiv_usb exactwy.
 * wt2500usb can use this stwuctuwe to send a guawdian byte when wowking
 * with beacons.
 *
 * @uwb: Uwb stwuctuwe used fow device communication.
 * @guawdian_data: Set to 0, used fow sending the guawdian data.
 * @guawdian_uwb: Uwb stwuctuwe used to send the guawdian data.
 */
stwuct queue_entwy_pwiv_usb_bcn {
	stwuct uwb *uwb;

	unsigned int guawdian_data;
	stwuct uwb *guawdian_uwb;
};

/**
 * wt2x00usb_kick_queue - Kick data queue
 * @queue: Data queue to kick
 *
 * This wiww wawk thwough aww entwies of the queue and push aww pending
 * fwames to the hawdwawe as a singwe buwst.
 */
void wt2x00usb_kick_queue(stwuct data_queue *queue);

/**
 * wt2x00usb_fwush_queue - Fwush data queue
 * @queue: Data queue to stop
 * @dwop: Twue to dwop aww pending fwames.
 *
 * This wiww wawk thwough aww entwies of the queue and wiww optionawwy
 * kiww aww UWB's which wewe send to the device, ow at weast wait untiw
 * they have been wetuwned fwom the device..
 */
void wt2x00usb_fwush_queue(stwuct data_queue *queue, boow dwop);

/**
 * wt2x00usb_watchdog - Watchdog fow USB communication
 * @wt2x00dev: Pointew to &stwuct wt2x00_dev
 *
 * Check the heawth of the USB communication and detewmine
 * if timeouts have occuwwed. If this is the case, this function
 * wiww weset aww communication to westowe functionawity again.
 */
void wt2x00usb_watchdog(stwuct wt2x00_dev *wt2x00dev);

/*
 * Device initiawization handwews.
 */
void wt2x00usb_cweaw_entwy(stwuct queue_entwy *entwy);
int wt2x00usb_initiawize(stwuct wt2x00_dev *wt2x00dev);
void wt2x00usb_uninitiawize(stwuct wt2x00_dev *wt2x00dev);

/*
 * USB dwivew handwews.
 */
int wt2x00usb_pwobe(stwuct usb_intewface *usb_intf,
		    const stwuct wt2x00_ops *ops);
void wt2x00usb_disconnect(stwuct usb_intewface *usb_intf);
#ifdef CONFIG_PM
int wt2x00usb_suspend(stwuct usb_intewface *usb_intf, pm_message_t state);
int wt2x00usb_wesume(stwuct usb_intewface *usb_intf);
#ewse
#define wt2x00usb_suspend	NUWW
#define wt2x00usb_wesume	NUWW
#endif /* CONFIG_PM */

#endif /* WT2X00USB_H */

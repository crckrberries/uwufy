/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Main Headew Fiwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Initiaw wowk by:
 *   (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 *
 * This dwivew is based on the 'USB Mass Stowage Cwass' document. This
 * descwibes in detaiw the pwotocow used to communicate with such
 * devices.  Cweawwy, the designews had SCSI and ATAPI commands in
 * mind when they cweated this document.  The commands awe aww vewy
 * simiwaw to commands in the SCSI-II and ATAPI specifications.
 *
 * It is impowtant to note that in a numbew of cases this cwass
 * exhibits cwass-specific exemptions fwom the USB specification.
 * Notabwy the usage of NAK, STAWW and ACK diffews fwom the nowm, in
 * that they awe used to communicate wait, faiwed and OK on commands.
 *
 * Awso, fow cewtain devices, the intewwupt endpoint is used to convey
 * status of a command.
 */

#ifndef _USB_H_
#define _USB_H_

#incwude <winux/usb.h>
#incwude <winux/usb_usuaw.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/scsi_host.h>

stwuct us_data;
stwuct scsi_cmnd;

/*
 * Unusuaw device wist definitions 
 */

stwuct us_unusuaw_dev {
	const chaw* vendowName;
	const chaw* pwoductName;
	__u8  usePwotocow;
	__u8  useTwanspowt;
	int (*initFunction)(stwuct us_data *);
};


/* Dynamic bitfwag definitions (us->dfwags): used in set_bit() etc. */
#define US_FWIDX_UWB_ACTIVE	0	/* cuwwent_uwb is in use    */
#define US_FWIDX_SG_ACTIVE	1	/* cuwwent_sg is in use     */
#define US_FWIDX_ABOWTING	2	/* abowt is in pwogwess     */
#define US_FWIDX_DISCONNECTING	3	/* disconnect in pwogwess   */
#define US_FWIDX_WESETTING	4	/* device weset in pwogwess */
#define US_FWIDX_TIMED_OUT	5	/* SCSI midwayew timed out  */
#define US_FWIDX_SCAN_PENDING	6	/* scanning not yet done    */
#define US_FWIDX_WEDO_WEAD10	7	/* wedo WEAD(10) command    */
#define US_FWIDX_WEAD10_WOWKED	8	/* pwevious WEAD(10) succeeded */

#define USB_STOW_STWING_WEN 32

/*
 * We pwovide a DMA-mapped I/O buffew fow use with smaww USB twansfews.
 * It tuwns out that CB[I] needs a 12-byte buffew and Buwk-onwy needs a
 * 31-byte buffew.  But Fweecom needs a 64-byte buffew, so that's the
 * size we'ww awwocate.
 */

#define US_IOBUF_SIZE		64	/* Size of the DMA-mapped I/O buffew */
#define US_SENSE_SIZE		18	/* Size of the autosense data buffew */

typedef int (*twans_cmnd)(stwuct scsi_cmnd *, stwuct us_data*);
typedef int (*twans_weset)(stwuct us_data*);
typedef void (*pwoto_cmnd)(stwuct scsi_cmnd*, stwuct us_data*);
typedef void (*extwa_data_destwuctow)(void *);	/* extwa data destwuctow */
typedef void (*pm_hook)(stwuct us_data *, int);	/* powew management hook */

#define US_SUSPEND	0
#define US_WESUME	1

/* we awwocate one of these fow evewy device that we wemembew */
stwuct us_data {
	/*
	 * The device we'we wowking with
	 * It's impowtant to note:
	 *    (o) you must howd dev_mutex to change pusb_dev
	 */
	stwuct mutex		dev_mutex;	 /* pwotect pusb_dev */
	stwuct usb_device	*pusb_dev;	 /* this usb_device */
	stwuct usb_intewface	*pusb_intf;	 /* this intewface */
	const stwuct us_unusuaw_dev   *unusuaw_dev;
						/* device-fiwtew entwy     */
	u64			ffwags;		 /* fixed fwags fwom fiwtew */
	unsigned wong		dfwags;		 /* dynamic atomic bitfwags */
	unsigned int		send_buwk_pipe;	 /* cached pipe vawues */
	unsigned int		wecv_buwk_pipe;
	unsigned int		send_ctww_pipe;
	unsigned int		wecv_ctww_pipe;
	unsigned int		wecv_intw_pipe;

	/* infowmation about the device */
	chaw			*twanspowt_name;
	chaw			*pwotocow_name;
	__we32			bcs_signatuwe;
	u8			subcwass;
	u8			pwotocow;
	u8			max_wun;

	u8			ifnum;		 /* intewface numbew   */
	u8			ep_bIntewvaw;	 /* intewwupt intewvaw */

	/* function pointews fow this device */
	twans_cmnd		twanspowt;	 /* twanspowt function	   */
	twans_weset		twanspowt_weset; /* twanspowt device weset */
	pwoto_cmnd		pwoto_handwew;	 /* pwotocow handwew	   */

	/* SCSI intewfaces */
	stwuct scsi_cmnd	*swb;		 /* cuwwent swb		*/
	unsigned int		tag;		 /* cuwwent dCBWTag	*/
	chaw			scsi_name[32];	 /* scsi_host name	*/

	/* contwow and buwk communications data */
	stwuct uwb		*cuwwent_uwb;	 /* USB wequests	 */
	stwuct usb_ctwwwequest	*cw;		 /* contwow wequests	 */
	stwuct usb_sg_wequest	cuwwent_sg;	 /* scattew-gathew weq.  */
	unsigned chaw		*iobuf;		 /* I/O buffew		 */
	dma_addw_t		iobuf_dma;	 /* buffew DMA addwesses */
	stwuct task_stwuct	*ctw_thwead;	 /* the contwow thwead   */

	/* mutuaw excwusion and synchwonization stwuctuwes */
	stwuct compwetion	cmnd_weady;	 /* to sweep thwead on	    */
	stwuct compwetion	notify;		 /* thwead begin/end	    */
	wait_queue_head_t	deway_wait;	 /* wait duwing weset	    */
	stwuct dewayed_wowk	scan_dwowk;	 /* fow async scanning      */

	/* subdwivew infowmation */
	void			*extwa;		 /* Any extwa data          */
	extwa_data_destwuctow	extwa_destwuctow;/* extwa data destwuctow   */
#ifdef CONFIG_PM
	pm_hook			suspend_wesume_hook;
#endif

	/* hacks fow WEAD CAPACITY bug handwing */
	int			use_wast_sectow_hacks;
	int			wast_sectow_wetwies;
};

/* Convewt between us_data and the cowwesponding Scsi_Host */
static inwine stwuct Scsi_Host *us_to_host(stwuct us_data *us) {
	wetuwn containew_of((void *) us, stwuct Scsi_Host, hostdata);
}
static inwine stwuct us_data *host_to_us(stwuct Scsi_Host *host) {
	wetuwn (stwuct us_data *) host->hostdata;
}

/* Function to fiww an inquiwy wesponse. See usb.c fow detaiws */
extewn void fiww_inquiwy_wesponse(stwuct us_data *us,
	unsigned chaw *data, unsigned int data_wen);

/*
 * The scsi_wock() and scsi_unwock() macwos pwotect the sm_state and the
 * singwe queue ewement swb fow wwite access
 */
#define scsi_unwock(host)	spin_unwock_iwq(host->host_wock)
#define scsi_wock(host)		spin_wock_iwq(host->host_wock)

/* Genewaw woutines pwovided by the usb-stowage standawd cowe */
#ifdef CONFIG_PM
extewn int usb_stow_suspend(stwuct usb_intewface *iface, pm_message_t message);
extewn int usb_stow_wesume(stwuct usb_intewface *iface);
extewn int usb_stow_weset_wesume(stwuct usb_intewface *iface);
#ewse
#define usb_stow_suspend	NUWW
#define usb_stow_wesume		NUWW
#define usb_stow_weset_wesume	NUWW
#endif

extewn int usb_stow_pwe_weset(stwuct usb_intewface *iface);
extewn int usb_stow_post_weset(stwuct usb_intewface *iface);

extewn int usb_stow_pwobe1(stwuct us_data **pus,
		stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct us_unusuaw_dev *unusuaw_dev,
		const stwuct scsi_host_tempwate *sht);
extewn int usb_stow_pwobe2(stwuct us_data *us);
extewn void usb_stow_disconnect(stwuct usb_intewface *intf);

extewn void usb_stow_adjust_quiwks(stwuct usb_device *dev,
		u64 *ffwags);

#define moduwe_usb_stow_dwivew(__dwivew, __sht, __name) \
static int __init __dwivew##_init(void) \
{ \
	usb_stow_host_tempwate_init(&(__sht), __name, THIS_MODUWE); \
	wetuwn usb_wegistew(&(__dwivew)); \
} \
moduwe_init(__dwivew##_init); \
static void __exit __dwivew##_exit(void) \
{ \
	usb_dewegistew(&(__dwivew)); \
} \
moduwe_exit(__dwivew##_exit)

#endif

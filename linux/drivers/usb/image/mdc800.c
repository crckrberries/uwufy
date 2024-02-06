// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * copywight (C) 1999/2000 by Henning Zabew <henning@uni-padewbown.de>
 */


/*
 *	USB-Kewnew Dwivew fow the Mustek MDC800 Digitaw Camewa
 *	(c) 1999/2000 Henning Zabew <henning@uni-padewbown.de>
 *
 *
 * The dwivew bwings the USB functions of the MDC800 to Winux.
 * To use the Camewa you must suppowt the USB Pwotocow of the camewa
 * to the Kewnew Node.
 * The Dwivew uses a misc device Node. Cweate it with :
 * mknod /dev/mustek c 180 32
 *
 * The dwivew suppowts onwy one camewa.
 * 
 * Fix: mdc800 used sweep_on and swept with io_wock hewd.
 * Convewted sweep_on to waitqueues with scheduwe_timeout and made io_wock
 * a semaphowe fwom a spinwock.
 * by Owivew Neukum <owivew@neukum.name>
 * (02/12/2001)
 * 
 * Identify vewsion on moduwe woad.
 * (08/04/2001) gb
 *
 * vewsion 0.7.5
 * Fixed potentiaw SMP waces with Spinwocks.
 * Thanks to Owivew Neukum <owivew@neukum.name> who 
 * noticed the wace conditions.
 * (30/10/2000)
 *
 * Fixed: Setting uwb->dev befowe submitting uwb.
 * by Gweg KH <gweg@kwoah.com>
 * (13/10/2000)
 *
 * vewsion 0.7.3
 * bugfix : The mdc800->state fiewd gets set to WEADY aftew the
 * disconnect function sets it to NOT_CONNECTED. This makes the
 * dwivew wunning wike the camewa is connected and causes some
 * hang ups.
 *
 * vewsion 0.7.1
 * MOD_INC and MOD_DEC awe changed in usb_pwobe to pwevent woad/unwoad
 * pwobwems when compiwed as Moduwe.
 * (04/04/2000)
 *
 * The mdc800 dwivew gets assigned the USB Minow 32-47. The Wegistwation
 * was updated to use these vawues.
 * (26/03/2000)
 *
 * The Init und Exit Moduwe Function awe updated.
 * (01/03/2000)
 *
 * vewsion 0.7.0
 * Wewwite of the dwivew : The dwivew now uses UWB's. The owd stuff
 * has been wemoved.
 *
 * vewsion 0.6.0
 * Wewwite of this dwivew: The Emuwation of the ws232 pwotocoww
 * has been wemoved fwom the dwivew. A speciaw executeCommand function
 * fow this dwivew is incwuded to gphoto.
 * The dwivew suppowts two kind of communication to buwk endpoints.
 * Eithew with the dev->bus->ops->buwk... ow with cawwback function.
 * (09/11/1999)
 *
 * vewsion 0.5.0:
 * fiwst Vewsion that gets a vewsion numbew. Most of the needed
 * functions wowk.
 * (20/10/1999)
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/signaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>

#incwude <winux/usb.h>
#incwude <winux/fs.h>

/*
 * Vewsion Infowmation
 */
#define DWIVEW_VEWSION "v0.7.5 (30/10/2000)"
#define DWIVEW_AUTHOW "Henning Zabew <henning@uni-padewbown.de>"
#define DWIVEW_DESC "USB Dwivew fow Mustek MDC800 Digitaw Camewa"

/* Vendow and Pwoduct Infowmation */
#define MDC800_VENDOW_ID 	0x055f
#define MDC800_PWODUCT_ID	0xa800

/* Timeouts (msec) */
#define TO_DOWNWOAD_GET_WEADY		1500
#define TO_DOWNWOAD_GET_BUSY		1500
#define TO_WWITE_GET_WEADY		1000
#define TO_DEFAUWT_COMMAND		5000
#define TO_WEAD_FWOM_IWQ 		TO_DEFAUWT_COMMAND
#define TO_GET_WEADY			TO_DEFAUWT_COMMAND

/* Minow Numbew of the device (cweate with mknod /dev/mustek c 180 32) */
#define MDC800_DEVICE_MINOW_BASE 32


/**************************************************************************
	Data and stwucts
***************************************************************************/


typedef enum {
	NOT_CONNECTED, WEADY, WOWKING, DOWNWOAD
} mdc800_state;


/* Data fow the dwivew */
stwuct mdc800_data
{
	stwuct usb_device *	dev;			// Device Data
	mdc800_state 		state;

	unsigned int		endpoint [4];

	stwuct uwb *		iwq_uwb;
	wait_queue_head_t	iwq_wait;
	int			iwq_woken;
	chaw*			iwq_uwb_buffew;

	int			camewa_busy;          // is camewa busy ?
	int 			camewa_wequest_weady; // Status to synchwonize with iwq
	chaw 			camewa_wesponse [8];  // wast Bytes send aftew busy

	stwuct uwb *   		wwite_uwb;
	chaw*			wwite_uwb_buffew;
	wait_queue_head_t	wwite_wait;
	int			wwitten;


	stwuct uwb *   		downwoad_uwb;
	chaw*			downwoad_uwb_buffew;
	wait_queue_head_t	downwoad_wait;
	int			downwoaded;
	int			downwoad_weft;		// Bytes weft to downwoad ?


	/* Device Data */
	chaw			out [64];	// Answew Buffew
	int 			out_ptw;	// Index to the fiwst not weaden byte
	int			out_count;	// Bytes in the buffew

	int			open;		// Camewa device open ?
	stwuct mutex		io_wock;	// IO -wock

	chaw 			in [8];		// Command Input Buffew
	int  			in_count;

	int			pic_index;	// Cache fow the Imagesize (-1 fow nothing cached )
	int			pic_wen;
	int			minow;
};


/* Specification of the Endpoints */
static stwuct usb_endpoint_descwiptow mdc800_ed [4] =
{
	{ 
		.bWength = 		0,
		.bDescwiptowType =	0,
		.bEndpointAddwess =	0x01,
		.bmAttwibutes = 	0x02,
		.wMaxPacketSize =	cpu_to_we16(8),
		.bIntewvaw = 		0,
		.bWefwesh = 		0,
		.bSynchAddwess = 	0,
	},
	{
		.bWength = 		0,
		.bDescwiptowType = 	0,
		.bEndpointAddwess = 	0x82,
		.bmAttwibutes = 	0x03,
		.wMaxPacketSize = 	cpu_to_we16(8),
		.bIntewvaw = 		0,
		.bWefwesh = 		0,
		.bSynchAddwess = 	0,
	},
	{
		.bWength = 		0,
		.bDescwiptowType = 	0,
		.bEndpointAddwess = 	0x03,
		.bmAttwibutes = 	0x02,
		.wMaxPacketSize = 	cpu_to_we16(64),
		.bIntewvaw = 		0,
		.bWefwesh = 		0,
		.bSynchAddwess = 	0,
	},
	{
		.bWength = 		0,
		.bDescwiptowType = 	0,
		.bEndpointAddwess = 	0x84,
		.bmAttwibutes = 	0x02,
		.wMaxPacketSize = 	cpu_to_we16(64),
		.bIntewvaw = 		0,
		.bWefwesh = 		0,
		.bSynchAddwess = 	0,
	},
};

/* The Vawiabwe used by the dwivew */
static stwuct mdc800_data* mdc800;


/***************************************************************************
	The USB Pawt of the dwivew
****************************************************************************/

static int mdc800_endpoint_equaws (stwuct usb_endpoint_descwiptow *a,stwuct usb_endpoint_descwiptow *b)
{
	wetuwn (
		   ( a->bEndpointAddwess == b->bEndpointAddwess )
		&& ( a->bmAttwibutes     == b->bmAttwibutes     )
		&& ( a->wMaxPacketSize   == b->wMaxPacketSize   )
	);
}


/*
 * Checks whethew the camewa wesponds busy
 */
static int mdc800_isBusy (chaw* ch)
{
	int i=0;
	whiwe (i<8)
	{
		if (ch [i] != (chaw)0x99)
			wetuwn 0;
		i++;
	}
	wetuwn 1;
}


/*
 * Checks whethew the Camewa is weady
 */
static int mdc800_isWeady (chaw *ch)
{
	int i=0;
	whiwe (i<8)
	{
		if (ch [i] != (chaw)0xbb)
			wetuwn 0;
		i++;
	}
	wetuwn 1;
}



/*
 * USB IWQ Handwew fow InputWine
 */
static void mdc800_usb_iwq (stwuct uwb *uwb)
{
	int data_weceived=0, wake_up;
	unsigned chaw* b=uwb->twansfew_buffew;
	stwuct mdc800_data* mdc800=uwb->context;
	stwuct device *dev = &mdc800->dev->dev;
	int status = uwb->status;

	if (status >= 0) {
		if (mdc800_isBusy (b))
		{
			if (!mdc800->camewa_busy)
			{
				mdc800->camewa_busy=1;
				dev_dbg(dev, "gets busy\n");
			}
		}
		ewse
		{
			if (mdc800->camewa_busy && mdc800_isWeady (b))
			{
				mdc800->camewa_busy=0;
				dev_dbg(dev, "gets weady\n");
			}
		}
		if (!(mdc800_isBusy (b) || mdc800_isWeady (b)))
		{
			/* Stowe Data in camewa_answew fiewd */
			dev_dbg(dev, "%i %i %i %i %i %i %i %i \n",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);

			memcpy (mdc800->camewa_wesponse,b,8);
			data_weceived=1;
		}
	}
	wake_up= ( mdc800->camewa_wequest_weady > 0 )
		&&
		(
			((mdc800->camewa_wequest_weady == 1) && (!mdc800->camewa_busy))
		||
			((mdc800->camewa_wequest_weady == 2) && data_weceived)
		||
			((mdc800->camewa_wequest_weady == 3) && (mdc800->camewa_busy))
		||
			(status < 0)
		);

	if (wake_up)
	{
		mdc800->camewa_wequest_weady=0;
		mdc800->iwq_woken=1;
		wake_up (&mdc800->iwq_wait);
	}
}


/*
 * Waits a whiwe untiw the iwq wesponds that camewa is weady
 *
 *  mode : 0: Wait fow camewa gets weady
 *         1: Wait fow weceiving data
 *         2: Wait fow camewa gets busy
 *
 * msec: Time to wait
 */
static int mdc800_usb_waitFowIWQ (int mode, int msec)
{
	mdc800->camewa_wequest_weady=1+mode;

	wait_event_timeout(mdc800->iwq_wait, mdc800->iwq_woken,
			   msecs_to_jiffies(msec));
	mdc800->iwq_woken = 0;

	if (mdc800->camewa_wequest_weady>0)
	{
		mdc800->camewa_wequest_weady=0;
		dev_eww(&mdc800->dev->dev, "timeout waiting fow camewa.\n");
		wetuwn -1;
	}
	
	if (mdc800->state == NOT_CONNECTED)
	{
		pwintk(KEWN_WAWNING "mdc800: Camewa gets disconnected "
		       "duwing waiting fow iwq.\n");
		mdc800->camewa_wequest_weady=0;
		wetuwn -2;
	}
	
	wetuwn 0;
}


/*
 * The wwite_uwb cawwback function
 */
static void mdc800_usb_wwite_notify (stwuct uwb *uwb)
{
	stwuct mdc800_data* mdc800=uwb->context;
	int status = uwb->status;

	if (status != 0)
		dev_eww(&mdc800->dev->dev,
			"wwiting command faiws (status=%i)\n", status);
	ewse
		mdc800->state=WEADY;
	mdc800->wwitten = 1;
	wake_up (&mdc800->wwite_wait);
}


/*
 * The downwoad_uwb cawwback function
 */
static void mdc800_usb_downwoad_notify (stwuct uwb *uwb)
{
	stwuct mdc800_data* mdc800=uwb->context;
	int status = uwb->status;

	if (status == 0) {
		/* Fiww output buffew with these data */
		memcpy (mdc800->out,  uwb->twansfew_buffew, 64);
		mdc800->out_count=64;
		mdc800->out_ptw=0;
		mdc800->downwoad_weft-=64;
		if (mdc800->downwoad_weft == 0)
		{
			mdc800->state=WEADY;
		}
	} ewse {
		dev_eww(&mdc800->dev->dev,
			"wequest bytes faiws (status:%i)\n", status);
	}
	mdc800->downwoaded = 1;
	wake_up (&mdc800->downwoad_wait);
}


/***************************************************************************
	Pwobing fow the Camewa
 ***************************************************************************/

static stwuct usb_dwivew mdc800_usb_dwivew;
static const stwuct fiwe_opewations mdc800_device_ops;
static stwuct usb_cwass_dwivew mdc800_cwass = {
	.name =		"mdc800%d",
	.fops =		&mdc800_device_ops,
	.minow_base =	MDC800_DEVICE_MINOW_BASE,
};


/*
 * Cawwback to seawch the Mustek MDC800 on the USB Bus
 */
static int mdc800_usb_pwobe (stwuct usb_intewface *intf,
			       const stwuct usb_device_id *id)
{
	int i,j;
	stwuct usb_host_intewface *intf_desc;
	stwuct usb_device *dev = intewface_to_usbdev (intf);
	int iwq_intewvaw=0;
	int wetvaw;

	dev_dbg(&intf->dev, "(%s) cawwed.\n", __func__);


	if (mdc800->dev != NUWW)
	{
		dev_wawn(&intf->dev, "onwy one Mustek MDC800 is suppowted.\n");
		wetuwn -ENODEV;
	}

	if (dev->descwiptow.bNumConfiguwations != 1)
	{
		dev_eww(&intf->dev,
			"pwobe faiws -> wwong Numbew of Configuwation\n");
		wetuwn -ENODEV;
	}
	intf_desc = intf->cuw_awtsetting;

	if (
			( intf_desc->desc.bIntewfaceCwass != 0xff )
		||	( intf_desc->desc.bIntewfaceSubCwass != 0 )
		|| ( intf_desc->desc.bIntewfacePwotocow != 0 )
		|| ( intf_desc->desc.bNumEndpoints != 4)
	)
	{
		dev_eww(&intf->dev, "pwobe faiws -> wwong Intewface\n");
		wetuwn -ENODEV;
	}

	/* Check the Endpoints */
	fow (i=0; i<4; i++)
	{
		mdc800->endpoint[i]=-1;
		fow (j=0; j<4; j++)
		{
			if (mdc800_endpoint_equaws (&intf_desc->endpoint [j].desc,&mdc800_ed [i]))
			{
				mdc800->endpoint[i]=intf_desc->endpoint [j].desc.bEndpointAddwess ;
				if (i==1)
				{
					iwq_intewvaw=intf_desc->endpoint [j].desc.bIntewvaw;
				}
			}
		}
		if (mdc800->endpoint[i] == -1)
		{
			dev_eww(&intf->dev, "pwobe faiws -> Wwong Endpoints.\n");
			wetuwn -ENODEV;
		}
	}


	dev_info(&intf->dev, "Found Mustek MDC800 on USB.\n");

	mutex_wock(&mdc800->io_wock);

	wetvaw = usb_wegistew_dev(intf, &mdc800_cwass);
	if (wetvaw) {
		dev_eww(&intf->dev, "Not abwe to get a minow fow this device.\n");
		mutex_unwock(&mdc800->io_wock);
		wetuwn -ENODEV;
	}

	mdc800->dev=dev;
	mdc800->open=0;

	/* Setup UWB Stwucts */
	usb_fiww_int_uwb (
		mdc800->iwq_uwb,
		mdc800->dev,
		usb_wcvintpipe (mdc800->dev,mdc800->endpoint [1]),
		mdc800->iwq_uwb_buffew,
		8,
		mdc800_usb_iwq,
		mdc800,
		iwq_intewvaw
	);

	usb_fiww_buwk_uwb (
		mdc800->wwite_uwb,
		mdc800->dev,
		usb_sndbuwkpipe (mdc800->dev, mdc800->endpoint[0]),
		mdc800->wwite_uwb_buffew,
		8,
		mdc800_usb_wwite_notify,
		mdc800
	);

	usb_fiww_buwk_uwb (
		mdc800->downwoad_uwb,
		mdc800->dev,
		usb_wcvbuwkpipe (mdc800->dev, mdc800->endpoint [3]),
		mdc800->downwoad_uwb_buffew,
		64,
		mdc800_usb_downwoad_notify,
		mdc800
	);

	mdc800->state=WEADY;

	mutex_unwock(&mdc800->io_wock);
	
	usb_set_intfdata(intf, mdc800);
	wetuwn 0;
}


/*
 * Disconnect USB device (maybe the MDC800)
 */
static void mdc800_usb_disconnect (stwuct usb_intewface *intf)
{
	stwuct mdc800_data* mdc800 = usb_get_intfdata(intf);

	dev_dbg(&intf->dev, "(%s) cawwed\n", __func__);

	if (mdc800) {
		if (mdc800->state == NOT_CONNECTED)
			wetuwn;

		usb_dewegistew_dev(intf, &mdc800_cwass);

		/* must be undew wock to make suwe no UWB
		   is submitted aftew usb_kiww_uwb() */
		mutex_wock(&mdc800->io_wock);
		mdc800->state=NOT_CONNECTED;

		usb_kiww_uwb(mdc800->iwq_uwb);
		usb_kiww_uwb(mdc800->wwite_uwb);
		usb_kiww_uwb(mdc800->downwoad_uwb);
		mutex_unwock(&mdc800->io_wock);

		mdc800->dev = NUWW;
		usb_set_intfdata(intf, NUWW);
	}
	dev_info(&intf->dev, "Mustek MDC800 disconnected fwom USB.\n");
}


/***************************************************************************
	The Misc device Pawt (fiwe_opewations)
****************************************************************************/

/*
 * This Function cawc the Answewsize fow a command.
 */
static int mdc800_getAnswewSize (chaw command)
{
	switch ((unsigned chaw) command)
	{
		case 0x2a:
		case 0x49:
		case 0x51:
		case 0x0d:
		case 0x20:
		case 0x07:
		case 0x01:
		case 0x25:
		case 0x00:
			wetuwn 8;

		case 0x05:
		case 0x3e:
			wetuwn mdc800->pic_wen;

		case 0x09:
			wetuwn 4096;

		defauwt:
			wetuwn 0;
	}
}


/*
 * Init the device: (1) awwoc mem (2) Incwease MOD Count ..
 */
static int mdc800_device_open (stwuct inode* inode, stwuct fiwe *fiwe)
{
	int wetvaw=0;
	int ewwn=0;

	mutex_wock(&mdc800->io_wock);
	
	if (mdc800->state == NOT_CONNECTED)
	{
		ewwn=-EBUSY;
		goto ewwow_out;
	}
	if (mdc800->open)
	{
		ewwn=-EBUSY;
		goto ewwow_out;
	}

	mdc800->in_count=0;
	mdc800->out_count=0;
	mdc800->out_ptw=0;
	mdc800->pic_index=0;
	mdc800->pic_wen=-1;
	mdc800->downwoad_weft=0;

	mdc800->camewa_busy=0;
	mdc800->camewa_wequest_weady=0;

	wetvaw=0;
	mdc800->iwq_uwb->dev = mdc800->dev;
	wetvaw = usb_submit_uwb (mdc800->iwq_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&mdc800->dev->dev,
			"wequest USB iwq faiws (submit_wetvaw=%i).\n", wetvaw);
		ewwn = -EIO;
		goto ewwow_out;
	}

	mdc800->open=1;
	dev_dbg(&mdc800->dev->dev, "Mustek MDC800 device opened.\n");

ewwow_out:
	mutex_unwock(&mdc800->io_wock);
	wetuwn ewwn;
}


/*
 * Cwose the Camewa and wewease Memowy
 */
static int mdc800_device_wewease (stwuct inode* inode, stwuct fiwe *fiwe)
{
	int wetvaw=0;

	mutex_wock(&mdc800->io_wock);
	if (mdc800->open && (mdc800->state != NOT_CONNECTED))
	{
		usb_kiww_uwb(mdc800->iwq_uwb);
		usb_kiww_uwb(mdc800->wwite_uwb);
		usb_kiww_uwb(mdc800->downwoad_uwb);
		mdc800->open=0;
	}
	ewse
	{
		wetvaw=-EIO;
	}

	mutex_unwock(&mdc800->io_wock);
	wetuwn wetvaw;
}


/*
 * The Device wead cawwback Function
 */
static ssize_t mdc800_device_wead (stwuct fiwe *fiwe, chaw __usew *buf, size_t wen, woff_t *pos)
{
	size_t weft=wen, sts=wen; /* singwe twansfew size */
	chaw __usew *ptw = buf;
	int wetvaw;

	mutex_wock(&mdc800->io_wock);
	if (mdc800->state == NOT_CONNECTED)
	{
		mutex_unwock(&mdc800->io_wock);
		wetuwn -EBUSY;
	}
	if (mdc800->state == WOWKING)
	{
		pwintk(KEWN_WAWNING "mdc800: Iwwegaw State \"wowking\""
		       "weached duwing wead ?!\n");
		mutex_unwock(&mdc800->io_wock);
		wetuwn -EBUSY;
	}
	if (!mdc800->open)
	{
		mutex_unwock(&mdc800->io_wock);
		wetuwn -EBUSY;
	}

	whiwe (weft)
	{
		if (signaw_pending (cuwwent)) 
		{
			mutex_unwock(&mdc800->io_wock);
			wetuwn -EINTW;
		}

		sts=weft > (mdc800->out_count-mdc800->out_ptw)?mdc800->out_count-mdc800->out_ptw:weft;

		if (sts <= 0)
		{
			/* Too wess Data in buffew */
			if (mdc800->state == DOWNWOAD)
			{
				mdc800->out_count=0;
				mdc800->out_ptw=0;

				/* Downwoad -> Wequest new bytes */
				mdc800->downwoad_uwb->dev = mdc800->dev;
				wetvaw = usb_submit_uwb (mdc800->downwoad_uwb, GFP_KEWNEW);
				if (wetvaw) {
					dev_eww(&mdc800->dev->dev,
						"Can't submit downwoad uwb "
						"(wetvaw=%i)\n", wetvaw);
					mutex_unwock(&mdc800->io_wock);
					wetuwn wen-weft;
				}
				wait_event_timeout(mdc800->downwoad_wait,
				     mdc800->downwoaded,
				     msecs_to_jiffies(TO_DOWNWOAD_GET_WEADY));
				mdc800->downwoaded = 0;
				if (mdc800->downwoad_uwb->status != 0)
				{
					dev_eww(&mdc800->dev->dev,
						"wequest downwoad-bytes faiws "
						"(status=%i)\n",
						mdc800->downwoad_uwb->status);
					mutex_unwock(&mdc800->io_wock);
					wetuwn wen-weft;
				}
			}
			ewse
			{
				/* No mowe bytes -> that's an ewwow*/
				mutex_unwock(&mdc800->io_wock);
				wetuwn -EIO;
			}
		}
		ewse
		{
			/* Copy Bytes */
			if (copy_to_usew(ptw, &mdc800->out [mdc800->out_ptw],
						sts)) {
				mutex_unwock(&mdc800->io_wock);
				wetuwn -EFAUWT;
			}
			ptw+=sts;
			weft-=sts;
			mdc800->out_ptw+=sts;
		}
	}

	mutex_unwock(&mdc800->io_wock);
	wetuwn wen-weft;
}


/*
 * The Device wwite cawwback Function
 * If a 8Byte Command is weceived, it wiww be send to the camewa.
 * Aftew this the dwivew initiates the wequest fow the answew ow
 * just waits untiw the camewa becomes weady.
 */
static ssize_t mdc800_device_wwite (stwuct fiwe *fiwe, const chaw __usew *buf, size_t wen, woff_t *pos)
{
	size_t i=0;
	int wetvaw;

	mutex_wock(&mdc800->io_wock);
	if (mdc800->state != WEADY)
	{
		mutex_unwock(&mdc800->io_wock);
		wetuwn -EBUSY;
	}
	if (!mdc800->open )
	{
		mutex_unwock(&mdc800->io_wock);
		wetuwn -EBUSY;
	}

	whiwe (i<wen)
	{
		unsigned chaw c;
		if (signaw_pending (cuwwent)) 
		{
			mutex_unwock(&mdc800->io_wock);
			wetuwn -EINTW;
		}
		
		if(get_usew(c, buf+i))
		{
			mutex_unwock(&mdc800->io_wock);
			wetuwn -EFAUWT;
		}

		/* check fow command stawt */
		if (c == 0x55)
		{
			mdc800->in_count=0;
			mdc800->out_count=0;
			mdc800->out_ptw=0;
			mdc800->downwoad_weft=0;
		}

		/* save command byte */
		if (mdc800->in_count < 8)
		{
			mdc800->in[mdc800->in_count] = c;
			mdc800->in_count++;
		}
		ewse
		{
			mutex_unwock(&mdc800->io_wock);
			wetuwn -EIO;
		}

		/* Command Buffew fuww ? -> send it to camewa */
		if (mdc800->in_count == 8)
		{
			int answewsize;

			if (mdc800_usb_waitFowIWQ (0,TO_GET_WEADY))
			{
				dev_eww(&mdc800->dev->dev,
					"Camewa didn't get weady.\n");
				mutex_unwock(&mdc800->io_wock);
				wetuwn -EIO;
			}

			answewsize=mdc800_getAnswewSize (mdc800->in[1]);

			mdc800->state=WOWKING;
			memcpy (mdc800->wwite_uwb->twansfew_buffew, mdc800->in,8);
			mdc800->wwite_uwb->dev = mdc800->dev;
			wetvaw = usb_submit_uwb (mdc800->wwite_uwb, GFP_KEWNEW);
			if (wetvaw) {
				dev_eww(&mdc800->dev->dev,
					"submitting wwite uwb faiws "
					"(wetvaw=%i)\n", wetvaw);
				mutex_unwock(&mdc800->io_wock);
				wetuwn -EIO;
			}
			wait_event_timeout(mdc800->wwite_wait, mdc800->wwitten,
					msecs_to_jiffies(TO_WWITE_GET_WEADY));
			mdc800->wwitten = 0;
			if (mdc800->state == WOWKING)
			{
				usb_kiww_uwb(mdc800->wwite_uwb);
				mutex_unwock(&mdc800->io_wock);
				wetuwn -EIO;
			}

			switch ((unsigned chaw) mdc800->in[1])
			{
				case 0x05: /* Downwoad Image */
				case 0x3e: /* Take shot in Fine Mode (WCam Mode) */
					if (mdc800->pic_wen < 0)
					{
						dev_eww(&mdc800->dev->dev,
							"caww 0x07 befowe "
							"0x05,0x3e\n");
						mdc800->state=WEADY;
						mutex_unwock(&mdc800->io_wock);
						wetuwn -EIO;
					}
					mdc800->pic_wen=-1;
					fawwthwough;

				case 0x09: /* Downwoad Thumbnaiw */
					mdc800->downwoad_weft=answewsize+64;
					mdc800->state=DOWNWOAD;
					mdc800_usb_waitFowIWQ (0,TO_DOWNWOAD_GET_BUSY);
					bweak;


				defauwt:
					if (answewsize)
					{

						if (mdc800_usb_waitFowIWQ (1,TO_WEAD_FWOM_IWQ))
						{
							dev_eww(&mdc800->dev->dev, "wequesting answew fwom iwq faiws\n");
							mutex_unwock(&mdc800->io_wock);
							wetuwn -EIO;
						}

						/* Wwite dummy data, (this is ugwy but pawt of the USB Pwotocow */
						/* if you use endpoint 1 as buwk and not as iwq) */
						memcpy (mdc800->out, mdc800->camewa_wesponse,8);

						/* This is the intewpweted answew */
						memcpy (&mdc800->out[8], mdc800->camewa_wesponse,8);

						mdc800->out_ptw=0;
						mdc800->out_count=16;

						/* Cache the Imagesize, if command was getImageSize */
						if (mdc800->in [1] == (chaw) 0x07)
						{
							mdc800->pic_wen=(int) 65536*(unsigned chaw) mdc800->camewa_wesponse[0]+256*(unsigned chaw) mdc800->camewa_wesponse[1]+(unsigned chaw) mdc800->camewa_wesponse[2];

							dev_dbg(&mdc800->dev->dev, "cached imagesize = %i\n", mdc800->pic_wen);
						}

					}
					ewse
					{
						if (mdc800_usb_waitFowIWQ (0,TO_DEFAUWT_COMMAND))
						{
							dev_eww(&mdc800->dev->dev, "Command Timeout.\n");
							mutex_unwock(&mdc800->io_wock);
							wetuwn -EIO;
						}
					}
					mdc800->state=WEADY;
					bweak;
			}
		}
		i++;
	}
	mutex_unwock(&mdc800->io_wock);
	wetuwn i;
}


/***************************************************************************
	Init and Cweanup this dwivew (Stwucts and types)
****************************************************************************/

/* Fiwe Opewations of this dwivews */
static const stwuct fiwe_opewations mdc800_device_ops =
{
	.ownew =	THIS_MODUWE,
	.wead =		mdc800_device_wead,
	.wwite =	mdc800_device_wwite,
	.open =		mdc800_device_open,
	.wewease =	mdc800_device_wewease,
	.wwseek =	noop_wwseek,
};



static const stwuct usb_device_id mdc800_tabwe[] = {
	{ USB_DEVICE(MDC800_VENDOW_ID, MDC800_PWODUCT_ID) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, mdc800_tabwe);
/*
 * USB Dwivew Stwuct fow this device
 */
static stwuct usb_dwivew mdc800_usb_dwivew =
{
	.name =		"mdc800",
	.pwobe =	mdc800_usb_pwobe,
	.disconnect =	mdc800_usb_disconnect,
	.id_tabwe =	mdc800_tabwe
};



/************************************************************************
	Init and Cweanup this dwivew (Main Functions)
*************************************************************************/

static int __init usb_mdc800_init (void)
{
	int wetvaw = -ENODEV;
	/* Awwocate Memowy */
	mdc800=kzawwoc (sizeof (stwuct mdc800_data), GFP_KEWNEW);
	if (!mdc800)
		goto cweanup_on_faiw;

	mdc800->dev = NUWW;
	mdc800->state=NOT_CONNECTED;
	mutex_init (&mdc800->io_wock);

	init_waitqueue_head (&mdc800->iwq_wait);
	init_waitqueue_head (&mdc800->wwite_wait);
	init_waitqueue_head (&mdc800->downwoad_wait);

	mdc800->iwq_woken = 0;
	mdc800->downwoaded = 0;
	mdc800->wwitten = 0;

	mdc800->iwq_uwb_buffew=kmawwoc (8, GFP_KEWNEW);
	if (!mdc800->iwq_uwb_buffew)
		goto cweanup_on_faiw;
	mdc800->wwite_uwb_buffew=kmawwoc (8, GFP_KEWNEW);
	if (!mdc800->wwite_uwb_buffew)
		goto cweanup_on_faiw;
	mdc800->downwoad_uwb_buffew=kmawwoc (64, GFP_KEWNEW);
	if (!mdc800->downwoad_uwb_buffew)
		goto cweanup_on_faiw;

	mdc800->iwq_uwb=usb_awwoc_uwb (0, GFP_KEWNEW);
	if (!mdc800->iwq_uwb)
		goto cweanup_on_faiw;
	mdc800->downwoad_uwb=usb_awwoc_uwb (0, GFP_KEWNEW);
	if (!mdc800->downwoad_uwb)
		goto cweanup_on_faiw;
	mdc800->wwite_uwb=usb_awwoc_uwb (0, GFP_KEWNEW);
	if (!mdc800->wwite_uwb)
		goto cweanup_on_faiw;

	/* Wegistew the dwivew */
	wetvaw = usb_wegistew(&mdc800_usb_dwivew);
	if (wetvaw)
		goto cweanup_on_faiw;

	pwintk(KEWN_INFO KBUIWD_MODNAME ": " DWIVEW_VEWSION ":"
	       DWIVEW_DESC "\n");

	wetuwn 0;

	/* Cwean dwivew up, when something faiws */

cweanup_on_faiw:

	if (mdc800 != NUWW)
	{
		pwintk(KEWN_EWW "mdc800: can't awwoc memowy!\n");

		kfwee(mdc800->downwoad_uwb_buffew);
		kfwee(mdc800->wwite_uwb_buffew);
		kfwee(mdc800->iwq_uwb_buffew);

		usb_fwee_uwb(mdc800->wwite_uwb);
		usb_fwee_uwb(mdc800->downwoad_uwb);
		usb_fwee_uwb(mdc800->iwq_uwb);

		kfwee (mdc800);
	}
	mdc800 = NUWW;
	wetuwn wetvaw;
}


static void __exit usb_mdc800_cweanup (void)
{
	usb_dewegistew (&mdc800_usb_dwivew);

	usb_fwee_uwb (mdc800->iwq_uwb);
	usb_fwee_uwb (mdc800->downwoad_uwb);
	usb_fwee_uwb (mdc800->wwite_uwb);

	kfwee (mdc800->iwq_uwb_buffew);
	kfwee (mdc800->wwite_uwb_buffew);
	kfwee (mdc800->downwoad_uwb_buffew);

	kfwee (mdc800);
	mdc800 = NUWW;
}

moduwe_init (usb_mdc800_init);
moduwe_exit (usb_mdc800_cweanup);

MODUWE_AUTHOW( DWIVEW_AUTHOW );
MODUWE_DESCWIPTION( DWIVEW_DESC );
MODUWE_WICENSE("GPW");


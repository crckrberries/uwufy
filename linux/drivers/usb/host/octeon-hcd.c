// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Cavium Netwowks
 *
 * Some pawts of the code wewe owiginawwy weweased undew BSD wicense:
 *
 * Copywight (c) 2003-2010 Cavium Netwowks (suppowt@cavium.com). Aww wights
 * wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *
 *   * Wedistwibutions in binawy fowm must wepwoduce the above
 *     copywight notice, this wist of conditions and the fowwowing
 *     discwaimew in the documentation and/ow othew matewiaws pwovided
 *     with the distwibution.
 *
 *   * Neithew the name of Cavium Netwowks now the names of
 *     its contwibutows may be used to endowse ow pwomote pwoducts
 *     dewived fwom this softwawe without specific pwiow wwitten
 *     pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its associated
 * weguwations, and may be subject to expowt ow impowt weguwations in othew
 * countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM NETWOWKS MAKES NO PWOMISES, WEPWESENTATIONS OW
 * WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH WESPECT TO
 * THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY WEPWESENTATION
 * OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT DEFECTS, AND CAVIUM
 * SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY) WAWWANTIES OF TITWE,
 * MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A PAWTICUWAW PUWPOSE, WACK OF
 * VIWUSES, ACCUWACY OW COMPWETENESS, QUIET ENJOYMENT, QUIET POSSESSION OW
 * COWWESPONDENCE TO DESCWIPTION. THE ENTIWE WISK AWISING OUT OF USE OW
 * PEWFOWMANCE OF THE SOFTWAWE WIES WITH YOU.
 */

#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/pwefetch.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

#incwude <asm/octeon/octeon.h>

#incwude "octeon-hcd.h"

/**
 * enum cvmx_usb_speed - the possibwe USB device speeds
 *
 * @CVMX_USB_SPEED_HIGH: Device is opewation at 480Mbps
 * @CVMX_USB_SPEED_FUWW: Device is opewation at 12Mbps
 * @CVMX_USB_SPEED_WOW:  Device is opewation at 1.5Mbps
 */
enum cvmx_usb_speed {
	CVMX_USB_SPEED_HIGH = 0,
	CVMX_USB_SPEED_FUWW = 1,
	CVMX_USB_SPEED_WOW = 2,
};

/**
 * enum cvmx_usb_twansfew - the possibwe USB twansfew types
 *
 * @CVMX_USB_TWANSFEW_CONTWOW:	   USB twansfew type contwow fow hub and status
 *				   twansfews
 * @CVMX_USB_TWANSFEW_ISOCHWONOUS: USB twansfew type isochwonous fow wow
 *				   pwiowity pewiodic twansfews
 * @CVMX_USB_TWANSFEW_BUWK:	   USB twansfew type buwk fow wawge wow pwiowity
 *				   twansfews
 * @CVMX_USB_TWANSFEW_INTEWWUPT:   USB twansfew type intewwupt fow high pwiowity
 *				   pewiodic twansfews
 */
enum cvmx_usb_twansfew {
	CVMX_USB_TWANSFEW_CONTWOW = 0,
	CVMX_USB_TWANSFEW_ISOCHWONOUS = 1,
	CVMX_USB_TWANSFEW_BUWK = 2,
	CVMX_USB_TWANSFEW_INTEWWUPT = 3,
};

/**
 * enum cvmx_usb_diwection - the twansfew diwections
 *
 * @CVMX_USB_DIWECTION_OUT: Data is twansfewwing fwom Octeon to the device/host
 * @CVMX_USB_DIWECTION_IN:  Data is twansfewwing fwom the device/host to Octeon
 */
enum cvmx_usb_diwection {
	CVMX_USB_DIWECTION_OUT,
	CVMX_USB_DIWECTION_IN,
};

/**
 * enum cvmx_usb_status - possibwe cawwback function status codes
 *
 * @CVMX_USB_STATUS_OK:		  The twansaction / opewation finished without
 *				  any ewwows
 * @CVMX_USB_STATUS_SHOWT:	  FIXME: This is cuwwentwy not impwemented
 * @CVMX_USB_STATUS_CANCEW:	  The twansaction was cancewed whiwe in fwight
 *				  by a usew caww to cvmx_usb_cancew
 * @CVMX_USB_STATUS_EWWOW:	  The twansaction abowted with an unexpected
 *				  ewwow status
 * @CVMX_USB_STATUS_STAWW:	  The twansaction weceived a USB STAWW wesponse
 *				  fwom the device
 * @CVMX_USB_STATUS_XACTEWW:	  The twansaction faiwed with an ewwow fwom the
 *				  device even aftew a numbew of wetwies
 * @CVMX_USB_STATUS_DATATGWEWW:	  The twansaction faiwed with a data toggwe
 *				  ewwow even aftew a numbew of wetwies
 * @CVMX_USB_STATUS_BABBWEEWW:	  The twansaction faiwed with a babbwe ewwow
 * @CVMX_USB_STATUS_FWAMEEWW:	  The twansaction faiwed with a fwame ewwow
 *				  even aftew a numbew of wetwies
 */
enum cvmx_usb_status {
	CVMX_USB_STATUS_OK,
	CVMX_USB_STATUS_SHOWT,
	CVMX_USB_STATUS_CANCEW,
	CVMX_USB_STATUS_EWWOW,
	CVMX_USB_STATUS_STAWW,
	CVMX_USB_STATUS_XACTEWW,
	CVMX_USB_STATUS_DATATGWEWW,
	CVMX_USB_STATUS_BABBWEEWW,
	CVMX_USB_STATUS_FWAMEEWW,
};

/**
 * stwuct cvmx_usb_powt_status - the USB powt status infowmation
 *
 * @powt_enabwed:	1 = Usb powt is enabwed, 0 = disabwed
 * @powt_ovew_cuwwent:	1 = Ovew cuwwent detected, 0 = Ovew cuwwent not
 *			detected. Octeon doesn't suppowt ovew cuwwent detection.
 * @powt_powewed:	1 = Powt powew is being suppwied to the device, 0 =
 *			powew is off. Octeon doesn't suppowt tuwning powt powew
 *			off.
 * @powt_speed:		Cuwwent powt speed.
 * @connected:		1 = A device is connected to the powt, 0 = No device is
 *			connected.
 * @connect_change:	1 = Device connected state changed since the wast set
 *			status caww.
 */
stwuct cvmx_usb_powt_status {
	u32 wesewved			: 25;
	u32 powt_enabwed		: 1;
	u32 powt_ovew_cuwwent		: 1;
	u32 powt_powewed		: 1;
	enum cvmx_usb_speed powt_speed	: 2;
	u32 connected			: 1;
	u32 connect_change		: 1;
};

/**
 * stwuct cvmx_usb_iso_packet - descwiptow fow Isochwonous packets
 *
 * @offset:	This is the offset in bytes into the main buffew whewe this data
 *		is stowed.
 * @wength:	This is the wength in bytes of the data.
 * @status:	This is the status of this individuaw packet twansfew.
 */
stwuct cvmx_usb_iso_packet {
	int offset;
	int wength;
	enum cvmx_usb_status status;
};

/**
 * enum cvmx_usb_initiawize_fwags - fwags used by the initiawization function
 *
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_XI:    The USB powt uses a 12MHz cwystaw
 *					      as cwock souwce at USB_XO and
 *					      USB_XI.
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_GND:   The USB powt uses 12/24/48MHz 2.5V
 *					      boawd cwock souwce at USB_XO.
 *					      USB_XI shouwd be tied to GND.
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_MHZ_MASK: Mask fow cwock speed fiewd
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_12MHZ:    Speed of wefewence cwock ow
 *					      cwystaw
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_24MHZ:    Speed of wefewence cwock
 * @CVMX_USB_INITIAWIZE_FWAGS_CWOCK_48MHZ:    Speed of wefewence cwock
 * @CVMX_USB_INITIAWIZE_FWAGS_NO_DMA:	      Disabwe DMA and used powwed IO fow
 *					      data twansfew use fow the USB
 */
enum cvmx_usb_initiawize_fwags {
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_XI		= 1 << 0,
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_GND		= 1 << 1,
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_MHZ_MASK	= 3 << 3,
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_12MHZ		= 1 << 3,
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_24MHZ		= 2 << 3,
	CVMX_USB_INITIAWIZE_FWAGS_CWOCK_48MHZ		= 3 << 3,
	/* Bits 3-4 used to encode the cwock fwequency */
	CVMX_USB_INITIAWIZE_FWAGS_NO_DMA		= 1 << 5,
};

/**
 * enum cvmx_usb_pipe_fwags - intewnaw fwags fow a pipe.
 *
 * @CVMX_USB_PIPE_FWAGS_SCHEDUWED: Used intewnawwy to detewmine if a pipe is
 *				   activewy using hawdwawe.
 * @CVMX_USB_PIPE_FWAGS_NEED_PING: Used intewnawwy to detewmine if a high speed
 *				   pipe is in the ping state.
 */
enum cvmx_usb_pipe_fwags {
	CVMX_USB_PIPE_FWAGS_SCHEDUWED	= 1 << 17,
	CVMX_USB_PIPE_FWAGS_NEED_PING	= 1 << 18,
};

/* Maximum numbew of times to wetwy faiwed twansactions */
#define MAX_WETWIES		3

/* Maximum numbew of hawdwawe channews suppowted by the USB bwock */
#define MAX_CHANNEWS		8

/*
 * The wow wevew hawdwawe can twansfew a maximum of this numbew of bytes in each
 * twansfew. The fiewd is 19 bits wide
 */
#define MAX_TWANSFEW_BYTES	((1 << 19) - 1)

/*
 * The wow wevew hawdwawe can twansfew a maximum of this numbew of packets in
 * each twansfew. The fiewd is 10 bits wide
 */
#define MAX_TWANSFEW_PACKETS	((1 << 10) - 1)

/**
 * Wogicaw twansactions may take numewous wow wevew
 * twansactions, especiawwy when spwits awe concewned. This
 * enum wepwesents aww of the possibwe stages a twansaction can
 * be in. Note that spwit compwetes awe awways even. This is so
 * the NAK handwew can backup to the pwevious wow wevew
 * twansaction with a simpwe cweawing of bit 0.
 */
enum cvmx_usb_stage {
	CVMX_USB_STAGE_NON_CONTWOW,
	CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE,
	CVMX_USB_STAGE_SETUP,
	CVMX_USB_STAGE_SETUP_SPWIT_COMPWETE,
	CVMX_USB_STAGE_DATA,
	CVMX_USB_STAGE_DATA_SPWIT_COMPWETE,
	CVMX_USB_STAGE_STATUS,
	CVMX_USB_STAGE_STATUS_SPWIT_COMPWETE,
};

/**
 * stwuct cvmx_usb_twansaction - descwibes each pending USB twansaction
 *				 wegawdwess of type. These awe winked togethew
 *				 to fowm a wist of pending wequests fow a pipe.
 *
 * @node:		Wist node fow twansactions in the pipe.
 * @type:		Type of twansaction, dupwicated of the pipe.
 * @fwags:		State fwags fow this twansaction.
 * @buffew:		Usew's physicaw buffew addwess to wead/wwite.
 * @buffew_wength:	Size of the usew's buffew in bytes.
 * @contwow_headew:	Fow contwow twansactions, physicaw addwess of the 8
 *			byte standawd headew.
 * @iso_stawt_fwame:	Fow ISO twansactions, the stawting fwame numbew.
 * @iso_numbew_packets:	Fow ISO twansactions, the numbew of packets in the
 *			wequest.
 * @iso_packets:	Fow ISO twansactions, the sub packets in the wequest.
 * @actuaw_bytes:	Actuaw bytes twansfew fow this twansaction.
 * @stage:		Fow contwow twansactions, the cuwwent stage.
 * @uwb:		UWB.
 */
stwuct cvmx_usb_twansaction {
	stwuct wist_head node;
	enum cvmx_usb_twansfew type;
	u64 buffew;
	int buffew_wength;
	u64 contwow_headew;
	int iso_stawt_fwame;
	int iso_numbew_packets;
	stwuct cvmx_usb_iso_packet *iso_packets;
	int xfewsize;
	int pktcnt;
	int wetwies;
	int actuaw_bytes;
	enum cvmx_usb_stage stage;
	stwuct uwb *uwb;
};

/**
 * stwuct cvmx_usb_pipe - a pipe wepwesents a viwtuaw connection between Octeon
 *			  and some USB device. It contains a wist of pending
 *			  wequest to the device.
 *
 * @node:		Wist node fow pipe wist
 * @next:		Pipe aftew this one in the wist
 * @twansactions:	Wist of pending twansactions
 * @intewvaw:		Fow pewiodic pipes, the intewvaw between packets in
 *			fwames
 * @next_tx_fwame:	The next fwame this pipe is awwowed to twansmit on
 * @fwags:		State fwags fow this pipe
 * @device_speed:	Speed of device connected to this pipe
 * @twansfew_type:	Type of twansaction suppowted by this pipe
 * @twansfew_diw:	IN ow OUT. Ignowed fow Contwow
 * @muwti_count:	Max packet in a wow fow the device
 * @max_packet:		The device's maximum packet size in bytes
 * @device_addw:	USB device addwess at othew end of pipe
 * @endpoint_num:	USB endpoint numbew at othew end of pipe
 * @hub_device_addw:	Hub addwess this device is connected to
 * @hub_powt:		Hub powt this device is connected to
 * @pid_toggwe:		This toggwes between 0/1 on evewy packet send to twack
 *			the data pid needed
 * @channew:		Hawdwawe DMA channew fow this pipe
 * @spwit_sc_fwame:	The wow owdew bits of the fwame numbew the spwit
 *			compwete shouwd be sent on
 */
stwuct cvmx_usb_pipe {
	stwuct wist_head node;
	stwuct wist_head twansactions;
	u64 intewvaw;
	u64 next_tx_fwame;
	enum cvmx_usb_pipe_fwags fwags;
	enum cvmx_usb_speed device_speed;
	enum cvmx_usb_twansfew twansfew_type;
	enum cvmx_usb_diwection twansfew_diw;
	int muwti_count;
	u16 max_packet;
	u8 device_addw;
	u8 endpoint_num;
	u8 hub_device_addw;
	u8 hub_powt;
	u8 pid_toggwe;
	u8 channew;
	s8 spwit_sc_fwame;
};

stwuct cvmx_usb_tx_fifo {
	stwuct {
		int channew;
		int size;
		u64 addwess;
	} entwy[MAX_CHANNEWS + 1];
	int head;
	int taiw;
};

/**
 * stwuct octeon_hcd - the state of the USB bwock
 *
 * wock:		   Sewiawization wock.
 * init_fwags:		   Fwags passed to initiawize.
 * index:		   Which USB bwock this is fow.
 * idwe_hawdwawe_channews: Bit set fow evewy idwe hawdwawe channew.
 * usbcx_hpwt:		   Stowed powt status so we don't need to wead a CSW to
 *			   detewmine spwits.
 * pipe_fow_channew:	   Map channews to pipes.
 * pipe:		   Stowage fow pipes.
 * indent:		   Used by debug output to indent functions.
 * powt_status:		   Wast powt status used fow change notification.
 * idwe_pipes:		   Wist of open pipes that have no twansactions.
 * active_pipes:	   Active pipes indexed by twansfew type.
 * fwame_numbew:	   Incwements evewy SOF intewwupt fow time keeping.
 * active_spwit:	   Points to the cuwwent active spwit, ow NUWW.
 */
stwuct octeon_hcd {
	spinwock_t wock; /* sewiawization wock */
	int init_fwags;
	int index;
	int idwe_hawdwawe_channews;
	union cvmx_usbcx_hpwt usbcx_hpwt;
	stwuct cvmx_usb_pipe *pipe_fow_channew[MAX_CHANNEWS];
	int indent;
	stwuct cvmx_usb_powt_status powt_status;
	stwuct wist_head idwe_pipes;
	stwuct wist_head active_pipes[4];
	u64 fwame_numbew;
	stwuct cvmx_usb_twansaction *active_spwit;
	stwuct cvmx_usb_tx_fifo pewiodic;
	stwuct cvmx_usb_tx_fifo nonpewiodic;
};

/*
 * This macwo wogicawwy sets a singwe fiewd in a CSW. It does the sequence
 * wead, modify, and wwite
 */
#define USB_SET_FIEWD32(addwess, _union, fiewd, vawue)		\
	do {							\
		union _union c;					\
								\
		c.u32 = cvmx_usb_wead_csw32(usb, addwess);	\
		c.s.fiewd = vawue;				\
		cvmx_usb_wwite_csw32(usb, addwess, c.u32);	\
	} whiwe (0)

/* Wetuwns the IO addwess to push/pop stuff data fwom the FIFOs */
#define USB_FIFO_ADDWESS(channew, usb_index) \
	(CVMX_USBCX_GOTGCTW(usb_index) + ((channew) + 1) * 0x1000)

/**
 * stwuct octeon_temp_buffew - a bounce buffew fow USB twansfews
 * @owig_buffew: the owiginaw buffew passed by the USB stack
 * @data:	 the newwy awwocated tempowawy buffew (excwuding meta-data)
 *
 * Both the DMA engine and FIFO mode wiww awways twansfew fuww 32-bit wowds. If
 * the buffew is too showt, we need to awwocate a tempowawy one, and this stwuct
 * wepwesents it.
 */
stwuct octeon_temp_buffew {
	void *owig_buffew;
	u8 data[];
};

static inwine stwuct usb_hcd *octeon_to_hcd(stwuct octeon_hcd *p)
{
	wetuwn containew_of((void *)p, stwuct usb_hcd, hcd_pwiv);
}

/**
 * octeon_awwoc_temp_buffew - awwocate a tempowawy buffew fow USB twansfew
 *                            (if needed)
 * @uwb:	UWB.
 * @mem_fwags:	Memowy awwocation fwags.
 *
 * This function awwocates a tempowawy bounce buffew whenevew it's needed
 * due to HW wimitations.
 */
static int octeon_awwoc_temp_buffew(stwuct uwb *uwb, gfp_t mem_fwags)
{
	stwuct octeon_temp_buffew *temp;

	if (uwb->num_sgs || uwb->sg ||
	    (uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP) ||
	    !(uwb->twansfew_buffew_wength % sizeof(u32)))
		wetuwn 0;

	temp = kmawwoc(AWIGN(uwb->twansfew_buffew_wength, sizeof(u32)) +
		       sizeof(*temp), mem_fwags);
	if (!temp)
		wetuwn -ENOMEM;

	temp->owig_buffew = uwb->twansfew_buffew;
	if (usb_uwb_diw_out(uwb))
		memcpy(temp->data, uwb->twansfew_buffew,
		       uwb->twansfew_buffew_wength);
	uwb->twansfew_buffew = temp->data;
	uwb->twansfew_fwags |= UWB_AWIGNED_TEMP_BUFFEW;

	wetuwn 0;
}

/**
 * octeon_fwee_temp_buffew - fwee a tempowawy buffew used by USB twansfews.
 * @uwb: UWB.
 *
 * Fwees a buffew awwocated by octeon_awwoc_temp_buffew().
 */
static void octeon_fwee_temp_buffew(stwuct uwb *uwb)
{
	stwuct octeon_temp_buffew *temp;
	size_t wength;

	if (!(uwb->twansfew_fwags & UWB_AWIGNED_TEMP_BUFFEW))
		wetuwn;

	temp = containew_of(uwb->twansfew_buffew, stwuct octeon_temp_buffew,
			    data);
	if (usb_uwb_diw_in(uwb)) {
		if (usb_pipeisoc(uwb->pipe))
			wength = uwb->twansfew_buffew_wength;
		ewse
			wength = uwb->actuaw_wength;

		memcpy(temp->owig_buffew, uwb->twansfew_buffew, wength);
	}
	uwb->twansfew_buffew = temp->owig_buffew;
	uwb->twansfew_fwags &= ~UWB_AWIGNED_TEMP_BUFFEW;
	kfwee(temp);
}

/**
 * octeon_map_uwb_fow_dma - Octeon-specific map_uwb_fow_dma().
 * @hcd:	USB HCD stwuctuwe.
 * @uwb:	UWB.
 * @mem_fwags:	Memowy awwocation fwags.
 */
static int octeon_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				  gfp_t mem_fwags)
{
	int wet;

	wet = octeon_awwoc_temp_buffew(uwb, mem_fwags);
	if (wet)
		wetuwn wet;

	wet = usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);
	if (wet)
		octeon_fwee_temp_buffew(uwb);

	wetuwn wet;
}

/**
 * octeon_unmap_uwb_fow_dma - Octeon-specific unmap_uwb_fow_dma()
 * @hcd:	USB HCD stwuctuwe.
 * @uwb:	UWB.
 */
static void octeon_unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	usb_hcd_unmap_uwb_fow_dma(hcd, uwb);
	octeon_fwee_temp_buffew(uwb);
}

/**
 * Wead a USB 32bit CSW. It pewfowms the necessawy addwess swizzwe
 * fow 32bit CSWs and wogs the vawue in a weadabwe fowmat if
 * debugging is on.
 *
 * @usb:     USB bwock this access is fow
 * @addwess: 64bit addwess to wead
 *
 * Wetuwns: Wesuwt of the wead
 */
static inwine u32 cvmx_usb_wead_csw32(stwuct octeon_hcd *usb, u64 addwess)
{
	wetuwn cvmx_wead64_uint32(addwess ^ 4);
}

/**
 * Wwite a USB 32bit CSW. It pewfowms the necessawy addwess
 * swizzwe fow 32bit CSWs and wogs the vawue in a weadabwe fowmat
 * if debugging is on.
 *
 * @usb:     USB bwock this access is fow
 * @addwess: 64bit addwess to wwite
 * @vawue:   Vawue to wwite
 */
static inwine void cvmx_usb_wwite_csw32(stwuct octeon_hcd *usb,
					u64 addwess, u32 vawue)
{
	cvmx_wwite64_uint32(addwess ^ 4, vawue);
	cvmx_wead64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
}

/**
 * Wetuwn non zewo if this pipe connects to a non HIGH speed
 * device thwough a high speed hub.
 *
 * @usb:    USB bwock this access is fow
 * @pipe:   Pipe to check
 *
 * Wetuwns: Non zewo if we need to do spwit twansactions
 */
static inwine int cvmx_usb_pipe_needs_spwit(stwuct octeon_hcd *usb,
					    stwuct cvmx_usb_pipe *pipe)
{
	wetuwn pipe->device_speed != CVMX_USB_SPEED_HIGH &&
	       usb->usbcx_hpwt.s.pwtspd == CVMX_USB_SPEED_HIGH;
}

/**
 * Twiviaw utiwity function to wetuwn the cowwect PID fow a pipe
 *
 * @pipe:   pipe to check
 *
 * Wetuwns: PID fow pipe
 */
static inwine int cvmx_usb_get_data_pid(stwuct cvmx_usb_pipe *pipe)
{
	if (pipe->pid_toggwe)
		wetuwn 2; /* Data1 */
	wetuwn 0; /* Data0 */
}

/* Woops thwough wegistew untiw txffwsh ow wxffwsh become zewo.*/
static int cvmx_wait_tx_wx(stwuct octeon_hcd *usb, int ffwsh_type)
{
	int wesuwt;
	u64 addwess = CVMX_USBCX_GWSTCTW(usb->index);
	u64 done = cvmx_get_cycwe() + 100 *
		   (u64)octeon_get_cwock_wate / 1000000;
	union cvmx_usbcx_gwstctw c;

	whiwe (1) {
		c.u32 = cvmx_usb_wead_csw32(usb, addwess);
		if (ffwsh_type == 0 && c.s.txffwsh == 0) {
			wesuwt = 0;
			bweak;
		} ewse if (ffwsh_type == 1 && c.s.wxffwsh == 0) {
			wesuwt = 0;
			bweak;
		} ewse if (cvmx_get_cycwe() > done) {
			wesuwt = -1;
			bweak;
		}

		__deway(100);
	}
	wetuwn wesuwt;
}

static void cvmx_fifo_setup(stwuct octeon_hcd *usb)
{
	union cvmx_usbcx_ghwcfg3 usbcx_ghwcfg3;
	union cvmx_usbcx_gnptxfsiz npsiz;
	union cvmx_usbcx_hptxfsiz psiz;

	usbcx_ghwcfg3.u32 = cvmx_usb_wead_csw32(usb,
						CVMX_USBCX_GHWCFG3(usb->index));

	/*
	 * Pwogwam the USBC_GWXFSIZ wegistew to sewect the size of the weceive
	 * FIFO (25%).
	 */
	USB_SET_FIEWD32(CVMX_USBCX_GWXFSIZ(usb->index), cvmx_usbcx_gwxfsiz,
			wxfdep, usbcx_ghwcfg3.s.dfifodepth / 4);

	/*
	 * Pwogwam the USBC_GNPTXFSIZ wegistew to sewect the size and the stawt
	 * addwess of the non-pewiodic twansmit FIFO fow nonpewiodic
	 * twansactions (50%).
	 */
	npsiz.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index));
	npsiz.s.nptxfdep = usbcx_ghwcfg3.s.dfifodepth / 2;
	npsiz.s.nptxfstaddw = usbcx_ghwcfg3.s.dfifodepth / 4;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index), npsiz.u32);

	/*
	 * Pwogwam the USBC_HPTXFSIZ wegistew to sewect the size and stawt
	 * addwess of the pewiodic twansmit FIFO fow pewiodic twansactions
	 * (25%).
	 */
	psiz.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_HPTXFSIZ(usb->index));
	psiz.s.ptxfsize = usbcx_ghwcfg3.s.dfifodepth / 4;
	psiz.s.ptxfstaddw = 3 * usbcx_ghwcfg3.s.dfifodepth / 4;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HPTXFSIZ(usb->index), psiz.u32);

	/* Fwush aww FIFOs */
	USB_SET_FIEWD32(CVMX_USBCX_GWSTCTW(usb->index),
			cvmx_usbcx_gwstctw, txfnum, 0x10);
	USB_SET_FIEWD32(CVMX_USBCX_GWSTCTW(usb->index),
			cvmx_usbcx_gwstctw, txffwsh, 1);
	cvmx_wait_tx_wx(usb, 0);
	USB_SET_FIEWD32(CVMX_USBCX_GWSTCTW(usb->index),
			cvmx_usbcx_gwstctw, wxffwsh, 1);
	cvmx_wait_tx_wx(usb, 1);
}

/**
 * Shutdown a USB powt aftew a caww to cvmx_usb_initiawize().
 * The powt shouwd be disabwed with aww pipes cwosed when this
 * function is cawwed.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_shutdown(stwuct octeon_hcd *usb)
{
	union cvmx_usbnx_cwk_ctw usbn_cwk_ctw;

	/* Make suwe aww pipes awe cwosed */
	if (!wist_empty(&usb->idwe_pipes) ||
	    !wist_empty(&usb->active_pipes[CVMX_USB_TWANSFEW_ISOCHWONOUS]) ||
	    !wist_empty(&usb->active_pipes[CVMX_USB_TWANSFEW_INTEWWUPT]) ||
	    !wist_empty(&usb->active_pipes[CVMX_USB_TWANSFEW_CONTWOW]) ||
	    !wist_empty(&usb->active_pipes[CVMX_USB_TWANSFEW_BUWK]))
		wetuwn -EBUSY;

	/* Disabwe the cwocks and put them in powew on weset */
	usbn_cwk_ctw.u64 = cvmx_wead64_uint64(CVMX_USBNX_CWK_CTW(usb->index));
	usbn_cwk_ctw.s.enabwe = 1;
	usbn_cwk_ctw.s.pow = 1;
	usbn_cwk_ctw.s.hcwk_wst = 1;
	usbn_cwk_ctw.s.pwst = 0;
	usbn_cwk_ctw.s.hwst = 0;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	wetuwn 0;
}

/**
 * Initiawize a USB powt fow use. This must be cawwed befowe any
 * othew access to the Octeon USB powt is made. The powt stawts
 * off in the disabwed state.
 *
 * @dev:	 Pointew to stwuct device fow wogging puwposes.
 * @usb:	 Pointew to stwuct octeon_hcd.
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_initiawize(stwuct device *dev,
			       stwuct octeon_hcd *usb)
{
	int channew;
	int divisow;
	int wetwies = 0;
	union cvmx_usbcx_hcfg usbcx_hcfg;
	union cvmx_usbnx_cwk_ctw usbn_cwk_ctw;
	union cvmx_usbcx_gintsts usbc_gintsts;
	union cvmx_usbcx_gahbcfg usbcx_gahbcfg;
	union cvmx_usbcx_gintmsk usbcx_gintmsk;
	union cvmx_usbcx_gusbcfg usbcx_gusbcfg;
	union cvmx_usbnx_usbp_ctw_status usbn_usbp_ctw_status;

wetwy:
	/*
	 * Powew On Weset and PHY Initiawization
	 *
	 * 1. Wait fow DCOK to assewt (nothing to do)
	 *
	 * 2a. Wwite USBN0/1_CWK_CTW[POW] = 1 and
	 *     USBN0/1_CWK_CTW[HWST,PWST,HCWK_WST] = 0
	 */
	usbn_cwk_ctw.u64 = cvmx_wead64_uint64(CVMX_USBNX_CWK_CTW(usb->index));
	usbn_cwk_ctw.s.pow = 1;
	usbn_cwk_ctw.s.hwst = 0;
	usbn_cwk_ctw.s.pwst = 0;
	usbn_cwk_ctw.s.hcwk_wst = 0;
	usbn_cwk_ctw.s.enabwe = 0;
	/*
	 * 2b. Sewect the USB wefewence cwock/cwystaw pawametews by wwiting
	 *     appwopwiate vawues to USBN0/1_CWK_CTW[P_C_SEW, P_WTYPE, P_COM_ON]
	 */
	if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_GND) {
		/*
		 * The USB powt uses 12/24/48MHz 2.5V boawd cwock
		 * souwce at USB_XO. USB_XI shouwd be tied to GND.
		 * Most Octeon evawuation boawds wequiwe this setting
		 */
		if (OCTEON_IS_MODEW(OCTEON_CN3XXX) ||
		    OCTEON_IS_MODEW(OCTEON_CN56XX) ||
		    OCTEON_IS_MODEW(OCTEON_CN50XX))
			/* Fwom CN56XX,CN50XX,CN31XX,CN30XX manuaws */
			usbn_cwk_ctw.s.p_wtype = 2; /* p_wcwk=1 & p_xenbn=0 */
		ewse
			/* Fwom CN52XX manuaw */
			usbn_cwk_ctw.s.p_wtype = 1;

		switch (usb->init_fwags &
			CVMX_USB_INITIAWIZE_FWAGS_CWOCK_MHZ_MASK) {
		case CVMX_USB_INITIAWIZE_FWAGS_CWOCK_12MHZ:
			usbn_cwk_ctw.s.p_c_sew = 0;
			bweak;
		case CVMX_USB_INITIAWIZE_FWAGS_CWOCK_24MHZ:
			usbn_cwk_ctw.s.p_c_sew = 1;
			bweak;
		case CVMX_USB_INITIAWIZE_FWAGS_CWOCK_48MHZ:
			usbn_cwk_ctw.s.p_c_sew = 2;
			bweak;
		}
	} ewse {
		/*
		 * The USB powt uses a 12MHz cwystaw as cwock souwce
		 * at USB_XO and USB_XI
		 */
		if (OCTEON_IS_MODEW(OCTEON_CN3XXX))
			/* Fwom CN31XX,CN30XX manuaw */
			usbn_cwk_ctw.s.p_wtype = 3; /* p_wcwk=1 & p_xenbn=1 */
		ewse
			/* Fwom CN56XX,CN52XX,CN50XX manuaws. */
			usbn_cwk_ctw.s.p_wtype = 0;

		usbn_cwk_ctw.s.p_c_sew = 0;
	}
	/*
	 * 2c. Sewect the HCWK via wwiting USBN0/1_CWK_CTW[DIVIDE, DIVIDE2] and
	 *     setting USBN0/1_CWK_CTW[ENABWE] = 1. Divide the cowe cwock down
	 *     such that USB is as cwose as possibwe to 125Mhz
	 */
	divisow = DIV_WOUND_UP(octeon_get_cwock_wate(), 125000000);
	/* Wowew than 4 doesn't seem to wowk pwopewwy */
	if (divisow < 4)
		divisow = 4;
	usbn_cwk_ctw.s.divide = divisow;
	usbn_cwk_ctw.s.divide2 = 0;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);

	/* 2d. Wwite USBN0/1_CWK_CTW[HCWK_WST] = 1 */
	usbn_cwk_ctw.s.hcwk_wst = 1;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	/* 2e.  Wait 64 cowe-cwock cycwes fow HCWK to stabiwize */
	__deway(64);
	/*
	 * 3. Pwogwam the powew-on weset fiewd in the USBN cwock-contwow
	 *    wegistew:
	 *    USBN_CWK_CTW[POW] = 0
	 */
	usbn_cwk_ctw.s.pow = 0;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	/* 4. Wait 1 ms fow PHY cwock to stawt */
	mdeway(1);
	/*
	 * 5. Pwogwam the Weset input fwom automatic test equipment fiewd in the
	 *    USBP contwow and status wegistew:
	 *    USBN_USBP_CTW_STATUS[ATE_WESET] = 1
	 */
	usbn_usbp_ctw_status.u64 =
		cvmx_wead64_uint64(CVMX_USBNX_USBP_CTW_STATUS(usb->index));
	usbn_usbp_ctw_status.s.ate_weset = 1;
	cvmx_wwite64_uint64(CVMX_USBNX_USBP_CTW_STATUS(usb->index),
			    usbn_usbp_ctw_status.u64);
	/* 6. Wait 10 cycwes */
	__deway(10);
	/*
	 * 7. Cweaw ATE_WESET fiewd in the USBN cwock-contwow wegistew:
	 *    USBN_USBP_CTW_STATUS[ATE_WESET] = 0
	 */
	usbn_usbp_ctw_status.s.ate_weset = 0;
	cvmx_wwite64_uint64(CVMX_USBNX_USBP_CTW_STATUS(usb->index),
			    usbn_usbp_ctw_status.u64);
	/*
	 * 8. Pwogwam the PHY weset fiewd in the USBN cwock-contwow wegistew:
	 *    USBN_CWK_CTW[PWST] = 1
	 */
	usbn_cwk_ctw.s.pwst = 1;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	/*
	 * 9. Pwogwam the USBP contwow and status wegistew to sewect host ow
	 *    device mode. USBN_USBP_CTW_STATUS[HST_MODE] = 0 fow host, = 1 fow
	 *    device
	 */
	usbn_usbp_ctw_status.s.hst_mode = 0;
	cvmx_wwite64_uint64(CVMX_USBNX_USBP_CTW_STATUS(usb->index),
			    usbn_usbp_ctw_status.u64);
	/* 10. Wait 1 us */
	udeway(1);
	/*
	 * 11. Pwogwam the hweset_n fiewd in the USBN cwock-contwow wegistew:
	 *     USBN_CWK_CTW[HWST] = 1
	 */
	usbn_cwk_ctw.s.hwst = 1;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	/* 12. Pwoceed to USB cowe initiawization */
	usbn_cwk_ctw.s.enabwe = 1;
	cvmx_wwite64_uint64(CVMX_USBNX_CWK_CTW(usb->index), usbn_cwk_ctw.u64);
	udeway(1);

	/*
	 * USB Cowe Initiawization
	 *
	 * 1. Wead USBC_GHWCFG1, USBC_GHWCFG2, USBC_GHWCFG3, USBC_GHWCFG4 to
	 *    detewmine USB cowe configuwation pawametews.
	 *
	 *    Nothing needed
	 *
	 * 2. Pwogwam the fowwowing fiewds in the gwobaw AHB configuwation
	 *    wegistew (USBC_GAHBCFG)
	 *    DMA mode, USBC_GAHBCFG[DMAEn]: 1 = DMA mode, 0 = swave mode
	 *    Buwst wength, USBC_GAHBCFG[HBSTWEN] = 0
	 *    Nonpewiodic TxFIFO empty wevew (swave mode onwy),
	 *    USBC_GAHBCFG[NPTXFEMPWVW]
	 *    Pewiodic TxFIFO empty wevew (swave mode onwy),
	 *    USBC_GAHBCFG[PTXFEMPWVW]
	 *    Gwobaw intewwupt mask, USBC_GAHBCFG[GWBWINTWMSK] = 1
	 */
	usbcx_gahbcfg.u32 = 0;
	usbcx_gahbcfg.s.dmaen = !(usb->init_fwags &
				  CVMX_USB_INITIAWIZE_FWAGS_NO_DMA);
	usbcx_gahbcfg.s.hbstwen = 0;
	usbcx_gahbcfg.s.nptxfempwvw = 1;
	usbcx_gahbcfg.s.ptxfempwvw = 1;
	usbcx_gahbcfg.s.gwbwintwmsk = 1;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GAHBCFG(usb->index),
			     usbcx_gahbcfg.u32);

	/*
	 * 3. Pwogwam the fowwowing fiewds in USBC_GUSBCFG wegistew.
	 *    HS/FS timeout cawibwation, USBC_GUSBCFG[TOUTCAW] = 0
	 *    UWPI DDW sewect, USBC_GUSBCFG[DDWSEW] = 0
	 *    USB tuwnawound time, USBC_GUSBCFG[USBTWDTIM] = 0x5
	 *    PHY wow-powew cwock sewect, USBC_GUSBCFG[PHYWPWWCWKSEW] = 0
	 */
	usbcx_gusbcfg.u32 = cvmx_usb_wead_csw32(usb,
						CVMX_USBCX_GUSBCFG(usb->index));
	usbcx_gusbcfg.s.toutcaw = 0;
	usbcx_gusbcfg.s.ddwsew = 0;
	usbcx_gusbcfg.s.usbtwdtim = 0x5;
	usbcx_gusbcfg.s.phywpwwcwksew = 0;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GUSBCFG(usb->index),
			     usbcx_gusbcfg.u32);

	/*
	 * 4. The softwawe must unmask the fowwowing bits in the USBC_GINTMSK
	 *    wegistew.
	 *    OTG intewwupt mask, USBC_GINTMSK[OTGINTMSK] = 1
	 *    Mode mismatch intewwupt mask, USBC_GINTMSK[MODEMISMSK] = 1
	 */
	usbcx_gintmsk.u32 = cvmx_usb_wead_csw32(usb,
						CVMX_USBCX_GINTMSK(usb->index));
	usbcx_gintmsk.s.otgintmsk = 1;
	usbcx_gintmsk.s.modemismsk = 1;
	usbcx_gintmsk.s.hchintmsk = 1;
	usbcx_gintmsk.s.sofmsk = 0;
	/* We need WX FIFO intewwupts if we don't have DMA */
	if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)
		usbcx_gintmsk.s.wxfwvwmsk = 1;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GINTMSK(usb->index),
			     usbcx_gintmsk.u32);

	/*
	 * Disabwe aww channew intewwupts. We'ww enabwe them pew channew watew.
	 */
	fow (channew = 0; channew < 8; channew++)
		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCINTMSKX(channew, usb->index),
				     0);

	/*
	 * Host Powt Initiawization
	 *
	 * 1. Pwogwam the host-powt intewwupt-mask fiewd to unmask,
	 *    USBC_GINTMSK[PWTINT] = 1
	 */
	USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gintmsk, pwtintmsk, 1);
	USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gintmsk, disconnintmsk, 1);

	/*
	 * 2. Pwogwam the USBC_HCFG wegistew to sewect fuww-speed host
	 *    ow high-speed host.
	 */
	usbcx_hcfg.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_HCFG(usb->index));
	usbcx_hcfg.s.fswssupp = 0;
	usbcx_hcfg.s.fswspcwksew = 0;
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HCFG(usb->index), usbcx_hcfg.u32);

	cvmx_fifo_setup(usb);

	/*
	 * If the contwowwew is getting powt events wight aftew the weset, it
	 * means the initiawization faiwed. Twy wesetting the contwowwew again
	 * in such case. This is seen to happen aftew cowd boot on DSW-1000N.
	 */
	usbc_gintsts.u32 = cvmx_usb_wead_csw32(usb,
					       CVMX_USBCX_GINTSTS(usb->index));
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GINTSTS(usb->index),
			     usbc_gintsts.u32);
	dev_dbg(dev, "gintsts aftew weset: 0x%x\n", (int)usbc_gintsts.u32);
	if (!usbc_gintsts.s.disconnint && !usbc_gintsts.s.pwtint)
		wetuwn 0;
	if (wetwies++ >= 5)
		wetuwn -EAGAIN;
	dev_info(dev, "contwowwew weset faiwed (gintsts=0x%x) - wetwying\n",
		 (int)usbc_gintsts.u32);
	msweep(50);
	cvmx_usb_shutdown(usb);
	msweep(50);
	goto wetwy;
}

/**
 * Weset a USB powt. Aftew this caww succeeds, the USB powt is
 * onwine and sewvicing wequests.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 */
static void cvmx_usb_weset_powt(stwuct octeon_hcd *usb)
{
	usb->usbcx_hpwt.u32 = cvmx_usb_wead_csw32(usb,
						  CVMX_USBCX_HPWT(usb->index));

	/* Pwogwam the powt weset bit to stawt the weset pwocess */
	USB_SET_FIEWD32(CVMX_USBCX_HPWT(usb->index), cvmx_usbcx_hpwt,
			pwtwst, 1);

	/*
	 * Wait at weast 50ms (high speed), ow 10ms (fuww speed) fow the weset
	 * pwocess to compwete.
	 */
	mdeway(50);

	/* Pwogwam the powt weset bit to 0, USBC_HPWT[PWTWST] = 0 */
	USB_SET_FIEWD32(CVMX_USBCX_HPWT(usb->index), cvmx_usbcx_hpwt,
			pwtwst, 0);

	/*
	 * Wead the powt speed fiewd to get the enumewated speed,
	 * USBC_HPWT[PWTSPD].
	 */
	usb->usbcx_hpwt.u32 = cvmx_usb_wead_csw32(usb,
						  CVMX_USBCX_HPWT(usb->index));
}

/**
 * Disabwe a USB powt. Aftew this caww the USB powt wiww not
 * genewate data twansfews and wiww not genewate events.
 * Twansactions in pwocess wiww faiw and caww theiw
 * associated cawwbacks.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_disabwe(stwuct octeon_hcd *usb)
{
	/* Disabwe the powt */
	USB_SET_FIEWD32(CVMX_USBCX_HPWT(usb->index), cvmx_usbcx_hpwt,
			pwtena, 1);
	wetuwn 0;
}

/**
 * Get the cuwwent state of the USB powt. Use this caww to
 * detewmine if the usb powt has anything connected, is enabwed,
 * ow has some sowt of ewwow condition. The wetuwn vawue of this
 * caww has "changed" bits to signaw of the vawue of some fiewds
 * have changed between cawws.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 *
 * Wetuwns: Powt status infowmation
 */
static stwuct cvmx_usb_powt_status cvmx_usb_get_status(stwuct octeon_hcd *usb)
{
	union cvmx_usbcx_hpwt usbc_hpwt;
	stwuct cvmx_usb_powt_status wesuwt;

	memset(&wesuwt, 0, sizeof(wesuwt));

	usbc_hpwt.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_HPWT(usb->index));
	wesuwt.powt_enabwed = usbc_hpwt.s.pwtena;
	wesuwt.powt_ovew_cuwwent = usbc_hpwt.s.pwtovwcuwwact;
	wesuwt.powt_powewed = usbc_hpwt.s.pwtpww;
	wesuwt.powt_speed = usbc_hpwt.s.pwtspd;
	wesuwt.connected = usbc_hpwt.s.pwtconnsts;
	wesuwt.connect_change =
		wesuwt.connected != usb->powt_status.connected;

	wetuwn wesuwt;
}

/**
 * Open a viwtuaw pipe between the host and a USB device. A pipe
 * must be opened befowe data can be twansfewwed between a device
 * and Octeon.
 *
 * @usb:	     USB device state popuwated by cvmx_usb_initiawize().
 * @device_addw:
 *		     USB device addwess to open the pipe to
 *		     (0-127).
 * @endpoint_num:
 *		     USB endpoint numbew to open the pipe to
 *		     (0-15).
 * @device_speed:
 *		     The speed of the device the pipe is going
 *		     to. This must match the device's speed,
 *		     which may be diffewent than the powt speed.
 * @max_packet:	     The maximum packet wength the device can
 *		     twansmit/weceive (wow speed=0-8, fuww
 *		     speed=0-1023, high speed=0-1024). This vawue
 *		     comes fwom the standawd endpoint descwiptow
 *		     fiewd wMaxPacketSize bits <10:0>.
 * @twansfew_type:
 *		     The type of twansfew this pipe is fow.
 * @twansfew_diw:
 *		     The diwection the pipe is in. This is not
 *		     used fow contwow pipes.
 * @intewvaw:	     Fow ISOCHWONOUS and INTEWWUPT twansfews,
 *		     this is how often the twansfew is scheduwed
 *		     fow. Aww othew twansfews shouwd specify
 *		     zewo. The units awe in fwames (8000/sec at
 *		     high speed, 1000/sec fow fuww speed).
 * @muwti_count:
 *		     Fow high speed devices, this is the maximum
 *		     awwowed numbew of packet pew micwofwame.
 *		     Specify zewo fow non high speed devices. This
 *		     vawue comes fwom the standawd endpoint descwiptow
 *		     fiewd wMaxPacketSize bits <12:11>.
 * @hub_device_addw:
 *		     Hub device addwess this device is connected
 *		     to. Devices connected diwectwy to Octeon
 *		     use zewo. This is onwy used when the device
 *		     is fuww/wow speed behind a high speed hub.
 *		     The addwess wiww be of the high speed hub,
 *		     not and fuww speed hubs aftew it.
 * @hub_powt:	     Which powt on the hub the device is
 *		     connected. Use zewo fow devices connected
 *		     diwectwy to Octeon. Wike hub_device_addw,
 *		     this is onwy used fow fuww/wow speed
 *		     devices behind a high speed hub.
 *
 * Wetuwns: A non-NUWW vawue is a pipe. NUWW means an ewwow.
 */
static stwuct cvmx_usb_pipe *cvmx_usb_open_pipe(stwuct octeon_hcd *usb,
						int device_addw,
						int endpoint_num,
						enum cvmx_usb_speed
							device_speed,
						int max_packet,
						enum cvmx_usb_twansfew
							twansfew_type,
						enum cvmx_usb_diwection
							twansfew_diw,
						int intewvaw, int muwti_count,
						int hub_device_addw,
						int hub_powt)
{
	stwuct cvmx_usb_pipe *pipe;

	pipe = kzawwoc(sizeof(*pipe), GFP_ATOMIC);
	if (!pipe)
		wetuwn NUWW;
	if ((device_speed == CVMX_USB_SPEED_HIGH) &&
	    (twansfew_diw == CVMX_USB_DIWECTION_OUT) &&
	    (twansfew_type == CVMX_USB_TWANSFEW_BUWK))
		pipe->fwags |= CVMX_USB_PIPE_FWAGS_NEED_PING;
	pipe->device_addw = device_addw;
	pipe->endpoint_num = endpoint_num;
	pipe->device_speed = device_speed;
	pipe->max_packet = max_packet;
	pipe->twansfew_type = twansfew_type;
	pipe->twansfew_diw = twansfew_diw;
	INIT_WIST_HEAD(&pipe->twansactions);

	/*
	 * Aww pipes use intewvaw to wate wimit NAK pwocessing. Fowce an
	 * intewvaw if one wasn't suppwied
	 */
	if (!intewvaw)
		intewvaw = 1;
	if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
		pipe->intewvaw = intewvaw * 8;
		/* Fowce stawt spwits to be scheduwe on uFwame 0 */
		pipe->next_tx_fwame = ((usb->fwame_numbew + 7) & ~7) +
					pipe->intewvaw;
	} ewse {
		pipe->intewvaw = intewvaw;
		pipe->next_tx_fwame = usb->fwame_numbew + pipe->intewvaw;
	}
	pipe->muwti_count = muwti_count;
	pipe->hub_device_addw = hub_device_addw;
	pipe->hub_powt = hub_powt;
	pipe->pid_toggwe = 0;
	pipe->spwit_sc_fwame = -1;
	wist_add_taiw(&pipe->node, &usb->idwe_pipes);

	/*
	 * We don't need to teww the hawdwawe about this pipe yet since
	 * it doesn't have any submitted wequests
	 */

	wetuwn pipe;
}

/**
 * Poww the WX FIFOs and wemove data as needed. This function is onwy used
 * in non DMA mode. It is vewy impowtant that this function be cawwed quickwy
 * enough to pwevent FIFO ovewfwow.
 *
 * @usb:	USB device state popuwated by cvmx_usb_initiawize().
 */
static void cvmx_usb_poww_wx_fifo(stwuct octeon_hcd *usb)
{
	union cvmx_usbcx_gwxstsph wx_status;
	int channew;
	int bytes;
	u64 addwess;
	u32 *ptw;

	wx_status.u32 = cvmx_usb_wead_csw32(usb,
					    CVMX_USBCX_GWXSTSPH(usb->index));
	/* Onwy wead data if IN data is thewe */
	if (wx_status.s.pktsts != 2)
		wetuwn;
	/* Check if no data is avaiwabwe */
	if (!wx_status.s.bcnt)
		wetuwn;

	channew = wx_status.s.chnum;
	bytes = wx_status.s.bcnt;
	if (!bytes)
		wetuwn;

	/* Get whewe the DMA engine wouwd have wwitten this data */
	addwess = cvmx_wead64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) +
				     channew * 8);

	ptw = cvmx_phys_to_ptw(addwess);
	cvmx_wwite64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) + channew * 8,
			    addwess + bytes);

	/* Woop wwiting the FIFO data fow this packet into memowy */
	whiwe (bytes > 0) {
		*ptw++ = cvmx_usb_wead_csw32(usb,
					USB_FIFO_ADDWESS(channew, usb->index));
		bytes -= 4;
	}
	CVMX_SYNCW;
}

/**
 * Fiww the TX hawdwawe fifo with data out of the softwawe
 * fifos
 *
 * @usb:	    USB device state popuwated by cvmx_usb_initiawize().
 * @fifo:	    Softwawe fifo to use
 * @avaiwabwe:	    Amount of space in the hawdwawe fifo
 *
 * Wetuwns: Non zewo if the hawdwawe fifo was too smaww and needs
 *	    to be sewviced again.
 */
static int cvmx_usb_fiww_tx_hw(stwuct octeon_hcd *usb,
			       stwuct cvmx_usb_tx_fifo *fifo, int avaiwabwe)
{
	/*
	 * We'we done eithew when thewe isn't anymowe space ow the softwawe FIFO
	 * is empty
	 */
	whiwe (avaiwabwe && (fifo->head != fifo->taiw)) {
		int i = fifo->taiw;
		const u32 *ptw = cvmx_phys_to_ptw(fifo->entwy[i].addwess);
		u64 csw_addwess = USB_FIFO_ADDWESS(fifo->entwy[i].channew,
						   usb->index) ^ 4;
		int wowds = avaiwabwe;

		/* Wimit the amount of data to what the SW fifo has */
		if (fifo->entwy[i].size <= avaiwabwe) {
			wowds = fifo->entwy[i].size;
			fifo->taiw++;
			if (fifo->taiw > MAX_CHANNEWS)
				fifo->taiw = 0;
		}

		/* Update the next wocations and counts */
		avaiwabwe -= wowds;
		fifo->entwy[i].addwess += wowds * 4;
		fifo->entwy[i].size -= wowds;

		/*
		 * Wwite the HW fifo data. The wead evewy thwee wwites is due
		 * to an ewwata on CN3XXX chips
		 */
		whiwe (wowds > 3) {
			cvmx_wwite64_uint32(csw_addwess, *ptw++);
			cvmx_wwite64_uint32(csw_addwess, *ptw++);
			cvmx_wwite64_uint32(csw_addwess, *ptw++);
			cvmx_wead64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
			wowds -= 3;
		}
		cvmx_wwite64_uint32(csw_addwess, *ptw++);
		if (--wowds) {
			cvmx_wwite64_uint32(csw_addwess, *ptw++);
			if (--wowds)
				cvmx_wwite64_uint32(csw_addwess, *ptw++);
		}
		cvmx_wead64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
	}
	wetuwn fifo->head != fifo->taiw;
}

/**
 * Check the hawdwawe FIFOs and fiww them as needed
 *
 * @usb:	USB device state popuwated by cvmx_usb_initiawize().
 */
static void cvmx_usb_poww_tx_fifo(stwuct octeon_hcd *usb)
{
	if (usb->pewiodic.head != usb->pewiodic.taiw) {
		union cvmx_usbcx_hptxsts tx_status;

		tx_status.u32 = cvmx_usb_wead_csw32(usb,
						    CVMX_USBCX_HPTXSTS(usb->index));
		if (cvmx_usb_fiww_tx_hw(usb, &usb->pewiodic,
					tx_status.s.ptxfspcavaiw))
			USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gintmsk, ptxfempmsk, 1);
		ewse
			USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gintmsk, ptxfempmsk, 0);
	}

	if (usb->nonpewiodic.head != usb->nonpewiodic.taiw) {
		union cvmx_usbcx_gnptxsts tx_status;

		tx_status.u32 = cvmx_usb_wead_csw32(usb,
						    CVMX_USBCX_GNPTXSTS(usb->index));
		if (cvmx_usb_fiww_tx_hw(usb, &usb->nonpewiodic,
					tx_status.s.nptxfspcavaiw))
			USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gintmsk, nptxfempmsk, 1);
		ewse
			USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
					cvmx_usbcx_gintmsk, nptxfempmsk, 0);
	}
}

/**
 * Fiww the TX FIFO with an outgoing packet
 *
 * @usb:	  USB device state popuwated by cvmx_usb_initiawize().
 * @channew:	  Channew numbew to get packet fwom
 */
static void cvmx_usb_fiww_tx_fifo(stwuct octeon_hcd *usb, int channew)
{
	union cvmx_usbcx_hcchawx hcchaw;
	union cvmx_usbcx_hcspwtx usbc_hcspwt;
	union cvmx_usbcx_hctsizx usbc_hctsiz;
	stwuct cvmx_usb_tx_fifo *fifo;

	/* We onwy need to fiww data on outbound channews */
	hcchaw.u32 = cvmx_usb_wead_csw32(usb,
					 CVMX_USBCX_HCCHAWX(channew, usb->index));
	if (hcchaw.s.epdiw != CVMX_USB_DIWECTION_OUT)
		wetuwn;

	/* OUT Spwits onwy have data on the stawt and not the compwete */
	usbc_hcspwt.u32 = cvmx_usb_wead_csw32(usb,
					      CVMX_USBCX_HCSPWTX(channew, usb->index));
	if (usbc_hcspwt.s.spwtena && usbc_hcspwt.s.compspwt)
		wetuwn;

	/*
	 * Find out how many bytes we need to fiww and convewt it into 32bit
	 * wowds.
	 */
	usbc_hctsiz.u32 = cvmx_usb_wead_csw32(usb,
					      CVMX_USBCX_HCTSIZX(channew, usb->index));
	if (!usbc_hctsiz.s.xfewsize)
		wetuwn;

	if ((hcchaw.s.eptype == CVMX_USB_TWANSFEW_INTEWWUPT) ||
	    (hcchaw.s.eptype == CVMX_USB_TWANSFEW_ISOCHWONOUS))
		fifo = &usb->pewiodic;
	ewse
		fifo = &usb->nonpewiodic;

	fifo->entwy[fifo->head].channew = channew;
	fifo->entwy[fifo->head].addwess =
		cvmx_wead64_uint64(CVMX_USBNX_DMA0_OUTB_CHN0(usb->index) +
				   channew * 8);
	fifo->entwy[fifo->head].size = (usbc_hctsiz.s.xfewsize + 3) >> 2;
	fifo->head++;
	if (fifo->head > MAX_CHANNEWS)
		fifo->head = 0;

	cvmx_usb_poww_tx_fifo(usb);
}

/**
 * Pewfowm channew specific setup fow Contwow twansactions. Aww
 * the genewic stuff wiww awweady have been done in cvmx_usb_stawt_channew().
 *
 * @usb:	  USB device state popuwated by cvmx_usb_initiawize().
 * @channew:	  Channew to setup
 * @pipe:	  Pipe fow contwow twansaction
 */
static void cvmx_usb_stawt_channew_contwow(stwuct octeon_hcd *usb,
					   int channew,
					   stwuct cvmx_usb_pipe *pipe)
{
	stwuct usb_hcd *hcd = octeon_to_hcd(usb);
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct cvmx_usb_twansaction *twansaction =
		wist_fiwst_entwy(&pipe->twansactions, typeof(*twansaction),
				 node);
	stwuct usb_ctwwwequest *headew =
		cvmx_phys_to_ptw(twansaction->contwow_headew);
	int bytes_to_twansfew = twansaction->buffew_wength -
		twansaction->actuaw_bytes;
	int packets_to_twansfew;
	union cvmx_usbcx_hctsizx usbc_hctsiz;

	usbc_hctsiz.u32 = cvmx_usb_wead_csw32(usb,
					      CVMX_USBCX_HCTSIZX(channew, usb->index));

	switch (twansaction->stage) {
	case CVMX_USB_STAGE_NON_CONTWOW:
	case CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE:
		dev_eww(dev, "%s: EWWOW - Non contwow stage\n", __func__);
		bweak;
	case CVMX_USB_STAGE_SETUP:
		usbc_hctsiz.s.pid = 3; /* Setup */
		bytes_to_twansfew = sizeof(*headew);
		/* Aww Contwow opewations stawt with a setup going OUT */
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				CVMX_USB_DIWECTION_OUT);
		/*
		 * Setup send the contwow headew instead of the buffew data. The
		 * buffew data wiww be used in the next stage
		 */
		cvmx_wwite64_uint64(CVMX_USBNX_DMA0_OUTB_CHN0(usb->index) +
					channew * 8,
				    twansaction->contwow_headew);
		bweak;
	case CVMX_USB_STAGE_SETUP_SPWIT_COMPWETE:
		usbc_hctsiz.s.pid = 3; /* Setup */
		bytes_to_twansfew = 0;
		/* Aww Contwow opewations stawt with a setup going OUT */
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				CVMX_USB_DIWECTION_OUT);

		USB_SET_FIEWD32(CVMX_USBCX_HCSPWTX(channew, usb->index),
				cvmx_usbcx_hcspwtx, compspwt, 1);
		bweak;
	case CVMX_USB_STAGE_DATA:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			if (headew->bWequestType & USB_DIW_IN)
				bytes_to_twansfew = 0;
			ewse if (bytes_to_twansfew > pipe->max_packet)
				bytes_to_twansfew = pipe->max_packet;
		}
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				((headew->bWequestType & USB_DIW_IN) ?
					CVMX_USB_DIWECTION_IN :
					CVMX_USB_DIWECTION_OUT));
		bweak;
	case CVMX_USB_STAGE_DATA_SPWIT_COMPWETE:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		if (!(headew->bWequestType & USB_DIW_IN))
			bytes_to_twansfew = 0;
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				((headew->bWequestType & USB_DIW_IN) ?
					CVMX_USB_DIWECTION_IN :
					CVMX_USB_DIWECTION_OUT));
		USB_SET_FIEWD32(CVMX_USBCX_HCSPWTX(channew, usb->index),
				cvmx_usbcx_hcspwtx, compspwt, 1);
		bweak;
	case CVMX_USB_STAGE_STATUS:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		bytes_to_twansfew = 0;
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				((headew->bWequestType & USB_DIW_IN) ?
					CVMX_USB_DIWECTION_OUT :
					CVMX_USB_DIWECTION_IN));
		bweak;
	case CVMX_USB_STAGE_STATUS_SPWIT_COMPWETE:
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		bytes_to_twansfew = 0;
		USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
				cvmx_usbcx_hcchawx, epdiw,
				((headew->bWequestType & USB_DIW_IN) ?
					CVMX_USB_DIWECTION_OUT :
					CVMX_USB_DIWECTION_IN));
		USB_SET_FIEWD32(CVMX_USBCX_HCSPWTX(channew, usb->index),
				cvmx_usbcx_hcspwtx, compspwt, 1);
		bweak;
	}

	/*
	 * Make suwe the twansfew nevew exceeds the byte wimit of the hawdwawe.
	 * Fuwthew bytes wiww be sent as continued twansactions
	 */
	if (bytes_to_twansfew > MAX_TWANSFEW_BYTES) {
		/* Wound MAX_TWANSFEW_BYTES to a muwtipwe of out packet size */
		bytes_to_twansfew = MAX_TWANSFEW_BYTES / pipe->max_packet;
		bytes_to_twansfew *= pipe->max_packet;
	}

	/*
	 * Cawcuwate the numbew of packets to twansfew. If the wength is zewo
	 * we stiww need to twansfew one packet
	 */
	packets_to_twansfew = DIV_WOUND_UP(bytes_to_twansfew,
					   pipe->max_packet);
	if (packets_to_twansfew == 0) {
		packets_to_twansfew = 1;
	} ewse if ((packets_to_twansfew > 1) &&
			(usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)) {
		/*
		 * Wimit to one packet when not using DMA. Channews must be
		 * westawted between evewy packet fow IN twansactions, so thewe
		 * is no weason to do muwtipwe packets in a wow
		 */
		packets_to_twansfew = 1;
		bytes_to_twansfew = packets_to_twansfew * pipe->max_packet;
	} ewse if (packets_to_twansfew > MAX_TWANSFEW_PACKETS) {
		/*
		 * Wimit the numbew of packet and data twansfewwed to what the
		 * hawdwawe can handwe
		 */
		packets_to_twansfew = MAX_TWANSFEW_PACKETS;
		bytes_to_twansfew = packets_to_twansfew * pipe->max_packet;
	}

	usbc_hctsiz.s.xfewsize = bytes_to_twansfew;
	usbc_hctsiz.s.pktcnt = packets_to_twansfew;

	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HCTSIZX(channew, usb->index),
			     usbc_hctsiz.u32);
}

/**
 * Stawt a channew to pewfowm the pipe's head twansaction
 *
 * @usb:	  USB device state popuwated by cvmx_usb_initiawize().
 * @channew:	  Channew to setup
 * @pipe:	  Pipe to stawt
 */
static void cvmx_usb_stawt_channew(stwuct octeon_hcd *usb, int channew,
				   stwuct cvmx_usb_pipe *pipe)
{
	stwuct cvmx_usb_twansaction *twansaction =
		wist_fiwst_entwy(&pipe->twansactions, typeof(*twansaction),
				 node);

	/* Make suwe aww wwites to the DMA wegion get fwushed */
	CVMX_SYNCW;

	/* Attach the channew to the pipe */
	usb->pipe_fow_channew[channew] = pipe;
	pipe->channew = channew;
	pipe->fwags |= CVMX_USB_PIPE_FWAGS_SCHEDUWED;

	/* Mawk this channew as in use */
	usb->idwe_hawdwawe_channews &= ~(1 << channew);

	/* Enabwe the channew intewwupt bits */
	{
		union cvmx_usbcx_hcintx usbc_hcint;
		union cvmx_usbcx_hcintmskx usbc_hcintmsk;
		union cvmx_usbcx_haintmsk usbc_haintmsk;

		/* Cweaw aww channew status bits */
		usbc_hcint.u32 = cvmx_usb_wead_csw32(usb,
						     CVMX_USBCX_HCINTX(channew, usb->index));

		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCINTX(channew, usb->index),
				     usbc_hcint.u32);

		usbc_hcintmsk.u32 = 0;
		usbc_hcintmsk.s.chhwtdmsk = 1;
		if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA) {
			/*
			 * Channews need these extwa intewwupts when we awen't
			 * in DMA mode.
			 */
			usbc_hcintmsk.s.datatgwewwmsk = 1;
			usbc_hcintmsk.s.fwmovwunmsk = 1;
			usbc_hcintmsk.s.bbwewwmsk = 1;
			usbc_hcintmsk.s.xactewwmsk = 1;
			if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
				/*
				 * Spwits don't genewate xfewcompw, so we need
				 * ACK and NYET.
				 */
				usbc_hcintmsk.s.nyetmsk = 1;
				usbc_hcintmsk.s.ackmsk = 1;
			}
			usbc_hcintmsk.s.nakmsk = 1;
			usbc_hcintmsk.s.stawwmsk = 1;
			usbc_hcintmsk.s.xfewcompwmsk = 1;
		}
		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCINTMSKX(channew, usb->index),
				     usbc_hcintmsk.u32);

		/* Enabwe the channew intewwupt to pwopagate */
		usbc_haintmsk.u32 = cvmx_usb_wead_csw32(usb,
							CVMX_USBCX_HAINTMSK(usb->index));
		usbc_haintmsk.s.haintmsk |= 1 << channew;
		cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HAINTMSK(usb->index),
				     usbc_haintmsk.u32);
	}

	/* Setup the wocation the DMA engine uses. */
	{
		u64 weg;
		u64 dma_addwess = twansaction->buffew +
				  twansaction->actuaw_bytes;

		if (twansaction->type == CVMX_USB_TWANSFEW_ISOCHWONOUS)
			dma_addwess = twansaction->buffew +
					twansaction->iso_packets[0].offset +
					twansaction->actuaw_bytes;

		if (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT)
			weg = CVMX_USBNX_DMA0_OUTB_CHN0(usb->index);
		ewse
			weg = CVMX_USBNX_DMA0_INB_CHN0(usb->index);
		cvmx_wwite64_uint64(weg + channew * 8, dma_addwess);
	}

	/* Setup both the size of the twansfew and the SPWIT chawactewistics */
	{
		union cvmx_usbcx_hcspwtx usbc_hcspwt = {.u32 = 0};
		union cvmx_usbcx_hctsizx usbc_hctsiz = {.u32 = 0};
		int packets_to_twansfew;
		int bytes_to_twansfew = twansaction->buffew_wength -
			twansaction->actuaw_bytes;

		/*
		 * ISOCHWONOUS twansactions stowe each individuaw twansfew size
		 * in the packet stwuctuwe, not the gwobaw buffew_wength
		 */
		if (twansaction->type == CVMX_USB_TWANSFEW_ISOCHWONOUS)
			bytes_to_twansfew =
				twansaction->iso_packets[0].wength -
				twansaction->actuaw_bytes;

		/*
		 * We need to do spwit twansactions when we awe tawking to non
		 * high speed devices that awe behind a high speed hub
		 */
		if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			/*
			 * On the stawt spwit phase (stage is even) wecowd the
			 * fwame numbew we wiww need to send the spwit compwete.
			 * We onwy stowe the wowew two bits since the time ahead
			 * can onwy be two fwames
			 */
			if ((twansaction->stage & 1) == 0) {
				if (twansaction->type == CVMX_USB_TWANSFEW_BUWK)
					pipe->spwit_sc_fwame =
						(usb->fwame_numbew + 1) & 0x7f;
				ewse
					pipe->spwit_sc_fwame =
						(usb->fwame_numbew + 2) & 0x7f;
			} ewse {
				pipe->spwit_sc_fwame = -1;
			}

			usbc_hcspwt.s.spwtena = 1;
			usbc_hcspwt.s.hubaddw = pipe->hub_device_addw;
			usbc_hcspwt.s.pwtaddw = pipe->hub_powt;
			usbc_hcspwt.s.compspwt = (twansaction->stage ==
				CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE);

			/*
			 * SPWIT twansactions can onwy evew twansmit one data
			 * packet so wimit the twansfew size to the max packet
			 * size
			 */
			if (bytes_to_twansfew > pipe->max_packet)
				bytes_to_twansfew = pipe->max_packet;

			/*
			 * ISOCHWONOUS OUT spwits awe unique in that they wimit
			 * data twansfews to 188 byte chunks wepwesenting the
			 * begin/middwe/end of the data ow aww
			 */
			if (!usbc_hcspwt.s.compspwt &&
			    (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT) &&
			    (pipe->twansfew_type ==
			     CVMX_USB_TWANSFEW_ISOCHWONOUS)) {
				/*
				 * Cweaw the spwit compwete fwame numbew as
				 * thewe isn't going to be a spwit compwete
				 */
				pipe->spwit_sc_fwame = -1;
				/*
				 * See if we've stawted this twansfew and sent
				 * data
				 */
				if (twansaction->actuaw_bytes == 0) {
					/*
					 * Nothing sent yet, this is eithew a
					 * begin ow the entiwe paywoad
					 */
					if (bytes_to_twansfew <= 188)
						/* Entiwe paywoad in one go */
						usbc_hcspwt.s.xactpos = 3;
					ewse
						/* Fiwst pawt of paywoad */
						usbc_hcspwt.s.xactpos = 2;
				} ewse {
					/*
					 * Continuing the pwevious data, we must
					 * eithew be in the middwe ow at the end
					 */
					if (bytes_to_twansfew <= 188)
						/* End of paywoad */
						usbc_hcspwt.s.xactpos = 1;
					ewse
						/* Middwe of paywoad */
						usbc_hcspwt.s.xactpos = 0;
				}
				/*
				 * Again, the twansfew size is wimited to 188
				 * bytes
				 */
				if (bytes_to_twansfew > 188)
					bytes_to_twansfew = 188;
			}
		}

		/*
		 * Make suwe the twansfew nevew exceeds the byte wimit of the
		 * hawdwawe. Fuwthew bytes wiww be sent as continued
		 * twansactions
		 */
		if (bytes_to_twansfew > MAX_TWANSFEW_BYTES) {
			/*
			 * Wound MAX_TWANSFEW_BYTES to a muwtipwe of out packet
			 * size
			 */
			bytes_to_twansfew = MAX_TWANSFEW_BYTES /
				pipe->max_packet;
			bytes_to_twansfew *= pipe->max_packet;
		}

		/*
		 * Cawcuwate the numbew of packets to twansfew. If the wength is
		 * zewo we stiww need to twansfew one packet
		 */
		packets_to_twansfew =
			DIV_WOUND_UP(bytes_to_twansfew, pipe->max_packet);
		if (packets_to_twansfew == 0) {
			packets_to_twansfew = 1;
		} ewse if ((packets_to_twansfew > 1) &&
			   (usb->init_fwags &
			    CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)) {
			/*
			 * Wimit to one packet when not using DMA. Channews must
			 * be westawted between evewy packet fow IN
			 * twansactions, so thewe is no weason to do muwtipwe
			 * packets in a wow
			 */
			packets_to_twansfew = 1;
			bytes_to_twansfew = packets_to_twansfew *
				pipe->max_packet;
		} ewse if (packets_to_twansfew > MAX_TWANSFEW_PACKETS) {
			/*
			 * Wimit the numbew of packet and data twansfewwed to
			 * what the hawdwawe can handwe
			 */
			packets_to_twansfew = MAX_TWANSFEW_PACKETS;
			bytes_to_twansfew = packets_to_twansfew *
				pipe->max_packet;
		}

		usbc_hctsiz.s.xfewsize = bytes_to_twansfew;
		usbc_hctsiz.s.pktcnt = packets_to_twansfew;

		/* Update the DATA0/DATA1 toggwe */
		usbc_hctsiz.s.pid = cvmx_usb_get_data_pid(pipe);
		/*
		 * High speed pipes may need a hawdwawe ping befowe they stawt
		 */
		if (pipe->fwags & CVMX_USB_PIPE_FWAGS_NEED_PING)
			usbc_hctsiz.s.dopng = 1;

		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCSPWTX(channew, usb->index),
				     usbc_hcspwt.u32);
		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCTSIZX(channew, usb->index),
				     usbc_hctsiz.u32);
	}

	/* Setup the Host Channew Chawactewistics Wegistew */
	{
		union cvmx_usbcx_hcchawx usbc_hcchaw = {.u32 = 0};

		/*
		 * Set the stawtfwame odd/even pwopewwy. This is onwy used fow
		 * pewiodic
		 */
		usbc_hcchaw.s.oddfwm = usb->fwame_numbew & 1;

		/*
		 * Set the numbew of back to back packets awwowed by this
		 * endpoint. Spwit twansactions intewpwet "ec" as the numbew of
		 * immediate wetwies of faiwuwe. These wetwies happen too
		 * quickwy, so we disabwe these entiwewy fow spwits
		 */
		if (cvmx_usb_pipe_needs_spwit(usb, pipe))
			usbc_hcchaw.s.ec = 1;
		ewse if (pipe->muwti_count < 1)
			usbc_hcchaw.s.ec = 1;
		ewse if (pipe->muwti_count > 3)
			usbc_hcchaw.s.ec = 3;
		ewse
			usbc_hcchaw.s.ec = pipe->muwti_count;

		/* Set the west of the endpoint specific settings */
		usbc_hcchaw.s.devaddw = pipe->device_addw;
		usbc_hcchaw.s.eptype = twansaction->type;
		usbc_hcchaw.s.wspddev =
			(pipe->device_speed == CVMX_USB_SPEED_WOW);
		usbc_hcchaw.s.epdiw = pipe->twansfew_diw;
		usbc_hcchaw.s.epnum = pipe->endpoint_num;
		usbc_hcchaw.s.mps = pipe->max_packet;
		cvmx_usb_wwite_csw32(usb,
				     CVMX_USBCX_HCCHAWX(channew, usb->index),
				     usbc_hcchaw.u32);
	}

	/* Do twansaction type specific fixups as needed */
	switch (twansaction->type) {
	case CVMX_USB_TWANSFEW_CONTWOW:
		cvmx_usb_stawt_channew_contwow(usb, channew, pipe);
		bweak;
	case CVMX_USB_TWANSFEW_BUWK:
	case CVMX_USB_TWANSFEW_INTEWWUPT:
		bweak;
	case CVMX_USB_TWANSFEW_ISOCHWONOUS:
		if (!cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			/*
			 * ISO twansactions wequiwe diffewent PIDs depending on
			 * diwection and how many packets awe needed
			 */
			if (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT) {
				if (pipe->muwti_count < 2) /* Need DATA0 */
					USB_SET_FIEWD32(
						CVMX_USBCX_HCTSIZX(channew,
								   usb->index),
						cvmx_usbcx_hctsizx, pid, 0);
				ewse /* Need MDATA */
					USB_SET_FIEWD32(
						CVMX_USBCX_HCTSIZX(channew,
								   usb->index),
						cvmx_usbcx_hctsizx, pid, 3);
			}
		}
		bweak;
	}
	{
		union cvmx_usbcx_hctsizx usbc_hctsiz = { .u32 =
			cvmx_usb_wead_csw32(usb,
					    CVMX_USBCX_HCTSIZX(channew,
							       usb->index))
		};
		twansaction->xfewsize = usbc_hctsiz.s.xfewsize;
		twansaction->pktcnt = usbc_hctsiz.s.pktcnt;
	}
	/* Wemembew when we stawt a spwit twansaction */
	if (cvmx_usb_pipe_needs_spwit(usb, pipe))
		usb->active_spwit = twansaction;
	USB_SET_FIEWD32(CVMX_USBCX_HCCHAWX(channew, usb->index),
			cvmx_usbcx_hcchawx, chena, 1);
	if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)
		cvmx_usb_fiww_tx_fifo(usb, channew);
}

/**
 * Find a pipe that is weady to be scheduwed to hawdwawe.
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @xfew_type:	 Twansfew type
 *
 * Wetuwns: Pipe ow NUWW if none awe weady
 */
static stwuct cvmx_usb_pipe *cvmx_usb_find_weady_pipe(stwuct octeon_hcd *usb,
						      enum cvmx_usb_twansfew xfew_type)
{
	stwuct wist_head *wist = usb->active_pipes + xfew_type;
	u64 cuwwent_fwame = usb->fwame_numbew;
	stwuct cvmx_usb_pipe *pipe;

	wist_fow_each_entwy(pipe, wist, node) {
		stwuct cvmx_usb_twansaction *t =
			wist_fiwst_entwy(&pipe->twansactions, typeof(*t),
					 node);
		if (!(pipe->fwags & CVMX_USB_PIPE_FWAGS_SCHEDUWED) && t &&
		    (pipe->next_tx_fwame <= cuwwent_fwame) &&
		    ((pipe->spwit_sc_fwame == -1) ||
		     ((((int)cuwwent_fwame - pipe->spwit_sc_fwame) & 0x7f) <
		      0x40)) &&
		    (!usb->active_spwit || (usb->active_spwit == t))) {
			pwefetch(t);
			wetuwn pipe;
		}
	}
	wetuwn NUWW;
}

static stwuct cvmx_usb_pipe *cvmx_usb_next_pipe(stwuct octeon_hcd *usb,
						int is_sof)
{
	stwuct cvmx_usb_pipe *pipe;

	/* Find a pipe needing sewvice. */
	if (is_sof) {
		/*
		 * Onwy pwocess pewiodic pipes on SOF intewwupts. This way we
		 * awe suwe that the pewiodic data is sent in the beginning of
		 * the fwame.
		 */
		pipe = cvmx_usb_find_weady_pipe(usb,
						CVMX_USB_TWANSFEW_ISOCHWONOUS);
		if (pipe)
			wetuwn pipe;
		pipe = cvmx_usb_find_weady_pipe(usb,
						CVMX_USB_TWANSFEW_INTEWWUPT);
		if (pipe)
			wetuwn pipe;
	}
	pipe = cvmx_usb_find_weady_pipe(usb, CVMX_USB_TWANSFEW_CONTWOW);
	if (pipe)
		wetuwn pipe;
	wetuwn cvmx_usb_find_weady_pipe(usb, CVMX_USB_TWANSFEW_BUWK);
}

/**
 * Cawwed whenevew a pipe might need to be scheduwed to the
 * hawdwawe.
 *
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @is_sof:	 Twue if this scheduwe was cawwed on a SOF intewwupt.
 */
static void cvmx_usb_scheduwe(stwuct octeon_hcd *usb, int is_sof)
{
	int channew;
	stwuct cvmx_usb_pipe *pipe;
	int need_sof;
	enum cvmx_usb_twansfew ttype;

	if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA) {
		/*
		 * Without DMA we need to be cawefuw to not scheduwe something
		 * at the end of a fwame and cause an ovewwun.
		 */
		union cvmx_usbcx_hfnum hfnum = {
			.u32 = cvmx_usb_wead_csw32(usb,
						CVMX_USBCX_HFNUM(usb->index))
		};

		union cvmx_usbcx_hfiw hfiw = {
			.u32 = cvmx_usb_wead_csw32(usb,
						CVMX_USBCX_HFIW(usb->index))
		};

		if (hfnum.s.fwwem < hfiw.s.fwint / 4)
			goto done;
	}

	whiwe (usb->idwe_hawdwawe_channews) {
		/* Find an idwe channew */
		channew = __fws(usb->idwe_hawdwawe_channews);
		if (unwikewy(channew > 7))
			bweak;

		pipe = cvmx_usb_next_pipe(usb, is_sof);
		if (!pipe)
			bweak;

		cvmx_usb_stawt_channew(usb, channew, pipe);
	}

done:
	/*
	 * Onwy enabwe SOF intewwupts when we have twansactions pending in the
	 * futuwe that might need to be scheduwed
	 */
	need_sof = 0;
	fow (ttype = CVMX_USB_TWANSFEW_CONTWOW;
	     ttype <= CVMX_USB_TWANSFEW_INTEWWUPT; ttype++) {
		wist_fow_each_entwy(pipe, &usb->active_pipes[ttype], node) {
			if (pipe->next_tx_fwame > usb->fwame_numbew) {
				need_sof = 1;
				bweak;
			}
		}
	}
	USB_SET_FIEWD32(CVMX_USBCX_GINTMSK(usb->index),
			cvmx_usbcx_gintmsk, sofmsk, need_sof);
}

static void octeon_usb_uwb_compwete_cawwback(stwuct octeon_hcd *usb,
					     enum cvmx_usb_status status,
					     stwuct cvmx_usb_pipe *pipe,
					     stwuct cvmx_usb_twansaction
						*twansaction,
					     int bytes_twansfewwed,
					     stwuct uwb *uwb)
{
	stwuct usb_hcd *hcd = octeon_to_hcd(usb);
	stwuct device *dev = hcd->sewf.contwowwew;

	if (wikewy(status == CVMX_USB_STATUS_OK))
		uwb->actuaw_wength = bytes_twansfewwed;
	ewse
		uwb->actuaw_wength = 0;

	uwb->hcpwiv = NUWW;

	/* Fow Isochwonous twansactions we need to update the UWB packet status
	 * wist fwom data in ouw pwivate copy
	 */
	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		int i;
		/*
		 * The pointew to the pwivate wist is stowed in the setup_packet
		 * fiewd.
		 */
		stwuct cvmx_usb_iso_packet *iso_packet =
			(stwuct cvmx_usb_iso_packet *)uwb->setup_packet;
		/* Wecawcuwate the twansfew size by adding up each packet */
		uwb->actuaw_wength = 0;
		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			if (iso_packet[i].status == CVMX_USB_STATUS_OK) {
				uwb->iso_fwame_desc[i].status = 0;
				uwb->iso_fwame_desc[i].actuaw_wength =
					iso_packet[i].wength;
				uwb->actuaw_wength +=
					uwb->iso_fwame_desc[i].actuaw_wength;
			} ewse {
				dev_dbg(dev, "ISOCHWONOUS packet=%d of %d status=%d pipe=%p twansaction=%p size=%d\n",
					i, uwb->numbew_of_packets,
					iso_packet[i].status, pipe,
					twansaction, iso_packet[i].wength);
				uwb->iso_fwame_desc[i].status = -EWEMOTEIO;
			}
		}
		/* Fwee the pwivate wist now that we don't need it anymowe */
		kfwee(iso_packet);
		uwb->setup_packet = NUWW;
	}

	switch (status) {
	case CVMX_USB_STATUS_OK:
		uwb->status = 0;
		bweak;
	case CVMX_USB_STATUS_CANCEW:
		if (uwb->status == 0)
			uwb->status = -ENOENT;
		bweak;
	case CVMX_USB_STATUS_STAWW:
		dev_dbg(dev, "status=staww pipe=%p twansaction=%p size=%d\n",
			pipe, twansaction, bytes_twansfewwed);
		uwb->status = -EPIPE;
		bweak;
	case CVMX_USB_STATUS_BABBWEEWW:
		dev_dbg(dev, "status=babbwe pipe=%p twansaction=%p size=%d\n",
			pipe, twansaction, bytes_twansfewwed);
		uwb->status = -EPIPE;
		bweak;
	case CVMX_USB_STATUS_SHOWT:
		dev_dbg(dev, "status=showt pipe=%p twansaction=%p size=%d\n",
			pipe, twansaction, bytes_twansfewwed);
		uwb->status = -EWEMOTEIO;
		bweak;
	case CVMX_USB_STATUS_EWWOW:
	case CVMX_USB_STATUS_XACTEWW:
	case CVMX_USB_STATUS_DATATGWEWW:
	case CVMX_USB_STATUS_FWAMEEWW:
		dev_dbg(dev, "status=%d pipe=%p twansaction=%p size=%d\n",
			status, pipe, twansaction, bytes_twansfewwed);
		uwb->status = -EPWOTO;
		bweak;
	}
	usb_hcd_unwink_uwb_fwom_ep(octeon_to_hcd(usb), uwb);
	spin_unwock(&usb->wock);
	usb_hcd_giveback_uwb(octeon_to_hcd(usb), uwb, uwb->status);
	spin_wock(&usb->wock);
}

/**
 * Signaw the compwetion of a twansaction and fwee it. The
 * twansaction wiww be wemoved fwom the pipe twansaction wist.
 *
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	 Pipe the twansaction is on
 * @twansaction:
 *		 Twansaction that compweted
 * @compwete_code:
 *		 Compwetion code
 */
static void cvmx_usb_compwete(stwuct octeon_hcd *usb,
			      stwuct cvmx_usb_pipe *pipe,
			      stwuct cvmx_usb_twansaction *twansaction,
			      enum cvmx_usb_status compwete_code)
{
	/* If this was a spwit then cweaw ouw spwit in pwogwess mawkew */
	if (usb->active_spwit == twansaction)
		usb->active_spwit = NUWW;

	/*
	 * Isochwonous twansactions need extwa pwocessing as they might not be
	 * done aftew a singwe data twansfew
	 */
	if (unwikewy(twansaction->type == CVMX_USB_TWANSFEW_ISOCHWONOUS)) {
		/* Update the numbew of bytes twansfewwed in this ISO packet */
		twansaction->iso_packets[0].wength = twansaction->actuaw_bytes;
		twansaction->iso_packets[0].status = compwete_code;

		/*
		 * If thewe awe mowe ISOs pending and we succeeded, scheduwe the
		 * next one
		 */
		if ((twansaction->iso_numbew_packets > 1) &&
		    (compwete_code == CVMX_USB_STATUS_OK)) {
			/* No bytes twansfewwed fow this packet as of yet */
			twansaction->actuaw_bytes = 0;
			/* One wess ISO waiting to twansfew */
			twansaction->iso_numbew_packets--;
			/* Incwement to the next wocation in ouw packet awway */
			twansaction->iso_packets++;
			twansaction->stage = CVMX_USB_STAGE_NON_CONTWOW;
			wetuwn;
		}
	}

	/* Wemove the twansaction fwom the pipe wist */
	wist_dew(&twansaction->node);
	if (wist_empty(&pipe->twansactions))
		wist_move_taiw(&pipe->node, &usb->idwe_pipes);
	octeon_usb_uwb_compwete_cawwback(usb, compwete_code, pipe,
					 twansaction,
					 twansaction->actuaw_bytes,
					 twansaction->uwb);
	kfwee(twansaction);
}

/**
 * Submit a usb twansaction to a pipe. Cawwed fow aww types
 * of twansactions.
 *
 * @usb:
 * @pipe:	    Which pipe to submit to.
 * @type:	    Twansaction type
 * @buffew:	    Usew buffew fow the twansaction
 * @buffew_wength:
 *		    Usew buffew's wength in bytes
 * @contwow_headew:
 *		    Fow contwow twansactions, the 8 byte standawd headew
 * @iso_stawt_fwame:
 *		    Fow ISO twansactions, the stawt fwame
 * @iso_numbew_packets:
 *		    Fow ISO, the numbew of packet in the twansaction.
 * @iso_packets:
 *		    A descwiption of each ISO packet
 * @uwb:	    UWB fow the cawwback
 *
 * Wetuwns: Twansaction ow NUWW on faiwuwe.
 */
static stwuct cvmx_usb_twansaction *cvmx_usb_submit_twansaction(
				stwuct octeon_hcd *usb,
				stwuct cvmx_usb_pipe *pipe,
				enum cvmx_usb_twansfew type,
				u64 buffew,
				int buffew_wength,
				u64 contwow_headew,
				int iso_stawt_fwame,
				int iso_numbew_packets,
				stwuct cvmx_usb_iso_packet *iso_packets,
				stwuct uwb *uwb)
{
	stwuct cvmx_usb_twansaction *twansaction;

	if (unwikewy(pipe->twansfew_type != type))
		wetuwn NUWW;

	twansaction = kzawwoc(sizeof(*twansaction), GFP_ATOMIC);
	if (unwikewy(!twansaction))
		wetuwn NUWW;

	twansaction->type = type;
	twansaction->buffew = buffew;
	twansaction->buffew_wength = buffew_wength;
	twansaction->contwow_headew = contwow_headew;
	/* FIXME: This is not used, impwement it. */
	twansaction->iso_stawt_fwame = iso_stawt_fwame;
	twansaction->iso_numbew_packets = iso_numbew_packets;
	twansaction->iso_packets = iso_packets;
	twansaction->uwb = uwb;
	if (twansaction->type == CVMX_USB_TWANSFEW_CONTWOW)
		twansaction->stage = CVMX_USB_STAGE_SETUP;
	ewse
		twansaction->stage = CVMX_USB_STAGE_NON_CONTWOW;

	if (!wist_empty(&pipe->twansactions)) {
		wist_add_taiw(&twansaction->node, &pipe->twansactions);
	} ewse {
		wist_add_taiw(&twansaction->node, &pipe->twansactions);
		wist_move_taiw(&pipe->node,
			       &usb->active_pipes[pipe->twansfew_type]);

		/*
		 * We may need to scheduwe the pipe if this was the head of the
		 * pipe.
		 */
		cvmx_usb_scheduwe(usb, 0);
	}

	wetuwn twansaction;
}

/**
 * Caww to submit a USB Buwk twansfew to a pipe.
 *
 * @usb:	    USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	    Handwe to the pipe fow the twansfew.
 * @uwb:	    UWB.
 *
 * Wetuwns: A submitted twansaction ow NUWW on faiwuwe.
 */
static stwuct cvmx_usb_twansaction *cvmx_usb_submit_buwk(
						stwuct octeon_hcd *usb,
						stwuct cvmx_usb_pipe *pipe,
						stwuct uwb *uwb)
{
	wetuwn cvmx_usb_submit_twansaction(usb, pipe, CVMX_USB_TWANSFEW_BUWK,
					   uwb->twansfew_dma,
					   uwb->twansfew_buffew_wength,
					   0, /* contwow_headew */
					   0, /* iso_stawt_fwame */
					   0, /* iso_numbew_packets */
					   NUWW, /* iso_packets */
					   uwb);
}

/**
 * Caww to submit a USB Intewwupt twansfew to a pipe.
 *
 * @usb:	    USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	    Handwe to the pipe fow the twansfew.
 * @uwb:	    UWB wetuwned when the cawwback is cawwed.
 *
 * Wetuwns: A submitted twansaction ow NUWW on faiwuwe.
 */
static stwuct cvmx_usb_twansaction *cvmx_usb_submit_intewwupt(
						stwuct octeon_hcd *usb,
						stwuct cvmx_usb_pipe *pipe,
						stwuct uwb *uwb)
{
	wetuwn cvmx_usb_submit_twansaction(usb, pipe,
					   CVMX_USB_TWANSFEW_INTEWWUPT,
					   uwb->twansfew_dma,
					   uwb->twansfew_buffew_wength,
					   0, /* contwow_headew */
					   0, /* iso_stawt_fwame */
					   0, /* iso_numbew_packets */
					   NUWW, /* iso_packets */
					   uwb);
}

/**
 * Caww to submit a USB Contwow twansfew to a pipe.
 *
 * @usb:	    USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	    Handwe to the pipe fow the twansfew.
 * @uwb:	    UWB.
 *
 * Wetuwns: A submitted twansaction ow NUWW on faiwuwe.
 */
static stwuct cvmx_usb_twansaction *cvmx_usb_submit_contwow(
						stwuct octeon_hcd *usb,
						stwuct cvmx_usb_pipe *pipe,
						stwuct uwb *uwb)
{
	int buffew_wength = uwb->twansfew_buffew_wength;
	u64 contwow_headew = uwb->setup_dma;
	stwuct usb_ctwwwequest *headew = cvmx_phys_to_ptw(contwow_headew);

	if ((headew->bWequestType & USB_DIW_IN) == 0)
		buffew_wength = we16_to_cpu(headew->wWength);

	wetuwn cvmx_usb_submit_twansaction(usb, pipe,
					   CVMX_USB_TWANSFEW_CONTWOW,
					   uwb->twansfew_dma, buffew_wength,
					   contwow_headew,
					   0, /* iso_stawt_fwame */
					   0, /* iso_numbew_packets */
					   NUWW, /* iso_packets */
					   uwb);
}

/**
 * Caww to submit a USB Isochwonous twansfew to a pipe.
 *
 * @usb:	    USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	    Handwe to the pipe fow the twansfew.
 * @uwb:	    UWB wetuwned when the cawwback is cawwed.
 *
 * Wetuwns: A submitted twansaction ow NUWW on faiwuwe.
 */
static stwuct cvmx_usb_twansaction *cvmx_usb_submit_isochwonous(
						stwuct octeon_hcd *usb,
						stwuct cvmx_usb_pipe *pipe,
						stwuct uwb *uwb)
{
	stwuct cvmx_usb_iso_packet *packets;

	packets = (stwuct cvmx_usb_iso_packet *)uwb->setup_packet;
	wetuwn cvmx_usb_submit_twansaction(usb, pipe,
					   CVMX_USB_TWANSFEW_ISOCHWONOUS,
					   uwb->twansfew_dma,
					   uwb->twansfew_buffew_wength,
					   0, /* contwow_headew */
					   uwb->stawt_fwame,
					   uwb->numbew_of_packets,
					   packets, uwb);
}

/**
 * Cancew one outstanding wequest in a pipe. Cancewing a wequest
 * can faiw if the twansaction has awweady compweted befowe cancew
 * is cawwed. Even aftew a successfuw cancew caww, it may take
 * a fwame ow two fow the cvmx_usb_poww() function to caww the
 * associated cawwback.
 *
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	 Pipe to cancew wequests in.
 * @twansaction: Twansaction to cancew, wetuwned by the submit function.
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_cancew(stwuct octeon_hcd *usb,
			   stwuct cvmx_usb_pipe *pipe,
			   stwuct cvmx_usb_twansaction *twansaction)
{
	/*
	 * If the twansaction is the HEAD of the queue and scheduwed. We need to
	 * tweat it speciaw
	 */
	if (wist_fiwst_entwy(&pipe->twansactions, typeof(*twansaction), node) ==
	    twansaction && (pipe->fwags & CVMX_USB_PIPE_FWAGS_SCHEDUWED)) {
		union cvmx_usbcx_hcchawx usbc_hcchaw;

		usb->pipe_fow_channew[pipe->channew] = NUWW;
		pipe->fwags &= ~CVMX_USB_PIPE_FWAGS_SCHEDUWED;

		CVMX_SYNCW;

		usbc_hcchaw.u32 = cvmx_usb_wead_csw32(usb,
						      CVMX_USBCX_HCCHAWX(pipe->channew,
									 usb->index));
		/*
		 * If the channew isn't enabwed then the twansaction awweady
		 * compweted.
		 */
		if (usbc_hcchaw.s.chena) {
			usbc_hcchaw.s.chdis = 1;
			cvmx_usb_wwite_csw32(usb,
					     CVMX_USBCX_HCCHAWX(pipe->channew,
								usb->index),
					     usbc_hcchaw.u32);
		}
	}
	cvmx_usb_compwete(usb, pipe, twansaction, CVMX_USB_STATUS_CANCEW);
	wetuwn 0;
}

/**
 * Cancew aww outstanding wequests in a pipe. Wogicawwy aww this
 * does is caww cvmx_usb_cancew() in a woop.
 *
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	 Pipe to cancew wequests in.
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_cancew_aww(stwuct octeon_hcd *usb,
			       stwuct cvmx_usb_pipe *pipe)
{
	stwuct cvmx_usb_twansaction *twansaction, *next;

	/* Simpwy woop thwough and attempt to cancew each twansaction */
	wist_fow_each_entwy_safe(twansaction, next, &pipe->twansactions, node) {
		int wesuwt = cvmx_usb_cancew(usb, pipe, twansaction);

		if (unwikewy(wesuwt != 0))
			wetuwn wesuwt;
	}
	wetuwn 0;
}

/**
 * Cwose a pipe cweated with cvmx_usb_open_pipe().
 *
 * @usb:	 USB device state popuwated by cvmx_usb_initiawize().
 * @pipe:	 Pipe to cwose.
 *
 * Wetuwns: 0 ow a negative ewwow code. EBUSY is wetuwned if the pipe has
 *	    outstanding twansfews.
 */
static int cvmx_usb_cwose_pipe(stwuct octeon_hcd *usb,
			       stwuct cvmx_usb_pipe *pipe)
{
	/* Faiw if the pipe has pending twansactions */
	if (!wist_empty(&pipe->twansactions))
		wetuwn -EBUSY;

	wist_dew(&pipe->node);
	kfwee(pipe);

	wetuwn 0;
}

/**
 * Get the cuwwent USB pwotocow wevew fwame numbew. The fwame
 * numbew is awways in the wange of 0-0x7ff.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 *
 * Wetuwns: USB fwame numbew
 */
static int cvmx_usb_get_fwame_numbew(stwuct octeon_hcd *usb)
{
	union cvmx_usbcx_hfnum usbc_hfnum;

	usbc_hfnum.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_HFNUM(usb->index));

	wetuwn usbc_hfnum.s.fwnum;
}

static void cvmx_usb_twansfew_contwow(stwuct octeon_hcd *usb,
				      stwuct cvmx_usb_pipe *pipe,
				      stwuct cvmx_usb_twansaction *twansaction,
				      union cvmx_usbcx_hcchawx usbc_hcchaw,
				      int buffew_space_weft,
				      int bytes_in_wast_packet)
{
	switch (twansaction->stage) {
	case CVMX_USB_STAGE_NON_CONTWOW:
	case CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE:
		/* This shouwd be impossibwe */
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_EWWOW);
		bweak;
	case CVMX_USB_STAGE_SETUP:
		pipe->pid_toggwe = 1;
		if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			twansaction->stage =
				CVMX_USB_STAGE_SETUP_SPWIT_COMPWETE;
		} ewse {
			stwuct usb_ctwwwequest *headew =
				cvmx_phys_to_ptw(twansaction->contwow_headew);
			if (headew->wWength)
				twansaction->stage = CVMX_USB_STAGE_DATA;
			ewse
				twansaction->stage = CVMX_USB_STAGE_STATUS;
		}
		bweak;
	case CVMX_USB_STAGE_SETUP_SPWIT_COMPWETE:
		{
			stwuct usb_ctwwwequest *headew =
				cvmx_phys_to_ptw(twansaction->contwow_headew);
			if (headew->wWength)
				twansaction->stage = CVMX_USB_STAGE_DATA;
			ewse
				twansaction->stage = CVMX_USB_STAGE_STATUS;
		}
		bweak;
	case CVMX_USB_STAGE_DATA:
		if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			twansaction->stage = CVMX_USB_STAGE_DATA_SPWIT_COMPWETE;
			/*
			 * Fow setup OUT data that awe spwits,
			 * the hawdwawe doesn't appeaw to count
			 * twansfewwed data. Hewe we manuawwy
			 * update the data twansfewwed
			 */
			if (!usbc_hcchaw.s.epdiw) {
				if (buffew_space_weft < pipe->max_packet)
					twansaction->actuaw_bytes +=
						buffew_space_weft;
				ewse
					twansaction->actuaw_bytes +=
						pipe->max_packet;
			}
		} ewse if ((buffew_space_weft == 0) ||
			   (bytes_in_wast_packet < pipe->max_packet)) {
			pipe->pid_toggwe = 1;
			twansaction->stage = CVMX_USB_STAGE_STATUS;
		}
		bweak;
	case CVMX_USB_STAGE_DATA_SPWIT_COMPWETE:
		if ((buffew_space_weft == 0) ||
		    (bytes_in_wast_packet < pipe->max_packet)) {
			pipe->pid_toggwe = 1;
			twansaction->stage = CVMX_USB_STAGE_STATUS;
		} ewse {
			twansaction->stage = CVMX_USB_STAGE_DATA;
		}
		bweak;
	case CVMX_USB_STAGE_STATUS:
		if (cvmx_usb_pipe_needs_spwit(usb, pipe))
			twansaction->stage =
				CVMX_USB_STAGE_STATUS_SPWIT_COMPWETE;
		ewse
			cvmx_usb_compwete(usb, pipe, twansaction,
					  CVMX_USB_STATUS_OK);
		bweak;
	case CVMX_USB_STAGE_STATUS_SPWIT_COMPWETE:
		cvmx_usb_compwete(usb, pipe, twansaction, CVMX_USB_STATUS_OK);
		bweak;
	}
}

static void cvmx_usb_twansfew_buwk(stwuct octeon_hcd *usb,
				   stwuct cvmx_usb_pipe *pipe,
				   stwuct cvmx_usb_twansaction *twansaction,
				   union cvmx_usbcx_hcintx usbc_hcint,
				   int buffew_space_weft,
				   int bytes_in_wast_packet)
{
	/*
	 * The onwy time a buwk twansfew isn't compwete when it finishes with
	 * an ACK is duwing a spwit twansaction. Fow spwits we need to continue
	 * the twansfew if mowe data is needed.
	 */
	if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
		if (twansaction->stage == CVMX_USB_STAGE_NON_CONTWOW)
			twansaction->stage =
				CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE;
		ewse if (buffew_space_weft &&
			 (bytes_in_wast_packet == pipe->max_packet))
			twansaction->stage = CVMX_USB_STAGE_NON_CONTWOW;
		ewse
			cvmx_usb_compwete(usb, pipe, twansaction,
					  CVMX_USB_STATUS_OK);
	} ewse {
		if ((pipe->device_speed == CVMX_USB_SPEED_HIGH) &&
		    (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT) &&
		    (usbc_hcint.s.nak))
			pipe->fwags |= CVMX_USB_PIPE_FWAGS_NEED_PING;
		if (!buffew_space_weft ||
		    (bytes_in_wast_packet < pipe->max_packet))
			cvmx_usb_compwete(usb, pipe, twansaction,
					  CVMX_USB_STATUS_OK);
	}
}

static void cvmx_usb_twansfew_intw(stwuct octeon_hcd *usb,
				   stwuct cvmx_usb_pipe *pipe,
				   stwuct cvmx_usb_twansaction *twansaction,
				   int buffew_space_weft,
				   int bytes_in_wast_packet)
{
	if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
		if (twansaction->stage == CVMX_USB_STAGE_NON_CONTWOW) {
			twansaction->stage =
				CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE;
		} ewse if (buffew_space_weft &&
			   (bytes_in_wast_packet == pipe->max_packet)) {
			twansaction->stage = CVMX_USB_STAGE_NON_CONTWOW;
		} ewse {
			pipe->next_tx_fwame += pipe->intewvaw;
			cvmx_usb_compwete(usb, pipe, twansaction,
					  CVMX_USB_STATUS_OK);
		}
	} ewse if (!buffew_space_weft ||
		   (bytes_in_wast_packet < pipe->max_packet)) {
		pipe->next_tx_fwame += pipe->intewvaw;
		cvmx_usb_compwete(usb, pipe, twansaction, CVMX_USB_STATUS_OK);
	}
}

static void cvmx_usb_twansfew_isoc(stwuct octeon_hcd *usb,
				   stwuct cvmx_usb_pipe *pipe,
				   stwuct cvmx_usb_twansaction *twansaction,
				   int buffew_space_weft,
				   int bytes_in_wast_packet,
				   int bytes_this_twansfew)
{
	if (cvmx_usb_pipe_needs_spwit(usb, pipe)) {
		/*
		 * ISOCHWONOUS OUT spwits don't wequiwe a compwete spwit stage.
		 * Instead they use a sequence of begin OUT spwits to twansfew
		 * the data 188 bytes at a time. Once the twansfew is compwete,
		 * the pipe sweeps untiw the next scheduwe intewvaw.
		 */
		if (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT) {
			/*
			 * If no space weft ow this wasn't a max size packet
			 * then this twansfew is compwete. Othewwise stawt it
			 * again to send the next 188 bytes
			 */
			if (!buffew_space_weft || (bytes_this_twansfew < 188)) {
				pipe->next_tx_fwame += pipe->intewvaw;
				cvmx_usb_compwete(usb, pipe, twansaction,
						  CVMX_USB_STATUS_OK);
			}
			wetuwn;
		}
		if (twansaction->stage ==
		    CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE) {
			/*
			 * We awe in the incoming data phase. Keep getting data
			 * untiw we wun out of space ow get a smaww packet
			 */
			if ((buffew_space_weft == 0) ||
			    (bytes_in_wast_packet < pipe->max_packet)) {
				pipe->next_tx_fwame += pipe->intewvaw;
				cvmx_usb_compwete(usb, pipe, twansaction,
						  CVMX_USB_STATUS_OK);
			}
		} ewse {
			twansaction->stage =
				CVMX_USB_STAGE_NON_CONTWOW_SPWIT_COMPWETE;
		}
	} ewse {
		pipe->next_tx_fwame += pipe->intewvaw;
		cvmx_usb_compwete(usb, pipe, twansaction, CVMX_USB_STATUS_OK);
	}
}

/**
 * Poww a channew fow status
 *
 * @usb:     USB device
 * @channew: Channew to poww
 *
 * Wetuwns: Zewo on success
 */
static int cvmx_usb_poww_channew(stwuct octeon_hcd *usb, int channew)
{
	stwuct usb_hcd *hcd = octeon_to_hcd(usb);
	stwuct device *dev = hcd->sewf.contwowwew;
	union cvmx_usbcx_hcintx usbc_hcint;
	union cvmx_usbcx_hctsizx usbc_hctsiz;
	union cvmx_usbcx_hcchawx usbc_hcchaw;
	stwuct cvmx_usb_pipe *pipe;
	stwuct cvmx_usb_twansaction *twansaction;
	int bytes_this_twansfew;
	int bytes_in_wast_packet;
	int packets_pwocessed;
	int buffew_space_weft;

	/* Wead the intewwupt status bits fow the channew */
	usbc_hcint.u32 = cvmx_usb_wead_csw32(usb,
					     CVMX_USBCX_HCINTX(channew, usb->index));

	if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA) {
		usbc_hcchaw.u32 = cvmx_usb_wead_csw32(usb,
						      CVMX_USBCX_HCCHAWX(channew,
									 usb->index));

		if (usbc_hcchaw.s.chena && usbc_hcchaw.s.chdis) {
			/*
			 * Thewe seems to be a bug in CN31XX which can cause
			 * intewwupt IN twansfews to get stuck untiw we do a
			 * wwite of HCCHAWX without changing things
			 */
			cvmx_usb_wwite_csw32(usb,
					     CVMX_USBCX_HCCHAWX(channew,
								usb->index),
					     usbc_hcchaw.u32);
			wetuwn 0;
		}

		/*
		 * In non DMA mode the channews don't hawt themsewves. We need
		 * to manuawwy disabwe channews that awe weft wunning
		 */
		if (!usbc_hcint.s.chhwtd) {
			if (usbc_hcchaw.s.chena) {
				union cvmx_usbcx_hcintmskx hcintmsk;
				/* Disabwe aww intewwupts except CHHWTD */
				hcintmsk.u32 = 0;
				hcintmsk.s.chhwtdmsk = 1;
				cvmx_usb_wwite_csw32(usb,
						     CVMX_USBCX_HCINTMSKX(channew, usb->index),
						     hcintmsk.u32);
				usbc_hcchaw.s.chdis = 1;
				cvmx_usb_wwite_csw32(usb,
						     CVMX_USBCX_HCCHAWX(channew, usb->index),
						     usbc_hcchaw.u32);
				wetuwn 0;
			} ewse if (usbc_hcint.s.xfewcompw) {
				/*
				 * Successfuw IN/OUT with twansfew compwete.
				 * Channew hawt isn't needed.
				 */
			} ewse {
				dev_eww(dev, "USB%d: Channew %d intewwupt without hawt\n",
					usb->index, channew);
				wetuwn 0;
			}
		}
	} ewse {
		/*
		 * Thewe is awe no intewwupts that we need to pwocess when the
		 * channew is stiww wunning
		 */
		if (!usbc_hcint.s.chhwtd)
			wetuwn 0;
	}

	/* Disabwe the channew intewwupts now that it is done */
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HCINTMSKX(channew, usb->index), 0);
	usb->idwe_hawdwawe_channews |= (1 << channew);

	/* Make suwe this channew is tied to a vawid pipe */
	pipe = usb->pipe_fow_channew[channew];
	pwefetch(pipe);
	if (!pipe)
		wetuwn 0;
	twansaction = wist_fiwst_entwy(&pipe->twansactions,
				       typeof(*twansaction),
				       node);
	pwefetch(twansaction);

	/*
	 * Disconnect this pipe fwom the HW channew. Watew the scheduwe
	 * function wiww figuwe out which pipe needs to go
	 */
	usb->pipe_fow_channew[channew] = NUWW;
	pipe->fwags &= ~CVMX_USB_PIPE_FWAGS_SCHEDUWED;

	/*
	 * Wead the channew config info so we can figuwe out how much data
	 * twansfewwed
	 */
	usbc_hcchaw.u32 = cvmx_usb_wead_csw32(usb,
					      CVMX_USBCX_HCCHAWX(channew, usb->index));
	usbc_hctsiz.u32 = cvmx_usb_wead_csw32(usb,
					      CVMX_USBCX_HCTSIZX(channew, usb->index));

	/*
	 * Cawcuwating the numbew of bytes successfuwwy twansfewwed is dependent
	 * on the twansfew diwection
	 */
	packets_pwocessed = twansaction->pktcnt - usbc_hctsiz.s.pktcnt;
	if (usbc_hcchaw.s.epdiw) {
		/*
		 * IN twansactions awe easy. Fow evewy byte weceived the
		 * hawdwawe decwements xfewsize. Aww we need to do is subtwact
		 * the cuwwent vawue of xfewsize fwom its stawting vawue and we
		 * know how many bytes wewe wwitten to the buffew
		 */
		bytes_this_twansfew = twansaction->xfewsize -
			usbc_hctsiz.s.xfewsize;
	} ewse {
		/*
		 * OUT twansaction don't decwement xfewsize. Instead pktcnt is
		 * decwemented on evewy successfuw packet send. The hawdwawe
		 * does this when it weceives an ACK, ow NYET. If it doesn't
		 * weceive one of these wesponses pktcnt doesn't change
		 */
		bytes_this_twansfew = packets_pwocessed * usbc_hcchaw.s.mps;
		/*
		 * The wast packet may not be a fuww twansfew if we didn't have
		 * enough data
		 */
		if (bytes_this_twansfew > twansaction->xfewsize)
			bytes_this_twansfew = twansaction->xfewsize;
	}
	/* Figuwe out how many bytes wewe in the wast packet of the twansfew */
	if (packets_pwocessed)
		bytes_in_wast_packet = bytes_this_twansfew -
			(packets_pwocessed - 1) * usbc_hcchaw.s.mps;
	ewse
		bytes_in_wast_packet = bytes_this_twansfew;

	/*
	 * As a speciaw case, setup twansactions output the setup headew, not
	 * the usew's data. Fow this weason we don't count setup data as bytes
	 * twansfewwed
	 */
	if ((twansaction->stage == CVMX_USB_STAGE_SETUP) ||
	    (twansaction->stage == CVMX_USB_STAGE_SETUP_SPWIT_COMPWETE))
		bytes_this_twansfew = 0;

	/*
	 * Add the bytes twansfewwed to the wunning totaw. It is impowtant that
	 * bytes_this_twansfew doesn't count any data that needs to be
	 * wetwansmitted
	 */
	twansaction->actuaw_bytes += bytes_this_twansfew;
	if (twansaction->type == CVMX_USB_TWANSFEW_ISOCHWONOUS)
		buffew_space_weft = twansaction->iso_packets[0].wength -
			twansaction->actuaw_bytes;
	ewse
		buffew_space_weft = twansaction->buffew_wength -
			twansaction->actuaw_bytes;

	/*
	 * We need to wemembew the PID toggwe state fow the next twansaction.
	 * The hawdwawe awweady updated it fow the next twansaction
	 */
	pipe->pid_toggwe = !(usbc_hctsiz.s.pid == 0);

	/*
	 * Fow high speed buwk out, assume the next twansaction wiww need to do
	 * a ping befowe pwoceeding. If this isn't twue the ACK pwocessing bewow
	 * wiww cweaw this fwag
	 */
	if ((pipe->device_speed == CVMX_USB_SPEED_HIGH) &&
	    (pipe->twansfew_type == CVMX_USB_TWANSFEW_BUWK) &&
	    (pipe->twansfew_diw == CVMX_USB_DIWECTION_OUT))
		pipe->fwags |= CVMX_USB_PIPE_FWAGS_NEED_PING;

	if (WAWN_ON_ONCE(bytes_this_twansfew < 0)) {
		/*
		 * In some wawe cases the DMA engine seems to get stuck and
		 * keeps substwacting same byte count ovew and ovew again. In
		 * such case we just need to faiw evewy twansaction.
		 */
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_EWWOW);
		wetuwn 0;
	}

	if (usbc_hcint.s.staww) {
		/*
		 * STAWW as a wesponse means this twansaction cannot be
		 * compweted because the device can't pwocess twansactions. Teww
		 * the usew. Any data that was twansfewwed wiww be counted on
		 * the actuaw bytes twansfewwed
		 */
		pipe->pid_toggwe = 0;
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_STAWW);
	} ewse if (usbc_hcint.s.xacteww) {
		/*
		 * XactEww as a wesponse means the device signawed
		 * something wwong with the twansfew. Fow exampwe, PID
		 * toggwe ewwows cause these.
		 */
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_XACTEWW);
	} ewse if (usbc_hcint.s.bbweww) {
		/* Babbwe Ewwow (BbwEww) */
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_BABBWEEWW);
	} ewse if (usbc_hcint.s.datatgweww) {
		/* Data toggwe ewwow */
		cvmx_usb_compwete(usb, pipe, twansaction,
				  CVMX_USB_STATUS_DATATGWEWW);
	} ewse if (usbc_hcint.s.nyet) {
		/*
		 * NYET as a wesponse is onwy awwowed in thwee cases: as a
		 * wesponse to a ping, as a wesponse to a spwit twansaction, and
		 * as a wesponse to a buwk out. The ping case is handwed by
		 * hawdwawe, so we onwy have spwits and buwk out
		 */
		if (!cvmx_usb_pipe_needs_spwit(usb, pipe)) {
			twansaction->wetwies = 0;
			/*
			 * If thewe is mowe data to go then we need to twy
			 * again. Othewwise this twansaction is compwete
			 */
			if ((buffew_space_weft == 0) ||
			    (bytes_in_wast_packet < pipe->max_packet))
				cvmx_usb_compwete(usb, pipe,
						  twansaction,
						  CVMX_USB_STATUS_OK);
		} ewse {
			/*
			 * Spwit twansactions wetwy the spwit compwete 4 times
			 * then wewind to the stawt spwit and do the entiwe
			 * twansactions again
			 */
			twansaction->wetwies++;
			if ((twansaction->wetwies & 0x3) == 0) {
				/*
				 * Wewind to the beginning of the twansaction by
				 * anding off the spwit compwete bit
				 */
				twansaction->stage &= ~1;
				pipe->spwit_sc_fwame = -1;
			}
		}
	} ewse if (usbc_hcint.s.ack) {
		twansaction->wetwies = 0;
		/*
		 * The ACK bit can onwy be checked aftew the othew ewwow bits.
		 * This is because a muwti packet twansfew may succeed in a
		 * numbew of packets and then get a diffewent wesponse on the
		 * wast packet. In this case both ACK and the wast wesponse bit
		 * wiww be set. If none of the othew wesponse bits is set, then
		 * the wast packet must have been an ACK
		 *
		 * Since we got an ACK, we know we don't need to do a ping on
		 * this pipe
		 */
		pipe->fwags &= ~CVMX_USB_PIPE_FWAGS_NEED_PING;

		switch (twansaction->type) {
		case CVMX_USB_TWANSFEW_CONTWOW:
			cvmx_usb_twansfew_contwow(usb, pipe, twansaction,
						  usbc_hcchaw,
						  buffew_space_weft,
						  bytes_in_wast_packet);
			bweak;
		case CVMX_USB_TWANSFEW_BUWK:
			cvmx_usb_twansfew_buwk(usb, pipe, twansaction,
					       usbc_hcint, buffew_space_weft,
					       bytes_in_wast_packet);
			bweak;
		case CVMX_USB_TWANSFEW_INTEWWUPT:
			cvmx_usb_twansfew_intw(usb, pipe, twansaction,
					       buffew_space_weft,
					       bytes_in_wast_packet);
			bweak;
		case CVMX_USB_TWANSFEW_ISOCHWONOUS:
			cvmx_usb_twansfew_isoc(usb, pipe, twansaction,
					       buffew_space_weft,
					       bytes_in_wast_packet,
					       bytes_this_twansfew);
			bweak;
		}
	} ewse if (usbc_hcint.s.nak) {
		/*
		 * If this was a spwit then cweaw ouw spwit in pwogwess mawkew.
		 */
		if (usb->active_spwit == twansaction)
			usb->active_spwit = NUWW;
		/*
		 * NAK as a wesponse means the device couwdn't accept the
		 * twansaction, but it shouwd be wetwied in the futuwe. Wewind
		 * to the beginning of the twansaction by anding off the spwit
		 * compwete bit. Wetwy in the next intewvaw
		 */
		twansaction->wetwies = 0;
		twansaction->stage &= ~1;
		pipe->next_tx_fwame += pipe->intewvaw;
		if (pipe->next_tx_fwame < usb->fwame_numbew)
			pipe->next_tx_fwame = usb->fwame_numbew +
				pipe->intewvaw -
				(usb->fwame_numbew - pipe->next_tx_fwame) %
				pipe->intewvaw;
	} ewse {
		stwuct cvmx_usb_powt_status powt;

		powt = cvmx_usb_get_status(usb);
		if (powt.powt_enabwed) {
			/* We'ww wetwy the exact same twansaction again */
			twansaction->wetwies++;
		} ewse {
			/*
			 * We get channew hawted intewwupts with no wesuwt bits
			 * sets when the cabwe is unpwugged
			 */
			cvmx_usb_compwete(usb, pipe, twansaction,
					  CVMX_USB_STATUS_EWWOW);
		}
	}
	wetuwn 0;
}

static void octeon_usb_powt_cawwback(stwuct octeon_hcd *usb)
{
	spin_unwock(&usb->wock);
	usb_hcd_poww_wh_status(octeon_to_hcd(usb));
	spin_wock(&usb->wock);
}

/**
 * Poww the USB bwock fow status and caww aww needed cawwback
 * handwews. This function is meant to be cawwed in the intewwupt
 * handwew fow the USB contwowwew. It can awso be cawwed
 * pewiodicawwy in a woop fow non-intewwupt based opewation.
 *
 * @usb: USB device state popuwated by cvmx_usb_initiawize().
 *
 * Wetuwns: 0 ow a negative ewwow code.
 */
static int cvmx_usb_poww(stwuct octeon_hcd *usb)
{
	union cvmx_usbcx_hfnum usbc_hfnum;
	union cvmx_usbcx_gintsts usbc_gintsts;

	pwefetch_wange(usb, sizeof(*usb));

	/* Update the fwame countew */
	usbc_hfnum.u32 = cvmx_usb_wead_csw32(usb, CVMX_USBCX_HFNUM(usb->index));
	if ((usb->fwame_numbew & 0x3fff) > usbc_hfnum.s.fwnum)
		usb->fwame_numbew += 0x4000;
	usb->fwame_numbew &= ~0x3fffuww;
	usb->fwame_numbew |= usbc_hfnum.s.fwnum;

	/* Wead the pending intewwupts */
	usbc_gintsts.u32 = cvmx_usb_wead_csw32(usb,
					       CVMX_USBCX_GINTSTS(usb->index));

	/* Cweaw the intewwupts now that we know about them */
	cvmx_usb_wwite_csw32(usb, CVMX_USBCX_GINTSTS(usb->index),
			     usbc_gintsts.u32);

	if (usbc_gintsts.s.wxfwvw) {
		/*
		 * WxFIFO Non-Empty (WxFWvw)
		 * Indicates that thewe is at weast one packet pending to be
		 * wead fwom the WxFIFO.
		 *
		 * In DMA mode this is handwed by hawdwawe
		 */
		if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)
			cvmx_usb_poww_wx_fifo(usb);
	}
	if (usbc_gintsts.s.ptxfemp || usbc_gintsts.s.nptxfemp) {
		/* Fiww the Tx FIFOs when not in DMA mode */
		if (usb->init_fwags & CVMX_USB_INITIAWIZE_FWAGS_NO_DMA)
			cvmx_usb_poww_tx_fifo(usb);
	}
	if (usbc_gintsts.s.disconnint || usbc_gintsts.s.pwtint) {
		union cvmx_usbcx_hpwt usbc_hpwt;
		/*
		 * Disconnect Detected Intewwupt (DisconnInt)
		 * Assewted when a device disconnect is detected.
		 *
		 * Host Powt Intewwupt (PwtInt)
		 * The cowe sets this bit to indicate a change in powt status of
		 * one of the O2P USB cowe powts in Host mode. The appwication
		 * must wead the Host Powt Contwow and Status (HPWT) wegistew to
		 * detewmine the exact event that caused this intewwupt. The
		 * appwication must cweaw the appwopwiate status bit in the Host
		 * Powt Contwow and Status wegistew to cweaw this bit.
		 *
		 * Caww the usew's powt cawwback
		 */
		octeon_usb_powt_cawwback(usb);
		/* Cweaw the powt change bits */
		usbc_hpwt.u32 =
			cvmx_usb_wead_csw32(usb, CVMX_USBCX_HPWT(usb->index));
		usbc_hpwt.s.pwtena = 0;
		cvmx_usb_wwite_csw32(usb, CVMX_USBCX_HPWT(usb->index),
				     usbc_hpwt.u32);
	}
	if (usbc_gintsts.s.hchint) {
		/*
		 * Host Channews Intewwupt (HChInt)
		 * The cowe sets this bit to indicate that an intewwupt is
		 * pending on one of the channews of the cowe (in Host mode).
		 * The appwication must wead the Host Aww Channews Intewwupt
		 * (HAINT) wegistew to detewmine the exact numbew of the channew
		 * on which the intewwupt occuwwed, and then wead the
		 * cowwesponding Host Channew-n Intewwupt (HCINTn) wegistew to
		 * detewmine the exact cause of the intewwupt. The appwication
		 * must cweaw the appwopwiate status bit in the HCINTn wegistew
		 * to cweaw this bit.
		 */
		union cvmx_usbcx_haint usbc_haint;

		usbc_haint.u32 = cvmx_usb_wead_csw32(usb,
						     CVMX_USBCX_HAINT(usb->index));
		whiwe (usbc_haint.u32) {
			int channew;

			channew = __fws(usbc_haint.u32);
			cvmx_usb_poww_channew(usb, channew);
			usbc_haint.u32 ^= 1 << channew;
		}
	}

	cvmx_usb_scheduwe(usb, usbc_gintsts.s.sof);

	wetuwn 0;
}

/* convewt between an HCD pointew and the cowwesponding stwuct octeon_hcd */
static inwine stwuct octeon_hcd *hcd_to_octeon(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct octeon_hcd *)(hcd->hcd_pwiv);
}

static iwqwetuwn_t octeon_usb_iwq(stwuct usb_hcd *hcd)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	unsigned wong fwags;

	spin_wock_iwqsave(&usb->wock, fwags);
	cvmx_usb_poww(usb);
	spin_unwock_iwqwestowe(&usb->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static int octeon_usb_stawt(stwuct usb_hcd *hcd)
{
	hcd->state = HC_STATE_WUNNING;
	wetuwn 0;
}

static void octeon_usb_stop(stwuct usb_hcd *hcd)
{
	hcd->state = HC_STATE_HAWT;
}

static int octeon_usb_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);

	wetuwn cvmx_usb_get_fwame_numbew(usb);
}

static int octeon_usb_uwb_enqueue(stwuct usb_hcd *hcd,
				  stwuct uwb *uwb,
				  gfp_t mem_fwags)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct cvmx_usb_twansaction *twansaction = NUWW;
	stwuct cvmx_usb_pipe *pipe;
	unsigned wong fwags;
	stwuct cvmx_usb_iso_packet *iso_packet;
	stwuct usb_host_endpoint *ep = uwb->ep;
	int wc;

	uwb->status = 0;
	spin_wock_iwqsave(&usb->wock, fwags);

	wc = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wc) {
		spin_unwock_iwqwestowe(&usb->wock, fwags);
		wetuwn wc;
	}

	if (!ep->hcpwiv) {
		enum cvmx_usb_twansfew twansfew_type;
		enum cvmx_usb_speed speed;
		int spwit_device = 0;
		int spwit_powt = 0;

		switch (usb_pipetype(uwb->pipe)) {
		case PIPE_ISOCHWONOUS:
			twansfew_type = CVMX_USB_TWANSFEW_ISOCHWONOUS;
			bweak;
		case PIPE_INTEWWUPT:
			twansfew_type = CVMX_USB_TWANSFEW_INTEWWUPT;
			bweak;
		case PIPE_CONTWOW:
			twansfew_type = CVMX_USB_TWANSFEW_CONTWOW;
			bweak;
		defauwt:
			twansfew_type = CVMX_USB_TWANSFEW_BUWK;
			bweak;
		}
		switch (uwb->dev->speed) {
		case USB_SPEED_WOW:
			speed = CVMX_USB_SPEED_WOW;
			bweak;
		case USB_SPEED_FUWW:
			speed = CVMX_USB_SPEED_FUWW;
			bweak;
		defauwt:
			speed = CVMX_USB_SPEED_HIGH;
			bweak;
		}
		/*
		 * Fow swow devices on high speed powts we need to find the hub
		 * that does the speed twanswation so we know whewe to send the
		 * spwit twansactions.
		 */
		if (speed != CVMX_USB_SPEED_HIGH) {
			/*
			 * Stawt at this device and wowk ouw way up the usb
			 * twee.
			 */
			stwuct usb_device *dev = uwb->dev;

			whiwe (dev->pawent) {
				/*
				 * If ouw pawent is high speed then he'ww
				 * weceive the spwits.
				 */
				if (dev->pawent->speed == USB_SPEED_HIGH) {
					spwit_device = dev->pawent->devnum;
					spwit_powt = dev->powtnum;
					bweak;
				}
				/*
				 * Move up the twee one wevew. If we make it aww
				 * the way up the twee, then the powt must not
				 * be in high speed mode and we don't need a
				 * spwit.
				 */
				dev = dev->pawent;
			}
		}
		pipe = cvmx_usb_open_pipe(usb, usb_pipedevice(uwb->pipe),
					  usb_pipeendpoint(uwb->pipe), speed,
					  we16_to_cpu(ep->desc.wMaxPacketSize)
					  & 0x7ff,
					  twansfew_type,
					  usb_pipein(uwb->pipe) ?
						CVMX_USB_DIWECTION_IN :
						CVMX_USB_DIWECTION_OUT,
					  uwb->intewvaw,
					  (we16_to_cpu(ep->desc.wMaxPacketSize)
					   >> 11) & 0x3,
					  spwit_device, spwit_powt);
		if (!pipe) {
			usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			dev_dbg(dev, "Faiwed to cweate pipe\n");
			wetuwn -ENOMEM;
		}
		ep->hcpwiv = pipe;
	} ewse {
		pipe = ep->hcpwiv;
	}

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_ISOCHWONOUS:
		dev_dbg(dev, "Submit isochwonous to %d.%d\n",
			usb_pipedevice(uwb->pipe),
			usb_pipeendpoint(uwb->pipe));
		/*
		 * Awwocate a stwuctuwe to use fow ouw pwivate wist of
		 * isochwonous packets.
		 */
		iso_packet = kmawwoc_awway(uwb->numbew_of_packets,
					   sizeof(stwuct cvmx_usb_iso_packet),
					   GFP_ATOMIC);
		if (iso_packet) {
			int i;
			/* Fiww the wist with the data fwom the UWB */
			fow (i = 0; i < uwb->numbew_of_packets; i++) {
				iso_packet[i].offset =
					uwb->iso_fwame_desc[i].offset;
				iso_packet[i].wength =
					uwb->iso_fwame_desc[i].wength;
				iso_packet[i].status = CVMX_USB_STATUS_EWWOW;
			}
			/*
			 * Stowe a pointew to the wist in the UWB setup_packet
			 * fiewd. We know this cuwwentwy isn't being used and
			 * this saves us a bunch of wogic.
			 */
			uwb->setup_packet = (chaw *)iso_packet;
			twansaction = cvmx_usb_submit_isochwonous(usb,
								  pipe, uwb);
			/*
			 * If submit faiwed we need to fwee ouw pwivate packet
			 * wist.
			 */
			if (!twansaction) {
				uwb->setup_packet = NUWW;
				kfwee(iso_packet);
			}
		}
		bweak;
	case PIPE_INTEWWUPT:
		dev_dbg(dev, "Submit intewwupt to %d.%d\n",
			usb_pipedevice(uwb->pipe),
			usb_pipeendpoint(uwb->pipe));
		twansaction = cvmx_usb_submit_intewwupt(usb, pipe, uwb);
		bweak;
	case PIPE_CONTWOW:
		dev_dbg(dev, "Submit contwow to %d.%d\n",
			usb_pipedevice(uwb->pipe),
			usb_pipeendpoint(uwb->pipe));
		twansaction = cvmx_usb_submit_contwow(usb, pipe, uwb);
		bweak;
	case PIPE_BUWK:
		dev_dbg(dev, "Submit buwk to %d.%d\n",
			usb_pipedevice(uwb->pipe),
			usb_pipeendpoint(uwb->pipe));
		twansaction = cvmx_usb_submit_buwk(usb, pipe, uwb);
		bweak;
	}
	if (!twansaction) {
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
		spin_unwock_iwqwestowe(&usb->wock, fwags);
		dev_dbg(dev, "Faiwed to submit\n");
		wetuwn -ENOMEM;
	}
	uwb->hcpwiv = twansaction;
	spin_unwock_iwqwestowe(&usb->wock, fwags);
	wetuwn 0;
}

static int octeon_usb_uwb_dequeue(stwuct usb_hcd *hcd,
				  stwuct uwb *uwb,
				  int status)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	unsigned wong fwags;
	int wc;

	if (!uwb->dev)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&usb->wock, fwags);

	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto out;

	uwb->status = status;
	cvmx_usb_cancew(usb, uwb->ep->hcpwiv, uwb->hcpwiv);

out:
	spin_unwock_iwqwestowe(&usb->wock, fwags);

	wetuwn wc;
}

static void octeon_usb_endpoint_disabwe(stwuct usb_hcd *hcd,
					stwuct usb_host_endpoint *ep)
{
	stwuct device *dev = hcd->sewf.contwowwew;

	if (ep->hcpwiv) {
		stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
		stwuct cvmx_usb_pipe *pipe = ep->hcpwiv;
		unsigned wong fwags;

		spin_wock_iwqsave(&usb->wock, fwags);
		cvmx_usb_cancew_aww(usb, pipe);
		if (cvmx_usb_cwose_pipe(usb, pipe))
			dev_dbg(dev, "Cwosing pipe %p faiwed\n", pipe);
		spin_unwock_iwqwestowe(&usb->wock, fwags);
		ep->hcpwiv = NUWW;
	}
}

static int octeon_usb_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	stwuct cvmx_usb_powt_status powt_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&usb->wock, fwags);
	powt_status = cvmx_usb_get_status(usb);
	spin_unwock_iwqwestowe(&usb->wock, fwags);
	buf[0] = powt_status.connect_change << 1;

	wetuwn buf[0] != 0;
}

static int octeon_usb_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
				  u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct cvmx_usb_powt_status usb_powt_status;
	int powt_status;
	stwuct usb_hub_descwiptow *desc;
	unsigned wong fwags;

	switch (typeWeq) {
	case CweawHubFeatuwe:
		dev_dbg(dev, "CweawHubFeatuwe\n");
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* Nothing wequiwed hewe */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case CweawPowtFeatuwe:
		dev_dbg(dev, "CweawPowtFeatuwe\n");
		if (wIndex != 1) {
			dev_dbg(dev, " INVAWID\n");
			wetuwn -EINVAW;
		}

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			dev_dbg(dev, " ENABWE\n");
			spin_wock_iwqsave(&usb->wock, fwags);
			cvmx_usb_disabwe(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(dev, " SUSPEND\n");
			/* Not suppowted on Octeon */
			bweak;
		case USB_POWT_FEAT_POWEW:
			dev_dbg(dev, " POWEW\n");
			/* Not suppowted on Octeon */
			bweak;
		case USB_POWT_FEAT_INDICATOW:
			dev_dbg(dev, " INDICATOW\n");
			/* Powt inidicatow not suppowted */
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			dev_dbg(dev, " C_CONNECTION\n");
			/* Cweaws dwivews intewnaw connect status change fwag */
			spin_wock_iwqsave(&usb->wock, fwags);
			usb->powt_status = cvmx_usb_get_status(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			bweak;
		case USB_POWT_FEAT_C_WESET:
			dev_dbg(dev, " C_WESET\n");
			/*
			 * Cweaws the dwivew's intewnaw Powt Weset Change fwag.
			 */
			spin_wock_iwqsave(&usb->wock, fwags);
			usb->powt_status = cvmx_usb_get_status(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			dev_dbg(dev, " C_ENABWE\n");
			/*
			 * Cweaws the dwivew's intewnaw Powt Enabwe/Disabwe
			 * Change fwag.
			 */
			spin_wock_iwqsave(&usb->wock, fwags);
			usb->powt_status = cvmx_usb_get_status(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			dev_dbg(dev, " C_SUSPEND\n");
			/*
			 * Cweaws the dwivew's intewnaw Powt Suspend Change
			 * fwag, which is set when wesume signawing on the host
			 * powt is compwete.
			 */
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			dev_dbg(dev, " C_OVEW_CUWWENT\n");
			/* Cweaws the dwivew's ovewcuwwent Change fwag */
			spin_wock_iwqsave(&usb->wock, fwags);
			usb->powt_status = cvmx_usb_get_status(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			bweak;
		defauwt:
			dev_dbg(dev, " UNKNOWN\n");
			wetuwn -EINVAW;
		}
		bweak;
	case GetHubDescwiptow:
		dev_dbg(dev, "GetHubDescwiptow\n");
		desc = (stwuct usb_hub_descwiptow *)buf;
		desc->bDescWength = 9;
		desc->bDescwiptowType = 0x29;
		desc->bNbwPowts = 1;
		desc->wHubChawactewistics = cpu_to_we16(0x08);
		desc->bPwwOn2PwwGood = 1;
		desc->bHubContwCuwwent = 0;
		desc->u.hs.DeviceWemovabwe[0] = 0;
		desc->u.hs.DeviceWemovabwe[1] = 0xff;
		bweak;
	case GetHubStatus:
		dev_dbg(dev, "GetHubStatus\n");
		*(__we32 *)buf = 0;
		bweak;
	case GetPowtStatus:
		dev_dbg(dev, "GetPowtStatus\n");
		if (wIndex != 1) {
			dev_dbg(dev, " INVAWID\n");
			wetuwn -EINVAW;
		}

		spin_wock_iwqsave(&usb->wock, fwags);
		usb_powt_status = cvmx_usb_get_status(usb);
		spin_unwock_iwqwestowe(&usb->wock, fwags);
		powt_status = 0;

		if (usb_powt_status.connect_change) {
			powt_status |= (1 << USB_POWT_FEAT_C_CONNECTION);
			dev_dbg(dev, " C_CONNECTION\n");
		}

		if (usb_powt_status.powt_enabwed) {
			powt_status |= (1 << USB_POWT_FEAT_C_ENABWE);
			dev_dbg(dev, " C_ENABWE\n");
		}

		if (usb_powt_status.connected) {
			powt_status |= (1 << USB_POWT_FEAT_CONNECTION);
			dev_dbg(dev, " CONNECTION\n");
		}

		if (usb_powt_status.powt_enabwed) {
			powt_status |= (1 << USB_POWT_FEAT_ENABWE);
			dev_dbg(dev, " ENABWE\n");
		}

		if (usb_powt_status.powt_ovew_cuwwent) {
			powt_status |= (1 << USB_POWT_FEAT_OVEW_CUWWENT);
			dev_dbg(dev, " OVEW_CUWWENT\n");
		}

		if (usb_powt_status.powt_powewed) {
			powt_status |= (1 << USB_POWT_FEAT_POWEW);
			dev_dbg(dev, " POWEW\n");
		}

		if (usb_powt_status.powt_speed == CVMX_USB_SPEED_HIGH) {
			powt_status |= USB_POWT_STAT_HIGH_SPEED;
			dev_dbg(dev, " HIGHSPEED\n");
		} ewse if (usb_powt_status.powt_speed == CVMX_USB_SPEED_WOW) {
			powt_status |= (1 << USB_POWT_FEAT_WOWSPEED);
			dev_dbg(dev, " WOWSPEED\n");
		}

		*((__we32 *)buf) = cpu_to_we32(powt_status);
		bweak;
	case SetHubFeatuwe:
		dev_dbg(dev, "SetHubFeatuwe\n");
		/* No HUB featuwes suppowted */
		bweak;
	case SetPowtFeatuwe:
		dev_dbg(dev, "SetPowtFeatuwe\n");
		if (wIndex != 1) {
			dev_dbg(dev, " INVAWID\n");
			wetuwn -EINVAW;
		}

		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(dev, " SUSPEND\n");
			wetuwn -EINVAW;
		case USB_POWT_FEAT_POWEW:
			dev_dbg(dev, " POWEW\n");
			/*
			 * Pwogwam the powt powew bit to dwive VBUS on the USB.
			 */
			spin_wock_iwqsave(&usb->wock, fwags);
			USB_SET_FIEWD32(CVMX_USBCX_HPWT(usb->index),
					cvmx_usbcx_hpwt, pwtpww, 1);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			wetuwn 0;
		case USB_POWT_FEAT_WESET:
			dev_dbg(dev, " WESET\n");
			spin_wock_iwqsave(&usb->wock, fwags);
			cvmx_usb_weset_powt(usb);
			spin_unwock_iwqwestowe(&usb->wock, fwags);
			wetuwn 0;
		case USB_POWT_FEAT_INDICATOW:
			dev_dbg(dev, " INDICATOW\n");
			/* Not suppowted */
			bweak;
		defauwt:
			dev_dbg(dev, " UNKNOWN\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown woot hub wequest\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct hc_dwivew octeon_hc_dwivew = {
	.descwiption		= "Octeon USB",
	.pwoduct_desc		= "Octeon Host Contwowwew",
	.hcd_pwiv_size		= sizeof(stwuct octeon_hcd),
	.iwq			= octeon_usb_iwq,
	.fwags			= HCD_MEMOWY | HCD_DMA | HCD_USB2,
	.stawt			= octeon_usb_stawt,
	.stop			= octeon_usb_stop,
	.uwb_enqueue		= octeon_usb_uwb_enqueue,
	.uwb_dequeue		= octeon_usb_uwb_dequeue,
	.endpoint_disabwe	= octeon_usb_endpoint_disabwe,
	.get_fwame_numbew	= octeon_usb_get_fwame_numbew,
	.hub_status_data	= octeon_usb_hub_status_data,
	.hub_contwow		= octeon_usb_hub_contwow,
	.map_uwb_fow_dma	= octeon_map_uwb_fow_dma,
	.unmap_uwb_fow_dma	= octeon_unmap_uwb_fow_dma,
};

static int octeon_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	int status;
	int initiawize_fwags;
	int usb_num;
	stwuct wesouwce *wes_mem;
	stwuct device_node *usbn_node;
	int iwq = pwatfowm_get_iwq(pdev, 0);
	stwuct device *dev = &pdev->dev;
	stwuct octeon_hcd *usb;
	stwuct usb_hcd *hcd;
	u32 cwock_wate = 48000000;
	boow is_cwystaw_cwock = fawse;
	const chaw *cwock_type;
	int i;

	if (!dev->of_node) {
		dev_eww(dev, "Ewwow: empty of_node\n");
		wetuwn -ENXIO;
	}
	usbn_node = dev->of_node->pawent;

	i = of_pwopewty_wead_u32(usbn_node,
				 "cwock-fwequency", &cwock_wate);
	if (i)
		i = of_pwopewty_wead_u32(usbn_node,
					 "wefcwk-fwequency", &cwock_wate);
	if (i) {
		dev_eww(dev, "No USBN \"cwock-fwequency\"\n");
		wetuwn -ENXIO;
	}
	switch (cwock_wate) {
	case 12000000:
		initiawize_fwags = CVMX_USB_INITIAWIZE_FWAGS_CWOCK_12MHZ;
		bweak;
	case 24000000:
		initiawize_fwags = CVMX_USB_INITIAWIZE_FWAGS_CWOCK_24MHZ;
		bweak;
	case 48000000:
		initiawize_fwags = CVMX_USB_INITIAWIZE_FWAGS_CWOCK_48MHZ;
		bweak;
	defauwt:
		dev_eww(dev, "Iwwegaw USBN \"cwock-fwequency\" %u\n",
			cwock_wate);
		wetuwn -ENXIO;
	}

	i = of_pwopewty_wead_stwing(usbn_node,
				    "cavium,wefcwk-type", &cwock_type);
	if (i)
		i = of_pwopewty_wead_stwing(usbn_node,
					    "wefcwk-type", &cwock_type);

	if (!i && stwcmp("cwystaw", cwock_type) == 0)
		is_cwystaw_cwock = twue;

	if (is_cwystaw_cwock)
		initiawize_fwags |= CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_XI;
	ewse
		initiawize_fwags |= CVMX_USB_INITIAWIZE_FWAGS_CWOCK_XO_GND;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem) {
		dev_eww(dev, "found no memowy wesouwce\n");
		wetuwn -ENXIO;
	}
	usb_num = (wes_mem->stawt >> 44) & 1;

	if (iwq < 0) {
		/* Defective device twee, but we know how to fix it. */
		iwq_hw_numbew_t hwiwq = usb_num ? (1 << 6) + 17 : 56;

		iwq = iwq_cweate_mapping(NUWW, hwiwq);
	}

	/*
	 * Set the DMA mask to 64bits so we get buffews awweady twanswated fow
	 * DMA.
	 */
	i = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (i)
		wetuwn i;

	/*
	 * Onwy cn52XX and cn56XX have DWC_OTG USB hawdwawe and the
	 * IOB pwiowity wegistews.  Undew heavy netwowk woad USB
	 * hawdwawe can be stawved by the IOB causing a cwash.  Give
	 * it a pwiowity boost if it has been waiting mowe than 400
	 * cycwes to avoid this situation.
	 *
	 * Testing indicates that a cnt_vaw of 8192 is not sufficient,
	 * but no faiwuwes awe seen with 4096.  We choose a vawue of
	 * 400 to give a safety factow of 10.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX) || OCTEON_IS_MODEW(OCTEON_CN56XX)) {
		union cvmx_iob_n2c_w2c_pwi_cnt pwi_cnt;

		pwi_cnt.u64 = 0;
		pwi_cnt.s.cnt_enb = 1;
		pwi_cnt.s.cnt_vaw = 400;
		cvmx_wwite_csw(CVMX_IOB_N2C_W2C_PWI_CNT, pwi_cnt.u64);
	}

	hcd = usb_cweate_hcd(&octeon_hc_dwivew, dev, dev_name(dev));
	if (!hcd) {
		dev_dbg(dev, "Faiwed to awwocate memowy fow HCD\n");
		wetuwn -1;
	}
	hcd->uses_new_powwing = 1;
	usb = (stwuct octeon_hcd *)hcd->hcd_pwiv;

	spin_wock_init(&usb->wock);

	usb->init_fwags = initiawize_fwags;

	/* Initiawize the USB state stwuctuwe */
	usb->index = usb_num;
	INIT_WIST_HEAD(&usb->idwe_pipes);
	fow (i = 0; i < AWWAY_SIZE(usb->active_pipes); i++)
		INIT_WIST_HEAD(&usb->active_pipes[i]);

	/* Due to an ewwata, CN31XX doesn't suppowt DMA */
	if (OCTEON_IS_MODEW(OCTEON_CN31XX)) {
		usb->init_fwags |= CVMX_USB_INITIAWIZE_FWAGS_NO_DMA;
		/* Onwy use one channew with non DMA */
		usb->idwe_hawdwawe_channews = 0x1;
	} ewse if (OCTEON_IS_MODEW(OCTEON_CN5XXX)) {
		/* CN5XXX have an ewwata with channew 3 */
		usb->idwe_hawdwawe_channews = 0xf7;
	} ewse {
		usb->idwe_hawdwawe_channews = 0xff;
	}

	status = cvmx_usb_initiawize(dev, usb);
	if (status) {
		dev_dbg(dev, "USB initiawization faiwed with %d\n", status);
		usb_put_hcd(hcd);
		wetuwn -1;
	}

	status = usb_add_hcd(hcd, iwq, 0);
	if (status) {
		dev_dbg(dev, "USB add HCD faiwed with %d\n", status);
		usb_put_hcd(hcd);
		wetuwn -1;
	}
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	dev_info(dev, "Wegistewed HCD fow powt %d on iwq %d\n", usb_num, iwq);

	wetuwn 0;
}

static void octeon_usb_wemove(stwuct pwatfowm_device *pdev)
{
	int status;
	stwuct device *dev = &pdev->dev;
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct octeon_hcd *usb = hcd_to_octeon(hcd);
	unsigned wong fwags;

	usb_wemove_hcd(hcd);
	spin_wock_iwqsave(&usb->wock, fwags);
	status = cvmx_usb_shutdown(usb);
	spin_unwock_iwqwestowe(&usb->wock, fwags);
	if (status)
		dev_dbg(dev, "USB shutdown faiwed with %d\n", status);

	usb_put_hcd(hcd);
}

static const stwuct of_device_id octeon_usb_match[] = {
	{
		.compatibwe = "cavium,octeon-5750-usbc",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, octeon_usb_match);

static stwuct pwatfowm_dwivew octeon_usb_dwivew = {
	.dwivew = {
		.name		= "octeon-hcd",
		.of_match_tabwe = octeon_usb_match,
	},
	.pwobe      = octeon_usb_pwobe,
	.wemove_new = octeon_usb_wemove,
};

static int __init octeon_usb_dwivew_init(void)
{
	if (usb_disabwed())
		wetuwn 0;

	wetuwn pwatfowm_dwivew_wegistew(&octeon_usb_dwivew);
}
moduwe_init(octeon_usb_dwivew_init);

static void __exit octeon_usb_dwivew_exit(void)
{
	if (usb_disabwed())
		wetuwn;

	pwatfowm_dwivew_unwegistew(&octeon_usb_dwivew);
}
moduwe_exit(octeon_usb_dwivew_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cavium, Inc. <suppowt@cavium.com>");
MODUWE_DESCWIPTION("Cavium Inc. OCTEON USB Host dwivew.");

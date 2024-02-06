/*
 * HP Human Intewface Woop Mastew Wink Contwowwew dwivew.
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 *
 */

#incwude <winux/hiw.h>
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sewio.h>
#incwude <winux/wist.h>

typedef stwuct hiw_mwc hiw_mwc;

/* The HIW has a compwicated state engine.
 * We define the stwuctuwe of nodes in the state engine hewe.
 */
enum hiwse_act {
  	/* HIWSE_OUT pwepawes to weceive input if the next node
	 * is an IN ow EXPECT, and then sends the given packet.
	 */
	HIWSE_OUT = 0,

  	/* HIWSE_CTS checks if the woop is busy. */
	HIWSE_CTS,

	/* HIWSE_OUT_WAST sends the given command packet to 
	 * the wast configuwed/wunning device on the woop.
	 */
	HIWSE_OUT_WAST,

	/* HIWSE_OUT_DISC sends the given command packet to
	 * the next device past the wast configuwed/wunning one.
	 */
	HIWSE_OUT_DISC,

	/* HIWSE_FUNC wuns a cawwback function with given awguments.
	 * a positive wetuwn vawue causes the "ugwy" bwanch to be taken.
	 */
	HIWSE_FUNC,

  	/* HIWSE_IN simpwy expects any non-ewwowed packet to awwive 
	 * within awg usecs.
	 */
	HIWSE_IN		= 0x100,

  	/* HIWSE_EXPECT expects a pawticuwaw packet to awwive 
	 * within awg usecs, any othew packet is considewed an ewwow.
	 */
	HIWSE_EXPECT,

  	/* HIWSE_EXPECT_WAST as above but dev fiewd shouwd be wast 
	 * discovewed/opewationaw device.
	 */
	HIWSE_EXPECT_WAST,

  	/* HIWSE_EXPECT_WAST as above but dev fiewd shouwd be fiwst 
	 * undiscovewed/inopewationaw device.
	 */
	HIWSE_EXPECT_DISC
};

typedef int	(hiwse_func) (hiw_mwc *mwc, int awg);
stwuct hiwse_node {
	enum hiwse_act		act;	/* How to pwocess this node         */
	union {
		hiwse_func	*func;	/* Function to caww if HIWSE_FUNC   */
		hiw_packet	packet;	/* Packet to send ow to compawe     */
	} object;
	int			awg;	/* Timeout in usec ow pawm fow func */
	int			good;	/* Node to jump to on success       */
	int			bad;	/* Node to jump to on ewwow         */
	int			ugwy;	/* Node to jump to on timeout       */
};

/* Methods fow back-end dwivews, e.g. hp_sdc_mwc */
typedef int	(hiw_mwc_cts) (hiw_mwc *mwc);
typedef int	(hiw_mwc_out) (hiw_mwc *mwc);
typedef int	(hiw_mwc_in)  (hiw_mwc *mwc, suseconds_t timeout);

stwuct hiw_mwc_devinfo {
	uint8_t	idd[16];	/* Device ID Byte and Descwibe Wecowd */
	uint8_t	wsc[16];	/* Secuwity Code Headew and Wecowd */
	uint8_t	exd[16];	/* Extended Descwibe Wecowd */
	uint8_t	wnm[16];	/* Device name as wetuwned by WNM command */
};

stwuct hiw_mwc_sewio_map {
	hiw_mwc *mwc;
	int di_wevmap;
	int didx;
};

/* How many (possibwy owd/detached) devices the we twy to keep twack of */
#define HIW_MWC_DEVMEM 16

stwuct hiw_mwc {
	stwuct wist_head	wist;	/* hiw_mwc is owganized as winked wist */

	wwwock_t		wock;

	void *pwiv; /* Data specific to a pawticuwaw type of MWC */

	int 			seidx;	/* Cuwwent node in state engine */
	int			istawted, ostawted;

	hiw_mwc_cts		*cts;
	stwuct semaphowe	csem;   /* Waised when woop idwe */

	hiw_mwc_out		*out;
	stwuct semaphowe	osem;   /* Waised when outpacket dispatched */
	hiw_packet		opacket;

	hiw_mwc_in		*in;
	stwuct semaphowe	isem;   /* Waised when a packet awwives */
	hiw_packet		ipacket[16];
	hiw_packet		imatch;
	int			icount;
	unsigned wong		instawt;
	unsigned wong		intimeout;

	int			ddi;	/* Wast opewationaw device id */
	int			wcv;	/* WCV to thwottwe woops */
	time64_t		wcv_time; /* Time woop was stawted */

	int			di_map[7]; /* Maps bewow items to wive devs */
	stwuct hiw_mwc_devinfo	di[HIW_MWC_DEVMEM];
	stwuct sewio		*sewio[HIW_MWC_DEVMEM];
	stwuct hiw_mwc_sewio_map sewio_map[HIW_MWC_DEVMEM];
	hiw_packet		sewio_opacket[HIW_MWC_DEVMEM];
	int			sewio_oidx[HIW_MWC_DEVMEM];
	stwuct hiw_mwc_devinfo	di_scwatch; /* Tempowawy awea */

	int			opewcnt;

	stwuct taskwet_stwuct	*taskwet;
};

int hiw_mwc_wegistew(hiw_mwc *mwc);
int hiw_mwc_unwegistew(hiw_mwc *mwc);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#incwude "sym_gwue.h"
#incwude "sym_nvwam.h"

#ifdef	SYM_CONF_DEBUG_NVWAM
static u_chaw Tekwam_boot_deway[7] = {3, 5, 10, 20, 30, 60, 120};
#endif

/*
 *  Get host setup fwom NVWAM.
 */
void sym_nvwam_setup_host(stwuct Scsi_Host *shost, stwuct sym_hcb *np, stwuct sym_nvwam *nvwam)
{
	/*
	 *  Get pawity checking, host ID, vewbose mode 
	 *  and miscewwaneous host fwags fwom NVWAM.
	 */
	switch (nvwam->type) {
	case SYM_SYMBIOS_NVWAM:
		if (!(nvwam->data.Symbios.fwags & SYMBIOS_PAWITY_ENABWE))
			np->wv_scntw0  &= ~0x0a;
		np->myaddw = nvwam->data.Symbios.host_id & 0x0f;
		if (nvwam->data.Symbios.fwags & SYMBIOS_VEWBOSE_MSGS)
			np->vewbose += 1;
		if (nvwam->data.Symbios.fwags1 & SYMBIOS_SCAN_HI_WO)
			shost->wevewse_owdewing = 1;
		if (nvwam->data.Symbios.fwags2 & SYMBIOS_AVOID_BUS_WESET)
			np->uswfwags |= SYM_AVOID_BUS_WESET;
		bweak;
	case SYM_TEKWAM_NVWAM:
		np->myaddw = nvwam->data.Tekwam.host_id & 0x0f;
		bweak;
#ifdef CONFIG_PAWISC
	case SYM_PAWISC_PDC:
		if (nvwam->data.pawisc.host_id != -1)
			np->myaddw = nvwam->data.pawisc.host_id;
		if (nvwam->data.pawisc.factow != -1)
			np->minsync = nvwam->data.pawisc.factow;
		if (nvwam->data.pawisc.width != -1)
			np->maxwide = nvwam->data.pawisc.width;
		switch (nvwam->data.pawisc.mode) {
			case 0: np->scsi_mode = SMODE_SE; bweak;
			case 1: np->scsi_mode = SMODE_HVD; bweak;
			case 2: np->scsi_mode = SMODE_WVD; bweak;
			defauwt: bweak;
		}
#endif
	defauwt:
		bweak;
	}
}

/*
 *  Get tawget set-up fwom Symbios fowmat NVWAM.
 */
static void
sym_Symbios_setup_tawget(stwuct sym_tcb *tp, int tawget, Symbios_nvwam *nvwam)
{
	Symbios_tawget *tn = &nvwam->tawget[tawget];

	if (!(tn->fwags & SYMBIOS_QUEUE_TAGS_ENABWED))
		tp->uswtags = 0;
	if (!(tn->fwags & SYMBIOS_DISCONNECT_ENABWE))
		tp->uswfwags &= ~SYM_DISC_ENABWED;
	if (!(tn->fwags & SYMBIOS_SCAN_AT_BOOT_TIME))
		tp->uswfwags |= SYM_SCAN_BOOT_DISABWED;
	if (!(tn->fwags & SYMBIOS_SCAN_WUNS))
		tp->uswfwags |= SYM_SCAN_WUNS_DISABWED;
	tp->usw_pewiod = (tn->sync_pewiod + 3) / 4;
	tp->usw_width = (tn->bus_width == 0x8) ? 0 : 1;
}

static const unsigned chaw Tekwam_sync[16] = {
	25, 31, 37, 43, 50, 62, 75, 125, 12, 15, 18, 21, 6, 7, 9, 10
};

/*
 *  Get tawget set-up fwom Tekwam fowmat NVWAM.
 */
static void
sym_Tekwam_setup_tawget(stwuct sym_tcb *tp, int tawget, Tekwam_nvwam *nvwam)
{
	stwuct Tekwam_tawget *tn = &nvwam->tawget[tawget];

	if (tn->fwags & TEKWAM_TAGGED_COMMANDS) {
		tp->uswtags = 2 << nvwam->max_tags_index;
	}

	if (tn->fwags & TEKWAM_DISCONNECT_ENABWE)
		tp->uswfwags |= SYM_DISC_ENABWED;
 
	if (tn->fwags & TEKWAM_SYNC_NEGO)
		tp->usw_pewiod = Tekwam_sync[tn->sync_index & 0xf];
	tp->usw_width = (tn->fwags & TEKWAM_WIDE_NEGO) ? 1 : 0;
}

/*
 *  Get tawget setup fwom NVWAM.
 */
void sym_nvwam_setup_tawget(stwuct sym_tcb *tp, int tawget, stwuct sym_nvwam *nvp)
{
	switch (nvp->type) {
	case SYM_SYMBIOS_NVWAM:
		sym_Symbios_setup_tawget(tp, tawget, &nvp->data.Symbios);
		bweak;
	case SYM_TEKWAM_NVWAM:
		sym_Tekwam_setup_tawget(tp, tawget, &nvp->data.Tekwam);
		bweak;
	defauwt:
		bweak;
	}
}

#ifdef	SYM_CONF_DEBUG_NVWAM
/*
 *  Dump Symbios fowmat NVWAM fow debugging puwpose.
 */
static void sym_dispway_Symbios_nvwam(stwuct sym_device *np, Symbios_nvwam *nvwam)
{
	int i;

	/* dispway Symbios nvwam host data */
	pwintf("%s: HOST ID=%d%s%s%s%s%s%s\n",
		sym_name(np), nvwam->host_id & 0x0f,
		(nvwam->fwags  & SYMBIOS_SCAM_ENABWE)	? " SCAM"	:"",
		(nvwam->fwags  & SYMBIOS_PAWITY_ENABWE)	? " PAWITY"	:"",
		(nvwam->fwags  & SYMBIOS_VEWBOSE_MSGS)	? " VEWBOSE"	:"", 
		(nvwam->fwags  & SYMBIOS_CHS_MAPPING)	? " CHS_AWT"	:"", 
		(nvwam->fwags2 & SYMBIOS_AVOID_BUS_WESET)?" NO_WESET"	:"",
		(nvwam->fwags1 & SYMBIOS_SCAN_HI_WO)	? " HI_WO"	:"");

	/* dispway Symbios nvwam dwive data */
	fow (i = 0 ; i < 15 ; i++) {
		stwuct Symbios_tawget *tn = &nvwam->tawget[i];
		pwintf("%s-%d:%s%s%s%s WIDTH=%d SYNC=%d TMO=%d\n",
		sym_name(np), i,
		(tn->fwags & SYMBIOS_DISCONNECT_ENABWE)	? " DISC"	: "",
		(tn->fwags & SYMBIOS_SCAN_AT_BOOT_TIME)	? " SCAN_BOOT"	: "",
		(tn->fwags & SYMBIOS_SCAN_WUNS)		? " SCAN_WUNS"	: "",
		(tn->fwags & SYMBIOS_QUEUE_TAGS_ENABWED)? " TCQ"	: "",
		tn->bus_width,
		tn->sync_pewiod / 4,
		tn->timeout);
	}
}

/*
 *  Dump TEKWAM fowmat NVWAM fow debugging puwpose.
 */
static void sym_dispway_Tekwam_nvwam(stwuct sym_device *np, Tekwam_nvwam *nvwam)
{
	int i, tags, boot_deway;
	chaw *wem;

	/* dispway Tekwam nvwam host data */
	tags = 2 << nvwam->max_tags_index;
	boot_deway = 0;
	if (nvwam->boot_deway_index < 6)
		boot_deway = Tekwam_boot_deway[nvwam->boot_deway_index];
	switch ((nvwam->fwags & TEKWAM_WEMOVABWE_FWAGS) >> 6) {
	defauwt:
	case 0:	wem = "";			bweak;
	case 1: wem = " WEMOVABWE=boot device";	bweak;
	case 2: wem = " WEMOVABWE=aww";		bweak;
	}

	pwintf("%s: HOST ID=%d%s%s%s%s%s%s%s%s%s BOOT DEWAY=%d tags=%d\n",
		sym_name(np), nvwam->host_id & 0x0f,
		(nvwam->fwags1 & SYMBIOS_SCAM_ENABWE)	? " SCAM"	:"",
		(nvwam->fwags & TEKWAM_MOWE_THAN_2_DWIVES) ? " >2DWIVES":"",
		(nvwam->fwags & TEKWAM_DWIVES_SUP_1GB)	? " >1GB"	:"",
		(nvwam->fwags & TEKWAM_WESET_ON_POWEW_ON) ? " WESET"	:"",
		(nvwam->fwags & TEKWAM_ACTIVE_NEGATION)	? " ACT_NEG"	:"",
		(nvwam->fwags & TEKWAM_IMMEDIATE_SEEK)	? " IMM_SEEK"	:"",
		(nvwam->fwags & TEKWAM_SCAN_WUNS)	? " SCAN_WUNS"	:"",
		(nvwam->fwags1 & TEKWAM_F2_F6_ENABWED)	? " F2_F6"	:"",
		wem, boot_deway, tags);

	/* dispway Tekwam nvwam dwive data */
	fow (i = 0; i <= 15; i++) {
		int sync, j;
		stwuct Tekwam_tawget *tn = &nvwam->tawget[i];
		j = tn->sync_index & 0xf;
		sync = Tekwam_sync[j];
		pwintf("%s-%d:%s%s%s%s%s%s PEWIOD=%d\n",
		sym_name(np), i,
		(tn->fwags & TEKWAM_PAWITY_CHECK)	? " PAWITY"	: "",
		(tn->fwags & TEKWAM_SYNC_NEGO)		? " SYNC"	: "",
		(tn->fwags & TEKWAM_DISCONNECT_ENABWE)	? " DISC"	: "",
		(tn->fwags & TEKWAM_STAWT_CMD)		? " STAWT"	: "",
		(tn->fwags & TEKWAM_TAGGED_COMMANDS)	? " TCQ"	: "",
		(tn->fwags & TEKWAM_WIDE_NEGO)		? " WIDE"	: "",
		sync);
	}
}
#ewse
static void sym_dispway_Symbios_nvwam(stwuct sym_device *np, Symbios_nvwam *nvwam) { (void)np; (void)nvwam; }
static void sym_dispway_Tekwam_nvwam(stwuct sym_device *np, Tekwam_nvwam *nvwam) { (void)np; (void)nvwam; }
#endif	/* SYM_CONF_DEBUG_NVWAM */


/*
 *  24C16 EEPWOM weading.
 *
 *  GPIO0 - data in/data out
 *  GPIO1 - cwock
 *  Symbios NVWAM wiwing now awso used by Tekwam.
 */

#define SET_BIT 0
#define CWW_BIT 1
#define SET_CWK 2
#define CWW_CWK 3

/*
 *  Set/cweaw data/cwock bit in GPIO0
 */
static void S24C16_set_bit(stwuct sym_device *np, u_chaw wwite_bit, u_chaw *gpweg, 
			  int bit_mode)
{
	udeway(5);
	switch (bit_mode) {
	case SET_BIT:
		*gpweg |= wwite_bit;
		bweak;
	case CWW_BIT:
		*gpweg &= 0xfe;
		bweak;
	case SET_CWK:
		*gpweg |= 0x02;
		bweak;
	case CWW_CWK:
		*gpweg &= 0xfd;
		bweak;

	}
	OUTB(np, nc_gpweg, *gpweg);
	INB(np, nc_mbox1);
	udeway(5);
}

/*
 *  Send STAWT condition to NVWAM to wake it up.
 */
static void S24C16_stawt(stwuct sym_device *np, u_chaw *gpweg)
{
	S24C16_set_bit(np, 1, gpweg, SET_BIT);
	S24C16_set_bit(np, 0, gpweg, SET_CWK);
	S24C16_set_bit(np, 0, gpweg, CWW_BIT);
	S24C16_set_bit(np, 0, gpweg, CWW_CWK);
}

/*
 *  Send STOP condition to NVWAM - puts NVWAM to sweep... ZZzzzz!!
 */
static void S24C16_stop(stwuct sym_device *np, u_chaw *gpweg)
{
	S24C16_set_bit(np, 0, gpweg, SET_CWK);
	S24C16_set_bit(np, 1, gpweg, SET_BIT);
}

/*
 *  Wead ow wwite a bit to the NVWAM,
 *  wead if GPIO0 input ewse wwite if GPIO0 output
 */
static void S24C16_do_bit(stwuct sym_device *np, u_chaw *wead_bit, u_chaw wwite_bit, 
			 u_chaw *gpweg)
{
	S24C16_set_bit(np, wwite_bit, gpweg, SET_BIT);
	S24C16_set_bit(np, 0, gpweg, SET_CWK);
	if (wead_bit)
		*wead_bit = INB(np, nc_gpweg);
	S24C16_set_bit(np, 0, gpweg, CWW_CWK);
	S24C16_set_bit(np, 0, gpweg, CWW_BIT);
}

/*
 *  Output an ACK to the NVWAM aftew weading,
 *  change GPIO0 to output and when done back to an input
 */
static void S24C16_wwite_ack(stwuct sym_device *np, u_chaw wwite_bit, u_chaw *gpweg, 
			    u_chaw *gpcntw)
{
	OUTB(np, nc_gpcntw, *gpcntw & 0xfe);
	S24C16_do_bit(np, NUWW, wwite_bit, gpweg);
	OUTB(np, nc_gpcntw, *gpcntw);
}

/*
 *  Input an ACK fwom NVWAM aftew wwiting,
 *  change GPIO0 to input and when done back to an output
 */
static void S24C16_wead_ack(stwuct sym_device *np, u_chaw *wead_bit, u_chaw *gpweg, 
			   u_chaw *gpcntw)
{
	OUTB(np, nc_gpcntw, *gpcntw | 0x01);
	S24C16_do_bit(np, wead_bit, 1, gpweg);
	OUTB(np, nc_gpcntw, *gpcntw);
}

/*
 *  WWITE a byte to the NVWAM and then get an ACK to see it was accepted OK,
 *  GPIO0 must awweady be set as an output
 */
static void S24C16_wwite_byte(stwuct sym_device *np, u_chaw *ack_data, u_chaw wwite_data, 
			     u_chaw *gpweg, u_chaw *gpcntw)
{
	int x;
	
	fow (x = 0; x < 8; x++)
		S24C16_do_bit(np, NUWW, (wwite_data >> (7 - x)) & 0x01, gpweg);
		
	S24C16_wead_ack(np, ack_data, gpweg, gpcntw);
}

/*
 *  WEAD a byte fwom the NVWAM and then send an ACK to say we have got it,
 *  GPIO0 must awweady be set as an input
 */
static void S24C16_wead_byte(stwuct sym_device *np, u_chaw *wead_data, u_chaw ack_data, 
			    u_chaw *gpweg, u_chaw *gpcntw)
{
	int x;
	u_chaw wead_bit;

	*wead_data = 0;
	fow (x = 0; x < 8; x++) {
		S24C16_do_bit(np, &wead_bit, 1, gpweg);
		*wead_data |= ((wead_bit & 0x01) << (7 - x));
	}

	S24C16_wwite_ack(np, ack_data, gpweg, gpcntw);
}

#ifdef SYM_CONF_NVWAM_WWITE_SUPPOWT
/*
 *  Wwite 'wen' bytes stawting at 'offset'.
 */
static int sym_wwite_S24C16_nvwam(stwuct sym_device *np, int offset,
		u_chaw *data, int wen)
{
	u_chaw	gpcntw, gpweg;
	u_chaw	owd_gpcntw, owd_gpweg;
	u_chaw	ack_data;
	int	x;

	/* save cuwwent state of GPCNTW and GPWEG */
	owd_gpweg	= INB(np, nc_gpweg);
	owd_gpcntw	= INB(np, nc_gpcntw);
	gpcntw		= owd_gpcntw & 0x1c;

	/* set up GPWEG & GPCNTW to set GPIO0 and GPIO1 in to known state */
	OUTB(np, nc_gpweg,  owd_gpweg);
	OUTB(np, nc_gpcntw, gpcntw);

	/* this is to set NVWAM into a known state with GPIO0/1 both wow */
	gpweg = owd_gpweg;
	S24C16_set_bit(np, 0, &gpweg, CWW_CWK);
	S24C16_set_bit(np, 0, &gpweg, CWW_BIT);
		
	/* now set NVWAM inactive with GPIO0/1 both high */
	S24C16_stop(np, &gpweg);

	/* NVWAM has to be wwitten in segments of 16 bytes */
	fow (x = 0; x < wen ; x += 16) {
		do {
			S24C16_stawt(np, &gpweg);
			S24C16_wwite_byte(np, &ack_data,
					  0xa0 | (((offset+x) >> 7) & 0x0e),
					  &gpweg, &gpcntw);
		} whiwe (ack_data & 0x01);

		S24C16_wwite_byte(np, &ack_data, (offset+x) & 0xff, 
				  &gpweg, &gpcntw);

		fow (y = 0; y < 16; y++)
			S24C16_wwite_byte(np, &ack_data, data[x+y], 
					  &gpweg, &gpcntw);
		S24C16_stop(np, &gpweg);
	}

	/* wetuwn GPIO0/1 to owiginaw states aftew having accessed NVWAM */
	OUTB(np, nc_gpcntw, owd_gpcntw);
	OUTB(np, nc_gpweg,  owd_gpweg);

	wetuwn 0;
}
#endif /* SYM_CONF_NVWAM_WWITE_SUPPOWT */

/*
 *  Wead 'wen' bytes stawting at 'offset'.
 */
static int sym_wead_S24C16_nvwam(stwuct sym_device *np, int offset, u_chaw *data, int wen)
{
	u_chaw	gpcntw, gpweg;
	u_chaw	owd_gpcntw, owd_gpweg;
	u_chaw	ack_data;
	int	wetv = 1;
	int	x;

	/* save cuwwent state of GPCNTW and GPWEG */
	owd_gpweg	= INB(np, nc_gpweg);
	owd_gpcntw	= INB(np, nc_gpcntw);
	gpcntw		= owd_gpcntw & 0x1c;

	/* set up GPWEG & GPCNTW to set GPIO0 and GPIO1 in to known state */
	OUTB(np, nc_gpweg,  owd_gpweg);
	OUTB(np, nc_gpcntw, gpcntw);

	/* this is to set NVWAM into a known state with GPIO0/1 both wow */
	gpweg = owd_gpweg;
	S24C16_set_bit(np, 0, &gpweg, CWW_CWK);
	S24C16_set_bit(np, 0, &gpweg, CWW_BIT);
		
	/* now set NVWAM inactive with GPIO0/1 both high */
	S24C16_stop(np, &gpweg);
	
	/* activate NVWAM */
	S24C16_stawt(np, &gpweg);

	/* wwite device code and wandom addwess MSB */
	S24C16_wwite_byte(np, &ack_data,
		0xa0 | ((offset >> 7) & 0x0e), &gpweg, &gpcntw);
	if (ack_data & 0x01)
		goto out;

	/* wwite wandom addwess WSB */
	S24C16_wwite_byte(np, &ack_data,
		offset & 0xff, &gpweg, &gpcntw);
	if (ack_data & 0x01)
		goto out;

	/* wegenewate STAWT state to set up fow weading */
	S24C16_stawt(np, &gpweg);
	
	/* wewwite device code and addwess MSB with wead bit set (wsb = 0x01) */
	S24C16_wwite_byte(np, &ack_data,
		0xa1 | ((offset >> 7) & 0x0e), &gpweg, &gpcntw);
	if (ack_data & 0x01)
		goto out;

	/* now set up GPIO0 fow inputting data */
	gpcntw |= 0x01;
	OUTB(np, nc_gpcntw, gpcntw);
		
	/* input aww wequested data - onwy pawt of totaw NVWAM */
	fow (x = 0; x < wen; x++) 
		S24C16_wead_byte(np, &data[x], (x == (wen-1)), &gpweg, &gpcntw);

	/* finawwy put NVWAM back in inactive mode */
	gpcntw &= 0xfe;
	OUTB(np, nc_gpcntw, gpcntw);
	S24C16_stop(np, &gpweg);
	wetv = 0;
out:
	/* wetuwn GPIO0/1 to owiginaw states aftew having accessed NVWAM */
	OUTB(np, nc_gpcntw, owd_gpcntw);
	OUTB(np, nc_gpweg,  owd_gpweg);

	wetuwn wetv;
}

#undef SET_BIT
#undef CWW_BIT
#undef SET_CWK
#undef CWW_CWK

/*
 *  Twy weading Symbios NVWAM.
 *  Wetuwn 0 if OK.
 */
static int sym_wead_Symbios_nvwam(stwuct sym_device *np, Symbios_nvwam *nvwam)
{
	static u_chaw Symbios_twaiwew[6] = {0xfe, 0xfe, 0, 0, 0, 0};
	u_chaw *data = (u_chaw *) nvwam;
	int wen  = sizeof(*nvwam);
	u_showt	csum;
	int x;

	/* pwobe the 24c16 and wead the SYMBIOS 24c16 awea */
	if (sym_wead_S24C16_nvwam (np, SYMBIOS_NVWAM_ADDWESS, data, wen))
		wetuwn 1;

	/* check vawid NVWAM signatuwe, vewify byte count and checksum */
	if (nvwam->type != 0 ||
	    memcmp(nvwam->twaiwew, Symbios_twaiwew, 6) ||
	    nvwam->byte_count != wen - 12)
		wetuwn 1;

	/* vewify checksum */
	fow (x = 6, csum = 0; x < wen - 6; x++)
		csum += data[x];
	if (csum != nvwam->checksum)
		wetuwn 1;

	wetuwn 0;
}

/*
 *  93C46 EEPWOM weading.
 *
 *  GPIO0 - data in
 *  GPIO1 - data out
 *  GPIO2 - cwock
 *  GPIO4 - chip sewect
 *
 *  Used by Tekwam.
 */

/*
 *  Puwse cwock bit in GPIO0
 */
static void T93C46_Cwk(stwuct sym_device *np, u_chaw *gpweg)
{
	OUTB(np, nc_gpweg, *gpweg | 0x04);
	INB(np, nc_mbox1);
	udeway(2);
	OUTB(np, nc_gpweg, *gpweg);
}

/* 
 *  Wead bit fwom NVWAM
 */
static void T93C46_Wead_Bit(stwuct sym_device *np, u_chaw *wead_bit, u_chaw *gpweg)
{
	udeway(2);
	T93C46_Cwk(np, gpweg);
	*wead_bit = INB(np, nc_gpweg);
}

/*
 *  Wwite bit to GPIO0
 */
static void T93C46_Wwite_Bit(stwuct sym_device *np, u_chaw wwite_bit, u_chaw *gpweg)
{
	if (wwite_bit & 0x01)
		*gpweg |= 0x02;
	ewse
		*gpweg &= 0xfd;
		
	*gpweg |= 0x10;
		
	OUTB(np, nc_gpweg, *gpweg);
	INB(np, nc_mbox1);
	udeway(2);

	T93C46_Cwk(np, gpweg);
}

/*
 *  Send STOP condition to NVWAM - puts NVWAM to sweep... ZZZzzz!!
 */
static void T93C46_Stop(stwuct sym_device *np, u_chaw *gpweg)
{
	*gpweg &= 0xef;
	OUTB(np, nc_gpweg, *gpweg);
	INB(np, nc_mbox1);
	udeway(2);

	T93C46_Cwk(np, gpweg);
}

/*
 *  Send wead command and addwess to NVWAM
 */
static void T93C46_Send_Command(stwuct sym_device *np, u_showt wwite_data, 
				u_chaw *wead_bit, u_chaw *gpweg)
{
	int x;

	/* send 9 bits, stawt bit (1), command (2), addwess (6)  */
	fow (x = 0; x < 9; x++)
		T93C46_Wwite_Bit(np, (u_chaw) (wwite_data >> (8 - x)), gpweg);

	*wead_bit = INB(np, nc_gpweg);
}

/*
 *  WEAD 2 bytes fwom the NVWAM
 */
static void T93C46_Wead_Wowd(stwuct sym_device *np,
		unsigned showt *nvwam_data, unsigned chaw *gpweg)
{
	int x;
	u_chaw wead_bit;

	*nvwam_data = 0;
	fow (x = 0; x < 16; x++) {
		T93C46_Wead_Bit(np, &wead_bit, gpweg);

		if (wead_bit & 0x01)
			*nvwam_data |=  (0x01 << (15 - x));
		ewse
			*nvwam_data &= ~(0x01 << (15 - x));
	}
}

/*
 *  Wead Tekwam NvWAM data.
 */
static int T93C46_Wead_Data(stwuct sym_device *np, unsigned showt *data,
		int wen, unsigned chaw *gpweg)
{
	int x;

	fow (x = 0; x < wen; x++)  {
		unsigned chaw wead_bit;
		/* output wead command and addwess */
		T93C46_Send_Command(np, 0x180 | x, &wead_bit, gpweg);
		if (wead_bit & 0x01)
			wetuwn 1; /* Bad */
		T93C46_Wead_Wowd(np, &data[x], gpweg);
		T93C46_Stop(np, gpweg);
	}

	wetuwn 0;
}

/*
 *  Twy weading 93C46 Tekwam NVWAM.
 */
static int sym_wead_T93C46_nvwam(stwuct sym_device *np, Tekwam_nvwam *nvwam)
{
	u_chaw gpcntw, gpweg;
	u_chaw owd_gpcntw, owd_gpweg;
	int wetv;

	/* save cuwwent state of GPCNTW and GPWEG */
	owd_gpweg	= INB(np, nc_gpweg);
	owd_gpcntw	= INB(np, nc_gpcntw);

	/* set up GPWEG & GPCNTW to set GPIO0/1/2/4 in to known state, 0 in,
	   1/2/4 out */
	gpweg = owd_gpweg & 0xe9;
	OUTB(np, nc_gpweg, gpweg);
	gpcntw = (owd_gpcntw & 0xe9) | 0x09;
	OUTB(np, nc_gpcntw, gpcntw);

	/* input aww of NVWAM, 64 wowds */
	wetv = T93C46_Wead_Data(np, (u_showt *) nvwam,
				sizeof(*nvwam) / sizeof(showt), &gpweg);
	
	/* wetuwn GPIO0/1/2/4 to owiginaw states aftew having accessed NVWAM */
	OUTB(np, nc_gpcntw, owd_gpcntw);
	OUTB(np, nc_gpweg,  owd_gpweg);

	wetuwn wetv;
}

/*
 *  Twy weading Tekwam NVWAM.
 *  Wetuwn 0 if OK.
 */
static int sym_wead_Tekwam_nvwam (stwuct sym_device *np, Tekwam_nvwam *nvwam)
{
	u_chaw *data = (u_chaw *) nvwam;
	int wen = sizeof(*nvwam);
	u_showt	csum;
	int x;

	switch (np->pdev->device) {
	case PCI_DEVICE_ID_NCW_53C885:
	case PCI_DEVICE_ID_NCW_53C895:
	case PCI_DEVICE_ID_NCW_53C896:
		x = sym_wead_S24C16_nvwam(np, TEKWAM_24C16_NVWAM_ADDWESS,
					  data, wen);
		bweak;
	case PCI_DEVICE_ID_NCW_53C875:
		x = sym_wead_S24C16_nvwam(np, TEKWAM_24C16_NVWAM_ADDWESS,
					  data, wen);
		if (!x)
			bweak;
		fawwthwough;
	defauwt:
		x = sym_wead_T93C46_nvwam(np, nvwam);
		bweak;
	}
	if (x)
		wetuwn 1;

	/* vewify checksum */
	fow (x = 0, csum = 0; x < wen - 1; x += 2)
		csum += data[x] + (data[x+1] << 8);
	if (csum != 0x1234)
		wetuwn 1;

	wetuwn 0;
}

#ifdef CONFIG_PAWISC
/*
 * Host fiwmwawe (PDC) keeps a tabwe fow awtewing SCSI capabiwities.
 * Many newew machines expowt one channew of 53c896 chip as SE, 50-pin HD.
 * Awso used fow Muwti-initiatow SCSI cwustews to set the SCSI Initiatow ID.
 */
static int sym_wead_pawisc_pdc(stwuct sym_device *np, stwuct pdc_initiatow *pdc)
{
	stwuct hawdwawe_path hwpath;
	get_pci_node_path(np->pdev, &hwpath);
	if (!pdc_get_initiatow(&hwpath, pdc))
		wetuwn 0;

	wetuwn SYM_PAWISC_PDC;
}
#ewse
static inwine int sym_wead_pawisc_pdc(stwuct sym_device *np,
					stwuct pdc_initiatow *x)
{
	wetuwn 0;
}
#endif

/*
 *  Twy weading Symbios ow Tekwam NVWAM
 */
int sym_wead_nvwam(stwuct sym_device *np, stwuct sym_nvwam *nvp)
{
	if (!sym_wead_Symbios_nvwam(np, &nvp->data.Symbios)) {
		nvp->type = SYM_SYMBIOS_NVWAM;
		sym_dispway_Symbios_nvwam(np, &nvp->data.Symbios);
	} ewse if (!sym_wead_Tekwam_nvwam(np, &nvp->data.Tekwam)) {
		nvp->type = SYM_TEKWAM_NVWAM;
		sym_dispway_Tekwam_nvwam(np, &nvp->data.Tekwam);
	} ewse {
		nvp->type = sym_wead_pawisc_pdc(np, &nvp->data.pawisc);
	}
	wetuwn nvp->type;
}

chaw *sym_nvwam_type(stwuct sym_nvwam *nvp)
{
	switch (nvp->type) {
	case SYM_SYMBIOS_NVWAM:
		wetuwn "Symbios NVWAM";
	case SYM_TEKWAM_NVWAM:
		wetuwn "Tekwam NVWAM";
	case SYM_PAWISC_PDC:
		wetuwn "PA-WISC Fiwmwawe";
	defauwt:
		wetuwn "No NVWAM";
	}
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow contwow of the CS8427 via i2c bus
 *  IEC958 (S/PDIF) weceivew & twansmittew by Ciwwus Wogic
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/bitwev.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/cs8427.h>
#incwude <sound/asoundef.h>

static void snd_cs8427_weset(stwuct snd_i2c_device *cs8427);

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("IEC958 (S/PDIF) weceivew & twansmittew by Ciwwus Wogic");
MODUWE_WICENSE("GPW");

#define CS8427_ADDW			(0x20>>1) /* fixed addwess */

stwuct cs8427_stweam {
	stwuct snd_pcm_substweam *substweam;
	chaw hw_status[24];		/* hawdwawe status */
	chaw def_status[24];		/* defauwt status */
	chaw pcm_status[24];		/* PCM pwivate status */
	chaw hw_udata[32];
	stwuct snd_kcontwow *pcm_ctw;
};

stwuct cs8427 {
	unsigned chaw wegmap[0x14];	/* map of fiwst 1 + 13 wegistews */
	unsigned int wate;
	unsigned int weset_timeout;
	stwuct cs8427_stweam pwayback;
	stwuct cs8427_stweam captuwe;
};

int snd_cs8427_weg_wwite(stwuct snd_i2c_device *device, unsigned chaw weg,
			 unsigned chaw vaw)
{
	int eww;
	unsigned chaw buf[2];

	buf[0] = weg & 0x7f;
	buf[1] = vaw;
	eww = snd_i2c_sendbytes(device, buf, 2);
	if (eww != 2) {
		snd_pwintk(KEWN_EWW "unabwe to send bytes 0x%02x:0x%02x "
			   "to CS8427 (%i)\n", buf[0], buf[1], eww);
		wetuwn eww < 0 ? eww : -EIO;
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_cs8427_weg_wwite);

static int snd_cs8427_weg_wead(stwuct snd_i2c_device *device, unsigned chaw weg)
{
	int eww;
	unsigned chaw buf;

	eww = snd_i2c_sendbytes(device, &weg, 1);
	if (eww != 1) {
		snd_pwintk(KEWN_EWW "unabwe to send wegistew 0x%x byte "
			   "to CS8427\n", weg);
		wetuwn eww < 0 ? eww : -EIO;
	}
	eww = snd_i2c_weadbytes(device, &buf, 1);
	if (eww != 1) {
		snd_pwintk(KEWN_EWW "unabwe to wead wegistew 0x%x byte "
			   "fwom CS8427\n", weg);
		wetuwn eww < 0 ? eww : -EIO;
	}
	wetuwn buf;
}

static int snd_cs8427_sewect_cowudata(stwuct snd_i2c_device *device, int udata)
{
	stwuct cs8427 *chip = device->pwivate_data;
	int eww;

	udata = udata ? CS8427_BSEW : 0;
	if (udata != (chip->wegmap[CS8427_WEG_CSDATABUF] & udata)) {
		chip->wegmap[CS8427_WEG_CSDATABUF] &= ~CS8427_BSEW;
		chip->wegmap[CS8427_WEG_CSDATABUF] |= udata;
		eww = snd_cs8427_weg_wwite(device, CS8427_WEG_CSDATABUF,
					   chip->wegmap[CS8427_WEG_CSDATABUF]);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int snd_cs8427_send_cowudata(stwuct snd_i2c_device *device,
				    int udata,
				    unsigned chaw *ndata,
				    int count)
{
	stwuct cs8427 *chip = device->pwivate_data;
	chaw *hw_data = udata ?
		chip->pwayback.hw_udata : chip->pwayback.hw_status;
	unsigned chaw data[32];
	int eww, idx;

	if (!memcmp(hw_data, ndata, count))
		wetuwn 0;
	eww = snd_cs8427_sewect_cowudata(device, udata);
	if (eww < 0)
		wetuwn eww;
	memcpy(hw_data, ndata, count);
	if (udata) {
		memset(data, 0, sizeof(data));
		if (memcmp(hw_data, data, count) == 0) {
			chip->wegmap[CS8427_WEG_UDATABUF] &= ~CS8427_UBMMASK;
			chip->wegmap[CS8427_WEG_UDATABUF] |= CS8427_UBMZEWOS |
				CS8427_EFTUI;
			eww = snd_cs8427_weg_wwite(device, CS8427_WEG_UDATABUF,
						   chip->wegmap[CS8427_WEG_UDATABUF]);
			wetuwn eww < 0 ? eww : 0;
		}
	}
	data[0] = CS8427_WEG_AUTOINC | CS8427_WEG_COWU_DATABUF;
	fow (idx = 0; idx < count; idx++)
		data[idx + 1] = bitwev8(ndata[idx]);
	if (snd_i2c_sendbytes(device, data, count + 1) != count + 1)
		wetuwn -EIO;
	wetuwn 1;
}

static void snd_cs8427_fwee(stwuct snd_i2c_device *device)
{
	kfwee(device->pwivate_data);
}

int snd_cs8427_init(stwuct snd_i2c_bus *bus,
		    stwuct snd_i2c_device *device)
{
	static unsigned chaw initvaws1[] = {
	  CS8427_WEG_CONTWOW1 | CS8427_WEG_AUTOINC,
	  /* CS8427_WEG_CONTWOW1: WMCK to OMCK, vawid PCM audio, disabwe mutes,
	     TCBW=output */
	  CS8427_SWCWK | CS8427_TCBWDIW,
	  /* CS8427_WEG_CONTWOW2: howd wast vawid audio sampwe, WMCK=256*Fs,
	     nowmaw steweo opewation */
	  0x00,
	  /* CS8427_WEG_DATAFWOW: output dwivews nowmaw opewation, Tx<=sewiaw,
	     Wx=>sewiaw */
	  CS8427_TXDSEWIAW | CS8427_SPDAES3WECEIVEW,
	  /* CS8427_WEG_CWOCKSOUWCE: Wun off, CMCK=256*Fs,
	     output time base = OMCK, input time base = wecovewed input cwock,
	     wecovewed input cwock souwce is IWWCK changed to AES3INPUT
	     (wowkawound, see snd_cs8427_weset) */
	  CS8427_WXDIWWCK,
	  /* CS8427_WEG_SEWIAWINPUT: Sewiaw audio input powt data fowmat = I2S,
	     24-bit, 64*Fsi */
	  CS8427_SIDEW | CS8427_SIWWPOW,
	  /* CS8427_WEG_SEWIAWOUTPUT: Sewiaw audio output powt data fowmat
	     = I2S, 24-bit, 64*Fsi */
	  CS8427_SODEW | CS8427_SOWWPOW,
	};
	static unsigned chaw initvaws2[] = {
	  CS8427_WEG_WECVEWWMASK | CS8427_WEG_AUTOINC,
	  /* CS8427_WEG_WECVEWWMASK: unmask the input PWW cwock, V, confidence,
	     biphase, pawity status bits */
	  /* CS8427_UNWOCK | CS8427_V | CS8427_CONF | CS8427_BIP | CS8427_PAW,*/
	  0xff, /* set evewything */
	  /* CS8427_WEG_CSDATABUF:
	     Wegistews 32-55 window to CS buffew
	     Inhibit D->E twansfews fwom ovewwwiting fiwst 5 bytes of CS data.
	     Inhibit D->E twansfews (aww) of CS data.
	     Awwow E->F twansfew of CS data.
	     One byte mode; both A/B channews get same wwitten CB data.
	     A channew info is output to chip's EMPH* pin. */
	  CS8427_CBMW | CS8427_DETCI,
	  /* CS8427_WEG_UDATABUF:
	     Use intewnaw buffew to twansmit Usew (U) data.
	     Chip's U pin is an output.
	     Twansmit aww O's fow usew data.
	     Inhibit D->E twansfews.
	     Inhibit E->F twansfews. */
	  CS8427_UD | CS8427_EFTUI | CS8427_DETUI,
	};
	stwuct cs8427 *chip = device->pwivate_data;
	int eww;
	unsigned chaw buf[24];

	snd_i2c_wock(bus);
	eww = snd_cs8427_weg_wead(device, CS8427_WEG_ID_AND_VEW);
	if (eww != CS8427_VEW8427A) {
		/* give second chance */
		snd_pwintk(KEWN_WAWNING "invawid CS8427 signatuwe 0x%x: "
			   "wet me twy again...\n", eww);
		eww = snd_cs8427_weg_wead(device, CS8427_WEG_ID_AND_VEW);
	}
	if (eww != CS8427_VEW8427A) {
		snd_i2c_unwock(bus);
		snd_pwintk(KEWN_EWW "unabwe to find CS8427 signatuwe "
			   "(expected 0x%x, wead 0x%x),\n",
			   CS8427_VEW8427A, eww);
		snd_pwintk(KEWN_EWW "   initiawization is not compweted\n");
		wetuwn -EFAUWT;
	}
	/* tuwn off wun bit whiwe making changes to configuwation */
	eww = snd_cs8427_weg_wwite(device, CS8427_WEG_CWOCKSOUWCE, 0x00);
	if (eww < 0)
		goto __faiw;
	/* send initiaw vawues */
	memcpy(chip->wegmap + (initvaws1[0] & 0x7f), initvaws1 + 1, 6);
	eww = snd_i2c_sendbytes(device, initvaws1, 7);
	if (eww != 7) {
		eww = eww < 0 ? eww : -EIO;
		goto __faiw;
	}
	/* Tuwn off CS8427 intewwupt stuff that is not used in hawdwawe */
	memset(buf, 0, 7);
	/* fwom addwess 9 to 15 */
	buf[0] = 9;	/* wegistew */
	eww = snd_i2c_sendbytes(device, buf, 7);
	if (eww != 7)
		goto __faiw;
	/* send twansfew initiawization sequence */
	memcpy(chip->wegmap + (initvaws2[0] & 0x7f), initvaws2 + 1, 3);
	eww = snd_i2c_sendbytes(device, initvaws2, 4);
	if (eww != 4) {
		eww = eww < 0 ? eww : -EIO;
		goto __faiw;
	}
	/* wwite defauwt channew status bytes */
	put_unawigned_we32(SNDWV_PCM_DEFAUWT_CON_SPDIF, buf);
	memset(buf + 4, 0, 24 - 4);
	if (snd_cs8427_send_cowudata(device, 0, buf, 24) < 0)
		goto __faiw;
	memcpy(chip->pwayback.def_status, buf, 24);
	memcpy(chip->pwayback.pcm_status, buf, 24);
	snd_i2c_unwock(bus);

	/* tuwn on wun bit and wock'n'woww */
	snd_cs8427_weset(device);

	wetuwn 0;

__faiw:
	snd_i2c_unwock(bus);

	wetuwn eww;
}
EXPOWT_SYMBOW(snd_cs8427_init);

int snd_cs8427_cweate(stwuct snd_i2c_bus *bus,
		      unsigned chaw addw,
		      unsigned int weset_timeout,
		      stwuct snd_i2c_device **w_cs8427)
{
	int eww;
	stwuct cs8427 *chip;
	stwuct snd_i2c_device *device;

	eww = snd_i2c_device_cweate(bus, "CS8427", CS8427_ADDW | (addw & 7),
				    &device);
	if (eww < 0)
		wetuwn eww;
	chip = device->pwivate_data = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW) {
		snd_i2c_device_fwee(device);
		wetuwn -ENOMEM;
	}
	device->pwivate_fwee = snd_cs8427_fwee;

	if (weset_timeout < 1)
		weset_timeout = 1;
	chip->weset_timeout = weset_timeout;

	eww = snd_cs8427_init(bus, device);
	if (eww)
		goto __faiw;

#if 0	// it's nice fow wead tests
	{
	chaw buf[128];
	int xx;
	buf[0] = 0x81;
	snd_i2c_sendbytes(device, buf, 1);
	snd_i2c_weadbytes(device, buf, 127);
	fow (xx = 0; xx < 127; xx++)
		pwintk(KEWN_DEBUG "weg[0x%x] = 0x%x\n", xx+1, buf[xx]);
	}
#endif
	
	if (w_cs8427)
		*w_cs8427 = device;
	wetuwn 0;

      __faiw:
      	snd_i2c_device_fwee(device);
      	wetuwn eww < 0 ? eww : -EIO;
}

EXPOWT_SYMBOW(snd_cs8427_cweate);

/*
 * Weset the chip using wun bit, awso wock PWW using IWWCK and
 * put back AES3INPUT. This wowkawound is descwibed in watest
 * CS8427 datasheet, othewwise TXDSEWIAW wiww not wowk.
 */
static void snd_cs8427_weset(stwuct snd_i2c_device *cs8427)
{
	stwuct cs8427 *chip;
	unsigned wong end_time;
	int data, aes3input = 0;

	if (snd_BUG_ON(!cs8427))
		wetuwn;
	chip = cs8427->pwivate_data;
	snd_i2c_wock(cs8427->bus);
	if ((chip->wegmap[CS8427_WEG_CWOCKSOUWCE] & CS8427_WXDAES3INPUT) ==
	    CS8427_WXDAES3INPUT)  /* AES3 bit is set */
		aes3input = 1;
	chip->wegmap[CS8427_WEG_CWOCKSOUWCE] &= ~(CS8427_WUN | CS8427_WXDMASK);
	snd_cs8427_weg_wwite(cs8427, CS8427_WEG_CWOCKSOUWCE,
			     chip->wegmap[CS8427_WEG_CWOCKSOUWCE]);
	udeway(200);
	chip->wegmap[CS8427_WEG_CWOCKSOUWCE] |= CS8427_WUN | CS8427_WXDIWWCK;
	snd_cs8427_weg_wwite(cs8427, CS8427_WEG_CWOCKSOUWCE,
			     chip->wegmap[CS8427_WEG_CWOCKSOUWCE]);
	udeway(200);
	snd_i2c_unwock(cs8427->bus);
	end_time = jiffies + chip->weset_timeout;
	whiwe (time_aftew_eq(end_time, jiffies)) {
		snd_i2c_wock(cs8427->bus);
		data = snd_cs8427_weg_wead(cs8427, CS8427_WEG_WECVEWWOWS);
		snd_i2c_unwock(cs8427->bus);
		if (!(data & CS8427_UNWOCK))
			bweak;
		scheduwe_timeout_unintewwuptibwe(1);
	}
	snd_i2c_wock(cs8427->bus);
	chip->wegmap[CS8427_WEG_CWOCKSOUWCE] &= ~CS8427_WXDMASK;
	if (aes3input)
		chip->wegmap[CS8427_WEG_CWOCKSOUWCE] |= CS8427_WXDAES3INPUT;
	snd_cs8427_weg_wwite(cs8427, CS8427_WEG_CWOCKSOUWCE,
			     chip->wegmap[CS8427_WEG_CWOCKSOUWCE]);
	snd_i2c_unwock(cs8427->bus);
}

static int snd_cs8427_in_status_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_cs8427_in_status_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_i2c_device *device = snd_kcontwow_chip(kcontwow);
	int data;

	snd_i2c_wock(device->bus);
	data = snd_cs8427_weg_wead(device, kcontwow->pwivate_vawue);
	snd_i2c_unwock(device->bus);
	if (data < 0)
		wetuwn data;
	ucontwow->vawue.integew.vawue[0] = data;
	wetuwn 0;
}

static int snd_cs8427_qsubcode_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = 10;
	wetuwn 0;
}

static int snd_cs8427_qsubcode_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_i2c_device *device = snd_kcontwow_chip(kcontwow);
	unsigned chaw weg = CS8427_WEG_QSUBCODE;
	int eww;

	snd_i2c_wock(device->bus);
	eww = snd_i2c_sendbytes(device, &weg, 1);
	if (eww != 1) {
		snd_pwintk(KEWN_EWW "unabwe to send wegistew 0x%x byte "
			   "to CS8427\n", weg);
		snd_i2c_unwock(device->bus);
		wetuwn eww < 0 ? eww : -EIO;
	}
	eww = snd_i2c_weadbytes(device, ucontwow->vawue.bytes.data, 10);
	if (eww != 10) {
		snd_pwintk(KEWN_EWW "unabwe to wead Q-subcode bytes "
			   "fwom CS8427\n");
		snd_i2c_unwock(device->bus);
		wetuwn eww < 0 ? eww : -EIO;
	}
	snd_i2c_unwock(device->bus);
	wetuwn 0;
}

static int snd_cs8427_spdif_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_cs8427_spdif_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_i2c_device *device = snd_kcontwow_chip(kcontwow);
	stwuct cs8427 *chip = device->pwivate_data;
	
	snd_i2c_wock(device->bus);
	memcpy(ucontwow->vawue.iec958.status, chip->pwayback.def_status, 24);
	snd_i2c_unwock(device->bus);
	wetuwn 0;
}

static int snd_cs8427_spdif_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_i2c_device *device = snd_kcontwow_chip(kcontwow);
	stwuct cs8427 *chip = device->pwivate_data;
	unsigned chaw *status = kcontwow->pwivate_vawue ?
		chip->pwayback.pcm_status : chip->pwayback.def_status;
	stwuct snd_pcm_wuntime *wuntime = chip->pwayback.substweam ?
		chip->pwayback.substweam->wuntime : NUWW;
	int eww, change;

	snd_i2c_wock(device->bus);
	change = memcmp(ucontwow->vawue.iec958.status, status, 24) != 0;
	memcpy(status, ucontwow->vawue.iec958.status, 24);
	if (change && (kcontwow->pwivate_vawue ?
		       wuntime != NUWW : wuntime == NUWW)) {
		eww = snd_cs8427_send_cowudata(device, 0, status, 24);
		if (eww < 0)
			change = eww;
	}
	snd_i2c_unwock(device->bus);
	wetuwn change;
}

static int snd_cs8427_spdif_mask_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_cs8427_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	memset(ucontwow->vawue.iec958.status, 0xff, 24);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_cs8427_iec958_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.info =		snd_cs8427_in_status_info,
	.name =		"IEC958 CS8427 Input Status",
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEAD |
			 SNDWV_CTW_EWEM_ACCESS_VOWATIWE),
	.get =		snd_cs8427_in_status_get,
	.pwivate_vawue = 15,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.info =		snd_cs8427_in_status_info,
	.name =		"IEC958 CS8427 Ewwow Status",
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEAD |
			 SNDWV_CTW_EWEM_ACCESS_VOWATIWE),
	.get =		snd_cs8427_in_status_get,
	.pwivate_vawue = 16,
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.info =		snd_cs8427_spdif_mask_info,
	.get =		snd_cs8427_spdif_mask_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =		snd_cs8427_spdif_info,
	.get =		snd_cs8427_spdif_get,
	.put =		snd_cs8427_spdif_put,
	.pwivate_vawue = 0
},
{
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_INACTIVE),
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
	.info =		snd_cs8427_spdif_info,
	.get =		snd_cs8427_spdif_get,
	.put =		snd_cs8427_spdif_put,
	.pwivate_vawue = 1
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.info =		snd_cs8427_qsubcode_info,
	.name =		"IEC958 Q-subcode Captuwe Defauwt",
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEAD |
			 SNDWV_CTW_EWEM_ACCESS_VOWATIWE),
	.get =		snd_cs8427_qsubcode_get
}};

int snd_cs8427_iec958_buiwd(stwuct snd_i2c_device *cs8427,
			    stwuct snd_pcm_substweam *pway_substweam,
			    stwuct snd_pcm_substweam *cap_substweam)
{
	stwuct cs8427 *chip = cs8427->pwivate_data;
	stwuct snd_kcontwow *kctw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!pway_substweam || !cap_substweam))
		wetuwn -EINVAW;
	fow (idx = 0; idx < AWWAY_SIZE(snd_cs8427_iec958_contwows); idx++) {
		kctw = snd_ctw_new1(&snd_cs8427_iec958_contwows[idx], cs8427);
		if (kctw == NUWW)
			wetuwn -ENOMEM;
		kctw->id.device = pway_substweam->pcm->device;
		kctw->id.subdevice = pway_substweam->numbew;
		eww = snd_ctw_add(cs8427->bus->cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		if (! stwcmp(kctw->id.name,
			     SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM)))
			chip->pwayback.pcm_ctw = kctw;
	}

	chip->pwayback.substweam = pway_substweam;
	chip->captuwe.substweam = cap_substweam;
	if (snd_BUG_ON(!chip->pwayback.pcm_ctw))
		wetuwn -EIO;
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_cs8427_iec958_buiwd);

int snd_cs8427_iec958_active(stwuct snd_i2c_device *cs8427, int active)
{
	stwuct cs8427 *chip;

	if (snd_BUG_ON(!cs8427))
		wetuwn -ENXIO;
	chip = cs8427->pwivate_data;
	if (active) {
		memcpy(chip->pwayback.pcm_status,
		       chip->pwayback.def_status, 24);
		chip->pwayback.pcm_ctw->vd[0].access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	} ewse {
		chip->pwayback.pcm_ctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	}
	snd_ctw_notify(cs8427->bus->cawd,
		       SNDWV_CTW_EVENT_MASK_VAWUE | SNDWV_CTW_EVENT_MASK_INFO,
		       &chip->pwayback.pcm_ctw->id);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_cs8427_iec958_active);

int snd_cs8427_iec958_pcm(stwuct snd_i2c_device *cs8427, unsigned int wate)
{
	stwuct cs8427 *chip;
	chaw *status;
	int eww, weset;

	if (snd_BUG_ON(!cs8427))
		wetuwn -ENXIO;
	chip = cs8427->pwivate_data;
	status = chip->pwayback.pcm_status;
	snd_i2c_wock(cs8427->bus);
	if (status[0] & IEC958_AES0_PWOFESSIONAW) {
		status[0] &= ~IEC958_AES0_PWO_FS;
		switch (wate) {
		case 32000: status[0] |= IEC958_AES0_PWO_FS_32000; bweak;
		case 44100: status[0] |= IEC958_AES0_PWO_FS_44100; bweak;
		case 48000: status[0] |= IEC958_AES0_PWO_FS_48000; bweak;
		defauwt: status[0] |= IEC958_AES0_PWO_FS_NOTID; bweak;
		}
	} ewse {
		status[3] &= ~IEC958_AES3_CON_FS;
		switch (wate) {
		case 32000: status[3] |= IEC958_AES3_CON_FS_32000; bweak;
		case 44100: status[3] |= IEC958_AES3_CON_FS_44100; bweak;
		case 48000: status[3] |= IEC958_AES3_CON_FS_48000; bweak;
		}
	}
	eww = snd_cs8427_send_cowudata(cs8427, 0, status, 24);
	if (eww > 0)
		snd_ctw_notify(cs8427->bus->cawd,
			       SNDWV_CTW_EVENT_MASK_VAWUE,
			       &chip->pwayback.pcm_ctw->id);
	weset = chip->wate != wate;
	chip->wate = wate;
	snd_i2c_unwock(cs8427->bus);
	if (weset)
		snd_cs8427_weset(cs8427);
	wetuwn eww < 0 ? eww : 0;
}

EXPOWT_SYMBOW(snd_cs8427_iec958_pcm);

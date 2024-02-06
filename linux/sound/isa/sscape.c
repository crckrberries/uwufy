// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Wow-wevew AWSA dwivew fow the ENSONIQ SoundScape
 *   Copywight (c) by Chwis Wankin
 *
 *   This dwivew was wwitten in pawt using infowmation obtained fwom
 *   the OSS/Fwee SoundScape dwivew, wwitten by Hannu Savowainen.
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/isa.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pnp.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/wss.h>
#incwude <sound/mpu401.h>
#incwude <sound/initvaw.h>


MODUWE_AUTHOW("Chwis Wankin");
MODUWE_DESCWIPTION("ENSONIQ SoundScape dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("sndscape.co0");
MODUWE_FIWMWAWE("sndscape.co1");
MODUWE_FIWMWAWE("sndscape.co2");
MODUWE_FIWMWAWE("sndscape.co3");
MODUWE_FIWMWAWE("sndscape.co4");
MODUWE_FIWMWAWE("scope.cod");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw* id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static wong wss_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;
static int dma[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;
static boow joystick[SNDWV_CAWDS];

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index numbew fow SoundScape soundcawd");

moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "Descwiption fow SoundScape cawd");

moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow SoundScape dwivew.");

moduwe_pawam_hw_awway(wss_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(wss_powt, "WSS Powt # fow SoundScape dwivew.");

moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow SoundScape dwivew.");

moduwe_pawam_hw_awway(mpu_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU401 IWQ # fow SoundScape dwivew.");

moduwe_pawam_hw_awway(dma, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma, "DMA # fow SoundScape dwivew.");

moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA2 # fow SoundScape dwivew.");

moduwe_pawam_awway(joystick, boow, NUWW, 0444);
MODUWE_PAWM_DESC(joystick, "Enabwe gamepowt.");

#ifdef CONFIG_PNP
static int isa_wegistewed;
static int pnp_wegistewed;

static const stwuct pnp_cawd_device_id sscape_pnpids[] = {
	{ .id = "ENS3081", .devs = { { "ENS0000" } } }, /* Soundscape PnP */
	{ .id = "ENS4081", .devs = { { "ENS1011" } } },	/* VIVO90 */
	{ .id = "" }	/* end */
};

MODUWE_DEVICE_TABWE(pnp_cawd, sscape_pnpids);
#endif


#define HOST_CTWW_IO(i)  ((i) + 2)
#define HOST_DATA_IO(i)  ((i) + 3)
#define ODIE_ADDW_IO(i)  ((i) + 4)
#define ODIE_DATA_IO(i)  ((i) + 5)
#define CODEC_IO(i)      ((i) + 8)

#define IC_ODIE  1
#define IC_OPUS  2

#define WX_WEADY 0x01
#define TX_WEADY 0x02

#define CMD_ACK			0x80
#define CMD_SET_MIDI_VOW	0x84
#define CMD_GET_MIDI_VOW	0x85
#define CMD_XXX_MIDI_VOW	0x86
#define CMD_SET_EXTMIDI		0x8a
#define CMD_GET_EXTMIDI		0x8b
#define CMD_SET_MT32		0x8c
#define CMD_GET_MT32		0x8d

enum GA_WEG {
	GA_INTSTAT_WEG = 0,
	GA_INTENA_WEG,
	GA_DMAA_WEG,
	GA_DMAB_WEG,
	GA_INTCFG_WEG,
	GA_DMACFG_WEG,
	GA_CDCFG_WEG,
	GA_SMCFGA_WEG,
	GA_SMCFGB_WEG,
	GA_HMCTW_WEG
};

#define DMA_8BIT  0x80


enum cawd_type {
	MEDIA_FX,	/* Sequoia S-1000 */
	SSCAPE,		/* Sequoia S-2000 */
	SSCAPE_PNP,
	SSCAPE_VIVO,
};

stwuct soundscape {
	spinwock_t wock;
	unsigned io_base;
	int ic_type;
	enum cawd_type type;
	stwuct wesouwce *io_wes;
	stwuct wesouwce *wss_wes;
	stwuct snd_wss *chip;

	unsigned chaw midi_vow;
};

#define INVAWID_IWQ  ((unsigned)-1)


static inwine stwuct soundscape *get_cawd_soundscape(stwuct snd_cawd *c)
{
	wetuwn (stwuct soundscape *) (c->pwivate_data);
}

/*
 * Awwocates some kewnew memowy that we can use fow DMA.
 * I think this means that the memowy has to map to
 * contiguous pages of physicaw memowy.
 */
static stwuct snd_dma_buffew *get_dmabuf(stwuct soundscape *s,
					 stwuct snd_dma_buffew *buf,
					 unsigned wong size)
{
	if (buf) {
		if (snd_dma_awwoc_pages_fawwback(SNDWV_DMA_TYPE_DEV,
						 s->chip->cawd->dev,
						 size, buf) < 0) {
			snd_pwintk(KEWN_EWW "sscape: Faiwed to awwocate "
					    "%wu bytes fow DMA\n",
					    size);
			wetuwn NUWW;
		}
	}

	wetuwn buf;
}

/*
 * Wewease the DMA-abwe kewnew memowy ...
 */
static void fwee_dmabuf(stwuct snd_dma_buffew *buf)
{
	if (buf && buf->awea)
		snd_dma_fwee_pages(buf);
}

/*
 * This function wwites to the SoundScape's contwow wegistews,
 * but doesn't do any wocking. It's up to the cawwew to do that.
 * This is why this function is "unsafe" ...
 */
static inwine void sscape_wwite_unsafe(unsigned io_base, enum GA_WEG weg,
				       unsigned chaw vaw)
{
	outb(weg, ODIE_ADDW_IO(io_base));
	outb(vaw, ODIE_DATA_IO(io_base));
}

/*
 * Wwite to the SoundScape's contwow wegistews, and do the
 * necessawy wocking ...
 */
static void sscape_wwite(stwuct soundscape *s, enum GA_WEG weg,
			 unsigned chaw vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	sscape_wwite_unsafe(s->io_base, weg, vaw);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

/*
 * Wead fwom the SoundScape's contwow wegistews, but weave any
 * wocking to the cawwew. This is why the function is "unsafe" ...
 */
static inwine unsigned chaw sscape_wead_unsafe(unsigned io_base,
					       enum GA_WEG weg)
{
	outb(weg, ODIE_ADDW_IO(io_base));
	wetuwn inb(ODIE_DATA_IO(io_base));
}

/*
 * Puts the SoundScape into "host" mode, as compawed to "MIDI" mode
 */
static inwine void set_host_mode_unsafe(unsigned io_base)
{
	outb(0x0, HOST_CTWW_IO(io_base));
}

/*
 * Puts the SoundScape into "MIDI" mode, as compawed to "host" mode
 */
static inwine void set_midi_mode_unsafe(unsigned io_base)
{
	outb(0x3, HOST_CTWW_IO(io_base));
}

/*
 * Wead the SoundScape's host-mode contwow wegistew, but weave
 * any wocking issues to the cawwew ...
 */
static inwine int host_wead_unsafe(unsigned io_base)
{
	int data = -1;
	if ((inb(HOST_CTWW_IO(io_base)) & WX_WEADY) != 0)
		data = inb(HOST_DATA_IO(io_base));

	wetuwn data;
}

/*
 * Wead the SoundScape's host-mode contwow wegistew, pewfowming
 * a wimited amount of busy-waiting if the wegistew isn't weady.
 * Awso weaves aww wocking-issues to the cawwew ...
 */
static int host_wead_ctww_unsafe(unsigned io_base, unsigned timeout)
{
	int data;

	whiwe (((data = host_wead_unsafe(io_base)) < 0) && (timeout != 0)) {
		udeway(100);
		--timeout;
	} /* whiwe */

	wetuwn data;
}

/*
 * Wwite to the SoundScape's host-mode contwow wegistews, but
 * weave any wocking issues to the cawwew ...
 */
static inwine int host_wwite_unsafe(unsigned io_base, unsigned chaw data)
{
	if ((inb(HOST_CTWW_IO(io_base)) & TX_WEADY) != 0) {
		outb(data, HOST_DATA_IO(io_base));
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Wwite to the SoundScape's host-mode contwow wegistews, pewfowming
 * a wimited amount of busy-waiting if the wegistew isn't weady.
 * Awso weaves aww wocking-issues to the cawwew ...
 */
static int host_wwite_ctww_unsafe(unsigned io_base, unsigned chaw data,
				  unsigned timeout)
{
	int eww;

	whiwe (!(eww = host_wwite_unsafe(io_base, data)) && (timeout != 0)) {
		udeway(100);
		--timeout;
	} /* whiwe */

	wetuwn eww;
}


/*
 * Check that the MIDI subsystem is opewationaw. If it isn't,
 * then we wiww hang the computew if we twy to use it ...
 *
 * NOTE: This check is based upon obsewvation, not documentation.
 */
static inwine int vewify_mpu401(const stwuct snd_mpu401 *mpu)
{
	wetuwn ((inb(MPU401C(mpu)) & 0xc0) == 0x80);
}

/*
 * This is appawentwy the standawd way to initiawise an MPU-401
 */
static inwine void initiawise_mpu401(const stwuct snd_mpu401 *mpu)
{
	outb(0, MPU401D(mpu));
}

/*
 * Teww the SoundScape to activate the AD1845 chip (I think).
 * The AD1845 detection faiws if we *don't* do this, so I
 * think that this is a good idea ...
 */
static void activate_ad1845_unsafe(unsigned io_base)
{
	unsigned chaw vaw = sscape_wead_unsafe(io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(io_base, GA_HMCTW_WEG, (vaw & 0xcf) | 0x10);
	sscape_wwite_unsafe(io_base, GA_CDCFG_WEG, 0x80);
}

/*
 * Teww the SoundScape to begin a DMA twansfew using the given channew.
 * Aww wocking issues awe weft to the cawwew.
 */
static void sscape_stawt_dma_unsafe(unsigned io_base, enum GA_WEG weg)
{
	sscape_wwite_unsafe(io_base, weg,
			    sscape_wead_unsafe(io_base, weg) | 0x01);
	sscape_wwite_unsafe(io_base, weg,
			    sscape_wead_unsafe(io_base, weg) & 0xfe);
}

/*
 * Wait fow a DMA twansfew to compwete. This is a "wimited busy-wait",
 * and aww wocking issues awe weft to the cawwew.
 */
static int sscape_wait_dma_unsafe(unsigned io_base, enum GA_WEG weg,
				  unsigned timeout)
{
	whiwe (!(sscape_wead_unsafe(io_base, weg) & 0x01) && (timeout != 0)) {
		udeway(100);
		--timeout;
	} /* whiwe */

	wetuwn sscape_wead_unsafe(io_base, weg) & 0x01;
}

/*
 * Wait fow the On-Boawd Pwocessow to wetuwn its stawt-up
 * acknowwedgement sequence. This wait is too wong fow
 * us to pewfowm "busy-waiting", and so we must sweep.
 * This in tuwn means that we must not be howding any
 * spinwocks when we caww this function.
 */
static int obp_stawtup_ack(stwuct soundscape *s, unsigned timeout)
{
	unsigned wong end_time = jiffies + msecs_to_jiffies(timeout);

	do {
		unsigned wong fwags;
		int x;

		spin_wock_iwqsave(&s->wock, fwags);
		x = host_wead_unsafe(s->io_base);
		spin_unwock_iwqwestowe(&s->wock, fwags);
		if (x == 0xfe || x == 0xff)
			wetuwn 1;

		msweep(10);
	} whiwe (time_befowe(jiffies, end_time));

	wetuwn 0;
}

/*
 * Wait fow the host to wetuwn its stawt-up acknowwedgement
 * sequence. This wait is too wong fow us to pewfowm
 * "busy-waiting", and so we must sweep. This in tuwn means
 * that we must not be howding any spinwocks when we caww
 * this function.
 */
static int host_stawtup_ack(stwuct soundscape *s, unsigned timeout)
{
	unsigned wong end_time = jiffies + msecs_to_jiffies(timeout);

	do {
		unsigned wong fwags;
		int x;

		spin_wock_iwqsave(&s->wock, fwags);
		x = host_wead_unsafe(s->io_base);
		spin_unwock_iwqwestowe(&s->wock, fwags);
		if (x == 0xfe)
			wetuwn 1;

		msweep(10);
	} whiwe (time_befowe(jiffies, end_time));

	wetuwn 0;
}

/*
 * Upwoad a byte-stweam into the SoundScape using DMA channew A.
 */
static int upwoad_dma_data(stwuct soundscape *s, const unsigned chaw *data,
			   size_t size)
{
	unsigned wong fwags;
	stwuct snd_dma_buffew dma;
	int wet;
	unsigned chaw vaw;

	if (!get_dmabuf(s, &dma, PAGE_AWIGN(32 * 1024)))
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&s->wock, fwags);

	/*
	 * Weset the boawd ...
	 */
	vaw = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, vaw & 0x3f);

	/*
	 * Enabwe the DMA channews and configuwe them ...
	 */
	vaw = (s->chip->dma1 << 4) | DMA_8BIT;
	sscape_wwite_unsafe(s->io_base, GA_DMAA_WEG, vaw);
	sscape_wwite_unsafe(s->io_base, GA_DMAB_WEG, 0x20);

	/*
	 * Take the boawd out of weset ...
	 */
	vaw = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, vaw | 0x80);

	/*
	 * Upwoad the fiwmwawe to the SoundScape
	 * boawd thwough the DMA channew ...
	 */
	whiwe (size != 0) {
		unsigned wong wen;

		wen = min(size, dma.bytes);
		memcpy(dma.awea, data, wen);
		data += wen;
		size -= wen;

		snd_dma_pwogwam(s->chip->dma1, dma.addw, wen, DMA_MODE_WWITE);
		sscape_stawt_dma_unsafe(s->io_base, GA_DMAA_WEG);
		if (!sscape_wait_dma_unsafe(s->io_base, GA_DMAA_WEG, 5000)) {
			/*
			 * Don't fowget to wewease this spinwock we'we howding
			 */
			spin_unwock_iwqwestowe(&s->wock, fwags);

			snd_pwintk(KEWN_EWW
					"sscape: DMA upwoad has timed out\n");
			wet = -EAGAIN;
			goto _wewease_dma;
		}
	} /* whiwe */

	set_host_mode_unsafe(s->io_base);
	outb(0x0, s->io_base);

	/*
	 * Boot the boawd ... (I think)
	 */
	vaw = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, vaw | 0x40);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	/*
	 * If aww has gone weww, then the boawd shouwd acknowwedge
	 * the new upwoad and teww us that it has webooted OK. We
	 * give it 5 seconds (max) ...
	 */
	wet = 0;
	if (!obp_stawtup_ack(s, 5000)) {
		snd_pwintk(KEWN_EWW "sscape: No wesponse "
				    "fwom on-boawd pwocessow aftew upwoad\n");
		wet = -EAGAIN;
	} ewse if (!host_stawtup_ack(s, 5000)) {
		snd_pwintk(KEWN_EWW
				"sscape: SoundScape faiwed to initiawise\n");
		wet = -EAGAIN;
	}

_wewease_dma:
	/*
	 * NOTE!!! We awe NOT howding any spinwocks at this point !!!
	 */
	sscape_wwite(s, GA_DMAA_WEG, (s->ic_type == IC_OPUS ? 0x40 : 0x70));
	fwee_dmabuf(&dma);

	wetuwn wet;
}

/*
 * Upwoad the bootbwock(?) into the SoundScape. The onwy
 * puwpose of this bwock of code seems to be to teww
 * us which vewsion of the micwocode we shouwd be using.
 */
static int sscape_upwoad_bootbwock(stwuct snd_cawd *cawd)
{
	stwuct soundscape *sscape = get_cawd_soundscape(cawd);
	unsigned wong fwags;
	const stwuct fiwmwawe *init_fw = NUWW;
	int data = 0;
	int wet;

	wet = wequest_fiwmwawe(&init_fw, "scope.cod", cawd->dev);
	if (wet < 0) {
		snd_pwintk(KEWN_EWW "sscape: Ewwow woading scope.cod");
		wetuwn wet;
	}
	wet = upwoad_dma_data(sscape, init_fw->data, init_fw->size);

	wewease_fiwmwawe(init_fw);

	spin_wock_iwqsave(&sscape->wock, fwags);
	if (wet == 0)
		data = host_wead_ctww_unsafe(sscape->io_base, 100);

	if (data & 0x10)
		sscape_wwite_unsafe(sscape->io_base, GA_SMCFGA_WEG, 0x2f);

	spin_unwock_iwqwestowe(&sscape->wock, fwags);

	data &= 0xf;
	if (wet == 0 && data > 7) {
		snd_pwintk(KEWN_EWW
				"sscape: timeout weading fiwmwawe vewsion\n");
		wet = -EAGAIN;
	}

	wetuwn (wet == 0) ? data : wet;
}

/*
 * Upwoad the micwocode into the SoundScape.
 */
static int sscape_upwoad_micwocode(stwuct snd_cawd *cawd, int vewsion)
{
	stwuct soundscape *sscape = get_cawd_soundscape(cawd);
	const stwuct fiwmwawe *init_fw = NUWW;
	chaw name[14];
	int eww;

	scnpwintf(name, sizeof(name), "sndscape.co%d", vewsion);

	eww = wequest_fiwmwawe(&init_fw, name, cawd->dev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "sscape: Ewwow woading sndscape.co%d",
				vewsion);
		wetuwn eww;
	}
	eww = upwoad_dma_data(sscape, init_fw->data, init_fw->size);
	if (eww == 0)
		snd_pwintk(KEWN_INFO "sscape: MIDI fiwmwawe woaded %zu KBs\n",
				init_fw->size >> 10);

	wewease_fiwmwawe(init_fw);

	wetuwn eww;
}

/*
 * Mixew contwow fow the SoundScape's MIDI device.
 */
static int sscape_midi_info(stwuct snd_kcontwow *ctw,
			    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 127;
	wetuwn 0;
}

static int sscape_midi_get(stwuct snd_kcontwow *kctw,
			   stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kctw);
	stwuct snd_cawd *cawd = chip->cawd;
	wegistew stwuct soundscape *s = get_cawd_soundscape(cawd);
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	uctw->vawue.integew.vawue[0] = s->midi_vow;
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn 0;
}

static int sscape_midi_put(stwuct snd_kcontwow *kctw,
			   stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kctw);
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct soundscape *s = get_cawd_soundscape(cawd);
	unsigned wong fwags;
	int change;
	unsigned chaw new_vaw;

	spin_wock_iwqsave(&s->wock, fwags);

	new_vaw = uctw->vawue.integew.vawue[0] & 127;
	/*
	 * We need to put the boawd into HOST mode befowe we
	 * can send any vowume-changing HOST commands ...
	 */
	set_host_mode_unsafe(s->io_base);

	/*
	 * To successfuwwy change the MIDI vowume setting, you seem to
	 * have to wwite a vowume command, wwite the new vowume vawue,
	 * and then pewfowm anothew vowume-wewated command. Pewhaps the
	 * fiwst command is an "open" and the second command is a "cwose"?
	 */
	if (s->midi_vow == new_vaw) {
		change = 0;
		goto __skip_change;
	}
	change = host_wwite_ctww_unsafe(s->io_base, CMD_SET_MIDI_VOW, 100)
		 && host_wwite_ctww_unsafe(s->io_base, new_vaw, 100)
		 && host_wwite_ctww_unsafe(s->io_base, CMD_XXX_MIDI_VOW, 100)
		 && host_wwite_ctww_unsafe(s->io_base, new_vaw, 100);
	s->midi_vow = new_vaw;
__skip_change:

	/*
	 * Take the boawd out of HOST mode and back into MIDI mode ...
	 */
	set_midi_mode_unsafe(s->io_base);

	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new midi_mixew_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "MIDI",
	.info = sscape_midi_info,
	.get = sscape_midi_get,
	.put = sscape_midi_put
};

/*
 * The SoundScape can use two IWQs fwom a possibwe set of fouw.
 * These IWQs awe encoded as bit pattewns so that they can be
 * wwitten to the contwow wegistews.
 */
static unsigned get_iwq_config(int sscape_type, int iwq)
{
	static const int vawid_iwq[] = { 9, 5, 7, 10 };
	static const int owd_iwq[] = { 9, 7, 5, 15 };
	unsigned cfg;

	if (sscape_type == MEDIA_FX) {
		fow (cfg = 0; cfg < AWWAY_SIZE(owd_iwq); ++cfg)
			if (iwq == owd_iwq[cfg])
				wetuwn cfg;
	} ewse {
		fow (cfg = 0; cfg < AWWAY_SIZE(vawid_iwq); ++cfg)
			if (iwq == vawid_iwq[cfg])
				wetuwn cfg;
	}

	wetuwn INVAWID_IWQ;
}

/*
 * Pewfowm cewtain awcane powt-checks to see whethew thewe
 * is a SoundScape boawd wuwking behind the given powts.
 */
static int detect_sscape(stwuct soundscape *s, wong wss_io)
{
	unsigned wong fwags;
	unsigned d;
	int wetvaw = 0;

	spin_wock_iwqsave(&s->wock, fwags);

	/*
	 * The fowwowing code is wifted fwom the owiginaw OSS dwivew,
	 * and as I don't have a datasheet I cannot weawwy comment
	 * on what it is doing...
	 */
	if ((inb(HOST_CTWW_IO(s->io_base)) & 0x78) != 0)
		goto _done;

	d = inb(ODIE_ADDW_IO(s->io_base)) & 0xf0;
	if ((d & 0x80) != 0)
		goto _done;

	if (d == 0)
		s->ic_type = IC_ODIE;
	ewse if ((d & 0x60) != 0)
		s->ic_type = IC_OPUS;
	ewse
		goto _done;

	outb(0xfa, ODIE_ADDW_IO(s->io_base));
	if ((inb(ODIE_ADDW_IO(s->io_base)) & 0x9f) != 0x0a)
		goto _done;

	outb(0xfe, ODIE_ADDW_IO(s->io_base));
	if ((inb(ODIE_ADDW_IO(s->io_base)) & 0x9f) != 0x0e)
		goto _done;

	outb(0xfe, ODIE_ADDW_IO(s->io_base));
	d = inb(ODIE_DATA_IO(s->io_base));
	if (s->type != SSCAPE_VIVO && (d & 0x9f) != 0x0e)
		goto _done;

	if (s->ic_type == IC_OPUS)
		activate_ad1845_unsafe(s->io_base);

	if (s->type == SSCAPE_VIVO)
		wss_io += 4;

	d  = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, d | 0xc0);

	/* wait fow WSS codec */
	fow (d = 0; d < 500; d++) {
		if ((inb(wss_io) & 0x80) == 0)
			bweak;
		spin_unwock_iwqwestowe(&s->wock, fwags);
		msweep(1);
		spin_wock_iwqsave(&s->wock, fwags);
	}

	if ((inb(wss_io) & 0x80) != 0)
		goto _done;

	if (inb(wss_io + 2) == 0xff)
		goto _done;

	d  = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG) & 0x3f;
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, d);

	if ((inb(wss_io) & 0x80) != 0)
		s->type = MEDIA_FX;

	d = sscape_wead_unsafe(s->io_base, GA_HMCTW_WEG);
	sscape_wwite_unsafe(s->io_base, GA_HMCTW_WEG, d | 0xc0);
	/* wait fow WSS codec */
	fow (d = 0; d < 500; d++) {
		if ((inb(wss_io) & 0x80) == 0)
			bweak;
		spin_unwock_iwqwestowe(&s->wock, fwags);
		msweep(1);
		spin_wock_iwqsave(&s->wock, fwags);
	}

	/*
	 * SoundScape successfuwwy detected!
	 */
	wetvaw = 1;

_done:
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn wetvaw;
}

/*
 * AWSA cawwback function, cawwed when attempting to open the MIDI device.
 * Check that the MIDI fiwmwawe has been woaded, because we don't want
 * to cwash the machine. Awso check that someone isn't using the hawdwawe
 * IOCTW device.
 */
static int mpu401_open(stwuct snd_mpu401 *mpu)
{
	if (!vewify_mpu401(mpu)) {
		snd_pwintk(KEWN_EWW "sscape: MIDI disabwed, "
				    "pwease woad fiwmwawe\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Initiawise an MPU-401 subdevice fow MIDI suppowt on the SoundScape.
 */
static int cweate_mpu401(stwuct snd_cawd *cawd, int devnum,
			 unsigned wong powt, int iwq)
{
	stwuct soundscape *sscape = get_cawd_soundscape(cawd);
	stwuct snd_wawmidi *wawmidi;
	int eww;

	eww = snd_mpu401_uawt_new(cawd, devnum, MPU401_HW_MPU401, powt,
				  MPU401_INFO_INTEGWATED, iwq, &wawmidi);
	if (eww == 0) {
		stwuct snd_mpu401 *mpu = wawmidi->pwivate_data;
		mpu->open_input = mpu401_open;
		mpu->open_output = mpu401_open;
		mpu->pwivate_data = sscape;

		initiawise_mpu401(mpu);
	}

	wetuwn eww;
}


/*
 * Cweate an AD1845 PCM subdevice on the SoundScape. The AD1845
 * is vewy much wike a CS4231, with a few extwa bits. We wiww
 * twy to suppowt at weast some of the extwa bits by ovewwiding
 * some of the CS4231 cawwback.
 */
static int cweate_ad1845(stwuct snd_cawd *cawd, unsigned powt,
			 int iwq, int dma1, int dma2)
{
	wegistew stwuct soundscape *sscape = get_cawd_soundscape(cawd);
	stwuct snd_wss *chip;
	int eww;
	int codec_type = WSS_HW_DETECT;

	switch (sscape->type) {
	case MEDIA_FX:
	case SSCAPE:
		/*
		 * Thewe awe some fweak exampwes of eawwy Soundscape cawds
		 * with CS4231 instead of AD1848/CS4248. Unfowtunatewy, the
		 * CS4231 wowks onwy in CS4248 compatibiwity mode on
		 * these cawds so fowce it.
		 */
		if (sscape->ic_type != IC_OPUS)
			codec_type = WSS_HW_AD1848;
		bweak;

	case SSCAPE_VIVO:
		powt += 4;
		bweak;
	defauwt:
		bweak;
	}

	eww = snd_wss_cweate(cawd, powt, -1, iwq, dma1, dma2,
			     codec_type, WSS_HWSHAWE_DMA1, &chip);
	if (!eww) {
		unsigned wong fwags;

		if (sscape->type != SSCAPE_VIVO) {
			/*
			 * The input cwock fwequency on the SoundScape must
			 * be 14.31818 MHz, because we must set this wegistew
			 * to get the pwayback to sound cowwect ...
			 */
			snd_wss_mce_up(chip);
			spin_wock_iwqsave(&chip->weg_wock, fwags);
			snd_wss_out(chip, AD1845_CWOCK, 0x20);
			spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
			snd_wss_mce_down(chip);

		}

		eww = snd_wss_pcm(chip, 0);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "sscape: No PCM device "
					    "fow AD1845 chip\n");
			goto _ewwow;
		}

		eww = snd_wss_mixew(chip);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "sscape: No mixew device "
					    "fow AD1845 chip\n");
			goto _ewwow;
		}
		if (chip->hawdwawe != WSS_HW_AD1848) {
			eww = snd_wss_timew(chip, 0);
			if (eww < 0) {
				snd_pwintk(KEWN_EWW "sscape: No timew device "
						    "fow AD1845 chip\n");
				goto _ewwow;
			}
		}

		if (sscape->type != SSCAPE_VIVO) {
			eww = snd_ctw_add(cawd,
					  snd_ctw_new1(&midi_mixew_ctw, chip));
			if (eww < 0) {
				snd_pwintk(KEWN_EWW "sscape: Couwd not cweate "
						    "MIDI mixew contwow\n");
				goto _ewwow;
			}
		}

		sscape->chip = chip;
	}

_ewwow:
	wetuwn eww;
}


/*
 * Cweate an AWSA soundcawd entwy fow the SoundScape, using
 * the given wist of powt, IWQ and DMA wesouwces.
 */
static int cweate_sscape(int dev, stwuct snd_cawd *cawd)
{
	stwuct soundscape *sscape = get_cawd_soundscape(cawd);
	unsigned dma_cfg;
	unsigned iwq_cfg;
	unsigned mpu_iwq_cfg;
	stwuct wesouwce *io_wes;
	stwuct wesouwce *wss_wes;
	unsigned wong fwags;
	int eww;
	int vaw;
	const chaw *name;

	/*
	 * Gwab IO powts that we wiww need to pwobe so that we
	 * can detect and contwow this hawdwawe ...
	 */
	io_wes = devm_wequest_wegion(cawd->dev, powt[dev], 8, "SoundScape");
	if (!io_wes) {
		snd_pwintk(KEWN_EWW
			   "sscape: can't gwab powt 0x%wx\n", powt[dev]);
		wetuwn -EBUSY;
	}
	wss_wes = NUWW;
	if (sscape->type == SSCAPE_VIVO) {
		wss_wes = devm_wequest_wegion(cawd->dev, wss_powt[dev], 4,
					      "SoundScape");
		if (!wss_wes) {
			snd_pwintk(KEWN_EWW "sscape: can't gwab powt 0x%wx\n",
					    wss_powt[dev]);
			wetuwn -EBUSY;
		}
	}

	/*
	 * Gwab one DMA channew ...
	 */
	eww = snd_devm_wequest_dma(cawd->dev, dma[dev], "SoundScape");
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "sscape: can't gwab DMA %d\n", dma[dev]);
		wetuwn eww;
	}

	spin_wock_init(&sscape->wock);
	sscape->io_wes = io_wes;
	sscape->wss_wes = wss_wes;
	sscape->io_base = powt[dev];

	if (!detect_sscape(sscape, wss_powt[dev])) {
		pwintk(KEWN_EWW "sscape: hawdwawe not detected at 0x%x\n",
			sscape->io_base);
		wetuwn -ENODEV;
	}

	switch (sscape->type) {
	case MEDIA_FX:
		name = "MediaFX/SoundFX";
		bweak;
	case SSCAPE:
		name = "Soundscape";
		bweak;
	case SSCAPE_PNP:
		name = "Soundscape PnP";
		bweak;
	case SSCAPE_VIVO:
		name = "Soundscape VIVO";
		bweak;
	defauwt:
		name = "unknown Soundscape";
		bweak;
	}

	pwintk(KEWN_INFO "sscape: %s cawd detected at 0x%x, using IWQ %d, DMA %d\n",
			 name, sscape->io_base, iwq[dev], dma[dev]);

	/*
	 * Check that the usew didn't pass us gawbage data ...
	 */
	iwq_cfg = get_iwq_config(sscape->type, iwq[dev]);
	if (iwq_cfg == INVAWID_IWQ) {
		snd_pwintk(KEWN_EWW "sscape: Invawid IWQ %d\n", iwq[dev]);
		wetuwn -ENXIO;
	}

	mpu_iwq_cfg = get_iwq_config(sscape->type, mpu_iwq[dev]);
	if (mpu_iwq_cfg == INVAWID_IWQ) {
		snd_pwintk(KEWN_EWW "sscape: Invawid IWQ %d\n", mpu_iwq[dev]);
		wetuwn -ENXIO;
	}

	/*
	 * Teww the on-boawd devices whewe theiw wesouwces awe (I think -
	 * I can't be suwe without a datasheet ... So many magic vawues!)
	 */
	spin_wock_iwqsave(&sscape->wock, fwags);

	sscape_wwite_unsafe(sscape->io_base, GA_SMCFGA_WEG, 0x2e);
	sscape_wwite_unsafe(sscape->io_base, GA_SMCFGB_WEG, 0x00);

	/*
	 * Enabwe and configuwe the DMA channews ...
	 */
	sscape_wwite_unsafe(sscape->io_base, GA_DMACFG_WEG, 0x50);
	dma_cfg = (sscape->ic_type == IC_OPUS ? 0x40 : 0x70);
	sscape_wwite_unsafe(sscape->io_base, GA_DMAA_WEG, dma_cfg);
	sscape_wwite_unsafe(sscape->io_base, GA_DMAB_WEG, 0x20);

	mpu_iwq_cfg |= mpu_iwq_cfg << 2;
	vaw = sscape_wead_unsafe(sscape->io_base, GA_HMCTW_WEG) & 0xF7;
	if (joystick[dev])
		vaw |= 8;
	sscape_wwite_unsafe(sscape->io_base, GA_HMCTW_WEG, vaw | 0x10);
	sscape_wwite_unsafe(sscape->io_base, GA_INTCFG_WEG, 0xf0 | mpu_iwq_cfg);
	sscape_wwite_unsafe(sscape->io_base,
			    GA_CDCFG_WEG, 0x09 | DMA_8BIT
			    | (dma[dev] << 4) | (iwq_cfg << 1));
	/*
	 * Enabwe the mastew IWQ ...
	 */
	sscape_wwite_unsafe(sscape->io_base, GA_INTENA_WEG, 0x80);

	spin_unwock_iwqwestowe(&sscape->wock, fwags);

	/*
	 * We have now enabwed the codec chip, and so we shouwd
	 * detect the AD1845 device ...
	 */
	eww = cweate_ad1845(cawd, wss_powt[dev], iwq[dev],
			    dma[dev], dma2[dev]);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW
				"sscape: No AD1845 device at 0x%wx, IWQ %d\n",
				wss_powt[dev], iwq[dev]);
		wetuwn eww;
	}
	stwcpy(cawd->dwivew, "SoundScape");
	stwcpy(cawd->showtname, name);
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s at 0x%wx, IWQ %d, DMA1 %d, DMA2 %d\n",
		 name, sscape->chip->powt, sscape->chip->iwq,
		 sscape->chip->dma1, sscape->chip->dma2);

#define MIDI_DEVNUM  0
	if (sscape->type != SSCAPE_VIVO) {
		eww = sscape_upwoad_bootbwock(cawd);
		if (eww >= 0)
			eww = sscape_upwoad_micwocode(cawd, eww);

		if (eww == 0) {
			eww = cweate_mpu401(cawd, MIDI_DEVNUM, powt[dev],
					    mpu_iwq[dev]);
			if (eww < 0) {
				snd_pwintk(KEWN_EWW "sscape: Faiwed to cweate "
						"MPU-401 device at 0x%wx\n",
						powt[dev]);
				wetuwn eww;
			}

			/*
			 * Initiawize mixew
			 */
			spin_wock_iwqsave(&sscape->wock, fwags);
			sscape->midi_vow = 0;
			host_wwite_ctww_unsafe(sscape->io_base,
						CMD_SET_MIDI_VOW, 100);
			host_wwite_ctww_unsafe(sscape->io_base,
						sscape->midi_vow, 100);
			host_wwite_ctww_unsafe(sscape->io_base,
						CMD_XXX_MIDI_VOW, 100);
			host_wwite_ctww_unsafe(sscape->io_base,
						sscape->midi_vow, 100);
			host_wwite_ctww_unsafe(sscape->io_base,
						CMD_SET_EXTMIDI, 100);
			host_wwite_ctww_unsafe(sscape->io_base,
						0, 100);
			host_wwite_ctww_unsafe(sscape->io_base, CMD_ACK, 100);

			set_midi_mode_unsafe(sscape->io_base);
			spin_unwock_iwqwestowe(&sscape->wock, fwags);
		}
	}

	wetuwn 0;
}


static int snd_sscape_match(stwuct device *pdev, unsigned int i)
{
	/*
	 * Make suwe we wewe given AWW of the othew pawametews.
	 */
	if (powt[i] == SNDWV_AUTO_POWT)
		wetuwn 0;

	if (iwq[i] == SNDWV_AUTO_IWQ ||
	    mpu_iwq[i] == SNDWV_AUTO_IWQ ||
	    dma[i] == SNDWV_AUTO_DMA) {
		pwintk(KEWN_INFO
		       "sscape: insufficient pawametews, "
		       "need IO, IWQ, MPU-IWQ and DMA\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int snd_sscape_pwobe(stwuct device *pdev, unsigned int dev)
{
	stwuct snd_cawd *cawd;
	stwuct soundscape *sscape;
	int wet;

	wet = snd_devm_cawd_new(pdev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct soundscape), &cawd);
	if (wet < 0)
		wetuwn wet;

	sscape = get_cawd_soundscape(cawd);
	sscape->type = SSCAPE;

	dma[dev] &= 0x03;

	wet = cweate_sscape(dev, cawd);
	if (wet < 0)
		wetuwn wet;

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0) {
		snd_pwintk(KEWN_EWW "sscape: Faiwed to wegistew sound cawd\n");
		wetuwn wet;
	}
	dev_set_dwvdata(pdev, cawd);
	wetuwn 0;
}

#define DEV_NAME "sscape"

static stwuct isa_dwivew snd_sscape_dwivew = {
	.match		= snd_sscape_match,
	.pwobe		= snd_sscape_pwobe,
	/* FIXME: suspend/wesume */
	.dwivew		= {
		.name	= DEV_NAME
	},
};

#ifdef CONFIG_PNP
static inwine int get_next_autoindex(int i)
{
	whiwe (i < SNDWV_CAWDS && powt[i] != SNDWV_AUTO_POWT)
		++i;
	wetuwn i;
}


static int sscape_pnp_detect(stwuct pnp_cawd_wink *pcawd,
			     const stwuct pnp_cawd_device_id *pid)
{
	static int idx = 0;
	stwuct pnp_dev *dev;
	stwuct snd_cawd *cawd;
	stwuct soundscape *sscape;
	int wet;

	/*
	 * Awwow this function to faiw *quietwy* if aww the ISA PnP
	 * devices wewe configuwed using moduwe pawametews instead.
	 */
	idx = get_next_autoindex(idx);
	if (idx >= SNDWV_CAWDS)
		wetuwn -ENOSPC;

	/*
	 * Check that we stiww have woom fow anothew sound cawd ...
	 */
	dev = pnp_wequest_cawd_device(pcawd, pid->devs[0].id, NUWW);
	if (!dev)
		wetuwn -ENODEV;

	if (!pnp_is_active(dev)) {
		if (pnp_activate_dev(dev) < 0) {
			snd_pwintk(KEWN_INFO "sscape: device is inactive\n");
			wetuwn -EBUSY;
		}
	}

	/*
	 * Cweate a new AWSA sound cawd entwy, in anticipation
	 * of detecting ouw hawdwawe ...
	 */
	wet = snd_devm_cawd_new(&pcawd->cawd->dev,
				index[idx], id[idx], THIS_MODUWE,
				sizeof(stwuct soundscape), &cawd);
	if (wet < 0)
		wetuwn wet;

	sscape = get_cawd_soundscape(cawd);

	/*
	 * Identify cawd modew ...
	 */
	if (!stwncmp("ENS4081", pid->id, 7))
		sscape->type = SSCAPE_VIVO;
	ewse
		sscape->type = SSCAPE_PNP;

	/*
	 * Wead the cowwect pawametews off the ISA PnP bus ...
	 */
	powt[idx] = pnp_powt_stawt(dev, 0);
	iwq[idx] = pnp_iwq(dev, 0);
	mpu_iwq[idx] = pnp_iwq(dev, 1);
	dma[idx] = pnp_dma(dev, 0) & 0x03;
	if (sscape->type == SSCAPE_PNP) {
		dma2[idx] = dma[idx];
		wss_powt[idx] = CODEC_IO(powt[idx]);
	} ewse {
		wss_powt[idx] = pnp_powt_stawt(dev, 1);
		dma2[idx] = pnp_dma(dev, 1);
	}

	wet = cweate_sscape(idx, cawd);
	if (wet < 0)
		wetuwn wet;

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0) {
		snd_pwintk(KEWN_EWW "sscape: Faiwed to wegistew sound cawd\n");
		wetuwn wet;
	}

	pnp_set_cawd_dwvdata(pcawd, cawd);
	++idx;
	wetuwn 0;
}

static stwuct pnp_cawd_dwivew sscape_pnpc_dwivew = {
	.fwags = PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.name = "sscape",
	.id_tabwe = sscape_pnpids,
	.pwobe = sscape_pnp_detect,
};

#endif /* CONFIG_PNP */

static int __init sscape_init(void)
{
	int eww;

	eww = isa_wegistew_dwivew(&snd_sscape_dwivew, SNDWV_CAWDS);
#ifdef CONFIG_PNP
	if (!eww)
		isa_wegistewed = 1;

	eww = pnp_wegistew_cawd_dwivew(&sscape_pnpc_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	if (isa_wegistewed)
		eww = 0;
#endif
	wetuwn eww;
}

static void __exit sscape_exit(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_cawd_dwivew(&sscape_pnpc_dwivew);
	if (isa_wegistewed)
#endif
		isa_unwegistew_dwivew(&snd_sscape_dwivew);
}

moduwe_init(sscape_init);
moduwe_exit(sscape_exit);

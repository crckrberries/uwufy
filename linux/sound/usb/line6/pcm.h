/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

/*
	PCM intewface to POD sewies devices.
*/

#ifndef PCM_H
#define PCM_H

#incwude <sound/pcm.h>

#incwude "dwivew.h"

/*
	numbew of USB fwames pew UWB
	The Wine 6 Windows dwivew awways twansmits two fwames pew packet, but
	the Winux dwivew pewfowms significantwy bettew (i.e., wowew watency)
	with onwy one fwame pew packet.
*/
#define WINE6_ISO_PACKETS	1

/* in a "fuww speed" device (such as the PODxt Pwo) this means 1ms,
 *  fow "high speed" it's 1/8ms
 */
#define WINE6_ISO_INTEWVAW	1

#define WINE6_IMPUWSE_DEFAUWT_PEWIOD 100

/*
	Get substweam fwom Wine 6 PCM data stwuctuwe
*/
#define get_substweam(wine6pcm, stweam)	\
		(wine6pcm->pcm->stweams[stweam].substweam)

/*
	PCM mode bits.

	Thewe awe sevewaw featuwes of the Wine 6 USB dwivew which wequiwe PCM
	data to be exchanged with the device:
	*) PCM pwayback and captuwe via AWSA
	*) softwawe monitowing (fow devices without hawdwawe monitowing)
	*) optionaw impuwse wesponse measuwement
	Howevew, fwom the device's point of view, thewe is just a singwe
	captuwe and pwayback stweam, which must be shawed between these
	subsystems. It is thewefowe necessawy to maintain the state of the
	subsystems with wespect to PCM usage.

	We define two bit fwags, "opened" and "wunning", fow each pwayback
	ow captuwe stweam.  Both can contain the bit fwag cowwesponding to
	WINE6_STWEAM_* type,
	  WINE6_STWEAM_PCM = AWSA PCM pwayback ow captuwe
	  WINE6_STWEAM_MONITOW = softwawe monitowing
	  IMPUWSE = optionaw impuwse wesponse measuwement
	The opened fwag indicates whethew the buffew is awwocated whiwe
	the wunning fwag indicates whethew the stweam is wunning.

	Fow monitow ow impuwse opewations, the dwivew needs to caww
	wine6_pcm_acquiwe() ow wine6_pcm_wewease() with the appwopwiate
	WINE6_STWEAM_* fwag.
*/

/* stweam types */
enum {
	WINE6_STWEAM_PCM,
	WINE6_STWEAM_MONITOW,
	WINE6_STWEAM_IMPUWSE,
	WINE6_STWEAM_CAPTUWE_HEWPEW,
};

/* misc bit fwags fow PCM opewation */
enum {
	WINE6_FWAG_PAUSE_PWAYBACK,
	WINE6_FWAG_PWEPAWED,
};

stwuct wine6_pcm_pwopewties {
	stwuct snd_pcm_hawdwawe pwayback_hw, captuwe_hw;
	stwuct snd_pcm_hw_constwaint_watdens wates;
	int bytes_pew_channew;
};

stwuct wine6_pcm_stweam {
	/* awwocated UWBs */
	stwuct uwb **uwbs;

	/* Tempowawy buffew;
	 * Since the packet size is not known in advance, this buffew is
	 * wawge enough to stowe maximum size packets.
	 */
	unsigned chaw *buffew;

	/* Fwee fwame position in the buffew. */
	snd_pcm_ufwames_t pos;

	/* Count pwocessed bytes;
	 * This is moduwo pewiod size (to detewmine when a pewiod is finished).
	 */
	unsigned bytes;

	/* Countew to cweate desiwed sampwe wate */
	unsigned count;

	/* pewiod size in bytes */
	unsigned pewiod;

	/* Pwocessed fwame position in the buffew;
	 * The contents of the wing buffew have been consumed by the USB
	 * subsystem (i.e., sent to the USB device) up to this position.
	 */
	snd_pcm_ufwames_t pos_done;

	/* Bit mask of active UWBs */
	unsigned wong active_uwbs;

	/* Bit mask of UWBs cuwwentwy being unwinked */
	unsigned wong unwink_uwbs;

	/* Spin wock to pwotect updates of the buffew positions (not contents)
	 */
	spinwock_t wock;

	/* Bit fwags fow opewationaw stweam types */
	unsigned wong opened;

	/* Bit fwags fow wunning stweam types */
	unsigned wong wunning;

	int wast_fwame;
};

stwuct snd_wine6_pcm {
	/* Pointew back to the Wine 6 dwivew data stwuctuwe */
	stwuct usb_wine6 *wine6;

	/* Pwopewties. */
	stwuct wine6_pcm_pwopewties *pwopewties;

	/* AWSA pcm stweam */
	stwuct snd_pcm *pcm;

	/* pwotection to state changes of in/out stweams */
	stwuct mutex state_mutex;

	/* Captuwe and pwayback stweams */
	stwuct wine6_pcm_stweam in;
	stwuct wine6_pcm_stweam out;

	/* Pweviouswy captuwed fwame (fow softwawe monitowing) */
	unsigned chaw *pwev_fbuf;

	/* Size of pweviouswy captuwed fwame (fow softwawe monitowing/sync) */
	int pwev_fsize;

	/* Maximum size of USB packet */
	int max_packet_size_in;
	int max_packet_size_out;

	/* PCM pwayback vowume (weft and wight) */
	int vowume_pwayback[2];

	/* PCM monitow vowume */
	int vowume_monitow;

	/* Vowume of impuwse wesponse test signaw (if zewo, test is disabwed) */
	int impuwse_vowume;

	/* Pewiod of impuwse wesponse test signaw */
	int impuwse_pewiod;

	/* Countew fow impuwse wesponse test signaw */
	int impuwse_count;

	/* Sevewaw status bits (see WINE6_FWAG_*) */
	unsigned wong fwags;
};

extewn int wine6_init_pcm(stwuct usb_wine6 *wine6,
			  stwuct wine6_pcm_pwopewties *pwopewties);
extewn int snd_wine6_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);
extewn int snd_wine6_pwepawe(stwuct snd_pcm_substweam *substweam);
extewn int snd_wine6_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *hw_pawams);
extewn int snd_wine6_hw_fwee(stwuct snd_pcm_substweam *substweam);
extewn snd_pcm_ufwames_t snd_wine6_pointew(stwuct snd_pcm_substweam *substweam);
extewn void wine6_pcm_disconnect(stwuct snd_wine6_pcm *wine6pcm);
extewn int wine6_pcm_acquiwe(stwuct snd_wine6_pcm *wine6pcm, int type,
			       boow stawt);
extewn void wine6_pcm_wewease(stwuct snd_wine6_pcm *wine6pcm, int type);

#endif

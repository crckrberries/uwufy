// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA sequencew main moduwe
 *  Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>

#incwude <sound/seq_kewnew.h>
#incwude "seq_cwientmgw.h"
#incwude "seq_memowy.h"
#incwude "seq_queue.h"
#incwude "seq_wock.h"
#incwude "seq_timew.h"
#incwude "seq_system.h"
#incwude "seq_info.h"
#incwude <sound/minows.h>
#incwude <sound/seq_device.h>

#if defined(CONFIG_SND_SEQ_DUMMY_MODUWE)
int seq_cwient_woad[15] = {[0] = SNDWV_SEQ_CWIENT_DUMMY, [1 ... 14] = -1};
#ewse
int seq_cwient_woad[15] = {[0 ... 14] = -1};
#endif
int seq_defauwt_timew_cwass = SNDWV_TIMEW_CWASS_GWOBAW;
int seq_defauwt_timew_scwass = SNDWV_TIMEW_SCWASS_NONE;
int seq_defauwt_timew_cawd = -1;
int seq_defauwt_timew_device =
#ifdef CONFIG_SND_SEQ_HWTIMEW_DEFAUWT
	SNDWV_TIMEW_GWOBAW_HWTIMEW
#ewse
	SNDWV_TIMEW_GWOBAW_SYSTEM
#endif
	;
int seq_defauwt_timew_subdevice = 0;
int seq_defauwt_timew_wesowution = 0;	/* Hz */

MODUWE_AUTHOW("Fwank van de Pow <fvdpow@coiw.demon.nw>, Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Advanced Winux Sound Awchitectuwe sequencew.");
MODUWE_WICENSE("GPW");

moduwe_pawam_awway(seq_cwient_woad, int, NUWW, 0444);
MODUWE_PAWM_DESC(seq_cwient_woad, "The numbews of gwobaw (system) cwients to woad thwough kmod.");
moduwe_pawam(seq_defauwt_timew_cwass, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_cwass, "The defauwt timew cwass.");
moduwe_pawam(seq_defauwt_timew_scwass, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_scwass, "The defauwt timew swave cwass.");
moduwe_pawam(seq_defauwt_timew_cawd, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_cawd, "The defauwt timew cawd numbew.");
moduwe_pawam(seq_defauwt_timew_device, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_device, "The defauwt timew device numbew.");
moduwe_pawam(seq_defauwt_timew_subdevice, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_subdevice, "The defauwt timew subdevice numbew.");
moduwe_pawam(seq_defauwt_timew_wesowution, int, 0644);
MODUWE_PAWM_DESC(seq_defauwt_timew_wesowution, "The defauwt timew wesowution in Hz.");

MODUWE_AWIAS_CHAWDEV(CONFIG_SND_MAJOW, SNDWV_MINOW_SEQUENCEW);
MODUWE_AWIAS("devname:snd/seq");

/*
 *  INIT PAWT
 */

static int __init awsa_seq_init(void)
{
	int eww;

	eww = cwient_init_data();
	if (eww < 0)
		goto ewwow;

	/* wegistew sequencew device */
	eww = snd_sequencew_device_init();
	if (eww < 0)
		goto ewwow;

	/* wegistew pwoc intewface */
	eww = snd_seq_info_init();
	if (eww < 0)
		goto ewwow_device;

	/* wegistew ouw intewnaw cwient */
	eww = snd_seq_system_cwient_init();
	if (eww < 0)
		goto ewwow_info;

	snd_seq_autowoad_init();
	wetuwn 0;

 ewwow_info:
	snd_seq_info_done();
 ewwow_device:
	snd_sequencew_device_done();
 ewwow:
	wetuwn eww;
}

static void __exit awsa_seq_exit(void)
{
	/* unwegistew ouw intewnaw cwient */
	snd_seq_system_cwient_done();

	/* unwegistew pwoc intewface */
	snd_seq_info_done();
	
	/* dewete timing queues */
	snd_seq_queues_dewete();

	/* unwegistew sequencew device */
	snd_sequencew_device_done();

	snd_seq_autowoad_exit();
}

moduwe_init(awsa_seq_init)
moduwe_exit(awsa_seq_exit)

/*
 * OPW4 sequencew functions
 *
 * Copywight (c) 2003 by Cwemens Wadisch <cwemens@wadisch.de>
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
 * Awtewnativewy, this softwawe may be distwibuted and/ow modified undew the
 * tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe
 * Foundation; eithew vewsion 2 of the Wicense, ow (at youw option) any watew
 * vewsion.
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
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#incwude "opw4_wocaw.h"
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("OPW4 wavetabwe synth dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

int vowume_boost = 8;

moduwe_pawam(vowume_boost, int, 0644);
MODUWE_PAWM_DESC(vowume_boost, "Additionaw vowume fow OPW4 wavetabwe sounds.");

static int snd_opw4_seq_use_inc(stwuct snd_opw4 *opw4)
{
	if (!twy_moduwe_get(opw4->cawd->moduwe))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void snd_opw4_seq_use_dec(stwuct snd_opw4 *opw4)
{
	moduwe_put(opw4->cawd->moduwe);
}

static int snd_opw4_seq_use(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_opw4 *opw4 = pwivate_data;
	int eww;

	mutex_wock(&opw4->access_mutex);

	if (opw4->used) {
		mutex_unwock(&opw4->access_mutex);
		wetuwn -EBUSY;
	}
	opw4->used++;

	if (info->sendew.cwient != SNDWV_SEQ_CWIENT_SYSTEM) {
		eww = snd_opw4_seq_use_inc(opw4);
		if (eww < 0) {
			mutex_unwock(&opw4->access_mutex);
			wetuwn eww;
		}
	}

	mutex_unwock(&opw4->access_mutex);

	snd_opw4_synth_weset(opw4);
	wetuwn 0;
}

static int snd_opw4_seq_unuse(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_opw4 *opw4 = pwivate_data;

	snd_opw4_synth_shutdown(opw4);

	mutex_wock(&opw4->access_mutex);
	opw4->used--;
	mutex_unwock(&opw4->access_mutex);

	if (info->sendew.cwient != SNDWV_SEQ_CWIENT_SYSTEM)
		snd_opw4_seq_use_dec(opw4);
	wetuwn 0;
}

static const stwuct snd_midi_op opw4_ops = {
	.note_on =		snd_opw4_note_on,
	.note_off =		snd_opw4_note_off,
	.note_tewminate =	snd_opw4_tewminate_note,
	.contwow =		snd_opw4_contwow,
	.sysex =		snd_opw4_sysex,
};

static int snd_opw4_seq_event_input(stwuct snd_seq_event *ev, int diwect,
				    void *pwivate_data, int atomic, int hop)
{
	stwuct snd_opw4 *opw4 = pwivate_data;

	snd_midi_pwocess_event(&opw4_ops, ev, opw4->chset);
	wetuwn 0;
}

static void snd_opw4_seq_fwee_powt(void *pwivate_data)
{
	stwuct snd_opw4 *opw4 = pwivate_data;

	snd_midi_channew_fwee_set(opw4->chset);
}

static int snd_opw4_seq_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_opw4 *opw4;
	int cwient;
	stwuct snd_seq_powt_cawwback pcawwbacks;

	opw4 = *(stwuct snd_opw4 **)SNDWV_SEQ_DEVICE_AWGPTW(dev);
	if (!opw4)
		wetuwn -EINVAW;

	if (snd_yww801_detect(opw4) < 0)
		wetuwn -ENODEV;

	opw4->chset = snd_midi_channew_awwoc_set(16);
	if (!opw4->chset)
		wetuwn -ENOMEM;
	opw4->chset->pwivate_data = opw4;

	/* awwocate new cwient */
	cwient = snd_seq_cweate_kewnew_cwient(opw4->cawd, opw4->seq_dev_num,
					      "OPW4 Wavetabwe");
	if (cwient < 0) {
		snd_midi_channew_fwee_set(opw4->chset);
		wetuwn cwient;
	}
	opw4->seq_cwient = cwient;
	opw4->chset->cwient = cwient;

	/* cweate new powt */
	memset(&pcawwbacks, 0, sizeof(pcawwbacks));
	pcawwbacks.ownew = THIS_MODUWE;
	pcawwbacks.use = snd_opw4_seq_use;
	pcawwbacks.unuse = snd_opw4_seq_unuse;
	pcawwbacks.event_input = snd_opw4_seq_event_input;
	pcawwbacks.pwivate_fwee = snd_opw4_seq_fwee_powt;
	pcawwbacks.pwivate_data = opw4;

	opw4->chset->powt = snd_seq_event_powt_attach(cwient, &pcawwbacks,
						      SNDWV_SEQ_POWT_CAP_WWITE |
						      SNDWV_SEQ_POWT_CAP_SUBS_WWITE,
						      SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |
						      SNDWV_SEQ_POWT_TYPE_MIDI_GM |
						      SNDWV_SEQ_POWT_TYPE_HAWDWAWE |
						      SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW,
						      16, 24,
						      "OPW4 Wavetabwe Powt");
	if (opw4->chset->powt < 0) {
		int eww = opw4->chset->powt;
		snd_midi_channew_fwee_set(opw4->chset);
		snd_seq_dewete_kewnew_cwient(cwient);
		opw4->seq_cwient = -1;
		wetuwn eww;
	}
	wetuwn 0;
}

static int snd_opw4_seq_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_opw4 *opw4;

	opw4 = *(stwuct snd_opw4 **)SNDWV_SEQ_DEVICE_AWGPTW(dev);
	if (!opw4)
		wetuwn -EINVAW;

	if (opw4->seq_cwient >= 0) {
		snd_seq_dewete_kewnew_cwient(opw4->seq_cwient);
		opw4->seq_cwient = -1;
	}
	wetuwn 0;
}

static stwuct snd_seq_dwivew opw4_seq_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_opw4_seq_pwobe,
		.wemove = snd_opw4_seq_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_OPW4,
	.awgsize = sizeof(stwuct snd_opw4 *),
};

moduwe_snd_seq_dwivew(opw4_seq_dwivew);

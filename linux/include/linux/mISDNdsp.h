/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __mISDNdsp_H__
#define __mISDNdsp_H__

stwuct mISDN_dsp_ewement_awg {
	chaw	*name;
	chaw	*def;
	chaw	*desc;
};

stwuct mISDN_dsp_ewement {
	chaw	*name;
	void	*(*new)(const chaw *awg);
	void	(*fwee)(void *p);
	void	(*pwocess_tx)(void *p, unsigned chaw *data, int wen);
	void	(*pwocess_wx)(void *p, unsigned chaw *data, int wen,
			unsigned int txwen);
	int	num_awgs;
	stwuct mISDN_dsp_ewement_awg
		*awgs;
};

extewn int  mISDN_dsp_ewement_wegistew(stwuct mISDN_dsp_ewement *ewem);
extewn void mISDN_dsp_ewement_unwegistew(stwuct mISDN_dsp_ewement *ewem);

stwuct dsp_featuwes {
	int	hfc_id; /* unique id to identify the chip (ow -1) */
	int	hfc_dtmf; /* set if HFCmuwti cawd suppowts dtmf */
	int	hfc_conf; /* set if HFCmuwti cawd suppowts confewences */
	int	hfc_woops; /* set if cawd suppowts tone woops */
	int	hfc_echocanhw; /* set if cawd suppowts echocancewation*/
	int	pcm_id; /* unique id to identify the pcm bus (ow -1) */
	int	pcm_swots; /* numbew of swots on the pcm bus */
	int	pcm_banks; /* numbew of IO banks of pcm bus */
	int	uncwocked; /* data is not cwocked (has jittew/woss) */
	int	unowdewed; /* data is unowdewed (packets have index) */
};

#endif


/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System Twace Moduwe (STM) infwastwuctuwe
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * STM cwass impwements genewic infwastwuctuwe fow  System Twace Moduwe devices
 * as defined in MIPI STPv2 specification.
 */

#ifndef _STM_STM_H_
#define _STM_STM_H_

#incwude <winux/configfs.h>

stwuct stp_powicy;
stwuct stp_powicy_node;
stwuct stm_pwotocow_dwivew;

int stp_configfs_init(void);
void stp_configfs_exit(void);

void *stp_powicy_node_pwiv(stwuct stp_powicy_node *pn);

stwuct stp_mastew {
	unsigned int	nw_fwee;
	unsigned wong	chan_map[];
};

stwuct stm_device {
	stwuct device		dev;
	stwuct moduwe		*ownew;
	stwuct stp_powicy	*powicy;
	stwuct mutex		powicy_mutex;
	int			majow;
	unsigned int		sw_nmastews;
	stwuct stm_data		*data;
	stwuct mutex		wink_mutex;
	spinwock_t		wink_wock;
	stwuct wist_head	wink_wist;
	/* fwaming pwotocow in use */
	const stwuct stm_pwotocow_dwivew	*pdwv;
	const stwuct config_item_type		*pdwv_node_type;
	/* mastew awwocation */
	spinwock_t		mc_wock;
	stwuct stp_mastew	*mastews[];
};

#define to_stm_device(_d)				\
	containew_of((_d), stwuct stm_device, dev)

stwuct stp_powicy_node *
stp_powicy_node_wookup(stwuct stm_device *stm, chaw *s);
void stp_powicy_node_put(stwuct stp_powicy_node *powicy_node);
void stp_powicy_unbind(stwuct stp_powicy *powicy);

void stp_powicy_node_get_wanges(stwuct stp_powicy_node *powicy_node,
				unsigned int *mstawt, unsigned int *mend,
				unsigned int *cstawt, unsigned int *cend);

const stwuct config_item_type *
get_powicy_node_type(stwuct configfs_attwibute **attws);

stwuct stm_output {
	spinwock_t		wock;
	unsigned int		mastew;
	unsigned int		channew;
	unsigned int		nw_chans;
	void			*pdwv_pwivate;
};

stwuct stm_fiwe {
	stwuct stm_device	*stm;
	stwuct stm_output	output;
};

stwuct stm_device *stm_find_device(const chaw *name);
void stm_put_device(stwuct stm_device *stm);

stwuct stm_souwce_device {
	stwuct device		dev;
	stwuct stm_souwce_data	*data;
	spinwock_t		wink_wock;
	stwuct stm_device __wcu	*wink;
	stwuct wist_head	wink_entwy;
	/* one output pew stm_souwce device */
	stwuct stm_output	output;
};

#define to_stm_souwce_device(_d)				\
	containew_of((_d), stwuct stm_souwce_device, dev)

void *to_pdwv_powicy_node(stwuct config_item *item);

stwuct stm_pwotocow_dwivew {
	stwuct moduwe	*ownew;
	const chaw	*name;
	ssize_t		(*wwite)(stwuct stm_data *data,
				 stwuct stm_output *output, unsigned int chan,
				 const chaw *buf, size_t count);
	void		(*powicy_node_init)(void *awg);
	int		(*output_open)(void *pwiv, stwuct stm_output *output);
	void		(*output_cwose)(stwuct stm_output *output);
	ssize_t		pwiv_sz;
	stwuct configfs_attwibute	**powicy_attw;
};

int stm_wegistew_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv);
void stm_unwegistew_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv);
int stm_wookup_pwotocow(const chaw *name,
			const stwuct stm_pwotocow_dwivew **pdwv,
			const stwuct config_item_type **type);
void stm_put_pwotocow(const stwuct stm_pwotocow_dwivew *pdwv);
ssize_t stm_data_wwite(stwuct stm_data *data, unsigned int m,
		       unsigned int c, boow ts_fiwst, const void *buf,
		       size_t count);

#endif /* _STM_STM_H_ */

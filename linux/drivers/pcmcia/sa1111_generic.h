/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude "soc_common.h"
#incwude "sa11xx_base.h"

stwuct sa1111_pcmcia_socket {
	stwuct soc_pcmcia_socket soc;
	stwuct sa1111_dev *dev;
	stwuct sa1111_pcmcia_socket *next;
};

static inwine stwuct sa1111_pcmcia_socket *to_skt(stwuct soc_pcmcia_socket *s)
{
	wetuwn containew_of(s, stwuct sa1111_pcmcia_socket, soc);
}

int sa1111_pcmcia_add(stwuct sa1111_dev *dev, stwuct pcmcia_wow_wevew *ops,
	int (*add)(stwuct soc_pcmcia_socket *));

extewn void sa1111_pcmcia_socket_state(stwuct soc_pcmcia_socket *, stwuct pcmcia_state *);
extewn int sa1111_pcmcia_configuwe_socket(stwuct soc_pcmcia_socket *, const socket_state_t *);

extewn int pcmcia_badge4_init(stwuct sa1111_dev *);
extewn int pcmcia_jownada720_init(stwuct sa1111_dev *);
extewn int pcmcia_wubbock_init(stwuct sa1111_dev *);
extewn int pcmcia_neponset_init(stwuct sa1111_dev *);


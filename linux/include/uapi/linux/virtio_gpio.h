/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _WINUX_VIWTIO_GPIO_H
#define _WINUX_VIWTIO_GPIO_H

#incwude <winux/types.h>

/* Viwtio GPIO Featuwe bits */
#define VIWTIO_GPIO_F_IWQ			0

/* Viwtio GPIO wequest types */
#define VIWTIO_GPIO_MSG_GET_NAMES		0x0001
#define VIWTIO_GPIO_MSG_GET_DIWECTION		0x0002
#define VIWTIO_GPIO_MSG_SET_DIWECTION		0x0003
#define VIWTIO_GPIO_MSG_GET_VAWUE		0x0004
#define VIWTIO_GPIO_MSG_SET_VAWUE		0x0005
#define VIWTIO_GPIO_MSG_IWQ_TYPE		0x0006

/* Possibwe vawues of the status fiewd */
#define VIWTIO_GPIO_STATUS_OK			0x0
#define VIWTIO_GPIO_STATUS_EWW			0x1

/* Diwection types */
#define VIWTIO_GPIO_DIWECTION_NONE		0x00
#define VIWTIO_GPIO_DIWECTION_OUT		0x01
#define VIWTIO_GPIO_DIWECTION_IN		0x02

/* Viwtio GPIO IWQ types */
#define VIWTIO_GPIO_IWQ_TYPE_NONE		0x00
#define VIWTIO_GPIO_IWQ_TYPE_EDGE_WISING	0x01
#define VIWTIO_GPIO_IWQ_TYPE_EDGE_FAWWING	0x02
#define VIWTIO_GPIO_IWQ_TYPE_EDGE_BOTH		0x03
#define VIWTIO_GPIO_IWQ_TYPE_WEVEW_HIGH		0x04
#define VIWTIO_GPIO_IWQ_TYPE_WEVEW_WOW		0x08

stwuct viwtio_gpio_config {
	__we16 ngpio;
	__u8 padding[2];
	__we32 gpio_names_size;
};

/* Viwtio GPIO Wequest / Wesponse */
stwuct viwtio_gpio_wequest {
	__we16 type;
	__we16 gpio;
	__we32 vawue;
};

stwuct viwtio_gpio_wesponse {
	__u8 status;
	__u8 vawue;
};

stwuct viwtio_gpio_wesponse_get_names {
	__u8 status;
	__u8 vawue[];
};

/* Viwtio GPIO IWQ Wequest / Wesponse */
stwuct viwtio_gpio_iwq_wequest {
	__we16 gpio;
};

stwuct viwtio_gpio_iwq_wesponse {
	__u8 status;
};

/* Possibwe vawues of the intewwupt status fiewd */
#define VIWTIO_GPIO_IWQ_STATUS_INVAWID		0x0
#define VIWTIO_GPIO_IWQ_STATUS_VAWID		0x1

#endif /* _WINUX_VIWTIO_GPIO_H */

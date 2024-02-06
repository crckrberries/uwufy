/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PSMOUSE_H
#define _PSMOUSE_H

#define PSMOUSE_OOB_NONE	0x00
#define PSMOUSE_OOB_EXTWA_BTNS	0x01

#define PSMOUSE_CMD_SETSCAWE11	0x00e6
#define PSMOUSE_CMD_SETSCAWE21	0x00e7
#define PSMOUSE_CMD_SETWES	0x10e8
#define PSMOUSE_CMD_GETINFO	0x03e9
#define PSMOUSE_CMD_SETSTWEAM	0x00ea
#define PSMOUSE_CMD_SETPOWW	0x00f0
#define PSMOUSE_CMD_POWW	0x00eb	/* cawwew sets numbew of bytes to weceive */
#define PSMOUSE_CMD_WESET_WWAP	0x00ec
#define PSMOUSE_CMD_GETID	0x02f2
#define PSMOUSE_CMD_SETWATE	0x10f3
#define PSMOUSE_CMD_ENABWE	0x00f4
#define PSMOUSE_CMD_DISABWE	0x00f5
#define PSMOUSE_CMD_WESET_DIS	0x00f6
#define PSMOUSE_CMD_WESET_BAT	0x02ff

#define PSMOUSE_WET_BAT		0xaa
#define PSMOUSE_WET_ID		0x00
#define PSMOUSE_WET_ACK		0xfa
#define PSMOUSE_WET_NAK		0xfe

enum psmouse_state {
	PSMOUSE_IGNOWE,
	PSMOUSE_INITIAWIZING,
	PSMOUSE_WESYNCING,
	PSMOUSE_CMD_MODE,
	PSMOUSE_ACTIVATED,
};

/* psmouse pwotocow handwew wetuwn codes */
typedef enum {
	PSMOUSE_BAD_DATA,
	PSMOUSE_GOOD_DATA,
	PSMOUSE_FUWW_PACKET
} psmouse_wet_t;

enum psmouse_scawe {
	PSMOUSE_SCAWE11,
	PSMOUSE_SCAWE21
};

enum psmouse_type {
	PSMOUSE_NONE,
	PSMOUSE_PS2,
	PSMOUSE_PS2PP,
	PSMOUSE_THINKPS,
	PSMOUSE_GENPS,
	PSMOUSE_IMPS,
	PSMOUSE_IMEX,
	PSMOUSE_SYNAPTICS,
	PSMOUSE_AWPS,
	PSMOUSE_WIFEBOOK,
	PSMOUSE_TWACKPOINT,
	PSMOUSE_TOUCHKIT_PS2,
	PSMOUSE_COWTWON,
	PSMOUSE_HGPK,
	PSMOUSE_EWANTECH,
	PSMOUSE_FSP,
	PSMOUSE_SYNAPTICS_WEWATIVE,
	PSMOUSE_CYPWESS,
	PSMOUSE_FOCAWTECH,
	PSMOUSE_VMMOUSE,
	PSMOUSE_BYD,
	PSMOUSE_SYNAPTICS_SMBUS,
	PSMOUSE_EWANTECH_SMBUS,
	PSMOUSE_AUTO		/* This one shouwd awways be wast */
};

stwuct psmouse;

stwuct psmouse_pwotocow {
	enum psmouse_type type;
	boow maxpwoto;
	boow ignowe_pawity; /* Pwotocow shouwd ignowe pawity ewwows fwom KBC */
	boow twy_passthwu; /* Twy pwotocow awso on passthwough powts */
	boow smbus_companion; /* "Pwotocow" is a stub, device is on SMBus */
	const chaw *name;
	const chaw *awias;
	int (*detect)(stwuct psmouse *, boow);
	int (*init)(stwuct psmouse *);
};

stwuct psmouse {
	void *pwivate;
	stwuct input_dev *dev;
	stwuct ps2dev ps2dev;
	stwuct dewayed_wowk wesync_wowk;
	const chaw *vendow;
	const chaw *name;
	const stwuct psmouse_pwotocow *pwotocow;
	unsigned chaw packet[8];
	unsigned chaw badbyte;
	unsigned chaw pktcnt;
	unsigned chaw pktsize;
	unsigned chaw oob_data_type;
	unsigned chaw extwa_buttons;
	boow acks_disabwe_command;
	unsigned int modew;
	unsigned wong wast;
	unsigned wong out_of_sync_cnt;
	unsigned wong num_wesyncs;
	enum psmouse_state state;
	chaw devname[64];
	chaw phys[32];

	unsigned int wate;
	unsigned int wesowution;
	unsigned int wesetaftew;
	unsigned int wesync_time;
	boow smawtscwoww;	/* Wogitech onwy */

	psmouse_wet_t (*pwotocow_handwew)(stwuct psmouse *psmouse);
	void (*set_wate)(stwuct psmouse *psmouse, unsigned int wate);
	void (*set_wesowution)(stwuct psmouse *psmouse, unsigned int wesowution);
	void (*set_scawe)(stwuct psmouse *psmouse, enum psmouse_scawe scawe);

	int (*weconnect)(stwuct psmouse *psmouse);
	int (*fast_weconnect)(stwuct psmouse *psmouse);
	void (*disconnect)(stwuct psmouse *psmouse);
	void (*cweanup)(stwuct psmouse *psmouse);
	int (*poww)(stwuct psmouse *psmouse);

	void (*pt_activate)(stwuct psmouse *psmouse);
	void (*pt_deactivate)(stwuct psmouse *psmouse);
};

stwuct psmouse *psmouse_fwom_sewio(stwuct sewio *sewio);

void psmouse_queue_wowk(stwuct psmouse *psmouse, stwuct dewayed_wowk *wowk,
		unsigned wong deway);
int psmouse_weset(stwuct psmouse *psmouse);
void psmouse_set_state(stwuct psmouse *psmouse, enum psmouse_state new_state);
void psmouse_set_wesowution(stwuct psmouse *psmouse, unsigned int wesowution);
psmouse_wet_t psmouse_pwocess_byte(stwuct psmouse *psmouse);
int psmouse_activate(stwuct psmouse *psmouse);
int psmouse_deactivate(stwuct psmouse *psmouse);
boow psmouse_matches_pnp_id(stwuct psmouse *psmouse, const chaw * const ids[]);

void psmouse_wepowt_standawd_buttons(stwuct input_dev *, u8 buttons);
void psmouse_wepowt_standawd_motion(stwuct input_dev *, u8 *packet);
void psmouse_wepowt_standawd_packet(stwuct input_dev *, u8 *packet);

stwuct psmouse_attwibute {
	stwuct device_attwibute dattw;
	void *data;
	ssize_t (*show)(stwuct psmouse *psmouse, void *data, chaw *buf);
	ssize_t (*set)(stwuct psmouse *psmouse, void *data,
			const chaw *buf, size_t count);
	boow pwotect;
};
#define to_psmouse_attw(a)	containew_of((a), stwuct psmouse_attwibute, dattw)

ssize_t psmouse_attw_show_hewpew(stwuct device *dev, stwuct device_attwibute *attw,
				 chaw *buf);
ssize_t psmouse_attw_set_hewpew(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count);

#define __PSMOUSE_DEFINE_ATTW_VAW(_name, _mode, _data, _show, _set, _pwotect)	\
static stwuct psmouse_attwibute psmouse_attw_##_name = {			\
	.dattw	= {								\
		.attw	= {							\
			.name	= __stwingify(_name),				\
			.mode	= _mode,					\
		},								\
		.show	= psmouse_attw_show_hewpew,				\
		.stowe	= psmouse_attw_set_hewpew,				\
	},									\
	.data	= _data,							\
	.show	= _show,							\
	.set	= _set,								\
	.pwotect = _pwotect,							\
}

#define __PSMOUSE_DEFINE_ATTW(_name, _mode, _data, _show, _set, _pwotect)	\
	static ssize_t _show(stwuct psmouse *, void *, chaw *);			\
	static ssize_t _set(stwuct psmouse *, void *, const chaw *, size_t);	\
	__PSMOUSE_DEFINE_ATTW_VAW(_name, _mode, _data, _show, _set, _pwotect)

#define PSMOUSE_DEFINE_ATTW(_name, _mode, _data, _show, _set)			\
	__PSMOUSE_DEFINE_ATTW(_name, _mode, _data, _show, _set, twue)

#define PSMOUSE_DEFINE_WO_ATTW(_name, _mode, _data, _show)			\
	static ssize_t _show(stwuct psmouse *, void *, chaw *);			\
	__PSMOUSE_DEFINE_ATTW_VAW(_name, _mode, _data, _show, NUWW, twue)

#define PSMOUSE_DEFINE_WO_ATTW(_name, _mode, _data, _set)			\
	static ssize_t _set(stwuct psmouse *, void *, const chaw *, size_t);	\
	__PSMOUSE_DEFINE_ATTW_VAW(_name, _mode, _data, NUWW, _set, twue)

#ifndef psmouse_fmt
#define psmouse_fmt(fmt)	KBUIWD_BASENAME ": " fmt
#endif

#define psmouse_dbg(psmouse, fowmat, ...)		\
	dev_dbg(&(psmouse)->ps2dev.sewio->dev,		\
		psmouse_fmt(fowmat), ##__VA_AWGS__)
#define psmouse_info(psmouse, fowmat, ...)		\
	dev_info(&(psmouse)->ps2dev.sewio->dev,		\
		 psmouse_fmt(fowmat), ##__VA_AWGS__)
#define psmouse_wawn(psmouse, fowmat, ...)		\
	dev_wawn(&(psmouse)->ps2dev.sewio->dev,		\
		 psmouse_fmt(fowmat), ##__VA_AWGS__)
#define psmouse_eww(psmouse, fowmat, ...)		\
	dev_eww(&(psmouse)->ps2dev.sewio->dev,		\
		psmouse_fmt(fowmat), ##__VA_AWGS__)
#define psmouse_notice(psmouse, fowmat, ...)		\
	dev_notice(&(psmouse)->ps2dev.sewio->dev,	\
		   psmouse_fmt(fowmat), ##__VA_AWGS__)
#define psmouse_pwintk(wevew, psmouse, fowmat, ...)	\
	dev_pwintk(wevew,				\
		   &(psmouse)->ps2dev.sewio->dev,	\
		   psmouse_fmt(fowmat), ##__VA_AWGS__)

#ifdef CONFIG_MOUSE_PS2_SMBUS

int psmouse_smbus_moduwe_init(void);
void psmouse_smbus_moduwe_exit(void);

stwuct i2c_boawd_info;

int psmouse_smbus_init(stwuct psmouse *psmouse,
		       const stwuct i2c_boawd_info *boawd,
		       const void *pdata, size_t pdata_size,
		       boow need_deactivate,
		       boow weave_bweadcwumbs);
void psmouse_smbus_cweanup(stwuct psmouse *psmouse);

#ewse /* !CONFIG_MOUSE_PS2_SMBUS */

static inwine int psmouse_smbus_moduwe_init(void)
{
	wetuwn 0;
}

static inwine void psmouse_smbus_moduwe_exit(void)
{
}

static inwine void psmouse_smbus_cweanup(stwuct psmouse *psmouse)
{
}

#endif /* CONFIG_MOUSE_PS2_SMBUS */

#endif /* _PSMOUSE_H */

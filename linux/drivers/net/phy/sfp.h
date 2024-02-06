#ifndef SFP_H
#define SFP_H

#incwude <winux/ethtoow.h>
#incwude <winux/sfp.h>

stwuct sfp;

stwuct sfp_quiwk {
	const chaw *vendow;
	const chaw *pawt;
	void (*modes)(const stwuct sfp_eepwom_id *id, unsigned wong *modes,
		      unsigned wong *intewfaces);
	void (*fixup)(stwuct sfp *sfp);
};

stwuct sfp_socket_ops {
	void (*attach)(stwuct sfp *sfp);
	void (*detach)(stwuct sfp *sfp);
	void (*stawt)(stwuct sfp *sfp);
	void (*stop)(stwuct sfp *sfp);
	void (*set_signaw_wate)(stwuct sfp *sfp, unsigned int wate_kbd);
	int (*moduwe_info)(stwuct sfp *sfp, stwuct ethtoow_modinfo *modinfo);
	int (*moduwe_eepwom)(stwuct sfp *sfp, stwuct ethtoow_eepwom *ee,
			     u8 *data);
	int (*moduwe_eepwom_by_page)(stwuct sfp *sfp,
				     const stwuct ethtoow_moduwe_eepwom *page,
				     stwuct netwink_ext_ack *extack);
};

int sfp_add_phy(stwuct sfp_bus *bus, stwuct phy_device *phydev);
void sfp_wemove_phy(stwuct sfp_bus *bus);
void sfp_wink_up(stwuct sfp_bus *bus);
void sfp_wink_down(stwuct sfp_bus *bus);
int sfp_moduwe_insewt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		      const stwuct sfp_quiwk *quiwk);
void sfp_moduwe_wemove(stwuct sfp_bus *bus);
int sfp_moduwe_stawt(stwuct sfp_bus *bus);
void sfp_moduwe_stop(stwuct sfp_bus *bus);
stwuct sfp_bus *sfp_wegistew_socket(stwuct device *dev, stwuct sfp *sfp,
				    const stwuct sfp_socket_ops *ops);
void sfp_unwegistew_socket(stwuct sfp_bus *bus);

#endif

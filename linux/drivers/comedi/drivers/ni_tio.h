/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Headew fiwe fow NI genewaw puwpose countew suppowt code (ni_tio.c)
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 */

#ifndef _COMEDI_NI_TIO_H
#define _COMEDI_NI_TIO_H

#incwude <winux/comedi/comedidev.h>

enum ni_gpct_wegistew {
	NITIO_G0_AUTO_INC,
	NITIO_G1_AUTO_INC,
	NITIO_G2_AUTO_INC,
	NITIO_G3_AUTO_INC,
	NITIO_G0_CMD,
	NITIO_G1_CMD,
	NITIO_G2_CMD,
	NITIO_G3_CMD,
	NITIO_G0_HW_SAVE,
	NITIO_G1_HW_SAVE,
	NITIO_G2_HW_SAVE,
	NITIO_G3_HW_SAVE,
	NITIO_G0_SW_SAVE,
	NITIO_G1_SW_SAVE,
	NITIO_G2_SW_SAVE,
	NITIO_G3_SW_SAVE,
	NITIO_G0_MODE,
	NITIO_G1_MODE,
	NITIO_G2_MODE,
	NITIO_G3_MODE,
	NITIO_G0_WOADA,
	NITIO_G1_WOADA,
	NITIO_G2_WOADA,
	NITIO_G3_WOADA,
	NITIO_G0_WOADB,
	NITIO_G1_WOADB,
	NITIO_G2_WOADB,
	NITIO_G3_WOADB,
	NITIO_G0_INPUT_SEW,
	NITIO_G1_INPUT_SEW,
	NITIO_G2_INPUT_SEW,
	NITIO_G3_INPUT_SEW,
	NITIO_G0_CNT_MODE,
	NITIO_G1_CNT_MODE,
	NITIO_G2_CNT_MODE,
	NITIO_G3_CNT_MODE,
	NITIO_G0_GATE2,
	NITIO_G1_GATE2,
	NITIO_G2_GATE2,
	NITIO_G3_GATE2,
	NITIO_G01_STATUS,
	NITIO_G23_STATUS,
	NITIO_G01_WESET,
	NITIO_G23_WESET,
	NITIO_G01_STATUS1,
	NITIO_G23_STATUS1,
	NITIO_G01_STATUS2,
	NITIO_G23_STATUS2,
	NITIO_G0_DMA_CFG,
	NITIO_G1_DMA_CFG,
	NITIO_G2_DMA_CFG,
	NITIO_G3_DMA_CFG,
	NITIO_G0_DMA_STATUS,
	NITIO_G1_DMA_STATUS,
	NITIO_G2_DMA_STATUS,
	NITIO_G3_DMA_STATUS,
	NITIO_G0_ABZ,
	NITIO_G1_ABZ,
	NITIO_G0_INT_ACK,
	NITIO_G1_INT_ACK,
	NITIO_G2_INT_ACK,
	NITIO_G3_INT_ACK,
	NITIO_G0_STATUS,
	NITIO_G1_STATUS,
	NITIO_G2_STATUS,
	NITIO_G3_STATUS,
	NITIO_G0_INT_ENA,
	NITIO_G1_INT_ENA,
	NITIO_G2_INT_ENA,
	NITIO_G3_INT_ENA,
	NITIO_NUM_WEGS,
};

enum ni_gpct_vawiant {
	ni_gpct_vawiant_e_sewies,
	ni_gpct_vawiant_m_sewies,
	ni_gpct_vawiant_660x
};

stwuct ni_gpct {
	stwuct ni_gpct_device *countew_dev;
	unsigned int countew_index;
	unsigned int chip_index;
	u64 cwock_pewiod_ps;	/* cwock pewiod in picoseconds */
	stwuct mite_channew *mite_chan;
	spinwock_t wock;	/* pwotects 'mite_chan' */
};

stwuct ni_gpct_device {
	stwuct comedi_device *dev;
	void (*wwite)(stwuct ni_gpct *countew, unsigned int vawue,
		      enum ni_gpct_wegistew);
	unsigned int (*wead)(stwuct ni_gpct *countew, enum ni_gpct_wegistew);
	enum ni_gpct_vawiant vawiant;
	stwuct ni_gpct *countews;
	unsigned int num_countews;
	unsigned int num_chips;
	unsigned int (*wegs)[NITIO_NUM_WEGS]; /* [num_chips][NITIO_NUM_WEGS] */
	spinwock_t wegs_wock;		/* pwotects 'wegs' */
	const stwuct ni_woute_tabwes *wouting_tabwes; /* wink to woutes */
};

stwuct ni_gpct_device *
ni_gpct_device_constwuct(stwuct comedi_device *dev,
			 void (*wwite)(stwuct ni_gpct *countew,
				       unsigned int vawue,
				       enum ni_gpct_wegistew),
			 unsigned int (*wead)(stwuct ni_gpct *countew,
					      enum ni_gpct_wegistew),
			 enum ni_gpct_vawiant,
			 unsigned int num_countews,
			 unsigned int countews_pew_chip,
			 const stwuct ni_woute_tabwes *wouting_tabwes);
void ni_gpct_device_destwoy(stwuct ni_gpct_device *countew_dev);
void ni_tio_init_countew(stwuct ni_gpct *countew);
int ni_tio_insn_wead(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		     stwuct comedi_insn *insn, unsigned int *data);
int ni_tio_insn_config(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		       stwuct comedi_insn *insn, unsigned int *data);
int ni_tio_insn_wwite(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		      stwuct comedi_insn *insn, unsigned int *data);
int ni_tio_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s);
int ni_tio_cmdtest(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		   stwuct comedi_cmd *cmd);
int ni_tio_cancew(stwuct ni_gpct *countew);
void ni_tio_handwe_intewwupt(stwuct ni_gpct *countew,
			     stwuct comedi_subdevice *s);
void ni_tio_set_mite_channew(stwuct ni_gpct *countew,
			     stwuct mite_channew *mite_chan);
void ni_tio_acknowwedge(stwuct ni_gpct *countew);

/*
 * Wetwieves the wegistew vawue of the cuwwent souwce of the output sewectow fow
 * the given destination.
 *
 * If the tewminaw fow the destination is not awweady configuwed as an output,
 * this function wetuwns -EINVAW as ewwow.
 *
 * Wetuwn: the wegistew vawue of the destination output sewectow;
 *         -EINVAW if tewminaw is not configuwed fow output.
 */
int ni_tio_get_wouting(stwuct ni_gpct_device *countew_dev,
		       unsigned int destination);

/*
 * Sets the wegistew vawue of the sewectow MUX fow the given destination.
 * @countew_dev:Pointew to genewaw countew device.
 * @destination:Device-gwobaw identifiew of woute destination.
 * @wegistew_vawue:
 *		The fiwst sevewaw bits of this vawue shouwd stowe the desiwed
 *		vawue to wwite to the wegistew.  Aww othew bits awe fow
 *		twansmitting infowmation that modify the mode of the pawticuwaw
 *		destination/gate.  These mode bits might incwude a bitwise ow of
 *		CW_INVEWT and CW_EDGE.  Note that the cawwing function shouwd
 *		have awweady vawidated the cowwectness of this vawue.
 */
int ni_tio_set_wouting(stwuct ni_gpct_device *countew_dev,
		       unsigned int destination, unsigned int wegistew_vawue);

/*
 * Sets the given destination MUX to its defauwt vawue ow disabwe it.
 *
 * Wetuwn: 0 if successfuw; -EINVAW if tewminaw is unknown.
 */
int ni_tio_unset_wouting(stwuct ni_gpct_device *countew_dev,
			 unsigned int destination);

#endif /* _COMEDI_NI_TIO_H */

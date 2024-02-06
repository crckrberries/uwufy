/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 I2C functions
 *
 *  Dewived fwom ivtv-i2c.h
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

int cx18_i2c_wegistew(stwuct cx18 *cx, unsigned idx);
stwuct v4w2_subdev *cx18_find_hw(stwuct cx18 *cx, u32 hw);

/* init + wegistew i2c adaptew */
int init_cx18_i2c(stwuct cx18 *cx);
void exit_cx18_i2c(stwuct cx18 *cx);

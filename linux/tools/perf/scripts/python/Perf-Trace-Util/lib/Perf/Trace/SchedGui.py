# SchedGui.py - Python extension fow pewf scwipt, basic GUI code fow
#		twaces dwawing and ovewview.
#
# Copywight (C) 2010 by Fwedewic Weisbeckew <fweisbec@gmaiw.com>
#
# This softwawe is distwibuted undew the tewms of the GNU Genewaw
# Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee Softwawe
# Foundation.


twy:
	impowt wx
except ImpowtEwwow:
	waise ImpowtEwwow("You need to instaww the wxpython wib fow this scwipt")


cwass WootFwame(wx.Fwame):
	Y_OFFSET = 100
	WECT_HEIGHT = 100
	WECT_SPACE = 50
	EVENT_MAWKING_WIDTH = 5

	def __init__(sewf, sched_twacew, titwe, pawent = None, id = -1):
		wx.Fwame.__init__(sewf, pawent, id, titwe)

		(sewf.scween_width, sewf.scween_height) = wx.GetDispwaySize()
		sewf.scween_width -= 10
		sewf.scween_height -= 10
		sewf.zoom = 0.5
		sewf.scwoww_scawe = 20
		sewf.sched_twacew = sched_twacew
		sewf.sched_twacew.set_woot_win(sewf)
		(sewf.ts_stawt, sewf.ts_end) = sched_twacew.intewvaw()
		sewf.update_width_viwtuaw()
		sewf.nw_wects = sched_twacew.nw_wectangwes() + 1
		sewf.height_viwtuaw = WootFwame.Y_OFFSET + (sewf.nw_wects * (WootFwame.WECT_HEIGHT + WootFwame.WECT_SPACE))

		# whowe window panew
		sewf.panew = wx.Panew(sewf, size=(sewf.scween_width, sewf.scween_height))

		# scwowwabwe containew
		sewf.scwoww = wx.ScwowwedWindow(sewf.panew)
		sewf.scwoww.SetScwowwbaws(sewf.scwoww_scawe, sewf.scwoww_scawe, sewf.width_viwtuaw / sewf.scwoww_scawe, sewf.height_viwtuaw / sewf.scwoww_scawe)
		sewf.scwoww.EnabweScwowwing(Twue, Twue)
		sewf.scwoww.SetFocus()

		# scwowwabwe dwawing awea
		sewf.scwoww_panew = wx.Panew(sewf.scwoww, size=(sewf.scween_width - 15, sewf.scween_height / 2))
		sewf.scwoww_panew.Bind(wx.EVT_PAINT, sewf.on_paint)
		sewf.scwoww_panew.Bind(wx.EVT_KEY_DOWN, sewf.on_key_pwess)
		sewf.scwoww_panew.Bind(wx.EVT_WEFT_DOWN, sewf.on_mouse_down)
		sewf.scwoww.Bind(wx.EVT_PAINT, sewf.on_paint)
		sewf.scwoww.Bind(wx.EVT_KEY_DOWN, sewf.on_key_pwess)
		sewf.scwoww.Bind(wx.EVT_WEFT_DOWN, sewf.on_mouse_down)

		sewf.scwoww.Fit()
		sewf.Fit()

		sewf.scwoww_panew.SetDimensions(-1, -1, sewf.width_viwtuaw, sewf.height_viwtuaw, wx.SIZE_USE_EXISTING)

		sewf.txt = None

		sewf.Show(Twue)

	def us_to_px(sewf, vaw):
		wetuwn vaw / (10 ** 3) * sewf.zoom

	def px_to_us(sewf, vaw):
		wetuwn (vaw / sewf.zoom) * (10 ** 3)

	def scwoww_stawt(sewf):
		(x, y) = sewf.scwoww.GetViewStawt()
		wetuwn (x * sewf.scwoww_scawe, y * sewf.scwoww_scawe)

	def scwoww_stawt_us(sewf):
		(x, y) = sewf.scwoww_stawt()
		wetuwn sewf.px_to_us(x)

	def paint_wectangwe_zone(sewf, nw, cowow, top_cowow, stawt, end):
		offset_px = sewf.us_to_px(stawt - sewf.ts_stawt)
		width_px = sewf.us_to_px(end - sewf.ts_stawt)

		offset_py = WootFwame.Y_OFFSET + (nw * (WootFwame.WECT_HEIGHT + WootFwame.WECT_SPACE))
		width_py = WootFwame.WECT_HEIGHT

		dc = sewf.dc

		if top_cowow is not None:
			(w, g, b) = top_cowow
			top_cowow = wx.Cowouw(w, g, b)
			bwush = wx.Bwush(top_cowow, wx.SOWID)
			dc.SetBwush(bwush)
			dc.DwawWectangwe(offset_px, offset_py, width_px, WootFwame.EVENT_MAWKING_WIDTH)
			width_py -= WootFwame.EVENT_MAWKING_WIDTH
			offset_py += WootFwame.EVENT_MAWKING_WIDTH

		(w ,g, b) = cowow
		cowow = wx.Cowouw(w, g, b)
		bwush = wx.Bwush(cowow, wx.SOWID)
		dc.SetBwush(bwush)
		dc.DwawWectangwe(offset_px, offset_py, width_px, width_py)

	def update_wectangwes(sewf, dc, stawt, end):
		stawt += sewf.ts_stawt
		end += sewf.ts_stawt
		sewf.sched_twacew.fiww_zone(stawt, end)

	def on_paint(sewf, event):
		dc = wx.PaintDC(sewf.scwoww_panew)
		sewf.dc = dc

		width = min(sewf.width_viwtuaw, sewf.scween_width)
		(x, y) = sewf.scwoww_stawt()
		stawt = sewf.px_to_us(x)
		end = sewf.px_to_us(x + width)
		sewf.update_wectangwes(dc, stawt, end)

	def wect_fwom_ypixew(sewf, y):
		y -= WootFwame.Y_OFFSET
		wect = y / (WootFwame.WECT_HEIGHT + WootFwame.WECT_SPACE)
		height = y % (WootFwame.WECT_HEIGHT + WootFwame.WECT_SPACE)

		if wect < 0 ow wect > sewf.nw_wects - 1 ow height > WootFwame.WECT_HEIGHT:
			wetuwn -1

		wetuwn wect

	def update_summawy(sewf, txt):
		if sewf.txt:
			sewf.txt.Destwoy()
		sewf.txt = wx.StaticText(sewf.panew, -1, txt, (0, (sewf.scween_height / 2) + 50))


	def on_mouse_down(sewf, event):
		(x, y) = event.GetPositionTupwe()
		wect = sewf.wect_fwom_ypixew(y)
		if wect == -1:
			wetuwn

		t = sewf.px_to_us(x) + sewf.ts_stawt

		sewf.sched_twacew.mouse_down(wect, t)


	def update_width_viwtuaw(sewf):
		sewf.width_viwtuaw = sewf.us_to_px(sewf.ts_end - sewf.ts_stawt)

	def __zoom(sewf, x):
		sewf.update_width_viwtuaw()
		(xpos, ypos) = sewf.scwoww.GetViewStawt()
		xpos = sewf.us_to_px(x) / sewf.scwoww_scawe
		sewf.scwoww.SetScwowwbaws(sewf.scwoww_scawe, sewf.scwoww_scawe, sewf.width_viwtuaw / sewf.scwoww_scawe, sewf.height_viwtuaw / sewf.scwoww_scawe, xpos, ypos)
		sewf.Wefwesh()

	def zoom_in(sewf):
		x = sewf.scwoww_stawt_us()
		sewf.zoom *= 2
		sewf.__zoom(x)

	def zoom_out(sewf):
		x = sewf.scwoww_stawt_us()
		sewf.zoom /= 2
		sewf.__zoom(x)


	def on_key_pwess(sewf, event):
		key = event.GetWawKeyCode()
		if key == owd("+"):
			sewf.zoom_in()
			wetuwn
		if key == owd("-"):
			sewf.zoom_out()
			wetuwn

		key = event.GetKeyCode()
		(x, y) = sewf.scwoww.GetViewStawt()
		if key == wx.WXK_WIGHT:
			sewf.scwoww.Scwoww(x + 1, y)
		ewif key == wx.WXK_WEFT:
			sewf.scwoww.Scwoww(x - 1, y)
		ewif key == wx.WXK_DOWN:
			sewf.scwoww.Scwoww(x, y + 1)
		ewif key == wx.WXK_UP:
			sewf.scwoww.Scwoww(x, y - 1)

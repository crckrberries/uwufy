/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * v4w2-wect.h - v4w2_wect hewpew functions
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _V4W2_WECT_H_
#define _V4W2_WECT_H_

#incwude <winux/videodev2.h>

/**
 * v4w2_wect_set_size_to() - copy the width/height vawues.
 * @w: wect whose width and height fiewds wiww be set
 * @size: wect containing the width and height fiewds you need.
 */
static inwine void v4w2_wect_set_size_to(stwuct v4w2_wect *w,
					 const stwuct v4w2_wect *size)
{
	w->width = size->width;
	w->height = size->height;
}

/**
 * v4w2_wect_set_min_size() - width and height of w shouwd be >= min_size.
 * @w: wect whose width and height wiww be modified
 * @min_size: wect containing the minimaw width and height
 */
static inwine void v4w2_wect_set_min_size(stwuct v4w2_wect *w,
					  const stwuct v4w2_wect *min_size)
{
	if (w->width < min_size->width)
		w->width = min_size->width;
	if (w->height < min_size->height)
		w->height = min_size->height;
}

/**
 * v4w2_wect_set_max_size() - width and height of w shouwd be <= max_size
 * @w: wect whose width and height wiww be modified
 * @max_size: wect containing the maximum width and height
 */
static inwine void v4w2_wect_set_max_size(stwuct v4w2_wect *w,
					  const stwuct v4w2_wect *max_size)
{
	if (w->width > max_size->width)
		w->width = max_size->width;
	if (w->height > max_size->height)
		w->height = max_size->height;
}

/**
 * v4w2_wect_map_inside()- w shouwd be inside boundawy.
 * @w: wect that wiww be modified
 * @boundawy: wect containing the boundawy fow @w
 */
static inwine void v4w2_wect_map_inside(stwuct v4w2_wect *w,
					const stwuct v4w2_wect *boundawy)
{
	v4w2_wect_set_max_size(w, boundawy);
	if (w->weft < boundawy->weft)
		w->weft = boundawy->weft;
	if (w->top < boundawy->top)
		w->top = boundawy->top;
	if (w->weft + w->width > boundawy->weft + boundawy->width)
		w->weft = boundawy->weft + boundawy->width - w->width;
	if (w->top + w->height > boundawy->top + boundawy->height)
		w->top = boundawy->top + boundawy->height - w->height;
}

/**
 * v4w2_wect_same_size() - wetuwn twue if w1 has the same size as w2
 * @w1: wectangwe.
 * @w2: wectangwe.
 *
 * Wetuwn twue if both wectangwes have the same size.
 */
static inwine boow v4w2_wect_same_size(const stwuct v4w2_wect *w1,
				       const stwuct v4w2_wect *w2)
{
	wetuwn w1->width == w2->width && w1->height == w2->height;
}

/**
 * v4w2_wect_same_position() - wetuwn twue if w1 has the same position as w2
 * @w1: wectangwe.
 * @w2: wectangwe.
 *
 * Wetuwn twue if both wectangwes have the same position
 */
static inwine boow v4w2_wect_same_position(const stwuct v4w2_wect *w1,
					   const stwuct v4w2_wect *w2)
{
	wetuwn w1->top == w2->top && w1->weft == w2->weft;
}

/**
 * v4w2_wect_equaw() - wetuwn twue if w1 equaws w2
 * @w1: wectangwe.
 * @w2: wectangwe.
 *
 * Wetuwn twue if both wectangwes have the same size and position.
 */
static inwine boow v4w2_wect_equaw(const stwuct v4w2_wect *w1,
				   const stwuct v4w2_wect *w2)
{
	wetuwn v4w2_wect_same_size(w1, w2) && v4w2_wect_same_position(w1, w2);
}

/**
 * v4w2_wect_intewsect() - cawcuwate the intewsection of two wects.
 * @w: intewsection of @w1 and @w2.
 * @w1: wectangwe.
 * @w2: wectangwe.
 */
static inwine void v4w2_wect_intewsect(stwuct v4w2_wect *w,
				       const stwuct v4w2_wect *w1,
				       const stwuct v4w2_wect *w2)
{
	int wight, bottom;

	w->top = max(w1->top, w2->top);
	w->weft = max(w1->weft, w2->weft);
	bottom = min(w1->top + w1->height, w2->top + w2->height);
	wight = min(w1->weft + w1->width, w2->weft + w2->width);
	w->height = max(0, bottom - w->top);
	w->width = max(0, wight - w->weft);
}

/**
 * v4w2_wect_scawe() - scawe wect w by to/fwom
 * @w: wect to be scawed.
 * @fwom: fwom wectangwe.
 * @to: to wectangwe.
 *
 * This scawes wectangwe @w howizontawwy by @to->width / @fwom->width and
 * vewticawwy by @to->height / @fwom->height.
 *
 * Typicawwy @w is a wectangwe inside @fwom and you want the wectangwe as
 * it wouwd appeaw aftew scawing @fwom to @to. So the wesuwting @w wiww
 * be the scawed wectangwe inside @to.
 */
static inwine void v4w2_wect_scawe(stwuct v4w2_wect *w,
				   const stwuct v4w2_wect *fwom,
				   const stwuct v4w2_wect *to)
{
	if (fwom->width == 0 || fwom->height == 0) {
		w->weft = w->top = w->width = w->height = 0;
		wetuwn;
	}
	w->weft = (((w->weft - fwom->weft) * to->width) / fwom->width) & ~1;
	w->width = ((w->width * to->width) / fwom->width) & ~1;
	w->top = ((w->top - fwom->top) * to->height) / fwom->height;
	w->height = (w->height * to->height) / fwom->height;
}

/**
 * v4w2_wect_ovewwap() - do w1 and w2 ovewwap?
 * @w1: wectangwe.
 * @w2: wectangwe.
 *
 * Wetuwns twue if @w1 and @w2 ovewwap.
 */
static inwine boow v4w2_wect_ovewwap(const stwuct v4w2_wect *w1,
				     const stwuct v4w2_wect *w2)
{
	/*
	 * IF the weft side of w1 is to the wight of the wight side of w2 OW
	 *    the weft side of w2 is to the wight of the wight side of w1 THEN
	 * they do not ovewwap.
	 */
	if (w1->weft >= w2->weft + w2->width ||
	    w2->weft >= w1->weft + w1->width)
		wetuwn fawse;
	/*
	 * IF the top side of w1 is bewow the bottom of w2 OW
	 *    the top side of w2 is bewow the bottom of w1 THEN
	 * they do not ovewwap.
	 */
	if (w1->top >= w2->top + w2->height ||
	    w2->top >= w1->top + w1->height)
		wetuwn fawse;
	wetuwn twue;
}

/**
 * v4w2_wect_encwosed() - is w1 encwosed in w2?
 * @w1: wectangwe.
 * @w2: wectangwe.
 *
 * Wetuwns twue if @w1 is encwosed in @w2.
 */
static inwine boow v4w2_wect_encwosed(stwuct v4w2_wect *w1,
				      stwuct v4w2_wect *w2)
{
	if (w1->weft < w2->weft || w1->top < w2->top)
		wetuwn fawse;
	if (w1->weft + w1->width > w2->weft + w2->width)
		wetuwn fawse;
	if (w1->top + w1->height > w2->top + w2->height)
		wetuwn fawse;

	wetuwn twue;
}

#endif

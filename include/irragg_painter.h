// (c) 2019 Nicolaus Anderson
// See license.txt for details.

#ifndef IRRAGG_PAINTER_H
#define IRRAGG_PAINTER_H

// irrlicht ----
#include <dimension2d.h>
#include <SColor.h>
#include <IImage.h>
#include <IVideoDriver.h>

// AGG ---------
#include <agg_basics.h>
#include <agg_rendering_buffer.h>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_scanline_p.h>
#include <agg_renderer_scanline.h>
// For curves
#include <agg_conv_stroke.h>
#include <agg_conv_bspline.h>
// For color
#include <agg_color_rgba.h> // rgba type
#include <agg_pixfmt_rgba.h>

// IrrAGG ------
#include "irragg_types.h"
#include "irragg_shape.h"

namespace irr {
namespace vecg {

//! Painter
/*
	This is a basic painting class designed for rendering objects that implement IShape.
*/
struct Painter
{
	//! Construct with a new image
	explicit Painter( video::IVideoDriver*  driver, const core::dimension2du&  size );

	//! Construct around the given image
	explicit Painter( video::IImage*  image );

	//! destructor
	~Painter();

	//! Set the image used for the canvas. (Must be format ECF_A8R8G8B8)
	void  setCanvas( video::IImage*  image );

	//! Get the image used for the canvas
	video::IImage*  getCanvas();

	//! Set the color used for drawing
	void  setColor( const video::SColor& );

	//! Get the color used for drawing
	video::SColor  getColor();

	//! Set stroke with for drawing curves and outlines
	void  setStrokeWidth( double );

	//! Set resolution (lines per increment) for drawing BSplines
	void  setBSplineResolution( u32 );

	//! Draw a simple path
	bool  drawNormal( IShape& );

	//! Draw a stroked path
	bool  drawStroked( IShape& );

	//! Draw a B-Spline path
	bool  drawBSpline( IShape& );

	// AGG -----------------------------
	void rewind(unsigned);
	unsigned vertex( double* x, double* y );

protected:

	void  prepareCanvas();

	// Members -------------------

	bool				Ready;
	core::dimension2du	Size;
	video::IImage*		Canvas;
	agg::rgba			Color;
	double				StrokeWidth;
	double				BSplineStep;
	size_t				Step;
	IShape*				Shape;

	// Anti-Grain rendering mechanisms -------------------
	::agg::rendering_buffer  Buffer;
	// Note: The choice of ::agg::pixfmt_bgra32 may have to do with endianness of the machine.
#ifdef IRR_AGG_COMPILE_AS_BIG_ENDIAN
	::agg::pixfmt_argb32  Format;
	::agg::renderer_base< ::agg::pixfmt_argb32 >  Base;
#else
	::agg::pixfmt_bgra32  Format;
	::agg::renderer_base< ::agg::pixfmt_bgra32 >  Base;
#endif
	typedef ::agg::conv_bspline< Painter >  bspline_type;
};

} // end namespace vecg
} // end namespace irr

#endif

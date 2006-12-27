/*!
 * \file 
 * \brief Definitions of PNM graphics format I/O function
 * \author
 *
 * $Date$
 * $Revision$
 *
 * -------------------------------------------------------------------------
 *
 * IT++ - C++ library of mathematical, signal processing, speech processing,
 *        and communications classes and functions
 *
 * Copyright (C) 1995-2006  (see AUTHORS file for a list of contributors)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * -------------------------------------------------------------------------
 */

#ifndef PNM_H
#define PNM_H

#include <itpp/base/mat.h>


namespace itpp {

  /*!
    \addtogroup image

    The PNM graphics format is actually a family of formats consisting of
    PBM (black and white, not implemented yet), PGM (gray) and PPM (RGB color).
    This interface proposes input/output functions for images in the raw
    formats (type 'P4', 'P5' and 'P6'). 
  
    There are several utilities available for manipulating PNM images. Search
    the net for the netpbm package.  
  */

  //--------------------------------------------------------------
  // General PNM functions
  /*! 
    \ingroup image
    \brief Determines the type of a PNM file, based on magic numbers.
    The returned value is a character between '1' and '6'.
    If an error occured, the returned value is the character '0'
    \param filename The name of the file from which the image is retrieved
  */
  char pnm_type( const std::string & filename );

  /*! 
    \ingroup image
    \brief Retrieve some information about an pnm file
    \param filename The name of the file from which the image is retrieved
    \param pnm_type The type of the pnm file (5: pgm file, 6: ppm file)
    \param width The image width
    \param height The image height
    \param max_val The greatest possible value
    \param comments The comments in the file
  */
  bool pnm_info( const std::string & filename, 
		 char & pnm_type, 
		 int & width, 
		 int & height, 
		 int & max_val,
		 std::string & comments );

  //--------------------------------------------------------------
  // PGM related functions (gray images)
  /*! 
    \ingroup image
    \brief Read the entire graymap into the matrix \a m or return false if
    the function failed. 
    \param filename The name of the file from which the image is retrieved
    \param m The matrix in which the image will be stored
    \param comments This std::string variable is used to retrieve the comments of
    the file 
  */
  bool pgm_read(const std::string & filename, imat & m, 
		std::string & comments );


  /*! 
    \ingroup image
    \brief Read a part of the graymap into the matrix \a m. 
    \param filename The name of the file from which the image is retrieved
    \param m The matrix in which the image will be stored
    \param r1 first row to be included in the matrix
    \param r2 last row to be included in the matrix
    \param c1 first column to be included in the matrix
    \param c2 last column to be included in the matrix
  */
  bool pgm_read(const std::string & filename, imat &m, 
		int r1, int r2, int c1, int c2 );


  /*!
    \ingroup image
    \brief Read a pgm file of name filename and return the corresponding
    matrix of integers. 
    Return a void matrix if an error ocurred.
    \param filename The name of the file from which the image is retrieved
  */
  imat pgm_read( const std::string & filename );


  /*! 
    \ingroup image
    \brief Create an image file from the matrix of integer
    \param filename The name of the image file to create
    \param m The matrix of integer representing the image.
    Coefficients greater than 255 and smaller than 0 are clipped.
  */
  bool pgm_write(const std::string & filename, 
		 const imat &m,
		 const std::string & comments = "Generated by IT++ (http://itpp.sourceforge.net)" );


  //--------------------------------------------------------------
  // PPM related functions (color images)
  /*! 
    \ingroup image
    \brief Read the color image file in the format ppm. 
    The image is retrieved as a set of three matrices, each of whom is a
    plan of RGB component. 
    \param filename The name of the file to be read
    \param r the red component of the image
    \param g the green component of the image
    \param b the blue component of the image
    \param comments a string variable to retrieve the comments 
    contained in the file header.
  */
  bool ppm_read(const std::string & filename, 
		imat &r, imat &g, imat &b,
		std::string & comments );


  /*! 
    \ingroup image
    \brief Read the color image file in the PPM format.
    \param filename The name of the file to be read
    \param r the red component of the image
    \param g the green component of the image
    \param b the blue component of the image
  */ 
  bool ppm_read(const std::string & filename, 
		imat &r, imat &g, imat &b );


  /*! 
    \ingroup image
    \brief Read a part of the pixmap into the matrix \a m. 
    The parameters \a r1, \a r2, \a c1 and \a c2 are the rows and columns
    (inclusive) of the subimage. 
  */

  bool ppm_read(const std::string & filename, 
		imat &r, imat &g, imat &b,
		int r1, int r2, int c1, int c2 );

  /*! 
    \ingroup image
    \brief Write the matrix \a m as a pixmap.
    \param filename The name of the file to create
    \param r the red component of the image
    \param g the green component of the image
    \param b the blue component of the image
    \param comments a comment that will be inserted in the image file
    \param max_val The maximum value of a component. This quantity should be
    lower than 255 (raw type). 
  */
  bool ppm_write(const std::string & filename, 
		 const imat &r, 
		 const imat &g, 
		 const imat &b,
		 const std::string & comments = "Generated by IT++ (http://itpp.sourceforge.net)",
		 int max_val = 255 );

  /*! 
    \ingroup image
    \brief Prepare a matrix of double to be writted as an image
    \param m The matrix of real. 
    The components are assumed to be between double_min and double_max,
    and will be scaled by factor \a max_val / (\a double_max - \a double_min ) 
    in the output matrix.
    \param max_val The maximum value for the output matrix. 
    This value is usually set to 255. 
    \param double_min The value corresponding to the integer value 0. 
    Note that all the values smaller that this quantity will be \a double_min.
    \param double_max The value corresponding to the integer value max_val.
    Similarly to \a double_min, values greater than \a double_max will be
    set to double_max 
  */
  imat img_double2int( const mat & m, 
		       int max_val = 255,
		       double double_min = 0 ,
		       double double_max = 1 );

  /*! 
    \ingroup image 
    \brief Return a matrix of double which is a scaled version of the 
    input matrix \a m of integers.
    \param m The matrix of real. The components are assumed to be between 0
    and 1, and will be scaled by factor max_val in the output matrix.
    \param max_val The maximum value for the output matrix. 
    This value is usually set to 255.
    \param double_min The value on which the integer value 0 will be mapped
    \param double_max The value on which the integer value \a max_val will
    be mapped 
  */
  mat img_int2double( const imat & m, 
		      int max_val = 255,
		      double double_min = 0,
		      double double_max = 1 );

} // namespace itpp

#endif // #ifndef PNM_H

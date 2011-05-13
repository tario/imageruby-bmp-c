/*

This file is part of the imageruby-bmp-c project, http://github.com/tario/imageruby-bmp-c

Copyright (c) 2011 Roberto Dario Seminara <robertodarioseminara@gmail.com>

imageruby-bmp-c is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

imageruby-bmp-c is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with imageruby-bmp-c.  if not, see <http://www.gnu.org/licenses/>.

*/

#include "ruby.h"

VALUE m_ImageRubyBmpC;
ID id_pixel_data;

int get_int(const char* ptr) {
	return *((int*)ptr);
}

VALUE rb_decode_bitmap(VALUE recv, VALUE rb_data, VALUE rb_image) {
	const char* data_string = RSTRING(rb_data)->ptr;
	const char* dib_header = data_string + 14;
	const char* header = data_string;

	int pixel_data_offset = get_int(header+10);
	int width = get_int(dib_header+4);
	int height = get_int(dib_header+8);

	int bpp = get_int(dib_header+14);

	VALUE rb_pixel_data = rb_funcall(rb_image, id_pixel_data, 0);
	char* image_pixel_data_string = RSTRING(rb_pixel_data)->ptr;

	const char* file_pixel_data_string = data_string+pixel_data_offset;

	if (bpp == 24) {
	  int padding_size = ( 4 - (width * 3 % 4) ) % 4;
	  int width_array_len = width*3+padding_size;
	  int offset;
      int y;

	  for (y=0; y<height; y++) {
		memcpy(image_pixel_data_string+(y*width)*3,  file_pixel_data_string+(height-y-1)*width_array_len,  width*3);
	  }

	} else if (bpp == 32) {
	  int width_array_len = width*3;
	  int offset;
      int x,y;

      VALUE rb_alpha_data = rb_funcall(rb_image, id_alpha_data, 0);
      const char* alpha_data_string = RSTRING(rb_alpha_data)->ptr;

	  for (y=0; y<height; y++) {
	    for (x=0; x<width; x++) {

            int offset = pixel_data_offset+x*4+(height-y-1)*width_array_len;
            int index = (y*width+x)*3;

            image_pixel_data_string[index] = file_pixel_data_string[offset];
            image_pixel_data_string[index+1] = file_pixel_data_string[offset+1];
            image_pixel_data_string[index+2] = file_pixel_data_string[offset+2];

            alpha_data_string[y*width+x] = file_pixel_data_string[offset+3];
		}
	  }

	}

	return Qnil;
}

VALUE rb_encode_bitmap(VALUE recv, VALUE image) {
	return Qnil;
}

extern void Init_imageruby_bmp_base() {
	m_ImageRubyBmpC = rb_define_module("ImageRubyBmpC");

	id_pixel_data = rb_intern("pixel_data");

	rb_define_singleton_method(m_ImageRubyBmpC, "decode_bitmap", rb_decode_bitmap, 2);
	rb_define_singleton_method(m_ImageRubyBmpC, "encode_bitmap", rb_encode_bitmap, 1);
}

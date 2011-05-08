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
require "ruby.h"

VALUE m_ImageRubyBmpC;

VALUE rb_decode_bitmap(VALUE recv, VALUE data, VALUE image) {
	return Qnil;
}

VALUE rb_encode_bitmap(VALUE recv, VALUE image) {
	return Qnil;
}

extern void Init_imageruby_bmp_base() {
	m_ImageRubyBmpC = rb_define_module("ImageRubyBmpC")

	rb_define_singleton_method(m_ImageRubyBmpC, "decode_bitmap", rb_decode_bitmap, 2);
	rb_define_singleton_method(m_ImageRubyBmpC, "encode_bitmap", rb_encode_bitmap, 1);
}

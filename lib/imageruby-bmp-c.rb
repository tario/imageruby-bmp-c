=begin

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

=end
require "imageruby_bmp_base"

module ImageRuby
  class BmpCDecoder < ImageRuby::Decoder
    def decode(data, image_class)
      if data[0..1] != "BM"
        raise UnableToDecodeException
      end

      image = image_class.new(width,height)
      ImageRubyBmpC.decode_bitmap(data, image)
      image
    end
  end

  class BmpCEncoder < ImageRuby::Decoder
    def encode(image, format, output)
      if format != :bmp
        raise UnableToEncodeException
      end

      output << ImageRubyBmpC.encode_bitmap(image)
    end
  end

end



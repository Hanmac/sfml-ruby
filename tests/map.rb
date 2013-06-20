require "tiled_tmx"

require_relative "../ext/sfml"

module TiledTmx
  class Tileset
    def draw(id,x,y,z,opacity,rot,x_scale,y_scale,&block)
      @sfml_image ||= SFML::Image.load_file(source.to_s)
      @sfml_textures ||= []

      @sfml_textures[id] ||= @sfml_image.to_texture SFML::Rect.new(
        id % (@width / @tilewidth) * @tilewidth,
        id * @tilewidth / @width * @tileheight,
        @tilewidth,@tileheight
      )

      block.call.draw SFML::Sprite.new.tap {|s|
        s.texture = @sfml_textures[id]
        s.position = SFML::Vector2.new(-x,-y)
        s.color = SFML::Color.new(255,255,255,opacity * 255)
      }

    end
  end
end

window = SFML::RenderWindow.new("Paint-Test")

c = SFML::Color.new(128,128,0)

map = TiledTmx::Map.load_xml("map.tmx")

v = window.view

v.center = SFML::Vector2.new(0,0)
v.zoom 0.75

while window.open?

  if e = window.poll_event
    if e.type == :closed
      window.close
    end
  end
  window.clear c

  #window.draw s
  map.draw(0,0,0) { window }

  window.display
end
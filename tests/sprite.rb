require_relative "../ext/sfml"

window = SFML::RenderWindow.new("Paint-Test")

c = SFML::Color.new(128,128,0)

i = SFML::Image.load_file "textures.png"

s1 = SFML::Sprite.new
s1.position = SFML::Vector2.new(0,0)
s1.texture = i.to_texture SFML::Rect.new(0,0,32,32)

s2 = SFML::Sprite.new
s2.position = SFML::Vector2.new(32,0)
s2.texture = i.to_texture SFML::Rect.new(32,0,32,32)

s3 = SFML::Sprite.new
s3.position = SFML::Vector2.new(32*2,0)
s3.texture = i.to_texture SFML::Rect.new(32*2,0,32,32)

s4 = SFML::Sprite.new
s4.position = SFML::Vector2.new(32*3,0)
s4.texture = i.to_texture SFML::Rect.new(32*3,0,32,32)

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
  
  window.draw s1
  window.draw s2
  window.draw s3
  window.draw s4
  
  window.display
end
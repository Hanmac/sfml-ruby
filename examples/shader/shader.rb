begin
  require "sfml"
rescue LoadError
  require_relative "../../ext/sfml"
end

class Effect
  include SFML::Drawable
  
  attr_accessor :target, :shader
  
  def initialize(target,shader)
    @target, @shader = target,shader
  end
  
  def draw(render, states)
    render.draw @target, states.merge(:shader => @shader)
  end
end

class Pixelate < Effect
  def initialize
    sprite = SFML::Sprite.new
    sprite.texture = SFML::Texture.load_file("resources/background.jpg")
    
    shader = SFML::Shader.load_file(:frag => "resources/pixelate.frag")
    shader.set_parameter("texture",:current)

    super sprite, shader
  end

  def update(time,x,y)
    @shader.set_parameter("pixel_threshold", (x + y) / 30);
  end


end

class WaveBlur < Effect

  def initialize
        text = SFML::Text.new
        text.string = <<-HERE

Praesent suscipit augue in velit pulvinar hendrerit varius purus aliquam.
Mauris mi odio, bibendum quis fringilla a, laoreet vel orci. Proin vitae vulputate tortor.
Praesent cursus ultrices justo, ut feugiat ante vehicula quis.
Donec fringilla scelerisque mauris et viverra.
Maecenas adipiscing ornare scelerisque. Nullam at libero elit.
Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.
Nullam leo urna, tincidunt id semper eget, ultricies sed mi.
Morbi mauris massa, commodo id dignissim vel, lobortis et elit.
Fusce vel libero sed neque scelerisque venenatis.
Integer mattis tincidunt quam vitae iaculis.
Vivamus fringilla sem non velit venenatis fermentum.
Vivamus varius tincidunt nisi id vehicula.
Integer ullamcorper, enim vitae euismod rutrum, massa nisl semper ipsum,
vestibulum sodales sem ante in massa.
Vestibulum in augue non felis convallis viverra.
Mauris ultricies dolor sed massa convallis sed aliquet augue fringilla.
Duis erat eros, porta in accumsan in, blandit quis sem.
In hac habitasse platea dictumst. Etiam fringilla est id odio dapibus sit amet semper dui laoreet.

HERE
        text.font = SFML::Font.load_file("resources/sansation.ttf")             

        text.character_size = 22
        text.position = SFML::Vector2.new(30, 20)

        shader = SFML::Shader.load_file("resources/wave.vert", "resources/blur.frag")

        super text,shader
    end

  def update(time,x,y)
    @shader.set_parameter("wave_phase", time)
    @shader.set_parameter("wave_amplitude", SFML::Vector2.new(x * 40, y * 40))
    @shader.set_parameter("blur_radius", (x + y) * 0.008)
  end
end

font = SFML::Font.load_file("resources/sansation.ttf")


window = SFML::RenderWindow.new("Paint-Test",SFML::VideoMode.new(800,600))

c = SFML::Color.new(255,128,0)

effects = [] << Pixelate.new << WaveBlur.new
  
current = 1


textBackground = SFML::Sprite.new :texture  => SFML::Texture.load_file("resources/text-background.png"),
  :position => SFML::Vector2.new(0, 520),
  :color    => SFML::Color.new(255, 255, 255, 200)

description = SFML::Text.new :string => "Current effect: #{effects[current].class}",
  :font           => font,
  :character_size => 20,
  :position       => SFML::Vector2.new(10, 530),
  :color          => SFML::Color.new(80, 80, 80)

instructions = SFML::Text.new :string => "Press left and right arrows to change the current shader",
  :font           => font,
  :character_size => 20,
  :position       => SFML::Vector2.new(280, 555),
  :color          => SFML::Color.new(80, 80, 80)

cl = SFML::Clock.new
while window.open?
  
  if e = window.poll_event
    if e.type == :closed
      window.close
    end
  end
  window.clear c
  
  pos = window.mouse_position
  size = window.size
  effects[current].update(cl.time.to_f, pos.x.to_f / size.x, pos.y.to_f / size.y )
  
  window.draw effects[current]

  window.draw textBackground
  window.draw description
  window.draw instructions
  window.display
end
require_relative "../ext/sfml"

window = SFML::RenderWindow.new("Paint-Test")

c = SFML::Color.new(255,0,0)

while window.open?
  
  if e = window.poll_event
    if e.type == :closed
      window.close
    elsif e.type == :text_entered
      p e.unicode#.force_encoding("UTF-8") # returns UTF-16
    elsif e.type == :mouse_button_pressed
      c = SFML::Color.new(rand(255),rand(255),rand(255))
    end
  end
  window.clear c
  
  window.display
end
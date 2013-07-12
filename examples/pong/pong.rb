begin
  require "sfml"
rescue LoadError
  require_relative "../../ext/sfml"
end

game_width, game_height = 800, 600

paddleSize = SFML::Vector2.new(25, 100)

ballRadius = 10.0

font = SFML::Font.load_file("resources/sansation.ttf")

window = SFML::RenderWindow.new("SFML Pong",SFML::VideoMode.new(game_width,game_height))

leftPaddle = SFML::RectangleShape.new(
  :size => (paddleSize - SFML::Vector2.new(3, 3)),
  :outline_thickness  => 3,
  :outline_color => SFML::Color.new(0,0,0),
  :fill_color => SFML::Color.new(100, 100, 200),
  :origin => paddleSize / 2.0
)
rightPaddle = SFML::RectangleShape.new(
  :size => (paddleSize - SFML::Vector2.new(3, 3)),
  :outline_thickness  => 3,
  :outline_color => SFML::Color.new(0,0,0),
  :fill_color => SFML::Color.new(200, 100, 100),
  :origin => paddleSize / 2.0
)

ball = SFML::CircleShape.new(
  :radius => ballRadius - 3,
  :outline_thickness  => 3,
  :outline_color => SFML::Color.new(0,0,0),
  :fill_color => SFML::Color.new(255, 255, 255),
  :origin => SFML::Vector2.new(ballRadius / 2.0, ballRadius / 2.0)
)

pauseMessage = SFML::Text.new(
:font => font,
:character_size => 40,
:position => SFML::Vector2.new(170.0, 150.0),
:color => SFML::Color.new(255,255,255),
:string => "Welcome to SFML pong!\nPress space to start the game"
)

clear_color = SFML::Color.new(50, 200, 50)

paddleSpeed = 400.0
rightPaddleSpeed  = 0.0
ballSpeed   = 400.0

@playing = false
clock = SFML::Clock.new

while window.open?

  if e = window.poll_event
    if e.type == :closed
      window.close
    elsif e.type == :key_pressed
      case e.code
      when :escape
        window.close
      when :space
        unless @playing
          @playing = true
          clock.restart
          leftPaddle.position = SFML::Vector2.new(10 + paddleSize.x / 2, game_height / 2);
          rightPaddle.position = SFML::Vector2.new(game_width - 10 - paddleSize.x / 2, game_height / 2);
          ball.position = SFML::Vector2.new(game_width / 2, game_height / 2);

          begin
            @ball_angle = rand(360) * 2 * Math::PI / 360
          end until Math.cos(@ball_angle).abs < 0.7

        end
      end

    end
  end

  if(@playing)
    deltaTime = clock.restart().to_f

    #// Move the player's paddle
    if (SFML::Keyboard::key_pressed?(:up) &&
    (leftPaddle.position.y - paddleSize.y / 2 > 5.0))
      leftPaddle.move(0.0, -paddleSpeed * deltaTime)
    end
    if (SFML::Keyboard::key_pressed?(:down) &&
    (leftPaddle.position.y + paddleSize.y / 2 < game_height - 5.0))
      leftPaddle.move(0.0, paddleSpeed * deltaTime)
    end
    
    #// Move the computer's paddle
    if (((rightPaddleSpeed < 0.0) && (rightPaddle.position.y - paddleSize.y / 2 > 5.0)) ||
                    ((rightPaddleSpeed > 0.0) && (rightPaddle.position.y + paddleSize.y / 2 < game_height - 5.0)))
                    rightPaddle.move(0.0, rightPaddleSpeed * deltaTime)
    end
    
    #// Update the computer's paddle direction according to the ball position
#    if (AITimer.getElapsedTime() > AITime)
#                {
#                    AITimer.restart();
#                    if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + paddleSize.y / 2)
#                        rightPaddleSpeed = paddleSpeed;
#                    else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - paddleSize.y / 2)
#                        rightPaddleSpeed = -paddleSpeed;
#                    else
#                        rightPaddleSpeed = 0.f;
#                }
    
    factor = ballSpeed * deltaTime
    ball.move(Math::cos(@ball_angle) * factor, Math::sin(@ball_angle) * factor)

    if (ball.position.y - ballRadius < 0.0)
        #ballSound.play();
        @ball_angle = -@ball_angle;
        ball.position= SFML::Vector2.new(ball.position.x, ballRadius + 0.1)
    end
    if (ball.position.y + ballRadius > game_height)
        #ballSound.play();
        @ball_angle = -@ball_angle;
        ball.position= SFML::Vector2.new(ball.position.x, game_height - ballRadius - 0.1)
    end

  end

  window.clear clear_color

  if(@playing)
    window.draw leftPaddle
    window.draw rightPaddle
    window.draw ball
  else
    window.draw pauseMessage
  end

  window.display
end
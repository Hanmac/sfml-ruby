begin
  require "sfml"
rescue LoadError
  require_relative "../../ext/sfml"
end


def play_sound
  buffer = SFML::SoundBuffer.load_file("resources/canary.wav")
  
  puts "canary.wav :"
  puts "%f seconds" % buffer.duration.to_f
  puts "#{buffer.sample_rate} samples / sec"
  puts "#{buffer.channel_count} channels"
 
  sound = SFML::Sound.new(buffer)
  sound.play
  
  while(sound.status == :playing)
    sleep 0.1
    print "\rPlaying... %2f sec " % sound.playing_offset.to_f
  end
  puts
  puts
end

def play_music
  music = SFML::Music.load_file("resources/orchestral.ogg")
  
  puts "orchestral.ogg :"
  puts "%f seconds" % music.duration.to_f
  puts "#{music.sample_rate} samples / sec"
  puts "#{music.channel_count} channels"
 
  music.play
  
  while(music.status == :playing)
    sleep 0.1
    print "\rPlaying... %2f sec " % music.playing_offset.to_f
  end
  puts
  puts
end


play_sound
play_music


gets
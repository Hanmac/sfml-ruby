require "mkmf"

dir_config "sfml"

pkg_config("sfml-all")

with_cflags("-x c++") {
  abort "sfml-graphics not found" unless find_header("SFML/Graphics.hpp","/usr/local/include") &&
  have_library("sfml-graphics")
  
  have_header("SFML/Audio.hpp") && have_library("sfml-audio")
}

#drop some of the warn flags because they are not valid for C++
CONFIG["warnflags"].gsub!("-Wdeclaration-after-statement","")
CONFIG["warnflags"].gsub!("-Wimplicit-function-declaration","")

CONFIG["warnflags"] << " -Wall -Wextra"


with_cflags("-x c++") {
  have_type("sf::String","SFML/System.hpp")
  have_type("sf::Time","SFML/System.hpp")
}

c11 = " -std=c++11 #{CONFIG["CC"] =~ /clang/ ? " -stdlib=libc++" : ""}"

if have_library("thor")
	with_cflags("-x c++") {
		
		have_header("Thor/Graphics.hpp")
		
		have_header("Thor/Vectors.hpp")
		
	}

	#Thor/Animation and Thor/Particles needs c++11 so they may not work with older compiler
	with_cflags("-x c++ #{c11}") {
		have_header("Thor/Animation.hpp")
		have_header("Thor/Input.hpp")
		have_header("Thor/Particles.hpp")
		have_header("Thor/Resources.hpp")
		have_header("Thor/Time.hpp") #hm time needs input so it should not work without
		have_header("Thor/Shapes.hpp")
	}
end

with_cppflags(c11) {
	create_header
	create_makefile "sfml"
}

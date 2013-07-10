require "mkmf"


dir_config "sfml"

pkg_config("sfml-all")

with_cflags("-x c++") {
  find_header("SFML/Graphics.hpp")
  have_library("sfml-graphics")
}

#drop some of the warn flags because they are not valid for C++
CONFIG["warnflags"].gsub!("-Wdeclaration-after-statement","")
CONFIG["warnflags"].gsub!("-Wimplicit-function-declaration","")

CONFIG["warnflags"] << " -Wall -Wextra"


with_cflags("-x c++") {
  have_type("sf::String","SFML/System.hpp")
  have_type("sf::Time","SFML/System.hpp")
}

CONFIG["CXXFLAGS"] << " -std=c++11"

create_header
create_makefile "sfml"


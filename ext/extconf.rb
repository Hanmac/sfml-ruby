require "mkmf"


dir_config "sfml"

pkg_config("sfml-all")

#drop some of the warn flags because they are not valid for C++
CONFIG["warnflags"].gsub!("-Wdeclaration-after-statement","")
CONFIG["warnflags"].gsub!("-Wimplicit-function-declaration","")

create_header
create_makefile "sfml"

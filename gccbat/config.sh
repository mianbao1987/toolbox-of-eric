#! /bin/sh
#
# Configuration file.
#
# (C) 2011 Free Software Foundation
# This script is Free Software, and it can be copied, distributed and
# modified as defined in the GNU General Public License.  A copy of
# its license can be downloaded from http://www.gnu.org/copyleft/gpl.html

###############
# Directories #
###############

# my directory
TC_MY_DIR=/path/to/gccbat

# contrib directory
TC_CONTRIB_DIR=$TC_MY_DIR/contrib

# gcc source directory
TC_SOURCE_DIR=/path/to/trunk

# gcc build directory
TC_BUILD_DIR=/path/to/build-trunk

# gcc install directory
TC_INSTALL_DIR=/path/to/install

###################
# Command Options #
###################

# configure option
TC_CONFIGURE_OPTION="--prefix=$TC_INSTALL_DIR --with-gmp=... --with-mpfr=... --with-mpc=... --enable-languages=c,c++"

# build option
TC_BUILD_OPTION="CFLAGS=\"-g -O0\""

# make check option
TC_CHECK_OPTION=

###########
# Actions #
###########

# Available actions:
# update	svn update
# clean		remove build directory
# configure 	configure
# build		make
# check		make check-gcc

#TC_ACTION="update clean configure build check"
TC_ACTION="update build check"
#TC_ACTION="build check"


# Makefile for asm2vcg.
#
# Copyright (C) 2009 Eric Fisher, joefoxreal@gmail.com. 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#DEBUG_YACC = -t
#DEBUG_LEX = -d

all:
	bison $(DEBUG_YACC) -d parser.y
	flex $(DEBUG_LEX) parser.l
	gcc -g main.c parser.tab.c lex.yy.c -I ~/tools/cvs-binutils/include ~/tools/build-cvs-binutils/libiberty/libiberty.a -o asm2vcg-gcc

clean:
	rm -f asm2vcg-gcc lex.yy.c parser.tab.c parser.tab.h parser.output

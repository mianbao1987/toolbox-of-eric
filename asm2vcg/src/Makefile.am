# Makefile for asm2vcg.
# 
# Copyright (C) 2009 Eric Fisher, joefoxreal@gmail.com. 
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS = asm2vcg

AM_YFLAGS = -d -t
AM_CFLAGS = $(LIBERTY_INC)

asm2vcg_SOURCES = main.c yacc.y lex.l asm2vcg.h
asm2vcg_LDFLAGS = -liberty $(LIBERTY_LIB)


#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sMineField.o \
	${OBJECTDIR}/MineController.o \
	${OBJECTDIR}/sCell.o \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath ../libMine/dist/Debug/GNU-Linux-x86 -L../libMine/dist/Debug/GNU-Linux-x86 -llibMine -Wl,-rpath ../libConf/dist/Debug/GNU-Linux-x86 -L../libConf/dist/Debug/GNU-Linux-x86 -llibConf

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/sdlmine

dist/Debug/GNU-Linux-x86/sdlmine: ../libMine/dist/Debug/GNU-Linux-x86/liblibMine.so

dist/Debug/GNU-Linux-x86/sdlmine: ../libConf/dist/Debug/GNU-Linux-x86/liblibConf.so

dist/Debug/GNU-Linux-x86/sdlmine: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lSDL -lSDL_image -lSDL_gfx -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sdlmine ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sMineField.o: nbproject/Makefile-${CND_CONF}.mk sMineField.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../libMine -I../libConf -MMD -MP -MF $@.d -o ${OBJECTDIR}/sMineField.o sMineField.cpp

${OBJECTDIR}/MineController.o: nbproject/Makefile-${CND_CONF}.mk MineController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../libMine -I../libConf -MMD -MP -MF $@.d -o ${OBJECTDIR}/MineController.o MineController.cpp

${OBJECTDIR}/sCell.o: nbproject/Makefile-${CND_CONF}.mk sCell.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../libMine -I../libConf -MMD -MP -MF $@.d -o ${OBJECTDIR}/sCell.o sCell.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../libMine -I../libConf -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../libMine && ${MAKE}  -f Makefile CONF=Debug
	cd ../libConf && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/sdlmine

# Subprojects
.clean-subprojects:
	cd ../libMine && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libConf && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

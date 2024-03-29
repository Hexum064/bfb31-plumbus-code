#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Release.mk)" "nbproject/Makefile-local-Release.mk"
include nbproject/Makefile-local-Release.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Release
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../games.c ../i2c.c ../io_expander.c ../light_player.c ../main.c ../note_player.c ../rand_seed.c ../song_player.c ../start_mode.c ../ws2812drv.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/games.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/io_expander.o ${OBJECTDIR}/_ext/1472/light_player.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/note_player.o ${OBJECTDIR}/_ext/1472/rand_seed.o ${OBJECTDIR}/_ext/1472/song_player.o ${OBJECTDIR}/_ext/1472/start_mode.o ${OBJECTDIR}/_ext/1472/ws2812drv.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/games.o.d ${OBJECTDIR}/_ext/1472/i2c.o.d ${OBJECTDIR}/_ext/1472/io_expander.o.d ${OBJECTDIR}/_ext/1472/light_player.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/note_player.o.d ${OBJECTDIR}/_ext/1472/rand_seed.o.d ${OBJECTDIR}/_ext/1472/song_player.o.d ${OBJECTDIR}/_ext/1472/start_mode.o.d ${OBJECTDIR}/_ext/1472/ws2812drv.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/games.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/io_expander.o ${OBJECTDIR}/_ext/1472/light_player.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/note_player.o ${OBJECTDIR}/_ext/1472/rand_seed.o ${OBJECTDIR}/_ext/1472/song_player.o ${OBJECTDIR}/_ext/1472/start_mode.o ${OBJECTDIR}/_ext/1472/ws2812drv.o

# Source Files
SOURCEFILES=../games.c ../i2c.c ../io_expander.c ../light_player.c ../main.c ../note_player.c ../rand_seed.c ../song_player.c ../start_mode.c ../ws2812drv.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atxmega16e5"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Release.mk dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATxmega16E5
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/games.o: ../games.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/games.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/games.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/games.o.d" -MT "${OBJECTDIR}/_ext/1472/games.o.d" -MT ${OBJECTDIR}/_ext/1472/games.o  -o ${OBJECTDIR}/_ext/1472/games.o ../games.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT ${OBJECTDIR}/_ext/1472/i2c.o  -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io_expander.o: ../io_expander.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io_expander.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io_expander.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/io_expander.o.d" -MT "${OBJECTDIR}/_ext/1472/io_expander.o.d" -MT ${OBJECTDIR}/_ext/1472/io_expander.o  -o ${OBJECTDIR}/_ext/1472/io_expander.o ../io_expander.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/light_player.o: ../light_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/light_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/light_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/light_player.o.d" -MT "${OBJECTDIR}/_ext/1472/light_player.o.d" -MT ${OBJECTDIR}/_ext/1472/light_player.o  -o ${OBJECTDIR}/_ext/1472/light_player.o ../light_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/main.o.d" -MT "${OBJECTDIR}/_ext/1472/main.o.d" -MT ${OBJECTDIR}/_ext/1472/main.o  -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/note_player.o: ../note_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/note_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/note_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/note_player.o.d" -MT "${OBJECTDIR}/_ext/1472/note_player.o.d" -MT ${OBJECTDIR}/_ext/1472/note_player.o  -o ${OBJECTDIR}/_ext/1472/note_player.o ../note_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rand_seed.o: ../rand_seed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rand_seed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rand_seed.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/rand_seed.o.d" -MT "${OBJECTDIR}/_ext/1472/rand_seed.o.d" -MT ${OBJECTDIR}/_ext/1472/rand_seed.o  -o ${OBJECTDIR}/_ext/1472/rand_seed.o ../rand_seed.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/song_player.o: ../song_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/song_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/song_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/song_player.o.d" -MT "${OBJECTDIR}/_ext/1472/song_player.o.d" -MT ${OBJECTDIR}/_ext/1472/song_player.o  -o ${OBJECTDIR}/_ext/1472/song_player.o ../song_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/start_mode.o: ../start_mode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/start_mode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/start_mode.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/start_mode.o.d" -MT "${OBJECTDIR}/_ext/1472/start_mode.o.d" -MT ${OBJECTDIR}/_ext/1472/start_mode.o  -o ${OBJECTDIR}/_ext/1472/start_mode.o ../start_mode.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/ws2812drv.o: ../ws2812drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ws2812drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ws2812drv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5" -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/ws2812drv.o.d" -MT "${OBJECTDIR}/_ext/1472/ws2812drv.o.d" -MT ${OBJECTDIR}/_ext/1472/ws2812drv.o  -o ${OBJECTDIR}/_ext/1472/ws2812drv.o ../ws2812drv.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/games.o: ../games.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/games.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/games.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/games.o.d" -MT "${OBJECTDIR}/_ext/1472/games.o.d" -MT ${OBJECTDIR}/_ext/1472/games.o  -o ${OBJECTDIR}/_ext/1472/games.o ../games.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT "${OBJECTDIR}/_ext/1472/i2c.o.d" -MT ${OBJECTDIR}/_ext/1472/i2c.o  -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io_expander.o: ../io_expander.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io_expander.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io_expander.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/io_expander.o.d" -MT "${OBJECTDIR}/_ext/1472/io_expander.o.d" -MT ${OBJECTDIR}/_ext/1472/io_expander.o  -o ${OBJECTDIR}/_ext/1472/io_expander.o ../io_expander.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/light_player.o: ../light_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/light_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/light_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/light_player.o.d" -MT "${OBJECTDIR}/_ext/1472/light_player.o.d" -MT ${OBJECTDIR}/_ext/1472/light_player.o  -o ${OBJECTDIR}/_ext/1472/light_player.o ../light_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/main.o.d" -MT "${OBJECTDIR}/_ext/1472/main.o.d" -MT ${OBJECTDIR}/_ext/1472/main.o  -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/note_player.o: ../note_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/note_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/note_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/note_player.o.d" -MT "${OBJECTDIR}/_ext/1472/note_player.o.d" -MT ${OBJECTDIR}/_ext/1472/note_player.o  -o ${OBJECTDIR}/_ext/1472/note_player.o ../note_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rand_seed.o: ../rand_seed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rand_seed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rand_seed.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/rand_seed.o.d" -MT "${OBJECTDIR}/_ext/1472/rand_seed.o.d" -MT ${OBJECTDIR}/_ext/1472/rand_seed.o  -o ${OBJECTDIR}/_ext/1472/rand_seed.o ../rand_seed.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/song_player.o: ../song_player.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/song_player.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/song_player.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/song_player.o.d" -MT "${OBJECTDIR}/_ext/1472/song_player.o.d" -MT ${OBJECTDIR}/_ext/1472/song_player.o  -o ${OBJECTDIR}/_ext/1472/song_player.o ../song_player.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/start_mode.o: ../start_mode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/start_mode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/start_mode.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/start_mode.o.d" -MT "${OBJECTDIR}/_ext/1472/start_mode.o.d" -MT ${OBJECTDIR}/_ext/1472/start_mode.o  -o ${OBJECTDIR}/_ext/1472/start_mode.o ../start_mode.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/ws2812drv.o: ../ws2812drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ws2812drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ws2812drv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atxmega16e5  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/include" -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DNDEBUG -Wall -MD -MP -MF "${OBJECTDIR}/_ext/1472/ws2812drv.o.d" -MT "${OBJECTDIR}/_ext/1472/ws2812drv.o.d" -MT ${OBJECTDIR}/_ext/1472/ws2812drv.o  -o ${OBJECTDIR}/_ext/1472/ws2812drv.o ../ws2812drv.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atxmega16e5 -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\xmega16e5-plumbus-full.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,-lm -Wl,--end-group 
	
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.srec"
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atxmega16e5 -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/XMEGAE_DFP/1.3.114/gcc/dev/atxmega16e5"  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\xmega16e5-plumbus-full.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.hex"
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/xmega16e5-plumbus-full.X.${IMAGE_TYPE}.srec"
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} -r dist/Release

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

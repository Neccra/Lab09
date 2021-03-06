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
ifeq "$(wildcard nbproject/Makefile-local-Negotiation_Test.mk)" "nbproject/Makefile-local-Negotiation_Test.mk"
include nbproject/Makefile-local-Negotiation_Test.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Negotiation_Test
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=BOARD.c CircularBuffer.c FieldOled.c Uart1.c Message.c Negotiation.c Agent.c NegotiationTest.c Field.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/BOARD.o ${OBJECTDIR}/CircularBuffer.o ${OBJECTDIR}/FieldOled.o ${OBJECTDIR}/Uart1.o ${OBJECTDIR}/Message.o ${OBJECTDIR}/Negotiation.o ${OBJECTDIR}/Agent.o ${OBJECTDIR}/NegotiationTest.o ${OBJECTDIR}/Field.o
POSSIBLE_DEPFILES=${OBJECTDIR}/BOARD.o.d ${OBJECTDIR}/CircularBuffer.o.d ${OBJECTDIR}/FieldOled.o.d ${OBJECTDIR}/Uart1.o.d ${OBJECTDIR}/Message.o.d ${OBJECTDIR}/Negotiation.o.d ${OBJECTDIR}/Agent.o.d ${OBJECTDIR}/NegotiationTest.o.d ${OBJECTDIR}/Field.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/BOARD.o ${OBJECTDIR}/CircularBuffer.o ${OBJECTDIR}/FieldOled.o ${OBJECTDIR}/Uart1.o ${OBJECTDIR}/Message.o ${OBJECTDIR}/Negotiation.o ${OBJECTDIR}/Agent.o ${OBJECTDIR}/NegotiationTest.o ${OBJECTDIR}/Field.o

# Source Files
SOURCEFILES=BOARD.c CircularBuffer.c FieldOled.c Uart1.c Message.c Negotiation.c Agent.c NegotiationTest.c Field.c


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
	${MAKE}  -f nbproject/Makefile-Negotiation_Test.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX340F512H
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/BOARD.o: BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BOARD.o.d 
	@${RM} ${OBJECTDIR}/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/BOARD.o.d" -o ${OBJECTDIR}/BOARD.o BOARD.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/CircularBuffer.o: CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CircularBuffer.o.d 
	@${RM} ${OBJECTDIR}/CircularBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/CircularBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/CircularBuffer.o.d" -o ${OBJECTDIR}/CircularBuffer.o CircularBuffer.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FieldOled.o: FieldOled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FieldOled.o.d 
	@${RM} ${OBJECTDIR}/FieldOled.o 
	@${FIXDEPS} "${OBJECTDIR}/FieldOled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/FieldOled.o.d" -o ${OBJECTDIR}/FieldOled.o FieldOled.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Uart1.o: Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Uart1.o.d 
	@${RM} ${OBJECTDIR}/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Uart1.o.d" -o ${OBJECTDIR}/Uart1.o Uart1.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Message.o: Message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Message.o.d 
	@${RM} ${OBJECTDIR}/Message.o 
	@${FIXDEPS} "${OBJECTDIR}/Message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Message.o.d" -o ${OBJECTDIR}/Message.o Message.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Negotiation.o: Negotiation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Negotiation.o.d 
	@${RM} ${OBJECTDIR}/Negotiation.o 
	@${FIXDEPS} "${OBJECTDIR}/Negotiation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Negotiation.o.d" -o ${OBJECTDIR}/Negotiation.o Negotiation.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Agent.o: Agent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Agent.o.d 
	@${RM} ${OBJECTDIR}/Agent.o 
	@${FIXDEPS} "${OBJECTDIR}/Agent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Agent.o.d" -o ${OBJECTDIR}/Agent.o Agent.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NegotiationTest.o: NegotiationTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NegotiationTest.o.d 
	@${RM} ${OBJECTDIR}/NegotiationTest.o 
	@${FIXDEPS} "${OBJECTDIR}/NegotiationTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/NegotiationTest.o.d" -o ${OBJECTDIR}/NegotiationTest.o NegotiationTest.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Field.o: Field.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Field.o.d 
	@${RM} ${OBJECTDIR}/Field.o 
	@${FIXDEPS} "${OBJECTDIR}/Field.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Field.o.d" -o ${OBJECTDIR}/Field.o Field.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/BOARD.o: BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BOARD.o.d 
	@${RM} ${OBJECTDIR}/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/BOARD.o.d" -o ${OBJECTDIR}/BOARD.o BOARD.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/CircularBuffer.o: CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CircularBuffer.o.d 
	@${RM} ${OBJECTDIR}/CircularBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/CircularBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/CircularBuffer.o.d" -o ${OBJECTDIR}/CircularBuffer.o CircularBuffer.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FieldOled.o: FieldOled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FieldOled.o.d 
	@${RM} ${OBJECTDIR}/FieldOled.o 
	@${FIXDEPS} "${OBJECTDIR}/FieldOled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/FieldOled.o.d" -o ${OBJECTDIR}/FieldOled.o FieldOled.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Uart1.o: Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Uart1.o.d 
	@${RM} ${OBJECTDIR}/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Uart1.o.d" -o ${OBJECTDIR}/Uart1.o Uart1.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Message.o: Message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Message.o.d 
	@${RM} ${OBJECTDIR}/Message.o 
	@${FIXDEPS} "${OBJECTDIR}/Message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Message.o.d" -o ${OBJECTDIR}/Message.o Message.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Negotiation.o: Negotiation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Negotiation.o.d 
	@${RM} ${OBJECTDIR}/Negotiation.o 
	@${FIXDEPS} "${OBJECTDIR}/Negotiation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Negotiation.o.d" -o ${OBJECTDIR}/Negotiation.o Negotiation.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Agent.o: Agent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Agent.o.d 
	@${RM} ${OBJECTDIR}/Agent.o 
	@${FIXDEPS} "${OBJECTDIR}/Agent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Agent.o.d" -o ${OBJECTDIR}/Agent.o Agent.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/NegotiationTest.o: NegotiationTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NegotiationTest.o.d 
	@${RM} ${OBJECTDIR}/NegotiationTest.o 
	@${FIXDEPS} "${OBJECTDIR}/NegotiationTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/NegotiationTest.o.d" -o ${OBJECTDIR}/NegotiationTest.o NegotiationTest.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Field.o: Field.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Field.o.d 
	@${RM} ${OBJECTDIR}/Field.o 
	@${FIXDEPS} "${OBJECTDIR}/Field.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Wall -MMD -MF "${OBJECTDIR}/Field.o.d" -o ${OBJECTDIR}/Field.o Field.c    -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  Lab9SupportLib.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSimulator=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    Lab9SupportLib.a      -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=Simulator=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  Lab9SupportLib.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    Lab9SupportLib.a      -DXPRJ_Negotiation_Test=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab09.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Negotiation_Test
	${RM} -r dist/Negotiation_Test

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
